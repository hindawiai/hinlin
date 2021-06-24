<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Palmchip bk3710 IDE controller
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 *
 * ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/ide.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>

/* Offset of the primary पूर्णांकerface रेजिस्टरs */
#घोषणा IDE_PALM_ATA_PRI_REG_OFFSET 0x1F0

/* Primary Control Offset */
#घोषणा IDE_PALM_ATA_PRI_CTL_OFFSET 0x3F6

#घोषणा BK3710_BMICP		0x00
#घोषणा BK3710_BMISP		0x02
#घोषणा BK3710_BMIDTP		0x04
#घोषणा BK3710_IDETIMP		0x40
#घोषणा BK3710_IDESTATUS	0x47
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

अटल अचिन्हित ideclk_period; /* in nanoseconds */

काष्ठा palm_bk3710_udmatiming अणु
	अचिन्हित पूर्णांक rpसमय;	/* tRP -- Ready to छोड़ो समय (nsec) */
	अचिन्हित पूर्णांक cycleसमय;	/* tCYCTYP2/2 -- avg Cycle Time (nsec) */
				/* tENV is always a minimum of 20 nsec */
पूर्ण;

अटल स्थिर काष्ठा palm_bk3710_udmatiming palm_bk3710_udmatimings[6] = अणु
	अणु 160, 240 / 2 पूर्ण,	/* UDMA Mode 0 */
	अणु 125, 160 / 2 पूर्ण,	/* UDMA Mode 1 */
	अणु 100, 120 / 2 पूर्ण,	/* UDMA Mode 2 */
	अणु 100,  90 / 2 पूर्ण,	/* UDMA Mode 3 */
	अणु 100,  60 / 2 पूर्ण,	/* UDMA Mode 4 */
	अणु  85,  40 / 2 पूर्ण,	/* UDMA Mode 5 */
पूर्ण;

अटल व्योम palm_bk3710_setudmamode(व्योम __iomem *base, अचिन्हित पूर्णांक dev,
				    अचिन्हित पूर्णांक mode)
अणु
	u8 tenv, trp, t0;
	u32 val32;
	u16 val16;

	/* DMA Data Setup */
	t0 = DIV_ROUND_UP(palm_bk3710_udmatimings[mode].cycleसमय,
			  ideclk_period) - 1;
	tenv = DIV_ROUND_UP(20, ideclk_period) - 1;
	trp = DIV_ROUND_UP(palm_bk3710_udmatimings[mode].rpसमय,
			   ideclk_period) - 1;

	/* udmastb Ultra DMA Access Strobe Width */
	val32 = पढ़ोl(base + BK3710_UDMASTB) & (0xFF << (dev ? 0 : 8));
	val32 |= (t0 << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_UDMASTB);

	/* udmatrp Ultra DMA Ready to Pause Time */
	val32 = पढ़ोl(base + BK3710_UDMATRP) & (0xFF << (dev ? 0 : 8));
	val32 |= (trp << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_UDMATRP);

	/* udmaenv Ultra DMA envelop Time */
	val32 = पढ़ोl(base + BK3710_UDMAENV) & (0xFF << (dev ? 0 : 8));
	val32 |= (tenv << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_UDMAENV);

	/* Enable UDMA क्रम Device */
	val16 = पढ़ोw(base + BK3710_UDMACTL) | (1 << dev);
	ग_लिखोw(val16, base + BK3710_UDMACTL);
पूर्ण

अटल व्योम palm_bk3710_setdmamode(व्योम __iomem *base, अचिन्हित पूर्णांक dev,
				   अचिन्हित लघु min_cycle,
				   अचिन्हित पूर्णांक mode)
अणु
	u8 td, tkw, t0;
	u32 val32;
	u16 val16;
	काष्ठा ide_timing *t;
	पूर्णांक cycleसमय;

	t = ide_timing_find_mode(mode);
	cycleसमय = max_t(पूर्णांक, t->cycle, min_cycle);

	/* DMA Data Setup */
	t0 = DIV_ROUND_UP(cycleसमय, ideclk_period);
	td = DIV_ROUND_UP(t->active, ideclk_period);
	tkw = t0 - td - 1;
	td -= 1;

	val32 = पढ़ोl(base + BK3710_DMASTB) & (0xFF << (dev ? 0 : 8));
	val32 |= (td << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_DMASTB);

	val32 = पढ़ोl(base + BK3710_DMARCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= (tkw << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_DMARCVR);

	/* Disable UDMA क्रम Device */
	val16 = पढ़ोw(base + BK3710_UDMACTL) & ~(1 << dev);
	ग_लिखोw(val16, base + BK3710_UDMACTL);
पूर्ण

अटल व्योम palm_bk3710_setpiomode(व्योम __iomem *base, ide_drive_t *mate,
				   अचिन्हित पूर्णांक dev, अचिन्हित पूर्णांक cycleसमय,
				   अचिन्हित पूर्णांक mode)
अणु
	u8 t2, t2i, t0;
	u32 val32;
	काष्ठा ide_timing *t;

	t = ide_timing_find_mode(XFER_PIO_0 + mode);

	/* PIO Data Setup */
	t0 = DIV_ROUND_UP(cycleसमय, ideclk_period);
	t2 = DIV_ROUND_UP(t->active, ideclk_period);

	t2i = t0 - t2 - 1;
	t2 -= 1;

	val32 = पढ़ोl(base + BK3710_DATSTB) & (0xFF << (dev ? 0 : 8));
	val32 |= (t2 << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_DATSTB);

	val32 = पढ़ोl(base + BK3710_DATRCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= (t2i << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_DATRCVR);

	अगर (mate) अणु
		u8 mode2 = mate->pio_mode - XFER_PIO_0;

		अगर (mode2 < mode)
			mode = mode2;
	पूर्ण

	/* TASKखाता Setup */
	t0 = DIV_ROUND_UP(t->cyc8b, ideclk_period);
	t2 = DIV_ROUND_UP(t->act8b, ideclk_period);

	t2i = t0 - t2 - 1;
	t2 -= 1;

	val32 = पढ़ोl(base + BK3710_REGSTB) & (0xFF << (dev ? 0 : 8));
	val32 |= (t2 << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_REGSTB);

	val32 = पढ़ोl(base + BK3710_REGRCVR) & (0xFF << (dev ? 0 : 8));
	val32 |= (t2i << (dev ? 8 : 0));
	ग_लिखोl(val32, base + BK3710_REGRCVR);
पूर्ण

अटल व्योम palm_bk3710_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	पूर्णांक is_slave = drive->dn & 1;
	व्योम __iomem *base = (व्योम __iomem *)hwअगर->dma_base;
	स्थिर u8 xferspeed = drive->dma_mode;

	अगर (xferspeed >= XFER_UDMA_0) अणु
		palm_bk3710_setudmamode(base, is_slave,
					xferspeed - XFER_UDMA_0);
	पूर्ण अन्यथा अणु
		palm_bk3710_setdmamode(base, is_slave,
				       drive->id[ATA_ID_EIDE_DMA_MIN],
				       xferspeed);
	पूर्ण
पूर्ण

अटल व्योम palm_bk3710_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित पूर्णांक cycle_समय;
	पूर्णांक is_slave = drive->dn & 1;
	ide_drive_t *mate;
	व्योम __iomem *base = (व्योम __iomem *)hwअगर->dma_base;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * Obtain the drive PIO data क्रम tuning the Palm Chip रेजिस्टरs
	 */
	cycle_समय = ide_pio_cycle_समय(drive, pio);
	mate = ide_get_pair_dev(drive);
	palm_bk3710_setpiomode(base, mate, is_slave, cycle_समय, pio);
पूर्ण

अटल व्योम palm_bk3710_chipinit(व्योम __iomem *base)
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
	ग_लिखोw(BIT(15), base + BK3710_IDETIMP);

	/*
	 * UDMACTL Ultra-ATA DMA Control
	 * (ATA_UDMACTL_UDMAP1	, 0 ) |
	 * (ATA_UDMACTL_UDMAP0	, 0 )
	 *
	 */
	ग_लिखोw(0, base + BK3710_UDMACTL);

	/*
	 * MISCCTL Miscellaneous Conrol Register
	 * (ATA_MISCCTL_HWNHLD1P	, 1 cycle)
	 * (ATA_MISCCTL_HWNHLD0P	, 1 cycle)
	 * (ATA_MISCCTL_TIMORIDE	, 1)
	 */
	ग_लिखोl(0x001, base + BK3710_MISCCTL);

	/*
	 * IORDYTMP IORDY Timer क्रम Primary Register
	 * (ATA_IORDYTMP_IORDYTMP     , 0xffff  )
	 */
	ग_लिखोl(0xFFFF, base + BK3710_IORDYTMP);

	/*
	 * Configure BMISP Register
	 * (ATA_BMISP_DMAEN1	, DISABLE )	|
	 * (ATA_BMISP_DMAEN0	, DISABLE )	|
	 * (ATA_BMISP_IORDYINT	, CLEAR)	|
	 * (ATA_BMISP_INTRSTAT	, CLEAR)	|
	 * (ATA_BMISP_DMAERROR	, CLEAR)
	 */
	ग_लिखोw(0, base + BK3710_BMISP);

	palm_bk3710_setpiomode(base, शून्य, 0, 600, 0);
	palm_bk3710_setpiomode(base, शून्य, 1, 600, 0);
पूर्ण

अटल u8 palm_bk3710_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	वापस ATA_CBL_PATA80;
पूर्ण

अटल पूर्णांक palm_bk3710_init_dma(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	prपूर्णांकk(KERN_INFO "    %s: MMIO-DMA\n", hwअगर->name);

	अगर (ide_allocate_dma_engine(hwअगर))
		वापस -1;

	hwअगर->dma_base = hwअगर->io_ports.data_addr - IDE_PALM_ATA_PRI_REG_OFFSET;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops palm_bk3710_ports_ops = अणु
	.set_pio_mode		= palm_bk3710_set_pio_mode,
	.set_dma_mode		= palm_bk3710_set_dma_mode,
	.cable_detect		= palm_bk3710_cable_detect,
पूर्ण;

अटल काष्ठा ide_port_info palm_bk3710_port_info __initdata = अणु
	.init_dma		= palm_bk3710_init_dma,
	.port_ops		= &palm_bk3710_ports_ops,
	.dma_ops		= &sff_dma_ops,
	.host_flags		= IDE_HFLAG_MMIO,
	.pio_mask		= ATA_PIO4,
	.mwdma_mask		= ATA_MWDMA2,
	.chipset		= ide_palm3710,
पूर्ण;

अटल पूर्णांक __init palm_bk3710_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;
	काष्ठा resource *mem, *irq;
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate, mem_size;
	पूर्णांक i, rc;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;

	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस -ENODEV;

	clk_enable(clk);
	rate = clk_get_rate(clk);
	अगर (!rate)
		वापस -EINVAL;

	/* NOTE:  round *करोwn* to meet minimum timings; we count in घड़ीs */
	ideclk_period = 1000000000UL / rate;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mem == शून्य) अणु
		prपूर्णांकk(KERN_ERR "failed to get memory region resource\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (irq == शून्य) अणु
		prपूर्णांकk(KERN_ERR "failed to get IRQ resource\n");
		वापस -ENODEV;
	पूर्ण

	mem_size = resource_size(mem);
	अगर (request_mem_region(mem->start, mem_size, "palm_bk3710") == शून्य) अणु
		prपूर्णांकk(KERN_ERR "failed to request memory region\n");
		वापस -EBUSY;
	पूर्ण

	base = ioremap(mem->start, mem_size);
	अगर (!base) अणु
		prपूर्णांकk(KERN_ERR "failed to map IO memory\n");
		release_mem_region(mem->start, mem_size);
		वापस -ENOMEM;
	पूर्ण

	/* Configure the Palm Chip controller */
	palm_bk3710_chipinit(base);

	स_रखो(&hw, 0, माप(hw));
	क्रम (i = 0; i < IDE_NR_PORTS - 2; i++)
		hw.io_ports_array[i] = (अचिन्हित दीर्घ)
				(base + IDE_PALM_ATA_PRI_REG_OFFSET + i);
	hw.io_ports.ctl_addr = (अचिन्हित दीर्घ)
			(base + IDE_PALM_ATA_PRI_CTL_OFFSET);
	hw.irq = irq->start;
	hw.dev = &pdev->dev;

	palm_bk3710_port_info.udma_mask = rate < 100000000 ? ATA_UDMA4 :
							     ATA_UDMA5;

	/* Register the IDE पूर्णांकerface with Linux */
	rc = ide_host_add(&palm_bk3710_port_info, hws, 1, शून्य);
	अगर (rc)
		जाओ out;

	वापस 0;
out:
	prपूर्णांकk(KERN_WARNING "Palm Chip BK3710 IDE Register Fail\n");
	वापस rc;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:palm_bk3710");

अटल काष्ठा platक्रमm_driver platक्रमm_bk_driver = अणु
	.driver = अणु
		.name = "palm_bk3710",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init palm_bk3710_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&platक्रमm_bk_driver, palm_bk3710_probe);
पूर्ण

module_init(palm_bk3710_init);
MODULE_LICENSE("GPL");
