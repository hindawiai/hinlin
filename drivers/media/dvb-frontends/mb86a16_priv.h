<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Fujitsu MB86A16 DVB-S/DSS DC Receiver driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MB86A16_PRIV_H
#घोषणा __MB86A16_PRIV_H

#घोषणा MB86A16_TSOUT		0x00
#घोषणा MB86A16_TSOUT_HIZSEL	(0x01 << 5)
#घोषणा MB86A16_TSOUT_HIZCNTI	(0x01 << 4)
#घोषणा MB86A16_TSOUT_MODE	(0x01 << 3)
#घोषणा MB86A16_TSOUT_ORDER	(0x01 << 2)
#घोषणा MB86A16_TSOUT_ERROR	(0x01 << 1)
#घोषणा Mb86A16_TSOUT_EDGE	(0x01 << 0)

#घोषणा MB86A16_FEC		0x01
#घोषणा MB86A16_FEC_FSYNC	(0x01 << 5)
#घोषणा MB86A16_FEC_PCKB8	(0x01 << 4)
#घोषणा MB86A16_FEC_DVDS	(0x01 << 3)
#घोषणा MB86A16_FEC_EREN	(0x01 << 2)
#घोषणा Mb86A16_FEC_RSEN	(0x01 << 1)
#घोषणा MB86A16_FEC_DIEN	(0x01 << 0)

#घोषणा MB86A16_AGC		0x02
#घोषणा MB86A16_AGC_AGMD	(0x01 << 6)
#घोषणा MB86A16_AGC_AGCW	(0x0f << 2)
#घोषणा MB86A16_AGC_AGCP	(0x01 << 1)
#घोषणा MB86A16_AGC_AGCR	(0x01 << 0)

#घोषणा MB86A16_SRATE1		0x03
#घोषणा MB86A16_SRATE1_DECI	(0x07 << 2)
#घोषणा MB86A16_SRATE1_CSEL	(0x01 << 1)
#घोषणा MB86A16_SRATE1_RSEL	(0x01 << 0)

#घोषणा MB86A16_SRATE2		0x04
#घोषणा MB86A16_SRATE2_STOFSL	(0xff << 0)

#घोषणा MB86A16_SRATE3		0x05
#घोषणा MB86A16_SRATE2_STOFSH	(0xff << 0)

#घोषणा MB86A16_VITERBI		0x06
#घोषणा MB86A16_FRAMESYNC	0x07
#घोषणा MB86A16_CRLFILTCOEF1	0x08
#घोषणा MB86A16_CRLFILTCOEF2	0x09
#घोषणा MB86A16_STRFILTCOEF1	0x0a
#घोषणा MB86A16_STRFILTCOEF2	0x0b
#घोषणा MB86A16_RESET		0x0c
#घोषणा MB86A16_STATUS		0x0d
#घोषणा MB86A16_AFCML		0x0e
#घोषणा MB86A16_AFCMH		0x0f
#घोषणा MB86A16_BERMON		0x10
#घोषणा MB86A16_BERTAB		0x11
#घोषणा MB86A16_BERLSB		0x12
#घोषणा MB86A16_BERMID		0x13
#घोषणा MB86A16_BERMSB		0x14
#घोषणा MB86A16_AGCM		0x15

#घोषणा MB86A16_DCC1		0x16
#घोषणा MB86A16_DCC1_DISTA	(0x01 << 7)
#घोषणा MB86A16_DCC1_PRTY	(0x01 << 6)
#घोषणा MB86A16_DCC1_CTOE	(0x01 << 5)
#घोषणा MB86A16_DCC1_TBEN	(0x01 << 4)
#घोषणा MB86A16_DCC1_TBO	(0x01 << 3)
#घोषणा MB86A16_DCC1_NUM	(0x07 << 0)

#घोषणा MB86A16_DCC2		0x17
#घोषणा MB86A16_DCC2_DCBST	(0x01 << 0)

#घोषणा MB86A16_DCC3		0x18
#घोषणा MB86A16_DCC3_CODE0	(0xff << 0)

#घोषणा MB86A16_DCC4		0x19
#घोषणा MB86A16_DCC4_CODE1	(0xff << 0)

#घोषणा MB86A16_DCC5		0x1a
#घोषणा MB86A16_DCC5_CODE2	(0xff << 0)

#घोषणा MB86A16_DCC6		0x1b
#घोषणा MB86A16_DCC6_CODE3	(0xff << 0)

#घोषणा MB86A16_DCC7		0x1c
#घोषणा MB86A16_DCC7_CODE4	(0xff << 0)

#घोषणा MB86A16_DCC8		0x1d
#घोषणा MB86A16_DCC8_CODE5	(0xff << 0)

#घोषणा MB86A16_DCCOUT		0x1e
#घोषणा MB86A16_DCCOUT_DISEN	(0x01 << 0)

#घोषणा MB86A16_TONEOUT1	0x1f
#घोषणा MB86A16_TONE_TDIVL	(0xff << 0)

#घोषणा MB86A16_TONEOUT2	0x20
#घोषणा MB86A16_TONE_TMD	(0x03 << 2)
#घोषणा MB86A16_TONE_TDIVH	(0x03 << 0)

#घोषणा MB86A16_FREQ1		0x21
#घोषणा MB86A16_FREQ2		0x22
#घोषणा MB86A16_FREQ3		0x23
#घोषणा MB86A16_FREQ4		0x24
#घोषणा MB86A16_FREQSET		0x25
#घोषणा MB86A16_CNM		0x26
#घोषणा MB86A16_PORT0		0x27
#घोषणा MB86A16_PORT1		0x28
#घोषणा MB86A16_DRCFILT		0x29
#घोषणा MB86A16_AFC		0x2a
#घोषणा MB86A16_AFCEXL		0x2b
#घोषणा MB86A16_AFCEXH		0x2c
#घोषणा MB86A16_DAGC		0x2d
#घोषणा MB86A16_SEQMODE		0x32
#घोषणा MB86A16_S0S1T		0x33
#घोषणा MB86A16_S2S3T		0x34
#घोषणा MB86A16_S4S5T		0x35
#घोषणा MB86A16_CNTMR		0x36
#घोषणा MB86A16_SIG1		0x37
#घोषणा MB86A16_SIG2		0x38
#घोषणा MB86A16_VIMAG		0x39
#घोषणा MB86A16_VISET1		0x3a
#घोषणा MB86A16_VISET2		0x3b
#घोषणा MB86A16_VISET3		0x3c
#घोषणा MB86A16_FAGCS1		0x3d
#घोषणा MB86A16_FAGCS2		0x3e
#घोषणा MB86A16_FAGCS3		0x3f
#घोषणा MB86A16_FAGCS4		0x40
#घोषणा MB86A16_FAGCS5		0x41
#घोषणा MB86A16_FAGCS6		0x42
#घोषणा MB86A16_CRM		0x43
#घोषणा MB86A16_STRM		0x44
#घोषणा MB86A16_DAGCML		0x45
#घोषणा MB86A16_DAGCMH		0x46
#घोषणा MB86A16_QPSKTST		0x49
#घोषणा MB86A16_DISTMON		0x52
#घोषणा MB86A16_VERSION		0x7f

#पूर्ण_अगर /* __MB86A16_PRIV_H */
