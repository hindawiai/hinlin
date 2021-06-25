<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_SECURITY_H_
#घोषणा __RTW_SECURITY_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#घोषणा _NO_PRIVACY_			0x0
#घोषणा _WEP40_				0x1
#घोषणा _TKIP_				0x2
#घोषणा _TKIP_WTMIC_			0x3
#घोषणा _AES_				0x4
#घोषणा _WEP104_			0x5
#घोषणा _WEP_WPA_MIXED_			0x07  /*  WEP + WPA */
#घोषणा _SMS4_				0x06

#घोषणा is_wep_enc(alg) (((alg) == _WEP40_) || ((alg) == _WEP104_))

#घोषणा SHA256_MAC_LEN 32
#घोषणा AES_BLOCK_SIZE 16
#घोषणा AES_PRIV_SIZE (4 * 44)

क्रमागत अणु
	ENCRYP_PROTOCOL_OPENSYS,   /* खोलो प्रणाली */
	ENCRYP_PROTOCOL_WEP,       /* WEP */
	ENCRYP_PROTOCOL_WPA,       /* WPA */
	ENCRYP_PROTOCOL_WPA2,      /* WPA2 */
	ENCRYP_PROTOCOL_WAPI,      /* WAPI: Not support in this version */
	ENCRYP_PROTOCOL_MAX
पूर्ण;

#अगर_अघोषित Ndis802_11AuthModeWPA2
#घोषणा Ndis802_11AuthModeWPA2 (Ndis802_11AuthModeWPANone + 1)
#पूर्ण_अगर

#अगर_अघोषित Ndis802_11AuthModeWPA2PSK
#घोषणा Ndis802_11AuthModeWPA2PSK (Ndis802_11AuthModeWPANone + 2)
#पूर्ण_अगर

जोड़ pn48	अणु
	u64	val;

#अगर_घोषित __LITTLE_ENDIAN
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

#या_अगर defined(__BIG_ENDIAN)

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
#पूर्ण_अगर
पूर्ण;

जोड़ Keytype अणु
	u8   skey[16];
	u32    lkey[4];
पूर्ण;

काष्ठा rt_pmkid_list अणु
	u8	used;
	u8	bssid[ETH_ALEN];
	u8	PMKID[16];
	u8	SsidBuf[33];
	u8	*ssid_octet;
	u16	ssid_length;
पूर्ण;

काष्ठा security_priv अणु
	u32	  करोt11AuthAlgrthm;	/*  802.11 auth, could be खोलो,
					 * shared, 8021x and authचयन
					 */
	u32	  करोt11PrivacyAlgrthm;	/*  This specअगरy the privacy क्रम
					 * shared auth. algorithm.
					 */
	/* WEP */
	u32	  करोt11PrivacyKeyIndex;	/*  this is only valid क्रम legendary
					 * wep, 0~3 क्रम key id.(tx key index)
					 */
	जोड़ Keytype करोt11DefKey[4];	/*  this is only valid क्रम def. key */
	u32	करोt11DefKeylen[4];
	u32 करोt118021XGrpPrivacy;	/*  This specअगरy the privacy algthm.
					 * used क्रम Grp key
					 */
	u32	करोt118021XGrpKeyid;	/*  key id used क्रम Grp Key
					 * ( tx key index)
					 */
	जोड़ Keytype	करोt118021XGrpKey[4];	/*  802.1x Group Key,
						 * क्रम inx0 and inx1
						 */
	जोड़ Keytype	करोt118021XGrptxmickey[4];
	जोड़ Keytype	करोt118021XGrprxmickey[4];
	जोड़ pn48	करोt11Grptxpn;		/* PN48 used क्रम Grp Key xmit.*/
	जोड़ pn48	करोt11Grprxpn;		/* PN48 used क्रम Grp Key recv.*/
#अगर_घोषित CONFIG_88EU_AP_MODE
	/* extend security capabilities क्रम AP_MODE */
	अचिन्हित पूर्णांक करोt8021xalg;/* 0:disable, 1:psk, 2:802.1x */
	अचिन्हित पूर्णांक wpa_psk;/* 0:disable, bit(0): WPA, bit(1):WPA2 */
	अचिन्हित पूर्णांक wpa_group_cipher;
	अचिन्हित पूर्णांक wpa2_group_cipher;
	अचिन्हित पूर्णांक wpa_pairwise_cipher;
	अचिन्हित पूर्णांक wpa2_pairwise_cipher;
#पूर्ण_अगर
	u8 wps_ie[MAX_WPS_IE_LEN];/* added in assoc req */
	पूर्णांक wps_ie_len;
	u8	binstallGrpkey;
	u8	busetkipkey;
	u8	bcheck_grpkey;
	u8	bgrpkey_handshake;
	s32	hw_decrypted;/* अगर the rx packets is hw_decrypted==false,i
			      * it means the hw has not been पढ़ोy.
			      */

	/* keeps the auth_type & enc_status from upper layer
	 * ioctl(wpa_supplicant or wzc)
	 */
	u32 ndisauthtype;	/*  NDIS_802_11_AUTHENTICATION_MODE */
	u32 ndisencryptstatus;	/*  NDIS_802_11_ENCRYPTION_STATUS */
	काष्ठा wlan_bssid_ex sec_bss;  /* क्रम joinbss (h2c buffer) usage */
	काष्ठा ndis_802_11_wep ndiswep;
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

	/*  */
	/*  For WPA2 Pre-Authentication. */
	/*  */
	काष्ठा rt_pmkid_list PMKIDList[NUM_PMKID_CACHE];
	u8	PMKIDIndex;
	u8 bWepDefaultKeyIdxSet;
पूर्ण;

#घोषणा GET_ENCRY_ALGO(psecuritypriv, psta, encry_algo, bmcst)		\
करो अणु									\
	चयन (psecuritypriv->करोt11AuthAlgrthm) अणु			\
	हाल करोt11AuthAlgrthm_Open:					\
	हाल करोt11AuthAlgrthm_Shared:					\
	हाल करोt11AuthAlgrthm_Auto:					\
		encry_algo = (u8)psecuritypriv->करोt11PrivacyAlgrthm;	\
		अवरोध;							\
	हाल करोt11AuthAlgrthm_8021X:					\
		अगर (bmcst)						\
			encry_algo = (u8)psecuritypriv->करोt118021XGrpPrivacy;\
		अन्यथा							\
			encry_algo = (u8)psta->करोt118021XPrivacy;	\
		अवरोध;							\
	हाल करोt11AuthAlgrthm_WAPI:					\
		encry_algo = (u8)psecuritypriv->करोt11PrivacyAlgrthm;	\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा SET_ICE_IV_LEN(iv_len, icv_len, encrypt)			\
करो अणु									\
	चयन (encrypt) अणु						\
	हाल _WEP40_:							\
	हाल _WEP104_:							\
		iv_len = 4;						\
		icv_len = 4;						\
		अवरोध;							\
	हाल _TKIP_:							\
		iv_len = 8;						\
		icv_len = 4;						\
		अवरोध;							\
	हाल _AES_:							\
		iv_len = 8;						\
		icv_len = 8;						\
		अवरोध;							\
	हाल _SMS4_:							\
		iv_len = 18;						\
		icv_len = 16;						\
		अवरोध;							\
	शेष:							\
		iv_len = 0;						\
		icv_len = 0;						\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा GET_TKIP_PN(iv, करोt11txpn)					\
करो अणु									\
	करोt11txpn._byte_.TSC0 = iv[2];					\
	करोt11txpn._byte_.TSC1 = iv[0];					\
	करोt11txpn._byte_.TSC2 = iv[4];					\
	करोt11txpn._byte_.TSC3 = iv[5];					\
	करोt11txpn._byte_.TSC4 = iv[6];					\
	करोt11txpn._byte_.TSC5 = iv[7];					\
पूर्ण जबतक (0)

#घोषणा ROL32(A, n)	(((A) << (n)) | (((A) >> (32 - (n)))  & ((1UL << (n)) - 1)))
#घोषणा ROR32(A, n)	ROL32((A), 32 - (n))

काष्ठा mic_data अणु
	u32  K0, K1;         /*  Key */
	u32  L, R;           /*  Current state */
	u32  M;              /*  Message accumulator (single word) */
	u32  nBytesInM;      /*  # bytes in M */
पूर्ण;

व्योम rtw_secmicsetkey(काष्ठा mic_data *pmicdata, u8 *key);
व्योम rtw_secmicappendbyte(काष्ठा mic_data *pmicdata, u8 b);
व्योम rtw_secmicappend(काष्ठा mic_data *pmicdata, u8 *src, u32 nBytes);
व्योम rtw_secgeपंचांगic(काष्ठा mic_data *pmicdata, u8 *dst);
व्योम rtw_seccalctkipmic(u8 *key, u8 *header, u8 *data, u32 data_len,
			u8 *Miccode, u8   priority);
u32 rtw_aes_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
u32 rtw_tkip_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
व्योम rtw_wep_encrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
u32 rtw_aes_decrypt(काष्ठा adapter *padapter, काष्ठा recv_frame *precvframe);
u32 rtw_tkip_decrypt(काष्ठा adapter *padapter, काष्ठा recv_frame *precvframe);
पूर्णांक rtw_wep_decrypt(काष्ठा adapter *padapter, काष्ठा recv_frame *precvframe);

#पूर्ण_अगर	/* __RTL871X_SECURITY_H_ */
