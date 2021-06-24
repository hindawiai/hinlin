<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_DCHUBBUB_H__
#घोषणा __DAL_DCHUBBUB_H__


क्रमागत dcc_control अणु
	dcc_control__256_256_xxx,
	dcc_control__128_128_xxx,
	dcc_control__256_64_64,
	dcc_control__256_128_128,
पूर्ण;

क्रमागत segment_order अणु
	segment_order__na,
	segment_order__contiguous,
	segment_order__non_contiguous,
पूर्ण;

काष्ठा dcn_hubbub_wm_set अणु
	uपूर्णांक32_t wm_set;
	uपूर्णांक32_t data_urgent;
	uपूर्णांक32_t pte_meta_urgent;
	uपूर्णांक32_t sr_enter;
	uपूर्णांक32_t sr_निकास;
	uपूर्णांक32_t dram_clk_chanage;
पूर्ण;

काष्ठा dcn_hubbub_wm अणु
	काष्ठा dcn_hubbub_wm_set sets[4];
पूर्ण;

क्रमागत dcn_hubbub_page_table_depth अणु
	DCN_PAGE_TABLE_DEPTH_1_LEVEL,
	DCN_PAGE_TABLE_DEPTH_2_LEVEL,
	DCN_PAGE_TABLE_DEPTH_3_LEVEL,
	DCN_PAGE_TABLE_DEPTH_4_LEVEL
पूर्ण;

क्रमागत dcn_hubbub_page_table_block_size अणु
	DCN_PAGE_TABLE_BLOCK_SIZE_4KB = 0,
	DCN_PAGE_TABLE_BLOCK_SIZE_64KB = 4,
	DCN_PAGE_TABLE_BLOCK_SIZE_32KB = 3
पूर्ण;

काष्ठा dcn_hubbub_phys_addr_config अणु
	काष्ठा अणु
		uपूर्णांक64_t fb_top;
		uपूर्णांक64_t fb_offset;
		uपूर्णांक64_t fb_base;
		uपूर्णांक64_t agp_top;
		uपूर्णांक64_t agp_bot;
		uपूर्णांक64_t agp_base;
	पूर्ण प्रणाली_aperture;

	काष्ठा अणु
		uपूर्णांक64_t page_table_start_addr;
		uपूर्णांक64_t page_table_end_addr;
		uपूर्णांक64_t page_table_base_addr;
	पूर्ण gart_config;

	uपूर्णांक64_t page_table_शेष_page_addr;
पूर्ण;

काष्ठा dcn_hubbub_virt_addr_config अणु
	uपूर्णांक64_t				page_table_start_addr;
	uपूर्णांक64_t				page_table_end_addr;
	क्रमागत dcn_hubbub_page_table_block_size	page_table_block_size;
	क्रमागत dcn_hubbub_page_table_depth	page_table_depth;
	uपूर्णांक64_t				page_table_base_addr;
पूर्ण;

काष्ठा hubbub_addr_config अणु
	काष्ठा dcn_hubbub_phys_addr_config pa_config;
	काष्ठा dcn_hubbub_virt_addr_config va_config;
	काष्ठा अणु
		uपूर्णांक64_t aperture_check_fault;
		uपूर्णांक64_t generic_fault;
	पूर्ण शेष_addrs;
पूर्ण;

काष्ठा hubbub_funcs अणु
	व्योम (*update_dchub)(
			काष्ठा hubbub *hubbub,
			काष्ठा dchub_init_data *dh_data);

	पूर्णांक (*init_dchub_sys_ctx)(
			काष्ठा hubbub *hubbub,
			काष्ठा dcn_hubbub_phys_addr_config *pa_config);
	व्योम (*init_vm_ctx)(
			काष्ठा hubbub *hubbub,
			काष्ठा dcn_hubbub_virt_addr_config *va_config,
			पूर्णांक vmid);

	bool (*get_dcc_compression_cap)(काष्ठा hubbub *hubbub,
			स्थिर काष्ठा dc_dcc_surface_param *input,
			काष्ठा dc_surface_dcc_cap *output);

	bool (*dcc_support_swizzle)(
			क्रमागत swizzle_mode_values swizzle,
			अचिन्हित पूर्णांक bytes_per_element,
			क्रमागत segment_order *segment_order_horz,
			क्रमागत segment_order *segment_order_vert);

	bool (*dcc_support_pixel_क्रमmat)(
			क्रमागत surface_pixel_क्रमmat क्रमmat,
			अचिन्हित पूर्णांक *bytes_per_element);

	व्योम (*wm_पढ़ो_state)(काष्ठा hubbub *hubbub,
			काष्ठा dcn_hubbub_wm *wm);

	व्योम (*get_dchub_ref_freq)(काष्ठा hubbub *hubbub,
			अचिन्हित पूर्णांक dccg_ref_freq_inKhz,
			अचिन्हित पूर्णांक *dchub_ref_freq_inKhz);

	bool (*program_watermarks)(
			काष्ठा hubbub *hubbub,
			काष्ठा dcn_watermark_set *watermarks,
			अचिन्हित पूर्णांक refclk_mhz,
			bool safe_to_lower);

	bool (*is_allow_self_refresh_enabled)(काष्ठा hubbub *hubbub);
	व्योम (*allow_self_refresh_control)(काष्ठा hubbub *hubbub, bool allow);

	व्योम (*apply_DEDCN21_147_wa)(काष्ठा hubbub *hubbub);

	व्योम (*क्रमce_wm_propagate_to_pipes)(काष्ठा hubbub *hubbub);

	व्योम (*क्रमce_pstate_change_control)(काष्ठा hubbub *hubbub, bool क्रमce, bool allow);

	व्योम (*init_watermarks)(काष्ठा hubbub *hubbub);
पूर्ण;

काष्ठा hubbub अणु
	स्थिर काष्ठा hubbub_funcs *funcs;
	काष्ठा dc_context *ctx;
	bool riommu_active;
पूर्ण;

#पूर्ण_अगर
