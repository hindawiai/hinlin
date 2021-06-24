<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_MLME_EXT_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_wअगरi_regd.h>
#समावेश <hal_btcoex.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>

अटल काष्ठा mlme_handler mlme_sta_tbl[] = अणु
	अणुWIFI_ASSOCREQ,		"OnAssocReq",	&OnAssocReqपूर्ण,
	अणुWIFI_ASSOCRSP,		"OnAssocRsp",	&OnAssocRspपूर्ण,
	अणुWIFI_REASSOCREQ,	"OnReAssocReq",	&OnAssocReqपूर्ण,
	अणुWIFI_REASSOCRSP,	"OnReAssocRsp",	&OnAssocRspपूर्ण,
	अणुWIFI_PROBEREQ,		"OnProbeReq",	&OnProbeReqपूर्ण,
	अणुWIFI_PROBERSP,		"OnProbeRsp",		&OnProbeRspपूर्ण,

	/*----------------------------------------------------------
					below 2 are reserved
	-----------------------------------------------------------*/
	अणु0,					"DoReserved",		&DoReservedपूर्ण,
	अणु0,					"DoReserved",		&DoReservedपूर्ण,
	अणुWIFI_BEACON,		"OnBeacon",		&OnBeaconपूर्ण,
	अणुWIFI_ATIM,			"OnATIM",		&OnAtimपूर्ण,
	अणुWIFI_DISASSOC,		"OnDisassoc",		&OnDisassocपूर्ण,
	अणुWIFI_AUTH,			"OnAuth",		&OnAuthClientपूर्ण,
	अणुWIFI_DEAUTH,		"OnDeAuth",		&OnDeAuthपूर्ण,
	अणुWIFI_ACTION,		"OnAction",		&OnActionपूर्ण,
	अणुWIFI_ACTION_NOACK, "OnActionNoAck",	&OnActionपूर्ण,
पूर्ण;

अटल काष्ठा action_handler OnAction_tbl[] = अणु
	अणुRTW_WLAN_CATEGORY_SPECTRUM_MGMT,	 "ACTION_SPECTRUM_MGMT", on_action_spctपूर्ण,
	अणुRTW_WLAN_CATEGORY_QOS, "ACTION_QOS", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_DLS, "ACTION_DLS", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_BACK, "ACTION_BACK", &OnAction_backपूर्ण,
	अणुRTW_WLAN_CATEGORY_PUBLIC, "ACTION_PUBLIC", on_action_खुलापूर्ण,
	अणुRTW_WLAN_CATEGORY_RADIO_MEASUREMENT, "ACTION_RADIO_MEASUREMENT", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_FT, "ACTION_FT",	&DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_HT,	"ACTION_HT",	&OnAction_htपूर्ण,
	अणुRTW_WLAN_CATEGORY_SA_QUERY, "ACTION_SA_QUERY", &OnAction_sa_queryपूर्ण,
	अणुRTW_WLAN_CATEGORY_UNPROTECTED_WNM, "ACTION_UNPROTECTED_WNM", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_SELF_PROTECTED, "ACTION_SELF_PROTECTED", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_WMM, "ACTION_WMM", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_VHT, "ACTION_VHT", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_P2P, "ACTION_P2P", &DoReservedपूर्ण,
पूर्ण;

अटल u8 null_addr[ETH_ALEN] = अणु0, 0, 0, 0, 0, 0पूर्ण;

/**************************************************
OUI definitions क्रम the venकरोr specअगरic IE
***************************************************/
अचिन्हित अक्षर RTW_WPA_OUI[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
अचिन्हित अक्षर WMM_OUI[] = अणु0x00, 0x50, 0xf2, 0x02पूर्ण;
अचिन्हित अक्षर WPS_OUI[] = अणु0x00, 0x50, 0xf2, 0x04पूर्ण;
अचिन्हित अक्षर P2P_OUI[] = अणु0x50, 0x6F, 0x9A, 0x09पूर्ण;
अचिन्हित अक्षर WFD_OUI[] = अणु0x50, 0x6F, 0x9A, 0x0Aपूर्ण;

अचिन्हित अक्षर WMM_INFO_OUI[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01पूर्ण;
अचिन्हित अक्षर WMM_PARA_OUI[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;

अटल अचिन्हित अक्षर REALTEK_96B_IE[] = अणु0x00, 0xe0, 0x4c, 0x02, 0x01, 0x20पूर्ण;

/********************************************************
ChannelPlan definitions
*********************************************************/
अटल काष्ठा rt_channel_plan_2g	RTW_ChannelPlan2G[RT_CHANNEL_DOMAIN_2G_MAX] = अणु
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,		/*  0x00, RT_CHANNEL_DOMAIN_2G_WORLD , Passive scan CH 12, 13 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,		/*  0x01, RT_CHANNEL_DOMAIN_2G_ETSI1 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11पूर्ण, 11पूर्ण,			/*  0x02, RT_CHANNEL_DOMAIN_2G_FCC1 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14पूर्ण, 14पूर्ण,	/*  0x03, RT_CHANNEL_DOMAIN_2G_MIKK1 */
	अणुअणु10, 11, 12, 13पूर्ण, 4पूर्ण,						/*  0x04, RT_CHANNEL_DOMAIN_2G_ETSI2 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14पूर्ण, 14पूर्ण,	/*  0x05, RT_CHANNEL_DOMAIN_2G_GLOBAL , Passive scan CH 12, 13, 14 */
	अणुअणुपूर्ण, 0पूर्ण,								/*  0x06, RT_CHANNEL_DOMAIN_2G_शून्य */
पूर्ण;

अटल काष्ठा rt_channel_plan_5g	RTW_ChannelPlan5G[RT_CHANNEL_DOMAIN_5G_MAX] = अणु
	अणुअणुपूर्ण, 0पूर्ण,																					/*  0x00, RT_CHANNEL_DOMAIN_5G_शून्य */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140पूर्ण, 19पूर्ण,						/*  0x01, RT_CHANNEL_DOMAIN_5G_ETSI1 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 24पूर्ण,	/*  0x02, RT_CHANNEL_DOMAIN_5G_ETSI2 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 149, 153, 157, 161, 165पूर्ण, 22पूर्ण,			/*  0x03, RT_CHANNEL_DOMAIN_5G_ETSI3 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 24पूर्ण,	/*  0x04, RT_CHANNEL_DOMAIN_5G_FCC1 */
	अणुअणु36, 40, 44, 48, 149, 153, 157, 161, 165पूर्ण, 9पूर्ण,														/*  0x05, RT_CHANNEL_DOMAIN_5G_FCC2 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161, 165पूर्ण, 13पूर्ण,											/*  0x06, RT_CHANNEL_DOMAIN_5G_FCC3 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161पूर्ण, 12पूर्ण,												/*  0x07, RT_CHANNEL_DOMAIN_5G_FCC4 */
	अणुअणु149, 153, 157, 161, 165पूर्ण, 5पूर्ण,																	/*  0x08, RT_CHANNEL_DOMAIN_5G_FCC5 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 8पूर्ण,																/*  0x09, RT_CHANNEL_DOMAIN_5G_FCC6 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 136, 140, 149, 153, 157, 161, 165पूर्ण, 20पूर्ण,					/*  0x0A, RT_CHANNEL_DOMAIN_5G_FCC7_IC1 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 149, 153, 157, 161, 165पूर्ण, 20पूर्ण,					/*  0x0B, RT_CHANNEL_DOMAIN_5G_KCC1 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140पूर्ण, 19पूर्ण,						/*  0x0C, RT_CHANNEL_DOMAIN_5G_MKK1 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 8पूर्ण,																/*  0x0D, RT_CHANNEL_DOMAIN_5G_MKK2 */
	अणुअणु100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140पूर्ण, 11पूर्ण,											/*  0x0E, RT_CHANNEL_DOMAIN_5G_MKK3 */
	अणुअणु56, 60, 64, 100, 104, 108, 112, 116, 136, 140, 149, 153, 157, 161, 165पूर्ण, 15पूर्ण,								/*  0x0F, RT_CHANNEL_DOMAIN_5G_NCC1 */
	अणुअणु56, 60, 64, 149, 153, 157, 161, 165पूर्ण, 8पूर्ण,															/*  0x10, RT_CHANNEL_DOMAIN_5G_NCC2 */
	अणुअणु149, 153, 157, 161, 165पूर्ण, 5पूर्ण,																	/*  0x11, RT_CHANNEL_DOMAIN_5G_NCC3 */
	अणुअणु36, 40, 44, 48पूर्ण, 4पूर्ण,																			/*  0x12, RT_CHANNEL_DOMAIN_5G_ETSI4 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 136, 140, 149, 153, 157, 161, 165पूर्ण, 20पूर्ण,					/*  0x13, RT_CHANNEL_DOMAIN_5G_ETSI5 */
	अणुअणु149, 153, 157, 161पूर्ण, 4पूर्ण,																		/*  0x14, RT_CHANNEL_DOMAIN_5G_FCC8 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 8पूर्ण,																/*  0x15, RT_CHANNEL_DOMAIN_5G_ETSI6 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161, 165पूर्ण, 13पूर्ण,											/*  0x16, RT_CHANNEL_DOMAIN_5G_ETSI7 */
	अणुअणु36, 40, 44, 48, 149, 153, 157, 161, 165पूर्ण, 9पूर्ण,														/*  0x17, RT_CHANNEL_DOMAIN_5G_ETSI8 */
	अणुअणु100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140पूर्ण, 11पूर्ण,											/*  0x18, RT_CHANNEL_DOMAIN_5G_ETSI9 */
	अणुअणु149, 153, 157, 161, 165पूर्ण, 5पूर्ण,																	/*  0x19, RT_CHANNEL_DOMAIN_5G_ETSI10 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 16पूर्ण,									/*  0x1A, RT_CHANNEL_DOMAIN_5G_ETSI11 */
	अणुअणु52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 17पूर्ण,							/*  0x1B, RT_CHANNEL_DOMAIN_5G_NCC4 */
	अणुअणु149, 153, 157, 161पूर्ण, 4पूर्ण,																		/*  0x1C, RT_CHANNEL_DOMAIN_5G_ETSI12 */
	अणुअणु36, 40, 44, 48, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 17पूर्ण,							/*  0x1D, RT_CHANNEL_DOMAIN_5G_FCC9 */
	अणुअणु36, 40, 44, 48, 100, 104, 108, 112, 116, 132, 136, 140पूर्ण, 12पूर्ण,											/*  0x1E, RT_CHANNEL_DOMAIN_5G_ETSI13 */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161पूर्ण, 20पूर्ण,					/*  0x1F, RT_CHANNEL_DOMAIN_5G_FCC10 */

	/*  Driver self defined क्रम old channel plan Compatible , Remember to modअगरy अगर have new channel plan definition ===== */
	अणुअणु36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165पूर्ण, 21पूर्ण,				/*  0x20, RT_CHANNEL_DOMAIN_5G_FCC */
	अणुअणु36, 40, 44, 48पूर्ण, 4पूर्ण,																			/*  0x21, RT_CHANNEL_DOMAIN_5G_JAPAN_NO_DFS */
	अणुअणु36, 40, 44, 48, 149, 153, 157, 161पूर्ण, 8पूर्ण,															/*  0x22, RT_CHANNEL_DOMAIN_5G_FCC4_NO_DFS */
पूर्ण;

अटल काष्ठा rt_channel_plan_map	RTW_ChannelPlanMap[RT_CHANNEL_DOMAIN_MAX] = अणु
	/*  0x00 ~ 0x1F , Old Define ===== */
	अणु0x02, 0x20पूर्ण,	/* 0x00, RT_CHANNEL_DOMAIN_FCC */
	अणु0x02, 0x0Aपूर्ण,	/* 0x01, RT_CHANNEL_DOMAIN_IC */
	अणु0x01, 0x01पूर्ण,	/* 0x02, RT_CHANNEL_DOMAIN_ETSI */
	अणु0x01, 0x00पूर्ण,	/* 0x03, RT_CHANNEL_DOMAIN_SPAIN */
	अणु0x01, 0x00पूर्ण,	/* 0x04, RT_CHANNEL_DOMAIN_FRANCE */
	अणु0x03, 0x00पूर्ण,	/* 0x05, RT_CHANNEL_DOMAIN_MKK */
	अणु0x03, 0x00पूर्ण,	/* 0x06, RT_CHANNEL_DOMAIN_MKK1 */
	अणु0x01, 0x09पूर्ण,	/* 0x07, RT_CHANNEL_DOMAIN_ISRAEL */
	अणु0x03, 0x09पूर्ण,	/* 0x08, RT_CHANNEL_DOMAIN_TELEC */
	अणु0x03, 0x00पूर्ण,	/* 0x09, RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN */
	अणु0x00, 0x00पूर्ण,	/* 0x0A, RT_CHANNEL_DOMAIN_WORLD_WIDE_13 */
	अणु0x02, 0x0Fपूर्ण,	/* 0x0B, RT_CHANNEL_DOMAIN_TAIWAN */
	अणु0x01, 0x08पूर्ण,	/* 0x0C, RT_CHANNEL_DOMAIN_CHINA */
	अणु0x02, 0x06पूर्ण,	/* 0x0D, RT_CHANNEL_DOMAIN_SINGAPORE_INDIA_MEXICO */
	अणु0x02, 0x0Bपूर्ण,	/* 0x0E, RT_CHANNEL_DOMAIN_KOREA */
	अणु0x02, 0x09पूर्ण,	/* 0x0F, RT_CHANNEL_DOMAIN_TURKEY */
	अणु0x01, 0x01पूर्ण,	/* 0x10, RT_CHANNEL_DOMAIN_JAPAN */
	अणु0x02, 0x05पूर्ण,	/* 0x11, RT_CHANNEL_DOMAIN_FCC_NO_DFS */
	अणु0x01, 0x21पूर्ण,	/* 0x12, RT_CHANNEL_DOMAIN_JAPAN_NO_DFS */
	अणु0x00, 0x04पूर्ण,	/* 0x13, RT_CHANNEL_DOMAIN_WORLD_WIDE_5G */
	अणु0x02, 0x10पूर्ण,	/* 0x14, RT_CHANNEL_DOMAIN_TAIWAN_NO_DFS */
	अणु0x00, 0x21पूर्ण,	/* 0x15, RT_CHANNEL_DOMAIN_ETSI_NO_DFS */
	अणु0x00, 0x22पूर्ण,	/* 0x16, RT_CHANNEL_DOMAIN_KOREA_NO_DFS */
	अणु0x03, 0x21पूर्ण,	/* 0x17, RT_CHANNEL_DOMAIN_JAPAN_NO_DFS */
	अणु0x06, 0x08पूर्ण,	/* 0x18, RT_CHANNEL_DOMAIN_PAKISTAN_NO_DFS */
	अणु0x02, 0x08पूर्ण,	/* 0x19, RT_CHANNEL_DOMAIN_TAIWAN2_NO_DFS */
	अणु0x00, 0x00पूर्ण,	/* 0x1A, */
	अणु0x00, 0x00पूर्ण,	/* 0x1B, */
	अणु0x00, 0x00पूर्ण,	/* 0x1C, */
	अणु0x00, 0x00पूर्ण,	/* 0x1D, */
	अणु0x00, 0x00पूर्ण,	/* 0x1E, */
	अणु0x06, 0x04पूर्ण,	/* 0x1F, RT_CHANNEL_DOMAIN_WORLD_WIDE_ONLY_5G */
	/*  0x20 ~ 0x7F , New Define ===== */
	अणु0x00, 0x00पूर्ण,	/* 0x20, RT_CHANNEL_DOMAIN_WORLD_शून्य */
	अणु0x01, 0x00पूर्ण,	/* 0x21, RT_CHANNEL_DOMAIN_ETSI1_शून्य */
	अणु0x02, 0x00पूर्ण,	/* 0x22, RT_CHANNEL_DOMAIN_FCC1_शून्य */
	अणु0x03, 0x00पूर्ण,	/* 0x23, RT_CHANNEL_DOMAIN_MKK1_शून्य */
	अणु0x04, 0x00पूर्ण,	/* 0x24, RT_CHANNEL_DOMAIN_ETSI2_शून्य */
	अणु0x02, 0x04पूर्ण,	/* 0x25, RT_CHANNEL_DOMAIN_FCC1_FCC1 */
	अणु0x00, 0x01पूर्ण,	/* 0x26, RT_CHANNEL_DOMAIN_WORLD_ETSI1 */
	अणु0x03, 0x0Cपूर्ण,	/* 0x27, RT_CHANNEL_DOMAIN_MKK1_MKK1 */
	अणु0x00, 0x0Bपूर्ण,	/* 0x28, RT_CHANNEL_DOMAIN_WORLD_KCC1 */
	अणु0x00, 0x05पूर्ण,	/* 0x29, RT_CHANNEL_DOMAIN_WORLD_FCC2 */
	अणु0x00, 0x00पूर्ण,	/* 0x2A, */
	अणु0x00, 0x00पूर्ण,	/* 0x2B, */
	अणु0x00, 0x00पूर्ण,	/* 0x2C, */
	अणु0x00, 0x00पूर्ण,	/* 0x2D, */
	अणु0x00, 0x00पूर्ण,	/* 0x2E, */
	अणु0x00, 0x00पूर्ण,	/* 0x2F, */
	अणु0x00, 0x06पूर्ण,	/* 0x30, RT_CHANNEL_DOMAIN_WORLD_FCC3 */
	अणु0x00, 0x07पूर्ण,	/* 0x31, RT_CHANNEL_DOMAIN_WORLD_FCC4 */
	अणु0x00, 0x08पूर्ण,	/* 0x32, RT_CHANNEL_DOMAIN_WORLD_FCC5 */
	अणु0x00, 0x09पूर्ण,	/* 0x33, RT_CHANNEL_DOMAIN_WORLD_FCC6 */
	अणु0x02, 0x0Aपूर्ण,	/* 0x34, RT_CHANNEL_DOMAIN_FCC1_FCC7 */
	अणु0x00, 0x02पूर्ण,	/* 0x35, RT_CHANNEL_DOMAIN_WORLD_ETSI2 */
	अणु0x00, 0x03पूर्ण,	/* 0x36, RT_CHANNEL_DOMAIN_WORLD_ETSI3 */
	अणु0x03, 0x0Dपूर्ण,	/* 0x37, RT_CHANNEL_DOMAIN_MKK1_MKK2 */
	अणु0x03, 0x0Eपूर्ण,	/* 0x38, RT_CHANNEL_DOMAIN_MKK1_MKK3 */
	अणु0x02, 0x0Fपूर्ण,	/* 0x39, RT_CHANNEL_DOMAIN_FCC1_NCC1 */
	अणु0x00, 0x00पूर्ण,	/* 0x3A, */
	अणु0x00, 0x00पूर्ण,	/* 0x3B, */
	अणु0x00, 0x00पूर्ण,	/* 0x3C, */
	अणु0x00, 0x00पूर्ण,	/* 0x3D, */
	अणु0x00, 0x00पूर्ण,	/* 0x3E, */
	अणु0x00, 0x00पूर्ण,	/* 0x3F, */
	अणु0x02, 0x10पूर्ण,	/* 0x40, RT_CHANNEL_DOMAIN_FCC1_NCC2 */
	अणु0x05, 0x00पूर्ण,	/* 0x41, RT_CHANNEL_DOMAIN_GLOBAL_शून्य */
	अणु0x01, 0x12पूर्ण,	/* 0x42, RT_CHANNEL_DOMAIN_ETSI1_ETSI4 */
	अणु0x02, 0x05पूर्ण,	/* 0x43, RT_CHANNEL_DOMAIN_FCC1_FCC2 */
	अणु0x02, 0x11पूर्ण,	/* 0x44, RT_CHANNEL_DOMAIN_FCC1_NCC3 */
	अणु0x00, 0x13पूर्ण,	/* 0x45, RT_CHANNEL_DOMAIN_WORLD_ETSI5 */
	अणु0x02, 0x14पूर्ण,	/* 0x46, RT_CHANNEL_DOMAIN_FCC1_FCC8 */
	अणु0x00, 0x15पूर्ण,	/* 0x47, RT_CHANNEL_DOMAIN_WORLD_ETSI6 */
	अणु0x00, 0x16पूर्ण,	/* 0x48, RT_CHANNEL_DOMAIN_WORLD_ETSI7 */
	अणु0x00, 0x17पूर्ण,	/* 0x49, RT_CHANNEL_DOMAIN_WORLD_ETSI8 */
	अणु0x00, 0x18पूर्ण,	/* 0x50, RT_CHANNEL_DOMAIN_WORLD_ETSI9 */
	अणु0x00, 0x19पूर्ण,	/* 0x51, RT_CHANNEL_DOMAIN_WORLD_ETSI10 */
	अणु0x00, 0x1Aपूर्ण,	/* 0x52, RT_CHANNEL_DOMAIN_WORLD_ETSI11 */
	अणु0x02, 0x1Bपूर्ण,	/* 0x53, RT_CHANNEL_DOMAIN_FCC1_NCC4 */
	अणु0x00, 0x1Cपूर्ण,	/* 0x54, RT_CHANNEL_DOMAIN_WORLD_ETSI12 */
	अणु0x02, 0x1Dपूर्ण,	/* 0x55, RT_CHANNEL_DOMAIN_FCC1_FCC9 */
	अणु0x00, 0x1Eपूर्ण,	/* 0x56, RT_CHANNEL_DOMAIN_WORLD_ETSI13 */
	अणु0x02, 0x1Fपूर्ण,	/* 0x57, RT_CHANNEL_DOMAIN_FCC1_FCC10 */
पूर्ण;

 /* use the combination क्रम max channel numbers */
अटल काष्ठा rt_channel_plan_map RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE = अणु0x03, 0x02पूर्ण;

/* Search the @param ch in given @param ch_set
 * @ch_set: the given channel set
 * @ch: the given channel number
 *
 * वापस the index of channel_num in channel_set, -1 अगर not found
 */
पूर्णांक rtw_ch_set_search_ch(काष्ठा rt_channel_info *ch_set, स्थिर u32 ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; ch_set[i].ChannelNum != 0; i++) अणु
		अगर (ch == ch_set[i].ChannelNum)
			अवरोध;
	पूर्ण

	अगर (i >= ch_set[i].ChannelNum)
		वापस -1;
	वापस i;
पूर्ण

/* Check the @param ch is fit with setband setting of @param adapter
 * @adapter: the given adapter
 * @ch: the given channel number
 *
 * वापस true when check valid, false not valid
 */
bool rtw_mlme_band_check(काष्ठा adapter *adapter, स्थिर u32 ch)
अणु
	अगर (adapter->setband == GHZ24_50 /* 2.4G and 5G */
		|| (adapter->setband == GHZ_24 && ch < 35) /* 2.4G only */
		|| (adapter->setband == GHZ_50 && ch > 35) /* 5G only */
	) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/****************************************************************************

Following are the initialization functions क्रम WiFi MLME

*****************************************************************************/

पूर्णांक init_hw_mlme_ext(काष्ठा adapter *padapter)
अणु
	काष्ठा	mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
	वापस _SUCCESS;
पूर्ण

व्योम init_mlme_शेष_rate_set(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अचिन्हित अक्षर mixed_datarate[NumRates] = अणु_1M_RATE_, _2M_RATE_, _5M_RATE_, _11M_RATE_, _6M_RATE_, _9M_RATE_, _12M_RATE_, _18M_RATE_, _24M_RATE_, _36M_RATE_, _48M_RATE_, _54M_RATE_, 0xffपूर्ण;
	अचिन्हित अक्षर mixed_basicrate[NumRates] = अणु_1M_RATE_, _2M_RATE_, _5M_RATE_, _11M_RATE_, _6M_RATE_, _12M_RATE_, _24M_RATE_, 0xff,पूर्ण;
	अचिन्हित अक्षर supported_mcs_set[16] = अणु0xff, 0xff, 0x00, 0x00, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0पूर्ण;

	स_नकल(pmlmeext->datarate, mixed_datarate, NumRates);
	स_नकल(pmlmeext->basicrate, mixed_basicrate, NumRates);

	स_नकल(pmlmeext->शेष_supported_mcs_set, supported_mcs_set, माप(pmlmeext->शेष_supported_mcs_set));
पूर्ण

अटल व्योम init_mlme_ext_priv_value(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	atomic_set(&pmlmeext->event_seq, 0);
	pmlmeext->mgnt_seq = 0;/* reset to zero when disconnect at client mode */
	pmlmeext->sa_query_seq = 0;
	pmlmeext->mgnt_80211w_IPN = 0;
	pmlmeext->mgnt_80211w_IPN_rx = 0;
	pmlmeext->cur_channel = padapter->registrypriv.channel;
	pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	pmlmeext->retry = 0;

	pmlmeext->cur_wireless_mode = padapter->registrypriv.wireless_mode;

	init_mlme_शेष_rate_set(padapter);

	pmlmeext->tx_rate = IEEE80211_CCK_RATE_1MB;
	pmlmeext->sitesurvey_res.state = SCAN_DISABLE;
	pmlmeext->sitesurvey_res.channel_idx = 0;
	pmlmeext->sitesurvey_res.bss_cnt = 0;
	pmlmeext->scan_पात = false;

	pmlmeinfo->state = WIFI_FW_शून्य_STATE;
	pmlmeinfo->reauth_count = 0;
	pmlmeinfo->reassoc_count = 0;
	pmlmeinfo->link_count = 0;
	pmlmeinfo->auth_seq = 0;
	pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Open;
	pmlmeinfo->key_index = 0;
	pmlmeinfo->iv = 0;

	pmlmeinfo->enc_algo = _NO_PRIVACY_;
	pmlmeinfo->authModeToggle = 0;

	स_रखो(pmlmeinfo->chg_txt, 0, 128);

	pmlmeinfo->slotTime = SHORT_SLOT_TIME;
	pmlmeinfo->preamble_mode = PREAMBLE_AUTO;

	pmlmeinfo->dialogToken = 0;

	pmlmeext->action_खुला_rxseq = 0xffff;
	pmlmeext->action_खुला_dialog_token = 0xff;
पूर्ण

अटल पूर्णांक has_channel(काष्ठा rt_channel_info *channel_set,
					   u8 chanset_size,
					   u8 chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chanset_size; i++) अणु
		अगर (channel_set[i].ChannelNum == chan) अणु
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम init_channel_list(काष्ठा adapter *padapter, काष्ठा rt_channel_info *channel_set,
							  u8 chanset_size,
							  काष्ठा p2p_channels *channel_list)
अणु

	अटल स्थिर काष्ठा p2p_oper_class_map op_class[] = अणु
		अणु IEEE80211G,  81,   1,  13,  1, BW20 पूर्ण,
		अणु IEEE80211G,  82,  14,  14,  1, BW20 पूर्ण,
		अणु IEEE80211A, 115,  36,  48,  4, BW20 पूर्ण,
		अणु IEEE80211A, 116,  36,  44,  8, BW40PLUS पूर्ण,
		अणु IEEE80211A, 117,  40,  48,  8, BW40MINUS पूर्ण,
		अणु IEEE80211A, 124, 149, 161,  4, BW20 पूर्ण,
		अणु IEEE80211A, 125, 149, 169,  4, BW20 पूर्ण,
		अणु IEEE80211A, 126, 149, 157,  8, BW40PLUS पूर्ण,
		अणु IEEE80211A, 127, 153, 161,  8, BW40MINUS पूर्ण,
		अणु -1, 0, 0, 0, 0, BW20 पूर्ण
	पूर्ण;

	पूर्णांक cla, op;

	cla = 0;

	क्रम (op = 0; op_class[op].op_class; op++) अणु
		u8 ch;
		स्थिर काष्ठा p2p_oper_class_map *o = &op_class[op];
		काष्ठा p2p_reg_class *reg = शून्य;

		क्रम (ch = o->min_chan; ch <= o->max_chan; ch += o->inc) अणु
			अगर (!has_channel(channel_set, chanset_size, ch))
				जारी;

			अगर ((0 == padapter->registrypriv.ht_enable) && (8 == o->inc))
				जारी;

			अगर ((0 < (padapter->registrypriv.bw_mode & 0xf0)) &&
				((BW40MINUS == o->bw) || (BW40PLUS == o->bw)))
				जारी;

			अगर (!reg) अणु
				reg = &channel_list->reg_class[cla];
				cla++;
				reg->reg_class = o->op_class;
				reg->channels = 0;
			पूर्ण
			reg->channel[reg->channels] = ch;
			reg->channels++;
		पूर्ण
	पूर्ण
	channel_list->reg_classes = cla;

पूर्ण

अटल u8 init_channel_set(काष्ठा adapter *padapter, u8 ChannelPlan, काष्ठा rt_channel_info *channel_set)
अणु
	u8 index, chanset_size = 0;
	u8 b5GBand = false, b2_4GBand = false;
	u8 Index2G = 0, Index5G = 0;

	स_रखो(channel_set, 0, माप(काष्ठा rt_channel_info)*MAX_CHANNEL_NUM);

	अगर (ChannelPlan >= RT_CHANNEL_DOMAIN_MAX && ChannelPlan != RT_CHANNEL_DOMAIN_REALTEK_DEFINE)
		वापस chanset_size;

	अगर (IsSupported24G(padapter->registrypriv.wireless_mode)) अणु
		b2_4GBand = true;
		अगर (RT_CHANNEL_DOMAIN_REALTEK_DEFINE == ChannelPlan)
			Index2G = RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE.Index2G;
		अन्यथा
			Index2G = RTW_ChannelPlanMap[ChannelPlan].Index2G;
	पूर्ण

	अगर (b2_4GBand) अणु
		क्रम (index = 0; index < RTW_ChannelPlan2G[Index2G].Len; index++) अणु
			channel_set[chanset_size].ChannelNum = RTW_ChannelPlan2G[Index2G].Channel[index];

			अगर ((RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN == ChannelPlan) ||/* Channel 1~11 is active, and 12~14 is passive */
				(RT_CHANNEL_DOMAIN_GLOBAL_शून्य == ChannelPlan)) अणु
				अगर (channel_set[chanset_size].ChannelNum >= 1 && channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				अन्यथा अगर ((channel_set[chanset_size].ChannelNum  >= 12 && channel_set[chanset_size].ChannelNum  <= 14))
					channel_set[chanset_size].ScanType  = SCAN_PASSIVE;
			पूर्ण अन्यथा अगर (RT_CHANNEL_DOMAIN_WORLD_WIDE_13 == ChannelPlan ||
				RT_CHANNEL_DOMAIN_WORLD_WIDE_5G == ChannelPlan ||
				RT_CHANNEL_DOMAIN_2G_WORLD == Index2G) अणु /*  channel 12~13, passive scan */
				अगर (channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				अन्यथा
					channel_set[chanset_size].ScanType = SCAN_PASSIVE;
			पूर्ण अन्यथा
				channel_set[chanset_size].ScanType = SCAN_ACTIVE;

			chanset_size++;
		पूर्ण
	पूर्ण

	अगर (b5GBand) अणु
		क्रम (index = 0; index < RTW_ChannelPlan5G[Index5G].Len; index++) अणु
			अगर (RTW_ChannelPlan5G[Index5G].Channel[index] <= 48
				|| RTW_ChannelPlan5G[Index5G].Channel[index] >= 149) अणु
				channel_set[chanset_size].ChannelNum = RTW_ChannelPlan5G[Index5G].Channel[index];
				अगर (RT_CHANNEL_DOMAIN_WORLD_WIDE_5G == ChannelPlan)/* passive scan क्रम all 5G channels */
					channel_set[chanset_size].ScanType = SCAN_PASSIVE;
				अन्यथा
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				chanset_size++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस chanset_size;
पूर्ण

व्योम init_mlme_ext_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	pmlmeext->padapter = padapter;

	/* fill_fwpriv(padapter, &(pmlmeext->fwpriv)); */

	init_mlme_ext_priv_value(padapter);
	pmlmeinfo->accept_addba_req = pregistrypriv->accept_addba_req;

	init_mlme_ext_समयr(padapter);

	init_mlme_ap_info(padapter);

	pmlmeext->max_chan_nums = init_channel_set(padapter, pmlmepriv->ChannelPlan, pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);
	pmlmeext->last_scan_समय = 0;
	pmlmeext->chan_scan_समय = SURVEY_TO;
	pmlmeext->mlmeext_init = true;
	pmlmeext->active_keep_alive_check = true;

#अगर_घोषित DBG_FIXED_CHAN
	pmlmeext->fixed_chan = 0xFF;
#पूर्ण_अगर
पूर्ण

व्योम मुक्त_mlme_ext_priv(काष्ठा mlme_ext_priv *pmlmeext)
अणु
	काष्ठा adapter *padapter = pmlmeext->padapter;

	अगर (!padapter)
		वापस;

	अगर (padapter->bDriverStopped) अणु
		del_समयr_sync(&pmlmeext->survey_समयr);
		del_समयr_sync(&pmlmeext->link_समयr);
		/* del_समयr_sync(&pmlmeext->ADDBA_समयr); */
	पूर्ण
पूर्ण

अटल व्योम _mgt_dispatcher(काष्ठा adapter *padapter, काष्ठा mlme_handler *ptable, जोड़ recv_frame *precv_frame)
अणु
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 *pframe = precv_frame->u.hdr.rx_data;

	अगर (ptable->func) अणु
		/* receive the frames that ra(a1) is my address or ra(a1) is bc address. */
		अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN) &&
		    स_भेद(GetAddr1Ptr(pframe), bc_addr, ETH_ALEN))
			वापस;

		ptable->func(padapter, precv_frame);
	पूर्ण
पूर्ण

व्योम mgt_dispatcher(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	पूर्णांक index;
	काष्ठा mlme_handler *ptable;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	काष्ठा sta_info *psta = rtw_get_stainfo(&padapter->stapriv, GetAddr2Ptr(pframe));
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (GetFrameType(pframe) != WIFI_MGT_TYPE)
		वापस;

	/* receive the frames that ra(a1) is my address or ra(a1) is bc address. */
	अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN) &&
		स_भेद(GetAddr1Ptr(pframe), bc_addr, ETH_ALEN)) अणु
		वापस;
	पूर्ण

	ptable = mlme_sta_tbl;

	index = GetFrameSubType(pframe) >> 4;

	अगर (index >= ARRAY_SIZE(mlme_sta_tbl))
		वापस;

	ptable += index;

	अगर (psta) अणु
		अगर (GetRetry(pframe)) अणु
			अगर (precv_frame->u.hdr.attrib.seq_num == psta->RxMgmtFrameSeqNum) अणु
				/* drop the duplicate management frame */
				pdbgpriv->dbg_rx_dup_mgt_frame_drop_count++;
				वापस;
			पूर्ण
		पूर्ण
		psta->RxMgmtFrameSeqNum = precv_frame->u.hdr.attrib.seq_num;
	पूर्ण

	चयन (GetFrameSubType(pframe)) अणु
	हाल WIFI_AUTH:
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
			ptable->func = &OnAuth;
		अन्यथा
			ptable->func = &OnAuthClient;
		fallthrough;
	हाल WIFI_ASSOCREQ:
	हाल WIFI_REASSOCREQ:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	हाल WIFI_PROBEREQ:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	हाल WIFI_BEACON:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	हाल WIFI_ACTION:
		/* अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) */
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	शेष:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	पूर्ण
पूर्ण

/****************************************************************************

Following are the callback functions क्रम each subtype of the management frames

*****************************************************************************/

अचिन्हित पूर्णांक OnProbeReq(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक	ielen;
	अचिन्हित अक्षर *p;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex	*cur = &pmlmeinfo->network;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक len = precv_frame->u.hdr.len;
	u8 is_valid_p2p_probereq = false;

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		वापस _SUCCESS;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == false &&
		check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE) == false) अणु
		वापस _SUCCESS;
	पूर्ण

	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, WLAN_EID_SSID, (पूर्णांक *)&ielen,
			len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);


	/* check (wildcard) SSID */
	अगर (p) अणु
		अगर (is_valid_p2p_probereq)
			जाओ _issue_probersp;

		अगर ((ielen != 0 && false == !स_भेद((व्योम *)(p+2), (व्योम *)cur->Ssid.Ssid, cur->Ssid.SsidLength))
			|| (ielen == 0 && pmlmeinfo->hidden_ssid_mode)
		)
			वापस _SUCCESS;

_issue_probersp:
		अगर ((check_fwstate(pmlmepriv, _FW_LINKED) &&
		     pmlmepriv->cur_network.join_res) ||
		    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
			issue_probersp(padapter, get_sa(pframe), is_valid_p2p_probereq);
	पूर्ण

	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक OnProbeRsp(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		report_survey_event(padapter, precv_frame);
		वापस _SUCCESS;
	पूर्ण

	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक OnBeacon(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	पूर्णांक cam_idx;
	काष्ठा sta_info *psta;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक len = precv_frame->u.hdr.len;
	काष्ठा wlan_bssid_ex *pbss;
	पूर्णांक ret = _SUCCESS;
	u8 *p = शून्य;
	u32 ielen = 0;

	p = rtw_get_ie(pframe + माप(काष्ठा ieee80211_hdr_3addr) + _BEACON_IE_OFFSET_, WLAN_EID_EXT_SUPP_RATES, &ielen, precv_frame->u.hdr.len - माप(काष्ठा ieee80211_hdr_3addr) - _BEACON_IE_OFFSET_);
	अगर (p && ielen > 0) अणु
		अगर ((*(p + 1 + ielen) == 0x2D) && (*(p + 2 + ielen) != 0x2D))
			/* Invalid value 0x2D is detected in Extended Supported Rates (ESR) IE. Try to fix the IE length to aव्योम failed Beacon parsing. */
			*(p + 1) = ielen - 1;
	पूर्ण

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		report_survey_event(padapter, precv_frame);
		वापस _SUCCESS;
	पूर्ण

	अगर (!स_भेद(GetAddr3Ptr(pframe), get_my_bssid(&pmlmeinfo->network), ETH_ALEN)) अणु
		अगर (pmlmeinfo->state & WIFI_FW_AUTH_शून्य) अणु
			/* we should update current network beक्रमe auth, or some IE is wrong */
			pbss = rtw_दो_स्मृति(माप(काष्ठा wlan_bssid_ex));
			अगर (pbss) अणु
				अगर (collect_bss_info(padapter, precv_frame, pbss) == _SUCCESS) अणु
					update_network(&(pmlmepriv->cur_network.network), pbss, padapter, true);
					rtw_get_bcn_info(&(pmlmepriv->cur_network));
				पूर्ण
				kमुक्त(pbss);
			पूर्ण

			/* check the venकरोr of the assoc AP */
			pmlmeinfo->assoc_AP_venकरोr = check_assoc_AP(pframe+माप(काष्ठा ieee80211_hdr_3addr), len-माप(काष्ठा ieee80211_hdr_3addr));

			/* update TSF Value */
			update_TSF(pmlmeext, pframe, len);

			/* reset क्रम adaptive_early_32k */
			pmlmeext->adaptive_tsf_करोne = false;
			pmlmeext->DrvBcnEarly = 0xff;
			pmlmeext->DrvBcnTimeOut = 0xff;
			pmlmeext->bcn_cnt = 0;
			स_रखो(pmlmeext->bcn_delay_cnt, 0, माप(pmlmeext->bcn_delay_cnt));
			स_रखो(pmlmeext->bcn_delay_ratio, 0, माप(pmlmeext->bcn_delay_ratio));

			/* start auth */
			start_clnt_auth(padapter);

			वापस _SUCCESS;
		पूर्ण

		अगर (((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE) && (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)) अणु
			psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
			अगर (psta) अणु
				ret = rtw_check_bcn_info(padapter, pframe, len);
				अगर (!ret) अणु
					netdev_dbg(padapter->pnetdev,
						   "ap has changed, disconnect now\n ");
					receive_disconnect(padapter,
							   pmlmeinfo->network.MacAddress, 0);
					वापस _SUCCESS;
				पूर्ण
				/* update WMM, ERP in the beacon */
				/* toकरो: the समयr is used instead of the number of the beacon received */
				अगर ((sta_rx_pkts(psta) & 0xf) == 0)
					update_beacon_info(padapter, pframe, len, psta);

				adaptive_early_32k(pmlmeext, pframe, len);
			पूर्ण
		पूर्ण अन्यथा अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) अणु
			psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
			अगर (psta) अणु
				/* update WMM, ERP in the beacon */
				/* toकरो: the समयr is used instead of the number of the beacon received */
				अगर ((sta_rx_pkts(psta) & 0xf) == 0) अणु
					update_beacon_info(padapter, pframe, len, psta);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* allocate a new CAM entry क्रम IBSS station */
				cam_idx = allocate_fw_sta_entry(padapter);
				अगर (cam_idx == NUM_STA)
					जाओ _END_ONBEACON_;

				/* get supported rate */
				अगर (update_sta_support_rate(padapter, (pframe + WLAN_HDR_A3_LEN + _BEACON_IE_OFFSET_), (len - WLAN_HDR_A3_LEN - _BEACON_IE_OFFSET_), cam_idx) == _FAIL) अणु
					pmlmeinfo->FW_sta_info[cam_idx].status = 0;
					जाओ _END_ONBEACON_;
				पूर्ण

				/* update TSF Value */
				update_TSF(pmlmeext, pframe, len);

				/* report sta add event */
				report_add_sta_event(padapter, GetAddr2Ptr(pframe), cam_idx);
			पूर्ण
		पूर्ण
	पूर्ण

_END_ONBEACON_:

	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक OnAuth(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक	auth_mode, seq, ie_len;
	अचिन्हित अक्षर *sa, *p;
	u16 algorithm;
	पूर्णांक	status;
	अटल काष्ठा sta_info stat;
	काष्ठा	sta_info *pstat = शून्य;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक len = precv_frame->u.hdr.len;
	u8 offset = 0;

	अगर ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		वापस _FAIL;

	sa = GetAddr2Ptr(pframe);

	auth_mode = psecuritypriv->करोt11AuthAlgrthm;

	अगर (GetPrivacy(pframe)) अणु
		u8 *iv;
		काष्ठा rx_pkt_attrib	 *prxattrib = &(precv_frame->u.hdr.attrib);

		prxattrib->hdrlen = WLAN_HDR_A3_LEN;
		prxattrib->encrypt = _WEP40_;

		iv = pframe+prxattrib->hdrlen;
		prxattrib->key_index = ((iv[3]>>6)&0x3);

		prxattrib->iv_len = 4;
		prxattrib->icv_len = 4;

		rtw_wep_decrypt(padapter, (u8 *)precv_frame);

		offset = 4;
	पूर्ण

	algorithm = le16_to_cpu(*(__le16 *)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN + offset));
	seq	= le16_to_cpu(*(__le16 *)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN + offset + 2));

	अगर (auth_mode == 2 &&
			psecuritypriv->करोt11PrivacyAlgrthm != _WEP40_ &&
			psecuritypriv->करोt11PrivacyAlgrthm != _WEP104_)
		auth_mode = 0;

	अगर ((algorithm > 0 && auth_mode == 0) ||	/*  rx a shared-key auth but shared not enabled */
		(algorithm == 0 && auth_mode == 1)) अणु	/*  rx a खोलो-प्रणाली auth but shared-key is enabled */

		status = WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;

		जाओ auth_fail;
	पूर्ण

	अगर (rtw_access_ctrl(padapter, sa) == false) अणु
		status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
		जाओ auth_fail;
	पूर्ण

	pstat = rtw_get_stainfo(pstapriv, sa);
	अगर (pstat == शून्य) अणु

		/*  allocate a new one */
		pstat = rtw_alloc_stainfo(pstapriv, sa);
		अगर (pstat == शून्य) अणु
			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
			जाओ auth_fail;
		पूर्ण

		pstat->state = WIFI_FW_AUTH_शून्य;
		pstat->auth_seq = 0;

		/* pstat->flags = 0; */
		/* pstat->capability = 0; */
	पूर्ण अन्यथा अणु

		spin_lock_bh(&pstapriv->asoc_list_lock);
		अगर (list_empty(&pstat->asoc_list) == false) अणु
			list_del_init(&pstat->asoc_list);
			pstapriv->asoc_list_cnt--;
			अगर (pstat->expire_to > 0) अणु
				/* TODO: STA re_auth within expire_to */
			पूर्ण
		पूर्ण
		spin_unlock_bh(&pstapriv->asoc_list_lock);

		अगर (seq == 1) अणु
			/* TODO: STA re_auth and auth समयout */
		पूर्ण
	पूर्ण

	spin_lock_bh(&pstapriv->auth_list_lock);
	अगर (list_empty(&pstat->auth_list)) अणु

		list_add_tail(&pstat->auth_list, &pstapriv->auth_list);
		pstapriv->auth_list_cnt++;
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	अगर (pstat->auth_seq == 0)
		pstat->expire_to = pstapriv->auth_to;


	अगर ((pstat->auth_seq + 1) != seq) अणु
		status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
		जाओ auth_fail;
	पूर्ण

	अगर (algorithm == 0 && (auth_mode == 0 || auth_mode == 2 || auth_mode == 3)) अणु
		अगर (seq == 1) अणु
			pstat->state &= ~WIFI_FW_AUTH_शून्य;
			pstat->state |= WIFI_FW_AUTH_SUCCESS;
			pstat->expire_to = pstapriv->assoc_to;
			pstat->authalg = algorithm;
		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			जाओ auth_fail;
		पूर्ण
	पूर्ण अन्यथा अणु /*  shared प्रणाली or स्वतः authentication */
		अगर (seq == 1) अणु
			/* prepare क्रम the challenging txt... */
			स_रखो((व्योम *)pstat->chg_txt, 78, 128);

			pstat->state &= ~WIFI_FW_AUTH_शून्य;
			pstat->state |= WIFI_FW_AUTH_STATE;
			pstat->authalg = algorithm;
			pstat->auth_seq = 2;
		पूर्ण अन्यथा अगर (seq == 3) अणु

			p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + 4 + _AUTH_IE_OFFSET_, WLAN_EID_CHALLENGE, (पूर्णांक *)&ie_len,
					len - WLAN_HDR_A3_LEN - _AUTH_IE_OFFSET_ - 4);

			अगर ((p == शून्य) || (ie_len <= 0)) अणु
				status = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ auth_fail;
			पूर्ण

			अगर (!स_भेद((व्योम *)(p + 2), pstat->chg_txt, 128)) अणु
				pstat->state &= (~WIFI_FW_AUTH_STATE);
				pstat->state |= WIFI_FW_AUTH_SUCCESS;
				/*  challenging txt is correct... */
				pstat->expire_to =  pstapriv->assoc_to;
			पूर्ण अन्यथा अणु
				status = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ auth_fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			जाओ auth_fail;
		पूर्ण
	पूर्ण


	/*  Now, we are going to issue_auth... */
	pstat->auth_seq = seq + 1;

	issue_auth(padapter, pstat, (अचिन्हित लघु)(WLAN_STATUS_SUCCESS));

	अगर (pstat->state & WIFI_FW_AUTH_SUCCESS)
		pstat->auth_seq = 0;


	वापस _SUCCESS;

auth_fail:

	अगर (pstat)
		rtw_मुक्त_stainfo(padapter, pstat);

	pstat = &stat;
	स_रखो((अक्षर *)pstat, '\0', माप(stat));
	pstat->auth_seq = 2;
	स_नकल(pstat->hwaddr, sa, 6);

	issue_auth(padapter, pstat, (अचिन्हित लघु)status);

	वापस _FAIL;

पूर्ण

अचिन्हित पूर्णांक OnAuthClient(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक	seq, len, status, offset;
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक	go2asoc = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक pkt_len = precv_frame->u.hdr.len;

	/* check A1 matches or not */
	अगर (स_भेद(myid(&(padapter->eeprompriv)), get_da(pframe), ETH_ALEN))
		वापस _SUCCESS;

	अगर (!(pmlmeinfo->state & WIFI_FW_AUTH_STATE))
		वापस _SUCCESS;

	offset = (GetPrivacy(pframe)) ? 4 : 0;

	seq	= le16_to_cpu(*(__le16 *)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN + offset + 2));
	status	= le16_to_cpu(*(__le16 *)((SIZE_PTR)pframe + WLAN_HDR_A3_LEN + offset + 4));

	अगर (status != 0) अणु
		अगर (status == 13) अणु /*  pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Auto) */
			अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared)
				pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Open;
			अन्यथा
				pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Shared;
			/* pmlmeinfo->reauth_count = 0; */
		पूर्ण

		set_link_समयr(pmlmeext, 1);
		जाओ authclnt_fail;
	पूर्ण

	अगर (seq == 2) अणु
		अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared) अणु
			 /*  legendary shared प्रणाली */
			p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _AUTH_IE_OFFSET_, WLAN_EID_CHALLENGE, (पूर्णांक *)&len,
				pkt_len - WLAN_HDR_A3_LEN - _AUTH_IE_OFFSET_);

			अगर (!p)
				जाओ authclnt_fail;

			स_नकल((व्योम *)(pmlmeinfo->chg_txt), (व्योम *)(p + 2), len);
			pmlmeinfo->auth_seq = 3;
			issue_auth(padapter, शून्य, 0);
			set_link_समयr(pmlmeext, REAUTH_TO);

			वापस _SUCCESS;
		पूर्ण अन्यथा अणु
			/*  खोलो प्रणाली */
			go2asoc = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (seq == 4) अणु
		अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared) अणु
			go2asoc = 1;
		पूर्ण अन्यथा अणु
			जाओ authclnt_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  this is also illegal */
		जाओ authclnt_fail;
	पूर्ण

	अगर (go2asoc) अणु
		netdev_dbg(padapter->pnetdev, "auth success, start assoc\n");
		start_clnt_assoc(padapter);
		वापस _SUCCESS;
	पूर्ण

authclnt_fail:

	/* pmlmeinfo->state &= ~(WIFI_FW_AUTH_STATE); */

	वापस _FAIL;

पूर्ण

अचिन्हित पूर्णांक OnAssocReq(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	u16 capab_info;
	काष्ठा rtw_ieee802_11_elems elems;
	काष्ठा sta_info *pstat;
	अचिन्हित अक्षर 	reassoc, *p, *pos, *wpa_ie;
	अचिन्हित अक्षर WMM_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01पूर्ण;
	पूर्णांक		i, ie_len, wpa_ie_len, left;
	अचिन्हित अक्षर 	supportRate[16];
	पूर्णांक					supportRateNum;
	अचिन्हित लघु		status = WLAN_STATUS_SUCCESS;
	अचिन्हित लघु		frame_type, ie_offset = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex	*cur = &(pmlmeinfo->network);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक pkt_len = precv_frame->u.hdr.len;

	अगर ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		वापस _FAIL;

	frame_type = GetFrameSubType(pframe);
	अगर (frame_type == WIFI_ASSOCREQ) अणु
		reassoc = 0;
		ie_offset = _ASOCREQ_IE_OFFSET_;
	पूर्ण अन्यथा अणु /*  WIFI_REASSOCREQ */
		reassoc = 1;
		ie_offset = _REASOCREQ_IE_OFFSET_;
	पूर्ण


	अगर (pkt_len < माप(काष्ठा ieee80211_hdr_3addr) + ie_offset)
		वापस _FAIL;

	pstat = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
	अगर (!pstat) अणु
		status = WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA;
		जाओ asoc_class2_error;
	पूर्ण

	capab_info = get_unaligned_le16(pframe + WLAN_HDR_A3_LEN);
	/* capab_info = le16_to_cpu(*(अचिन्हित लघु *)(pframe + WLAN_HDR_A3_LEN)); */

	left = pkt_len - (माप(काष्ठा ieee80211_hdr_3addr) + ie_offset);
	pos = pframe + (माप(काष्ठा ieee80211_hdr_3addr) + ie_offset);

	/*  check अगर this stat has been successfully authenticated/assocated */
	अगर (!((pstat->state) & WIFI_FW_AUTH_SUCCESS)) अणु
		अगर (!((pstat->state) & WIFI_FW_ASSOC_SUCCESS)) अणु
			status = WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA;
			जाओ asoc_class2_error;
		पूर्ण अन्यथा अणु
			pstat->state &= (~WIFI_FW_ASSOC_SUCCESS);
			pstat->state |= WIFI_FW_ASSOC_STATE;
		पूर्ण
	पूर्ण अन्यथा अणु
		pstat->state &= (~WIFI_FW_AUTH_SUCCESS);
		pstat->state |= WIFI_FW_ASSOC_STATE;
	पूर्ण


	pstat->capability = capab_info;

	/* now parse all ieee802_11 ie to poपूर्णांक to elems */
	अगर (rtw_ieee802_11_parse_elems(pos, left, &elems, 1) == ParseFailed ||
	    !elems.ssid) अणु
		status = WLAN_STATUS_CHALLENGE_FAIL;
		जाओ OnAssocReqFail;
	पूर्ण

	/*  now we should check all the fields... */
	/*  checking SSID */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_SSID, &ie_len,
		pkt_len - WLAN_HDR_A3_LEN - ie_offset);

	अगर (!p || ie_len == 0) अणु
		/*  broadcast ssid, however it is not allowed in assocreq */
		status = WLAN_STATUS_CHALLENGE_FAIL;
		जाओ OnAssocReqFail;
	पूर्ण अन्यथा अणु
		/*  check अगर ssid match */
		अगर (स_भेद((व्योम *)(p+2), cur->Ssid.Ssid, cur->Ssid.SsidLength))
			status = WLAN_STATUS_CHALLENGE_FAIL;

		अगर (ie_len != cur->Ssid.SsidLength)
			status = WLAN_STATUS_CHALLENGE_FAIL;
	पूर्ण

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	/*  check अगर the supported rate is ok */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_SUPP_RATES, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	अगर (p == शून्य) अणु
		/*  use our own rate set as stम_से_पn used */
		/* स_नकल(supportRate, AP_BSSRATE, AP_BSSRATE_LEN); */
		/* supportRateNum = AP_BSSRATE_LEN; */

		status = WLAN_STATUS_CHALLENGE_FAIL;
		जाओ OnAssocReqFail;
	पूर्ण अन्यथा अणु
		स_नकल(supportRate, p+2, ie_len);
		supportRateNum = ie_len;

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_EXT_SUPP_RATES, &ie_len,
				pkt_len - WLAN_HDR_A3_LEN - ie_offset);
		अगर (p !=  शून्य) अणु

			अगर (supportRateNum <= माप(supportRate)) अणु
				स_नकल(supportRate+supportRateNum, p+2, ie_len);
				supportRateNum += ie_len;
			पूर्ण
		पूर्ण
	पूर्ण

	/* toकरो: mask supportRate between AP & STA -> move to update raid */
	/* get_matched_rate(pmlmeext, supportRate, &supportRateNum, 0); */

	/* update station supportRate */
	pstat->bssratelen = supportRateNum;
	स_नकल(pstat->bssrateset, supportRate, supportRateNum);
	UpdateBrateTblForSoftAP(pstat->bssrateset, pstat->bssratelen);

	/* check RSN/WPA/WPS */
	pstat->करोt8021xalg = 0;
	pstat->wpa_psk = 0;
	pstat->wpa_group_cipher = 0;
	pstat->wpa2_group_cipher = 0;
	pstat->wpa_pairwise_cipher = 0;
	pstat->wpa2_pairwise_cipher = 0;
	स_रखो(pstat->wpa_ie, 0, माप(pstat->wpa_ie));
	अगर ((psecuritypriv->wpa_psk & BIT(1)) && elems.rsn_ie) अणु

		पूर्णांक group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.rsn_ie;
		wpa_ie_len = elems.rsn_ie_len;

		अगर (rtw_parse_wpa2_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			pstat->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			pstat->wpa_psk |= BIT(1);

			pstat->wpa2_group_cipher = group_cipher&psecuritypriv->wpa2_group_cipher;
			pstat->wpa2_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa2_pairwise_cipher;

			अगर (!pstat->wpa2_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			अगर (!pstat->wpa2_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;
		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_INVALID_IE;
		पूर्ण

	पूर्ण अन्यथा अगर ((psecuritypriv->wpa_psk & BIT(0)) && elems.wpa_ie) अणु

		पूर्णांक group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.wpa_ie;
		wpa_ie_len = elems.wpa_ie_len;

		अगर (rtw_parse_wpa_ie(wpa_ie-2, wpa_ie_len+2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			pstat->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			pstat->wpa_psk |= BIT(0);

			pstat->wpa_group_cipher = group_cipher&psecuritypriv->wpa_group_cipher;
			pstat->wpa_pairwise_cipher = pairwise_cipher&psecuritypriv->wpa_pairwise_cipher;

			अगर (!pstat->wpa_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			अगर (!pstat->wpa_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;

		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_INVALID_IE;
		पूर्ण

	पूर्ण अन्यथा अणु
		wpa_ie = शून्य;
		wpa_ie_len = 0;
	पूर्ण

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	pstat->flags &= ~(WLAN_STA_WPS | WLAN_STA_MAYBE_WPS);
	अगर (!wpa_ie) अणु
		अगर (elems.wps_ie) अणु
			pstat->flags |= WLAN_STA_WPS;
			/* wpabuf_मुक्त(sta->wps_ie); */
			/* sta->wps_ie = wpabuf_alloc_copy(elems.wps_ie + 4, */
			/* 				elems.wps_ie_len - 4); */
		पूर्ण अन्यथा अणु
			pstat->flags |= WLAN_STA_MAYBE_WPS;
		पूर्ण


		/*  AP support WPA/RSN, and sta is going to करो WPS, but AP is not पढ़ोy */
		/*  that the selected registrar of AP is _FLASE */
		अगर ((psecuritypriv->wpa_psk > 0)
			&& (pstat->flags & (WLAN_STA_WPS|WLAN_STA_MAYBE_WPS))) अणु
			अगर (pmlmepriv->wps_beacon_ie) अणु
				u8 selected_registrar = 0;

				rtw_get_wps_attr_content(pmlmepriv->wps_beacon_ie, pmlmepriv->wps_beacon_ie_len, WPS_ATTR_SELECTED_REGISTRAR, &selected_registrar, शून्य);

				अगर (!selected_registrar) अणु
					status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;

					जाओ OnAssocReqFail;
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		पूर्णांक copy_len;

		अगर (psecuritypriv->wpa_psk == 0) अणु
			status = WLAN_STATUS_INVALID_IE;

			जाओ OnAssocReqFail;

		पूर्ण

		अगर (elems.wps_ie) अणु
			pstat->flags |= WLAN_STA_WPS;
			copy_len = 0;
		पूर्ण अन्यथा अणु
			copy_len = ((wpa_ie_len+2) > माप(pstat->wpa_ie)) ? (माप(pstat->wpa_ie)):(wpa_ie_len+2);
		पूर्ण


		अगर (copy_len > 0)
			स_नकल(pstat->wpa_ie, wpa_ie-2, copy_len);

	पूर्ण


	/*  check अगर there is WMM IE & support WWM-PS */
	pstat->flags &= ~WLAN_STA_WME;
	pstat->qos_option = 0;
	pstat->qos_info = 0;
	pstat->has_legacy_ac = true;
	pstat->uapsd_vo = 0;
	pstat->uapsd_vi = 0;
	pstat->uapsd_be = 0;
	pstat->uapsd_bk = 0;
	अगर (pmlmepriv->qospriv.qos_option) अणु
		p = pframe + WLAN_HDR_A3_LEN + ie_offset; ie_len = 0;
		क्रम (;;) अणु
			p = rtw_get_ie(p, WLAN_EID_VENDOR_SPECIFIC, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
			अगर (p) अणु
				अगर (!स_भेद(p+2, WMM_IE, 6)) अणु

					pstat->flags |= WLAN_STA_WME;

					pstat->qos_option = 1;
					pstat->qos_info = *(p+8);

					pstat->max_sp_len = (pstat->qos_info>>5)&0x3;

					अगर ((pstat->qos_info&0xf) != 0xf)
						pstat->has_legacy_ac = true;
					अन्यथा
						pstat->has_legacy_ac = false;

					अगर (pstat->qos_info&0xf) अणु
						अगर (pstat->qos_info&BIT(0))
							pstat->uapsd_vo = BIT(0)|BIT(1);
						अन्यथा
							pstat->uapsd_vo = 0;

						अगर (pstat->qos_info&BIT(1))
							pstat->uapsd_vi = BIT(0)|BIT(1);
						अन्यथा
							pstat->uapsd_vi = 0;

						अगर (pstat->qos_info&BIT(2))
							pstat->uapsd_bk = BIT(0)|BIT(1);
						अन्यथा
							pstat->uapsd_bk = 0;

						अगर (pstat->qos_info&BIT(3))
							pstat->uapsd_be = BIT(0)|BIT(1);
						अन्यथा
							pstat->uapsd_be = 0;

					पूर्ण

					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
			p = p + ie_len + 2;
		पूर्ण
	पूर्ण

	/* save HT capabilities in the sta object */
	स_रखो(&pstat->htpriv.ht_cap, 0, माप(काष्ठा ieee80211_ht_cap));
	अगर (elems.ht_capabilities && elems.ht_capabilities_len >= माप(काष्ठा ieee80211_ht_cap)) अणु
		pstat->flags |= WLAN_STA_HT;

		pstat->flags |= WLAN_STA_WME;

		स_नकल(&pstat->htpriv.ht_cap, elems.ht_capabilities, माप(काष्ठा ieee80211_ht_cap));

	पूर्ण अन्यथा
		pstat->flags &= ~WLAN_STA_HT;


	अगर ((pmlmepriv->htpriv.ht_option == false) && (pstat->flags&WLAN_STA_HT)) अणु
		status = WLAN_STATUS_CHALLENGE_FAIL;
		जाओ OnAssocReqFail;
	पूर्ण


	अगर ((pstat->flags & WLAN_STA_HT) &&
		    ((pstat->wpa2_pairwise_cipher&WPA_CIPHER_TKIP) ||
		      (pstat->wpa_pairwise_cipher&WPA_CIPHER_TKIP))) अणु
		/* status = WLAN_STATUS_CIPHER_SUITE_REJECTED; */
		/* जाओ OnAssocReqFail; */
	पूर्ण
	pstat->flags |= WLAN_STA_NONERP;
	क्रम (i = 0; i < pstat->bssratelen; i++) अणु
		अगर ((pstat->bssrateset[i] & 0x7f) > 22) अणु
			pstat->flags &= ~WLAN_STA_NONERP;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pstat->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		pstat->flags |= WLAN_STA_SHORT_PREAMBLE;
	अन्यथा
		pstat->flags &= ~WLAN_STA_SHORT_PREAMBLE;



	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	/* TODO: identअगरy_proprietary_venकरोr_ie(); */
	/*  Realtek proprietary IE */
	/*  identअगरy अगर this is Broadcom sta */
	/*  identअगरy अगर this is ralink sta */
	/*  Customer proprietary IE */



	/* get a unique AID */
	अगर (pstat->aid == 0) अणु
		क्रम (pstat->aid = 1; pstat->aid <= NUM_STA; pstat->aid++)
			अगर (pstapriv->sta_aid[pstat->aid - 1] == शून्य)
				अवरोध;

		/* अगर (pstat->aid > NUM_STA) अणु */
		अगर (pstat->aid > pstapriv->max_num_sta) अणु

			pstat->aid = 0;

			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;

			जाओ OnAssocReqFail;


		पूर्ण अन्यथा अणु
			pstapriv->sta_aid[pstat->aid - 1] = pstat;
		पूर्ण
	पूर्ण


	pstat->state &= (~WIFI_FW_ASSOC_STATE);
	pstat->state |= WIFI_FW_ASSOC_SUCCESS;

	spin_lock_bh(&pstapriv->auth_list_lock);
	अगर (!list_empty(&pstat->auth_list)) अणु
		list_del_init(&pstat->auth_list);
		pstapriv->auth_list_cnt--;
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	spin_lock_bh(&pstapriv->asoc_list_lock);
	अगर (list_empty(&pstat->asoc_list)) अणु
		pstat->expire_to = pstapriv->expire_to;
		list_add_tail(&pstat->asoc_list, &pstapriv->asoc_list);
		pstapriv->asoc_list_cnt++;
	पूर्ण
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	/*  now the station is qualअगरied to join our BSS... */
	अगर (pstat && (pstat->state & WIFI_FW_ASSOC_SUCCESS) && (WLAN_STATUS_SUCCESS == status)) अणु
		/* 1 bss_cap_update & sta_info_update */
		bss_cap_update_on_sta_join(padapter, pstat);
		sta_info_update(padapter, pstat);

		/* 2 issue assoc rsp beक्रमe notअगरy station join event. */
		अगर (frame_type == WIFI_ASSOCREQ)
			issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
		अन्यथा
			issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

		spin_lock_bh(&pstat->lock);
		अगर (pstat->passoc_req) अणु
			kमुक्त(pstat->passoc_req);
			pstat->passoc_req = शून्य;
			pstat->assoc_req_len = 0;
		पूर्ण

		pstat->passoc_req =  rtw_zदो_स्मृति(pkt_len);
		अगर (pstat->passoc_req) अणु
			स_नकल(pstat->passoc_req, pframe, pkt_len);
			pstat->assoc_req_len = pkt_len;
		पूर्ण
		spin_unlock_bh(&pstat->lock);

		/* 3-(1) report sta add event */
		report_add_sta_event(padapter, pstat->hwaddr, pstat->aid);
	पूर्ण

	वापस _SUCCESS;

asoc_class2_error:

	issue_deauth(padapter, (व्योम *)GetAddr2Ptr(pframe), status);

	वापस _FAIL;

OnAssocReqFail:

	pstat->aid = 0;
	अगर (frame_type == WIFI_ASSOCREQ)
		issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
	अन्यथा
		issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

	वापस _FAIL;
पूर्ण

अचिन्हित पूर्णांक OnAssocRsp(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	uपूर्णांक i;
	पूर्णांक res;
	अचिन्हित लघु	status;
	काष्ठा ndis_80211_var_ie *pIE;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	/* काष्ठा wlan_bssid_ex			*cur_network = &(pmlmeinfo->network); */
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक pkt_len = precv_frame->u.hdr.len;

	/* check A1 matches or not */
	अगर (स_भेद(myid(&(padapter->eeprompriv)), get_da(pframe), ETH_ALEN))
		वापस _SUCCESS;

	अगर (!(pmlmeinfo->state & (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE)))
		वापस _SUCCESS;

	अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)
		वापस _SUCCESS;

	del_समयr_sync(&pmlmeext->link_समयr);

	/* status */
	status = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN + 2));
	अगर (status > 0) अणु
		pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		res = -4;
		जाओ report_assoc_result;
	पूर्ण

	/* get capabilities */
	pmlmeinfo->capability = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	/* set slot समय */
	pmlmeinfo->slotTime = (pmlmeinfo->capability & BIT(10)) ? 9 : 20;

	/* AID */
	res = pmlmeinfo->aid = (पूर्णांक)(le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN + 4))&0x3fff);

	/* following are moved to join event callback function */
	/* to handle HT, WMM, rate adaptive, update MAC reg */
	/* क्रम not to handle the synchronous IO in the tasklet */
	क्रम (i = (6 + WLAN_HDR_A3_LEN); i < pkt_len;) अणु
		pIE = (काष्ठा ndis_80211_var_ie *)(pframe + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (!स_भेद(pIE->data, WMM_PARA_OUI, 6))	/* WMM */
				WMM_param_handler(padapter, pIE);
			अवरोध;

		हाल WLAN_EID_HT_CAPABILITY:	/* HT caps */
			HT_caps_handler(padapter, pIE);
			अवरोध;

		हाल WLAN_EID_HT_OPERATION:	/* HT info */
			HT_info_handler(padapter, pIE);
			अवरोध;

		हाल WLAN_EID_ERP_INFO:
			ERP_IE_handler(padapter, pIE);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण

	pmlmeinfo->state &= (~WIFI_FW_ASSOC_STATE);
	pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;

	/* Update Basic Rate Table क्रम spec, 2010-12-28 , by thomas */
	UpdateBrateTbl(padapter, pmlmeinfo->network.SupportedRates);

report_assoc_result:
	अगर (res > 0) अणु
		rtw_buf_update(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len, pframe, pkt_len);
	पूर्ण अन्यथा अणु
		rtw_buf_मुक्त(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len);
	पूर्ण

	report_join_res(padapter, res);

	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक OnDeAuth(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित लघु	reason;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data;

	/* check A3 */
	अगर (स_भेद(GetAddr3Ptr(pframe), get_my_bssid(&pmlmeinfo->network), ETH_ALEN))
		वापस _SUCCESS;

	reason = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		/* spin_lock_bh(&(pstapriv->sta_hash_lock)); */
		/* rtw_मुक्त_stainfo(padapter, psta); */
		/* spin_unlock_bh(&(pstapriv->sta_hash_lock)); */

		netdev_dbg(padapter->pnetdev,
			   "ap recv deauth reason code(%d) sta:%pM\n", reason,
			   GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		अगर (psta) अणु
			u8 updated = false;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			अगर (list_empty(&psta->asoc_list) == false) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_मुक्त_sta(padapter, psta, false, reason);

			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update(padapter, updated);
		पूर्ण


		वापस _SUCCESS;
	पूर्ण अन्यथा अणु
		पूर्णांक	ignore_received_deauth = 0;

		/* 	Commented by Albert 20130604 */
		/* 	Beक्रमe sending the auth frame to start the STA/GC mode connection with AP/GO, */
		/* 	we will send the deauth first. */
		/* 	However, the Win8.1 with BRCM Wi-Fi will send the deauth with reason code 6 to us after receieving our deauth. */
		/* 	Added the following code to aव्योम this हाल. */
		अगर ((pmlmeinfo->state & WIFI_FW_AUTH_STATE) ||
			(pmlmeinfo->state & WIFI_FW_ASSOC_STATE)) अणु
			अगर (reason == WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA) अणु
				ignore_received_deauth = 1;
			पूर्ण अन्यथा अगर (WLAN_REASON_PREV_AUTH_NOT_VALID == reason) अणु
				/*  TODO: 802.11r */
				ignore_received_deauth = 1;
			पूर्ण
		पूर्ण

		netdev_dbg(padapter->pnetdev,
			   "sta recv deauth reason code(%d) sta:%pM, ignore = %d\n",
			   reason, GetAddr3Ptr(pframe),
			   ignore_received_deauth);

		अगर (0 == ignore_received_deauth) अणु
			receive_disconnect(padapter, GetAddr3Ptr(pframe), reason);
		पूर्ण
	पूर्ण
	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;
	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक OnDisassoc(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित लघु	reason;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data;

	/* check A3 */
	अगर (स_भेद(GetAddr3Ptr(pframe), get_my_bssid(&pmlmeinfo->network), ETH_ALEN))
		वापस _SUCCESS;

	reason = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		/* spin_lock_bh(&(pstapriv->sta_hash_lock)); */
		/* rtw_मुक्त_stainfo(padapter, psta); */
		/* spin_unlock_bh(&(pstapriv->sta_hash_lock)); */

		netdev_dbg(padapter->pnetdev,
			   "ap recv disassoc reason code(%d) sta:%pM\n",
			   reason, GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		अगर (psta) अणु
			u8 updated = false;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			अगर (list_empty(&psta->asoc_list) == false) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_मुक्त_sta(padapter, psta, false, reason);

			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update(padapter, updated);
		पूर्ण

		वापस _SUCCESS;
	पूर्ण अन्यथा अणु
		netdev_dbg(padapter->pnetdev,
			   "sta recv disassoc reason code(%d) sta:%pM\n",
			   reason, GetAddr3Ptr(pframe));

		receive_disconnect(padapter, GetAddr3Ptr(pframe), reason);
	पूर्ण
	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;
	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक OnAtim(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक on_action_spct(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = (u8 *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));
	u8 category;
	u8 action;

	psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));

	अगर (!psta)
		जाओ निकास;

	category = frame_body[0];
	अगर (category != RTW_WLAN_CATEGORY_SPECTRUM_MGMT)
		जाओ निकास;

	action = frame_body[1];
	चयन (action) अणु
	हाल WLAN_ACTION_SPCT_MSR_REQ:
	हाल WLAN_ACTION_SPCT_MSR_RPRT:
	हाल WLAN_ACTION_SPCT_TPC_REQ:
	हाल WLAN_ACTION_SPCT_TPC_RPRT:
	हाल WLAN_ACTION_SPCT_CHL_SWITCH:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

निकास:
	वापस _FAIL;
पूर्ण

अचिन्हित पूर्णांक OnAction_back(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	u8 *addr;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	अचिन्हित अक्षर 	*frame_body;
	अचिन्हित अक्षर 	category, action;
	अचिन्हित लघु	tid, status, reason_code = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 *pframe = precv_frame->u.hdr.rx_data;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	/* check RA matches or not */
	अगर (स_भेद(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))/* क्रम अगर1, sta/ap mode */
		वापस _SUCCESS;

	अगर ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		अगर (!(pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
			वापस _SUCCESS;

	addr = GetAddr2Ptr(pframe);
	psta = rtw_get_stainfo(pstapriv, addr);

	अगर (!psta)
		वापस _SUCCESS;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));

	category = frame_body[0];
	अगर (category == RTW_WLAN_CATEGORY_BACK) अणु/*  representing Block Ack */
		अगर (!pmlmeinfo->HT_enable)
			वापस _SUCCESS;

		action = frame_body[1];
		चयन (action) अणु
		हाल WLAN_ACTION_ADDBA_REQ: /* ADDBA request */

			स_नकल(&(pmlmeinfo->ADDBA_req), &(frame_body[2]), माप(काष्ठा ADDBA_request));
			/* process_addba_req(padapter, (u8 *)&(pmlmeinfo->ADDBA_req), GetAddr3Ptr(pframe)); */
			process_addba_req(padapter, (u8 *)&(pmlmeinfo->ADDBA_req), addr);

			अगर (pmlmeinfo->accept_addba_req) अणु
				issue_action_BA(padapter, addr, WLAN_ACTION_ADDBA_RESP, 0);
			पूर्ण अन्यथा अणु
				issue_action_BA(padapter, addr, WLAN_ACTION_ADDBA_RESP, 37);/* reject ADDBA Req */
			पूर्ण

			अवरोध;

		हाल WLAN_ACTION_ADDBA_RESP: /* ADDBA response */
			status = get_unaligned_le16(&frame_body[3]);
			tid = ((frame_body[5] >> 2) & 0x7);

			अगर (status == 0) अणु
				/* successful */
				psta->htpriv.agg_enable_biपंचांगap |= BIT(tid);
				psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(tid);
			पूर्ण अन्यथा अणु
				psta->htpriv.agg_enable_biपंचांगap &= ~BIT(tid);
			पूर्ण

			अगर (psta->state & WIFI_STA_ALIVE_CHK_STATE) अणु
				psta->htpriv.agg_enable_biपंचांगap &= ~BIT(tid);
				psta->expire_to = pstapriv->expire_to;
				psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
			पूर्ण

			अवरोध;

		हाल WLAN_ACTION_DELBA: /* DELBA */
			अगर ((frame_body[3] & BIT(3)) == 0) अणु
				psta->htpriv.agg_enable_biपंचांगap &=
					~BIT((frame_body[3] >> 4) & 0xf);
				psta->htpriv.candidate_tid_biपंचांगap &=
					~BIT((frame_body[3] >> 4) & 0xf);

				/* reason_code = frame_body[4] | (frame_body[5] << 8); */
				reason_code = get_unaligned_le16(&frame_body[4]);
			पूर्ण अन्यथा अगर ((frame_body[3] & BIT(3)) == BIT(3)) अणु
				tid = (frame_body[3] >> 4) & 0x0F;

				preorder_ctrl =  &psta->recvreorder_ctrl[tid];
				preorder_ctrl->enable = false;
				preorder_ctrl->indicate_seq = 0xffff;
			पूर्ण
			/* toकरो: how to notअगरy the host जबतक receiving DELETE BA */
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल s32 rtw_action_खुला_decache(जोड़ recv_frame *recv_frame, s32 token)
अणु
	काष्ठा adapter *adapter = recv_frame->u.hdr.adapter;
	काष्ठा mlme_ext_priv *mlmeext = &(adapter->mlmeextpriv);
	u8 *frame = recv_frame->u.hdr.rx_data;
	u16 seq_ctrl = ((recv_frame->u.hdr.attrib.seq_num&0xffff) << 4) |
		(recv_frame->u.hdr.attrib.frag_num & 0xf);

	अगर (GetRetry(frame)) अणु
		अगर (token >= 0) अणु
			अगर ((seq_ctrl == mlmeext->action_खुला_rxseq)
				&& (token == mlmeext->action_खुला_dialog_token))
				वापस _FAIL;
		पूर्ण अन्यथा अणु
			अगर (seq_ctrl == mlmeext->action_खुला_rxseq)
				वापस _FAIL;
		पूर्ण
	पूर्ण

	mlmeext->action_खुला_rxseq = seq_ctrl;

	अगर (token >= 0)
		mlmeext->action_खुला_dialog_token = token;

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_p2p(जोड़ recv_frame *precv_frame)
अणु
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body;
	u8 dialogToken = 0;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));

	dialogToken = frame_body[7];

	अगर (rtw_action_खुला_decache(precv_frame, dialogToken) == _FAIL)
		वापस _FAIL;

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_venकरोr(जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);

	अगर (!स_भेद(frame_body + 2, P2P_OUI, 4)) अणु
		ret = on_action_खुला_p2p(precv_frame);
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_शेष(जोड़ recv_frame *precv_frame, u8 action)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uपूर्णांक frame_len = precv_frame->u.hdr.len;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 token;
	काष्ठा adapter *adapter = precv_frame->u.hdr.adapter;
	अक्षर msg[64];

	token = frame_body[2];

	अगर (rtw_action_खुला_decache(precv_frame, token) == _FAIL)
		जाओ निकास;

	scnम_लिखो(msg, माप(msg), "%s(token:%u)", action_खुला_str(action), token);
	rtw_cfg80211_rx_action(adapter, pframe, frame_len, msg);

	ret = _SUCCESS;

निकास:
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक on_action_खुला(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 category, action;

	/* check RA matches or not */
	अगर (स_भेद(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))
		जाओ निकास;

	category = frame_body[0];
	अगर (category != RTW_WLAN_CATEGORY_PUBLIC)
		जाओ निकास;

	action = frame_body[1];
	चयन (action) अणु
	हाल ACT_PUBLIC_VENDOR:
		ret = on_action_खुला_venकरोr(precv_frame);
		अवरोध;
	शेष:
		ret = on_action_खुला_शेष(precv_frame, action);
		अवरोध;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक OnAction_ht(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 category, action;

	/* check RA matches or not */
	अगर (स_भेद(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))
		जाओ निकास;

	category = frame_body[0];
	अगर (category != RTW_WLAN_CATEGORY_HT)
		जाओ निकास;

	action = frame_body[1];
	चयन (action) अणु
	हाल WLAN_HT_ACTION_COMPRESSED_BF:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

निकास:

	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक OnAction_sa_query(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	u8 *pframe = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	अचिन्हित लघु tid;

	चयन (pframe[WLAN_HDR_A3_LEN+1]) अणु
	हाल 0: /* SA Query req */
		स_नकल(&tid, &pframe[WLAN_HDR_A3_LEN+2], माप(अचिन्हित लघु));
		issue_action_SA_Query(padapter, GetAddr2Ptr(pframe), 1, tid);
		अवरोध;

	हाल 1: /* SA Query rsp */
		del_समयr_sync(&pmlmeext->sa_query_समयr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (0) अणु
		पूर्णांक pp;

		prपूर्णांकk("pattrib->pktlen = %d =>", pattrib->pkt_len);
		क्रम (pp = 0; pp < pattrib->pkt_len; pp++)
			prपूर्णांकk(" %02x ", pframe[pp]);
		prपूर्णांकk("\n");
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक OnAction(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर category;
	काष्ठा action_handler *ptable;
	अचिन्हित अक्षर *frame_body;
	u8 *pframe = precv_frame->u.hdr.rx_data;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));

	category = frame_body[0];

	क्रम (i = 0; i < ARRAY_SIZE(OnAction_tbl); i++) अणु
		ptable = &OnAction_tbl[i];

		अगर (category == ptable->num)
			ptable->func(padapter, precv_frame);

	पूर्ण

	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक DoReserved(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल काष्ठा xmit_frame *_alloc_mgtxmitframe(काष्ठा xmit_priv *pxmitpriv, bool once)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा xmit_buf *pxmitbuf;

	अगर (once)
		pmgntframe = rtw_alloc_xmitframe_once(pxmitpriv);
	अन्यथा
		pmgntframe = rtw_alloc_xmitframe_ext(pxmitpriv);

	अगर (!pmgntframe)
		जाओ निकास;

	pxmitbuf = rtw_alloc_xmitbuf_ext(pxmitpriv);
	अगर (pxmitbuf == शून्य) अणु
		rtw_मुक्त_xmitframe(pxmitpriv, pmgntframe);
		pmgntframe = शून्य;
		जाओ निकास;
	पूर्ण

	pmgntframe->frame_tag = MGNT_FRAMETAG;
	pmgntframe->pxmitbuf = pxmitbuf;
	pmgntframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pmgntframe;

निकास:
	वापस pmgntframe;

पूर्ण

अंतरभूत काष्ठा xmit_frame *alloc_mgtxmitframe(काष्ठा xmit_priv *pxmitpriv)
अणु
	वापस _alloc_mgtxmitframe(pxmitpriv, false);
पूर्ण

/****************************************************************************

Following are some TX functions क्रम WiFi MLME

*****************************************************************************/

व्योम update_mgnt_tx_rate(काष्ठा adapter *padapter, u8 rate)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	pmlmeext->tx_rate = rate;
पूर्ण

व्योम update_mgntframe_attrib(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib)
अणु
	u8 wireless_mode;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	/* स_रखो((u8 *)(pattrib), 0, माप(काष्ठा pkt_attrib)); */

	pattrib->hdrlen = 24;
	pattrib->nr_frags = 1;
	pattrib->priority = 7;
	pattrib->mac_id = 0;
	pattrib->qsel = 0x12;

	pattrib->pktlen = 0;

	अगर (pmlmeext->tx_rate == IEEE80211_CCK_RATE_1MB)
		wireless_mode = WIRELESS_11B;
	अन्यथा
		wireless_mode = WIRELESS_11G;
	pattrib->raid =  rtw_get_mgntframe_raid(padapter, wireless_mode);
	pattrib->rate = pmlmeext->tx_rate;

	pattrib->encrypt = _NO_PRIVACY_;
	pattrib->bswenc = false;

	pattrib->qos_en = false;
	pattrib->ht_en = false;
	pattrib->bwmode = CHANNEL_WIDTH_20;
	pattrib->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pattrib->sgi = false;

	pattrib->seqnum = pmlmeext->mgnt_seq;

	pattrib->retry_ctrl = true;

	pattrib->mbssid = 0;

पूर्ण

व्योम update_mgntframe_attrib_addr(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe)
अणु
	u8 *pframe;
	काष्ठा pkt_attrib	*pattrib = &pmgntframe->attrib;

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	स_नकल(pattrib->ra, GetAddr1Ptr(pframe), ETH_ALEN);
	स_नकल(pattrib->ta, GetAddr2Ptr(pframe), ETH_ALEN);
पूर्ण

व्योम dump_mgntframe(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe)
अणु
	अगर (padapter->bSurpriseRemoved ||
		padapter->bDriverStopped) अणु
		rtw_मुक्त_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_मुक्त_xmitframe(&padapter->xmitpriv, pmgntframe);
		वापस;
	पूर्ण

	rtw_hal_mgnt_xmit(padapter, pmgntframe);
पूर्ण

s32 dump_mgntframe_and_रुको(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe, पूर्णांक समयout_ms)
अणु
	s32 ret = _FAIL;
	अचिन्हित दीर्घ irqL;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा xmit_buf *pxmitbuf = pmgntframe->pxmitbuf;
	काष्ठा submit_ctx sctx;

	अगर (padapter->bSurpriseRemoved ||
		padapter->bDriverStopped) अणु
		rtw_मुक्त_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_मुक्त_xmitframe(&padapter->xmitpriv, pmgntframe);
		वापस ret;
	पूर्ण

	rtw_sctx_init(&sctx, समयout_ms);
	pxmitbuf->sctx = &sctx;

	ret = rtw_hal_mgnt_xmit(padapter, pmgntframe);

	अगर (ret == _SUCCESS)
		ret = rtw_sctx_रुको(&sctx, __func__);

	spin_lock_irqsave(&pxmitpriv->lock_sctx, irqL);
	pxmitbuf->sctx = शून्य;
	spin_unlock_irqrestore(&pxmitpriv->lock_sctx, irqL);

	वापस ret;
पूर्ण

s32 dump_mgntframe_and_रुको_ack(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe)
अणु
	अटल u8 seq_no;
	s32 ret = _FAIL;
	u32 समयout_ms = 500;/*   500ms */
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	अगर (padapter->bSurpriseRemoved ||
		padapter->bDriverStopped) अणु
		rtw_मुक्त_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_मुक्त_xmitframe(&padapter->xmitpriv, pmgntframe);
		वापस -1;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&pxmitpriv->ack_tx_mutex) == 0) अणु
		pxmitpriv->ack_tx = true;
		pxmitpriv->seq_no = seq_no++;
		pmgntframe->ack_report = 1;
		अगर (rtw_hal_mgnt_xmit(padapter, pmgntframe) == _SUCCESS)
			ret = rtw_ack_tx_रुको(pxmitpriv, समयout_ms);

		pxmitpriv->ack_tx = false;
		mutex_unlock(&pxmitpriv->ack_tx_mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक update_hidden_ssid(u8 *ies, u32 ies_len, u8 hidden_ssid_mode)
अणु
	u8 *ssid_ie;
	चिन्हित पूर्णांक ssid_len_ori;
	पूर्णांक len_dअगरf = 0;

	ssid_ie = rtw_get_ie(ies,  WLAN_EID_SSID, &ssid_len_ori, ies_len);

	अगर (ssid_ie && ssid_len_ori > 0) अणु
		चयन (hidden_ssid_mode) अणु
		हाल 1:
		अणु
			u8 *next_ie = ssid_ie + 2 + ssid_len_ori;
			u32 reमुख्य_len = 0;

			reमुख्य_len = ies_len - (next_ie-ies);

			ssid_ie[1] = 0;
			स_नकल(ssid_ie+2, next_ie, reमुख्य_len);
			len_dअगरf -= ssid_len_ori;

			अवरोध;
		पूर्ण
		हाल 2:
			स_रखो(&ssid_ie[2], 0, ssid_len_ori);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण
	पूर्ण

	वापस len_dअगरf;
पूर्ण

व्योम issue_beacon(काष्ठा adapter *padapter, पूर्णांक समयout_ms)
अणु
	काष्ठा xmit_frame	*pmgntframe;
	काष्ठा pkt_attrib	*pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित पूर्णांक	rate_len;
	काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	spin_lock_bh(&pmlmepriv->bcn_update_lock);

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->qsel = 0x10;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;


	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	स_नकल(pwlanhdr->addr1, bc_addr, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(cur_network), ETH_ALEN);

	SetSeqNum(pwlanhdr, 0/*pmlmeext->mgnt_seq*/);
	/* pmlmeext->mgnt_seq++; */
	SetFrameSubType(pframe, WIFI_BEACON);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) अणु
		अणु
			पूर्णांक len_dअगरf;

			स_नकल(pframe, cur_network->IEs, cur_network->IELength);
			len_dअगरf = update_hidden_ssid(pframe+_BEACON_IE_OFFSET_,
						      cur_network->IELength-_BEACON_IE_OFFSET_,
						      pmlmeinfo->hidden_ssid_mode);
			pframe += (cur_network->IELength+len_dअगरf);
			pattrib->pktlen += (cur_network->IELength+len_dअगरf);
		पूर्ण

		अणु
			u8 *wps_ie;
			uपूर्णांक wps_ielen;
			u8 sr = 0;

			wps_ie = rtw_get_wps_ie(pmgntframe->buf_addr+TXDESC_OFFSET+माप(काष्ठा ieee80211_hdr_3addr)+_BEACON_IE_OFFSET_,
				pattrib->pktlen-माप(काष्ठा ieee80211_hdr_3addr)-_BEACON_IE_OFFSET_, शून्य, &wps_ielen);
			अगर (wps_ie && wps_ielen > 0) अणु
				rtw_get_wps_attr_content(wps_ie,  wps_ielen, WPS_ATTR_SELECTED_REGISTRAR, (u8 *)(&sr), शून्य);
			पूर्ण
			अगर (sr != 0)
				set_fwstate(pmlmepriv, WIFI_UNDER_WPS);
			अन्यथा
				_clr_fwstate_(pmlmepriv, WIFI_UNDER_WPS);
		पूर्ण

		जाओ _issue_bcn;

	पूर्ण

	/* below क्रम ad-hoc mode */

	/* बारtamp will be inserted by hardware */
	pframe += 8;
	pattrib->pktlen += 8;

	/*  beacon पूर्णांकerval: 2 bytes */

	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->IEs)), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/*  capability info: 2 bytes */

	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->IEs)), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/*  SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->Ssid.SsidLength, cur_network->Ssid.Ssid, &pattrib->pktlen);

	/*  supported rates... */
	rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
	pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, ((rate_len > 8) ? 8 : rate_len), cur_network->SupportedRates, &pattrib->pktlen);

	/*  DS parameter set */
	pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&(cur_network->Configuration.DSConfig), &pattrib->pktlen);

	/* अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) */
	अणु
		u8 erpinfo = 0;
		u32 ATIMWinकरोw;
		/*  IBSS Parameter Set... */
		/* ATIMWinकरोw = cur->Configuration.ATIMWinकरोw; */
		ATIMWinकरोw = 0;
		pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pattrib->pktlen);

		/* ERP IE */
		pframe = rtw_set_ie(pframe, WLAN_EID_ERP_INFO, 1, &erpinfo, &pattrib->pktlen);
	पूर्ण


	/*  EXTERNDED SUPPORTED RATE */
	अगर (rate_len > 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pattrib->pktlen);
	पूर्ण


	/* toकरो:HT क्रम adhoc */

_issue_bcn:

	pmlmepriv->update_bcn = false;

	spin_unlock_bh(&pmlmepriv->bcn_update_lock);

	अगर ((pattrib->pktlen + TXDESC_SIZE) > 512)
		वापस;

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (समयout_ms > 0)
		dump_mgntframe_and_रुको(padapter, pmgntframe, समयout_ms);
	अन्यथा
		dump_mgntframe(padapter, pmgntframe);

पूर्ण

व्योम issue_probersp(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, u8 is_valid_p2p_probereq)
अणु
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	अचिन्हित अक्षर 				*mac, *bssid;
	काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);

	u8 *pwps_ie;
	uपूर्णांक wps_ielen;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);
	अचिन्हित पूर्णांक	rate_len;

	अगर (da == शून्य)
		वापस;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	mac = myid(&(padapter->eeprompriv));
	bssid = cur_network->MacAddress;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;
	स_नकल(pwlanhdr->addr1, da, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, mac, ETH_ALEN);
	स_नकल(pwlanhdr->addr3, bssid, ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(fctrl, WIFI_PROBERSP);

	pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = pattrib->hdrlen;
	pframe += pattrib->hdrlen;


	अगर (cur_network->IELength > MAX_IE_SZ)
		वापस;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) अणु
		pwps_ie = rtw_get_wps_ie(cur_network->IEs+_FIXED_IE_LENGTH_, cur_network->IELength-_FIXED_IE_LENGTH_, शून्य, &wps_ielen);

		/* inerset & update wps_probe_resp_ie */
		अगर (pmlmepriv->wps_probe_resp_ie && pwps_ie && wps_ielen > 0) अणु
			uपूर्णांक wps_offset, reमुख्यder_ielen;
			u8 *preमुख्यder_ie;

			wps_offset = (uपूर्णांक)(pwps_ie - cur_network->IEs);

			preमुख्यder_ie = pwps_ie + wps_ielen;

			reमुख्यder_ielen = cur_network->IELength - wps_offset - wps_ielen;

			स_नकल(pframe, cur_network->IEs, wps_offset);
			pframe += wps_offset;
			pattrib->pktlen += wps_offset;

			wps_ielen = (uपूर्णांक)pmlmepriv->wps_probe_resp_ie[1];/* to get ie data len */
			अगर ((wps_offset+wps_ielen+2) <= MAX_IE_SZ) अणु
				स_नकल(pframe, pmlmepriv->wps_probe_resp_ie, wps_ielen+2);
				pframe += wps_ielen+2;
				pattrib->pktlen += wps_ielen+2;
			पूर्ण

			अगर ((wps_offset+wps_ielen+2+reमुख्यder_ielen) <= MAX_IE_SZ) अणु
				स_नकल(pframe, preमुख्यder_ie, reमुख्यder_ielen);
				pframe += reमुख्यder_ielen;
				pattrib->pktlen += reमुख्यder_ielen;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(pframe, cur_network->IEs, cur_network->IELength);
			pframe += cur_network->IELength;
			pattrib->pktlen += cur_network->IELength;
		पूर्ण

		/* retrieve SSID IE from cur_network->Ssid */
		अणु
			u8 *ssid_ie;
			चिन्हित पूर्णांक ssid_ielen;
			चिन्हित पूर्णांक ssid_ielen_dअगरf;
			u8 buf[MAX_IE_SZ];
			u8 *ies = pmgntframe->buf_addr+TXDESC_OFFSET+माप(काष्ठा ieee80211_hdr_3addr);

			ssid_ie = rtw_get_ie(ies+_FIXED_IE_LENGTH_, WLAN_EID_SSID, &ssid_ielen,
				(pframe-ies)-_FIXED_IE_LENGTH_);

			ssid_ielen_dअगरf = cur_network->Ssid.SsidLength - ssid_ielen;

			अगर (ssid_ie &&  cur_network->Ssid.SsidLength) अणु
				uपूर्णांक reमुख्यder_ielen;
				u8 *reमुख्यder_ie;

				reमुख्यder_ie = ssid_ie+2;
				reमुख्यder_ielen = (pframe-reमुख्यder_ie);

				अगर (reमुख्यder_ielen > MAX_IE_SZ) अणु
					netdev_warn(padapter->pnetdev,
						    FUNC_ADPT_FMT " remainder_ielen > MAX_IE_SZ\n",
						    FUNC_ADPT_ARG(padapter));
					reमुख्यder_ielen = MAX_IE_SZ;
				पूर्ण

				स_नकल(buf, reमुख्यder_ie, reमुख्यder_ielen);
				स_नकल(reमुख्यder_ie+ssid_ielen_dअगरf, buf, reमुख्यder_ielen);
				*(ssid_ie+1) = cur_network->Ssid.SsidLength;
				स_नकल(ssid_ie+2, cur_network->Ssid.Ssid, cur_network->Ssid.SsidLength);

				pframe += ssid_ielen_dअगरf;
				pattrib->pktlen += ssid_ielen_dअगरf;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* बारtamp will be inserted by hardware */
		pframe += 8;
		pattrib->pktlen += 8;

		/*  beacon पूर्णांकerval: 2 bytes */

		स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->IEs)), 2);

		pframe += 2;
		pattrib->pktlen += 2;

		/*  capability info: 2 bytes */

		स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->IEs)), 2);

		pframe += 2;
		pattrib->pktlen += 2;

		/* below क्रम ad-hoc mode */

		/*  SSID */
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->Ssid.SsidLength, cur_network->Ssid.Ssid, &pattrib->pktlen);

		/*  supported rates... */
		rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, ((rate_len > 8) ? 8 : rate_len), cur_network->SupportedRates, &pattrib->pktlen);

		/*  DS parameter set */
		pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&(cur_network->Configuration.DSConfig), &pattrib->pktlen);

		अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) अणु
			u8 erpinfo = 0;
			u32 ATIMWinकरोw;
			/*  IBSS Parameter Set... */
			/* ATIMWinकरोw = cur->Configuration.ATIMWinकरोw; */
			ATIMWinकरोw = 0;
			pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pattrib->pktlen);

			/* ERP IE */
			pframe = rtw_set_ie(pframe, WLAN_EID_ERP_INFO, 1, &erpinfo, &pattrib->pktlen);
		पूर्ण


		/*  EXTERNDED SUPPORTED RATE */
		अगर (rate_len > 8) अणु
			pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pattrib->pktlen);
		पूर्ण


		/* toकरो:HT क्रम adhoc */

	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;


	dump_mgntframe(padapter, pmgntframe);

	वापस;

पूर्ण

अटल पूर्णांक _issue_probereq(काष्ठा adapter *padapter,
			   काष्ठा ndis_802_11_ssid *pssid,
			   u8 *da, u8 ch, bool append_wps, bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame		*pmgntframe;
	काष्ठा pkt_attrib		*pattrib;
	अचिन्हित अक्षर 		*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	अचिन्हित अक्षर 		*mac;
	अचिन्हित अक्षर 		bssrate[NumRates];
	काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	पूर्णांक	bssrate_len = 0;
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);


	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	mac = myid(&(padapter->eeprompriv));

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	अगर (da) अणु
		/* 	unicast probe request frame */
		स_नकल(pwlanhdr->addr1, da, ETH_ALEN);
		स_नकल(pwlanhdr->addr3, da, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* 	broadcast probe request frame */
		स_नकल(pwlanhdr->addr1, bc_addr, ETH_ALEN);
		स_नकल(pwlanhdr->addr3, bc_addr, ETH_ALEN);
	पूर्ण

	स_नकल(pwlanhdr->addr2, mac, ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_PROBEREQ);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	अगर (pssid)
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, pssid->SsidLength, pssid->Ssid, &(pattrib->pktlen));
	अन्यथा
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, 0, शून्य, &(pattrib->pktlen));

	get_rate_set(padapter, bssrate, &bssrate_len);

	अगर (bssrate_len > 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, bssrate, &(pattrib->pktlen));
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (bssrate_len - 8), (bssrate + 8), &(pattrib->pktlen));
	पूर्ण अन्यथा अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, bssrate_len, bssrate, &(pattrib->pktlen));
	पूर्ण

	अगर (ch)
		pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, &ch, &pattrib->pktlen);

	अगर (append_wps) अणु
		/* add wps_ie क्रम wps2.0 */
		अगर (pmlmepriv->wps_probe_req_ie_len > 0 && pmlmepriv->wps_probe_req_ie) अणु
			स_नकल(pframe, pmlmepriv->wps_probe_req_ie, pmlmepriv->wps_probe_req_ie_len);
			pframe += pmlmepriv->wps_probe_req_ie_len;
			pattrib->pktlen += pmlmepriv->wps_probe_req_ie_len;
		पूर्ण
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अंतरभूत व्योम issue_probereq(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, u8 *da)
अणु
	_issue_probereq(padapter, pssid, da, 0, 1, false);
पूर्ण

पूर्णांक issue_probereq_ex(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, u8 *da, u8 ch, bool append_wps,
	पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;

	करो अणु
		ret = _issue_probereq(padapter, pssid, da, ch, append_wps,
				      रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);

	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		#अगर_अघोषित DBG_XMIT_ACK
		जाओ निकास;
		#पूर्ण_अगर
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/*  अगर psta == शून्य, indicate we are station(client) now... */
व्योम issue_auth(काष्ठा adapter *padapter, काष्ठा sta_info *psta, अचिन्हित लघु status)
अणु
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	अचिन्हित पूर्णांक					val32;
	अचिन्हित लघु				val16;
	पूर्णांक use_shared_key = 0;
	काष्ठा xmit_priv 		*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	__le16 le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_AUTH);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);


	अगर (psta) अणु /*  क्रम AP mode */
		स_नकल(pwlanhdr->addr1, psta->hwaddr, ETH_ALEN);
		स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
		स_नकल(pwlanhdr->addr3, myid(&(padapter->eeprompriv)), ETH_ALEN);

		/*  setting auth algo number */
		val16 = (u16)psta->authalg;

		अगर (status != WLAN_STATUS_SUCCESS)
			val16 = 0;

		अगर (val16)
			use_shared_key = 1;

		le_पंचांगp = cpu_to_le16(val16);

		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

		/*  setting auth seq number */
		val16 = (u16)psta->auth_seq;
		le_पंचांगp = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

		/*  setting status code... */
		val16 = status;
		le_पंचांगp = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

		/*  added challenging text... */
		अगर ((psta->auth_seq == 2) && (psta->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1))
			pframe = rtw_set_ie(pframe, WLAN_EID_CHALLENGE, 128, psta->chg_txt, &(pattrib->pktlen));

	पूर्ण अन्यथा अणु
		स_नकल(pwlanhdr->addr1, get_my_bssid(&pmlmeinfo->network), ETH_ALEN);
		स_नकल(pwlanhdr->addr2, myid(&padapter->eeprompriv), ETH_ALEN);
		स_नकल(pwlanhdr->addr3, get_my_bssid(&pmlmeinfo->network), ETH_ALEN);

		/*  setting auth algo number */
		val16 = (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared) ? 1 : 0;/*  0:OPEN System, 1:Shared key */
		अगर (val16) अणु
			use_shared_key = 1;
		पूर्ण
		le_पंचांगp = cpu_to_le16(val16);

		/* setting IV क्रम auth seq #3 */
		अगर ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1)) अणु
			__le32 le_पंचांगp32;

			val32 = ((pmlmeinfo->iv++) | (pmlmeinfo->key_index << 30));
			le_पंचांगp32 = cpu_to_le32(val32);
			pframe = rtw_set_fixed_ie(pframe, 4, (अचिन्हित अक्षर *)&le_पंचांगp32, &(pattrib->pktlen));

			pattrib->iv_len = 4;
		पूर्ण

		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

		/*  setting auth seq number */
		le_पंचांगp = cpu_to_le16(pmlmeinfo->auth_seq);
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));


		/*  setting status code... */
		le_पंचांगp = cpu_to_le16(status);
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

		/*  then checking to see अगर sending challenging text... */
		अगर ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1)) अणु
			pframe = rtw_set_ie(pframe, WLAN_EID_CHALLENGE, 128, pmlmeinfo->chg_txt, &(pattrib->pktlen));

			SetPrivacy(fctrl);

			pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);

			pattrib->encrypt = _WEP40_;

			pattrib->icv_len = 4;

			pattrib->pktlen += pattrib->icv_len;

		पूर्ण

	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	rtw_wep_encrypt(padapter, (u8 *)pmgntframe);
	dump_mgntframe(padapter, pmgntframe);
पूर्ण


व्योम issue_asocrsp(काष्ठा adapter *padapter, अचिन्हित लघु status, काष्ठा sta_info *pstat, पूर्णांक pkt_type)
अणु
	काष्ठा xmit_frame	*pmgntframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pbuf, *pframe;
	अचिन्हित लघु val;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *pnetwork = &(pmlmeinfo->network);
	u8 *ie = pnetwork->IEs;
	__le16 lestatus, le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);


	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	स_नकल((व्योम *)GetAddr1Ptr(pwlanhdr), pstat->hwaddr, ETH_ALEN);
	स_नकल((व्योम *)GetAddr2Ptr(pwlanhdr), myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल((व्योम *)GetAddr3Ptr(pwlanhdr), get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);


	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	अगर ((pkt_type == WIFI_ASSOCRSP) || (pkt_type == WIFI_REASSOCRSP))
		SetFrameSubType(pwlanhdr, pkt_type);
	अन्यथा
		वापस;

	pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen += pattrib->hdrlen;
	pframe += pattrib->hdrlen;

	/* capability */
	val = *(अचिन्हित लघु *)rtw_get_capability_from_ie(ie);

	pframe = rtw_set_fixed_ie(pframe, _CAPABILITY_, (अचिन्हित अक्षर *)&val, &(pattrib->pktlen));

	lestatus = cpu_to_le16(status);
	pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, (अचिन्हित अक्षर *)&lestatus, &(pattrib->pktlen));

	le_पंचांगp = cpu_to_le16(pstat->aid | BIT(14) | BIT(15));
	pframe = rtw_set_fixed_ie(pframe, _ASOC_ID_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

	अगर (pstat->bssratelen <= 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, pstat->bssratelen, pstat->bssrateset, &(pattrib->pktlen));
	पूर्ण अन्यथा अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, pstat->bssrateset, &(pattrib->pktlen));
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (pstat->bssratelen-8), pstat->bssrateset+8, &(pattrib->pktlen));
	पूर्ण

	अगर ((pstat->flags & WLAN_STA_HT) && (pmlmepriv->htpriv.ht_option)) अणु
		uपूर्णांक ie_len = 0;

		/* FILL HT CAP INFO IE */
		/* p = hostapd_eid_ht_capabilities_info(hapd, p); */
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_CAPABILITY, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_));
		अगर (pbuf && ie_len > 0) अणु
			स_नकल(pframe, pbuf, ie_len+2);
			pframe += (ie_len+2);
			pattrib->pktlen += (ie_len+2);
		पूर्ण

		/* FILL HT ADD INFO IE */
		/* p = hostapd_eid_ht_operation(hapd, p); */
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_OPERATION, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_));
		अगर (pbuf && ie_len > 0) अणु
			स_नकल(pframe, pbuf, ie_len+2);
			pframe += (ie_len+2);
			pattrib->pktlen += (ie_len+2);
		पूर्ण

	पूर्ण

	/* FILL WMM IE */
	अगर ((pstat->flags & WLAN_STA_WME) && (pmlmepriv->qospriv.qos_option)) अणु
		uपूर्णांक ie_len = 0;
		अचिन्हित अक्षर WMM_PARA_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;

		क्रम (pbuf = ie + _BEACON_IE_OFFSET_; ; pbuf += (ie_len + 2)) अणु
			pbuf = rtw_get_ie(pbuf, WLAN_EID_VENDOR_SPECIFIC, &ie_len, (pnetwork->IELength - _BEACON_IE_OFFSET_ - (ie_len + 2)));
			अगर (pbuf && !स_भेद(pbuf+2, WMM_PARA_IE, 6)) अणु
				स_नकल(pframe, pbuf, ie_len+2);
				pframe += (ie_len+2);
				pattrib->pktlen += (ie_len+2);

				अवरोध;
			पूर्ण

			अगर ((pbuf == शून्य) || (ie_len == 0)) अणु
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_REALTEK) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, 6, REALTEK_96B_IE, &(pattrib->pktlen));
	पूर्ण

	/* add WPS IE ie क्रम wps 2.0 */
	अगर (pmlmepriv->wps_assoc_resp_ie && pmlmepriv->wps_assoc_resp_ie_len > 0) अणु
		स_नकल(pframe, pmlmepriv->wps_assoc_resp_ie, pmlmepriv->wps_assoc_resp_ie_len);

		pframe += pmlmepriv->wps_assoc_resp_ie_len;
		pattrib->pktlen += pmlmepriv->wps_assoc_resp_ie_len;
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

व्योम issue_assocreq(काष्ठा adapter *padapter)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame				*pmgntframe;
	काष्ठा pkt_attrib				*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr			*pwlanhdr;
	__le16 *fctrl;
	__le16 val16;
	अचिन्हित पूर्णांक					i, j, index = 0;
	अचिन्हित अक्षर bssrate[NumRates], sta_bssrate[NumRates];
	काष्ठा ndis_80211_var_ie *pIE;
	काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	पूर्णांक	bssrate_len = 0, sta_bssrate_len = 0;
	u8 vs_ie_length = 0;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;
	स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ASSOCREQ);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	/* caps */
	स_नकल(pframe, rtw_get_capability_from_ie(pmlmeinfo->network.IEs), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/* listen पूर्णांकerval */
	/* toकरो: listen पूर्णांकerval क्रम घातer saving */
	val16 = cpu_to_le16(3);
	स_नकल(pframe, (अचिन्हित अक्षर *)&val16, 2);
	pframe += 2;
	pattrib->pktlen += 2;

	/* SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID,  pmlmeinfo->network.Ssid.SsidLength, pmlmeinfo->network.Ssid.Ssid, &(pattrib->pktlen));

	/* supported rate & extended supported rate */

	/*  Check अगर the AP's supported rates are also supported by STA. */
	get_rate_set(padapter, sta_bssrate, &sta_bssrate_len);

	अगर (pmlmeext->cur_channel == 14) /*  क्रम JAPAN, channel 14 can only uses B Mode(CCK) */
		sta_bssrate_len = 4;


	/* क्रम (i = 0; i < sta_bssrate_len; i++) अणु */
	/*  */

	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		अगर (pmlmeinfo->network.SupportedRates[i] == 0)
			अवरोध;
	पूर्ण


	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		अगर (pmlmeinfo->network.SupportedRates[i] == 0)
			अवरोध;


		/*  Check अगर the AP's supported rates are also supported by STA. */
		क्रम (j = 0; j < sta_bssrate_len; j++) अणु
			 /*  Aव्योम the proprietary data rate (22Mbps) of Handlink WSG-4000 AP */
			अगर ((pmlmeinfo->network.SupportedRates[i] | IEEE80211_BASIC_RATE_MASK)
					== (sta_bssrate[j] | IEEE80211_BASIC_RATE_MASK))
				अवरोध;
		पूर्ण

		अगर (j != sta_bssrate_len)
			/*  the rate is supported by STA */
			bssrate[index++] = pmlmeinfo->network.SupportedRates[i];
	पूर्ण

	bssrate_len = index;

	अगर (bssrate_len == 0) अणु
		rtw_मुक्त_xmitbuf(pxmitpriv, pmgntframe->pxmitbuf);
		rtw_मुक्त_xmitframe(pxmitpriv, pmgntframe);
		जाओ निकास; /* करोn't connect to AP अगर no joपूर्णांक supported rate */
	पूर्ण


	अगर (bssrate_len > 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, bssrate, &(pattrib->pktlen));
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (bssrate_len - 8), (bssrate + 8), &(pattrib->pktlen));
	पूर्ण अन्यथा
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, bssrate_len, bssrate, &(pattrib->pktlen));

	/* venकरोr specअगरic IE, such as WPA, WMM, WPS */
	क्रम (i = माप(काष्ठा ndis_802_11_fix_ie); i < pmlmeinfo->network.IELength;) अणु
		pIE = (काष्ठा ndis_80211_var_ie *)(pmlmeinfo->network.IEs + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर ((!स_भेद(pIE->data, RTW_WPA_OUI, 4)) ||
					(!स_भेद(pIE->data, WMM_OUI, 4)) ||
					(!स_भेद(pIE->data, WPS_OUI, 4))) अणु
				vs_ie_length = pIE->Length;
				अगर ((!padapter->registrypriv.wअगरi_spec) && (!स_भेद(pIE->data, WPS_OUI, 4))) अणु
					/* Commented by Kurt 20110629
					 * In some older APs, WPS handshake
					 * would be fail अगर we append venकरोr
					 * extensions inक्रमmation to AP
					 */

					vs_ie_length = 14;
				पूर्ण

				pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, vs_ie_length, pIE->data, &(pattrib->pktlen));
			पूर्ण
			अवरोध;

		हाल WLAN_EID_RSN:
			pframe = rtw_set_ie(pframe, WLAN_EID_RSN, pIE->Length, pIE->data, &(pattrib->pktlen));
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			अगर (padapter->mlmepriv.htpriv.ht_option) अणु
				अगर (!(is_ap_in_tkip(padapter))) अणु
					स_नकल(&(pmlmeinfo->HT_caps), pIE->data, माप(काष्ठा HT_caps_element));
					pframe = rtw_set_ie(pframe, WLAN_EID_HT_CAPABILITY, pIE->Length, (u8 *)(&(pmlmeinfo->HT_caps)), &(pattrib->pktlen));
				पूर्ण
			पूर्ण
			अवरोध;

		हाल WLAN_EID_EXT_CAPABILITY:
			अगर (padapter->mlmepriv.htpriv.ht_option)
				pframe = rtw_set_ie(pframe, WLAN_EID_EXT_CAPABILITY, pIE->Length, pIE->data, &(pattrib->pktlen));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_REALTEK)
		pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, 6, REALTEK_96B_IE, &(pattrib->pktlen));


	pattrib->last_txcmdsz = pattrib->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	ret = _SUCCESS;

निकास:
	अगर (ret == _SUCCESS)
		rtw_buf_update(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len, (u8 *)pwlanhdr, pattrib->pktlen);
	अन्यथा
		rtw_buf_मुक्त(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len);
पूर्ण

/* when रुको_ack is true, this function should be called at process context */
अटल पूर्णांक _issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			   अचिन्हित पूर्णांक घातer_mode, bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;

	अगर (!padapter)
		जाओ निकास;

	pxmitpriv = &(padapter->xmitpriv);
	pmlmeext = &(padapter->mlmeextpriv);
	pmlmeinfo = &(pmlmeext->mlmext_info);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
		SetFrDs(fctrl);
	अन्यथा अगर ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE)
		SetToDs(fctrl);

	अगर (घातer_mode)
		SetPwrMgt(fctrl);

	स_नकल(pwlanhdr->addr1, da, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DATA_शून्य);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/*
 * [IMPORTANT] Don't call this function in पूर्णांकerrupt context
 *
 * When रुको_ms > 0, this function should be called at process context
 * da == शून्य क्रम station mode
 */
पूर्णांक issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित पूर्णांक घातer_mode, पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा sta_info *psta;


	/* da == शून्य, assume it's null data क्रम sta to ap*/
	अगर (!da)
		da = get_my_bssid(&(pmlmeinfo->network));

	psta = rtw_get_stainfo(&padapter->stapriv, da);
	अगर (psta) अणु
		अगर (घातer_mode)
			rtw_hal_macid_sleep(padapter, psta->mac_id);
		अन्यथा
			rtw_hal_macid_wakeup(padapter, psta->mac_id);
	पूर्ण अन्यथा अणु
		rtw_warn_on(1);
	पूर्ण

	करो अणु
		ret = _issue_nulldata(padapter, da, घातer_mode, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);

	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		#अगर_अघोषित DBG_XMIT_ACK
		जाओ निकास;
		#पूर्ण_अगर
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/*
 * [IMPORTANT] This function run in पूर्णांकerrupt context
 *
 * The null data packet would be sent without घातer bit,
 * and not guarantee success.
 */
s32 issue_nulldata_in_पूर्णांकerrupt(काष्ठा adapter *padapter, u8 *da)
अणु
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;


	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	/* da == शून्य, assume it's null data क्रम sta to ap*/
	अगर (!da)
		da = get_my_bssid(&(pmlmeinfo->network));

	वापस _issue_nulldata(padapter, da, 0, false);
पूर्ण

/* when रुको_ack is true, this function should be called at process context */
अटल पूर्णांक _issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			       u16 tid, bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	u16 *qc;
	काष्ठा xmit_priv 		*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	pattrib->hdrlen += 2;
	pattrib->qos_en = true;
	pattrib->eosp = 1;
	pattrib->ack_policy = 0;
	pattrib->mdata = 0;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
		SetFrDs(fctrl);
	अन्यथा अगर ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE)
		SetToDs(fctrl);

	अगर (pattrib->mdata)
		SetMData(fctrl);

	qc = (अचिन्हित लघु *)(pframe + pattrib->hdrlen - 2);

	SetPriority(qc, tid);

	SetEOSP(qc, pattrib->eosp);

	SetAckpolicy(qc, pattrib->ack_policy);

	स_नकल(pwlanhdr->addr1, da, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_QOS_DATA_शून्य);

	pframe += माप(काष्ठा ieee80211_qos_hdr);
	pattrib->pktlen = माप(काष्ठा ieee80211_qos_hdr);

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/* when रुको_ms >0 , this function should be called at process context */
/* da == शून्य क्रम station mode */
पूर्णांक issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, u16 tid, पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	/* da == शून्य, assume it's null data क्रम sta to ap*/
	अगर (!da)
		da = get_my_bssid(&(pmlmeinfo->network));

	करो अणु
		ret = _issue_qos_nulldata(padapter, da, tid, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);

	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		#अगर_अघोषित DBG_XMIT_ACK
		जाओ निकास;
		#पूर्ण_अगर
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक _issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			 अचिन्हित लघु reason, bool रुको_ack)
अणु
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 				*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv 		*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	पूर्णांक ret = _FAIL;
	__le16 le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य) अणु
		जाओ निकास;
	पूर्ण

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	स_नकल(pwlanhdr->addr1, da, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DEAUTH);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	le_पंचांगp = cpu_to_le16(reason);
	pframe = rtw_set_fixed_ie(pframe, _RSON_CODE_, (अचिन्हित अक्षर *)&le_पंचांगp, &(pattrib->pktlen));

	pattrib->last_txcmdsz = pattrib->pktlen;


	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित लघु reason)
अणु
	वापस _issue_deauth(padapter, da, reason, false);
पूर्ण

पूर्णांक issue_deauth_ex(काष्ठा adapter *padapter, u8 *da, अचिन्हित लघु reason, पूर्णांक try_cnt,
	पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;

	करो अणु
		ret = _issue_deauth(padapter, da, reason, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			mdelay(रुको_ms);

	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		#अगर_अघोषित DBG_XMIT_ACK
		जाओ निकास;
		#पूर्ण_अगर
	पूर्ण

निकास:
	वापस ret;
पूर्ण

व्योम issue_action_SA_Query(काष्ठा adapter *padapter, अचिन्हित अक्षर *raddr, अचिन्हित अक्षर action, अचिन्हित लघु tid)
अणु
	u8 category = RTW_WLAN_CATEGORY_SA_QUERY;
	काष्ठा xmit_frame		*pmgntframe;
	काष्ठा pkt_attrib		*pattrib;
	u8 			*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	__le16 le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	अगर (raddr)
		स_नकल(pwlanhdr->addr1, raddr, ETH_ALEN);
	अन्यथा
		स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ACTION);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pframe = rtw_set_fixed_ie(pframe, 1, &category, &pattrib->pktlen);
	pframe = rtw_set_fixed_ie(pframe, 1, &action, &pattrib->pktlen);

	चयन (action) अणु
	हाल 0: /* SA Query req */
		pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)&pmlmeext->sa_query_seq, &pattrib->pktlen);
		pmlmeext->sa_query_seq++;
		/* send sa query request to AP, AP should reply sa query response in 1 second */
		set_sa_query_समयr(pmlmeext, 1000);
		अवरोध;

	हाल 1: /* SA Query rsp */
		le_पंचांगp = cpu_to_le16(tid);
		pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)&le_पंचांगp, &pattrib->pktlen);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

व्योम issue_action_BA(काष्ठा adapter *padapter, अचिन्हित अक्षर *raddr, अचिन्हित अक्षर action, अचिन्हित लघु status)
अणु
	u8 category = RTW_WLAN_CATEGORY_BACK;
	u16 start_seq;
	u16 BA_para_set;
	u16 reason_code;
	u16 BA_समयout_value;
	u16 BA_starting_seqctrl = 0;
	क्रमागत ieee80211_max_ampdu_length_exp max_rx_ampdu_factor;
	काष्ठा xmit_frame		*pmgntframe;
	काष्ठा pkt_attrib		*pattrib;
	u8 			*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा sta_info 	*psta;
	काष्ठा sta_priv 	*pstapriv = &padapter->stapriv;
	काष्ठा registry_priv 	*pregpriv = &padapter->registrypriv;
	__le16 le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	/* स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN); */
	स_नकल(pwlanhdr->addr1, raddr, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ACTION);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pframe = rtw_set_fixed_ie(pframe, 1, &(category), &(pattrib->pktlen));
	pframe = rtw_set_fixed_ie(pframe, 1, &(action), &(pattrib->pktlen));

	अगर (category == 3) अणु
		चयन (action) अणु
		हाल 0: /* ADDBA req */
			करो अणु
				pmlmeinfo->dialogToken++;
			पूर्ण जबतक (pmlmeinfo->dialogToken == 0);
			pframe = rtw_set_fixed_ie(pframe, 1, &(pmlmeinfo->dialogToken), &(pattrib->pktlen));

			अगर (hal_btcoex_IsBTCoexCtrlAMPDUSize(padapter)) अणु
				/*  A-MSDU NOT Supported */
				BA_para_set = 0;
				/*  immediate Block Ack */
				BA_para_set |= BIT(1) & IEEE80211_ADDBA_PARAM_POLICY_MASK;
				/*  TID */
				BA_para_set |= (status << 2) & IEEE80211_ADDBA_PARAM_TID_MASK;
				/*  max buffer size is 8 MSDU */
				BA_para_set |= (8 << 6) & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK;
			पूर्ण अन्यथा अणु
				BA_para_set = (0x1002 | ((status & 0xf) << 2)); /* immediate ack & 64 buffer size */
			पूर्ण
			le_पंचांगp = cpu_to_le16(BA_para_set);
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));

			BA_समयout_value = 5000;/*  5ms */
			le_पंचांगp = cpu_to_le16(BA_समयout_value);
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));

			/* अगर ((psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress)) != शून्य) */
			psta = rtw_get_stainfo(pstapriv, raddr);
			अगर (psta) अणु
				start_seq = (psta->sta_xmitpriv.txseq_tid[status & 0x07]&0xfff) + 1;

				psta->BA_starting_seqctrl[status & 0x07] = start_seq;

				BA_starting_seqctrl = start_seq << 4;
			पूर्ण

			le_पंचांगp = cpu_to_le16(BA_starting_seqctrl);
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));
			अवरोध;

		हाल 1: /* ADDBA rsp */
			pframe = rtw_set_fixed_ie(pframe, 1, &(pmlmeinfo->ADDBA_req.dialog_token), &(pattrib->pktlen));
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&status), &(pattrib->pktlen));
			अगर (padapter->driver_rx_ampdu_factor != 0xFF)
				max_rx_ampdu_factor =
				  (क्रमागत ieee80211_max_ampdu_length_exp)padapter->driver_rx_ampdu_factor;
			अन्यथा
				rtw_hal_get_def_var(padapter,
						    HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor);

			अगर (IEEE80211_HT_MAX_AMPDU_64K == max_rx_ampdu_factor)
				BA_para_set = ((le16_to_cpu(pmlmeinfo->ADDBA_req.BA_para_set) & 0x3f) | 0x1000); /* 64 buffer size */
			अन्यथा अगर (IEEE80211_HT_MAX_AMPDU_32K == max_rx_ampdu_factor)
				BA_para_set = ((le16_to_cpu(pmlmeinfo->ADDBA_req.BA_para_set) & 0x3f) | 0x0800); /* 32 buffer size */
			अन्यथा अगर (IEEE80211_HT_MAX_AMPDU_16K == max_rx_ampdu_factor)
				BA_para_set = ((le16_to_cpu(pmlmeinfo->ADDBA_req.BA_para_set) & 0x3f) | 0x0400); /* 16 buffer size */
			अन्यथा अगर (IEEE80211_HT_MAX_AMPDU_8K == max_rx_ampdu_factor)
				BA_para_set = ((le16_to_cpu(pmlmeinfo->ADDBA_req.BA_para_set) & 0x3f) | 0x0200); /* 8 buffer size */
			अन्यथा
				BA_para_set = ((le16_to_cpu(pmlmeinfo->ADDBA_req.BA_para_set) & 0x3f) | 0x1000); /* 64 buffer size */

			अगर (hal_btcoex_IsBTCoexCtrlAMPDUSize(padapter) &&
			    padapter->driver_rx_ampdu_factor == 0xFF) अणु
				/*  max buffer size is 8 MSDU */
				BA_para_set &= ~IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK;
				BA_para_set |= (8 << 6) & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK;
			पूर्ण

			अगर (pregpriv->ampdu_amsdu == 0)/* disabled */
				le_पंचांगp = cpu_to_le16(BA_para_set & ~BIT(0));
			अन्यथा अगर (pregpriv->ampdu_amsdu == 1)/* enabled */
				le_पंचांगp = cpu_to_le16(BA_para_set | BIT(0));
			अन्यथा /* स्वतः */
				le_पंचांगp = cpu_to_le16(BA_para_set);

			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(pmlmeinfo->ADDBA_req.BA_समयout_value)), &(pattrib->pktlen));
			अवरोध;
		हाल 2:/* DELBA */
			BA_para_set = (status & 0x1F) << 3;
			le_पंचांगp = cpu_to_le16(BA_para_set);
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));

			reason_code = 37;
			le_पंचांगp = cpu_to_le16(reason_code);
			pframe = rtw_set_fixed_ie(pframe, 2, (अचिन्हित अक्षर *)(&(le_पंचांगp)), &(pattrib->pktlen));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

अटल व्योम issue_action_BSSCoexistPacket(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head		*plist, *phead;
	अचिन्हित अक्षर category, action;
	काष्ठा xmit_frame			*pmgntframe;
	काष्ठा pkt_attrib			*pattrib;
	अचिन्हित अक्षर 			*pframe;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	__le16 *fctrl;
	काष्ठा	wlan_network	*pnetwork = शून्य;
	काष्ठा xmit_priv 		*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा __queue		*queue	= &(pmlmepriv->scanned_queue);
	u8 InfoContent[16] = अणु0पूर्ण;
	u8 ICS[8][15];

	अगर ((pmlmepriv->num_FortyMHzIntolerant == 0) || (pmlmepriv->num_sta_no_ht == 0))
		वापस;

	अगर (true == pmlmeinfo->bwmode_updated)
		वापस;

	category = RTW_WLAN_CATEGORY_PUBLIC;
	action = ACT_PUBLIC_BSSCOEXIST;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (pmgntframe == शून्य) अणु
		वापस;
	पूर्ण

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ACTION);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pframe = rtw_set_fixed_ie(pframe, 1, &(category), &(pattrib->pktlen));
	pframe = rtw_set_fixed_ie(pframe, 1, &(action), &(pattrib->pktlen));


	/*  */
	अगर (pmlmepriv->num_FortyMHzIntolerant > 0) अणु
		u8 iedata = 0;

		iedata |= BIT(2);/* 20 MHz BSS Width Request */

		pframe = rtw_set_ie(pframe, WLAN_EID_BSS_COEX_2040,  1, &iedata, &(pattrib->pktlen));

	पूर्ण


	/*  */
	स_रखो(ICS, 0, माप(ICS));
	अगर (pmlmepriv->num_sta_no_ht > 0) अणु
		पूर्णांक i;

		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));

		phead = get_list_head(queue);
		plist = get_next(phead);

		जबतक (1) अणु
			पूर्णांक len;
			u8 *p;
			काष्ठा wlan_bssid_ex *pbss_network;

			अगर (phead == plist)
				अवरोध;

			pnetwork = container_of(plist, काष्ठा wlan_network, list);

			plist = get_next(plist);

			pbss_network = (काष्ठा wlan_bssid_ex *)&pnetwork->network;

			p = rtw_get_ie(pbss_network->IEs + _FIXED_IE_LENGTH_, WLAN_EID_HT_CAPABILITY, &len, pbss_network->IELength - _FIXED_IE_LENGTH_);
			अगर ((p == शून्य) || (len == 0)) अणु/* non-HT */

				अगर ((pbss_network->Configuration.DSConfig <= 0) || (pbss_network->Configuration.DSConfig > 14))
					जारी;

				ICS[0][pbss_network->Configuration.DSConfig] = 1;

				अगर (ICS[0][0] == 0)
					ICS[0][0] = 1;
			पूर्ण

		पूर्ण

		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));


		क्रम (i = 0; i < 8; i++) अणु
			अगर (ICS[i][0] == 1) अणु
				पूर्णांक j, k = 0;

				InfoContent[k] = i;
				/* SET_BSS_INTOLERANT_ELE_REG_CLASS(InfoContent, i); */
				k++;

				क्रम (j = 1; j <= 14; j++) अणु
					अगर (ICS[i][j] == 1) अणु
						अगर (k < 16) अणु
							InfoContent[k] = j; /* channel number */
							/* SET_BSS_INTOLERANT_ELE_CHANNEL(InfoContent+k, j); */
							k++;
						पूर्ण
					पूर्ण
				पूर्ण

				pframe = rtw_set_ie(pframe, WLAN_EID_BSS_INTOLERANT_CHL_REPORT, k, InfoContent, &(pattrib->pktlen));

			पूर्ण

		पूर्ण


	पूर्ण


	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

अचिन्हित पूर्णांक send_delba(काष्ठा adapter *padapter, u8 initiator, u8 *addr)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;
	/* काष्ठा recv_reorder_ctrl *preorder_ctrl; */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u16 tid;

	अगर ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		अगर (!(pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
			वापस _SUCCESS;

	psta = rtw_get_stainfo(pstapriv, addr);
	अगर (psta == शून्य)
		वापस _SUCCESS;

	अगर (initiator == 0) अणु/*  recipient */
		क्रम (tid = 0; tid < MAXTID; tid++) अणु
			अगर (psta->recvreorder_ctrl[tid].enable) अणु
				issue_action_BA(padapter, addr, WLAN_ACTION_DELBA, (((tid << 1) | initiator)&0x1F));
				psta->recvreorder_ctrl[tid].enable = false;
				psta->recvreorder_ctrl[tid].indicate_seq = 0xffff;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (initiator == 1) अणु/*  originator */
		क्रम (tid = 0; tid < MAXTID; tid++) अणु
			अगर (psta->htpriv.agg_enable_biपंचांगap & BIT(tid)) अणु
				issue_action_BA(padapter, addr, WLAN_ACTION_DELBA, (((tid << 1) | initiator)&0x1F));
				psta->htpriv.agg_enable_biपंचांगap &= ~BIT(tid);
				psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(tid);

			पूर्ण
		पूर्ण
	पूर्ण

	वापस _SUCCESS;

पूर्ण

अचिन्हित पूर्णांक send_beacon(काष्ठा adapter *padapter)
अणु
	u8 bxmitok = false;
	पूर्णांक	issue = 0;
	पूर्णांक poll = 0;

	rtw_hal_set_hwreg(padapter, HW_VAR_BCN_VALID, शून्य);
	rtw_hal_set_hwreg(padapter, HW_VAR_DL_BCN_SEL, शून्य);
	करो अणु
		issue_beacon(padapter, 100);
		issue++;
		करो अणु
			cond_resched();
			rtw_hal_get_hwreg(padapter, HW_VAR_BCN_VALID, (u8 *)(&bxmitok));
			poll++;
		पूर्ण जबतक ((poll%10) != 0 && false == bxmitok && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	पूर्ण जबतक (false == bxmitok && issue < 100 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped) अणु
		वापस _FAIL;
	पूर्ण


	अगर (!bxmitok)
		वापस _FAIL;
	अन्यथा
		वापस _SUCCESS;
पूर्ण

/****************************************************************************

Following are some utility functions क्रम WiFi MLME

*****************************************************************************/

व्योम site_survey(काष्ठा adapter *padapter)
अणु
	अचिन्हित अक्षर 	survey_channel = 0, val8;
	क्रमागत rt_scan_type	ScanType = SCAN_PASSIVE;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u32 initialgain = 0;
	u32 channel_scan_समय_ms = 0;

	अणु
		काष्ठा rtw_ieee80211_channel *ch;

		अगर (pmlmeext->sitesurvey_res.channel_idx < pmlmeext->sitesurvey_res.ch_num) अणु
			ch = &pmlmeext->sitesurvey_res.ch[pmlmeext->sitesurvey_res.channel_idx];
			survey_channel = ch->hw_value;
			ScanType = (ch->flags & RTW_IEEE80211_CHAN_PASSIVE_SCAN) ? SCAN_PASSIVE : SCAN_ACTIVE;
		पूर्ण
	पूर्ण

	अगर (survey_channel != 0) अणु
		/* PAUSE 4-AC Queue when site_survey */
		/* rtw_hal_get_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		/* val8 |= 0x0f; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		अगर (pmlmeext->sitesurvey_res.channel_idx == 0) अणु
#अगर_घोषित DBG_FIXED_CHAN
			अगर (pmlmeext->fixed_chan != 0xff)
				set_channel_bwmode(padapter, pmlmeext->fixed_chan, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
			अन्यथा
#पूर्ण_अगर
				set_channel_bwmode(padapter, survey_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
		पूर्ण अन्यथा अणु
#अगर_घोषित DBG_FIXED_CHAN
			अगर (pmlmeext->fixed_chan != 0xff)
				SelectChannel(padapter, pmlmeext->fixed_chan);
			अन्यथा
#पूर्ण_अगर
				SelectChannel(padapter, survey_channel);
		पूर्ण

		अगर (ScanType == SCAN_ACTIVE) अणु /* obey the channel plan setting... */
			अणु
				पूर्णांक i;

				क्रम (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) अणु
					अगर (pmlmeext->sitesurvey_res.ssid[i].SsidLength) अणु
						/* IOT issue, When wअगरi_spec is not set, send one probe req without WPS IE. */
						अगर (padapter->registrypriv.wअगरi_spec)
							issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), शून्य);
						अन्यथा
							issue_probereq_ex(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), शून्य, 0, 0, 0, 0);
						issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), शून्य);
					पूर्ण
				पूर्ण

				अगर (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) अणु
					/* IOT issue, When wअगरi_spec is not set, send one probe req without WPS IE. */
					अगर (padapter->registrypriv.wअगरi_spec)
						issue_probereq(padapter, शून्य, शून्य);
					अन्यथा
						issue_probereq_ex(padapter, शून्य, शून्य, 0, 0, 0, 0);
					issue_probereq(padapter, शून्य, शून्य);
				पूर्ण
			पूर्ण
		पूर्ण

		channel_scan_समय_ms = pmlmeext->chan_scan_समय;

		set_survey_समयr(pmlmeext, channel_scan_समय_ms);
	पूर्ण अन्यथा अणु

		/* 	channel number is 0 or this channel is not valid. */

		अणु
			pmlmeext->sitesurvey_res.state = SCAN_COMPLETE;

			/* चयन back to the original channel */
			/* SelectChannel(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset); */

			set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

			/* flush 4-AC Queue after site_survey */
			/* val8 = 0; */
			/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */

			/* config MSR */
			Set_MSR(padapter, (pmlmeinfo->state & 0x3));

			initialgain = 0xff; /* restore RX GAIN */
			rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));
			/* turn on dynamic functions */
			Restore_DM_Func_Flag(padapter);
			/* Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true); */

			अगर (is_client_associated_to_ap(padapter))
				issue_nulldata(padapter, शून्य, 0, 3, 500);

			val8 = 0; /* survey करोne */
			rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

			report_surveyकरोne_event(padapter);

			pmlmeext->chan_scan_समय = SURVEY_TO;
			pmlmeext->sitesurvey_res.state = SCAN_DISABLE;

			issue_action_BSSCoexistPacket(padapter);
			issue_action_BSSCoexistPacket(padapter);
			issue_action_BSSCoexistPacket(padapter);
		पूर्ण
	पूर्ण

	वापस;

पूर्ण

/* collect bss info from Beacon and Probe request/response frames. */
u8 collect_bss_info(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame, काष्ठा wlan_bssid_ex *bssid)
अणु
	पूर्णांक	i;
	u32 len;
	u8 *p;
	u16 val16, subtype;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u32 packet_len = precv_frame->u.hdr.len;
	u8 ie_offset;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	__le32 le32_पंचांगp;

	len = packet_len - माप(काष्ठा ieee80211_hdr_3addr);

	अगर (len > MAX_IE_SZ)
		वापस _FAIL;

	स_रखो(bssid, 0, माप(काष्ठा wlan_bssid_ex));

	subtype = GetFrameSubType(pframe);

	अगर (subtype == WIFI_BEACON) अणु
		bssid->Reserved[0] = 1;
		ie_offset = _BEACON_IE_OFFSET_;
	पूर्ण अन्यथा अणु
		/*  FIXME : more type */
		अगर (subtype == WIFI_PROBERSP) अणु
			ie_offset = _PROBERSP_IE_OFFSET_;
			bssid->Reserved[0] = 3;
		पूर्ण अन्यथा अगर (subtype == WIFI_PROBEREQ) अणु
			ie_offset = _PROBEREQ_IE_OFFSET_;
			bssid->Reserved[0] = 2;
		पूर्ण अन्यथा अणु
			bssid->Reserved[0] = 0;
			ie_offset = _FIXED_IE_LENGTH_;
		पूर्ण
	पूर्ण

	bssid->Length = माप(काष्ठा wlan_bssid_ex) - MAX_IE_SZ + len;

	/* below is to copy the inक्रमmation element */
	bssid->IELength = len;
	स_नकल(bssid->IEs, (pframe + माप(काष्ठा ieee80211_hdr_3addr)), bssid->IELength);

	/* get the संकेत strength */
	bssid->Rssi = precv_frame->u.hdr.attrib.phy_info.RecvSignalPower; /*  in dBM.raw data */
	bssid->PhyInfo.SignalQuality = precv_frame->u.hdr.attrib.phy_info.SignalQuality;/* in percentage */
	bssid->PhyInfo.SignalStrength = precv_frame->u.hdr.attrib.phy_info.SignalStrength;/* in percentage */

	/*  checking SSID */
	p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_SSID, &len, bssid->IELength - ie_offset);
	अगर (!p)
		वापस _FAIL;

	अगर (*(p + 1)) अणु
		अगर (len > NDIS_802_11_LENGTH_SSID)
			वापस _FAIL;

		स_नकल(bssid->Ssid.Ssid, (p + 2), *(p + 1));
		bssid->Ssid.SsidLength = *(p + 1);
	पूर्ण अन्यथा
		bssid->Ssid.SsidLength = 0;

	स_रखो(bssid->SupportedRates, 0, NDIS_802_11_LENGTH_RATES_EX);

	/* checking rate info... */
	i = 0;
	p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_SUPP_RATES, &len, bssid->IELength - ie_offset);
	अगर (p) अणु
		अगर (len > NDIS_802_11_LENGTH_RATES_EX)
			वापस _FAIL;

		स_नकल(bssid->SupportedRates, (p + 2), len);
		i = len;
	पूर्ण

	p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_EXT_SUPP_RATES, &len, bssid->IELength - ie_offset);
	अगर (p) अणु
		अगर (len > (NDIS_802_11_LENGTH_RATES_EX-i))
			वापस _FAIL;

		स_नकल(bssid->SupportedRates + i, (p + 2), len);
	पूर्ण

	bssid->NetworkTypeInUse = Ndis802_11OFDM24;

	अगर (bssid->IELength < 12)
		वापस _FAIL;

	/*  Checking क्रम DSConfig */
	p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_DS_PARAMS, &len, bssid->IELength - ie_offset);

	bssid->Configuration.DSConfig = 0;
	bssid->Configuration.Length = 0;

	अगर (p) अणु
		bssid->Configuration.DSConfig = *(p + 2);
	पूर्ण अन्यथा अणु
		/*  In 5G, some ap करो not have DSSET IE */
		/*  checking HT info क्रम channel */
		p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_HT_OPERATION, &len, bssid->IELength - ie_offset);
		अगर (p) अणु
			काष्ठा HT_info_element *HT_info = (काष्ठा HT_info_element *)(p + 2);

			bssid->Configuration.DSConfig = HT_info->primary_channel;
		पूर्ण अन्यथा अणु /*  use current channel */
			bssid->Configuration.DSConfig = rtw_get_oper_ch(padapter);
		पूर्ण
	पूर्ण

	स_नकल(&le32_पंचांगp, rtw_get_beacon_पूर्णांकerval_from_ie(bssid->IEs), 2);
	bssid->Configuration.BeaconPeriod = le32_to_cpu(le32_पंचांगp);

	val16 = rtw_get_capability((काष्ठा wlan_bssid_ex *)bssid);

	अगर (val16 & BIT(0)) अणु
		bssid->Infraकाष्ठाureMode = Ndis802_11Infraकाष्ठाure;
		स_नकल(bssid->MacAddress, GetAddr2Ptr(pframe), ETH_ALEN);
	पूर्ण अन्यथा अणु
		bssid->Infraकाष्ठाureMode = Ndis802_11IBSS;
		स_नकल(bssid->MacAddress, GetAddr3Ptr(pframe), ETH_ALEN);
	पूर्ण

	अगर (val16 & BIT(4))
		bssid->Privacy = 1;
	अन्यथा
		bssid->Privacy = 0;

	bssid->Configuration.ATIMWinकरोw = 0;

	/* 20/40 BSS Coexistence check */
	अगर ((pregistrypriv->wअगरi_spec == 1) && (false == pmlmeinfo->bwmode_updated)) अणु
		काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

		p = rtw_get_ie(bssid->IEs + ie_offset, WLAN_EID_HT_CAPABILITY, &len, bssid->IELength - ie_offset);
		अगर (p && len > 0) अणु
			काष्ठा HT_caps_element	*pHT_caps;

			pHT_caps = (काष्ठा HT_caps_element	*)(p + 2);

			अगर (le16_to_cpu(pHT_caps->u.HT_cap_element.HT_caps_info) & BIT(14))
				pmlmepriv->num_FortyMHzIntolerant++;
		पूर्ण अन्यथा
			pmlmepriv->num_sta_no_ht++;
	पूर्ण

	/*  mark bss info receiving from nearby channel as SignalQuality 101 */
	अगर (bssid->Configuration.DSConfig != rtw_get_oper_ch(padapter))
		bssid->PhyInfo.SignalQuality = 101;

	वापस _SUCCESS;
पूर्ण

व्योम start_create_ibss(काष्ठा adapter *padapter)
अणु
	अचिन्हित लघु	caps;
	u8 val8;
	u8 join_type;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));

	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_पूर्णांकerval = get_beacon_पूर्णांकerval(pnetwork);

	/* update wireless mode */
	update_wireless_mode(padapter);

	/* update capability */
	caps = rtw_get_capability((काष्ठा wlan_bssid_ex *)pnetwork);
	update_capinfo(padapter, caps);
	अगर (caps&WLAN_CAPABILITY_IBSS) अणु/* adhoc master */
		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK, शून्य);

		/* चयन channel */
		/* SelectChannel(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE); */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);

		beacon_timing_control(padapter);

		/* set msr to WIFI_FW_ADHOC_STATE */
		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		/* issue beacon */
		अगर (send_beacon(padapter) == _FAIL) अणु
			report_join_res(padapter, -1);
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		पूर्ण अन्यथा अणु
			rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, padapter->registrypriv.dev_network.MacAddress);
			join_type = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

			report_join_res(padapter, 1);
			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;
			rtw_indicate_connect(padapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
	/* update bc/mc sta_info */
	update_bmc_sta(padapter);

पूर्ण

व्योम start_clnt_join(काष्ठा adapter *padapter)
अणु
	अचिन्हित लघु	caps;
	u8 val8;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));
	पूर्णांक beacon_समयout;

	/* update wireless mode */
	update_wireless_mode(padapter);

	/* update capability */
	caps = rtw_get_capability((काष्ठा wlan_bssid_ex *)pnetwork);
	update_capinfo(padapter, caps);
	अगर (caps&WLAN_CAPABILITY_ESS) अणु
		Set_MSR(padapter, WIFI_FW_STATION_STATE);

		val8 = (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_8021X) ? 0xcc : 0xcf;

		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		/*  Because of AP's not receiving deauth beक्रमe */
		/*  AP may: 1)not response auth or 2)deauth us after link is complete */
		/*  issue deauth beक्रमe issuing auth to deal with the situation */

		/* 	Commented by Albert 2012/07/21 */
		/* 	For the Win8 P2P connection, it will be hard to have a successful connection अगर this Wi-Fi करोesn't connect to it. */
		अणु
				/* To aव्योम connecting to AP fail during resume process, change retry count from 5 to 1 */
				issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, 1, 100);
		पूर्ण

		/* here रुको क्रम receiving the beacon to start auth */
		/* and enable a समयr */
		beacon_समयout = decide_रुको_क्रम_beacon_समयout(pmlmeinfo->bcn_पूर्णांकerval);
		set_link_समयr(pmlmeext, beacon_समयout);
		_set_समयr(&padapter->mlmepriv.assoc_समयr,
			(REAUTH_TO * REAUTH_LIMIT) + (REASSOC_TO*REASSOC_LIMIT) + beacon_समयout);

		pmlmeinfo->state = WIFI_FW_AUTH_शून्य | WIFI_FW_STATION_STATE;
	पूर्ण अन्यथा अगर (caps&WLAN_CAPABILITY_IBSS) अणु /* adhoc client */
		Set_MSR(padapter, WIFI_FW_ADHOC_STATE);

		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		beacon_timing_control(padapter);

		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;

		report_join_res(padapter, 1);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

पूर्ण

व्योम start_clnt_auth(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	del_समयr_sync(&pmlmeext->link_समयr);

	pmlmeinfo->state &= (~WIFI_FW_AUTH_शून्य);
	pmlmeinfo->state |= WIFI_FW_AUTH_STATE;

	pmlmeinfo->auth_seq = 1;
	pmlmeinfo->reauth_count = 0;
	pmlmeinfo->reassoc_count = 0;
	pmlmeinfo->link_count = 0;
	pmlmeext->retry = 0;


	netdev_dbg(padapter->pnetdev, "start auth\n");
	issue_auth(padapter, शून्य, 0);

	set_link_समयr(pmlmeext, REAUTH_TO);

पूर्ण


व्योम start_clnt_assoc(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	del_समयr_sync(&pmlmeext->link_समयr);

	pmlmeinfo->state &= (~(WIFI_FW_AUTH_शून्य | WIFI_FW_AUTH_STATE));
	pmlmeinfo->state |= (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE);

	issue_assocreq(padapter);

	set_link_समयr(pmlmeext, REASSOC_TO);
पूर्ण

अचिन्हित पूर्णांक receive_disconnect(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, अचिन्हित लघु reason)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	/* check A3 */
	अगर (!(!स_भेद(MacAddr, get_my_bssid(&pmlmeinfo->network), ETH_ALEN)))
		वापस _SUCCESS;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE) अणु
		अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_del_sta_event(padapter, MacAddr, reason);

		पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_LINKING_STATE) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_join_res(padapter, -2);
		पूर्ण
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल व्योम process_80211d(काष्ठा adapter *padapter, काष्ठा wlan_bssid_ex *bssid)
अणु
	काष्ठा registry_priv *pregistrypriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा rt_channel_info *chplan_new;
	u8 channel;
	u8 i;


	pregistrypriv = &padapter->registrypriv;
	pmlmeext = &padapter->mlmeextpriv;

	/*  Adjust channel plan by AP Country IE */
	अगर (pregistrypriv->enable80211d &&
		(!pmlmeext->update_channel_plan_by_ap_करोne)) अणु
		u8 *ie, *p;
		u32 len;
		काष्ठा rt_channel_plan chplan_ap;
		काष्ठा rt_channel_info chplan_sta[MAX_CHANNEL_NUM];
		u8 country[4];
		u8 fcn; /*  first channel number */
		u8 noc; /*  number of channel */
		u8 j, k;

		ie = rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_COUNTRY, &len, bssid->IELength - _FIXED_IE_LENGTH_);
		अगर (!ie)
			वापस;
		अगर (len < 6)
			वापस;

		ie += 2;
		p = ie;
		ie += len;

		स_रखो(country, 0, 4);
		स_नकल(country, p, 3);
		p += 3;

		i = 0;
		जबतक ((ie - p) >= 3) अणु
			fcn = *(p++);
			noc = *(p++);
			p++;

			क्रम (j = 0; j < noc; j++) अणु
				अगर (fcn <= 14)
					channel = fcn + j; /*  2.4 GHz */
				अन्यथा
					channel = fcn + j*4; /*  5 GHz */

				chplan_ap.Channel[i++] = channel;
			पूर्ण
		पूर्ण
		chplan_ap.Len = i;

		स_नकल(chplan_sta, pmlmeext->channel_set, माप(chplan_sta));

		स_रखो(pmlmeext->channel_set, 0, माप(pmlmeext->channel_set));
		chplan_new = pmlmeext->channel_set;

		i = j = k = 0;
		अगर (pregistrypriv->wireless_mode & WIRELESS_11G) अणु
			करो अणु
				अगर ((i == MAX_CHANNEL_NUM) ||
					(chplan_sta[i].ChannelNum == 0) ||
					(chplan_sta[i].ChannelNum > 14))
					अवरोध;

				अगर ((j == chplan_ap.Len) || (chplan_ap.Channel[j] > 14))
					अवरोध;

				अगर (chplan_sta[i].ChannelNum == chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					i++;
					j++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum < chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
/* 					chplan_new[k].ScanType = chplan_sta[i].ScanType; */
					chplan_new[k].ScanType = SCAN_PASSIVE;
					i++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum > chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					j++;
					k++;
				पूर्ण
			पूर्ण जबतक (1);

			/*  change AP not support channel to Passive scan */
			जबतक ((i < MAX_CHANNEL_NUM) &&
				(chplan_sta[i].ChannelNum != 0) &&
				(chplan_sta[i].ChannelNum <= 14)) अणु

				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
/* 				chplan_new[k].ScanType = chplan_sta[i].ScanType; */
				chplan_new[k].ScanType = SCAN_PASSIVE;
				i++;
				k++;
			पूर्ण

			/*  add channel AP supported */
			जबतक ((j < chplan_ap.Len) && (chplan_ap.Channel[j] <= 14)) अणु
				chplan_new[k].ChannelNum = chplan_ap.Channel[j];
				chplan_new[k].ScanType = SCAN_ACTIVE;
				j++;
				k++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  keep original STA 2.4G channel plan */
			जबतक ((i < MAX_CHANNEL_NUM) &&
				(chplan_sta[i].ChannelNum != 0) &&
				(chplan_sta[i].ChannelNum <= 14)) अणु
				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
				chplan_new[k].ScanType = chplan_sta[i].ScanType;
				i++;
				k++;
			पूर्ण

			/*  skip AP 2.4G channel plan */
			जबतक ((j < chplan_ap.Len) && (chplan_ap.Channel[j] <= 14)) अणु
				j++;
			पूर्ण
		पूर्ण

		अगर (pregistrypriv->wireless_mode & WIRELESS_11A) अणु
			करो अणु
				अगर ((i == MAX_CHANNEL_NUM) ||
					(chplan_sta[i].ChannelNum == 0))
					अवरोध;

				अगर ((j == chplan_ap.Len) || (chplan_ap.Channel[j] == 0))
					अवरोध;

				अगर (chplan_sta[i].ChannelNum == chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					i++;
					j++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum < chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
/* 					chplan_new[k].ScanType = chplan_sta[i].ScanType; */
					chplan_new[k].ScanType = SCAN_PASSIVE;
					i++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum > chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					j++;
					k++;
				पूर्ण
			पूर्ण जबतक (1);

			/*  change AP not support channel to Passive scan */
			जबतक ((i < MAX_CHANNEL_NUM) && (chplan_sta[i].ChannelNum != 0)) अणु
				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
/* 				chplan_new[k].ScanType = chplan_sta[i].ScanType; */
				chplan_new[k].ScanType = SCAN_PASSIVE;
				i++;
				k++;
			पूर्ण

			/*  add channel AP supported */
			जबतक ((j < chplan_ap.Len) && (chplan_ap.Channel[j] != 0)) अणु
				chplan_new[k].ChannelNum = chplan_ap.Channel[j];
				chplan_new[k].ScanType = SCAN_ACTIVE;
				j++;
				k++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  keep original STA 5G channel plan */
			जबतक ((i < MAX_CHANNEL_NUM) && (chplan_sta[i].ChannelNum != 0)) अणु
				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
				chplan_new[k].ScanType = chplan_sta[i].ScanType;
				i++;
				k++;
			पूर्ण
		पूर्ण

		pmlmeext->update_channel_plan_by_ap_करोne = 1;
	पूर्ण

	/*  If channel is used by AP, set channel scan type to active */
	channel = bssid->Configuration.DSConfig;
	chplan_new = pmlmeext->channel_set;
	i = 0;
	जबतक ((i < MAX_CHANNEL_NUM) && (chplan_new[i].ChannelNum != 0)) अणु
		अगर (chplan_new[i].ChannelNum == channel) अणु
			अगर (chplan_new[i].ScanType == SCAN_PASSIVE) अणु
				/* 5G Bnad 2, 3 (DFS) करोesn't change to active scan */
				अगर (channel >= 52 && channel <= 144)
					अवरोध;

				chplan_new[i].ScanType = SCAN_ACTIVE;
			पूर्ण
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
पूर्ण

/****************************************************************************

Following are the functions to report events

*****************************************************************************/

व्योम report_survey_event(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा survey_event	*psurvey_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा cmd_priv *pcmdpriv;
	/* u8 *pframe = precv_frame->u.hdr.rx_data; */
	/* uपूर्णांक len = precv_frame->u.hdr.len; */

	अगर (!padapter)
		वापस;

	pmlmeext = &padapter->mlmeextpriv;
	pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!pcmd_obj)
		वापस;

	cmdsz = (माप(काष्ठा survey_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा survey_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_Survey);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	psurvey_evt = (काष्ठा survey_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));

	अगर (collect_bss_info(padapter, precv_frame, (काष्ठा wlan_bssid_ex *)&psurvey_evt->bss) == _FAIL) अणु
		kमुक्त(pcmd_obj);
		kमुक्त(pevtcmd);
		वापस;
	पूर्ण

	process_80211d(padapter, &psurvey_evt->bss);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	pmlmeext->sitesurvey_res.bss_cnt++;

	वापस;

पूर्ण

व्योम report_surveyकरोne_event(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा surveyकरोne_event *psurveyकरोne_evt;
	काष्ठा C2HEvent_Header	*pc2h_evt_hdr;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!pcmd_obj)
		वापस;

	cmdsz = (माप(काष्ठा surveyकरोne_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा surveyकरोne_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_SurveyDone);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	psurveyकरोne_evt = (काष्ठा surveyकरोne_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	psurveyकरोne_evt->bss_cnt = pmlmeext->sitesurvey_res.bss_cnt;

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	वापस;

पूर्ण

व्योम report_join_res(काष्ठा adapter *padapter, पूर्णांक res)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा joinbss_event		*pjoinbss_evt;
	काष्ठा C2HEvent_Header	*pc2h_evt_hdr;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!pcmd_obj)
		वापस;

	cmdsz = (माप(काष्ठा joinbss_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा joinbss_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_JoinBss);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	pjoinbss_evt = (काष्ठा joinbss_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	स_नकल((अचिन्हित अक्षर *)(&(pjoinbss_evt->network.network)), &(pmlmeinfo->network), माप(काष्ठा wlan_bssid_ex));
	pjoinbss_evt->network.join_res	= pjoinbss_evt->network.aid = res;


	rtw_joinbss_event_prehandle(padapter, (u8 *)&pjoinbss_evt->network);


	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	वापस;

पूर्ण

व्योम report_wmm_edca_update(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा wmm_event		*pwmm_event;
	काष्ठा C2HEvent_Header	*pc2h_evt_hdr;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!pcmd_obj)
		वापस;

	cmdsz = (माप(काष्ठा wmm_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा wmm_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_WMM);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	pwmm_event = (काष्ठा wmm_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	pwmm_event->wmm = 0;

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	वापस;

पूर्ण

व्योम report_del_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, अचिन्हित लघु reason)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा sta_info *psta;
	पूर्णांक	mac_id;
	काष्ठा stadel_event			*pdel_sta_evt;
	काष्ठा C2HEvent_Header	*pc2h_evt_hdr;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (pcmd_obj == शून्य) अणु
		वापस;
	पूर्ण

	cmdsz = (माप(काष्ठा stadel_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (pevtcmd == शून्य) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा stadel_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_DelSTA);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	pdel_sta_evt = (काष्ठा stadel_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	स_नकल((अचिन्हित अक्षर *)(&(pdel_sta_evt->macaddr)), MacAddr, ETH_ALEN);
	स_नकल((अचिन्हित अक्षर *)(pdel_sta_evt->rsvd), (अचिन्हित अक्षर *)(&reason), 2);


	psta = rtw_get_stainfo(&padapter->stapriv, MacAddr);
	अगर (psta)
		mac_id = (पूर्णांक)psta->mac_id;
	अन्यथा
		mac_id = (-1);

	pdel_sta_evt->mac_id = mac_id;

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

व्योम report_add_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, पूर्णांक cam_idx)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा stassoc_event		*padd_sta_evt;
	काष्ठा C2HEvent_Header	*pc2h_evt_hdr;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (pcmd_obj == शून्य)
		वापस;

	cmdsz = (माप(काष्ठा stassoc_event) + माप(काष्ठा C2HEvent_Header));
	pevtcmd = rtw_zदो_स्मृति(cmdsz);
	अगर (pevtcmd == शून्य) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा stassoc_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_AddSTA);
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	padd_sta_evt = (काष्ठा stassoc_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	स_नकल((अचिन्हित अक्षर *)(&(padd_sta_evt->macaddr)), MacAddr, ETH_ALEN);
	padd_sta_evt->cam_id = cam_idx;

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

/****************************************************************************

Following are the event callback functions

*****************************************************************************/

/* क्रम sta/adhoc mode */
व्योम update_sta_info(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	/* ERP */
	VCS_update(padapter, psta);

	/* HT */
	अगर (pmlmepriv->htpriv.ht_option) अणु
		psta->htpriv.ht_option = true;

		psta->htpriv.ampdu_enable = pmlmepriv->htpriv.ampdu_enable;

		psta->htpriv.rx_ampdu_min_spacing = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para&IEEE80211_HT_CAP_AMPDU_DENSITY)>>2;

		अगर (support_लघु_GI(padapter, &(pmlmeinfo->HT_caps), CHANNEL_WIDTH_20))
			psta->htpriv.sgi_20m = true;

		अगर (support_लघु_GI(padapter, &(pmlmeinfo->HT_caps), CHANNEL_WIDTH_40))
			psta->htpriv.sgi_40m = true;

		psta->qos_option = true;

		psta->htpriv.ldpc_cap = pmlmepriv->htpriv.ldpc_cap;
		psta->htpriv.stbc_cap = pmlmepriv->htpriv.stbc_cap;
		psta->htpriv.beamक्रमm_cap = pmlmepriv->htpriv.beamक्रमm_cap;

		स_नकल(&psta->htpriv.ht_cap, &pmlmeinfo->HT_caps, माप(काष्ठा ieee80211_ht_cap));
	पूर्ण अन्यथा अणु
		psta->htpriv.ht_option = false;

		psta->htpriv.ampdu_enable = false;

		psta->htpriv.sgi_20m = false;
		psta->htpriv.sgi_40m = false;
		psta->qos_option = false;

	पूर्ण

	psta->htpriv.ch_offset = pmlmeext->cur_ch_offset;

	psta->htpriv.agg_enable_biपंचांगap = 0x0;/* reset */
	psta->htpriv.candidate_tid_biपंचांगap = 0x0;/* reset */

	psta->bw_mode = pmlmeext->cur_bwmode;

	/* QoS */
	अगर (pmlmepriv->qospriv.qos_option)
		psta->qos_option = true;

	update_ldpc_stbc_cap(psta);

	spin_lock_bh(&psta->lock);
	psta->state = _FW_LINKED;
	spin_unlock_bh(&psta->lock);

पूर्ण

अटल व्योम rtw_mlmeext_disconnect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));

	/* set_opmode_cmd(padapter, infra_client_with_mlme); */

	/* For safety, prevent from keeping macid sleep.
	 * If we can sure all घातer mode enter/leave are paired,
	 * this check can be हटाओd.
	 * Lucas@20131113
	 */
	/* wakeup macid after disconnect. */
	अणु
		काष्ठा sta_info *psta;

		psta = rtw_get_stainfo(&padapter->stapriv, get_my_bssid(pnetwork));
		अगर (psta)
			rtw_hal_macid_wakeup(padapter, psta->mac_id);
	पूर्ण

	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, शून्य);
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

	/* set MSR to no link state -> infra. mode */
	Set_MSR(padapter, _HW_STATE_STATION_);

	pmlmeinfo->state = WIFI_FW_शून्य_STATE;

	/* चयन to the 20M Hz mode after disconnect */
	pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	flush_all_cam_entry(padapter);

	del_समयr_sync(&pmlmeext->link_समयr);

	/* pmlmepriv->LinkDetectInfo.TrafficBusyState = false; */
	pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;
	pmlmepriv->LinkDetectInfo.LowPowerTransitionCount = 0;

पूर्ण

व्योम mlmeext_joinbss_event_callback(काष्ठा adapter *padapter, पूर्णांक join_res)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);
	काष्ठा sta_priv 	*pstapriv = &padapter->stapriv;
	u8 join_type;
	काष्ठा sta_info *psta;

	अगर (join_res < 0) अणु
		join_type = 1;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
		rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

		वापस;
	पूर्ण

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE)
		/* update bc/mc sta_info */
		update_bmc_sta(padapter);


	/* turn on dynamic functions */
	Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true);

	/*  update IOT-related issue */
	update_IOT_info(padapter);

	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, cur_network->SupportedRates);

	/* BCN पूर्णांकerval */
	rtw_hal_set_hwreg(padapter, HW_VAR_BEACON_INTERVAL, (u8 *)(&pmlmeinfo->bcn_पूर्णांकerval));

	/* update capability */
	update_capinfo(padapter, pmlmeinfo->capability);

	/* WMM, Update EDCA param */
	WMMOnAssocRsp(padapter);

	/* HT */
	HTOnAssocRsp(padapter);

	/* Set cur_channel&cur_bwmode&cur_ch_offset */
	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
	अगर (psta) अणु /* only क्रम infra. mode */

		pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

		psta->wireless_mode = pmlmeext->cur_wireless_mode;

		/* set per sta rate after updating HT cap. */
		set_sta_rate(padapter, psta);

		rtw_sta_media_status_rpt(padapter, psta, 1);

		/* wakeup macid after join bss successfully to ensure
			the subsequent data frames can be sent out normally */
		rtw_hal_macid_wakeup(padapter, psta->mac_id);
	पूर्ण

	join_type = 2;
	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE) अणु
		/*  correcting TSF */
		correct_TSF(padapter, pmlmeext);

		/* set_link_समयr(pmlmeext, DISCONNECT_TO); */
	पूर्ण

	अगर (get_अगरace_type(padapter) == IFACE_PORT0)
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_CONNECT, 0);
पूर्ण

/* currently only adhoc mode will go here */
व्योम mlmeext_sta_add_event_callback(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 join_type;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) अणु
		अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु /* adhoc master or sta_count>1 */

			/* nothing to करो */
		पूर्ण अन्यथा अणु /* adhoc client */
			/* update TSF Value */
			/* update_TSF(pmlmeext, pframe, len); */

			/*  correcting TSF */
			correct_TSF(padapter, pmlmeext);

			/* start beacon */
			अगर (send_beacon(padapter) == _FAIL) अणु
				pmlmeinfo->FW_sta_info[psta->mac_id].status = 0;

				pmlmeinfo->state ^= WIFI_FW_ADHOC_STATE;

				वापस;
			पूर्ण

			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;

		पूर्ण

		join_type = 2;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
	पूर्ण

	pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

	psta->bssratelen = rtw_get_rateset_len(pmlmeinfo->FW_sta_info[psta->mac_id].SupportedRates);
	स_नकल(psta->bssrateset, pmlmeinfo->FW_sta_info[psta->mac_id].SupportedRates, psta->bssratelen);

	/* update adhoc sta_info */
	update_sta_info(padapter, psta);

	rtw_hal_update_sta_rate_mask(padapter, psta);

	/*  ToDo: HT क्रम Ad-hoc */
	psta->wireless_mode = rtw_check_network_type(psta->bssrateset, psta->bssratelen, pmlmeext->cur_channel);
	psta->raid = networktype_to_raid_ex(padapter, psta);

	/* rate radaptive */
	Update_RA_Entry(padapter, psta);
पूर्ण

व्योम mlmeext_sta_del_event_callback(काष्ठा adapter *padapter)
अणु
	अगर (is_client_associated_to_ap(padapter) || is_IBSS_empty(padapter))
		rtw_mlmeext_disconnect(padapter);
पूर्ण

/****************************************************************************

Following are the functions क्रम the समयr handlers

*****************************************************************************/
व्योम _linked_info_dump(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा mlme_ext_priv    *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info    *pmlmeinfo = &(pmlmeext->mlmext_info);
	पूर्णांक UndecoratedSmoothedPWDB;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(padapter);

	अगर (padapter->bLinkInfoDump) अणु

		अगर ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE) अणु
			rtw_hal_get_def_var(padapter, HAL_DEF_UNDERCORATEDSMOOTHEDPWDB, &UndecoratedSmoothedPWDB);
		पूर्ण अन्यथा अगर ((pmlmeinfo->state&0x03) == _HW_STATE_AP_) अणु
			काष्ठा list_head	*phead, *plist;

			काष्ठा sta_info *psta = शून्य;
			काष्ठा sta_priv *pstapriv = &padapter->stapriv;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			phead = &pstapriv->asoc_list;
			plist = get_next(phead);
			जबतक (phead != plist) अणु
				psta = container_of(plist, काष्ठा sta_info, asoc_list);
				plist = get_next(plist);
			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);

		पूर्ण
		क्रम (i = 0; i < NUM_STA; i++) अणु
			अगर (pdvobj->macid[i]) अणु
				अगर (i != 1) /* skip bc/mc sta */
					/*   tx info ============ */
					rtw_hal_get_def_var(padapter, HW_DEF_RA_INFO_DUMP, &i);
			पूर्ण
		पूर्ण
		rtw_hal_set_def_var(padapter, HAL_DEF_DBG_RX_INFO_DUMP, शून्य);


	पूर्ण


पूर्ण

अटल u8 chk_ap_is_alive(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 ret = false;

	अगर ((sta_rx_data_pkts(psta) == sta_last_rx_data_pkts(psta))
		&& sta_rx_beacon_pkts(psta) == sta_last_rx_beacon_pkts(psta)
		&& sta_rx_probersp_pkts(psta) == sta_last_rx_probersp_pkts(psta)
	) अणु
		ret = false;
	पूर्ण अन्यथा अणु
		ret = true;
	पूर्ण

	sta_update_last_rx_pkts(psta);

	वापस ret;
पूर्ण

व्योम linked_status_chk(काष्ठा adapter *padapter)
अणु
	u32 i;
	काष्ठा sta_info 	*psta;
	काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा sta_priv 	*pstapriv = &padapter->stapriv;


	अगर (is_client_associated_to_ap(padapter)) अणु
		/* linked infraकाष्ठाure client mode */

		पूर्णांक tx_chk = _SUCCESS, rx_chk = _SUCCESS;
		पूर्णांक rx_chk_limit;
		पूर्णांक link_count_limit;

		#अगर defined(DBG_ROAMING_TEST)
		rx_chk_limit = 1;
		#अन्यथा
		rx_chk_limit = 8;
		#पूर्ण_अगर
		link_count_limit = 7; /*  16 sec */

		/*  Marked by Kurt 20130715 */
		/*  For WiDi 3.5 and latered on, they करोn't ask WiDi sink to करो roaming, so we could not check rx limit that strictly. */
		/*  toकरो: To check why we under miracast session, rx_chk would be false */
		psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress);
		अगर (psta) अणु
			अगर (chk_ap_is_alive(padapter, psta) == false)
				rx_chk = _FAIL;

			अगर (pxmitpriv->last_tx_pkts == pxmitpriv->tx_pkts)
				tx_chk = _FAIL;

			अणु
				अगर (rx_chk != _SUCCESS) अणु
					अगर (pmlmeext->retry == 0) अणु
						issue_probereq_ex(padapter, &pmlmeinfo->network.Ssid, pmlmeinfo->network.MacAddress, 0, 0, 0, 0);
						issue_probereq_ex(padapter, &pmlmeinfo->network.Ssid, pmlmeinfo->network.MacAddress, 0, 0, 0, 0);
						issue_probereq_ex(padapter, &pmlmeinfo->network.Ssid, pmlmeinfo->network.MacAddress, 0, 0, 0, 0);
					पूर्ण
				पूर्ण

				अगर (tx_chk != _SUCCESS &&
				    pmlmeinfo->link_count++ == link_count_limit)
					tx_chk = issue_nulldata_in_पूर्णांकerrupt(padapter, शून्य);
			पूर्ण

			अगर (rx_chk == _FAIL) अणु
				pmlmeext->retry++;
				अगर (pmlmeext->retry > rx_chk_limit) अणु
					netdev_dbg(padapter->pnetdev,
						   FUNC_ADPT_FMT " disconnect or roaming\n",
						   FUNC_ADPT_ARG(padapter));
					receive_disconnect(padapter, pmlmeinfo->network.MacAddress
						, WLAN_REASON_EXPIRATION_CHK);
					वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				pmlmeext->retry = 0;
			पूर्ण

			अगर (tx_chk == _FAIL) अणु
				pmlmeinfo->link_count %= (link_count_limit+1);
			पूर्ण अन्यथा अणु
				pxmitpriv->last_tx_pkts = pxmitpriv->tx_pkts;
				pmlmeinfo->link_count = 0;
			पूर्ण

		पूर्ण /* end of अगर ((psta = rtw_get_stainfo(pstapriv, passoc_res->network.MacAddress)) != शून्य) */
	पूर्ण अन्यथा अगर (is_client_associated_to_ibss(padapter)) अणु
		/* linked IBSS mode */
		/* क्रम each assoc list entry to check the rx pkt counter */
		क्रम (i = IBSS_START_MAC_ID; i < NUM_STA; i++) अणु
			अगर (pmlmeinfo->FW_sta_info[i].status == 1) अणु
				psta = pmlmeinfo->FW_sta_info[i].psta;

				अगर (शून्य == psta)
					जारी;

				अगर (pmlmeinfo->FW_sta_info[i].rx_pkt == sta_rx_pkts(psta)) अणु

					अगर (pmlmeinfo->FW_sta_info[i].retry < 3) अणु
						pmlmeinfo->FW_sta_info[i].retry++;
					पूर्ण अन्यथा अणु
						pmlmeinfo->FW_sta_info[i].retry = 0;
						pmlmeinfo->FW_sta_info[i].status = 0;
						report_del_sta_event(padapter, psta->hwaddr
							, 65535/*  indicate disconnect caused by no rx */
						);
					पूर्ण
				पूर्ण अन्यथा अणु
					pmlmeinfo->FW_sta_info[i].retry = 0;
					pmlmeinfo->FW_sta_info[i].rx_pkt = (u32)sta_rx_pkts(psta);
				पूर्ण
			पूर्ण
		पूर्ण

		/* set_link_समयr(pmlmeext, DISCONNECT_TO); */

	पूर्ण

पूर्ण

व्योम survey_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter =
		from_समयr(padapter, t, mlmeextpriv.survey_समयr);
	काष्ठा cmd_obj	*ph2c;
	काष्ठा sitesurvey_parm	*psurveyPara;
	काष्ठा cmd_priv 				*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_ext_priv 	*pmlmeext = &padapter->mlmeextpriv;

	/* issue rtw_sitesurvey_cmd */
	अगर (pmlmeext->sitesurvey_res.state > SCAN_START) अणु
		अगर (pmlmeext->sitesurvey_res.state ==  SCAN_PROCESS) अणु
			pmlmeext->sitesurvey_res.channel_idx++;
		पूर्ण

		अगर (pmlmeext->scan_पात) अणु
			pmlmeext->sitesurvey_res.channel_idx = pmlmeext->sitesurvey_res.ch_num;

			pmlmeext->scan_पात = false;/* reset */
		पूर्ण

		ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (ph2c == शून्य) अणु
			जाओ निकास_survey_समयr_hdl;
		पूर्ण

		psurveyPara = rtw_zदो_स्मृति(माप(काष्ठा sitesurvey_parm));
		अगर (psurveyPara == शून्य) अणु
			kमुक्त(ph2c);
			जाओ निकास_survey_समयr_hdl;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psurveyPara, GEN_CMD_CODE(_SiteSurvey));
		rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण


निकास_survey_समयr_hdl:

	वापस;
पूर्ण

व्योम link_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter =
		from_समयr(padapter, t, mlmeextpriv.link_समयr);
	/* अटल अचिन्हित पूर्णांक		rx_pkt = 0; */
	/* अटल u64				tx_cnt = 0; */
	/* काष्ठा xmit_priv 	*pxmitpriv = &(padapter->xmitpriv); */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	/* काष्ठा sta_priv 	*pstapriv = &padapter->stapriv; */


	अगर (pmlmeinfo->state & WIFI_FW_AUTH_शून्य) अणु
		pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		report_join_res(padapter, -3);
	पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_AUTH_STATE) अणु
		/* re-auth समयr */
		अगर (++pmlmeinfo->reauth_count > REAUTH_LIMIT) अणु
			/* अगर (pmlmeinfo->auth_algo != करोt11AuthAlgrthm_Auto) */
			/*  */
				pmlmeinfo->state = 0;
				report_join_res(padapter, -1);
				वापस;
			/*  */
			/* अन्यथा */
			/*  */
			/* 	pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Shared; */
			/* 	pmlmeinfo->reauth_count = 0; */
			/*  */
		पूर्ण

		pmlmeinfo->auth_seq = 1;
		issue_auth(padapter, शून्य, 0);
		set_link_समयr(pmlmeext, REAUTH_TO);
	पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_ASSOC_STATE) अणु
		/* re-assoc समयr */
		अगर (++pmlmeinfo->reassoc_count > REASSOC_LIMIT) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_join_res(padapter, -2);
			वापस;
		पूर्ण

		issue_assocreq(padapter);
		set_link_समयr(pmlmeext, REASSOC_TO);
	पूर्ण
पूर्ण

व्योम addba_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा sta_info *psta = from_समयr(psta, t, addba_retry_समयr);
	काष्ठा ht_priv *phtpriv;

	अगर (!psta)
		वापस;

	phtpriv = &psta->htpriv;

	अगर (phtpriv->ht_option && phtpriv->ampdu_enable) अणु
		अगर (phtpriv->candidate_tid_biपंचांगap)
			phtpriv->candidate_tid_biपंचांगap = 0x0;

	पूर्ण
पूर्ण

व्योम sa_query_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter =
		from_समयr(padapter, t, mlmeextpriv.sa_query_समयr);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	/* disconnect */
	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		rtw_disassoc_cmd(padapter, 0, true);
		rtw_indicate_disconnect(padapter);
		rtw_मुक्त_assoc_resources(padapter, 1);
	पूर्ण

	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

u8 शून्य_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	वापस H2C_SUCCESS;
पूर्ण

u8 setopmode_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 type;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा setopmode_parm *psetop = (काष्ठा setopmode_parm *)pbuf;

	अगर (psetop->mode == Ndis802_11APMode) अणु
		pmlmeinfo->state = WIFI_FW_AP_STATE;
		type = _HW_STATE_AP_;
		/* start_ap_mode(padapter); */
	पूर्ण अन्यथा अगर (psetop->mode == Ndis802_11Infraकाष्ठाure) अणु
		pmlmeinfo->state &= ~(BIT(0)|BIT(1));/*  clear state */
		pmlmeinfo->state |= WIFI_FW_STATION_STATE;/* set to	STATION_STATE */
		type = _HW_STATE_STATION_;
	पूर्ण अन्यथा अगर (psetop->mode == Ndis802_11IBSS) अणु
		type = _HW_STATE_ADHOC_;
	पूर्ण अन्यथा अणु
		type = _HW_STATE_NOLINK_;
	पूर्ण

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_OPMODE, (u8 *)(&type));
	/* Set_MSR(padapter, type); */

	अगर (psetop->mode == Ndis802_11APMode) अणु
		/*  Do this after port चयन to */
		/*  prevent from करोwnloading rsvd page to wrong port */
		rtw_btcoex_MediaStatusNotअगरy(padapter, 1); /* connect */
	पूर्ण

	वापस H2C_SUCCESS;

पूर्ण

u8 createbss_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex	*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));
	काष्ठा joinbss_parm *pparm = (काष्ठा joinbss_parm *)pbuf;
	/* u32 initialgain; */

	अगर (pmlmeinfo->state == WIFI_FW_AP_STATE) अणु
		काष्ठा wlan_bssid_ex *network = &padapter->mlmepriv.cur_network.network;

		start_bss_network(padapter, (u8 *)network);
		वापस H2C_SUCCESS;
	पूर्ण

	/* below is क्रम ad-hoc master */
	अगर (pparm->network.Infraकाष्ठाureMode == Ndis802_11IBSS) अणु
		rtw_joinbss_reset(padapter);

		pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
		pmlmeinfo->ERP_enable = 0;
		pmlmeinfo->WMM_enable = 0;
		pmlmeinfo->HT_enable = 0;
		pmlmeinfo->HT_caps_enable = 0;
		pmlmeinfo->HT_info_enable = 0;
		pmlmeinfo->agg_enable_biपंचांगap = 0;
		pmlmeinfo->candidate_tid_biपंचांगap = 0;

		/* disable dynamic functions, such as high घातer, DIG */
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false);

		/* config the initial gain under linking, need to ग_लिखो the BB रेजिस्टरs */
		/* initialgain = 0x1E; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain)); */

		/* cancel link समयr */
		del_समयr_sync(&pmlmeext->link_समयr);

		/* clear CAM */
		flush_all_cam_entry(padapter);

		स_नकल(pnetwork, pbuf, FIELD_OFFSET(काष्ठा wlan_bssid_ex, IELength));
		pnetwork->IELength = ((काष्ठा wlan_bssid_ex *)pbuf)->IELength;

		अगर (pnetwork->IELength > MAX_IE_SZ)/* Check pbuf->IELength */
			वापस H2C_PARAMETERS_ERROR;

		स_नकल(pnetwork->IEs, ((काष्ठा wlan_bssid_ex *)pbuf)->IEs, pnetwork->IELength);

		start_create_ibss(padapter);

	पूर्ण

	वापस H2C_SUCCESS;

पूर्ण

u8 join_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 join_type;
	काष्ठा ndis_80211_var_ie *pIE;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));
	u32 i;
	u8 cbw40_enable = 0;
	/* u32 initialgain; */
	/* u32 acparm; */
	u8 ch, bw, offset;

	/* check alपढ़ोy connecting to AP or not */
	अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु
		अगर (pmlmeinfo->state & WIFI_FW_STATION_STATE) अणु
			issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, 1, 100);
		पूर्ण
		pmlmeinfo->state = WIFI_FW_शून्य_STATE;

		/* clear CAM */
		flush_all_cam_entry(padapter);

		del_समयr_sync(&pmlmeext->link_समयr);

		/* set MSR to nolink -> infra. mode */
		/* Set_MSR(padapter, _HW_STATE_NOLINK_); */
		Set_MSR(padapter, _HW_STATE_STATION_);


		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, शून्य);
	पूर्ण

	rtw_joinbss_reset(padapter);

	pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pmlmeinfo->ERP_enable = 0;
	pmlmeinfo->WMM_enable = 0;
	pmlmeinfo->HT_enable = 0;
	pmlmeinfo->HT_caps_enable = 0;
	pmlmeinfo->HT_info_enable = 0;
	pmlmeinfo->agg_enable_biपंचांगap = 0;
	pmlmeinfo->candidate_tid_biपंचांगap = 0;
	pmlmeinfo->bwmode_updated = false;
	/* pmlmeinfo->assoc_AP_venकरोr = HT_IOT_PEER_MAX; */
	pmlmeinfo->VHT_enable = 0;

	स_नकल(pnetwork, pbuf, FIELD_OFFSET(काष्ठा wlan_bssid_ex, IELength));
	pnetwork->IELength = ((काष्ठा wlan_bssid_ex *)pbuf)->IELength;

	अगर (pnetwork->IELength > MAX_IE_SZ)/* Check pbuf->IELength */
		वापस H2C_PARAMETERS_ERROR;

	स_नकल(pnetwork->IEs, ((काष्ठा wlan_bssid_ex *)pbuf)->IEs, pnetwork->IELength);

	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_पूर्णांकerval = get_beacon_पूर्णांकerval(pnetwork);

	/* Check AP venकरोr to move rtw_joinbss_cmd() */
	/* pmlmeinfo->assoc_AP_venकरोr = check_assoc_AP(pnetwork->IEs, pnetwork->IELength); */

	/* माप(काष्ठा ndis_802_11_fix_ie) */
	क्रम (i = _FIXED_IE_LENGTH_; i < pnetwork->IELength;) अणु
		pIE = (काष्ठा ndis_80211_var_ie *)(pnetwork->IEs + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:/* Get WMM IE. */
			अगर (!स_भेद(pIE->data, WMM_OUI, 4))
				WMM_param_handler(padapter, pIE);
			अवरोध;

		हाल WLAN_EID_HT_CAPABILITY:	/* Get HT Cap IE. */
			pmlmeinfo->HT_caps_enable = 1;
			अवरोध;

		हाल WLAN_EID_HT_OPERATION:	/* Get HT Info IE. */
			pmlmeinfo->HT_info_enable = 1;

			/* spec हाल only क्रम cisco's ap because cisco's ap issue assoc rsp using mcs rate @40MHz or @20MHz */
			अणु
				काष्ठा HT_info_element *pht_info = (काष्ठा HT_info_element *)(pIE->data);

				अगर (pnetwork->Configuration.DSConfig > 14) अणु
					अगर ((pregpriv->bw_mode >> 4) > CHANNEL_WIDTH_20)
						cbw40_enable = 1;
				पूर्ण अन्यथा अणु
					अगर ((pregpriv->bw_mode & 0x0f) > CHANNEL_WIDTH_20)
						cbw40_enable = 1;
				पूर्ण

				अगर ((cbw40_enable) && (pht_info->infos[0] & BIT(2))) अणु
					/* चयन to the 40M Hz mode according to the AP */
					pmlmeext->cur_bwmode = CHANNEL_WIDTH_40;
					चयन (pht_info->infos[0] & 0x3) अणु
					हाल 1:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
						अवरोध;

					हाल 3:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
						अवरोध;

					शेष:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
						pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण

	/* check channel, bandwidth, offset and चयन */
	अगर (rtw_chk_start_clnt_join(padapter, &ch, &bw, &offset) == _FAIL) अणु
		report_join_res(padapter, (-4));
		वापस H2C_SUCCESS;
	पूर्ण

	/* disable dynamic functions, such as high घातer, DIG */
	/* Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false); */

	/* config the initial gain under linking, need to ग_लिखो the BB रेजिस्टरs */
	/* initialgain = 0x1E; */
	/* rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain)); */

	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pmlmeinfo->network.MacAddress);
	join_type = 0;
	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
	rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK, शून्य);

	set_channel_bwmode(padapter, ch, offset, bw);

	/* cancel link समयr */
	del_समयr_sync(&pmlmeext->link_समयr);

	start_clnt_join(padapter);

	वापस H2C_SUCCESS;

पूर्ण

u8 disconnect_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा disconnect_parm *param = (काष्ठा disconnect_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));
	u8 val8;

	अगर (is_client_associated_to_ap(padapter)) अणु
			issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, param->deauth_समयout_ms/100, 100);
	पूर्ण

	अगर (((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)) अणु
		/* Stop BCN */
		val8 = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_BCN_FUNC, (u8 *)(&val8));
	पूर्ण

	rtw_mlmeext_disconnect(padapter);

	rtw_मुक्त_uc_swdec_pending_queue(padapter);

	वापस	H2C_SUCCESS;
पूर्ण

अटल पूर्णांक rtw_scan_ch_decision(काष्ठा adapter *padapter, काष्ठा rtw_ieee80211_channel *out,
	u32 out_num, काष्ठा rtw_ieee80211_channel *in, u32 in_num)
अणु
	पूर्णांक i, j;
	पूर्णांक set_idx;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	/* clear first */
	स_रखो(out, 0, माप(काष्ठा rtw_ieee80211_channel)*out_num);

	/* acquire channels from in */
	j = 0;
	क्रम (i = 0; i < in_num; i++) अणु

		set_idx = rtw_ch_set_search_ch(pmlmeext->channel_set, in[i].hw_value);
		अगर (in[i].hw_value && !(in[i].flags & RTW_IEEE80211_CHAN_DISABLED)
			&& set_idx >= 0
			&& rtw_mlme_band_check(padapter, in[i].hw_value)
		) अणु
			अगर (j >= out_num) अणु
				netdev_dbg(padapter->pnetdev,
					   FUNC_ADPT_FMT " out_num:%u not enough\n",
					   FUNC_ADPT_ARG(padapter), out_num);
				अवरोध;
			पूर्ण

			स_नकल(&out[j], &in[i], माप(काष्ठा rtw_ieee80211_channel));

			अगर (pmlmeext->channel_set[set_idx].ScanType == SCAN_PASSIVE)
				out[j].flags |= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

			j++;
		पूर्ण
		अगर (j >= out_num)
			अवरोध;
	पूर्ण

	/* अगर out is empty, use channel_set as शेष */
	अगर (j == 0) अणु
		क्रम (i = 0; i < pmlmeext->max_chan_nums; i++) अणु

			अगर (rtw_mlme_band_check(padapter, pmlmeext->channel_set[i].ChannelNum)) अणु

				अगर (j >= out_num) अणु
					netdev_dbg(padapter->pnetdev,
						   FUNC_ADPT_FMT " out_num:%u not enough\n",
						   FUNC_ADPT_ARG(padapter),
						   out_num);
					अवरोध;
				पूर्ण

				out[j].hw_value = pmlmeext->channel_set[i].ChannelNum;

				अगर (pmlmeext->channel_set[i].ScanType == SCAN_PASSIVE)
					out[j].flags |= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

				j++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस j;
पूर्ण

u8 sitesurvey_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा sitesurvey_parm	*pparm = (काष्ठा sitesurvey_parm *)pbuf;
	u8 bdelayscan = false;
	u8 val8;
	u32 initialgain;
	u32 i;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_DISABLE) अणु
		pmlmeext->sitesurvey_res.state = SCAN_START;
		pmlmeext->sitesurvey_res.bss_cnt = 0;
		pmlmeext->sitesurvey_res.channel_idx = 0;

		क्रम (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) अणु
			अगर (pparm->ssid[i].SsidLength) अणु
				स_नकल(pmlmeext->sitesurvey_res.ssid[i].Ssid, pparm->ssid[i].Ssid, IW_ESSID_MAX_SIZE);
				pmlmeext->sitesurvey_res.ssid[i].SsidLength = pparm->ssid[i].SsidLength;
			पूर्ण अन्यथा अणु
				pmlmeext->sitesurvey_res.ssid[i].SsidLength = 0;
			पूर्ण
		पूर्ण

		pmlmeext->sitesurvey_res.ch_num = rtw_scan_ch_decision(padapter
			, pmlmeext->sitesurvey_res.ch, RTW_CHANNEL_SCAN_AMOUNT
			, pparm->ch, pparm->ch_num
		);

		pmlmeext->sitesurvey_res.scan_mode = pparm->scan_mode;

		/* issue null data अगर associating to the AP */
		अगर (is_client_associated_to_ap(padapter)) अणु
			pmlmeext->sitesurvey_res.state = SCAN_TXशून्य;

			issue_nulldata(padapter, शून्य, 1, 3, 500);

			bdelayscan = true;
		पूर्ण
		अगर (bdelayscan) अणु
			/* delay 50ms to protect nulldata(1). */
			set_survey_समयr(pmlmeext, 50);
			वापस H2C_SUCCESS;
		पूर्ण
	पूर्ण

	अगर ((pmlmeext->sitesurvey_res.state == SCAN_START) || (pmlmeext->sitesurvey_res.state == SCAN_TXशून्य)) अणु
		/* disable dynamic functions, such as high घातer, DIG */
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false);

		/* config the initial gain under scanning, need to ग_लिखो the BB
		 * रेजिस्टरs
		 */
		initialgain = 0x1e;

		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));

		/* set MSR to no link state */
		Set_MSR(padapter, _HW_STATE_NOLINK_);

		val8 = 1; /* under site survey */
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		pmlmeext->sitesurvey_res.state = SCAN_PROCESS;
	पूर्ण

	site_survey(padapter);

	वापस H2C_SUCCESS;

पूर्ण

u8 setauth_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा setauth_parm		*pparm = (काष्ठा setauth_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (pparm->mode < 4)
		pmlmeinfo->auth_algo = pparm->mode;

	वापस	H2C_SUCCESS;
पूर्ण

u8 setkey_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u16 ctrl = 0;
	s16 cam_id = 0;
	काष्ठा setkey_parm		*pparm = (काष्ठा setkey_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	अचिन्हित अक्षर null_addr[] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	u8 *addr;

	/* मुख्य tx key क्रम wep. */
	अगर (pparm->set_tx)
		pmlmeinfo->key_index = pparm->keyid;

	cam_id = rtw_camid_alloc(padapter, शून्य, pparm->keyid);

	अगर (cam_id < 0) अणु
	पूर्ण अन्यथा अणु
		अगर (cam_id > 3) /* not शेष key, searched by A2 */
			addr = get_bssid(&padapter->mlmepriv);
		अन्यथा
			addr = null_addr;

		ctrl = BIT(15) | BIT6 | ((pparm->algorithm) << 2) | pparm->keyid;
		ग_लिखो_cam(padapter, cam_id, ctrl, addr, pparm->key);
		netdev_dbg(padapter->pnetdev,
			   "set group key camid:%d, addr:%pM, kid:%d, type:%s\n",
			   cam_id, MAC_ARG(addr), pparm->keyid,
			   security_type_str(pparm->algorithm));
	पूर्ण

	अगर (cam_id >= 0 && cam_id <= 3)
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_DK_CFG, (u8 *)true);

	/* allow multicast packets to driver */
	padapter->HalFunc.SetHwRegHandler(padapter, HW_VAR_ON_RCR_AM, null_addr);

	वापस H2C_SUCCESS;
पूर्ण

u8 set_stakey_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u16 ctrl = 0;
	s16 cam_id = 0;
	u8 ret = H2C_SUCCESS;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा set_stakey_parm	*pparm = (काष्ठा set_stakey_parm *)pbuf;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta;

	अगर (pparm->algorithm == _NO_PRIVACY_)
		जाओ ग_लिखो_to_cam;

	psta = rtw_get_stainfo(pstapriv, pparm->addr);
	अगर (!psta) अणु
		netdev_dbg(padapter->pnetdev, "%s sta:%pM not found\n",
			   __func__, MAC_ARG(pparm->addr));
		ret = H2C_REJECTED;
		जाओ निकास;
	पूर्ण

	pmlmeinfo->enc_algo = pparm->algorithm;
	cam_id = rtw_camid_alloc(padapter, psta, 0);
	अगर (cam_id < 0)
		जाओ निकास;

ग_लिखो_to_cam:
	अगर (pparm->algorithm == _NO_PRIVACY_) अणु
		जबतक ((cam_id = rtw_camid_search(padapter, pparm->addr, -1)) >= 0) अणु
			netdev_dbg(padapter->pnetdev,
				   "clear key for addr:%pM, camid:%d\n",
				   MAC_ARG(pparm->addr), cam_id);
			clear_cam_entry(padapter, cam_id);
			rtw_camid_मुक्त(padapter, cam_id);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_dbg(padapter->pnetdev,
			   "set pairwise key camid:%d, addr:%pM, kid:%d, type:%s\n",
			   cam_id, MAC_ARG(pparm->addr), pparm->keyid,
			   security_type_str(pparm->algorithm));
		ctrl = BIT(15) | ((pparm->algorithm) << 2) | pparm->keyid;
		ग_लिखो_cam(padapter, cam_id, ctrl, pparm->addr, pparm->key);
	पूर्ण
	ret = H2C_SUCCESS_RSP;

निकास:
	वापस ret;
पूर्ण

u8 add_ba_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा addBaReq_parm	*pparm = (काष्ठा addBaReq_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	काष्ठा sta_info *psta = rtw_get_stainfo(&padapter->stapriv, pparm->addr);

	अगर (!psta)
		वापस	H2C_SUCCESS;

	अगर (((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) && (pmlmeinfo->HT_enable)) ||
		((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)) अणु
		/* pmlmeinfo->ADDBA_retry_count = 0; */
		/* pmlmeinfo->candidate_tid_biपंचांगap |= (0x1 << pparm->tid); */
		/* psta->htpriv.candidate_tid_biपंचांगap |= BIT(pparm->tid); */
		issue_action_BA(padapter, pparm->addr, WLAN_ACTION_ADDBA_REQ, (u16)pparm->tid);
		/* _set_समयr(&pmlmeext->ADDBA_समयr, ADDBA_TO); */
		_set_समयr(&psta->addba_retry_समयr, ADDBA_TO);
	पूर्ण अन्यथा अणु
		psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(pparm->tid);
	पूर्ण
	वापस	H2C_SUCCESS;
पूर्ण


u8 chk_bmc_sleepq_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	init_h2fwcmd_w_parm_no_parm_rsp(ph2c, GEN_CMD_CODE(_ChkBMCSleepq));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

u8 set_tx_beacon_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा Tx_Beacon_param	*ptxBeacon_parm;
	काष्ठा cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 res = _SUCCESS;
	पूर्णांक len_dअगरf = 0;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	ptxBeacon_parm = rtw_zदो_स्मृति(माप(काष्ठा Tx_Beacon_param));
	अगर (ptxBeacon_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	स_नकल(&(ptxBeacon_parm->network), &(pmlmeinfo->network), माप(काष्ठा wlan_bssid_ex));

	len_dअगरf = update_hidden_ssid(ptxBeacon_parm->network.IEs+_BEACON_IE_OFFSET_,
				      ptxBeacon_parm->network.IELength-_BEACON_IE_OFFSET_,
				      pmlmeinfo->hidden_ssid_mode);
	ptxBeacon_parm->network.IELength += len_dअगरf;

	init_h2fwcmd_w_parm_no_rsp(ph2c, ptxBeacon_parm, GEN_CMD_CODE(_TX_Beacon));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण


u8 mlme_evt_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	u8 evt_code, evt_seq;
	u16 evt_sz;
	uपूर्णांक	*peventbuf;
	व्योम (*event_callback)(काष्ठा adapter *dev, u8 *pbuf);
	काष्ठा evt_priv *pevt_priv = &(padapter->evtpriv);

	अगर (pbuf == शून्य)
		जाओ _पात_event_;

	peventbuf = (uपूर्णांक *)pbuf;
	evt_sz = (u16)(*peventbuf&0xffff);
	evt_seq = (u8)((*peventbuf>>24)&0x7f);
	evt_code = (u8)((*peventbuf>>16)&0xff);


	#अगर_घोषित CHECK_EVENT_SEQ
	/*  checking event sequence... */
	अगर (evt_seq != (atomic_पढ़ो(&pevt_priv->event_seq) & 0x7f)) अणु
		pevt_priv->event_seq = (evt_seq+1)&0x7f;

		जाओ _पात_event_;
	पूर्ण
	#पूर्ण_अगर

	/*  checking अगर event code is valid */
	अगर (evt_code >= MAX_C2HEVT)
		जाओ _पात_event_;

	/*  checking अगर event size match the event parm size */
	अगर ((wlanevents[evt_code].parmsize != 0) &&
			(wlanevents[evt_code].parmsize != evt_sz))
		जाओ _पात_event_;

	atomic_inc(&pevt_priv->event_seq);

	peventbuf += 2;

	अगर (peventbuf) अणु
		event_callback = wlanevents[evt_code].event_callback;
		event_callback(padapter, (u8 *)peventbuf);

		pevt_priv->evt_करोne_cnt++;
	पूर्ण


_पात_event_:


	वापस H2C_SUCCESS;

पूर्ण

u8 h2c_msg_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	वापस H2C_SUCCESS;
पूर्ण

u8 chk_bmc_sleepq_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा sta_info *psta_bmc;
	काष्ठा list_head	*xmitframe_plist, *xmitframe_phead;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा sta_priv  *pstapriv = &padapter->stapriv;

	/* क्रम BC/MC Frames */
	psta_bmc = rtw_get_bcmc_stainfo(padapter);
	अगर (!psta_bmc)
		वापस H2C_SUCCESS;

	अगर ((pstapriv->tim_biपंचांगap&BIT(0)) && (psta_bmc->sleepq_len > 0)) अणु
		msleep(10);/*  10ms, ATIM(HIQ) Winकरोws */

		/* spin_lock_bh(&psta_bmc->sleep_q.lock); */
		spin_lock_bh(&pxmitpriv->lock);

		xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
		xmitframe_plist = get_next(xmitframe_phead);

		जबतक (xmitframe_phead != xmitframe_plist) अणु
			pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

			xmitframe_plist = get_next(xmitframe_plist);

			list_del_init(&pxmitframe->list);

			psta_bmc->sleepq_len--;
			अगर (psta_bmc->sleepq_len > 0)
				pxmitframe->attrib.mdata = 1;
			अन्यथा
				pxmitframe->attrib.mdata = 0;

			pxmitframe->attrib.triggered = 1;

			अगर (xmitframe_hiq_filter(pxmitframe))
				pxmitframe->attrib.qsel = 0x11;/* HIQ */

			rtw_hal_xmitframe_enqueue(padapter, pxmitframe);
		पूर्ण

		/* spin_unlock_bh(&psta_bmc->sleep_q.lock); */
		spin_unlock_bh(&pxmitpriv->lock);

		/* check hi queue and bmc_sleepq */
		rtw_chk_hi_queue_cmd(padapter);
	पूर्ण

	वापस H2C_SUCCESS;
पूर्ण

u8 tx_beacon_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	अगर (send_beacon(padapter) == _FAIL)
		वापस H2C_PARAMETERS_ERROR;

	/* tx bc/mc frames after update TIM */
	chk_bmc_sleepq_hdl(padapter, शून्य);

	वापस H2C_SUCCESS;
पूर्ण

पूर्णांक rtw_chk_start_clnt_join(काष्ठा adapter *padapter, u8 *ch, u8 *bw, u8 *offset)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	अचिन्हित अक्षर cur_ch = pmlmeext->cur_channel;
	अचिन्हित अक्षर cur_bw = pmlmeext->cur_bwmode;
	अचिन्हित अक्षर cur_ch_offset = pmlmeext->cur_ch_offset;
	bool connect_allow = true;

	अगर (!ch || !bw || !offset) अणु
		rtw_warn_on(1);
		connect_allow = false;
	पूर्ण

	अगर (connect_allow) अणु
		*ch = cur_ch;
		*bw = cur_bw;
		*offset = cur_ch_offset;
	पूर्ण

	वापस connect_allow ? _SUCCESS : _FAIL;
पूर्ण

/* Find जोड़ about ch, bw, ch_offset of all linked/linking पूर्णांकerfaces */
पूर्णांक rtw_get_ch_setting_जोड़(काष्ठा adapter *adapter, u8 *ch, u8 *bw, u8 *offset)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा adapter *अगरace;

	अगर (ch)
		*ch = 0;
	अगर (bw)
		*bw = CHANNEL_WIDTH_20;
	अगर (offset)
		*offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	अगरace = dvobj->padapters;

	अगर (!check_fwstate(&अगरace->mlmepriv, _FW_LINKED|_FW_UNDER_LINKING))
		वापस 0;

	वापस 1;
पूर्ण

u8 set_ch_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा set_ch_parm *set_ch_parm;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	set_ch_parm = (काष्ठा set_ch_parm *)pbuf;

	pmlmeext->cur_channel = set_ch_parm->ch;
	pmlmeext->cur_ch_offset = set_ch_parm->ch_offset;
	pmlmeext->cur_bwmode = set_ch_parm->bw;

	set_channel_bwmode(padapter, set_ch_parm->ch, set_ch_parm->ch_offset, set_ch_parm->bw);

	वापस	H2C_SUCCESS;
पूर्ण

u8 set_chplan_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा SetChannelPlan_param *setChannelPlan_param;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	setChannelPlan_param = (काष्ठा SetChannelPlan_param *)pbuf;

	pmlmeext->max_chan_nums = init_channel_set(padapter, setChannelPlan_param->channel_plan, pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);

	अगर (padapter->rtw_wdev && padapter->rtw_wdev->wiphy) अणु
		काष्ठा regulatory_request request;

		request.initiator = NL80211_REGDOM_SET_BY_DRIVER;
		rtw_reg_notअगरier(padapter->rtw_wdev->wiphy, &request);
	पूर्ण

	वापस	H2C_SUCCESS;
पूर्ण

u8 set_csa_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	वापस	H2C_REJECTED;
पूर्ण

/*  TDLS_ESTABLISHED	: ग_लिखो RCR DATA BIT */
/*  TDLS_CS_OFF		: go back to the channel linked with AP, terminating channel चयन procedure */
/*  TDLS_INIT_CH_SEN	: init channel sensing, receive all data and mgnt frame */
/*  TDLS_DONE_CH_SEN: channel sensing and report candidate channel */
/*  TDLS_OFF_CH		: first समय set channel to off channel */
/*  TDLS_BASE_CH		: go back tp the channel linked with AP when set base channel as target channel */
/*  TDLS_P_OFF_CH	: periodically go to off channel */
/*  TDLS_P_BASE_CH	: periodically go back to base channel */
/*  TDLS_RS_RCR		: restore RCR */
/*  TDLS_TEAR_STA	: मुक्त tdls sta */
u8 tdls_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	वापस H2C_REJECTED;
पूर्ण

u8 run_in_thपढ़ो_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा RunInThपढ़ो_param *p;


	अगर (शून्य == pbuf)
		वापस H2C_PARAMETERS_ERROR;
	p = (काष्ठा RunInThपढ़ो_param *)pbuf;

	अगर (p->func)
		p->func(p->context);

	वापस H2C_SUCCESS;
पूर्ण
