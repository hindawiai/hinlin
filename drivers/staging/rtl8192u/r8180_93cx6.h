<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	This is part of rtl8187 OpenSource driver
 *	Copyright (C) Andrea Merello 2004-2005  <andrea.merello@gmail.com>
 *	Released under the terms of GPL (General Public Licence)
 *
 *	Parts of this driver are based on the GPL part of the
 *	official realtek driver
 *	Parts of this driver are based on the rtl8180 driver skeleton
 *	from Patric Schenke & Andres Salomon
 *	Parts of this driver are based on the Intel Pro Wireless 2100 GPL driver
 *
 *	We want to thank the Authors of such projects and the Ndiswrapper
 *	project Authors.
 */

/*This files contains card eeprom (93c46 or 93c56) programming routines*/
/*memory is addressed by WORDS*/

#समावेश "r8192U.h"
#समावेश "r8192U_hw.h"

#घोषणा EPROM_DELAY 10

पूर्णांक eprom_पढ़ो(काष्ठा net_device *dev, u32 addr); /* पढ़ोs a 16 bits word */
