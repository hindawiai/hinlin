<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * External Connector (extcon) framework
 * - linux/include/linux/extcon-provider.h क्रम extcon provider device driver.
 *
 * Copyright (C) 2017 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 */

#अगर_अघोषित __LINUX_EXTCON_PROVIDER_H__
#घोषणा __LINUX_EXTCON_PROVIDER_H__

#समावेश <linux/extcon.h>

काष्ठा extcon_dev;

#अगर IS_ENABLED(CONFIG_EXTCON)

/* Following APIs रेजिस्टर/unरेजिस्टर the extcon device. */
पूर्णांक extcon_dev_रेजिस्टर(काष्ठा extcon_dev *edev);
व्योम extcon_dev_unरेजिस्टर(काष्ठा extcon_dev *edev);
पूर्णांक devm_extcon_dev_रेजिस्टर(काष्ठा device *dev,
				काष्ठा extcon_dev *edev);
व्योम devm_extcon_dev_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा extcon_dev *edev);

/* Following APIs allocate/मुक्त the memory of the extcon device. */
काष्ठा extcon_dev *extcon_dev_allocate(स्थिर अचिन्हित पूर्णांक *cable);
व्योम extcon_dev_मुक्त(काष्ठा extcon_dev *edev);
काष्ठा extcon_dev *devm_extcon_dev_allocate(काष्ठा device *dev,
				स्थिर अचिन्हित पूर्णांक *cable);
व्योम devm_extcon_dev_मुक्त(काष्ठा device *dev, काष्ठा extcon_dev *edev);

/* Synchronize the state and property value क्रम each बाह्यal connector. */
पूर्णांक extcon_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id);

/*
 * Following APIs set the connected state of each बाह्यal connector.
 * The 'id' argument indicates the defined बाह्यal connector.
 */
पूर्णांक extcon_set_state(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				bool state);
पूर्णांक extcon_set_state_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				bool state);

/*
 * Following APIs set the property of each बाह्यal connector.
 * The 'id' argument indicates the defined बाह्यal connector
 * and the 'prop' indicates the extcon property.
 *
 * And extcon_set_property_capability() set the capability of the property
 * क्रम each बाह्यal connector. They are used to set the capability of the
 * property of each बाह्यal connector based on the id and property.
 */
पूर्णांक extcon_set_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val);
पूर्णांक extcon_set_property_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val);
पूर्णांक extcon_set_property_capability(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop);

#अन्यथा /* CONFIG_EXTCON */
अटल अंतरभूत पूर्णांक extcon_dev_रेजिस्टर(काष्ठा extcon_dev *edev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम extcon_dev_unरेजिस्टर(काष्ठा extcon_dev *edev) अणु पूर्ण

अटल अंतरभूत पूर्णांक devm_extcon_dev_रेजिस्टर(काष्ठा device *dev,
				काष्ठा extcon_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम devm_extcon_dev_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा extcon_dev *edev) अणु पूर्ण

अटल अंतरभूत काष्ठा extcon_dev *extcon_dev_allocate(स्थिर अचिन्हित पूर्णांक *cable)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम extcon_dev_मुक्त(काष्ठा extcon_dev *edev) अणु पूर्ण

अटल अंतरभूत काष्ठा extcon_dev *devm_extcon_dev_allocate(काष्ठा device *dev,
				स्थिर अचिन्हित पूर्णांक *cable)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम devm_extcon_dev_मुक्त(काष्ठा extcon_dev *edev) अणु पूर्ण


अटल अंतरभूत पूर्णांक extcon_set_state(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				bool state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_set_state_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				bool state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_set_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_set_property_sync(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक extcon_set_property_capability(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_EXTCON */
#पूर्ण_अगर /* __LINUX_EXTCON_PROVIDER_H__ */
