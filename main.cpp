#include <string>
#include <iostream>
#include <vector>
#include "video_proc.hpp"

using namespace std;

void nextImage(string path) {
    OpenPPMFile(path);
}

vector<bool> getRed() {
    vector<bool> output;
    output.reserve(320 * 220);

    for (int x=0; x<320; x++) {
        for (int y=0; y<220; y++) {
            Pixel pixel = get_pixel(y, x);

            float red = (float) pixel.red;
            float green = (float) pixel.green;
            float blue = (float) pixel.blue;
            
            float redness = red / (red + green + blue);
            output.push_back(redness > 0.6);
        }
    }

    return output;
}

float isSimilar(vector<bool> red1, vector<bool> red2) {
    float similar = 0;

    for (int i=0; i<red1.size(); i++) {
        if (red1[i] == red2[i])
            similar += 1;
    }

    return similar / (320 * 220) > 0.93;
}

bool isRubyPresent(vector<bool> redScale) {
    float totalRed = 0;
    for (int i=0; i<redScale.size(); i++) {
        if (redScale[i])
            totalRed += 1;
    }

    return totalRed / (320 * 220) > 0.001;
}

int main() {
    string base = "./Images/Core/";
    cout << base << endl;

    nextImage(base + "0.ppm");
    vector<bool> original = getRed();

    if (!isRubyPresent(original)) {
        cout << "Ruby missing! Not continuing." << endl;
        return 0;
    }

    cout << "Ruby is present" << endl;

    for (int i=1; i<20; i++) {
        nextImage(base + to_string(i) + ".ppm");
        vector<bool> current = getRed();

        cout << "#" << i << endl;

        if (!isRubyPresent(current)) {
            cout << "Ruby is missing! Not continuing." << endl;
            return 0;
        }

        if (!isSimilar(original, current)) {
            cout << "Don't steal my ruby!" << endl;
            return 0;
        }
    }

    return 0;
}
