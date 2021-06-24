<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fsl_asrc.h - Freescale ASRC ALSA SoC header file
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * Author: Nicolin Chen <nicoleotsuka@gmail.com>
 */

#अगर_अघोषित _FSL_ASRC_H
#घोषणा _FSL_ASRC_H

#समावेश  "fsl_asrc_common.h"

#घोषणा ASRC_DMA_BUFFER_NUM		2
#घोषणा ASRC_INPUTFIFO_THRESHOLD	32
#घोषणा ASRC_OUTPUTFIFO_THRESHOLD	32
#घोषणा ASRC_FIFO_THRESHOLD_MIN		0
#घोषणा ASRC_FIFO_THRESHOLD_MAX		63
#घोषणा ASRC_DMA_BUFFER_SIZE		(1024 * 48 * 4)
#घोषणा ASRC_MAX_BUFFER_SIZE		(1024 * 48)
#घोषणा ASRC_OUTPUT_LAST_SAMPLE		8

#घोषणा IDEAL_RATIO_RATE		1000000

#घोषणा REG_ASRCTR			0x00
#घोषणा REG_ASRIER			0x04
#घोषणा REG_ASRCNCR			0x0C
#घोषणा REG_ASRCFG			0x10
#घोषणा REG_ASRCSR			0x14

#घोषणा REG_ASRCDR1			0x18
#घोषणा REG_ASRCDR2			0x1C
#घोषणा REG_ASRCDR(i)			((i < 2) ? REG_ASRCDR1 : REG_ASRCDR2)

#घोषणा REG_ASRSTR			0x20
#घोषणा REG_ASRRA			0x24
#घोषणा REG_ASRRB			0x28
#घोषणा REG_ASRRC			0x2C
#घोषणा REG_ASRPM1			0x40
#घोषणा REG_ASRPM2			0x44
#घोषणा REG_ASRPM3			0x48
#घोषणा REG_ASRPM4			0x4C
#घोषणा REG_ASRPM5			0x50
#घोषणा REG_ASRTFR1			0x54
#घोषणा REG_ASRCCR			0x5C

#घोषणा REG_ASRDIA			0x60
#घोषणा REG_ASRDOA			0x64
#घोषणा REG_ASRDIB			0x68
#घोषणा REG_ASRDOB			0x6C
#घोषणा REG_ASRDIC			0x70
#घोषणा REG_ASRDOC			0x74
#घोषणा REG_ASRDI(i)			(REG_ASRDIA + (i << 3))
#घोषणा REG_ASRDO(i)			(REG_ASRDOA + (i << 3))
#घोषणा REG_ASRDx(x, i)			((x) == IN ? REG_ASRDI(i) : REG_ASRDO(i))

#घोषणा REG_ASRIDRHA			0x80
#घोषणा REG_ASRIDRLA			0x84
#घोषणा REG_ASRIDRHB			0x88
#घोषणा REG_ASRIDRLB			0x8C
#घोषणा REG_ASRIDRHC			0x90
#घोषणा REG_ASRIDRLC			0x94
#घोषणा REG_ASRIDRH(i)			(REG_ASRIDRHA + (i << 3))
#घोषणा REG_ASRIDRL(i)			(REG_ASRIDRLA + (i << 3))

#घोषणा REG_ASR76K			0x98
#घोषणा REG_ASR56K			0x9C

#घोषणा REG_ASRMCRA			0xA0
#घोषणा REG_ASRFSTA			0xA4
#घोषणा REG_ASRMCRB			0xA8
#घोषणा REG_ASRFSTB			0xAC
#घोषणा REG_ASRMCRC			0xB0
#घोषणा REG_ASRFSTC			0xB4
#घोषणा REG_ASRMCR(i)			(REG_ASRMCRA + (i << 3))
#घोषणा REG_ASRFST(i)			(REG_ASRFSTA + (i << 3))

#घोषणा REG_ASRMCR1A			0xC0
#घोषणा REG_ASRMCR1B			0xC4
#घोषणा REG_ASRMCR1C			0xC8
#घोषणा REG_ASRMCR1(i)			(REG_ASRMCR1A + (i << 2))


/* REG0 0x00 REG_ASRCTR */
#घोषणा ASRCTR_ATSi_SHIFT(i)		(20 + i)
#घोषणा ASRCTR_ATSi_MASK(i)		(1 << ASRCTR_ATSi_SHIFT(i))
#घोषणा ASRCTR_ATS(i)			(1 << ASRCTR_ATSi_SHIFT(i))
#घोषणा ASRCTR_USRi_SHIFT(i)		(14 + (i << 1))
#घोषणा ASRCTR_USRi_MASK(i)		(1 << ASRCTR_USRi_SHIFT(i))
#घोषणा ASRCTR_USR(i)			(1 << ASRCTR_USRi_SHIFT(i))
#घोषणा ASRCTR_IDRi_SHIFT(i)		(13 + (i << 1))
#घोषणा ASRCTR_IDRi_MASK(i)		(1 << ASRCTR_IDRi_SHIFT(i))
#घोषणा ASRCTR_IDR(i)			(1 << ASRCTR_IDRi_SHIFT(i))
#घोषणा ASRCTR_SRST_SHIFT		4
#घोषणा ASRCTR_SRST_MASK		(1 << ASRCTR_SRST_SHIFT)
#घोषणा ASRCTR_SRST			(1 << ASRCTR_SRST_SHIFT)
#घोषणा ASRCTR_ASRCEi_SHIFT(i)		(1 + i)
#घोषणा ASRCTR_ASRCEi_MASK(i)		(1 << ASRCTR_ASRCEi_SHIFT(i))
#घोषणा ASRCTR_ASRCE(i)			(1 << ASRCTR_ASRCEi_SHIFT(i))
#घोषणा ASRCTR_ASRCEi_ALL_MASK		(0x7 << ASRCTR_ASRCEi_SHIFT(0))
#घोषणा ASRCTR_ASRCEN_SHIFT		0
#घोषणा ASRCTR_ASRCEN_MASK		(1 << ASRCTR_ASRCEN_SHIFT)
#घोषणा ASRCTR_ASRCEN			(1 << ASRCTR_ASRCEN_SHIFT)

/* REG1 0x04 REG_ASRIER */
#घोषणा ASRIER_AFPWE_SHIFT		7
#घोषणा ASRIER_AFPWE_MASK		(1 << ASRIER_AFPWE_SHIFT)
#घोषणा ASRIER_AFPWE			(1 << ASRIER_AFPWE_SHIFT)
#घोषणा ASRIER_AOLIE_SHIFT		6
#घोषणा ASRIER_AOLIE_MASK		(1 << ASRIER_AOLIE_SHIFT)
#घोषणा ASRIER_AOLIE			(1 << ASRIER_AOLIE_SHIFT)
#घोषणा ASRIER_ADOEi_SHIFT(i)		(3 + i)
#घोषणा ASRIER_ADOEi_MASK(i)		(1 << ASRIER_ADOEi_SHIFT(i))
#घोषणा ASRIER_ADOE(i)			(1 << ASRIER_ADOEi_SHIFT(i))
#घोषणा ASRIER_ADIEi_SHIFT(i)		(0 + i)
#घोषणा ASRIER_ADIEi_MASK(i)		(1 << ASRIER_ADIEi_SHIFT(i))
#घोषणा ASRIER_ADIE(i)			(1 << ASRIER_ADIEi_SHIFT(i))

/* REG2 0x0C REG_ASRCNCR */
#घोषणा ASRCNCR_ANCi_SHIFT(i, b)	(b * i)
#घोषणा ASRCNCR_ANCi_MASK(i, b)		(((1 << b) - 1) << ASRCNCR_ANCi_SHIFT(i, b))
#घोषणा ASRCNCR_ANCi(i, v, b)		((v << ASRCNCR_ANCi_SHIFT(i, b)) & ASRCNCR_ANCi_MASK(i, b))

/* REG3 0x10 REG_ASRCFG */
#घोषणा ASRCFG_INIRQi_SHIFT(i)		(21 + i)
#घोषणा ASRCFG_INIRQi_MASK(i)		(1 << ASRCFG_INIRQi_SHIFT(i))
#घोषणा ASRCFG_INIRQi			(1 << ASRCFG_INIRQi_SHIFT(i))
#घोषणा ASRCFG_NDPRi_SHIFT(i)		(18 + i)
#घोषणा ASRCFG_NDPRi_MASK(i)		(1 << ASRCFG_NDPRi_SHIFT(i))
#घोषणा ASRCFG_NDPRi_ALL_SHIFT		18
#घोषणा ASRCFG_NDPRi_ALL_MASK		(7 << ASRCFG_NDPRi_ALL_SHIFT)
#घोषणा ASRCFG_NDPRi			(1 << ASRCFG_NDPRi_SHIFT(i))
#घोषणा ASRCFG_POSTMODi_SHIFT(i)	(8 + (i << 2))
#घोषणा ASRCFG_POSTMODi_WIDTH		2
#घोषणा ASRCFG_POSTMODi_MASK(i)		(((1 << ASRCFG_POSTMODi_WIDTH) - 1) << ASRCFG_POSTMODi_SHIFT(i))
#घोषणा ASRCFG_POSTMODi_ALL_MASK	(ASRCFG_POSTMODi_MASK(0) | ASRCFG_POSTMODi_MASK(1) | ASRCFG_POSTMODi_MASK(2))
#घोषणा ASRCFG_POSTMOD(i, v)		((v) << ASRCFG_POSTMODi_SHIFT(i))
#घोषणा ASRCFG_POSTMODi_UP(i)		(0 << ASRCFG_POSTMODi_SHIFT(i))
#घोषणा ASRCFG_POSTMODi_DCON(i)		(1 << ASRCFG_POSTMODi_SHIFT(i))
#घोषणा ASRCFG_POSTMODi_DOWN(i)		(2 << ASRCFG_POSTMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_SHIFT(i)		(6 + (i << 2))
#घोषणा ASRCFG_PREMODi_WIDTH		2
#घोषणा ASRCFG_PREMODi_MASK(i)		(((1 << ASRCFG_PREMODi_WIDTH) - 1) << ASRCFG_PREMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_ALL_MASK		(ASRCFG_PREMODi_MASK(0) | ASRCFG_PREMODi_MASK(1) | ASRCFG_PREMODi_MASK(2))
#घोषणा ASRCFG_PREMOD(i, v)		((v) << ASRCFG_PREMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_UP(i)		(0 << ASRCFG_PREMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_DCON(i)		(1 << ASRCFG_PREMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_DOWN(i)		(2 << ASRCFG_PREMODi_SHIFT(i))
#घोषणा ASRCFG_PREMODi_BYPASS(i)	(3 << ASRCFG_PREMODi_SHIFT(i))

/* REG4 0x14 REG_ASRCSR */
#घोषणा ASRCSR_AxCSi_WIDTH		4
#घोषणा ASRCSR_AxCSi_MASK		((1 << ASRCSR_AxCSi_WIDTH) - 1)
#घोषणा ASRCSR_AOCSi_SHIFT(i)		(12 + (i << 2))
#घोषणा ASRCSR_AOCSi_MASK(i)		(((1 << ASRCSR_AxCSi_WIDTH) - 1) << ASRCSR_AOCSi_SHIFT(i))
#घोषणा ASRCSR_AOCS(i, v)		((v) << ASRCSR_AOCSi_SHIFT(i))
#घोषणा ASRCSR_AICSi_SHIFT(i)		(i << 2)
#घोषणा ASRCSR_AICSi_MASK(i)		(((1 << ASRCSR_AxCSi_WIDTH) - 1) << ASRCSR_AICSi_SHIFT(i))
#घोषणा ASRCSR_AICS(i, v)		((v) << ASRCSR_AICSi_SHIFT(i))

/* REG5&6 0x18 & 0x1C REG_ASRCDR1 & ASRCDR2 */
#घोषणा ASRCDRi_AxCPi_WIDTH		3
#घोषणा ASRCDRi_AICPi_SHIFT(i)		(0 + (i % 2) * 6)
#घोषणा ASRCDRi_AICPi_MASK(i)		(((1 << ASRCDRi_AxCPi_WIDTH) - 1) << ASRCDRi_AICPi_SHIFT(i))
#घोषणा ASRCDRi_AICP(i, v)		((v) << ASRCDRi_AICPi_SHIFT(i))
#घोषणा ASRCDRi_AICDi_SHIFT(i)		(3 + (i % 2) * 6)
#घोषणा ASRCDRi_AICDi_MASK(i)		(((1 << ASRCDRi_AxCPi_WIDTH) - 1) << ASRCDRi_AICDi_SHIFT(i))
#घोषणा ASRCDRi_AICD(i, v)		((v) << ASRCDRi_AICDi_SHIFT(i))
#घोषणा ASRCDRi_AOCPi_SHIFT(i)		((i < 2) ? 12 + i * 6 : 6)
#घोषणा ASRCDRi_AOCPi_MASK(i)		(((1 << ASRCDRi_AxCPi_WIDTH) - 1) << ASRCDRi_AOCPi_SHIFT(i))
#घोषणा ASRCDRi_AOCP(i, v)		((v) << ASRCDRi_AOCPi_SHIFT(i))
#घोषणा ASRCDRi_AOCDi_SHIFT(i)		((i < 2) ? 15 + i * 6 : 9)
#घोषणा ASRCDRi_AOCDi_MASK(i)		(((1 << ASRCDRi_AxCPi_WIDTH) - 1) << ASRCDRi_AOCDi_SHIFT(i))
#घोषणा ASRCDRi_AOCD(i, v)		((v) << ASRCDRi_AOCDi_SHIFT(i))

/* REG7 0x20 REG_ASRSTR */
#घोषणा ASRSTR_DSLCNT_SHIFT		21
#घोषणा ASRSTR_DSLCNT_MASK		(1 << ASRSTR_DSLCNT_SHIFT)
#घोषणा ASRSTR_DSLCNT			(1 << ASRSTR_DSLCNT_SHIFT)
#घोषणा ASRSTR_ATQOL_SHIFT		20
#घोषणा ASRSTR_ATQOL_MASK		(1 << ASRSTR_ATQOL_SHIFT)
#घोषणा ASRSTR_ATQOL			(1 << ASRSTR_ATQOL_SHIFT)
#घोषणा ASRSTR_AOOLi_SHIFT(i)		(17 + i)
#घोषणा ASRSTR_AOOLi_MASK(i)		(1 << ASRSTR_AOOLi_SHIFT(i))
#घोषणा ASRSTR_AOOL(i)			(1 << ASRSTR_AOOLi_SHIFT(i))
#घोषणा ASRSTR_AIOLi_SHIFT(i)		(14 + i)
#घोषणा ASRSTR_AIOLi_MASK(i)		(1 << ASRSTR_AIOLi_SHIFT(i))
#घोषणा ASRSTR_AIOL(i)			(1 << ASRSTR_AIOLi_SHIFT(i))
#घोषणा ASRSTR_AODOi_SHIFT(i)		(11 + i)
#घोषणा ASRSTR_AODOi_MASK(i)		(1 << ASRSTR_AODOi_SHIFT(i))
#घोषणा ASRSTR_AODO(i)			(1 << ASRSTR_AODOi_SHIFT(i))
#घोषणा ASRSTR_AIDUi_SHIFT(i)		(8 + i)
#घोषणा ASRSTR_AIDUi_MASK(i)		(1 << ASRSTR_AIDUi_SHIFT(i))
#घोषणा ASRSTR_AIDU(i)			(1 << ASRSTR_AIDUi_SHIFT(i))
#घोषणा ASRSTR_FPWT_SHIFT		7
#घोषणा ASRSTR_FPWT_MASK		(1 << ASRSTR_FPWT_SHIFT)
#घोषणा ASRSTR_FPWT			(1 << ASRSTR_FPWT_SHIFT)
#घोषणा ASRSTR_AOLE_SHIFT		6
#घोषणा ASRSTR_AOLE_MASK		(1 << ASRSTR_AOLE_SHIFT)
#घोषणा ASRSTR_AOLE			(1 << ASRSTR_AOLE_SHIFT)
#घोषणा ASRSTR_AODEi_SHIFT(i)		(3 + i)
#घोषणा ASRSTR_AODFi_MASK(i)		(1 << ASRSTR_AODEi_SHIFT(i))
#घोषणा ASRSTR_AODF(i)			(1 << ASRSTR_AODEi_SHIFT(i))
#घोषणा ASRSTR_AIDEi_SHIFT(i)		(0 + i)
#घोषणा ASRSTR_AIDEi_MASK(i)		(1 << ASRSTR_AIDEi_SHIFT(i))
#घोषणा ASRSTR_AIDE(i)			(1 << ASRSTR_AIDEi_SHIFT(i))

/* REG10 0x54 REG_ASRTFR1 */
#घोषणा ASRTFR1_TF_BASE_WIDTH		7
#घोषणा ASRTFR1_TF_BASE_SHIFT		6
#घोषणा ASRTFR1_TF_BASE_MASK		(((1 << ASRTFR1_TF_BASE_WIDTH) - 1) << ASRTFR1_TF_BASE_SHIFT)
#घोषणा ASRTFR1_TF_BASE(i)		((i) << ASRTFR1_TF_BASE_SHIFT)

/*
 * REG22 0xA0 REG_ASRMCRA
 * REG24 0xA8 REG_ASRMCRB
 * REG26 0xB0 REG_ASRMCRC
 */
#घोषणा ASRMCRi_ZEROBUFi_SHIFT		23
#घोषणा ASRMCRi_ZEROBUFi_MASK		(1 << ASRMCRi_ZEROBUFi_SHIFT)
#घोषणा ASRMCRi_ZEROBUFi		(1 << ASRMCRi_ZEROBUFi_SHIFT)
#घोषणा ASRMCRi_EXTTHRSHi_SHIFT		22
#घोषणा ASRMCRi_EXTTHRSHi_MASK		(1 << ASRMCRi_EXTTHRSHi_SHIFT)
#घोषणा ASRMCRi_EXTTHRSHi		(1 << ASRMCRi_EXTTHRSHi_SHIFT)
#घोषणा ASRMCRi_BUFSTALLi_SHIFT		21
#घोषणा ASRMCRi_BUFSTALLi_MASK		(1 << ASRMCRi_BUFSTALLi_SHIFT)
#घोषणा ASRMCRi_BUFSTALLi		(1 << ASRMCRi_BUFSTALLi_SHIFT)
#घोषणा ASRMCRi_BYPASSPOLYi_SHIFT	20
#घोषणा ASRMCRi_BYPASSPOLYi_MASK	(1 << ASRMCRi_BYPASSPOLYi_SHIFT)
#घोषणा ASRMCRi_BYPASSPOLYi		(1 << ASRMCRi_BYPASSPOLYi_SHIFT)
#घोषणा ASRMCRi_OUTFIFO_THRESHOLD_WIDTH	6
#घोषणा ASRMCRi_OUTFIFO_THRESHOLD_SHIFT	12
#घोषणा ASRMCRi_OUTFIFO_THRESHOLD_MASK	(((1 << ASRMCRi_OUTFIFO_THRESHOLD_WIDTH) - 1) << ASRMCRi_OUTFIFO_THRESHOLD_SHIFT)
#घोषणा ASRMCRi_OUTFIFO_THRESHOLD(v)	(((v) << ASRMCRi_OUTFIFO_THRESHOLD_SHIFT) & ASRMCRi_OUTFIFO_THRESHOLD_MASK)
#घोषणा ASRMCRi_RSYNIFi_SHIFT		11
#घोषणा ASRMCRi_RSYNIFi_MASK		(1 << ASRMCRi_RSYNIFi_SHIFT)
#घोषणा ASRMCRi_RSYNIFi			(1 << ASRMCRi_RSYNIFi_SHIFT)
#घोषणा ASRMCRi_RSYNOFi_SHIFT		10
#घोषणा ASRMCRi_RSYNOFi_MASK		(1 << ASRMCRi_RSYNOFi_SHIFT)
#घोषणा ASRMCRi_RSYNOFi			(1 << ASRMCRi_RSYNOFi_SHIFT)
#घोषणा ASRMCRi_INFIFO_THRESHOLD_WIDTH	6
#घोषणा ASRMCRi_INFIFO_THRESHOLD_SHIFT	0
#घोषणा ASRMCRi_INFIFO_THRESHOLD_MASK	(((1 << ASRMCRi_INFIFO_THRESHOLD_WIDTH) - 1) << ASRMCRi_INFIFO_THRESHOLD_SHIFT)
#घोषणा ASRMCRi_INFIFO_THRESHOLD(v)	(((v) << ASRMCRi_INFIFO_THRESHOLD_SHIFT) & ASRMCRi_INFIFO_THRESHOLD_MASK)

/*
 * REG23 0xA4 REG_ASRFSTA
 * REG25 0xAC REG_ASRFSTB
 * REG27 0xB4 REG_ASRFSTC
 */
#घोषणा ASRFSTi_OAFi_SHIFT		23
#घोषणा ASRFSTi_OAFi_MASK		(1 << ASRFSTi_OAFi_SHIFT)
#घोषणा ASRFSTi_OAFi			(1 << ASRFSTi_OAFi_SHIFT)
#घोषणा ASRFSTi_OUTPUT_FIFO_WIDTH	7
#घोषणा ASRFSTi_OUTPUT_FIFO_SHIFT	12
#घोषणा ASRFSTi_OUTPUT_FIFO_MASK	(((1 << ASRFSTi_OUTPUT_FIFO_WIDTH) - 1) << ASRFSTi_OUTPUT_FIFO_SHIFT)
#घोषणा ASRFSTi_IAEi_SHIFT		11
#घोषणा ASRFSTi_IAEi_MASK		(1 << ASRFSTi_IAEi_SHIFT)
#घोषणा ASRFSTi_IAEi			(1 << ASRFSTi_IAEi_SHIFT)
#घोषणा ASRFSTi_INPUT_FIFO_WIDTH	7
#घोषणा ASRFSTi_INPUT_FIFO_SHIFT	0
#घोषणा ASRFSTi_INPUT_FIFO_MASK		((1 << ASRFSTi_INPUT_FIFO_WIDTH) - 1)

/* REG28 0xC0 & 0xC4 & 0xC8 REG_ASRMCR1i */
#घोषणा ASRMCR1i_IWD_WIDTH		3
#घोषणा ASRMCR1i_IWD_SHIFT		9
#घोषणा ASRMCR1i_IWD_MASK		(((1 << ASRMCR1i_IWD_WIDTH) - 1) << ASRMCR1i_IWD_SHIFT)
#घोषणा ASRMCR1i_IWD(v)			((v) << ASRMCR1i_IWD_SHIFT)
#घोषणा ASRMCR1i_IMSB_SHIFT		8
#घोषणा ASRMCR1i_IMSB_MASK		(1 << ASRMCR1i_IMSB_SHIFT)
#घोषणा ASRMCR1i_IMSB_MSB		(1 << ASRMCR1i_IMSB_SHIFT)
#घोषणा ASRMCR1i_IMSB_LSB		(0 << ASRMCR1i_IMSB_SHIFT)
#घोषणा ASRMCR1i_OMSB_SHIFT		2
#घोषणा ASRMCR1i_OMSB_MASK		(1 << ASRMCR1i_OMSB_SHIFT)
#घोषणा ASRMCR1i_OMSB_MSB		(1 << ASRMCR1i_OMSB_SHIFT)
#घोषणा ASRMCR1i_OMSB_LSB		(0 << ASRMCR1i_OMSB_SHIFT)
#घोषणा ASRMCR1i_OSGN_SHIFT		1
#घोषणा ASRMCR1i_OSGN_MASK		(1 << ASRMCR1i_OSGN_SHIFT)
#घोषणा ASRMCR1i_OSGN			(1 << ASRMCR1i_OSGN_SHIFT)
#घोषणा ASRMCR1i_OW16_SHIFT		0
#घोषणा ASRMCR1i_OW16_MASK		(1 << ASRMCR1i_OW16_SHIFT)
#घोषणा ASRMCR1i_OW16(v)		((v) << ASRMCR1i_OW16_SHIFT)

#घोषणा ASRC_PAIR_MAX_NUM	(ASRC_PAIR_C + 1)

क्रमागत asrc_inclk अणु
	INCLK_NONE = 0x03,
	INCLK_ESAI_RX = 0x00,
	INCLK_SSI1_RX = 0x01,
	INCLK_SSI2_RX = 0x02,
	INCLK_SSI3_RX = 0x07,
	INCLK_SPDIF_RX = 0x04,
	INCLK_MLB_CLK = 0x05,
	INCLK_PAD = 0x06,
	INCLK_ESAI_TX = 0x08,
	INCLK_SSI1_TX = 0x09,
	INCLK_SSI2_TX = 0x0a,
	INCLK_SSI3_TX = 0x0b,
	INCLK_SPDIF_TX = 0x0c,
	INCLK_ASRCK1_CLK = 0x0f,

	/* घड़ीs क्रम imx8 */
	INCLK_AUD_PLL_DIV_CLK0 = 0x10,
	INCLK_AUD_PLL_DIV_CLK1 = 0x11,
	INCLK_AUD_CLK0         = 0x12,
	INCLK_AUD_CLK1         = 0x13,
	INCLK_ESAI0_RX_CLK     = 0x14,
	INCLK_ESAI0_TX_CLK     = 0x15,
	INCLK_SPDIF0_RX        = 0x16,
	INCLK_SPDIF1_RX        = 0x17,
	INCLK_SAI0_RX_BCLK     = 0x18,
	INCLK_SAI0_TX_BCLK     = 0x19,
	INCLK_SAI1_RX_BCLK     = 0x1a,
	INCLK_SAI1_TX_BCLK     = 0x1b,
	INCLK_SAI2_RX_BCLK     = 0x1c,
	INCLK_SAI3_RX_BCLK     = 0x1d,
	INCLK_ASRC0_MUX_CLK    = 0x1e,

	INCLK_ESAI1_RX_CLK     = 0x20,
	INCLK_ESAI1_TX_CLK     = 0x21,
	INCLK_SAI6_TX_BCLK     = 0x22,
	INCLK_HDMI_RX_SAI0_RX_BCLK     = 0x24,
	INCLK_HDMI_TX_SAI0_TX_BCLK     = 0x25,
पूर्ण;

क्रमागत asrc_outclk अणु
	OUTCLK_NONE = 0x03,
	OUTCLK_ESAI_TX = 0x00,
	OUTCLK_SSI1_TX = 0x01,
	OUTCLK_SSI2_TX = 0x02,
	OUTCLK_SSI3_TX = 0x07,
	OUTCLK_SPDIF_TX = 0x04,
	OUTCLK_MLB_CLK = 0x05,
	OUTCLK_PAD = 0x06,
	OUTCLK_ESAI_RX = 0x08,
	OUTCLK_SSI1_RX = 0x09,
	OUTCLK_SSI2_RX = 0x0a,
	OUTCLK_SSI3_RX = 0x0b,
	OUTCLK_SPDIF_RX = 0x0c,
	OUTCLK_ASRCK1_CLK = 0x0f,

	/* घड़ीs क्रम imx8 */
	OUTCLK_AUD_PLL_DIV_CLK0 = 0x10,
	OUTCLK_AUD_PLL_DIV_CLK1 = 0x11,
	OUTCLK_AUD_CLK0         = 0x12,
	OUTCLK_AUD_CLK1         = 0x13,
	OUTCLK_ESAI0_RX_CLK     = 0x14,
	OUTCLK_ESAI0_TX_CLK     = 0x15,
	OUTCLK_SPDIF0_RX        = 0x16,
	OUTCLK_SPDIF1_RX        = 0x17,
	OUTCLK_SAI0_RX_BCLK     = 0x18,
	OUTCLK_SAI0_TX_BCLK     = 0x19,
	OUTCLK_SAI1_RX_BCLK     = 0x1a,
	OUTCLK_SAI1_TX_BCLK     = 0x1b,
	OUTCLK_SAI2_RX_BCLK     = 0x1c,
	OUTCLK_SAI3_RX_BCLK     = 0x1d,
	OUTCLK_ASRCO_MUX_CLK    = 0x1e,

	OUTCLK_ESAI1_RX_CLK     = 0x20,
	OUTCLK_ESAI1_TX_CLK     = 0x21,
	OUTCLK_SAI6_TX_BCLK     = 0x22,
	OUTCLK_HDMI_RX_SAI0_RX_BCLK     = 0x24,
	OUTCLK_HDMI_TX_SAI0_TX_BCLK     = 0x25,
पूर्ण;

#घोषणा ASRC_CLK_MAX_NUM	16
#घोषणा ASRC_CLK_MAP_LEN	0x30

क्रमागत asrc_word_width अणु
	ASRC_WIDTH_24_BIT = 0,
	ASRC_WIDTH_16_BIT = 1,
	ASRC_WIDTH_8_BIT = 2,
पूर्ण;

काष्ठा asrc_config अणु
	क्रमागत asrc_pair_index pair;
	अचिन्हित पूर्णांक channel_num;
	अचिन्हित पूर्णांक buffer_num;
	अचिन्हित पूर्णांक dma_buffer_size;
	अचिन्हित पूर्णांक input_sample_rate;
	अचिन्हित पूर्णांक output_sample_rate;
	snd_pcm_क्रमmat_t input_क्रमmat;
	snd_pcm_क्रमmat_t output_क्रमmat;
	क्रमागत asrc_inclk inclk;
	क्रमागत asrc_outclk outclk;
पूर्ण;

काष्ठा asrc_req अणु
	अचिन्हित पूर्णांक chn_num;
	क्रमागत asrc_pair_index index;
पूर्ण;

काष्ठा asrc_querybuf अणु
	अचिन्हित पूर्णांक buffer_index;
	अचिन्हित पूर्णांक input_length;
	अचिन्हित पूर्णांक output_length;
	अचिन्हित दीर्घ input_offset;
	अचिन्हित दीर्घ output_offset;
पूर्ण;

काष्ठा asrc_convert_buffer अणु
	व्योम *input_buffer_vaddr;
	व्योम *output_buffer_vaddr;
	अचिन्हित पूर्णांक input_buffer_length;
	अचिन्हित पूर्णांक output_buffer_length;
पूर्ण;

काष्ठा asrc_status_flags अणु
	क्रमागत asrc_pair_index index;
	अचिन्हित पूर्णांक overload_error;
पूर्ण;

क्रमागत asrc_error_status अणु
	ASRC_TASK_Q_OVERLOAD		= 0x01,
	ASRC_OUTPUT_TASK_OVERLOAD	= 0x02,
	ASRC_INPUT_TASK_OVERLOAD	= 0x04,
	ASRC_OUTPUT_BUFFER_OVERFLOW	= 0x08,
	ASRC_INPUT_BUFFER_UNDERRUN	= 0x10,
पूर्ण;

काष्ठा dma_block अणु
	dma_addr_t dma_paddr;
	व्योम *dma_vaddr;
	अचिन्हित पूर्णांक length;
पूर्ण;

/**
 * fsl_asrc_soc_data: soc specअगरic data
 *
 * @use_edma: using edma as dma device or not
 * @channel_bits: width of ASRCNCR रेजिस्टर क्रम each pair
 */
काष्ठा fsl_asrc_soc_data अणु
	bool use_edma;
	अचिन्हित पूर्णांक channel_bits;
पूर्ण;

/**
 * fsl_asrc_pair_priv: ASRC Pair निजी data
 *
 * @config: configuration profile
 */
काष्ठा fsl_asrc_pair_priv अणु
	काष्ठा asrc_config *config;
पूर्ण;

/**
 * fsl_asrc_priv: ASRC निजी data
 *
 * @asrck_clk: घड़ी sources to driver ASRC पूर्णांकernal logic
 * @soc: soc specअगरic data
 * @clk_map: घड़ी map क्रम input/output घड़ी
 * @regcache_cfg: store रेजिस्टर value of REG_ASRCFG
 */
काष्ठा fsl_asrc_priv अणु
	काष्ठा clk *asrck_clk[ASRC_CLK_MAX_NUM];
	स्थिर काष्ठा fsl_asrc_soc_data *soc;
	अचिन्हित अक्षर *clk_map[2];

	u32 regcache_cfg;
पूर्ण;

#पूर्ण_अगर /* _FSL_ASRC_H */
