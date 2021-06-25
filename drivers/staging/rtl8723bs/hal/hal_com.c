<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HAL_COM_C_

#समावेश <linux/kernel.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश "hal_com_h2c.h"

#समावेश "odm_precomp.h"

u8 rtw_hal_data_init(काष्ठा adapter *padapter)
अणु
	अगर (is_primary_adapter(padapter)) अणु	/* अगर (padapter->isprimary) */
		padapter->hal_data_sz = माप(काष्ठा hal_com_data);
		padapter->HalData = vzalloc(padapter->hal_data_sz);
		अगर (!padapter->HalData)
			वापस _FAIL;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

व्योम rtw_hal_data_deinit(काष्ठा adapter *padapter)
अणु
	अगर (is_primary_adapter(padapter)) अणु	/* अगर (padapter->isprimary) */
		अगर (padapter->HalData) अणु
			vमुक्त(padapter->HalData);
			padapter->HalData = शून्य;
			padapter->hal_data_sz = 0;
		पूर्ण
	पूर्ण
पूर्ण


व्योम dump_chip_info(काष्ठा hal_version	ChipVersion)
अणु
	अक्षर buf[128];
	माप_प्रकार cnt = 0;

	cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "Chip Version Info: CHIP_8723B_%s_",
			IS_NORMAL_CHIP(ChipVersion) ? "Normal_Chip" : "Test_Chip");

	अगर (IS_CHIP_VENDOR_TSMC(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "TSMC_");
	अन्यथा अगर (IS_CHIP_VENDOR_UMC(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "UMC_");
	अन्यथा अगर (IS_CHIP_VENDOR_SMIC(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "SMIC_");

	अगर (IS_A_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "A_CUT_");
	अन्यथा अगर (IS_B_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "B_CUT_");
	अन्यथा अगर (IS_C_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "C_CUT_");
	अन्यथा अगर (IS_D_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "D_CUT_");
	अन्यथा अगर (IS_E_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "E_CUT_");
	अन्यथा अगर (IS_I_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "I_CUT_");
	अन्यथा अगर (IS_J_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "J_CUT_");
	अन्यथा अगर (IS_K_CUT(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "K_CUT_");
	अन्यथा
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt,
				"UNKNOWN_CUT(%d)_", ChipVersion.CUTVersion);

	अगर (IS_1T1R(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "1T1R_");
	अन्यथा अगर (IS_1T2R(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "1T2R_");
	अन्यथा अगर (IS_2T2R(ChipVersion))
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "2T2R_");
	अन्यथा
		cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt,
				"UNKNOWN_RFTYPE(%d)_", ChipVersion.RFType);

	cnt += scnम_लिखो(buf + cnt, माप(buf) - cnt, "RomVer(%d)\n", ChipVersion.ROMVer);
पूर्ण


#घोषणा	EEPROM_CHANNEL_PLAN_BY_HW_MASK	0x80

/*
 * Description:
 *Use hardware(efuse), driver parameter(registry) and शेष channel plan
 *to decide which one should be used.
 *
 * Parameters:
 *padapter			poपूर्णांकer of adapter
 *hw_channel_plan		channel plan from HW (efuse/eeprom)
 *					BIT[7] software configure mode; 0:Enable, 1:disable
 *					BIT[6:0] Channel Plan
 *sw_channel_plan		channel plan from SW (registry/module param)
 *def_channel_plan	channel plan used when HW/SW both invalid
 *AutoLoadFail		efuse स्वतःload fail or not
 *
 * Return:
 *Final channel plan decision
 *
 */
u8 hal_com_config_channel_plan(
	काष्ठा adapter *padapter,
	u8 hw_channel_plan,
	u8 sw_channel_plan,
	u8 def_channel_plan,
	bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData;
	u8 chnlPlan;

	pHalData = GET_HAL_DATA(padapter);
	pHalData->bDisableSWChannelPlan = false;
	chnlPlan = def_channel_plan;

	अगर (0xFF == hw_channel_plan)
		AutoLoadFail = true;

	अगर (!AutoLoadFail) अणु
		u8 hw_chnlPlan;

		hw_chnlPlan = hw_channel_plan & (~EEPROM_CHANNEL_PLAN_BY_HW_MASK);
		अगर (rtw_is_channel_plan_valid(hw_chnlPlan)) अणु
			अगर (hw_channel_plan & EEPROM_CHANNEL_PLAN_BY_HW_MASK)
				pHalData->bDisableSWChannelPlan = true;

			chnlPlan = hw_chnlPlan;
		पूर्ण
	पूर्ण

	अगर (
		(false == pHalData->bDisableSWChannelPlan) &&
		rtw_is_channel_plan_valid(sw_channel_plan)
	)
		chnlPlan = sw_channel_plan;

	वापस chnlPlan;
पूर्ण

bool HAL_IsLegalChannel(काष्ठा adapter *Adapter, u32 Channel)
अणु
	bool bLegalChannel = true;

	अगर ((Channel <= 14) && (Channel >= 1)) अणु
		अगर (IsSupported24G(Adapter->registrypriv.wireless_mode) == false)
			bLegalChannel = false;
	पूर्ण अन्यथा अणु
		bLegalChannel = false;
	पूर्ण

	वापस bLegalChannel;
पूर्ण

u8 MRateToHwRate(u8 rate)
अणु
	u8 ret = DESC_RATE1M;

	चयन (rate) अणु
	हाल MGN_1M:
		ret = DESC_RATE1M;
		अवरोध;
	हाल MGN_2M:
		ret = DESC_RATE2M;
		अवरोध;
	हाल MGN_5_5M:
		ret = DESC_RATE5_5M;
		अवरोध;
	हाल MGN_11M:
		ret = DESC_RATE11M;
		अवरोध;
	हाल MGN_6M:
		ret = DESC_RATE6M;
		अवरोध;
	हाल MGN_9M:
		ret = DESC_RATE9M;
		अवरोध;
	हाल MGN_12M:
		ret = DESC_RATE12M;
		अवरोध;
	हाल MGN_18M:
		ret = DESC_RATE18M;
		अवरोध;
	हाल MGN_24M:
		ret = DESC_RATE24M;
		अवरोध;
	हाल MGN_36M:
		ret = DESC_RATE36M;
		अवरोध;
	हाल MGN_48M:
		ret = DESC_RATE48M;
		अवरोध;
	हाल MGN_54M:
		ret = DESC_RATE54M;
		अवरोध;
	हाल MGN_MCS0:
		ret = DESC_RATEMCS0;
		अवरोध;
	हाल MGN_MCS1:
		ret = DESC_RATEMCS1;
		अवरोध;
	हाल MGN_MCS2:
		ret = DESC_RATEMCS2;
		अवरोध;
	हाल MGN_MCS3:
		ret = DESC_RATEMCS3;
		अवरोध;
	हाल MGN_MCS4:
		ret = DESC_RATEMCS4;
		अवरोध;
	हाल MGN_MCS5:
		ret = DESC_RATEMCS5;
		अवरोध;
	हाल MGN_MCS6:
		ret = DESC_RATEMCS6;
		अवरोध;
	हाल MGN_MCS7:
		ret = DESC_RATEMCS7;
		अवरोध;
	हाल MGN_MCS8:
		ret = DESC_RATEMCS8;
		अवरोध;
	हाल MGN_MCS9:
		ret = DESC_RATEMCS9;
		अवरोध;
	हाल MGN_MCS10:
		ret = DESC_RATEMCS10;
		अवरोध;
	हाल MGN_MCS11:
		ret = DESC_RATEMCS11;
		अवरोध;
	हाल MGN_MCS12:
		ret = DESC_RATEMCS12;
		अवरोध;
	हाल MGN_MCS13:
		ret = DESC_RATEMCS13;
		अवरोध;
	हाल MGN_MCS14:
		ret = DESC_RATEMCS14;
		अवरोध;
	हाल MGN_MCS15:
		ret = DESC_RATEMCS15;
		अवरोध;
	हाल MGN_MCS16:
		ret = DESC_RATEMCS16;
		अवरोध;
	हाल MGN_MCS17:
		ret = DESC_RATEMCS17;
		अवरोध;
	हाल MGN_MCS18:
		ret = DESC_RATEMCS18;
		अवरोध;
	हाल MGN_MCS19:
		ret = DESC_RATEMCS19;
		अवरोध;
	हाल MGN_MCS20:
		ret = DESC_RATEMCS20;
		अवरोध;
	हाल MGN_MCS21:
		ret = DESC_RATEMCS21;
		अवरोध;
	हाल MGN_MCS22:
		ret = DESC_RATEMCS22;
		अवरोध;
	हाल MGN_MCS23:
		ret = DESC_RATEMCS23;
		अवरोध;
	हाल MGN_MCS24:
		ret = DESC_RATEMCS24;
		अवरोध;
	हाल MGN_MCS25:
		ret = DESC_RATEMCS25;
		अवरोध;
	हाल MGN_MCS26:
		ret = DESC_RATEMCS26;
		अवरोध;
	हाल MGN_MCS27:
		ret = DESC_RATEMCS27;
		अवरोध;
	हाल MGN_MCS28:
		ret = DESC_RATEMCS28;
		अवरोध;
	हाल MGN_MCS29:
		ret = DESC_RATEMCS29;
		अवरोध;
	हाल MGN_MCS30:
		ret = DESC_RATEMCS30;
		अवरोध;
	हाल MGN_MCS31:
		ret = DESC_RATEMCS31;
		अवरोध;
	हाल MGN_VHT1SS_MCS0:
		ret = DESC_RATEVHTSS1MCS0;
		अवरोध;
	हाल MGN_VHT1SS_MCS1:
		ret = DESC_RATEVHTSS1MCS1;
		अवरोध;
	हाल MGN_VHT1SS_MCS2:
		ret = DESC_RATEVHTSS1MCS2;
		अवरोध;
	हाल MGN_VHT1SS_MCS3:
		ret = DESC_RATEVHTSS1MCS3;
		अवरोध;
	हाल MGN_VHT1SS_MCS4:
		ret = DESC_RATEVHTSS1MCS4;
		अवरोध;
	हाल MGN_VHT1SS_MCS5:
		ret = DESC_RATEVHTSS1MCS5;
		अवरोध;
	हाल MGN_VHT1SS_MCS6:
		ret = DESC_RATEVHTSS1MCS6;
		अवरोध;
	हाल MGN_VHT1SS_MCS7:
		ret = DESC_RATEVHTSS1MCS7;
		अवरोध;
	हाल MGN_VHT1SS_MCS8:
		ret = DESC_RATEVHTSS1MCS8;
		अवरोध;
	हाल MGN_VHT1SS_MCS9:
		ret = DESC_RATEVHTSS1MCS9;
		अवरोध;
	हाल MGN_VHT2SS_MCS0:
		ret = DESC_RATEVHTSS2MCS0;
		अवरोध;
	हाल MGN_VHT2SS_MCS1:
		ret = DESC_RATEVHTSS2MCS1;
		अवरोध;
	हाल MGN_VHT2SS_MCS2:
		ret = DESC_RATEVHTSS2MCS2;
		अवरोध;
	हाल MGN_VHT2SS_MCS3:
		ret = DESC_RATEVHTSS2MCS3;
		अवरोध;
	हाल MGN_VHT2SS_MCS4:
		ret = DESC_RATEVHTSS2MCS4;
		अवरोध;
	हाल MGN_VHT2SS_MCS5:
		ret = DESC_RATEVHTSS2MCS5;
		अवरोध;
	हाल MGN_VHT2SS_MCS6:
		ret = DESC_RATEVHTSS2MCS6;
		अवरोध;
	हाल MGN_VHT2SS_MCS7:
		ret = DESC_RATEVHTSS2MCS7;
		अवरोध;
	हाल MGN_VHT2SS_MCS8:
		ret = DESC_RATEVHTSS2MCS8;
		अवरोध;
	हाल MGN_VHT2SS_MCS9:
		ret = DESC_RATEVHTSS2MCS9;
		अवरोध;
	हाल MGN_VHT3SS_MCS0:
		ret = DESC_RATEVHTSS3MCS0;
		अवरोध;
	हाल MGN_VHT3SS_MCS1:
		ret = DESC_RATEVHTSS3MCS1;
		अवरोध;
	हाल MGN_VHT3SS_MCS2:
		ret = DESC_RATEVHTSS3MCS2;
		अवरोध;
	हाल MGN_VHT3SS_MCS3:
		ret = DESC_RATEVHTSS3MCS3;
		अवरोध;
	हाल MGN_VHT3SS_MCS4:
		ret = DESC_RATEVHTSS3MCS4;
		अवरोध;
	हाल MGN_VHT3SS_MCS5:
		ret = DESC_RATEVHTSS3MCS5;
		अवरोध;
	हाल MGN_VHT3SS_MCS6:
		ret = DESC_RATEVHTSS3MCS6;
		अवरोध;
	हाल MGN_VHT3SS_MCS7:
		ret = DESC_RATEVHTSS3MCS7;
		अवरोध;
	हाल MGN_VHT3SS_MCS8:
		ret = DESC_RATEVHTSS3MCS8;
		अवरोध;
	हाल MGN_VHT3SS_MCS9:
		ret = DESC_RATEVHTSS3MCS9;
		अवरोध;
	हाल MGN_VHT4SS_MCS0:
		ret = DESC_RATEVHTSS4MCS0;
		अवरोध;
	हाल MGN_VHT4SS_MCS1:
		ret = DESC_RATEVHTSS4MCS1;
		अवरोध;
	हाल MGN_VHT4SS_MCS2:
		ret = DESC_RATEVHTSS4MCS2;
		अवरोध;
	हाल MGN_VHT4SS_MCS3:
		ret = DESC_RATEVHTSS4MCS3;
		अवरोध;
	हाल MGN_VHT4SS_MCS4:
		ret = DESC_RATEVHTSS4MCS4;
		अवरोध;
	हाल MGN_VHT4SS_MCS5:
		ret = DESC_RATEVHTSS4MCS5;
		अवरोध;
	हाल MGN_VHT4SS_MCS6:
		ret = DESC_RATEVHTSS4MCS6;
		अवरोध;
	हाल MGN_VHT4SS_MCS7:
		ret = DESC_RATEVHTSS4MCS7;
		अवरोध;
	हाल MGN_VHT4SS_MCS8:
		ret = DESC_RATEVHTSS4MCS8;
		अवरोध;
	हाल MGN_VHT4SS_MCS9:
		ret = DESC_RATEVHTSS4MCS9;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

u8 HwRateToMRate(u8 rate)
अणु
	u8 ret_rate = MGN_1M;

	चयन (rate) अणु
	हाल DESC_RATE1M:
		ret_rate = MGN_1M;
		अवरोध;
	हाल DESC_RATE2M:
		ret_rate = MGN_2M;
		अवरोध;
	हाल DESC_RATE5_5M:
		ret_rate = MGN_5_5M;
		अवरोध;
	हाल DESC_RATE11M:
		ret_rate = MGN_11M;
		अवरोध;
	हाल DESC_RATE6M:
		ret_rate = MGN_6M;
		अवरोध;
	हाल DESC_RATE9M:
		ret_rate = MGN_9M;
		अवरोध;
	हाल DESC_RATE12M:
		ret_rate = MGN_12M;
		अवरोध;
	हाल DESC_RATE18M:
		ret_rate = MGN_18M;
		अवरोध;
	हाल DESC_RATE24M:
		ret_rate = MGN_24M;
		अवरोध;
	हाल DESC_RATE36M:
		ret_rate = MGN_36M;
		अवरोध;
	हाल DESC_RATE48M:
		ret_rate = MGN_48M;
		अवरोध;
	हाल DESC_RATE54M:
		ret_rate = MGN_54M;
		अवरोध;
	हाल DESC_RATEMCS0:
		ret_rate = MGN_MCS0;
		अवरोध;
	हाल DESC_RATEMCS1:
		ret_rate = MGN_MCS1;
		अवरोध;
	हाल DESC_RATEMCS2:
		ret_rate = MGN_MCS2;
		अवरोध;
	हाल DESC_RATEMCS3:
		ret_rate = MGN_MCS3;
		अवरोध;
	हाल DESC_RATEMCS4:
		ret_rate = MGN_MCS4;
		अवरोध;
	हाल DESC_RATEMCS5:
		ret_rate = MGN_MCS5;
		अवरोध;
	हाल DESC_RATEMCS6:
		ret_rate = MGN_MCS6;
		अवरोध;
	हाल DESC_RATEMCS7:
		ret_rate = MGN_MCS7;
		अवरोध;
	हाल DESC_RATEMCS8:
		ret_rate = MGN_MCS8;
		अवरोध;
	हाल DESC_RATEMCS9:
		ret_rate = MGN_MCS9;
		अवरोध;
	हाल DESC_RATEMCS10:
		ret_rate = MGN_MCS10;
		अवरोध;
	हाल DESC_RATEMCS11:
		ret_rate = MGN_MCS11;
		अवरोध;
	हाल DESC_RATEMCS12:
		ret_rate = MGN_MCS12;
		अवरोध;
	हाल DESC_RATEMCS13:
		ret_rate = MGN_MCS13;
		अवरोध;
	हाल DESC_RATEMCS14:
		ret_rate = MGN_MCS14;
		अवरोध;
	हाल DESC_RATEMCS15:
		ret_rate = MGN_MCS15;
		अवरोध;
	हाल DESC_RATEMCS16:
		ret_rate = MGN_MCS16;
		अवरोध;
	हाल DESC_RATEMCS17:
		ret_rate = MGN_MCS17;
		अवरोध;
	हाल DESC_RATEMCS18:
		ret_rate = MGN_MCS18;
		अवरोध;
	हाल DESC_RATEMCS19:
		ret_rate = MGN_MCS19;
		अवरोध;
	हाल DESC_RATEMCS20:
		ret_rate = MGN_MCS20;
		अवरोध;
	हाल DESC_RATEMCS21:
		ret_rate = MGN_MCS21;
		अवरोध;
	हाल DESC_RATEMCS22:
		ret_rate = MGN_MCS22;
		अवरोध;
	हाल DESC_RATEMCS23:
		ret_rate = MGN_MCS23;
		अवरोध;
	हाल DESC_RATEMCS24:
		ret_rate = MGN_MCS24;
		अवरोध;
	हाल DESC_RATEMCS25:
		ret_rate = MGN_MCS25;
		अवरोध;
	हाल DESC_RATEMCS26:
		ret_rate = MGN_MCS26;
		अवरोध;
	हाल DESC_RATEMCS27:
		ret_rate = MGN_MCS27;
		अवरोध;
	हाल DESC_RATEMCS28:
		ret_rate = MGN_MCS28;
		अवरोध;
	हाल DESC_RATEMCS29:
		ret_rate = MGN_MCS29;
		अवरोध;
	हाल DESC_RATEMCS30:
		ret_rate = MGN_MCS30;
		अवरोध;
	हाल DESC_RATEMCS31:
		ret_rate = MGN_MCS31;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS0:
		ret_rate = MGN_VHT1SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS1:
		ret_rate = MGN_VHT1SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS2:
		ret_rate = MGN_VHT1SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS3:
		ret_rate = MGN_VHT1SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS4:
		ret_rate = MGN_VHT1SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS5:
		ret_rate = MGN_VHT1SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS6:
		ret_rate = MGN_VHT1SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS7:
		ret_rate = MGN_VHT1SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS8:
		ret_rate = MGN_VHT1SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHTSS1MCS9:
		ret_rate = MGN_VHT1SS_MCS9;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS0:
		ret_rate = MGN_VHT2SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS1:
		ret_rate = MGN_VHT2SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS2:
		ret_rate = MGN_VHT2SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS3:
		ret_rate = MGN_VHT2SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS4:
		ret_rate = MGN_VHT2SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS5:
		ret_rate = MGN_VHT2SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS6:
		ret_rate = MGN_VHT2SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS7:
		ret_rate = MGN_VHT2SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS8:
		ret_rate = MGN_VHT2SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHTSS2MCS9:
		ret_rate = MGN_VHT2SS_MCS9;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS0:
		ret_rate = MGN_VHT3SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS1:
		ret_rate = MGN_VHT3SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS2:
		ret_rate = MGN_VHT3SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS3:
		ret_rate = MGN_VHT3SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS4:
		ret_rate = MGN_VHT3SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS5:
		ret_rate = MGN_VHT3SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS6:
		ret_rate = MGN_VHT3SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS7:
		ret_rate = MGN_VHT3SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS8:
		ret_rate = MGN_VHT3SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHTSS3MCS9:
		ret_rate = MGN_VHT3SS_MCS9;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS0:
		ret_rate = MGN_VHT4SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS1:
		ret_rate = MGN_VHT4SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS2:
		ret_rate = MGN_VHT4SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS3:
		ret_rate = MGN_VHT4SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS4:
		ret_rate = MGN_VHT4SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS5:
		ret_rate = MGN_VHT4SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS6:
		ret_rate = MGN_VHT4SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS7:
		ret_rate = MGN_VHT4SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS8:
		ret_rate = MGN_VHT4SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHTSS4MCS9:
		ret_rate = MGN_VHT4SS_MCS9;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret_rate;
पूर्ण

व्योम HalSetBrateCfg(काष्ठा adapter *Adapter, u8 *mBratesOS, u16 *pBrateCfg)
अणु
	u8 i, is_brate, brate;

	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु

		is_brate = mBratesOS[i] & IEEE80211_BASIC_RATE_MASK;
		brate = mBratesOS[i] & 0x7f;

		अगर (is_brate) अणु
			चयन (brate) अणु
			हाल IEEE80211_CCK_RATE_1MB:
				*pBrateCfg |= RATE_1M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_2MB:
				*pBrateCfg |= RATE_2M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_5MB:
				*pBrateCfg |= RATE_5_5M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_11MB:
				*pBrateCfg |= RATE_11M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_6MB:
				*pBrateCfg |= RATE_6M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_9MB:
				*pBrateCfg |= RATE_9M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_12MB:
				*pBrateCfg |= RATE_12M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_18MB:
				*pBrateCfg |= RATE_18M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_24MB:
				*pBrateCfg |= RATE_24M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_36MB:
				*pBrateCfg |= RATE_36M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_48MB:
				*pBrateCfg |= RATE_48M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_54MB:
				*pBrateCfg |= RATE_54M;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _OneOutPipeMapping(काष्ठा adapter *padapter)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);

	pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
	pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
	pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[0];/* BE */
	pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[0];/* BK */

	pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
	pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
	pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
	pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
पूर्ण

अटल व्योम _TwoOutPipeMapping(काष्ठा adapter *padapter, bool bWIFICfg)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);

	अगर (bWIFICfg) अणु /* WMM */

		/* 	BK,	BE,	VI,	VO,	BCN,	CMD, MGT, HIGH, HCCA */
		/*   0,		1,	0,	1,	0,	0,	0,	0,		0	पूर्ण; */
		/* 0:ep_0 num, 1:ep_1 num */

		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[1];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[1];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[0];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */

	पूर्ण अन्यथा अणु /* typical setting */


		/* BK,	BE,	VI,	VO,	BCN,	CMD, MGT, HIGH, HCCA */
		/*   1,		1,	0,	0,	0,	0,	0,	0,		0	पूर्ण; */
		/* 0:ep_0 num, 1:ep_1 num */

		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[1];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[1];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */

	पूर्ण

पूर्ण

अटल व्योम _ThreeOutPipeMapping(काष्ठा adapter *padapter, bool bWIFICfg)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);

	अगर (bWIFICfg) अणु /* क्रम WMM */

		/* 	BK,	BE,	VI,	VO,	BCN,	CMD, MGT, HIGH, HCCA */
		/*   1,		2,	1,	0,	0,	0,	0,	0,		0	पूर्ण; */
		/* 0:H, 1:N, 2:L */

		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[1];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[2];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[1];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */

	पूर्ण अन्यथा अणु /* typical setting */


		/* 	BK,	BE,	VI,	VO,	BCN,	CMD, MGT, HIGH, HCCA */
		/*   2,		2,	1,	0,	0,	0,	0,	0,		0	पूर्ण; */
		/* 0:H, 1:N, 2:L */

		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[1];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[2];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[2];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
	पूर्ण

पूर्ण

bool Hal_MappingOutPipe(काष्ठा adapter *padapter, u8 NumOutPipe)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;

	bool bWIFICfg = (pregistrypriv->wअगरi_spec) ? true : false;

	bool result = true;

	चयन (NumOutPipe) अणु
	हाल 2:
		_TwoOutPipeMapping(padapter, bWIFICfg);
		अवरोध;
	हाल 3:
	हाल 4:
		_ThreeOutPipeMapping(padapter, bWIFICfg);
		अवरोध;
	हाल 1:
		_OneOutPipeMapping(padapter);
		अवरोध;
	शेष:
		result = false;
		अवरोध;
	पूर्ण

	वापस result;

पूर्ण

व्योम hal_init_macaddr(काष्ठा adapter *adapter)
अणु
	rtw_hal_set_hwreg(adapter, HW_VAR_MAC_ADDR, adapter->eeprompriv.mac_addr);
पूर्ण

व्योम rtw_init_hal_com_शेष_value(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	pHalData->AntDetection = 1;
पूर्ण

/*
* C2H event क्रमmat:
* Field	 TRIGGER		CONTENT	   CMD_SEQ	CMD_LEN		 CMD_ID
* BITS	 [127:120]	[119:16]      [15:8]		  [7:4]		   [3:0]
*/

व्योम c2h_evt_clear(काष्ठा adapter *adapter)
अणु
	rtw_ग_लिखो8(adapter, REG_C2HEVT_CLEAR, C2H_EVT_HOST_CLOSE);
पूर्ण

/*
* C2H event क्रमmat:
* Field    TRIGGER    CMD_LEN    CONTENT    CMD_SEQ    CMD_ID
* BITS    [127:120]   [119:112]    [111:16]	     [15:8]         [7:0]
*/
s32 c2h_evt_पढ़ो_88xx(काष्ठा adapter *adapter, u8 *buf)
अणु
	s32 ret = _FAIL;
	काष्ठा c2h_evt_hdr_88xx *c2h_evt;
	पूर्णांक i;
	u8 trigger;

	अगर (!buf)
		जाओ निकास;

	trigger = rtw_पढ़ो8(adapter, REG_C2HEVT_CLEAR);

	अगर (trigger == C2H_EVT_HOST_CLOSE)
		जाओ निकास; /* Not पढ़ोy */
	अन्यथा अगर (trigger != C2H_EVT_FW_CLOSE)
		जाओ clear_evt; /* Not a valid value */

	c2h_evt = (काष्ठा c2h_evt_hdr_88xx *)buf;

	स_रखो(c2h_evt, 0, 16);

	c2h_evt->id = rtw_पढ़ो8(adapter, REG_C2HEVT_MSG_NORMAL);
	c2h_evt->seq = rtw_पढ़ो8(adapter, REG_C2HEVT_CMD_SEQ_88XX);
	c2h_evt->plen = rtw_पढ़ो8(adapter, REG_C2HEVT_CMD_LEN_88XX);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": c2h_evt_read(): ", DUMP_PREFIX_NONE,
			     16, 1, &c2h_evt, माप(c2h_evt), false);

	/* Read the content */
	क्रम (i = 0; i < c2h_evt->plen; i++)
		c2h_evt->payload[i] = rtw_पढ़ो8(adapter, REG_C2HEVT_MSG_NORMAL + 2 + i);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": c2h_evt_read(): Command Content:\n",
			     DUMP_PREFIX_NONE, 16, 1, c2h_evt->payload, c2h_evt->plen, false);

	ret = _SUCCESS;

clear_evt:
	/*
	* Clear event to notअगरy FW we have पढ़ो the command.
	* If this field isn't clear, the FW won't update the next command message.
	*/
	c2h_evt_clear(adapter);
निकास:
	वापस ret;
पूर्ण

u8 rtw_get_mgntframe_raid(काष्ठा adapter *adapter, अचिन्हित अक्षर network_type)
अणु
	वापस (network_type & WIRELESS_11B) ? RATEID_IDX_B : RATEID_IDX_G;
पूर्ण

व्योम rtw_hal_update_sta_rate_mask(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 i, rf_type, limit;
	u32 tx_ra_biपंचांगap;

	अगर (!psta)
		वापस;

	tx_ra_biपंचांगap = 0;

	/* b/g mode ra_biपंचांगap */
	क्रम (i = 0; i < माप(psta->bssrateset); i++) अणु
		अगर (psta->bssrateset[i])
			tx_ra_biपंचांगap |= rtw_get_bit_value_from_ieee_value(psta->bssrateset[i]&0x7f);
	पूर्ण

	/* n mode ra_biपंचांगap */
	अगर (psta->htpriv.ht_option) अणु
		rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
		अगर (rf_type == RF_2T2R)
			limit = 16; /*  2R */
		अन्यथा
			limit = 8; /*   1R */

		क्रम (i = 0; i < limit; i++) अणु
			अगर (psta->htpriv.ht_cap.mcs.rx_mask[i/8] & BIT(i%8))
				tx_ra_biपंचांगap |= BIT(i+12);
		पूर्ण
	पूर्ण

	psta->ra_mask = tx_ra_biपंचांगap;
	psta->init_rate = get_highest_rate_idx(tx_ra_biपंचांगap)&0x3f;
पूर्ण

व्योम hw_var_port_चयन(काष्ठा adapter *adapter)
अणु
पूर्ण

व्योम SetHwReg(काष्ठा adapter *adapter, u8 variable, u8 *val)
अणु
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &(hal_data->odmpriv);

	चयन (variable) अणु
	हाल HW_VAR_PORT_SWITCH:
		hw_var_port_चयन(adapter);
		अवरोध;
	हाल HW_VAR_INIT_RTS_RATE:
		rtw_warn_on(1);
		अवरोध;
	हाल HW_VAR_SEC_CFG:
	अणु
		u16 reg_scr;

		reg_scr = rtw_पढ़ो16(adapter, REG_SECCFG);
		rtw_ग_लिखो16(adapter, REG_SECCFG, reg_scr|SCR_CHK_KEYID|SCR_RxDecEnable|SCR_TxEncEnable);
	पूर्ण
		अवरोध;
	हाल HW_VAR_SEC_DK_CFG:
	अणु
		काष्ठा security_priv *sec = &adapter->securitypriv;
		u8 reg_scr = rtw_पढ़ो8(adapter, REG_SECCFG);

		अगर (val) अणु /* Enable शेष key related setting */
			reg_scr |= SCR_TXBCUSEDK;
			अगर (sec->करोt11AuthAlgrthm != करोt11AuthAlgrthm_8021X)
				reg_scr |= (SCR_RxUseDK|SCR_TxUseDK);
		पूर्ण अन्यथा /* Disable शेष key related setting */
			reg_scr &= ~(SCR_RXBCUSEDK|SCR_TXBCUSEDK|SCR_RxUseDK|SCR_TxUseDK);

		rtw_ग_लिखो8(adapter, REG_SECCFG, reg_scr);
	पूर्ण
		अवरोध;
	हाल HW_VAR_DM_FLAG:
		odm->SupportAbility = *((u32 *)val);
		अवरोध;
	हाल HW_VAR_DM_FUNC_OP:
		अगर (*((u8 *)val) == true) अणु
			/* save dm flag */
			odm->BK_SupportAbility = odm->SupportAbility;
		पूर्ण अन्यथा अणु
			/* restore dm flag */
			odm->SupportAbility = odm->BK_SupportAbility;
		पूर्ण
		अवरोध;
	हाल HW_VAR_DM_FUNC_SET:
		अगर (*((u32 *)val) == DYNAMIC_ALL_FUNC_ENABLE) अणु
			काष्ठा dm_priv *dm = &hal_data->dmpriv;
			dm->DMFlag = dm->InitDMFlag;
			odm->SupportAbility = dm->InitODMFlag;
		पूर्ण अन्यथा अणु
			odm->SupportAbility |= *((u32 *)val);
		पूर्ण
		अवरोध;
	हाल HW_VAR_DM_FUNC_CLR:
		/*
		* input is alपढ़ोy a mask to clear function
		* करोn't invert it again! George, Lucas@20130513
		*/
		odm->SupportAbility &= *((u32 *)val);
		अवरोध;
	हाल HW_VAR_AMPDU_MIN_SPACE:
		/* TODO - Is something needed here? */
		अवरोध;
	हाल HW_VAR_WIRELESS_MODE:
		/* TODO - Is something needed here? */
		अवरोध;
	शेष:
		netdev_dbg(adapter->pnetdev,
			   FUNC_ADPT_FMT " variable(%d) not defined!\n",
			   FUNC_ADPT_ARG(adapter), variable);
		अवरोध;
	पूर्ण
पूर्ण

व्योम GetHwReg(काष्ठा adapter *adapter, u8 variable, u8 *val)
अणु
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &(hal_data->odmpriv);

	चयन (variable) अणु
	हाल HW_VAR_BASIC_RATE:
		*((u16 *)val) = hal_data->BasicRateSet;
		अवरोध;
	हाल HW_VAR_DM_FLAG:
		*((u32 *)val) = odm->SupportAbility;
		अवरोध;
	हाल HW_VAR_RF_TYPE:
		*((u8 *)val) = hal_data->rf_type;
		अवरोध;
	शेष:
		netdev_dbg(adapter->pnetdev,
			   FUNC_ADPT_FMT " variable(%d) not defined!\n",
			   FUNC_ADPT_ARG(adapter), variable);
		अवरोध;
	पूर्ण
पूर्ण




u8 SetHalDefVar(
	काष्ठा adapter *adapter, क्रमागत hal_def_variable variable, व्योम *value
)
अणु
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &(hal_data->odmpriv);
	u8 bResult = _SUCCESS;

	चयन (variable) अणु
	हाल HW_DEF_FA_CNT_DUMP:
		/* ODM_COMP_COMMON */
		अगर (*((u8 *)value))
			odm->DebugComponents |= (ODM_COMP_DIG | ODM_COMP_FA_CNT);
		अन्यथा
			odm->DebugComponents &= ~(ODM_COMP_DIG | ODM_COMP_FA_CNT);
		अवरोध;
	हाल HAL_DEF_DBG_RX_INFO_DUMP:

		अगर (odm->bLinked) अणु
			#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
			rtw_dump_raw_rssi_info(adapter);
			#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल HW_DEF_ODM_DBG_FLAG:
		ODM_CmnInfoUpdate(odm, ODM_CMNINFO_DBG_COMP, *((u64 *)value));
		अवरोध;
	हाल HW_DEF_ODM_DBG_LEVEL:
		ODM_CmnInfoUpdate(odm, ODM_CMNINFO_DBG_LEVEL, *((u32 *)value));
		अवरोध;
	हाल HAL_DEF_DBG_DM_FUNC:
	अणु
		u8 dm_func = *((u8 *)value);
		काष्ठा dm_priv *dm = &hal_data->dmpriv;

		अगर (dm_func == 0) अणु /* disable all dynamic func */
			odm->SupportAbility = DYNAMIC_FUNC_DISABLE;
		पूर्ण अन्यथा अगर (dm_func == 1) अणु/* disable DIG */
			odm->SupportAbility  &= (~DYNAMIC_BB_DIG);
		पूर्ण अन्यथा अगर (dm_func == 2) अणु/* disable High घातer */
			odm->SupportAbility  &= (~DYNAMIC_BB_DYNAMIC_TXPWR);
		पूर्ण अन्यथा अगर (dm_func == 3) अणु/* disable tx घातer tracking */
			odm->SupportAbility  &= (~DYNAMIC_RF_CALIBRATION);
		पूर्ण अन्यथा अगर (dm_func == 4) अणु/* disable BT coexistence */
			dm->DMFlag &= (~DYNAMIC_FUNC_BT);
		पूर्ण अन्यथा अगर (dm_func == 5) अणु/* disable antenna भागersity */
			odm->SupportAbility  &= (~DYNAMIC_BB_ANT_DIV);
		पूर्ण अन्यथा अगर (dm_func == 6) अणु/* turn on all dynamic func */
			अगर (!(odm->SupportAbility  & DYNAMIC_BB_DIG)) अणु
				काष्ठा dig_t	*pDigTable = &odm->DM_DigTable;
				pDigTable->CurIGValue = rtw_पढ़ो8(adapter, 0xc50);
			पूर्ण
			dm->DMFlag |= DYNAMIC_FUNC_BT;
			odm->SupportAbility = DYNAMIC_ALL_FUNC_ENABLE;
		पूर्ण
	पूर्ण
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_RXPKT:
		hal_data->bDumpRxPkt = *((u8 *)value);
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_TXPKT:
		hal_data->bDumpTxPkt = *((u8 *)value);
		अवरोध;
	हाल HAL_DEF_ANT_DETECT:
		hal_data->AntDetection = *((u8 *)value);
		अवरोध;
	शेष:
		netdev_dbg(adapter->pnetdev,
			   "%s: [WARNING] HAL_DEF_VARIABLE(%d) not defined!\n",
			   __func__, variable);
		bResult = _FAIL;
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

u8 GetHalDefVar(
	काष्ठा adapter *adapter, क्रमागत hal_def_variable variable, व्योम *value
)
अणु
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &(hal_data->odmpriv);
	u8 bResult = _SUCCESS;

	चयन (variable) अणु
	हाल HAL_DEF_UNDERCORATEDSMOOTHEDPWDB:
		अणु
			काष्ठा mlme_priv *pmlmepriv;
			काष्ठा sta_priv *pstapriv;
			काष्ठा sta_info *psta;

			pmlmepriv = &adapter->mlmepriv;
			pstapriv = &adapter->stapriv;
			psta = rtw_get_stainfo(pstapriv, pmlmepriv->cur_network.network.MacAddress);
			अगर (psta)
				*((पूर्णांक *)value) = psta->rssi_stat.UndecoratedSmoothedPWDB;
		पूर्ण
		अवरोध;
	हाल HW_DEF_ODM_DBG_FLAG:
		*((u64 *)value) = odm->DebugComponents;
		अवरोध;
	हाल HW_DEF_ODM_DBG_LEVEL:
		*((u32 *)value) = odm->DebugLevel;
		अवरोध;
	हाल HAL_DEF_DBG_DM_FUNC:
		*((u32 *)value) = hal_data->odmpriv.SupportAbility;
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_RXPKT:
		*((u8 *)value) = hal_data->bDumpRxPkt;
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_TXPKT:
		*((u8 *)value) = hal_data->bDumpTxPkt;
		अवरोध;
	हाल HAL_DEF_ANT_DETECT:
		*((u8 *)value) = hal_data->AntDetection;
		अवरोध;
	हाल HAL_DEF_MACID_SLEEP:
		*(u8 *)value = false;
		अवरोध;
	हाल HAL_DEF_TX_PAGE_SIZE:
		*((u32 *)value) = PAGE_SIZE_128;
		अवरोध;
	शेष:
		netdev_dbg(adapter->pnetdev,
			   "%s: [WARNING] HAL_DEF_VARIABLE(%d) not defined!\n",
			   __func__, variable);
		bResult = _FAIL;
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

व्योम GetHalODMVar(
	काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable eVariable,
	व्योम *pValue1,
	व्योम *pValue2
)
अणु
	चयन (eVariable) अणु
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम SetHalODMVar(
	काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable eVariable,
	व्योम *pValue1,
	bool bSet
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_odm_t *podmpriv = &pHalData->odmpriv;
	/* _irqL irqL; */
	चयन (eVariable) अणु
	हाल HAL_ODM_STA_INFO:
		अणु
			काष्ठा sta_info *psta = pValue1;
			अगर (bSet) अणु
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, psta);
			पूर्ण अन्यथा अणु
				/* spin_lock_bh(&pHalData->odm_stainfo_lock); */
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, शून्य);

				/* spin_unlock_bh(&pHalData->odm_stainfo_lock); */
		    पूर्ण
		पूर्ण
		अवरोध;
	हाल HAL_ODM_P2P_STATE:
			ODM_CmnInfoUpdate(podmpriv, ODM_CMNINFO_WIFI_सूचीECT, bSet);
		अवरोध;
	हाल HAL_ODM_WIFI_DISPLAY_STATE:
			ODM_CmnInfoUpdate(podmpriv, ODM_CMNINFO_WIFI_DISPLAY, bSet);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण


bool eqNByte(u8 *str1, u8 *str2, u32 num)
अणु
	अगर (num == 0)
		वापस false;
	जबतक (num > 0) अणु
		num--;
		अगर (str1[num] != str2[num])
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*  */
/* 	Description: */
/* 		Return true अगर chTmp is represent क्रम hex digit and */
/* 		false otherwise. */
/*  */
/*  */
bool IsHexDigit(अक्षर chTmp)
अणु
	अगर (
		(chTmp >= '0' && chTmp <= '9') ||
		(chTmp >= 'a' && chTmp <= 'f') ||
		(chTmp >= 'A' && chTmp <= 'F')
	)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण


/*  */
/* 	Description: */
/* 		Translate a अक्षरacter to hex digit. */
/*  */
u32 MapCharToHexDigit(अक्षर chTmp)
अणु
	अगर (chTmp >= '0' && chTmp <= '9')
		वापस chTmp - '0';
	अन्यथा अगर (chTmp >= 'a' && chTmp <= 'f')
		वापस 10 + (chTmp - 'a');
	अन्यथा अगर (chTmp >= 'A' && chTmp <= 'F')
		वापस 10 + (chTmp - 'A');
	अन्यथा
		वापस 0;
पूर्ण



/* 	Description: */
/* 		Parse hex number from the string pucStr. */
bool GetHexValueFromString(अक्षर *szStr, u32 *pu4bVal, u32 *pu4bMove)
अणु
	अक्षर *szScan = szStr;

	/*  Check input parameter. */
	अगर (!szStr || !pu4bVal || !pu4bMove)
		वापस false;

	/*  Initialize output. */
	*pu4bMove = 0;
	*pu4bVal = 0;

	/*  Skip leading space. */
	जबतक (*szScan != '\0' && (*szScan == ' ' || *szScan == '\t')) अणु
		szScan++;
		(*pu4bMove)++;
	पूर्ण

	/*  Skip leading '0x' or '0X'. */
	अगर (*szScan == '0' && (*(szScan+1) == 'x' || *(szScan+1) == 'X')) अणु
		szScan += 2;
		(*pu4bMove) += 2;
	पूर्ण

	/*  Check अगर szScan is now poपूर्णांकer to a अक्षरacter क्रम hex digit, */
	/*  अगर not, it means this is not a valid hex number. */
	अगर (!IsHexDigit(*szScan))
		वापस false;

	/*  Parse each digit. */
	करो अणु
		(*pu4bVal) <<= 4;
		*pu4bVal += MapCharToHexDigit(*szScan);

		szScan++;
		(*pu4bMove)++;
	पूर्ण जबतक (IsHexDigit(*szScan));

	वापस true;
पूर्ण

bool GetFractionValueFromString(
	अक्षर *szStr, u8 *pInteger, u8 *pFraction, u32 *pu4bMove
)
अणु
	अक्षर *szScan = szStr;

	/*  Initialize output. */
	*pu4bMove = 0;
	*pInteger = 0;
	*pFraction = 0;

	/*  Skip leading space. */
	जबतक (*szScan != '\0' &&	(*szScan == ' ' || *szScan == '\t')) अणु
		++szScan;
		++(*pu4bMove);
	पूर्ण

	/*  Parse each digit. */
	करो अणु
		(*pInteger) *= 10;
		*pInteger += (*szScan - '0');

		++szScan;
		++(*pu4bMove);

		अगर (*szScan == '.') अणु
			++szScan;
			++(*pu4bMove);

			अगर (*szScan < '0' || *szScan > '9')
				वापस false;
			अन्यथा अणु
				*pFraction = *szScan - '0';
				++szScan;
				++(*pu4bMove);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (*szScan >= '0' && *szScan <= '9');

	वापस true;
पूर्ण

/*  */
/* 	Description: */
/* 		Return true अगर szStr is comment out with leading "//". */
/*  */
bool IsCommentString(अक्षर *szStr)
अणु
	अगर (*szStr == '/' && *(szStr+1) == '/')
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

bool GetU1ByteIntegerFromStringInDecimal(अक्षर *Str, u8 *pInt)
अणु
	u16 i = 0;
	*pInt = 0;

	जबतक (Str[i] != '\0') अणु
		अगर (Str[i] >= '0' && Str[i] <= '9') अणु
			*pInt *= 10;
			*pInt += (Str[i] - '0');
		पूर्ण अन्यथा
			वापस false;

		++i;
	पूर्ण

	वापस true;
पूर्ण

/*  <20121004, Kordan> For example,
 *  ParseQualअगरiedString(inString, 0, outString, '[', ']') माला_लो "Kordan" from
 *  a string "Hello [Kordan]".
 *  If RightQualअगरier करोes not exist, it will hang in the जबतक loop
 */
bool ParseQualअगरiedString(
	अक्षर *In, u32 *Start, अक्षर *Out, अक्षर LeftQualअगरier, अक्षर RightQualअगरier
)
अणु
	u32 i = 0, j = 0;
	अक्षर c = In[(*Start)++];

	अगर (c != LeftQualअगरier)
		वापस false;

	i = (*Start);
	जबतक ((c = In[(*Start)++]) != RightQualअगरier)
		; /*  find ']' */
	j = (*Start) - 2;
	म_नकलन((अक्षर *)Out, (स्थिर अक्षर *)(In+i), j-i+1);

	वापस true;
पूर्ण

bool isAllSpaceOrTab(u8 *data, u8 size)
अणु
	u8 cnt = 0, NumOfSpaceAndTab = 0;

	जबतक (size > cnt) अणु
		अगर (data[cnt] == ' ' || data[cnt] == '\t' || data[cnt] == '\0')
			++NumOfSpaceAndTab;

		++cnt;
	पूर्ण

	वापस size == NumOfSpaceAndTab;
पूर्ण


व्योम rtw_hal_check_rxfअगरo_full(काष्ठा adapter *adapter)
अणु
	काष्ठा dvobj_priv *psdpriv = adapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	पूर्णांक save_cnt = false;

	/* चयन counter to RX fअगरo */
	/* prपूर्णांकk("8723b or 8192e , MAC_667 set 0xf0\n"); */
	rtw_ग_लिखो8(adapter, REG_RXERR_RPT+3, rtw_पढ़ो8(adapter, REG_RXERR_RPT+3)|0xf0);
	save_cnt = true;
	/* toकरो: other chips */

	अगर (save_cnt) अणु
		/* rtw_ग_लिखो8(adapter, REG_RXERR_RPT+3, rtw_पढ़ो8(adapter, REG_RXERR_RPT+3)|0xa0); */
		pdbgpriv->dbg_rx_fअगरo_last_overflow = pdbgpriv->dbg_rx_fअगरo_curr_overflow;
		pdbgpriv->dbg_rx_fअगरo_curr_overflow = rtw_पढ़ो16(adapter, REG_RXERR_RPT);
		pdbgpriv->dbg_rx_fअगरo_dअगरf_overflow = pdbgpriv->dbg_rx_fअगरo_curr_overflow-pdbgpriv->dbg_rx_fअगरo_last_overflow;
	पूर्ण
पूर्ण

व्योम linked_info_dump(काष्ठा adapter *padapter, u8 benable)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	अगर (padapter->bLinkInfoDump == benable)
		वापस;

	अगर (benable) अणु
		pwrctrlpriv->org_घातer_mgnt = pwrctrlpriv->घातer_mgnt;/* keep org value */
		rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

		pwrctrlpriv->ips_org_mode = pwrctrlpriv->ips_mode;/* keep org value */
		rtw_pm_set_ips(padapter, IPS_NONE);
	पूर्ण अन्यथा अणु
		rtw_pm_set_ips(padapter, pwrctrlpriv->ips_org_mode);

		rtw_pm_set_lps(padapter, pwrctrlpriv->ips_org_mode);
	पूर्ण
	padapter->bLinkInfoDump = benable;
पूर्ण

#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
व्योम rtw_get_raw_rssi_info(व्योम *sel, काष्ठा adapter *padapter)
अणु
	u8 isCCKrate, rf_path;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा rx_raw_rssi *psample_pkt_rssi = &padapter->recvpriv.raw_rssi_info;

	netdev_dbg(padapter->pnetdev,
		   "RxRate = %s, PWDBALL = %d(%%), rx_pwr_all = %d(dBm)\n",
		   HDATA_RATE(psample_pkt_rssi->data_rate),
		   psample_pkt_rssi->pwdball, psample_pkt_rssi->pwr_all);

	isCCKrate = psample_pkt_rssi->data_rate <= DESC_RATE11M;

	अगर (isCCKrate)
		psample_pkt_rssi->mimo_संकेत_strength[0] = psample_pkt_rssi->pwdball;

	क्रम (rf_path = 0; rf_path < pHalData->NumTotalRFPath; rf_path++) अणु
		netdev_dbg(padapter->pnetdev,
			   "RF_PATH_%d =>signal_strength:%d(%%), signal_quality:%d(%%)\n",
			   rf_path,
			   psample_pkt_rssi->mimo_संकेत_strength[rf_path],
			   psample_pkt_rssi->mimo_संकेत_quality[rf_path]);

		अगर (!isCCKrate) अणु
			netdev_dbg(padapter->pnetdev,
				   "\trx_ofdm_pwr:%d(dBm), rx_ofdm_snr:%d(dB)\n",
				   psample_pkt_rssi->ofdm_pwr[rf_path],
				   psample_pkt_rssi->ofdm_snr[rf_path]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_dump_raw_rssi_info(काष्ठा adapter *padapter)
अणु
	u8 isCCKrate, rf_path;
	काष्ठा hal_com_data *pHalData =  GET_HAL_DATA(padapter);
	काष्ठा rx_raw_rssi *psample_pkt_rssi = &padapter->recvpriv.raw_rssi_info;

	isCCKrate = psample_pkt_rssi->data_rate <= DESC_RATE11M;

	अगर (isCCKrate)
		psample_pkt_rssi->mimo_संकेत_strength[0] = psample_pkt_rssi->pwdball;

	क्रम (rf_path = 0; rf_path < pHalData->NumTotalRFPath; rf_path++) अणु
		अगर (!isCCKrate) अणु
			prपूर्णांकk(", rx_ofdm_pwr:%d(dBm), rx_ofdm_snr:%d(dB)\n",
			psample_pkt_rssi->ofdm_pwr[rf_path], psample_pkt_rssi->ofdm_snr[rf_path]);
		पूर्ण अन्यथा अणु
			prपूर्णांकk("\n");
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_store_phy_info(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	u8 isCCKrate, rf_path;
	काष्ठा hal_com_data *pHalData =  GET_HAL_DATA(padapter);
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;

	काष्ठा odm_phy_info *pPhyInfo  = (PODM_PHY_INFO_T)(&pattrib->phy_info);
	काष्ठा rx_raw_rssi *psample_pkt_rssi = &padapter->recvpriv.raw_rssi_info;

	psample_pkt_rssi->data_rate = pattrib->data_rate;
	isCCKrate = pattrib->data_rate <= DESC_RATE11M;

	psample_pkt_rssi->pwdball = pPhyInfo->rx_pwd_ba11;
	psample_pkt_rssi->pwr_all = pPhyInfo->recv_संकेत_घातer;

	क्रम (rf_path = 0; rf_path < pHalData->NumTotalRFPath; rf_path++) अणु
		psample_pkt_rssi->mimo_संकेत_strength[rf_path] = pPhyInfo->rx_mimo_संकेत_strength[rf_path];
		psample_pkt_rssi->mimo_संकेत_quality[rf_path] = pPhyInfo->rx_mimo_संकेत_quality[rf_path];
		अगर (!isCCKrate) अणु
			psample_pkt_rssi->ofdm_pwr[rf_path] = pPhyInfo->RxPwr[rf_path];
			psample_pkt_rssi->ofdm_snr[rf_path] = pPhyInfo->RxSNR[rf_path];
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल u32 Array_kमुक्तmap[] = अणु
	0xf8, 0xe,
	0xf6, 0xc,
	0xf4, 0xa,
	0xf2, 0x8,
	0xf0, 0x6,
	0xf3, 0x4,
	0xf5, 0x2,
	0xf7, 0x0,
	0xf9, 0x0,
	0xfc, 0x0,
पूर्ण;

व्योम rtw_bb_rf_gain_offset(काष्ठा adapter *padapter)
अणु
	u8 value = padapter->eeprompriv.EEPROMRFGainOffset;
	u32 res, i = 0;
	u32 *Array = Array_kमुक्तmap;
	u32 v1 = 0, v2 = 0, target = 0;

	अगर (value & BIT4) अणु
		अगर (padapter->eeprompriv.EEPROMRFGainVal != 0xff) अणु
			res = rtw_hal_पढ़ो_rfreg(padapter, RF_PATH_A, 0x7f, 0xffffffff);
			res &= 0xfff87fff;
			/* res &= 0xfff87fff; */
			क्रम (i = 0; i < ARRAY_SIZE(Array_kमुक्तmap); i += 2) अणु
				v1 = Array[i];
				v2 = Array[i+1];
				अगर (v1 == padapter->eeprompriv.EEPROMRFGainVal) अणु
					target = v2;
					अवरोध;
				पूर्ण
			पूर्ण
			PHY_SetRFReg(padapter, RF_PATH_A, REG_RF_BB_GAIN_OFFSET, BIT18|BIT17|BIT16|BIT15, target);

			/* res |= (padapter->eeprompriv.EEPROMRFGainVal & 0x0f)<< 15; */
			/* rtw_hal_ग_लिखो_rfreg(padapter, RF_PATH_A, REG_RF_BB_GAIN_OFFSET, RF_GAIN_OFFSET_MASK, res); */
			res = rtw_hal_पढ़ो_rfreg(padapter, RF_PATH_A, 0x7f, 0xffffffff);
		पूर्ण
	पूर्ण
पूर्ण
