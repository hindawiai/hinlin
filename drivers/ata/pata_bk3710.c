<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Palmchip BK3710 PATA controller driver
 *
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on palm_bk3710.c:
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 */

#समावेश <linux/ata.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#घोषणा DRV_NAME "pata_bk3710"

#घोषणा BK3710_TF_OFFSET	0x1F0
#घोषणा BK3710_CTL_OFFSET	0x3F6

#घोषणा BK3710_BMISP		0x02
#घोषणा BK3710_IDETIMP		0x40
#घोषणा BK3710_UDMACTL		0x48
#घोषणा BK3710_MISCCTL		0x50
#घोषणा BK3710_REGSTB		0x54
#घोषणा BK3710_REGRCVR		0x58
#घोषणा BK3710_DATSTB		0x5C
#घोषणा BK3710_DATRCVR		0x60
#घोषणा BK3710_DMASTB		0x64
#घोषणा BK3710_DMARCVR		0x68
#घोषणा BK3710_UDMASTB		0x6C
#घोषणा BK3710_UDMATRP		0x70
#घोषणा BK3710_UDMAENV		0x74
#घोषणा BK3710_IORDYTMP		0x78

अटल काष्ठा scsi_host_ढाँचा pata_bk3710_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल अचिन्हित पूर्णांक ideclk_period; /* in nanoseconds */

काष्ठा pata_bk3710_udmatiming अणु
	अचिन्हित पूर्णांक rpसमय;	/* tRP -- Ready to छोड़ो समय (nsec) */
	अचिन्हित पूर्णांक cycleसमय;	/* tCYCTYP2/2 -- avg Cycle Time (nsec) */
				/* tENV is always a minimum of 20 nsec */
पूर्ण;

अटल स्थिर काष्ठा pata_bk3710_udmatiming pata_bk3710_udmatimings[6] = अणु
	अणु 160, 240 / 2 पूर्ण,	/* UDMA Mode 0 */
	अणु 125, 160 / 2 पूर्ण,	/* UDMA Mode 1 */
	अणु 100, 120 / 2 पूर्ण,	/* UDMA Mode 2 */
	अणु 100,  90 / 2 पूर्ण,	/* UDMA Mode 3 */
	अणु 100,  60 / 2 पूर्ण,	/* UDMA Mode 4 */
	अणु  85,  40 / 2 पूर्ण,	/* UDMA Mode 5 */
पूर्ण;

अटल व्योम pata_bk3710_setudmamode(व्योम __iomem *base, अचिन्हित पूर्णांक dev,
				    अचिन्हित पूर्णांक mode)
अणु
	u32 val32;
	u16 val16;
	u8 tenv, trp, t0;

	/* DMA Data Setup */
	t0 = DIV_ROUND_UP(pata_bk3710_udmatimings[mode].cycleसमय,
			  ideclk_period) - 1;
	tenv = DIV_ROUND_UP(20, ideclk_period) - 1;
	trp = DIV_ROUND_UP(pata_bk3710_udmatimings[mode].rpसमय,
			   ideclk_period) - 1;

	/* udmastb Ultra DMA Access Strobe Width */
	val32 = ioपढ़ो32(base + BK3710_UDMASTB) & (0xFF << (dev ? 0 : 8));
	val32 |= t0 << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_UDMASTB);

	/* udmatrp Ultra DMA Ready to Pause Time */
	val32 = ioपढ़ो32(base + BK3710_UDMATRP) & (0xFF << (dev ? 0 : 8));
	val32 |= trp << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_UDMATRP);

	/* udmaenv Ultra DMA envelop Time */
	val32 = ioपढ़ो32(base + BK3710_UDMAENV) & (0xFF << (dev ? 0 : 8));
	val32 |= tenv << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_UDMAENV);

	/* Enable UDMA क्रम Device */
	val16 = ioपढ़ो16(base + BK3710_UDMACTL) | (1 << dev);
	ioग_लिखो16(val16, base + BK3710_UDMACTL);
पूर्ण

अटल व्योम pata_bk3710_seपंचांगwdmamode(व्योम __iomem *base, अचिन्हित पूर्णांक dev,
				     अचिन्हित लघु min_cycle,
				     अचिन्हित पूर्णांक mode)
अणु
	स्थिर काष्ठा ata_timing *t;
	पूर्णांक cycleसमय;
	u32 val32;
	u16 val16;
	u8 td, tkw, t0;

	t = ata_timing_find_mode(mode);
	cycleसमय = max_t(पूर्णांक, t->cycle, min_cycle);

	/* DMA Data Setup */
	t0 = DIV_ROUND_UP(cycleसमय, ideclk_period);
	td = DIV_ROUND_UP(t->active, ideclk_period);
	tkw = t0 - td - 1;
	td--;

	val32 = ioपढ़ो32(base + BK3710_DMASTB) & (0xFF << (dev ? 0 : 8));
	val32 |= td << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_DMASTB);

	val32 = ioपढ़ो32(base + BK3710_DMARCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= tkw << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_DMARCVR);

	/* Disable UDMA क्रम Device */
	val16 = ioपढ़ो16(base + BK3710_UDMACTL) & ~(1 << dev);
	ioग_लिखो16(val16, base + BK3710_UDMACTL);
पूर्ण

अटल व्योम pata_bk3710_set_dmamode(काष्ठा ata_port *ap,
				    काष्ठा ata_device *adev)
अणु
	व्योम __iomem *base = (व्योम __iomem *)ap->ioaddr.bmdma_addr;
	पूर्णांक is_slave = adev->devno;
	स्थिर u8 xferspeed = adev->dma_mode;

	अगर (xferspeed >= XFER_UDMA_0)
		pata_bk3710_setudmamode(base, is_slave,
					xferspeed - XFER_UDMA_0);
	अन्यथा
		pata_bk3710_seपंचांगwdmamode(base, is_slave,
					 adev->id[ATA_ID_EIDE_DMA_MIN],
					 xferspeed);
पूर्ण

अटल व्योम pata_bk3710_setpiomode(व्योम __iomem *base, काष्ठा ata_device *pair,
				   अचिन्हित पूर्णांक dev, अचिन्हित पूर्णांक cycleसमय,
				   अचिन्हित पूर्णांक mode)
अणु
	स्थिर काष्ठा ata_timing *t;
	u32 val32;
	u8 t2, t2i, t0;

	t = ata_timing_find_mode(XFER_PIO_0 + mode);

	/* PIO Data Setup */
	t0 = DIV_ROUND_UP(cycleसमय, ideclk_period);
	t2 = DIV_ROUND_UP(t->active, ideclk_period);

	t2i = t0 - t2 - 1;
	t2--;

	val32 = ioपढ़ो32(base + BK3710_DATSTB) & (0xFF << (dev ? 0 : 8));
	val32 |= t2 << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_DATSTB);

	val32 = ioपढ़ो32(base + BK3710_DATRCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= t2i << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_DATRCVR);

	/* FIXME: this is broken also in the old driver */
	अगर (pair) अणु
		u8 mode2 = pair->pio_mode - XFER_PIO_0;

		अगर (mode2 < mode)
			mode = mode2;
	पूर्ण

	/* TASKखाता Setup */
	t0 = DIV_ROUND_UP(t->cyc8b, ideclk_period);
	t2 = DIV_ROUND_UP(t->act8b, ideclk_period);

	t2i = t0 - t2 - 1;
	t2--;

	val32 = ioपढ़ो32(base + BK3710_REGSTB) & (0xFF << (dev ? 0 : 8));
	val32 |= t2 << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_REGSTB);

	val32 = ioपढ़ो32(base + BK3710_REGRCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= t2i << (dev ? 8 : 0);
	ioग_लिखो32(val32, base + BK3710_REGRCVR);
पूर्ण

अटल व्योम pata_bk3710_set_piomode(काष्ठा ata_port *ap,
				    काष्ठा ata_device *adev)
अणु
	व्योम __iomem *base = (व्योम __iomem *)ap->ioaddr.bmdma_addr;
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	स्थिर काष्ठा ata_timing *t = ata_timing_find_mode(adev->pio_mode);
	स्थिर u16 *id = adev->id;
	अचिन्हित पूर्णांक cycle_समय = 0;
	पूर्णांक is_slave = adev->devno;
	स्थिर u8 pio = adev->pio_mode - XFER_PIO_0;

	अगर (id[ATA_ID_FIELD_VALID] & 2) अणु
		अगर (ata_id_has_iordy(id))
			cycle_समय = id[ATA_ID_EIDE_PIO_IORDY];
		अन्यथा
			cycle_समय = id[ATA_ID_EIDE_PIO];

		/* conservative "downgrade" क्रम all pre-ATA2 drives */
		अगर (pio < 3 && cycle_समय < t->cycle)
			cycle_समय = 0; /* use standard timing */
	पूर्ण

	अगर (!cycle_समय)
		cycle_समय = t->cycle;

	pata_bk3710_setpiomode(base, pair, is_slave, cycle_समय, pio);
पूर्ण

अटल व्योम pata_bk3710_chipinit(व्योम __iomem *base)
अणु
	/*
	 * REVISIT:  the ATA reset संकेत needs to be managed through a
	 * GPIO, which means it should come from platक्रमm_data.  Until
	 * we get and use such inक्रमmation, we have to trust that things
	 * have been reset beक्रमe we get here.
	 */

	/*
	 * Program the IDETIMP Register Value based on the following assumptions
	 *
	 * (ATA_IDETIMP_IDEEN		, ENABLE ) |
	 * (ATA_IDETIMP_PREPOST1	, DISABLE) |
	 * (ATA_IDETIMP_PREPOST0	, DISABLE) |
	 *
	 * DM6446 silicon rev 2.1 and earlier have no observed net benefit
	 * from enabling prefetch/postग_लिखो.
	 */
	ioग_लिखो16(BIT(15), base + BK3710_IDETIMP);

	/*
	 * UDMACTL Ultra-ATA DMA Control
	 * (ATA_UDMACTL_UDMAP1	, 0 ) |
	 * (ATA_UDMACTL_UDMAP0	, 0 )
	 *
	 */
	ioग_लिखो16(0, base + BK3710_UDMACTL);

	/*
	 * MISCCTL Miscellaneous Conrol Register
	 * (ATA_MISCCTL_HWNHLD1P	, 1 cycle)
	 * (ATA_MISCCTL_HWNHLD0P	, 1 cycle)
	 * (ATA_MISCCTL_TIMORIDE	, 1)
	 */
	ioग_लिखो32(0x001, base + BK3710_MISCCTL);

	/*
	 * IORDYTMP IORDY Timer क्रम Primary Register
	 * (ATA_IORDYTMP_IORDYTMP	, DISABLE)
	 */
	ioग_लिखो32(0, base + BK3710_IORDYTMP);

	/*
	 * Configure BMISP Register
	 * (ATA_BMISP_DMAEN1	, DISABLE )	|
	 * (ATA_BMISP_DMAEN0	, DISABLE )	|
	 * (ATA_BMISP_IORDYINT	, CLEAR)	|
	 * (ATA_BMISP_INTRSTAT	, CLEAR)	|
	 * (ATA_BMISP_DMAERROR	, CLEAR)
	 */
	ioग_लिखो16(0xE, base + BK3710_BMISP);

	pata_bk3710_setpiomode(base, शून्य, 0, 600, 0);
	pata_bk3710_setpiomode(base, शून्य, 1, 600, 0);
पूर्ण

अटल काष्ठा ata_port_operations pata_bk3710_ports_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= ata_cable_80wire,

	.set_piomode		= pata_bk3710_set_piomode,
	.set_dmamode		= pata_bk3710_set_dmamode,
पूर्ण;

अटल पूर्णांक __init pata_bk3710_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;
	काष्ठा resource *mem;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
	पूर्णांक irq;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस -ENODEV;

	clk_enable(clk);
	rate = clk_get_rate(clk);
	अगर (!rate)
		वापस -EINVAL;

	/* NOTE:  round *करोwn* to meet minimum timings; we count in घड़ीs */
	ideclk_period = 1000000000UL / rate;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		pr_err(DRV_NAME ": failed to get IRQ resource\n");
		वापस irq;
	पूर्ण

	base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* configure the Palmchip controller */
	pata_bk3710_chipinit(base);

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;
	ap = host->ports[0];

	ap->ops = &pata_bk3710_ports_ops;
	ap->pio_mask = ATA_PIO4;
	ap->mwdma_mask = ATA_MWDMA2;
	ap->udma_mask = rate < 100000000 ? ATA_UDMA4 : ATA_UDMA5;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	ap->ioaddr.data_addr		= base + BK3710_TF_OFFSET;
	ap->ioaddr.error_addr		= base + BK3710_TF_OFFSET + 1;
	ap->ioaddr.feature_addr		= base + BK3710_TF_OFFSET + 1;
	ap->ioaddr.nsect_addr		= base + BK3710_TF_OFFSET + 2;
	ap->ioaddr.lbal_addr		= base + BK3710_TF_OFFSET + 3;
	ap->ioaddr.lbam_addr		= base + BK3710_TF_OFFSET + 4;
	ap->ioaddr.lbah_addr		= base + BK3710_TF_OFFSET + 5;
	ap->ioaddr.device_addr		= base + BK3710_TF_OFFSET + 6;
	ap->ioaddr.status_addr		= base + BK3710_TF_OFFSET + 7;
	ap->ioaddr.command_addr		= base + BK3710_TF_OFFSET + 7;

	ap->ioaddr.altstatus_addr	= base + BK3710_CTL_OFFSET;
	ap->ioaddr.ctl_addr		= base + BK3710_CTL_OFFSET;

	ap->ioaddr.bmdma_addr		= base;

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx",
		      (अचिन्हित दीर्घ)base + BK3710_TF_OFFSET,
		      (अचिन्हित दीर्घ)base + BK3710_CTL_OFFSET);

	/* activate */
	वापस ata_host_activate(host, irq, ata_sff_पूर्णांकerrupt, 0,
				 &pata_bk3710_sht);
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:palm_bk3710");

अटल काष्ठा platक्रमm_driver pata_bk3710_driver = अणु
	.driver = अणु
		.name = "palm_bk3710",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pata_bk3710_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&pata_bk3710_driver, pata_bk3710_probe);
पूर्ण

module_init(pata_bk3710_init);
MODULE_LICENSE("GPL v2");
