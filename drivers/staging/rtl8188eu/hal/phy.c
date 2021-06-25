<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188E_PHYCFG_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtl8188e_hal.h>
#समावेश <rf.h>
#समावेश <phy.h>

#घोषणा MAX_PRECMD_CNT 16
#घोषणा MAX_RFDEPENDCMD_CNT 16
#घोषणा MAX_POSTCMD_CNT 16

#घोषणा MAX_DOZE_WAITING_TIMES_9x 64

अटल u32 cal_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i;

	क्रम (i = 0; i <= 31; i++) अणु
		अगर (((biपंचांगask >> i) & 0x1) == 1)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

u32 phy_query_bb_reg(काष्ठा adapter *adapt, u32 regaddr, u32 biपंचांगask)
अणु
	u32 original_value, bit_shअगरt;

	original_value = usb_पढ़ो32(adapt, regaddr);
	bit_shअगरt = cal_bit_shअगरt(biपंचांगask);
	वापस (original_value & biपंचांगask) >> bit_shअगरt;
पूर्ण

व्योम phy_set_bb_reg(काष्ठा adapter *adapt, u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	u32 original_value, bit_shअगरt;

	अगर (biपंचांगask != bMaskDWord) अणु /* अगर not "double word" ग_लिखो */
		original_value = usb_पढ़ो32(adapt, regaddr);
		bit_shअगरt = cal_bit_shअगरt(biपंचांगask);
		data = (original_value & (~biपंचांगask)) | (data << bit_shअगरt);
	पूर्ण

	usb_ग_लिखो32(adapt, regaddr, data);
पूर्ण

अटल u32 rf_serial_पढ़ो(काष्ठा adapter *adapt, क्रमागत rf_radio_path rfpath, u32 offset)
अणु
	u32 ret = 0;
	काष्ठा bb_reg_def *phyreg = &adapt->HalData->PHYRegDef[rfpath];
	u32 पंचांगpदीर्घ, पंचांगpदीर्घ2;
	u8 rfpi_enable = 0;

	offset &= 0xff;

	पंचांगpदीर्घ = phy_query_bb_reg(adapt, rFPGA0_XA_HSSIParameter2, bMaskDWord);
	अगर (rfpath == RF_PATH_A)
		पंचांगpदीर्घ2 = पंचांगpदीर्घ;
	अन्यथा
		पंचांगpदीर्घ2 = phy_query_bb_reg(adapt, phyreg->rfHSSIPara2,
					    bMaskDWord);

	पंचांगpदीर्घ2 = (पंचांगpदीर्घ2 & (~bLSSIReadAddress)) |
		   (offset << 23) | bLSSIReadEdge;

	phy_set_bb_reg(adapt, rFPGA0_XA_HSSIParameter2, bMaskDWord,
		       पंचांगpदीर्घ & (~bLSSIReadEdge));
	udelay(10);

	phy_set_bb_reg(adapt, phyreg->rfHSSIPara2, bMaskDWord, पंचांगpदीर्घ2);
	udelay(100);

	udelay(10);

	अगर (rfpath == RF_PATH_A)
		rfpi_enable = (u8)phy_query_bb_reg(adapt, rFPGA0_XA_HSSIParameter1, BIT(8));
	अन्यथा अगर (rfpath == RF_PATH_B)
		rfpi_enable = (u8)phy_query_bb_reg(adapt, rFPGA0_XB_HSSIParameter1, BIT(8));

	अगर (rfpi_enable)
		ret = phy_query_bb_reg(adapt, phyreg->rfLSSIReadBackPi,
				       bLSSIReadBackData);
	अन्यथा
		ret = phy_query_bb_reg(adapt, phyreg->rfLSSIReadBack,
				       bLSSIReadBackData);
	वापस ret;
पूर्ण

अटल व्योम rf_serial_ग_लिखो(काष्ठा adapter *adapt,
			    क्रमागत rf_radio_path rfpath, u32 offset,
			    u32 data)
अणु
	u32 data_and_addr = 0;
	काष्ठा bb_reg_def *phyreg = &adapt->HalData->PHYRegDef[rfpath];

	offset &= 0xff;
	data_and_addr = ((offset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	phy_set_bb_reg(adapt, phyreg->rf3wireOffset, bMaskDWord, data_and_addr);
पूर्ण

u32 rtw_hal_पढ़ो_rfreg(काष्ठा adapter *adapt, क्रमागत rf_radio_path rf_path,
		       u32 reg_addr, u32 bit_mask)
अणु
	u32 original_value, bit_shअगरt;

	original_value = rf_serial_पढ़ो(adapt, rf_path, reg_addr);
	bit_shअगरt =  cal_bit_shअगरt(bit_mask);
	वापस (original_value & bit_mask) >> bit_shअगरt;
पूर्ण

व्योम phy_set_rf_reg(काष्ठा adapter *adapt, क्रमागत rf_radio_path rf_path,
		    u32 reg_addr, u32 bit_mask, u32 data)
अणु
	u32 original_value, bit_shअगरt;

	/*  RF data is 12 bits only */
	अगर (bit_mask != bRFRegOffsetMask) अणु
		original_value = rf_serial_पढ़ो(adapt, rf_path, reg_addr);
		bit_shअगरt =  cal_bit_shअगरt(bit_mask);
		data = (original_value & (~bit_mask)) | (data << bit_shअगरt);
	पूर्ण

	rf_serial_ग_लिखो(adapt, rf_path, reg_addr, data);
पूर्ण

अटल व्योम get_tx_घातer_index(काष्ठा adapter *adapt, u8 channel, u8 *cck_pwr,
			       u8 *ofdm_pwr, u8 *bw20_pwr, u8 *bw40_pwr)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	u8 index = (channel - 1);
	u8 TxCount = 0, path_nums;

	path_nums = 1;

	क्रम (TxCount = 0; TxCount < path_nums; TxCount++) अणु
		अगर (TxCount == RF_PATH_A) अणु
			cck_pwr[TxCount] = hal_data->Index24G_CCK_Base[TxCount][index];
			ofdm_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index] +
					    hal_data->OFDM_24G_Dअगरf[TxCount][RF_PATH_A];

			bw20_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index] +
					    hal_data->BW20_24G_Dअगरf[TxCount][RF_PATH_A];
			bw40_pwr[TxCount] = hal_data->Index24G_BW40_Base[TxCount][index];
		पूर्ण अन्यथा अगर (TxCount == RF_PATH_B) अणु
			cck_pwr[TxCount] = hal_data->Index24G_CCK_Base[TxCount][index];
			ofdm_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index] +
			hal_data->BW20_24G_Dअगरf[RF_PATH_A][index] +
			hal_data->BW20_24G_Dअगरf[TxCount][index];

			bw20_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index] +
			hal_data->BW20_24G_Dअगरf[TxCount][RF_PATH_A] +
			hal_data->BW20_24G_Dअगरf[TxCount][index];
			bw40_pwr[TxCount] = hal_data->Index24G_BW40_Base[TxCount][index];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम phy_घातer_index_check(काष्ठा adapter *adapt, u8 channel,
				  u8 *cck_pwr, u8 *ofdm_pwr, u8 *bw20_pwr,
				  u8 *bw40_pwr)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;

	hal_data->CurrentCckTxPwrIdx = cck_pwr[0];
	hal_data->CurrentOfdm24GTxPwrIdx = ofdm_pwr[0];
	hal_data->CurrentBW2024GTxPwrIdx = bw20_pwr[0];
	hal_data->CurrentBW4024GTxPwrIdx = bw40_pwr[0];
पूर्ण

व्योम phy_set_tx_घातer_level(काष्ठा adapter *adapt, u8 channel)
अणु
	u8 cck_pwr[MAX_TX_COUNT] = अणु0पूर्ण;
	u8 ofdm_pwr[MAX_TX_COUNT] = अणु0पूर्ण;/*  [0]:RF-A, [1]:RF-B */
	u8 bw20_pwr[MAX_TX_COUNT] = अणु0पूर्ण;
	u8 bw40_pwr[MAX_TX_COUNT] = अणु0पूर्ण;

	get_tx_घातer_index(adapt, channel, &cck_pwr[0], &ofdm_pwr[0],
			   &bw20_pwr[0], &bw40_pwr[0]);

	phy_घातer_index_check(adapt, channel, &cck_pwr[0], &ofdm_pwr[0],
			      &bw20_pwr[0], &bw40_pwr[0]);

	rtl88eu_phy_rf6052_set_cck_txघातer(adapt, &cck_pwr[0]);
	rtl88eu_phy_rf6052_set_ofdm_txघातer(adapt, &ofdm_pwr[0], &bw20_pwr[0],
					    &bw40_pwr[0], channel);
पूर्ण

अटल व्योम phy_set_bw_mode_callback(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	u8 reg_bw_opmode;
	u8 reg_prsr_rsc;

	अगर (adapt->bDriverStopped)
		वापस;

	/* Set MAC रेजिस्टर */

	reg_bw_opmode = usb_पढ़ो8(adapt, REG_BWOPMODE);
	reg_prsr_rsc = usb_पढ़ो8(adapt, REG_RRSR + 2);

	चयन (hal_data->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		usb_ग_लिखो8(adapt, REG_BWOPMODE, reg_bw_opmode);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		usb_ग_लिखो8(adapt, REG_BWOPMODE, reg_bw_opmode);
		reg_prsr_rsc = (reg_prsr_rsc & 0x90) |
			       (hal_data->nCur40MhzPrimeSC << 5);
		usb_ग_लिखो8(adapt, REG_RRSR + 2, reg_prsr_rsc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Set PHY related रेजिस्टर */
	चयन (hal_data->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		phy_set_bb_reg(adapt, rFPGA0_RFMOD, bRFMOD, 0x0);
		phy_set_bb_reg(adapt, rFPGA1_RFMOD, bRFMOD, 0x0);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_40:
		phy_set_bb_reg(adapt, rFPGA0_RFMOD, bRFMOD, 0x1);
		phy_set_bb_reg(adapt, rFPGA1_RFMOD, bRFMOD, 0x1);
		/* Set Control channel to upper or lower.
		 * These settings are required only क्रम 40MHz
		 */
		phy_set_bb_reg(adapt, rCCK0_System, bCCKSideBand,
			       (hal_data->nCur40MhzPrimeSC >> 1));
		phy_set_bb_reg(adapt, rOFDM1_LSTF, 0xC00,
			       hal_data->nCur40MhzPrimeSC);
		phy_set_bb_reg(adapt, 0x818, (BIT(26) | BIT(27)),
			       (hal_data->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Set RF related रेजिस्टर */
	rtl88eu_phy_rf6052_set_bandwidth(adapt, hal_data->CurrentChannelBW);
पूर्ण

व्योम rtw_hal_set_bwmode(काष्ठा adapter *adapt, क्रमागत ht_channel_width bandwidth,
			अचिन्हित अक्षर offset)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	क्रमागत ht_channel_width पंचांगp_bw = hal_data->CurrentChannelBW;

	hal_data->CurrentChannelBW = bandwidth;
	hal_data->nCur40MhzPrimeSC = offset;

	अगर ((!adapt->bDriverStopped) && (!adapt->bSurpriseRemoved))
		phy_set_bw_mode_callback(adapt);
	अन्यथा
		hal_data->CurrentChannelBW = पंचांगp_bw;
पूर्ण

अटल व्योम phy_sw_chnl_callback(काष्ठा adapter *adapt, u8 channel)
अणु
	u32 param1, param2;
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;

	phy_set_tx_घातer_level(adapt, channel);

	param1 = RF_CHNLBW;
	param2 = channel;
	hal_data->RfRegChnlVal[0] = (hal_data->RfRegChnlVal[0] &
					  0xfffffc00) | param2;
	phy_set_rf_reg(adapt, 0, param1,
		       bRFRegOffsetMask, hal_data->RfRegChnlVal[0]);
पूर्ण

व्योम rtw_hal_set_chan(काष्ठा adapter *adapt, u8 channel)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	u8 पंचांगpchannel = hal_data->CurrentChannel;

	अगर (channel == 0)
		channel = 1;

	hal_data->CurrentChannel = channel;

	अगर ((!adapt->bDriverStopped) && (!adapt->bSurpriseRemoved))
		phy_sw_chnl_callback(adapt, channel);
	अन्यथा
		hal_data->CurrentChannel = पंचांगpchannel;
पूर्ण

#घोषणा ODM_TXPWRTRACK_MAX_IDX_88E  6

व्योम rtl88eu_dm_txघातer_track_adjust(काष्ठा odm_dm_काष्ठा *dm_odm, u8 type,
				     u8 *direction, u32 *out_ग_लिखो_val)
अणु
	u8 pwr_value = 0;
	/*  Tx घातer tracking BB swing table. */
	अगर (type == 0) अणु /* For OFDM adjust */
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("BbSwingIdxOfdm = %d BbSwingFlagOfdm=%d\n",
			     dm_odm->BbSwingIdxOfdm, dm_odm->BbSwingFlagOfdm));

		अगर (dm_odm->BbSwingIdxOfdm <= dm_odm->BbSwingIdxOfdmBase) अणु
			*direction = 1;
			pwr_value = dm_odm->BbSwingIdxOfdmBase -
				     dm_odm->BbSwingIdxOfdm;
		पूर्ण अन्यथा अणु
			*direction = 2;
			pwr_value = dm_odm->BbSwingIdxOfdm -
				     dm_odm->BbSwingIdxOfdmBase;
		पूर्ण

	पूर्ण अन्यथा अगर (type == 1) अणु /* For CCK adjust. */
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("dm_odm->BbSwingIdxCck = %d dm_odm->BbSwingIdxCckBase = %d\n",
			     dm_odm->BbSwingIdxCck, dm_odm->BbSwingIdxCckBase));

		अगर (dm_odm->BbSwingIdxCck <= dm_odm->BbSwingIdxCckBase) अणु
			*direction = 1;
			pwr_value = dm_odm->BbSwingIdxCckBase -
				     dm_odm->BbSwingIdxCck;
		पूर्ण अन्यथा अणु
			*direction = 2;
			pwr_value = dm_odm->BbSwingIdxCck -
				     dm_odm->BbSwingIdxCckBase;
		पूर्ण
	पूर्ण

	अगर (pwr_value >= ODM_TXPWRTRACK_MAX_IDX_88E && *direction == 1)
		pwr_value = ODM_TXPWRTRACK_MAX_IDX_88E;

	*out_ग_लिखो_val = pwr_value | (pwr_value << 8) | (pwr_value << 16) |
			 (pwr_value << 24);
पूर्ण

अटल व्योम dm_txpwr_track_setpwr(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	अगर (dm_odm->BbSwingFlagOfdm || dm_odm->BbSwingFlagCck) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("%s CH=%d\n", __func__, *dm_odm->pChannel));
		phy_set_tx_घातer_level(dm_odm->Adapter, *dm_odm->pChannel);
		dm_odm->BbSwingFlagOfdm = false;
		dm_odm->BbSwingFlagCck = false;
	पूर्ण
पूर्ण

व्योम rtl88eu_dm_txघातer_tracking_callback_thermalmeter(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	u8 thermal_val = 0, delta, delta_lck, delta_iqk, offset;
	u8 thermal_avg_count = 0;
	u32 thermal_avg = 0;
	s32 ele_d, temp_cck;
	s8 ofdm_index[2], cck_index = 0;
	s8 ofdm_index_old[2] = अणु0, 0पूर्ण, cck_index_old = 0;
	u32 i = 0, j = 0;

	u8 ofdm_min_index = 6; /* OFDM BB Swing should be less than +3.0dB */
	s8 ofdm_index_mapping[2][index_mapping_NUM_88E] = अणु
		/* 2.4G, decrease घातer */
		अणु0, 0, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 11पूर्ण,
		/* 2.4G, increase घातer */
		अणु0, 0, -1, -2, -3, -4, -4, -4, -4, -5, -7, -8, -9, -9, -10पूर्ण,
	पूर्ण;
	u8 thermal_mapping[2][index_mapping_NUM_88E] = अणु
		/* 2.4G, decrease घातer */
		अणु0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 27पूर्ण,
		/* 2.4G, increase घातer */
		अणु0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 25, 25, 25पूर्ण,
	पूर्ण;
	काष्ठा odm_dm_काष्ठा *dm_odm = &hal_data->odmpriv;

	dm_txpwr_track_setpwr(dm_odm);

	dm_odm->RFCalibrateInfo.TXPowerTrackingCallbackCnt++;

	dm_odm->RFCalibrateInfo.RegA24 = 0x090e1317;

	thermal_val = (u8)rtw_hal_पढ़ो_rfreg(adapt, RF_PATH_A,
					   RF_T_METER_88E, 0xfc00);

	अगर (thermal_val) अणु
		/* Query OFDM path A शेष setting */
		ele_d = phy_query_bb_reg(adapt, rOFDM0_XATxIQImbalance, bMaskDWord) & bMaskOFDM_D;
		क्रम (i = 0; i < OFDM_TABLE_SIZE_92D; i++) अणु
			अगर (ele_d == (OFDMSwingTable[i] & bMaskOFDM_D)) अणु
				ofdm_index_old[0] = (u8)i;
				dm_odm->BbSwingIdxOfdmBase = (u8)i;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Query CCK शेष setting From 0xa24 */
		temp_cck = dm_odm->RFCalibrateInfo.RegA24;

		क्रम (i = 0; i < CCK_TABLE_SIZE; i++) अणु
			अगर ((dm_odm->RFCalibrateInfo.bCCKinCH14 &&
			     स_भेद(&temp_cck, &CCKSwingTable_Ch14[i][2], 4)) ||
			    स_भेद(&temp_cck, &CCKSwingTable_Ch1_Ch13[i][2], 4)) अणु
				cck_index_old = (u8)i;
				dm_odm->BbSwingIdxCckBase = (u8)i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!dm_odm->RFCalibrateInfo.ThermalValue) अणु
			dm_odm->RFCalibrateInfo.ThermalValue = hal_data->EEPROMThermalMeter;
			dm_odm->RFCalibrateInfo.ThermalValue_LCK = thermal_val;
			dm_odm->RFCalibrateInfo.ThermalValue_IQK = thermal_val;

			dm_odm->RFCalibrateInfo.OFDM_index[0] = ofdm_index_old[0];
			dm_odm->RFCalibrateInfo.CCK_index = cck_index_old;
		पूर्ण

		/* calculate average thermal meter */
		dm_odm->RFCalibrateInfo.ThermalValue_AVG[dm_odm->RFCalibrateInfo.ThermalValue_AVG_index] = thermal_val;
		dm_odm->RFCalibrateInfo.ThermalValue_AVG_index++;
		अगर (dm_odm->RFCalibrateInfo.ThermalValue_AVG_index == AVG_THERMAL_NUM_88E)
			dm_odm->RFCalibrateInfo.ThermalValue_AVG_index = 0;

		क्रम (i = 0; i < AVG_THERMAL_NUM_88E; i++) अणु
			अगर (dm_odm->RFCalibrateInfo.ThermalValue_AVG[i]) अणु
				thermal_avg += dm_odm->RFCalibrateInfo.ThermalValue_AVG[i];
				thermal_avg_count++;
			पूर्ण
		पूर्ण

		अगर (thermal_avg_count)
			thermal_val = (u8)(thermal_avg / thermal_avg_count);

		अगर (dm_odm->RFCalibrateInfo.bDoneTxघातer &&
		    !dm_odm->RFCalibrateInfo.bReloadtxघातerindex) अणु
			delta = असल(thermal_val - dm_odm->RFCalibrateInfo.ThermalValue);
		पूर्ण अन्यथा अणु
			delta = असल(thermal_val - hal_data->EEPROMThermalMeter);
			अगर (dm_odm->RFCalibrateInfo.bReloadtxघातerindex) अणु
				dm_odm->RFCalibrateInfo.bReloadtxघातerindex = false;
				dm_odm->RFCalibrateInfo.bDoneTxघातer = false;
			पूर्ण
		पूर्ण

		delta_lck = असल(dm_odm->RFCalibrateInfo.ThermalValue_LCK - thermal_val);
		delta_iqk = असल(dm_odm->RFCalibrateInfo.ThermalValue_IQK - thermal_val);

		/* Delta temperature is equal to or larger than 20 centigrade.*/
		अगर ((delta_lck >= 8)) अणु
			dm_odm->RFCalibrateInfo.ThermalValue_LCK = thermal_val;
			rtl88eu_phy_lc_calibrate(adapt);
		पूर्ण

		अगर (delta > 0 && dm_odm->RFCalibrateInfo.TxPowerTrackControl) अणु
			delta = असल(hal_data->EEPROMThermalMeter - thermal_val);

			/* calculate new OFDM / CCK offset */
			अगर (thermal_val > hal_data->EEPROMThermalMeter)
				j = 1;
			अन्यथा
				j = 0;
			क्रम (offset = 0; offset < index_mapping_NUM_88E; offset++) अणु
				अगर (delta < thermal_mapping[j][offset]) अणु
					अगर (offset != 0)
						offset--;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (offset >= index_mapping_NUM_88E)
				offset = index_mapping_NUM_88E - 1;

			/* Updating ofdm_index values with new OFDM / CCK offset */
			ofdm_index[0] = dm_odm->RFCalibrateInfo.OFDM_index[0] + ofdm_index_mapping[j][offset];
			अगर (ofdm_index[0] > OFDM_TABLE_SIZE_92D - 1)
				ofdm_index[0] = OFDM_TABLE_SIZE_92D - 1;
			अन्यथा अगर (ofdm_index[0] < ofdm_min_index)
				ofdm_index[0] = ofdm_min_index;

			cck_index = dm_odm->RFCalibrateInfo.CCK_index + ofdm_index_mapping[j][offset];
			अगर (cck_index > CCK_TABLE_SIZE - 1)
				cck_index = CCK_TABLE_SIZE - 1;
			अन्यथा अगर (cck_index < 0)
				cck_index = 0;

			/* 2 temporarily हटाओ bNOPG */
			/* Config by SwingTable */
			अगर (dm_odm->RFCalibrateInfo.TxPowerTrackControl) अणु
				dm_odm->RFCalibrateInfo.bDoneTxघातer = true;

				/*  Revse TX घातer table. */
				dm_odm->BbSwingIdxOfdm = (u8)ofdm_index[0];
				dm_odm->BbSwingIdxCck = (u8)cck_index;

				अगर (dm_odm->BbSwingIdxOfdmCurrent != dm_odm->BbSwingIdxOfdm) अणु
					dm_odm->BbSwingIdxOfdmCurrent = dm_odm->BbSwingIdxOfdm;
					dm_odm->BbSwingFlagOfdm = true;
				पूर्ण

				अगर (dm_odm->BbSwingIdxCckCurrent != dm_odm->BbSwingIdxCck) अणु
					dm_odm->BbSwingIdxCckCurrent = dm_odm->BbSwingIdxCck;
					dm_odm->BbSwingFlagCck = true;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Delta temperature is equal to or larger than 20 centigrade.*/
		अगर (delta_iqk >= 8) अणु
			dm_odm->RFCalibrateInfo.ThermalValue_IQK = thermal_val;
			rtl88eu_phy_iq_calibrate(adapt, false);
		पूर्ण
		/* update thermal meter value */
		अगर (dm_odm->RFCalibrateInfo.TxPowerTrackControl)
			dm_odm->RFCalibrateInfo.ThermalValue = thermal_val;
	पूर्ण
	dm_odm->RFCalibrateInfo.TXPowercount = 0;
पूर्ण

#घोषणा MAX_TOLERANCE 5

अटल u8 phy_path_a_iqk(काष्ठा adapter *adapt, bool config_pathb)
अणु
	u32 reg_eac, reg_e94, reg_e9c;
	u8 result = 0x00;

	/* 1 Tx IQK */
	/* path-A IQK setting */
	phy_set_bb_reg(adapt, rTx_IQK_Tone_A, bMaskDWord, 0x10008c1c);
	phy_set_bb_reg(adapt, rRx_IQK_Tone_A, bMaskDWord, 0x30008c1c);
	phy_set_bb_reg(adapt, rTx_IQK_PI_A, bMaskDWord, 0x8214032a);
	phy_set_bb_reg(adapt, rRx_IQK_PI_A, bMaskDWord, 0x28160000);

	/* LO calibration setting */
	phy_set_bb_reg(adapt, rIQK_AGC_Rsp, bMaskDWord, 0x00462911);

	/* One shot, path A LOK & IQK */
	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	mdelay(IQK_DELAY_TIME_88E);

	reg_eac = phy_query_bb_reg(adapt, rRx_Power_After_IQK_A_2, bMaskDWord);
	reg_e94 = phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	reg_e9c = phy_query_bb_reg(adapt, rTx_Power_After_IQK_A, bMaskDWord);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	वापस result;
पूर्ण

अटल u8 phy_path_a_rx_iqk(काष्ठा adapter *adapt, bool configPathB)
अणु
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4, u4पंचांगp;
	u8 result = 0x00;
	काष्ठा odm_dm_काष्ठा *dm_odm = &adapt->HalData->odmpriv;

	/* 1 Get TXIMR setting */
	/* modअगरy RXIQK mode table */
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x00000000);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_WE_LUT, bRFRegOffsetMask, 0x800a0);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x30000);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0000f);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf117B);

	/* PA,PAD off */
	phy_set_rf_reg(adapt, RF_PATH_A, 0xdf, bRFRegOffsetMask, 0x980);
	phy_set_rf_reg(adapt, RF_PATH_A, 0x56, bRFRegOffsetMask, 0x51000);

	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x80800000);

	/* IQK setting */
	phy_set_bb_reg(adapt, rTx_IQK, bMaskDWord, 0x01007c00);
	phy_set_bb_reg(adapt, rRx_IQK, bMaskDWord, 0x81004800);

	/* path-A IQK setting */
	phy_set_bb_reg(adapt, rTx_IQK_Tone_A, bMaskDWord, 0x10008c1c);
	phy_set_bb_reg(adapt, rRx_IQK_Tone_A, bMaskDWord, 0x30008c1c);
	phy_set_bb_reg(adapt, rTx_IQK_PI_A, bMaskDWord, 0x82160c1f);
	phy_set_bb_reg(adapt, rRx_IQK_PI_A, bMaskDWord, 0x28160000);

	/* LO calibration setting */
	phy_set_bb_reg(adapt, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

	/* One shot, path A LOK & IQK */
	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/* delay x ms */
	mdelay(IQK_DELAY_TIME_88E);

	/* Check failed */
	reg_eac = phy_query_bb_reg(adapt, rRx_Power_After_IQK_A_2, bMaskDWord);
	reg_e94 = phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	reg_e9c = phy_query_bb_reg(adapt, rTx_Power_After_IQK_A, bMaskDWord);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा					/* अगर Tx not OK, ignore Rx */
		वापस result;

	u4पंचांगp = 0x80007C00 | (reg_e94 & 0x3FF0000)  | ((reg_e9c & 0x3FF0000) >> 16);
	phy_set_bb_reg(adapt, rTx_IQK, bMaskDWord, u4पंचांगp);

	/* 1 RX IQK */
	/* modअगरy RXIQK mode table */
	ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
		     ("Path-A Rx IQK modify RXIQK mode table 2!\n"));
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x00000000);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_WE_LUT, bRFRegOffsetMask, 0x800a0);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x30000);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0000f);
	phy_set_rf_reg(adapt, RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7ffa);
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x80800000);

	/* IQK setting */
	phy_set_bb_reg(adapt, rRx_IQK, bMaskDWord, 0x01004800);

	/* path-A IQK setting */
	phy_set_bb_reg(adapt, rTx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	phy_set_bb_reg(adapt, rRx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	phy_set_bb_reg(adapt, rTx_IQK_PI_A, bMaskDWord, 0x82160c05);
	phy_set_bb_reg(adapt, rRx_IQK_PI_A, bMaskDWord, 0x28160c1f);

	/* LO calibration setting */
	phy_set_bb_reg(adapt, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	phy_set_bb_reg(adapt, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	mdelay(IQK_DELAY_TIME_88E);

	/*  Check failed */
	reg_eac = phy_query_bb_reg(adapt, rRx_Power_After_IQK_A_2, bMaskDWord);
	reg_e94 = phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	reg_e9c = phy_query_bb_reg(adapt, rTx_Power_After_IQK_A, bMaskDWord);
	reg_ea4 = phy_query_bb_reg(adapt, rRx_Power_Beक्रमe_IQK_A_2, bMaskDWord);

	/* reload RF 0xdf */
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x00000000);
	phy_set_rf_reg(adapt, RF_PATH_A, 0xdf, bRFRegOffsetMask, 0x180);

	अगर (!(reg_eac & BIT(27)) && /* अगर Tx is OK, check whether Rx is OK */
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
			     ("Path A Rx IQK fail!!\n"));

	वापस result;
पूर्ण

अटल u8 phy_path_b_iqk(काष्ठा adapter *adapt)
अणु
	u32 regeac, regeb4, regebc, regec4, regecc;
	u8 result = 0x00;
	काष्ठा odm_dm_काष्ठा *dm_odm = &adapt->HalData->odmpriv;

	/* One shot, path B LOK & IQK */
	phy_set_bb_reg(adapt, rIQK_AGC_Cont, bMaskDWord, 0x00000002);
	phy_set_bb_reg(adapt, rIQK_AGC_Cont, bMaskDWord, 0x00000000);

	mdelay(IQK_DELAY_TIME_88E);

	regeac = phy_query_bb_reg(adapt, rRx_Power_After_IQK_A_2, bMaskDWord);
	regeb4 = phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_B, bMaskDWord);
	regebc = phy_query_bb_reg(adapt, rTx_Power_After_IQK_B, bMaskDWord);
	regec4 = phy_query_bb_reg(adapt, rRx_Power_Beक्रमe_IQK_B_2, bMaskDWord);
	regecc = phy_query_bb_reg(adapt, rRx_Power_After_IQK_B_2, bMaskDWord);

	अगर (!(regeac & BIT(31)) &&
	    (((regeb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((regebc & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;

	अगर (!(regeac & BIT(30)) &&
	    (((regec4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((regecc & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION,
			     ODM_DBG_LOUD,  ("Path B Rx IQK fail!!\n"));
	वापस result;
पूर्ण

अटल व्योम patha_fill_iqk(काष्ठा adapter *adapt, bool iqkok, s32 result[][8],
			   u8 final_candidate, bool txonly)
अणु
	u32 oldval_0, x, tx0_a, reg;
	s32 y, tx0_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (iqkok) अणु
		oldval_0 = (phy_query_bb_reg(adapt, rOFDM0_XATxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		x = result[final_candidate][0];
		अगर ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;

		tx0_a = (x * oldval_0) >> 8;
		phy_set_bb_reg(adapt, rOFDM0_XATxIQImbalance, 0x3FF, tx0_a);
		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(31),
			       ((x * oldval_0 >> 7) & 0x1));

		y = result[final_candidate][1];
		अगर ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;

		tx0_c = (y * oldval_0) >> 8;
		phy_set_bb_reg(adapt, rOFDM0_XCTxAFE, 0xF0000000,
			       ((tx0_c & 0x3C0) >> 6));
		phy_set_bb_reg(adapt, rOFDM0_XATxIQImbalance, 0x003F0000,
			       (tx0_c & 0x3F));
		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(29),
			       ((y * oldval_0 >> 7) & 0x1));

		अगर (txonly)
			वापस;

		reg = result[final_candidate][2];
		phy_set_bb_reg(adapt, rOFDM0_XARxIQImbalance, 0x3FF, reg);

		reg = result[final_candidate][3] & 0x3F;
		phy_set_bb_reg(adapt, rOFDM0_XARxIQImbalance, 0xFC00, reg);

		reg = (result[final_candidate][3] >> 6) & 0xF;
		phy_set_bb_reg(adapt, rOFDM0_RxIQExtAnta, 0xF0000000, reg);
	पूर्ण
पूर्ण

अटल व्योम pathb_fill_iqk(काष्ठा adapter *adapt, bool iqkok, s32 result[][8],
			   u8 final_candidate, bool txonly)
अणु
	u32 oldval_1, x, tx1_a, reg;
	s32 y, tx1_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (iqkok) अणु
		oldval_1 = (phy_query_bb_reg(adapt, rOFDM0_XBTxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		x = result[final_candidate][4];
		अगर ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx1_a = (x * oldval_1) >> 8;
		phy_set_bb_reg(adapt, rOFDM0_XBTxIQImbalance, 0x3FF, tx1_a);

		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(27),
			       ((x * oldval_1 >> 7) & 0x1));

		y = result[final_candidate][5];
		अगर ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;

		tx1_c = (y * oldval_1) >> 8;

		phy_set_bb_reg(adapt, rOFDM0_XDTxAFE, 0xF0000000,
			       ((tx1_c & 0x3C0) >> 6));
		phy_set_bb_reg(adapt, rOFDM0_XBTxIQImbalance, 0x003F0000,
			       (tx1_c & 0x3F));
		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(25),
			       ((y * oldval_1 >> 7) & 0x1));

		अगर (txonly)
			वापस;

		reg = result[final_candidate][6];
		phy_set_bb_reg(adapt, rOFDM0_XBRxIQImbalance, 0x3FF, reg);

		reg = result[final_candidate][7] & 0x3F;
		phy_set_bb_reg(adapt, rOFDM0_XBRxIQImbalance, 0xFC00, reg);

		reg = (result[final_candidate][7] >> 6) & 0xF;
		phy_set_bb_reg(adapt, rOFDM0_AGCRSSITable, 0x0000F000, reg);
	पूर्ण
पूर्ण

अटल व्योम save_adda_रेजिस्टरs(काष्ठा adapter *adapt, स्थिर u32 *addareg,
				u32 *backup, u32 रेजिस्टर_num)
अणु
	u32 i;

	क्रम (i = 0; i < रेजिस्टर_num; i++)
		backup[i] = phy_query_bb_reg(adapt, addareg[i], bMaskDWord);
पूर्ण

अटल व्योम save_mac_रेजिस्टरs(काष्ठा adapter *adapt, स्थिर u32 *mac_reg,
			       u32 *backup)
अणु
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		backup[i] = usb_पढ़ो8(adapt, mac_reg[i]);

	backup[i] = usb_पढ़ो32(adapt, mac_reg[i]);
पूर्ण

अटल व्योम reload_adda_reg(काष्ठा adapter *adapt, स्थिर u32 *adda_reg,
			    u32 *backup, u32 regiester_num)
अणु
	u32 i;

	क्रम (i = 0; i < regiester_num; i++)
		phy_set_bb_reg(adapt, adda_reg[i], bMaskDWord, backup[i]);
पूर्ण

अटल व्योम reload_mac_रेजिस्टरs(काष्ठा adapter *adapt, स्थिर u32 *mac_reg,
				 u32 *backup)
अणु
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		usb_ग_लिखो8(adapt, mac_reg[i], (u8)backup[i]);

	usb_ग_लिखो32(adapt, mac_reg[i], backup[i]);
पूर्ण

अटल व्योम path_adda_on(काष्ठा adapter *adapt, स्थिर u32 *adda_reg,
			 bool is_path_a_on, bool is2t)
अणु
	u32 path_on;
	u32 i;

	अगर (!is2t) अणु
		path_on = 0x0bdb25a0;
		phy_set_bb_reg(adapt, adda_reg[0], bMaskDWord, 0x0b1b25a0);
	पूर्ण अन्यथा अणु
		path_on = is_path_a_on ? 0x04db25a4 : 0x0b1b25a4;
		phy_set_bb_reg(adapt, adda_reg[0], bMaskDWord, path_on);
	पूर्ण

	क्रम (i = 1; i < IQK_ADDA_REG_NUM; i++)
		phy_set_bb_reg(adapt, adda_reg[i], bMaskDWord, path_on);
पूर्ण

अटल व्योम mac_setting_calibration(काष्ठा adapter *adapt, स्थिर u32 *mac_reg,
				    u32 *backup)
अणु
	u32 i = 0;

	usb_ग_लिखो8(adapt, mac_reg[i], 0x3F);

	क्रम (i = 1; i < (IQK_MAC_REG_NUM - 1); i++)
		usb_ग_लिखो8(adapt, mac_reg[i], (u8)(backup[i] & (~BIT(3))));

	usb_ग_लिखो8(adapt, mac_reg[i], (u8)(backup[i] & (~BIT(5))));
पूर्ण

अटल व्योम path_a_standby(काष्ठा adapter *adapt)
अणु
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x0);
	phy_set_bb_reg(adapt, 0x840, bMaskDWord, 0x00010000);
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x80800000);
पूर्ण

अटल व्योम pi_mode_चयन(काष्ठा adapter *adapt, bool pi_mode)
अणु
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	phy_set_bb_reg(adapt, rFPGA0_XA_HSSIParameter1, bMaskDWord, mode);
	phy_set_bb_reg(adapt, rFPGA0_XB_HSSIParameter1, bMaskDWord, mode);
पूर्ण

अटल bool simularity_compare(काष्ठा adapter *adapt, s32 resulta[][8],
			       u8 c1, u8 c2)
अणु
	u32 i, j, dअगरf, sim_biपंचांगap = 0, bound;
	u8 final_candidate[2] = अणु0xFF, 0xFFपूर्ण;	/* क्रम path A and path B */
	bool result = true;
	s32 पंचांगp1 = 0, पंचांगp2 = 0;

	bound = 4;

	क्रम (i = 0; i < bound; i++) अणु
		अगर ((i == 1) || (i == 3) || (i == 5) || (i == 7)) अणु
			अगर ((resulta[c1][i] & 0x00000200) != 0)
				पंचांगp1 = resulta[c1][i] | 0xFFFFFC00;
			अन्यथा
				पंचांगp1 = resulta[c1][i];

			अगर ((resulta[c2][i] & 0x00000200) != 0)
				पंचांगp2 = resulta[c2][i] | 0xFFFFFC00;
			अन्यथा
				पंचांगp2 = resulta[c2][i];
		पूर्ण अन्यथा अणु
			पंचांगp1 = resulta[c1][i];
			पंचांगp2 = resulta[c2][i];
		पूर्ण

		dअगरf = असल(पंचांगp1 - पंचांगp2);

		अगर (dअगरf > MAX_TOLERANCE) अणु
			अगर ((i == 2 || i == 6) && !sim_biपंचांगap) अणु
				अगर (resulta[c1][i] + resulta[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				अन्यथा अगर (resulta[c2][i] + resulta[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				अन्यथा
					sim_biपंचांगap = sim_biपंचांगap | (1 << i);
			पूर्ण अन्यथा अणु
				sim_biपंचांगap = sim_biपंचांगap | (1 << i);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sim_biपंचांगap == 0) अणु
		क्रम (i = 0; i < (bound / 4); i++) अणु
			अगर (final_candidate[i] != 0xFF) अणु
				क्रम (j = i * 4; j < (i + 1) * 4 - 2; j++)
					resulta[3][j] = resulta[final_candidate[i]][j];
				result = false;
			पूर्ण
		पूर्ण
		वापस result;
	पूर्ण

	अगर (!(sim_biपंचांगap & 0x03)) अणु		   /* path A TX OK */
		क्रम (i = 0; i < 2; i++)
			resulta[3][i] = resulta[c1][i];
	पूर्ण
	अगर (!(sim_biपंचांगap & 0x0c)) अणु		   /* path A RX OK */
		क्रम (i = 2; i < 4; i++)
			resulta[3][i] = resulta[c1][i];
	पूर्ण

	अगर (!(sim_biपंचांगap & 0x30)) अणु /* path B TX OK */
		क्रम (i = 4; i < 6; i++)
			resulta[3][i] = resulta[c1][i];
	पूर्ण

	अगर (!(sim_biपंचांगap & 0xc0)) अणु /* path B RX OK */
		क्रम (i = 6; i < 8; i++)
			resulta[3][i] = resulta[c1][i];
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम phy_iq_calibrate(काष्ठा adapter *adapt, s32 result[][8],
			     u8 t, bool is2t)
अणु
	काष्ठा odm_dm_काष्ठा *dm_odm = &adapt->HalData->odmpriv;
	u32 i;
	u8 path_a_ok, path_b_ok;
	अटल स्थिर u32 adda_reg[IQK_ADDA_REG_NUM] = अणु
		rFPGA0_XCD_SwitchControl, rBlue_Tooth,
		rRx_Wait_CCA, rTx_CCK_RFON,
		rTx_CCK_BBON, rTx_OFDM_RFON,
		rTx_OFDM_BBON, rTx_To_Rx,
		rTx_To_Tx, rRx_CCK,
		rRx_OFDM, rRx_Wait_RIFS,
		rRx_TO_Rx, rStandby,
		rSleep, rPMPD_ANAEN
	पूर्ण;
	अटल स्थिर u32 iqk_mac_reg[IQK_MAC_REG_NUM] = अणु
		REG_TXPAUSE, REG_BCN_CTRL,
		REG_BCN_CTRL_1, REG_GPIO_MUXCFG
	पूर्ण;
	/* since 92C & 92D have the dअगरferent define in IQK_BB_REG */
	अटल स्थिर u32 iqk_bb_reg_92c[IQK_BB_REG_NUM] = अणु
		rOFDM0_TRxPathEnable, rOFDM0_TRMuxPar,
		rFPGA0_XCD_RFInterfaceSW, rConfig_AntA, rConfig_AntB,
		rFPGA0_XAB_RFInterfaceSW, rFPGA0_XA_RFInterfaceOE,
		rFPGA0_XB_RFInterfaceOE, rFPGA0_RFMOD
	पूर्ण;

	u32 retry_count = 9;

	अगर (*dm_odm->mp_mode == 1)
		retry_count = 9;
	अन्यथा
		retry_count = 2;

	अगर (t == 0) अणु
		/*  Save ADDA parameters, turn Path A ADDA on */
		save_adda_रेजिस्टरs(adapt, adda_reg, dm_odm->RFCalibrateInfo.ADDA_backup,
				    IQK_ADDA_REG_NUM);
		save_mac_रेजिस्टरs(adapt, iqk_mac_reg,
				   dm_odm->RFCalibrateInfo.IQK_MAC_backup);
		save_adda_रेजिस्टरs(adapt, iqk_bb_reg_92c,
				    dm_odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
	पूर्ण

	path_adda_on(adapt, adda_reg, true, is2t);
	अगर (t == 0)
		dm_odm->RFCalibrateInfo.bRfPiEnable = (u8)phy_query_bb_reg(adapt, rFPGA0_XA_HSSIParameter1,
									   BIT(8));

	अगर (!dm_odm->RFCalibrateInfo.bRfPiEnable) अणु
		/*  Switch BB to PI mode to करो IQ Calibration. */
		pi_mode_चयन(adapt, true);
	पूर्ण

	/* BB setting */
	phy_set_bb_reg(adapt, rFPGA0_RFMOD, BIT(24), 0x00);
	phy_set_bb_reg(adapt, rOFDM0_TRxPathEnable, bMaskDWord, 0x03a05600);
	phy_set_bb_reg(adapt, rOFDM0_TRMuxPar, bMaskDWord, 0x000800e4);
	phy_set_bb_reg(adapt, rFPGA0_XCD_RFInterfaceSW, bMaskDWord, 0x22204000);

	phy_set_bb_reg(adapt, rFPGA0_XAB_RFInterfaceSW, BIT(10), 0x01);
	phy_set_bb_reg(adapt, rFPGA0_XAB_RFInterfaceSW, BIT(26), 0x01);
	phy_set_bb_reg(adapt, rFPGA0_XA_RFInterfaceOE, BIT(10), 0x00);
	phy_set_bb_reg(adapt, rFPGA0_XB_RFInterfaceOE, BIT(10), 0x00);

	अगर (is2t) अणु
		phy_set_bb_reg(adapt, rFPGA0_XA_LSSIParameter, bMaskDWord,
			       0x00010000);
		phy_set_bb_reg(adapt, rFPGA0_XB_LSSIParameter, bMaskDWord,
			       0x00010000);
	पूर्ण

	/* MAC settings */
	mac_setting_calibration(adapt, iqk_mac_reg,
				dm_odm->RFCalibrateInfo.IQK_MAC_backup);

	/* Page B init */
	/* AP or IQK */
	phy_set_bb_reg(adapt, rConfig_AntA, bMaskDWord, 0x0f600000);

	अगर (is2t)
		phy_set_bb_reg(adapt, rConfig_AntB, bMaskDWord, 0x0f600000);

	/*  IQ calibration setting */
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0x80800000);
	phy_set_bb_reg(adapt, rTx_IQK, bMaskDWord, 0x01007c00);
	phy_set_bb_reg(adapt, rRx_IQK, bMaskDWord, 0x81004800);

	क्रम (i = 0; i < retry_count; i++) अणु
		path_a_ok = phy_path_a_iqk(adapt, is2t);
		अगर (path_a_ok == 0x01) अणु
			result[t][0] = (phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_A,
							 bMaskDWord) & 0x3FF0000) >> 16;
			result[t][1] = (phy_query_bb_reg(adapt, rTx_Power_After_IQK_A,
							 bMaskDWord) & 0x3FF0000) >> 16;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < retry_count; i++) अणु
		path_a_ok = phy_path_a_rx_iqk(adapt, is2t);
		अगर (path_a_ok == 0x03) अणु
			result[t][2] = (phy_query_bb_reg(adapt, rRx_Power_Beक्रमe_IQK_A_2,
							 bMaskDWord) & 0x3FF0000) >> 16;
			result[t][3] = (phy_query_bb_reg(adapt, rRx_Power_After_IQK_A_2,
							 bMaskDWord) & 0x3FF0000) >> 16;
			अवरोध;
		पूर्ण
		ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
			     ("Path A Rx IQK Fail!!\n"));
	पूर्ण

	अगर (path_a_ok == 0x00) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
			     ("Path A IQK failed!!\n"));
	पूर्ण

	अगर (is2t) अणु
		path_a_standby(adapt);

		/*  Turn Path B ADDA on */
		path_adda_on(adapt, adda_reg, false, is2t);

		क्रम (i = 0; i < retry_count; i++) अणु
			path_b_ok = phy_path_b_iqk(adapt);
			अगर (path_b_ok == 0x03) अणु
				result[t][4] = (phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_B,
								 bMaskDWord) & 0x3FF0000) >> 16;
				result[t][5] = (phy_query_bb_reg(adapt, rTx_Power_After_IQK_B,
								 bMaskDWord) & 0x3FF0000) >> 16;
				result[t][6] = (phy_query_bb_reg(adapt, rRx_Power_Beक्रमe_IQK_B_2,
								 bMaskDWord) & 0x3FF0000) >> 16;
				result[t][7] = (phy_query_bb_reg(adapt, rRx_Power_After_IQK_B_2,
								 bMaskDWord) & 0x3FF0000) >> 16;
				अवरोध;
			पूर्ण अन्यथा अगर (i == (retry_count - 1) && path_b_ok == 0x01) अणु	/* Tx IQK OK */
				result[t][4] = (phy_query_bb_reg(adapt, rTx_Power_Beक्रमe_IQK_B,
								 bMaskDWord) & 0x3FF0000) >> 16;
				result[t][5] = (phy_query_bb_reg(adapt, rTx_Power_After_IQK_B,
								 bMaskDWord) & 0x3FF0000) >> 16;
			पूर्ण
		पूर्ण

		अगर (path_b_ok == 0x00) अणु
			ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
				     ("Path B IQK failed!!\n"));
		पूर्ण
	पूर्ण

	/* Back to BB mode, load original value */
	phy_set_bb_reg(adapt, rFPGA0_IQK, bMaskDWord, 0);

	अगर (t != 0) अणु
		अगर (!dm_odm->RFCalibrateInfo.bRfPiEnable) अणु
			/* Switch back BB to SI mode after
			 * finish IQ Calibration.
			 */
			pi_mode_चयन(adapt, false);
		पूर्ण

		/*  Reload ADDA घातer saving parameters */
		reload_adda_reg(adapt, adda_reg, dm_odm->RFCalibrateInfo.ADDA_backup,
				IQK_ADDA_REG_NUM);

		/*  Reload MAC parameters */
		reload_mac_रेजिस्टरs(adapt, iqk_mac_reg,
				     dm_odm->RFCalibrateInfo.IQK_MAC_backup);

		reload_adda_reg(adapt, iqk_bb_reg_92c, dm_odm->RFCalibrateInfo.IQK_BB_backup,
				IQK_BB_REG_NUM);

		/*  Restore RX initial gain */
		phy_set_bb_reg(adapt, rFPGA0_XA_LSSIParameter,
			       bMaskDWord, 0x00032ed3);
		अगर (is2t)
			phy_set_bb_reg(adapt, rFPGA0_XB_LSSIParameter,
				       bMaskDWord, 0x00032ed3);

		/* load 0xe30 IQC शेष value */
		phy_set_bb_reg(adapt, rTx_IQK_Tone_A, bMaskDWord, 0x01008c00);
		phy_set_bb_reg(adapt, rRx_IQK_Tone_A, bMaskDWord, 0x01008c00);
	पूर्ण
पूर्ण

अटल व्योम phy_lc_calibrate(काष्ठा adapter *adapt, bool is2t)
अणु
	u8 पंचांगpreg;
	u32 rf_a_mode = 0, rf_b_mode = 0, lc_cal;

	/* Check continuous TX and Packet TX */
	पंचांगpreg = usb_पढ़ो8(adapt, 0xd03);

	अगर ((पंचांगpreg & 0x70) != 0)
		usb_ग_लिखो8(adapt, 0xd03, पंचांगpreg & 0x8F);
	अन्यथा
		usb_ग_लिखो8(adapt, REG_TXPAUSE, 0xFF);

	अगर ((पंचांगpreg & 0x70) != 0) अणु
		/* 1. Read original RF mode */
		/* Path-A */
		rf_a_mode = rtw_hal_पढ़ो_rfreg(adapt, RF_PATH_A, RF_AC,
					       bMask12Bits);

		/* Path-B */
		अगर (is2t)
			rf_b_mode = rtw_hal_पढ़ो_rfreg(adapt, RF_PATH_B, RF_AC,
						       bMask12Bits);

		/* 2. Set RF mode = standby mode */
		/* Path-A */
		phy_set_rf_reg(adapt, RF_PATH_A, RF_AC, bMask12Bits,
			       (rf_a_mode & 0x8FFFF) | 0x10000);

		/* Path-B */
		अगर (is2t)
			phy_set_rf_reg(adapt, RF_PATH_B, RF_AC, bMask12Bits,
				       (rf_b_mode & 0x8FFFF) | 0x10000);
	पूर्ण

	/* 3. Read RF reg18 */
	lc_cal = rtw_hal_पढ़ो_rfreg(adapt, RF_PATH_A, RF_CHNLBW, bMask12Bits);

	/* 4. Set LC calibration begin bit15 */
	phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bMask12Bits,
		       lc_cal | 0x08000);

	msleep(100);

	/* Restore original situation */
	अगर ((पंचांगpreg & 0x70) != 0) अणु
		/* Deal with continuous TX हाल */
		/* Path-A */
		usb_ग_लिखो8(adapt, 0xd03, पंचांगpreg);
		phy_set_rf_reg(adapt, RF_PATH_A, RF_AC, bMask12Bits, rf_a_mode);

		/* Path-B */
		अगर (is2t)
			phy_set_rf_reg(adapt, RF_PATH_B, RF_AC, bMask12Bits,
				       rf_b_mode);
	पूर्ण अन्यथा अणु
		/* Deal with Packet TX हाल */
		usb_ग_लिखो8(adapt, REG_TXPAUSE, 0x00);
	पूर्ण
पूर्ण

व्योम rtl88eu_phy_iq_calibrate(काष्ठा adapter *adapt, bool recovery)
अणु
	काष्ठा odm_dm_काष्ठा *dm_odm = &adapt->HalData->odmpriv;
	s32 result[4][8];
	u8 i, final;
	bool pathaok, pathbok;
	s32 reg_e94, reg_e9c, reg_ea4, reg_eb4, reg_ebc, reg_ec4;
	bool is12simular, is13simular, is23simular;
	u32 iqk_bb_reg_92c[IQK_BB_REG_NUM] = अणु
		rOFDM0_XARxIQImbalance, rOFDM0_XBRxIQImbalance,
		rOFDM0_ECCAThreshold, rOFDM0_AGCRSSITable,
		rOFDM0_XATxIQImbalance, rOFDM0_XBTxIQImbalance,
		rOFDM0_XCTxAFE, rOFDM0_XDTxAFE,
		rOFDM0_RxIQExtAntaपूर्ण;
	bool is2t;

	is2t = false;

	अगर (!(dm_odm->SupportAbility & ODM_RF_CALIBRATION))
		वापस;

	अगर (recovery) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_INIT, ODM_DBG_LOUD,
			     ("phy_iq_calibrate: Return due to recovery!\n"));
		reload_adda_reg(adapt, iqk_bb_reg_92c,
				dm_odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
		वापस;
	पूर्ण

	स_रखो(result, 0, माप(result));
	क्रम (i = 0; i < 8; i += 2)
		result[3][i] = 0x100;

	final = 0xff;
	pathaok = false;
	pathbok = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;

	क्रम (i = 0; i < 3; i++) अणु
		phy_iq_calibrate(adapt, result, i, is2t);

		अगर (i == 1) अणु
			is12simular = simularity_compare(adapt, result, 0, 1);
			अगर (is12simular) अणु
				final = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 2) अणु
			is13simular = simularity_compare(adapt, result, 0, 2);
			अगर (is13simular) अणु
				final = 0;
				अवरोध;
			पूर्ण
			is23simular = simularity_compare(adapt, result, 1, 2);
			अगर (is23simular)
				final = 1;
			अन्यथा
				final = 3;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		reg_e94 = result[i][0];
		reg_e9c = result[i][1];
		reg_ea4 = result[i][2];
		reg_eb4 = result[i][4];
		reg_ebc = result[i][5];
		reg_ec4 = result[i][6];
	पूर्ण

	अगर (final != 0xff) अणु
		reg_e94 = result[final][0];
		reg_e9c = result[final][1];
		reg_ea4 = result[final][2];
		reg_eb4 = result[final][4];
		reg_ebc = result[final][5];
		dm_odm->RFCalibrateInfo.RegE94 = reg_e94;
		dm_odm->RFCalibrateInfo.RegE9C = reg_e9c;
		dm_odm->RFCalibrateInfo.RegEB4 = reg_eb4;
		dm_odm->RFCalibrateInfo.RegEBC = reg_ebc;
		reg_ec4 = result[final][6];
		pathaok = true;
		pathbok = true;
	पूर्ण अन्यथा अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
			     ("IQK: FAIL use default value\n"));
		dm_odm->RFCalibrateInfo.RegE94 = 0x100;
		dm_odm->RFCalibrateInfo.RegEB4 = 0x100;
		dm_odm->RFCalibrateInfo.RegE9C = 0x0;
		dm_odm->RFCalibrateInfo.RegEBC = 0x0;
	पूर्ण
	अगर (reg_e94 != 0)
		patha_fill_iqk(adapt, pathaok, result, final,
			       (reg_ea4 == 0));
	अगर (is2t) अणु
		अगर (reg_eb4 != 0)
			pathb_fill_iqk(adapt, pathbok, result, final,
				       (reg_ec4 == 0));
	पूर्ण

	अगर (final < 4) अणु
		क्रम (i = 0; i < IQK_Matrix_REG_NUM; i++)
			dm_odm->RFCalibrateInfo.IQKMatrixRegSetting[0].Value[0][i] = result[final][i];
		dm_odm->RFCalibrateInfo.IQKMatrixRegSetting[0].bIQKDone = true;
	पूर्ण

	save_adda_रेजिस्टरs(adapt, iqk_bb_reg_92c,
			    dm_odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
पूर्ण

व्योम rtl88eu_phy_lc_calibrate(काष्ठा adapter *adapt)
अणु
	u32 समयout = 2000, समयcount = 0;
	काष्ठा odm_dm_काष्ठा *dm_odm = &adapt->HalData->odmpriv;

	अगर (!(dm_odm->SupportAbility & ODM_RF_CALIBRATION))
		वापस;

	जबतक (*dm_odm->pbScanInProcess && समयcount < समयout) अणु
		mdelay(50);
		समयcount += 50;
	पूर्ण

	dm_odm->RFCalibrateInfo.bLCKInProgress = true;

	phy_lc_calibrate(adapt, false);

	dm_odm->RFCalibrateInfo.bLCKInProgress = false;
पूर्ण
