<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __FSL_FTM_H__
#घोषणा __FSL_FTM_H__

#घोषणा FTM_SC       0x0 /* Status And Control */
#घोषणा FTM_CNT      0x4 /* Counter */
#घोषणा FTM_MOD      0x8 /* Modulo */

#घोषणा FTM_CNTIN    0x4C /* Counter Initial Value */
#घोषणा FTM_STATUS   0x50 /* Capture And Compare Status */
#घोषणा FTM_MODE     0x54 /* Features Mode Selection */
#घोषणा FTM_SYNC     0x58 /* Synchronization */
#घोषणा FTM_OUTINIT  0x5C /* Initial State For Channels Output */
#घोषणा FTM_OUTMASK  0x60 /* Output Mask */
#घोषणा FTM_COMBINE  0x64 /* Function For Linked Channels */
#घोषणा FTM_DEADTIME 0x68 /* Deadसमय Insertion Control */
#घोषणा FTM_EXTTRIG  0x6C /* FTM External Trigger */
#घोषणा FTM_POL      0x70 /* Channels Polarity */
#घोषणा FTM_FMS      0x74 /* Fault Mode Status */
#घोषणा FTM_FILTER   0x78 /* Input Capture Filter Control */
#घोषणा FTM_FLTCTRL  0x7C /* Fault Control */
#घोषणा FTM_QDCTRL   0x80 /* Quadrature Decoder Control And Status */
#घोषणा FTM_CONF     0x84 /* Configuration */
#घोषणा FTM_FLTPOL   0x88 /* FTM Fault Input Polarity */
#घोषणा FTM_SYNCONF  0x8C /* Synchronization Configuration */
#घोषणा FTM_INVCTRL  0x90 /* FTM Inverting Control */
#घोषणा FTM_SWOCTRL  0x94 /* FTM Software Output Control */
#घोषणा FTM_PWMLOAD  0x98 /* FTM PWM Load */

#घोषणा FTM_SC_CLK_MASK_SHIFT	3
#घोषणा FTM_SC_CLK_MASK		(3 << FTM_SC_CLK_MASK_SHIFT)
#घोषणा FTM_SC_TOF		0x80
#घोषणा FTM_SC_TOIE		0x40
#घोषणा FTM_SC_CPWMS		0x20
#घोषणा FTM_SC_CLKS		0x18
#घोषणा FTM_SC_PS_1		0x0
#घोषणा FTM_SC_PS_2		0x1
#घोषणा FTM_SC_PS_4		0x2
#घोषणा FTM_SC_PS_8		0x3
#घोषणा FTM_SC_PS_16		0x4
#घोषणा FTM_SC_PS_32		0x5
#घोषणा FTM_SC_PS_64		0x6
#घोषणा FTM_SC_PS_128		0x7
#घोषणा FTM_SC_PS_MASK		0x7

#घोषणा FTM_MODE_FAULTIE	0x80
#घोषणा FTM_MODE_FAULTM		0x60
#घोषणा FTM_MODE_CAPTEST	0x10
#घोषणा FTM_MODE_PWMSYNC	0x8
#घोषणा FTM_MODE_WPDIS		0x4
#घोषणा FTM_MODE_INIT		0x2
#घोषणा FTM_MODE_FTMEN		0x1

/* NXP Errata: The PHAFLTREN and PHBFLTREN bits are tide to zero पूर्णांकernally
 * and these bits cannot be set. Flexसमयr cannot use Filter in
 * Quadrature Decoder Mode.
 * https://community.nxp.com/thपढ़ो/467648#comment-1010319
 */
#घोषणा FTM_QDCTRL_PHAFLTREN	0x80
#घोषणा FTM_QDCTRL_PHBFLTREN	0x40
#घोषणा FTM_QDCTRL_PHAPOL	0x20
#घोषणा FTM_QDCTRL_PHBPOL	0x10
#घोषणा FTM_QDCTRL_QUADMODE	0x8
#घोषणा FTM_QDCTRL_QUADसूची	0x4
#घोषणा FTM_QDCTRL_TOFसूची	0x2
#घोषणा FTM_QDCTRL_QUADEN	0x1

#घोषणा FTM_FMS_FAULTF		0x80
#घोषणा FTM_FMS_WPEN		0x40
#घोषणा FTM_FMS_FAULTIN		0x10
#घोषणा FTM_FMS_FAULTF3		0x8
#घोषणा FTM_FMS_FAULTF2		0x4
#घोषणा FTM_FMS_FAULTF1		0x2
#घोषणा FTM_FMS_FAULTF0		0x1

#घोषणा FTM_CSC_BASE		0xC
#घोषणा FTM_CSC_MSB		0x20
#घोषणा FTM_CSC_MSA		0x10
#घोषणा FTM_CSC_ELSB		0x8
#घोषणा FTM_CSC_ELSA		0x4
#घोषणा FTM_CSC(_channel)	(FTM_CSC_BASE + ((_channel) * 8))

#घोषणा FTM_CV_BASE		0x10
#घोषणा FTM_CV(_channel)	(FTM_CV_BASE + ((_channel) * 8))

#घोषणा FTM_PS_MAX		7

#पूर्ण_अगर
