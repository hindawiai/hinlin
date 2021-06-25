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
 * Veritas fileप्रणाली driver - inode routines.
 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>

#समावेश "vxfs.h"
#समावेश "vxfs_inode.h"
#समावेश "vxfs_extern.h"


#अगर_घोषित DIAGNOSTIC
/*
 * Dump inode contents (partially).
 */
व्योम
vxfs_dumpi(काष्ठा vxfs_inode_info *vip, ino_t ino)
अणु
	prपूर्णांकk(KERN_DEBUG "\n\n");
	अगर (ino)
		prपूर्णांकk(KERN_DEBUG "dumping vxfs inode %ld\n", ino);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "dumping unknown vxfs inode\n");

	prपूर्णांकk(KERN_DEBUG "---------------------------\n");
	prपूर्णांकk(KERN_DEBUG "mode is %x\n", vip->vii_mode);
	prपूर्णांकk(KERN_DEBUG "nlink:%u, uid:%u, gid:%u\n",
			vip->vii_nlink, vip->vii_uid, vip->vii_gid);
	prपूर्णांकk(KERN_DEBUG "size:%Lx, blocks:%u\n",
			vip->vii_size, vip->vii_blocks);
	prपूर्णांकk(KERN_DEBUG "orgtype:%u\n", vip->vii_orgtype);
पूर्ण
#पूर्ण_अगर

/**
 * vxfs_transmod - mode क्रम a VxFS inode
 * @vip:	VxFS inode
 *
 * Description:
 *  vxfs_transmod वापसs a Linux mode_t क्रम a given
 *  VxFS inode काष्ठाure.
 */
अटल __अंतरभूत__ umode_t
vxfs_transmod(काष्ठा vxfs_inode_info *vip)
अणु
	umode_t			ret = vip->vii_mode & ~VXFS_TYPE_MASK;

	अगर (VXFS_ISFIFO(vip))
		ret |= S_IFIFO;
	अगर (VXFS_ISCHR(vip))
		ret |= S_IFCHR;
	अगर (VXFS_ISसूची(vip))
		ret |= S_IFसूची;
	अगर (VXFS_ISBLK(vip))
		ret |= S_IFBLK;
	अगर (VXFS_ISLNK(vip))
		ret |= S_IFLNK;
	अगर (VXFS_ISREG(vip))
		ret |= S_IFREG;
	अगर (VXFS_ISSOC(vip))
		ret |= S_IFSOCK;

	वापस (ret);
पूर्ण

अटल अंतरभूत व्योम dip2vip_cpy(काष्ठा vxfs_sb_info *sbi,
		काष्ठा vxfs_inode_info *vip, काष्ठा vxfs_dinode *dip)
अणु
	काष्ठा inode *inode = &vip->vfs_inode;

	vip->vii_mode = fs32_to_cpu(sbi, dip->vdi_mode);
	vip->vii_nlink = fs32_to_cpu(sbi, dip->vdi_nlink);
	vip->vii_uid = fs32_to_cpu(sbi, dip->vdi_uid);
	vip->vii_gid = fs32_to_cpu(sbi, dip->vdi_gid);
	vip->vii_size = fs64_to_cpu(sbi, dip->vdi_size);
	vip->vii_aसमय = fs32_to_cpu(sbi, dip->vdi_aसमय);
	vip->vii_auसमय = fs32_to_cpu(sbi, dip->vdi_auसमय);
	vip->vii_mसमय = fs32_to_cpu(sbi, dip->vdi_mसमय);
	vip->vii_muसमय = fs32_to_cpu(sbi, dip->vdi_muसमय);
	vip->vii_स_समय = fs32_to_cpu(sbi, dip->vdi_स_समय);
	vip->vii_cuसमय = fs32_to_cpu(sbi, dip->vdi_cuसमय);
	vip->vii_orgtype = dip->vdi_orgtype;

	vip->vii_blocks = fs32_to_cpu(sbi, dip->vdi_blocks);
	vip->vii_gen = fs32_to_cpu(sbi, dip->vdi_gen);

	अगर (VXFS_ISसूची(vip))
		vip->vii_करोtकरोt = fs32_to_cpu(sbi, dip->vdi_करोtकरोt);
	अन्यथा अगर (!VXFS_ISREG(vip) && !VXFS_ISLNK(vip))
		vip->vii_rdev = fs32_to_cpu(sbi, dip->vdi_rdev);

	/* करोn't endian swap the fields that dअगरfer by orgtype */
	स_नकल(&vip->vii_org, &dip->vdi_org, माप(vip->vii_org));

	inode->i_mode = vxfs_transmod(vip);
	i_uid_ग_लिखो(inode, (uid_t)vip->vii_uid);
	i_gid_ग_लिखो(inode, (gid_t)vip->vii_gid);

	set_nlink(inode, vip->vii_nlink);
	inode->i_size = vip->vii_size;

	inode->i_aसमय.tv_sec = vip->vii_aसमय;
	inode->i_स_समय.tv_sec = vip->vii_स_समय;
	inode->i_mसमय.tv_sec = vip->vii_mसमय;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;
	inode->i_mसमय.tv_nsec = 0;

	inode->i_blocks = vip->vii_blocks;
	inode->i_generation = vip->vii_gen;
पूर्ण

/**
 * vxfs_blkiget - find inode based on extent #
 * @sbp:	superblock of the fileप्रणाली we search in
 * @extent:	number of the extent to search
 * @ino:	inode number to search
 *
 * Description:
 *  vxfs_blkiget searches inode @ino in the fileप्रणाली described by
 *  @sbp in the extent @extent.
 *  Returns the matching VxFS inode on success, अन्यथा a शून्य poपूर्णांकer.
 *
 * NOTE:
 *  While __vxfs_iget uses the pagecache vxfs_blkiget uses the
 *  buffercache.  This function should not be used outside the
 *  पढ़ो_super() method, otherwise the data may be incoherent.
 */
काष्ठा inode *
vxfs_blkiget(काष्ठा super_block *sbp, u_दीर्घ extent, ino_t ino)
अणु
	काष्ठा buffer_head		*bp;
	काष्ठा inode			*inode;
	u_दीर्घ				block, offset;

	inode = new_inode(sbp);
	अगर (!inode)
		वापस शून्य;
	inode->i_ino = get_next_ino();

	block = extent + ((ino * VXFS_ISIZE) / sbp->s_blocksize);
	offset = ((ino % (sbp->s_blocksize / VXFS_ISIZE)) * VXFS_ISIZE);
	bp = sb_bपढ़ो(sbp, block);

	अगर (bp && buffer_mapped(bp)) अणु
		काष्ठा vxfs_inode_info	*vip = VXFS_INO(inode);
		काष्ठा vxfs_dinode	*dip;

		dip = (काष्ठा vxfs_dinode *)(bp->b_data + offset);
		dip2vip_cpy(VXFS_SBI(sbp), vip, dip);
		vip->vfs_inode.i_mapping->a_ops = &vxfs_aops;
#अगर_घोषित DIAGNOSTIC
		vxfs_dumpi(vip, ino);
#पूर्ण_अगर
		brअन्यथा(bp);
		वापस inode;
	पूर्ण

	prपूर्णांकk(KERN_WARNING "vxfs: unable to read block %ld\n", block);
	brअन्यथा(bp);
	iput(inode);
	वापस शून्य;
पूर्ण

/**
 * __vxfs_iget - generic find inode facility
 * @ilistp:		inode list
 * @vip:		VxFS inode to fill in
 * @ino:		inode number
 *
 * Description:
 *  Search the क्रम inode number @ino in the fileप्रणाली
 *  described by @sbp.  Use the specअगरied inode table (@ilistp).
 *  Returns the matching inode on success, अन्यथा an error code.
 */
अटल पूर्णांक
__vxfs_iget(काष्ठा inode *ilistp, काष्ठा vxfs_inode_info *vip, ino_t ino)
अणु
	काष्ठा page			*pp;
	u_दीर्घ				offset;

	offset = (ino % (PAGE_SIZE / VXFS_ISIZE)) * VXFS_ISIZE;
	pp = vxfs_get_page(ilistp->i_mapping, ino * VXFS_ISIZE / PAGE_SIZE);

	अगर (!IS_ERR(pp)) अणु
		काष्ठा vxfs_dinode	*dip;
		caddr_t			kaddr = (अक्षर *)page_address(pp);

		dip = (काष्ठा vxfs_dinode *)(kaddr + offset);
		dip2vip_cpy(VXFS_SBI(ilistp->i_sb), vip, dip);
		vip->vfs_inode.i_mapping->a_ops = &vxfs_aops;
#अगर_घोषित DIAGNOSTIC
		vxfs_dumpi(vip, ino);
#पूर्ण_अगर
		vxfs_put_page(pp);
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_WARNING "vxfs: error on page 0x%p for inode %ld\n",
		pp, (अचिन्हित दीर्घ)ino);
	वापस PTR_ERR(pp);
पूर्ण

/**
 * vxfs_stiget - find inode using the काष्ठाural inode list
 * @sbp:	VFS superblock
 * @ino:	inode #
 *
 * Description:
 *  Find inode @ino in the fileप्रणाली described by @sbp using
 *  the काष्ठाural inode list.
 *  Returns the matching inode on success, अन्यथा a शून्य poपूर्णांकer.
 */
काष्ठा inode *
vxfs_stiget(काष्ठा super_block *sbp, ino_t ino)
अणु
	काष्ठा inode *inode;
	पूर्णांक error;

	inode = new_inode(sbp);
	अगर (!inode)
		वापस शून्य;
	inode->i_ino = get_next_ino();

	error = __vxfs_iget(VXFS_SBI(sbp)->vsi_stilist, VXFS_INO(inode), ino);
	अगर (error) अणु
		iput(inode);
		वापस शून्य;
	पूर्ण

	वापस inode;
पूर्ण

/**
 * vxfs_iget - get an inode
 * @sbp:	the superblock to get the inode क्रम
 * @ino:	the number of the inode to get
 *
 * Description:
 *  vxfs_पढ़ो_inode creates an inode, पढ़ोs the disk inode क्रम @ino and fills
 *  in all relevant fields in the new inode.
 */
काष्ठा inode *
vxfs_iget(काष्ठा super_block *sbp, ino_t ino)
अणु
	काष्ठा vxfs_inode_info		*vip;
	स्थिर काष्ठा address_space_operations	*aops;
	काष्ठा inode *ip;
	पूर्णांक error;

	ip = iget_locked(sbp, ino);
	अगर (!ip)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(ip->i_state & I_NEW))
		वापस ip;

	vip = VXFS_INO(ip);
	error = __vxfs_iget(VXFS_SBI(sbp)->vsi_ilist, vip, ino);
	अगर (error) अणु
		iget_failed(ip);
		वापस ERR_PTR(error);
	पूर्ण

	अगर (VXFS_ISIMMED(vip))
		aops = &vxfs_immed_aops;
	अन्यथा
		aops = &vxfs_aops;

	अगर (S_ISREG(ip->i_mode)) अणु
		ip->i_fop = &generic_ro_fops;
		ip->i_mapping->a_ops = aops;
	पूर्ण अन्यथा अगर (S_ISसूची(ip->i_mode)) अणु
		ip->i_op = &vxfs_dir_inode_ops;
		ip->i_fop = &vxfs_dir_operations;
		ip->i_mapping->a_ops = aops;
	पूर्ण अन्यथा अगर (S_ISLNK(ip->i_mode)) अणु
		अगर (!VXFS_ISIMMED(vip)) अणु
			ip->i_op = &page_symlink_inode_operations;
			inode_nohighmem(ip);
			ip->i_mapping->a_ops = &vxfs_aops;
		पूर्ण अन्यथा अणु
			ip->i_op = &simple_symlink_inode_operations;
			ip->i_link = vip->vii_immed.vi_immed;
			nd_terminate_link(ip->i_link, ip->i_size,
					  माप(vip->vii_immed.vi_immed) - 1);
		पूर्ण
	पूर्ण अन्यथा
		init_special_inode(ip, ip->i_mode, old_decode_dev(vip->vii_rdev));

	unlock_new_inode(ip);
	वापस ip;
पूर्ण

/**
 * vxfs_evict_inode - हटाओ inode from मुख्य memory
 * @ip:		inode to discard.
 *
 * Description:
 *  vxfs_evict_inode() is called on the final iput and मुक्तs the निजी
 *  inode area.
 */
व्योम
vxfs_evict_inode(काष्ठा inode *ip)
अणु
	truncate_inode_pages_final(&ip->i_data);
	clear_inode(ip);
पूर्ण
