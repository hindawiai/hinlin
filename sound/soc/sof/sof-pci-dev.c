<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/firmware.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश <sound/sof.h>
#समावेश "ops.h"
#समावेश "sof-pci-dev.h"

अटल अक्षर *fw_path;
module_param(fw_path, अक्षरp, 0444);
MODULE_PARM_DESC(fw_path, "alternate path for SOF firmware.");

अटल अक्षर *tplg_path;
module_param(tplg_path, अक्षरp, 0444);
MODULE_PARM_DESC(tplg_path, "alternate path for SOF topology.");

अटल पूर्णांक sof_pci_debug;
module_param_named(sof_pci_debug, sof_pci_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(sof_pci_debug, "SOF PCI debug options (0x0 all off)");

अटल स्थिर अक्षर *sof_override_tplg_name;

#घोषणा SOF_PCI_DISABLE_PM_RUNTIME BIT(0)

अटल पूर्णांक sof_tplg_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_override_tplg_name = id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_tplg_table[] = अणु
	अणु
		.callback = sof_tplg_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Google_Volteer"),
			DMI_MATCH(DMI_OEM_STRING, "AUDIO-MAX98373_ALC5682I_I2S_UP4"),
		पूर्ण,
		.driver_data = "sof-tgl-rt5682-ssp0-max98373-ssp2.tplg",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id community_key_platक्रमms[] = अणु
	अणु
		.ident = "Up Squared",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
			DMI_MATCH(DMI_BOARD_NAME, "UP-APL01"),
		पूर्ण
	पूर्ण,
	अणु
		.ident = "Up Extreme",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
			DMI_MATCH(DMI_BOARD_NAME, "UP-WHL01"),
		पूर्ण
	पूर्ण,
	अणु
		.ident = "Google Chromebooks",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Google"),
		पूर्ण
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा dev_pm_ops sof_pci_pm = अणु
	.prepare = snd_sof_prepare,
	.complete = snd_sof_complete,
	SET_SYSTEM_SLEEP_PM_OPS(snd_sof_suspend, snd_sof_resume)
	SET_RUNTIME_PM_OPS(snd_sof_runसमय_suspend, snd_sof_runसमय_resume,
			   snd_sof_runसमय_idle)
पूर्ण;
EXPORT_SYMBOL_NS(sof_pci_pm, SND_SOC_SOF_PCI_DEV);

अटल व्योम sof_pci_probe_complete(काष्ठा device *dev)
अणु
	dev_dbg(dev, "Completing SOF PCI probe");

	अगर (sof_pci_debug & SOF_PCI_DISABLE_PM_RUNTIME)
		वापस;

	/* allow runसमय_pm */
	pm_runसमय_set_स्वतःsuspend_delay(dev, SND_SOF_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);

	/*
	 * runसमय pm क्रम pci device is "forbidden" by शेष.
	 * so call pm_runसमय_allow() to enable it.
	 */
	pm_runसमय_allow(dev);

	/* mark last_busy क्रम pm_runसमय to make sure not suspend immediately */
	pm_runसमय_mark_last_busy(dev);

	/* follow recommendation in pci-driver.c to decrement usage counter */
	pm_runसमय_put_noidle(dev);
पूर्ण

पूर्णांक sof_pci_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा device *dev = &pci->dev;
	स्थिर काष्ठा sof_dev_desc *desc =
		(स्थिर काष्ठा sof_dev_desc *)pci_id->driver_data;
	काष्ठा snd_sof_pdata *sof_pdata;
	स्थिर काष्ठा snd_sof_dsp_ops *ops;
	पूर्णांक ret;

	dev_dbg(&pci->dev, "PCI DSP detected");

	/* get ops क्रम platक्रमm */
	ops = desc->ops;
	अगर (!ops) अणु
		dev_err(dev, "error: no matching PCI descriptor ops\n");
		वापस -ENODEV;
	पूर्ण

	sof_pdata = devm_kzalloc(dev, माप(*sof_pdata), GFP_KERNEL);
	अगर (!sof_pdata)
		वापस -ENOMEM;

	ret = pcim_enable_device(pci);
	अगर (ret < 0)
		वापस ret;

	ret = pci_request_regions(pci, "Audio DSP");
	अगर (ret < 0)
		वापस ret;

	sof_pdata->name = pci_name(pci);
	sof_pdata->desc = (काष्ठा sof_dev_desc *)pci_id->driver_data;
	sof_pdata->dev = dev;
	sof_pdata->fw_filename = desc->शेष_fw_filename;

	/*
	 * क्रम platक्रमms using the SOF community key, change the
	 * शेष path स्वतःmatically to pick the right files from the
	 * linux-firmware tree. This can be overridden with the
	 * fw_path kernel parameter, e.g. क्रम developers.
	 */

	/* alternate fw and tplg filenames ? */
	अगर (fw_path) अणु
		sof_pdata->fw_filename_prefix = fw_path;

		dev_dbg(dev,
			"Module parameter used, changed fw path to %s\n",
			sof_pdata->fw_filename_prefix);

	पूर्ण अन्यथा अगर (dmi_check_प्रणाली(community_key_platक्रमms)) अणु
		sof_pdata->fw_filename_prefix =
			devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s/%s",
				       sof_pdata->desc->शेष_fw_path,
				       "community");

		dev_dbg(dev,
			"Platform uses community key, changed fw path to %s\n",
			sof_pdata->fw_filename_prefix);
	पूर्ण अन्यथा अणु
		sof_pdata->fw_filename_prefix =
			sof_pdata->desc->शेष_fw_path;
	पूर्ण

	अगर (tplg_path)
		sof_pdata->tplg_filename_prefix = tplg_path;
	अन्यथा
		sof_pdata->tplg_filename_prefix =
			sof_pdata->desc->शेष_tplg_path;

	dmi_check_प्रणाली(sof_tplg_table);
	अगर (sof_override_tplg_name)
		sof_pdata->tplg_filename = sof_override_tplg_name;

	/* set callback to be called on successful device probe to enable runसमय_pm */
	sof_pdata->sof_probe_complete = sof_pci_probe_complete;

	/* call sof helper क्रम DSP hardware probe */
	ret = snd_sof_device_probe(dev, sof_pdata);
	अगर (ret)
		pci_release_regions(pci);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_NS(sof_pci_probe, SND_SOC_SOF_PCI_DEV);

व्योम sof_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	/* call sof helper क्रम DSP hardware हटाओ */
	snd_sof_device_हटाओ(&pci->dev);

	/* follow recommendation in pci-driver.c to increment usage counter */
	अगर (snd_sof_device_probe_completed(&pci->dev) &&
	    !(sof_pci_debug & SOF_PCI_DISABLE_PM_RUNTIME))
		pm_runसमय_get_noresume(&pci->dev);

	/* release pci regions and disable device */
	pci_release_regions(pci);
पूर्ण
EXPORT_SYMBOL_NS(sof_pci_हटाओ, SND_SOC_SOF_PCI_DEV);

व्योम sof_pci_shutकरोwn(काष्ठा pci_dev *pci)
अणु
	snd_sof_device_shutकरोwn(&pci->dev);
पूर्ण
EXPORT_SYMBOL_NS(sof_pci_shutकरोwn, SND_SOC_SOF_PCI_DEV);

MODULE_LICENSE("Dual BSD/GPL");
