<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STA2x11 mfd क्रम GPIO, SCTL and APBREG
 *
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 * Copyright (c) 2011 ST Microelectronics (Alessandro Rubini, Davide Ciminaghi)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/sta2x11-mfd.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/sta2x11.h>

अटल अंतरभूत पूर्णांक __reg_within_range(अचिन्हित पूर्णांक r,
				     अचिन्हित पूर्णांक start,
				     अचिन्हित पूर्णांक end)
अणु
	वापस ((r >= start) && (r <= end));
पूर्ण

/* This describes STA2X11 MFD chip क्रम us, we may have several */
काष्ठा sta2x11_mfd अणु
	काष्ठा sta2x11_instance *instance;
	काष्ठा regmap *regmap[sta2x11_n_mfd_plat_devs];
	spinlock_t lock[sta2x11_n_mfd_plat_devs];
	काष्ठा list_head list;
	व्योम __iomem *regs[sta2x11_n_mfd_plat_devs];
पूर्ण;

अटल LIST_HEAD(sta2x11_mfd_list);

/* Three functions to act on the list */
अटल काष्ठा sta2x11_mfd *sta2x11_mfd_find(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance;
	काष्ठा sta2x11_mfd *mfd;

	अगर (!pdev && !list_empty(&sta2x11_mfd_list)) अणु
		pr_warn("%s: Unspecified device, using first instance\n",
			__func__);
		वापस list_entry(sta2x11_mfd_list.next,
				  काष्ठा sta2x11_mfd, list);
	पूर्ण

	instance = sta2x11_get_instance(pdev);
	अगर (!instance)
		वापस शून्य;
	list_क्रम_each_entry(mfd, &sta2x11_mfd_list, list) अणु
		अगर (mfd->instance == instance)
			वापस mfd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक sta2x11_mfd_add(काष्ठा pci_dev *pdev, gfp_t flags)
अणु
	पूर्णांक i;
	काष्ठा sta2x11_mfd *mfd = sta2x11_mfd_find(pdev);
	काष्ठा sta2x11_instance *instance;

	अगर (mfd)
		वापस -EBUSY;
	instance = sta2x11_get_instance(pdev);
	अगर (!instance)
		वापस -EINVAL;
	mfd = kzalloc(माप(*mfd), flags);
	अगर (!mfd)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&mfd->list);
	क्रम (i = 0; i < ARRAY_SIZE(mfd->lock); i++)
		spin_lock_init(&mfd->lock[i]);
	mfd->instance = instance;
	list_add(&mfd->list, &sta2x11_mfd_list);
	वापस 0;
पूर्ण

/* This function is exported and is not expected to fail */
u32 __sta2x11_mfd_mask(काष्ठा pci_dev *pdev, u32 reg, u32 mask, u32 val,
		       क्रमागत sta2x11_mfd_plat_dev index)
अणु
	काष्ठा sta2x11_mfd *mfd = sta2x11_mfd_find(pdev);
	u32 r;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *regs;

	अगर (!mfd) अणु
		dev_warn(&pdev->dev, ": can't access sctl regs\n");
		वापस 0;
	पूर्ण

	regs = mfd->regs[index];
	अगर (!regs) अणु
		dev_warn(&pdev->dev, ": system ctl not initialized\n");
		वापस 0;
	पूर्ण
	spin_lock_irqsave(&mfd->lock[index], flags);
	r = पढ़ोl(regs + reg);
	r &= ~mask;
	r |= val;
	अगर (mask)
		ग_लिखोl(r, regs + reg);
	spin_unlock_irqrestore(&mfd->lock[index], flags);
	वापस r;
पूर्ण
EXPORT_SYMBOL(__sta2x11_mfd_mask);

पूर्णांक sta2x11_mfd_get_regs_data(काष्ठा platक्रमm_device *dev,
			      क्रमागत sta2x11_mfd_plat_dev index,
			      व्योम __iomem **regs,
			      spinlock_t **lock)
अणु
	काष्ठा pci_dev *pdev = *(काष्ठा pci_dev **)dev_get_platdata(&dev->dev);
	काष्ठा sta2x11_mfd *mfd;

	अगर (!pdev)
		वापस -ENODEV;
	mfd = sta2x11_mfd_find(pdev);
	अगर (!mfd)
		वापस -ENODEV;
	अगर (index >= sta2x11_n_mfd_plat_devs)
		वापस -ENODEV;
	*regs = mfd->regs[index];
	*lock = &mfd->lock[index];
	pr_debug("%s %d *regs = %p\n", __func__, __LINE__, *regs);
	वापस *regs ? 0 : -ENODEV;
पूर्ण
EXPORT_SYMBOL(sta2x11_mfd_get_regs_data);

/*
 * Special sta2x11-mfd regmap lock/unlock functions
 */

अटल व्योम sta2x11_regmap_lock(व्योम *__lock)
अणु
	spinlock_t *lock = __lock;
	spin_lock(lock);
पूर्ण

अटल व्योम sta2x11_regmap_unlock(व्योम *__lock)
अणु
	spinlock_t *lock = __lock;
	spin_unlock(lock);
पूर्ण

/* OTP (one समय programmable रेजिस्टरs करो not require locking */
अटल व्योम sta2x11_regmap_nolock(व्योम *__lock)
अणु
पूर्ण

अटल स्थिर अक्षर *sta2x11_mfd_names[sta2x11_n_mfd_plat_devs] = अणु
	[sta2x11_sctl] = STA2X11_MFD_SCTL_NAME,
	[sta2x11_apbreg] = STA2X11_MFD_APBREG_NAME,
	[sta2x11_apb_soc_regs] = STA2X11_MFD_APB_SOC_REGS_NAME,
	[sta2x11_scr] = STA2X11_MFD_SCR_NAME,
पूर्ण;

अटल bool sta2x11_sctl_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस !__reg_within_range(reg, SCTL_SCPCIECSBRST, SCTL_SCRSTSTA);
पूर्ण

अटल काष्ठा regmap_config sta2x11_sctl_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.lock = sta2x11_regmap_lock,
	.unlock = sta2x11_regmap_unlock,
	.max_रेजिस्टर = SCTL_SCRSTSTA,
	.ग_लिखोable_reg = sta2x11_sctl_ग_लिखोable_reg,
पूर्ण;

अटल bool sta2x11_scr_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == STA2X11_SECR_CR) ||
		__reg_within_range(reg, STA2X11_SECR_FVR0, STA2X11_SECR_FVR1);
पूर्ण

अटल bool sta2x11_scr_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल काष्ठा regmap_config sta2x11_scr_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.lock = sta2x11_regmap_nolock,
	.unlock = sta2x11_regmap_nolock,
	.max_रेजिस्टर = STA2X11_SECR_FVR1,
	.पढ़ोable_reg = sta2x11_scr_पढ़ोable_reg,
	.ग_लिखोable_reg = sta2x11_scr_ग_लिखोable_reg,
पूर्ण;

अटल bool sta2x11_apbreg_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Two blocks (CAN and MLB, SARAC) 0x100 bytes apart */
	अगर (reg >= APBREG_BSR_SARAC)
		reg -= APBREG_BSR_SARAC;
	चयन (reg) अणु
	हाल APBREG_BSR:
	हाल APBREG_PAER:
	हाल APBREG_PWAC:
	हाल APBREG_PRAC:
	हाल APBREG_PCG:
	हाल APBREG_PUR:
	हाल APBREG_EMU_PCG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sta2x11_apbreg_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg >= APBREG_BSR_SARAC)
		reg -= APBREG_BSR_SARAC;
	अगर (!sta2x11_apbreg_पढ़ोable_reg(dev, reg))
		वापस false;
	वापस reg != APBREG_PAER;
पूर्ण

अटल काष्ठा regmap_config sta2x11_apbreg_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.lock = sta2x11_regmap_lock,
	.unlock = sta2x11_regmap_unlock,
	.max_रेजिस्टर = APBREG_EMU_PCG_SARAC,
	.पढ़ोable_reg = sta2x11_apbreg_पढ़ोable_reg,
	.ग_लिखोable_reg = sta2x11_apbreg_ग_लिखोable_reg,
पूर्ण;

अटल bool sta2x11_apb_soc_regs_पढ़ोable_reg(काष्ठा device *dev,
					      अचिन्हित पूर्णांक reg)
अणु
	वापस reg <= PCIE_SoC_INT_ROUTER_STATUS3_REG ||
		__reg_within_range(reg, DMA_IP_CTRL_REG, SPARE3_RESERVED) ||
		__reg_within_range(reg, MASTER_LOCK_REG,
				   SYSTEM_CONFIG_STATUS_REG) ||
		reg == MSP_CLK_CTRL_REG ||
		__reg_within_range(reg, COMPENSATION_REG1, TEST_CTL_REG);
पूर्ण

अटल bool sta2x11_apb_soc_regs_ग_लिखोable_reg(काष्ठा device *dev,
					       अचिन्हित पूर्णांक reg)
अणु
	अगर (!sta2x11_apb_soc_regs_पढ़ोable_reg(dev, reg))
		वापस false;
	चयन (reg) अणु
	हाल PCIE_COMMON_CLOCK_CONFIG_0_4_0:
	हाल SYSTEM_CONFIG_STATUS_REG:
	हाल COMPENSATION_REG1:
	हाल PCIE_SoC_INT_ROUTER_STATUS0_REG...PCIE_SoC_INT_ROUTER_STATUS3_REG:
	हाल PCIE_PM_STATUS_0_PORT_0_4...PCIE_PM_STATUS_7_0_EP4:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल काष्ठा regmap_config sta2x11_apb_soc_regs_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.lock = sta2x11_regmap_lock,
	.unlock = sta2x11_regmap_unlock,
	.max_रेजिस्टर = TEST_CTL_REG,
	.पढ़ोable_reg = sta2x11_apb_soc_regs_पढ़ोable_reg,
	.ग_लिखोable_reg = sta2x11_apb_soc_regs_ग_लिखोable_reg,
पूर्ण;

अटल काष्ठा regmap_config *
sta2x11_mfd_regmap_configs[sta2x11_n_mfd_plat_devs] = अणु
	[sta2x11_sctl] = &sta2x11_sctl_regmap_config,
	[sta2x11_apbreg] = &sta2x11_apbreg_regmap_config,
	[sta2x11_apb_soc_regs] = &sta2x11_apb_soc_regs_regmap_config,
	[sta2x11_scr] = &sta2x11_scr_regmap_config,
पूर्ण;

/* Probe क्रम the four platक्रमm devices */

अटल पूर्णांक sta2x11_mfd_platक्रमm_probe(काष्ठा platक्रमm_device *dev,
				      क्रमागत sta2x11_mfd_plat_dev index)
अणु
	काष्ठा pci_dev **pdev;
	काष्ठा sta2x11_mfd *mfd;
	काष्ठा resource *res;
	स्थिर अक्षर *name = sta2x11_mfd_names[index];
	काष्ठा regmap_config *regmap_config = sta2x11_mfd_regmap_configs[index];

	pdev = dev_get_platdata(&dev->dev);
	mfd = sta2x11_mfd_find(*pdev);
	अगर (!mfd)
		वापस -ENODEV;
	अगर (!regmap_config)
		वापस -ENODEV;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOMEM;

	अगर (!request_mem_region(res->start, resource_size(res), name))
		वापस -EBUSY;

	mfd->regs[index] = ioremap(res->start, resource_size(res));
	अगर (!mfd->regs[index]) अणु
		release_mem_region(res->start, resource_size(res));
		वापस -ENOMEM;
	पूर्ण
	regmap_config->lock_arg = &mfd->lock;
	/*
	   No caching, रेजिस्टरs could be reached both via regmap and via
	   व्योम __iomem *
	*/
	regmap_config->cache_type = REGCACHE_NONE;
	mfd->regmap[index] = devm_regmap_init_mmio(&dev->dev, mfd->regs[index],
						   regmap_config);
	WARN_ON(IS_ERR(mfd->regmap[index]));

	वापस 0;
पूर्ण

अटल पूर्णांक sta2x11_sctl_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस sta2x11_mfd_platक्रमm_probe(dev, sta2x11_sctl);
पूर्ण

अटल पूर्णांक sta2x11_apbreg_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस sta2x11_mfd_platक्रमm_probe(dev, sta2x11_apbreg);
पूर्ण

अटल पूर्णांक sta2x11_apb_soc_regs_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस sta2x11_mfd_platक्रमm_probe(dev, sta2x11_apb_soc_regs);
पूर्ण

अटल पूर्णांक sta2x11_scr_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस sta2x11_mfd_platक्रमm_probe(dev, sta2x11_scr);
पूर्ण

/* The three platक्रमm drivers */
अटल काष्ठा platक्रमm_driver sta2x11_sctl_platक्रमm_driver = अणु
	.driver = अणु
		.name	= STA2X11_MFD_SCTL_NAME,
	पूर्ण,
	.probe		= sta2x11_sctl_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver sta2x11_platक्रमm_driver = अणु
	.driver = अणु
		.name	= STA2X11_MFD_APBREG_NAME,
	पूर्ण,
	.probe		= sta2x11_apbreg_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver sta2x11_apb_soc_regs_platक्रमm_driver = अणु
	.driver = अणु
		.name	= STA2X11_MFD_APB_SOC_REGS_NAME,
	पूर्ण,
	.probe		= sta2x11_apb_soc_regs_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver sta2x11_scr_platक्रमm_driver = अणु
	.driver = अणु
		.name = STA2X11_MFD_SCR_NAME,
	पूर्ण,
	.probe = sta2x11_scr_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&sta2x11_platक्रमm_driver,
	&sta2x11_sctl_platक्रमm_driver,
	&sta2x11_apb_soc_regs_platक्रमm_driver,
	&sta2x11_scr_platक्रमm_driver,
पूर्ण;

अटल पूर्णांक __init sta2x11_drivers_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

/*
 * What follows are the PCI devices that host the above pdevs.
 * Each logic block is 4kB and they are all consecutive: we use this info.
 */

/* Mfd 0 device */

/* Mfd 0, Bar 0 */
क्रमागत mfd0_bar0_cells अणु
	STA2X11_GPIO_0 = 0,
	STA2X11_GPIO_1,
	STA2X11_GPIO_2,
	STA2X11_GPIO_3,
	STA2X11_SCTL,
	STA2X11_SCR,
	STA2X11_TIME,
पूर्ण;
/* Mfd 0 , Bar 1 */
क्रमागत mfd0_bar1_cells अणु
	STA2X11_APBREG = 0,
पूर्ण;
#घोषणा CELL_4K(_name, _cell) अणु \
		.name = _name, \
		.start = _cell * 4096, .end = _cell * 4096 + 4095, \
		.flags = IORESOURCE_MEM, \
		पूर्ण

अटल स्थिर काष्ठा resource gpio_resources[] = अणु
	अणु
		/* 4 consecutive cells, 1 driver */
		.name = STA2X11_MFD_GPIO_NAME,
		.start = 0,
		.end = (4 * 4096) - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;
अटल स्थिर काष्ठा resource sctl_resources[] = अणु
	CELL_4K(STA2X11_MFD_SCTL_NAME, STA2X11_SCTL),
पूर्ण;
अटल स्थिर काष्ठा resource scr_resources[] = अणु
	CELL_4K(STA2X11_MFD_SCR_NAME, STA2X11_SCR),
पूर्ण;
अटल स्थिर काष्ठा resource समय_resources[] = अणु
	CELL_4K(STA2X11_MFD_TIME_NAME, STA2X11_TIME),
पूर्ण;

अटल स्थिर काष्ठा resource apbreg_resources[] = अणु
	CELL_4K(STA2X11_MFD_APBREG_NAME, STA2X11_APBREG),
पूर्ण;

#घोषणा DEV(_name, _r) \
	अणु .name = _name, .num_resources = ARRAY_SIZE(_r), .resources = _r, पूर्ण

अटल काष्ठा mfd_cell sta2x11_mfd0_bar0[] = अणु
	/* offset 0: we add pdata later */
	DEV(STA2X11_MFD_GPIO_NAME, gpio_resources),
	DEV(STA2X11_MFD_SCTL_NAME, sctl_resources),
	DEV(STA2X11_MFD_SCR_NAME,  scr_resources),
	DEV(STA2X11_MFD_TIME_NAME, समय_resources),
पूर्ण;

अटल काष्ठा mfd_cell sta2x11_mfd0_bar1[] = अणु
	DEV(STA2X11_MFD_APBREG_NAME, apbreg_resources),
पूर्ण;

/* Mfd 1 devices */

/* Mfd 1, Bar 0 */
क्रमागत mfd1_bar0_cells अणु
	STA2X11_VIC = 0,
पूर्ण;

/* Mfd 1, Bar 1 */
क्रमागत mfd1_bar1_cells अणु
	STA2X11_APB_SOC_REGS = 0,
पूर्ण;

अटल स्थिर काष्ठा resource vic_resources[] = अणु
	CELL_4K(STA2X11_MFD_VIC_NAME, STA2X11_VIC),
पूर्ण;

अटल स्थिर काष्ठा resource apb_soc_regs_resources[] = अणु
	CELL_4K(STA2X11_MFD_APB_SOC_REGS_NAME, STA2X11_APB_SOC_REGS),
पूर्ण;

अटल काष्ठा mfd_cell sta2x11_mfd1_bar0[] = अणु
	DEV(STA2X11_MFD_VIC_NAME, vic_resources),
पूर्ण;

अटल काष्ठा mfd_cell sta2x11_mfd1_bar1[] = अणु
	DEV(STA2X11_MFD_APB_SOC_REGS_NAME, apb_soc_regs_resources),
पूर्ण;


अटल पूर्णांक sta2x11_mfd_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक sta2x11_mfd_resume(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	pci_set_घातer_state(pdev, PCI_D0);
	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;
	pci_restore_state(pdev);

	वापस 0;
पूर्ण

काष्ठा sta2x11_mfd_bar_setup_data अणु
	काष्ठा mfd_cell *cells;
	पूर्णांक ncells;
पूर्ण;

काष्ठा sta2x11_mfd_setup_data अणु
	काष्ठा sta2x11_mfd_bar_setup_data bars[2];
पूर्ण;

#घोषणा STA2X11_MFD0 0
#घोषणा STA2X11_MFD1 1

अटल काष्ठा sta2x11_mfd_setup_data mfd_setup_data[] = अणु
	/* Mfd 0: gpio, sctl, scr, समयrs / apbregs */
	[STA2X11_MFD0] = अणु
		.bars = अणु
			[0] = अणु
				.cells = sta2x11_mfd0_bar0,
				.ncells = ARRAY_SIZE(sta2x11_mfd0_bar0),
			पूर्ण,
			[1] = अणु
				.cells = sta2x11_mfd0_bar1,
				.ncells = ARRAY_SIZE(sta2x11_mfd0_bar1),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	/* Mfd 1: vic / apb-soc-regs */
	[STA2X11_MFD1] = अणु
		.bars = अणु
			[0] = अणु
				.cells = sta2x11_mfd1_bar0,
				.ncells = ARRAY_SIZE(sta2x11_mfd1_bar0),
			पूर्ण,
			[1] = अणु
				.cells = sta2x11_mfd1_bar1,
				.ncells = ARRAY_SIZE(sta2x11_mfd1_bar1),
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम sta2x11_mfd_setup(काष्ठा pci_dev *pdev,
			      काष्ठा sta2x11_mfd_setup_data *sd)
अणु
	पूर्णांक i, j;
	क्रम (i = 0; i < ARRAY_SIZE(sd->bars); i++)
		क्रम (j = 0; j < sd->bars[i].ncells; j++) अणु
			sd->bars[i].cells[j].pdata_size = माप(pdev);
			sd->bars[i].cells[j].platक्रमm_data = &pdev;
		पूर्ण
पूर्ण

अटल पूर्णांक sta2x11_mfd_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक err, i;
	काष्ठा sta2x11_mfd_setup_data *setup_data;

	dev_info(&pdev->dev, "%s\n", __func__);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't enable device.\n");
		वापस err;
	पूर्ण

	err = pci_enable_msi(pdev);
	अगर (err)
		dev_info(&pdev->dev, "Enable msi failed\n");

	setup_data = pci_id->device == PCI_DEVICE_ID_STMICRO_GPIO ?
		&mfd_setup_data[STA2X11_MFD0] :
		&mfd_setup_data[STA2X11_MFD1];

	/* platक्रमm data is the pci device क्रम all of them */
	sta2x11_mfd_setup(pdev, setup_data);

	/* Record this pdev beक्रमe mfd_add_devices: their probe looks क्रम it */
	अगर (!sta2x11_mfd_find(pdev))
		sta2x11_mfd_add(pdev, GFP_ATOMIC);

	/* Just 2 bars क्रम all mfd's at present */
	क्रम (i = 0; i < 2; i++) अणु
		err = mfd_add_devices(&pdev->dev, -1,
				      setup_data->bars[i].cells,
				      setup_data->bars[i].ncells,
				      &pdev->resource[i],
				      0, शून्य);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"mfd_add_devices[%d] failed: %d\n", i, err);
			जाओ err_disable;
		पूर्ण
	पूर्ण

	वापस 0;

err_disable:
	mfd_हटाओ_devices(&pdev->dev);
	pci_disable_device(pdev);
	pci_disable_msi(pdev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sta2x11_mfd_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_STMICRO, PCI_DEVICE_ID_STMICRO_GPIO)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_STMICRO, PCI_DEVICE_ID_STMICRO_VIC)पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sta2x11_mfd_driver = अणु
	.name =		"sta2x11-mfd",
	.id_table =	sta2x11_mfd_tbl,
	.probe =	sta2x11_mfd_probe,
	.suspend =	sta2x11_mfd_suspend,
	.resume =	sta2x11_mfd_resume,
पूर्ण;

अटल पूर्णांक __init sta2x11_mfd_init(व्योम)
अणु
	pr_info("%s\n", __func__);
	वापस pci_रेजिस्टर_driver(&sta2x11_mfd_driver);
पूर्ण

/*
 * All of this must be पढ़ोy beक्रमe "normal" devices like MMCI appear.
 * But MFD (the pci device) can't be too early. The following choice
 * prepares platक्रमm drivers very early and probe the PCI device later,
 * but beक्रमe other PCI devices.
 */
subsys_initcall(sta2x11_drivers_init);
rootfs_initcall(sta2x11_mfd_init);
