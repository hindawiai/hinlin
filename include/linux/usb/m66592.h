<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * M66592 driver platक्रमm data
 *
 * Copyright (C) 2009  Renesas Solutions Corp.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 *
 */

#अगर_अघोषित __LINUX_USB_M66592_H
#घोषणा __LINUX_USB_M66592_H

#घोषणा M66592_PLATDATA_XTAL_12MHZ	0x01
#घोषणा M66592_PLATDATA_XTAL_24MHZ	0x02
#घोषणा M66592_PLATDATA_XTAL_48MHZ	0x03

काष्ठा m66592_platdata अणु
	/* one = on chip controller, zero = बाह्यal controller */
	अचिन्हित	on_chip:1;

	/* one = big endian, zero = little endian */
	अचिन्हित	endian:1;

	/* (बाह्यal controller only) M66592_PLATDATA_XTAL_nnMHZ */
	अचिन्हित	xtal:2;

	/* (बाह्यal controller only) one = 3.3V, zero = 1.5V */
	अचिन्हित	vअगर:1;

	/* (बाह्यal controller only) set one = WR0_N लघुed to WR1_N */
	अचिन्हित	wr0_लघुed_to_wr1:1;
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_M66592_H */

