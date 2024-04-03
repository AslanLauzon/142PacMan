// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include <stdlib.h>
#include "ghost.h"
#include "map.h"

char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    if (pacman_x == ghost_x && pacman_y == ghost_y) {
        return EATING_PACMAN;
    }

    int step;
    // Check for vertical alignment (same column)
    if (pacman_x == ghost_x) {
        if (pacman_y > ghost_y) {
            step = 1; // Pacman is below the ghost
        } else {
            step = -1; // Pacman is above the ghost
        }
        for (int y = ghost_y + step; y <= pacman_y; y += step) {
            if (is_wall(y, ghost_x)) {
                return SEES_NOTHING;
            }
        }
        if (step == 1) {
            return DOWN;
        } else {
            return UP;
        }
    }

    // Check for horizontal alignment (same row)
    if (pacman_y == ghost_y) {
        if (pacman_x > ghost_x) {
            step = 1; // Pacman is to the right of the ghost
        } else {
            step = -1; // Pacman is to the left of the ghost
        }
        for (int x = ghost_x + step; x != pacman_x; x += step) {
            if (is_wall(ghost_y, x)) {
                return SEES_NOTHING;
            }
        }
        if (step == 1) {
            return RIGHT;
        } else {
            return LEFT;
        }
    }

    return SEES_NOTHING;
}

char moveGhost(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    char direction = sees_pacman(pacman_y, pacman_x, ghost_y, ghost_x);

    // Based on the direction, the ghost will make a decision
    // For the sake of this example, we just return the direction seen
    // In a real game, additional logic would be used to handle movement and strategy
    return direction;
}