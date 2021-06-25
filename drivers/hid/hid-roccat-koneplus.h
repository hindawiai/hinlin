<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_KONEPLUS_H
#घोषणा __HID_ROCCAT_KONEPLUS_H

/*
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

क्रमागत अणु
	KONEPLUS_SIZE_ACTUAL_PROखाता = 0x03,
	KONEPLUS_SIZE_CONTROL = 0x03,
	KONEPLUS_SIZE_FIRMWARE_WRITE = 0x0402,
	KONEPLUS_SIZE_INFO = 0x06,
	KONEPLUS_SIZE_MACRO = 0x0822,
	KONEPLUS_SIZE_PROखाता_SETTINGS = 0x2b,
	KONEPLUS_SIZE_PROखाता_BUTTONS = 0x4d,
	KONEPLUS_SIZE_SENSOR = 0x06,
	KONEPLUS_SIZE_TALK = 0x10,
	KONEPLUS_SIZE_TCU = 0x04,
	KONEPLUS_SIZE_TCU_IMAGE = 0x0404,
पूर्ण;

क्रमागत koneplus_control_requests अणु
	KONEPLUS_CONTROL_REQUEST_PROखाता_SETTINGS = 0x80,
	KONEPLUS_CONTROL_REQUEST_PROखाता_BUTTONS = 0x90,
पूर्ण;

काष्ठा koneplus_actual_profile अणु
	uपूर्णांक8_t command; /* KONEPLUS_COMMAND_ACTUAL_PROखाता */
	uपूर्णांक8_t size; /* always 3 */
	uपूर्णांक8_t actual_profile; /* Range 0-4! */
पूर्ण __attribute__ ((__packed__));

काष्ठा koneplus_info अणु
	uपूर्णांक8_t command; /* KONEPLUS_COMMAND_INFO */
	uपूर्णांक8_t size; /* always 6 */
	uपूर्णांक8_t firmware_version;
	uपूर्णांक8_t unknown[3];
पूर्ण __attribute__ ((__packed__));

क्रमागत koneplus_commands अणु
	KONEPLUS_COMMAND_ACTUAL_PROखाता = 0x5,
	KONEPLUS_COMMAND_CONTROL = 0x4,
	KONEPLUS_COMMAND_PROखाता_SETTINGS = 0x6,
	KONEPLUS_COMMAND_PROखाता_BUTTONS = 0x7,
	KONEPLUS_COMMAND_MACRO = 0x8,
	KONEPLUS_COMMAND_INFO = 0x9,
	KONEPLUS_COMMAND_TCU = 0xc,
	KONEPLUS_COMMAND_TCU_IMAGE = 0xc,
	KONEPLUS_COMMAND_E = 0xe,
	KONEPLUS_COMMAND_SENSOR = 0xf,
	KONEPLUS_COMMAND_TALK = 0x10,
	KONEPLUS_COMMAND_FIRMWARE_WRITE = 0x1b,
	KONEPLUS_COMMAND_FIRMWARE_WRITE_CONTROL = 0x1c,
पूर्ण;

क्रमागत koneplus_mouse_report_numbers अणु
	KONEPLUS_MOUSE_REPORT_NUMBER_HID = 1,
	KONEPLUS_MOUSE_REPORT_NUMBER_AUDIO = 2,
	KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON = 3,
पूर्ण;

काष्ठा koneplus_mouse_report_button अणु
	uपूर्णांक8_t report_number; /* always KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON */
	uपूर्णांक8_t zero1;
	uपूर्णांक8_t type;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
	uपूर्णांक8_t zero2;
	uपूर्णांक8_t unknown[2];
पूर्ण __attribute__ ((__packed__));

क्रमागत koneplus_mouse_report_button_types अणु
	/* data1 = new profile range 1-5 */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता = 0x20,

	/* data1 = button number range 1-24; data2 = action */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH = 0x60,

	/* data1 = button number range 1-24; data2 = action */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_TIMER = 0x80,

	/* data1 = setting number range 1-5 */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = range 0x1-0xb */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	/* data1 = 22 = next track...
	 * data2 = action
	 */
	KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_MULTIMEDIA = 0xf0,
	KONEPLUS_MOUSE_REPORT_TALK = 0xff,
पूर्ण;

क्रमागत koneplus_mouse_report_button_action अणु
	KONEPLUS_MOUSE_REPORT_BUTTON_ACTION_PRESS = 0,
	KONEPLUS_MOUSE_REPORT_BUTTON_ACTION_RELEASE = 1,
पूर्ण;

काष्ठा koneplus_roccat_report अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
	uपूर्णांक8_t profile;
पूर्ण __attribute__ ((__packed__));

काष्ठा koneplus_device अणु
	पूर्णांक actual_profile;

	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;

	काष्ठा mutex koneplus_lock;
पूर्ण;

#पूर्ण_अगर
