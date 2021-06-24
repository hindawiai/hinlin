<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_managed.h>

#समावेश "mgag200_drv.h"

अटल माप_प्रकार mgag200_probe_vram(काष्ठा mga_device *mdev, व्योम __iomem *mem,
				 माप_प्रकार size)
अणु
	पूर्णांक offset;
	पूर्णांक orig;
	पूर्णांक test1, test2;
	पूर्णांक orig1, orig2;
	माप_प्रकार vram_size;

	/* Probe */
	orig = ioपढ़ो16(mem);
	ioग_लिखो16(0, mem);

	vram_size = size;

	अगर ((mdev->type == G200_EW3) && (vram_size >= 0x1000000))
		vram_size = vram_size - 0x400000;

	क्रम (offset = 0x100000; offset < vram_size; offset += 0x4000) अणु
		orig1 = ioपढ़ो8(mem + offset);
		orig2 = ioपढ़ो8(mem + offset + 0x100);

		ioग_लिखो16(0xaa55, mem + offset);
		ioग_लिखो16(0xaa55, mem + offset + 0x100);

		test1 = ioपढ़ो16(mem + offset);
		test2 = ioपढ़ो16(mem);

		ioग_लिखो16(orig1, mem + offset);
		ioग_लिखो16(orig2, mem + offset + 0x100);

		अगर (test1 != 0xaa55)
			अवरोध;

		अगर (test2)
			अवरोध;
	पूर्ण

	ioग_लिखो16(orig, mem);

	वापस offset - 65536;
पूर्ण

अटल व्योम mgag200_mm_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा mga_device *mdev = to_mga_device(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	mdev->vram_fb_available = 0;
	iounmap(mdev->vram);
	arch_io_मुक्त_memtype_wc(pci_resource_start(pdev, 0),
				pci_resource_len(pdev, 0));
	arch_phys_wc_del(mdev->fb_mtrr);
	mdev->fb_mtrr = 0;
पूर्ण

पूर्णांक mgag200_mm_init(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u8 misc;
	resource_माप_प्रकार start, len;
	पूर्णांक ret;

	WREG_ECRT(0x04, 0x00);

	misc = RREG8(MGA_MISC_IN);
	misc |= MGAREG_MISC_RAMMAPEN |
		MGAREG_MISC_HIGH_PG_SEL;
	WREG8(MGA_MISC_OUT, misc);

	/* BAR 0 is VRAM */
	start = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);

	अगर (!devm_request_mem_region(dev->dev, start, len, "mgadrmfb_vram")) अणु
		drm_err(dev, "can't reserve VRAM\n");
		वापस -ENXIO;
	पूर्ण

	arch_io_reserve_memtype_wc(start, len);

	mdev->fb_mtrr = arch_phys_wc_add(start, len);

	mdev->vram = ioremap(start, len);
	अगर (!mdev->vram) अणु
		ret = -ENOMEM;
		जाओ err_arch_phys_wc_del;
	पूर्ण

	mdev->mc.vram_size = mgag200_probe_vram(mdev, mdev->vram, len);
	mdev->mc.vram_base = start;
	mdev->mc.vram_winकरोw = len;

	mdev->vram_fb_available = mdev->mc.vram_size;

	वापस drmm_add_action_or_reset(dev, mgag200_mm_release, शून्य);

err_arch_phys_wc_del:
	arch_phys_wc_del(mdev->fb_mtrr);
	arch_io_मुक्त_memtype_wc(start, len);
	वापस ret;
पूर्ण
