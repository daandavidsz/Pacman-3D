#pragma once

class BloodParticle {

    Vector position;   
    Vector movementVector; 
    
    public:
        void setPosition(Vector position);
        void setMovementVector(Vector movementVector);        
        void update(float ticks);
        void render();
};
