<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_PYRA_H
#घोषणा __HID_ROCCAT_PYRA_H

/*
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

क्रमागत अणु
	PYRA_SIZE_CONTROL = 0x03,
	PYRA_SIZE_INFO = 0x06,
	PYRA_SIZE_PROखाता_SETTINGS = 0x0d,
	PYRA_SIZE_PROखाता_BUTTONS = 0x13,
	PYRA_SIZE_SETTINGS = 0x03,
पूर्ण;

क्रमागत pyra_control_requests अणु
	PYRA_CONTROL_REQUEST_PROखाता_SETTINGS = 0x10,
	PYRA_CONTROL_REQUEST_PROखाता_BUTTONS = 0x20
पूर्ण;

काष्ठा pyra_settings अणु
	uपूर्णांक8_t command; /* PYRA_COMMAND_SETTINGS */
	uपूर्णांक8_t size; /* always 3 */
	uपूर्णांक8_t startup_profile; /* Range 0-4! */
पूर्ण __attribute__ ((__packed__));

काष्ठा pyra_profile_settings अणु
	uपूर्णांक8_t command; /* PYRA_COMMAND_PROखाता_SETTINGS */
	uपूर्णांक8_t size; /* always 0xd */
	uपूर्णांक8_t number; /* Range 0-4 */
	uपूर्णांक8_t xysync;
	uपूर्णांक8_t x_sensitivity; /* 0x1-0xa */
	uपूर्णांक8_t y_sensitivity;
	uपूर्णांक8_t x_cpi; /* unused */
	uपूर्णांक8_t y_cpi; /* this value is क्रम x and y */
	uपूर्णांक8_t lightचयन; /* 0 = off, 1 = on */
	uपूर्णांक8_t light_effect;
	uपूर्णांक8_t handedness;
	uपूर्णांक16_t checksum; /* byte sum */
पूर्ण __attribute__ ((__packed__));

काष्ठा pyra_info अणु
	uपूर्णांक8_t command; /* PYRA_COMMAND_INFO */
	uपूर्णांक8_t size; /* always 6 */
	uपूर्णांक8_t firmware_version;
	uपूर्णांक8_t unknown1; /* always 0 */
	uपूर्णांक8_t unknown2; /* always 1 */
	uपूर्णांक8_t unknown3; /* always 0 */
पूर्ण __attribute__ ((__packed__));

क्रमागत pyra_commands अणु
	PYRA_COMMAND_CONTROL = 0x4,
	PYRA_COMMAND_SETTINGS = 0x5,
	PYRA_COMMAND_PROखाता_SETTINGS = 0x6,
	PYRA_COMMAND_PROखाता_BUTTONS = 0x7,
	PYRA_COMMAND_INFO = 0x9,
	PYRA_COMMAND_B = 0xb
पूर्ण;

क्रमागत pyra_mouse_report_numbers अणु
	PYRA_MOUSE_REPORT_NUMBER_HID = 1,
	PYRA_MOUSE_REPORT_NUMBER_AUDIO = 2,
	PYRA_MOUSE_REPORT_NUMBER_BUTTON = 3,
पूर्ण;

काष्ठा pyra_mouse_event_button अणु
	uपूर्णांक8_t report_number; /* always 3 */
	uपूर्णांक8_t unknown; /* always 0 */
	uपूर्णांक8_t type;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
पूर्ण __attribute__ ((__packed__));

काष्ठा pyra_mouse_event_audio अणु
	uपूर्णांक8_t report_number; /* always 2 */
	uपूर्णांक8_t type;
	uपूर्णांक8_t unused; /* always 0 */
पूर्ण __attribute__ ((__packed__));

/* hid audio controls */
क्रमागत pyra_mouse_event_audio_types अणु
	PYRA_MOUSE_EVENT_AUDIO_TYPE_MUTE = 0xe2,
	PYRA_MOUSE_EVENT_AUDIO_TYPE_VOLUME_UP = 0xe9,
	PYRA_MOUSE_EVENT_AUDIO_TYPE_VOLUME_DOWN = 0xea,
पूर्ण;

क्रमागत pyra_mouse_event_button_types अणु
	/*
	 * Mouse sends tilt events on report_number 1 and 3
	 * Tilt events are sent repeatedly with 0.94s between first and second
	 * event and 0.22s on subsequent
	 */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_TILT = 0x10,

	/*
	 * These are sent sequentially
	 * data1 contains new profile number in range 1-5
	 */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_PROखाता_1 = 0x20,
	PYRA_MOUSE_EVENT_BUTTON_TYPE_PROखाता_2 = 0x30,

	/*
	 * data1 = button_number (rmp index)
	 * data2 = pressed/released
	 */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_MACRO = 0x40,
	PYRA_MOUSE_EVENT_BUTTON_TYPE_SHORTCUT = 0x50,

	/*
	 * data1 = button_number (rmp index)
	 */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_QUICKLAUNCH = 0x60,

	/* data1 = new cpi */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = new sensitivity */
	PYRA_MOUSE_EVENT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	PYRA_MOUSE_EVENT_BUTTON_TYPE_MULTIMEDIA = 0xf0,
पूर्ण;

क्रमागत अणु
	PYRA_MOUSE_EVENT_BUTTON_PRESS = 0,
	PYRA_MOUSE_EVENT_BUTTON_RELEASE = 1,
पूर्ण;

काष्ठा pyra_roccat_report अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t value;
	uपूर्णांक8_t key;
पूर्ण __attribute__ ((__packed__));

काष्ठा pyra_device अणु
	पूर्णांक actual_profile;
	पूर्णांक actual_cpi;
	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;
	काष्ठा mutex pyra_lock;
	काष्ठा pyra_profile_settings profile_settings[5];
पूर्ण;

#पूर्ण_अगर
