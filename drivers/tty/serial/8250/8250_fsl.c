<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale 16550 UART "driver", Copyright (C) 2011 Paul Gorपंचांगaker.
 * Copyright 2020 NXP
 * Copyright 2020 Puresoftware Ltd.
 *
 * This isn't a full driver; it just provides an alternate IRQ
 * handler to deal with an errata and provide ACPI wrapper.
 * Everything अन्यथा is just using the bog standard 8250 support.
 *
 * We follow code flow of serial8250_शेष_handle_irq() but add
 * a check क्रम a अवरोध and insert a dummy पढ़ो on the Rx क्रम the
 * immediately following IRQ event.
 *
 * We re-use the alपढ़ोy existing "bug handling" lsr_saved_flags
 * field to carry the "what we just did" inक्रमmation from the one
 * IRQ event to the next one.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_8250.h>

#समावेश "8250.h"

काष्ठा fsl8250_data अणु
	पूर्णांक	line;
पूर्ण;

पूर्णांक fsl8250_handle_irq(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर lsr, orig_lsr;
	अचिन्हित पूर्णांक iir;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	spin_lock(&up->port.lock);

	iir = port->serial_in(port, UART_IIR);
	अगर (iir & UART_IIR_NO_INT) अणु
		spin_unlock(&up->port.lock);
		वापस 0;
	पूर्ण

	/* This is the WAR; अगर last event was BRK, then पढ़ो and वापस */
	अगर (unlikely(up->lsr_saved_flags & UART_LSR_BI)) अणु
		up->lsr_saved_flags &= ~UART_LSR_BI;
		port->serial_in(port, UART_RX);
		spin_unlock(&up->port.lock);
		वापस 1;
	पूर्ण

	lsr = orig_lsr = up->port.serial_in(&up->port, UART_LSR);

	/* Process incoming अक्षरacters first */
	अगर ((lsr & (UART_LSR_DR | UART_LSR_BI)) &&
	    (up->ier & (UART_IER_RLSI | UART_IER_RDI))) अणु
		lsr = serial8250_rx_अक्षरs(up, lsr);
	पूर्ण

	/* Stop processing पूर्णांकerrupts on input overrun */
	अगर ((orig_lsr & UART_LSR_OE) && (up->overrun_backoff_समय_ms > 0)) अणु
		अचिन्हित दीर्घ delay;

		up->ier = port->serial_in(port, UART_IER);
		अगर (up->ier & (UART_IER_RLSI | UART_IER_RDI)) अणु
			port->ops->stop_rx(port);
		पूर्ण अन्यथा अणु
			/* Keep restarting the समयr until
			 * the input overrun subsides.
			 */
			cancel_delayed_work(&up->overrun_backoff);
		पूर्ण

		delay = msecs_to_jअगरfies(up->overrun_backoff_समय_ms);
		schedule_delayed_work(&up->overrun_backoff, delay);
	पूर्ण

	serial8250_modem_status(up);

	अगर ((lsr & UART_LSR_THRE) && (up->ier & UART_IER_THRI))
		serial8250_tx_अक्षरs(up);

	up->lsr_saved_flags = orig_lsr;

	uart_unlock_and_check_sysrq(&up->port);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(fsl8250_handle_irq);

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक fsl8250_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl8250_data *data;
	काष्ठा uart_8250_port port8250;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *regs;

	पूर्णांक ret, irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(dev, "no registers defined\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	स_रखो(&port8250, 0, माप(port8250));

	ret = device_property_पढ़ो_u32(dev, "clock-frequency",
					&port8250.port.uartclk);
	अगर (ret)
		वापस ret;

	spin_lock_init(&port8250.port.lock);

	port8250.port.mapbase           = regs->start;
	port8250.port.irq               = irq;
	port8250.port.handle_irq        = fsl8250_handle_irq;
	port8250.port.type              = PORT_16550A;
	port8250.port.flags             = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF
						| UPF_FIXED_PORT | UPF_IOREMAP
						| UPF_FIXED_TYPE;
	port8250.port.dev               = dev;
	port8250.port.mapsize           = resource_size(regs);
	port8250.port.iotype            = UPIO_MEM;
	port8250.port.irqflags          = IRQF_SHARED;

	port8250.port.membase = devm_ioremap(dev,  port8250.port.mapbase,
							port8250.port.mapsize);
	अगर (!port8250.port.membase)
		वापस -ENOMEM;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->line = serial8250_रेजिस्टर_8250_port(&port8250);
	अगर (data->line < 0)
		वापस data->line;

	platक्रमm_set_drvdata(pdev, data);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl8250_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl8250_data *data = platक्रमm_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(data->line);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id fsl_8250_acpi_id[] = अणु
	अणु "NXP0018", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fsl_8250_acpi_id);

अटल काष्ठा platक्रमm_driver fsl8250_platक्रमm_driver = अणु
	.driver = अणु
		.name			= "fsl-16550-uart",
		.acpi_match_table	= ACPI_PTR(fsl_8250_acpi_id),
	पूर्ण,
	.probe			= fsl8250_acpi_probe,
	.हटाओ			= fsl8250_acpi_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl8250_platक्रमm_driver);
#पूर्ण_अगर
