<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001, 2002 Ralf Baechle
 */

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/ioc3.h>

#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>

#समावेश "ip27-common.h"

#घोषणा IOC3_CLK	(22000000 / 3)
#घोषणा IOC3_FLAGS	(0)

अटल अंतरभूत काष्ठा ioc3_uartregs *console_uart(व्योम)
अणु
	काष्ठा ioc3 *ioc3;
	nasid_t nasid;

	nasid = (master_nasid == INVALID_NASID) ? get_nasid() : master_nasid;
	ioc3 = (काष्ठा ioc3 *)KL_CONFIG_CH_CONS_INFO(nasid)->memory_base;

	वापस &ioc3->sregs.uarta;
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	काष्ठा ioc3_uartregs *uart = console_uart();

	जबतक ((पढ़ोb(&uart->iu_lsr) & 0x20) == 0)
		;
	ग_लिखोb(c, &uart->iu_thr);
पूर्ण
