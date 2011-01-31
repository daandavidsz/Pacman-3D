#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            glow[i][j] = 0.0;
        }
    }

    digits['0'] = std::bitset<15>(std::string("111101101101111")); // 0
    digits['1'] = std::bitset<15>(std::string("001001001001001")); // 1
    digits['2'] = std::bitset<15>(std::string("111001111100111")); // 2   
    digits['3'] = std::bitset<15>(std::string("111001111001111")); // 3    
    digits['4'] = std::bitset<15>(std::string("101101111001001")); // 4
    digits['5'] = std::bitset<15>(std::string("111100111001111")); // 5
    digits['6'] = std::bitset<15>(std::string("111100111101111")); // 6
    digits['7'] = std::bitset<15>(std::string("111001001010010")); // 7
    digits['8'] = std::bitset<15>(std::string("111101111101111")); // 8
    digits['9'] = std::bitset<15>(std::string("111101111001111")); // 9
}

void ScoreBoard::onSignal(std::string name) {
    if (name == "energizer")
            score += 50;
    else if(name ==  "pellet")
            score += 10;
}

void ScoreBoard::render(float ticks) {
    glPushMatrix();
    glTranslatef(-2.3, 1.3, -5);
    
    std::string scoreString;
    std::stringstream stringStream;
    stringStream << score;
    scoreString = stringStream.str();
    
    for (int d = 0; d < scoreString.length(); d++) {
        std::bitset<15> digit = digits[scoreString[d]];
        int counter = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 3; x++) {
                float wantedGlow = 1*digit[counter];
                float newGlow = (1.0 - 10*ticks) * glow[d][counter] + 10*ticks * wantedGlow;
                if (wantedGlow > 0.1) {
                    glow[d][counter] = newGlow;
                    glColor4f(1-newGlow, 1, 1-newGlow, 1);        
                    glTranslatef(-x/9.0, y/9.0, 0);        
                    glutSolidSphere(0.05, 10, 10);            
                    glTranslatef(x/9.0, -y/9.0, 0);        
                }
                else {
                    glow[d][counter] = wantedGlow;
                }
                counter++;            
            }
        }
        glTranslatef(0.45, 0, 0);
    }
    glPopMatrix();
}
