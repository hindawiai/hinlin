<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */

#अगर_अघोषित _fwil_h_
#घोषणा _fwil_h_

/*******************************************************************************
 * Dongle command codes that are पूर्णांकerpreted by firmware
 ******************************************************************************/
#घोषणा BRCMF_C_GET_VERSION			1
#घोषणा BRCMF_C_UP				2
#घोषणा BRCMF_C_DOWN				3
#घोषणा BRCMF_C_SET_PROMISC			10
#घोषणा BRCMF_C_GET_RATE			12
#घोषणा BRCMF_C_GET_INFRA			19
#घोषणा BRCMF_C_SET_INFRA			20
#घोषणा BRCMF_C_GET_AUTH			21
#घोषणा BRCMF_C_SET_AUTH			22
#घोषणा BRCMF_C_GET_BSSID			23
#घोषणा BRCMF_C_GET_SSID			25
#घोषणा BRCMF_C_SET_SSID			26
#घोषणा BRCMF_C_TERMINATED			28
#घोषणा BRCMF_C_GET_CHANNEL			29
#घोषणा BRCMF_C_SET_CHANNEL			30
#घोषणा BRCMF_C_GET_SRL				31
#घोषणा BRCMF_C_SET_SRL				32
#घोषणा BRCMF_C_GET_LRL				33
#घोषणा BRCMF_C_SET_LRL				34
#घोषणा BRCMF_C_GET_RADIO			37
#घोषणा BRCMF_C_SET_RADIO			38
#घोषणा BRCMF_C_GET_PHYTYPE			39
#घोषणा BRCMF_C_SET_KEY				45
#घोषणा BRCMF_C_GET_REGULATORY			46
#घोषणा BRCMF_C_SET_REGULATORY			47
#घोषणा BRCMF_C_SET_PASSIVE_SCAN		49
#घोषणा BRCMF_C_SCAN				50
#घोषणा BRCMF_C_SCAN_RESULTS			51
#घोषणा BRCMF_C_DISASSOC			52
#घोषणा BRCMF_C_REASSOC				53
#घोषणा BRCMF_C_SET_ROAM_TRIGGER		55
#घोषणा BRCMF_C_SET_ROAM_DELTA			57
#घोषणा BRCMF_C_GET_BCNPRD			75
#घोषणा BRCMF_C_SET_BCNPRD			76
#घोषणा BRCMF_C_GET_DTIMPRD			77
#घोषणा BRCMF_C_SET_DTIMPRD			78
#घोषणा BRCMF_C_SET_COUNTRY			84
#घोषणा BRCMF_C_GET_PM				85
#घोषणा BRCMF_C_SET_PM				86
#घोषणा BRCMF_C_GET_REVINFO			98
#घोषणा BRCMF_C_GET_MONITOR			107
#घोषणा BRCMF_C_SET_MONITOR			108
#घोषणा BRCMF_C_GET_CURR_RATESET		114
#घोषणा BRCMF_C_GET_AP				117
#घोषणा BRCMF_C_SET_AP				118
#घोषणा BRCMF_C_SET_SCB_AUTHORIZE		121
#घोषणा BRCMF_C_SET_SCB_DEAUTHORIZE		122
#घोषणा BRCMF_C_GET_RSSI			127
#घोषणा BRCMF_C_GET_WSEC			133
#घोषणा BRCMF_C_SET_WSEC			134
#घोषणा BRCMF_C_GET_PHY_NOISE			135
#घोषणा BRCMF_C_GET_BSS_INFO			136
#घोषणा BRCMF_C_GET_GET_PKTCNTS			137
#घोषणा BRCMF_C_GET_BANDLIST			140
#घोषणा BRCMF_C_SET_SCB_TIMEOUT			158
#घोषणा BRCMF_C_GET_ASSOCLIST			159
#घोषणा BRCMF_C_GET_PHYLIST			180
#घोषणा BRCMF_C_SET_SCAN_CHANNEL_TIME		185
#घोषणा BRCMF_C_SET_SCAN_UNASSOC_TIME		187
#घोषणा BRCMF_C_SCB_DEAUTHENTICATE_FOR_REASON	201
#घोषणा BRCMF_C_SET_ASSOC_PREFER		205
#घोषणा BRCMF_C_GET_VALID_CHANNELS		217
#घोषणा BRCMF_C_SET_FAKEFRAG			219
#घोषणा BRCMF_C_GET_KEY_PRIMARY			235
#घोषणा BRCMF_C_SET_KEY_PRIMARY			236
#घोषणा BRCMF_C_SET_SCAN_PASSIVE_TIME		258
#घोषणा BRCMF_C_GET_VAR				262
#घोषणा BRCMF_C_SET_VAR				263
#घोषणा BRCMF_C_SET_WSEC_PMK			268

s32 brcmf_fil_cmd_data_set(काष्ठा brcmf_अगर *अगरp, u32 cmd, व्योम *data, u32 len);
s32 brcmf_fil_cmd_data_get(काष्ठा brcmf_अगर *अगरp, u32 cmd, व्योम *data, u32 len);
s32 brcmf_fil_cmd_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, u32 cmd, u32 data);
s32 brcmf_fil_cmd_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, u32 cmd, u32 *data);

s32 brcmf_fil_iovar_data_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, स्थिर व्योम *data,
			     u32 len);
s32 brcmf_fil_iovar_data_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, व्योम *data,
			     u32 len);
s32 brcmf_fil_iovar_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 data);
s32 brcmf_fil_iovar_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 *data);

s32 brcmf_fil_bsscfg_data_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, व्योम *data,
			      u32 len);
s32 brcmf_fil_bsscfg_data_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, व्योम *data,
			      u32 len);
s32 brcmf_fil_bsscfg_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 data);
s32 brcmf_fil_bsscfg_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 *data);

#पूर्ण_अगर /* _fwil_h_ */
