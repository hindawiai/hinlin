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

#समावेश <drm/radeon_drm.h>
#समावेश "radeon_reg.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"

#समावेश "r100d.h"
#समावेश "r200_reg_safe.h"

#समावेश "r100_track.h"

अटल पूर्णांक r200_get_vtx_size_0(uपूर्णांक32_t vtx_fmt_0)
अणु
	पूर्णांक vtx_size, i;
	vtx_size = 2;

	अगर (vtx_fmt_0 & R200_VTX_Z0)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_W0)
		vtx_size++;
	/* blend weight */
	अगर (vtx_fmt_0 & (0x7 << R200_VTX_WEIGHT_COUNT_SHIFT))
		vtx_size += (vtx_fmt_0 >> R200_VTX_WEIGHT_COUNT_SHIFT) & 0x7;
	अगर (vtx_fmt_0 & R200_VTX_PV_MATRIX_SEL)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_N0)
		vtx_size += 3;
	अगर (vtx_fmt_0 & R200_VTX_POINT_SIZE)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_DISCRETE_FOG)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_SHININESS_0)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_SHININESS_1)
		vtx_size++;
	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक color_size = (vtx_fmt_0 >> (11 + 2*i)) & 0x3;
		चयन (color_size) अणु
		हाल 0: अवरोध;
		हाल 1: vtx_size++; अवरोध;
		हाल 2: vtx_size += 3; अवरोध;
		हाल 3: vtx_size += 4; अवरोध;
		पूर्ण
	पूर्ण
	अगर (vtx_fmt_0 & R200_VTX_XY1)
		vtx_size += 2;
	अगर (vtx_fmt_0 & R200_VTX_Z1)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_W1)
		vtx_size++;
	अगर (vtx_fmt_0 & R200_VTX_N1)
		vtx_size += 3;
	वापस vtx_size;
पूर्ण

काष्ठा radeon_fence *r200_copy_dma(काष्ठा radeon_device *rdev,
				   uपूर्णांक64_t src_offset,
				   uपूर्णांक64_t dst_offset,
				   अचिन्हित num_gpu_pages,
				   काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	काष्ठा radeon_fence *fence;
	uपूर्णांक32_t size;
	uपूर्णांक32_t cur_size;
	पूर्णांक i, num_loops;
	पूर्णांक r = 0;

	/* radeon pitch is /64 */
	size = num_gpu_pages << RADEON_GPU_PAGE_SHIFT;
	num_loops = DIV_ROUND_UP(size, 0x1FFFFF);
	r = radeon_ring_lock(rdev, ring, num_loops * 4 + 64);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		वापस ERR_PTR(r);
	पूर्ण
	/* Must रुको क्रम 2D idle & clean beक्रमe DMA or hangs might happen */
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, (1 << 16));
	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size = size;
		अगर (cur_size > 0x1FFFFF) अणु
			cur_size = 0x1FFFFF;
		पूर्ण
		size -= cur_size;
		radeon_ring_ग_लिखो(ring, PACKET0(0x720, 2));
		radeon_ring_ग_लिखो(ring, src_offset);
		radeon_ring_ग_लिखो(ring, dst_offset);
		radeon_ring_ग_लिखो(ring, cur_size | (1 << 31) | (1 << 30));
		src_offset += cur_size;
		dst_offset += cur_size;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, RADEON_WAIT_DMA_GUI_IDLE);
	r = radeon_fence_emit(rdev, &fence, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		वापस ERR_PTR(r);
	पूर्ण
	radeon_ring_unlock_commit(rdev, ring, false);
	वापस fence;
पूर्ण


अटल पूर्णांक r200_get_vtx_size_1(uपूर्णांक32_t vtx_fmt_1)
अणु
	पूर्णांक vtx_size, i, tex_size;
	vtx_size = 0;
	क्रम (i = 0; i < 6; i++) अणु
		tex_size = (vtx_fmt_1 >> (i * 3)) & 0x7;
		अगर (tex_size > 4)
			जारी;
		vtx_size += tex_size;
	पूर्ण
	वापस vtx_size;
पूर्ण

पूर्णांक r200_packet0_check(काष्ठा radeon_cs_parser *p,
		       काष्ठा radeon_cs_packet *pkt,
		       अचिन्हित idx, अचिन्हित reg)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	अस्थिर uपूर्णांक32_t *ib;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;
	पूर्णांक i;
	पूर्णांक face;
	u32 tile_flags = 0;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (काष्ठा r100_cs_track *)p->track;
	idx_value = radeon_get_ib_value(p, idx);
	चयन (reg) अणु
	हाल RADEON_CRTC_GUI_TRIG_VLINE:
		r = r100_cs_packet_parse_vline(p);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अवरोध;
		/* FIXME: only allow PACKET3 blit? easier to check क्रम out of
		 * range access */
	हाल RADEON_DST_PITCH_OFFSET:
	हाल RADEON_SRC_PITCH_OFFSET:
		r = r100_reloc_pitch_offset(p, pkt, idx, reg);
		अगर (r)
			वापस r;
		अवरोध;
	हाल RADEON_RB3D_DEPTHOFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->zb.robj = reloc->robj;
		track->zb.offset = idx_value;
		track->zb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल RADEON_RB3D_COLOROFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->cb[0].robj = reloc->robj;
		track->cb[0].offset = idx_value;
		track->cb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल R200_PP_TXOFFSET_0:
	हाल R200_PP_TXOFFSET_1:
	हाल R200_PP_TXOFFSET_2:
	हाल R200_PP_TXOFFSET_3:
	हाल R200_PP_TXOFFSET_4:
	हाल R200_PP_TXOFFSET_5:
		i = (reg - R200_PP_TXOFFSET_0) / 24;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= R200_TXO_MACRO_TILE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= R200_TXO_MICRO_TILE;

			पंचांगp = idx_value & ~(0x7 << 2);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp + ((u32)reloc->gpu_offset);
		पूर्ण अन्यथा
			ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_CUBIC_OFFSET_F1_0:
	हाल R200_PP_CUBIC_OFFSET_F2_0:
	हाल R200_PP_CUBIC_OFFSET_F3_0:
	हाल R200_PP_CUBIC_OFFSET_F4_0:
	हाल R200_PP_CUBIC_OFFSET_F5_0:
	हाल R200_PP_CUBIC_OFFSET_F1_1:
	हाल R200_PP_CUBIC_OFFSET_F2_1:
	हाल R200_PP_CUBIC_OFFSET_F3_1:
	हाल R200_PP_CUBIC_OFFSET_F4_1:
	हाल R200_PP_CUBIC_OFFSET_F5_1:
	हाल R200_PP_CUBIC_OFFSET_F1_2:
	हाल R200_PP_CUBIC_OFFSET_F2_2:
	हाल R200_PP_CUBIC_OFFSET_F3_2:
	हाल R200_PP_CUBIC_OFFSET_F4_2:
	हाल R200_PP_CUBIC_OFFSET_F5_2:
	हाल R200_PP_CUBIC_OFFSET_F1_3:
	हाल R200_PP_CUBIC_OFFSET_F2_3:
	हाल R200_PP_CUBIC_OFFSET_F3_3:
	हाल R200_PP_CUBIC_OFFSET_F4_3:
	हाल R200_PP_CUBIC_OFFSET_F5_3:
	हाल R200_PP_CUBIC_OFFSET_F1_4:
	हाल R200_PP_CUBIC_OFFSET_F2_4:
	हाल R200_PP_CUBIC_OFFSET_F3_4:
	हाल R200_PP_CUBIC_OFFSET_F4_4:
	हाल R200_PP_CUBIC_OFFSET_F5_4:
	हाल R200_PP_CUBIC_OFFSET_F1_5:
	हाल R200_PP_CUBIC_OFFSET_F2_5:
	हाल R200_PP_CUBIC_OFFSET_F3_5:
	हाल R200_PP_CUBIC_OFFSET_F4_5:
	हाल R200_PP_CUBIC_OFFSET_F5_5:
		i = (reg - R200_PP_TXOFFSET_0) / 24;
		face = (reg - ((i * 24) + R200_PP_TXOFFSET_0)) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->textures[i].cube_info[face - 1].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].cube_info[face - 1].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_RE_WIDTH_HEIGHT:
		track->maxy = ((idx_value >> 16) & 0x7FF);
		track->cb_dirty = true;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_COLORPITCH:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण

		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= RADEON_COLOR_TILE_ENABLE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= RADEON_COLOR_MICROTILE_ENABLE;

			पंचांगp = idx_value & ~(0x7 << 16);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp;
		पूर्ण अन्यथा
			ib[idx] = idx_value;

		track->cb[0].pitch = idx_value & RADEON_COLORPITCH_MASK;
		track->cb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_DEPTHPITCH:
		track->zb.pitch = idx_value & RADEON_DEPTHPITCH_MASK;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_CNTL:
		चयन ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f) अणु
		हाल 7:
		हाल 8:
		हाल 9:
		हाल 11:
		हाल 12:
			track->cb[0].cpp = 1;
			अवरोध;
		हाल 3:
		हाल 4:
		हाल 15:
			track->cb[0].cpp = 2;
			अवरोध;
		हाल 6:
			track->cb[0].cpp = 4;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid color buffer format (%d) !\n",
				  ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f));
			वापस -EINVAL;
		पूर्ण
		अगर (idx_value & RADEON_DEPTHXY_OFFSET_ENABLE) अणु
			DRM_ERROR("No support for depth xy offset in kms\n");
			वापस -EINVAL;
		पूर्ण

		track->z_enabled = !!(idx_value & RADEON_Z_ENABLE);
		track->cb_dirty = true;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_ZSTENCILCNTL:
		चयन (idx_value & 0xf) अणु
		हाल 0:
			track->zb.cpp = 2;
			अवरोध;
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 9:
		हाल 11:
			track->zb.cpp = 4;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_ZPASS_ADDR:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल RADEON_PP_CNTL:
		अणु
			uपूर्णांक32_t temp = idx_value >> 4;
			क्रम (i = 0; i < track->num_texture; i++)
				track->textures[i].enabled = !!(temp & (1 << i));
			track->tex_dirty = true;
		पूर्ण
		अवरोध;
	हाल RADEON_SE_VF_CNTL:
		track->vap_vf_cntl = idx_value;
		अवरोध;
	हाल 0x210c:
		/* VAP_VF_MAX_VTX_INDX */
		track->max_indx = idx_value & 0x00FFFFFFUL;
		अवरोध;
	हाल R200_SE_VTX_FMT_0:
		track->vtx_size = r200_get_vtx_size_0(idx_value);
		अवरोध;
	हाल R200_SE_VTX_FMT_1:
		track->vtx_size += r200_get_vtx_size_1(idx_value);
		अवरोध;
	हाल R200_PP_TXSIZE_0:
	हाल R200_PP_TXSIZE_1:
	हाल R200_PP_TXSIZE_2:
	हाल R200_PP_TXSIZE_3:
	हाल R200_PP_TXSIZE_4:
	हाल R200_PP_TXSIZE_5:
		i = (reg - R200_PP_TXSIZE_0) / 32;
		track->textures[i].width = (idx_value & RADEON_TEX_USIZE_MASK) + 1;
		track->textures[i].height = ((idx_value & RADEON_TEX_VSIZE_MASK) >> RADEON_TEX_VSIZE_SHIFT) + 1;
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_TXPITCH_0:
	हाल R200_PP_TXPITCH_1:
	हाल R200_PP_TXPITCH_2:
	हाल R200_PP_TXPITCH_3:
	हाल R200_PP_TXPITCH_4:
	हाल R200_PP_TXPITCH_5:
		i = (reg - R200_PP_TXPITCH_0) / 32;
		track->textures[i].pitch = idx_value + 32;
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_TXFILTER_0:
	हाल R200_PP_TXFILTER_1:
	हाल R200_PP_TXFILTER_2:
	हाल R200_PP_TXFILTER_3:
	हाल R200_PP_TXFILTER_4:
	हाल R200_PP_TXFILTER_5:
		i = (reg - R200_PP_TXFILTER_0) / 32;
		track->textures[i].num_levels = ((idx_value & R200_MAX_MIP_LEVEL_MASK)
						 >> R200_MAX_MIP_LEVEL_SHIFT);
		पंचांगp = (idx_value >> 23) & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 6)
			track->textures[i].roundup_w = false;
		पंचांगp = (idx_value >> 27) & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 6)
			track->textures[i].roundup_h = false;
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_TXMULTI_CTL_0:
	हाल R200_PP_TXMULTI_CTL_1:
	हाल R200_PP_TXMULTI_CTL_2:
	हाल R200_PP_TXMULTI_CTL_3:
	हाल R200_PP_TXMULTI_CTL_4:
	हाल R200_PP_TXMULTI_CTL_5:
		i = (reg - R200_PP_TXMULTI_CTL_0) / 32;
		अवरोध;
	हाल R200_PP_TXFORMAT_X_0:
	हाल R200_PP_TXFORMAT_X_1:
	हाल R200_PP_TXFORMAT_X_2:
	हाल R200_PP_TXFORMAT_X_3:
	हाल R200_PP_TXFORMAT_X_4:
	हाल R200_PP_TXFORMAT_X_5:
		i = (reg - R200_PP_TXFORMAT_X_0) / 32;
		track->textures[i].txdepth = idx_value & 0x7;
		पंचांगp = (idx_value >> 16) & 0x3;
		/* 2D, 3D, CUBE */
		चयन (पंचांगp) अणु
		हाल 0:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
			/* 1D/2D */
			track->textures[i].tex_coord_type = 0;
			अवरोध;
		हाल 1:
			/* CUBE */
			track->textures[i].tex_coord_type = 2;
			अवरोध;
		हाल 2:
			/* 3D */
			track->textures[i].tex_coord_type = 1;
			अवरोध;
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_TXFORMAT_0:
	हाल R200_PP_TXFORMAT_1:
	हाल R200_PP_TXFORMAT_2:
	हाल R200_PP_TXFORMAT_3:
	हाल R200_PP_TXFORMAT_4:
	हाल R200_PP_TXFORMAT_5:
		i = (reg - R200_PP_TXFORMAT_0) / 32;
		अगर (idx_value & R200_TXFORMAT_NON_POWER2) अणु
			track->textures[i].use_pitch = 1;
		पूर्ण अन्यथा अणु
			track->textures[i].use_pitch = 0;
			track->textures[i].width = 1 << ((idx_value & RADEON_TXFORMAT_WIDTH_MASK) >> RADEON_TXFORMAT_WIDTH_SHIFT);
			track->textures[i].height = 1 << ((idx_value & RADEON_TXFORMAT_HEIGHT_MASK) >> RADEON_TXFORMAT_HEIGHT_SHIFT);
		पूर्ण
		अगर (idx_value & R200_TXFORMAT_LOOKUP_DISABLE)
			track->textures[i].lookup_disable = true;
		चयन ((idx_value & RADEON_TXFORMAT_FORMAT_MASK)) अणु
		हाल R200_TXFORMAT_I8:
		हाल R200_TXFORMAT_RGB332:
		हाल R200_TXFORMAT_Y8:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R200_TXFORMAT_AI88:
		हाल R200_TXFORMAT_ARGB1555:
		हाल R200_TXFORMAT_RGB565:
		हाल R200_TXFORMAT_ARGB4444:
		हाल R200_TXFORMAT_VYUY422:
		हाल R200_TXFORMAT_YVYU422:
		हाल R200_TXFORMAT_LDVDU655:
		हाल R200_TXFORMAT_DVDU88:
		हाल R200_TXFORMAT_AVYU4444:
			track->textures[i].cpp = 2;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R200_TXFORMAT_ARGB8888:
		हाल R200_TXFORMAT_RGBA8888:
		हाल R200_TXFORMAT_ABGR8888:
		हाल R200_TXFORMAT_BGR111110:
		हाल R200_TXFORMAT_LDVDU8888:
			track->textures[i].cpp = 4;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R200_TXFORMAT_DXT1:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT1;
			अवरोध;
		हाल R200_TXFORMAT_DXT23:
		हाल R200_TXFORMAT_DXT45:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT1;
			अवरोध;
		पूर्ण
		track->textures[i].cube_info[4].width = 1 << ((idx_value >> 16) & 0xf);
		track->textures[i].cube_info[4].height = 1 << ((idx_value >> 20) & 0xf);
		track->tex_dirty = true;
		अवरोध;
	हाल R200_PP_CUBIC_FACES_0:
	हाल R200_PP_CUBIC_FACES_1:
	हाल R200_PP_CUBIC_FACES_2:
	हाल R200_PP_CUBIC_FACES_3:
	हाल R200_PP_CUBIC_FACES_4:
	हाल R200_PP_CUBIC_FACES_5:
		पंचांगp = idx_value;
		i = (reg - R200_PP_CUBIC_FACES_0) / 32;
		क्रम (face = 0; face < 4; face++) अणु
			track->textures[i].cube_info[face].width = 1 << ((पंचांगp >> (face * 8)) & 0xf);
			track->textures[i].cube_info[face].height = 1 << ((पंचांगp >> ((face * 8) + 4)) & 0xf);
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	शेष:
		pr_err("Forbidden register 0x%04X in cs at %d\n", reg, idx);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम r200_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	rdev->config.r100.reg_safe_bm = r200_reg_safe_bm;
	rdev->config.r100.reg_safe_bm_size = ARRAY_SIZE(r200_reg_safe_bm);
पूर्ण
