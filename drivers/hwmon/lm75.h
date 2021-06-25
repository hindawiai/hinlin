<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lm75.h - Part of lm_sensors, Linux kernel modules क्रम hardware monitoring
 * Copyright (c) 2003 Mark M. Hoffman <mhoffman@lightlink.com>
 */

/*
 * This file contains common code क्रम encoding/decoding LM75 type
 * temperature पढ़ोings, which are emulated by many of the chips
 * we support.  As the user is unlikely to load more than one driver
 * which contains this code, we करोn't worry about the wasted space.
 */

#समावेश <linux/kernel.h>

/* straight from the datasheet */
#घोषणा LM75_TEMP_MIN (-55000)
#घोषणा LM75_TEMP_MAX 125000
#घोषणा LM75_SHUTDOWN 0x01

/*
 * TEMP: 0.001C/bit (-55C to +125C)
 * REG: (0.5C/bit, two's complement) << 7
 */
अटल अंतरभूत u16 LM75_TEMP_TO_REG(दीर्घ temp)
अणु
	पूर्णांक ntemp = clamp_val(temp, LM75_TEMP_MIN, LM75_TEMP_MAX);

	ntemp += (ntemp < 0 ? -250 : 250);
	वापस (u16)((ntemp / 500) << 7);
पूर्ण

अटल अंतरभूत पूर्णांक LM75_TEMP_FROM_REG(u16 reg)
अणु
	/*
	 * use पूर्णांकeger भागision instead of equivalent right shअगरt to
	 * guarantee arithmetic shअगरt and preserve the sign
	 */
	वापस ((s16)reg / 128) * 500;
पूर्ण
