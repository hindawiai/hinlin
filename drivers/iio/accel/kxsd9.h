<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>

#घोषणा KXSD9_STATE_RX_SIZE 2
#घोषणा KXSD9_STATE_TX_SIZE 2

पूर्णांक kxsd9_common_probe(काष्ठा device *dev,
		       काष्ठा regmap *map,
		       स्थिर अक्षर *name);
पूर्णांक kxsd9_common_हटाओ(काष्ठा device *dev);

बाह्य स्थिर काष्ठा dev_pm_ops kxsd9_dev_pm_ops;
