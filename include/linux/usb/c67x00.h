<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * usb_c67x00.h: platक्रमm definitions क्रम the Cypress C67X00 USB chip
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston,
 * MA  02110-1301  USA.
 */

#अगर_अघोषित _LINUX_USB_C67X00_H
#घोषणा _LINUX_USB_C67X00_H

/* SIE configuration */
#घोषणा C67X00_SIE_UNUSED	0
#घोषणा C67X00_SIE_HOST		1
#घोषणा C67X00_SIE_PERIPHERAL_A	2	/* peripheral on A port */
#घोषणा C67X00_SIE_PERIPHERAL_B	3	/* peripheral on B port */

#घोषणा c67x00_sie_config(config, n)  (((config)>>(4*(n)))&0x3)

#घोषणा C67X00_SIE1_UNUSED	        (C67X00_SIE_UNUSED		<< 0)
#घोषणा C67X00_SIE1_HOST	        (C67X00_SIE_HOST		<< 0)
#घोषणा C67X00_SIE1_PERIPHERAL_A	(C67X00_SIE_PERIPHERAL_A	<< 0)
#घोषणा C67X00_SIE1_PERIPHERAL_B	(C67X00_SIE_PERIPHERAL_B	<< 0)

#घोषणा C67X00_SIE2_UNUSED		(C67X00_SIE_UNUSED		<< 4)
#घोषणा C67X00_SIE2_HOST		(C67X00_SIE_HOST		<< 4)
#घोषणा C67X00_SIE2_PERIPHERAL_A	(C67X00_SIE_PERIPHERAL_A	<< 4)
#घोषणा C67X00_SIE2_PERIPHERAL_B	(C67X00_SIE_PERIPHERAL_B	<< 4)

काष्ठा c67x00_platक्रमm_data अणु
	पूर्णांक sie_config;			/* SIEs config (C67X00_SIEx_*) */
	अचिन्हित दीर्घ hpi_regstep;	/* Step between HPI रेजिस्टरs  */
पूर्ण;

#पूर्ण_अगर /* _LINUX_USB_C67X00_H */
