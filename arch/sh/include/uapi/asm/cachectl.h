<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SH_CACHECTL_H
#घोषणा _SH_CACHECTL_H

/* Definitions क्रम the cacheflush प्रणाली call.  */

#घोषणा CACHEFLUSH_D_INVAL	0x1	/* invalidate (without ग_लिखो back) */
#घोषणा CACHEFLUSH_D_WB		0x2	/* ग_लिखो back (without invalidate) */
#घोषणा CACHEFLUSH_D_PURGE	0x3	/* ग_लिखोback and invalidate */

#घोषणा CACHEFLUSH_I		0x4

/*
 * Options क्रम cacheflush प्रणाली call
 */
#घोषणा ICACHE	CACHEFLUSH_I		/* flush inकाष्ठाion cache */
#घोषणा DCACHE	CACHEFLUSH_D_PURGE	/* ग_लिखोback and flush data cache */
#घोषणा BCACHE	(ICACHE|DCACHE)		/* flush both caches */

#पूर्ण_अगर /* _SH_CACHECTL_H */
