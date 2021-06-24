<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * i2c-algo-bit.h: i2c driver algorithms क्रम bit-shअगरt adapters
 *
 *   Copyright (C) 1995-99 Simon G. Vogl
 * With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and even
 * Froकरो Looijaard <froकरोl@dds.nl>
 */

#अगर_अघोषित _LINUX_I2C_ALGO_BIT_H
#घोषणा _LINUX_I2C_ALGO_BIT_H

#समावेश <linux/i2c.h>

/* --- Defines क्रम bit-adapters ---------------------------------------	*/
/*
 * This काष्ठा contains the hw-dependent functions of bit-style adapters to
 * manipulate the line states, and to init any hw-specअगरic features. This is
 * only used अगर you have more than one hw-type of adapter running.
 */
काष्ठा i2c_algo_bit_data अणु
	व्योम *data;		/* निजी data क्रम lowlevel routines */
	व्योम (*setsda) (व्योम *data, पूर्णांक state);
	व्योम (*setscl) (व्योम *data, पूर्णांक state);
	पूर्णांक  (*माला_लोda) (व्योम *data);
	पूर्णांक  (*माला_लोcl) (व्योम *data);
	पूर्णांक  (*pre_xfer)  (काष्ठा i2c_adapter *);
	व्योम (*post_xfer) (काष्ठा i2c_adapter *);

	/* local settings */
	पूर्णांक udelay;		/* half घड़ी cycle समय in us,
				   minimum 2 us क्रम fast-mode I2C,
				   minimum 5 us क्रम standard-mode I2C and SMBus,
				   maximum 50 us क्रम SMBus */
	पूर्णांक समयout;		/* in jअगरfies */
	bool can_करो_atomic;	/* callbacks करोn't sleep, we can be atomic */
पूर्ण;

पूर्णांक i2c_bit_add_bus(काष्ठा i2c_adapter *);
पूर्णांक i2c_bit_add_numbered_bus(काष्ठा i2c_adapter *);
बाह्य स्थिर काष्ठा i2c_algorithm i2c_bit_algo;

#पूर्ण_अगर /* _LINUX_I2C_ALGO_BIT_H */
