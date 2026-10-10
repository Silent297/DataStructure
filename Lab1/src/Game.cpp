#include "../include/Game.h"

Game::Game() = default;

void Game::initGame() {
    gameBoard.reset();
    score = 0;
    moveCount = 0;
    historyGameBoards = std::stack<GameBoard>();
    historyScores.clear();
    startTime = std::chrono::steady_clock::now();
    historyGameBoards.push(gameBoard);  // The initial state is the base of the history.
    historyScores.push_back(score);
}

void Game::updateGame(Direction direction) {
    // Safe placeholder use until the TODOs below are completed.
    // Perform the move and determine whether the board actually changed.
    // DONE 1
    Board bfboard = gameBoard.getBoard();
    int getscore = gameBoard.move(direction);
    
    if (bfboard != gameBoard.getBoard()){
        score += getscore;
        moveCount ++;
        historyGameBoards.push(gameBoard);
        historyScores.push_back(score);
    }
    // For a valid move, update the score and move count.
    // DONE 2
    // Save the resulting board and score. Invalid moves must not be recorded.
    // DONE 3

}

void Game::undoLastMove() {
    if (historyGameBoards.size() > 1) {
        // Remove the current state and restore the previous board.
        // DONE 1
        historyGameBoards.pop();
        gameBoard = historyGameBoards.top();
    
        // Restore the matching score and decrease the valid-move count.
        // DONE 2
        historyScores.pop_back();
        score = historyScores.back();
        moveCount --;
    }
    // With only the initial state in history, undo is intentionally a no-op.
}

bool Game::hasWon() const {
    return gameBoard.hasWinningTile();
}

bool Game::hasLost() const {
    return gameBoard.isGameOver();
}

double Game::getElapsedTime() const {
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

int Game::getScore() const {
    return score;
}

int Game::getMoveCount() const {
    return moveCount;
}

const GameBoard& Game::getGameBoard() const {
    return gameBoard;
}
