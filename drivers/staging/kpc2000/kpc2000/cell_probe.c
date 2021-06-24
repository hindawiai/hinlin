<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/uio_driver.h>
#समावेश "pcie.h"

/*  Core (Resource) Table Layout:
 *      one Resource per record (8 bytes)
 *                 6         5         4         3         2         1         0
 *              3210987654321098765432109876543210987654321098765432109876543210
 *              IIIIIIIIIIII                                                        Core Type    [up to 4095 types]
 *                          D                                                       S2C DMA Present
 *                           DDD                                                    S2C DMA Channel Number    [up to 8 channels]
 *                              LLLLLLLLLLLLLLLL                                    Register Count (64-bit रेजिस्टरs)    [up to 65535 रेजिस्टरs]
 *                                              OOOOOOOOOOOOOOOO                    Core Offset (in 4kB blocks)    [up to 65535 cores]
 *                                                              D                   C2S DMA Present
 *                                                               DDD                C2S DMA Channel Number    [up to 8 channels]
 *                                                                  II              IRQ Count [0 to 3 IRQs per core]
 *                                                                    1111111000
 *                                                                    IIIIIII       IRQ Base Number [up to 128 IRQs per card]
 *                                                                           ___    Spare
 *
 */

#घोषणा KPC_OLD_DMA_CH_NUM(present, channel)   \
		((present) ? (0x8 | ((channel) & 0x7)) : 0)
#घोषणा KPC_OLD_S2C_DMA_CH_NUM(cte)   \
		KPC_OLD_DMA_CH_NUM(cte.s2c_dma_present, cte.s2c_dma_channel_num)
#घोषणा KPC_OLD_C2S_DMA_CH_NUM(cte)   \
		KPC_OLD_DMA_CH_NUM(cte.c2s_dma_present, cte.c2s_dma_channel_num)

#घोषणा KP_CORE_ID_INVALID      0
#घोषणा KP_CORE_ID_I2C          3
#घोषणा KP_CORE_ID_SPI          5

काष्ठा core_table_entry अणु
	u16  type;
	u32  offset;
	u32  length;
	bool s2c_dma_present;
	u8   s2c_dma_channel_num;
	bool c2s_dma_present;
	u8   c2s_dma_channel_num;
	u8   irq_count;
	u8   irq_base_num;
पूर्ण;

अटल
व्योम  parse_core_table_entry_v0(काष्ठा core_table_entry *cte, स्थिर u64 पढ़ो_val)
अणु
	cte->type                = ((पढ़ो_val & 0xFFF0000000000000UL) >> 52);
	cte->offset              = ((पढ़ो_val & 0x00000000FFFF0000UL) >> 16) * 4096;
	cte->length              = ((पढ़ो_val & 0x0000FFFF00000000UL) >> 32) * 8;
	cte->s2c_dma_present     = ((पढ़ो_val & 0x0008000000000000UL) >> 51);
	cte->s2c_dma_channel_num = ((पढ़ो_val & 0x0007000000000000UL) >> 48);
	cte->c2s_dma_present     = ((पढ़ो_val & 0x0000000000008000UL) >> 15);
	cte->c2s_dma_channel_num = ((पढ़ो_val & 0x0000000000007000UL) >> 12);
	cte->irq_count           = ((पढ़ो_val & 0x0000000000000C00UL) >> 10);
	cte->irq_base_num        = ((पढ़ो_val & 0x00000000000003F8UL) >>  3);
पूर्ण

अटल
व्योम dbg_cte(काष्ठा kp2000_device *pcard, काष्ठा core_table_entry *cte)
अणु
	dev_dbg(&pcard->pdev->dev,
		"CTE: type:%3d  offset:%3d (%3d)  length:%3d (%3d)  s2c:%d  c2s:%d  irq_count:%d  base_irq:%d\n",
		cte->type,
		cte->offset,
		cte->offset / 4096,
		cte->length,
		cte->length / 8,
		(cte->s2c_dma_present ? cte->s2c_dma_channel_num : -1),
		(cte->c2s_dma_present ? cte->c2s_dma_channel_num : -1),
		cte->irq_count,
		cte->irq_base_num
	);
पूर्ण

अटल
व्योम parse_core_table_entry(काष्ठा core_table_entry *cte, स्थिर u64 पढ़ो_val, स्थिर u8 entry_rev)
अणु
	चयन (entry_rev) अणु
	हाल 0:
		parse_core_table_entry_v0(cte, पढ़ो_val);
		अवरोध;
	शेष:
		cte->type = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक probe_core_basic(अचिन्हित पूर्णांक core_num, काष्ठा kp2000_device *pcard,
			    अक्षर *name, स्थिर काष्ठा core_table_entry cte)
अणु
	काष्ठा mfd_cell  cell = अणु .id = core_num, .name = name पूर्ण;
	काष्ठा resource resources[2];

	काष्ठा kpc_core_device_platdata core_pdata = अणु
		.card_id           = pcard->card_id,
		.build_version     = pcard->build_version,
		.hardware_revision = pcard->hardware_revision,
		.ssid              = pcard->ssid,
		.ddna              = pcard->ddna,
	पूर्ण;

	dev_dbg(&pcard->pdev->dev,
		"Found Basic core: type = %02d  dma = %02x / %02x  offset = 0x%x  length = 0x%x (%d regs)\n",
		cte.type,
		KPC_OLD_S2C_DMA_CH_NUM(cte),
		KPC_OLD_C2S_DMA_CH_NUM(cte),
		cte.offset,
		cte.length,
		cte.length / 8);

	cell.platक्रमm_data = &core_pdata;
	cell.pdata_size = माप(काष्ठा kpc_core_device_platdata);
	cell.num_resources = 2;

	स_रखो(&resources, 0, माप(resources));

	resources[0].start = cte.offset;
	resources[0].end   = cte.offset + (cte.length - 1);
	resources[0].flags = IORESOURCE_MEM;

	resources[1].start = pcard->pdev->irq;
	resources[1].end   = pcard->pdev->irq;
	resources[1].flags = IORESOURCE_IRQ;

	cell.resources = resources;

	वापस mfd_add_devices(PCARD_TO_DEV(pcard),    // parent
			       pcard->card_num * 100,  // id
			       &cell,                  // काष्ठा mfd_cell *
			       1,                      // ndevs
			       &pcard->regs_base_resource,
			       0,                      // irq_base
			       शून्य);                  // काष्ठा irq_करोमुख्य *
पूर्ण

काष्ठा kpc_uio_device अणु
	काष्ठा list_head list;
	काष्ठा kp2000_device *pcard;
	काष्ठा device  *dev;
	काष्ठा uio_info uioinfo;
	काष्ठा core_table_entry cte;
	u16 core_num;
पूर्ण;

अटल sमाप_प्रकार offset_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.offset);
पूर्ण
अटल DEVICE_ATTR_RO(offset);

अटल sमाप_प्रकार size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.length);
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार s2c_dma_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	अगर (!kudev->cte.s2c_dma_present)
		वापस प्र_लिखो(buf, "%s", "not present\n");

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.s2c_dma_channel_num);
पूर्ण
अटल DEVICE_ATTR_RO(s2c_dma);

अटल sमाप_प्रकार c2s_dma_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	अगर (!kudev->cte.c2s_dma_present)
		वापस प्र_लिखो(buf, "%s", "not present\n");

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.c2s_dma_channel_num);
पूर्ण
अटल DEVICE_ATTR_RO(c2s_dma);

अटल sमाप_प्रकार irq_count_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.irq_count);
पूर्ण
अटल DEVICE_ATTR_RO(irq_count);

अटल sमाप_प्रकार irq_base_num_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->cte.irq_base_num);
पूर्ण
अटल DEVICE_ATTR_RO(irq_base_num);

अटल sमाप_प्रकार core_num_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा kpc_uio_device *kudev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", kudev->core_num);
पूर्ण
अटल DEVICE_ATTR_RO(core_num);

काष्ठा attribute *kpc_uio_class_attrs[] = अणु
	&dev_attr_offset.attr,
	&dev_attr_size.attr,
	&dev_attr_type.attr,
	&dev_attr_s2c_dma.attr,
	&dev_attr_c2s_dma.attr,
	&dev_attr_irq_count.attr,
	&dev_attr_irq_base_num.attr,
	&dev_attr_core_num.attr,
	शून्य,
पूर्ण;

अटल
पूर्णांक  kp2000_check_uio_irq(काष्ठा kp2000_device *pcard, u32 irq_num)
अणु
	u64 पूर्णांकerrupt_active   =  पढ़ोq(pcard->sysinfo_regs_base + REG_INTERRUPT_ACTIVE);
	u64 पूर्णांकerrupt_mask_inv = ~पढ़ोq(pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	u64 irq_check_mask = BIT_ULL(irq_num);

	अगर (पूर्णांकerrupt_active & irq_check_mask) अणु // अगर it's active (पूर्णांकerrupt pending)
		अगर (पूर्णांकerrupt_mask_inv & irq_check_mask) अणु    // and अगर it's not masked off
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल
irqवापस_t  kuio_handler(पूर्णांक irq, काष्ठा uio_info *uioinfo)
अणु
	काष्ठा kpc_uio_device *kudev = uioinfo->priv;

	अगर (irq != kudev->pcard->pdev->irq)
		वापस IRQ_NONE;

	अगर (kp2000_check_uio_irq(kudev->pcard, kudev->cte.irq_base_num)) अणु
		/* Clear the active flag */
		ग_लिखोq(BIT_ULL(kudev->cte.irq_base_num),
		       kudev->pcard->sysinfo_regs_base + REG_INTERRUPT_ACTIVE);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल
पूर्णांक kuio_irqcontrol(काष्ठा uio_info *uioinfo, s32 irq_on)
अणु
	काष्ठा kpc_uio_device *kudev = uioinfo->priv;
	काष्ठा kp2000_device *pcard = kudev->pcard;
	u64 mask;

	mutex_lock(&pcard->sem);
	mask = पढ़ोq(pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	अगर (irq_on)
		mask &= ~(BIT_ULL(kudev->cte.irq_base_num));
	अन्यथा
		mask |= BIT_ULL(kudev->cte.irq_base_num);
	ग_लिखोq(mask, pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	mutex_unlock(&pcard->sem);

	वापस 0;
पूर्ण

अटल पूर्णांक probe_core_uio(अचिन्हित पूर्णांक core_num, काष्ठा kp2000_device *pcard,
			  अक्षर *name, स्थिर काष्ठा core_table_entry cte)
अणु
	काष्ठा kpc_uio_device *kudev;
	पूर्णांक rv;

	dev_dbg(&pcard->pdev->dev,
		"Found UIO core:   type = %02d  dma = %02x / %02x  offset = 0x%x  length = 0x%x (%d regs)\n",
		cte.type,
		KPC_OLD_S2C_DMA_CH_NUM(cte),
		KPC_OLD_C2S_DMA_CH_NUM(cte),
		cte.offset,
		cte.length,
		cte.length / 8);

	kudev = kzalloc(माप(*kudev), GFP_KERNEL);
	अगर (!kudev)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&kudev->list);
	kudev->pcard = pcard;
	kudev->cte = cte;
	kudev->core_num = core_num;

	kudev->uioinfo.priv = kudev;
	kudev->uioinfo.name = name;
	kudev->uioinfo.version = "0.0";
	अगर (cte.irq_count > 0) अणु
		kudev->uioinfo.irq_flags = IRQF_SHARED;
		kudev->uioinfo.irq = pcard->pdev->irq;
		kudev->uioinfo.handler = kuio_handler;
		kudev->uioinfo.irqcontrol = kuio_irqcontrol;
	पूर्ण अन्यथा अणु
		kudev->uioinfo.irq = 0;
	पूर्ण

	kudev->uioinfo.mem[0].name = "uiomap";
	kudev->uioinfo.mem[0].addr = pci_resource_start(pcard->pdev, REG_BAR) + cte.offset;

	// Round up to nearest PAGE_SIZE boundary
	kudev->uioinfo.mem[0].size = (cte.length + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	kudev->uioinfo.mem[0].memtype = UIO_MEM_PHYS;

	kudev->dev = device_create(kpc_uio_class,
				   &pcard->pdev->dev, MKDEV(0, 0), kudev, "%s.%d.%d.%d",
				   kudev->uioinfo.name, pcard->card_num, cte.type, kudev->core_num);
	अगर (IS_ERR(kudev->dev)) अणु
		dev_err(&pcard->pdev->dev, "%s: device_create failed!\n",
			__func__);
		kमुक्त(kudev);
		वापस -ENODEV;
	पूर्ण
	dev_set_drvdata(kudev->dev, kudev);

	rv = uio_रेजिस्टर_device(kudev->dev, &kudev->uioinfo);
	अगर (rv) अणु
		dev_err(&pcard->pdev->dev, "%s: failed uio_register_device: %d\n",
			__func__, rv);
		put_device(kudev->dev);
		kमुक्त(kudev);
		वापस rv;
	पूर्ण

	list_add_tail(&kudev->list, &pcard->uio_devices_list);

	वापस 0;
पूर्ण

अटल पूर्णांक  create_dma_engine_core(काष्ठा kp2000_device *pcard,
				   माप_प्रकार engine_regs_offset,
				   पूर्णांक engine_num, पूर्णांक irq_num)
अणु
	काष्ठा mfd_cell  cell = अणु .id = engine_num पूर्ण;
	काष्ठा resource  resources[2];

	cell.platक्रमm_data = शून्य;
	cell.pdata_size = 0;
	cell.name = KP_DRIVER_NAME_DMA_CONTROLLER;
	cell.num_resources = 2;

	स_रखो(&resources, 0, माप(resources));

	resources[0].start = engine_regs_offset;
	resources[0].end   = engine_regs_offset + (KPC_DMA_ENGINE_SIZE - 1);
	resources[0].flags = IORESOURCE_MEM;

	resources[1].start = irq_num;
	resources[1].end   = irq_num;
	resources[1].flags = IORESOURCE_IRQ;

	cell.resources = resources;

	वापस mfd_add_devices(PCARD_TO_DEV(pcard),    // parent
			       pcard->card_num * 100,  // id
			       &cell,                  // काष्ठा mfd_cell *
			       1,                      // ndevs
			       &pcard->dma_base_resource,
			       0,                      // irq_base
			       शून्य);                  // काष्ठा irq_करोमुख्य *
पूर्ण

अटल पूर्णांक  kp2000_setup_dma_controller(काष्ठा kp2000_device *pcard)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	u64 capabilities_reg;

	// S2C Engines
	क्रम (i = 0 ; i < 32 ; i++) अणु
		capabilities_reg = पढ़ोq(pcard->dma_bar_base +
					 KPC_DMA_S2C_BASE_OFFSET +
					 (KPC_DMA_ENGINE_SIZE * i));

		अगर (capabilities_reg & ENGINE_CAP_PRESENT_MASK) अणु
			err = create_dma_engine_core(pcard, (KPC_DMA_S2C_BASE_OFFSET +
							    (KPC_DMA_ENGINE_SIZE * i)),
						     i, pcard->pdev->irq);
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण
	// C2S Engines
	क्रम (i = 0 ; i < 32 ; i++) अणु
		capabilities_reg = पढ़ोq(pcard->dma_bar_base +
					 KPC_DMA_C2S_BASE_OFFSET +
					 (KPC_DMA_ENGINE_SIZE * i));

		अगर (capabilities_reg & ENGINE_CAP_PRESENT_MASK) अणु
			err = create_dma_engine_core(pcard, (KPC_DMA_C2S_BASE_OFFSET +
							    (KPC_DMA_ENGINE_SIZE * i)),
						     32 + i,  pcard->pdev->irq);
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	dev_err(&pcard->pdev->dev, "%s: failed to add a DMA Engine: %d\n",
		__func__, err);
	वापस err;
पूर्ण

पूर्णांक  kp2000_probe_cores(काष्ठा kp2000_device *pcard)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;
	पूर्णांक current_type_id;
	u64 पढ़ो_val;
	अचिन्हित पूर्णांक highest_core_id = 0;
	काष्ठा core_table_entry cte;

	err = kp2000_setup_dma_controller(pcard);
	अगर (err)
		वापस err;

	INIT_LIST_HEAD(&pcard->uio_devices_list);

	// First, iterate the core table looking क्रम the highest CORE_ID
	क्रम (i = 0 ; i < pcard->core_table_length ; i++) अणु
		पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + ((pcard->core_table_offset + i) * 8));
		parse_core_table_entry(&cte, पढ़ो_val, pcard->core_table_rev);
		dbg_cte(pcard, &cte);
		अगर (cte.type > highest_core_id)
			highest_core_id = cte.type;
		अगर (cte.type == KP_CORE_ID_INVALID)
			dev_info(&pcard->pdev->dev, "Found Invalid core: %016llx\n", पढ़ो_val);
	पूर्ण
	// Then, iterate over the possible core types.
	क्रम (current_type_id = 1 ; current_type_id <= highest_core_id ; current_type_id++) अणु
		अचिन्हित पूर्णांक core_num = 0;
		/*
		 * Foreach core type, iterate the whole table and instantiate
		 * subdevices क्रम each core.
		 * Yes, this is O(n*m) but the actual runसमय is small enough
		 * that it's an acceptable tradeoff.
		 */
		क्रम (i = 0 ; i < pcard->core_table_length ; i++) अणु
			पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base +
					 ((pcard->core_table_offset + i) * 8));
			parse_core_table_entry(&cte, पढ़ो_val, pcard->core_table_rev);

			अगर (cte.type != current_type_id)
				जारी;

			चयन (cte.type) अणु
			हाल KP_CORE_ID_I2C:
				err = probe_core_basic(core_num, pcard,
						       KP_DRIVER_NAME_I2C, cte);
				अवरोध;

			हाल KP_CORE_ID_SPI:
				err = probe_core_basic(core_num, pcard,
						       KP_DRIVER_NAME_SPI, cte);
				अवरोध;

			शेष:
				err = probe_core_uio(core_num, pcard, "kpc_uio", cte);
				अवरोध;
			पूर्ण
			अगर (err) अणु
				dev_err(&pcard->pdev->dev,
					"%s: failed to add core %d: %d\n",
					__func__, i, err);
				जाओ error;
			पूर्ण
			core_num++;
		पूर्ण
	पूर्ण

	// Finally, instantiate a UIO device क्रम the core_table.
	cte.type                = 0; // CORE_ID_BOARD_INFO
	cte.offset              = 0; // board info is always at the beginning
	cte.length              = 512 * 8;
	cte.s2c_dma_present     = false;
	cte.s2c_dma_channel_num = 0;
	cte.c2s_dma_present     = false;
	cte.c2s_dma_channel_num = 0;
	cte.irq_count           = 0;
	cte.irq_base_num        = 0;
	err = probe_core_uio(0, pcard, "kpc_uio", cte);
	अगर (err) अणु
		dev_err(&pcard->pdev->dev, "%s: failed to add board_info core: %d\n",
			__func__, err);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	kp2000_हटाओ_cores(pcard);
	mfd_हटाओ_devices(PCARD_TO_DEV(pcard));
	वापस err;
पूर्ण

व्योम  kp2000_हटाओ_cores(काष्ठा kp2000_device *pcard)
अणु
	काष्ठा list_head *ptr;
	काष्ठा list_head *next;

	list_क्रम_each_safe(ptr, next, &pcard->uio_devices_list) अणु
		काष्ठा kpc_uio_device *kudev = list_entry(ptr, काष्ठा kpc_uio_device, list);

		uio_unरेजिस्टर_device(&kudev->uioinfo);
		device_unरेजिस्टर(kudev->dev);
		list_del(&kudev->list);
		kमुक्त(kudev);
	पूर्ण
पूर्ण

