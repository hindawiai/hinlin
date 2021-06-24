<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: cache.h,v 1.6 2004/03/11 18:08:05 lethal Exp $
 *
 * include/यंत्र-sh/cache.h
 *
 * Copyright 1999 (C) Niibe Yutaka
 * Copyright 2002, 2003 (C) Paul Mundt
 */
#अगर_अघोषित __ASM_SH_CACHE_H
#घोषणा __ASM_SH_CACHE_H

#समावेश <linux/init.h>
#समावेश <cpu/cache.h>

#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#अगर_अघोषित __ASSEMBLY__
काष्ठा cache_info अणु
	अचिन्हित पूर्णांक ways;		/* Number of cache ways */
	अचिन्हित पूर्णांक sets;		/* Number of cache sets */
	अचिन्हित पूर्णांक linesz;		/* Cache line size (bytes) */

	अचिन्हित पूर्णांक way_size;		/* sets * line size */

	/*
	 * way_incr is the address offset क्रम accessing the next way
	 * in memory mapped cache array ops.
	 */
	अचिन्हित पूर्णांक way_incr;
	अचिन्हित पूर्णांक entry_shअगरt;
	अचिन्हित पूर्णांक entry_mask;

	/*
	 * Compute a mask which selects the address bits which overlap between
	 * 1. those used to select the cache set during indexing
	 * 2. those in the physical page number.
	 */
	अचिन्हित पूर्णांक alias_mask;
	अचिन्हित पूर्णांक n_aliases;		/* Number of aliases */

	अचिन्हित दीर्घ flags;
पूर्ण;
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_SH_CACHE_H */
