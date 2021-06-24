<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_GENERIC_REGS_H_
#घोषणा DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_GENERIC_REGS_H_

#समावेश "gpio_regs.h"

#घोषणा GENERIC_GPIO_REG_LIST_ENTRY(type, cd, id) \
	.type ## _reg =  REG(DC_GPIO_GENERIC_## type),\
	.type ## _mask =  DC_GPIO_GENERIC_ ## type ## __DC_GPIO_GENERIC ## id ## _ ## type ## _MASK,\
	.type ## _shअगरt = DC_GPIO_GENERIC_ ## type ## __DC_GPIO_GENERIC ## id ## _ ## type ## __SHIFT

#घोषणा GENERIC_GPIO_REG_LIST(id) \
	अणु\
	GENERIC_GPIO_REG_LIST_ENTRY(MASK, cd, id),\
	GENERIC_GPIO_REG_LIST_ENTRY(A, cd, id),\
	GENERIC_GPIO_REG_LIST_ENTRY(EN, cd, id),\
	GENERIC_GPIO_REG_LIST_ENTRY(Y, cd, id)\
	पूर्ण

#घोषणा GENERIC_REG_LIST(id) \
	GENERIC_GPIO_REG_LIST(id), \
	.mux = REG(DC_GENERIC ## id),\

#घोषणा GENERIC_MASK_SH_LIST(mask_sh, cd) \
	अणु(DC_GENERIC ## cd ##__GENERIC ## cd ##_EN## mask_sh),\
	(DC_GENERIC ## cd ##__GENERIC ## cd ##_SEL## mask_sh)पूर्ण

काष्ठा generic_रेजिस्टरs अणु
	काष्ठा gpio_रेजिस्टरs gpio;
	uपूर्णांक32_t mux;
पूर्ण;

काष्ठा generic_sh_mask अणु
	/* enable */
	uपूर्णांक32_t GENERIC_EN;
	/* select */
	uपूर्णांक32_t GENERIC_SEL;

पूर्ण;


#पूर्ण_अगर /* DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_GENERIC_REGS_H_ */
