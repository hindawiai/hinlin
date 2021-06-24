<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_ARVO_H
#घोषणा __HID_ROCCAT_ARVO_H

/*
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

काष्ठा arvo_mode_key अणु /* 2 bytes */
	uपूर्णांक8_t command; /* ARVO_COMMAND_MODE_KEY */
	uपूर्णांक8_t state;
पूर्ण __packed;

काष्ठा arvo_button अणु
	uपूर्णांक8_t unknown[24];
पूर्ण __packed;

काष्ठा arvo_info अणु
	uपूर्णांक8_t unknown[8];
पूर्ण __packed;

काष्ठा arvo_key_mask अणु /* 2 bytes */
	uपूर्णांक8_t command; /* ARVO_COMMAND_KEY_MASK */
	uपूर्णांक8_t key_mask;
पूर्ण __packed;

/* selected profile is persistent */
काष्ठा arvo_actual_profile अणु /* 2 bytes */
	uपूर्णांक8_t command; /* ARVO_COMMAND_ACTUAL_PROखाता */
	uपूर्णांक8_t actual_profile;
पूर्ण __packed;

क्रमागत arvo_commands अणु
	ARVO_COMMAND_MODE_KEY = 0x3,
	ARVO_COMMAND_BUTTON = 0x4,
	ARVO_COMMAND_INFO = 0x5,
	ARVO_COMMAND_KEY_MASK = 0x6,
	ARVO_COMMAND_ACTUAL_PROखाता = 0x7,
पूर्ण;

काष्ठा arvo_special_report अणु
	uपूर्णांक8_t unknown1; /* always 0x01 */
	uपूर्णांक8_t event;
	uपूर्णांक8_t unknown2; /* always 0x70 */
पूर्ण __packed;

क्रमागत arvo_special_report_events अणु
	ARVO_SPECIAL_REPORT_EVENT_ACTION_PRESS = 0x10,
	ARVO_SPECIAL_REPORT_EVENT_ACTION_RELEASE = 0x0,
पूर्ण;

क्रमागत arvo_special_report_event_masks अणु
	ARVO_SPECIAL_REPORT_EVENT_MASK_ACTION = 0xf0,
	ARVO_SPECIAL_REPORT_EVENT_MASK_BUTTON = 0x0f,
पूर्ण;

काष्ठा arvo_roccat_report अणु
	uपूर्णांक8_t profile;
	uपूर्णांक8_t button;
	uपूर्णांक8_t action;
पूर्ण __packed;

क्रमागत arvo_roccat_report_action अणु
	ARVO_ROCCAT_REPORT_ACTION_RELEASE = 0,
	ARVO_ROCCAT_REPORT_ACTION_PRESS = 1,
पूर्ण;

काष्ठा arvo_device अणु
	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;

	काष्ठा mutex arvo_lock;

	पूर्णांक actual_profile;
पूर्ण;

#पूर्ण_अगर
