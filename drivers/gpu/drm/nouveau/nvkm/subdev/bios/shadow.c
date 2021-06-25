<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/image.h>

काष्ठा shaकरोw अणु
	u32 skip;
	स्थिर काष्ठा nvbios_source *func;
	व्योम *data;
	u32 size;
	पूर्णांक score;
पूर्ण;

अटल bool
shaकरोw_fetch(काष्ठा nvkm_bios *bios, काष्ठा shaकरोw *mthd, u32 upto)
अणु
	स्थिर u32 limit = (upto + 3) & ~3;
	स्थिर u32 start = bios->size;
	व्योम *data = mthd->data;
	अगर (nvbios_extend(bios, limit) > 0) अणु
		u32 पढ़ो = mthd->func->पढ़ो(data, start, limit - start, bios);
		bios->size = start + पढ़ो;
	पूर्ण
	वापस bios->size >= upto;
पूर्ण

अटल पूर्णांक
shaकरोw_image(काष्ठा nvkm_bios *bios, पूर्णांक idx, u32 offset, काष्ठा shaकरोw *mthd)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvbios_image image;
	पूर्णांक score = 1;

	अगर (mthd->func->no_pcir) अणु
		image.base = 0;
		image.type = 0;
		image.size = mthd->func->size(mthd->data);
		image.last = 1;
	पूर्ण अन्यथा अणु
		अगर (!shaकरोw_fetch(bios, mthd, offset + 0x1000)) अणु
			nvkm_debug(subdev, "%08x: header fetch failed\n",
				   offset);
			वापस 0;
		पूर्ण

		अगर (!nvbios_image(bios, idx, &image)) अणु
			nvkm_debug(subdev, "image %d invalid\n", idx);
			वापस 0;
		पूर्ण
	पूर्ण
	nvkm_debug(subdev, "%08x: type %02x, %d bytes\n",
		   image.base, image.type, image.size);

	अगर (!shaकरोw_fetch(bios, mthd, image.base + image.size)) अणु
		nvkm_debug(subdev, "%08x: fetch failed\n", image.base);
		वापस 0;
	पूर्ण

	चयन (image.type) अणु
	हाल 0x00:
		अगर (!mthd->func->ignore_checksum &&
		    nvbios_checksum(&bios->data[image.base], image.size)) अणु
			nvkm_debug(subdev, "%08x: checksum failed\n",
				   image.base);
			अगर (!mthd->func->require_checksum) अणु
				अगर (mthd->func->rw)
					score += 1;
				score += 1;
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण अन्यथा अणु
			score += 3;
		पूर्ण
		अवरोध;
	शेष:
		score += 3;
		अवरोध;
	पूर्ण

	अगर (!image.last)
		score += shaकरोw_image(bios, idx + 1, offset + image.size, mthd);
	वापस score;
पूर्ण

अटल पूर्णांक
shaकरोw_method(काष्ठा nvkm_bios *bios, काष्ठा shaकरोw *mthd, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा nvbios_source *func = mthd->func;
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	अगर (func->name) अणु
		nvkm_debug(subdev, "trying %s...\n", name ? name : func->name);
		अगर (func->init) अणु
			mthd->data = func->init(bios, name);
			अगर (IS_ERR(mthd->data)) अणु
				mthd->data = शून्य;
				वापस 0;
			पूर्ण
		पूर्ण
		mthd->score = shaकरोw_image(bios, 0, 0, mthd);
		अगर (func->fini)
			func->fini(mthd->data);
		nvkm_debug(subdev, "scored %d\n", mthd->score);
		mthd->data = bios->data;
		mthd->size = bios->size;
		bios->data  = शून्य;
		bios->size  = 0;
	पूर्ण
	वापस mthd->score;
पूर्ण

अटल u32
shaकरोw_fw_पढ़ो(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	स्थिर काष्ठा firmware *fw = data;
	अगर (offset + length <= fw->size) अणु
		स_नकल(bios->data + offset, fw->data + offset, length);
		वापस length;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *
shaकरोw_fw_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
	काष्ठा device *dev = bios->subdev.device->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = request_firmware(&fw, name, dev);
	अगर (ret)
		वापस ERR_PTR(-ENOENT);
	वापस (व्योम *)fw;
पूर्ण

अटल स्थिर काष्ठा nvbios_source
shaकरोw_fw = अणु
	.name = "firmware",
	.init = shaकरोw_fw_init,
	.fini = (व्योम(*)(व्योम *))release_firmware,
	.पढ़ो = shaकरोw_fw_पढ़ो,
	.rw = false,
पूर्ण;

पूर्णांक
nvbios_shaकरोw(काष्ठा nvkm_bios *bios)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा shaकरोw mthds[] = अणु
		अणु 0, &nvbios_of पूर्ण,
		अणु 0, &nvbios_ramin पूर्ण,
		अणु 0, &nvbios_rom पूर्ण,
		अणु 0, &nvbios_acpi_fast पूर्ण,
		अणु 4, &nvbios_acpi_slow पूर्ण,
		अणु 1, &nvbios_pcirom पूर्ण,
		अणु 1, &nvbios_platक्रमm पूर्ण,
		अणुपूर्ण
	पूर्ण, *mthd, *best = शून्य;
	स्थिर अक्षर *optarg;
	अक्षर *source;
	पूर्णांक optlen;

	/* handle user-specअगरied bios source */
	optarg = nvkm_stropt(device->cfgopt, "NvBios", &optlen);
	source = optarg ? kstrndup(optarg, optlen, GFP_KERNEL) : शून्य;
	अगर (source) अणु
		/* try to match one of the built-in methods */
		क्रम (mthd = mthds; mthd->func; mthd++) अणु
			अगर (mthd->func->name &&
			    !strहालcmp(source, mthd->func->name)) अणु
				best = mthd;
				अगर (shaकरोw_method(bios, mthd, शून्य))
					अवरोध;
			पूर्ण
		पूर्ण

		/* otherwise, attempt to load as firmware */
		अगर (!best && (best = mthd)) अणु
			mthd->func = &shaकरोw_fw;
			shaकरोw_method(bios, mthd, source);
			mthd->func = शून्य;
		पूर्ण

		अगर (!best->score) अणु
			nvkm_error(subdev, "%s invalid\n", source);
			kमुक्त(source);
			source = शून्य;
		पूर्ण
	पूर्ण

	/* scan all potential bios sources, looking क्रम best image */
	अगर (!best || !best->score) अणु
		क्रम (mthd = mthds, best = mthd; mthd->func; mthd++) अणु
			अगर (!mthd->skip || best->score < mthd->skip) अणु
				अगर (shaकरोw_method(bios, mthd, शून्य)) अणु
					अगर (mthd->score > best->score)
						best = mthd;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* cleanup the ones we didn't use */
	क्रम (mthd = mthds; mthd->func; mthd++) अणु
		अगर (mthd != best)
			kमुक्त(mthd->data);
	पूर्ण

	अगर (!best->score) अणु
		nvkm_error(subdev, "unable to locate usable image\n");
		वापस -EINVAL;
	पूर्ण

	nvkm_debug(subdev, "using image from %s\n", best->func ?
		   best->func->name : source);
	bios->data = best->data;
	bios->size = best->size;
	kमुक्त(source);
	वापस 0;
पूर्ण
