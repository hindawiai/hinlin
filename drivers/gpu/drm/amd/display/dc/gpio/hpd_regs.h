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

#अगर_अघोषित DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_HPD_REGS_H_
#घोषणा DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_HPD_REGS_H_

#समावेश "gpio_regs.h"

#घोषणा ONE_MORE_0 1
#घोषणा ONE_MORE_1 2
#घोषणा ONE_MORE_2 3
#घोषणा ONE_MORE_3 4
#घोषणा ONE_MORE_4 5
#घोषणा ONE_MORE_5 6


#घोषणा HPD_GPIO_REG_LIST_ENTRY(type,cd,id) \
	.type ## _reg =  REG(DC_GPIO_HPD_## type),\
	.type ## _mask =  DC_GPIO_HPD_ ## type ## __DC_GPIO_HPD ## id ## _ ## type ## _MASK,\
	.type ## _shअगरt = DC_GPIO_HPD_ ## type ## __DC_GPIO_HPD ## id ## _ ## type ## __SHIFT

#घोषणा HPD_GPIO_REG_LIST(id) \
	अणु\
	HPD_GPIO_REG_LIST_ENTRY(MASK,cd,id),\
	HPD_GPIO_REG_LIST_ENTRY(A,cd,id),\
	HPD_GPIO_REG_LIST_ENTRY(EN,cd,id),\
	HPD_GPIO_REG_LIST_ENTRY(Y,cd,id)\
	पूर्ण

#घोषणा HPD_REG_LIST(id) \
	HPD_GPIO_REG_LIST(ONE_MORE_ ## id), \
	.पूर्णांक_status = REGI(DC_HPD_INT_STATUS, HPD, id),\
	.toggle_filt_cntl = REGI(DC_HPD_TOGGLE_FILT_CNTL, HPD, id)

 #घोषणा HPD_MASK_SH_LIST(mask_sh) \
		SF_HPD(DC_HPD_INT_STATUS, DC_HPD_SENSE_DELAYED, mask_sh),\
		SF_HPD(DC_HPD_INT_STATUS, DC_HPD_SENSE, mask_sh),\
		SF_HPD(DC_HPD_TOGGLE_FILT_CNTL, DC_HPD_CONNECT_INT_DELAY, mask_sh),\
		SF_HPD(DC_HPD_TOGGLE_FILT_CNTL, DC_HPD_DISCONNECT_INT_DELAY, mask_sh)

काष्ठा hpd_रेजिस्टरs अणु
	काष्ठा gpio_रेजिस्टरs gpio;
	uपूर्णांक32_t पूर्णांक_status;
	uपूर्णांक32_t toggle_filt_cntl;
पूर्ण;

काष्ठा hpd_sh_mask अणु
	/* पूर्णांक_status */
	uपूर्णांक32_t DC_HPD_SENSE_DELAYED;
	uपूर्णांक32_t DC_HPD_SENSE;
	/* toggle_filt_cntl */
	uपूर्णांक32_t DC_HPD_CONNECT_INT_DELAY;
	uपूर्णांक32_t DC_HPD_DISCONNECT_INT_DELAY;
पूर्ण;


#पूर्ण_अगर /* DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_HPD_REGS_H_ */
