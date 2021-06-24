<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश "hw.h"
#समावेश "ar9003_phy.h"
#समावेश "ar9003_eeprom.h"
#समावेश "ar9003_mci.h"

#घोषणा COMP_HDR_LEN 4
#घोषणा COMP_CKSUM_LEN 2

#घोषणा LE16(x) cpu_to_le16(x)
#घोषणा LE32(x) cpu_to_le32(x)

/* Local defines to distinguish between extension and control CTL's */
#घोषणा EXT_ADDITIVE (0x8000)
#घोषणा CTL_11A_EXT (CTL_11A | EXT_ADDITIVE)
#घोषणा CTL_11G_EXT (CTL_11G | EXT_ADDITIVE)
#घोषणा CTL_11B_EXT (CTL_11B | EXT_ADDITIVE)

#घोषणा SUB_NUM_CTL_MODES_AT_5G_40 2    /* excluding HT40, EXT-OFDM */
#घोषणा SUB_NUM_CTL_MODES_AT_2G_40 3    /* excluding HT40, EXT-OFDM, EXT-CCK */

#घोषणा CTL(_tघातer, _flag) ((_tघातer) | ((_flag) << 6))

#घोषणा EEPROM_DATA_LEN_9485	1088

अटल पूर्णांक ar9003_hw_घातer_पूर्णांकerpolate(पूर्णांक32_t x,
				       पूर्णांक32_t *px, पूर्णांक32_t *py, u_पूर्णांक16_t np);

अटल स्थिर काष्ठा ar9300_eeprom ar9300_शेष = अणु
	.eepromVersion = 2,
	.ढाँचाVersion = 2,
	.macAddr = अणु0, 2, 3, 4, 5, 6पूर्ण,
	.custData = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		     0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
	.baseEepHeader = अणु
		.regDmn = अणु LE16(0), LE16(0x1f) पूर्ण,
		.txrxMask =  0x77, /* 4 bits tx and 4 bits rx */
		.opCapFlags = अणु
			.opFlags = AR5416_OPFLAGS_11G | AR5416_OPFLAGS_11A,
			.eepMisc = AR9300_EEPMISC_LITTLE_ENDIAN,
		पूर्ण,
		.rfSilent = 0,
		.blueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes lower byte in eeprom location */
		.pwrTableOffset = AR9300_PWR_TABLE_OFFSET,
		.params_क्रम_tuning_caps = अणु0, 0पूर्ण,
		.featureEnable = 0x0c,
		 /*
		  * bit0 - enable tx temp comp - disabled
		  * bit1 - enable tx volt comp - disabled
		  * bit2 - enable fastClock - enabled
		  * bit3 - enable करोubling - enabled
		  * bit4 - enable पूर्णांकernal regulator - disabled
		  * bit5 - enable pa predistortion - disabled
		  */
		.miscConfiguration = 0, /* bit0 - turn करोwn drivestrength */
		.eepromWriteEnableGpio = 3,
		.wlanDisableGpio = 0,
		.wlanLedGpio = 8,
		.rxBandSelectGpio = 0xff,
		.txrxgain = 0,
		.swreg = 0,
	 पूर्ण,
	.modalHeader2G = अणु
	/* ar9300_modal_eep_header  2g */
		/* 4 idle,t1,t2,b(4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
		.antCtrlCommon2 = LE32(0x22222),

		/*
		 * antCtrlChain[AR9300_MAX_CHAINS]; 6 idle, t, r,
		 * rx1, rx12, b (2 bits each)
		 */
		.antCtrlChain = अणु LE16(0x150), LE16(0x150), LE16(0x150) पूर्ण,

		/*
		 * xatten1DB[AR9300_MAX_CHAINS];  3 xatten1_db
		 * क्रम ar9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम ar9280 (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 36,
		.voltSlope = 0,

		/*
		 * spurChans[OSPREY_EEPROM_MODAL_SPURS]; spur
		 * channels in usual fbin coding क्रमmat
		 */
		.spurChans = अणु0, 0, 0, 0, 0पूर्ण,

		/*
		 * noiseFloorThreshCh[AR9300_MAX_CHAINS]; 3 Check
		 * अगर the रेजिस्टर is per chain
		 */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2c,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0cf0e0e0),
		.papdRateMaskHt40 = LE32(0x6cf0e0e0),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	.base_ext1 = अणु
		.ant_भाग_control = 0,
		.future = अणु0, 0पूर्ण,
		.tempslopextension = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	पूर्ण,
	.calFreqPier2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1),
	 पूर्ण,
	/* ar9300_cal_data_per_freq_op_loop 2g */
	.calPierData2G = अणु
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.calTarget_freqbin_Cck = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2484, 1),
	 पूर्ण,
	.calTarget_freqbin_2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT20 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT40 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTargetPowerCck = अणु
		 /* 1L-5L,5S,11L,11S */
		 अणु अणु36, 36, 36, 36पूर्ण पूर्ण,
		 अणु अणु36, 36, 36, 36पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2G = अणु
		 /* 6-24,36,48,54 */
		 अणु अणु32, 32, 28, 24पूर्ण पूर्ण,
		 अणु अणु32, 32, 28, 24पूर्ण पूर्ण,
		 अणु अणु32, 32, 28, 24पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT20 = अणु
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT40 = अणु
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_2G =  अणु
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	पूर्ण,
	.ctl_freqbin_2G = अणु
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2457, 1),
			FREQ2FBIN(2462, 1)
		पूर्ण,
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,

		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,
		अणु
			FREQ2FBIN(2422, 1),
			FREQ2FBIN(2427, 1),
			FREQ2FBIN(2447, 1),
			FREQ2FBIN(2452, 1)
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(2484, 1),
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
		पूर्ण,

		अणु
			/* Data[9].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[9].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[9].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[10].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[10].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[10].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[11].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[11].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[11].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[11].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण
	 पूर्ण,
	.ctlPowerData_2G = अणु
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 1) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
	 पूर्ण,
	.modalHeader5G = अणु
		/* 4 idle,t1,t2,b (4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2,ra2l2,ra12 */
		.antCtrlCommon2 = LE32(0x22222),
		 /* antCtrlChain 6 idle, t,r,rx1,rx12,b (2 bits each) */
		.antCtrlChain = अणु
			LE16(0x000), LE16(0x000), LE16(0x000),
		पूर्ण,
		 /* xatten1DB 3 xatten1_db क्रम AR9280 (0xa20c/b20c 5:0) */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम merlin (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 68,
		.voltSlope = 0,
		/* spurChans spur channels in usual fbin coding क्रमmat */
		.spurChans = अणु0, 0, 0, 0, 0पूर्ण,
		/* noiseFloorThreshCh Check अगर the रेजिस्टर is per chain */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2d,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0c80c080),
		.papdRateMaskHt40 = LE32(0x0080c080),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	.base_ext2 = अणु
		.tempSlopeLow = 0,
		.tempSlopeHigh = 0,
		.xatten1DBLow = अणु0, 0, 0पूर्ण,
		.xatten1MarginLow = अणु0, 0, 0पूर्ण,
		.xatten1DBHigh = अणु0, 0, 0पूर्ण,
		.xatten1MarginHigh = अणु0, 0, 0पूर्ण
	पूर्ण,
	.calFreqPier5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calPierData5G = अणु
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,

	पूर्ण,
	.calTarget_freqbin_5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT20 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT40 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	 पूर्ण,
	.calTargetPower5G = अणु
		/* 6-24,36,48,54 */
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
		अणु अणु20, 20, 20, 10पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT20 = अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT40 =  अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
		अणु अणु20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.ctlIndex_5G =  अणु
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	पूर्ण,
	.ctl_freqbin_5G =  अणु
		अणु
			/* Data[0].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[0].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[0].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[0].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[0].ctlEdges[4].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[0].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[0].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[0].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,
		अणु
			/* Data[1].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[1].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[1].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[1].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[1].ctlEdges[4].bChannel */ FREQ2FBIN(5520, 0),
			/* Data[1].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[1].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[1].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[2].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[2].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[2].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[2].ctlEdges[3].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[2].ctlEdges[4].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[2].ctlEdges[5].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[2].ctlEdges[6].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[2].ctlEdges[7].bChannel */ FREQ2FBIN(5755, 0)
		पूर्ण,

		अणु
			/* Data[3].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[3].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[3].ctlEdges[2].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[3].ctlEdges[3].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[3].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[3].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[3].ctlEdges[6].bChannel */ 0xFF,
			/* Data[3].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[4].ctlEdges[4].bChannel */ 0xFF,
			/* Data[4].ctlEdges[5].bChannel */ 0xFF,
			/* Data[4].ctlEdges[6].bChannel */ 0xFF,
			/* Data[4].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[5].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[5].ctlEdges[4].bChannel */ FREQ2FBIN(5590, 0),
			/* Data[5].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[5].ctlEdges[6].bChannel */ 0xFF,
			/* Data[5].ctlEdges[7].bChannel */ 0xFF
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[6].ctlEdges[2].bChannel */ FREQ2FBIN(5220, 0),
			/* Data[6].ctlEdges[3].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[6].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[6].ctlEdges[5].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[6].ctlEdges[6].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[6].ctlEdges[7].bChannel */ FREQ2FBIN(5745, 0)
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[7].ctlEdges[4].bChannel */ FREQ2FBIN(5560, 0),
			/* Data[7].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[7].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[7].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[8].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[8].ctlEdges[4].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[8].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[8].ctlEdges[6].bChannel */ FREQ2FBIN(5755, 0),
			/* Data[8].ctlEdges[7].bChannel */ FREQ2FBIN(5795, 0)
		पूर्ण
	 पूर्ण,
	.ctlPowerData_5G = अणु
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 0), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 0), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
			पूर्ण
		पूर्ण,
	 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ar9300_eeprom ar9300_x113 = अणु
	.eepromVersion = 2,
	.ढाँचाVersion = 6,
	.macAddr = अणु0x00, 0x03, 0x7f, 0x0, 0x0, 0x0पूर्ण,
	.custData = अणु"x113-023-f0000"पूर्ण,
	.baseEepHeader = अणु
		.regDmn = अणु LE16(0), LE16(0x1f) पूर्ण,
		.txrxMask =  0x77, /* 4 bits tx and 4 bits rx */
		.opCapFlags = अणु
			.opFlags = AR5416_OPFLAGS_11A,
			.eepMisc = AR9300_EEPMISC_LITTLE_ENDIAN,
		पूर्ण,
		.rfSilent = 0,
		.blueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes lower byte in eeprom location */
		.pwrTableOffset = AR9300_PWR_TABLE_OFFSET,
		.params_क्रम_tuning_caps = अणु0, 0पूर्ण,
		.featureEnable = 0x0d,
		 /*
		  * bit0 - enable tx temp comp - disabled
		  * bit1 - enable tx volt comp - disabled
		  * bit2 - enable fastClock - enabled
		  * bit3 - enable करोubling - enabled
		  * bit4 - enable पूर्णांकernal regulator - disabled
		  * bit5 - enable pa predistortion - disabled
		  */
		.miscConfiguration = 0, /* bit0 - turn करोwn drivestrength */
		.eepromWriteEnableGpio = 6,
		.wlanDisableGpio = 0,
		.wlanLedGpio = 8,
		.rxBandSelectGpio = 0xff,
		.txrxgain = 0x21,
		.swreg = 0,
	 पूर्ण,
	.modalHeader2G = अणु
	/* ar9300_modal_eep_header  2g */
		/* 4 idle,t1,t2,b(4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
		.antCtrlCommon2 = LE32(0x44444),

		/*
		 * antCtrlChain[AR9300_MAX_CHAINS]; 6 idle, t, r,
		 * rx1, rx12, b (2 bits each)
		 */
		.antCtrlChain = अणु LE16(0x150), LE16(0x150), LE16(0x150) पूर्ण,

		/*
		 * xatten1DB[AR9300_MAX_CHAINS];  3 xatten1_db
		 * क्रम ar9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम ar9280 (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 25,
		.voltSlope = 0,

		/*
		 * spurChans[OSPREY_EEPROM_MODAL_SPURS]; spur
		 * channels in usual fbin coding क्रमmat
		 */
		.spurChans = अणुFREQ2FBIN(2464, 1), 0, 0, 0, 0पूर्ण,

		/*
		 * noiseFloorThreshCh[AR9300_MAX_CHAINS]; 3 Check
		 * अगर the रेजिस्टर is per chain
		 */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2c,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0c80c080),
		.papdRateMaskHt40 = LE32(0x0080c080),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	 .base_ext1 = अणु
		.ant_भाग_control = 0,
		.future = अणु0, 0पूर्ण,
		.tempslopextension = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	 पूर्ण,
	.calFreqPier2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1),
	 पूर्ण,
	/* ar9300_cal_data_per_freq_op_loop 2g */
	.calPierData2G = अणु
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.calTarget_freqbin_Cck = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2472, 1),
	 पूर्ण,
	.calTarget_freqbin_2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT20 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT40 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTargetPowerCck = अणु
		 /* 1L-5L,5S,11L,11S */
		 अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
		 अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2G = अणु
		 /* 6-24,36,48,54 */
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT20 = अणु
		अणु अणु32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT40 = अणु
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_2G =  अणु
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	पूर्ण,
	.ctl_freqbin_2G = अणु
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2457, 1),
			FREQ2FBIN(2462, 1)
		पूर्ण,
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,

		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,
		अणु
			FREQ2FBIN(2422, 1),
			FREQ2FBIN(2427, 1),
			FREQ2FBIN(2447, 1),
			FREQ2FBIN(2452, 1)
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(2484, 1),
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
		पूर्ण,

		अणु
			/* Data[9].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[9].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[9].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[10].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[10].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[10].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[11].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[11].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[11].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[11].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण
	 पूर्ण,
	.ctlPowerData_2G = अणु
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 1) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
	 पूर्ण,
	.modalHeader5G = अणु
		/* 4 idle,t1,t2,b (4 bits per setting) */
		.antCtrlCommon = LE32(0x220),
		/* 4 ra1l1, ra2l1, ra1l2,ra2l2,ra12 */
		.antCtrlCommon2 = LE32(0x11111),
		 /* antCtrlChain 6 idle, t,r,rx1,rx12,b (2 bits each) */
		.antCtrlChain = अणु
			LE16(0x150), LE16(0x150), LE16(0x150),
		पूर्ण,
		 /* xatten1DB 3 xatten1_db क्रम AR9280 (0xa20c/b20c 5:0) */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम merlin (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 68,
		.voltSlope = 0,
		/* spurChans spur channels in usual fbin coding क्रमmat */
		.spurChans = अणुFREQ2FBIN(5500, 0), 0, 0, 0, 0पूर्ण,
		/* noiseFloorThreshCh Check अगर the रेजिस्टर is per chain */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0xf,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2d,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0cf0e0e0),
		.papdRateMaskHt40 = LE32(0x6cf0e0e0),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	.base_ext2 = अणु
		.tempSlopeLow = 72,
		.tempSlopeHigh = 105,
		.xatten1DBLow = अणु0, 0, 0पूर्ण,
		.xatten1MarginLow = अणु0, 0, 0पूर्ण,
		.xatten1DBHigh = अणु0, 0, 0पूर्ण,
		.xatten1MarginHigh = अणु0, 0, 0पूर्ण
	 पूर्ण,
	.calFreqPier5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5785, 0)
	पूर्ण,
	.calPierData5G = अणु
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,

	पूर्ण,
	.calTarget_freqbin_5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5785, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT20 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT40 = अणु
		FREQ2FBIN(5190, 0),
		FREQ2FBIN(5230, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5410, 0),
		FREQ2FBIN(5510, 0),
		FREQ2FBIN(5670, 0),
		FREQ2FBIN(5755, 0),
		FREQ2FBIN(5825, 0)
	 पूर्ण,
	.calTargetPower5G = अणु
		/* 6-24,36,48,54 */
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
		अणु अणु42, 40, 40, 34पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT20 = अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20पूर्ण पूर्ण,
		अणु अणु38, 38, 38, 38, 32, 28, 38, 38, 32, 28, 38, 38, 32, 26पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 32, 28, 36, 36, 32, 28, 36, 36, 32, 26पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT40 =  अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 30, 26, 36, 36, 30, 26, 36, 36, 30, 24पूर्ण पूर्ण,
		अणु अणु34, 34, 34, 34, 30, 26, 34, 34, 30, 26, 34, 34, 30, 24पूर्ण पूर्ण,
	 पूर्ण,
	.ctlIndex_5G =  अणु
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	पूर्ण,
	.ctl_freqbin_5G =  अणु
		अणु
			/* Data[0].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[0].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[0].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[0].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[0].ctlEdges[4].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[0].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[0].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[0].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,
		अणु
			/* Data[1].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[1].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[1].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[1].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[1].ctlEdges[4].bChannel */ FREQ2FBIN(5520, 0),
			/* Data[1].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[1].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[1].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[2].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[2].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[2].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[2].ctlEdges[3].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[2].ctlEdges[4].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[2].ctlEdges[5].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[2].ctlEdges[6].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[2].ctlEdges[7].bChannel */ FREQ2FBIN(5755, 0)
		पूर्ण,

		अणु
			/* Data[3].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[3].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[3].ctlEdges[2].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[3].ctlEdges[3].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[3].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[3].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[3].ctlEdges[6].bChannel */ 0xFF,
			/* Data[3].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[4].ctlEdges[4].bChannel */ 0xFF,
			/* Data[4].ctlEdges[5].bChannel */ 0xFF,
			/* Data[4].ctlEdges[6].bChannel */ 0xFF,
			/* Data[4].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[5].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[5].ctlEdges[4].bChannel */ FREQ2FBIN(5590, 0),
			/* Data[5].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[5].ctlEdges[6].bChannel */ 0xFF,
			/* Data[5].ctlEdges[7].bChannel */ 0xFF
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[6].ctlEdges[2].bChannel */ FREQ2FBIN(5220, 0),
			/* Data[6].ctlEdges[3].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[6].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[6].ctlEdges[5].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[6].ctlEdges[6].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[6].ctlEdges[7].bChannel */ FREQ2FBIN(5745, 0)
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[7].ctlEdges[4].bChannel */ FREQ2FBIN(5560, 0),
			/* Data[7].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[7].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[7].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[8].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[8].ctlEdges[4].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[8].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[8].ctlEdges[6].bChannel */ FREQ2FBIN(5755, 0),
			/* Data[8].ctlEdges[7].bChannel */ FREQ2FBIN(5795, 0)
		पूर्ण
	 पूर्ण,
	.ctlPowerData_5G = अणु
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 0), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 0), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
			पूर्ण
		पूर्ण,
	 पूर्ण
पूर्ण;


अटल स्थिर काष्ठा ar9300_eeprom ar9300_h112 = अणु
	.eepromVersion = 2,
	.ढाँचाVersion = 3,
	.macAddr = अणु0x00, 0x03, 0x7f, 0x0, 0x0, 0x0पूर्ण,
	.custData = अणु"h112-241-f0000"पूर्ण,
	.baseEepHeader = अणु
		.regDmn = अणु LE16(0), LE16(0x1f) पूर्ण,
		.txrxMask =  0x77, /* 4 bits tx and 4 bits rx */
		.opCapFlags = अणु
			.opFlags = AR5416_OPFLAGS_11G | AR5416_OPFLAGS_11A,
			.eepMisc = AR9300_EEPMISC_LITTLE_ENDIAN,
		पूर्ण,
		.rfSilent = 0,
		.blueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes lower byte in eeprom location */
		.pwrTableOffset = AR9300_PWR_TABLE_OFFSET,
		.params_क्रम_tuning_caps = अणु0, 0पूर्ण,
		.featureEnable = 0x0d,
		/*
		 * bit0 - enable tx temp comp - disabled
		 * bit1 - enable tx volt comp - disabled
		 * bit2 - enable fastClock - enabled
		 * bit3 - enable करोubling - enabled
		 * bit4 - enable पूर्णांकernal regulator - disabled
		 * bit5 - enable pa predistortion - disabled
		 */
		.miscConfiguration = 0, /* bit0 - turn करोwn drivestrength */
		.eepromWriteEnableGpio = 6,
		.wlanDisableGpio = 0,
		.wlanLedGpio = 8,
		.rxBandSelectGpio = 0xff,
		.txrxgain = 0x10,
		.swreg = 0,
	पूर्ण,
	.modalHeader2G = अणु
		/* ar9300_modal_eep_header  2g */
		/* 4 idle,t1,t2,b(4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
		.antCtrlCommon2 = LE32(0x44444),

		/*
		 * antCtrlChain[AR9300_MAX_CHAINS]; 6 idle, t, r,
		 * rx1, rx12, b (2 bits each)
		 */
		.antCtrlChain = अणु LE16(0x150), LE16(0x150), LE16(0x150) पूर्ण,

		/*
		 * xatten1DB[AR9300_MAX_CHAINS];  3 xatten1_db
		 * क्रम ar9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम ar9280 (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 25,
		.voltSlope = 0,

		/*
		 * spurChans[OSPREY_EEPROM_MODAL_SPURS]; spur
		 * channels in usual fbin coding क्रमmat
		 */
		.spurChans = अणुFREQ2FBIN(2464, 1), 0, 0, 0, 0पूर्ण,

		/*
		 * noiseFloorThreshCh[AR9300_MAX_CHAINS]; 3 Check
		 * अगर the रेजिस्टर is per chain
		 */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2c,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0c80c080),
		.papdRateMaskHt40 = LE32(0x0080c080),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	पूर्ण,
	.base_ext1 = अणु
		.ant_भाग_control = 0,
		.future = अणु0, 0पूर्ण,
		.tempslopextension = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	पूर्ण,
	.calFreqPier2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2462, 1),
	पूर्ण,
	/* ar9300_cal_data_per_freq_op_loop 2g */
	.calPierData2G = अणु
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.calTarget_freqbin_Cck = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2472, 1),
	पूर्ण,
	.calTarget_freqbin_2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTarget_freqbin_2GHT20 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTarget_freqbin_2GHT40 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTargetPowerCck = अणु
		/* 1L-5L,5S,11L,11S */
		अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
		अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2G = अणु
		/* 6-24,36,48,54 */
		अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT20 = अणु
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT40 = अणु
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_2G =  अणु
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	पूर्ण,
	.ctl_freqbin_2G = अणु
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2457, 1),
			FREQ2FBIN(2462, 1)
		पूर्ण,
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,

		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,
		अणु
			FREQ2FBIN(2422, 1),
			FREQ2FBIN(2427, 1),
			FREQ2FBIN(2447, 1),
			FREQ2FBIN(2452, 1)
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(2484, 1),
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
		पूर्ण,

		अणु
			/* Data[9].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[9].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[9].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[10].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[10].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[10].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[11].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[11].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[11].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[11].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण
	पूर्ण,
	.ctlPowerData_2G = अणु
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 1) पूर्ण पूर्ण,

		अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
	पूर्ण,
	.modalHeader5G = अणु
		/* 4 idle,t1,t2,b (4 bits per setting) */
		.antCtrlCommon = LE32(0x220),
		/* 4 ra1l1, ra2l1, ra1l2,ra2l2,ra12 */
		.antCtrlCommon2 = LE32(0x44444),
		/* antCtrlChain 6 idle, t,r,rx1,rx12,b (2 bits each) */
		.antCtrlChain = अणु
			LE16(0x150), LE16(0x150), LE16(0x150),
		पूर्ण,
		/* xatten1DB 3 xatten1_db क्रम AR9280 (0xa20c/b20c 5:0) */
		.xatten1DB = अणु0, 0, 0पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम merlin (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0, 0, 0पूर्ण,
		.tempSlope = 45,
		.voltSlope = 0,
		/* spurChans spur channels in usual fbin coding क्रमmat */
		.spurChans = अणु0, 0, 0, 0, 0पूर्ण,
		/* noiseFloorThreshCh Check अगर the रेजिस्टर is per chain */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2d,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0cf0e0e0),
		.papdRateMaskHt40 = LE32(0x6cf0e0e0),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	पूर्ण,
	.base_ext2 = अणु
		.tempSlopeLow = 40,
		.tempSlopeHigh = 50,
		.xatten1DBLow = अणु0, 0, 0पूर्ण,
		.xatten1MarginLow = अणु0, 0, 0पूर्ण,
		.xatten1DBHigh = अणु0, 0, 0पूर्ण,
		.xatten1MarginHigh = अणु0, 0, 0पूर्ण
	पूर्ण,
	.calFreqPier5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5785, 0)
	पूर्ण,
	.calPierData5G = अणु
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,

	पूर्ण,
	.calTarget_freqbin_5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT20 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT40 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTargetPower5G = अणु
		/* 6-24,36,48,54 */
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower5GHT20 = अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 20, 20, 20, 16पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 20, 20, 20, 16पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 18, 18, 18, 16पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 18, 18, 18, 16पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 16, 16, 16, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 16, 16, 16, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 14, 14, 14, 12पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 14, 14, 14, 12पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower5GHT40 =  अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 18, 18, 18, 14पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 18, 18, 18, 14पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 16, 16, 16, 12पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 16, 16, 16, 12पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 14, 14, 14, 10पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 14, 14, 14, 10पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 12, 12, 12, 8पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 12, 12, 12, 8पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_5G =  अणु
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	पूर्ण,
	.ctl_freqbin_5G =  अणु
		अणु
			/* Data[0].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[0].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[0].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[0].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[0].ctlEdges[4].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[0].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[0].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[0].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,
		अणु
			/* Data[1].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[1].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[1].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[1].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[1].ctlEdges[4].bChannel */ FREQ2FBIN(5520, 0),
			/* Data[1].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[1].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[1].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[2].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[2].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[2].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[2].ctlEdges[3].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[2].ctlEdges[4].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[2].ctlEdges[5].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[2].ctlEdges[6].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[2].ctlEdges[7].bChannel */ FREQ2FBIN(5755, 0)
		पूर्ण,

		अणु
			/* Data[3].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[3].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[3].ctlEdges[2].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[3].ctlEdges[3].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[3].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[3].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[3].ctlEdges[6].bChannel */ 0xFF,
			/* Data[3].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[4].ctlEdges[4].bChannel */ 0xFF,
			/* Data[4].ctlEdges[5].bChannel */ 0xFF,
			/* Data[4].ctlEdges[6].bChannel */ 0xFF,
			/* Data[4].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[5].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[5].ctlEdges[4].bChannel */ FREQ2FBIN(5590, 0),
			/* Data[5].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[5].ctlEdges[6].bChannel */ 0xFF,
			/* Data[5].ctlEdges[7].bChannel */ 0xFF
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[6].ctlEdges[2].bChannel */ FREQ2FBIN(5220, 0),
			/* Data[6].ctlEdges[3].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[6].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[6].ctlEdges[5].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[6].ctlEdges[6].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[6].ctlEdges[7].bChannel */ FREQ2FBIN(5745, 0)
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[7].ctlEdges[4].bChannel */ FREQ2FBIN(5560, 0),
			/* Data[7].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[7].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[7].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[8].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[8].ctlEdges[4].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[8].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[8].ctlEdges[6].bChannel */ FREQ2FBIN(5755, 0),
			/* Data[8].ctlEdges[7].bChannel */ FREQ2FBIN(5795, 0)
		पूर्ण
	पूर्ण,
	.ctlPowerData_5G = अणु
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 0), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 0), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
			पूर्ण
		पूर्ण,
	पूर्ण
पूर्ण;


अटल स्थिर काष्ठा ar9300_eeprom ar9300_x112 = अणु
	.eepromVersion = 2,
	.ढाँचाVersion = 5,
	.macAddr = अणु0x00, 0x03, 0x7f, 0x0, 0x0, 0x0पूर्ण,
	.custData = अणु"x112-041-f0000"पूर्ण,
	.baseEepHeader = अणु
		.regDmn = अणु LE16(0), LE16(0x1f) पूर्ण,
		.txrxMask =  0x77, /* 4 bits tx and 4 bits rx */
		.opCapFlags = अणु
			.opFlags = AR5416_OPFLAGS_11G | AR5416_OPFLAGS_11A,
			.eepMisc = AR9300_EEPMISC_LITTLE_ENDIAN,
		पूर्ण,
		.rfSilent = 0,
		.blueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes lower byte in eeprom location */
		.pwrTableOffset = AR9300_PWR_TABLE_OFFSET,
		.params_क्रम_tuning_caps = अणु0, 0पूर्ण,
		.featureEnable = 0x0d,
		/*
		 * bit0 - enable tx temp comp - disabled
		 * bit1 - enable tx volt comp - disabled
		 * bit2 - enable fastघड़ी - enabled
		 * bit3 - enable करोubling - enabled
		 * bit4 - enable पूर्णांकernal regulator - disabled
		 * bit5 - enable pa predistortion - disabled
		 */
		.miscConfiguration = 0, /* bit0 - turn करोwn drivestrength */
		.eepromWriteEnableGpio = 6,
		.wlanDisableGpio = 0,
		.wlanLedGpio = 8,
		.rxBandSelectGpio = 0xff,
		.txrxgain = 0x0,
		.swreg = 0,
	पूर्ण,
	.modalHeader2G = अणु
		/* ar9300_modal_eep_header  2g */
		/* 4 idle,t1,t2,b(4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
		.antCtrlCommon2 = LE32(0x22222),

		/*
		 * antCtrlChain[ar9300_max_chains]; 6 idle, t, r,
		 * rx1, rx12, b (2 bits each)
		 */
		.antCtrlChain = अणु LE16(0x10), LE16(0x10), LE16(0x10) पूर्ण,

		/*
		 * xatten1DB[AR9300_max_chains];  3 xatten1_db
		 * क्रम ar9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = अणु0x1b, 0x1b, 0x1bपूर्ण,

		/*
		 * xatten1Margin[ar9300_max_chains]; 3 xatten1_margin
		 * क्रम ar9280 (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0x15, 0x15, 0x15पूर्ण,
		.tempSlope = 50,
		.voltSlope = 0,

		/*
		 * spurChans[OSPrey_eeprom_modal_sPURS]; spur
		 * channels in usual fbin coding क्रमmat
		 */
		.spurChans = अणुFREQ2FBIN(2464, 1), 0, 0, 0, 0पूर्ण,

		/*
		 * noiseFloorThreshch[ar9300_max_cHAINS]; 3 Check
		 * अगर the रेजिस्टर is per chain
		 */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2c,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0c80c080),
		.papdRateMaskHt40 = LE32(0x0080c080),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	पूर्ण,
	.base_ext1 = अणु
		.ant_भाग_control = 0,
		.future = अणु0, 0पूर्ण,
		.tempslopextension = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	पूर्ण,
	.calFreqPier2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1),
	पूर्ण,
	/* ar9300_cal_data_per_freq_op_loop 2g */
	.calPierData2G = अणु
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.calTarget_freqbin_Cck = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2472, 1),
	पूर्ण,
	.calTarget_freqbin_2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTarget_freqbin_2GHT20 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTarget_freqbin_2GHT40 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	पूर्ण,
	.calTargetPowerCck = अणु
		/* 1L-5L,5S,11L,11s */
		अणु अणु38, 38, 38, 38पूर्ण पूर्ण,
		अणु अणु38, 38, 38, 38पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2G = अणु
		/* 6-24,36,48,54 */
		अणु अणु38, 38, 36, 34पूर्ण पूर्ण,
		अणु अणु38, 38, 36, 34पूर्ण पूर्ण,
		अणु अणु38, 38, 34, 32पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT20 = अणु
		अणु अणु36, 36, 36, 36, 36, 34, 34, 32, 30, 28, 28, 28, 28, 26पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 36, 34, 36, 34, 32, 30, 30, 30, 28, 26पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 36, 34, 34, 32, 30, 28, 28, 28, 28, 26पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT40 = अणु
		अणु अणु36, 36, 36, 36, 34, 32, 32, 30, 28, 26, 26, 26, 26, 24पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 34, 32, 34, 32, 30, 28, 28, 28, 28, 24पूर्ण पूर्ण,
		अणु अणु36, 36, 36, 36, 34, 32, 32, 30, 28, 26, 26, 26, 26, 24पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_2G =  अणु
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	पूर्ण,
	.ctl_freqbin_2G = अणु
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2457, 1),
			FREQ2FBIN(2462, 1)
		पूर्ण,
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,

		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,
		अणु
			FREQ2FBIN(2422, 1),
			FREQ2FBIN(2427, 1),
			FREQ2FBIN(2447, 1),
			FREQ2FBIN(2452, 1)
		पूर्ण,

		अणु
			/* Data[4].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[4].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			/* Data[4].ctledges[2].bchannel */ FREQ2FBIN(2472, 1),
			/* Data[4].ctledges[3].bchannel */ FREQ2FBIN(2484, 1),
		पूर्ण,

		अणु
			/* Data[5].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[5].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			/* Data[5].ctledges[2].bchannel */ FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[6].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[6].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[7].ctledges[0].bchannel */ FREQ2FBIN(2422, 1),
			/* Data[7].ctledges[1].bchannel */ FREQ2FBIN(2427, 1),
			/* Data[7].ctledges[2].bchannel */ FREQ2FBIN(2447, 1),
			/* Data[7].ctledges[3].bchannel */ FREQ2FBIN(2462, 1),
		पूर्ण,

		अणु
			/* Data[8].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[8].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			/* Data[8].ctledges[2].bchannel */ FREQ2FBIN(2472, 1),
		पूर्ण,

		अणु
			/* Data[9].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[9].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			/* Data[9].ctledges[2].bchannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[10].ctledges[0].bchannel */ FREQ2FBIN(2412, 1),
			/* Data[10].ctledges[1].bchannel */ FREQ2FBIN(2417, 1),
			/* Data[10].ctledges[2].bchannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[11].ctledges[0].bchannel */ FREQ2FBIN(2422, 1),
			/* Data[11].ctledges[1].bchannel */ FREQ2FBIN(2427, 1),
			/* Data[11].ctledges[2].bchannel */ FREQ2FBIN(2447, 1),
			/* Data[11].ctledges[3].bchannel */ FREQ2FBIN(2462, 1),
		पूर्ण
	पूर्ण,
	.ctlPowerData_2G = अणु
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 1) पूर्ण पूर्ण,

		अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
		अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
	पूर्ण,
	.modalHeader5G = अणु
		/* 4 idle,t1,t2,b (4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2,ra2l2,ra12 */
		.antCtrlCommon2 = LE32(0x22222),
		/* antCtrlChain 6 idle, t,r,rx1,rx12,b (2 bits each) */
		.antCtrlChain = अणु
			LE16(0x0), LE16(0x0), LE16(0x0),
		पूर्ण,
		/* xatten1DB 3 xatten1_db क्रम ar9280 (0xa20c/b20c 5:0) */
		.xatten1DB = अणु0x13, 0x19, 0x17पूर्ण,

		/*
		 * xatten1Margin[ar9300_max_chains]; 3 xatten1_margin
		 * क्रम merlin (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0x19, 0x19, 0x19पूर्ण,
		.tempSlope = 70,
		.voltSlope = 15,
		/* spurChans spur channels in usual fbin coding क्रमmat */
		.spurChans = अणु0, 0, 0, 0, 0पूर्ण,
		/* noiseFloorThreshch check अगर the रेजिस्टर is per chain */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2d,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0cf0e0e0),
		.papdRateMaskHt40 = LE32(0x6cf0e0e0),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	पूर्ण,
	.base_ext2 = अणु
		.tempSlopeLow = 72,
		.tempSlopeHigh = 105,
		.xatten1DBLow = अणु0x10, 0x14, 0x10पूर्ण,
		.xatten1MarginLow = अणु0x19, 0x19 , 0x19पूर्ण,
		.xatten1DBHigh = अणु0x1d, 0x20, 0x24पूर्ण,
		.xatten1MarginHigh = अणु0x10, 0x10, 0x10पूर्ण
	पूर्ण,
	.calFreqPier5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5785, 0)
	पूर्ण,
	.calPierData5G = अणु
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,
		अणु
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
			अणु0, 0, 0, 0, 0पूर्ण,
		पूर्ण,

	पूर्ण,
	.calTarget_freqbin_5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT20 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT40 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5725, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTargetPower5G = अणु
		/* 6-24,36,48,54 */
		अणु अणु32, 32, 28, 26पूर्ण पूर्ण,
		अणु अणु32, 32, 28, 26पूर्ण पूर्ण,
		अणु अणु32, 32, 28, 26पूर्ण पूर्ण,
		अणु अणु32, 32, 26, 24पूर्ण पूर्ण,
		अणु अणु32, 32, 26, 24पूर्ण पूर्ण,
		अणु अणु32, 32, 24, 22पूर्ण पूर्ण,
		अणु अणु30, 30, 24, 22पूर्ण पूर्ण,
		अणु अणु30, 30, 24, 22पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower5GHT20 = अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 26, 32, 26, 24, 22, 22, 22, 20, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 26, 32, 26, 24, 22, 20, 18, 16, 16पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 28, 26, 32, 24, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 28, 26, 30, 24, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 28, 26, 30, 24, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower5GHT40 =  अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 30, 28, 26, 30, 26, 24, 22, 22, 22, 20, 20पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 30, 28, 26, 30, 26, 24, 22, 20, 18, 16, 16पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_5G =  अणु
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	पूर्ण,
	.ctl_freqbin_5G =  अणु
		अणु
			/* Data[0].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[0].ctledges[1].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[0].ctledges[2].bchannel */ FREQ2FBIN(5280, 0),
			/* Data[0].ctledges[3].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[0].ctledges[4].bchannel */ FREQ2FBIN(5600, 0),
			/* Data[0].ctledges[5].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[0].ctledges[6].bchannel */ FREQ2FBIN(5745, 0),
			/* Data[0].ctledges[7].bchannel */ FREQ2FBIN(5825, 0)
		पूर्ण,
		अणु
			/* Data[1].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[1].ctledges[1].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[1].ctledges[2].bchannel */ FREQ2FBIN(5280, 0),
			/* Data[1].ctledges[3].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[1].ctledges[4].bchannel */ FREQ2FBIN(5520, 0),
			/* Data[1].ctledges[5].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[1].ctledges[6].bchannel */ FREQ2FBIN(5745, 0),
			/* Data[1].ctledges[7].bchannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[2].ctledges[0].bchannel */ FREQ2FBIN(5190, 0),
			/* Data[2].ctledges[1].bchannel */ FREQ2FBIN(5230, 0),
			/* Data[2].ctledges[2].bchannel */ FREQ2FBIN(5270, 0),
			/* Data[2].ctledges[3].bchannel */ FREQ2FBIN(5310, 0),
			/* Data[2].ctledges[4].bchannel */ FREQ2FBIN(5510, 0),
			/* Data[2].ctledges[5].bchannel */ FREQ2FBIN(5550, 0),
			/* Data[2].ctledges[6].bchannel */ FREQ2FBIN(5670, 0),
			/* Data[2].ctledges[7].bchannel */ FREQ2FBIN(5755, 0)
		पूर्ण,

		अणु
			/* Data[3].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[3].ctledges[1].bchannel */ FREQ2FBIN(5200, 0),
			/* Data[3].ctledges[2].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[3].ctledges[3].bchannel */ FREQ2FBIN(5320, 0),
			/* Data[3].ctledges[4].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[3].ctledges[5].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[3].ctledges[6].bchannel */ 0xFF,
			/* Data[3].ctledges[7].bchannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[4].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[4].ctledges[1].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[4].ctledges[2].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[4].ctledges[3].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[4].ctledges[4].bchannel */ 0xFF,
			/* Data[4].ctledges[5].bchannel */ 0xFF,
			/* Data[4].ctledges[6].bchannel */ 0xFF,
			/* Data[4].ctledges[7].bchannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[5].ctledges[0].bchannel */ FREQ2FBIN(5190, 0),
			/* Data[5].ctledges[1].bchannel */ FREQ2FBIN(5270, 0),
			/* Data[5].ctledges[2].bchannel */ FREQ2FBIN(5310, 0),
			/* Data[5].ctledges[3].bchannel */ FREQ2FBIN(5510, 0),
			/* Data[5].ctledges[4].bchannel */ FREQ2FBIN(5590, 0),
			/* Data[5].ctledges[5].bchannel */ FREQ2FBIN(5670, 0),
			/* Data[5].ctledges[6].bchannel */ 0xFF,
			/* Data[5].ctledges[7].bchannel */ 0xFF
		पूर्ण,

		अणु
			/* Data[6].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[6].ctledges[1].bchannel */ FREQ2FBIN(5200, 0),
			/* Data[6].ctledges[2].bchannel */ FREQ2FBIN(5220, 0),
			/* Data[6].ctledges[3].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[6].ctledges[4].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[6].ctledges[5].bchannel */ FREQ2FBIN(5600, 0),
			/* Data[6].ctledges[6].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[6].ctledges[7].bchannel */ FREQ2FBIN(5745, 0)
		पूर्ण,

		अणु
			/* Data[7].ctledges[0].bchannel */ FREQ2FBIN(5180, 0),
			/* Data[7].ctledges[1].bchannel */ FREQ2FBIN(5260, 0),
			/* Data[7].ctledges[2].bchannel */ FREQ2FBIN(5320, 0),
			/* Data[7].ctledges[3].bchannel */ FREQ2FBIN(5500, 0),
			/* Data[7].ctledges[4].bchannel */ FREQ2FBIN(5560, 0),
			/* Data[7].ctledges[5].bchannel */ FREQ2FBIN(5700, 0),
			/* Data[7].ctledges[6].bchannel */ FREQ2FBIN(5745, 0),
			/* Data[7].ctledges[7].bchannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[8].ctledges[0].bchannel */ FREQ2FBIN(5190, 0),
			/* Data[8].ctledges[1].bchannel */ FREQ2FBIN(5230, 0),
			/* Data[8].ctledges[2].bchannel */ FREQ2FBIN(5270, 0),
			/* Data[8].ctledges[3].bchannel */ FREQ2FBIN(5510, 0),
			/* Data[8].ctledges[4].bchannel */ FREQ2FBIN(5550, 0),
			/* Data[8].ctledges[5].bchannel */ FREQ2FBIN(5670, 0),
			/* Data[8].ctledges[6].bchannel */ FREQ2FBIN(5755, 0),
			/* Data[8].ctledges[7].bchannel */ FREQ2FBIN(5795, 0)
		पूर्ण
	पूर्ण,
	.ctlPowerData_5G = अणु
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 0), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 0), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
			पूर्ण
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ar9300_eeprom ar9300_h116 = अणु
	.eepromVersion = 2,
	.ढाँचाVersion = 4,
	.macAddr = अणु0x00, 0x03, 0x7f, 0x0, 0x0, 0x0पूर्ण,
	.custData = अणु"h116-041-f0000"पूर्ण,
	.baseEepHeader = अणु
		.regDmn = अणु LE16(0), LE16(0x1f) पूर्ण,
		.txrxMask =  0x33, /* 4 bits tx and 4 bits rx */
		.opCapFlags = अणु
			.opFlags = AR5416_OPFLAGS_11G | AR5416_OPFLAGS_11A,
			.eepMisc = AR9300_EEPMISC_LITTLE_ENDIAN,
		पूर्ण,
		.rfSilent = 0,
		.blueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes lower byte in eeprom location */
		.pwrTableOffset = AR9300_PWR_TABLE_OFFSET,
		.params_क्रम_tuning_caps = अणु0, 0पूर्ण,
		.featureEnable = 0x0d,
		 /*
		  * bit0 - enable tx temp comp - disabled
		  * bit1 - enable tx volt comp - disabled
		  * bit2 - enable fastClock - enabled
		  * bit3 - enable करोubling - enabled
		  * bit4 - enable पूर्णांकernal regulator - disabled
		  * bit5 - enable pa predistortion - disabled
		  */
		.miscConfiguration = 0, /* bit0 - turn करोwn drivestrength */
		.eepromWriteEnableGpio = 6,
		.wlanDisableGpio = 0,
		.wlanLedGpio = 8,
		.rxBandSelectGpio = 0xff,
		.txrxgain = 0x10,
		.swreg = 0,
	 पूर्ण,
	.modalHeader2G = अणु
	/* ar9300_modal_eep_header  2g */
		/* 4 idle,t1,t2,b(4 bits per setting) */
		.antCtrlCommon = LE32(0x110),
		/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
		.antCtrlCommon2 = LE32(0x44444),

		/*
		 * antCtrlChain[AR9300_MAX_CHAINS]; 6 idle, t, r,
		 * rx1, rx12, b (2 bits each)
		 */
		.antCtrlChain = अणु LE16(0x10), LE16(0x10), LE16(0x10) पूर्ण,

		/*
		 * xatten1DB[AR9300_MAX_CHAINS];  3 xatten1_db
		 * क्रम ar9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = अणु0x1f, 0x1f, 0x1fपूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम ar9280 (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0x12, 0x12, 0x12पूर्ण,
		.tempSlope = 25,
		.voltSlope = 0,

		/*
		 * spurChans[OSPREY_EEPROM_MODAL_SPURS]; spur
		 * channels in usual fbin coding क्रमmat
		 */
		.spurChans = अणुFREQ2FBIN(2464, 1), 0, 0, 0, 0पूर्ण,

		/*
		 * noiseFloorThreshCh[AR9300_MAX_CHAINS]; 3 Check
		 * अगर the रेजिस्टर is per chain
		 */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2c,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0c80C080),
		.papdRateMaskHt40 = LE32(0x0080C080),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	 .base_ext1 = अणु
		.ant_भाग_control = 0,
		.future = अणु0, 0पूर्ण,
		.tempslopextension = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	 पूर्ण,
	.calFreqPier2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2462, 1),
	 पूर्ण,
	/* ar9300_cal_data_per_freq_op_loop 2g */
	.calPierData2G = अणु
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण, अणु0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.calTarget_freqbin_Cck = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2472, 1),
	 पूर्ण,
	.calTarget_freqbin_2G = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT20 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTarget_freqbin_2GHT40 = अणु
		FREQ2FBIN(2412, 1),
		FREQ2FBIN(2437, 1),
		FREQ2FBIN(2472, 1)
	 पूर्ण,
	.calTargetPowerCck = अणु
		 /* 1L-5L,5S,11L,11S */
		 अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
		 अणु अणु34, 34, 34, 34पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2G = अणु
		 /* 6-24,36,48,54 */
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
		 अणु अणु34, 34, 32, 32पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT20 = अणु
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.calTargetPower2GHT40 = अणु
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0पूर्ण पूर्ण,
	पूर्ण,
	.ctlIndex_2G =  अणु
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	पूर्ण,
	.ctl_freqbin_2G = अणु
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2457, 1),
			FREQ2FBIN(2462, 1)
		पूर्ण,
		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,

		अणु
			FREQ2FBIN(2412, 1),
			FREQ2FBIN(2417, 1),
			FREQ2FBIN(2462, 1),
			0xFF,
		पूर्ण,
		अणु
			FREQ2FBIN(2422, 1),
			FREQ2FBIN(2427, 1),
			FREQ2FBIN(2447, 1),
			FREQ2FBIN(2452, 1)
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(2484, 1),
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			FREQ2FBIN(2472, 1),
			0,
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
		पूर्ण,

		अणु
			/* Data[9].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[9].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[9].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[10].ctlEdges[0].bChannel */ FREQ2FBIN(2412, 1),
			/* Data[10].ctlEdges[1].bChannel */ FREQ2FBIN(2417, 1),
			/* Data[10].ctlEdges[2].bChannel */ FREQ2FBIN(2472, 1),
			0
		पूर्ण,

		अणु
			/* Data[11].ctlEdges[0].bChannel */ FREQ2FBIN(2422, 1),
			/* Data[11].ctlEdges[1].bChannel */ FREQ2FBIN(2427, 1),
			/* Data[11].ctlEdges[2].bChannel */ FREQ2FBIN(2447, 1),
			/* Data[11].ctlEdges[3].bChannel */ FREQ2FBIN(2462, 1),
		पूर्ण
	 पूर्ण,
	.ctlPowerData_2G = अणु
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 1) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,

		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 0) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
		 अणु अणु CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 1) पूर्ण पूर्ण,
	 पूर्ण,
	.modalHeader5G = अणु
		/* 4 idle,t1,t2,b (4 bits per setting) */
		.antCtrlCommon = LE32(0x220),
		/* 4 ra1l1, ra2l1, ra1l2,ra2l2,ra12 */
		.antCtrlCommon2 = LE32(0x44444),
		 /* antCtrlChain 6 idle, t,r,rx1,rx12,b (2 bits each) */
		.antCtrlChain = अणु
			LE16(0x150), LE16(0x150), LE16(0x150),
		पूर्ण,
		 /* xatten1DB 3 xatten1_db क्रम AR9280 (0xa20c/b20c 5:0) */
		.xatten1DB = अणु0x19, 0x19, 0x19पूर्ण,

		/*
		 * xatten1Margin[AR9300_MAX_CHAINS]; 3 xatten1_margin
		 * क्रम merlin (0xa20c/b20c 16:12
		 */
		.xatten1Margin = अणु0x14, 0x14, 0x14पूर्ण,
		.tempSlope = 70,
		.voltSlope = 0,
		/* spurChans spur channels in usual fbin coding क्रमmat */
		.spurChans = अणु0, 0, 0, 0, 0पूर्ण,
		/* noiseFloorThreshCh Check अगर the रेजिस्टर is per chain */
		.noiseFloorThreshCh = अणु-1, 0, 0पूर्ण,
		.reserved = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
		.quick_drop = 0,
		.xpaBiasLvl = 0,
		.txFrameToDataStart = 0x0e,
		.txFrameToPaOn = 0x0e,
		.txClip = 3, /* 4 bits tx_clip, 4 bits dac_scale_cck */
		.antennaGain = 0,
		.चयनSettling = 0x2d,
		.adcDesiredSize = -30,
		.txEndToXpaOff = 0,
		.txEndToRxOn = 0x2,
		.txFrameToXpaOn = 0xe,
		.thresh62 = 28,
		.papdRateMaskHt20 = LE32(0x0cf0e0e0),
		.papdRateMaskHt40 = LE32(0x6cf0e0e0),
		.चयनcomspdt = 0,
		.xlna_bias_strength = 0,
		.futureModal = अणु
			0, 0, 0, 0, 0, 0, 0,
		पूर्ण,
	 पूर्ण,
	.base_ext2 = अणु
		.tempSlopeLow = 35,
		.tempSlopeHigh = 50,
		.xatten1DBLow = अणु0, 0, 0पूर्ण,
		.xatten1MarginLow = अणु0, 0, 0पूर्ण,
		.xatten1DBHigh = अणु0, 0, 0पूर्ण,
		.xatten1MarginHigh = अणु0, 0, 0पूर्ण
	 पूर्ण,
	.calFreqPier5G = अणु
		FREQ2FBIN(5160, 0),
		FREQ2FBIN(5220, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5785, 0)
	पूर्ण,
	.calPierData5G = अणु
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,
			अणु
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
				अणु0, 0, 0, 0, 0पूर्ण,
			पूर्ण,

	पूर्ण,
	.calTarget_freqbin_5G = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5600, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT20 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5825, 0)
	पूर्ण,
	.calTarget_freqbin_5GHT40 = अणु
		FREQ2FBIN(5180, 0),
		FREQ2FBIN(5240, 0),
		FREQ2FBIN(5320, 0),
		FREQ2FBIN(5400, 0),
		FREQ2FBIN(5500, 0),
		FREQ2FBIN(5700, 0),
		FREQ2FBIN(5745, 0),
		FREQ2FBIN(5825, 0)
	 पूर्ण,
	.calTargetPower5G = अणु
		/* 6-24,36,48,54 */
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
		अणु अणु30, 30, 28, 24पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT20 = अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 0, 0, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.calTargetPower5GHT40 =  अणु
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		अणु अणु28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 0, 0, 0, 0पूर्ण पूर्ण,
		अणु अणु28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 0, 0, 0, 0पूर्ण पूर्ण,
	 पूर्ण,
	.ctlIndex_5G =  अणु
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	पूर्ण,
	.ctl_freqbin_5G =  अणु
		अणु
			/* Data[0].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[0].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[0].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[0].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[0].ctlEdges[4].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[0].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[0].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[0].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,
		अणु
			/* Data[1].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[1].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[1].ctlEdges[2].bChannel */ FREQ2FBIN(5280, 0),
			/* Data[1].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[1].ctlEdges[4].bChannel */ FREQ2FBIN(5520, 0),
			/* Data[1].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[1].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[1].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[2].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[2].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[2].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[2].ctlEdges[3].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[2].ctlEdges[4].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[2].ctlEdges[5].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[2].ctlEdges[6].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[2].ctlEdges[7].bChannel */ FREQ2FBIN(5755, 0)
		पूर्ण,

		अणु
			/* Data[3].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[3].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[3].ctlEdges[2].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[3].ctlEdges[3].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[3].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[3].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[3].ctlEdges[6].bChannel */ 0xFF,
			/* Data[3].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[4].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[4].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[4].ctlEdges[2].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[4].ctlEdges[3].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[4].ctlEdges[4].bChannel */ 0xFF,
			/* Data[4].ctlEdges[5].bChannel */ 0xFF,
			/* Data[4].ctlEdges[6].bChannel */ 0xFF,
			/* Data[4].ctlEdges[7].bChannel */ 0xFF,
		पूर्ण,

		अणु
			/* Data[5].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[5].ctlEdges[1].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[5].ctlEdges[2].bChannel */ FREQ2FBIN(5310, 0),
			/* Data[5].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[5].ctlEdges[4].bChannel */ FREQ2FBIN(5590, 0),
			/* Data[5].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[5].ctlEdges[6].bChannel */ 0xFF,
			/* Data[5].ctlEdges[7].bChannel */ 0xFF
		पूर्ण,

		अणु
			/* Data[6].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[6].ctlEdges[1].bChannel */ FREQ2FBIN(5200, 0),
			/* Data[6].ctlEdges[2].bChannel */ FREQ2FBIN(5220, 0),
			/* Data[6].ctlEdges[3].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[6].ctlEdges[4].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[6].ctlEdges[5].bChannel */ FREQ2FBIN(5600, 0),
			/* Data[6].ctlEdges[6].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[6].ctlEdges[7].bChannel */ FREQ2FBIN(5745, 0)
		पूर्ण,

		अणु
			/* Data[7].ctlEdges[0].bChannel */ FREQ2FBIN(5180, 0),
			/* Data[7].ctlEdges[1].bChannel */ FREQ2FBIN(5260, 0),
			/* Data[7].ctlEdges[2].bChannel */ FREQ2FBIN(5320, 0),
			/* Data[7].ctlEdges[3].bChannel */ FREQ2FBIN(5500, 0),
			/* Data[7].ctlEdges[4].bChannel */ FREQ2FBIN(5560, 0),
			/* Data[7].ctlEdges[5].bChannel */ FREQ2FBIN(5700, 0),
			/* Data[7].ctlEdges[6].bChannel */ FREQ2FBIN(5745, 0),
			/* Data[7].ctlEdges[7].bChannel */ FREQ2FBIN(5825, 0)
		पूर्ण,

		अणु
			/* Data[8].ctlEdges[0].bChannel */ FREQ2FBIN(5190, 0),
			/* Data[8].ctlEdges[1].bChannel */ FREQ2FBIN(5230, 0),
			/* Data[8].ctlEdges[2].bChannel */ FREQ2FBIN(5270, 0),
			/* Data[8].ctlEdges[3].bChannel */ FREQ2FBIN(5510, 0),
			/* Data[8].ctlEdges[4].bChannel */ FREQ2FBIN(5550, 0),
			/* Data[8].ctlEdges[5].bChannel */ FREQ2FBIN(5670, 0),
			/* Data[8].ctlEdges[6].bChannel */ FREQ2FBIN(5755, 0),
			/* Data[8].ctlEdges[7].bChannel */ FREQ2FBIN(5795, 0)
		पूर्ण
	 पूर्ण,
	.ctlPowerData_5G = अणु
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 0), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
				CTL(60, 0), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 0), CTL(60, 0), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 1),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 1), CTL(60, 0),
			पूर्ण
		पूर्ण,
		अणु
			अणु
				CTL(60, 1), CTL(60, 0), CTL(60, 1), CTL(60, 1),
				CTL(60, 1), CTL(60, 1), CTL(60, 0), CTL(60, 1),
			पूर्ण
		पूर्ण,
	 पूर्ण
पूर्ण;


अटल स्थिर काष्ठा ar9300_eeprom *ar9300_eep_ढाँचाs[] = अणु
	&ar9300_शेष,
	&ar9300_x112,
	&ar9300_h116,
	&ar9300_h112,
	&ar9300_x113,
पूर्ण;

अटल स्थिर काष्ठा ar9300_eeprom *ar9003_eeprom_काष्ठा_find_by_id(पूर्णांक id)
अणु
	पूर्णांक it;

	क्रम (it = 0; it < ARRAY_SIZE(ar9300_eep_ढाँचाs); it++)
		अगर (ar9300_eep_ढाँचाs[it]->ढाँचाVersion == id)
			वापस ar9300_eep_ढाँचाs[it];
	वापस शून्य;
पूर्ण

अटल पूर्णांक ath9k_hw_ar9300_check_eeprom(काष्ठा ath_hw *ah)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerpolate(पूर्णांक x, पूर्णांक xa, पूर्णांक xb, पूर्णांक ya, पूर्णांक yb)
अणु
	पूर्णांक bf, factor, plus;

	bf = 2 * (yb - ya) * (x - xa) / (xb - xa);
	factor = bf / 2;
	plus = bf % 2;
	वापस ya + factor + plus;
पूर्ण

अटल u32 ath9k_hw_ar9300_get_eeprom(काष्ठा ath_hw *ah,
				      क्रमागत eeprom_param param)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;

	चयन (param) अणु
	हाल EEP_MAC_LSW:
		वापस get_unaligned_be16(eep->macAddr);
	हाल EEP_MAC_MID:
		वापस get_unaligned_be16(eep->macAddr + 2);
	हाल EEP_MAC_MSW:
		वापस get_unaligned_be16(eep->macAddr + 4);
	हाल EEP_REG_0:
		वापस le16_to_cpu(pBase->regDmn[0]);
	हाल EEP_OP_CAP:
		वापस pBase->deviceCap;
	हाल EEP_OP_MODE:
		वापस pBase->opCapFlags.opFlags;
	हाल EEP_RF_SILENT:
		वापस pBase->rfSilent;
	हाल EEP_TX_MASK:
		वापस (pBase->txrxMask >> 4) & 0xf;
	हाल EEP_RX_MASK:
		वापस pBase->txrxMask & 0xf;
	हाल EEP_PAPRD:
		वापस !!(pBase->featureEnable & BIT(5));
	हाल EEP_CHAIN_MASK_REDUCE:
		वापस (pBase->miscConfiguration >> 0x3) & 0x1;
	हाल EEP_ANT_DIV_CTL1:
		अगर (AR_SREV_9565(ah))
			वापस AR9300_EEP_ANTDIV_CONTROL_DEFAULT_VALUE;
		अन्यथा
			वापस eep->base_ext1.ant_भाग_control;
	हाल EEP_ANTENNA_GAIN_5G:
		वापस eep->modalHeader5G.antennaGain;
	हाल EEP_ANTENNA_GAIN_2G:
		वापस eep->modalHeader2G.antennaGain;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool ar9300_eeprom_पढ़ो_byte(काष्ठा ath_hw *ah, पूर्णांक address,
				    u8 *buffer)
अणु
	u16 val;

	अगर (unlikely(!ath9k_hw_nvram_पढ़ो(ah, address / 2, &val)))
		वापस false;

	*buffer = (val >> (8 * (address % 2))) & 0xff;
	वापस true;
पूर्ण

अटल bool ar9300_eeprom_पढ़ो_word(काष्ठा ath_hw *ah, पूर्णांक address,
				    u8 *buffer)
अणु
	u16 val;

	अगर (unlikely(!ath9k_hw_nvram_पढ़ो(ah, address / 2, &val)))
		वापस false;

	buffer[0] = val >> 8;
	buffer[1] = val & 0xff;

	वापस true;
पूर्ण

अटल bool ar9300_पढ़ो_eeprom(काष्ठा ath_hw *ah, पूर्णांक address, u8 *buffer,
			       पूर्णांक count)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक i;

	अगर ((address < 0) || ((address + count) / 2 > AR9300_EEPROM_SIZE - 1)) अणु
		ath_dbg(common, EEPROM, "eeprom address not in range\n");
		वापस false;
	पूर्ण

	/*
	 * Since we're पढ़ोing the bytes in reverse order from a little-endian
	 * word stream, an even address means we only use the lower half of
	 * the 16-bit word at that address
	 */
	अगर (address % 2 == 0) अणु
		अगर (!ar9300_eeprom_पढ़ो_byte(ah, address--, buffer++))
			जाओ error;

		count--;
	पूर्ण

	क्रम (i = 0; i < count / 2; i++) अणु
		अगर (!ar9300_eeprom_पढ़ो_word(ah, address, buffer))
			जाओ error;

		address -= 2;
		buffer += 2;
	पूर्ण

	अगर (count % 2)
		अगर (!ar9300_eeprom_पढ़ो_byte(ah, address, buffer))
			जाओ error;

	वापस true;

error:
	ath_dbg(common, EEPROM, "unable to read eeprom region at offset %d\n",
		address);
	वापस false;
पूर्ण

अटल bool ar9300_otp_पढ़ो_word(काष्ठा ath_hw *ah, पूर्णांक addr, u32 *data)
अणु
	REG_READ(ah, AR9300_OTP_BASE + (4 * addr));

	अगर (!ath9k_hw_रुको(ah, AR9300_OTP_STATUS, AR9300_OTP_STATUS_TYPE,
			   AR9300_OTP_STATUS_VALID, 1000))
		वापस false;

	*data = REG_READ(ah, AR9300_OTP_READ_DATA);
	वापस true;
पूर्ण

अटल bool ar9300_पढ़ो_otp(काष्ठा ath_hw *ah, पूर्णांक address, u8 *buffer,
			    पूर्णांक count)
अणु
	u32 data;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक offset = 8 * ((address - i) % 4);
		अगर (!ar9300_otp_पढ़ो_word(ah, (address - i) / 4, &data))
			वापस false;

		buffer[i] = (data >> offset) & 0xff;
	पूर्ण

	वापस true;
पूर्ण


अटल व्योम ar9300_comp_hdr_unpack(u8 *best, पूर्णांक *code, पूर्णांक *reference,
				   पूर्णांक *length, पूर्णांक *major, पूर्णांक *minor)
अणु
	अचिन्हित दीर्घ value[4];

	value[0] = best[0];
	value[1] = best[1];
	value[2] = best[2];
	value[3] = best[3];
	*code = ((value[0] >> 5) & 0x0007);
	*reference = (value[0] & 0x001f) | ((value[1] >> 2) & 0x0020);
	*length = ((value[1] << 4) & 0x07f0) | ((value[2] >> 4) & 0x000f);
	*major = (value[2] & 0x000f);
	*minor = (value[3] & 0x00ff);
पूर्ण

अटल u16 ar9300_comp_cksum(u8 *data, पूर्णांक dsize)
अणु
	पूर्णांक it, checksum = 0;

	क्रम (it = 0; it < dsize; it++) अणु
		checksum += data[it];
		checksum &= 0xffff;
	पूर्ण

	वापस checksum;
पूर्ण

अटल bool ar9300_uncompress_block(काष्ठा ath_hw *ah,
				    u8 *mptr,
				    पूर्णांक mdataSize,
				    u8 *block,
				    पूर्णांक size)
अणु
	पूर्णांक it;
	पूर्णांक spot;
	पूर्णांक offset;
	पूर्णांक length;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	spot = 0;

	क्रम (it = 0; it < size; it += (length+2)) अणु
		offset = block[it];
		offset &= 0xff;
		spot += offset;
		length = block[it+1];
		length &= 0xff;

		अगर (length > 0 && spot >= 0 && spot+length <= mdataSize) अणु
			ath_dbg(common, EEPROM,
				"Restore at %d: spot=%d offset=%d length=%d\n",
				it, spot, offset, length);
			स_नकल(&mptr[spot], &block[it+2], length);
			spot += length;
		पूर्ण अन्यथा अगर (length > 0) अणु
			ath_dbg(common, EEPROM,
				"Bad restore at %d: spot=%d offset=%d length=%d\n",
				it, spot, offset, length);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ar9300_compress_decision(काष्ठा ath_hw *ah,
				    पूर्णांक it,
				    पूर्णांक code,
				    पूर्णांक reference,
				    u8 *mptr,
				    u8 *word, पूर्णांक length, पूर्णांक mdata_size)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	स्थिर काष्ठा ar9300_eeprom *eep = शून्य;

	चयन (code) अणु
	हाल _CompressNone:
		अगर (length != mdata_size) अणु
			ath_dbg(common, EEPROM,
				"EEPROM structure size mismatch memory=%d eeprom=%d\n",
				mdata_size, length);
			वापस -1;
		पूर्ण
		स_नकल(mptr, word + COMP_HDR_LEN, length);
		ath_dbg(common, EEPROM,
			"restored eeprom %d: uncompressed, length %d\n",
			it, length);
		अवरोध;
	हाल _CompressBlock:
		अगर (reference != 0) अणु
			eep = ar9003_eeprom_काष्ठा_find_by_id(reference);
			अगर (eep == शून्य) अणु
				ath_dbg(common, EEPROM,
					"can't find reference eeprom struct %d\n",
					reference);
				वापस -1;
			पूर्ण
			स_नकल(mptr, eep, mdata_size);
		पूर्ण
		ath_dbg(common, EEPROM,
			"restore eeprom %d: block, reference %d, length %d\n",
			it, reference, length);
		ar9300_uncompress_block(ah, mptr, mdata_size,
					(word + COMP_HDR_LEN), length);
		अवरोध;
	शेष:
		ath_dbg(common, EEPROM, "unknown compression code %d\n", code);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

प्रकार bool (*eeprom_पढ़ो_op)(काष्ठा ath_hw *ah, पूर्णांक address, u8 *buffer,
			       पूर्णांक count);

अटल bool ar9300_check_header(व्योम *data)
अणु
	u32 *word = data;
	वापस !(*word == 0 || *word == ~0);
पूर्ण

अटल bool ar9300_check_eeprom_header(काष्ठा ath_hw *ah, eeprom_पढ़ो_op पढ़ो,
				       पूर्णांक base_addr)
अणु
	u8 header[4];

	अगर (!पढ़ो(ah, base_addr, header, 4))
		वापस false;

	वापस ar9300_check_header(header);
पूर्ण

अटल पूर्णांक ar9300_eeprom_restore_flash(काष्ठा ath_hw *ah, u8 *mptr,
				       पूर्णांक mdata_size)
अणु
	u16 *data = (u16 *) mptr;
	पूर्णांक i;

	क्रम (i = 0; i < mdata_size / 2; i++, data++)
		अगर (!ath9k_hw_nvram_पढ़ो(ah, i, data))
			वापस -EIO;

	वापस 0;
पूर्ण
/*
 * Read the configuration data from the eeprom.
 * The data can be put in any specअगरied memory buffer.
 *
 * Returns -1 on error.
 * Returns address of next memory location on success.
 */
अटल पूर्णांक ar9300_eeprom_restore_पूर्णांकernal(काष्ठा ath_hw *ah,
					  u8 *mptr, पूर्णांक mdata_size)
अणु
#घोषणा MDEFAULT 15
#घोषणा MSTATE 100
	पूर्णांक cptr;
	u8 *word;
	पूर्णांक code;
	पूर्णांक reference, length, major, minor;
	पूर्णांक osize;
	पूर्णांक it;
	u16 checksum, mchecksum;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar9300_eeprom *eep;
	eeprom_पढ़ो_op पढ़ो;

	अगर (ath9k_hw_use_flash(ah)) अणु
		u8 txrx;

		अगर (ar9300_eeprom_restore_flash(ah, mptr, mdata_size))
			वापस -EIO;

		/* check अगर eeprom contains valid data */
		eep = (काष्ठा ar9300_eeprom *) mptr;
		txrx = eep->baseEepHeader.txrxMask;
		अगर (txrx != 0 && txrx != 0xff)
			वापस 0;
	पूर्ण

	word = kzalloc(2048, GFP_KERNEL);
	अगर (!word)
		वापस -ENOMEM;

	स_नकल(mptr, &ar9300_शेष, mdata_size);

	पढ़ो = ar9300_पढ़ो_eeprom;
	अगर (AR_SREV_9485(ah))
		cptr = AR9300_BASE_ADDR_4K;
	अन्यथा अगर (AR_SREV_9330(ah))
		cptr = AR9300_BASE_ADDR_512;
	अन्यथा
		cptr = AR9300_BASE_ADDR;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	अगर (ar9300_check_eeprom_header(ah, पढ़ो, cptr))
		जाओ found;

	cptr = AR9300_BASE_ADDR_4K;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	अगर (ar9300_check_eeprom_header(ah, पढ़ो, cptr))
		जाओ found;

	cptr = AR9300_BASE_ADDR_512;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	अगर (ar9300_check_eeprom_header(ah, पढ़ो, cptr))
		जाओ found;

	पढ़ो = ar9300_पढ़ो_otp;
	cptr = AR9300_BASE_ADDR;
	ath_dbg(common, EEPROM, "Trying OTP access at Address 0x%04x\n", cptr);
	अगर (ar9300_check_eeprom_header(ah, पढ़ो, cptr))
		जाओ found;

	cptr = AR9300_BASE_ADDR_512;
	ath_dbg(common, EEPROM, "Trying OTP access at Address 0x%04x\n", cptr);
	अगर (ar9300_check_eeprom_header(ah, पढ़ो, cptr))
		जाओ found;

	जाओ fail;

found:
	ath_dbg(common, EEPROM, "Found valid EEPROM data\n");

	क्रम (it = 0; it < MSTATE; it++) अणु
		अगर (!पढ़ो(ah, cptr, word, COMP_HDR_LEN))
			जाओ fail;

		अगर (!ar9300_check_header(word))
			अवरोध;

		ar9300_comp_hdr_unpack(word, &code, &reference,
				       &length, &major, &minor);
		ath_dbg(common, EEPROM,
			"Found block at %x: code=%d ref=%d length=%d major=%d minor=%d\n",
			cptr, code, reference, length, major, minor);
		अगर ((!AR_SREV_9485(ah) && length >= 1024) ||
		    (AR_SREV_9485(ah) && length > EEPROM_DATA_LEN_9485)) अणु
			ath_dbg(common, EEPROM, "Skipping bad header\n");
			cptr -= COMP_HDR_LEN;
			जारी;
		पूर्ण

		osize = length;
		पढ़ो(ah, cptr, word, COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
		checksum = ar9300_comp_cksum(&word[COMP_HDR_LEN], length);
		mchecksum = get_unaligned_le16(&word[COMP_HDR_LEN + osize]);
		ath_dbg(common, EEPROM, "checksum %x %x\n",
			checksum, mchecksum);
		अगर (checksum == mchecksum) अणु
			ar9300_compress_decision(ah, it, code, reference, mptr,
						 word, length, mdata_size);
		पूर्ण अन्यथा अणु
			ath_dbg(common, EEPROM,
				"skipping block with bad checksum\n");
		पूर्ण
		cptr -= (COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
	पूर्ण

	kमुक्त(word);
	वापस cptr;

fail:
	kमुक्त(word);
	वापस -1;
पूर्ण

/*
 * Restore the configuration काष्ठाure by पढ़ोing the eeprom.
 * This function destroys any existing in-memory काष्ठाure
 * content.
 */
अटल bool ath9k_hw_ar9300_fill_eeprom(काष्ठा ath_hw *ah)
अणु
	u8 *mptr = (u8 *) &ah->eeprom.ar9300_eep;

	अगर (ar9300_eeprom_restore_पूर्णांकernal(ah, mptr,
			माप(काष्ठा ar9300_eeprom)) < 0)
		वापस false;

	वापस true;
पूर्ण

#अगर defined(CONFIG_ATH9K_DEBUGFS) || defined(CONFIG_ATH9K_HTC_DEBUGFS)
अटल u32 ar9003_dump_modal_eeprom(अक्षर *buf, u32 len, u32 size,
				    काष्ठा ar9300_modal_eep_header *modal_hdr)
अणु
	PR_EEP("Chain0 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[0]));
	PR_EEP("Chain1 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[1]));
	PR_EEP("Chain2 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[2]));
	PR_EEP("Ant. Common Control", le32_to_cpu(modal_hdr->antCtrlCommon));
	PR_EEP("Ant. Common Control2", le32_to_cpu(modal_hdr->antCtrlCommon2));
	PR_EEP("Ant. Gain", modal_hdr->antennaGain);
	PR_EEP("Switch Settle", modal_hdr->चयनSettling);
	PR_EEP("Chain0 xatten1DB", modal_hdr->xatten1DB[0]);
	PR_EEP("Chain1 xatten1DB", modal_hdr->xatten1DB[1]);
	PR_EEP("Chain2 xatten1DB", modal_hdr->xatten1DB[2]);
	PR_EEP("Chain0 xatten1Margin", modal_hdr->xatten1Margin[0]);
	PR_EEP("Chain1 xatten1Margin", modal_hdr->xatten1Margin[1]);
	PR_EEP("Chain2 xatten1Margin", modal_hdr->xatten1Margin[2]);
	PR_EEP("Temp Slope", modal_hdr->tempSlope);
	PR_EEP("Volt Slope", modal_hdr->voltSlope);
	PR_EEP("spur Channels0", modal_hdr->spurChans[0]);
	PR_EEP("spur Channels1", modal_hdr->spurChans[1]);
	PR_EEP("spur Channels2", modal_hdr->spurChans[2]);
	PR_EEP("spur Channels3", modal_hdr->spurChans[3]);
	PR_EEP("spur Channels4", modal_hdr->spurChans[4]);
	PR_EEP("Chain0 NF Threshold", modal_hdr->noiseFloorThreshCh[0]);
	PR_EEP("Chain1 NF Threshold", modal_hdr->noiseFloorThreshCh[1]);
	PR_EEP("Chain2 NF Threshold", modal_hdr->noiseFloorThreshCh[2]);
	PR_EEP("Quick Drop", modal_hdr->quick_drop);
	PR_EEP("txEndToXpaOff", modal_hdr->txEndToXpaOff);
	PR_EEP("xPA Bias Level", modal_hdr->xpaBiasLvl);
	PR_EEP("txFrameToDataStart", modal_hdr->txFrameToDataStart);
	PR_EEP("txFrameToPaOn", modal_hdr->txFrameToPaOn);
	PR_EEP("txFrameToXpaOn", modal_hdr->txFrameToXpaOn);
	PR_EEP("txClip", modal_hdr->txClip);
	PR_EEP("ADC Desired size", modal_hdr->adcDesiredSize);

	वापस len;
पूर्ण

अटल u32 ar9003_dump_cal_data(काष्ठा ath_hw *ah, अक्षर *buf, u32 len, u32 size,
				bool is_2g)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase;
	काष्ठा ar9300_cal_data_per_freq_op_loop *cal_pier;
	पूर्णांक cal_pier_nr;
	पूर्णांक freq;
	पूर्णांक i, j;

	pBase = &eep->baseEepHeader;

	अगर (is_2g)
		cal_pier_nr = AR9300_NUM_2G_CAL_PIERS;
	अन्यथा
		cal_pier_nr = AR9300_NUM_5G_CAL_PIERS;

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (!((pBase->txrxMask >> i) & 1))
			जारी;

		len += scnम_लिखो(buf + len, size - len, "Chain %d\n", i);

		len += scnम_लिखो(buf + len, size - len,
			"Freq\t ref\tvolt\ttemp\tnf_cal\tnf_pow\trx_temp\n");

		क्रम (j = 0; j < cal_pier_nr; j++) अणु
			अगर (is_2g) अणु
				cal_pier = &eep->calPierData2G[i][j];
				freq = 2300 + eep->calFreqPier2G[j];
			पूर्ण अन्यथा अणु
				cal_pier = &eep->calPierData5G[i][j];
				freq = 4800 + eep->calFreqPier5G[j] * 5;
			पूर्ण

			len += scnम_लिखो(buf + len, size - len,
				"%d\t", freq);

			len += scnम_लिखो(buf + len, size - len,
				"%d\t%d\t%d\t%d\t%d\t%d\n",
				cal_pier->refPower,
				cal_pier->voltMeas,
				cal_pier->tempMeas,
				cal_pier->rxTempMeas ?
				N2DBM(cal_pier->rxNoiseन्यूनमानCal) : 0,
				cal_pier->rxTempMeas ?
				N2DBM(cal_pier->rxNoiseन्यूनमानPower) : 0,
				cal_pier->rxTempMeas);
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल u32 ath9k_hw_ar9003_dump_eeprom(काष्ठा ath_hw *ah, bool dump_base_hdr,
				       u8 *buf, u32 len, u32 size)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase;

	अगर (!dump_base_hdr) अणु
		len += scnम_लिखो(buf + len, size - len,
				 "%20s :\n", "2GHz modal Header");
		len = ar9003_dump_modal_eeprom(buf, len, size,
						&eep->modalHeader2G);

		len += scnम_लिखो(buf + len, size - len, "Calibration data\n");
		len = ar9003_dump_cal_data(ah, buf, len, size, true);

		len += scnम_लिखो(buf + len, size - len,
				 "%20s :\n", "5GHz modal Header");
		len = ar9003_dump_modal_eeprom(buf, len, size,
						&eep->modalHeader5G);

		len += scnम_लिखो(buf + len, size - len, "Calibration data\n");
		len = ar9003_dump_cal_data(ah, buf, len, size, false);

		जाओ out;
	पूर्ण

	pBase = &eep->baseEepHeader;

	PR_EEP("EEPROM Version", ah->eeprom.ar9300_eep.eepromVersion);
	PR_EEP("RegDomain1", le16_to_cpu(pBase->regDmn[0]));
	PR_EEP("RegDomain2", le16_to_cpu(pBase->regDmn[1]));
	PR_EEP("TX Mask", (pBase->txrxMask >> 4));
	PR_EEP("RX Mask", (pBase->txrxMask & 0x0f));
	PR_EEP("Allow 5GHz", !!(pBase->opCapFlags.opFlags &
				AR5416_OPFLAGS_11A));
	PR_EEP("Allow 2GHz", !!(pBase->opCapFlags.opFlags &
				AR5416_OPFLAGS_11G));
	PR_EEP("Disable 2GHz HT20", !!(pBase->opCapFlags.opFlags &
					AR5416_OPFLAGS_N_2G_HT20));
	PR_EEP("Disable 2GHz HT40", !!(pBase->opCapFlags.opFlags &
					AR5416_OPFLAGS_N_2G_HT40));
	PR_EEP("Disable 5Ghz HT20", !!(pBase->opCapFlags.opFlags &
					AR5416_OPFLAGS_N_5G_HT20));
	PR_EEP("Disable 5Ghz HT40", !!(pBase->opCapFlags.opFlags &
					AR5416_OPFLAGS_N_5G_HT40));
	PR_EEP("Big Endian", !!(pBase->opCapFlags.eepMisc &
				AR5416_EEPMISC_BIG_ENDIAN));
	PR_EEP("RF Silent", pBase->rfSilent);
	PR_EEP("BT option", pBase->blueToothOptions);
	PR_EEP("Device Cap", pBase->deviceCap);
	PR_EEP("Device Type", pBase->deviceType);
	PR_EEP("Power Table Offset", pBase->pwrTableOffset);
	PR_EEP("Tuning Caps1", pBase->params_क्रम_tuning_caps[0]);
	PR_EEP("Tuning Caps2", pBase->params_क्रम_tuning_caps[1]);
	PR_EEP("Enable Tx Temp Comp", !!(pBase->featureEnable & BIT(0)));
	PR_EEP("Enable Tx Volt Comp", !!(pBase->featureEnable & BIT(1)));
	PR_EEP("Enable fast clock", !!(pBase->featureEnable & BIT(2)));
	PR_EEP("Enable doubling", !!(pBase->featureEnable & BIT(3)));
	PR_EEP("Internal regulator", !!(pBase->featureEnable & BIT(4)));
	PR_EEP("Enable Paprd", !!(pBase->featureEnable & BIT(5)));
	PR_EEP("Driver Strength", !!(pBase->miscConfiguration & BIT(0)));
	PR_EEP("Quick Drop", !!(pBase->miscConfiguration & BIT(1)));
	PR_EEP("Chain mask Reduce", (pBase->miscConfiguration >> 0x3) & 0x1);
	PR_EEP("Write enable Gpio", pBase->eepromWriteEnableGpio);
	PR_EEP("WLAN Disable Gpio", pBase->wlanDisableGpio);
	PR_EEP("WLAN LED Gpio", pBase->wlanLedGpio);
	PR_EEP("Rx Band Select Gpio", pBase->rxBandSelectGpio);
	PR_EEP("Tx Gain", pBase->txrxgain >> 4);
	PR_EEP("Rx Gain", pBase->txrxgain & 0xf);
	PR_EEP("SW Reg", le32_to_cpu(pBase->swreg));

	len += scnम_लिखो(buf + len, size - len, "%20s : %pM\n", "MacAddress",
			 ah->eeprom.ar9300_eep.macAddr);
out:
	अगर (len > size)
		len = size;

	वापस len;
पूर्ण
#अन्यथा
अटल u32 ath9k_hw_ar9003_dump_eeprom(काष्ठा ath_hw *ah, bool dump_base_hdr,
				       u8 *buf, u32 len, u32 size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* XXX: review hardware करोcs */
अटल पूर्णांक ath9k_hw_ar9300_get_eeprom_ver(काष्ठा ath_hw *ah)
अणु
	वापस ah->eeprom.ar9300_eep.eepromVersion;
पूर्ण

/* XXX: could be पढ़ो from the eepromVersion, not sure yet */
अटल पूर्णांक ath9k_hw_ar9300_get_eeprom_rev(काष्ठा ath_hw *ah)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा ar9300_modal_eep_header *ar9003_modal_header(काष्ठा ath_hw *ah,
							   bool is2ghz)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	अगर (is2ghz)
		वापस &eep->modalHeader2G;
	अन्यथा
		वापस &eep->modalHeader5G;
पूर्ण

अटल व्योम ar9003_hw_xpa_bias_level_apply(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	पूर्णांक bias = ar9003_modal_header(ah, is2ghz)->xpaBiasLvl;

	अगर (AR_SREV_9485(ah) || AR_SREV_9330(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9531(ah) || AR_SREV_9561(ah))
		REG_RMW_FIELD(ah, AR_CH0_TOP2, AR_CH0_TOP2_XPABIASLVL, bias);
	अन्यथा अगर (AR_SREV_9462(ah) || AR_SREV_9550(ah) || AR_SREV_9565(ah))
		REG_RMW_FIELD(ah, AR_CH0_TOP, AR_CH0_TOP_XPABIASLVL, bias);
	अन्यथा अणु
		REG_RMW_FIELD(ah, AR_CH0_TOP, AR_CH0_TOP_XPABIASLVL, bias);
		REG_RMW_FIELD(ah, AR_CH0_THERM,
				AR_CH0_THERM_XPABIASLVL_MSB,
				bias >> 2);
		REG_RMW_FIELD(ah, AR_CH0_THERM,
				AR_CH0_THERM_XPASHORT2GND, 1);
	पूर्ण
पूर्ण

अटल u16 ar9003_चयन_com_spdt_get(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	वापस le16_to_cpu(ar9003_modal_header(ah, is2ghz)->चयनcomspdt);
पूर्ण

u32 ar9003_hw_ant_ctrl_common_get(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	वापस le32_to_cpu(ar9003_modal_header(ah, is2ghz)->antCtrlCommon);
पूर्ण

u32 ar9003_hw_ant_ctrl_common_2_get(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	वापस le32_to_cpu(ar9003_modal_header(ah, is2ghz)->antCtrlCommon2);
पूर्ण

अटल u16 ar9003_hw_ant_ctrl_chain_get(काष्ठा ath_hw *ah, पूर्णांक chain,
					bool is2ghz)
अणु
	__le16 val = ar9003_modal_header(ah, is2ghz)->antCtrlChain[chain];
	वापस le16_to_cpu(val);
पूर्ण

अटल व्योम ar9003_hw_ant_ctrl_apply(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	पूर्णांक chain;
	u32 regval, value, gpio;
	अटल स्थिर u32 चयन_chain_reg[AR9300_MAX_CHAINS] = अणु
			AR_PHY_SWITCH_CHAIN_0,
			AR_PHY_SWITCH_CHAIN_1,
			AR_PHY_SWITCH_CHAIN_2,
	पूर्ण;

	अगर (AR_SREV_9485(ah) && (ar9003_hw_get_rx_gain_idx(ah) == 0)) अणु
		अगर (ah->config.xlna_gpio)
			gpio = ah->config.xlna_gpio;
		अन्यथा
			gpio = AR9300_EXT_LNA_CTL_GPIO_AR9485;

		ath9k_hw_gpio_request_out(ah, gpio, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_LED);
	पूर्ण

	value = ar9003_hw_ant_ctrl_common_get(ah, is2ghz);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		REG_RMW_FIELD(ah, AR_PHY_SWITCH_COM,
				AR_SWITCH_TABLE_COM_AR9462_ALL, value);
	पूर्ण अन्यथा अगर (AR_SREV_9550(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah)) अणु
		REG_RMW_FIELD(ah, AR_PHY_SWITCH_COM,
				AR_SWITCH_TABLE_COM_AR9550_ALL, value);
	पूर्ण अन्यथा
		REG_RMW_FIELD(ah, AR_PHY_SWITCH_COM,
			      AR_SWITCH_TABLE_COM_ALL, value);


	/*
	 *   AR9462 defines new चयन table क्रम BT/WLAN,
	 *       here's new field name in XXX.ref क्रम both 2G and 5G.
	 *   Register: [GLB_CONTROL] GLB_CONTROL (@0x20044)
	 *   15:12   R/W     SWITCH_TABLE_COM_SPDT_WLAN_RX
	 * SWITCH_TABLE_COM_SPDT_WLAN_RX
	 *
	 *   11:8     R/W     SWITCH_TABLE_COM_SPDT_WLAN_TX
	 * SWITCH_TABLE_COM_SPDT_WLAN_TX
	 *
	 *   7:4 R/W  SWITCH_TABLE_COM_SPDT_WLAN_IDLE
	 * SWITCH_TABLE_COM_SPDT_WLAN_IDLE
	 */
	अगर (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565(ah)) अणु
		value = ar9003_चयन_com_spdt_get(ah, is2ghz);
		REG_RMW_FIELD(ah, AR_PHY_GLB_CONTROL,
				AR_SWITCH_TABLE_COM_SPDT_ALL, value);
		REG_SET_BIT(ah, AR_PHY_GLB_CONTROL, AR_BTCOEX_CTRL_SPDT_ENABLE);
	पूर्ण

	value = ar9003_hw_ant_ctrl_common_2_get(ah, is2ghz);
	अगर (AR_SREV_9485(ah) && common->bt_ant_भागersity) अणु
		value &= ~AR_SWITCH_TABLE_COM2_ALL;
		value |= ah->config.ant_ctrl_comm2g_चयन_enable;

	पूर्ण
	REG_RMW_FIELD(ah, AR_PHY_SWITCH_COM_2, AR_SWITCH_TABLE_COM2_ALL, value);

	अगर ((AR_SREV_9462(ah)) && (ah->rxchainmask == 0x2)) अणु
		value = ar9003_hw_ant_ctrl_chain_get(ah, 1, is2ghz);
		REG_RMW_FIELD(ah, चयन_chain_reg[0],
			      AR_SWITCH_TABLE_ALL, value);
	पूर्ण

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर ((ah->rxchainmask & BIT(chain)) ||
		    (ah->txchainmask & BIT(chain))) अणु
			value = ar9003_hw_ant_ctrl_chain_get(ah, chain,
							     is2ghz);
			REG_RMW_FIELD(ah, चयन_chain_reg[chain],
				      AR_SWITCH_TABLE_ALL, value);
		पूर्ण
	पूर्ण

	अगर (AR_SREV_9330(ah) || AR_SREV_9485(ah) || AR_SREV_9565(ah)) अणु
		value = ath9k_hw_ar9300_get_eeprom(ah, EEP_ANT_DIV_CTL1);
		/*
		 * मुख्य_lnaconf, alt_lnaconf, मुख्य_tb, alt_tb
		 * are the fields present
		 */
		regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
		regval &= (~AR_ANT_DIV_CTRL_ALL);
		regval |= (value & 0x3f) << AR_ANT_DIV_CTRL_ALL_S;
		/* enable_lnaभाग */
		regval &= (~AR_PHY_ANT_DIV_LNADIV);
		regval |= ((value >> 6) & 0x1) << AR_PHY_ANT_DIV_LNADIV_S;

		अगर (AR_SREV_9485(ah) && common->bt_ant_भागersity)
			regval |= AR_ANT_DIV_ENABLE;

		अगर (AR_SREV_9565(ah)) अणु
			अगर (common->bt_ant_भागersity) अणु
				regval |= (1 << AR_PHY_ANT_SW_RX_PROT_S);

				REG_SET_BIT(ah, AR_PHY_RESTART,
					    AR_PHY_RESTART_ENABLE_DIV_M2FLAG);

				/* Force WLAN LNA भागersity ON */
				REG_SET_BIT(ah, AR_BTCOEX_WL_LNADIV,
					    AR_BTCOEX_WL_LNADIV_FORCE_ON);
			पूर्ण अन्यथा अणु
				regval &= ~(1 << AR_PHY_ANT_DIV_LNADIV_S);
				regval &= ~(1 << AR_PHY_ANT_SW_RX_PROT_S);

				REG_CLR_BIT(ah, AR_PHY_MC_GAIN_CTRL,
					    (1 << AR_PHY_ANT_SW_RX_PROT_S));

				/* Force WLAN LNA भागersity OFF */
				REG_CLR_BIT(ah, AR_BTCOEX_WL_LNADIV,
					    AR_BTCOEX_WL_LNADIV_FORCE_ON);
			पूर्ण
		पूर्ण

		REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);

		/* enable fast_भाग */
		regval = REG_READ(ah, AR_PHY_CCK_DETECT);
		regval &= (~AR_FAST_DIV_ENABLE);
		regval |= ((value >> 7) & 0x1) << AR_FAST_DIV_ENABLE_S;

		अगर ((AR_SREV_9485(ah) || AR_SREV_9565(ah))
		    && common->bt_ant_भागersity)
			regval |= AR_FAST_DIV_ENABLE;

		REG_WRITE(ah, AR_PHY_CCK_DETECT, regval);

		अगर (pCap->hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB) अणु
			regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
			/*
			 * clear bits 25-30 मुख्य_lnaconf, alt_lnaconf,
			 * मुख्य_tb, alt_tb
			 */
			regval &= (~(AR_PHY_ANT_DIV_MAIN_LNACONF |
				     AR_PHY_ANT_DIV_ALT_LNACONF |
				     AR_PHY_ANT_DIV_ALT_GAINTB |
				     AR_PHY_ANT_DIV_MAIN_GAINTB));
			/* by शेष use LNA1 क्रम the मुख्य antenna */
			regval |= (ATH_ANT_DIV_COMB_LNA1 <<
				   AR_PHY_ANT_DIV_MAIN_LNACONF_S);
			regval |= (ATH_ANT_DIV_COMB_LNA2 <<
				   AR_PHY_ANT_DIV_ALT_LNACONF_S);
			REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_drive_strength_apply(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	पूर्णांक drive_strength;
	अचिन्हित दीर्घ reg;

	drive_strength = pBase->miscConfiguration & BIT(0);
	अगर (!drive_strength)
		वापस;

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS1);
	reg &= ~0x00ffffc0;
	reg |= 0x5 << 21;
	reg |= 0x5 << 18;
	reg |= 0x5 << 15;
	reg |= 0x5 << 12;
	reg |= 0x5 << 9;
	reg |= 0x5 << 6;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS1, reg);

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS2);
	reg &= ~0xffffffe0;
	reg |= 0x5 << 29;
	reg |= 0x5 << 26;
	reg |= 0x5 << 23;
	reg |= 0x5 << 20;
	reg |= 0x5 << 17;
	reg |= 0x5 << 14;
	reg |= 0x5 << 11;
	reg |= 0x5 << 8;
	reg |= 0x5 << 5;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS2, reg);

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS4);
	reg &= ~0xff800000;
	reg |= 0x5 << 29;
	reg |= 0x5 << 26;
	reg |= 0x5 << 23;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS4, reg);
पूर्ण

अटल u16 ar9003_hw_atten_chain_get(काष्ठा ath_hw *ah, पूर्णांक chain,
				     काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक f[3], t[3];
	u16 value;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	अगर (chain >= 0 && chain < 3) अणु
		अगर (IS_CHAN_2GHZ(chan))
			वापस eep->modalHeader2G.xatten1DB[chain];
		अन्यथा अगर (eep->base_ext2.xatten1DBLow[chain] != 0) अणु
			t[0] = eep->base_ext2.xatten1DBLow[chain];
			f[0] = 5180;
			t[1] = eep->modalHeader5G.xatten1DB[chain];
			f[1] = 5500;
			t[2] = eep->base_ext2.xatten1DBHigh[chain];
			f[2] = 5785;
			value = ar9003_hw_घातer_पूर्णांकerpolate((s32) chan->channel,
							    f, t, 3);
			वापस value;
		पूर्ण अन्यथा
			वापस eep->modalHeader5G.xatten1DB[chain];
	पूर्ण

	वापस 0;
पूर्ण


अटल u16 ar9003_hw_atten_chain_get_margin(काष्ठा ath_hw *ah, पूर्णांक chain,
					    काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक f[3], t[3];
	u16 value;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	अगर (chain >= 0 && chain < 3) अणु
		अगर (IS_CHAN_2GHZ(chan))
			वापस eep->modalHeader2G.xatten1Margin[chain];
		अन्यथा अगर (eep->base_ext2.xatten1MarginLow[chain] != 0) अणु
			t[0] = eep->base_ext2.xatten1MarginLow[chain];
			f[0] = 5180;
			t[1] = eep->modalHeader5G.xatten1Margin[chain];
			f[1] = 5500;
			t[2] = eep->base_ext2.xatten1MarginHigh[chain];
			f[2] = 5785;
			value = ar9003_hw_घातer_पूर्णांकerpolate((s32) chan->channel,
							    f, t, 3);
			वापस value;
		पूर्ण अन्यथा
			वापस eep->modalHeader5G.xatten1Margin[chain];
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ar9003_hw_atten_apply(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक i;
	u16 value;
	अचिन्हित दीर्घ ext_atten_reg[3] = अणुAR_PHY_EXT_ATTEN_CTL_0,
					  AR_PHY_EXT_ATTEN_CTL_1,
					  AR_PHY_EXT_ATTEN_CTL_2,
					 पूर्ण;

	अगर ((AR_SREV_9462(ah)) && (ah->rxchainmask == 0x2)) अणु
		value = ar9003_hw_atten_chain_get(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

		value = ar9003_hw_atten_chain_get_margin(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
			      value);
	पूर्ण

	/* Test value. अगर 0 then attenuation is unused. Don't load anything. */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (ah->txchainmask & BIT(i)) अणु
			value = ar9003_hw_atten_chain_get(ah, i, chan);
			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

			अगर (AR_SREV_9485(ah) &&
			    (ar9003_hw_get_rx_gain_idx(ah) == 0) &&
			    ah->config.xatten_margin_cfg)
				value = 5;
			अन्यथा
				value = ar9003_hw_atten_chain_get_margin(ah, i, chan);

			अगर (ah->config.alt_mingainidx)
				REG_RMW_FIELD(ah, AR_PHY_EXT_ATTEN_CTL_0,
					      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
					      value);

			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
				      value);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool is_pmu_set(काष्ठा ath_hw *ah, u32 pmu_reg, पूर्णांक pmu_set)
अणु
	पूर्णांक समयout = 100;

	जबतक (pmu_set != REG_READ(ah, pmu_reg)) अणु
		अगर (समयout-- == 0)
			वापस false;
		REG_WRITE(ah, pmu_reg, pmu_set);
		udelay(10);
	पूर्ण

	वापस true;
पूर्ण

व्योम ar9003_hw_पूर्णांकernal_regulator_apply(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	u32 reg_val;

	अगर (pBase->featureEnable & BIT(4)) अणु
		अगर (AR_SREV_9330(ah) || AR_SREV_9485(ah)) अणु
			पूर्णांक reg_pmu_set;

			reg_pmu_set = REG_READ(ah, AR_PHY_PMU2) & ~AR_PHY_PMU2_PGM;
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			अगर (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				वापस;

			अगर (AR_SREV_9330(ah)) अणु
				अगर (ah->is_clk_25mhz) अणु
					reg_pmu_set = (3 << 1) | (8 << 4) |
						      (3 << 8) | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				पूर्ण अन्यथा अणु
					reg_pmu_set = (4 << 1)  | (7 << 4) |
						      (3 << 8)  | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				पूर्ण
			पूर्ण अन्यथा अणु
				reg_pmu_set = (5 << 1) | (7 << 4) |
					      (2 << 8) | (2 << 14) |
					      (6 << 17) | (1 << 20) |
					      (3 << 24) | (1 << 28);
			पूर्ण

			REG_WRITE(ah, AR_PHY_PMU1, reg_pmu_set);
			अगर (!is_pmu_set(ah, AR_PHY_PMU1, reg_pmu_set))
				वापस;

			reg_pmu_set = (REG_READ(ah, AR_PHY_PMU2) & ~0xFFC00000)
					| (4 << 26);
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			अगर (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				वापस;

			reg_pmu_set = (REG_READ(ah, AR_PHY_PMU2) & ~0x00200000)
					| (1 << 21);
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			अगर (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				वापस;
		पूर्ण अन्यथा अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah) ||
			   AR_SREV_9561(ah)) अणु
			reg_val = le32_to_cpu(pBase->swreg);
			REG_WRITE(ah, AR_PHY_PMU1, reg_val);

			अगर (AR_SREV_9561(ah))
				REG_WRITE(ah, AR_PHY_PMU2, 0x10200000);
		पूर्ण अन्यथा अणु
			/* Internal regulator is ON. Write swreg रेजिस्टर. */
			reg_val = le32_to_cpu(pBase->swreg);
			REG_WRITE(ah, AR_RTC_REG_CONTROL1,
				  REG_READ(ah, AR_RTC_REG_CONTROL1) &
				  (~AR_RTC_REG_CONTROL1_SWREG_PROGRAM));
			REG_WRITE(ah, AR_RTC_REG_CONTROL0, reg_val);
			/* Set REG_CONTROL1.SWREG_PROGRAM */
			REG_WRITE(ah, AR_RTC_REG_CONTROL1,
				  REG_READ(ah,
					   AR_RTC_REG_CONTROL1) |
					   AR_RTC_REG_CONTROL1_SWREG_PROGRAM);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (AR_SREV_9330(ah) || AR_SREV_9485(ah)) अणु
			REG_RMW_FIELD(ah, AR_PHY_PMU2, AR_PHY_PMU2_PGM, 0);
			जबतक (REG_READ_FIELD(ah, AR_PHY_PMU2,
						AR_PHY_PMU2_PGM))
				udelay(10);

			REG_RMW_FIELD(ah, AR_PHY_PMU1, AR_PHY_PMU1_PWD, 0x1);
			जबतक (!REG_READ_FIELD(ah, AR_PHY_PMU1,
						AR_PHY_PMU1_PWD))
				udelay(10);
			REG_RMW_FIELD(ah, AR_PHY_PMU2, AR_PHY_PMU2_PGM, 0x1);
			जबतक (!REG_READ_FIELD(ah, AR_PHY_PMU2,
						AR_PHY_PMU2_PGM))
				udelay(10);
		पूर्ण अन्यथा अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			REG_RMW_FIELD(ah, AR_PHY_PMU1, AR_PHY_PMU1_PWD, 0x1);
		अन्यथा अणु
			reg_val = REG_READ(ah, AR_RTC_SLEEP_CLK) |
				AR_RTC_FORCE_SWREG_PRD;
			REG_WRITE(ah, AR_RTC_SLEEP_CLK, reg_val);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम ar9003_hw_apply_tuning_caps(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 tuning_caps_param = eep->baseEepHeader.params_क्रम_tuning_caps[0];

	अगर (AR_SREV_9340(ah) || AR_SREV_9531(ah))
		वापस;

	अगर (eep->baseEepHeader.featureEnable & 0x40) अणु
		tuning_caps_param &= 0x7f;
		REG_RMW_FIELD(ah, AR_CH0_XTAL, AR_CH0_XTAL_CAPINDAC,
			      tuning_caps_param);
		REG_RMW_FIELD(ah, AR_CH0_XTAL, AR_CH0_XTAL_CAPOUTDAC,
			      tuning_caps_param);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_quick_drop_apply(काष्ठा ath_hw *ah, u16 freq)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	पूर्णांक quick_drop;
	s32 t[3], f[3] = अणु5180, 5500, 5785पूर्ण;

	अगर (!(pBase->miscConfiguration & BIT(4)))
		वापस;

	अगर (AR_SREV_9300(ah) || AR_SREV_9580(ah) || AR_SREV_9340(ah)) अणु
		अगर (freq < 4000) अणु
			quick_drop = eep->modalHeader2G.quick_drop;
		पूर्ण अन्यथा अणु
			t[0] = eep->base_ext1.quick_drop_low;
			t[1] = eep->modalHeader5G.quick_drop;
			t[2] = eep->base_ext1.quick_drop_high;
			quick_drop = ar9003_hw_घातer_पूर्णांकerpolate(freq, f, t, 3);
		पूर्ण
		REG_RMW_FIELD(ah, AR_PHY_AGC, AR_PHY_AGC_QUICK_DROP, quick_drop);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_txend_to_xpa_off_apply(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	u32 value;

	value = ar9003_modal_header(ah, is2ghz)->txEndToXpaOff;

	REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
		      AR_PHY_XPA_TIMING_CTL_TX_END_XPAB_OFF, value);
	REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
		      AR_PHY_XPA_TIMING_CTL_TX_END_XPAA_OFF, value);
पूर्ण

अटल व्योम ar9003_hw_xpa_timing_control_apply(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 xpa_ctl;

	अगर (!(eep->baseEepHeader.featureEnable & 0x80))
		वापस;

	अगर (!AR_SREV_9300(ah) &&
	    !AR_SREV_9340(ah) &&
	    !AR_SREV_9580(ah) &&
	    !AR_SREV_9531(ah) &&
	    !AR_SREV_9561(ah))
		वापस;

	xpa_ctl = ar9003_modal_header(ah, is2ghz)->txFrameToXpaOn;
	अगर (is2ghz)
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAB_ON, xpa_ctl);
	अन्यथा
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAA_ON, xpa_ctl);
पूर्ण

अटल व्योम ar9003_hw_xlna_bias_strength_apply(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 bias;

	अगर (!(eep->baseEepHeader.miscConfiguration & 0x40))
		वापस;

	अगर (!AR_SREV_9300(ah))
		वापस;

	bias = ar9003_modal_header(ah, is2ghz)->xlna_bias_strength;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
पूर्ण

अटल पूर्णांक ar9003_hw_get_thermometer(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	पूर्णांक thermometer =  (pBase->miscConfiguration >> 1) & 0x3;

	वापस --thermometer;
पूर्ण

अटल व्योम ar9003_hw_thermometer_apply(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	पूर्णांक thermometer = ar9003_hw_get_thermometer(ah);
	u8 therm_on = (thermometer < 0) ? 0 : 1;

	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4,
		      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);
	अगर (pCap->chip_chainmask & BIT(1))
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);
	अगर (pCap->chip_chainmask & BIT(2))
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);

	therm_on = thermometer == 0;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4,
		      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	अगर (pCap->chip_chainmask & BIT(1)) अणु
		therm_on = thermometer == 1;
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	पूर्ण
	अगर (pCap->chip_chainmask & BIT(2)) अणु
		therm_on = thermometer == 2;
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_thermo_cal_apply(काष्ठा ath_hw *ah)
अणु
	u32 data = 0, ko, kg;

	अगर (!AR_SREV_9462_20_OR_LATER(ah))
		वापस;

	ar9300_otp_पढ़ो_word(ah, 1, &data);
	ko = data & 0xff;
	kg = (data >> 8) & 0xff;
	अगर (ko || kg) अणु
		REG_RMW_FIELD(ah, AR_PHY_BB_THERM_ADC_3,
			      AR_PHY_BB_THERM_ADC_3_THERM_ADC_OFFSET, ko);
		REG_RMW_FIELD(ah, AR_PHY_BB_THERM_ADC_3,
			      AR_PHY_BB_THERM_ADC_3_THERM_ADC_SCALE_GAIN,
			      kg + 256);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_apply_minccapwr_thresh(काष्ठा ath_hw *ah,
					     bool is2ghz)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	स्थिर u_पूर्णांक32_t cca_ctrl[AR9300_MAX_CHAINS] = अणु
		AR_PHY_CCA_CTRL_0,
		AR_PHY_CCA_CTRL_1,
		AR_PHY_CCA_CTRL_2,
	पूर्ण;
	पूर्णांक chain;
	u32 val;

	अगर (is2ghz) अणु
		अगर (!(eep->base_ext1.misc_enable & BIT(2)))
			वापस;
	पूर्ण अन्यथा अणु
		अगर (!(eep->base_ext1.misc_enable & BIT(3)))
			वापस;
	पूर्ण

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->caps.tx_chainmask & BIT(chain)))
			जारी;

		val = ar9003_modal_header(ah, is2ghz)->noiseFloorThreshCh[chain];
		REG_RMW_FIELD(ah, cca_ctrl[chain],
			      AR_PHY_EXT_CCA0_THRESH62_1, val);
	पूर्ण

पूर्ण

अटल व्योम ath9k_hw_ar9300_set_board_values(काष्ठा ath_hw *ah,
					     काष्ठा ath9k_channel *chan)
अणु
	bool is2ghz = IS_CHAN_2GHZ(chan);
	ar9003_hw_xpa_timing_control_apply(ah, is2ghz);
	ar9003_hw_xpa_bias_level_apply(ah, is2ghz);
	ar9003_hw_ant_ctrl_apply(ah, is2ghz);
	ar9003_hw_drive_strength_apply(ah);
	ar9003_hw_xlna_bias_strength_apply(ah, is2ghz);
	ar9003_hw_atten_apply(ah, chan);
	ar9003_hw_quick_drop_apply(ah, chan->channel);
	अगर (!AR_SREV_9330(ah) && !AR_SREV_9340(ah) && !AR_SREV_9531(ah))
		ar9003_hw_पूर्णांकernal_regulator_apply(ah);
	ar9003_hw_apply_tuning_caps(ah);
	ar9003_hw_apply_minccapwr_thresh(ah, is2ghz);
	ar9003_hw_txend_to_xpa_off_apply(ah, is2ghz);
	ar9003_hw_thermometer_apply(ah);
	ar9003_hw_thermo_cal_apply(ah);
पूर्ण

अटल व्योम ath9k_hw_ar9300_set_addac(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *chan)
अणु
पूर्ण

/*
 * Returns the पूर्णांकerpolated y value corresponding to the specअगरied x value
 * from the np ordered pairs of data (px,py).
 * The pairs करो not have to be in any order.
 * If the specअगरied x value is less than any of the px,
 * the वापसed y value is equal to the py क्रम the lowest px.
 * If the specअगरied x value is greater than any of the px,
 * the वापसed y value is equal to the py क्रम the highest px.
 */
अटल पूर्णांक ar9003_hw_घातer_पूर्णांकerpolate(पूर्णांक32_t x,
				       पूर्णांक32_t *px, पूर्णांक32_t *py, u_पूर्णांक16_t np)
अणु
	पूर्णांक ip = 0;
	पूर्णांक lx = 0, ly = 0, lhave = 0;
	पूर्णांक hx = 0, hy = 0, hhave = 0;
	पूर्णांक dx = 0;
	पूर्णांक y = 0;

	lhave = 0;
	hhave = 0;

	/* identअगरy best lower and higher x calibration measurement */
	क्रम (ip = 0; ip < np; ip++) अणु
		dx = x - px[ip];

		/* this measurement is higher than our desired x */
		अगर (dx <= 0) अणु
			अगर (!hhave || dx > (x - hx)) अणु
				/* new best higher x measurement */
				hx = px[ip];
				hy = py[ip];
				hhave = 1;
			पूर्ण
		पूर्ण
		/* this measurement is lower than our desired x */
		अगर (dx >= 0) अणु
			अगर (!lhave || dx < (x - lx)) अणु
				/* new best lower x measurement */
				lx = px[ip];
				ly = py[ip];
				lhave = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* the low x is good */
	अगर (lhave) अणु
		/* so is the high x */
		अगर (hhave) अणु
			/* they're the same, so just pick one */
			अगर (hx == lx)
				y = ly;
			अन्यथा	/* पूर्णांकerpolate  */
				y = पूर्णांकerpolate(x, lx, hx, ly, hy);
		पूर्ण अन्यथा		/* only low is good, use it */
			y = ly;
	पूर्ण अन्यथा अगर (hhave)	/* only high is good, use it */
		y = hy;
	अन्यथा /* nothing is good,this should never happen unless np=0, ???? */
		y = -(1 << 30);
	वापस y;
पूर्ण

अटल u8 ar9003_hw_eeprom_get_tgt_pwr(काष्ठा ath_hw *ah,
				       u16 rateIndex, u16 freq, bool is2GHz)
अणु
	u16 numPiers, i;
	s32 targetPowerArray[AR9300_NUM_5G_20_TARGET_POWERS];
	s32 freqArray[AR9300_NUM_5G_20_TARGET_POWERS];
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा cal_tgt_घात_legacy *pEepromTargetPwr;
	u8 *pFreqBin;

	अगर (is2GHz) अणु
		numPiers = AR9300_NUM_2G_20_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower2G;
		pFreqBin = eep->calTarget_freqbin_2G;
	पूर्ण अन्यथा अणु
		numPiers = AR9300_NUM_5G_20_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower5G;
		pFreqBin = eep->calTarget_freqbin_5G;
	पूर्ण

	/*
	 * create array of channels and targetघातer from
	 * targetघातer piers stored on eeprom
	 */
	क्रम (i = 0; i < numPiers; i++) अणु
		freqArray[i] = ath9k_hw_fbin2freq(pFreqBin[i], is2GHz);
		targetPowerArray[i] = pEepromTargetPwr[i].tPow2x[rateIndex];
	पूर्ण

	/* पूर्णांकerpolate to get target घातer क्रम given frequency */
	वापस (u8) ar9003_hw_घातer_पूर्णांकerpolate((s32) freq,
						 freqArray,
						 targetPowerArray, numPiers);
पूर्ण

अटल u8 ar9003_hw_eeprom_get_ht20_tgt_pwr(काष्ठा ath_hw *ah,
					    u16 rateIndex,
					    u16 freq, bool is2GHz)
अणु
	u16 numPiers, i;
	s32 targetPowerArray[AR9300_NUM_5G_20_TARGET_POWERS];
	s32 freqArray[AR9300_NUM_5G_20_TARGET_POWERS];
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा cal_tgt_घात_ht *pEepromTargetPwr;
	u8 *pFreqBin;

	अगर (is2GHz) अणु
		numPiers = AR9300_NUM_2G_20_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower2GHT20;
		pFreqBin = eep->calTarget_freqbin_2GHT20;
	पूर्ण अन्यथा अणु
		numPiers = AR9300_NUM_5G_20_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower5GHT20;
		pFreqBin = eep->calTarget_freqbin_5GHT20;
	पूर्ण

	/*
	 * create array of channels and targetघातer
	 * from targetघातer piers stored on eeprom
	 */
	क्रम (i = 0; i < numPiers; i++) अणु
		freqArray[i] = ath9k_hw_fbin2freq(pFreqBin[i], is2GHz);
		targetPowerArray[i] = pEepromTargetPwr[i].tPow2x[rateIndex];
	पूर्ण

	/* पूर्णांकerpolate to get target घातer क्रम given frequency */
	वापस (u8) ar9003_hw_घातer_पूर्णांकerpolate((s32) freq,
						 freqArray,
						 targetPowerArray, numPiers);
पूर्ण

अटल u8 ar9003_hw_eeprom_get_ht40_tgt_pwr(काष्ठा ath_hw *ah,
					    u16 rateIndex,
					    u16 freq, bool is2GHz)
अणु
	u16 numPiers, i;
	s32 targetPowerArray[AR9300_NUM_5G_40_TARGET_POWERS];
	s32 freqArray[AR9300_NUM_5G_40_TARGET_POWERS];
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा cal_tgt_घात_ht *pEepromTargetPwr;
	u8 *pFreqBin;

	अगर (is2GHz) अणु
		numPiers = AR9300_NUM_2G_40_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower2GHT40;
		pFreqBin = eep->calTarget_freqbin_2GHT40;
	पूर्ण अन्यथा अणु
		numPiers = AR9300_NUM_5G_40_TARGET_POWERS;
		pEepromTargetPwr = eep->calTargetPower5GHT40;
		pFreqBin = eep->calTarget_freqbin_5GHT40;
	पूर्ण

	/*
	 * create array of channels and targetघातer from
	 * targetघातer piers stored on eeprom
	 */
	क्रम (i = 0; i < numPiers; i++) अणु
		freqArray[i] = ath9k_hw_fbin2freq(pFreqBin[i], is2GHz);
		targetPowerArray[i] = pEepromTargetPwr[i].tPow2x[rateIndex];
	पूर्ण

	/* पूर्णांकerpolate to get target घातer क्रम given frequency */
	वापस (u8) ar9003_hw_घातer_पूर्णांकerpolate((s32) freq,
						 freqArray,
						 targetPowerArray, numPiers);
पूर्ण

अटल u8 ar9003_hw_eeprom_get_cck_tgt_pwr(काष्ठा ath_hw *ah,
					   u16 rateIndex, u16 freq)
अणु
	u16 numPiers = AR9300_NUM_2G_CCK_TARGET_POWERS, i;
	s32 targetPowerArray[AR9300_NUM_2G_CCK_TARGET_POWERS];
	s32 freqArray[AR9300_NUM_2G_CCK_TARGET_POWERS];
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा cal_tgt_घात_legacy *pEepromTargetPwr = eep->calTargetPowerCck;
	u8 *pFreqBin = eep->calTarget_freqbin_Cck;

	/*
	 * create array of channels and targetघातer from
	 * targetघातer piers stored on eeprom
	 */
	क्रम (i = 0; i < numPiers; i++) अणु
		freqArray[i] = ath9k_hw_fbin2freq(pFreqBin[i], 1);
		targetPowerArray[i] = pEepromTargetPwr[i].tPow2x[rateIndex];
	पूर्ण

	/* पूर्णांकerpolate to get target घातer क्रम given frequency */
	वापस (u8) ar9003_hw_घातer_पूर्णांकerpolate((s32) freq,
						 freqArray,
						 targetPowerArray, numPiers);
पूर्ण

अटल व्योम ar9003_hw_selfgen_tpc_txघातer(काष्ठा ath_hw *ah,
					  काष्ठा ath9k_channel *chan,
					  u8 *pwr_array)
अणु
	u32 val;

	/* target घातer values क्रम self generated frames (ACK,RTS/CTS) */
	अगर (IS_CHAN_2GHZ(chan)) अणु
		val = SM(pwr_array[ALL_TARGET_LEGACY_1L_5L], AR_TPC_ACK) |
		      SM(pwr_array[ALL_TARGET_LEGACY_1L_5L], AR_TPC_CTS) |
		      SM(0x3f, AR_TPC_CHIRP) | SM(0x3f, AR_TPC_RPT);
	पूर्ण अन्यथा अणु
		val = SM(pwr_array[ALL_TARGET_LEGACY_6_24], AR_TPC_ACK) |
		      SM(pwr_array[ALL_TARGET_LEGACY_6_24], AR_TPC_CTS) |
		      SM(0x3f, AR_TPC_CHIRP) | SM(0x3f, AR_TPC_RPT);
	पूर्ण
	REG_WRITE(ah, AR_TPC, val);
पूर्ण

/* Set tx घातer रेजिस्टरs to array of values passed in */
पूर्णांक ar9003_hw_tx_घातer_regग_लिखो(काष्ठा ath_hw *ah, u8 * pPwrArray)
अणु
#घोषणा POW_SM(_r, _s)     (((_r) & 0x3f) << (_s))
	/* make sure क्रमced gain is not set */
	REG_WRITE(ah, AR_PHY_TX_FORCED_GAIN, 0);

	/* Write the OFDM घातer per rate set */

	/* 6 (LSB), 9, 12, 18 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(0),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 0));

	/* 24 (LSB), 36, 48, 54 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(1),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_54], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_48], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_36], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 0));

	/* Write the CCK घातer per rate set */

	/* 1L (LSB), reserved, 2L, 2S (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(2),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 16) |
		  /* POW_SM(txPowerTimes2,  8) | this is reserved क्रम AR9003 */
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 0));

	/* 5.5L (LSB), 5.5S, 11L, 11S (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(3),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_11S], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_11L], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_5S], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 0)
	    );

        /* Write the घातer क्रम duplicated frames - HT40 */

        /* dup40_cck (LSB), dup40_ofdm, ext20_cck, ext20_ofdm (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(8),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24],  8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L],  0)
	    );

	/* Write the HT20 घातer per rate set */

	/* 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(4),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_5], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_4], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_1_3_9_11_17_19], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_0_8_16], 0)
	    );

	/* 6 (LSB), 7, 12, 13 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(5),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_13], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_12], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_7], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_6], 0)
	    );

	/* 14 (LSB), 15, 20, 21 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(9),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_21], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_20], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_15], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_14], 0)
	    );

	/* Mixed HT20 and HT40 rates */

	/* HT20 22 (LSB), HT20 23, HT40 22, HT40 23 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(10),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_23], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_22], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_23], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_22], 0)
	    );

	/*
	 * Write the HT40 घातer per rate set
	 * correct PAR dअगरference between HT40 and HT20/LEGACY
	 * 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB)
	 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(6),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_5], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_4], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_1_3_9_11_17_19], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_0_8_16], 0)
	    );

	/* 6 (LSB), 7, 12, 13 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(7),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_13], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_12], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_7], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_6], 0)
	    );

	/* 14 (LSB), 15, 20, 21 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(11),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_21], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_20], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_15], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_14], 0)
	    );

	वापस 0;
#अघोषित POW_SM
पूर्ण

अटल व्योम ar9003_hw_get_legacy_target_घातers(काष्ठा ath_hw *ah, u16 freq,
					       u8 *targetPowerValT2,
					       bool is2GHz)
अणु
	targetPowerValT2[ALL_TARGET_LEGACY_6_24] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_6_24, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_36] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_36, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_48] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_48, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_54] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_54, freq,
					 is2GHz);
पूर्ण

अटल व्योम ar9003_hw_get_cck_target_घातers(काष्ठा ath_hw *ah, u16 freq,
					    u8 *targetPowerValT2)
अणु
	targetPowerValT2[ALL_TARGET_LEGACY_1L_5L] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_1L_5L,
					     freq);
	targetPowerValT2[ALL_TARGET_LEGACY_5S] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_5S, freq);
	targetPowerValT2[ALL_TARGET_LEGACY_11L] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_11L, freq);
	targetPowerValT2[ALL_TARGET_LEGACY_11S] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_11S, freq);
पूर्ण

अटल व्योम ar9003_hw_get_ht20_target_घातers(काष्ठा ath_hw *ah, u16 freq,
					     u8 *targetPowerValT2, bool is2GHz)
अणु
	targetPowerValT2[ALL_TARGET_HT20_0_8_16] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_0_8_16, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_1_3_9_11_17_19] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_1_3_9_11_17_19,
					      freq, is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_4] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_4, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_5] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_5, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_6] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_6, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_7] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_7, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_12] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_12, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_13] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_13, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_14] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_14, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_15] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_15, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_20] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_20, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_21] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_21, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_22] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_22, freq,
					      is2GHz);
	targetPowerValT2[ALL_TARGET_HT20_23] =
	    ar9003_hw_eeprom_get_ht20_tgt_pwr(ah, HT_TARGET_RATE_23, freq,
					      is2GHz);
पूर्ण

अटल व्योम ar9003_hw_get_ht40_target_घातers(काष्ठा ath_hw *ah,
						   u16 freq,
						   u8 *targetPowerValT2,
						   bool is2GHz)
अणु
	/* XXX: hard code क्रम now, need to get from eeprom काष्ठा */
	u8 ht40PowerIncForPdadc = 0;

	targetPowerValT2[ALL_TARGET_HT40_0_8_16] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_0_8_16, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_1_3_9_11_17_19] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_1_3_9_11_17_19,
					      freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_4] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_4, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_5] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_5, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_6] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_6, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_7] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_7, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_12] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_12, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_13] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_13, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_14] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_14, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_15] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_15, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_20] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_20, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_21] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_21, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_22] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_22, freq,
					      is2GHz) + ht40PowerIncForPdadc;
	targetPowerValT2[ALL_TARGET_HT40_23] =
	    ar9003_hw_eeprom_get_ht40_tgt_pwr(ah, HT_TARGET_RATE_23, freq,
					      is2GHz) + ht40PowerIncForPdadc;
पूर्ण

अटल व्योम ar9003_hw_get_target_घातer_eeprom(काष्ठा ath_hw *ah,
					      काष्ठा ath9k_channel *chan,
					      u8 *targetPowerValT2)
अणु
	bool is2GHz = IS_CHAN_2GHZ(chan);
	अचिन्हित पूर्णांक i = 0;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u16 freq = chan->channel;

	अगर (is2GHz)
		ar9003_hw_get_cck_target_घातers(ah, freq, targetPowerValT2);

	ar9003_hw_get_legacy_target_घातers(ah, freq, targetPowerValT2, is2GHz);
	ar9003_hw_get_ht20_target_घातers(ah, freq, targetPowerValT2, is2GHz);

	अगर (IS_CHAN_HT40(chan))
		ar9003_hw_get_ht40_target_घातers(ah, freq, targetPowerValT2,
						 is2GHz);

	क्रम (i = 0; i < ar9300RateSize; i++) अणु
		ath_dbg(common, REGULATORY, "TPC[%02d] 0x%08x\n",
			i, targetPowerValT2[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक ar9003_hw_cal_pier_get(काष्ठा ath_hw *ah,
				  पूर्णांक mode,
				  पूर्णांक ipier,
				  पूर्णांक ichain,
				  पूर्णांक *pfrequency,
				  पूर्णांक *pcorrection,
				  पूर्णांक *ptemperature, पूर्णांक *pvoltage,
				  पूर्णांक *pnf_cal, पूर्णांक *pnf_घातer)
अणु
	u8 *pCalPier;
	काष्ठा ar9300_cal_data_per_freq_op_loop *pCalPierStruct;
	पूर्णांक is2GHz;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (ichain >= AR9300_MAX_CHAINS) अणु
		ath_dbg(common, EEPROM,
			"Invalid chain index, must be less than %d\n",
			AR9300_MAX_CHAINS);
		वापस -1;
	पूर्ण

	अगर (mode) अणु		/* 5GHz */
		अगर (ipier >= AR9300_NUM_5G_CAL_PIERS) अणु
			ath_dbg(common, EEPROM,
				"Invalid 5GHz cal pier index, must be less than %d\n",
				AR9300_NUM_5G_CAL_PIERS);
			वापस -1;
		पूर्ण
		pCalPier = &(eep->calFreqPier5G[ipier]);
		pCalPierStruct = &(eep->calPierData5G[ichain][ipier]);
		is2GHz = 0;
	पूर्ण अन्यथा अणु
		अगर (ipier >= AR9300_NUM_2G_CAL_PIERS) अणु
			ath_dbg(common, EEPROM,
				"Invalid 2GHz cal pier index, must be less than %d\n",
				AR9300_NUM_2G_CAL_PIERS);
			वापस -1;
		पूर्ण

		pCalPier = &(eep->calFreqPier2G[ipier]);
		pCalPierStruct = &(eep->calPierData2G[ichain][ipier]);
		is2GHz = 1;
	पूर्ण

	*pfrequency = ath9k_hw_fbin2freq(*pCalPier, is2GHz);
	*pcorrection = pCalPierStruct->refPower;
	*ptemperature = pCalPierStruct->tempMeas;
	*pvoltage = pCalPierStruct->voltMeas;
	*pnf_cal = pCalPierStruct->rxTempMeas ?
			N2DBM(pCalPierStruct->rxNoiseन्यूनमानCal) : 0;
	*pnf_घातer = pCalPierStruct->rxTempMeas ?
			N2DBM(pCalPierStruct->rxNoiseन्यूनमानPower) : 0;

	वापस 0;
पूर्ण

अटल व्योम ar9003_hw_घातer_control_override(काष्ठा ath_hw *ah,
					     पूर्णांक frequency,
					     पूर्णांक *correction,
					     पूर्णांक *voltage, पूर्णांक *temperature)
अणु
	पूर्णांक temp_slope = 0, temp_slope1 = 0, temp_slope2 = 0;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	पूर्णांक f[8], t[8], t1[3], t2[3], i;

	REG_RMW(ah, AR_PHY_TPC_11_B0,
		(correction[0] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
		AR_PHY_TPC_OLPC_GAIN_DELTA);
	अगर (ah->caps.tx_chainmask & BIT(1))
		REG_RMW(ah, AR_PHY_TPC_11_B1,
			(correction[1] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
			AR_PHY_TPC_OLPC_GAIN_DELTA);
	अगर (ah->caps.tx_chainmask & BIT(2))
		REG_RMW(ah, AR_PHY_TPC_11_B2,
			(correction[2] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
			AR_PHY_TPC_OLPC_GAIN_DELTA);

	/* enable खोलो loop घातer control on chip */
	REG_RMW(ah, AR_PHY_TPC_6_B0,
		(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
		AR_PHY_TPC_6_ERROR_EST_MODE);
	अगर (ah->caps.tx_chainmask & BIT(1))
		REG_RMW(ah, AR_PHY_TPC_6_B1,
			(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
			AR_PHY_TPC_6_ERROR_EST_MODE);
	अगर (ah->caps.tx_chainmask & BIT(2))
		REG_RMW(ah, AR_PHY_TPC_6_B2,
			(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
			AR_PHY_TPC_6_ERROR_EST_MODE);

	/*
	 * enable temperature compensation
	 * Need to use रेजिस्टर names
	 */
	अगर (frequency < 4000) अणु
		temp_slope = eep->modalHeader2G.tempSlope;
	पूर्ण अन्यथा अणु
		अगर (AR_SREV_9550(ah)) अणु
			t[0] = eep->base_ext1.tempslopextension[2];
			t1[0] = eep->base_ext1.tempslopextension[3];
			t2[0] = eep->base_ext1.tempslopextension[4];
			f[0] = 5180;

			t[1] = eep->modalHeader5G.tempSlope;
			t1[1] = eep->base_ext1.tempslopextension[0];
			t2[1] = eep->base_ext1.tempslopextension[1];
			f[1] = 5500;

			t[2] = eep->base_ext1.tempslopextension[5];
			t1[2] = eep->base_ext1.tempslopextension[6];
			t2[2] = eep->base_ext1.tempslopextension[7];
			f[2] = 5785;

			temp_slope = ar9003_hw_घातer_पूर्णांकerpolate(frequency,
								 f, t, 3);
			temp_slope1 = ar9003_hw_घातer_पूर्णांकerpolate(frequency,
								   f, t1, 3);
			temp_slope2 = ar9003_hw_घातer_पूर्णांकerpolate(frequency,
								   f, t2, 3);

			जाओ tempslope;
		पूर्ण

		अगर ((eep->baseEepHeader.miscConfiguration & 0x20) != 0) अणु
			क्रम (i = 0; i < 8; i++) अणु
				t[i] = eep->base_ext1.tempslopextension[i];
				f[i] = FBIN2FREQ(eep->calFreqPier5G[i], 0);
			पूर्ण
			temp_slope = ar9003_hw_घातer_पूर्णांकerpolate((s32) frequency,
								 f, t, 8);
		पूर्ण अन्यथा अगर (eep->base_ext2.tempSlopeLow != 0) अणु
			t[0] = eep->base_ext2.tempSlopeLow;
			f[0] = 5180;
			t[1] = eep->modalHeader5G.tempSlope;
			f[1] = 5500;
			t[2] = eep->base_ext2.tempSlopeHigh;
			f[2] = 5785;
			temp_slope = ar9003_hw_घातer_पूर्णांकerpolate((s32) frequency,
								 f, t, 3);
		पूर्ण अन्यथा अणु
			temp_slope = eep->modalHeader5G.tempSlope;
		पूर्ण
	पूर्ण

tempslope:
	अगर (AR_SREV_9550(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah)) अणु
		u8 txmask = (eep->baseEepHeader.txrxMask & 0xf0) >> 4;

		/*
		 * AR955x has tempSlope रेजिस्टर क्रम each chain.
		 * Check whether temp_compensation feature is enabled or not.
		 */
		अगर (eep->baseEepHeader.featureEnable & 0x1) अणु
			अगर (frequency < 4000) अणु
				अगर (txmask & BIT(0))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      eep->base_ext2.tempSlopeLow);
				अगर (txmask & BIT(1))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope);
				अगर (txmask & BIT(2))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      eep->base_ext2.tempSlopeHigh);
			पूर्ण अन्यथा अणु
				अगर (txmask & BIT(0))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope);
				अगर (txmask & BIT(1))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope1);
				अगर (txmask & BIT(2))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope2);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If temp compensation is not enabled,
			 * set all रेजिस्टरs to 0.
			 */
			अगर (txmask & BIT(0))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
			अगर (txmask & BIT(1))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
			अगर (txmask & BIT(2))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		REG_RMW_FIELD(ah, AR_PHY_TPC_19,
			      AR_PHY_TPC_19_ALPHA_THERM, temp_slope);
	पूर्ण

	अगर (AR_SREV_9462_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
			      AR_PHY_TPC_19_B1_ALPHA_THERM, temp_slope);


	REG_RMW_FIELD(ah, AR_PHY_TPC_18, AR_PHY_TPC_18_THERM_CAL_VALUE,
		      temperature[0]);
पूर्ण

/* Apply the recorded correction values. */
अटल पूर्णांक ar9003_hw_calibration_apply(काष्ठा ath_hw *ah, पूर्णांक frequency)
अणु
	पूर्णांक ichain, ipier, npier;
	पूर्णांक mode;
	पूर्णांक lfrequency[AR9300_MAX_CHAINS],
	    lcorrection[AR9300_MAX_CHAINS],
	    ltemperature[AR9300_MAX_CHAINS], lvoltage[AR9300_MAX_CHAINS],
	    lnf_cal[AR9300_MAX_CHAINS], lnf_pwr[AR9300_MAX_CHAINS];
	पूर्णांक hfrequency[AR9300_MAX_CHAINS],
	    hcorrection[AR9300_MAX_CHAINS],
	    htemperature[AR9300_MAX_CHAINS], hvoltage[AR9300_MAX_CHAINS],
	    hnf_cal[AR9300_MAX_CHAINS], hnf_pwr[AR9300_MAX_CHAINS];
	पूर्णांक fdअगरf;
	पूर्णांक correction[AR9300_MAX_CHAINS],
	    voltage[AR9300_MAX_CHAINS], temperature[AR9300_MAX_CHAINS],
	    nf_cal[AR9300_MAX_CHAINS], nf_pwr[AR9300_MAX_CHAINS];
	पूर्णांक pfrequency, pcorrection, ptemperature, pvoltage,
	    pnf_cal, pnf_pwr;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	mode = (frequency >= 4000);
	अगर (mode)
		npier = AR9300_NUM_5G_CAL_PIERS;
	अन्यथा
		npier = AR9300_NUM_2G_CAL_PIERS;

	क्रम (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) अणु
		lfrequency[ichain] = 0;
		hfrequency[ichain] = 100000;
	पूर्ण
	/* identअगरy best lower and higher frequency calibration measurement */
	क्रम (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) अणु
		क्रम (ipier = 0; ipier < npier; ipier++) अणु
			अगर (!ar9003_hw_cal_pier_get(ah, mode, ipier, ichain,
						    &pfrequency, &pcorrection,
						    &ptemperature, &pvoltage,
						    &pnf_cal, &pnf_pwr)) अणु
				fdअगरf = frequency - pfrequency;

				/*
				 * this measurement is higher than
				 * our desired frequency
				 */
				अगर (fdअगरf <= 0) अणु
					अगर (hfrequency[ichain] <= 0 ||
					    hfrequency[ichain] >= 100000 ||
					    fdअगरf >
					    (frequency - hfrequency[ichain])) अणु
						/*
						 * new best higher
						 * frequency measurement
						 */
						hfrequency[ichain] = pfrequency;
						hcorrection[ichain] =
						    pcorrection;
						htemperature[ichain] =
						    ptemperature;
						hvoltage[ichain] = pvoltage;
						hnf_cal[ichain] = pnf_cal;
						hnf_pwr[ichain] = pnf_pwr;
					पूर्ण
				पूर्ण
				अगर (fdअगरf >= 0) अणु
					अगर (lfrequency[ichain] <= 0
					    || fdअगरf <
					    (frequency - lfrequency[ichain])) अणु
						/*
						 * new best lower
						 * frequency measurement
						 */
						lfrequency[ichain] = pfrequency;
						lcorrection[ichain] =
						    pcorrection;
						ltemperature[ichain] =
						    ptemperature;
						lvoltage[ichain] = pvoltage;
						lnf_cal[ichain] = pnf_cal;
						lnf_pwr[ichain] = pnf_pwr;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* पूर्णांकerpolate  */
	क्रम (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) अणु
		ath_dbg(common, EEPROM,
			"ch=%d f=%d low=%d %d h=%d %d n=%d %d p=%d %d\n",
			ichain, frequency, lfrequency[ichain],
			lcorrection[ichain], hfrequency[ichain],
			hcorrection[ichain], lnf_cal[ichain],
			hnf_cal[ichain], lnf_pwr[ichain],
			hnf_pwr[ichain]);
		/* they're the same, so just pick one */
		अगर (hfrequency[ichain] == lfrequency[ichain]) अणु
			correction[ichain] = lcorrection[ichain];
			voltage[ichain] = lvoltage[ichain];
			temperature[ichain] = ltemperature[ichain];
			nf_cal[ichain] = lnf_cal[ichain];
			nf_pwr[ichain] = lnf_pwr[ichain];
		पूर्ण
		/* the low frequency is good */
		अन्यथा अगर (frequency - lfrequency[ichain] < 1000) अणु
			/* so is the high frequency, पूर्णांकerpolate */
			अगर (hfrequency[ichain] - frequency < 1000) अणु

				correction[ichain] = पूर्णांकerpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lcorrection[ichain],
						hcorrection[ichain]);

				temperature[ichain] = पूर्णांकerpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						ltemperature[ichain],
						htemperature[ichain]);

				voltage[ichain] = पूर्णांकerpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lvoltage[ichain],
						hvoltage[ichain]);

				nf_cal[ichain] = पूर्णांकerpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lnf_cal[ichain],
						hnf_cal[ichain]);

				nf_pwr[ichain] = पूर्णांकerpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lnf_pwr[ichain],
						hnf_pwr[ichain]);
			पूर्ण
			/* only low is good, use it */
			अन्यथा अणु
				correction[ichain] = lcorrection[ichain];
				temperature[ichain] = ltemperature[ichain];
				voltage[ichain] = lvoltage[ichain];
				nf_cal[ichain] = lnf_cal[ichain];
				nf_pwr[ichain] = lnf_pwr[ichain];
			पूर्ण
		पूर्ण
		/* only high is good, use it */
		अन्यथा अगर (hfrequency[ichain] - frequency < 1000) अणु
			correction[ichain] = hcorrection[ichain];
			temperature[ichain] = htemperature[ichain];
			voltage[ichain] = hvoltage[ichain];
			nf_cal[ichain] = hnf_cal[ichain];
			nf_pwr[ichain] = hnf_pwr[ichain];
		पूर्ण अन्यथा अणु	/* nothing is good, presume 0???? */
			correction[ichain] = 0;
			temperature[ichain] = 0;
			voltage[ichain] = 0;
			nf_cal[ichain] = 0;
			nf_pwr[ichain] = 0;
		पूर्ण
	पूर्ण

	ar9003_hw_घातer_control_override(ah, frequency, correction, voltage,
					 temperature);

	ath_dbg(common, EEPROM,
		"for frequency=%d, calibration correction = %d %d %d\n",
		frequency, correction[0], correction[1], correction[2]);

	/* Store calibrated noise न्यूनमान values */
	क्रम (ichain = 0; ichain < AR5416_MAX_CHAINS; ichain++)
		अगर (mode) अणु
			ah->nf_5g.cal[ichain] = nf_cal[ichain];
			ah->nf_5g.pwr[ichain] = nf_pwr[ichain];
		पूर्ण अन्यथा अणु
			ah->nf_2g.cal[ichain] = nf_cal[ichain];
			ah->nf_2g.pwr[ichain] = nf_pwr[ichain];
		पूर्ण

	वापस 0;
पूर्ण

अटल u16 ar9003_hw_get_direct_edge_घातer(काष्ठा ar9300_eeprom *eep,
					   पूर्णांक idx,
					   पूर्णांक edge,
					   bool is2GHz)
अणु
	काष्ठा cal_ctl_data_2g *ctl_2g = eep->ctlPowerData_2G;
	काष्ठा cal_ctl_data_5g *ctl_5g = eep->ctlPowerData_5G;

	अगर (is2GHz)
		वापस CTL_EDGE_TPOWER(ctl_2g[idx].ctlEdges[edge]);
	अन्यथा
		वापस CTL_EDGE_TPOWER(ctl_5g[idx].ctlEdges[edge]);
पूर्ण

अटल u16 ar9003_hw_get_indirect_edge_घातer(काष्ठा ar9300_eeprom *eep,
					     पूर्णांक idx,
					     अचिन्हित पूर्णांक edge,
					     u16 freq,
					     bool is2GHz)
अणु
	काष्ठा cal_ctl_data_2g *ctl_2g = eep->ctlPowerData_2G;
	काष्ठा cal_ctl_data_5g *ctl_5g = eep->ctlPowerData_5G;

	u8 *ctl_freqbin = is2GHz ?
		&eep->ctl_freqbin_2G[idx][0] :
		&eep->ctl_freqbin_5G[idx][0];

	अगर (is2GHz) अणु
		अगर (ath9k_hw_fbin2freq(ctl_freqbin[edge - 1], 1) < freq &&
		    CTL_EDGE_FLAGS(ctl_2g[idx].ctlEdges[edge - 1]))
			वापस CTL_EDGE_TPOWER(ctl_2g[idx].ctlEdges[edge - 1]);
	पूर्ण अन्यथा अणु
		अगर (ath9k_hw_fbin2freq(ctl_freqbin[edge - 1], 0) < freq &&
		    CTL_EDGE_FLAGS(ctl_5g[idx].ctlEdges[edge - 1]))
			वापस CTL_EDGE_TPOWER(ctl_5g[idx].ctlEdges[edge - 1]);
	पूर्ण

	वापस MAX_RATE_POWER;
पूर्ण

/*
 * Find the maximum conक्रमmance test limit क्रम the given channel and CTL info
 */
अटल u16 ar9003_hw_get_max_edge_घातer(काष्ठा ar9300_eeprom *eep,
					u16 freq, पूर्णांक idx, bool is2GHz)
अणु
	u16 twiceMaxEdgePower = MAX_RATE_POWER;
	u8 *ctl_freqbin = is2GHz ?
		&eep->ctl_freqbin_2G[idx][0] :
		&eep->ctl_freqbin_5G[idx][0];
	u16 num_edges = is2GHz ?
		AR9300_NUM_BAND_EDGES_2G : AR9300_NUM_BAND_EDGES_5G;
	अचिन्हित पूर्णांक edge;

	/* Get the edge घातer */
	क्रम (edge = 0;
	     (edge < num_edges) && (ctl_freqbin[edge] != AR5416_BCHAN_UNUSED);
	     edge++) अणु
		/*
		 * If there's an exact channel match or an inband flag set
		 * on the lower channel use the given rdEdgePower
		 */
		अगर (freq == ath9k_hw_fbin2freq(ctl_freqbin[edge], is2GHz)) अणु
			twiceMaxEdgePower =
				ar9003_hw_get_direct_edge_घातer(eep, idx,
								edge, is2GHz);
			अवरोध;
		पूर्ण अन्यथा अगर ((edge > 0) &&
			   (freq < ath9k_hw_fbin2freq(ctl_freqbin[edge],
						      is2GHz))) अणु
			twiceMaxEdgePower =
				ar9003_hw_get_indirect_edge_घातer(eep, idx,
								  edge, freq,
								  is2GHz);
			/*
			 * Leave loop - no more affecting edges possible in
			 * this monotonic increasing list
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (is2GHz && !twiceMaxEdgePower)
		twiceMaxEdgePower = 60;

	वापस twiceMaxEdgePower;
पूर्ण

अटल व्योम ar9003_hw_set_घातer_per_rate_table(काष्ठा ath_hw *ah,
					       काष्ठा ath9k_channel *chan,
					       u8 *pPwrArray, u16 cfgCtl,
					       u8 antenna_reduction,
					       u16 घातerLimit)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar9300_eeprom *pEepData = &ah->eeprom.ar9300_eep;
	u16 twiceMaxEdgePower;
	पूर्णांक i;
	u16 scaledPower = 0, minCtlPower;
	अटल स्थिर u16 ctlModesFor11a[] = अणु
		CTL_11A, CTL_5GHT20, CTL_11A_EXT, CTL_5GHT40
	पूर्ण;
	अटल स्थिर u16 ctlModesFor11g[] = अणु
		CTL_11B, CTL_11G, CTL_2GHT20, CTL_11B_EXT,
		CTL_11G_EXT, CTL_2GHT40
	पूर्ण;
	u16 numCtlModes;
	स्थिर u16 *pCtlMode;
	u16 ctlMode, freq;
	काष्ठा chan_centers centers;
	u8 *ctlIndex;
	u8 ctlNum;
	u16 twiceMinEdgePower;
	bool is2ghz = IS_CHAN_2GHZ(chan);

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	scaledPower = ath9k_hw_get_scaled_घातer(ah, घातerLimit,
						antenna_reduction);

	अगर (is2ghz) अणु
		/* Setup क्रम CTL modes */
		/* CTL_11B, CTL_11G, CTL_2GHT20 */
		numCtlModes =
			ARRAY_SIZE(ctlModesFor11g) -
				   SUB_NUM_CTL_MODES_AT_2G_40;
		pCtlMode = ctlModesFor11g;
		अगर (IS_CHAN_HT40(chan))
			/* All 2G CTL's */
			numCtlModes = ARRAY_SIZE(ctlModesFor11g);
	पूर्ण अन्यथा अणु
		/* Setup क्रम CTL modes */
		/* CTL_11A, CTL_5GHT20 */
		numCtlModes = ARRAY_SIZE(ctlModesFor11a) -
					 SUB_NUM_CTL_MODES_AT_5G_40;
		pCtlMode = ctlModesFor11a;
		अगर (IS_CHAN_HT40(chan))
			/* All 5G CTL's */
			numCtlModes = ARRAY_SIZE(ctlModesFor11a);
	पूर्ण

	/*
	 * For MIMO, need to apply regulatory caps inभागidually across
	 * dynamically running modes: CCK, OFDM, HT20, HT40
	 *
	 * The outer loop walks through each possible applicable runसमय mode.
	 * The inner loop walks through each ctlIndex entry in EEPROM.
	 * The ctl value is encoded as [7:4] == test group, [3:0] == test mode.
	 */
	क्रम (ctlMode = 0; ctlMode < numCtlModes; ctlMode++) अणु
		bool isHt40CtlMode = (pCtlMode[ctlMode] == CTL_5GHT40) ||
			(pCtlMode[ctlMode] == CTL_2GHT40);
		अगर (isHt40CtlMode)
			freq = centers.synth_center;
		अन्यथा अगर (pCtlMode[ctlMode] & EXT_ADDITIVE)
			freq = centers.ext_center;
		अन्यथा
			freq = centers.ctl_center;

		ath_dbg(common, REGULATORY,
			"LOOP-Mode ctlMode %d < %d, isHt40CtlMode %d, EXT_ADDITIVE %d\n",
			ctlMode, numCtlModes, isHt40CtlMode,
			(pCtlMode[ctlMode] & EXT_ADDITIVE));

		/* walk through each CTL index stored in EEPROM */
		अगर (is2ghz) अणु
			ctlIndex = pEepData->ctlIndex_2G;
			ctlNum = AR9300_NUM_CTLS_2G;
		पूर्ण अन्यथा अणु
			ctlIndex = pEepData->ctlIndex_5G;
			ctlNum = AR9300_NUM_CTLS_5G;
		पूर्ण

		twiceMaxEdgePower = MAX_RATE_POWER;
		क्रम (i = 0; (i < ctlNum) && ctlIndex[i]; i++) अणु
			ath_dbg(common, REGULATORY,
				"LOOP-Ctlidx %d: cfgCtl 0x%2.2x pCtlMode 0x%2.2x ctlIndex 0x%2.2x chan %d\n",
				i, cfgCtl, pCtlMode[ctlMode], ctlIndex[i],
				chan->channel);

			/*
			 * compare test group from regulatory
			 * channel list with test mode from pCtlMode
			 * list
			 */
			अगर ((((cfgCtl & ~CTL_MODE_M) |
			       (pCtlMode[ctlMode] & CTL_MODE_M)) ==
				ctlIndex[i]) ||
			    (((cfgCtl & ~CTL_MODE_M) |
			       (pCtlMode[ctlMode] & CTL_MODE_M)) ==
			     ((ctlIndex[i] & CTL_MODE_M) |
			       SD_NO_CTL))) अणु
				twiceMinEdgePower =
				  ar9003_hw_get_max_edge_घातer(pEepData,
							       freq, i,
							       is2ghz);

				अगर ((cfgCtl & ~CTL_MODE_M) == SD_NO_CTL)
					/*
					 * Find the minimum of all CTL
					 * edge घातers that apply to
					 * this channel
					 */
					twiceMaxEdgePower =
						min(twiceMaxEdgePower,
						    twiceMinEdgePower);
				अन्यथा अणु
					/* specअगरic */
					twiceMaxEdgePower = twiceMinEdgePower;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		minCtlPower = (u8)min(twiceMaxEdgePower, scaledPower);

		ath_dbg(common, REGULATORY,
			"SEL-Min ctlMode %d pCtlMode %d 2xMaxEdge %d sP %d minCtlPwr %d\n",
			ctlMode, pCtlMode[ctlMode], twiceMaxEdgePower,
			scaledPower, minCtlPower);

		/* Apply ctl mode to correct target घातer set */
		चयन (pCtlMode[ctlMode]) अणु
		हाल CTL_11B:
			क्रम (i = ALL_TARGET_LEGACY_1L_5L;
			     i <= ALL_TARGET_LEGACY_11S; i++)
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
			अवरोध;
		हाल CTL_11A:
		हाल CTL_11G:
			क्रम (i = ALL_TARGET_LEGACY_6_24;
			     i <= ALL_TARGET_LEGACY_54; i++)
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
			अवरोध;
		हाल CTL_5GHT20:
		हाल CTL_2GHT20:
			क्रम (i = ALL_TARGET_HT20_0_8_16;
			     i <= ALL_TARGET_HT20_23; i++) अणु
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
				अगर (ath9k_hw_mci_is_enabled(ah))
					pPwrArray[i] =
						(u8)min((u16)pPwrArray[i],
						ar9003_mci_get_max_txघातer(ah,
							pCtlMode[ctlMode]));
			पूर्ण
			अवरोध;
		हाल CTL_5GHT40:
		हाल CTL_2GHT40:
			क्रम (i = ALL_TARGET_HT40_0_8_16;
			     i <= ALL_TARGET_HT40_23; i++) अणु
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
				अगर (ath9k_hw_mci_is_enabled(ah))
					pPwrArray[i] =
						(u8)min((u16)pPwrArray[i],
						ar9003_mci_get_max_txघातer(ah,
							pCtlMode[ctlMode]));
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण /* end ctl mode checking */
पूर्ण

अटल अंतरभूत u8 mcsidx_to_tgtpwridx(अचिन्हित पूर्णांक mcs_idx, u8 base_pwridx)
अणु
	u8 mod_idx = mcs_idx % 8;

	अगर (mod_idx <= 3)
		वापस mod_idx ? (base_pwridx + 1) : base_pwridx;
	अन्यथा
		वापस base_pwridx + 4 * (mcs_idx / 8) + mod_idx - 2;
पूर्ण

अटल व्योम ar9003_paprd_set_txघातer(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_channel *chan,
				     u8 *targetPowerValT2)
अणु
	पूर्णांक i;

	अगर (!ar9003_is_paprd_enabled(ah))
		वापस;

	अगर (IS_CHAN_HT40(chan))
		i = ALL_TARGET_HT40_7;
	अन्यथा
		i = ALL_TARGET_HT20_7;

	अगर (IS_CHAN_2GHZ(chan)) अणु
		अगर (!AR_SREV_9330(ah) && !AR_SREV_9340(ah) &&
		    !AR_SREV_9462(ah) && !AR_SREV_9565(ah)) अणु
			अगर (IS_CHAN_HT40(chan))
				i = ALL_TARGET_HT40_0_8_16;
			अन्यथा
				i = ALL_TARGET_HT20_0_8_16;
		पूर्ण
	पूर्ण

	ah->paprd_target_घातer = targetPowerValT2[i];
पूर्ण

अटल व्योम ath9k_hw_ar9300_set_txघातer(काष्ठा ath_hw *ah,
					काष्ठा ath9k_channel *chan, u16 cfgCtl,
					u8 twiceAntennaReduction,
					u8 घातerLimit, bool test)
अणु
	काष्ठा ath_regulatory *regulatory = ath9k_hw_regulatory(ah);
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	काष्ठा ar9300_modal_eep_header *modal_hdr;
	u8 targetPowerValT2[ar9300RateSize];
	u8 target_घातer_val_t2_eep[ar9300RateSize];
	u8 targetPowerValT2_tpc[ar9300RateSize];
	अचिन्हित पूर्णांक i = 0, paprd_scale_factor = 0;
	u8 pwr_idx, min_pwridx = 0;

	स_रखो(targetPowerValT2, 0 , माप(targetPowerValT2));

	/*
	 * Get target घातers from EEPROM - our baseline क्रम TX Power
	 */
	ar9003_hw_get_target_घातer_eeprom(ah, chan, targetPowerValT2);

	अगर (ar9003_is_paprd_enabled(ah)) अणु
		अगर (IS_CHAN_2GHZ(chan))
			modal_hdr = &eep->modalHeader2G;
		अन्यथा
			modal_hdr = &eep->modalHeader5G;

		ah->paprd_ratemask =
			le32_to_cpu(modal_hdr->papdRateMaskHt20) &
			AR9300_PAPRD_RATE_MASK;

		ah->paprd_ratemask_ht40 =
			le32_to_cpu(modal_hdr->papdRateMaskHt40) &
			AR9300_PAPRD_RATE_MASK;

		paprd_scale_factor = ar9003_get_paprd_scale_factor(ah, chan);
		min_pwridx = IS_CHAN_HT40(chan) ? ALL_TARGET_HT40_0_8_16 :
						  ALL_TARGET_HT20_0_8_16;

		अगर (!ah->paprd_table_ग_लिखो_करोne) अणु
			स_नकल(target_घातer_val_t2_eep, targetPowerValT2,
			       माप(targetPowerValT2));
			क्रम (i = 0; i < 24; i++) अणु
				pwr_idx = mcsidx_to_tgtpwridx(i, min_pwridx);
				अगर (ah->paprd_ratemask & (1 << i)) अणु
					अगर (targetPowerValT2[pwr_idx] &&
					    targetPowerValT2[pwr_idx] ==
					    target_घातer_val_t2_eep[pwr_idx])
						targetPowerValT2[pwr_idx] -=
							paprd_scale_factor;
				पूर्ण
			पूर्ण
		पूर्ण
		स_नकल(target_घातer_val_t2_eep, targetPowerValT2,
		       माप(targetPowerValT2));
	पूर्ण

	ar9003_hw_set_घातer_per_rate_table(ah, chan,
					   targetPowerValT2, cfgCtl,
					   twiceAntennaReduction,
					   घातerLimit);

	स_नकल(targetPowerValT2_tpc, targetPowerValT2,
	       माप(targetPowerValT2));

	अगर (ar9003_is_paprd_enabled(ah)) अणु
		क्रम (i = 0; i < ar9300RateSize; i++) अणु
			अगर ((ah->paprd_ratemask & (1 << i)) &&
			    (असल(targetPowerValT2[i] -
				target_घातer_val_t2_eep[i]) >
			    paprd_scale_factor)) अणु
				ah->paprd_ratemask &= ~(1 << i);
				ath_dbg(common, EEPROM,
					"paprd disabled for mcs %d\n", i);
			पूर्ण
		पूर्ण
	पूर्ण

	regulatory->max_घातer_level = 0;
	क्रम (i = 0; i < ar9300RateSize; i++) अणु
		अगर (targetPowerValT2[i] > regulatory->max_घातer_level)
			regulatory->max_घातer_level = targetPowerValT2[i];
	पूर्ण

	ath9k_hw_update_regulatory_maxघातer(ah);

	अगर (test)
		वापस;

	क्रम (i = 0; i < ar9300RateSize; i++) अणु
		ath_dbg(common, REGULATORY, "TPC[%02d] 0x%08x\n",
			i, targetPowerValT2[i]);
	पूर्ण

	/* Write target घातer array to रेजिस्टरs */
	ar9003_hw_tx_घातer_regग_लिखो(ah, targetPowerValT2);
	ar9003_hw_calibration_apply(ah, chan->channel);
	ar9003_paprd_set_txघातer(ah, chan, targetPowerValT2);

	ar9003_hw_selfgen_tpc_txघातer(ah, chan, targetPowerValT2);

	/* TPC initializations */
	अगर (ah->tpc_enabled) अणु
		u32 val;

		ar9003_hw_init_rate_txघातer(ah, targetPowerValT2_tpc, chan);

		/* Enable TPC */
		REG_WRITE(ah, AR_PHY_PWRTX_MAX,
			  AR_PHY_POWER_TX_RATE_MAX_TPC_ENABLE);
		/* Disable per chain घातer reduction */
		val = REG_READ(ah, AR_PHY_POWER_TX_SUB);
		अगर (AR_SREV_9340(ah))
			REG_WRITE(ah, AR_PHY_POWER_TX_SUB,
				  val & 0xFFFFFFC0);
		अन्यथा
			REG_WRITE(ah, AR_PHY_POWER_TX_SUB,
				  val & 0xFFFFF000);
	पूर्ण अन्यथा अणु
		/* Disable TPC */
		REG_WRITE(ah, AR_PHY_PWRTX_MAX, 0);
	पूर्ण
पूर्ण

अटल u16 ath9k_hw_ar9300_get_spur_channel(काष्ठा ath_hw *ah,
					    u16 i, bool is2GHz)
अणु
	वापस AR_NO_SPUR;
पूर्ण

s32 ar9003_hw_get_tx_gain_idx(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	वापस (eep->baseEepHeader.txrxgain >> 4) & 0xf; /* bits 7:4 */
पूर्ण

s32 ar9003_hw_get_rx_gain_idx(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	वापस (eep->baseEepHeader.txrxgain) & 0xf; /* bits 3:0 */
पूर्ण

u8 *ar9003_get_spur_chan_ptr(काष्ठा ath_hw *ah, bool is2ghz)
अणु
	वापस ar9003_modal_header(ah, is2ghz)->spurChans;
पूर्ण

अचिन्हित पूर्णांक ar9003_get_paprd_scale_factor(काष्ठा ath_hw *ah,
					   काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	अगर (IS_CHAN_2GHZ(chan))
		वापस MS(le32_to_cpu(eep->modalHeader2G.papdRateMaskHt20),
			  AR9300_PAPRD_SCALE_1);
	अन्यथा अणु
		अगर (chan->channel >= 5700)
			वापस MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt20),
				  AR9300_PAPRD_SCALE_1);
		अन्यथा अगर (chan->channel >= 5400)
			वापस MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt40),
				  AR9300_PAPRD_SCALE_2);
		अन्यथा
			वापस MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt40),
				  AR9300_PAPRD_SCALE_1);
	पूर्ण
पूर्ण

अटल u8 ar9003_get_eepmisc(काष्ठा ath_hw *ah)
अणु
	वापस ah->eeprom.map4k.baseEepHeader.eepMisc;
पूर्ण

स्थिर काष्ठा eeprom_ops eep_ar9300_ops = अणु
	.check_eeprom = ath9k_hw_ar9300_check_eeprom,
	.get_eeprom = ath9k_hw_ar9300_get_eeprom,
	.fill_eeprom = ath9k_hw_ar9300_fill_eeprom,
	.dump_eeprom = ath9k_hw_ar9003_dump_eeprom,
	.get_eeprom_ver = ath9k_hw_ar9300_get_eeprom_ver,
	.get_eeprom_rev = ath9k_hw_ar9300_get_eeprom_rev,
	.set_board_values = ath9k_hw_ar9300_set_board_values,
	.set_addac = ath9k_hw_ar9300_set_addac,
	.set_txघातer = ath9k_hw_ar9300_set_txघातer,
	.get_spur_channel = ath9k_hw_ar9300_get_spur_channel,
	.get_eepmisc = ar9003_get_eepmisc
पूर्ण;
