<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#अगर_अघोषित INV_ICM42600_TEMP_H_
#घोषणा INV_ICM42600_TEMP_H_

#समावेश <linux/iio/iपन.स>

#घोषणा INV_ICM42600_TEMP_CHAN(_index)					\
	अणु								\
		.type = IIO_TEMP,					\
		.info_mask_separate =					\
			BIT(IIO_CHAN_INFO_RAW) |			\
			BIT(IIO_CHAN_INFO_OFFSET) |			\
			BIT(IIO_CHAN_INFO_SCALE),			\
		.scan_index = _index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
		पूर्ण,							\
	पूर्ण

पूर्णांक inv_icm42600_temp_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask);

#पूर्ण_अगर
