<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * nzxt-kraken2.c - hwmon driver क्रम NZXT Kraken X42/X52/X62/X72 coolers
 *
 * The device asynchronously sends HID reports (with id 0x04) twice a second to
 * communicate current fan speed, pump speed and coolant temperature.  The
 * device करोes not respond to Get_Report requests क्रम this status report.
 *
 * Copyright 2019-2021  Jonas Malaco <jonas@protocubo.io>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/hid.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>

#घोषणा STATUS_REPORT_ID	0x04
#घोषणा STATUS_VALIDITY		2 /* seconds; equivalent to 4 missed updates */

अटल स्थिर अक्षर *स्थिर kraken2_temp_label[] = अणु
	"Coolant",
पूर्ण;

अटल स्थिर अक्षर *स्थिर kraken2_fan_label[] = अणु
	"Fan",
	"Pump",
पूर्ण;

काष्ठा kraken2_priv_data अणु
	काष्ठा hid_device *hid_dev;
	काष्ठा device *hwmon_dev;
	s32 temp_input[1];
	u16 fan_input[2];
	अचिन्हित दीर्घ updated; /* jअगरfies */
पूर्ण;

अटल umode_t kraken2_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल पूर्णांक kraken2_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा kraken2_priv_data *priv = dev_get_drvdata(dev);

	अगर (समय_after(jअगरfies, priv->updated + STATUS_VALIDITY * HZ))
		वापस -ENODATA;

	चयन (type) अणु
	हाल hwmon_temp:
		*val = priv->temp_input[channel];
		अवरोध;
	हाल hwmon_fan:
		*val = priv->fan_input[channel];
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP; /* unreachable */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kraken2_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		*str = kraken2_temp_label[channel];
		अवरोध;
	हाल hwmon_fan:
		*str = kraken2_fan_label[channel];
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP; /* unreachable */
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops kraken2_hwmon_ops = अणु
	.is_visible = kraken2_is_visible,
	.पढ़ो = kraken2_पढ़ो,
	.पढ़ो_string = kraken2_पढ़ो_string,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *kraken2_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_LABEL,
			   HWMON_F_INPUT | HWMON_F_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info kraken2_chip_info = अणु
	.ops = &kraken2_hwmon_ops,
	.info = kraken2_info,
पूर्ण;

अटल पूर्णांक kraken2_raw_event(काष्ठा hid_device *hdev,
			     काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा kraken2_priv_data *priv;

	अगर (size < 7 || report->id != STATUS_REPORT_ID)
		वापस 0;

	priv = hid_get_drvdata(hdev);

	/*
	 * The fractional byte of the coolant temperature has been observed to
	 * be in the पूर्णांकerval [1,9], but some of these steps are also
	 * consistently skipped क्रम certain पूर्णांकeger parts.
	 *
	 * For the lack of a better idea, assume that the resolution is 0.1तओC,
	 * and that the missing steps are artअगरacts of how the firmware
	 * processes the raw sensor data.
	 */
	priv->temp_input[0] = data[1] * 1000 + data[2] * 100;

	priv->fan_input[0] = get_unaligned_be16(data + 3);
	priv->fan_input[1] = get_unaligned_be16(data + 5);

	priv->updated = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक kraken2_probe(काष्ठा hid_device *hdev,
			 स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा kraken2_priv_data *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&hdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->hid_dev = hdev;
	hid_set_drvdata(hdev, priv);

	/*
	 * Initialize ->updated to STATUS_VALIDITY seconds in the past, making
	 * the initial empty data invalid क्रम kraken2_पढ़ो without the need क्रम
	 * a special हाल there.
	 */
	priv->updated = jअगरfies - STATUS_VALIDITY * HZ;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hid parse failed with %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Enable hidraw so existing user-space tools can जारी to work.
	 */
	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "hid hw start failed with %d\n", ret);
		जाओ fail_and_stop;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hid hw open failed with %d\n", ret);
		जाओ fail_and_बंद;
	पूर्ण

	priv->hwmon_dev = hwmon_device_रेजिस्टर_with_info(&hdev->dev, "kraken2",
							  priv, &kraken2_chip_info,
							  शून्य);
	अगर (IS_ERR(priv->hwmon_dev)) अणु
		ret = PTR_ERR(priv->hwmon_dev);
		hid_err(hdev, "hwmon registration failed with %d\n", ret);
		जाओ fail_and_बंद;
	पूर्ण

	वापस 0;

fail_and_बंद:
	hid_hw_बंद(hdev);
fail_and_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम kraken2_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा kraken2_priv_data *priv = hid_get_drvdata(hdev);

	hwmon_device_unरेजिस्टर(priv->hwmon_dev);

	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id kraken2_table[] = अणु
	अणु HID_USB_DEVICE(0x1e71, 0x170e) पूर्ण, /* NZXT Kraken X42/X52/X62/X72 */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, kraken2_table);

अटल काष्ठा hid_driver kraken2_driver = अणु
	.name = "nzxt-kraken2",
	.id_table = kraken2_table,
	.probe = kraken2_probe,
	.हटाओ = kraken2_हटाओ,
	.raw_event = kraken2_raw_event,
पूर्ण;

अटल पूर्णांक __init kraken2_init(व्योम)
अणु
	वापस hid_रेजिस्टर_driver(&kraken2_driver);
पूर्ण

अटल व्योम __निकास kraken2_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&kraken2_driver);
पूर्ण

/*
 * When compiled पूर्णांकo the kernel, initialize after the hid bus.
 */
late_initcall(kraken2_init);
module_निकास(kraken2_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonas Malaco <jonas@protocubo.io>");
MODULE_DESCRIPTION("Hwmon driver for NZXT Kraken X42/X52/X62/X72 coolers");
