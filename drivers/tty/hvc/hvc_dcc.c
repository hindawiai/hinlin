<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2010, 2014 The Linux Foundation. All rights reserved.  */

#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>

#समावेश <यंत्र/dcc.h>
#समावेश <यंत्र/processor.h>

#समावेश "hvc_console.h"

/* DCC Status Bits */
#घोषणा DCC_STATUS_RX		(1 << 30)
#घोषणा DCC_STATUS_TX		(1 << 29)

अटल व्योम dcc_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (__dcc_माला_लोtatus() & DCC_STATUS_TX)
		cpu_relax();

	__dcc_अक्षर_दो(ch);
पूर्ण

अटल व्योम dcc_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, dcc_uart_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init dcc_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	device->con->ग_लिखो = dcc_early_ग_लिखो;

	वापस 0;
पूर्ण

EARLYCON_DECLARE(dcc, dcc_early_console_setup);

अटल पूर्णांक hvc_dcc_put_अक्षरs(uपूर्णांक32_t vt, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		जबतक (__dcc_माला_लोtatus() & DCC_STATUS_TX)
			cpu_relax();

		__dcc_अक्षर_दो(buf[i]);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक hvc_dcc_get_अक्षरs(uपूर्णांक32_t vt, अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; ++i)
		अगर (__dcc_माला_लोtatus() & DCC_STATUS_RX)
			buf[i] = __dcc_अक्षर_लो();
		अन्यथा
			अवरोध;

	वापस i;
पूर्ण

अटल bool hvc_dcc_check(व्योम)
अणु
	अचिन्हित दीर्घ समय = jअगरfies + (HZ / 10);

	/* Write a test अक्षरacter to check अगर it is handled */
	__dcc_अक्षर_दो('\n');

	जबतक (समय_is_after_jअगरfies(समय)) अणु
		अगर (!(__dcc_माला_लोtatus() & DCC_STATUS_TX))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvc_dcc_get_put_ops = अणु
	.get_अक्षरs = hvc_dcc_get_अक्षरs,
	.put_अक्षरs = hvc_dcc_put_अक्षरs,
पूर्ण;

अटल पूर्णांक __init hvc_dcc_console_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!hvc_dcc_check())
		वापस -ENODEV;

	/* Returns -1 अगर error */
	ret = hvc_instantiate(0, 0, &hvc_dcc_get_put_ops);

	वापस ret < 0 ? -ENODEV : 0;
पूर्ण
console_initcall(hvc_dcc_console_init);

अटल पूर्णांक __init hvc_dcc_init(व्योम)
अणु
	काष्ठा hvc_काष्ठा *p;

	अगर (!hvc_dcc_check())
		वापस -ENODEV;

	p = hvc_alloc(0, 0, &hvc_dcc_get_put_ops, 128);

	वापस PTR_ERR_OR_ZERO(p);
पूर्ण
device_initcall(hvc_dcc_init);
