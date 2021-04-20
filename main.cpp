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
    int cropX = 50;
    int cropY = 50;

    vector<bool> output;
    output.reserve((320 - cropX * 2) * (220 - cropY * 2));

    for (int x=cropX; x<320-cropX; x+=5) {
        for (int y=cropY; y<220-cropY; y+=5) {
            float red = (float) get_pixel(y, x, 0);
            float green = (float) get_pixel(y, x, 1);
            float blue = (float) get_pixel(y, x, 2);
            
            float redness = red / (red + green + blue);
            output.push_back(redness > 0.6);
        }
    }

    return output;
}

float isSimilar(vector<bool> image1, vector<bool> image2) {
    float similar = 0;

    for (int i=0; i<image1.size(); i++) {
        if (image1[i] == image2[i])
            similar += 1;
    }

    return similar / image1.size() > 0.90;
}

bool isRubyPresent(vector<bool> image) {
    float totalRed = 0;
    for (int i=0; i<image.size(); i++) {
        if (image[i])
            totalRed += 1;
    }

    return totalRed / image.size() > 0.001;
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
    }

    close_screen_stream();
    return 0;
}
