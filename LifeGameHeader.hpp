#pragma once
#include <iostream>
#include <vector>
#include <string_view>
#include <exception>
#include <fstream>
#include <string>
#include <iomanip>

class Point;

using GameField = std::vector<Point>;

class Exception : public std::exception {
public:
	Exception(const std::string& message, const std::string& function)
		: errorMessage(message), functionName(function) {}
	const char* what() const noexcept override;

	const char* where() const noexcept;

private:
	std::string errorMessage;
	std::string functionName;
};

class Point
{
	static const unsigned int countNeighbours = 8;
public:
	Point();
	Point(int x, int y, bool isLive = false, size_t sizeBoard = 0);
	void Normalize(size_t sizeBoard);
	bool IsAlive() const;
	int FirstCoordinate() const;
	int SecondCoordinate() const;
	void IsAlive(bool val);
	void CoordinatesNeighbours(int neighbours[][2], size_t sizeBoard) const;
	unsigned char CountLiveNeighbours(const GameField& data, size_t sizeBoard) const;
private:
	int x;
	int y;
	bool isAlive;
};

class Board
{
public:
	Board(size_t size, const std::string& filename);
	Board(size_t size);
	void PushPoint(Point p);
	void NextGeneration(const std::string& birthPointCount, const std::string& survivalPointCount);
	unsigned int LivePointCount() const;
	size_t GetSize() const;
	bool GetElement(int x = 0, int y = 0) const;
	bool ChangeMode() const;
private:
	GameField fields[2];
	bool modeGameField;
	size_t sizeBoard;
};

class Life {
public:
	Life(const std::string& inputName, size_t size = 0, const std::string_view& universeName_t = "My Universe",
		const std::string_view& birthPointCount = "3", const std::string_view& survivalPointCount = "23");
	Life(const std::string_view& universeName_t = "My Universe",
		const std::string_view& birthPointCount = "3", const std::string_view& survivalPointCount = "23");
	~Life();
	void Dump(const std::string& outputName = "out.life") const;
	void Tick(unsigned int n = 1);
	void Help() const;
	void PrintGame(std::ostream& out) const;
private:
	std::string inputName;
	size_t sizeBoard;
	std::string universeName;
	std::string birthPointCount;
	std::string survivalPointCount;
	Board* board;
};

std::ostream& operator<<(std::ostream& out, const Board& board);

template<typename Stream>
Stream openFile(const std::string& filename);