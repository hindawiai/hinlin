<शैली गुरु>
/*
 * drivers/ata/pata_mpc52xx.c
 *
 * libata driver क्रम the Freescale MPC52xx on-chip IDE पूर्णांकerface
 *
 * Copyright (C) 2006 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003 Mipsys - Benjamin Herrenschmidt
 *
 * UDMA support based on patches by Freescale (Bernard Kuhn, John Rigby),
 * Domen Puncer and Tim Yamin.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/libata.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc52xx.h>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/bestcomm_priv.h>
#समावेश <linux/fsl/bestcomm/ata.h>

#घोषणा DRV_NAME	"mpc52xx_ata"

/* Private काष्ठाures used by the driver */
काष्ठा mpc52xx_ata_timings अणु
	u32	pio1;
	u32	pio2;
	u32	mdma1;
	u32	mdma2;
	u32	udma1;
	u32	udma2;
	u32	udma3;
	u32	udma4;
	u32	udma5;
	पूर्णांक	using_udma;
पूर्ण;

काष्ठा mpc52xx_ata_priv अणु
	अचिन्हित पूर्णांक			ipb_period;
	काष्ठा mpc52xx_ata __iomem	*ata_regs;
	phys_addr_t			ata_regs_pa;
	पूर्णांक				ata_irq;
	काष्ठा mpc52xx_ata_timings	timings[2];
	पूर्णांक				csel;

	/* DMA */
	काष्ठा bcom_task		*dmatsk;
	स्थिर काष्ठा udmaspec		*udmaspec;
	स्थिर काष्ठा mdmaspec		*mdmaspec;
	पूर्णांक 				mpc52xx_ata_dma_last_ग_लिखो;
	पूर्णांक				रुकोing_क्रम_dma;
पूर्ण;


/* ATAPI-4 PIO specs (in ns) */
अटल स्थिर u16 ataspec_t0[5]		= अणु600, 383, 240, 180, 120पूर्ण;
अटल स्थिर u16 ataspec_t1[5]		= अणु 70,  50,  30,  30,  25पूर्ण;
अटल स्थिर u16 ataspec_t2_8[5]	= अणु290, 290, 290,  80,  70पूर्ण;
अटल स्थिर u16 ataspec_t2_16[5]	= अणु165, 125, 100,  80,  70पूर्ण;
अटल स्थिर u16 ataspec_t2i[5]		= अणु  0,   0,   0,  70,  25पूर्ण;
अटल स्थिर u16 ataspec_t4[5]		= अणु 30,  20,  15,  10,  10पूर्ण;
अटल स्थिर u16 ataspec_ta[5]		= अणु 35,  35,  35,  35,  35पूर्ण;

#घोषणा CALC_CLKCYC(c,v) ((((v)+(c)-1)/(c)))

/* ======================================================================== */

/* ATAPI-4 MDMA specs (in घड़ीs) */
काष्ठा mdmaspec अणु
	u8 t0M;
	u8 td;
	u8 th;
	u8 tj;
	u8 tkw;
	u8 पंचांग;
	u8 tn;
पूर्ण;

अटल स्थिर काष्ठा mdmaspec mdmaspec66[3] = अणु
	अणु .t0M = 32, .td = 15, .th = 2, .tj = 2, .tkw = 15, .पंचांग = 4, .tn = 1 पूर्ण,
	अणु .t0M = 10, .td = 6,  .th = 1, .tj = 1, .tkw = 4,  .पंचांग = 2, .tn = 1 पूर्ण,
	अणु .t0M = 8,  .td = 5,  .th = 1, .tj = 1, .tkw = 2,  .पंचांग = 2, .tn = 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mdmaspec mdmaspec132[3] = अणु
	अणु .t0M = 64, .td = 29, .th = 3, .tj = 3, .tkw = 29, .पंचांग = 7, .tn = 2 पूर्ण,
	अणु .t0M = 20, .td = 11, .th = 2, .tj = 1, .tkw = 7,  .पंचांग = 4, .tn = 1 पूर्ण,
	अणु .t0M = 16, .td = 10, .th = 2, .tj = 1, .tkw = 4,  .पंचांग = 4, .tn = 1 पूर्ण,
पूर्ण;

/* ATAPI-4 UDMA specs (in घड़ीs) */
काष्ठा udmaspec अणु
	u8 tcyc;
	u8 t2cyc;
	u8 tds;
	u8 tdh;
	u8 tdvs;
	u8 tdvh;
	u8 tfs;
	u8 tli;
	u8 पंचांगli;
	u8 taz;
	u8 tzah;
	u8 tenv;
	u8 tsr;
	u8 trfs;
	u8 trp;
	u8 tack;
	u8 tss;
पूर्ण;

अटल स्थिर काष्ठा udmaspec udmaspec66[6] = अणु
	अणु .tcyc = 8,  .t2cyc = 16, .tds  = 1,  .tdh  = 1, .tdvs = 5,  .tdvh = 1,
	  .tfs  = 16, .tli   = 10, .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 3,  .trfs  = 5,  .trp  = 11, .tack = 2, .tss  = 4,
	पूर्ण,
	अणु .tcyc = 5,  .t2cyc = 11, .tds  = 1,  .tdh  = 1, .tdvs = 4,  .tdvh = 1,
	  .tfs  = 14, .tli   = 10, .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 5,  .trp  = 9,  .tack = 2, .tss  = 4,
	पूर्ण,
	अणु .tcyc = 4,  .t2cyc = 8,  .tds  = 1,  .tdh  = 1, .tdvs = 3,  .tdvh = 1,
	  .tfs  = 12, .tli   = 10, .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 4,  .trp  = 7,  .tack = 2, .tss  = 4,
	पूर्ण,
	अणु .tcyc = 3,  .t2cyc = 6,  .tds  = 1,  .tdh  = 1, .tdvs = 2,  .tdvh = 1,
	  .tfs  = 9,  .tli   = 7,  .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 4,  .trp  = 7,  .tack = 2, .tss  = 4,
	पूर्ण,
	अणु .tcyc = 2,  .t2cyc = 4,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 8,  .tli   = 8,  .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 4,  .trp  = 7,  .tack = 2, .tss  = 4,
	पूर्ण,
	अणु .tcyc = 2,  .t2cyc = 2,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 6,  .tli   = 5,  .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 4,  .trp  = 6,  .tack = 2, .tss  = 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा udmaspec udmaspec132[6] = अणु
	अणु .tcyc = 15, .t2cyc = 31, .tds  = 2,  .tdh  = 1, .tdvs = 10, .tdvh = 1,
	  .tfs  = 30, .tli   = 20, .पंचांगli = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsr  = 7,  .trfs  = 10, .trp  = 22, .tack = 3, .tss  = 7,
	पूर्ण,
	अणु .tcyc = 10, .t2cyc = 21, .tds  = 2,  .tdh  = 1, .tdvs = 7,  .tdvh = 1,
	  .tfs  = 27, .tli   = 20, .पंचांगli = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsr  = 4,  .trfs  = 10, .trp  = 17, .tack = 3, .tss  = 7,
	पूर्ण,
	अणु .tcyc = 6,  .t2cyc = 12, .tds  = 1,  .tdh  = 1, .tdvs = 5,  .tdvh = 1,
	  .tfs  = 23, .tli   = 20, .पंचांगli = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsr  = 3,  .trfs  = 8,  .trp  = 14, .tack = 3, .tss  = 7,
	पूर्ण,
	अणु .tcyc = 7,  .t2cyc = 12, .tds  = 1,  .tdh  = 1, .tdvs = 3,  .tdvh = 1,
	  .tfs  = 15, .tli   = 13, .पंचांगli = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsr  = 3,  .trfs  = 8,  .trp  = 14, .tack = 3, .tss  = 7,
	पूर्ण,
	अणु .tcyc = 2,  .t2cyc = 5,  .tds  = 0,  .tdh  = 0, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 16, .tli   = 14, .पंचांगli = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsr  = 2,  .trfs  = 7,  .trp  = 13, .tack = 2, .tss  = 6,
	पूर्ण,
	अणु .tcyc = 3,  .t2cyc = 6,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 12, .tli   = 10, .पंचांगli = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsr  = 3,  .trfs  = 7,  .trp  = 12, .tack = 3, .tss  = 7,
	पूर्ण,
पूर्ण;

/* ======================================================================== */

/* Bit definitions inside the रेजिस्टरs */
#घोषणा MPC52xx_ATA_HOSTCONF_SMR	0x80000000UL /* State machine reset */
#घोषणा MPC52xx_ATA_HOSTCONF_FR		0x40000000UL /* FIFO Reset */
#घोषणा MPC52xx_ATA_HOSTCONF_IE		0x02000000UL /* Enable पूर्णांकerrupt in PIO */
#घोषणा MPC52xx_ATA_HOSTCONF_IORDY	0x01000000UL /* Drive supports IORDY protocol */

#घोषणा MPC52xx_ATA_HOSTSTAT_TIP	0x80000000UL /* Transaction in progress */
#घोषणा MPC52xx_ATA_HOSTSTAT_UREP	0x40000000UL /* UDMA Read Extended Pause */
#घोषणा MPC52xx_ATA_HOSTSTAT_RERR	0x02000000UL /* Read Error */
#घोषणा MPC52xx_ATA_HOSTSTAT_WERR	0x01000000UL /* Write Error */

#घोषणा MPC52xx_ATA_FIFOSTAT_EMPTY	0x01 /* FIFO Empty */
#घोषणा MPC52xx_ATA_FIFOSTAT_ERROR	0x40 /* FIFO Error */

#घोषणा MPC52xx_ATA_DMAMODE_WRITE	0x01 /* Write DMA */
#घोषणा MPC52xx_ATA_DMAMODE_READ	0x02 /* Read DMA */
#घोषणा MPC52xx_ATA_DMAMODE_UDMA	0x04 /* UDMA enabled */
#घोषणा MPC52xx_ATA_DMAMODE_IE		0x08 /* Enable drive पूर्णांकerrupt to CPU in DMA mode */
#घोषणा MPC52xx_ATA_DMAMODE_FE		0x10 /* FIFO Flush enable in Rx mode */
#घोषणा MPC52xx_ATA_DMAMODE_FR		0x20 /* FIFO Reset */
#घोषणा MPC52xx_ATA_DMAMODE_HUT		0x40 /* Host UDMA burst terminate */

#घोषणा MAX_DMA_BUFFERS 128
#घोषणा MAX_DMA_BUFFER_SIZE 0x20000u

/* Structure of the hardware रेजिस्टरs */
काष्ठा mpc52xx_ata अणु

	/* Host पूर्णांकerface रेजिस्टरs */
	u32 config;		/* ATA + 0x00 Host configuration */
	u32 host_status;	/* ATA + 0x04 Host controller status */
	u32 pio1;		/* ATA + 0x08 PIO Timing 1 */
	u32 pio2;		/* ATA + 0x0c PIO Timing 2 */
	u32 mdma1;		/* ATA + 0x10 MDMA Timing 1 */
	u32 mdma2;		/* ATA + 0x14 MDMA Timing 2 */
	u32 udma1;		/* ATA + 0x18 UDMA Timing 1 */
	u32 udma2;		/* ATA + 0x1c UDMA Timing 2 */
	u32 udma3;		/* ATA + 0x20 UDMA Timing 3 */
	u32 udma4;		/* ATA + 0x24 UDMA Timing 4 */
	u32 udma5;		/* ATA + 0x28 UDMA Timing 5 */
	u32 share_cnt;		/* ATA + 0x2c ATA share counter */
	u32 reserved0[3];

	/* FIFO रेजिस्टरs */
	u32 fअगरo_data;		/* ATA + 0x3c */
	u8  fअगरo_status_frame;	/* ATA + 0x40 */
	u8  fअगरo_status;	/* ATA + 0x41 */
	u16 reserved7[1];
	u8  fअगरo_control;	/* ATA + 0x44 */
	u8  reserved8[5];
	u16 fअगरo_alarm;		/* ATA + 0x4a */
	u16 reserved9;
	u16 fअगरo_rdp;		/* ATA + 0x4e */
	u16 reserved10;
	u16 fअगरo_wrp;		/* ATA + 0x52 */
	u16 reserved11;
	u16 fअगरo_lfrdp;		/* ATA + 0x56 */
	u16 reserved12;
	u16 fअगरo_lfwrp;		/* ATA + 0x5a */

	/* Drive TaskFile रेजिस्टरs */
	u8  tf_control;		/* ATA + 0x5c TASKखाता Control/Alt Status */
	u8  reserved13[3];
	u16 tf_data;		/* ATA + 0x60 TASKखाता Data */
	u16 reserved14;
	u8  tf_features;	/* ATA + 0x64 TASKखाता Features/Error */
	u8  reserved15[3];
	u8  tf_sec_count;	/* ATA + 0x68 TASKखाता Sector Count */
	u8  reserved16[3];
	u8  tf_sec_num;		/* ATA + 0x6c TASKखाता Sector Number */
	u8  reserved17[3];
	u8  tf_cyl_low;		/* ATA + 0x70 TASKखाता Cylinder Low */
	u8  reserved18[3];
	u8  tf_cyl_high;	/* ATA + 0x74 TASKखाता Cylinder High */
	u8  reserved19[3];
	u8  tf_dev_head;	/* ATA + 0x78 TASKखाता Device/Head */
	u8  reserved20[3];
	u8  tf_command;		/* ATA + 0x7c TASKखाता Command/Status */
	u8  dma_mode;		/* ATA + 0x7d ATA Host DMA Mode configuration */
	u8  reserved21[2];
पूर्ण;


/* ======================================================================== */
/* Aux fns                                                                  */
/* ======================================================================== */


/* MPC52xx low level hw control */
अटल पूर्णांक
mpc52xx_ata_compute_pio_timings(काष्ठा mpc52xx_ata_priv *priv, पूर्णांक dev, पूर्णांक pio)
अणु
	काष्ठा mpc52xx_ata_timings *timing = &priv->timings[dev];
	अचिन्हित पूर्णांक ipb_period = priv->ipb_period;
	u32 t0, t1, t2_8, t2_16, t2i, t4, ta;

	अगर ((pio < 0) || (pio > 4))
		वापस -EINVAL;

	t0	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t0[pio]);
	t1	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t1[pio]);
	t2_8	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t2_8[pio]);
	t2_16	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t2_16[pio]);
	t2i	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t2i[pio]);
	t4	= CALC_CLKCYC(ipb_period, 1000 * ataspec_t4[pio]);
	ta	= CALC_CLKCYC(ipb_period, 1000 * ataspec_ta[pio]);

	timing->pio1 = (t0 << 24) | (t2_8 << 16) | (t2_16 << 8) | (t2i);
	timing->pio2 = (t4 << 24) | (t1 << 16) | (ta << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_ata_compute_mdma_timings(काष्ठा mpc52xx_ata_priv *priv, पूर्णांक dev,
				 पूर्णांक speed)
अणु
	काष्ठा mpc52xx_ata_timings *t = &priv->timings[dev];
	स्थिर काष्ठा mdmaspec *s = &priv->mdmaspec[speed];

	अगर (speed < 0 || speed > 2)
		वापस -EINVAL;

	t->mdma1 = ((u32)s->t0M << 24) | ((u32)s->td << 16) | ((u32)s->tkw << 8) | s->पंचांग;
	t->mdma2 = ((u32)s->th << 24) | ((u32)s->tj << 16) | ((u32)s->tn << 8);
	t->using_udma = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_ata_compute_udma_timings(काष्ठा mpc52xx_ata_priv *priv, पूर्णांक dev,
				 पूर्णांक speed)
अणु
	काष्ठा mpc52xx_ata_timings *t = &priv->timings[dev];
	स्थिर काष्ठा udmaspec *s = &priv->udmaspec[speed];

	अगर (speed < 0 || speed > 2)
		वापस -EINVAL;

	t->udma1 = ((u32)s->t2cyc << 24) | ((u32)s->tcyc << 16) | ((u32)s->tds << 8) | s->tdh;
	t->udma2 = ((u32)s->tdvs << 24) | ((u32)s->tdvh << 16) | ((u32)s->tfs << 8) | s->tli;
	t->udma3 = ((u32)s->पंचांगli << 24) | ((u32)s->taz << 16) | ((u32)s->tenv << 8) | s->tsr;
	t->udma4 = ((u32)s->tss << 24) | ((u32)s->trfs << 16) | ((u32)s->trp << 8) | s->tack;
	t->udma5 = (u32)s->tzah << 24;
	t->using_udma = 1;

	वापस 0;
पूर्ण

अटल व्योम
mpc52xx_ata_apply_timings(काष्ठा mpc52xx_ata_priv *priv, पूर्णांक device)
अणु
	काष्ठा mpc52xx_ata __iomem *regs = priv->ata_regs;
	काष्ठा mpc52xx_ata_timings *timing = &priv->timings[device];

	out_be32(&regs->pio1,  timing->pio1);
	out_be32(&regs->pio2,  timing->pio2);
	out_be32(&regs->mdma1, timing->mdma1);
	out_be32(&regs->mdma2, timing->mdma2);
	out_be32(&regs->udma1, timing->udma1);
	out_be32(&regs->udma2, timing->udma2);
	out_be32(&regs->udma3, timing->udma3);
	out_be32(&regs->udma4, timing->udma4);
	out_be32(&regs->udma5, timing->udma5);
	priv->csel = device;
पूर्ण

अटल पूर्णांक
mpc52xx_ata_hw_init(काष्ठा mpc52xx_ata_priv *priv)
अणु
	काष्ठा mpc52xx_ata __iomem *regs = priv->ata_regs;
	पूर्णांक tslot;

	/* Clear share_cnt (all sample code करो this ...) */
	out_be32(&regs->share_cnt, 0);

	/* Configure and reset host */
	out_be32(&regs->config,
			MPC52xx_ATA_HOSTCONF_IE |
			MPC52xx_ATA_HOSTCONF_IORDY |
			MPC52xx_ATA_HOSTCONF_SMR |
			MPC52xx_ATA_HOSTCONF_FR);

	udelay(10);

	out_be32(&regs->config,
			MPC52xx_ATA_HOSTCONF_IE |
			MPC52xx_ATA_HOSTCONF_IORDY);

	/* Set the समय slot to 1us */
	tslot = CALC_CLKCYC(priv->ipb_period, 1000000);
	out_be32(&regs->share_cnt, tslot << 16);

	/* Init timings to PIO0 */
	स_रखो(priv->timings, 0x00, 2*माप(काष्ठा mpc52xx_ata_timings));

	mpc52xx_ata_compute_pio_timings(priv, 0, 0);
	mpc52xx_ata_compute_pio_timings(priv, 1, 0);

	mpc52xx_ata_apply_timings(priv, 0);

	वापस 0;
पूर्ण


/* ======================================================================== */
/* libata driver                                                            */
/* ======================================================================== */

अटल व्योम
mpc52xx_ata_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;
	पूर्णांक pio, rv;

	pio = adev->pio_mode - XFER_PIO_0;

	rv = mpc52xx_ata_compute_pio_timings(priv, adev->devno, pio);

	अगर (rv) अणु
		dev_err(ap->dev, "error: invalid PIO mode: %d\n", pio);
		वापस;
	पूर्ण

	mpc52xx_ata_apply_timings(priv, adev->devno);
पूर्ण

अटल व्योम
mpc52xx_ata_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;
	पूर्णांक rv;

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		पूर्णांक dma = adev->dma_mode - XFER_UDMA_0;
		rv = mpc52xx_ata_compute_udma_timings(priv, adev->devno, dma);
	पूर्ण अन्यथा अणु
		पूर्णांक dma = adev->dma_mode - XFER_MW_DMA_0;
		rv = mpc52xx_ata_compute_mdma_timings(priv, adev->devno, dma);
	पूर्ण

	अगर (rv) अणु
		dev_alert(ap->dev,
			"Trying to select invalid DMA mode %d\n",
			adev->dma_mode);
		वापस;
	पूर्ण

	mpc52xx_ata_apply_timings(priv, adev->devno);
पूर्ण

अटल व्योम
mpc52xx_ata_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;

	अगर (device != priv->csel)
		mpc52xx_ata_apply_timings(priv, device);

	ata_sff_dev_select(ap, device);
पूर्ण

अटल पूर्णांक
mpc52xx_ata_build_dmatable(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;
	काष्ठा bcom_ata_bd *bd;
	अचिन्हित पूर्णांक पढ़ो = !(qc->tf.flags & ATA_TFLAG_WRITE), si;
	काष्ठा scatterlist *sg;
	पूर्णांक count = 0;

	अगर (पढ़ो)
		bcom_ata_rx_prepare(priv->dmatsk);
	अन्यथा
		bcom_ata_tx_prepare(priv->dmatsk);

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		dma_addr_t cur_addr = sg_dma_address(sg);
		u32 cur_len = sg_dma_len(sg);

		जबतक (cur_len) अणु
			अचिन्हित पूर्णांक tc = min(cur_len, MAX_DMA_BUFFER_SIZE);
			bd = (काष्ठा bcom_ata_bd *)
				bcom_prepare_next_buffer(priv->dmatsk);

			अगर (पढ़ो) अणु
				bd->status = tc;
				bd->src_pa = (__क्रमce u32) priv->ata_regs_pa +
					दुरत्व(काष्ठा mpc52xx_ata, fअगरo_data);
				bd->dst_pa = (__क्रमce u32) cur_addr;
			पूर्ण अन्यथा अणु
				bd->status = tc;
				bd->src_pa = (__क्रमce u32) cur_addr;
				bd->dst_pa = (__क्रमce u32) priv->ata_regs_pa +
					दुरत्व(काष्ठा mpc52xx_ata, fअगरo_data);
			पूर्ण

			bcom_submit_next_buffer(priv->dmatsk, शून्य);

			cur_addr += tc;
			cur_len -= tc;
			count++;

			अगर (count > MAX_DMA_BUFFERS) अणु
				dev_alert(ap->dev, "dma table"
					"too small\n");
				जाओ use_pio_instead;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;

 use_pio_instead:
	bcom_ata_reset_bd(priv->dmatsk);
	वापस 0;
पूर्ण

अटल व्योम
mpc52xx_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;
	काष्ठा mpc52xx_ata __iomem *regs = priv->ata_regs;

	अचिन्हित पूर्णांक पढ़ो = !(qc->tf.flags & ATA_TFLAG_WRITE);
	u8 dma_mode;

	अगर (!mpc52xx_ata_build_dmatable(qc))
		dev_alert(ap->dev, "%s: %i, return 1?\n",
			__func__, __LINE__);

	/* Check FIFO is OK... */
	अगर (in_8(&priv->ata_regs->fअगरo_status) & MPC52xx_ATA_FIFOSTAT_ERROR)
		dev_alert(ap->dev, "%s: FIFO error detected: 0x%02x!\n",
			__func__, in_8(&priv->ata_regs->fअगरo_status));

	अगर (पढ़ो) अणु
		dma_mode = MPC52xx_ATA_DMAMODE_IE | MPC52xx_ATA_DMAMODE_READ |
				MPC52xx_ATA_DMAMODE_FE;

		/* Setup FIFO अगर direction changed */
		अगर (priv->mpc52xx_ata_dma_last_ग_लिखो != 0) अणु
			priv->mpc52xx_ata_dma_last_ग_लिखो = 0;

			/* Configure FIFO with granularity to 7 */
			out_8(&regs->fअगरo_control, 7);
			out_be16(&regs->fअगरo_alarm, 128);

			/* Set FIFO Reset bit (FR) */
			out_8(&regs->dma_mode, MPC52xx_ATA_DMAMODE_FR);
		पूर्ण
	पूर्ण अन्यथा अणु
		dma_mode = MPC52xx_ATA_DMAMODE_IE | MPC52xx_ATA_DMAMODE_WRITE;

		/* Setup FIFO अगर direction changed */
		अगर (priv->mpc52xx_ata_dma_last_ग_लिखो != 1) अणु
			priv->mpc52xx_ata_dma_last_ग_लिखो = 1;

			/* Configure FIFO with granularity to 4 */
			out_8(&regs->fअगरo_control, 4);
			out_be16(&regs->fअगरo_alarm, 128);
		पूर्ण
	पूर्ण

	अगर (priv->timings[qc->dev->devno].using_udma)
		dma_mode |= MPC52xx_ATA_DMAMODE_UDMA;

	out_8(&regs->dma_mode, dma_mode);
	priv->रुकोing_क्रम_dma = ATA_DMA_ACTIVE;

	ata_रुको_idle(ap);
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

अटल व्योम
mpc52xx_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;

	bcom_set_task_स्वतः_start(priv->dmatsk->tasknum, priv->dmatsk->tasknum);
	bcom_enable(priv->dmatsk);
पूर्ण

अटल व्योम
mpc52xx_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;

	bcom_disable(priv->dmatsk);
	bcom_ata_reset_bd(priv->dmatsk);
	priv->रुकोing_क्रम_dma = 0;

	/* Check FIFO is OK... */
	अगर (in_8(&priv->ata_regs->fअगरo_status) & MPC52xx_ATA_FIFOSTAT_ERROR)
		dev_alert(ap->dev, "%s: FIFO error detected: 0x%02x!\n",
			__func__, in_8(&priv->ata_regs->fअगरo_status));
पूर्ण

अटल u8
mpc52xx_bmdma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा mpc52xx_ata_priv *priv = ap->host->निजी_data;

	/* Check FIFO is OK... */
	अगर (in_8(&priv->ata_regs->fअगरo_status) & MPC52xx_ATA_FIFOSTAT_ERROR) अणु
		dev_alert(ap->dev, "%s: FIFO error detected: 0x%02x!\n",
			__func__, in_8(&priv->ata_regs->fअगरo_status));
		वापस priv->रुकोing_क्रम_dma | ATA_DMA_ERR;
	पूर्ण

	वापस priv->रुकोing_क्रम_dma;
पूर्ण

अटल irqवापस_t
mpc52xx_ata_task_irq(पूर्णांक irq, व्योम *vpriv)
अणु
	काष्ठा mpc52xx_ata_priv *priv = vpriv;
	जबतक (bcom_buffer_करोne(priv->dmatsk))
		bcom_retrieve_buffer(priv->dmatsk, शून्य, शून्य);

	priv->रुकोing_क्रम_dma |= ATA_DMA_INTR;

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mpc52xx_ata_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations mpc52xx_ata_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.sff_dev_select		= mpc52xx_ata_dev_select,
	.set_piomode		= mpc52xx_ata_set_piomode,
	.set_dmamode		= mpc52xx_ata_set_dmamode,
	.bmdma_setup		= mpc52xx_bmdma_setup,
	.bmdma_start		= mpc52xx_bmdma_start,
	.bmdma_stop		= mpc52xx_bmdma_stop,
	.bmdma_status		= mpc52xx_bmdma_status,
	.qc_prep		= ata_noop_qc_prep,
पूर्ण;

अटल पूर्णांक mpc52xx_ata_init_one(काष्ठा device *dev,
				काष्ठा mpc52xx_ata_priv *priv,
				अचिन्हित दीर्घ raw_ata_regs,
				पूर्णांक mwdma_mask, पूर्णांक udma_mask)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	काष्ठा ata_ioports *aio;

	host = ata_host_alloc(dev, 1);
	अगर (!host)
		वापस -ENOMEM;

	ap = host->ports[0];
	ap->flags		|= ATA_FLAG_SLAVE_POSS;
	ap->pio_mask		= ATA_PIO4;
	ap->mwdma_mask		= mwdma_mask;
	ap->udma_mask		= udma_mask;
	ap->ops			= &mpc52xx_ata_port_ops;
	host->निजी_data	= priv;

	aio = &ap->ioaddr;
	aio->cmd_addr		= शून्य;	/* Don't have a classic reg block */
	aio->altstatus_addr	= &priv->ata_regs->tf_control;
	aio->ctl_addr		= &priv->ata_regs->tf_control;
	aio->data_addr		= &priv->ata_regs->tf_data;
	aio->error_addr		= &priv->ata_regs->tf_features;
	aio->feature_addr	= &priv->ata_regs->tf_features;
	aio->nsect_addr		= &priv->ata_regs->tf_sec_count;
	aio->lbal_addr		= &priv->ata_regs->tf_sec_num;
	aio->lbam_addr		= &priv->ata_regs->tf_cyl_low;
	aio->lbah_addr		= &priv->ata_regs->tf_cyl_high;
	aio->device_addr	= &priv->ata_regs->tf_dev_head;
	aio->status_addr	= &priv->ata_regs->tf_command;
	aio->command_addr	= &priv->ata_regs->tf_command;

	ata_port_desc(ap, "ata_regs 0x%lx", raw_ata_regs);

	/* activate host */
	वापस ata_host_activate(host, priv->ata_irq, ata_bmdma_पूर्णांकerrupt, 0,
				 &mpc52xx_ata_sht);
पूर्ण

/* ======================================================================== */
/* OF Platक्रमm driver                                                       */
/* ======================================================================== */

अटल पूर्णांक mpc52xx_ata_probe(काष्ठा platक्रमm_device *op)
अणु
	अचिन्हित पूर्णांक ipb_freq;
	काष्ठा resource res_mem;
	पूर्णांक ata_irq = 0;
	काष्ठा mpc52xx_ata __iomem *ata_regs;
	काष्ठा mpc52xx_ata_priv *priv = शून्य;
	पूर्णांक rv, task_irq;
	पूर्णांक mwdma_mask = 0, udma_mask = 0;
	स्थिर __be32 *prop;
	पूर्णांक proplen;
	काष्ठा bcom_task *dmatsk;

	/* Get ipb frequency */
	ipb_freq = mpc5xxx_get_bus_frequency(op->dev.of_node);
	अगर (!ipb_freq) अणु
		dev_err(&op->dev, "could not determine IPB bus frequency\n");
		वापस -ENODEV;
	पूर्ण

	/* Get device base address from device tree, request the region
	 * and ioremap it. */
	rv = of_address_to_resource(op->dev.of_node, 0, &res_mem);
	अगर (rv) अणु
		dev_err(&op->dev, "could not determine device base address\n");
		वापस rv;
	पूर्ण

	अगर (!devm_request_mem_region(&op->dev, res_mem.start,
				     माप(*ata_regs), DRV_NAME)) अणु
		dev_err(&op->dev, "error requesting register region\n");
		वापस -EBUSY;
	पूर्ण

	ata_regs = devm_ioremap(&op->dev, res_mem.start, माप(*ata_regs));
	अगर (!ata_regs) अणु
		dev_err(&op->dev, "error mapping device registers\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * By शेष, all DMA modes are disabled क्रम the MPC5200.  Some
	 * boards करोn't have the required संकेतs routed to make DMA work.
	 * Also, the MPC5200B has a silicon bug that causes data corruption
	 * with UDMA अगर it is used at the same समय as the LocalPlus bus.
	 *
	 * Instead of trying to guess what modes are usable, check the
	 * ATA device tree node to find out what DMA modes work on the board.
	 * UDMA/MWDMA modes can also be क्रमced by adding "libata.force=<mode>"
	 * to the kernel boot parameters.
	 *
	 * The MPC5200 ATA controller supports MWDMA modes 0, 1 and 2 and
	 * UDMA modes 0, 1 and 2.
	 */
	prop = of_get_property(op->dev.of_node, "mwdma-mode", &proplen);
	अगर ((prop) && (proplen >= 4))
		mwdma_mask = ATA_MWDMA2 & ((1 << (*prop + 1)) - 1);
	prop = of_get_property(op->dev.of_node, "udma-mode", &proplen);
	अगर ((prop) && (proplen >= 4))
		udma_mask = ATA_UDMA2 & ((1 << (*prop + 1)) - 1);

	ata_irq = irq_of_parse_and_map(op->dev.of_node, 0);
	अगर (ata_irq == NO_IRQ) अणु
		dev_err(&op->dev, "error mapping irq\n");
		वापस -EINVAL;
	पूर्ण

	/* Prepare our निजी काष्ठाure */
	priv = devm_kzalloc(&op->dev, माप(*priv), GFP_ATOMIC);
	अगर (!priv) अणु
		rv = -ENOMEM;
		जाओ err1;
	पूर्ण

	priv->ipb_period = 1000000000 / (ipb_freq / 1000);
	priv->ata_regs = ata_regs;
	priv->ata_regs_pa = res_mem.start;
	priv->ata_irq = ata_irq;
	priv->csel = -1;
	priv->mpc52xx_ata_dma_last_ग_लिखो = -1;

	अगर (ipb_freq/1000000 == 66) अणु
		priv->mdmaspec = mdmaspec66;
		priv->udmaspec = udmaspec66;
	पूर्ण अन्यथा अणु
		priv->mdmaspec = mdmaspec132;
		priv->udmaspec = udmaspec132;
	पूर्ण

	/* Allocate a BestComm task क्रम DMA */
	dmatsk = bcom_ata_init(MAX_DMA_BUFFERS, MAX_DMA_BUFFER_SIZE);
	अगर (!dmatsk) अणु
		dev_err(&op->dev, "bestcomm initialization failed\n");
		rv = -ENOMEM;
		जाओ err1;
	पूर्ण

	task_irq = bcom_get_task_irq(dmatsk);
	rv = devm_request_irq(&op->dev, task_irq, &mpc52xx_ata_task_irq, 0,
				"ATA task", priv);
	अगर (rv) अणु
		dev_err(&op->dev, "error requesting DMA IRQ\n");
		जाओ err2;
	पूर्ण
	priv->dmatsk = dmatsk;

	/* Init the hw */
	rv = mpc52xx_ata_hw_init(priv);
	अगर (rv) अणु
		dev_err(&op->dev, "error initializing hardware\n");
		जाओ err2;
	पूर्ण

	/* Register ourselves to libata */
	rv = mpc52xx_ata_init_one(&op->dev, priv, res_mem.start,
				  mwdma_mask, udma_mask);
	अगर (rv) अणु
		dev_err(&op->dev, "error registering with ATA layer\n");
		जाओ err2;
	पूर्ण

	वापस 0;

 err2:
	irq_dispose_mapping(task_irq);
	bcom_ata_release(dmatsk);
 err1:
	irq_dispose_mapping(ata_irq);
	वापस rv;
पूर्ण

अटल पूर्णांक
mpc52xx_ata_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(op);
	काष्ठा mpc52xx_ata_priv *priv = host->निजी_data;
	पूर्णांक task_irq;

	/* Deरेजिस्टर the ATA पूर्णांकerface */
	ata_platक्रमm_हटाओ_one(op);

	/* Clean up DMA */
	task_irq = bcom_get_task_irq(priv->dmatsk);
	irq_dispose_mapping(task_irq);
	bcom_ata_release(priv->dmatsk);
	irq_dispose_mapping(priv->ata_irq);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक
mpc52xx_ata_suspend(काष्ठा platक्रमm_device *op, pm_message_t state)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(op);

	वापस ata_host_suspend(host, state);
पूर्ण

अटल पूर्णांक
mpc52xx_ata_resume(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(op);
	काष्ठा mpc52xx_ata_priv *priv = host->निजी_data;
	पूर्णांक rv;

	rv = mpc52xx_ata_hw_init(priv);
	अगर (rv) अणु
		dev_err(host->dev, "error initializing hardware\n");
		वापस rv;
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id mpc52xx_ata_of_match[] = अणु
	अणु .compatible = "fsl,mpc5200-ata", पूर्ण,
	अणु .compatible = "mpc5200-ata", पूर्ण,
	अणुपूर्ण,
पूर्ण;


अटल काष्ठा platक्रमm_driver mpc52xx_ata_of_platक्रमm_driver = अणु
	.probe		= mpc52xx_ata_probe,
	.हटाओ		= mpc52xx_ata_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= mpc52xx_ata_suspend,
	.resume		= mpc52xx_ata_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = mpc52xx_ata_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mpc52xx_ata_of_platक्रमm_driver);

MODULE_AUTHOR("Sylvain Munaut <tnt@246tNt.com>");
MODULE_DESCRIPTION("Freescale MPC52xx IDE/ATA libata driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, mpc52xx_ata_of_match);

