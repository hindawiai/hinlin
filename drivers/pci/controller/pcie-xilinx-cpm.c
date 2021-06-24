<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCIe host controller driver क्रम Xilinx Versal CPM DMA Bridge
 *
 * (C) Copyright 2019 - 2020, Xilinx, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci-ecam.h>

#समावेश "../pci.h"

/* Register definitions */
#घोषणा XILINX_CPM_PCIE_REG_IDR		0x00000E10
#घोषणा XILINX_CPM_PCIE_REG_IMR		0x00000E14
#घोषणा XILINX_CPM_PCIE_REG_PSCR	0x00000E1C
#घोषणा XILINX_CPM_PCIE_REG_RPSC	0x00000E20
#घोषणा XILINX_CPM_PCIE_REG_RPEFR	0x00000E2C
#घोषणा XILINX_CPM_PCIE_REG_IDRN	0x00000E38
#घोषणा XILINX_CPM_PCIE_REG_IDRN_MASK	0x00000E3C
#घोषणा XILINX_CPM_PCIE_MISC_IR_STATUS	0x00000340
#घोषणा XILINX_CPM_PCIE_MISC_IR_ENABLE	0x00000348
#घोषणा XILINX_CPM_PCIE_MISC_IR_LOCAL	BIT(1)

/* Interrupt रेजिस्टरs definitions */
#घोषणा XILINX_CPM_PCIE_INTR_LINK_DOWN		0
#घोषणा XILINX_CPM_PCIE_INTR_HOT_RESET		3
#घोषणा XILINX_CPM_PCIE_INTR_CFG_PCIE_TIMEOUT	4
#घोषणा XILINX_CPM_PCIE_INTR_CFG_TIMEOUT	8
#घोषणा XILINX_CPM_PCIE_INTR_CORRECTABLE	9
#घोषणा XILINX_CPM_PCIE_INTR_NONFATAL		10
#घोषणा XILINX_CPM_PCIE_INTR_FATAL		11
#घोषणा XILINX_CPM_PCIE_INTR_CFG_ERR_POISON	12
#घोषणा XILINX_CPM_PCIE_INTR_PME_TO_ACK_RCVD	15
#घोषणा XILINX_CPM_PCIE_INTR_INTX		16
#घोषणा XILINX_CPM_PCIE_INTR_PM_PME_RCVD	17
#घोषणा XILINX_CPM_PCIE_INTR_SLV_UNSUPP		20
#घोषणा XILINX_CPM_PCIE_INTR_SLV_UNEXP		21
#घोषणा XILINX_CPM_PCIE_INTR_SLV_COMPL		22
#घोषणा XILINX_CPM_PCIE_INTR_SLV_ERRP		23
#घोषणा XILINX_CPM_PCIE_INTR_SLV_CMPABT		24
#घोषणा XILINX_CPM_PCIE_INTR_SLV_ILLBUR		25
#घोषणा XILINX_CPM_PCIE_INTR_MST_DECERR		26
#घोषणा XILINX_CPM_PCIE_INTR_MST_SLVERR		27
#घोषणा XILINX_CPM_PCIE_INTR_SLV_PCIE_TIMEOUT	28

#घोषणा IMR(x) BIT(XILINX_CPM_PCIE_INTR_ ##x)

#घोषणा XILINX_CPM_PCIE_IMR_ALL_MASK			\
	(						\
		IMR(LINK_DOWN)		|		\
		IMR(HOT_RESET)		|		\
		IMR(CFG_PCIE_TIMEOUT)	|		\
		IMR(CFG_TIMEOUT)	|		\
		IMR(CORRECTABLE)	|		\
		IMR(NONFATAL)		|		\
		IMR(FATAL)		|		\
		IMR(CFG_ERR_POISON)	|		\
		IMR(PME_TO_ACK_RCVD)	|		\
		IMR(INTX)		|		\
		IMR(PM_PME_RCVD)	|		\
		IMR(SLV_UNSUPP)		|		\
		IMR(SLV_UNEXP)		|		\
		IMR(SLV_COMPL)		|		\
		IMR(SLV_ERRP)		|		\
		IMR(SLV_CMPABT)		|		\
		IMR(SLV_ILLBUR)		|		\
		IMR(MST_DECERR)		|		\
		IMR(MST_SLVERR)		|		\
		IMR(SLV_PCIE_TIMEOUT)			\
	)

#घोषणा XILINX_CPM_PCIE_IDR_ALL_MASK		0xFFFFFFFF
#घोषणा XILINX_CPM_PCIE_IDRN_MASK		GENMASK(19, 16)
#घोषणा XILINX_CPM_PCIE_IDRN_SHIFT		16

/* Root Port Error FIFO Read Register definitions */
#घोषणा XILINX_CPM_PCIE_RPEFR_ERR_VALID		BIT(18)
#घोषणा XILINX_CPM_PCIE_RPEFR_REQ_ID		GENMASK(15, 0)
#घोषणा XILINX_CPM_PCIE_RPEFR_ALL_MASK		0xFFFFFFFF

/* Root Port Status/control Register definitions */
#घोषणा XILINX_CPM_PCIE_REG_RPSC_BEN		BIT(0)

/* Phy Status/Control Register definitions */
#घोषणा XILINX_CPM_PCIE_REG_PSCR_LNKUP		BIT(11)

/**
 * काष्ठा xilinx_cpm_pcie_port - PCIe port inक्रमmation
 * @reg_base: Bridge Register Base
 * @cpm_base: CPM System Level Control and Status Register(SLCR) Base
 * @dev: Device poपूर्णांकer
 * @पूर्णांकx_करोमुख्य: Legacy IRQ करोमुख्य poपूर्णांकer
 * @cpm_करोमुख्य: CPM IRQ करोमुख्य poपूर्णांकer
 * @cfg: Holds mappings of config space winकरोw
 * @पूर्णांकx_irq: legacy पूर्णांकerrupt number
 * @irq: Error पूर्णांकerrupt number
 * @lock: lock protecting shared रेजिस्टर access
 */
काष्ठा xilinx_cpm_pcie_port अणु
	व्योम __iomem			*reg_base;
	व्योम __iomem			*cpm_base;
	काष्ठा device			*dev;
	काष्ठा irq_करोमुख्य		*पूर्णांकx_करोमुख्य;
	काष्ठा irq_करोमुख्य		*cpm_करोमुख्य;
	काष्ठा pci_config_winकरोw	*cfg;
	पूर्णांक				पूर्णांकx_irq;
	पूर्णांक				irq;
	raw_spinlock_t			lock;
पूर्ण;

अटल u32 pcie_पढ़ो(काष्ठा xilinx_cpm_pcie_port *port, u32 reg)
अणु
	वापस पढ़ोl_relaxed(port->reg_base + reg);
पूर्ण

अटल व्योम pcie_ग_लिखो(काष्ठा xilinx_cpm_pcie_port *port,
		       u32 val, u32 reg)
अणु
	ग_लिखोl_relaxed(val, port->reg_base + reg);
पूर्ण

अटल bool cpm_pcie_link_up(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	वापस (pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_PSCR) &
		XILINX_CPM_PCIE_REG_PSCR_LNKUP);
पूर्ण

अटल व्योम cpm_pcie_clear_err_पूर्णांकerrupts(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	अचिन्हित दीर्घ val = pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_RPEFR);

	अगर (val & XILINX_CPM_PCIE_RPEFR_ERR_VALID) अणु
		dev_dbg(port->dev, "Requester ID %lu\n",
			val & XILINX_CPM_PCIE_RPEFR_REQ_ID);
		pcie_ग_लिखो(port, XILINX_CPM_PCIE_RPEFR_ALL_MASK,
			   XILINX_CPM_PCIE_REG_RPEFR);
	पूर्ण
पूर्ण

अटल व्योम xilinx_cpm_mask_leg_irq(काष्ठा irq_data *data)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 mask;
	u32 val;

	mask = BIT(data->hwirq + XILINX_CPM_PCIE_IDRN_SHIFT);
	raw_spin_lock_irqsave(&port->lock, flags);
	val = pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IDRN_MASK);
	pcie_ग_लिखो(port, (val & (~mask)), XILINX_CPM_PCIE_REG_IDRN_MASK);
	raw_spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम xilinx_cpm_unmask_leg_irq(काष्ठा irq_data *data)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 mask;
	u32 val;

	mask = BIT(data->hwirq + XILINX_CPM_PCIE_IDRN_SHIFT);
	raw_spin_lock_irqsave(&port->lock, flags);
	val = pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IDRN_MASK);
	pcie_ग_लिखो(port, (val | mask), XILINX_CPM_PCIE_REG_IDRN_MASK);
	raw_spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल काष्ठा irq_chip xilinx_cpm_leg_irq_chip = अणु
	.name		= "INTx",
	.irq_mask	= xilinx_cpm_mask_leg_irq,
	.irq_unmask	= xilinx_cpm_unmask_leg_irq,
पूर्ण;

/**
 * xilinx_cpm_pcie_पूर्णांकx_map - Set the handler क्रम the INTx and mark IRQ as valid
 * @करोमुख्य: IRQ करोमुख्य
 * @irq: Virtual IRQ number
 * @hwirq: HW पूर्णांकerrupt number
 *
 * Return: Always वापसs 0.
 */
अटल पूर्णांक xilinx_cpm_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &xilinx_cpm_leg_irq_chip,
				 handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_status_flags(irq, IRQ_LEVEL);

	वापस 0;
पूर्ण

/* INTx IRQ Doमुख्य operations */
अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = xilinx_cpm_pcie_पूर्णांकx_map,
पूर्ण;

अटल व्योम xilinx_cpm_pcie_पूर्णांकx_flow(काष्ठा irq_desc *desc)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	chained_irq_enter(chip, desc);

	val = FIELD_GET(XILINX_CPM_PCIE_IDRN_MASK,
			pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IDRN));

	क्रम_each_set_bit(i, &val, PCI_NUM_INTX)
		generic_handle_irq(irq_find_mapping(port->पूर्णांकx_करोमुख्य, i));

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम xilinx_cpm_mask_event_irq(काष्ठा irq_data *d)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_data_get_irq_chip_data(d);
	u32 val;

	raw_spin_lock(&port->lock);
	val = pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IMR);
	val &= ~BIT(d->hwirq);
	pcie_ग_लिखो(port, val, XILINX_CPM_PCIE_REG_IMR);
	raw_spin_unlock(&port->lock);
पूर्ण

अटल व्योम xilinx_cpm_unmask_event_irq(काष्ठा irq_data *d)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_data_get_irq_chip_data(d);
	u32 val;

	raw_spin_lock(&port->lock);
	val = pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IMR);
	val |= BIT(d->hwirq);
	pcie_ग_लिखो(port, val, XILINX_CPM_PCIE_REG_IMR);
	raw_spin_unlock(&port->lock);
पूर्ण

अटल काष्ठा irq_chip xilinx_cpm_event_irq_chip = अणु
	.name		= "RC-Event",
	.irq_mask	= xilinx_cpm_mask_event_irq,
	.irq_unmask	= xilinx_cpm_unmask_event_irq,
पूर्ण;

अटल पूर्णांक xilinx_cpm_pcie_event_map(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &xilinx_cpm_event_irq_chip,
				 handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_status_flags(irq, IRQ_LEVEL);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops event_करोमुख्य_ops = अणु
	.map = xilinx_cpm_pcie_event_map,
पूर्ण;

अटल व्योम xilinx_cpm_pcie_event_flow(काष्ठा irq_desc *desc)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	chained_irq_enter(chip, desc);
	val =  pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IDR);
	val &= pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IMR);
	क्रम_each_set_bit(i, &val, 32)
		generic_handle_irq(irq_find_mapping(port->cpm_करोमुख्य, i));
	pcie_ग_लिखो(port, val, XILINX_CPM_PCIE_REG_IDR);

	/*
	 * XILINX_CPM_PCIE_MISC_IR_STATUS रेजिस्टर is mapped to
	 * CPM SLCR block.
	 */
	val = पढ़ोl_relaxed(port->cpm_base + XILINX_CPM_PCIE_MISC_IR_STATUS);
	अगर (val)
		ग_लिखोl_relaxed(val,
			       port->cpm_base + XILINX_CPM_PCIE_MISC_IR_STATUS);

	chained_irq_निकास(chip, desc);
पूर्ण

#घोषणा _IC(x, s)                              \
	[XILINX_CPM_PCIE_INTR_ ## x] = अणु __stringअगरy(x), s पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर      *sym;
	स्थिर अक्षर      *str;
पूर्ण पूर्णांकr_cause[32] = अणु
	_IC(LINK_DOWN,		"Link Down"),
	_IC(HOT_RESET,		"Hot reset"),
	_IC(CFG_TIMEOUT,	"ECAM access timeout"),
	_IC(CORRECTABLE,	"Correctable error message"),
	_IC(NONFATAL,		"Non fatal error message"),
	_IC(FATAL,		"Fatal error message"),
	_IC(SLV_UNSUPP,		"Slave unsupported request"),
	_IC(SLV_UNEXP,		"Slave unexpected completion"),
	_IC(SLV_COMPL,		"Slave completion timeout"),
	_IC(SLV_ERRP,		"Slave Error Poison"),
	_IC(SLV_CMPABT,		"Slave Completer Abort"),
	_IC(SLV_ILLBUR,		"Slave Illegal Burst"),
	_IC(MST_DECERR,		"Master decode error"),
	_IC(MST_SLVERR,		"Master slave error"),
	_IC(CFG_PCIE_TIMEOUT,	"PCIe ECAM access timeout"),
	_IC(CFG_ERR_POISON,	"ECAM poisoned completion received"),
	_IC(PME_TO_ACK_RCVD,	"PME_TO_ACK message received"),
	_IC(PM_PME_RCVD,	"PM_PME message received"),
	_IC(SLV_PCIE_TIMEOUT,	"PCIe completion timeout received"),
पूर्ण;

अटल irqवापस_t xilinx_cpm_pcie_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xilinx_cpm_pcie_port *port = dev_id;
	काष्ठा device *dev = port->dev;
	काष्ठा irq_data *d;

	d = irq_करोमुख्य_get_irq_data(port->cpm_करोमुख्य, irq);

	चयन (d->hwirq) अणु
	हाल XILINX_CPM_PCIE_INTR_CORRECTABLE:
	हाल XILINX_CPM_PCIE_INTR_NONFATAL:
	हाल XILINX_CPM_PCIE_INTR_FATAL:
		cpm_pcie_clear_err_पूर्णांकerrupts(port);
		fallthrough;

	शेष:
		अगर (पूर्णांकr_cause[d->hwirq].str)
			dev_warn(dev, "%s\n", पूर्णांकr_cause[d->hwirq].str);
		अन्यथा
			dev_warn(dev, "Unknown IRQ %ld\n", d->hwirq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xilinx_cpm_मुक्त_irq_करोमुख्यs(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	अगर (port->पूर्णांकx_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(port->पूर्णांकx_करोमुख्य);
		port->पूर्णांकx_करोमुख्य = शून्य;
	पूर्ण

	अगर (port->cpm_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(port->cpm_करोमुख्य);
		port->cpm_करोमुख्य = शून्य;
	पूर्ण
पूर्ण

/**
 * xilinx_cpm_pcie_init_irq_करोमुख्य - Initialize IRQ करोमुख्य
 * @port: PCIe port inक्रमmation
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_cpm_pcie_init_irq_करोमुख्य(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *pcie_पूर्णांकc_node;

	/* Setup INTx */
	pcie_पूर्णांकc_node = of_get_next_child(node, शून्य);
	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "No PCIe Intc node found\n");
		वापस -EINVAL;
	पूर्ण

	port->cpm_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, 32,
						 &event_करोमुख्य_ops,
						 port);
	अगर (!port->cpm_करोमुख्य)
		जाओ out;

	irq_करोमुख्य_update_bus_token(port->cpm_करोमुख्य, DOMAIN_BUS_NEXUS);

	port->पूर्णांकx_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
						  &पूर्णांकx_करोमुख्य_ops,
						  port);
	अगर (!port->पूर्णांकx_करोमुख्य)
		जाओ out;

	irq_करोमुख्य_update_bus_token(port->पूर्णांकx_करोमुख्य, DOMAIN_BUS_WIRED);

	of_node_put(pcie_पूर्णांकc_node);
	raw_spin_lock_init(&port->lock);

	वापस 0;
out:
	xilinx_cpm_मुक्त_irq_करोमुख्यs(port);
	of_node_put(pcie_पूर्णांकc_node);
	dev_err(dev, "Failed to allocate IRQ domains\n");

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक xilinx_cpm_setup_irq(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक i, irq;

	port->irq = platक्रमm_get_irq(pdev, 0);
	अगर (port->irq < 0)
		वापस port->irq;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकr_cause); i++) अणु
		पूर्णांक err;

		अगर (!पूर्णांकr_cause[i].str)
			जारी;

		irq = irq_create_mapping(port->cpm_करोमुख्य, i);
		अगर (!irq) अणु
			dev_err(dev, "Failed to map interrupt\n");
			वापस -ENXIO;
		पूर्ण

		err = devm_request_irq(dev, irq, xilinx_cpm_pcie_पूर्णांकr_handler,
				       0, पूर्णांकr_cause[i].sym, port);
		अगर (err) अणु
			dev_err(dev, "Failed to request IRQ %d\n", irq);
			वापस err;
		पूर्ण
	पूर्ण

	port->पूर्णांकx_irq = irq_create_mapping(port->cpm_करोमुख्य,
					    XILINX_CPM_PCIE_INTR_INTX);
	अगर (!port->पूर्णांकx_irq) अणु
		dev_err(dev, "Failed to map INTx interrupt\n");
		वापस -ENXIO;
	पूर्ण

	/* Plug the INTx chained handler */
	irq_set_chained_handler_and_data(port->पूर्णांकx_irq,
					 xilinx_cpm_pcie_पूर्णांकx_flow, port);

	/* Plug the मुख्य event chained handler */
	irq_set_chained_handler_and_data(port->irq,
					 xilinx_cpm_pcie_event_flow, port);

	वापस 0;
पूर्ण

/**
 * xilinx_cpm_pcie_init_port - Initialize hardware
 * @port: PCIe port inक्रमmation
 */
अटल व्योम xilinx_cpm_pcie_init_port(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	अगर (cpm_pcie_link_up(port))
		dev_info(port->dev, "PCIe Link is UP\n");
	अन्यथा
		dev_info(port->dev, "PCIe Link is DOWN\n");

	/* Disable all पूर्णांकerrupts */
	pcie_ग_लिखो(port, ~XILINX_CPM_PCIE_IDR_ALL_MASK,
		   XILINX_CPM_PCIE_REG_IMR);

	/* Clear pending पूर्णांकerrupts */
	pcie_ग_लिखो(port, pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_IDR) &
		   XILINX_CPM_PCIE_IMR_ALL_MASK,
		   XILINX_CPM_PCIE_REG_IDR);

	/*
	 * XILINX_CPM_PCIE_MISC_IR_ENABLE रेजिस्टर is mapped to
	 * CPM SLCR block.
	 */
	ग_लिखोl(XILINX_CPM_PCIE_MISC_IR_LOCAL,
	       port->cpm_base + XILINX_CPM_PCIE_MISC_IR_ENABLE);
	/* Enable the Bridge enable bit */
	pcie_ग_लिखो(port, pcie_पढ़ो(port, XILINX_CPM_PCIE_REG_RPSC) |
		   XILINX_CPM_PCIE_REG_RPSC_BEN,
		   XILINX_CPM_PCIE_REG_RPSC);
पूर्ण

/**
 * xilinx_cpm_pcie_parse_dt - Parse Device tree
 * @port: PCIe port inक्रमmation
 * @bus_range: Bus resource
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_cpm_pcie_parse_dt(काष्ठा xilinx_cpm_pcie_port *port,
				    काष्ठा resource *bus_range)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;

	port->cpm_base = devm_platक्रमm_ioremap_resource_byname(pdev,
							       "cpm_slcr");
	अगर (IS_ERR(port->cpm_base))
		वापस PTR_ERR(port->cpm_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cfg");
	अगर (!res)
		वापस -ENXIO;

	port->cfg = pci_ecam_create(dev, res, bus_range,
				    &pci_generic_ecam_ops);
	अगर (IS_ERR(port->cfg))
		वापस PTR_ERR(port->cfg);

	port->reg_base = port->cfg->win;

	वापस 0;
पूर्ण

अटल व्योम xilinx_cpm_मुक्त_पूर्णांकerrupts(काष्ठा xilinx_cpm_pcie_port *port)
अणु
	irq_set_chained_handler_and_data(port->पूर्णांकx_irq, शून्य, शून्य);
	irq_set_chained_handler_and_data(port->irq, शून्य, शून्य);
पूर्ण

/**
 * xilinx_cpm_pcie_probe - Probe function
 * @pdev: Platक्रमm device poपूर्णांकer
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक xilinx_cpm_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xilinx_cpm_pcie_port *port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा resource_entry *bus;
	पूर्णांक err;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*port));
	अगर (!bridge)
		वापस -ENODEV;

	port = pci_host_bridge_priv(bridge);

	port->dev = dev;

	err = xilinx_cpm_pcie_init_irq_करोमुख्य(port);
	अगर (err)
		वापस err;

	bus = resource_list_first_type(&bridge->winकरोws, IORESOURCE_BUS);
	अगर (!bus)
		वापस -ENODEV;

	err = xilinx_cpm_pcie_parse_dt(port, bus->res);
	अगर (err) अणु
		dev_err(dev, "Parsing DT failed\n");
		जाओ err_parse_dt;
	पूर्ण

	xilinx_cpm_pcie_init_port(port);

	err = xilinx_cpm_setup_irq(port);
	अगर (err) अणु
		dev_err(dev, "Failed to set up interrupts\n");
		जाओ err_setup_irq;
	पूर्ण

	bridge->sysdata = port->cfg;
	bridge->ops = (काष्ठा pci_ops *)&pci_generic_ecam_ops.pci_ops;

	err = pci_host_probe(bridge);
	अगर (err < 0)
		जाओ err_host_bridge;

	वापस 0;

err_host_bridge:
	xilinx_cpm_मुक्त_पूर्णांकerrupts(port);
err_setup_irq:
	pci_ecam_मुक्त(port->cfg);
err_parse_dt:
	xilinx_cpm_मुक्त_irq_करोमुख्यs(port);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id xilinx_cpm_pcie_of_match[] = अणु
	अणु .compatible = "xlnx,versal-cpm-host-1.00", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver xilinx_cpm_pcie_driver = अणु
	.driver = अणु
		.name = "xilinx-cpm-pcie",
		.of_match_table = xilinx_cpm_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = xilinx_cpm_pcie_probe,
पूर्ण;

builtin_platक्रमm_driver(xilinx_cpm_pcie_driver);
