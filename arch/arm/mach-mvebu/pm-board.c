<शैली गुरु>
/*
 * Board-level suspend/resume support.
 *
 * Copyright (C) 2014-2015 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश "common.h"

#घोषणा ARMADA_PIC_NR_GPIOS 3

अटल व्योम __iomem *gpio_ctrl;
अटल पूर्णांक pic_gpios[ARMADA_PIC_NR_GPIOS];
अटल पूर्णांक pic_raw_gpios[ARMADA_PIC_NR_GPIOS];

अटल व्योम mvebu_armada_pm_enter(व्योम __iomem *sdram_reg, u32 srcmd)
अणु
	u32 reg, ackcmd;
	पूर्णांक i;

	/* Put 001 as value on the GPIOs */
	reg = पढ़ोl(gpio_ctrl);
	क्रम (i = 0; i < ARMADA_PIC_NR_GPIOS; i++)
		reg &= ~BIT(pic_raw_gpios[i]);
	reg |= BIT(pic_raw_gpios[0]);
	ग_लिखोl(reg, gpio_ctrl);

	/* Prepare writing 111 to the GPIOs */
	ackcmd = पढ़ोl(gpio_ctrl);
	क्रम (i = 0; i < ARMADA_PIC_NR_GPIOS; i++)
		ackcmd |= BIT(pic_raw_gpios[i]);

	srcmd = cpu_to_le32(srcmd);
	ackcmd = cpu_to_le32(ackcmd);

	/*
	 * Wait a जबतक, the PIC needs quite a bit of समय between the
	 * two GPIO commands.
	 */
	mdelay(3000);

	यंत्र अस्थिर (
		/* Align to a cache line */
		".balign 32\n\t"

		/* Enter self refresh */
		"str %[srcmd], [%[sdram_reg]]\n\t"

		/*
		 * Wait 100 cycles क्रम DDR to enter self refresh, by
		 * करोing 50 बार two inकाष्ठाions.
		 */
		"mov r1, #50\n\t"
		"1: subs r1, r1, #1\n\t"
		"bne 1b\n\t"

		/* Issue the command ACK */
		"str %[ackcmd], [%[gpio_ctrl]]\n\t"

		/* Trap the processor */
		"b .\n\t"
		: : [srcmd] "r" (srcmd), [sdram_reg] "r" (sdram_reg),
		  [ackcmd] "r" (ackcmd), [gpio_ctrl] "r" (gpio_ctrl) : "r1");
पूर्ण

अटल पूर्णांक __init mvebu_armada_pm_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा device_node *gpio_ctrl_np = शून्य;
	पूर्णांक ret = 0, i;

	अगर (!of_machine_is_compatible("marvell,axp-gp"))
		वापस -ENODEV;

	np = of_find_node_by_name(शून्य, "pm_pic");
	अगर (!np)
		वापस -ENODEV;

	क्रम (i = 0; i < ARMADA_PIC_NR_GPIOS; i++) अणु
		अक्षर *name;
		काष्ठा of_phandle_args args;

		pic_gpios[i] = of_get_named_gpio(np, "ctrl-gpios", i);
		अगर (pic_gpios[i] < 0) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

		name = kaप्र_लिखो(GFP_KERNEL, "pic-pin%d", i);
		अगर (!name) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ret = gpio_request(pic_gpios[i], name);
		अगर (ret < 0) अणु
			kमुक्त(name);
			जाओ out;
		पूर्ण

		ret = gpio_direction_output(pic_gpios[i], 0);
		अगर (ret < 0) अणु
			gpio_मुक्त(pic_gpios[i]);
			kमुक्त(name);
			जाओ out;
		पूर्ण

		ret = of_parse_phandle_with_fixed_args(np, "ctrl-gpios", 2,
						       i, &args);
		अगर (ret < 0) अणु
			gpio_मुक्त(pic_gpios[i]);
			kमुक्त(name);
			जाओ out;
		पूर्ण

		अगर (gpio_ctrl_np)
			of_node_put(gpio_ctrl_np);
		gpio_ctrl_np = args.np;
		pic_raw_gpios[i] = args.args[0];
	पूर्ण

	gpio_ctrl = of_iomap(gpio_ctrl_np, 0);
	अगर (!gpio_ctrl) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mvebu_pm_suspend_init(mvebu_armada_pm_enter);

out:
	of_node_put(np);
	of_node_put(gpio_ctrl_np);
	वापस ret;
पूर्ण

/*
 * Registering the mvebu_board_pm_enter callback must be करोne beक्रमe
 * the platक्रमm_suspend_ops will be रेजिस्टरed. In the same समय we
 * also need to have the gpio devices रेजिस्टरed. That's why we use a
 * device_initcall_sync which is called after all the device_initcall
 * (used by the gpio device) but beक्रमe the late_initcall (used to
 * रेजिस्टर the platक्रमm_suspend_ops)
 */
device_initcall_sync(mvebu_armada_pm_init);
