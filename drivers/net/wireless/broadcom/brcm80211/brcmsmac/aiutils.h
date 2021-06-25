<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
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
 */

#अगर_अघोषित	_BRCM_AIUTILS_H_
#घोषणा	_BRCM_AIUTILS_H_

#समावेश <linux/bcma/bcma.h>

#समावेश "types.h"

/*
 * SOC Interconnect Address Map.
 * All regions may not exist on all chips.
 */
/* each core माला_लो 4Kbytes क्रम रेजिस्टरs */
#घोषणा SI_CORE_SIZE		0x1000
/*
 * Max cores (this is arbitrary, क्रम software
 * convenience and could be changed अगर we
 * make any larger chips
 */
#घोषणा	SI_MAXCORES		16

/* Client Mode sb2pcitranslation2 size in bytes */
#घोषणा SI_PCI_DMA_SZ		0x40000000

/* PCIE Client Mode sb2pcitranslation2 (2 ZettaBytes), high 32 bits */
#घोषणा SI_PCIE_DMA_H32		0x80000000

/* chipcommon being the first core: */
#घोषणा	SI_CC_IDX		0

/* SOC Interconnect types (aka chip types) */
#घोषणा	SOCI_AI			1

/* A रेजिस्टर that is common to all cores to
 * communicate w/PMU regarding घड़ी control.
 */
#घोषणा SI_CLK_CTL_ST		0x1e0	/* घड़ी control and status */

/* clk_ctl_st रेजिस्टर */
#घोषणा	CCS_FORCEALP		0x00000001	/* क्रमce ALP request */
#घोषणा	CCS_FORCEHT		0x00000002	/* क्रमce HT request */
#घोषणा	CCS_FORCEILP		0x00000004	/* क्रमce ILP request */
#घोषणा	CCS_ALPAREQ		0x00000008	/* ALP Avail Request */
#घोषणा	CCS_HTAREQ		0x00000010	/* HT Avail Request */
#घोषणा	CCS_FORCEHWREQOFF	0x00000020	/* Force HW Clock Request Off */
#घोषणा CCS_ERSRC_REQ_MASK	0x00000700	/* बाह्यal resource requests */
#घोषणा CCS_ERSRC_REQ_SHIFT	8
#घोषणा	CCS_ALPAVAIL		0x00010000	/* ALP is available */
#घोषणा	CCS_HTAVAIL		0x00020000	/* HT is available */
#घोषणा CCS_BP_ON_APL		0x00040000	/* RO: running on ALP घड़ी */
#घोषणा CCS_BP_ON_HT		0x00080000	/* RO: running on HT घड़ी */
#घोषणा CCS_ERSRC_STS_MASK	0x07000000	/* बाह्यal resource status */
#घोषणा CCS_ERSRC_STS_SHIFT	24

/* HT avail in chipc and pcmcia on 4328a0 */
#घोषणा	CCS0_HTAVAIL		0x00010000
/* ALP avail in chipc and pcmcia on 4328a0 */
#घोषणा	CCS0_ALPAVAIL		0x00020000

/* Not really related to SOC Interconnect, but a couple of software
 * conventions क्रम the use the flash space:
 */

/* Minumum amount of flash we support */
#घोषणा FLASH_MIN		0x00020000	/* Minimum flash size */

#घोषणा	CC_SROM_OTP		0x800	/* SROM/OTP address space */

/* gpioसमयrval */
#घोषणा GPIO_ONTIME_SHIFT	16

/* Fields in clkभाग */
#घोषणा	CLKD_OTP		0x000f0000
#घोषणा	CLKD_OTP_SHIFT		16

/* dynamic घड़ी control defines */
#घोषणा	LPOMINFREQ		25000	/* low घातer oscillator min */
#घोषणा	LPOMAXFREQ		43000	/* low घातer oscillator max */
#घोषणा	XTALMINFREQ		19800000	/* 20 MHz - 1% */
#घोषणा	XTALMAXFREQ		20200000	/* 20 MHz + 1% */
#घोषणा	PCIMINFREQ		25000000	/* 25 MHz */
#घोषणा	PCIMAXFREQ		34000000	/* 33 MHz + fudge */

#घोषणा	ILP_DIV_5MHZ		0	/* ILP = 5 MHz */
#घोषणा	ILP_DIV_1MHZ		4	/* ILP = 1 MHz */

/* clkctl xtal what flags */
#घोषणा	XTAL			0x1	/* primary crystal oscillator (2050) */
#घोषणा	PLL			0x2	/* मुख्य chip pll */

/* GPIO usage priorities */
#घोषणा GPIO_DRV_PRIORITY	0	/* Driver */
#घोषणा GPIO_APP_PRIORITY	1	/* Application */
#घोषणा GPIO_HI_PRIORITY	2	/* Highest priority. Ignore GPIO
					 * reservation
					 */

/* GPIO pull up/करोwn */
#घोषणा GPIO_PULLUP		0
#घोषणा GPIO_PULLDN		1

/* GPIO event regtype */
#घोषणा GPIO_REGEVT		0	/* GPIO रेजिस्टर event */
#घोषणा GPIO_REGEVT_INTMSK	1	/* GPIO रेजिस्टर event पूर्णांक mask */
#घोषणा GPIO_REGEVT_INTPOL	2	/* GPIO रेजिस्टर event पूर्णांक polarity */

/* device path */
#घोषणा SI_DEVPATH_BUFSZ	16	/* min buffer size in bytes */

/* SI routine क्रमागतeration: to be used by update function with multiple hooks */
#घोषणा	SI_DOATTACH	1
#घोषणा SI_PCIDOWN	2
#घोषणा SI_PCIUP	3

/*
 * Data काष्ठाure to export all chip specअगरic common variables
 *   खुला (पढ़ो-only) portion of aiutils handle वापसed by si_attach()
 */
काष्ठा si_pub अणु
	पूर्णांक ccrev;		/* chip common core rev */
	u32 cccaps;		/* chip common capabilities */
	पूर्णांक pmurev;		/* pmu core rev */
	u32 pmucaps;		/* pmu capabilities */
	uपूर्णांक boardtype;		/* board type */
	uपूर्णांक boardvenकरोr;	/* board venकरोr */
	uपूर्णांक chip;		/* chip number */
	uपूर्णांक chiprev;		/* chip revision */
	uपूर्णांक chippkg;		/* chip package option */
पूर्ण;

काष्ठा pci_dev;

काष्ठा gpioh_item अणु
	व्योम *arg;
	bool level;
	व्योम (*handler) (u32 stat, व्योम *arg);
	u32 event;
	काष्ठा gpioh_item *next;
पूर्ण;

/* misc si info needed by some of the routines */
काष्ठा si_info अणु
	काष्ठा si_pub pub;	/* back plane खुला state (must be first) */
	काष्ठा bcma_bus *icbus;	/* handle to soc पूर्णांकerconnect bus */
	काष्ठा pci_dev *pcibus;	/* handle to pci bus */

	u32 chipst;		/* chip status */
पूर्ण;

/*
 * Many of the routines below take an 'sih' handle as their first arg.
 * Allocate this by calling si_attach().  Free it by calling si_detach().
 * At any one समय, the sih is logically focused on one particular si core
 * (the "current core").
 * Use si_setcore() or si_setcoreidx() to change the association to another core
 */


/* AMBA Interconnect exported बाह्यs */
u32 ai_core_cflags(काष्ठा bcma_device *core, u32 mask, u32 val);

/* === exported functions === */
काष्ठा si_pub *ai_attach(काष्ठा bcma_bus *pbus);
व्योम ai_detach(काष्ठा si_pub *sih);
uपूर्णांक ai_cc_reg(काष्ठा si_pub *sih, uपूर्णांक regoff, u32 mask, u32 val);
व्योम ai_clkctl_init(काष्ठा si_pub *sih);
u16 ai_clkctl_fast_pwrup_delay(काष्ठा si_pub *sih);
bool ai_clkctl_cc(काष्ठा si_pub *sih, क्रमागत bcma_clkmode mode);
bool ai_deviceहटाओd(काष्ठा si_pub *sih);

/* Enable Ex-PA क्रम 4313 */
व्योम ai_epa_4313war(काष्ठा si_pub *sih);

अटल अंतरभूत u32 ai_get_cccaps(काष्ठा si_pub *sih)
अणु
	वापस sih->cccaps;
पूर्ण

अटल अंतरभूत पूर्णांक ai_get_pmurev(काष्ठा si_pub *sih)
अणु
	वापस sih->pmurev;
पूर्ण

अटल अंतरभूत u32 ai_get_pmucaps(काष्ठा si_pub *sih)
अणु
	वापस sih->pmucaps;
पूर्ण

अटल अंतरभूत uपूर्णांक ai_get_boardtype(काष्ठा si_pub *sih)
अणु
	वापस sih->boardtype;
पूर्ण

अटल अंतरभूत uपूर्णांक ai_get_boardvenकरोr(काष्ठा si_pub *sih)
अणु
	वापस sih->boardvenकरोr;
पूर्ण

अटल अंतरभूत uपूर्णांक ai_get_chip_id(काष्ठा si_pub *sih)
अणु
	वापस sih->chip;
पूर्ण

अटल अंतरभूत uपूर्णांक ai_get_chiprev(काष्ठा si_pub *sih)
अणु
	वापस sih->chiprev;
पूर्ण

अटल अंतरभूत uपूर्णांक ai_get_chippkg(काष्ठा si_pub *sih)
अणु
	वापस sih->chippkg;
पूर्ण

#पूर्ण_अगर				/* _BRCM_AIUTILS_H_ */
