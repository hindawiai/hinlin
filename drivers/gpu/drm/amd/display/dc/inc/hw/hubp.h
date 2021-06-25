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

#अगर_अघोषित __DAL_HUBP_H__
#घोषणा __DAL_HUBP_H__

#समावेश "mem_input.h"

#घोषणा OPP_ID_INVALID 0xf
#घोषणा MAX_TTU 0xffffff


क्रमागत cursor_pitch अणु
	CURSOR_PITCH_64_PIXELS = 0,
	CURSOR_PITCH_128_PIXELS,
	CURSOR_PITCH_256_PIXELS
पूर्ण;

क्रमागत cursor_lines_per_chunk अणु
	CURSOR_LINE_PER_CHUNK_1 = 0, /* new क्रम DCN2 */
	CURSOR_LINE_PER_CHUNK_2 = 1,
	CURSOR_LINE_PER_CHUNK_4,
	CURSOR_LINE_PER_CHUNK_8,
	CURSOR_LINE_PER_CHUNK_16
पूर्ण;

क्रमागत hubp_ind_block_size अणु
	hubp_ind_block_unस्थिरrained = 0,
	hubp_ind_block_64b,
	hubp_ind_block_128b,
	hubp_ind_block_64b_no_128bcl,
पूर्ण;

काष्ठा hubp अणु
	स्थिर काष्ठा hubp_funcs *funcs;
	काष्ठा dc_context *ctx;
	काष्ठा dc_plane_address request_address;
	पूर्णांक inst;

	/* run समय states */
	पूर्णांक opp_id;
	पूर्णांक mpcc_id;
	काष्ठा dc_cursor_attributes curs_attr;
	bool घातer_gated;
पूर्ण;

काष्ठा surface_flip_रेजिस्टरs अणु
	uपूर्णांक32_t DCSURF_SURFACE_CONTROL;
	uपूर्णांक32_t DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t DCSURF_PRIMARY_META_SURFACE_ADDRESS;
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS;
	uपूर्णांक32_t DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C;
	uपूर्णांक32_t DCSURF_PRIMARY_META_SURFACE_ADDRESS_C;
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C;
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_C;
	uपूर्णांक32_t DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t DCSURF_SECONDARY_META_SURFACE_ADDRESS;
	uपूर्णांक32_t DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t DCSURF_SECONDARY_SURFACE_ADDRESS;
	bool पंचांगz_surface;
	bool immediate;
	uपूर्णांक8_t vmid;
	bool grph_stereo;
पूर्ण;

काष्ठा hubp_funcs अणु
	व्योम (*hubp_setup)(
			काष्ठा hubp *hubp,
			काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs,
			काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs,
			काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
			काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest);

	व्योम (*hubp_setup_पूर्णांकerdependent)(
			काष्ठा hubp *hubp,
			काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs,
			काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs);

	व्योम (*dcc_control)(काष्ठा hubp *hubp, bool enable,
			क्रमागत hubp_ind_block_size blk_size);

	व्योम (*mem_program_viewport)(
			काष्ठा hubp *hubp,
			स्थिर काष्ठा rect *viewport,
			स्थिर काष्ठा rect *viewport_c);

	bool (*hubp_program_surface_flip_and_addr)(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_plane_address *address,
		bool flip_immediate);

	व्योम (*hubp_program_pte_vm)(
		काष्ठा hubp *hubp,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		क्रमागत dc_rotation_angle rotation);

	व्योम (*hubp_set_vm_प्रणाली_aperture_settings)(
			काष्ठा hubp *hubp,
			काष्ठा vm_प्रणाली_aperture_param *apt);

	व्योम (*hubp_set_vm_context0_settings)(
			काष्ठा hubp *hubp,
			स्थिर काष्ठा vm_context0_param *vm0);

	व्योम (*hubp_program_surface_config)(
		काष्ठा hubp *hubp,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		काष्ठा plane_size *plane_size,
		क्रमागत dc_rotation_angle rotation,
		काष्ठा dc_plane_dcc_param *dcc,
		bool horizontal_mirror,
		अचिन्हित पूर्णांक compa_level);

	bool (*hubp_is_flip_pending)(काष्ठा hubp *hubp);

	व्योम (*set_blank)(काष्ठा hubp *hubp, bool blank);
	व्योम (*set_hubp_blank_en)(काष्ठा hubp *hubp, bool blank);

	व्योम (*set_cursor_attributes)(
			काष्ठा hubp *hubp,
			स्थिर काष्ठा dc_cursor_attributes *attr);

	व्योम (*set_cursor_position)(
			काष्ठा hubp *hubp,
			स्थिर काष्ठा dc_cursor_position *pos,
			स्थिर काष्ठा dc_cursor_mi_param *param);

	व्योम (*hubp_disconnect)(काष्ठा hubp *hubp);

	व्योम (*hubp_clk_cntl)(काष्ठा hubp *hubp, bool enable);
	व्योम (*hubp_vtg_sel)(काष्ठा hubp *hubp, uपूर्णांक32_t otg_inst);
	व्योम (*hubp_पढ़ो_state)(काष्ठा hubp *hubp);
	व्योम (*hubp_clear_underflow)(काष्ठा hubp *hubp);
	व्योम (*hubp_disable_control)(काष्ठा hubp *hubp, bool disable_hubp);
	अचिन्हित पूर्णांक (*hubp_get_underflow_status)(काष्ठा hubp *hubp);
	व्योम (*hubp_init)(काष्ठा hubp *hubp);

	व्योम (*dmdata_set_attributes)(
			काष्ठा hubp *hubp,
			स्थिर काष्ठा dc_dmdata_attributes *attr);

	व्योम (*dmdata_load)(
			काष्ठा hubp *hubp,
			uपूर्णांक32_t dmdata_sw_size,
			स्थिर uपूर्णांक32_t *dmdata_sw_data);
	bool (*dmdata_status_करोne)(काष्ठा hubp *hubp);
	व्योम (*hubp_enable_tripleBuffer)(
		काष्ठा hubp *hubp,
		bool enable);

	bool (*hubp_is_triplebuffer_enabled)(
		काष्ठा hubp *hubp);

	व्योम (*hubp_set_flip_control_surface_gsl)(
		काष्ठा hubp *hubp,
		bool enable);

	व्योम (*validate_dml_output)(
			काष्ठा hubp *hubp,
			काष्ठा dc_context *ctx,
			काष्ठा _vcs_dpi_display_rq_regs_st *dml_rq_regs,
			काष्ठा _vcs_dpi_display_dlg_regs_st *dml_dlg_attr,
			काष्ठा _vcs_dpi_display_ttu_regs_st *dml_ttu_attr);
	व्योम (*set_unbounded_requesting)(
		काष्ठा hubp *hubp,
		bool enable);
	bool (*hubp_in_blank)(काष्ठा hubp *hubp);
	व्योम (*hubp_soft_reset)(काष्ठा hubp *hubp, bool reset);

	व्योम (*hubp_set_flip_पूर्णांक)(काष्ठा hubp *hubp);

पूर्ण;

#पूर्ण_अगर
