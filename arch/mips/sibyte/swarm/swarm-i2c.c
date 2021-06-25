<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Broadcom BCM91250A (SWARM), etc. I2C platक्रमm setup.
 *
 *	Copyright (c) 2008  Maciej W. Rozycki
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>


अटल काष्ठा i2c_board_info swarm_i2c_info1[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("m41t81", 0x68),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init swarm_i2c_init(व्योम)
अणु
	पूर्णांक err;

	err = i2c_रेजिस्टर_board_info(1, swarm_i2c_info1,
				      ARRAY_SIZE(swarm_i2c_info1));
	अगर (err < 0)
		prपूर्णांकk(KERN_ERR
		       "swarm-i2c: cannot register board I2C devices\n");
	वापस err;
पूर्ण

arch_initcall(swarm_i2c_init);
