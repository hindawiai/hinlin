<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O core function defs.
 *
 * Copyright (c) 2008 Jonathan Cameron
 *
 * These definitions are meant क्रम use only within the IIO core, not inभागidual
 * drivers.
 */

#अगर_अघोषित _IIO_CORE_H_
#घोषणा _IIO_CORE_H_
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>

काष्ठा iio_buffer;
काष्ठा iio_chan_spec;
काष्ठा iio_dev;

बाह्य काष्ठा device_type iio_device_type;

काष्ठा iio_dev_buffer_pair अणु
	काष्ठा iio_dev		*indio_dev;
	काष्ठा iio_buffer	*buffer;
पूर्ण;

#घोषणा IIO_IOCTL_UNHANDLED	1
काष्ठा iio_ioctl_handler अणु
	काष्ठा list_head entry;
	दीर्घ (*ioctl)(काष्ठा iio_dev *indio_dev, काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्ण;

दीर्घ iio_device_ioctl(काष्ठा iio_dev *indio_dev, काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

व्योम iio_device_ioctl_handler_रेजिस्टर(काष्ठा iio_dev *indio_dev,
				       काष्ठा iio_ioctl_handler *h);
व्योम iio_device_ioctl_handler_unरेजिस्टर(काष्ठा iio_ioctl_handler *h);

पूर्णांक __iio_add_chan_devattr(स्थिर अक्षर *postfix,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   sमाप_प्रकार (*func)(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf),
			   sमाप_प्रकार (*ग_लिखोfunc)(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len),
			   u64 mask,
			   क्रमागत iio_shared_by shared_by,
			   काष्ठा device *dev,
			   काष्ठा iio_buffer *buffer,
			   काष्ठा list_head *attr_list);
व्योम iio_मुक्त_chan_devattr_list(काष्ठा list_head *attr_list);

पूर्णांक iio_device_रेजिस्टर_sysfs_group(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा attribute_group *group);

sमाप_प्रकार iio_क्रमmat_value(अक्षर *buf, अचिन्हित पूर्णांक type, पूर्णांक size, पूर्णांक *vals);

/* Event पूर्णांकerface flags */
#घोषणा IIO_BUSY_BIT_POS 1

#अगर_घोषित CONFIG_IIO_BUFFER
काष्ठा poll_table_काष्ठा;

__poll_t iio_buffer_poll_wrapper(काष्ठा file *filp,
				 काष्ठा poll_table_काष्ठा *रुको);
sमाप_प्रकार iio_buffer_पढ़ो_wrapper(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार n, loff_t *f_ps);

पूर्णांक iio_buffers_alloc_sysfs_and_mask(काष्ठा iio_dev *indio_dev);
व्योम iio_buffers_मुक्त_sysfs_and_mask(काष्ठा iio_dev *indio_dev);

#घोषणा iio_buffer_poll_addr (&iio_buffer_poll_wrapper)
#घोषणा iio_buffer_पढ़ो_outer_addr (&iio_buffer_पढ़ो_wrapper)

व्योम iio_disable_all_buffers(काष्ठा iio_dev *indio_dev);
व्योम iio_buffer_wakeup_poll(काष्ठा iio_dev *indio_dev);
व्योम iio_device_detach_buffers(काष्ठा iio_dev *indio_dev);

#अन्यथा

#घोषणा iio_buffer_poll_addr शून्य
#घोषणा iio_buffer_पढ़ो_outer_addr शून्य

अटल अंतरभूत पूर्णांक iio_buffers_alloc_sysfs_and_mask(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iio_buffers_मुक्त_sysfs_and_mask(काष्ठा iio_dev *indio_dev) अणुपूर्ण

अटल अंतरभूत व्योम iio_disable_all_buffers(काष्ठा iio_dev *indio_dev) अणुपूर्ण
अटल अंतरभूत व्योम iio_buffer_wakeup_poll(काष्ठा iio_dev *indio_dev) अणुपूर्ण
अटल अंतरभूत व्योम iio_device_detach_buffers(काष्ठा iio_dev *indio_dev) अणुपूर्ण

#पूर्ण_अगर

पूर्णांक iio_device_रेजिस्टर_eventset(काष्ठा iio_dev *indio_dev);
व्योम iio_device_unरेजिस्टर_eventset(काष्ठा iio_dev *indio_dev);
व्योम iio_device_wakeup_eventset(काष्ठा iio_dev *indio_dev);

काष्ठा iio_event_पूर्णांकerface;
bool iio_event_enabled(स्थिर काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक);

#पूर्ण_अगर
