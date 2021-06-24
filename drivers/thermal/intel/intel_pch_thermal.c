<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* पूर्णांकel_pch_thermal.c - Intel PCH Thermal driver
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * Authors:
 *     Tushar Dave <tushar.n.dave@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/thermal.h>
#समावेश <linux/types.h>
#समावेश <linux/units.h>

/* Intel PCH thermal Device IDs */
#घोषणा PCH_THERMAL_DID_HSW_1	0x9C24 /* Haswell PCH */
#घोषणा PCH_THERMAL_DID_HSW_2	0x8C24 /* Haswell PCH */
#घोषणा PCH_THERMAL_DID_WPT	0x9CA4 /* Wildcat Poपूर्णांक */
#घोषणा PCH_THERMAL_DID_SKL	0x9D31 /* Skylake PCH */
#घोषणा PCH_THERMAL_DID_SKL_H	0xA131 /* Skylake PCH 100 series */
#घोषणा PCH_THERMAL_DID_CNL	0x9Df9 /* CNL PCH */
#घोषणा PCH_THERMAL_DID_CNL_H	0xA379 /* CNL-H PCH */
#घोषणा PCH_THERMAL_DID_CNL_LP	0x02F9 /* CNL-LP PCH */
#घोषणा PCH_THERMAL_DID_CML_H	0X06F9 /* CML-H PCH */
#घोषणा PCH_THERMAL_DID_LWB	0xA1B1 /* Lewisburg PCH */

/* Wildcat Poपूर्णांक-LP  PCH Thermal रेजिस्टरs */
#घोषणा WPT_TEMP	0x0000	/* Temperature */
#घोषणा WPT_TSC	0x04	/* Thermal Sensor Control */
#घोषणा WPT_TSS	0x06	/* Thermal Sensor Status */
#घोषणा WPT_TSEL	0x08	/* Thermal Sensor Enable and Lock */
#घोषणा WPT_TSREL	0x0A	/* Thermal Sensor Report Enable and Lock */
#घोषणा WPT_TSMIC	0x0C	/* Thermal Sensor SMI Control */
#घोषणा WPT_CTT	0x0010	/* Catastrophic Trip Poपूर्णांक */
#घोषणा WPT_TSPM	0x001C	/* Thermal Sensor Power Management */
#घोषणा WPT_TAHV	0x0014	/* Thermal Alert High Value */
#घोषणा WPT_TALV	0x0018	/* Thermal Alert Low Value */
#घोषणा WPT_TL		0x00000040	/* Throttle Value */
#घोषणा WPT_PHL	0x0060	/* PCH Hot Level */
#घोषणा WPT_PHLC	0x62	/* PHL Control */
#घोषणा WPT_TAS	0x80	/* Thermal Alert Status */
#घोषणा WPT_TSPIEN	0x82	/* PCI Interrupt Event Enables */
#घोषणा WPT_TSGPEN	0x84	/* General Purpose Event Enables */

/*  Wildcat Poपूर्णांक-LP  PCH Thermal Register bit definitions */
#घोषणा WPT_TEMP_TSR	0x01ff	/* Temp TS Reading */
#घोषणा WPT_TSC_CPDE	0x01	/* Catastrophic Power-Down Enable */
#घोषणा WPT_TSS_TSDSS	0x10	/* Thermal Sensor Dynamic Shutकरोwn Status */
#घोषणा WPT_TSS_GPES	0x08	/* GPE status */
#घोषणा WPT_TSEL_ETS	0x01    /* Enable TS */
#घोषणा WPT_TSEL_PLDB	0x80	/* TSEL Policy Lock-Down Bit */
#घोषणा WPT_TL_TOL	0x000001FF	/* T0 Level */
#घोषणा WPT_TL_T1L	0x1ff00000	/* T1 Level */
#घोषणा WPT_TL_TTEN	0x20000000	/* TT Enable */

/* Resolution of 1/2 degree C and an offset of -50C */
#घोषणा PCH_TEMP_OFFSET	(-50)
#घोषणा GET_WPT_TEMP(x)	((x) * MILLIDEGREE_PER_DEGREE / 2 + WPT_TEMP_OFFSET)
#घोषणा WPT_TEMP_OFFSET	(PCH_TEMP_OFFSET * MILLIDEGREE_PER_DEGREE)
#घोषणा GET_PCH_TEMP(x)	(((x) / 2) + PCH_TEMP_OFFSET)

/* Amount of समय क्रम each cooling delay, 100ms by शेष क्रम now */
अटल अचिन्हित पूर्णांक delay_समयout = 100;
module_param(delay_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(delay_समयout, "amount of time delay for each iteration.");

/* Number of iterations क्रम cooling delay, 10 counts by शेष क्रम now */
अटल अचिन्हित पूर्णांक delay_cnt = 10;
module_param(delay_cnt, पूर्णांक, 0644);
MODULE_PARM_DESC(delay_cnt, "total number of iterations for time delay.");

अटल अक्षर driver_name[] = "Intel PCH thermal driver";

काष्ठा pch_thermal_device अणु
	व्योम __iomem *hw_base;
	स्थिर काष्ठा pch_dev_ops *ops;
	काष्ठा pci_dev *pdev;
	काष्ठा thermal_zone_device *tzd;
	पूर्णांक crt_trip_id;
	अचिन्हित दीर्घ crt_temp;
	पूर्णांक hot_trip_id;
	अचिन्हित दीर्घ hot_temp;
	पूर्णांक psv_trip_id;
	अचिन्हित दीर्घ psv_temp;
	bool bios_enabled;
पूर्ण;

#अगर_घोषित CONFIG_ACPI

/*
 * On some platक्रमms, there is a companion ACPI device, which adds
 * passive trip temperature using _PSV method. There is no specअगरic
 * passive temperature setting in MMIO पूर्णांकerface of this PCI device.
 */
अटल व्योम pch_wpt_add_acpi_psv_trip(काष्ठा pch_thermal_device *ptd,
				      पूर्णांक *nr_trips)
अणु
	काष्ठा acpi_device *adev;

	ptd->psv_trip_id = -1;

	adev = ACPI_COMPANION(&ptd->pdev->dev);
	अगर (adev) अणु
		अचिन्हित दीर्घ दीर्घ r;
		acpi_status status;

		status = acpi_evaluate_पूर्णांकeger(adev->handle, "_PSV", शून्य,
					       &r);
		अगर (ACPI_SUCCESS(status)) अणु
			अचिन्हित दीर्घ trip_temp;

			trip_temp = deci_kelvin_to_millicelsius(r);
			अगर (trip_temp) अणु
				ptd->psv_temp = trip_temp;
				ptd->psv_trip_id = *nr_trips;
				++(*nr_trips);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम pch_wpt_add_acpi_psv_trip(काष्ठा pch_thermal_device *ptd,
				      पूर्णांक *nr_trips)
अणु
	ptd->psv_trip_id = -1;

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pch_wpt_init(काष्ठा pch_thermal_device *ptd, पूर्णांक *nr_trips)
अणु
	u8 tsel;
	u16 trip_temp;

	*nr_trips = 0;

	/* Check अगर BIOS has alपढ़ोy enabled thermal sensor */
	अगर (WPT_TSEL_ETS & पढ़ोb(ptd->hw_base + WPT_TSEL)) अणु
		ptd->bios_enabled = true;
		जाओ पढ़ो_trips;
	पूर्ण

	tsel = पढ़ोb(ptd->hw_base + WPT_TSEL);
	/*
	 * When TSEL's Policy Lock-Down bit is 1, TSEL become RO.
	 * If so, thermal sensor cannot enable. Bail out.
	 */
	अगर (tsel & WPT_TSEL_PLDB) अणु
		dev_err(&ptd->pdev->dev, "Sensor can't be enabled\n");
		वापस -ENODEV;
	पूर्ण

	ग_लिखोb(tsel|WPT_TSEL_ETS, ptd->hw_base + WPT_TSEL);
	अगर (!(WPT_TSEL_ETS & पढ़ोb(ptd->hw_base + WPT_TSEL))) अणु
		dev_err(&ptd->pdev->dev, "Sensor can't be enabled\n");
		वापस -ENODEV;
	पूर्ण

पढ़ो_trips:
	ptd->crt_trip_id = -1;
	trip_temp = पढ़ोw(ptd->hw_base + WPT_CTT);
	trip_temp &= 0x1FF;
	अगर (trip_temp) अणु
		ptd->crt_temp = GET_WPT_TEMP(trip_temp);
		ptd->crt_trip_id = 0;
		++(*nr_trips);
	पूर्ण

	ptd->hot_trip_id = -1;
	trip_temp = पढ़ोw(ptd->hw_base + WPT_PHL);
	trip_temp &= 0x1FF;
	अगर (trip_temp) अणु
		ptd->hot_temp = GET_WPT_TEMP(trip_temp);
		ptd->hot_trip_id = *nr_trips;
		++(*nr_trips);
	पूर्ण

	pch_wpt_add_acpi_psv_trip(ptd, nr_trips);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_wpt_get_temp(काष्ठा pch_thermal_device *ptd, पूर्णांक *temp)
अणु
	*temp = GET_WPT_TEMP(WPT_TEMP_TSR & पढ़ोw(ptd->hw_base + WPT_TEMP));

	वापस 0;
पूर्ण

अटल पूर्णांक pch_wpt_suspend(काष्ठा pch_thermal_device *ptd)
अणु
	u8 tsel;
	u8 pch_delay_cnt = 1;
	u16 pch_thr_temp, pch_cur_temp;

	/* Shutकरोwn the thermal sensor अगर it is not enabled by BIOS */
	अगर (!ptd->bios_enabled) अणु
		tsel = पढ़ोb(ptd->hw_base + WPT_TSEL);
		ग_लिखोb(tsel & 0xFE, ptd->hw_base + WPT_TSEL);
		वापस 0;
	पूर्ण

	/* Do not check temperature अगर it is not a S0ix capable platक्रमm */
#अगर_घोषित CONFIG_ACPI
	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
		वापस 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर

	/* Do not check temperature अगर it is not s2idle */
	अगर (pm_suspend_via_firmware())
		वापस 0;

	/* Get the PCH temperature threshold value */
	pch_thr_temp = GET_PCH_TEMP(WPT_TEMP_TSR & पढ़ोw(ptd->hw_base + WPT_TSPM));

	/* Get the PCH current temperature value */
	pch_cur_temp = GET_PCH_TEMP(WPT_TEMP_TSR & पढ़ोw(ptd->hw_base + WPT_TEMP));

	/*
	 * If current PCH temperature is higher than configured PCH threshold
	 * value, run some delay loop with sleep to let the current temperature
	 * go करोwn below the threshold value which helps to allow प्रणाली enter
	 * lower घातer S0ix suspend state. Even after delay loop अगर PCH current
	 * temperature stays above threshold, notअगरy the warning message
	 * which helps to indentअगरy the reason why S0ix entry was rejected.
	 */
	जबतक (pch_delay_cnt <= delay_cnt) अणु
		अगर (pch_cur_temp <= pch_thr_temp)
			अवरोध;

		dev_warn(&ptd->pdev->dev,
			"CPU-PCH current temp [%dC] higher than the threshold temp [%dC], sleep %d times for %d ms duration\n",
			pch_cur_temp, pch_thr_temp, pch_delay_cnt, delay_समयout);
		msleep(delay_समयout);
		/* Read the PCH current temperature क्रम next cycle. */
		pch_cur_temp = GET_PCH_TEMP(WPT_TEMP_TSR & पढ़ोw(ptd->hw_base + WPT_TEMP));
		pch_delay_cnt++;
	पूर्ण

	अगर (pch_cur_temp > pch_thr_temp)
		dev_warn(&ptd->pdev->dev,
			"CPU-PCH is hot [%dC] even after delay, continue to suspend. S0ix might fail\n",
			pch_cur_temp);
	अन्यथा
		dev_info(&ptd->pdev->dev,
			"CPU-PCH is cool [%dC], continue to suspend\n", pch_cur_temp);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_wpt_resume(काष्ठा pch_thermal_device *ptd)
अणु
	u8 tsel;

	अगर (ptd->bios_enabled)
		वापस 0;

	tsel = पढ़ोb(ptd->hw_base + WPT_TSEL);

	ग_लिखोb(tsel | WPT_TSEL_ETS, ptd->hw_base + WPT_TSEL);

	वापस 0;
पूर्ण

काष्ठा pch_dev_ops अणु
	पूर्णांक (*hw_init)(काष्ठा pch_thermal_device *ptd, पूर्णांक *nr_trips);
	पूर्णांक (*get_temp)(काष्ठा pch_thermal_device *ptd, पूर्णांक *temp);
	पूर्णांक (*suspend)(काष्ठा pch_thermal_device *ptd);
	पूर्णांक (*resume)(काष्ठा pch_thermal_device *ptd);
पूर्ण;


/* dev ops क्रम Wildcat Poपूर्णांक */
अटल स्थिर काष्ठा pch_dev_ops pch_dev_ops_wpt = अणु
	.hw_init = pch_wpt_init,
	.get_temp = pch_wpt_get_temp,
	.suspend = pch_wpt_suspend,
	.resume = pch_wpt_resume,
पूर्ण;

अटल पूर्णांक pch_thermal_get_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक *temp)
अणु
	काष्ठा pch_thermal_device *ptd = tzd->devdata;

	वापस	ptd->ops->get_temp(ptd, temp);
पूर्ण

अटल पूर्णांक pch_get_trip_type(काष्ठा thermal_zone_device *tzd, पूर्णांक trip,
			     क्रमागत thermal_trip_type *type)
अणु
	काष्ठा pch_thermal_device *ptd = tzd->devdata;

	अगर (ptd->crt_trip_id == trip)
		*type = THERMAL_TRIP_CRITICAL;
	अन्यथा अगर (ptd->hot_trip_id == trip)
		*type = THERMAL_TRIP_HOT;
	अन्यथा अगर (ptd->psv_trip_id == trip)
		*type = THERMAL_TRIP_PASSIVE;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pch_get_trip_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा pch_thermal_device *ptd = tzd->devdata;

	अगर (ptd->crt_trip_id == trip)
		*temp = ptd->crt_temp;
	अन्यथा अगर (ptd->hot_trip_id == trip)
		*temp = ptd->hot_temp;
	अन्यथा अगर (ptd->psv_trip_id == trip)
		*temp = ptd->psv_temp;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम pch_critical(काष्ठा thermal_zone_device *tzd)
अणु
	dev_dbg(&tzd->device, "%s: critical temperature reached\n", tzd->type);
पूर्ण

अटल काष्ठा thermal_zone_device_ops tzd_ops = अणु
	.get_temp = pch_thermal_get_temp,
	.get_trip_type = pch_get_trip_type,
	.get_trip_temp = pch_get_trip_temp,
	.critical = pch_critical,
पूर्ण;

क्रमागत board_ids अणु
	board_hsw,
	board_wpt,
	board_skl,
	board_cnl,
	board_cml,
	board_lwb,
पूर्ण;

अटल स्थिर काष्ठा board_info अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा pch_dev_ops *ops;
पूर्ण board_info[] = अणु
	[board_hsw] = अणु
		.name = "pch_haswell",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
	[board_wpt] = अणु
		.name = "pch_wildcat_point",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
	[board_skl] = अणु
		.name = "pch_skylake",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
	[board_cnl] = अणु
		.name = "pch_cannonlake",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
	[board_cml] = अणु
		.name = "pch_cometlake",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
	[board_lwb] = अणु
		.name = "pch_lewisburg",
		.ops = &pch_dev_ops_wpt,
	पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_pch_thermal_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	क्रमागत board_ids board_id = id->driver_data;
	स्थिर काष्ठा board_info *bi = &board_info[board_id];
	काष्ठा pch_thermal_device *ptd;
	पूर्णांक err;
	पूर्णांक nr_trips;

	ptd = devm_kzalloc(&pdev->dev, माप(*ptd), GFP_KERNEL);
	अगर (!ptd)
		वापस -ENOMEM;

	ptd->ops = bi->ops;

	pci_set_drvdata(pdev, ptd);
	ptd->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable pci device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request pci region\n");
		जाओ error_disable;
	पूर्ण

	ptd->hw_base = pci_ioremap_bar(pdev, 0);
	अगर (!ptd->hw_base) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "failed to map mem base\n");
		जाओ error_release;
	पूर्ण

	err = ptd->ops->hw_init(ptd, &nr_trips);
	अगर (err)
		जाओ error_cleanup;

	ptd->tzd = thermal_zone_device_रेजिस्टर(bi->name, nr_trips, 0, ptd,
						&tzd_ops, शून्य, 0, 0);
	अगर (IS_ERR(ptd->tzd)) अणु
		dev_err(&pdev->dev, "Failed to register thermal zone %s\n",
			bi->name);
		err = PTR_ERR(ptd->tzd);
		जाओ error_cleanup;
	पूर्ण
	err = thermal_zone_device_enable(ptd->tzd);
	अगर (err)
		जाओ err_unरेजिस्टर;

	वापस 0;

err_unरेजिस्टर:
	thermal_zone_device_unरेजिस्टर(ptd->tzd);
error_cleanup:
	iounmap(ptd->hw_base);
error_release:
	pci_release_regions(pdev);
error_disable:
	pci_disable_device(pdev);
	dev_err(&pdev->dev, "pci device failed to probe\n");
	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_pch_thermal_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_thermal_device *ptd = pci_get_drvdata(pdev);

	thermal_zone_device_unरेजिस्टर(ptd->tzd);
	iounmap(ptd->hw_base);
	pci_set_drvdata(pdev, शून्य);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक पूर्णांकel_pch_thermal_suspend(काष्ठा device *device)
अणु
	काष्ठा pch_thermal_device *ptd = dev_get_drvdata(device);

	वापस ptd->ops->suspend(ptd);
पूर्ण

अटल पूर्णांक पूर्णांकel_pch_thermal_resume(काष्ठा device *device)
अणु
	काष्ठा pch_thermal_device *ptd = dev_get_drvdata(device);

	वापस ptd->ops->resume(ptd);
पूर्ण

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_pch_thermal_id[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_HSW_1),
		.driver_data = board_hsw, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_HSW_2),
		.driver_data = board_hsw, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_WPT),
		.driver_data = board_wpt, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_SKL),
		.driver_data = board_skl, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_SKL_H),
		.driver_data = board_skl, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_CNL),
		.driver_data = board_cnl, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_CNL_H),
		.driver_data = board_cnl, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_CNL_LP),
		.driver_data = board_cnl, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_CML_H),
		.driver_data = board_cml, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCH_THERMAL_DID_LWB),
		.driver_data = board_lwb, पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_pch_thermal_id);

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_pch_pm_ops = अणु
	.suspend = पूर्णांकel_pch_thermal_suspend,
	.resume = पूर्णांकel_pch_thermal_resume,
पूर्ण;

अटल काष्ठा pci_driver पूर्णांकel_pch_thermal_driver = अणु
	.name		= "intel_pch_thermal",
	.id_table	= पूर्णांकel_pch_thermal_id,
	.probe		= पूर्णांकel_pch_thermal_probe,
	.हटाओ		= पूर्णांकel_pch_thermal_हटाओ,
	.driver.pm	= &पूर्णांकel_pch_pm_ops,
पूर्ण;

module_pci_driver(पूर्णांकel_pch_thermal_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel PCH Thermal driver");
