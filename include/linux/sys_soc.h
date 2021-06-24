<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2011
 * Author: Lee Jones <lee.jones@linaro.org> क्रम ST-Ericsson.
 */
#अगर_अघोषित __SOC_BUS_H
#घोषणा __SOC_BUS_H

#समावेश <linux/device.h>

काष्ठा soc_device_attribute अणु
	स्थिर अक्षर *machine;
	स्थिर अक्षर *family;
	स्थिर अक्षर *revision;
	स्थिर अक्षर *serial_number;
	स्थिर अक्षर *soc_id;
	स्थिर व्योम *data;
	स्थिर काष्ठा attribute_group *custom_attr_group;
पूर्ण;

/**
 * soc_device_रेजिस्टर - रेजिस्टर SoC as a device
 * @soc_plat_dev_attr: Attributes passed from platक्रमm to be attributed to a SoC
 */
काष्ठा soc_device *soc_device_रेजिस्टर(
	काष्ठा soc_device_attribute *soc_plat_dev_attr);

/**
 * soc_device_unरेजिस्टर - unरेजिस्टर SoC device
 * @dev: SoC device to be unरेजिस्टरed
 */
व्योम soc_device_unरेजिस्टर(काष्ठा soc_device *soc_dev);

/**
 * soc_device_to_device - helper function to fetch काष्ठा device
 * @soc: Previously रेजिस्टरed SoC device container
 */
काष्ठा device *soc_device_to_device(काष्ठा soc_device *soc);

#अगर_घोषित CONFIG_SOC_BUS
स्थिर काष्ठा soc_device_attribute *soc_device_match(
	स्थिर काष्ठा soc_device_attribute *matches);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा soc_device_attribute *soc_device_match(
	स्थिर काष्ठा soc_device_attribute *matches) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_BUS_H */
