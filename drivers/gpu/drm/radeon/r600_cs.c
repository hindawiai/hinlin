<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#समावेश <linux/kernel.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "r600.h"
#समावेश "r600d.h"
#समावेश "r600_reg_safe.h"

अटल पूर्णांक r600_nomm;
बाह्य व्योम r600_cs_legacy_get_tiling_conf(काष्ठा drm_device *dev, u32 *npipes, u32 *nbanks, u32 *group_size);


काष्ठा r600_cs_track अणु
	/* configuration we mirror so that we use same code btw kms/ums */
	u32			group_size;
	u32			nbanks;
	u32			npipes;
	/* value we track */
	u32			sq_config;
	u32			log_nsamples;
	u32			nsamples;
	u32			cb_color_base_last[8];
	काष्ठा radeon_bo	*cb_color_bo[8];
	u64			cb_color_bo_mc[8];
	u64			cb_color_bo_offset[8];
	काष्ठा radeon_bo	*cb_color_frag_bo[8];
	u64			cb_color_frag_offset[8];
	काष्ठा radeon_bo	*cb_color_tile_bo[8];
	u64			cb_color_tile_offset[8];
	u32			cb_color_mask[8];
	u32			cb_color_info[8];
	u32			cb_color_view[8];
	u32			cb_color_size_idx[8]; /* unused */
	u32			cb_target_mask;
	u32			cb_shader_mask;  /* unused */
	bool			is_resolve;
	u32			cb_color_size[8];
	u32			vgt_strmout_en;
	u32			vgt_strmout_buffer_en;
	काष्ठा radeon_bo	*vgt_strmout_bo[4];
	u64			vgt_strmout_bo_mc[4]; /* unused */
	u32			vgt_strmout_bo_offset[4];
	u32			vgt_strmout_size[4];
	u32			db_depth_control;
	u32			db_depth_info;
	u32			db_depth_size_idx;
	u32			db_depth_view;
	u32			db_depth_size;
	u32			db_offset;
	काष्ठा radeon_bo	*db_bo;
	u64			db_bo_mc;
	bool			sx_misc_समाप्त_all_prims;
	bool			cb_dirty;
	bool			db_dirty;
	bool			streamout_dirty;
	काष्ठा radeon_bo	*htile_bo;
	u64			htile_offset;
	u32			htile_surface;
पूर्ण;

#घोषणा FMT_8_BIT(fmt, vc)   [fmt] = अणु 1, 1, 1, vc, CHIP_R600 पूर्ण
#घोषणा FMT_16_BIT(fmt, vc)  [fmt] = अणु 1, 1, 2, vc, CHIP_R600 पूर्ण
#घोषणा FMT_24_BIT(fmt)      [fmt] = अणु 1, 1, 4,  0, CHIP_R600 पूर्ण
#घोषणा FMT_32_BIT(fmt, vc)  [fmt] = अणु 1, 1, 4, vc, CHIP_R600 पूर्ण
#घोषणा FMT_48_BIT(fmt)      [fmt] = अणु 1, 1, 8,  0, CHIP_R600 पूर्ण
#घोषणा FMT_64_BIT(fmt, vc)  [fmt] = अणु 1, 1, 8, vc, CHIP_R600 पूर्ण
#घोषणा FMT_96_BIT(fmt)      [fmt] = अणु 1, 1, 12, 0, CHIP_R600 पूर्ण
#घोषणा FMT_128_BIT(fmt, vc) [fmt] = अणु 1, 1, 16,vc, CHIP_R600 पूर्ण

काष्ठा gpu_क्रमmats अणु
	अचिन्हित blockwidth;
	अचिन्हित blockheight;
	अचिन्हित blocksize;
	अचिन्हित valid_color;
	क्रमागत radeon_family min_family;
पूर्ण;

अटल स्थिर काष्ठा gpu_क्रमmats color_क्रमmats_table[] = अणु
	/* 8 bit */
	FMT_8_BIT(V_038004_COLOR_8, 1),
	FMT_8_BIT(V_038004_COLOR_4_4, 1),
	FMT_8_BIT(V_038004_COLOR_3_3_2, 1),
	FMT_8_BIT(V_038004_FMT_1, 0),

	/* 16-bit */
	FMT_16_BIT(V_038004_COLOR_16, 1),
	FMT_16_BIT(V_038004_COLOR_16_FLOAT, 1),
	FMT_16_BIT(V_038004_COLOR_8_8, 1),
	FMT_16_BIT(V_038004_COLOR_5_6_5, 1),
	FMT_16_BIT(V_038004_COLOR_6_5_5, 1),
	FMT_16_BIT(V_038004_COLOR_1_5_5_5, 1),
	FMT_16_BIT(V_038004_COLOR_4_4_4_4, 1),
	FMT_16_BIT(V_038004_COLOR_5_5_5_1, 1),

	/* 24-bit */
	FMT_24_BIT(V_038004_FMT_8_8_8),

	/* 32-bit */
	FMT_32_BIT(V_038004_COLOR_32, 1),
	FMT_32_BIT(V_038004_COLOR_32_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_16_16, 1),
	FMT_32_BIT(V_038004_COLOR_16_16_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_8_24, 1),
	FMT_32_BIT(V_038004_COLOR_8_24_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_24_8, 1),
	FMT_32_BIT(V_038004_COLOR_24_8_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_10_11_11, 1),
	FMT_32_BIT(V_038004_COLOR_10_11_11_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_11_11_10, 1),
	FMT_32_BIT(V_038004_COLOR_11_11_10_FLOAT, 1),
	FMT_32_BIT(V_038004_COLOR_2_10_10_10, 1),
	FMT_32_BIT(V_038004_COLOR_8_8_8_8, 1),
	FMT_32_BIT(V_038004_COLOR_10_10_10_2, 1),
	FMT_32_BIT(V_038004_FMT_5_9_9_9_SHAREDEXP, 0),
	FMT_32_BIT(V_038004_FMT_32_AS_8, 0),
	FMT_32_BIT(V_038004_FMT_32_AS_8_8, 0),

	/* 48-bit */
	FMT_48_BIT(V_038004_FMT_16_16_16),
	FMT_48_BIT(V_038004_FMT_16_16_16_FLOAT),

	/* 64-bit */
	FMT_64_BIT(V_038004_COLOR_X24_8_32_FLOAT, 1),
	FMT_64_BIT(V_038004_COLOR_32_32, 1),
	FMT_64_BIT(V_038004_COLOR_32_32_FLOAT, 1),
	FMT_64_BIT(V_038004_COLOR_16_16_16_16, 1),
	FMT_64_BIT(V_038004_COLOR_16_16_16_16_FLOAT, 1),

	FMT_96_BIT(V_038004_FMT_32_32_32),
	FMT_96_BIT(V_038004_FMT_32_32_32_FLOAT),

	/* 128-bit */
	FMT_128_BIT(V_038004_COLOR_32_32_32_32, 1),
	FMT_128_BIT(V_038004_COLOR_32_32_32_32_FLOAT, 1),

	[V_038004_FMT_GB_GR] = अणु 2, 1, 4, 0 पूर्ण,
	[V_038004_FMT_BG_RG] = अणु 2, 1, 4, 0 पूर्ण,

	/* block compressed क्रमmats */
	[V_038004_FMT_BC1] = अणु 4, 4, 8, 0 पूर्ण,
	[V_038004_FMT_BC2] = अणु 4, 4, 16, 0 पूर्ण,
	[V_038004_FMT_BC3] = अणु 4, 4, 16, 0 पूर्ण,
	[V_038004_FMT_BC4] = अणु 4, 4, 8, 0 पूर्ण,
	[V_038004_FMT_BC5] = अणु 4, 4, 16, 0पूर्ण,
	[V_038004_FMT_BC6] = अणु 4, 4, 16, 0, CHIP_CEDARपूर्ण, /* Evergreen-only */
	[V_038004_FMT_BC7] = अणु 4, 4, 16, 0, CHIP_CEDARपूर्ण, /* Evergreen-only */

	/* The other Evergreen क्रमmats */
	[V_038004_FMT_32_AS_32_32_32_32] = अणु 1, 1, 4, 0, CHIP_CEDARपूर्ण,
पूर्ण;

bool r600_fmt_is_valid_color(u32 क्रमmat)
अणु
	अगर (क्रमmat >= ARRAY_SIZE(color_क्रमmats_table))
		वापस false;

	अगर (color_क्रमmats_table[क्रमmat].valid_color)
		वापस true;

	वापस false;
पूर्ण

bool r600_fmt_is_valid_texture(u32 क्रमmat, क्रमागत radeon_family family)
अणु
	अगर (क्रमmat >= ARRAY_SIZE(color_क्रमmats_table))
		वापस false;

	अगर (family < color_क्रमmats_table[क्रमmat].min_family)
		वापस false;

	अगर (color_क्रमmats_table[क्रमmat].blockwidth > 0)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक r600_fmt_get_blocksize(u32 क्रमmat)
अणु
	अगर (क्रमmat >= ARRAY_SIZE(color_क्रमmats_table))
		वापस 0;

	वापस color_क्रमmats_table[क्रमmat].blocksize;
पूर्ण

पूर्णांक r600_fmt_get_nblocksx(u32 क्रमmat, u32 w)
अणु
	अचिन्हित bw;

	अगर (क्रमmat >= ARRAY_SIZE(color_क्रमmats_table))
		वापस 0;

	bw = color_क्रमmats_table[क्रमmat].blockwidth;
	अगर (bw == 0)
		वापस 0;

	वापस DIV_ROUND_UP(w, bw);
पूर्ण

पूर्णांक r600_fmt_get_nblocksy(u32 क्रमmat, u32 h)
अणु
	अचिन्हित bh;

	अगर (क्रमmat >= ARRAY_SIZE(color_क्रमmats_table))
		वापस 0;

	bh = color_क्रमmats_table[क्रमmat].blockheight;
	अगर (bh == 0)
		वापस 0;

	वापस DIV_ROUND_UP(h, bh);
पूर्ण

काष्ठा array_mode_checker अणु
	पूर्णांक array_mode;
	u32 group_size;
	u32 nbanks;
	u32 npipes;
	u32 nsamples;
	u32 blocksize;
पूर्ण;

/* वापसs alignment in pixels क्रम pitch/height/depth and bytes क्रम base */
अटल पूर्णांक r600_get_array_mode_alignment(काष्ठा array_mode_checker *values,
						u32 *pitch_align,
						u32 *height_align,
						u32 *depth_align,
						u64 *base_align)
अणु
	u32 tile_width = 8;
	u32 tile_height = 8;
	u32 macro_tile_width = values->nbanks;
	u32 macro_tile_height = values->npipes;
	u32 tile_bytes = tile_width * tile_height * values->blocksize * values->nsamples;
	u32 macro_tile_bytes = macro_tile_width * macro_tile_height * tile_bytes;

	चयन (values->array_mode) अणु
	हाल ARRAY_LINEAR_GENERAL:
		/* technically tile_width/_height क्रम pitch/height */
		*pitch_align = 1; /* tile_width */
		*height_align = 1; /* tile_height */
		*depth_align = 1;
		*base_align = 1;
		अवरोध;
	हाल ARRAY_LINEAR_ALIGNED:
		*pitch_align = max((u32)64, (u32)(values->group_size / values->blocksize));
		*height_align = 1;
		*depth_align = 1;
		*base_align = values->group_size;
		अवरोध;
	हाल ARRAY_1D_TILED_THIN1:
		*pitch_align = max((u32)tile_width,
				   (u32)(values->group_size /
					 (tile_height * values->blocksize * values->nsamples)));
		*height_align = tile_height;
		*depth_align = 1;
		*base_align = values->group_size;
		अवरोध;
	हाल ARRAY_2D_TILED_THIN1:
		*pitch_align = max((u32)macro_tile_width * tile_width,
				(u32)((values->group_size * values->nbanks) /
				(values->blocksize * values->nsamples * tile_width)));
		*height_align = macro_tile_height * tile_height;
		*depth_align = 1;
		*base_align = max(macro_tile_bytes,
				  (*pitch_align) * values->blocksize * (*height_align) * values->nsamples);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम r600_cs_track_init(काष्ठा r600_cs_track *track)
अणु
	पूर्णांक i;

	/* assume DX9 mode */
	track->sq_config = DX9_CONSTS;
	क्रम (i = 0; i < 8; i++) अणु
		track->cb_color_base_last[i] = 0;
		track->cb_color_size[i] = 0;
		track->cb_color_size_idx[i] = 0;
		track->cb_color_info[i] = 0;
		track->cb_color_view[i] = 0xFFFFFFFF;
		track->cb_color_bo[i] = शून्य;
		track->cb_color_bo_offset[i] = 0xFFFFFFFF;
		track->cb_color_bo_mc[i] = 0xFFFFFFFF;
		track->cb_color_frag_bo[i] = शून्य;
		track->cb_color_frag_offset[i] = 0xFFFFFFFF;
		track->cb_color_tile_bo[i] = शून्य;
		track->cb_color_tile_offset[i] = 0xFFFFFFFF;
		track->cb_color_mask[i] = 0xFFFFFFFF;
	पूर्ण
	track->is_resolve = false;
	track->nsamples = 16;
	track->log_nsamples = 4;
	track->cb_target_mask = 0xFFFFFFFF;
	track->cb_shader_mask = 0xFFFFFFFF;
	track->cb_dirty = true;
	track->db_bo = शून्य;
	track->db_bo_mc = 0xFFFFFFFF;
	/* assume the biggest क्रमmat and that htile is enabled */
	track->db_depth_info = 7 | (1 << 25);
	track->db_depth_view = 0xFFFFC000;
	track->db_depth_size = 0xFFFFFFFF;
	track->db_depth_size_idx = 0;
	track->db_depth_control = 0xFFFFFFFF;
	track->db_dirty = true;
	track->htile_bo = शून्य;
	track->htile_offset = 0xFFFFFFFF;
	track->htile_surface = 0;

	क्रम (i = 0; i < 4; i++) अणु
		track->vgt_strmout_size[i] = 0;
		track->vgt_strmout_bo[i] = शून्य;
		track->vgt_strmout_bo_offset[i] = 0xFFFFFFFF;
		track->vgt_strmout_bo_mc[i] = 0xFFFFFFFF;
	पूर्ण
	track->streamout_dirty = true;
	track->sx_misc_समाप्त_all_prims = false;
पूर्ण

अटल पूर्णांक r600_cs_track_validate_cb(काष्ठा radeon_cs_parser *p, पूर्णांक i)
अणु
	काष्ठा r600_cs_track *track = p->track;
	u32 slice_tile_max, पंचांगp;
	u32 height, height_align, pitch, pitch_align, depth_align;
	u64 base_offset, base_align;
	काष्ठा array_mode_checker array_check;
	अस्थिर u32 *ib = p->ib.ptr;
	अचिन्हित array_mode;
	u32 क्रमmat;
	/* When resolve is used, the second colorbuffer has always 1 sample. */
	अचिन्हित nsamples = track->is_resolve && i == 1 ? 1 : track->nsamples;

	क्रमmat = G_0280A0_FORMAT(track->cb_color_info[i]);
	अगर (!r600_fmt_is_valid_color(क्रमmat)) अणु
		dev_warn(p->dev, "%s:%d cb invalid format %d for %d (0x%08X)\n",
			 __func__, __LINE__, क्रमmat,
			i, track->cb_color_info[i]);
		वापस -EINVAL;
	पूर्ण
	/* pitch in pixels */
	pitch = (G_028060_PITCH_TILE_MAX(track->cb_color_size[i]) + 1) * 8;
	slice_tile_max = G_028060_SLICE_TILE_MAX(track->cb_color_size[i]) + 1;
	slice_tile_max *= 64;
	height = slice_tile_max / pitch;
	अगर (height > 8192)
		height = 8192;
	array_mode = G_0280A0_ARRAY_MODE(track->cb_color_info[i]);

	base_offset = track->cb_color_bo_mc[i] + track->cb_color_bo_offset[i];
	array_check.array_mode = array_mode;
	array_check.group_size = track->group_size;
	array_check.nbanks = track->nbanks;
	array_check.npipes = track->npipes;
	array_check.nsamples = nsamples;
	array_check.blocksize = r600_fmt_get_blocksize(क्रमmat);
	अगर (r600_get_array_mode_alignment(&array_check,
					  &pitch_align, &height_align, &depth_align, &base_align)) अणु
		dev_warn(p->dev, "%s invalid tiling %d for %d (0x%08X)\n", __func__,
			 G_0280A0_ARRAY_MODE(track->cb_color_info[i]), i,
			 track->cb_color_info[i]);
		वापस -EINVAL;
	पूर्ण
	चयन (array_mode) अणु
	हाल V_0280A0_ARRAY_LINEAR_GENERAL:
		अवरोध;
	हाल V_0280A0_ARRAY_LINEAR_ALIGNED:
		अवरोध;
	हाल V_0280A0_ARRAY_1D_TILED_THIN1:
		/* aव्योम अवरोधing userspace */
		अगर (height > 7)
			height &= ~0x7;
		अवरोध;
	हाल V_0280A0_ARRAY_2D_TILED_THIN1:
		अवरोध;
	शेष:
		dev_warn(p->dev, "%s invalid tiling %d for %d (0x%08X)\n", __func__,
			G_0280A0_ARRAY_MODE(track->cb_color_info[i]), i,
			track->cb_color_info[i]);
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(pitch, pitch_align)) अणु
		dev_warn(p->dev, "%s:%d cb pitch (%d, 0x%x, %d) invalid\n",
			 __func__, __LINE__, pitch, pitch_align, array_mode);
		वापस -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(height, height_align)) अणु
		dev_warn(p->dev, "%s:%d cb height (%d, 0x%x, %d) invalid\n",
			 __func__, __LINE__, height, height_align, array_mode);
		वापस -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(base_offset, base_align)) अणु
		dev_warn(p->dev, "%s offset[%d] 0x%llx 0x%llx, %d not aligned\n", __func__, i,
			 base_offset, base_align, array_mode);
		वापस -EINVAL;
	पूर्ण

	/* check offset */
	पंचांगp = r600_fmt_get_nblocksy(क्रमmat, height) * r600_fmt_get_nblocksx(क्रमmat, pitch) *
	      r600_fmt_get_blocksize(क्रमmat) * nsamples;
	चयन (array_mode) अणु
	शेष:
	हाल V_0280A0_ARRAY_LINEAR_GENERAL:
	हाल V_0280A0_ARRAY_LINEAR_ALIGNED:
		पंचांगp += track->cb_color_view[i] & 0xFF;
		अवरोध;
	हाल V_0280A0_ARRAY_1D_TILED_THIN1:
	हाल V_0280A0_ARRAY_2D_TILED_THIN1:
		पंचांगp += G_028080_SLICE_MAX(track->cb_color_view[i]) * पंचांगp;
		अवरोध;
	पूर्ण
	अगर ((पंचांगp + track->cb_color_bo_offset[i]) > radeon_bo_size(track->cb_color_bo[i])) अणु
		अगर (array_mode == V_0280A0_ARRAY_LINEAR_GENERAL) अणु
			/* the initial DDX करोes bad things with the CB size occasionally */
			/* it rounds up height too far क्रम slice tile max but the BO is smaller */
			/* r600c,g also seem to flush at bad बार in some apps resulting in
			 * bogus values here. So क्रम linear just allow anything to aव्योम अवरोधing
			 * broken userspace.
			 */
		पूर्ण अन्यथा अणु
			dev_warn(p->dev, "%s offset[%d] %d %llu %d %lu too big (%d %d) (%d %d %d)\n",
				 __func__, i, array_mode,
				 track->cb_color_bo_offset[i], पंचांगp,
				 radeon_bo_size(track->cb_color_bo[i]),
				 pitch, height, r600_fmt_get_nblocksx(क्रमmat, pitch),
				 r600_fmt_get_nblocksy(क्रमmat, height),
				 r600_fmt_get_blocksize(क्रमmat));
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* limit max tile */
	पंचांगp = (height * pitch) >> 6;
	अगर (पंचांगp < slice_tile_max)
		slice_tile_max = पंचांगp;
	पंचांगp = S_028060_PITCH_TILE_MAX((pitch / 8) - 1) |
		S_028060_SLICE_TILE_MAX(slice_tile_max - 1);
	ib[track->cb_color_size_idx[i]] = पंचांगp;

	/* FMASK/CMASK */
	चयन (G_0280A0_TILE_MODE(track->cb_color_info[i])) अणु
	हाल V_0280A0_TILE_DISABLE:
		अवरोध;
	हाल V_0280A0_FRAG_ENABLE:
		अगर (track->nsamples > 1) अणु
			uपूर्णांक32_t tile_max = G_028100_FMASK_TILE_MAX(track->cb_color_mask[i]);
			/* the tile size is 8x8, but the size is in units of bits.
			 * क्रम bytes, करो just * 8. */
			uपूर्णांक32_t bytes = track->nsamples * track->log_nsamples * 8 * (tile_max + 1);

			अगर (bytes + track->cb_color_frag_offset[i] >
			    radeon_bo_size(track->cb_color_frag_bo[i])) अणु
				dev_warn(p->dev, "%s FMASK_TILE_MAX too large "
					 "(tile_max=%u, bytes=%u, offset=%llu, bo_size=%lu)\n",
					 __func__, tile_max, bytes,
					 track->cb_color_frag_offset[i],
					 radeon_bo_size(track->cb_color_frag_bo[i]));
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		fallthrough;
	हाल V_0280A0_CLEAR_ENABLE:
	अणु
		uपूर्णांक32_t block_max = G_028100_CMASK_BLOCK_MAX(track->cb_color_mask[i]);
		/* One block = 128x128 pixels, one 8x8 tile has 4 bits..
		 * (128*128) / (8*8) / 2 = 128 bytes per block. */
		uपूर्णांक32_t bytes = (block_max + 1) * 128;

		अगर (bytes + track->cb_color_tile_offset[i] >
		    radeon_bo_size(track->cb_color_tile_bo[i])) अणु
			dev_warn(p->dev, "%s CMASK_BLOCK_MAX too large "
				 "(block_max=%u, bytes=%u, offset=%llu, bo_size=%lu)\n",
				 __func__, block_max, bytes,
				 track->cb_color_tile_offset[i],
				 radeon_bo_size(track->cb_color_tile_bo[i]));
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		dev_warn(p->dev, "%s invalid tile mode\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r600_cs_track_validate_db(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा r600_cs_track *track = p->track;
	u32 nviews, bpe, ntiles, slice_tile_max, पंचांगp;
	u32 height_align, pitch_align, depth_align;
	u32 pitch = 8192;
	u32 height = 8192;
	u64 base_offset, base_align;
	काष्ठा array_mode_checker array_check;
	पूर्णांक array_mode;
	अस्थिर u32 *ib = p->ib.ptr;


	अगर (track->db_bo == शून्य) अणु
		dev_warn(p->dev, "z/stencil with no depth buffer\n");
		वापस -EINVAL;
	पूर्ण
	चयन (G_028010_FORMAT(track->db_depth_info)) अणु
	हाल V_028010_DEPTH_16:
		bpe = 2;
		अवरोध;
	हाल V_028010_DEPTH_X8_24:
	हाल V_028010_DEPTH_8_24:
	हाल V_028010_DEPTH_X8_24_FLOAT:
	हाल V_028010_DEPTH_8_24_FLOAT:
	हाल V_028010_DEPTH_32_FLOAT:
		bpe = 4;
		अवरोध;
	हाल V_028010_DEPTH_X24_8_32_FLOAT:
		bpe = 8;
		अवरोध;
	शेष:
		dev_warn(p->dev, "z/stencil with invalid format %d\n", G_028010_FORMAT(track->db_depth_info));
		वापस -EINVAL;
	पूर्ण
	अगर ((track->db_depth_size & 0xFFFFFC00) == 0xFFFFFC00) अणु
		अगर (!track->db_depth_size_idx) अणु
			dev_warn(p->dev, "z/stencil buffer size not set\n");
			वापस -EINVAL;
		पूर्ण
		पंचांगp = radeon_bo_size(track->db_bo) - track->db_offset;
		पंचांगp = (पंचांगp / bpe) >> 6;
		अगर (!पंचांगp) अणु
			dev_warn(p->dev, "z/stencil buffer too small (0x%08X %d %d %ld)\n",
					track->db_depth_size, bpe, track->db_offset,
					radeon_bo_size(track->db_bo));
			वापस -EINVAL;
		पूर्ण
		ib[track->db_depth_size_idx] = S_028000_SLICE_TILE_MAX(पंचांगp - 1) | (track->db_depth_size & 0x3FF);
	पूर्ण अन्यथा अणु
		/* pitch in pixels */
		pitch = (G_028000_PITCH_TILE_MAX(track->db_depth_size) + 1) * 8;
		slice_tile_max = G_028000_SLICE_TILE_MAX(track->db_depth_size) + 1;
		slice_tile_max *= 64;
		height = slice_tile_max / pitch;
		अगर (height > 8192)
			height = 8192;
		base_offset = track->db_bo_mc + track->db_offset;
		array_mode = G_028010_ARRAY_MODE(track->db_depth_info);
		array_check.array_mode = array_mode;
		array_check.group_size = track->group_size;
		array_check.nbanks = track->nbanks;
		array_check.npipes = track->npipes;
		array_check.nsamples = track->nsamples;
		array_check.blocksize = bpe;
		अगर (r600_get_array_mode_alignment(&array_check,
					&pitch_align, &height_align, &depth_align, &base_align)) अणु
			dev_warn(p->dev, "%s invalid tiling %d (0x%08X)\n", __func__,
					G_028010_ARRAY_MODE(track->db_depth_info),
					track->db_depth_info);
			वापस -EINVAL;
		पूर्ण
		चयन (array_mode) अणु
		हाल V_028010_ARRAY_1D_TILED_THIN1:
			/* करोn't अवरोध userspace */
			height &= ~0x7;
			अवरोध;
		हाल V_028010_ARRAY_2D_TILED_THIN1:
			अवरोध;
		शेष:
			dev_warn(p->dev, "%s invalid tiling %d (0x%08X)\n", __func__,
					G_028010_ARRAY_MODE(track->db_depth_info),
					track->db_depth_info);
			वापस -EINVAL;
		पूर्ण

		अगर (!IS_ALIGNED(pitch, pitch_align)) अणु
			dev_warn(p->dev, "%s:%d db pitch (%d, 0x%x, %d) invalid\n",
					__func__, __LINE__, pitch, pitch_align, array_mode);
			वापस -EINVAL;
		पूर्ण
		अगर (!IS_ALIGNED(height, height_align)) अणु
			dev_warn(p->dev, "%s:%d db height (%d, 0x%x, %d) invalid\n",
					__func__, __LINE__, height, height_align, array_mode);
			वापस -EINVAL;
		पूर्ण
		अगर (!IS_ALIGNED(base_offset, base_align)) अणु
			dev_warn(p->dev, "%s offset 0x%llx, 0x%llx, %d not aligned\n", __func__,
					base_offset, base_align, array_mode);
			वापस -EINVAL;
		पूर्ण

		ntiles = G_028000_SLICE_TILE_MAX(track->db_depth_size) + 1;
		nviews = G_028004_SLICE_MAX(track->db_depth_view) + 1;
		पंचांगp = ntiles * bpe * 64 * nviews * track->nsamples;
		अगर ((पंचांगp + track->db_offset) > radeon_bo_size(track->db_bo)) अणु
			dev_warn(p->dev, "z/stencil buffer (%d) too small (0x%08X %d %d %d -> %u have %lu)\n",
					array_mode,
					track->db_depth_size, ntiles, nviews, bpe, पंचांगp + track->db_offset,
					radeon_bo_size(track->db_bo));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* hyperz */
	अगर (G_028010_TILE_SURFACE_ENABLE(track->db_depth_info)) अणु
		अचिन्हित दीर्घ size;
		अचिन्हित nbx, nby;

		अगर (track->htile_bo == शून्य) अणु
			dev_warn(p->dev, "%s:%d htile enabled without htile surface 0x%08x\n",
				 __func__, __LINE__, track->db_depth_info);
			वापस -EINVAL;
		पूर्ण
		अगर ((track->db_depth_size & 0xFFFFFC00) == 0xFFFFFC00) अणु
			dev_warn(p->dev, "%s:%d htile can't be enabled with bogus db_depth_size 0x%08x\n",
				 __func__, __LINE__, track->db_depth_size);
			वापस -EINVAL;
		पूर्ण

		nbx = pitch;
		nby = height;
		अगर (G_028D24_LINEAR(track->htile_surface)) अणु
			/* nbx must be 16 htiles aligned == 16 * 8 pixel aligned */
			nbx = round_up(nbx, 16 * 8);
			/* nby is npipes htiles aligned == npipes * 8 pixel aligned */
			nby = round_up(nby, track->npipes * 8);
		पूर्ण अन्यथा अणु
			/* always assume 8x8 htile */
			/* align is htile align * 8, htile align vary according to
			 * number of pipe and tile width and nby
			 */
			चयन (track->npipes) अणु
			हाल 8:
				/* HTILE_WIDTH = 8 & HTILE_HEIGHT = 8*/
				nbx = round_up(nbx, 64 * 8);
				nby = round_up(nby, 64 * 8);
				अवरोध;
			हाल 4:
				/* HTILE_WIDTH = 8 & HTILE_HEIGHT = 8*/
				nbx = round_up(nbx, 64 * 8);
				nby = round_up(nby, 32 * 8);
				अवरोध;
			हाल 2:
				/* HTILE_WIDTH = 8 & HTILE_HEIGHT = 8*/
				nbx = round_up(nbx, 32 * 8);
				nby = round_up(nby, 32 * 8);
				अवरोध;
			हाल 1:
				/* HTILE_WIDTH = 8 & HTILE_HEIGHT = 8*/
				nbx = round_up(nbx, 32 * 8);
				nby = round_up(nby, 16 * 8);
				अवरोध;
			शेष:
				dev_warn(p->dev, "%s:%d invalid num pipes %d\n",
					 __func__, __LINE__, track->npipes);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		/* compute number of htile */
		nbx = nbx >> 3;
		nby = nby >> 3;
		/* size must be aligned on npipes * 2K boundary */
		size = roundup(nbx * nby * 4, track->npipes * (2 << 10));
		size += track->htile_offset;

		अगर (size > radeon_bo_size(track->htile_bo)) अणु
			dev_warn(p->dev, "%s:%d htile surface too small %ld for %ld (%d %d)\n",
				 __func__, __LINE__, radeon_bo_size(track->htile_bo),
				 size, nbx, nby);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	track->db_dirty = false;
	वापस 0;
पूर्ण

अटल पूर्णांक r600_cs_track_check(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा r600_cs_track *track = p->track;
	u32 पंचांगp;
	पूर्णांक r, i;

	/* on legacy kernel we करोn't perक्रमm advanced check */
	अगर (p->rdev == शून्य)
		वापस 0;

	/* check streamout */
	अगर (track->streamout_dirty && track->vgt_strmout_en) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर (track->vgt_strmout_buffer_en & (1 << i)) अणु
				अगर (track->vgt_strmout_bo[i]) अणु
					u64 offset = (u64)track->vgt_strmout_bo_offset[i] +
						(u64)track->vgt_strmout_size[i];
					अगर (offset > radeon_bo_size(track->vgt_strmout_bo[i])) अणु
						DRM_ERROR("streamout %d bo too small: 0x%llx, 0x%lx\n",
							  i, offset,
							  radeon_bo_size(track->vgt_strmout_bo[i]));
						वापस -EINVAL;
					पूर्ण
				पूर्ण अन्यथा अणु
					dev_warn(p->dev, "No buffer for streamout %d\n", i);
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
		track->streamout_dirty = false;
	पूर्ण

	अगर (track->sx_misc_समाप्त_all_prims)
		वापस 0;

	/* check that we have a cb क्रम each enabled target, we करोn't check
	 * shader_mask because it seems mesa isn't always setting it :(
	 */
	अगर (track->cb_dirty) अणु
		पंचांगp = track->cb_target_mask;

		/* We must check both colorbuffers क्रम RESOLVE. */
		अगर (track->is_resolve) अणु
			पंचांगp |= 0xff;
		पूर्ण

		क्रम (i = 0; i < 8; i++) अणु
			u32 क्रमmat = G_0280A0_FORMAT(track->cb_color_info[i]);

			अगर (क्रमmat != V_0280A0_COLOR_INVALID &&
			    (पंचांगp >> (i * 4)) & 0xF) अणु
				/* at least one component is enabled */
				अगर (track->cb_color_bo[i] == शून्य) अणु
					dev_warn(p->dev, "%s:%d mask 0x%08X | 0x%08X no cb for %d\n",
						__func__, __LINE__, track->cb_target_mask, track->cb_shader_mask, i);
					वापस -EINVAL;
				पूर्ण
				/* perक्रमm reग_लिखो of CB_COLOR[0-7]_SIZE */
				r = r600_cs_track_validate_cb(p, i);
				अगर (r)
					वापस r;
			पूर्ण
		पूर्ण
		track->cb_dirty = false;
	पूर्ण

	/* Check depth buffer */
	अगर (track->db_dirty &&
	    G_028010_FORMAT(track->db_depth_info) != V_028010_DEPTH_INVALID &&
	    (G_028800_STENCIL_ENABLE(track->db_depth_control) ||
	     G_028800_Z_ENABLE(track->db_depth_control))) अणु
		r = r600_cs_track_validate_db(p);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * r600_cs_packet_parse_vline() - parse userspace VLINE packet
 * @p:		parser काष्ठाure holding parsing context.
 *
 * This is an R600-specअगरic function क्रम parsing VLINE packets.
 * Real work is करोne by r600_cs_common_vline_parse function.
 * Here we just set up ASIC-specअगरic रेजिस्टर table and call
 * the common implementation function.
 */
अटल पूर्णांक r600_cs_packet_parse_vline(काष्ठा radeon_cs_parser *p)
अणु
	अटल uपूर्णांक32_t vline_start_end[2] = अणुAVIVO_D1MODE_VLINE_START_END,
					      AVIVO_D2MODE_VLINE_START_ENDपूर्ण;
	अटल uपूर्णांक32_t vline_status[2] = अणुAVIVO_D1MODE_VLINE_STATUS,
					   AVIVO_D2MODE_VLINE_STATUSपूर्ण;

	वापस r600_cs_common_vline_parse(p, vline_start_end, vline_status);
पूर्ण

/**
 * r600_cs_common_vline_parse() - common vline parser
 * @p:			parser काष्ठाure holding parsing context.
 * @vline_start_end:    table of vline_start_end रेजिस्टरs
 * @vline_status:       table of vline_status रेजिस्टरs
 *
 * Userspace sends a special sequence क्रम VLINE रुकोs.
 * PACKET0 - VLINE_START_END + value
 * PACKET3 - WAIT_REG_MEM poll vline status reg
 * RELOC (P3) - crtc_id in reloc.
 *
 * This function parses this and relocates the VLINE START END
 * and WAIT_REG_MEM packets to the correct crtc.
 * It also detects a चयनed off crtc and nulls out the
 * रुको in that हाल. This function is common क्रम all ASICs that
 * are R600 and newer. The parsing algorithm is the same, and only
 * dअगरfers in which रेजिस्टरs are used.
 *
 * Caller is the ASIC-specअगरic function which passes the parser
 * context and ASIC-specअगरic रेजिस्टर table
 */
पूर्णांक r600_cs_common_vline_parse(काष्ठा radeon_cs_parser *p,
			       uपूर्णांक32_t *vline_start_end,
			       uपूर्णांक32_t *vline_status)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	काष्ठा radeon_cs_packet p3reloc, रुको_reg_mem;
	पूर्णांक crtc_id;
	पूर्णांक r;
	uपूर्णांक32_t header, h_idx, reg, रुको_reg_mem_info;
	अस्थिर uपूर्णांक32_t *ib;

	ib = p->ib.ptr;

	/* parse the WAIT_REG_MEM */
	r = radeon_cs_packet_parse(p, &रुको_reg_mem, p->idx);
	अगर (r)
		वापस r;

	/* check its a WAIT_REG_MEM */
	अगर (रुको_reg_mem.type != RADEON_PACKET_TYPE3 ||
	    रुको_reg_mem.opcode != PACKET3_WAIT_REG_MEM) अणु
		DRM_ERROR("vline wait missing WAIT_REG_MEM segment\n");
		वापस -EINVAL;
	पूर्ण

	रुको_reg_mem_info = radeon_get_ib_value(p, रुको_reg_mem.idx + 1);
	/* bit 4 is reg (0) or mem (1) */
	अगर (रुको_reg_mem_info & 0x10) अणु
		DRM_ERROR("vline WAIT_REG_MEM waiting on MEM instead of REG\n");
		वापस -EINVAL;
	पूर्ण
	/* bit 8 is me (0) or pfp (1) */
	अगर (रुको_reg_mem_info & 0x100) अणु
		DRM_ERROR("vline WAIT_REG_MEM waiting on PFP instead of ME\n");
		वापस -EINVAL;
	पूर्ण
	/* रुकोing क्रम value to be equal */
	अगर ((रुको_reg_mem_info & 0x7) != 0x3) अणु
		DRM_ERROR("vline WAIT_REG_MEM function not equal\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((radeon_get_ib_value(p, रुको_reg_mem.idx + 2) << 2) != vline_status[0]) अणु
		DRM_ERROR("vline WAIT_REG_MEM bad reg\n");
		वापस -EINVAL;
	पूर्ण

	अगर (radeon_get_ib_value(p, रुको_reg_mem.idx + 5) != RADEON_VLINE_STAT) अणु
		DRM_ERROR("vline WAIT_REG_MEM bad bit mask\n");
		वापस -EINVAL;
	पूर्ण

	/* jump over the NOP */
	r = radeon_cs_packet_parse(p, &p3reloc, p->idx + रुको_reg_mem.count + 2);
	अगर (r)
		वापस r;

	h_idx = p->idx - 2;
	p->idx += रुको_reg_mem.count + 2;
	p->idx += p3reloc.count + 2;

	header = radeon_get_ib_value(p, h_idx);
	crtc_id = radeon_get_ib_value(p, h_idx + 2 + 7 + 1);
	reg = R600_CP_PACKET0_GET_REG(header);

	crtc = drm_crtc_find(p->rdev->ddev, p->filp, crtc_id);
	अगर (!crtc) अणु
		DRM_ERROR("cannot find crtc %d\n", crtc_id);
		वापस -ENOENT;
	पूर्ण
	radeon_crtc = to_radeon_crtc(crtc);
	crtc_id = radeon_crtc->crtc_id;

	अगर (!crtc->enabled) अणु
		/* CRTC isn't enabled - we need to nop out the WAIT_REG_MEM */
		ib[h_idx + 2] = PACKET2(0);
		ib[h_idx + 3] = PACKET2(0);
		ib[h_idx + 4] = PACKET2(0);
		ib[h_idx + 5] = PACKET2(0);
		ib[h_idx + 6] = PACKET2(0);
		ib[h_idx + 7] = PACKET2(0);
		ib[h_idx + 8] = PACKET2(0);
	पूर्ण अन्यथा अगर (reg == vline_start_end[0]) अणु
		header &= ~R600_CP_PACKET0_REG_MASK;
		header |= vline_start_end[crtc_id] >> 2;
		ib[h_idx] = header;
		ib[h_idx + 4] = vline_status[crtc_id] >> 2;
	पूर्ण अन्यथा अणु
		DRM_ERROR("unknown crtc reloc\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r600_packet0_check(काष्ठा radeon_cs_parser *p,
				काष्ठा radeon_cs_packet *pkt,
				अचिन्हित idx, अचिन्हित reg)
अणु
	पूर्णांक r;

	चयन (reg) अणु
	हाल AVIVO_D1MODE_VLINE_START_END:
		r = r600_cs_packet_parse_vline(p);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			वापस r;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Forbidden register 0x%04X in cs at %d\n", reg, idx);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r600_cs_parse_packet0(काष्ठा radeon_cs_parser *p,
				काष्ठा radeon_cs_packet *pkt)
अणु
	अचिन्हित reg, i;
	अचिन्हित idx;
	पूर्णांक r;

	idx = pkt->idx + 1;
	reg = pkt->reg;
	क्रम (i = 0; i <= pkt->count; i++, idx++, reg += 4) अणु
		r = r600_packet0_check(p, pkt, idx, reg);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * r600_cs_check_reg() - check अगर रेजिस्टर is authorized or not
 * @p: parser काष्ठाure holding parsing context
 * @reg: रेजिस्टर we are testing
 * @idx: index पूर्णांकo the cs buffer
 *
 * This function will test against r600_reg_safe_bm and वापस 0
 * अगर रेजिस्टर is safe. If रेजिस्टर is not flag as safe this function
 * will test it against a list of रेजिस्टर needing special handling.
 */
अटल पूर्णांक r600_cs_check_reg(काष्ठा radeon_cs_parser *p, u32 reg, u32 idx)
अणु
	काष्ठा r600_cs_track *track = (काष्ठा r600_cs_track *)p->track;
	काष्ठा radeon_bo_list *reloc;
	u32 m, i, पंचांगp, *ib;
	पूर्णांक r;

	i = (reg >> 7);
	अगर (i >= ARRAY_SIZE(r600_reg_safe_bm)) अणु
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		वापस -EINVAL;
	पूर्ण
	m = 1 << ((reg >> 2) & 31);
	अगर (!(r600_reg_safe_bm[i] & m))
		वापस 0;
	ib = p->ib.ptr;
	चयन (reg) अणु
	/* क्रमce following reg to 0 in an attempt to disable out buffer
	 * which will need us to better understand how it works to perक्रमm
	 * security check on it (Jerome)
	 */
	हाल R_0288A8_SQ_ESGS_RING_ITEMSIZE:
	हाल R_008C44_SQ_ESGS_RING_SIZE:
	हाल R_0288B0_SQ_ESTMP_RING_ITEMSIZE:
	हाल R_008C54_SQ_ESTMP_RING_SIZE:
	हाल R_0288C0_SQ_FBUF_RING_ITEMSIZE:
	हाल R_008C74_SQ_FBUF_RING_SIZE:
	हाल R_0288B4_SQ_GSTMP_RING_ITEMSIZE:
	हाल R_008C5C_SQ_GSTMP_RING_SIZE:
	हाल R_0288AC_SQ_GSVS_RING_ITEMSIZE:
	हाल R_008C4C_SQ_GSVS_RING_SIZE:
	हाल R_0288BC_SQ_PSTMP_RING_ITEMSIZE:
	हाल R_008C6C_SQ_PSTMP_RING_SIZE:
	हाल R_0288C4_SQ_REDUC_RING_ITEMSIZE:
	हाल R_008C7C_SQ_REDUC_RING_SIZE:
	हाल R_0288B8_SQ_VSTMP_RING_ITEMSIZE:
	हाल R_008C64_SQ_VSTMP_RING_SIZE:
	हाल R_0288C8_SQ_GS_VERT_ITEMSIZE:
		/* get value to populate the IB करोn't हटाओ */
		/*पंचांगp =radeon_get_ib_value(p, idx);
		  ib[idx] = 0;*/
		अवरोध;
	हाल SQ_ESGS_RING_BASE:
	हाल SQ_GSVS_RING_BASE:
	हाल SQ_ESTMP_RING_BASE:
	हाल SQ_GSTMP_RING_BASE:
	हाल SQ_PSTMP_RING_BASE:
	हाल SQ_VSTMP_RING_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल SQ_CONFIG:
		track->sq_config = radeon_get_ib_value(p, idx);
		अवरोध;
	हाल R_028800_DB_DEPTH_CONTROL:
		track->db_depth_control = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल R_028010_DB_DEPTH_INFO:
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS) &&
		    radeon_cs_packet_next_is_pkt3_nop(p)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				dev_warn(p->dev, "bad SET_CONTEXT_REG "
					 "0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			track->db_depth_info = radeon_get_ib_value(p, idx);
			ib[idx] &= C_028010_ARRAY_MODE;
			track->db_depth_info &= C_028010_ARRAY_MODE;
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
				ib[idx] |= S_028010_ARRAY_MODE(V_028010_ARRAY_2D_TILED_THIN1);
				track->db_depth_info |= S_028010_ARRAY_MODE(V_028010_ARRAY_2D_TILED_THIN1);
			पूर्ण अन्यथा अणु
				ib[idx] |= S_028010_ARRAY_MODE(V_028010_ARRAY_1D_TILED_THIN1);
				track->db_depth_info |= S_028010_ARRAY_MODE(V_028010_ARRAY_1D_TILED_THIN1);
			पूर्ण
		पूर्ण अन्यथा अणु
			track->db_depth_info = radeon_get_ib_value(p, idx);
		पूर्ण
		track->db_dirty = true;
		अवरोध;
	हाल R_028004_DB_DEPTH_VIEW:
		track->db_depth_view = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल R_028000_DB_DEPTH_SIZE:
		track->db_depth_size = radeon_get_ib_value(p, idx);
		track->db_depth_size_idx = idx;
		track->db_dirty = true;
		अवरोध;
	हाल R_028AB0_VGT_STRMOUT_EN:
		track->vgt_strmout_en = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		अवरोध;
	हाल R_028B20_VGT_STRMOUT_BUFFER_EN:
		track->vgt_strmout_buffer_en = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		अवरोध;
	हाल VGT_STRMOUT_BUFFER_BASE_0:
	हाल VGT_STRMOUT_BUFFER_BASE_1:
	हाल VGT_STRMOUT_BUFFER_BASE_2:
	हाल VGT_STRMOUT_BUFFER_BASE_3:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = (reg - VGT_STRMOUT_BUFFER_BASE_0) / 16;
		track->vgt_strmout_bo_offset[पंचांगp] = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->vgt_strmout_bo[पंचांगp] = reloc->robj;
		track->vgt_strmout_bo_mc[पंचांगp] = reloc->gpu_offset;
		track->streamout_dirty = true;
		अवरोध;
	हाल VGT_STRMOUT_BUFFER_SIZE_0:
	हाल VGT_STRMOUT_BUFFER_SIZE_1:
	हाल VGT_STRMOUT_BUFFER_SIZE_2:
	हाल VGT_STRMOUT_BUFFER_SIZE_3:
		पंचांगp = (reg - VGT_STRMOUT_BUFFER_SIZE_0) / 16;
		/* size in रेजिस्टर is DWs, convert to bytes */
		track->vgt_strmout_size[पंचांगp] = radeon_get_ib_value(p, idx) * 4;
		track->streamout_dirty = true;
		अवरोध;
	हाल CP_COHER_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "missing reloc for CP_COHER_BASE "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल R_028238_CB_TARGET_MASK:
		track->cb_target_mask = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल R_02823C_CB_SHADER_MASK:
		track->cb_shader_mask = radeon_get_ib_value(p, idx);
		अवरोध;
	हाल R_028C04_PA_SC_AA_CONFIG:
		पंचांगp = G_028C04_MSAA_NUM_SAMPLES(radeon_get_ib_value(p, idx));
		track->log_nsamples = पंचांगp;
		track->nsamples = 1 << पंचांगp;
		track->cb_dirty = true;
		अवरोध;
	हाल R_028808_CB_COLOR_CONTROL:
		पंचांगp = G_028808_SPECIAL_OP(radeon_get_ib_value(p, idx));
		track->is_resolve = पंचांगp == V_028808_SPECIAL_RESOLVE_BOX;
		track->cb_dirty = true;
		अवरोध;
	हाल R_0280A0_CB_COLOR0_INFO:
	हाल R_0280A4_CB_COLOR1_INFO:
	हाल R_0280A8_CB_COLOR2_INFO:
	हाल R_0280AC_CB_COLOR3_INFO:
	हाल R_0280B0_CB_COLOR4_INFO:
	हाल R_0280B4_CB_COLOR5_INFO:
	हाल R_0280B8_CB_COLOR6_INFO:
	हाल R_0280BC_CB_COLOR7_INFO:
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS) &&
		     radeon_cs_packet_next_is_pkt3_nop(p)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			पंचांगp = (reg - R_0280A0_CB_COLOR0_INFO) / 4;
			track->cb_color_info[पंचांगp] = radeon_get_ib_value(p, idx);
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
				ib[idx] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_2D_TILED_THIN1);
				track->cb_color_info[पंचांगp] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_2D_TILED_THIN1);
			पूर्ण अन्यथा अगर (reloc->tiling_flags & RADEON_TILING_MICRO) अणु
				ib[idx] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_1D_TILED_THIN1);
				track->cb_color_info[पंचांगp] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_1D_TILED_THIN1);
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp = (reg - R_0280A0_CB_COLOR0_INFO) / 4;
			track->cb_color_info[पंचांगp] = radeon_get_ib_value(p, idx);
		पूर्ण
		track->cb_dirty = true;
		अवरोध;
	हाल R_028080_CB_COLOR0_VIEW:
	हाल R_028084_CB_COLOR1_VIEW:
	हाल R_028088_CB_COLOR2_VIEW:
	हाल R_02808C_CB_COLOR3_VIEW:
	हाल R_028090_CB_COLOR4_VIEW:
	हाल R_028094_CB_COLOR5_VIEW:
	हाल R_028098_CB_COLOR6_VIEW:
	हाल R_02809C_CB_COLOR7_VIEW:
		पंचांगp = (reg - R_028080_CB_COLOR0_VIEW) / 4;
		track->cb_color_view[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल R_028060_CB_COLOR0_SIZE:
	हाल R_028064_CB_COLOR1_SIZE:
	हाल R_028068_CB_COLOR2_SIZE:
	हाल R_02806C_CB_COLOR3_SIZE:
	हाल R_028070_CB_COLOR4_SIZE:
	हाल R_028074_CB_COLOR5_SIZE:
	हाल R_028078_CB_COLOR6_SIZE:
	हाल R_02807C_CB_COLOR7_SIZE:
		पंचांगp = (reg - R_028060_CB_COLOR0_SIZE) / 4;
		track->cb_color_size[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_color_size_idx[पंचांगp] = idx;
		track->cb_dirty = true;
		अवरोध;
		/* This रेजिस्टर were added late, there is userspace
		 * which करोes provide relocation क्रम those but set
		 * 0 offset. In order to aव्योम अवरोधing old userspace
		 * we detect this and set address to poपूर्णांक to last
		 * CB_COLOR0_BASE, note that अगर userspace करोesn't set
		 * CB_COLOR0_BASE beक्रमe this रेजिस्टर we will report
		 * error. Old userspace always set CB_COLOR0_BASE
		 * beक्रमe any of this.
		 */
	हाल R_0280E0_CB_COLOR0_FRAG:
	हाल R_0280E4_CB_COLOR1_FRAG:
	हाल R_0280E8_CB_COLOR2_FRAG:
	हाल R_0280EC_CB_COLOR3_FRAG:
	हाल R_0280F0_CB_COLOR4_FRAG:
	हाल R_0280F4_CB_COLOR5_FRAG:
	हाल R_0280F8_CB_COLOR6_FRAG:
	हाल R_0280FC_CB_COLOR7_FRAG:
		पंचांगp = (reg - R_0280E0_CB_COLOR0_FRAG) / 4;
		अगर (!radeon_cs_packet_next_is_pkt3_nop(p)) अणु
			अगर (!track->cb_color_base_last[पंचांगp]) अणु
				dev_err(p->dev, "Broken old userspace ? no cb_color0_base supplied before trying to write 0x%08X\n", reg);
				वापस -EINVAL;
			पूर्ण
			track->cb_color_frag_bo[पंचांगp] = track->cb_color_bo[पंचांगp];
			track->cb_color_frag_offset[पंचांगp] = track->cb_color_bo_offset[पंचांगp];
			ib[idx] = track->cb_color_base_last[पंचांगp];
		पूर्ण अन्यथा अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			track->cb_color_frag_bo[पंचांगp] = reloc->robj;
			track->cb_color_frag_offset[पंचांगp] = (u64)ib[idx] << 8;
			ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		पूर्ण
		अगर (G_0280A0_TILE_MODE(track->cb_color_info[पंचांगp])) अणु
			track->cb_dirty = true;
		पूर्ण
		अवरोध;
	हाल R_0280C0_CB_COLOR0_TILE:
	हाल R_0280C4_CB_COLOR1_TILE:
	हाल R_0280C8_CB_COLOR2_TILE:
	हाल R_0280CC_CB_COLOR3_TILE:
	हाल R_0280D0_CB_COLOR4_TILE:
	हाल R_0280D4_CB_COLOR5_TILE:
	हाल R_0280D8_CB_COLOR6_TILE:
	हाल R_0280DC_CB_COLOR7_TILE:
		पंचांगp = (reg - R_0280C0_CB_COLOR0_TILE) / 4;
		अगर (!radeon_cs_packet_next_is_pkt3_nop(p)) अणु
			अगर (!track->cb_color_base_last[पंचांगp]) अणु
				dev_err(p->dev, "Broken old userspace ? no cb_color0_base supplied before trying to write 0x%08X\n", reg);
				वापस -EINVAL;
			पूर्ण
			track->cb_color_tile_bo[पंचांगp] = track->cb_color_bo[पंचांगp];
			track->cb_color_tile_offset[पंचांगp] = track->cb_color_bo_offset[पंचांगp];
			ib[idx] = track->cb_color_base_last[पंचांगp];
		पूर्ण अन्यथा अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			track->cb_color_tile_bo[पंचांगp] = reloc->robj;
			track->cb_color_tile_offset[पंचांगp] = (u64)ib[idx] << 8;
			ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		पूर्ण
		अगर (G_0280A0_TILE_MODE(track->cb_color_info[पंचांगp])) अणु
			track->cb_dirty = true;
		पूर्ण
		अवरोध;
	हाल R_028100_CB_COLOR0_MASK:
	हाल R_028104_CB_COLOR1_MASK:
	हाल R_028108_CB_COLOR2_MASK:
	हाल R_02810C_CB_COLOR3_MASK:
	हाल R_028110_CB_COLOR4_MASK:
	हाल R_028114_CB_COLOR5_MASK:
	हाल R_028118_CB_COLOR6_MASK:
	हाल R_02811C_CB_COLOR7_MASK:
		पंचांगp = (reg - R_028100_CB_COLOR0_MASK) / 4;
		track->cb_color_mask[पंचांगp] = radeon_get_ib_value(p, idx);
		अगर (G_0280A0_TILE_MODE(track->cb_color_info[पंचांगp])) अणु
			track->cb_dirty = true;
		पूर्ण
		अवरोध;
	हाल CB_COLOR0_BASE:
	हाल CB_COLOR1_BASE:
	हाल CB_COLOR2_BASE:
	हाल CB_COLOR3_BASE:
	हाल CB_COLOR4_BASE:
	हाल CB_COLOR5_BASE:
	हाल CB_COLOR6_BASE:
	हाल CB_COLOR7_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = (reg - CB_COLOR0_BASE) / 4;
		track->cb_color_bo_offset[पंचांगp] = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_base_last[पंचांगp] = ib[idx];
		track->cb_color_bo[पंचांगp] = reloc->robj;
		track->cb_color_bo_mc[पंचांगp] = reloc->gpu_offset;
		track->cb_dirty = true;
		अवरोध;
	हाल DB_DEPTH_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->db_offset = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_bo = reloc->robj;
		track->db_bo_mc = reloc->gpu_offset;
		track->db_dirty = true;
		अवरोध;
	हाल DB_HTILE_DATA_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->htile_offset = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->htile_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल DB_HTILE_SURFACE:
		track->htile_surface = radeon_get_ib_value(p, idx);
		/* क्रमce 8x8 htile width and height */
		ib[idx] |= 3;
		track->db_dirty = true;
		अवरोध;
	हाल SQ_PGM_START_FS:
	हाल SQ_PGM_START_ES:
	हाल SQ_PGM_START_VS:
	हाल SQ_PGM_START_GS:
	हाल SQ_PGM_START_PS:
	हाल SQ_ALU_CONST_CACHE_GS_0:
	हाल SQ_ALU_CONST_CACHE_GS_1:
	हाल SQ_ALU_CONST_CACHE_GS_2:
	हाल SQ_ALU_CONST_CACHE_GS_3:
	हाल SQ_ALU_CONST_CACHE_GS_4:
	हाल SQ_ALU_CONST_CACHE_GS_5:
	हाल SQ_ALU_CONST_CACHE_GS_6:
	हाल SQ_ALU_CONST_CACHE_GS_7:
	हाल SQ_ALU_CONST_CACHE_GS_8:
	हाल SQ_ALU_CONST_CACHE_GS_9:
	हाल SQ_ALU_CONST_CACHE_GS_10:
	हाल SQ_ALU_CONST_CACHE_GS_11:
	हाल SQ_ALU_CONST_CACHE_GS_12:
	हाल SQ_ALU_CONST_CACHE_GS_13:
	हाल SQ_ALU_CONST_CACHE_GS_14:
	हाल SQ_ALU_CONST_CACHE_GS_15:
	हाल SQ_ALU_CONST_CACHE_PS_0:
	हाल SQ_ALU_CONST_CACHE_PS_1:
	हाल SQ_ALU_CONST_CACHE_PS_2:
	हाल SQ_ALU_CONST_CACHE_PS_3:
	हाल SQ_ALU_CONST_CACHE_PS_4:
	हाल SQ_ALU_CONST_CACHE_PS_5:
	हाल SQ_ALU_CONST_CACHE_PS_6:
	हाल SQ_ALU_CONST_CACHE_PS_7:
	हाल SQ_ALU_CONST_CACHE_PS_8:
	हाल SQ_ALU_CONST_CACHE_PS_9:
	हाल SQ_ALU_CONST_CACHE_PS_10:
	हाल SQ_ALU_CONST_CACHE_PS_11:
	हाल SQ_ALU_CONST_CACHE_PS_12:
	हाल SQ_ALU_CONST_CACHE_PS_13:
	हाल SQ_ALU_CONST_CACHE_PS_14:
	हाल SQ_ALU_CONST_CACHE_PS_15:
	हाल SQ_ALU_CONST_CACHE_VS_0:
	हाल SQ_ALU_CONST_CACHE_VS_1:
	हाल SQ_ALU_CONST_CACHE_VS_2:
	हाल SQ_ALU_CONST_CACHE_VS_3:
	हाल SQ_ALU_CONST_CACHE_VS_4:
	हाल SQ_ALU_CONST_CACHE_VS_5:
	हाल SQ_ALU_CONST_CACHE_VS_6:
	हाल SQ_ALU_CONST_CACHE_VS_7:
	हाल SQ_ALU_CONST_CACHE_VS_8:
	हाल SQ_ALU_CONST_CACHE_VS_9:
	हाल SQ_ALU_CONST_CACHE_VS_10:
	हाल SQ_ALU_CONST_CACHE_VS_11:
	हाल SQ_ALU_CONST_CACHE_VS_12:
	हाल SQ_ALU_CONST_CACHE_VS_13:
	हाल SQ_ALU_CONST_CACHE_VS_14:
	हाल SQ_ALU_CONST_CACHE_VS_15:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल SX_MEMORY_EXPORT_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONFIG_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल SX_MISC:
		track->sx_misc_समाप्त_all_prims = (radeon_get_ib_value(p, idx) & 0x1) != 0;
		अवरोध;
	शेष:
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित r600_mip_minअगरy(अचिन्हित size, अचिन्हित level)
अणु
	अचिन्हित val;

	val = max(1U, size >> level);
	अगर (level > 0)
		val = roundup_घात_of_two(val);
	वापस val;
पूर्ण

अटल व्योम r600_texture_size(अचिन्हित nfaces, अचिन्हित blevel, अचिन्हित llevel,
			      अचिन्हित w0, अचिन्हित h0, अचिन्हित d0, अचिन्हित nsamples, अचिन्हित क्रमmat,
			      अचिन्हित block_align, अचिन्हित height_align, अचिन्हित base_align,
			      अचिन्हित *l0_size, अचिन्हित *mipmap_size)
अणु
	अचिन्हित offset, i, level;
	अचिन्हित width, height, depth, size;
	अचिन्हित blocksize;
	अचिन्हित nbx, nby;
	अचिन्हित nlevels = llevel - blevel + 1;

	*l0_size = -1;
	blocksize = r600_fmt_get_blocksize(क्रमmat);

	w0 = r600_mip_minअगरy(w0, 0);
	h0 = r600_mip_minअगरy(h0, 0);
	d0 = r600_mip_minअगरy(d0, 0);
	क्रम(i = 0, offset = 0, level = blevel; i < nlevels; i++, level++) अणु
		width = r600_mip_minअगरy(w0, i);
		nbx = r600_fmt_get_nblocksx(क्रमmat, width);

		nbx = round_up(nbx, block_align);

		height = r600_mip_minअगरy(h0, i);
		nby = r600_fmt_get_nblocksy(क्रमmat, height);
		nby = round_up(nby, height_align);

		depth = r600_mip_minअगरy(d0, i);

		size = nbx * nby * blocksize * nsamples;
		अगर (nfaces)
			size *= nfaces;
		अन्यथा
			size *= depth;

		अगर (i == 0)
			*l0_size = size;

		अगर (i == 0 || i == 1)
			offset = round_up(offset, base_align);

		offset += size;
	पूर्ण
	*mipmap_size = offset;
	अगर (llevel == 0)
		*mipmap_size = *l0_size;
	अगर (!blevel)
		*mipmap_size -= *l0_size;
पूर्ण

/**
 * r600_check_texture_resource() - check अगर रेजिस्टर is authorized or not
 * @p: parser काष्ठाure holding parsing context
 * @idx: index पूर्णांकo the cs buffer
 * @texture: texture's bo काष्ठाure
 * @mipmap: mipmap's bo काष्ठाure
 * @base_offset: base offset (used क्रम error checking)
 * @mip_offset: mip offset (used क्रम error checking)
 * @tiling_flags: tiling flags
 *
 * This function will check that the resource has valid field and that
 * the texture and mipmap bo object are big enough to cover this resource.
 */
अटल पूर्णांक r600_check_texture_resource(काष्ठा radeon_cs_parser *p,  u32 idx,
					      काष्ठा radeon_bo *texture,
					      काष्ठा radeon_bo *mipmap,
					      u64 base_offset,
					      u64 mip_offset,
					      u32 tiling_flags)
अणु
	काष्ठा r600_cs_track *track = p->track;
	u32 dim, nfaces, llevel, blevel, w0, h0, d0;
	u32 word0, word1, l0_size, mipmap_size, word2, word3, word4, word5;
	u32 height_align, pitch, pitch_align, depth_align;
	u32 barray, larray;
	u64 base_align;
	काष्ठा array_mode_checker array_check;
	u32 क्रमmat;
	bool is_array;

	/* on legacy kernel we करोn't perक्रमm advanced check */
	अगर (p->rdev == शून्य)
		वापस 0;

	/* convert to bytes */
	base_offset <<= 8;
	mip_offset <<= 8;

	word0 = radeon_get_ib_value(p, idx + 0);
	अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
		अगर (tiling_flags & RADEON_TILING_MACRO)
			word0 |= S_038000_TILE_MODE(V_038000_ARRAY_2D_TILED_THIN1);
		अन्यथा अगर (tiling_flags & RADEON_TILING_MICRO)
			word0 |= S_038000_TILE_MODE(V_038000_ARRAY_1D_TILED_THIN1);
	पूर्ण
	word1 = radeon_get_ib_value(p, idx + 1);
	word2 = radeon_get_ib_value(p, idx + 2) << 8;
	word3 = radeon_get_ib_value(p, idx + 3) << 8;
	word4 = radeon_get_ib_value(p, idx + 4);
	word5 = radeon_get_ib_value(p, idx + 5);
	dim = G_038000_DIM(word0);
	w0 = G_038000_TEX_WIDTH(word0) + 1;
	pitch = (G_038000_PITCH(word0) + 1) * 8;
	h0 = G_038004_TEX_HEIGHT(word1) + 1;
	d0 = G_038004_TEX_DEPTH(word1);
	क्रमmat = G_038004_DATA_FORMAT(word1);
	blevel = G_038010_BASE_LEVEL(word4);
	llevel = G_038014_LAST_LEVEL(word5);
	/* pitch in texels */
	array_check.array_mode = G_038000_TILE_MODE(word0);
	array_check.group_size = track->group_size;
	array_check.nbanks = track->nbanks;
	array_check.npipes = track->npipes;
	array_check.nsamples = 1;
	array_check.blocksize = r600_fmt_get_blocksize(क्रमmat);
	nfaces = 1;
	is_array = false;
	चयन (dim) अणु
	हाल V_038000_SQ_TEX_DIM_1D:
	हाल V_038000_SQ_TEX_DIM_2D:
	हाल V_038000_SQ_TEX_DIM_3D:
		अवरोध;
	हाल V_038000_SQ_TEX_DIM_CUBEMAP:
		अगर (p->family >= CHIP_RV770)
			nfaces = 8;
		अन्यथा
			nfaces = 6;
		अवरोध;
	हाल V_038000_SQ_TEX_DIM_1D_ARRAY:
	हाल V_038000_SQ_TEX_DIM_2D_ARRAY:
		is_array = true;
		अवरोध;
	हाल V_038000_SQ_TEX_DIM_2D_ARRAY_MSAA:
		is_array = true;
		fallthrough;
	हाल V_038000_SQ_TEX_DIM_2D_MSAA:
		array_check.nsamples = 1 << llevel;
		llevel = 0;
		अवरोध;
	शेष:
		dev_warn(p->dev, "this kernel doesn't support %d texture dim\n", G_038000_DIM(word0));
		वापस -EINVAL;
	पूर्ण
	अगर (!r600_fmt_is_valid_texture(क्रमmat, p->family)) अणु
		dev_warn(p->dev, "%s:%d texture invalid format %d\n",
			 __func__, __LINE__, क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (r600_get_array_mode_alignment(&array_check,
					  &pitch_align, &height_align, &depth_align, &base_align)) अणु
		dev_warn(p->dev, "%s:%d tex array mode (%d) invalid\n",
			 __func__, __LINE__, G_038000_TILE_MODE(word0));
		वापस -EINVAL;
	पूर्ण

	/* XXX check height as well... */

	अगर (!IS_ALIGNED(pitch, pitch_align)) अणु
		dev_warn(p->dev, "%s:%d tex pitch (%d, 0x%x, %d) invalid\n",
			 __func__, __LINE__, pitch, pitch_align, G_038000_TILE_MODE(word0));
		वापस -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(base_offset, base_align)) अणु
		dev_warn(p->dev, "%s:%d tex base offset (0x%llx, 0x%llx, %d) invalid\n",
			 __func__, __LINE__, base_offset, base_align, G_038000_TILE_MODE(word0));
		वापस -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(mip_offset, base_align)) अणु
		dev_warn(p->dev, "%s:%d tex mip offset (0x%llx, 0x%llx, %d) invalid\n",
			 __func__, __LINE__, mip_offset, base_align, G_038000_TILE_MODE(word0));
		वापस -EINVAL;
	पूर्ण

	अगर (blevel > llevel) अणु
		dev_warn(p->dev, "texture blevel %d > llevel %d\n",
			 blevel, llevel);
	पूर्ण
	अगर (is_array) अणु
		barray = G_038014_BASE_ARRAY(word5);
		larray = G_038014_LAST_ARRAY(word5);

		nfaces = larray - barray + 1;
	पूर्ण
	r600_texture_size(nfaces, blevel, llevel, w0, h0, d0, array_check.nsamples, क्रमmat,
			  pitch_align, height_align, base_align,
			  &l0_size, &mipmap_size);
	/* using get ib will give us the offset पूर्णांकo the texture bo */
	अगर ((l0_size + word2) > radeon_bo_size(texture)) अणु
		dev_warn(p->dev, "texture bo too small ((%d %d) (%d %d) %d %d %d -> %d have %ld)\n",
			 w0, h0, pitch_align, height_align,
			 array_check.array_mode, क्रमmat, word2,
			 l0_size, radeon_bo_size(texture));
		dev_warn(p->dev, "alignments %d %d %d %lld\n", pitch, pitch_align, height_align, base_align);
		वापस -EINVAL;
	पूर्ण
	/* using get ib will give us the offset पूर्णांकo the mipmap bo */
	अगर ((mipmap_size + word3) > radeon_bo_size(mipmap)) अणु
		/*dev_warn(p->dev, "mipmap bo too small (%d %d %d %d %d %d -> %d have %ld)\n",
		  w0, h0, क्रमmat, blevel, nlevels, word3, mipmap_size, radeon_bo_size(texture));*/
	पूर्ण
	वापस 0;
पूर्ण

अटल bool r600_is_safe_reg(काष्ठा radeon_cs_parser *p, u32 reg, u32 idx)
अणु
	u32 m, i;

	i = (reg >> 7);
	अगर (i >= ARRAY_SIZE(r600_reg_safe_bm)) अणु
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		वापस false;
	पूर्ण
	m = 1 << ((reg >> 2) & 31);
	अगर (!(r600_reg_safe_bm[i] & m))
		वापस true;
	dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
	वापस false;
पूर्ण

अटल पूर्णांक r600_packet3_check(काष्ठा radeon_cs_parser *p,
				काष्ठा radeon_cs_packet *pkt)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r600_cs_track *track;
	अस्थिर u32 *ib;
	अचिन्हित idx;
	अचिन्हित i;
	अचिन्हित start_reg, end_reg, reg;
	पूर्णांक r;
	u32 idx_value;

	track = (काष्ठा r600_cs_track *)p->track;
	ib = p->ib.ptr;
	idx = pkt->idx + 1;
	idx_value = radeon_get_ib_value(p, idx);

	चयन (pkt->opcode) अणु
	हाल PACKET3_SET_PREDICATION:
	अणु
		पूर्णांक pred_op;
		पूर्णांक पंचांगp;
		uपूर्णांक64_t offset;

		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad SET PREDICATION\n");
			वापस -EINVAL;
		पूर्ण

		पंचांगp = radeon_get_ib_value(p, idx + 1);
		pred_op = (पंचांगp >> 16) & 0x7;

		/* क्रम the clear predicate operation */
		अगर (pred_op == 0)
			वापस 0;

		अगर (pred_op > 2) अणु
			DRM_ERROR("bad SET PREDICATION operation %d\n", pred_op);
			वापस -EINVAL;
		पूर्ण

		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			DRM_ERROR("bad SET PREDICATION\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 (idx_value & 0xfffffff0) +
			 ((u64)(पंचांगp & 0xff) << 32);

		ib[idx + 0] = offset;
		ib[idx + 1] = (पंचांगp & 0xffffff00) | (upper_32_bits(offset) & 0xff);
	पूर्ण
	अवरोध;

	हाल PACKET3_START_3D_CMDBUF:
		अगर (p->family >= CHIP_RV770 || pkt->count) अणु
			DRM_ERROR("bad START_3D\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CONTEXT_CONTROL:
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad CONTEXT_CONTROL\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_INDEX_TYPE:
	हाल PACKET3_NUM_INSTANCES:
		अगर (pkt->count) अणु
			DRM_ERROR("bad INDEX_TYPE/NUM_INSTANCES\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX:
	अणु
		uपूर्णांक64_t offset;
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad DRAW_INDEX\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			DRM_ERROR("bad DRAW_INDEX\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 idx_value +
			 ((u64)(radeon_get_ib_value(p, idx+1) & 0xff) << 32);

		ib[idx+0] = offset;
		ib[idx+1] = upper_32_bits(offset) & 0xff;

		r = r600_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_DRAW_INDEX_AUTO:
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad DRAW_INDEX_AUTO\n");
			वापस -EINVAL;
		पूर्ण
		r = r600_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream %d\n", __func__, __LINE__, idx);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX_IMMD_BE:
	हाल PACKET3_DRAW_INDEX_IMMD:
		अगर (pkt->count < 2) अणु
			DRM_ERROR("bad DRAW_INDEX_IMMD\n");
			वापस -EINVAL;
		पूर्ण
		r = r600_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_WAIT_REG_MEM:
		अगर (pkt->count != 5) अणु
			DRM_ERROR("bad WAIT_REG_MEM\n");
			वापस -EINVAL;
		पूर्ण
		/* bit 4 is reg (0) or mem (1) */
		अगर (idx_value & 0x10) अणु
			uपूर्णांक64_t offset;

			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad WAIT_REG_MEM\n");
				वापस -EINVAL;
			पूर्ण

			offset = reloc->gpu_offset +
				 (radeon_get_ib_value(p, idx+1) & 0xfffffff0) +
				 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

			ib[idx+1] = (ib[idx+1] & 0x3) | (offset & 0xfffffff0);
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण अन्यथा अगर (idx_value & 0x100) अणु
			DRM_ERROR("cannot use PFP on REG wait\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CP_DMA:
	अणु
		u32 command, size;
		u64 offset, पंचांगp;
		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad CP DMA\n");
			वापस -EINVAL;
		पूर्ण
		command = radeon_get_ib_value(p, idx+4);
		size = command & 0x1fffff;
		अगर (command & PACKET3_CP_DMA_CMD_SAS) अणु
			/* src address space is रेजिस्टर */
			DRM_ERROR("CP DMA SAS not supported\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (command & PACKET3_CP_DMA_CMD_SAIC) अणु
				DRM_ERROR("CP DMA SAIC only supported for registers\n");
				वापस -EINVAL;
			पूर्ण
			/* src address space is memory */
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad CP DMA SRC\n");
				वापस -EINVAL;
			पूर्ण

			पंचांगp = radeon_get_ib_value(p, idx) +
				((u64)(radeon_get_ib_value(p, idx+1) & 0xff) << 32);

			offset = reloc->gpu_offset + पंचांगp;

			अगर ((पंचांगp + size) > radeon_bo_size(reloc->robj)) अणु
				dev_warn(p->dev, "CP DMA src buffer too small (%llu %lu)\n",
					 पंचांगp + size, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण

			ib[idx] = offset;
			ib[idx+1] = (ib[idx+1] & 0xffffff00) | (upper_32_bits(offset) & 0xff);
		पूर्ण
		अगर (command & PACKET3_CP_DMA_CMD_DAS) अणु
			/* dst address space is रेजिस्टर */
			DRM_ERROR("CP DMA DAS not supported\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* dst address space is memory */
			अगर (command & PACKET3_CP_DMA_CMD_DAIC) अणु
				DRM_ERROR("CP DMA DAIC only supported for registers\n");
				वापस -EINVAL;
			पूर्ण
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad CP DMA DST\n");
				वापस -EINVAL;
			पूर्ण

			पंचांगp = radeon_get_ib_value(p, idx+2) +
				((u64)(radeon_get_ib_value(p, idx+3) & 0xff) << 32);

			offset = reloc->gpu_offset + पंचांगp;

			अगर ((पंचांगp + size) > radeon_bo_size(reloc->robj)) अणु
				dev_warn(p->dev, "CP DMA dst buffer too small (%llu %lu)\n",
					 पंचांगp + size, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण

			ib[idx+2] = offset;
			ib[idx+3] = upper_32_bits(offset) & 0xff;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_SURFACE_SYNC:
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad SURFACE_SYNC\n");
			वापस -EINVAL;
		पूर्ण
		/* 0xffffffff/0x0 is flush all cache flag */
		अगर (radeon_get_ib_value(p, idx + 1) != 0xffffffff ||
		    radeon_get_ib_value(p, idx + 2) != 0) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad SURFACE_SYNC\n");
				वापस -EINVAL;
			पूर्ण
			ib[idx+2] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		पूर्ण
		अवरोध;
	हाल PACKET3_EVENT_WRITE:
		अगर (pkt->count != 2 && pkt->count != 0) अणु
			DRM_ERROR("bad EVENT_WRITE\n");
			वापस -EINVAL;
		पूर्ण
		अगर (pkt->count) अणु
			uपूर्णांक64_t offset;

			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad EVENT_WRITE\n");
				वापस -EINVAL;
			पूर्ण
			offset = reloc->gpu_offset +
				 (radeon_get_ib_value(p, idx+1) & 0xfffffff8) +
				 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

			ib[idx+1] = offset & 0xfffffff8;
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण
		अवरोध;
	हाल PACKET3_EVENT_WRITE_EOP:
	अणु
		uपूर्णांक64_t offset;

		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad EVENT_WRITE_EOP\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			DRM_ERROR("bad EVENT_WRITE\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 (radeon_get_ib_value(p, idx+1) & 0xfffffffc) +
			 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

		ib[idx+1] = offset & 0xfffffffc;
		ib[idx+2] = (ib[idx+2] & 0xffffff00) | (upper_32_bits(offset) & 0xff);
		अवरोध;
	पूर्ण
	हाल PACKET3_SET_CONFIG_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONFIG_REG_OFFSET) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < pkt->count; i++) अणु
			reg = start_reg + (4 * i);
			r = r600_cs_check_reg(p, reg, idx+1+i);
			अगर (r)
				वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CONTEXT_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONTEXT_REG_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONTEXT_REG_OFFSET) ||
		    (start_reg >= PACKET3_SET_CONTEXT_REG_END) ||
		    (end_reg >= PACKET3_SET_CONTEXT_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONTEXT_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < pkt->count; i++) अणु
			reg = start_reg + (4 * i);
			r = r600_cs_check_reg(p, reg, idx+1+i);
			अगर (r)
				वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_RESOURCE:
		अगर (pkt->count % 7) अणु
			DRM_ERROR("bad SET_RESOURCE\n");
			वापस -EINVAL;
		पूर्ण
		start_reg = (idx_value << 2) + PACKET3_SET_RESOURCE_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_RESOURCE_OFFSET) ||
		    (start_reg >= PACKET3_SET_RESOURCE_END) ||
		    (end_reg >= PACKET3_SET_RESOURCE_END)) अणु
			DRM_ERROR("bad SET_RESOURCE\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < (pkt->count / 7); i++) अणु
			काष्ठा radeon_bo *texture, *mipmap;
			u32 size, offset, base_offset, mip_offset;

			चयन (G__SQ_VTX_CONSTANT_TYPE(radeon_get_ib_value(p, idx+(i*7)+6+1))) अणु
			हाल SQ_TEX_VTX_VALID_TEXTURE:
				/* tex base */
				r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
				अगर (r) अणु
					DRM_ERROR("bad SET_RESOURCE\n");
					वापस -EINVAL;
				पूर्ण
				base_offset = (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
				अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
					अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
						ib[idx+1+(i*7)+0] |= S_038000_TILE_MODE(V_038000_ARRAY_2D_TILED_THIN1);
					अन्यथा अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
						ib[idx+1+(i*7)+0] |= S_038000_TILE_MODE(V_038000_ARRAY_1D_TILED_THIN1);
				पूर्ण
				texture = reloc->robj;
				/* tex mip base */
				r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
				अगर (r) अणु
					DRM_ERROR("bad SET_RESOURCE\n");
					वापस -EINVAL;
				पूर्ण
				mip_offset = (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
				mipmap = reloc->robj;
				r = r600_check_texture_resource(p,  idx+(i*7)+1,
								texture, mipmap,
								base_offset + radeon_get_ib_value(p, idx+1+(i*7)+2),
								mip_offset + radeon_get_ib_value(p, idx+1+(i*7)+3),
								reloc->tiling_flags);
				अगर (r)
					वापस r;
				ib[idx+1+(i*7)+2] += base_offset;
				ib[idx+1+(i*7)+3] += mip_offset;
				अवरोध;
			हाल SQ_TEX_VTX_VALID_BUFFER:
			अणु
				uपूर्णांक64_t offset64;
				/* vtx base */
				r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
				अगर (r) अणु
					DRM_ERROR("bad SET_RESOURCE\n");
					वापस -EINVAL;
				पूर्ण
				offset = radeon_get_ib_value(p, idx+1+(i*7)+0);
				size = radeon_get_ib_value(p, idx+1+(i*7)+1) + 1;
				अगर (p->rdev && (size + offset) > radeon_bo_size(reloc->robj)) अणु
					/* क्रमce size to size of the buffer */
					dev_warn(p->dev, "vbo resource seems too big (%d) for the bo (%ld)\n",
						 size + offset, radeon_bo_size(reloc->robj));
					ib[idx+1+(i*7)+1] = radeon_bo_size(reloc->robj) - offset;
				पूर्ण

				offset64 = reloc->gpu_offset + offset;
				ib[idx+1+(i*8)+0] = offset64;
				ib[idx+1+(i*8)+2] = (ib[idx+1+(i*8)+2] & 0xffffff00) |
						    (upper_32_bits(offset64) & 0xff);
				अवरोध;
			पूर्ण
			हाल SQ_TEX_VTX_INVALID_TEXTURE:
			हाल SQ_TEX_VTX_INVALID_BUFFER:
			शेष:
				DRM_ERROR("bad SET_RESOURCE\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_ALU_CONST:
		अगर (track->sq_config & DX9_CONSTS) अणु
			start_reg = (idx_value << 2) + PACKET3_SET_ALU_CONST_OFFSET;
			end_reg = 4 * pkt->count + start_reg - 4;
			अगर ((start_reg < PACKET3_SET_ALU_CONST_OFFSET) ||
			    (start_reg >= PACKET3_SET_ALU_CONST_END) ||
			    (end_reg >= PACKET3_SET_ALU_CONST_END)) अणु
				DRM_ERROR("bad SET_ALU_CONST\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_BOOL_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_BOOL_CONST_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_BOOL_CONST_OFFSET) ||
		    (start_reg >= PACKET3_SET_BOOL_CONST_END) ||
		    (end_reg >= PACKET3_SET_BOOL_CONST_END)) अणु
			DRM_ERROR("bad SET_BOOL_CONST\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_LOOP_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_LOOP_CONST_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_LOOP_CONST_OFFSET) ||
		    (start_reg >= PACKET3_SET_LOOP_CONST_END) ||
		    (end_reg >= PACKET3_SET_LOOP_CONST_END)) अणु
			DRM_ERROR("bad SET_LOOP_CONST\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CTL_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_CTL_CONST_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CTL_CONST_OFFSET) ||
		    (start_reg >= PACKET3_SET_CTL_CONST_END) ||
		    (end_reg >= PACKET3_SET_CTL_CONST_END)) अणु
			DRM_ERROR("bad SET_CTL_CONST\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_SAMPLER:
		अगर (pkt->count % 3) अणु
			DRM_ERROR("bad SET_SAMPLER\n");
			वापस -EINVAL;
		पूर्ण
		start_reg = (idx_value << 2) + PACKET3_SET_SAMPLER_OFFSET;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_SAMPLER_OFFSET) ||
		    (start_reg >= PACKET3_SET_SAMPLER_END) ||
		    (end_reg >= PACKET3_SET_SAMPLER_END)) अणु
			DRM_ERROR("bad SET_SAMPLER\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_STRMOUT_BASE_UPDATE:
		/* RS780 and RS880 also need this */
		अगर (p->family < CHIP_RS780) अणु
			DRM_ERROR("STRMOUT_BASE_UPDATE only supported on 7xx\n");
			वापस -EINVAL;
		पूर्ण
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad STRMOUT_BASE_UPDATE packet count\n");
			वापस -EINVAL;
		पूर्ण
		अगर (idx_value > 3) अणु
			DRM_ERROR("bad STRMOUT_BASE_UPDATE index\n");
			वापस -EINVAL;
		पूर्ण
		अणु
			u64 offset;

			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad STRMOUT_BASE_UPDATE reloc\n");
				वापस -EINVAL;
			पूर्ण

			अगर (reloc->robj != track->vgt_strmout_bo[idx_value]) अणु
				DRM_ERROR("bad STRMOUT_BASE_UPDATE, bo does not match\n");
				वापस -EINVAL;
			पूर्ण

			offset = radeon_get_ib_value(p, idx+1) << 8;
			अगर (offset != track->vgt_strmout_bo_offset[idx_value]) अणु
				DRM_ERROR("bad STRMOUT_BASE_UPDATE, bo offset does not match: 0x%llx, 0x%x\n",
					  offset, track->vgt_strmout_bo_offset[idx_value]);
				वापस -EINVAL;
			पूर्ण

			अगर ((offset + 4) > radeon_bo_size(reloc->robj)) अणु
				DRM_ERROR("bad STRMOUT_BASE_UPDATE bo too small: 0x%llx, 0x%lx\n",
					  offset + 4, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण
			ib[idx+1] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		पूर्ण
		अवरोध;
	हाल PACKET3_SURFACE_BASE_UPDATE:
		अगर (p->family >= CHIP_RV770 || p->family == CHIP_R600) अणु
			DRM_ERROR("bad SURFACE_BASE_UPDATE\n");
			वापस -EINVAL;
		पूर्ण
		अगर (pkt->count) अणु
			DRM_ERROR("bad SURFACE_BASE_UPDATE\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_STRMOUT_BUFFER_UPDATE:
		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad STRMOUT_BUFFER_UPDATE (invalid count)\n");
			वापस -EINVAL;
		पूर्ण
		/* Updating memory at DST_ADDRESS. */
		अगर (idx_value & 0x1) अणु
			u64 offset;
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad STRMOUT_BUFFER_UPDATE (missing dst reloc)\n");
				वापस -EINVAL;
			पूर्ण
			offset = radeon_get_ib_value(p, idx+1);
			offset += ((u64)(radeon_get_ib_value(p, idx+2) & 0xff)) << 32;
			अगर ((offset + 4) > radeon_bo_size(reloc->robj)) अणु
				DRM_ERROR("bad STRMOUT_BUFFER_UPDATE dst bo too small: 0x%llx, 0x%lx\n",
					  offset + 4, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण
			offset += reloc->gpu_offset;
			ib[idx+1] = offset;
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण
		/* Reading data from SRC_ADDRESS. */
		अगर (((idx_value >> 1) & 0x3) == 2) अणु
			u64 offset;
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad STRMOUT_BUFFER_UPDATE (missing src reloc)\n");
				वापस -EINVAL;
			पूर्ण
			offset = radeon_get_ib_value(p, idx+3);
			offset += ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
			अगर ((offset + 4) > radeon_bo_size(reloc->robj)) अणु
				DRM_ERROR("bad STRMOUT_BUFFER_UPDATE src bo too small: 0x%llx, 0x%lx\n",
					  offset + 4, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण
			offset += reloc->gpu_offset;
			ib[idx+3] = offset;
			ib[idx+4] = upper_32_bits(offset) & 0xff;
		पूर्ण
		अवरोध;
	हाल PACKET3_MEM_WRITE:
	अणु
		u64 offset;

		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad MEM_WRITE (invalid count)\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		अगर (r) अणु
			DRM_ERROR("bad MEM_WRITE (missing reloc)\n");
			वापस -EINVAL;
		पूर्ण
		offset = radeon_get_ib_value(p, idx+0);
		offset += ((u64)(radeon_get_ib_value(p, idx+1) & 0xff)) << 32UL;
		अगर (offset & 0x7) अणु
			DRM_ERROR("bad MEM_WRITE (address not qwords aligned)\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((offset + 8) > radeon_bo_size(reloc->robj)) अणु
			DRM_ERROR("bad MEM_WRITE bo too small: 0x%llx, 0x%lx\n",
				  offset + 8, radeon_bo_size(reloc->robj));
			वापस -EINVAL;
		पूर्ण
		offset += reloc->gpu_offset;
		ib[idx+0] = offset;
		ib[idx+1] = upper_32_bits(offset) & 0xff;
		अवरोध;
	पूर्ण
	हाल PACKET3_COPY_DW:
		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad COPY_DW (invalid count)\n");
			वापस -EINVAL;
		पूर्ण
		अगर (idx_value & 0x1) अणु
			u64 offset;
			/* SRC is memory. */
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad COPY_DW (missing src reloc)\n");
				वापस -EINVAL;
			पूर्ण
			offset = radeon_get_ib_value(p, idx+1);
			offset += ((u64)(radeon_get_ib_value(p, idx+2) & 0xff)) << 32;
			अगर ((offset + 4) > radeon_bo_size(reloc->robj)) अणु
				DRM_ERROR("bad COPY_DW src bo too small: 0x%llx, 0x%lx\n",
					  offset + 4, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण
			offset += reloc->gpu_offset;
			ib[idx+1] = offset;
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण अन्यथा अणु
			/* SRC is a reg. */
			reg = radeon_get_ib_value(p, idx+1) << 2;
			अगर (!r600_is_safe_reg(p, reg, idx+1))
				वापस -EINVAL;
		पूर्ण
		अगर (idx_value & 0x2) अणु
			u64 offset;
			/* DST is memory. */
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			अगर (r) अणु
				DRM_ERROR("bad COPY_DW (missing dst reloc)\n");
				वापस -EINVAL;
			पूर्ण
			offset = radeon_get_ib_value(p, idx+3);
			offset += ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
			अगर ((offset + 4) > radeon_bo_size(reloc->robj)) अणु
				DRM_ERROR("bad COPY_DW dst bo too small: 0x%llx, 0x%lx\n",
					  offset + 4, radeon_bo_size(reloc->robj));
				वापस -EINVAL;
			पूर्ण
			offset += reloc->gpu_offset;
			ib[idx+3] = offset;
			ib[idx+4] = upper_32_bits(offset) & 0xff;
		पूर्ण अन्यथा अणु
			/* DST is a reg. */
			reg = radeon_get_ib_value(p, idx+3) << 2;
			अगर (!r600_is_safe_reg(p, reg, idx+3))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_NOP:
		अवरोध;
	शेष:
		DRM_ERROR("Packet3 opcode %x not supported\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r600_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet pkt;
	काष्ठा r600_cs_track *track;
	पूर्णांक r;

	अगर (p->track == शून्य) अणु
		/* initialize tracker, we are in kms */
		track = kzalloc(माप(*track), GFP_KERNEL);
		अगर (track == शून्य)
			वापस -ENOMEM;
		r600_cs_track_init(track);
		अगर (p->rdev->family < CHIP_RV770) अणु
			track->npipes = p->rdev->config.r600.tiling_npipes;
			track->nbanks = p->rdev->config.r600.tiling_nbanks;
			track->group_size = p->rdev->config.r600.tiling_group_size;
		पूर्ण अन्यथा अगर (p->rdev->family <= CHIP_RV740) अणु
			track->npipes = p->rdev->config.rv770.tiling_npipes;
			track->nbanks = p->rdev->config.rv770.tiling_nbanks;
			track->group_size = p->rdev->config.rv770.tiling_group_size;
		पूर्ण
		p->track = track;
	पूर्ण
	करो अणु
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		अगर (r) अणु
			kमुक्त(p->track);
			p->track = शून्य;
			वापस r;
		पूर्ण
		p->idx += pkt.count + 2;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			r = r600_cs_parse_packet0(p, &pkt);
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			r = r600_packet3_check(p, &pkt);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d !\n", pkt.type);
			kमुक्त(p->track);
			p->track = शून्य;
			वापस -EINVAL;
		पूर्ण
		अगर (r) अणु
			kमुक्त(p->track);
			p->track = शून्य;
			वापस r;
		पूर्ण
	पूर्ण जबतक (p->idx < p->chunk_ib->length_dw);
#अगर 0
	क्रम (r = 0; r < p->ib.length_dw; r++) अणु
		pr_info("%05d  0x%08X\n", r, p->ib.ptr[r]);
		mdelay(1);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(p->track);
	p->track = शून्य;
	वापस 0;
पूर्ण

/*
 *  DMA
 */
/**
 * r600_dma_cs_next_reloc() - parse next reloc
 * @p:		parser काष्ठाure holding parsing context.
 * @cs_reloc:		reloc inक्रमmation
 *
 * Return the next reloc, करो bo validation and compute
 * GPU offset using the provided start.
 **/
पूर्णांक r600_dma_cs_next_reloc(काष्ठा radeon_cs_parser *p,
			   काष्ठा radeon_bo_list **cs_reloc)
अणु
	अचिन्हित idx;

	*cs_reloc = शून्य;
	अगर (p->chunk_relocs == शून्य) अणु
		DRM_ERROR("No relocation chunk !\n");
		वापस -EINVAL;
	पूर्ण
	idx = p->dma_reloc_idx;
	अगर (idx >= p->nrelocs) अणु
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, p->nrelocs);
		वापस -EINVAL;
	पूर्ण
	*cs_reloc = &p->relocs[idx];
	p->dma_reloc_idx++;
	वापस 0;
पूर्ण

#घोषणा GET_DMA_CMD(h) (((h) & 0xf0000000) >> 28)
#घोषणा GET_DMA_COUNT(h) ((h) & 0x0000ffff)
#घोषणा GET_DMA_T(h) (((h) & 0x00800000) >> 23)

/**
 * r600_dma_cs_parse() - parse the DMA IB
 * @p:		parser काष्ठाure holding parsing context.
 *
 * Parses the DMA IB from the CS ioctl and updates
 * the GPU addresses based on the reloc inक्रमmation and
 * checks क्रम errors. (R6xx-R7xx)
 * Returns 0 क्रम success and an error on failure.
 **/
पूर्णांक r600_dma_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_chunk *ib_chunk = p->chunk_ib;
	काष्ठा radeon_bo_list *src_reloc, *dst_reloc;
	u32 header, cmd, count, tiled;
	अस्थिर u32 *ib = p->ib.ptr;
	u32 idx, idx_value;
	u64 src_offset, dst_offset;
	पूर्णांक r;

	करो अणु
		अगर (p->idx >= ib_chunk->length_dw) अणु
			DRM_ERROR("Can not parse packet at %d after CS end %d !\n",
				  p->idx, ib_chunk->length_dw);
			वापस -EINVAL;
		पूर्ण
		idx = p->idx;
		header = radeon_get_ib_value(p, idx);
		cmd = GET_DMA_CMD(header);
		count = GET_DMA_COUNT(header);
		tiled = GET_DMA_T(header);

		चयन (cmd) अणु
		हाल DMA_PACKET_WRITE:
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_WRITE\n");
				वापस -EINVAL;
			पूर्ण
			अगर (tiled) अणु
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				p->idx += count + 5;
			पूर्ण अन्यथा अणु
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+2) & 0xff)) << 32;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				p->idx += count + 3;
			पूर्ण
			अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
				dev_warn(p->dev, "DMA write buffer too small (%llu %lu)\n",
					 dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DMA_PACKET_COPY:
			r = r600_dma_cs_next_reloc(p, &src_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_COPY\n");
				वापस -EINVAL;
			पूर्ण
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_COPY\n");
				वापस -EINVAL;
			पूर्ण
			अगर (tiled) अणु
				idx_value = radeon_get_ib_value(p, idx + 2);
				/* detile bit */
				अगर (idx_value & (1 << 31)) अणु
					/* tiled src, linear dst */
					src_offset = radeon_get_ib_value(p, idx+1);
					src_offset <<= 8;
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					dst_offset = radeon_get_ib_value(p, idx+5);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+6) & 0xff)) << 32;
					ib[idx+5] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+6] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				पूर्ण अन्यथा अणु
					/* linear src, tiled dst */
					src_offset = radeon_get_ib_value(p, idx+5);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+6) & 0xff)) << 32;
					ib[idx+5] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+6] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset <<= 8;
					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				पूर्ण
				p->idx += 7;
			पूर्ण अन्यथा अणु
				अगर (p->family >= CHIP_RV770) अणु
					src_offset = radeon_get_ib_value(p, idx+2);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;

					ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+3] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
					ib[idx+4] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
					p->idx += 5;
				पूर्ण अन्यथा अणु
					src_offset = radeon_get_ib_value(p, idx+2);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;
					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff0000)) << 16;

					ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+3] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
					ib[idx+3] += (upper_32_bits(dst_reloc->gpu_offset) & 0xff) << 16;
					p->idx += 4;
				पूर्ण
			पूर्ण
			अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
				dev_warn(p->dev, "DMA copy src buffer too small (%llu %lu)\n",
					 src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
				वापस -EINVAL;
			पूर्ण
			अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
				dev_warn(p->dev, "DMA write dst buffer too small (%llu %lu)\n",
					 dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DMA_PACKET_CONSTANT_FILL:
			अगर (p->family < CHIP_RV770) अणु
				DRM_ERROR("Constant Fill is 7xx only !\n");
				वापस -EINVAL;
			पूर्ण
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_WRITE\n");
				वापस -EINVAL;
			पूर्ण
			dst_offset = radeon_get_ib_value(p, idx+1);
			dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0x00ff0000)) << 16;
			अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
				dev_warn(p->dev, "DMA constant fill buffer too small (%llu %lu)\n",
					 dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
				वापस -EINVAL;
			पूर्ण
			ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
			ib[idx+3] += (upper_32_bits(dst_reloc->gpu_offset) << 16) & 0x00ff0000;
			p->idx += 4;
			अवरोध;
		हाल DMA_PACKET_NOP:
			p->idx += 1;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d at %d !\n", cmd, idx);
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (p->idx < p->chunk_ib->length_dw);
#अगर 0
	क्रम (r = 0; r < p->ib->length_dw; r++) अणु
		pr_info("%05d  0x%08X\n", r, p->ib.ptr[r]);
		mdelay(1);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
