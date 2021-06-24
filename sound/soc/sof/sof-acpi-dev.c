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

#समावेश <linux/acpi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश <sound/sof.h>
#समावेश "../intel/common/soc-intel-quirks.h"
#समावेश "ops.h"
#समावेश "sof-acpi-dev.h"

/* platक्रमm specअगरic devices */
#समावेश "intel/shim.h"

अटल अक्षर *fw_path;
module_param(fw_path, अक्षरp, 0444);
MODULE_PARM_DESC(fw_path, "alternate path for SOF firmware.");

अटल अक्षर *tplg_path;
module_param(tplg_path, अक्षरp, 0444);
MODULE_PARM_DESC(tplg_path, "alternate path for SOF topology.");

अटल पूर्णांक sof_acpi_debug;
module_param_named(sof_acpi_debug, sof_acpi_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(sof_acpi_debug, "SOF ACPI debug options (0x0 all off)");

#घोषणा SOF_ACPI_DISABLE_PM_RUNTIME BIT(0)

स्थिर काष्ठा dev_pm_ops sof_acpi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(snd_sof_suspend, snd_sof_resume)
	SET_RUNTIME_PM_OPS(snd_sof_runसमय_suspend, snd_sof_runसमय_resume,
			   snd_sof_runसमय_idle)
पूर्ण;
EXPORT_SYMBOL_NS(sof_acpi_pm, SND_SOC_SOF_ACPI_DEV);

अटल व्योम sof_acpi_probe_complete(काष्ठा device *dev)
अणु
	dev_dbg(dev, "Completing SOF ACPI probe");

	अगर (sof_acpi_debug & SOF_ACPI_DISABLE_PM_RUNTIME)
		वापस;

	/* allow runसमय_pm */
	pm_runसमय_set_स्वतःsuspend_delay(dev, SND_SOF_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);
पूर्ण

पूर्णांक sof_acpi_probe(काष्ठा platक्रमm_device *pdev, स्थिर काष्ठा sof_dev_desc *desc)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_sof_pdata *sof_pdata;
	स्थिर काष्ठा snd_sof_dsp_ops *ops;

	dev_dbg(dev, "ACPI DSP detected");

	sof_pdata = devm_kzalloc(dev, माप(*sof_pdata), GFP_KERNEL);
	अगर (!sof_pdata)
		वापस -ENOMEM;

	/* get ops क्रम platक्रमm */
	ops = desc->ops;
	अगर (!ops) अणु
		dev_err(dev, "error: no matching ACPI descriptor ops\n");
		वापस -ENODEV;
	पूर्ण

	sof_pdata->desc = desc;
	sof_pdata->dev = &pdev->dev;
	sof_pdata->fw_filename = desc->शेष_fw_filename;

	/* alternate fw and tplg filenames ? */
	अगर (fw_path)
		sof_pdata->fw_filename_prefix = fw_path;
	अन्यथा
		sof_pdata->fw_filename_prefix =
			sof_pdata->desc->शेष_fw_path;

	अगर (tplg_path)
		sof_pdata->tplg_filename_prefix = tplg_path;
	अन्यथा
		sof_pdata->tplg_filename_prefix =
			sof_pdata->desc->शेष_tplg_path;

	/* set callback to be called on successful device probe to enable runसमय_pm */
	sof_pdata->sof_probe_complete = sof_acpi_probe_complete;

	/* call sof helper क्रम DSP hardware probe */
	वापस snd_sof_device_probe(dev, sof_pdata);
पूर्ण
EXPORT_SYMBOL_NS(sof_acpi_probe, SND_SOC_SOF_ACPI_DEV);

पूर्णांक sof_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	अगर (!(sof_acpi_debug & SOF_ACPI_DISABLE_PM_RUNTIME))
		pm_runसमय_disable(dev);

	/* call sof helper क्रम DSP hardware हटाओ */
	snd_sof_device_हटाओ(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS(sof_acpi_हटाओ, SND_SOC_SOF_ACPI_DEV);

MODULE_LICENSE("Dual BSD/GPL");
