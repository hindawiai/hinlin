<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Silicon Lअसल C2 port Linux support क्रम Eurotech Duramar 2150
 *
 *  Copyright (c) 2008 Roकरोlfo Giometti <giometti@linux.it>
 *  Copyright (c) 2008 Eurotech S.p.A. <info@eurotech.it>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/c2port.h>

#घोषणा DATA_PORT	0x325
#घोषणा सूची_PORT	0x326
#घोषणा    C2D		   (1 << 0)
#घोषणा    C2CK		   (1 << 1)

अटल DEFINE_MUTEX(update_lock);

/*
 * C2 port operations
 */

अटल व्योम duramar2150_c2port_access(काष्ठा c2port_device *dev, पूर्णांक status)
अणु
	u8 v;

	mutex_lock(&update_lock);

	v = inb(सूची_PORT);

	/* 0 = input, 1 = output */
	अगर (status)
		outb(v | (C2D | C2CK), सूची_PORT);
	अन्यथा
		/* When access is "off" is important that both lines are set
		 * as inमाला_दो or hi-impedance */
		outb(v & ~(C2D | C2CK), सूची_PORT);

	mutex_unlock(&update_lock);
पूर्ण

अटल व्योम duramar2150_c2port_c2d_dir(काष्ठा c2port_device *dev, पूर्णांक dir)
अणु
	u8 v;

	mutex_lock(&update_lock);

	v = inb(सूची_PORT);

	अगर (dir)
		outb(v & ~C2D, सूची_PORT);
	अन्यथा
		outb(v | C2D, सूची_PORT);

	mutex_unlock(&update_lock);
पूर्ण

अटल पूर्णांक duramar2150_c2port_c2d_get(काष्ठा c2port_device *dev)
अणु
	वापस inb(DATA_PORT) & C2D;
पूर्ण

अटल व्योम duramar2150_c2port_c2d_set(काष्ठा c2port_device *dev, पूर्णांक status)
अणु
	u8 v;

	mutex_lock(&update_lock);

	v = inb(DATA_PORT);

	अगर (status)
		outb(v | C2D, DATA_PORT);
	अन्यथा
		outb(v & ~C2D, DATA_PORT);

	mutex_unlock(&update_lock);
पूर्ण

अटल व्योम duramar2150_c2port_c2ck_set(काष्ठा c2port_device *dev, पूर्णांक status)
अणु
	u8 v;

	mutex_lock(&update_lock);

	v = inb(DATA_PORT);

	अगर (status)
		outb(v | C2CK, DATA_PORT);
	अन्यथा
		outb(v & ~C2CK, DATA_PORT);

	mutex_unlock(&update_lock);
पूर्ण

अटल काष्ठा c2port_ops duramar2150_c2port_ops = अणु
	.block_size	= 512,	/* bytes */
	.blocks_num	= 30,	/* total flash size: 15360 bytes */

	.access		= duramar2150_c2port_access,
	.c2d_dir	= duramar2150_c2port_c2d_dir,
	.c2d_get	= duramar2150_c2port_c2d_get,
	.c2d_set	= duramar2150_c2port_c2d_set,
	.c2ck_set	= duramar2150_c2port_c2ck_set,
पूर्ण;

अटल काष्ठा c2port_device *duramar2150_c2port_dev;

/*
 * Module stuff
 */

अटल पूर्णांक __init duramar2150_c2port_init(व्योम)
अणु
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	res = request_region(0x325, 2, "c2port");
	अगर (!res)
		वापस -EBUSY;

	duramar2150_c2port_dev = c2port_device_रेजिस्टर("uc",
					&duramar2150_c2port_ops, शून्य);
	अगर (IS_ERR(duramar2150_c2port_dev)) अणु
		ret = PTR_ERR(duramar2150_c2port_dev);
		जाओ मुक्त_region;
	पूर्ण

	वापस 0;

मुक्त_region:
	release_region(0x325, 2);
	वापस ret;
पूर्ण

अटल व्योम __निकास duramar2150_c2port_निकास(व्योम)
अणु
	/* Setup the GPIOs as input by शेष (access = 0) */
	duramar2150_c2port_access(duramar2150_c2port_dev, 0);

	c2port_device_unरेजिस्टर(duramar2150_c2port_dev);

	release_region(0x325, 2);
पूर्ण

module_init(duramar2150_c2port_init);
module_निकास(duramar2150_c2port_निकास);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("Silicon Labs C2 port Linux support for Duramar 2150");
MODULE_LICENSE("GPL");
