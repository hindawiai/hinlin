<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_ISKU_H
#घोषणा __HID_ROCCAT_ISKU_H

/*
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

क्रमागत अणु
	ISKU_SIZE_CONTROL = 0x03,
	ISKU_SIZE_INFO = 0x06,
	ISKU_SIZE_KEY_MASK = 0x06,
	ISKU_SIZE_KEYS_FUNCTION = 0x29,
	ISKU_SIZE_KEYS_EASYZONE = 0x41,
	ISKU_SIZE_KEYS_MEDIA = 0x1d,
	ISKU_SIZE_KEYS_THUMBSTER = 0x17,
	ISKU_SIZE_KEYS_MACRO = 0x23,
	ISKU_SIZE_KEYS_CAPSLOCK = 0x06,
	ISKU_SIZE_LAST_SET = 0x14,
	ISKU_SIZE_LIGHT = 0x10,
	ISKU_SIZE_MACRO = 0x823,
	ISKU_SIZE_RESET = 0x03,
	ISKU_SIZE_TALK = 0x10,
	ISKU_SIZE_TALKFX = 0x10,
पूर्ण;

क्रमागत अणु
	ISKU_PROखाता_NUM = 5,
	ISKU_USB_INTERFACE_PROTOCOL = 0,
पूर्ण;

काष्ठा isku_actual_profile अणु
	uपूर्णांक8_t command; /* ISKU_COMMAND_ACTUAL_PROखाता */
	uपूर्णांक8_t size; /* always 3 */
	uपूर्णांक8_t actual_profile;
पूर्ण __packed;

क्रमागत isku_commands अणु
	ISKU_COMMAND_CONTROL = 0x4,
	ISKU_COMMAND_ACTUAL_PROखाता = 0x5,
	ISKU_COMMAND_KEY_MASK = 0x7,
	ISKU_COMMAND_KEYS_FUNCTION = 0x8,
	ISKU_COMMAND_KEYS_EASYZONE = 0x9,
	ISKU_COMMAND_KEYS_MEDIA = 0xa,
	ISKU_COMMAND_KEYS_THUMBSTER = 0xb,
	ISKU_COMMAND_KEYS_MACRO = 0xd,
	ISKU_COMMAND_MACRO = 0xe,
	ISKU_COMMAND_INFO = 0xf,
	ISKU_COMMAND_LIGHT = 0x10,
	ISKU_COMMAND_RESET = 0x11,
	ISKU_COMMAND_KEYS_CAPSLOCK = 0x13,
	ISKU_COMMAND_LAST_SET = 0x14,
	ISKU_COMMAND_15 = 0x15,
	ISKU_COMMAND_TALK = 0x16,
	ISKU_COMMAND_TALKFX = 0x17,
	ISKU_COMMAND_FIRMWARE_WRITE = 0x1b,
	ISKU_COMMAND_FIRMWARE_WRITE_CONTROL = 0x1c,
पूर्ण;

काष्ठा isku_report_button अणु
	uपूर्णांक8_t number; /* ISKU_REPORT_NUMBER_BUTTON */
	uपूर्णांक8_t zero;
	uपूर्णांक8_t event;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
पूर्ण;

क्रमागत isku_report_numbers अणु
	ISKU_REPORT_NUMBER_BUTTON = 3,
पूर्ण;

क्रमागत isku_report_button_events अणु
	ISKU_REPORT_BUTTON_EVENT_PROखाता = 0x2,
पूर्ण;

काष्ठा isku_roccat_report अणु
	uपूर्णांक8_t event;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
	uपूर्णांक8_t profile;
पूर्ण __packed;

काष्ठा isku_device अणु
	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;

	काष्ठा mutex isku_lock;

	पूर्णांक actual_profile;
पूर्ण;

#पूर्ण_अगर
