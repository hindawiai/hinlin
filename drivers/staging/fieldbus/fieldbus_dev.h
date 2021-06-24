<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Fieldbus Device Driver Core
 *
 */

#अगर_अघोषित __FIELDBUS_DEV_H
#घोषणा __FIELDBUS_DEV_H

#समावेश <linux/cdev.h>
#समावेश <linux/रुको.h>

क्रमागत fieldbus_dev_type अणु
	FIELDBUS_DEV_TYPE_UNKNOWN = 0,
	FIELDBUS_DEV_TYPE_PROFINET,
पूर्ण;

क्रमागत fieldbus_dev_offl_mode अणु
	FIELDBUS_DEV_OFFL_MODE_CLEAR = 0,
	FIELDBUS_DEV_OFFL_MODE_FREEZE,
	FIELDBUS_DEV_OFFL_MODE_SET
पूर्ण;

/**
 * काष्ठा fieldbus_dev - Fieldbus device
 * @पढ़ो_area:		[DRIVER] function to पढ़ो the process data area of the
 *				 device. same parameters/वापस values as
 *				 the पढ़ो function in काष्ठा file_operations
 * @ग_लिखो_area:		[DRIVER] function to ग_लिखो to the process data area of
 *				 the device. same parameters/वापस values as
 *				 the ग_लिखो function in काष्ठा file_operations
 * @ग_लिखो_area_sz	[DRIVER] size of the writable process data area
 * @पढ़ो_area_sz	[DRIVER] size of the पढ़ोable process data area
 * @card_name		[DRIVER] name of the card, e.g. "ACME Inc. profinet"
 * @fieldbus_type	[DRIVER] fieldbus type of this device, e.g.
 *					FIELDBUS_DEV_TYPE_PROFINET
 * @enable_get		[DRIVER] function which वापसs true अगर the card
 *				 is enabled, false otherwise
 * @fieldbus_id_get	[DRIVER] function to retrieve the unique fieldbus id
 *				 by which this device can be identअगरied;
 *				 वापस value follows the snम_लिखो convention
 * @simple_enable_set	[DRIVER] (optional) function to enable the device
 *				 according to its शेष settings
 * @parent		[DRIVER] (optional) the device's parent device
 */
काष्ठा fieldbus_dev अणु
	sमाप_प्रकार (*पढ़ो_area)(काष्ठा fieldbus_dev *fbdev, अक्षर __user *buf,
			     माप_प्रकार size, loff_t *offset);
	sमाप_प्रकार (*ग_लिखो_area)(काष्ठा fieldbus_dev *fbdev,
			      स्थिर अक्षर __user *buf, माप_प्रकार size,
			      loff_t *offset);
	माप_प्रकार ग_लिखो_area_sz, पढ़ो_area_sz;
	स्थिर अक्षर *card_name;
	क्रमागत fieldbus_dev_type fieldbus_type;
	bool (*enable_get)(काष्ठा fieldbus_dev *fbdev);
	पूर्णांक (*fieldbus_id_get)(काष्ठा fieldbus_dev *fbdev, अक्षर *buf,
			       माप_प्रकार max_size);
	पूर्णांक (*simple_enable_set)(काष्ठा fieldbus_dev *fbdev, bool enable);
	काष्ठा device *parent;

	/* निजी data */
	पूर्णांक id;
	काष्ठा cdev cdev;
	काष्ठा device *dev;
	पूर्णांक dc_event;
	रुको_queue_head_t dc_wq;
	bool online;
पूर्ण;

#अगर IS_ENABLED(CONFIG_FIELDBUS_DEV)

/**
 * fieldbus_dev_unरेजिस्टर()
 *	- unरेजिस्टर a previously रेजिस्टरed fieldbus device
 * @fb:		Device काष्ठाure previously रेजिस्टरed
 **/
व्योम fieldbus_dev_unरेजिस्टर(काष्ठा fieldbus_dev *fb);

/**
 * fieldbus_dev_रेजिस्टर()
 *	- रेजिस्टर a device with the fieldbus device subप्रणाली
 * @fb:		Device काष्ठाure filled by the device driver
 **/
पूर्णांक __must_check fieldbus_dev_रेजिस्टर(काष्ठा fieldbus_dev *fb);

/**
 * fieldbus_dev_area_updated()
 *	- notअगरy the subप्रणाली that an बाह्यal fieldbus controller updated
 *			the process data area
 * @fb:		Device काष्ठाure
 **/
व्योम fieldbus_dev_area_updated(काष्ठा fieldbus_dev *fb);

/**
 * fieldbus_dev_online_changed()
 *	- notअगरy the subप्रणाली that the fieldbus online status changed
 * @fb:		Device काष्ठाure
 **/
व्योम fieldbus_dev_online_changed(काष्ठा fieldbus_dev *fb, bool online);

#अन्यथा /* IS_ENABLED(CONFIG_FIELDBUS_DEV) */

अटल अंतरभूत व्योम fieldbus_dev_unरेजिस्टर(काष्ठा fieldbus_dev *fb) अणुपूर्ण
अटल अंतरभूत पूर्णांक __must_check fieldbus_dev_रेजिस्टर(काष्ठा fieldbus_dev *fb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम fieldbus_dev_area_updated(काष्ठा fieldbus_dev *fb) अणुपूर्ण
अटल अंतरभूत व्योम fieldbus_dev_online_changed(काष्ठा fieldbus_dev *fb,
					       bool online) अणुपूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_FIELDBUS_DEV) */
#पूर्ण_अगर /* __FIELDBUS_DEV_H */
