<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA USRGPIR Support.
 *
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <mach/fpga.h>

#घोषणा NR_FPGA_GPIOS	8

अटल स्थिर अक्षर *usrgpir_gpio_names[NR_FPGA_GPIOS] = अणु
	"in0", "in1", "in2", "in3", "in4", "in5", "in6", "in7",
पूर्ण;

अटल पूर्णांक usrgpir_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	/* always in */
	वापस 0;
पूर्ण

अटल पूर्णांक usrgpir_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस !!(fpga_पढ़ो_reg(USRGPIR) & (1 << gpio));
पूर्ण

अटल काष्ठा gpio_chip usrgpir_gpio_chip = अणु
	.label			= "sdk7786-fpga",
	.names			= usrgpir_gpio_names,
	.direction_input	= usrgpir_gpio_direction_input,
	.get			= usrgpir_gpio_get,
	.base			= -1, /* करोn't care */
	.ngpio			= NR_FPGA_GPIOS,
पूर्ण;

अटल पूर्णांक __init usrgpir_gpio_setup(व्योम)
अणु
	वापस gpiochip_add_data(&usrgpir_gpio_chip, शून्य);
पूर्ण
device_initcall(usrgpir_gpio_setup);
