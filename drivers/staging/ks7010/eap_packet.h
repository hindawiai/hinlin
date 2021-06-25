<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित EAP_PACKET_H
#घोषणा EAP_PACKET_H

#समावेश <linux/compiler.h>
#समावेश <linux/bitops.h>
#समावेश <uapi/linux/अगर_ether.h>

काष्ठा ether_hdr अणु
	अचिन्हित अक्षर h_dest[ETH_ALEN];	/* destination eth addr */
	अचिन्हित अक्षर h_source[ETH_ALEN];	/* source ether addr    */
	अचिन्हित अक्षर h_dest_snap;
	अचिन्हित अक्षर h_source_snap;
	अचिन्हित अक्षर h_command;
	अचिन्हित अक्षर h_venकरोr_id[3];
	__be16 h_proto;	/* packet type ID field */
	/* followed by length octets of data */
पूर्ण __packed;

#घोषणा ETHER_HDR_SIZE माप(काष्ठा ether_hdr)

काष्ठा ieee802_1x_hdr अणु
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर type;
	अचिन्हित लघु length;
	/* followed by length octets of data */
पूर्ण __packed;

क्रमागत अणु
	IEEE802_1X_TYPE_EAP_PACKET = 0,
	IEEE802_1X_TYPE_EAPOL_START = 1,
	IEEE802_1X_TYPE_EAPOL_LOGOFF = 2,
	IEEE802_1X_TYPE_EAPOL_KEY = 3,
	IEEE802_1X_TYPE_EAPOL_ENCAPSULATED_ASF_ALERT = 4
पूर्ण;

#घोषणा WPA_NONCE_LEN 32
#घोषणा WPA_REPLAY_COUNTER_LEN 8

काष्ठा wpa_eapol_key अणु
	अचिन्हित अक्षर type;
	__be16 key_info;
	अचिन्हित लघु key_length;
	अचिन्हित अक्षर replay_counter[WPA_REPLAY_COUNTER_LEN];
	अचिन्हित अक्षर key_nonce[WPA_NONCE_LEN];
	अचिन्हित अक्षर key_iv[16];
	अचिन्हित अक्षर key_rsc[8];
	अचिन्हित अक्षर key_id[8];	/* Reserved in IEEE 802.11i/RSN */
	अचिन्हित अक्षर key_mic[16];
	अचिन्हित लघु key_data_length;
	/* followed by key_data_length bytes of key_data */
पूर्ण __packed;

#घोषणा WPA_KEY_INFO_TYPE_MASK GENMASK(2, 0)
#घोषणा WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 BIT(0)
#घोषणा WPA_KEY_INFO_TYPE_HMAC_SHA1_AES BIT(1)
#घोषणा WPA_KEY_INFO_KEY_TYPE BIT(3)	/* 1 = Pairwise, 0 = Group key */
/* bit4..5 is used in WPA, but is reserved in IEEE 802.11i/RSN */
#घोषणा WPA_KEY_INFO_KEY_INDEX_MASK GENMASK(5, 4)
#घोषणा WPA_KEY_INFO_KEY_INDEX_SHIFT 4
#घोषणा WPA_KEY_INFO_INSTALL BIT(6)	/* pairwise */
#घोषणा WPA_KEY_INFO_TXRX BIT(6)	/* group */
#घोषणा WPA_KEY_INFO_ACK BIT(7)
#घोषणा WPA_KEY_INFO_MIC BIT(8)
#घोषणा WPA_KEY_INFO_SECURE BIT(9)
#घोषणा WPA_KEY_INFO_ERROR BIT(10)
#घोषणा WPA_KEY_INFO_REQUEST BIT(11)
#घोषणा WPA_KEY_INFO_ENCR_KEY_DATA BIT(12)	/* IEEE 802.11i/RSN only */

#पूर्ण_अगर /* EAP_PACKET_H */
