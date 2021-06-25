<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensor Time Driver
 * Copyright (c) 2012, Alexander Holler.
 */
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/rtc.h>

क्रमागत hid_समय_channel अणु
	CHANNEL_SCAN_INDEX_YEAR,
	CHANNEL_SCAN_INDEX_MONTH,
	CHANNEL_SCAN_INDEX_DAY,
	CHANNEL_SCAN_INDEX_HOUR,
	CHANNEL_SCAN_INDEX_MINUTE,
	CHANNEL_SCAN_INDEX_SECOND,
	TIME_RTC_CHANNEL_MAX,
पूर्ण;

काष्ठा hid_समय_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info info[TIME_RTC_CHANNEL_MAX];
	काष्ठा rtc_समय last_समय;
	spinlock_t lock_last_समय;
	काष्ठा completion comp_last_समय;
	काष्ठा rtc_समय समय_buf;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल स्थिर u32 hid_समय_addresses[TIME_RTC_CHANNEL_MAX] = अणु
	HID_USAGE_SENSOR_TIME_YEAR,
	HID_USAGE_SENSOR_TIME_MONTH,
	HID_USAGE_SENSOR_TIME_DAY,
	HID_USAGE_SENSOR_TIME_HOUR,
	HID_USAGE_SENSOR_TIME_MINUTE,
	HID_USAGE_SENSOR_TIME_SECOND,
पूर्ण;

/* Channel names क्रम verbose error messages */
अटल स्थिर अक्षर * स्थिर hid_समय_channel_names[TIME_RTC_CHANNEL_MAX] = अणु
	"year", "month", "day", "hour", "minute", "second",
पूर्ण;

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक hid_समय_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id, व्योम *priv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hid_समय_state *समय_state = platक्रमm_get_drvdata(priv);

	spin_lock_irqsave(&समय_state->lock_last_समय, flags);
	समय_state->last_समय = समय_state->समय_buf;
	spin_unlock_irqrestore(&समय_state->lock_last_समय, flags);
	complete(&समय_state->comp_last_समय);
	वापस 0;
पूर्ण

अटल u32 hid_समय_value(माप_प्रकार raw_len, अक्षर *raw_data)
अणु
	चयन (raw_len) अणु
	हाल 1:
		वापस *(u8 *)raw_data;
	हाल 2:
		वापस *(u16 *)raw_data;
	हाल 4:
		वापस *(u32 *)raw_data;
	शेष:
		वापस (u32)(~0U); /* 0xff... or -1 to denote an error */
	पूर्ण
पूर्ण

अटल पूर्णांक hid_समय_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id, माप_प्रकार raw_len,
				अक्षर *raw_data, व्योम *priv)
अणु
	काष्ठा hid_समय_state *समय_state = platक्रमm_get_drvdata(priv);
	काष्ठा rtc_समय *समय_buf = &समय_state->समय_buf;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_TIME_YEAR:
		/*
		 * The draft क्रम HID-sensors (HUTRR39) currently करोesn't define
		 * the range क्रम the year attribute. Thereक्रम we support
		 * 8 bit (0-99) and 16 or 32 bits (full) as size क्रम the year.
		 */
		अगर (raw_len == 1) अणु
			समय_buf->पंचांग_year = *(u8 *)raw_data;
			अगर (समय_buf->पंचांग_year < 70)
				/* assume we are in 1970...2069 */
				समय_buf->पंचांग_year += 100;
		पूर्ण अन्यथा
			समय_buf->पंचांग_year =
				(पूर्णांक)hid_समय_value(raw_len, raw_data)-1900;
		अवरोध;
	हाल HID_USAGE_SENSOR_TIME_MONTH:
		/* sensors are sending the month as 1-12, we need 0-11 */
		समय_buf->पंचांग_mon = (पूर्णांक)hid_समय_value(raw_len, raw_data)-1;
		अवरोध;
	हाल HID_USAGE_SENSOR_TIME_DAY:
		समय_buf->पंचांग_mday = (पूर्णांक)hid_समय_value(raw_len, raw_data);
		अवरोध;
	हाल HID_USAGE_SENSOR_TIME_HOUR:
		समय_buf->पंचांग_hour = (पूर्णांक)hid_समय_value(raw_len, raw_data);
		अवरोध;
	हाल HID_USAGE_SENSOR_TIME_MINUTE:
		समय_buf->पंचांग_min = (पूर्णांक)hid_समय_value(raw_len, raw_data);
		अवरोध;
	हाल HID_USAGE_SENSOR_TIME_SECOND:
		समय_buf->पंचांग_sec = (पूर्णांक)hid_समय_value(raw_len, raw_data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* small helper, haven't found any other way */
अटल स्थिर अक्षर *hid_समय_attrib_name(u32 attrib_id)
अणु
	अटल स्थिर अक्षर unknown[] = "unknown";
	अचिन्हित i;

	क्रम (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i) अणु
		अगर (hid_समय_addresses[i] == attrib_id)
			वापस hid_समय_channel_names[i];
	पूर्ण
	वापस unknown; /* should never happen */
पूर्ण

अटल पूर्णांक hid_समय_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				काष्ठा hid_समय_state *समय_state)
अणु
	पूर्णांक report_id, i;

	क्रम (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i)
		अगर (sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT, usage_id,
				hid_समय_addresses[i],
				&समय_state->info[i]) < 0)
			वापस -EINVAL;
	/* Check the (needed) attributes क्रम sanity */
	report_id = समय_state->info[0].report_id;
	अगर (report_id < 0) अणु
		dev_err(&pdev->dev, "bad report ID!\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i) अणु
		अगर (समय_state->info[i].report_id != report_id) अणु
			dev_err(&pdev->dev,
				"not all needed attributes inside the same report!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (समय_state->info[i].size == 3 ||
				समय_state->info[i].size > 4) अणु
			dev_err(&pdev->dev,
				"attribute '%s' not 8, 16 or 32 bits wide!\n",
				hid_समय_attrib_name(
					समय_state->info[i].attrib_id));
			वापस -EINVAL;
		पूर्ण
		अगर (समय_state->info[i].units !=
				HID_USAGE_SENSOR_UNITS_NOT_SPECIFIED &&
				/* allow attribute seconds with unit seconds */
				!(समय_state->info[i].attrib_id ==
				HID_USAGE_SENSOR_TIME_SECOND &&
				समय_state->info[i].units ==
				HID_USAGE_SENSOR_UNITS_SECOND)) अणु
			dev_err(&pdev->dev,
				"attribute '%s' hasn't a unit of type 'none'!\n",
				hid_समय_attrib_name(
					समय_state->info[i].attrib_id));
			वापस -EINVAL;
		पूर्ण
		अगर (समय_state->info[i].unit_expo) अणु
			dev_err(&pdev->dev,
				"attribute '%s' hasn't a unit exponent of 1!\n",
				hid_समय_attrib_name(
					समय_state->info[i].attrib_id));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hid_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hid_समय_state *समय_state = dev_get_drvdata(dev);
	पूर्णांक ret;

	reinit_completion(&समय_state->comp_last_समय);
	/* get a report with all values through requesting one value */
	sensor_hub_input_attr_get_raw_value(समय_state->common_attributes.hsdev,
			HID_USAGE_SENSOR_TIME, hid_समय_addresses[0],
			समय_state->info[0].report_id, SENSOR_HUB_SYNC, false);
	/* रुको क्रम all values (event) */
	ret = रुको_क्रम_completion_समाप्तable_समयout(
			&समय_state->comp_last_समय, HZ*6);
	अगर (ret > 0) अणु
		/* no error */
		spin_lock_irqsave(&समय_state->lock_last_समय, flags);
		*पंचांग = समय_state->last_समय;
		spin_unlock_irqrestore(&समय_state->lock_last_समय, flags);
		वापस 0;
	पूर्ण
	अगर (!ret)
		वापस -EIO; /* समयouted */
	वापस ret; /* समाप्तed (-ERESTARTSYS) */
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops hid_समय_rtc_ops = अणु
	.पढ़ो_समय = hid_rtc_पढ़ो_समय,
पूर्ण;

अटल पूर्णांक hid_समय_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);
	काष्ठा hid_समय_state *समय_state = devm_kzalloc(&pdev->dev,
		माप(काष्ठा hid_समय_state), GFP_KERNEL);

	अगर (समय_state == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, समय_state);

	spin_lock_init(&समय_state->lock_last_समय);
	init_completion(&समय_state->comp_last_समय);
	समय_state->common_attributes.hsdev = hsdev;
	समय_state->common_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
				HID_USAGE_SENSOR_TIME,
				&समय_state->common_attributes,
				शून्य,
				0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes!\n");
		वापस ret;
	पूर्ण

	ret = hid_समय_parse_report(pdev, hsdev, HID_USAGE_SENSOR_TIME,
					समय_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes!\n");
		वापस ret;
	पूर्ण

	समय_state->callbacks.send_event = hid_समय_proc_event;
	समय_state->callbacks.capture_sample = hid_समय_capture_sample;
	समय_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, HID_USAGE_SENSOR_TIME,
					&समय_state->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "register callback failed!\n");
		वापस ret;
	पूर्ण

	ret = sensor_hub_device_खोलो(hsdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to open sensor hub device!\n");
		जाओ err_खोलो;
	पूर्ण

	/*
	 * Enable HID input processing early in order to be able to पढ़ो the
	 * घड़ी alपढ़ोy in devm_rtc_device_रेजिस्टर().
	 */
	hid_device_io_start(hsdev->hdev);

	समय_state->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev,
					"hid-sensor-time", &hid_समय_rtc_ops,
					THIS_MODULE);

	अगर (IS_ERR(समय_state->rtc)) अणु
		hid_device_io_stop(hsdev->hdev);
		ret = PTR_ERR(समय_state->rtc);
		समय_state->rtc = शून्य;
		dev_err(&pdev->dev, "rtc device register failed!\n");
		जाओ err_rtc;
	पूर्ण

	वापस ret;

err_rtc:
	sensor_hub_device_बंद(hsdev);
err_खोलो:
	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_TIME);
	वापस ret;
पूर्ण

अटल पूर्णांक hid_समय_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);

	sensor_hub_device_बंद(hsdev);
	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_TIME);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_समय_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-2000a0",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_समय_ids);

अटल काष्ठा platक्रमm_driver hid_समय_platक्रमm_driver = अणु
	.id_table = hid_समय_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= hid_समय_probe,
	.हटाओ		= hid_समय_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_समय_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Time");
MODULE_AUTHOR("Alexander Holler <holler@ahsoftware.de>");
MODULE_LICENSE("GPL");
