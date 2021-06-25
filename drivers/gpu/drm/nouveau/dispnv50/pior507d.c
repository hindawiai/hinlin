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

#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl507d.h>
#समावेश <nvhw/class/cl837d.h>

अटल पूर्णांक
pior507d_ctrl(काष्ठा nv50_core *core, पूर्णांक or, u32 ctrl,
	      काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर (asyh) अणु
		ctrl |= NVVAL(NV507D, PIOR_SET_CONTROL, HSYNC_POLARITY, asyh->or.nhsync);
		ctrl |= NVVAL(NV507D, PIOR_SET_CONTROL, VSYNC_POLARITY, asyh->or.nvsync);
		ctrl |= NVVAL(NV837D, PIOR_SET_CONTROL, PIXEL_DEPTH, asyh->or.depth);
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507D, PIOR_SET_CONTROL(or), ctrl);
	वापस 0;
पूर्ण

अटल व्योम
pior507d_get_caps(काष्ठा nv50_disp *disp, काष्ठा nouveau_encoder *outp,
		  पूर्णांक or)
अणु
	outp->caps.dp_पूर्णांकerlace = true;
पूर्ण

स्थिर काष्ठा nv50_outp_func
pior507d = अणु
	.ctrl = pior507d_ctrl,
	.get_caps = pior507d_get_caps,
पूर्ण;
