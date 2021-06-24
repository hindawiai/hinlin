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
 */

/*
 * Veritas fileप्रणाली driver - support क्रम 'immed' inodes.
 */
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

#समावेश "vxfs.h"
#समावेश "vxfs_extern.h"
#समावेश "vxfs_inode.h"


अटल पूर्णांक	vxfs_immed_पढ़ोpage(काष्ठा file *, काष्ठा page *);

/*
 * Address space operations क्रम immed files and directories.
 */
स्थिर काष्ठा address_space_operations vxfs_immed_aops = अणु
	.पढ़ोpage =		vxfs_immed_पढ़ोpage,
पूर्ण;

/**
 * vxfs_immed_पढ़ोpage - पढ़ो part of an immed inode पूर्णांकo pagecache
 * @file:	file context (unused)
 * @page:	page frame to fill in.
 *
 * Description:
 *   vxfs_immed_पढ़ोpage पढ़ोs a part of the immed area of the
 *   file that hosts @pp पूर्णांकo the pagecache.
 *
 * Returns:
 *   Zero on success, अन्यथा a negative error code.
 *
 * Locking status:
 *   @page is locked and will be unlocked.
 */
अटल पूर्णांक
vxfs_immed_पढ़ोpage(काष्ठा file *fp, काष्ठा page *pp)
अणु
	काष्ठा vxfs_inode_info	*vip = VXFS_INO(pp->mapping->host);
	u_पूर्णांक64_t	offset = (u_पूर्णांक64_t)pp->index << PAGE_SHIFT;
	caddr_t		kaddr;

	kaddr = kmap(pp);
	स_नकल(kaddr, vip->vii_immed.vi_immed + offset, PAGE_SIZE);
	kunmap(pp);
	
	flush_dcache_page(pp);
	SetPageUptodate(pp);
        unlock_page(pp);

	वापस 0;
पूर्ण
