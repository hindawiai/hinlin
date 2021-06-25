<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INT3406 thermal driver क्रम display participant device
 *
 * Copyright (C) 2016, Intel Corporation
 * Authors: Aaron Lu <aaron.lu@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/thermal.h>
#समावेश <acpi/video.h>

#घोषणा INT3406_BRIGHTNESS_LIMITS_CHANGED	0x80

काष्ठा पूर्णांक3406_thermal_data अणु
	पूर्णांक upper_limit;
	पूर्णांक lower_limit;
	acpi_handle handle;
	काष्ठा acpi_video_device_brightness *br;
	काष्ठा backlight_device *raw_bd;
	काष्ठा thermal_cooling_device *cooling_dev;
पूर्ण;

/*
 * According to the ACPI spec,
 * "Each brightness level is represented by a number between 0 and 100,
 * and can be thought of as a percentage. For example, 50 can be 50%
 * घातer consumption or 50% brightness, as defined by the OEM."
 *
 * As पूर्णांक3406 device uses this value to communicate with the native
 * graphics driver, we make the assumption that it represents
 * the percentage of brightness only
 */
#घोषणा ACPI_TO_RAW(v, d) (d->raw_bd->props.max_brightness * v / 100)
#घोषणा RAW_TO_ACPI(v, d) (v * 100 / d->raw_bd->props.max_brightness)

अटल पूर्णांक
पूर्णांक3406_thermal_get_max_state(काष्ठा thermal_cooling_device *cooling_dev,
			      अचिन्हित दीर्घ *state)
अणु
	काष्ठा पूर्णांक3406_thermal_data *d = cooling_dev->devdata;

	*state = d->upper_limit - d->lower_limit;
	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांक3406_thermal_set_cur_state(काष्ठा thermal_cooling_device *cooling_dev,
			      अचिन्हित दीर्घ state)
अणु
	काष्ठा पूर्णांक3406_thermal_data *d = cooling_dev->devdata;
	पूर्णांक acpi_level, raw_level;

	अगर (state > d->upper_limit - d->lower_limit)
		वापस -EINVAL;

	acpi_level = d->br->levels[d->upper_limit - state];

	raw_level = ACPI_TO_RAW(acpi_level, d);

	वापस backlight_device_set_brightness(d->raw_bd, raw_level);
पूर्ण

अटल पूर्णांक
पूर्णांक3406_thermal_get_cur_state(काष्ठा thermal_cooling_device *cooling_dev,
			      अचिन्हित दीर्घ *state)
अणु
	काष्ठा पूर्णांक3406_thermal_data *d = cooling_dev->devdata;
	पूर्णांक acpi_level;
	पूर्णांक index;

	acpi_level = RAW_TO_ACPI(d->raw_bd->props.brightness, d);

	/*
	 * There is no 1:1 mapping between the firmware पूर्णांकerface level
	 * with the raw पूर्णांकerface level, we will have to find one that is
	 * right above it.
	 */
	क्रम (index = d->lower_limit; index < d->upper_limit; index++) अणु
		अगर (acpi_level <= d->br->levels[index])
			अवरोध;
	पूर्ण

	*state = d->upper_limit - index;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops video_cooling_ops = अणु
	.get_max_state = पूर्णांक3406_thermal_get_max_state,
	.get_cur_state = पूर्णांक3406_thermal_get_cur_state,
	.set_cur_state = पूर्णांक3406_thermal_set_cur_state,
पूर्ण;

अटल पूर्णांक पूर्णांक3406_thermal_get_index(पूर्णांक *array, पूर्णांक nr, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 2; i < nr; i++) अणु
		अगर (array[i] == value)
			अवरोध;
	पूर्ण
	वापस i == nr ? -ENOENT : i;
पूर्ण

अटल व्योम पूर्णांक3406_thermal_get_limit(काष्ठा पूर्णांक3406_thermal_data *d)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ lower_limit, upper_limit;

	status = acpi_evaluate_पूर्णांकeger(d->handle, "DDDL", शून्य, &lower_limit);
	अगर (ACPI_SUCCESS(status))
		d->lower_limit = पूर्णांक3406_thermal_get_index(d->br->levels,
					d->br->count, lower_limit);

	status = acpi_evaluate_पूर्णांकeger(d->handle, "DDPC", शून्य, &upper_limit);
	अगर (ACPI_SUCCESS(status))
		d->upper_limit = पूर्णांक3406_thermal_get_index(d->br->levels,
					d->br->count, upper_limit);

	/* lower_limit and upper_limit should be always set */
	d->lower_limit = d->lower_limit > 0 ? d->lower_limit : 2;
	d->upper_limit = d->upper_limit > 0 ? d->upper_limit : d->br->count - 1;
पूर्ण

अटल व्योम पूर्णांक3406_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	अगर (event == INT3406_BRIGHTNESS_LIMITS_CHANGED)
		पूर्णांक3406_thermal_get_limit(data);
पूर्ण

अटल पूर्णांक पूर्णांक3406_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	काष्ठा पूर्णांक3406_thermal_data *d;
	काष्ठा backlight_device *bd;
	पूर्णांक ret;

	अगर (!ACPI_HANDLE(&pdev->dev))
		वापस -ENODEV;

	d = devm_kzalloc(&pdev->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;
	d->handle = ACPI_HANDLE(&pdev->dev);

	bd = backlight_device_get_by_type(BACKLIGHT_RAW);
	अगर (!bd)
		वापस -ENODEV;
	d->raw_bd = bd;

	ret = acpi_video_get_levels(ACPI_COMPANION(&pdev->dev), &d->br, शून्य);
	अगर (ret)
		वापस ret;

	पूर्णांक3406_thermal_get_limit(d);

	d->cooling_dev = thermal_cooling_device_रेजिस्टर(acpi_device_bid(adev),
							 d, &video_cooling_ops);
	अगर (IS_ERR(d->cooling_dev))
		जाओ err;

	ret = acpi_install_notअगरy_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					  पूर्णांक3406_notअगरy, d);
	अगर (ret)
		जाओ err_cdev;

	platक्रमm_set_drvdata(pdev, d);

	वापस 0;

err_cdev:
	thermal_cooling_device_unरेजिस्टर(d->cooling_dev);
err:
	kमुक्त(d->br);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक पूर्णांक3406_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांक3406_thermal_data *d = platक्रमm_get_drvdata(pdev);

	thermal_cooling_device_unरेजिस्टर(d->cooling_dev);
	kमुक्त(d->br);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3406_thermal_match[] = अणु
	अणु"INT3406", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, पूर्णांक3406_thermal_match);

अटल काष्ठा platक्रमm_driver पूर्णांक3406_thermal_driver = अणु
	.probe = पूर्णांक3406_thermal_probe,
	.हटाओ = पूर्णांक3406_thermal_हटाओ,
	.driver = अणु
		   .name = "int3406 thermal",
		   .acpi_match_table = पूर्णांक3406_thermal_match,
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांक3406_thermal_driver);

MODULE_DESCRIPTION("INT3406 Thermal driver");
MODULE_LICENSE("GPL v2");
