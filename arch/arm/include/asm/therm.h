<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/therm.h: Definitions क्रम Dallas Semiconductor
 *  DS1620 thermometer driver (as used in the Rebel.com NetWinder)
 */
#अगर_अघोषित __ASM_THERM_H
#घोषणा __ASM_THERM_H

/* ioctl numbers क्रम /dev/therm */
#घोषणा CMD_SET_THERMOSTATE	0x53
#घोषणा CMD_GET_THERMOSTATE	0x54
#घोषणा CMD_GET_STATUS		0x56
#घोषणा CMD_GET_TEMPERATURE	0x57
#घोषणा CMD_SET_THERMOSTATE2	0x58
#घोषणा CMD_GET_THERMOSTATE2	0x59
#घोषणा CMD_GET_TEMPERATURE2	0x5a
#घोषणा CMD_GET_FAN		0x5b
#घोषणा CMD_SET_FAN		0x5c

#घोषणा FAN_OFF			0
#घोषणा FAN_ON			1
#घोषणा FAN_ALWAYS_ON		2

काष्ठा therm अणु
	पूर्णांक hi;
	पूर्णांक lo;
पूर्ण;

#पूर्ण_अगर
