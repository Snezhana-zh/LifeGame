#include "LifeGameHeader.hpp"

const char* Exception::what() const noexcept 
{
	return errorMessage.c_str();
}
const char* Exception::where() const noexcept 
{
	return functionName.c_str();
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
	size_t sizeBoard = board.GetSize();
	for (unsigned int i = 0; i < sizeBoard; i++)
	{
		for (unsigned int j = 0; j < sizeBoard; j++)
		{
			if (board.GetElement(j, i))
			{
				out << std::setw(2) << '*';
			}
			else
			{
				out << std::setw(2) << ' ';
			}
		}
		out << std::endl;
	}
	return out;
}

Point::Point() : x(0), y(0), isLive(0) {}
Point::Point(int x, int y, bool isLive, size_t sizeBoard) : x(x), y(y), isLive(isLive)
{
	Normalize(sizeBoard);
}
bool Point::IsLive() const
{
	return isLive;
}
int Point::FirstCoordinate()  const 
{
	return x;
}
int Point::SecondCoordinate() const 
{
	return y;
}
void Point::IsLive(bool val)
{
	isLive = val;
}
void Point::Normalize(size_t sizeBoard) 
{
	int i = x;
	int j = y;
	if (i < 0)
	{
		x = sizeBoard + i;
	}
	else if (i >= sizeBoard)
	{
		x = i - sizeBoard;
	}
	if (j < 0)
	{
		y = sizeBoard + j;
	}
	else if (j >= sizeBoard)
	{
		y = j - sizeBoard;
	}
	if (x < 0 || y < 0 || x >= sizeBoard || y >= sizeBoard) {
		x = 0;
		y = 0;
	}
}
void Point::CoordinatesNeighbours(int neighbours[][2], size_t sizeBoard) const
{
	unsigned int k = 0;
	for (int i = x - 1; i < x + 2; ++i) 
	{
		for (int j = y - 1; j < y + 2; ++j) 
		{
			Point p(i, j, false, sizeBoard);
			if (p.x == x && p.y == y) 
			{
				continue;
			}
			neighbours[k][0] = p.x;
			neighbours[k][1] = p.y;
			k++;
		}
	}
}
unsigned char Point::CountLiveNeighbours(const std::vector<Point>& data, size_t sizeBoard) const
{
	int neighbours[countNeighbours][2];
	CoordinatesNeighbours(neighbours, sizeBoard);
	unsigned char count = 0;
	for (int i = 0; i < countNeighbours; ++i) 
	{
		int xt = neighbours[i][0];
		int yt = neighbours[i][1];
		if (data.at(yt * sizeBoard + xt).IsLive()) 
		{
			count++;
		}
	}
	return count;
}

template<typename Stream>
Stream openFile(const std::string& filename) 
{
	Stream ifs(filename);
	if (!ifs) {
		throw std::ifstream::failbit;
	}
	return ifs;
}

Board::Board(size_t size, const std::string& filename) : data(new std::vector<Point>(size * size)), 
	sizeBoard(size)
{
	for (unsigned int y = 0; y < sizeBoard; ++y) 
	{
		for (unsigned int x = 0; x < sizeBoard; ++x)
		{
			Point pt(x, y, false, sizeBoard);
			data->at(y * sizeBoard + x) = pt;
		}
	}
	std::ifstream ifs = openFile<std::ifstream>(filename);
	std::string coordinates;
	while(std::getline(ifs, coordinates)) 
	{
		if (coordinates[0] == '#' || coordinates.find(' ') == coordinates.npos) 
		{
			continue;
		}
		if (coordinates.size() < 3) 
		{
			throw Exception("Wrong count of coordinates in the input file", __func__);
		}
		size_t pos = coordinates.find(' ');
		std::string xt = coordinates.substr(0, pos);
		if (pos + 1 >= coordinates.size()) {
			throw Exception("Wrong coordinates", __func__);
		}
		std::string yt = coordinates.substr(pos + 1);
		Point p(std::stoi(xt), std::stoi(yt), true, sizeBoard);
		PushPoint(p);
	}
}
Board::Board(size_t size) : sizeBoard(size) , data(new std::vector<Point>(size* size)) 
{
	for (unsigned int y = 0; y < sizeBoard; ++y)
	{
		for (unsigned int x = 0; x < sizeBoard; ++x)
		{
			Point pt(x, y, false, sizeBoard);
			data->at(y * sizeBoard + x) = pt;
		}
	}
}
Board::~Board()
{
	delete data;
}
void Board::PushPoint(Point p) 
{
	if (p.SecondCoordinate() >= sizeBoard || p.FirstCoordinate() >= sizeBoard) 
	{
		throw Exception("The Normalize func in class Point works wrong", __func__);
	}
	data->at(p.SecondCoordinate() * sizeBoard + p.FirstCoordinate()) = p;
}
unsigned int Board::LivePointCount() const
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < sizeBoard; ++i) 
	{
		for (unsigned int j = 0; j < sizeBoard; ++j) 
		{
			if (data->at(i * sizeBoard + j).IsLive()) 
			{
				count++;
			}
		}
	}
	return count;
}
size_t Board::GetSize() const
{
	return sizeBoard;
}
void Board::NextGeneration(const std::string& birthPointCount, const std::string& survivalPointCount)
{
	std::vector<Point>* newData = new std::vector<Point>(sizeBoard * sizeBoard);
	*newData = *data;
	for (size_t l = 0; l < data->size(); ++l) 
	{
		Point p = data->at(l);
		Point& newP = newData->at(l);
		unsigned char countLiveNb = p.CountLiveNeighbours(*data, sizeBoard);
		if (p.IsLive())
		{
			if (survivalPointCount.find(std::to_string(countLiveNb)) != survivalPointCount.npos)
			{
				newP.IsLive(true);
			}
			else {
				newP.IsLive(false);
			}
		}
		else
		{
			if (birthPointCount.find(std::to_string(countLiveNb)) != birthPointCount.npos)
			{
				newP.IsLive(true);
			}
			else
			{
				newP.IsLive(false);
			}
		}
	}		
	delete data;
	data = newData;
}
bool Board::GetElement(int x, int y) const 
{
	if (sizeBoard <= 0) {
		throw Exception("Board is empty", __func__);
	}
	Point p(x, y, false, sizeBoard);
	return data->at(p.SecondCoordinate() * sizeBoard + p.FirstCoordinate()).IsLive();
}

Life::Life(const std::string& inputName, size_t size, const std::string_view& universeName_t,
	const std::string_view& birthPointCount_t, const std::string_view& survivalPointCount_t) : inputName(inputName), sizeBoard(size),
	universeName(universeName_t), birthPointCount(birthPointCount_t), survivalPointCount(survivalPointCount_t)
{
	std::ifstream ifs = openFile<std::ifstream>(inputName);
	std::string str;
	while (true)
	{
		if (!std::getline(ifs, str)) 
		{
			throw Exception("Cannot read file", __func__);
		}
		if (str[0] != '#') 
		{
			sizeBoard = std::stoi(str);
			break;
		}
		else if (str.size() > 2 && str[0] == '#')
		{
			if (str[1] == 'N')
			{
				universeName = str.substr(3);
			}
			if (str[1] == 'R')
			{
				size_t pos = str.find('/');
				if (str.size() < 8 || pos == str.npos || pos < 5 || pos + 2 > str.size()) 
				{
					throw Exception("Wrong parameter of game", __func__);
				}
				birthPointCount = str.substr(4, pos - 4);
				survivalPointCount = str.substr(pos + 2);
			}
		}
	}
	board = new Board(sizeBoard, inputName);
}
Life::~Life()
{
	delete board;
}
void Life::Dump(const std::string& outputName) const
{
	std::ofstream out = openFile<std::ofstream>(outputName);
	out << "Name universe: " << universeName << std::endl <<
		"Game parameters: " << "B" + birthPointCount + "/" + "S" + survivalPointCount << std::endl;
	out << "Playing board: " << std::endl;
	out << *board;
}
void Life::Tick(unsigned int n)
{
	for (unsigned int i = 0; i < n; ++i) {
		board->NextGeneration(birthPointCount, survivalPointCount);
	}
}
void Life::Help() const
{
	std::ifstream ifs("help.txt");
	std::string str;
	while (std::getline(ifs, str)) 
	{
		std::cout << str << std::endl;
	}
}
void Life::PrintGame(std::ostream& out) const 
{
	out << "Name universe: " << universeName << std::endl <<
		"Game parameters: " << "B" + birthPointCount + "/" + "S" + survivalPointCount << std::endl;
	out << "Playing board: " << std::endl;
	out << *board;
}