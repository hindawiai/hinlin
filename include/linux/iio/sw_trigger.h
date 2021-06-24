<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industrial I/O software trigger पूर्णांकerface
 *
 * Copyright (c) 2015 Intel Corporation
 */

#अगर_अघोषित __IIO_SW_TRIGGER
#घोषणा __IIO_SW_TRIGGER

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/configfs.h>

#घोषणा module_iio_sw_trigger_driver(__iio_sw_trigger_type) \
	module_driver(__iio_sw_trigger_type, iio_रेजिस्टर_sw_trigger_type, \
		      iio_unरेजिस्टर_sw_trigger_type)

काष्ठा iio_sw_trigger_ops;

काष्ठा iio_sw_trigger_type अणु
	स्थिर अक्षर *name;
	काष्ठा module *owner;
	स्थिर काष्ठा iio_sw_trigger_ops *ops;
	काष्ठा list_head list;
	काष्ठा config_group *group;
पूर्ण;

काष्ठा iio_sw_trigger अणु
	काष्ठा iio_trigger *trigger;
	काष्ठा iio_sw_trigger_type *trigger_type;
	काष्ठा config_group group;
पूर्ण;

काष्ठा iio_sw_trigger_ops अणु
	काष्ठा iio_sw_trigger* (*probe)(स्थिर अक्षर *);
	पूर्णांक (*हटाओ)(काष्ठा iio_sw_trigger *);
पूर्ण;

अटल अंतरभूत
काष्ठा iio_sw_trigger *to_iio_sw_trigger(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा iio_sw_trigger,
			    group);
पूर्ण

पूर्णांक iio_रेजिस्टर_sw_trigger_type(काष्ठा iio_sw_trigger_type *tt);
व्योम iio_unरेजिस्टर_sw_trigger_type(काष्ठा iio_sw_trigger_type *tt);

काष्ठा iio_sw_trigger *iio_sw_trigger_create(स्थिर अक्षर *, स्थिर अक्षर *);
व्योम iio_sw_trigger_destroy(काष्ठा iio_sw_trigger *);

पूर्णांक iio_sw_trigger_type_configfs_रेजिस्टर(काष्ठा iio_sw_trigger_type *tt);
व्योम iio_sw_trigger_type_configfs_unरेजिस्टर(काष्ठा iio_sw_trigger_type *tt);

अटल अंतरभूत
व्योम iio_swt_group_init_type_name(काष्ठा iio_sw_trigger *t,
				  स्थिर अक्षर *name,
				  स्थिर काष्ठा config_item_type *type)
अणु
#अगर IS_ENABLED(CONFIG_CONFIGFS_FS)
	config_group_init_type_name(&t->group, name, type);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __IIO_SW_TRIGGER */
