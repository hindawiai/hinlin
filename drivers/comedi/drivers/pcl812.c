<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * comedi/drivers/pcl812.c
 *
 * Author: Michal Dobes <करोbes@tesnet.cz>
 *
 * hardware driver क्रम Advantech cards
 *  card:   PCL-812, PCL-812PG, PCL-813, PCL-813B
 *  driver: pcl812,  pcl812pg,  pcl813,  pcl813b
 * and क्रम ADlink cards
 *  card:   ACL-8112DG, ACL-8112HG, ACL-8112PG, ACL-8113, ACL-8216
 *  driver: acl8112dg,  acl8112hg,  acl8112pg,  acl8113,  acl8216
 * and क्रम ICP DAS cards
 *  card:   ISO-813, A-821PGH, A-821PGL, A-821PGL-NDA, A-822PGH, A-822PGL,
 *  driver: iso813,  a821pgh,  a-821pgl, a-821pglnda,  a822pgh,  a822pgl,
 *  card:   A-823PGH, A-823PGL, A-826PG
 * driver:  a823pgh,  a823pgl,  a826pg
 */

/*
 * Driver: pcl812
 * Description: Advantech PCL-812/PG, PCL-813/B,
 *	     ADLink ACL-8112DG/HG/PG, ACL-8113, ACL-8216,
 *	     ICP DAS A-821PGH/PGL/PGL-NDA, A-822PGH/PGL, A-823PGH/PGL, A-826PG,
 *	     ICP DAS ISO-813
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Devices: [Advantech] PCL-812 (pcl812), PCL-812PG (pcl812pg),
 *	PCL-813 (pcl813), PCL-813B (pcl813b), [ADLink] ACL-8112DG (acl8112dg),
 *	ACL-8112HG (acl8112hg), ACL-8113 (acl-8113), ACL-8216 (acl8216),
 *	[ICP] ISO-813 (iso813), A-821PGH (a821pgh), A-821PGL (a821pgl),
 *	A-821PGL-NDA (a821pclnda), A-822PGH (a822pgh), A-822PGL (a822pgl),
 *	A-823PGH (a823pgh), A-823PGL (a823pgl), A-826PG (a826pg)
 * Updated: Mon, 06 Aug 2007 12:03:15 +0100
 * Status: works (I hope. My board fire up under my hands
 *	       and I cann't test all features.)
 *
 * This driver supports insn and cmd पूर्णांकerfaces. Some boards support only insn
 * because their hardware करोn't allow more (PCL-813/B, ACL-8113, ISO-813).
 * Data transfer over DMA is supported only when you measure only one
 * channel, this is too hardware limitation of these boards.
 *
 * Options क्रम PCL-812:
 *   [0] - IO Base
 *   [1] - IRQ  (0=disable, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disable, 1, 3)
 *   [3] - 0=trigger source is पूर्णांकernal 8253 with 2MHz घड़ी
 *         1=trigger source is बाह्यal
 *   [4] - 0=A/D input range is +/-10V
 *	   1=A/D input range is +/-5V
 *	   2=A/D input range is +/-2.5V
 *	   3=A/D input range is +/-1.25V
 *	   4=A/D input range is +/-0.625V
 *	   5=A/D input range is +/-0.3125V
 *   [5] - 0=D/A outमाला_दो 0-5V  (पूर्णांकernal reference -5V)
 *	   1=D/A outमाला_दो 0-10V (पूर्णांकernal reference -10V)
 *	   2=D/A outमाला_दो unknown (बाह्यal reference)
 *
 * Options क्रम PCL-812PG, ACL-8112PG:
 *   [0] - IO Base
 *   [1] - IRQ  (0=disable, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disable, 1, 3)
 *   [3] - 0=trigger source is पूर्णांकernal 8253 with 2MHz घड़ी
 *	   1=trigger source is बाह्यal
 *   [4] - 0=A/D have max +/-5V input
 *	   1=A/D have max +/-10V input
 *   [5] - 0=D/A outमाला_दो 0-5V  (पूर्णांकernal reference -5V)
 *	   1=D/A outमाला_दो 0-10V (पूर्णांकernal reference -10V)
 *	   2=D/A outमाला_दो unknown (बाह्यal reference)
 *
 * Options क्रम ACL-8112DG/HG, A-822PGL/PGH, A-823PGL/PGH, ACL-8216, A-826PG:
 *   [0] - IO Base
 *   [1] - IRQ  (0=disable, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disable, 1, 3)
 *   [3] - 0=trigger source is पूर्णांकernal 8253 with 2MHz घड़ी
 *	   1=trigger source is बाह्यal
 *   [4] - 0=A/D channels are S.E.
 *	   1=A/D channels are DIFF
 *   [5] - 0=D/A outमाला_दो 0-5V  (पूर्णांकernal reference -5V)
 *	   1=D/A outमाला_दो 0-10V (पूर्णांकernal reference -10V)
 *	   2=D/A outमाला_दो unknown (बाह्यal reference)
 *
 * Options क्रम A-821PGL/PGH:
 *   [0] - IO Base
 *   [1] - IRQ  (0=disable, 2, 3, 4, 5, 6, 7)
 *   [2] - 0=A/D channels are S.E.
 *	   1=A/D channels are DIFF
 *   [3] - 0=D/A output 0-5V  (पूर्णांकernal reference -5V)
 *	   1=D/A output 0-10V (पूर्णांकernal reference -10V)
 *
 * Options क्रम A-821PGL-NDA:
 *   [0] - IO Base
 *   [1] - IRQ  (0=disable, 2, 3, 4, 5, 6, 7)
 *   [2] - 0=A/D channels are S.E.
 *	   1=A/D channels are DIFF
 *
 * Options क्रम PCL-813:
 *   [0] - IO Base
 *
 * Options क्रम PCL-813B:
 *   [0] - IO Base
 *   [1] - 0= bipolar inमाला_दो
 *	   1= unipolar inमाला_दो
 *
 * Options क्रम ACL-8113, ISO-813:
 *   [0] - IO Base
 *   [1] - 0= 10V bipolar inमाला_दो
 *	   1= 10V unipolar inमाला_दो
 *	   2= 20V bipolar inमाला_दो
 *	   3= 20V unipolar inमाला_दो
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"

/*
 * Register I/O map
 */
#घोषणा PCL812_TIMER_BASE			0x00
#घोषणा PCL812_AI_LSB_REG			0x04
#घोषणा PCL812_AI_MSB_REG			0x05
#घोषणा PCL812_AI_MSB_DRDY			BIT(4)
#घोषणा PCL812_AO_LSB_REG(x)			(0x04 + ((x) * 2))
#घोषणा PCL812_AO_MSB_REG(x)			(0x05 + ((x) * 2))
#घोषणा PCL812_DI_LSB_REG			0x06
#घोषणा PCL812_DI_MSB_REG			0x07
#घोषणा PCL812_STATUS_REG			0x08
#घोषणा PCL812_STATUS_DRDY			BIT(5)
#घोषणा PCL812_RANGE_REG			0x09
#घोषणा PCL812_MUX_REG				0x0a
#घोषणा PCL812_MUX_CHAN(x)			((x) << 0)
#घोषणा PCL812_MUX_CS0				BIT(4)
#घोषणा PCL812_MUX_CS1				BIT(5)
#घोषणा PCL812_CTRL_REG				0x0b
#घोषणा PCL812_CTRL_TRIG(x)			(((x) & 0x7) << 0)
#घोषणा PCL812_CTRL_DISABLE_TRIG		PCL812_CTRL_TRIG(0)
#घोषणा PCL812_CTRL_SOFT_TRIG			PCL812_CTRL_TRIG(1)
#घोषणा PCL812_CTRL_PACER_DMA_TRIG		PCL812_CTRL_TRIG(2)
#घोषणा PCL812_CTRL_PACER_EOC_TRIG		PCL812_CTRL_TRIG(6)
#घोषणा PCL812_SOFTTRIG_REG			0x0c
#घोषणा PCL812_DO_LSB_REG			0x0d
#घोषणा PCL812_DO_MSB_REG			0x0e

#घोषणा MAX_CHANLIST_LEN    256	/* length of scan list */

अटल स्थिर काष्ठा comedi_lrange range_pcl812pg_ai = अणु
	5, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		BIP_RANGE(0.3125)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl812pg2_ai = अणु
	5, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range812_bipolar1_25 = अणु
	1, अणु
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range812_bipolar0_625 = अणु
	1, अणु
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range812_bipolar0_3125 = अणु
	1, अणु
		BIP_RANGE(0.3125)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl813b_ai = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl813b2_ai = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_iso813_1_ai = अणु
	5, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		BIP_RANGE(0.3125)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_iso813_1_2_ai = अणु
	5, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		UNI_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_iso813_2_ai = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_iso813_2_2_ai = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8113_1_ai = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8113_1_2_ai = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8113_2_ai = अणु
	3, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8113_2_2_ai = अणु
	3, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8112dg_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_acl8112hg_ai = अणु
	12, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.005),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01),
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_a821pgh_ai = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.005)
	पूर्ण
पूर्ण;

क्रमागत pcl812_boardtype अणु
	BOARD_PCL812PG	= 0,	/* and ACL-8112PG */
	BOARD_PCL813B	= 1,
	BOARD_PCL812	= 2,
	BOARD_PCL813	= 3,
	BOARD_ISO813	= 5,
	BOARD_ACL8113	= 6,
	BOARD_ACL8112	= 7,	/* ACL-8112DG/HG, A-822PGL/PGH, A-823PGL/PGH */
	BOARD_ACL8216	= 8,	/* and ICP DAS A-826PG */
	BOARD_A821	= 9,	/* PGH, PGL, PGL/NDA versions */
पूर्ण;

काष्ठा pcl812_board अणु
	स्थिर अक्षर *name;
	क्रमागत pcl812_boardtype board_type;
	पूर्णांक n_aichan;
	पूर्णांक n_aochan;
	अचिन्हित पूर्णांक ai_ns_min;
	स्थिर काष्ठा comedi_lrange *rangelist_ai;
	अचिन्हित पूर्णांक irq_bits;
	अचिन्हित पूर्णांक has_dma:1;
	अचिन्हित पूर्णांक has_16bit_ai:1;
	अचिन्हित पूर्णांक has_mpc508_mux:1;
	अचिन्हित पूर्णांक has_dio:1;
पूर्ण;

अटल स्थिर काष्ठा pcl812_board boardtypes[] = अणु
	अणु
		.name		= "pcl812",
		.board_type	= BOARD_PCL812,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 33000,
		.rangelist_ai	= &range_bipolar10,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "pcl812pg",
		.board_type	= BOARD_PCL812PG,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 33000,
		.rangelist_ai	= &range_pcl812pg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "acl8112pg",
		.board_type	= BOARD_PCL812PG,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_pcl812pg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "acl8112dg",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_acl8112dg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "acl8112hg",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_acl8112hg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a821pgl",
		.board_type	= BOARD_A821,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 1,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_pcl813b_ai,
		.irq_bits	= 0x000c,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a821pglnda",
		.board_type	= BOARD_A821,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_pcl813b_ai,
		.irq_bits	= 0x000c,
	पूर्ण, अणु
		.name		= "a821pgh",
		.board_type	= BOARD_A821,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 1,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_a821pgh_ai,
		.irq_bits	= 0x000c,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a822pgl",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_acl8112dg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a822pgh",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_acl8112hg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a823pgl",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 8000,
		.rangelist_ai	= &range_acl8112dg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a823pgh",
		.board_type	= BOARD_ACL8112,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 8000,
		.rangelist_ai	= &range_acl8112hg_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "pcl813",
		.board_type	= BOARD_PCL813,
		.n_aichan	= 32,
		.rangelist_ai	= &range_pcl813b_ai,
	पूर्ण, अणु
		.name		= "pcl813b",
		.board_type	= BOARD_PCL813B,
		.n_aichan	= 32,
		.rangelist_ai	= &range_pcl813b_ai,
	पूर्ण, अणु
		.name		= "acl8113",
		.board_type	= BOARD_ACL8113,
		.n_aichan	= 32,
		.rangelist_ai	= &range_acl8113_1_ai,
	पूर्ण, अणु
		.name		= "iso813",
		.board_type	= BOARD_ISO813,
		.n_aichan	= 32,
		.rangelist_ai	= &range_iso813_1_ai,
	पूर्ण, अणु
		.name		= "acl8216",
		.board_type	= BOARD_ACL8216,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_pcl813b2_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_16bit_ai	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	पूर्ण, अणु
		.name		= "a826pg",
		.board_type	= BOARD_ACL8216,
		.n_aichan	= 16,	/* 8 dअगरferential */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.rangelist_ai	= &range_pcl813b2_ai,
		.irq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_16bit_ai	= 1,
		.has_dio	= 1,
	पूर्ण,
पूर्ण;

काष्ठा pcl812_निजी अणु
	काष्ठा comedi_isadma *dma;
	अचिन्हित अक्षर range_correction;	/* =1 we must add 1 to range number */
	अचिन्हित पूर्णांक last_ai_chanspec;
	अचिन्हित अक्षर mode_reg_पूर्णांक; /* stored INT number क्रम some cards */
	अचिन्हित पूर्णांक ai_poll_ptr; /* how many samples transfer poll */
	अचिन्हित पूर्णांक max_812_ai_mode0_rangeरुको; /* settling समय क्रम gain */
	अचिन्हित पूर्णांक use_dअगरf:1;
	अचिन्हित पूर्णांक use_mpc508:1;
	अचिन्हित पूर्णांक use_ext_trg:1;
	अचिन्हित पूर्णांक ai_dma:1;
	अचिन्हित पूर्णांक ai_eos:1;
पूर्ण;

अटल व्योम pcl812_ai_setup_dma(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक unपढ़ो_samples)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक bytes;
	अचिन्हित पूर्णांक max_samples;
	अचिन्हित पूर्णांक nsamples;

	comedi_isadma_disable(dma->chan);

	/* अगर using EOS, adapt DMA buffer to one scan */
	bytes = devpriv->ai_eos ? comedi_bytes_per_scan(s) : desc->maxsize;
	max_samples = comedi_bytes_to_samples(s, bytes);

	/*
	 * Determine dma size based on the buffer size plus the number of
	 * unपढ़ो samples and the number of samples reमुख्यing in the command.
	 */
	nsamples = comedi_nsamples_left(s, max_samples + unपढ़ो_samples);
	अगर (nsamples > unपढ़ो_samples) अणु
		nsamples -= unपढ़ो_samples;
		desc->size = comedi_samples_to_bytes(s, nsamples);
		comedi_isadma_program(desc);
	पूर्ण
पूर्ण

अटल व्योम pcl812_ai_set_chan_range(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक chanspec, अक्षर रुको)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक mux = 0;

	अगर (chanspec == devpriv->last_ai_chanspec)
		वापस;

	devpriv->last_ai_chanspec = chanspec;

	अगर (devpriv->use_mpc508) अणु
		अगर (devpriv->use_dअगरf) अणु
			mux |= PCL812_MUX_CS0 | PCL812_MUX_CS1;
		पूर्ण अन्यथा अणु
			अगर (chan < 8)
				mux |= PCL812_MUX_CS0;
			अन्यथा
				mux |= PCL812_MUX_CS1;
		पूर्ण
	पूर्ण

	outb(mux | PCL812_MUX_CHAN(chan), dev->iobase + PCL812_MUX_REG);
	outb(range + devpriv->range_correction, dev->iobase + PCL812_RANGE_REG);

	अगर (रुको)
		/*
		 * XXX this depends on selected range and can be very दीर्घ क्रम
		 * some high gain ranges!
		 */
		udelay(devpriv->max_812_ai_mode0_rangeरुको);
पूर्ण

अटल व्योम pcl812_ai_clear_eoc(काष्ठा comedi_device *dev)
अणु
	/* writing any value clears the पूर्णांकerrupt request */
	outb(0, dev->iobase + PCL812_STATUS_REG);
पूर्ण

अटल व्योम pcl812_ai_soft_trig(काष्ठा comedi_device *dev)
अणु
	/* writing any value triggers a software conversion */
	outb(255, dev->iobase + PCL812_SOFTTRIG_REG);
पूर्ण

अटल अचिन्हित पूर्णांक pcl812_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL812_AI_MSB_REG) << 8;
	val |= inb(dev->iobase + PCL812_AI_LSB_REG);

	वापस val & s->maxdata;
पूर्ण

अटल पूर्णांक pcl812_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	अगर (s->maxdata > 0x0fff) अणु
		status = inb(dev->iobase + PCL812_STATUS_REG);
		अगर ((status & PCL812_STATUS_DRDY) == 0)
			वापस 0;
	पूर्ण अन्यथा अणु
		status = inb(dev->iobase + PCL812_AI_MSB_REG);
		अगर ((status & PCL812_AI_MSB_DRDY) == 0)
			वापस 0;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pcl812_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcl812_board *board = dev->board_ptr;
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक flags;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);

	अगर (devpriv->use_ext_trg)
		flags = TRIG_EXT;
	अन्यथा
		flags = TRIG_TIMER;
	err |= comedi_check_trigger_src(&cmd->convert_src, flags);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_ns_min);
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->convert_arg;

		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक pcl812_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक ctrl = 0;
	अचिन्हित पूर्णांक i;

	pcl812_ai_set_chan_range(dev, cmd->chanlist[0], 1);

	अगर (dma) अणु	/*  check अगर we can use DMA transfer */
		devpriv->ai_dma = 1;
		क्रम (i = 1; i < cmd->chanlist_len; i++)
			अगर (cmd->chanlist[0] != cmd->chanlist[i]) अणु
				/*  we cann't use DMA :-( */
				devpriv->ai_dma = 0;
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा अणु
		devpriv->ai_dma = 0;
	पूर्ण

	devpriv->ai_poll_ptr = 0;

	/*  करोn't we want wake up every scan? */
	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		devpriv->ai_eos = 1;

		/*  DMA is useless क्रम this situation */
		अगर (cmd->chanlist_len == 1)
			devpriv->ai_dma = 0;
	पूर्ण

	अगर (devpriv->ai_dma) अणु
		/* setup and enable dma क्रम the first buffer */
		dma->cur_dma = 0;
		pcl812_ai_setup_dma(dev, s, 0);
	पूर्ण

	चयन (cmd->convert_src) अणु
	हाल TRIG_TIMER:
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		अवरोध;
	पूर्ण

	अगर (devpriv->ai_dma)
		ctrl |= PCL812_CTRL_PACER_DMA_TRIG;
	अन्यथा
		ctrl |= PCL812_CTRL_PACER_EOC_TRIG;
	outb(devpriv->mode_reg_पूर्णांक | ctrl, dev->iobase + PCL812_CTRL_REG);

	वापस 0;
पूर्ण

अटल bool pcl812_ai_next_chan(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg) अणु
		s->async->events |= COMEDI_CB_EOA;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम pcl812_handle_eoc(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक chan = s->async->cur_chan;
	अचिन्हित पूर्णांक next_chan;
	अचिन्हित लघु val;

	अगर (pcl812_ai_eoc(dev, s, शून्य, 0)) अणु
		dev_dbg(dev->class_dev, "A/D cmd IRQ without DRDY!\n");
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	val = pcl812_ai_get_sample(dev, s);
	comedi_buf_ग_लिखो_samples(s, &val, 1);

	/* Set up next channel. Added by abbotti 2010-01-20, but untested. */
	next_chan = s->async->cur_chan;
	अगर (cmd->chanlist[chan] != cmd->chanlist[next_chan])
		pcl812_ai_set_chan_range(dev, cmd->chanlist[next_chan], 0);

	pcl812_ai_next_chan(dev, s);
पूर्ण

अटल व्योम transfer_from_dma_buf(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित लघु *ptr,
				  अचिन्हित पूर्णांक bufptr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित लघु val;

	क्रम (i = len; i; i--) अणु
		val = ptr[bufptr++];
		comedi_buf_ग_लिखो_samples(s, &val, 1);

		अगर (!pcl812_ai_next_chan(dev, s))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pcl812_handle_dma(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक nsamples;
	पूर्णांक bufptr;

	nsamples = comedi_bytes_to_samples(s, desc->size) -
		   devpriv->ai_poll_ptr;
	bufptr = devpriv->ai_poll_ptr;
	devpriv->ai_poll_ptr = 0;

	/* restart dma with the next buffer */
	dma->cur_dma = 1 - dma->cur_dma;
	pcl812_ai_setup_dma(dev, s, nsamples);

	transfer_from_dma_buf(dev, s, desc->virt_addr, bufptr, nsamples);
पूर्ण

अटल irqवापस_t pcl812_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा pcl812_निजी *devpriv = dev->निजी;

	अगर (!dev->attached) अणु
		pcl812_ai_clear_eoc(dev);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (devpriv->ai_dma)
		pcl812_handle_dma(dev, s);
	अन्यथा
		pcl812_handle_eoc(dev, s);

	pcl812_ai_clear_eoc(dev);

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcl812_ai_poll(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक poll;
	पूर्णांक ret;

	/* poll is valid only क्रम DMA transfer */
	अगर (!devpriv->ai_dma)
		वापस 0;

	spin_lock_irqsave(&dev->spinlock, flags);

	poll = comedi_isadma_poll(dma);
	poll = comedi_bytes_to_samples(s, poll);
	अगर (poll > devpriv->ai_poll_ptr) अणु
		desc = &dma->desc[dma->cur_dma];
		transfer_from_dma_buf(dev, s, desc->virt_addr,
				      devpriv->ai_poll_ptr,
				      poll - devpriv->ai_poll_ptr);
		/* new buffer position */
		devpriv->ai_poll_ptr = poll;

		ret = comedi_buf_n_bytes_पढ़ोy(s);
	पूर्ण अन्यथा अणु
		/* no new samples */
		ret = 0;
	पूर्ण

	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक pcl812_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;

	अगर (devpriv->ai_dma)
		comedi_isadma_disable(devpriv->dma->chan);

	outb(devpriv->mode_reg_पूर्णांक | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	pcl812_ai_clear_eoc(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pcl812_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	पूर्णांक ret = 0;
	पूर्णांक i;

	outb(devpriv->mode_reg_पूर्णांक | PCL812_CTRL_SOFT_TRIG,
	     dev->iobase + PCL812_CTRL_REG);

	pcl812_ai_set_chan_range(dev, insn->chanspec, 1);

	क्रम (i = 0; i < insn->n; i++) अणु
		pcl812_ai_clear_eoc(dev);
		pcl812_ai_soft_trig(dev);

		ret = comedi_समयout(dev, s, insn, pcl812_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		data[i] = pcl812_ai_get_sample(dev, s);
	पूर्ण
	outb(devpriv->mode_reg_पूर्णांक | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	pcl812_ai_clear_eoc(dev);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक pcl812_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outb(val & 0xff, dev->iobase + PCL812_AO_LSB_REG(chan));
		outb((val >> 8) & 0x0f, dev->iobase + PCL812_AO_MSB_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl812_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PCL812_DI_LSB_REG) |
		  (inb(dev->iobase + PCL812_DI_MSB_REG) << 8);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl812_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + PCL812_DO_LSB_REG);
		outb((s->state >> 8), dev->iobase + PCL812_DO_MSB_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम pcl812_reset(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcl812_board *board = dev->board_ptr;
	काष्ठा pcl812_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan;

	/* disable analog input trigger */
	outb(devpriv->mode_reg_पूर्णांक | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	pcl812_ai_clear_eoc(dev);

	/*
	 * Invalidate last_ai_chanspec then set analog input to
	 * known channel/range.
	 */
	devpriv->last_ai_chanspec = CR_PACK(16, 0, 0);
	pcl812_ai_set_chan_range(dev, CR_PACK(0, 0, 0), 0);

	/* set analog output channels to 0V */
	क्रम (chan = 0; chan < board->n_aochan; chan++) अणु
		outb(0, dev->iobase + PCL812_AO_LSB_REG(chan));
		outb(0, dev->iobase + PCL812_AO_MSB_REG(chan));
	पूर्ण

	/* set all digital outमाला_दो low */
	अगर (board->has_dio) अणु
		outb(0, dev->iobase + PCL812_DO_MSB_REG);
		outb(0, dev->iobase + PCL812_DO_LSB_REG);
	पूर्ण
पूर्ण

अटल व्योम pcl812_set_ai_range_table(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl812_board *board = dev->board_ptr;
	काष्ठा pcl812_निजी *devpriv = dev->निजी;

	चयन (board->board_type) अणु
	हाल BOARD_PCL812PG:
		अगर (it->options[4] == 1)
			s->range_table = &range_pcl812pg2_ai;
		अन्यथा
			s->range_table = board->rangelist_ai;
		अवरोध;
	हाल BOARD_PCL812:
		चयन (it->options[4]) अणु
		हाल 0:
			s->range_table = &range_bipolar10;
			अवरोध;
		हाल 1:
			s->range_table = &range_bipolar5;
			अवरोध;
		हाल 2:
			s->range_table = &range_bipolar2_5;
			अवरोध;
		हाल 3:
			s->range_table = &range812_bipolar1_25;
			अवरोध;
		हाल 4:
			s->range_table = &range812_bipolar0_625;
			अवरोध;
		हाल 5:
			s->range_table = &range812_bipolar0_3125;
			अवरोध;
		शेष:
			s->range_table = &range_bipolar10;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BOARD_PCL813B:
		अगर (it->options[1] == 1)
			s->range_table = &range_pcl813b2_ai;
		अन्यथा
			s->range_table = board->rangelist_ai;
		अवरोध;
	हाल BOARD_ISO813:
		चयन (it->options[1]) अणु
		हाल 0:
			s->range_table = &range_iso813_1_ai;
			अवरोध;
		हाल 1:
			s->range_table = &range_iso813_1_2_ai;
			अवरोध;
		हाल 2:
			s->range_table = &range_iso813_2_ai;
			devpriv->range_correction = 1;
			अवरोध;
		हाल 3:
			s->range_table = &range_iso813_2_2_ai;
			devpriv->range_correction = 1;
			अवरोध;
		शेष:
			s->range_table = &range_iso813_1_ai;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BOARD_ACL8113:
		चयन (it->options[1]) अणु
		हाल 0:
			s->range_table = &range_acl8113_1_ai;
			अवरोध;
		हाल 1:
			s->range_table = &range_acl8113_1_2_ai;
			अवरोध;
		हाल 2:
			s->range_table = &range_acl8113_2_ai;
			devpriv->range_correction = 1;
			अवरोध;
		हाल 3:
			s->range_table = &range_acl8113_2_2_ai;
			devpriv->range_correction = 1;
			अवरोध;
		शेष:
			s->range_table = &range_acl8113_1_ai;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		s->range_table = board->rangelist_ai;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pcl812_alloc_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक dma_chan)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;

	/* only DMA channels 3 and 1 are valid */
	अगर (!(dma_chan == 3 || dma_chan == 1))
		वापस;

	/* DMA uses two 8K buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 2, COMEDI_ISADMA_READ);
पूर्ण

अटल व्योम pcl812_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcl812_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल पूर्णांक pcl812_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl812_board *board = dev->board_ptr;
	काष्ठा pcl812_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक n_subdevices;
	पूर्णांक subdev;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	अगर (board->irq_bits) अणु
		dev->pacer = comedi_8254_init(dev->iobase + PCL812_TIMER_BASE,
					      I8254_OSC_BASE_2MHZ,
					      I8254_IO8, 0);
		अगर (!dev->pacer)
			वापस -ENOMEM;

		अगर ((1 << it->options[1]) & board->irq_bits) अणु
			ret = request_irq(it->options[1], pcl812_पूर्णांकerrupt, 0,
					  dev->board_name, dev);
			अगर (ret == 0)
				dev->irq = it->options[1];
		पूर्ण
	पूर्ण

	/* we need an IRQ to करो DMA on channel 3 or 1 */
	अगर (dev->irq && board->has_dma)
		pcl812_alloc_dma(dev, it->options[2]);

	/* dअगरferential analog inमाला_दो? */
	चयन (board->board_type) अणु
	हाल BOARD_A821:
		अगर (it->options[2] == 1)
			devpriv->use_dअगरf = 1;
		अवरोध;
	हाल BOARD_ACL8112:
	हाल BOARD_ACL8216:
		अगर (it->options[4] == 1)
			devpriv->use_dअगरf = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	n_subdevices = 1;		/* all boardtypes have analog inमाला_दो */
	अगर (board->n_aochan > 0)
		n_subdevices++;
	अगर (board->has_dio)
		n_subdevices += 2;

	ret = comedi_alloc_subdevices(dev, n_subdevices);
	अगर (ret)
		वापस ret;

	subdev = 0;

	/* Analog Input subdevice */
	s = &dev->subdevices[subdev];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE;
	अगर (devpriv->use_dअगरf) अणु
		s->subdev_flags	|= SDF_DIFF;
		s->n_chan	= board->n_aichan / 2;
	पूर्ण अन्यथा अणु
		s->subdev_flags	|= SDF_GROUND;
		s->n_chan	= board->n_aichan;
	पूर्ण
	s->maxdata	= board->has_16bit_ai ? 0xffff : 0x0fff;

	pcl812_set_ai_range_table(dev, s, it);

	s->insn_पढ़ो	= pcl812_ai_insn_पढ़ो;

	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= MAX_CHANLIST_LEN;
		s->करो_cmdtest	= pcl812_ai_cmdtest;
		s->करो_cmd	= pcl812_ai_cmd;
		s->poll		= pcl812_ai_poll;
		s->cancel	= pcl812_ai_cancel;
	पूर्ण

	devpriv->use_mpc508 = board->has_mpc508_mux;

	subdev++;

	/* analog output */
	अगर (board->n_aochan > 0) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= board->n_aochan;
		s->maxdata	= 0xfff;
		चयन (board->board_type) अणु
		हाल BOARD_A821:
			अगर (it->options[3] == 1)
				s->range_table = &range_unipolar10;
			अन्यथा
				s->range_table = &range_unipolar5;
			अवरोध;
		हाल BOARD_PCL812:
		हाल BOARD_ACL8112:
		हाल BOARD_PCL812PG:
		हाल BOARD_ACL8216:
			चयन (it->options[5]) अणु
			हाल 1:
				s->range_table = &range_unipolar10;
				अवरोध;
			हाल 2:
				s->range_table = &range_unknown;
				अवरोध;
			शेष:
				s->range_table = &range_unipolar5;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			s->range_table = &range_unipolar5;
			अवरोध;
		पूर्ण
		s->insn_ग_लिखो	= pcl812_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		subdev++;
	पूर्ण

	अगर (board->has_dio) अणु
		/* Digital Input subdevice */
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl812_di_insn_bits;
		subdev++;

		/* Digital Output subdevice */
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl812_करो_insn_bits;
		subdev++;
	पूर्ण

	चयन (board->board_type) अणु
	हाल BOARD_ACL8216:
	हाल BOARD_PCL812PG:
	हाल BOARD_PCL812:
	हाल BOARD_ACL8112:
		devpriv->max_812_ai_mode0_rangeरुको = 1;
		अगर (it->options[3] > 0)
						/*  we use बाह्यal trigger */
			devpriv->use_ext_trg = 1;
		अवरोध;
	हाल BOARD_A821:
		devpriv->max_812_ai_mode0_rangeरुको = 1;
		devpriv->mode_reg_पूर्णांक = (dev->irq << 4) & 0xf0;
		अवरोध;
	हाल BOARD_PCL813B:
	हाल BOARD_PCL813:
	हाल BOARD_ISO813:
	हाल BOARD_ACL8113:
		/* maybe there must by greatest समयout */
		devpriv->max_812_ai_mode0_rangeरुको = 5;
		अवरोध;
	पूर्ण

	pcl812_reset(dev);

	वापस 0;
पूर्ण

अटल व्योम pcl812_detach(काष्ठा comedi_device *dev)
अणु
	pcl812_मुक्त_dma(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver pcl812_driver = अणु
	.driver_name	= "pcl812",
	.module		= THIS_MODULE,
	.attach		= pcl812_attach,
	.detach		= pcl812_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा pcl812_board),
पूर्ण;
module_comedi_driver(pcl812_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
