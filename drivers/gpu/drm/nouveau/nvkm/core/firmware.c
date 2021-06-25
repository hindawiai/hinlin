<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश <core/device.h>
#समावेश <core/firmware.h>

पूर्णांक
nvkm_firmware_load_name(स्थिर काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *base,
			स्थिर अक्षर *name, पूर्णांक ver, स्थिर काष्ठा firmware **pfw)
अणु
	अक्षर path[64];
	पूर्णांक ret;

	snम_लिखो(path, माप(path), "%s%s", base, name);
	ret = nvkm_firmware_get(subdev, path, ver, pfw);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक
nvkm_firmware_load_blob(स्थिर काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *base,
			स्थिर अक्षर *name, पूर्णांक ver, काष्ठा nvkm_blob *blob)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = nvkm_firmware_load_name(subdev, base, name, ver, &fw);
	अगर (ret == 0) अणु
		blob->data = kmemdup(fw->data, fw->size, GFP_KERNEL);
		blob->size = fw->size;
		nvkm_firmware_put(fw);
		अगर (!blob->data)
			वापस -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nvkm_firmware_get - load firmware from the official nvidia/chip/ directory
 * @subdev:	subdevice that will use that firmware
 * @fwname:	name of firmware file to load
 * @ver:	firmware version to load
 * @fw:		firmware काष्ठाure to load to
 *
 * Use this function to load firmware files in the क्रमm nvidia/chip/fwname.bin.
 * Firmware files released by NVIDIA will always follow this क्रमmat.
 */
पूर्णांक
nvkm_firmware_get(स्थिर काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *fwname, पूर्णांक ver,
		  स्थिर काष्ठा firmware **fw)
अणु
	काष्ठा nvkm_device *device = subdev->device;
	अक्षर f[64];
	अक्षर cname[16];
	पूर्णांक i;

	/* Convert device name to lowerहाल */
	म_नकलन(cname, device->chip->name, माप(cname));
	cname[माप(cname) - 1] = '\0';
	i = म_माप(cname);
	जबतक (i) अणु
		--i;
		cname[i] = छोटे(cname[i]);
	पूर्ण

	अगर (ver != 0)
		snम_लिखो(f, माप(f), "nvidia/%s/%s-%d.bin", cname, fwname, ver);
	अन्यथा
		snम_लिखो(f, माप(f), "nvidia/%s/%s.bin", cname, fwname);

	अगर (!firmware_request_nowarn(fw, f, device->dev)) अणु
		nvkm_debug(subdev, "firmware \"%s\" loaded - %zu byte(s)\n",
			   f, (*fw)->size);
		वापस 0;
	पूर्ण

	nvkm_debug(subdev, "firmware \"%s\" unavailable\n", f);
	वापस -ENOENT;
पूर्ण

/*
 * nvkm_firmware_put - release firmware loaded with nvkm_firmware_get
 */
व्योम
nvkm_firmware_put(स्थिर काष्ठा firmware *fw)
अणु
	release_firmware(fw);
पूर्ण
