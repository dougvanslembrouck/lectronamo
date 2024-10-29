class AllDropTargetsMode {
private:
    int score;                          // Player's score
    bool allTargetsModeActive;          // Flag to indicate if "All Drop Targets" mode is active
    bool dropTarget3BankState[3];       // State of the 3-bank drop targets
    bool dropTarget5BankState[5];       // State of the 5-bank drop targets
    bool additionalDropTargets[2];      // Additional drop targets (if any)

public:
    // Constructor to initialize game state
    AllDropTargetsMode() : score(0), allTargetsModeActive(false) {
        // Initialize all targets to the "up" position
        for (int i = 0; i < 3; i++) {
            dropTarget3BankState[i] = false;
        }
        for (int i = 0; i < 5; i++) {
            dropTarget5BankState[i] = false;
        }
        for (int i = 0; i < 2; i++) {
            additionalDropTargets[i] = false;
        }
    }

    // Function to activate the "All Drop Targets" mode
    void activateAllDropTargetsMode() {
        allTargetsModeActive = true;
        resetAllDropTargets();  // Reset all targets at the start of the mode
        displayMessage("All Drop Targets Mode Activated!");
    }

    // Function to reset all drop targets (3-bank, 5-bank, and additional targets)
    void resetAllDropTargets() {
        for (int i = 0; i < 3; i++) {
            dropTarget3BankState[i] = false;  // Reset 3-bank targets to "up" position
        }
        for (int i = 0; i < 5; i++) {
            dropTarget5BankState[i] = false;  // Reset 5-bank targets to "up" position
        }
        for (int i = 0; i < 2; i++) {
            additionalDropTargets[i] = false;  // Reset additional targets to "up" position
        }
        displayMessage("All Drop Targets Reset");
    }

    // Function to handle hits on all drop targets during the "All Drop Targets" mode
    void handleDropTargetHit(int bank, int targetIndex) {
        if (allTargetsModeActive) {
            if (bank == 3 && targetIndex < 3) {
                dropTarget3BankState[targetIndex] = true;  // Mark 3-bank target as down
            } else if (bank == 5 && targetIndex < 5) {
                dropTarget5BankState[targetIndex] = true;  // Mark 5-bank target as down
            } else if (bank == 1 && targetIndex < 2) {
                additionalDropTargets[targetIndex] = true;  // Mark additional target as down
            }

            checkIfAllTargetsDown();  // Check if all targets are down
        }
    }

    // Check if all drop targets (3-bank, 5-bank, and additional) are down to complete the mode
    void checkIfAllTargetsDown() {
        bool all3BankDown = true;
        bool all5BankDown = true;
        bool allAdditionalDown = true;

        // Check if all 3-bank targets are down
        for (int i = 0; i < 3; i++) {
            if (!dropTarget3BankState[i]) {
                all3BankDown = false;
                break;
            }
        }

        // Check if all 5-bank targets are down
        for (int i = 0; i < 5; i++) {
            if (!dropTarget5BankState[i]) {
                all5BankDown = false;
                break;
            }
        }

        // Check if all additional drop targets are down
        for (int i = 0; i < 2; i++) {
            if (!additionalDropTargets[i]) {
                allAdditionalDown = false;
                break;
            }
        }

        // If all drop targets are down, the mode is complete
        if (all3BankDown && all5BankDown && allAdditionalDown) {
            completeAllTargetsMode();
        }
    }

    // Function to complete the "All Drop Targets" mode
    void completeAllTargetsMode() {
        allTargetsModeActive = false;
        displayMessage("All Drop Targets Mode Completed! Awarding Bonus Points.");
        awardAllTargetsCompletionPoints();
    }

    // Function to award points when all drop targets are successfully completed
    void awardAllTargetsCompletionPoints() {
        score += 10000;  // Award 10000 points for completing the mode
    }

    // Function to display messages (to console or display)
    void displayMessage(const char* message) {
        // For now, we'll print to the console (or you can replace this with actual display code)
        Serial.println(message);
    }

    // Function to get the current score
    int getScore() const {
        return score;
    }

    // Additional game loop functions, event handling, etc.
};

// Example usage in the main game loop
void loop() {
    AllDropTargetsMode allTargetsMode;  // Create a new game instance

    // Simulate activating the "All Drop Targets" mode
    allTargetsMode.activateAllDropTargetsMode();

    // Simulate dropping all 3-bank, 5-bank, and additional targets
    allTargetsMode.handleDropTargetHit(3, 0);  // Drop first 3-bank target
    allTargetsMode.handleDropTargetHit(3, 1);  // Drop second 3-bank target
    allTargetsMode.handleDropTargetHit(3, 2);  // Drop third 3-bank target
    allTargetsMode.handleDropTargetHit(5, 0);  // Drop first 5-bank target
    allTargetsMode.handleDropTargetHit(5, 1);  // Drop second 5-bank target
    allTargetsMode.handleDropTargetHit(5, 2);  // Drop third 5-bank target
    allTargetsMode.handleDropTargetHit(5, 3);  // Drop fourth 5-bank target
    allTargetsMode.handleDropTargetHit(5, 4);  // Drop fifth 5-bank target
    allTargetsMode.handleDropTargetHit(1, 0);  // Drop first additional target
    allTargetsMode.handleDropTargetHit(1, 1);  // Drop second additional target
}
