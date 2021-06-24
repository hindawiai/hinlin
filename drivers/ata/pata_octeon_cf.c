<शैली गुरु>
/*
 * Driver क्रम the Octeon bootbus compact flash.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 - 2012 Cavium Inc.
 * Copyright (C) 2008 Wind River Systems
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/octeon/octeon.h>

/*
 * The Octeon bootbus compact flash पूर्णांकerface is connected in at least
 * 3 dअगरferent configurations on various evaluation boards:
 *
 * -- 8  bits no irq, no DMA
 * -- 16 bits no irq, no DMA
 * -- 16 bits True IDE mode with DMA, but no irq.
 *
 * In the last हाल the DMA engine can generate an पूर्णांकerrupt when the
 * transfer is complete.  For the first two हालs only PIO is supported.
 *
 */

#घोषणा DRV_NAME	"pata_octeon_cf"
#घोषणा DRV_VERSION	"2.2"

/* Poll पूर्णांकerval in nS. */
#घोषणा OCTEON_CF_BUSY_POLL_INTERVAL 500000

#घोषणा DMA_CFG 0
#घोषणा DMA_TIM 0x20
#घोषणा DMA_INT 0x38
#घोषणा DMA_INT_EN 0x50

काष्ठा octeon_cf_port अणु
	काष्ठा hrसमयr delayed_finish;
	काष्ठा ata_port *ap;
	पूर्णांक dma_finished;
	व्योम		*c0;
	अचिन्हित पूर्णांक cs0;
	अचिन्हित पूर्णांक cs1;
	bool is_true_ide;
	u64 dma_base;
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा octeon_cf_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक enable_dma;
module_param(enable_dma, पूर्णांक, 0444);
MODULE_PARM_DESC(enable_dma,
		 "Enable use of DMA on interfaces that support it (0=no dma [default], 1=use dma)");

/**
 * Convert nanosecond based समय to setting used in the
 * boot bus timing रेजिस्टर, based on timing multiple
 */
अटल अचिन्हित पूर्णांक ns_to_tim_reg(अचिन्हित पूर्णांक tim_mult, अचिन्हित पूर्णांक nsecs)
अणु
	अचिन्हित पूर्णांक val;

	/*
	 * Compute # of eघड़ी periods to get desired duration in
	 * nanoseconds.
	 */
	val = DIV_ROUND_UP(nsecs * (octeon_get_io_घड़ी_rate() / 1000000),
			  1000 * tim_mult);

	वापस val;
पूर्ण

अटल व्योम octeon_cf_set_boot_reg_cfg(पूर्णांक cs, अचिन्हित पूर्णांक multiplier)
अणु
	जोड़ cvmx_mio_boot_reg_cfgx reg_cfg;
	अचिन्हित पूर्णांक tim_mult;

	चयन (multiplier) अणु
	हाल 8:
		tim_mult = 3;
		अवरोध;
	हाल 4:
		tim_mult = 0;
		अवरोध;
	हाल 2:
		tim_mult = 2;
		अवरोध;
	शेष:
		tim_mult = 1;
		अवरोध;
	पूर्ण

	reg_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_CFGX(cs));
	reg_cfg.s.dmack = 0;	/* Don't निश्चित DMACK on access */
	reg_cfg.s.tim_mult = tim_mult;	/* Timing mutiplier */
	reg_cfg.s.rd_dly = 0;	/* Sample on falling edge of BOOT_OE */
	reg_cfg.s.sam = 0;	/* Don't combine ग_लिखो and output enable */
	reg_cfg.s.we_ext = 0;	/* No ग_लिखो enable extension */
	reg_cfg.s.oe_ext = 0;	/* No पढ़ो enable extension */
	reg_cfg.s.en = 1;	/* Enable this region */
	reg_cfg.s.orbit = 0;	/* Don't combine with previous region */
	reg_cfg.s.ale = 0;	/* Don't करो address multiplexing */
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_REG_CFGX(cs), reg_cfg.u64);
पूर्ण

/**
 * Called after libata determines the needed PIO mode. This
 * function programs the Octeon bootbus regions to support the
 * timing requirements of the PIO mode.
 *
 * @ap:     ATA port inक्रमmation
 * @dev:    ATA device
 */
अटल व्योम octeon_cf_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *dev)
अणु
	काष्ठा octeon_cf_port *cf_port = ap->निजी_data;
	जोड़ cvmx_mio_boot_reg_timx reg_tim;
	पूर्णांक T;
	काष्ठा ata_timing timing;

	अचिन्हित पूर्णांक भाग;
	पूर्णांक use_iordy;
	पूर्णांक trh;
	पूर्णांक छोड़ो;
	/* These names are timing parameters from the ATA spec */
	पूर्णांक t2;

	/*
	 * A भागisor value of four will overflow the timing fields at
	 * घड़ी rates greater than 800MHz
	 */
	अगर (octeon_get_io_घड़ी_rate() <= 800000000)
		भाग = 4;
	अन्यथा
		भाग = 8;
	T = (पूर्णांक)((1000000000000LL * भाग) / octeon_get_io_घड़ी_rate());

	BUG_ON(ata_timing_compute(dev, dev->pio_mode, &timing, T, T));

	t2 = timing.active;
	अगर (t2)
		t2--;

	trh = ns_to_tim_reg(भाग, 20);
	अगर (trh)
		trh--;

	छोड़ो = (पूर्णांक)timing.cycle - (पूर्णांक)timing.active -
		(पूर्णांक)timing.setup - trh;
	अगर (छोड़ो < 0)
		छोड़ो = 0;
	अगर (छोड़ो)
		छोड़ो--;

	octeon_cf_set_boot_reg_cfg(cf_port->cs0, भाग);
	अगर (cf_port->is_true_ide)
		/* True IDE mode, program both chip selects.  */
		octeon_cf_set_boot_reg_cfg(cf_port->cs1, भाग);


	use_iordy = ata_pio_need_iordy(dev);

	reg_tim.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_TIMX(cf_port->cs0));
	/* Disable page mode */
	reg_tim.s.pagem = 0;
	/* Enable dynamic timing */
	reg_tim.s.रुकोm = use_iordy;
	/* Pages are disabled */
	reg_tim.s.pages = 0;
	/* We करोn't use multiplexed address mode */
	reg_tim.s.ale = 0;
	/* Not used */
	reg_tim.s.page = 0;
	/* Time after IORDY to coninue to निश्चित the data */
	reg_tim.s.रुको = 0;
	/* Time to रुको to complete the cycle. */
	reg_tim.s.छोड़ो = छोड़ो;
	/* How दीर्घ to hold after a ग_लिखो to de-निश्चित CE. */
	reg_tim.s.wr_hld = trh;
	/* How दीर्घ to रुको after a पढ़ो to de-निश्चित CE. */
	reg_tim.s.rd_hld = trh;
	/* How दीर्घ ग_लिखो enable is निश्चितed */
	reg_tim.s.we = t2;
	/* How दीर्घ पढ़ो enable is निश्चितed */
	reg_tim.s.oe = t2;
	/* Time after CE that पढ़ो/ग_लिखो starts */
	reg_tim.s.ce = ns_to_tim_reg(भाग, 5);
	/* Time beक्रमe CE that address is valid */
	reg_tim.s.adr = 0;

	/* Program the bootbus region timing क्रम the data port chip select. */
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_REG_TIMX(cf_port->cs0), reg_tim.u64);
	अगर (cf_port->is_true_ide)
		/* True IDE mode, program both chip selects.  */
		cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_REG_TIMX(cf_port->cs1),
			       reg_tim.u64);
पूर्ण

अटल व्योम octeon_cf_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *dev)
अणु
	काष्ठा octeon_cf_port *cf_port = ap->निजी_data;
	जोड़ cvmx_mio_boot_pin_defs pin_defs;
	जोड़ cvmx_mio_boot_dma_timx dma_tim;
	अचिन्हित पूर्णांक oe_a;
	अचिन्हित पूर्णांक oe_n;
	अचिन्हित पूर्णांक dma_ackh;
	अचिन्हित पूर्णांक dma_arq;
	अचिन्हित पूर्णांक छोड़ो;
	अचिन्हित पूर्णांक T0, Tkr, Td;
	अचिन्हित पूर्णांक tim_mult;
	पूर्णांक c;

	स्थिर काष्ठा ata_timing *timing;

	timing = ata_timing_find_mode(dev->dma_mode);
	T0	= timing->cycle;
	Td	= timing->active;
	Tkr	= timing->recover;
	dma_ackh = timing->dmack_hold;

	dma_tim.u64 = 0;
	/* dma_tim.s.tim_mult = 0 --> 4x */
	tim_mult = 4;

	/* not spec'ed, value in eघड़ीs, not affected by tim_mult */
	dma_arq = 8;
	छोड़ो = 25 - dma_arq * 1000 /
		(octeon_get_io_घड़ी_rate() / 1000000); /* Tz */

	oe_a = Td;
	/* Tkr from cf spec, lengthened to meet T0 */
	oe_n = max(T0 - oe_a, Tkr);

	pin_defs.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_PIN_DEFS);

	/* DMA channel number. */
	c = (cf_port->dma_base & 8) >> 3;

	/* Invert the polarity अगर the शेष is 0*/
	dma_tim.s.dmack_pi = (pin_defs.u64 & (1ull << (11 + c))) ? 0 : 1;

	dma_tim.s.oe_n = ns_to_tim_reg(tim_mult, oe_n);
	dma_tim.s.oe_a = ns_to_tim_reg(tim_mult, oe_a);

	/*
	 * This is tI, C.F. spec. says 0, but Sony CF card requires
	 * more, we use 20 nS.
	 */
	dma_tim.s.dmack_s = ns_to_tim_reg(tim_mult, 20);
	dma_tim.s.dmack_h = ns_to_tim_reg(tim_mult, dma_ackh);

	dma_tim.s.dmarq = dma_arq;
	dma_tim.s.छोड़ो = ns_to_tim_reg(tim_mult, छोड़ो);

	dma_tim.s.rd_dly = 0;	/* Sample right on edge */

	/*  ग_लिखोs only */
	dma_tim.s.we_n = ns_to_tim_reg(tim_mult, oe_n);
	dma_tim.s.we_a = ns_to_tim_reg(tim_mult, oe_a);

	pr_debug("ns to ticks (mult %d) of %d is: %d\n", tim_mult, 60,
		 ns_to_tim_reg(tim_mult, 60));
	pr_debug("oe_n: %d, oe_a: %d, dmack_s: %d, dmack_h: %d, dmarq: %d, pause: %d\n",
		 dma_tim.s.oe_n, dma_tim.s.oe_a, dma_tim.s.dmack_s,
		 dma_tim.s.dmack_h, dma_tim.s.dmarq, dma_tim.s.छोड़ो);

	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_TIM, dma_tim.u64);
पूर्ण

/**
 * Handle an 8 bit I/O request.
 *
 * @qc:         Queued command
 * @buffer:     Data buffer
 * @buflen:     Length of the buffer.
 * @rw:         True to ग_लिखो.
 */
अटल अचिन्हित पूर्णांक octeon_cf_data_xfer8(काष्ठा ata_queued_cmd *qc,
					 अचिन्हित अक्षर *buffer,
					 अचिन्हित पूर्णांक buflen,
					 पूर्णांक rw)
अणु
	काष्ठा ata_port *ap		= qc->dev->link->ap;
	व्योम __iomem *data_addr		= ap->ioaddr.data_addr;
	अचिन्हित दीर्घ words;
	पूर्णांक count;

	words = buflen;
	अगर (rw) अणु
		count = 16;
		जबतक (words--) अणु
			ioग_लिखो8(*buffer, data_addr);
			buffer++;
			/*
			 * Every 16 ग_लिखोs करो a पढ़ो so the bootbus
			 * FIFO करोesn't fill up.
			 */
			अगर (--count == 0) अणु
				ioपढ़ो8(ap->ioaddr.altstatus_addr);
				count = 16;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ioपढ़ो8_rep(data_addr, buffer, words);
	पूर्ण
	वापस buflen;
पूर्ण

/**
 * Handle a 16 bit I/O request.
 *
 * @qc:         Queued command
 * @buffer:     Data buffer
 * @buflen:     Length of the buffer.
 * @rw:         True to ग_लिखो.
 */
अटल अचिन्हित पूर्णांक octeon_cf_data_xfer16(काष्ठा ata_queued_cmd *qc,
					  अचिन्हित अक्षर *buffer,
					  अचिन्हित पूर्णांक buflen,
					  पूर्णांक rw)
अणु
	काष्ठा ata_port *ap		= qc->dev->link->ap;
	व्योम __iomem *data_addr		= ap->ioaddr.data_addr;
	अचिन्हित दीर्घ words;
	पूर्णांक count;

	words = buflen / 2;
	अगर (rw) अणु
		count = 16;
		जबतक (words--) अणु
			ioग_लिखो16(*(uपूर्णांक16_t *)buffer, data_addr);
			buffer += माप(uपूर्णांक16_t);
			/*
			 * Every 16 ग_लिखोs करो a पढ़ो so the bootbus
			 * FIFO करोesn't fill up.
			 */
			अगर (--count == 0) अणु
				ioपढ़ो8(ap->ioaddr.altstatus_addr);
				count = 16;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (words--) अणु
			*(uपूर्णांक16_t *)buffer = ioपढ़ो16(data_addr);
			buffer += माप(uपूर्णांक16_t);
		पूर्ण
	पूर्ण
	/* Transfer trailing 1 byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		__le16 align_buf[1] = अणु 0 पूर्ण;

		अगर (rw == READ) अणु
			align_buf[0] = cpu_to_le16(ioपढ़ो16(data_addr));
			स_नकल(buffer, align_buf, 1);
		पूर्ण अन्यथा अणु
			स_नकल(align_buf, buffer, 1);
			ioग_लिखो16(le16_to_cpu(align_buf[0]), data_addr);
		पूर्ण
		words++;
	पूर्ण
	वापस buflen;
पूर्ण

/**
 * Read the taskfile क्रम 16bit non-True IDE only.
 */
अटल व्योम octeon_cf_tf_पढ़ो16(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	u16 blob;
	/* The base of the रेजिस्टरs is at ioaddr.data_addr. */
	व्योम __iomem *base = ap->ioaddr.data_addr;

	blob = __raw_पढ़ोw(base + 0xc);
	tf->feature = blob >> 8;

	blob = __raw_पढ़ोw(base + 2);
	tf->nsect = blob & 0xff;
	tf->lbal = blob >> 8;

	blob = __raw_पढ़ोw(base + 4);
	tf->lbam = blob & 0xff;
	tf->lbah = blob >> 8;

	blob = __raw_पढ़ोw(base + 6);
	tf->device = blob & 0xff;
	tf->command = blob >> 8;

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		अगर (likely(ap->ioaddr.ctl_addr)) अणु
			ioग_लिखो8(tf->ctl | ATA_HOB, ap->ioaddr.ctl_addr);

			blob = __raw_पढ़ोw(base + 0xc);
			tf->hob_feature = blob >> 8;

			blob = __raw_पढ़ोw(base + 2);
			tf->hob_nsect = blob & 0xff;
			tf->hob_lbal = blob >> 8;

			blob = __raw_पढ़ोw(base + 4);
			tf->hob_lbam = blob & 0xff;
			tf->hob_lbah = blob >> 8;

			ioग_लिखो8(tf->ctl, ap->ioaddr.ctl_addr);
			ap->last_ctl = tf->ctl;
		पूर्ण अन्यथा अणु
			WARN_ON(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 octeon_cf_check_status16(काष्ठा ata_port *ap)
अणु
	u16 blob;
	व्योम __iomem *base = ap->ioaddr.data_addr;

	blob = __raw_पढ़ोw(base + 6);
	वापस blob >> 8;
पूर्ण

अटल पूर्णांक octeon_cf_softreset16(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
				 अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *base = ap->ioaddr.data_addr;
	पूर्णांक rc;
	u8 err;

	DPRINTK("about to softreset\n");
	__raw_ग_लिखोw(ap->ctl, base + 0xe);
	udelay(20);
	__raw_ग_लिखोw(ap->ctl | ATA_SRST, base + 0xe);
	udelay(20);
	__raw_ग_लिखोw(ap->ctl, base + 0xe);

	rc = ata_sff_रुको_after_reset(link, 1, deadline);
	अगर (rc) अणु
		ata_link_err(link, "SRST failed (errno=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classअगरy(&link->device[0], 1, &err);
	DPRINTK("EXIT, classes[0]=%u [1]=%u\n", classes[0], classes[1]);
	वापस 0;
पूर्ण

/**
 * Load the taskfile क्रम 16bit non-True IDE only.  The device_addr is
 * not loaded, we करो this as part of octeon_cf_exec_command16.
 */
अटल व्योम octeon_cf_tf_load16(काष्ठा ata_port *ap,
				स्थिर काष्ठा ata_taskfile *tf)
अणु
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;
	/* The base of the रेजिस्टरs is at ioaddr.data_addr. */
	व्योम __iomem *base = ap->ioaddr.data_addr;

	अगर (tf->ctl != ap->last_ctl) अणु
		ioग_लिखो8(tf->ctl, ap->ioaddr.ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण
	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		__raw_ग_लिखोw(tf->hob_feature << 8, base + 0xc);
		__raw_ग_लिखोw(tf->hob_nsect | tf->hob_lbal << 8, base + 2);
		__raw_ग_लिखोw(tf->hob_lbam | tf->hob_lbah << 8, base + 4);
		VPRINTK("hob: feat 0x%X nsect 0x%X, lba 0x%X 0x%X 0x%X\n",
			tf->hob_feature,
			tf->hob_nsect,
			tf->hob_lbal,
			tf->hob_lbam,
			tf->hob_lbah);
	पूर्ण
	अगर (is_addr) अणु
		__raw_ग_लिखोw(tf->feature << 8, base + 0xc);
		__raw_ग_लिखोw(tf->nsect | tf->lbal << 8, base + 2);
		__raw_ग_लिखोw(tf->lbam | tf->lbah << 8, base + 4);
		VPRINTK("feat 0x%X nsect 0x%X, lba 0x%X 0x%X 0x%X\n",
			tf->feature,
			tf->nsect,
			tf->lbal,
			tf->lbam,
			tf->lbah);
	पूर्ण
	ata_रुको_idle(ap);
पूर्ण


अटल व्योम octeon_cf_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
/*  There is only one device, करो nothing. */
	वापस;
पूर्ण

/*
 * Issue ATA command to host controller.  The device_addr is also sent
 * as it must be written in a combined ग_लिखो with the command.
 */
अटल व्योम octeon_cf_exec_command16(काष्ठा ata_port *ap,
				स्थिर काष्ठा ata_taskfile *tf)
अणु
	/* The base of the रेजिस्टरs is at ioaddr.data_addr. */
	व्योम __iomem *base = ap->ioaddr.data_addr;
	u16 blob;

	अगर (tf->flags & ATA_TFLAG_DEVICE) अणु
		VPRINTK("device 0x%X\n", tf->device);
		blob = tf->device;
	पूर्ण अन्यथा अणु
		blob = 0;
	पूर्ण

	DPRINTK("ata%u: cmd 0x%X\n", ap->prपूर्णांक_id, tf->command);
	blob |= (tf->command << 8);
	__raw_ग_लिखोw(blob, base + 6);


	ata_रुको_idle(ap);
पूर्ण

अटल व्योम octeon_cf_ata_port_noaction(काष्ठा ata_port *ap)
अणु
पूर्ण

अटल व्योम octeon_cf_dma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा octeon_cf_port *cf_port;

	cf_port = ap->निजी_data;
	DPRINTK("ENTER\n");
	/* issue r/w command */
	qc->cursg = qc->sg;
	cf_port->dma_finished = 0;
	ap->ops->sff_exec_command(ap, &qc->tf);
	DPRINTK("EXIT\n");
पूर्ण

/**
 * Start a DMA transfer that was alपढ़ोy setup
 *
 * @qc:     Inक्रमmation about the DMA
 */
अटल व्योम octeon_cf_dma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा octeon_cf_port *cf_port = qc->ap->निजी_data;
	जोड़ cvmx_mio_boot_dma_cfgx mio_boot_dma_cfg;
	जोड़ cvmx_mio_boot_dma_पूर्णांकx mio_boot_dma_पूर्णांक;
	काष्ठा scatterlist *sg;

	VPRINTK("%d scatterlists\n", qc->n_elem);

	/* Get the scatter list entry we need to DMA पूर्णांकo */
	sg = qc->cursg;
	BUG_ON(!sg);

	/*
	 * Clear the DMA complete status.
	 */
	mio_boot_dma_पूर्णांक.u64 = 0;
	mio_boot_dma_पूर्णांक.s.करोne = 1;
	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT, mio_boot_dma_पूर्णांक.u64);

	/* Enable the पूर्णांकerrupt.  */
	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT_EN, mio_boot_dma_पूर्णांक.u64);

	/* Set the direction of the DMA */
	mio_boot_dma_cfg.u64 = 0;
#अगर_घोषित __LITTLE_ENDIAN
	mio_boot_dma_cfg.s.endian = 1;
#पूर्ण_अगर
	mio_boot_dma_cfg.s.en = 1;
	mio_boot_dma_cfg.s.rw = ((qc->tf.flags & ATA_TFLAG_WRITE) != 0);

	/*
	 * Don't stop the DMA अगर the device deनिश्चितs DMARQ. Many
	 * compact flashes deनिश्चित DMARQ क्रम a लघु समय between
	 * sectors. Instead of stopping and restarting the DMA, we'll
	 * let the hardware करो it. If the DMA is really stopped early
	 * due to an error condition, a later समयout will क्रमce us to
	 * stop.
	 */
	mio_boot_dma_cfg.s.clr = 0;

	/* Size is specअगरied in 16bit words and minus one notation */
	mio_boot_dma_cfg.s.size = sg_dma_len(sg) / 2 - 1;

	/* We need to swap the high and low bytes of every 16 bits */
	mio_boot_dma_cfg.s.swap8 = 1;

	mio_boot_dma_cfg.s.adr = sg_dma_address(sg);

	VPRINTK("%s %d bytes address=%p\n",
		(mio_boot_dma_cfg.s.rw) ? "write" : "read", sg->length,
		(व्योम *)(अचिन्हित दीर्घ)mio_boot_dma_cfg.s.adr);

	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_CFG, mio_boot_dma_cfg.u64);
पूर्ण

/**
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 */
अटल अचिन्हित पूर्णांक octeon_cf_dma_finished(काष्ठा ata_port *ap,
					काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	काष्ठा octeon_cf_port *cf_port = ap->निजी_data;
	जोड़ cvmx_mio_boot_dma_cfgx dma_cfg;
	जोड़ cvmx_mio_boot_dma_पूर्णांकx dma_पूर्णांक;
	u8 status;

	VPRINTK("ata%u: protocol %d task_state %d\n",
		ap->prपूर्णांक_id, qc->tf.protocol, ap->hsm_task_state);


	अगर (ap->hsm_task_state != HSM_ST_LAST)
		वापस 0;

	dma_cfg.u64 = cvmx_पढ़ो_csr(cf_port->dma_base + DMA_CFG);
	अगर (dma_cfg.s.size != 0xfffff) अणु
		/* Error, the transfer was not complete.  */
		qc->err_mask |= AC_ERR_HOST_BUS;
		ap->hsm_task_state = HSM_ST_ERR;
	पूर्ण

	/* Stop and clear the dma engine.  */
	dma_cfg.u64 = 0;
	dma_cfg.s.size = -1;
	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_CFG, dma_cfg.u64);

	/* Disable the पूर्णांकerrupt.  */
	dma_पूर्णांक.u64 = 0;
	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT_EN, dma_पूर्णांक.u64);

	/* Clear the DMA complete status */
	dma_पूर्णांक.s.करोne = 1;
	cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT, dma_पूर्णांक.u64);

	status = ap->ops->sff_check_status(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	अगर (unlikely(qc->err_mask) && (qc->tf.protocol == ATA_PROT_DMA))
		ata_ehi_push_desc(ehi, "DMA stat 0x%x", status);

	वापस 1;
पूर्ण

/*
 * Check अगर any queued commands have more DMAs, अगर so start the next
 * transfer, अन्यथा करो end of transfer handling.
 */
अटल irqवापस_t octeon_cf_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा octeon_cf_port *cf_port;
	पूर्णांक i;
	अचिन्हित पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	DPRINTK("ENTER\n");
	क्रम (i = 0; i < host->n_ports; i++) अणु
		u8 status;
		काष्ठा ata_port *ap;
		काष्ठा ata_queued_cmd *qc;
		जोड़ cvmx_mio_boot_dma_पूर्णांकx dma_पूर्णांक;
		जोड़ cvmx_mio_boot_dma_cfgx dma_cfg;

		ap = host->ports[i];
		cf_port = ap->निजी_data;

		dma_पूर्णांक.u64 = cvmx_पढ़ो_csr(cf_port->dma_base + DMA_INT);
		dma_cfg.u64 = cvmx_पढ़ो_csr(cf_port->dma_base + DMA_CFG);

		qc = ata_qc_from_tag(ap, ap->link.active_tag);

		अगर (!qc || (qc->tf.flags & ATA_TFLAG_POLLING))
			जारी;

		अगर (dma_पूर्णांक.s.करोne && !dma_cfg.s.en) अणु
			अगर (!sg_is_last(qc->cursg)) अणु
				qc->cursg = sg_next(qc->cursg);
				handled = 1;
				octeon_cf_dma_start(qc);
				जारी;
			पूर्ण अन्यथा अणु
				cf_port->dma_finished = 1;
			पूर्ण
		पूर्ण
		अगर (!cf_port->dma_finished)
			जारी;
		status = ioपढ़ो8(ap->ioaddr.altstatus_addr);
		अगर (status & (ATA_BUSY | ATA_DRQ)) अणु
			/*
			 * We are busy, try to handle it later.  This
			 * is the DMA finished पूर्णांकerrupt, and it could
			 * take a little जबतक क्रम the card to be
			 * पढ़ोy क्रम more commands.
			 */
			/* Clear DMA irq. */
			dma_पूर्णांक.u64 = 0;
			dma_पूर्णांक.s.करोne = 1;
			cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT,
				       dma_पूर्णांक.u64);
			hrसमयr_start_range_ns(&cf_port->delayed_finish,
					       ns_to_kसमय(OCTEON_CF_BUSY_POLL_INTERVAL),
					       OCTEON_CF_BUSY_POLL_INTERVAL / 5,
					       HRTIMER_MODE_REL);
			handled = 1;
		पूर्ण अन्यथा अणु
			handled |= octeon_cf_dma_finished(ap, qc);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&host->lock, flags);
	DPRINTK("EXIT\n");
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल क्रमागत hrसमयr_restart octeon_cf_delayed_finish(काष्ठा hrसमयr *hrt)
अणु
	काष्ठा octeon_cf_port *cf_port = container_of(hrt,
						      काष्ठा octeon_cf_port,
						      delayed_finish);
	काष्ठा ata_port *ap = cf_port->ap;
	काष्ठा ata_host *host = ap->host;
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित दीर्घ flags;
	u8 status;
	क्रमागत hrसमयr_restart rv = HRTIMER_NORESTART;

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * If the port is not रुकोing क्रम completion, it must have
	 * handled it previously.  The hsm_task_state is
	 * रक्षित by host->lock.
	 */
	अगर (ap->hsm_task_state != HSM_ST_LAST || !cf_port->dma_finished)
		जाओ out;

	status = ioपढ़ो8(ap->ioaddr.altstatus_addr);
	अगर (status & (ATA_BUSY | ATA_DRQ)) अणु
		/* Still busy, try again. */
		hrसमयr_क्रमward_now(hrt,
				    ns_to_kसमय(OCTEON_CF_BUSY_POLL_INTERVAL));
		rv = HRTIMER_RESTART;
		जाओ out;
	पूर्ण
	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING)))
		octeon_cf_dma_finished(ap, qc);
out:
	spin_unlock_irqrestore(&host->lock, flags);
	वापस rv;
पूर्ण

अटल व्योम octeon_cf_dev_config(काष्ठा ata_device *dev)
अणु
	/*
	 * A maximum of 2^20 - 1 16 bit transfers are possible with
	 * the bootbus DMA.  So we need to throttle max_sectors to
	 * (2^12 - 1 == 4095) to assure that this can never happen.
	 */
	dev->max_sectors = min(dev->max_sectors, 4095U);
पूर्ण

/*
 * We करोn't करो ATAPI DMA so वापस 0.
 */
अटल पूर्णांक octeon_cf_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक octeon_cf_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		WARN_ON(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf रेजिस्टरs */
		octeon_cf_dma_setup(qc);	    /* set up dma */
		octeon_cf_dma_start(qc);	    /* initiate dma */
		ap->hsm_task_state = HSM_ST_LAST;
		अवरोध;

	हाल ATAPI_PROT_DMA:
		dev_err(ap->dev, "Error, ATAPI not supported\n");
		BUG();

	शेष:
		वापस ata_sff_qc_issue(qc);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ata_port_operations octeon_cf_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.check_atapi_dma	= octeon_cf_check_atapi_dma,
	.qc_prep		= ata_noop_qc_prep,
	.qc_issue		= octeon_cf_qc_issue,
	.sff_dev_select		= octeon_cf_dev_select,
	.sff_irq_on		= octeon_cf_ata_port_noaction,
	.sff_irq_clear		= octeon_cf_ata_port_noaction,
	.cable_detect		= ata_cable_40wire,
	.set_piomode		= octeon_cf_set_piomode,
	.set_dmamode		= octeon_cf_set_dmamode,
	.dev_config		= octeon_cf_dev_config,
पूर्ण;

अटल पूर्णांक octeon_cf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_cs0, *res_cs1;

	bool is_16bit;
	स्थिर __be32 *cs_num;
	काष्ठा property *reg_prop;
	पूर्णांक n_addr, n_size, reg_len;
	काष्ठा device_node *node;
	व्योम __iomem *cs0;
	व्योम __iomem *cs1 = शून्य;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	पूर्णांक irq = 0;
	irq_handler_t irq_handler = शून्य;
	व्योम __iomem *base;
	काष्ठा octeon_cf_port *cf_port;
	पूर्णांक rv = -ENOMEM;
	u32 bus_width;

	node = pdev->dev.of_node;
	अगर (node == शून्य)
		वापस -EINVAL;

	cf_port = devm_kzalloc(&pdev->dev, माप(*cf_port), GFP_KERNEL);
	अगर (!cf_port)
		वापस -ENOMEM;

	cf_port->is_true_ide = of_property_पढ़ो_bool(node, "cavium,true-ide");

	अगर (of_property_पढ़ो_u32(node, "cavium,bus-width", &bus_width) == 0)
		is_16bit = (bus_width == 16);
	अन्यथा
		is_16bit = false;

	n_addr = of_n_addr_cells(node);
	n_size = of_n_size_cells(node);

	reg_prop = of_find_property(node, "reg", &reg_len);
	अगर (!reg_prop || reg_len < माप(__be32))
		वापस -EINVAL;

	cs_num = reg_prop->value;
	cf_port->cs0 = be32_to_cpup(cs_num);

	अगर (cf_port->is_true_ide) अणु
		काष्ठा device_node *dma_node;
		dma_node = of_parse_phandle(node,
					    "cavium,dma-engine-handle", 0);
		अगर (dma_node) अणु
			काष्ठा platक्रमm_device *dma_dev;
			dma_dev = of_find_device_by_node(dma_node);
			अगर (dma_dev) अणु
				काष्ठा resource *res_dma;
				पूर्णांक i;
				res_dma = platक्रमm_get_resource(dma_dev, IORESOURCE_MEM, 0);
				अगर (!res_dma) अणु
					of_node_put(dma_node);
					वापस -EINVAL;
				पूर्ण
				cf_port->dma_base = (u64)devm_ioremap(&pdev->dev, res_dma->start,
									 resource_size(res_dma));
				अगर (!cf_port->dma_base) अणु
					of_node_put(dma_node);
					वापस -EINVAL;
				पूर्ण

				irq_handler = octeon_cf_पूर्णांकerrupt;
				i = platक्रमm_get_irq(dma_dev, 0);
				अगर (i > 0)
					irq = i;
			पूर्ण
			of_node_put(dma_node);
		पूर्ण
		res_cs1 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (!res_cs1)
			वापस -EINVAL;

		cs1 = devm_ioremap(&pdev->dev, res_cs1->start,
					   resource_size(res_cs1));
		अगर (!cs1)
			वापस rv;

		अगर (reg_len < (n_addr + n_size + 1) * माप(__be32))
			वापस -EINVAL;

		cs_num += n_addr + n_size;
		cf_port->cs1 = be32_to_cpup(cs_num);
	पूर्ण

	res_cs0 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_cs0)
		वापस -EINVAL;

	cs0 = devm_ioremap(&pdev->dev, res_cs0->start,
				   resource_size(res_cs0));
	अगर (!cs0)
		वापस rv;

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस rv;

	ap = host->ports[0];
	ap->निजी_data = cf_port;
	pdev->dev.platक्रमm_data = cf_port;
	cf_port->ap = ap;
	ap->ops = &octeon_cf_ops;
	ap->pio_mask = ATA_PIO6;
	ap->flags |= ATA_FLAG_NO_ATAPI | ATA_FLAG_PIO_POLLING;

	अगर (!is_16bit) अणु
		base = cs0 + 0x800;
		ap->ioaddr.cmd_addr	= base;
		ata_sff_std_ports(&ap->ioaddr);

		ap->ioaddr.altstatus_addr = base + 0xe;
		ap->ioaddr.ctl_addr	= base + 0xe;
		octeon_cf_ops.sff_data_xfer = octeon_cf_data_xfer8;
	पूर्ण अन्यथा अगर (cf_port->is_true_ide) अणु
		base = cs0;
		ap->ioaddr.cmd_addr	= base + (ATA_REG_CMD << 1) + 1;
		ap->ioaddr.data_addr	= base + (ATA_REG_DATA << 1);
		ap->ioaddr.error_addr	= base + (ATA_REG_ERR << 1) + 1;
		ap->ioaddr.feature_addr	= base + (ATA_REG_FEATURE << 1) + 1;
		ap->ioaddr.nsect_addr	= base + (ATA_REG_NSECT << 1) + 1;
		ap->ioaddr.lbal_addr	= base + (ATA_REG_LBAL << 1) + 1;
		ap->ioaddr.lbam_addr	= base + (ATA_REG_LBAM << 1) + 1;
		ap->ioaddr.lbah_addr	= base + (ATA_REG_LBAH << 1) + 1;
		ap->ioaddr.device_addr	= base + (ATA_REG_DEVICE << 1) + 1;
		ap->ioaddr.status_addr	= base + (ATA_REG_STATUS << 1) + 1;
		ap->ioaddr.command_addr	= base + (ATA_REG_CMD << 1) + 1;
		ap->ioaddr.altstatus_addr = cs1 + (6 << 1) + 1;
		ap->ioaddr.ctl_addr	= cs1 + (6 << 1) + 1;
		octeon_cf_ops.sff_data_xfer = octeon_cf_data_xfer16;

		ap->mwdma_mask	= enable_dma ? ATA_MWDMA4 : 0;

		/* True IDE mode needs a समयr to poll क्रम not-busy.  */
		hrसमयr_init(&cf_port->delayed_finish, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		cf_port->delayed_finish.function = octeon_cf_delayed_finish;
	पूर्ण अन्यथा अणु
		/* 16 bit but not True IDE */
		base = cs0 + 0x800;
		octeon_cf_ops.sff_data_xfer	= octeon_cf_data_xfer16;
		octeon_cf_ops.softreset		= octeon_cf_softreset16;
		octeon_cf_ops.sff_check_status	= octeon_cf_check_status16;
		octeon_cf_ops.sff_tf_पढ़ो	= octeon_cf_tf_पढ़ो16;
		octeon_cf_ops.sff_tf_load	= octeon_cf_tf_load16;
		octeon_cf_ops.sff_exec_command	= octeon_cf_exec_command16;

		ap->ioaddr.data_addr	= base + ATA_REG_DATA;
		ap->ioaddr.nsect_addr	= base + ATA_REG_NSECT;
		ap->ioaddr.lbal_addr	= base + ATA_REG_LBAL;
		ap->ioaddr.ctl_addr	= base + 0xe;
		ap->ioaddr.altstatus_addr = base + 0xe;
	पूर्ण
	cf_port->c0 = ap->ioaddr.ctl_addr;

	rv = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rv)
		वापस rv;

	ata_port_desc(ap, "cmd %p ctl %p", base, ap->ioaddr.ctl_addr);

	dev_info(&pdev->dev, "version " DRV_VERSION" %d bit%s.\n",
		 is_16bit ? 16 : 8,
		 cf_port->is_true_ide ? ", True IDE" : "");

	वापस ata_host_activate(host, irq, irq_handler,
				 IRQF_SHARED, &octeon_cf_sht);
पूर्ण

अटल व्योम octeon_cf_shutकरोwn(काष्ठा device *dev)
अणु
	जोड़ cvmx_mio_boot_dma_cfgx dma_cfg;
	जोड़ cvmx_mio_boot_dma_पूर्णांकx dma_पूर्णांक;

	काष्ठा octeon_cf_port *cf_port = dev_get_platdata(dev);

	अगर (cf_port->dma_base) अणु
		/* Stop and clear the dma engine.  */
		dma_cfg.u64 = 0;
		dma_cfg.s.size = -1;
		cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_CFG, dma_cfg.u64);

		/* Disable the पूर्णांकerrupt.  */
		dma_पूर्णांक.u64 = 0;
		cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT_EN, dma_पूर्णांक.u64);

		/* Clear the DMA complete status */
		dma_पूर्णांक.s.करोne = 1;
		cvmx_ग_लिखो_csr(cf_port->dma_base + DMA_INT, dma_पूर्णांक.u64);

		__raw_ग_लिखोb(0, cf_port->c0);
		udelay(20);
		__raw_ग_लिखोb(ATA_SRST, cf_port->c0);
		udelay(20);
		__raw_ग_लिखोb(0, cf_port->c0);
		mdelay(100);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_cf_match[] = अणु
	अणु
		.compatible = "cavium,ebt3000-compact-flash",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_cf_match);

अटल काष्ठा platक्रमm_driver octeon_cf_driver = अणु
	.probe		= octeon_cf_probe,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = octeon_cf_match,
		.shutकरोwn = octeon_cf_shutकरोwn
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init octeon_cf_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&octeon_cf_driver);
पूर्ण


MODULE_AUTHOR("David Daney <ddaney@caviumnetworks.com>");
MODULE_DESCRIPTION("low-level driver for Cavium OCTEON Compact Flash PATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_NAME);

module_init(octeon_cf_init);
