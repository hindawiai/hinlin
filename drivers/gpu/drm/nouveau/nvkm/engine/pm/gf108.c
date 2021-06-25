<शैली गुरु>
/*
 * Copyright 2015 Samuel Pitoiset
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
 * Authors: Samuel Pitoiset
 */
#समावेश "gf100.h"

अटल स्थिर काष्ठा nvkm_specकरोm
gf108_pm_hub[] = अणु
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gf108_pm_part[] = अणु
	अणु 0xe0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x14, "part00_pbfb_00", gf100_pbfb_sources पूर्ण,
			अणु 0x15, "part00_pbfb_01", gf100_pbfb_sources पूर्ण,
			अणु 0x20, "part00_pbfb_02", gf100_pbfb_sources पूर्ण,
			अणु 0x21, "part00_pbfb_03", gf100_pbfb_sources पूर्ण,
			अणु 0x01, "part00_pmfb_00", gf100_pmfb_sources पूर्ण,
			अणु 0x04, "part00_pmfb_01", gf100_pmfb_sources पूर्ण,
			अणु 0x05, "part00_pmfb_02", gf100_pmfb_sourcesपूर्ण,
			अणु 0x07, "part00_pmfb_03", gf100_pmfb_sources पूर्ण,
			अणु 0x0d, "part00_pmfb_04", gf100_pmfb_sources पूर्ण,
			अणु 0x12, "part00_pmfb_05", gf100_pmfb_sources पूर्ण,
			अणु 0x13, "part00_pmfb_06", gf100_pmfb_sources पूर्ण,
			अणु 0x2c, "part00_pmfb_07", gf100_pmfb_sources पूर्ण,
			अणु 0x2d, "part00_pmfb_08", gf100_pmfb_sources पूर्ण,
			अणु 0x2e, "part00_pmfb_09", gf100_pmfb_sources पूर्ण,
			अणु 0x2f, "part00_pmfb_0a", gf100_pmfb_sources पूर्ण,
			अणु 0x30, "part00_pmfb_0b", gf100_pmfb_sources पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_pm_func
gf108_pm = अणु
	.करोms_gpc = gf100_pm_gpc,
	.करोms_hub = gf108_pm_hub,
	.करोms_part = gf108_pm_part,
पूर्ण;

पूर्णांक
gf108_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस gf100_pm_new_(&gf108_pm, device, type, inst, ppm);
पूर्ण
