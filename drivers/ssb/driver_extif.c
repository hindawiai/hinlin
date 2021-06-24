<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom EXTIF core driver
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2006, 2007, Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright 2007, Aurelien Jarno <aurelien@aurel32.net>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>


अटल अंतरभूत u32 extअगर_पढ़ो32(काष्ठा ssb_extअगर *extअगर, u16 offset)
अणु
	वापस ssb_पढ़ो32(extअगर->dev, offset);
पूर्ण

अटल अंतरभूत व्योम extअगर_ग_लिखो32(काष्ठा ssb_extअगर *extअगर, u16 offset, u32 value)
अणु
	ssb_ग_लिखो32(extअगर->dev, offset, value);
पूर्ण

अटल अंतरभूत u32 extअगर_ग_लिखो32_masked(काष्ठा ssb_extअगर *extअगर, u16 offset,
				       u32 mask, u32 value)
अणु
	value &= mask;
	value |= extअगर_पढ़ो32(extअगर, offset) & ~mask;
	extअगर_ग_लिखो32(extअगर, offset, value);

	वापस value;
पूर्ण

#अगर_घोषित CONFIG_SSB_SERIAL
अटल bool serial_exists(u8 *regs)
अणु
	u8 save_mcr, msr = 0;

	अगर (regs) अणु
		save_mcr = regs[UART_MCR];
		regs[UART_MCR] = (UART_MCR_LOOP | UART_MCR_OUT2 | UART_MCR_RTS);
		msr = regs[UART_MSR] & (UART_MSR_DCD | UART_MSR_RI
					| UART_MSR_CTS | UART_MSR_DSR);
		regs[UART_MCR] = save_mcr;
	पूर्ण
	वापस (msr == (UART_MSR_DCD | UART_MSR_CTS));
पूर्ण

पूर्णांक ssb_extअगर_serial_init(काष्ठा ssb_extअगर *extअगर, काष्ठा ssb_serial_port *ports)
अणु
	u32 i, nr_ports = 0;

	/* Disable GPIO पूर्णांकerrupt initially */
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_GPIO_INTPOL, 0);
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_GPIO_INTMASK, 0);

	क्रम (i = 0; i < 2; i++) अणु
		व्योम __iomem *uart_regs;

		uart_regs = ioremap(SSB_EUART, 16);
		अगर (uart_regs) अणु
			uart_regs += (i * 8);

			अगर (serial_exists(uart_regs) && ports) अणु
				extअगर_ग_लिखो32(extअगर, SSB_EXTIF_GPIO_INTMASK, 2);

				nr_ports++;
				ports[i].regs = uart_regs;
				ports[i].irq = 2;
				ports[i].baud_base = 13500000;
				ports[i].reg_shअगरt = 0;
			पूर्ण
			iounmap(uart_regs);
		पूर्ण
	पूर्ण
	वापस nr_ports;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SERIAL */

व्योम ssb_extअगर_timing_init(काष्ठा ssb_extअगर *extअगर, अचिन्हित दीर्घ ns)
अणु
	u32 पंचांगp;

	/* Initialize extअगर so we can get to the LEDs and बाह्यal UART */
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_PROG_CFG, SSB_EXTCFG_EN);

	/* Set timing क्रम the flash */
	पंचांगp  = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;
	पंचांगp |= DIV_ROUND_UP(40, ns) << SSB_PROG_WCNT_1_SHIFT;
	पंचांगp |= DIV_ROUND_UP(120, ns);
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_PROG_WAITCNT, पंचांगp);

	/* Set programmable पूर्णांकerface timing क्रम बाह्यal uart */
	पंचांगp  = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;
	पंचांगp |= DIV_ROUND_UP(20, ns) << SSB_PROG_WCNT_2_SHIFT;
	पंचांगp |= DIV_ROUND_UP(100, ns) << SSB_PROG_WCNT_1_SHIFT;
	पंचांगp |= DIV_ROUND_UP(120, ns);
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_PROG_WAITCNT, पंचांगp);
पूर्ण

व्योम ssb_extअगर_get_घड़ीcontrol(काष्ठा ssb_extअगर *extअगर,
				u32 *pll_type, u32 *n, u32 *m)
अणु
	*pll_type = SSB_PLLTYPE_1;
	*n = extअगर_पढ़ो32(extअगर, SSB_EXTIF_CLOCK_N);
	*m = extअगर_पढ़ो32(extअगर, SSB_EXTIF_CLOCK_SB);
पूर्ण

u32 ssb_extअगर_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt, u32 ticks)
अणु
	काष्ठा ssb_extअगर *extअगर = bcm47xx_wdt_get_drvdata(wdt);

	वापस ssb_extअगर_watchकरोg_समयr_set(extअगर, ticks);
पूर्ण

u32 ssb_extअगर_watchकरोg_समयr_set_ms(काष्ठा bcm47xx_wdt *wdt, u32 ms)
अणु
	काष्ठा ssb_extअगर *extअगर = bcm47xx_wdt_get_drvdata(wdt);
	u32 ticks = (SSB_EXTIF_WATCHDOG_CLK / 1000) * ms;

	ticks = ssb_extअगर_watchकरोg_समयr_set(extअगर, ticks);

	वापस (ticks * 1000) / SSB_EXTIF_WATCHDOG_CLK;
पूर्ण

u32 ssb_extअगर_watchकरोg_समयr_set(काष्ठा ssb_extअगर *extअगर, u32 ticks)
अणु
	अगर (ticks > SSB_EXTIF_WATCHDOG_MAX_TIMER)
		ticks = SSB_EXTIF_WATCHDOG_MAX_TIMER;
	extअगर_ग_लिखो32(extअगर, SSB_EXTIF_WATCHDOG, ticks);

	वापस ticks;
पूर्ण

व्योम ssb_extअगर_init(काष्ठा ssb_extअगर *extअगर)
अणु
	अगर (!extअगर->dev)
		वापस; /* We करोn't have a Extअगर core */
	spin_lock_init(&extअगर->gpio_lock);
पूर्ण

u32 ssb_extअगर_gpio_in(काष्ठा ssb_extअगर *extअगर, u32 mask)
अणु
	वापस extअगर_पढ़ो32(extअगर, SSB_EXTIF_GPIO_IN) & mask;
पूर्ण

u32 ssb_extअगर_gpio_out(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&extअगर->gpio_lock, flags);
	res = extअगर_ग_लिखो32_masked(extअगर, SSB_EXTIF_GPIO_OUT(0),
				   mask, value);
	spin_unlock_irqrestore(&extअगर->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_extअगर_gpio_outen(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&extअगर->gpio_lock, flags);
	res = extअगर_ग_लिखो32_masked(extअगर, SSB_EXTIF_GPIO_OUTEN(0),
				   mask, value);
	spin_unlock_irqrestore(&extअगर->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_extअगर_gpio_polarity(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&extअगर->gpio_lock, flags);
	res = extअगर_ग_लिखो32_masked(extअगर, SSB_EXTIF_GPIO_INTPOL, mask, value);
	spin_unlock_irqrestore(&extअगर->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_extअगर_gpio_पूर्णांकmask(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&extअगर->gpio_lock, flags);
	res = extअगर_ग_लिखो32_masked(extअगर, SSB_EXTIF_GPIO_INTMASK, mask, value);
	spin_unlock_irqrestore(&extअगर->gpio_lock, flags);

	वापस res;
पूर्ण
