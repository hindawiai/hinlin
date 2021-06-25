<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industrial I/O in kernel access map पूर्णांकerface.
 *
 * Copyright (c) 2011 Jonathan Cameron
 */

#अगर_अघोषित _IIO_INKERN_H_
#घोषणा _IIO_INKERN_H_

काष्ठा iio_dev;
काष्ठा iio_map;

/**
 * iio_map_array_रेजिस्टर() - tell the core about inkernel consumers
 * @indio_dev:	provider device
 * @map:	array of mappings specअगरying association of channel with client
 */
पूर्णांक iio_map_array_रेजिस्टर(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_map *map);

/**
 * iio_map_array_unरेजिस्टर() - tell the core to हटाओ consumer mappings क्रम
 *				the given provider device
 * @indio_dev:	provider device
 */
पूर्णांक iio_map_array_unरेजिस्टर(काष्ठा iio_dev *indio_dev);

#पूर्ण_अगर
