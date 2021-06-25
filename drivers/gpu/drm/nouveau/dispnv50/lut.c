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
#समावेश "lut.h"
#समावेश "disp.h"

#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_property.h>

#समावेश <nvअगर/class.h>

u32
nv50_lut_load(काष्ठा nv50_lut *lut, पूर्णांक buffer, काष्ठा drm_property_blob *blob,
	      व्योम (*load)(काष्ठा drm_color_lut *, पूर्णांक, व्योम __iomem *))
अणु
	काष्ठा drm_color_lut *in = blob ? blob->data : शून्य;
	व्योम __iomem *mem = lut->mem[buffer].object.map.ptr;
	स्थिर u32 addr = lut->mem[buffer].addr;
	पूर्णांक i;

	अगर (!in) अणु
		in = kvदो_स्मृति_array(1024, माप(*in), GFP_KERNEL);
		अगर (!WARN_ON(!in)) अणु
			क्रम (i = 0; i < 1024; i++) अणु
				in[i].red   =
				in[i].green =
				in[i].blue  = (i << 16) >> 10;
			पूर्ण
			load(in, 1024, mem);
			kvमुक्त(in);
		पूर्ण
	पूर्ण अन्यथा अणु
		load(in, drm_color_lut_size(blob), mem);
	पूर्ण

	वापस addr;
पूर्ण

व्योम
nv50_lut_fini(काष्ठा nv50_lut *lut)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(lut->mem); i++)
		nvअगर_mem_dtor(&lut->mem[i]);
पूर्ण

पूर्णांक
nv50_lut_init(काष्ठा nv50_disp *disp, काष्ठा nvअगर_mmu *mmu,
	      काष्ठा nv50_lut *lut)
अणु
	स्थिर u32 size = disp->disp->object.oclass < GF110_DISP ? 257 : 1025;
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(lut->mem); i++) अणु
		पूर्णांक ret = nvअगर_mem_ctor_map(mmu, "kmsLut", NVIF_MEM_VRAM,
					    size * 8, &lut->mem[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
