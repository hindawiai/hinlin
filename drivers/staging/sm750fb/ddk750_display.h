<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_DISPLAY_H__
#घोषणा DDK750_DISPLAY_H__

/*
 * panel path select
 *	80000[29:28]
 */

#घोषणा PNL_2_OFFSET 0
#घोषणा PNL_2_MASK (3 << PNL_2_OFFSET)
#घोषणा PNL_2_USAGE	(PNL_2_MASK << 16)
#घोषणा PNL_2_PRI	((0 << PNL_2_OFFSET) | PNL_2_USAGE)
#घोषणा PNL_2_SEC	((2 << PNL_2_OFFSET) | PNL_2_USAGE)

/*
 * primary timing & plane enable bit
 *	1: 80000[8] & 80000[2] on
 *	0: both off
 */
#घोषणा PRI_TP_OFFSET 4
#घोषणा PRI_TP_MASK BIT(PRI_TP_OFFSET)
#घोषणा PRI_TP_USAGE (PRI_TP_MASK << 16)
#घोषणा PRI_TP_ON ((0x1 << PRI_TP_OFFSET) | PRI_TP_USAGE)
#घोषणा PRI_TP_OFF ((0x0 << PRI_TP_OFFSET) | PRI_TP_USAGE)

/*
 * panel sequency status
 *	80000[27:24]
 */
#घोषणा PNL_SEQ_OFFSET 6
#घोषणा PNL_SEQ_MASK BIT(PNL_SEQ_OFFSET)
#घोषणा PNL_SEQ_USAGE (PNL_SEQ_MASK << 16)
#घोषणा PNL_SEQ_ON (BIT(PNL_SEQ_OFFSET) | PNL_SEQ_USAGE)
#घोषणा PNL_SEQ_OFF ((0 << PNL_SEQ_OFFSET) | PNL_SEQ_USAGE)

/*
 * dual digital output
 *	80000[19]
 */
#घोषणा DUAL_TFT_OFFSET 8
#घोषणा DUAL_TFT_MASK BIT(DUAL_TFT_OFFSET)
#घोषणा DUAL_TFT_USAGE (DUAL_TFT_MASK << 16)
#घोषणा DUAL_TFT_ON (BIT(DUAL_TFT_OFFSET) | DUAL_TFT_USAGE)
#घोषणा DUAL_TFT_OFF ((0 << DUAL_TFT_OFFSET) | DUAL_TFT_USAGE)

/*
 * secondary timing & plane enable bit
 *	1:80200[8] & 80200[2] on
 *	0: both off
 */
#घोषणा SEC_TP_OFFSET 5
#घोषणा SEC_TP_MASK BIT(SEC_TP_OFFSET)
#घोषणा SEC_TP_USAGE (SEC_TP_MASK << 16)
#घोषणा SEC_TP_ON  ((0x1 << SEC_TP_OFFSET) | SEC_TP_USAGE)
#घोषणा SEC_TP_OFF ((0x0 << SEC_TP_OFFSET) | SEC_TP_USAGE)

/*
 * crt path select
 *	80200[19:18]
 */
#घोषणा CRT_2_OFFSET 2
#घोषणा CRT_2_MASK (3 << CRT_2_OFFSET)
#घोषणा CRT_2_USAGE (CRT_2_MASK << 16)
#घोषणा CRT_2_PRI ((0x0 << CRT_2_OFFSET) | CRT_2_USAGE)
#घोषणा CRT_2_SEC ((0x2 << CRT_2_OFFSET) | CRT_2_USAGE)

/*
 * DAC affect both DVI and DSUB
 *	4[20]
 */
#घोषणा DAC_OFFSET 7
#घोषणा DAC_MASK BIT(DAC_OFFSET)
#घोषणा DAC_USAGE (DAC_MASK << 16)
#घोषणा DAC_ON ((0x0 << DAC_OFFSET) | DAC_USAGE)
#घोषणा DAC_OFF ((0x1 << DAC_OFFSET) | DAC_USAGE)

/*
 * DPMS only affect D-SUB head
 *	0[31:30]
 */
#घोषणा DPMS_OFFSET 9
#घोषणा DPMS_MASK (3 << DPMS_OFFSET)
#घोषणा DPMS_USAGE (DPMS_MASK << 16)
#घोषणा DPMS_OFF ((3 << DPMS_OFFSET) | DPMS_USAGE)
#घोषणा DPMS_ON ((0 << DPMS_OFFSET) | DPMS_USAGE)

/*
 * LCD1 means panel path TFT1  & panel path DVI (so enable DAC)
 * CRT means crt path DSUB
 */
क्रमागत disp_output अणु
	करो_LCD1_PRI = PNL_2_PRI | PRI_TP_ON | PNL_SEQ_ON | DAC_ON,
	करो_LCD1_SEC = PNL_2_SEC | SEC_TP_ON | PNL_SEQ_ON | DAC_ON,
	करो_LCD2_PRI = CRT_2_PRI | PRI_TP_ON | DUAL_TFT_ON,
	करो_LCD2_SEC = CRT_2_SEC | SEC_TP_ON | DUAL_TFT_ON,
	/*
	 * करो_DSUB_PRI = CRT_2_PRI | PRI_TP_ON | DPMS_ON|DAC_ON,
	 * करो_DSUB_SEC = CRT_2_SEC | SEC_TP_ON | DPMS_ON|DAC_ON,
	 */
	करो_CRT_PRI = CRT_2_PRI | PRI_TP_ON | DPMS_ON | DAC_ON,
	करो_CRT_SEC = CRT_2_SEC | SEC_TP_ON | DPMS_ON | DAC_ON,
पूर्ण;

व्योम ddk750_set_logical_disp_out(क्रमागत disp_output output);

#पूर्ण_अगर
