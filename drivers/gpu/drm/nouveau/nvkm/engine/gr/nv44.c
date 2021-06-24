<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "nv40.h"
#समावेश "regs.h"

#समावेश <subdev/fb.h>
#समावेश <engine/fअगरo.h>

अटल व्योम
nv44_gr_tile(काष्ठा nvkm_gr *base, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nv40_gr *gr = nv40_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;
	अचिन्हित दीर्घ flags;

	nvkm_fअगरo_छोड़ो(fअगरo, &flags);
	nv04_gr_idle(&gr->base);

	चयन (device->chipset) अणु
	हाल 0x44:
	हाल 0x4a:
		nvkm_wr32(device, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV20_PGRAPH_TILE(i), tile->addr);
		अवरोध;
	हाल 0x46:
	हाल 0x4c:
	हाल 0x63:
	हाल 0x67:
	हाल 0x68:
		nvkm_wr32(device, NV47_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV47_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV47_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		अवरोध;
	हाल 0x4e:
		nvkm_wr32(device, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV20_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	nvkm_fअगरo_start(fअगरo, &flags);
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv44_gr = अणु
	.init = nv40_gr_init,
	.पूर्णांकr = nv40_gr_पूर्णांकr,
	.tile = nv44_gr_tile,
	.units = nv40_gr_units,
	.chan_new = nv40_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv40_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0019, &nv40_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x0030, &nv40_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0039, &nv40_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0043, &nv40_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv40_gr_object पूर्ण, /* patt */
		अणु -1, -1, 0x004a, &nv40_gr_object पूर्ण, /* gdi */
		अणु -1, -1, 0x0062, &nv40_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0072, &nv40_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0089, &nv40_gr_object पूर्ण, /* sअगरm */
		अणु -1, -1, 0x008a, &nv40_gr_object पूर्ण, /* अगरc */
		अणु -1, -1, 0x009f, &nv40_gr_object पूर्ण, /* imageblit */
		अणु -1, -1, 0x3062, &nv40_gr_object पूर्ण, /* surf2d (nv40) */
		अणु -1, -1, 0x3089, &nv40_gr_object पूर्ण, /* sअगरm (nv40) */
		अणु -1, -1, 0x309e, &nv40_gr_object पूर्ण, /* swzsurf (nv40) */
		अणु -1, -1, 0x4497, &nv40_gr_object पूर्ण, /* curie */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv44_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv40_gr_new_(&nv44_gr, device, type, inst, pgr);
पूर्ण
