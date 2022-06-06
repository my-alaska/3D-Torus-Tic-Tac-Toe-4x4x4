#include <iostream>
#include "game_map.h"
using namespace std;

game_map::game_map(int size, int length, int start_value) {
    a = b = c = 0;
    _value = start_value;
    map_size = size;
    winning_length = length;
    map = new int**[map_size];
    for(int i = 0; i < map_size; i++){
        map[i] = new int*[map_size];
        for(int j = 0; j < map_size; j++){
            map[i][j] = new int[map_size];
            for(int k = 0; k < map_size; k++){
                map[i][j][k] = 0;
            }
        }
    }
}

game_map::~game_map() {
    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            delete [] map[i][j];
        }
        delete [] map[i];
    }
    delete [] map;
}

void game_map::clear() {
    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            for(int k = 0; k < map_size; k++){
                map[i][j][k] = 0;
            }
        }
    }
}

int ** game_map::single_check(int i, int j, int k) {
    int counter = 0;
    for(int s = - winning_length + 1; s <= winning_length - 1; s++){
        if(map[(map_size+a+i*s)%map_size][(map_size+b+j*s)%map_size][(map_size+c+k*s)%map_size] == _value){
            counter++;
        }else counter = 0;
        if(counter == winning_length){
            int ** result = new int*[winning_length];
            for( int t = 0; t < winning_length; t++){
                result[t] = new int[3];
                result[t][0] = (map_size+a+i*(s-t))%map_size;
                result[t][1] = (map_size+b+j*(s-t))%map_size;
                result[t][2] = (map_size+c+k*(s-t))%map_size;
            }
            return result;
        }
    }
    return nullptr;
}

int ** game_map::check() {
    int ** result = nullptr;
    for ( int i = 0; i < base_size; i++ ){
        if((result = single_check(base[i][0],base[i][1],base[i][2])) != nullptr){
            return result;
        }
    }
    return nullptr;
}

int game_map::place(int i, int j, int k, int value) {
    if(map[i][j][k] != 0) return 1;
    map[i][j][k] = value;
    _value = value;
    a = i;
    b = j;
    c = k;
    return 0;
}


