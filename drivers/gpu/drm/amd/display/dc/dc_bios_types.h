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

#अगर_अघोषित DC_BIOS_TYPES_H
#घोषणा DC_BIOS_TYPES_H

/******************************************************************************
 * Interface file क्रम VBIOS implementations.
 *
 * The शेष implementation is inside DC.
 * Display Manager (which instantiates DC) has the option to supply it's own
 * (बाह्यal to DC) implementation of VBIOS, which will be called by DC, using
 * this पूर्णांकerface.
 * (The पूर्णांकended use is Diagnostics, but other uses may appear.)
 *****************************************************************************/

#समावेश "include/bios_parser_types.h"

काष्ठा dc_vbios_funcs अणु
	uपूर्णांक8_t (*get_connectors_number)(काष्ठा dc_bios *bios);

	काष्ठा graphics_object_id (*get_connector_id)(
		काष्ठा dc_bios *bios,
		uपूर्णांक8_t connector_index);
	क्रमागत bp_result (*get_src_obj)(
		काष्ठा dc_bios *bios,
		काष्ठा graphics_object_id object_id, uपूर्णांक32_t index,
		काष्ठा graphics_object_id *src_object_id);
	क्रमागत bp_result (*get_i2c_info)(
		काष्ठा dc_bios *dcb,
		काष्ठा graphics_object_id id,
		काष्ठा graphics_object_i2c_info *info);
	क्रमागत bp_result (*get_hpd_info)(
		काष्ठा dc_bios *bios,
		काष्ठा graphics_object_id id,
		काष्ठा graphics_object_hpd_info *info);
	क्रमागत bp_result (*get_device_tag)(
		काष्ठा dc_bios *bios,
		काष्ठा graphics_object_id connector_object_id,
		uपूर्णांक32_t device_tag_index,
		काष्ठा connector_device_tag_info *info);
	क्रमागत bp_result (*get_spपढ़ो_spectrum_info)(
		काष्ठा dc_bios *bios,
		क्रमागत as_संकेत_type संकेत,
		uपूर्णांक32_t index,
		काष्ठा spपढ़ो_spectrum_info *ss_info);
	uपूर्णांक32_t (*get_ss_entry_number)(
		काष्ठा dc_bios *bios,
		क्रमागत as_संकेत_type संकेत);
	क्रमागत bp_result (*get_embedded_panel_info)(
		काष्ठा dc_bios *bios,
		काष्ठा embedded_panel_info *info);
	क्रमागत bp_result (*get_gpio_pin_info)(
		काष्ठा dc_bios *bios,
		uपूर्णांक32_t gpio_id,
		काष्ठा gpio_pin_info *info);
	क्रमागत bp_result (*get_encoder_cap_info)(
		काष्ठा dc_bios *bios,
		काष्ठा graphics_object_id object_id,
		काष्ठा bp_encoder_cap_info *info);

	bool (*is_accelerated_mode)(
		काष्ठा dc_bios *bios);
	व्योम (*set_scratch_critical_state)(
		काष्ठा dc_bios *bios,
		bool state);
	bool (*is_device_id_supported)(
		काष्ठा dc_bios *bios,
		काष्ठा device_id id);
	/* COMMANDS */

	क्रमागत bp_result (*encoder_control)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_encoder_control *cntl);
	क्रमागत bp_result (*transmitter_control)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_transmitter_control *cntl);
	क्रमागत bp_result (*enable_crtc)(
		काष्ठा dc_bios *bios,
		क्रमागत controller_id id,
		bool enable);
	क्रमागत bp_result (*adjust_pixel_घड़ी)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*set_pixel_घड़ी)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*set_dce_घड़ी)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_set_dce_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*enable_spपढ़ो_spectrum_on_ppll)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
		bool enable);
	क्रमागत bp_result (*program_crtc_timing)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_hw_crtc_timing_parameters *bp_params);
	क्रमागत bp_result (*program_display_engine_pll)(
		काष्ठा dc_bios *bios,
		काष्ठा bp_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*enable_disp_घातer_gating)(
		काष्ठा dc_bios *bios,
		क्रमागत controller_id controller_id,
		क्रमागत bp_pipe_control_action action);

	व्योम (*bios_parser_destroy)(काष्ठा dc_bios **dcb);

	क्रमागत bp_result (*get_board_layout_info)(
		काष्ठा dc_bios *dcb,
		काष्ठा board_layout_info *board_layout_info);
	uपूर्णांक16_t (*pack_data_tables)(
		काष्ठा dc_bios *dcb,
		व्योम *dst);

	क्रमागत bp_result (*get_atom_dc_golden_table)(
			काष्ठा dc_bios *dcb);

	क्रमागत bp_result (*enable_lvपंचांगa_control)(
		काष्ठा dc_bios *bios,
		uपूर्णांक8_t uc_pwr_on,
		uपूर्णांक8_t panel_instance);

	क्रमागत bp_result (*get_soc_bb_info)(
		काष्ठा dc_bios *dcb,
		काष्ठा bp_soc_bb_info *soc_bb_info);

	क्रमागत bp_result (*get_disp_connector_caps_info)(
			काष्ठा dc_bios *dcb,
			काष्ठा graphics_object_id object_id,
			काष्ठा bp_disp_connector_caps_info *info);
	क्रमागत bp_result (*get_lttpr_caps)(
			काष्ठा dc_bios *dcb,
			uपूर्णांक8_t *dce_caps);
	क्रमागत bp_result (*get_lttpr_पूर्णांकerop)(
			काष्ठा dc_bios *dcb,
			uपूर्णांक8_t *dce_caps);
पूर्ण;

काष्ठा bios_रेजिस्टरs अणु
	uपूर्णांक32_t BIOS_SCRATCH_3;
	uपूर्णांक32_t BIOS_SCRATCH_6;
पूर्ण;

काष्ठा dc_bios अणु
	स्थिर काष्ठा dc_vbios_funcs *funcs;

	uपूर्णांक8_t *bios;
	uपूर्णांक32_t bios_size;

	uपूर्णांक8_t *bios_local_image;

	काष्ठा dc_context *ctx;
	स्थिर काष्ठा bios_रेजिस्टरs *regs;
	काष्ठा पूर्णांकegrated_info *पूर्णांकegrated_info;
	काष्ठा dc_firmware_info fw_info;
	bool fw_info_valid;
	काष्ठा dc_vram_info vram_info;
	काष्ठा dc_golden_table golden_table;
पूर्ण;

#पूर्ण_अगर /* DC_BIOS_TYPES_H */
