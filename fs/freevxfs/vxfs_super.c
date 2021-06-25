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
 * Veritas fileप्रणाली driver - superblock related routines.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <linux/blkdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/vfs.h>
#समावेश <linux/mount.h>

#समावेश "vxfs.h"
#समावेश "vxfs_extern.h"
#समावेश "vxfs_dir.h"
#समावेश "vxfs_inode.h"


MODULE_AUTHOR("Christoph Hellwig, Krzysztof Blaszkowski");
MODULE_DESCRIPTION("Veritas Filesystem (VxFS) driver");
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा kmem_cache *vxfs_inode_cachep;

/**
 * vxfs_put_super - मुक्त superblock resources
 * @sbp:	VFS superblock.
 *
 * Description:
 *   vxfs_put_super मुक्तs all resources allocated क्रम @sbp
 *   after the last instance of the fileप्रणाली is unmounted.
 */

अटल व्योम
vxfs_put_super(काष्ठा super_block *sbp)
अणु
	काष्ठा vxfs_sb_info	*infp = VXFS_SBI(sbp);

	iput(infp->vsi_fship);
	iput(infp->vsi_ilist);
	iput(infp->vsi_stilist);

	brअन्यथा(infp->vsi_bp);
	kमुक्त(infp);
पूर्ण

/**
 * vxfs_statfs - get fileप्रणाली inक्रमmation
 * @dentry:	VFS dentry to locate superblock
 * @bufp:	output buffer
 *
 * Description:
 *   vxfs_statfs fills the statfs buffer @bufp with inक्रमmation
 *   about the fileप्रणाली described by @dentry.
 *
 * Returns:
 *   Zero.
 *
 * Locking:
 *   No locks held.
 *
 * Notes:
 *   This is everything but complete...
 */
अटल पूर्णांक
vxfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *bufp)
अणु
	काष्ठा vxfs_sb_info		*infp = VXFS_SBI(dentry->d_sb);
	काष्ठा vxfs_sb *raw_sb = infp->vsi_raw;

	bufp->f_type = VXFS_SUPER_MAGIC;
	bufp->f_bsize = dentry->d_sb->s_blocksize;
	bufp->f_blocks = fs32_to_cpu(infp, raw_sb->vs_dsize);
	bufp->f_bमुक्त = fs32_to_cpu(infp, raw_sb->vs_मुक्त);
	bufp->f_bavail = 0;
	bufp->f_files = 0;
	bufp->f_fमुक्त = fs32_to_cpu(infp, raw_sb->vs_अगरree);
	bufp->f_namelen = VXFS_NAMELEN;

	वापस 0;
पूर्ण

अटल पूर्णांक vxfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल काष्ठा inode *vxfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा vxfs_inode_info *vi;

	vi = kmem_cache_alloc(vxfs_inode_cachep, GFP_KERNEL);
	अगर (!vi)
		वापस शून्य;
	inode_init_once(&vi->vfs_inode);
	वापस &vi->vfs_inode;
पूर्ण

अटल व्योम vxfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(vxfs_inode_cachep, VXFS_INO(inode));
पूर्ण

अटल स्थिर काष्ठा super_operations vxfs_super_ops = अणु
	.alloc_inode		= vxfs_alloc_inode,
	.मुक्त_inode		= vxfs_मुक्त_inode,
	.evict_inode		= vxfs_evict_inode,
	.put_super		= vxfs_put_super,
	.statfs			= vxfs_statfs,
	.remount_fs		= vxfs_remount,
पूर्ण;

अटल पूर्णांक vxfs_try_sb_magic(काष्ठा super_block *sbp, पूर्णांक silent,
		अचिन्हित blk, __fs32 magic)
अणु
	काष्ठा buffer_head *bp;
	काष्ठा vxfs_sb *rsbp;
	काष्ठा vxfs_sb_info *infp = VXFS_SBI(sbp);
	पूर्णांक rc = -ENOMEM;

	bp = sb_bपढ़ो(sbp, blk);
	करो अणु
		अगर (!bp || !buffer_mapped(bp)) अणु
			अगर (!silent) अणु
				prपूर्णांकk(KERN_WARNING
					"vxfs: unable to read disk superblock at %u\n",
					blk);
			पूर्ण
			अवरोध;
		पूर्ण

		rc = -EINVAL;
		rsbp = (काष्ठा vxfs_sb *)bp->b_data;
		अगर (rsbp->vs_magic != magic) अणु
			अगर (!silent)
				prपूर्णांकk(KERN_NOTICE
					"vxfs: WRONG superblock magic %08x at %u\n",
					rsbp->vs_magic, blk);
			अवरोध;
		पूर्ण

		rc = 0;
		infp->vsi_raw = rsbp;
		infp->vsi_bp = bp;
	पूर्ण जबतक (0);

	अगर (rc) अणु
		infp->vsi_raw = शून्य;
		infp->vsi_bp = शून्य;
		brअन्यथा(bp);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * vxfs_पढ़ो_super - पढ़ो superblock पूर्णांकo memory and initialize fileप्रणाली
 * @sbp:		VFS superblock (to fill)
 * @dp:			fs निजी mount data
 * @silent:		करो not complain loudly when sth is wrong
 *
 * Description:
 *   We are called on the first mount of a fileप्रणाली to पढ़ो the
 *   superblock पूर्णांकo memory and करो some basic setup.
 *
 * Returns:
 *   The superblock on success, अन्यथा %शून्य.
 *
 * Locking:
 *   We are under @sbp->s_lock.
 */
अटल पूर्णांक vxfs_fill_super(काष्ठा super_block *sbp, व्योम *dp, पूर्णांक silent)
अणु
	काष्ठा vxfs_sb_info	*infp;
	काष्ठा vxfs_sb		*rsbp;
	u_दीर्घ			bsize;
	काष्ठा inode *root;
	पूर्णांक ret = -EINVAL;
	u32 j;

	sbp->s_flags |= SB_RDONLY;

	infp = kzalloc(माप(*infp), GFP_KERNEL);
	अगर (!infp) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to allocate incore superblock\n");
		वापस -ENOMEM;
	पूर्ण

	bsize = sb_min_blocksize(sbp, BLOCK_SIZE);
	अगर (!bsize) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to set blocksize\n");
		जाओ out;
	पूर्ण

	sbp->s_op = &vxfs_super_ops;
	sbp->s_fs_info = infp;
	sbp->s_समय_min = 0;
	sbp->s_समय_max = U32_MAX;

	अगर (!vxfs_try_sb_magic(sbp, silent, 1,
			(__क्रमce __fs32)cpu_to_le32(VXFS_SUPER_MAGIC))) अणु
		/* Unixware, x86 */
		infp->byte_order = VXFS_BO_LE;
	पूर्ण अन्यथा अगर (!vxfs_try_sb_magic(sbp, silent, 8,
			(__क्रमce __fs32)cpu_to_be32(VXFS_SUPER_MAGIC))) अणु
		/* HP-UX, parisc */
		infp->byte_order = VXFS_BO_BE;
	पूर्ण अन्यथा अणु
		अगर (!silent)
			prपूर्णांकk(KERN_NOTICE "vxfs: can't find superblock.\n");
		जाओ out;
	पूर्ण

	rsbp = infp->vsi_raw;
	j = fs32_to_cpu(infp, rsbp->vs_version);
	अगर ((j < 2 || j > 4) && !silent) अणु
		prपूर्णांकk(KERN_NOTICE "vxfs: unsupported VxFS version (%d)\n", j);
		जाओ out;
	पूर्ण

#अगर_घोषित DIAGNOSTIC
	prपूर्णांकk(KERN_DEBUG "vxfs: supported VxFS version (%d)\n", j);
	prपूर्णांकk(KERN_DEBUG "vxfs: blocksize: %d\n",
		fs32_to_cpu(infp, rsbp->vs_bsize));
#पूर्ण_अगर

	sbp->s_magic = fs32_to_cpu(infp, rsbp->vs_magic);

	infp->vsi_oltext = fs32_to_cpu(infp, rsbp->vs_oltext[0]);
	infp->vsi_oltsize = fs32_to_cpu(infp, rsbp->vs_oltsize);

	j = fs32_to_cpu(infp, rsbp->vs_bsize);
	अगर (!sb_set_blocksize(sbp, j)) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to set final block size\n");
		जाओ out;
	पूर्ण

	अगर (vxfs_पढ़ो_olt(sbp, bsize)) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to read olt\n");
		जाओ out;
	पूर्ण

	अगर (vxfs_पढ़ो_fshead(sbp)) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to read fshead\n");
		जाओ out;
	पूर्ण

	root = vxfs_iget(sbp, VXFS_ROOT_INO);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ out;
	पूर्ण
	sbp->s_root = d_make_root(root);
	अगर (!sbp->s_root) अणु
		prपूर्णांकk(KERN_WARNING "vxfs: unable to get root dentry.\n");
		जाओ out_मुक्त_ilist;
	पूर्ण

	वापस 0;
	
out_मुक्त_ilist:
	iput(infp->vsi_fship);
	iput(infp->vsi_ilist);
	iput(infp->vsi_stilist);
out:
	brअन्यथा(infp->vsi_bp);
	kमुक्त(infp);
	वापस ret;
पूर्ण

/*
 * The usual module blurb.
 */
अटल काष्ठा dentry *vxfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, vxfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type vxfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "vxfs",
	.mount		= vxfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("vxfs"); /* makes mount -t vxfs स्वतःload the module */
MODULE_ALIAS("vxfs");

अटल पूर्णांक __init
vxfs_init(व्योम)
अणु
	पूर्णांक rv;

	vxfs_inode_cachep = kmem_cache_create_usercopy("vxfs_inode",
			माप(काष्ठा vxfs_inode_info), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD,
			दुरत्व(काष्ठा vxfs_inode_info, vii_immed.vi_immed),
			माप_field(काष्ठा vxfs_inode_info,
				vii_immed.vi_immed),
			शून्य);
	अगर (!vxfs_inode_cachep)
		वापस -ENOMEM;
	rv = रेजिस्टर_fileप्रणाली(&vxfs_fs_type);
	अगर (rv < 0)
		kmem_cache_destroy(vxfs_inode_cachep);
	वापस rv;
पूर्ण

अटल व्योम __निकास
vxfs_cleanup(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&vxfs_fs_type);
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(vxfs_inode_cachep);
पूर्ण

module_init(vxfs_init);
module_निकास(vxfs_cleanup);
