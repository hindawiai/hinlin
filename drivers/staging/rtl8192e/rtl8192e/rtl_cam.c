<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_phy.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h" /* RTL8225 Radio frontend */
#समावेश "r8192E_cmdpkt.h"

व्योम rtl92e_cam_reset(काष्ठा net_device *dev)
अणु
	u32 ulcommand = 0;

	ulcommand |= BIT31|BIT30;
	rtl92e_ग_लिखोl(dev, RWCAM, ulcommand);
पूर्ण

व्योम rtl92e_enable_hw_security_config(काष्ठा net_device *dev)
अणु
	u8 SECR_value = 0x0;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	SECR_value = SCR_TxEncEnable | SCR_RxDecEnable;
	अगर (((ieee->pairwise_key_type == KEY_TYPE_WEP40) ||
	     (ieee->pairwise_key_type == KEY_TYPE_WEP104)) &&
	     (priv->rtllib->auth_mode != 2)) अणु
		SECR_value |= SCR_RxUseDK;
		SECR_value |= SCR_TxUseDK;
	पूर्ण अन्यथा अगर ((ieee->iw_mode == IW_MODE_ADHOC) &&
		   (ieee->pairwise_key_type & (KEY_TYPE_CCMP |
		   KEY_TYPE_TKIP))) अणु
		SECR_value |= SCR_RxUseDK;
		SECR_value |= SCR_TxUseDK;
	पूर्ण


	ieee->hwsec_active = 1;
	अगर ((ieee->pHTInfo->IOTAction&HT_IOT_ACT_PURE_N_MODE) || !hwwep) अणु
		ieee->hwsec_active = 0;
		SECR_value &= ~SCR_RxDecEnable;
	पूर्ण

	RT_TRACE(COMP_SEC, "%s:, hwsec:%d, pairwise_key:%d, SECR_value:%x\n",
		 __func__, ieee->hwsec_active, ieee->pairwise_key_type,
		 SECR_value);
	rtl92e_ग_लिखोb(dev, SECR, SECR_value);
पूर्ण

व्योम rtl92e_set_swcam(काष्ठा net_device *dev, u8 EntryNo, u8 KeyIndex,
		      u16 KeyType, स्थिर u8 *MacAddr, u8 DefaultKey,
		      u32 *KeyContent, u8 is_mesh)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	RT_TRACE(COMP_DBG,
		 "===========>%s():EntryNo is %d,KeyIndex is %d,KeyType is %d,is_mesh is %d\n",
		 __func__, EntryNo, KeyIndex, KeyType, is_mesh);

	अगर (EntryNo >= TOTAL_CAM_ENTRY)
		वापस;

	अगर (!is_mesh) अणु
		ieee->swcamtable[EntryNo].bused = true;
		ieee->swcamtable[EntryNo].key_index = KeyIndex;
		ieee->swcamtable[EntryNo].key_type = KeyType;
		स_नकल(ieee->swcamtable[EntryNo].macaddr, MacAddr, 6);
		ieee->swcamtable[EntryNo].useDK = DefaultKey;
		स_नकल(ieee->swcamtable[EntryNo].key_buf, (u8 *)KeyContent, 16);
	पूर्ण
पूर्ण

व्योम rtl92e_set_key(काष्ठा net_device *dev, u8 EntryNo, u8 KeyIndex,
		    u16 KeyType, स्थिर u8 *MacAddr, u8 DefaultKey,
		    u32 *KeyContent)
अणु
	u32 TargetCommand = 0;
	u32 TargetContent = 0;
	u16 usConfig = 0;
	u8 i;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	क्रमागत rt_rf_घातer_state rtState;

	rtState = priv->rtllib->eRFPowerState;
	अगर (priv->rtllib->PowerSaveControl.bInactivePs) अणु
		अगर (rtState == eRfOff) अणु
			अगर (priv->rtllib->RfOffReason > RF_CHANGE_BY_IPS) अणु
				netdev_warn(dev, "%s(): RF is OFF.\n",
					    __func__);
				वापस;
			पूर्ण
			mutex_lock(&priv->rtllib->ips_mutex);
			rtl92e_ips_leave(dev);
			mutex_unlock(&priv->rtllib->ips_mutex);
		पूर्ण
	पूर्ण
	priv->rtllib->is_set_key = true;
	अगर (EntryNo >= TOTAL_CAM_ENTRY) अणु
		netdev_info(dev, "%s(): Invalid CAM entry\n", __func__);
		वापस;
	पूर्ण

	RT_TRACE(COMP_SEC,
		 "====>to %s, dev:%p, EntryNo:%d, KeyIndex:%d,KeyType:%d, MacAddr %pM\n",
		 __func__, dev, EntryNo, KeyIndex, KeyType, MacAddr);

	अगर (DefaultKey)
		usConfig |= BIT15 | (KeyType<<2);
	अन्यथा
		usConfig |= BIT15 | (KeyType<<2) | KeyIndex;


	क्रम (i = 0; i < CAM_CONTENT_COUNT; i++) अणु
		TargetCommand  = i + CAM_CONTENT_COUNT * EntryNo;
		TargetCommand |= BIT31|BIT16;

		अगर (i == 0) अणु
			TargetContent = (u32)(*(MacAddr+0)) << 16 |
				(u32)(*(MacAddr+1)) << 24 |
				(u32)usConfig;

			rtl92e_ग_लिखोl(dev, WCAMI, TargetContent);
			rtl92e_ग_लिखोl(dev, RWCAM, TargetCommand);
		पूर्ण अन्यथा अगर (i == 1) अणु
			TargetContent = (u32)(*(MacAddr+2)) |
				(u32)(*(MacAddr+3)) <<  8 |
				(u32)(*(MacAddr+4)) << 16 |
				(u32)(*(MacAddr+5)) << 24;
			rtl92e_ग_लिखोl(dev, WCAMI, TargetContent);
			rtl92e_ग_लिखोl(dev, RWCAM, TargetCommand);
		पूर्ण अन्यथा अणु
			अगर (KeyContent != शून्य) अणु
				rtl92e_ग_लिखोl(dev, WCAMI,
					      (u32)(*(KeyContent+i-2)));
				rtl92e_ग_लिखोl(dev, RWCAM, TargetCommand);
				udelay(100);
			पूर्ण
		पूर्ण
	पूर्ण
	RT_TRACE(COMP_SEC, "=========>after set key, usconfig:%x\n", usConfig);
पूर्ण

व्योम rtl92e_cam_restore(काष्ठा net_device *dev)
अणु
	u8 EntryId = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 *MacAddr = priv->rtllib->current_network.bssid;

	अटल u8	CAM_CONST_ADDR[4][6] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण
	पूर्ण;
	अटल u8	CAM_CONST_BROAD[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;

	RT_TRACE(COMP_SEC, "%s:\n", __func__);


	अगर ((priv->rtllib->pairwise_key_type == KEY_TYPE_WEP40) ||
	    (priv->rtllib->pairwise_key_type == KEY_TYPE_WEP104)) अणु

		क्रम (EntryId = 0; EntryId < 4; EntryId++) अणु
			MacAddr = CAM_CONST_ADDR[EntryId];
			अगर (priv->rtllib->swcamtable[EntryId].bused) अणु
				rtl92e_set_key(dev, EntryId, EntryId,
					       priv->rtllib->pairwise_key_type,
					       MacAddr, 0,
					       (u32 *)(&priv->rtllib->swcamtable
						       [EntryId].key_buf[0]));
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (priv->rtllib->pairwise_key_type == KEY_TYPE_TKIP) अणु
		अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC) अणु
			rtl92e_set_key(dev, 4, 0,
				       priv->rtllib->pairwise_key_type,
				       (u8 *)dev->dev_addr, 0,
				       (u32 *)(&priv->rtllib->swcamtable[4].
				       key_buf[0]));
		पूर्ण अन्यथा अणु
			rtl92e_set_key(dev, 4, 0,
				       priv->rtllib->pairwise_key_type,
				       MacAddr, 0,
				       (u32 *)(&priv->rtllib->swcamtable[4].
				       key_buf[0]));
		पूर्ण

	पूर्ण अन्यथा अगर (priv->rtllib->pairwise_key_type == KEY_TYPE_CCMP) अणु
		अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC) अणु
			rtl92e_set_key(dev, 4, 0,
				       priv->rtllib->pairwise_key_type,
				       (u8 *)dev->dev_addr, 0,
				       (u32 *)(&priv->rtllib->swcamtable[4].
				       key_buf[0]));
		पूर्ण अन्यथा अणु
			rtl92e_set_key(dev, 4, 0,
				       priv->rtllib->pairwise_key_type, MacAddr,
				       0, (u32 *)(&priv->rtllib->swcamtable[4].
				       key_buf[0]));
			पूर्ण
	पूर्ण

	अगर (priv->rtllib->group_key_type == KEY_TYPE_TKIP) अणु
		MacAddr = CAM_CONST_BROAD;
		क्रम (EntryId = 1; EntryId < 4; EntryId++) अणु
			अगर (priv->rtllib->swcamtable[EntryId].bused) अणु
				rtl92e_set_key(dev, EntryId, EntryId,
					       priv->rtllib->group_key_type,
					       MacAddr, 0,
					       (u32 *)(&priv->rtllib->swcamtable[EntryId].key_buf[0]));
			पूर्ण
		पूर्ण
		अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC) अणु
			अगर (priv->rtllib->swcamtable[0].bused) अणु
				rtl92e_set_key(dev, 0, 0,
					       priv->rtllib->group_key_type,
					       CAM_CONST_ADDR[0], 0,
					       (u32 *)(&priv->rtllib->swcamtable[0].key_buf[0]));
			पूर्ण अन्यथा अणु
				netdev_warn(dev,
					    "%s(): ADHOC TKIP: missing key entry.\n",
					    __func__);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (priv->rtllib->group_key_type == KEY_TYPE_CCMP) अणु
		MacAddr = CAM_CONST_BROAD;
		क्रम (EntryId = 1; EntryId < 4; EntryId++) अणु
			अगर (priv->rtllib->swcamtable[EntryId].bused) अणु
				rtl92e_set_key(dev, EntryId, EntryId,
					       priv->rtllib->group_key_type,
					       MacAddr, 0,
					       (u32 *)(&priv->rtllib->swcamtable[EntryId].key_buf[0]));
			पूर्ण
		पूर्ण

		अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC) अणु
			अगर (priv->rtllib->swcamtable[0].bused) अणु
				rtl92e_set_key(dev, 0, 0,
					       priv->rtllib->group_key_type,
					       CAM_CONST_ADDR[0], 0,
					       (u32 *)(&priv->rtllib->swcamtable[0].key_buf[0]));
			पूर्ण अन्यथा अणु
				netdev_warn(dev,
					    "%s(): ADHOC CCMP: missing key entry.\n",
					    __func__);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
