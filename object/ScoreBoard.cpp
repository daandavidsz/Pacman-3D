#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    EventSystem::getInstance()->addObserver(this, "pellet");
    EventSystem::getInstance()->addObserver(this, "energizer");
    EventSystem::getInstance()->addObserver(this, "ghost_eaten");    

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            glow[i][j] = 0.0;
        }
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
    
    reset();
}

void ScoreBoard::reset() {
    ghostPoints = 1000;
    score = 0;
}

void ScoreBoard::onSignal(std::string name) {
    if (name == "energizer") {
        ghostPoints = 1000;
        score += 50;
    }
    else if (name == "pellet") {
        score += 10;
    }
    else if (name == "ghost_eaten") {
        score += ghostPoints;
        ghostPoints += 1000;
    }
}

void ScoreBoard::update(float ticks) {
    lastTicks = ticks;
}

void ScoreBoard::render() {
    glPushMatrix();
    glTranslatef(-2.28, 1.60, -5);
    
    unsigned int currentScore = score;
    while (currentScore > 0) {
        numberStack.push(currentScore % 10);
        currentScore = (int)currentScore / 10;
    }
    
    int stackSize = numberStack.size();
    for (int d = 0; d < stackSize; d++) {
        std::bitset<15> digit = digits[(int)numberStack.top()];
    
        if ((int)numberStack.top() == 1) {
            //glTranslatef(-0.20, 0, 0);
        }
        
        int counter = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 3; x++) {
                float wantedGlow = 1*digit[counter];
                float newGlow = (1.0 - 10*lastTicks) * glow[d][counter] + 10*lastTicks * wantedGlow;
                if (wantedGlow > 0.1) {
                    glow[d][counter] = newGlow;
                    //glColor4f(1-newGlow, 1, 1-newGlow, 1);
                    glColor4f(0.3, 0.3, 0.3, 1);                
                    glTranslatef(-x/11.0, y/11.0, 0);        
                    glutSolidSphere(0.04, 10, 10);            
                    glTranslatef(x/11.0, -y/11.0, 0);        
                }
                else {
                    glow[d][counter] = wantedGlow;
                }
                counter++;            
            }
        }
        glTranslatef(0.35, 0, 0);
            
        numberStack.pop();
    }
    glPopMatrix();
}
