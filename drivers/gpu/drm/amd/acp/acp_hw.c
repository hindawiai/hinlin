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

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "acp_gfx_if.h"

#घोषणा ACP_MODE_I2S	0
#घोषणा ACP_MODE_AZ	1

#घोषणा mmACP_AZALIA_I2S_SELECT 0x51d4

पूर्णांक amd_acp_hw_init(काष्ठा cgs_device *cgs_device,
		    अचिन्हित acp_version_major, अचिन्हित acp_version_minor)
अणु
	अचिन्हित पूर्णांक acp_mode = ACP_MODE_I2S;

	अगर ((acp_version_major == 2) && (acp_version_minor == 2))
		acp_mode = cgs_पढ़ो_रेजिस्टर(cgs_device,
					mmACP_AZALIA_I2S_SELECT);

	अगर (acp_mode != ACP_MODE_I2S)
		वापस -ENODEV;

	वापस 0;
पूर्ण
