<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * tpci200.c
 *
 * driver क्रम the TEWS TPCI-200 device
 *
 * Copyright (C) 2009-2012 CERN (www.cern.ch)
 * Author: Nicolas Serafini, EIC2 SA
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "tpci200.h"

अटल स्थिर u16 tpci200_status_समयout[] = अणु
	TPCI200_A_TIMEOUT,
	TPCI200_B_TIMEOUT,
	TPCI200_C_TIMEOUT,
	TPCI200_D_TIMEOUT,
पूर्ण;

अटल स्थिर u16 tpci200_status_error[] = अणु
	TPCI200_A_ERROR,
	TPCI200_B_ERROR,
	TPCI200_C_ERROR,
	TPCI200_D_ERROR,
पूर्ण;

अटल स्थिर माप_प्रकार tpci200_space_size[IPACK_SPACE_COUNT] = अणु
	[IPACK_IO_SPACE]    = TPCI200_IO_SPACE_SIZE,
	[IPACK_ID_SPACE]    = TPCI200_ID_SPACE_SIZE,
	[IPACK_INT_SPACE]   = TPCI200_INT_SPACE_SIZE,
	[IPACK_MEM8_SPACE]  = TPCI200_MEM8_SPACE_SIZE,
	[IPACK_MEM16_SPACE] = TPCI200_MEM16_SPACE_SIZE,
पूर्ण;

अटल स्थिर माप_प्रकार tpci200_space_पूर्णांकerval[IPACK_SPACE_COUNT] = अणु
	[IPACK_IO_SPACE]    = TPCI200_IO_SPACE_INTERVAL,
	[IPACK_ID_SPACE]    = TPCI200_ID_SPACE_INTERVAL,
	[IPACK_INT_SPACE]   = TPCI200_INT_SPACE_INTERVAL,
	[IPACK_MEM8_SPACE]  = TPCI200_MEM8_SPACE_INTERVAL,
	[IPACK_MEM16_SPACE] = TPCI200_MEM16_SPACE_INTERVAL,
पूर्ण;

अटल काष्ठा tpci200_board *check_slot(काष्ठा ipack_device *dev)
अणु
	काष्ठा tpci200_board *tpci200;

	अगर (dev == शून्य)
		वापस शून्य;


	tpci200 = dev_get_drvdata(dev->bus->parent);

	अगर (tpci200 == शून्य) अणु
		dev_info(&dev->dev, "carrier board not found\n");
		वापस शून्य;
	पूर्ण

	अगर (dev->slot >= TPCI200_NB_SLOT) अणु
		dev_info(&dev->dev,
			 "Slot [%d:%d] doesn't exist! Last tpci200 slot is %d.\n",
			 dev->bus->bus_nr, dev->slot, TPCI200_NB_SLOT-1);
		वापस शून्य;
	पूर्ण

	वापस tpci200;
पूर्ण

अटल व्योम tpci200_clear_mask(काष्ठा tpci200_board *tpci200,
			       __le16 __iomem *addr, u16 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&tpci200->regs_lock, flags);
	ioग_लिखो16(ioपढ़ो16(addr) & (~mask), addr);
	spin_unlock_irqrestore(&tpci200->regs_lock, flags);
पूर्ण

अटल व्योम tpci200_set_mask(काष्ठा tpci200_board *tpci200,
			     __le16 __iomem *addr, u16 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&tpci200->regs_lock, flags);
	ioग_लिखो16(ioपढ़ो16(addr) | mask, addr);
	spin_unlock_irqrestore(&tpci200->regs_lock, flags);
पूर्ण

अटल व्योम tpci200_unरेजिस्टर(काष्ठा tpci200_board *tpci200)
अणु
	मुक्त_irq(tpci200->info->pdev->irq, (व्योम *) tpci200);

	pci_iounmap(tpci200->info->pdev, tpci200->info->पूर्णांकerface_regs);
	pci_iounmap(tpci200->info->pdev, tpci200->info->cfg_regs);

	pci_release_region(tpci200->info->pdev, TPCI200_IP_INTERFACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_IO_ID_INT_SPACES_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_CFG_MEM_BAR);

	pci_disable_device(tpci200->info->pdev);
	pci_dev_put(tpci200->info->pdev);
पूर्ण

अटल व्योम tpci200_enable_irq(काष्ठा tpci200_board *tpci200,
			       पूर्णांक islot)
अणु
	tpci200_set_mask(tpci200,
			&tpci200->info->पूर्णांकerface_regs->control[islot],
			TPCI200_INT0_EN | TPCI200_INT1_EN);
पूर्ण

अटल व्योम tpci200_disable_irq(काष्ठा tpci200_board *tpci200,
				पूर्णांक islot)
अणु
	tpci200_clear_mask(tpci200,
			&tpci200->info->पूर्णांकerface_regs->control[islot],
			TPCI200_INT0_EN | TPCI200_INT1_EN);
पूर्ण

अटल irqवापस_t tpci200_slot_irq(काष्ठा slot_irq *slot_irq)
अणु
	irqवापस_t ret;

	अगर (!slot_irq)
		वापस -ENODEV;
	ret = slot_irq->handler(slot_irq->arg);

	वापस ret;
पूर्ण

अटल irqवापस_t tpci200_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tpci200_board *tpci200 = (काष्ठा tpci200_board *) dev_id;
	काष्ठा slot_irq *slot_irq;
	irqवापस_t ret;
	u16 status_reg;
	पूर्णांक i;

	/* Read status रेजिस्टर */
	status_reg = ioपढ़ो16(&tpci200->info->पूर्णांकerface_regs->status);

	/* Did we cause the पूर्णांकerrupt? */
	अगर (!(status_reg & TPCI200_SLOT_INT_MASK))
		वापस IRQ_NONE;

	/* callback to the IRQ handler क्रम the corresponding slot */
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < TPCI200_NB_SLOT; i++) अणु
		अगर (!(status_reg & ((TPCI200_A_INT0 | TPCI200_A_INT1) << (2 * i))))
			जारी;
		slot_irq = rcu_dereference(tpci200->slots[i].irq);
		ret = tpci200_slot_irq(slot_irq);
		अगर (ret == -ENODEV) अणु
			dev_info(&tpci200->info->pdev->dev,
				 "No registered ISR for slot [%d:%d]!. IRQ will be disabled.\n",
				 tpci200->number, i);
			tpci200_disable_irq(tpci200, i);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tpci200_मुक्त_irq(काष्ठा ipack_device *dev)
अणु
	काष्ठा slot_irq *slot_irq;
	काष्ठा tpci200_board *tpci200;

	tpci200 = check_slot(dev);
	अगर (tpci200 == शून्य)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&tpci200->mutex))
		वापस -ERESTARTSYS;

	अगर (tpci200->slots[dev->slot].irq == शून्य) अणु
		mutex_unlock(&tpci200->mutex);
		वापस -EINVAL;
	पूर्ण

	tpci200_disable_irq(tpci200, dev->slot);
	slot_irq = tpci200->slots[dev->slot].irq;
	/* uninstall handler */
	RCU_INIT_POINTER(tpci200->slots[dev->slot].irq, शून्य);
	synchronize_rcu();
	kमुक्त(slot_irq);
	mutex_unlock(&tpci200->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक tpci200_request_irq(काष्ठा ipack_device *dev,
			       irqवापस_t (*handler)(व्योम *), व्योम *arg)
अणु
	पूर्णांक res = 0;
	काष्ठा slot_irq *slot_irq;
	काष्ठा tpci200_board *tpci200;

	tpci200 = check_slot(dev);
	अगर (tpci200 == शून्य)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&tpci200->mutex))
		वापस -ERESTARTSYS;

	अगर (tpci200->slots[dev->slot].irq != शून्य) अणु
		dev_err(&dev->dev,
			"Slot [%d:%d] IRQ already registered !\n",
			dev->bus->bus_nr,
			dev->slot);
		res = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	slot_irq = kzalloc(माप(काष्ठा slot_irq), GFP_KERNEL);
	अगर (slot_irq == शून्य) अणु
		dev_err(&dev->dev,
			"Slot [%d:%d] unable to allocate memory for IRQ !\n",
			dev->bus->bus_nr, dev->slot);
		res = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	/*
	 * WARNING: Setup Interrupt Vector in the IndustryPack device
	 * beक्रमe an IRQ request.
	 * Read the User Manual of your IndustryPack device to know
	 * where to ग_लिखो the vector in memory.
	 */
	slot_irq->handler = handler;
	slot_irq->arg = arg;
	slot_irq->holder = dev;

	rcu_assign_poपूर्णांकer(tpci200->slots[dev->slot].irq, slot_irq);
	tpci200_enable_irq(tpci200, dev->slot);

out_unlock:
	mutex_unlock(&tpci200->mutex);
	वापस res;
पूर्ण

अटल पूर्णांक tpci200_रेजिस्टर(काष्ठा tpci200_board *tpci200)
अणु
	पूर्णांक i;
	पूर्णांक res;
	phys_addr_t ioidपूर्णांक_base;
	अचिन्हित लघु slot_ctrl;

	अगर (pci_enable_device(tpci200->info->pdev) < 0)
		वापस -ENODEV;

	/* Request IP पूर्णांकerface रेजिस्टर (Bar 2) */
	res = pci_request_region(tpci200->info->pdev, TPCI200_IP_INTERFACE_BAR,
				 "Carrier IP interface registers");
	अगर (res) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) failed to allocate PCI resource for BAR 2 !",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		जाओ out_disable_pci;
	पूर्ण

	/* Request IO ID INT space (Bar 3) */
	res = pci_request_region(tpci200->info->pdev,
				 TPCI200_IO_ID_INT_SPACES_BAR,
				 "Carrier IO ID INT space");
	अगर (res) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) failed to allocate PCI resource for BAR 3 !",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		जाओ out_release_ip_space;
	पूर्ण

	/* Request MEM8 space (Bar 5) */
	res = pci_request_region(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAR,
				 "Carrier MEM8 space");
	अगर (res) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) failed to allocate PCI resource for BAR 5!",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		जाओ out_release_ioid_पूर्णांक_space;
	पूर्ण

	/* Request MEM16 space (Bar 4) */
	res = pci_request_region(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAR,
				 "Carrier MEM16 space");
	अगर (res) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) failed to allocate PCI resource for BAR 4!",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		जाओ out_release_mem8_space;
	पूर्ण

	/* Map पूर्णांकernal tpci200 driver user space */
	tpci200->info->पूर्णांकerface_regs =
		ioremap(pci_resource_start(tpci200->info->pdev,
					   TPCI200_IP_INTERFACE_BAR),
			TPCI200_IFACE_SIZE);
	अगर (!tpci200->info->पूर्णांकerface_regs) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) failed to map driver user space!",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		res = -ENOMEM;
		जाओ out_release_mem8_space;
	पूर्ण

	/* Initialize lock that protects पूर्णांकerface_regs */
	spin_lock_init(&tpci200->regs_lock);

	ioidपूर्णांक_base = pci_resource_start(tpci200->info->pdev,
					  TPCI200_IO_ID_INT_SPACES_BAR);
	tpci200->mod_mem[IPACK_IO_SPACE] = ioidपूर्णांक_base + TPCI200_IO_SPACE_OFF;
	tpci200->mod_mem[IPACK_ID_SPACE] = ioidपूर्णांक_base + TPCI200_ID_SPACE_OFF;
	tpci200->mod_mem[IPACK_INT_SPACE] =
		ioidपूर्णांक_base + TPCI200_INT_SPACE_OFF;
	tpci200->mod_mem[IPACK_MEM8_SPACE] =
		pci_resource_start(tpci200->info->pdev,
				   TPCI200_MEM8_SPACE_BAR);
	tpci200->mod_mem[IPACK_MEM16_SPACE] =
		pci_resource_start(tpci200->info->pdev,
				   TPCI200_MEM16_SPACE_BAR);

	/* Set the शेष parameters of the slot
	 * INT0 disabled, level sensitive
	 * INT1 disabled, level sensitive
	 * error पूर्णांकerrupt disabled
	 * समयout पूर्णांकerrupt disabled
	 * recover समय disabled
	 * घड़ी rate 8 MHz
	 */
	slot_ctrl = 0;
	क्रम (i = 0; i < TPCI200_NB_SLOT; i++)
		ग_लिखोw(slot_ctrl, &tpci200->info->पूर्णांकerface_regs->control[i]);

	res = request_irq(tpci200->info->pdev->irq,
			  tpci200_पूर्णांकerrupt, IRQF_SHARED,
			  KBUILD_MODNAME, (व्योम *) tpci200);
	अगर (res) अणु
		dev_err(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) unable to register IRQ !",
			tpci200->info->pdev->bus->number,
			tpci200->info->pdev->devfn);
		जाओ out_release_ioid_पूर्णांक_space;
	पूर्ण

	वापस 0;

out_release_mem8_space:
	pci_release_region(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAR);
out_release_ioid_पूर्णांक_space:
	pci_release_region(tpci200->info->pdev, TPCI200_IO_ID_INT_SPACES_BAR);
out_release_ip_space:
	pci_release_region(tpci200->info->pdev, TPCI200_IP_INTERFACE_BAR);
out_disable_pci:
	pci_disable_device(tpci200->info->pdev);
	वापस res;
पूर्ण

अटल पूर्णांक tpci200_get_घड़ीrate(काष्ठा ipack_device *dev)
अणु
	काष्ठा tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;

	अगर (!tpci200)
		वापस -ENODEV;

	addr = &tpci200->info->पूर्णांकerface_regs->control[dev->slot];
	वापस (ioपढ़ो16(addr) & TPCI200_CLK32) ? 32 : 8;
पूर्ण

अटल पूर्णांक tpci200_set_घड़ीrate(काष्ठा ipack_device *dev, पूर्णांक mherz)
अणु
	काष्ठा tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;

	अगर (!tpci200)
		वापस -ENODEV;

	addr = &tpci200->info->पूर्णांकerface_regs->control[dev->slot];

	चयन (mherz) अणु
	हाल 8:
		tpci200_clear_mask(tpci200, addr, TPCI200_CLK32);
		अवरोध;
	हाल 32:
		tpci200_set_mask(tpci200, addr, TPCI200_CLK32);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tpci200_get_error(काष्ठा ipack_device *dev)
अणु
	काष्ठा tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;
	u16 mask;

	अगर (!tpci200)
		वापस -ENODEV;

	addr = &tpci200->info->पूर्णांकerface_regs->status;
	mask = tpci200_status_error[dev->slot];
	वापस (ioपढ़ो16(addr) & mask) ? 1 : 0;
पूर्ण

अटल पूर्णांक tpci200_get_समयout(काष्ठा ipack_device *dev)
अणु
	काष्ठा tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;
	u16 mask;

	अगर (!tpci200)
		वापस -ENODEV;

	addr = &tpci200->info->पूर्णांकerface_regs->status;
	mask = tpci200_status_समयout[dev->slot];

	वापस (ioपढ़ो16(addr) & mask) ? 1 : 0;
पूर्ण

अटल पूर्णांक tpci200_reset_समयout(काष्ठा ipack_device *dev)
अणु
	काष्ठा tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;
	u16 mask;

	अगर (!tpci200)
		वापस -ENODEV;

	addr = &tpci200->info->पूर्णांकerface_regs->status;
	mask = tpci200_status_समयout[dev->slot];

	ioग_लिखो16(mask, addr);
	वापस 0;
पूर्ण

अटल व्योम tpci200_uninstall(काष्ठा tpci200_board *tpci200)
अणु
	tpci200_unरेजिस्टर(tpci200);
	kमुक्त(tpci200->slots);
पूर्ण

अटल स्थिर काष्ठा ipack_bus_ops tpci200_bus_ops = अणु
	.request_irq = tpci200_request_irq,
	.मुक्त_irq = tpci200_मुक्त_irq,
	.get_घड़ीrate = tpci200_get_घड़ीrate,
	.set_घड़ीrate = tpci200_set_घड़ीrate,
	.get_error     = tpci200_get_error,
	.get_समयout   = tpci200_get_समयout,
	.reset_समयout = tpci200_reset_समयout,
पूर्ण;

अटल पूर्णांक tpci200_install(काष्ठा tpci200_board *tpci200)
अणु
	पूर्णांक res;

	tpci200->slots = kसुस्मृति(TPCI200_NB_SLOT, माप(काष्ठा tpci200_slot),
				 GFP_KERNEL);
	अगर (tpci200->slots == शून्य)
		वापस -ENOMEM;

	res = tpci200_रेजिस्टर(tpci200);
	अगर (res) अणु
		kमुक्त(tpci200->slots);
		tpci200->slots = शून्य;
		वापस res;
	पूर्ण

	mutex_init(&tpci200->mutex);
	वापस 0;
पूर्ण

अटल व्योम tpci200_release_device(काष्ठा ipack_device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक tpci200_create_device(काष्ठा tpci200_board *tpci200, पूर्णांक i)
अणु
	पूर्णांक ret;
	क्रमागत ipack_space space;
	काष्ठा ipack_device *dev =
		kzalloc(माप(काष्ठा ipack_device), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->slot = i;
	dev->bus = tpci200->info->ipack_bus;
	dev->release = tpci200_release_device;

	क्रम (space = 0; space < IPACK_SPACE_COUNT; space++) अणु
		dev->region[space].start =
			tpci200->mod_mem[space]
			+ tpci200_space_पूर्णांकerval[space] * i;
		dev->region[space].size = tpci200_space_size[space];
	पूर्ण

	ret = ipack_device_init(dev);
	अगर (ret < 0) अणु
		ipack_put_device(dev);
		वापस ret;
	पूर्ण

	ret = ipack_device_add(dev);
	अगर (ret < 0)
		ipack_put_device(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tpci200_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret, i;
	काष्ठा tpci200_board *tpci200;
	u32 reg32;

	tpci200 = kzalloc(माप(काष्ठा tpci200_board), GFP_KERNEL);
	अगर (!tpci200)
		वापस -ENOMEM;

	tpci200->info = kzalloc(माप(काष्ठा tpci200_infos), GFP_KERNEL);
	अगर (!tpci200->info) अणु
		ret = -ENOMEM;
		जाओ out_err_info;
	पूर्ण

	pci_dev_get(pdev);

	/* Obtain a mapping of the carrier's PCI configuration रेजिस्टरs */
	ret = pci_request_region(pdev, TPCI200_CFG_MEM_BAR,
				 KBUILD_MODNAME " Configuration Memory");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to allocate PCI Configuration Memory");
		ret = -EBUSY;
		जाओ out_err_pci_request;
	पूर्ण
	tpci200->info->cfg_regs = ioremap(
			pci_resource_start(pdev, TPCI200_CFG_MEM_BAR),
			pci_resource_len(pdev, TPCI200_CFG_MEM_BAR));
	अगर (!tpci200->info->cfg_regs) अणु
		dev_err(&pdev->dev, "Failed to map PCI Configuration Memory");
		ret = -EFAULT;
		जाओ out_err_ioremap;
	पूर्ण

	/* Disable byte swapping क्रम 16 bit IP module access. This will ensure
	 * that the Industrypack big endian byte order is preserved by the
	 * carrier. */
	reg32 = ioपढ़ो32(tpci200->info->cfg_regs + LAS1_DESC);
	reg32 |= 1 << LAS_BIT_BIGENDIAN;
	ioग_लिखो32(reg32, tpci200->info->cfg_regs + LAS1_DESC);

	reg32 = ioपढ़ो32(tpci200->info->cfg_regs + LAS2_DESC);
	reg32 |= 1 << LAS_BIT_BIGENDIAN;
	ioग_लिखो32(reg32, tpci200->info->cfg_regs + LAS2_DESC);

	/* Save काष्ठा pci_dev poपूर्णांकer */
	tpci200->info->pdev = pdev;
	tpci200->info->id_table = (काष्ठा pci_device_id *)id;

	/* रेजिस्टर the device and initialize it */
	ret = tpci200_install(tpci200);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error during tpci200 install\n");
		ret = -ENODEV;
		जाओ out_err_install;
	पूर्ण

	/* Register the carrier in the industry pack bus driver */
	tpci200->info->ipack_bus = ipack_bus_रेजिस्टर(&pdev->dev,
						      TPCI200_NB_SLOT,
						      &tpci200_bus_ops,
						      THIS_MODULE);
	अगर (!tpci200->info->ipack_bus) अणु
		dev_err(&pdev->dev,
			"error registering the carrier on ipack driver\n");
		ret = -EFAULT;
		जाओ out_err_bus_रेजिस्टर;
	पूर्ण

	/* save the bus number given by ipack to logging purpose */
	tpci200->number = tpci200->info->ipack_bus->bus_nr;
	dev_set_drvdata(&pdev->dev, tpci200);

	क्रम (i = 0; i < TPCI200_NB_SLOT; i++)
		tpci200_create_device(tpci200, i);
	वापस 0;

out_err_bus_रेजिस्टर:
	tpci200_uninstall(tpci200);
out_err_install:
	iounmap(tpci200->info->cfg_regs);
out_err_ioremap:
	pci_release_region(pdev, TPCI200_CFG_MEM_BAR);
out_err_pci_request:
	pci_dev_put(pdev);
	kमुक्त(tpci200->info);
out_err_info:
	kमुक्त(tpci200);
	वापस ret;
पूर्ण

अटल व्योम __tpci200_pci_हटाओ(काष्ठा tpci200_board *tpci200)
अणु
	ipack_bus_unरेजिस्टर(tpci200->info->ipack_bus);
	tpci200_uninstall(tpci200);

	kमुक्त(tpci200->info);
	kमुक्त(tpci200);
पूर्ण

अटल व्योम tpci200_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा tpci200_board *tpci200 = pci_get_drvdata(dev);

	__tpci200_pci_हटाओ(tpci200);
पूर्ण

अटल स्थिर काष्ठा pci_device_id tpci200_idtable[] = अणु
	अणु TPCI200_VENDOR_ID, TPCI200_DEVICE_ID, TPCI200_SUBVENDOR_ID,
	  TPCI200_SUBDEVICE_ID पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, tpci200_idtable);

अटल काष्ठा pci_driver tpci200_pci_drv = अणु
	.name = "tpci200",
	.id_table = tpci200_idtable,
	.probe = tpci200_pci_probe,
	.हटाओ = tpci200_pci_हटाओ,
पूर्ण;

module_pci_driver(tpci200_pci_drv);

MODULE_DESCRIPTION("TEWS TPCI-200 device driver");
MODULE_LICENSE("GPL");
