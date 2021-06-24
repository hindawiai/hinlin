<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IO workarounds क्रम PCI on Celleb/Cell platक्रमm
 *
 * (C) Copyright 2006-2007 TOSHIBA CORPORATION
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/io-workarounds.h>

#घोषणा SPIDER_PCI_DISABLE_PREFETCH

काष्ठा spiderpci_iowa_निजी अणु
	व्योम __iomem *regs;
पूर्ण;

अटल व्योम spiderpci_io_flush(काष्ठा iowa_bus *bus)
अणु
	काष्ठा spiderpci_iowa_निजी *priv;
	u32 val;

	priv = bus->निजी;
	val = in_be32(priv->regs + SPIDER_PCI_DUMMY_READ);
	iosync();
पूर्ण

#घोषणा SPIDER_PCI_MMIO_READ(name, ret)					\
अटल ret spiderpci_##name(स्थिर PCI_IO_ADDR addr)			\
अणु									\
	ret val = __करो_##name(addr);					\
	spiderpci_io_flush(iowa_mem_find_bus(addr));			\
	वापस val;							\
पूर्ण

#घोषणा SPIDER_PCI_MMIO_READ_STR(name)					\
अटल व्योम spiderpci_##name(स्थिर PCI_IO_ADDR addr, व्योम *buf, 	\
			     अचिन्हित दीर्घ count)			\
अणु									\
	__करो_##name(addr, buf, count);					\
	spiderpci_io_flush(iowa_mem_find_bus(addr));			\
पूर्ण

SPIDER_PCI_MMIO_READ(पढ़ोb, u8)
SPIDER_PCI_MMIO_READ(पढ़ोw, u16)
SPIDER_PCI_MMIO_READ(पढ़ोl, u32)
SPIDER_PCI_MMIO_READ(पढ़ोq, u64)
SPIDER_PCI_MMIO_READ(पढ़ोw_be, u16)
SPIDER_PCI_MMIO_READ(पढ़ोl_be, u32)
SPIDER_PCI_MMIO_READ(पढ़ोq_be, u64)
SPIDER_PCI_MMIO_READ_STR(पढ़ोsb)
SPIDER_PCI_MMIO_READ_STR(पढ़ोsw)
SPIDER_PCI_MMIO_READ_STR(पढ़ोsl)

अटल व्योम spiderpci_स_नकल_fromio(व्योम *dest, स्थिर PCI_IO_ADDR src,
				    अचिन्हित दीर्घ n)
अणु
	__करो_स_नकल_fromio(dest, src, n);
	spiderpci_io_flush(iowa_mem_find_bus(src));
पूर्ण

अटल पूर्णांक __init spiderpci_pci_setup_chip(काष्ठा pci_controller *phb,
					   व्योम __iomem *regs)
अणु
	व्योम *dummy_page_va;
	dma_addr_t dummy_page_da;

#अगर_घोषित SPIDER_PCI_DISABLE_PREFETCH
	u32 val = in_be32(regs + SPIDER_PCI_VCI_CNTL_STAT);
	pr_debug("SPIDER_IOWA:PVCI_Control_Status was 0x%08x\n", val);
	out_be32(regs + SPIDER_PCI_VCI_CNTL_STAT, val | 0x8);
#पूर्ण_अगर /* SPIDER_PCI_DISABLE_PREFETCH */

	/* setup dummy पढ़ो */
	/*
	 * On CellBlade, we can't know that which XDR memory is used by
	 * kदो_स्मृति() to allocate dummy_page_va.
	 * In order to imporve the perक्रमmance, the XDR which is used to
	 * allocate dummy_page_va is the nearest the spider-pci.
	 * We have to select the CBE which is the nearest the spider-pci
	 * to allocate memory from the best XDR, but I करोn't know that
	 * how to करो.
	 *
	 * Celleb करोes not have this problem, because it has only one XDR.
	 */
	dummy_page_va = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!dummy_page_va) अणु
		pr_err("SPIDERPCI-IOWA:Alloc dummy_page_va failed.\n");
		वापस -1;
	पूर्ण

	dummy_page_da = dma_map_single(phb->parent, dummy_page_va,
				       PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(phb->parent, dummy_page_da)) अणु
		pr_err("SPIDER-IOWA:Map dummy page filed.\n");
		kमुक्त(dummy_page_va);
		वापस -1;
	पूर्ण

	out_be32(regs + SPIDER_PCI_DUMMY_READ_BASE, dummy_page_da);

	वापस 0;
पूर्ण

पूर्णांक __init spiderpci_iowa_init(काष्ठा iowa_bus *bus, व्योम *data)
अणु
	व्योम __iomem *regs = शून्य;
	काष्ठा spiderpci_iowa_निजी *priv;
	काष्ठा device_node *np = bus->phb->dn;
	काष्ठा resource r;
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)data;

	pr_debug("SPIDERPCI-IOWA:Bus initialize for spider(%pOF)\n",
		 np);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		pr_err("SPIDERPCI-IOWA:"
		       "Can't allocate struct spiderpci_iowa_private");
		वापस -1;
	पूर्ण

	अगर (of_address_to_resource(np, 0, &r)) अणु
		pr_err("SPIDERPCI-IOWA:Can't get resource.\n");
		जाओ error;
	पूर्ण

	regs = ioremap(r.start + offset, SPIDER_PCI_REG_SIZE);
	अगर (!regs) अणु
		pr_err("SPIDERPCI-IOWA:ioremap failed.\n");
		जाओ error;
	पूर्ण
	priv->regs = regs;
	bus->निजी = priv;

	अगर (spiderpci_pci_setup_chip(bus->phb, regs))
		जाओ error;

	वापस 0;

error:
	kमुक्त(priv);
	bus->निजी = शून्य;

	अगर (regs)
		iounmap(regs);

	वापस -1;
पूर्ण

काष्ठा ppc_pci_io spiderpci_ops = अणु
	.पढ़ोb = spiderpci_पढ़ोb,
	.पढ़ोw = spiderpci_पढ़ोw,
	.पढ़ोl = spiderpci_पढ़ोl,
	.पढ़ोq = spiderpci_पढ़ोq,
	.पढ़ोw_be = spiderpci_पढ़ोw_be,
	.पढ़ोl_be = spiderpci_पढ़ोl_be,
	.पढ़ोq_be = spiderpci_पढ़ोq_be,
	.पढ़ोsb = spiderpci_पढ़ोsb,
	.पढ़ोsw = spiderpci_पढ़ोsw,
	.पढ़ोsl = spiderpci_पढ़ोsl,
	.स_नकल_fromio = spiderpci_स_नकल_fromio,
पूर्ण;

