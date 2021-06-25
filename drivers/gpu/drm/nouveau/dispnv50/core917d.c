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
#समावेश "head.h"

अटल स्थिर काष्ठा nv50_core_func
core917d = अणु
	.init = core507d_init,
	.ntfy_init = core507d_ntfy_init,
	.caps_init = core907d_caps_init,
	.ntfy_रुको_करोne = core507d_ntfy_रुको_करोne,
	.update = core507d_update,
	.head = &head917d,
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	.crc = &crc907d,
#पूर्ण_अगर
	.dac = &dac907d,
	.sor = &sor907d,
पूर्ण;

पूर्णांक
core917d_new(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_core **pcore)
अणु
	वापस core507d_new_(&core917d, drm, oclass, pcore);
पूर्ण
