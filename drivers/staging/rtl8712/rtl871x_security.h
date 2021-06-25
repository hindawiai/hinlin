<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_SECURITY_H_
#घोषणा __RTL871X_SECURITY_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#घोषणा _NO_PRIVACY_	0x0
#घोषणा _WEP40_		0x1
#घोषणा _TKIP_		0x2
#घोषणा _TKIP_WTMIC_	0x3
#घोषणा _AES_		0x4
#घोषणा _WEP104_	0x5

#घोषणा _WPA_IE_ID_	0xdd
#घोषणा _WPA2_IE_ID_	0x30

#अगर_अघोषित Ndis802_11AuthModeWPA2
#घोषणा Ndis802_11AuthModeWPA2 (Ndis802_11AuthModeWPANone + 1)
#पूर्ण_अगर

#अगर_अघोषित Ndis802_11AuthModeWPA2PSK
#घोषणा Ndis802_11AuthModeWPA2PSK (Ndis802_11AuthModeWPANone + 2)
#पूर्ण_अगर

जोड़ pn48 अणु
	u64 val;
#अगर defined(__BIG_ENDIAN)
	काष्ठा अणु
		u8 TSC7;
		u8 TSC6;
		u8 TSC5;
		u8 TSC4;
		u8 TSC3;
		u8 TSC2;
		u8 TSC1;
		u8 TSC0;
	पूर्ण _byte_;
#अन्यथा
	काष्ठा अणु
		u8 TSC0;
		u8 TSC1;
		u8 TSC2;
		u8 TSC3;
		u8 TSC4;
		u8 TSC5;
		u8 TSC6;
		u8 TSC7;
	पूर्ण _byte_;
#पूर्ण_अगर
पूर्ण;

जोड़ Keytype अणु
	u8 skey[16];
	u32 lkey[4];
पूर्ण;

काष्ठा RT_PMKID_LIST अणु
	u8 bUsed;
	u8 Bssid[6];
	u8 PMKID[16];
	u8 SsidBuf[33];
	u8 *ssid_octet;
	u16 ssid_length;
पूर्ण;

काष्ठा security_priv अणु
	u32 AuthAlgrthm;		/* 802.11 auth, could be खोलो, shared,
					 * 8021x and authचयन
					 */
	u32 PrivacyAlgrthm;		/* This specअगरy the privacy क्रम shared
					 * auth. algorithm.
					 */
	u32 PrivacyKeyIndex;		/* this is only valid क्रम legendary
					 * wep, 0~3 क्रम key id.
					 */
	जोड़ Keytype DefKey[4];	/* this is only valid क्रम def. key */
	u32 DefKeylen[4];
	u32 XGrpPrivacy;		/* This specअगरy the privacy algthm.
					 * used क्रम Grp key
					 */
	u32 XGrpKeyid;			/* key id used क्रम Grp Key */
	जोड़ Keytype	XGrpKey[2];	/* 802.1x Group Key, क्रम
					 * inx0 and inx1
					 */
	जोड़ Keytype	XGrptxmickey[2];
	जोड़ Keytype	XGrprxmickey[2];
	जोड़ pn48 Grptxpn;		/* PN48 used क्रम Grp Key xmit. */
	जोड़ pn48 Grprxpn;		/* PN48 used क्रम Grp Key recv. */
	u8 wps_hw_pbc_pressed;/*क्रम hw pbc pressed*/
	u8 wps_phase;/*क्रम wps*/
	u8 wps_ie[MAX_WPA_IE_LEN << 2];
	पूर्णांक wps_ie_len;
	u8	binstallGrpkey;
	u8	busetkipkey;
	काष्ठा समयr_list tkip_समयr;
	u8	bcheck_grpkey;
	u8	bgrpkey_handshake;
	s32	sw_encrypt;	/* from registry_priv */
	s32	sw_decrypt;	/* from registry_priv */
	s32	hw_decrypted;	/* अगर the rx packets is hw_decrypted==false,
				 * it means the hw has not been पढ़ोy.
				 */
	u32 ndisauthtype;	/* keeps the auth_type & enc_status from upper
				 * layer ioctl(wpa_supplicant or wzc)
				 */
	u32 ndisencryptstatus;
	काष्ठा wlan_bssid_ex sec_bss;  /* क्रम joinbss (h2c buffer) usage */
	काष्ठा NDIS_802_11_WEP ndiswep;
	u8 assoc_info[600];
	u8 szofcapability[256]; /* क्रम wpa2 usage */
	u8 oidassociation[512]; /* क्रम wpa/wpa2 usage */
	u8 authenticator_ie[256];  /* store ap security inक्रमmation element */
	u8 supplicant_ie[256];  /* store sta security inक्रमmation element */
	/* क्रम tkip countermeasure */
	u32 last_mic_err_समय;
	u8	btkip_countermeasure;
	u8	btkip_रुको_report;
	u32 btkip_countermeasure_समय;
	/*-------------------------------------------------------------------
	 * For WPA2 Pre-Authentication.
	 *------------------------------------------------------------------
	 **/
	काष्ठा RT_PMKID_LIST		PMKIDList[NUM_PMKID_CACHE];
	u8				PMKIDIndex;
पूर्ण;

#घोषणा GET_ENCRY_ALGO(psecuritypriv, psta, encry_algo, bmcst) \
करो अणु \
	चयन (psecuritypriv->AuthAlgrthm) अणु \
	हाल 0: \
	हाल 1: \
	हाल 3: \
		encry_algo = (u8)psecuritypriv->PrivacyAlgrthm; \
		अवरोध; \
	हाल 2: \
		अगर (bmcst) \
			encry_algo = (u8)psecuritypriv->XGrpPrivacy; \
		अन्यथा \
			encry_algo = (u8)psta->XPrivacy; \
		अवरोध; \
	पूर्ण \
पूर्ण जबतक (0)
#घोषणा SET_ICE_IV_LEN(iv_len, icv_len, encrypt)\
करो अणु\
	चयन (encrypt) अणु \
	हाल _WEP40_: \
	हाल _WEP104_: \
		iv_len = 4; \
		icv_len = 4; \
		अवरोध; \
	हाल _TKIP_: \
		iv_len = 8; \
		icv_len = 4; \
		अवरोध; \
	हाल _AES_: \
		iv_len = 8; \
		icv_len = 8; \
		अवरोध; \
	शेष: \
		iv_len = 0; \
		icv_len = 0; \
		अवरोध; \
	पूर्ण \
पूर्ण जबतक (0)
#घोषणा GET_TKIP_PN(iv, txpn) \
करो अणु\
	txpn._byte_.TSC0 = iv[2];\
	txpn._byte_.TSC1 = iv[0];\
	txpn._byte_.TSC2 = iv[4];\
	txpn._byte_.TSC3 = iv[5];\
	txpn._byte_.TSC4 = iv[6];\
	txpn._byte_.TSC5 = iv[7];\
पूर्ण जबतक (0)

#घोषणा ROL32(A, n) (((A) << (n)) | (((A) >> (32 - (n)))  & ((1UL << (n)) - 1)))
#घोषणा ROR32(A, n) ROL32((A), 32 - (n))

काष्ठा mic_data अणु
	u32  K0, K1;         /* Key */
	u32  L, R;           /* Current state */
	u32  M;              /* Message accumulator (single word) */
	u32  nBytesInM;      /* # bytes in M */
पूर्ण;

व्योम seccalctkipmic(
	u8  *key,
	u8  *header,
	u8  *data,
	u32  data_len,
	u8  *Miccode,
	u8   priority);

व्योम r8712_secmicsetkey(काष्ठा mic_data *pmicdata, u8 *key);
व्योम r8712_secmicappend(काष्ठा mic_data *pmicdata, u8 *src, u32 nBytes);
व्योम r8712_secgeपंचांगic(काष्ठा mic_data *pmicdata, u8 *dst);
u32 r8712_aes_encrypt(काष्ठा _adapter *padapter, u8 *pxmitframe);
u32 r8712_tkip_encrypt(काष्ठा _adapter *padapter, u8 *pxmitframe);
व्योम r8712_wep_encrypt(काष्ठा _adapter *padapter, u8  *pxmitframe);
व्योम r8712_aes_decrypt(काष्ठा _adapter *padapter, u8  *precvframe);
व्योम r8712_tkip_decrypt(काष्ठा _adapter *padapter, u8  *precvframe);
व्योम r8712_wep_decrypt(काष्ठा _adapter *padapter, u8  *precvframe);
व्योम r8712_use_tkipkey_handler(काष्ठा समयr_list *t);

#पूर्ण_अगर	/*__RTL871X_SECURITY_H_ */

