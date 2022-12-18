BUILD_DIR=build

include $(N64_INST)/include/n64.mk

src = $(wildcard ./*.c) \
	  $(wildcard ../../libdragon-extensions/src/*.c)

assets_xm = $(wildcard assets/*.xm)
assets_wav = $(wildcard assets/*.wav)
assets_png = $(wildcard assets/*.png)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_xm:%.xm=%.xm64))) \
              $(addprefix filesystem/,$(notdir $(assets_wav:%.wav=%.wav64))) \
              $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(wildcard filesystem/*)

AUDIOCONV_FLAGS ?=
MKSPRITE_FLAGS ?=

CFLAGS += -I../../libdragon-extensions/

all: opengl_tilemap_test_1.z64

filesystem/%.xm64: assets/%.xm
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o filesystem $<

filesystem/%.wav64: assets/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) -o filesystem $<

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/tileset.sprite: MKSPRITE_FLAGS=--format RGBA16 --tiles 16,16
filesystem/tileset_CI4.sprite: MKSPRITE_FLAGS=--format CI4 --tiles 16,16

$(BUILD_DIR)/opengl_tilemap_test_1.dfs: $(assets_conv)
$(BUILD_DIR)/opengl_tilemap_test_1.elf: $(src:%.c=$(BUILD_DIR)/%.o)

opengl_tilemap_test_1.z64: N64_ROM_TITLE="OpenGL Branch Tilemap Test 1"
opengl_tilemap_test_1.z64: $(BUILD_DIR)/opengl_tilemap_test_1.dfs 

clean:
	rm -rf $(BUILD_DIR) opengl_tilemap_test_1.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean