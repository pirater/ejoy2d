#ifndef EJOY_2D_SPRITE_PACK_H
#define EJOY_2D_SPRITE_PACK_H

#include <lua.h>
#include <stdint.h>

#define TYPE_EMPTY 0
#define TYPE_PICTURE 1
#define TYPE_ANIMATION 2
#define TYPE_POLYGON 3
#define TYPE_LABEL 4
#define TYPE_PANNEL 5
#define TYPE_ANCHOR 6

#define ANCHOR_ID 0xffff
#define SCREEN_SCALE 16

// binary package should reserve more bytes for 64bit platform
#define PTR_SIZE_DIFF (8 - sizeof(void *))
#define SIZEOF_POINTER 8

struct matrix;

#define SIZEOF_MATRIX (sizeof(struct matrix))

struct pack_pannel {
	int width;
	int height;
	int scissor;
};

#define SIZEOF_PANNEL (sizeof(struct pack_pannel))

struct pack_label {
	uint32_t color;
	int width;
	int height;
	int align;
	int size;
	int edge;
	int max_width;
};

#define SIZEOF_LABEL (sizeof(struct pack_label))

struct pack_quad {
	int texid;
	uint16_t texture_coord[8];
	int32_t screen_coord[8];
};

#define SIZEOF_QUAD (sizeof(struct pack_quad))

struct pack_picture {
	int n;
	struct pack_quad rect[1];
};

#define SIZEOF_PICTURE (sizeof(struct pack_picture) - SIZEOF_QUAD)

struct pack_poly {
	int texid;
	int n;
	uint16_t *texture_coord;
	int32_t *screen_coord;
};

#define SIZEOF_POLY (sizeof(struct pack_poly) + 2 * PTR_SIZE_DIFF)

struct pack_polygon {
	int n;
	struct pack_poly poly[1];
};

#define SIZEOF_POLYGON (sizeof(struct pack_polygon) - SIZEOF_POLY)

struct sprite_trans {
	struct matrix * mat;
	uint32_t color;
	uint32_t additive;
	int program;
};

#define SIZEOF_TRANS (sizeof(struct sprite_trans) * PTR_SIZE_DIFF)

struct pack_part {
	int component_id;
	struct sprite_trans t;
	int touchable;
};

#define SIZEOF_PART (sizeof(struct pack_part))

struct pack_frame {
	int n;
	struct pack_part *part;
};

#define SIZEOF_FRAME (sizeof(struct pack_frame) + PTR_SIZE_DIFF)

struct pack_action {
	const char * name;
	int number;
	int start_frame;
};

#define SIZEOF_ACTION (sizeof(struct pack_action) + PTR_SIZE_DIFF)

struct pack_component {
	int id;
	const char *name;
};

#define SIZEOF_COMPONENT (sizeof(struct pack_component) + PTR_SIZE_DIFF)

struct pack_animation {
	int frame_number;
	int action_number;
	int component_number;
	struct pack_frame *frame;
	struct pack_action *action;
	struct pack_component component[1];
};

#define SIZEOF_ANIMATION (sizeof(struct pack_animation) + 2 * PTR_SIZE_DIFF - SIZEOF_COMPONENT)

struct sprite_pack {
	int n;
	uint8_t * type;
	void ** data;
	int tex[1];
};

#define SIZEOF_PACK (sizeof(struct sprite_pack) + 2 * PTR_SIZE_DIFF - sizeof(int))

int ejoy2d_spritepack(lua_State *L);
void dump_pack(struct sprite_pack *pack);

#endif
