<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Renesas R-Car SATA driver
 *
 * Author: Vladimir Barinov <source@cogentembedded.com>
 * Copyright (C) 2013-2015 Cogent Embedded, Inc.
 * Copyright (C) 2013-2015 Renesas Solutions Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>

#घोषणा DRV_NAME "sata_rcar"

/* SH-Navi2G/ATAPI-ATA compatible task रेजिस्टरs */
#घोषणा DATA_REG			0x100
#घोषणा SDEVCON_REG			0x138

/* SH-Navi2G/ATAPI module compatible control रेजिस्टरs */
#घोषणा ATAPI_CONTROL1_REG		0x180
#घोषणा ATAPI_STATUS_REG		0x184
#घोषणा ATAPI_INT_ENABLE_REG		0x188
#घोषणा ATAPI_DTB_ADR_REG		0x198
#घोषणा ATAPI_DMA_START_ADR_REG		0x19C
#घोषणा ATAPI_DMA_TRANS_CNT_REG		0x1A0
#घोषणा ATAPI_CONTROL2_REG		0x1A4
#घोषणा ATAPI_SIG_ST_REG		0x1B0
#घोषणा ATAPI_BYTE_SWAP_REG		0x1BC

/* ATAPI control 1 रेजिस्टर (ATAPI_CONTROL1) bits */
#घोषणा ATAPI_CONTROL1_ISM		BIT(16)
#घोषणा ATAPI_CONTROL1_DTA32M		BIT(11)
#घोषणा ATAPI_CONTROL1_RESET		BIT(7)
#घोषणा ATAPI_CONTROL1_DESE		BIT(3)
#घोषणा ATAPI_CONTROL1_RW		BIT(2)
#घोषणा ATAPI_CONTROL1_STOP		BIT(1)
#घोषणा ATAPI_CONTROL1_START		BIT(0)

/* ATAPI status रेजिस्टर (ATAPI_STATUS) bits */
#घोषणा ATAPI_STATUS_SATAINT		BIT(11)
#घोषणा ATAPI_STATUS_DNEND		BIT(6)
#घोषणा ATAPI_STATUS_DEVTRM		BIT(5)
#घोषणा ATAPI_STATUS_DEVINT		BIT(4)
#घोषणा ATAPI_STATUS_ERR		BIT(2)
#घोषणा ATAPI_STATUS_NEND		BIT(1)
#घोषणा ATAPI_STATUS_ACT		BIT(0)

/* Interrupt enable रेजिस्टर (ATAPI_INT_ENABLE) bits */
#घोषणा ATAPI_INT_ENABLE_SATAINT	BIT(11)
#घोषणा ATAPI_INT_ENABLE_DNEND		BIT(6)
#घोषणा ATAPI_INT_ENABLE_DEVTRM		BIT(5)
#घोषणा ATAPI_INT_ENABLE_DEVINT		BIT(4)
#घोषणा ATAPI_INT_ENABLE_ERR		BIT(2)
#घोषणा ATAPI_INT_ENABLE_NEND		BIT(1)
#घोषणा ATAPI_INT_ENABLE_ACT		BIT(0)

/* Access control रेजिस्टरs क्रम physical layer control रेजिस्टर */
#घोषणा SATAPHYADDR_REG			0x200
#घोषणा SATAPHYWDATA_REG		0x204
#घोषणा SATAPHYACCEN_REG		0x208
#घोषणा SATAPHYRESET_REG		0x20C
#घोषणा SATAPHYRDATA_REG		0x210
#घोषणा SATAPHYACK_REG			0x214

/* Physical layer control address command रेजिस्टर (SATAPHYADDR) bits */
#घोषणा SATAPHYADDR_PHYRATEMODE		BIT(10)
#घोषणा SATAPHYADDR_PHYCMD_READ		BIT(9)
#घोषणा SATAPHYADDR_PHYCMD_WRITE	BIT(8)

/* Physical layer control enable रेजिस्टर (SATAPHYACCEN) bits */
#घोषणा SATAPHYACCEN_PHYLANE		BIT(0)

/* Physical layer control reset रेजिस्टर (SATAPHYRESET) bits */
#घोषणा SATAPHYRESET_PHYRST		BIT(1)
#घोषणा SATAPHYRESET_PHYSRES		BIT(0)

/* Physical layer control acknowledge रेजिस्टर (SATAPHYACK) bits */
#घोषणा SATAPHYACK_PHYACK		BIT(0)

/* Serial-ATA HOST control रेजिस्टरs */
#घोषणा BISTCONF_REG			0x102C
#घोषणा SDATA_REG			0x1100
#घोषणा SSDEVCON_REG			0x1204

#घोषणा SCRSSTS_REG			0x1400
#घोषणा SCRSERR_REG			0x1404
#घोषणा SCRSCON_REG			0x1408
#घोषणा SCRSACT_REG			0x140C

#घोषणा SATAINTSTAT_REG			0x1508
#घोषणा SATAINTMASK_REG			0x150C

/* SATA INT status रेजिस्टर (SATAINTSTAT) bits */
#घोषणा SATAINTSTAT_SERR		BIT(3)
#घोषणा SATAINTSTAT_ATA			BIT(0)

/* SATA INT mask रेजिस्टर (SATAINTSTAT) bits */
#घोषणा SATAINTMASK_SERRMSK		BIT(3)
#घोषणा SATAINTMASK_ERRMSK		BIT(2)
#घोषणा SATAINTMASK_ERRCRTMSK		BIT(1)
#घोषणा SATAINTMASK_ATAMSK		BIT(0)
#घोषणा SATAINTMASK_ALL_GEN1		0x7ff
#घोषणा SATAINTMASK_ALL_GEN2		0xfff

#घोषणा SATA_RCAR_INT_MASK		(SATAINTMASK_SERRMSK | \
					 SATAINTMASK_ATAMSK)

/* Physical Layer Control Registers */
#घोषणा SATAPCTLR1_REG			0x43
#घोषणा SATAPCTLR2_REG			0x52
#घोषणा SATAPCTLR3_REG			0x5A
#घोषणा SATAPCTLR4_REG			0x60

/* Descriptor table word 0 bit (when DTA32M = 1) */
#घोषणा SATA_RCAR_DTEND			BIT(0)

#घोषणा SATA_RCAR_DMA_BOUNDARY		0x1FFFFFFFUL

/* Gen2 Physical Layer Control Registers */
#घोषणा RCAR_GEN2_PHY_CTL1_REG		0x1704
#घोषणा RCAR_GEN2_PHY_CTL1		0x34180002
#घोषणा RCAR_GEN2_PHY_CTL1_SS		0xC180	/* Spपढ़ो Spectrum */

#घोषणा RCAR_GEN2_PHY_CTL2_REG		0x170C
#घोषणा RCAR_GEN2_PHY_CTL2		0x00002303

#घोषणा RCAR_GEN2_PHY_CTL3_REG		0x171C
#घोषणा RCAR_GEN2_PHY_CTL3		0x000B0194

#घोषणा RCAR_GEN2_PHY_CTL4_REG		0x1724
#घोषणा RCAR_GEN2_PHY_CTL4		0x00030994

#घोषणा RCAR_GEN2_PHY_CTL5_REG		0x1740
#घोषणा RCAR_GEN2_PHY_CTL5		0x03004001
#घोषणा RCAR_GEN2_PHY_CTL5_DC		BIT(1)	/* DC connection */
#घोषणा RCAR_GEN2_PHY_CTL5_TR		BIT(2)	/* Termination Resistor */

क्रमागत sata_rcar_type अणु
	RCAR_GEN1_SATA,
	RCAR_GEN2_SATA,
	RCAR_GEN3_SATA,
	RCAR_R8A7790_ES1_SATA,
पूर्ण;

काष्ठा sata_rcar_priv अणु
	व्योम __iomem *base;
	u32 sataपूर्णांक_mask;
	क्रमागत sata_rcar_type type;
पूर्ण;

अटल व्योम sata_rcar_gen1_phy_preinit(काष्ठा sata_rcar_priv *priv)
अणु
	व्योम __iomem *base = priv->base;

	/* idle state */
	ioग_लिखो32(0, base + SATAPHYADDR_REG);
	/* reset */
	ioग_लिखो32(SATAPHYRESET_PHYRST, base + SATAPHYRESET_REG);
	udelay(10);
	/* deनिश्चित reset */
	ioग_लिखो32(0, base + SATAPHYRESET_REG);
पूर्ण

अटल व्योम sata_rcar_gen1_phy_ग_लिखो(काष्ठा sata_rcar_priv *priv, u16 reg,
				     u32 val, पूर्णांक group)
अणु
	व्योम __iomem *base = priv->base;
	पूर्णांक समयout;

	/* deनिश्चित reset */
	ioग_लिखो32(0, base + SATAPHYRESET_REG);
	/* lane 1 */
	ioग_लिखो32(SATAPHYACCEN_PHYLANE, base + SATAPHYACCEN_REG);
	/* ग_लिखो phy रेजिस्टर value */
	ioग_लिखो32(val, base + SATAPHYWDATA_REG);
	/* set रेजिस्टर group */
	अगर (group)
		reg |= SATAPHYADDR_PHYRATEMODE;
	/* ग_लिखो command */
	ioग_लिखो32(SATAPHYADDR_PHYCMD_WRITE | reg, base + SATAPHYADDR_REG);
	/* रुको क्रम ack */
	क्रम (समयout = 0; समयout < 100; समयout++) अणु
		val = ioपढ़ो32(base + SATAPHYACK_REG);
		अगर (val & SATAPHYACK_PHYACK)
			अवरोध;
	पूर्ण
	अगर (समयout >= 100)
		pr_err("%s timeout\n", __func__);
	/* idle state */
	ioग_लिखो32(0, base + SATAPHYADDR_REG);
पूर्ण

अटल व्योम sata_rcar_gen1_phy_init(काष्ठा sata_rcar_priv *priv)
अणु
	sata_rcar_gen1_phy_preinit(priv);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR1_REG, 0x00200188, 0);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR1_REG, 0x00200188, 1);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR3_REG, 0x0000A061, 0);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR2_REG, 0x20000000, 0);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR2_REG, 0x20000000, 1);
	sata_rcar_gen1_phy_ग_लिखो(priv, SATAPCTLR4_REG, 0x28E80000, 0);
पूर्ण

अटल व्योम sata_rcar_gen2_phy_init(काष्ठा sata_rcar_priv *priv)
अणु
	व्योम __iomem *base = priv->base;

	ioग_लिखो32(RCAR_GEN2_PHY_CTL1, base + RCAR_GEN2_PHY_CTL1_REG);
	ioग_लिखो32(RCAR_GEN2_PHY_CTL2, base + RCAR_GEN2_PHY_CTL2_REG);
	ioग_लिखो32(RCAR_GEN2_PHY_CTL3, base + RCAR_GEN2_PHY_CTL3_REG);
	ioग_लिखो32(RCAR_GEN2_PHY_CTL4, base + RCAR_GEN2_PHY_CTL4_REG);
	ioग_लिखो32(RCAR_GEN2_PHY_CTL5 | RCAR_GEN2_PHY_CTL5_DC |
		  RCAR_GEN2_PHY_CTL5_TR, base + RCAR_GEN2_PHY_CTL5_REG);
पूर्ण

अटल व्योम sata_rcar_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;

	/* mask */
	ioग_लिखो32(priv->sataपूर्णांक_mask, priv->base + SATAINTMASK_REG);

	ata_sff_मुक्तze(ap);
पूर्ण

अटल व्योम sata_rcar_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	व्योम __iomem *base = priv->base;

	/* ack */
	ioग_लिखो32(~(u32)SATA_RCAR_INT_MASK, base + SATAINTSTAT_REG);

	ata_sff_thaw(ap);

	/* unmask */
	ioग_लिखो32(priv->sataपूर्णांक_mask & ~SATA_RCAR_INT_MASK, base + SATAINTMASK_REG);
पूर्ण

अटल व्योम sata_rcar_ioपढ़ो16_rep(व्योम __iomem *reg, व्योम *buffer, पूर्णांक count)
अणु
	u16 *ptr = buffer;

	जबतक (count--) अणु
		u16 data = ioपढ़ो32(reg);

		*ptr++ = data;
	पूर्ण
पूर्ण

अटल व्योम sata_rcar_ioग_लिखो16_rep(व्योम __iomem *reg, व्योम *buffer, पूर्णांक count)
अणु
	स्थिर u16 *ptr = buffer;

	जबतक (count--)
		ioग_लिखो32(*ptr++, reg);
पूर्ण

अटल u8 sata_rcar_check_status(काष्ठा ata_port *ap)
अणु
	वापस ioपढ़ो32(ap->ioaddr.status_addr);
पूर्ण

अटल u8 sata_rcar_check_altstatus(काष्ठा ata_port *ap)
अणु
	वापस ioपढ़ो32(ap->ioaddr.altstatus_addr);
पूर्ण

अटल व्योम sata_rcar_set_devctl(काष्ठा ata_port *ap, u8 ctl)
अणु
	ioग_लिखो32(ctl, ap->ioaddr.ctl_addr);
पूर्ण

अटल व्योम sata_rcar_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	ioग_लिखो32(ATA_DEVICE_OBS, ap->ioaddr.device_addr);
	ata_sff_छोड़ो(ap);	/* needed; also flushes, क्रम mmio */
पूर्ण

अटल अचिन्हित पूर्णांक sata_rcar_ata_devchk(काष्ठा ata_port *ap,
					 अचिन्हित पूर्णांक device)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	u8 nsect, lbal;

	sata_rcar_dev_select(ap, device);

	ioग_लिखो32(0x55, ioaddr->nsect_addr);
	ioग_लिखो32(0xaa, ioaddr->lbal_addr);

	ioग_लिखो32(0xaa, ioaddr->nsect_addr);
	ioग_लिखो32(0x55, ioaddr->lbal_addr);

	ioग_लिखो32(0x55, ioaddr->nsect_addr);
	ioग_लिखो32(0xaa, ioaddr->lbal_addr);

	nsect = ioपढ़ो32(ioaddr->nsect_addr);
	lbal  = ioपढ़ो32(ioaddr->lbal_addr);

	अगर (nsect == 0x55 && lbal == 0xaa)
		वापस 1;	/* found a device */

	वापस 0;		/* nothing found */
पूर्ण

अटल पूर्णांक sata_rcar_रुको_after_reset(काष्ठा ata_link *link,
				      अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;

	ata_msleep(ap, ATA_WAIT_AFTER_RESET);

	वापस ata_sff_रुको_पढ़ोy(link, deadline);
पूर्ण

अटल पूर्णांक sata_rcar_bus_softreset(काष्ठा ata_port *ap, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	DPRINTK("ata%u: bus reset via SRST\n", ap->prपूर्णांक_id);

	/* software reset.  causes dev0 to be selected */
	ioग_लिखो32(ap->ctl, ioaddr->ctl_addr);
	udelay(20);
	ioग_लिखो32(ap->ctl | ATA_SRST, ioaddr->ctl_addr);
	udelay(20);
	ioग_लिखो32(ap->ctl, ioaddr->ctl_addr);
	ap->last_ctl = ap->ctl;

	/* रुको the port to become पढ़ोy */
	वापस sata_rcar_रुको_after_reset(&ap->link, deadline);
पूर्ण

अटल पूर्णांक sata_rcar_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
			       अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित पूर्णांक devmask = 0;
	पूर्णांक rc;
	u8 err;

	/* determine अगर device 0 is present */
	अगर (sata_rcar_ata_devchk(ap, 0))
		devmask |= 1 << 0;

	/* issue bus reset */
	DPRINTK("about to softreset, devmask=%x\n", devmask);
	rc = sata_rcar_bus_softreset(ap, deadline);
	/* अगर link is occupied, -ENODEV too is an error */
	अगर (rc && (rc != -ENODEV || sata_scr_valid(link))) अणु
		ata_link_err(link, "SRST failed (errno=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classअगरy(&link->device[0], devmask, &err);

	DPRINTK("classes[0]=%u\n", classes[0]);
	वापस 0;
पूर्ण

अटल व्योम sata_rcar_tf_load(काष्ठा ata_port *ap,
			      स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	अगर (tf->ctl != ap->last_ctl) अणु
		ioग_लिखो32(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण

	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		ioग_लिखो32(tf->hob_feature, ioaddr->feature_addr);
		ioग_लिखो32(tf->hob_nsect, ioaddr->nsect_addr);
		ioग_लिखो32(tf->hob_lbal, ioaddr->lbal_addr);
		ioग_लिखो32(tf->hob_lbam, ioaddr->lbam_addr);
		ioग_लिखो32(tf->hob_lbah, ioaddr->lbah_addr);
		VPRINTK("hob: feat 0x%X nsect 0x%X, lba 0x%X 0x%X 0x%X\n",
			tf->hob_feature,
			tf->hob_nsect,
			tf->hob_lbal,
			tf->hob_lbam,
			tf->hob_lbah);
	पूर्ण

	अगर (is_addr) अणु
		ioग_लिखो32(tf->feature, ioaddr->feature_addr);
		ioग_लिखो32(tf->nsect, ioaddr->nsect_addr);
		ioग_लिखो32(tf->lbal, ioaddr->lbal_addr);
		ioग_लिखो32(tf->lbam, ioaddr->lbam_addr);
		ioग_लिखो32(tf->lbah, ioaddr->lbah_addr);
		VPRINTK("feat 0x%X nsect 0x%X lba 0x%X 0x%X 0x%X\n",
			tf->feature,
			tf->nsect,
			tf->lbal,
			tf->lbam,
			tf->lbah);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE) अणु
		ioग_लिखो32(tf->device, ioaddr->device_addr);
		VPRINTK("device 0x%X\n", tf->device);
	पूर्ण

	ata_रुको_idle(ap);
पूर्ण

अटल व्योम sata_rcar_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	tf->command = sata_rcar_check_status(ap);
	tf->feature = ioपढ़ो32(ioaddr->error_addr);
	tf->nsect = ioपढ़ो32(ioaddr->nsect_addr);
	tf->lbal = ioपढ़ो32(ioaddr->lbal_addr);
	tf->lbam = ioपढ़ो32(ioaddr->lbam_addr);
	tf->lbah = ioपढ़ो32(ioaddr->lbah_addr);
	tf->device = ioपढ़ो32(ioaddr->device_addr);

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		ioग_लिखो32(tf->ctl | ATA_HOB, ioaddr->ctl_addr);
		tf->hob_feature = ioपढ़ो32(ioaddr->error_addr);
		tf->hob_nsect = ioपढ़ो32(ioaddr->nsect_addr);
		tf->hob_lbal = ioपढ़ो32(ioaddr->lbal_addr);
		tf->hob_lbam = ioपढ़ो32(ioaddr->lbam_addr);
		tf->hob_lbah = ioपढ़ो32(ioaddr->lbah_addr);
		ioग_लिखो32(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
	पूर्ण
पूर्ण

अटल व्योम sata_rcar_exec_command(काष्ठा ata_port *ap,
				   स्थिर काष्ठा ata_taskfile *tf)
अणु
	DPRINTK("ata%u: cmd 0x%X\n", ap->prपूर्णांक_id, tf->command);

	ioग_लिखो32(tf->command, ap->ioaddr.command_addr);
	ata_sff_छोड़ो(ap);
पूर्ण

अटल अचिन्हित पूर्णांक sata_rcar_data_xfer(काष्ठा ata_queued_cmd *qc,
					      अचिन्हित अक्षर *buf,
					      अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_port *ap = qc->dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ)
		sata_rcar_ioपढ़ो16_rep(data_addr, buf, words);
	अन्यथा
		sata_rcar_ioग_लिखो16_rep(data_addr, buf, words);

	/* Transfer trailing byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - 1;

		/*
		 * Use io*16_rep() accessors here as well to aव्योम poपूर्णांकlessly
		 * swapping bytes to and from on the big endian machines...
		 */
		अगर (rw == READ) अणु
			sata_rcar_ioपढ़ो16_rep(data_addr, pad, 1);
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			sata_rcar_ioग_लिखो16_rep(data_addr, pad, 1);
		पूर्ण
		words++;
	पूर्ण

	वापस words << 1;
पूर्ण

अटल व्योम sata_rcar_drain_fअगरo(काष्ठा ata_queued_cmd *qc)
अणु
	पूर्णांक count;
	काष्ठा ata_port *ap;

	/* We only need to flush incoming data when a command was running */
	अगर (qc == शून्य || qc->dma_dir == DMA_TO_DEVICE)
		वापस;

	ap = qc->ap;
	/* Drain up to 64K of data beक्रमe we give up this recovery method */
	क्रम (count = 0; (ap->ops->sff_check_status(ap) & ATA_DRQ) &&
			count < 65536; count += 2)
		ioपढ़ो32(ap->ioaddr.data_addr);

	/* Can become DEBUG later */
	अगर (count)
		ata_port_dbg(ap, "drained %d bytes to clear DRQ\n", count);
पूर्ण

अटल पूर्णांक sata_rcar_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg,
			      u32 *val)
अणु
	अगर (sc_reg > SCR_ACTIVE)
		वापस -EINVAL;

	*val = ioपढ़ो32(link->ap->ioaddr.scr_addr + (sc_reg << 2));
	वापस 0;
पूर्ण

अटल पूर्णांक sata_rcar_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg,
			       u32 val)
अणु
	अगर (sc_reg > SCR_ACTIVE)
		वापस -EINVAL;

	ioग_लिखो32(val, link->ap->ioaddr.scr_addr + (sc_reg << 2));
	वापस 0;
पूर्ण

अटल व्योम sata_rcar_bmdma_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_bmdma_prd *prd = ap->bmdma_prd;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, sg_len;

		/*
		 * Note: h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		addr = (u32)sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		prd[si].addr = cpu_to_le32(addr);
		prd[si].flags_len = cpu_to_le32(sg_len);
		VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", si, addr, sg_len);
	पूर्ण

	/* end-of-table flag */
	prd[si - 1].addr |= cpu_to_le32(SATA_RCAR_DTEND);
पूर्ण

अटल क्रमागत ata_completion_errors sata_rcar_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	sata_rcar_bmdma_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण

अटल व्योम sata_rcar_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक rw = qc->tf.flags & ATA_TFLAG_WRITE;
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	व्योम __iomem *base = priv->base;
	u32 dmactl;

	/* load PRD table addr. */
	mb();   /* make sure PRD table ग_लिखोs are visible to controller */
	ioग_लिखो32(ap->bmdma_prd_dma, base + ATAPI_DTB_ADR_REG);

	/* specअगरy data direction, triple-check start bit is clear */
	dmactl = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	dmactl &= ~(ATAPI_CONTROL1_RW | ATAPI_CONTROL1_STOP);
	अगर (dmactl & ATAPI_CONTROL1_START) अणु
		dmactl &= ~ATAPI_CONTROL1_START;
		dmactl |= ATAPI_CONTROL1_STOP;
	पूर्ण
	अगर (!rw)
		dmactl |= ATAPI_CONTROL1_RW;
	ioग_लिखो32(dmactl, base + ATAPI_CONTROL1_REG);

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

अटल व्योम sata_rcar_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	व्योम __iomem *base = priv->base;
	u32 dmactl;

	/* start host DMA transaction */
	dmactl = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	dmactl &= ~ATAPI_CONTROL1_STOP;
	dmactl |= ATAPI_CONTROL1_START;
	ioग_लिखो32(dmactl, base + ATAPI_CONTROL1_REG);
पूर्ण

अटल व्योम sata_rcar_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	व्योम __iomem *base = priv->base;
	u32 dmactl;

	/* क्रमce termination of DMA transfer अगर active */
	dmactl = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	अगर (dmactl & ATAPI_CONTROL1_START) अणु
		dmactl &= ~ATAPI_CONTROL1_START;
		dmactl |= ATAPI_CONTROL1_STOP;
		ioग_लिखो32(dmactl, base + ATAPI_CONTROL1_REG);
	पूर्ण

	/* one-PIO-cycle guaranteed रुको, per spec, क्रम HDMA1:0 transition */
	ata_sff_dma_छोड़ो(ap);
पूर्ण

अटल u8 sata_rcar_bmdma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	u8 host_stat = 0;
	u32 status;

	status = ioपढ़ो32(priv->base + ATAPI_STATUS_REG);
	अगर (status & ATAPI_STATUS_DEVINT)
		host_stat |= ATA_DMA_INTR;
	अगर (status & ATAPI_STATUS_ACT)
		host_stat |= ATA_DMA_ACTIVE;

	वापस host_stat;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sata_rcar_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	/*
	 * This controller allows transfer chunks up to 512MB which cross 64KB
	 * boundaries, thereक्रमe the DMA limits are more relaxed than standard
	 * ATA SFF.
	 */
	.sg_tablesize		= ATA_MAX_PRD,
	.dma_boundary		= SATA_RCAR_DMA_BOUNDARY,
पूर्ण;

अटल काष्ठा ata_port_operations sata_rcar_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.मुक्तze			= sata_rcar_मुक्तze,
	.thaw			= sata_rcar_thaw,
	.softreset		= sata_rcar_softreset,

	.scr_पढ़ो		= sata_rcar_scr_पढ़ो,
	.scr_ग_लिखो		= sata_rcar_scr_ग_लिखो,

	.sff_dev_select		= sata_rcar_dev_select,
	.sff_set_devctl		= sata_rcar_set_devctl,
	.sff_check_status	= sata_rcar_check_status,
	.sff_check_altstatus	= sata_rcar_check_altstatus,
	.sff_tf_load		= sata_rcar_tf_load,
	.sff_tf_पढ़ो		= sata_rcar_tf_पढ़ो,
	.sff_exec_command	= sata_rcar_exec_command,
	.sff_data_xfer		= sata_rcar_data_xfer,
	.sff_drain_fअगरo		= sata_rcar_drain_fअगरo,

	.qc_prep		= sata_rcar_qc_prep,

	.bmdma_setup		= sata_rcar_bmdma_setup,
	.bmdma_start		= sata_rcar_bmdma_start,
	.bmdma_stop		= sata_rcar_bmdma_stop,
	.bmdma_status		= sata_rcar_bmdma_status,
पूर्ण;

अटल व्योम sata_rcar_serr_पूर्णांकerrupt(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_rcar_priv *priv = ap->host->निजी_data;
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	पूर्णांक मुक्तze = 0;
	u32 serror;

	serror = ioपढ़ो32(priv->base + SCRSERR_REG);
	अगर (!serror)
		वापस;

	DPRINTK("SError @host_intr: 0x%x\n", serror);

	/* first, analyze and record host port events */
	ata_ehi_clear_desc(ehi);

	अगर (serror & (SERR_DEV_XCHG | SERR_PHYRDY_CHG)) अणु
		/* Setup a soft-reset EH action */
		ata_ehi_hotplugged(ehi);
		ata_ehi_push_desc(ehi, "%s", "hotplug");

		मुक्तze = serror & SERR_COMM_WAKE ? 0 : 1;
	पूर्ण

	/* मुक्तze or पात */
	अगर (मुक्तze)
		ata_port_मुक्तze(ap);
	अन्यथा
		ata_port_पात(ap);
पूर्ण

अटल व्योम sata_rcar_ata_पूर्णांकerrupt(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक handled = 0;

	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc)
		handled |= ata_bmdma_port_पूर्णांकr(ap, qc);

	/* be sure to clear ATA पूर्णांकerrupt */
	अगर (!handled)
		sata_rcar_check_status(ap);
पूर्ण

अटल irqवापस_t sata_rcar_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा sata_rcar_priv *priv = host->निजी_data;
	व्योम __iomem *base = priv->base;
	अचिन्हित पूर्णांक handled = 0;
	काष्ठा ata_port *ap;
	u32 sataपूर्णांकstat;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	sataपूर्णांकstat = ioपढ़ो32(base + SATAINTSTAT_REG);
	sataपूर्णांकstat &= SATA_RCAR_INT_MASK;
	अगर (!sataपूर्णांकstat)
		जाओ करोne;
	/* ack */
	ioग_लिखो32(~sataपूर्णांकstat & priv->sataपूर्णांक_mask, base + SATAINTSTAT_REG);

	ap = host->ports[0];

	अगर (sataपूर्णांकstat & SATAINTSTAT_ATA)
		sata_rcar_ata_पूर्णांकerrupt(ap);

	अगर (sataपूर्णांकstat & SATAINTSTAT_SERR)
		sata_rcar_serr_पूर्णांकerrupt(ap);

	handled = 1;
करोne:
	spin_unlock_irqrestore(&host->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम sata_rcar_setup_port(काष्ठा ata_host *host)
अणु
	काष्ठा ata_port *ap = host->ports[0];
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	काष्ठा sata_rcar_priv *priv = host->निजी_data;
	व्योम __iomem *base = priv->base;

	ap->ops		= &sata_rcar_port_ops;
	ap->pio_mask	= ATA_PIO4;
	ap->udma_mask	= ATA_UDMA6;
	ap->flags	|= ATA_FLAG_SATA;

	अगर (priv->type == RCAR_R8A7790_ES1_SATA)
		ap->flags	|= ATA_FLAG_NO_DIPM;

	ioaddr->cmd_addr = base + SDATA_REG;
	ioaddr->ctl_addr = base + SSDEVCON_REG;
	ioaddr->scr_addr = base + SCRSSTS_REG;
	ioaddr->altstatus_addr = ioaddr->ctl_addr;

	ioaddr->data_addr	= ioaddr->cmd_addr + (ATA_REG_DATA << 2);
	ioaddr->error_addr	= ioaddr->cmd_addr + (ATA_REG_ERR << 2);
	ioaddr->feature_addr	= ioaddr->cmd_addr + (ATA_REG_FEATURE << 2);
	ioaddr->nsect_addr	= ioaddr->cmd_addr + (ATA_REG_NSECT << 2);
	ioaddr->lbal_addr	= ioaddr->cmd_addr + (ATA_REG_LBAL << 2);
	ioaddr->lbam_addr	= ioaddr->cmd_addr + (ATA_REG_LBAM << 2);
	ioaddr->lbah_addr	= ioaddr->cmd_addr + (ATA_REG_LBAH << 2);
	ioaddr->device_addr	= ioaddr->cmd_addr + (ATA_REG_DEVICE << 2);
	ioaddr->status_addr	= ioaddr->cmd_addr + (ATA_REG_STATUS << 2);
	ioaddr->command_addr	= ioaddr->cmd_addr + (ATA_REG_CMD << 2);
पूर्ण

अटल व्योम sata_rcar_init_module(काष्ठा sata_rcar_priv *priv)
अणु
	व्योम __iomem *base = priv->base;
	u32 val;

	/* SATA-IP reset state */
	val = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	val |= ATAPI_CONTROL1_RESET;
	ioग_लिखो32(val, base + ATAPI_CONTROL1_REG);

	/* ISM mode, PRD mode, DTEND flag at bit 0 */
	val = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	val |= ATAPI_CONTROL1_ISM;
	val |= ATAPI_CONTROL1_DESE;
	val |= ATAPI_CONTROL1_DTA32M;
	ioग_लिखो32(val, base + ATAPI_CONTROL1_REG);

	/* Release the SATA-IP from the reset state */
	val = ioपढ़ो32(base + ATAPI_CONTROL1_REG);
	val &= ~ATAPI_CONTROL1_RESET;
	ioग_लिखो32(val, base + ATAPI_CONTROL1_REG);

	/* ack and mask */
	ioग_लिखो32(0, base + SATAINTSTAT_REG);
	ioग_लिखो32(priv->sataपूर्णांक_mask, base + SATAINTMASK_REG);

	/* enable पूर्णांकerrupts */
	ioग_लिखो32(ATAPI_INT_ENABLE_SATAINT, base + ATAPI_INT_ENABLE_REG);
पूर्ण

अटल व्योम sata_rcar_init_controller(काष्ठा ata_host *host)
अणु
	काष्ठा sata_rcar_priv *priv = host->निजी_data;

	priv->sataपूर्णांक_mask = SATAINTMASK_ALL_GEN2;

	/* reset and setup phy */
	चयन (priv->type) अणु
	हाल RCAR_GEN1_SATA:
		priv->sataपूर्णांक_mask = SATAINTMASK_ALL_GEN1;
		sata_rcar_gen1_phy_init(priv);
		अवरोध;
	हाल RCAR_GEN2_SATA:
	हाल RCAR_R8A7790_ES1_SATA:
		sata_rcar_gen2_phy_init(priv);
		अवरोध;
	हाल RCAR_GEN3_SATA:
		अवरोध;
	शेष:
		dev_warn(host->dev, "SATA phy is not initialized\n");
		अवरोध;
	पूर्ण

	sata_rcar_init_module(priv);
पूर्ण

अटल स्थिर काष्ठा of_device_id sata_rcar_match[] = अणु
	अणु
		/* Deprecated by "renesas,sata-r8a7779" */
		.compatible = "renesas,rcar-sata",
		.data = (व्योम *)RCAR_GEN1_SATA,
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7779",
		.data = (व्योम *)RCAR_GEN1_SATA,
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7790",
		.data = (व्योम *)RCAR_GEN2_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7790-es1",
		.data = (व्योम *)RCAR_R8A7790_ES1_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7791",
		.data = (व्योम *)RCAR_GEN2_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7793",
		.data = (व्योम *)RCAR_GEN2_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,sata-r8a7795",
		.data = (व्योम *)RCAR_GEN3_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-sata",
		.data = (व्योम *)RCAR_GEN2_SATA
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-sata",
		.data = (व्योम *)RCAR_GEN3_SATA
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sata_rcar_match);

अटल पूर्णांक sata_rcar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ata_host *host;
	काष्ठा sata_rcar_priv *priv;
	काष्ठा resource *mem;
	पूर्णांक irq;
	पूर्णांक ret = 0;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	अगर (!irq)
		वापस -EINVAL;

	priv = devm_kzalloc(dev, माप(काष्ठा sata_rcar_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->type = (क्रमागत sata_rcar_type)of_device_get_match_data(dev);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_pm_put;

	host = ata_host_alloc(dev, 1);
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ err_pm_put;
	पूर्ण

	host->निजी_data = priv;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ err_pm_put;
	पूर्ण

	/* setup port */
	sata_rcar_setup_port(host);

	/* initialize host controller */
	sata_rcar_init_controller(host);

	ret = ata_host_activate(host, irq, sata_rcar_पूर्णांकerrupt, 0,
				&sata_rcar_sht);
	अगर (!ret)
		वापस 0;

err_pm_put:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक sata_rcar_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sata_rcar_priv *priv = host->निजी_data;
	व्योम __iomem *base = priv->base;

	ata_host_detach(host);

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(0, base + ATAPI_INT_ENABLE_REG);
	/* ack and mask */
	ioग_लिखो32(0, base + SATAINTSTAT_REG);
	ioग_लिखो32(priv->sataपूर्णांक_mask, base + SATAINTMASK_REG);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sata_rcar_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा sata_rcar_priv *priv = host->निजी_data;
	व्योम __iomem *base = priv->base;
	पूर्णांक ret;

	ret = ata_host_suspend(host, PMSG_SUSPEND);
	अगर (!ret) अणु
		/* disable पूर्णांकerrupts */
		ioग_लिखो32(0, base + ATAPI_INT_ENABLE_REG);
		/* mask */
		ioग_लिखो32(priv->sataपूर्णांक_mask, base + SATAINTMASK_REG);

		pm_runसमय_put(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sata_rcar_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा sata_rcar_priv *priv = host->निजी_data;
	व्योम __iomem *base = priv->base;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put(dev);
		वापस ret;
	पूर्ण

	अगर (priv->type == RCAR_GEN3_SATA) अणु
		sata_rcar_init_module(priv);
	पूर्ण अन्यथा अणु
		/* ack and mask */
		ioग_लिखो32(0, base + SATAINTSTAT_REG);
		ioग_लिखो32(priv->sataपूर्णांक_mask, base + SATAINTMASK_REG);

		/* enable पूर्णांकerrupts */
		ioग_लिखो32(ATAPI_INT_ENABLE_SATAINT,
			  base + ATAPI_INT_ENABLE_REG);
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण

अटल पूर्णांक sata_rcar_restore(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put(dev);
		वापस ret;
	पूर्ण

	sata_rcar_setup_port(host);

	/* initialize host controller */
	sata_rcar_init_controller(host);

	ata_host_resume(host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sata_rcar_pm_ops = अणु
	.suspend	= sata_rcar_suspend,
	.resume		= sata_rcar_resume,
	.मुक्तze		= sata_rcar_suspend,
	.thaw		= sata_rcar_resume,
	.घातeroff	= sata_rcar_suspend,
	.restore	= sata_rcar_restore,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sata_rcar_driver = अणु
	.probe		= sata_rcar_probe,
	.हटाओ		= sata_rcar_हटाओ,
	.driver = अणु
		.name		= DRV_NAME,
		.of_match_table	= sata_rcar_match,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm		= &sata_rcar_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sata_rcar_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladimir Barinov");
MODULE_DESCRIPTION("Renesas R-Car SATA controller low level driver");
