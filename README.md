# DS-A-A3-i230033

Player BST class:

h=height of tree, n is no of nodes and k is the gameCount of a player

1:insert() O(h)
2:print BST() O(n)
3:searchPLayer() O(h)
4:deletePLayer() O(h)
5:getHeight() O(n)
6:getNumberOfLayer() O(n)
7:getLayerNumber() O(h)
8:showPathToPlaye() O(h)
9:hasPLayed() O(h + logK)
10:updatePLayer() O(1)
11:printInordeR() O(n)
12:search() O(h)
13:findMin() O(h)
14:printPathToNode()  O(n) and find node() O(n) 


Game BST class:

n=no of nodes and h is height of the tree

1:insert() - O(h)
2:printGameBST() - O(n)
3:searchGame() - O(h)
4:deleteGame() - O(h)
5:getHeight() - O(n)
6:getNumberOfLayers() - O(n)
7:getLayerNumber() - O(h)
8:insertRec() - O(h)
9:printInOrder() - O(n)
10:search() - O(h)
11:deleteGame() - O(h)
12:findMin() - O(h)



Features
1. Load Data from CSV Files
    Load Games: Reads game data from Games.txt into a gameBST.
    Load Players: Reads player data from Players.txt into a playerBST.
2. Search Functionality
    Search Game: Allows the user to search for a game by its ID and display its details.
    Search Player Detail: Searches for a player by their ID and shows detailed information, including games they have played.
3. Delete Functionality
    Delete Game: Removes a game from the game BST by its ID.
    Delete Player: Deletes a player from the player BST by their ID.
4. Display Information
    Print Player BST: Displays the player BST in an in-order traversal, showing players in sorted order.
    Print Game BST: Displays the game BST in an in-order traversal, showing games in sorted order.
    Display Total Layers: Outputs the total number of layers (height) in both game and player BSTs.
    Display Specific Layer: Shows the layer number for a specific game or player by ID.
5. Edit Player Information
    Edit Player Details: Allows modification of player information, including their ID, name, phone number, email, password, and the games they have played. Changes in player ID trigger repositioning in the BST to maintain the structure.
6. Show Path
    Path to Player: Displays the path from the root to a specified player node in the BST.
7. Check Game Participation
        Has Played: Verifies if a specific player has played a particular game.
8. Top N Players
    Show Top N Players: Lists the top N players based on custom criteria defined in the playerBST class.
9. Save Data to CSV
    Save Player Data: Exports player data from the BST to a CSV file, maintaining a pre-order traversal format.
10. Random Filtering
    Random Data Loading: While reading from the CSV files, a random number is used to filter out some entries, simulating selective data entry.




How the Program Works

Initialization
    The program defines two BST classes: gameBST for managing games and playerBST for managing players. Each BST holds nodes (gameNode and playerNode) containing relevant data and pointers to left and right child nodes.
File Reading and Data Loading
    The program reads data from CSV files (Games.txt and Players.txt) line by line using the ifstream class. The data is parsed using istringstream and stored in respective BSTs.
    The loadGamesFromFile() and loadPlayersFromFile() functions include a randomness factor, using rand() to selectively load data based on a threshold.
User Interaction
    A Menu() function provides a user-friendly command-line interface with options to perform various operations such as loading data, searching, deleting, editing, and displaying data.
    Users interact with the program through inputs prompted by cout and captured by cin.
Editing and Deleting Nodes
    The editPlayer() function allows users to modify player details. If a player ID is changed, the node is repositioned to maintain BST properties.
    The deletePlayer() and deleteGame() functions remove specified nodes from their respective BSTs, ensuring the tree's structure is preserved.
Exporting Data
    The MakeCSV() function, alongside saveBSTToCSV(), writes the BST data to a CSV file in pre-order format, facilitating data export and backup.
    Checking Paths and Participation
    Functions like showPathToPlayer() and hasPlayed() provide insights into a player's history and game involvement.
Comprehensive Layer Information
    The program calculates and displays the number of layers in the BSTs using getNumberOfLayers() and finds the layer of a specific node using getLayerNumber().
Top Players
    The topNPlayers() function displays the top N players based on predefined criteria within the BST class.
User Instructions
    Compile and Run: Use a C++ compiler to build and run the program.
    Navigate the Menu: Choose options from the menu to interact with the database.
    Load Data: Load games and players from CSV files to start using the program.
    Perform Operations: Search, delete, edit, or view details as needed.
    Export Data: Save the current state of the player database to a CSV file for backup or further analysis.