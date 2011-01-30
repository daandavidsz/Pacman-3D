#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    for (int i = 0; i < 15; i++) {
        glow[i] = 0.0;
    }

    digits.push_back(std::bitset<15>(std::string("111101101101111"))); // 0
    digits.push_back(std::bitset<15>(std::string("001001001001001"))); // 1
    digits.push_back(std::bitset<15>(std::string("111001111100111"))); // 2   
    digits.push_back(std::bitset<15>(std::string("111001111001111"))); // 3    
    digits.push_back(std::bitset<15>(std::string("101101111001001"))); // 4
    digits.push_back(std::bitset<15>(std::string("111100111001111"))); // 5
    digits.push_back(std::bitset<15>(std::string("111100111101111"))); // 6
    digits.push_back(std::bitset<15>(std::string("111001001010010"))); // 7
    digits.push_back(std::bitset<15>(std::string("111101111101111"))); // 8
    digits.push_back(std::bitset<15>(std::string("111101111001111"))); // 9
}

void ScoreBoard::onSignal(std::string name) {
    if (name == "energizer")
            score += 2;
    else if(name ==  "pellet")
            score += 1;

    // std::cout << "Score: " << score << "\n"; 
}

void ScoreBoard::render(float ticks) {
    glPushMatrix();
    glTranslatef(0, -19, -19.5);        
    
    std::bitset<15> digit = digits[score % 10];
    int counter = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 3; x++) {
            float wantedGlow = 1*digit[counter];
            float newGlow = (1.0 - 10*ticks) * glow[counter] + 10*ticks * wantedGlow;
            glow[counter] = newGlow;
            glColor4f(0, newGlow, 0, 1);        
            glTranslatef(-x, y, 0);        
            glutSolidSphere(0.4, 10, 10);            
            glTranslatef(x, -y, 0);        
            counter++;            
        }
    }
    glPopMatrix();
}
