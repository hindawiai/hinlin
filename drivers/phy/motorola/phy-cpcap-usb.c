<शैली गुरु>
/*
 * Motorola CPCAP PMIC USB PHY driver
 * Copyright (C) 2017 Tony Lindgren <tony@atomide.com>
 *
 * Some parts based on earlier Motorola Linux kernel tree code in
 * board-mapphone-usb.c and cpcap-usb-det.c:
 * Copyright (C) 2007 - 2011 Motorola, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mfd/motorola-cpcap.h>
#समावेश <linux/phy/omap_usb.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/musb.h>

/* CPCAP_REG_USBC1 रेजिस्टर bits */
#घोषणा CPCAP_BIT_IDPULSE		BIT(15)
#घोषणा CPCAP_BIT_ID100KPU		BIT(14)
#घोषणा CPCAP_BIT_IDPUCNTRL		BIT(13)
#घोषणा CPCAP_BIT_IDPU			BIT(12)
#घोषणा CPCAP_BIT_IDPD			BIT(11)
#घोषणा CPCAP_BIT_VBUSCHRGTMR3		BIT(10)
#घोषणा CPCAP_BIT_VBUSCHRGTMR2		BIT(9)
#घोषणा CPCAP_BIT_VBUSCHRGTMR1		BIT(8)
#घोषणा CPCAP_BIT_VBUSCHRGTMR0		BIT(7)
#घोषणा CPCAP_BIT_VBUSPU		BIT(6)
#घोषणा CPCAP_BIT_VBUSPD		BIT(5)
#घोषणा CPCAP_BIT_DMPD			BIT(4)
#घोषणा CPCAP_BIT_DPPD			BIT(3)
#घोषणा CPCAP_BIT_DM1K5PU		BIT(2)
#घोषणा CPCAP_BIT_DP1K5PU		BIT(1)
#घोषणा CPCAP_BIT_DP150KPU		BIT(0)

/* CPCAP_REG_USBC2 रेजिस्टर bits */
#घोषणा CPCAP_BIT_ZHSDRV1		BIT(15)
#घोषणा CPCAP_BIT_ZHSDRV0		BIT(14)
#घोषणा CPCAP_BIT_DPLLCLKREQ		BIT(13)
#घोषणा CPCAP_BIT_SE0CONN		BIT(12)
#घोषणा CPCAP_BIT_UARTTXTRI		BIT(11)
#घोषणा CPCAP_BIT_UARTSWAP		BIT(10)
#घोषणा CPCAP_BIT_UARTMUX1		BIT(9)
#घोषणा CPCAP_BIT_UARTMUX0		BIT(8)
#घोषणा CPCAP_BIT_ULPISTPLOW		BIT(7)
#घोषणा CPCAP_BIT_TXENPOL		BIT(6)
#घोषणा CPCAP_BIT_USBXCVREN		BIT(5)
#घोषणा CPCAP_BIT_USBCNTRL		BIT(4)
#घोषणा CPCAP_BIT_USBSUSPEND		BIT(3)
#घोषणा CPCAP_BIT_EMUMODE2		BIT(2)
#घोषणा CPCAP_BIT_EMUMODE1		BIT(1)
#घोषणा CPCAP_BIT_EMUMODE0		BIT(0)

/* CPCAP_REG_USBC3 रेजिस्टर bits */
#घोषणा CPCAP_BIT_SPARE_898_15		BIT(15)
#घोषणा CPCAP_BIT_IHSTX03		BIT(14)
#घोषणा CPCAP_BIT_IHSTX02		BIT(13)
#घोषणा CPCAP_BIT_IHSTX01		BIT(12)
#घोषणा CPCAP_BIT_IHSTX0		BIT(11)
#घोषणा CPCAP_BIT_IDPU_SPI		BIT(10)
#घोषणा CPCAP_BIT_UNUSED_898_9		BIT(9)
#घोषणा CPCAP_BIT_VBUSSTBY_EN		BIT(8)
#घोषणा CPCAP_BIT_VBUSEN_SPI		BIT(7)
#घोषणा CPCAP_BIT_VBUSPU_SPI		BIT(6)
#घोषणा CPCAP_BIT_VBUSPD_SPI		BIT(5)
#घोषणा CPCAP_BIT_DMPD_SPI		BIT(4)
#घोषणा CPCAP_BIT_DPPD_SPI		BIT(3)
#घोषणा CPCAP_BIT_SUSPEND_SPI		BIT(2)
#घोषणा CPCAP_BIT_PU_SPI		BIT(1)
#घोषणा CPCAP_BIT_ULPI_SPI_SEL		BIT(0)

काष्ठा cpcap_usb_पूर्णांकs_state अणु
	bool id_ground;
	bool id_भग्न;
	bool chrg_det;
	bool rvrs_chrg;
	bool vbusov;

	bool chrg_se1b;
	bool se0conn;
	bool rvrs_mode;
	bool chrgcurr1;
	bool vbusvld;
	bool sessvld;
	bool sessend;
	bool se1;

	bool battdetb;
	bool dm;
	bool dp;
पूर्ण;

क्रमागत cpcap_gpio_mode अणु
	CPCAP_DM_DP,
	CPCAP_MDM_RX_TX,
	CPCAP_UNKNOWN_DISABLED,	/* Seems to disable USB lines */
	CPCAP_OTG_DM_DP,
पूर्ण;

काष्ठा cpcap_phy_ddata अणु
	काष्ठा regmap *reg;
	काष्ठा device *dev;
	काष्ठा usb_phy phy;
	काष्ठा delayed_work detect_work;
	काष्ठा pinctrl *pins;
	काष्ठा pinctrl_state *pins_ulpi;
	काष्ठा pinctrl_state *pins_uपंचांगi;
	काष्ठा pinctrl_state *pins_uart;
	काष्ठा gpio_desc *gpio[2];
	काष्ठा iio_channel *vbus;
	काष्ठा iio_channel *id;
	काष्ठा regulator *vusb;
	atomic_t active;
	अचिन्हित पूर्णांक vbus_provider:1;
	अचिन्हित पूर्णांक करोcked:1;
पूर्ण;

अटल bool cpcap_usb_vbus_valid(काष्ठा cpcap_phy_ddata *ddata)
अणु
	पूर्णांक error, value = 0;

	error = iio_पढ़ो_channel_processed(ddata->vbus, &value);
	अगर (error >= 0)
		वापस value > 3900;

	dev_err(ddata->dev, "error reading VBUS: %i\n", error);

	वापस false;
पूर्ण

अटल पूर्णांक cpcap_usb_phy_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	otg->host = host;
	अगर (!host)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_usb_phy_set_peripheral(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget)
अणु
	otg->gadget = gadget;
	अगर (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक cpcap_phy_get_पूर्णांकs_state(काष्ठा cpcap_phy_ddata *ddata,
				    काष्ठा cpcap_usb_पूर्णांकs_state *s)
अणु
	पूर्णांक val, error;

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS1, &val);
	अगर (error)
		वापस error;

	s->id_ground = val & BIT(15);
	s->id_भग्न = val & BIT(14);
	s->vbusov = val & BIT(11);

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS2, &val);
	अगर (error)
		वापस error;

	s->vbusvld = val & BIT(3);
	s->sessvld = val & BIT(2);
	s->sessend = val & BIT(1);
	s->se1 = val & BIT(0);

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_INTS4, &val);
	अगर (error)
		वापस error;

	s->dm = val & BIT(1);
	s->dp = val & BIT(0);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_usb_set_uart_mode(काष्ठा cpcap_phy_ddata *ddata);
अटल पूर्णांक cpcap_usb_set_usb_mode(काष्ठा cpcap_phy_ddata *ddata);

अटल व्योम cpcap_usb_try_musb_mailbox(काष्ठा cpcap_phy_ddata *ddata,
				       क्रमागत musb_vbus_id_status status)
अणु
	पूर्णांक error;

	error = musb_mailbox(status);
	अगर (!error)
		वापस;

	dev_dbg(ddata->dev, "%s: musb_mailbox failed: %i\n",
		__func__, error);
पूर्ण

अटल व्योम cpcap_usb_detect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpcap_phy_ddata *ddata;
	काष्ठा cpcap_usb_पूर्णांकs_state s;
	bool vbus = false;
	पूर्णांक error;

	ddata = container_of(work, काष्ठा cpcap_phy_ddata, detect_work.work);

	error = cpcap_phy_get_पूर्णांकs_state(ddata, &s);
	अगर (error)
		वापस;

	vbus = cpcap_usb_vbus_valid(ddata);

	/* We need to kick the VBUS as USB A-host */
	अगर (s.id_ground && ddata->vbus_provider) अणु
		dev_dbg(ddata->dev, "still in USB A-host mode, kicking VBUS\n");

		cpcap_usb_try_musb_mailbox(ddata, MUSB_ID_GROUND);

		error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC3,
					   CPCAP_BIT_VBUSSTBY_EN |
					   CPCAP_BIT_VBUSEN_SPI,
					   CPCAP_BIT_VBUSEN_SPI);
		अगर (error)
			जाओ out_err;

		वापस;
	पूर्ण

	अगर (vbus && s.id_ground && ddata->करोcked) अणु
		dev_dbg(ddata->dev, "still docked as A-host, signal ID down\n");

		cpcap_usb_try_musb_mailbox(ddata, MUSB_ID_GROUND);

		वापस;
	पूर्ण

	/* No VBUS needed with करोcks */
	अगर (vbus && s.id_ground && !ddata->vbus_provider) अणु
		dev_dbg(ddata->dev, "connected to a dock\n");

		ddata->करोcked = true;

		error = cpcap_usb_set_usb_mode(ddata);
		अगर (error)
			जाओ out_err;

		cpcap_usb_try_musb_mailbox(ddata, MUSB_ID_GROUND);

		/*
		 * Force check state again after musb has reoriented,
		 * otherwise devices won't क्रमागतerate after loading PHY
		 * driver.
		 */
		schedule_delayed_work(&ddata->detect_work,
				      msecs_to_jअगरfies(1000));

		वापस;
	पूर्ण

	अगर (s.id_ground && !ddata->करोcked) अणु
		dev_dbg(ddata->dev, "id ground, USB host mode\n");

		ddata->vbus_provider = true;

		error = cpcap_usb_set_usb_mode(ddata);
		अगर (error)
			जाओ out_err;

		cpcap_usb_try_musb_mailbox(ddata, MUSB_ID_GROUND);

		error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC3,
					   CPCAP_BIT_VBUSSTBY_EN |
					   CPCAP_BIT_VBUSEN_SPI,
					   CPCAP_BIT_VBUSEN_SPI);
		अगर (error)
			जाओ out_err;

		वापस;
	पूर्ण

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC3,
				   CPCAP_BIT_VBUSSTBY_EN |
				   CPCAP_BIT_VBUSEN_SPI, 0);
	अगर (error)
		जाओ out_err;

	vbus = cpcap_usb_vbus_valid(ddata);

	/* Otherwise assume we're connected to a USB host */
	अगर (vbus) अणु
		dev_dbg(ddata->dev, "connected to USB host\n");
		error = cpcap_usb_set_usb_mode(ddata);
		अगर (error)
			जाओ out_err;
		cpcap_usb_try_musb_mailbox(ddata, MUSB_VBUS_VALID);

		वापस;
	पूर्ण

	ddata->vbus_provider = false;
	ddata->करोcked = false;
	cpcap_usb_try_musb_mailbox(ddata, MUSB_VBUS_OFF);

	/* Default to debug UART mode */
	error = cpcap_usb_set_uart_mode(ddata);
	अगर (error)
		जाओ out_err;

	dev_dbg(ddata->dev, "set UART mode\n");

	वापस;

out_err:
	dev_err(ddata->dev, "error setting cable state: %i\n", error);
पूर्ण

अटल irqवापस_t cpcap_phy_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cpcap_phy_ddata *ddata = data;

	अगर (!atomic_पढ़ो(&ddata->active))
		वापस IRQ_NONE;

	schedule_delayed_work(&ddata->detect_work, msecs_to_jअगरfies(1));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpcap_usb_init_irq(काष्ठा platक्रमm_device *pdev,
			      काष्ठा cpcap_phy_ddata *ddata,
			      स्थिर अक्षर *name)
अणु
	पूर्णांक irq, error;

	irq = platक्रमm_get_irq_byname(pdev, name);
	अगर (irq < 0)
		वापस -ENODEV;

	error = devm_request_thपढ़ोed_irq(ddata->dev, irq, शून्य,
					  cpcap_phy_irq_thपढ़ो,
					  IRQF_SHARED |
					  IRQF_ONESHOT,
					  name, ddata);
	अगर (error) अणु
		dev_err(ddata->dev, "could not get irq %s: %i\n",
			name, error);

		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर cpcap_phy_irqs[] = अणु
	/* REG_INT_0 */
	"id_ground", "id_float",

	/* REG_INT1 */
	"se0conn", "vbusvld", "sessvld", "sessend", "se1",

	/* REG_INT_3 */
	"dm", "dp",
पूर्ण;

अटल पूर्णांक cpcap_usb_init_पूर्णांकerrupts(काष्ठा platक्रमm_device *pdev,
				     काष्ठा cpcap_phy_ddata *ddata)
अणु
	पूर्णांक i, error;

	क्रम (i = 0; i < ARRAY_SIZE(cpcap_phy_irqs); i++) अणु
		error = cpcap_usb_init_irq(pdev, ddata, cpcap_phy_irqs[i]);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Optional pins and modes. At least Motorola mapphone devices
 * are using two GPIOs and dynamic pinctrl to multiplex PHY pins
 * to UART, ULPI or UTMI mode.
 */

अटल पूर्णांक cpcap_usb_gpio_set_mode(काष्ठा cpcap_phy_ddata *ddata,
				   क्रमागत cpcap_gpio_mode mode)
अणु
	अगर (!ddata->gpio[0] || !ddata->gpio[1])
		वापस 0;

	gpiod_set_value(ddata->gpio[0], mode & 1);
	gpiod_set_value(ddata->gpio[1], mode >> 1);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_usb_set_uart_mode(काष्ठा cpcap_phy_ddata *ddata)
अणु
	पूर्णांक error;

	/* Disable lines to prevent glitches from waking up mdm6600 */
	error = cpcap_usb_gpio_set_mode(ddata, CPCAP_UNKNOWN_DISABLED);
	अगर (error)
		जाओ out_err;

	अगर (ddata->pins_uart) अणु
		error = pinctrl_select_state(ddata->pins, ddata->pins_uart);
		अगर (error)
			जाओ out_err;
	पूर्ण

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC1,
				   CPCAP_BIT_VBUSPD,
				   CPCAP_BIT_VBUSPD);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC2,
				   0xffff, CPCAP_BIT_UARTMUX0 |
				   CPCAP_BIT_EMUMODE0);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC3, 0x7fff,
				   CPCAP_BIT_IDPU_SPI);
	अगर (error)
		जाओ out_err;

	/* Enable UART mode */
	error = cpcap_usb_gpio_set_mode(ddata, CPCAP_DM_DP);
	अगर (error)
		जाओ out_err;

	वापस 0;

out_err:
	dev_err(ddata->dev, "%s failed with %i\n", __func__, error);

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_usb_set_usb_mode(काष्ठा cpcap_phy_ddata *ddata)
अणु
	पूर्णांक error;

	/* Disable lines to prevent glitches from waking up mdm6600 */
	error = cpcap_usb_gpio_set_mode(ddata, CPCAP_UNKNOWN_DISABLED);
	अगर (error)
		वापस error;

	अगर (ddata->pins_uपंचांगi) अणु
		error = pinctrl_select_state(ddata->pins, ddata->pins_uपंचांगi);
		अगर (error) अणु
			dev_err(ddata->dev, "could not set usb mode: %i\n",
				error);

			वापस error;
		पूर्ण
	पूर्ण

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC1,
				   CPCAP_BIT_VBUSPD, 0);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC3,
				   CPCAP_BIT_PU_SPI |
				   CPCAP_BIT_DMPD_SPI |
				   CPCAP_BIT_DPPD_SPI |
				   CPCAP_BIT_SUSPEND_SPI |
				   CPCAP_BIT_ULPI_SPI_SEL, 0);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_USBC2,
				   CPCAP_BIT_USBXCVREN,
				   CPCAP_BIT_USBXCVREN);
	अगर (error)
		जाओ out_err;

	/* Enable USB mode */
	error = cpcap_usb_gpio_set_mode(ddata, CPCAP_OTG_DM_DP);
	अगर (error)
		जाओ out_err;

	वापस 0;

out_err:
	dev_err(ddata->dev, "%s failed with %i\n", __func__, error);

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_usb_init_optional_pins(काष्ठा cpcap_phy_ddata *ddata)
अणु
	ddata->pins = devm_pinctrl_get(ddata->dev);
	अगर (IS_ERR(ddata->pins)) अणु
		dev_info(ddata->dev, "default pins not configured: %ld\n",
			 PTR_ERR(ddata->pins));
		ddata->pins = शून्य;

		वापस 0;
	पूर्ण

	ddata->pins_ulpi = pinctrl_lookup_state(ddata->pins, "ulpi");
	अगर (IS_ERR(ddata->pins_ulpi)) अणु
		dev_info(ddata->dev, "ulpi pins not configured\n");
		ddata->pins_ulpi = शून्य;
	पूर्ण

	ddata->pins_uपंचांगi = pinctrl_lookup_state(ddata->pins, "utmi");
	अगर (IS_ERR(ddata->pins_uपंचांगi)) अणु
		dev_info(ddata->dev, "utmi pins not configured\n");
		ddata->pins_uपंचांगi = शून्य;
	पूर्ण

	ddata->pins_uart = pinctrl_lookup_state(ddata->pins, "uart");
	अगर (IS_ERR(ddata->pins_uart)) अणु
		dev_info(ddata->dev, "uart pins not configured\n");
		ddata->pins_uart = शून्य;
	पूर्ण

	अगर (ddata->pins_uart)
		वापस pinctrl_select_state(ddata->pins, ddata->pins_uart);

	वापस 0;
पूर्ण

अटल व्योम cpcap_usb_init_optional_gpios(काष्ठा cpcap_phy_ddata *ddata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		ddata->gpio[i] = devm_gpiod_get_index(ddata->dev, "mode",
						      i, GPIOD_OUT_HIGH);
		अगर (IS_ERR(ddata->gpio[i])) अणु
			dev_info(ddata->dev, "no mode change GPIO%i: %li\n",
				 i, PTR_ERR(ddata->gpio[i]));
			ddata->gpio[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cpcap_usb_init_iio(काष्ठा cpcap_phy_ddata *ddata)
अणु
	क्रमागत iio_chan_type type;
	पूर्णांक error;

	ddata->vbus = devm_iio_channel_get(ddata->dev, "vbus");
	अगर (IS_ERR(ddata->vbus)) अणु
		error = PTR_ERR(ddata->vbus);
		जाओ out_err;
	पूर्ण

	अगर (!ddata->vbus->indio_dev) अणु
		error = -ENXIO;
		जाओ out_err;
	पूर्ण

	error = iio_get_channel_type(ddata->vbus, &type);
	अगर (error < 0)
		जाओ out_err;

	अगर (type != IIO_VOLTAGE) अणु
		error = -EINVAL;
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	dev_err(ddata->dev, "could not initialize VBUS or ID IIO: %i\n",
		error);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cpcap_usb_phy_id_table[] = अणु
	अणु
		.compatible = "motorola,cpcap-usb-phy",
	पूर्ण,
	अणु
		.compatible = "motorola,mapphone-cpcap-usb-phy",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_usb_phy_id_table);
#पूर्ण_अगर

अटल पूर्णांक cpcap_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_phy_ddata *ddata;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा usb_otg *otg;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक error;

	of_id = of_match_device(of_match_ptr(cpcap_usb_phy_id_table),
				&pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->reg = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!ddata->reg)
		वापस -ENODEV;

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->phy.dev = ddata->dev;
	ddata->phy.label = "cpcap_usb_phy";
	ddata->phy.otg = otg;
	ddata->phy.type = USB_PHY_TYPE_USB2;
	otg->set_host = cpcap_usb_phy_set_host;
	otg->set_peripheral = cpcap_usb_phy_set_peripheral;
	otg->usb_phy = &ddata->phy;
	INIT_DELAYED_WORK(&ddata->detect_work, cpcap_usb_detect);
	platक्रमm_set_drvdata(pdev, ddata);

	ddata->vusb = devm_regulator_get(&pdev->dev, "vusb");
	अगर (IS_ERR(ddata->vusb))
		वापस PTR_ERR(ddata->vusb);

	error = regulator_enable(ddata->vusb);
	अगर (error)
		वापस error;

	generic_phy = devm_phy_create(ddata->dev, शून्य, &ops);
	अगर (IS_ERR(generic_phy)) अणु
		error = PTR_ERR(generic_phy);
		जाओ out_reg_disable;
	पूर्ण

	phy_set_drvdata(generic_phy, ddata);

	phy_provider = devm_of_phy_provider_रेजिस्टर(ddata->dev,
						     of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		error = PTR_ERR(phy_provider);
		जाओ out_reg_disable;
	पूर्ण

	error = cpcap_usb_init_optional_pins(ddata);
	अगर (error)
		जाओ out_reg_disable;

	cpcap_usb_init_optional_gpios(ddata);

	error = cpcap_usb_init_iio(ddata);
	अगर (error)
		जाओ out_reg_disable;

	error = cpcap_usb_init_पूर्णांकerrupts(pdev, ddata);
	अगर (error)
		जाओ out_reg_disable;

	usb_add_phy_dev(&ddata->phy);
	atomic_set(&ddata->active, 1);
	schedule_delayed_work(&ddata->detect_work, msecs_to_jअगरfies(1));

	वापस 0;

out_reg_disable:
	regulator_disable(ddata->vusb);

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_phy_ddata *ddata = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	atomic_set(&ddata->active, 0);
	error = cpcap_usb_set_uart_mode(ddata);
	अगर (error)
		dev_err(ddata->dev, "could not set UART mode\n");

	cpcap_usb_try_musb_mailbox(ddata, MUSB_VBUS_OFF);

	usb_हटाओ_phy(&ddata->phy);
	cancel_delayed_work_sync(&ddata->detect_work);
	regulator_disable(ddata->vusb);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_usb_phy_driver = अणु
	.probe		= cpcap_usb_phy_probe,
	.हटाओ		= cpcap_usb_phy_हटाओ,
	.driver		= अणु
		.name	= "cpcap-usb-phy",
		.of_match_table = of_match_ptr(cpcap_usb_phy_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cpcap_usb_phy_driver);

MODULE_ALIAS("platform:cpcap_usb");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("CPCAP usb phy driver");
MODULE_LICENSE("GPL v2");
