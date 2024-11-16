#include <iostream>
using namespace std;

#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <ctime> 
#include <queue>
#include <vector>
//#include <limits>

class Graph;

class Node2;

using namespace std;
using namespace sf;

const int CELL_SIZE = 20; // Size of each cell in the maze

// Define hash and equal_to for std::pair<int, int> for use in unordered_map
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };

    template <>
    struct equal_to<std::pair<int, int>> {
        bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };
}


class Node2 {
public:
    struct Neighbor {
        Node2* node;
        int weight;
    };

private:
    int row, col;
    int numNeighbors;
    Neighbor* neighbors;

public:
    Node2(int r, int c) : row(r), col(c), numNeighbors(0), neighbors(nullptr) {}

    void addNeighbor(Node2* neighbor, int weight) {
        Neighbor* newNeighbors = new Neighbor[numNeighbors + 1];
        for (int i = 0; i < numNeighbors; ++i) {
            newNeighbors[i] = neighbors[i];
        }
        newNeighbors[numNeighbors++] = { neighbor, weight };
        delete[] neighbors;
        neighbors = newNeighbors;
    }

    const Neighbor* getNeighbors() const {
        return neighbors;
    }

    int getNumNeighbors() const {
        return numNeighbors;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    ~Node2() {
        delete[] neighbors;
    }
};



class Maze {
private:
    Texture mazeTexture;
    Sprite mazeSprite;
    Sprite shortestPathSp;
    int rows, cols;
    int startX, startY; // Starting position
    int exitX, exitY;   // Exit position

public:

    bool** grid;


    Maze(int rows, int cols) : rows(rows), cols(cols) {
        // Load the maze texture
        mazeTexture.loadFromFile("images/redo.jpg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);

        // Initialize grid with all walls
        grid = new bool* [rows];
        for (int i = 0; i < rows; ++i) {
            grid[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = true;
            }
        }

        // Generate the maze with a single escape route
        srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
        generateMaze();

        exitX = cols - 2;
        exitY = 10;

        // Add boundary around the maze
        addBoundary();
    }

    ~Maze() {
        for (int i = 0; i < rows; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    // Copy constructor
    Maze(const Maze& other) : rows(other.rows), cols(other.cols), startX(other.startX), startY(other.startY), exitX(other.exitX), exitY(other.exitY) {
        // Allocate memory for the new grid
        grid = new bool* [rows];
        for (int i = 0; i < rows; ++i) {
            grid[i] = new bool[cols];
            // Copy the values of the grid from the source maze to the new maze
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = other.grid[i][j];
            }
        }

        // Load the maze texture and set the maze sprite
        mazeTexture.loadFromFile("images/redo.jpg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    int getExitX() const {
        return exitX;
    }

    int getExitY() const {
        return exitY;
    }

    void generateMaze() {
        startY = 5;
        startX = 4;
        int num = 0;
        int target = 15; // Adjust the target based on the desired complexity of the maze
        generateMaze(startY, startX, num, target);

        // Ensure connectivity from the start to the end
        ensureConnectivity();
    }

    void generateMaze(int row, int col, int& numPaths, int targetPaths) {
        grid[row][col] = false;
        numPaths++;

        std::pair<int, int> directions[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::random_shuffle(std::begin(directions), std::end(directions));

        for (const auto& dir : directions) {
            int newRow = row + dir.first * 2;
            int newCol = col + dir.second * 2;

            // Check if the new position is within the boundary
            if (newRow >= 3 && newRow < rows - 2 && newCol >= 3 && newCol < cols - 2 && grid[newRow][newCol]) {
                grid[row + dir.first][col + dir.second] = false;
                generateMaze(newRow, newCol, numPaths, targetPaths);
            }
        }

        if (numPaths < targetPaths) {
            int deadEndRow = row + (std::rand() % 3 - 1) * 2;
            int deadEndCol = col + (std::rand() % 3 - 1) * 2;
            if (deadEndRow >= 3 && deadEndRow < rows - 2 && deadEndCol >= 3 && deadEndCol < cols - 2 && grid[deadEndRow][deadEndCol]) {
                grid[deadEndRow][deadEndCol] = false;
                numPaths++;
            }
        }
    }

    void ensureConnectivity() {
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        dfs(startY, startX, visited);
        if (!visited[exitY][exitX]) {
            // The endpoint is not reachable, so mark it as accessible
            grid[exitY][exitX] = true;
        }
    }


    void dfs(int row, int col, std::vector<std::vector<bool>>& visited) {
        visited[row][col] = true;

        std::pair<int, int> directions[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol] && !grid[newRow][newCol]) {
                dfs(newRow, newCol, visited);
            }
        }
    }


    // Add walls around the perimeter of the maze
    void addBoundary() {
        // Add walls around the perimeter of the maze
        for (int i = 2; i < rows - 2; ++i) {
            grid[i][2] = true;          // Left boundary
            grid[i][cols - 2] = true;   // Right boundary
        }
        for (int j = 2; j < cols - 2; ++j) {
            grid[2][j] = true;          // Top boundary
            grid[rows - 2][j] = true;   // Bottom boundary
        }

        grid[30][2] = false;
        grid[10][cols - 2] = false;
    }

    // Check if a cell is a wall
    bool isWall(int row, int col) const {
        if (col == 3 && row != 2 && row != rows - 2) {
            return false;
        }
        else if (col == cols - 3 && row != 2 && row != rows - 2) {
            return false;
        }
        else if (row >= 2 && row < rows - 1 && col >= 2 && col < cols - 1)
            return grid[row][col];
        else if (col == 2 && row == 30) {
            return false;
        }
        else if (col < 2 && row < 2)
            return !grid[row][col];
        else
            return false;

    }

    // Get the size of the maze
    sf::Vector2i getSize() const {
        return sf::Vector2i(cols, rows);
    }

    // Draw the maze
    void draw(sf::RenderWindow& window) {
        // Draw maze walls
        for (int i = 3; i < rows - 2; ++i) {
            for (int j = 4; j < cols - 3; ++j) {
                if (grid[i][j]) {
                    mazeSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    window.draw(mazeSprite);
                }
            }
        }

        // Draw Boundary
        mazeTexture.loadFromFile("images/download.jpeg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);

        for (int i = 2; i < rows - 1; ++i) {
            for (int j = 2; j < cols - 1; ++j) {
                if (j == 2 || j == cols - 2 || i == 2 || i == rows - 2) {
                    if (!((i == 30 && j == 2) || (i == 10 && j == cols - 2))) {
                        mazeSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                        window.draw(mazeSprite);
                    }
                }
            }
        }

        // Reset the maze texture
        mazeTexture.loadFromFile("images/redo.jpg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);
    }


    // shortest path draw
    void drawShortestPath(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& shortestPath) {
        mazeTexture.loadFromFile("images/download.jpeg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);

        // Draw only the first 10 cells of the shortest path
        int drawCount = std::min(static_cast<int>(shortestPath.size()), 10);
        for (int i = 0; i < drawCount; ++i) {
            int row = shortestPath[i].first;
            int col = shortestPath[i].second;
            mazeSprite.setPosition(col * CELL_SIZE, row * CELL_SIZE);
            window.draw(mazeSprite);
        }

        // Reset the maze texture
        mazeTexture.loadFromFile("images/redo.jpg");
        mazeSprite.setTexture(mazeTexture);
        mazeSprite.setScale(0.03f, 0.04f);
    }

    void printScore(int score, RenderWindow& window) {
        Text text;
        Font font;
        font.loadFromFile("fonts/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(35);
        text.setFillColor(Color::White);
        stringstream ss;
        ss << score;
        text.setString(ss.str().c_str());
        text.setPosition(1000, 350);
        window.draw(text);
    }

    // is won functon
    bool isWon(int playerY, int playerX) {
        if (playerY == exitY && playerX == exitX) {
            return true;
        }
        else
            return false;

    }

};

class Graph;

class Node {
private:
    int row;
    int col;
    bool visited;
    Node* prev;
    std::vector<Node*> neighbors;

public:
    int distance;

    Node(int r = 0, int c = 0) : row(r), col(c), distance(std::numeric_limits<int>::max()), visited(false), prev(nullptr) {}

    void addNeighbor(Node* neighbor) {
        neighbors.push_back(neighbor);
        row = neighbor->row;
        col = neighbor->col;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    int getDistance() const {
        return distance;
    }

    bool isVisited() const {
        return visited;
    }

    Node* getPrev() const {
        return prev;
    }

    const std::vector<Node*>& getNeighbors() const {
        return neighbors;
    }

    void setDistance(int dist) {
        distance = dist;
    }

    void setVisited(bool flag) {
        visited = flag;
    }

    void setPrev(Node* node) {
        prev = node;
    }
};


class Graph {
private:
    std::vector<std::vector<Node>> nodes;

public:
    Graph(int rows, int cols, const Maze& maze) {
        nodes.resize(rows);
        for (int i = 0; i < rows; ++i) {
            nodes[i].resize(cols);
            for (int j = 0; j < cols; ++j) {
                nodes[i][j] = Node(i, j); // Initialize each node with its correct position
            }
        }

        // Connect each cell to its neighbors
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i > 0) {
                    nodes[i][j].addNeighbor(&nodes[i - 1][j]);
                }
                if (j > 0) {
                    nodes[i][j].addNeighbor(&nodes[i][j - 1]);
                }
                if (i < rows - 1) {
                    nodes[i][j].addNeighbor(&nodes[i + 1][j]);
                }
                if (j < cols - 1) {
                    nodes[i][j].addNeighbor(&nodes[i][j + 1]);
                }
            }
        }

        // Debug print to check node connections
        //std::cout << "Graph constructed with " << rows << " rows and " << cols << " columns." << std::endl;
    }

    int** shortestPath(int startRow, int startCol, int endRow, int endCol, Maze maze) {
        constexpr int MAX_PATH_LENGTH = 1000;
        int** shortestPathArray = new int* [MAX_PATH_LENGTH];
        for (int i = 0; i < MAX_PATH_LENGTH; ++i) {
            shortestPathArray[i] = new int[2]; // Each element is a coordinate pair (row, col)
        }
        Graph g(maze.getRows(), maze.getCols(), maze);

        if (startRow < 0 || startRow >= g.nodes.size() || startCol < 0 || startCol >= nodes[0].size() ||
            endRow < 0 || endRow >= nodes.size() || endCol < 0 || endCol >= nodes[0].size()) {
            return shortestPathArray; // Invalid start or end coordinates
        }

        auto compare = [](const Node* a, const Node* b) { return a->distance > b->distance; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pq(compare);

        Node* startNode = &nodes[startRow][startCol - 1];
        startNode->setDistance(0);
        pq.push(startNode);

        int index = 0;

        while (!pq.empty() && index < 10) {
            Node* current = pq.top();
            pq.pop();

            if (current->getRow() == endRow && current->getCol() == endCol) {
                // Reconstruct the shortest path into the array
                while (current != nullptr) {
                    shortestPathArray[index][0] = current->getRow();
                    shortestPathArray[index][1] = current->getCol();
                    current = current->getPrev();
                    index++;
                }
                shortestPathArray[index] = nullptr;

                return shortestPathArray;
            }

            if (!current->isVisited()) {
                current->setVisited(true);
                for (Node* neighbor : current->getNeighbors()) {
                    // Check if the neighbor is within maze bounds, not a wall, and not visited
                    if (neighbor->getRow() >= 3 &&
                        neighbor->getCol() >= 3 &&
                        !maze.isWall(neighbor->getRow(), neighbor->getCol()) &&
                        !neighbor->isVisited()) {
                        int distanceToNeighbor = current->getDistance() + 1; // Assuming each edge has weight 1
                        if (distanceToNeighbor < neighbor->getDistance()) {
                            neighbor->setDistance(distanceToNeighbor);
                            neighbor->setPrev(current);
                            pq.push(neighbor);
                        }
                    }
                }
            }
        }

        shortestPathArray[index] = nullptr;

        // If no path found, return the partially filled array
        return shortestPathArray;
    }

    void drawShortestPath(sf::RenderWindow& window, int** Path, int playerRow, int playerCol) {
        if (!Path)
            return;

        // Load the maze texture
        sf::Texture mazeTexture;
        mazeTexture.loadFromFile("images/download.jpeg");

        // Create a sprite for the maze texture
        sf::Sprite mazeSprite(mazeTexture);
        mazeSprite.setScale(0.1f, 0.1f);

        // Find the length of the path
        int len = 0;
        while (Path[len] != nullptr) {
            len++;
        }

        // Calculate the starting index for drawing
        int startIdx = len - 1;
        while (startIdx >= 0 && (Path[startIdx][0] != playerRow || Path[startIdx][1] != playerCol)) {
            startIdx--;
        }

        // Draw the first ten cells of the path from the player's position
        for (int i = startIdx; i >= 0 && i > startIdx - 10; --i) {
            int row = Path[i][0];
            int col = Path[i][1];

            // Calculate the position of the cell in the window
            float posX = col * 20;
            float posY = row * 20;

            // Set the position and draw the path cell
            mazeSprite.setPosition(posX, posY);
            window.draw(mazeSprite);
        }
    }


};



#endif


