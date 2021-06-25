<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "head.h"

अटल व्योम
nv50_head_vblank_put(काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_mask(device, 0x61002c, (4 << head->id), 0);
पूर्ण

अटल व्योम
nv50_head_vblank_get(काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_mask(device, 0x61002c, (4 << head->id), (4 << head->id));
पूर्ण

अटल व्योम
nv50_head_rgclk(काष्ठा nvkm_head *head, पूर्णांक भाग)
अणु
	काष्ठा nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_mask(device, 0x614200 + (head->id * 0x800), 0x0000000f, भाग);
पूर्ण

व्योम
nv50_head_rgpos(काष्ठा nvkm_head *head, u16 *hline, u16 *vline)
अणु
	काष्ठा nvkm_device *device = head->disp->engine.subdev.device;
	स्थिर u32 hoff = head->id * 0x800;
	/* vline पढ़ो locks hline. */
	*vline = nvkm_rd32(device, 0x616340 + hoff) & 0x0000ffff;
	*hline = nvkm_rd32(device, 0x616344 + hoff) & 0x0000ffff;
पूर्ण

अटल व्योम
nv50_head_state(काष्ठा nvkm_head *head, काष्ठा nvkm_head_state *state)
अणु
	काष्ठा nvkm_device *device = head->disp->engine.subdev.device;
	स्थिर u32 hoff = head->id * 0x540 + (state == &head->arm) * 4;
	u32 data;

	data = nvkm_rd32(device, 0x610ae8 + hoff);
	state->vblanke = (data & 0xffff0000) >> 16;
	state->hblanke = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610af0 + hoff);
	state->vblanks = (data & 0xffff0000) >> 16;
	state->hblanks = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610af8 + hoff);
	state->vtotal = (data & 0xffff0000) >> 16;
	state->htotal = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610b00 + hoff);
	state->vsynce = (data & 0xffff0000) >> 16;
	state->hsynce = (data & 0x0000ffff);
	state->hz = (nvkm_rd32(device, 0x610ad0 + hoff) & 0x003fffff) * 1000;
पूर्ण

अटल स्थिर काष्ठा nvkm_head_func
nv50_head = अणु
	.state = nv50_head_state,
	.rgpos = nv50_head_rgpos,
	.rgclk = nv50_head_rgclk,
	.vblank_get = nv50_head_vblank_get,
	.vblank_put = nv50_head_vblank_put,
पूर्ण;

पूर्णांक
nv50_head_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_head_new_(&nv50_head, disp, id);
पूर्ण

पूर्णांक
nv50_head_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	*pmask = 3;
	वापस 2;
पूर्ण
