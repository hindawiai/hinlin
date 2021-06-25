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
 * Veritas fileप्रणाली driver - object location table support.
 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>

#समावेश "vxfs.h"
#समावेश "vxfs_olt.h"
#समावेश "vxfs_extern.h"


अटल अंतरभूत व्योम
vxfs_get_fshead(काष्ठा vxfs_oltfshead *fshp, काष्ठा vxfs_sb_info *infp)
अणु
	BUG_ON(infp->vsi_fshino);
	infp->vsi_fshino = fs32_to_cpu(infp, fshp->olt_fsino[0]);
पूर्ण

अटल अंतरभूत व्योम
vxfs_get_ilist(काष्ठा vxfs_oltilist *ilistp, काष्ठा vxfs_sb_info *infp)
अणु
	BUG_ON(infp->vsi_iext);
	infp->vsi_iext = fs32_to_cpu(infp, ilistp->olt_iext[0]);
पूर्ण

अटल अंतरभूत u_दीर्घ
vxfs_oblock(काष्ठा super_block *sbp, daddr_t block, u_दीर्घ bsize)
अणु
	BUG_ON(sbp->s_blocksize % bsize);
	वापस (block * (sbp->s_blocksize / bsize));
पूर्ण


/**
 * vxfs_पढ़ो_olt - पढ़ो olt
 * @sbp:	superblock of the fileप्रणाली
 * @bsize:	blocksize of the fileप्रणाली
 *
 * Description:
 *   vxfs_पढ़ो_olt पढ़ोs the olt of the fileप्रणाली described by @sbp
 *   पूर्णांकo मुख्य memory and करोes some basic setup.
 *
 * Returns:
 *   Zero on success, अन्यथा a negative error code.
 */
पूर्णांक
vxfs_पढ़ो_olt(काष्ठा super_block *sbp, u_दीर्घ bsize)
अणु
	काष्ठा vxfs_sb_info	*infp = VXFS_SBI(sbp);
	काष्ठा buffer_head	*bp;
	काष्ठा vxfs_olt		*op;
	अक्षर			*oaddr, *eaddr;

	bp = sb_bपढ़ो(sbp, vxfs_oblock(sbp, infp->vsi_oltext, bsize));
	अगर (!bp || !bp->b_data)
		जाओ fail;

	op = (काष्ठा vxfs_olt *)bp->b_data;
	अगर (fs32_to_cpu(infp, op->olt_magic) != VXFS_OLT_MAGIC) अणु
		prपूर्णांकk(KERN_NOTICE "vxfs: ivalid olt magic number\n");
		जाओ fail;
	पूर्ण

	/*
	 * It is in theory possible that vsi_oltsize is > 1.
	 * I've not seen any such filesystem yet and I'm lazy..  --hch
	 */
	अगर (infp->vsi_oltsize > 1) अणु
		prपूर्णांकk(KERN_NOTICE "vxfs: oltsize > 1 detected.\n");
		prपूर्णांकk(KERN_NOTICE "vxfs: please notify hch@infradead.org\n");
		जाओ fail;
	पूर्ण

	oaddr = bp->b_data + fs32_to_cpu(infp, op->olt_size);
	eaddr = bp->b_data + (infp->vsi_oltsize * sbp->s_blocksize);

	जबतक (oaddr < eaddr) अणु
		काष्ठा vxfs_oltcommon	*ocp =
			(काष्ठा vxfs_oltcommon *)oaddr;
		
		चयन (fs32_to_cpu(infp, ocp->olt_type)) अणु
		हाल VXFS_OLT_FSHEAD:
			vxfs_get_fshead((काष्ठा vxfs_oltfshead *)oaddr, infp);
			अवरोध;
		हाल VXFS_OLT_ILIST:
			vxfs_get_ilist((काष्ठा vxfs_oltilist *)oaddr, infp);
			अवरोध;
		पूर्ण

		oaddr += fs32_to_cpu(infp, ocp->olt_size);
	पूर्ण

	brअन्यथा(bp);
	वापस (infp->vsi_fshino && infp->vsi_iext) ? 0 : -EINVAL;

fail:
	brअन्यथा(bp);
	वापस -EINVAL;
पूर्ण
