#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

bool isNight = false;
float birdOffset = 0.0f; // ›ﬁÿ ··ÿÌÊ— «·„ Õ—ﬂ…

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        isNight = !isNight;
    }
}

// œ«·… ·—”„ œ«∆—…
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * std::cos(theta);
        float y = r * std::sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// —”„ „À·À (·Ã»«· √Ê ÿÌÊ—)
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// —”„ „” ÿÌ· (··√—÷Ì… √Ê «·€ÌÊ„)
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Day/Night Scene with Birds", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //  ÕœÌÀ „Êﬁ⁄ «·ÿÌÊ— »Õ—ﬂ… »ÿÌ∆… Ãœ«
        birdOffset += 0.0008f; // «·¬‰ √»ÿ√ „‰ ﬁ»·
        if (birdOffset > 2.0f) birdOffset = -2.0f;

        // ·Ê‰ «·”„«¡ Õ”» «·Êﬁ 
        if (isNight) {
            glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // ·Ì·
        }
        else {
            glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // ‰Â«—
        }

        // —”„ «·√—÷
        glColor3f(0.1f, 0.6f, 0.1f);
        drawRectangle(-1.0f, -1.0f, 2.0f, 0.4f);

        // —”„ Ã»«·
        glColor3f(0.2f, 0.3f, 0.2f);
        drawTriangle(-1.0f, -0.6f, -0.5f, -0.6f, -0.75f, 0.0f);
        drawTriangle(-0.6f, -0.6f, 0.0f, -0.6f, -0.3f, 0.1f);
        drawTriangle(0.1f, -0.6f, 0.6f, -0.6f, 0.35f, 0.15f);

        // «·‘„” √Ê «·ﬁ„— À«» Ì‰
        float sunX = 0.7f;
        float sunY = 0.7f;
        if (isNight) {
            glColor3f(1.0f, 1.0f, 0.8f); // «·ﬁ„—
        }
        else {
            glColor3f(1.0f, 1.0f, 0.0f); // «·‘„”
        }
        drawCircle(sunX, sunY, 0.08f, 50);

        // —”„ «·€ÌÊ„ «·À«» … »«·‰Â«—
        if (!isNight) {
            glColor3f(1.0f, 1.0f, 1.0f);
            drawCircle(-0.5f, 0.8f, 0.1f, 30);
            drawCircle(-0.4f, 0.82f, 0.12f, 30);
            drawCircle(0.3f, 0.75f, 0.08f, 30);
            drawCircle(0.4f, 0.78f, 0.1f, 30);
        }

        // —”„ ‰ÃÊ„ »«··Ì·
        if (isNight) {
            glColor3f(1.0f, 1.0f, 1.0f);
            for (int i = 0; i < 20; i++) {
                float x = -1.0f + 2.0f * ((i * 7 % 20) / 20.0f);
                float y = 0.2f + 0.8f * ((i * 3 % 10) / 10.0f);
                drawCircle(x, y, 0.01f, 10);
            }
        }

        // —”„ ⁄’«›Ì— „ Õ—ﬂ… »«·‰Â«— »”—⁄… √»ÿ√ Ãœ«
        if (!isNight) {
            glColor3f(0.0f, 0.0f, 0.0f);
            // ÿ«∆— 1
            drawTriangle(-0.6f + birdOffset, 0.6f, -0.58f + birdOffset, 0.62f, -0.55f + birdOffset, 0.6f);
            // ÿ«∆— 2
            drawTriangle(-0.4f + birdOffset, 0.65f, -0.38f + birdOffset, 0.67f, -0.35f + birdOffset, 0.65f);
            // ÿ«∆— 3
            drawTriangle(-0.2f + birdOffset, 0.62f, -0.18f + birdOffset, 0.64f, -0.15f + birdOffset, 0.62f);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}