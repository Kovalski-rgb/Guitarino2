

class Tela{

    private: static const int width = 10;
    private: static const int height = 22;
    private: boolean arrayLeds[height][width];

    public: Tela(){
    };
    public: void setDisplay(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                arrayLeds[i][j] = false;
            }
        }
    }

    public: int getWidth(){
        return width;
    }

    public: int getHeight(){
        return height;
    }

    public: void printSerial(){
        for(int i = 0; i < height; i++){
            Serial.print("|");
            for(int j = 0; j < width; j++){
                Serial.print(arrayLeds[i][j]);
                Serial.print("|");
            }
            Serial.println();
        }
        Serial.println("+-------------------+");
    }

    // LEO me ajuda a limpar a tela do serial pelo amor de deus
    public: void clearDebugScreen(){
        
    }

public: void setColumn(int column, boolean state){
        /*
        if(column < 0 || column > width){
            throw new InvalidArgumentException("Coluna selecionada ("+column+") fora da tela");
        }*/
        for(int h = 0; h<height; h++){
            arrayLeds[h][column] = state;
        }
    }

    public: void setRow(int row, boolean state){
        /*
        if(row < 0 || row > height){
            throw new InvalidArgumentException("Linha selecionada ("+row+") fora da tela");
        }*/
        for(int w = 0; w<width; w++){
            arrayLeds[row][w] = state;
        }
    }

    public: void setPixel(int row, int column, boolean state){
        /*
        if(row < 0 || row > height || column < 0 || column > height){
            throw new InvalidArgumentException("Pixel selecionado ("+row+", "+column+") fora da tela");
        }*/
        arrayLeds[row][column] = state;
        
    }

    public: void setDisplay(boolean state){
        for(int w = 0; w < width; w++){
            for(int h = 0; h < height; h++){
                arrayLeds[h][w] = state;
            }
        }
    }

};
