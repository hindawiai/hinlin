<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO driver क्रम Fपूर्णांकek Super-I/O F71869, F71869A, F71882, F71889 and F81866
 *
 * Copyright (C) 2010-2013 LaCie
 *
 * Author: Simon Guinot <simon.guinot@sequanux.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>

#घोषणा DRVNAME "gpio-f7188x"

/*
 * Super-I/O रेजिस्टरs
 */
#घोषणा SIO_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_DEVREV		0x22	/* Device revision */
#घोषणा SIO_MANID		0x23	/* Fपूर्णांकek ID (2 bytes) */

#घोषणा SIO_LD_GPIO		0x06	/* GPIO logical device */
#घोषणा SIO_UNLOCK_KEY		0x87	/* Key to enable Super-I/O */
#घोषणा SIO_LOCK_KEY		0xAA	/* Key to disable Super-I/O */

#घोषणा SIO_FINTEK_ID		0x1934	/* Manufacturer ID */
#घोषणा SIO_F71869_ID		0x0814	/* F71869 chipset ID */
#घोषणा SIO_F71869A_ID		0x1007	/* F71869A chipset ID */
#घोषणा SIO_F71882_ID		0x0541	/* F71882 chipset ID */
#घोषणा SIO_F71889_ID		0x0909	/* F71889 chipset ID */
#घोषणा SIO_F71889A_ID		0x1005	/* F71889A chipset ID */
#घोषणा SIO_F81866_ID		0x1010	/* F81866 chipset ID */
#घोषणा SIO_F81804_ID		0x1502  /* F81804 chipset ID, same क्रम f81966 */
#घोषणा SIO_F81865_ID		0x0704	/* F81865 chipset ID */


क्रमागत chips अणु
	f71869,
	f71869a,
	f71882fg,
	f71889a,
	f71889f,
	f81866,
	f81804,
	f81865,
पूर्ण;

अटल स्थिर अक्षर * स्थिर f7188x_names[] = अणु
	"f71869",
	"f71869a",
	"f71882fg",
	"f71889a",
	"f71889f",
	"f81866",
	"f81804",
	"f81865",
पूर्ण;

काष्ठा f7188x_sio अणु
	पूर्णांक addr;
	क्रमागत chips type;
पूर्ण;

काष्ठा f7188x_gpio_bank अणु
	काष्ठा gpio_chip chip;
	अचिन्हित पूर्णांक regbase;
	काष्ठा f7188x_gpio_data *data;
पूर्ण;

काष्ठा f7188x_gpio_data अणु
	काष्ठा f7188x_sio *sio;
	पूर्णांक nr_bank;
	काष्ठा f7188x_gpio_bank *bank;
पूर्ण;

/*
 * Super-I/O functions.
 */

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक base, पूर्णांक reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल पूर्णांक superio_inw(पूर्णांक base, पूर्णांक reg)
अणु
	पूर्णांक val;

	outb(reg++, base);
	val = inb(base + 1) << 8;
	outb(reg, base);
	val |= inb(base + 1);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_outb(पूर्णांक base, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, base);
	outb(val, base + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base)
अणु
	/* Don't step on other drivers' I/O space by accident. */
	अगर (!request_muxed_region(base, 2, DRVNAME)) अणु
		pr_err(DRVNAME "I/O address 0x%04x already in use\n", base);
		वापस -EBUSY;
	पूर्ण

	/* According to the datasheet the key must be send twice. */
	outb(SIO_UNLOCK_KEY, base);
	outb(SIO_UNLOCK_KEY, base);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक base, पूर्णांक ld)
अणु
	outb(SIO_LDSEL, base);
	outb(ld, base + 1);
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक base)
अणु
	outb(SIO_LOCK_KEY, base);
	release_region(base, 2);
पूर्ण

/*
 * GPIO chip.
 */

अटल पूर्णांक f7188x_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset);
अटल पूर्णांक f7188x_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset);
अटल पूर्णांक f7188x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset);
अटल पूर्णांक f7188x_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value);
अटल व्योम f7188x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value);
अटल पूर्णांक f7188x_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  अचिन्हित दीर्घ config);

#घोषणा F7188X_GPIO_BANK(_base, _ngpio, _regbase)			\
	अणु								\
		.chip = अणु						\
			.label            = DRVNAME,			\
			.owner            = THIS_MODULE,		\
			.get_direction    = f7188x_gpio_get_direction,	\
			.direction_input  = f7188x_gpio_direction_in,	\
			.get              = f7188x_gpio_get,		\
			.direction_output = f7188x_gpio_direction_out,	\
			.set              = f7188x_gpio_set,		\
			.set_config	  = f7188x_gpio_set_config,	\
			.base             = _base,			\
			.ngpio            = _ngpio,			\
			.can_sleep        = true,			\
		पूर्ण,							\
		.regbase = _regbase,					\
	पूर्ण

#घोषणा gpio_dir(base) (base + 0)
#घोषणा gpio_data_out(base) (base + 1)
#घोषणा gpio_data_in(base) (base + 2)
/* Output mode रेजिस्टर (0:खोलो drain 1:push-pull). */
#घोषणा gpio_out_mode(base) (base + 3)

अटल काष्ठा f7188x_gpio_bank f71869_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 6, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 5, 0xA0),
	F7188X_GPIO_BANK(60, 6, 0x90),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f71869a_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 6, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 5, 0xA0),
	F7188X_GPIO_BANK(60, 8, 0x90),
	F7188X_GPIO_BANK(70, 8, 0x80),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f71882_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 8, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 4, 0xC0),
	F7188X_GPIO_BANK(40, 4, 0xB0),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f71889a_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 7, 0xF0),
	F7188X_GPIO_BANK(10, 7, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 5, 0xA0),
	F7188X_GPIO_BANK(60, 8, 0x90),
	F7188X_GPIO_BANK(70, 8, 0x80),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f71889_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 7, 0xF0),
	F7188X_GPIO_BANK(10, 7, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 5, 0xA0),
	F7188X_GPIO_BANK(60, 8, 0x90),
	F7188X_GPIO_BANK(70, 8, 0x80),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f81866_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 8, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 8, 0xA0),
	F7188X_GPIO_BANK(60, 8, 0x90),
	F7188X_GPIO_BANK(70, 8, 0x80),
	F7188X_GPIO_BANK(80, 8, 0x88),
पूर्ण;


अटल काष्ठा f7188x_gpio_bank f81804_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 8, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(50, 8, 0xA0),
	F7188X_GPIO_BANK(60, 8, 0x90),
	F7188X_GPIO_BANK(70, 8, 0x80),
	F7188X_GPIO_BANK(90, 8, 0x98),
पूर्ण;

अटल काष्ठा f7188x_gpio_bank f81865_gpio_bank[] = अणु
	F7188X_GPIO_BANK(0, 8, 0xF0),
	F7188X_GPIO_BANK(10, 8, 0xE0),
	F7188X_GPIO_BANK(20, 8, 0xD0),
	F7188X_GPIO_BANK(30, 8, 0xC0),
	F7188X_GPIO_BANK(40, 8, 0xB0),
	F7188X_GPIO_BANK(50, 8, 0xA0),
	F7188X_GPIO_BANK(60, 5, 0x90),
पूर्ण;

अटल पूर्णांक f7188x_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	पूर्णांक err;
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 dir;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस err;
	superio_select(sio->addr, SIO_LD_GPIO);

	dir = superio_inb(sio->addr, gpio_dir(bank->regbase));

	superio_निकास(sio->addr);

	अगर (dir & 1 << offset)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक f7188x_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	पूर्णांक err;
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 dir;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस err;
	superio_select(sio->addr, SIO_LD_GPIO);

	dir = superio_inb(sio->addr, gpio_dir(bank->regbase));
	dir &= ~BIT(offset);
	superio_outb(sio->addr, gpio_dir(bank->regbase), dir);

	superio_निकास(sio->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक f7188x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	पूर्णांक err;
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 dir, data;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस err;
	superio_select(sio->addr, SIO_LD_GPIO);

	dir = superio_inb(sio->addr, gpio_dir(bank->regbase));
	dir = !!(dir & BIT(offset));
	अगर (dir)
		data = superio_inb(sio->addr, gpio_data_out(bank->regbase));
	अन्यथा
		data = superio_inb(sio->addr, gpio_data_in(bank->regbase));

	superio_निकास(sio->addr);

	वापस !!(data & BIT(offset));
पूर्ण

अटल पूर्णांक f7188x_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	पूर्णांक err;
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 dir, data_out;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस err;
	superio_select(sio->addr, SIO_LD_GPIO);

	data_out = superio_inb(sio->addr, gpio_data_out(bank->regbase));
	अगर (value)
		data_out |= BIT(offset);
	अन्यथा
		data_out &= ~BIT(offset);
	superio_outb(sio->addr, gpio_data_out(bank->regbase), data_out);

	dir = superio_inb(sio->addr, gpio_dir(bank->regbase));
	dir |= BIT(offset);
	superio_outb(sio->addr, gpio_dir(bank->regbase), dir);

	superio_निकास(sio->addr);

	वापस 0;
पूर्ण

अटल व्योम f7188x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	पूर्णांक err;
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 data_out;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस;
	superio_select(sio->addr, SIO_LD_GPIO);

	data_out = superio_inb(sio->addr, gpio_data_out(bank->regbase));
	अगर (value)
		data_out |= BIT(offset);
	अन्यथा
		data_out &= ~BIT(offset);
	superio_outb(sio->addr, gpio_data_out(bank->regbase), data_out);

	superio_निकास(sio->addr);
पूर्ण

अटल पूर्णांक f7188x_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  अचिन्हित दीर्घ config)
अणु
	पूर्णांक err;
	क्रमागत pin_config_param param = pinconf_to_config_param(config);
	काष्ठा f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा f7188x_sio *sio = bank->data->sio;
	u8 data;

	अगर (param != PIN_CONFIG_DRIVE_OPEN_DRAIN &&
	    param != PIN_CONFIG_DRIVE_PUSH_PULL)
		वापस -ENOTSUPP;

	err = superio_enter(sio->addr);
	अगर (err)
		वापस err;
	superio_select(sio->addr, SIO_LD_GPIO);

	data = superio_inb(sio->addr, gpio_out_mode(bank->regbase));
	अगर (param == PIN_CONFIG_DRIVE_OPEN_DRAIN)
		data &= ~BIT(offset);
	अन्यथा
		data |= BIT(offset);
	superio_outb(sio->addr, gpio_out_mode(bank->regbase), data);

	superio_निकास(sio->addr);
	वापस 0;
पूर्ण

/*
 * Platक्रमm device and driver.
 */

अटल पूर्णांक f7188x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	पूर्णांक i;
	काष्ठा f7188x_sio *sio = dev_get_platdata(&pdev->dev);
	काष्ठा f7188x_gpio_data *data;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	चयन (sio->type) अणु
	हाल f71869:
		data->nr_bank = ARRAY_SIZE(f71869_gpio_bank);
		data->bank = f71869_gpio_bank;
		अवरोध;
	हाल f71869a:
		data->nr_bank = ARRAY_SIZE(f71869a_gpio_bank);
		data->bank = f71869a_gpio_bank;
		अवरोध;
	हाल f71882fg:
		data->nr_bank = ARRAY_SIZE(f71882_gpio_bank);
		data->bank = f71882_gpio_bank;
		अवरोध;
	हाल f71889a:
		data->nr_bank = ARRAY_SIZE(f71889a_gpio_bank);
		data->bank = f71889a_gpio_bank;
		अवरोध;
	हाल f71889f:
		data->nr_bank = ARRAY_SIZE(f71889_gpio_bank);
		data->bank = f71889_gpio_bank;
		अवरोध;
	हाल f81866:
		data->nr_bank = ARRAY_SIZE(f81866_gpio_bank);
		data->bank = f81866_gpio_bank;
		अवरोध;
	हाल  f81804:
		data->nr_bank = ARRAY_SIZE(f81804_gpio_bank);
		data->bank = f81804_gpio_bank;
		अवरोध;
	हाल f81865:
		data->nr_bank = ARRAY_SIZE(f81865_gpio_bank);
		data->bank = f81865_gpio_bank;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	data->sio = sio;

	platक्रमm_set_drvdata(pdev, data);

	/* For each GPIO bank, रेजिस्टर a GPIO chip. */
	क्रम (i = 0; i < data->nr_bank; i++) अणु
		काष्ठा f7188x_gpio_bank *bank = &data->bank[i];

		bank->chip.parent = &pdev->dev;
		bank->data = data;

		err = devm_gpiochip_add_data(&pdev->dev, &bank->chip, bank);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to register gpiochip %d: %d\n",
				i, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init f7188x_find(पूर्णांक addr, काष्ठा f7188x_sio *sio)
अणु
	पूर्णांक err;
	u16 devid;

	err = superio_enter(addr);
	अगर (err)
		वापस err;

	err = -ENODEV;
	devid = superio_inw(addr, SIO_MANID);
	अगर (devid != SIO_FINTEK_ID) अणु
		pr_debug(DRVNAME ": Not a Fintek device at 0x%08x\n", addr);
		जाओ err;
	पूर्ण

	devid = superio_inw(addr, SIO_DEVID);
	चयन (devid) अणु
	हाल SIO_F71869_ID:
		sio->type = f71869;
		अवरोध;
	हाल SIO_F71869A_ID:
		sio->type = f71869a;
		अवरोध;
	हाल SIO_F71882_ID:
		sio->type = f71882fg;
		अवरोध;
	हाल SIO_F71889A_ID:
		sio->type = f71889a;
		अवरोध;
	हाल SIO_F71889_ID:
		sio->type = f71889f;
		अवरोध;
	हाल SIO_F81866_ID:
		sio->type = f81866;
		अवरोध;
	हाल SIO_F81804_ID:
		sio->type = f81804;
		अवरोध;
	हाल SIO_F81865_ID:
		sio->type = f81865;
		अवरोध;
	शेष:
		pr_info(DRVNAME ": Unsupported Fintek device 0x%04x\n", devid);
		जाओ err;
	पूर्ण
	sio->addr = addr;
	err = 0;

	pr_info(DRVNAME ": Found %s at %#x, revision %d\n",
		f7188x_names[sio->type],
		(अचिन्हित पूर्णांक) addr,
		(पूर्णांक) superio_inb(addr, SIO_DEVREV));

err:
	superio_निकास(addr);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_device *f7188x_gpio_pdev;

अटल पूर्णांक __init
f7188x_gpio_device_add(स्थिर काष्ठा f7188x_sio *sio)
अणु
	पूर्णांक err;

	f7188x_gpio_pdev = platक्रमm_device_alloc(DRVNAME, -1);
	अगर (!f7188x_gpio_pdev)
		वापस -ENOMEM;

	err = platक्रमm_device_add_data(f7188x_gpio_pdev,
				       sio, माप(*sio));
	अगर (err) अणु
		pr_err(DRVNAME "Platform data allocation failed\n");
		जाओ err;
	पूर्ण

	err = platक्रमm_device_add(f7188x_gpio_pdev);
	अगर (err) अणु
		pr_err(DRVNAME "Device addition failed\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	platक्रमm_device_put(f7188x_gpio_pdev);

	वापस err;
पूर्ण

/*
 * Try to match a supported Fपूर्णांकek device by पढ़ोing the (hard-wired)
 * configuration I/O ports. If available, then रेजिस्टर both the platक्रमm
 * device and driver to support the GPIOs.
 */

अटल काष्ठा platक्रमm_driver f7188x_gpio_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= f7188x_gpio_probe,
पूर्ण;

अटल पूर्णांक __init f7188x_gpio_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा f7188x_sio sio;

	अगर (f7188x_find(0x2e, &sio) &&
	    f7188x_find(0x4e, &sio))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&f7188x_gpio_driver);
	अगर (!err) अणु
		err = f7188x_gpio_device_add(&sio);
		अगर (err)
			platक्रमm_driver_unरेजिस्टर(&f7188x_gpio_driver);
	पूर्ण

	वापस err;
पूर्ण
subsys_initcall(f7188x_gpio_init);

अटल व्योम __निकास f7188x_gpio_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(f7188x_gpio_pdev);
	platक्रमm_driver_unरेजिस्टर(&f7188x_gpio_driver);
पूर्ण
module_निकास(f7188x_gpio_निकास);

MODULE_DESCRIPTION("GPIO driver for Super-I/O chips F71869, F71869A, F71882FG, F71889A, F71889F and F81866");
MODULE_AUTHOR("Simon Guinot <simon.guinot@sequanux.org>");
MODULE_LICENSE("GPL");
