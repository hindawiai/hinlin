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

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश <brcm_hw_ids.h>
#समावेश <chipcommon.h>
#समावेश <brcmu_utils.h>
#समावेश "pub.h"
#समावेश "aiutils.h"
#समावेश "pmu.h"
#समावेश "soc.h"

/*
 * बाह्यal LPO crystal frequency
 */
#घोषणा EXT_ILP_HZ 32768

/*
 * Duration क्रम ILP घड़ी frequency measurment in milliseconds
 *
 * remark: 1000 must be an पूर्णांकeger multiple of this duration
 */
#घोषणा ILP_CALC_DUR	10

/* Fields in pmucontrol */
#घोषणा	PCTL_ILP_DIV_MASK	0xffff0000
#घोषणा	PCTL_ILP_DIV_SHIFT	16
#घोषणा PCTL_PLL_PLLCTL_UPD	0x00000400	/* rev 2 */
#घोषणा PCTL_NOILP_ON_WAIT	0x00000200	/* rev 1 */
#घोषणा	PCTL_HT_REQ_EN		0x00000100
#घोषणा	PCTL_ALP_REQ_EN		0x00000080
#घोषणा	PCTL_XTALFREQ_MASK	0x0000007c
#घोषणा	PCTL_XTALFREQ_SHIFT	2
#घोषणा	PCTL_ILP_DIV_EN		0x00000002
#घोषणा	PCTL_LPO_SEL		0x00000001

/* ILP घड़ी */
#घोषणा	ILP_CLOCK		32000

/* ALP घड़ी on pre-PMU chips */
#घोषणा	ALP_CLOCK		20000000

/* pmustatus */
#घोषणा PST_EXTLPOAVAIL	0x0100
#घोषणा PST_WDRESET	0x0080
#घोषणा	PST_INTPEND	0x0040
#घोषणा	PST_SBCLKST	0x0030
#घोषणा	PST_SBCLKST_ILP	0x0010
#घोषणा	PST_SBCLKST_ALP	0x0020
#घोषणा	PST_SBCLKST_HT	0x0030
#घोषणा	PST_ALPAVAIL	0x0008
#घोषणा	PST_HTAVAIL	0x0004
#घोषणा	PST_RESINIT	0x0003

/* PMU resource bit position */
#घोषणा PMURES_BIT(bit)	(1 << (bit))

/* PMU corerev and chip specअगरic PLL controls.
 * PMU<rev>_PLL<num>_XX where <rev> is PMU corerev and <num> is an arbitrary
 * number to dअगरferentiate dअगरferent PLLs controlled by the same PMU rev.
 */

/* pmu XtalFreqRatio */
#घोषणा	PMU_XTALFREQ_REG_ILPCTR_MASK	0x00001FFF
#घोषणा	PMU_XTALFREQ_REG_MEASURE_MASK	0x80000000
#घोषणा	PMU_XTALFREQ_REG_MEASURE_SHIFT	31

/* 4313 resources */
#घोषणा	RES4313_BB_PU_RSRC		0
#घोषणा	RES4313_ILP_REQ_RSRC		1
#घोषणा	RES4313_XTAL_PU_RSRC		2
#घोषणा	RES4313_ALP_AVAIL_RSRC		3
#घोषणा	RES4313_RADIO_PU_RSRC		4
#घोषणा	RES4313_BG_PU_RSRC		5
#घोषणा	RES4313_VREG1P4_PU_RSRC		6
#घोषणा	RES4313_AFE_PWRSW_RSRC		7
#घोषणा	RES4313_RX_PWRSW_RSRC		8
#घोषणा	RES4313_TX_PWRSW_RSRC		9
#घोषणा	RES4313_BB_PWRSW_RSRC		10
#घोषणा	RES4313_SYNTH_PWRSW_RSRC	11
#घोषणा	RES4313_MISC_PWRSW_RSRC		12
#घोषणा	RES4313_BB_PLL_PWRSW_RSRC	13
#घोषणा	RES4313_HT_AVAIL_RSRC		14
#घोषणा	RES4313_MACPHY_CLK_AVAIL_RSRC	15

u16 si_pmu_fast_pwrup_delay(काष्ठा si_pub *sih)
अणु
	uपूर्णांक delay = PMU_MAX_TRANSITION_DLY;

	चयन (ai_get_chip_id(sih)) अणु
	हाल BCMA_CHIP_ID_BCM43224:
	हाल BCMA_CHIP_ID_BCM43225:
	हाल BCMA_CHIP_ID_BCM4313:
		delay = 3700;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस (u16) delay;
पूर्ण

u32 si_pmu_measure_alpclk(काष्ठा si_pub *sih)
अणु
	काष्ठा si_info *sii = container_of(sih, काष्ठा si_info, pub);
	काष्ठा bcma_device *core;
	u32 alp_khz;

	अगर (ai_get_pmurev(sih) < 10)
		वापस 0;

	/* Remember original core beक्रमe चयन to chipc */
	core = sii->icbus->drv_cc.core;

	अगर (bcma_पढ़ो32(core, CHIPCREGOFFS(pmustatus)) & PST_EXTLPOAVAIL) अणु
		u32 ilp_ctr, alp_hz;

		/*
		 * Enable the reg to measure the freq,
		 * in हाल it was disabled beक्रमe
		 */
		bcma_ग_लिखो32(core, CHIPCREGOFFS(pmu_xtalfreq),
			    1U << PMU_XTALFREQ_REG_MEASURE_SHIFT);

		/* Delay क्रम well over 4 ILP घड़ीs */
		udelay(1000);

		/* Read the latched number of ALP ticks per 4 ILP ticks */
		ilp_ctr = bcma_पढ़ो32(core, CHIPCREGOFFS(pmu_xtalfreq)) &
			  PMU_XTALFREQ_REG_ILPCTR_MASK;

		/*
		 * Turn off the PMU_XTALFREQ_REG_MEASURE_SHIFT
		 * bit to save घातer
		 */
		bcma_ग_लिखो32(core, CHIPCREGOFFS(pmu_xtalfreq), 0);

		/* Calculate ALP frequency */
		alp_hz = (ilp_ctr * EXT_ILP_HZ) / 4;

		/*
		 * Round to nearest 100KHz, and at
		 * the same समय convert to KHz
		 */
		alp_khz = (alp_hz + 50000) / 100000 * 100;
	पूर्ण अन्यथा
		alp_khz = 0;

	वापस alp_khz;
पूर्ण
