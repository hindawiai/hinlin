<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI INT3403 thermal driver
 * Copyright (c) 2013, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "int340x_thermal_zone.h"

#घोषणा INT3403_TYPE_SENSOR		0x03
#घोषणा INT3403_TYPE_CHARGER		0x0B
#घोषणा INT3403_TYPE_BATTERY		0x0C
#घोषणा INT3403_PERF_CHANGED_EVENT	0x80
#घोषणा INT3403_PERF_TRIP_POINT_CHANGED	0x81
#घोषणा INT3403_THERMAL_EVENT		0x90

/* Preserved काष्ठाure क्रम future expandbility */
काष्ठा पूर्णांक3403_sensor अणु
	काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक340x_zone;
पूर्ण;

काष्ठा पूर्णांक3403_perक्रमmance_state अणु
	u64 perक्रमmance;
	u64 घातer;
	u64 latency;
	u64 linear;
	u64 control;
	u64 raw_perक्रमmace;
	अक्षर *raw_unit;
	पूर्णांक reserved;
पूर्ण;

काष्ठा पूर्णांक3403_cdev अणु
	काष्ठा thermal_cooling_device *cdev;
	अचिन्हित दीर्घ max_state;
पूर्ण;

काष्ठा पूर्णांक3403_priv अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा acpi_device *adev;
	अचिन्हित दीर्घ दीर्घ type;
	व्योम *priv;
पूर्ण;

अटल व्योम पूर्णांक3403_notअगरy(acpi_handle handle,
		u32 event, व्योम *data)
अणु
	काष्ठा पूर्णांक3403_priv *priv = data;
	काष्ठा पूर्णांक3403_sensor *obj;

	अगर (!priv)
		वापस;

	obj = priv->priv;
	अगर (priv->type != INT3403_TYPE_SENSOR || !obj)
		वापस;

	चयन (event) अणु
	हाल INT3403_PERF_CHANGED_EVENT:
		अवरोध;
	हाल INT3403_THERMAL_EVENT:
		पूर्णांक340x_thermal_zone_device_update(obj->पूर्णांक340x_zone,
						   THERMAL_TRIP_VIOLATED);
		अवरोध;
	हाल INT3403_PERF_TRIP_POINT_CHANGED:
		पूर्णांक340x_thermal_पढ़ो_trips(obj->पूर्णांक340x_zone);
		पूर्णांक340x_thermal_zone_device_update(obj->पूर्णांक340x_zone,
						   THERMAL_TRIP_CHANGED);
		अवरोध;
	शेष:
		dev_dbg(&priv->pdev->dev, "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांक3403_sensor_add(काष्ठा पूर्णांक3403_priv *priv)
अणु
	पूर्णांक result = 0;
	काष्ठा पूर्णांक3403_sensor *obj;

	obj = devm_kzalloc(&priv->pdev->dev, माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	priv->priv = obj;

	obj->पूर्णांक340x_zone = पूर्णांक340x_thermal_zone_add(priv->adev, शून्य);
	अगर (IS_ERR(obj->पूर्णांक340x_zone))
		वापस PTR_ERR(obj->पूर्णांक340x_zone);

	result = acpi_install_notअगरy_handler(priv->adev->handle,
			ACPI_DEVICE_NOTIFY, पूर्णांक3403_notअगरy,
			(व्योम *)priv);
	अगर (result)
		जाओ err_मुक्त_obj;

	वापस 0;

 err_मुक्त_obj:
	पूर्णांक340x_thermal_zone_हटाओ(obj->पूर्णांक340x_zone);
	वापस result;
पूर्ण

अटल पूर्णांक पूर्णांक3403_sensor_हटाओ(काष्ठा पूर्णांक3403_priv *priv)
अणु
	काष्ठा पूर्णांक3403_sensor *obj = priv->priv;

	acpi_हटाओ_notअगरy_handler(priv->adev->handle,
				   ACPI_DEVICE_NOTIFY, पूर्णांक3403_notअगरy);
	पूर्णांक340x_thermal_zone_हटाओ(obj->पूर्णांक340x_zone);

	वापस 0;
पूर्ण

/* INT3403 Cooling devices */
अटल पूर्णांक पूर्णांक3403_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा पूर्णांक3403_priv *priv = cdev->devdata;
	काष्ठा पूर्णांक3403_cdev *obj = priv->priv;

	*state = obj->max_state;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक3403_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा पूर्णांक3403_priv *priv = cdev->devdata;
	अचिन्हित दीर्घ दीर्घ level;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(priv->adev->handle, "PPPC", शून्य, &level);
	अगर (ACPI_SUCCESS(status)) अणु
		*state = level;
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक
पूर्णांक3403_set_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ state)
अणु
	काष्ठा पूर्णांक3403_priv *priv = cdev->devdata;
	acpi_status status;

	status = acpi_execute_simple_method(priv->adev->handle, "SPPC", state);
	अगर (ACPI_SUCCESS(status))
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops पूर्णांक3403_cooling_ops = अणु
	.get_max_state = पूर्णांक3403_get_max_state,
	.get_cur_state = पूर्णांक3403_get_cur_state,
	.set_cur_state = पूर्णांक3403_set_cur_state,
पूर्ण;

अटल पूर्णांक पूर्णांक3403_cdev_add(काष्ठा पूर्णांक3403_priv *priv)
अणु
	पूर्णांक result = 0;
	acpi_status status;
	काष्ठा पूर्णांक3403_cdev *obj;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *p;

	obj = devm_kzalloc(&priv->pdev->dev, माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	status = acpi_evaluate_object(priv->adev->handle, "PPSS", शून्य, &buf);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	p = buf.poपूर्णांकer;
	अगर (!p || (p->type != ACPI_TYPE_PACKAGE)) अणु
		pr_warn("Invalid PPSS data\n");
		kमुक्त(buf.poपूर्णांकer);
		वापस -EFAULT;
	पूर्ण

	priv->priv = obj;
	obj->max_state = p->package.count - 1;
	obj->cdev =
		thermal_cooling_device_रेजिस्टर(acpi_device_bid(priv->adev),
				priv, &पूर्णांक3403_cooling_ops);
	अगर (IS_ERR(obj->cdev))
		result = PTR_ERR(obj->cdev);

	kमुक्त(buf.poपूर्णांकer);
	/* TODO: add ACPI notअगरication support */

	वापस result;
पूर्ण

अटल पूर्णांक पूर्णांक3403_cdev_हटाओ(काष्ठा पूर्णांक3403_priv *priv)
अणु
	काष्ठा पूर्णांक3403_cdev *obj = priv->priv;

	thermal_cooling_device_unरेजिस्टर(obj->cdev);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक3403_add(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांक3403_priv *priv;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	acpi_status status;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा पूर्णांक3403_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdev = pdev;
	priv->adev = ACPI_COMPANION(&(pdev->dev));
	अगर (!priv->adev) अणु
		result = -EINVAL;
		जाओ err;
	पूर्ण


	status = acpi_evaluate_पूर्णांकeger(priv->adev->handle, "_TMP",
				       शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status)) अणु
		status = acpi_evaluate_पूर्णांकeger(priv->adev->handle, "PTYP",
				       शून्य, &priv->type);
		अगर (ACPI_FAILURE(status)) अणु
			result = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->type = INT3403_TYPE_SENSOR;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	चयन (priv->type) अणु
	हाल INT3403_TYPE_SENSOR:
		result = पूर्णांक3403_sensor_add(priv);
		अवरोध;
	हाल INT3403_TYPE_CHARGER:
	हाल INT3403_TYPE_BATTERY:
		result = पूर्णांक3403_cdev_add(priv);
		अवरोध;
	शेष:
		result = -EINVAL;
	पूर्ण

	अगर (result)
		जाओ err;
	वापस result;

err:
	वापस result;
पूर्ण

अटल पूर्णांक पूर्णांक3403_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांक3403_priv *priv = platक्रमm_get_drvdata(pdev);

	चयन (priv->type) अणु
	हाल INT3403_TYPE_SENSOR:
		पूर्णांक3403_sensor_हटाओ(priv);
		अवरोध;
	हाल INT3403_TYPE_CHARGER:
	हाल INT3403_TYPE_BATTERY:
		पूर्णांक3403_cdev_हटाओ(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3403_device_ids[] = अणु
	अणु"INT3403", 0पूर्ण,
	अणु"INTC1043", 0पूर्ण,
	अणु"INTC1046", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांक3403_device_ids);

अटल काष्ठा platक्रमm_driver पूर्णांक3403_driver = अणु
	.probe = पूर्णांक3403_add,
	.हटाओ = पूर्णांक3403_हटाओ,
	.driver = अणु
		.name = "int3403 thermal",
		.acpi_match_table = पूर्णांक3403_device_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांक3403_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ACPI INT3403 thermal driver");
