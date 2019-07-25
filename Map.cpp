#include "Map.h"

using namespace std;

Map::Map(Game* _game, Objects* _objects) {
    game = _game;
    objects = _objects;
}



void Map::getMap(string mapAdress) {
    ifstream *mapFile = new ifstream("1.txt");
    mapFile->open("1.txt");
    mapFile->close();
    getMapp();
    mapFile-> close();
    string line;
    while (getline(cin, line)) {
        map.push_back(vector<char>());
        for(int i = 0; i < line.length(); i++) {
            map[map.size() - 1].push_back(line[i]);
        }
    }
    // mapFile->close();
}

void Map::initGameSetup() {
    for(int row = 0; row < map.size(); row++) {
        processMapRow(map[row], row);
    }
}

void Map::processMapRow(vector<char>& mapRow, int row) {
    for (int charIndex = 0 ; charIndex < mapRow.size(); charIndex++){
       processChar(mapRow[charIndex], Point(charIndex, row));
    }
}

void Map::processChar(char c, Point pos) {
    Point pixelPos(pos.x * BLOCK_SIZE
        , pos.y * BLOCK_SIZE );
    switch(c){
        case MARIO: {
            Mario* mario = new Mario(pixelPos);
            game->setMario(mario);
        }
        break;
        case PIPE: {
            Pipe* pipe = new Pipe(pixelPos,
                findPipeHeight(pos.y, pos.x));
            clearPipe(pos.y, pos.x);
            objects->addPipe(pipe);
        }
        break;
        case FLAG: {
            Flag* flag = new Flag(pixelPos,
                findFlagHeight(pos.y, pos.x));
            objects->addFlag(flag);
            clearFlag(pos.y, pos.x);
        }
        break;
        case GROUND_BLOCK: {
            NormalBlock* normalBlock = new NormalBlock(pixelPos,
                GROUND_BLOCK);
            objects->addNormalBlock(normalBlock);
        }
        break;
        case NORMAL_BLOCK: {
            NormalBlock* normalBlock = new NormalBlock(pixelPos,
                NORMAL_BLOCK);
            objects->addNormalBlock(normalBlock);
        }
        break;
        case COIN_BLOCK: {
            QuestionBlock* coinBlock = new QuestionBlock(pixelPos,
                COIN_BLOCK);
            objects->addQuestionBlock(coinBlock);
        }
    }
}

int Map::findPipeHeight(int headRow, int headCol){
    int i = headRow;
    int height = 0;
    while (map[i][headCol] == PIPE){
        height++;
        i++;
        if (i >= map.size())
            break;
    }
    return height;
}

void Map::clearPipe(int headRow, int headCol) {
    int height = findPipeHeight(headRow, headCol);
    for (int i = 0; i <  height; i++) {
        map[headRow + i][headCol] = EMPTY;
        map[headRow + i][headCol + 1] = EMPTY;
    }
}

int Map::findFlagHeight(int headRow, int headCol){
    int i = headRow;
    int height = 0;
    while (map[i][headCol] == FLAG){
        height++;
        i++;
        if (i >= map.size())
            break;
    }
    return height;
}

void Map::clearFlag (int headRow, int headCol) {
    int height = findFlagHeight(headRow, headCol);
    for (int i = 0; i < height; i++)
        map[headRow + i][headCol] = EMPTY;
}

int Map::getMapHeight(){
    return map.size();
}
