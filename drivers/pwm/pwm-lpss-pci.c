<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Low Power Subप्रणाली PWM controller PCI driver
 *
 * Copyright (C) 2014, Intel Corporation
 *
 * Derived from the original pwm-lpss.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
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
पूर्ण;

/* Broxton */
अटल स्थिर काष्ठा pwm_lpss_boardinfo pwm_lpss_bxt_info = अणु
	.clk_rate = 19200000,
	.npwm = 4,
	.base_unit_bits = 22,
	.bypass = true,
पूर्ण;

/* Tangier */
अटल स्थिर काष्ठा pwm_lpss_boardinfo pwm_lpss_tng_info = अणु
	.clk_rate = 19200000,
	.npwm = 4,
	.base_unit_bits = 22,
पूर्ण;

अटल पूर्णांक pwm_lpss_probe_pci(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा pwm_lpss_boardinfo *info;
	काष्ठा pwm_lpss_chip *lpwm;
	पूर्णांक err;

	err = pcim_enable_device(pdev);
	अगर (err < 0)
		वापस err;

	info = (काष्ठा pwm_lpss_boardinfo *)id->driver_data;
	lpwm = pwm_lpss_probe(&pdev->dev, &pdev->resource[0], info);
	अगर (IS_ERR(lpwm))
		वापस PTR_ERR(lpwm);

	pci_set_drvdata(pdev, lpwm);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम pwm_lpss_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pwm_lpss_chip *lpwm = pci_get_drvdata(pdev);

	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	pwm_lpss_हटाओ(lpwm);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pwm_lpss_runसमय_suspend_pci(काष्ठा device *dev)
अणु
	/*
	 * The PCI core will handle transition to D3 स्वतःmatically. We only
	 * need to provide runसमय PM hooks क्रम that to happen.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक pwm_lpss_runसमय_resume_pci(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pwm_lpss_pci_pm = अणु
	SET_RUNTIME_PM_OPS(pwm_lpss_runसमय_suspend_pci,
			   pwm_lpss_runसमय_resume_pci, शून्य)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pwm_lpss_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0ac8), (अचिन्हित दीर्घ)&pwm_lpss_bxt_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f08), (अचिन्हित दीर्घ)&pwm_lpss_byt_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f09), (अचिन्हित दीर्घ)&pwm_lpss_byt_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x11a5), (अचिन्हित दीर्घ)&pwm_lpss_tng_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac8), (अचिन्हित दीर्घ)&pwm_lpss_bxt_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2288), (अचिन्हित दीर्घ)&pwm_lpss_bsw_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2289), (अचिन्हित दीर्घ)&pwm_lpss_bsw_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c8), (अचिन्हित दीर्घ)&pwm_lpss_bxt_infoपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac8), (अचिन्हित दीर्घ)&pwm_lpss_bxt_infoपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pwm_lpss_pci_ids);

अटल काष्ठा pci_driver pwm_lpss_driver_pci = अणु
	.name = "pwm-lpss",
	.id_table = pwm_lpss_pci_ids,
	.probe = pwm_lpss_probe_pci,
	.हटाओ = pwm_lpss_हटाओ_pci,
	.driver = अणु
		.pm = &pwm_lpss_pci_pm,
	पूर्ण,
पूर्ण;
module_pci_driver(pwm_lpss_driver_pci);

MODULE_DESCRIPTION("PWM PCI driver for Intel LPSS");
MODULE_LICENSE("GPL v2");
