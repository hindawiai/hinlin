<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Coda fileप्रणाली -- Linux Minicache
 *
 * Copyright (C) 1989 - 1997 Carnegie Mellon University
 *
 * Carnegie Mellon University encourages users of this software to
 * contribute improvements to the Coda project. Contact Peter Braam
 * <coda@cs.cmu.edu>
 */

#अगर_अघोषित _CFSNC_HEADER_
#घोषणा _CFSNC_HEADER_

/* credential cache */
व्योम coda_cache_enter(काष्ठा inode *inode, पूर्णांक mask);
व्योम coda_cache_clear_inode(काष्ठा inode *);
व्योम coda_cache_clear_all(काष्ठा super_block *sb);
पूर्णांक coda_cache_check(काष्ठा inode *inode, पूर्णांक mask);

/* क्रम करोwncalls and attributes and lookups */
व्योम coda_flag_inode_children(काष्ठा inode *inode, पूर्णांक flag);

#पूर्ण_अगर /* _CFSNC_HEADER_ */
