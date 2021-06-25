<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// Copyright 2019 NXP
//
// Author: Daniel Baluta <daniel.baluta@nxp.com>
//

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/sof.h>

#समावेश "ops.h"

बाह्य काष्ठा snd_sof_dsp_ops sof_imx8_ops;
बाह्य काष्ठा snd_sof_dsp_ops sof_imx8x_ops;
बाह्य काष्ठा snd_sof_dsp_ops sof_imx8m_ops;

/* platक्रमm specअगरic devices */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_IMX8)
अटल काष्ठा sof_dev_desc sof_of_imx8qxp_desc = अणु
	.शेष_fw_path = "imx/sof",
	.शेष_tplg_path = "imx/sof-tplg",
	.शेष_fw_filename = "sof-imx8x.ri",
	.nocodec_tplg_filename = "sof-imx8-nocodec.tplg",
	.ops = &sof_imx8x_ops,
पूर्ण;

अटल काष्ठा sof_dev_desc sof_of_imx8qm_desc = अणु
	.शेष_fw_path = "imx/sof",
	.शेष_tplg_path = "imx/sof-tplg",
	.शेष_fw_filename = "sof-imx8.ri",
	.nocodec_tplg_filename = "sof-imx8-nocodec.tplg",
	.ops = &sof_imx8_ops,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_IMX8M)
अटल काष्ठा sof_dev_desc sof_of_imx8mp_desc = अणु
	.शेष_fw_path = "imx/sof",
	.शेष_tplg_path = "imx/sof-tplg",
	.शेष_fw_filename = "sof-imx8m.ri",
	.nocodec_tplg_filename = "sof-imx8-nocodec.tplg",
	.ops = &sof_imx8m_ops,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sof_of_pm = अणु
	.prepare = snd_sof_prepare,
	.complete = snd_sof_complete,
	SET_SYSTEM_SLEEP_PM_OPS(snd_sof_suspend, snd_sof_resume)
	SET_RUNTIME_PM_OPS(snd_sof_runसमय_suspend, snd_sof_runसमय_resume,
			   शून्य)
पूर्ण;

अटल व्योम sof_of_probe_complete(काष्ठा device *dev)
अणु
	/* allow runसमय_pm */
	pm_runसमय_set_स्वतःsuspend_delay(dev, SND_SOF_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल पूर्णांक sof_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sof_dev_desc *desc;
	काष्ठा snd_sof_pdata *sof_pdata;
	स्थिर काष्ठा snd_sof_dsp_ops *ops;

	dev_info(&pdev->dev, "DT DSP detected");

	sof_pdata = devm_kzalloc(dev, माप(*sof_pdata), GFP_KERNEL);
	अगर (!sof_pdata)
		वापस -ENOMEM;

	desc = device_get_match_data(dev);
	अगर (!desc)
		वापस -ENODEV;

	/* get ops क्रम platक्रमm */
	ops = desc->ops;
	अगर (!ops) अणु
		dev_err(dev, "error: no matching DT descriptor ops\n");
		वापस -ENODEV;
	पूर्ण

	sof_pdata->desc = desc;
	sof_pdata->dev = &pdev->dev;
	sof_pdata->fw_filename = desc->शेष_fw_filename;

	/* TODO: पढ़ो alternate fw and tplg filenames from DT */
	sof_pdata->fw_filename_prefix = sof_pdata->desc->शेष_fw_path;
	sof_pdata->tplg_filename_prefix = sof_pdata->desc->शेष_tplg_path;

	/* set callback to be called on successful device probe to enable runसमय_pm */
	sof_pdata->sof_probe_complete = sof_of_probe_complete;

	/* call sof helper क्रम DSP hardware probe */
	वापस snd_sof_device_probe(dev, sof_pdata);
पूर्ण

अटल पूर्णांक sof_of_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	/* call sof helper क्रम DSP hardware हटाओ */
	snd_sof_device_हटाओ(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sof_of_ids[] = अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_IMX8)
	अणु .compatible = "fsl,imx8qxp-dsp", .data = &sof_of_imx8qxp_descपूर्ण,
	अणु .compatible = "fsl,imx8qm-dsp", .data = &sof_of_imx8qm_descपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_IMX8M)
	अणु .compatible = "fsl,imx8mp-dsp", .data = &sof_of_imx8mp_descपूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sof_of_ids);

/* DT driver definition */
अटल काष्ठा platक्रमm_driver snd_sof_of_driver = अणु
	.probe = sof_of_probe,
	.हटाओ = sof_of_हटाओ,
	.driver = अणु
		.name = "sof-audio-of",
		.pm = &sof_of_pm,
		.of_match_table = sof_of_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_sof_of_driver);

MODULE_LICENSE("Dual BSD/GPL");
