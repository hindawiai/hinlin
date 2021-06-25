<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/uPD98402.h - NEC uPD98402 (PHY) declarations */
 
/* Written 1995 by Werner Almesberger, EPFL LRC */


#अगर_अघोषित DRIVERS_ATM_uPD98402_H
#घोषणा DRIVERS_ATM_uPD98402_H

/*
 * Registers
 */

#घोषणा uPD98402_CMR		0x00	/* Command Register */
#घोषणा uPD98402_MDR		0x01	/* Mode Register */
#घोषणा uPD98402_PICR		0x02	/* PHY Interrupt Cause Register */
#घोषणा uPD98402_PIMR		0x03	/* PHY Interrupt Mask Register */
#घोषणा uPD98402_ACR		0x04	/* Alarm Cause Register */
#घोषणा uPD98402_ACMR		0x05	/* Alarm Cause Mask Register */
#घोषणा uPD98402_PCR		0x06	/* Perक्रमmance Cause Register */
#घोषणा uPD98402_PCMR		0x07	/* Perक्रमmance Cause Mask Register */
#घोषणा uPD98402_IACM		0x08	/* Internal Alarm Cause Mask Register */
#घोषणा uPD98402_B1ECT		0x09	/* B1 Error Count Register */
#घोषणा uPD98402_B2ECT		0x0a	/* B2 Error Count Register */
#घोषणा uPD98402_B3ECT		0x0b	/* B3 Error Count Regster */
#घोषणा uPD98402_PFECB		0x0c	/* Path FEBE Count Register */
#घोषणा uPD98402_LECCT		0x0d	/* Line FEBE Count Register */
#घोषणा uPD98402_HECCT		0x0e	/* HEC Error Count Register */
#घोषणा uPD98402_FJCT		0x0f	/* Frequence Justअगरication Count Reg */
#घोषणा uPD98402_PCOCR		0x10	/* Perf. Counter Overflow Cause Reg */
#घोषणा uPD98402_PCOMR		0x11	/* Perf. Counter Overflow Mask Reg */
#घोषणा uPD98402_C11T		0x20	/* C11T Data Register */
#घोषणा uPD98402_C12T		0x21	/* C12T Data Register */
#घोषणा uPD98402_C13T		0x22	/* C13T Data Register */
#घोषणा uPD98402_F1T		0x23	/* F1T Data Register */
#घोषणा uPD98402_K2T		0x25	/* K2T Data Register */
#घोषणा uPD98402_C2T		0x26	/* C2T Data Register */
#घोषणा uPD98402_F2T		0x27	/* F2T Data Register */
#घोषणा uPD98402_C11R		0x30	/* C11T Data Register */
#घोषणा uPD98402_C12R		0x31	/* C12T Data Register */
#घोषणा uPD98402_C13R		0x32	/* C13T Data Register */
#घोषणा uPD98402_F1R		0x33	/* F1T Data Register */
#घोषणा uPD98402_K2R		0x35	/* K2T Data Register */
#घोषणा uPD98402_C2R		0x36	/* C2T Data Register */
#घोषणा uPD98402_F2R		0x37	/* F2T Data Register */

/* CMR is at 0x00 */
#घोषणा uPD98402_CMR_PFRF	0x01	/* Send path FERF */
#घोषणा uPD98402_CMR_LFRF	0x02	/* Send line FERF */
#घोषणा uPD98402_CMR_PAIS	0x04	/* Send path AIS */
#घोषणा uPD98402_CMR_LAIS	0x08	/* Send line AIS */

/* MDR is at 0x01 */
#घोषणा uPD98402_MDR_ALP	0x01	/* ATM layer loopback */
#घोषणा uPD98402_MDR_TPLP	0x02	/* PMD loopback, to host */
#घोषणा uPD98402_MDR_RPLP	0x04	/* PMD loopback, to network */
#घोषणा uPD98402_MDR_SS0	0x08	/* SS0 */
#घोषणा uPD98402_MDR_SS1	0x10	/* SS1 */
#घोषणा uPD98402_MDR_SS_MASK	0x18	/* mask */
#घोषणा uPD98402_MDR_SS_SHIFT	3	/* shअगरt */
#घोषणा uPD98402_MDR_HEC	0x20	/* disable HEC inbound processing */
#घोषणा uPD98402_MDR_FSR	0x40	/* disable frame scrambler */
#घोषणा uPD98402_MDR_CSR	0x80	/* disable cell scrambler */

/* PICR is at 0x02, PIMR is at 0x03 */
#घोषणा uPD98402_INT_PFM	0x01	/* perक्रमmance counter has changed */
#घोषणा uPD98402_INT_ALM	0x02	/* line fault */
#घोषणा uPD98402_INT_RFO	0x04	/* receive FIFO overflow */
#घोषणा uPD98402_INT_PCO	0x08	/* perक्रमmance counter overflow */
#घोषणा uPD98402_INT_OTD	0x20	/* OTD has occurred */
#घोषणा uPD98402_INT_LOS	0x40	/* Loss Of Signal */
#घोषणा uPD98402_INT_LOF	0x80	/* Loss Of Frame */

/* ACR is as 0x04, ACMR is at 0x05 */
#घोषणा uPD98402_ALM_PFRF	0x01	/* path FERF */
#घोषणा uPD98402_ALM_LFRF	0x02	/* line FERF */
#घोषणा uPD98402_ALM_PAIS	0x04	/* path AIS */
#घोषणा uPD98402_ALM_LAIS	0x08	/* line AIS */
#घोषणा uPD98402_ALM_LOD	0x10	/* loss of delineation */
#घोषणा uPD98402_ALM_LOP	0x20	/* loss of poपूर्णांकer */
#घोषणा uPD98402_ALM_OOF	0x40	/* out of frame */

/* PCR is at 0x06, PCMR is at 0x07 */
#घोषणा uPD98402_PFM_PFEB	0x01	/* path FEBE */
#घोषणा uPD98402_PFM_LFEB	0x02	/* line FEBE */
#घोषणा uPD98402_PFM_B3E	0x04	/* B3 error */
#घोषणा uPD98402_PFM_B2E	0x08	/* B2 error */
#घोषणा uPD98402_PFM_B1E	0x10	/* B1 error */
#घोषणा uPD98402_PFM_FJ		0x20	/* frequency justअगरication */

/* IACM is at 0x08 */
#घोषणा uPD98402_IACM_PFRF	0x01	/* करोn't generate path FERF */
#घोषणा uPD98402_IACM_LFRF	0x02	/* करोn't generate line FERF */

/* PCOCR is at 0x010, PCOMR is at 0x11 */
#घोषणा uPD98402_PCO_B1EC	0x01	/* B1ECT overflow */
#घोषणा uPD98402_PCO_B2EC	0x02	/* B2ECT overflow */
#घोषणा uPD98402_PCO_B3EC	0x04	/* B3ECT overflow */
#घोषणा uPD98402_PCO_PFBC	0x08	/* PFEBC overflow */
#घोषणा uPD98402_PCO_LFBC	0x10	/* LFEVC overflow */
#घोषणा uPD98402_PCO_HECC	0x20	/* HECCT overflow */
#घोषणा uPD98402_PCO_FJC	0x40	/* FJCT overflow */


पूर्णांक uPD98402_init(काष्ठा aपंचांग_dev *dev);

#पूर्ण_अगर
