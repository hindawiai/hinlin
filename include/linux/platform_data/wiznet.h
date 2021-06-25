<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Ethernet driver क्रम the WIZnet W5x00 chip.
 */

#अगर_अघोषित PLATFORM_DATA_WIZNET_H
#घोषणा PLATFORM_DATA_WIZNET_H

#समावेश <linux/अगर_ether.h>

काष्ठा wiznet_platक्रमm_data अणु
	पूर्णांक	link_gpio;
	u8	mac_addr[ETH_ALEN];
पूर्ण;

#अगर_अघोषित CONFIG_WIZNET_BUS_SHIFT
#घोषणा CONFIG_WIZNET_BUS_SHIFT 0
#पूर्ण_अगर

#घोषणा W5100_BUS_सूचीECT_SIZE	(0x8000 << CONFIG_WIZNET_BUS_SHIFT)
#घोषणा W5300_BUS_सूचीECT_SIZE	(0x0400 << CONFIG_WIZNET_BUS_SHIFT)

#पूर्ण_अगर /* PLATFORM_DATA_WIZNET_H */
