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
 * Veritas fileप्रणाली driver - shared subroutines.
 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>

#समावेश "vxfs_extern.h"


अटल पूर्णांक		vxfs_पढ़ोpage(काष्ठा file *, काष्ठा page *);
अटल sector_t		vxfs_bmap(काष्ठा address_space *, sector_t);

स्थिर काष्ठा address_space_operations vxfs_aops = अणु
	.पढ़ोpage =		vxfs_पढ़ोpage,
	.bmap =			vxfs_bmap,
पूर्ण;

अंतरभूत व्योम
vxfs_put_page(काष्ठा page *pp)
अणु
	kunmap(pp);
	put_page(pp);
पूर्ण

/**
 * vxfs_get_page - पढ़ो a page पूर्णांकo memory.
 * @ip:		inode to पढ़ो from
 * @n:		page number
 *
 * Description:
 *   vxfs_get_page पढ़ोs the @n th page of @ip पूर्णांकo the pagecache.
 *
 * Returns:
 *   The wanted page on success, अन्यथा a शून्य poपूर्णांकer.
 */
काष्ठा page *
vxfs_get_page(काष्ठा address_space *mapping, u_दीर्घ n)
अणु
	काष्ठा page *			pp;

	pp = पढ़ो_mapping_page(mapping, n, शून्य);

	अगर (!IS_ERR(pp)) अणु
		kmap(pp);
		/** अगर (!PageChecked(pp)) **/
			/** vxfs_check_page(pp); **/
		अगर (PageError(pp))
			जाओ fail;
	पूर्ण
	
	वापस (pp);
		 
fail:
	vxfs_put_page(pp);
	वापस ERR_PTR(-EIO);
पूर्ण

/**
 * vxfs_bपढ़ो - पढ़ो buffer क्रम a give inode,block tuple
 * @ip:		inode
 * @block:	logical block
 *
 * Description:
 *   The vxfs_bपढ़ो function पढ़ोs block no @block  of
 *   @ip पूर्णांकo the buffercache.
 *
 * Returns:
 *   The resulting &काष्ठा buffer_head.
 */
काष्ठा buffer_head *
vxfs_bपढ़ो(काष्ठा inode *ip, पूर्णांक block)
अणु
	काष्ठा buffer_head	*bp;
	daddr_t			pblock;

	pblock = vxfs_bmap1(ip, block);
	bp = sb_bपढ़ो(ip->i_sb, pblock);

	वापस (bp);
पूर्ण

/**
 * vxfs_get_block - locate buffer क्रम given inode,block tuple 
 * @ip:		inode
 * @iblock:	logical block
 * @bp:		buffer skeleton
 * @create:	%TRUE अगर blocks may be newly allocated.
 *
 * Description:
 *   The vxfs_get_block function fills @bp with the right physical
 *   block and device number to perक्रमm a lowlevel पढ़ो/ग_लिखो on
 *   it.
 *
 * Returns:
 *   Zero on success, अन्यथा a negativ error code (-EIO).
 */
अटल पूर्णांक
vxfs_getblk(काष्ठा inode *ip, sector_t iblock,
	    काष्ठा buffer_head *bp, पूर्णांक create)
अणु
	daddr_t			pblock;

	pblock = vxfs_bmap1(ip, iblock);
	अगर (pblock != 0) अणु
		map_bh(bp, ip->i_sb, pblock);
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/**
 * vxfs_पढ़ोpage - पढ़ो one page synchronously पूर्णांकo the pagecache
 * @file:	file context (unused)
 * @page:	page frame to fill in.
 *
 * Description:
 *   The vxfs_पढ़ोpage routine पढ़ोs @page synchronously पूर्णांकo the
 *   pagecache.
 *
 * Returns:
 *   Zero on success, अन्यथा a negative error code.
 *
 * Locking status:
 *   @page is locked and will be unlocked.
 */
अटल पूर्णांक
vxfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, vxfs_getblk);
पूर्ण
 
/**
 * vxfs_bmap - perक्रमm logical to physical block mapping
 * @mapping:	logical to physical mapping to use
 * @block:	logical block (relative to @mapping).
 *
 * Description:
 *   Vxfs_bmap find out the corresponding phsical block to the
 *   @mapping, @block pair.
 *
 * Returns:
 *   Physical block number on success, अन्यथा Zero.
 *
 * Locking status:
 *   We are under the bkl.
 */
अटल sector_t
vxfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, vxfs_getblk);
पूर्ण
