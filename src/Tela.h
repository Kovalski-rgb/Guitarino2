#pragma once
#include <Shape.h>

class Tela{

    private: static const int width = 10;
    private: static const int height = 22;
    private: boolean arrayLeds[height][width];

    // Cria um objeto Tela, que manipula o display do equipamento, se auto-inicializa dentro do construtor
    public: Tela(){
        setDisplay();
    };

    /*
    Inicializa o display, obrigatório para funcionamento correto da tela.
    É chamado automaticamente no construtor
    */
    private: void setDisplay(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                arrayLeds[i][j] = false;
            }
        }
    }

    // Retorna a largura da tabela
    public: int getWidth(){
        return width;
    }

    // Retorna a altura da tabela
    int getHeight(){
        return height;
    }

    // Imprime no serial uma representação da tela, sendo os 0 leds apagados e 1, leds ligados
    void printSerial(){
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
    void clearSerial(){
        
    }

    // Seta a coluna especificada (0-9) com o estado especificado (true/false)
    void setColumn(int column, boolean state){
        /*
        if(column < 0 || column > width){
            throw new InvalidArgumentException("Coluna selecionada ("+column+") fora da tela");
        }*/
        for(int h = 0; h<height; h++){
            arrayLeds[h][column] = state;
        }
    }

    // Seta a linha especificada (0-21) com o estado especificado (true/false)
    public: void setRow(int row, boolean state){
        /*
        if(row < 0 || row > height){
            throw new InvalidArgumentException("Linha selecionada ("+row+") fora da tela");
        }*/
        for(int w = 0; w<width; w++){
            arrayLeds[row][w] = state;
        }
    }

    // Seta o pixel X, y como o estado especificado (true/false)
    public: void setPixel(int row, int column, boolean state){
        /*
        if(row < 0 || row > height || column < 0 || column > height){
            throw new InvalidArgumentException("Pixel selecionado ("+row+", "+column+") fora da tela");
        }*/
        arrayLeds[row][column] = state;
        
    }

    // Seta o display inteiro com o estado espeficicado (true/false)
    void setDisplay(boolean state){
        for(int w = 0; w < width; w++){
            for(int h = 0; h < height; h++){
                arrayLeds[h][w] = state;
            }
        }
    }

    // Retorna true somente se todas as posições da linha estiverem ligadas
    bool isRowOn(int row){
        for(int w = 0; w<width; w++){
            if(!arrayLeds[row][w]){
                return false;
            }
        }
        return true;
    }

    // Retorna true somente se todas as posições da coluna estiverem ligadas
    bool isColumnOn(int column){
        for(int h = 0; h<height; h++){
            if(!arrayLeds[h][column]){
                return false;
            }
        }
        return true;
    }

    // Retorna true se o pixel estiver ligado, caso contrario, retorna false
    bool isPixelOn(int row, int column){
        if(!arrayLeds[row][column]){
            return false;
        }
        return true;
    }

    // desenha uma forma, especificada dentro de uma matrix shape, começando na posição x, y, indo para baixo e para a direita
    void drawShape(Shape* shape, int y, int x){
        
        int* matriz = shape->matriz;

        int size = sizeof(matriz)/sizeof(matriz[0]);

        for(int i = 0; i<size; i++){
            arrayLeds[y][x + i] = matriz[i];
        }
    }

};
