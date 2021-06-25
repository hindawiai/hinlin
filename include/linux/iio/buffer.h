<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O core - generic buffer पूर्णांकerfaces.
 *
 * Copyright (c) 2008 Jonathan Cameron
 */

#अगर_अघोषित _IIO_BUFFER_GENERIC_H_
#घोषणा _IIO_BUFFER_GENERIC_H_
#समावेश <linux/sysfs.h>
#समावेश <linux/iio/iपन.स>

काष्ठा iio_buffer;

पूर्णांक iio_push_to_buffers(काष्ठा iio_dev *indio_dev, स्थिर व्योम *data);

/**
 * iio_push_to_buffers_with_बारtamp() - push data and बारtamp to buffers
 * @indio_dev:		iio_dev काष्ठाure क्रम device.
 * @data:		sample data
 * @बारtamp:		बारtamp क्रम the sample data
 *
 * Pushes data to the IIO device's buffers. If बारtamps are enabled क्रम the
 * device the function will store the supplied बारtamp as the last element in
 * the sample data buffer beक्रमe pushing it to the device buffers. The sample
 * data buffer needs to be large enough to hold the additional बारtamp
 * (usually the buffer should be indio->scan_bytes bytes large).
 *
 * Returns 0 on success, a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक iio_push_to_buffers_with_बारtamp(काष्ठा iio_dev *indio_dev,
	व्योम *data, पूर्णांक64_t बारtamp)
अणु
	अगर (indio_dev->scan_बारtamp) अणु
		माप_प्रकार ts_offset = indio_dev->scan_bytes / माप(पूर्णांक64_t) - 1;
		((पूर्णांक64_t *)data)[ts_offset] = बारtamp;
	पूर्ण

	वापस iio_push_to_buffers(indio_dev, data);
पूर्ण

bool iio_validate_scan_mask_onehot(काष्ठा iio_dev *indio_dev,
				   स्थिर अचिन्हित दीर्घ *mask);

पूर्णांक iio_device_attach_buffer(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_buffer *buffer);

#पूर्ण_अगर /* _IIO_BUFFER_GENERIC_H_ */
