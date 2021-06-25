<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 99, 2001 Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) 2009 Wind River Systems
 * Written by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित __ASM_IOCTL_H
#घोषणा __ASM_IOCTL_H

#घोषणा _IOC_SIZEBITS	13
#घोषणा _IOC_सूचीBITS	3

/*
 * Direction bits _IOC_NONE could be 0, but OSF/1 gives it a bit.
 * And this turns out useful to catch old ioctl numbers in header
 * files क्रम us.
 */
#घोषणा _IOC_NONE	1U
#घोषणा _IOC_READ	2U
#घोषणा _IOC_WRITE	4U

#समावेश <यंत्र-generic/ioctl.h>

#पूर्ण_अगर /* __ASM_IOCTL_H */
