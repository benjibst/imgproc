#include <stdio.h>
#include <raylib.h>
#define SIZE 7
int main()
{
    int width,height,channels;
    bool new_image = false;
    bool image = false;
    Image img = {0};
    Texture texture = {0};
    InitWindow(800, 600, "Hello, World!");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsFileDropped()){
            FilePathList files = LoadDroppedFiles();
            char* file1 = files.paths[0];
            stbi_uc *data = stbi_load(file1, &width, &height, &channels,0);
            if(data){
                Image imgnew = {data, width, height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8};
                image = true;
                printf("Loaded image: %s\n", file1);
                printf("Image size: %d x %d\n", imgnew.width, imgnew.height);
                if (img.data != NULL){
                    UnloadImage(img);
                    printf("Releasing previous image\n");
                }
                new_image = true;
                img = imgnew;
            }
            UnloadDroppedFiles(files);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(image){
            if(new_image){
                texture = LoadTextureFromImage(img);
                new_image = false;
            }
            DrawTexture(texture, 0, 0, WHITE);
        }
        EndDrawing();
    }
    printf("Hello, World!\n");
    return 0;
}
