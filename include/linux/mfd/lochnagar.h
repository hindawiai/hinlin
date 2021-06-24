<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lochnagar पूर्णांकernals
 *
 * Copyright (c) 2013-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>

#अगर_अघोषित CIRRUS_LOCHNAGAR_H
#घोषणा CIRRUS_LOCHNAGAR_H

क्रमागत lochnagar_type अणु
	LOCHNAGAR1,
	LOCHNAGAR2,
पूर्ण;

/**
 * काष्ठा lochnagar - Core data क्रम the Lochnagar audio board driver.
 *
 * @type: The type of Lochnagar device connected.
 * @dev: A poपूर्णांकer to the काष्ठा device क्रम the मुख्य MFD.
 * @regmap: The devices मुख्य रेजिस्टर map.
 * @analogue_config_lock: Lock used to protect updates in the analogue
 * configuration as these must not be changed whilst the hardware is processing
 * the last update.
 */
काष्ठा lochnagar अणु
	क्रमागत lochnagar_type type;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	/* Lock to protect updates to the analogue configuration */
	काष्ठा mutex analogue_config_lock;
पूर्ण;

/* Register Addresses */
#घोषणा LOCHNAGAR_SOFTWARE_RESET                             0x00
#घोषणा LOCHNAGAR_FIRMWARE_ID1                               0x01
#घोषणा LOCHNAGAR_FIRMWARE_ID2                               0x02

/* (0x0000)  Software Reset */
#घोषणा LOCHNAGAR_DEVICE_ID_MASK                           0xFFFC
#घोषणा LOCHNAGAR_DEVICE_ID_SHIFT                               2
#घोषणा LOCHNAGAR_REV_ID_MASK                              0x0003
#घोषणा LOCHNAGAR_REV_ID_SHIFT                                  0

पूर्णांक lochnagar_update_config(काष्ठा lochnagar *lochnagar);

#पूर्ण_अगर
