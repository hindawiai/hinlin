<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI DaVinci serial driver
 *
 * Copyright (C) 2006 Texas Instruments.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <mach/serial.h>
#समावेश <mach/cputype.h>

अटल अंतरभूत व्योम serial_ग_लिखो_reg(काष्ठा plat_serial8250_port *p, पूर्णांक offset,
				    पूर्णांक value)
अणु
	offset <<= p->regshअगरt;

	WARN_ONCE(!p->membase, "unmapped write: uart[%d]\n", offset);

	__raw_ग_लिखोl(value, p->membase + offset);
पूर्ण

अटल व्योम __init davinci_serial_reset(काष्ठा plat_serial8250_port *p)
अणु
	अचिन्हित पूर्णांक pwremu = 0;

	serial_ग_लिखो_reg(p, UART_IER, 0);  /* disable all पूर्णांकerrupts */

	/* reset both transmitter and receiver: bits 14,13 = UTRST, URRST */
	serial_ग_लिखो_reg(p, UART_DAVINCI_PWREMU, pwremu);
	mdelay(10);

	pwremu |= (0x3 << 13);
	pwremu |= 0x1;
	serial_ग_लिखो_reg(p, UART_DAVINCI_PWREMU, pwremu);

	अगर (cpu_is_davinci_dm646x())
		serial_ग_लिखो_reg(p, UART_DM646X_SCR,
				 UART_DM646X_SCR_TX_WATERMARK);
पूर्ण

पूर्णांक __init davinci_serial_init(काष्ठा platक्रमm_device *serial_dev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा device *dev;
	काष्ठा plat_serial8250_port *p;
	काष्ठा clk *clk;

	/*
	 * Make sure the serial ports are muxed on at this poपूर्णांक.
	 * You have to mux them off in device drivers later on अगर not needed.
	 */
	क्रम (i = 0; serial_dev[i].dev.platक्रमm_data != शून्य; i++) अणु
		dev = &serial_dev[i].dev;
		p = dev->platक्रमm_data;

		ret = platक्रमm_device_रेजिस्टर(&serial_dev[i]);
		अगर (ret)
			जारी;

		clk = clk_get(dev, शून्य);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s:%d: failed to get UART%d clock\n",
			       __func__, __LINE__, i);
			जारी;
		पूर्ण

		clk_prepare_enable(clk);

		p->uartclk = clk_get_rate(clk);

		अगर (!p->membase && p->mapbase) अणु
			p->membase = ioremap(p->mapbase, SZ_4K);

			अगर (p->membase)
				p->flags &= ~UPF_IOREMAP;
			अन्यथा
				pr_err("uart regs ioremap failed\n");
		पूर्ण

		अगर (p->membase && p->type != PORT_AR7)
			davinci_serial_reset(p);
	पूर्ण
	वापस ret;
पूर्ण
