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

#अगर_अघोषित __DC_COMPRESSOR_DCE112_H__
#घोषणा __DC_COMPRESSOR_DCE112_H__

#समावेश "../inc/compressor.h"

#घोषणा TO_DCE112_COMPRESSOR(compressor)\
	container_of(compressor, काष्ठा dce112_compressor, base)

काष्ठा dce112_compressor_reg_offsets अणु
	uपूर्णांक32_t dcp_offset;
	uपूर्णांक32_t dmअगर_offset;
पूर्ण;

काष्ठा dce112_compressor अणु
	काष्ठा compressor base;
	काष्ठा dce112_compressor_reg_offsets offsets;
पूर्ण;

काष्ठा compressor *dce112_compressor_create(काष्ठा dc_context *ctx);

व्योम dce112_compressor_स्थिरruct(काष्ठा dce112_compressor *cp110,
	काष्ठा dc_context *ctx);

व्योम dce112_compressor_destroy(काष्ठा compressor **cp);

/* FBC RELATED */
व्योम dce112_compressor_घातer_up_fbc(काष्ठा compressor *cp);

व्योम dce112_compressor_enable_fbc(काष्ठा compressor *cp, uपूर्णांक32_t paths_num,
	काष्ठा compr_addr_and_pitch_params *params);

व्योम dce112_compressor_disable_fbc(काष्ठा compressor *cp);

व्योम dce112_compressor_set_fbc_invalidation_triggers(काष्ठा compressor *cp,
	uपूर्णांक32_t fbc_trigger);

व्योम dce112_compressor_program_compressed_surface_address_and_pitch(
	काष्ठा compressor *cp,
	काष्ठा compr_addr_and_pitch_params *params);

bool dce112_compressor_is_fbc_enabled_in_hw(काष्ठा compressor *cp,
	uपूर्णांक32_t *fbc_mapped_crtc_id);

/* LPT RELATED */
व्योम dce112_compressor_enable_lpt(काष्ठा compressor *cp);

व्योम dce112_compressor_disable_lpt(काष्ठा compressor *cp);

व्योम dce112_compressor_program_lpt_control(काष्ठा compressor *cp,
	काष्ठा compr_addr_and_pitch_params *params);

bool dce112_compressor_is_lpt_enabled_in_hw(काष्ठा compressor *cp);

#पूर्ण_अगर
