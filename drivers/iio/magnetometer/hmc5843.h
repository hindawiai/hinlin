<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम hmc5843 driver
 *
 * Split from hmc5843.c
 * Copyright (C) Josef Gajdusek <atx@atx.name>
 */

#अगर_अघोषित HMC5843_CORE_H
#घोषणा HMC5843_CORE_H

#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>

#घोषणा HMC5843_CONFIG_REG_A			0x00
#घोषणा HMC5843_CONFIG_REG_B			0x01
#घोषणा HMC5843_MODE_REG			0x02
#घोषणा HMC5843_DATA_OUT_MSB_REGS		0x03
#घोषणा HMC5843_STATUS_REG			0x09
#घोषणा HMC5843_ID_REG				0x0a
#घोषणा HMC5843_ID_END				0x0c

क्रमागत hmc5843_ids अणु
	HMC5843_ID,
	HMC5883_ID,
	HMC5883L_ID,
	HMC5983_ID,
पूर्ण;

/**
 * काष्ठा hmc5843_data	- device specअगरic data
 * @dev:		actual device
 * @lock:		update and पढ़ो regmap data
 * @regmap:		hardware access रेजिस्टर maps
 * @variant:		describe chip variants
 * @buffer:		3x 16-bit channels + padding + 64-bit बारtamp
 */
काष्ठा hmc5843_data अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा hmc5843_chip_info *variant;
	काष्ठा iio_mount_matrix orientation;
	__be16 buffer[8];
पूर्ण;

पूर्णांक hmc5843_common_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
			 क्रमागत hmc5843_ids id, स्थिर अक्षर *name);
पूर्णांक hmc5843_common_हटाओ(काष्ठा device *dev);

पूर्णांक hmc5843_common_suspend(काष्ठा device *dev);
पूर्णांक hmc5843_common_resume(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM_SLEEP
अटल __maybe_unused SIMPLE_DEV_PM_OPS(hmc5843_pm_ops,
					hmc5843_common_suspend,
					hmc5843_common_resume);
#घोषणा HMC5843_PM_OPS (&hmc5843_pm_ops)
#अन्यथा
#घोषणा HMC5843_PM_OPS शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* HMC5843_CORE_H */
