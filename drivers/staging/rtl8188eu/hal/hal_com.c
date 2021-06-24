<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#समावेश <hal_पूर्णांकf.h>
#समावेश <hal_com.h>
#समावेश <rtl8188e_hal.h>

#घोषणा _HAL_INIT_C_

व्योम dump_chip_info(काष्ठा HAL_VERSION	chip_vers)
अणु
	uपूर्णांक cnt = 0;
	अक्षर buf[128];

	cnt += प्र_लिखो((buf + cnt), "Chip Version Info: CHIP_8188E_");
	cnt += प्र_लिखो((buf + cnt), "%s_", chip_vers.ChipType == NORMAL_CHIP ?
		       "Normal_Chip" : "Test_Chip");
	cnt += प्र_लिखो((buf + cnt), "%s_", chip_vers.VenकरोrType == CHIP_VENDOR_TSMC ?
		       "TSMC" : "UMC");
	अगर (chip_vers.CUTVersion == A_CUT_VERSION)
		cnt += प्र_लिखो((buf + cnt), "A_CUT_");
	अन्यथा अगर (chip_vers.CUTVersion == B_CUT_VERSION)
		cnt += प्र_लिखो((buf + cnt), "B_CUT_");
	अन्यथा अगर (chip_vers.CUTVersion == C_CUT_VERSION)
		cnt += प्र_लिखो((buf + cnt), "C_CUT_");
	अन्यथा अगर (chip_vers.CUTVersion == D_CUT_VERSION)
		cnt += प्र_लिखो((buf + cnt), "D_CUT_");
	अन्यथा अगर (chip_vers.CUTVersion == E_CUT_VERSION)
		cnt += प्र_लिखो((buf + cnt), "E_CUT_");
	अन्यथा
		cnt += प्र_लिखो((buf + cnt), "UNKNOWN_CUT(%d)_",
			       chip_vers.CUTVersion);
	cnt += प्र_लिखो((buf + cnt), "1T1R_");
	cnt += प्र_लिखो((buf + cnt), "RomVer(0)\n");

	pr_info("%s", buf);
पूर्ण

#घोषणा	CHAN_PLAN_HW	0x80

/* वापस the final channel plan decision */
u8 hal_com_get_channel_plan(u8 hw_channel_plan, u8 sw_channel_plan,
			    u8 def_channel_plan, bool load_fail)
अणु
	u8 sw_cfg;
	u8 chnlplan;

	sw_cfg = true;
	अगर (!load_fail) अणु
		अगर (!rtw_is_channel_plan_valid(sw_channel_plan))
			sw_cfg = false;
		अगर (hw_channel_plan & CHAN_PLAN_HW)
			sw_cfg = false;
	पूर्ण

	अगर (sw_cfg)
		chnlplan = sw_channel_plan;
	अन्यथा
		chnlplan = hw_channel_plan & (~CHAN_PLAN_HW);

	अगर (!rtw_is_channel_plan_valid(chnlplan))
		chnlplan = def_channel_plan;

	वापस chnlplan;
पूर्ण

u8 MRateToHwRate(u8 rate)
अणु
	u8 ret = DESC_RATE1M;

	चयन (rate) अणु
		/*  CCK and OFDM non-HT rates */
	हाल IEEE80211_CCK_RATE_1MB:
		ret = DESC_RATE1M;
		अवरोध;
	हाल IEEE80211_CCK_RATE_2MB:
		ret = DESC_RATE2M;
		अवरोध;
	हाल IEEE80211_CCK_RATE_5MB:
		ret = DESC_RATE5_5M;
		अवरोध;
	हाल IEEE80211_CCK_RATE_11MB:
		ret = DESC_RATE11M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_6MB:
		ret = DESC_RATE6M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_9MB:
		ret = DESC_RATE9M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_12MB:
		ret = DESC_RATE12M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_18MB:
		ret = DESC_RATE18M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_24MB:
		ret = DESC_RATE24M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_36MB:
		ret = DESC_RATE36M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_48MB:
		ret = DESC_RATE48M;
		अवरोध;
	हाल IEEE80211_OFDM_RATE_54MB:
		ret = DESC_RATE54M;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम hal_set_brate_cfg(u8 *brates, u16 *rate_cfg)
अणु
	u8 i, is_brate, brate;

	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		is_brate = brates[i] & IEEE80211_BASIC_RATE_MASK;
		brate = brates[i] & 0x7f;

		अगर (is_brate) अणु
			चयन (brate) अणु
			हाल IEEE80211_CCK_RATE_1MB:
				*rate_cfg |= RATE_1M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_2MB:
				*rate_cfg |= RATE_2M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_5MB:
				*rate_cfg |= RATE_5_5M;
				अवरोध;
			हाल IEEE80211_CCK_RATE_11MB:
				*rate_cfg |= RATE_11M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_6MB:
				*rate_cfg |= RATE_6M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_9MB:
				*rate_cfg |= RATE_9M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_12MB:
				*rate_cfg |= RATE_12M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_18MB:
				*rate_cfg |= RATE_18M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_24MB:
				*rate_cfg |= RATE_24M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_36MB:
				*rate_cfg |= RATE_36M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_48MB:
				*rate_cfg |= RATE_48M;
				अवरोध;
			हाल IEEE80211_OFDM_RATE_54MB:
				*rate_cfg |= RATE_54M;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम one_out_pipe(काष्ठा adapter *adapter)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(adapter);

	pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
	pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
	pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[0];/* BE */
	pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[0];/* BK */

	pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
	pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
	pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
	pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
पूर्ण

अटल व्योम two_out_pipe(काष्ठा adapter *adapter, bool wअगरi_cfg)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(adapter);

	अगर (wअगरi_cfg) अणु
		/*
		 * WMM
		 * BK, BE, VI, VO, BCN, CMD, MGT, HIGH, HCCA
		 *  0,  1,  0,  1,   0,   0,   0,    0,    0
		 * 0:H, 1:L
		 */
		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[1];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[1];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[0];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
	पूर्ण अन्यथा अणु
		/*
		 * typical setting
		 * BK, BE, VI, VO, BCN, CMD, MGT, HIGH, HCCA
		 *  1,  1,  0,  0,   0,   0,   0,    0,    0
		 * 0:H, 1:L
		 */
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

अटल व्योम three_out_pipe(काष्ठा adapter *adapter, bool wअगरi_cfg)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(adapter);

	अगर (wअगरi_cfg) अणु
		/*
		 * क्रम WMM
		 * BK, BE, VI, VO, BCN, CMD, MGT, HIGH, HCCA
		 *  1,  2,  1,  0,   0,   0,   0,    0,    0
		 * 0:H, 1:N, 2:L
		 */
		pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
		pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[1];/* VI */
		pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[2];/* BE */
		pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[1];/* BK */

		pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
		pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
		pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
		pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
	पूर्ण अन्यथा अणु
		/*
		 * typical setting
		 * BK, BE, VI, VO, BCN, CMD, MGT, HIGH, HCCA
		 *  2,  2,  1,  0,   0,   0,   0,    0,    0
		 * 0:H, 1:N, 2:L
		 */
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

bool hal_mapping_out_pipe(काष्ठा adapter *adapter, u8 numoutpipe)
अणु
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	bool wअगरi_cfg = (pregistrypriv->wअगरi_spec) ? true : false;
	bool result = true;

	चयन (numoutpipe) अणु
	हाल 1:
		one_out_pipe(adapter);
		अवरोध;
	हाल 2:
		two_out_pipe(adapter, wअगरi_cfg);
		अवरोध;
	हाल 3:
		three_out_pipe(adapter, wअगरi_cfg);
		अवरोध;
	शेष:
		result = false;
	पूर्ण
	वापस result;
पूर्ण
