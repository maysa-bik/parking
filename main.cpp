#include <iostream>
#include <vector>

using namespace std;

class ParkingGame {
private:
    vector<vector<char>> grid;
    vector<pair<char, vector<pair<int, int>>>> vehicles;

public:
    ParkingGame() : grid(6, vector<char>(6, '_')) {}

    void printGrid() {
        for (const auto& row : grid) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    void placeVehicles() {
        vehicles.push_back(make_pair('X', vector<pair<int, int>>{{0, 1}, {0, 2}})); // Exemple de véhicule à sortir (X)
        vehicles.push_back(make_pair('1', vector<pair<int, int>>{{3, 0}, {3, 1}, {3, 2}})); // Exemple de véhicule contrainte (1)

        for (const auto& vehicle : vehicles) {
            char type = vehicle.first;
            const auto& positions = vehicle.second;
            for (const auto& position : positions) {
                int i = position.first;
                int j = position.second;
                grid[i][j] = type;
            }
        }
    }

    bool moveVehicle(char type, char direction) {
        int di = 0, dj = 0;
        if (direction == 'G') dj = -1;
        else if (direction == 'D') dj = 1;
        else if (direction == 'H') di = -1;
        else if (direction == 'B') di = 1;
        else return false; // Mouvement invalide

        for (auto& vehicle : vehicles) {
            if (vehicle.first == type) {
                for (auto& position : vehicle.second) {
                    int i = position.first;
                    int j = position.second;
                    int newI = i + di;
                    int newJ = j + dj;
                    if (newI < 0 || newI >= 6 || newJ < 0 || newJ >= 6 || grid[newI][newJ] != '_') {
                        return false; // Mouvement invalide
                    }
                }

                // Mettre à jour la grille
                for (auto& position : vehicle.second) {
                    int i = position.first;
                    int j = position.second;
                    grid[i][j] = '_';
                    position.first += di;
                    position.second += dj;
                    grid[position.first][position.second] = type;
                }
                return true; // Mouvement valide
            }
        }
        return false; // Véhicule non trouvé
    }
};

int main() {
    ParkingGame game;
    game.placeVehicles();
    game.printGrid();
    
    while (true) {
        char type, direction;
        cout << "Entrez le type de véhicule et la direction (ex: X D) ou 'Q' pour quitter : ";
        cin >> type;
        if (type == 'Q') break;
        cin >> direction;
        if (!game.moveVehicle(type, direction)) {
            cout << "Mouvement invalide, veuillez réessayer." << endl;
        } else {
            game.printGrid();
        }
    }

    return 0;
}
