<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RISC-V SBI based earlycon
 *
 * Copyright (C) 2018 Anup Patel <anup@brainfault.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <यंत्र/sbi.h>

अटल व्योम sbi_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	sbi_console_अक्षर_दो(c);
पूर्ण

अटल व्योम sbi_console_ग_लिखो(काष्ठा console *con,
			      स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;
	uart_console_ग_लिखो(&dev->port, s, n, sbi_अ_दो);
पूर्ण

अटल पूर्णांक __init early_sbi_setup(काष्ठा earlycon_device *device,
				  स्थिर अक्षर *opt)
अणु
	device->con->ग_लिखो = sbi_console_ग_लिखो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(sbi, early_sbi_setup);
