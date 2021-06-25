<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -------------------------------------------------------------------- */
/* i2c-pcf8584.h: PCF 8584 global defines				*/
/* -------------------------------------------------------------------- */
/*   Copyright (C) 1996 Simon G. Vogl
                   1999 Hans Berglund

 */
/* --------------------------------------------------------------------	*/

/* With some changes from Froकरो Looijaard <froकरोl@dds.nl> */

#अगर_अघोषित I2C_PCF8584_H
#घोषणा I2C_PCF8584_H 1

/* ----- Control रेजिस्टर bits ----------------------------------------	*/
#घोषणा I2C_PCF_PIN	0x80
#घोषणा I2C_PCF_ESO	0x40
#घोषणा I2C_PCF_ES1	0x20
#घोषणा I2C_PCF_ES2	0x10
#घोषणा I2C_PCF_ENI	0x08
#घोषणा I2C_PCF_STA	0x04
#घोषणा I2C_PCF_STO	0x02
#घोषणा I2C_PCF_ACK	0x01

#घोषणा I2C_PCF_START    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#घोषणा I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
#घोषणा I2C_PCF_REPSTART (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#घोषणा I2C_PCF_IDLE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)

/* ----- Status रेजिस्टर bits -----------------------------------------	*/
/*#घोषणा I2C_PCF_PIN  0x80    as above*/

#घोषणा I2C_PCF_INI 0x40   /* 1 अगर not initialized */
#घोषणा I2C_PCF_STS 0x20
#घोषणा I2C_PCF_BER 0x10
#घोषणा I2C_PCF_AD0 0x08
#घोषणा I2C_PCF_LRB 0x08
#घोषणा I2C_PCF_AAS 0x04
#घोषणा I2C_PCF_LAB 0x02
#घोषणा I2C_PCF_BB  0x01

/* ----- Chip घड़ी frequencies ---------------------------------------	*/
#घोषणा I2C_PCF_CLK3	0x00
#घोषणा I2C_PCF_CLK443	0x10
#घोषणा I2C_PCF_CLK6	0x14
#घोषणा I2C_PCF_CLK	0x18
#घोषणा I2C_PCF_CLK12	0x1c

/* ----- transmission frequencies -------------------------------------	*/
#घोषणा I2C_PCF_TRNS90 0x00	/*  90 kHz */
#घोषणा I2C_PCF_TRNS45 0x01	/*  45 kHz */
#घोषणा I2C_PCF_TRNS11 0x02	/*  11 kHz */
#घोषणा I2C_PCF_TRNS15 0x03	/* 1.5 kHz */


/* ----- Access to पूर्णांकernal रेजिस्टरs according to ES1,ES2 ------------	*/
/* they are mapped to the data port ( a0 = 0 ) 				*/
/* available when ESO == 0 :						*/

#घोषणा I2C_PCF_OWNADR	0
#घोषणा I2C_PCF_INTREG	I2C_PCF_ES2
#घोषणा I2C_PCF_CLKREG	I2C_PCF_ES1

#पूर्ण_अगर /* I2C_PCF8584_H */
