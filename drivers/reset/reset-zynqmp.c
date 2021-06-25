<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Xilinx, Inc.
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश <linux/of_device.h>

#घोषणा ZYNQMP_NR_RESETS (ZYNQMP_PM_RESET_END - ZYNQMP_PM_RESET_START)
#घोषणा ZYNQMP_RESET_ID ZYNQMP_PM_RESET_START
#घोषणा VERSAL_NR_RESETS	95

काष्ठा zynqmp_reset_soc_data अणु
	u32 reset_id;
	u32 num_resets;
पूर्ण;

काष्ठा zynqmp_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	स्थिर काष्ठा zynqmp_reset_soc_data *data;
पूर्ण;

अटल अंतरभूत काष्ठा zynqmp_reset_data *
to_zynqmp_reset_data(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा zynqmp_reset_data, rcdev);
पूर्ण

अटल पूर्णांक zynqmp_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा zynqmp_reset_data *priv = to_zynqmp_reset_data(rcdev);

	वापस zynqmp_pm_reset_निश्चित(priv->data->reset_id + id,
				      PM_RESET_ACTION_ASSERT);
पूर्ण

अटल पूर्णांक zynqmp_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा zynqmp_reset_data *priv = to_zynqmp_reset_data(rcdev);

	वापस zynqmp_pm_reset_निश्चित(priv->data->reset_id + id,
				      PM_RESET_ACTION_RELEASE);
पूर्ण

अटल पूर्णांक zynqmp_reset_status(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा zynqmp_reset_data *priv = to_zynqmp_reset_data(rcdev);
	पूर्णांक val, err;

	err = zynqmp_pm_reset_get_status(priv->data->reset_id + id, &val);
	अगर (err)
		वापस err;

	वापस val;
पूर्ण

अटल पूर्णांक zynqmp_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा zynqmp_reset_data *priv = to_zynqmp_reset_data(rcdev);

	वापस zynqmp_pm_reset_निश्चित(priv->data->reset_id + id,
				      PM_RESET_ACTION_PULSE);
पूर्ण

अटल पूर्णांक zynqmp_reset_of_xlate(काष्ठा reset_controller_dev *rcdev,
				 स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	वापस reset_spec->args[0];
पूर्ण

अटल स्थिर काष्ठा zynqmp_reset_soc_data zynqmp_reset_data = अणु
	.reset_id = ZYNQMP_RESET_ID,
	.num_resets = ZYNQMP_NR_RESETS,
पूर्ण;

अटल स्थिर काष्ठा zynqmp_reset_soc_data versal_reset_data = अणु
        .reset_id = 0,
        .num_resets = VERSAL_NR_RESETS,
पूर्ण;

अटल स्थिर काष्ठा reset_control_ops zynqmp_reset_ops = अणु
	.reset = zynqmp_reset_reset,
	.निश्चित = zynqmp_reset_निश्चित,
	.deनिश्चित = zynqmp_reset_deनिश्चित,
	.status = zynqmp_reset_status,
पूर्ण;

अटल पूर्णांक zynqmp_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_reset_data *priv;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = of_device_get_match_data(&pdev->dev);
	अगर (!priv->data)
		वापस -EINVAL;

	platक्रमm_set_drvdata(pdev, priv);

	priv->rcdev.ops = &zynqmp_reset_ops;
	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.of_node = pdev->dev.of_node;
	priv->rcdev.nr_resets = priv->data->num_resets;
	priv->rcdev.of_reset_n_cells = 1;
	priv->rcdev.of_xlate = zynqmp_reset_of_xlate;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_reset_dt_ids[] = अणु
	अणु .compatible = "xlnx,zynqmp-reset", .data = &zynqmp_reset_data, पूर्ण,
	अणु .compatible = "xlnx,versal-reset", .data = &versal_reset_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver zynqmp_reset_driver = अणु
	.probe	= zynqmp_reset_probe,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= zynqmp_reset_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init zynqmp_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&zynqmp_reset_driver);
पूर्ण

arch_initcall(zynqmp_reset_init);
