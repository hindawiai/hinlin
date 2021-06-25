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
#समावेश "ram.h"

#समावेश <core/memory.h>
#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/M0203.h>
#समावेश <engine/gr.h>
#समावेश <engine/mpeg.h>

व्योम
nvkm_fb_tile_fini(काष्ठा nvkm_fb *fb, पूर्णांक region, काष्ठा nvkm_fb_tile *tile)
अणु
	fb->func->tile.fini(fb, region, tile);
पूर्ण

व्योम
nvkm_fb_tile_init(काष्ठा nvkm_fb *fb, पूर्णांक region, u32 addr, u32 size,
		  u32 pitch, u32 flags, काष्ठा nvkm_fb_tile *tile)
अणु
	fb->func->tile.init(fb, region, addr, size, pitch, flags, tile);
पूर्ण

व्योम
nvkm_fb_tile_prog(काष्ठा nvkm_fb *fb, पूर्णांक region, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	अगर (fb->func->tile.prog) अणु
		fb->func->tile.prog(fb, region, tile);
		अगर (device->gr)
			nvkm_engine_tile(&device->gr->engine, region);
		अगर (device->mpeg)
			nvkm_engine_tile(device->mpeg, region);
	पूर्ण
पूर्ण

पूर्णांक
nvkm_fb_bios_memtype(काष्ठा nvkm_bios *bios)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u8 ramcfg = (nvkm_rd32(device, 0x101000) & 0x0000003c) >> 2;
	काष्ठा nvbios_M0203E M0203E;
	u8 ver, hdr;

	अगर (nvbios_M0203Em(bios, ramcfg, &ver, &hdr, &M0203E)) अणु
		चयन (M0203E.type) अणु
		हाल M0203E_TYPE_DDR2  : वापस NVKM_RAM_TYPE_DDR2;
		हाल M0203E_TYPE_DDR3  : वापस NVKM_RAM_TYPE_DDR3;
		हाल M0203E_TYPE_GDDR3 : वापस NVKM_RAM_TYPE_GDDR3;
		हाल M0203E_TYPE_GDDR5 : वापस NVKM_RAM_TYPE_GDDR5;
		हाल M0203E_TYPE_GDDR5X: वापस NVKM_RAM_TYPE_GDDR5X;
		हाल M0203E_TYPE_GDDR6 : वापस NVKM_RAM_TYPE_GDDR6;
		हाल M0203E_TYPE_HBM2  : वापस NVKM_RAM_TYPE_HBM2;
		शेष:
			nvkm_warn(subdev, "M0203E type %02x\n", M0203E.type);
			वापस NVKM_RAM_TYPE_UNKNOWN;
		पूर्ण
	पूर्ण

	nvkm_warn(subdev, "M0203E not matched!\n");
	वापस NVKM_RAM_TYPE_UNKNOWN;
पूर्ण

अटल व्योम
nvkm_fb_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fb *fb = nvkm_fb(subdev);
	अगर (fb->func->पूर्णांकr)
		fb->func->पूर्णांकr(fb);
पूर्ण

अटल पूर्णांक
nvkm_fb_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fb *fb = nvkm_fb(subdev);
	u32 tags = 0;

	अगर (fb->func->ram_new) अणु
		पूर्णांक ret = fb->func->ram_new(fb, &fb->ram);
		अगर (ret) अणु
			nvkm_error(subdev, "vram setup failed, %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (fb->func->oneinit) अणु
		पूर्णांक ret = fb->func->oneinit(fb);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Initialise compression tag allocator.
	 *
	 * LTC oneinit() will override this on Fermi and newer.
	 */
	अगर (fb->func->tags) अणु
		tags = fb->func->tags(fb);
		nvkm_debug(subdev, "%d comptags\n", tags);
	पूर्ण

	वापस nvkm_mm_init(&fb->tags.mm, 0, 0, tags, 1);
पूर्ण

अटल पूर्णांक
nvkm_fb_init_scrub_vpr(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	पूर्णांक ret;

	nvkm_debug(subdev, "VPR locked, running scrubber binary\n");

	अगर (!fb->vpr_scrubber.size) अणु
		nvkm_warn(subdev, "VPR locked, but no scrubber binary!\n");
		वापस 0;
	पूर्ण

	ret = fb->func->vpr.scrub(fb);
	अगर (ret) अणु
		nvkm_error(subdev, "VPR scrubber binary failed\n");
		वापस ret;
	पूर्ण

	अगर (fb->func->vpr.scrub_required(fb)) अणु
		nvkm_error(subdev, "VPR still locked after scrub!\n");
		वापस -EIO;
	पूर्ण

	nvkm_debug(subdev, "VPR scrubber binary successful\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fb_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fb *fb = nvkm_fb(subdev);
	पूर्णांक ret, i;

	अगर (fb->ram) अणु
		ret = nvkm_ram_init(fb->ram);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < fb->tile.regions; i++)
		fb->func->tile.prog(fb, i, &fb->tile.region[i]);

	अगर (fb->func->init)
		fb->func->init(fb);

	अगर (fb->func->init_remapper)
		fb->func->init_remapper(fb);

	अगर (fb->func->init_page) अणु
		ret = fb->func->init_page(fb);
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण

	अगर (fb->func->init_unkn)
		fb->func->init_unkn(fb);

	अगर (fb->func->vpr.scrub_required &&
	    fb->func->vpr.scrub_required(fb)) अणु
		ret = nvkm_fb_init_scrub_vpr(fb);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_fb_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fb *fb = nvkm_fb(subdev);
	पूर्णांक i;

	nvkm_memory_unref(&fb->mmu_wr);
	nvkm_memory_unref(&fb->mmu_rd);

	क्रम (i = 0; i < fb->tile.regions; i++)
		fb->func->tile.fini(fb, i, &fb->tile.region[i]);

	nvkm_mm_fini(&fb->tags.mm);
	mutex_destroy(&fb->tags.mutex);

	nvkm_ram_del(&fb->ram);

	nvkm_blob_dtor(&fb->vpr_scrubber);

	अगर (fb->func->dtor)
		वापस fb->func->dtor(fb);
	वापस fb;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_fb = अणु
	.dtor = nvkm_fb_dtor,
	.oneinit = nvkm_fb_oneinit,
	.init = nvkm_fb_init,
	.पूर्णांकr = nvkm_fb_पूर्णांकr,
पूर्ण;

व्योम
nvkm_fb_ctor(स्थिर काष्ठा nvkm_fb_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb *fb)
अणु
	nvkm_subdev_ctor(&nvkm_fb, device, type, inst, &fb->subdev);
	fb->func = func;
	fb->tile.regions = fb->func->tile.regions;
	fb->page = nvkm_दीर्घopt(device->cfgopt, "NvFbBigPage", fb->func->शेष_bigpage);
	mutex_init(&fb->tags.mutex);
पूर्ण

पूर्णांक
nvkm_fb_new_(स्थिर काष्ठा nvkm_fb_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	अगर (!(*pfb = kzalloc(माप(**pfb), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_fb_ctor(func, device, type, inst, *pfb);
	वापस 0;
पूर्ण
