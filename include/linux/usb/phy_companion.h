<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * phy-companion.h -- phy companion to indicate the comparator part of PHY
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित __DRIVERS_PHY_COMPANION_H
#घोषणा __DRIVERS_PHY_COMPANION_H

#समावेश <linux/usb/otg.h>

/* phy_companion to take care of VBUS, ID and srp capabilities */
काष्ठा phy_companion अणु

	/* effective क्रम A-peripheral, ignored क्रम B devices */
	पूर्णांक	(*set_vbus)(काष्ठा phy_companion *x, bool enabled);

	/* क्रम B devices only:  start session with A-Host */
	पूर्णांक	(*start_srp)(काष्ठा phy_companion *x);
पूर्ण;

#पूर्ण_अगर /* __DRIVERS_PHY_COMPANION_H */
