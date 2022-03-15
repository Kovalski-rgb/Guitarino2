#pragma once

struct Shape{
    // BASICAMENTE os bits dentro do int vão ser os "vetores" dentro do vetor principal
    // isso limita o guitarino em uma parada meio monocromatica, mas convenhamos que 220 leds rgb ia sair MUITO caro
    Shape(){
        
    }
    
    byte coluna1 = 0b00;
    byte coluna2 = 0b00;

    int matriz[2] {coluna1, coluna2};
    
    /* 
    Shape(int t_matriz[2]){
        matriz[0] = t_matriz[0];
    }*/

    int* PecaI(){
        int peca = 0b1111;
        return &peca;
    }

    int* PecaT(){
        int cima =  0b111;
        int meio =  0b010;
        int baixo = 0b010;
        int mat[3] = {cima, meio, baixo};
        return mat;
    }

};

//Shape PecaT( {1, 0, 0} );