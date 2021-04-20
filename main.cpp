#include <string>
#include <iostream>
#include <vector>
#include "E101.h"

using namespace std;

void nextImage() {
    take_picture();
	update_screen();
}

vector<bool> getRed() {
    vector<bool> output;
    output.reserve(320 * 220);

    for (int x=0; x<320; x++) {
        for (int y=0; y<220; y++) {
            //Pixel pixel = get_pixel(y, x);

            float red = (float) get_pixel(y, x, 0);
            float green = (float) get_pixel(y, x, 1);
            float blue = (float) get_pixel(y, x, 2);
            
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

void setupConnection() {
    int err = init(0);
    cout<<" Starting. err="<<err<<endl;
    open_screen_stream();
}

int main() {
    vector<bool> original;
    vector<bool> current;

    // setup
    setupConnection();
    nextImage();
    original = getRed();

    // check ruby is initially present
    if (!isRubyPresent(original)) {
        cout << "Ruby missing! Find the ruby and restart." << endl;
        return 0;
    }

    cout << "Ruby is present" << endl;

    // now start ruby watching loop
    while (true) {
        nextImage();
        current = getRed();

        if (!isRubyPresent(current)) {
            cout << "Ruby is missing!" << endl;
            break;
        }

        if (!isSimilar(original, current)) {
            cout << "Don't steal my ruby!" << endl;
            break;
        }

        sleep1(100);
    }

    close_screen_stream();
    return 0;
}
