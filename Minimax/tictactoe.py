import math

EMPTY = ' '

# Player representation
PLAYER_X = 'X'  # Program/PC/AI
PLAYER_O = 'O'  # Human

# To check for winner
def winner(board):
    # For rows & columns
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != EMPTY:
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != EMPTY:
            return board[0][i]
    
    # For diagonals
    if board[0][0] == board[1][1] == board[2][2] != EMPTY:
        return board[0][0]
    
    if board[0][2] == board[1][1] == board[2][0] != EMPTY:
        return board[0][2]
    
    return None

# To check if the board is full
def isDraw(board):
    for row in board:
        for cell in row:
            if cell == EMPTY:
                return False
    return True

# To check if the game is over
def gameOver(board):
    return winner(board) != None or isDraw(board)

# To evaluate the game
def evaluate(board):
    if winner(board) == PLAYER_X:
        return 1
    elif winner(board) == PLAYER_O:
        return -1
    return 0

# To get all available moves on the board
def availableMoves(board):
    moves = []
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                moves.append((i, j))
    return moves

# To make a move on the board
def makeMove(board, move, player):
    board[move[0]][move[1]] = player

# To undo a move on the board
def undoMove(board, move):
    board[move[0]][move[1]] = EMPTY
    
# Printing the board
def printBoard(board):
    count = 0
    for row in board:
        print(" | ".join(row))
        count+=1
        if count!=3:
            print("----------")

# Main Minimax algorithm ab aaya 
def minimax(board, depth, is_maximizing_player):
    if gameOver(board):
        return evaluate(board)
    
    if is_maximizing_player:
        bestScore = -math.inf
        for move in availableMoves(board):
            makeMove(board, move, PLAYER_X)
            eval = minimax(board, depth + 1, False)
            undoMove(board, move)
            bestScore = max(bestScore, eval)
        return bestScore
    else:
        leastScore = math.inf
        for move in availableMoves(board):
            makeMove(board, move, PLAYER_O)
            eval = minimax(board, depth + 1, True)
            undoMove(board, move)
            leastScore = min(leastScore, eval)
        return leastScore

# To find the best move for program
def findBestMove(board):
    bestValue = -math.inf
    bestMove = None
    
    for move in availableMoves(board):
        makeMove(board, move, PLAYER_X)
        moveValue = minimax(board, 0, False)
        undoMove(board, move)
        
        if moveValue > bestValue:
            bestValue = moveValue
            bestMove = move
    
    return bestMove

# Main function to play the game
def playGame():
    board = []
    for i in range(3):
        board.append([EMPTY] * 3)

    currentPlayer = PLAYER_O
    
    while not gameOver(board):     
        printBoard(board)
        
        if currentPlayer == PLAYER_X:
            print("Program's turn (Player X):")
            move = findBestMove(board)
            makeMove(board, move, PLAYER_X)
            currentPlayer = PLAYER_O
        else:
            print("Your turn (Player O):")
            validMove = False
            while not validMove:
                try:
                    row = int(input("Enter row (0-2): "))
                    col = int(input("Enter column (0-2): "))
                    if board[row][col] == EMPTY:
                        makeMove(board, (row, col), PLAYER_O)
                        validMove = True
                    else:
                        print("Cell already taken, try again.")
                except (ValueError, IndexError):
                    print("Invalid move, try again.")
            currentPlayer = PLAYER_X
    
    printBoard(board)
    
    if winner(board) == PLAYER_X:
        print("You lost, better luck next time!")
    elif winner(board) == PLAYER_O:
        print("You won!")
    else:
        print("It's a draw :)")

# Entry Point into Algorithm
playGame()