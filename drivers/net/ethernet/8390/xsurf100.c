<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/zorro.h>
#समावेश <net/ax88796.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

#घोषणा ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF100 \
		ZORRO_ID(INDIVIDUAL_COMPUTERS, 0x64, 0)

#घोषणा XS100_IRQSTATUS_BASE 0x40
#घोषणा XS100_8390_BASE 0x800

/* Longword-access area. Translated to 2 16-bit access cycles by the
 * X-Surf 100 FPGA
 */
#घोषणा XS100_8390_DATA32_BASE 0x8000
#घोषणा XS100_8390_DATA32_SIZE 0x2000
/* Sub-Areas क्रम fast data रेजिस्टर access; addresses relative to area begin */
#घोषणा XS100_8390_DATA_READ32_BASE 0x0880
#घोषणा XS100_8390_DATA_WRITE32_BASE 0x0C80
#घोषणा XS100_8390_DATA_AREA_SIZE 0x80

#घोषणा __NS8390_init ax_NS8390_init

/* क्रमce अचिन्हित दीर्घ back to 'void __iomem *' */
#घोषणा ax_convert_addr(_a) ((व्योम __क्रमce __iomem *)(_a))

#घोषणा ei_inb(_a) z_पढ़ोb(ax_convert_addr(_a))
#घोषणा ei_outb(_v, _a) z_ग_लिखोb(_v, ax_convert_addr(_a))

#घोषणा ei_inw(_a) z_पढ़ोw(ax_convert_addr(_a))
#घोषणा ei_outw(_v, _a) z_ग_लिखोw(_v, ax_convert_addr(_a))

#घोषणा ei_inb_p(_a) ei_inb(_a)
#घोषणा ei_outb_p(_v, _a) ei_outb(_v, _a)

/* define EI_SHIFT() to take पूर्णांकo account our रेजिस्टर offsets */
#घोषणा EI_SHIFT(x) (ei_local->reg_offset[(x)])

/* Ensure we have our RCR base value */
#घोषणा AX88796_PLATFORM

अटल अचिन्हित अक्षर version[] =
		"ax88796.c: Copyright 2005,2007 Simtec Electronics\n";

#समावेश "lib8390.c"

/* from ne.c */
#घोषणा NE_CMD		EI_SHIFT(0x00)
#घोषणा NE_RESET	EI_SHIFT(0x1f)
#घोषणा NE_DATAPORT	EI_SHIFT(0x10)

काष्ठा xsurf100_ax_plat_data अणु
	काष्ठा ax_plat_data ax;
	व्योम __iomem *base_regs;
	व्योम __iomem *data_area;
पूर्ण;

अटल पूर्णांक is_xsurf100_network_irq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	वापस (पढ़ोw(xs100->base_regs + XS100_IRQSTATUS_BASE) & 0xaaaa) != 0;
पूर्ण

/* These functions guarantee that the iomem is accessed with 32 bit
 * cycles only. z_स_नकल_fromio / z_स_नकल_toio करोn't
 */
अटल व्योम z_स_नकल_fromio32(व्योम *dst, स्थिर व्योम __iomem *src, माप_प्रकार bytes)
अणु
	जबतक (bytes > 32) अणु
		यंत्र __अस्थिर__
		   ("movem.l (%0)+,%%d0-%%d7\n"
		    "movem.l %%d0-%%d7,(%1)\n"
		    "adda.l #32,%1" : "=a"(src), "=a"(dst)
		    : "0"(src), "1"(dst) : "d0", "d1", "d2", "d3", "d4",
					   "d5", "d6", "d7", "memory");
		bytes -= 32;
	पूर्ण
	जबतक (bytes) अणु
		*(uपूर्णांक32_t *)dst = z_पढ़ोl(src);
		src += 4;
		dst += 4;
		bytes -= 4;
	पूर्ण
पूर्ण

अटल व्योम z_स_नकल_toio32(व्योम __iomem *dst, स्थिर व्योम *src, माप_प्रकार bytes)
अणु
	जबतक (bytes) अणु
		z_ग_लिखोl(*(स्थिर uपूर्णांक32_t *)src, dst);
		src += 4;
		dst += 4;
		bytes -= 4;
	पूर्ण
पूर्ण

अटल व्योम xs100_ग_लिखो(काष्ठा net_device *dev, स्थिर व्योम *src,
			अचिन्हित पूर्णांक count)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev.parent);
	काष्ठा xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	/* copy whole blocks */
	जबतक (count > XS100_8390_DATA_AREA_SIZE) अणु
		z_स_नकल_toio32(xs100->data_area +
				XS100_8390_DATA_WRITE32_BASE, src,
				XS100_8390_DATA_AREA_SIZE);
		src += XS100_8390_DATA_AREA_SIZE;
		count -= XS100_8390_DATA_AREA_SIZE;
	पूर्ण
	/* copy whole dwords */
	z_स_नकल_toio32(xs100->data_area + XS100_8390_DATA_WRITE32_BASE,
			src, count & ~3);
	src += count & ~3;
	अगर (count & 2) अणु
		ei_outw(*(uपूर्णांक16_t *)src, ei_local->mem + NE_DATAPORT);
		src += 2;
	पूर्ण
	अगर (count & 1)
		ei_outb(*(uपूर्णांक8_t *)src, ei_local->mem + NE_DATAPORT);
पूर्ण

अटल व्योम xs100_पढ़ो(काष्ठा net_device *dev, व्योम *dst, अचिन्हित पूर्णांक count)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev.parent);
	काष्ठा xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	/* copy whole blocks */
	जबतक (count > XS100_8390_DATA_AREA_SIZE) अणु
		z_स_नकल_fromio32(dst, xs100->data_area +
				  XS100_8390_DATA_READ32_BASE,
				  XS100_8390_DATA_AREA_SIZE);
		dst += XS100_8390_DATA_AREA_SIZE;
		count -= XS100_8390_DATA_AREA_SIZE;
	पूर्ण
	/* copy whole dwords */
	z_स_नकल_fromio32(dst, xs100->data_area + XS100_8390_DATA_READ32_BASE,
			  count & ~3);
	dst += count & ~3;
	अगर (count & 2) अणु
		*(uपूर्णांक16_t *)dst = ei_inw(ei_local->mem + NE_DATAPORT);
		dst += 2;
	पूर्ण
	अगर (count & 1)
		*(uपूर्णांक8_t *)dst = ei_inb(ei_local->mem + NE_DATAPORT);
पूर्ण

/* Block input and output, similar to the Crynwr packet driver. If
 * you are porting to a new ethercard, look at the packet driver
 * source क्रम hपूर्णांकs. The NEx000 करोesn't share the on-board packet
 * memory -- you have to put the packet out through the "remote DMA"
 * dataport using ei_outb.
 */
अटल व्योम xs100_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *nic_base = ei_local->mem;
	अक्षर *buf = skb->data;

	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev,
			   "DMAing conflict in %s [DMAstat:%d][irqlock:%d]\n",
			   __func__,
			   ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;

	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	ei_outb(count & 0xff, nic_base + EN0_RCNTLO);
	ei_outb(count >> 8, nic_base + EN0_RCNTHI);
	ei_outb(ring_offset & 0xff, nic_base + EN0_RSARLO);
	ei_outb(ring_offset >> 8, nic_base + EN0_RSARHI);
	ei_outb(E8390_RREAD + E8390_START, nic_base + NE_CMD);

	xs100_पढ़ो(dev, buf, count);

	ei_local->dमुख्यg &= ~1;
पूर्ण

अटल व्योम xs100_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	व्योम __iomem *nic_base = ei_local->mem;
	अचिन्हित दीर्घ dma_start;

	/* Round the count up क्रम word ग_लिखोs. Do we need to करो this?
	 * What effect will an odd byte count have on the 8390?  I
	 * should check someday.
	 */
	अगर (ei_local->word16 && (count & 0x01))
		count++;

	/* This *shouldn't* happen. If it does, it's the last thing
	 * you'll see
	 */
	अगर (ei_local->dमुख्यg) अणु
		netdev_err(dev,
			   "DMAing conflict in %s [DMAstat:%d][irqlock:%d]\n",
			   __func__,
			   ei_local->dमुख्यg, ei_local->irqlock);
		वापस;
	पूर्ण

	ei_local->dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	ei_outb(E8390_PAGE0 + E8390_START + E8390_NODMA, nic_base + NE_CMD);

	ei_outb(ENISR_RDC, nic_base + EN0_ISR);

	/* Now the normal output. */
	ei_outb(count & 0xff, nic_base + EN0_RCNTLO);
	ei_outb(count >> 8, nic_base + EN0_RCNTHI);
	ei_outb(0x00, nic_base + EN0_RSARLO);
	ei_outb(start_page, nic_base + EN0_RSARHI);

	ei_outb(E8390_RWRITE + E8390_START, nic_base + NE_CMD);

	xs100_ग_लिखो(dev, buf, count);

	dma_start = jअगरfies;

	जबतक ((ei_inb(nic_base + EN0_ISR) & ENISR_RDC) == 0) अणु
		अगर (jअगरfies - dma_start > 2 * HZ / 100) अणु	/* 20ms */
			netdev_warn(dev, "timeout waiting for Tx RDC.\n");
			ei_local->reset_8390(dev);
			ax_NS8390_init(dev, 1);
			अवरोध;
		पूर्ण
	पूर्ण

	ei_outb(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_local->dमुख्यg &= ~0x01;
पूर्ण

अटल पूर्णांक xsurf100_probe(काष्ठा zorro_dev *zdev,
			  स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा xsurf100_ax_plat_data ax88796_data;
	काष्ठा resource res[2] = अणु
		DEFINE_RES_NAMED(IRQ_AMIGA_PORTS, 1, शून्य,
				 IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE),
		DEFINE_RES_MEM(zdev->resource.start + XS100_8390_BASE,
			       4 * 0x20)
	पूर्ण;
	पूर्णांक reg;
	/* This table is referenced in the device काष्ठाure, so it must
	 * outlive the scope of xsurf100_probe.
	 */
	अटल u32 reg_offsets[32];
	पूर्णांक ret = 0;

	/* X-Surf 100 control and 32 bit ring buffer data access areas.
	 * These resources are not used by the ax88796 driver, so must
	 * be requested here and passed via platक्रमm data.
	 */

	अगर (!request_mem_region(zdev->resource.start, 0x100, zdev->name)) अणु
		dev_err(&zdev->dev, "cannot reserve X-Surf 100 control registers\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!request_mem_region(zdev->resource.start +
				XS100_8390_DATA32_BASE,
				XS100_8390_DATA32_SIZE,
				"X-Surf 100 32-bit data access")) अणु
		dev_err(&zdev->dev, "cannot reserve 32-bit area\n");
		ret = -ENXIO;
		जाओ निकास_req;
	पूर्ण

	क्रम (reg = 0; reg < 0x20; reg++)
		reg_offsets[reg] = 4 * reg;

	स_रखो(&ax88796_data, 0, माप(ax88796_data));
	ax88796_data.ax.flags = AXFLG_HAS_EEPROM;
	ax88796_data.ax.wordlength = 2;
	ax88796_data.ax.dcr_val = 0x48;
	ax88796_data.ax.rcr_val = 0x40;
	ax88796_data.ax.reg_offsets = reg_offsets;
	ax88796_data.ax.check_irq = is_xsurf100_network_irq;
	ax88796_data.base_regs = ioremap(zdev->resource.start, 0x100);

	/* error handling क्रम ioremap regs */
	अगर (!ax88796_data.base_regs) अणु
		dev_err(&zdev->dev, "Cannot ioremap area %pR (registers)\n",
			&zdev->resource);

		ret = -ENXIO;
		जाओ निकास_req2;
	पूर्ण

	ax88796_data.data_area = ioremap(zdev->resource.start +
			XS100_8390_DATA32_BASE, XS100_8390_DATA32_SIZE);

	/* error handling क्रम ioremap data */
	अगर (!ax88796_data.data_area) अणु
		dev_err(&zdev->dev,
			"Cannot ioremap area %pR offset %x (32-bit access)\n",
			&zdev->resource,  XS100_8390_DATA32_BASE);

		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	ax88796_data.ax.block_output = xs100_block_output;
	ax88796_data.ax.block_input = xs100_block_input;

	pdev = platक्रमm_device_रेजिस्टर_resndata(&zdev->dev, "ax88796",
						 zdev->slotaddr, res, 2,
						 &ax88796_data,
						 माप(ax88796_data));

	अगर (IS_ERR(pdev)) अणु
		dev_err(&zdev->dev, "cannot register platform device\n");
		ret = -ENXIO;
		जाओ निकास_mem2;
	पूर्ण

	zorro_set_drvdata(zdev, pdev);

	अगर (!ret)
		वापस 0;

 निकास_mem2:
	iounmap(ax88796_data.data_area);

 निकास_mem:
	iounmap(ax88796_data.base_regs);

 निकास_req2:
	release_mem_region(zdev->resource.start + XS100_8390_DATA32_BASE,
			   XS100_8390_DATA32_SIZE);

 निकास_req:
	release_mem_region(zdev->resource.start, 0x100);

	वापस ret;
पूर्ण

अटल व्योम xsurf100_हटाओ(काष्ठा zorro_dev *zdev)
अणु
	काष्ठा platक्रमm_device *pdev = zorro_get_drvdata(zdev);
	काष्ठा xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	iounmap(xs100->base_regs);
	release_mem_region(zdev->resource.start, 0x100);
	iounmap(xs100->data_area);
	release_mem_region(zdev->resource.start + XS100_8390_DATA32_BASE,
			   XS100_8390_DATA32_SIZE);
पूर्ण

अटल स्थिर काष्ठा zorro_device_id xsurf100_zorro_tbl[] = अणु
	अणु ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF100, पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(zorro, xsurf100_zorro_tbl);

अटल काष्ठा zorro_driver xsurf100_driver = अणु
	.name           = "xsurf100",
	.id_table       = xsurf100_zorro_tbl,
	.probe          = xsurf100_probe,
	.हटाओ         = xsurf100_हटाओ,
पूर्ण;

module_driver(xsurf100_driver, zorro_रेजिस्टर_driver, zorro_unरेजिस्टर_driver);

MODULE_DESCRIPTION("X-Surf 100 driver");
MODULE_AUTHOR("Michael Karcher <kernel@mkarcher.dialup.fu-berlin.de>");
MODULE_LICENSE("GPL v2");
