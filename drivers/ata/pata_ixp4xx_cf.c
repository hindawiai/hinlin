<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ixp4xx PATA/Compact Flash driver
 * Copyright (C) 2006-07 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * An ATA driver to handle a Compact Flash connected
 * to the ixp4xx expansion bus in TrueIDE mode. The CF
 * must have it chip selects connected to two CS lines
 * on the ixp4xx. In the irq is not available, you might
 * want to modअगरy both this driver and libata to run in
 * polling mode.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <scsi/scsi_host.h>

#घोषणा DRV_NAME	"pata_ixp4xx_cf"
#घोषणा DRV_VERSION	"0.2"

अटल पूर्णांक ixp4xx_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **error)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		ata_dev_info(dev, "configured for PIO0\n");
		dev->pio_mode = XFER_PIO_0;
		dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ixp4xx_mmio_data_xfer(काष्ठा ata_queued_cmd *qc,
				अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक words = buflen >> 1;
	u16 *buf16 = (u16 *) buf;
	काष्ठा ata_port *ap = qc->dev->link->ap;
	व्योम __iomem *mmio = ap->ioaddr.data_addr;
	काष्ठा ixp4xx_pata_data *data = dev_get_platdata(ap->host->dev);

	/* set the expansion bus in 16bit mode and restore
	 * 8 bit mode after the transaction.
	 */
	*data->cs0_cfg &= ~(0x01);
	udelay(100);

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ)
		क्रम (i = 0; i < words; i++)
			buf16[i] = पढ़ोw(mmio);
	अन्यथा
		क्रम (i = 0; i < words; i++)
			ग_लिखोw(buf16[i], mmio);

	/* Transfer trailing 1 byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		u16 align_buf[1] = अणु 0 पूर्ण;
		अचिन्हित अक्षर *trailing_buf = buf + buflen - 1;

		अगर (rw == READ) अणु
			align_buf[0] = पढ़ोw(mmio);
			स_नकल(trailing_buf, align_buf, 1);
		पूर्ण अन्यथा अणु
			स_नकल(align_buf, trailing_buf, 1);
			ग_लिखोw(align_buf[0], mmio);
		पूर्ण
		words++;
	पूर्ण

	udelay(100);
	*data->cs0_cfg |= 0x01;

	वापस words << 1;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ixp4xx_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations ixp4xx_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.sff_data_xfer		= ixp4xx_mmio_data_xfer,
	.cable_detect		= ata_cable_40wire,
	.set_mode		= ixp4xx_set_mode,
पूर्ण;

अटल व्योम ixp4xx_setup_port(काष्ठा ata_port *ap,
			      काष्ठा ixp4xx_pata_data *data,
			      अचिन्हित दीर्घ raw_cs0, अचिन्हित दीर्घ raw_cs1)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित दीर्घ raw_cmd = raw_cs0;
	अचिन्हित दीर्घ raw_ctl = raw_cs1 + 0x06;

	ioaddr->cmd_addr	= data->cs0;
	ioaddr->altstatus_addr	= data->cs1 + 0x06;
	ioaddr->ctl_addr	= data->cs1 + 0x06;

	ata_sff_std_ports(ioaddr);

#अगर_अघोषित __ARMEB__

	/* adjust the addresses to handle the address swizzling of the
	 * ixp4xx in little endian mode.
	 */

	*(अचिन्हित दीर्घ *)&ioaddr->data_addr		^= 0x02;
	*(अचिन्हित दीर्घ *)&ioaddr->cmd_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->altstatus_addr	^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->ctl_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->error_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->feature_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->nsect_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->lbal_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->lbam_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->lbah_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->device_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->status_addr		^= 0x03;
	*(अचिन्हित दीर्घ *)&ioaddr->command_addr		^= 0x03;

	raw_cmd ^= 0x03;
	raw_ctl ^= 0x03;
#पूर्ण_अगर

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", raw_cmd, raw_ctl);
पूर्ण

अटल पूर्णांक ixp4xx_pata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *cs0, *cs1;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	काष्ठा ixp4xx_pata_data *data = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;
	पूर्णांक irq;

	cs0 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cs1 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);

	अगर (!cs0 || !cs1)
		वापस -EINVAL;

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	data->cs0 = devm_ioremap(&pdev->dev, cs0->start, 0x1000);
	data->cs1 = devm_ioremap(&pdev->dev, cs1->start, 0x1000);

	अगर (!data->cs0 || !data->cs1)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0)
		irq_set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
	अन्यथा अगर (irq < 0)
		वापस irq;
	अन्यथा
		वापस -EINVAL;

	/* Setup expansion bus chip selects */
	*data->cs0_cfg = data->cs0_bits;
	*data->cs1_cfg = data->cs1_bits;

	ap = host->ports[0];

	ap->ops	= &ixp4xx_port_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_NO_ATAPI;

	ixp4xx_setup_port(ap, data, cs0->start, cs1->start);

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* activate host */
	वापस ata_host_activate(host, irq, ata_sff_पूर्णांकerrupt, 0, &ixp4xx_sht);
पूर्ण

अटल काष्ठा platक्रमm_driver ixp4xx_pata_platक्रमm_driver = अणु
	.driver	 = अणु
		.name   = DRV_NAME,
	पूर्ण,
	.probe		= ixp4xx_pata_probe,
	.हटाओ		= ata_platक्रमm_हटाओ_one,
पूर्ण;

module_platक्रमm_driver(ixp4xx_pata_platक्रमm_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("low-level driver for ixp4xx Compact Flash PATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_NAME);
