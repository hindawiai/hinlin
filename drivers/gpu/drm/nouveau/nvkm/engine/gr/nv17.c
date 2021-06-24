<शैली गुरु>
/*
 * Copyright 2007 Matthieu CASTET <castet.matthieu@मुक्त.fr>
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragr) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "nv10.h"

अटल स्थिर काष्ठा nvkm_gr_func
nv17_gr = अणु
	.init = nv10_gr_init,
	.पूर्णांकr = nv10_gr_पूर्णांकr,
	.tile = nv10_gr_tile,
	.chan_new = nv10_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv04_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0019, &nv04_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x0030, &nv04_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0039, &nv04_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0043, &nv04_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv04_gr_object पूर्ण, /* pattern */
		अणु -1, -1, 0x004a, &nv04_gr_object पूर्ण, /* gdi */
		अणु -1, -1, 0x0052, &nv04_gr_object पूर्ण, /* swzsurf */
		अणु -1, -1, 0x005f, &nv04_gr_object पूर्ण, /* blit */
		अणु -1, -1, 0x0062, &nv04_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0072, &nv04_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0089, &nv04_gr_object पूर्ण, /* sअगरm */
		अणु -1, -1, 0x008a, &nv04_gr_object पूर्ण, /* अगरc */
		अणु -1, -1, 0x009f, &nv04_gr_object पूर्ण, /* blit */
		अणु -1, -1, 0x0093, &nv04_gr_object पूर्ण, /* surf3d */
		अणु -1, -1, 0x0094, &nv04_gr_object पूर्ण, /* ttri */
		अणु -1, -1, 0x0095, &nv04_gr_object पूर्ण, /* mtri */
		अणु -1, -1, 0x0099, &nv04_gr_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv17_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv10_gr_new_(&nv17_gr, device, type, inst, pgr);
पूर्ण
