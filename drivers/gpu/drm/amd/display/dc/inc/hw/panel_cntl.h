<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 */
/*
 * panel_cntl.h
 *
 *  Created on: Oct 6, 2015
 *      Author: yonsun
 */

#अगर_अघोषित DC_PANEL_CNTL_H_
#घोषणा DC_PANEL_CNTL_H_

#समावेश "dc_types.h"

#घोषणा MAX_BACKLIGHT_LEVEL 0xFFFF

काष्ठा panel_cntl_backlight_रेजिस्टरs अणु
	अचिन्हित पूर्णांक BL_PWM_CNTL;
	अचिन्हित पूर्णांक BL_PWM_CNTL2;
	अचिन्हित पूर्णांक BL_PWM_PERIOD_CNTL;
	अचिन्हित पूर्णांक LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV;
पूर्ण;

काष्ठा panel_cntl_funcs अणु
	व्योम (*destroy)(काष्ठा panel_cntl **panel_cntl);
	uपूर्णांक32_t (*hw_init)(काष्ठा panel_cntl *panel_cntl);
	bool (*is_panel_backlight_on)(काष्ठा panel_cntl *panel_cntl);
	bool (*is_panel_घातered_on)(काष्ठा panel_cntl *panel_cntl);
	व्योम (*store_backlight_level)(काष्ठा panel_cntl *panel_cntl);
	व्योम (*driver_set_backlight)(काष्ठा panel_cntl *panel_cntl,
			uपूर्णांक32_t backlight_pwm_u16_16);
	uपूर्णांक32_t (*get_current_backlight)(काष्ठा panel_cntl *panel_cntl);
पूर्ण;

काष्ठा panel_cntl_init_data अणु
	काष्ठा dc_context *ctx;
	uपूर्णांक32_t inst;
पूर्ण;

काष्ठा panel_cntl अणु
	स्थिर काष्ठा panel_cntl_funcs *funcs;
	काष्ठा dc_context *ctx;
	uपूर्णांक32_t inst;
	/* रेजिस्टरs setting needs to be saved and restored at InitBacklight */
	काष्ठा panel_cntl_backlight_रेजिस्टरs stored_backlight_रेजिस्टरs;
पूर्ण;

#पूर्ण_अगर /* DC_PANEL_CNTL_H_ */
