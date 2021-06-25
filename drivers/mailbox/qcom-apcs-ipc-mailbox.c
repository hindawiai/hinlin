<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, Linaro Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mailbox_controller.h>

#घोषणा QCOM_APCS_IPC_BITS	32

काष्ठा qcom_apcs_ipc अणु
	काष्ठा mbox_controller mbox;
	काष्ठा mbox_chan mbox_chans[QCOM_APCS_IPC_BITS];

	काष्ठा regmap *regmap;
	अचिन्हित दीर्घ offset;
	काष्ठा platक्रमm_device *clk;
पूर्ण;

काष्ठा qcom_apcs_ipc_data अणु
	पूर्णांक offset;
	अक्षर *clk_name;
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data ipq6018_apcs_data = अणु
	.offset = 8, .clk_name = "qcom,apss-ipq6018-clk"
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data ipq8074_apcs_data = अणु
	.offset = 8, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data msm8916_apcs_data = अणु
	.offset = 8, .clk_name = "qcom-apcs-msm8916-clk"
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data msm8994_apcs_data = अणु
	.offset = 8, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data msm8996_apcs_data = अणु
	.offset = 16, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data msm8998_apcs_data = अणु
	.offset = 8, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data sdm660_apcs_data = अणु
	.offset = 8, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data apps_shared_apcs_data = अणु
	.offset = 12, .clk_name = शून्य
पूर्ण;

अटल स्थिर काष्ठा qcom_apcs_ipc_data sdx55_apcs_data = अणु
	.offset = 0x1008, .clk_name = "qcom-sdx55-acps-clk"
पूर्ण;

अटल स्थिर काष्ठा regmap_config apcs_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0x1008,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक qcom_apcs_ipc_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा qcom_apcs_ipc *apcs = container_of(chan->mbox,
						  काष्ठा qcom_apcs_ipc, mbox);
	अचिन्हित दीर्घ idx = (अचिन्हित दीर्घ)chan->con_priv;

	वापस regmap_ग_लिखो(apcs->regmap, apcs->offset, BIT(idx));
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops qcom_apcs_ipc_ops = अणु
	.send_data = qcom_apcs_ipc_send_data,
पूर्ण;

अटल पूर्णांक qcom_apcs_ipc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_apcs_ipc *apcs;
	स्थिर काष्ठा qcom_apcs_ipc_data *apcs_data;
	काष्ठा regmap *regmap;
	काष्ठा resource *res;
	व्योम __iomem *base;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;

	apcs = devm_kzalloc(&pdev->dev, माप(*apcs), GFP_KERNEL);
	अगर (!apcs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base, &apcs_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	apcs_data = of_device_get_match_data(&pdev->dev);

	apcs->regmap = regmap;
	apcs->offset = apcs_data->offset;

	/* Initialize channel identअगरiers */
	क्रम (i = 0; i < ARRAY_SIZE(apcs->mbox_chans); i++)
		apcs->mbox_chans[i].con_priv = (व्योम *)i;

	apcs->mbox.dev = &pdev->dev;
	apcs->mbox.ops = &qcom_apcs_ipc_ops;
	apcs->mbox.chans = apcs->mbox_chans;
	apcs->mbox.num_chans = ARRAY_SIZE(apcs->mbox_chans);

	ret = devm_mbox_controller_रेजिस्टर(&pdev->dev, &apcs->mbox);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register APCS IPC controller\n");
		वापस ret;
	पूर्ण

	अगर (apcs_data->clk_name) अणु
		apcs->clk = platक्रमm_device_रेजिस्टर_data(&pdev->dev,
							  apcs_data->clk_name,
							  PLATFORM_DEVID_NONE,
							  शून्य, 0);
		अगर (IS_ERR(apcs->clk))
			dev_err(&pdev->dev, "failed to register APCS clk\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, apcs);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_apcs_ipc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_apcs_ipc *apcs = platक्रमm_get_drvdata(pdev);
	काष्ठा platक्रमm_device *clk = apcs->clk;

	platक्रमm_device_unरेजिस्टर(clk);

	वापस 0;
पूर्ण

/* .data is the offset of the ipc रेजिस्टर within the global block */
अटल स्थिर काष्ठा of_device_id qcom_apcs_ipc_of_match[] = अणु
	अणु .compatible = "qcom,ipq6018-apcs-apps-global", .data = &ipq6018_apcs_data पूर्ण,
	अणु .compatible = "qcom,ipq8074-apcs-apps-global", .data = &ipq8074_apcs_data पूर्ण,
	अणु .compatible = "qcom,msm8916-apcs-kpss-global", .data = &msm8916_apcs_data पूर्ण,
	अणु .compatible = "qcom,msm8994-apcs-kpss-global", .data = &msm8994_apcs_data पूर्ण,
	अणु .compatible = "qcom,msm8996-apcs-hmss-global", .data = &msm8996_apcs_data पूर्ण,
	अणु .compatible = "qcom,msm8998-apcs-hmss-global", .data = &msm8998_apcs_data पूर्ण,
	अणु .compatible = "qcom,qcs404-apcs-apps-global", .data = &msm8916_apcs_data पूर्ण,
	अणु .compatible = "qcom,sc7180-apss-shared", .data = &apps_shared_apcs_data पूर्ण,
	अणु .compatible = "qcom,sc8180x-apss-shared", .data = &apps_shared_apcs_data पूर्ण,
	अणु .compatible = "qcom,sdm660-apcs-hmss-global", .data = &sdm660_apcs_data पूर्ण,
	अणु .compatible = "qcom,sdm845-apss-shared", .data = &apps_shared_apcs_data पूर्ण,
	अणु .compatible = "qcom,sm8150-apss-shared", .data = &apps_shared_apcs_data पूर्ण,
	अणु .compatible = "qcom,sdx55-apcs-gcc", .data = &sdx55_apcs_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_apcs_ipc_of_match);

अटल काष्ठा platक्रमm_driver qcom_apcs_ipc_driver = अणु
	.probe = qcom_apcs_ipc_probe,
	.हटाओ = qcom_apcs_ipc_हटाओ,
	.driver = अणु
		.name = "qcom_apcs_ipc",
		.of_match_table = qcom_apcs_ipc_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_apcs_ipc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_apcs_ipc_driver);
पूर्ण
postcore_initcall(qcom_apcs_ipc_init);

अटल व्योम __निकास qcom_apcs_ipc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_apcs_ipc_driver);
पूर्ण
module_निकास(qcom_apcs_ipc_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm APCS IPC driver");
