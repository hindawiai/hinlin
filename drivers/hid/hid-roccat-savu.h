<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_SAVU_H
#घोषणा __HID_ROCCAT_SAVU_H

/*
 * Copyright (c) 2012 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

काष्ठा savu_mouse_report_special अणु
	uपूर्णांक8_t report_number; /* always 3 */
	uपूर्णांक8_t zero;
	uपूर्णांक8_t type;
	uपूर्णांक8_t data[2];
पूर्ण __packed;

क्रमागत अणु
	SAVU_MOUSE_REPORT_NUMBER_SPECIAL = 3,
पूर्ण;

क्रमागत savu_mouse_report_button_types अणु
	/* data1 = new profile range 1-5 */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_PROखाता = 0x20,

	/* data1 = button number range 1-24; data2 = action */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH = 0x60,

	/* data1 = button number range 1-24; data2 = action */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_TIMER = 0x80,

	/* data1 = setting number range 1-5 */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = range 0x1-0xb */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	/* data1 = 22 = next track...
	 * data2 = action
	 */
	SAVU_MOUSE_REPORT_BUTTON_TYPE_MULTIMEDIA = 0xf0,
पूर्ण;

काष्ठा savu_roccat_report अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t data[2];
पूर्ण __packed;

#पूर्ण_अगर
