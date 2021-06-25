<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/resource.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/*
 * There are 3 YU GPIO blocks:
 * gpio[0]: HOST_GPIO0->HOST_GPIO31
 * gpio[1]: HOST_GPIO32->HOST_GPIO63
 * gpio[2]: HOST_GPIO64->HOST_GPIO69
 */
#घोषणा MLXBF2_GPIO_MAX_PINS_PER_BLOCK 32

/*
 * arm_gpio_lock रेजिस्टर:
 * bit[31]	lock status: active अगर set
 * bit[15:0]	set lock
 * The lock is enabled only अगर 0xd42f is written to this field
 */
#घोषणा YU_ARM_GPIO_LOCK_ADDR		0x2801088
#घोषणा YU_ARM_GPIO_LOCK_SIZE		0x8
#घोषणा YU_LOCK_ACTIVE_BIT(val)		(val >> 31)
#घोषणा YU_ARM_GPIO_LOCK_ACQUIRE	0xd42f
#घोषणा YU_ARM_GPIO_LOCK_RELEASE	0x0

/*
 * gpio[x] block रेजिस्टरs and their offset
 */
#घोषणा YU_GPIO_DATAIN			0x04
#घोषणा YU_GPIO_MODE1			0x08
#घोषणा YU_GPIO_MODE0			0x0c
#घोषणा YU_GPIO_DATASET			0x14
#घोषणा YU_GPIO_DATACLEAR		0x18
#घोषणा YU_GPIO_MODE1_CLEAR		0x50
#घोषणा YU_GPIO_MODE0_SET		0x54
#घोषणा YU_GPIO_MODE0_CLEAR		0x58

#अगर_घोषित CONFIG_PM
काष्ठा mlxbf2_gpio_context_save_regs अणु
	u32 gpio_mode0;
	u32 gpio_mode1;
पूर्ण;
#पूर्ण_अगर

/* BlueField-2 gpio block context काष्ठाure. */
काष्ठा mlxbf2_gpio_context अणु
	काष्ठा gpio_chip gc;

	/* YU GPIO blocks address */
	व्योम __iomem *gpio_io;

#अगर_घोषित CONFIG_PM
	काष्ठा mlxbf2_gpio_context_save_regs *csave_regs;
#पूर्ण_अगर
पूर्ण;

/* BlueField-2 gpio shared काष्ठाure. */
काष्ठा mlxbf2_gpio_param अणु
	व्योम __iomem *io;
	काष्ठा resource *res;
	काष्ठा mutex *lock;
पूर्ण;

अटल काष्ठा resource yu_arm_gpio_lock_res = अणु
	.start = YU_ARM_GPIO_LOCK_ADDR,
	.end   = YU_ARM_GPIO_LOCK_ADDR + YU_ARM_GPIO_LOCK_SIZE - 1,
	.name  = "YU_ARM_GPIO_LOCK",
पूर्ण;

अटल DEFINE_MUTEX(yu_arm_gpio_lock_mutex);

अटल काष्ठा mlxbf2_gpio_param yu_arm_gpio_lock_param = अणु
	.res = &yu_arm_gpio_lock_res,
	.lock = &yu_arm_gpio_lock_mutex,
पूर्ण;

/* Request memory region and map yu_arm_gpio_lock resource */
अटल पूर्णांक mlxbf2_gpio_get_lock_res(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	पूर्णांक ret = 0;

	mutex_lock(yu_arm_gpio_lock_param.lock);

	/* Check अगर the memory map alपढ़ोy exists */
	अगर (yu_arm_gpio_lock_param.io)
		जाओ निकास;

	res = yu_arm_gpio_lock_param.res;
	size = resource_size(res);

	अगर (!devm_request_mem_region(dev, res->start, size, res->name)) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	yu_arm_gpio_lock_param.io = devm_ioremap(dev, res->start, size);
	अगर (!yu_arm_gpio_lock_param.io)
		ret = -ENOMEM;

निकास:
	mutex_unlock(yu_arm_gpio_lock_param.lock);

	वापस ret;
पूर्ण

/*
 * Acquire the YU arm_gpio_lock to be able to change the direction
 * mode. If the lock_active bit is alपढ़ोy set, वापस an error.
 */
अटल पूर्णांक mlxbf2_gpio_lock_acquire(काष्ठा mlxbf2_gpio_context *gs)
अणु
	u32 arm_gpio_lock_val;

	mutex_lock(yu_arm_gpio_lock_param.lock);
	spin_lock(&gs->gc.bgpio_lock);

	arm_gpio_lock_val = पढ़ोl(yu_arm_gpio_lock_param.io);

	/*
	 * When lock active bit[31] is set, ModeX is ग_लिखो enabled
	 */
	अगर (YU_LOCK_ACTIVE_BIT(arm_gpio_lock_val)) अणु
		spin_unlock(&gs->gc.bgpio_lock);
		mutex_unlock(yu_arm_gpio_lock_param.lock);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(YU_ARM_GPIO_LOCK_ACQUIRE, yu_arm_gpio_lock_param.io);

	वापस 0;
पूर्ण

/*
 * Release the YU arm_gpio_lock after changing the direction mode.
 */
अटल व्योम mlxbf2_gpio_lock_release(काष्ठा mlxbf2_gpio_context *gs)
	__releases(&gs->gc.bgpio_lock)
	__releases(yu_arm_gpio_lock_param.lock)
अणु
	ग_लिखोl(YU_ARM_GPIO_LOCK_RELEASE, yu_arm_gpio_lock_param.io);
	spin_unlock(&gs->gc.bgpio_lock);
	mutex_unlock(yu_arm_gpio_lock_param.lock);
पूर्ण

/*
 * mode0 and mode1 are both locked by the gpio_lock field.
 *
 * Together, mode0 and mode1 define the gpio Mode dependeing also
 * on Reg_DataOut.
 *
 * अणुmode1,mode0पूर्ण:अणुReg_DataOut=0,Reg_DataOut=1पूर्ण->अणुDataOut=0,DataOut=1पूर्ण
 *
 * अणु0,0पूर्ण:Reg_DataOutअणु0,1पूर्ण->अणुZ,Zपूर्ण Input PAD
 * अणु0,1पूर्ण:Reg_DataOutअणु0,1पूर्ण->अणु0,1पूर्ण Full drive Output PAD
 * अणु1,0पूर्ण:Reg_DataOutअणु0,1पूर्ण->अणु0,Zपूर्ण 0-set PAD to low, 1-भग्न
 * अणु1,1पूर्ण:Reg_DataOutअणु0,1पूर्ण->अणुZ,1पूर्ण 0-भग्न, 1-set PAD to high
 */

/*
 * Set input direction:
 * अणुmode1,mode0पूर्ण = अणु0,0पूर्ण
 */
अटल पूर्णांक mlxbf2_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mlxbf2_gpio_context *gs = gpiochip_get_data(chip);
	पूर्णांक ret;

	/*
	 * Although the arm_gpio_lock was set in the probe function, check again
	 * अगर it is still enabled to be able to ग_लिखो to the ModeX रेजिस्टरs.
	 */
	ret = mlxbf2_gpio_lock_acquire(gs);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(BIT(offset), gs->gpio_io + YU_GPIO_MODE0_CLEAR);
	ग_लिखोl(BIT(offset), gs->gpio_io + YU_GPIO_MODE1_CLEAR);

	mlxbf2_gpio_lock_release(gs);

	वापस ret;
पूर्ण

/*
 * Set output direction:
 * अणुmode1,mode0पूर्ण = अणु0,1पूर्ण
 */
अटल पूर्णांक mlxbf2_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset,
					पूर्णांक value)
अणु
	काष्ठा mlxbf2_gpio_context *gs = gpiochip_get_data(chip);
	पूर्णांक ret = 0;

	/*
	 * Although the arm_gpio_lock was set in the probe function,
	 * check again it is still enabled to be able to ग_लिखो to the
	 * ModeX रेजिस्टरs.
	 */
	ret = mlxbf2_gpio_lock_acquire(gs);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(BIT(offset), gs->gpio_io + YU_GPIO_MODE1_CLEAR);
	ग_लिखोl(BIT(offset), gs->gpio_io + YU_GPIO_MODE0_SET);

	mlxbf2_gpio_lock_release(gs);

	वापस ret;
पूर्ण

/* BlueField-2 GPIO driver initialization routine. */
अटल पूर्णांक
mlxbf2_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf2_gpio_context *gs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_chip *gc;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक npins;
	पूर्णांक ret;

	gs = devm_kzalloc(dev, माप(*gs), GFP_KERNEL);
	अगर (!gs)
		वापस -ENOMEM;

	/* YU GPIO block address */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	gs->gpio_io = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!gs->gpio_io)
		वापस -ENOMEM;

	ret = mlxbf2_gpio_get_lock_res(pdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to get yu_arm_gpio_lock resource\n");
		वापस ret;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "npins", &npins))
		npins = MLXBF2_GPIO_MAX_PINS_PER_BLOCK;

	gc = &gs->gc;

	ret = bgpio_init(gc, dev, 4,
			gs->gpio_io + YU_GPIO_DATAIN,
			gs->gpio_io + YU_GPIO_DATASET,
			gs->gpio_io + YU_GPIO_DATACLEAR,
			शून्य,
			शून्य,
			0);

	gc->direction_input = mlxbf2_gpio_direction_input;
	gc->direction_output = mlxbf2_gpio_direction_output;
	gc->ngpio = npins;
	gc->owner = THIS_MODULE;

	platक्रमm_set_drvdata(pdev, gs);

	ret = devm_gpiochip_add_data(dev, &gs->gc, gs);
	अगर (ret) अणु
		dev_err(dev, "Failed adding memory mapped gpiochip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mlxbf2_gpio_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t state)
अणु
	काष्ठा mlxbf2_gpio_context *gs = platक्रमm_get_drvdata(pdev);

	gs->csave_regs->gpio_mode0 = पढ़ोl(gs->gpio_io +
		YU_GPIO_MODE0);
	gs->csave_regs->gpio_mode1 = पढ़ोl(gs->gpio_io +
		YU_GPIO_MODE1);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf2_gpio_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf2_gpio_context *gs = platक्रमm_get_drvdata(pdev);

	ग_लिखोl(gs->csave_regs->gpio_mode0, gs->gpio_io +
		YU_GPIO_MODE0);
	ग_लिखोl(gs->csave_regs->gpio_mode1, gs->gpio_io +
		YU_GPIO_MODE1);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा acpi_device_id __maybe_unused mlxbf2_gpio_acpi_match[] = अणु
	अणु "MLNXBF22", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mlxbf2_gpio_acpi_match);

अटल काष्ठा platक्रमm_driver mlxbf2_gpio_driver = अणु
	.driver = अणु
		.name = "mlxbf2_gpio",
		.acpi_match_table = ACPI_PTR(mlxbf2_gpio_acpi_match),
	पूर्ण,
	.probe    = mlxbf2_gpio_probe,
#अगर_घोषित CONFIG_PM
	.suspend  = mlxbf2_gpio_suspend,
	.resume   = mlxbf2_gpio_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(mlxbf2_gpio_driver);

MODULE_DESCRIPTION("Mellanox BlueField-2 GPIO Driver");
MODULE_AUTHOR("Mellanox Technologies");
MODULE_LICENSE("GPL v2");
