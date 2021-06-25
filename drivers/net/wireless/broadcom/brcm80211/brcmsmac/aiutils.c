<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * File contents: support functions क्रम PCI/PCIe
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>

#समावेश <defs.h>
#समावेश <chipcommon.h>
#समावेश <brcmu_utils.h>
#समावेश <brcm_hw_ids.h>
#समावेश <soc.h>
#समावेश "types.h"
#समावेश "pub.h"
#समावेश "pmu.h"
#समावेश "aiutils.h"

/* slow_clk_ctl */
 /* slow घड़ी source mask */
#घोषणा SCC_SS_MASK		0x00000007
 /* source of slow घड़ी is LPO */
#घोषणा	SCC_SS_LPO		0x00000000
 /* source of slow घड़ी is crystal */
#घोषणा	SCC_SS_XTAL		0x00000001
 /* source of slow घड़ी is PCI */
#घोषणा	SCC_SS_PCI		0x00000002
 /* LPOFreqSel, 1: 160Khz, 0: 32KHz */
#घोषणा SCC_LF			0x00000200
 /* LPOPowerDown, 1: LPO is disabled, 0: LPO is enabled */
#घोषणा SCC_LP			0x00000400
 /* ForceSlowClk, 1: sb/cores running on slow घड़ी, 0: घातer logic control */
#घोषणा SCC_FS			0x00000800
 /* IgnorePllOffReq, 1/0:
  *  घातer logic ignores/honors PLL घड़ी disable requests from core
  */
#घोषणा SCC_IP			0x00001000
 /* XtalControlEn, 1/0:
  *  घातer logic करोes/करोesn't disable crystal when appropriate
  */
#घोषणा SCC_XC			0x00002000
 /* XtalPU (RO), 1/0: crystal running/disabled */
#घोषणा SCC_XP			0x00004000
 /* ClockDivider (SlowClk = 1/(4+भागisor)) */
#घोषणा SCC_CD_MASK		0xffff0000
#घोषणा SCC_CD_SHIFT		16

/* प्रणाली_clk_ctl */
 /* ILPen: Enable Idle Low Power */
#घोषणा	SYCC_IE			0x00000001
 /* ALPen: Enable Active Low Power */
#घोषणा	SYCC_AE			0x00000002
 /* ForcePLLOn */
#घोषणा	SYCC_FP			0x00000004
 /* Force ALP (or HT अगर ALPen is not set */
#घोषणा	SYCC_AR			0x00000008
 /* Force HT */
#घोषणा	SYCC_HR			0x00000010
 /* ClkDiv  (ILP = 1/(4 * (भागisor + 1)) */
#घोषणा SYCC_CD_MASK		0xffff0000
#घोषणा SYCC_CD_SHIFT		16

#घोषणा CST4329_SPROM_OTP_SEL_MASK	0x00000003
 /* OTP is घातered up, use def. CIS, no SPROM */
#घोषणा CST4329_DEFCIS_SEL		0
 /* OTP is घातered up, SPROM is present */
#घोषणा CST4329_SPROM_SEL		1
 /* OTP is घातered up, no SPROM */
#घोषणा CST4329_OTP_SEL			2
 /* OTP is घातered करोwn, SPROM is present */
#घोषणा CST4329_OTP_PWRDN		3

#घोषणा CST4329_SPI_SDIO_MODE_MASK	0x00000004
#घोषणा CST4329_SPI_SDIO_MODE_SHIFT	2

/* 43224 chip-specअगरic ChipControl रेजिस्टर bits */
#घोषणा CCTRL43224_GPIO_TOGGLE          0x8000
 /* 12 mA drive strength */
#घोषणा CCTRL_43224A0_12MA_LED_DRIVE    0x00F000F0
 /* 12 mA drive strength क्रम later 43224s */
#घोषणा CCTRL_43224B0_12MA_LED_DRIVE    0xF0

/* 43236 Chip specअगरic ChipStatus रेजिस्टर bits */
#घोषणा CST43236_SFLASH_MASK		0x00000040
#घोषणा CST43236_OTP_MASK		0x00000080
#घोषणा CST43236_HSIC_MASK		0x00000100	/* USB/HSIC */
#घोषणा CST43236_BP_CLK			0x00000200	/* 120/96Mbps */
#घोषणा CST43236_BOOT_MASK		0x00001800
#घोषणा CST43236_BOOT_SHIFT		11
#घोषणा CST43236_BOOT_FROM_SRAM		0 /* boot from SRAM, ARM in reset */
#घोषणा CST43236_BOOT_FROM_ROM		1 /* boot from ROM */
#घोषणा CST43236_BOOT_FROM_FLASH	2 /* boot from FLASH */
#घोषणा CST43236_BOOT_FROM_INVALID	3

/* 4331 chip-specअगरic ChipControl रेजिस्टर bits */
 /* 0 disable */
#घोषणा CCTRL4331_BT_COEXIST		(1<<0)
 /* 0 SECI is disabled (JTAG functional) */
#घोषणा CCTRL4331_SECI			(1<<1)
 /* 0 disable */
#घोषणा CCTRL4331_EXT_LNA		(1<<2)
 /* sprom/gpio13-15 mux */
#घोषणा CCTRL4331_SPROM_GPIO13_15       (1<<3)
 /* 0 ext pa disable, 1 ext pa enabled */
#घोषणा CCTRL4331_EXTPA_EN		(1<<4)
 /* set drive out GPIO_CLK on sprom_cs pin */
#घोषणा CCTRL4331_GPIOCLK_ON_SPROMCS	(1<<5)
 /* use sprom_cs pin as PCIE mdio पूर्णांकerface */
#घोषणा CCTRL4331_PCIE_MDIO_ON_SPROMCS	(1<<6)
 /* aband extpa will be at gpio2/5 and sprom_करोut */
#घोषणा CCTRL4331_EXTPA_ON_GPIO2_5	(1<<7)
 /* override core control on pipe_AuxClkEnable */
#घोषणा CCTRL4331_OVR_PIPEAUXCLKEN	(1<<8)
 /* override core control on pipe_AuxPowerDown */
#घोषणा CCTRL4331_OVR_PIPEAUXPWRDOWN	(1<<9)
 /* pcie_auxclkenable */
#घोषणा CCTRL4331_PCIE_AUXCLKEN		(1<<10)
 /* pcie_pipe_pllघातerकरोwn */
#घोषणा CCTRL4331_PCIE_PIPE_PLLDOWN	(1<<11)
 /* enable bt_shd0 at gpio4 */
#घोषणा CCTRL4331_BT_SHD0_ON_GPIO4	(1<<16)
 /* enable bt_shd1 at gpio5 */
#घोषणा CCTRL4331_BT_SHD1_ON_GPIO5	(1<<17)

/* 4331 Chip specअगरic ChipStatus रेजिस्टर bits */
 /* crystal frequency 20/40Mhz */
#घोषणा	CST4331_XTAL_FREQ		0x00000001
#घोषणा	CST4331_SPROM_PRESENT		0x00000002
#घोषणा	CST4331_OTP_PRESENT		0x00000004
#घोषणा	CST4331_LDO_RF			0x00000008
#घोषणा	CST4331_LDO_PAR			0x00000010

/* 4319 chip-specअगरic ChipStatus रेजिस्टर bits */
#घोषणा	CST4319_SPI_CPULESSUSB		0x00000001
#घोषणा	CST4319_SPI_CLK_POL		0x00000002
#घोषणा	CST4319_SPI_CLK_PH		0x00000008
 /* gpio [7:6], SDIO CIS selection */
#घोषणा	CST4319_SPROM_OTP_SEL_MASK	0x000000c0
#घोषणा	CST4319_SPROM_OTP_SEL_SHIFT	6
 /* use शेष CIS, OTP is घातered up */
#घोषणा	CST4319_DEFCIS_SEL		0x00000000
 /* use SPROM, OTP is घातered up */
#घोषणा	CST4319_SPROM_SEL		0x00000040
 /* use OTP, OTP is घातered up */
#घोषणा	CST4319_OTP_SEL			0x00000080
 /* use SPROM, OTP is घातered करोwn */
#घोषणा	CST4319_OTP_PWRDN		0x000000c0
 /* gpio [8], sdio/usb mode */
#घोषणा	CST4319_SDIO_USB_MODE		0x00000100
#घोषणा	CST4319_REMAP_SEL_MASK		0x00000600
#घोषणा	CST4319_ILPDIV_EN		0x00000800
#घोषणा	CST4319_XTAL_PD_POL		0x00001000
#घोषणा	CST4319_LPO_SEL			0x00002000
#घोषणा	CST4319_RES_INIT_MODE		0x0000c000
 /* PALDO is configured with बाह्यal PNP */
#घोषणा	CST4319_PALDO_EXTPNP		0x00010000
#घोषणा	CST4319_CBUCK_MODE_MASK		0x00060000
#घोषणा CST4319_CBUCK_MODE_BURST	0x00020000
#घोषणा CST4319_CBUCK_MODE_LPBURST	0x00060000
#घोषणा	CST4319_RCAL_VALID		0x01000000
#घोषणा	CST4319_RCAL_VALUE_MASK		0x3e000000
#घोषणा	CST4319_RCAL_VALUE_SHIFT	25

/* 4336 chip-specअगरic ChipStatus रेजिस्टर bits */
#घोषणा	CST4336_SPI_MODE_MASK		0x00000001
#घोषणा	CST4336_SPROM_PRESENT		0x00000002
#घोषणा	CST4336_OTP_PRESENT		0x00000004
#घोषणा	CST4336_ARMREMAP_0		0x00000008
#घोषणा	CST4336_ILPDIV_EN_MASK		0x00000010
#घोषणा	CST4336_ILPDIV_EN_SHIFT		4
#घोषणा	CST4336_XTAL_PD_POL_MASK	0x00000020
#घोषणा	CST4336_XTAL_PD_POL_SHIFT	5
#घोषणा	CST4336_LPO_SEL_MASK		0x00000040
#घोषणा	CST4336_LPO_SEL_SHIFT		6
#घोषणा	CST4336_RES_INIT_MODE_MASK	0x00000180
#घोषणा	CST4336_RES_INIT_MODE_SHIFT	7
#घोषणा	CST4336_CBUCK_MODE_MASK		0x00000600
#घोषणा	CST4336_CBUCK_MODE_SHIFT	9

/* 4313 chip-specअगरic ChipStatus रेजिस्टर bits */
#घोषणा	CST4313_SPROM_PRESENT			1
#घोषणा	CST4313_OTP_PRESENT			2
#घोषणा	CST4313_SPROM_OTP_SEL_MASK		0x00000002
#घोषणा	CST4313_SPROM_OTP_SEL_SHIFT		0

/* 4313 Chip specअगरic ChipControl रेजिस्टर bits */
 /* 12 mA drive strengh क्रम later 4313 */
#घोषणा CCTRL_4313_12MA_LED_DRIVE    0x00000007

/* Manufacturer Ids */
#घोषणा	MFGID_ARM		0x43b
#घोषणा	MFGID_BRCM		0x4bf
#घोषणा	MFGID_MIPS		0x4a7

/* Enumeration ROM रेजिस्टरs */
#घोषणा	ER_EROMENTRY		0x000
#घोषणा	ER_REMAPCONTROL		0xe00
#घोषणा	ER_REMAPSELECT		0xe04
#घोषणा	ER_MASTERSELECT		0xe10
#घोषणा	ER_ITCR			0xf00
#घोषणा	ER_ITIP			0xf04

/* Erom entries */
#घोषणा	ER_TAG			0xe
#घोषणा	ER_TAG1			0x6
#घोषणा	ER_VALID		1
#घोषणा	ER_CI			0
#घोषणा	ER_MP			2
#घोषणा	ER_ADD			4
#घोषणा	ER_END			0xe
#घोषणा	ER_BAD			0xffffffff

/* EROM CompIdentA */
#घोषणा	CIA_MFG_MASK		0xfff00000
#घोषणा	CIA_MFG_SHIFT		20
#घोषणा	CIA_CID_MASK		0x000fff00
#घोषणा	CIA_CID_SHIFT		8
#घोषणा	CIA_CCL_MASK		0x000000f0
#घोषणा	CIA_CCL_SHIFT		4

/* EROM CompIdentB */
#घोषणा	CIB_REV_MASK		0xff000000
#घोषणा	CIB_REV_SHIFT		24
#घोषणा	CIB_NSW_MASK		0x00f80000
#घोषणा	CIB_NSW_SHIFT		19
#घोषणा	CIB_NMW_MASK		0x0007c000
#घोषणा	CIB_NMW_SHIFT		14
#घोषणा	CIB_NSP_MASK		0x00003e00
#घोषणा	CIB_NSP_SHIFT		9
#घोषणा	CIB_NMP_MASK		0x000001f0
#घोषणा	CIB_NMP_SHIFT		4

/* EROM AddrDesc */
#घोषणा	AD_ADDR_MASK		0xfffff000
#घोषणा	AD_SP_MASK		0x00000f00
#घोषणा	AD_SP_SHIFT		8
#घोषणा	AD_ST_MASK		0x000000c0
#घोषणा	AD_ST_SHIFT		6
#घोषणा	AD_ST_SLAVE		0x00000000
#घोषणा	AD_ST_BRIDGE		0x00000040
#घोषणा	AD_ST_SWRAP		0x00000080
#घोषणा	AD_ST_MWRAP		0x000000c0
#घोषणा	AD_SZ_MASK		0x00000030
#घोषणा	AD_SZ_SHIFT		4
#घोषणा	AD_SZ_4K		0x00000000
#घोषणा	AD_SZ_8K		0x00000010
#घोषणा	AD_SZ_16K		0x00000020
#घोषणा	AD_SZ_SZD		0x00000030
#घोषणा	AD_AG32			0x00000008
#घोषणा	AD_ADDR_ALIGN		0x00000fff
#घोषणा	AD_SZ_BASE		0x00001000	/* 4KB */

/* EROM SizeDesc */
#घोषणा	SD_SZ_MASK		0xfffff000
#घोषणा	SD_SG32			0x00000008
#घोषणा	SD_SZ_ALIGN		0x00000fff

/* PCI config space bit 4 क्रम 4306c0 slow घड़ी source */
#घोषणा	PCI_CFG_GPIO_SCS	0x10
/* PCI config space GPIO 14 क्रम Xtal घातer-up */
#घोषणा PCI_CFG_GPIO_XTAL	0x40
/* PCI config space GPIO 15 क्रम PLL घातer-करोwn */
#घोषणा PCI_CFG_GPIO_PLL	0x80

/* घातer control defines */
#घोषणा PLL_DELAY		150	/* us pll on delay */
#घोषणा FREF_DELAY		200	/* us fref change delay */
#घोषणा	XTAL_ON_DELAY		1000	/* us crystal घातer-on delay */

/* resetctrl */
#घोषणा	AIRC_RESET		1

#घोषणा	NOREV		-1	/* Invalid rev */

/* GPIO Based LED घातersave defines */
#घोषणा DEFAULT_GPIO_ONTIME	10	/* Default: 10% on */
#घोषणा DEFAULT_GPIO_OFFTIME	90	/* Default: 10% on */

/* When Srom support present, fields in sromcontrol */
#घोषणा	SRC_START		0x80000000
#घोषणा	SRC_BUSY		0x80000000
#घोषणा	SRC_OPCODE		0x60000000
#घोषणा	SRC_OP_READ		0x00000000
#घोषणा	SRC_OP_WRITE		0x20000000
#घोषणा	SRC_OP_WRDIS		0x40000000
#घोषणा	SRC_OP_WREN		0x60000000
#घोषणा	SRC_OTPSEL		0x00000010
#घोषणा	SRC_LOCK		0x00000008
#घोषणा	SRC_SIZE_MASK		0x00000006
#घोषणा	SRC_SIZE_1K		0x00000000
#घोषणा	SRC_SIZE_4K		0x00000002
#घोषणा	SRC_SIZE_16K		0x00000004
#घोषणा	SRC_SIZE_SHIFT		1
#घोषणा	SRC_PRESENT		0x00000001

/* External PA enable mask */
#घोषणा GPIO_CTRL_EPA_EN_MASK 0x40

#घोषणा DEFAULT_GPIOTIMERVAL \
	((DEFAULT_GPIO_ONTIME << GPIO_ONTIME_SHIFT) | DEFAULT_GPIO_OFFTIME)

#घोषणा	BADIDX		(SI_MAXCORES + 1)

#घोषणा	IS_SIM(chippkg)	\
	((chippkg == HDLSIM_PKG_ID) || (chippkg == HWSIM_PKG_ID))

#घोषणा	GOODCOREADDR(x, b) \
	(((x) >= (b)) && ((x) < ((b) + SI_MAXCORES * SI_CORE_SIZE)) && \
		IS_ALIGNED((x), SI_CORE_SIZE))

काष्ठा aidmp अणु
	u32 oobselina30;	/* 0x000 */
	u32 oobselina74;	/* 0x004 */
	u32 PAD[6];
	u32 oobselinb30;	/* 0x020 */
	u32 oobselinb74;	/* 0x024 */
	u32 PAD[6];
	u32 oobselinc30;	/* 0x040 */
	u32 oobselinc74;	/* 0x044 */
	u32 PAD[6];
	u32 oobselind30;	/* 0x060 */
	u32 oobselind74;	/* 0x064 */
	u32 PAD[38];
	u32 oobselouta30;	/* 0x100 */
	u32 oobselouta74;	/* 0x104 */
	u32 PAD[6];
	u32 oobseloutb30;	/* 0x120 */
	u32 oobseloutb74;	/* 0x124 */
	u32 PAD[6];
	u32 oobseloutc30;	/* 0x140 */
	u32 oobseloutc74;	/* 0x144 */
	u32 PAD[6];
	u32 oobseloutd30;	/* 0x160 */
	u32 oobseloutd74;	/* 0x164 */
	u32 PAD[38];
	u32 oobsynca;	/* 0x200 */
	u32 oobseloutaen;	/* 0x204 */
	u32 PAD[6];
	u32 oobsyncb;	/* 0x220 */
	u32 oobseloutben;	/* 0x224 */
	u32 PAD[6];
	u32 oobsyncc;	/* 0x240 */
	u32 oobseloutcen;	/* 0x244 */
	u32 PAD[6];
	u32 oobsyncd;	/* 0x260 */
	u32 oobseloutden;	/* 0x264 */
	u32 PAD[38];
	u32 oobaextwidth;	/* 0x300 */
	u32 oobainwidth;	/* 0x304 */
	u32 oobaoutwidth;	/* 0x308 */
	u32 PAD[5];
	u32 oobbextwidth;	/* 0x320 */
	u32 oobbinwidth;	/* 0x324 */
	u32 oobboutwidth;	/* 0x328 */
	u32 PAD[5];
	u32 oobcextwidth;	/* 0x340 */
	u32 oobcinwidth;	/* 0x344 */
	u32 oobcoutwidth;	/* 0x348 */
	u32 PAD[5];
	u32 oobdextwidth;	/* 0x360 */
	u32 oobdinwidth;	/* 0x364 */
	u32 oobकरोutwidth;	/* 0x368 */
	u32 PAD[37];
	u32 ioctrlset;	/* 0x400 */
	u32 ioctrlclear;	/* 0x404 */
	u32 ioctrl;		/* 0x408 */
	u32 PAD[61];
	u32 iostatus;	/* 0x500 */
	u32 PAD[127];
	u32 ioctrlwidth;	/* 0x700 */
	u32 iostatuswidth;	/* 0x704 */
	u32 PAD[62];
	u32 resetctrl;	/* 0x800 */
	u32 resetstatus;	/* 0x804 */
	u32 resetपढ़ोid;	/* 0x808 */
	u32 resetग_लिखोid;	/* 0x80c */
	u32 PAD[60];
	u32 errlogctrl;	/* 0x900 */
	u32 errlogकरोne;	/* 0x904 */
	u32 errlogstatus;	/* 0x908 */
	u32 errlogaddrlo;	/* 0x90c */
	u32 errlogaddrhi;	/* 0x910 */
	u32 errlogid;	/* 0x914 */
	u32 errloguser;	/* 0x918 */
	u32 errlogflags;	/* 0x91c */
	u32 PAD[56];
	u32 पूर्णांकstatus;	/* 0xa00 */
	u32 PAD[127];
	u32 config;		/* 0xe00 */
	u32 PAD[63];
	u32 itcr;		/* 0xf00 */
	u32 PAD[3];
	u32 itipooba;	/* 0xf10 */
	u32 itipoobb;	/* 0xf14 */
	u32 itipoobc;	/* 0xf18 */
	u32 itipoobd;	/* 0xf1c */
	u32 PAD[4];
	u32 itipoobaout;	/* 0xf30 */
	u32 itipoobbout;	/* 0xf34 */
	u32 itipoobcout;	/* 0xf38 */
	u32 itipoobकरोut;	/* 0xf3c */
	u32 PAD[4];
	u32 itopooba;	/* 0xf50 */
	u32 itopoobb;	/* 0xf54 */
	u32 itopoobc;	/* 0xf58 */
	u32 itopoobd;	/* 0xf5c */
	u32 PAD[4];
	u32 itopoobain;	/* 0xf70 */
	u32 itopoobbin;	/* 0xf74 */
	u32 itopoobcin;	/* 0xf78 */
	u32 itopoobdin;	/* 0xf7c */
	u32 PAD[4];
	u32 itopreset;	/* 0xf90 */
	u32 PAD[15];
	u32 peripherialid4;	/* 0xfd0 */
	u32 peripherialid5;	/* 0xfd4 */
	u32 peripherialid6;	/* 0xfd8 */
	u32 peripherialid7;	/* 0xfdc */
	u32 peripherialid0;	/* 0xfe0 */
	u32 peripherialid1;	/* 0xfe4 */
	u32 peripherialid2;	/* 0xfe8 */
	u32 peripherialid3;	/* 0xfec */
	u32 componentid0;	/* 0xff0 */
	u32 componentid1;	/* 0xff4 */
	u32 componentid2;	/* 0xff8 */
	u32 componentid3;	/* 0xffc */
पूर्ण;

अटल bool
ai_buscore_setup(काष्ठा si_info *sii, काष्ठा bcma_device *cc)
अणु
	/* no cores found, bail out */
	अगर (cc->bus->nr_cores == 0)
		वापस false;

	/* get chipcommon rev */
	sii->pub.ccrev = cc->id.rev;

	/* get chipcommon chipstatus */
	sii->chipst = bcma_पढ़ो32(cc, CHIPCREGOFFS(chipstatus));

	/* get chipcommon capabilites */
	sii->pub.cccaps = bcma_पढ़ो32(cc, CHIPCREGOFFS(capabilities));

	/* get pmu rev and caps */
	अगर (ai_get_cccaps(&sii->pub) & CC_CAP_PMU) अणु
		sii->pub.pmucaps = bcma_पढ़ो32(cc,
					       CHIPCREGOFFS(pmucapabilities));
		sii->pub.pmurev = sii->pub.pmucaps & PCAP_REV_MASK;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा si_info *ai_करोattach(काष्ठा si_info *sii,
				   काष्ठा bcma_bus *pbus)
अणु
	काष्ठा si_pub *sih = &sii->pub;
	काष्ठा bcma_device *cc;

	sii->icbus = pbus;
	sii->pcibus = pbus->host_pci;

	/* चयन to Chipcommon core */
	cc = pbus->drv_cc.core;

	sih->chip = pbus->chipinfo.id;
	sih->chiprev = pbus->chipinfo.rev;
	sih->chippkg = pbus->chipinfo.pkg;
	sih->boardvenकरोr = pbus->boardinfo.venकरोr;
	sih->boardtype = pbus->boardinfo.type;

	अगर (!ai_buscore_setup(sii, cc))
		जाओ निकास;

	/* === NVRAM, घड़ी is पढ़ोy === */
	bcma_ग_लिखो32(cc, CHIPCREGOFFS(gpiopullup), 0);
	bcma_ग_लिखो32(cc, CHIPCREGOFFS(gpiopullकरोwn), 0);

	/* PMU specअगरic initializations */
	अगर (ai_get_cccaps(sih) & CC_CAP_PMU) अणु
		(व्योम)si_pmu_measure_alpclk(sih);
	पूर्ण

	वापस sii;

 निकास:

	वापस शून्य;
पूर्ण

/*
 * Allocate a si handle and करो the attach.
 */
काष्ठा si_pub *
ai_attach(काष्ठा bcma_bus *pbus)
अणु
	काष्ठा si_info *sii;

	/* alloc काष्ठा si_info */
	sii = kzalloc(माप(काष्ठा si_info), GFP_ATOMIC);
	अगर (sii == शून्य)
		वापस शून्य;

	अगर (ai_करोattach(sii, pbus) == शून्य) अणु
		kमुक्त(sii);
		वापस शून्य;
	पूर्ण

	वापस (काष्ठा si_pub *) sii;
पूर्ण

/* may be called with core in reset */
व्योम ai_detach(काष्ठा si_pub *sih)
अणु
	काष्ठा si_info *sii;

	sii = container_of(sih, काष्ठा si_info, pub);

	अगर (sii == शून्य)
		वापस;

	kमुक्त(sii);
पूर्ण

/*
 * पढ़ो/modअगरy chipcommon core रेजिस्टर.
 */
uपूर्णांक ai_cc_reg(काष्ठा si_pub *sih, uपूर्णांक regoff, u32 mask, u32 val)
अणु
	काष्ठा bcma_device *cc;
	u32 w;
	काष्ठा si_info *sii;

	sii = container_of(sih, काष्ठा si_info, pub);
	cc = sii->icbus->drv_cc.core;

	/* mask and set */
	अगर (mask || val)
		bcma_maskset32(cc, regoff, ~mask, val);

	/* पढ़ोback */
	w = bcma_पढ़ो32(cc, regoff);

	वापस w;
पूर्ण

/* वापस the slow घड़ी source - LPO, XTAL, or PCI */
अटल uपूर्णांक ai_slowclk_src(काष्ठा si_pub *sih, काष्ठा bcma_device *cc)
अणु
	वापस SCC_SS_XTAL;
पूर्ण

/*
* वापस the ILP (slowघड़ी) min or max frequency
* precondition: we've established the chip has dynamic clk control
*/
अटल uपूर्णांक ai_slowclk_freq(काष्ठा si_pub *sih, bool max_freq,
			    काष्ठा bcma_device *cc)
अणु
	uपूर्णांक भाग;

	/* Chipc rev 10 is InstaClock */
	भाग = bcma_पढ़ो32(cc, CHIPCREGOFFS(प्रणाली_clk_ctl));
	भाग = 4 * ((भाग >> SYCC_CD_SHIFT) + 1);
	वापस max_freq ? XTALMAXFREQ : (XTALMINFREQ / भाग);
पूर्ण

अटल व्योम
ai_clkctl_setdelay(काष्ठा si_pub *sih, काष्ठा bcma_device *cc)
अणु
	uपूर्णांक slowmaxfreq, pll_delay, slowclk;
	uपूर्णांक pll_on_delay, fref_sel_delay;

	pll_delay = PLL_DELAY;

	/*
	 * If the slow घड़ी is not sourced by the xtal then
	 * add the xtal_on_delay since the xtal will also be
	 * घातered करोwn by dynamic clk control logic.
	 */

	slowclk = ai_slowclk_src(sih, cc);
	अगर (slowclk != SCC_SS_XTAL)
		pll_delay += XTAL_ON_DELAY;

	/* Starting with 4318 it is ILP that is used क्रम the delays */
	slowmaxfreq =
	    ai_slowclk_freq(sih, false, cc);

	pll_on_delay = ((slowmaxfreq * pll_delay) + 999999) / 1000000;
	fref_sel_delay = ((slowmaxfreq * FREF_DELAY) + 999999) / 1000000;

	bcma_ग_लिखो32(cc, CHIPCREGOFFS(pll_on_delay), pll_on_delay);
	bcma_ग_लिखो32(cc, CHIPCREGOFFS(fref_sel_delay), fref_sel_delay);
पूर्ण

/* initialize घातer control delay रेजिस्टरs */
व्योम ai_clkctl_init(काष्ठा si_pub *sih)
अणु
	काष्ठा si_info *sii = container_of(sih, काष्ठा si_info, pub);
	काष्ठा bcma_device *cc;

	अगर (!(ai_get_cccaps(sih) & CC_CAP_PWR_CTL))
		वापस;

	cc = sii->icbus->drv_cc.core;
	अगर (cc == शून्य)
		वापस;

	/* set all Instaclk chip ILP to 1 MHz */
	bcma_maskset32(cc, CHIPCREGOFFS(प्रणाली_clk_ctl), SYCC_CD_MASK,
		       (ILP_DIV_1MHZ << SYCC_CD_SHIFT));

	ai_clkctl_setdelay(sih, cc);
पूर्ण

/*
 * वापस the value suitable क्रम writing to the
 * करोt11 core FAST_PWRUP_DELAY रेजिस्टर
 */
u16 ai_clkctl_fast_pwrup_delay(काष्ठा si_pub *sih)
अणु
	काष्ठा si_info *sii;
	काष्ठा bcma_device *cc;
	uपूर्णांक slowminfreq;
	u16 fpdelay;

	sii = container_of(sih, काष्ठा si_info, pub);
	अगर (ai_get_cccaps(sih) & CC_CAP_PMU) अणु
		fpdelay = si_pmu_fast_pwrup_delay(sih);
		वापस fpdelay;
	पूर्ण

	अगर (!(ai_get_cccaps(sih) & CC_CAP_PWR_CTL))
		वापस 0;

	fpdelay = 0;
	cc = sii->icbus->drv_cc.core;
	अगर (cc) अणु
		slowminfreq = ai_slowclk_freq(sih, false, cc);
		fpdelay = (((bcma_पढ़ो32(cc, CHIPCREGOFFS(pll_on_delay)) + 2)
			    * 1000000) + (slowminfreq - 1)) / slowminfreq;
	पूर्ण
	वापस fpdelay;
पूर्ण

/*
 *  घड़ी control policy function throught chipcommon
 *
 *    set dynamic clk control mode (क्रमceslow, क्रमcefast, dynamic)
 *    वापसs true अगर we are क्रमcing fast घड़ी
 *    this is a wrapper over the next पूर्णांकernal function
 *      to allow flexible policy settings क्रम outside caller
 */
bool ai_clkctl_cc(काष्ठा si_pub *sih, क्रमागत bcma_clkmode mode)
अणु
	काष्ठा si_info *sii;
	काष्ठा bcma_device *cc;

	sii = container_of(sih, काष्ठा si_info, pub);

	cc = sii->icbus->drv_cc.core;
	bcma_core_set_घड़ीmode(cc, mode);
	वापस mode == BCMA_CLKMODE_FAST;
पूर्ण

/* Enable BT-COEX & Ex-PA क्रम 4313 */
व्योम ai_epa_4313war(काष्ठा si_pub *sih)
अणु
	काष्ठा si_info *sii = container_of(sih, काष्ठा si_info, pub);
	काष्ठा bcma_device *cc;

	cc = sii->icbus->drv_cc.core;

	/* EPA Fix */
	bcma_set32(cc, CHIPCREGOFFS(gpiocontrol), GPIO_CTRL_EPA_EN_MASK);
पूर्ण

/* check अगर the device is हटाओd */
bool ai_deviceहटाओd(काष्ठा si_pub *sih)
अणु
	u32 w = 0;
	काष्ठा si_info *sii;

	sii = container_of(sih, काष्ठा si_info, pub);

	अगर (sii->icbus->hosttype != BCMA_HOSTTYPE_PCI)
		वापस false;

	pci_पढ़ो_config_dword(sii->pcibus, PCI_VENDOR_ID, &w);
	अगर ((w & 0xFFFF) != PCI_VENDOR_ID_BROADCOM)
		वापस true;

	वापस false;
पूर्ण
