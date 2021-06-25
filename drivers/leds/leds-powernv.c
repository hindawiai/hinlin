<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV LED Driver
 *
 * Copyright IBM Corp. 2015
 *
 * Author: Vasant Hegde <hegdevasant@linux.vnet.ibm.com>
 * Author: Anshuman Khandual <khandual@linux.vnet.ibm.com>
 */

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/opal.h>

/* Map LED type to description. */
काष्ठा led_type_map अणु
	स्थिर पूर्णांक	type;
	स्थिर अक्षर	*desc;
पूर्ण;
अटल स्थिर काष्ठा led_type_map led_type_map[] = अणु
	अणुOPAL_SLOT_LED_TYPE_ID,		"identify"पूर्ण,
	अणुOPAL_SLOT_LED_TYPE_FAULT,	"fault"पूर्ण,
	अणुOPAL_SLOT_LED_TYPE_ATTN,	"attention"पूर्ण,
	अणु-1,				शून्यपूर्ण,
पूर्ण;

काष्ठा घातernv_led_common अणु
	/*
	 * By शेष unload path resets all the LEDs. But on PowerNV
	 * platक्रमm we want to retain LED state across reboot as these
	 * are controlled by firmware. Also service processor can modअगरy
	 * the LEDs independent of OS. Hence aव्योम resetting LEDs in
	 * unload path.
	 */
	bool		led_disabled;

	/* Max supported LED type */
	__be64		max_led_type;

	/* glabal lock */
	काष्ठा mutex	lock;
पूर्ण;

/* PowerNV LED data */
काष्ठा घातernv_led_data अणु
	काष्ठा led_classdev	cdev;
	अक्षर			*loc_code;	/* LED location code */
	पूर्णांक			led_type;	/* OPAL_SLOT_LED_TYPE_* */

	काष्ठा घातernv_led_common *common;
पूर्ण;


/* Returns OPAL_SLOT_LED_TYPE_* क्रम given led type string */
अटल पूर्णांक घातernv_get_led_type(स्थिर अक्षर *led_type_desc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(led_type_map); i++)
		अगर (!म_भेद(led_type_map[i].desc, led_type_desc))
			वापस led_type_map[i].type;

	वापस -1;
पूर्ण

/*
 * This commits the state change of the requested LED through an OPAL call.
 * This function is called from work queue task context when ever it माला_लो
 * scheduled. This function can sleep at opal_async_रुको_response call.
 */
अटल पूर्णांक घातernv_led_set(काष्ठा घातernv_led_data *घातernv_led,
			    क्रमागत led_brightness value)
अणु
	पूर्णांक rc, token;
	u64 led_mask, led_value = 0;
	__be64 max_type;
	काष्ठा opal_msg msg;
	काष्ठा device *dev = घातernv_led->cdev.dev;
	काष्ठा घातernv_led_common *घातernv_led_common = घातernv_led->common;

	/* Prepare क्रम the OPAL call */
	max_type = घातernv_led_common->max_led_type;
	led_mask = OPAL_SLOT_LED_STATE_ON << घातernv_led->led_type;
	अगर (value)
		led_value = led_mask;

	/* OPAL async call */
	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			dev_err(dev, "%s: Couldn't get OPAL async token\n",
				__func__);
		वापस token;
	पूर्ण

	rc = opal_leds_set_ind(token, घातernv_led->loc_code,
			       led_mask, led_value, &max_type);
	अगर (rc != OPAL_ASYNC_COMPLETION) अणु
		dev_err(dev, "%s: OPAL set LED call failed for %s [rc=%d]\n",
			__func__, घातernv_led->loc_code, rc);
		जाओ out_token;
	पूर्ण

	rc = opal_async_रुको_response(token, &msg);
	अगर (rc) अणु
		dev_err(dev,
			"%s: Failed to wait for the async response [rc=%d]\n",
			__func__, rc);
		जाओ out_token;
	पूर्ण

	rc = opal_get_async_rc(msg);
	अगर (rc != OPAL_SUCCESS)
		dev_err(dev, "%s : OAPL async call returned failed [rc=%d]\n",
			__func__, rc);

out_token:
	opal_async_release_token(token);
	वापस rc;
पूर्ण

/*
 * This function fetches the LED state क्रम a given LED type क्रम
 * mentioned LED classdev काष्ठाure.
 */
अटल क्रमागत led_brightness घातernv_led_get(काष्ठा घातernv_led_data *घातernv_led)
अणु
	पूर्णांक rc;
	__be64 mask, value, max_type;
	u64 led_mask, led_value;
	काष्ठा device *dev = घातernv_led->cdev.dev;
	काष्ठा घातernv_led_common *घातernv_led_common = घातernv_led->common;

	/* Fetch all LED status */
	mask = cpu_to_be64(0);
	value = cpu_to_be64(0);
	max_type = घातernv_led_common->max_led_type;

	rc = opal_leds_get_ind(घातernv_led->loc_code,
			       &mask, &value, &max_type);
	अगर (rc != OPAL_SUCCESS && rc != OPAL_PARTIAL) अणु
		dev_err(dev, "%s: OPAL get led call failed [rc=%d]\n",
			__func__, rc);
		वापस LED_OFF;
	पूर्ण

	led_mask = be64_to_cpu(mask);
	led_value = be64_to_cpu(value);

	/* LED status available */
	अगर (!((led_mask >> घातernv_led->led_type) & OPAL_SLOT_LED_STATE_ON)) अणु
		dev_err(dev, "%s: LED status not available for %s\n",
			__func__, घातernv_led->cdev.name);
		वापस LED_OFF;
	पूर्ण

	/* LED status value */
	अगर ((led_value >> घातernv_led->led_type) & OPAL_SLOT_LED_STATE_ON)
		वापस LED_FULL;

	वापस LED_OFF;
पूर्ण

/*
 * LED classdev 'brightness_get' function. This schedules work
 * to update LED state.
 */
अटल पूर्णांक घातernv_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness value)
अणु
	काष्ठा घातernv_led_data *घातernv_led =
		container_of(led_cdev, काष्ठा घातernv_led_data, cdev);
	काष्ठा घातernv_led_common *घातernv_led_common = घातernv_led->common;
	पूर्णांक rc;

	/* Do not modअगरy LED in unload path */
	अगर (घातernv_led_common->led_disabled)
		वापस 0;

	mutex_lock(&घातernv_led_common->lock);
	rc = घातernv_led_set(घातernv_led, value);
	mutex_unlock(&घातernv_led_common->lock);

	वापस rc;
पूर्ण

/* LED classdev 'brightness_get' function */
अटल क्रमागत led_brightness घातernv_brightness_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा घातernv_led_data *घातernv_led =
		container_of(led_cdev, काष्ठा घातernv_led_data, cdev);

	वापस घातernv_led_get(घातernv_led);
पूर्ण

/*
 * This function रेजिस्टरs classdev काष्ठाure क्रम any given type of LED on
 * a given child LED device node.
 */
अटल पूर्णांक घातernv_led_create(काष्ठा device *dev,
			      काष्ठा घातernv_led_data *घातernv_led,
			      स्थिर अक्षर *led_type_desc)
अणु
	पूर्णांक rc;

	/* Make sure LED type is supported */
	घातernv_led->led_type = घातernv_get_led_type(led_type_desc);
	अगर (घातernv_led->led_type == -1) अणु
		dev_warn(dev, "%s: No support for led type : %s\n",
			 __func__, led_type_desc);
		वापस -EINVAL;
	पूर्ण

	/* Create the name क्रम classdev */
	घातernv_led->cdev.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s:%s",
						घातernv_led->loc_code,
						led_type_desc);
	अगर (!घातernv_led->cdev.name)
		वापस -ENOMEM;

	घातernv_led->cdev.brightness_set_blocking = घातernv_brightness_set;
	घातernv_led->cdev.brightness_get = घातernv_brightness_get;
	घातernv_led->cdev.brightness = LED_OFF;
	घातernv_led->cdev.max_brightness = LED_FULL;

	/* Register the classdev */
	rc = devm_led_classdev_रेजिस्टर(dev, &घातernv_led->cdev);
	अगर (rc) अणु
		dev_err(dev, "%s: Classdev registration failed for %s\n",
			__func__, घातernv_led->cdev.name);
	पूर्ण

	वापस rc;
पूर्ण

/* Go through LED device tree node and रेजिस्टर LED classdev काष्ठाure */
अटल पूर्णांक घातernv_led_classdev(काष्ठा platक्रमm_device *pdev,
				काष्ठा device_node *led_node,
				काष्ठा घातernv_led_common *घातernv_led_common)
अणु
	स्थिर अक्षर *cur = शून्य;
	पूर्णांक rc = -1;
	काष्ठा property *p;
	काष्ठा device_node *np;
	काष्ठा घातernv_led_data *घातernv_led;
	काष्ठा device *dev = &pdev->dev;

	क्रम_each_available_child_of_node(led_node, np) अणु
		p = of_find_property(np, "led-types", शून्य);

		जबतक ((cur = of_prop_next_string(p, cur)) != शून्य) अणु
			घातernv_led = devm_kzalloc(dev, माप(*घातernv_led),
						   GFP_KERNEL);
			अगर (!घातernv_led) अणु
				of_node_put(np);
				वापस -ENOMEM;
			पूर्ण

			घातernv_led->common = घातernv_led_common;
			घातernv_led->loc_code = (अक्षर *)np->name;

			rc = घातernv_led_create(dev, घातernv_led, cur);
			अगर (rc) अणु
				of_node_put(np);
				वापस rc;
			पूर्ण
		पूर्ण /* जबतक end */
	पूर्ण

	वापस rc;
पूर्ण

/* Platक्रमm driver probe */
अटल पूर्णांक घातernv_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *led_node;
	काष्ठा घातernv_led_common *घातernv_led_common;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;

	led_node = of_find_node_by_path("/ibm,opal/leds");
	अगर (!led_node) अणु
		dev_err(dev, "%s: LED parent device node not found\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	घातernv_led_common = devm_kzalloc(dev, माप(*घातernv_led_common),
					  GFP_KERNEL);
	अगर (!घातernv_led_common) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_init(&घातernv_led_common->lock);
	घातernv_led_common->max_led_type = cpu_to_be64(OPAL_SLOT_LED_TYPE_MAX);

	platक्रमm_set_drvdata(pdev, घातernv_led_common);

	rc = घातernv_led_classdev(pdev, led_node, घातernv_led_common);
out:
	of_node_put(led_node);
	वापस rc;
पूर्ण

/* Platक्रमm driver हटाओ */
अटल पूर्णांक घातernv_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातernv_led_common *घातernv_led_common;

	/* Disable LED operation */
	घातernv_led_common = platक्रमm_get_drvdata(pdev);
	घातernv_led_common->led_disabled = true;

	/* Destroy lock */
	mutex_destroy(&घातernv_led_common->lock);

	dev_info(&pdev->dev, "PowerNV led module unregistered\n");
	वापस 0;
पूर्ण

/* Platक्रमm driver property match */
अटल स्थिर काष्ठा of_device_id घातernv_led_match[] = अणु
	अणु
		.compatible	= "ibm,opal-v3-led",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, घातernv_led_match);

अटल काष्ठा platक्रमm_driver घातernv_led_driver = अणु
	.probe	= घातernv_led_probe,
	.हटाओ = घातernv_led_हटाओ,
	.driver = अणु
		.name = "powernv-led-driver",
		.of_match_table = घातernv_led_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(घातernv_led_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PowerNV LED driver");
MODULE_AUTHOR("Vasant Hegde <hegdevasant@linux.vnet.ibm.com>");
