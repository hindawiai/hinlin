<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Adapted क्रम ARM and earlycon:
 * Copyright (C) 2014 Linaro Ltd.
 * Author: Rob Herring <robh@kernel.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा SEMIHOST_SWI	"0xab"
#अन्यथा
#घोषणा SEMIHOST_SWI	"0x123456"
#पूर्ण_अगर

/*
 * Semihosting-based debug console
 */
अटल व्योम smh_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
#अगर_घोषित CONFIG_ARM64
	यंत्र अस्थिर("mov  x1, %0\n"
		     "mov  x0, #3\n"
		     "hlt  0xf000\n"
		     : : "r" (&c) : "x0", "x1", "memory");
#अन्यथा
	यंत्र अस्थिर("mov  r1, %0\n"
		     "mov  r0, #3\n"
		     "svc  " SEMIHOST_SWI "\n"
		     : : "r" (&c) : "r0", "r1", "memory");
#पूर्ण_अगर
पूर्ण

अटल व्योम smh_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;
	uart_console_ग_लिखो(&dev->port, s, n, smh_अ_दो);
पूर्ण

अटल पूर्णांक
__init early_smh_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	device->con->ग_लिखो = smh_ग_लिखो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(smh, early_smh_setup);
