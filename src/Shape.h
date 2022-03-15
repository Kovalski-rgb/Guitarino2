#pragma once

struct Shape{

    int x = 0b000;
    int y = 0b000;
    int z = 0b000;

int matriz[3] {x, y, z};


    
        Shape(int t_matriz[3]){
            matriz[0] = t_matriz[0];
    }
};

//Shape PecaT( {1, 0, 0} );