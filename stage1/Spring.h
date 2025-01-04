#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "player.h"
#include "timer.h"
#include <vector>


struct Spring {
    float k;            // Σταθερά ελατηρίου (spring constant)
    float rest_length;  // Φυσικό μήκος του ελατηρίου
    float damping;      // Απόσβεση (damping coefficient)

    // Constructor
    Spring(float k_, float rest_length_, float damping_)
        : k(k_), rest_length(rest_length_), damping(damping_) {}

    // Υπολογισμός της δύναμης του ελατηρίου
    vector<float> calculateForce(float attach_point_x,float attach_point_y, float position_point_x,float position_point_y, const float velocity=1.0f) const {  //F = -k*x
        // Διαφορά θέσης (vector από το σημείο σύνδεσης μέχρι τη θέση του αντικειμένου)
        float delta_x = attach_point_x- position_point_x;
        float delta_y = attach_point_y - position_point_y;

        // Απόσταση από το φυσικό μήκος
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);       //x = distance the spring has been deformed from its natural position


        float dir_x,dir_y;
        // Κατεύθυνση της δύναμης (μονάδα διάνυσμα)
        if (distance > 0)
        {
            float dir_x = delta_x / distance;
            float dir_y = delta_y / distance;
        }
        else
            float dir_x, dir_y = 0.0f;

        // Δύναμη από το ελατήριο
        float spring_force_x = -k * (distance - rest_length) * dir_x;
        float spring_force_y = -k * (distance - rest_length) * dir_y;


        // Απόσβεση (damping force)
        float damping_force_x = -damping * velocity;
        float damping_force_y = -damping * velocity;

        // Τελικές δυνάμεις
        std::vector<float> result;
        float result_x = spring_force_x + damping_force_x;
        result.push_back(result_x);
        float result_y = spring_force_y + damping_force_y;
        result.push_back(result_y);

        return result;
    }
};
