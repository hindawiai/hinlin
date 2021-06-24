<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * g_prपूर्णांकer.h -- Header file क्रम USB Prपूर्णांकer gadget driver
 *
 * Copyright (C) 2007 Craig W. Nadler
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित __LINUX_USB_G_PRINTER_H
#घोषणा __LINUX_USB_G_PRINTER_H

#घोषणा PRINTER_NOT_ERROR	0x08
#घोषणा PRINTER_SELECTED	0x10
#घोषणा PRINTER_PAPER_EMPTY	0x20

/* The 'g' code is also used by gadgetfs ioctl requests.
 * Don't add any colliding codes to either driver, and keep
 * them in unique ranges (size 0x20 क्रम now).
 */
#घोषणा GADGET_GET_PRINTER_STATUS	_IOR('g', 0x21, अचिन्हित अक्षर)
#घोषणा GADGET_SET_PRINTER_STATUS	_IOWR('g', 0x22, अचिन्हित अक्षर)

#पूर्ण_अगर /* __LINUX_USB_G_PRINTER_H */
