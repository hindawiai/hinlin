<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Serial Port driver क्रम Aspeed VUART device
 *
 *    Copyright (C) 2016 Jeremy Kerr <jk@ozद_असल.org>, IBM Corp.
 *    Copyright (C) 2006 Arnd Bergmann <arnd@arndb.de>, IBM Corp.
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/clk.h>

#समावेश "8250.h"

#घोषणा ASPEED_VUART_GCRA		0x20
#घोषणा ASPEED_VUART_GCRA_VUART_EN		BIT(0)
#घोषणा ASPEED_VUART_GCRA_HOST_SIRQ_POLARITY	BIT(1)
#घोषणा ASPEED_VUART_GCRA_DISABLE_HOST_TX_DISCARD BIT(5)
#घोषणा ASPEED_VUART_GCRB		0x24
#घोषणा ASPEED_VUART_GCRB_HOST_SIRQ_MASK	GENMASK(7, 4)
#घोषणा ASPEED_VUART_GCRB_HOST_SIRQ_SHIFT	4
#घोषणा ASPEED_VUART_ADDRL		0x28
#घोषणा ASPEED_VUART_ADDRH		0x2c

#घोषणा ASPEED_VUART_DEFAULT_LPC_ADDR	0x3f8
#घोषणा ASPEED_VUART_DEFAULT_SIRQ	4
#घोषणा ASPEED_VUART_DEFAULT_SIRQ_POLARITY	IRQ_TYPE_LEVEL_LOW

काष्ठा aspeed_vuart अणु
	काष्ठा device		*dev;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	पूर्णांक			line;
	काष्ठा समयr_list	unthrottle_समयr;
	काष्ठा uart_8250_port	*port;
पूर्ण;

/*
 * If we fill the tty flip buffers, we throttle the data पढ़ोy पूर्णांकerrupt
 * to prevent dropped अक्षरacters. This समयout defines how दीर्घ we रुको
 * to (conditionally, depending on buffer state) unthrottle.
 */
अटल स्थिर पूर्णांक unthrottle_समयout = HZ/10;

/*
 * The VUART is basically two UART 'front ends' connected by their FIFO
 * (no actual serial line in between). One is on the BMC side (management
 * controller) and one is on the host CPU side.
 *
 * It allows the BMC to provide to the host a "UART" that pipes पूर्णांकo
 * the BMC itself and can then be turned by the BMC पूर्णांकo a network console
 * of some sort क्रम example.
 *
 * This driver is क्रम the BMC side. The sysfs files allow the BMC
 * userspace which owns the प्रणाली configuration policy, to specअगरy
 * at what IO port and पूर्णांकerrupt number the host side will appear
 * to the host on the Host <-> BMC LPC bus. It could be dअगरferent on a
 * dअगरferent प्रणाली (though most of them use 3f8/4).
 */

अटल sमाप_प्रकार lpc_address_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	u16 addr;

	addr = (पढ़ोb(vuart->regs + ASPEED_VUART_ADDRH) << 8) |
		(पढ़ोb(vuart->regs + ASPEED_VUART_ADDRL));

	वापस snम_लिखो(buf, PAGE_SIZE - 1, "0x%x\n", addr);
पूर्ण

अटल पूर्णांक aspeed_vuart_set_lpc_address(काष्ठा aspeed_vuart *vuart, u32 addr)
अणु
	अगर (addr > U16_MAX)
		वापस -EINVAL;

	ग_लिखोb(addr >> 8, vuart->regs + ASPEED_VUART_ADDRH);
	ग_लिखोb(addr >> 0, vuart->regs + ASPEED_VUART_ADDRL);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार lpc_address_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	u32 val;
	पूर्णांक err;

	err = kstrtou32(buf, 0, &val);
	अगर (err)
		वापस err;

	err = aspeed_vuart_set_lpc_address(vuart, val);
	वापस err ? : count;
पूर्ण

अटल DEVICE_ATTR_RW(lpc_address);

अटल sमाप_प्रकार sirq_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	u8 reg;

	reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRB);
	reg &= ASPEED_VUART_GCRB_HOST_SIRQ_MASK;
	reg >>= ASPEED_VUART_GCRB_HOST_SIRQ_SHIFT;

	वापस snम_लिखो(buf, PAGE_SIZE - 1, "%u\n", reg);
पूर्ण

अटल पूर्णांक aspeed_vuart_set_sirq(काष्ठा aspeed_vuart *vuart, u32 sirq)
अणु
	u8 reg;

	अगर (sirq > (ASPEED_VUART_GCRB_HOST_SIRQ_MASK >> ASPEED_VUART_GCRB_HOST_SIRQ_SHIFT))
		वापस -EINVAL;

	sirq <<= ASPEED_VUART_GCRB_HOST_SIRQ_SHIFT;
	sirq &= ASPEED_VUART_GCRB_HOST_SIRQ_MASK;

	reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRB);
	reg &= ~ASPEED_VUART_GCRB_HOST_SIRQ_MASK;
	reg |= sirq;
	ग_लिखोb(reg, vuart->regs + ASPEED_VUART_GCRB);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sirq_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	err = aspeed_vuart_set_sirq(vuart, val);
	वापस err ? : count;
पूर्ण

अटल DEVICE_ATTR_RW(sirq);

अटल sमाप_प्रकार sirq_polarity_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	u8 reg;

	reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRA);
	reg &= ASPEED_VUART_GCRA_HOST_SIRQ_POLARITY;

	वापस snम_लिखो(buf, PAGE_SIZE - 1, "%u\n", reg ? 1 : 0);
पूर्ण

अटल व्योम aspeed_vuart_set_sirq_polarity(काष्ठा aspeed_vuart *vuart,
					   bool polarity)
अणु
	u8 reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRA);

	अगर (polarity)
		reg |= ASPEED_VUART_GCRA_HOST_SIRQ_POLARITY;
	अन्यथा
		reg &= ~ASPEED_VUART_GCRA_HOST_SIRQ_POLARITY;

	ग_लिखोb(reg, vuart->regs + ASPEED_VUART_GCRA);
पूर्ण

अटल sमाप_प्रकार sirq_polarity_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aspeed_vuart *vuart = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	aspeed_vuart_set_sirq_polarity(vuart, val != 0);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(sirq_polarity);

अटल काष्ठा attribute *aspeed_vuart_attrs[] = अणु
	&dev_attr_sirq.attr,
	&dev_attr_sirq_polarity.attr,
	&dev_attr_lpc_address.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group aspeed_vuart_attr_group = अणु
	.attrs = aspeed_vuart_attrs,
पूर्ण;

अटल व्योम aspeed_vuart_set_enabled(काष्ठा aspeed_vuart *vuart, bool enabled)
अणु
	u8 reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRA);

	अगर (enabled)
		reg |= ASPEED_VUART_GCRA_VUART_EN;
	अन्यथा
		reg &= ~ASPEED_VUART_GCRA_VUART_EN;

	ग_लिखोb(reg, vuart->regs + ASPEED_VUART_GCRA);
पूर्ण

अटल व्योम aspeed_vuart_set_host_tx_discard(काष्ठा aspeed_vuart *vuart,
					     bool discard)
अणु
	u8 reg;

	reg = पढ़ोb(vuart->regs + ASPEED_VUART_GCRA);

	/* If the DISABLE_HOST_TX_DISCARD bit is set, discard is disabled */
	अगर (!discard)
		reg |= ASPEED_VUART_GCRA_DISABLE_HOST_TX_DISCARD;
	अन्यथा
		reg &= ~ASPEED_VUART_GCRA_DISABLE_HOST_TX_DISCARD;

	ग_लिखोb(reg, vuart->regs + ASPEED_VUART_GCRA);
पूर्ण

अटल पूर्णांक aspeed_vuart_startup(काष्ठा uart_port *uart_port)
अणु
	काष्ठा uart_8250_port *uart_8250_port = up_to_u8250p(uart_port);
	काष्ठा aspeed_vuart *vuart = uart_8250_port->port.निजी_data;
	पूर्णांक rc;

	rc = serial8250_करो_startup(uart_port);
	अगर (rc)
		वापस rc;

	aspeed_vuart_set_host_tx_discard(vuart, false);

	वापस 0;
पूर्ण

अटल व्योम aspeed_vuart_shutकरोwn(काष्ठा uart_port *uart_port)
अणु
	काष्ठा uart_8250_port *uart_8250_port = up_to_u8250p(uart_port);
	काष्ठा aspeed_vuart *vuart = uart_8250_port->port.निजी_data;

	aspeed_vuart_set_host_tx_discard(vuart, true);

	serial8250_करो_shutकरोwn(uart_port);
पूर्ण

अटल व्योम __aspeed_vuart_set_throttle(काष्ठा uart_8250_port *up,
		bool throttle)
अणु
	अचिन्हित अक्षर irqs = UART_IER_RLSI | UART_IER_RDI;

	up->ier &= ~irqs;
	अगर (!throttle)
		up->ier |= irqs;
	serial_out(up, UART_IER, up->ier);
पूर्ण
अटल व्योम aspeed_vuart_set_throttle(काष्ठा uart_port *port, bool throttle)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	__aspeed_vuart_set_throttle(up, throttle);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम aspeed_vuart_throttle(काष्ठा uart_port *port)
अणु
	aspeed_vuart_set_throttle(port, true);
पूर्ण

अटल व्योम aspeed_vuart_unthrottle(काष्ठा uart_port *port)
अणु
	aspeed_vuart_set_throttle(port, false);
पूर्ण

अटल व्योम aspeed_vuart_unthrottle_exp(काष्ठा समयr_list *समयr)
अणु
	काष्ठा aspeed_vuart *vuart = from_समयr(vuart, समयr, unthrottle_समयr);
	काष्ठा uart_8250_port *up = vuart->port;

	अगर (!tty_buffer_space_avail(&up->port.state->port)) अणु
		mod_समयr(&vuart->unthrottle_समयr,
			  jअगरfies + unthrottle_समयout);
		वापस;
	पूर्ण

	aspeed_vuart_unthrottle(&up->port);
पूर्ण

/*
 * Custom पूर्णांकerrupt handler to manage finer-grained flow control. Although we
 * have throttle/unthrottle callbacks, we've seen that the VUART device can
 * deliver अक्षरacters faster than the ldisc has a chance to check buffer space
 * against the throttle threshold. This results in dropped अक्षरacters beक्रमe
 * the throttle.
 *
 * We करो this by checking क्रम flip buffer space beक्रमe RX. If we have no space,
 * throttle now and schedule an unthrottle क्रम later, once the ldisc has had
 * a chance to drain the buffers.
 */
अटल पूर्णांक aspeed_vuart_handle_irq(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक iir, lsr;
	पूर्णांक space, count;

	iir = serial_port_in(port, UART_IIR);

	अगर (iir & UART_IIR_NO_INT)
		वापस 0;

	spin_lock(&port->lock);

	lsr = serial_port_in(port, UART_LSR);

	अगर (lsr & (UART_LSR_DR | UART_LSR_BI)) अणु
		space = tty_buffer_space_avail(&port->state->port);

		अगर (!space) अणु
			/* throttle and schedule an unthrottle later */
			काष्ठा aspeed_vuart *vuart = port->निजी_data;
			__aspeed_vuart_set_throttle(up, true);

			अगर (!समयr_pending(&vuart->unthrottle_समयr)) अणु
				vuart->port = up;
				mod_समयr(&vuart->unthrottle_समयr,
					  jअगरfies + unthrottle_समयout);
			पूर्ण

		पूर्ण अन्यथा अणु
			count = min(space, 256);

			करो अणु
				serial8250_पढ़ो_अक्षर(up, lsr);
				lsr = serial_in(up, UART_LSR);
				अगर (--count == 0)
					अवरोध;
			पूर्ण जबतक (lsr & (UART_LSR_DR | UART_LSR_BI));

			tty_flip_buffer_push(&port->state->port);
		पूर्ण
	पूर्ण

	serial8250_modem_status(up);
	अगर (lsr & UART_LSR_THRE)
		serial8250_tx_अक्षरs(up);

	uart_unlock_and_check_sysrq(port);

	वापस 1;
पूर्ण

अटल व्योम aspeed_vuart_स्वतः_configure_sirq_polarity(
	काष्ठा aspeed_vuart *vuart, काष्ठा device_node *syscon_np,
	u32 reg_offset, u32 reg_mask)
अणु
	काष्ठा regmap *regmap;
	u32 value;

	regmap = syscon_node_to_regmap(syscon_np);
	अगर (IS_ERR(regmap)) अणु
		dev_warn(vuart->dev,
			 "could not get regmap for aspeed,sirq-polarity-sense\n");
		वापस;
	पूर्ण
	अगर (regmap_पढ़ो(regmap, reg_offset, &value)) अणु
		dev_warn(vuart->dev, "could not read hw strap table\n");
		वापस;
	पूर्ण

	aspeed_vuart_set_sirq_polarity(vuart, (value & reg_mask) == 0);
पूर्ण

अटल पूर्णांक aspeed_vuart_map_irq_polarity(u32 dt)
अणु
	चयन (dt) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		वापस 0;
	हाल IRQ_TYPE_LEVEL_HIGH:
		वापस 1;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aspeed_vuart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा of_phandle_args sirq_polarity_sense_args;
	काष्ठा uart_8250_port port;
	काष्ठा aspeed_vuart *vuart;
	काष्ठा device_node *np;
	काष्ठा resource *res;
	u32 clk, prop, sirq[2];
	पूर्णांक rc, sirq_polarity;

	np = pdev->dev.of_node;

	vuart = devm_kzalloc(&pdev->dev, माप(*vuart), GFP_KERNEL);
	अगर (!vuart)
		वापस -ENOMEM;

	vuart->dev = &pdev->dev;
	समयr_setup(&vuart->unthrottle_समयr, aspeed_vuart_unthrottle_exp, 0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vuart->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(vuart->regs))
		वापस PTR_ERR(vuart->regs);

	स_रखो(&port, 0, माप(port));
	port.port.निजी_data = vuart;
	port.port.membase = vuart->regs;
	port.port.mapbase = res->start;
	port.port.mapsize = resource_size(res);
	port.port.startup = aspeed_vuart_startup;
	port.port.shutकरोwn = aspeed_vuart_shutकरोwn;
	port.port.throttle = aspeed_vuart_throttle;
	port.port.unthrottle = aspeed_vuart_unthrottle;
	port.port.status = UPSTAT_SYNC_FIFO;
	port.port.dev = &pdev->dev;
	port.port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_8250_CONSOLE);
	port.bugs |= UART_BUG_TXRACE;

	rc = sysfs_create_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	अगर (rc < 0)
		वापस rc;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &clk)) अणु
		vuart->clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(vuart->clk)) अणु
			dev_warn(&pdev->dev,
				"clk or clock-frequency not defined\n");
			rc = PTR_ERR(vuart->clk);
			जाओ err_sysfs_हटाओ;
		पूर्ण

		rc = clk_prepare_enable(vuart->clk);
		अगर (rc < 0)
			जाओ err_sysfs_हटाओ;

		clk = clk_get_rate(vuart->clk);
	पूर्ण

	/* If current-speed was set, then try not to change it. */
	अगर (of_property_पढ़ो_u32(np, "current-speed", &prop) == 0)
		port.port.custom_भागisor = clk / (16 * prop);

	/* Check क्रम shअगरted address mapping */
	अगर (of_property_पढ़ो_u32(np, "reg-offset", &prop) == 0)
		port.port.mapbase += prop;

	/* Check क्रम रेजिस्टरs offset within the devices address range */
	अगर (of_property_पढ़ो_u32(np, "reg-shift", &prop) == 0)
		port.port.regshअगरt = prop;

	/* Check क्रम fअगरo size */
	अगर (of_property_पढ़ो_u32(np, "fifo-size", &prop) == 0)
		port.port.fअगरosize = prop;

	/* Check क्रम a fixed line number */
	rc = of_alias_get_id(np, "serial");
	अगर (rc >= 0)
		port.port.line = rc;

	port.port.irq = irq_of_parse_and_map(np, 0);
	port.port.handle_irq = aspeed_vuart_handle_irq;
	port.port.iotype = UPIO_MEM;
	port.port.type = PORT_16550A;
	port.port.uartclk = clk;
	port.port.flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF
		| UPF_FIXED_PORT | UPF_FIXED_TYPE | UPF_NO_THRE_TEST;

	अगर (of_property_पढ़ो_bool(np, "no-loopback-test"))
		port.port.flags |= UPF_SKIP_TEST;

	अगर (port.port.fअगरosize)
		port.capabilities = UART_CAP_FIFO;

	अगर (of_property_पढ़ो_bool(np, "auto-flow-control"))
		port.capabilities |= UART_CAP_AFE;

	rc = serial8250_रेजिस्टर_8250_port(&port);
	अगर (rc < 0)
		जाओ err_clk_disable;

	vuart->line = rc;

	rc = of_parse_phandle_with_fixed_args(
		np, "aspeed,sirq-polarity-sense", 2, 0,
		&sirq_polarity_sense_args);
	अगर (rc < 0) अणु
		dev_dbg(&pdev->dev,
			"aspeed,sirq-polarity-sense property not found\n");
	पूर्ण अन्यथा अणु
		aspeed_vuart_स्वतः_configure_sirq_polarity(
			vuart, sirq_polarity_sense_args.np,
			sirq_polarity_sense_args.args[0],
			BIT(sirq_polarity_sense_args.args[1]));
		of_node_put(sirq_polarity_sense_args.np);
	पूर्ण

	rc = of_property_पढ़ो_u32(np, "aspeed,lpc-io-reg", &prop);
	अगर (rc < 0)
		prop = ASPEED_VUART_DEFAULT_LPC_ADDR;

	rc = aspeed_vuart_set_lpc_address(vuart, prop);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "invalid value in aspeed,lpc-io-reg property\n");
		जाओ err_clk_disable;
	पूर्ण

	rc = of_property_पढ़ो_u32_array(np, "aspeed,lpc-interrupts", sirq, 2);
	अगर (rc < 0) अणु
		sirq[0] = ASPEED_VUART_DEFAULT_SIRQ;
		sirq[1] = ASPEED_VUART_DEFAULT_SIRQ_POLARITY;
	पूर्ण

	rc = aspeed_vuart_set_sirq(vuart, sirq[0]);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "invalid sirq number in aspeed,lpc-interrupts property\n");
		जाओ err_clk_disable;
	पूर्ण

	sirq_polarity = aspeed_vuart_map_irq_polarity(sirq[1]);
	अगर (sirq_polarity < 0) अणु
		dev_err(&pdev->dev, "invalid sirq polarity in aspeed,lpc-interrupts property\n");
		rc = sirq_polarity;
		जाओ err_clk_disable;
	पूर्ण

	aspeed_vuart_set_sirq_polarity(vuart, sirq_polarity);

	aspeed_vuart_set_enabled(vuart, true);
	aspeed_vuart_set_host_tx_discard(vuart, true);
	platक्रमm_set_drvdata(pdev, vuart);

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(vuart->clk);
	irq_dispose_mapping(port.port.irq);
err_sysfs_हटाओ:
	sysfs_हटाओ_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	वापस rc;
पूर्ण

अटल पूर्णांक aspeed_vuart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_vuart *vuart = platक्रमm_get_drvdata(pdev);

	del_समयr_sync(&vuart->unthrottle_समयr);
	aspeed_vuart_set_enabled(vuart, false);
	serial8250_unरेजिस्टर_port(vuart->line);
	sysfs_हटाओ_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	clk_disable_unprepare(vuart->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_vuart_table[] = अणु
	अणु .compatible = "aspeed,ast2400-vuart" पूर्ण,
	अणु .compatible = "aspeed,ast2500-vuart" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_vuart_driver = अणु
	.driver = अणु
		.name = "aspeed-vuart",
		.of_match_table = aspeed_vuart_table,
	पूर्ण,
	.probe = aspeed_vuart_probe,
	.हटाओ = aspeed_vuart_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_vuart_driver);

MODULE_AUTHOR("Jeremy Kerr <jk@ozlabs.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for Aspeed VUART device");
