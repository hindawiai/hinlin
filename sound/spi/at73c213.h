<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम the AT73C213 16-bit stereo DAC on Aपंचांगel ATSTK1000
 *
 * Copyright (C) 2006 - 2007 Aपंचांगel Corporation
 */

#अगर_अघोषित _SND_AT73C213_H
#घोषणा _SND_AT73C213_H

/* DAC control रेजिस्टर */
#घोषणा DAC_CTRL		0x00
#घोषणा DAC_CTRL_ONPADRV	7
#घोषणा DAC_CTRL_ONAUXIN	6
#घोषणा DAC_CTRL_ONDACR		5
#घोषणा DAC_CTRL_ONDACL		4
#घोषणा DAC_CTRL_ONLNOR		3
#घोषणा DAC_CTRL_ONLNOL		2
#घोषणा DAC_CTRL_ONLNIR		1
#घोषणा DAC_CTRL_ONLNIL		0

/* DAC left line in gain रेजिस्टर */
#घोषणा DAC_LLIG		0x01
#घोषणा DAC_LLIG_LLIG		0

/* DAC right line in gain रेजिस्टर */
#घोषणा DAC_RLIG		0x02
#घोषणा DAC_RLIG_RLIG		0

/* DAC Left Master Playback Gain Register */
#घोषणा DAC_LMPG		0x03
#घोषणा DAC_LMPG_LMPG		0

/* DAC Right Master Playback Gain Register */
#घोषणा DAC_RMPG		0x04
#घोषणा DAC_RMPG_RMPG		0

/* DAC Left Line Out Gain Register */
#घोषणा DAC_LLOG		0x05
#घोषणा DAC_LLOG_LLOG		0

/* DAC Right Line Out Gain Register */
#घोषणा DAC_RLOG		0x06
#घोषणा DAC_RLOG_RLOG		0

/* DAC Output Level Control Register */
#घोषणा DAC_OLC			0x07
#घोषणा DAC_OLC_RSHORT		7
#घोषणा DAC_OLC_ROLC		4
#घोषणा DAC_OLC_LSHORT		3
#घोषणा DAC_OLC_LOLC		0

/* DAC Mixer Control Register */
#घोषणा DAC_MC			0x08
#घोषणा DAC_MC_INVR		5
#घोषणा DAC_MC_INVL		4
#घोषणा DAC_MC_RMSMIN2		3
#घोषणा DAC_MC_RMSMIN1		2
#घोषणा DAC_MC_LMSMIN2		1
#घोषणा DAC_MC_LMSMIN1		0

/* DAC Clock and Sampling Frequency Control Register */
#घोषणा DAC_CSFC		0x09
#घोषणा DAC_CSFC_OVRSEL		4

/* DAC Miscellaneous Register */
#घोषणा DAC_MISC		0x0A
#घोषणा DAC_MISC_VCMCAPSEL	7
#घोषणा DAC_MISC_DINTSEL	4
#घोषणा DAC_MISC_DITHEN		3
#घोषणा DAC_MISC_DEEMPEN	2
#घोषणा DAC_MISC_NBITS		0

/* DAC Preअक्षरge Control Register */
#घोषणा DAC_PRECH		0x0C
#घोषणा DAC_PRECH_PRCHGPDRV	7
#घोषणा DAC_PRECH_PRCHGAUX1	6
#घोषणा DAC_PRECH_PRCHGLNOR	5
#घोषणा DAC_PRECH_PRCHGLNOL	4
#घोषणा DAC_PRECH_PRCHGLNIR	3
#घोषणा DAC_PRECH_PRCHGLNIL	2
#घोषणा DAC_PRECH_PRCHG		1
#घोषणा DAC_PRECH_ONMSTR	0

/* DAC Auxiliary Input Gain Control Register */
#घोषणा DAC_AUXG		0x0D
#घोषणा DAC_AUXG_AUXG		0

/* DAC Reset Register */
#घोषणा DAC_RST			0x10
#घोषणा DAC_RST_RESMASK		2
#घोषणा DAC_RST_RESFILZ		1
#घोषणा DAC_RST_RSTZ		0

/* Power Amplअगरier Control Register */
#घोषणा PA_CTRL			0x11
#घोषणा PA_CTRL_APAON		6
#घोषणा PA_CTRL_APAPRECH	5
#घोषणा PA_CTRL_APALP		4
#घोषणा PA_CTRL_APAGAIN		0

#पूर्ण_अगर /* _SND_AT73C213_H */
