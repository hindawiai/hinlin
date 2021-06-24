<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_CACHE_H
#घोषणा _ASM_IA64_CACHE_H


/*
 * Copyright (C) 1998-2000 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

/* Bytes per L1 (data) cache line.  */
#घोषणा L1_CACHE_SHIFT		CONFIG_IA64_L1_CACHE_SHIFT
#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#अगर_घोषित CONFIG_SMP
# define SMP_CACHE_SHIFT	L1_CACHE_SHIFT
# define SMP_CACHE_BYTES	L1_CACHE_BYTES
#अन्यथा
  /*
   * The "aligned" directive can only _increase_ alignment, so this is
   * safe and provides an easy way to aव्योम wasting space on a
   * uni-processor:
   */
# define SMP_CACHE_SHIFT	3
# define SMP_CACHE_BYTES	(1 << 3)
#पूर्ण_अगर

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#पूर्ण_अगर /* _ASM_IA64_CACHE_H */
