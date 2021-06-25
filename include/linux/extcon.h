<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * External Connector (extcon) framework
 * - linux/include/linux/extcon.h क्रम extcon consumer device driver.
 *
 * Copyright (C) 2015 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * Copyright (C) 2012 Samsung Electronics
 * Author: Donggeun Kim <dg77.kim@samsung.com>
 * Author: MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * based on चयन class driver
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 */

#अगर_अघोषित __LINUX_EXTCON_H__
#घोषणा __LINUX_EXTCON_H__

#समावेश <linux/device.h>

/*
 * Define the type of supported बाह्यal connectors
 */
#घोषणा EXTCON_TYPE_USB		BIT(0)	/* USB connector */
#घोषणा EXTCON_TYPE_CHG		BIT(1)	/* Charger connector */
#घोषणा EXTCON_TYPE_JACK	BIT(2)	/* Jack connector */
#घोषणा EXTCON_TYPE_DISP	BIT(3)	/* Display connector */
#घोषणा EXTCON_TYPE_MISC	BIT(4)	/* Miscellaneous connector */

/*
 * Define the unique id of supported बाह्यal connectors
 */
#घोषणा EXTCON_NONE		0

/* USB बाह्यal connector */
#घोषणा EXTCON_USB		1
#घोषणा EXTCON_USB_HOST		2

/*
 * Charging बाह्यal connector
 *
 * When one SDP अक्षरger connector was reported, we should also report
 * the USB connector, which means EXTCON_CHG_USB_SDP should always
 * appear together with EXTCON_USB. The same as ACA अक्षरger connector,
 * EXTCON_CHG_USB_ACA would normally appear with EXTCON_USB_HOST.
 *
 * The EXTCON_CHG_USB_SLOW connector can provide at least 500mA of
 * current at 5V. The EXTCON_CHG_USB_FAST connector can provide at
 * least 1A of current at 5V.
 */
#घोषणा EXTCON_CHG_USB_SDP	5	/* Standard Downstream Port */
#घोषणा EXTCON_CHG_USB_DCP	6	/* Dedicated Charging Port */
#घोषणा EXTCON_CHG_USB_CDP	7	/* Charging Downstream Port */
#घोषणा EXTCON_CHG_USB_ACA	8	/* Accessory Charger Adapter */
#घोषणा EXTCON_CHG_USB_FAST	9
#घोषणा EXTCON_CHG_USB_SLOW	10
#घोषणा EXTCON_CHG_WPT		11	/* Wireless Power Transfer */
#घोषणा EXTCON_CHG_USB_PD	12	/* USB Power Delivery */

/* Jack बाह्यal connector */
#घोषणा EXTCON_JACK_MICROPHONE	20
#घोषणा EXTCON_JACK_HEADPHONE	21
#घोषणा EXTCON_JACK_LINE_IN	22
#घोषणा EXTCON_JACK_LINE_OUT	23
#घोषणा EXTCON_JACK_VIDEO_IN	24
#घोषणा EXTCON_JACK_VIDEO_OUT	25
#घोषणा EXTCON_JACK_SPDIF_IN	26	/* Sony Philips Digital InterFace */
#घोषणा EXTCON_JACK_SPDIF_OUT	27

/* Display बाह्यal connector */
#घोषणा EXTCON_DISP_HDMI	40	/* High-Definition Mulसमयdia Interface */
#घोषणा EXTCON_DISP_MHL		41	/* Mobile High-Definition Link */
#घोषणा EXTCON_DISP_DVI		42	/* Digital Visual Interface */
#घोषणा EXTCON_DISP_VGA		43	/* Video Graphics Array */
#घोषणा EXTCON_DISP_DP		44	/* Display Port */
#घोषणा EXTCON_DISP_HMD		45	/* Head-Mounted Display */

/* Miscellaneous बाह्यal connector */
#घोषणा EXTCON_DOCK		60
#घोषणा EXTCON_JIG		61
#घोषणा EXTCON_MECHANICAL	62

#घोषणा EXTCON_NUM		63

/*
 * Define the properties of supported बाह्यal connectors.
 *
 * When adding the new extcon property, they *must* have
 * the type/value/शेष inक्रमmation. Also, you *have to*
 * modअगरy the EXTCON_PROP_[type]_START/END definitions
 * which mean the range of the supported properties
 * क्रम each extcon type.
 *
 * The naming style of property
 * : EXTCON_PROP_[type]_[property name]
 *
 * EXTCON_PROP_USB_[property name]	: USB property
 * EXTCON_PROP_CHG_[property name]	: Charger property
 * EXTCON_PROP_JACK_[property name]	: Jack property
 * EXTCON_PROP_DISP_[property name]	: Display property
 */

/*
 * Properties of EXTCON_TYPE_USB.
 *
 * - EXTCON_PROP_USB_VBUS
 * @type:	पूर्णांकeger (पूर्णांकval)
 * @value:	0 (low) or 1 (high)
 * @शेष:	0 (low)
 * - EXTCON_PROP_USB_TYPEC_POLARITY
 * @type:	पूर्णांकeger (पूर्णांकval)
 * @value:	0 (normal) or 1 (flip)
 * @शेष:	0 (normal)
 * - EXTCON_PROP_USB_SS (SuperSpeed)
 * @type:       पूर्णांकeger (पूर्णांकval)
 * @value:      0 (USB/USB2) or 1 (USB3)
 * @शेष:    0 (USB/USB2)
 *
 */
#घोषणा EXTCON_PROP_USB_VBUS		0
#घोषणा EXTCON_PROP_USB_TYPEC_POLARITY	1
#घोषणा EXTCON_PROP_USB_SS		2

#घोषणा EXTCON_PROP_USB_MIN		0
#घोषणा EXTCON_PROP_USB_MAX		2
#घोषणा EXTCON_PROP_USB_CNT	(EXTCON_PROP_USB_MAX - EXTCON_PROP_USB_MIN + 1)

/* Properties of EXTCON_TYPE_CHG. */
#घोषणा EXTCON_PROP_CHG_MIN		50
#घोषणा EXTCON_PROP_CHG_MAX		50
#घोषणा EXTCON_PROP_CHG_CNT	(EXTCON_PROP_CHG_MAX - EXTCON_PROP_CHG_MIN + 1)

/* Properties of EXTCON_TYPE_JACK. */
#घोषणा EXTCON_PROP_JACK_MIN		100
#घोषणा EXTCON_PROP_JACK_MAX		100
#घोषणा EXTCON_PROP_JACK_CNT (EXTCON_PROP_JACK_MAX - EXTCON_PROP_JACK_MIN + 1)

/*
 * Properties of EXTCON_TYPE_DISP.
 *
 * - EXTCON_PROP_DISP_HPD (Hot Plug Detect)
 * @type:       पूर्णांकeger (पूर्णांकval)
 * @value:      0 (no hpd) or 1 (hpd)
 * @शेष:    0 (no hpd)
 *
 */
#घोषणा EXTCON_PROP_DISP_HPD		150

/* Properties of EXTCON_TYPE_DISP. */
#घोषणा EXTCON_PROP_DISP_MIN		150
#घोषणा EXTCON_PROP_DISP_MAX		151
#घोषणा EXTCON_PROP_DISP_CNT (EXTCON_PROP_DISP_MAX - EXTCON_PROP_DISP_MIN + 1)

/*
 * Define the type of property's value.
 *
 * Define the property's value as जोड़ type. Because each property
 * would need the dअगरferent data type to store it.
 */
जोड़ extcon_property_value अणु
	पूर्णांक पूर्णांकval;	/* type : पूर्णांकeger (पूर्णांकval) */
पूर्ण;

काष्ठा extcon_dev;

#अगर IS_ENABLED(CONFIG_EXTCON)
/*
 * Following APIs get the connected state of each बाह्यal connector.
 * The 'id' argument indicates the defined बाह्यal connector.
 */
पूर्णांक extcon_get_state(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id);

/*
 * Following APIs get the property of each बाह्यal connector.
 * The 'id' argument indicates the defined बाह्यal connector
 * and the 'prop' indicates the extcon property.
 *
 * And extcon_get_property_capability() get the capability of the property
 * क्रम each बाह्यal connector. They are used to get the capability of the
 * property of each बाह्यal connector based on the id and property.
 */
पूर्णांक extcon_get_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value *prop_val);
पूर्णांक extcon_get_property_capability(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop);

/*
 * Following APIs रेजिस्टर the notअगरier block in order to detect
 * the change of both state and property value क्रम each बाह्यal connector.
 *
 * extcon_रेजिस्टर_notअगरier(*edev, id, *nb) : Register a notअगरier block
 *			क्रम specअगरic बाह्यal connector of the extcon.
 * extcon_रेजिस्टर_notअगरier_all(*edev, *nb) : Register a notअगरier block
 *			क्रम all supported बाह्यal connectors of the extcon.
 */
पूर्णांक extcon_रेजिस्टर_notअगरier(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb);
पूर्णांक extcon_unरेजिस्टर_notअगरier(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb);
पूर्णांक devm_extcon_रेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb);
व्योम devm_extcon_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb);

पूर्णांक extcon_रेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb);
पूर्णांक extcon_unरेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb);
पूर्णांक devm_extcon_रेजिस्टर_notअगरier_all(काष्ठा device *dev,
				काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb);
व्योम devm_extcon_unरेजिस्टर_notअगरier_all(काष्ठा device *dev,
				काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb);

/*
 * Following APIs get the extcon_dev from devicetree or by through extcon name.
 */
काष्ठा extcon_dev *extcon_get_extcon_dev(स्थिर अक्षर *extcon_name);
काष्ठा extcon_dev *extcon_find_edev_by_node(काष्ठा device_node *node);
काष्ठा extcon_dev *extcon_get_edev_by_phandle(काष्ठा device *dev,
						     पूर्णांक index);

/* Following API get the name of extcon device. */
स्थिर अक्षर *extcon_get_edev_name(काष्ठा extcon_dev *edev);

#अन्यथा /* CONFIG_EXTCON */
अटल अंतरभूत पूर्णांक extcon_get_state(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_get_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value *prop_val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_get_property_capability(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_रेजिस्टर_notअगरier(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_unरेजिस्टर_notअगरier(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_extcon_रेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत  व्योम devm_extcon_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb) अणु पूर्ण

अटल अंतरभूत पूर्णांक extcon_रेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
					       काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_unरेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
						 काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_extcon_रेजिस्टर_notअगरier_all(काष्ठा device *dev,
						    काष्ठा extcon_dev *edev,
						    काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_extcon_unरेजिस्टर_notअगरier_all(काष्ठा device *dev,
						       काष्ठा extcon_dev *edev,
						       काष्ठा notअगरier_block *nb) अणु पूर्ण

अटल अंतरभूत काष्ठा extcon_dev *extcon_get_extcon_dev(स्थिर अक्षर *extcon_name)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा extcon_dev *extcon_find_edev_by_node(काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा extcon_dev *extcon_get_edev_by_phandle(काष्ठा device *dev,
				पूर्णांक index)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *extcon_get_edev_name(काष्ठा extcon_dev *edev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_EXTCON */

/*
 * Following काष्ठाure and API are deprecated. EXTCON reमुख्यs the function
 * definition to prevent the build अवरोध.
 */
काष्ठा extcon_specअगरic_cable_nb अणु
       काष्ठा notअगरier_block *user_nb;
       पूर्णांक cable_index;
       काष्ठा extcon_dev *edev;
       अचिन्हित दीर्घ previous_value;
पूर्ण;

अटल अंतरभूत पूर्णांक extcon_रेजिस्टर_पूर्णांकerest(काष्ठा extcon_specअगरic_cable_nb *obj,
				स्थिर अक्षर *extcon_name, स्थिर अक्षर *cable_name,
				काष्ठा notअगरier_block *nb)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_unरेजिस्टर_पूर्णांकerest(काष्ठा extcon_specअगरic_cable_nb *obj)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* __LINUX_EXTCON_H__ */
