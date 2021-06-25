<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IIO_TRIGGERED_BUFFER_H_
#घोषणा _LINUX_IIO_TRIGGERED_BUFFER_H_

#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा attribute;
काष्ठा iio_dev;
काष्ठा iio_buffer_setup_ops;

पूर्णांक iio_triggered_buffer_setup_ext(काष्ठा iio_dev *indio_dev,
	irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
	irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
	स्थिर काष्ठा iio_buffer_setup_ops *setup_ops,
	स्थिर काष्ठा attribute **buffer_attrs);
व्योम iio_triggered_buffer_cleanup(काष्ठा iio_dev *indio_dev);

#घोषणा iio_triggered_buffer_setup(indio_dev, h, thपढ़ो, setup_ops)		\
	iio_triggered_buffer_setup_ext((indio_dev), (h), (thपढ़ो), (setup_ops), शून्य)

पूर्णांक devm_iio_triggered_buffer_setup_ext(काष्ठा device *dev,
					काष्ठा iio_dev *indio_dev,
					irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
					irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
					स्थिर काष्ठा iio_buffer_setup_ops *ops,
					स्थिर काष्ठा attribute **buffer_attrs);

#घोषणा devm_iio_triggered_buffer_setup(dev, indio_dev, h, thपढ़ो, setup_ops)	\
	devm_iio_triggered_buffer_setup_ext((dev), (indio_dev), (h), (thपढ़ो), (setup_ops), शून्य)

#पूर्ण_अगर
