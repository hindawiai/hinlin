<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Part of the HSI अक्षरacter device driver.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Andras Domokos <andras.करोmokos at nokia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */

#अगर_अघोषित __HSI_CHAR_H
#घोषणा __HSI_CHAR_H

#समावेश <linux/types.h>

#घोषणा HSI_CHAR_MAGIC		'k'
#घोषणा HSC_IOW(num, dtype)	_IOW(HSI_CHAR_MAGIC, num, dtype)
#घोषणा HSC_IOR(num, dtype)	_IOR(HSI_CHAR_MAGIC, num, dtype)
#घोषणा HSC_IOWR(num, dtype)	_IOWR(HSI_CHAR_MAGIC, num, dtype)
#घोषणा HSC_IO(num)		_IO(HSI_CHAR_MAGIC, num)

#घोषणा HSC_RESET		HSC_IO(16)
#घोषणा HSC_SET_PM		HSC_IO(17)
#घोषणा HSC_SEND_BREAK		HSC_IO(18)
#घोषणा HSC_SET_RX		HSC_IOW(19, काष्ठा hsc_rx_config)
#घोषणा HSC_GET_RX		HSC_IOW(20, काष्ठा hsc_rx_config)
#घोषणा HSC_SET_TX		HSC_IOW(21, काष्ठा hsc_tx_config)
#घोषणा HSC_GET_TX		HSC_IOW(22, काष्ठा hsc_tx_config)

#घोषणा HSC_PM_DISABLE		0
#घोषणा HSC_PM_ENABLE		1

#घोषणा HSC_MODE_STREAM		1
#घोषणा HSC_MODE_FRAME		2
#घोषणा HSC_FLOW_SYNC		0
#घोषणा HSC_ARB_RR		0
#घोषणा HSC_ARB_PRIO		1

काष्ठा hsc_rx_config अणु
	__u32 mode;
	__u32 flow;
	__u32 channels;
पूर्ण;

काष्ठा hsc_tx_config अणु
	__u32 mode;
	__u32 channels;
	__u32 speed;
	__u32 arb_mode;
पूर्ण;

#पूर्ण_अगर /* __HSI_CHAR_H */
