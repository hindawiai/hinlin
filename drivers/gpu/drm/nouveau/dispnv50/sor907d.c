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

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl907d.h>

#समावेश <nouveau_bo.h>

अटल पूर्णांक
sor907d_ctrl(काष्ठा nv50_core *core, पूर्णांक or, u32 ctrl,
	     काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, SOR_SET_CONTROL(or), ctrl);
	वापस 0;
पूर्ण

अटल व्योम
sor907d_get_caps(काष्ठा nv50_disp *disp, काष्ठा nouveau_encoder *outp, पूर्णांक or)
अणु
	काष्ठा nouveau_bo *bo = disp->sync;
	स्थिर पूर्णांक off = or * 2;
	outp->caps.dp_पूर्णांकerlace =
		NVBO_RV32(bo, off, NV907D_CORE_NOTIFIER_3, CAPABILITIES_CAP_SOR0_20, DP_INTERLACE);
पूर्ण

स्थिर काष्ठा nv50_outp_func
sor907d = अणु
	.ctrl = sor907d_ctrl,
	.get_caps = sor907d_get_caps,
पूर्ण;
