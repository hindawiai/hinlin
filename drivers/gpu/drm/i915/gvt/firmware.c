<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 * Contributors:
 *    Changbin Du <changbin.du@पूर्णांकel.com>
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/crc32.h>

#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"

#घोषणा FIRMWARE_VERSION (0x0)

काष्ठा gvt_firmware_header अणु
	u64 magic;
	u32 crc32;		/* protect the data after this field */
	u32 version;
	u64 cfg_space_size;
	u64 cfg_space_offset;	/* offset in the file */
	u64 mmio_size;
	u64 mmio_offset;	/* offset in the file */
	अचिन्हित अक्षर data[1];
पूर्ण;

#घोषणा dev_to_drm_minor(d) dev_get_drvdata((d))

अटल sमाप_प्रकार
gvt_firmware_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *attr, अक्षर *buf,
	     loff_t offset, माप_प्रकार count)
अणु
	स_नकल(buf, attr->निजी + offset, count);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute firmware_attr = अणु
	.attr = अणु.name = "gvt_firmware", .mode = (S_IRUSR)पूर्ण,
	.पढ़ो = gvt_firmware_पढ़ो,
	.ग_लिखो = शून्य,
	.mmap = शून्य,
पूर्ण;

अटल पूर्णांक mmio_snapshot_handler(काष्ठा पूर्णांकel_gvt *gvt, u32 offset, व्योम *data)
अणु
	*(u32 *)(data + offset) = पूर्णांकel_uncore_पढ़ो_notrace(gvt->gt->uncore,
							    _MMIO(offset));
	वापस 0;
पूर्ण

अटल पूर्णांक expose_firmware_sysfs(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);
	काष्ठा gvt_firmware_header *h;
	व्योम *firmware;
	व्योम *p;
	अचिन्हित दीर्घ size, crc32_start;
	पूर्णांक i, ret;

	size = माप(*h) + info->mmio_size + info->cfg_space_size;
	firmware = vzalloc(size);
	अगर (!firmware)
		वापस -ENOMEM;

	h = firmware;

	h->magic = VGT_MAGIC;
	h->version = FIRMWARE_VERSION;
	h->cfg_space_size = info->cfg_space_size;
	h->cfg_space_offset = दुरत्व(काष्ठा gvt_firmware_header, data);
	h->mmio_size = info->mmio_size;
	h->mmio_offset = h->cfg_space_offset + h->cfg_space_size;

	p = firmware + h->cfg_space_offset;

	क्रम (i = 0; i < h->cfg_space_size; i += 4)
		pci_पढ़ो_config_dword(pdev, i, p + i);

	स_नकल(gvt->firmware.cfg_space, p, info->cfg_space_size);

	p = firmware + h->mmio_offset;

	/* Take a snapshot of hw mmio रेजिस्टरs. */
	पूर्णांकel_gvt_क्रम_each_tracked_mmio(gvt, mmio_snapshot_handler, p);

	स_नकल(gvt->firmware.mmio, p, info->mmio_size);

	crc32_start = दुरत्व(काष्ठा gvt_firmware_header, crc32) + 4;
	h->crc32 = crc32_le(0, firmware + crc32_start, size - crc32_start);

	firmware_attr.size = size;
	firmware_attr.निजी = firmware;

	ret = device_create_bin_file(&pdev->dev, &firmware_attr);
	अगर (ret) अणु
		vमुक्त(firmware);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम clean_firmware_sysfs(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);

	device_हटाओ_bin_file(&pdev->dev, &firmware_attr);
	vमुक्त(firmware_attr.निजी);
पूर्ण

/**
 * पूर्णांकel_gvt_मुक्त_firmware - मुक्त GVT firmware
 * @gvt: पूर्णांकel gvt device
 *
 */
व्योम पूर्णांकel_gvt_मुक्त_firmware(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	अगर (!gvt->firmware.firmware_loaded)
		clean_firmware_sysfs(gvt);

	kमुक्त(gvt->firmware.cfg_space);
	vमुक्त(gvt->firmware.mmio);
पूर्ण

अटल पूर्णांक verअगरy_firmware(काष्ठा पूर्णांकel_gvt *gvt,
			   स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);
	काष्ठा gvt_firmware_header *h;
	अचिन्हित दीर्घ id, crc32_start;
	स्थिर व्योम *mem;
	स्थिर अक्षर *item;
	u64 file, request;

	h = (काष्ठा gvt_firmware_header *)fw->data;

	crc32_start = दुरत्वend(काष्ठा gvt_firmware_header, crc32);
	mem = fw->data + crc32_start;

#घोषणा VERIFY(s, a, b) करो अणु \
	item = (s); file = (u64)(a); request = (u64)(b); \
	अगर ((a) != (b)) \
		जाओ invalid_firmware; \
पूर्ण जबतक (0)

	VERIFY("magic number", h->magic, VGT_MAGIC);
	VERIFY("version", h->version, FIRMWARE_VERSION);
	VERIFY("crc32", h->crc32, crc32_le(0, mem, fw->size - crc32_start));
	VERIFY("cfg space size", h->cfg_space_size, info->cfg_space_size);
	VERIFY("mmio size", h->mmio_size, info->mmio_size);

	mem = (fw->data + h->cfg_space_offset);

	id = *(u16 *)(mem + PCI_VENDOR_ID);
	VERIFY("vender id", id, pdev->venकरोr);

	id = *(u16 *)(mem + PCI_DEVICE_ID);
	VERIFY("device id", id, pdev->device);

	id = *(u8 *)(mem + PCI_REVISION_ID);
	VERIFY("revision id", id, pdev->revision);

#अघोषित VERIFY
	वापस 0;

invalid_firmware:
	gvt_dbg_core("Invalid firmware: %s [file] 0x%llx [request] 0x%llx\n",
		     item, file, request);
	वापस -EINVAL;
पूर्ण

#घोषणा GVT_FIRMWARE_PATH "i915/gvt"

/**
 * पूर्णांकel_gvt_load_firmware - load GVT firmware
 * @gvt: पूर्णांकel gvt device
 *
 */
पूर्णांक पूर्णांकel_gvt_load_firmware(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);
	काष्ठा पूर्णांकel_gvt_firmware *firmware = &gvt->firmware;
	काष्ठा gvt_firmware_header *h;
	स्थिर काष्ठा firmware *fw;
	अक्षर *path;
	व्योम *mem;
	पूर्णांक ret;

	path = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!path)
		वापस -ENOMEM;

	mem = kदो_स्मृति(info->cfg_space_size, GFP_KERNEL);
	अगर (!mem) अणु
		kमुक्त(path);
		वापस -ENOMEM;
	पूर्ण

	firmware->cfg_space = mem;

	mem = vदो_स्मृति(info->mmio_size);
	अगर (!mem) अणु
		kमुक्त(path);
		kमुक्त(firmware->cfg_space);
		वापस -ENOMEM;
	पूर्ण

	firmware->mmio = mem;

	प्र_लिखो(path, "%s/vid_0x%04x_did_0x%04x_rid_0x%02x.golden_hw_state",
		 GVT_FIRMWARE_PATH, pdev->venकरोr, pdev->device,
		 pdev->revision);

	gvt_dbg_core("request hw state firmware %s...\n", path);

	ret = request_firmware(&fw, path, gvt->gt->i915->drm.dev);
	kमुक्त(path);

	अगर (ret)
		जाओ expose_firmware;

	gvt_dbg_core("success.\n");

	ret = verअगरy_firmware(gvt, fw);
	अगर (ret)
		जाओ out_मुक्त_fw;

	gvt_dbg_core("verified.\n");

	h = (काष्ठा gvt_firmware_header *)fw->data;

	स_नकल(firmware->cfg_space, fw->data + h->cfg_space_offset,
	       h->cfg_space_size);
	स_नकल(firmware->mmio, fw->data + h->mmio_offset,
	       h->mmio_size);

	release_firmware(fw);
	firmware->firmware_loaded = true;
	वापस 0;

out_मुक्त_fw:
	release_firmware(fw);
expose_firmware:
	expose_firmware_sysfs(gvt);
	वापस 0;
पूर्ण
