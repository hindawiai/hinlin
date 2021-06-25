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
#अगर_अघोषित __DAL_MEM_INPUT_H__
#घोषणा __DAL_MEM_INPUT_H__

#समावेश "dc.h"
#समावेश "include/grph_object_id.h"

#समावेश "dml/display_mode_structs.h"

काष्ठा dchub_init_data;
काष्ठा cstate_pstate_watermarks_st अणु
	uपूर्णांक32_t cstate_निकास_ns;
	uपूर्णांक32_t cstate_enter_plus_निकास_ns;
	uपूर्णांक32_t pstate_change_ns;
पूर्ण;

काष्ठा dcn_watermarks अणु
	uपूर्णांक32_t pte_meta_urgent_ns;
	uपूर्णांक32_t urgent_ns;
	uपूर्णांक32_t frac_urg_bw_nom;
	uपूर्णांक32_t frac_urg_bw_flip;
	पूर्णांक32_t urgent_latency_ns;
	काष्ठा cstate_pstate_watermarks_st cstate_pstate;
पूर्ण;

काष्ठा dcn_watermark_set अणु
	काष्ठा dcn_watermarks a;
	काष्ठा dcn_watermarks b;
	काष्ठा dcn_watermarks c;
	काष्ठा dcn_watermarks d;
पूर्ण;

काष्ठा dce_watermarks अणु
	पूर्णांक a_mark;
	पूर्णांक b_mark;
	पूर्णांक c_mark;
	पूर्णांक d_mark;
पूर्ण;

काष्ठा stutter_modes अणु
	bool enhanced;
	bool quad_dmअगर_buffer;
	bool watermark_nb_pstate;
पूर्ण;

काष्ठा mem_input अणु
	स्थिर काष्ठा mem_input_funcs *funcs;
	काष्ठा dc_context *ctx;
	काष्ठा dc_plane_address request_address;
	काष्ठा dc_plane_address current_address;
	पूर्णांक inst;
	काष्ठा stutter_modes stutter_mode;
पूर्ण;

काष्ठा vm_प्रणाली_aperture_param अणु
	PHYSICAL_ADDRESS_LOC sys_शेष;
	PHYSICAL_ADDRESS_LOC sys_low;
	PHYSICAL_ADDRESS_LOC sys_high;
पूर्ण;

काष्ठा vm_context0_param अणु
	PHYSICAL_ADDRESS_LOC pte_base;
	PHYSICAL_ADDRESS_LOC pte_start;
	PHYSICAL_ADDRESS_LOC pte_end;
	PHYSICAL_ADDRESS_LOC fault_शेष;
पूर्ण;

काष्ठा mem_input_funcs अणु
	व्योम (*mem_input_setup)(
			काष्ठा mem_input *mem_input,
			काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs,
			काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs,
			काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
			काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest);

	व्योम (*dcc_control)(काष्ठा mem_input *mem_input, bool enable,
			bool independent_64b_blks);
	व्योम (*mem_program_viewport)(
			काष्ठा mem_input *mem_input,
			स्थिर काष्ठा rect *viewport,
			स्थिर काष्ठा rect *viewport_c);

	व्योम (*mem_input_program_display_marks)(
		काष्ठा mem_input *mem_input,
		काष्ठा dce_watermarks nbp,
		काष्ठा dce_watermarks stutter,
		काष्ठा dce_watermarks stutter_enter,
		काष्ठा dce_watermarks urgent,
		uपूर्णांक32_t total_dest_line_समय_ns);

	व्योम (*mem_input_program_chroma_display_marks)(
			काष्ठा mem_input *mem_input,
			काष्ठा dce_watermarks nbp,
			काष्ठा dce_watermarks stutter,
			काष्ठा dce_watermarks urgent,
			uपूर्णांक32_t total_dest_line_समय_ns);

	व्योम (*allocate_mem_input)(
		काष्ठा mem_input *mem_input,
		uपूर्णांक32_t h_total,/* क्रम current target */
		uपूर्णांक32_t v_total,/* क्रम current target */
		uपूर्णांक32_t pix_clk_khz,/* क्रम current target */
		uपूर्णांक32_t total_streams_num);

	व्योम (*मुक्त_mem_input)(
		काष्ठा mem_input *mem_input,
		uपूर्णांक32_t paths_num);

	bool (*mem_input_program_surface_flip_and_addr)(
		काष्ठा mem_input *mem_input,
		स्थिर काष्ठा dc_plane_address *address,
		bool flip_immediate);

	व्योम (*mem_input_program_pte_vm)(
		काष्ठा mem_input *mem_input,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		क्रमागत dc_rotation_angle rotation);

	व्योम (*mem_input_set_vm_प्रणाली_aperture_settings)(
			काष्ठा mem_input *mem_input,
			काष्ठा vm_प्रणाली_aperture_param *apt);

	व्योम (*mem_input_set_vm_context0_settings)(
			काष्ठा mem_input *mem_input,
			स्थिर काष्ठा vm_context0_param *vm0);

	व्योम (*mem_input_program_surface_config)(
		काष्ठा mem_input *mem_input,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		काष्ठा plane_size *plane_size,
		क्रमागत dc_rotation_angle rotation,
		काष्ठा dc_plane_dcc_param *dcc,
		bool horizontal_mirror);

	bool (*mem_input_is_flip_pending)(काष्ठा mem_input *mem_input);

	व्योम (*mem_input_update_dchub)(काष्ठा mem_input *mem_input,
				काष्ठा dchub_init_data *dh_data);

	व्योम (*set_blank)(काष्ठा mem_input *mi, bool blank);
	व्योम (*set_hubp_blank_en)(काष्ठा mem_input *mi, bool blank);

	व्योम (*set_cursor_attributes)(
			काष्ठा mem_input *mem_input,
			स्थिर काष्ठा dc_cursor_attributes *attr);

	व्योम (*set_cursor_position)(
			काष्ठा mem_input *mem_input,
			स्थिर काष्ठा dc_cursor_position *pos,
			स्थिर काष्ठा dc_cursor_mi_param *param);

पूर्ण;

#पूर्ण_अगर
