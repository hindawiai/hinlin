<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RPM over SMD communication wrapper क्रम पूर्णांकerconnects
 *
 * Copyright (C) 2019 Linaro Ltd
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/qcom/smd-rpm.h>

#समावेश "smd-rpm.h"

#घोषणा RPM_KEY_BW		0x00007762

अटल काष्ठा qcom_smd_rpm *icc_smd_rpm;

काष्ठा icc_rpm_smd_req अणु
	__le32 key;
	__le32 nbytes;
	__le32 value;
पूर्ण;

bool qcom_icc_rpm_smd_available(व्योम)
अणु
	वापस !!icc_smd_rpm;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_rpm_smd_available);

पूर्णांक qcom_icc_rpm_smd_send(पूर्णांक ctx, पूर्णांक rsc_type, पूर्णांक id, u32 val)
अणु
	काष्ठा icc_rpm_smd_req req = अणु
		.key = cpu_to_le32(RPM_KEY_BW),
		.nbytes = cpu_to_le32(माप(u32)),
		.value = cpu_to_le32(val),
	पूर्ण;

	वापस qcom_rpm_smd_ग_लिखो(icc_smd_rpm, ctx, rsc_type, id, &req,
				  माप(req));
पूर्ण
EXPORT_SYMBOL_GPL(qcom_icc_rpm_smd_send);

अटल पूर्णांक qcom_icc_rpm_smd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	icc_smd_rpm = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_icc_rpm_smd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	icc_smd_rpm = dev_get_drvdata(pdev->dev.parent);

	अगर (!icc_smd_rpm) अणु
		dev_err(&pdev->dev, "unable to retrieve handle to RPM\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_पूर्णांकerconnect_rpm_smd_driver = अणु
	.driver = अणु
		.name		= "icc_smd_rpm",
	पूर्ण,
	.probe = qcom_icc_rpm_smd_probe,
	.हटाओ = qcom_icc_rpm_smd_हटाओ,
पूर्ण;
module_platक्रमm_driver(qcom_पूर्णांकerconnect_rpm_smd_driver);
MODULE_AUTHOR("Georgi Djakov <georgi.djakov@linaro.org>");
MODULE_DESCRIPTION("Qualcomm SMD RPM interconnect proxy driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:icc_smd_rpm");
