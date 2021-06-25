<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BMI088_ACCEL_H
#घोषणा BMI088_ACCEL_H

#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

काष्ठा device;

बाह्य स्थिर काष्ठा regmap_config bmi088_regmap_conf;
बाह्य स्थिर काष्ठा dev_pm_ops bmi088_accel_pm_ops;

पूर्णांक bmi088_accel_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			    स्थिर अक्षर *name, bool block_supported);
पूर्णांक bmi088_accel_core_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर /* BMI088_ACCEL_H */
