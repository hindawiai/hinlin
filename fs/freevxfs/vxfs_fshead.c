<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
 * Copyright (c) 2016 Krzysztof Blaszkowski
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
 * Veritas fileप्रणाली driver - fileset header routines.
 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "vxfs.h"
#समावेश "vxfs_inode.h"
#समावेश "vxfs_extern.h"
#समावेश "vxfs_fshead.h"


#अगर_घोषित DIAGNOSTIC
अटल व्योम
vxfs_dumpfsh(काष्ठा vxfs_fsh *fhp)
अणु
	prपूर्णांकk("\n\ndumping fileset header:\n");
	prपूर्णांकk("----------------------------\n");
	prपूर्णांकk("version: %u\n", fhp->fsh_version);
	prपूर्णांकk("fsindex: %u\n", fhp->fsh_fsindex);
	prपूर्णांकk("iauino: %u\tninodes:%u\n",
			fhp->fsh_iauino, fhp->fsh_ninodes);
	prपूर्णांकk("maxinode: %u\tlctino: %u\n",
			fhp->fsh_maxinode, fhp->fsh_lctino);
	prपूर्णांकk("nau: %u\n", fhp->fsh_nau);
	prपूर्णांकk("ilistino[0]: %u\tilistino[1]: %u\n",
			fhp->fsh_ilistino[0], fhp->fsh_ilistino[1]);
पूर्ण
#पूर्ण_अगर

/**
 * vxfs_getfsh - पढ़ो fileset header पूर्णांकo memory
 * @ip:		the (fake) fileset header inode
 * @which:	0 क्रम the काष्ठाural, 1 क्रम the primary fsh.
 *
 * Description:
 *   vxfs_getfsh पढ़ोs either the काष्ठाural or primary fileset header
 *   described by @ip पूर्णांकo memory.
 *
 * Returns:
 *   The fileset header काष्ठाure on success, अन्यथा Zero.
 */
अटल काष्ठा vxfs_fsh *
vxfs_getfsh(काष्ठा inode *ip, पूर्णांक which)
अणु
	काष्ठा buffer_head		*bp;

	bp = vxfs_bपढ़ो(ip, which);
	अगर (bp) अणु
		काष्ठा vxfs_fsh		*fhp;

		अगर (!(fhp = kदो_स्मृति(माप(*fhp), GFP_KERNEL)))
			जाओ out;
		स_नकल(fhp, bp->b_data, माप(*fhp));

		put_bh(bp);
		वापस (fhp);
	पूर्ण
out:
	brअन्यथा(bp);
	वापस शून्य;
पूर्ण

/**
 * vxfs_पढ़ो_fshead - पढ़ो the fileset headers
 * @sbp:	superblock to which the fileset beदीर्घs
 *
 * Description:
 *   vxfs_पढ़ो_fshead will fill the inode and काष्ठाural inode list in @sb.
 *
 * Returns:
 *   Zero on success, अन्यथा a negative error code (-EINVAL).
 */
पूर्णांक
vxfs_पढ़ो_fshead(काष्ठा super_block *sbp)
अणु
	काष्ठा vxfs_sb_info		*infp = VXFS_SBI(sbp);
	काष्ठा vxfs_fsh			*pfp, *sfp;
	काष्ठा vxfs_inode_info		*vip;

	infp->vsi_fship = vxfs_blkiget(sbp, infp->vsi_iext, infp->vsi_fshino);
	अगर (!infp->vsi_fship) अणु
		prपूर्णांकk(KERN_ERR "vxfs: unable to read fsh inode\n");
		वापस -EINVAL;
	पूर्ण

	vip = VXFS_INO(infp->vsi_fship);
	अगर (!VXFS_ISFSH(vip)) अणु
		prपूर्णांकk(KERN_ERR "vxfs: fsh list inode is of wrong type (%x)\n",
				vip->vii_mode & VXFS_TYPE_MASK); 
		जाओ out_iput_fship;
	पूर्ण

#अगर_घोषित DIAGNOSTIC
	prपूर्णांकk("vxfs: fsh inode dump:\n");
	vxfs_dumpi(vip, infp->vsi_fshino);
#पूर्ण_अगर

	sfp = vxfs_getfsh(infp->vsi_fship, 0);
	अगर (!sfp) अणु
		prपूर्णांकk(KERN_ERR "vxfs: unable to get structural fsh\n");
		जाओ out_iput_fship;
	पूर्ण 

#अगर_घोषित DIAGNOSTIC
	vxfs_dumpfsh(sfp);
#पूर्ण_अगर

	pfp = vxfs_getfsh(infp->vsi_fship, 1);
	अगर (!pfp) अणु
		prपूर्णांकk(KERN_ERR "vxfs: unable to get primary fsh\n");
		जाओ out_मुक्त_sfp;
	पूर्ण

#अगर_घोषित DIAGNOSTIC
	vxfs_dumpfsh(pfp);
#पूर्ण_अगर

	infp->vsi_stilist = vxfs_blkiget(sbp, infp->vsi_iext,
			fs32_to_cpu(infp, sfp->fsh_ilistino[0]));
	अगर (!infp->vsi_stilist) अणु
		prपूर्णांकk(KERN_ERR "vxfs: unable to get structural list inode\n");
		जाओ out_मुक्त_pfp;
	पूर्ण
	अगर (!VXFS_ISILT(VXFS_INO(infp->vsi_stilist))) अणु
		prपूर्णांकk(KERN_ERR "vxfs: structural list inode is of wrong type (%x)\n",
				VXFS_INO(infp->vsi_stilist)->vii_mode & VXFS_TYPE_MASK); 
		जाओ out_iput_stilist;
	पूर्ण

	infp->vsi_ilist = vxfs_stiget(sbp, fs32_to_cpu(infp, pfp->fsh_ilistino[0]));
	अगर (!infp->vsi_ilist) अणु
		prपूर्णांकk(KERN_ERR "vxfs: unable to get inode list inode\n");
		जाओ out_iput_stilist;
	पूर्ण
	अगर (!VXFS_ISILT(VXFS_INO(infp->vsi_ilist))) अणु
		prपूर्णांकk(KERN_ERR "vxfs: inode list inode is of wrong type (%x)\n",
				VXFS_INO(infp->vsi_ilist)->vii_mode & VXFS_TYPE_MASK);
		जाओ out_iput_ilist;
	पूर्ण

	kमुक्त(pfp);
	kमुक्त(sfp);
	वापस 0;

 out_iput_ilist:
 	iput(infp->vsi_ilist);
 out_iput_stilist:
 	iput(infp->vsi_stilist);
 out_मुक्त_pfp:
	kमुक्त(pfp);
 out_मुक्त_sfp:
 	kमुक्त(sfp);
 out_iput_fship:
	iput(infp->vsi_fship);
	वापस -EINVAL;
पूर्ण
