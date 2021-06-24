<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCIe host controller driver क्रम Xilinx AXI PCIe Bridge
 *
 * Copyright (c) 2012 - 2014 Xilinx, Inc.
 *
 * Based on the Tegra PCIe driver
 *
 * Bits taken from Synopsys DesignWare Host controller driver and
 * ARM PCI Host generic driver.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../pci.h"

/* Register definitions */
#घोषणा XILINX_PCIE_REG_BIR		0x00000130
#घोषणा XILINX_PCIE_REG_IDR		0x00000138
#घोषणा XILINX_PCIE_REG_IMR		0x0000013c
#घोषणा XILINX_PCIE_REG_PSCR		0x00000144
#घोषणा XILINX_PCIE_REG_RPSC		0x00000148
#घोषणा XILINX_PCIE_REG_MSIBASE1	0x0000014c
#घोषणा XILINX_PCIE_REG_MSIBASE2	0x00000150
#घोषणा XILINX_PCIE_REG_RPEFR		0x00000154
#घोषणा XILINX_PCIE_REG_RPIFR1		0x00000158
#घोषणा XILINX_PCIE_REG_RPIFR2		0x0000015c

/* Interrupt रेजिस्टरs definitions */
#घोषणा XILINX_PCIE_INTR_LINK_DOWN	BIT(0)
#घोषणा XILINX_PCIE_INTR_ECRC_ERR	BIT(1)
#घोषणा XILINX_PCIE_INTR_STR_ERR	BIT(2)
#घोषणा XILINX_PCIE_INTR_HOT_RESET	BIT(3)
#घोषणा XILINX_PCIE_INTR_CFG_TIMEOUT	BIT(8)
#घोषणा XILINX_PCIE_INTR_CORRECTABLE	BIT(9)
#घोषणा XILINX_PCIE_INTR_NONFATAL	BIT(10)
#घोषणा XILINX_PCIE_INTR_FATAL		BIT(11)
#घोषणा XILINX_PCIE_INTR_INTX		BIT(16)
#घोषणा XILINX_PCIE_INTR_MSI		BIT(17)
#घोषणा XILINX_PCIE_INTR_SLV_UNSUPP	BIT(20)
#घोषणा XILINX_PCIE_INTR_SLV_UNEXP	BIT(21)
#घोषणा XILINX_PCIE_INTR_SLV_COMPL	BIT(22)
#घोषणा XILINX_PCIE_INTR_SLV_ERRP	BIT(23)
#घोषणा XILINX_PCIE_INTR_SLV_CMPABT	BIT(24)
#घोषणा XILINX_PCIE_INTR_SLV_ILLBUR	BIT(25)
#घोषणा XILINX_PCIE_INTR_MST_DECERR	BIT(26)
#घोषणा XILINX_PCIE_INTR_MST_SLVERR	BIT(27)
#घोषणा XILINX_PCIE_INTR_MST_ERRP	BIT(28)
#घोषणा XILINX_PCIE_IMR_ALL_MASK	0x1FF30FED
#घोषणा XILINX_PCIE_IMR_ENABLE_MASK	0x1FF30F0D
#घोषणा XILINX_PCIE_IDR_ALL_MASK	0xFFFFFFFF

/* Root Port Error FIFO Read Register definitions */
#घोषणा XILINX_PCIE_RPEFR_ERR_VALID	BIT(18)
#घोषणा XILINX_PCIE_RPEFR_REQ_ID	GENMASK(15, 0)
#घोषणा XILINX_PCIE_RPEFR_ALL_MASK	0xFFFFFFFF

/* Root Port Interrupt FIFO Read Register 1 definitions */
#घोषणा XILINX_PCIE_RPIFR1_INTR_VALID	BIT(31)
#घोषणा XILINX_PCIE_RPIFR1_MSI_INTR	BIT(30)
#घोषणा XILINX_PCIE_RPIFR1_INTR_MASK	GENMASK(28, 27)
#घोषणा XILINX_PCIE_RPIFR1_ALL_MASK	0xFFFFFFFF
#घोषणा XILINX_PCIE_RPIFR1_INTR_SHIFT	27

/* Bridge Info Register definitions */
#घोषणा XILINX_PCIE_BIR_ECAM_SZ_MASK	GENMASK(18, 16)
#घोषणा XILINX_PCIE_BIR_ECAM_SZ_SHIFT	16

/* Root Port Interrupt FIFO Read Register 2 definitions */
#घोषणा XILINX_PCIE_RPIFR2_MSG_DATA	GENMASK(15, 0)

/* Root Port Status/control Register definitions */
#घोषणा XILINX_PCIE_REG_RPSC_BEN	BIT(0)

/* Phy Status/Control Register definitions */
#घोषणा XILINX_PCIE_REG_PSCR_LNKUP	BIT(11)

/* Number of MSI IRQs */
#घोषणा XILINX_NUM_MSI_IRQS		128

/**
 * काष्ठा xilinx_pcie_port - PCIe port inक्रमmation
 * @reg_base: IO Mapped Register Base
 * @dev: Device poपूर्णांकer
 * @msi_map: Biपंचांगap of allocated MSIs
 * @map_lock: Mutex protecting the MSI allocation
 * @msi_करोमुख्य: MSI IRQ करोमुख्य poपूर्णांकer
 * @leg_करोमुख्य: Legacy IRQ करोमुख्य poपूर्णांकer
 * @resources: Bus Resources
 */
काष्ठा xilinx_pcie_port अणु
	व्योम __iomem *reg_base;
	काष्ठा device *dev;
	अचिन्हित दीर्घ msi_map[BITS_TO_LONGS(XILINX_NUM_MSI_IRQS)];
	काष्ठा mutex map_lock;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा irq_करोमुख्य *leg_करोमुख्य;
	काष्ठा list_head resources;
पूर्ण;

अटल अंतरभूत u32 pcie_पढ़ो(काष्ठा xilinx_pcie_port *port, u32 reg)
अणु
	वापस पढ़ोl(port->reg_base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_ग_लिखो(काष्ठा xilinx_pcie_port *port, u32 val, u32 reg)
अणु
	ग_लिखोl(val, port->reg_base + reg);
पूर्ण

अटल अंतरभूत bool xilinx_pcie_link_up(काष्ठा xilinx_pcie_port *port)
अणु
	वापस (pcie_पढ़ो(port, XILINX_PCIE_REG_PSCR) &
		XILINX_PCIE_REG_PSCR_LNKUP) ? 1 : 0;
पूर्ण

/**
 * xilinx_pcie_clear_err_पूर्णांकerrupts - Clear Error Interrupts
 * @port: PCIe port inक्रमmation
 */
अटल व्योम xilinx_pcie_clear_err_पूर्णांकerrupts(काष्ठा xilinx_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	अचिन्हित दीर्घ val = pcie_पढ़ो(port, XILINX_PCIE_REG_RPEFR);

	अगर (val & XILINX_PCIE_RPEFR_ERR_VALID) अणु
		dev_dbg(dev, "Requester ID %lu\n",
			val & XILINX_PCIE_RPEFR_REQ_ID);
		pcie_ग_लिखो(port, XILINX_PCIE_RPEFR_ALL_MASK,
			   XILINX_PCIE_REG_RPEFR);
	पूर्ण
पूर्ण

/**
 * xilinx_pcie_valid_device - Check अगर a valid device is present on bus
 * @bus: PCI Bus काष्ठाure
 * @devfn: device/function
 *
 * Return: 'true' on success and 'false' अगर invalid device is found
 */
अटल bool xilinx_pcie_valid_device(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा xilinx_pcie_port *port = bus->sysdata;

	/* Check अगर link is up when trying to access करोwnstream ports */
	अगर (!pci_is_root_bus(bus)) अणु
		अगर (!xilinx_pcie_link_up(port))
			वापस false;
	पूर्ण अन्यथा अगर (devfn > 0) अणु
		/* Only one device करोwn on each root port */
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * xilinx_pcie_map_bus - Get configuration base
 * @bus: PCI Bus काष्ठाure
 * @devfn: Device/function
 * @where: Offset from base
 *
 * Return: Base address of the configuration space needed to be
 *	   accessed.
 */
अटल व्योम __iomem *xilinx_pcie_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा xilinx_pcie_port *port = bus->sysdata;

	अगर (!xilinx_pcie_valid_device(bus, devfn))
		वापस शून्य;

	वापस port->reg_base + PCIE_ECAM_OFFSET(bus->number, devfn, where);
पूर्ण

/* PCIe operations */
अटल काष्ठा pci_ops xilinx_pcie_ops = अणु
	.map_bus = xilinx_pcie_map_bus,
	.पढ़ो	= pci_generic_config_पढ़ो,
	.ग_लिखो	= pci_generic_config_ग_लिखो,
पूर्ण;

/* MSI functions */

अटल व्योम xilinx_msi_top_irq_ack(काष्ठा irq_data *d)
अणु
	/*
	 * xilinx_pcie_पूर्णांकr_handler() will have perक्रमmed the Ack.
	 * Eventually, this should be fixed and the Ack be moved in
	 * the respective callbacks क्रम INTx and MSI.
	 */
पूर्ण

अटल काष्ठा irq_chip xilinx_msi_top_chip = अणु
	.name		= "PCIe MSI",
	.irq_ack	= xilinx_msi_top_irq_ack,
पूर्ण;

अटल पूर्णांक xilinx_msi_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम xilinx_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा xilinx_pcie_port *pcie = irq_data_get_irq_chip_data(data);
	phys_addr_t pa = ALIGN_DOWN(virt_to_phys(pcie), SZ_4K);

	msg->address_lo = lower_32_bits(pa);
	msg->address_hi = upper_32_bits(pa);
	msg->data = data->hwirq;
पूर्ण

अटल काष्ठा irq_chip xilinx_msi_bottom_chip = अणु
	.name			= "Xilinx MSI",
	.irq_set_affinity 	= xilinx_msi_set_affinity,
	.irq_compose_msi_msg	= xilinx_compose_msi_msg,
पूर्ण;

अटल पूर्णांक xilinx_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा xilinx_pcie_port *port = करोमुख्य->host_data;
	पूर्णांक hwirq, i;

	mutex_lock(&port->map_lock);

	hwirq = biपंचांगap_find_मुक्त_region(port->msi_map, XILINX_NUM_MSI_IRQS, order_base_2(nr_irqs));

	mutex_unlock(&port->map_lock);

	अगर (hwirq < 0)
		वापस -ENOSPC;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &xilinx_msi_bottom_chip, करोमुख्य->host_data,
				    handle_edge_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम xilinx_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा xilinx_pcie_port *port = करोमुख्य->host_data;

	mutex_lock(&port->map_lock);

	biपंचांगap_release_region(port->msi_map, d->hwirq, order_base_2(nr_irqs));

	mutex_unlock(&port->map_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xilinx_msi_करोमुख्य_ops = अणु
	.alloc	= xilinx_msi_करोमुख्य_alloc,
	.मुक्त	= xilinx_msi_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info xilinx_msi_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.chip	= &xilinx_msi_top_chip,
पूर्ण;

अटल पूर्णांक xilinx_allocate_msi_करोमुख्यs(काष्ठा xilinx_pcie_port *pcie)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(pcie->dev);
	काष्ठा irq_करोमुख्य *parent;

	parent = irq_करोमुख्य_create_linear(fwnode, XILINX_NUM_MSI_IRQS,
					  &xilinx_msi_करोमुख्य_ops, pcie);
	अगर (!parent) अणु
		dev_err(pcie->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण
	irq_करोमुख्य_update_bus_token(parent, DOMAIN_BUS_NEXUS);

	pcie->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode, &xilinx_msi_info, parent);
	अगर (!pcie->msi_करोमुख्य) अणु
		dev_err(pcie->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(parent);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xilinx_मुक्त_msi_करोमुख्यs(काष्ठा xilinx_pcie_port *pcie)
अणु
	काष्ठा irq_करोमुख्य *parent = pcie->msi_करोमुख्य->parent;

	irq_करोमुख्य_हटाओ(pcie->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(parent);
पूर्ण

/* INTx Functions */

/**
 * xilinx_pcie_पूर्णांकx_map - Set the handler क्रम the INTx and mark IRQ as valid
 * @करोमुख्य: IRQ करोमुख्य
 * @irq: Virtual IRQ number
 * @hwirq: HW पूर्णांकerrupt number
 *
 * Return: Always वापसs 0.
 */
अटल पूर्णांक xilinx_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

/* INTx IRQ Doमुख्य operations */
अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = xilinx_pcie_पूर्णांकx_map,
	.xlate = pci_irqd_पूर्णांकx_xlate,
पूर्ण;

/* PCIe HW Functions */

/**
 * xilinx_pcie_पूर्णांकr_handler - Interrupt Service Handler
 * @irq: IRQ number
 * @data: PCIe port inक्रमmation
 *
 * Return: IRQ_HANDLED on success and IRQ_NONE on failure
 */
अटल irqवापस_t xilinx_pcie_पूर्णांकr_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xilinx_pcie_port *port = (काष्ठा xilinx_pcie_port *)data;
	काष्ठा device *dev = port->dev;
	u32 val, mask, status;

	/* Read पूर्णांकerrupt decode and mask रेजिस्टरs */
	val = pcie_पढ़ो(port, XILINX_PCIE_REG_IDR);
	mask = pcie_पढ़ो(port, XILINX_PCIE_REG_IMR);

	status = val & mask;
	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & XILINX_PCIE_INTR_LINK_DOWN)
		dev_warn(dev, "Link Down\n");

	अगर (status & XILINX_PCIE_INTR_ECRC_ERR)
		dev_warn(dev, "ECRC failed\n");

	अगर (status & XILINX_PCIE_INTR_STR_ERR)
		dev_warn(dev, "Streaming error\n");

	अगर (status & XILINX_PCIE_INTR_HOT_RESET)
		dev_info(dev, "Hot reset\n");

	अगर (status & XILINX_PCIE_INTR_CFG_TIMEOUT)
		dev_warn(dev, "ECAM access timeout\n");

	अगर (status & XILINX_PCIE_INTR_CORRECTABLE) अणु
		dev_warn(dev, "Correctable error message\n");
		xilinx_pcie_clear_err_पूर्णांकerrupts(port);
	पूर्ण

	अगर (status & XILINX_PCIE_INTR_NONFATAL) अणु
		dev_warn(dev, "Non fatal error message\n");
		xilinx_pcie_clear_err_पूर्णांकerrupts(port);
	पूर्ण

	अगर (status & XILINX_PCIE_INTR_FATAL) अणु
		dev_warn(dev, "Fatal error message\n");
		xilinx_pcie_clear_err_पूर्णांकerrupts(port);
	पूर्ण

	अगर (status & (XILINX_PCIE_INTR_INTX | XILINX_PCIE_INTR_MSI)) अणु
		अचिन्हित पूर्णांक irq;

		val = pcie_पढ़ो(port, XILINX_PCIE_REG_RPIFR1);

		/* Check whether पूर्णांकerrupt valid */
		अगर (!(val & XILINX_PCIE_RPIFR1_INTR_VALID)) अणु
			dev_warn(dev, "RP Intr FIFO1 read error\n");
			जाओ error;
		पूर्ण

		/* Decode the IRQ number */
		अगर (val & XILINX_PCIE_RPIFR1_MSI_INTR) अणु
			val = pcie_पढ़ो(port, XILINX_PCIE_REG_RPIFR2) &
				XILINX_PCIE_RPIFR2_MSG_DATA;
			irq = irq_find_mapping(port->msi_करोमुख्य->parent, val);
		पूर्ण अन्यथा अणु
			val = (val & XILINX_PCIE_RPIFR1_INTR_MASK) >>
				XILINX_PCIE_RPIFR1_INTR_SHIFT;
			irq = irq_find_mapping(port->leg_करोमुख्य, val);
		पूर्ण

		/* Clear पूर्णांकerrupt FIFO रेजिस्टर 1 */
		pcie_ग_लिखो(port, XILINX_PCIE_RPIFR1_ALL_MASK,
			   XILINX_PCIE_REG_RPIFR1);

		अगर (irq)
			generic_handle_irq(irq);
	पूर्ण

	अगर (status & XILINX_PCIE_INTR_SLV_UNSUPP)
		dev_warn(dev, "Slave unsupported request\n");

	अगर (status & XILINX_PCIE_INTR_SLV_UNEXP)
		dev_warn(dev, "Slave unexpected completion\n");

	अगर (status & XILINX_PCIE_INTR_SLV_COMPL)
		dev_warn(dev, "Slave completion timeout\n");

	अगर (status & XILINX_PCIE_INTR_SLV_ERRP)
		dev_warn(dev, "Slave Error Poison\n");

	अगर (status & XILINX_PCIE_INTR_SLV_CMPABT)
		dev_warn(dev, "Slave Completer Abort\n");

	अगर (status & XILINX_PCIE_INTR_SLV_ILLBUR)
		dev_warn(dev, "Slave Illegal Burst\n");

	अगर (status & XILINX_PCIE_INTR_MST_DECERR)
		dev_warn(dev, "Master decode error\n");

	अगर (status & XILINX_PCIE_INTR_MST_SLVERR)
		dev_warn(dev, "Master slave error\n");

	अगर (status & XILINX_PCIE_INTR_MST_ERRP)
		dev_warn(dev, "Master error poison\n");

error:
	/* Clear the Interrupt Decode रेजिस्टर */
	pcie_ग_लिखो(port, status, XILINX_PCIE_REG_IDR);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * xilinx_pcie_init_irq_करोमुख्य - Initialize IRQ करोमुख्य
 * @port: PCIe port inक्रमmation
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_pcie_init_irq_करोमुख्य(काष्ठा xilinx_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा device_node *pcie_पूर्णांकc_node;
	पूर्णांक ret;

	/* Setup INTx */
	pcie_पूर्णांकc_node = of_get_next_child(dev->of_node, शून्य);
	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "No PCIe Intc node found\n");
		वापस -ENODEV;
	पूर्ण

	port->leg_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
						 &पूर्णांकx_करोमुख्य_ops,
						 port);
	of_node_put(pcie_पूर्णांकc_node);
	अगर (!port->leg_करोमुख्य) अणु
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	/* Setup MSI */
	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		phys_addr_t pa = ALIGN_DOWN(virt_to_phys(port), SZ_4K);

		ret = xilinx_allocate_msi_करोमुख्यs(port);
		अगर (ret)
			वापस ret;

		pcie_ग_लिखो(port, upper_32_bits(pa), XILINX_PCIE_REG_MSIBASE1);
		pcie_ग_लिखो(port, lower_32_bits(pa), XILINX_PCIE_REG_MSIBASE2);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xilinx_pcie_init_port - Initialize hardware
 * @port: PCIe port inक्रमmation
 */
अटल व्योम xilinx_pcie_init_port(काष्ठा xilinx_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;

	अगर (xilinx_pcie_link_up(port))
		dev_info(dev, "PCIe Link is UP\n");
	अन्यथा
		dev_info(dev, "PCIe Link is DOWN\n");

	/* Disable all पूर्णांकerrupts */
	pcie_ग_लिखो(port, ~XILINX_PCIE_IDR_ALL_MASK,
		   XILINX_PCIE_REG_IMR);

	/* Clear pending पूर्णांकerrupts */
	pcie_ग_लिखो(port, pcie_पढ़ो(port, XILINX_PCIE_REG_IDR) &
			 XILINX_PCIE_IMR_ALL_MASK,
		   XILINX_PCIE_REG_IDR);

	/* Enable all पूर्णांकerrupts we handle */
	pcie_ग_लिखो(port, XILINX_PCIE_IMR_ENABLE_MASK, XILINX_PCIE_REG_IMR);

	/* Enable the Bridge enable bit */
	pcie_ग_लिखो(port, pcie_पढ़ो(port, XILINX_PCIE_REG_RPSC) |
			 XILINX_PCIE_REG_RPSC_BEN,
		   XILINX_PCIE_REG_RPSC);
पूर्ण

/**
 * xilinx_pcie_parse_dt - Parse Device tree
 * @port: PCIe port inक्रमmation
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_pcie_parse_dt(काष्ठा xilinx_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource regs;
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;

	err = of_address_to_resource(node, 0, &regs);
	अगर (err) अणु
		dev_err(dev, "missing \"reg\" property\n");
		वापस err;
	पूर्ण

	port->reg_base = devm_pci_remap_cfg_resource(dev, &regs);
	अगर (IS_ERR(port->reg_base))
		वापस PTR_ERR(port->reg_base);

	irq = irq_of_parse_and_map(node, 0);
	err = devm_request_irq(dev, irq, xilinx_pcie_पूर्णांकr_handler,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       "xilinx-pcie", port);
	अगर (err) अणु
		dev_err(dev, "unable to request irq %d\n", irq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xilinx_pcie_probe - Probe function
 * @pdev: Platक्रमm device poपूर्णांकer
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा xilinx_pcie_port *port;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक err;

	अगर (!dev->of_node)
		वापस -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*port));
	अगर (!bridge)
		वापस -ENODEV;

	port = pci_host_bridge_priv(bridge);
	mutex_init(&port->map_lock);
	port->dev = dev;

	err = xilinx_pcie_parse_dt(port);
	अगर (err) अणु
		dev_err(dev, "Parsing DT failed\n");
		वापस err;
	पूर्ण

	xilinx_pcie_init_port(port);

	err = xilinx_pcie_init_irq_करोमुख्य(port);
	अगर (err) अणु
		dev_err(dev, "Failed creating IRQ Domain\n");
		वापस err;
	पूर्ण

	bridge->sysdata = port;
	bridge->ops = &xilinx_pcie_ops;

	err = pci_host_probe(bridge);
	अगर (err)
		xilinx_मुक्त_msi_करोमुख्यs(port);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id xilinx_pcie_of_match[] = अणु
	अणु .compatible = "xlnx,axi-pcie-host-1.00.a", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver xilinx_pcie_driver = अणु
	.driver = अणु
		.name = "xilinx-pcie",
		.of_match_table = xilinx_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = xilinx_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(xilinx_pcie_driver);
