<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _PP_OVERDRIVER_H_
#घोषणा _PP_OVERDRIVER_H_

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

काष्ठा phm_fuses_शेष अणु
	uपूर्णांक64_t key;
	uपूर्णांक32_t VFT2_m1;
	uपूर्णांक32_t VFT2_m2;
	uपूर्णांक32_t VFT2_b;
	uपूर्णांक32_t VFT1_m1;
	uपूर्णांक32_t VFT1_m2;
	uपूर्णांक32_t VFT1_b;
	uपूर्णांक32_t VFT0_m1;
	uपूर्णांक32_t VFT0_m2;
	uपूर्णांक32_t VFT0_b;
पूर्ण;

बाह्य पूर्णांक pp_override_get_शेष_fuse_value(uपूर्णांक64_t key,
			काष्ठा phm_fuses_शेष *result);

#पूर्ण_अगर
