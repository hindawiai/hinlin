<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */


#समावेश "dcn20_hubbub.h"
#समावेश "reg_helper.h"
#समावेश "clk_mgr.h"

#घोषणा REG(reg)\
	hubbub1->regs->reg

#घोषणा CTX \
	hubbub1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name

#घोषणा REG(reg)\
	hubbub1->regs->reg

#घोषणा CTX \
	hubbub1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name

#अगर_घोषित NUM_VMID
#अघोषित NUM_VMID
#पूर्ण_अगर
#घोषणा NUM_VMID 16

bool hubbub2_dcc_support_swizzle(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक bytes_per_element,
		क्रमागत segment_order *segment_order_horz,
		क्रमागत segment_order *segment_order_vert)
अणु
	bool standard_swizzle = false;
	bool display_swizzle = false;
	bool render_swizzle = false;

	चयन (swizzle) अणु
	हाल DC_SW_4KB_S:
	हाल DC_SW_64KB_S:
	हाल DC_SW_VAR_S:
	हाल DC_SW_4KB_S_X:
	हाल DC_SW_64KB_S_X:
	हाल DC_SW_VAR_S_X:
		standard_swizzle = true;
		अवरोध;
	हाल DC_SW_64KB_R_X:
		render_swizzle = true;
		अवरोध;
	हाल DC_SW_4KB_D:
	हाल DC_SW_64KB_D:
	हाल DC_SW_VAR_D:
	हाल DC_SW_4KB_D_X:
	हाल DC_SW_64KB_D_X:
	हाल DC_SW_VAR_D_X:
		display_swizzle = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (standard_swizzle) अणु
		अगर (bytes_per_element == 1) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__na;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 2) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 4) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 8) अणु
			*segment_order_horz = segment_order__na;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
	पूर्ण
	अगर (render_swizzle) अणु
		अगर (bytes_per_element == 2) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 4) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 8) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__non_contiguous;
			वापस true;
		पूर्ण
	पूर्ण
	अगर (display_swizzle && bytes_per_element == 8) अणु
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__non_contiguous;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool hubbub2_dcc_support_pixel_क्रमmat(
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		अचिन्हित पूर्णांक *bytes_per_element)
अणु
	/* DML: get_bytes_per_element */
	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		*bytes_per_element = 2;
		वापस true;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
		*bytes_per_element = 4;
		वापस true;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		*bytes_per_element = 8;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम hubbub2_get_blk256_size(अचिन्हित पूर्णांक *blk256_width, अचिन्हित पूर्णांक *blk256_height,
		अचिन्हित पूर्णांक bytes_per_element)
अणु
	/* copied from DML.  might want to refactor DML to leverage from DML */
	/* DML : get_blk256_size */
	अगर (bytes_per_element == 1) अणु
		*blk256_width = 16;
		*blk256_height = 16;
	पूर्ण अन्यथा अगर (bytes_per_element == 2) अणु
		*blk256_width = 16;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 4) अणु
		*blk256_width = 8;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 8) अणु
		*blk256_width = 8;
		*blk256_height = 4;
	पूर्ण
पूर्ण

अटल व्योम hubbub2_det_request_size(
		अचिन्हित पूर्णांक detile_buf_size,
		अचिन्हित पूर्णांक height,
		अचिन्हित पूर्णांक width,
		अचिन्हित पूर्णांक bpe,
		bool *req128_horz_wc,
		bool *req128_vert_wc)
अणु
	अचिन्हित पूर्णांक blk256_height = 0;
	अचिन्हित पूर्णांक blk256_width = 0;
	अचिन्हित पूर्णांक swath_bytes_horz_wc, swath_bytes_vert_wc;

	hubbub2_get_blk256_size(&blk256_width, &blk256_height, bpe);

	swath_bytes_horz_wc = width * blk256_height * bpe;
	swath_bytes_vert_wc = height * blk256_width * bpe;

	*req128_horz_wc = (2 * swath_bytes_horz_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */

	*req128_vert_wc = (2 * swath_bytes_vert_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */
पूर्ण

bool hubbub2_get_dcc_compression_cap(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output)
अणु
	काष्ठा dc *dc = hubbub->ctx->dc;
	/* implement section 1.6.2.1 of DCN1_Programming_Guide.करोcx */
	क्रमागत dcc_control dcc_control;
	अचिन्हित पूर्णांक bpe;
	क्रमागत segment_order segment_order_horz, segment_order_vert;
	bool req128_horz_wc, req128_vert_wc;

	स_रखो(output, 0, माप(*output));

	अगर (dc->debug.disable_dcc == DCC_DISABLE)
		वापस false;

	अगर (!hubbub->funcs->dcc_support_pixel_क्रमmat(input->क्रमmat,
			&bpe))
		वापस false;

	अगर (!hubbub->funcs->dcc_support_swizzle(input->swizzle_mode, bpe,
			&segment_order_horz, &segment_order_vert))
		वापस false;

	hubbub2_det_request_size(TO_DCN20_HUBBUB(hubbub)->detile_buf_size,
			input->surface_size.height,  input->surface_size.width,
			bpe, &req128_horz_wc, &req128_vert_wc);

	अगर (!req128_horz_wc && !req128_vert_wc) अणु
		dcc_control = dcc_control__256_256_xxx;
	पूर्ण अन्यथा अगर (input->scan == SCAN_सूचीECTION_HORIZONTAL) अणु
		अगर (!req128_horz_wc)
			dcc_control = dcc_control__256_256_xxx;
		अन्यथा अगर (segment_order_horz == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		अन्यथा
			dcc_control = dcc_control__256_64_64;
	पूर्ण अन्यथा अगर (input->scan == SCAN_सूचीECTION_VERTICAL) अणु
		अगर (!req128_vert_wc)
			dcc_control = dcc_control__256_256_xxx;
		अन्यथा अगर (segment_order_vert == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		अन्यथा
			dcc_control = dcc_control__256_64_64;
	पूर्ण अन्यथा अणु
		अगर ((req128_horz_wc &&
			segment_order_horz == segment_order__non_contiguous) ||
			(req128_vert_wc &&
			segment_order_vert == segment_order__non_contiguous))
			/* access_dir not known, must use most स्थिरraining */
			dcc_control = dcc_control__256_64_64;
		अन्यथा
			/* reg128 is true क्रम either horz and vert
			 * but segment_order is contiguous
			 */
			dcc_control = dcc_control__128_128_xxx;
	पूर्ण

	/* Exception क्रम 64KB_R_X */
	अगर ((bpe == 2) && (input->swizzle_mode == DC_SW_64KB_R_X))
		dcc_control = dcc_control__128_128_xxx;

	अगर (dc->debug.disable_dcc == DCC_HALF_REQ_DISALBE &&
		dcc_control != dcc_control__256_256_xxx)
		वापस false;

	चयन (dcc_control) अणु
	हाल dcc_control__256_256_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 256;
		output->grph.rgb.independent_64b_blks = false;
		अवरोध;
	हाल dcc_control__128_128_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 128;
		output->grph.rgb.max_compressed_blk_size = 128;
		output->grph.rgb.independent_64b_blks = false;
		अवरोध;
	हाल dcc_control__256_64_64:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 64;
		output->grph.rgb.independent_64b_blks = true;
		अवरोध;
	शेष:
		ASSERT(false);
		अवरोध;
	पूर्ण
	output->capable = true;
	output->स्थिर_color_support = true;

	वापस true;
पूर्ण

अटल क्रमागत dcn_hubbub_page_table_depth page_table_depth_to_hw(अचिन्हित पूर्णांक page_table_depth)
अणु
	क्रमागत dcn_hubbub_page_table_depth depth = 0;

	चयन (page_table_depth) अणु
	हाल 1:
		depth = DCN_PAGE_TABLE_DEPTH_1_LEVEL;
		अवरोध;
	हाल 2:
		depth = DCN_PAGE_TABLE_DEPTH_2_LEVEL;
		अवरोध;
	हाल 3:
		depth = DCN_PAGE_TABLE_DEPTH_3_LEVEL;
		अवरोध;
	हाल 4:
		depth = DCN_PAGE_TABLE_DEPTH_4_LEVEL;
		अवरोध;
	शेष:
		ASSERT(false);
		अवरोध;
	पूर्ण

	वापस depth;
पूर्ण

अटल क्रमागत dcn_hubbub_page_table_block_size page_table_block_माप_प्रकारo_hw(अचिन्हित पूर्णांक page_table_block_size)
अणु
	क्रमागत dcn_hubbub_page_table_block_size block_size = 0;

	चयन (page_table_block_size) अणु
	हाल 4096:
		block_size = DCN_PAGE_TABLE_BLOCK_SIZE_4KB;
		अवरोध;
	हाल 65536:
		block_size = DCN_PAGE_TABLE_BLOCK_SIZE_64KB;
		अवरोध;
	हाल 32768:
		block_size = DCN_PAGE_TABLE_BLOCK_SIZE_32KB;
		अवरोध;
	शेष:
		ASSERT(false);
		block_size = page_table_block_size;
		अवरोध;
	पूर्ण

	वापस block_size;
पूर्ण

व्योम hubbub2_init_vm_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_virt_addr_config *va_config,
		पूर्णांक vmid)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	काष्ठा dcn_vmid_page_table_config virt_config;

	virt_config.page_table_start_addr = va_config->page_table_start_addr >> 12;
	virt_config.page_table_end_addr = va_config->page_table_end_addr >> 12;
	virt_config.depth = page_table_depth_to_hw(va_config->page_table_depth);
	virt_config.block_size = page_table_block_माप_प्रकारo_hw(va_config->page_table_block_size);
	virt_config.page_table_base_addr = va_config->page_table_base_addr;

	dcn20_vmid_setup(&hubbub1->vmid[vmid], &virt_config);
पूर्ण

पूर्णांक hubbub2_init_dchub_sys_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_phys_addr_config *pa_config)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	काष्ठा dcn_vmid_page_table_config phys_config;

	REG_SET(DCN_VM_FB_LOCATION_BASE, 0,
			FB_BASE, pa_config->प्रणाली_aperture.fb_base >> 24);
	REG_SET(DCN_VM_FB_LOCATION_TOP, 0,
			FB_TOP, pa_config->प्रणाली_aperture.fb_top >> 24);
	REG_SET(DCN_VM_FB_OFFSET, 0,
			FB_OFFSET, pa_config->प्रणाली_aperture.fb_offset >> 24);
	REG_SET(DCN_VM_AGP_BOT, 0,
			AGP_BOT, pa_config->प्रणाली_aperture.agp_bot >> 24);
	REG_SET(DCN_VM_AGP_TOP, 0,
			AGP_TOP, pa_config->प्रणाली_aperture.agp_top >> 24);
	REG_SET(DCN_VM_AGP_BASE, 0,
			AGP_BASE, pa_config->प्रणाली_aperture.agp_base >> 24);

	REG_SET(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_MSB, 0,
			DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_MSB, (pa_config->page_table_शेष_page_addr >> 44) & 0xF);
	REG_SET(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_LSB, 0,
			DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_LSB, (pa_config->page_table_शेष_page_addr >> 12) & 0xFFFFFFFF);

	अगर (pa_config->gart_config.page_table_start_addr != pa_config->gart_config.page_table_end_addr) अणु
		phys_config.page_table_start_addr = pa_config->gart_config.page_table_start_addr >> 12;
		phys_config.page_table_end_addr = pa_config->gart_config.page_table_end_addr >> 12;
		phys_config.page_table_base_addr = pa_config->gart_config.page_table_base_addr;
		phys_config.depth = 0;
		phys_config.block_size = 0;
		// Init VMID 0 based on PA config
		dcn20_vmid_setup(&hubbub1->vmid[0], &phys_config);
	पूर्ण

	वापस NUM_VMID;
पूर्ण

व्योम hubbub2_update_dchub(काष्ठा hubbub *hubbub,
		काष्ठा dchub_init_data *dh_data)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	अगर (REG(DCN_VM_FB_LOCATION_TOP) == 0)
		वापस;

	चयन (dh_data->fb_mode) अणु
	हाल FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB हाल need to put DCHUB FB BASE and TOP upside करोwn to indicate ZFB mode*/
		REG_UPDATE(DCN_VM_FB_LOCATION_TOP,
				FB_TOP, 0);

		REG_UPDATE(DCN_VM_FB_LOCATION_BASE,
				FB_BASE, 0xFFFFFF);

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 24);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 24);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 24);
		अवरोध;
	हाल FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (करोne by VBIOS on AsicInit table)*/

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 24);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 24);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 24);
		अवरोध;
	हाल FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (should be करोne by VBIOS)*/

		/*This field defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		REG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, 0);

		/*This field defines the bottom range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, 0xFFFFFF);

		/*This field defines the top range of the AGP aperture and represents the 24*/
		/*MSBs, bits [47:24] of the 48 address bits*/
		REG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
पूर्ण

व्योम hubbub2_wm_पढ़ो_state(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_wm *wm)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	काष्ठा dcn_hubbub_wm_set *s;

	स_रखो(wm, 0, माप(काष्ठा dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A);
	अगर (REG(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A))
		s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A);

	s = &wm->sets[1];
	s->wm_set = 1;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B);
	अगर (REG(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B))
		s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B);

	s = &wm->sets[2];
	s->wm_set = 2;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C);
	अगर (REG(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C))
		s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C);

	s = &wm->sets[3];
	s->wm_set = 3;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D);
	अगर (REG(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D))
		s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D);
पूर्ण

व्योम hubbub2_get_dchub_ref_freq(काष्ठा hubbub *hubbub,
		अचिन्हित पूर्णांक dccg_ref_freq_inKhz,
		अचिन्हित पूर्णांक *dchub_ref_freq_inKhz)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uपूर्णांक32_t ref_भाग = 0;
	uपूर्णांक32_t ref_en = 0;

	REG_GET_2(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, &ref_भाग,
			DCHUBBUB_GLOBAL_TIMER_ENABLE, &ref_en);

	अगर (ref_en) अणु
		अगर (ref_भाग == 2)
			*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz / 2;
		अन्यथा
			*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz;

		// DC hub reference frequency must be around 50Mhz, otherwise there may be
		// overflow/underflow issues when करोing HUBBUB programming
		अगर (*dchub_ref_freq_inKhz < 40000 || *dchub_ref_freq_inKhz > 60000)
			ASSERT_CRITICAL(false);

		वापस;
	पूर्ण अन्यथा अणु
		*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz;

		// HUBBUB global समयr must be enabled.
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण
पूर्ण

अटल bool hubbub2_program_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	bool wm_pending = false;
	/*
	 * Need to clamp to max of the रेजिस्टर values (i.e. no wrap)
	 * क्रम dcn1, all wm रेजिस्टरs are 21-bit wide
	 */
	अगर (hubbub1_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	अगर (hubbub1_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	/*
	 * There's a special हाल when going from p-state support to p-state unsupported
	 * here we are going to LOWER watermarks to go to dummy p-state only, but this has
	 * to be करोne prepare_bandwidth, not optimize
	 */
	अगर (hubbub1->base.ctx->dc->clk_mgr->clks.prev_p_state_change_support == true &&
		hubbub1->base.ctx->dc->clk_mgr->clks.p_state_change_support == false)
		safe_to_lower = true;

	hubbub1_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);

	REG_SET(DCHUBBUB_ARB_SAT_LEVEL, 0,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND, DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 180);

	hubbub->funcs->allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);
	वापस wm_pending;
पूर्ण

अटल स्थिर काष्ठा hubbub_funcs hubbub2_funcs = अणु
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub2_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_support_swizzle = hubbub2_dcc_support_swizzle,
	.dcc_support_pixel_क्रमmat = hubbub2_dcc_support_pixel_क्रमmat,
	.get_dcc_compression_cap = hubbub2_get_dcc_compression_cap,
	.wm_पढ़ो_state = hubbub2_wm_पढ़ो_state,
	.get_dchub_ref_freq = hubbub2_get_dchub_ref_freq,
	.program_watermarks = hubbub2_program_watermarks,
	.is_allow_self_refresh_enabled = hubbub1_is_allow_self_refresh_enabled,
	.allow_self_refresh_control = hubbub1_allow_self_refresh_control,
पूर्ण;

व्योम hubbub2_स्थिरruct(काष्ठा dcn20_hubbub *hubbub,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask)
अणु
	hubbub->base.ctx = ctx;

	hubbub->base.funcs = &hubbub2_funcs;

	hubbub->regs = hubbub_regs;
	hubbub->shअगरts = hubbub_shअगरt;
	hubbub->masks = hubbub_mask;

	hubbub->debug_test_index_pstate = 0xB;
	hubbub->detile_buf_size = 164 * 1024; /* 164KB क्रम DCN2.0 */
पूर्ण
