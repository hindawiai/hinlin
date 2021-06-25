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
 *
 * Authors: Lyude Paul
 */
#समावेश <core/device.h>

#समावेश "priv.h"

#घोषणा pack_क्रम_each_init(init, pack, head)                          \
	क्रम (pack = head; pack && pack->init; pack++)                 \
		  क्रम (init = pack->init; init && init->count; init++)
व्योम
gf100_clkgate_init(काष्ठा nvkm_therm *therm,
		   स्थिर काष्ठा nvkm_therm_clkgate_pack *p)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	स्थिर काष्ठा nvkm_therm_clkgate_pack *pack;
	स्थिर काष्ठा nvkm_therm_clkgate_init *init;
	u32 next, addr;

	pack_क्रम_each_init(init, pack, p) अणु
		next = init->addr + init->count * 8;
		addr = init->addr;

		nvkm_trace(&therm->subdev, "{ 0x%06x, %d, 0x%08x }\n",
			   init->addr, init->count, init->data);
		जबतक (addr < next) अणु
			nvkm_trace(&therm->subdev, "\t0x%06x = 0x%08x\n",
				   addr, init->data);
			nvkm_wr32(device, addr, init->data);
			addr += 8;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * TODO: Fermi घड़ीgating isn't understood fully yet, so we don't specअगरy any
 * घड़ीgate functions to use
 */
