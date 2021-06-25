<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 *
 * cx88-i2c.c  --  all the i2c code is here
 *
 * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
 *			   & Marcus Metzler (mocm@thp.uni-koeln.de)
 * (c) 2002 Yurij Sysoev <yurij@naturesoft.net>
 * (c) 1999-2003 Gerd Knorr <kraxel@bytesex.org>
 * (c) 2005 Mauro Carvalho Chehab <mchehab@kernel.org>
 *	- Multituner support and i2c address binding
 */

#समावेश "cx88.h"

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <media/v4l2-common.h>

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

अटल अचिन्हित पूर्णांक i2c_udelay = 5;
module_param(i2c_udelay, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_udelay,
		 "i2c delay at insmod time, in usecs (should be 5 or higher). Lower value means higher bus speed.");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (i2c_debug >= level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: i2c:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

/* ----------------------------------------------------------------------- */

अटल व्योम cx8800_bit_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx88_core *core = data;

	अगर (state)
		core->i2c_state |= 0x02;
	अन्यथा
		core->i2c_state &= ~0x02;
	cx_ग_लिखो(MO_I2C, core->i2c_state);
	cx_पढ़ो(MO_I2C);
पूर्ण

अटल व्योम cx8800_bit_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx88_core *core = data;

	अगर (state)
		core->i2c_state |= 0x01;
	अन्यथा
		core->i2c_state &= ~0x01;
	cx_ग_लिखो(MO_I2C, core->i2c_state);
	cx_पढ़ो(MO_I2C);
पूर्ण

अटल पूर्णांक cx8800_bit_माला_लोcl(व्योम *data)
अणु
	काष्ठा cx88_core *core = data;
	u32 state;

	state = cx_पढ़ो(MO_I2C);
	वापस state & 0x02 ? 1 : 0;
पूर्ण

अटल पूर्णांक cx8800_bit_माला_लोda(व्योम *data)
अणु
	काष्ठा cx88_core *core = data;
	u32 state;

	state = cx_पढ़ो(MO_I2C);
	वापस state & 0x01;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_algo_bit_data cx8800_i2c_algo_ढाँचा = अणु
	.setsda  = cx8800_bit_setsda,
	.setscl  = cx8800_bit_setscl,
	.माला_लोda  = cx8800_bit_माला_लोda,
	.माला_लोcl  = cx8800_bit_माला_लोcl,
	.udelay  = 16,
	.समयout = 200,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल स्थिर अक्षर * स्थिर i2c_devs[128] = अणु
	[0x1c >> 1] = "lgdt330x",
	[0x86 >> 1] = "tda9887/cx22702",
	[0xa0 >> 1] = "eeprom",
	[0xc0 >> 1] = "tuner (analog)",
	[0xc2 >> 1] = "tuner (analog/dvb)",
	[0xc8 >> 1] = "xc5000",
पूर्ण;

अटल व्योम करो_i2c_scan(स्थिर अक्षर *name, काष्ठा i2c_client *c)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_devs); i++) अणु
		c->addr = i;
		rc = i2c_master_recv(c, &buf, 0);
		अगर (rc < 0)
			जारी;
		pr_info("i2c scan: found device @ 0x%x  [%s]\n",
			i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण
पूर्ण

/* init + रेजिस्टर i2c adapter */
पूर्णांक cx88_i2c_init(काष्ठा cx88_core *core, काष्ठा pci_dev *pci)
अणु
	/* Prevents usage of invalid delay values */
	अगर (i2c_udelay < 5)
		i2c_udelay = 5;

	core->i2c_algo = cx8800_i2c_algo_ढाँचा;

	core->i2c_adap.dev.parent = &pci->dev;
	strscpy(core->i2c_adap.name, core->name, माप(core->i2c_adap.name));
	core->i2c_adap.owner = THIS_MODULE;
	core->i2c_algo.udelay = i2c_udelay;
	core->i2c_algo.data = core;
	i2c_set_adapdata(&core->i2c_adap, &core->v4l2_dev);
	core->i2c_adap.algo_data = &core->i2c_algo;
	core->i2c_client.adapter = &core->i2c_adap;
	strscpy(core->i2c_client.name, "cx88xx internal", I2C_NAME_SIZE);

	cx8800_bit_setscl(core, 1);
	cx8800_bit_setsda(core, 1);

	core->i2c_rc = i2c_bit_add_bus(&core->i2c_adap);
	अगर (core->i2c_rc == 0) अणु
		अटल u8 tuner_data[] = अणु
			0x0b, 0xdc, 0x86, 0x52 पूर्ण;
		अटल काष्ठा i2c_msg tuner_msg = अणु
			.flags = 0,
			.addr = 0xc2 >> 1,
			.buf = tuner_data,
			.len = 4
		पूर्ण;

		dprपूर्णांकk(1, "i2c register ok\n");
		चयन (core->boardnr) अणु
		हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		हाल CX88_BOARD_HAUPPAUGE_HVR3000:
		हाल CX88_BOARD_HAUPPAUGE_HVR4000:
			pr_info("i2c init: enabling analog demod on HVR1300/3000/4000 tuner\n");
			i2c_transfer(core->i2c_client.adapter, &tuner_msg, 1);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (i2c_scan)
			करो_i2c_scan(core->name, &core->i2c_client);
	पूर्ण अन्यथा
		pr_err("i2c register FAILED\n");

	वापस core->i2c_rc;
पूर्ण
