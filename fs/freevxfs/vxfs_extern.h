<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#अगर_अघोषित _VXFS_EXTERN_H_
#घोषणा _VXFS_EXTERN_H_

/*
 * Veritas fileप्रणाली driver - बाह्यal prototypes.
 *
 * This file contains prototypes क्रम all vxfs functions used
 * outside their respective source files.
 */


काष्ठा kmem_cache;
काष्ठा super_block;
काष्ठा vxfs_inode_info;
काष्ठा inode;


/* vxfs_bmap.c */
बाह्य daddr_t			vxfs_bmap1(काष्ठा inode *, दीर्घ);

/* vxfs_fshead.c */
बाह्य पूर्णांक			vxfs_पढ़ो_fshead(काष्ठा super_block *);

/* vxfs_inode.c */
बाह्य स्थिर काष्ठा address_space_operations vxfs_immed_aops;
बाह्य व्योम			vxfs_dumpi(काष्ठा vxfs_inode_info *, ino_t);
बाह्य काष्ठा inode		*vxfs_blkiget(काष्ठा super_block *, u_दीर्घ, ino_t);
बाह्य काष्ठा inode		*vxfs_stiget(काष्ठा super_block *, ino_t);
बाह्य काष्ठा inode		*vxfs_iget(काष्ठा super_block *, ino_t);
बाह्य व्योम			vxfs_evict_inode(काष्ठा inode *);

/* vxfs_lookup.c */
बाह्य स्थिर काष्ठा inode_operations	vxfs_dir_inode_ops;
बाह्य स्थिर काष्ठा file_operations	vxfs_dir_operations;

/* vxfs_olt.c */
बाह्य पूर्णांक			vxfs_पढ़ो_olt(काष्ठा super_block *, u_दीर्घ);

/* vxfs_subr.c */
बाह्य स्थिर काष्ठा address_space_operations vxfs_aops;
बाह्य काष्ठा page *		vxfs_get_page(काष्ठा address_space *, u_दीर्घ);
बाह्य व्योम			vxfs_put_page(काष्ठा page *);
बाह्य काष्ठा buffer_head *	vxfs_bपढ़ो(काष्ठा inode *, पूर्णांक);

#पूर्ण_अगर /* _VXFS_EXTERN_H_ */
