<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/pinctrl/pinmux-xway.c
 *  based on linux/drivers/pinctrl/pinmux-pxa910.c
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 *  Copyright (C) 2015 Martin Schiller <mschiller@tdt.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pinctrl-lantiq.h"

#समावेश <lantiq_soc.h>

/* we have up to 4 banks of 16 bit each */
#घोषणा PINS			16
#घोषणा PORT3			3
#घोषणा PORT(x)			(x / PINS)
#घोषणा PORT_PIN(x)		(x % PINS)

/* we have 2 mux bits that can be set क्रम each pin */
#घोषणा MUX_ALT0	0x1
#घोषणा MUX_ALT1	0x2

/*
 * each bank has this offset apart from the 4th bank that is mixed पूर्णांकo the
 * other 3 ranges
 */
#घोषणा REG_OFF			0x30

/* these are the offsets to our रेजिस्टरs */
#घोषणा GPIO_BASE(p)		(REG_OFF * PORT(p))
#घोषणा GPIO_OUT(p)		GPIO_BASE(p)
#घोषणा GPIO_IN(p)		(GPIO_BASE(p) + 0x04)
#घोषणा GPIO_सूची(p)		(GPIO_BASE(p) + 0x08)
#घोषणा GPIO_ALT0(p)		(GPIO_BASE(p) + 0x0C)
#घोषणा GPIO_ALT1(p)		(GPIO_BASE(p) + 0x10)
#घोषणा GPIO_OD(p)		(GPIO_BASE(p) + 0x14)
#घोषणा GPIO_PUDSEL(p)		(GPIO_BASE(p) + 0x1c)
#घोषणा GPIO_PUDEN(p)		(GPIO_BASE(p) + 0x20)

/* the 4th port needs special offsets क्रम some रेजिस्टरs */
#घोषणा GPIO3_OD		(GPIO_BASE(0) + 0x24)
#घोषणा GPIO3_PUDSEL		(GPIO_BASE(0) + 0x28)
#घोषणा GPIO3_PUDEN		(GPIO_BASE(0) + 0x2C)
#घोषणा GPIO3_ALT1		(GPIO_BASE(PINS) + 0x24)

/* macros to help us access the रेजिस्टरs */
#घोषणा gpio_getbit(m, r, p)	(!!(ltq_r32(m + r) & BIT(p)))
#घोषणा gpio_setbit(m, r, p)	ltq_w32_mask(0, BIT(p), m + r)
#घोषणा gpio_clearbit(m, r, p)	ltq_w32_mask(BIT(p), 0, m + r)

#घोषणा MFP_XWAY(a, f0, f1, f2, f3)	\
	अणु				\
		.name = #a,		\
		.pin = a,		\
		.func = अणु		\
			XWAY_MUX_##f0,	\
			XWAY_MUX_##f1,	\
			XWAY_MUX_##f2,	\
			XWAY_MUX_##f3,	\
		पूर्ण,			\
	पूर्ण

#घोषणा GRP_MUX(a, m, p)		\
	अणु .name = a, .mux = XWAY_MUX_##m, .pins = p, .npins = ARRAY_SIZE(p), पूर्ण

#घोषणा FUNC_MUX(f, m)		\
	अणु .func = f, .mux = XWAY_MUX_##m, पूर्ण

क्रमागत xway_mux अणु
	XWAY_MUX_GPIO = 0,
	XWAY_MUX_SPI,
	XWAY_MUX_ASC,
	XWAY_MUX_USIF,
	XWAY_MUX_PCI,
	XWAY_MUX_CBUS,
	XWAY_MUX_CGU,
	XWAY_MUX_EBU,
	XWAY_MUX_EBU2,
	XWAY_MUX_JTAG,
	XWAY_MUX_MCD,
	XWAY_MUX_EXIN,
	XWAY_MUX_TDM,
	XWAY_MUX_STP,
	XWAY_MUX_SIN,
	XWAY_MUX_GPT,
	XWAY_MUX_NMI,
	XWAY_MUX_MDIO,
	XWAY_MUX_MII,
	XWAY_MUX_EPHY,
	XWAY_MUX_DFE,
	XWAY_MUX_SDIO,
	XWAY_MUX_GPHY,
	XWAY_MUX_SSI,
	XWAY_MUX_WIFI,
	XWAY_MUX_NONE = 0xffff,
पूर्ण;

/* ---------  DEPRECATED: xr9 related code --------- */
/* ----------  use xrx100/xrx200 instead  ---------- */
#घोषणा XR9_MAX_PIN		56

अटल स्थिर काष्ठा ltq_mfp_pin xway_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	NONE,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	NONE,	NONE),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	GPHY),
	MFP_XWAY(GPIO3, GPIO,	CGU,	NONE,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	NONE,	ASC),
	MFP_XWAY(GPIO5, GPIO,	STP,	GPHY,	NONE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	ASC),
	MFP_XWAY(GPIO7, GPIO,	CGU,	PCI,	GPHY),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	NONE),
	MFP_XWAY(GPIO9, GPIO,	ASC,	SPI,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	ASC,	SPI,	NONE),
	MFP_XWAY(GPIO11, GPIO,	ASC,	PCI,	SPI),
	MFP_XWAY(GPIO12, GPIO,	ASC,	NONE,	NONE),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	PCI,	NONE),
	MFP_XWAY(GPIO15, GPIO,	SPI,	JTAG,	NONE),
	MFP_XWAY(GPIO16, GPIO,	SPI,	NONE,	JTAG),
	MFP_XWAY(GPIO17, GPIO,	SPI,	NONE,	JTAG),
	MFP_XWAY(GPIO18, GPIO,	SPI,	NONE,	JTAG),
	MFP_XWAY(GPIO19, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO20, GPIO,	JTAG,	NONE,	NONE),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	NONE,	NONE),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	NONE,	ASC),
	MFP_XWAY(GPIO26, GPIO,	EBU,	NONE,	TDM),
	MFP_XWAY(GPIO27, GPIO,	TDM,	NONE,	ASC),
	MFP_XWAY(GPIO28, GPIO,	GPT,	NONE,	NONE),
	MFP_XWAY(GPIO29, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO30, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	NONE),
	MFP_XWAY(GPIO32, GPIO,	NONE,	NONE,	EBU),
	MFP_XWAY(GPIO33, GPIO,	NONE,	NONE,	EBU),
	MFP_XWAY(GPIO34, GPIO,	NONE,	NONE,	EBU),
	MFP_XWAY(GPIO35, GPIO,	NONE,	NONE,	EBU),
	MFP_XWAY(GPIO36, GPIO,	SIN,	NONE,	EBU),
	MFP_XWAY(GPIO37, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO38, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO39, GPIO,	EXIN,	NONE,	NONE),
	MFP_XWAY(GPIO40, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO41, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, GPIO,	MII,	SIN,	GPHY),
	MFP_XWAY(GPIO45, GPIO,	NONE,	GPHY,	SIN),
	MFP_XWAY(GPIO46, GPIO,	NONE,	NONE,	EXIN),
	MFP_XWAY(GPIO47, GPIO,	MII,	GPHY,	SIN),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO50, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO51, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO52, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO53, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO54, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO55, GPIO,	NONE,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित pins_jtag[] = अणुGPIO15, GPIO16, GPIO17, GPIO19, GPIO35पूर्ण;
अटल स्थिर अचिन्हित pins_asc0[] = अणुGPIO11, GPIO12पूर्ण;
अटल स्थिर अचिन्हित pins_asc0_cts_rts[] = अणुGPIO9, GPIO10पूर्ण;
अटल स्थिर अचिन्हित pins_stp[] = अणुGPIO4, GPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित pins_nmi[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित pins_mdio[] = अणुGPIO42, GPIO43पूर्ण;

अटल स्थिर अचिन्हित pins_gphy0_led0[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित pins_gphy0_led1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित pins_gphy0_led2[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित pins_gphy1_led0[] = अणुGPIO44पूर्ण;
अटल स्थिर अचिन्हित pins_gphy1_led1[] = अणुGPIO45पूर्ण;
अटल स्थिर अचिन्हित pins_gphy1_led2[] = अणुGPIO47पूर्ण;

अटल स्थिर अचिन्हित pins_ebu_a24[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_clk[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_a23[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_रुको[] = अणुGPIO26पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_a25[] = अणुGPIO31पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_rdy[] = अणुGPIO48पूर्ण;
अटल स्थिर अचिन्हित pins_ebu_rd[] = अणुGPIO49पूर्ण;

अटल स्थिर अचिन्हित pins_nand_ale[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित pins_nand_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित pins_nand_cle[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित pins_nand_rdy[] = अणुGPIO48पूर्ण;
अटल स्थिर अचिन्हित pins_nand_rd[] = अणुGPIO49पूर्ण;

अटल स्थिर अचिन्हित xway_exin_pin_map[] = अणुGPIO0, GPIO1, GPIO2, GPIO39, GPIO46, GPIO9पूर्ण;

अटल स्थिर अचिन्हित pins_exin0[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित pins_exin1[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित pins_exin2[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित pins_exin3[] = अणुGPIO39पूर्ण;
अटल स्थिर अचिन्हित pins_exin4[] = अणुGPIO46पूर्ण;
अटल स्थिर अचिन्हित pins_exin5[] = अणुGPIO9पूर्ण;

अटल स्थिर अचिन्हित pins_spi[] = अणुGPIO16, GPIO17, GPIO18पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs1[] = अणुGPIO15पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs2[] = अणुGPIO22पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs3[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs5[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs6[] = अणुGPIO11पूर्ण;

अटल स्थिर अचिन्हित pins_gpt1[] = अणुGPIO28पूर्ण;
अटल स्थिर अचिन्हित pins_gpt2[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित pins_gpt3[] = अणुGPIO6पूर्ण;

अटल स्थिर अचिन्हित pins_clkout0[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित pins_clkout1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित pins_clkout2[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित pins_clkout3[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित pins_pci_gnt1[] = अणुGPIO30पूर्ण;
अटल स्थिर अचिन्हित pins_pci_gnt2[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित pins_pci_gnt3[] = अणुGPIO19पूर्ण;
अटल स्थिर अचिन्हित pins_pci_gnt4[] = अणुGPIO38पूर्ण;
अटल स्थिर अचिन्हित pins_pci_req1[] = अणुGPIO29पूर्ण;
अटल स्थिर अचिन्हित pins_pci_req2[] = अणुGPIO31पूर्ण;
अटल स्थिर अचिन्हित pins_pci_req3[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित pins_pci_req4[] = अणुGPIO37पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group xway_grps[] = अणु
	GRP_MUX("exin0", EXIN, pins_exin0),
	GRP_MUX("exin1", EXIN, pins_exin1),
	GRP_MUX("exin2", EXIN, pins_exin2),
	GRP_MUX("jtag", JTAG, pins_jtag),
	GRP_MUX("ebu a23", EBU, pins_ebu_a23),
	GRP_MUX("ebu a24", EBU, pins_ebu_a24),
	GRP_MUX("ebu a25", EBU, pins_ebu_a25),
	GRP_MUX("ebu clk", EBU, pins_ebu_clk),
	GRP_MUX("ebu cs1", EBU, pins_ebu_cs1),
	GRP_MUX("ebu wait", EBU, pins_ebu_रुको),
	GRP_MUX("nand ale", EBU, pins_nand_ale),
	GRP_MUX("nand cs1", EBU, pins_nand_cs1),
	GRP_MUX("nand cle", EBU, pins_nand_cle),
	GRP_MUX("spi", SPI, pins_spi),
	GRP_MUX("spi_cs1", SPI, pins_spi_cs1),
	GRP_MUX("spi_cs2", SPI, pins_spi_cs2),
	GRP_MUX("spi_cs3", SPI, pins_spi_cs3),
	GRP_MUX("spi_cs4", SPI, pins_spi_cs4),
	GRP_MUX("spi_cs5", SPI, pins_spi_cs5),
	GRP_MUX("spi_cs6", SPI, pins_spi_cs6),
	GRP_MUX("asc0", ASC, pins_asc0),
	GRP_MUX("asc0 cts rts", ASC, pins_asc0_cts_rts),
	GRP_MUX("stp", STP, pins_stp),
	GRP_MUX("nmi", NMI, pins_nmi),
	GRP_MUX("gpt1", GPT, pins_gpt1),
	GRP_MUX("gpt2", GPT, pins_gpt2),
	GRP_MUX("gpt3", GPT, pins_gpt3),
	GRP_MUX("clkout0", CGU, pins_clkout0),
	GRP_MUX("clkout1", CGU, pins_clkout1),
	GRP_MUX("clkout2", CGU, pins_clkout2),
	GRP_MUX("clkout3", CGU, pins_clkout3),
	GRP_MUX("gnt1", PCI, pins_pci_gnt1),
	GRP_MUX("gnt2", PCI, pins_pci_gnt2),
	GRP_MUX("gnt3", PCI, pins_pci_gnt3),
	GRP_MUX("req1", PCI, pins_pci_req1),
	GRP_MUX("req2", PCI, pins_pci_req2),
	GRP_MUX("req3", PCI, pins_pci_req3),
/* xrx only */
	GRP_MUX("nand rdy", EBU, pins_nand_rdy),
	GRP_MUX("nand rd", EBU, pins_nand_rd),
	GRP_MUX("exin3", EXIN, pins_exin3),
	GRP_MUX("exin4", EXIN, pins_exin4),
	GRP_MUX("exin5", EXIN, pins_exin5),
	GRP_MUX("gnt4", PCI, pins_pci_gnt4),
	GRP_MUX("req4", PCI, pins_pci_gnt4),
	GRP_MUX("mdio", MDIO, pins_mdio),
	GRP_MUX("gphy0 led0", GPHY, pins_gphy0_led0),
	GRP_MUX("gphy0 led1", GPHY, pins_gphy0_led1),
	GRP_MUX("gphy0 led2", GPHY, pins_gphy0_led2),
	GRP_MUX("gphy1 led0", GPHY, pins_gphy1_led0),
	GRP_MUX("gphy1 led1", GPHY, pins_gphy1_led1),
	GRP_MUX("gphy1 led2", GPHY, pins_gphy1_led2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर xway_pci_grps[] = अणु"gnt1", "gnt2",
						"gnt3", "req1",
						"req2", "req3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_spi_grps[] = अणु"spi", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_cgu_grps[] = अणु"clkout0", "clkout1",
						"clkout2", "clkout3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_ebu_grps[] = अणु"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu clk",
						"nand ale", "nand cs1",
						"nand cle"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_exin_grps[] = अणु"exin0", "exin1", "exin2"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_gpt_grps[] = अणु"gpt1", "gpt2", "gpt3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_asc_grps[] = अणु"asc0", "asc0 cts rts"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_jtag_grps[] = अणु"jtag"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर xway_nmi_grps[] = अणु"nmi"पूर्ण;

/* ar9/vr9/gr9 */
अटल स्थिर अक्षर * स्थिर xrx_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx_gphy_grps[] = अणु"gphy0 led0", "gphy0 led1",
						"gphy0 led2", "gphy1 led0",
						"gphy1 led1", "gphy1 led2"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx_ebu_grps[] = अणु"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu clk",
						"nand ale", "nand cs1",
						"nand cle", "nand rdy",
						"nand rd"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx_exin_grps[] = अणु"exin0", "exin1", "exin2",
						"exin3", "exin4", "exin5"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx_pci_grps[] = अणु"gnt1", "gnt2",
						"gnt3", "gnt4",
						"req1", "req2",
						"req3", "req4"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func xrx_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(xway_spi_grps)पूर्ण,
	अणु"asc",		ARRAY_AND_SIZE(xway_asc_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(xway_cgu_grps)पूर्ण,
	अणु"jtag",	ARRAY_AND_SIZE(xway_jtag_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(xrx_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(xway_stp_grps)पूर्ण,
	अणु"gpt",		ARRAY_AND_SIZE(xway_gpt_grps)पूर्ण,
	अणु"nmi",		ARRAY_AND_SIZE(xway_nmi_grps)पूर्ण,
	अणु"pci",		ARRAY_AND_SIZE(xrx_pci_grps)पूर्ण,
	अणु"ebu",		ARRAY_AND_SIZE(xrx_ebu_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(xrx_mdio_grps)पूर्ण,
	अणु"gphy",	ARRAY_AND_SIZE(xrx_gphy_grps)पूर्ण,
पूर्ण;

/* ---------  ase related code --------- */
#घोषणा ASE_MAX_PIN		32

अटल स्थिर काष्ठा ltq_mfp_pin ase_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	MII,	TDM),
	MFP_XWAY(GPIO1, GPIO,	STP,	DFE,	EBU),
	MFP_XWAY(GPIO2, GPIO,	STP,	DFE,	EPHY),
	MFP_XWAY(GPIO3, GPIO,	STP,	EPHY,	EBU),
	MFP_XWAY(GPIO4, GPIO,	GPT,	EPHY,	MII),
	MFP_XWAY(GPIO5, GPIO,	MII,	ASC,	GPT),
	MFP_XWAY(GPIO6, GPIO,	MII,	ASC,	EXIN),
	MFP_XWAY(GPIO7, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO8, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO9, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO10, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO11, GPIO,	EBU,	CGU,	JTAG),
	MFP_XWAY(GPIO12, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO13, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO14, GPIO,	EBU,	SPI,	CGU),
	MFP_XWAY(GPIO15, GPIO,	EBU,	SPI,	SDIO),
	MFP_XWAY(GPIO16, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO17, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO18, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO19, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO20, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO21, GPIO,	EBU,	MII,	EBU2),
	MFP_XWAY(GPIO22, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO24, GPIO,	EBU,	EBU2,	MDIO),
	MFP_XWAY(GPIO25, GPIO,	EBU,	MII,	GPT),
	MFP_XWAY(GPIO26, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	EBU,	NONE,	MDIO),
	MFP_XWAY(GPIO28, GPIO,	MII,	EBU,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	EBU,	MII,	EXIN),
	MFP_XWAY(GPIO30, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO31, GPIO,	NONE,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित ase_exin_pin_map[] = अणुGPIO6, GPIO29, GPIO0पूर्ण;

अटल स्थिर अचिन्हित ase_pins_exin0[] = अणुGPIO6पूर्ण;
अटल स्थिर अचिन्हित ase_pins_exin1[] = अणुGPIO29पूर्ण;
अटल स्थिर अचिन्हित ase_pins_exin2[] = अणुGPIO0पूर्ण;

अटल स्थिर अचिन्हित ase_pins_jtag[] = अणुGPIO7, GPIO8, GPIO9, GPIO10, GPIO11पूर्ण;
अटल स्थिर अचिन्हित ase_pins_asc[] = अणुGPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित ase_pins_stp[] = अणुGPIO1, GPIO2, GPIO3पूर्ण;
अटल स्थिर अचिन्हित ase_pins_mdio[] = अणुGPIO24, GPIO27पूर्ण;
अटल स्थिर अचिन्हित ase_pins_ephy_led0[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित ase_pins_ephy_led1[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित ase_pins_ephy_led2[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित ase_pins_dfe_led0[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित ase_pins_dfe_led1[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित ase_pins_spi[] = अणुGPIO8, GPIO9, GPIO10पूर्ण; /* DEPRECATED */
अटल स्थिर अचिन्हित ase_pins_spi_di[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित ase_pins_spi_करो[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित ase_pins_spi_clk[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित ase_pins_spi_cs1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित ase_pins_spi_cs2[] = अणुGPIO15पूर्ण;
अटल स्थिर अचिन्हित ase_pins_spi_cs3[] = अणुGPIO14पूर्ण;

अटल स्थिर अचिन्हित ase_pins_gpt1[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित ase_pins_gpt2[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित ase_pins_gpt3[] = अणुGPIO25पूर्ण;

अटल स्थिर अचिन्हित ase_pins_clkout0[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित ase_pins_clkout1[] = अणुGPIO22पूर्ण;
अटल स्थिर अचिन्हित ase_pins_clkout2[] = अणुGPIO14पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group ase_grps[] = अणु
	GRP_MUX("exin0", EXIN, ase_pins_exin0),
	GRP_MUX("exin1", EXIN, ase_pins_exin1),
	GRP_MUX("exin2", EXIN, ase_pins_exin2),
	GRP_MUX("jtag", JTAG, ase_pins_jtag),
	GRP_MUX("spi", SPI, ase_pins_spi), /* DEPRECATED */
	GRP_MUX("spi_di", SPI, ase_pins_spi_di),
	GRP_MUX("spi_do", SPI, ase_pins_spi_करो),
	GRP_MUX("spi_clk", SPI, ase_pins_spi_clk),
	GRP_MUX("spi_cs1", SPI, ase_pins_spi_cs1),
	GRP_MUX("spi_cs2", SPI, ase_pins_spi_cs2),
	GRP_MUX("spi_cs3", SPI, ase_pins_spi_cs3),
	GRP_MUX("asc", ASC, ase_pins_asc),
	GRP_MUX("stp", STP, ase_pins_stp),
	GRP_MUX("gpt1", GPT, ase_pins_gpt1),
	GRP_MUX("gpt2", GPT, ase_pins_gpt2),
	GRP_MUX("gpt3", GPT, ase_pins_gpt3),
	GRP_MUX("clkout0", CGU, ase_pins_clkout0),
	GRP_MUX("clkout1", CGU, ase_pins_clkout1),
	GRP_MUX("clkout2", CGU, ase_pins_clkout2),
	GRP_MUX("mdio", MDIO, ase_pins_mdio),
	GRP_MUX("dfe led0", DFE, ase_pins_dfe_led0),
	GRP_MUX("dfe led1", DFE, ase_pins_dfe_led1),
	GRP_MUX("ephy led0", EPHY, ase_pins_ephy_led0),
	GRP_MUX("ephy led1", EPHY, ase_pins_ephy_led1),
	GRP_MUX("ephy led2", EPHY, ase_pins_ephy_led2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर ase_exin_grps[] = अणु"exin0", "exin1", "exin2"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_gpt_grps[] = अणु"gpt1", "gpt2", "gpt3"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_cgu_grps[] = अणु"clkout0", "clkout1",
						"clkout2"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_dfe_grps[] = अणु"dfe led0", "dfe led1"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_ephy_grps[] = अणु"ephy led0", "ephy led1",
						"ephy led2"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_asc_grps[] = अणु"asc"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_jtag_grps[] = अणु"jtag"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर ase_spi_grps[] = अणु"spi",  /* DEPRECATED */
						"spi_di", "spi_do",
						"spi_clk", "spi_cs1",
						"spi_cs2", "spi_cs3"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func ase_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(ase_spi_grps)पूर्ण,
	अणु"asc",		ARRAY_AND_SIZE(ase_asc_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(ase_cgu_grps)पूर्ण,
	अणु"jtag",	ARRAY_AND_SIZE(ase_jtag_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(ase_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(ase_stp_grps)पूर्ण,
	अणु"gpt",		ARRAY_AND_SIZE(ase_gpt_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(ase_mdio_grps)पूर्ण,
	अणु"ephy",	ARRAY_AND_SIZE(ase_ephy_grps)पूर्ण,
	अणु"dfe",		ARRAY_AND_SIZE(ase_dfe_grps)पूर्ण,
पूर्ण;

/* ---------  danube related code --------- */
#घोषणा DANUBE_MAX_PIN		32

अटल स्थिर काष्ठा ltq_mfp_pin danube_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	MII),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	MII),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	ASC),
	MFP_XWAY(GPIO5, GPIO,	STP,	MII,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	ASC),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	MII),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	MII),
	MFP_XWAY(GPIO9, GPIO,	ASC,	SPI,	MII),
	MFP_XWAY(GPIO10, GPIO,	ASC,	SPI,	MII),
	MFP_XWAY(GPIO11, GPIO,	ASC,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	ASC,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	MII),
	MFP_XWAY(GPIO14, GPIO,	CGU,	CBUS,	MII),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	MII),
	MFP_XWAY(GPIO20, GPIO,	JTAG,	SDIO,	MII),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	MCD,	MII),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO28, GPIO,	GPT,	MII,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	MII),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	MII),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	MII),
पूर्ण;

अटल स्थिर अचिन्हित danube_exin_pin_map[] = अणुGPIO0, GPIO1, GPIO2पूर्ण;

अटल स्थिर अचिन्हित danube_pins_exin0[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित danube_pins_exin1[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित danube_pins_exin2[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित danube_pins_jtag[] = अणुGPIO15, GPIO16, GPIO17, GPIO18, GPIO20पूर्ण;
अटल स्थिर अचिन्हित danube_pins_asc0[] = अणुGPIO11, GPIO12पूर्ण;
अटल स्थिर अचिन्हित danube_pins_asc0_cts_rts[] = अणुGPIO9, GPIO10पूर्ण;
अटल स्थिर अचिन्हित danube_pins_stp[] = अणुGPIO4, GPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित danube_pins_nmi[] = अणुGPIO8पूर्ण;

अटल स्थिर अचिन्हित danube_pins_dfe_led0[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित danube_pins_dfe_led1[] = अणुGPIO5पूर्ण;

अटल स्थिर अचिन्हित danube_pins_ebu_a24[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित danube_pins_ebu_clk[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित danube_pins_ebu_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित danube_pins_ebu_a23[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित danube_pins_ebu_रुको[] = अणुGPIO26पूर्ण;
अटल स्थिर अचिन्हित danube_pins_ebu_a25[] = अणुGPIO31पूर्ण;

अटल स्थिर अचिन्हित danube_pins_nand_ale[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित danube_pins_nand_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित danube_pins_nand_cle[] = अणुGPIO24पूर्ण;

अटल स्थिर अचिन्हित danube_pins_spi[] = अणुGPIO16, GPIO17, GPIO18पूर्ण; /* DEPRECATED */
अटल स्थिर अचिन्हित danube_pins_spi_di[] = अणुGPIO16पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_करो[] = अणुGPIO17पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_clk[] = अणुGPIO18पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs1[] = अणुGPIO15पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs2[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs3[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs5[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित danube_pins_spi_cs6[] = अणुGPIO11पूर्ण;

अटल स्थिर अचिन्हित danube_pins_gpt1[] = अणुGPIO28पूर्ण;
अटल स्थिर अचिन्हित danube_pins_gpt2[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित danube_pins_gpt3[] = अणुGPIO6पूर्ण;

अटल स्थिर अचिन्हित danube_pins_clkout0[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित danube_pins_clkout1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित danube_pins_clkout2[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित danube_pins_clkout3[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित danube_pins_pci_gnt1[] = अणुGPIO30पूर्ण;
अटल स्थिर अचिन्हित danube_pins_pci_gnt2[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित danube_pins_pci_gnt3[] = अणुGPIO19पूर्ण;
अटल स्थिर अचिन्हित danube_pins_pci_req1[] = अणुGPIO29पूर्ण;
अटल स्थिर अचिन्हित danube_pins_pci_req2[] = अणुGPIO31पूर्ण;
अटल स्थिर अचिन्हित danube_pins_pci_req3[] = अणुGPIO3पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group danube_grps[] = अणु
	GRP_MUX("exin0", EXIN, danube_pins_exin0),
	GRP_MUX("exin1", EXIN, danube_pins_exin1),
	GRP_MUX("exin2", EXIN, danube_pins_exin2),
	GRP_MUX("jtag", JTAG, danube_pins_jtag),
	GRP_MUX("ebu a23", EBU, danube_pins_ebu_a23),
	GRP_MUX("ebu a24", EBU, danube_pins_ebu_a24),
	GRP_MUX("ebu a25", EBU, danube_pins_ebu_a25),
	GRP_MUX("ebu clk", EBU, danube_pins_ebu_clk),
	GRP_MUX("ebu cs1", EBU, danube_pins_ebu_cs1),
	GRP_MUX("ebu wait", EBU, danube_pins_ebu_रुको),
	GRP_MUX("nand ale", EBU, danube_pins_nand_ale),
	GRP_MUX("nand cs1", EBU, danube_pins_nand_cs1),
	GRP_MUX("nand cle", EBU, danube_pins_nand_cle),
	GRP_MUX("spi", SPI, danube_pins_spi), /* DEPRECATED */
	GRP_MUX("spi_di", SPI, danube_pins_spi_di),
	GRP_MUX("spi_do", SPI, danube_pins_spi_करो),
	GRP_MUX("spi_clk", SPI, danube_pins_spi_clk),
	GRP_MUX("spi_cs1", SPI, danube_pins_spi_cs1),
	GRP_MUX("spi_cs2", SPI, danube_pins_spi_cs2),
	GRP_MUX("spi_cs3", SPI, danube_pins_spi_cs3),
	GRP_MUX("spi_cs4", SPI, danube_pins_spi_cs4),
	GRP_MUX("spi_cs5", SPI, danube_pins_spi_cs5),
	GRP_MUX("spi_cs6", SPI, danube_pins_spi_cs6),
	GRP_MUX("asc0", ASC, danube_pins_asc0),
	GRP_MUX("asc0 cts rts", ASC, danube_pins_asc0_cts_rts),
	GRP_MUX("stp", STP, danube_pins_stp),
	GRP_MUX("nmi", NMI, danube_pins_nmi),
	GRP_MUX("gpt1", GPT, danube_pins_gpt1),
	GRP_MUX("gpt2", GPT, danube_pins_gpt2),
	GRP_MUX("gpt3", GPT, danube_pins_gpt3),
	GRP_MUX("clkout0", CGU, danube_pins_clkout0),
	GRP_MUX("clkout1", CGU, danube_pins_clkout1),
	GRP_MUX("clkout2", CGU, danube_pins_clkout2),
	GRP_MUX("clkout3", CGU, danube_pins_clkout3),
	GRP_MUX("gnt1", PCI, danube_pins_pci_gnt1),
	GRP_MUX("gnt2", PCI, danube_pins_pci_gnt2),
	GRP_MUX("gnt3", PCI, danube_pins_pci_gnt3),
	GRP_MUX("req1", PCI, danube_pins_pci_req1),
	GRP_MUX("req2", PCI, danube_pins_pci_req2),
	GRP_MUX("req3", PCI, danube_pins_pci_req3),
	GRP_MUX("dfe led0", DFE, danube_pins_dfe_led0),
	GRP_MUX("dfe led1", DFE, danube_pins_dfe_led1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर danube_pci_grps[] = अणु"gnt1", "gnt2",
						"gnt3", "req1",
						"req2", "req3"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_spi_grps[] = अणु"spi", /* DEPRECATED */
						"spi_di", "spi_do",
						"spi_clk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_cgu_grps[] = अणु"clkout0", "clkout1",
						"clkout2", "clkout3"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_ebu_grps[] = अणु"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu clk",
						"nand ale", "nand cs1",
						"nand cle"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_dfe_grps[] = अणु"dfe led0", "dfe led1"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_exin_grps[] = अणु"exin0", "exin1", "exin2"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_gpt_grps[] = अणु"gpt1", "gpt2", "gpt3"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_asc_grps[] = अणु"asc0", "asc0 cts rts"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_jtag_grps[] = अणु"jtag"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर danube_nmi_grps[] = अणु"nmi"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func danube_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(danube_spi_grps)पूर्ण,
	अणु"asc",		ARRAY_AND_SIZE(danube_asc_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(danube_cgu_grps)पूर्ण,
	अणु"jtag",	ARRAY_AND_SIZE(danube_jtag_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(danube_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(danube_stp_grps)पूर्ण,
	अणु"gpt",		ARRAY_AND_SIZE(danube_gpt_grps)पूर्ण,
	अणु"nmi",		ARRAY_AND_SIZE(danube_nmi_grps)पूर्ण,
	अणु"pci",		ARRAY_AND_SIZE(danube_pci_grps)पूर्ण,
	अणु"ebu",		ARRAY_AND_SIZE(danube_ebu_grps)पूर्ण,
	अणु"dfe",		ARRAY_AND_SIZE(danube_dfe_grps)पूर्ण,
पूर्ण;

/* ---------  xrx100 related code --------- */
#घोषणा XRX100_MAX_PIN		56

अटल स्थिर काष्ठा ltq_mfp_pin xrx100_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	SIN),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	NONE),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	ASC),
	MFP_XWAY(GPIO5, GPIO,	STP,	NONE,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	ASC),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	NONE),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	NONE),
	MFP_XWAY(GPIO9, GPIO,	ASC,	SPI,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	ASC,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	ASC,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	ASC,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	NONE,	NONE),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	CGU),
	MFP_XWAY(GPIO20, GPIO,	NONE,	SDIO,	EBU),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	NONE,	EBU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO28, GPIO,	GPT,	NONE,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	NONE),
	MFP_XWAY(GPIO32, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO33, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO34, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO37, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO38, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO39, GPIO,	NONE,	EXIN,	NONE),
	MFP_XWAY(GPIO40, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO41, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, GPIO,	MII,	SIN,	NONE),
	MFP_XWAY(GPIO45, GPIO,	MII,	NONE,	SIN),
	MFP_XWAY(GPIO46, GPIO,	MII,	NONE,	EXIN),
	MFP_XWAY(GPIO47, GPIO,	MII,	NONE,	SIN),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO50, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO51, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO52, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO53, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO54, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO55, GPIO,	NONE,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित xrx100_exin_pin_map[] = अणुGPIO0, GPIO1, GPIO2, GPIO39, GPIO10, GPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_exin0[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_exin1[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_exin2[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_exin3[] = अणुGPIO39पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_exin4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_exin5[] = अणुGPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_asc0[] = अणुGPIO11, GPIO12पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_asc0_cts_rts[] = अणुGPIO9, GPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_stp[] = अणुGPIO4, GPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_nmi[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_mdio[] = अणुGPIO42, GPIO43पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_dfe_led0[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_dfe_led1[] = अणुGPIO5पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_ebu_a24[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_ebu_clk[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_ebu_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_ebu_a23[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_ebu_रुको[] = अणुGPIO26पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_ebu_a25[] = अणुGPIO31पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_nand_ale[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_nand_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_nand_cle[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_nand_rdy[] = अणुGPIO48पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_nand_rd[] = अणुGPIO49पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_spi_di[] = अणुGPIO16पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_करो[] = अणुGPIO17पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_clk[] = अणुGPIO18पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs1[] = अणुGPIO15पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs2[] = अणुGPIO22पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs3[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs5[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_spi_cs6[] = अणुGPIO11पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_gpt1[] = अणुGPIO28पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_gpt2[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_gpt3[] = अणुGPIO6पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_clkout0[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_clkout1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_clkout2[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_clkout3[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित xrx100_pins_pci_gnt1[] = अणुGPIO30पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_gnt2[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_gnt3[] = अणुGPIO19पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_gnt4[] = अणुGPIO38पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_req1[] = अणुGPIO29पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_req2[] = अणुGPIO31पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_req3[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित xrx100_pins_pci_req4[] = अणुGPIO37पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group xrx100_grps[] = अणु
	GRP_MUX("exin0", EXIN, xrx100_pins_exin0),
	GRP_MUX("exin1", EXIN, xrx100_pins_exin1),
	GRP_MUX("exin2", EXIN, xrx100_pins_exin2),
	GRP_MUX("exin3", EXIN, xrx100_pins_exin3),
	GRP_MUX("exin4", EXIN, xrx100_pins_exin4),
	GRP_MUX("exin5", EXIN, xrx100_pins_exin5),
	GRP_MUX("ebu a23", EBU, xrx100_pins_ebu_a23),
	GRP_MUX("ebu a24", EBU, xrx100_pins_ebu_a24),
	GRP_MUX("ebu a25", EBU, xrx100_pins_ebu_a25),
	GRP_MUX("ebu clk", EBU, xrx100_pins_ebu_clk),
	GRP_MUX("ebu cs1", EBU, xrx100_pins_ebu_cs1),
	GRP_MUX("ebu wait", EBU, xrx100_pins_ebu_रुको),
	GRP_MUX("nand ale", EBU, xrx100_pins_nand_ale),
	GRP_MUX("nand cs1", EBU, xrx100_pins_nand_cs1),
	GRP_MUX("nand cle", EBU, xrx100_pins_nand_cle),
	GRP_MUX("nand rdy", EBU, xrx100_pins_nand_rdy),
	GRP_MUX("nand rd", EBU, xrx100_pins_nand_rd),
	GRP_MUX("spi_di", SPI, xrx100_pins_spi_di),
	GRP_MUX("spi_do", SPI, xrx100_pins_spi_करो),
	GRP_MUX("spi_clk", SPI, xrx100_pins_spi_clk),
	GRP_MUX("spi_cs1", SPI, xrx100_pins_spi_cs1),
	GRP_MUX("spi_cs2", SPI, xrx100_pins_spi_cs2),
	GRP_MUX("spi_cs3", SPI, xrx100_pins_spi_cs3),
	GRP_MUX("spi_cs4", SPI, xrx100_pins_spi_cs4),
	GRP_MUX("spi_cs5", SPI, xrx100_pins_spi_cs5),
	GRP_MUX("spi_cs6", SPI, xrx100_pins_spi_cs6),
	GRP_MUX("asc0", ASC, xrx100_pins_asc0),
	GRP_MUX("asc0 cts rts", ASC, xrx100_pins_asc0_cts_rts),
	GRP_MUX("stp", STP, xrx100_pins_stp),
	GRP_MUX("nmi", NMI, xrx100_pins_nmi),
	GRP_MUX("gpt1", GPT, xrx100_pins_gpt1),
	GRP_MUX("gpt2", GPT, xrx100_pins_gpt2),
	GRP_MUX("gpt3", GPT, xrx100_pins_gpt3),
	GRP_MUX("clkout0", CGU, xrx100_pins_clkout0),
	GRP_MUX("clkout1", CGU, xrx100_pins_clkout1),
	GRP_MUX("clkout2", CGU, xrx100_pins_clkout2),
	GRP_MUX("clkout3", CGU, xrx100_pins_clkout3),
	GRP_MUX("gnt1", PCI, xrx100_pins_pci_gnt1),
	GRP_MUX("gnt2", PCI, xrx100_pins_pci_gnt2),
	GRP_MUX("gnt3", PCI, xrx100_pins_pci_gnt3),
	GRP_MUX("gnt4", PCI, xrx100_pins_pci_gnt4),
	GRP_MUX("req1", PCI, xrx100_pins_pci_req1),
	GRP_MUX("req2", PCI, xrx100_pins_pci_req2),
	GRP_MUX("req3", PCI, xrx100_pins_pci_req3),
	GRP_MUX("req4", PCI, xrx100_pins_pci_req4),
	GRP_MUX("mdio", MDIO, xrx100_pins_mdio),
	GRP_MUX("dfe led0", DFE, xrx100_pins_dfe_led0),
	GRP_MUX("dfe led1", DFE, xrx100_pins_dfe_led1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर xrx100_pci_grps[] = अणु"gnt1", "gnt2",
						"gnt3", "gnt4",
						"req1", "req2",
						"req3", "req4"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_spi_grps[] = अणु"spi_di", "spi_do",
						"spi_clk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_cgu_grps[] = अणु"clkout0", "clkout1",
						"clkout2", "clkout3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_ebu_grps[] = अणु"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu clk",
						"nand ale", "nand cs1",
						"nand cle", "nand rdy",
						"nand rd"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_exin_grps[] = अणु"exin0", "exin1", "exin2",
						"exin3", "exin4", "exin5"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_gpt_grps[] = अणु"gpt1", "gpt2", "gpt3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_asc_grps[] = अणु"asc0", "asc0 cts rts"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_nmi_grps[] = अणु"nmi"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx100_dfe_grps[] = अणु"dfe led0", "dfe led1"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func xrx100_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(xrx100_spi_grps)पूर्ण,
	अणु"asc",		ARRAY_AND_SIZE(xrx100_asc_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(xrx100_cgu_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(xrx100_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(xrx100_stp_grps)पूर्ण,
	अणु"gpt",		ARRAY_AND_SIZE(xrx100_gpt_grps)पूर्ण,
	अणु"nmi",		ARRAY_AND_SIZE(xrx100_nmi_grps)पूर्ण,
	अणु"pci",		ARRAY_AND_SIZE(xrx100_pci_grps)पूर्ण,
	अणु"ebu",		ARRAY_AND_SIZE(xrx100_ebu_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(xrx100_mdio_grps)पूर्ण,
	अणु"dfe",		ARRAY_AND_SIZE(xrx100_dfe_grps)पूर्ण,
पूर्ण;

/* ---------  xrx200 related code --------- */
#घोषणा XRX200_MAX_PIN		50

अटल स्थिर काष्ठा ltq_mfp_pin xrx200_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	SIN),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	GPHY),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	USIF),
	MFP_XWAY(GPIO5, GPIO,	STP,	GPHY,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	USIF),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	GPHY),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	NONE),
	MFP_XWAY(GPIO9, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	USIF,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	USIF,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	CBUS,	USIF),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	CGU),
	MFP_XWAY(GPIO20, GPIO,	NONE,	SDIO,	EBU),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	CGU,	EBU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	USIF),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	USIF),
	MFP_XWAY(GPIO28, GPIO,	GPT,	PCI,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	EXIN),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	NONE),
	MFP_XWAY(GPIO32, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO33, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO34, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	SIN,	SSI,	EXIN),
	MFP_XWAY(GPIO37, GPIO,	USIF,	NONE,	PCI),
	MFP_XWAY(GPIO38, GPIO,	PCI,	USIF,	NONE),
	MFP_XWAY(GPIO39, GPIO,	USIF,	EXIN,	NONE),
	MFP_XWAY(GPIO40, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO41, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, GPIO,	MII,	SIN,	GPHY),
	MFP_XWAY(GPIO45, GPIO,	MII,	GPHY,	SIN),
	MFP_XWAY(GPIO46, GPIO,	MII,	NONE,	EXIN),
	MFP_XWAY(GPIO47, GPIO,	MII,	GPHY,	SIN),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित xrx200_exin_pin_map[] = अणुGPIO0, GPIO1, GPIO2, GPIO39, GPIO10, GPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_exin0[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_exin1[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_exin2[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_exin3[] = अणुGPIO39पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_exin4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_exin5[] = अणुGPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_rx[] = अणुGPIO11पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_tx[] = अणुGPIO12पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_rts[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_cts[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_dtr[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_dsr[] = अणुGPIO6पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_dcd[] = अणुGPIO25पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_uart_ri[] = अणुGPIO27पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_di[] = अणुGPIO11पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_करो[] = अणुGPIO12पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_clk[] = अणुGPIO38पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_cs0[] = अणुGPIO37पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_cs1[] = अणुGPIO39पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_usअगर_spi_cs2[] = अणुGPIO14पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_stp[] = अणुGPIO4, GPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_nmi[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_mdio[] = अणुGPIO42, GPIO43पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_dfe_led0[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_dfe_led1[] = अणुGPIO5पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_gphy0_led0[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gphy0_led1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gphy0_led2[] = अणुGPIO2पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gphy1_led0[] = अणुGPIO44पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gphy1_led1[] = अणुGPIO45पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gphy1_led2[] = अणुGPIO47पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_ebu_a24[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_ebu_clk[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_ebu_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_ebu_a23[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_ebu_रुको[] = अणुGPIO26पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_ebu_a25[] = अणुGPIO31पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_nand_ale[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_nand_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_nand_cle[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_nand_rdy[] = अणुGPIO48पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_nand_rd[] = अणुGPIO49पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_spi_di[] = अणुGPIO16पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_करो[] = अणुGPIO17पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_clk[] = अणुGPIO18पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs1[] = अणुGPIO15पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs2[] = अणुGPIO22पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs3[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs5[] = अणुGPIO9पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_spi_cs6[] = अणुGPIO11पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_gpt1[] = अणुGPIO28पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gpt2[] = अणुGPIO21पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_gpt3[] = अणुGPIO6पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_clkout0[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_clkout1[] = अणुGPIO7पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_clkout2[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_clkout3[] = अणुGPIO2पूर्ण;

अटल स्थिर अचिन्हित xrx200_pins_pci_gnt1[] = अणुGPIO28पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_gnt2[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_gnt3[] = अणुGPIO19पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_gnt4[] = अणुGPIO38पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_req1[] = अणुGPIO29पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_req2[] = अणुGPIO31पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_req3[] = अणुGPIO3पूर्ण;
अटल स्थिर अचिन्हित xrx200_pins_pci_req4[] = अणुGPIO37पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group xrx200_grps[] = अणु
	GRP_MUX("exin0", EXIN, xrx200_pins_exin0),
	GRP_MUX("exin1", EXIN, xrx200_pins_exin1),
	GRP_MUX("exin2", EXIN, xrx200_pins_exin2),
	GRP_MUX("exin3", EXIN, xrx200_pins_exin3),
	GRP_MUX("exin4", EXIN, xrx200_pins_exin4),
	GRP_MUX("exin5", EXIN, xrx200_pins_exin5),
	GRP_MUX("ebu a23", EBU, xrx200_pins_ebu_a23),
	GRP_MUX("ebu a24", EBU, xrx200_pins_ebu_a24),
	GRP_MUX("ebu a25", EBU, xrx200_pins_ebu_a25),
	GRP_MUX("ebu clk", EBU, xrx200_pins_ebu_clk),
	GRP_MUX("ebu cs1", EBU, xrx200_pins_ebu_cs1),
	GRP_MUX("ebu wait", EBU, xrx200_pins_ebu_रुको),
	GRP_MUX("nand ale", EBU, xrx200_pins_nand_ale),
	GRP_MUX("nand cs1", EBU, xrx200_pins_nand_cs1),
	GRP_MUX("nand cle", EBU, xrx200_pins_nand_cle),
	GRP_MUX("nand rdy", EBU, xrx200_pins_nand_rdy),
	GRP_MUX("nand rd", EBU, xrx200_pins_nand_rd),
	GRP_MUX("spi_di", SPI, xrx200_pins_spi_di),
	GRP_MUX("spi_do", SPI, xrx200_pins_spi_करो),
	GRP_MUX("spi_clk", SPI, xrx200_pins_spi_clk),
	GRP_MUX("spi_cs1", SPI, xrx200_pins_spi_cs1),
	GRP_MUX("spi_cs2", SPI, xrx200_pins_spi_cs2),
	GRP_MUX("spi_cs3", SPI, xrx200_pins_spi_cs3),
	GRP_MUX("spi_cs4", SPI, xrx200_pins_spi_cs4),
	GRP_MUX("spi_cs5", SPI, xrx200_pins_spi_cs5),
	GRP_MUX("spi_cs6", SPI, xrx200_pins_spi_cs6),
	GRP_MUX("usif uart_rx", USIF, xrx200_pins_usअगर_uart_rx),
	GRP_MUX("usif uart_tx", USIF, xrx200_pins_usअगर_uart_tx),
	GRP_MUX("usif uart_rts", USIF, xrx200_pins_usअगर_uart_rts),
	GRP_MUX("usif uart_cts", USIF, xrx200_pins_usअगर_uart_cts),
	GRP_MUX("usif uart_dtr", USIF, xrx200_pins_usअगर_uart_dtr),
	GRP_MUX("usif uart_dsr", USIF, xrx200_pins_usअगर_uart_dsr),
	GRP_MUX("usif uart_dcd", USIF, xrx200_pins_usअगर_uart_dcd),
	GRP_MUX("usif uart_ri", USIF, xrx200_pins_usअगर_uart_ri),
	GRP_MUX("usif spi_di", USIF, xrx200_pins_usअगर_spi_di),
	GRP_MUX("usif spi_do", USIF, xrx200_pins_usअगर_spi_करो),
	GRP_MUX("usif spi_clk", USIF, xrx200_pins_usअगर_spi_clk),
	GRP_MUX("usif spi_cs0", USIF, xrx200_pins_usअगर_spi_cs0),
	GRP_MUX("usif spi_cs1", USIF, xrx200_pins_usअगर_spi_cs1),
	GRP_MUX("usif spi_cs2", USIF, xrx200_pins_usअगर_spi_cs2),
	GRP_MUX("stp", STP, xrx200_pins_stp),
	GRP_MUX("nmi", NMI, xrx200_pins_nmi),
	GRP_MUX("gpt1", GPT, xrx200_pins_gpt1),
	GRP_MUX("gpt2", GPT, xrx200_pins_gpt2),
	GRP_MUX("gpt3", GPT, xrx200_pins_gpt3),
	GRP_MUX("clkout0", CGU, xrx200_pins_clkout0),
	GRP_MUX("clkout1", CGU, xrx200_pins_clkout1),
	GRP_MUX("clkout2", CGU, xrx200_pins_clkout2),
	GRP_MUX("clkout3", CGU, xrx200_pins_clkout3),
	GRP_MUX("gnt1", PCI, xrx200_pins_pci_gnt1),
	GRP_MUX("gnt2", PCI, xrx200_pins_pci_gnt2),
	GRP_MUX("gnt3", PCI, xrx200_pins_pci_gnt3),
	GRP_MUX("gnt4", PCI, xrx200_pins_pci_gnt4),
	GRP_MUX("req1", PCI, xrx200_pins_pci_req1),
	GRP_MUX("req2", PCI, xrx200_pins_pci_req2),
	GRP_MUX("req3", PCI, xrx200_pins_pci_req3),
	GRP_MUX("req4", PCI, xrx200_pins_pci_req4),
	GRP_MUX("mdio", MDIO, xrx200_pins_mdio),
	GRP_MUX("dfe led0", DFE, xrx200_pins_dfe_led0),
	GRP_MUX("dfe led1", DFE, xrx200_pins_dfe_led1),
	GRP_MUX("gphy0 led0", GPHY, xrx200_pins_gphy0_led0),
	GRP_MUX("gphy0 led1", GPHY, xrx200_pins_gphy0_led1),
	GRP_MUX("gphy0 led2", GPHY, xrx200_pins_gphy0_led2),
	GRP_MUX("gphy1 led0", GPHY, xrx200_pins_gphy1_led0),
	GRP_MUX("gphy1 led1", GPHY, xrx200_pins_gphy1_led1),
	GRP_MUX("gphy1 led2", GPHY, xrx200_pins_gphy1_led2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर xrx200_pci_grps[] = अणु"gnt1", "gnt2",
						"gnt3", "gnt4",
						"req1", "req2",
						"req3", "req4"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_spi_grps[] = अणु"spi_di", "spi_do",
						"spi_clk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_cgu_grps[] = अणु"clkout0", "clkout1",
						"clkout2", "clkout3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_ebu_grps[] = अणु"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu clk",
						"nand ale", "nand cs1",
						"nand cle", "nand rdy",
						"nand rd"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_exin_grps[] = अणु"exin0", "exin1", "exin2",
						"exin3", "exin4", "exin5"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_gpt_grps[] = अणु"gpt1", "gpt2", "gpt3"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_usअगर_grps[] = अणु"usif uart_rx", "usif uart_tx",
						"usif uart_rts", "usif uart_cts",
						"usif uart_dtr", "usif uart_dsr",
						"usif uart_dcd", "usif uart_ri",
						"usif spi_di", "usif spi_do",
						"usif spi_clk", "usif spi_cs0",
						"usif spi_cs1", "usif spi_cs2"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_nmi_grps[] = अणु"nmi"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_dfe_grps[] = अणु"dfe led0", "dfe led1"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx200_gphy_grps[] = अणु"gphy0 led0", "gphy0 led1",
						"gphy0 led2", "gphy1 led0",
						"gphy1 led1", "gphy1 led2"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func xrx200_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(xrx200_spi_grps)पूर्ण,
	अणु"usif",	ARRAY_AND_SIZE(xrx200_usअगर_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(xrx200_cgu_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(xrx200_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(xrx200_stp_grps)पूर्ण,
	अणु"gpt",		ARRAY_AND_SIZE(xrx200_gpt_grps)पूर्ण,
	अणु"nmi",		ARRAY_AND_SIZE(xrx200_nmi_grps)पूर्ण,
	अणु"pci",		ARRAY_AND_SIZE(xrx200_pci_grps)पूर्ण,
	अणु"ebu",		ARRAY_AND_SIZE(xrx200_ebu_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(xrx200_mdio_grps)पूर्ण,
	अणु"dfe",		ARRAY_AND_SIZE(xrx200_dfe_grps)पूर्ण,
	अणु"gphy",	ARRAY_AND_SIZE(xrx200_gphy_grps)पूर्ण,
पूर्ण;

/* ---------  xrx300 related code --------- */
#घोषणा XRX300_MAX_PIN		64

अटल स्थिर काष्ठा ltq_mfp_pin xrx300_mfp[] = अणु
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	EPHY,	NONE),
	MFP_XWAY(GPIO1, GPIO,	NONE,	EXIN,	NONE),
	MFP_XWAY(GPIO2, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO3, GPIO,	CGU,	NONE,	NONE),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	NONE),
	MFP_XWAY(GPIO5, GPIO,	STP,	EPHY,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	NONE,	NONE),
	MFP_XWAY(GPIO7, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO8, GPIO,	CGU,	GPHY,	EPHY),
	MFP_XWAY(GPIO9, GPIO,	WIFI,	NONE,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	USIF,	WIFI,	SPI),
	MFP_XWAY(GPIO12, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO13, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	USIF,	EPHY),
	MFP_XWAY(GPIO15, GPIO,	SPI,	NONE,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	EXIN,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	NONE,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	NONE,	NONE),
	MFP_XWAY(GPIO19, GPIO,	USIF,	NONE,	EPHY),
	MFP_XWAY(GPIO20, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO21, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO22, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO23, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO24, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO25, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO26, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO27, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO28, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO29, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO30, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO31, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO32, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO33, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO34, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO37, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO38, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO39, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO40, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO41, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO45, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO46, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO47, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO50, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO51, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO52, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO53, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO54, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO55, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO56, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO57, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO58, GPIO,	EBU,	TDM,	NONE),
	MFP_XWAY(GPIO59, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO60, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO61, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO62, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO63, NONE,	NONE,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित xrx300_exin_pin_map[] = अणुGPIO0, GPIO1, GPIO16, GPIO10, GPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_exin0[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_exin1[] = अणुGPIO1पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_exin2[] = अणुGPIO16पूर्ण;
/* EXIN3 is not available on xrX300 */
अटल स्थिर अचिन्हित xrx300_pins_exin4[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_exin5[] = अणुGPIO9पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_usअगर_uart_rx[] = अणुGPIO11पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_usअगर_uart_tx[] = अणुGPIO10पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_usअगर_spi_di[] = अणुGPIO11पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_usअगर_spi_करो[] = अणुGPIO10पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_usअगर_spi_clk[] = अणुGPIO19पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_usअगर_spi_cs0[] = अणुGPIO14पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_stp[] = अणुGPIO4, GPIO5, GPIO6पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_mdio[] = अणुGPIO42, GPIO43पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_dfe_led0[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_dfe_led1[] = अणुGPIO5पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_ephy0_led0[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_ephy0_led1[] = अणुGPIO8पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_ephy1_led0[] = अणुGPIO14पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_ephy1_led1[] = अणुGPIO19पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_nand_ale[] = अणुGPIO13पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_cs1[] = अणुGPIO23पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_cle[] = अणुGPIO24पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_rdy[] = अणुGPIO48पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_rd[] = अणुGPIO49पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d1[] = अणुGPIO50पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d0[] = अणुGPIO51पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d2[] = अणुGPIO52पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d7[] = अणुGPIO53पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d6[] = अणुGPIO54पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d5[] = अणुGPIO55पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d4[] = अणुGPIO56पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_d3[] = अणुGPIO57पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_cs0[] = अणुGPIO58पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_wr[] = अणुGPIO59पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_wp[] = अणुGPIO60पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_nand_se[] = अणुGPIO61पूर्ण;

अटल स्थिर अचिन्हित xrx300_pins_spi_di[] = अणुGPIO16पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_spi_करो[] = अणुGPIO17पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_spi_clk[] = अणुGPIO18पूर्ण;
अटल स्थिर अचिन्हित xrx300_pins_spi_cs1[] = अणुGPIO15पूर्ण;
/* SPI_CS2 is not available on xrX300 */
/* SPI_CS3 is not available on xrX300 */
अटल स्थिर अचिन्हित xrx300_pins_spi_cs4[] = अणुGPIO10पूर्ण;
/* SPI_CS5 is not available on xrX300 */
अटल स्थिर अचिन्हित xrx300_pins_spi_cs6[] = अणुGPIO11पूर्ण;

/* CLKOUT0 is not available on xrX300 */
/* CLKOUT1 is not available on xrX300 */
अटल स्थिर अचिन्हित xrx300_pins_clkout2[] = अणुGPIO3पूर्ण;

अटल स्थिर काष्ठा ltq_pin_group xrx300_grps[] = अणु
	GRP_MUX("exin0", EXIN, xrx300_pins_exin0),
	GRP_MUX("exin1", EXIN, xrx300_pins_exin1),
	GRP_MUX("exin2", EXIN, xrx300_pins_exin2),
	GRP_MUX("exin4", EXIN, xrx300_pins_exin4),
	GRP_MUX("exin5", EXIN, xrx300_pins_exin5),
	GRP_MUX("nand ale", EBU, xrx300_pins_nand_ale),
	GRP_MUX("nand cs1", EBU, xrx300_pins_nand_cs1),
	GRP_MUX("nand cle", EBU, xrx300_pins_nand_cle),
	GRP_MUX("nand rdy", EBU, xrx300_pins_nand_rdy),
	GRP_MUX("nand rd", EBU, xrx300_pins_nand_rd),
	GRP_MUX("nand d1", EBU, xrx300_pins_nand_d1),
	GRP_MUX("nand d0", EBU, xrx300_pins_nand_d0),
	GRP_MUX("nand d2", EBU, xrx300_pins_nand_d2),
	GRP_MUX("nand d7", EBU, xrx300_pins_nand_d7),
	GRP_MUX("nand d6", EBU, xrx300_pins_nand_d6),
	GRP_MUX("nand d5", EBU, xrx300_pins_nand_d5),
	GRP_MUX("nand d4", EBU, xrx300_pins_nand_d4),
	GRP_MUX("nand d3", EBU, xrx300_pins_nand_d3),
	GRP_MUX("nand cs0", EBU, xrx300_pins_nand_cs0),
	GRP_MUX("nand wr", EBU, xrx300_pins_nand_wr),
	GRP_MUX("nand wp", EBU, xrx300_pins_nand_wp),
	GRP_MUX("nand se", EBU, xrx300_pins_nand_se),
	GRP_MUX("spi_di", SPI, xrx300_pins_spi_di),
	GRP_MUX("spi_do", SPI, xrx300_pins_spi_करो),
	GRP_MUX("spi_clk", SPI, xrx300_pins_spi_clk),
	GRP_MUX("spi_cs1", SPI, xrx300_pins_spi_cs1),
	GRP_MUX("spi_cs4", SPI, xrx300_pins_spi_cs4),
	GRP_MUX("spi_cs6", SPI, xrx300_pins_spi_cs6),
	GRP_MUX("usif uart_rx", USIF, xrx300_pins_usअगर_uart_rx),
	GRP_MUX("usif uart_tx", USIF, xrx300_pins_usअगर_uart_tx),
	GRP_MUX("usif spi_di", USIF, xrx300_pins_usअगर_spi_di),
	GRP_MUX("usif spi_do", USIF, xrx300_pins_usअगर_spi_करो),
	GRP_MUX("usif spi_clk", USIF, xrx300_pins_usअगर_spi_clk),
	GRP_MUX("usif spi_cs0", USIF, xrx300_pins_usअगर_spi_cs0),
	GRP_MUX("stp", STP, xrx300_pins_stp),
	GRP_MUX("clkout2", CGU, xrx300_pins_clkout2),
	GRP_MUX("mdio", MDIO, xrx300_pins_mdio),
	GRP_MUX("dfe led0", DFE, xrx300_pins_dfe_led0),
	GRP_MUX("dfe led1", DFE, xrx300_pins_dfe_led1),
	GRP_MUX("ephy0 led0", GPHY, xrx300_pins_ephy0_led0),
	GRP_MUX("ephy0 led1", GPHY, xrx300_pins_ephy0_led1),
	GRP_MUX("ephy1 led0", GPHY, xrx300_pins_ephy1_led0),
	GRP_MUX("ephy1 led1", GPHY, xrx300_pins_ephy1_led1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर xrx300_spi_grps[] = अणु"spi_di", "spi_do",
						"spi_clk", "spi_cs1",
						"spi_cs4", "spi_cs6"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_cgu_grps[] = अणु"clkout2"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_ebu_grps[] = अणु"nand ale", "nand cs1",
						"nand cle", "nand rdy",
						"nand rd", "nand d1",
						"nand d0", "nand d2",
						"nand d7", "nand d6",
						"nand d5", "nand d4",
						"nand d3", "nand cs0",
						"nand wr", "nand wp",
						"nand se"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_exin_grps[] = अणु"exin0", "exin1", "exin2",
						"exin4", "exin5"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_usअगर_grps[] = अणु"usif uart_rx", "usif uart_tx",
						"usif spi_di", "usif spi_do",
						"usif spi_clk", "usif spi_cs0"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_stp_grps[] = अणु"stp"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_dfe_grps[] = अणु"dfe led0", "dfe led1"पूर्ण;
अटल स्थिर अक्षर * स्थिर xrx300_gphy_grps[] = अणु"ephy0 led0", "ephy0 led1",
						"ephy1 led0", "ephy1 led1"पूर्ण;

अटल स्थिर काष्ठा ltq_pmx_func xrx300_funcs[] = अणु
	अणु"spi",		ARRAY_AND_SIZE(xrx300_spi_grps)पूर्ण,
	अणु"usif",	ARRAY_AND_SIZE(xrx300_usअगर_grps)पूर्ण,
	अणु"cgu",		ARRAY_AND_SIZE(xrx300_cgu_grps)पूर्ण,
	अणु"exin",	ARRAY_AND_SIZE(xrx300_exin_grps)पूर्ण,
	अणु"stp",		ARRAY_AND_SIZE(xrx300_stp_grps)पूर्ण,
	अणु"ebu",		ARRAY_AND_SIZE(xrx300_ebu_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(xrx300_mdio_grps)पूर्ण,
	अणु"dfe",		ARRAY_AND_SIZE(xrx300_dfe_grps)पूर्ण,
	अणु"ephy",	ARRAY_AND_SIZE(xrx300_gphy_grps)पूर्ण,
पूर्ण;

/* ---------  pinconf related code --------- */
अटल पूर्णांक xway_pinconf_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित pin,
				अचिन्हित दीर्घ *config)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत ltq_pinconf_param param = LTQ_PINCONF_UNPACK_PARAM(*config);
	पूर्णांक port = PORT(pin);
	u32 reg;

	चयन (param) अणु
	हाल LTQ_PINCONF_PARAM_OPEN_DRAIN:
		अगर (port == PORT3)
			reg = GPIO3_OD;
		अन्यथा
			reg = GPIO_OD(pin);
		*config = LTQ_PINCONF_PACK(param,
			!gpio_getbit(info->membase[0], reg, PORT_PIN(pin)));
		अवरोध;

	हाल LTQ_PINCONF_PARAM_PULL:
		अगर (port == PORT3)
			reg = GPIO3_PUDEN;
		अन्यथा
			reg = GPIO_PUDEN(pin);
		अगर (!gpio_getbit(info->membase[0], reg, PORT_PIN(pin))) अणु
			*config = LTQ_PINCONF_PACK(param, 0);
			अवरोध;
		पूर्ण

		अगर (port == PORT3)
			reg = GPIO3_PUDSEL;
		अन्यथा
			reg = GPIO_PUDSEL(pin);
		अगर (!gpio_getbit(info->membase[0], reg, PORT_PIN(pin)))
			*config = LTQ_PINCONF_PACK(param, 2);
		अन्यथा
			*config = LTQ_PINCONF_PACK(param, 1);
		अवरोध;

	हाल LTQ_PINCONF_PARAM_OUTPUT:
		reg = GPIO_सूची(pin);
		*config = LTQ_PINCONF_PACK(param,
			gpio_getbit(info->membase[0], reg, PORT_PIN(pin)));
		अवरोध;
	शेष:
		dev_err(pctldev->dev, "Invalid config param %04x\n", param);
		वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xway_pinconf_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित pin,
				अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत ltq_pinconf_param param;
	पूर्णांक arg;
	पूर्णांक port = PORT(pin);
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = LTQ_PINCONF_UNPACK_PARAM(configs[i]);
		arg = LTQ_PINCONF_UNPACK_ARG(configs[i]);

		चयन (param) अणु
		हाल LTQ_PINCONF_PARAM_OPEN_DRAIN:
			अगर (port == PORT3)
				reg = GPIO3_OD;
			अन्यथा
				reg = GPIO_OD(pin);
			अगर (arg == 0)
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अन्यथा
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अवरोध;

		हाल LTQ_PINCONF_PARAM_PULL:
			अगर (port == PORT3)
				reg = GPIO3_PUDEN;
			अन्यथा
				reg = GPIO_PUDEN(pin);
			अगर (arg == 0) अणु
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
				अवरोध;
			पूर्ण
			gpio_setbit(info->membase[0], reg, PORT_PIN(pin));

			अगर (port == PORT3)
				reg = GPIO3_PUDSEL;
			अन्यथा
				reg = GPIO_PUDSEL(pin);
			अगर (arg == 1)
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अन्यथा अगर (arg == 2)
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अन्यथा
				dev_err(pctldev->dev,
					"Invalid pull value %d\n", arg);
			अवरोध;

		हाल LTQ_PINCONF_PARAM_OUTPUT:
			reg = GPIO_सूची(pin);
			अगर (arg == 0)
				gpio_clearbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अन्यथा
				gpio_setbit(info->membase[0],
					reg,
					PORT_PIN(pin));
			अवरोध;

		शेष:
			dev_err(pctldev->dev,
				"Invalid config param %04x\n", param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

पूर्णांक xway_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित selector,
			अचिन्हित दीर्घ *configs,
			अचिन्हित num_configs)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < info->grps[selector].npins && !ret; i++)
		ret = xway_pinconf_set(pctldev,
				info->grps[selector].pins[i],
				configs,
				num_configs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops xway_pinconf_ops = अणु
	.pin_config_get	= xway_pinconf_get,
	.pin_config_set	= xway_pinconf_set,
	.pin_config_group_set = xway_pinconf_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc xway_pctrl_desc = अणु
	.owner		= THIS_MODULE,
	.confops	= &xway_pinconf_ops,
पूर्ण;

अटल अंतरभूत पूर्णांक xway_mux_apply(काष्ठा pinctrl_dev *pctrldev,
				पूर्णांक pin, पूर्णांक mux)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	पूर्णांक port = PORT(pin);
	u32 alt1_reg = GPIO_ALT1(pin);

	अगर (port == PORT3)
		alt1_reg = GPIO3_ALT1;

	अगर (mux & MUX_ALT0)
		gpio_setbit(info->membase[0], GPIO_ALT0(pin), PORT_PIN(pin));
	अन्यथा
		gpio_clearbit(info->membase[0], GPIO_ALT0(pin), PORT_PIN(pin));

	अगर (mux & MUX_ALT1)
		gpio_setbit(info->membase[0], alt1_reg, PORT_PIN(pin));
	अन्यथा
		gpio_clearbit(info->membase[0], alt1_reg, PORT_PIN(pin));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ltq_cfg_param xway_cfg_params[] = अणु
	अणु"lantiq,pull",		LTQ_PINCONF_PARAM_PULLपूर्ण,
	अणु"lantiq,open-drain",	LTQ_PINCONF_PARAM_OPEN_DRAINपूर्ण,
	अणु"lantiq,output",	LTQ_PINCONF_PARAM_OUTPUTपूर्ण,
पूर्ण;

अटल काष्ठा ltq_pinmux_info xway_info = अणु
	.desc		= &xway_pctrl_desc,
	.apply_mux	= xway_mux_apply,
	.params		= xway_cfg_params,
	.num_params	= ARRAY_SIZE(xway_cfg_params),
पूर्ण;

/* ---------  gpio_chip related code --------- */
अटल व्योम xway_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin, पूर्णांक val)
अणु
	काष्ठा ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	अगर (val)
		gpio_setbit(info->membase[0], GPIO_OUT(pin), PORT_PIN(pin));
	अन्यथा
		gpio_clearbit(info->membase[0], GPIO_OUT(pin), PORT_PIN(pin));
पूर्ण

अटल पूर्णांक xway_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	वापस !!gpio_getbit(info->membase[0], GPIO_IN(pin), PORT_PIN(pin));
पूर्ण

अटल पूर्णांक xway_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	gpio_clearbit(info->membase[0], GPIO_सूची(pin), PORT_PIN(pin));

	वापस 0;
पूर्ण

अटल पूर्णांक xway_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin, पूर्णांक val)
अणु
	काष्ठा ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	अगर (PORT(pin) == PORT3)
		gpio_setbit(info->membase[0], GPIO3_OD, PORT_PIN(pin));
	अन्यथा
		gpio_setbit(info->membase[0], GPIO_OD(pin), PORT_PIN(pin));
	gpio_setbit(info->membase[0], GPIO_सूची(pin), PORT_PIN(pin));
	xway_gpio_set(chip, pin, val);

	वापस 0;
पूर्ण

/*
 * gpiolib gpiod_to_irq callback function.
 * Returns the mapped IRQ (बाह्यal पूर्णांकerrupt) number क्रम a given GPIO pin.
 */
अटल पूर्णांक xway_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ltq_pinmux_info *info = dev_get_drvdata(chip->parent);
	पूर्णांक i;

	क्रम (i = 0; i < info->num_exin; i++)
		अगर (info->exin[i] == offset)
			वापस ltq_eiu_get_irq(i);

	वापस -1;
पूर्ण

अटल काष्ठा gpio_chip xway_chip = अणु
	.label = "gpio-xway",
	.direction_input = xway_gpio_dir_in,
	.direction_output = xway_gpio_dir_out,
	.get = xway_gpio_get,
	.set = xway_gpio_set,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.to_irq = xway_gpio_to_irq,
	.base = -1,
पूर्ण;


/* --------- रेजिस्टर the pinctrl layer --------- */
काष्ठा pinctrl_xway_soc अणु
	पूर्णांक pin_count;
	स्थिर काष्ठा ltq_mfp_pin *mfp;
	स्थिर काष्ठा ltq_pin_group *grps;
	अचिन्हित पूर्णांक num_grps;
	स्थिर काष्ठा ltq_pmx_func *funcs;
	अचिन्हित पूर्णांक num_funcs;
	स्थिर अचिन्हित *exin;
	अचिन्हित पूर्णांक num_exin;
पूर्ण;

/* xway xr9 series (DEPRECATED: Use XWAY xRX100/xRX200 Family) */
अटल काष्ठा pinctrl_xway_soc xr9_pinctrl = अणु
	.pin_count = XR9_MAX_PIN,
	.mfp = xway_mfp,
	.grps = xway_grps,
	.num_grps = ARRAY_SIZE(xway_grps),
	.funcs = xrx_funcs,
	.num_funcs = ARRAY_SIZE(xrx_funcs),
	.exin = xway_exin_pin_map,
	.num_exin = 6
पूर्ण;

/* XWAY AMAZON Family */
अटल काष्ठा pinctrl_xway_soc ase_pinctrl = अणु
	.pin_count = ASE_MAX_PIN,
	.mfp = ase_mfp,
	.grps = ase_grps,
	.num_grps = ARRAY_SIZE(ase_grps),
	.funcs = ase_funcs,
	.num_funcs = ARRAY_SIZE(ase_funcs),
	.exin = ase_exin_pin_map,
	.num_exin = 3
पूर्ण;

/* XWAY DANUBE Family */
अटल काष्ठा pinctrl_xway_soc danube_pinctrl = अणु
	.pin_count = DANUBE_MAX_PIN,
	.mfp = danube_mfp,
	.grps = danube_grps,
	.num_grps = ARRAY_SIZE(danube_grps),
	.funcs = danube_funcs,
	.num_funcs = ARRAY_SIZE(danube_funcs),
	.exin = danube_exin_pin_map,
	.num_exin = 3
पूर्ण;

/* XWAY xRX100 Family */
अटल काष्ठा pinctrl_xway_soc xrx100_pinctrl = अणु
	.pin_count = XRX100_MAX_PIN,
	.mfp = xrx100_mfp,
	.grps = xrx100_grps,
	.num_grps = ARRAY_SIZE(xrx100_grps),
	.funcs = xrx100_funcs,
	.num_funcs = ARRAY_SIZE(xrx100_funcs),
	.exin = xrx100_exin_pin_map,
	.num_exin = 6
पूर्ण;

/* XWAY xRX200 Family */
अटल काष्ठा pinctrl_xway_soc xrx200_pinctrl = अणु
	.pin_count = XRX200_MAX_PIN,
	.mfp = xrx200_mfp,
	.grps = xrx200_grps,
	.num_grps = ARRAY_SIZE(xrx200_grps),
	.funcs = xrx200_funcs,
	.num_funcs = ARRAY_SIZE(xrx200_funcs),
	.exin = xrx200_exin_pin_map,
	.num_exin = 6
पूर्ण;

/* XWAY xRX300 Family */
अटल काष्ठा pinctrl_xway_soc xrx300_pinctrl = अणु
	.pin_count = XRX300_MAX_PIN,
	.mfp = xrx300_mfp,
	.grps = xrx300_grps,
	.num_grps = ARRAY_SIZE(xrx300_grps),
	.funcs = xrx300_funcs,
	.num_funcs = ARRAY_SIZE(xrx300_funcs),
	.exin = xrx300_exin_pin_map,
	.num_exin = 5
पूर्ण;

अटल काष्ठा pinctrl_gpio_range xway_gpio_range = अणु
	.name	= "XWAY GPIO",
	.gc	= &xway_chip,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xway_match[] = अणु
	अणु .compatible = "lantiq,pinctrl-xway", .data = &danube_pinctrlपूर्ण, /*DEPRECATED*/
	अणु .compatible = "lantiq,pinctrl-xr9", .data = &xr9_pinctrlपूर्ण, /*DEPRECATED*/
	अणु .compatible = "lantiq,pinctrl-ase", .data = &ase_pinctrlपूर्ण, /*DEPRECATED*/
	अणु .compatible = "lantiq,ase-pinctrl", .data = &ase_pinctrlपूर्ण,
	अणु .compatible = "lantiq,danube-pinctrl", .data = &danube_pinctrlपूर्ण,
	अणु .compatible = "lantiq,xrx100-pinctrl", .data = &xrx100_pinctrlपूर्ण,
	अणु .compatible = "lantiq,xrx200-pinctrl", .data = &xrx200_pinctrlपूर्ण,
	अणु .compatible = "lantiq,xrx300-pinctrl", .data = &xrx300_pinctrlपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xway_match);

अटल पूर्णांक pinmux_xway_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा pinctrl_xway_soc *xway_soc;
	पूर्णांक ret, i;

	/* get and remap our रेजिस्टर range */
	xway_info.membase[0] = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xway_info.membase[0]))
		वापस PTR_ERR(xway_info.membase[0]);

	match = of_match_device(xway_match, &pdev->dev);
	अगर (match)
		xway_soc = (स्थिर काष्ठा pinctrl_xway_soc *) match->data;
	अन्यथा
		xway_soc = &danube_pinctrl;

	/* find out how many pads we have */
	xway_chip.ngpio = xway_soc->pin_count;

	/* load our pad descriptors */
	xway_info.pads = devm_kसुस्मृति(&pdev->dev,
			xway_chip.ngpio, माप(काष्ठा pinctrl_pin_desc),
			GFP_KERNEL);
	अगर (!xway_info.pads)
		वापस -ENOMEM;

	क्रम (i = 0; i < xway_chip.ngpio; i++) अणु
		अक्षर *name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "io%d", i);

		अगर (!name)
			वापस -ENOMEM;

		xway_info.pads[i].number = GPIO0 + i;
		xway_info.pads[i].name = name;
	पूर्ण
	xway_pctrl_desc.pins = xway_info.pads;

	/* setup the data needed by pinctrl */
	xway_pctrl_desc.name	= dev_name(&pdev->dev);
	xway_pctrl_desc.npins	= xway_chip.ngpio;

	xway_info.num_pads	= xway_chip.ngpio;
	xway_info.num_mfp	= xway_chip.ngpio;
	xway_info.mfp		= xway_soc->mfp;
	xway_info.grps		= xway_soc->grps;
	xway_info.num_grps	= xway_soc->num_grps;
	xway_info.funcs		= xway_soc->funcs;
	xway_info.num_funcs	= xway_soc->num_funcs;
	xway_info.exin		= xway_soc->exin;
	xway_info.num_exin	= xway_soc->num_exin;

	/* रेजिस्टर with the generic lantiq layer */
	ret = ltq_pinctrl_रेजिस्टर(pdev, &xway_info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl driver\n");
		वापस ret;
	पूर्ण

	/* रेजिस्टर the gpio chip */
	xway_chip.parent = &pdev->dev;
	xway_chip.owner = THIS_MODULE;
	xway_chip.of_node = pdev->dev.of_node;
	ret = devm_gpiochip_add_data(&pdev->dev, &xway_chip, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register gpio chip\n");
		वापस ret;
	पूर्ण

	/*
	 * For DeviceTree-supported प्रणालीs, the gpio core checks the
	 * pinctrl's device node क्रम the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * क्रम the driver. In this हाल the driver can skip ahead.
	 *
	 * In order to reमुख्य compatible with older, existing DeviceTree
	 * files which करोn't set the "gpio-ranges" property or प्रणालीs that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "gpio-ranges")) अणु
		/* finish with रेजिस्टरing the gpio range in pinctrl */
		xway_gpio_range.npins = xway_chip.ngpio;
		xway_gpio_range.base = xway_chip.base;
		pinctrl_add_gpio_range(xway_info.pctrl, &xway_gpio_range);
	पूर्ण

	dev_info(&pdev->dev, "Init done\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pinmux_xway_driver = अणु
	.probe	= pinmux_xway_probe,
	.driver = अणु
		.name	= "pinctrl-xway",
		.of_match_table = xway_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pinmux_xway_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pinmux_xway_driver);
पूर्ण

core_initcall_sync(pinmux_xway_init);
