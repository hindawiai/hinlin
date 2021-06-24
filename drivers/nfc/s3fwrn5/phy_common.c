<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Link Layer क्रम Samsung S3FWRN5 NCI based Driver
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 * Copyright (C) 2020 Samsung Electrnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश "phy_common.h"

व्योम s3fwrn5_phy_set_wake(व्योम *phy_id, bool wake)
अणु
	काष्ठा phy_common *phy = phy_id;

	mutex_lock(&phy->mutex);
	gpio_set_value(phy->gpio_fw_wake, wake);
	अगर (wake)
		msleep(S3FWRN5_EN_WAIT_TIME);
	mutex_unlock(&phy->mutex);
पूर्ण
EXPORT_SYMBOL(s3fwrn5_phy_set_wake);

bool s3fwrn5_phy_घातer_ctrl(काष्ठा phy_common *phy, क्रमागत s3fwrn5_mode mode)
अणु
	अगर (phy->mode == mode)
		वापस false;

	phy->mode = mode;

	gpio_set_value(phy->gpio_en, 1);
	gpio_set_value(phy->gpio_fw_wake, 0);
	अगर (mode == S3FWRN5_MODE_FW)
		gpio_set_value(phy->gpio_fw_wake, 1);

	अगर (mode != S3FWRN5_MODE_COLD) अणु
		msleep(S3FWRN5_EN_WAIT_TIME);
		gpio_set_value(phy->gpio_en, 0);
		msleep(S3FWRN5_EN_WAIT_TIME);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(s3fwrn5_phy_घातer_ctrl);

व्योम s3fwrn5_phy_set_mode(व्योम *phy_id, क्रमागत s3fwrn5_mode mode)
अणु
	काष्ठा phy_common *phy = phy_id;

	mutex_lock(&phy->mutex);

	s3fwrn5_phy_घातer_ctrl(phy, mode);

	mutex_unlock(&phy->mutex);
पूर्ण
EXPORT_SYMBOL(s3fwrn5_phy_set_mode);

क्रमागत s3fwrn5_mode s3fwrn5_phy_get_mode(व्योम *phy_id)
अणु
	काष्ठा phy_common *phy = phy_id;
	क्रमागत s3fwrn5_mode mode;

	mutex_lock(&phy->mutex);

	mode = phy->mode;

	mutex_unlock(&phy->mutex);

	वापस mode;
पूर्ण
EXPORT_SYMBOL(s3fwrn5_phy_get_mode);
