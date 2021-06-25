<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/bcma/bcma_regs.h>

#समावेश <defs.h>
#समावेश <soc.h>
#समावेश <brcm_hw_ids.h>
#समावेश <brcmu_utils.h>
#समावेश <chipcommon.h>
#समावेश "debug.h"
#समावेश "chip.h"

/* SOC Interconnect types (aka chip types) */
#घोषणा SOCI_SB		0
#घोषणा SOCI_AI		1

/* PL-368 DMP definitions */
#घोषणा DMP_DESC_TYPE_MSK	0x0000000F
#घोषणा  DMP_DESC_EMPTY		0x00000000
#घोषणा  DMP_DESC_VALID		0x00000001
#घोषणा  DMP_DESC_COMPONENT	0x00000001
#घोषणा  DMP_DESC_MASTER_PORT	0x00000003
#घोषणा  DMP_DESC_ADDRESS	0x00000005
#घोषणा  DMP_DESC_ADDRSIZE_GT32	0x00000008
#घोषणा  DMP_DESC_EOT		0x0000000F

#घोषणा DMP_COMP_DESIGNER	0xFFF00000
#घोषणा DMP_COMP_DESIGNER_S	20
#घोषणा DMP_COMP_PARTNUM	0x000FFF00
#घोषणा DMP_COMP_PARTNUM_S	8
#घोषणा DMP_COMP_CLASS		0x000000F0
#घोषणा DMP_COMP_CLASS_S	4
#घोषणा DMP_COMP_REVISION	0xFF000000
#घोषणा DMP_COMP_REVISION_S	24
#घोषणा DMP_COMP_NUM_SWRAP	0x00F80000
#घोषणा DMP_COMP_NUM_SWRAP_S	19
#घोषणा DMP_COMP_NUM_MWRAP	0x0007C000
#घोषणा DMP_COMP_NUM_MWRAP_S	14
#घोषणा DMP_COMP_NUM_SPORT	0x00003E00
#घोषणा DMP_COMP_NUM_SPORT_S	9
#घोषणा DMP_COMP_NUM_MPORT	0x000001F0
#घोषणा DMP_COMP_NUM_MPORT_S	4

#घोषणा DMP_MASTER_PORT_UID	0x0000FF00
#घोषणा DMP_MASTER_PORT_UID_S	8
#घोषणा DMP_MASTER_PORT_NUM	0x000000F0
#घोषणा DMP_MASTER_PORT_NUM_S	4

#घोषणा DMP_SLAVE_ADDR_BASE	0xFFFFF000
#घोषणा DMP_SLAVE_ADDR_BASE_S	12
#घोषणा DMP_SLAVE_PORT_NUM	0x00000F00
#घोषणा DMP_SLAVE_PORT_NUM_S	8
#घोषणा DMP_SLAVE_TYPE		0x000000C0
#घोषणा DMP_SLAVE_TYPE_S	6
#घोषणा  DMP_SLAVE_TYPE_SLAVE	0
#घोषणा  DMP_SLAVE_TYPE_BRIDGE	1
#घोषणा  DMP_SLAVE_TYPE_SWRAP	2
#घोषणा  DMP_SLAVE_TYPE_MWRAP	3
#घोषणा DMP_SLAVE_SIZE_TYPE	0x00000030
#घोषणा DMP_SLAVE_SIZE_TYPE_S	4
#घोषणा  DMP_SLAVE_SIZE_4K	0
#घोषणा  DMP_SLAVE_SIZE_8K	1
#घोषणा  DMP_SLAVE_SIZE_16K	2
#घोषणा  DMP_SLAVE_SIZE_DESC	3

/* EROM CompIdentB */
#घोषणा CIB_REV_MASK		0xff000000
#घोषणा CIB_REV_SHIFT		24

/* ARM CR4 core specअगरic control flag bits */
#घोषणा ARMCR4_BCMA_IOCTL_CPUHALT	0x0020

/* D11 core specअगरic control flag bits */
#घोषणा D11_BCMA_IOCTL_PHYCLOCKEN	0x0004
#घोषणा D11_BCMA_IOCTL_PHYRESET		0x0008

/* chip core base & ramsize */
/* bcm4329 */
/* SDIO device core, ID 0x829 */
#घोषणा BCM4329_CORE_BUS_BASE		0x18011000
/* पूर्णांकernal memory core, ID 0x80e */
#घोषणा BCM4329_CORE_SOCRAM_BASE	0x18003000
/* ARM Cortex M3 core, ID 0x82a */
#घोषणा BCM4329_CORE_ARM_BASE		0x18002000

/* Max possibly supported memory size (limited by IO mapped memory) */
#घोषणा BRCMF_CHIP_MAX_MEMSIZE		(4 * 1024 * 1024)

#घोषणा CORE_SB(base, field) \
		(base + SBCONFIGOFF + दुरत्व(काष्ठा sbconfig, field))
#घोषणा	SBCOREREV(sbidh) \
	((((sbidh) & SSB_IDHIGH_RCHI) >> SSB_IDHIGH_RCHI_SHIFT) | \
	  ((sbidh) & SSB_IDHIGH_RCLO))

काष्ठा sbconfig अणु
	u32 PAD[2];
	u32 sbipsflag;	/* initiator port ocp slave flag */
	u32 PAD[3];
	u32 sbtpsflag;	/* target port ocp slave flag */
	u32 PAD[11];
	u32 sbपंचांगerrloga;	/* (sonics >= 2.3) */
	u32 PAD;
	u32 sbपंचांगerrlog;	/* (sonics >= 2.3) */
	u32 PAD[3];
	u32 sbadmatch3;	/* address match3 */
	u32 PAD;
	u32 sbadmatch2;	/* address match2 */
	u32 PAD;
	u32 sbadmatch1;	/* address match1 */
	u32 PAD[7];
	u32 sbimstate;	/* initiator agent state */
	u32 sbपूर्णांकvec;	/* पूर्णांकerrupt mask */
	u32 sbपंचांगstatelow;	/* target state */
	u32 sbपंचांगstatehigh;	/* target state */
	u32 sbbwa0;		/* bandwidth allocation table0 */
	u32 PAD;
	u32 sbimconfiglow;	/* initiator configuration */
	u32 sbimconfighigh;	/* initiator configuration */
	u32 sbadmatch0;	/* address match0 */
	u32 PAD;
	u32 sbपंचांगconfiglow;	/* target configuration */
	u32 sbपंचांगconfighigh;	/* target configuration */
	u32 sbbconfig;	/* broadcast configuration */
	u32 PAD;
	u32 sbbstate;	/* broadcast state */
	u32 PAD[3];
	u32 sbactcnfg;	/* activate configuration */
	u32 PAD[3];
	u32 sbflagst;	/* current sbflags */
	u32 PAD[3];
	u32 sbidlow;		/* identअगरication */
	u32 sbidhigh;	/* identअगरication */
पूर्ण;

/* bankidx and bankinfo reg defines corerev >= 8 */
#घोषणा SOCRAM_BANKINFO_RETNTRAM_MASK	0x00010000
#घोषणा SOCRAM_BANKINFO_SZMASK		0x0000007f
#घोषणा SOCRAM_BANKIDX_ROM_MASK		0x00000100

#घोषणा SOCRAM_BANKIDX_MEMTYPE_SHIFT	8
/* socram bankinfo memtype */
#घोषणा SOCRAM_MEMTYPE_RAM		0
#घोषणा SOCRAM_MEMTYPE_R0M		1
#घोषणा SOCRAM_MEMTYPE_DEVRAM		2

#घोषणा SOCRAM_BANKINFO_SZBASE		8192
#घोषणा SRCI_LSS_MASK		0x00f00000
#घोषणा SRCI_LSS_SHIFT		20
#घोषणा	SRCI_SRNB_MASK		0xf0
#घोषणा	SRCI_SRNB_MASK_EXT	0x100
#घोषणा	SRCI_SRNB_SHIFT		4
#घोषणा	SRCI_SRBSZ_MASK		0xf
#घोषणा	SRCI_SRBSZ_SHIFT	0
#घोषणा SR_BSZ_BASE		14

काष्ठा sbsocramregs अणु
	u32 coreinfo;
	u32 bwalloc;
	u32 extracoreinfo;
	u32 biststat;
	u32 bankidx;
	u32 standbyctrl;

	u32 errlogstatus;	/* rev 6 */
	u32 errlogaddr;	/* rev 6 */
	/* used क्रम patching rev 3 & 5 */
	u32 cambankidx;
	u32 cambankstandbyctrl;
	u32 cambankpatchctrl;
	u32 cambankpatchtblbaseaddr;
	u32 cambankcmdreg;
	u32 cambankdatareg;
	u32 cambankmaskreg;
	u32 PAD[1];
	u32 bankinfo;	/* corev 8 */
	u32 bankpda;
	u32 PAD[14];
	u32 exपंचांगemconfig;
	u32 exपंचांगemparitycsr;
	u32 exपंचांगemparityerrdata;
	u32 exपंचांगemparityerrcnt;
	u32 exपंचांगemwrctrlandsize;
	u32 PAD[84];
	u32 workaround;
	u32 pwrctl;		/* corerev >= 2 */
	u32 PAD[133];
	u32 sr_control;     /* corerev >= 15 */
	u32 sr_status;      /* corerev >= 15 */
	u32 sr_address;     /* corerev >= 15 */
	u32 sr_data;        /* corerev >= 15 */
पूर्ण;

#घोषणा SOCRAMREGOFFS(_f)	दुरत्व(काष्ठा sbsocramregs, _f)
#घोषणा SYSMEMREGOFFS(_f)	दुरत्व(काष्ठा sbsocramregs, _f)

#घोषणा ARMCR4_CAP		(0x04)
#घोषणा ARMCR4_BANKIDX		(0x40)
#घोषणा ARMCR4_BANKINFO		(0x44)
#घोषणा ARMCR4_BANKPDA		(0x4C)

#घोषणा	ARMCR4_TCBBNB_MASK	0xf0
#घोषणा	ARMCR4_TCBBNB_SHIFT	4
#घोषणा	ARMCR4_TCBANB_MASK	0xf
#घोषणा	ARMCR4_TCBANB_SHIFT	0

#घोषणा	ARMCR4_BSZ_MASK		0x3f
#घोषणा	ARMCR4_BSZ_MULT		8192

काष्ठा brcmf_core_priv अणु
	काष्ठा brcmf_core pub;
	u32 wrapbase;
	काष्ठा list_head list;
	काष्ठा brcmf_chip_priv *chip;
पूर्ण;

काष्ठा brcmf_chip_priv अणु
	काष्ठा brcmf_chip pub;
	स्थिर काष्ठा brcmf_buscore_ops *ops;
	व्योम *ctx;
	/* assured first core is chipcommon, second core is buscore */
	काष्ठा list_head cores;
	u16 num_cores;

	bool (*iscoreup)(काष्ठा brcmf_core_priv *core);
	व्योम (*coredisable)(काष्ठा brcmf_core_priv *core, u32 prereset,
			    u32 reset);
	व्योम (*resetcore)(काष्ठा brcmf_core_priv *core, u32 prereset, u32 reset,
			  u32 postreset);
पूर्ण;

अटल व्योम brcmf_chip_sb_corerev(काष्ठा brcmf_chip_priv *ci,
				  काष्ठा brcmf_core *core)
अणु
	u32 regdata;

	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(core->base, sbidhigh));
	core->rev = SBCOREREV(regdata);
पूर्ण

अटल bool brcmf_chip_sb_iscoreup(काष्ठा brcmf_core_priv *core)
अणु
	काष्ठा brcmf_chip_priv *ci;
	u32 regdata;
	u32 address;

	ci = core->chip;
	address = CORE_SB(core->pub.base, sbपंचांगstatelow);
	regdata = ci->ops->पढ़ो32(ci->ctx, address);
	regdata &= (SSB_TMSLOW_RESET | SSB_TMSLOW_REJECT |
		    SSB_IMSTATE_REJECT | SSB_TMSLOW_CLOCK);
	वापस SSB_TMSLOW_CLOCK == regdata;
पूर्ण

अटल bool brcmf_chip_ai_iscoreup(काष्ठा brcmf_core_priv *core)
अणु
	काष्ठा brcmf_chip_priv *ci;
	u32 regdata;
	bool ret;

	ci = core->chip;
	regdata = ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_IOCTL);
	ret = (regdata & (BCMA_IOCTL_FGC | BCMA_IOCTL_CLK)) == BCMA_IOCTL_CLK;

	regdata = ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL);
	ret = ret && ((regdata & BCMA_RESET_CTL_RESET) == 0);

	वापस ret;
पूर्ण

अटल व्योम brcmf_chip_sb_coredisable(काष्ठा brcmf_core_priv *core,
				      u32 prereset, u32 reset)
अणु
	काष्ठा brcmf_chip_priv *ci;
	u32 val, base;

	ci = core->chip;
	base = core->pub.base;
	val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
	अगर (val & SSB_TMSLOW_RESET)
		वापस;

	val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
	अगर ((val & SSB_TMSLOW_CLOCK) != 0) अणु
		/*
		 * set target reject and spin until busy is clear
		 * (preserve core-specअगरic bits)
		 */
		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
		ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow),
					 val | SSB_TMSLOW_REJECT);

		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
		udelay(1);
		SPINWAIT((ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatehigh))
			  & SSB_TMSHIGH_BUSY), 100000);

		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatehigh));
		अगर (val & SSB_TMSHIGH_BUSY)
			brcmf_err("core state still busy\n");

		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbidlow));
		अगर (val & SSB_IDLOW_INITIATOR) अणु
			val = ci->ops->पढ़ो32(ci->ctx,
					      CORE_SB(base, sbimstate));
			val |= SSB_IMSTATE_REJECT;
			ci->ops->ग_लिखो32(ci->ctx,
					 CORE_SB(base, sbimstate), val);
			val = ci->ops->पढ़ो32(ci->ctx,
					      CORE_SB(base, sbimstate));
			udelay(1);
			SPINWAIT((ci->ops->पढ़ो32(ci->ctx,
						  CORE_SB(base, sbimstate)) &
				  SSB_IMSTATE_BUSY), 100000);
		पूर्ण

		/* set reset and reject जबतक enabling the घड़ीs */
		val = SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
		      SSB_TMSLOW_REJECT | SSB_TMSLOW_RESET;
		ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow), val);
		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
		udelay(10);

		/* clear the initiator reject bit */
		val = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbidlow));
		अगर (val & SSB_IDLOW_INITIATOR) अणु
			val = ci->ops->पढ़ो32(ci->ctx,
					      CORE_SB(base, sbimstate));
			val &= ~SSB_IMSTATE_REJECT;
			ci->ops->ग_लिखो32(ci->ctx,
					 CORE_SB(base, sbimstate), val);
		पूर्ण
	पूर्ण

	/* leave reset and reject निश्चितed */
	ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow),
			 (SSB_TMSLOW_REJECT | SSB_TMSLOW_RESET));
	udelay(1);
पूर्ण

अटल व्योम brcmf_chip_ai_coredisable(काष्ठा brcmf_core_priv *core,
				      u32 prereset, u32 reset)
अणु
	काष्ठा brcmf_chip_priv *ci;
	u32 regdata;

	ci = core->chip;

	/* अगर core is alपढ़ोy in reset, skip reset */
	regdata = ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL);
	अगर ((regdata & BCMA_RESET_CTL_RESET) != 0)
		जाओ in_reset_configure;

	/* configure reset */
	ci->ops->ग_लिखो32(ci->ctx, core->wrapbase + BCMA_IOCTL,
			 prereset | BCMA_IOCTL_FGC | BCMA_IOCTL_CLK);
	ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_IOCTL);

	/* put in reset */
	ci->ops->ग_लिखो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL,
			 BCMA_RESET_CTL_RESET);
	usleep_range(10, 20);

	/* रुको till reset is 1 */
	SPINWAIT(ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL) !=
		 BCMA_RESET_CTL_RESET, 300);

in_reset_configure:
	/* in-reset configure */
	ci->ops->ग_लिखो32(ci->ctx, core->wrapbase + BCMA_IOCTL,
			 reset | BCMA_IOCTL_FGC | BCMA_IOCTL_CLK);
	ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_IOCTL);
पूर्ण

अटल व्योम brcmf_chip_sb_resetcore(काष्ठा brcmf_core_priv *core, u32 prereset,
				    u32 reset, u32 postreset)
अणु
	काष्ठा brcmf_chip_priv *ci;
	u32 regdata;
	u32 base;

	ci = core->chip;
	base = core->pub.base;
	/*
	 * Must करो the disable sequence first to work क्रम
	 * arbitrary current core state.
	 */
	brcmf_chip_sb_coredisable(core, 0, 0);

	/*
	 * Now करो the initialization sequence.
	 * set reset जबतक enabling the घड़ी and
	 * क्रमcing them on throughout the core
	 */
	ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow),
			 SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
			 SSB_TMSLOW_RESET);
	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
	udelay(1);

	/* clear any serror */
	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatehigh));
	अगर (regdata & SSB_TMSHIGH_SERR)
		ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatehigh), 0);

	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbimstate));
	अगर (regdata & (SSB_IMSTATE_IBE | SSB_IMSTATE_TO)) अणु
		regdata &= ~(SSB_IMSTATE_IBE | SSB_IMSTATE_TO);
		ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbimstate), regdata);
	पूर्ण

	/* clear reset and allow it to propagate throughout the core */
	ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow),
			 SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK);
	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
	udelay(1);

	/* leave घड़ी enabled */
	ci->ops->ग_लिखो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow),
			 SSB_TMSLOW_CLOCK);
	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_SB(base, sbपंचांगstatelow));
	udelay(1);
पूर्ण

अटल व्योम brcmf_chip_ai_resetcore(काष्ठा brcmf_core_priv *core, u32 prereset,
				    u32 reset, u32 postreset)
अणु
	काष्ठा brcmf_chip_priv *ci;
	पूर्णांक count;
	काष्ठा brcmf_core *d11core2 = शून्य;
	काष्ठा brcmf_core_priv *d11priv2 = शून्य;

	ci = core->chip;

	/* special handle two D11 cores reset */
	अगर (core->pub.id == BCMA_CORE_80211) अणु
		d11core2 = brcmf_chip_get_d11core(&ci->pub, 1);
		अगर (d11core2) अणु
			brcmf_dbg(INFO, "found two d11 cores, reset both\n");
			d11priv2 = container_of(d11core2,
						काष्ठा brcmf_core_priv, pub);
		पूर्ण
	पूर्ण

	/* must disable first to work क्रम arbitrary current core state */
	brcmf_chip_ai_coredisable(core, prereset, reset);
	अगर (d11priv2)
		brcmf_chip_ai_coredisable(d11priv2, prereset, reset);

	count = 0;
	जबतक (ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL) &
	       BCMA_RESET_CTL_RESET) अणु
		ci->ops->ग_लिखो32(ci->ctx, core->wrapbase + BCMA_RESET_CTL, 0);
		count++;
		अगर (count > 50)
			अवरोध;
		usleep_range(40, 60);
	पूर्ण

	अगर (d11priv2) अणु
		count = 0;
		जबतक (ci->ops->पढ़ो32(ci->ctx,
				       d11priv2->wrapbase + BCMA_RESET_CTL) &
				       BCMA_RESET_CTL_RESET) अणु
			ci->ops->ग_लिखो32(ci->ctx,
					 d11priv2->wrapbase + BCMA_RESET_CTL,
					 0);
			count++;
			अगर (count > 50)
				अवरोध;
			usleep_range(40, 60);
		पूर्ण
	पूर्ण

	ci->ops->ग_लिखो32(ci->ctx, core->wrapbase + BCMA_IOCTL,
			 postreset | BCMA_IOCTL_CLK);
	ci->ops->पढ़ो32(ci->ctx, core->wrapbase + BCMA_IOCTL);

	अगर (d11priv2) अणु
		ci->ops->ग_लिखो32(ci->ctx, d11priv2->wrapbase + BCMA_IOCTL,
				 postreset | BCMA_IOCTL_CLK);
		ci->ops->पढ़ो32(ci->ctx, d11priv2->wrapbase + BCMA_IOCTL);
	पूर्ण
पूर्ण

अक्षर *brcmf_chip_name(u32 id, u32 rev, अक्षर *buf, uपूर्णांक len)
अणु
	स्थिर अक्षर *fmt;

	fmt = ((id > 0xa000) || (id < 0x4000)) ? "BCM%d/%u" : "BCM%x/%u";
	snम_लिखो(buf, len, fmt, id, rev);
	वापस buf;
पूर्ण

अटल काष्ठा brcmf_core *brcmf_chip_add_core(काष्ठा brcmf_chip_priv *ci,
					      u16 coreid, u32 base,
					      u32 wrapbase)
अणु
	काष्ठा brcmf_core_priv *core;

	core = kzalloc(माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस ERR_PTR(-ENOMEM);

	core->pub.id = coreid;
	core->pub.base = base;
	core->chip = ci;
	core->wrapbase = wrapbase;

	list_add_tail(&core->list, &ci->cores);
	वापस &core->pub;
पूर्ण

/* safety check क्रम chipinfo */
अटल पूर्णांक brcmf_chip_cores_check(काष्ठा brcmf_chip_priv *ci)
अणु
	काष्ठा brcmf_core_priv *core;
	bool need_socram = false;
	bool has_socram = false;
	bool cpu_found = false;
	पूर्णांक idx = 1;

	list_क्रम_each_entry(core, &ci->cores, list) अणु
		brcmf_dbg(INFO, " [%-2d] core 0x%x:%-2d base 0x%08x wrap 0x%08x\n",
			  idx++, core->pub.id, core->pub.rev, core->pub.base,
			  core->wrapbase);

		चयन (core->pub.id) अणु
		हाल BCMA_CORE_ARM_CM3:
			cpu_found = true;
			need_socram = true;
			अवरोध;
		हाल BCMA_CORE_INTERNAL_MEM:
			has_socram = true;
			अवरोध;
		हाल BCMA_CORE_ARM_CR4:
			cpu_found = true;
			अवरोध;
		हाल BCMA_CORE_ARM_CA7:
			cpu_found = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cpu_found) अणु
		brcmf_err("CPU core not detected\n");
		वापस -ENXIO;
	पूर्ण
	/* check RAM core presence क्रम ARM CM3 core */
	अगर (need_socram && !has_socram) अणु
		brcmf_err("RAM core not provided with ARM CM3 core\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 brcmf_chip_core_पढ़ो32(काष्ठा brcmf_core_priv *core, u16 reg)
अणु
	वापस core->chip->ops->पढ़ो32(core->chip->ctx, core->pub.base + reg);
पूर्ण

अटल व्योम brcmf_chip_core_ग_लिखो32(काष्ठा brcmf_core_priv *core,
				    u16 reg, u32 val)
अणु
	core->chip->ops->ग_लिखो32(core->chip->ctx, core->pub.base + reg, val);
पूर्ण

अटल bool brcmf_chip_socram_banksize(काष्ठा brcmf_core_priv *core, u8 idx,
				       u32 *banksize)
अणु
	u32 bankinfo;
	u32 bankidx = (SOCRAM_MEMTYPE_RAM << SOCRAM_BANKIDX_MEMTYPE_SHIFT);

	bankidx |= idx;
	brcmf_chip_core_ग_लिखो32(core, SOCRAMREGOFFS(bankidx), bankidx);
	bankinfo = brcmf_chip_core_पढ़ो32(core, SOCRAMREGOFFS(bankinfo));
	*banksize = (bankinfo & SOCRAM_BANKINFO_SZMASK) + 1;
	*banksize *= SOCRAM_BANKINFO_SZBASE;
	वापस !!(bankinfo & SOCRAM_BANKINFO_RETNTRAM_MASK);
पूर्ण

अटल व्योम brcmf_chip_socram_ramsize(काष्ठा brcmf_core_priv *sr, u32 *ramsize,
				      u32 *srsize)
अणु
	u32 coreinfo;
	uपूर्णांक nb, banksize, lss;
	bool retent;
	पूर्णांक i;

	*ramsize = 0;
	*srsize = 0;

	अगर (WARN_ON(sr->pub.rev < 4))
		वापस;

	अगर (!brcmf_chip_iscoreup(&sr->pub))
		brcmf_chip_resetcore(&sr->pub, 0, 0, 0);

	/* Get info क्रम determining size */
	coreinfo = brcmf_chip_core_पढ़ो32(sr, SOCRAMREGOFFS(coreinfo));
	nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;

	अगर ((sr->pub.rev <= 7) || (sr->pub.rev == 12)) अणु
		banksize = (coreinfo & SRCI_SRBSZ_MASK);
		lss = (coreinfo & SRCI_LSS_MASK) >> SRCI_LSS_SHIFT;
		अगर (lss != 0)
			nb--;
		*ramsize = nb * (1 << (banksize + SR_BSZ_BASE));
		अगर (lss != 0)
			*ramsize += (1 << ((lss - 1) + SR_BSZ_BASE));
	पूर्ण अन्यथा अणु
		/* length of SRAM Banks increased क्रम corerev greater than 23 */
		अगर (sr->pub.rev >= 23) अणु
			nb = (coreinfo & (SRCI_SRNB_MASK | SRCI_SRNB_MASK_EXT))
				>> SRCI_SRNB_SHIFT;
		पूर्ण अन्यथा अणु
			nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;
		पूर्ण
		क्रम (i = 0; i < nb; i++) अणु
			retent = brcmf_chip_socram_banksize(sr, i, &banksize);
			*ramsize += banksize;
			अगर (retent)
				*srsize += banksize;
		पूर्ण
	पूर्ण

	/* hardcoded save&restore memory sizes */
	चयन (sr->chip->pub.chip) अणु
	हाल BRCM_CC_4334_CHIP_ID:
		अगर (sr->chip->pub.chiprev < 2)
			*srsize = (32 * 1024);
		अवरोध;
	हाल BRCM_CC_43430_CHIP_ID:
		/* assume sr क्रम now as we can not check
		 * firmware sr capability at this poपूर्णांक.
		 */
		*srsize = (64 * 1024);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/** Return the SYS MEM size */
अटल u32 brcmf_chip_sysmem_ramsize(काष्ठा brcmf_core_priv *sysmem)
अणु
	u32 memsize = 0;
	u32 coreinfo;
	u32 idx;
	u32 nb;
	u32 banksize;

	अगर (!brcmf_chip_iscoreup(&sysmem->pub))
		brcmf_chip_resetcore(&sysmem->pub, 0, 0, 0);

	coreinfo = brcmf_chip_core_पढ़ो32(sysmem, SYSMEMREGOFFS(coreinfo));
	nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;

	क्रम (idx = 0; idx < nb; idx++) अणु
		brcmf_chip_socram_banksize(sysmem, idx, &banksize);
		memsize += banksize;
	पूर्ण

	वापस memsize;
पूर्ण

/** Return the TCM-RAM size of the ARMCR4 core. */
अटल u32 brcmf_chip_tcm_ramsize(काष्ठा brcmf_core_priv *cr4)
अणु
	u32 corecap;
	u32 memsize = 0;
	u32 nab;
	u32 nbb;
	u32 totb;
	u32 bxinfo;
	u32 idx;

	corecap = brcmf_chip_core_पढ़ो32(cr4, ARMCR4_CAP);

	nab = (corecap & ARMCR4_TCBANB_MASK) >> ARMCR4_TCBANB_SHIFT;
	nbb = (corecap & ARMCR4_TCBBNB_MASK) >> ARMCR4_TCBBNB_SHIFT;
	totb = nab + nbb;

	क्रम (idx = 0; idx < totb; idx++) अणु
		brcmf_chip_core_ग_लिखो32(cr4, ARMCR4_BANKIDX, idx);
		bxinfo = brcmf_chip_core_पढ़ो32(cr4, ARMCR4_BANKINFO);
		memsize += ((bxinfo & ARMCR4_BSZ_MASK) + 1) * ARMCR4_BSZ_MULT;
	पूर्ण

	वापस memsize;
पूर्ण

अटल u32 brcmf_chip_tcm_rambase(काष्ठा brcmf_chip_priv *ci)
अणु
	चयन (ci->pub.chip) अणु
	हाल BRCM_CC_4345_CHIP_ID:
		वापस 0x198000;
	हाल BRCM_CC_4335_CHIP_ID:
	हाल BRCM_CC_4339_CHIP_ID:
	हाल BRCM_CC_4350_CHIP_ID:
	हाल BRCM_CC_4354_CHIP_ID:
	हाल BRCM_CC_4356_CHIP_ID:
	हाल BRCM_CC_43567_CHIP_ID:
	हाल BRCM_CC_43569_CHIP_ID:
	हाल BRCM_CC_43570_CHIP_ID:
	हाल BRCM_CC_4358_CHIP_ID:
	हाल BRCM_CC_43602_CHIP_ID:
	हाल BRCM_CC_4371_CHIP_ID:
		वापस 0x180000;
	हाल BRCM_CC_43465_CHIP_ID:
	हाल BRCM_CC_43525_CHIP_ID:
	हाल BRCM_CC_4365_CHIP_ID:
	हाल BRCM_CC_4366_CHIP_ID:
	हाल BRCM_CC_43664_CHIP_ID:
	हाल BRCM_CC_43666_CHIP_ID:
		वापस 0x200000;
	हाल BRCM_CC_4359_CHIP_ID:
		वापस (ci->pub.chiprev < 9) ? 0x180000 : 0x160000;
	हाल BRCM_CC_4364_CHIP_ID:
	हाल CY_CC_4373_CHIP_ID:
		वापस 0x160000;
	शेष:
		brcmf_err("unknown chip: %s\n", ci->pub.name);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक brcmf_chip_get_raminfo(काष्ठा brcmf_chip *pub)
अणु
	काष्ठा brcmf_chip_priv *ci = container_of(pub, काष्ठा brcmf_chip_priv,
						  pub);
	काष्ठा brcmf_core_priv *mem_core;
	काष्ठा brcmf_core *mem;

	mem = brcmf_chip_get_core(&ci->pub, BCMA_CORE_ARM_CR4);
	अगर (mem) अणु
		mem_core = container_of(mem, काष्ठा brcmf_core_priv, pub);
		ci->pub.ramsize = brcmf_chip_tcm_ramsize(mem_core);
		ci->pub.rambase = brcmf_chip_tcm_rambase(ci);
		अगर (!ci->pub.rambase) अणु
			brcmf_err("RAM base not provided with ARM CR4 core\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		mem = brcmf_chip_get_core(&ci->pub, BCMA_CORE_SYS_MEM);
		अगर (mem) अणु
			mem_core = container_of(mem, काष्ठा brcmf_core_priv,
						pub);
			ci->pub.ramsize = brcmf_chip_sysmem_ramsize(mem_core);
			ci->pub.rambase = brcmf_chip_tcm_rambase(ci);
			अगर (!ci->pub.rambase) अणु
				brcmf_err("RAM base not provided with ARM CA7 core\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			mem = brcmf_chip_get_core(&ci->pub,
						  BCMA_CORE_INTERNAL_MEM);
			अगर (!mem) अणु
				brcmf_err("No memory cores found\n");
				वापस -ENOMEM;
			पूर्ण
			mem_core = container_of(mem, काष्ठा brcmf_core_priv,
						pub);
			brcmf_chip_socram_ramsize(mem_core, &ci->pub.ramsize,
						  &ci->pub.srsize);
		पूर्ण
	पूर्ण
	brcmf_dbg(INFO, "RAM: base=0x%x size=%d (0x%x) sr=%d (0x%x)\n",
		  ci->pub.rambase, ci->pub.ramsize, ci->pub.ramsize,
		  ci->pub.srsize, ci->pub.srsize);

	अगर (!ci->pub.ramsize) अणु
		brcmf_err("RAM size is undetermined\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ci->pub.ramsize > BRCMF_CHIP_MAX_MEMSIZE) अणु
		brcmf_err("RAM size is incorrect\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 brcmf_chip_dmp_get_desc(काष्ठा brcmf_chip_priv *ci, u32 *eromaddr,
				   u8 *type)
अणु
	u32 val;

	/* पढ़ो next descriptor */
	val = ci->ops->पढ़ो32(ci->ctx, *eromaddr);
	*eromaddr += 4;

	अगर (!type)
		वापस val;

	/* determine descriptor type */
	*type = (val & DMP_DESC_TYPE_MSK);
	अगर ((*type & ~DMP_DESC_ADDRSIZE_GT32) == DMP_DESC_ADDRESS)
		*type = DMP_DESC_ADDRESS;

	वापस val;
पूर्ण

अटल पूर्णांक brcmf_chip_dmp_get_regaddr(काष्ठा brcmf_chip_priv *ci, u32 *eromaddr,
				      u32 *regbase, u32 *wrapbase)
अणु
	u8 desc;
	u32 val, szdesc;
	u8 stype, sztype, wraptype;

	*regbase = 0;
	*wrapbase = 0;

	val = brcmf_chip_dmp_get_desc(ci, eromaddr, &desc);
	अगर (desc == DMP_DESC_MASTER_PORT) अणु
		wraptype = DMP_SLAVE_TYPE_MWRAP;
	पूर्ण अन्यथा अगर (desc == DMP_DESC_ADDRESS) अणु
		/* revert erom address */
		*eromaddr -= 4;
		wraptype = DMP_SLAVE_TYPE_SWRAP;
	पूर्ण अन्यथा अणु
		*eromaddr -= 4;
		वापस -EILSEQ;
	पूर्ण

	करो अणु
		/* locate address descriptor */
		करो अणु
			val = brcmf_chip_dmp_get_desc(ci, eromaddr, &desc);
			/* unexpected table end */
			अगर (desc == DMP_DESC_EOT) अणु
				*eromaddr -= 4;
				वापस -EFAULT;
			पूर्ण
		पूर्ण जबतक (desc != DMP_DESC_ADDRESS &&
			 desc != DMP_DESC_COMPONENT);

		/* stop अगर we crossed current component border */
		अगर (desc == DMP_DESC_COMPONENT) अणु
			*eromaddr -= 4;
			वापस 0;
		पूर्ण

		/* skip upper 32-bit address descriptor */
		अगर (val & DMP_DESC_ADDRSIZE_GT32)
			brcmf_chip_dmp_get_desc(ci, eromaddr, शून्य);

		sztype = (val & DMP_SLAVE_SIZE_TYPE) >> DMP_SLAVE_SIZE_TYPE_S;

		/* next size descriptor can be skipped */
		अगर (sztype == DMP_SLAVE_SIZE_DESC) अणु
			szdesc = brcmf_chip_dmp_get_desc(ci, eromaddr, शून्य);
			/* skip upper size descriptor अगर present */
			अगर (szdesc & DMP_DESC_ADDRSIZE_GT32)
				brcmf_chip_dmp_get_desc(ci, eromaddr, शून्य);
		पूर्ण

		/* look क्रम 4K or 8K रेजिस्टर regions */
		अगर (sztype != DMP_SLAVE_SIZE_4K &&
		    sztype != DMP_SLAVE_SIZE_8K)
			जारी;

		stype = (val & DMP_SLAVE_TYPE) >> DMP_SLAVE_TYPE_S;

		/* only regular slave and wrapper */
		अगर (*regbase == 0 && stype == DMP_SLAVE_TYPE_SLAVE)
			*regbase = val & DMP_SLAVE_ADDR_BASE;
		अगर (*wrapbase == 0 && stype == wraptype)
			*wrapbase = val & DMP_SLAVE_ADDR_BASE;
	पूर्ण जबतक (*regbase == 0 || *wrapbase == 0);

	वापस 0;
पूर्ण

अटल
पूर्णांक brcmf_chip_dmp_erom_scan(काष्ठा brcmf_chip_priv *ci)
अणु
	काष्ठा brcmf_core *core;
	u32 eromaddr;
	u8 desc_type = 0;
	u32 val;
	u16 id;
	u8 nmw, nsw, rev;
	u32 base, wrap;
	पूर्णांक err;

	eromaddr = ci->ops->पढ़ो32(ci->ctx, CORE_CC_REG(SI_ENUM_BASE, eromptr));

	जबतक (desc_type != DMP_DESC_EOT) अणु
		val = brcmf_chip_dmp_get_desc(ci, &eromaddr, &desc_type);
		अगर (!(val & DMP_DESC_VALID))
			जारी;

		अगर (desc_type == DMP_DESC_EMPTY)
			जारी;

		/* need a component descriptor */
		अगर (desc_type != DMP_DESC_COMPONENT)
			जारी;

		id = (val & DMP_COMP_PARTNUM) >> DMP_COMP_PARTNUM_S;

		/* next descriptor must be component as well */
		val = brcmf_chip_dmp_get_desc(ci, &eromaddr, &desc_type);
		अगर (WARN_ON((val & DMP_DESC_TYPE_MSK) != DMP_DESC_COMPONENT))
			वापस -EFAULT;

		/* only look at cores with master port(s) */
		nmw = (val & DMP_COMP_NUM_MWRAP) >> DMP_COMP_NUM_MWRAP_S;
		nsw = (val & DMP_COMP_NUM_SWRAP) >> DMP_COMP_NUM_SWRAP_S;
		rev = (val & DMP_COMP_REVISION) >> DMP_COMP_REVISION_S;

		/* need core with ports */
		अगर (nmw + nsw == 0 &&
		    id != BCMA_CORE_PMU &&
		    id != BCMA_CORE_GCI)
			जारी;

		/* try to obtain रेजिस्टर address info */
		err = brcmf_chip_dmp_get_regaddr(ci, &eromaddr, &base, &wrap);
		अगर (err)
			जारी;

		/* finally a core to be added */
		core = brcmf_chip_add_core(ci, id, base, wrap);
		अगर (IS_ERR(core))
			वापस PTR_ERR(core);

		core->rev = rev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_chip_recognition(काष्ठा brcmf_chip_priv *ci)
अणु
	काष्ठा brcmf_core *core;
	u32 regdata;
	u32 socitype;
	पूर्णांक ret;

	/* Get CC core rev
	 * Chipid is assume to be at offset 0 from SI_ENUM_BASE
	 * For dअगरferent chiptypes or old sdio hosts w/o chipcommon,
	 * other ways of recognition should be added here.
	 */
	regdata = ci->ops->पढ़ो32(ci->ctx, CORE_CC_REG(SI_ENUM_BASE, chipid));
	ci->pub.chip = regdata & CID_ID_MASK;
	ci->pub.chiprev = (regdata & CID_REV_MASK) >> CID_REV_SHIFT;
	socitype = (regdata & CID_TYPE_MASK) >> CID_TYPE_SHIFT;

	brcmf_chip_name(ci->pub.chip, ci->pub.chiprev,
			ci->pub.name, माप(ci->pub.name));
	brcmf_dbg(INFO, "found %s chip: %s\n",
		  socitype == SOCI_SB ? "SB" : "AXI", ci->pub.name);

	अगर (socitype == SOCI_SB) अणु
		अगर (ci->pub.chip != BRCM_CC_4329_CHIP_ID) अणु
			brcmf_err("SB chip is not supported\n");
			वापस -ENODEV;
		पूर्ण
		ci->iscoreup = brcmf_chip_sb_iscoreup;
		ci->coredisable = brcmf_chip_sb_coredisable;
		ci->resetcore = brcmf_chip_sb_resetcore;

		core = brcmf_chip_add_core(ci, BCMA_CORE_CHIPCOMMON,
					   SI_ENUM_BASE, 0);
		brcmf_chip_sb_corerev(ci, core);
		core = brcmf_chip_add_core(ci, BCMA_CORE_SDIO_DEV,
					   BCM4329_CORE_BUS_BASE, 0);
		brcmf_chip_sb_corerev(ci, core);
		core = brcmf_chip_add_core(ci, BCMA_CORE_INTERNAL_MEM,
					   BCM4329_CORE_SOCRAM_BASE, 0);
		brcmf_chip_sb_corerev(ci, core);
		core = brcmf_chip_add_core(ci, BCMA_CORE_ARM_CM3,
					   BCM4329_CORE_ARM_BASE, 0);
		brcmf_chip_sb_corerev(ci, core);

		core = brcmf_chip_add_core(ci, BCMA_CORE_80211, 0x18001000, 0);
		brcmf_chip_sb_corerev(ci, core);
	पूर्ण अन्यथा अगर (socitype == SOCI_AI) अणु
		ci->iscoreup = brcmf_chip_ai_iscoreup;
		ci->coredisable = brcmf_chip_ai_coredisable;
		ci->resetcore = brcmf_chip_ai_resetcore;

		brcmf_chip_dmp_erom_scan(ci);
	पूर्ण अन्यथा अणु
		brcmf_err("chip backplane type %u is not supported\n",
			  socitype);
		वापस -ENODEV;
	पूर्ण

	ret = brcmf_chip_cores_check(ci);
	अगर (ret)
		वापस ret;

	/* assure chip is passive क्रम core access */
	brcmf_chip_set_passive(&ci->pub);

	/* Call bus specअगरic reset function now. Cores have been determined
	 * but further access may require a chip specअगरic reset at this poपूर्णांक.
	 */
	अगर (ci->ops->reset) अणु
		ci->ops->reset(ci->ctx, &ci->pub);
		brcmf_chip_set_passive(&ci->pub);
	पूर्ण

	वापस brcmf_chip_get_raminfo(&ci->pub);
पूर्ण

अटल व्योम brcmf_chip_disable_arm(काष्ठा brcmf_chip_priv *chip, u16 id)
अणु
	काष्ठा brcmf_core *core;
	काष्ठा brcmf_core_priv *cpu;
	u32 val;


	core = brcmf_chip_get_core(&chip->pub, id);
	अगर (!core)
		वापस;

	चयन (id) अणु
	हाल BCMA_CORE_ARM_CM3:
		brcmf_chip_coredisable(core, 0, 0);
		अवरोध;
	हाल BCMA_CORE_ARM_CR4:
	हाल BCMA_CORE_ARM_CA7:
		cpu = container_of(core, काष्ठा brcmf_core_priv, pub);

		/* clear all IOCTL bits except HALT bit */
		val = chip->ops->पढ़ो32(chip->ctx, cpu->wrapbase + BCMA_IOCTL);
		val &= ARMCR4_BCMA_IOCTL_CPUHALT;
		brcmf_chip_resetcore(core, val, ARMCR4_BCMA_IOCTL_CPUHALT,
				     ARMCR4_BCMA_IOCTL_CPUHALT);
		अवरोध;
	शेष:
		brcmf_err("unknown id: %u\n", id);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_chip_setup(काष्ठा brcmf_chip_priv *chip)
अणु
	काष्ठा brcmf_chip *pub;
	काष्ठा brcmf_core_priv *cc;
	काष्ठा brcmf_core *pmu;
	u32 base;
	u32 val;
	पूर्णांक ret = 0;

	pub = &chip->pub;
	cc = list_first_entry(&chip->cores, काष्ठा brcmf_core_priv, list);
	base = cc->pub.base;

	/* get chipcommon capabilites */
	pub->cc_caps = chip->ops->पढ़ो32(chip->ctx,
					 CORE_CC_REG(base, capabilities));
	pub->cc_caps_ext = chip->ops->पढ़ो32(chip->ctx,
					     CORE_CC_REG(base,
							 capabilities_ext));

	/* get pmu caps & rev */
	pmu = brcmf_chip_get_pmu(pub); /* after पढ़ोing cc_caps_ext */
	अगर (pub->cc_caps & CC_CAP_PMU) अणु
		val = chip->ops->पढ़ो32(chip->ctx,
					CORE_CC_REG(pmu->base, pmucapabilities));
		pub->pmurev = val & PCAP_REV_MASK;
		pub->pmucaps = val;
	पूर्ण

	brcmf_dbg(INFO, "ccrev=%d, pmurev=%d, pmucaps=0x%x\n",
		  cc->pub.rev, pub->pmurev, pub->pmucaps);

	/* execute bus core specअगरic setup */
	अगर (chip->ops->setup)
		ret = chip->ops->setup(chip->ctx, pub);

	वापस ret;
पूर्ण

काष्ठा brcmf_chip *brcmf_chip_attach(व्योम *ctx,
				     स्थिर काष्ठा brcmf_buscore_ops *ops)
अणु
	काष्ठा brcmf_chip_priv *chip;
	पूर्णांक err = 0;

	अगर (WARN_ON(!ops->पढ़ो32))
		err = -EINVAL;
	अगर (WARN_ON(!ops->ग_लिखो32))
		err = -EINVAL;
	अगर (WARN_ON(!ops->prepare))
		err = -EINVAL;
	अगर (WARN_ON(!ops->activate))
		err = -EINVAL;
	अगर (err < 0)
		वापस ERR_PTR(-EINVAL);

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&chip->cores);
	chip->num_cores = 0;
	chip->ops = ops;
	chip->ctx = ctx;

	err = ops->prepare(ctx);
	अगर (err < 0)
		जाओ fail;

	err = brcmf_chip_recognition(chip);
	अगर (err < 0)
		जाओ fail;

	err = brcmf_chip_setup(chip);
	अगर (err < 0)
		जाओ fail;

	वापस &chip->pub;

fail:
	brcmf_chip_detach(&chip->pub);
	वापस ERR_PTR(err);
पूर्ण

व्योम brcmf_chip_detach(काष्ठा brcmf_chip *pub)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core_priv *core;
	काष्ठा brcmf_core_priv *पंचांगp;

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	list_क्रम_each_entry_safe(core, पंचांगp, &chip->cores, list) अणु
		list_del(&core->list);
		kमुक्त(core);
	पूर्ण
	kमुक्त(chip);
पूर्ण

काष्ठा brcmf_core *brcmf_chip_get_d11core(काष्ठा brcmf_chip *pub, u8 unit)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core_priv *core;

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	list_क्रम_each_entry(core, &chip->cores, list) अणु
		अगर (core->pub.id == BCMA_CORE_80211) अणु
			अगर (unit-- == 0)
				वापस &core->pub;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा brcmf_core *brcmf_chip_get_core(काष्ठा brcmf_chip *pub, u16 coreid)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core_priv *core;

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	list_क्रम_each_entry(core, &chip->cores, list)
		अगर (core->pub.id == coreid)
			वापस &core->pub;

	वापस शून्य;
पूर्ण

काष्ठा brcmf_core *brcmf_chip_get_chipcommon(काष्ठा brcmf_chip *pub)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core_priv *cc;

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	cc = list_first_entry(&chip->cores, काष्ठा brcmf_core_priv, list);
	अगर (WARN_ON(!cc || cc->pub.id != BCMA_CORE_CHIPCOMMON))
		वापस brcmf_chip_get_core(pub, BCMA_CORE_CHIPCOMMON);
	वापस &cc->pub;
पूर्ण

काष्ठा brcmf_core *brcmf_chip_get_pmu(काष्ठा brcmf_chip *pub)
अणु
	काष्ठा brcmf_core *cc = brcmf_chip_get_chipcommon(pub);
	काष्ठा brcmf_core *pmu;

	/* See अगर there is separated PMU core available */
	अगर (cc->rev >= 35 &&
	    pub->cc_caps_ext & BCMA_CC_CAP_EXT_AOB_PRESENT) अणु
		pmu = brcmf_chip_get_core(pub, BCMA_CORE_PMU);
		अगर (pmu)
			वापस pmu;
	पूर्ण

	/* Fallback to ChipCommon core क्रम older hardware */
	वापस cc;
पूर्ण

bool brcmf_chip_iscoreup(काष्ठा brcmf_core *pub)
अणु
	काष्ठा brcmf_core_priv *core;

	core = container_of(pub, काष्ठा brcmf_core_priv, pub);
	वापस core->chip->iscoreup(core);
पूर्ण

व्योम brcmf_chip_coredisable(काष्ठा brcmf_core *pub, u32 prereset, u32 reset)
अणु
	काष्ठा brcmf_core_priv *core;

	core = container_of(pub, काष्ठा brcmf_core_priv, pub);
	core->chip->coredisable(core, prereset, reset);
पूर्ण

व्योम brcmf_chip_resetcore(काष्ठा brcmf_core *pub, u32 prereset, u32 reset,
			  u32 postreset)
अणु
	काष्ठा brcmf_core_priv *core;

	core = container_of(pub, काष्ठा brcmf_core_priv, pub);
	core->chip->resetcore(core, prereset, reset, postreset);
पूर्ण

अटल व्योम
brcmf_chip_cm3_set_passive(काष्ठा brcmf_chip_priv *chip)
अणु
	काष्ठा brcmf_core *core;
	काष्ठा brcmf_core_priv *sr;

	brcmf_chip_disable_arm(chip, BCMA_CORE_ARM_CM3);
	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_80211);
	brcmf_chip_resetcore(core, D11_BCMA_IOCTL_PHYRESET |
				   D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN);
	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_INTERNAL_MEM);
	brcmf_chip_resetcore(core, 0, 0, 0);

	/* disable bank #3 remap क्रम this device */
	अगर (chip->pub.chip == BRCM_CC_43430_CHIP_ID) अणु
		sr = container_of(core, काष्ठा brcmf_core_priv, pub);
		brcmf_chip_core_ग_लिखो32(sr, SOCRAMREGOFFS(bankidx), 3);
		brcmf_chip_core_ग_लिखो32(sr, SOCRAMREGOFFS(bankpda), 0);
	पूर्ण
पूर्ण

अटल bool brcmf_chip_cm3_set_active(काष्ठा brcmf_chip_priv *chip)
अणु
	काष्ठा brcmf_core *core;

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_INTERNAL_MEM);
	अगर (!brcmf_chip_iscoreup(core)) अणु
		brcmf_err("SOCRAM core is down after reset?\n");
		वापस false;
	पूर्ण

	chip->ops->activate(chip->ctx, &chip->pub, 0);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CM3);
	brcmf_chip_resetcore(core, 0, 0, 0);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम
brcmf_chip_cr4_set_passive(काष्ठा brcmf_chip_priv *chip)
अणु
	काष्ठा brcmf_core *core;

	brcmf_chip_disable_arm(chip, BCMA_CORE_ARM_CR4);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_80211);
	brcmf_chip_resetcore(core, D11_BCMA_IOCTL_PHYRESET |
				   D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN);
पूर्ण

अटल bool brcmf_chip_cr4_set_active(काष्ठा brcmf_chip_priv *chip, u32 rstvec)
अणु
	काष्ठा brcmf_core *core;

	chip->ops->activate(chip->ctx, &chip->pub, rstvec);

	/* restore ARM */
	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CR4);
	brcmf_chip_resetcore(core, ARMCR4_BCMA_IOCTL_CPUHALT, 0, 0);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम
brcmf_chip_ca7_set_passive(काष्ठा brcmf_chip_priv *chip)
अणु
	काष्ठा brcmf_core *core;

	brcmf_chip_disable_arm(chip, BCMA_CORE_ARM_CA7);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_80211);
	brcmf_chip_resetcore(core, D11_BCMA_IOCTL_PHYRESET |
				   D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN);
पूर्ण

अटल bool brcmf_chip_ca7_set_active(काष्ठा brcmf_chip_priv *chip, u32 rstvec)
अणु
	काष्ठा brcmf_core *core;

	chip->ops->activate(chip->ctx, &chip->pub, rstvec);

	/* restore ARM */
	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CA7);
	brcmf_chip_resetcore(core, ARMCR4_BCMA_IOCTL_CPUHALT, 0, 0);

	वापस true;
पूर्ण

व्योम brcmf_chip_set_passive(काष्ठा brcmf_chip *pub)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core *arm;

	brcmf_dbg(TRACE, "Enter\n");

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CR4);
	अगर (arm) अणु
		brcmf_chip_cr4_set_passive(chip);
		वापस;
	पूर्ण
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CA7);
	अगर (arm) अणु
		brcmf_chip_ca7_set_passive(chip);
		वापस;
	पूर्ण
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CM3);
	अगर (arm) अणु
		brcmf_chip_cm3_set_passive(chip);
		वापस;
	पूर्ण
पूर्ण

bool brcmf_chip_set_active(काष्ठा brcmf_chip *pub, u32 rstvec)
अणु
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core *arm;

	brcmf_dbg(TRACE, "Enter\n");

	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CR4);
	अगर (arm)
		वापस brcmf_chip_cr4_set_active(chip, rstvec);
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CA7);
	अगर (arm)
		वापस brcmf_chip_ca7_set_active(chip, rstvec);
	arm = brcmf_chip_get_core(pub, BCMA_CORE_ARM_CM3);
	अगर (arm)
		वापस brcmf_chip_cm3_set_active(chip);

	वापस false;
पूर्ण

bool brcmf_chip_sr_capable(काष्ठा brcmf_chip *pub)
अणु
	u32 base, addr, reg, pmu_cc3_mask = ~0;
	काष्ठा brcmf_chip_priv *chip;
	काष्ठा brcmf_core *pmu = brcmf_chip_get_pmu(pub);

	brcmf_dbg(TRACE, "Enter\n");

	/* old chips with PMU version less than 17 करोn't support save restore */
	अगर (pub->pmurev < 17)
		वापस false;

	base = brcmf_chip_get_chipcommon(pub)->base;
	chip = container_of(pub, काष्ठा brcmf_chip_priv, pub);

	चयन (pub->chip) अणु
	हाल BRCM_CC_4354_CHIP_ID:
	हाल BRCM_CC_4356_CHIP_ID:
	हाल BRCM_CC_4345_CHIP_ID:
		/* explicitly check SR engine enable bit */
		pmu_cc3_mask = BIT(2);
		fallthrough;
	हाल BRCM_CC_43241_CHIP_ID:
	हाल BRCM_CC_4335_CHIP_ID:
	हाल BRCM_CC_4339_CHIP_ID:
		/* पढ़ो PMU chipcontrol रेजिस्टर 3 */
		addr = CORE_CC_REG(pmu->base, chipcontrol_addr);
		chip->ops->ग_लिखो32(chip->ctx, addr, 3);
		addr = CORE_CC_REG(pmu->base, chipcontrol_data);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		वापस (reg & pmu_cc3_mask) != 0;
	हाल BRCM_CC_43430_CHIP_ID:
		addr = CORE_CC_REG(base, sr_control1);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		वापस reg != 0;
	हाल CY_CC_4373_CHIP_ID:
		/* explicitly check SR engine enable bit */
		addr = CORE_CC_REG(base, sr_control0);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		वापस (reg & CC_SR_CTL0_ENABLE_MASK) != 0;
	हाल BRCM_CC_4359_CHIP_ID:
	हाल CY_CC_43012_CHIP_ID:
		addr = CORE_CC_REG(pmu->base, retention_ctl);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		वापस (reg & (PMU_RCTL_MACPHY_DISABLE_MASK |
			       PMU_RCTL_LOGIC_DISABLE_MASK)) == 0;
	शेष:
		addr = CORE_CC_REG(pmu->base, pmucapabilities_ext);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		अगर ((reg & PCAPEXT_SR_SUPPORTED_MASK) == 0)
			वापस false;

		addr = CORE_CC_REG(pmu->base, retention_ctl);
		reg = chip->ops->पढ़ो32(chip->ctx, addr);
		वापस (reg & (PMU_RCTL_MACPHY_DISABLE_MASK |
			       PMU_RCTL_LOGIC_DISABLE_MASK)) == 0;
	पूर्ण
पूर्ण
