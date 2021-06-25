<शैली गुरु>
/* Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित MODULES_POWER_POWER_HELPERS_H_
#घोषणा MODULES_POWER_POWER_HELPERS_H_

#समावेश "dc/inc/hw/dmcu.h"
#समावेश "dc/inc/hw/abm.h"

काष्ठा resource_pool;


क्रमागत abm_defines अणु
	abm_defines_max_level = 4,
	abm_defines_max_config = 4,
पूर्ण;

काष्ठा dmcu_iram_parameters अणु
	अचिन्हित पूर्णांक *backlight_lut_array;
	अचिन्हित पूर्णांक backlight_lut_array_size;
	bool backlight_ramping_override;
	अचिन्हित पूर्णांक backlight_ramping_reduction;
	अचिन्हित पूर्णांक backlight_ramping_start;
	अचिन्हित पूर्णांक min_abm_backlight;
	अचिन्हित पूर्णांक set;
पूर्ण;

bool dmcu_load_iram(काष्ठा dmcu *dmcu,
		काष्ठा dmcu_iram_parameters params);
bool dmub_init_abm_config(काष्ठा resource_pool *res_pool,
		काष्ठा dmcu_iram_parameters params);

#पूर्ण_अगर /* MODULES_POWER_POWER_HELPERS_H_ */
