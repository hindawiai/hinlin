<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 1996-2000 Vojtech Pavlik
 *
 *  Sponsored by SuSE
 */
/*
 */
#अगर_अघोषित _LINUX_JOYSTICK_H
#घोषणा _LINUX_JOYSTICK_H

#समावेश <uapi/linux/joystick.h>

#अगर BITS_PER_LONG == 64
#घोषणा JS_DATA_SAVE_TYPE JS_DATA_SAVE_TYPE_64
#या_अगर BITS_PER_LONG == 32
#घोषणा JS_DATA_SAVE_TYPE JS_DATA_SAVE_TYPE_32
#अन्यथा
#त्रुटि Unexpected BITS_PER_LONG
#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_JOYSTICK_H */
