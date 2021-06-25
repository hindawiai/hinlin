<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_DMCU_H__
#घोषणा __DC_DMCU_H__

#समावेश "dm_services_types.h"

/* If HW itself ever घातered करोwn it will be 0.
 * fwDmcuInit will ग_लिखो to 1.
 * Driver will only call MCP init अगर current state is 1,
 * and the MCP command will transition this to 2.
 */
क्रमागत dmcu_state अणु
	DMCU_UNLOADED = 0,
	DMCU_LOADED_UNINITIALIZED = 1,
	DMCU_RUNNING = 2,
पूर्ण;

काष्ठा dmcu_version अणु
	अचिन्हित पूर्णांक पूर्णांकerface_version;
	अचिन्हित पूर्णांक abm_version;
	अचिन्हित पूर्णांक psr_version;
	अचिन्हित पूर्णांक build_version;
पूर्ण;

काष्ठा dmcu अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dmcu_funcs *funcs;

	क्रमागत dmcu_state dmcu_state;
	काष्ठा dmcu_version dmcu_version;
	अचिन्हित पूर्णांक cached_रुको_loop_number;
	uपूर्णांक32_t psp_version;
	bool स्वतः_load_dmcu;
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
काष्ठा crc_region अणु
	uपूर्णांक16_t x_start;
	uपूर्णांक16_t y_start;
	uपूर्णांक16_t x_end;
	uपूर्णांक16_t y_end;
पूर्ण;

काष्ठा otg_phy_mux अणु
	uपूर्णांक8_t phy_output_num;
	uपूर्णांक8_t otg_output_num;
पूर्ण;
#पूर्ण_अगर

काष्ठा dmcu_funcs अणु
	bool (*dmcu_init)(काष्ठा dmcu *dmcu);
	bool (*load_iram)(काष्ठा dmcu *dmcu,
			अचिन्हित पूर्णांक start_offset,
			स्थिर अक्षर *src,
			अचिन्हित पूर्णांक bytes);
	व्योम (*set_psr_enable)(काष्ठा dmcu *dmcu, bool enable, bool रुको);
	bool (*setup_psr)(काष्ठा dmcu *dmcu,
			काष्ठा dc_link *link,
			काष्ठा psr_context *psr_context);
	व्योम (*get_psr_state)(काष्ठा dmcu *dmcu, क्रमागत dc_psr_state *dc_psr_state);
	व्योम (*set_psr_रुको_loop)(काष्ठा dmcu *dmcu,
			अचिन्हित पूर्णांक रुको_loop_number);
	व्योम (*get_psr_रुको_loop)(काष्ठा dmcu *dmcu,
			अचिन्हित पूर्णांक *psr_रुको_loop_number);
	bool (*is_dmcu_initialized)(काष्ठा dmcu *dmcu);
	bool (*lock_phy)(काष्ठा dmcu *dmcu);
	bool (*unlock_phy)(काष्ठा dmcu *dmcu);
	bool (*send_edid_cea)(काष्ठा dmcu *dmcu,
			पूर्णांक offset,
			पूर्णांक total_length,
			uपूर्णांक8_t *data,
			पूर्णांक length);
	bool (*recv_amd_vsdb)(काष्ठा dmcu *dmcu,
			पूर्णांक *version,
			पूर्णांक *min_frame_rate,
			पूर्णांक *max_frame_rate);
	bool (*recv_edid_cea_ack)(काष्ठा dmcu *dmcu, पूर्णांक *offset);
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	व्योम (*क्रमward_crc_winकरोw)(काष्ठा dmcu *dmcu,
			काष्ठा crc_region *crc_win,
			काष्ठा otg_phy_mux *mux_mapping);
	व्योम (*stop_crc_win_update)(काष्ठा dmcu *dmcu,
			काष्ठा otg_phy_mux *mux_mapping);
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
