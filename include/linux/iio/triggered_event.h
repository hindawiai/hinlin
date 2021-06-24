<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IIO_TRIGGERED_EVENT_H_
#घोषणा _LINUX_IIO_TRIGGERED_EVENT_H_

#समावेश <linux/पूर्णांकerrupt.h>

पूर्णांक iio_triggered_event_setup(काष्ठा iio_dev *indio_dev,
	irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
	irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p));
व्योम iio_triggered_event_cleanup(काष्ठा iio_dev *indio_dev);

#पूर्ण_अगर
