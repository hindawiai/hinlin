<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediated भव PCI display host device driver
 *
 * Emulate enough of qemu stdvga to make bochs-drm.ko happy.  That is
 * basically the vram memory bar and the bochs dispi पूर्णांकerface vbe
 * रेजिस्टरs in the mmio रेजिस्टर bar.	Specअगरically it करोes *not*
 * include any legacy vga stuff.  Device looks a lot like "qemu -device
 * secondary-vga".
 *
 *   (c) Gerd Hoffmann <kraxel@redhat.com>
 *
 * based on mtty driver which is:
 *   Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *	 Author: Neo Jia <cjia@nvidia.com>
 *		 Kirti Wankhede <kwankhede@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/cdev.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/mdev.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/highस्मृति.स>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_modeset_lock.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_plane.h>


#घोषणा VBE_DISPI_INDEX_ID		0x0
#घोषणा VBE_DISPI_INDEX_XRES		0x1
#घोषणा VBE_DISPI_INDEX_YRES		0x2
#घोषणा VBE_DISPI_INDEX_BPP		0x3
#घोषणा VBE_DISPI_INDEX_ENABLE		0x4
#घोषणा VBE_DISPI_INDEX_BANK		0x5
#घोषणा VBE_DISPI_INDEX_VIRT_WIDTH	0x6
#घोषणा VBE_DISPI_INDEX_VIRT_HEIGHT	0x7
#घोषणा VBE_DISPI_INDEX_X_OFFSET	0x8
#घोषणा VBE_DISPI_INDEX_Y_OFFSET	0x9
#घोषणा VBE_DISPI_INDEX_VIDEO_MEMORY_64K 0xa
#घोषणा VBE_DISPI_INDEX_COUNT		0xb

#घोषणा VBE_DISPI_ID0			0xB0C0
#घोषणा VBE_DISPI_ID1			0xB0C1
#घोषणा VBE_DISPI_ID2			0xB0C2
#घोषणा VBE_DISPI_ID3			0xB0C3
#घोषणा VBE_DISPI_ID4			0xB0C4
#घोषणा VBE_DISPI_ID5			0xB0C5

#घोषणा VBE_DISPI_DISABLED		0x00
#घोषणा VBE_DISPI_ENABLED		0x01
#घोषणा VBE_DISPI_GETCAPS		0x02
#घोषणा VBE_DISPI_8BIT_DAC		0x20
#घोषणा VBE_DISPI_LFB_ENABLED		0x40
#घोषणा VBE_DISPI_NOCLEARMEM		0x80


#घोषणा MBOCHS_NAME		  "mbochs"
#घोषणा MBOCHS_CLASS_NAME	  "mbochs"

#घोषणा MBOCHS_EDID_REGION_INDEX  VFIO_PCI_NUM_REGIONS
#घोषणा MBOCHS_NUM_REGIONS        (MBOCHS_EDID_REGION_INDEX+1)

#घोषणा MBOCHS_CONFIG_SPACE_SIZE  0xff
#घोषणा MBOCHS_MMIO_BAR_OFFSET	  PAGE_SIZE
#घोषणा MBOCHS_MMIO_BAR_SIZE	  PAGE_SIZE
#घोषणा MBOCHS_EDID_OFFSET	  (MBOCHS_MMIO_BAR_OFFSET +	\
				   MBOCHS_MMIO_BAR_SIZE)
#घोषणा MBOCHS_EDID_SIZE	  PAGE_SIZE
#घोषणा MBOCHS_MEMORY_BAR_OFFSET  (MBOCHS_EDID_OFFSET + \
				   MBOCHS_EDID_SIZE)

#घोषणा MBOCHS_EDID_BLOB_OFFSET   (MBOCHS_EDID_SIZE/2)

#घोषणा STORE_LE16(addr, val)	(*(u16 *)addr = val)
#घोषणा STORE_LE32(addr, val)	(*(u32 *)addr = val)


MODULE_LICENSE("GPL v2");

अटल पूर्णांक max_mbytes = 256;
module_param_named(count, max_mbytes, पूर्णांक, 0444);
MODULE_PARM_DESC(mem, "megabytes available to " MBOCHS_NAME " devices");


#घोषणा MBOCHS_TYPE_1 "small"
#घोषणा MBOCHS_TYPE_2 "medium"
#घोषणा MBOCHS_TYPE_3 "large"

अटल स्थिर काष्ठा mbochs_type अणु
	स्थिर अक्षर *name;
	u32 mbytes;
	u32 max_x;
	u32 max_y;
पूर्ण mbochs_types[] = अणु
	अणु
		.name	= MBOCHS_CLASS_NAME "-" MBOCHS_TYPE_1,
		.mbytes = 4,
		.max_x  = 800,
		.max_y  = 600,
	पूर्ण, अणु
		.name	= MBOCHS_CLASS_NAME "-" MBOCHS_TYPE_2,
		.mbytes = 16,
		.max_x  = 1920,
		.max_y  = 1440,
	पूर्ण, अणु
		.name	= MBOCHS_CLASS_NAME "-" MBOCHS_TYPE_3,
		.mbytes = 64,
		.max_x  = 0,
		.max_y  = 0,
	पूर्ण,
पूर्ण;


अटल dev_t		mbochs_devt;
अटल काष्ठा class	*mbochs_class;
अटल काष्ठा cdev	mbochs_cdev;
अटल काष्ठा device	mbochs_dev;
अटल पूर्णांक		mbochs_used_mbytes;

काष्ठा vfio_region_info_ext अणु
	काष्ठा vfio_region_info          base;
	काष्ठा vfio_region_info_cap_type type;
पूर्ण;

काष्ठा mbochs_mode अणु
	u32 drm_क्रमmat;
	u32 bytepp;
	u32 width;
	u32 height;
	u32 stride;
	u32 __pad;
	u64 offset;
	u64 size;
पूर्ण;

काष्ठा mbochs_dmabuf अणु
	काष्ठा mbochs_mode mode;
	u32 id;
	काष्ठा page **pages;
	pgoff_t pagecount;
	काष्ठा dma_buf *buf;
	काष्ठा mdev_state *mdev_state;
	काष्ठा list_head next;
	bool unlinked;
पूर्ण;

/* State of each mdev device */
काष्ठा mdev_state अणु
	u8 *vconfig;
	u64 bar_mask[3];
	u32 memory_bar_mask;
	काष्ठा mutex ops_lock;
	काष्ठा mdev_device *mdev;

	स्थिर काष्ठा mbochs_type *type;
	u16 vbe[VBE_DISPI_INDEX_COUNT];
	u64 memsize;
	काष्ठा page **pages;
	pgoff_t pagecount;
	काष्ठा vfio_region_gfx_edid edid_regs;
	u8 edid_blob[0x400];

	काष्ठा list_head dmabufs;
	u32 active_id;
	u32 next_id;
पूर्ण;

अटल स्थिर अक्षर *vbe_name_list[VBE_DISPI_INDEX_COUNT] = अणु
	[VBE_DISPI_INDEX_ID]               = "id",
	[VBE_DISPI_INDEX_XRES]             = "xres",
	[VBE_DISPI_INDEX_YRES]             = "yres",
	[VBE_DISPI_INDEX_BPP]              = "bpp",
	[VBE_DISPI_INDEX_ENABLE]           = "enable",
	[VBE_DISPI_INDEX_BANK]             = "bank",
	[VBE_DISPI_INDEX_VIRT_WIDTH]       = "virt-width",
	[VBE_DISPI_INDEX_VIRT_HEIGHT]      = "virt-height",
	[VBE_DISPI_INDEX_X_OFFSET]         = "x-offset",
	[VBE_DISPI_INDEX_Y_OFFSET]         = "y-offset",
	[VBE_DISPI_INDEX_VIDEO_MEMORY_64K] = "video-mem",
पूर्ण;

अटल स्थिर अक्षर *vbe_name(u32 index)
अणु
	अगर (index < ARRAY_SIZE(vbe_name_list))
		वापस vbe_name_list[index];
	वापस "(invalid)";
पूर्ण

अटल काष्ठा page *__mbochs_get_page(काष्ठा mdev_state *mdev_state,
				      pgoff_t pgoff);
अटल काष्ठा page *mbochs_get_page(काष्ठा mdev_state *mdev_state,
				    pgoff_t pgoff);

अटल व्योम mbochs_create_config_space(काष्ठा mdev_state *mdev_state)
अणु
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_VENDOR_ID],
		   0x1234);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_DEVICE_ID],
		   0x1111);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_VENDOR_ID],
		   PCI_SUBVENDOR_ID_REDHAT_QUMRANET);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_ID],
		   PCI_SUBDEVICE_ID_QEMU);

	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_COMMAND],
		   PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_CLASS_DEVICE],
		   PCI_CLASS_DISPLAY_OTHER);
	mdev_state->vconfig[PCI_CLASS_REVISION] =  0x01;

	STORE_LE32((u32 *) &mdev_state->vconfig[PCI_BASE_ADDRESS_0],
		   PCI_BASE_ADDRESS_SPACE_MEMORY |
		   PCI_BASE_ADDRESS_MEM_TYPE_32	 |
		   PCI_BASE_ADDRESS_MEM_PREFETCH);
	mdev_state->bar_mask[0] = ~(mdev_state->memsize) + 1;

	STORE_LE32((u32 *) &mdev_state->vconfig[PCI_BASE_ADDRESS_2],
		   PCI_BASE_ADDRESS_SPACE_MEMORY |
		   PCI_BASE_ADDRESS_MEM_TYPE_32);
	mdev_state->bar_mask[2] = ~(MBOCHS_MMIO_BAR_SIZE) + 1;
पूर्ण

अटल पूर्णांक mbochs_check_framebuffer(काष्ठा mdev_state *mdev_state,
				    काष्ठा mbochs_mode *mode)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	u16 *vbe = mdev_state->vbe;
	u32 virt_width;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	अगर (!(vbe[VBE_DISPI_INDEX_ENABLE] & VBE_DISPI_ENABLED))
		जाओ nofb;

	स_रखो(mode, 0, माप(*mode));
	चयन (vbe[VBE_DISPI_INDEX_BPP]) अणु
	हाल 32:
		mode->drm_क्रमmat = DRM_FORMAT_XRGB8888;
		mode->bytepp = 4;
		अवरोध;
	शेष:
		dev_info_ratelimited(dev, "%s: bpp %d not supported\n",
				     __func__, vbe[VBE_DISPI_INDEX_BPP]);
		जाओ nofb;
	पूर्ण

	mode->width  = vbe[VBE_DISPI_INDEX_XRES];
	mode->height = vbe[VBE_DISPI_INDEX_YRES];
	virt_width  = vbe[VBE_DISPI_INDEX_VIRT_WIDTH];
	अगर (virt_width < mode->width)
		virt_width = mode->width;
	mode->stride = virt_width * mode->bytepp;
	mode->size   = (u64)mode->stride * mode->height;
	mode->offset = ((u64)vbe[VBE_DISPI_INDEX_X_OFFSET] * mode->bytepp +
		       (u64)vbe[VBE_DISPI_INDEX_Y_OFFSET] * mode->stride);

	अगर (mode->width < 64 || mode->height < 64) अणु
		dev_info_ratelimited(dev, "%s: invalid resolution %dx%d\n",
				     __func__, mode->width, mode->height);
		जाओ nofb;
	पूर्ण
	अगर (mode->offset + mode->size > mdev_state->memsize) अणु
		dev_info_ratelimited(dev, "%s: framebuffer memory overflow\n",
				     __func__);
		जाओ nofb;
	पूर्ण

	वापस 0;

nofb:
	स_रखो(mode, 0, माप(*mode));
	वापस -EINVAL;
पूर्ण

अटल bool mbochs_modes_equal(काष्ठा mbochs_mode *mode1,
			       काष्ठा mbochs_mode *mode2)
अणु
	वापस स_भेद(mode1, mode2, माप(काष्ठा mbochs_mode)) == 0;
पूर्ण

अटल व्योम handle_pci_cfg_ग_लिखो(काष्ठा mdev_state *mdev_state, u16 offset,
				 अक्षर *buf, u32 count)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	पूर्णांक index = (offset - PCI_BASE_ADDRESS_0) / 0x04;
	u32 cfg_addr;

	चयन (offset) अणु
	हाल PCI_BASE_ADDRESS_0:
	हाल PCI_BASE_ADDRESS_2:
		cfg_addr = *(u32 *)buf;

		अगर (cfg_addr == 0xffffffff) अणु
			cfg_addr = (cfg_addr & mdev_state->bar_mask[index]);
		पूर्ण अन्यथा अणु
			cfg_addr &= PCI_BASE_ADDRESS_MEM_MASK;
			अगर (cfg_addr)
				dev_info(dev, "BAR #%d @ 0x%x\n",
					 index, cfg_addr);
		पूर्ण

		cfg_addr |= (mdev_state->vconfig[offset] &
			     ~PCI_BASE_ADDRESS_MEM_MASK);
		STORE_LE32(&mdev_state->vconfig[offset], cfg_addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_mmio_ग_लिखो(काष्ठा mdev_state *mdev_state, u16 offset,
			      अक्षर *buf, u32 count)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	पूर्णांक index;
	u16 reg16;

	चयन (offset) अणु
	हाल 0x400 ... 0x41f: /* vga ioports remapped */
		जाओ unhandled;
	हाल 0x500 ... 0x515: /* bochs dispi पूर्णांकerface */
		अगर (count != 2)
			जाओ unhandled;
		index = (offset - 0x500) / 2;
		reg16 = *(u16 *)buf;
		अगर (index < ARRAY_SIZE(mdev_state->vbe))
			mdev_state->vbe[index] = reg16;
		dev_dbg(dev, "%s: vbe write %d = %d (%s)\n",
			__func__, index, reg16, vbe_name(index));
		अवरोध;
	हाल 0x600 ... 0x607: /* qemu extended regs */
		जाओ unhandled;
	शेष:
unhandled:
		dev_dbg(dev, "%s: @0x%03x, count %d (unhandled)\n",
			__func__, offset, count);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_mmio_पढ़ो(काष्ठा mdev_state *mdev_state, u16 offset,
			     अक्षर *buf, u32 count)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	काष्ठा vfio_region_gfx_edid *edid;
	u16 reg16 = 0;
	पूर्णांक index;

	चयन (offset) अणु
	हाल 0x000 ... 0x3ff: /* edid block */
		edid = &mdev_state->edid_regs;
		अगर (edid->link_state != VFIO_DEVICE_GFX_LINK_STATE_UP ||
		    offset >= edid->edid_size) अणु
			स_रखो(buf, 0, count);
			अवरोध;
		पूर्ण
		स_नकल(buf, mdev_state->edid_blob + offset, count);
		अवरोध;
	हाल 0x500 ... 0x515: /* bochs dispi पूर्णांकerface */
		अगर (count != 2)
			जाओ unhandled;
		index = (offset - 0x500) / 2;
		अगर (index < ARRAY_SIZE(mdev_state->vbe))
			reg16 = mdev_state->vbe[index];
		dev_dbg(dev, "%s: vbe read %d = %d (%s)\n",
			__func__, index, reg16, vbe_name(index));
		*(u16 *)buf = reg16;
		अवरोध;
	शेष:
unhandled:
		dev_dbg(dev, "%s: @0x%03x, count %d (unhandled)\n",
			__func__, offset, count);
		स_रखो(buf, 0, count);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_edid_regs(काष्ठा mdev_state *mdev_state, u16 offset,
			     अक्षर *buf, u32 count, bool is_ग_लिखो)
अणु
	अक्षर *regs = (व्योम *)&mdev_state->edid_regs;

	अगर (offset + count > माप(mdev_state->edid_regs))
		वापस;
	अगर (count != 4)
		वापस;
	अगर (offset % 4)
		वापस;

	अगर (is_ग_लिखो) अणु
		चयन (offset) अणु
		हाल दुरत्व(काष्ठा vfio_region_gfx_edid, link_state):
		हाल दुरत्व(काष्ठा vfio_region_gfx_edid, edid_size):
			स_नकल(regs + offset, buf, count);
			अवरोध;
		शेष:
			/* पढ़ो-only regs */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(buf, regs + offset, count);
	पूर्ण
पूर्ण

अटल व्योम handle_edid_blob(काष्ठा mdev_state *mdev_state, u16 offset,
			     अक्षर *buf, u32 count, bool is_ग_लिखो)
अणु
	अगर (offset + count > mdev_state->edid_regs.edid_max_size)
		वापस;
	अगर (is_ग_लिखो)
		स_नकल(mdev_state->edid_blob + offset, buf, count);
	अन्यथा
		स_नकल(buf, mdev_state->edid_blob + offset, count);
पूर्ण

अटल sमाप_प्रकार mdev_access(काष्ठा mdev_device *mdev, अक्षर *buf, माप_प्रकार count,
			   loff_t pos, bool is_ग_लिखो)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा device *dev = mdev_dev(mdev);
	काष्ठा page *pg;
	loff_t poff;
	अक्षर *map;
	पूर्णांक ret = 0;

	mutex_lock(&mdev_state->ops_lock);

	अगर (pos < MBOCHS_CONFIG_SPACE_SIZE) अणु
		अगर (is_ग_लिखो)
			handle_pci_cfg_ग_लिखो(mdev_state, pos, buf, count);
		अन्यथा
			स_नकल(buf, (mdev_state->vconfig + pos), count);

	पूर्ण अन्यथा अगर (pos >= MBOCHS_MMIO_BAR_OFFSET &&
		   pos + count <= (MBOCHS_MMIO_BAR_OFFSET +
				   MBOCHS_MMIO_BAR_SIZE)) अणु
		pos -= MBOCHS_MMIO_BAR_OFFSET;
		अगर (is_ग_लिखो)
			handle_mmio_ग_लिखो(mdev_state, pos, buf, count);
		अन्यथा
			handle_mmio_पढ़ो(mdev_state, pos, buf, count);

	पूर्ण अन्यथा अगर (pos >= MBOCHS_EDID_OFFSET &&
		   pos + count <= (MBOCHS_EDID_OFFSET +
				   MBOCHS_EDID_SIZE)) अणु
		pos -= MBOCHS_EDID_OFFSET;
		अगर (pos < MBOCHS_EDID_BLOB_OFFSET) अणु
			handle_edid_regs(mdev_state, pos, buf, count, is_ग_लिखो);
		पूर्ण अन्यथा अणु
			pos -= MBOCHS_EDID_BLOB_OFFSET;
			handle_edid_blob(mdev_state, pos, buf, count, is_ग_लिखो);
		पूर्ण

	पूर्ण अन्यथा अगर (pos >= MBOCHS_MEMORY_BAR_OFFSET &&
		   pos + count <=
		   MBOCHS_MEMORY_BAR_OFFSET + mdev_state->memsize) अणु
		pos -= MBOCHS_MMIO_BAR_OFFSET;
		poff = pos & ~PAGE_MASK;
		pg = __mbochs_get_page(mdev_state, pos >> PAGE_SHIFT);
		map = kmap(pg);
		अगर (is_ग_लिखो)
			स_नकल(map + poff, buf, count);
		अन्यथा
			स_नकल(buf, map + poff, count);
		kunmap(pg);
		put_page(pg);

	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: %s @0x%llx (unhandled)\n",
			__func__, is_ग_लिखो ? "WR" : "RD", pos);
		ret = -1;
		जाओ accessfailed;
	पूर्ण

	ret = count;


accessfailed:
	mutex_unlock(&mdev_state->ops_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mbochs_reset(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	u32 size64k = mdev_state->memsize / (64 * 1024);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mdev_state->vbe); i++)
		mdev_state->vbe[i] = 0;
	mdev_state->vbe[VBE_DISPI_INDEX_ID] = VBE_DISPI_ID5;
	mdev_state->vbe[VBE_DISPI_INDEX_VIDEO_MEMORY_64K] = size64k;
	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_create(काष्ठा mdev_device *mdev)
अणु
	स्थिर काष्ठा mbochs_type *type =
		&mbochs_types[mdev_get_type_group_id(mdev)];
	काष्ठा device *dev = mdev_dev(mdev);
	काष्ठा mdev_state *mdev_state;

	अगर (type->mbytes + mbochs_used_mbytes > max_mbytes)
		वापस -ENOMEM;

	mdev_state = kzalloc(माप(काष्ठा mdev_state), GFP_KERNEL);
	अगर (mdev_state == शून्य)
		वापस -ENOMEM;

	mdev_state->vconfig = kzalloc(MBOCHS_CONFIG_SPACE_SIZE, GFP_KERNEL);
	अगर (mdev_state->vconfig == शून्य)
		जाओ err_mem;

	mdev_state->memsize = type->mbytes * 1024 * 1024;
	mdev_state->pagecount = mdev_state->memsize >> PAGE_SHIFT;
	mdev_state->pages = kसुस्मृति(mdev_state->pagecount,
				    माप(काष्ठा page *),
				    GFP_KERNEL);
	अगर (!mdev_state->pages)
		जाओ err_mem;

	dev_info(dev, "%s: %s, %d MB, %ld pages\n", __func__,
		 type->name, type->mbytes, mdev_state->pagecount);

	mutex_init(&mdev_state->ops_lock);
	mdev_state->mdev = mdev;
	mdev_set_drvdata(mdev, mdev_state);
	INIT_LIST_HEAD(&mdev_state->dmabufs);
	mdev_state->next_id = 1;

	mdev_state->type = type;
	mdev_state->edid_regs.max_xres = type->max_x;
	mdev_state->edid_regs.max_yres = type->max_y;
	mdev_state->edid_regs.edid_offset = MBOCHS_EDID_BLOB_OFFSET;
	mdev_state->edid_regs.edid_max_size = माप(mdev_state->edid_blob);
	mbochs_create_config_space(mdev_state);
	mbochs_reset(mdev);

	mbochs_used_mbytes += type->mbytes;
	वापस 0;

err_mem:
	kमुक्त(mdev_state->vconfig);
	kमुक्त(mdev_state);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक mbochs_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	mbochs_used_mbytes -= mdev_state->type->mbytes;
	mdev_set_drvdata(mdev, शून्य);
	kमुक्त(mdev_state->pages);
	kमुक्त(mdev_state->vconfig);
	kमुक्त(mdev_state);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mbochs_पढ़ो(काष्ठा mdev_device *mdev, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			ret =  mdev_access(mdev, (अक्षर *)&val, माप(val),
					   *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;

पढ़ो_err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार mbochs_ग_लिखो(काष्ठा mdev_device *mdev, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 1;
		पूर्ण
		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
ग_लिखो_err:
	वापस -EFAULT;
पूर्ण

अटल काष्ठा page *__mbochs_get_page(काष्ठा mdev_state *mdev_state,
				      pgoff_t pgoff)
अणु
	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	अगर (!mdev_state->pages[pgoff]) अणु
		mdev_state->pages[pgoff] =
			alloc_pages(GFP_HIGHUSER | __GFP_ZERO, 0);
		अगर (!mdev_state->pages[pgoff])
			वापस शून्य;
	पूर्ण

	get_page(mdev_state->pages[pgoff]);
	वापस mdev_state->pages[pgoff];
पूर्ण

अटल काष्ठा page *mbochs_get_page(काष्ठा mdev_state *mdev_state,
				    pgoff_t pgoff)
अणु
	काष्ठा page *page;

	अगर (WARN_ON(pgoff >= mdev_state->pagecount))
		वापस शून्य;

	mutex_lock(&mdev_state->ops_lock);
	page = __mbochs_get_page(mdev_state, pgoff);
	mutex_unlock(&mdev_state->ops_lock);

	वापस page;
पूर्ण

अटल व्योम mbochs_put_pages(काष्ठा mdev_state *mdev_state)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	पूर्णांक i, count = 0;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	क्रम (i = 0; i < mdev_state->pagecount; i++) अणु
		अगर (!mdev_state->pages[i])
			जारी;
		put_page(mdev_state->pages[i]);
		mdev_state->pages[i] = शून्य;
		count++;
	पूर्ण
	dev_dbg(dev, "%s: %d pages released\n", __func__, count);
पूर्ण

अटल vm_fault_t mbochs_region_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा mdev_state *mdev_state = vma->vm_निजी_data;
	pgoff_t page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	अगर (page_offset >= mdev_state->pagecount)
		वापस VM_FAULT_SIGBUS;

	vmf->page = mbochs_get_page(mdev_state, page_offset);
	अगर (!vmf->page)
		वापस VM_FAULT_SIGBUS;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा mbochs_region_vm_ops = अणु
	.fault = mbochs_region_vm_fault,
पूर्ण;

अटल पूर्णांक mbochs_mmap(काष्ठा mdev_device *mdev, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	अगर (vma->vm_pgoff != MBOCHS_MEMORY_BAR_OFFSET >> PAGE_SHIFT)
		वापस -EINVAL;
	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर (vma->vm_end - vma->vm_start > mdev_state->memsize)
		वापस -EINVAL;
	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;

	vma->vm_ops = &mbochs_region_vm_ops;
	vma->vm_निजी_data = mdev_state;
	वापस 0;
पूर्ण

अटल vm_fault_t mbochs_dmabuf_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा mbochs_dmabuf *dmabuf = vma->vm_निजी_data;

	अगर (WARN_ON(vmf->pgoff >= dmabuf->pagecount))
		वापस VM_FAULT_SIGBUS;

	vmf->page = dmabuf->pages[vmf->pgoff];
	get_page(vmf->page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा mbochs_dmabuf_vm_ops = अणु
	.fault = mbochs_dmabuf_vm_fault,
पूर्ण;

अटल पूर्णांक mbochs_mmap_dmabuf(काष्ठा dma_buf *buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mbochs_dmabuf *dmabuf = buf->priv;
	काष्ठा device *dev = mdev_dev(dmabuf->mdev_state->mdev);

	dev_dbg(dev, "%s: %d\n", __func__, dmabuf->id);

	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;

	vma->vm_ops = &mbochs_dmabuf_vm_ops;
	vma->vm_निजी_data = dmabuf;
	वापस 0;
पूर्ण

अटल व्योम mbochs_prपूर्णांक_dmabuf(काष्ठा mbochs_dmabuf *dmabuf,
				स्थिर अक्षर *prefix)
अणु
	काष्ठा device *dev = mdev_dev(dmabuf->mdev_state->mdev);
	u32 fourcc = dmabuf->mode.drm_क्रमmat;

	dev_dbg(dev, "%s/%d: %c%c%c%c, %dx%d, stride %d, off 0x%llx, size 0x%llx, pages %ld\n",
		prefix, dmabuf->id,
		fourcc ? ((fourcc >>  0) & 0xff) : '-',
		fourcc ? ((fourcc >>  8) & 0xff) : '-',
		fourcc ? ((fourcc >> 16) & 0xff) : '-',
		fourcc ? ((fourcc >> 24) & 0xff) : '-',
		dmabuf->mode.width, dmabuf->mode.height, dmabuf->mode.stride,
		dmabuf->mode.offset, dmabuf->mode.size, dmabuf->pagecount);
पूर्ण

अटल काष्ठा sg_table *mbochs_map_dmabuf(काष्ठा dma_buf_attachment *at,
					  क्रमागत dma_data_direction direction)
अणु
	काष्ठा mbochs_dmabuf *dmabuf = at->dmabuf->priv;
	काष्ठा device *dev = mdev_dev(dmabuf->mdev_state->mdev);
	काष्ठा sg_table *sg;

	dev_dbg(dev, "%s: %d\n", __func__, dmabuf->id);

	sg = kzalloc(माप(*sg), GFP_KERNEL);
	अगर (!sg)
		जाओ err1;
	अगर (sg_alloc_table_from_pages(sg, dmabuf->pages, dmabuf->pagecount,
				      0, dmabuf->mode.size, GFP_KERNEL) < 0)
		जाओ err2;
	अगर (dma_map_sgtable(at->dev, sg, direction, 0))
		जाओ err3;

	वापस sg;

err3:
	sg_मुक्त_table(sg);
err2:
	kमुक्त(sg);
err1:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम mbochs_unmap_dmabuf(काष्ठा dma_buf_attachment *at,
				काष्ठा sg_table *sg,
				क्रमागत dma_data_direction direction)
अणु
	काष्ठा mbochs_dmabuf *dmabuf = at->dmabuf->priv;
	काष्ठा device *dev = mdev_dev(dmabuf->mdev_state->mdev);

	dev_dbg(dev, "%s: %d\n", __func__, dmabuf->id);

	dma_unmap_sgtable(at->dev, sg, direction, 0);
	sg_मुक्त_table(sg);
	kमुक्त(sg);
पूर्ण

अटल व्योम mbochs_release_dmabuf(काष्ठा dma_buf *buf)
अणु
	काष्ठा mbochs_dmabuf *dmabuf = buf->priv;
	काष्ठा mdev_state *mdev_state = dmabuf->mdev_state;
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	pgoff_t pg;

	dev_dbg(dev, "%s: %d\n", __func__, dmabuf->id);

	क्रम (pg = 0; pg < dmabuf->pagecount; pg++)
		put_page(dmabuf->pages[pg]);

	mutex_lock(&mdev_state->ops_lock);
	dmabuf->buf = शून्य;
	अगर (dmabuf->unlinked)
		kमुक्त(dmabuf);
	mutex_unlock(&mdev_state->ops_lock);
पूर्ण

अटल काष्ठा dma_buf_ops mbochs_dmabuf_ops = अणु
	.map_dma_buf	  = mbochs_map_dmabuf,
	.unmap_dma_buf	  = mbochs_unmap_dmabuf,
	.release	  = mbochs_release_dmabuf,
	.mmap		  = mbochs_mmap_dmabuf,
पूर्ण;

अटल काष्ठा mbochs_dmabuf *mbochs_dmabuf_alloc(काष्ठा mdev_state *mdev_state,
						 काष्ठा mbochs_mode *mode)
अणु
	काष्ठा mbochs_dmabuf *dmabuf;
	pgoff_t page_offset, pg;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	dmabuf = kzalloc(माप(काष्ठा mbochs_dmabuf), GFP_KERNEL);
	अगर (!dmabuf)
		वापस शून्य;

	dmabuf->mode = *mode;
	dmabuf->id = mdev_state->next_id++;
	dmabuf->pagecount = DIV_ROUND_UP(mode->size, PAGE_SIZE);
	dmabuf->pages = kसुस्मृति(dmabuf->pagecount, माप(काष्ठा page *),
				GFP_KERNEL);
	अगर (!dmabuf->pages)
		जाओ err_मुक्त_dmabuf;

	page_offset = dmabuf->mode.offset >> PAGE_SHIFT;
	क्रम (pg = 0; pg < dmabuf->pagecount; pg++) अणु
		dmabuf->pages[pg] = __mbochs_get_page(mdev_state,
						      page_offset + pg);
		अगर (!dmabuf->pages[pg])
			जाओ err_मुक्त_pages;
	पूर्ण

	dmabuf->mdev_state = mdev_state;
	list_add(&dmabuf->next, &mdev_state->dmabufs);

	mbochs_prपूर्णांक_dmabuf(dmabuf, __func__);
	वापस dmabuf;

err_मुक्त_pages:
	जबतक (pg > 0)
		put_page(dmabuf->pages[--pg]);
	kमुक्त(dmabuf->pages);
err_मुक्त_dmabuf:
	kमुक्त(dmabuf);
	वापस शून्य;
पूर्ण

अटल काष्ठा mbochs_dmabuf *
mbochs_dmabuf_find_by_mode(काष्ठा mdev_state *mdev_state,
			   काष्ठा mbochs_mode *mode)
अणु
	काष्ठा mbochs_dmabuf *dmabuf;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	list_क्रम_each_entry(dmabuf, &mdev_state->dmabufs, next)
		अगर (mbochs_modes_equal(&dmabuf->mode, mode))
			वापस dmabuf;

	वापस शून्य;
पूर्ण

अटल काष्ठा mbochs_dmabuf *
mbochs_dmabuf_find_by_id(काष्ठा mdev_state *mdev_state, u32 id)
अणु
	काष्ठा mbochs_dmabuf *dmabuf;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	list_क्रम_each_entry(dmabuf, &mdev_state->dmabufs, next)
		अगर (dmabuf->id == id)
			वापस dmabuf;

	वापस शून्य;
पूर्ण

अटल पूर्णांक mbochs_dmabuf_export(काष्ठा mbochs_dmabuf *dmabuf)
अणु
	काष्ठा mdev_state *mdev_state = dmabuf->mdev_state;
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	काष्ठा dma_buf *buf;

	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	अगर (!IS_ALIGNED(dmabuf->mode.offset, PAGE_SIZE)) अणु
		dev_info_ratelimited(dev, "%s: framebuffer not page-aligned\n",
				     __func__);
		वापस -EINVAL;
	पूर्ण

	exp_info.ops = &mbochs_dmabuf_ops;
	exp_info.size = dmabuf->mode.size;
	exp_info.priv = dmabuf;

	buf = dma_buf_export(&exp_info);
	अगर (IS_ERR(buf)) अणु
		dev_info_ratelimited(dev, "%s: dma_buf_export failed: %ld\n",
				     __func__, PTR_ERR(buf));
		वापस PTR_ERR(buf);
	पूर्ण

	dmabuf->buf = buf;
	dev_dbg(dev, "%s: %d\n", __func__, dmabuf->id);
	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_get_region_info(काष्ठा mdev_device *mdev,
				  काष्ठा vfio_region_info_ext *ext)
अणु
	काष्ठा vfio_region_info *region_info = &ext->base;
	काष्ठा mdev_state *mdev_state;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -EINVAL;

	अगर (region_info->index >= MBOCHS_NUM_REGIONS)
		वापस -EINVAL;

	चयन (region_info->index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:
		region_info->offset = 0;
		region_info->size   = MBOCHS_CONFIG_SPACE_SIZE;
		region_info->flags  = (VFIO_REGION_INFO_FLAG_READ |
				       VFIO_REGION_INFO_FLAG_WRITE);
		अवरोध;
	हाल VFIO_PCI_BAR0_REGION_INDEX:
		region_info->offset = MBOCHS_MEMORY_BAR_OFFSET;
		region_info->size   = mdev_state->memsize;
		region_info->flags  = (VFIO_REGION_INFO_FLAG_READ  |
				       VFIO_REGION_INFO_FLAG_WRITE |
				       VFIO_REGION_INFO_FLAG_MMAP);
		अवरोध;
	हाल VFIO_PCI_BAR2_REGION_INDEX:
		region_info->offset = MBOCHS_MMIO_BAR_OFFSET;
		region_info->size   = MBOCHS_MMIO_BAR_SIZE;
		region_info->flags  = (VFIO_REGION_INFO_FLAG_READ  |
				       VFIO_REGION_INFO_FLAG_WRITE);
		अवरोध;
	हाल MBOCHS_EDID_REGION_INDEX:
		ext->base.argsz = माप(*ext);
		ext->base.offset = MBOCHS_EDID_OFFSET;
		ext->base.size = MBOCHS_EDID_SIZE;
		ext->base.flags = (VFIO_REGION_INFO_FLAG_READ  |
				   VFIO_REGION_INFO_FLAG_WRITE |
				   VFIO_REGION_INFO_FLAG_CAPS);
		ext->base.cap_offset = दुरत्व(typeof(*ext), type);
		ext->type.header.id = VFIO_REGION_INFO_CAP_TYPE;
		ext->type.header.version = 1;
		ext->type.header.next = 0;
		ext->type.type = VFIO_REGION_TYPE_GFX;
		ext->type.subtype = VFIO_REGION_SUBTYPE_GFX_EDID;
		अवरोध;
	शेष:
		region_info->size   = 0;
		region_info->offset = 0;
		region_info->flags  = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_get_irq_info(काष्ठा mdev_device *mdev,
			       काष्ठा vfio_irq_info *irq_info)
अणु
	irq_info->count = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_get_device_info(काष्ठा mdev_device *mdev,
				  काष्ठा vfio_device_info *dev_info)
अणु
	dev_info->flags = VFIO_DEVICE_FLAGS_PCI;
	dev_info->num_regions = MBOCHS_NUM_REGIONS;
	dev_info->num_irqs = VFIO_PCI_NUM_IRQS;
	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_query_gfx_plane(काष्ठा mdev_device *mdev,
				  काष्ठा vfio_device_gfx_plane_info *plane)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा device *dev = mdev_dev(mdev);
	काष्ठा mbochs_dmabuf *dmabuf;
	काष्ठा mbochs_mode mode;
	पूर्णांक ret;

	अगर (plane->flags & VFIO_GFX_PLANE_TYPE_PROBE) अणु
		अगर (plane->flags == (VFIO_GFX_PLANE_TYPE_PROBE |
				     VFIO_GFX_PLANE_TYPE_DMABUF))
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	अगर (plane->flags != VFIO_GFX_PLANE_TYPE_DMABUF)
		वापस -EINVAL;

	plane->drm_क्रमmat_mod = 0;
	plane->x_pos	      = 0;
	plane->y_pos	      = 0;
	plane->x_hot	      = 0;
	plane->y_hot	      = 0;

	mutex_lock(&mdev_state->ops_lock);

	ret = -EINVAL;
	अगर (plane->drm_plane_type == DRM_PLANE_TYPE_PRIMARY)
		ret = mbochs_check_framebuffer(mdev_state, &mode);
	अगर (ret < 0) अणु
		plane->drm_क्रमmat     = 0;
		plane->width	      = 0;
		plane->height	      = 0;
		plane->stride	      = 0;
		plane->size	      = 0;
		plane->dmabuf_id      = 0;
		जाओ करोne;
	पूर्ण

	dmabuf = mbochs_dmabuf_find_by_mode(mdev_state, &mode);
	अगर (!dmabuf)
		mbochs_dmabuf_alloc(mdev_state, &mode);
	अगर (!dmabuf) अणु
		mutex_unlock(&mdev_state->ops_lock);
		वापस -ENOMEM;
	पूर्ण

	plane->drm_क्रमmat     = dmabuf->mode.drm_क्रमmat;
	plane->width	      = dmabuf->mode.width;
	plane->height	      = dmabuf->mode.height;
	plane->stride	      = dmabuf->mode.stride;
	plane->size	      = dmabuf->mode.size;
	plane->dmabuf_id      = dmabuf->id;

करोne:
	अगर (plane->drm_plane_type == DRM_PLANE_TYPE_PRIMARY &&
	    mdev_state->active_id != plane->dmabuf_id) अणु
		dev_dbg(dev, "%s: primary: %d => %d\n", __func__,
			mdev_state->active_id, plane->dmabuf_id);
		mdev_state->active_id = plane->dmabuf_id;
	पूर्ण
	mutex_unlock(&mdev_state->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mbochs_get_gfx_dmabuf(काष्ठा mdev_device *mdev,
				 u32 id)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा mbochs_dmabuf *dmabuf;

	mutex_lock(&mdev_state->ops_lock);

	dmabuf = mbochs_dmabuf_find_by_id(mdev_state, id);
	अगर (!dmabuf) अणु
		mutex_unlock(&mdev_state->ops_lock);
		वापस -ENOENT;
	पूर्ण

	अगर (!dmabuf->buf)
		mbochs_dmabuf_export(dmabuf);

	mutex_unlock(&mdev_state->ops_lock);

	अगर (!dmabuf->buf)
		वापस -EINVAL;

	वापस dma_buf_fd(dmabuf->buf, 0);
पूर्ण

अटल दीर्घ mbochs_ioctl(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ minsz, outsz;

	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
	अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = mbochs_get_device_info(mdev, &info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_REGION_INFO:
	अणु
		काष्ठा vfio_region_info_ext info;

		minsz = दुरत्वend(typeof(info), base.offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		outsz = info.base.argsz;
		अगर (outsz < minsz)
			वापस -EINVAL;
		अगर (outsz > माप(info))
			वापस -EINVAL;

		ret = mbochs_get_region_info(mdev, &info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, outsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_GET_IRQ_INFO:
	अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर ((info.argsz < minsz) ||
		    (info.index >= VFIO_PCI_NUM_IRQS))
			वापस -EINVAL;

		ret = mbochs_get_irq_info(mdev, &info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_QUERY_GFX_PLANE:
	अणु
		काष्ठा vfio_device_gfx_plane_info plane;

		minsz = दुरत्वend(काष्ठा vfio_device_gfx_plane_info,
				    region_index);

		अगर (copy_from_user(&plane, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (plane.argsz < minsz)
			वापस -EINVAL;

		ret = mbochs_query_gfx_plane(mdev, &plane);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &plane, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_GET_GFX_DMABUF:
	अणु
		u32 dmabuf_id;

		अगर (get_user(dmabuf_id, (__u32 __user *)arg))
			वापस -EFAULT;

		वापस mbochs_get_gfx_dmabuf(mdev, dmabuf_id);
	पूर्ण

	हाल VFIO_DEVICE_SET_IRQS:
		वापस -EINVAL;

	हाल VFIO_DEVICE_RESET:
		वापस mbochs_reset(mdev);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक mbochs_खोलो(काष्ठा mdev_device *mdev)
अणु
	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम mbochs_बंद(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा mbochs_dmabuf *dmabuf, *पंचांगp;

	mutex_lock(&mdev_state->ops_lock);

	list_क्रम_each_entry_safe(dmabuf, पंचांगp, &mdev_state->dmabufs, next) अणु
		list_del(&dmabuf->next);
		अगर (dmabuf->buf) अणु
			/* मुक्त in mbochs_release_dmabuf() */
			dmabuf->unlinked = true;
		पूर्ण अन्यथा अणु
			kमुक्त(dmabuf);
		पूर्ण
	पूर्ण
	mbochs_put_pages(mdev_state);

	mutex_unlock(&mdev_state->ops_lock);
	module_put(THIS_MODULE);
पूर्ण

अटल sमाप_प्रकार
memory_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	    अक्षर *buf)
अणु
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	वापस प्र_लिखो(buf, "%d MB\n", mdev_state->type->mbytes);
पूर्ण
अटल DEVICE_ATTR_RO(memory);

अटल काष्ठा attribute *mdev_dev_attrs[] = अणु
	&dev_attr_memory.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mdev_dev_group = अणु
	.name  = "vendor",
	.attrs = mdev_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mdev_dev_groups[] = अणु
	&mdev_dev_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा mbochs_type *type =
		&mbochs_types[mtype_get_type_group_id(mtype)];

	वापस प्र_लिखो(buf, "%s\n", type->name);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(name);

अटल sमाप_प्रकार description_show(काष्ठा mdev_type *mtype,
				काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा mbochs_type *type =
		&mbochs_types[mtype_get_type_group_id(mtype)];

	वापस प्र_लिखो(buf, "virtual display, %d MB video memory\n",
		       type ? type->mbytes  : 0);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(description);

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	स्थिर काष्ठा mbochs_type *type =
		&mbochs_types[mtype_get_type_group_id(mtype)];
	पूर्णांक count = (max_mbytes - mbochs_used_mbytes) / type->mbytes;

	वापस प्र_लिखो(buf, "%d\n", count);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(available_instances);

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_PCI_STRING);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(device_api);

अटल काष्ठा attribute *mdev_types_attrs[] = अणु
	&mdev_type_attr_name.attr,
	&mdev_type_attr_description.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_available_instances.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group1 = अणु
	.name  = MBOCHS_TYPE_1,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group2 = अणु
	.name  = MBOCHS_TYPE_2,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group3 = अणु
	.name  = MBOCHS_TYPE_3,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group *mdev_type_groups[] = अणु
	&mdev_type_group1,
	&mdev_type_group2,
	&mdev_type_group3,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा mdev_parent_ops mdev_fops = अणु
	.owner			= THIS_MODULE,
	.mdev_attr_groups	= mdev_dev_groups,
	.supported_type_groups	= mdev_type_groups,
	.create			= mbochs_create,
	.हटाओ			= mbochs_हटाओ,
	.खोलो			= mbochs_खोलो,
	.release		= mbochs_बंद,
	.पढ़ो			= mbochs_पढ़ो,
	.ग_लिखो			= mbochs_ग_लिखो,
	.ioctl			= mbochs_ioctl,
	.mmap			= mbochs_mmap,
पूर्ण;

अटल स्थिर काष्ठा file_operations vd_fops = अणु
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम mbochs_device_release(काष्ठा device *dev)
अणु
	/* nothing */
पूर्ण

अटल पूर्णांक __init mbochs_dev_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = alloc_chrdev_region(&mbochs_devt, 0, MINORMASK + 1, MBOCHS_NAME);
	अगर (ret < 0) अणु
		pr_err("Error: failed to register mbochs_dev, err: %d\n", ret);
		वापस ret;
	पूर्ण
	cdev_init(&mbochs_cdev, &vd_fops);
	cdev_add(&mbochs_cdev, mbochs_devt, MINORMASK + 1);
	pr_info("%s: major %d\n", __func__, MAJOR(mbochs_devt));

	mbochs_class = class_create(THIS_MODULE, MBOCHS_CLASS_NAME);
	अगर (IS_ERR(mbochs_class)) अणु
		pr_err("Error: failed to register mbochs_dev class\n");
		ret = PTR_ERR(mbochs_class);
		जाओ failed1;
	पूर्ण
	mbochs_dev.class = mbochs_class;
	mbochs_dev.release = mbochs_device_release;
	dev_set_name(&mbochs_dev, "%s", MBOCHS_NAME);

	ret = device_रेजिस्टर(&mbochs_dev);
	अगर (ret)
		जाओ failed2;

	ret = mdev_रेजिस्टर_device(&mbochs_dev, &mdev_fops);
	अगर (ret)
		जाओ failed3;

	वापस 0;

failed3:
	device_unरेजिस्टर(&mbochs_dev);
failed2:
	class_destroy(mbochs_class);
failed1:
	cdev_del(&mbochs_cdev);
	unरेजिस्टर_chrdev_region(mbochs_devt, MINORMASK + 1);
	वापस ret;
पूर्ण

अटल व्योम __निकास mbochs_dev_निकास(व्योम)
अणु
	mbochs_dev.bus = शून्य;
	mdev_unरेजिस्टर_device(&mbochs_dev);

	device_unरेजिस्टर(&mbochs_dev);
	cdev_del(&mbochs_cdev);
	unरेजिस्टर_chrdev_region(mbochs_devt, MINORMASK + 1);
	class_destroy(mbochs_class);
	mbochs_class = शून्य;
पूर्ण

module_init(mbochs_dev_init)
module_निकास(mbochs_dev_निकास)
