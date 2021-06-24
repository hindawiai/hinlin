<शैली गुरु>
/*
 * include/यंत्र-xtensa/shmparam.h
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 */

#अगर_अघोषित _XTENSA_SHMPARAM_H
#घोषणा _XTENSA_SHMPARAM_H

/*
 * Xtensa can have variable size caches, and अगर
 * the size of single way is larger than the page size,
 * then we have to start worrying about cache aliasing
 * problems.
 */

#घोषणा SHMLBA	((PAGE_SIZE > DCACHE_WAY_SIZE)? PAGE_SIZE : DCACHE_WAY_SIZE)

#पूर्ण_अगर /* _XTENSA_SHMPARAM_H */
