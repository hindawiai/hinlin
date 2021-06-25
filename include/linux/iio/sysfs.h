<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O core
 *
 *Copyright (c) 2008 Jonathan Cameron
 *
 * General attributes
 */

#अगर_अघोषित _INDUSTRIAL_IO_SYSFS_H_
#घोषणा _INDUSTRIAL_IO_SYSFS_H_

काष्ठा iio_buffer;
काष्ठा iio_chan_spec;

/**
 * काष्ठा iio_dev_attr - iio specअगरic device attribute
 * @dev_attr:	underlying device attribute
 * @address:	associated रेजिस्टर address
 * @l:		list head क्रम मुख्यtaining list of dynamically created attrs
 * @c:		specअगरication क्रम the underlying channel
 * @buffer:	the IIO buffer to which this attribute beदीर्घs to (अगर any)
 */
काष्ठा iio_dev_attr अणु
	काष्ठा device_attribute dev_attr;
	u64 address;
	काष्ठा list_head l;
	काष्ठा iio_chan_spec स्थिर *c;
	काष्ठा iio_buffer *buffer;
पूर्ण;

#घोषणा to_iio_dev_attr(_dev_attr)				\
	container_of(_dev_attr, काष्ठा iio_dev_attr, dev_attr)

sमाप_प्रकार iio_पढ़ो_स्थिर_attr(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *len);

/**
 * काष्ठा iio_स्थिर_attr - स्थिरant device specअगरic attribute
 *                         often used क्रम things like available modes
 * @string:	attribute string
 * @dev_attr:	underlying device attribute
 */
काष्ठा iio_स्थिर_attr अणु
	स्थिर अक्षर *string;
	काष्ठा device_attribute dev_attr;
पूर्ण;

#घोषणा to_iio_स्थिर_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा iio_स्थिर_attr, dev_attr)

/* Some attributes will be hard coded (device dependent) and not require an
   address, in these हालs pass a negative */
#घोषणा IIO_ATTR(_name, _mode, _show, _store, _addr)		\
	अणु .dev_attr = __ATTR(_name, _mode, _show, _store),	\
	  .address = _addr पूर्ण

#घोषणा IIO_ATTR_RO(_name, _addr)       \
	अणु .dev_attr = __ATTR_RO(_name), \
	  .address = _addr पूर्ण

#घोषणा IIO_ATTR_WO(_name, _addr)       \
	अणु .dev_attr = __ATTR_WO(_name), \
	  .address = _addr पूर्ण

#घोषणा IIO_ATTR_RW(_name, _addr)       \
	अणु .dev_attr = __ATTR_RW(_name), \
	  .address = _addr पूर्ण

#घोषणा IIO_DEVICE_ATTR(_name, _mode, _show, _store, _addr)	\
	काष्ठा iio_dev_attr iio_dev_attr_##_name		\
	= IIO_ATTR(_name, _mode, _show, _store, _addr)

#घोषणा IIO_DEVICE_ATTR_RO(_name, _addr)                       \
	काष्ठा iio_dev_attr iio_dev_attr_##_name                \
	= IIO_ATTR_RO(_name, _addr)

#घोषणा IIO_DEVICE_ATTR_WO(_name, _addr)                       \
	काष्ठा iio_dev_attr iio_dev_attr_##_name                \
	= IIO_ATTR_WO(_name, _addr)

#घोषणा IIO_DEVICE_ATTR_RW(_name, _addr)                                   \
	काष्ठा iio_dev_attr iio_dev_attr_##_name                            \
	= IIO_ATTR_RW(_name, _addr)

#घोषणा IIO_DEVICE_ATTR_NAMED(_vname, _name, _mode, _show, _store, _addr) \
	काष्ठा iio_dev_attr iio_dev_attr_##_vname			\
	= IIO_ATTR(_name, _mode, _show, _store, _addr)

#घोषणा IIO_CONST_ATTR(_name, _string)					\
	काष्ठा iio_स्थिर_attr iio_स्थिर_attr_##_name			\
	= अणु .string = _string,						\
	    .dev_attr = __ATTR(_name, S_IRUGO, iio_पढ़ो_स्थिर_attr, शून्य)पूर्ण

#घोषणा IIO_CONST_ATTR_NAMED(_vname, _name, _string)			\
	काष्ठा iio_स्थिर_attr iio_स्थिर_attr_##_vname			\
	= अणु .string = _string,						\
	    .dev_attr = __ATTR(_name, S_IRUGO, iio_पढ़ो_स्थिर_attr, शून्य)पूर्ण

/* Generic attributes of onetype or another */

/**
 * IIO_DEV_ATTR_SAMP_FREQ - sets any पूर्णांकernal घड़ी frequency
 * @_mode: sysfs file mode/permissions
 * @_show: output method क्रम the attribute
 * @_store: input method क्रम the attribute
 **/
#घोषणा IIO_DEV_ATTR_SAMP_FREQ(_mode, _show, _store)			\
	IIO_DEVICE_ATTR(sampling_frequency, _mode, _show, _store, 0)

/**
 * IIO_DEV_ATTR_SAMP_FREQ_AVAIL - list available sampling frequencies
 * @_show: output method क्रम the attribute
 *
 * May be mode dependent on some devices
 **/
#घोषणा IIO_DEV_ATTR_SAMP_FREQ_AVAIL(_show)				\
	IIO_DEVICE_ATTR(sampling_frequency_available, S_IRUGO, _show, शून्य, 0)
/**
 * IIO_CONST_ATTR_SAMP_FREQ_AVAIL - list available sampling frequencies
 * @_string: frequency string क्रम the attribute
 *
 * Constant version
 **/
#घोषणा IIO_CONST_ATTR_SAMP_FREQ_AVAIL(_string)			\
	IIO_CONST_ATTR(sampling_frequency_available, _string)

/**
 * IIO_DEV_ATTR_INT_TIME_AVAIL - list available पूर्णांकegration बार
 * @_show: output method क्रम the attribute
 **/
#घोषणा IIO_DEV_ATTR_INT_TIME_AVAIL(_show)		\
	IIO_DEVICE_ATTR(पूर्णांकegration_समय_available, S_IRUGO, _show, शून्य, 0)
/**
 * IIO_CONST_ATTR_INT_TIME_AVAIL - list available पूर्णांकegration बार
 * @_string: frequency string क्रम the attribute
 *
 * Constant version
 **/
#घोषणा IIO_CONST_ATTR_INT_TIME_AVAIL(_string)		\
	IIO_CONST_ATTR(पूर्णांकegration_समय_available, _string)

#घोषणा IIO_DEV_ATTR_TEMP_RAW(_show)			\
	IIO_DEVICE_ATTR(in_temp_raw, S_IRUGO, _show, शून्य, 0)

#घोषणा IIO_CONST_ATTR_TEMP_OFFSET(_string)		\
	IIO_CONST_ATTR(in_temp_offset, _string)

#घोषणा IIO_CONST_ATTR_TEMP_SCALE(_string)		\
	IIO_CONST_ATTR(in_temp_scale, _string)

#पूर्ण_अगर /* _INDUSTRIAL_IO_SYSFS_H_ */
