#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    // Update the paths with the correct file locations
    string backgroundPath = "C:\\Users\\jones\\Downloads\\images1\\backgrounds\\winter.png";
    string foregroundPath = "C:\\Users\\jones\\Downloads\\images1\\characters\\yoda.png";

    // Load background image
    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(backgroundPath)) {
        cout << "Couldn't Load Background Image" << endl;
        exit(1);
    }

    // Load foreground image
    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foregroundPath)) {
        cout << "Couldn't Load Foreground Image" << endl;
        exit(1);
    }

    // Create Image objects for background and foreground
    Image backgroundImage = backgroundTex.copyToImage();
    Image foregroundImage = foregroundTex.copyToImage();

    // Get the size of the images
    Vector2u sz = backgroundImage.getSize();

    // Perform green-screen compositing
    for (int y = 0; y < sz.y; y++) {
        for (int x = 0; x < sz.x; x++) {
            // Get the pixel color from the foreground image
            Color foregroundPixel = foregroundImage.getPixel(x, y);

            // Check if the pixel is green (adjust thresholds as needed)
            if (foregroundPixel.g > 100 && foregroundPixel.r < 50 && foregroundPixel.b < 50) {
                // Replace green pixel with corresponding pixel from the background image
                foregroundPixel = backgroundImage.getPixel(x, y);
            }

            // Set the resulting pixel color to the foreground image
            foregroundImage.setPixel(x, y, foregroundPixel);
        }
    }

    // Display the resulting image
    RenderWindow window(VideoMode(sz.x, sz.y), "Green-Screen Compositing");
    Texture resultTex;
    resultTex.loadFromImage(foregroundImage);
    Sprite resultSprite(resultTex);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(resultSprite);
        window.display();
    }

    return 0;
}
