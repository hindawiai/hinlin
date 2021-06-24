<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Linaro Ltd.
 * Author: Rob Herring <robh@kernel.org>
 *
 * Based on 8250 earlycon:
 * (c) Copyright 2004 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/sizes.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/acpi.h>

#अगर_घोषित CONFIG_FIX_EARLYCON_MEM
#समावेश <यंत्र/fixmap.h>
#पूर्ण_अगर

#समावेश <यंत्र/serial.h>

अटल काष्ठा console early_con = अणु
	.name =		"uart",		/* fixed up at earlycon registration */
	.flags =	CON_PRINTBUFFER | CON_BOOT,
	.index =	0,
पूर्ण;

अटल काष्ठा earlycon_device early_console_dev = अणु
	.con = &early_con,
पूर्ण;

अटल व्योम __iomem * __init earlycon_map(resource_माप_प्रकार paddr, माप_प्रकार size)
अणु
	व्योम __iomem *base;
#अगर_घोषित CONFIG_FIX_EARLYCON_MEM
	set_fixmap_io(FIX_EARLYCON_MEM_BASE, paddr & PAGE_MASK);
	base = (व्योम __iomem *)__fix_to_virt(FIX_EARLYCON_MEM_BASE);
	base += paddr & ~PAGE_MASK;
#अन्यथा
	base = ioremap(paddr, size);
#पूर्ण_अगर
	अगर (!base)
		pr_err("%s: Couldn't map %pa\n", __func__, &paddr);

	वापस base;
पूर्ण

अटल व्योम __init earlycon_init(काष्ठा earlycon_device *device,
				 स्थिर अक्षर *name)
अणु
	काष्ठा console *earlycon = device->con;
	स्थिर अक्षर *s;
	माप_प्रकार len;

	/* scan backwards from end of string क्रम first non-numeral */
	क्रम (s = name + म_माप(name);
	     s > name && s[-1] >= '0' && s[-1] <= '9';
	     s--)
		;
	अगर (*s)
		earlycon->index = simple_म_से_अदीर्घ(s, शून्य, 10);
	len = s - name;
	strlcpy(earlycon->name, name, min(len + 1, माप(earlycon->name)));
	earlycon->data = &early_console_dev;
पूर्ण

अटल व्योम __init earlycon_prपूर्णांक_info(काष्ठा earlycon_device *device)
अणु
	काष्ठा console *earlycon = device->con;
	काष्ठा uart_port *port = &device->port;

	अगर (port->iotype == UPIO_MEM || port->iotype == UPIO_MEM16 ||
	    port->iotype == UPIO_MEM32 || port->iotype == UPIO_MEM32BE)
		pr_info("%s%d at MMIO%s %pa (options '%s')\n",
			earlycon->name, earlycon->index,
			(port->iotype == UPIO_MEM) ? "" :
			(port->iotype == UPIO_MEM16) ? "16" :
			(port->iotype == UPIO_MEM32) ? "32" : "32be",
			&port->mapbase, device->options);
	अन्यथा
		pr_info("%s%d at I/O port 0x%lx (options '%s')\n",
			earlycon->name, earlycon->index,
			port->iobase, device->options);
पूर्ण

अटल पूर्णांक __init parse_options(काष्ठा earlycon_device *device, अक्षर *options)
अणु
	काष्ठा uart_port *port = &device->port;
	पूर्णांक length;
	resource_माप_प्रकार addr;

	अगर (uart_parse_earlycon(options, &port->iotype, &addr, &options))
		वापस -EINVAL;

	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		port->mapbase = addr;
		अवरोध;
	हाल UPIO_MEM16:
		port->regshअगरt = 1;
		port->mapbase = addr;
		अवरोध;
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
		port->regshअगरt = 2;
		port->mapbase = addr;
		अवरोध;
	हाल UPIO_PORT:
		port->iobase = addr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (options) अणु
		device->baud = simple_म_से_अदीर्घ(options, शून्य, 0);
		length = min(म_खोज(options, " ") + 1,
			     (माप_प्रकार)(माप(device->options)));
		strlcpy(device->options, options, length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init रेजिस्टर_earlycon(अक्षर *buf, स्थिर काष्ठा earlycon_id *match)
अणु
	पूर्णांक err;
	काष्ठा uart_port *port = &early_console_dev.port;

	/* On parsing error, pass the options buf to the setup function */
	अगर (buf && !parse_options(&early_console_dev, buf))
		buf = शून्य;

	spin_lock_init(&port->lock);
	port->uartclk = BASE_BAUD * 16;
	अगर (port->mapbase)
		port->membase = earlycon_map(port->mapbase, 64);

	earlycon_init(&early_console_dev, match->name);
	err = match->setup(&early_console_dev, buf);
	earlycon_prपूर्णांक_info(&early_console_dev);
	अगर (err < 0)
		वापस err;
	अगर (!early_console_dev.con->ग_लिखो)
		वापस -ENODEV;

	रेजिस्टर_console(early_console_dev.con);
	वापस 0;
पूर्ण

/**
 *	setup_earlycon - match and रेजिस्टर earlycon console
 *	@buf:	earlycon param string
 *
 *	Registers the earlycon console matching the earlycon specअगरied
 *	in the param string @buf. Acceptable param strings are of the क्रमm
 *	   <name>,io|mmio|mmio32|mmio32be,<addr>,<options>
 *	   <name>,0x<addr>,<options>
 *	   <name>,<options>
 *	   <name>
 *
 *	Only क्रम the third क्रमm करोes the earlycon setup() method receive the
 *	<options> string in the 'options' parameter; all other क्रमms set
 *	the parameter to शून्य.
 *
 *	Returns 0 अगर an attempt to रेजिस्टर the earlycon was made,
 *	otherwise negative error code
 */
पूर्णांक __init setup_earlycon(अक्षर *buf)
अणु
	स्थिर काष्ठा earlycon_id *match;
	bool empty_compatible = true;

	अगर (!buf || !buf[0])
		वापस -EINVAL;

	अगर (early_con.flags & CON_ENABLED)
		वापस -EALREADY;

again:
	क्रम (match = __earlycon_table; match < __earlycon_table_end; match++) अणु
		माप_प्रकार len = म_माप(match->name);

		अगर (म_भेदन(buf, match->name, len))
			जारी;

		/* prefer entries with empty compatible */
		अगर (empty_compatible && *match->compatible)
			जारी;

		अगर (buf[len]) अणु
			अगर (buf[len] != ',')
				जारी;
			buf += len + 1;
		पूर्ण अन्यथा
			buf = शून्य;

		वापस रेजिस्टर_earlycon(buf, match);
	पूर्ण

	अगर (empty_compatible) अणु
		empty_compatible = false;
		जाओ again;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/*
 * This defers the initialization of the early console until after ACPI has
 * been initialized.
 */
bool earlycon_acpi_spcr_enable __initdata;

/* early_param wrapper क्रम setup_earlycon() */
अटल पूर्णांक __init param_setup_earlycon(अक्षर *buf)
अणु
	पूर्णांक err;

	/* Just 'earlycon' is a valid param क्रम devicetree and ACPI SPCR. */
	अगर (!buf || !buf[0]) अणु
		अगर (IS_ENABLED(CONFIG_ACPI_SPCR_TABLE)) अणु
			earlycon_acpi_spcr_enable = true;
			वापस 0;
		पूर्ण अन्यथा अगर (!buf) अणु
			वापस early_init_dt_scan_chosen_मानक_निकास();
		पूर्ण
	पूर्ण

	err = setup_earlycon(buf);
	अगर (err == -ENOENT || err == -EALREADY)
		वापस 0;
	वापस err;
पूर्ण
early_param("earlycon", param_setup_earlycon);

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE

पूर्णांक __init of_setup_earlycon(स्थिर काष्ठा earlycon_id *match,
			     अचिन्हित दीर्घ node,
			     स्थिर अक्षर *options)
अणु
	पूर्णांक err;
	काष्ठा uart_port *port = &early_console_dev.port;
	स्थिर __be32 *val;
	bool big_endian;
	u64 addr;

	spin_lock_init(&port->lock);
	port->iotype = UPIO_MEM;
	addr = of_flat_dt_translate_address(node);
	अगर (addr == OF_BAD_ADDR) अणु
		pr_warn("[%s] bad address\n", match->name);
		वापस -ENXIO;
	पूर्ण
	port->mapbase = addr;

	val = of_get_flat_dt_prop(node, "reg-offset", शून्य);
	अगर (val)
		port->mapbase += be32_to_cpu(*val);
	port->membase = earlycon_map(port->mapbase, SZ_4K);

	val = of_get_flat_dt_prop(node, "reg-shift", शून्य);
	अगर (val)
		port->regshअगरt = be32_to_cpu(*val);
	big_endian = of_get_flat_dt_prop(node, "big-endian", शून्य) != शून्य ||
		(IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) &&
		 of_get_flat_dt_prop(node, "native-endian", शून्य) != शून्य);
	val = of_get_flat_dt_prop(node, "reg-io-width", शून्य);
	अगर (val) अणु
		चयन (be32_to_cpu(*val)) अणु
		हाल 1:
			port->iotype = UPIO_MEM;
			अवरोध;
		हाल 2:
			port->iotype = UPIO_MEM16;
			अवरोध;
		हाल 4:
			port->iotype = (big_endian) ? UPIO_MEM32BE : UPIO_MEM32;
			अवरोध;
		शेष:
			pr_warn("[%s] unsupported reg-io-width\n", match->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	val = of_get_flat_dt_prop(node, "current-speed", शून्य);
	अगर (val)
		early_console_dev.baud = be32_to_cpu(*val);

	val = of_get_flat_dt_prop(node, "clock-frequency", शून्य);
	अगर (val)
		port->uartclk = be32_to_cpu(*val);

	अगर (options) अणु
		early_console_dev.baud = simple_म_से_अदीर्घ(options, शून्य, 0);
		strlcpy(early_console_dev.options, options,
			माप(early_console_dev.options));
	पूर्ण
	earlycon_init(&early_console_dev, match->name);
	err = match->setup(&early_console_dev, options);
	earlycon_prपूर्णांक_info(&early_console_dev);
	अगर (err < 0)
		वापस err;
	अगर (!early_console_dev.con->ग_लिखो)
		वापस -ENODEV;


	रेजिस्टर_console(early_console_dev.con);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF_EARLY_FLATTREE */
