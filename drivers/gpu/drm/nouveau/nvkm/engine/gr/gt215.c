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
#समावेश "nv50.h"

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_gr_func
gt215_gr = अणु
	.init = nv50_gr_init,
	.पूर्णांकr = nv50_gr_पूर्णांकr,
	.chan_new = nv50_gr_chan_new,
	.tlb_flush = g84_gr_tlb_flush,
	.units = nv50_gr_units,
	.sclass = अणु
		अणु -1, -1, NV_शून्य_CLASS, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_TWOD, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_MEMORY_TO_MEMORY_FORMAT, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_COMPUTE, &nv50_gr_object पूर्ण,
		अणु -1, -1, GT214_TESLA, &nv50_gr_object पूर्ण,
		अणु -1, -1, GT214_COMPUTE, &nv50_gr_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gt215_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv50_gr_new_(&gt215_gr, device, type, inst, pgr);
पूर्ण
