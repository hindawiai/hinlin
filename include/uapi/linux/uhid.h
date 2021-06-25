<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित __UHID_H_
#घोषणा __UHID_H_

/*
 * User-space I/O driver support क्रम HID subप्रणाली
 * Copyright (c) 2012 David Herrmann
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

/*
 * Public header क्रम user-space communication. We try to keep every काष्ठाure
 * aligned but to be safe we also use __attribute__((__packed__)). Thereक्रमe,
 * the communication should be ABI compatible even between architectures.
 */

#समावेश <linux/input.h>
#समावेश <linux/types.h>
#समावेश <linux/hid.h>

क्रमागत uhid_event_type अणु
	__UHID_LEGACY_CREATE,
	UHID_DESTROY,
	UHID_START,
	UHID_STOP,
	UHID_OPEN,
	UHID_CLOSE,
	UHID_OUTPUT,
	__UHID_LEGACY_OUTPUT_EV,
	__UHID_LEGACY_INPUT,
	UHID_GET_REPORT,
	UHID_GET_REPORT_REPLY,
	UHID_CREATE2,
	UHID_INPUT2,
	UHID_SET_REPORT,
	UHID_SET_REPORT_REPLY,
पूर्ण;

काष्ठा uhid_create2_req अणु
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];
	__u16 rd_size;
	__u16 bus;
	__u32 venकरोr;
	__u32 product;
	__u32 version;
	__u32 country;
	__u8 rd_data[HID_MAX_DESCRIPTOR_SIZE];
पूर्ण __attribute__((__packed__));

क्रमागत uhid_dev_flag अणु
	UHID_DEV_NUMBERED_FEATURE_REPORTS			= (1ULL << 0),
	UHID_DEV_NUMBERED_OUTPUT_REPORTS			= (1ULL << 1),
	UHID_DEV_NUMBERED_INPUT_REPORTS				= (1ULL << 2),
पूर्ण;

काष्ठा uhid_start_req अणु
	__u64 dev_flags;
पूर्ण;

#घोषणा UHID_DATA_MAX 4096

क्रमागत uhid_report_type अणु
	UHID_FEATURE_REPORT,
	UHID_OUTPUT_REPORT,
	UHID_INPUT_REPORT,
पूर्ण;

काष्ठा uhid_input2_req अणु
	__u16 size;
	__u8 data[UHID_DATA_MAX];
पूर्ण __attribute__((__packed__));

काष्ठा uhid_output_req अणु
	__u8 data[UHID_DATA_MAX];
	__u16 size;
	__u8 rtype;
पूर्ण __attribute__((__packed__));

काष्ठा uhid_get_report_req अणु
	__u32 id;
	__u8 rnum;
	__u8 rtype;
पूर्ण __attribute__((__packed__));

काष्ठा uhid_get_report_reply_req अणु
	__u32 id;
	__u16 err;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
पूर्ण __attribute__((__packed__));

काष्ठा uhid_set_report_req अणु
	__u32 id;
	__u8 rnum;
	__u8 rtype;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
पूर्ण __attribute__((__packed__));

काष्ठा uhid_set_report_reply_req अणु
	__u32 id;
	__u16 err;
पूर्ण __attribute__((__packed__));

/*
 * Compat Layer
 * All these commands and requests are obsolete. You should aव्योम using them in
 * new code. We support them क्रम backwards-compatibility, but you might not get
 * access to new feature in हाल you use them.
 */

क्रमागत uhid_legacy_event_type अणु
	UHID_CREATE			= __UHID_LEGACY_CREATE,
	UHID_OUTPUT_EV			= __UHID_LEGACY_OUTPUT_EV,
	UHID_INPUT			= __UHID_LEGACY_INPUT,
	UHID_FEATURE			= UHID_GET_REPORT,
	UHID_FEATURE_ANSWER		= UHID_GET_REPORT_REPLY,
पूर्ण;

/* Obsolete! Use UHID_CREATE2. */
काष्ठा uhid_create_req अणु
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];
	__u8 __user *rd_data;
	__u16 rd_size;

	__u16 bus;
	__u32 venकरोr;
	__u32 product;
	__u32 version;
	__u32 country;
पूर्ण __attribute__((__packed__));

/* Obsolete! Use UHID_INPUT2. */
काष्ठा uhid_input_req अणु
	__u8 data[UHID_DATA_MAX];
	__u16 size;
पूर्ण __attribute__((__packed__));

/* Obsolete! Kernel uses UHID_OUTPUT exclusively now. */
काष्ठा uhid_output_ev_req अणु
	__u16 type;
	__u16 code;
	__s32 value;
पूर्ण __attribute__((__packed__));

/* Obsolete! Kernel uses ABI compatible UHID_GET_REPORT. */
काष्ठा uhid_feature_req अणु
	__u32 id;
	__u8 rnum;
	__u8 rtype;
पूर्ण __attribute__((__packed__));

/* Obsolete! Use ABI compatible UHID_GET_REPORT_REPLY. */
काष्ठा uhid_feature_answer_req अणु
	__u32 id;
	__u16 err;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
पूर्ण __attribute__((__packed__));

/*
 * UHID Events
 * All UHID events from and to the kernel are encoded as "struct uhid_event".
 * The "type" field contains a UHID_* type identअगरier. All payload depends on
 * that type and can be accessed via ev->u.XYZ accordingly.
 * If user-space ग_लिखोs लघु events, they're extended with 0s by the kernel. If
 * the kernel ग_लिखोs लघु events, user-space shall extend them with 0s.
 */

काष्ठा uhid_event अणु
	__u32 type;

	जोड़ अणु
		काष्ठा uhid_create_req create;
		काष्ठा uhid_input_req input;
		काष्ठा uhid_output_req output;
		काष्ठा uhid_output_ev_req output_ev;
		काष्ठा uhid_feature_req feature;
		काष्ठा uhid_get_report_req get_report;
		काष्ठा uhid_feature_answer_req feature_answer;
		काष्ठा uhid_get_report_reply_req get_report_reply;
		काष्ठा uhid_create2_req create2;
		काष्ठा uhid_input2_req input2;
		काष्ठा uhid_set_report_req set_report;
		काष्ठा uhid_set_report_reply_req set_report_reply;
		काष्ठा uhid_start_req start;
	पूर्ण u;
पूर्ण __attribute__((__packed__));

#पूर्ण_अगर /* __UHID_H_ */
