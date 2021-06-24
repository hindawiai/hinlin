<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/**
 * Both AR2315 and AR2316 chips have PCI पूर्णांकerface unit, which supports DMA
 * and पूर्णांकerrupt. PCI पूर्णांकerface supports MMIO access method, but करोes not
 * seem to support I/O ports.
 *
 * Read/ग_लिखो operation in the region 0x80000000-0xBFFFFFFF causes
 * a memory पढ़ो/ग_लिखो command on the PCI bus. 30 LSBs of address on
 * the bus are taken from memory पढ़ो/ग_लिखो request and 2 MSBs are
 * determined by PCI unit configuration.
 *
 * To work with the configuration space instead of memory is necessary set
 * the CFG_SEL bit in the PCI_MISC_CONFIG रेजिस्टर.
 *
 * Devices on the bus can perक्रमm DMA requests via chip BAR1. PCI host
 * controller BARs are programmend as अगर an बाह्यal device is programmed.
 * Which means that during configuration, IDSEL pin of the chip should be
 * निश्चितed.
 *
 * We know (and support) only one board that uses the PCI पूर्णांकerface -
 * Fonera 2.0g (FON2202). It has a USB EHCI controller connected to the
 * AR2315 PCI bus. IDSEL pin of USB controller is connected to AD[13] line
 * and IDSEL pin of AR2315 is connected to AD[16] line.
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/paccess.h>

/*
 * PCI Bus Interface Registers
 */
#घोषणा AR2315_PCI_1MS_REG		0x0008

#घोषणा AR2315_PCI_1MS_MASK		0x3FFFF	/* # of AHB clk cycles in 1ms */

#घोषणा AR2315_PCI_MISC_CONFIG		0x000c

#घोषणा AR2315_PCIMISC_TXD_EN	0x00000001	/* Enable TXD क्रम fragments */
#घोषणा AR2315_PCIMISC_CFG_SEL	0x00000002	/* Mem or Config cycles */
#घोषणा AR2315_PCIMISC_GIG_MASK	0x0000000C	/* bits 31-30 क्रम pci req */
#घोषणा AR2315_PCIMISC_RST_MODE	0x00000030
#घोषणा AR2315_PCIRST_INPUT	0x00000000	/* 4:5=0 rst is input */
#घोषणा AR2315_PCIRST_LOW	0x00000010	/* 4:5=1 rst to GND */
#घोषणा AR2315_PCIRST_HIGH	0x00000020	/* 4:5=2 rst to VDD */
#घोषणा AR2315_PCIGRANT_EN	0x00000000	/* 6:7=0 early grant en */
#घोषणा AR2315_PCIGRANT_FRAME	0x00000040	/* 6:7=1 grant रुकोs 4 frame */
#घोषणा AR2315_PCIGRANT_IDLE	0x00000080	/* 6:7=2 grant रुकोs 4 idle */
#घोषणा AR2315_PCIGRANT_GAP	0x00000000	/* 6:7=2 grant रुकोs 4 idle */
#घोषणा AR2315_PCICACHE_DIS	0x00001000	/* PCI बाह्यal access cache
						 * disable */

#घोषणा AR2315_PCI_OUT_TSTAMP		0x0010

#घोषणा AR2315_PCI_UNCACHE_CFG		0x0014

#घोषणा AR2315_PCI_IN_EN		0x0100

#घोषणा AR2315_PCI_IN_EN0	0x01	/* Enable chain 0 */
#घोषणा AR2315_PCI_IN_EN1	0x02	/* Enable chain 1 */
#घोषणा AR2315_PCI_IN_EN2	0x04	/* Enable chain 2 */
#घोषणा AR2315_PCI_IN_EN3	0x08	/* Enable chain 3 */

#घोषणा AR2315_PCI_IN_DIS		0x0104

#घोषणा AR2315_PCI_IN_DIS0	0x01	/* Disable chain 0 */
#घोषणा AR2315_PCI_IN_DIS1	0x02	/* Disable chain 1 */
#घोषणा AR2315_PCI_IN_DIS2	0x04	/* Disable chain 2 */
#घोषणा AR2315_PCI_IN_DIS3	0x08	/* Disable chain 3 */

#घोषणा AR2315_PCI_IN_PTR		0x0200

#घोषणा AR2315_PCI_OUT_EN		0x0400

#घोषणा AR2315_PCI_OUT_EN0	0x01	/* Enable chain 0 */

#घोषणा AR2315_PCI_OUT_DIS		0x0404

#घोषणा AR2315_PCI_OUT_DIS0	0x01	/* Disable chain 0 */

#घोषणा AR2315_PCI_OUT_PTR		0x0408

/* PCI पूर्णांकerrupt status (ग_लिखो one to clear) */
#घोषणा AR2315_PCI_ISR			0x0500

#घोषणा AR2315_PCI_INT_TX	0x00000001	/* Desc In Completed */
#घोषणा AR2315_PCI_INT_TXOK	0x00000002	/* Desc In OK */
#घोषणा AR2315_PCI_INT_TXERR	0x00000004	/* Desc In ERR */
#घोषणा AR2315_PCI_INT_TXEOL	0x00000008	/* Desc In End-of-List */
#घोषणा AR2315_PCI_INT_RX	0x00000010	/* Desc Out Completed */
#घोषणा AR2315_PCI_INT_RXOK	0x00000020	/* Desc Out OK */
#घोषणा AR2315_PCI_INT_RXERR	0x00000040	/* Desc Out ERR */
#घोषणा AR2315_PCI_INT_RXEOL	0x00000080	/* Desc Out EOL */
#घोषणा AR2315_PCI_INT_TXOOD	0x00000200	/* Desc In Out-of-Desc */
#घोषणा AR2315_PCI_INT_DESCMASK	0x0000FFFF	/* Desc Mask */
#घोषणा AR2315_PCI_INT_EXT	0x02000000	/* Extern PCI INTA */
#घोषणा AR2315_PCI_INT_ABORT	0x04000000	/* PCI bus पात event */

/* PCI पूर्णांकerrupt mask */
#घोषणा AR2315_PCI_IMR			0x0504

/* Global PCI पूर्णांकerrupt enable */
#घोषणा AR2315_PCI_IER			0x0508

#घोषणा AR2315_PCI_IER_DISABLE		0x00	/* disable pci पूर्णांकerrupts */
#घोषणा AR2315_PCI_IER_ENABLE		0x01	/* enable pci पूर्णांकerrupts */

#घोषणा AR2315_PCI_HOST_IN_EN		0x0800
#घोषणा AR2315_PCI_HOST_IN_DIS		0x0804
#घोषणा AR2315_PCI_HOST_IN_PTR		0x0810
#घोषणा AR2315_PCI_HOST_OUT_EN		0x0900
#घोषणा AR2315_PCI_HOST_OUT_DIS		0x0904
#घोषणा AR2315_PCI_HOST_OUT_PTR		0x0908

/*
 * PCI पूर्णांकerrupts, which share IP5
 * Keep ordered according to AR2315_PCI_INT_XXX bits
 */
#घोषणा AR2315_PCI_IRQ_EXT		25
#घोषणा AR2315_PCI_IRQ_ABORT		26
#घोषणा AR2315_PCI_IRQ_COUNT		27

/* Arbitrary size of memory region to access the configuration space */
#घोषणा AR2315_PCI_CFG_SIZE	0x00100000

#घोषणा AR2315_PCI_HOST_SLOT	3
#घोषणा AR2315_PCI_HOST_DEVID	((0xff18 << 16) | PCI_VENDOR_ID_ATHEROS)

/*
 * We need some arbitrary non-zero value to be programmed to the BAR1 रेजिस्टर
 * of PCI host controller to enable DMA. The same value should be used as the
 * offset to calculate the physical address of DMA buffer क्रम PCI devices.
 */
#घोषणा AR2315_PCI_HOST_SDRAM_BASEADDR	0x20000000

/* ??? access BAR */
#घोषणा AR2315_PCI_HOST_MBAR0		0x10000000
/* RAM access BAR */
#घोषणा AR2315_PCI_HOST_MBAR1		AR2315_PCI_HOST_SDRAM_BASEADDR
/* ??? access BAR */
#घोषणा AR2315_PCI_HOST_MBAR2		0x30000000

काष्ठा ar2315_pci_ctrl अणु
	व्योम __iomem *cfg_mem;
	व्योम __iomem *mmr_mem;
	अचिन्हित irq;
	अचिन्हित irq_ext;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा pci_controller pci_ctrl;
	काष्ठा resource mem_res;
	काष्ठा resource io_res;
पूर्ण;

अटल अंतरभूत dma_addr_t ar2315_dev_offset(काष्ठा device *dev)
अणु
	अगर (dev && dev_is_pci(dev))
		वापस AR2315_PCI_HOST_SDRAM_BASEADDR;
	वापस 0;
पूर्ण

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस paddr + ar2315_dev_offset(dev);
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस dma_addr - ar2315_dev_offset(dev);
पूर्ण

अटल अंतरभूत काष्ठा ar2315_pci_ctrl *ar2315_pci_bus_to_apc(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	वापस container_of(hose, काष्ठा ar2315_pci_ctrl, pci_ctrl);
पूर्ण

अटल अंतरभूत u32 ar2315_pci_reg_पढ़ो(काष्ठा ar2315_pci_ctrl *apc, u32 reg)
अणु
	वापस __raw_पढ़ोl(apc->mmr_mem + reg);
पूर्ण

अटल अंतरभूत व्योम ar2315_pci_reg_ग_लिखो(काष्ठा ar2315_pci_ctrl *apc, u32 reg,
					u32 val)
अणु
	__raw_ग_लिखोl(val, apc->mmr_mem + reg);
पूर्ण

अटल अंतरभूत व्योम ar2315_pci_reg_mask(काष्ठा ar2315_pci_ctrl *apc, u32 reg,
				       u32 mask, u32 val)
अणु
	u32 ret = ar2315_pci_reg_पढ़ो(apc, reg);

	ret &= ~mask;
	ret |= val;
	ar2315_pci_reg_ग_लिखो(apc, reg, ret);
पूर्ण

अटल पूर्णांक ar2315_pci_cfg_access(काष्ठा ar2315_pci_ctrl *apc, अचिन्हित devfn,
				 पूर्णांक where, पूर्णांक size, u32 *ptr, bool ग_लिखो)
अणु
	पूर्णांक func = PCI_FUNC(devfn);
	पूर्णांक dev = PCI_SLOT(devfn);
	u32 addr = (1 << (13 + dev)) | (func << 8) | (where & ~3);
	u32 mask = 0xffffffff >> 8 * (4 - size);
	u32 sh = (where & 3) * 8;
	u32 value, isr;

	/* Prevent access past the remapped area */
	अगर (addr >= AR2315_PCI_CFG_SIZE || dev > 18)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Clear pending errors */
	ar2315_pci_reg_ग_लिखो(apc, AR2315_PCI_ISR, AR2315_PCI_INT_ABORT);
	/* Select Configuration access */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG, 0,
			    AR2315_PCIMISC_CFG_SEL);

	mb();	/* PCI must see space change beक्रमe we begin */

	value = __raw_पढ़ोl(apc->cfg_mem + addr);

	isr = ar2315_pci_reg_पढ़ो(apc, AR2315_PCI_ISR);

	अगर (isr & AR2315_PCI_INT_ABORT)
		जाओ निकास_err;

	अगर (ग_लिखो) अणु
		value = (value & ~(mask << sh)) | *ptr << sh;
		__raw_ग_लिखोl(value, apc->cfg_mem + addr);
		isr = ar2315_pci_reg_पढ़ो(apc, AR2315_PCI_ISR);
		अगर (isr & AR2315_PCI_INT_ABORT)
			जाओ निकास_err;
	पूर्ण अन्यथा अणु
		*ptr = (value >> sh) & mask;
	पूर्ण

	जाओ निकास;

निकास_err:
	ar2315_pci_reg_ग_लिखो(apc, AR2315_PCI_ISR, AR2315_PCI_INT_ABORT);
	अगर (!ग_लिखो)
		*ptr = 0xffffffff;

निकास:
	/* Select Memory access */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG, AR2315_PCIMISC_CFG_SEL,
			    0);

	वापस isr & AR2315_PCI_INT_ABORT ? PCIBIOS_DEVICE_NOT_FOUND :
					    PCIBIOS_SUCCESSFUL;
पूर्ण

अटल अंतरभूत पूर्णांक ar2315_pci_local_cfg_rd(काष्ठा ar2315_pci_ctrl *apc,
					  अचिन्हित devfn, पूर्णांक where, u32 *val)
अणु
	वापस ar2315_pci_cfg_access(apc, devfn, where, माप(u32), val,
				     false);
पूर्ण

अटल अंतरभूत पूर्णांक ar2315_pci_local_cfg_wr(काष्ठा ar2315_pci_ctrl *apc,
					  अचिन्हित devfn, पूर्णांक where, u32 val)
अणु
	वापस ar2315_pci_cfg_access(apc, devfn, where, माप(u32), &val,
				     true);
पूर्ण

अटल पूर्णांक ar2315_pci_cfg_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित devfn, पूर्णांक where,
			       पूर्णांक size, u32 *value)
अणु
	काष्ठा ar2315_pci_ctrl *apc = ar2315_pci_bus_to_apc(bus);

	अगर (PCI_SLOT(devfn) == AR2315_PCI_HOST_SLOT)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस ar2315_pci_cfg_access(apc, devfn, where, size, value, false);
पूर्ण

अटल पूर्णांक ar2315_pci_cfg_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित devfn, पूर्णांक where,
				पूर्णांक size, u32 value)
अणु
	काष्ठा ar2315_pci_ctrl *apc = ar2315_pci_bus_to_apc(bus);

	अगर (PCI_SLOT(devfn) == AR2315_PCI_HOST_SLOT)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस ar2315_pci_cfg_access(apc, devfn, where, size, &value, true);
पूर्ण

अटल काष्ठा pci_ops ar2315_pci_ops = अणु
	.पढ़ो	= ar2315_pci_cfg_पढ़ो,
	.ग_लिखो	= ar2315_pci_cfg_ग_लिखो,
पूर्ण;

अटल पूर्णांक ar2315_pci_host_setup(काष्ठा ar2315_pci_ctrl *apc)
अणु
	अचिन्हित devfn = PCI_DEVFN(AR2315_PCI_HOST_SLOT, 0);
	पूर्णांक res;
	u32 id;

	res = ar2315_pci_local_cfg_rd(apc, devfn, PCI_VENDOR_ID, &id);
	अगर (res != PCIBIOS_SUCCESSFUL || id != AR2315_PCI_HOST_DEVID)
		वापस -ENODEV;

	/* Program MBARs */
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_0,
				AR2315_PCI_HOST_MBAR0);
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_1,
				AR2315_PCI_HOST_MBAR1);
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_2,
				AR2315_PCI_HOST_MBAR2);

	/* Run */
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_COMMAND, PCI_COMMAND_MEMORY |
				PCI_COMMAND_MASTER | PCI_COMMAND_SPECIAL |
				PCI_COMMAND_INVALIDATE | PCI_COMMAND_PARITY |
				PCI_COMMAND_SERR | PCI_COMMAND_FAST_BACK);

	वापस 0;
पूर्ण

अटल व्योम ar2315_pci_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ar2315_pci_ctrl *apc = irq_desc_get_handler_data(desc);
	u32 pending = ar2315_pci_reg_पढ़ो(apc, AR2315_PCI_ISR) &
		      ar2315_pci_reg_पढ़ो(apc, AR2315_PCI_IMR);
	अचिन्हित pci_irq = 0;

	अगर (pending)
		pci_irq = irq_find_mapping(apc->करोमुख्य, __ffs(pending));

	अगर (pci_irq)
		generic_handle_irq(pci_irq);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

अटल व्योम ar2315_pci_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ar2315_pci_ctrl *apc = irq_data_get_irq_chip_data(d);

	ar2315_pci_reg_mask(apc, AR2315_PCI_IMR, BIT(d->hwirq), 0);
पूर्ण

अटल व्योम ar2315_pci_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा ar2315_pci_ctrl *apc = irq_data_get_irq_chip_data(d);
	u32 m = BIT(d->hwirq);

	ar2315_pci_reg_mask(apc, AR2315_PCI_IMR, m, 0);
	ar2315_pci_reg_ग_लिखो(apc, AR2315_PCI_ISR, m);
पूर्ण

अटल व्योम ar2315_pci_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ar2315_pci_ctrl *apc = irq_data_get_irq_chip_data(d);

	ar2315_pci_reg_mask(apc, AR2315_PCI_IMR, 0, BIT(d->hwirq));
पूर्ण

अटल काष्ठा irq_chip ar2315_pci_irq_chip = अणु
	.name = "AR2315-PCI",
	.irq_mask = ar2315_pci_irq_mask,
	.irq_mask_ack = ar2315_pci_irq_mask_ack,
	.irq_unmask = ar2315_pci_irq_unmask,
पूर्ण;

अटल पूर्णांक ar2315_pci_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित irq,
			      irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &ar2315_pci_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, d->host_data);
	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops ar2315_pci_irq_करोमुख्य_ops = अणु
	.map = ar2315_pci_irq_map,
पूर्ण;

अटल व्योम ar2315_pci_irq_init(काष्ठा ar2315_pci_ctrl *apc)
अणु
	ar2315_pci_reg_mask(apc, AR2315_PCI_IER, AR2315_PCI_IER_ENABLE, 0);
	ar2315_pci_reg_mask(apc, AR2315_PCI_IMR, (AR2315_PCI_INT_ABORT |
			    AR2315_PCI_INT_EXT), 0);

	apc->irq_ext = irq_create_mapping(apc->करोमुख्य, AR2315_PCI_IRQ_EXT);

	irq_set_chained_handler_and_data(apc->irq, ar2315_pci_irq_handler,
					 apc);

	/* Clear any pending Abort or बाह्यal Interrupts
	 * and enable पूर्णांकerrupt processing */
	ar2315_pci_reg_ग_लिखो(apc, AR2315_PCI_ISR, AR2315_PCI_INT_ABORT |
						  AR2315_PCI_INT_EXT);
	ar2315_pci_reg_mask(apc, AR2315_PCI_IER, 0, AR2315_PCI_IER_ENABLE);
पूर्ण

अटल पूर्णांक ar2315_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar2315_pci_ctrl *apc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक irq, err;

	apc = devm_kzalloc(dev, माप(*apc), GFP_KERNEL);
	अगर (!apc)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;
	apc->irq = irq;

	apc->mmr_mem = devm_platक्रमm_ioremap_resource_byname(pdev,
							     "ar2315-pci-ctrl");
	अगर (IS_ERR(apc->mmr_mem))
		वापस PTR_ERR(apc->mmr_mem);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "ar2315-pci-ext");
	अगर (!res)
		वापस -EINVAL;

	apc->mem_res.name = "AR2315 PCI mem space";
	apc->mem_res.parent = res;
	apc->mem_res.start = res->start;
	apc->mem_res.end = res->end;
	apc->mem_res.flags = IORESOURCE_MEM;

	/* Remap PCI config space */
	apc->cfg_mem = devm_ioremap(dev, res->start,
					    AR2315_PCI_CFG_SIZE);
	अगर (!apc->cfg_mem) अणु
		dev_err(dev, "failed to remap PCI config space\n");
		वापस -ENOMEM;
	पूर्ण

	/* Reset the PCI bus by setting bits 5-4 in PCI_MCFG */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG,
			    AR2315_PCIMISC_RST_MODE,
			    AR2315_PCIRST_LOW);
	msleep(100);

	/* Bring the PCI out of reset */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG,
			    AR2315_PCIMISC_RST_MODE,
			    AR2315_PCIRST_HIGH | AR2315_PCICACHE_DIS | 0x8);

	ar2315_pci_reg_ग_लिखो(apc, AR2315_PCI_UNCACHE_CFG,
			     0x1E | /* 1GB uncached */
			     (1 << 5) | /* Enable uncached */
			     (0x2 << 30) /* Base: 0x80000000 */);
	ar2315_pci_reg_पढ़ो(apc, AR2315_PCI_UNCACHE_CFG);

	msleep(500);

	err = ar2315_pci_host_setup(apc);
	अगर (err)
		वापस err;

	apc->करोमुख्य = irq_करोमुख्य_add_linear(शून्य, AR2315_PCI_IRQ_COUNT,
					    &ar2315_pci_irq_करोमुख्य_ops, apc);
	अगर (!apc->करोमुख्य) अणु
		dev_err(dev, "failed to add IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	ar2315_pci_irq_init(apc);

	/* PCI controller करोes not support I/O ports */
	apc->io_res.name = "AR2315 IO space";
	apc->io_res.start = 0;
	apc->io_res.end = 0;
	apc->io_res.flags = IORESOURCE_IO;

	apc->pci_ctrl.pci_ops = &ar2315_pci_ops;
	apc->pci_ctrl.mem_resource = &apc->mem_res;
	apc->pci_ctrl.io_resource = &apc->io_res;

	रेजिस्टर_pci_controller(&apc->pci_ctrl);

	dev_info(dev, "register PCI controller\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ar2315_pci_driver = अणु
	.probe = ar2315_pci_probe,
	.driver = अणु
		.name = "ar2315-pci",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ar2315_pci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ar2315_pci_driver);
पूर्ण
arch_initcall(ar2315_pci_init);

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा ar2315_pci_ctrl *apc = ar2315_pci_bus_to_apc(dev->bus);

	वापस slot ? 0 : apc->irq_ext;
पूर्ण

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
