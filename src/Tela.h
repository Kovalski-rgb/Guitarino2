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
    public: int getHeight(){
        return height;
    }

    // Imprime no serial uma representação da tela, sendo os 0 leds apagados e 1, leds ligados
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
    public: void clearSerial(){
        
    }

    // Seta a coluna especificada (0-9) com o estado especificado (true/false)
    public: void setColumn(int column, boolean state){
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
    public: void setDisplay(boolean state){
        for(int w = 0; w < width; w++){
            for(int h = 0; h < height; h++){
                arrayLeds[h][w] = state;
            }
        }
    }

    // desenha uma forma, especificada dentro de uma matrix shape, começando na posição x, y, indo para baixo e para a direita
    public: void drawShape(int* shape, int y, int x){
        int LarguraArray = sizeof(shape) / 2;
        Serial.println(LarguraArray);
        for(int i = 0; i<LarguraArray; i++){
            arrayLeds[y][x+i] = shape[i];
        }
    }

};
