#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "raylib.h"

#define ZDX_GAP_BUFFER_IMPLEMENTATION
#include "./src/zdx_gap_buffer.h"
#define ZDX_FILE_IMPLEMENTATION
#include "./src/zdx_file.h"

int main(void)
{
  const uint16_t width = 1024, height = 780;
  const char* file_path = "tests/mocks/typescript.ts";
  const uint8_t file_path_len = strlen(file_path) + 1 + 7; /* for \0 as needed by snprintf + "Eddy - " */
  /**
   * this is a bad idea as anyone can open a ridiculously big filename
   * that may blow the stack but given PATH_MAX is smaller than 8mb,
   * we should be good in most cases. But really, don't allocate this
   * on stack jfc for proper non-demo version
   */
  char window_title[file_path_len];
  snprintf(window_title, file_path_len, "Eddy - %s", file_path);

  fl_content_t f = fl_read_file_str(file_path, "r");

  if (!f.is_valid) {
    log(L_ERROR, "File read failed: %s", f.err_msg);
    return 1;
  }

  gb_t gb = {0};
  gb_insert_buf(&gb, f.contents, f.size);
  fc_deinit(&f);
  gb_move_cursor(&gb, -10000);
  gb_insert_cstr(&gb, "OMGOMG\n");

  InitWindow(width, height, window_title);
  SetTargetFPS(60);

  Font fira_ttf = LoadFontEx("resources/firacode.ttf", 18, NULL, 250);
  SetTextLineSpacing(20);

  while (!WindowShouldClose()) {
    const char* gb_str = gb_buf_as_cstr(&gb);
    BeginDrawing();
    ClearBackground(GetColor(0x282c34ff));
    DrawTextEx(fira_ttf,
               gb_str,
               (Vector2){ 10.0f, 20.0f } ,
               (float)fira_ttf.baseSize, 2.0f, WHITE);
    EndDrawing();
    free((void *)gb_str);
  }

  UnloadFont(fira_ttf);
  CloseWindow();

  return 0;
}
