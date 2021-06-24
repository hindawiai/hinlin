<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* parport.h: sparc64 specअगरic parport initialization and dma.
 *
 * Copyright (C) 1999  Eddie C. Dost  (ecd@skynet.be)
 */

#अगर_अघोषित _ASM_SPARC64_PARPORT_H
#घोषणा _ASM_SPARC64_PARPORT_H 1

#समावेश <linux/of_device.h>

#समावेश <यंत्र/ebus_dma.h>
#समावेश <यंत्र/ns87303.h>
#समावेश <यंत्र/prom.h>

#घोषणा PARPORT_PC_MAX_PORTS	PARPORT_MAX

/*
 * While sparc64 करोesn't have an ISA DMA API, we provide something that looks
 * बंद enough to make parport_pc happy
 */
#घोषणा HAS_DMA

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
अटल DEFINE_SPINLOCK(dma_spin_lock);

#घोषणा claim_dma_lock() \
(अणु	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&dma_spin_lock, flags); \
	flags; \
पूर्ण)

#घोषणा release_dma_lock(__flags) \
	spin_unlock_irqrestore(&dma_spin_lock, __flags);
#पूर्ण_अगर

अटल काष्ठा sparc_ebus_info अणु
	काष्ठा ebus_dma_info info;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक count;
	पूर्णांक lock;

	काष्ठा parport *port;
पूर्ण sparc_ebus_dmas[PARPORT_PC_MAX_PORTS];

अटल DECLARE_BITMAP(dma_slot_map, PARPORT_PC_MAX_PORTS);

अटल अंतरभूत पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर *device_id)
अणु
	अगर (dmanr >= PARPORT_PC_MAX_PORTS)
		वापस -EINVAL;
	अगर (xchg(&sparc_ebus_dmas[dmanr].lock, 1) != 0)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr >= PARPORT_PC_MAX_PORTS) अणु
		prपूर्णांकk(KERN_WARNING "Trying to free DMA%d\n", dmanr);
		वापस;
	पूर्ण
	अगर (xchg(&sparc_ebus_dmas[dmanr].lock, 0) == 0) अणु
		prपूर्णांकk(KERN_WARNING "Trying to free free DMA%d\n", dmanr);
		वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम enable_dma(अचिन्हित पूर्णांक dmanr)
अणु
	ebus_dma_enable(&sparc_ebus_dmas[dmanr].info, 1);

	अगर (ebus_dma_request(&sparc_ebus_dmas[dmanr].info,
			     sparc_ebus_dmas[dmanr].addr,
			     sparc_ebus_dmas[dmanr].count))
		BUG();
पूर्ण

अटल अंतरभूत व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
	ebus_dma_enable(&sparc_ebus_dmas[dmanr].info, 0);
पूर्ण

अटल अंतरभूत व्योम clear_dma_ff(अचिन्हित पूर्णांक dmanr)
अणु
	/* nothing */
पूर्ण

अटल अंतरभूत व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अक्षर mode)
अणु
	ebus_dma_prepare(&sparc_ebus_dmas[dmanr].info, (mode != DMA_MODE_WRITE));
पूर्ण

अटल अंतरभूत व्योम set_dma_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक addr)
अणु
	sparc_ebus_dmas[dmanr].addr = addr;
पूर्ण

अटल अंतरभूत व्योम set_dma_count(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
	sparc_ebus_dmas[dmanr].count = count;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_dma_residue(अचिन्हित पूर्णांक dmanr)
अणु
	वापस ebus_dma_residue(&sparc_ebus_dmas[dmanr].info);
पूर्ण

अटल पूर्णांक ecpp_probe(काष्ठा platक्रमm_device *op)
अणु
	अचिन्हित दीर्घ base = op->resource[0].start;
	अचिन्हित दीर्घ config = op->resource[1].start;
	अचिन्हित दीर्घ d_base = op->resource[2].start;
	अचिन्हित दीर्घ d_len;
	काष्ठा device_node *parent;
	काष्ठा parport *p;
	पूर्णांक slot, err;

	parent = op->dev.of_node->parent;
	अगर (of_node_name_eq(parent, "dma")) अणु
		p = parport_pc_probe_port(base, base + 0x400,
					  op->archdata.irqs[0], PARPORT_DMA_NOFIFO,
					  op->dev.parent->parent, 0);
		अगर (!p)
			वापस -ENOMEM;
		dev_set_drvdata(&op->dev, p);
		वापस 0;
	पूर्ण

	क्रम (slot = 0; slot < PARPORT_PC_MAX_PORTS; slot++) अणु
		अगर (!test_and_set_bit(slot, dma_slot_map))
			अवरोध;
	पूर्ण
	err = -ENODEV;
	अगर (slot >= PARPORT_PC_MAX_PORTS)
		जाओ out_err;

	spin_lock_init(&sparc_ebus_dmas[slot].info.lock);

	d_len = (op->resource[2].end - d_base) + 1UL;
	sparc_ebus_dmas[slot].info.regs =
		of_ioremap(&op->resource[2], 0, d_len, "ECPP DMA");

	अगर (!sparc_ebus_dmas[slot].info.regs)
		जाओ out_clear_map;

	sparc_ebus_dmas[slot].info.flags = 0;
	sparc_ebus_dmas[slot].info.callback = शून्य;
	sparc_ebus_dmas[slot].info.client_cookie = शून्य;
	sparc_ebus_dmas[slot].info.irq = 0xdeadbeef;
	म_नकल(sparc_ebus_dmas[slot].info.name, "parport");
	अगर (ebus_dma_रेजिस्टर(&sparc_ebus_dmas[slot].info))
		जाओ out_unmap_regs;

	ebus_dma_irq_enable(&sparc_ebus_dmas[slot].info, 1);

	/* Configure IRQ to Push Pull, Level Low */
	/* Enable ECP, set bit 2 of the CTR first */
	outb(0x04, base + 0x02);
	ns87303_modअगरy(config, PCR,
		       PCR_EPP_ENABLE |
		       PCR_IRQ_ODRAIN,
		       PCR_ECP_ENABLE |
		       PCR_ECP_CLK_ENA |
		       PCR_IRQ_POLAR);

	/* CTR bit 5 controls direction of port */
	ns87303_modअगरy(config, PTR,
		       0, PTR_LPT_REG_सूची);

	p = parport_pc_probe_port(base, base + 0x400,
				  op->archdata.irqs[0],
				  slot,
				  op->dev.parent,
				  0);
	err = -ENOMEM;
	अगर (!p)
		जाओ out_disable_irq;

	dev_set_drvdata(&op->dev, p);

	वापस 0;

out_disable_irq:
	ebus_dma_irq_enable(&sparc_ebus_dmas[slot].info, 0);
	ebus_dma_unरेजिस्टर(&sparc_ebus_dmas[slot].info);

out_unmap_regs:
	of_iounmap(&op->resource[2], sparc_ebus_dmas[slot].info.regs, d_len);

out_clear_map:
	clear_bit(slot, dma_slot_map);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक ecpp_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा parport *p = dev_get_drvdata(&op->dev);
	पूर्णांक slot = p->dma;

	parport_pc_unरेजिस्टर_port(p);

	अगर (slot != PARPORT_DMA_NOFIFO) अणु
		अचिन्हित दीर्घ d_base = op->resource[2].start;
		अचिन्हित दीर्घ d_len;

		d_len = (op->resource[2].end - d_base) + 1UL;

		ebus_dma_irq_enable(&sparc_ebus_dmas[slot].info, 0);
		ebus_dma_unरेजिस्टर(&sparc_ebus_dmas[slot].info);
		of_iounmap(&op->resource[2],
			   sparc_ebus_dmas[slot].info.regs,
			   d_len);
		clear_bit(slot, dma_slot_map);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ecpp_match[] = अणु
	अणु
		.name = "ecpp",
	पूर्ण,
	अणु
		.name = "parallel",
		.compatible = "ecpp",
	पूर्ण,
	अणु
		.name = "parallel",
		.compatible = "ns87317-ecpp",
	पूर्ण,
	अणु
		.name = "parallel",
		.compatible = "pnpALI,1533,3",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ecpp_driver = अणु
	.driver = अणु
		.name = "ecpp",
		.of_match_table = ecpp_match,
	पूर्ण,
	.probe			= ecpp_probe,
	.हटाओ			= ecpp_हटाओ,
पूर्ण;

अटल पूर्णांक parport_pc_find_nonpci_ports(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ecpp_driver);
पूर्ण

#पूर्ण_अगर /* !(_ASM_SPARC64_PARPORT_H */
