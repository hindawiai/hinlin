<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Authors:
 *    Rafael Antognolli <rafael.antognolli@पूर्णांकel.com>
 *    Scott  Bauer      <scott.bauer@पूर्णांकel.com>
 */

#अगर_अघोषित _UAPI_SED_OPAL_H
#घोषणा _UAPI_SED_OPAL_H

#समावेश <linux/types.h>

#घोषणा OPAL_KEY_MAX 256
#घोषणा OPAL_MAX_LRS 9

क्रमागत opal_mbr अणु
	OPAL_MBR_ENABLE = 0x0,
	OPAL_MBR_DISABLE = 0x01,
पूर्ण;

क्रमागत opal_mbr_करोne_flag अणु
	OPAL_MBR_NOT_DONE = 0x0,
	OPAL_MBR_DONE = 0x01
पूर्ण;

क्रमागत opal_user अणु
	OPAL_ADMIN1 = 0x0,
	OPAL_USER1 = 0x01,
	OPAL_USER2 = 0x02,
	OPAL_USER3 = 0x03,
	OPAL_USER4 = 0x04,
	OPAL_USER5 = 0x05,
	OPAL_USER6 = 0x06,
	OPAL_USER7 = 0x07,
	OPAL_USER8 = 0x08,
	OPAL_USER9 = 0x09,
पूर्ण;

क्रमागत opal_lock_state अणु
	OPAL_RO = 0x01, /* 0001 */
	OPAL_RW = 0x02, /* 0010 */
	OPAL_LK = 0x04, /* 0100 */
पूर्ण;

काष्ठा opal_key अणु
	__u8 lr;
	__u8 key_len;
	__u8 __align[6];
	__u8 key[OPAL_KEY_MAX];
पूर्ण;

काष्ठा opal_lr_act अणु
	काष्ठा opal_key key;
	__u32 sum;
	__u8 num_lrs;
	__u8 lr[OPAL_MAX_LRS];
	__u8 align[2]; /* Align to 8 byte boundary */
पूर्ण;

काष्ठा opal_session_info अणु
	__u32 sum;
	__u32 who;
	काष्ठा opal_key opal_key;
पूर्ण;

काष्ठा opal_user_lr_setup अणु
	__u64 range_start;
	__u64 range_length;
	__u32 RLE; /* Read Lock enabled */
	__u32 WLE; /* Write Lock Enabled */
	काष्ठा opal_session_info session;
पूर्ण;

काष्ठा opal_lock_unlock अणु
	काष्ठा opal_session_info session;
	__u32 l_state;
	__u8 __align[4];
पूर्ण;

काष्ठा opal_new_pw अणु
	काष्ठा opal_session_info session;

	/* When we're not operating in sum, and we first set
	 * passwords we need to set them via ADMIN authority.
	 * After passwords are changed, we can set them via,
	 * User authorities.
	 * Because of this restriction we need to know about
	 * Two dअगरferent users. One in 'session' which we will use
	 * to start the session and new_userr_pw as the user we're
	 * chaning the pw क्रम.
	 */
	काष्ठा opal_session_info new_user_pw;
पूर्ण;

काष्ठा opal_mbr_data अणु
	काष्ठा opal_key key;
	__u8 enable_disable;
	__u8 __align[7];
पूर्ण;

काष्ठा opal_mbr_करोne अणु
	काष्ठा opal_key key;
	__u8 करोne_flag;
	__u8 __align[7];
पूर्ण;

काष्ठा opal_shaकरोw_mbr अणु
	काष्ठा opal_key key;
	स्थिर __u64 data;
	__u64 offset;
	__u64 size;
पूर्ण;

/* Opal table operations */
क्रमागत opal_table_ops अणु
	OPAL_READ_TABLE,
	OPAL_WRITE_TABLE,
पूर्ण;

#घोषणा OPAL_UID_LENGTH 8
काष्ठा opal_पढ़ो_ग_लिखो_table अणु
	काष्ठा opal_key key;
	स्थिर __u64 data;
	स्थिर __u8 table_uid[OPAL_UID_LENGTH];
	__u64 offset;
	__u64 size;
#घोषणा OPAL_TABLE_READ (1 << OPAL_READ_TABLE)
#घोषणा OPAL_TABLE_WRITE (1 << OPAL_WRITE_TABLE)
	__u64 flags;
	__u64 priv;
पूर्ण;

#घोषणा IOC_OPAL_SAVE		    _IOW('p', 220, काष्ठा opal_lock_unlock)
#घोषणा IOC_OPAL_LOCK_UNLOCK	    _IOW('p', 221, काष्ठा opal_lock_unlock)
#घोषणा IOC_OPAL_TAKE_OWNERSHIP	    _IOW('p', 222, काष्ठा opal_key)
#घोषणा IOC_OPAL_ACTIVATE_LSP       _IOW('p', 223, काष्ठा opal_lr_act)
#घोषणा IOC_OPAL_SET_PW             _IOW('p', 224, काष्ठा opal_new_pw)
#घोषणा IOC_OPAL_ACTIVATE_USR       _IOW('p', 225, काष्ठा opal_session_info)
#घोषणा IOC_OPAL_REVERT_TPR         _IOW('p', 226, काष्ठा opal_key)
#घोषणा IOC_OPAL_LR_SETUP           _IOW('p', 227, काष्ठा opal_user_lr_setup)
#घोषणा IOC_OPAL_ADD_USR_TO_LR      _IOW('p', 228, काष्ठा opal_lock_unlock)
#घोषणा IOC_OPAL_ENABLE_DISABLE_MBR _IOW('p', 229, काष्ठा opal_mbr_data)
#घोषणा IOC_OPAL_ERASE_LR           _IOW('p', 230, काष्ठा opal_session_info)
#घोषणा IOC_OPAL_SECURE_ERASE_LR    _IOW('p', 231, काष्ठा opal_session_info)
#घोषणा IOC_OPAL_PSID_REVERT_TPR    _IOW('p', 232, काष्ठा opal_key)
#घोषणा IOC_OPAL_MBR_DONE           _IOW('p', 233, काष्ठा opal_mbr_करोne)
#घोषणा IOC_OPAL_WRITE_SHADOW_MBR   _IOW('p', 234, काष्ठा opal_shaकरोw_mbr)
#घोषणा IOC_OPAL_GENERIC_TABLE_RW   _IOW('p', 235, काष्ठा opal_पढ़ो_ग_लिखो_table)

#पूर्ण_अगर /* _UAPI_SED_OPAL_H */
