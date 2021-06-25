<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EP93XX PATA controller driver.
 *
 * Copyright (c) 2012, Metasoft s.c.
 *	Rafal Prylowski <prylowski@metasoft.pl>
 *
 * Based on pata_scc.c, pata_icside.c and on earlier version of EP93XX
 * PATA driver by Lennert Buytenhek and Alessandro Zummo.
 * Read/Write timings, resource management and other improvements
 * from driver by Joao Ramos and Bartlomiej Zolnierkiewicz.
 * DMA engine support based on spi-ep93xx.c by Mika Westerberg.
 *
 * Original copyrights:
 *
 * Support क्रम Cirrus Logic's EP93xx (EP9312, EP9315) CPUs
 * PATA host controller driver.
 *
 * Copyright (c) 2009, Bartlomiej Zolnierkiewicz
 *
 * Heavily based on the ep93xx-ide.c driver:
 *
 * Copyright (c) 2009, Joao Ramos <joao.ramos@inov.pt>
 *		      INESC Inovacao (INOV)
 *
 * EP93XX PATA controller driver.
 * Copyright (C) 2007 Lennert Buytenhek <buytenh@wantstofly.org>
 *
 * An ATA driver क्रम the Cirrus Logic EP93xx PATA controller.
 *
 * Based on an earlier version by Alessandro Zummo, which is:
 *   Copyright (C) 2006 Tower Technologies
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#घोषणा DRV_NAME	"ep93xx-ide"
#घोषणा DRV_VERSION	"1.0"

क्रमागत अणु
	/* IDE Control Register */
	IDECTRL				= 0x00,
	IDECTRL_CS0N			= (1 << 0),
	IDECTRL_CS1N			= (1 << 1),
	IDECTRL_DIORN			= (1 << 5),
	IDECTRL_DIOWN			= (1 << 6),
	IDECTRL_INTRQ			= (1 << 9),
	IDECTRL_IORDY			= (1 << 10),
	/*
	 * the device IDE रेजिस्टर to be accessed is selected through
	 * IDECTRL रेजिस्टर's specific bitfields 'DA', 'CS1N' and 'CS0N':
	 *   b4   b3   b2    b1     b0
	 *   A2   A1   A0   CS1N   CS0N
	 * the values filled in this काष्ठाure allows the value to be directly
	 * ORed to the IDECTRL रेजिस्टर, hence giving directly the A[2:0] and
	 * CS1N/CS0N values क्रम each IDE रेजिस्टर.
	 * The values correspond to the transक्रमmation:
	 *   ((real IDE address) << 2) | CS1N value << 1 | CS0N value
	 */
	IDECTRL_ADDR_CMD		= 0 + 2, /* CS1 */
	IDECTRL_ADDR_DATA		= (ATA_REG_DATA << 2) + 2,
	IDECTRL_ADDR_ERROR		= (ATA_REG_ERR << 2) + 2,
	IDECTRL_ADDR_FEATURE		= (ATA_REG_FEATURE << 2) + 2,
	IDECTRL_ADDR_NSECT		= (ATA_REG_NSECT << 2) + 2,
	IDECTRL_ADDR_LBAL		= (ATA_REG_LBAL << 2) + 2,
	IDECTRL_ADDR_LBAM		= (ATA_REG_LBAM << 2) + 2,
	IDECTRL_ADDR_LBAH		= (ATA_REG_LBAH << 2) + 2,
	IDECTRL_ADDR_DEVICE		= (ATA_REG_DEVICE << 2) + 2,
	IDECTRL_ADDR_STATUS		= (ATA_REG_STATUS << 2) + 2,
	IDECTRL_ADDR_COMMAND		= (ATA_REG_CMD << 2) + 2,
	IDECTRL_ADDR_ALTSTATUS		= (0x06 << 2) + 1, /* CS0 */
	IDECTRL_ADDR_CTL		= (0x06 << 2) + 1, /* CS0 */

	/* IDE Configuration Register */
	IDECFG				= 0x04,
	IDECFG_IDEEN			= (1 << 0),
	IDECFG_PIO			= (1 << 1),
	IDECFG_MDMA			= (1 << 2),
	IDECFG_UDMA			= (1 << 3),
	IDECFG_MODE_SHIFT		= 4,
	IDECFG_MODE_MASK		= (0xf << 4),
	IDECFG_WST_SHIFT		= 8,
	IDECFG_WST_MASK			= (0x3 << 8),

	/* MDMA Operation Register */
	IDEMDMAOP			= 0x08,

	/* UDMA Operation Register */
	IDEUDMAOP			= 0x0c,
	IDEUDMAOP_UEN			= (1 << 0),
	IDEUDMAOP_RWOP			= (1 << 1),

	/* PIO/MDMA/UDMA Data Registers */
	IDEDATAOUT			= 0x10,
	IDEDATAIN			= 0x14,
	IDEMDMADATAOUT			= 0x18,
	IDEMDMADATAIN			= 0x1c,
	IDEUDMADATAOUT			= 0x20,
	IDEUDMADATAIN			= 0x24,

	/* UDMA Status Register */
	IDEUDMASTS			= 0x28,
	IDEUDMASTS_DMAIDE		= (1 << 16),
	IDEUDMASTS_INTIDE		= (1 << 17),
	IDEUDMASTS_SBUSY		= (1 << 18),
	IDEUDMASTS_NDO			= (1 << 24),
	IDEUDMASTS_NDI			= (1 << 25),
	IDEUDMASTS_N4X			= (1 << 26),

	/* UDMA Debug Status Register */
	IDEUDMADEBUG			= 0x2c,
पूर्ण;

काष्ठा ep93xx_pata_data अणु
	स्थिर काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *ide_base;
	काष्ठा ata_timing t;
	bool iordy;

	अचिन्हित दीर्घ udma_in_phys;
	अचिन्हित दीर्घ udma_out_phys;

	काष्ठा dma_chan *dma_rx_channel;
	काष्ठा ep93xx_dma_data dma_rx_data;
	काष्ठा dma_chan *dma_tx_channel;
	काष्ठा ep93xx_dma_data dma_tx_data;
पूर्ण;

अटल व्योम ep93xx_pata_clear_regs(व्योम __iomem *base)
अणु
	ग_लिखोl(IDECTRL_CS0N | IDECTRL_CS1N | IDECTRL_DIORN |
		IDECTRL_DIOWN, base + IDECTRL);

	ग_लिखोl(0, base + IDECFG);
	ग_लिखोl(0, base + IDEMDMAOP);
	ग_लिखोl(0, base + IDEUDMAOP);
	ग_लिखोl(0, base + IDEDATAOUT);
	ग_लिखोl(0, base + IDEDATAIN);
	ग_लिखोl(0, base + IDEMDMADATAOUT);
	ग_लिखोl(0, base + IDEMDMADATAIN);
	ग_लिखोl(0, base + IDEUDMADATAOUT);
	ग_लिखोl(0, base + IDEUDMADATAIN);
	ग_लिखोl(0, base + IDEUDMADEBUG);
पूर्ण

अटल bool ep93xx_pata_check_iordy(व्योम __iomem *base)
अणु
	वापस !!(पढ़ोl(base + IDECTRL) & IDECTRL_IORDY);
पूर्ण

/*
 * According to EP93xx User's Guide, WST field of IDECFG specअगरies number
 * of HCLK cycles to hold the data bus after a PIO ग_लिखो operation.
 * It should be programmed to guarantee following delays:
 *
 * PIO Mode   [ns]
 * 0          30
 * 1          20
 * 2          15
 * 3          10
 * 4          5
 *
 * Maximum possible value क्रम HCLK is 100MHz.
 */
अटल पूर्णांक ep93xx_pata_get_wst(पूर्णांक pio_mode)
अणु
	पूर्णांक val;

	अगर (pio_mode == 0)
		val = 3;
	अन्यथा अगर (pio_mode < 3)
		val = 2;
	अन्यथा
		val = 1;

	वापस val << IDECFG_WST_SHIFT;
पूर्ण

अटल व्योम ep93xx_pata_enable_pio(व्योम __iomem *base, पूर्णांक pio_mode)
अणु
	ग_लिखोl(IDECFG_IDEEN | IDECFG_PIO |
		ep93xx_pata_get_wst(pio_mode) |
		(pio_mode << IDECFG_MODE_SHIFT), base + IDECFG);
पूर्ण

/*
 * Based on delay loop found in mach-pxa/mp900.c.
 *
 * Single iteration should take 5 cpu cycles. This is 25ns assuming the
 * fastest ep93xx cpu speed (200MHz) and is better optimized क्रम PIO4 timings
 * than eg. 20ns.
 */
अटल व्योम ep93xx_pata_delay(अचिन्हित दीर्घ count)
अणु
	__यंत्र__ अस्थिर (
		"0:\n"
		"mov r0, r0\n"
		"subs %0, %1, #1\n"
		"bge 0b\n"
		: "=r" (count)
		: "0" (count)
	);
पूर्ण

अटल अचिन्हित दीर्घ ep93xx_pata_रुको_क्रम_iordy(व्योम __iomem *base,
						अचिन्हित दीर्घ t2)
अणु
	/*
	 * According to ATA specअगरication, IORDY pin can be first sampled
	 * tA = 35ns after activation of DIOR-/DIOW-. Maximum IORDY pulse
	 * width is tB = 1250ns.
	 *
	 * We are alपढ़ोy t2 delay loop iterations after activation of
	 * DIOR-/DIOW-, so we set समयout to (1250 + 35) / 25 - t2 additional
	 * delay loop iterations.
	 */
	अचिन्हित दीर्घ start = (1250 + 35) / 25 - t2;
	अचिन्हित दीर्घ counter = start;

	जबतक (!ep93xx_pata_check_iordy(base) && counter--)
		ep93xx_pata_delay(1);
	वापस start - counter;
पूर्ण

/* common part at start of ep93xx_pata_पढ़ो/ग_लिखो() */
अटल व्योम ep93xx_pata_rw_begin(व्योम __iomem *base, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ t1)
अणु
	ग_लिखोl(IDECTRL_DIOWN | IDECTRL_DIORN | addr, base + IDECTRL);
	ep93xx_pata_delay(t1);
पूर्ण

/* common part at end of ep93xx_pata_पढ़ो/ग_लिखो() */
अटल व्योम ep93xx_pata_rw_end(व्योम __iomem *base, अचिन्हित दीर्घ addr,
			       bool iordy, अचिन्हित दीर्घ t0, अचिन्हित दीर्घ t2,
			       अचिन्हित दीर्घ t2i)
अणु
	ep93xx_pata_delay(t2);
	/* lengthen t2 अगर needed */
	अगर (iordy)
		t2 += ep93xx_pata_रुको_क्रम_iordy(base, t2);
	ग_लिखोl(IDECTRL_DIOWN | IDECTRL_DIORN | addr, base + IDECTRL);
	अगर (t0 > t2 && t0 - t2 > t2i)
		ep93xx_pata_delay(t0 - t2);
	अन्यथा
		ep93xx_pata_delay(t2i);
पूर्ण

अटल u16 ep93xx_pata_पढ़ो(काष्ठा ep93xx_pata_data *drv_data,
			    अचिन्हित दीर्घ addr,
			    bool reg)
अणु
	व्योम __iomem *base = drv_data->ide_base;
	स्थिर काष्ठा ata_timing *t = &drv_data->t;
	अचिन्हित दीर्घ t0 = reg ? t->cyc8b : t->cycle;
	अचिन्हित दीर्घ t2 = reg ? t->act8b : t->active;
	अचिन्हित दीर्घ t2i = reg ? t->rec8b : t->recover;

	ep93xx_pata_rw_begin(base, addr, t->setup);
	ग_लिखोl(IDECTRL_DIOWN | addr, base + IDECTRL);
	/*
	 * The IDEDATAIN रेजिस्टर is loaded from the DD pins at the positive
	 * edge of the DIORN संकेत. (EP93xx UG p27-14)
	 */
	ep93xx_pata_rw_end(base, addr, drv_data->iordy, t0, t2, t2i);
	वापस पढ़ोl(base + IDEDATAIN);
पूर्ण

/* IDE रेजिस्टर पढ़ो */
अटल u16 ep93xx_pata_पढ़ो_reg(काष्ठा ep93xx_pata_data *drv_data,
				अचिन्हित दीर्घ addr)
अणु
	वापस ep93xx_pata_पढ़ो(drv_data, addr, true);
पूर्ण

/* PIO data पढ़ो */
अटल u16 ep93xx_pata_पढ़ो_data(काष्ठा ep93xx_pata_data *drv_data,
				 अचिन्हित दीर्घ addr)
अणु
	वापस ep93xx_pata_पढ़ो(drv_data, addr, false);
पूर्ण

अटल व्योम ep93xx_pata_ग_लिखो(काष्ठा ep93xx_pata_data *drv_data,
			      u16 value, अचिन्हित दीर्घ addr,
			      bool reg)
अणु
	व्योम __iomem *base = drv_data->ide_base;
	स्थिर काष्ठा ata_timing *t = &drv_data->t;
	अचिन्हित दीर्घ t0 = reg ? t->cyc8b : t->cycle;
	अचिन्हित दीर्घ t2 = reg ? t->act8b : t->active;
	अचिन्हित दीर्घ t2i = reg ? t->rec8b : t->recover;

	ep93xx_pata_rw_begin(base, addr, t->setup);
	/*
	 * Value from IDEDATAOUT रेजिस्टर is driven onto the DD pins when
	 * DIOWN is low. (EP93xx UG p27-13)
	 */
	ग_लिखोl(value, base + IDEDATAOUT);
	ग_लिखोl(IDECTRL_DIORN | addr, base + IDECTRL);
	ep93xx_pata_rw_end(base, addr, drv_data->iordy, t0, t2, t2i);
पूर्ण

/* IDE रेजिस्टर ग_लिखो */
अटल व्योम ep93xx_pata_ग_लिखो_reg(काष्ठा ep93xx_pata_data *drv_data,
				  u16 value, अचिन्हित दीर्घ addr)
अणु
	ep93xx_pata_ग_लिखो(drv_data, value, addr, true);
पूर्ण

/* PIO data ग_लिखो */
अटल व्योम ep93xx_pata_ग_लिखो_data(काष्ठा ep93xx_pata_data *drv_data,
				   u16 value, अचिन्हित दीर्घ addr)
अणु
	ep93xx_pata_ग_लिखो(drv_data, value, addr, false);
पूर्ण

अटल व्योम ep93xx_pata_set_piomode(काष्ठा ata_port *ap,
				    काष्ठा ata_device *adev)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	/*
	 * Calculate timings क्रम the delay loop, assuming ep93xx cpu speed
	 * is 200MHz (maximum possible क्रम ep93xx). If actual cpu speed is
	 * slower, we will रुको a bit दीर्घer in each delay.
	 * Additional भागision of cpu speed by 5, because single iteration
	 * of our delay loop takes 5 cpu cycles (25ns).
	 */
	अचिन्हित दीर्घ T = 1000000 / (200 / 5);

	ata_timing_compute(adev, adev->pio_mode, &drv_data->t, T, 0);
	अगर (pair && pair->pio_mode) अणु
		काष्ठा ata_timing t;
		ata_timing_compute(pair, pair->pio_mode, &t, T, 0);
		ata_timing_merge(&t, &drv_data->t, &drv_data->t,
			ATA_TIMING_SETUP | ATA_TIMING_8BIT);
	पूर्ण
	drv_data->iordy = ata_pio_need_iordy(adev);

	ep93xx_pata_enable_pio(drv_data->ide_base,
			       adev->pio_mode - XFER_PIO_0);
पूर्ण

/* Note: original code is ata_sff_check_status */
अटल u8 ep93xx_pata_check_status(काष्ठा ata_port *ap)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	वापस ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_STATUS);
पूर्ण

अटल u8 ep93xx_pata_check_altstatus(काष्ठा ata_port *ap)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	वापस ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_ALTSTATUS);
पूर्ण

/* Note: original code is ata_sff_tf_load */
अटल व्योम ep93xx_pata_tf_load(काष्ठा ata_port *ap,
				स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	अगर (tf->ctl != ap->last_ctl) अणु
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->ctl, IDECTRL_ADDR_CTL);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण

	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->hob_feature,
			IDECTRL_ADDR_FEATURE);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->hob_nsect,
			IDECTRL_ADDR_NSECT);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->hob_lbal,
			IDECTRL_ADDR_LBAL);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->hob_lbam,
			IDECTRL_ADDR_LBAM);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->hob_lbah,
			IDECTRL_ADDR_LBAH);
	पूर्ण

	अगर (is_addr) अणु
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->feature,
			IDECTRL_ADDR_FEATURE);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->nsect, IDECTRL_ADDR_NSECT);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->lbal, IDECTRL_ADDR_LBAL);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->lbam, IDECTRL_ADDR_LBAM);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->lbah, IDECTRL_ADDR_LBAH);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE)
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->device,
			IDECTRL_ADDR_DEVICE);

	ata_रुको_idle(ap);
पूर्ण

/* Note: original code is ata_sff_tf_पढ़ो */
अटल व्योम ep93xx_pata_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	tf->command = ep93xx_pata_check_status(ap);
	tf->feature = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_FEATURE);
	tf->nsect = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_NSECT);
	tf->lbal = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_LBAL);
	tf->lbam = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_LBAM);
	tf->lbah = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_LBAH);
	tf->device = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_DEVICE);

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->ctl | ATA_HOB,
			IDECTRL_ADDR_CTL);
		tf->hob_feature = ep93xx_pata_पढ़ो_reg(drv_data,
			IDECTRL_ADDR_FEATURE);
		tf->hob_nsect = ep93xx_pata_पढ़ो_reg(drv_data,
			IDECTRL_ADDR_NSECT);
		tf->hob_lbal = ep93xx_pata_पढ़ो_reg(drv_data,
			IDECTRL_ADDR_LBAL);
		tf->hob_lbam = ep93xx_pata_पढ़ो_reg(drv_data,
			IDECTRL_ADDR_LBAM);
		tf->hob_lbah = ep93xx_pata_पढ़ो_reg(drv_data,
			IDECTRL_ADDR_LBAH);
		ep93xx_pata_ग_लिखो_reg(drv_data, tf->ctl, IDECTRL_ADDR_CTL);
		ap->last_ctl = tf->ctl;
	पूर्ण
पूर्ण

/* Note: original code is ata_sff_exec_command */
अटल व्योम ep93xx_pata_exec_command(काष्ठा ata_port *ap,
				     स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	ep93xx_pata_ग_लिखो_reg(drv_data, tf->command,
			  IDECTRL_ADDR_COMMAND);
	ata_sff_छोड़ो(ap);
पूर्ण

/* Note: original code is ata_sff_dev_select */
अटल व्योम ep93xx_pata_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	u8 पंचांगp = ATA_DEVICE_OBS;

	अगर (device != 0)
		पंचांगp |= ATA_DEV1;

	ep93xx_pata_ग_लिखो_reg(drv_data, पंचांगp, IDECTRL_ADDR_DEVICE);
	ata_sff_छोड़ो(ap);	/* needed; also flushes, क्रम mmio */
पूर्ण

/* Note: original code is ata_sff_set_devctl */
अटल व्योम ep93xx_pata_set_devctl(काष्ठा ata_port *ap, u8 ctl)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	ep93xx_pata_ग_लिखो_reg(drv_data, ctl, IDECTRL_ADDR_CTL);
पूर्ण

/* Note: original code is ata_sff_data_xfer */
अटल अचिन्हित पूर्णांक ep93xx_pata_data_xfer(काष्ठा ata_queued_cmd *qc,
					  अचिन्हित अक्षर *buf,
					  अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_port *ap = qc->dev->link->ap;
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	u16 *data = (u16 *)buf;
	अचिन्हित पूर्णांक words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	जबतक (words--)
		अगर (rw == READ)
			*data++ = cpu_to_le16(
				ep93xx_pata_पढ़ो_data(
					drv_data, IDECTRL_ADDR_DATA));
		अन्यथा
			ep93xx_pata_ग_लिखो_data(drv_data, le16_to_cpu(*data++),
				IDECTRL_ADDR_DATA);

	/* Transfer trailing 1 byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		buf += buflen - 1;

		अगर (rw == READ) अणु
			*pad = cpu_to_le16(
				ep93xx_pata_पढ़ो_data(
					drv_data, IDECTRL_ADDR_DATA));
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			ep93xx_pata_ग_लिखो_data(drv_data, le16_to_cpu(*pad),
					  IDECTRL_ADDR_DATA);
		पूर्ण
		words++;
	पूर्ण

	वापस words << 1;
पूर्ण

/* Note: original code is ata_devchk */
अटल bool ep93xx_pata_device_is_present(काष्ठा ata_port *ap,
					  अचिन्हित पूर्णांक device)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	u8 nsect, lbal;

	ap->ops->sff_dev_select(ap, device);

	ep93xx_pata_ग_लिखो_reg(drv_data, 0x55, IDECTRL_ADDR_NSECT);
	ep93xx_pata_ग_लिखो_reg(drv_data, 0xaa, IDECTRL_ADDR_LBAL);

	ep93xx_pata_ग_लिखो_reg(drv_data, 0xaa, IDECTRL_ADDR_NSECT);
	ep93xx_pata_ग_लिखो_reg(drv_data, 0x55, IDECTRL_ADDR_LBAL);

	ep93xx_pata_ग_लिखो_reg(drv_data, 0x55, IDECTRL_ADDR_NSECT);
	ep93xx_pata_ग_लिखो_reg(drv_data, 0xaa, IDECTRL_ADDR_LBAL);

	nsect = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_NSECT);
	lbal = ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_LBAL);

	अगर ((nsect == 0x55) && (lbal == 0xaa))
		वापस true;

	वापस false;
पूर्ण

/* Note: original code is ata_sff_रुको_after_reset */
अटल पूर्णांक ep93xx_pata_रुको_after_reset(काष्ठा ata_link *link,
					अचिन्हित पूर्णांक devmask,
					अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	अचिन्हित पूर्णांक dev0 = devmask & (1 << 0);
	अचिन्हित पूर्णांक dev1 = devmask & (1 << 1);
	पूर्णांक rc, ret = 0;

	ata_msleep(ap, ATA_WAIT_AFTER_RESET);

	/* always check पढ़ोiness of the master device */
	rc = ata_sff_रुको_पढ़ोy(link, deadline);
	/*
	 * -ENODEV means the odd clown क्रमgot the D7 pullकरोwn resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	अगर (rc)
		वापस rc;

	/*
	 * अगर device 1 was found in ata_devchk, रुको क्रम रेजिस्टर
	 * access briefly, then रुको क्रम BSY to clear.
	 */
	अगर (dev1) अणु
		पूर्णांक i;

		ap->ops->sff_dev_select(ap, 1);

		/*
		 * Wait क्रम रेजिस्टर access.  Some ATAPI devices fail
		 * to set nsect/lbal after reset, so करोn't waste too
		 * much समय on it.  We're gonna रुको क्रम !BSY anyway.
		 */
		क्रम (i = 0; i < 2; i++) अणु
			u8 nsect, lbal;

			nsect = ep93xx_pata_पढ़ो_reg(drv_data,
				IDECTRL_ADDR_NSECT);
			lbal = ep93xx_pata_पढ़ो_reg(drv_data,
				IDECTRL_ADDR_LBAL);
			अगर (nsect == 1 && lbal == 1)
				अवरोध;
			msleep(50);	/* give drive a breather */
		पूर्ण

		rc = ata_sff_रुको_पढ़ोy(link, deadline);
		अगर (rc) अणु
			अगर (rc != -ENODEV)
				वापस rc;
			ret = rc;
		पूर्ण
	पूर्ण
	/* is all this really necessary? */
	ap->ops->sff_dev_select(ap, 0);
	अगर (dev1)
		ap->ops->sff_dev_select(ap, 1);
	अगर (dev0)
		ap->ops->sff_dev_select(ap, 0);

	वापस ret;
पूर्ण

/* Note: original code is ata_bus_softreset */
अटल पूर्णांक ep93xx_pata_bus_softreset(काष्ठा ata_port *ap, अचिन्हित पूर्णांक devmask,
				     अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	ep93xx_pata_ग_लिखो_reg(drv_data, ap->ctl, IDECTRL_ADDR_CTL);
	udelay(20);		/* FIXME: flush */
	ep93xx_pata_ग_लिखो_reg(drv_data, ap->ctl | ATA_SRST, IDECTRL_ADDR_CTL);
	udelay(20);		/* FIXME: flush */
	ep93xx_pata_ग_लिखो_reg(drv_data, ap->ctl, IDECTRL_ADDR_CTL);
	ap->last_ctl = ap->ctl;

	वापस ep93xx_pata_रुको_after_reset(&ap->link, devmask, deadline);
पूर्ण

अटल व्योम ep93xx_pata_release_dma(काष्ठा ep93xx_pata_data *drv_data)
अणु
	अगर (drv_data->dma_rx_channel) अणु
		dma_release_channel(drv_data->dma_rx_channel);
		drv_data->dma_rx_channel = शून्य;
	पूर्ण
	अगर (drv_data->dma_tx_channel) अणु
		dma_release_channel(drv_data->dma_tx_channel);
		drv_data->dma_tx_channel = शून्य;
	पूर्ण
पूर्ण

अटल bool ep93xx_pata_dma_filter(काष्ठा dma_chan *chan, व्योम *filter_param)
अणु
	अगर (ep93xx_dma_chan_is_m2p(chan))
		वापस false;

	chan->निजी = filter_param;
	वापस true;
पूर्ण

अटल व्योम ep93xx_pata_dma_init(काष्ठा ep93xx_pata_data *drv_data)
अणु
	स्थिर काष्ठा platक्रमm_device *pdev = drv_data->pdev;
	dma_cap_mask_t mask;
	काष्ठा dma_slave_config conf;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/*
	 * Request two channels क्रम IDE. Another possibility would be
	 * to request only one channel, and reprogram it's direction at
	 * start of new transfer.
	 */
	drv_data->dma_rx_data.port = EP93XX_DMA_IDE;
	drv_data->dma_rx_data.direction = DMA_DEV_TO_MEM;
	drv_data->dma_rx_data.name = "ep93xx-pata-rx";
	drv_data->dma_rx_channel = dma_request_channel(mask,
		ep93xx_pata_dma_filter, &drv_data->dma_rx_data);
	अगर (!drv_data->dma_rx_channel)
		वापस;

	drv_data->dma_tx_data.port = EP93XX_DMA_IDE;
	drv_data->dma_tx_data.direction = DMA_MEM_TO_DEV;
	drv_data->dma_tx_data.name = "ep93xx-pata-tx";
	drv_data->dma_tx_channel = dma_request_channel(mask,
		ep93xx_pata_dma_filter, &drv_data->dma_tx_data);
	अगर (!drv_data->dma_tx_channel) अणु
		dma_release_channel(drv_data->dma_rx_channel);
		वापस;
	पूर्ण

	/* Configure receive channel direction and source address */
	स_रखो(&conf, 0, माप(conf));
	conf.direction = DMA_DEV_TO_MEM;
	conf.src_addr = drv_data->udma_in_phys;
	conf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	अगर (dmaengine_slave_config(drv_data->dma_rx_channel, &conf)) अणु
		dev_err(&pdev->dev, "failed to configure rx dma channel\n");
		ep93xx_pata_release_dma(drv_data);
		वापस;
	पूर्ण

	/* Configure transmit channel direction and destination address */
	स_रखो(&conf, 0, माप(conf));
	conf.direction = DMA_MEM_TO_DEV;
	conf.dst_addr = drv_data->udma_out_phys;
	conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	अगर (dmaengine_slave_config(drv_data->dma_tx_channel, &conf)) अणु
		dev_err(&pdev->dev, "failed to configure tx dma channel\n");
		ep93xx_pata_release_dma(drv_data);
	पूर्ण
पूर्ण

अटल व्योम ep93xx_pata_dma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा dma_async_tx_descriptor *txd;
	काष्ठा ep93xx_pata_data *drv_data = qc->ap->host->निजी_data;
	व्योम __iomem *base = drv_data->ide_base;
	काष्ठा ata_device *adev = qc->dev;
	u32 v = qc->dma_dir == DMA_TO_DEVICE ? IDEUDMAOP_RWOP : 0;
	काष्ठा dma_chan *channel = qc->dma_dir == DMA_TO_DEVICE
		? drv_data->dma_tx_channel : drv_data->dma_rx_channel;

	txd = dmaengine_prep_slave_sg(channel, qc->sg, qc->n_elem, qc->dma_dir,
		DMA_CTRL_ACK);
	अगर (!txd) अणु
		dev_err(qc->ap->dev, "failed to prepare slave for sg dma\n");
		वापस;
	पूर्ण
	txd->callback = शून्य;
	txd->callback_param = शून्य;

	अगर (dmaengine_submit(txd) < 0) अणु
		dev_err(qc->ap->dev, "failed to submit dma transfer\n");
		वापस;
	पूर्ण
	dma_async_issue_pending(channel);

	/*
	 * When enabling UDMA operation, IDEUDMAOP रेजिस्टर needs to be
	 * programmed in three step sequence:
	 * 1) set or clear the RWOP bit,
	 * 2) perक्रमm dummy पढ़ो of the रेजिस्टर,
	 * 3) set the UEN bit.
	 */
	ग_लिखोl(v, base + IDEUDMAOP);
	पढ़ोl(base + IDEUDMAOP);
	ग_लिखोl(v | IDEUDMAOP_UEN, base + IDEUDMAOP);

	ग_लिखोl(IDECFG_IDEEN | IDECFG_UDMA |
		((adev->xfer_mode - XFER_UDMA_0) << IDECFG_MODE_SHIFT),
		base + IDECFG);
पूर्ण

अटल व्योम ep93xx_pata_dma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ep93xx_pata_data *drv_data = qc->ap->host->निजी_data;
	व्योम __iomem *base = drv_data->ide_base;

	/* terminate all dma transfers, अगर not yet finished */
	dmaengine_terminate_all(drv_data->dma_rx_channel);
	dmaengine_terminate_all(drv_data->dma_tx_channel);

	/*
	 * To properly stop IDE-DMA, IDEUDMAOP रेजिस्टर must to be cleared
	 * and IDECTRL रेजिस्टर must be set to शेष value.
	 */
	ग_लिखोl(0, base + IDEUDMAOP);
	ग_लिखोl(पढ़ोl(base + IDECTRL) | IDECTRL_DIOWN | IDECTRL_DIORN |
		IDECTRL_CS0N | IDECTRL_CS1N, base + IDECTRL);

	ep93xx_pata_enable_pio(drv_data->ide_base,
		qc->dev->pio_mode - XFER_PIO_0);

	ata_sff_dma_छोड़ो(qc->ap);
पूर्ण

अटल व्योम ep93xx_pata_dma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	qc->ap->ops->sff_exec_command(qc->ap, &qc->tf);
पूर्ण

अटल u8 ep93xx_pata_dma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;
	u32 val = पढ़ोl(drv_data->ide_base + IDEUDMASTS);

	/*
	 * UDMA Status Register bits:
	 *
	 * DMAIDE - DMA request संकेत from UDMA state machine,
	 * INTIDE - INT line generated by UDMA because of errors in the
	 *          state machine,
	 * SBUSY - UDMA state machine busy, not in idle state,
	 * NDO   - error क्रम data-out not completed,
	 * NDI   - error क्रम data-in not completed,
	 * N4X   - error क्रम data transferred not multiplies of four
	 *         32-bit words.
	 * (EP93xx UG p27-17)
	 */
	अगर (val & IDEUDMASTS_NDO || val & IDEUDMASTS_NDI ||
	    val & IDEUDMASTS_N4X || val & IDEUDMASTS_INTIDE)
		वापस ATA_DMA_ERR;

	/* पढ़ो INTRQ (INT[3]) pin input state */
	अगर (पढ़ोl(drv_data->ide_base + IDECTRL) & IDECTRL_INTRQ)
		वापस ATA_DMA_INTR;

	अगर (val & IDEUDMASTS_SBUSY || val & IDEUDMASTS_DMAIDE)
		वापस ATA_DMA_ACTIVE;

	वापस 0;
पूर्ण

/* Note: original code is ata_sff_softreset */
अटल पूर्णांक ep93xx_pata_softreset(काष्ठा ata_link *al, अचिन्हित पूर्णांक *classes,
				 अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = al->ap;
	अचिन्हित पूर्णांक slave_possible = ap->flags & ATA_FLAG_SLAVE_POSS;
	अचिन्हित पूर्णांक devmask = 0;
	पूर्णांक rc;
	u8 err;

	/* determine अगर device 0/1 are present */
	अगर (ep93xx_pata_device_is_present(ap, 0))
		devmask |= (1 << 0);
	अगर (slave_possible && ep93xx_pata_device_is_present(ap, 1))
		devmask |= (1 << 1);

	/* select device 0 again */
	ap->ops->sff_dev_select(al->ap, 0);

	/* issue bus reset */
	rc = ep93xx_pata_bus_softreset(ap, devmask, deadline);
	/* अगर link is ocuppied, -ENODEV too is an error */
	अगर (rc && (rc != -ENODEV || sata_scr_valid(al))) अणु
		ata_link_err(al, "SRST failed (errno=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classअगरy(&al->device[0], devmask & (1 << 0),
					  &err);
	अगर (slave_possible && err != 0x81)
		classes[1] = ata_sff_dev_classअगरy(&al->device[1],
						  devmask & (1 << 1), &err);

	वापस 0;
पूर्ण

/* Note: original code is ata_sff_drain_fअगरo */
अटल व्योम ep93xx_pata_drain_fअगरo(काष्ठा ata_queued_cmd *qc)
अणु
	पूर्णांक count;
	काष्ठा ata_port *ap;
	काष्ठा ep93xx_pata_data *drv_data;

	/* We only need to flush incoming data when a command was running */
	अगर (qc == शून्य || qc->dma_dir == DMA_TO_DEVICE)
		वापस;

	ap = qc->ap;
	drv_data = ap->host->निजी_data;
	/* Drain up to 64K of data beक्रमe we give up this recovery method */
	क्रम (count = 0; (ap->ops->sff_check_status(ap) & ATA_DRQ)
		     && count < 65536; count += 2)
		ep93xx_pata_पढ़ो_reg(drv_data, IDECTRL_ADDR_DATA);

	/* Can become DEBUG later */
	अगर (count)
		ata_port_dbg(ap, "drained %d bytes to clear DRQ.\n", count);

पूर्ण

अटल पूर्णांक ep93xx_pata_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा ep93xx_pata_data *drv_data = ap->host->निजी_data;

	/*
	 * Set timings to safe values at startup (= number of ns from ATA
	 * specअगरication), we'll चयन to properly calculated values later.
	 */
	drv_data->t = *ata_timing_find_mode(XFER_PIO_0);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ep93xx_pata_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	/* ep93xx dma implementation limit */
	.sg_tablesize		= 32,
	/* ep93xx dma can't transfer 65536 bytes at once */
	.dma_boundary		= 0x7fff,
पूर्ण;

अटल काष्ठा ata_port_operations ep93xx_pata_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.qc_prep		= ata_noop_qc_prep,

	.softreset		= ep93xx_pata_softreset,
	.hardreset		= ATA_OP_शून्य,

	.sff_dev_select		= ep93xx_pata_dev_select,
	.sff_set_devctl		= ep93xx_pata_set_devctl,
	.sff_check_status	= ep93xx_pata_check_status,
	.sff_check_altstatus	= ep93xx_pata_check_altstatus,
	.sff_tf_load		= ep93xx_pata_tf_load,
	.sff_tf_पढ़ो		= ep93xx_pata_tf_पढ़ो,
	.sff_exec_command	= ep93xx_pata_exec_command,
	.sff_data_xfer		= ep93xx_pata_data_xfer,
	.sff_drain_fअगरo		= ep93xx_pata_drain_fअगरo,
	.sff_irq_clear		= ATA_OP_शून्य,

	.set_piomode		= ep93xx_pata_set_piomode,

	.bmdma_setup		= ep93xx_pata_dma_setup,
	.bmdma_start		= ep93xx_pata_dma_start,
	.bmdma_stop		= ep93xx_pata_dma_stop,
	.bmdma_status		= ep93xx_pata_dma_status,

	.cable_detect		= ata_cable_unknown,
	.port_start		= ep93xx_pata_port_start,
पूर्ण;

अटल पूर्णांक ep93xx_pata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_pata_data *drv_data;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	पूर्णांक irq;
	काष्ठा resource *mem_res;
	व्योम __iomem *ide_base;
	पूर्णांक err;

	err = ep93xx_ide_acquire_gpio(pdev);
	अगर (err)
		वापस err;

	/* INT[3] (IRQ_EP93XX_EXT3) line connected as pull करोwn */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = -ENXIO;
		जाओ err_rel_gpio;
	पूर्ण

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ide_base = devm_ioremap_resource(&pdev->dev, mem_res);
	अगर (IS_ERR(ide_base)) अणु
		err = PTR_ERR(ide_base);
		जाओ err_rel_gpio;
	पूर्ण

	drv_data = devm_kzalloc(&pdev->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data) अणु
		err = -ENXIO;
		जाओ err_rel_gpio;
	पूर्ण

	drv_data->pdev = pdev;
	drv_data->ide_base = ide_base;
	drv_data->udma_in_phys = mem_res->start + IDEUDMADATAIN;
	drv_data->udma_out_phys = mem_res->start + IDEUDMADATAOUT;
	ep93xx_pata_dma_init(drv_data);

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host) अणु
		err = -ENXIO;
		जाओ err_rel_dma;
	पूर्ण

	ep93xx_pata_clear_regs(ide_base);

	host->निजी_data = drv_data;

	ap = host->ports[0];
	ap->dev = &pdev->dev;
	ap->ops = &ep93xx_pata_port_ops;
	ap->flags |= ATA_FLAG_SLAVE_POSS;
	ap->pio_mask = ATA_PIO4;

	/*
	 * Maximum UDMA modes:
	 * EP931x rev.E0 - UDMA2
	 * EP931x rev.E1 - UDMA3
	 * EP931x rev.E2 - UDMA4
	 *
	 * MWDMA support was हटाओd from EP931x rev.E2,
	 * so this driver supports only UDMA modes.
	 */
	अगर (drv_data->dma_rx_channel && drv_data->dma_tx_channel) अणु
		पूर्णांक chip_rev = ep93xx_chip_revision();

		अगर (chip_rev == EP93XX_CHIP_REV_E1)
			ap->udma_mask = ATA_UDMA3;
		अन्यथा अगर (chip_rev == EP93XX_CHIP_REV_E2)
			ap->udma_mask = ATA_UDMA4;
		अन्यथा
			ap->udma_mask = ATA_UDMA2;
	पूर्ण

	/* शेषs, pio 0 */
	ep93xx_pata_enable_pio(ide_base, 0);

	dev_info(&pdev->dev, "version " DRV_VERSION "\n");

	/* activate host */
	err = ata_host_activate(host, irq, ata_bmdma_पूर्णांकerrupt, 0,
		&ep93xx_pata_sht);
	अगर (err == 0)
		वापस 0;

err_rel_dma:
	ep93xx_pata_release_dma(drv_data);
err_rel_gpio:
	ep93xx_ide_release_gpio(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक ep93xx_pata_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा ep93xx_pata_data *drv_data = host->निजी_data;

	ata_host_detach(host);
	ep93xx_pata_release_dma(drv_data);
	ep93xx_pata_clear_regs(drv_data->ide_base);
	ep93xx_ide_release_gpio(pdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_pata_platक्रमm_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = ep93xx_pata_probe,
	.हटाओ = ep93xx_pata_हटाओ,
पूर्ण;

module_platक्रमm_driver(ep93xx_pata_platक्रमm_driver);

MODULE_AUTHOR("Alessandro Zummo, Lennert Buytenhek, Joao Ramos, "
		"Bartlomiej Zolnierkiewicz, Rafal Prylowski");
MODULE_DESCRIPTION("low-level driver for cirrus ep93xx IDE controller");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:pata_ep93xx");
