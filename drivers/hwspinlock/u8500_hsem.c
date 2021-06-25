<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * u8500 HWSEM driver
 *
 * Copyright (C) 2010-2011 ST-Ericsson
 *
 * Implements u8500 semaphore handling क्रम protocol 1, no पूर्णांकerrupts.
 *
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 * Heavily borrowed from the work of :
 *   Simon Que <sque@ti.com>
 *   Hari Kanigeri <h-kanigeri2@ti.com>
 *   Ohad Ben-Cohen <ohad@wizery.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hwspinlock_internal.h"

/*
 * Implementation of STE's HSem protocol 1 without पूर्णांकerrutps.
 * The only masterID we allow is '0x01' to क्रमce people to use
 * HSems क्रम synchronisation between processors rather than processes
 * on the ARM core.
 */

#घोषणा U8500_MAX_SEMAPHORE		32	/* a total of 32 semaphore */
#घोषणा RESET_SEMAPHORE			(0)	/* मुक्त */

/*
 * CPU ID क्रम master running u8500 kernel.
 * Hswpinlocks should only be used to synchonise operations
 * between the Cortex A9 core and the other CPUs.  Hence
 * क्रमcing the masterID to a preset value.
 */
#घोषणा HSEM_MASTER_ID			0x01

#घोषणा HSEM_REGISTER_OFFSET		0x08

#घोषणा HSEM_CTRL_REG			0x00
#घोषणा HSEM_ICRALL			0x90
#घोषणा HSEM_PROTOCOL_1			0x01

अटल पूर्णांक u8500_hsem_trylock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	ग_लिखोl(HSEM_MASTER_ID, lock_addr);

	/* get only first 4 bit and compare to masterID.
	 * अगर equal, we have the semaphore, otherwise
	 * someone अन्यथा has it.
	 */
	वापस (HSEM_MASTER_ID == (0x0F & पढ़ोl(lock_addr)));
पूर्ण

अटल व्योम u8500_hsem_unlock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	/* release the lock by writing 0 to it */
	ग_लिखोl(RESET_SEMAPHORE, lock_addr);
पूर्ण

/*
 * u8500: what value is recommended here ?
 */
अटल व्योम u8500_hsem_relax(काष्ठा hwspinlock *lock)
अणु
	ndelay(50);
पूर्ण

अटल स्थिर काष्ठा hwspinlock_ops u8500_hwspinlock_ops = अणु
	.trylock	= u8500_hsem_trylock,
	.unlock		= u8500_hsem_unlock,
	.relax		= u8500_hsem_relax,
पूर्ण;

अटल पूर्णांक u8500_hsem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwspinlock_pdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा hwspinlock_device *bank;
	काष्ठा hwspinlock *hwlock;
	व्योम __iomem *io_base;
	पूर्णांक i, num_locks = U8500_MAX_SEMAPHORE;
	uदीर्घ val;

	अगर (!pdata)
		वापस -ENODEV;

	io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	/* make sure protocol 1 is selected */
	val = पढ़ोl(io_base + HSEM_CTRL_REG);
	ग_लिखोl((val & ~HSEM_PROTOCOL_1), io_base + HSEM_CTRL_REG);

	/* clear all पूर्णांकerrupts */
	ग_लिखोl(0xFFFF, io_base + HSEM_ICRALL);

	bank = devm_kzalloc(&pdev->dev, काष्ठा_size(bank, lock, num_locks),
			    GFP_KERNEL);
	अगर (!bank)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bank);

	क्रम (i = 0, hwlock = &bank->lock[0]; i < num_locks; i++, hwlock++)
		hwlock->priv = io_base + HSEM_REGISTER_OFFSET + माप(u32) * i;

	वापस devm_hwspin_lock_रेजिस्टर(&pdev->dev, bank,
					 &u8500_hwspinlock_ops,
					 pdata->base_id, num_locks);
पूर्ण

अटल पूर्णांक u8500_hsem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwspinlock_device *bank = platक्रमm_get_drvdata(pdev);
	व्योम __iomem *io_base = bank->lock[0].priv - HSEM_REGISTER_OFFSET;

	/* clear all पूर्णांकerrupts */
	ग_लिखोl(0xFFFF, io_base + HSEM_ICRALL);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver u8500_hsem_driver = अणु
	.probe		= u8500_hsem_probe,
	.हटाओ		= u8500_hsem_हटाओ,
	.driver		= अणु
		.name	= "u8500_hsem",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init u8500_hsem_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&u8500_hsem_driver);
पूर्ण
/* board init code might need to reserve hwspinlocks क्रम predefined purposes */
postcore_initcall(u8500_hsem_init);

अटल व्योम __निकास u8500_hsem_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&u8500_hsem_driver);
पूर्ण
module_निकास(u8500_hsem_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware Spinlock driver for u8500");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
