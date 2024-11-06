#include <iostream>
#include <fstream>
#include<sstream>
#include <cstdlib>    // for rand() and srand()
#include <ctime>      // for time()
using namespace std;

class games_played_node 
{
public:
    string gameId;
    float hoursPlayed;
    int achievements;
    games_played_node* left;
    games_played_node* right;

    games_played_node() : left(nullptr), right(nullptr), achievements(0), hoursPlayed(0.0f) {}

    games_played_node(string id, float hours, int ach)
        : gameId(id), hoursPlayed(hours), achievements(ach), left(nullptr), right(nullptr) {}
};

class playerNode {
public:
    string playerId;
    string name;
    string phoneNo;
    string email;
    string password;
    games_played_node* gamesPlayed; 
    int gameCount;                  
    playerNode* left;
    playerNode* right;

    playerNode(string id, string n, string ph, string em, string pw, int gCount)
        : playerId(id), name(n), phoneNo(ph), email(em), password(pw), gameCount(gCount), left(nullptr), right(nullptr) {
        gamesPlayed = new games_played_node[gameCount]; 
    }

    ~playerNode() {
        delete[] gamesPlayed;
    }
};

class gameNode
{
public:
    string gameId;
    string name;
    string developer;
    string publisher;
    float fileSize;
    int downloads;
    gameNode* left;
    gameNode* right;

    gameNode(string id, string n, string dev, string pub, float size, int dl)
        : gameId(id), name(n), developer(dev), publisher(pub), fileSize(size), downloads(dl), left(nullptr), right(nullptr) {}
};



class playerBST
{
public:
    playerNode* root;
    playerNode* topPlayers[10] = {nullptr}; // Array to hold top 10 players

    playerBST() : root(nullptr) {}

void setSize(int s)
{

}
void insert(string playerId, string name, string phoneNo, string email, string password, games_played_node* gamesPlayed, int gameCount) {
        root = insertRec(root, playerId, name, phoneNo, email, password, gamesPlayed, gameCount);
    }
void printPlayerBST() 
    {
        int count=0;
        printInOrder(root,count);
    }
playerNode* searchPlayer(const string& playerId) 
    {
        return search(root, playerId);
    }
void deletePlayer(const string& playerId) 
    {
        root = deletePlayer(root, playerId);
    }
int getHeight(playerNode* node) 
    {
    if (node == nullptr) return 0;
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + max(leftHeight, rightHeight);
    }

int getNumberOfLayers() 
    {
    return getHeight(root);
    }
int getLayerNumber(playerNode* node, const string& playerId, int currentLayer = 1) 
    {
    if (node == nullptr) {
        return -1; // Not found
    }

    if (node->playerId == playerId) {
        return currentLayer; // Node found, return the current layer
    }

    // Search in the left subtree
    int leftLayer = getLayerNumber(node->left, playerId, currentLayer + 1);
    if (leftLayer != -1) return leftLayer; // If found in left subtree, return layer

    // Search in the right subtree
    return getLayerNumber(node->right, playerId, currentLayer + 1);
    }
    void showPathToPlayer(const string& playerId) 
    {
        bool found = false;

        // First traversal: Check if the node exists in the tree
        if (findNode(root, playerId)) {
            found = true;
        }

        if (found) {
            cout << "Path to player with ID '" << playerId << "': ";
            printPathToNode(root, playerId);
            cout << " -> Found!" << endl;
        } else {
            cout << "Player with ID '" << playerId << "' not found in the BST." << endl;
        }
    }
    bool hasPLayed(const string& playerId, const string& gameId)
    {
        playerNode* player = search(root, playerId);
    
        if (player == nullptr) 
        {
            cout << "Player not found." << endl;
            return false;
        }

         int left = 0, right = player->gameCount - 1;

    while (left <= right) 
        {
        int mid = left + (right - left) / 2;
        if (player->gamesPlayed[mid].gameId == gameId) {
            return true; // Game found
        } else if (player->gamesPlayed[mid].gameId < gameId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        }
    
    return false; // Game not found
    }




private:
    playerNode* insertRec(playerNode* node, string playerId, string name, string phoneNo, string email, string password, games_played_node* gamesPlayed, int gameCount) 
    {
        if (node == nullptr) {
            playerNode* newNode = new playerNode(playerId, name, phoneNo, email, password, gameCount);
            for (int i = 0; i < gameCount; i++) 
            {
                newNode->gamesPlayed[i] = gamesPlayed[i];
            }
            updateTopPlayers(newNode); // this updates the array everytime the node is added to store top 10 max game played players
            return newNode;
        }

        if (playerId < node->playerId) {
            node->left = insertRec(node->left, playerId, name, phoneNo, email, password, gamesPlayed, gameCount);
        } else if (playerId > node->playerId) {
            node->right = insertRec(node->right, playerId, name, phoneNo, email, password, gamesPlayed, gameCount);
        } else {
            // Duplicate playerId found
            cout << "Error: Player ID '" << playerId << "' already exists." << endl;
            return node; // Do not insert, return existing node
        }

        return node;
    }
    void updateTopPlayers(playerNode* newNode) 
    {
    int newCount = newNode->gameCount;

    // Find position in the array for the new node
    for (int i = 0; i < 10; i++) {
        if (topPlayers[i] == nullptr || newCount > topPlayers[i]->gameCount) {
            // Shift elements to the right to make space
            for (int j = 9; j > i; j--) {
                topPlayers[j] = topPlayers[j - 1];
            }
            // Insert the new node at the found position
            topPlayers[i] = newNode;
            break;
        }
    }
    }
    void printInOrder(playerNode* node, int& count) 
    {
    if (node == nullptr || count >= 10) return;

    // Traverse left subtree
    if (count < 10) printInOrder(node->left, count);

    // Print current node if within the limit
    if (count < 10) {
        cout << "Player ID: " << node->playerId << ", Name: " << node->name
             << ", Phone: " << node->phoneNo << ", Email: " << node->email
             << ", Password: " << node->password << endl;

        cout << "Games Played:" << endl;
        for (int i = 0; i < node->gameCount; i++) {
            cout << "    Game ID: " << node->gamesPlayed[i].gameId << ", Hours Played: " << node->gamesPlayed[i].hoursPlayed
                 << ", Achievements: " << node->gamesPlayed[i].achievements << endl;
        }
        count++;  // Increment count after printing each player
    }

    // Traverse right subtree
    if (count < 10) printInOrder(node->right, count);
    }
    playerNode* search(playerNode* node, const string& playerId) 
    {
        if (node == nullptr || node->playerId == playerId)
            return node;

        if (playerId < node->playerId)
            return search(node->left, playerId);

        return search(node->right, playerId);
    }
    playerNode* deletePlayer(playerNode* node, const string& playerId) 
    {
    if (node == nullptr) return node;

    // Search for the node to delete
    if (playerId < node->playerId) {
        node->left = deletePlayer(node->left, playerId);
    } else if (playerId > node->playerId) {
        node->right = deletePlayer(node->right, playerId);
    } else {
        // Node found
        if (node->left == nullptr) {
            // Case 1 & 2: Node has no left child or no children
            playerNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            // Case 2: Node has no right child
            playerNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // Case 3: Node has two children
            playerNode* temp = findMin(node->right);
            node->playerId = temp->playerId;
            node->name = temp->name;
            node->phoneNo = temp->phoneNo;
            node->email = temp->email;
            node->password = temp->password;
            node->gameCount = temp->gameCount;

            // Free existing gamesPlayed array
            delete[] node->gamesPlayed;
            
            // Copy the gamesPlayed array from the successor
            node->gamesPlayed = new games_played_node[temp->gameCount];
            for (int i = 0; i < temp->gameCount; ++i) {
                node->gamesPlayed[i] = temp->gamesPlayed[i];
            }

            node->right = deletePlayer(node->right, temp->playerId);
        }
    }
    return node;
    }

    playerNode* findMin(playerNode* node) 
    {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
    }
        bool findNode(playerNode* node, const string& playerId) {
        if (node == nullptr) return false;
        if (node->playerId == playerId) return true;

        // Search in left and right subtrees
        return findNode(node->left, playerId) || findNode(node->right, playerId);
    }

    // Second traversal to print path to the node
    bool printPathToNode(playerNode* node, const string& playerId) {
        if (node == nullptr) return false;

        // Print the current node's ID
        cout << node->playerId;
        if (node->playerId == playerId) return true;

        cout << " -> ";  // Separator for path

        // Traverse left and right subtrees
        if (printPathToNode(node->left, playerId) || printPathToNode(node->right, playerId)) {
            return true;
        }

        // Backtrack if not found (erase last path step)
        return false;
    }

};

class gameBST
{
public:
    gameNode* root;

    gameBST() : root(nullptr) {}

    void insert(string gameId, string name, string developer, string publisher, float fileSize, int downloads)
    {
        root = insertRec(root, gameId, name, developer, publisher, fileSize, downloads);
    }

    void printGameBST()
    {
        int count=0;
        printInOrder(root,count);
    }
    gameNode* searchGame(const string& gameId) 
    {
        return search(root, gameId);
    }
    void deleteGame(const string& gameId)
    {
    root = deleteGame(root, gameId);
    }
    int getHeight(gameNode* node) 
    {
    if (node == nullptr) return 0; // Base case: Empty tree has height 0

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + max(leftHeight, rightHeight); // Include current level
    }

    int getNumberOfLayers() 
    {
    return getHeight(root);
    }
    int getLayerNumber(gameNode* node, const string& gameId, int currentLayer = 1) 
    {
    if (node == nullptr) {
        return -1; // Not found
    }

    if (node->gameId == gameId) {
        return currentLayer; // Node found, return the current layer
    }

    // Search in the left subtree
    int leftLayer = getLayerNumber(node->left, gameId, currentLayer + 1);
    if (leftLayer != -1) return leftLayer; // If found in left subtree, return layer

    // Search in the right subtree
    return getLayerNumber(node->right, gameId, currentLayer + 1);
    }
private:
     gameNode* insertRec(gameNode* node, string gameId, string name, string developer, string publisher, float fileSize, int downloads) {
        if (node == nullptr)
            return new gameNode(gameId, name, developer, publisher, fileSize, downloads);

        if (gameId < node->gameId) {
            node->left = insertRec(node->left, gameId, name, developer, publisher, fileSize, downloads);
        } 
        else if (gameId > node->gameId) {
            node->right = insertRec(node->right, gameId, name, developer, publisher, fileSize, downloads);
        } 
        else {
            cout << "Error: Game ID '" << gameId << "' already exists." << endl;
            return node; // Do not insert, return existing node
        }

        return node;
    }

    void printInOrder(gameNode* node, int& count) {
    if (node == nullptr || count >= 10) return;

    // Traverse left subtree
    if (count < 10) printInOrder(node->left, count);

    // Print current node if within the limit
    if (count < 10) {
        cout << "Game ID: " << node->gameId << ", Name: " << node->name
             << ", Developer: " << node->developer << ", Publisher: " << node->publisher
             << ", File Size: " << node->fileSize << " MB, Downloads: " << node->downloads << endl;
        count++;  // Increment count after printing each game
    }

    // Traverse right subtree
    if (count < 10) printInOrder(node->right, count);
}
gameNode* search(gameNode* node, const string& gameId) 
 {
        if (node == nullptr || node->gameId == gameId)
            return node;

        if (gameId < node->gameId)
            return search(node->left, gameId);

        return search(node->right, gameId);
}
gameNode* deleteGame(gameNode* node, const string& gameId) 
{
    if (node == nullptr) return node;

    // Search for the node to delete
    if (gameId < node->gameId) 
    {
        node->left = deleteGame(node->left, gameId);
    }
     else if (gameId > node->gameId)
    {
        node->right = deleteGame(node->right, gameId);
    }
    else
    {
        // Node found
        if (node->left == nullptr) 
        {
            // Case 1 & 2: Node has no left child or no children
            gameNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) 
        {
            // Case 2: Node has no right child
            gameNode* temp = node->left;
            delete node;
            return temp;
        } 
        else 
        {
            // Case 3: Node has two children
            gameNode* temp = findMin(node->right);
            node->gameId = temp->gameId;
            node->name = temp->name;
            node->developer = temp->developer;
            node->publisher = temp->publisher;
            node->fileSize = temp->fileSize;
            node->downloads = temp->downloads;

            node->right = deleteGame(node->right, temp->gameId);
        }
    }
    return node;
}

gameNode* findMin(gameNode* node) 
{
    while (node && node->left != nullptr) 
    {
        node = node->left;
    }
    return node;
}



};



void loadGamesFromFile(const string& filePath, gameBST& games) 
{
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    srand(time(0));

    while (getline(file, line)) 
    {
        int randomNum = rand() % 1000 + 1;
        //cout << "Random Number: " << randomNum << " (for line: " << line << ")" << endl;

        if (randomNum <= 430) {
            //cout << "Skipping line due to random number <= 430" << endl;
            continue;
        }

        istringstream ss(line);
        string gameId, name, developer, publisher, fileSizeStr, downloadsStr;
        
        if (getline(ss, gameId, ',') &&
            getline(ss, name, ',') &&
            getline(ss, developer, ',') &&
            getline(ss, publisher, ',') &&
            getline(ss, fileSizeStr, ',') &&
            getline(ss, downloadsStr, ',')) {
            
            float fileSize = stof(fileSizeStr);
            int downloads = stoi(downloadsStr);
            games.insert(gameId, name, developer, publisher, fileSize, downloads);
            //cout << "Inserted: " << gameId << ", " << name << endl;
        } else {
            cout << "Error: Line format is incorrect!" << endl;
        }
    }

    file.close();
}
void loadPlayersFromFile(const string& filePath, playerBST& players) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    srand(time(0));

    while (getline(file, line)) {
        int randomNum = rand() % 1000 + 1;
        //cout << "Random Number: " << randomNum << " (for line: " << line << ")" << endl;

        if (randomNum <= 430) {
           // cout << "Skipping line due to random number <= 430" << endl;
            continue;
        }

        istringstream ss(line);
        string playerId, name, phoneNo, email, password;
        if (getline(ss, playerId, ',') &&
            getline(ss, name, ',') &&
            getline(ss, phoneNo, ',') &&
            getline(ss, email, ',') &&
            getline(ss, password, ',')) {

            int gameCount = 0;
            games_played_node* gamesPlayed = new games_played_node[50];  // Assume max 50 games per player temporarily
            string gameId, hoursPlayedStr, achievementsStr;

            // Extract game data in sets of three values
            while (getline(ss, gameId, ',') &&
                   getline(ss, hoursPlayedStr, ',') &&
                   getline(ss, achievementsStr, ',')) {
                if (gameCount >= 50) break;  // Ensure we don't exceed max temporary array size
                gamesPlayed[gameCount++] = games_played_node(gameId, stof(hoursPlayedStr), stoi(achievementsStr));
            }

            players.insert(playerId, name, phoneNo, email, password, gamesPlayed, gameCount);
            //cout << "Inserted Player: " << playerId << ", " << name << endl;

            delete[] gamesPlayed;  // Clean up temporary array
        } else {
            cout << "Error: Line format is incorrect!" << endl;
        }
    }

    file.close();
}

class Database
{
private:
    playerBST players;
    gameBST games;
public:
void loadPlayersFromCSV()
{
 
    loadPlayersFromFile("Players.txt", players);
    cout << "Players loaded based on random selection criteria." << endl;
    printPlayer();
    
}
void loadGamesFromCSV()
{
    loadGamesFromFile("Games.txt", games);
    cout << "Games loaded based on random selection criteria." << endl;
    PrintGame();
}
void printPlayer()
{
    cout << "\nPrinting the Player BST in sorted order:" << endl;
    players.printPlayerBST();    
}
void PrintGame()
{
    cout << "\nPrinting the Game BST in sorted order:" << endl;
    games.printGameBST();
}


void deletePlayer()
{
    string playerIdToDelete;
    cout << "\nEnter Player ID to delete: ";
    cin >> playerIdToDelete;
    players.deletePlayer(playerIdToDelete);
}
void deleteGame()
{
    string gameIdToDelete;
    cout << "\nEnter Game ID to delete: ";
    cin >> gameIdToDelete;
    games.deleteGame(gameIdToDelete);
    cout<<"\n you can verify the game is deleted from here\n";
    games.printGameBST();
}
void searchPlayerDetail()
{
    string searchPlayerId;
    cout << "\nEnter Player ID to search: ";
    cin >> searchPlayerId;
    playerNode* player = players.searchPlayer(searchPlayerId);
    if (player) {
        cout << "Player found!" << endl;
        cout << "Player ID: " << player->playerId << ", Name: " << player->name 
             << ", Phone: " << player->phoneNo << ", Email: " << player->email 
             << ", Password: " << player->password << endl;

        // Print the games played by this player
        cout << "Games Played:" << endl;
        for (int i = 0; i < player->gameCount; i++) {
            cout << "    Game ID: " << player->gamesPlayed[i].gameId 
                 << ", Hours Played: " << player->gamesPlayed[i].hoursPlayed 
                 << ", Achievements: " << player->gamesPlayed[i].achievements << endl;
        }
    } else {
        cout << "Player with ID '" << searchPlayerId << "' not found." << endl;
    }
}
void searchGame()
{
    string searchGameId;
    cout << "\nEnter Game ID to search: ";
    cin >> searchGameId;

    gameNode* game = games.searchGame(searchGameId);
    if (game) {
        cout << "Game found!" << endl;
        cout << "Game ID: " << game->gameId << ", Name: " << game->name 
            << ", Developer: " << game->developer << ", Publisher: " << game->publisher 
            << ", File Size: " << game->fileSize << " MB, Downloads: " << game->downloads << endl;
    } else {
        cout << "Game with ID '" << searchGameId << "' not found." << endl;
    }
}
void GamesLayer()
{
    string gameL;
    cout<<"\n Enter game's id to check for the layer: ";
    cin>>gameL;
    int gameLayer = games.getLayerNumber(games.root, gameL);
    if (gameLayer != -1) 
    {
        cout << "Game with ID " << gameL << " is at layer " << gameLayer << "." << endl;
    }
    else {
        cout << "Game with ID " << gameL << " not found in the tree." << endl;
    }
  
}
void PlayersLayer()
{
    string playerL;
    cout<<"\n Enter player's id to check for the layer: ";
    cin>>playerL;
    int playerLayer = players.getLayerNumber(players.root, playerL);
    if (playerLayer != -1) 
    {
        cout << "Player with ID " << playerL << " is at layer " << playerLayer << "." << endl;
    } 
    else {
        cout << "Player with ID " << playerL << " not found in the tree." << endl;
    }
}

void TotalLayers()
{
    cout << "Number of layers in Game BST: " << games.getNumberOfLayers() << endl;                // gives the max subtree which is the max layer of that binary tree
    cout << "Number of layers in Player BST: " << players.getNumberOfLayers() << endl;
}
 void playerPath()
{
        string playerId;
        cout << "Enter player's id to check for the path: ";
        cin>>playerId;
        players.showPathToPlayer(playerId);
}
   
void editPlayer() 
{
    string searchPlayerId;
    cout << "\nEnter Player ID to search: ";
    cin >> searchPlayerId;
    
    playerNode* player = players.searchPlayer(searchPlayerId); // Assuming `players` is your BST

    if (player) {
        cout << "\nPlayer found!" << endl;
        cout << "Player ID: " << player->playerId << ", Name: " << player->name 
             << ", Phone: " << player->phoneNo << ", Email: " << player->email 
             << ", Password: " << player->password << endl;

        // Print the games played by this player
        cout << "\nGames Played:" << endl;
        for (int i = 0; i < player->gameCount; i++) {
            cout << "    Game ID: " << player->gamesPlayed[i].gameId 
                 << ", Hours Played: " << player->gamesPlayed[i].hoursPlayed 
                 << ", Achievements: " << player->gamesPlayed[i].achievements << endl;
        }

        // Ask if the user wants to edit the player's data
        char choice;
        cout << "\nDo you want to edit the entry of this player? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            bool editing = true;
            while (editing) {
                cout << "\nWhat would you like to edit?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Phone Number" << endl;
                cout << "3. Email" << endl;
                cout << "4. Password" << endl;
                cout << "5. Games Played" << endl;
                cout << "6. Exit Editing" << endl;
                cout << "Enter your choice: ";
                int option;
                cin >> option;

                switch (option) {
                    case 1:
                        cout << "Enter new name: ";
                        cin >> player->name;
                        break;
                    case 2:
                        cout << "Enter new phone number: ";
                        cin >> player->phoneNo;
                        break;
                    case 3:
                        cout << "Enter new email: ";
                        cin >> player->email;
                        break;
                    case 4:
                        cout << "Enter new password: ";
                        cin >> player->password;
                        break;
                    case 5:
                        cout << "Enter the index of the game to edit (0 to " << player->gameCount - 1 << "): ";
                        int gameIndex;
                        cin >> gameIndex;
                        if (gameIndex >= 0 && gameIndex < player->gameCount) {
                            cout << "Current game data:" << endl;
                            cout << "    Game ID: " << player->gamesPlayed[gameIndex].gameId 
                                 << ", Hours Played: " << player->gamesPlayed[gameIndex].hoursPlayed 
                                 << ", Achievements: " << player->gamesPlayed[gameIndex].achievements << endl;
                            cout << "Enter new game ID: ";
                            cin >> player->gamesPlayed[gameIndex].gameId;
                            cout << "Enter hours played: ";
                            cin >> player->gamesPlayed[gameIndex].hoursPlayed;
                            cout << "Enter achievements: ";
                            cin >> player->gamesPlayed[gameIndex].achievements;
                        } else {
                            cout << "Invalid game index." << endl;
                        }
                        break;
                    case 6:
                        editing = false;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            }
            cout << "Player information updated." << endl;
        } else {
            cout << "Edit cancelled." << endl;
        }

    } else {
        cout << "Player with ID '" << searchPlayerId << "' not found." << endl;
    }
}
void showPrePattern()
{
    string ID;
    cout << "Enter player ID: ";
    cin >> ID;
    players.showPathToPlayer(ID);
}
void hasPlayed()
{
    string playerId, gameId;
    
    cout << "Enter Player ID: ";
    cin >> playerId;
    cout << "Enter Game ID: ";
    cin >> gameId;

    // Call the playerBST class function
    if (players.hasPLayed(playerId, gameId)) 
    {
        cout << "Player has played the game." << endl;
    } else {
        cout << "Player has not played the game." << endl;
    }
}
void topNPlayers(int n)
{
    cout<<"Top "<<n<<" Players are: "<<endl;
        for (int i=0;i<n;i++)
        {
            cout <<"Name of Player:  "<< players.topPlayers[i]->name<<endl;
        }
}
//---------------------------------------------------
        void addPlayer(string playerId, string name, string phoneNo, string email, string password)
    {
        // Add player logic here

    }
    void addGame(string gameId, string name, string developer, string publisher, float fileSize, int downloads)
    {
        // Add game logic here
    }
    playerNode* getPlayer(string playerId)
    {
            // Get player node by ID logic here
            return nullptr;
    }
    gameNode* getGame(string gameId)
    {
            // Get game node by ID logic here
            return nullptr;
    }
    //-------------------------------------------------------------------------
};



int main()
{
Database db;
db.loadGamesFromCSV();
db.loadPlayersFromCSV();
// db.deleteGame();
// db.deletePlayer();
// db.searchGame();
// db.searchPlayerDetail();
// db.TotalLayers();
// db.GamesLayer();
// db.PlayersLayer();
// db.editPlayer();
//db.showPrePattern();
// db.hasPlayed();
db.topNPlayers(5);

return 0;
}
