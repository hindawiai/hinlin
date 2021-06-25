<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __ARC_ASM_CACHECTL_H
#घोषणा __ARC_ASM_CACHECTL_H

/*
 * ARC ABI flags defined क्रम Android's finegrained cacheflush requirements
 */
#घोषणा CF_I_INV	0x0002
#घोषणा CF_D_FLUSH	0x0010
#घोषणा CF_D_FLUSH_INV	0x0020

#घोषणा CF_DEFAULT	(CF_I_INV | CF_D_FLUSH)

/*
 * Standard flags expected by cacheflush प्रणाली call users
 */
#घोषणा ICACHE	CF_I_INV
#घोषणा DCACHE	CF_D_FLUSH
#घोषणा BCACHE	(CF_I_INV | CF_D_FLUSH)

#पूर्ण_अगर
