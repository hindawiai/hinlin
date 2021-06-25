<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_KONE_H
#घोषणा __HID_ROCCAT_KONE_H

/*
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/types.h>

काष्ठा kone_keystroke अणु
	uपूर्णांक8_t key;
	uपूर्णांक8_t action;
	uपूर्णांक16_t period; /* in milliseconds */
पूर्ण __attribute__ ((__packed__));

क्रमागत kone_keystroke_buttons अणु
	kone_keystroke_button_1 = 0xf0, /* left mouse button */
	kone_keystroke_button_2 = 0xf1, /* right mouse button */
	kone_keystroke_button_3 = 0xf2, /* wheel */
	kone_keystroke_button_9 = 0xf3, /* side button up */
	kone_keystroke_button_8 = 0xf4 /* side button करोwn */
पूर्ण;

क्रमागत kone_keystroke_actions अणु
	kone_keystroke_action_press = 0,
	kone_keystroke_action_release = 1
पूर्ण;

काष्ठा kone_button_info अणु
	uपूर्णांक8_t number; /* range 1-8 */
	uपूर्णांक8_t type;
	uपूर्णांक8_t macro_type; /* 0 = लघु, 1 = overदीर्घ */
	uपूर्णांक8_t macro_set_name[16]; /* can be max 15 अक्षरs दीर्घ */
	uपूर्णांक8_t macro_name[16]; /* can be max 15 अक्षरs दीर्घ */
	uपूर्णांक8_t count;
	काष्ठा kone_keystroke keystrokes[20];
पूर्ण __attribute__ ((__packed__));

क्रमागत kone_button_info_types अणु
	/* valid button types until firmware 1.32 */
	kone_button_info_type_button_1 = 0x1, /* click (left mouse button) */
	kone_button_info_type_button_2 = 0x2, /* menu (right mouse button)*/
	kone_button_info_type_button_3 = 0x3, /* scroll (wheel) */
	kone_button_info_type_द्विगुन_click = 0x4,
	kone_button_info_type_key = 0x5,
	kone_button_info_type_macro = 0x6,
	kone_button_info_type_off = 0x7,
	/* TODO clarअगरy function and नाम */
	kone_button_info_type_osd_xy_prescaling = 0x8,
	kone_button_info_type_osd_dpi = 0x9,
	kone_button_info_type_osd_profile = 0xa,
	kone_button_info_type_button_9 = 0xb, /* ie क्रमward */
	kone_button_info_type_button_8 = 0xc, /* ie backward */
	kone_button_info_type_dpi_up = 0xd, /* पूर्णांकernal */
	kone_button_info_type_dpi_करोwn = 0xe, /* पूर्णांकernal */
	kone_button_info_type_button_7 = 0xf, /* tilt left */
	kone_button_info_type_button_6 = 0x10, /* tilt right */
	kone_button_info_type_profile_up = 0x11, /* पूर्णांकernal */
	kone_button_info_type_profile_करोwn = 0x12, /* पूर्णांकernal */
	/* additional valid button types since firmware 1.38 */
	kone_button_info_type_mulसमयdia_खोलो_player = 0x20,
	kone_button_info_type_mulसमयdia_next_track = 0x21,
	kone_button_info_type_mulसमयdia_prev_track = 0x22,
	kone_button_info_type_mulसमयdia_play_छोड़ो = 0x23,
	kone_button_info_type_mulसमयdia_stop = 0x24,
	kone_button_info_type_mulसमयdia_mute = 0x25,
	kone_button_info_type_mulसमयdia_volume_up = 0x26,
	kone_button_info_type_mulसमयdia_volume_करोwn = 0x27
पूर्ण;

क्रमागत kone_button_info_numbers अणु
	kone_button_top = 1,
	kone_button_wheel_tilt_left = 2,
	kone_button_wheel_tilt_right = 3,
	kone_button_क्रमward = 4,
	kone_button_backward = 5,
	kone_button_middle = 6,
	kone_button_plus = 7,
	kone_button_minus = 8,
पूर्ण;

काष्ठा kone_light_info अणु
	uपूर्णांक8_t number; /* number of light 1-5 */
	uपूर्णांक8_t mod;   /* 1 = on, 2 = off */
	uपूर्णांक8_t red;   /* range 0x00-0xff */
	uपूर्णांक8_t green; /* range 0x00-0xff */
	uपूर्णांक8_t blue;  /* range 0x00-0xff */
पूर्ण __attribute__ ((__packed__));

काष्ठा kone_profile अणु
	uपूर्णांक16_t size; /* always 975 */
	uपूर्णांक16_t unused; /* always 0 */

	/*
	 * range 1-5
	 * This number करोes not need to correspond with location where profile
	 * saved
	 */
	uपूर्णांक8_t profile; /* range 1-5 */

	uपूर्णांक16_t मुख्य_sensitivity; /* range 100-1000 */
	uपूर्णांक8_t xy_sensitivity_enabled; /* 1 = on, 2 = off */
	uपूर्णांक16_t x_sensitivity; /* range 100-1000 */
	uपूर्णांक16_t y_sensitivity; /* range 100-1000 */
	uपूर्णांक8_t dpi_rate; /* bit 1 = 800, ... */
	uपूर्णांक8_t startup_dpi; /* range 1-6 */
	uपूर्णांक8_t polling_rate; /* 1 = 125Hz, 2 = 500Hz, 3 = 1000Hz */
	/* kone has no dcu
	 * value is always 2 in firmwares <= 1.32 and
	 * 1 in firmwares > 1.32
	 */
	uपूर्णांक8_t dcu_flag;
	uपूर्णांक8_t light_effect_1; /* range 1-3 */
	uपूर्णांक8_t light_effect_2; /* range 1-5 */
	uपूर्णांक8_t light_effect_3; /* range 1-4 */
	uपूर्णांक8_t light_effect_speed; /* range 0-255 */

	काष्ठा kone_light_info light_infos[5];
	/* offset is kone_button_info_numbers - 1 */
	काष्ठा kone_button_info button_infos[8];

	uपूर्णांक16_t checksum; /* \मrief holds checksum of काष्ठा */
पूर्ण __attribute__ ((__packed__));

क्रमागत kone_polling_rates अणु
	kone_polling_rate_125 = 1,
	kone_polling_rate_500 = 2,
	kone_polling_rate_1000 = 3
पूर्ण;

काष्ठा kone_settings अणु
	uपूर्णांक16_t size; /* always 36 */
	uपूर्णांक8_t  startup_profile; /* 1-5 */
	uपूर्णांक8_t	 unknown1;
	uपूर्णांक8_t  tcu; /* 0 = off, 1 = on */
	uपूर्णांक8_t  unknown2[23];
	uपूर्णांक8_t  calibration_data[4];
	uपूर्णांक8_t  unknown3[2];
	uपूर्णांक16_t checksum;
पूर्ण __attribute__ ((__packed__));

/*
 * 12 byte mouse event पढ़ो by पूर्णांकerrupt_पढ़ो
 */
काष्ठा kone_mouse_event अणु
	uपूर्णांक8_t report_number; /* always 1 */
	uपूर्णांक8_t button;
	uपूर्णांक16_t x;
	uपूर्णांक16_t y;
	uपूर्णांक8_t wheel; /* up = 1, करोwn = -1 */
	uपूर्णांक8_t tilt; /* right = 1, left = -1 */
	uपूर्णांक8_t unknown;
	uपूर्णांक8_t event;
	uपूर्णांक8_t value; /* press = 0, release = 1 */
	uपूर्णांक8_t macro_key; /* 0 to 8 */
पूर्ण __attribute__ ((__packed__));

क्रमागत kone_mouse_events अणु
	/* osd events are thought to be display on screen */
	kone_mouse_event_osd_dpi = 0xa0,
	kone_mouse_event_osd_profile = 0xb0,
	/* TODO clarअगरy meaning and occurence of kone_mouse_event_calibration */
	kone_mouse_event_calibration = 0xc0,
	kone_mouse_event_call_overदीर्घ_macro = 0xe0,
	kone_mouse_event_mulसमयdia = 0xe1,
	/* चयन events notअगरy अगर user changed values with mousebutton click */
	kone_mouse_event_चयन_dpi = 0xf0,
	kone_mouse_event_चयन_profile = 0xf1
पूर्ण;

क्रमागत kone_commands अणु
	kone_command_profile = 0x5a,
	kone_command_settings = 0x15a,
	kone_command_firmware_version = 0x25a,
	kone_command_weight = 0x45a,
	kone_command_calibrate = 0x55a,
	kone_command_confirm_ग_लिखो = 0x65a,
	kone_command_firmware = 0xe5a
पूर्ण;

काष्ठा kone_roccat_report अणु
	uपूर्णांक8_t event;
	uपूर्णांक8_t value; /* holds dpi or profile value */
	uपूर्णांक8_t key; /* macro key on overदीर्घ macro execution */
पूर्ण __attribute__ ((__packed__));

काष्ठा kone_device अणु
	/*
	 * Storing actual values when we get inक्रमmed about changes since there
	 * is no way of getting this inक्रमmation from the device on demand
	 */
	पूर्णांक actual_profile, actual_dpi;
	/* Used क्रम neutralizing abnormal button behaviour */
	काष्ठा kone_mouse_event last_mouse_event;

	/*
	 * It's unlikely that multiple sysfs attributes are accessed at a समय,
	 * so only one mutex is used to secure hardware access and profiles and
	 * settings of this काष्ठा.
	 */
	काष्ठा mutex kone_lock;

	/*
	 * Storing the data here reduces IO and ensures that data is available
	 * when its needed (E.g. पूर्णांकerrupt handler).
	 */
	काष्ठा kone_profile profiles[5];
	काष्ठा kone_settings settings;

	/*
	 * firmware करोesn't change unless firmware update is implemented,
	 * so it's पढ़ो only once
	 */
	पूर्णांक firmware_version;

	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;
पूर्ण;

#पूर्ण_अगर
