<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#समावेश "core.h"

#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc37d.h>

अटल पूर्णांक
sorc37d_ctrl(काष्ठा nv50_core *core, पूर्णांक or, u32 ctrl,
	     काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, SOR_SET_CONTROL(or), ctrl);
	वापस 0;
पूर्ण

अटल व्योम
sorc37d_get_caps(काष्ठा nv50_disp *disp, काष्ठा nouveau_encoder *outp, पूर्णांक or)
अणु
	u32 पंचांगp = nvअगर_rd32(&disp->caps, 0x000144 + (or * 8));

	outp->caps.dp_पूर्णांकerlace = !!(पंचांगp & 0x04000000);
पूर्ण

स्थिर काष्ठा nv50_outp_func
sorc37d = अणु
	.ctrl = sorc37d_ctrl,
	.get_caps = sorc37d_get_caps,
पूर्ण;
