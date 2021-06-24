<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Low Power Subप्रणाली PWM controller driver
 *
 * Copyright (C) 2014, Intel Corporation
 *
 * Derived from the original pwm-lpss.c
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "pwm-lpss.h"

/* BayTrail */
अटल स्थिर काष्ठा pwm_lpss_boardinfo pwm_lpss_byt_info = अणु
	.clk_rate = 25000000,
	.npwm = 1,
	.base_unit_bits = 16,
पूर्ण;

/* Braswell */
अटल स्थिर काष्ठा pwm_lpss_boardinfo pwm_lpss_bsw_info = अणु
	.clk_rate = 19200000,
	.npwm = 1,
	.base_unit_bits = 16,
	.other_devices_aml_touches_pwm_regs = true,
पूर्ण;

/* Broxton */
अटल स्थिर काष्ठा pwm_lpss_boardinfo pwm_lpss_bxt_info = अणु
	.clk_rate = 19200000,
	.npwm = 4,
	.base_unit_bits = 22,
	.bypass = true,
पूर्ण;

अटल पूर्णांक pwm_lpss_probe_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा pwm_lpss_boardinfo *info;
	स्थिर काष्ठा acpi_device_id *id;
	काष्ठा pwm_lpss_chip *lpwm;
	काष्ठा resource *r;

	id = acpi_match_device(pdev->dev.driver->acpi_match_table, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	info = (स्थिर काष्ठा pwm_lpss_boardinfo *)id->driver_data;
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	lpwm = pwm_lpss_probe(&pdev->dev, r, info);
	अगर (IS_ERR(lpwm))
		वापस PTR_ERR(lpwm);

	platक्रमm_set_drvdata(pdev, lpwm);

	/*
	 * On Cherry Trail devices the GFX0._PS0 AML checks अगर the controller
	 * is on and अगर it is not on it turns it on and restores what it
	 * believes is the correct state to the PWM controller.
	 * Because of this we must disallow direct-complete, which keeps the
	 * controller (runसमय)suspended on resume, to aव्योम 2 issues:
	 * 1. The controller getting turned on without the linux-pm code
	 *    knowing about this. On devices where the controller is unused
	 *    this causes it to stay on during the next suspend causing high
	 *    battery drain (because S0i3 is not reached)
	 * 2. The state restoring code unexpectedly messing with the controller
	 *
	 * Leaving the controller runसमय-suspended (skipping runसमय-resume +
	 * normal-suspend) during suspend is fine.
	 */
	अगर (info->other_devices_aml_touches_pwm_regs)
		dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE|
						    DPM_FLAG_SMART_SUSPEND);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_lpss_हटाओ_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_lpss_chip *lpwm = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	वापस pwm_lpss_हटाओ(lpwm);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pwm_lpss_acpi_match[] = अणु
	अणु "80860F09", (अचिन्हित दीर्घ)&pwm_lpss_byt_info पूर्ण,
	अणु "80862288", (अचिन्हित दीर्घ)&pwm_lpss_bsw_info पूर्ण,
	अणु "80862289", (अचिन्हित दीर्घ)&pwm_lpss_bsw_info पूर्ण,
	अणु "80865AC8", (अचिन्हित दीर्घ)&pwm_lpss_bxt_info पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pwm_lpss_acpi_match);

अटल काष्ठा platक्रमm_driver pwm_lpss_driver_platक्रमm = अणु
	.driver = अणु
		.name = "pwm-lpss",
		.acpi_match_table = pwm_lpss_acpi_match,
	पूर्ण,
	.probe = pwm_lpss_probe_platक्रमm,
	.हटाओ = pwm_lpss_हटाओ_platक्रमm,
पूर्ण;
module_platक्रमm_driver(pwm_lpss_driver_platक्रमm);

MODULE_DESCRIPTION("PWM platform driver for Intel LPSS");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pwm-lpss");
