<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    hwmon-vid.h - VID/VRM/VRD voltage conversions

    Originally part of lm_sensors
    Copyright (c) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
    With assistance from Trent Piepho <xyzzy@speakeasy.org>

*/

#अगर_अघोषित _LINUX_HWMON_VID_H
#घोषणा _LINUX_HWMON_VID_H

पूर्णांक vid_from_reg(पूर्णांक val, u8 vrm);
u8 vid_which_vrm(व्योम);

/* vrm is the VRM/VRD करोcument version multiplied by 10.
   val is in mV to aव्योम भग्नing poपूर्णांक in the kernel.
   Returned value is the 4-, 5- or 6-bit VID code.
   Note that only VRM 9.x is supported क्रम now. */
अटल अंतरभूत पूर्णांक vid_to_reg(पूर्णांक val, u8 vrm)
अणु
	चयन (vrm) अणु
	हाल 91:		/* VRM 9.1 */
	हाल 90:		/* VRM 9.0 */
		वापस ((val >= 1100) && (val <= 1850) ?
			((18499 - val * 10) / 25 + 5) / 10 : -1);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _LINUX_HWMON_VID_H */
