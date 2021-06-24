<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 1998-2009 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.
 * Copyright 2009 Jonathan Corbet <corbet@lwn.net>
 */

/*
 * Core code क्रम the Via multअगरunction framebuffer device.
 */
#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>
#समावेश <linux/via-gpपन.स>
#समावेश "global.h"

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/pm.h>

/*
 * The शेष port config.
 */
अटल काष्ठा via_port_cfg adap_configs[] = अणु
	[VIA_PORT_26]	= अणु VIA_PORT_I2C,  VIA_MODE_I2C, VIASR, 0x26 पूर्ण,
	[VIA_PORT_31]	= अणु VIA_PORT_I2C,  VIA_MODE_I2C, VIASR, 0x31 पूर्ण,
	[VIA_PORT_25]	= अणु VIA_PORT_GPIO, VIA_MODE_GPIO, VIASR, 0x25 पूर्ण,
	[VIA_PORT_2C]	= अणु VIA_PORT_GPIO, VIA_MODE_I2C, VIASR, 0x2c पूर्ण,
	[VIA_PORT_3D]	= अणु VIA_PORT_GPIO, VIA_MODE_GPIO, VIASR, 0x3d पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

/*
 * The OLPC XO-1.5 माला_दो the camera घातer and reset lines onto
 * GPIO 2C.
 */
अटल काष्ठा via_port_cfg olpc_adap_configs[] = अणु
	[VIA_PORT_26]	= अणु VIA_PORT_I2C,  VIA_MODE_I2C, VIASR, 0x26 पूर्ण,
	[VIA_PORT_31]	= अणु VIA_PORT_I2C,  VIA_MODE_I2C, VIASR, 0x31 पूर्ण,
	[VIA_PORT_25]	= अणु VIA_PORT_GPIO, VIA_MODE_GPIO, VIASR, 0x25 पूर्ण,
	[VIA_PORT_2C]	= अणु VIA_PORT_GPIO, VIA_MODE_GPIO, VIASR, 0x2c पूर्ण,
	[VIA_PORT_3D]	= अणु VIA_PORT_GPIO, VIA_MODE_GPIO, VIASR, 0x3d पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

/*
 * We currently only support one viafb device (will there ever be
 * more than one?), so just declare it globally here.
 */
अटल काष्ठा viafb_dev global_dev;


/*
 * Basic रेजिस्टर access; spinlock required.
 */
अटल अंतरभूत व्योम viafb_mmio_ग_लिखो(पूर्णांक reg, u32 v)
अणु
	ioग_लिखो32(v, global_dev.engine_mmio + reg);
पूर्ण

अटल अंतरभूत पूर्णांक viafb_mmio_पढ़ो(पूर्णांक reg)
अणु
	वापस ioपढ़ो32(global_dev.engine_mmio + reg);
पूर्ण

/* ---------------------------------------------------------------------- */
/*
 * Interrupt management.  We have a single IRQ line क्रम a lot of
 * dअगरferent functions, so we need to share it.  The design here
 * is that we करोn't want to reimplement the shared IRQ code here;
 * we also want to aव्योम having contention क्रम a single handler thपढ़ो.
 * So each subdev driver which needs पूर्णांकerrupts just requests
 * them directly from the kernel.  We just have what's needed क्रम
 * overall access to the पूर्णांकerrupt control रेजिस्टर.
 */

/*
 * Which पूर्णांकerrupts are enabled now?
 */
अटल u32 viafb_enabled_पूर्णांकs;

अटल व्योम viafb_पूर्णांक_init(व्योम)
अणु
	viafb_enabled_पूर्णांकs = 0;

	viafb_mmio_ग_लिखो(VDE_INTERRUPT, 0);
पूर्ण

/*
 * Allow subdevs to ask क्रम specअगरic पूर्णांकerrupts to be enabled.  These
 * functions must be called with reg_lock held
 */
व्योम viafb_irq_enable(u32 mask)
अणु
	viafb_enabled_पूर्णांकs |= mask;
	viafb_mmio_ग_लिखो(VDE_INTERRUPT, viafb_enabled_पूर्णांकs | VDE_I_ENABLE);
पूर्ण
EXPORT_SYMBOL_GPL(viafb_irq_enable);

व्योम viafb_irq_disable(u32 mask)
अणु
	viafb_enabled_पूर्णांकs &= ~mask;
	अगर (viafb_enabled_पूर्णांकs == 0)
		viafb_mmio_ग_लिखो(VDE_INTERRUPT, 0);  /* Disable entirely */
	अन्यथा
		viafb_mmio_ग_लिखो(VDE_INTERRUPT,
				viafb_enabled_पूर्णांकs | VDE_I_ENABLE);
पूर्ण
EXPORT_SYMBOL_GPL(viafb_irq_disable);

/* ---------------------------------------------------------------------- */
/*
 * Currently, the camera driver is the only user of the DMA code, so we
 * only compile it in अगर the camera driver is being built.  Chances are,
 * most viafb प्रणालीs will not need to have this extra code क्रम a जबतक.
 * As soon as another user comes दीर्घ, the अगरdef can be हटाओd.
 */
#अगर IS_ENABLED(CONFIG_VIDEO_VIA_CAMERA)
/*
 * Access to the DMA engine.  This currently provides what the camera
 * driver needs (i.e. outgoing only) but is easily expandable अगर need
 * be.
 */

/*
 * There are four DMA channels in the vx855.  For now, we only
 * use one of them, though.  Most of the समय, the DMA channel
 * will be idle, so we keep the IRQ handler unरेजिस्टरed except
 * when some subप्रणाली has indicated an पूर्णांकerest.
 */
अटल पूर्णांक viafb_dma_users;
अटल DECLARE_COMPLETION(viafb_dma_completion);
/*
 * This mutex protects viafb_dma_users and our global पूर्णांकerrupt
 * registration state; it also serializes access to the DMA
 * engine.
 */
अटल DEFINE_MUTEX(viafb_dma_lock);

/*
 * The VX855 DMA descriptor (used क्रम s/g transfers) looks
 * like this.
 */
काष्ठा viafb_vx855_dma_descr अणु
	u32	addr_low;	/* Low part of phys addr */
	u32	addr_high;	/* High 12 bits of addr */
	u32	fb_offset;	/* Offset पूर्णांकo FB memory */
	u32	seg_size;	/* Size, 16-byte units */
	u32	tile_mode;	/* "tile mode" setting */
	u32	next_desc_low;	/* Next descriptor addr */
	u32	next_desc_high;
	u32	pad;		/* Fill out to 64 bytes */
पूर्ण;

/*
 * Flags added to the "next descriptor low" poपूर्णांकers
 */
#घोषणा VIAFB_DMA_MAGIC		0x01  /* ??? Just has to be there */
#घोषणा VIAFB_DMA_FINAL_SEGMENT 0x02  /* Final segment */

/*
 * The completion IRQ handler.
 */
अटल irqवापस_t viafb_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक csr;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&global_dev.reg_lock);
	csr = viafb_mmio_पढ़ो(VDMA_CSR0);
	अगर (csr & VDMA_C_DONE) अणु
		viafb_mmio_ग_लिखो(VDMA_CSR0, VDMA_C_DONE);
		complete(&viafb_dma_completion);
		ret = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&global_dev.reg_lock);
	वापस ret;
पूर्ण

/*
 * Indicate a need क्रम DMA functionality.
 */
पूर्णांक viafb_request_dma(व्योम)
अणु
	पूर्णांक ret = 0;

	/*
	 * Only VX855 is supported currently.
	 */
	अगर (global_dev.chip_type != UNICHROME_VX855)
		वापस -ENODEV;
	/*
	 * Note the new user and set up our पूर्णांकerrupt handler
	 * अगर need be.
	 */
	mutex_lock(&viafb_dma_lock);
	viafb_dma_users++;
	अगर (viafb_dma_users == 1) अणु
		ret = request_irq(global_dev.pdev->irq, viafb_dma_irq,
				IRQF_SHARED, "via-dma", &viafb_dma_users);
		अगर (ret)
			viafb_dma_users--;
		अन्यथा
			viafb_irq_enable(VDE_I_DMA0TDEN);
	पूर्ण
	mutex_unlock(&viafb_dma_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(viafb_request_dma);

व्योम viafb_release_dma(व्योम)
अणु
	mutex_lock(&viafb_dma_lock);
	viafb_dma_users--;
	अगर (viafb_dma_users == 0) अणु
		viafb_irq_disable(VDE_I_DMA0TDEN);
		मुक्त_irq(global_dev.pdev->irq, &viafb_dma_users);
	पूर्ण
	mutex_unlock(&viafb_dma_lock);
पूर्ण
EXPORT_SYMBOL_GPL(viafb_release_dma);

/*
 * Do a scatter/gather DMA copy from FB memory.  You must have करोne
 * a successful call to viafb_request_dma() first.
 */
पूर्णांक viafb_dma_copy_out_sg(अचिन्हित पूर्णांक offset, काष्ठा scatterlist *sg, पूर्णांक nsg)
अणु
	काष्ठा viafb_vx855_dma_descr *descr;
	व्योम *descrpages;
	dma_addr_t descr_handle;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा scatterlist *sgentry;
	dma_addr_t nextdesc;

	/*
	 * Get a place to put the descriptors.
	 */
	descrpages = dma_alloc_coherent(&global_dev.pdev->dev,
			nsg*माप(काष्ठा viafb_vx855_dma_descr),
			&descr_handle, GFP_KERNEL);
	अगर (descrpages == शून्य) अणु
		dev_err(&global_dev.pdev->dev, "Unable to get descr page.\n");
		वापस -ENOMEM;
	पूर्ण
	mutex_lock(&viafb_dma_lock);
	/*
	 * Fill them in.
	 */
	descr = descrpages;
	nextdesc = descr_handle + माप(काष्ठा viafb_vx855_dma_descr);
	क्रम_each_sg(sg, sgentry, nsg, i) अणु
		dma_addr_t paddr = sg_dma_address(sgentry);
		descr->addr_low = paddr & 0xfffffff0;
		descr->addr_high = ((u64) paddr >> 32) & 0x0fff;
		descr->fb_offset = offset;
		descr->seg_size = sg_dma_len(sgentry) >> 4;
		descr->tile_mode = 0;
		descr->next_desc_low = (nextdesc&0xfffffff0) | VIAFB_DMA_MAGIC;
		descr->next_desc_high = ((u64) nextdesc >> 32) & 0x0fff;
		descr->pad = 0xffffffff;  /* VIA driver करोes this */
		offset += sg_dma_len(sgentry);
		nextdesc += माप(काष्ठा viafb_vx855_dma_descr);
		descr++;
	पूर्ण
	descr[-1].next_desc_low = VIAFB_DMA_FINAL_SEGMENT|VIAFB_DMA_MAGIC;
	/*
	 * Program the engine.
	 */
	spin_lock_irqsave(&global_dev.reg_lock, flags);
	init_completion(&viafb_dma_completion);
	viafb_mmio_ग_लिखो(VDMA_DQWCR0, 0);
	viafb_mmio_ग_लिखो(VDMA_CSR0, VDMA_C_ENABLE|VDMA_C_DONE);
	viafb_mmio_ग_लिखो(VDMA_MR0, VDMA_MR_TDIE | VDMA_MR_CHAIN);
	viafb_mmio_ग_लिखो(VDMA_DPRL0, descr_handle | VIAFB_DMA_MAGIC);
	viafb_mmio_ग_लिखो(VDMA_DPRH0,
			(((u64)descr_handle >> 32) & 0x0fff) | 0xf0000);
	(व्योम) viafb_mmio_पढ़ो(VDMA_CSR0);
	viafb_mmio_ग_लिखो(VDMA_CSR0, VDMA_C_ENABLE|VDMA_C_START);
	spin_unlock_irqrestore(&global_dev.reg_lock, flags);
	/*
	 * Now we just रुको until the पूर्णांकerrupt handler says
	 * we're करोne.  Except that, actually, we need to रुको a little
	 * दीर्घer: the पूर्णांकerrupts seem to jump the gun a little and we
	 * get corrupted frames someबार.
	 */
	रुको_क्रम_completion_समयout(&viafb_dma_completion, 1);
	msleep(1);
	अगर ((viafb_mmio_पढ़ो(VDMA_CSR0)&VDMA_C_DONE) == 0)
		prपूर्णांकk(KERN_ERR "VIA DMA timeout!\n");
	/*
	 * Clean up and we're करोne.
	 */
	viafb_mmio_ग_लिखो(VDMA_CSR0, VDMA_C_DONE);
	viafb_mmio_ग_लिखो(VDMA_MR0, 0); /* Reset पूर्णांक enable */
	mutex_unlock(&viafb_dma_lock);
	dma_मुक्त_coherent(&global_dev.pdev->dev,
			nsg*माप(काष्ठा viafb_vx855_dma_descr), descrpages,
			descr_handle);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(viafb_dma_copy_out_sg);
#पूर्ण_अगर /* CONFIG_VIDEO_VIA_CAMERA */

/* ---------------------------------------------------------------------- */
/*
 * Figure out how big our framebuffer memory is.  Kind of ugly,
 * but evidently we can't trust the inक्रमmation found in the
 * fbdev configuration area.
 */
अटल u16 via_function3[] = अणु
	CLE266_FUNCTION3, KM400_FUNCTION3, CN400_FUNCTION3, CN700_FUNCTION3,
	CX700_FUNCTION3, KM800_FUNCTION3, KM890_FUNCTION3, P4M890_FUNCTION3,
	P4M900_FUNCTION3, VX800_FUNCTION3, VX855_FUNCTION3, VX900_FUNCTION3,
पूर्ण;

/* Get the BIOS-configured framebuffer size from PCI configuration space
 * of function 3 in the respective chipset */
अटल पूर्णांक viafb_get_fb_size_from_pci(पूर्णांक chip_type)
अणु
	पूर्णांक i;
	u8 offset = 0;
	u32 FBSize;
	u32 VideoMemSize;

	/* search क्रम the "FUNCTION3" device in this chipset */
	क्रम (i = 0; i < ARRAY_SIZE(via_function3); i++) अणु
		काष्ठा pci_dev *pdev;

		pdev = pci_get_device(PCI_VENDOR_ID_VIA, via_function3[i],
				      शून्य);
		अगर (!pdev)
			जारी;

		DEBUG_MSG(KERN_INFO "Device ID = %x\n", pdev->device);

		चयन (pdev->device) अणु
		हाल CLE266_FUNCTION3:
		हाल KM400_FUNCTION3:
			offset = 0xE0;
			अवरोध;
		हाल CN400_FUNCTION3:
		हाल CN700_FUNCTION3:
		हाल CX700_FUNCTION3:
		हाल KM800_FUNCTION3:
		हाल KM890_FUNCTION3:
		हाल P4M890_FUNCTION3:
		हाल P4M900_FUNCTION3:
		हाल VX800_FUNCTION3:
		हाल VX855_FUNCTION3:
		हाल VX900_FUNCTION3:
		/*हाल CN750_FUNCTION3: */
			offset = 0xA0;
			अवरोध;
		पूर्ण

		अगर (!offset)
			अवरोध;

		pci_पढ़ो_config_dword(pdev, offset, &FBSize);
		pci_dev_put(pdev);
	पूर्ण

	अगर (!offset) अणु
		prपूर्णांकk(KERN_ERR "cannot determine framebuffer size\n");
		वापस -EIO;
	पूर्ण

	FBSize = FBSize & 0x00007000;
	DEBUG_MSG(KERN_INFO "FB Size = %x\n", FBSize);

	अगर (chip_type < UNICHROME_CX700) अणु
		चयन (FBSize) अणु
		हाल 0x00004000:
			VideoMemSize = (16 << 20);	/*16M */
			अवरोध;

		हाल 0x00005000:
			VideoMemSize = (32 << 20);	/*32M */
			अवरोध;

		हाल 0x00006000:
			VideoMemSize = (64 << 20);	/*64M */
			अवरोध;

		शेष:
			VideoMemSize = (32 << 20);	/*32M */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (FBSize) अणु
		हाल 0x00001000:
			VideoMemSize = (8 << 20);	/*8M */
			अवरोध;

		हाल 0x00002000:
			VideoMemSize = (16 << 20);	/*16M */
			अवरोध;

		हाल 0x00003000:
			VideoMemSize = (32 << 20);	/*32M */
			अवरोध;

		हाल 0x00004000:
			VideoMemSize = (64 << 20);	/*64M */
			अवरोध;

		हाल 0x00005000:
			VideoMemSize = (128 << 20);	/*128M */
			अवरोध;

		हाल 0x00006000:
			VideoMemSize = (256 << 20);	/*256M */
			अवरोध;

		हाल 0x00007000:	/* Only on VX855/875 */
			VideoMemSize = (512 << 20);	/*512M */
			अवरोध;

		शेष:
			VideoMemSize = (32 << 20);	/*32M */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस VideoMemSize;
पूर्ण


/*
 * Figure out and map our MMIO regions.
 */
अटल पूर्णांक via_pci_setup_mmio(काष्ठा viafb_dev *vdev)
अणु
	पूर्णांक ret;
	/*
	 * Hook up to the device रेजिस्टरs.  Note that we soldier
	 * on अगर it fails; the framebuffer can operate (without
	 * acceleration) without this region.
	 */
	vdev->engine_start = pci_resource_start(vdev->pdev, 1);
	vdev->engine_len = pci_resource_len(vdev->pdev, 1);
	vdev->engine_mmio = ioremap(vdev->engine_start,
			vdev->engine_len);
	अगर (vdev->engine_mmio == शून्य)
		dev_err(&vdev->pdev->dev,
				"Unable to map engine MMIO; operation will be "
				"slow and crippled.\n");
	/*
	 * Map in framebuffer memory.  For now, failure here is
	 * fatal.  Unक्रमtunately, in the असलence of signअगरicant
	 * vदो_स्मृति space, failure here is also entirely plausible.
	 * Eventually we want to move away from mapping this
	 * entire region.
	 */
	अगर (vdev->chip_type == UNICHROME_VX900)
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 2);
	अन्यथा
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 0);
	ret = vdev->fbmem_len = viafb_get_fb_size_from_pci(vdev->chip_type);
	अगर (ret < 0)
		जाओ out_unmap;

	/* try to map less memory on failure, 8 MB should be still enough */
	क्रम (; vdev->fbmem_len >= 8 << 20; vdev->fbmem_len /= 2) अणु
		vdev->fbmem = ioremap_wc(vdev->fbmem_start, vdev->fbmem_len);
		अगर (vdev->fbmem)
			अवरोध;
	पूर्ण

	अगर (vdev->fbmem == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण
	वापस 0;
out_unmap:
	iounmap(vdev->engine_mmio);
	वापस ret;
पूर्ण

अटल व्योम via_pci_tearकरोwn_mmio(काष्ठा viafb_dev *vdev)
अणु
	iounmap(vdev->fbmem);
	iounmap(vdev->engine_mmio);
पूर्ण

/*
 * Create our subsidiary devices.
 */
अटल काष्ठा viafb_subdev_info अणु
	अक्षर *name;
	काष्ठा platक्रमm_device *platdev;
पूर्ण viafb_subdevs[] = अणु
	अणु
		.name = "viafb-gpio",
	पूर्ण,
	अणु
		.name = "viafb-i2c",
	पूर्ण,
#अगर IS_ENABLED(CONFIG_VIDEO_VIA_CAMERA)
	अणु
		.name = "viafb-camera",
	पूर्ण,
#पूर्ण_अगर
पूर्ण;
#घोषणा N_SUBDEVS ARRAY_SIZE(viafb_subdevs)

अटल पूर्णांक via_create_subdev(काष्ठा viafb_dev *vdev,
			     काष्ठा viafb_subdev_info *info)
अणु
	पूर्णांक ret;

	info->platdev = platक्रमm_device_alloc(info->name, -1);
	अगर (!info->platdev) अणु
		dev_err(&vdev->pdev->dev, "Unable to allocate pdev %s\n",
			info->name);
		वापस -ENOMEM;
	पूर्ण
	info->platdev->dev.parent = &vdev->pdev->dev;
	info->platdev->dev.platक्रमm_data = vdev;
	ret = platक्रमm_device_add(info->platdev);
	अगर (ret) अणु
		dev_err(&vdev->pdev->dev, "Unable to add pdev %s\n",
				info->name);
		platक्रमm_device_put(info->platdev);
		info->platdev = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक via_setup_subdevs(काष्ठा viafb_dev *vdev)
अणु
	पूर्णांक i;

	/*
	 * Ignore वापस values.  Even अगर some of the devices
	 * fail to be created, we'll still be able to use some
	 * of the rest.
	 */
	क्रम (i = 0; i < N_SUBDEVS; i++)
		via_create_subdev(vdev, viafb_subdevs + i);
	वापस 0;
पूर्ण

अटल व्योम via_tearकरोwn_subdevs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_SUBDEVS; i++)
		अगर (viafb_subdevs[i].platdev) अणु
			viafb_subdevs[i].platdev->dev.platक्रमm_data = शून्य;
			platक्रमm_device_unरेजिस्टर(viafb_subdevs[i].platdev);
		पूर्ण
पूर्ण

/*
 * Power management functions
 */
अटल __maybe_unused LIST_HEAD(viafb_pm_hooks);
अटल __maybe_unused DEFINE_MUTEX(viafb_pm_hooks_lock);

व्योम viafb_pm_रेजिस्टर(काष्ठा viafb_pm_hooks *hooks)
अणु
	INIT_LIST_HEAD(&hooks->list);

	mutex_lock(&viafb_pm_hooks_lock);
	list_add_tail(&hooks->list, &viafb_pm_hooks);
	mutex_unlock(&viafb_pm_hooks_lock);
पूर्ण
EXPORT_SYMBOL_GPL(viafb_pm_रेजिस्टर);

व्योम viafb_pm_unरेजिस्टर(काष्ठा viafb_pm_hooks *hooks)
अणु
	mutex_lock(&viafb_pm_hooks_lock);
	list_del(&hooks->list);
	mutex_unlock(&viafb_pm_hooks_lock);
पूर्ण
EXPORT_SYMBOL_GPL(viafb_pm_unरेजिस्टर);

अटल पूर्णांक __maybe_unused via_suspend(काष्ठा device *dev)
अणु
	काष्ठा viafb_pm_hooks *hooks;

	/*
	 * "I've occasionally hit a few drivers that caused suspend
	 * failures, and each and every समय it was a driver bug, and
	 * the right thing to करो was to just ignore the error and suspend
	 * anyway - वापसing an error code and trying to unकरो the suspend
	 * is not what anybody ever really wants, even अगर our model
	 *_allows_ क्रम it."
	 * -- Linus Torvalds, Dec. 7, 2009
	 */
	mutex_lock(&viafb_pm_hooks_lock);
	list_क्रम_each_entry_reverse(hooks, &viafb_pm_hooks, list)
		hooks->suspend(hooks->निजी);
	mutex_unlock(&viafb_pm_hooks_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused via_resume(काष्ठा device *dev)
अणु
	काष्ठा viafb_pm_hooks *hooks;

	/* Now bring back any subdevs */
	mutex_lock(&viafb_pm_hooks_lock);
	list_क्रम_each_entry(hooks, &viafb_pm_hooks, list)
		hooks->resume(hooks->निजी);
	mutex_unlock(&viafb_pm_hooks_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक via_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	/*
	 * Global device initialization.
	 */
	स_रखो(&global_dev, 0, माप(global_dev));
	global_dev.pdev = pdev;
	global_dev.chip_type = ent->driver_data;
	global_dev.port_cfg = adap_configs;
	अगर (machine_is_olpc())
		global_dev.port_cfg = olpc_adap_configs;

	spin_lock_init(&global_dev.reg_lock);
	ret = via_pci_setup_mmio(&global_dev);
	अगर (ret)
		जाओ out_disable;
	/*
	 * Set up पूर्णांकerrupts and create our subdevices.  Continue even अगर
	 * some things fail.
	 */
	viafb_पूर्णांक_init();
	via_setup_subdevs(&global_dev);
	/*
	 * Set up the framebuffer device
	 */
	ret = via_fb_pci_probe(&global_dev);
	अगर (ret)
		जाओ out_subdevs;
	वापस 0;

out_subdevs:
	via_tearकरोwn_subdevs();
	via_pci_tearकरोwn_mmio(&global_dev);
out_disable:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम via_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	via_tearकरोwn_subdevs();
	via_fb_pci_हटाओ(pdev);
	via_pci_tearकरोwn_mmio(&global_dev);
	pci_disable_device(pdev);
पूर्ण


अटल स्थिर काष्ठा pci_device_id via_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_CLE266_DID),
	  .driver_data = UNICHROME_CLE266 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_K400_DID),
	  .driver_data = UNICHROME_K400 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_K800_DID),
	  .driver_data = UNICHROME_K800 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_PM800_DID),
	  .driver_data = UNICHROME_PM800 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_CN700_DID),
	  .driver_data = UNICHROME_CN700 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_CX700_DID),
	  .driver_data = UNICHROME_CX700 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_CN750_DID),
	  .driver_data = UNICHROME_CN750 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_K8M890_DID),
	  .driver_data = UNICHROME_K8M890 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_P4M890_DID),
	  .driver_data = UNICHROME_P4M890 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_P4M900_DID),
	  .driver_data = UNICHROME_P4M900 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_VX800_DID),
	  .driver_data = UNICHROME_VX800 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_VX855_DID),
	  .driver_data = UNICHROME_VX855 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, UNICHROME_VX900_DID),
	  .driver_data = UNICHROME_VX900 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, via_pci_table);

अटल स्थिर काष्ठा dev_pm_ops via_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= via_suspend,
	.resume		= via_resume,
	.मुक्तze		= शून्य,
	.thaw		= via_resume,
	.घातeroff	= शून्य,
	.restore	= via_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pci_driver via_driver = अणु
	.name		= "viafb",
	.id_table	= via_pci_table,
	.probe		= via_pci_probe,
	.हटाओ		= via_pci_हटाओ,
	.driver.pm	= &via_pm_ops,
पूर्ण;

अटल पूर्णांक __init via_core_init(व्योम)
अणु
	पूर्णांक ret;

	ret = viafb_init();
	अगर (ret)
		वापस ret;
	viafb_i2c_init();
	viafb_gpio_init();
	वापस pci_रेजिस्टर_driver(&via_driver);
पूर्ण

अटल व्योम __निकास via_core_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&via_driver);
	viafb_gpio_निकास();
	viafb_i2c_निकास();
	viafb_निकास();
पूर्ण

module_init(via_core_init);
module_निकास(via_core_निकास);
