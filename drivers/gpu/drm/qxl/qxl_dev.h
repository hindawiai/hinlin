<शैली गुरु>
/*
   Copyright (C) 2009 Red Hat, Inc.

   Redistribution and use in source and binary क्रमms, with or without
   modअगरication, are permitted provided that the following conditions are
   met:

       * Redistributions of source code must retain the above copyright
	 notice, this list of conditions and the following disclaimer.
       * Redistributions in binary क्रमm must reproduce the above copyright
	 notice, this list of conditions and the following disclaimer in
	 the करोcumentation and/or other materials provided with the
	 distribution.
       * Neither the name of the copyright holder nor the names of its
	 contributors may be used to enकरोrse or promote products derived
	 from this software without specअगरic prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#अगर_अघोषित H_QXL_DEV
#घोषणा H_QXL_DEV

#समावेश <linux/types.h>

/*
 * from spice-protocol
 * Release 0.10.0
 */

/* क्रमागतs.h */

क्रमागत SpiceImageType अणु
	SPICE_IMAGE_TYPE_BITMAP,
	SPICE_IMAGE_TYPE_QUIC,
	SPICE_IMAGE_TYPE_RESERVED,
	SPICE_IMAGE_TYPE_LZ_PLT = 100,
	SPICE_IMAGE_TYPE_LZ_RGB,
	SPICE_IMAGE_TYPE_GLZ_RGB,
	SPICE_IMAGE_TYPE_FROM_CACHE,
	SPICE_IMAGE_TYPE_SURFACE,
	SPICE_IMAGE_TYPE_JPEG,
	SPICE_IMAGE_TYPE_FROM_CACHE_LOSSLESS,
	SPICE_IMAGE_TYPE_ZLIB_GLZ_RGB,
	SPICE_IMAGE_TYPE_JPEG_ALPHA,

	SPICE_IMAGE_TYPE_ENUM_END
पूर्ण;

क्रमागत SpiceBiपंचांगapFmt अणु
	SPICE_BITMAP_FMT_INVALID,
	SPICE_BITMAP_FMT_1BIT_LE,
	SPICE_BITMAP_FMT_1BIT_BE,
	SPICE_BITMAP_FMT_4BIT_LE,
	SPICE_BITMAP_FMT_4BIT_BE,
	SPICE_BITMAP_FMT_8BIT,
	SPICE_BITMAP_FMT_16BIT,
	SPICE_BITMAP_FMT_24BIT,
	SPICE_BITMAP_FMT_32BIT,
	SPICE_BITMAP_FMT_RGBA,

	SPICE_BITMAP_FMT_ENUM_END
पूर्ण;

क्रमागत SpiceSurfaceFmt अणु
	SPICE_SURFACE_FMT_INVALID,
	SPICE_SURFACE_FMT_1_A,
	SPICE_SURFACE_FMT_8_A = 8,
	SPICE_SURFACE_FMT_16_555 = 16,
	SPICE_SURFACE_FMT_32_xRGB = 32,
	SPICE_SURFACE_FMT_16_565 = 80,
	SPICE_SURFACE_FMT_32_ARGB = 96,

	SPICE_SURFACE_FMT_ENUM_END
पूर्ण;

क्रमागत SpiceClipType अणु
	SPICE_CLIP_TYPE_NONE,
	SPICE_CLIP_TYPE_RECTS,

	SPICE_CLIP_TYPE_ENUM_END
पूर्ण;

क्रमागत SpiceRopd अणु
	SPICE_ROPD_INVERS_SRC = (1 << 0),
	SPICE_ROPD_INVERS_BRUSH = (1 << 1),
	SPICE_ROPD_INVERS_DEST = (1 << 2),
	SPICE_ROPD_OP_PUT = (1 << 3),
	SPICE_ROPD_OP_OR = (1 << 4),
	SPICE_ROPD_OP_AND = (1 << 5),
	SPICE_ROPD_OP_XOR = (1 << 6),
	SPICE_ROPD_OP_BLACKNESS = (1 << 7),
	SPICE_ROPD_OP_WHITENESS = (1 << 8),
	SPICE_ROPD_OP_INVERS = (1 << 9),
	SPICE_ROPD_INVERS_RES = (1 << 10),

	SPICE_ROPD_MASK = 0x7ff
पूर्ण;

क्रमागत SpiceBrushType अणु
	SPICE_BRUSH_TYPE_NONE,
	SPICE_BRUSH_TYPE_SOLID,
	SPICE_BRUSH_TYPE_PATTERN,

	SPICE_BRUSH_TYPE_ENUM_END
पूर्ण;

क्रमागत SpiceCursorType अणु
	SPICE_CURSOR_TYPE_ALPHA,
	SPICE_CURSOR_TYPE_MONO,
	SPICE_CURSOR_TYPE_COLOR4,
	SPICE_CURSOR_TYPE_COLOR8,
	SPICE_CURSOR_TYPE_COLOR16,
	SPICE_CURSOR_TYPE_COLOR24,
	SPICE_CURSOR_TYPE_COLOR32,

	SPICE_CURSOR_TYPE_ENUM_END
पूर्ण;

/* qxl_dev.h */

#आशय pack(push, 1)

/* 0x100-0x11f reserved क्रम spice, 0x1ff used क्रम unstable work */
#घोषणा QXL_DEVICE_ID_STABLE 0x0100

क्रमागत अणु
	QXL_REVISION_STABLE_V04 = 0x01,
	QXL_REVISION_STABLE_V06 = 0x02,
	QXL_REVISION_STABLE_V10 = 0x03,
	QXL_REVISION_STABLE_V12 = 0x04,
पूर्ण;

#घोषणा QXL_DEVICE_ID_DEVEL 0x01ff
#घोषणा QXL_REVISION_DEVEL 0x01

#घोषणा QXL_ROM_MAGIC (*(uपूर्णांक32_t *)"QXRO")
#घोषणा QXL_RAM_MAGIC (*(uपूर्णांक32_t *)"QXRA")

क्रमागत अणु
	QXL_RAM_RANGE_INDEX,
	QXL_VRAM_RANGE_INDEX,
	QXL_ROM_RANGE_INDEX,
	QXL_IO_RANGE_INDEX,

	QXL_PCI_RANGES
पूर्ण;

/* qxl-1 compat: append only */
क्रमागत अणु
	QXL_IO_NOTIFY_CMD,
	QXL_IO_NOTIFY_CURSOR,
	QXL_IO_UPDATE_AREA,
	QXL_IO_UPDATE_IRQ,
	QXL_IO_NOTIFY_OOM,
	QXL_IO_RESET,
	QXL_IO_SET_MODE,                  /* qxl-1 */
	QXL_IO_LOG,
	/* appended क्रम qxl-2 */
	QXL_IO_MEMSLOT_ADD,
	QXL_IO_MEMSLOT_DEL,
	QXL_IO_DETACH_PRIMARY,
	QXL_IO_ATTACH_PRIMARY,
	QXL_IO_CREATE_PRIMARY,
	QXL_IO_DESTROY_PRIMARY,
	QXL_IO_DESTROY_SURFACE_WAIT,
	QXL_IO_DESTROY_ALL_SURFACES,
	/* appended क्रम qxl-3 */
	QXL_IO_UPDATE_AREA_ASYNC,
	QXL_IO_MEMSLOT_ADD_ASYNC,
	QXL_IO_CREATE_PRIMARY_ASYNC,
	QXL_IO_DESTROY_PRIMARY_ASYNC,
	QXL_IO_DESTROY_SURFACE_ASYNC,
	QXL_IO_DESTROY_ALL_SURFACES_ASYNC,
	QXL_IO_FLUSH_SURFACES_ASYNC,
	QXL_IO_FLUSH_RELEASE,
	/* appended क्रम qxl-4 */
	QXL_IO_MONITORS_CONFIG_ASYNC,

	QXL_IO_RANGE_SIZE
पूर्ण;

प्रकार uपूर्णांक64_t QXLPHYSICAL;
प्रकार पूर्णांक32_t QXLFIXED; /* fixed 28.4 */

काष्ठा qxl_poपूर्णांक_fix अणु
	QXLFIXED x;
	QXLFIXED y;
पूर्ण;

काष्ठा qxl_poपूर्णांक अणु
	पूर्णांक32_t x;
	पूर्णांक32_t y;
पूर्ण;

काष्ठा qxl_poपूर्णांक_1_6 अणु
	पूर्णांक16_t x;
	पूर्णांक16_t y;
पूर्ण;

काष्ठा qxl_rect अणु
	पूर्णांक32_t top;
	पूर्णांक32_t left;
	पूर्णांक32_t bottom;
	पूर्णांक32_t right;
पूर्ण;

काष्ठा qxl_urect अणु
	uपूर्णांक32_t top;
	uपूर्णांक32_t left;
	uपूर्णांक32_t bottom;
	uपूर्णांक32_t right;
पूर्ण;

/* qxl-1 compat: append only */
काष्ठा qxl_rom अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t id;
	uपूर्णांक32_t update_id;
	uपूर्णांक32_t compression_level;
	uपूर्णांक32_t log_level;
	uपूर्णांक32_t mode;			  /* qxl-1 */
	uपूर्णांक32_t modes_offset;
	uपूर्णांक32_t num_io_pages;
	uपूर्णांक32_t pages_offset;		  /* qxl-1 */
	uपूर्णांक32_t draw_area_offset;	  /* qxl-1 */
	uपूर्णांक32_t surface0_area_size;	  /* qxl-1 name: draw_area_size */
	uपूर्णांक32_t ram_header_offset;
	uपूर्णांक32_t mm_घड़ी;
	/* appended क्रम qxl-2 */
	uपूर्णांक32_t n_surfaces;
	uपूर्णांक64_t flags;
	uपूर्णांक8_t slots_start;
	uपूर्णांक8_t slots_end;
	uपूर्णांक8_t slot_gen_bits;
	uपूर्णांक8_t slot_id_bits;
	uपूर्णांक8_t slot_generation;
	/* appended क्रम qxl-4 */
	uपूर्णांक8_t client_present;
	uपूर्णांक8_t client_capabilities[58];
	uपूर्णांक32_t client_monitors_config_crc;
	काष्ठा अणु
		uपूर्णांक16_t count;
	uपूर्णांक16_t padding;
		काष्ठा qxl_urect heads[64];
	पूर्ण client_monitors_config;
पूर्ण;

/* qxl-1 compat: fixed */
काष्ठा qxl_mode अणु
	uपूर्णांक32_t id;
	uपूर्णांक32_t x_res;
	uपूर्णांक32_t y_res;
	uपूर्णांक32_t bits;
	uपूर्णांक32_t stride;
	uपूर्णांक32_t x_mili;
	uपूर्णांक32_t y_mili;
	uपूर्णांक32_t orientation;
पूर्ण;

/* qxl-1 compat: fixed */
काष्ठा qxl_modes अणु
	uपूर्णांक32_t n_modes;
	काष्ठा qxl_mode modes[];
पूर्ण;

/* qxl-1 compat: append only */
क्रमागत qxl_cmd_type अणु
	QXL_CMD_NOP,
	QXL_CMD_DRAW,
	QXL_CMD_UPDATE,
	QXL_CMD_CURSOR,
	QXL_CMD_MESSAGE,
	QXL_CMD_SURFACE,
पूर्ण;

/* qxl-1 compat: fixed */
काष्ठा qxl_command अणु
	QXLPHYSICAL data;
	uपूर्णांक32_t type;
	uपूर्णांक32_t padding;
पूर्ण;

#घोषणा QXL_COMMAND_FLAG_COMPAT		(1<<0)
#घोषणा QXL_COMMAND_FLAG_COMPAT_16BPP	(2<<0)

काष्ठा qxl_command_ext अणु
	काष्ठा qxl_command cmd;
	uपूर्णांक32_t group_id;
	uपूर्णांक32_t flags;
पूर्ण;

काष्ठा qxl_mem_slot अणु
	uपूर्णांक64_t mem_start;
	uपूर्णांक64_t mem_end;
पूर्ण;

#घोषणा QXL_SURF_TYPE_PRIMARY	   0

#घोषणा QXL_SURF_FLAG_KEEP_DATA	   (1 << 0)

काष्ठा qxl_surface_create अणु
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	पूर्णांक32_t stride;
	uपूर्णांक32_t क्रमmat;
	uपूर्णांक32_t position;
	uपूर्णांक32_t mouse_mode;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t type;
	QXLPHYSICAL mem;
पूर्ण;

#घोषणा QXL_COMMAND_RING_SIZE 32
#घोषणा QXL_CURSOR_RING_SIZE 32
#घोषणा QXL_RELEASE_RING_SIZE 8

#घोषणा QXL_LOG_BUF_SIZE 4096

#घोषणा QXL_INTERRUPT_DISPLAY (1 << 0)
#घोषणा QXL_INTERRUPT_CURSOR (1 << 1)
#घोषणा QXL_INTERRUPT_IO_CMD (1 << 2)
#घोषणा QXL_INTERRUPT_ERROR  (1 << 3)
#घोषणा QXL_INTERRUPT_CLIENT (1 << 4)
#घोषणा QXL_INTERRUPT_CLIENT_MONITORS_CONFIG  (1 << 5)

काष्ठा qxl_ring_header अणु
	uपूर्णांक32_t num_items;
	uपूर्णांक32_t prod;
	uपूर्णांक32_t notअगरy_on_prod;
	uपूर्णांक32_t cons;
	uपूर्णांक32_t notअगरy_on_cons;
पूर्ण;

/* qxl-1 compat: append only */
काष्ठा qxl_ram_header अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t पूर्णांक_pending;
	uपूर्णांक32_t पूर्णांक_mask;
	uपूर्णांक8_t log_buf[QXL_LOG_BUF_SIZE];
	काष्ठा qxl_ring_header  cmd_ring_hdr;
	काष्ठा qxl_command	cmd_ring[QXL_COMMAND_RING_SIZE];
	काष्ठा qxl_ring_header  cursor_ring_hdr;
	काष्ठा qxl_command	cursor_ring[QXL_CURSOR_RING_SIZE];
	काष्ठा qxl_ring_header  release_ring_hdr;
	uपूर्णांक64_t		release_ring[QXL_RELEASE_RING_SIZE];
	काष्ठा qxl_rect update_area;
	/* appended क्रम qxl-2 */
	uपूर्णांक32_t update_surface;
	काष्ठा qxl_mem_slot mem_slot;
	काष्ठा qxl_surface_create create_surface;
	uपूर्णांक64_t flags;

	/* appended क्रम qxl-4 */

	/* used by QXL_IO_MONITORS_CONFIG_ASYNC */
	QXLPHYSICAL monitors_config;
	uपूर्णांक8_t guest_capabilities[64];
पूर्ण;

जोड़ qxl_release_info अणु
	uपूर्णांक64_t id;	  /* in  */
	uपूर्णांक64_t next;	  /* out */
पूर्ण;

काष्ठा qxl_release_info_ext अणु
	जोड़ qxl_release_info *info;
	uपूर्णांक32_t group_id;
पूर्ण;

काष्ठा qxl_data_chunk अणु
	uपूर्णांक32_t data_size;
	QXLPHYSICAL prev_chunk;
	QXLPHYSICAL next_chunk;
	uपूर्णांक8_t data[];
पूर्ण;

काष्ठा qxl_message अणु
	जोड़ qxl_release_info release_info;
	uपूर्णांक8_t data[];
पूर्ण;

काष्ठा qxl_compat_update_cmd अणु
	जोड़ qxl_release_info release_info;
	काष्ठा qxl_rect area;
	uपूर्णांक32_t update_id;
पूर्ण;

काष्ठा qxl_update_cmd अणु
	जोड़ qxl_release_info release_info;
	काष्ठा qxl_rect area;
	uपूर्णांक32_t update_id;
	uपूर्णांक32_t surface_id;
पूर्ण;

काष्ठा qxl_cursor_header अणु
	uपूर्णांक64_t unique;
	uपूर्णांक16_t type;
	uपूर्णांक16_t width;
	uपूर्णांक16_t height;
	uपूर्णांक16_t hot_spot_x;
	uपूर्णांक16_t hot_spot_y;
पूर्ण;

काष्ठा qxl_cursor अणु
	काष्ठा qxl_cursor_header header;
	uपूर्णांक32_t data_size;
	काष्ठा qxl_data_chunk chunk;
पूर्ण;

क्रमागत अणु
	QXL_CURSOR_SET,
	QXL_CURSOR_MOVE,
	QXL_CURSOR_HIDE,
	QXL_CURSOR_TRAIL,
पूर्ण;

#घोषणा QXL_CURSOR_DEVICE_DATA_SIZE 128

काष्ठा qxl_cursor_cmd अणु
	जोड़ qxl_release_info release_info;
	uपूर्णांक8_t type;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा qxl_poपूर्णांक_1_6 position;
			uपूर्णांक8_t visible;
			QXLPHYSICAL shape;
		पूर्ण set;
		काष्ठा अणु
			uपूर्णांक16_t length;
			uपूर्णांक16_t frequency;
		पूर्ण trail;
		काष्ठा qxl_poपूर्णांक_1_6 position;
	पूर्ण u;
	/* toकरो: dynamic size from rom */
	uपूर्णांक8_t device_data[QXL_CURSOR_DEVICE_DATA_SIZE];
पूर्ण;

क्रमागत अणु
	QXL_DRAW_NOP,
	QXL_DRAW_FILL,
	QXL_DRAW_OPAQUE,
	QXL_DRAW_COPY,
	QXL_COPY_BITS,
	QXL_DRAW_BLEND,
	QXL_DRAW_BLACKNESS,
	QXL_DRAW_WHITENESS,
	QXL_DRAW_INVERS,
	QXL_DRAW_ROP3,
	QXL_DRAW_STROKE,
	QXL_DRAW_TEXT,
	QXL_DRAW_TRANSPARENT,
	QXL_DRAW_ALPHA_BLEND,
	QXL_DRAW_COMPOSITE
पूर्ण;

काष्ठा qxl_raster_glyph अणु
	काष्ठा qxl_poपूर्णांक render_pos;
	काष्ठा qxl_poपूर्णांक glyph_origin;
	uपूर्णांक16_t width;
	uपूर्णांक16_t height;
	uपूर्णांक8_t data[];
पूर्ण;

काष्ठा qxl_string अणु
	uपूर्णांक32_t data_size;
	uपूर्णांक16_t length;
	uपूर्णांक16_t flags;
	काष्ठा qxl_data_chunk chunk;
पूर्ण;

काष्ठा qxl_copy_bits अणु
	काष्ठा qxl_poपूर्णांक src_pos;
पूर्ण;

क्रमागत qxl_effect_type अणु
	QXL_EFFECT_BLEND = 0,
	QXL_EFFECT_OPAQUE = 1,
	QXL_EFFECT_REVERT_ON_DUP = 2,
	QXL_EFFECT_BLACKNESS_ON_DUP = 3,
	QXL_EFFECT_WHITENESS_ON_DUP = 4,
	QXL_EFFECT_NOP_ON_DUP = 5,
	QXL_EFFECT_NOP = 6,
	QXL_EFFECT_OPAQUE_BRUSH = 7
पूर्ण;

काष्ठा qxl_pattern अणु
	QXLPHYSICAL pat;
	काष्ठा qxl_poपूर्णांक pos;
पूर्ण;

काष्ठा qxl_brush अणु
	uपूर्णांक32_t type;
	जोड़ अणु
		uपूर्णांक32_t color;
		काष्ठा qxl_pattern pattern;
	पूर्ण u;
पूर्ण;

काष्ठा qxl_q_mask अणु
	uपूर्णांक8_t flags;
	काष्ठा qxl_poपूर्णांक pos;
	QXLPHYSICAL biपंचांगap;
पूर्ण;

काष्ठा qxl_fill अणु
	काष्ठा qxl_brush brush;
	uपूर्णांक16_t rop_descriptor;
	काष्ठा qxl_q_mask mask;
पूर्ण;

काष्ठा qxl_opaque अणु
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
	काष्ठा qxl_brush brush;
	uपूर्णांक16_t rop_descriptor;
	uपूर्णांक8_t scale_mode;
	काष्ठा qxl_q_mask mask;
पूर्ण;

काष्ठा qxl_copy अणु
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
	uपूर्णांक16_t rop_descriptor;
	uपूर्णांक8_t scale_mode;
	काष्ठा qxl_q_mask mask;
पूर्ण;

काष्ठा qxl_transparent अणु
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
	uपूर्णांक32_t src_color;
	uपूर्णांक32_t true_color;
पूर्ण;

काष्ठा qxl_alpha_blend अणु
	uपूर्णांक16_t alpha_flags;
	uपूर्णांक8_t alpha;
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
पूर्ण;

काष्ठा qxl_compat_alpha_blend अणु
	uपूर्णांक8_t alpha;
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
पूर्ण;

काष्ठा qxl_rop_3 अणु
	QXLPHYSICAL src_biपंचांगap;
	काष्ठा qxl_rect src_area;
	काष्ठा qxl_brush brush;
	uपूर्णांक8_t rop3;
	uपूर्णांक8_t scale_mode;
	काष्ठा qxl_q_mask mask;
पूर्ण;

काष्ठा qxl_line_attr अणु
	uपूर्णांक8_t flags;
	uपूर्णांक8_t join_style;
	uपूर्णांक8_t end_style;
	uपूर्णांक8_t style_nseg;
	QXLFIXED width;
	QXLFIXED miter_limit;
	QXLPHYSICAL style;
पूर्ण;

काष्ठा qxl_stroke अणु
	QXLPHYSICAL path;
	काष्ठा qxl_line_attr attr;
	काष्ठा qxl_brush brush;
	uपूर्णांक16_t क्रमe_mode;
	uपूर्णांक16_t back_mode;
पूर्ण;

काष्ठा qxl_text अणु
	QXLPHYSICAL str;
	काष्ठा qxl_rect back_area;
	काष्ठा qxl_brush क्रमe_brush;
	काष्ठा qxl_brush back_brush;
	uपूर्णांक16_t क्रमe_mode;
	uपूर्णांक16_t back_mode;
पूर्ण;

काष्ठा qxl_mask अणु
	काष्ठा qxl_q_mask mask;
पूर्ण;

काष्ठा qxl_clip अणु
	uपूर्णांक32_t type;
	QXLPHYSICAL data;
पूर्ण;

क्रमागत qxl_चालक अणु
	QXL_OP_CLEAR			 = 0x00,
	QXL_OP_SOURCE			 = 0x01,
	QXL_OP_DST			 = 0x02,
	QXL_OP_OVER			 = 0x03,
	QXL_OP_OVER_REVERSE		 = 0x04,
	QXL_OP_IN			 = 0x05,
	QXL_OP_IN_REVERSE		 = 0x06,
	QXL_OP_OUT			 = 0x07,
	QXL_OP_OUT_REVERSE		 = 0x08,
	QXL_OP_ATOP			 = 0x09,
	QXL_OP_ATOP_REVERSE		 = 0x0a,
	QXL_OP_XOR			 = 0x0b,
	QXL_OP_ADD			 = 0x0c,
	QXL_OP_SATURATE			 = 0x0d,
	/* Note the jump here from 0x0d to 0x30 */
	QXL_OP_MULTIPLY			 = 0x30,
	QXL_OP_SCREEN			 = 0x31,
	QXL_OP_OVERLAY			 = 0x32,
	QXL_OP_DARKEN			 = 0x33,
	QXL_OP_LIGHTEN			 = 0x34,
	QXL_OP_COLOR_DODGE		 = 0x35,
	QXL_OP_COLOR_BURN		 = 0x36,
	QXL_OP_HARD_LIGHT		 = 0x37,
	QXL_OP_SOFT_LIGHT		 = 0x38,
	QXL_OP_DIFFERENCE		 = 0x39,
	QXL_OP_EXCLUSION		 = 0x3a,
	QXL_OP_HSL_HUE			 = 0x3b,
	QXL_OP_HSL_SATURATION		 = 0x3c,
	QXL_OP_HSL_COLOR		 = 0x3d,
	QXL_OP_HSL_LUMINOSITY		 = 0x3e
पूर्ण;

काष्ठा qxl_transक्रमm अणु
	uपूर्णांक32_t	t00;
	uपूर्णांक32_t	t01;
	uपूर्णांक32_t	t02;
	uपूर्णांक32_t	t10;
	uपूर्णांक32_t	t11;
	uपूर्णांक32_t	t12;
पूर्ण;

/* The flags field has the following bit fields:
 *
 *     चालक:		[  0 -  7 ]
 *     src_filter:		[  8 - 10 ]
 *     mask_filter:		[ 11 - 13 ]
 *     src_repeat:		[ 14 - 15 ]
 *     mask_repeat:		[ 16 - 17 ]
 *     component_alpha:		[ 18 - 18 ]
 *     reserved:		[ 19 - 31 ]
 *
 * The repeat and filter values are those of pixman:
 *		REPEAT_NONE =		0
 *              REPEAT_NORMAL =		1
 *		REPEAT_PAD =		2
 *		REPEAT_REFLECT =	3
 *
 * The filter values are:
 *		FILTER_NEAREST =	0
 *		FILTER_BILINEAR	=	1
 */
काष्ठा qxl_composite अणु
	uपूर्णांक32_t		flags;

	QXLPHYSICAL			src;
	QXLPHYSICAL			src_transक्रमm;	/* May be शून्य */
	QXLPHYSICAL			mask;		/* May be शून्य */
	QXLPHYSICAL			mask_transक्रमm;	/* May be शून्य */
	काष्ठा qxl_poपूर्णांक_1_6	src_origin;
	काष्ठा qxl_poपूर्णांक_1_6	mask_origin;
पूर्ण;

काष्ठा qxl_compat_drawable अणु
	जोड़ qxl_release_info release_info;
	uपूर्णांक8_t effect;
	uपूर्णांक8_t type;
	uपूर्णांक16_t biपंचांगap_offset;
	काष्ठा qxl_rect biपंचांगap_area;
	काष्ठा qxl_rect bbox;
	काष्ठा qxl_clip clip;
	uपूर्णांक32_t mm_समय;
	जोड़ अणु
		काष्ठा qxl_fill fill;
		काष्ठा qxl_opaque opaque;
		काष्ठा qxl_copy copy;
		काष्ठा qxl_transparent transparent;
		काष्ठा qxl_compat_alpha_blend alpha_blend;
		काष्ठा qxl_copy_bits copy_bits;
		काष्ठा qxl_copy blend;
		काष्ठा qxl_rop_3 rop3;
		काष्ठा qxl_stroke stroke;
		काष्ठा qxl_text text;
		काष्ठा qxl_mask blackness;
		काष्ठा qxl_mask invers;
		काष्ठा qxl_mask whiteness;
	पूर्ण u;
पूर्ण;

काष्ठा qxl_drawable अणु
	जोड़ qxl_release_info release_info;
	uपूर्णांक32_t surface_id;
	uपूर्णांक8_t effect;
	uपूर्णांक8_t type;
	uपूर्णांक8_t self_biपंचांगap;
	काष्ठा qxl_rect self_biपंचांगap_area;
	काष्ठा qxl_rect bbox;
	काष्ठा qxl_clip clip;
	uपूर्णांक32_t mm_समय;
	पूर्णांक32_t surfaces_dest[3];
	काष्ठा qxl_rect surfaces_rects[3];
	जोड़ अणु
		काष्ठा qxl_fill fill;
		काष्ठा qxl_opaque opaque;
		काष्ठा qxl_copy copy;
		काष्ठा qxl_transparent transparent;
		काष्ठा qxl_alpha_blend alpha_blend;
		काष्ठा qxl_copy_bits copy_bits;
		काष्ठा qxl_copy blend;
		काष्ठा qxl_rop_3 rop3;
		काष्ठा qxl_stroke stroke;
		काष्ठा qxl_text text;
		काष्ठा qxl_mask blackness;
		काष्ठा qxl_mask invers;
		काष्ठा qxl_mask whiteness;
		काष्ठा qxl_composite composite;
	पूर्ण u;
पूर्ण;

क्रमागत qxl_surface_cmd_type अणु
	QXL_SURFACE_CMD_CREATE,
	QXL_SURFACE_CMD_DESTROY,
पूर्ण;

काष्ठा qxl_surface अणु
	uपूर्णांक32_t क्रमmat;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	पूर्णांक32_t stride;
	QXLPHYSICAL data;
पूर्ण;

काष्ठा qxl_surface_cmd अणु
	जोड़ qxl_release_info release_info;
	uपूर्णांक32_t surface_id;
	uपूर्णांक8_t type;
	uपूर्णांक32_t flags;
	जोड़ अणु
		काष्ठा qxl_surface surface_create;
	पूर्ण u;
पूर्ण;

काष्ठा qxl_clip_rects अणु
	uपूर्णांक32_t num_rects;
	काष्ठा qxl_data_chunk chunk;
पूर्ण;

क्रमागत अणु
	QXL_PATH_BEGIN = (1 << 0),
	QXL_PATH_END = (1 << 1),
	QXL_PATH_CLOSE = (1 << 3),
	QXL_PATH_BEZIER = (1 << 4),
पूर्ण;

काष्ठा qxl_path_seg अणु
	uपूर्णांक32_t flags;
	uपूर्णांक32_t count;
	काष्ठा qxl_poपूर्णांक_fix poपूर्णांकs[];
पूर्ण;

काष्ठा qxl_path अणु
	uपूर्णांक32_t data_size;
	काष्ठा qxl_data_chunk chunk;
पूर्ण;

क्रमागत अणु
	QXL_IMAGE_GROUP_DRIVER,
	QXL_IMAGE_GROUP_DEVICE,
	QXL_IMAGE_GROUP_RED,
	QXL_IMAGE_GROUP_DRIVER_DONT_CACHE,
पूर्ण;

काष्ठा qxl_image_id अणु
	uपूर्णांक32_t group;
	uपूर्णांक32_t unique;
पूर्ण;

जोड़ qxl_image_id_जोड़ अणु
	काष्ठा qxl_image_id id;
	uपूर्णांक64_t value;
पूर्ण;

क्रमागत qxl_image_flags अणु
	QXL_IMAGE_CACHE = (1 << 0),
	QXL_IMAGE_HIGH_BITS_SET = (1 << 1),
पूर्ण;

क्रमागत qxl_biपंचांगap_flags अणु
	QXL_BITMAP_सूचीECT = (1 << 0),
	QXL_BITMAP_UNSTABLE = (1 << 1),
	QXL_BITMAP_TOP_DOWN = (1 << 2), /* == SPICE_BITMAP_FLAGS_TOP_DOWN */
पूर्ण;

#घोषणा QXL_SET_IMAGE_ID(image, _group, _unique) अणु              \
	(image)->descriptor.id = (((uपूर्णांक64_t)_unique) << 32) | _group;	\
पूर्ण

काष्ठा qxl_image_descriptor अणु
	uपूर्णांक64_t id;
	uपूर्णांक8_t type;
	uपूर्णांक8_t flags;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
पूर्ण;

काष्ठा qxl_palette अणु
	uपूर्णांक64_t unique;
	uपूर्णांक16_t num_ents;
	uपूर्णांक32_t ents[];
पूर्ण;

काष्ठा qxl_biपंचांगap अणु
	uपूर्णांक8_t क्रमmat;
	uपूर्णांक8_t flags;
	uपूर्णांक32_t x;
	uपूर्णांक32_t y;
	uपूर्णांक32_t stride;
	QXLPHYSICAL palette;
	QXLPHYSICAL data; /* data[0] ? */
पूर्ण;

काष्ठा qxl_surface_id अणु
	uपूर्णांक32_t surface_id;
पूर्ण;

काष्ठा qxl_encoder_data अणु
	uपूर्णांक32_t data_size;
	uपूर्णांक8_t data[];
पूर्ण;

काष्ठा qxl_image अणु
	काष्ठा qxl_image_descriptor descriptor;
	जोड़ अणु /* variable length */
		काष्ठा qxl_biपंचांगap biपंचांगap;
		काष्ठा qxl_encoder_data quic;
		काष्ठा qxl_surface_id surface_image;
	पूर्ण u;
पूर्ण;

/* A QXLHead is a single monitor output backed by a QXLSurface.
 * x and y offsets are अचिन्हित since they are used in relation to
 * the given surface, not the same as the x, y coordinates in the guest
 * screen reference frame. */
काष्ठा qxl_head अणु
	uपूर्णांक32_t id;
	uपूर्णांक32_t surface_id;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t x;
	uपूर्णांक32_t y;
	uपूर्णांक32_t flags;
पूर्ण;

काष्ठा qxl_monitors_config अणु
	uपूर्णांक16_t count;
	uपूर्णांक16_t max_allowed; /* If it is 0 no fixed limit is given by the
				 driver */
	काष्ठा qxl_head heads[];
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर /* _H_QXL_DEV */
