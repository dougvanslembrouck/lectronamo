class WizardModeGame {
private:
    int score;                          // Player's score
    int standupHitCount;                // Tracks how many times standup target #12 is hit
    bool wizardModeActive;              // Flag to indicate if wizard mode is active
    bool dropTarget3BankState[3];       // State of the 3-bank drop targets
    bool dropTarget5BankState[5];       // State of the 5-bank drop targets
    int litTargetIndex;                 // Index of the currently lit 3-bank target (0 to 2)
    int switches3Bank[3] = {12, 22, 30}; // Switch IDs corresponding to the 3-bank targets
    int switches5Bank[5] = {40, 41, 42, 43, 44}; // Switch IDs corresponding to the 5-bank targets

public:
    // Constructor to initialize game state
    WizardModeGame() : score(0), standupHitCount(0), wizardModeActive(false), litTargetIndex(-1) {
        // Initialize all targets to the "up" position
        for (int i = 0; i < 3; i++) {
            dropTarget3BankState[i] = false;
        }
        for (int i = 0; i < 5; i++) {
            dropTarget5BankState[i] = false;
        }
    }

    // Function to handle a hit on standup target #12
    void handleStandupTargetHit() {
        standupHitCount++;
        displayMessage("Standup Target #12 Hit!");

        // Initialize wizard mode after 2 hits
        if (standupHitCount >= 2 && !wizardModeActive) {
            initializeWizardMode();
        }
    }

    // Initialize final wizard mode
    void initializeWizardMode() {
        wizardModeActive = true;
        displayMessage("Final Wizard Mode Initialized!");
        cycleDropTargetLights();  // Start cycling 3-bank lights
    }

    // Function to cycle 3-bank drop target lights in sequential order
    void cycleDropTargetLights() {
        litTargetIndex = (litTargetIndex + 1) % 3;
        displayMessage("Cycling 3-bank Lights");
        for (int i = 0; i < 3; i++) {
            if (i == litTargetIndex) {
                lightTarget(i);  // Light up the current target
            } else {
                unlightTarget(i);  // Turn off lights for other targets
            }
        }
    }

    // Function to handle a 3-bank switch hit
    void handle3BankSwitchHit(int switchId) {
        for (int i = 0; i < 3; i++) {
            if (switchId == switches3Bank[i] && i == litTargetIndex && wizardModeActive) {
                displayMessage("Wizard Mode Activated! Resetting All Drops.");
                resetAllDropTargets();  // Reset all drop targets when wizard mode starts
                break;
            }
        }
    }

    // Function to reset both 3-bank and 5-bank drop targets
    void resetAllDropTargets() {
        for (int i = 0; i < 3; i++) {
            dropTarget3BankState[i] = false;  // Reset 3-bank targets to "up" position
        }
        for (int i = 0; i < 5; i++) {
            dropTarget5BankState[i] = false;  // Reset 5-bank targets to "up" position
        }
        displayMessage("All Drop Targets Reset");
    }

    // Function to handle hits on both 3-bank and 5-bank targets during wizard mode
    void handleDropTargetHit(int bank, int targetIndex) {
        if (wizardModeActive) {
            if (bank == 3 && targetIndex < 3) {
                dropTarget3BankState[targetIndex] = true;  // Mark 3-bank target as down
                checkIfWizardModeComplete();              // Check if wizard mode is complete
            } else if (bank == 5 && targetIndex < 5) {
                dropTarget5BankState[targetIndex] = true;  // Mark 5-bank target as down
                checkIfWizardModeComplete();              // Check if wizard mode is complete
            }
        }
    }

    // Check if both the 3-bank and 5-bank targets are down to complete wizard mode
    void checkIfWizardModeComplete() {
        bool all3BankDown = true;
        bool all5BankDown = true;

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

        // If all targets are down, the wizard mode is complete
        if (all3BankDown && all5BankDown) {
            wizardModeActive = false;
            displayMessage("Wizard Mode Completed! You Win!");
            awardWizardModeCompletionPoints();
        }
    }

    // Function to award points when wizard mode is successfully completed
    void awardWizardModeCompletionPoints() {
