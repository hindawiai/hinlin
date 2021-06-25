<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "bochs.h"

/* ---------------------------------------------------------------------- */

अटल व्योम bochs_vga_ग_लिखोb(काष्ठा bochs_device *bochs, u16 ioport, u8 val)
अणु
	अगर (WARN_ON(ioport < 0x3c0 || ioport > 0x3df))
		वापस;

	अगर (bochs->mmio) अणु
		पूर्णांक offset = ioport - 0x3c0 + 0x400;
		ग_लिखोb(val, bochs->mmio + offset);
	पूर्ण अन्यथा अणु
		outb(val, ioport);
	पूर्ण
पूर्ण

अटल u16 bochs_dispi_पढ़ो(काष्ठा bochs_device *bochs, u16 reg)
अणु
	u16 ret = 0;

	अगर (bochs->mmio) अणु
		पूर्णांक offset = 0x500 + (reg << 1);
		ret = पढ़ोw(bochs->mmio + offset);
	पूर्ण अन्यथा अणु
		outw(reg, VBE_DISPI_IOPORT_INDEX);
		ret = inw(VBE_DISPI_IOPORT_DATA);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम bochs_dispi_ग_लिखो(काष्ठा bochs_device *bochs, u16 reg, u16 val)
अणु
	अगर (bochs->mmio) अणु
		पूर्णांक offset = 0x500 + (reg << 1);
		ग_लिखोw(val, bochs->mmio + offset);
	पूर्ण अन्यथा अणु
		outw(reg, VBE_DISPI_IOPORT_INDEX);
		outw(val, VBE_DISPI_IOPORT_DATA);
	पूर्ण
पूर्ण

अटल व्योम bochs_hw_set_big_endian(काष्ठा bochs_device *bochs)
अणु
	अगर (bochs->qext_size < 8)
		वापस;

	ग_लिखोl(0xbebebebe, bochs->mmio + 0x604);
पूर्ण

अटल व्योम bochs_hw_set_little_endian(काष्ठा bochs_device *bochs)
अणु
	अगर (bochs->qext_size < 8)
		वापस;

	ग_लिखोl(0x1e1e1e1e, bochs->mmio + 0x604);
पूर्ण

#अगर_घोषित __BIG_ENDIAN
#घोषणा bochs_hw_set_native_endian(_b) bochs_hw_set_big_endian(_b)
#अन्यथा
#घोषणा bochs_hw_set_native_endian(_b) bochs_hw_set_little_endian(_b)
#पूर्ण_अगर

अटल पूर्णांक bochs_get_edid_block(व्योम *data, u8 *buf,
				अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा bochs_device *bochs = data;
	माप_प्रकार i, start = block * EDID_LENGTH;

	अगर (start + len > 0x400 /* vga रेजिस्टर offset */)
		वापस -1;

	क्रम (i = 0; i < len; i++) अणु
		buf[i] = पढ़ोb(bochs->mmio + start + i);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bochs_hw_load_edid(काष्ठा bochs_device *bochs)
अणु
	u8 header[8];

	अगर (!bochs->mmio)
		वापस -1;

	/* check header to detect whenever edid support is enabled in qemu */
	bochs_get_edid_block(bochs, header, 0, ARRAY_SIZE(header));
	अगर (drm_edid_header_is_valid(header) != 8)
		वापस -1;

	kमुक्त(bochs->edid);
	bochs->edid = drm_करो_get_edid(&bochs->connector,
				      bochs_get_edid_block, bochs);
	अगर (bochs->edid == शून्य)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक bochs_hw_init(काष्ठा drm_device *dev)
अणु
	काष्ठा bochs_device *bochs = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	अचिन्हित दीर्घ addr, size, mem, ioaddr, iosize;
	u16 id;

	अगर (pdev->resource[2].flags & IORESOURCE_MEM) अणु
		/* mmio bar with vga and bochs रेजिस्टरs present */
		अगर (pci_request_region(pdev, 2, "bochs-drm") != 0) अणु
			DRM_ERROR("Cannot request mmio region\n");
			वापस -EBUSY;
		पूर्ण
		ioaddr = pci_resource_start(pdev, 2);
		iosize = pci_resource_len(pdev, 2);
		bochs->mmio = ioremap(ioaddr, iosize);
		अगर (bochs->mmio == शून्य) अणु
			DRM_ERROR("Cannot map mmio region\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		ioaddr = VBE_DISPI_IOPORT_INDEX;
		iosize = 2;
		अगर (!request_region(ioaddr, iosize, "bochs-drm")) अणु
			DRM_ERROR("Cannot request ioports\n");
			वापस -EBUSY;
		पूर्ण
		bochs->ioports = 1;
	पूर्ण

	id = bochs_dispi_पढ़ो(bochs, VBE_DISPI_INDEX_ID);
	mem = bochs_dispi_पढ़ो(bochs, VBE_DISPI_INDEX_VIDEO_MEMORY_64K)
		* 64 * 1024;
	अगर ((id & 0xfff0) != VBE_DISPI_ID0) अणु
		DRM_ERROR("ID mismatch\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((pdev->resource[0].flags & IORESOURCE_MEM) == 0)
		वापस -ENODEV;
	addr = pci_resource_start(pdev, 0);
	size = pci_resource_len(pdev, 0);
	अगर (addr == 0)
		वापस -ENODEV;
	अगर (size != mem) अणु
		DRM_ERROR("Size mismatch: pci=%ld, bochs=%ld\n",
			size, mem);
		size = min(size, mem);
	पूर्ण

	अगर (pci_request_region(pdev, 0, "bochs-drm") != 0)
		DRM_WARN("Cannot request framebuffer, boot fb still active?\n");

	bochs->fb_map = ioremap(addr, size);
	अगर (bochs->fb_map == शून्य) अणु
		DRM_ERROR("Cannot map framebuffer\n");
		वापस -ENOMEM;
	पूर्ण
	bochs->fb_base = addr;
	bochs->fb_size = size;

	DRM_INFO("Found bochs VGA, ID 0x%x.\n", id);
	DRM_INFO("Framebuffer size %ld kB @ 0x%lx, %s @ 0x%lx.\n",
		 size / 1024, addr,
		 bochs->ioports ? "ioports" : "mmio",
		 ioaddr);

	अगर (bochs->mmio && pdev->revision >= 2) अणु
		bochs->qext_size = पढ़ोl(bochs->mmio + 0x600);
		अगर (bochs->qext_size < 4 || bochs->qext_size > iosize) अणु
			bochs->qext_size = 0;
			जाओ noext;
		पूर्ण
		DRM_DEBUG("Found qemu ext regs, size %ld\n",
			  bochs->qext_size);
		bochs_hw_set_native_endian(bochs);
	पूर्ण

noext:
	वापस 0;
पूर्ण

व्योम bochs_hw_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा bochs_device *bochs = dev->dev_निजी;

	/* TODO: shot करोwn existing vram mappings */

	अगर (bochs->mmio)
		iounmap(bochs->mmio);
	अगर (bochs->ioports)
		release_region(VBE_DISPI_IOPORT_INDEX, 2);
	अगर (bochs->fb_map)
		iounmap(bochs->fb_map);
	pci_release_regions(to_pci_dev(dev->dev));
	kमुक्त(bochs->edid);
पूर्ण

व्योम bochs_hw_seपंचांगode(काष्ठा bochs_device *bochs,
		      काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक idx;

	अगर (!drm_dev_enter(bochs->dev, &idx))
		वापस;

	bochs->xres = mode->hdisplay;
	bochs->yres = mode->vdisplay;
	bochs->bpp = 32;
	bochs->stride = mode->hdisplay * (bochs->bpp / 8);
	bochs->yres_भव = bochs->fb_size / bochs->stride;

	DRM_DEBUG_DRIVER("%dx%d @ %d bpp, vy %d\n",
			 bochs->xres, bochs->yres, bochs->bpp,
			 bochs->yres_भव);

	bochs_vga_ग_लिखोb(bochs, 0x3c0, 0x20); /* unblank */

	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_ENABLE,      0);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_BPP,         bochs->bpp);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_XRES,        bochs->xres);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_YRES,        bochs->yres);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_BANK,        0);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_VIRT_WIDTH,  bochs->xres);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_VIRT_HEIGHT,
			  bochs->yres_भव);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_X_OFFSET,    0);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_Y_OFFSET,    0);

	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_ENABLE,
			  VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);

	drm_dev_निकास(idx);
पूर्ण

व्योम bochs_hw_setक्रमmat(काष्ठा bochs_device *bochs,
			स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	पूर्णांक idx;

	अगर (!drm_dev_enter(bochs->dev, &idx))
		वापस;

	DRM_DEBUG_DRIVER("format %c%c%c%c\n",
			 (क्रमmat->क्रमmat >>  0) & 0xff,
			 (क्रमmat->क्रमmat >>  8) & 0xff,
			 (क्रमmat->क्रमmat >> 16) & 0xff,
			 (क्रमmat->क्रमmat >> 24) & 0xff);

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
		bochs_hw_set_little_endian(bochs);
		अवरोध;
	हाल DRM_FORMAT_BGRX8888:
		bochs_hw_set_big_endian(bochs);
		अवरोध;
	शेष:
		/* should not happen */
		DRM_ERROR("%s: Huh? Got framebuffer format 0x%x",
			  __func__, क्रमmat->क्रमmat);
		अवरोध;
	पूर्ण

	drm_dev_निकास(idx);
पूर्ण

व्योम bochs_hw_setbase(काष्ठा bochs_device *bochs,
		      पूर्णांक x, पूर्णांक y, पूर्णांक stride, u64 addr)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक vx, vy, vwidth, idx;

	अगर (!drm_dev_enter(bochs->dev, &idx))
		वापस;

	bochs->stride = stride;
	offset = (अचिन्हित दीर्घ)addr +
		y * bochs->stride +
		x * (bochs->bpp / 8);
	vy = offset / bochs->stride;
	vx = (offset % bochs->stride) * 8 / bochs->bpp;
	vwidth = stride * 8 / bochs->bpp;

	DRM_DEBUG_DRIVER("x %d, y %d, addr %llx -> offset %lx, vx %d, vy %d\n",
			 x, y, addr, offset, vx, vy);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_VIRT_WIDTH, vwidth);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_X_OFFSET, vx);
	bochs_dispi_ग_लिखो(bochs, VBE_DISPI_INDEX_Y_OFFSET, vy);

	drm_dev_निकास(idx);
पूर्ण
