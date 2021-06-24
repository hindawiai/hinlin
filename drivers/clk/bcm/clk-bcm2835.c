<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010,2015 Broadcom
 * Copyright (C) 2012 Stephen Warren
 */

/**
 * DOC: BCM2835 CPRMAN (घड़ी manager क्रम the "audio" करोमुख्य)
 *
 * The घड़ी tree on the 2835 has several levels.  There's a root
 * oscillator running at 19.2Mhz.  After the oscillator there are 5
 * PLLs, roughly भागided as "camera", "ARM", "core", "DSI displays",
 * and "HDMI displays".  Those 5 PLLs each can भागide their output to
 * produce up to 4 channels.  Finally, there is the level of घड़ीs to
 * be consumed by other hardware components (like "H264" or "HDMI
 * state machine"), which भागide off of some subset of the PLL
 * channels.
 *
 * All of the घड़ीs in the tree are exposed in the DT, because the DT
 * may want to make assignments of the final layer of घड़ीs to the
 * PLL channels, and some components of the hardware will actually
 * skip layers of the tree (क्रम example, the pixel घड़ी comes
 * directly from the PLLH PIX channel without using a CM_*CTL घड़ी
 * generator).
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <dt-bindings/घड़ी/bcm2835.h>

#घोषणा CM_PASSWORD		0x5a000000

#घोषणा CM_GNRICCTL		0x000
#घोषणा CM_GNRICDIV		0x004
# define CM_DIV_FRAC_BITS	12
# define CM_DIV_FRAC_MASK	GENMASK(CM_DIV_FRAC_BITS - 1, 0)

#घोषणा CM_VPUCTL		0x008
#घोषणा CM_VPUDIV		0x00c
#घोषणा CM_SYSCTL		0x010
#घोषणा CM_SYSDIV		0x014
#घोषणा CM_PERIACTL		0x018
#घोषणा CM_PERIADIV		0x01c
#घोषणा CM_PERIICTL		0x020
#घोषणा CM_PERIIDIV		0x024
#घोषणा CM_H264CTL		0x028
#घोषणा CM_H264DIV		0x02c
#घोषणा CM_ISPCTL		0x030
#घोषणा CM_ISPDIV		0x034
#घोषणा CM_V3DCTL		0x038
#घोषणा CM_V3DDIV		0x03c
#घोषणा CM_CAM0CTL		0x040
#घोषणा CM_CAM0DIV		0x044
#घोषणा CM_CAM1CTL		0x048
#घोषणा CM_CAM1DIV		0x04c
#घोषणा CM_CCP2CTL		0x050
#घोषणा CM_CCP2DIV		0x054
#घोषणा CM_DSI0ECTL		0x058
#घोषणा CM_DSI0EDIV		0x05c
#घोषणा CM_DSI0PCTL		0x060
#घोषणा CM_DSI0PDIV		0x064
#घोषणा CM_DPICTL		0x068
#घोषणा CM_DPIDIV		0x06c
#घोषणा CM_GP0CTL		0x070
#घोषणा CM_GP0DIV		0x074
#घोषणा CM_GP1CTL		0x078
#घोषणा CM_GP1DIV		0x07c
#घोषणा CM_GP2CTL		0x080
#घोषणा CM_GP2DIV		0x084
#घोषणा CM_HSMCTL		0x088
#घोषणा CM_HSMDIV		0x08c
#घोषणा CM_OTPCTL		0x090
#घोषणा CM_OTPDIV		0x094
#घोषणा CM_PCMCTL		0x098
#घोषणा CM_PCMDIV		0x09c
#घोषणा CM_PWMCTL		0x0a0
#घोषणा CM_PWMDIV		0x0a4
#घोषणा CM_SLIMCTL		0x0a8
#घोषणा CM_SLIMDIV		0x0ac
#घोषणा CM_SMICTL		0x0b0
#घोषणा CM_SMIDIV		0x0b4
/* no definition क्रम 0x0b8  and 0x0bc */
#घोषणा CM_TCNTCTL		0x0c0
# define CM_TCNT_SRC1_SHIFT		12
#घोषणा CM_TCNTCNT		0x0c4
#घोषणा CM_TECCTL		0x0c8
#घोषणा CM_TECDIV		0x0cc
#घोषणा CM_TD0CTL		0x0d0
#घोषणा CM_TD0DIV		0x0d4
#घोषणा CM_TD1CTL		0x0d8
#घोषणा CM_TD1DIV		0x0dc
#घोषणा CM_TSENSCTL		0x0e0
#घोषणा CM_TSENSDIV		0x0e4
#घोषणा CM_TIMERCTL		0x0e8
#घोषणा CM_TIMERDIV		0x0ec
#घोषणा CM_UARTCTL		0x0f0
#घोषणा CM_UARTDIV		0x0f4
#घोषणा CM_VECCTL		0x0f8
#घोषणा CM_VECDIV		0x0fc
#घोषणा CM_PULSECTL		0x190
#घोषणा CM_PULSEDIV		0x194
#घोषणा CM_SDCCTL		0x1a8
#घोषणा CM_SDCDIV		0x1ac
#घोषणा CM_ARMCTL		0x1b0
#घोषणा CM_AVEOCTL		0x1b8
#घोषणा CM_AVEODIV		0x1bc
#घोषणा CM_EMMCCTL		0x1c0
#घोषणा CM_EMMCDIV		0x1c4
#घोषणा CM_EMMC2CTL		0x1d0
#घोषणा CM_EMMC2DIV		0x1d4

/* General bits क्रम the CM_*CTL regs */
# define CM_ENABLE			BIT(4)
# define CM_KILL			BIT(5)
# define CM_GATE_BIT			6
# define CM_GATE			BIT(CM_GATE_BIT)
# define CM_BUSY			BIT(7)
# define CM_BUSYD			BIT(8)
# define CM_FRAC			BIT(9)
# define CM_SRC_SHIFT			0
# define CM_SRC_BITS			4
# define CM_SRC_MASK			0xf
# define CM_SRC_GND			0
# define CM_SRC_OSC			1
# define CM_SRC_TESTDEBUG0		2
# define CM_SRC_TESTDEBUG1		3
# define CM_SRC_PLLA_CORE		4
# define CM_SRC_PLLA_PER		4
# define CM_SRC_PLLC_CORE0		5
# define CM_SRC_PLLC_PER		5
# define CM_SRC_PLLC_CORE1		8
# define CM_SRC_PLLD_CORE		6
# define CM_SRC_PLLD_PER		6
# define CM_SRC_PLLH_AUX		7
# define CM_SRC_PLLC_CORE1		8
# define CM_SRC_PLLC_CORE2		9

#घोषणा CM_OSCCOUNT		0x100

#घोषणा CM_PLLA			0x104
# define CM_PLL_ANARST			BIT(8)
# define CM_PLLA_HOLDPER		BIT(7)
# define CM_PLLA_LOADPER		BIT(6)
# define CM_PLLA_HOLDCORE		BIT(5)
# define CM_PLLA_LOADCORE		BIT(4)
# define CM_PLLA_HOLDCCP2		BIT(3)
# define CM_PLLA_LOADCCP2		BIT(2)
# define CM_PLLA_HOLDDSI0		BIT(1)
# define CM_PLLA_LOADDSI0		BIT(0)

#घोषणा CM_PLLC			0x108
# define CM_PLLC_HOLDPER		BIT(7)
# define CM_PLLC_LOADPER		BIT(6)
# define CM_PLLC_HOLDCORE2		BIT(5)
# define CM_PLLC_LOADCORE2		BIT(4)
# define CM_PLLC_HOLDCORE1		BIT(3)
# define CM_PLLC_LOADCORE1		BIT(2)
# define CM_PLLC_HOLDCORE0		BIT(1)
# define CM_PLLC_LOADCORE0		BIT(0)

#घोषणा CM_PLLD			0x10c
# define CM_PLLD_HOLDPER		BIT(7)
# define CM_PLLD_LOADPER		BIT(6)
# define CM_PLLD_HOLDCORE		BIT(5)
# define CM_PLLD_LOADCORE		BIT(4)
# define CM_PLLD_HOLDDSI1		BIT(3)
# define CM_PLLD_LOADDSI1		BIT(2)
# define CM_PLLD_HOLDDSI0		BIT(1)
# define CM_PLLD_LOADDSI0		BIT(0)

#घोषणा CM_PLLH			0x110
# define CM_PLLH_LOADRCAL		BIT(2)
# define CM_PLLH_LOADAUX		BIT(1)
# define CM_PLLH_LOADPIX		BIT(0)

#घोषणा CM_LOCK			0x114
# define CM_LOCK_FLOCKH			BIT(12)
# define CM_LOCK_FLOCKD			BIT(11)
# define CM_LOCK_FLOCKC			BIT(10)
# define CM_LOCK_FLOCKB			BIT(9)
# define CM_LOCK_FLOCKA			BIT(8)

#घोषणा CM_EVENT		0x118
#घोषणा CM_DSI1ECTL		0x158
#घोषणा CM_DSI1EDIV		0x15c
#घोषणा CM_DSI1PCTL		0x160
#घोषणा CM_DSI1PDIV		0x164
#घोषणा CM_DFTCTL		0x168
#घोषणा CM_DFTDIV		0x16c

#घोषणा CM_PLLB			0x170
# define CM_PLLB_HOLDARM		BIT(1)
# define CM_PLLB_LOADARM		BIT(0)

#घोषणा A2W_PLLA_CTRL		0x1100
#घोषणा A2W_PLLC_CTRL		0x1120
#घोषणा A2W_PLLD_CTRL		0x1140
#घोषणा A2W_PLLH_CTRL		0x1160
#घोषणा A2W_PLLB_CTRL		0x11e0
# define A2W_PLL_CTRL_PRST_DISABLE	BIT(17)
# define A2W_PLL_CTRL_PWRDN		BIT(16)
# define A2W_PLL_CTRL_PDIV_MASK		0x000007000
# define A2W_PLL_CTRL_PDIV_SHIFT	12
# define A2W_PLL_CTRL_NDIV_MASK		0x0000003ff
# define A2W_PLL_CTRL_NDIV_SHIFT	0

#घोषणा A2W_PLLA_ANA0		0x1010
#घोषणा A2W_PLLC_ANA0		0x1030
#घोषणा A2W_PLLD_ANA0		0x1050
#घोषणा A2W_PLLH_ANA0		0x1070
#घोषणा A2W_PLLB_ANA0		0x10f0

#घोषणा A2W_PLL_KA_SHIFT	7
#घोषणा A2W_PLL_KA_MASK		GENMASK(9, 7)
#घोषणा A2W_PLL_KI_SHIFT	19
#घोषणा A2W_PLL_KI_MASK		GENMASK(21, 19)
#घोषणा A2W_PLL_KP_SHIFT	15
#घोषणा A2W_PLL_KP_MASK		GENMASK(18, 15)

#घोषणा A2W_PLLH_KA_SHIFT	19
#घोषणा A2W_PLLH_KA_MASK	GENMASK(21, 19)
#घोषणा A2W_PLLH_KI_LOW_SHIFT	22
#घोषणा A2W_PLLH_KI_LOW_MASK	GENMASK(23, 22)
#घोषणा A2W_PLLH_KI_HIGH_SHIFT	0
#घोषणा A2W_PLLH_KI_HIGH_MASK	GENMASK(0, 0)
#घोषणा A2W_PLLH_KP_SHIFT	1
#घोषणा A2W_PLLH_KP_MASK	GENMASK(4, 1)

#घोषणा A2W_XOSC_CTRL		0x1190
# define A2W_XOSC_CTRL_PLLB_ENABLE	BIT(7)
# define A2W_XOSC_CTRL_PLLA_ENABLE	BIT(6)
# define A2W_XOSC_CTRL_PLLD_ENABLE	BIT(5)
# define A2W_XOSC_CTRL_DDR_ENABLE	BIT(4)
# define A2W_XOSC_CTRL_CPR1_ENABLE	BIT(3)
# define A2W_XOSC_CTRL_USB_ENABLE	BIT(2)
# define A2W_XOSC_CTRL_HDMI_ENABLE	BIT(1)
# define A2W_XOSC_CTRL_PLLC_ENABLE	BIT(0)

#घोषणा A2W_PLLA_FRAC		0x1200
#घोषणा A2W_PLLC_FRAC		0x1220
#घोषणा A2W_PLLD_FRAC		0x1240
#घोषणा A2W_PLLH_FRAC		0x1260
#घोषणा A2W_PLLB_FRAC		0x12e0
# define A2W_PLL_FRAC_MASK		((1 << A2W_PLL_FRAC_BITS) - 1)
# define A2W_PLL_FRAC_BITS		20

#घोषणा A2W_PLL_CHANNEL_DISABLE		BIT(8)
#घोषणा A2W_PLL_DIV_BITS		8
#घोषणा A2W_PLL_DIV_SHIFT		0

#घोषणा A2W_PLLA_DSI0		0x1300
#घोषणा A2W_PLLA_CORE		0x1400
#घोषणा A2W_PLLA_PER		0x1500
#घोषणा A2W_PLLA_CCP2		0x1600

#घोषणा A2W_PLLC_CORE2		0x1320
#घोषणा A2W_PLLC_CORE1		0x1420
#घोषणा A2W_PLLC_PER		0x1520
#घोषणा A2W_PLLC_CORE0		0x1620

#घोषणा A2W_PLLD_DSI0		0x1340
#घोषणा A2W_PLLD_CORE		0x1440
#घोषणा A2W_PLLD_PER		0x1540
#घोषणा A2W_PLLD_DSI1		0x1640

#घोषणा A2W_PLLH_AUX		0x1360
#घोषणा A2W_PLLH_RCAL		0x1460
#घोषणा A2W_PLLH_PIX		0x1560
#घोषणा A2W_PLLH_STS		0x1660

#घोषणा A2W_PLLH_CTRLR		0x1960
#घोषणा A2W_PLLH_FRACR		0x1a60
#घोषणा A2W_PLLH_AUXR		0x1b60
#घोषणा A2W_PLLH_RCALR		0x1c60
#घोषणा A2W_PLLH_PIXR		0x1d60
#घोषणा A2W_PLLH_STSR		0x1e60

#घोषणा A2W_PLLB_ARM		0x13e0
#घोषणा A2W_PLLB_SP0		0x14e0
#घोषणा A2W_PLLB_SP1		0x15e0
#घोषणा A2W_PLLB_SP2		0x16e0

#घोषणा LOCK_TIMEOUT_NS		100000000
#घोषणा BCM2835_MAX_FB_RATE	1750000000u

#घोषणा SOC_BCM2835		BIT(0)
#घोषणा SOC_BCM2711		BIT(1)
#घोषणा SOC_ALL			(SOC_BCM2835 | SOC_BCM2711)

/*
 * Names of घड़ीs used within the driver that need to be replaced
 * with an बाह्यal parent's name.  This array is in the order that
 * the घड़ीs node in the DT references बाह्यal घड़ीs.
 */
अटल स्थिर अक्षर *स्थिर cprman_parent_names[] = अणु
	"xosc",
	"dsi0_byte",
	"dsi0_ddr2",
	"dsi0_ddr",
	"dsi1_byte",
	"dsi1_ddr2",
	"dsi1_ddr",
पूर्ण;

काष्ठा bcm2835_cprman अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	spinlock_t regs_lock; /* spinlock क्रम all घड़ीs */
	अचिन्हित पूर्णांक soc;

	/*
	 * Real names of cprman घड़ी parents looked up through
	 * of_clk_get_parent_name(), which will be used in the
	 * parent_names[] arrays क्रम घड़ी registration.
	 */
	स्थिर अक्षर *real_parent_names[ARRAY_SIZE(cprman_parent_names)];

	/* Must be last */
	काष्ठा clk_hw_onecell_data onecell;
पूर्ण;

काष्ठा cprman_plat_data अणु
	अचिन्हित पूर्णांक soc;
पूर्ण;

अटल अंतरभूत व्योम cprman_ग_लिखो(काष्ठा bcm2835_cprman *cprman, u32 reg, u32 val)
अणु
	ग_लिखोl(CM_PASSWORD | val, cprman->regs + reg);
पूर्ण

अटल अंतरभूत u32 cprman_पढ़ो(काष्ठा bcm2835_cprman *cprman, u32 reg)
अणु
	वापस पढ़ोl(cprman->regs + reg);
पूर्ण

/* Does a cycle of measuring a घड़ी through the TCNT घड़ी, which may
 * source from many other घड़ीs in the प्रणाली.
 */
अटल अचिन्हित दीर्घ bcm2835_measure_tcnt_mux(काष्ठा bcm2835_cprman *cprman,
					      u32 tcnt_mux)
अणु
	u32 osccount = 19200; /* 1ms */
	u32 count;
	kसमय_प्रकार समयout;

	spin_lock(&cprman->regs_lock);

	cprman_ग_लिखो(cprman, CM_TCNTCTL, CM_KILL);

	cprman_ग_लिखो(cprman, CM_TCNTCTL,
		     (tcnt_mux & CM_SRC_MASK) |
		     (tcnt_mux >> CM_SRC_BITS) << CM_TCNT_SRC1_SHIFT);

	cprman_ग_लिखो(cprman, CM_OSCCOUNT, osccount);

	/* करो a kind delay at the start */
	mdelay(1);

	/* Finish off whatever is left of OSCCOUNT */
	समयout = kसमय_add_ns(kसमय_get(), LOCK_TIMEOUT_NS);
	जबतक (cprman_पढ़ो(cprman, CM_OSCCOUNT)) अणु
		अगर (kसमय_after(kसमय_get(), समयout)) अणु
			dev_err(cprman->dev, "timeout waiting for OSCCOUNT\n");
			count = 0;
			जाओ out;
		पूर्ण
		cpu_relax();
	पूर्ण

	/* Wait क्रम BUSY to clear. */
	समयout = kसमय_add_ns(kसमय_get(), LOCK_TIMEOUT_NS);
	जबतक (cprman_पढ़ो(cprman, CM_TCNTCTL) & CM_BUSY) अणु
		अगर (kसमय_after(kसमय_get(), समयout)) अणु
			dev_err(cprman->dev, "timeout waiting for !BUSY\n");
			count = 0;
			जाओ out;
		पूर्ण
		cpu_relax();
	पूर्ण

	count = cprman_पढ़ो(cprman, CM_TCNTCNT);

	cprman_ग_लिखो(cprman, CM_TCNTCTL, 0);

out:
	spin_unlock(&cprman->regs_lock);

	वापस count * 1000;
पूर्ण

अटल व्योम bcm2835_debugfs_regset(काष्ठा bcm2835_cprman *cprman, u32 base,
				   स्थिर काष्ठा debugfs_reg32 *regs,
				   माप_प्रकार nregs, काष्ठा dentry *dentry)
अणु
	काष्ठा debugfs_regset32 *regset;

	regset = devm_kzalloc(cprman->dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस;

	regset->regs = regs;
	regset->nregs = nregs;
	regset->base = cprman->regs + base;

	debugfs_create_regset32("regdump", S_IRUGO, dentry, regset);
पूर्ण

काष्ठा bcm2835_pll_data अणु
	स्थिर अक्षर *name;
	u32 cm_ctrl_reg;
	u32 a2w_ctrl_reg;
	u32 frac_reg;
	u32 ana_reg_base;
	u32 reference_enable_mask;
	/* Bit in CM_LOCK to indicate when the PLL has locked. */
	u32 lock_mask;
	u32 flags;

	स्थिर काष्ठा bcm2835_pll_ana_bits *ana;

	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
	/*
	 * Highest rate क्रम the VCO beक्रमe we have to use the
	 * pre-भागide-by-2.
	 */
	अचिन्हित दीर्घ max_fb_rate;
पूर्ण;

काष्ठा bcm2835_pll_ana_bits अणु
	u32 mask0;
	u32 set0;
	u32 mask1;
	u32 set1;
	u32 mask3;
	u32 set3;
	u32 fb_preभाग_mask;
पूर्ण;

अटल स्थिर काष्ठा bcm2835_pll_ana_bits bcm2835_ana_शेष = अणु
	.mask0 = 0,
	.set0 = 0,
	.mask1 = A2W_PLL_KI_MASK | A2W_PLL_KP_MASK,
	.set1 = (2 << A2W_PLL_KI_SHIFT) | (8 << A2W_PLL_KP_SHIFT),
	.mask3 = A2W_PLL_KA_MASK,
	.set3 = (2 << A2W_PLL_KA_SHIFT),
	.fb_preभाग_mask = BIT(14),
पूर्ण;

अटल स्थिर काष्ठा bcm2835_pll_ana_bits bcm2835_ana_pllh = अणु
	.mask0 = A2W_PLLH_KA_MASK | A2W_PLLH_KI_LOW_MASK,
	.set0 = (2 << A2W_PLLH_KA_SHIFT) | (2 << A2W_PLLH_KI_LOW_SHIFT),
	.mask1 = A2W_PLLH_KI_HIGH_MASK | A2W_PLLH_KP_MASK,
	.set1 = (6 << A2W_PLLH_KP_SHIFT),
	.mask3 = 0,
	.set3 = 0,
	.fb_preभाग_mask = BIT(11),
पूर्ण;

काष्ठा bcm2835_pll_भागider_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *source_pll;

	u32 cm_reg;
	u32 a2w_reg;

	u32 load_mask;
	u32 hold_mask;
	u32 fixed_भागider;
	u32 flags;
पूर्ण;

काष्ठा bcm2835_घड़ी_data अणु
	स्थिर अक्षर *name;

	स्थिर अक्षर *स्थिर *parents;
	पूर्णांक num_mux_parents;

	/* Biपंचांगap encoding which parents accept rate change propagation. */
	अचिन्हित पूर्णांक set_rate_parent;

	u32 ctl_reg;
	u32 भाग_reg;

	/* Number of पूर्णांकeger bits in the भागider */
	u32 पूर्णांक_bits;
	/* Number of fractional bits in the भागider */
	u32 frac_bits;

	u32 flags;

	bool is_vpu_घड़ी;
	bool is_mash_घड़ी;
	bool low_jitter;

	u32 tcnt_mux;
पूर्ण;

काष्ठा bcm2835_gate_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;

	u32 ctl_reg;
पूर्ण;

काष्ठा bcm2835_pll अणु
	काष्ठा clk_hw hw;
	काष्ठा bcm2835_cprman *cprman;
	स्थिर काष्ठा bcm2835_pll_data *data;
पूर्ण;

अटल पूर्णांक bcm2835_pll_is_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;

	वापस cprman_पढ़ो(cprman, data->a2w_ctrl_reg) &
		A2W_PLL_CTRL_PRST_DISABLE;
पूर्ण

अटल u32 bcm2835_pll_get_preभाग_mask(काष्ठा bcm2835_cprman *cprman,
				       स्थिर काष्ठा bcm2835_pll_data *data)
अणु
	/*
	 * On BCM2711 there isn't a pre-भागisor available in the PLL feedback
	 * loop. Bits 13:14 of ANA1 (PLLA,PLLB,PLLC,PLLD) have been re-purposed
	 * क्रम to क्रम VCO RANGE bits.
	 */
	अगर (cprman->soc & SOC_BCM2711)
		वापस 0;

	वापस data->ana->fb_preभाग_mask;
पूर्ण

अटल व्योम bcm2835_pll_choose_nभाग_and_fभाग(अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ parent_rate,
					     u32 *nभाग, u32 *fभाग)
अणु
	u64 भाग;

	भाग = (u64)rate << A2W_PLL_FRAC_BITS;
	करो_भाग(भाग, parent_rate);

	*nभाग = भाग >> A2W_PLL_FRAC_BITS;
	*fभाग = भाग & ((1 << A2W_PLL_FRAC_BITS) - 1);
पूर्ण

अटल दीर्घ bcm2835_pll_rate_from_भागisors(अचिन्हित दीर्घ parent_rate,
					   u32 nभाग, u32 fभाग, u32 pभाग)
अणु
	u64 rate;

	अगर (pभाग == 0)
		वापस 0;

	rate = (u64)parent_rate * ((nभाग << A2W_PLL_FRAC_BITS) + fभाग);
	करो_भाग(rate, pभाग);
	वापस rate >> A2W_PLL_FRAC_BITS;
पूर्ण

अटल दीर्घ bcm2835_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;
	u32 nभाग, fभाग;

	rate = clamp(rate, data->min_rate, data->max_rate);

	bcm2835_pll_choose_nभाग_and_fभाग(rate, *parent_rate, &nभाग, &fभाग);

	वापस bcm2835_pll_rate_from_भागisors(*parent_rate, nभाग, fभाग, 1);
पूर्ण

अटल अचिन्हित दीर्घ bcm2835_pll_get_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;
	u32 a2wctrl = cprman_पढ़ो(cprman, data->a2w_ctrl_reg);
	u32 nभाग, pभाग, fभाग;
	bool using_preभाग;

	अगर (parent_rate == 0)
		वापस 0;

	fभाग = cprman_पढ़ो(cprman, data->frac_reg) & A2W_PLL_FRAC_MASK;
	nभाग = (a2wctrl & A2W_PLL_CTRL_NDIV_MASK) >> A2W_PLL_CTRL_NDIV_SHIFT;
	pभाग = (a2wctrl & A2W_PLL_CTRL_PDIV_MASK) >> A2W_PLL_CTRL_PDIV_SHIFT;
	using_preभाग = cprman_पढ़ो(cprman, data->ana_reg_base + 4) &
		       bcm2835_pll_get_preभाग_mask(cprman, data);

	अगर (using_preभाग) अणु
		nभाग *= 2;
		fभाग *= 2;
	पूर्ण

	वापस bcm2835_pll_rate_from_भागisors(parent_rate, nभाग, fभाग, pभाग);
पूर्ण

अटल व्योम bcm2835_pll_off(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;

	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->cm_ctrl_reg, CM_PLL_ANARST);
	cprman_ग_लिखो(cprman, data->a2w_ctrl_reg,
		     cprman_पढ़ो(cprman, data->a2w_ctrl_reg) |
		     A2W_PLL_CTRL_PWRDN);
	spin_unlock(&cprman->regs_lock);
पूर्ण

अटल पूर्णांक bcm2835_pll_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;
	kसमय_प्रकार समयout;

	cprman_ग_लिखो(cprman, data->a2w_ctrl_reg,
		     cprman_पढ़ो(cprman, data->a2w_ctrl_reg) &
		     ~A2W_PLL_CTRL_PWRDN);

	/* Take the PLL out of reset. */
	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->cm_ctrl_reg,
		     cprman_पढ़ो(cprman, data->cm_ctrl_reg) & ~CM_PLL_ANARST);
	spin_unlock(&cprman->regs_lock);

	/* Wait क्रम the PLL to lock. */
	समयout = kसमय_add_ns(kसमय_get(), LOCK_TIMEOUT_NS);
	जबतक (!(cprman_पढ़ो(cprman, CM_LOCK) & data->lock_mask)) अणु
		अगर (kसमय_after(kसमय_get(), समयout)) अणु
			dev_err(cprman->dev, "%s: couldn't lock PLL\n",
				clk_hw_get_name(hw));
			वापस -ETIMEDOUT;
		पूर्ण

		cpu_relax();
	पूर्ण

	cprman_ग_लिखो(cprman, data->a2w_ctrl_reg,
		     cprman_पढ़ो(cprman, data->a2w_ctrl_reg) |
		     A2W_PLL_CTRL_PRST_DISABLE);

	वापस 0;
पूर्ण

अटल व्योम
bcm2835_pll_ग_लिखो_ana(काष्ठा bcm2835_cprman *cprman, u32 ana_reg_base, u32 *ana)
अणु
	पूर्णांक i;

	/*
	 * ANA रेजिस्टर setup is करोne as a series of ग_लिखोs to
	 * ANA3-ANA0, in that order.  This lets us ग_लिखो all 4
	 * रेजिस्टरs as a single cycle of the serdes पूर्णांकerface (taking
	 * 100 xosc घड़ीs), whereas अगर we were to update ana0, 1, and
	 * 3 inभागidually through their partial-ग_लिखो रेजिस्टरs, each
	 * would be their own serdes cycle.
	 */
	क्रम (i = 3; i >= 0; i--)
		cprman_ग_लिखो(cprman, ana_reg_base + i * 4, ana[i]);
पूर्ण

अटल पूर्णांक bcm2835_pll_set_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;
	u32 preभाग_mask = bcm2835_pll_get_preभाग_mask(cprman, data);
	bool was_using_preभाग, use_fb_preभाग, करो_ana_setup_first;
	u32 nभाग, fभाग, a2w_ctl;
	u32 ana[4];
	पूर्णांक i;

	अगर (rate > data->max_fb_rate) अणु
		use_fb_preभाग = true;
		rate /= 2;
	पूर्ण अन्यथा अणु
		use_fb_preभाग = false;
	पूर्ण

	bcm2835_pll_choose_nभाग_and_fभाग(rate, parent_rate, &nभाग, &fभाग);

	क्रम (i = 3; i >= 0; i--)
		ana[i] = cprman_पढ़ो(cprman, data->ana_reg_base + i * 4);

	was_using_preभाग = ana[1] & preभाग_mask;

	ana[0] &= ~data->ana->mask0;
	ana[0] |= data->ana->set0;
	ana[1] &= ~data->ana->mask1;
	ana[1] |= data->ana->set1;
	ana[3] &= ~data->ana->mask3;
	ana[3] |= data->ana->set3;

	अगर (was_using_preभाग && !use_fb_preभाग) अणु
		ana[1] &= ~preभाग_mask;
		करो_ana_setup_first = true;
	पूर्ण अन्यथा अगर (!was_using_preभाग && use_fb_preभाग) अणु
		ana[1] |= preभाग_mask;
		करो_ana_setup_first = false;
	पूर्ण अन्यथा अणु
		करो_ana_setup_first = true;
	पूर्ण

	/* Unmask the reference घड़ी from the oscillator. */
	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, A2W_XOSC_CTRL,
		     cprman_पढ़ो(cprman, A2W_XOSC_CTRL) |
		     data->reference_enable_mask);
	spin_unlock(&cprman->regs_lock);

	अगर (करो_ana_setup_first)
		bcm2835_pll_ग_लिखो_ana(cprman, data->ana_reg_base, ana);

	/* Set the PLL multiplier from the oscillator. */
	cprman_ग_लिखो(cprman, data->frac_reg, fभाग);

	a2w_ctl = cprman_पढ़ो(cprman, data->a2w_ctrl_reg);
	a2w_ctl &= ~A2W_PLL_CTRL_NDIV_MASK;
	a2w_ctl |= nभाग << A2W_PLL_CTRL_NDIV_SHIFT;
	a2w_ctl &= ~A2W_PLL_CTRL_PDIV_MASK;
	a2w_ctl |= 1 << A2W_PLL_CTRL_PDIV_SHIFT;
	cprman_ग_लिखो(cprman, data->a2w_ctrl_reg, a2w_ctl);

	अगर (!करो_ana_setup_first)
		bcm2835_pll_ग_लिखो_ana(cprman, data->ana_reg_base, ana);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_pll_debug_init(काष्ठा clk_hw *hw,
				  काष्ठा dentry *dentry)
अणु
	काष्ठा bcm2835_pll *pll = container_of(hw, काष्ठा bcm2835_pll, hw);
	काष्ठा bcm2835_cprman *cprman = pll->cprman;
	स्थिर काष्ठा bcm2835_pll_data *data = pll->data;
	काष्ठा debugfs_reg32 *regs;

	regs = devm_kसुस्मृति(cprman->dev, 7, माप(*regs), GFP_KERNEL);
	अगर (!regs)
		वापस;

	regs[0].name = "cm_ctrl";
	regs[0].offset = data->cm_ctrl_reg;
	regs[1].name = "a2w_ctrl";
	regs[1].offset = data->a2w_ctrl_reg;
	regs[2].name = "frac";
	regs[2].offset = data->frac_reg;
	regs[3].name = "ana0";
	regs[3].offset = data->ana_reg_base + 0 * 4;
	regs[4].name = "ana1";
	regs[4].offset = data->ana_reg_base + 1 * 4;
	regs[5].name = "ana2";
	regs[5].offset = data->ana_reg_base + 2 * 4;
	regs[6].name = "ana3";
	regs[6].offset = data->ana_reg_base + 3 * 4;

	bcm2835_debugfs_regset(cprman, 0, regs, 7, dentry);
पूर्ण

अटल स्थिर काष्ठा clk_ops bcm2835_pll_clk_ops = अणु
	.is_prepared = bcm2835_pll_is_on,
	.prepare = bcm2835_pll_on,
	.unprepare = bcm2835_pll_off,
	.recalc_rate = bcm2835_pll_get_rate,
	.set_rate = bcm2835_pll_set_rate,
	.round_rate = bcm2835_pll_round_rate,
	.debug_init = bcm2835_pll_debug_init,
पूर्ण;

काष्ठा bcm2835_pll_भागider अणु
	काष्ठा clk_भागider भाग;
	काष्ठा bcm2835_cprman *cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data;
पूर्ण;

अटल काष्ठा bcm2835_pll_भागider *
bcm2835_pll_भागider_from_hw(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा bcm2835_pll_भागider, भाग.hw);
पूर्ण

अटल पूर्णांक bcm2835_pll_भागider_is_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll_भागider *भागider = bcm2835_pll_भागider_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = भागider->cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data = भागider->data;

	वापस !(cprman_पढ़ो(cprman, data->a2w_reg) & A2W_PLL_CHANNEL_DISABLE);
पूर्ण

अटल दीर्घ bcm2835_pll_भागider_round_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ *parent_rate)
अणु
	वापस clk_भागider_ops.round_rate(hw, rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ bcm2835_pll_भागider_get_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	वापस clk_भागider_ops.recalc_rate(hw, parent_rate);
पूर्ण

अटल व्योम bcm2835_pll_भागider_off(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll_भागider *भागider = bcm2835_pll_भागider_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = भागider->cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data = भागider->data;

	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->cm_reg,
		     (cprman_पढ़ो(cprman, data->cm_reg) &
		      ~data->load_mask) | data->hold_mask);
	cprman_ग_लिखो(cprman, data->a2w_reg,
		     cprman_पढ़ो(cprman, data->a2w_reg) |
		     A2W_PLL_CHANNEL_DISABLE);
	spin_unlock(&cprman->regs_lock);
पूर्ण

अटल पूर्णांक bcm2835_pll_भागider_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_pll_भागider *भागider = bcm2835_pll_भागider_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = भागider->cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data = भागider->data;

	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->a2w_reg,
		     cprman_पढ़ो(cprman, data->a2w_reg) &
		     ~A2W_PLL_CHANNEL_DISABLE);

	cprman_ग_लिखो(cprman, data->cm_reg,
		     cprman_पढ़ो(cprman, data->cm_reg) & ~data->hold_mask);
	spin_unlock(&cprman->regs_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_pll_भागider_set_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm2835_pll_भागider *भागider = bcm2835_pll_भागider_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = भागider->cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data = भागider->data;
	u32 cm, भाग, max_भाग = 1 << A2W_PLL_DIV_BITS;

	भाग = DIV_ROUND_UP_ULL(parent_rate, rate);

	भाग = min(भाग, max_भाग);
	अगर (भाग == max_भाग)
		भाग = 0;

	cprman_ग_लिखो(cprman, data->a2w_reg, भाग);
	cm = cprman_पढ़ो(cprman, data->cm_reg);
	cprman_ग_लिखो(cprman, data->cm_reg, cm | data->load_mask);
	cprman_ग_लिखो(cprman, data->cm_reg, cm & ~data->load_mask);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_pll_भागider_debug_init(काष्ठा clk_hw *hw,
					   काष्ठा dentry *dentry)
अणु
	काष्ठा bcm2835_pll_भागider *भागider = bcm2835_pll_भागider_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = भागider->cprman;
	स्थिर काष्ठा bcm2835_pll_भागider_data *data = भागider->data;
	काष्ठा debugfs_reg32 *regs;

	regs = devm_kसुस्मृति(cprman->dev, 7, माप(*regs), GFP_KERNEL);
	अगर (!regs)
		वापस;

	regs[0].name = "cm";
	regs[0].offset = data->cm_reg;
	regs[1].name = "a2w";
	regs[1].offset = data->a2w_reg;

	bcm2835_debugfs_regset(cprman, 0, regs, 2, dentry);
पूर्ण

अटल स्थिर काष्ठा clk_ops bcm2835_pll_भागider_clk_ops = अणु
	.is_prepared = bcm2835_pll_भागider_is_on,
	.prepare = bcm2835_pll_भागider_on,
	.unprepare = bcm2835_pll_भागider_off,
	.recalc_rate = bcm2835_pll_भागider_get_rate,
	.set_rate = bcm2835_pll_भागider_set_rate,
	.round_rate = bcm2835_pll_भागider_round_rate,
	.debug_init = bcm2835_pll_भागider_debug_init,
पूर्ण;

/*
 * The CM भागiders करो fixed-poपूर्णांक भागision, so we can't use the
 * generic पूर्णांकeger भागider code like the PLL भागiders करो (and we can't
 * fake it by having some fixed shअगरts preceding it in the घड़ी tree,
 * because we'd run out of bits in a 32-bit अचिन्हित दीर्घ).
 */
काष्ठा bcm2835_घड़ी अणु
	काष्ठा clk_hw hw;
	काष्ठा bcm2835_cprman *cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data;
पूर्ण;

अटल काष्ठा bcm2835_घड़ी *bcm2835_घड़ी_from_hw(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा bcm2835_घड़ी, hw);
पूर्ण

अटल पूर्णांक bcm2835_घड़ी_is_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;

	वापस (cprman_पढ़ो(cprman, data->ctl_reg) & CM_ENABLE) != 0;
पूर्ण

अटल u32 bcm2835_घड़ी_choose_भाग(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate,
				    bool round_up)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u32 unused_frac_mask =
		GENMASK(CM_DIV_FRAC_BITS - data->frac_bits, 0) >> 1;
	u64 temp = (u64)parent_rate << CM_DIV_FRAC_BITS;
	u64 rem;
	u32 भाग, minभाग, maxभाग;

	rem = करो_भाग(temp, rate);
	भाग = temp;

	/* Round up and mask off the unused bits */
	अगर (round_up && ((भाग & unused_frac_mask) != 0 || rem != 0))
		भाग += unused_frac_mask + 1;
	भाग &= ~unused_frac_mask;

	/* dअगरferent clamping limits apply क्रम a mash घड़ी */
	अगर (data->is_mash_घड़ी) अणु
		/* clamp to min भागider of 2 */
		minभाग = 2 << CM_DIV_FRAC_BITS;
		/* clamp to the highest possible पूर्णांकeger भागider */
		maxभाग = (BIT(data->पूर्णांक_bits) - 1) << CM_DIV_FRAC_BITS;
	पूर्ण अन्यथा अणु
		/* clamp to min भागider of 1 */
		minभाग = 1 << CM_DIV_FRAC_BITS;
		/* clamp to the highest possible fractional भागider */
		maxभाग = GENMASK(data->पूर्णांक_bits + CM_DIV_FRAC_BITS - 1,
				 CM_DIV_FRAC_BITS - data->frac_bits);
	पूर्ण

	/* apply the clamping  limits */
	भाग = max_t(u32, भाग, minभाग);
	भाग = min_t(u32, भाग, maxभाग);

	वापस भाग;
पूर्ण

अटल दीर्घ bcm2835_घड़ी_rate_from_भागisor(काष्ठा bcm2835_घड़ी *घड़ी,
					    अचिन्हित दीर्घ parent_rate,
					    u32 भाग)
अणु
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u64 temp;

	अगर (data->पूर्णांक_bits == 0 && data->frac_bits == 0)
		वापस parent_rate;

	/*
	 * The भागisor is a 12.12 fixed poपूर्णांक field, but only some of
	 * the bits are populated in any given घड़ी.
	 */
	भाग >>= CM_DIV_FRAC_BITS - data->frac_bits;
	भाग &= (1 << (data->पूर्णांक_bits + data->frac_bits)) - 1;

	अगर (भाग == 0)
		वापस 0;

	temp = (u64)parent_rate << data->frac_bits;

	करो_भाग(temp, भाग);

	वापस temp;
पूर्ण

अटल अचिन्हित दीर्घ bcm2835_घड़ी_get_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u32 भाग;

	अगर (data->पूर्णांक_bits == 0 && data->frac_bits == 0)
		वापस parent_rate;

	भाग = cprman_पढ़ो(cprman, data->भाग_reg);

	वापस bcm2835_घड़ी_rate_from_भागisor(घड़ी, parent_rate, भाग);
पूर्ण

अटल व्योम bcm2835_घड़ी_रुको_busy(काष्ठा bcm2835_घड़ी *घड़ी)
अणु
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	kसमय_प्रकार समयout = kसमय_add_ns(kसमय_get(), LOCK_TIMEOUT_NS);

	जबतक (cprman_पढ़ो(cprman, data->ctl_reg) & CM_BUSY) अणु
		अगर (kसमय_after(kसमय_get(), समयout)) अणु
			dev_err(cprman->dev, "%s: couldn't lock PLL\n",
				clk_hw_get_name(&घड़ी->hw));
			वापस;
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम bcm2835_घड़ी_off(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;

	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->ctl_reg,
		     cprman_पढ़ो(cprman, data->ctl_reg) & ~CM_ENABLE);
	spin_unlock(&cprman->regs_lock);

	/* BUSY will reमुख्य high until the भागider completes its cycle. */
	bcm2835_घड़ी_रुको_busy(घड़ी);
पूर्ण

अटल पूर्णांक bcm2835_घड़ी_on(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;

	spin_lock(&cprman->regs_lock);
	cprman_ग_लिखो(cprman, data->ctl_reg,
		     cprman_पढ़ो(cprman, data->ctl_reg) |
		     CM_ENABLE |
		     CM_GATE);
	spin_unlock(&cprman->regs_lock);

	/* Debug code to measure the घड़ी once it's turned on to see
	 * अगर it's ticking at the rate we expect.
	 */
	अगर (data->tcnt_mux && false) अणु
		dev_info(cprman->dev,
			 "clk %s: rate %ld, measure %ld\n",
			 data->name,
			 clk_hw_get_rate(hw),
			 bcm2835_measure_tcnt_mux(cprman, data->tcnt_mux));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_घड़ी_set_rate(काष्ठा clk_hw *hw,
				  अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u32 भाग = bcm2835_घड़ी_choose_भाग(hw, rate, parent_rate, false);
	u32 ctl;

	spin_lock(&cprman->regs_lock);

	/*
	 * Setting up frac support
	 *
	 * In principle it is recommended to stop/start the घड़ी first,
	 * but as we set CLK_SET_RATE_GATE during registration of the
	 * घड़ी this requirement should be take care of by the
	 * clk-framework.
	 */
	ctl = cprman_पढ़ो(cprman, data->ctl_reg) & ~CM_FRAC;
	ctl |= (भाग & CM_DIV_FRAC_MASK) ? CM_FRAC : 0;
	cprman_ग_लिखो(cprman, data->ctl_reg, ctl);

	cprman_ग_लिखो(cprman, data->भाग_reg, भाग);

	spin_unlock(&cprman->regs_lock);

	वापस 0;
पूर्ण

अटल bool
bcm2835_clk_is_pllc(काष्ठा clk_hw *hw)
अणु
	अगर (!hw)
		वापस false;

	वापस म_भेदन(clk_hw_get_name(hw), "pllc", 4) == 0;
पूर्ण

अटल अचिन्हित दीर्घ bcm2835_घड़ी_choose_भाग_and_prate(काष्ठा clk_hw *hw,
							पूर्णांक parent_idx,
							अचिन्हित दीर्घ rate,
							u32 *भाग,
							अचिन्हित दीर्घ *prate,
							अचिन्हित दीर्घ *avgrate)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	अचिन्हित दीर्घ best_rate = 0;
	u32 curभाग, minभाग, maxभाग;
	काष्ठा clk_hw *parent;

	parent = clk_hw_get_parent_by_index(hw, parent_idx);

	अगर (!(BIT(parent_idx) & data->set_rate_parent)) अणु
		*prate = clk_hw_get_rate(parent);
		*भाग = bcm2835_घड़ी_choose_भाग(hw, rate, *prate, true);

		*avgrate = bcm2835_घड़ी_rate_from_भागisor(घड़ी, *prate, *भाग);

		अगर (data->low_jitter && (*भाग & CM_DIV_FRAC_MASK)) अणु
			अचिन्हित दीर्घ high, low;
			u32 पूर्णांक_भाग = *भाग & ~CM_DIV_FRAC_MASK;

			high = bcm2835_घड़ी_rate_from_भागisor(घड़ी, *prate,
							       पूर्णांक_भाग);
			पूर्णांक_भाग += CM_DIV_FRAC_MASK + 1;
			low = bcm2835_घड़ी_rate_from_भागisor(घड़ी, *prate,
							      पूर्णांक_भाग);

			/*
			 * Return a value which is the maximum deviation
			 * below the ideal rate, क्रम use as a metric.
			 */
			वापस *avgrate - max(*avgrate - low, high - *avgrate);
		पूर्ण
		वापस *avgrate;
	पूर्ण

	अगर (data->frac_bits)
		dev_warn(cprman->dev,
			"frac bits are not used when propagating rate change");

	/* clamp to min भागider of 2 अगर we're dealing with a mash घड़ी */
	minभाग = data->is_mash_घड़ी ? 2 : 1;
	maxभाग = BIT(data->पूर्णांक_bits) - 1;

	/* TODO: Be smart, and only test a subset of the available भागisors. */
	क्रम (curभाग = minभाग; curभाग <= maxभाग; curभाग++) अणु
		अचिन्हित दीर्घ पंचांगp_rate;

		पंचांगp_rate = clk_hw_round_rate(parent, rate * curभाग);
		पंचांगp_rate /= curभाग;
		अगर (curभाग == minभाग ||
		    (पंचांगp_rate > best_rate && पंचांगp_rate <= rate))
			best_rate = पंचांगp_rate;

		अगर (best_rate == rate)
			अवरोध;
	पूर्ण

	*भाग = curभाग << CM_DIV_FRAC_BITS;
	*prate = curभाग * best_rate;
	*avgrate = best_rate;

	वापस best_rate;
पूर्ण

अटल पूर्णांक bcm2835_घड़ी_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *parent, *best_parent = शून्य;
	bool current_parent_is_pllc;
	अचिन्हित दीर्घ rate, best_rate = 0;
	अचिन्हित दीर्घ prate, best_prate = 0;
	अचिन्हित दीर्घ avgrate, best_avgrate = 0;
	माप_प्रकार i;
	u32 भाग;

	current_parent_is_pllc = bcm2835_clk_is_pllc(clk_hw_get_parent(hw));

	/*
	 * Select parent घड़ी that results in the बंदst but lower rate
	 */
	क्रम (i = 0; i < clk_hw_get_num_parents(hw); ++i) अणु
		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		/*
		 * Don't choose a PLLC-derived घड़ी as our parent
		 * unless it had been manually set that way.  PLLC's
		 * frequency माला_लो adjusted by the firmware due to
		 * over-temp or under-voltage conditions, without
		 * prior notअगरication to our घड़ी consumer.
		 */
		अगर (bcm2835_clk_is_pllc(parent) && !current_parent_is_pllc)
			जारी;

		rate = bcm2835_घड़ी_choose_भाग_and_prate(hw, i, req->rate,
							  &भाग, &prate,
							  &avgrate);
		अगर (rate > best_rate && rate <= req->rate) अणु
			best_parent = parent;
			best_prate = prate;
			best_rate = rate;
			best_avgrate = avgrate;
		पूर्ण
	पूर्ण

	अगर (!best_parent)
		वापस -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best_prate;

	req->rate = best_avgrate;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_घड़ी_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u8 src = (index << CM_SRC_SHIFT) & CM_SRC_MASK;

	cprman_ग_लिखो(cprman, data->ctl_reg, src);
	वापस 0;
पूर्ण

अटल u8 bcm2835_घड़ी_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;
	u32 src = cprman_पढ़ो(cprman, data->ctl_reg);

	वापस (src & CM_SRC_MASK) >> CM_SRC_SHIFT;
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 bcm2835_debugfs_घड़ी_reg32[] = अणु
	अणु
		.name = "ctl",
		.offset = 0,
	पूर्ण,
	अणु
		.name = "div",
		.offset = 4,
	पूर्ण,
पूर्ण;

अटल व्योम bcm2835_घड़ी_debug_init(काष्ठा clk_hw *hw,
				    काष्ठा dentry *dentry)
अणु
	काष्ठा bcm2835_घड़ी *घड़ी = bcm2835_घड़ी_from_hw(hw);
	काष्ठा bcm2835_cprman *cprman = घड़ी->cprman;
	स्थिर काष्ठा bcm2835_घड़ी_data *data = घड़ी->data;

	bcm2835_debugfs_regset(cprman, data->ctl_reg,
		bcm2835_debugfs_घड़ी_reg32,
		ARRAY_SIZE(bcm2835_debugfs_घड़ी_reg32),
		dentry);
पूर्ण

अटल स्थिर काष्ठा clk_ops bcm2835_घड़ी_clk_ops = अणु
	.is_prepared = bcm2835_घड़ी_is_on,
	.prepare = bcm2835_घड़ी_on,
	.unprepare = bcm2835_घड़ी_off,
	.recalc_rate = bcm2835_घड़ी_get_rate,
	.set_rate = bcm2835_घड़ी_set_rate,
	.determine_rate = bcm2835_घड़ी_determine_rate,
	.set_parent = bcm2835_घड़ी_set_parent,
	.get_parent = bcm2835_घड़ी_get_parent,
	.debug_init = bcm2835_घड़ी_debug_init,
पूर्ण;

अटल पूर्णांक bcm2835_vpu_घड़ी_is_on(काष्ठा clk_hw *hw)
अणु
	वापस true;
पूर्ण

/*
 * The VPU घड़ी can never be disabled (it करोesn't have an ENABLE
 * bit), so it माला_लो its own set of घड़ी ops.
 */
अटल स्थिर काष्ठा clk_ops bcm2835_vpu_घड़ी_clk_ops = अणु
	.is_prepared = bcm2835_vpu_घड़ी_is_on,
	.recalc_rate = bcm2835_घड़ी_get_rate,
	.set_rate = bcm2835_घड़ी_set_rate,
	.determine_rate = bcm2835_घड़ी_determine_rate,
	.set_parent = bcm2835_घड़ी_set_parent,
	.get_parent = bcm2835_घड़ी_get_parent,
	.debug_init = bcm2835_घड़ी_debug_init,
पूर्ण;

अटल काष्ठा clk_hw *bcm2835_रेजिस्टर_pll(काष्ठा bcm2835_cprman *cprman,
					   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा bcm2835_pll_data *pll_data = data;
	काष्ठा bcm2835_pll *pll;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	स_रखो(&init, 0, माप(init));

	/* All of the PLLs derive from the बाह्यal oscillator. */
	init.parent_names = &cprman->real_parent_names[0];
	init.num_parents = 1;
	init.name = pll_data->name;
	init.ops = &bcm2835_pll_clk_ops;
	init.flags = pll_data->flags | CLK_IGNORE_UNUSED;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस शून्य;

	pll->cprman = cprman;
	pll->data = pll_data;
	pll->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(cprman->dev, &pll->hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस शून्य;
	पूर्ण
	वापस &pll->hw;
पूर्ण

अटल काष्ठा clk_hw *
bcm2835_रेजिस्टर_pll_भागider(काष्ठा bcm2835_cprman *cprman,
			     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा bcm2835_pll_भागider_data *भागider_data = data;
	काष्ठा bcm2835_pll_भागider *भागider;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *भागider_name;
	पूर्णांक ret;

	अगर (भागider_data->fixed_भागider != 1) अणु
		भागider_name = devm_kaप्र_लिखो(cprman->dev, GFP_KERNEL,
					      "%s_prediv", भागider_data->name);
		अगर (!भागider_name)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		भागider_name = भागider_data->name;
	पूर्ण

	स_रखो(&init, 0, माप(init));

	init.parent_names = &भागider_data->source_pll;
	init.num_parents = 1;
	init.name = भागider_name;
	init.ops = &bcm2835_pll_भागider_clk_ops;
	init.flags = भागider_data->flags | CLK_IGNORE_UNUSED;

	भागider = devm_kzalloc(cprman->dev, माप(*भागider), GFP_KERNEL);
	अगर (!भागider)
		वापस शून्य;

	भागider->भाग.reg = cprman->regs + भागider_data->a2w_reg;
	भागider->भाग.shअगरt = A2W_PLL_DIV_SHIFT;
	भागider->भाग.width = A2W_PLL_DIV_BITS;
	भागider->भाग.flags = CLK_DIVIDER_MAX_AT_ZERO;
	भागider->भाग.lock = &cprman->regs_lock;
	भागider->भाग.hw.init = &init;
	भागider->भाग.table = शून्य;

	भागider->cprman = cprman;
	भागider->data = भागider_data;

	ret = devm_clk_hw_रेजिस्टर(cprman->dev, &भागider->भाग.hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	/*
	 * PLLH's channels have a fixed भागide by 10 afterwards, which
	 * is what our consumers are actually using.
	 */
	अगर (भागider_data->fixed_भागider != 1) अणु
		वापस clk_hw_रेजिस्टर_fixed_factor(cprman->dev,
						    भागider_data->name,
						    भागider_name,
						    CLK_SET_RATE_PARENT,
						    1,
						    भागider_data->fixed_भागider);
	पूर्ण

	वापस &भागider->भाग.hw;
पूर्ण

अटल काष्ठा clk_hw *bcm2835_रेजिस्टर_घड़ी(काष्ठा bcm2835_cprman *cprman,
					     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा bcm2835_घड़ी_data *घड़ी_data = data;
	काष्ठा bcm2835_घड़ी *घड़ी;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parents[1 << CM_SRC_BITS];
	माप_प्रकार i;
	पूर्णांक ret;

	/*
	 * Replace our strings referencing parent घड़ीs with the
	 * actual घड़ी-output-name of the parent.
	 */
	क्रम (i = 0; i < घड़ी_data->num_mux_parents; i++) अणु
		parents[i] = घड़ी_data->parents[i];

		ret = match_string(cprman_parent_names,
				   ARRAY_SIZE(cprman_parent_names),
				   parents[i]);
		अगर (ret >= 0)
			parents[i] = cprman->real_parent_names[ret];
	पूर्ण

	स_रखो(&init, 0, माप(init));
	init.parent_names = parents;
	init.num_parents = घड़ी_data->num_mux_parents;
	init.name = घड़ी_data->name;
	init.flags = घड़ी_data->flags | CLK_IGNORE_UNUSED;

	/*
	 * Pass the CLK_SET_RATE_PARENT flag अगर we are allowed to propagate
	 * rate changes on at least of the parents.
	 */
	अगर (घड़ी_data->set_rate_parent)
		init.flags |= CLK_SET_RATE_PARENT;

	अगर (घड़ी_data->is_vpu_घड़ी) अणु
		init.ops = &bcm2835_vpu_घड़ी_clk_ops;
	पूर्ण अन्यथा अणु
		init.ops = &bcm2835_घड़ी_clk_ops;
		init.flags |= CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;

		/* If the घड़ी wasn't actually enabled at boot, it's not
		 * critical.
		 */
		अगर (!(cprman_पढ़ो(cprman, घड़ी_data->ctl_reg) & CM_ENABLE))
			init.flags &= ~CLK_IS_CRITICAL;
	पूर्ण

	घड़ी = devm_kzalloc(cprman->dev, माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी)
		वापस शून्य;

	घड़ी->cprman = cprman;
	घड़ी->data = घड़ी_data;
	घड़ी->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(cprman->dev, &घड़ी->hw);
	अगर (ret)
		वापस ERR_PTR(ret);
	वापस &घड़ी->hw;
पूर्ण

अटल काष्ठा clk_hw *bcm2835_रेजिस्टर_gate(काष्ठा bcm2835_cprman *cprman,
					    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा bcm2835_gate_data *gate_data = data;

	वापस clk_hw_रेजिस्टर_gate(cprman->dev, gate_data->name,
				    gate_data->parent,
				    CLK_IGNORE_UNUSED | CLK_SET_RATE_GATE,
				    cprman->regs + gate_data->ctl_reg,
				    CM_GATE_BIT, 0, &cprman->regs_lock);
पूर्ण

काष्ठा bcm2835_clk_desc अणु
	काष्ठा clk_hw *(*clk_रेजिस्टर)(काष्ठा bcm2835_cprman *cprman,
				       स्थिर व्योम *data);
	अचिन्हित पूर्णांक supported;
	स्थिर व्योम *data;
पूर्ण;

/* assignment helper macros क्रम dअगरferent घड़ी types */
#घोषणा _REGISTER(f, s, ...) अणु .clk_रेजिस्टर = f, \
			       .supported = s,				\
			       .data = __VA_ARGS__ पूर्ण
#घोषणा REGISTER_PLL(s, ...)	_REGISTER(&bcm2835_रेजिस्टर_pll,	\
					  s,				\
					  &(काष्ठा bcm2835_pll_data)	\
					  अणु__VA_ARGS__पूर्ण)
#घोषणा REGISTER_PLL_DIV(s, ...) _REGISTER(&bcm2835_रेजिस्टर_pll_भागider, \
					   s,				  \
					   &(काष्ठा bcm2835_pll_भागider_data) \
					   अणु__VA_ARGS__पूर्ण)
#घोषणा REGISTER_CLK(s, ...)	_REGISTER(&bcm2835_रेजिस्टर_घड़ी,	\
					  s,				\
					  &(काष्ठा bcm2835_घड़ी_data)	\
					  अणु__VA_ARGS__पूर्ण)
#घोषणा REGISTER_GATE(s, ...)	_REGISTER(&bcm2835_रेजिस्टर_gate,	\
					  s,				\
					  &(काष्ठा bcm2835_gate_data)	\
					  अणु__VA_ARGS__पूर्ण)

/* parent mux arrays plus helper macros */

/* मुख्य oscillator parent mux */
अटल स्थिर अक्षर *स्थिर bcm2835_घड़ी_osc_parents[] = अणु
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1"
पूर्ण;

#घोषणा REGISTER_OSC_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_घड़ी_osc_parents),	\
	.parents = bcm2835_घड़ी_osc_parents,				\
	__VA_ARGS__)

/* मुख्य peripherial parent mux */
अटल स्थिर अक्षर *स्थिर bcm2835_घड़ी_per_parents[] = अणु
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"plla_per",
	"pllc_per",
	"plld_per",
	"pllh_aux",
पूर्ण;

#घोषणा REGISTER_PER_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_घड़ी_per_parents),	\
	.parents = bcm2835_घड़ी_per_parents,				\
	__VA_ARGS__)

/*
 * Restrict घड़ी sources क्रम the PCM peripheral to the oscillator and
 * PLLD_PER because other source may have varying rates or be चयनed
 * off.
 *
 * Prevent other sources from being selected by replacing their names in
 * the list of potential parents with dummy entries (entry index is
 * signअगरicant).
 */
अटल स्थिर अक्षर *स्थिर bcm2835_pcm_per_parents[] = अणु
	"-",
	"xosc",
	"-",
	"-",
	"-",
	"-",
	"plld_per",
	"-",
पूर्ण;

#घोषणा REGISTER_PCM_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_pcm_per_parents),		\
	.parents = bcm2835_pcm_per_parents,				\
	__VA_ARGS__)

/* मुख्य vpu parent mux */
अटल स्थिर अक्षर *स्थिर bcm2835_घड़ी_vpu_parents[] = अणु
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"plla_core",
	"pllc_core0",
	"plld_core",
	"pllh_aux",
	"pllc_core1",
	"pllc_core2",
पूर्ण;

#घोषणा REGISTER_VPU_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_घड़ी_vpu_parents),	\
	.parents = bcm2835_घड़ी_vpu_parents,				\
	__VA_ARGS__)

/*
 * DSI parent घड़ीs.  The DSI byte/DDR/DDR2 घड़ीs come from the DSI
 * analog PHY.  The _inv variants are generated पूर्णांकernally to cprman,
 * but we करोn't use them so they aren't hooked up.
 */
अटल स्थिर अक्षर *स्थिर bcm2835_घड़ी_dsi0_parents[] = अणु
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"dsi0_ddr",
	"dsi0_ddr_inv",
	"dsi0_ddr2",
	"dsi0_ddr2_inv",
	"dsi0_byte",
	"dsi0_byte_inv",
पूर्ण;

अटल स्थिर अक्षर *स्थिर bcm2835_घड़ी_dsi1_parents[] = अणु
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"dsi1_ddr",
	"dsi1_ddr_inv",
	"dsi1_ddr2",
	"dsi1_ddr2_inv",
	"dsi1_byte",
	"dsi1_byte_inv",
पूर्ण;

#घोषणा REGISTER_DSI0_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_घड़ी_dsi0_parents),	\
	.parents = bcm2835_घड़ी_dsi0_parents,				\
	__VA_ARGS__)

#घोषणा REGISTER_DSI1_CLK(s, ...)	REGISTER_CLK(			\
	s,								\
	.num_mux_parents = ARRAY_SIZE(bcm2835_घड़ी_dsi1_parents),	\
	.parents = bcm2835_घड़ी_dsi1_parents,				\
	__VA_ARGS__)

/*
 * the real definition of all the pll, pll_भागiders and घड़ीs
 * these make use of the above REGISTER_* macros
 */
अटल स्थिर काष्ठा bcm2835_clk_desc clk_desc_array[] = अणु
	/* the PLL + PLL भागiders */

	/*
	 * PLLA is the auxiliary PLL, used to drive the CCP2
	 * (Compact Camera Port 2) transmitter घड़ी.
	 *
	 * It is in the PX LDO घातer करोमुख्य, which is on when the
	 * AUDIO करोमुख्य is on.
	 */
	[BCM2835_PLLA]		= REGISTER_PLL(
		SOC_ALL,
		.name = "plla",
		.cm_ctrl_reg = CM_PLLA,
		.a2w_ctrl_reg = A2W_PLLA_CTRL,
		.frac_reg = A2W_PLLA_FRAC,
		.ana_reg_base = A2W_PLLA_ANA0,
		.reference_enable_mask = A2W_XOSC_CTRL_PLLA_ENABLE,
		.lock_mask = CM_LOCK_FLOCKA,

		.ana = &bcm2835_ana_शेष,

		.min_rate = 600000000u,
		.max_rate = 2400000000u,
		.max_fb_rate = BCM2835_MAX_FB_RATE),
	[BCM2835_PLLA_CORE]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plla_core",
		.source_pll = "plla",
		.cm_reg = CM_PLLA,
		.a2w_reg = A2W_PLLA_CORE,
		.load_mask = CM_PLLA_LOADCORE,
		.hold_mask = CM_PLLA_HOLDCORE,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLA_PER]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plla_per",
		.source_pll = "plla",
		.cm_reg = CM_PLLA,
		.a2w_reg = A2W_PLLA_PER,
		.load_mask = CM_PLLA_LOADPER,
		.hold_mask = CM_PLLA_HOLDPER,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLA_DSI0]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plla_dsi0",
		.source_pll = "plla",
		.cm_reg = CM_PLLA,
		.a2w_reg = A2W_PLLA_DSI0,
		.load_mask = CM_PLLA_LOADDSI0,
		.hold_mask = CM_PLLA_HOLDDSI0,
		.fixed_भागider = 1),
	[BCM2835_PLLA_CCP2]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plla_ccp2",
		.source_pll = "plla",
		.cm_reg = CM_PLLA,
		.a2w_reg = A2W_PLLA_CCP2,
		.load_mask = CM_PLLA_LOADCCP2,
		.hold_mask = CM_PLLA_HOLDCCP2,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),

	/* PLLB is used क्रम the ARM's घड़ी. */
	[BCM2835_PLLB]		= REGISTER_PLL(
		SOC_ALL,
		.name = "pllb",
		.cm_ctrl_reg = CM_PLLB,
		.a2w_ctrl_reg = A2W_PLLB_CTRL,
		.frac_reg = A2W_PLLB_FRAC,
		.ana_reg_base = A2W_PLLB_ANA0,
		.reference_enable_mask = A2W_XOSC_CTRL_PLLB_ENABLE,
		.lock_mask = CM_LOCK_FLOCKB,

		.ana = &bcm2835_ana_शेष,

		.min_rate = 600000000u,
		.max_rate = 3000000000u,
		.max_fb_rate = BCM2835_MAX_FB_RATE,
		.flags = CLK_GET_RATE_NOCACHE),
	[BCM2835_PLLB_ARM]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "pllb_arm",
		.source_pll = "pllb",
		.cm_reg = CM_PLLB,
		.a2w_reg = A2W_PLLB_ARM,
		.load_mask = CM_PLLB_LOADARM,
		.hold_mask = CM_PLLB_HOLDARM,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE),

	/*
	 * PLLC is the core PLL, used to drive the core VPU घड़ी.
	 *
	 * It is in the PX LDO घातer करोमुख्य, which is on when the
	 * AUDIO करोमुख्य is on.
	 */
	[BCM2835_PLLC]		= REGISTER_PLL(
		SOC_ALL,
		.name = "pllc",
		.cm_ctrl_reg = CM_PLLC,
		.a2w_ctrl_reg = A2W_PLLC_CTRL,
		.frac_reg = A2W_PLLC_FRAC,
		.ana_reg_base = A2W_PLLC_ANA0,
		.reference_enable_mask = A2W_XOSC_CTRL_PLLC_ENABLE,
		.lock_mask = CM_LOCK_FLOCKC,

		.ana = &bcm2835_ana_शेष,

		.min_rate = 600000000u,
		.max_rate = 3000000000u,
		.max_fb_rate = BCM2835_MAX_FB_RATE),
	[BCM2835_PLLC_CORE0]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "pllc_core0",
		.source_pll = "pllc",
		.cm_reg = CM_PLLC,
		.a2w_reg = A2W_PLLC_CORE0,
		.load_mask = CM_PLLC_LOADCORE0,
		.hold_mask = CM_PLLC_HOLDCORE0,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLC_CORE1]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "pllc_core1",
		.source_pll = "pllc",
		.cm_reg = CM_PLLC,
		.a2w_reg = A2W_PLLC_CORE1,
		.load_mask = CM_PLLC_LOADCORE1,
		.hold_mask = CM_PLLC_HOLDCORE1,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLC_CORE2]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "pllc_core2",
		.source_pll = "pllc",
		.cm_reg = CM_PLLC,
		.a2w_reg = A2W_PLLC_CORE2,
		.load_mask = CM_PLLC_LOADCORE2,
		.hold_mask = CM_PLLC_HOLDCORE2,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLC_PER]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "pllc_per",
		.source_pll = "pllc",
		.cm_reg = CM_PLLC,
		.a2w_reg = A2W_PLLC_PER,
		.load_mask = CM_PLLC_LOADPER,
		.hold_mask = CM_PLLC_HOLDPER,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),

	/*
	 * PLLD is the display PLL, used to drive DSI display panels.
	 *
	 * It is in the PX LDO घातer करोमुख्य, which is on when the
	 * AUDIO करोमुख्य is on.
	 */
	[BCM2835_PLLD]		= REGISTER_PLL(
		SOC_ALL,
		.name = "plld",
		.cm_ctrl_reg = CM_PLLD,
		.a2w_ctrl_reg = A2W_PLLD_CTRL,
		.frac_reg = A2W_PLLD_FRAC,
		.ana_reg_base = A2W_PLLD_ANA0,
		.reference_enable_mask = A2W_XOSC_CTRL_DDR_ENABLE,
		.lock_mask = CM_LOCK_FLOCKD,

		.ana = &bcm2835_ana_शेष,

		.min_rate = 600000000u,
		.max_rate = 2400000000u,
		.max_fb_rate = BCM2835_MAX_FB_RATE),
	[BCM2835_PLLD_CORE]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plld_core",
		.source_pll = "plld",
		.cm_reg = CM_PLLD,
		.a2w_reg = A2W_PLLD_CORE,
		.load_mask = CM_PLLD_LOADCORE,
		.hold_mask = CM_PLLD_HOLDCORE,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	/*
	 * VPU firmware assumes that PLLD_PER isn't disabled by the ARM core.
	 * Otherwise this could cause firmware lookups. That's why we mark
	 * it as critical.
	 */
	[BCM2835_PLLD_PER]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plld_per",
		.source_pll = "plld",
		.cm_reg = CM_PLLD,
		.a2w_reg = A2W_PLLD_PER,
		.load_mask = CM_PLLD_LOADPER,
		.hold_mask = CM_PLLD_HOLDPER,
		.fixed_भागider = 1,
		.flags = CLK_IS_CRITICAL | CLK_SET_RATE_PARENT),
	[BCM2835_PLLD_DSI0]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plld_dsi0",
		.source_pll = "plld",
		.cm_reg = CM_PLLD,
		.a2w_reg = A2W_PLLD_DSI0,
		.load_mask = CM_PLLD_LOADDSI0,
		.hold_mask = CM_PLLD_HOLDDSI0,
		.fixed_भागider = 1),
	[BCM2835_PLLD_DSI1]	= REGISTER_PLL_DIV(
		SOC_ALL,
		.name = "plld_dsi1",
		.source_pll = "plld",
		.cm_reg = CM_PLLD,
		.a2w_reg = A2W_PLLD_DSI1,
		.load_mask = CM_PLLD_LOADDSI1,
		.hold_mask = CM_PLLD_HOLDDSI1,
		.fixed_भागider = 1),

	/*
	 * PLLH is used to supply the pixel घड़ी or the AUX घड़ी क्रम the
	 * TV encoder.
	 *
	 * It is in the HDMI घातer करोमुख्य.
	 */
	[BCM2835_PLLH]		= REGISTER_PLL(
		SOC_BCM2835,
		"pllh",
		.cm_ctrl_reg = CM_PLLH,
		.a2w_ctrl_reg = A2W_PLLH_CTRL,
		.frac_reg = A2W_PLLH_FRAC,
		.ana_reg_base = A2W_PLLH_ANA0,
		.reference_enable_mask = A2W_XOSC_CTRL_PLLC_ENABLE,
		.lock_mask = CM_LOCK_FLOCKH,

		.ana = &bcm2835_ana_pllh,

		.min_rate = 600000000u,
		.max_rate = 3000000000u,
		.max_fb_rate = BCM2835_MAX_FB_RATE),
	[BCM2835_PLLH_RCAL]	= REGISTER_PLL_DIV(
		SOC_BCM2835,
		.name = "pllh_rcal",
		.source_pll = "pllh",
		.cm_reg = CM_PLLH,
		.a2w_reg = A2W_PLLH_RCAL,
		.load_mask = CM_PLLH_LOADRCAL,
		.hold_mask = 0,
		.fixed_भागider = 10,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLH_AUX]	= REGISTER_PLL_DIV(
		SOC_BCM2835,
		.name = "pllh_aux",
		.source_pll = "pllh",
		.cm_reg = CM_PLLH,
		.a2w_reg = A2W_PLLH_AUX,
		.load_mask = CM_PLLH_LOADAUX,
		.hold_mask = 0,
		.fixed_भागider = 1,
		.flags = CLK_SET_RATE_PARENT),
	[BCM2835_PLLH_PIX]	= REGISTER_PLL_DIV(
		SOC_BCM2835,
		.name = "pllh_pix",
		.source_pll = "pllh",
		.cm_reg = CM_PLLH,
		.a2w_reg = A2W_PLLH_PIX,
		.load_mask = CM_PLLH_LOADPIX,
		.hold_mask = 0,
		.fixed_भागider = 10,
		.flags = CLK_SET_RATE_PARENT),

	/* the घड़ीs */

	/* घड़ीs with oscillator parent mux */

	/* One Time Programmable Memory घड़ी.  Maximum 10Mhz. */
	[BCM2835_CLOCK_OTP]	= REGISTER_OSC_CLK(
		SOC_ALL,
		.name = "otp",
		.ctl_reg = CM_OTPCTL,
		.भाग_reg = CM_OTPDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 0,
		.tcnt_mux = 6),
	/*
	 * Used क्रम a 1Mhz घड़ी क्रम the प्रणाली घड़ीsource, and also used
	 * bythe watchकरोg समयr and the camera pulse generator.
	 */
	[BCM2835_CLOCK_TIMER]	= REGISTER_OSC_CLK(
		SOC_ALL,
		.name = "timer",
		.ctl_reg = CM_TIMERCTL,
		.भाग_reg = CM_TIMERDIV,
		.पूर्णांक_bits = 6,
		.frac_bits = 12),
	/*
	 * Clock क्रम the temperature sensor.
	 * Generally run at 2Mhz, max 5Mhz.
	 */
	[BCM2835_CLOCK_TSENS]	= REGISTER_OSC_CLK(
		SOC_ALL,
		.name = "tsens",
		.ctl_reg = CM_TSENSCTL,
		.भाग_reg = CM_TSENSDIV,
		.पूर्णांक_bits = 5,
		.frac_bits = 0),
	[BCM2835_CLOCK_TEC]	= REGISTER_OSC_CLK(
		SOC_ALL,
		.name = "tec",
		.ctl_reg = CM_TECCTL,
		.भाग_reg = CM_TECDIV,
		.पूर्णांक_bits = 6,
		.frac_bits = 0),

	/* घड़ीs with vpu parent mux */
	[BCM2835_CLOCK_H264]	= REGISTER_VPU_CLK(
		SOC_ALL,
		.name = "h264",
		.ctl_reg = CM_H264CTL,
		.भाग_reg = CM_H264DIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 1),
	[BCM2835_CLOCK_ISP]	= REGISTER_VPU_CLK(
		SOC_ALL,
		.name = "isp",
		.ctl_reg = CM_ISPCTL,
		.भाग_reg = CM_ISPDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 2),

	/*
	 * Secondary SDRAM घड़ी.  Used क्रम low-voltage modes when the PLL
	 * in the SDRAM controller can't be used.
	 */
	[BCM2835_CLOCK_SDRAM]	= REGISTER_VPU_CLK(
		SOC_ALL,
		.name = "sdram",
		.ctl_reg = CM_SDCCTL,
		.भाग_reg = CM_SDCDIV,
		.पूर्णांक_bits = 6,
		.frac_bits = 0,
		.tcnt_mux = 3),
	[BCM2835_CLOCK_V3D]	= REGISTER_VPU_CLK(
		SOC_ALL,
		.name = "v3d",
		.ctl_reg = CM_V3DCTL,
		.भाग_reg = CM_V3DDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 4),
	/*
	 * VPU घड़ी.  This करोesn't have an enable bit, since it drives
	 * the bus क्रम everything अन्यथा, and is special so it करोesn't need
	 * to be gated क्रम rate changes.  It is also known as "clk_audio"
	 * in various hardware करोcumentation.
	 */
	[BCM2835_CLOCK_VPU]	= REGISTER_VPU_CLK(
		SOC_ALL,
		.name = "vpu",
		.ctl_reg = CM_VPUCTL,
		.भाग_reg = CM_VPUDIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 8,
		.flags = CLK_IS_CRITICAL,
		.is_vpu_घड़ी = true,
		.tcnt_mux = 5),

	/* घड़ीs with per parent mux */
	[BCM2835_CLOCK_AVEO]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "aveo",
		.ctl_reg = CM_AVEOCTL,
		.भाग_reg = CM_AVEODIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 0,
		.tcnt_mux = 38),
	[BCM2835_CLOCK_CAM0]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "cam0",
		.ctl_reg = CM_CAM0CTL,
		.भाग_reg = CM_CAM0DIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 14),
	[BCM2835_CLOCK_CAM1]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "cam1",
		.ctl_reg = CM_CAM1CTL,
		.भाग_reg = CM_CAM1DIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 15),
	[BCM2835_CLOCK_DFT]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "dft",
		.ctl_reg = CM_DFTCTL,
		.भाग_reg = CM_DFTDIV,
		.पूर्णांक_bits = 5,
		.frac_bits = 0),
	[BCM2835_CLOCK_DPI]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "dpi",
		.ctl_reg = CM_DPICTL,
		.भाग_reg = CM_DPIDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 17),

	/* Arasan EMMC घड़ी */
	[BCM2835_CLOCK_EMMC]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "emmc",
		.ctl_reg = CM_EMMCCTL,
		.भाग_reg = CM_EMMCDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 39),

	/* EMMC2 घड़ी (only available क्रम BCM2711) */
	[BCM2711_CLOCK_EMMC2]	= REGISTER_PER_CLK(
		SOC_BCM2711,
		.name = "emmc2",
		.ctl_reg = CM_EMMC2CTL,
		.भाग_reg = CM_EMMC2DIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 42),

	/* General purpose (GPIO) घड़ीs */
	[BCM2835_CLOCK_GP0]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "gp0",
		.ctl_reg = CM_GP0CTL,
		.भाग_reg = CM_GP0DIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.is_mash_घड़ी = true,
		.tcnt_mux = 20),
	[BCM2835_CLOCK_GP1]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "gp1",
		.ctl_reg = CM_GP1CTL,
		.भाग_reg = CM_GP1DIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.flags = CLK_IS_CRITICAL,
		.is_mash_घड़ी = true,
		.tcnt_mux = 21),
	[BCM2835_CLOCK_GP2]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "gp2",
		.ctl_reg = CM_GP2CTL,
		.भाग_reg = CM_GP2DIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.flags = CLK_IS_CRITICAL),

	/* HDMI state machine */
	[BCM2835_CLOCK_HSM]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "hsm",
		.ctl_reg = CM_HSMCTL,
		.भाग_reg = CM_HSMDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 22),
	[BCM2835_CLOCK_PCM]	= REGISTER_PCM_CLK(
		SOC_ALL,
		.name = "pcm",
		.ctl_reg = CM_PCMCTL,
		.भाग_reg = CM_PCMDIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.is_mash_घड़ी = true,
		.low_jitter = true,
		.tcnt_mux = 23),
	[BCM2835_CLOCK_PWM]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "pwm",
		.ctl_reg = CM_PWMCTL,
		.भाग_reg = CM_PWMDIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.is_mash_घड़ी = true,
		.tcnt_mux = 24),
	[BCM2835_CLOCK_SLIM]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "slim",
		.ctl_reg = CM_SLIMCTL,
		.भाग_reg = CM_SLIMDIV,
		.पूर्णांक_bits = 12,
		.frac_bits = 12,
		.is_mash_घड़ी = true,
		.tcnt_mux = 25),
	[BCM2835_CLOCK_SMI]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "smi",
		.ctl_reg = CM_SMICTL,
		.भाग_reg = CM_SMIDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 27),
	[BCM2835_CLOCK_UART]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "uart",
		.ctl_reg = CM_UARTCTL,
		.भाग_reg = CM_UARTDIV,
		.पूर्णांक_bits = 10,
		.frac_bits = 12,
		.tcnt_mux = 28),

	/* TV encoder घड़ी.  Only operating frequency is 108Mhz.  */
	[BCM2835_CLOCK_VEC]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "vec",
		.ctl_reg = CM_VECCTL,
		.भाग_reg = CM_VECDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 0,
		/*
		 * Allow rate change propagation only on PLLH_AUX which is
		 * asचिन्हित index 7 in the parent array.
		 */
		.set_rate_parent = BIT(7),
		.tcnt_mux = 29),

	/* dsi घड़ीs */
	[BCM2835_CLOCK_DSI0E]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "dsi0e",
		.ctl_reg = CM_DSI0ECTL,
		.भाग_reg = CM_DSI0EDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 18),
	[BCM2835_CLOCK_DSI1E]	= REGISTER_PER_CLK(
		SOC_ALL,
		.name = "dsi1e",
		.ctl_reg = CM_DSI1ECTL,
		.भाग_reg = CM_DSI1EDIV,
		.पूर्णांक_bits = 4,
		.frac_bits = 8,
		.tcnt_mux = 19),
	[BCM2835_CLOCK_DSI0P]	= REGISTER_DSI0_CLK(
		SOC_ALL,
		.name = "dsi0p",
		.ctl_reg = CM_DSI0PCTL,
		.भाग_reg = CM_DSI0PDIV,
		.पूर्णांक_bits = 0,
		.frac_bits = 0,
		.tcnt_mux = 12),
	[BCM2835_CLOCK_DSI1P]	= REGISTER_DSI1_CLK(
		SOC_ALL,
		.name = "dsi1p",
		.ctl_reg = CM_DSI1PCTL,
		.भाग_reg = CM_DSI1PDIV,
		.पूर्णांक_bits = 0,
		.frac_bits = 0,
		.tcnt_mux = 13),

	/* the gates */

	/*
	 * CM_PERIICTL (and CM_PERIACTL, CM_SYSCTL and CM_VPUCTL अगर
	 * you have the debug bit set in the घातer manager, which we
	 * करोn't bother exposing) are inभागidual gates off of the
	 * non-stop vpu घड़ी.
	 */
	[BCM2835_CLOCK_PERI_IMAGE] = REGISTER_GATE(
		SOC_ALL,
		.name = "peri_image",
		.parent = "vpu",
		.ctl_reg = CM_PERIICTL),
पूर्ण;

/*
 * Permanently take a reference on the parent of the SDRAM घड़ी.
 *
 * While the SDRAM is being driven by its dedicated PLL most of the
 * समय, there is a little loop running in the firmware that
 * periodically चयनes the SDRAM to using our CM घड़ी to करो PVT
 * recalibration, with the assumption that the previously configured
 * SDRAM parent is still enabled and running.
 */
अटल पूर्णांक bcm2835_mark_sdc_parent_critical(काष्ठा clk *sdc)
अणु
	काष्ठा clk *parent = clk_get_parent(sdc);

	अगर (IS_ERR(parent))
		वापस PTR_ERR(parent);

	वापस clk_prepare_enable(parent);
पूर्ण

अटल पूर्णांक bcm2835_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk_hw **hws;
	काष्ठा bcm2835_cprman *cprman;
	स्थिर काष्ठा bcm2835_clk_desc *desc;
	स्थिर माप_प्रकार asize = ARRAY_SIZE(clk_desc_array);
	स्थिर काष्ठा cprman_plat_data *pdata;
	माप_प्रकार i;
	पूर्णांक ret;

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (!pdata)
		वापस -ENODEV;

	cprman = devm_kzalloc(dev,
			      काष्ठा_size(cprman, onecell.hws, asize),
			      GFP_KERNEL);
	अगर (!cprman)
		वापस -ENOMEM;

	spin_lock_init(&cprman->regs_lock);
	cprman->dev = dev;
	cprman->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cprman->regs))
		वापस PTR_ERR(cprman->regs);

	स_नकल(cprman->real_parent_names, cprman_parent_names,
	       माप(cprman_parent_names));
	of_clk_parent_fill(dev->of_node, cprman->real_parent_names,
			   ARRAY_SIZE(cprman_parent_names));

	/*
	 * Make sure the बाह्यal oscillator has been रेजिस्टरed.
	 *
	 * The other (DSI) घड़ीs are not present on older device
	 * trees, which we still need to support क्रम backwards
	 * compatibility.
	 */
	अगर (!cprman->real_parent_names[0])
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, cprman);

	cprman->onecell.num = asize;
	cprman->soc = pdata->soc;
	hws = cprman->onecell.hws;

	क्रम (i = 0; i < asize; i++) अणु
		desc = &clk_desc_array[i];
		अगर (desc->clk_रेजिस्टर && desc->data &&
		    (desc->supported & pdata->soc)) अणु
			hws[i] = desc->clk_रेजिस्टर(cprman, desc->data);
		पूर्ण
	पूर्ण

	ret = bcm2835_mark_sdc_parent_critical(hws[BCM2835_CLOCK_SDRAM]->clk);
	अगर (ret)
		वापस ret;

	वापस of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
				      &cprman->onecell);
पूर्ण

अटल स्थिर काष्ठा cprman_plat_data cprman_bcm2835_plat_data = अणु
	.soc = SOC_BCM2835,
पूर्ण;

अटल स्थिर काष्ठा cprman_plat_data cprman_bcm2711_plat_data = अणु
	.soc = SOC_BCM2711,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm2835_clk_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-cprman", .data = &cprman_bcm2835_plat_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-cprman", .data = &cprman_bcm2711_plat_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_clk_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_clk_driver = अणु
	.driver = अणु
		.name = "bcm2835-clk",
		.of_match_table = bcm2835_clk_of_match,
	पूर्ण,
	.probe          = bcm2835_clk_probe,
पूर्ण;

builtin_platक्रमm_driver(bcm2835_clk_driver);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("BCM2835 clock driver");
MODULE_LICENSE("GPL");
