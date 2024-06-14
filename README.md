# Light-Bounce-Game-Final
My final project for ENGR103
Rules: The light bounces between the left and right buttons along the neopixels, if it passes them, then the game is over. The delay speed gets faster as the game continues, and the score increases with every correct input. The left button must be pushed if the light moves left, and the right button must be pushed if the light heads right in order to score points and keep the game going..
Inputs: The right button adds score and sets the light to move left. The left button adds score and sets light to move right. The slide sets the gamestate to 0 and acts as a pause.
Outputs: Lights indicate where the light is and how long you have left to press the button. The speaker plays a noise every time the button is correctly hit, the game is paused, or the game ends. The serial monitor prints the score and the rules. Score increases with every correct hit. Speedvalue decreases with every correct hit.
