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
    
    playerBST() : root(nullptr) {}

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


private:
    playerNode* insertRec(playerNode* node, string playerId, string name, string phoneNo, string email, string password, games_played_node* gamesPlayed, int gameCount) 
    {
        if (node == nullptr) {
            playerNode* newNode = new playerNode(playerId, name, phoneNo, email, password, gameCount);
            for (int i = 0; i < gameCount; i++) 
            {
                newNode->gamesPlayed[i] = gamesPlayed[i];
            }
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

// class Database
// {
// private:
//     playerBST players;
//     gameBST games;
// public:
//     Database(int seed)
//     {
//         // Initialize database with seed logic here
//     }
//     void loadPlayersFromCSV(const string& filePath)
//     {
//         // Load player data from CSV with seed-based line-skipping logic here
//     }
//     void loadGamesFromCSV(const string& filePath)
//     {
//         // Load game data from CSV logic here
//     }
//     playerNode* getPlayer(string playerId)
//     {
//         // Get player node by ID logic here
//     }
//     gameNode* getGame(string gameId)
//     {
//         // Get game node by ID logic here
//     }
//     void addPlayer(string playerId, string name, string phoneNo, string email, string password)
//     {
//         // Add player logic here
//     }
//     void addGame(string gameId, string name, string developer, string publisher, float fileSize, int downloads)
//     {
//         // Add game logic here
//     }
//     void deletePlayer(string playerId)
//     {
//         // Delete player logic here
//     }
//     void deleteGame(string gameId)
//     {
//         // Delete game logic here
//     }
//     void topNPlayers(int N)
//     {
//         // Find top N players by games played logic here
//     }
//     bool hasPlayed(string playerId, string gameId)
//     {
//         // Check if player has played specific game logic here
//     }
// };
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

int main()
{
    gameBST games;
    loadGamesFromFile("Games.txt", games);
    cout << "Games loaded based on random selection criteria." << endl;
    cout << "\nPrinting the Game BST in sorted order:" << endl;
    games.printGameBST();
cout<<"-------------------------------------------------------------------------------";
    playerBST players;
    loadPlayersFromFile("Players.txt", players);
    cout << "Players loaded based on random selection criteria." << endl;
    cout << "\nPrinting the Player BST in sorted order:" << endl;
    players.printPlayerBST();

cout<<"-------------------------------------------------------------------------------";

     // Search for a player by playerId
    string searchPlayerId;
    cout << "\nEnter Player ID to search: ";
    cin >> searchPlayerId;

    // Call the searchPlayer function
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

cout<<"-------------------------------------------------------------------------------";
// Search for a game by gameId
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

cout<<"-------------------------------------------------------------------------------";

string gameIdToDelete;
cout << "\nEnter Game ID to delete: ";
cin >> gameIdToDelete;
games.deleteGame(gameIdToDelete);
cout<<"\n you can verify the game is deleted from here\n";
games.printGameBST();
cout<<"-------------------------------------------------------------------------------";
string playerIdToDelete;
cout << "\nEnter Player ID to delete: ";
cin >> playerIdToDelete;
players.deletePlayer(playerIdToDelete);

string gameL,playerL;
cout<<"\n Enter game's id to check for the layer: ";
cin>>gameL;
cout<<"\n Enter player's id to check for the layer: ";
cin>>playerL;

int gameLayer = games.getLayerNumber(games.root, gameL);
if (gameLayer != -1) 
{
    cout << "Game with ID " << gameL << " is at layer " << gameLayer << "." << endl;
}
else {
    cout << "Game with ID " << gameL << " not found in the tree." << endl;
}

int playerLayer = players.getLayerNumber(players.root, playerL);
if (playerLayer != -1) 
{
    cout << "Player with ID " << playerL << " is at layer " << playerLayer << "." << endl;
} 
else {
    cout << "Player with ID " << playerL << " not found in the tree." << endl;
}


// cout << "Number of layers in Game BST: " << games.getNumberOfLayers() << endl;                // gives the max subtree which is the max layer of that binary tree
// cout << "Number of layers in Player BST: " << players.getNumberOfLayers() << endl;

return 0;
}
