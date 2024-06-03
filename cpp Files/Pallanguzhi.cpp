#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
#include "demo.cpp"

int point = 0;

class GameBoard
{
public:
    std::vector<int> cups;

    GameBoard(int seedsPerCup) : cups(14, seedsPerCup) {}

    void displayBoard() const
    {
        for (int i = 0; i < 7; ++i)
        {
            std::cout << cups[6 - i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < 7; ++i)
        {
            std::cout << cups[7 + i] << " ";
        }
        std::cout << "\n--------------------" << std::endl;
    }

    GameBoard(const GameBoard &other) : cups(other.cups) {}
};

class Player
{
public:
    std::string name;

    Player(std::string name) : name(name) {}

    virtual int chooseCup(const GameBoard &board)
    {
        int cup;

        std::cout << RED << name << RESET << ", choose a cup (0-6 for your side): ";
        std::cin >> cup;
        return cup;
    }
};

class AIPlayer : public Player
{
public:
    AIPlayer(std::string name) : Player(name) {}

    int chooseCup(const GameBoard &board) override
    {
        int bestMove = -1;
        int maxScore = INT_MIN;

        for (int cup = 0; cup < 7; ++cup)
        {
            if (board.cups[cup + 7] == 0)
                continue; // Skip empty cups
            int score = minimax(board, cup + 7, 3, INT_MIN, INT_MAX, true);
            if (score > maxScore)
            {
                maxScore = score;
                bestMove = cup;
            }
        }
        return bestMove;
    }

private:
    int minimax(GameBoard board, int startCup, int depth, int alpha, int beta, bool isMaximizingPlayer)
    {
        if (depth == 0 || isTerminalNode(board))
        {
            return evaluateBoard(board);
        }

        if (isMaximizingPlayer)
        {
            int maxScore = INT_MIN;
            for (int cup = 0; cup < 7; ++cup)
            {
                int actualCup = cup + 7;
                if (board.cups[actualCup] == 0)
                    continue;
                GameBoard newBoard = board;
                sowSeeds(newBoard, actualCup);
                int score = minimax(newBoard, actualCup, depth - 1, alpha, beta, false);
                maxScore = std::max(maxScore, score);
                alpha = std::max(alpha, score);
                if (beta <= alpha)
                    break; // Beta cutoff
            }
            return maxScore;
        }
        else
        {
            int minScore = INT_MAX;
            for (int cup = 0; cup < 7; ++cup)
            {
                int actualCup = cup;
                if (board.cups[actualCup] == 0)
                    continue;
                GameBoard newBoard = board;
                sowSeeds(newBoard, actualCup);
                int score = minimax(newBoard, actualCup, depth - 1, alpha, beta, true);
                minScore = std::min(minScore, score);
                beta = std::min(beta, score);
                if (beta <= alpha)
                    break; // Alpha cutoff
            }
            return minScore;
        }
    }

    bool isTerminalNode(const GameBoard &board)
    {
        // Check if any player's side is empty
        for (int i = 0; i < 7; ++i)
        {
            if (board.cups[i] != 0)
                return false;
            if (board.cups[i + 7] != 0)
                return false;
        }
        return true;
    }

    void sowSeeds(GameBoard &board, int startCup)
    {
        int seeds = board.cups[startCup];
        board.cups[startCup] = 0;
        int cup = startCup;
        while (seeds > 0)
        {
            cup = (cup + 1) % 14;
            if (cup != startCup)
            {
                board.cups[cup]++;
                seeds--;
            }
        }
    }

    int evaluateBoard(const GameBoard &board)
    {
        int aiSeeds = std::accumulate(board.cups.begin() + 7, board.cups.end(), 0);
        int playerSeeds = std::accumulate(board.cups.begin(), board.cups.begin() + 7, 0);
        return aiSeeds - playerSeeds;
    }
};

class Game
{
private:
    GameBoard board;
    Player *player1;
    Player *player2;
    bool player1Turn;

    void sowSeeds(int startCup)
    {
        while (board.cups[startCup] != 0)
        {
            // board.displayBoard();
            int seeds = board.cups[startCup];
            board.cups[startCup] = 0;
            int cup = startCup;
            while (seeds > 0)
            {
                cup = (cup + 1) % 14;
                if (cup != startCup)
                {
                    board.cups[cup]++;
                    seeds--;
                }
            }
            startCup = (cup + 1) % 14;
        }

        startCup = (startCup + 1) % 14;
        point = board.cups[startCup];
        board.cups[startCup] = 0;

        std::cout << YELLOW << "\nPOINTS : " << point << RESET << "\n";
    }

public:
    Game(int seedsPerCup, Player *player1, Player *player2)
        : board(seedsPerCup), player1(player1), player2(player2), player1Turn(true) {}

    void playGame()
    {
        while (true)
        {
            board.displayBoard();

            int cup = player1Turn ? player1->chooseCup(board) : player2->chooseCup(board);
            cup = player1Turn ? cup : cup + 7;
            sowSeeds(cup);
            if (checkWin())
            {
                determineWinner();
                break;
            }
            player1Turn = !player1Turn;
        }
    }

private:
    bool checkWin()
    {
        int player1Seeds = std::accumulate(board.cups.begin(), board.cups.begin() + 7, 0);
        int player2Seeds = std::accumulate(board.cups.begin() + 7, board.cups.end(), 0);
        return player1Seeds == 0 || player2Seeds == 0;
    }

    void determineWinner()
    {
        int player1Seeds = std::accumulate(board.cups.begin(), board.cups.begin() + 7, 0);
        int player2Seeds = std::accumulate(board.cups.begin() + 7, board.cups.end(), 0);

        if (player1Seeds > player2Seeds)
        {
            std::cout << BLUE << player1->name << " wins!" << RESET << std::endl;
        }
        else if (player2Seeds > player1Seeds)
        {
            std::cout << player2->name << " wins!" << std::endl;
        }
        else
        {
            std::cout << "It's a tie!" << std::endl;
        }
    }
};

int main()
{
    std ::cout << GREEN << "Pallanguzhi " << RESET << std ::endl;
    Player humanPlayer("Player 1");
    AIPlayer aiPlayer("AI Opponent");
    Game game(5, &humanPlayer, &aiPlayer);
    game.playGame();
    return 0;
}
