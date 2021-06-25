<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71xx PCI host controller driver
 *
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15 BSP
 */

#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-ath79/ar71xx_regs.h>
#समावेश <यंत्र/mach-ath79/ath79.h>

#घोषणा AR71XX_PCI_REG_CRP_AD_CBE	0x00
#घोषणा AR71XX_PCI_REG_CRP_WRDATA	0x04
#घोषणा AR71XX_PCI_REG_CRP_RDDATA	0x08
#घोषणा AR71XX_PCI_REG_CFG_AD		0x0c
#घोषणा AR71XX_PCI_REG_CFG_CBE		0x10
#घोषणा AR71XX_PCI_REG_CFG_WRDATA	0x14
#घोषणा AR71XX_PCI_REG_CFG_RDDATA	0x18
#घोषणा AR71XX_PCI_REG_PCI_ERR		0x1c
#घोषणा AR71XX_PCI_REG_PCI_ERR_ADDR	0x20
#घोषणा AR71XX_PCI_REG_AHB_ERR		0x24
#घोषणा AR71XX_PCI_REG_AHB_ERR_ADDR	0x28

#घोषणा AR71XX_PCI_CRP_CMD_WRITE	0x00010000
#घोषणा AR71XX_PCI_CRP_CMD_READ		0x00000000
#घोषणा AR71XX_PCI_CFG_CMD_READ		0x0000000a
#घोषणा AR71XX_PCI_CFG_CMD_WRITE	0x0000000b

#घोषणा AR71XX_PCI_INT_CORE		BIT(4)
#घोषणा AR71XX_PCI_INT_DEV2		BIT(2)
#घोषणा AR71XX_PCI_INT_DEV1		BIT(1)
#घोषणा AR71XX_PCI_INT_DEV0		BIT(0)

#घोषणा AR71XX_PCI_IRQ_COUNT		5

काष्ठा ar71xx_pci_controller अणु
	व्योम __iomem *cfg_base;
	पूर्णांक irq;
	पूर्णांक irq_base;
	काष्ठा pci_controller pci_ctrl;
	काष्ठा resource io_res;
	काष्ठा resource mem_res;
पूर्ण;

/* Byte lane enable bits */
अटल स्थिर u8 ar71xx_pci_ble_table[4][4] = अणु
	अणु0x0, 0xf, 0xf, 0xfपूर्ण,
	अणु0xe, 0xd, 0xb, 0x7पूर्ण,
	अणु0xc, 0xf, 0x3, 0xfपूर्ण,
	अणु0xf, 0xf, 0xf, 0xfपूर्ण,
पूर्ण;

अटल स्थिर u32 ar71xx_pci_पढ़ो_mask[8] = अणु
	0, 0xff, 0xffff, 0, 0xffffffff, 0, 0, 0
पूर्ण;

अटल अंतरभूत u32 ar71xx_pci_get_ble(पूर्णांक where, पूर्णांक size, पूर्णांक local)
अणु
	u32 t;

	t = ar71xx_pci_ble_table[size & 3][where & 3];
	BUG_ON(t == 0xf);
	t <<= (local) ? 20 : 4;

	वापस t;
पूर्ण

अटल अंतरभूत u32 ar71xx_pci_bus_addr(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				      पूर्णांक where)
अणु
	u32 ret;

	अगर (!bus->number) अणु
		/* type 0 */
		ret = (1 << PCI_SLOT(devfn)) | (PCI_FUNC(devfn) << 8) |
		      (where & ~3);
	पूर्ण अन्यथा अणु
		/* type 1 */
		ret = (bus->number << 16) | (PCI_SLOT(devfn) << 11) |
		      (PCI_FUNC(devfn) << 8) | (where & ~3) | 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा ar71xx_pci_controller *
pci_bus_to_ar71xx_controller(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose;

	hose = (काष्ठा pci_controller *) bus->sysdata;
	वापस container_of(hose, काष्ठा ar71xx_pci_controller, pci_ctrl);
पूर्ण

अटल पूर्णांक ar71xx_pci_check_error(काष्ठा ar71xx_pci_controller *apc, पूर्णांक quiet)
अणु
	व्योम __iomem *base = apc->cfg_base;
	u32 pci_err;
	u32 ahb_err;

	pci_err = __raw_पढ़ोl(base + AR71XX_PCI_REG_PCI_ERR) & 3;
	अगर (pci_err) अणु
		अगर (!quiet) अणु
			u32 addr;

			addr = __raw_पढ़ोl(base + AR71XX_PCI_REG_PCI_ERR_ADDR);
			pr_crit("ar71xx: %s bus error %d at addr 0x%x\n",
				"PCI", pci_err, addr);
		पूर्ण

		/* clear PCI error status */
		__raw_ग_लिखोl(pci_err, base + AR71XX_PCI_REG_PCI_ERR);
	पूर्ण

	ahb_err = __raw_पढ़ोl(base + AR71XX_PCI_REG_AHB_ERR) & 1;
	अगर (ahb_err) अणु
		अगर (!quiet) अणु
			u32 addr;

			addr = __raw_पढ़ोl(base + AR71XX_PCI_REG_AHB_ERR_ADDR);
			pr_crit("ar71xx: %s bus error %d at addr 0x%x\n",
				"AHB", ahb_err, addr);
		पूर्ण

		/* clear AHB error status */
		__raw_ग_लिखोl(ahb_err, base + AR71XX_PCI_REG_AHB_ERR);
	पूर्ण

	वापस !!(ahb_err | pci_err);
पूर्ण

अटल अंतरभूत व्योम ar71xx_pci_local_ग_लिखो(काष्ठा ar71xx_pci_controller *apc,
					  पूर्णांक where, पूर्णांक size, u32 value)
अणु
	व्योम __iomem *base = apc->cfg_base;
	u32 ad_cbe;

	value = value << (8 * (where & 3));

	ad_cbe = AR71XX_PCI_CRP_CMD_WRITE | (where & ~3);
	ad_cbe |= ar71xx_pci_get_ble(where, size, 1);

	__raw_ग_लिखोl(ad_cbe, base + AR71XX_PCI_REG_CRP_AD_CBE);
	__raw_ग_लिखोl(value, base + AR71XX_PCI_REG_CRP_WRDATA);
पूर्ण

अटल अंतरभूत पूर्णांक ar71xx_pci_set_cfgaddr(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक devfn,
					 पूर्णांक where, पूर्णांक size, u32 cmd)
अणु
	काष्ठा ar71xx_pci_controller *apc = pci_bus_to_ar71xx_controller(bus);
	व्योम __iomem *base = apc->cfg_base;
	u32 addr;

	addr = ar71xx_pci_bus_addr(bus, devfn, where);

	__raw_ग_लिखोl(addr, base + AR71XX_PCI_REG_CFG_AD);
	__raw_ग_लिखोl(cmd | ar71xx_pci_get_ble(where, size, 0),
		     base + AR71XX_PCI_REG_CFG_CBE);

	वापस ar71xx_pci_check_error(apc, 1);
पूर्ण

अटल पूर्णांक ar71xx_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा ar71xx_pci_controller *apc = pci_bus_to_ar71xx_controller(bus);
	व्योम __iomem *base = apc->cfg_base;
	u32 data;
	पूर्णांक err;
	पूर्णांक ret;

	ret = PCIBIOS_SUCCESSFUL;
	data = ~0;

	err = ar71xx_pci_set_cfgaddr(bus, devfn, where, size,
				     AR71XX_PCI_CFG_CMD_READ);
	अगर (err)
		ret = PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		data = __raw_पढ़ोl(base + AR71XX_PCI_REG_CFG_RDDATA);

	*value = (data >> (8 * (where & 3))) & ar71xx_pci_पढ़ो_mask[size & 7];

	वापस ret;
पूर्ण

अटल पूर्णांक ar71xx_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा ar71xx_pci_controller *apc = pci_bus_to_ar71xx_controller(bus);
	व्योम __iomem *base = apc->cfg_base;
	पूर्णांक err;
	पूर्णांक ret;

	value = value << (8 * (where & 3));
	ret = PCIBIOS_SUCCESSFUL;

	err = ar71xx_pci_set_cfgaddr(bus, devfn, where, size,
				     AR71XX_PCI_CFG_CMD_WRITE);
	अगर (err)
		ret = PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		__raw_ग_लिखोl(value, base + AR71XX_PCI_REG_CFG_WRDATA);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops ar71xx_pci_ops = अणु
	.पढ़ो	= ar71xx_pci_पढ़ो_config,
	.ग_लिखो	= ar71xx_pci_ग_लिखो_config,
पूर्ण;

अटल व्योम ar71xx_pci_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ar71xx_pci_controller *apc;
	व्योम __iomem *base = ath79_reset_base;
	u32 pending;

	apc = irq_desc_get_handler_data(desc);

	pending = __raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_STATUS) &
		  __raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_ENABLE);

	अगर (pending & AR71XX_PCI_INT_DEV0)
		generic_handle_irq(apc->irq_base + 0);

	अन्यथा अगर (pending & AR71XX_PCI_INT_DEV1)
		generic_handle_irq(apc->irq_base + 1);

	अन्यथा अगर (pending & AR71XX_PCI_INT_DEV2)
		generic_handle_irq(apc->irq_base + 2);

	अन्यथा अगर (pending & AR71XX_PCI_INT_CORE)
		generic_handle_irq(apc->irq_base + 4);

	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

अटल व्योम ar71xx_pci_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ar71xx_pci_controller *apc;
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *base = ath79_reset_base;
	u32 t;

	apc = irq_data_get_irq_chip_data(d);
	irq = d->irq - apc->irq_base;

	t = __raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_ENABLE);
	__raw_ग_लिखोl(t | (1 << irq), base + AR71XX_RESET_REG_PCI_INT_ENABLE);

	/* flush ग_लिखो */
	__raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_ENABLE);
पूर्ण

अटल व्योम ar71xx_pci_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ar71xx_pci_controller *apc;
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *base = ath79_reset_base;
	u32 t;

	apc = irq_data_get_irq_chip_data(d);
	irq = d->irq - apc->irq_base;

	t = __raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_ENABLE);
	__raw_ग_लिखोl(t & ~(1 << irq), base + AR71XX_RESET_REG_PCI_INT_ENABLE);

	/* flush ग_लिखो */
	__raw_पढ़ोl(base + AR71XX_RESET_REG_PCI_INT_ENABLE);
पूर्ण

अटल काष्ठा irq_chip ar71xx_pci_irq_chip = अणु
	.name		= "AR71XX PCI",
	.irq_mask	= ar71xx_pci_irq_mask,
	.irq_unmask	= ar71xx_pci_irq_unmask,
	.irq_mask_ack	= ar71xx_pci_irq_mask,
पूर्ण;

अटल व्योम ar71xx_pci_irq_init(काष्ठा ar71xx_pci_controller *apc)
अणु
	व्योम __iomem *base = ath79_reset_base;
	पूर्णांक i;

	__raw_ग_लिखोl(0, base + AR71XX_RESET_REG_PCI_INT_ENABLE);
	__raw_ग_लिखोl(0, base + AR71XX_RESET_REG_PCI_INT_STATUS);

	BUILD_BUG_ON(ATH79_PCI_IRQ_COUNT < AR71XX_PCI_IRQ_COUNT);

	apc->irq_base = ATH79_PCI_IRQ_BASE;
	क्रम (i = apc->irq_base;
	     i < apc->irq_base + AR71XX_PCI_IRQ_COUNT; i++) अणु
		irq_set_chip_and_handler(i, &ar71xx_pci_irq_chip,
					 handle_level_irq);
		irq_set_chip_data(i, apc);
	पूर्ण

	irq_set_chained_handler_and_data(apc->irq, ar71xx_pci_irq_handler,
					 apc);
पूर्ण

अटल व्योम ar71xx_pci_reset(व्योम)
अणु
	ath79_device_reset_set(AR71XX_RESET_PCI_BUS | AR71XX_RESET_PCI_CORE);
	mdelay(100);

	ath79_device_reset_clear(AR71XX_RESET_PCI_BUS | AR71XX_RESET_PCI_CORE);
	mdelay(100);

	ath79_ddr_set_pci_winकरोws();
	mdelay(100);
पूर्ण

अटल पूर्णांक ar71xx_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar71xx_pci_controller *apc;
	काष्ठा resource *res;
	u32 t;

	apc = devm_kzalloc(&pdev->dev, माप(काष्ठा ar71xx_pci_controller),
			   GFP_KERNEL);
	अगर (!apc)
		वापस -ENOMEM;

	apc->cfg_base = devm_platक्रमm_ioremap_resource_byname(pdev,
							      "cfg_base");
	अगर (IS_ERR(apc->cfg_base))
		वापस PTR_ERR(apc->cfg_base);

	apc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (apc->irq < 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IO, "io_base");
	अगर (!res)
		वापस -EINVAL;

	apc->io_res.parent = res;
	apc->io_res.name = "PCI IO space";
	apc->io_res.start = res->start;
	apc->io_res.end = res->end;
	apc->io_res.flags = IORESOURCE_IO;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mem_base");
	अगर (!res)
		वापस -EINVAL;

	apc->mem_res.parent = res;
	apc->mem_res.name = "PCI memory space";
	apc->mem_res.start = res->start;
	apc->mem_res.end = res->end;
	apc->mem_res.flags = IORESOURCE_MEM;

	ar71xx_pci_reset();

	/* setup COMMAND रेजिस्टर */
	t = PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE
	  | PCI_COMMAND_PARITY | PCI_COMMAND_SERR | PCI_COMMAND_FAST_BACK;
	ar71xx_pci_local_ग_लिखो(apc, PCI_COMMAND, 4, t);

	/* clear bus errors */
	ar71xx_pci_check_error(apc, 1);

	ar71xx_pci_irq_init(apc);

	apc->pci_ctrl.pci_ops = &ar71xx_pci_ops;
	apc->pci_ctrl.mem_resource = &apc->mem_res;
	apc->pci_ctrl.io_resource = &apc->io_res;

	रेजिस्टर_pci_controller(&apc->pci_ctrl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ar71xx_pci_driver = अणु
	.probe = ar71xx_pci_probe,
	.driver = अणु
		.name = "ar71xx-pci",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ar71xx_pci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ar71xx_pci_driver);
पूर्ण

postcore_initcall(ar71xx_pci_init);
