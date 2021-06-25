<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    tvaudपन.स - definition क्रम tvaudio inमाला_दो

    Copyright (C) 2006 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _TVAUDIO_H
#घोषणा _TVAUDIO_H

/*
 * i2c bus addresses क्रम the chips supported by tvaudio.c
 */

#घोषणा I2C_ADDR_TDA8425	0x82
#घोषणा I2C_ADDR_TDA9840	0x84
#घोषणा I2C_ADDR_TDA9874	0xb0 /* also used by 9875 */
#घोषणा I2C_ADDR_TDA9875	0xb0
#घोषणा I2C_ADDR_TDA8425	0x82
#घोषणा I2C_ADDR_TDA9840	0x84 /* also used by TA8874Z */
#घोषणा I2C_ADDR_TDA985x_L	0xb4 /* also used by 9873 */
#घोषणा I2C_ADDR_TDA985x_H	0xb6
#घोषणा I2C_ADDR_TDA9874	0xb0 /* also used by 9875 */
#घोषणा I2C_ADDR_TEA6300	0x80 /* also used by 6320 */
#घोषणा I2C_ADDR_TEA6420	0x98
#घोषणा I2C_ADDR_PIC16C54	0x96 /* PV951 */

/* The tvaudio module accepts the following inमाला_दो: */
#घोषणा TVAUDIO_INPUT_TUNER  0
#घोषणा TVAUDIO_INPUT_RADIO  1
#घोषणा TVAUDIO_INPUT_EXTERN 2
#घोषणा TVAUDIO_INPUT_INTERN 3

अटल अंतरभूत स्थिर अचिन्हित लघु *tvaudio_addrs(व्योम)
अणु
	अटल स्थिर अचिन्हित लघु addrs[] = अणु
		I2C_ADDR_TDA8425   >> 1,
		I2C_ADDR_TEA6300   >> 1,
		I2C_ADDR_TEA6420   >> 1,
		I2C_ADDR_TDA9840   >> 1,
		I2C_ADDR_TDA985x_L >> 1,
		I2C_ADDR_TDA985x_H >> 1,
		I2C_ADDR_TDA9874   >> 1,
		I2C_ADDR_PIC16C54  >> 1,
		I2C_CLIENT_END
	पूर्ण;

	वापस addrs;
पूर्ण

#पूर्ण_अगर
