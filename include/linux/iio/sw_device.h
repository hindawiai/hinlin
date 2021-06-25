<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industrial I/O software device पूर्णांकerface
 *
 * Copyright (c) 2016 Intel Corporation
 */

#अगर_अघोषित __IIO_SW_DEVICE
#घोषणा __IIO_SW_DEVICE

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/configfs.h>

#घोषणा module_iio_sw_device_driver(__iio_sw_device_type) \
	module_driver(__iio_sw_device_type, iio_रेजिस्टर_sw_device_type, \
		      iio_unरेजिस्टर_sw_device_type)

काष्ठा iio_sw_device_ops;

काष्ठा iio_sw_device_type अणु
	स्थिर अक्षर *name;
	काष्ठा module *owner;
	स्थिर काष्ठा iio_sw_device_ops *ops;
	काष्ठा list_head list;
	काष्ठा config_group *group;
पूर्ण;

काष्ठा iio_sw_device अणु
	काष्ठा iio_dev *device;
	काष्ठा iio_sw_device_type *device_type;
	काष्ठा config_group group;
पूर्ण;

काष्ठा iio_sw_device_ops अणु
	काष्ठा iio_sw_device* (*probe)(स्थिर अक्षर *);
	पूर्णांक (*हटाओ)(काष्ठा iio_sw_device *);
पूर्ण;

अटल अंतरभूत
काष्ठा iio_sw_device *to_iio_sw_device(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा iio_sw_device,
			    group);
पूर्ण

पूर्णांक iio_रेजिस्टर_sw_device_type(काष्ठा iio_sw_device_type *dt);
व्योम iio_unरेजिस्टर_sw_device_type(काष्ठा iio_sw_device_type *dt);

काष्ठा iio_sw_device *iio_sw_device_create(स्थिर अक्षर *, स्थिर अक्षर *);
व्योम iio_sw_device_destroy(काष्ठा iio_sw_device *);

पूर्णांक iio_sw_device_type_configfs_रेजिस्टर(काष्ठा iio_sw_device_type *dt);
व्योम iio_sw_device_type_configfs_unरेजिस्टर(काष्ठा iio_sw_device_type *dt);

अटल अंतरभूत
व्योम iio_swd_group_init_type_name(काष्ठा iio_sw_device *d,
				  स्थिर अक्षर *name,
				  स्थिर काष्ठा config_item_type *type)
अणु
#अगर IS_ENABLED(CONFIG_CONFIGFS_FS)
	config_group_init_type_name(&d->group, name, type);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __IIO_SW_DEVICE */
