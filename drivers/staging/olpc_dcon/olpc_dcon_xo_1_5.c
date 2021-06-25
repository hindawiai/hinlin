<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2009,2010       One Laptop per Child
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/olpc.h>

/* TODO: this eventually beदीर्घs in linux/vx855.h */
#घोषणा NR_VX855_GPI    14
#घोषणा NR_VX855_GPO    13
#घोषणा NR_VX855_GPIO   15

#घोषणा VX855_GPI(n)    (n)
#घोषणा VX855_GPO(n)    (NR_VX855_GPI + (n))
#घोषणा VX855_GPIO(n)   (NR_VX855_GPI + NR_VX855_GPO + (n))

#समावेश "olpc_dcon.h"

/* Hardware setup on the XO 1.5:
 *	DCONLOAD connects to VX855_GPIO1 (not SMBCK2)
 *	DCONBLANK connects to VX855_GPIO8 (not SSPICLK)  unused in driver
 *	DCONSTAT0 connects to VX855_GPI10 (not SSPISDI)
 *	DCONSTAT1 connects to VX855_GPI11 (not nSSPISS)
 *	DCONIRQ connects to VX855_GPIO12
 *	DCONSMBDATA connects to VX855 graphics CRTSPD
 *	DCONSMBCLK connects to VX855 graphics CRTSPCLK
 */

#घोषणा VX855_GENL_PURPOSE_OUTPUT 0x44c /* PMIO_Rx4c-4f */
#घोषणा VX855_GPI_STATUS_CHG 0x450  /* PMIO_Rx50 */
#घोषणा VX855_GPI_SCI_SMI 0x452  /* PMIO_Rx52 */
#घोषणा BIT_GPIO12 0x40

#घोषणा PREFIX "OLPC DCON:"

क्रमागत dcon_gpios अणु
	OLPC_DCON_STAT0,
	OLPC_DCON_STAT1,
	OLPC_DCON_LOAD,
पूर्ण;

काष्ठा gpiod_lookup_table gpios_table = अणु
	.dev_id = शून्य,
	.table = अणु
		GPIO_LOOKUP("VX855 South Bridge", VX855_GPIO(1), "dcon_load",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("VX855 South Bridge", VX855_GPI(10), "dcon_stat0",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("VX855 South Bridge", VX855_GPI(11), "dcon_stat1",
			    GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dcon_gpio gpios_asis[] = अणु
	[OLPC_DCON_STAT0] = अणु .name = "dcon_stat0", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_STAT1] = अणु .name = "dcon_stat1", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_LOAD] = अणु .name = "dcon_load", .flags = GPIOD_ASIS पूर्ण,
पूर्ण;

अटल काष्ठा gpio_desc *gpios[3];

अटल व्योम dcon_clear_irq(व्योम)
अणु
	/* irq status will appear in PMIO_Rx50[6] (RW1C) on gpio12 */
	outb(BIT_GPIO12, VX855_GPI_STATUS_CHG);
पूर्ण

अटल पूर्णांक dcon_was_irq(व्योम)
अणु
	u8 पंचांगp;

	/* irq status will appear in PMIO_Rx50[6] on gpio12 */
	पंचांगp = inb(VX855_GPI_STATUS_CHG);

	वापस !!(पंचांगp & BIT_GPIO12);
पूर्ण

अटल पूर्णांक dcon_init_xo_1_5(काष्ठा dcon_priv *dcon)
अणु
	अचिन्हित पूर्णांक irq;
	स्थिर काष्ठा dcon_gpio *pin = &gpios_asis[0];
	पूर्णांक i;
	पूर्णांक ret;

	/* Add GPIO look up table */
	gpios_table.dev_id = dev_name(&dcon->client->dev);
	gpiod_add_lookup_table(&gpios_table);

	/* Get GPIO descriptor */
	क्रम (i = 0; i < ARRAY_SIZE(gpios_asis); i++) अणु
		gpios[i] = devm_gpiod_get(&dcon->client->dev, pin[i].name,
					  pin[i].flags);
		अगर (IS_ERR(gpios[i])) अणु
			ret = PTR_ERR(gpios[i]);
			pr_err("failed to request %s GPIO: %d\n", pin[i].name,
			       ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dcon_clear_irq();

	/* set   PMIO_Rx52[6] to enable SCI/SMI on gpio12 */
	outb(inb(VX855_GPI_SCI_SMI) | BIT_GPIO12, VX855_GPI_SCI_SMI);

	/* Determine the current state of DCONLOAD, likely set by firmware */
	/* GPIO1 */
	dcon->curr_src = (inl(VX855_GENL_PURPOSE_OUTPUT) & 0x1000) ?
			DCON_SOURCE_CPU : DCON_SOURCE_DCON;
	dcon->pending_src = dcon->curr_src;

	/* we're sharing the IRQ with ACPI */
	irq = acpi_gbl_FADT.sci_पूर्णांकerrupt;
	अगर (request_irq(irq, &dcon_पूर्णांकerrupt, IRQF_SHARED, "DCON", dcon)) अणु
		pr_err("DCON (IRQ%d) allocation failed\n", irq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_i2c_line(पूर्णांक sda, पूर्णांक scl)
अणु
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित पूर्णांक port = 0x26;

	/* FIXME: This directly accesses the CRT GPIO controller !!! */
	outb(port, 0x3c4);
	पंचांगp = inb(0x3c5);

	अगर (scl)
		पंचांगp |= 0x20;
	अन्यथा
		पंचांगp &= ~0x20;

	अगर (sda)
		पंचांगp |= 0x10;
	अन्यथा
		पंचांगp &= ~0x10;

	पंचांगp |= 0x01;

	outb(port, 0x3c4);
	outb(पंचांगp, 0x3c5);
पूर्ण

अटल व्योम dcon_wiggle_xo_1_5(व्योम)
अणु
	पूर्णांक x;

	/*
	 * According to HiMax, when घातering the DCON up we should hold
	 * SMB_DATA high क्रम 8 SMB_CLK cycles.  This will क्रमce the DCON
	 * state machine to reset to a (sane) initial state.  Mitch Bradley
	 * did some testing and discovered that holding क्रम 16 SMB_CLK cycles
	 * worked a lot more reliably, so that's what we करो here.
	 */
	set_i2c_line(1, 1);

	क्रम (x = 0; x < 16; x++) अणु
		udelay(5);
		set_i2c_line(1, 0);
		udelay(5);
		set_i2c_line(1, 1);
	पूर्ण
	udelay(5);

	/* set   PMIO_Rx52[6] to enable SCI/SMI on gpio12 */
	outb(inb(VX855_GPI_SCI_SMI) | BIT_GPIO12, VX855_GPI_SCI_SMI);
पूर्ण

अटल व्योम dcon_set_dconload_xo_1_5(पूर्णांक val)
अणु
	gpiod_set_value(gpios[OLPC_DCON_LOAD], val);
पूर्ण

अटल पूर्णांक dcon_पढ़ो_status_xo_1_5(u8 *status)
अणु
	अगर (!dcon_was_irq())
		वापस -1;

	/* i believe this is the same as "inb(0x44b) & 3" */
	*status = gpiod_get_value(gpios[OLPC_DCON_STAT0]);
	*status |= gpiod_get_value(gpios[OLPC_DCON_STAT1]) << 1;

	dcon_clear_irq();

	वापस 0;
पूर्ण

काष्ठा dcon_platक्रमm_data dcon_pdata_xo_1_5 = अणु
	.init = dcon_init_xo_1_5,
	.bus_stabilize_wiggle = dcon_wiggle_xo_1_5,
	.set_dconload = dcon_set_dconload_xo_1_5,
	.पढ़ो_status = dcon_पढ़ो_status_xo_1_5,
पूर्ण;
