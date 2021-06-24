<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BMC150_ACCEL_H_
#घोषणा _BMC150_ACCEL_H_

काष्ठा regmap;

क्रमागत अणु
	bmc150,
	bmi055,
	bma255,
	bma250e,
	bma222,
	bma222e,
	bma280,
पूर्ण;

पूर्णांक bmc150_accel_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			    स्थिर अक्षर *name, bool block_supported);
पूर्णांक bmc150_accel_core_हटाओ(काष्ठा device *dev);
काष्ठा i2c_client *bmc150_get_second_device(काष्ठा i2c_client *second_device);
व्योम bmc150_set_second_device(काष्ठा i2c_client *second_device);
बाह्य स्थिर काष्ठा dev_pm_ops bmc150_accel_pm_ops;
बाह्य स्थिर काष्ठा regmap_config bmc150_regmap_conf;

#पूर्ण_अगर  /* _BMC150_ACCEL_H_ */
