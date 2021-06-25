<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_KOVAPLUS_H
#घोषणा __HID_ROCCAT_KOVAPLUS_H

/*
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

क्रमागत अणु
	KOVAPLUS_SIZE_CONTROL = 0x03,
	KOVAPLUS_SIZE_INFO = 0x06,
	KOVAPLUS_SIZE_PROखाता_SETTINGS = 0x10,
	KOVAPLUS_SIZE_PROखाता_BUTTONS = 0x17,
पूर्ण;

क्रमागत kovaplus_control_requests अणु
	/* ग_लिखो; value = profile number range 0-4 */
	KOVAPLUS_CONTROL_REQUEST_PROखाता_SETTINGS = 0x10,
	/* ग_लिखो; value = profile number range 0-4 */
	KOVAPLUS_CONTROL_REQUEST_PROखाता_BUTTONS = 0x20,
पूर्ण;

काष्ठा kovaplus_actual_profile अणु
	uपूर्णांक8_t command; /* KOVAPLUS_COMMAND_ACTUAL_PROखाता */
	uपूर्णांक8_t size; /* always 3 */
	uपूर्णांक8_t actual_profile; /* Range 0-4! */
पूर्ण __packed;

काष्ठा kovaplus_profile_settings अणु
	uपूर्णांक8_t command; /* KOVAPLUS_COMMAND_PROखाता_SETTINGS */
	uपूर्णांक8_t size; /* 16 */
	uपूर्णांक8_t profile_index; /* range 0-4 */
	uपूर्णांक8_t unknown1;
	uपूर्णांक8_t sensitivity_x; /* range 1-10 */
	uपूर्णांक8_t sensitivity_y; /* range 1-10 */
	uपूर्णांक8_t cpi_levels_enabled;
	uपूर्णांक8_t cpi_startup_level; /* range 1-4 */
	uपूर्णांक8_t data[8];
पूर्ण __packed;

काष्ठा kovaplus_profile_buttons अणु
	uपूर्णांक8_t command; /* KOVAPLUS_COMMAND_PROखाता_BUTTONS */
	uपूर्णांक8_t size; /* 23 */
	uपूर्णांक8_t profile_index; /* range 0-4 */
	uपूर्णांक8_t data[20];
पूर्ण __packed;

काष्ठा kovaplus_info अणु
	uपूर्णांक8_t command; /* KOVAPLUS_COMMAND_INFO */
	uपूर्णांक8_t size; /* 6 */
	uपूर्णांक8_t firmware_version;
	uपूर्णांक8_t unknown[3];
पूर्ण __packed;

क्रमागत kovaplus_commands अणु
	KOVAPLUS_COMMAND_ACTUAL_PROखाता = 0x5,
	KOVAPLUS_COMMAND_CONTROL = 0x4,
	KOVAPLUS_COMMAND_PROखाता_SETTINGS = 0x6,
	KOVAPLUS_COMMAND_PROखाता_BUTTONS = 0x7,
	KOVAPLUS_COMMAND_INFO = 0x9,
	KOVAPLUS_COMMAND_A = 0xa,
पूर्ण;

क्रमागत kovaplus_mouse_report_numbers अणु
	KOVAPLUS_MOUSE_REPORT_NUMBER_MOUSE = 1,
	KOVAPLUS_MOUSE_REPORT_NUMBER_AUDIO = 2,
	KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON = 3,
	KOVAPLUS_MOUSE_REPORT_NUMBER_KBD = 4,
पूर्ण;

काष्ठा kovaplus_mouse_report_button अणु
	uपूर्णांक8_t report_number; /* KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON */
	uपूर्णांक8_t unknown1;
	uपूर्णांक8_t type;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
पूर्ण __packed;

क्रमागत kovaplus_mouse_report_button_types अणु
	/* data1 = profile_number range 1-5; no release event */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता_1 = 0x20,
	/* data1 = profile_number range 1-5; no release event */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता_2 = 0x30,
	/* data1 = button_number range 1-18; data2 = action */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_MACRO = 0x40,
	/* data1 = button_number range 1-18; data2 = action */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SHORTCUT = 0x50,
	/* data1 = button_number range 1-18; data2 = action */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH = 0x60,
	/* data1 = button_number range 1-18; data2 = action */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_TIMER = 0x80,
	/* data1 = 1 = 400, 2 = 800, 4 = 1600, 7 = 3200; no release event */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI = 0xb0,
	/* data1 + data2 = sense range 1-10; no release event */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY = 0xc0,
	/* data1 = type as in profile_buttons; data2 = action */
	KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_MULTIMEDIA = 0xf0,
पूर्ण;

क्रमागत kovaplus_mouse_report_button_actions अणु
	KOVAPLUS_MOUSE_REPORT_BUTTON_ACTION_PRESS = 0,
	KOVAPLUS_MOUSE_REPORT_BUTTON_ACTION_RELEASE = 1,
पूर्ण;

काष्ठा kovaplus_roccat_report अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t profile;
	uपूर्णांक8_t button;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
पूर्ण __packed;

काष्ठा kovaplus_device अणु
	पूर्णांक actual_profile;
	पूर्णांक actual_cpi;
	पूर्णांक actual_x_sensitivity;
	पूर्णांक actual_y_sensitivity;
	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;
	काष्ठा mutex kovaplus_lock;
	काष्ठा kovaplus_profile_settings profile_settings[5];
	काष्ठा kovaplus_profile_buttons profile_buttons[5];
पूर्ण;

#पूर्ण_अगर
