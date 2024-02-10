#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define ZDX_GAP_BUFFER_IMPLEMENTATION
#include "./src/zdx_gap_buffer.h"

int main(void)
{
  const uint16_t width = 800, height = 640;

  gb_t gb = {0};
  gb_insert_cstr(&gb, "This is a test using Fira Code Regular TTF coming from a gap buffer!");

  InitWindow(width, height, "Eddy");
  SetTargetFPS(60);

  Font fira_ttf = LoadFontEx("resources/firacode.ttf", 18, NULL, 250);
  SetTextLineSpacing(48);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x282c34ff));
    DrawTextEx(fira_ttf,
               gb_buf_as_cstr(&gb),
               (Vector2){ 10.0f, 20.0f } ,
               (float)fira_ttf.baseSize, 2.0f, WHITE);
    EndDrawing();
  }

  UnloadFont(fira_ttf);
  CloseWindow();

  return 0;
}
