<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * GPIO पूर्णांकerface क्रम Winbond Super I/O chips
 * Currently, only W83627UHG (Nuvoton NCT6627UD) is supported.
 *
 * Author: Maciej S. Szmigiero <mail@maciej.szmigiero.name>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/gpio/driver.h>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/module.h>

#घोषणा WB_GPIO_DRIVER_NAME		KBUILD_MODNAME

#घोषणा WB_SIO_BASE			0x2e
#घोषणा WB_SIO_BASE_HIGH		0x4e

#घोषणा WB_SIO_EXT_ENTER_KEY		0x87
#घोषणा WB_SIO_EXT_EXIT_KEY		0xaa

/* global chip रेजिस्टरs */

#घोषणा WB_SIO_REG_LOGICAL		0x07

#घोषणा WB_SIO_REG_CHIP_MSB		0x20
#घोषणा WB_SIO_REG_CHIP_LSB		0x21

#घोषणा WB_SIO_CHIP_ID_W83627UHG	0xa230
#घोषणा WB_SIO_CHIP_ID_W83627UHG_MASK	GENMASK(15, 4)

#घोषणा WB_SIO_REG_DPD			0x22
#घोषणा WB_SIO_REG_DPD_UARTA		4
#घोषणा WB_SIO_REG_DPD_UARTB		5

#घोषणा WB_SIO_REG_IDPD		0x23
#घोषणा WB_SIO_REG_IDPD_UARTC		4
#घोषणा WB_SIO_REG_IDPD_UARTD		5
#घोषणा WB_SIO_REG_IDPD_UARTE		6
#घोषणा WB_SIO_REG_IDPD_UARTF		7

#घोषणा WB_SIO_REG_GLOBAL_OPT		0x24
#घोषणा WB_SIO_REG_GO_ENFDC		1

#घोषणा WB_SIO_REG_OVTGPIO3456		0x29
#घोषणा WB_SIO_REG_OG3456_G3PP		3
#घोषणा WB_SIO_REG_OG3456_G4PP		4
#घोषणा WB_SIO_REG_OG3456_G5PP		5
#घोषणा WB_SIO_REG_OG3456_G6PP		7

#घोषणा WB_SIO_REG_I2C_PS		0x2a
#घोषणा WB_SIO_REG_I2CPS_I2CFS		1

#घोषणा WB_SIO_REG_GPIO1_MF		0x2c
#घोषणा WB_SIO_REG_G1MF_G1PP		6
#घोषणा WB_SIO_REG_G1MF_G2PP		7
#घोषणा WB_SIO_REG_G1MF_FS_MASK	GENMASK(1, 0)
#घोषणा WB_SIO_REG_G1MF_FS_IR_OFF	0
#घोषणा WB_SIO_REG_G1MF_FS_IR		1
#घोषणा WB_SIO_REG_G1MF_FS_GPIO1	2
#घोषणा WB_SIO_REG_G1MF_FS_UARTB	3

/* not an actual device number, just a value meaning 'no device' */
#घोषणा WB_SIO_DEV_NONE		0xff

/* रेजिस्टरs with offsets >= 0x30 are specअगरic क्रम a particular device */

/* UART B logical device */
#घोषणा WB_SIO_DEV_UARTB		0x03
#घोषणा WB_SIO_UARTB_REG_ENABLE	0x30
#घोषणा WB_SIO_UARTB_ENABLE_ON		0

/* UART C logical device */
#घोषणा WB_SIO_DEV_UARTC		0x06
#घोषणा WB_SIO_UARTC_REG_ENABLE	0x30
#घोषणा WB_SIO_UARTC_ENABLE_ON		0

/* GPIO3, GPIO4 logical device */
#घोषणा WB_SIO_DEV_GPIO34		0x07
#घोषणा WB_SIO_GPIO34_REG_ENABLE	0x30
#घोषणा WB_SIO_GPIO34_ENABLE_3		0
#घोषणा WB_SIO_GPIO34_ENABLE_4		1
#घोषणा WB_SIO_GPIO34_REG_IO3		0xe0
#घोषणा WB_SIO_GPIO34_REG_DATA3	0xe1
#घोषणा WB_SIO_GPIO34_REG_INV3		0xe2
#घोषणा WB_SIO_GPIO34_REG_IO4		0xe4
#घोषणा WB_SIO_GPIO34_REG_DATA4	0xe5
#घोषणा WB_SIO_GPIO34_REG_INV4		0xe6

/* WDTO, PLED, GPIO5, GPIO6 logical device */
#घोषणा WB_SIO_DEV_WDGPIO56		0x08
#घोषणा WB_SIO_WDGPIO56_REG_ENABLE	0x30
#घोषणा WB_SIO_WDGPIO56_ENABLE_5	1
#घोषणा WB_SIO_WDGPIO56_ENABLE_6	2
#घोषणा WB_SIO_WDGPIO56_REG_IO5	0xe0
#घोषणा WB_SIO_WDGPIO56_REG_DATA5	0xe1
#घोषणा WB_SIO_WDGPIO56_REG_INV5	0xe2
#घोषणा WB_SIO_WDGPIO56_REG_IO6	0xe4
#घोषणा WB_SIO_WDGPIO56_REG_DATA6	0xe5
#घोषणा WB_SIO_WDGPIO56_REG_INV6	0xe6

/* GPIO1, GPIO2, SUSLED logical device */
#घोषणा WB_SIO_DEV_GPIO12		0x09
#घोषणा WB_SIO_GPIO12_REG_ENABLE	0x30
#घोषणा WB_SIO_GPIO12_ENABLE_1		0
#घोषणा WB_SIO_GPIO12_ENABLE_2		1
#घोषणा WB_SIO_GPIO12_REG_IO1		0xe0
#घोषणा WB_SIO_GPIO12_REG_DATA1	0xe1
#घोषणा WB_SIO_GPIO12_REG_INV1		0xe2
#घोषणा WB_SIO_GPIO12_REG_IO2		0xe4
#घोषणा WB_SIO_GPIO12_REG_DATA2	0xe5
#घोषणा WB_SIO_GPIO12_REG_INV2		0xe6

/* UART D logical device */
#घोषणा WB_SIO_DEV_UARTD		0x0d
#घोषणा WB_SIO_UARTD_REG_ENABLE	0x30
#घोषणा WB_SIO_UARTD_ENABLE_ON		0

/* UART E logical device */
#घोषणा WB_SIO_DEV_UARTE		0x0e
#घोषणा WB_SIO_UARTE_REG_ENABLE	0x30
#घोषणा WB_SIO_UARTE_ENABLE_ON		0

/*
 * क्रम a description what a particular field of this काष्ठा means please see
 * a description of the relevant module parameter at the bottom of this file
 */
काष्ठा winbond_gpio_params अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ gpios;
	अचिन्हित दीर्घ ppgpios;
	अचिन्हित दीर्घ odgpios;
	bool pledgpio;
	bool beepgpio;
	bool i2cgpio;
पूर्ण;

अटल काष्ठा winbond_gpio_params params;

अटल पूर्णांक winbond_sio_enter(अचिन्हित दीर्घ base)
अणु
	अगर (!request_muxed_region(base, 2, WB_GPIO_DRIVER_NAME))
		वापस -EBUSY;

	/*
	 * datasheet says two successive ग_लिखोs of the "key" value are needed
	 * in order क्रम chip to enter the "Extended Function Mode"
	 */
	outb(WB_SIO_EXT_ENTER_KEY, base);
	outb(WB_SIO_EXT_ENTER_KEY, base);

	वापस 0;
पूर्ण

अटल व्योम winbond_sio_select_logical(अचिन्हित दीर्घ base, u8 dev)
अणु
	outb(WB_SIO_REG_LOGICAL, base);
	outb(dev, base + 1);
पूर्ण

अटल व्योम winbond_sio_leave(अचिन्हित दीर्घ base)
अणु
	outb(WB_SIO_EXT_EXIT_KEY, base);

	release_region(base, 2);
पूर्ण

अटल व्योम winbond_sio_reg_ग_लिखो(अचिन्हित दीर्घ base, u8 reg, u8 data)
अणु
	outb(reg, base);
	outb(data, base + 1);
पूर्ण

अटल u8 winbond_sio_reg_पढ़ो(अचिन्हित दीर्घ base, u8 reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल व्योम winbond_sio_reg_bset(अचिन्हित दीर्घ base, u8 reg, u8 bit)
अणु
	u8 val;

	val = winbond_sio_reg_पढ़ो(base, reg);
	val |= BIT(bit);
	winbond_sio_reg_ग_लिखो(base, reg, val);
पूर्ण

अटल व्योम winbond_sio_reg_bclear(अचिन्हित दीर्घ base, u8 reg, u8 bit)
अणु
	u8 val;

	val = winbond_sio_reg_पढ़ो(base, reg);
	val &= ~BIT(bit);
	winbond_sio_reg_ग_लिखो(base, reg, val);
पूर्ण

अटल bool winbond_sio_reg_btest(अचिन्हित दीर्घ base, u8 reg, u8 bit)
अणु
	वापस winbond_sio_reg_पढ़ो(base, reg) & BIT(bit);
पूर्ण

/**
 * काष्ठा winbond_gpio_port_conflict - possibly conflicting device inक्रमmation
 * @name:	device name (शून्य means no conflicting device defined)
 * @dev:	Super I/O logical device number where the testreg रेजिस्टर
 *		is located (or WB_SIO_DEV_NONE - करोn't select any
 *		logical device)
 * @testreg:	रेजिस्टर number where the testbit bit is located
 * @testbit:	index of a bit to check whether an actual conflict exists
 * @warnonly:	अगर set then a conflict isn't fatal (just warn about it),
 *		otherwise disable the particular GPIO port अगर a conflict
 *		is detected
 */
काष्ठा winbond_gpio_port_conflict अणु
	स्थिर अक्षर *name;
	u8 dev;
	u8 testreg;
	u8 testbit;
	bool warnonly;
पूर्ण;

/**
 * काष्ठा winbond_gpio_info - inक्रमmation about a particular GPIO port (device)
 * @dev:		Super I/O logical device number of the रेजिस्टरs
 *			specअगरied below
 * @enablereg:		port enable bit रेजिस्टर number
 * @enablebit:		index of a port enable bit
 * @outputreg:		output driver mode bit रेजिस्टर number
 * @outputppbit:	index of a push-pull output driver mode bit
 * @ioreg:		data direction रेजिस्टर number
 * @invreg:		pin data inversion रेजिस्टर number
 * @datareg:		pin data रेजिस्टर number
 * @conflict:		description of a device that possibly conflicts with
 *			this port
 */
काष्ठा winbond_gpio_info अणु
	u8 dev;
	u8 enablereg;
	u8 enablebit;
	u8 outputreg;
	u8 outputppbit;
	u8 ioreg;
	u8 invreg;
	u8 datareg;
	काष्ठा winbond_gpio_port_conflict conflict;
पूर्ण;

अटल स्थिर काष्ठा winbond_gpio_info winbond_gpio_infos[6] = अणु
	अणु /* 0 */
		.dev = WB_SIO_DEV_GPIO12,
		.enablereg = WB_SIO_GPIO12_REG_ENABLE,
		.enablebit = WB_SIO_GPIO12_ENABLE_1,
		.outputreg = WB_SIO_REG_GPIO1_MF,
		.outputppbit = WB_SIO_REG_G1MF_G1PP,
		.ioreg = WB_SIO_GPIO12_REG_IO1,
		.invreg = WB_SIO_GPIO12_REG_INV1,
		.datareg = WB_SIO_GPIO12_REG_DATA1,
		.conflict = अणु
			.name = "UARTB",
			.dev = WB_SIO_DEV_UARTB,
			.testreg = WB_SIO_UARTB_REG_ENABLE,
			.testbit = WB_SIO_UARTB_ENABLE_ON,
			.warnonly = true
		पूर्ण
	पूर्ण,
	अणु /* 1 */
		.dev = WB_SIO_DEV_GPIO12,
		.enablereg = WB_SIO_GPIO12_REG_ENABLE,
		.enablebit = WB_SIO_GPIO12_ENABLE_2,
		.outputreg = WB_SIO_REG_GPIO1_MF,
		.outputppbit = WB_SIO_REG_G1MF_G2PP,
		.ioreg = WB_SIO_GPIO12_REG_IO2,
		.invreg = WB_SIO_GPIO12_REG_INV2,
		.datareg = WB_SIO_GPIO12_REG_DATA2
		/* special conflict handling so करोesn't use conflict data */
	पूर्ण,
	अणु /* 2 */
		.dev = WB_SIO_DEV_GPIO34,
		.enablereg = WB_SIO_GPIO34_REG_ENABLE,
		.enablebit = WB_SIO_GPIO34_ENABLE_3,
		.outputreg = WB_SIO_REG_OVTGPIO3456,
		.outputppbit = WB_SIO_REG_OG3456_G3PP,
		.ioreg = WB_SIO_GPIO34_REG_IO3,
		.invreg = WB_SIO_GPIO34_REG_INV3,
		.datareg = WB_SIO_GPIO34_REG_DATA3,
		.conflict = अणु
			.name = "UARTC",
			.dev = WB_SIO_DEV_UARTC,
			.testreg = WB_SIO_UARTC_REG_ENABLE,
			.testbit = WB_SIO_UARTC_ENABLE_ON,
			.warnonly = true
		पूर्ण
	पूर्ण,
	अणु /* 3 */
		.dev = WB_SIO_DEV_GPIO34,
		.enablereg = WB_SIO_GPIO34_REG_ENABLE,
		.enablebit = WB_SIO_GPIO34_ENABLE_4,
		.outputreg = WB_SIO_REG_OVTGPIO3456,
		.outputppbit = WB_SIO_REG_OG3456_G4PP,
		.ioreg = WB_SIO_GPIO34_REG_IO4,
		.invreg = WB_SIO_GPIO34_REG_INV4,
		.datareg = WB_SIO_GPIO34_REG_DATA4,
		.conflict = अणु
			.name = "UARTD",
			.dev = WB_SIO_DEV_UARTD,
			.testreg = WB_SIO_UARTD_REG_ENABLE,
			.testbit = WB_SIO_UARTD_ENABLE_ON,
			.warnonly = true
		पूर्ण
	पूर्ण,
	अणु /* 4 */
		.dev = WB_SIO_DEV_WDGPIO56,
		.enablereg = WB_SIO_WDGPIO56_REG_ENABLE,
		.enablebit = WB_SIO_WDGPIO56_ENABLE_5,
		.outputreg = WB_SIO_REG_OVTGPIO3456,
		.outputppbit = WB_SIO_REG_OG3456_G5PP,
		.ioreg = WB_SIO_WDGPIO56_REG_IO5,
		.invreg = WB_SIO_WDGPIO56_REG_INV5,
		.datareg = WB_SIO_WDGPIO56_REG_DATA5,
		.conflict = अणु
			.name = "UARTE",
			.dev = WB_SIO_DEV_UARTE,
			.testreg = WB_SIO_UARTE_REG_ENABLE,
			.testbit = WB_SIO_UARTE_ENABLE_ON,
			.warnonly = true
		पूर्ण
	पूर्ण,
	अणु /* 5 */
		.dev = WB_SIO_DEV_WDGPIO56,
		.enablereg = WB_SIO_WDGPIO56_REG_ENABLE,
		.enablebit = WB_SIO_WDGPIO56_ENABLE_6,
		.outputreg = WB_SIO_REG_OVTGPIO3456,
		.outputppbit = WB_SIO_REG_OG3456_G6PP,
		.ioreg = WB_SIO_WDGPIO56_REG_IO6,
		.invreg = WB_SIO_WDGPIO56_REG_INV6,
		.datareg = WB_SIO_WDGPIO56_REG_DATA6,
		.conflict = अणु
			.name = "FDC",
			.dev = WB_SIO_DEV_NONE,
			.testreg = WB_SIO_REG_GLOBAL_OPT,
			.testbit = WB_SIO_REG_GO_ENFDC,
			.warnonly = false
		पूर्ण
	पूर्ण
पूर्ण;

/* वापसs whether changing a pin is allowed */
अटल bool winbond_gpio_get_info(अचिन्हित पूर्णांक *gpio_num,
				  स्थिर काष्ठा winbond_gpio_info **info)
अणु
	bool allow_changing = true;
	अचिन्हित दीर्घ i;

	क्रम_each_set_bit(i, &params.gpios, BITS_PER_LONG) अणु
		अगर (*gpio_num < 8)
			अवरोध;

		*gpio_num -= 8;
	पूर्ण

	*info = &winbond_gpio_infos[i];

	/*
	 * GPIO2 (the second port) shares some pins with a basic PC
	 * functionality, which is very likely controlled by the firmware.
	 * Don't allow changing these pins by शेष.
	 */
	अगर (i == 1) अणु
		अगर (*gpio_num == 0 && !params.pledgpio)
			allow_changing = false;
		अन्यथा अगर (*gpio_num == 1 && !params.beepgpio)
			allow_changing = false;
		अन्यथा अगर ((*gpio_num == 5 || *gpio_num == 6) && !params.i2cgpio)
			allow_changing = false;
	पूर्ण

	वापस allow_changing;
पूर्ण

अटल पूर्णांक winbond_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ *base = gpiochip_get_data(gc);
	स्थिर काष्ठा winbond_gpio_info *info;
	bool val;

	winbond_gpio_get_info(&offset, &info);

	val = winbond_sio_enter(*base);
	अगर (val)
		वापस val;

	winbond_sio_select_logical(*base, info->dev);

	val = winbond_sio_reg_btest(*base, info->datareg, offset);
	अगर (winbond_sio_reg_btest(*base, info->invreg, offset))
		val = !val;

	winbond_sio_leave(*base);

	वापस val;
पूर्ण

अटल पूर्णांक winbond_gpio_direction_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ *base = gpiochip_get_data(gc);
	स्थिर काष्ठा winbond_gpio_info *info;
	पूर्णांक ret;

	अगर (!winbond_gpio_get_info(&offset, &info))
		वापस -EACCES;

	ret = winbond_sio_enter(*base);
	अगर (ret)
		वापस ret;

	winbond_sio_select_logical(*base, info->dev);

	winbond_sio_reg_bset(*base, info->ioreg, offset);

	winbond_sio_leave(*base);

	वापस 0;
पूर्ण

अटल पूर्णांक winbond_gpio_direction_out(काष्ठा gpio_chip *gc,
				      अचिन्हित पूर्णांक offset,
				      पूर्णांक val)
अणु
	अचिन्हित दीर्घ *base = gpiochip_get_data(gc);
	स्थिर काष्ठा winbond_gpio_info *info;
	पूर्णांक ret;

	अगर (!winbond_gpio_get_info(&offset, &info))
		वापस -EACCES;

	ret = winbond_sio_enter(*base);
	अगर (ret)
		वापस ret;

	winbond_sio_select_logical(*base, info->dev);

	winbond_sio_reg_bclear(*base, info->ioreg, offset);

	अगर (winbond_sio_reg_btest(*base, info->invreg, offset))
		val = !val;

	अगर (val)
		winbond_sio_reg_bset(*base, info->datareg, offset);
	अन्यथा
		winbond_sio_reg_bclear(*base, info->datareg, offset);

	winbond_sio_leave(*base);

	वापस 0;
पूर्ण

अटल व्योम winbond_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			     पूर्णांक val)
अणु
	अचिन्हित दीर्घ *base = gpiochip_get_data(gc);
	स्थिर काष्ठा winbond_gpio_info *info;

	अगर (!winbond_gpio_get_info(&offset, &info))
		वापस;

	अगर (winbond_sio_enter(*base) != 0)
		वापस;

	winbond_sio_select_logical(*base, info->dev);

	अगर (winbond_sio_reg_btest(*base, info->invreg, offset))
		val = !val;

	अगर (val)
		winbond_sio_reg_bset(*base, info->datareg, offset);
	अन्यथा
		winbond_sio_reg_bclear(*base, info->datareg, offset);

	winbond_sio_leave(*base);
पूर्ण

अटल काष्ठा gpio_chip winbond_gpio_chip = अणु
	.base			= -1,
	.label			= WB_GPIO_DRIVER_NAME,
	.owner			= THIS_MODULE,
	.can_sleep		= true,
	.get			= winbond_gpio_get,
	.direction_input	= winbond_gpio_direction_in,
	.set			= winbond_gpio_set,
	.direction_output	= winbond_gpio_direction_out,
पूर्ण;

अटल व्योम winbond_gpio_configure_port0_pins(अचिन्हित दीर्घ base)
अणु
	अचिन्हित पूर्णांक val;

	val = winbond_sio_reg_पढ़ो(base, WB_SIO_REG_GPIO1_MF);
	अगर ((val & WB_SIO_REG_G1MF_FS_MASK) == WB_SIO_REG_G1MF_FS_GPIO1)
		वापस;

	pr_warn("GPIO1 pins were connected to something else (%.2x), fixing\n",
		val);

	val &= ~WB_SIO_REG_G1MF_FS_MASK;
	val |= WB_SIO_REG_G1MF_FS_GPIO1;

	winbond_sio_reg_ग_लिखो(base, WB_SIO_REG_GPIO1_MF, val);
पूर्ण

अटल व्योम winbond_gpio_configure_port1_check_i2c(अचिन्हित दीर्घ base)
अणु
	params.i2cgpio = !winbond_sio_reg_btest(base, WB_SIO_REG_I2C_PS,
						WB_SIO_REG_I2CPS_I2CFS);
	अगर (!params.i2cgpio)
		pr_warn("disabling GPIO2.5 and GPIO2.6 as I2C is enabled\n");
पूर्ण

अटल bool winbond_gpio_configure_port(अचिन्हित दीर्घ base, अचिन्हित पूर्णांक idx)
अणु
	स्थिर काष्ठा winbond_gpio_info *info = &winbond_gpio_infos[idx];
	स्थिर काष्ठा winbond_gpio_port_conflict *conflict = &info->conflict;

	/* is there a possible conflicting device defined? */
	अगर (conflict->name != शून्य) अणु
		अगर (conflict->dev != WB_SIO_DEV_NONE)
			winbond_sio_select_logical(base, conflict->dev);

		अगर (winbond_sio_reg_btest(base, conflict->testreg,
					  conflict->testbit)) अणु
			अगर (conflict->warnonly)
				pr_warn("enabled GPIO%u share pins with active %s\n",
					idx + 1, conflict->name);
			अन्यथा अणु
				pr_warn("disabling GPIO%u as %s is enabled\n",
					idx + 1, conflict->name);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	/* GPIO1 and GPIO2 need some (additional) special handling */
	अगर (idx == 0)
		winbond_gpio_configure_port0_pins(base);
	अन्यथा अगर (idx == 1)
		winbond_gpio_configure_port1_check_i2c(base);

	winbond_sio_select_logical(base, info->dev);

	winbond_sio_reg_bset(base, info->enablereg, info->enablebit);

	अगर (params.ppgpios & BIT(idx))
		winbond_sio_reg_bset(base, info->outputreg,
				     info->outputppbit);
	अन्यथा अगर (params.odgpios & BIT(idx))
		winbond_sio_reg_bclear(base, info->outputreg,
				       info->outputppbit);
	अन्यथा
		pr_notice("GPIO%u pins are %s\n", idx + 1,
			  winbond_sio_reg_btest(base, info->outputreg,
						info->outputppbit) ?
			  "push-pull" :
			  "open drain");

	वापस true;
पूर्ण

अटल पूर्णांक winbond_gpio_configure(अचिन्हित दीर्घ base)
अणु
	अचिन्हित दीर्घ i;

	क्रम_each_set_bit(i, &params.gpios, BITS_PER_LONG)
		अगर (!winbond_gpio_configure_port(base, i))
			__clear_bit(i, &params.gpios);

	अगर (!params.gpios) अणु
		pr_err("please use 'gpios' module parameter to select some active GPIO ports to enable\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक winbond_gpio_check_chip(अचिन्हित दीर्घ base)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक chip;

	ret = winbond_sio_enter(base);
	अगर (ret)
		वापस ret;

	chip = winbond_sio_reg_पढ़ो(base, WB_SIO_REG_CHIP_MSB) << 8;
	chip |= winbond_sio_reg_पढ़ो(base, WB_SIO_REG_CHIP_LSB);

	pr_notice("chip ID at %lx is %.4x\n", base, chip);

	अगर ((chip & WB_SIO_CHIP_ID_W83627UHG_MASK) !=
	    WB_SIO_CHIP_ID_W83627UHG) अणु
		pr_err("not an our chip\n");
		ret = -ENODEV;
	पूर्ण

	winbond_sio_leave(base);

	वापस ret;
पूर्ण

अटल पूर्णांक winbond_gpio_imatch(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	अचिन्हित दीर्घ gpios_rem;
	पूर्णांक ret;

	gpios_rem = params.gpios & ~GENMASK(ARRAY_SIZE(winbond_gpio_infos) - 1,
					    0);
	अगर (gpios_rem) अणु
		pr_warn("unknown ports (%lx) enabled in GPIO ports bitmask\n",
			gpios_rem);
		params.gpios &= ~gpios_rem;
	पूर्ण

	अगर (params.ppgpios & params.odgpios) अणु
		pr_err("some GPIO ports are set both to push-pull and open drain mode at the same time\n");
		वापस 0;
	पूर्ण

	अगर (params.base != 0)
		वापस winbond_gpio_check_chip(params.base) == 0;

	/*
	 * अगर the 'base' module parameter is unset probe two chip शेष
	 * I/O port bases
	 */
	params.base = WB_SIO_BASE;
	ret = winbond_gpio_check_chip(params.base);
	अगर (ret == 0)
		वापस 1;
	अगर (ret != -ENODEV && ret != -EBUSY)
		वापस 0;

	params.base = WB_SIO_BASE_HIGH;
	वापस winbond_gpio_check_chip(params.base) == 0;
पूर्ण

अटल पूर्णांक winbond_gpio_iprobe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक ret;

	अगर (params.base == 0)
		वापस -EINVAL;

	ret = winbond_sio_enter(params.base);
	अगर (ret)
		वापस ret;

	ret = winbond_gpio_configure(params.base);

	winbond_sio_leave(params.base);

	अगर (ret)
		वापस ret;

	/*
	 * Add 8 gpios क्रम every GPIO port that was enabled in gpios
	 * module parameter (that wasn't disabled earlier in
	 * winbond_gpio_configure() & co. due to, क्रम example, a pin conflict).
	 */
	winbond_gpio_chip.ngpio = hweight_दीर्घ(params.gpios) * 8;

	/*
	 * GPIO6 port has only 5 pins, so अगर it is enabled we have to adjust
	 * the total count appropriately
	 */
	अगर (params.gpios & BIT(5))
		winbond_gpio_chip.ngpio -= (8 - 5);

	winbond_gpio_chip.parent = dev;

	वापस devm_gpiochip_add_data(dev, &winbond_gpio_chip, &params.base);
पूर्ण

अटल काष्ठा isa_driver winbond_gpio_idriver = अणु
	.driver = अणु
		.name	= WB_GPIO_DRIVER_NAME,
	पूर्ण,
	.match	= winbond_gpio_imatch,
	.probe	= winbond_gpio_iprobe,
पूर्ण;

module_isa_driver(winbond_gpio_idriver, 1);

module_param_named(base, params.base, uदीर्घ, 0444);
MODULE_PARM_DESC(base,
		 "I/O port base (when unset - probe chip default ones)");

/* This parameter sets which GPIO devices (ports) we enable */
module_param_named(gpios, params.gpios, uदीर्घ, 0444);
MODULE_PARM_DESC(gpios,
		 "bitmask of GPIO ports to enable (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

/*
 * These two parameters below set how we configure GPIO ports output drivers.
 * It can't be a one biपंचांगask since we need three values per port: push-pull,
 * खोलो-drain and keep as-is (this is the शेष).
 */
module_param_named(ppgpios, params.ppgpios, uदीर्घ, 0444);
MODULE_PARM_DESC(ppgpios,
		 "bitmask of GPIO ports to set to push-pull mode (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

module_param_named(odgpios, params.odgpios, uदीर्घ, 0444);
MODULE_PARM_DESC(odgpios,
		 "bitmask of GPIO ports to set to open drain mode (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

/*
 * GPIO2.0 and GPIO2.1 control a basic PC functionality that we
 * करोn't allow tinkering with by शेष (it is very likely that the
 * firmware owns these pins).
 * These two parameters below allow overriding these prohibitions.
 */
module_param_named(pledgpio, params.pledgpio, bool, 0644);
MODULE_PARM_DESC(pledgpio,
		 "enable changing value of GPIO2.0 bit (Power LED), default no.");

module_param_named(beepgpio, params.beepgpio, bool, 0644);
MODULE_PARM_DESC(beepgpio,
		 "enable changing value of GPIO2.1 bit (BEEP), default no.");

MODULE_AUTHOR("Maciej S. Szmigiero <mail@maciej.szmigiero.name>");
MODULE_DESCRIPTION("GPIO interface for Winbond Super I/O chips");
MODULE_LICENSE("GPL");
