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

#अगर_अघोषित __DC_ABM_H__
#घोषणा __DC_ABM_H__

#समावेश "dm_services_types.h"

काष्ठा abm अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा abm_funcs *funcs;
	bool dmcu_is_running;
पूर्ण;

काष्ठा abm_funcs अणु
	व्योम (*abm_init)(काष्ठा abm *abm, uपूर्णांक32_t back_light);
	bool (*set_abm_level)(काष्ठा abm *abm, अचिन्हित पूर्णांक abm_level);
	bool (*set_abm_immediate_disable)(काष्ठा abm *abm, अचिन्हित पूर्णांक panel_inst);
	bool (*set_pipe)(काष्ठा abm *abm, अचिन्हित पूर्णांक controller_id, अचिन्हित पूर्णांक panel_inst);

	/* backlight_pwm_u16_16 is अचिन्हित 32 bit,
	 * 16 bit पूर्णांकeger + 16 fractional, where 1.0 is max backlight value.
	 */
	bool (*set_backlight_level_pwm)(काष्ठा abm *abm,
			अचिन्हित पूर्णांक backlight_pwm_u16_16,
			अचिन्हित पूर्णांक frame_ramp,
			अचिन्हित पूर्णांक controller_id,
			अचिन्हित पूर्णांक panel_inst);

	अचिन्हित पूर्णांक (*get_current_backlight)(काष्ठा abm *abm);
	अचिन्हित पूर्णांक (*get_target_backlight)(काष्ठा abm *abm);
	bool (*init_abm_config)(काष्ठा abm *abm,
			स्थिर अक्षर *src,
			अचिन्हित पूर्णांक bytes);
पूर्ण;

#पूर्ण_अगर
