<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *    Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *    Copyright (C) 1999,2003 Matthew Wilcox < willy at debian . org >
 *    portions from "linux/ioctl.h for Linux" by H.H. Bergman.
 *
 *    This program is मुक्त software; you can redistribute it and/or modअगरy
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License क्रम more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#अगर_अघोषित _ASM_PARISC_IOCTL_H
#घोषणा _ASM_PARISC_IOCTL_H

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 * size of the parameter काष्ठाure in the lower 14 bits of the
 * upper 16 bits.
 * Encoding the size of the parameter काष्ठाure in the ioctl request
 * is useful क्रम catching programs compiled with old versions
 * and to aव्योम overwriting user space outside the user buffer area.
 * The highest 2 bits are reserved क्रम indicating the ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 */

/*
 * Direction bits.
 */
#घोषणा _IOC_NONE	0U
#घोषणा _IOC_WRITE	2U
#घोषणा _IOC_READ	1U

#समावेश <यंत्र-generic/ioctl.h>

#पूर्ण_अगर /* _ASM_PARISC_IOCTL_H */
