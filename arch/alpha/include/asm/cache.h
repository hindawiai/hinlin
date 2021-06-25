<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-alpha/cache.h
 */
#अगर_अघोषित __ARCH_ALPHA_CACHE_H
#घोषणा __ARCH_ALPHA_CACHE_H


/* Bytes per L1 (data) cache line. */
#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EV6)
# define L1_CACHE_BYTES     64
# define L1_CACHE_SHIFT     6
#अन्यथा
/* Both EV4 and EV5 are ग_लिखो-through, पढ़ो-allocate,
   direct-mapped, physical.
*/
# define L1_CACHE_BYTES     32
# define L1_CACHE_SHIFT     5
#पूर्ण_अगर

#घोषणा SMP_CACHE_BYTES    L1_CACHE_BYTES

#पूर्ण_अगर
