<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_IIO_KFIFO_BUF_H__
#घोषणा __LINUX_IIO_KFIFO_BUF_H__

काष्ठा iio_buffer;
काष्ठा iio_buffer_setup_ops;
काष्ठा iio_dev;
काष्ठा device;

काष्ठा iio_buffer *iio_kfअगरo_allocate(व्योम);
व्योम iio_kfअगरo_मुक्त(काष्ठा iio_buffer *r);

पूर्णांक devm_iio_kfअगरo_buffer_setup_ext(काष्ठा device *dev,
				    काष्ठा iio_dev *indio_dev,
				    पूर्णांक mode_flags,
				    स्थिर काष्ठा iio_buffer_setup_ops *setup_ops,
				    स्थिर काष्ठा attribute **buffer_attrs);

#घोषणा devm_iio_kfअगरo_buffer_setup(dev, indio_dev, mode_flags, setup_ops)	\
	devm_iio_kfअगरo_buffer_setup_ext((dev), (indio_dev), (mode_flags), (setup_ops), शून्य)

#पूर्ण_अगर
