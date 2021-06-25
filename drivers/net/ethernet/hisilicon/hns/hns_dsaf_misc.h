<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित _HNS_DSAF_MISC_H
#घोषणा _HNS_DSAF_MISC_H

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hns_dsaf_mac.h"

#घोषणा CPLD_ADDR_PORT_OFFSET	0x4

#घोषणा HS_LED_ON		0xE
#घोषणा HS_LED_OFF		0xF

#घोषणा CPLD_LED_ON_VALUE	1
#घोषणा CPLD_LED_DEFAULT_VALUE	0

#घोषणा MAC_SFP_PORT_OFFSET	0x2

#घोषणा DSAF_LED_SPEED_S 0
#घोषणा DSAF_LED_SPEED_M (0x3 << DSAF_LED_SPEED_S)

#घोषणा DSAF_LED_LINK_B 2
#घोषणा DSAF_LED_DATA_B 4
#घोषणा DSAF_LED_ANCHOR_B 5

काष्ठा dsaf_misc_op *hns_misc_op_get(काष्ठा dsaf_device *dsaf_dev);
काष्ठा
platक्रमm_device *hns_dsaf_find_platक्रमm_device(काष्ठा fwnode_handle *fwnode);
#पूर्ण_अगर
