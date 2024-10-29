// Fourth successful hit of all targets will cycle drop target lights in sequential order. Successful hit on lit target and respective lit switch at #12, 22, 30 scores.

// Assuming we have a class for handling the game logic for the 3-bank drop targets
class DropTargetGame {
private:
    int score;                         // Player's score
    int bankCompleteCount;             // Number of times all drop targets have been completed
    bool dropTargetState[3];           // State of each drop target (true if down, false if up)
    int litTargetIndex;                // Index of the currently lit target (0 to 2)
    int switches[3] = {12, 22, 30};    // Switch IDs corresponding to the targets

public:
    // Constructor to initialize game state
    DropTargetGame() : score(0), bankCompleteCount(0), litTargetIndex(-1) {
        for (int i = 0; i < 3; i++) {
            dropTargetState[i] = false;  // All targets start in the "up" position
        }
    }

    // Function to handle a drop target hit
    void handleDropTargetHit(int targetIndex) {
        if (!dropTargetState[targetIndex]) {
            dropTargetState[targetIndex] = true;  // Mark target as hit (down)
            checkIfBankComplete();                // Check if all targets are down
        }
    }

    // Check if all targets in the 3-bank are down
    void checkIfBankComplete() {
        bool allDown = true;
        for (int i = 0; i < 3; i++) {
            if (!dropTargetState[i]) {
                allDown = false;
                break;
            }
        }

        if (allDown) {
            bankCompleteCount++;  // Increment the completion count
            resetDropTargets();   // Reset targets for the next round
            if (bankCompleteCount == 4) {
                cycleDropTargetLights();  // After fourth completion, cycle the lights
            }
        }
    }

    // Function to reset the drop targets (set them back to "up" state)
    void resetDropTargets() {
        for (int i = 0; i < 3; i++) {
            dropTargetState[i] = false;  // All targets reset to the "up" position
        }
    }

    // Function to cycle drop target lights in a sequential order
    void cycleDropTargetLights() {
        // Cycle through the targets to light them up one at a time
        litTargetIndex = (litTargetIndex + 1) % 3;
        displayMessage("Cycling Target Lights");
        for (int i = 0; i < 3; i++) {
            if
