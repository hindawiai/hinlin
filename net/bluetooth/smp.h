<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर_अघोषित __SMP_H
#घोषणा __SMP_H

काष्ठा smp_command_hdr अणु
	__u8	code;
पूर्ण __packed;

#घोषणा SMP_CMD_PAIRING_REQ	0x01
#घोषणा SMP_CMD_PAIRING_RSP	0x02
काष्ठा smp_cmd_pairing अणु
	__u8	io_capability;
	__u8	oob_flag;
	__u8	auth_req;
	__u8	max_key_size;
	__u8	init_key_dist;
	__u8	resp_key_dist;
पूर्ण __packed;

#घोषणा SMP_IO_DISPLAY_ONLY	0x00
#घोषणा SMP_IO_DISPLAY_YESNO	0x01
#घोषणा SMP_IO_KEYBOARD_ONLY	0x02
#घोषणा SMP_IO_NO_INPUT_OUTPUT	0x03
#घोषणा SMP_IO_KEYBOARD_DISPLAY	0x04

#घोषणा SMP_OOB_NOT_PRESENT	0x00
#घोषणा SMP_OOB_PRESENT		0x01

#घोषणा SMP_DIST_ENC_KEY	0x01
#घोषणा SMP_DIST_ID_KEY		0x02
#घोषणा SMP_DIST_SIGN		0x04
#घोषणा SMP_DIST_LINK_KEY	0x08

#घोषणा SMP_AUTH_NONE		0x00
#घोषणा SMP_AUTH_BONDING	0x01
#घोषणा SMP_AUTH_MITM		0x04
#घोषणा SMP_AUTH_SC		0x08
#घोषणा SMP_AUTH_KEYPRESS	0x10
#घोषणा SMP_AUTH_CT2		0x20

#घोषणा SMP_CMD_PAIRING_CONFIRM	0x03
काष्ठा smp_cmd_pairing_confirm अणु
	__u8	confirm_val[16];
पूर्ण __packed;

#घोषणा SMP_CMD_PAIRING_RANDOM	0x04
काष्ठा smp_cmd_pairing_अक्रमom अणु
	__u8	अक्रम_val[16];
पूर्ण __packed;

#घोषणा SMP_CMD_PAIRING_FAIL	0x05
काष्ठा smp_cmd_pairing_fail अणु
	__u8	reason;
पूर्ण __packed;

#घोषणा SMP_CMD_ENCRYPT_INFO	0x06
काष्ठा smp_cmd_encrypt_info अणु
	__u8	ltk[16];
पूर्ण __packed;

#घोषणा SMP_CMD_MASTER_IDENT	0x07
काष्ठा smp_cmd_master_ident अणु
	__le16	eभाग;
	__le64	अक्रम;
पूर्ण __packed;

#घोषणा SMP_CMD_IDENT_INFO	0x08
काष्ठा smp_cmd_ident_info अणु
	__u8	irk[16];
पूर्ण __packed;

#घोषणा SMP_CMD_IDENT_ADDR_INFO	0x09
काष्ठा smp_cmd_ident_addr_info अणु
	__u8	addr_type;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा SMP_CMD_SIGN_INFO	0x0a
काष्ठा smp_cmd_sign_info अणु
	__u8	csrk[16];
पूर्ण __packed;

#घोषणा SMP_CMD_SECURITY_REQ	0x0b
काष्ठा smp_cmd_security_req अणु
	__u8	auth_req;
पूर्ण __packed;

#घोषणा SMP_CMD_PUBLIC_KEY	0x0c
काष्ठा smp_cmd_खुला_key अणु
	__u8	x[32];
	__u8	y[32];
पूर्ण __packed;

#घोषणा SMP_CMD_DHKEY_CHECK	0x0d
काष्ठा smp_cmd_dhkey_check अणु
	__u8	e[16];
पूर्ण __packed;

#घोषणा SMP_CMD_KEYPRESS_NOTIFY	0x0e
काष्ठा smp_cmd_keypress_notअगरy अणु
	__u8	value;
पूर्ण __packed;

#घोषणा SMP_CMD_MAX		0x0e

#घोषणा SMP_PASSKEY_ENTRY_FAILED	0x01
#घोषणा SMP_OOB_NOT_AVAIL		0x02
#घोषणा SMP_AUTH_REQUIREMENTS		0x03
#घोषणा SMP_CONFIRM_FAILED		0x04
#घोषणा SMP_PAIRING_NOTSUPP		0x05
#घोषणा SMP_ENC_KEY_SIZE		0x06
#घोषणा SMP_CMD_NOTSUPP			0x07
#घोषणा SMP_UNSPECIFIED			0x08
#घोषणा SMP_REPEATED_ATTEMPTS		0x09
#घोषणा SMP_INVALID_PARAMS		0x0a
#घोषणा SMP_DHKEY_CHECK_FAILED		0x0b
#घोषणा SMP_NUMERIC_COMP_FAILED		0x0c
#घोषणा SMP_BREDR_PAIRING_IN_PROGRESS	0x0d
#घोषणा SMP_CROSS_TRANSP_NOT_ALLOWED	0x0e

#घोषणा SMP_MIN_ENC_KEY_SIZE		7
#घोषणा SMP_MAX_ENC_KEY_SIZE		16

/* LTK types used in पूर्णांकernal storage (काष्ठा smp_ltk) */
क्रमागत अणु
	SMP_STK,
	SMP_LTK,
	SMP_LTK_SLAVE,
	SMP_LTK_P256,
	SMP_LTK_P256_DEBUG,
पूर्ण;

अटल अंतरभूत bool smp_ltk_is_sc(काष्ठा smp_ltk *key)
अणु
	चयन (key->type) अणु
	हाल SMP_LTK_P256:
	हाल SMP_LTK_P256_DEBUG:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत u8 smp_ltk_sec_level(काष्ठा smp_ltk *key)
अणु
	अगर (key->authenticated) अणु
		अगर (smp_ltk_is_sc(key))
			वापस BT_SECURITY_FIPS;
		अन्यथा
			वापस BT_SECURITY_HIGH;
	पूर्ण

	वापस BT_SECURITY_MEDIUM;
पूर्ण

/* Key preferences क्रम smp_sufficient security */
क्रमागत smp_key_pref अणु
	SMP_ALLOW_STK,
	SMP_USE_LTK,
पूर्ण;

/* SMP Commands */
पूर्णांक smp_cancel_and_हटाओ_pairing(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 addr_type);
bool smp_sufficient_security(काष्ठा hci_conn *hcon, u8 sec_level,
			     क्रमागत smp_key_pref key_pref);
पूर्णांक smp_conn_security(काष्ठा hci_conn *hcon, __u8 sec_level);
पूर्णांक smp_user_confirm_reply(काष्ठा hci_conn *conn, u16 mgmt_op, __le32 passkey);

bool smp_irk_matches(काष्ठा hci_dev *hdev, स्थिर u8 irk[16],
		     स्थिर bdaddr_t *bdaddr);
पूर्णांक smp_generate_rpa(काष्ठा hci_dev *hdev, स्थिर u8 irk[16], bdaddr_t *rpa);
पूर्णांक smp_generate_oob(काष्ठा hci_dev *hdev, u8 hash[16], u8 अक्रम[16]);

पूर्णांक smp_क्रमce_bredr(काष्ठा hci_dev *hdev, bool enable);

पूर्णांक smp_रेजिस्टर(काष्ठा hci_dev *hdev);
व्योम smp_unरेजिस्टर(काष्ठा hci_dev *hdev);

#अगर IS_ENABLED(CONFIG_BT_SELFTEST_SMP)

पूर्णांक bt_selftest_smp(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक bt_selftest_smp(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __SMP_H */
