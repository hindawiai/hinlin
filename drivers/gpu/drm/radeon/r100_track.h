<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

#समावेश "radeon.h"

#घोषणा R100_TRACK_MAX_TEXTURE 3
#घोषणा R200_TRACK_MAX_TEXTURE 6
#घोषणा R300_TRACK_MAX_TEXTURE 16

#घोषणा R100_MAX_CB 1
#घोषणा R300_MAX_CB 4

/*
 * CS functions
 */
काष्ठा r100_cs_track_cb अणु
	काष्ठा radeon_bo	*robj;
	अचिन्हित		pitch;
	अचिन्हित		cpp;
	अचिन्हित		offset;
पूर्ण;

काष्ठा r100_cs_track_array अणु
	काष्ठा radeon_bo	*robj;
	अचिन्हित		esize;
पूर्ण;

काष्ठा r100_cs_cube_info अणु
	काष्ठा radeon_bo	*robj;
	अचिन्हित		offset;
	अचिन्हित		width;
	अचिन्हित		height;
पूर्ण;

#घोषणा R100_TRACK_COMP_NONE   0
#घोषणा R100_TRACK_COMP_DXT1   1
#घोषणा R100_TRACK_COMP_DXT35  2

काष्ठा r100_cs_track_texture अणु
	काष्ठा radeon_bo	*robj;
	काष्ठा r100_cs_cube_info cube_info[5]; /* info क्रम 5 non-primary faces */
	अचिन्हित		pitch;
	अचिन्हित		width;
	अचिन्हित		height;
	अचिन्हित		num_levels;
	अचिन्हित		cpp;
	अचिन्हित		tex_coord_type;
	अचिन्हित		txdepth;
	अचिन्हित		width_11;
	अचिन्हित		height_11;
	bool			use_pitch;
	bool			enabled;
	bool                    lookup_disable;
	bool			roundup_w;
	bool			roundup_h;
	अचिन्हित                compress_क्रमmat;
पूर्ण;

काष्ठा r100_cs_track अणु
	अचिन्हित			num_cb;
	अचिन्हित                        num_texture;
	अचिन्हित			maxy;
	अचिन्हित			vtx_size;
	अचिन्हित			vap_vf_cntl;
	अचिन्हित			vap_alt_nverts;
	अचिन्हित			immd_dwords;
	अचिन्हित			num_arrays;
	अचिन्हित			max_indx;
	अचिन्हित			color_channel_mask;
	काष्ठा r100_cs_track_array	arrays[16];
	काष्ठा r100_cs_track_cb 	cb[R300_MAX_CB];
	काष्ठा r100_cs_track_cb 	zb;
	काष्ठा r100_cs_track_cb 	aa;
	काष्ठा r100_cs_track_texture	textures[R300_TRACK_MAX_TEXTURE];
	bool				z_enabled;
	bool                            separate_cube;
	bool				zb_cb_clear;
	bool				blend_पढ़ो_enable;
	bool				cb_dirty;
	bool				zb_dirty;
	bool				tex_dirty;
	bool				aa_dirty;
	bool				aaresolve;
पूर्ण;

पूर्णांक r100_cs_track_check(काष्ठा radeon_device *rdev, काष्ठा r100_cs_track *track);
व्योम r100_cs_track_clear(काष्ठा radeon_device *rdev, काष्ठा r100_cs_track *track);

पूर्णांक r100_cs_packet_parse_vline(काष्ठा radeon_cs_parser *p);

पूर्णांक r200_packet0_check(काष्ठा radeon_cs_parser *p,
		       काष्ठा radeon_cs_packet *pkt,
		       अचिन्हित idx, अचिन्हित reg);

पूर्णांक r100_reloc_pitch_offset(काष्ठा radeon_cs_parser *p,
			    काष्ठा radeon_cs_packet *pkt,
			    अचिन्हित idx,
			    अचिन्हित reg);
पूर्णांक r100_packet3_load_vbpntr(काष्ठा radeon_cs_parser *p,
			     काष्ठा radeon_cs_packet *pkt,
			     पूर्णांक idx);
