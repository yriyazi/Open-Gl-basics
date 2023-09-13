#include <iostream>
#include <vector>

// Function to solve 2D heat transfer equation using finite difference method
void solveHeatTransferEquation2D(std::vector<std::vector<double>>& grid, double alpha, double dt, int numIterations)
{
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<double>> newGrid(rows, std::vector<double>(cols));

    for (int iteration = 0; iteration < numIterations; ++iteration)
    {
        for (int i = 1; i < rows - 1; ++i)
        {
            for (int j = 1; j < cols - 1; ++j)
            {
                grid[i][j] = grid[i][j] + alpha*2*(grid[i - 1][j] + grid[i + 1][j] + (grid[i][j - 1] + grid[i][j + 1])- 4*grid[i][j]) / (dt);
            }
        }         
    }
    
}

int main()
{
    // Define parameters
    double alpha = 0.002;     // Thermal diffusivity
    double dt = 0.1;       // Time step size
    int numIterations = 10000; // Number of iterations

    // Define grid size
    int rows = 10;
    int cols = 10;

    // Initialize the grid with initial values
    std::vector<std::vector<double>> grid(rows, std::vector<double>(cols, 0.0));

    // Set boundary conditions
    for (int i = 0; i < rows; ++i)
    {
        grid[i][0] = 100.0;  // Left boundary
        grid[i][cols - 1] = 100.0;  // Right boundary
    }

    for (int j = 0; j < cols; ++j)
    {
        grid[0][j]          = 10.0;    // Top boundary
        grid[rows - 1][j]   = -10.0;    // Bottom boundary
    }

    // Solve the heat transfer equation
    solveHeatTransferEquation2D(grid, alpha, dt, numIterations);




    // Print the final grid
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
