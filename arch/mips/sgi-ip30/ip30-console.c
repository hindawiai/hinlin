<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/पन.स>

#समावेश <यंत्र/sn/ioc3.h>

अटल अंतरभूत काष्ठा ioc3_uartregs *console_uart(व्योम)
अणु
	काष्ठा ioc3 *ioc3;

	ioc3 = (काष्ठा ioc3 *)((व्योम *)(0x900000001f600000));
	वापस &ioc3->sregs.uarta;
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	काष्ठा ioc3_uartregs *uart = console_uart();

	जबतक ((पढ़ोb(&uart->iu_lsr) & 0x20) == 0)
		cpu_relax();

	ग_लिखोb(c, &uart->iu_thr);
पूर्ण
