<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Analog Devices ADAU7118 8 channel PDM-to-I2S/TDM Converter Standalone Hw
// driver
//
// Copyright 2019 Analog Devices Inc.

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "adau7118.h"

अटल पूर्णांक adau7118_probe_hw(काष्ठा platक्रमm_device *pdev)
अणु
	वापस adau7118_probe(&pdev->dev, शून्य, true);
पूर्ण

अटल स्थिर काष्ठा of_device_id adau7118_of_match[] = अणु
	अणु .compatible = "adi,adau7118" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adau7118_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id adau7118_id[] = अणु
	अणु .name	= "adau7118" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, adau7118_id);

अटल काष्ठा platक्रमm_driver adau7118_driver_hw = अणु
	.driver = अणु
		.name = "adau7118",
		.of_match_table = adau7118_of_match,
	पूर्ण,
	.probe = adau7118_probe_hw,
	.id_table = adau7118_id,
पूर्ण;
module_platक्रमm_driver(adau7118_driver_hw);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("ADAU7118 8 channel PDM-to-I2S/TDM Converter driver for standalone hw mode");
MODULE_LICENSE("GPL");
