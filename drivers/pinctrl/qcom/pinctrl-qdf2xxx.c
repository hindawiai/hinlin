<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 *
 * GPIO and pin control functions on this SOC are handled by the "TLMM"
 * device.  The driver which controls this device is pinctrl-msm.c.  Each
 * SOC with a TLMM is expected to create a client driver that रेजिस्टरs
 * with pinctrl-msm.c.  This means that all TLMM drivers are pin control
 * drivers.
 *
 * This pin control driver is पूर्णांकended to be used only an ACPI-enabled
 * प्रणाली.  As such, UEFI will handle all pin control configuration, so
 * this driver करोes not provide pin control functions.  It is effectively
 * a GPIO-only driver.  The alternative is to duplicate the GPIO code of
 * pinctrl-msm.c पूर्णांकo another driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/acpi.h>

#समावेश "pinctrl-msm.h"

/* A maximum of 256 allows us to use a u8 array to hold the GPIO numbers */
#घोषणा MAX_GPIOS	256

/* maximum size of each gpio name (enough room क्रम "gpioXXX" + null) */
#घोषणा NAME_SIZE	8

अटल पूर्णांक qdf2xxx_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_pinctrl_soc_data *pinctrl;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा msm_pingroup *groups;
	अक्षर (*names)[NAME_SIZE];
	अचिन्हित पूर्णांक i;
	u32 num_gpios;
	अचिन्हित पूर्णांक avail_gpios; /* The number of GPIOs we support */
	u8 gpios[MAX_GPIOS];      /* An array of supported GPIOs */
	पूर्णांक ret;

	/* Query the number of GPIOs from ACPI */
	ret = device_property_पढ़ो_u32(&pdev->dev, "num-gpios", &num_gpios);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "missing 'num-gpios' property\n");
		वापस ret;
	पूर्ण
	अगर (!num_gpios || num_gpios > MAX_GPIOS) अणु
		dev_err(&pdev->dev, "invalid 'num-gpios' property\n");
		वापस -ENODEV;
	पूर्ण

	/* The number of GPIOs in the approved list */
	ret = device_property_count_u8(&pdev->dev, "gpios");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "missing 'gpios' property\n");
		वापस ret;
	पूर्ण
	/*
	 * The number of available GPIOs should be non-zero, and no
	 * more than the total number of GPIOS.
	 */
	अगर (!ret || ret > num_gpios) अणु
		dev_err(&pdev->dev, "invalid 'gpios' property\n");
		वापस -ENODEV;
	पूर्ण
	avail_gpios = ret;

	ret = device_property_पढ़ो_u8_array(&pdev->dev, "gpios", gpios,
					    avail_gpios);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not read list of GPIOs\n");
		वापस ret;
	पूर्ण

	pinctrl = devm_kzalloc(&pdev->dev, माप(*pinctrl), GFP_KERNEL);
	pins = devm_kसुस्मृति(&pdev->dev, num_gpios,
		माप(काष्ठा pinctrl_pin_desc), GFP_KERNEL);
	groups = devm_kसुस्मृति(&pdev->dev, num_gpios,
		माप(काष्ठा msm_pingroup), GFP_KERNEL);
	names = devm_kसुस्मृति(&pdev->dev, avail_gpios, NAME_SIZE, GFP_KERNEL);

	अगर (!pinctrl || !pins || !groups || !names)
		वापस -ENOMEM;

	/*
	 * Initialize the array.  GPIOs not listed in the 'gpios' array
	 * still need a number, but nothing अन्यथा.
	 */
	क्रम (i = 0; i < num_gpios; i++) अणु
		pins[i].number = i;
		groups[i].pins = &pins[i].number;
	पूर्ण

	/* Populate the entries that are meant to be exposed as GPIOs. */
	क्रम (i = 0; i < avail_gpios; i++) अणु
		अचिन्हित पूर्णांक gpio = gpios[i];

		groups[gpio].npins = 1;
		snम_लिखो(names[i], NAME_SIZE, "gpio%u", gpio);
		pins[gpio].name = names[i];
		groups[gpio].name = names[i];

		groups[gpio].ctl_reg = 0x10000 * gpio;
		groups[gpio].io_reg = 0x04 + 0x10000 * gpio;
		groups[gpio].पूर्णांकr_cfg_reg = 0x08 + 0x10000 * gpio;
		groups[gpio].पूर्णांकr_status_reg = 0x0c + 0x10000 * gpio;
		groups[gpio].पूर्णांकr_target_reg = 0x08 + 0x10000 * gpio;

		groups[gpio].mux_bit = 2;
		groups[gpio].pull_bit = 0;
		groups[gpio].drv_bit = 6;
		groups[gpio].oe_bit = 9;
		groups[gpio].in_bit = 0;
		groups[gpio].out_bit = 1;
		groups[gpio].पूर्णांकr_enable_bit = 0;
		groups[gpio].पूर्णांकr_status_bit = 0;
		groups[gpio].पूर्णांकr_target_bit = 5;
		groups[gpio].पूर्णांकr_target_kpss_val = 1;
		groups[gpio].पूर्णांकr_raw_status_bit = 4;
		groups[gpio].पूर्णांकr_polarity_bit = 1;
		groups[gpio].पूर्णांकr_detection_bit = 2;
		groups[gpio].पूर्णांकr_detection_width = 2;
	पूर्ण

	pinctrl->pins = pins;
	pinctrl->groups = groups;
	pinctrl->npins = num_gpios;
	pinctrl->ngroups = num_gpios;
	pinctrl->ngpios = num_gpios;

	वापस msm_pinctrl_probe(pdev, pinctrl);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id qdf2xxx_acpi_ids[] = अणु
	अणु"QCOM8002"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, qdf2xxx_acpi_ids);

अटल काष्ठा platक्रमm_driver qdf2xxx_pinctrl_driver = अणु
	.driver = अणु
		.name = "qdf2xxx-pinctrl",
		.acpi_match_table = ACPI_PTR(qdf2xxx_acpi_ids),
	पूर्ण,
	.probe = qdf2xxx_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init qdf2xxx_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qdf2xxx_pinctrl_driver);
पूर्ण
arch_initcall(qdf2xxx_pinctrl_init);

अटल व्योम __निकास qdf2xxx_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qdf2xxx_pinctrl_driver);
पूर्ण
module_निकास(qdf2xxx_pinctrl_निकास);

MODULE_DESCRIPTION("Qualcomm Technologies QDF2xxx pin control driver");
MODULE_LICENSE("GPL v2");
