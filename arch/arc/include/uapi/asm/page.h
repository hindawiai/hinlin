<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित _UAPI__ASM_ARC_PAGE_H
#घोषणा _UAPI__ASM_ARC_PAGE_H

#समावेश <linux/स्थिर.h>

/* PAGE_SHIFT determines the page size */
#अगर defined(CONFIG_ARC_PAGE_SIZE_16K)
#घोषणा PAGE_SHIFT 14
#या_अगर defined(CONFIG_ARC_PAGE_SIZE_4K)
#घोषणा PAGE_SHIFT 12
#अन्यथा
/*
 * Default 8k
 * करोne this way (instead of under CONFIG_ARC_PAGE_SIZE_8K) because adhoc
 * user code (busybox appletlib.h) expects PAGE_SHIFT to be defined w/o
 * using the correct uClibc header and in their build our स्वतःconf.h is
 * not available
 */
#घोषणा PAGE_SHIFT 13
#पूर्ण_अगर

#घोषणा PAGE_SIZE	_BITUL(PAGE_SHIFT)	/* Default 8K */
#घोषणा PAGE_OFFSET	_AC(0x80000000, UL)	/* Kernel starts at 2G onwrds */

#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#पूर्ण_अगर /* _UAPI__ASM_ARC_PAGE_H */
