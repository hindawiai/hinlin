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
#समावेश "priv.h"
#समावेश "regsnv04.h"

अटल व्योम
nv40_समयr_init(काष्ठा nvkm_समयr *पंचांगr)
अणु
	काष्ठा nvkm_subdev *subdev = &पंचांगr->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 f = 0; /*XXX: figure this out */
	u32 n, d;

	/* aim क्रम 31.25MHz, which gives us nanosecond बारtamps */
	d = 1000000 / 32;
	n = f;

	अगर (!f) अणु
		n = nvkm_rd32(device, NV04_PTIMER_NUMERATOR);
		d = nvkm_rd32(device, NV04_PTIMER_DENOMINATOR);
		अगर (!n || !d) अणु
			n = 1;
			d = 1;
		पूर्ण
		nvkm_warn(subdev, "unknown input clock freq\n");
	पूर्ण

	/* reduce ratio to acceptable values */
	जबतक (((n % 5) == 0) && ((d % 5) == 0)) अणु
		n /= 5;
		d /= 5;
	पूर्ण

	जबतक (((n % 2) == 0) && ((d % 2) == 0)) अणु
		n /= 2;
		d /= 2;
	पूर्ण

	जबतक (n > 0xffff || d > 0xffff) अणु
		n >>= 1;
		d >>= 1;
	पूर्ण

	nvkm_debug(subdev, "input frequency : %dHz\n", f);
	nvkm_debug(subdev, "numerator       : %08x\n", n);
	nvkm_debug(subdev, "denominator     : %08x\n", d);
	nvkm_debug(subdev, "timer frequency : %dHz\n", f * d / n);

	nvkm_wr32(device, NV04_PTIMER_NUMERATOR, n);
	nvkm_wr32(device, NV04_PTIMER_DENOMINATOR, d);
पूर्ण

अटल स्थिर काष्ठा nvkm_समयr_func
nv40_समयr = अणु
	.init = nv40_समयr_init,
	.पूर्णांकr = nv04_समयr_पूर्णांकr,
	.पढ़ो = nv04_समयr_पढ़ो,
	.समय = nv04_समयr_समय,
	.alarm_init = nv04_समयr_alarm_init,
	.alarm_fini = nv04_समयr_alarm_fini,
पूर्ण;

पूर्णांक
nv40_समयr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_समयr **pपंचांगr)
अणु
	वापस nvkm_समयr_new_(&nv40_समयr, device, type, inst, pपंचांगr);
पूर्ण
