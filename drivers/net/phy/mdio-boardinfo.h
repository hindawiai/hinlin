<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mdio-boardinfo.h - board info पूर्णांकerface पूर्णांकernal to the mdio_bus
 * component
 */

#अगर_अघोषित __MDIO_BOARD_INFO_H
#घोषणा __MDIO_BOARD_INFO_H

#समावेश <linux/phy.h>
#समावेश <linux/mutex.h>

काष्ठा mdio_board_entry अणु
	काष्ठा list_head	list;
	काष्ठा mdio_board_info	board_info;
पूर्ण;

व्योम mdiobus_setup_mdiodev_from_board_info(काष्ठा mii_bus *bus,
					   पूर्णांक (*cb)
					   (काष्ठा mii_bus *bus,
					    काष्ठा mdio_board_info *bi));

#पूर्ण_अगर /* __MDIO_BOARD_INFO_H */
