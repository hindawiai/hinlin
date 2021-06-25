<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  HID driver क्रम UC-Logic devices not fully compliant with HID standard
 *  - original and fixed report descriptors
 *
 *  Copyright (c) 2010-2018 Nikolai Kondrashov
 *  Copyright (c) 2013 Martin Rusko
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#अगर_अघोषित _HID_UCLOGIC_RDESC_H
#घोषणा _HID_UCLOGIC_RDESC_H

#समावेश <linux/usb.h>

/* Size of the original descriptor of WPXXXXU tablets */
#घोषणा UCLOGIC_RDESC_WPXXXXU_ORIG_SIZE		212

/* Fixed WP4030U report descriptor */
बाह्य __u8 uclogic_rdesc_wp4030u_fixed_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_wp4030u_fixed_size;

/* Fixed WP5540U report descriptor */
बाह्य __u8 uclogic_rdesc_wp5540u_fixed_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_wp5540u_fixed_size;

/* Fixed WP8060U report descriptor */
बाह्य __u8 uclogic_rdesc_wp8060u_fixed_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_wp8060u_fixed_size;

/* Size of the original descriptor of the new WP5540U tablet */
#घोषणा UCLOGIC_RDESC_WP5540U_V2_ORIG_SIZE	232

/* Size of the original descriptor of WP1062 tablet */
#घोषणा UCLOGIC_RDESC_WP1062_ORIG_SIZE		254

/* Fixed WP1062 report descriptor */
बाह्य __u8 uclogic_rdesc_wp1062_fixed_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_wp1062_fixed_size;

/* Size of the original descriptor of PF1209 tablet */
#घोषणा UCLOGIC_RDESC_PF1209_ORIG_SIZE		234

/* Fixed PF1209 report descriptor */
बाह्य __u8 uclogic_rdesc_pf1209_fixed_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_pf1209_fixed_size;

/* Size of the original descriptors of TWHL850 tablet */
#घोषणा UCLOGIC_RDESC_TWHL850_ORIG0_SIZE	182
#घोषणा UCLOGIC_RDESC_TWHL850_ORIG1_SIZE	161
#घोषणा UCLOGIC_RDESC_TWHL850_ORIG2_SIZE	92

/* Fixed PID 0522 tablet report descriptor, पूर्णांकerface 0 (stylus) */
बाह्य __u8 uclogic_rdesc_twhl850_fixed0_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_twhl850_fixed0_size;

/* Fixed PID 0522 tablet report descriptor, पूर्णांकerface 1 (mouse) */
बाह्य __u8 uclogic_rdesc_twhl850_fixed1_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_twhl850_fixed1_size;

/* Fixed PID 0522 tablet report descriptor, पूर्णांकerface 2 (frame buttons) */
बाह्य __u8 uclogic_rdesc_twhl850_fixed2_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_twhl850_fixed2_size;

/* Size of the original descriptors of TWHA60 tablet */
#घोषणा UCLOGIC_RDESC_TWHA60_ORIG0_SIZE		254
#घोषणा UCLOGIC_RDESC_TWHA60_ORIG1_SIZE		139

/* Fixed TWHA60 report descriptor, पूर्णांकerface 0 (stylus) */
बाह्य __u8 uclogic_rdesc_twha60_fixed0_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_twha60_fixed0_size;

/* Fixed TWHA60 report descriptor, पूर्णांकerface 1 (frame buttons) */
बाह्य __u8 uclogic_rdesc_twha60_fixed1_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_twha60_fixed1_size;

/* Report descriptor ढाँचा placeholder head */
#घोषणा UCLOGIC_RDESC_PH_HEAD	0xFE, 0xED, 0x1D

/* Apply report descriptor parameters to a report descriptor ढाँचा */
बाह्य __u8 *uclogic_rdesc_ढाँचा_apply(स्थिर __u8 *ढाँचा_ptr,
					  माप_प्रकार ढाँचा_size,
					  स्थिर s32 *param_list,
					  माप_प्रकार param_num);

/* Pen report descriptor ढाँचा placeholder IDs */
क्रमागत uclogic_rdesc_pen_ph_id अणु
	UCLOGIC_RDESC_PEN_PH_ID_X_LM,
	UCLOGIC_RDESC_PEN_PH_ID_X_PM,
	UCLOGIC_RDESC_PEN_PH_ID_Y_LM,
	UCLOGIC_RDESC_PEN_PH_ID_Y_PM,
	UCLOGIC_RDESC_PEN_PH_ID_PRESSURE_LM,
	UCLOGIC_RDESC_PEN_PH_ID_NUM
पूर्ण;

/* Report descriptor pen ढाँचा placeholder */
#घोषणा UCLOGIC_RDESC_PEN_PH(_ID) \
	UCLOGIC_RDESC_PH_HEAD, UCLOGIC_RDESC_PEN_PH_ID_##_ID

/* Report ID क्रम v1 pen reports */
#घोषणा UCLOGIC_RDESC_PEN_V1_ID	0x07

/* Fixed report descriptor ढाँचा क्रम (tweaked) v1 pen reports */
बाह्य स्थिर __u8 uclogic_rdesc_pen_v1_ढाँचा_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_pen_v1_ढाँचा_size;

/* Report ID क्रम v2 pen reports */
#घोषणा UCLOGIC_RDESC_PEN_V2_ID	0x08

/* Fixed report descriptor ढाँचा क्रम (tweaked) v2 pen reports */
बाह्य स्थिर __u8 uclogic_rdesc_pen_v2_ढाँचा_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_pen_v2_ढाँचा_size;

/* Fixed report descriptor क्रम (tweaked) v1 buttonpad reports */
बाह्य स्थिर __u8 uclogic_rdesc_buttonpad_v1_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_buttonpad_v1_size;

/* Report ID क्रम tweaked v1 buttonpad reports */
#घोषणा UCLOGIC_RDESC_BUTTONPAD_V1_ID 0xf7

/* Fixed report descriptor क्रम (tweaked) v2 buttonpad reports */
बाह्य स्थिर __u8 uclogic_rdesc_buttonpad_v2_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_buttonpad_v2_size;

/* Report ID क्रम tweaked v2 buttonpad reports */
#घोषणा UCLOGIC_RDESC_BUTTONPAD_V2_ID 0xf7

/* Fixed report descriptor क्रम Ugee EX07 buttonpad */
बाह्य स्थिर __u8 uclogic_rdesc_ugee_ex07_buttonpad_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_ugee_ex07_buttonpad_size;

/* Fixed report descriptor क्रम XP-Pen Deco 01 frame controls */
बाह्य स्थिर __u8 uclogic_rdesc_xppen_deco01_frame_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_xppen_deco01_frame_size;

/* Fixed report descriptor क्रम Ugee G5 frame controls */
बाह्य स्थिर __u8 uclogic_rdesc_ugee_g5_frame_arr[];
बाह्य स्थिर माप_प्रकार uclogic_rdesc_ugee_g5_frame_size;

/* Report ID of Ugee G5 frame control reports */
#घोषणा UCLOGIC_RDESC_UGEE_G5_FRAME_ID 0x06

/* Device ID byte offset in Ugee G5 frame report */
#घोषणा UCLOGIC_RDESC_UGEE_G5_FRAME_DEV_ID_BYTE	0x2

/* Least-signअगरicant bit of Ugee G5 frame rotary encoder state */
#घोषणा UCLOGIC_RDESC_UGEE_G5_FRAME_RE_LSB 38

#पूर्ण_अगर /* _HID_UCLOGIC_RDESC_H */
