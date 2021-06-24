<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UCSI ACPI driver
 *
 * Copyright (C) 2017, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>

#समावेश "ucsi.h"

#घोषणा UCSI_DSM_UUID		"6f8398c2-7ca4-11e4-ad36-631042b5008f"
#घोषणा UCSI_DSM_FUNC_WRITE	1
#घोषणा UCSI_DSM_FUNC_READ	2

काष्ठा ucsi_acpi अणु
	काष्ठा device *dev;
	काष्ठा ucsi *ucsi;
	व्योम __iomem *base;
	काष्ठा completion complete;
	अचिन्हित दीर्घ flags;
	guid_t guid;
पूर्ण;

अटल पूर्णांक ucsi_acpi_dsm(काष्ठा ucsi_acpi *ua, पूर्णांक func)
अणु
	जोड़ acpi_object *obj;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(ua->dev), &ua->guid, 1, func,
				शून्य);
	अगर (!obj) अणु
		dev_err(ua->dev, "%s: failed to evaluate _DSM %d\n",
			__func__, func);
		वापस -EIO;
	पूर्ण

	ACPI_FREE(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_acpi_पढ़ो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
			  व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा ucsi_acpi *ua = ucsi_get_drvdata(ucsi);
	पूर्णांक ret;

	ret = ucsi_acpi_dsm(ua, UCSI_DSM_FUNC_READ);
	अगर (ret)
		वापस ret;

	स_नकल(val, (स्थिर व्योम __क्रमce *)(ua->base + offset), val_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_acpi_async_ग_लिखो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
				 स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा ucsi_acpi *ua = ucsi_get_drvdata(ucsi);

	स_नकल((व्योम __क्रमce *)(ua->base + offset), val, val_len);

	वापस ucsi_acpi_dsm(ua, UCSI_DSM_FUNC_WRITE);
पूर्ण

अटल पूर्णांक ucsi_acpi_sync_ग_लिखो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
				स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा ucsi_acpi *ua = ucsi_get_drvdata(ucsi);
	पूर्णांक ret;

	set_bit(COMMAND_PENDING, &ua->flags);

	ret = ucsi_acpi_async_ग_लिखो(ucsi, offset, val, val_len);
	अगर (ret)
		जाओ out_clear_bit;

	अगर (!रुको_क्रम_completion_समयout(&ua->complete, 60 * HZ))
		ret = -ETIMEDOUT;

out_clear_bit:
	clear_bit(COMMAND_PENDING, &ua->flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ucsi_operations ucsi_acpi_ops = अणु
	.पढ़ो = ucsi_acpi_पढ़ो,
	.sync_ग_लिखो = ucsi_acpi_sync_ग_लिखो,
	.async_ग_लिखो = ucsi_acpi_async_ग_लिखो
पूर्ण;

अटल व्योम ucsi_acpi_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा ucsi_acpi *ua = data;
	u32 cci;
	पूर्णांक ret;

	ret = ucsi_acpi_पढ़ो(ua->ucsi, UCSI_CCI, &cci, माप(cci));
	अगर (ret)
		वापस;

	अगर (UCSI_CCI_CONNECTOR(cci))
		ucsi_connector_change(ua->ucsi, UCSI_CCI_CONNECTOR(cci));

	अगर (test_bit(COMMAND_PENDING, &ua->flags) &&
	    cci & (UCSI_CCI_ACK_COMPLETE | UCSI_CCI_COMMAND_COMPLETE))
		complete(&ua->complete);
पूर्ण

अटल पूर्णांक ucsi_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	काष्ठा ucsi_acpi *ua;
	काष्ठा resource *res;
	acpi_status status;
	पूर्णांक ret;

	अगर (adev->dep_unmet)
		वापस -EPROBE_DEFER;

	ua = devm_kzalloc(&pdev->dev, माप(*ua), GFP_KERNEL);
	अगर (!ua)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "missing memory resource\n");
		वापस -ENODEV;
	पूर्ण

	/* This will make sure we can use ioremap() */
	status = acpi_release_memory(ACPI_HANDLE(&pdev->dev), res, 1);
	अगर (ACPI_FAILURE(status))
		वापस -ENOMEM;

	/*
	 * NOTE: The memory region क्रम the data काष्ठाures is used also in an
	 * operation region, which means ACPI has alपढ़ोy reserved it. Thereक्रमe
	 * it can not be requested here, and we can not use
	 * devm_ioremap_resource().
	 */
	ua->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!ua->base)
		वापस -ENOMEM;

	ret = guid_parse(UCSI_DSM_UUID, &ua->guid);
	अगर (ret)
		वापस ret;

	init_completion(&ua->complete);
	ua->dev = &pdev->dev;

	ua->ucsi = ucsi_create(&pdev->dev, &ucsi_acpi_ops);
	अगर (IS_ERR(ua->ucsi))
		वापस PTR_ERR(ua->ucsi);

	ucsi_set_drvdata(ua->ucsi, ua);

	status = acpi_install_notअगरy_handler(ACPI_HANDLE(&pdev->dev),
					     ACPI_DEVICE_NOTIFY,
					     ucsi_acpi_notअगरy, ua);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&pdev->dev, "failed to install notify handler\n");
		ucsi_destroy(ua->ucsi);
		वापस -ENODEV;
	पूर्ण

	ret = ucsi_रेजिस्टर(ua->ucsi);
	अगर (ret) अणु
		acpi_हटाओ_notअगरy_handler(ACPI_HANDLE(&pdev->dev),
					   ACPI_DEVICE_NOTIFY,
					   ucsi_acpi_notअगरy);
		ucsi_destroy(ua->ucsi);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ua);

	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ucsi_acpi *ua = platक्रमm_get_drvdata(pdev);

	ucsi_unरेजिस्टर(ua->ucsi);
	ucsi_destroy(ua->ucsi);

	acpi_हटाओ_notअगरy_handler(ACPI_HANDLE(&pdev->dev), ACPI_DEVICE_NOTIFY,
				   ucsi_acpi_notअगरy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ucsi_acpi_match[] = अणु
	अणु "PNP0CA0", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ucsi_acpi_match);

अटल काष्ठा platक्रमm_driver ucsi_acpi_platक्रमm_driver = अणु
	.driver = अणु
		.name = "ucsi_acpi",
		.acpi_match_table = ACPI_PTR(ucsi_acpi_match),
	पूर्ण,
	.probe = ucsi_acpi_probe,
	.हटाओ = ucsi_acpi_हटाओ,
पूर्ण;

module_platक्रमm_driver(ucsi_acpi_platक्रमm_driver);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("UCSI ACPI driver");
