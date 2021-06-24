<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "r600.h"
#समावेश "evergreend.h"
#समावेश "evergreen_reg_safe.h"
#समावेश "cayman_reg_safe.h"

#घोषणा MAX(a,b)                   (((a)>(b))?(a):(b))
#घोषणा MIN(a,b)                   (((a)<(b))?(a):(b))

#घोषणा REG_SAFE_BM_SIZE ARRAY_SIZE(evergreen_reg_safe_bm)

काष्ठा evergreen_cs_track अणु
	u32			group_size;
	u32			nbanks;
	u32			npipes;
	u32			row_size;
	/* value we track */
	u32			nsamples;		/* unused */
	काष्ठा radeon_bo	*cb_color_bo[12];
	u32			cb_color_bo_offset[12];
	काष्ठा radeon_bo	*cb_color_fmask_bo[8];	/* unused */
	काष्ठा radeon_bo	*cb_color_cmask_bo[8];	/* unused */
	u32			cb_color_info[12];
	u32			cb_color_view[12];
	u32			cb_color_pitch[12];
	u32			cb_color_slice[12];
	u32			cb_color_slice_idx[12];
	u32			cb_color_attrib[12];
	u32			cb_color_cmask_slice[8];/* unused */
	u32			cb_color_fmask_slice[8];/* unused */
	u32			cb_target_mask;
	u32			cb_shader_mask; /* unused */
	u32			vgt_strmout_config;
	u32			vgt_strmout_buffer_config;
	काष्ठा radeon_bo	*vgt_strmout_bo[4];
	u32			vgt_strmout_bo_offset[4];
	u32			vgt_strmout_size[4];
	u32			db_depth_control;
	u32			db_depth_view;
	u32			db_depth_slice;
	u32			db_depth_size;
	u32			db_z_info;
	u32			db_z_पढ़ो_offset;
	u32			db_z_ग_लिखो_offset;
	काष्ठा radeon_bo	*db_z_पढ़ो_bo;
	काष्ठा radeon_bo	*db_z_ग_लिखो_bo;
	u32			db_s_info;
	u32			db_s_पढ़ो_offset;
	u32			db_s_ग_लिखो_offset;
	काष्ठा radeon_bo	*db_s_पढ़ो_bo;
	काष्ठा radeon_bo	*db_s_ग_लिखो_bo;
	bool			sx_misc_समाप्त_all_prims;
	bool			cb_dirty;
	bool			db_dirty;
	bool			streamout_dirty;
	u32			htile_offset;
	u32			htile_surface;
	काष्ठा radeon_bo	*htile_bo;
	अचिन्हित दीर्घ		indirect_draw_buffer_size;
	स्थिर अचिन्हित		*reg_safe_bm;
पूर्ण;

अटल u32 evergreen_cs_get_aray_mode(u32 tiling_flags)
अणु
	अगर (tiling_flags & RADEON_TILING_MACRO)
		वापस ARRAY_2D_TILED_THIN1;
	अन्यथा अगर (tiling_flags & RADEON_TILING_MICRO)
		वापस ARRAY_1D_TILED_THIN1;
	अन्यथा
		वापस ARRAY_LINEAR_GENERAL;
पूर्ण

अटल u32 evergreen_cs_get_num_banks(u32 nbanks)
अणु
	चयन (nbanks) अणु
	हाल 2:
		वापस ADDR_SURF_2_BANK;
	हाल 4:
		वापस ADDR_SURF_4_BANK;
	हाल 8:
	शेष:
		वापस ADDR_SURF_8_BANK;
	हाल 16:
		वापस ADDR_SURF_16_BANK;
	पूर्ण
पूर्ण

अटल व्योम evergreen_cs_track_init(काष्ठा evergreen_cs_track *track)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		track->cb_color_fmask_bo[i] = शून्य;
		track->cb_color_cmask_bo[i] = शून्य;
		track->cb_color_cmask_slice[i] = 0;
		track->cb_color_fmask_slice[i] = 0;
	पूर्ण

	क्रम (i = 0; i < 12; i++) अणु
		track->cb_color_bo[i] = शून्य;
		track->cb_color_bo_offset[i] = 0xFFFFFFFF;
		track->cb_color_info[i] = 0;
		track->cb_color_view[i] = 0xFFFFFFFF;
		track->cb_color_pitch[i] = 0;
		track->cb_color_slice[i] = 0xfffffff;
		track->cb_color_slice_idx[i] = 0;
	पूर्ण
	track->cb_target_mask = 0xFFFFFFFF;
	track->cb_shader_mask = 0xFFFFFFFF;
	track->cb_dirty = true;

	track->db_depth_slice = 0xffffffff;
	track->db_depth_view = 0xFFFFC000;
	track->db_depth_size = 0xFFFFFFFF;
	track->db_depth_control = 0xFFFFFFFF;
	track->db_z_info = 0xFFFFFFFF;
	track->db_z_पढ़ो_offset = 0xFFFFFFFF;
	track->db_z_ग_लिखो_offset = 0xFFFFFFFF;
	track->db_z_पढ़ो_bo = शून्य;
	track->db_z_ग_लिखो_bo = शून्य;
	track->db_s_info = 0xFFFFFFFF;
	track->db_s_पढ़ो_offset = 0xFFFFFFFF;
	track->db_s_ग_लिखो_offset = 0xFFFFFFFF;
	track->db_s_पढ़ो_bo = शून्य;
	track->db_s_ग_लिखो_bo = शून्य;
	track->db_dirty = true;
	track->htile_bo = शून्य;
	track->htile_offset = 0xFFFFFFFF;
	track->htile_surface = 0;

	क्रम (i = 0; i < 4; i++) अणु
		track->vgt_strmout_size[i] = 0;
		track->vgt_strmout_bo[i] = शून्य;
		track->vgt_strmout_bo_offset[i] = 0xFFFFFFFF;
	पूर्ण
	track->streamout_dirty = true;
	track->sx_misc_समाप्त_all_prims = false;
पूर्ण

काष्ठा eg_surface अणु
	/* value gathered from cs */
	अचिन्हित	nbx;
	अचिन्हित	nby;
	अचिन्हित	क्रमmat;
	अचिन्हित	mode;
	अचिन्हित	nbanks;
	अचिन्हित	bankw;
	अचिन्हित	bankh;
	अचिन्हित	tsplit;
	अचिन्हित	mtilea;
	अचिन्हित	nsamples;
	/* output value */
	अचिन्हित	bpe;
	अचिन्हित	layer_size;
	अचिन्हित	palign;
	अचिन्हित	halign;
	अचिन्हित दीर्घ	base_align;
पूर्ण;

अटल पूर्णांक evergreen_surface_check_linear(काष्ठा radeon_cs_parser *p,
					  काष्ठा eg_surface *surf,
					  स्थिर अक्षर *prefix)
अणु
	surf->layer_size = surf->nbx * surf->nby * surf->bpe * surf->nsamples;
	surf->base_align = surf->bpe;
	surf->palign = 1;
	surf->halign = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_surface_check_linear_aligned(काष्ठा radeon_cs_parser *p,
						  काष्ठा eg_surface *surf,
						  स्थिर अक्षर *prefix)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	अचिन्हित palign;

	palign = MAX(64, track->group_size / surf->bpe);
	surf->layer_size = surf->nbx * surf->nby * surf->bpe * surf->nsamples;
	surf->base_align = track->group_size;
	surf->palign = palign;
	surf->halign = 1;
	अगर (surf->nbx & (palign - 1)) अणु
		अगर (prefix) अणु
			dev_warn(p->dev, "%s:%d %s pitch %d invalid must be aligned with %d\n",
				 __func__, __LINE__, prefix, surf->nbx, palign);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_surface_check_1d(काष्ठा radeon_cs_parser *p,
				      काष्ठा eg_surface *surf,
				      स्थिर अक्षर *prefix)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	अचिन्हित palign;

	palign = track->group_size / (8 * surf->bpe * surf->nsamples);
	palign = MAX(8, palign);
	surf->layer_size = surf->nbx * surf->nby * surf->bpe;
	surf->base_align = track->group_size;
	surf->palign = palign;
	surf->halign = 8;
	अगर ((surf->nbx & (palign - 1))) अणु
		अगर (prefix) अणु
			dev_warn(p->dev, "%s:%d %s pitch %d invalid must be aligned with %d (%d %d %d)\n",
				 __func__, __LINE__, prefix, surf->nbx, palign,
				 track->group_size, surf->bpe, surf->nsamples);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	अगर ((surf->nby & (8 - 1))) अणु
		अगर (prefix) अणु
			dev_warn(p->dev, "%s:%d %s height %d invalid must be aligned with 8\n",
				 __func__, __LINE__, prefix, surf->nby);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_surface_check_2d(काष्ठा radeon_cs_parser *p,
				      काष्ठा eg_surface *surf,
				      स्थिर अक्षर *prefix)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	अचिन्हित palign, halign, tileb, slice_pt;
	अचिन्हित mtile_pr, mtile_ps, mtileb;

	tileb = 64 * surf->bpe * surf->nsamples;
	slice_pt = 1;
	अगर (tileb > surf->tsplit) अणु
		slice_pt = tileb / surf->tsplit;
	पूर्ण
	tileb = tileb / slice_pt;
	/* macro tile width & height */
	palign = (8 * surf->bankw * track->npipes) * surf->mtilea;
	halign = (8 * surf->bankh * surf->nbanks) / surf->mtilea;
	mtileb = (palign / 8) * (halign / 8) * tileb;
	mtile_pr = surf->nbx / palign;
	mtile_ps = (mtile_pr * surf->nby) / halign;
	surf->layer_size = mtile_ps * mtileb * slice_pt;
	surf->base_align = (palign / 8) * (halign / 8) * tileb;
	surf->palign = palign;
	surf->halign = halign;

	अगर ((surf->nbx & (palign - 1))) अणु
		अगर (prefix) अणु
			dev_warn(p->dev, "%s:%d %s pitch %d invalid must be aligned with %d\n",
				 __func__, __LINE__, prefix, surf->nbx, palign);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	अगर ((surf->nby & (halign - 1))) अणु
		अगर (prefix) अणु
			dev_warn(p->dev, "%s:%d %s height %d invalid must be aligned with %d\n",
				 __func__, __LINE__, prefix, surf->nby, halign);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_surface_check(काष्ठा radeon_cs_parser *p,
				   काष्ठा eg_surface *surf,
				   स्थिर अक्षर *prefix)
अणु
	/* some common value computed here */
	surf->bpe = r600_fmt_get_blocksize(surf->क्रमmat);

	चयन (surf->mode) अणु
	हाल ARRAY_LINEAR_GENERAL:
		वापस evergreen_surface_check_linear(p, surf, prefix);
	हाल ARRAY_LINEAR_ALIGNED:
		वापस evergreen_surface_check_linear_aligned(p, surf, prefix);
	हाल ARRAY_1D_TILED_THIN1:
		वापस evergreen_surface_check_1d(p, surf, prefix);
	हाल ARRAY_2D_TILED_THIN1:
		वापस evergreen_surface_check_2d(p, surf, prefix);
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid array mode %d\n",
				__func__, __LINE__, prefix, surf->mode);
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक evergreen_surface_value_conv_check(काष्ठा radeon_cs_parser *p,
					      काष्ठा eg_surface *surf,
					      स्थिर अक्षर *prefix)
अणु
	चयन (surf->mode) अणु
	हाल ARRAY_2D_TILED_THIN1:
		अवरोध;
	हाल ARRAY_LINEAR_GENERAL:
	हाल ARRAY_LINEAR_ALIGNED:
	हाल ARRAY_1D_TILED_THIN1:
		वापस 0;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid array mode %d\n",
				__func__, __LINE__, prefix, surf->mode);
		वापस -EINVAL;
	पूर्ण

	चयन (surf->nbanks) अणु
	हाल 0: surf->nbanks = 2; अवरोध;
	हाल 1: surf->nbanks = 4; अवरोध;
	हाल 2: surf->nbanks = 8; अवरोध;
	हाल 3: surf->nbanks = 16; अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid number of banks %d\n",
			 __func__, __LINE__, prefix, surf->nbanks);
		वापस -EINVAL;
	पूर्ण
	चयन (surf->bankw) अणु
	हाल 0: surf->bankw = 1; अवरोध;
	हाल 1: surf->bankw = 2; अवरोध;
	हाल 2: surf->bankw = 4; अवरोध;
	हाल 3: surf->bankw = 8; अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid bankw %d\n",
			 __func__, __LINE__, prefix, surf->bankw);
		वापस -EINVAL;
	पूर्ण
	चयन (surf->bankh) अणु
	हाल 0: surf->bankh = 1; अवरोध;
	हाल 1: surf->bankh = 2; अवरोध;
	हाल 2: surf->bankh = 4; अवरोध;
	हाल 3: surf->bankh = 8; अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid bankh %d\n",
			 __func__, __LINE__, prefix, surf->bankh);
		वापस -EINVAL;
	पूर्ण
	चयन (surf->mtilea) अणु
	हाल 0: surf->mtilea = 1; अवरोध;
	हाल 1: surf->mtilea = 2; अवरोध;
	हाल 2: surf->mtilea = 4; अवरोध;
	हाल 3: surf->mtilea = 8; अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid macro tile aspect %d\n",
			 __func__, __LINE__, prefix, surf->mtilea);
		वापस -EINVAL;
	पूर्ण
	चयन (surf->tsplit) अणु
	हाल 0: surf->tsplit = 64; अवरोध;
	हाल 1: surf->tsplit = 128; अवरोध;
	हाल 2: surf->tsplit = 256; अवरोध;
	हाल 3: surf->tsplit = 512; अवरोध;
	हाल 4: surf->tsplit = 1024; अवरोध;
	हाल 5: surf->tsplit = 2048; अवरोध;
	हाल 6: surf->tsplit = 4096; अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d %s invalid tile split %d\n",
			 __func__, __LINE__, prefix, surf->tsplit);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_validate_cb(काष्ठा radeon_cs_parser *p, अचिन्हित id)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	काष्ठा eg_surface surf;
	अचिन्हित pitch, slice, mslice;
	अचिन्हित दीर्घ offset;
	पूर्णांक r;

	mslice = G_028C6C_SLICE_MAX(track->cb_color_view[id]) + 1;
	pitch = track->cb_color_pitch[id];
	slice = track->cb_color_slice[id];
	surf.nbx = (pitch + 1) * 8;
	surf.nby = ((slice + 1) * 64) / surf.nbx;
	surf.mode = G_028C70_ARRAY_MODE(track->cb_color_info[id]);
	surf.क्रमmat = G_028C70_FORMAT(track->cb_color_info[id]);
	surf.tsplit = G_028C74_TILE_SPLIT(track->cb_color_attrib[id]);
	surf.nbanks = G_028C74_NUM_BANKS(track->cb_color_attrib[id]);
	surf.bankw = G_028C74_BANK_WIDTH(track->cb_color_attrib[id]);
	surf.bankh = G_028C74_BANK_HEIGHT(track->cb_color_attrib[id]);
	surf.mtilea = G_028C74_MACRO_TILE_ASPECT(track->cb_color_attrib[id]);
	surf.nsamples = 1;

	अगर (!r600_fmt_is_valid_color(surf.क्रमmat)) अणु
		dev_warn(p->dev, "%s:%d cb invalid format %d for %d (0x%08x)\n",
			 __func__, __LINE__, surf.क्रमmat,
			id, track->cb_color_info[id]);
		वापस -EINVAL;
	पूर्ण

	r = evergreen_surface_value_conv_check(p, &surf, "cb");
	अगर (r) अणु
		वापस r;
	पूर्ण

	r = evergreen_surface_check(p, &surf, "cb");
	अगर (r) अणु
		dev_warn(p->dev, "%s:%d cb[%d] invalid (0x%08x 0x%08x 0x%08x 0x%08x)\n",
			 __func__, __LINE__, id, track->cb_color_pitch[id],
			 track->cb_color_slice[id], track->cb_color_attrib[id],
			 track->cb_color_info[id]);
		वापस r;
	पूर्ण

	offset = track->cb_color_bo_offset[id] << 8;
	अगर (offset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d cb[%d] bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, id, offset, surf.base_align);
		वापस -EINVAL;
	पूर्ण

	offset += surf.layer_size * mslice;
	अगर (offset > radeon_bo_size(track->cb_color_bo[id])) अणु
		/* old ddx are broken they allocate bo with w*h*bpp but
		 * program slice with ALIGN(h, 8), catch this and patch
		 * command stream.
		 */
		अगर (!surf.mode) अणु
			uपूर्णांक32_t *ib = p->ib.ptr;
			अचिन्हित दीर्घ पंचांगp, nby, bsize, size, min = 0;

			/* find the height the ddx wants */
			अगर (surf.nby > 8) अणु
				min = surf.nby - 8;
			पूर्ण
			bsize = radeon_bo_size(track->cb_color_bo[id]);
			पंचांगp = track->cb_color_bo_offset[id] << 8;
			क्रम (nby = surf.nby; nby > min; nby--) अणु
				size = nby * surf.nbx * surf.bpe * surf.nsamples;
				अगर ((पंचांगp + size * mslice) <= bsize) अणु
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (nby > min) अणु
				surf.nby = nby;
				slice = ((nby * surf.nbx) / 64) - 1;
				अगर (!evergreen_surface_check(p, &surf, "cb")) अणु
					/* check अगर this one works */
					पंचांगp += surf.layer_size * mslice;
					अगर (पंचांगp <= bsize) अणु
						ib[track->cb_color_slice_idx[id]] = slice;
						जाओ old_ddx_ok;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		dev_warn(p->dev, "%s:%d cb[%d] bo too small (layer size %d, "
			 "offset %d, max layer %d, bo size %ld, slice %d)\n",
			 __func__, __LINE__, id, surf.layer_size,
			track->cb_color_bo_offset[id] << 8, mslice,
			radeon_bo_size(track->cb_color_bo[id]), slice);
		dev_warn(p->dev, "%s:%d problematic surf: (%d %d) (%d %d %d %d %d %d %d)\n",
			 __func__, __LINE__, surf.nbx, surf.nby,
			surf.mode, surf.bpe, surf.nsamples,
			surf.bankw, surf.bankh,
			surf.tsplit, surf.mtilea);
		वापस -EINVAL;
	पूर्ण
old_ddx_ok:

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_validate_htile(काष्ठा radeon_cs_parser *p,
						अचिन्हित nbx, अचिन्हित nby)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	अचिन्हित दीर्घ size;

	अगर (track->htile_bo == शून्य) अणु
		dev_warn(p->dev, "%s:%d htile enabled without htile surface 0x%08x\n",
				__func__, __LINE__, track->db_z_info);
		वापस -EINVAL;
	पूर्ण

	अगर (G_028ABC_LINEAR(track->htile_surface)) अणु
		/* pitch must be 16 htiles aligned == 16 * 8 pixel aligned */
		nbx = round_up(nbx, 16 * 8);
		/* height is npipes htiles aligned == npipes * 8 pixel aligned */
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
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_validate_stencil(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	काष्ठा eg_surface surf;
	अचिन्हित pitch, slice, mslice;
	अचिन्हित दीर्घ offset;
	पूर्णांक r;

	mslice = G_028008_SLICE_MAX(track->db_depth_view) + 1;
	pitch = G_028058_PITCH_TILE_MAX(track->db_depth_size);
	slice = track->db_depth_slice;
	surf.nbx = (pitch + 1) * 8;
	surf.nby = ((slice + 1) * 64) / surf.nbx;
	surf.mode = G_028040_ARRAY_MODE(track->db_z_info);
	surf.क्रमmat = G_028044_FORMAT(track->db_s_info);
	surf.tsplit = G_028044_TILE_SPLIT(track->db_s_info);
	surf.nbanks = G_028040_NUM_BANKS(track->db_z_info);
	surf.bankw = G_028040_BANK_WIDTH(track->db_z_info);
	surf.bankh = G_028040_BANK_HEIGHT(track->db_z_info);
	surf.mtilea = G_028040_MACRO_TILE_ASPECT(track->db_z_info);
	surf.nsamples = 1;

	अगर (surf.क्रमmat != 1) अणु
		dev_warn(p->dev, "%s:%d stencil invalid format %d\n",
			 __func__, __LINE__, surf.क्रमmat);
		वापस -EINVAL;
	पूर्ण
	/* replace by color क्रमmat so we can use same code */
	surf.क्रमmat = V_028C70_COLOR_8;

	r = evergreen_surface_value_conv_check(p, &surf, "stencil");
	अगर (r) अणु
		वापस r;
	पूर्ण

	r = evergreen_surface_check(p, &surf, शून्य);
	अगर (r) अणु
		/* old userspace करोesn't compute proper depth/stencil alignment
		 * check that alignment against a bigger byte per elements and
		 * only report अगर that alignment is wrong too.
		 */
		surf.क्रमmat = V_028C70_COLOR_8_8_8_8;
		r = evergreen_surface_check(p, &surf, "stencil");
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d stencil invalid (0x%08x 0x%08x 0x%08x 0x%08x)\n",
				 __func__, __LINE__, track->db_depth_size,
				 track->db_depth_slice, track->db_s_info, track->db_z_info);
		पूर्ण
		वापस r;
	पूर्ण

	offset = track->db_s_पढ़ो_offset << 8;
	अगर (offset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d stencil read bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, offset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	offset += surf.layer_size * mslice;
	अगर (offset > radeon_bo_size(track->db_s_पढ़ो_bo)) अणु
		dev_warn(p->dev, "%s:%d stencil read bo too small (layer size %d, "
			 "offset %ld, max layer %d, bo size %ld)\n",
			 __func__, __LINE__, surf.layer_size,
			(अचिन्हित दीर्घ)track->db_s_पढ़ो_offset << 8, mslice,
			radeon_bo_size(track->db_s_पढ़ो_bo));
		dev_warn(p->dev, "%s:%d stencil invalid (0x%08x 0x%08x 0x%08x 0x%08x)\n",
			 __func__, __LINE__, track->db_depth_size,
			 track->db_depth_slice, track->db_s_info, track->db_z_info);
		वापस -EINVAL;
	पूर्ण

	offset = track->db_s_ग_लिखो_offset << 8;
	अगर (offset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d stencil write bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, offset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	offset += surf.layer_size * mslice;
	अगर (offset > radeon_bo_size(track->db_s_ग_लिखो_bo)) अणु
		dev_warn(p->dev, "%s:%d stencil write bo too small (layer size %d, "
			 "offset %ld, max layer %d, bo size %ld)\n",
			 __func__, __LINE__, surf.layer_size,
			(अचिन्हित दीर्घ)track->db_s_ग_लिखो_offset << 8, mslice,
			radeon_bo_size(track->db_s_ग_लिखो_bo));
		वापस -EINVAL;
	पूर्ण

	/* hyperz */
	अगर (G_028040_TILE_SURFACE_ENABLE(track->db_z_info)) अणु
		r = evergreen_cs_track_validate_htile(p, surf.nbx, surf.nby);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_validate_depth(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	काष्ठा eg_surface surf;
	अचिन्हित pitch, slice, mslice;
	अचिन्हित दीर्घ offset;
	पूर्णांक r;

	mslice = G_028008_SLICE_MAX(track->db_depth_view) + 1;
	pitch = G_028058_PITCH_TILE_MAX(track->db_depth_size);
	slice = track->db_depth_slice;
	surf.nbx = (pitch + 1) * 8;
	surf.nby = ((slice + 1) * 64) / surf.nbx;
	surf.mode = G_028040_ARRAY_MODE(track->db_z_info);
	surf.क्रमmat = G_028040_FORMAT(track->db_z_info);
	surf.tsplit = G_028040_TILE_SPLIT(track->db_z_info);
	surf.nbanks = G_028040_NUM_BANKS(track->db_z_info);
	surf.bankw = G_028040_BANK_WIDTH(track->db_z_info);
	surf.bankh = G_028040_BANK_HEIGHT(track->db_z_info);
	surf.mtilea = G_028040_MACRO_TILE_ASPECT(track->db_z_info);
	surf.nsamples = 1;

	चयन (surf.क्रमmat) अणु
	हाल V_028040_Z_16:
		surf.क्रमmat = V_028C70_COLOR_16;
		अवरोध;
	हाल V_028040_Z_24:
	हाल V_028040_Z_32_FLOAT:
		surf.क्रमmat = V_028C70_COLOR_8_8_8_8;
		अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d depth invalid format %d\n",
			 __func__, __LINE__, surf.क्रमmat);
		वापस -EINVAL;
	पूर्ण

	r = evergreen_surface_value_conv_check(p, &surf, "depth");
	अगर (r) अणु
		dev_warn(p->dev, "%s:%d depth invalid (0x%08x 0x%08x 0x%08x)\n",
			 __func__, __LINE__, track->db_depth_size,
			 track->db_depth_slice, track->db_z_info);
		वापस r;
	पूर्ण

	r = evergreen_surface_check(p, &surf, "depth");
	अगर (r) अणु
		dev_warn(p->dev, "%s:%d depth invalid (0x%08x 0x%08x 0x%08x)\n",
			 __func__, __LINE__, track->db_depth_size,
			 track->db_depth_slice, track->db_z_info);
		वापस r;
	पूर्ण

	offset = track->db_z_पढ़ो_offset << 8;
	अगर (offset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d stencil read bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, offset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	offset += surf.layer_size * mslice;
	अगर (offset > radeon_bo_size(track->db_z_पढ़ो_bo)) अणु
		dev_warn(p->dev, "%s:%d depth read bo too small (layer size %d, "
			 "offset %ld, max layer %d, bo size %ld)\n",
			 __func__, __LINE__, surf.layer_size,
			(अचिन्हित दीर्घ)track->db_z_पढ़ो_offset << 8, mslice,
			radeon_bo_size(track->db_z_पढ़ो_bo));
		वापस -EINVAL;
	पूर्ण

	offset = track->db_z_ग_लिखो_offset << 8;
	अगर (offset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d stencil write bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, offset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	offset += surf.layer_size * mslice;
	अगर (offset > radeon_bo_size(track->db_z_ग_लिखो_bo)) अणु
		dev_warn(p->dev, "%s:%d depth write bo too small (layer size %d, "
			 "offset %ld, max layer %d, bo size %ld)\n",
			 __func__, __LINE__, surf.layer_size,
			(अचिन्हित दीर्घ)track->db_z_ग_लिखो_offset << 8, mslice,
			radeon_bo_size(track->db_z_ग_लिखो_bo));
		वापस -EINVAL;
	पूर्ण

	/* hyperz */
	अगर (G_028040_TILE_SURFACE_ENABLE(track->db_z_info)) अणु
		r = evergreen_cs_track_validate_htile(p, surf.nbx, surf.nby);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_validate_texture(काष्ठा radeon_cs_parser *p,
					       काष्ठा radeon_bo *texture,
					       काष्ठा radeon_bo *mipmap,
					       अचिन्हित idx)
अणु
	काष्ठा eg_surface surf;
	अचिन्हित दीर्घ toffset, moffset;
	अचिन्हित dim, llevel, mslice, width, height, depth, i;
	u32 texdw[8];
	पूर्णांक r;

	texdw[0] = radeon_get_ib_value(p, idx + 0);
	texdw[1] = radeon_get_ib_value(p, idx + 1);
	texdw[2] = radeon_get_ib_value(p, idx + 2);
	texdw[3] = radeon_get_ib_value(p, idx + 3);
	texdw[4] = radeon_get_ib_value(p, idx + 4);
	texdw[5] = radeon_get_ib_value(p, idx + 5);
	texdw[6] = radeon_get_ib_value(p, idx + 6);
	texdw[7] = radeon_get_ib_value(p, idx + 7);
	dim = G_030000_DIM(texdw[0]);
	llevel = G_030014_LAST_LEVEL(texdw[5]);
	mslice = G_030014_LAST_ARRAY(texdw[5]) + 1;
	width = G_030000_TEX_WIDTH(texdw[0]) + 1;
	height =  G_030004_TEX_HEIGHT(texdw[1]) + 1;
	depth = G_030004_TEX_DEPTH(texdw[1]) + 1;
	surf.क्रमmat = G_03001C_DATA_FORMAT(texdw[7]);
	surf.nbx = (G_030000_PITCH(texdw[0]) + 1) * 8;
	surf.nbx = r600_fmt_get_nblocksx(surf.क्रमmat, surf.nbx);
	surf.nby = r600_fmt_get_nblocksy(surf.क्रमmat, height);
	surf.mode = G_030004_ARRAY_MODE(texdw[1]);
	surf.tsplit = G_030018_TILE_SPLIT(texdw[6]);
	surf.nbanks = G_03001C_NUM_BANKS(texdw[7]);
	surf.bankw = G_03001C_BANK_WIDTH(texdw[7]);
	surf.bankh = G_03001C_BANK_HEIGHT(texdw[7]);
	surf.mtilea = G_03001C_MACRO_TILE_ASPECT(texdw[7]);
	surf.nsamples = 1;
	toffset = texdw[2] << 8;
	moffset = texdw[3] << 8;

	अगर (!r600_fmt_is_valid_texture(surf.क्रमmat, p->family)) अणु
		dev_warn(p->dev, "%s:%d texture invalid format %d\n",
			 __func__, __LINE__, surf.क्रमmat);
		वापस -EINVAL;
	पूर्ण
	चयन (dim) अणु
	हाल V_030000_SQ_TEX_DIM_1D:
	हाल V_030000_SQ_TEX_DIM_2D:
	हाल V_030000_SQ_TEX_DIM_CUBEMAP:
	हाल V_030000_SQ_TEX_DIM_1D_ARRAY:
	हाल V_030000_SQ_TEX_DIM_2D_ARRAY:
		depth = 1;
		अवरोध;
	हाल V_030000_SQ_TEX_DIM_2D_MSAA:
	हाल V_030000_SQ_TEX_DIM_2D_ARRAY_MSAA:
		surf.nsamples = 1 << llevel;
		llevel = 0;
		depth = 1;
		अवरोध;
	हाल V_030000_SQ_TEX_DIM_3D:
		अवरोध;
	शेष:
		dev_warn(p->dev, "%s:%d texture invalid dimension %d\n",
			 __func__, __LINE__, dim);
		वापस -EINVAL;
	पूर्ण

	r = evergreen_surface_value_conv_check(p, &surf, "texture");
	अगर (r) अणु
		वापस r;
	पूर्ण

	/* align height */
	evergreen_surface_check(p, &surf, शून्य);
	surf.nby = ALIGN(surf.nby, surf.halign);

	r = evergreen_surface_check(p, &surf, "texture");
	अगर (r) अणु
		dev_warn(p->dev, "%s:%d texture invalid 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
			 __func__, __LINE__, texdw[0], texdw[1], texdw[4],
			 texdw[5], texdw[6], texdw[7]);
		वापस r;
	पूर्ण

	/* check texture size */
	अगर (toffset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d texture bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, toffset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	अगर (surf.nsamples <= 1 && moffset & (surf.base_align - 1)) अणु
		dev_warn(p->dev, "%s:%d mipmap bo base %ld not aligned with %ld\n",
			 __func__, __LINE__, moffset, surf.base_align);
		वापस -EINVAL;
	पूर्ण
	अगर (dim == SQ_TEX_DIM_3D) अणु
		toffset += surf.layer_size * depth;
	पूर्ण अन्यथा अणु
		toffset += surf.layer_size * mslice;
	पूर्ण
	अगर (toffset > radeon_bo_size(texture)) अणु
		dev_warn(p->dev, "%s:%d texture bo too small (layer size %d, "
			 "offset %ld, max layer %d, depth %d, bo size %ld) (%d %d)\n",
			 __func__, __LINE__, surf.layer_size,
			(अचिन्हित दीर्घ)texdw[2] << 8, mslice,
			depth, radeon_bo_size(texture),
			surf.nbx, surf.nby);
		वापस -EINVAL;
	पूर्ण

	अगर (!mipmap) अणु
		अगर (llevel) अणु
			dev_warn(p->dev, "%s:%i got NULL MIP_ADDRESS relocation\n",
				 __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस 0; /* everything's ok */
		पूर्ण
	पूर्ण

	/* check mipmap size */
	क्रम (i = 1; i <= llevel; i++) अणु
		अचिन्हित w, h, d;

		w = r600_mip_minअगरy(width, i);
		h = r600_mip_minअगरy(height, i);
		d = r600_mip_minअगरy(depth, i);
		surf.nbx = r600_fmt_get_nblocksx(surf.क्रमmat, w);
		surf.nby = r600_fmt_get_nblocksy(surf.क्रमmat, h);

		चयन (surf.mode) अणु
		हाल ARRAY_2D_TILED_THIN1:
			अगर (surf.nbx < surf.palign || surf.nby < surf.halign) अणु
				surf.mode = ARRAY_1D_TILED_THIN1;
			पूर्ण
			/* recompute alignment */
			evergreen_surface_check(p, &surf, शून्य);
			अवरोध;
		हाल ARRAY_LINEAR_GENERAL:
		हाल ARRAY_LINEAR_ALIGNED:
		हाल ARRAY_1D_TILED_THIN1:
			अवरोध;
		शेष:
			dev_warn(p->dev, "%s:%d invalid array mode %d\n",
				 __func__, __LINE__, surf.mode);
			वापस -EINVAL;
		पूर्ण
		surf.nbx = ALIGN(surf.nbx, surf.palign);
		surf.nby = ALIGN(surf.nby, surf.halign);

		r = evergreen_surface_check(p, &surf, "mipmap");
		अगर (r) अणु
			वापस r;
		पूर्ण

		अगर (dim == SQ_TEX_DIM_3D) अणु
			moffset += surf.layer_size * d;
		पूर्ण अन्यथा अणु
			moffset += surf.layer_size * mslice;
		पूर्ण
		अगर (moffset > radeon_bo_size(mipmap)) अणु
			dev_warn(p->dev, "%s:%d mipmap [%d] bo too small (layer size %d, "
					"offset %ld, coffset %ld, max layer %d, depth %d, "
					"bo size %ld) level0 (%d %d %d)\n",
					__func__, __LINE__, i, surf.layer_size,
					(अचिन्हित दीर्घ)texdw[3] << 8, moffset, mslice,
					d, radeon_bo_size(mipmap),
					width, height, depth);
			dev_warn(p->dev, "%s:%d problematic surf: (%d %d) (%d %d %d %d %d %d %d)\n",
				 __func__, __LINE__, surf.nbx, surf.nby,
				surf.mode, surf.bpe, surf.nsamples,
				surf.bankw, surf.bankh,
				surf.tsplit, surf.mtilea);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cs_track_check(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	अचिन्हित पंचांगp, i;
	पूर्णांक r;
	अचिन्हित buffer_mask = 0;

	/* check streamout */
	अगर (track->streamout_dirty && track->vgt_strmout_config) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर (track->vgt_strmout_config & (1 << i)) अणु
				buffer_mask |= (track->vgt_strmout_buffer_config >> (i * 4)) & 0xf;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			अगर (buffer_mask & (1 << i)) अणु
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

	/* check that we have a cb क्रम each enabled target
	 */
	अगर (track->cb_dirty) अणु
		पंचांगp = track->cb_target_mask;
		क्रम (i = 0; i < 8; i++) अणु
			u32 क्रमmat = G_028C70_FORMAT(track->cb_color_info[i]);

			अगर (क्रमmat != V_028C70_COLOR_INVALID &&
			    (पंचांगp >> (i * 4)) & 0xF) अणु
				/* at least one component is enabled */
				अगर (track->cb_color_bo[i] == शून्य) अणु
					dev_warn(p->dev, "%s:%d mask 0x%08X | 0x%08X no cb for %d\n",
						__func__, __LINE__, track->cb_target_mask, track->cb_shader_mask, i);
					वापस -EINVAL;
				पूर्ण
				/* check cb */
				r = evergreen_cs_track_validate_cb(p, i);
				अगर (r) अणु
					वापस r;
				पूर्ण
			पूर्ण
		पूर्ण
		track->cb_dirty = false;
	पूर्ण

	अगर (track->db_dirty) अणु
		/* Check stencil buffer */
		अगर (G_028044_FORMAT(track->db_s_info) != V_028044_STENCIL_INVALID &&
		    G_028800_STENCIL_ENABLE(track->db_depth_control)) अणु
			r = evergreen_cs_track_validate_stencil(p);
			अगर (r)
				वापस r;
		पूर्ण
		/* Check depth buffer */
		अगर (G_028040_FORMAT(track->db_z_info) != V_028040_Z_INVALID &&
		    G_028800_Z_ENABLE(track->db_depth_control)) अणु
			r = evergreen_cs_track_validate_depth(p);
			अगर (r)
				वापस r;
		पूर्ण
		track->db_dirty = false;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * evergreen_cs_packet_parse_vline() - parse userspace VLINE packet
 * @p:		parser काष्ठाure holding parsing context.
 *
 * This is an Evergreen(+)-specअगरic function क्रम parsing VLINE packets.
 * Real work is करोne by r600_cs_common_vline_parse function.
 * Here we just set up ASIC-specअगरic रेजिस्टर table and call
 * the common implementation function.
 */
अटल पूर्णांक evergreen_cs_packet_parse_vline(काष्ठा radeon_cs_parser *p)
अणु

	अटल uपूर्णांक32_t vline_start_end[6] = अणु
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC0_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC1_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC2_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC3_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC4_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC5_REGISTER_OFFSET
	पूर्ण;
	अटल uपूर्णांक32_t vline_status[6] = अणु
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC0_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC1_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC2_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC3_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC4_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC5_REGISTER_OFFSET
	पूर्ण;

	वापस r600_cs_common_vline_parse(p, vline_start_end, vline_status);
पूर्ण

अटल पूर्णांक evergreen_packet0_check(काष्ठा radeon_cs_parser *p,
				   काष्ठा radeon_cs_packet *pkt,
				   अचिन्हित idx, अचिन्हित reg)
अणु
	पूर्णांक r;

	चयन (reg) अणु
	हाल EVERGREEN_VLINE_START_END:
		r = evergreen_cs_packet_parse_vline(p);
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

अटल पूर्णांक evergreen_cs_parse_packet0(काष्ठा radeon_cs_parser *p,
				      काष्ठा radeon_cs_packet *pkt)
अणु
	अचिन्हित reg, i;
	अचिन्हित idx;
	पूर्णांक r;

	idx = pkt->idx + 1;
	reg = pkt->reg;
	क्रम (i = 0; i <= pkt->count; i++, idx++, reg += 4) अणु
		r = evergreen_packet0_check(p, pkt, idx, reg);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * evergreen_cs_handle_reg() - process रेजिस्टरs that need special handling.
 * @p: parser काष्ठाure holding parsing context
 * @reg: रेजिस्टर we are testing
 * @idx: index पूर्णांकo the cs buffer
 */
अटल पूर्णांक evergreen_cs_handle_reg(काष्ठा radeon_cs_parser *p, u32 reg, u32 idx)
अणु
	काष्ठा evergreen_cs_track *track = (काष्ठा evergreen_cs_track *)p->track;
	काष्ठा radeon_bo_list *reloc;
	u32 पंचांगp, *ib;
	पूर्णांक r;

	ib = p->ib.ptr;
	चयन (reg) अणु
	/* क्रमce following reg to 0 in an attempt to disable out buffer
	 * which will need us to better understand how it works to perक्रमm
	 * security check on it (Jerome)
	 */
	हाल SQ_ESGS_RING_SIZE:
	हाल SQ_GSVS_RING_SIZE:
	हाल SQ_ESTMP_RING_SIZE:
	हाल SQ_GSTMP_RING_SIZE:
	हाल SQ_HSTMP_RING_SIZE:
	हाल SQ_LSTMP_RING_SIZE:
	हाल SQ_PSTMP_RING_SIZE:
	हाल SQ_VSTMP_RING_SIZE:
	हाल SQ_ESGS_RING_ITEMSIZE:
	हाल SQ_ESTMP_RING_ITEMSIZE:
	हाल SQ_GSTMP_RING_ITEMSIZE:
	हाल SQ_GSVS_RING_ITEMSIZE:
	हाल SQ_GS_VERT_ITEMSIZE:
	हाल SQ_GS_VERT_ITEMSIZE_1:
	हाल SQ_GS_VERT_ITEMSIZE_2:
	हाल SQ_GS_VERT_ITEMSIZE_3:
	हाल SQ_GSVS_RING_OFFSET_1:
	हाल SQ_GSVS_RING_OFFSET_2:
	हाल SQ_GSVS_RING_OFFSET_3:
	हाल SQ_HSTMP_RING_ITEMSIZE:
	हाल SQ_LSTMP_RING_ITEMSIZE:
	हाल SQ_PSTMP_RING_ITEMSIZE:
	हाल SQ_VSTMP_RING_ITEMSIZE:
	हाल VGT_TF_RING_SIZE:
		/* get value to populate the IB करोn't हटाओ */
		/*पंचांगp =radeon_get_ib_value(p, idx);
		  ib[idx] = 0;*/
		अवरोध;
	हाल SQ_ESGS_RING_BASE:
	हाल SQ_GSVS_RING_BASE:
	हाल SQ_ESTMP_RING_BASE:
	हाल SQ_GSTMP_RING_BASE:
	हाल SQ_HSTMP_RING_BASE:
	हाल SQ_LSTMP_RING_BASE:
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
	हाल DB_DEPTH_CONTROL:
		track->db_depth_control = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल CAYMAN_DB_EQAA:
		अगर (p->rdev->family < CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल CAYMAN_DB_DEPTH_INFO:
		अगर (p->rdev->family < CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल DB_Z_INFO:
		track->db_z_info = radeon_get_ib_value(p, idx);
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				dev_warn(p->dev, "bad SET_CONTEXT_REG "
						"0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			ib[idx] &= ~Z_ARRAY_MODE(0xf);
			track->db_z_info &= ~Z_ARRAY_MODE(0xf);
			ib[idx] |= Z_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
			track->db_z_info |= Z_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
				अचिन्हित bankw, bankh, mtaspect, tile_split;

				evergreen_tiling_fields(reloc->tiling_flags,
							&bankw, &bankh, &mtaspect,
							&tile_split);
				ib[idx] |= DB_NUM_BANKS(evergreen_cs_get_num_banks(track->nbanks));
				ib[idx] |= DB_TILE_SPLIT(tile_split) |
						DB_BANK_WIDTH(bankw) |
						DB_BANK_HEIGHT(bankh) |
						DB_MACRO_TILE_ASPECT(mtaspect);
			पूर्ण
		पूर्ण
		track->db_dirty = true;
		अवरोध;
	हाल DB_STENCIL_INFO:
		track->db_s_info = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल DB_DEPTH_VIEW:
		track->db_depth_view = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल DB_DEPTH_SIZE:
		track->db_depth_size = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल R_02805C_DB_DEPTH_SLICE:
		track->db_depth_slice = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		अवरोध;
	हाल DB_Z_READ_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->db_z_पढ़ो_offset = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_z_पढ़ो_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल DB_Z_WRITE_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->db_z_ग_लिखो_offset = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_z_ग_लिखो_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल DB_STENCIL_READ_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->db_s_पढ़ो_offset = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_s_पढ़ो_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल DB_STENCIL_WRITE_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->db_s_ग_लिखो_offset = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_s_ग_लिखो_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल VGT_STRMOUT_CONFIG:
		track->vgt_strmout_config = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		अवरोध;
	हाल VGT_STRMOUT_BUFFER_CONFIG:
		track->vgt_strmout_buffer_config = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		अवरोध;
	हाल VGT_STRMOUT_BUFFER_BASE_0:
	हाल VGT_STRMOUT_BUFFER_BASE_1:
	हाल VGT_STRMOUT_BUFFER_BASE_2:
	हाल VGT_STRMOUT_BUFFER_BASE_3:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = (reg - VGT_STRMOUT_BUFFER_BASE_0) / 16;
		track->vgt_strmout_bo_offset[पंचांगp] = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->vgt_strmout_bo[पंचांगp] = reloc->robj;
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
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "missing reloc for CP_COHER_BASE "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल CB_TARGET_MASK:
		track->cb_target_mask = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल CB_SHADER_MASK:
		track->cb_shader_mask = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल PA_SC_AA_CONFIG:
		अगर (p->rdev->family >= CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = radeon_get_ib_value(p, idx) & MSAA_NUM_SAMPLES_MASK;
		track->nsamples = 1 << पंचांगp;
		अवरोध;
	हाल CAYMAN_PA_SC_AA_CONFIG:
		अगर (p->rdev->family < CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = radeon_get_ib_value(p, idx) & CAYMAN_MSAA_NUM_SAMPLES_MASK;
		track->nsamples = 1 << पंचांगp;
		अवरोध;
	हाल CB_COLOR0_VIEW:
	हाल CB_COLOR1_VIEW:
	हाल CB_COLOR2_VIEW:
	हाल CB_COLOR3_VIEW:
	हाल CB_COLOR4_VIEW:
	हाल CB_COLOR5_VIEW:
	हाल CB_COLOR6_VIEW:
	हाल CB_COLOR7_VIEW:
		पंचांगp = (reg - CB_COLOR0_VIEW) / 0x3c;
		track->cb_color_view[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_VIEW:
	हाल CB_COLOR9_VIEW:
	हाल CB_COLOR10_VIEW:
	हाल CB_COLOR11_VIEW:
		पंचांगp = ((reg - CB_COLOR8_VIEW) / 0x1c) + 8;
		track->cb_color_view[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR0_INFO:
	हाल CB_COLOR1_INFO:
	हाल CB_COLOR2_INFO:
	हाल CB_COLOR3_INFO:
	हाल CB_COLOR4_INFO:
	हाल CB_COLOR5_INFO:
	हाल CB_COLOR6_INFO:
	हाल CB_COLOR7_INFO:
		पंचांगp = (reg - CB_COLOR0_INFO) / 0x3c;
		track->cb_color_info[पंचांगp] = radeon_get_ib_value(p, idx);
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				dev_warn(p->dev, "bad SET_CONTEXT_REG "
						"0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			ib[idx] |= CB_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
			track->cb_color_info[पंचांगp] |= CB_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
		पूर्ण
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_INFO:
	हाल CB_COLOR9_INFO:
	हाल CB_COLOR10_INFO:
	हाल CB_COLOR11_INFO:
		पंचांगp = ((reg - CB_COLOR8_INFO) / 0x1c) + 8;
		track->cb_color_info[पंचांगp] = radeon_get_ib_value(p, idx);
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				dev_warn(p->dev, "bad SET_CONTEXT_REG "
						"0x%04X\n", reg);
				वापस -EINVAL;
			पूर्ण
			ib[idx] |= CB_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
			track->cb_color_info[पंचांगp] |= CB_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
		पूर्ण
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR0_PITCH:
	हाल CB_COLOR1_PITCH:
	हाल CB_COLOR2_PITCH:
	हाल CB_COLOR3_PITCH:
	हाल CB_COLOR4_PITCH:
	हाल CB_COLOR5_PITCH:
	हाल CB_COLOR6_PITCH:
	हाल CB_COLOR7_PITCH:
		पंचांगp = (reg - CB_COLOR0_PITCH) / 0x3c;
		track->cb_color_pitch[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_PITCH:
	हाल CB_COLOR9_PITCH:
	हाल CB_COLOR10_PITCH:
	हाल CB_COLOR11_PITCH:
		पंचांगp = ((reg - CB_COLOR8_PITCH) / 0x1c) + 8;
		track->cb_color_pitch[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR0_SLICE:
	हाल CB_COLOR1_SLICE:
	हाल CB_COLOR2_SLICE:
	हाल CB_COLOR3_SLICE:
	हाल CB_COLOR4_SLICE:
	हाल CB_COLOR5_SLICE:
	हाल CB_COLOR6_SLICE:
	हाल CB_COLOR7_SLICE:
		पंचांगp = (reg - CB_COLOR0_SLICE) / 0x3c;
		track->cb_color_slice[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_color_slice_idx[पंचांगp] = idx;
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_SLICE:
	हाल CB_COLOR9_SLICE:
	हाल CB_COLOR10_SLICE:
	हाल CB_COLOR11_SLICE:
		पंचांगp = ((reg - CB_COLOR8_SLICE) / 0x1c) + 8;
		track->cb_color_slice[पंचांगp] = radeon_get_ib_value(p, idx);
		track->cb_color_slice_idx[पंचांगp] = idx;
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR0_ATTRIB:
	हाल CB_COLOR1_ATTRIB:
	हाल CB_COLOR2_ATTRIB:
	हाल CB_COLOR3_ATTRIB:
	हाल CB_COLOR4_ATTRIB:
	हाल CB_COLOR5_ATTRIB:
	हाल CB_COLOR6_ATTRIB:
	हाल CB_COLOR7_ATTRIB:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
				अचिन्हित bankw, bankh, mtaspect, tile_split;

				evergreen_tiling_fields(reloc->tiling_flags,
							&bankw, &bankh, &mtaspect,
							&tile_split);
				ib[idx] |= CB_NUM_BANKS(evergreen_cs_get_num_banks(track->nbanks));
				ib[idx] |= CB_TILE_SPLIT(tile_split) |
					   CB_BANK_WIDTH(bankw) |
					   CB_BANK_HEIGHT(bankh) |
					   CB_MACRO_TILE_ASPECT(mtaspect);
			पूर्ण
		पूर्ण
		पंचांगp = ((reg - CB_COLOR0_ATTRIB) / 0x3c);
		track->cb_color_attrib[पंचांगp] = ib[idx];
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_ATTRIB:
	हाल CB_COLOR9_ATTRIB:
	हाल CB_COLOR10_ATTRIB:
	हाल CB_COLOR11_ATTRIB:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
				अचिन्हित bankw, bankh, mtaspect, tile_split;

				evergreen_tiling_fields(reloc->tiling_flags,
							&bankw, &bankh, &mtaspect,
							&tile_split);
				ib[idx] |= CB_NUM_BANKS(evergreen_cs_get_num_banks(track->nbanks));
				ib[idx] |= CB_TILE_SPLIT(tile_split) |
					   CB_BANK_WIDTH(bankw) |
					   CB_BANK_HEIGHT(bankh) |
					   CB_MACRO_TILE_ASPECT(mtaspect);
			पूर्ण
		पूर्ण
		पंचांगp = ((reg - CB_COLOR8_ATTRIB) / 0x1c) + 8;
		track->cb_color_attrib[पंचांगp] = ib[idx];
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR0_FMASK:
	हाल CB_COLOR1_FMASK:
	हाल CB_COLOR2_FMASK:
	हाल CB_COLOR3_FMASK:
	हाल CB_COLOR4_FMASK:
	हाल CB_COLOR5_FMASK:
	हाल CB_COLOR6_FMASK:
	हाल CB_COLOR7_FMASK:
		पंचांगp = (reg - CB_COLOR0_FMASK) / 0x3c;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_fmask_bo[पंचांगp] = reloc->robj;
		अवरोध;
	हाल CB_COLOR0_CMASK:
	हाल CB_COLOR1_CMASK:
	हाल CB_COLOR2_CMASK:
	हाल CB_COLOR3_CMASK:
	हाल CB_COLOR4_CMASK:
	हाल CB_COLOR5_CMASK:
	हाल CB_COLOR6_CMASK:
	हाल CB_COLOR7_CMASK:
		पंचांगp = (reg - CB_COLOR0_CMASK) / 0x3c;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_cmask_bo[पंचांगp] = reloc->robj;
		अवरोध;
	हाल CB_COLOR0_FMASK_SLICE:
	हाल CB_COLOR1_FMASK_SLICE:
	हाल CB_COLOR2_FMASK_SLICE:
	हाल CB_COLOR3_FMASK_SLICE:
	हाल CB_COLOR4_FMASK_SLICE:
	हाल CB_COLOR5_FMASK_SLICE:
	हाल CB_COLOR6_FMASK_SLICE:
	हाल CB_COLOR7_FMASK_SLICE:
		पंचांगp = (reg - CB_COLOR0_FMASK_SLICE) / 0x3c;
		track->cb_color_fmask_slice[पंचांगp] = radeon_get_ib_value(p, idx);
		अवरोध;
	हाल CB_COLOR0_CMASK_SLICE:
	हाल CB_COLOR1_CMASK_SLICE:
	हाल CB_COLOR2_CMASK_SLICE:
	हाल CB_COLOR3_CMASK_SLICE:
	हाल CB_COLOR4_CMASK_SLICE:
	हाल CB_COLOR5_CMASK_SLICE:
	हाल CB_COLOR6_CMASK_SLICE:
	हाल CB_COLOR7_CMASK_SLICE:
		पंचांगp = (reg - CB_COLOR0_CMASK_SLICE) / 0x3c;
		track->cb_color_cmask_slice[पंचांगp] = radeon_get_ib_value(p, idx);
		अवरोध;
	हाल CB_COLOR0_BASE:
	हाल CB_COLOR1_BASE:
	हाल CB_COLOR2_BASE:
	हाल CB_COLOR3_BASE:
	हाल CB_COLOR4_BASE:
	हाल CB_COLOR5_BASE:
	हाल CB_COLOR6_BASE:
	हाल CB_COLOR7_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = (reg - CB_COLOR0_BASE) / 0x3c;
		track->cb_color_bo_offset[पंचांगp] = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_bo[पंचांगp] = reloc->robj;
		track->cb_dirty = true;
		अवरोध;
	हाल CB_COLOR8_BASE:
	हाल CB_COLOR9_BASE:
	हाल CB_COLOR10_BASE:
	हाल CB_COLOR11_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = ((reg - CB_COLOR8_BASE) / 0x1c) + 8;
		track->cb_color_bo_offset[पंचांगp] = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_bo[पंचांगp] = reloc->robj;
		track->cb_dirty = true;
		अवरोध;
	हाल DB_HTILE_DATA_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		track->htile_offset = radeon_get_ib_value(p, idx);
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->htile_bo = reloc->robj;
		track->db_dirty = true;
		अवरोध;
	हाल DB_HTILE_SURFACE:
		/* 8x8 only */
		track->htile_surface = radeon_get_ib_value(p, idx);
		/* क्रमce 8x8 htile width and height */
		ib[idx] |= 3;
		track->db_dirty = true;
		अवरोध;
	हाल CB_IMMED0_BASE:
	हाल CB_IMMED1_BASE:
	हाल CB_IMMED2_BASE:
	हाल CB_IMMED3_BASE:
	हाल CB_IMMED4_BASE:
	हाल CB_IMMED5_BASE:
	हाल CB_IMMED6_BASE:
	हाल CB_IMMED7_BASE:
	हाल CB_IMMED8_BASE:
	हाल CB_IMMED9_BASE:
	हाल CB_IMMED10_BASE:
	हाल CB_IMMED11_BASE:
	हाल SQ_PGM_START_FS:
	हाल SQ_PGM_START_ES:
	हाल SQ_PGM_START_VS:
	हाल SQ_PGM_START_GS:
	हाल SQ_PGM_START_PS:
	हाल SQ_PGM_START_HS:
	हाल SQ_PGM_START_LS:
	हाल SQ_CONST_MEM_BASE:
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
	हाल SQ_ALU_CONST_CACHE_HS_0:
	हाल SQ_ALU_CONST_CACHE_HS_1:
	हाल SQ_ALU_CONST_CACHE_HS_2:
	हाल SQ_ALU_CONST_CACHE_HS_3:
	हाल SQ_ALU_CONST_CACHE_HS_4:
	हाल SQ_ALU_CONST_CACHE_HS_5:
	हाल SQ_ALU_CONST_CACHE_HS_6:
	हाल SQ_ALU_CONST_CACHE_HS_7:
	हाल SQ_ALU_CONST_CACHE_HS_8:
	हाल SQ_ALU_CONST_CACHE_HS_9:
	हाल SQ_ALU_CONST_CACHE_HS_10:
	हाल SQ_ALU_CONST_CACHE_HS_11:
	हाल SQ_ALU_CONST_CACHE_HS_12:
	हाल SQ_ALU_CONST_CACHE_HS_13:
	हाल SQ_ALU_CONST_CACHE_HS_14:
	हाल SQ_ALU_CONST_CACHE_HS_15:
	हाल SQ_ALU_CONST_CACHE_LS_0:
	हाल SQ_ALU_CONST_CACHE_LS_1:
	हाल SQ_ALU_CONST_CACHE_LS_2:
	हाल SQ_ALU_CONST_CACHE_LS_3:
	हाल SQ_ALU_CONST_CACHE_LS_4:
	हाल SQ_ALU_CONST_CACHE_LS_5:
	हाल SQ_ALU_CONST_CACHE_LS_6:
	हाल SQ_ALU_CONST_CACHE_LS_7:
	हाल SQ_ALU_CONST_CACHE_LS_8:
	हाल SQ_ALU_CONST_CACHE_LS_9:
	हाल SQ_ALU_CONST_CACHE_LS_10:
	हाल SQ_ALU_CONST_CACHE_LS_11:
	हाल SQ_ALU_CONST_CACHE_LS_12:
	हाल SQ_ALU_CONST_CACHE_LS_13:
	हाल SQ_ALU_CONST_CACHE_LS_14:
	हाल SQ_ALU_CONST_CACHE_LS_15:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल SX_MEMORY_EXPORT_BASE:
		अगर (p->rdev->family >= CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONFIG_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONFIG_REG "
					"0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		अवरोध;
	हाल CAYMAN_SX_SCATTER_EXPORT_BASE:
		अगर (p->rdev->family < CHIP_CAYMAN) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
				 "0x%04X\n", reg);
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
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

/**
 * evergreen_is_safe_reg() - check अगर रेजिस्टर is authorized or not
 * @p: parser काष्ठाure holding parsing context
 * @reg: रेजिस्टर we are testing
 *
 * This function will test against reg_safe_bm and वापस true
 * अगर रेजिस्टर is safe or false otherwise.
 */
अटल अंतरभूत bool evergreen_is_safe_reg(काष्ठा radeon_cs_parser *p, u32 reg)
अणु
	काष्ठा evergreen_cs_track *track = p->track;
	u32 m, i;

	i = (reg >> 7);
	अगर (unlikely(i >= REG_SAFE_BM_SIZE)) अणु
		वापस false;
	पूर्ण
	m = 1 << ((reg >> 2) & 31);
	अगर (!(track->reg_safe_bm[i] & m))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक evergreen_packet3_check(काष्ठा radeon_cs_parser *p,
				   काष्ठा radeon_cs_packet *pkt)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा evergreen_cs_track *track;
	uपूर्णांक32_t *ib;
	अचिन्हित idx;
	अचिन्हित i;
	अचिन्हित start_reg, end_reg, reg;
	पूर्णांक r;
	u32 idx_value;

	track = (काष्ठा evergreen_cs_track *)p->track;
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

		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
	हाल PACKET3_CONTEXT_CONTROL:
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad CONTEXT_CONTROL\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_INDEX_TYPE:
	हाल PACKET3_NUM_INSTANCES:
	हाल PACKET3_CLEAR_STATE:
		अगर (pkt->count) अणु
			DRM_ERROR("bad INDEX_TYPE/NUM_INSTANCES/CLEAR_STATE\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल CAYMAN_PACKET3_DEALLOC_STATE:
		अगर (p->rdev->family < CHIP_CAYMAN) अणु
			DRM_ERROR("bad PACKET3_DEALLOC_STATE\n");
			वापस -EINVAL;
		पूर्ण
		अगर (pkt->count) अणु
			DRM_ERROR("bad INDEX_TYPE/NUM_INSTANCES/CLEAR_STATE\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_INDEX_BASE:
	अणु
		uपूर्णांक64_t offset;

		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad INDEX_BASE\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad INDEX_BASE\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 idx_value +
			 ((u64)(radeon_get_ib_value(p, idx+1) & 0xff) << 32);

		ib[idx+0] = offset;
		ib[idx+1] = upper_32_bits(offset) & 0xff;

		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_INDEX_BUFFER_SIZE:
	अणु
		अगर (pkt->count != 0) अणु
			DRM_ERROR("bad INDEX_BUFFER_SIZE\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_DRAW_INDEX:
	अणु
		uपूर्णांक64_t offset;
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad DRAW_INDEX\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad DRAW_INDEX\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 idx_value +
			 ((u64)(radeon_get_ib_value(p, idx+1) & 0xff) << 32);

		ib[idx+0] = offset;
		ib[idx+1] = upper_32_bits(offset) & 0xff;

		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_DRAW_INDEX_2:
	अणु
		uपूर्णांक64_t offset;

		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad DRAW_INDEX_2\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad DRAW_INDEX_2\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 radeon_get_ib_value(p, idx+1) +
			 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

		ib[idx+1] = offset;
		ib[idx+2] = upper_32_bits(offset) & 0xff;

		r = evergreen_cs_track_check(p);
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
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream %d\n", __func__, __LINE__, idx);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX_MULTI_AUTO:
		अगर (pkt->count != 2) अणु
			DRM_ERROR("bad DRAW_INDEX_MULTI_AUTO\n");
			वापस -EINVAL;
		पूर्ण
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream %d\n", __func__, __LINE__, idx);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX_IMMD:
		अगर (pkt->count < 2) अणु
			DRM_ERROR("bad DRAW_INDEX_IMMD\n");
			वापस -EINVAL;
		पूर्ण
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX_OFFSET:
		अगर (pkt->count != 2) अणु
			DRM_ERROR("bad DRAW_INDEX_OFFSET\n");
			वापस -EINVAL;
		पूर्ण
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DRAW_INDEX_OFFSET_2:
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad DRAW_INDEX_OFFSET_2\n");
			वापस -EINVAL;
		पूर्ण
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_BASE:
	अणु
		/*
		DW 1 HEADER Header of the packet. Shader_Type in bit 1 of the Header will correspond to the shader type of the Load, see Type-3 Packet.
		   2 BASE_INDEX Bits [3:0] BASE_INDEX - Base Index specअगरies which base address is specअगरied in the last two DWs.
		     0001: DX11 Draw_Index_Indirect Patch Table Base: Base address क्रम Draw_Index_Indirect data.
		   3 ADDRESS_LO Bits [31:3] - Lower bits of QWORD-Aligned Address. Bits [2:0] - Reserved
		   4 ADDRESS_HI Bits [31:8] - Reserved. Bits [7:0] - Upper bits of Address [47:32]
		*/
		अगर (pkt->count != 2) अणु
			DRM_ERROR("bad SET_BASE\n");
			वापस -EINVAL;
		पूर्ण

		/* currently only supporting setting indirect draw buffer base address */
		अगर (idx_value != 1) अणु
			DRM_ERROR("bad SET_BASE\n");
			वापस -EINVAL;
		पूर्ण

		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad SET_BASE\n");
			वापस -EINVAL;
		पूर्ण

		track->indirect_draw_buffer_size = radeon_bo_size(reloc->robj);

		ib[idx+1] = reloc->gpu_offset;
		ib[idx+2] = upper_32_bits(reloc->gpu_offset) & 0xff;

		अवरोध;
	पूर्ण
	हाल PACKET3_DRAW_INसूचीECT:
	हाल PACKET3_DRAW_INDEX_INसूचीECT:
	अणु
		u64 size = pkt->opcode == PACKET3_DRAW_INसूचीECT ? 16 : 20;

		/*
		DW 1 HEADER
		   2 DATA_OFFSET Bits [31:0] + byte aligned offset where the required data काष्ठाure starts. Bits 1:0 are zero
		   3 DRAW_INITIATOR Draw Initiator Register. Written to the VGT_DRAW_INITIATOR रेजिस्टर क्रम the asचिन्हित context
		*/
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad DRAW_INDIRECT\n");
			वापस -EINVAL;
		पूर्ण

		अगर (idx_value + size > track->indirect_draw_buffer_size) अणु
			dev_warn(p->dev, "DRAW_INDIRECT buffer too small %u + %llu > %lu\n",
				idx_value, size, track->indirect_draw_buffer_size);
			वापस -EINVAL;
		पूर्ण

		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream\n", __func__, __LINE__);
			वापस r;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_DISPATCH_सूचीECT:
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad DISPATCH_DIRECT\n");
			वापस -EINVAL;
		पूर्ण
		r = evergreen_cs_track_check(p);
		अगर (r) अणु
			dev_warn(p->dev, "%s:%d invalid cmd stream %d\n", __func__, __LINE__, idx);
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_DISPATCH_INसूचीECT:
		अगर (pkt->count != 1) अणु
			DRM_ERROR("bad DISPATCH_INDIRECT\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad DISPATCH_INDIRECT\n");
			वापस -EINVAL;
		पूर्ण
		ib[idx+0] = idx_value + (u32)(reloc->gpu_offset & 0xffffffff);
		r = evergreen_cs_track_check(p);
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

			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				DRM_ERROR("bad WAIT_REG_MEM\n");
				वापस -EINVAL;
			पूर्ण

			offset = reloc->gpu_offset +
				 (radeon_get_ib_value(p, idx+1) & 0xfffffffc) +
				 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

			ib[idx+1] = (ib[idx+1] & 0x3) | (offset & 0xfffffffc);
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण अन्यथा अगर (idx_value & 0x100) अणु
			DRM_ERROR("cannot use PFP on REG wait\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CP_DMA:
	अणु
		u32 command, size, info;
		u64 offset, पंचांगp;
		अगर (pkt->count != 4) अणु
			DRM_ERROR("bad CP DMA\n");
			वापस -EINVAL;
		पूर्ण
		command = radeon_get_ib_value(p, idx+4);
		size = command & 0x1fffff;
		info = radeon_get_ib_value(p, idx+1);
		अगर ((((info & 0x60000000) >> 29) != 0) || /* src = GDS or DATA */
		    (((info & 0x00300000) >> 20) != 0) || /* dst = GDS */
		    ((((info & 0x00300000) >> 20) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_DAS)) || /* dst = रेजिस्टर */
		    ((((info & 0x60000000) >> 29) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_SAS))) अणु /* src = रेजिस्टर */
			/* non mem to mem copies requires dw aligned count */
			अगर (size % 4) अणु
				DRM_ERROR("CP DMA command requires dw count alignment\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (command & PACKET3_CP_DMA_CMD_SAS) अणु
			/* src address space is रेजिस्टर */
			/* GDS is ok */
			अगर (((info & 0x60000000) >> 29) != 1) अणु
				DRM_ERROR("CP DMA SAS not supported\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (command & PACKET3_CP_DMA_CMD_SAIC) अणु
				DRM_ERROR("CP DMA SAIC only supported for registers\n");
				वापस -EINVAL;
			पूर्ण
			/* src address space is memory */
			अगर (((info & 0x60000000) >> 29) == 0) अणु
				r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			पूर्ण अन्यथा अगर (((info & 0x60000000) >> 29) != 2) अणु
				DRM_ERROR("bad CP DMA SRC_SEL\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (command & PACKET3_CP_DMA_CMD_DAS) अणु
			/* dst address space is रेजिस्टर */
			/* GDS is ok */
			अगर (((info & 0x00300000) >> 20) != 1) अणु
				DRM_ERROR("CP DMA DAS not supported\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* dst address space is memory */
			अगर (command & PACKET3_CP_DMA_CMD_DAIC) अणु
				DRM_ERROR("CP DMA DAIC only supported for registers\n");
				वापस -EINVAL;
			पूर्ण
			अगर (((info & 0x00300000) >> 20) == 0) अणु
				r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			पूर्ण अन्यथा अणु
				DRM_ERROR("bad CP DMA DST_SEL\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_PFP_SYNC_ME:
		अगर (pkt->count) अणु
			DRM_ERROR("bad PFP_SYNC_ME\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SURFACE_SYNC:
		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad SURFACE_SYNC\n");
			वापस -EINVAL;
		पूर्ण
		/* 0xffffffff/0x0 is flush all cache flag */
		अगर (radeon_get_ib_value(p, idx + 1) != 0xffffffff ||
		    radeon_get_ib_value(p, idx + 2) != 0) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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

			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad EVENT_WRITE_EOP\n");
			वापस -EINVAL;
		पूर्ण

		offset = reloc->gpu_offset +
			 (radeon_get_ib_value(p, idx+1) & 0xfffffffc) +
			 ((u64)(radeon_get_ib_value(p, idx+2) & 0xff) << 32);

		ib[idx+1] = offset & 0xfffffffc;
		ib[idx+2] = (ib[idx+2] & 0xffffff00) | (upper_32_bits(offset) & 0xff);
		अवरोध;
	पूर्ण
	हाल PACKET3_EVENT_WRITE_EOS:
	अणु
		uपूर्णांक64_t offset;

		अगर (pkt->count != 3) अणु
			DRM_ERROR("bad EVENT_WRITE_EOS\n");
			वापस -EINVAL;
		पूर्ण
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("bad EVENT_WRITE_EOS\n");
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
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONFIG_REG_START) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (reg = start_reg, idx++; reg <= end_reg; reg += 4, idx++) अणु
			अगर (evergreen_is_safe_reg(p, reg))
				जारी;
			r = evergreen_cs_handle_reg(p, reg, idx);
			अगर (r)
				वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CONTEXT_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONTEXT_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONTEXT_REG_START) ||
		    (start_reg >= PACKET3_SET_CONTEXT_REG_END) ||
		    (end_reg >= PACKET3_SET_CONTEXT_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONTEXT_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (reg = start_reg, idx++; reg <= end_reg; reg += 4, idx++) अणु
			अगर (evergreen_is_safe_reg(p, reg))
				जारी;
			r = evergreen_cs_handle_reg(p, reg, idx);
			अगर (r)
				वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_RESOURCE:
		अगर (pkt->count % 8) अणु
			DRM_ERROR("bad SET_RESOURCE\n");
			वापस -EINVAL;
		पूर्ण
		start_reg = (idx_value << 2) + PACKET3_SET_RESOURCE_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_RESOURCE_START) ||
		    (start_reg >= PACKET3_SET_RESOURCE_END) ||
		    (end_reg >= PACKET3_SET_RESOURCE_END)) अणु
			DRM_ERROR("bad SET_RESOURCE\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < (pkt->count / 8); i++) अणु
			काष्ठा radeon_bo *texture, *mipmap;
			u32 toffset, moffset;
			u32 size, offset, mip_address, tex_dim;

			चयन (G__SQ_CONSTANT_TYPE(radeon_get_ib_value(p, idx+1+(i*8)+7))) अणु
			हाल SQ_TEX_VTX_VALID_TEXTURE:
				/* tex base */
				r = radeon_cs_packet_next_reloc(p, &reloc, 0);
				अगर (r) अणु
					DRM_ERROR("bad SET_RESOURCE (tex)\n");
					वापस -EINVAL;
				पूर्ण
				अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
					ib[idx+1+(i*8)+1] |=
						TEX_ARRAY_MODE(evergreen_cs_get_aray_mode(reloc->tiling_flags));
					अगर (reloc->tiling_flags & RADEON_TILING_MACRO) अणु
						अचिन्हित bankw, bankh, mtaspect, tile_split;

						evergreen_tiling_fields(reloc->tiling_flags,
									&bankw, &bankh, &mtaspect,
									&tile_split);
						ib[idx+1+(i*8)+6] |= TEX_TILE_SPLIT(tile_split);
						ib[idx+1+(i*8)+7] |=
							TEX_BANK_WIDTH(bankw) |
							TEX_BANK_HEIGHT(bankh) |
							MACRO_TILE_ASPECT(mtaspect) |
							TEX_NUM_BANKS(evergreen_cs_get_num_banks(track->nbanks));
					पूर्ण
				पूर्ण
				texture = reloc->robj;
				toffset = (u32)((reloc->gpu_offset >> 8) & 0xffffffff);

				/* tex mip base */
				tex_dim = ib[idx+1+(i*8)+0] & 0x7;
				mip_address = ib[idx+1+(i*8)+3];

				अगर ((tex_dim == SQ_TEX_DIM_2D_MSAA || tex_dim == SQ_TEX_DIM_2D_ARRAY_MSAA) &&
				    !mip_address &&
				    !radeon_cs_packet_next_is_pkt3_nop(p)) अणु
					/* MIP_ADDRESS should poपूर्णांक to FMASK क्रम an MSAA texture.
					 * It should be 0 अगर FMASK is disabled. */
					moffset = 0;
					mipmap = शून्य;
				पूर्ण अन्यथा अणु
					r = radeon_cs_packet_next_reloc(p, &reloc, 0);
					अगर (r) अणु
						DRM_ERROR("bad SET_RESOURCE (tex)\n");
						वापस -EINVAL;
					पूर्ण
					moffset = (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
					mipmap = reloc->robj;
				पूर्ण

				r = evergreen_cs_track_validate_texture(p, texture, mipmap, idx+1+(i*8));
				अगर (r)
					वापस r;
				ib[idx+1+(i*8)+2] += toffset;
				ib[idx+1+(i*8)+3] += moffset;
				अवरोध;
			हाल SQ_TEX_VTX_VALID_BUFFER:
			अणु
				uपूर्णांक64_t offset64;
				/* vtx base */
				r = radeon_cs_packet_next_reloc(p, &reloc, 0);
				अगर (r) अणु
					DRM_ERROR("bad SET_RESOURCE (vtx)\n");
					वापस -EINVAL;
				पूर्ण
				offset = radeon_get_ib_value(p, idx+1+(i*8)+0);
				size = radeon_get_ib_value(p, idx+1+(i*8)+1);
				अगर (p->rdev && (size + offset) > radeon_bo_size(reloc->robj)) अणु
					/* क्रमce size to size of the buffer */
					dev_warn_ratelimited(p->dev, "vbo resource seems too big for the bo\n");
					ib[idx+1+(i*8)+1] = radeon_bo_size(reloc->robj) - offset;
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
		/* XXX fix me ALU स्थिर buffers only */
		अवरोध;
	हाल PACKET3_SET_BOOL_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_BOOL_CONST_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_BOOL_CONST_START) ||
		    (start_reg >= PACKET3_SET_BOOL_CONST_END) ||
		    (end_reg >= PACKET3_SET_BOOL_CONST_END)) अणु
			DRM_ERROR("bad SET_BOOL_CONST\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_LOOP_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_LOOP_CONST_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_LOOP_CONST_START) ||
		    (start_reg >= PACKET3_SET_LOOP_CONST_END) ||
		    (end_reg >= PACKET3_SET_LOOP_CONST_END)) अणु
			DRM_ERROR("bad SET_LOOP_CONST\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CTL_CONST:
		start_reg = (idx_value << 2) + PACKET3_SET_CTL_CONST_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CTL_CONST_START) ||
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
		start_reg = (idx_value << 2) + PACKET3_SET_SAMPLER_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_SAMPLER_START) ||
		    (start_reg >= PACKET3_SET_SAMPLER_END) ||
		    (end_reg >= PACKET3_SET_SAMPLER_END)) अणु
			DRM_ERROR("bad SET_SAMPLER\n");
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
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			अगर (!evergreen_is_safe_reg(p, reg)) अणु
				dev_warn(p->dev, "forbidden register 0x%08x at %d\n",
					 reg, idx + 1);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (idx_value & 0x2) अणु
			u64 offset;
			/* DST is memory. */
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
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
			अगर (!evergreen_is_safe_reg(p, reg)) अणु
				dev_warn(p->dev, "forbidden register 0x%08x at %d\n",
					 reg, idx + 3);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_APPEND_CNT:
	अणु
		uपूर्णांक32_t areg;
		uपूर्णांक32_t allowed_reg_base;
		uपूर्णांक32_t source_sel;
		अगर (pkt->count != 2) अणु
			DRM_ERROR("bad SET_APPEND_CNT (invalid count)\n");
			वापस -EINVAL;
		पूर्ण

		allowed_reg_base = GDS_APPEND_COUNT_0;
		allowed_reg_base -= PACKET3_SET_CONTEXT_REG_START;
		allowed_reg_base >>= 2;

		areg = idx_value >> 16;
		अगर (areg < allowed_reg_base || areg > (allowed_reg_base + 11)) अणु
			dev_warn(p->dev, "forbidden register for append cnt 0x%08x at %d\n",
				 areg, idx);
			वापस -EINVAL;
		पूर्ण

		source_sel = G_PACKET3_SET_APPEND_CNT_SRC_SELECT(idx_value);
		अगर (source_sel == PACKET3_SAC_SRC_SEL_MEM) अणु
			uपूर्णांक64_t offset;
			uपूर्णांक32_t swap;
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				DRM_ERROR("bad SET_APPEND_CNT (missing reloc)\n");
				वापस -EINVAL;
			पूर्ण
			offset = radeon_get_ib_value(p, idx + 1);
			swap = offset & 0x3;
			offset &= ~0x3;

			offset += ((u64)(radeon_get_ib_value(p, idx + 2) & 0xff)) << 32;

			offset += reloc->gpu_offset;
			ib[idx+1] = (offset & 0xfffffffc) | swap;
			ib[idx+2] = upper_32_bits(offset) & 0xff;
		पूर्ण अन्यथा अणु
			DRM_ERROR("bad SET_APPEND_CNT (unsupported operation)\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PACKET3_NOP:
		अवरोध;
	शेष:
		DRM_ERROR("Packet3 opcode %x not supported\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक evergreen_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet pkt;
	काष्ठा evergreen_cs_track *track;
	u32 पंचांगp;
	पूर्णांक r;

	अगर (p->track == शून्य) अणु
		/* initialize tracker, we are in kms */
		track = kzalloc(माप(*track), GFP_KERNEL);
		अगर (track == शून्य)
			वापस -ENOMEM;
		evergreen_cs_track_init(track);
		अगर (p->rdev->family >= CHIP_CAYMAN) अणु
			पंचांगp = p->rdev->config.cayman.tile_config;
			track->reg_safe_bm = cayman_reg_safe_bm;
		पूर्ण अन्यथा अणु
			पंचांगp = p->rdev->config.evergreen.tile_config;
			track->reg_safe_bm = evergreen_reg_safe_bm;
		पूर्ण
		BUILD_BUG_ON(ARRAY_SIZE(cayman_reg_safe_bm) != REG_SAFE_BM_SIZE);
		BUILD_BUG_ON(ARRAY_SIZE(evergreen_reg_safe_bm) != REG_SAFE_BM_SIZE);
		चयन (पंचांगp & 0xf) अणु
		हाल 0:
			track->npipes = 1;
			अवरोध;
		हाल 1:
		शेष:
			track->npipes = 2;
			अवरोध;
		हाल 2:
			track->npipes = 4;
			अवरोध;
		हाल 3:
			track->npipes = 8;
			अवरोध;
		पूर्ण

		चयन ((पंचांगp & 0xf0) >> 4) अणु
		हाल 0:
			track->nbanks = 4;
			अवरोध;
		हाल 1:
		शेष:
			track->nbanks = 8;
			अवरोध;
		हाल 2:
			track->nbanks = 16;
			अवरोध;
		पूर्ण

		चयन ((पंचांगp & 0xf00) >> 8) अणु
		हाल 0:
			track->group_size = 256;
			अवरोध;
		हाल 1:
		शेष:
			track->group_size = 512;
			अवरोध;
		पूर्ण

		चयन ((पंचांगp & 0xf000) >> 12) अणु
		हाल 0:
			track->row_size = 1;
			अवरोध;
		हाल 1:
		शेष:
			track->row_size = 2;
			अवरोध;
		हाल 2:
			track->row_size = 4;
			अवरोध;
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
			r = evergreen_cs_parse_packet0(p, &pkt);
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			r = evergreen_packet3_check(p, &pkt);
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

/**
 * evergreen_dma_cs_parse() - parse the DMA IB
 * @p:		parser काष्ठाure holding parsing context.
 *
 * Parses the DMA IB from the CS ioctl and updates
 * the GPU addresses based on the reloc inक्रमmation and
 * checks क्रम errors. (Evergreen-Cayman)
 * Returns 0 क्रम success and an error on failure.
 **/
पूर्णांक evergreen_dma_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_chunk *ib_chunk = p->chunk_ib;
	काष्ठा radeon_bo_list *src_reloc, *dst_reloc, *dst2_reloc;
	u32 header, cmd, count, sub_cmd;
	uपूर्णांक32_t *ib = p->ib.ptr;
	u32 idx;
	u64 src_offset, dst_offset, dst2_offset;
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
		sub_cmd = GET_DMA_SUB_CMD(header);

		चयन (cmd) अणु
		हाल DMA_PACKET_WRITE:
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_WRITE\n");
				वापस -EINVAL;
			पूर्ण
			चयन (sub_cmd) अणु
			/* tiled */
			हाल 8:
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				p->idx += count + 7;
				अवरोध;
			/* linear */
			हाल 0:
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+2) & 0xff)) << 32;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				p->idx += count + 3;
				अवरोध;
			शेष:
				DRM_ERROR("bad DMA_PACKET_WRITE [%6d] 0x%08x sub cmd is not 0 or 8\n", idx, header);
				वापस -EINVAL;
			पूर्ण
			अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
				dev_warn(p->dev, "DMA write buffer too small (%llu %lu)\n",
					 dst_offset, radeon_bo_size(dst_reloc->robj));
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
			चयन (sub_cmd) अणु
			/* Copy L2L, DW aligned */
			हाल 0x00:
				/* L2L, dw */
				src_offset = radeon_get_ib_value(p, idx+2);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, dw src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, dw dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+3] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+4] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 5;
				अवरोध;
			/* Copy L2T/T2L */
			हाल 0x08:
				/* detile bit */
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					/* tiled src, linear dst */
					src_offset = radeon_get_ib_value(p, idx+1);
					src_offset <<= 8;
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					dst_offset = radeon_get_ib_value(p, idx + 7);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				पूर्ण अन्यथा अणु
					/* linear src, tiled dst */
					src_offset = radeon_get_ib_value(p, idx+7);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset <<= 8;
					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				पूर्ण
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				p->idx += 9;
				अवरोध;
			/* Copy L2L, byte aligned */
			हाल 0x40:
				/* L2L, byte */
				src_offset = radeon_get_ib_value(p, idx+2);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;
				अगर ((src_offset + count) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, byte src buffer too small (%llu %lu)\n",
							src_offset + count, radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + count) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, byte dst buffer too small (%llu %lu)\n",
							dst_offset + count, radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xffffffff);
				ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xffffffff);
				ib[idx+3] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+4] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 5;
				अवरोध;
			/* Copy L2L, partial */
			हाल 0x41:
				/* L2L, partial */
				अगर (p->family < CHIP_CAYMAN) अणु
					DRM_ERROR("L2L Partial is cayman only !\n");
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(src_reloc->gpu_offset & 0xffffffff);
				ib[idx+2] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				ib[idx+4] += (u32)(dst_reloc->gpu_offset & 0xffffffff);
				ib[idx+5] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;

				p->idx += 9;
				अवरोध;
			/* Copy L2L, DW aligned, broadcast */
			हाल 0x44:
				/* L2L, dw, broadcast */
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				अगर (r) अणु
					DRM_ERROR("bad L2L, dw, broadcast DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset |= ((u64)(radeon_get_ib_value(p, idx+5) & 0xff)) << 32;
				src_offset = radeon_get_ib_value(p, idx+3);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+6) & 0xff)) << 32;
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, dw, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, dw, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2L, dw, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset & 0xfffffffc);
				ib[idx+3] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+4] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+5] += upper_32_bits(dst2_reloc->gpu_offset) & 0xff;
				ib[idx+6] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 7;
				अवरोध;
			/* Copy L2T Frame to Field */
			हाल 0x48:
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					DRM_ERROR("bad L2T, frame to fields DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				अगर (r) अणु
					DRM_ERROR("bad L2T, frame to fields DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, frame to fields src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, frame to fields buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, frame to fields buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				अवरोध;
			/* Copy L2T/T2L, partial */
			हाल 0x49:
				/* L2T, T2L partial */
				अगर (p->family < CHIP_CAYMAN) अणु
					DRM_ERROR("L2T, T2L Partial is cayman only !\n");
					वापस -EINVAL;
				पूर्ण
				/* detile bit */
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					/* tiled src, linear dst */
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				पूर्ण अन्यथा अणु
					/* linear src, tiled dst */
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				पूर्ण
				p->idx += 12;
				अवरोध;
			/* Copy L2T broadcast */
			हाल 0x4b:
				/* L2T, broadcast */
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				अगर (r) अणु
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				अवरोध;
			/* Copy L2T/T2L (tile units) */
			हाल 0x4c:
				/* L2T, T2L */
				/* detile bit */
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					/* tiled src, linear dst */
					src_offset = radeon_get_ib_value(p, idx+1);
					src_offset <<= 8;
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					dst_offset = radeon_get_ib_value(p, idx+7);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				पूर्ण अन्यथा अणु
					/* linear src, tiled dst */
					src_offset = radeon_get_ib_value(p, idx+7);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset <<= 8;
					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				पूर्ण
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, T2L src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, T2L dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				p->idx += 9;
				अवरोध;
			/* Copy T2T, partial (tile units) */
			हाल 0x4d:
				/* T2T partial */
				अगर (p->family < CHIP_CAYMAN) अणु
					DRM_ERROR("L2T, T2L Partial is cayman only !\n");
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);
				ib[idx+4] += (u32)(dst_reloc->gpu_offset >> 8);
				p->idx += 13;
				अवरोध;
			/* Copy L2T broadcast (tile units) */
			हाल 0x4f:
				/* L2T, broadcast */
				अगर (radeon_get_ib_value(p, idx + 2) & (1 << 31)) अणु
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				अगर (r) अणु
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					वापस -EINVAL;
				पूर्ण
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				अगर ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				अगर ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) अणु
					dev_warn(p->dev, "DMA L2T, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					वापस -EINVAL;
				पूर्ण
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				अवरोध;
			शेष:
				DRM_ERROR("bad DMA_PACKET_COPY [%6d] 0x%08x invalid sub cmd\n", idx, header);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DMA_PACKET_CONSTANT_FILL:
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			अगर (r) अणु
				DRM_ERROR("bad DMA_PACKET_CONSTANT_FILL\n");
				वापस -EINVAL;
			पूर्ण
			dst_offset = radeon_get_ib_value(p, idx+1);
			dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0x00ff0000)) << 16;
			अगर ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) अणु
				dev_warn(p->dev, "DMA constant fill buffer too small (%llu %lu)\n",
					 dst_offset, radeon_bo_size(dst_reloc->robj));
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

/* vm parser */
अटल bool evergreen_vm_reg_valid(u32 reg)
अणु
	/* context regs are fine */
	अगर (reg >= 0x28000)
		वापस true;

	/* check config regs */
	चयन (reg) अणु
	हाल WAIT_UNTIL:
	हाल GRBM_GFX_INDEX:
	हाल CP_STRMOUT_CNTL:
	हाल CP_COHER_CNTL:
	हाल CP_COHER_SIZE:
	हाल VGT_VTX_VECT_EJECT_REG:
	हाल VGT_CACHE_INVALIDATION:
	हाल VGT_GS_VERTEX_REUSE:
	हाल VGT_PRIMITIVE_TYPE:
	हाल VGT_INDEX_TYPE:
	हाल VGT_NUM_INDICES:
	हाल VGT_NUM_INSTANCES:
	हाल VGT_COMPUTE_DIM_X:
	हाल VGT_COMPUTE_DIM_Y:
	हाल VGT_COMPUTE_DIM_Z:
	हाल VGT_COMPUTE_START_X:
	हाल VGT_COMPUTE_START_Y:
	हाल VGT_COMPUTE_START_Z:
	हाल VGT_COMPUTE_INDEX:
	हाल VGT_COMPUTE_THREAD_GROUP_SIZE:
	हाल VGT_HS_OFFCHIP_PARAM:
	हाल PA_CL_ENHANCE:
	हाल PA_SU_LINE_STIPPLE_VALUE:
	हाल PA_SC_LINE_STIPPLE_STATE:
	हाल PA_SC_ENHANCE:
	हाल SQ_DYN_GPR_CNTL_PS_FLUSH_REQ:
	हाल SQ_DYN_GPR_SIMD_LOCK_EN:
	हाल SQ_CONFIG:
	हाल SQ_GPR_RESOURCE_MGMT_1:
	हाल SQ_GLOBAL_GPR_RESOURCE_MGMT_1:
	हाल SQ_GLOBAL_GPR_RESOURCE_MGMT_2:
	हाल SQ_CONST_MEM_BASE:
	हाल SQ_STATIC_THREAD_MGMT_1:
	हाल SQ_STATIC_THREAD_MGMT_2:
	हाल SQ_STATIC_THREAD_MGMT_3:
	हाल SPI_CONFIG_CNTL:
	हाल SPI_CONFIG_CNTL_1:
	हाल TA_CNTL_AUX:
	हाल DB_DEBUG:
	हाल DB_DEBUG2:
	हाल DB_DEBUG3:
	हाल DB_DEBUG4:
	हाल DB_WATERMARKS:
	हाल TD_PS_BORDER_COLOR_INDEX:
	हाल TD_PS_BORDER_COLOR_RED:
	हाल TD_PS_BORDER_COLOR_GREEN:
	हाल TD_PS_BORDER_COLOR_BLUE:
	हाल TD_PS_BORDER_COLOR_ALPHA:
	हाल TD_VS_BORDER_COLOR_INDEX:
	हाल TD_VS_BORDER_COLOR_RED:
	हाल TD_VS_BORDER_COLOR_GREEN:
	हाल TD_VS_BORDER_COLOR_BLUE:
	हाल TD_VS_BORDER_COLOR_ALPHA:
	हाल TD_GS_BORDER_COLOR_INDEX:
	हाल TD_GS_BORDER_COLOR_RED:
	हाल TD_GS_BORDER_COLOR_GREEN:
	हाल TD_GS_BORDER_COLOR_BLUE:
	हाल TD_GS_BORDER_COLOR_ALPHA:
	हाल TD_HS_BORDER_COLOR_INDEX:
	हाल TD_HS_BORDER_COLOR_RED:
	हाल TD_HS_BORDER_COLOR_GREEN:
	हाल TD_HS_BORDER_COLOR_BLUE:
	हाल TD_HS_BORDER_COLOR_ALPHA:
	हाल TD_LS_BORDER_COLOR_INDEX:
	हाल TD_LS_BORDER_COLOR_RED:
	हाल TD_LS_BORDER_COLOR_GREEN:
	हाल TD_LS_BORDER_COLOR_BLUE:
	हाल TD_LS_BORDER_COLOR_ALPHA:
	हाल TD_CS_BORDER_COLOR_INDEX:
	हाल TD_CS_BORDER_COLOR_RED:
	हाल TD_CS_BORDER_COLOR_GREEN:
	हाल TD_CS_BORDER_COLOR_BLUE:
	हाल TD_CS_BORDER_COLOR_ALPHA:
	हाल SQ_ESGS_RING_SIZE:
	हाल SQ_GSVS_RING_SIZE:
	हाल SQ_ESTMP_RING_SIZE:
	हाल SQ_GSTMP_RING_SIZE:
	हाल SQ_HSTMP_RING_SIZE:
	हाल SQ_LSTMP_RING_SIZE:
	हाल SQ_PSTMP_RING_SIZE:
	हाल SQ_VSTMP_RING_SIZE:
	हाल SQ_ESGS_RING_ITEMSIZE:
	हाल SQ_ESTMP_RING_ITEMSIZE:
	हाल SQ_GSTMP_RING_ITEMSIZE:
	हाल SQ_GSVS_RING_ITEMSIZE:
	हाल SQ_GS_VERT_ITEMSIZE:
	हाल SQ_GS_VERT_ITEMSIZE_1:
	हाल SQ_GS_VERT_ITEMSIZE_2:
	हाल SQ_GS_VERT_ITEMSIZE_3:
	हाल SQ_GSVS_RING_OFFSET_1:
	हाल SQ_GSVS_RING_OFFSET_2:
	हाल SQ_GSVS_RING_OFFSET_3:
	हाल SQ_HSTMP_RING_ITEMSIZE:
	हाल SQ_LSTMP_RING_ITEMSIZE:
	हाल SQ_PSTMP_RING_ITEMSIZE:
	हाल SQ_VSTMP_RING_ITEMSIZE:
	हाल VGT_TF_RING_SIZE:
	हाल SQ_ESGS_RING_BASE:
	हाल SQ_GSVS_RING_BASE:
	हाल SQ_ESTMP_RING_BASE:
	हाल SQ_GSTMP_RING_BASE:
	हाल SQ_HSTMP_RING_BASE:
	हाल SQ_LSTMP_RING_BASE:
	हाल SQ_PSTMP_RING_BASE:
	हाल SQ_VSTMP_RING_BASE:
	हाल CAYMAN_VGT_OFFCHIP_LDS_BASE:
	हाल CAYMAN_SQ_EX_ALLOC_TABLE_SLOTS:
		वापस true;
	शेष:
		DRM_ERROR("Invalid register 0x%x in CS\n", reg);
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक evergreen_vm_packet3_check(काष्ठा radeon_device *rdev,
				      u32 *ib, काष्ठा radeon_cs_packet *pkt)
अणु
	u32 idx = pkt->idx + 1;
	u32 idx_value = ib[idx];
	u32 start_reg, end_reg, reg, i;
	u32 command, info;

	चयन (pkt->opcode) अणु
	हाल PACKET3_NOP:
		अवरोध;
	हाल PACKET3_SET_BASE:
		अगर (idx_value != 1) अणु
			DRM_ERROR("bad SET_BASE");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CLEAR_STATE:
	हाल PACKET3_INDEX_BUFFER_SIZE:
	हाल PACKET3_DISPATCH_सूचीECT:
	हाल PACKET3_DISPATCH_INसूचीECT:
	हाल PACKET3_MODE_CONTROL:
	हाल PACKET3_SET_PREDICATION:
	हाल PACKET3_COND_EXEC:
	हाल PACKET3_PRED_EXEC:
	हाल PACKET3_DRAW_INसूचीECT:
	हाल PACKET3_DRAW_INDEX_INसूचीECT:
	हाल PACKET3_INDEX_BASE:
	हाल PACKET3_DRAW_INDEX_2:
	हाल PACKET3_CONTEXT_CONTROL:
	हाल PACKET3_DRAW_INDEX_OFFSET:
	हाल PACKET3_INDEX_TYPE:
	हाल PACKET3_DRAW_INDEX:
	हाल PACKET3_DRAW_INDEX_AUTO:
	हाल PACKET3_DRAW_INDEX_IMMD:
	हाल PACKET3_NUM_INSTANCES:
	हाल PACKET3_DRAW_INDEX_MULTI_AUTO:
	हाल PACKET3_STRMOUT_BUFFER_UPDATE:
	हाल PACKET3_DRAW_INDEX_OFFSET_2:
	हाल PACKET3_DRAW_INDEX_MULTI_ELEMENT:
	हाल PACKET3_MPEG_INDEX:
	हाल PACKET3_WAIT_REG_MEM:
	हाल PACKET3_MEM_WRITE:
	हाल PACKET3_PFP_SYNC_ME:
	हाल PACKET3_SURFACE_SYNC:
	हाल PACKET3_EVENT_WRITE:
	हाल PACKET3_EVENT_WRITE_EOP:
	हाल PACKET3_EVENT_WRITE_EOS:
	हाल PACKET3_SET_CONTEXT_REG:
	हाल PACKET3_SET_BOOL_CONST:
	हाल PACKET3_SET_LOOP_CONST:
	हाल PACKET3_SET_RESOURCE:
	हाल PACKET3_SET_SAMPLER:
	हाल PACKET3_SET_CTL_CONST:
	हाल PACKET3_SET_RESOURCE_OFFSET:
	हाल PACKET3_SET_CONTEXT_REG_INसूचीECT:
	हाल PACKET3_SET_RESOURCE_INसूचीECT:
	हाल CAYMAN_PACKET3_DEALLOC_STATE:
		अवरोध;
	हाल PACKET3_COND_WRITE:
		अगर (idx_value & 0x100) अणु
			reg = ib[idx + 5] * 4;
			अगर (!evergreen_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_COPY_DW:
		अगर (idx_value & 0x2) अणु
			reg = ib[idx + 3] * 4;
			अगर (!evergreen_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CONFIG_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONFIG_REG_START) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < pkt->count; i++) अणु
			reg = start_reg + (4 * i);
			अगर (!evergreen_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CP_DMA:
		command = ib[idx + 4];
		info = ib[idx + 1];
		अगर ((((info & 0x60000000) >> 29) != 0) || /* src = GDS or DATA */
		    (((info & 0x00300000) >> 20) != 0) || /* dst = GDS */
		    ((((info & 0x00300000) >> 20) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_DAS)) || /* dst = रेजिस्टर */
		    ((((info & 0x60000000) >> 29) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_SAS))) अणु /* src = रेजिस्टर */
			/* non mem to mem copies requires dw aligned count */
			अगर ((command & 0x1fffff) % 4) अणु
				DRM_ERROR("CP DMA command requires dw count alignment\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (command & PACKET3_CP_DMA_CMD_SAS) अणु
			/* src address space is रेजिस्टर */
			अगर (((info & 0x60000000) >> 29) == 0) अणु
				start_reg = idx_value << 2;
				अगर (command & PACKET3_CP_DMA_CMD_SAIC) अणु
					reg = start_reg;
					अगर (!evergreen_vm_reg_valid(reg)) अणु
						DRM_ERROR("CP DMA Bad SRC register\n");
						वापस -EINVAL;
					पूर्ण
				पूर्ण अन्यथा अणु
					क्रम (i = 0; i < (command & 0x1fffff); i++) अणु
						reg = start_reg + (4 * i);
						अगर (!evergreen_vm_reg_valid(reg)) अणु
							DRM_ERROR("CP DMA Bad SRC register\n");
							वापस -EINVAL;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (command & PACKET3_CP_DMA_CMD_DAS) अणु
			/* dst address space is रेजिस्टर */
			अगर (((info & 0x00300000) >> 20) == 0) अणु
				start_reg = ib[idx + 2];
				अगर (command & PACKET3_CP_DMA_CMD_DAIC) अणु
					reg = start_reg;
					अगर (!evergreen_vm_reg_valid(reg)) अणु
						DRM_ERROR("CP DMA Bad DST register\n");
						वापस -EINVAL;
					पूर्ण
				पूर्ण अन्यथा अणु
					क्रम (i = 0; i < (command & 0x1fffff); i++) अणु
						reg = start_reg + (4 * i);
						अगर (!evergreen_vm_reg_valid(reg)) अणु
							DRM_ERROR("CP DMA Bad DST register\n");
							वापस -EINVAL;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_APPEND_CNT: अणु
		uपूर्णांक32_t areg;
		uपूर्णांक32_t allowed_reg_base;

		अगर (pkt->count != 2) अणु
			DRM_ERROR("bad SET_APPEND_CNT (invalid count)\n");
			वापस -EINVAL;
		पूर्ण

		allowed_reg_base = GDS_APPEND_COUNT_0;
		allowed_reg_base -= PACKET3_SET_CONTEXT_REG_START;
		allowed_reg_base >>= 2;

		areg = idx_value >> 16;
		अगर (areg < allowed_reg_base || areg > (allowed_reg_base + 11)) अणु
			DRM_ERROR("forbidden register for append cnt 0x%08x at %d\n",
				  areg, idx);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक evergreen_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	पूर्णांक ret = 0;
	u32 idx = 0;
	काष्ठा radeon_cs_packet pkt;

	करो अणु
		pkt.idx = idx;
		pkt.type = RADEON_CP_PACKET_GET_TYPE(ib->ptr[idx]);
		pkt.count = RADEON_CP_PACKET_GET_COUNT(ib->ptr[idx]);
		pkt.one_reg_wr = 0;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			dev_err(rdev->dev, "Packet0 not allowed!\n");
			ret = -EINVAL;
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			idx += 1;
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			pkt.opcode = RADEON_CP_PACKET3_GET_OPCODE(ib->ptr[idx]);
			ret = evergreen_vm_packet3_check(rdev, ib->ptr, &pkt);
			idx += pkt.count + 2;
			अवरोध;
		शेष:
			dev_err(rdev->dev, "Unknown packet type %d !\n", pkt.type);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण जबतक (idx < ib->length_dw);

	वापस ret;
पूर्ण

/**
 * evergreen_dma_ib_parse() - parse the DMA IB क्रम VM
 * @rdev: radeon_device poपूर्णांकer
 * @ib:	radeon_ib poपूर्णांकer
 *
 * Parses the DMA IB from the VM CS ioctl
 * checks क्रम errors. (Cayman-SI)
 * Returns 0 क्रम success and an error on failure.
 **/
पूर्णांक evergreen_dma_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	u32 idx = 0;
	u32 header, cmd, count, sub_cmd;

	करो अणु
		header = ib->ptr[idx];
		cmd = GET_DMA_CMD(header);
		count = GET_DMA_COUNT(header);
		sub_cmd = GET_DMA_SUB_CMD(header);

		चयन (cmd) अणु
		हाल DMA_PACKET_WRITE:
			चयन (sub_cmd) अणु
			/* tiled */
			हाल 8:
				idx += count + 7;
				अवरोध;
			/* linear */
			हाल 0:
				idx += count + 3;
				अवरोध;
			शेष:
				DRM_ERROR("bad DMA_PACKET_WRITE [%6d] 0x%08x sub cmd is not 0 or 8\n", idx, ib->ptr[idx]);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DMA_PACKET_COPY:
			चयन (sub_cmd) अणु
			/* Copy L2L, DW aligned */
			हाल 0x00:
				idx += 5;
				अवरोध;
			/* Copy L2T/T2L */
			हाल 0x08:
				idx += 9;
				अवरोध;
			/* Copy L2L, byte aligned */
			हाल 0x40:
				idx += 5;
				अवरोध;
			/* Copy L2L, partial */
			हाल 0x41:
				idx += 9;
				अवरोध;
			/* Copy L2L, DW aligned, broadcast */
			हाल 0x44:
				idx += 7;
				अवरोध;
			/* Copy L2T Frame to Field */
			हाल 0x48:
				idx += 10;
				अवरोध;
			/* Copy L2T/T2L, partial */
			हाल 0x49:
				idx += 12;
				अवरोध;
			/* Copy L2T broadcast */
			हाल 0x4b:
				idx += 10;
				अवरोध;
			/* Copy L2T/T2L (tile units) */
			हाल 0x4c:
				idx += 9;
				अवरोध;
			/* Copy T2T, partial (tile units) */
			हाल 0x4d:
				idx += 13;
				अवरोध;
			/* Copy L2T broadcast (tile units) */
			हाल 0x4f:
				idx += 10;
				अवरोध;
			शेष:
				DRM_ERROR("bad DMA_PACKET_COPY [%6d] 0x%08x invalid sub cmd\n", idx, ib->ptr[idx]);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DMA_PACKET_CONSTANT_FILL:
			idx += 4;
			अवरोध;
		हाल DMA_PACKET_NOP:
			idx += 1;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d at %d !\n", cmd, idx);
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (idx < ib->length_dw);

	वापस 0;
पूर्ण
