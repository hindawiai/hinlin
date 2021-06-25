<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cx88-vp3054-i2c.c -- support क्रम the secondary I2C bus of the
 *			DNTV Live! DVB-T Pro (VP-3054), wired as:
 *			GPIO[0] -> SCL, GPIO[1] -> SDA
 *
 * (c) 2005 Chris Pascoe <c.pascoe@itee.uq.edu.au>
 */

#समावेश "cx88.h"
#समावेश "cx88-vp3054-i2c.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

MODULE_DESCRIPTION("driver for cx2388x VP3054 design");
MODULE_AUTHOR("Chris Pascoe <c.pascoe@itee.uq.edu.au>");
MODULE_LICENSE("GPL");

/* ----------------------------------------------------------------------- */

अटल व्योम vp3054_bit_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx8802_dev *dev = data;
	काष्ठा cx88_core *core = dev->core;
	काष्ठा vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	अगर (state) अणु
		vp3054_i2c->state |=  0x0001;	/* SCL high */
		vp3054_i2c->state &= ~0x0100;	/* बाह्यal pullup */
	पूर्ण अन्यथा अणु
		vp3054_i2c->state &= ~0x0001;	/* SCL low */
		vp3054_i2c->state |=  0x0100;	/* drive pin */
	पूर्ण
	cx_ग_लिखो(MO_GP0_IO, 0x010000 | vp3054_i2c->state);
	cx_पढ़ो(MO_GP0_IO);
पूर्ण

अटल व्योम vp3054_bit_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx8802_dev *dev = data;
	काष्ठा cx88_core *core = dev->core;
	काष्ठा vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	अगर (state) अणु
		vp3054_i2c->state |=  0x0002;	/* SDA high */
		vp3054_i2c->state &= ~0x0200;	/* tristate pin */
	पूर्ण अन्यथा अणु
		vp3054_i2c->state &= ~0x0002;	/* SDA low */
		vp3054_i2c->state |=  0x0200;	/* drive pin */
	पूर्ण
	cx_ग_लिखो(MO_GP0_IO, 0x020000 | vp3054_i2c->state);
	cx_पढ़ो(MO_GP0_IO);
पूर्ण

अटल पूर्णांक vp3054_bit_माला_लोcl(व्योम *data)
अणु
	काष्ठा cx8802_dev *dev = data;
	काष्ठा cx88_core *core = dev->core;
	u32 state;

	state = cx_पढ़ो(MO_GP0_IO);
	वापस (state & 0x01) ? 1 : 0;
पूर्ण

अटल पूर्णांक vp3054_bit_माला_लोda(व्योम *data)
अणु
	काष्ठा cx8802_dev *dev = data;
	काष्ठा cx88_core *core = dev->core;
	u32 state;

	state = cx_पढ़ो(MO_GP0_IO);
	वापस (state & 0x02) ? 1 : 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_algo_bit_data vp3054_i2c_algo_ढाँचा = अणु
	.setsda  = vp3054_bit_setsda,
	.setscl  = vp3054_bit_setscl,
	.माला_लोda  = vp3054_bit_माला_लोda,
	.माला_लोcl  = vp3054_bit_माला_लोcl,
	.udelay  = 16,
	.समयout = 200,
पूर्ण;

/* ----------------------------------------------------------------------- */

पूर्णांक vp3054_i2c_probe(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	काष्ठा vp3054_i2c_state *vp3054_i2c;
	पूर्णांक rc;

	अगर (core->boardnr != CX88_BOARD_DNTV_LIVE_DVB_T_PRO)
		वापस 0;

	vp3054_i2c = kzalloc(माप(*vp3054_i2c), GFP_KERNEL);
	अगर (!vp3054_i2c)
		वापस -ENOMEM;
	dev->vp3054 = vp3054_i2c;

	vp3054_i2c->algo = vp3054_i2c_algo_ढाँचा;

	vp3054_i2c->adap.dev.parent = &dev->pci->dev;
	strscpy(vp3054_i2c->adap.name, core->name,
		माप(vp3054_i2c->adap.name));
	vp3054_i2c->adap.owner = THIS_MODULE;
	vp3054_i2c->algo.data = dev;
	i2c_set_adapdata(&vp3054_i2c->adap, dev);
	vp3054_i2c->adap.algo_data = &vp3054_i2c->algo;

	vp3054_bit_setscl(dev, 1);
	vp3054_bit_setsda(dev, 1);

	rc = i2c_bit_add_bus(&vp3054_i2c->adap);
	अगर (rc != 0) अणु
		pr_err("vp3054_i2c register FAILED\n");

		kमुक्त(dev->vp3054);
		dev->vp3054 = शून्य;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(vp3054_i2c_probe);

व्योम vp3054_i2c_हटाओ(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	अगर (!vp3054_i2c ||
	    dev->core->boardnr != CX88_BOARD_DNTV_LIVE_DVB_T_PRO)
		वापस;

	i2c_del_adapter(&vp3054_i2c->adap);
	kमुक्त(vp3054_i2c);
पूर्ण
EXPORT_SYMBOL(vp3054_i2c_हटाओ);
