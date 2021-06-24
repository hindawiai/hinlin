<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPMC support functions
 *
 * Copyright (C) 2005-2006 Nokia Corporation
 *
 * Author: Juha Yrjola
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h> /* GPIO descriptor क्रमागत */
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/omap-gpmc.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>

#समावेश <linux/platक्रमm_data/mtd-nand-omap2.h>

#घोषणा	DEVICE_NAME		"omap-gpmc"

/* GPMC रेजिस्टर offsets */
#घोषणा GPMC_REVISION		0x00
#घोषणा GPMC_SYSCONFIG		0x10
#घोषणा GPMC_SYSSTATUS		0x14
#घोषणा GPMC_IRQSTATUS		0x18
#घोषणा GPMC_IRQENABLE		0x1c
#घोषणा GPMC_TIMEOUT_CONTROL	0x40
#घोषणा GPMC_ERR_ADDRESS	0x44
#घोषणा GPMC_ERR_TYPE		0x48
#घोषणा GPMC_CONFIG		0x50
#घोषणा GPMC_STATUS		0x54
#घोषणा GPMC_PREFETCH_CONFIG1	0x1e0
#घोषणा GPMC_PREFETCH_CONFIG2	0x1e4
#घोषणा GPMC_PREFETCH_CONTROL	0x1ec
#घोषणा GPMC_PREFETCH_STATUS	0x1f0
#घोषणा GPMC_ECC_CONFIG		0x1f4
#घोषणा GPMC_ECC_CONTROL	0x1f8
#घोषणा GPMC_ECC_SIZE_CONFIG	0x1fc
#घोषणा GPMC_ECC1_RESULT        0x200
#घोषणा GPMC_ECC_BCH_RESULT_0   0x240   /* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_1	0x244	/* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_2	0x248	/* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_3	0x24c	/* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_4	0x300	/* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_5	0x304	/* not available on OMAP2 */
#घोषणा	GPMC_ECC_BCH_RESULT_6	0x308	/* not available on OMAP2 */

/* GPMC ECC control settings */
#घोषणा GPMC_ECC_CTRL_ECCCLEAR		0x100
#घोषणा GPMC_ECC_CTRL_ECCDISABLE	0x000
#घोषणा GPMC_ECC_CTRL_ECCREG1		0x001
#घोषणा GPMC_ECC_CTRL_ECCREG2		0x002
#घोषणा GPMC_ECC_CTRL_ECCREG3		0x003
#घोषणा GPMC_ECC_CTRL_ECCREG4		0x004
#घोषणा GPMC_ECC_CTRL_ECCREG5		0x005
#घोषणा GPMC_ECC_CTRL_ECCREG6		0x006
#घोषणा GPMC_ECC_CTRL_ECCREG7		0x007
#घोषणा GPMC_ECC_CTRL_ECCREG8		0x008
#घोषणा GPMC_ECC_CTRL_ECCREG9		0x009

#घोषणा GPMC_CONFIG_LIMITEDADDRESS		BIT(1)

#घोषणा GPMC_STATUS_EMPTYWRITEBUFFERSTATUS	BIT(0)

#घोषणा	GPMC_CONFIG2_CSEXTRADELAY		BIT(7)
#घोषणा	GPMC_CONFIG3_ADVEXTRADELAY		BIT(7)
#घोषणा	GPMC_CONFIG4_OEEXTRADELAY		BIT(7)
#घोषणा	GPMC_CONFIG4_WEEXTRADELAY		BIT(23)
#घोषणा	GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN	BIT(6)
#घोषणा	GPMC_CONFIG6_CYCLE2CYCLESAMECSEN	BIT(7)

#घोषणा GPMC_CS0_OFFSET		0x60
#घोषणा GPMC_CS_SIZE		0x30
#घोषणा	GPMC_BCH_SIZE		0x10

/*
 * The first 1MB of GPMC address space is typically mapped to
 * the पूर्णांकernal ROM. Never allocate the first page, to
 * facilitate bug detection; even अगर we didn't boot from ROM.
 * As GPMC minimum partition size is 16MB we can only start from
 * there.
 */
#घोषणा GPMC_MEM_START		0x1000000
#घोषणा GPMC_MEM_END		0x3FFFFFFF

#घोषणा GPMC_CHUNK_SHIFT	24		/* 16 MB */
#घोषणा GPMC_SECTION_SHIFT	28		/* 128 MB */

#घोषणा CS_NUM_SHIFT		24
#घोषणा ENABLE_PREFETCH		(0x1 << 7)
#घोषणा DMA_MPU_MODE		2

#घोषणा	GPMC_REVISION_MAJOR(l)		(((l) >> 4) & 0xf)
#घोषणा	GPMC_REVISION_MINOR(l)		((l) & 0xf)

#घोषणा	GPMC_HAS_WR_ACCESS		0x1
#घोषणा	GPMC_HAS_WR_DATA_MUX_BUS	0x2
#घोषणा	GPMC_HAS_MUX_AAD		0x4

#घोषणा GPMC_NR_WAITPINS		4

#घोषणा GPMC_CS_CONFIG1		0x00
#घोषणा GPMC_CS_CONFIG2		0x04
#घोषणा GPMC_CS_CONFIG3		0x08
#घोषणा GPMC_CS_CONFIG4		0x0c
#घोषणा GPMC_CS_CONFIG5		0x10
#घोषणा GPMC_CS_CONFIG6		0x14
#घोषणा GPMC_CS_CONFIG7		0x18
#घोषणा GPMC_CS_न_अंकD_COMMAND	0x1c
#घोषणा GPMC_CS_न_अंकD_ADDRESS	0x20
#घोषणा GPMC_CS_न_अंकD_DATA	0x24

/* Control Commands */
#घोषणा GPMC_CONFIG_RDY_BSY	0x00000001
#घोषणा GPMC_CONFIG_DEV_SIZE	0x00000002
#घोषणा GPMC_CONFIG_DEV_TYPE	0x00000003

#घोषणा GPMC_CONFIG1_WRAPBURST_SUPP     (1 << 31)
#घोषणा GPMC_CONFIG1_READMULTIPLE_SUPP  (1 << 30)
#घोषणा GPMC_CONFIG1_READTYPE_ASYNC     (0 << 29)
#घोषणा GPMC_CONFIG1_READTYPE_SYNC      (1 << 29)
#घोषणा GPMC_CONFIG1_WRITEMULTIPLE_SUPP (1 << 28)
#घोषणा GPMC_CONFIG1_WRITETYPE_ASYNC    (0 << 27)
#घोषणा GPMC_CONFIG1_WRITETYPE_SYNC     (1 << 27)
#घोषणा GPMC_CONFIG1_CLKACTIVATIONTIME(val) (((val) & 3) << 25)
/** CLKACTIVATIONTIME Max Ticks */
#घोषणा GPMC_CONFIG1_CLKACTIVATIONTIME_MAX 2
#घोषणा GPMC_CONFIG1_PAGE_LEN(val)      (((val) & 3) << 23)
/** ATTACHEDDEVICEPAGELENGTH Max Value */
#घोषणा GPMC_CONFIG1_ATTACHEDDEVICEPAGELENGTH_MAX 2
#घोषणा GPMC_CONFIG1_WAIT_READ_MON      (1 << 22)
#घोषणा GPMC_CONFIG1_WAIT_WRITE_MON     (1 << 21)
#घोषणा GPMC_CONFIG1_WAIT_MON_TIME(val) (((val) & 3) << 18)
/** WAITMONITORINGTIME Max Ticks */
#घोषणा GPMC_CONFIG1_WAITMONITORINGTIME_MAX  2
#घोषणा GPMC_CONFIG1_WAIT_PIN_SEL(val)  (((val) & 3) << 16)
#घोषणा GPMC_CONFIG1_DEVICESIZE(val)    (((val) & 3) << 12)
#घोषणा GPMC_CONFIG1_DEVICESIZE_16      GPMC_CONFIG1_DEVICESIZE(1)
/** DEVICESIZE Max Value */
#घोषणा GPMC_CONFIG1_DEVICESIZE_MAX     1
#घोषणा GPMC_CONFIG1_DEVICETYPE(val)    (((val) & 3) << 10)
#घोषणा GPMC_CONFIG1_DEVICETYPE_NOR     GPMC_CONFIG1_DEVICETYPE(0)
#घोषणा GPMC_CONFIG1_MUXTYPE(val)       (((val) & 3) << 8)
#घोषणा GPMC_CONFIG1_TIME_PARA_GRAN     (1 << 4)
#घोषणा GPMC_CONFIG1_FCLK_DIV(val)      ((val) & 3)
#घोषणा GPMC_CONFIG1_FCLK_DIV2          (GPMC_CONFIG1_FCLK_DIV(1))
#घोषणा GPMC_CONFIG1_FCLK_DIV3          (GPMC_CONFIG1_FCLK_DIV(2))
#घोषणा GPMC_CONFIG1_FCLK_DIV4          (GPMC_CONFIG1_FCLK_DIV(3))
#घोषणा GPMC_CONFIG7_CSVALID		(1 << 6)

#घोषणा GPMC_CONFIG7_BASEADDRESS_MASK	0x3f
#घोषणा GPMC_CONFIG7_CSVALID_MASK	BIT(6)
#घोषणा GPMC_CONFIG7_MASKADDRESS_OFFSET	8
#घोषणा GPMC_CONFIG7_MASKADDRESS_MASK	(0xf << GPMC_CONFIG7_MASKADDRESS_OFFSET)
/* All CONFIG7 bits except reserved bits */
#घोषणा GPMC_CONFIG7_MASK		(GPMC_CONFIG7_BASEADDRESS_MASK | \
					 GPMC_CONFIG7_CSVALID_MASK |     \
					 GPMC_CONFIG7_MASKADDRESS_MASK)

#घोषणा GPMC_DEVICETYPE_NOR		0
#घोषणा GPMC_DEVICETYPE_न_अंकD		2
#घोषणा GPMC_CONFIG_WRITEPROTECT	0x00000010
#घोषणा WR_RD_PIN_MONITORING		0x00600000

/* ECC commands */
#घोषणा GPMC_ECC_READ		0 /* Reset Hardware ECC क्रम पढ़ो */
#घोषणा GPMC_ECC_WRITE		1 /* Reset Hardware ECC क्रम ग_लिखो */
#घोषणा GPMC_ECC_READSYN	2 /* Reset beक्रमe syndrom is पढ़ो back */

#घोषणा	GPMC_NR_न_अंकD_IRQS	2 /* number of न_अंकD specअगरic IRQs */

क्रमागत gpmc_clk_करोमुख्य अणु
	GPMC_CD_FCLK,
	GPMC_CD_CLK
पूर्ण;

काष्ठा gpmc_cs_data अणु
	स्थिर अक्षर *name;

#घोषणा GPMC_CS_RESERVED	(1 << 0)
	u32 flags;

	काष्ठा resource mem;
पूर्ण;

/* Structure to save gpmc cs context */
काष्ठा gpmc_cs_config अणु
	u32 config1;
	u32 config2;
	u32 config3;
	u32 config4;
	u32 config5;
	u32 config6;
	u32 config7;
	पूर्णांक is_valid;
पूर्ण;

/*
 * Structure to save/restore gpmc context
 * to support core off on OMAP3
 */
काष्ठा omap3_gpmc_regs अणु
	u32 sysconfig;
	u32 irqenable;
	u32 समयout_ctrl;
	u32 config;
	u32 prefetch_config1;
	u32 prefetch_config2;
	u32 prefetch_control;
	काष्ठा gpmc_cs_config cs_context[GPMC_CS_NUM];
पूर्ण;

काष्ठा gpmc_device अणु
	काष्ठा device *dev;
	पूर्णांक irq;
	काष्ठा irq_chip irq_chip;
	काष्ठा gpio_chip gpio_chip;
	पूर्णांक nirqs;
पूर्ण;

अटल काष्ठा irq_करोमुख्य *gpmc_irq_करोमुख्य;

अटल काष्ठा resource	gpmc_mem_root;
अटल काष्ठा gpmc_cs_data gpmc_cs[GPMC_CS_NUM];
अटल DEFINE_SPINLOCK(gpmc_mem_lock);
/* Define chip-selects as reserved by शेष until probe completes */
अटल अचिन्हित पूर्णांक gpmc_cs_num = GPMC_CS_NUM;
अटल अचिन्हित पूर्णांक gpmc_nr_रुकोpins;
अटल अचिन्हित पूर्णांक gpmc_capability;
अटल व्योम __iomem *gpmc_base;

अटल काष्ठा clk *gpmc_l3_clk;

अटल irqवापस_t gpmc_handle_irq(पूर्णांक irq, व्योम *dev);

अटल व्योम gpmc_ग_लिखो_reg(पूर्णांक idx, u32 val)
अणु
	ग_लिखोl_relaxed(val, gpmc_base + idx);
पूर्ण

अटल u32 gpmc_पढ़ो_reg(पूर्णांक idx)
अणु
	वापस पढ़ोl_relaxed(gpmc_base + idx);
पूर्ण

व्योम gpmc_cs_ग_लिखो_reg(पूर्णांक cs, पूर्णांक idx, u32 val)
अणु
	व्योम __iomem *reg_addr;

	reg_addr = gpmc_base + GPMC_CS0_OFFSET + (cs * GPMC_CS_SIZE) + idx;
	ग_लिखोl_relaxed(val, reg_addr);
पूर्ण

अटल u32 gpmc_cs_पढ़ो_reg(पूर्णांक cs, पूर्णांक idx)
अणु
	व्योम __iomem *reg_addr;

	reg_addr = gpmc_base + GPMC_CS0_OFFSET + (cs * GPMC_CS_SIZE) + idx;
	वापस पढ़ोl_relaxed(reg_addr);
पूर्ण

/* TODO: Add support क्रम gpmc_fck to घड़ी framework and use it */
अटल अचिन्हित दीर्घ gpmc_get_fclk_period(व्योम)
अणु
	अचिन्हित दीर्घ rate = clk_get_rate(gpmc_l3_clk);

	rate /= 1000;
	rate = 1000000000 / rate;	/* In picoseconds */

	वापस rate;
पूर्ण

/**
 * gpmc_get_clk_period - get period of selected घड़ी करोमुख्य in ps
 * @cs: Chip Select Region.
 * @cd: Clock Doमुख्य.
 *
 * GPMC_CS_CONFIG1 GPMCFCLKDIVIDER क्रम cs has to be setup
 * prior to calling this function with GPMC_CD_CLK.
 */
अटल अचिन्हित दीर्घ gpmc_get_clk_period(पूर्णांक cs, क्रमागत gpmc_clk_करोमुख्य cd)
अणु
	अचिन्हित दीर्घ tick_ps = gpmc_get_fclk_period();
	u32 l;
	पूर्णांक भाग;

	चयन (cd) अणु
	हाल GPMC_CD_CLK:
		/* get current clk भागider */
		l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG1);
		भाग = (l & 0x03) + 1;
		/* get GPMC_CLK period */
		tick_ps *= भाग;
		अवरोध;
	हाल GPMC_CD_FCLK:
	शेष:
		अवरोध;
	पूर्ण

	वापस tick_ps;
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_ns_to_clk_ticks(अचिन्हित पूर्णांक समय_ns, पूर्णांक cs,
					 क्रमागत gpmc_clk_करोमुख्य cd)
अणु
	अचिन्हित दीर्घ tick_ps;

	/* Calculate in picosecs to yield more exact results */
	tick_ps = gpmc_get_clk_period(cs, cd);

	वापस (समय_ns * 1000 + tick_ps - 1) / tick_ps;
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_ns_to_ticks(अचिन्हित पूर्णांक समय_ns)
अणु
	वापस gpmc_ns_to_clk_ticks(समय_ns, /* any CS */ 0, GPMC_CD_FCLK);
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_ps_to_ticks(अचिन्हित पूर्णांक समय_ps)
अणु
	अचिन्हित दीर्घ tick_ps;

	/* Calculate in picosecs to yield more exact results */
	tick_ps = gpmc_get_fclk_period();

	वापस (समय_ps + tick_ps - 1) / tick_ps;
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_clk_ticks_to_ns(अचिन्हित पूर्णांक ticks, पूर्णांक cs,
					 क्रमागत gpmc_clk_करोमुख्य cd)
अणु
	वापस ticks * gpmc_get_clk_period(cs, cd) / 1000;
पूर्ण

अचिन्हित पूर्णांक gpmc_ticks_to_ns(अचिन्हित पूर्णांक ticks)
अणु
	वापस gpmc_clk_ticks_to_ns(ticks, /* any CS */ 0, GPMC_CD_FCLK);
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_ticks_to_ps(अचिन्हित पूर्णांक ticks)
अणु
	वापस ticks * gpmc_get_fclk_period();
पूर्ण

अटल अचिन्हित पूर्णांक gpmc_round_ps_to_ticks(अचिन्हित पूर्णांक समय_ps)
अणु
	अचिन्हित दीर्घ ticks = gpmc_ps_to_ticks(समय_ps);

	वापस ticks * gpmc_get_fclk_period();
पूर्ण

अटल अंतरभूत व्योम gpmc_cs_modअगरy_reg(पूर्णांक cs, पूर्णांक reg, u32 mask, bool value)
अणु
	u32 l;

	l = gpmc_cs_पढ़ो_reg(cs, reg);
	अगर (value)
		l |= mask;
	अन्यथा
		l &= ~mask;
	gpmc_cs_ग_लिखो_reg(cs, reg, l);
पूर्ण

अटल व्योम gpmc_cs_bool_timings(पूर्णांक cs, स्थिर काष्ठा gpmc_bool_timings *p)
अणु
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG1,
			   GPMC_CONFIG1_TIME_PARA_GRAN,
			   p->समय_para_granularity);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG2,
			   GPMC_CONFIG2_CSEXTRADELAY, p->cs_extra_delay);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG3,
			   GPMC_CONFIG3_ADVEXTRADELAY, p->adv_extra_delay);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG4,
			   GPMC_CONFIG4_OEEXTRADELAY, p->oe_extra_delay);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG4,
			   GPMC_CONFIG4_WEEXTRADELAY, p->we_extra_delay);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG6,
			   GPMC_CONFIG6_CYCLE2CYCLESAMECSEN,
			   p->cycle2cyclesamecsen);
	gpmc_cs_modअगरy_reg(cs, GPMC_CS_CONFIG6,
			   GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN,
			   p->cycle2cycledअगरfcsen);
पूर्ण

#अगर_घोषित CONFIG_OMAP_GPMC_DEBUG
/**
 * get_gpmc_timing_reg - पढ़ो a timing parameter and prपूर्णांक DTS settings क्रम it.
 * @cs:      Chip Select Region
 * @reg:     GPMC_CS_CONFIGn रेजिस्टर offset.
 * @st_bit:  Start Bit
 * @end_bit: End Bit. Must be >= @st_bit.
 * @max:     Maximum parameter value (beक्रमe optional @shअगरt).
 *           If 0, maximum is as high as @st_bit and @end_bit allow.
 * @name:    DTS node name, w/o "gpmc,"
 * @cd:      Clock Doमुख्य of timing parameter.
 * @shअगरt:   Parameter value left shअगरts @shअगरt, which is then prपूर्णांकed instead of value.
 * @raw:     Raw Format Option.
 *           raw क्रमmat:  gpmc,name = <value>
 *           tick क्रमmat: gpmc,name = <value> /&zwj;* x ns -- y ns; x ticks *&zwj;/
 *           Where x ns -- y ns result in the same tick value.
 *           When @max is exceeded, "invalid" is prपूर्णांकed inside comment.
 * @noval:   Parameter values equal to 0 are not prपूर्णांकed.
 * @वापस:  Specअगरied timing parameter (after optional @shअगरt).
 *
 */
अटल पूर्णांक get_gpmc_timing_reg(
	/* timing specअगरiers */
	पूर्णांक cs, पूर्णांक reg, पूर्णांक st_bit, पूर्णांक end_bit, पूर्णांक max,
	स्थिर अक्षर *name, स्थिर क्रमागत gpmc_clk_करोमुख्य cd,
	/* value transक्रमm */
	पूर्णांक shअगरt,
	/* क्रमmat specअगरiers */
	bool raw, bool noval)
अणु
	u32 l;
	पूर्णांक nr_bits;
	पूर्णांक mask;
	bool invalid;

	l = gpmc_cs_पढ़ो_reg(cs, reg);
	nr_bits = end_bit - st_bit + 1;
	mask = (1 << nr_bits) - 1;
	l = (l >> st_bit) & mask;
	अगर (!max)
		max = mask;
	invalid = l > max;
	अगर (shअगरt)
		l = (shअगरt << l);
	अगर (noval && (l == 0))
		वापस 0;
	अगर (!raw) अणु
		/* DTS tick क्रमmat क्रम timings in ns */
		अचिन्हित पूर्णांक समय_ns;
		अचिन्हित पूर्णांक समय_ns_min = 0;

		अगर (l)
			समय_ns_min = gpmc_clk_ticks_to_ns(l - 1, cs, cd) + 1;
		समय_ns = gpmc_clk_ticks_to_ns(l, cs, cd);
		pr_info("gpmc,%s = <%u>; /* %u ns - %u ns; %i ticks%s*/\n",
			name, समय_ns, समय_ns_min, समय_ns, l,
			invalid ? "; invalid " : " ");
	पूर्ण अन्यथा अणु
		/* raw क्रमmat */
		pr_info("gpmc,%s = <%u>;%s\n", name, l,
			invalid ? " /* invalid */" : "");
	पूर्ण

	वापस l;
पूर्ण

#घोषणा GPMC_PRINT_CONFIG(cs, config) \
	pr_info("cs%i %s: 0x%08x\n", cs, #config, \
		gpmc_cs_पढ़ो_reg(cs, config))
#घोषणा GPMC_GET_RAW(reg, st, end, field) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), 0, field, GPMC_CD_FCLK, 0, 1, 0)
#घोषणा GPMC_GET_RAW_MAX(reg, st, end, max, field) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), (max), field, GPMC_CD_FCLK, 0, 1, 0)
#घोषणा GPMC_GET_RAW_BOOL(reg, st, end, field) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), 0, field, GPMC_CD_FCLK, 0, 1, 1)
#घोषणा GPMC_GET_RAW_SHIFT_MAX(reg, st, end, shअगरt, max, field) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), (max), field, GPMC_CD_FCLK, (shअगरt), 1, 1)
#घोषणा GPMC_GET_TICKS(reg, st, end, field) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), 0, field, GPMC_CD_FCLK, 0, 0, 0)
#घोषणा GPMC_GET_TICKS_CD(reg, st, end, field, cd) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), 0, field, (cd), 0, 0, 0)
#घोषणा GPMC_GET_TICKS_CD_MAX(reg, st, end, max, field, cd) \
	get_gpmc_timing_reg(cs, (reg), (st), (end), (max), field, (cd), 0, 0, 0)

अटल व्योम gpmc_show_regs(पूर्णांक cs, स्थिर अक्षर *desc)
अणु
	pr_info("gpmc cs%i %s:\n", cs, desc);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG1);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG2);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG3);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG4);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG5);
	GPMC_PRINT_CONFIG(cs, GPMC_CS_CONFIG6);
पूर्ण

/*
 * Note that gpmc,रुको-pin handing wrongly assumes bit 8 is available,
 * see commit c9fb809.
 */
अटल व्योम gpmc_cs_show_timings(पूर्णांक cs, स्थिर अक्षर *desc)
अणु
	gpmc_show_regs(cs, desc);

	pr_info("gpmc cs%i access configuration:\n", cs);
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1,  4,  4, "time-para-granularity");
	GPMC_GET_RAW(GPMC_CS_CONFIG1,  8,  9, "mux-add-data");
	GPMC_GET_RAW_SHIFT_MAX(GPMC_CS_CONFIG1, 12, 13, 1,
			       GPMC_CONFIG1_DEVICESIZE_MAX, "device-width");
	GPMC_GET_RAW(GPMC_CS_CONFIG1, 16, 17, "wait-pin");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 21, 21, "wait-on-write");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 22, 22, "wait-on-read");
	GPMC_GET_RAW_SHIFT_MAX(GPMC_CS_CONFIG1, 23, 24, 4,
			       GPMC_CONFIG1_ATTACHEDDEVICEPAGELENGTH_MAX,
			       "burst-length");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 27, 27, "sync-write");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 28, 28, "burst-write");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 29, 29, "gpmc,sync-read");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 30, 30, "burst-read");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG1, 31, 31, "burst-wrap");

	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG2,  7,  7, "cs-extra-delay");

	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG3,  7,  7, "adv-extra-delay");

	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG4, 23, 23, "we-extra-delay");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG4,  7,  7, "oe-extra-delay");

	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG6,  7,  7, "cycle2cycle-samecsen");
	GPMC_GET_RAW_BOOL(GPMC_CS_CONFIG6,  6,  6, "cycle2cycle-diffcsen");

	pr_info("gpmc cs%i timings configuration:\n", cs);
	GPMC_GET_TICKS(GPMC_CS_CONFIG2,  0,  3, "cs-on-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG2,  8, 12, "cs-rd-off-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG2, 16, 20, "cs-wr-off-ns");

	GPMC_GET_TICKS(GPMC_CS_CONFIG3,  0,  3, "adv-on-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG3,  8, 12, "adv-rd-off-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG3, 16, 20, "adv-wr-off-ns");
	अगर (gpmc_capability & GPMC_HAS_MUX_AAD) अणु
		GPMC_GET_TICKS(GPMC_CS_CONFIG3, 4, 6, "adv-aad-mux-on-ns");
		GPMC_GET_TICKS(GPMC_CS_CONFIG3, 24, 26,
				"adv-aad-mux-rd-off-ns");
		GPMC_GET_TICKS(GPMC_CS_CONFIG3, 28, 30,
				"adv-aad-mux-wr-off-ns");
	पूर्ण

	GPMC_GET_TICKS(GPMC_CS_CONFIG4,  0,  3, "oe-on-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG4,  8, 12, "oe-off-ns");
	अगर (gpmc_capability & GPMC_HAS_MUX_AAD) अणु
		GPMC_GET_TICKS(GPMC_CS_CONFIG4,  4,  6, "oe-aad-mux-on-ns");
		GPMC_GET_TICKS(GPMC_CS_CONFIG4, 13, 15, "oe-aad-mux-off-ns");
	पूर्ण
	GPMC_GET_TICKS(GPMC_CS_CONFIG4, 16, 19, "we-on-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG4, 24, 28, "we-off-ns");

	GPMC_GET_TICKS(GPMC_CS_CONFIG5,  0,  4, "rd-cycle-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG5,  8, 12, "wr-cycle-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG5, 16, 20, "access-ns");

	GPMC_GET_TICKS(GPMC_CS_CONFIG5, 24, 27, "page-burst-access-ns");

	GPMC_GET_TICKS(GPMC_CS_CONFIG6, 0, 3, "bus-turnaround-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG6, 8, 11, "cycle2cycle-delay-ns");

	GPMC_GET_TICKS_CD_MAX(GPMC_CS_CONFIG1, 18, 19,
			      GPMC_CONFIG1_WAITMONITORINGTIME_MAX,
			      "wait-monitoring-ns", GPMC_CD_CLK);
	GPMC_GET_TICKS_CD_MAX(GPMC_CS_CONFIG1, 25, 26,
			      GPMC_CONFIG1_CLKACTIVATIONTIME_MAX,
			      "clk-activation-ns", GPMC_CD_FCLK);

	GPMC_GET_TICKS(GPMC_CS_CONFIG6, 16, 19, "wr-data-mux-bus-ns");
	GPMC_GET_TICKS(GPMC_CS_CONFIG6, 24, 28, "wr-access-ns");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम gpmc_cs_show_timings(पूर्णांक cs, स्थिर अक्षर *desc)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * set_gpmc_timing_reg - set a single timing parameter क्रम Chip Select Region.
 * Caller is expected to have initialized CONFIG1 GPMCFCLKDIVIDER
 * prior to calling this function with @cd equal to GPMC_CD_CLK.
 *
 * @cs:      Chip Select Region.
 * @reg:     GPMC_CS_CONFIGn रेजिस्टर offset.
 * @st_bit:  Start Bit
 * @end_bit: End Bit. Must be >= @st_bit.
 * @max:     Maximum parameter value.
 *           If 0, maximum is as high as @st_bit and @end_bit allow.
 * @समय:    Timing parameter in ns.
 * @cd:      Timing parameter घड़ी करोमुख्य.
 * @name:    Timing parameter name.
 * @वापस:  0 on success, -1 on error.
 */
अटल पूर्णांक set_gpmc_timing_reg(पूर्णांक cs, पूर्णांक reg, पूर्णांक st_bit, पूर्णांक end_bit, पूर्णांक max,
			       पूर्णांक समय, क्रमागत gpmc_clk_करोमुख्य cd, स्थिर अक्षर *name)
अणु
	u32 l;
	पूर्णांक ticks, mask, nr_bits;

	अगर (समय == 0)
		ticks = 0;
	अन्यथा
		ticks = gpmc_ns_to_clk_ticks(समय, cs, cd);
	nr_bits = end_bit - st_bit + 1;
	mask = (1 << nr_bits) - 1;

	अगर (!max)
		max = mask;

	अगर (ticks > max) अणु
		pr_err("%s: GPMC CS%d: %s %d ns, %d ticks > %d ticks\n",
		       __func__, cs, name, समय, ticks, max);

		वापस -1;
	पूर्ण

	l = gpmc_cs_पढ़ो_reg(cs, reg);
#अगर_घोषित CONFIG_OMAP_GPMC_DEBUG
	pr_info("GPMC CS%d: %-17s: %3d ticks, %3lu ns (was %3i ticks) %3d ns\n",
		cs, name, ticks, gpmc_get_clk_period(cs, cd) * ticks / 1000,
			(l >> st_bit) & mask, समय);
#पूर्ण_अगर
	l &= ~(mask << st_bit);
	l |= ticks << st_bit;
	gpmc_cs_ग_लिखो_reg(cs, reg, l);

	वापस 0;
पूर्ण

/**
 * gpmc_calc_रुकोmonitoring_भागider - calculate proper GPMCFCLKDIVIDER based on WAITMONITORINGTIME
 * WAITMONITORINGTIME will be _at least_ as दीर्घ as desired, i.e.
 * पढ़ो  --> करोn't sample bus too early
 * ग_लिखो --> data is दीर्घer on bus
 *
 * Formula:
 * gpmc_clk_भाग + 1 = उच्चमान(उच्चमान(रुकोmonitoringसमय_ns / gpmc_fclk_ns)
 *                    / रुकोmonitoring_ticks)
 * WAITMONITORINGTIME resulting in 0 or 1 tick with भाग = 1 are caught by
 * भाग <= 0 check.
 *
 * @रुको_monitoring: WAITMONITORINGTIME in ns.
 * @वापस:          -1 on failure to scale, अन्यथा proper भागider > 0.
 */
अटल पूर्णांक gpmc_calc_रुकोmonitoring_भागider(अचिन्हित पूर्णांक रुको_monitoring)
अणु
	पूर्णांक भाग = gpmc_ns_to_ticks(रुको_monitoring);

	भाग += GPMC_CONFIG1_WAITMONITORINGTIME_MAX - 1;
	भाग /= GPMC_CONFIG1_WAITMONITORINGTIME_MAX;

	अगर (भाग > 4)
		वापस -1;
	अगर (भाग <= 0)
		भाग = 1;

	वापस भाग;
पूर्ण

/**
 * gpmc_calc_भागider - calculate GPMC_FCLK भागider क्रम sync_clk GPMC_CLK period.
 * @sync_clk: GPMC_CLK period in ps.
 * @वापस:   Returns at least 1 अगर GPMC_FCLK can be भागided to GPMC_CLK.
 *            Else, वापसs -1.
 */
पूर्णांक gpmc_calc_भागider(अचिन्हित पूर्णांक sync_clk)
अणु
	पूर्णांक भाग = gpmc_ps_to_ticks(sync_clk);

	अगर (भाग > 4)
		वापस -1;
	अगर (भाग <= 0)
		भाग = 1;

	वापस भाग;
पूर्ण

/**
 * gpmc_cs_set_timings - program timing parameters क्रम Chip Select Region.
 * @cs:     Chip Select Region.
 * @t:      GPMC timing parameters.
 * @s:      GPMC timing settings.
 * @वापस: 0 on success, -1 on error.
 */
पूर्णांक gpmc_cs_set_timings(पूर्णांक cs, स्थिर काष्ठा gpmc_timings *t,
			स्थिर काष्ठा gpmc_settings *s)
अणु
	पूर्णांक भाग, ret;
	u32 l;

	भाग = gpmc_calc_भागider(t->sync_clk);
	अगर (भाग < 0)
		वापस -EINVAL;

	/*
	 * See अगर we need to change the भागider क्रम रुकोmonitoringसमय.
	 *
	 * Calculate GPMCFCLKDIVIDER independent of gpmc,sync-clk-ps in DT क्रम
	 * pure asynchronous accesses, i.e. both पढ़ो and ग_लिखो asynchronous.
	 * However, only करो so अगर WAITMONITORINGTIME is actually used, i.e.
	 * either WAITREADMONITORING or WAITWRITEMONITORING is set.
	 *
	 * This statement must not change भाग to scale async WAITMONITORINGTIME
	 * to protect mixed synchronous and asynchronous accesses.
	 *
	 * We उठाओ an error later अगर WAITMONITORINGTIME करोes not fit.
	 */
	अगर (!s->sync_पढ़ो && !s->sync_ग_लिखो &&
	    (s->रुको_on_पढ़ो || s->रुको_on_ग_लिखो)
	   ) अणु
		भाग = gpmc_calc_रुकोmonitoring_भागider(t->रुको_monitoring);
		अगर (भाग < 0) अणु
			pr_err("%s: waitmonitoringtime %3d ns too large for greatest gpmcfclkdivider.\n",
			       __func__,
			       t->रुको_monitoring
			       );
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	ret = 0;
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG2, 0, 3, 0, t->cs_on,
				   GPMC_CD_FCLK, "cs_on");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG2, 8, 12, 0, t->cs_rd_off,
				   GPMC_CD_FCLK, "cs_rd_off");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG2, 16, 20, 0, t->cs_wr_off,
				   GPMC_CD_FCLK, "cs_wr_off");
	अगर (ret)
		वापस -ENXIO;

	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 0, 3, 0, t->adv_on,
				   GPMC_CD_FCLK, "adv_on");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 8, 12, 0, t->adv_rd_off,
				   GPMC_CD_FCLK, "adv_rd_off");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 16, 20, 0, t->adv_wr_off,
				   GPMC_CD_FCLK, "adv_wr_off");
	अगर (ret)
		वापस -ENXIO;

	अगर (gpmc_capability & GPMC_HAS_MUX_AAD) अणु
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 4, 6, 0,
					   t->adv_aad_mux_on, GPMC_CD_FCLK,
					   "adv_aad_mux_on");
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 24, 26, 0,
					   t->adv_aad_mux_rd_off, GPMC_CD_FCLK,
					   "adv_aad_mux_rd_off");
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG3, 28, 30, 0,
					   t->adv_aad_mux_wr_off, GPMC_CD_FCLK,
					   "adv_aad_mux_wr_off");
		अगर (ret)
			वापस -ENXIO;
	पूर्ण

	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 0, 3, 0, t->oe_on,
				   GPMC_CD_FCLK, "oe_on");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 8, 12, 0, t->oe_off,
				   GPMC_CD_FCLK, "oe_off");
	अगर (gpmc_capability & GPMC_HAS_MUX_AAD) अणु
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 4, 6, 0,
					   t->oe_aad_mux_on, GPMC_CD_FCLK,
					   "oe_aad_mux_on");
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 13, 15, 0,
					   t->oe_aad_mux_off, GPMC_CD_FCLK,
					   "oe_aad_mux_off");
	पूर्ण
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 16, 19, 0, t->we_on,
				   GPMC_CD_FCLK, "we_on");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG4, 24, 28, 0, t->we_off,
				   GPMC_CD_FCLK, "we_off");
	अगर (ret)
		वापस -ENXIO;

	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG5, 0, 4, 0, t->rd_cycle,
				   GPMC_CD_FCLK, "rd_cycle");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG5, 8, 12, 0, t->wr_cycle,
				   GPMC_CD_FCLK, "wr_cycle");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG5, 16, 20, 0, t->access,
				   GPMC_CD_FCLK, "access");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG5, 24, 27, 0,
				   t->page_burst_access, GPMC_CD_FCLK,
				   "page_burst_access");
	अगर (ret)
		वापस -ENXIO;

	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG6, 0, 3, 0,
				   t->bus_turnaround, GPMC_CD_FCLK,
				   "bus_turnaround");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG6, 8, 11, 0,
				   t->cycle2cycle_delay, GPMC_CD_FCLK,
				   "cycle2cycle_delay");
	अगर (ret)
		वापस -ENXIO;

	अगर (gpmc_capability & GPMC_HAS_WR_DATA_MUX_BUS) अणु
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG6, 16, 19, 0,
					   t->wr_data_mux_bus, GPMC_CD_FCLK,
					   "wr_data_mux_bus");
		अगर (ret)
			वापस -ENXIO;
	पूर्ण
	अगर (gpmc_capability & GPMC_HAS_WR_ACCESS) अणु
		ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG6, 24, 28, 0,
					   t->wr_access, GPMC_CD_FCLK,
					   "wr_access");
		अगर (ret)
			वापस -ENXIO;
	पूर्ण

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG1);
	l &= ~0x03;
	l |= (भाग - 1);
	gpmc_cs_ग_लिखो_reg(cs, GPMC_CS_CONFIG1, l);

	ret = 0;
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG1, 18, 19,
				   GPMC_CONFIG1_WAITMONITORINGTIME_MAX,
				   t->रुको_monitoring, GPMC_CD_CLK,
				   "wait_monitoring");
	ret |= set_gpmc_timing_reg(cs, GPMC_CS_CONFIG1, 25, 26,
				   GPMC_CONFIG1_CLKACTIVATIONTIME_MAX,
				   t->clk_activation, GPMC_CD_FCLK,
				   "clk_activation");
	अगर (ret)
		वापस -ENXIO;

#अगर_घोषित CONFIG_OMAP_GPMC_DEBUG
	pr_info("GPMC CS%d CLK period is %lu ns (div %d)\n",
			cs, (भाग * gpmc_get_fclk_period()) / 1000, भाग);
#पूर्ण_अगर

	gpmc_cs_bool_timings(cs, &t->bool_timings);
	gpmc_cs_show_timings(cs, "after gpmc_cs_set_timings");

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_cs_set_memconf(पूर्णांक cs, u32 base, u32 size)
अणु
	u32 l;
	u32 mask;

	/*
	 * Ensure that base address is aligned on a
	 * boundary equal to or greater than size.
	 */
	अगर (base & (size - 1))
		वापस -EINVAL;

	base >>= GPMC_CHUNK_SHIFT;
	mask = (1 << GPMC_SECTION_SHIFT) - size;
	mask >>= GPMC_CHUNK_SHIFT;
	mask <<= GPMC_CONFIG7_MASKADDRESS_OFFSET;

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG7);
	l &= ~GPMC_CONFIG7_MASK;
	l |= base & GPMC_CONFIG7_BASEADDRESS_MASK;
	l |= mask & GPMC_CONFIG7_MASKADDRESS_MASK;
	l |= GPMC_CONFIG7_CSVALID;
	gpmc_cs_ग_लिखो_reg(cs, GPMC_CS_CONFIG7, l);

	वापस 0;
पूर्ण

अटल व्योम gpmc_cs_enable_mem(पूर्णांक cs)
अणु
	u32 l;

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG7);
	l |= GPMC_CONFIG7_CSVALID;
	gpmc_cs_ग_लिखो_reg(cs, GPMC_CS_CONFIG7, l);
पूर्ण

अटल व्योम gpmc_cs_disable_mem(पूर्णांक cs)
अणु
	u32 l;

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG7);
	l &= ~GPMC_CONFIG7_CSVALID;
	gpmc_cs_ग_लिखो_reg(cs, GPMC_CS_CONFIG7, l);
पूर्ण

अटल व्योम gpmc_cs_get_memconf(पूर्णांक cs, u32 *base, u32 *size)
अणु
	u32 l;
	u32 mask;

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG7);
	*base = (l & 0x3f) << GPMC_CHUNK_SHIFT;
	mask = (l >> 8) & 0x0f;
	*size = (1 << GPMC_SECTION_SHIFT) - (mask << GPMC_CHUNK_SHIFT);
पूर्ण

अटल पूर्णांक gpmc_cs_mem_enabled(पूर्णांक cs)
अणु
	u32 l;

	l = gpmc_cs_पढ़ो_reg(cs, GPMC_CS_CONFIG7);
	वापस l & GPMC_CONFIG7_CSVALID;
पूर्ण

अटल व्योम gpmc_cs_set_reserved(पूर्णांक cs, पूर्णांक reserved)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];

	gpmc->flags |= GPMC_CS_RESERVED;
पूर्ण

अटल bool gpmc_cs_reserved(पूर्णांक cs)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];

	वापस gpmc->flags & GPMC_CS_RESERVED;
पूर्ण

अटल अचिन्हित दीर्घ gpmc_mem_align(अचिन्हित दीर्घ size)
अणु
	पूर्णांक order;

	size = (size - 1) >> (GPMC_CHUNK_SHIFT - 1);
	order = GPMC_CHUNK_SHIFT - 1;
	करो अणु
		size >>= 1;
		order++;
	पूर्ण जबतक (size);
	size = 1 << order;
	वापस size;
पूर्ण

अटल पूर्णांक gpmc_cs_insert_mem(पूर्णांक cs, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];
	काष्ठा resource *res = &gpmc->mem;
	पूर्णांक r;

	size = gpmc_mem_align(size);
	spin_lock(&gpmc_mem_lock);
	res->start = base;
	res->end = base + size - 1;
	r = request_resource(&gpmc_mem_root, res);
	spin_unlock(&gpmc_mem_lock);

	वापस r;
पूर्ण

अटल पूर्णांक gpmc_cs_delete_mem(पूर्णांक cs)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];
	काष्ठा resource *res = &gpmc->mem;
	पूर्णांक r;

	spin_lock(&gpmc_mem_lock);
	r = release_resource(res);
	res->start = 0;
	res->end = 0;
	spin_unlock(&gpmc_mem_lock);

	वापस r;
पूर्ण

पूर्णांक gpmc_cs_request(पूर्णांक cs, अचिन्हित दीर्घ size, अचिन्हित दीर्घ *base)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];
	काष्ठा resource *res = &gpmc->mem;
	पूर्णांक r = -1;

	अगर (cs >= gpmc_cs_num) अणु
		pr_err("%s: requested chip-select is disabled\n", __func__);
		वापस -ENODEV;
	पूर्ण
	size = gpmc_mem_align(size);
	अगर (size > (1 << GPMC_SECTION_SHIFT))
		वापस -ENOMEM;

	spin_lock(&gpmc_mem_lock);
	अगर (gpmc_cs_reserved(cs)) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (gpmc_cs_mem_enabled(cs))
		r = adjust_resource(res, res->start & ~(size - 1), size);
	अगर (r < 0)
		r = allocate_resource(&gpmc_mem_root, res, size, 0, ~0,
				      size, शून्य, शून्य);
	अगर (r < 0)
		जाओ out;

	/* Disable CS जबतक changing base address and size mask */
	gpmc_cs_disable_mem(cs);

	r = gpmc_cs_set_memconf(cs, res->start, resource_size(res));
	अगर (r < 0) अणु
		release_resource(res);
		जाओ out;
	पूर्ण

	/* Enable CS */
	gpmc_cs_enable_mem(cs);
	*base = res->start;
	gpmc_cs_set_reserved(cs, 1);
out:
	spin_unlock(&gpmc_mem_lock);
	वापस r;
पूर्ण
EXPORT_SYMBOL(gpmc_cs_request);

व्योम gpmc_cs_मुक्त(पूर्णांक cs)
अणु
	काष्ठा gpmc_cs_data *gpmc;
	काष्ठा resource *res;

	spin_lock(&gpmc_mem_lock);
	अगर (cs >= gpmc_cs_num || cs < 0 || !gpmc_cs_reserved(cs)) अणु
		WARN(1, "Trying to free non-reserved GPMC CS%d\n", cs);
		spin_unlock(&gpmc_mem_lock);
		वापस;
	पूर्ण
	gpmc = &gpmc_cs[cs];
	res = &gpmc->mem;

	gpmc_cs_disable_mem(cs);
	अगर (res->flags)
		release_resource(res);
	gpmc_cs_set_reserved(cs, 0);
	spin_unlock(&gpmc_mem_lock);
पूर्ण
EXPORT_SYMBOL(gpmc_cs_मुक्त);

/**
 * gpmc_configure - ग_लिखो request to configure gpmc
 * @cmd: command type
 * @wval: value to ग_लिखो
 * @वापस status of the operation
 */
पूर्णांक gpmc_configure(पूर्णांक cmd, पूर्णांक wval)
अणु
	u32 regval;

	चयन (cmd) अणु
	हाल GPMC_CONFIG_WP:
		regval = gpmc_पढ़ो_reg(GPMC_CONFIG);
		अगर (wval)
			regval &= ~GPMC_CONFIG_WRITEPROTECT; /* WP is ON */
		अन्यथा
			regval |= GPMC_CONFIG_WRITEPROTECT;  /* WP is OFF */
		gpmc_ग_लिखो_reg(GPMC_CONFIG, regval);
		अवरोध;

	शेष:
		pr_err("%s: command not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gpmc_configure);

अटल bool gpmc_nand_ग_लिखोbuffer_empty(व्योम)
अणु
	अगर (gpmc_पढ़ो_reg(GPMC_STATUS) & GPMC_STATUS_EMPTYWRITEBUFFERSTATUS)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा gpmc_nand_ops nand_ops = अणु
	.nand_ग_लिखोbuffer_empty = gpmc_nand_ग_लिखोbuffer_empty,
पूर्ण;

/**
 * gpmc_omap_get_nand_ops - Get the GPMC न_अंकD पूर्णांकerface
 * @reg: the GPMC न_अंकD रेजिस्टर map exclusive क्रम न_अंकD use.
 * @cs: GPMC chip select number on which the न_अंकD sits. The
 *      रेजिस्टर map वापसed will be specअगरic to this chip select.
 *
 * Returns शून्य on error e.g. invalid cs.
 */
काष्ठा gpmc_nand_ops *gpmc_omap_get_nand_ops(काष्ठा gpmc_nand_regs *reg, पूर्णांक cs)
अणु
	पूर्णांक i;

	अगर (cs >= gpmc_cs_num)
		वापस शून्य;

	reg->gpmc_nand_command = gpmc_base + GPMC_CS0_OFFSET +
				GPMC_CS_न_अंकD_COMMAND + GPMC_CS_SIZE * cs;
	reg->gpmc_nand_address = gpmc_base + GPMC_CS0_OFFSET +
				GPMC_CS_न_अंकD_ADDRESS + GPMC_CS_SIZE * cs;
	reg->gpmc_nand_data = gpmc_base + GPMC_CS0_OFFSET +
				GPMC_CS_न_अंकD_DATA + GPMC_CS_SIZE * cs;
	reg->gpmc_prefetch_config1 = gpmc_base + GPMC_PREFETCH_CONFIG1;
	reg->gpmc_prefetch_config2 = gpmc_base + GPMC_PREFETCH_CONFIG2;
	reg->gpmc_prefetch_control = gpmc_base + GPMC_PREFETCH_CONTROL;
	reg->gpmc_prefetch_status = gpmc_base + GPMC_PREFETCH_STATUS;
	reg->gpmc_ecc_config = gpmc_base + GPMC_ECC_CONFIG;
	reg->gpmc_ecc_control = gpmc_base + GPMC_ECC_CONTROL;
	reg->gpmc_ecc_size_config = gpmc_base + GPMC_ECC_SIZE_CONFIG;
	reg->gpmc_ecc1_result = gpmc_base + GPMC_ECC1_RESULT;

	क्रम (i = 0; i < GPMC_BCH_NUM_REMAINDER; i++) अणु
		reg->gpmc_bch_result0[i] = gpmc_base + GPMC_ECC_BCH_RESULT_0 +
					   GPMC_BCH_SIZE * i;
		reg->gpmc_bch_result1[i] = gpmc_base + GPMC_ECC_BCH_RESULT_1 +
					   GPMC_BCH_SIZE * i;
		reg->gpmc_bch_result2[i] = gpmc_base + GPMC_ECC_BCH_RESULT_2 +
					   GPMC_BCH_SIZE * i;
		reg->gpmc_bch_result3[i] = gpmc_base + GPMC_ECC_BCH_RESULT_3 +
					   GPMC_BCH_SIZE * i;
		reg->gpmc_bch_result4[i] = gpmc_base + GPMC_ECC_BCH_RESULT_4 +
					   i * GPMC_BCH_SIZE;
		reg->gpmc_bch_result5[i] = gpmc_base + GPMC_ECC_BCH_RESULT_5 +
					   i * GPMC_BCH_SIZE;
		reg->gpmc_bch_result6[i] = gpmc_base + GPMC_ECC_BCH_RESULT_6 +
					   i * GPMC_BCH_SIZE;
	पूर्ण

	वापस &nand_ops;
पूर्ण
EXPORT_SYMBOL_GPL(gpmc_omap_get_nand_ops);

अटल व्योम gpmc_omap_onenand_calc_sync_timings(काष्ठा gpmc_timings *t,
						काष्ठा gpmc_settings *s,
						पूर्णांक freq, पूर्णांक latency)
अणु
	काष्ठा gpmc_device_timings dev_t;
	स्थिर पूर्णांक t_cer  = 15;
	स्थिर पूर्णांक t_avdp = 12;
	स्थिर पूर्णांक t_cez  = 20; /* max of t_cez, t_oez */
	स्थिर पूर्णांक t_wpl  = 40;
	स्थिर पूर्णांक t_wph  = 30;
	पूर्णांक min_gpmc_clk_period, t_ces, t_avds, t_avdh, t_ach, t_aavdh, t_rdyo;

	चयन (freq) अणु
	हाल 104:
		min_gpmc_clk_period = 9600; /* 104 MHz */
		t_ces   = 3;
		t_avds  = 4;
		t_avdh  = 2;
		t_ach   = 3;
		t_aavdh = 6;
		t_rdyo  = 6;
		अवरोध;
	हाल 83:
		min_gpmc_clk_period = 12000; /* 83 MHz */
		t_ces   = 5;
		t_avds  = 4;
		t_avdh  = 2;
		t_ach   = 6;
		t_aavdh = 6;
		t_rdyo  = 9;
		अवरोध;
	हाल 66:
		min_gpmc_clk_period = 15000; /* 66 MHz */
		t_ces   = 6;
		t_avds  = 5;
		t_avdh  = 2;
		t_ach   = 6;
		t_aavdh = 6;
		t_rdyo  = 11;
		अवरोध;
	शेष:
		min_gpmc_clk_period = 18500; /* 54 MHz */
		t_ces   = 7;
		t_avds  = 7;
		t_avdh  = 7;
		t_ach   = 9;
		t_aavdh = 7;
		t_rdyo  = 15;
		अवरोध;
	पूर्ण

	/* Set synchronous पढ़ो timings */
	स_रखो(&dev_t, 0, माप(dev_t));

	अगर (!s->sync_ग_लिखो) अणु
		dev_t.t_avdp_w = max(t_avdp, t_cer) * 1000;
		dev_t.t_wpl = t_wpl * 1000;
		dev_t.t_wph = t_wph * 1000;
		dev_t.t_aavdh = t_aavdh * 1000;
	पूर्ण
	dev_t.ce_xdelay = true;
	dev_t.avd_xdelay = true;
	dev_t.oe_xdelay = true;
	dev_t.we_xdelay = true;
	dev_t.clk = min_gpmc_clk_period;
	dev_t.t_bacc = dev_t.clk;
	dev_t.t_ces = t_ces * 1000;
	dev_t.t_avds = t_avds * 1000;
	dev_t.t_avdh = t_avdh * 1000;
	dev_t.t_ach = t_ach * 1000;
	dev_t.cyc_iaa = (latency + 1);
	dev_t.t_cez_r = t_cez * 1000;
	dev_t.t_cez_w = dev_t.t_cez_r;
	dev_t.cyc_aavdh_oe = 1;
	dev_t.t_rdyo = t_rdyo * 1000 + min_gpmc_clk_period;

	gpmc_calc_timings(t, s, &dev_t);
पूर्ण

पूर्णांक gpmc_omap_onenand_set_timings(काष्ठा device *dev, पूर्णांक cs, पूर्णांक freq,
				  पूर्णांक latency,
				  काष्ठा gpmc_onenand_info *info)
अणु
	पूर्णांक ret;
	काष्ठा gpmc_timings gpmc_t;
	काष्ठा gpmc_settings gpmc_s;

	gpmc_पढ़ो_settings_dt(dev->of_node, &gpmc_s);

	info->sync_पढ़ो = gpmc_s.sync_पढ़ो;
	info->sync_ग_लिखो = gpmc_s.sync_ग_लिखो;
	info->burst_len = gpmc_s.burst_len;

	अगर (!gpmc_s.sync_पढ़ो && !gpmc_s.sync_ग_लिखो)
		वापस 0;

	gpmc_omap_onenand_calc_sync_timings(&gpmc_t, &gpmc_s, freq, latency);

	ret = gpmc_cs_program_settings(cs, &gpmc_s);
	अगर (ret < 0)
		वापस ret;

	वापस gpmc_cs_set_timings(cs, &gpmc_t, &gpmc_s);
पूर्ण
EXPORT_SYMBOL_GPL(gpmc_omap_onenand_set_timings);

पूर्णांक gpmc_get_client_irq(अचिन्हित पूर्णांक irq_config)
अणु
	अगर (!gpmc_irq_करोमुख्य) अणु
		pr_warn("%s called before GPMC IRQ domain available\n",
			__func__);
		वापस 0;
	पूर्ण

	/* we restrict this to न_अंकD IRQs only */
	अगर (irq_config >= GPMC_NR_न_अंकD_IRQS)
		वापस 0;

	वापस irq_create_mapping(gpmc_irq_करोमुख्य, irq_config);
पूर्ण

अटल पूर्णांक gpmc_irq_endis(अचिन्हित दीर्घ hwirq, bool endis)
अणु
	u32 regval;

	/* bits GPMC_NR_न_अंकD_IRQS to 8 are reserved */
	अगर (hwirq >= GPMC_NR_न_अंकD_IRQS)
		hwirq += 8 - GPMC_NR_न_अंकD_IRQS;

	regval = gpmc_पढ़ो_reg(GPMC_IRQENABLE);
	अगर (endis)
		regval |= BIT(hwirq);
	अन्यथा
		regval &= ~BIT(hwirq);
	gpmc_ग_लिखो_reg(GPMC_IRQENABLE, regval);

	वापस 0;
पूर्ण

अटल व्योम gpmc_irq_disable(काष्ठा irq_data *p)
अणु
	gpmc_irq_endis(p->hwirq, false);
पूर्ण

अटल व्योम gpmc_irq_enable(काष्ठा irq_data *p)
अणु
	gpmc_irq_endis(p->hwirq, true);
पूर्ण

अटल व्योम gpmc_irq_mask(काष्ठा irq_data *d)
अणु
	gpmc_irq_endis(d->hwirq, false);
पूर्ण

अटल व्योम gpmc_irq_unmask(काष्ठा irq_data *d)
अणु
	gpmc_irq_endis(d->hwirq, true);
पूर्ण

अटल व्योम gpmc_irq_edge_config(अचिन्हित दीर्घ hwirq, bool rising_edge)
अणु
	u32 regval;

	/* न_अंकD IRQs polarity is not configurable */
	अगर (hwirq < GPMC_NR_न_अंकD_IRQS)
		वापस;

	/* WAITPIN starts at BIT 8 */
	hwirq += 8 - GPMC_NR_न_अंकD_IRQS;

	regval = gpmc_पढ़ो_reg(GPMC_CONFIG);
	अगर (rising_edge)
		regval &= ~BIT(hwirq);
	अन्यथा
		regval |= BIT(hwirq);

	gpmc_ग_लिखो_reg(GPMC_CONFIG, regval);
पूर्ण

अटल व्योम gpmc_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hwirq = d->hwirq;

	/* skip reserved bits */
	अगर (hwirq >= GPMC_NR_न_अंकD_IRQS)
		hwirq += 8 - GPMC_NR_न_अंकD_IRQS;

	/* Setting bit to 1 clears (or Acks) the पूर्णांकerrupt */
	gpmc_ग_लिखो_reg(GPMC_IRQSTATUS, BIT(hwirq));
पूर्ण

अटल पूर्णांक gpmc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक trigger)
अणु
	/* can't set type क्रम न_अंकD IRQs */
	अगर (d->hwirq < GPMC_NR_न_अंकD_IRQS)
		वापस -EINVAL;

	/* We can support either rising or falling edge at a समय */
	अगर (trigger == IRQ_TYPE_EDGE_FALLING)
		gpmc_irq_edge_config(d->hwirq, false);
	अन्यथा अगर (trigger == IRQ_TYPE_EDGE_RISING)
		gpmc_irq_edge_config(d->hwirq, true);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hw)
अणु
	काष्ठा gpmc_device *gpmc = d->host_data;

	irq_set_chip_data(virq, gpmc);
	अगर (hw < GPMC_NR_न_अंकD_IRQS) अणु
		irq_modअगरy_status(virq, IRQ_NOREQUEST, IRQ_NOAUTOEN);
		irq_set_chip_and_handler(virq, &gpmc->irq_chip,
					 handle_simple_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(virq, &gpmc->irq_chip,
					 handle_edge_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gpmc_irq_करोमुख्य_ops = अणु
	.map    = gpmc_irq_map,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल irqवापस_t gpmc_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक hwirq, virq;
	u32 regval, regvalx;
	काष्ठा gpmc_device *gpmc = data;

	regval = gpmc_पढ़ो_reg(GPMC_IRQSTATUS);
	regvalx = regval;

	अगर (!regval)
		वापस IRQ_NONE;

	क्रम (hwirq = 0; hwirq < gpmc->nirqs; hwirq++) अणु
		/* skip reserved status bits */
		अगर (hwirq == GPMC_NR_न_अंकD_IRQS)
			regvalx >>= 8 - GPMC_NR_न_अंकD_IRQS;

		अगर (regvalx & BIT(hwirq)) अणु
			virq = irq_find_mapping(gpmc_irq_करोमुख्य, hwirq);
			अगर (!virq) अणु
				dev_warn(gpmc->dev,
					 "spurious irq detected hwirq %d, virq %d\n",
					 hwirq, virq);
			पूर्ण

			generic_handle_irq(virq);
		पूर्ण
	पूर्ण

	gpmc_ग_लिखो_reg(GPMC_IRQSTATUS, regval);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gpmc_setup_irq(काष्ठा gpmc_device *gpmc)
अणु
	u32 regval;
	पूर्णांक rc;

	/* Disable पूर्णांकerrupts */
	gpmc_ग_लिखो_reg(GPMC_IRQENABLE, 0);

	/* clear पूर्णांकerrupts */
	regval = gpmc_पढ़ो_reg(GPMC_IRQSTATUS);
	gpmc_ग_लिखो_reg(GPMC_IRQSTATUS, regval);

	gpmc->irq_chip.name = "gpmc";
	gpmc->irq_chip.irq_enable = gpmc_irq_enable;
	gpmc->irq_chip.irq_disable = gpmc_irq_disable;
	gpmc->irq_chip.irq_ack = gpmc_irq_ack;
	gpmc->irq_chip.irq_mask = gpmc_irq_mask;
	gpmc->irq_chip.irq_unmask = gpmc_irq_unmask;
	gpmc->irq_chip.irq_set_type = gpmc_irq_set_type;

	gpmc_irq_करोमुख्य = irq_करोमुख्य_add_linear(gpmc->dev->of_node,
						gpmc->nirqs,
						&gpmc_irq_करोमुख्य_ops,
						gpmc);
	अगर (!gpmc_irq_करोमुख्य) अणु
		dev_err(gpmc->dev, "IRQ domain add failed\n");
		वापस -ENODEV;
	पूर्ण

	rc = request_irq(gpmc->irq, gpmc_handle_irq, 0, "gpmc", gpmc);
	अगर (rc) अणु
		dev_err(gpmc->dev, "failed to request irq %d: %d\n",
			gpmc->irq, rc);
		irq_करोमुख्य_हटाओ(gpmc_irq_करोमुख्य);
		gpmc_irq_करोमुख्य = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gpmc_मुक्त_irq(काष्ठा gpmc_device *gpmc)
अणु
	पूर्णांक hwirq;

	मुक्त_irq(gpmc->irq, gpmc);

	क्रम (hwirq = 0; hwirq < gpmc->nirqs; hwirq++)
		irq_dispose_mapping(irq_find_mapping(gpmc_irq_करोमुख्य, hwirq));

	irq_करोमुख्य_हटाओ(gpmc_irq_करोमुख्य);
	gpmc_irq_करोमुख्य = शून्य;

	वापस 0;
पूर्ण

अटल व्योम gpmc_mem_निकास(व्योम)
अणु
	पूर्णांक cs;

	क्रम (cs = 0; cs < gpmc_cs_num; cs++) अणु
		अगर (!gpmc_cs_mem_enabled(cs))
			जारी;
		gpmc_cs_delete_mem(cs);
	पूर्ण
पूर्ण

अटल व्योम gpmc_mem_init(व्योम)
अणु
	पूर्णांक cs;

	gpmc_mem_root.start = GPMC_MEM_START;
	gpmc_mem_root.end = GPMC_MEM_END;

	/* Reserve all regions that has been set up by bootloader */
	क्रम (cs = 0; cs < gpmc_cs_num; cs++) अणु
		u32 base, size;

		अगर (!gpmc_cs_mem_enabled(cs))
			जारी;
		gpmc_cs_get_memconf(cs, &base, &size);
		अगर (gpmc_cs_insert_mem(cs, base, size)) अणु
			pr_warn("%s: disabling cs %d mapped at 0x%x-0x%x\n",
				__func__, cs, base, base + size);
			gpmc_cs_disable_mem(cs);
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 gpmc_round_ps_to_sync_clk(u32 समय_ps, u32 sync_clk)
अणु
	u32 temp;
	पूर्णांक भाग;

	भाग = gpmc_calc_भागider(sync_clk);
	temp = gpmc_ps_to_ticks(समय_ps);
	temp = (temp + भाग - 1) / भाग;
	वापस gpmc_ticks_to_ps(temp * भाग);
पूर्ण

/* XXX: can the cycles be aव्योमed ? */
अटल पूर्णांक gpmc_calc_sync_पढ़ो_timings(काष्ठा gpmc_timings *gpmc_t,
				       काष्ठा gpmc_device_timings *dev_t,
				       bool mux)
अणु
	u32 temp;

	/* adv_rd_off */
	temp = dev_t->t_avdp_r;
	/* XXX: mux check required ? */
	अगर (mux) अणु
		/* XXX: t_avdp not to be required क्रम sync, only added क्रम tusb
		 * this indirectly necessitates requirement of t_avdp_r and
		 * t_avdp_w instead of having a single t_avdp
		 */
		temp = max_t(u32, temp,	gpmc_t->clk_activation + dev_t->t_avdh);
		temp = max_t(u32, gpmc_t->adv_on + gpmc_ticks_to_ps(1), temp);
	पूर्ण
	gpmc_t->adv_rd_off = gpmc_round_ps_to_ticks(temp);

	/* oe_on */
	temp = dev_t->t_oeasu; /* XXX: हटाओ this ? */
	अगर (mux) अणु
		temp = max_t(u32, temp,	gpmc_t->clk_activation + dev_t->t_ach);
		temp = max_t(u32, temp, gpmc_t->adv_rd_off +
				gpmc_ticks_to_ps(dev_t->cyc_aavdh_oe));
	पूर्ण
	gpmc_t->oe_on = gpmc_round_ps_to_ticks(temp);

	/* access */
	/* XXX: any scope क्रम improvement ?, by combining oe_on
	 * and clk_activation, need to check whether
	 * access = clk_activation + round to sync clk ?
	 */
	temp = max_t(u32, dev_t->t_iaa,	dev_t->cyc_iaa * gpmc_t->sync_clk);
	temp += gpmc_t->clk_activation;
	अगर (dev_t->cyc_oe)
		temp = max_t(u32, temp, gpmc_t->oe_on +
				gpmc_ticks_to_ps(dev_t->cyc_oe));
	gpmc_t->access = gpmc_round_ps_to_ticks(temp);

	gpmc_t->oe_off = gpmc_t->access + gpmc_ticks_to_ps(1);
	gpmc_t->cs_rd_off = gpmc_t->oe_off;

	/* rd_cycle */
	temp = max_t(u32, dev_t->t_cez_r, dev_t->t_oez);
	temp = gpmc_round_ps_to_sync_clk(temp, gpmc_t->sync_clk) +
							gpmc_t->access;
	/* XXX: barter t_ce_rdyz with t_cez_r ? */
	अगर (dev_t->t_ce_rdyz)
		temp = max_t(u32, temp,	gpmc_t->cs_rd_off + dev_t->t_ce_rdyz);
	gpmc_t->rd_cycle = gpmc_round_ps_to_ticks(temp);

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_calc_sync_ग_लिखो_timings(काष्ठा gpmc_timings *gpmc_t,
					काष्ठा gpmc_device_timings *dev_t,
					bool mux)
अणु
	u32 temp;

	/* adv_wr_off */
	temp = dev_t->t_avdp_w;
	अगर (mux) अणु
		temp = max_t(u32, temp,
			gpmc_t->clk_activation + dev_t->t_avdh);
		temp = max_t(u32, gpmc_t->adv_on + gpmc_ticks_to_ps(1), temp);
	पूर्ण
	gpmc_t->adv_wr_off = gpmc_round_ps_to_ticks(temp);

	/* wr_data_mux_bus */
	temp = max_t(u32, dev_t->t_weasu,
			gpmc_t->clk_activation + dev_t->t_rdyo);
	/* XXX: shouldn't mux be kept as a whole क्रम wr_data_mux_bus ?,
	 * and in that हाल remember to handle we_on properly
	 */
	अगर (mux) अणु
		temp = max_t(u32, temp,
			gpmc_t->adv_wr_off + dev_t->t_aavdh);
		temp = max_t(u32, temp, gpmc_t->adv_wr_off +
				gpmc_ticks_to_ps(dev_t->cyc_aavdh_we));
	पूर्ण
	gpmc_t->wr_data_mux_bus = gpmc_round_ps_to_ticks(temp);

	/* we_on */
	अगर (gpmc_capability & GPMC_HAS_WR_DATA_MUX_BUS)
		gpmc_t->we_on = gpmc_round_ps_to_ticks(dev_t->t_weasu);
	अन्यथा
		gpmc_t->we_on = gpmc_t->wr_data_mux_bus;

	/* wr_access */
	/* XXX: gpmc_capability check reqd ? , even अगर not, will not harm */
	gpmc_t->wr_access = gpmc_t->access;

	/* we_off */
	temp = gpmc_t->we_on + dev_t->t_wpl;
	temp = max_t(u32, temp,
			gpmc_t->wr_access + gpmc_ticks_to_ps(1));
	temp = max_t(u32, temp,
		gpmc_t->we_on + gpmc_ticks_to_ps(dev_t->cyc_wpl));
	gpmc_t->we_off = gpmc_round_ps_to_ticks(temp);

	gpmc_t->cs_wr_off = gpmc_round_ps_to_ticks(gpmc_t->we_off +
							dev_t->t_wph);

	/* wr_cycle */
	temp = gpmc_round_ps_to_sync_clk(dev_t->t_cez_w, gpmc_t->sync_clk);
	temp += gpmc_t->wr_access;
	/* XXX: barter t_ce_rdyz with t_cez_w ? */
	अगर (dev_t->t_ce_rdyz)
		temp = max_t(u32, temp,
				 gpmc_t->cs_wr_off + dev_t->t_ce_rdyz);
	gpmc_t->wr_cycle = gpmc_round_ps_to_ticks(temp);

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_calc_async_पढ़ो_timings(काष्ठा gpmc_timings *gpmc_t,
					काष्ठा gpmc_device_timings *dev_t,
					bool mux)
अणु
	u32 temp;

	/* adv_rd_off */
	temp = dev_t->t_avdp_r;
	अगर (mux)
		temp = max_t(u32, gpmc_t->adv_on + gpmc_ticks_to_ps(1), temp);
	gpmc_t->adv_rd_off = gpmc_round_ps_to_ticks(temp);

	/* oe_on */
	temp = dev_t->t_oeasu;
	अगर (mux)
		temp = max_t(u32, temp, gpmc_t->adv_rd_off + dev_t->t_aavdh);
	gpmc_t->oe_on = gpmc_round_ps_to_ticks(temp);

	/* access */
	temp = max_t(u32, dev_t->t_iaa, /* XXX: हटाओ t_iaa in async ? */
		     gpmc_t->oe_on + dev_t->t_oe);
	temp = max_t(u32, temp, gpmc_t->cs_on + dev_t->t_ce);
	temp = max_t(u32, temp, gpmc_t->adv_on + dev_t->t_aa);
	gpmc_t->access = gpmc_round_ps_to_ticks(temp);

	gpmc_t->oe_off = gpmc_t->access + gpmc_ticks_to_ps(1);
	gpmc_t->cs_rd_off = gpmc_t->oe_off;

	/* rd_cycle */
	temp = max_t(u32, dev_t->t_rd_cycle,
			gpmc_t->cs_rd_off + dev_t->t_cez_r);
	temp = max_t(u32, temp, gpmc_t->oe_off + dev_t->t_oez);
	gpmc_t->rd_cycle = gpmc_round_ps_to_ticks(temp);

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_calc_async_ग_लिखो_timings(काष्ठा gpmc_timings *gpmc_t,
					 काष्ठा gpmc_device_timings *dev_t,
					 bool mux)
अणु
	u32 temp;

	/* adv_wr_off */
	temp = dev_t->t_avdp_w;
	अगर (mux)
		temp = max_t(u32, gpmc_t->adv_on + gpmc_ticks_to_ps(1), temp);
	gpmc_t->adv_wr_off = gpmc_round_ps_to_ticks(temp);

	/* wr_data_mux_bus */
	temp = dev_t->t_weasu;
	अगर (mux) अणु
		temp = max_t(u32, temp,	gpmc_t->adv_wr_off + dev_t->t_aavdh);
		temp = max_t(u32, temp, gpmc_t->adv_wr_off +
				gpmc_ticks_to_ps(dev_t->cyc_aavdh_we));
	पूर्ण
	gpmc_t->wr_data_mux_bus = gpmc_round_ps_to_ticks(temp);

	/* we_on */
	अगर (gpmc_capability & GPMC_HAS_WR_DATA_MUX_BUS)
		gpmc_t->we_on = gpmc_round_ps_to_ticks(dev_t->t_weasu);
	अन्यथा
		gpmc_t->we_on = gpmc_t->wr_data_mux_bus;

	/* we_off */
	temp = gpmc_t->we_on + dev_t->t_wpl;
	gpmc_t->we_off = gpmc_round_ps_to_ticks(temp);

	gpmc_t->cs_wr_off = gpmc_round_ps_to_ticks(gpmc_t->we_off +
							dev_t->t_wph);

	/* wr_cycle */
	temp = max_t(u32, dev_t->t_wr_cycle,
				gpmc_t->cs_wr_off + dev_t->t_cez_w);
	gpmc_t->wr_cycle = gpmc_round_ps_to_ticks(temp);

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_calc_sync_common_timings(काष्ठा gpmc_timings *gpmc_t,
			काष्ठा gpmc_device_timings *dev_t)
अणु
	u32 temp;

	gpmc_t->sync_clk = gpmc_calc_भागider(dev_t->clk) *
						gpmc_get_fclk_period();

	gpmc_t->page_burst_access = gpmc_round_ps_to_sync_clk(
					dev_t->t_bacc,
					gpmc_t->sync_clk);

	temp = max_t(u32, dev_t->t_ces, dev_t->t_avds);
	gpmc_t->clk_activation = gpmc_round_ps_to_ticks(temp);

	अगर (gpmc_calc_भागider(gpmc_t->sync_clk) != 1)
		वापस 0;

	अगर (dev_t->ce_xdelay)
		gpmc_t->bool_timings.cs_extra_delay = true;
	अगर (dev_t->avd_xdelay)
		gpmc_t->bool_timings.adv_extra_delay = true;
	अगर (dev_t->oe_xdelay)
		gpmc_t->bool_timings.oe_extra_delay = true;
	अगर (dev_t->we_xdelay)
		gpmc_t->bool_timings.we_extra_delay = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_calc_common_timings(काष्ठा gpmc_timings *gpmc_t,
				    काष्ठा gpmc_device_timings *dev_t,
				    bool sync)
अणु
	u32 temp;

	/* cs_on */
	gpmc_t->cs_on = gpmc_round_ps_to_ticks(dev_t->t_ceasu);

	/* adv_on */
	temp = dev_t->t_avdasu;
	अगर (dev_t->t_ce_avd)
		temp = max_t(u32, temp,
				gpmc_t->cs_on + dev_t->t_ce_avd);
	gpmc_t->adv_on = gpmc_round_ps_to_ticks(temp);

	अगर (sync)
		gpmc_calc_sync_common_timings(gpmc_t, dev_t);

	वापस 0;
पूर्ण

/*
 * TODO: हटाओ this function once all peripherals are confirmed to
 * work with generic timing. Simultaneously gpmc_cs_set_timings()
 * has to be modअगरied to handle timings in ps instead of ns
 */
अटल व्योम gpmc_convert_ps_to_ns(काष्ठा gpmc_timings *t)
अणु
	t->cs_on /= 1000;
	t->cs_rd_off /= 1000;
	t->cs_wr_off /= 1000;
	t->adv_on /= 1000;
	t->adv_rd_off /= 1000;
	t->adv_wr_off /= 1000;
	t->we_on /= 1000;
	t->we_off /= 1000;
	t->oe_on /= 1000;
	t->oe_off /= 1000;
	t->page_burst_access /= 1000;
	t->access /= 1000;
	t->rd_cycle /= 1000;
	t->wr_cycle /= 1000;
	t->bus_turnaround /= 1000;
	t->cycle2cycle_delay /= 1000;
	t->रुको_monitoring /= 1000;
	t->clk_activation /= 1000;
	t->wr_access /= 1000;
	t->wr_data_mux_bus /= 1000;
पूर्ण

पूर्णांक gpmc_calc_timings(काष्ठा gpmc_timings *gpmc_t,
		      काष्ठा gpmc_settings *gpmc_s,
		      काष्ठा gpmc_device_timings *dev_t)
अणु
	bool mux = false, sync = false;

	अगर (gpmc_s) अणु
		mux = gpmc_s->mux_add_data ? true : false;
		sync = (gpmc_s->sync_पढ़ो || gpmc_s->sync_ग_लिखो);
	पूर्ण

	स_रखो(gpmc_t, 0, माप(*gpmc_t));

	gpmc_calc_common_timings(gpmc_t, dev_t, sync);

	अगर (gpmc_s && gpmc_s->sync_पढ़ो)
		gpmc_calc_sync_पढ़ो_timings(gpmc_t, dev_t, mux);
	अन्यथा
		gpmc_calc_async_पढ़ो_timings(gpmc_t, dev_t, mux);

	अगर (gpmc_s && gpmc_s->sync_ग_लिखो)
		gpmc_calc_sync_ग_लिखो_timings(gpmc_t, dev_t, mux);
	अन्यथा
		gpmc_calc_async_ग_लिखो_timings(gpmc_t, dev_t, mux);

	/* TODO: हटाओ, see function definition */
	gpmc_convert_ps_to_ns(gpmc_t);

	वापस 0;
पूर्ण

/**
 * gpmc_cs_program_settings - programs non-timing related settings
 * @cs:		GPMC chip-select to program
 * @p:		poपूर्णांकer to GPMC settings काष्ठाure
 *
 * Programs non-timing related settings क्रम a GPMC chip-select, such as
 * bus-width, burst configuration, etc. Function should be called once
 * क्रम each chip-select that is being used and must be called beक्रमe
 * calling gpmc_cs_set_timings() as timing parameters in the CONFIG1
 * रेजिस्टर will be initialised to zero by this function. Returns 0 on
 * success and appropriate negative error code on failure.
 */
पूर्णांक gpmc_cs_program_settings(पूर्णांक cs, काष्ठा gpmc_settings *p)
अणु
	u32 config1;

	अगर ((!p->device_width) || (p->device_width > GPMC_DEVWIDTH_16BIT)) अणु
		pr_err("%s: invalid width %d!", __func__, p->device_width);
		वापस -EINVAL;
	पूर्ण

	/* Address-data multiplexing not supported क्रम न_अंकD devices */
	अगर (p->device_nand && p->mux_add_data) अणु
		pr_err("%s: invalid configuration!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर ((p->mux_add_data > GPMC_MUX_AD) ||
	    ((p->mux_add_data == GPMC_MUX_AAD) &&
	     !(gpmc_capability & GPMC_HAS_MUX_AAD))) अणु
		pr_err("%s: invalid multiplex configuration!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Page/burst mode supports lengths of 4, 8 and 16 bytes */
	अगर (p->burst_पढ़ो || p->burst_ग_लिखो) अणु
		चयन (p->burst_len) अणु
		हाल GPMC_BURST_4:
		हाल GPMC_BURST_8:
		हाल GPMC_BURST_16:
			अवरोध;
		शेष:
			pr_err("%s: invalid page/burst-length (%d)\n",
			       __func__, p->burst_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (p->रुको_pin > gpmc_nr_रुकोpins) अणु
		pr_err("%s: invalid wait-pin (%d)\n", __func__, p->रुको_pin);
		वापस -EINVAL;
	पूर्ण

	config1 = GPMC_CONFIG1_DEVICESIZE((p->device_width - 1));

	अगर (p->sync_पढ़ो)
		config1 |= GPMC_CONFIG1_READTYPE_SYNC;
	अगर (p->sync_ग_लिखो)
		config1 |= GPMC_CONFIG1_WRITETYPE_SYNC;
	अगर (p->रुको_on_पढ़ो)
		config1 |= GPMC_CONFIG1_WAIT_READ_MON;
	अगर (p->रुको_on_ग_लिखो)
		config1 |= GPMC_CONFIG1_WAIT_WRITE_MON;
	अगर (p->रुको_on_पढ़ो || p->रुको_on_ग_लिखो)
		config1 |= GPMC_CONFIG1_WAIT_PIN_SEL(p->रुको_pin);
	अगर (p->device_nand)
		config1	|= GPMC_CONFIG1_DEVICETYPE(GPMC_DEVICETYPE_न_अंकD);
	अगर (p->mux_add_data)
		config1	|= GPMC_CONFIG1_MUXTYPE(p->mux_add_data);
	अगर (p->burst_पढ़ो)
		config1 |= GPMC_CONFIG1_READMULTIPLE_SUPP;
	अगर (p->burst_ग_लिखो)
		config1 |= GPMC_CONFIG1_WRITEMULTIPLE_SUPP;
	अगर (p->burst_पढ़ो || p->burst_ग_लिखो) अणु
		config1 |= GPMC_CONFIG1_PAGE_LEN(p->burst_len >> 3);
		config1 |= p->burst_wrap ? GPMC_CONFIG1_WRAPBURST_SUPP : 0;
	पूर्ण

	gpmc_cs_ग_लिखो_reg(cs, GPMC_CS_CONFIG1, config1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpmc_dt_ids[] = अणु
	अणु .compatible = "ti,omap2420-gpmc" पूर्ण,
	अणु .compatible = "ti,omap2430-gpmc" पूर्ण,
	अणु .compatible = "ti,omap3430-gpmc" पूर्ण,	/* omap3430 & omap3630 */
	अणु .compatible = "ti,omap4430-gpmc" पूर्ण,	/* omap4430 & omap4460 & omap543x */
	अणु .compatible = "ti,am3352-gpmc" पूर्ण,	/* am335x devices */
	अणु पूर्ण
पूर्ण;

अटल व्योम gpmc_cs_set_name(पूर्णांक cs, स्थिर अक्षर *name)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];

	gpmc->name = name;
पूर्ण

अटल स्थिर अक्षर *gpmc_cs_get_name(पूर्णांक cs)
अणु
	काष्ठा gpmc_cs_data *gpmc = &gpmc_cs[cs];

	वापस gpmc->name;
पूर्ण

/**
 * gpmc_cs_remap - remaps a chip-select physical base address
 * @cs:		chip-select to remap
 * @base:	physical base address to re-map chip-select to
 *
 * Re-maps a chip-select to a new physical base address specअगरied by
 * "base". Returns 0 on success and appropriate negative error code
 * on failure.
 */
अटल पूर्णांक gpmc_cs_remap(पूर्णांक cs, u32 base)
अणु
	पूर्णांक ret;
	u32 old_base, size;

	अगर (cs >= gpmc_cs_num) अणु
		pr_err("%s: requested chip-select is disabled\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Make sure we ignore any device offsets from the GPMC partition
	 * allocated क्रम the chip select and that the new base confirms
	 * to the GPMC 16MB minimum granularity.
	 */
	base &= ~(SZ_16M - 1);

	gpmc_cs_get_memconf(cs, &old_base, &size);
	अगर (base == old_base)
		वापस 0;

	ret = gpmc_cs_delete_mem(cs);
	अगर (ret < 0)
		वापस ret;

	ret = gpmc_cs_insert_mem(cs, base, size);
	अगर (ret < 0)
		वापस ret;

	ret = gpmc_cs_set_memconf(cs, base, size);

	वापस ret;
पूर्ण

/**
 * gpmc_पढ़ो_settings_dt - पढ़ो gpmc settings from device-tree
 * @np:		poपूर्णांकer to device-tree node क्रम a gpmc child device
 * @p:		poपूर्णांकer to gpmc settings काष्ठाure
 *
 * Reads the GPMC settings क्रम a GPMC child device from device-tree and
 * stores them in the GPMC settings काष्ठाure passed. The GPMC settings
 * काष्ठाure is initialised to zero by this function and so any
 * previously stored settings will be cleared.
 */
व्योम gpmc_पढ़ो_settings_dt(काष्ठा device_node *np, काष्ठा gpmc_settings *p)
अणु
	स_रखो(p, 0, माप(काष्ठा gpmc_settings));

	p->sync_पढ़ो = of_property_पढ़ो_bool(np, "gpmc,sync-read");
	p->sync_ग_लिखो = of_property_पढ़ो_bool(np, "gpmc,sync-write");
	of_property_पढ़ो_u32(np, "gpmc,device-width", &p->device_width);
	of_property_पढ़ो_u32(np, "gpmc,mux-add-data", &p->mux_add_data);

	अगर (!of_property_पढ़ो_u32(np, "gpmc,burst-length", &p->burst_len)) अणु
		p->burst_wrap = of_property_पढ़ो_bool(np, "gpmc,burst-wrap");
		p->burst_पढ़ो = of_property_पढ़ो_bool(np, "gpmc,burst-read");
		p->burst_ग_लिखो = of_property_पढ़ो_bool(np, "gpmc,burst-write");
		अगर (!p->burst_पढ़ो && !p->burst_ग_लिखो)
			pr_warn("%s: page/burst-length set but not used!\n",
				__func__);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "gpmc,wait-pin", &p->रुको_pin)) अणु
		p->रुको_on_पढ़ो = of_property_पढ़ो_bool(np,
							"gpmc,wait-on-read");
		p->रुको_on_ग_लिखो = of_property_पढ़ो_bool(np,
							 "gpmc,wait-on-write");
		अगर (!p->रुको_on_पढ़ो && !p->रुको_on_ग_लिखो)
			pr_debug("%s: rd/wr wait monitoring not enabled!\n",
				 __func__);
	पूर्ण
पूर्ण

अटल व्योम __maybe_unused gpmc_पढ़ो_timings_dt(काष्ठा device_node *np,
						काष्ठा gpmc_timings *gpmc_t)
अणु
	काष्ठा gpmc_bool_timings *p;

	अगर (!np || !gpmc_t)
		वापस;

	स_रखो(gpmc_t, 0, माप(*gpmc_t));

	/* minimum घड़ी period क्रम syncronous mode */
	of_property_पढ़ो_u32(np, "gpmc,sync-clk-ps", &gpmc_t->sync_clk);

	/* chip select timtings */
	of_property_पढ़ो_u32(np, "gpmc,cs-on-ns", &gpmc_t->cs_on);
	of_property_पढ़ो_u32(np, "gpmc,cs-rd-off-ns", &gpmc_t->cs_rd_off);
	of_property_पढ़ो_u32(np, "gpmc,cs-wr-off-ns", &gpmc_t->cs_wr_off);

	/* ADV संकेत timings */
	of_property_पढ़ो_u32(np, "gpmc,adv-on-ns", &gpmc_t->adv_on);
	of_property_पढ़ो_u32(np, "gpmc,adv-rd-off-ns", &gpmc_t->adv_rd_off);
	of_property_पढ़ो_u32(np, "gpmc,adv-wr-off-ns", &gpmc_t->adv_wr_off);
	of_property_पढ़ो_u32(np, "gpmc,adv-aad-mux-on-ns",
			     &gpmc_t->adv_aad_mux_on);
	of_property_पढ़ो_u32(np, "gpmc,adv-aad-mux-rd-off-ns",
			     &gpmc_t->adv_aad_mux_rd_off);
	of_property_पढ़ो_u32(np, "gpmc,adv-aad-mux-wr-off-ns",
			     &gpmc_t->adv_aad_mux_wr_off);

	/* WE संकेत timings */
	of_property_पढ़ो_u32(np, "gpmc,we-on-ns", &gpmc_t->we_on);
	of_property_पढ़ो_u32(np, "gpmc,we-off-ns", &gpmc_t->we_off);

	/* OE संकेत timings */
	of_property_पढ़ो_u32(np, "gpmc,oe-on-ns", &gpmc_t->oe_on);
	of_property_पढ़ो_u32(np, "gpmc,oe-off-ns", &gpmc_t->oe_off);
	of_property_पढ़ो_u32(np, "gpmc,oe-aad-mux-on-ns",
			     &gpmc_t->oe_aad_mux_on);
	of_property_पढ़ो_u32(np, "gpmc,oe-aad-mux-off-ns",
			     &gpmc_t->oe_aad_mux_off);

	/* access and cycle timings */
	of_property_पढ़ो_u32(np, "gpmc,page-burst-access-ns",
			     &gpmc_t->page_burst_access);
	of_property_पढ़ो_u32(np, "gpmc,access-ns", &gpmc_t->access);
	of_property_पढ़ो_u32(np, "gpmc,rd-cycle-ns", &gpmc_t->rd_cycle);
	of_property_पढ़ो_u32(np, "gpmc,wr-cycle-ns", &gpmc_t->wr_cycle);
	of_property_पढ़ो_u32(np, "gpmc,bus-turnaround-ns",
			     &gpmc_t->bus_turnaround);
	of_property_पढ़ो_u32(np, "gpmc,cycle2cycle-delay-ns",
			     &gpmc_t->cycle2cycle_delay);
	of_property_पढ़ो_u32(np, "gpmc,wait-monitoring-ns",
			     &gpmc_t->रुको_monitoring);
	of_property_पढ़ो_u32(np, "gpmc,clk-activation-ns",
			     &gpmc_t->clk_activation);

	/* only applicable to OMAP3+ */
	of_property_पढ़ो_u32(np, "gpmc,wr-access-ns", &gpmc_t->wr_access);
	of_property_पढ़ो_u32(np, "gpmc,wr-data-mux-bus-ns",
			     &gpmc_t->wr_data_mux_bus);

	/* bool timing parameters */
	p = &gpmc_t->bool_timings;

	p->cycle2cycledअगरfcsen =
		of_property_पढ़ो_bool(np, "gpmc,cycle2cycle-diffcsen");
	p->cycle2cyclesamecsen =
		of_property_पढ़ो_bool(np, "gpmc,cycle2cycle-samecsen");
	p->we_extra_delay = of_property_पढ़ो_bool(np, "gpmc,we-extra-delay");
	p->oe_extra_delay = of_property_पढ़ो_bool(np, "gpmc,oe-extra-delay");
	p->adv_extra_delay = of_property_पढ़ो_bool(np, "gpmc,adv-extra-delay");
	p->cs_extra_delay = of_property_पढ़ो_bool(np, "gpmc,cs-extra-delay");
	p->समय_para_granularity =
		of_property_पढ़ो_bool(np, "gpmc,time-para-granularity");
पूर्ण

/**
 * gpmc_probe_generic_child - configures the gpmc क्रम a child device
 * @pdev:	poपूर्णांकer to gpmc platक्रमm device
 * @child:	poपूर्णांकer to device-tree node क्रम child device
 *
 * Allocates and configures a GPMC chip-select क्रम a child device.
 * Returns 0 on success and appropriate negative error code on failure.
 */
अटल पूर्णांक gpmc_probe_generic_child(काष्ठा platक्रमm_device *pdev,
				काष्ठा device_node *child)
अणु
	काष्ठा gpmc_settings gpmc_s;
	काष्ठा gpmc_timings gpmc_t;
	काष्ठा resource res;
	अचिन्हित दीर्घ base;
	स्थिर अक्षर *name;
	पूर्णांक ret, cs;
	u32 val;
	काष्ठा gpio_desc *रुकोpin_desc = शून्य;
	काष्ठा gpmc_device *gpmc = platक्रमm_get_drvdata(pdev);

	अगर (of_property_पढ़ो_u32(child, "reg", &cs) < 0) अणु
		dev_err(&pdev->dev, "%pOF has no 'reg' property\n",
			child);
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(child, 0, &res) < 0) अणु
		dev_err(&pdev->dev, "%pOF has malformed 'reg' property\n",
			child);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Check अगर we have multiple instances of the same device
	 * on a single chip select. If so, use the alपढ़ोy initialized
	 * timings.
	 */
	name = gpmc_cs_get_name(cs);
	अगर (name && of_node_name_eq(child, name))
		जाओ no_timings;

	ret = gpmc_cs_request(cs, resource_size(&res), &base);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot request GPMC CS %d\n", cs);
		वापस ret;
	पूर्ण
	gpmc_cs_set_name(cs, child->full_name);

	gpmc_पढ़ो_settings_dt(child, &gpmc_s);
	gpmc_पढ़ो_timings_dt(child, &gpmc_t);

	/*
	 * For some GPMC devices we still need to rely on the bootloader
	 * timings because the devices can be connected via FPGA.
	 * REVISIT: Add timing support from slls644g.pdf.
	 */
	अगर (!gpmc_t.cs_rd_off) अणु
		WARN(1, "enable GPMC debug to configure .dts timings for CS%i\n",
			cs);
		gpmc_cs_show_timings(cs,
				     "please add GPMC bootloader timings to .dts");
		जाओ no_timings;
	पूर्ण

	/* CS must be disabled जबतक making changes to gpmc configuration */
	gpmc_cs_disable_mem(cs);

	/*
	 * FIXME: gpmc_cs_request() will map the CS to an arbitrary
	 * location in the gpmc address space. When booting with
	 * device-tree we want the NOR flash to be mapped to the
	 * location specअगरied in the device-tree blob. So remap the
	 * CS to this location. Once DT migration is complete should
	 * just make gpmc_cs_request() map a specअगरic address.
	 */
	ret = gpmc_cs_remap(cs, res.start);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot remap GPMC CS %d to %pa\n",
			cs, &res.start);
		अगर (res.start < GPMC_MEM_START) अणु
			dev_info(&pdev->dev,
				 "GPMC CS %d start cannot be lesser than 0x%x\n",
				 cs, GPMC_MEM_START);
		पूर्ण अन्यथा अगर (res.end > GPMC_MEM_END) अणु
			dev_info(&pdev->dev,
				 "GPMC CS %d end cannot be greater than 0x%x\n",
				 cs, GPMC_MEM_END);
		पूर्ण
		जाओ err;
	पूर्ण

	अगर (of_node_name_eq(child, "nand")) अणु
		/* Warn about older DT blobs with no compatible property */
		अगर (!of_property_पढ़ो_bool(child, "compatible")) अणु
			dev_warn(&pdev->dev,
				 "Incompatible NAND node: missing compatible");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (of_node_name_eq(child, "onenand")) अणु
		/* Warn about older DT blobs with no compatible property */
		अगर (!of_property_पढ़ो_bool(child, "compatible")) अणु
			dev_warn(&pdev->dev,
				 "Incompatible OneNAND node: missing compatible");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(child, "ti,omap2-nand")) अणु
		/* न_अंकD specअगरic setup */
		val = 8;
		of_property_पढ़ो_u32(child, "nand-bus-width", &val);
		चयन (val) अणु
		हाल 8:
			gpmc_s.device_width = GPMC_DEVWIDTH_8BIT;
			अवरोध;
		हाल 16:
			gpmc_s.device_width = GPMC_DEVWIDTH_16BIT;
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "%pOFn: invalid 'nand-bus-width'\n",
				child);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		/* disable ग_लिखो protect */
		gpmc_configure(GPMC_CONFIG_WP, 0);
		gpmc_s.device_nand = true;
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_u32(child, "bank-width",
					   &gpmc_s.device_width);
		अगर (ret < 0 && !gpmc_s.device_width) अणु
			dev_err(&pdev->dev,
				"%pOF has no 'gpmc,device-width' property\n",
				child);
			जाओ err;
		पूर्ण
	पूर्ण

	/* Reserve रुको pin अगर it is required and valid */
	अगर (gpmc_s.रुको_on_पढ़ो || gpmc_s.रुको_on_ग_लिखो) अणु
		अचिन्हित पूर्णांक रुको_pin = gpmc_s.रुको_pin;

		रुकोpin_desc = gpiochip_request_own_desc(&gpmc->gpio_chip,
							 रुको_pin, "WAITPIN",
							 GPIO_ACTIVE_HIGH,
							 GPIOD_IN);
		अगर (IS_ERR(रुकोpin_desc)) अणु
			dev_err(&pdev->dev, "invalid wait-pin: %d\n", रुको_pin);
			ret = PTR_ERR(रुकोpin_desc);
			जाओ err;
		पूर्ण
	पूर्ण

	gpmc_cs_show_timings(cs, "before gpmc_cs_program_settings");

	ret = gpmc_cs_program_settings(cs, &gpmc_s);
	अगर (ret < 0)
		जाओ err_cs;

	ret = gpmc_cs_set_timings(cs, &gpmc_t, &gpmc_s);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to set gpmc timings for: %pOFn\n",
			child);
		जाओ err_cs;
	पूर्ण

	/* Clear limited address i.e. enable A26-A11 */
	val = gpmc_पढ़ो_reg(GPMC_CONFIG);
	val &= ~GPMC_CONFIG_LIMITEDADDRESS;
	gpmc_ग_लिखो_reg(GPMC_CONFIG, val);

	/* Enable CS region */
	gpmc_cs_enable_mem(cs);

no_timings:

	/* create platक्रमm device, शून्य on error or when disabled */
	अगर (!of_platक्रमm_device_create(child, शून्य, &pdev->dev))
		जाओ err_child_fail;

	/* is child a common bus? */
	अगर (of_match_node(of_शेष_bus_match_table, child))
		/* create children and other common bus children */
		अगर (of_platक्रमm_शेष_populate(child, शून्य, &pdev->dev))
			जाओ err_child_fail;

	वापस 0;

err_child_fail:

	dev_err(&pdev->dev, "failed to create gpmc child %pOFn\n", child);
	ret = -ENODEV;

err_cs:
	gpiochip_मुक्त_own_desc(रुकोpin_desc);
err:
	gpmc_cs_मुक्त(cs);

	वापस ret;
पूर्ण

अटल पूर्णांक gpmc_probe_dt(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(gpmc_dt_ids, &pdev->dev);

	अगर (!of_id)
		वापस 0;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "gpmc,num-cs",
				   &gpmc_cs_num);
	अगर (ret < 0) अणु
		pr_err("%s: number of chip-selects not defined\n", __func__);
		वापस ret;
	पूर्ण अन्यथा अगर (gpmc_cs_num < 1) अणु
		pr_err("%s: all chip-selects are disabled\n", __func__);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (gpmc_cs_num > GPMC_CS_NUM) अणु
		pr_err("%s: number of supported chip-selects cannot be > %d\n",
					 __func__, GPMC_CS_NUM);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "gpmc,num-waitpins",
				   &gpmc_nr_रुकोpins);
	अगर (ret < 0) अणु
		pr_err("%s: number of wait pins not found!\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpmc_probe_dt_children(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(pdev->dev.of_node, child) अणु
		ret = gpmc_probe_generic_child(pdev, child);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to probe DT child '%pOFn': %d\n",
				child, ret);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
व्योम gpmc_पढ़ो_settings_dt(काष्ठा device_node *np, काष्ठा gpmc_settings *p)
अणु
	स_रखो(p, 0, माप(*p));
पूर्ण
अटल पूर्णांक gpmc_probe_dt(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल व्योम gpmc_probe_dt_children(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक gpmc_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस 1;	/* we're input only */
पूर्ण

अटल पूर्णांक gpmc_gpio_direction_input(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	वापस 0;	/* we're input only */
पूर्ण

अटल पूर्णांक gpmc_gpio_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	वापस -EINVAL;	/* we're input only */
पूर्ण

अटल व्योम gpmc_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			  पूर्णांक value)
अणु
पूर्ण

अटल पूर्णांक gpmc_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	u32 reg;

	offset += 8;

	reg = gpmc_पढ़ो_reg(GPMC_STATUS) & BIT(offset);

	वापस !!reg;
पूर्ण

अटल पूर्णांक gpmc_gpio_init(काष्ठा gpmc_device *gpmc)
अणु
	पूर्णांक ret;

	gpmc->gpio_chip.parent = gpmc->dev;
	gpmc->gpio_chip.owner = THIS_MODULE;
	gpmc->gpio_chip.label = DEVICE_NAME;
	gpmc->gpio_chip.ngpio = gpmc_nr_रुकोpins;
	gpmc->gpio_chip.get_direction = gpmc_gpio_get_direction;
	gpmc->gpio_chip.direction_input = gpmc_gpio_direction_input;
	gpmc->gpio_chip.direction_output = gpmc_gpio_direction_output;
	gpmc->gpio_chip.set = gpmc_gpio_set;
	gpmc->gpio_chip.get = gpmc_gpio_get;
	gpmc->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(gpmc->dev, &gpmc->gpio_chip, शून्य);
	अगर (ret < 0) अणु
		dev_err(gpmc->dev, "could not register gpio chip: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	u32 l;
	काष्ठा resource *res;
	काष्ठा gpmc_device *gpmc;

	gpmc = devm_kzalloc(&pdev->dev, माप(*gpmc), GFP_KERNEL);
	अगर (!gpmc)
		वापस -ENOMEM;

	gpmc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, gpmc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	gpmc_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(gpmc_base))
		वापस PTR_ERR(gpmc_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get resource: irq\n");
		वापस -ENOENT;
	पूर्ण

	gpmc->irq = res->start;

	gpmc_l3_clk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(gpmc_l3_clk)) अणु
		dev_err(&pdev->dev, "Failed to get GPMC fck\n");
		वापस PTR_ERR(gpmc_l3_clk);
	पूर्ण

	अगर (!clk_get_rate(gpmc_l3_clk)) अणु
		dev_err(&pdev->dev, "Invalid GPMC fck clock rate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdev->dev.of_node) अणु
		rc = gpmc_probe_dt(pdev);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		gpmc_cs_num = GPMC_CS_NUM;
		gpmc_nr_रुकोpins = GPMC_NR_WAITPINS;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	l = gpmc_पढ़ो_reg(GPMC_REVISION);

	/*
	 * FIXME: Once device-tree migration is complete the below flags
	 * should be populated based upon the device-tree compatible
	 * string. For now just use the IP revision. OMAP3+ devices have
	 * the wr_access and wr_data_mux_bus रेजिस्टर fields. OMAP4+
	 * devices support the addr-addr-data multiplex protocol.
	 *
	 * GPMC IP revisions:
	 * - OMAP24xx			= 2.0
	 * - OMAP3xxx			= 5.0
	 * - OMAP44xx/54xx/AM335x	= 6.0
	 */
	अगर (GPMC_REVISION_MAJOR(l) > 0x4)
		gpmc_capability = GPMC_HAS_WR_ACCESS | GPMC_HAS_WR_DATA_MUX_BUS;
	अगर (GPMC_REVISION_MAJOR(l) > 0x5)
		gpmc_capability |= GPMC_HAS_MUX_AAD;
	dev_info(gpmc->dev, "GPMC revision %d.%d\n", GPMC_REVISION_MAJOR(l),
		 GPMC_REVISION_MINOR(l));

	gpmc_mem_init();
	rc = gpmc_gpio_init(gpmc);
	अगर (rc)
		जाओ gpio_init_failed;

	gpmc->nirqs = GPMC_NR_न_अंकD_IRQS + gpmc_nr_रुकोpins;
	rc = gpmc_setup_irq(gpmc);
	अगर (rc) अणु
		dev_err(gpmc->dev, "gpmc_setup_irq failed\n");
		जाओ gpio_init_failed;
	पूर्ण

	gpmc_probe_dt_children(pdev);

	वापस 0;

gpio_init_failed:
	gpmc_mem_निकास();
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस rc;
पूर्ण

अटल पूर्णांक gpmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpmc_device *gpmc = platक्रमm_get_drvdata(pdev);

	gpmc_मुक्त_irq(gpmc);
	gpmc_mem_निकास();
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpmc_suspend(काष्ठा device *dev)
अणु
	omap3_gpmc_save_context();
	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक gpmc_resume(काष्ठा device *dev)
अणु
	pm_runसमय_get_sync(dev);
	omap3_gpmc_restore_context();
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(gpmc_pm_ops, gpmc_suspend, gpmc_resume);

अटल काष्ठा platक्रमm_driver gpmc_driver = अणु
	.probe		= gpmc_probe,
	.हटाओ		= gpmc_हटाओ,
	.driver		= अणु
		.name	= DEVICE_NAME,
		.of_match_table = of_match_ptr(gpmc_dt_ids),
		.pm	= &gpmc_pm_ops,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक gpmc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpmc_driver);
पूर्ण
postcore_initcall(gpmc_init);

अटल काष्ठा omap3_gpmc_regs gpmc_context;

व्योम omap3_gpmc_save_context(व्योम)
अणु
	पूर्णांक i;

	अगर (!gpmc_base)
		वापस;

	gpmc_context.sysconfig = gpmc_पढ़ो_reg(GPMC_SYSCONFIG);
	gpmc_context.irqenable = gpmc_पढ़ो_reg(GPMC_IRQENABLE);
	gpmc_context.समयout_ctrl = gpmc_पढ़ो_reg(GPMC_TIMEOUT_CONTROL);
	gpmc_context.config = gpmc_पढ़ो_reg(GPMC_CONFIG);
	gpmc_context.prefetch_config1 = gpmc_पढ़ो_reg(GPMC_PREFETCH_CONFIG1);
	gpmc_context.prefetch_config2 = gpmc_पढ़ो_reg(GPMC_PREFETCH_CONFIG2);
	gpmc_context.prefetch_control = gpmc_पढ़ो_reg(GPMC_PREFETCH_CONTROL);
	क्रम (i = 0; i < gpmc_cs_num; i++) अणु
		gpmc_context.cs_context[i].is_valid = gpmc_cs_mem_enabled(i);
		अगर (gpmc_context.cs_context[i].is_valid) अणु
			gpmc_context.cs_context[i].config1 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG1);
			gpmc_context.cs_context[i].config2 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG2);
			gpmc_context.cs_context[i].config3 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG3);
			gpmc_context.cs_context[i].config4 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG4);
			gpmc_context.cs_context[i].config5 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG5);
			gpmc_context.cs_context[i].config6 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG6);
			gpmc_context.cs_context[i].config7 =
				gpmc_cs_पढ़ो_reg(i, GPMC_CS_CONFIG7);
		पूर्ण
	पूर्ण
पूर्ण

व्योम omap3_gpmc_restore_context(व्योम)
अणु
	पूर्णांक i;

	अगर (!gpmc_base)
		वापस;

	gpmc_ग_लिखो_reg(GPMC_SYSCONFIG, gpmc_context.sysconfig);
	gpmc_ग_लिखो_reg(GPMC_IRQENABLE, gpmc_context.irqenable);
	gpmc_ग_लिखो_reg(GPMC_TIMEOUT_CONTROL, gpmc_context.समयout_ctrl);
	gpmc_ग_लिखो_reg(GPMC_CONFIG, gpmc_context.config);
	gpmc_ग_लिखो_reg(GPMC_PREFETCH_CONFIG1, gpmc_context.prefetch_config1);
	gpmc_ग_लिखो_reg(GPMC_PREFETCH_CONFIG2, gpmc_context.prefetch_config2);
	gpmc_ग_लिखो_reg(GPMC_PREFETCH_CONTROL, gpmc_context.prefetch_control);
	क्रम (i = 0; i < gpmc_cs_num; i++) अणु
		अगर (gpmc_context.cs_context[i].is_valid) अणु
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG1,
				gpmc_context.cs_context[i].config1);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG2,
				gpmc_context.cs_context[i].config2);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG3,
				gpmc_context.cs_context[i].config3);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG4,
				gpmc_context.cs_context[i].config4);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG5,
				gpmc_context.cs_context[i].config5);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG6,
				gpmc_context.cs_context[i].config6);
			gpmc_cs_ग_लिखो_reg(i, GPMC_CS_CONFIG7,
				gpmc_context.cs_context[i].config7);
		पूर्ण
	पूर्ण
पूर्ण
