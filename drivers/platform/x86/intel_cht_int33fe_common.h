<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common code क्रम Intel Cherry Trail ACPI INT33FE pseuकरो device drivers
 * (USB Micro-B and Type-C connector variants), header file
 *
 * Copyright (c) 2019 Yauhen Kharuzhy <jekhor@gmail.com>
 */

#अगर_अघोषित _INTEL_CHT_INT33FE_COMMON_H
#घोषणा _INTEL_CHT_INT33FE_COMMON_H

#समावेश <linux/device.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/i2c.h>

क्रमागत पूर्णांक33fe_hw_type अणु
	INT33FE_HW_MICROB,
	INT33FE_HW_TYPEC,
पूर्ण;

काष्ठा cht_पूर्णांक33fe_data अणु
	काष्ठा device *dev;

	पूर्णांक (*probe)(काष्ठा cht_पूर्णांक33fe_data *data);
	पूर्णांक (*हटाओ)(काष्ठा cht_पूर्णांक33fe_data *data);

	काष्ठा i2c_client *battery_fg;

	/* Type-C only */
	काष्ठा i2c_client *fusb302;
	काष्ठा i2c_client *pi3usb30532;

	काष्ठा fwnode_handle *dp;
पूर्ण;

पूर्णांक cht_पूर्णांक33fe_microb_probe(काष्ठा cht_पूर्णांक33fe_data *data);
पूर्णांक cht_पूर्णांक33fe_microb_हटाओ(काष्ठा cht_पूर्णांक33fe_data *data);
पूर्णांक cht_पूर्णांक33fe_typec_probe(काष्ठा cht_पूर्णांक33fe_data *data);
पूर्णांक cht_पूर्णांक33fe_typec_हटाओ(काष्ठा cht_पूर्णांक33fe_data *data);

#पूर्ण_अगर /* _INTEL_CHT_INT33FE_COMMON_H */
