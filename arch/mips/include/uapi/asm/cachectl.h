<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995, 1996 by Ralf Baechle
 */
#अगर_अघोषित _ASM_CACHECTL
#घोषणा _ASM_CACHECTL

/*
 * Options क्रम cacheflush प्रणाली call
 */
#घोषणा ICACHE	(1<<0)		/* flush inकाष्ठाion cache	  */
#घोषणा DCACHE	(1<<1)		/* ग_लिखोback and flush data cache */
#घोषणा BCACHE	(ICACHE|DCACHE) /* flush both caches		  */

/*
 * Caching modes क्रम the cachectl(2) call
 *
 * cachectl(2) is currently not supported and वापसs ENOSYS.
 */
#घोषणा CACHEABLE	0	/* make pages cacheable */
#घोषणा UNCACHEABLE	1	/* make pages uncacheable */

#पूर्ण_अगर	/* _ASM_CACHECTL */
