#include <iostream>
#include <vector>
#include <string_view>
#include <exception>
#include <fstream>
#include <string>
#include <iomanip>

class Exception : public std::exception {
public:
	Exception(const std::string& message, const std::string& function = "in.txt")
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
	bool IsLive() const;
	int FirstCoordinate() const;
	int SecondCoordinate() const;
	void IsLive(bool val);
	void CoordinatesNeighbours(int neighbours[][2], size_t sizeBoard) const;
	unsigned char CountLiveNeighbours(const std::vector<Point>& data, size_t sizeBoard) const;
private:
	int x;
	int y;
	bool isLive;
};

class Board
{
public:
	Board(size_t size, const std::string& filename);
	Board(size_t size);
	~Board();
	void PushPoint(Point p);
	unsigned int LivePointCount() const;
	void NextGeneration(const std::string& birthPointCount, const std::string& survivalPointCount);
	size_t GetSize() const;
	bool GetElement(int x = 0, int y = 0) const;
private:
	std::vector<Point>* data;
	size_t sizeBoard;
};

class Life {
public:
	Life(const std::string& inputName = "in.txt", size_t size = 0, const std::string_view& universeName_t = "My Universe", 
		const std::string_view& birthPointCount = "3", const std::string_view& survivalPointCount = "23");	
	~Life();
	void Dump(const std::string& outputName = "out.txt") const;
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