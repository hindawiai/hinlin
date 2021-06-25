<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bपन.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/compat.h>
#समावेश <linux/security.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/uuid.h>
#समावेश <linux/btrfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/iversion.h>
#समावेश <linux/fileattr.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "export.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "print-tree.h"
#समावेश "volumes.h"
#समावेश "locking.h"
#समावेश "backref.h"
#समावेश "rcu-string.h"
#समावेश "send.h"
#समावेश "dev-replace.h"
#समावेश "props.h"
#समावेश "sysfs.h"
#समावेश "qgroup.h"
#समावेश "tree-log.h"
#समावेश "compression.h"
#समावेश "space-info.h"
#समावेश "delalloc-space.h"
#समावेश "block-group.h"

#अगर_घोषित CONFIG_64BIT
/* If we have a 32-bit userspace and 64-bit kernel, then the UAPI
 * काष्ठाures are incorrect, as the बारpec काष्ठाure from userspace
 * is 4 bytes too small. We define these alternatives here to teach
 * the kernel about the 32-bit काष्ठा packing.
 */
काष्ठा btrfs_ioctl_बारpec_32 अणु
	__u64 sec;
	__u32 nsec;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_ioctl_received_subvol_args_32 अणु
	अक्षर	uuid[BTRFS_UUID_SIZE];	/* in */
	__u64	stransid;		/* in */
	__u64	rtransid;		/* out */
	काष्ठा btrfs_ioctl_बारpec_32 sसमय; /* in */
	काष्ठा btrfs_ioctl_बारpec_32 rसमय; /* out */
	__u64	flags;			/* in */
	__u64	reserved[16];		/* in */
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_IOC_SET_RECEIVED_SUBVOL_32 _IOWR(BTRFS_IOCTL_MAGIC, 37, \
				काष्ठा btrfs_ioctl_received_subvol_args_32)
#पूर्ण_अगर

#अगर defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
काष्ठा btrfs_ioctl_send_args_32 अणु
	__s64 send_fd;			/* in */
	__u64 clone_sources_count;	/* in */
	compat_uptr_t clone_sources;	/* in */
	__u64 parent_root;		/* in */
	__u64 flags;			/* in */
	__u64 reserved[4];		/* in */
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_IOC_SEND_32 _IOW(BTRFS_IOCTL_MAGIC, 38, \
			       काष्ठा btrfs_ioctl_send_args_32)
#पूर्ण_अगर

/* Mask out flags that are inappropriate क्रम the given type of inode. */
अटल अचिन्हित पूर्णांक btrfs_mask_fsflags_क्रम_type(काष्ठा inode *inode,
		अचिन्हित पूर्णांक flags)
अणु
	अगर (S_ISसूची(inode->i_mode))
		वापस flags;
	अन्यथा अगर (S_ISREG(inode->i_mode))
		वापस flags & ~FS_सूचीSYNC_FL;
	अन्यथा
		वापस flags & (FS_NODUMP_FL | FS_NOATIME_FL);
पूर्ण

/*
 * Export पूर्णांकernal inode flags to the क्रमmat expected by the FS_IOC_GETFLAGS
 * ioctl.
 */
अटल अचिन्हित पूर्णांक btrfs_inode_flags_to_fsflags(अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक अगरlags = 0;

	अगर (flags & BTRFS_INODE_SYNC)
		अगरlags |= FS_SYNC_FL;
	अगर (flags & BTRFS_INODE_IMMUTABLE)
		अगरlags |= FS_IMMUTABLE_FL;
	अगर (flags & BTRFS_INODE_APPEND)
		अगरlags |= FS_APPEND_FL;
	अगर (flags & BTRFS_INODE_NODUMP)
		अगरlags |= FS_NODUMP_FL;
	अगर (flags & BTRFS_INODE_NOATIME)
		अगरlags |= FS_NOATIME_FL;
	अगर (flags & BTRFS_INODE_सूचीSYNC)
		अगरlags |= FS_सूचीSYNC_FL;
	अगर (flags & BTRFS_INODE_NODATACOW)
		अगरlags |= FS_NOCOW_FL;

	अगर (flags & BTRFS_INODE_NOCOMPRESS)
		अगरlags |= FS_NOCOMP_FL;
	अन्यथा अगर (flags & BTRFS_INODE_COMPRESS)
		अगरlags |= FS_COMPR_FL;

	वापस अगरlags;
पूर्ण

/*
 * Update inode->i_flags based on the btrfs पूर्णांकernal flags.
 */
व्योम btrfs_sync_inode_flags_to_i_flags(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_inode *binode = BTRFS_I(inode);
	अचिन्हित पूर्णांक new_fl = 0;

	अगर (binode->flags & BTRFS_INODE_SYNC)
		new_fl |= S_SYNC;
	अगर (binode->flags & BTRFS_INODE_IMMUTABLE)
		new_fl |= S_IMMUTABLE;
	अगर (binode->flags & BTRFS_INODE_APPEND)
		new_fl |= S_APPEND;
	अगर (binode->flags & BTRFS_INODE_NOATIME)
		new_fl |= S_NOATIME;
	अगर (binode->flags & BTRFS_INODE_सूचीSYNC)
		new_fl |= S_सूचीSYNC;

	set_mask_bits(&inode->i_flags,
		      S_SYNC | S_APPEND | S_IMMUTABLE | S_NOATIME | S_सूचीSYNC,
		      new_fl);
पूर्ण

/*
 * Check अगर @flags are a supported and valid set of FS_*_FL flags and that
 * the old and new flags are not conflicting
 */
अटल पूर्णांक check_fsflags(अचिन्हित पूर्णांक old_flags, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & ~(FS_IMMUTABLE_FL | FS_APPEND_FL | \
		      FS_NOATIME_FL | FS_NODUMP_FL | \
		      FS_SYNC_FL | FS_सूचीSYNC_FL | \
		      FS_NOCOMP_FL | FS_COMPR_FL |
		      FS_NOCOW_FL))
		वापस -EOPNOTSUPP;

	/* COMPR and NOCOMP on new/old are valid */
	अगर ((flags & FS_NOCOMP_FL) && (flags & FS_COMPR_FL))
		वापस -EINVAL;

	अगर ((flags & FS_COMPR_FL) && (flags & FS_NOCOW_FL))
		वापस -EINVAL;

	/* NOCOW and compression options are mutually exclusive */
	अगर ((old_flags & FS_NOCOW_FL) && (flags & (FS_COMPR_FL | FS_NOCOMP_FL)))
		वापस -EINVAL;
	अगर ((flags & FS_NOCOW_FL) && (old_flags & (FS_COMPR_FL | FS_NOCOMP_FL)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक check_fsflags_compatible(काष्ठा btrfs_fs_info *fs_info,
				    अचिन्हित पूर्णांक flags)
अणु
	अगर (btrfs_is_zoned(fs_info) && (flags & FS_NOCOW_FL))
		वापस -EPERM;

	वापस 0;
पूर्ण

/*
 * Set flags/xflags from the पूर्णांकernal inode flags. The reमुख्यing items of
 * fsxattr are zeroed.
 */
पूर्णांक btrfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा btrfs_inode *binode = BTRFS_I(d_inode(dentry));

	fileattr_fill_flags(fa, btrfs_inode_flags_to_fsflags(binode->flags));
	वापस 0;
पूर्ण

पूर्णांक btrfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_inode *binode = BTRFS_I(inode);
	काष्ठा btrfs_root *root = binode->root;
	काष्ठा btrfs_trans_handle *trans;
	अचिन्हित पूर्णांक fsflags, old_fsflags;
	पूर्णांक ret;
	स्थिर अक्षर *comp = शून्य;
	u32 binode_flags;

	अगर (btrfs_root_पढ़ोonly(root))
		वापस -EROFS;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	fsflags = btrfs_mask_fsflags_क्रम_type(inode, fa->flags);
	old_fsflags = btrfs_inode_flags_to_fsflags(binode->flags);
	ret = check_fsflags(old_fsflags, fsflags);
	अगर (ret)
		वापस ret;

	ret = check_fsflags_compatible(fs_info, fsflags);
	अगर (ret)
		वापस ret;

	binode_flags = binode->flags;
	अगर (fsflags & FS_SYNC_FL)
		binode_flags |= BTRFS_INODE_SYNC;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_SYNC;
	अगर (fsflags & FS_IMMUTABLE_FL)
		binode_flags |= BTRFS_INODE_IMMUTABLE;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_IMMUTABLE;
	अगर (fsflags & FS_APPEND_FL)
		binode_flags |= BTRFS_INODE_APPEND;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_APPEND;
	अगर (fsflags & FS_NODUMP_FL)
		binode_flags |= BTRFS_INODE_NODUMP;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_NODUMP;
	अगर (fsflags & FS_NOATIME_FL)
		binode_flags |= BTRFS_INODE_NOATIME;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_NOATIME;

	/* If coming from FS_IOC_FSSETXATTR then skip unconverted flags */
	अगर (!fa->flags_valid) अणु
		/* 1 item क्रम the inode */
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);
		जाओ update_flags;
	पूर्ण

	अगर (fsflags & FS_सूचीSYNC_FL)
		binode_flags |= BTRFS_INODE_सूचीSYNC;
	अन्यथा
		binode_flags &= ~BTRFS_INODE_सूचीSYNC;
	अगर (fsflags & FS_NOCOW_FL) अणु
		अगर (S_ISREG(inode->i_mode)) अणु
			/*
			 * It's safe to turn csums off here, no extents exist.
			 * Otherwise we want the flag to reflect the real COW
			 * status of the file and will not set it.
			 */
			अगर (inode->i_size == 0)
				binode_flags |= BTRFS_INODE_NODATACOW |
						BTRFS_INODE_NODATASUM;
		पूर्ण अन्यथा अणु
			binode_flags |= BTRFS_INODE_NODATACOW;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Revert back under same assumptions as above
		 */
		अगर (S_ISREG(inode->i_mode)) अणु
			अगर (inode->i_size == 0)
				binode_flags &= ~(BTRFS_INODE_NODATACOW |
						  BTRFS_INODE_NODATASUM);
		पूर्ण अन्यथा अणु
			binode_flags &= ~BTRFS_INODE_NODATACOW;
		पूर्ण
	पूर्ण

	/*
	 * The COMPRESS flag can only be changed by users, जबतक the NOCOMPRESS
	 * flag may be changed स्वतःmatically अगर compression code won't make
	 * things smaller.
	 */
	अगर (fsflags & FS_NOCOMP_FL) अणु
		binode_flags &= ~BTRFS_INODE_COMPRESS;
		binode_flags |= BTRFS_INODE_NOCOMPRESS;
	पूर्ण अन्यथा अगर (fsflags & FS_COMPR_FL) अणु

		अगर (IS_SWAPखाता(inode))
			वापस -ETXTBSY;

		binode_flags |= BTRFS_INODE_COMPRESS;
		binode_flags &= ~BTRFS_INODE_NOCOMPRESS;

		comp = btrfs_compress_type2str(fs_info->compress_type);
		अगर (!comp || comp[0] == 0)
			comp = btrfs_compress_type2str(BTRFS_COMPRESS_ZLIB);
	पूर्ण अन्यथा अणु
		binode_flags &= ~(BTRFS_INODE_COMPRESS | BTRFS_INODE_NOCOMPRESS);
	पूर्ण

	/*
	 * 1 क्रम inode item
	 * 2 क्रम properties
	 */
	trans = btrfs_start_transaction(root, 3);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	अगर (comp) अणु
		ret = btrfs_set_prop(trans, inode, "btrfs.compression", comp,
				     म_माप(comp), 0);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_end_trans;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = btrfs_set_prop(trans, inode, "btrfs.compression", शून्य,
				     0, 0);
		अगर (ret && ret != -ENODATA) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_end_trans;
		पूर्ण
	पूर्ण

update_flags:
	binode->flags = binode_flags;
	btrfs_sync_inode_flags_to_i_flags(inode);
	inode_inc_iversion(inode);
	inode->i_स_समय = current_समय(inode);
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));

 out_end_trans:
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

bool btrfs_exclop_start(काष्ठा btrfs_fs_info *fs_info,
			क्रमागत btrfs_exclusive_operation type)
अणु
	वापस !cmpxchg(&fs_info->exclusive_operation, BTRFS_EXCLOP_NONE, type);
पूर्ण

व्योम btrfs_exclop_finish(काष्ठा btrfs_fs_info *fs_info)
अणु
	WRITE_ONCE(fs_info->exclusive_operation, BTRFS_EXCLOP_NONE);
	sysfs_notअगरy(&fs_info->fs_devices->fsid_kobj, शून्य, "exclusive_operation");
पूर्ण

अटल पूर्णांक btrfs_ioctl_getversion(काष्ठा file *file, पूर्णांक __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);

	वापस put_user(inode->i_generation, arg);
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_fitrim(काष्ठा btrfs_fs_info *fs_info,
					व्योम __user *arg)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा request_queue *q;
	काष्ठा fstrim_range range;
	u64 minlen = ULदीर्घ_उच्च;
	u64 num_devices = 0;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * btrfs_trim_block_group() depends on space cache, which is not
	 * available in zoned fileप्रणाली. So, disallow fitrim on a zoned
	 * fileप्रणाली क्रम now.
	 */
	अगर (btrfs_is_zoned(fs_info))
		वापस -EOPNOTSUPP;

	/*
	 * If the fs is mounted with nologreplay, which requires it to be
	 * mounted in RO mode as well, we can not allow discard on मुक्त space
	 * inside block groups, because log trees refer to extents that are not
	 * pinned in a block group's मुक्त space cache (pinning the extents is
	 * precisely the first phase of replaying a log tree).
	 */
	अगर (btrfs_test_opt(fs_info, NOLOGREPLAY))
		वापस -EROFS;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(device, &fs_info->fs_devices->devices,
				dev_list) अणु
		अगर (!device->bdev)
			जारी;
		q = bdev_get_queue(device->bdev);
		अगर (blk_queue_discard(q)) अणु
			num_devices++;
			minlen = min_t(u64, q->limits.discard_granularity,
				     minlen);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!num_devices)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&range, arg, माप(range)))
		वापस -EFAULT;

	/*
	 * NOTE: Don't truncate the range using super->total_bytes.  Bytenr of
	 * block group is in the logical address space, which can be any
	 * sectorsize aligned bytenr in  the range [0, U64_MAX].
	 */
	अगर (range.len < fs_info->sb->s_blocksize)
		वापस -EINVAL;

	range.minlen = max(range.minlen, minlen);
	ret = btrfs_trim_fs(fs_info, &range);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(arg, &range, माप(range)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक __pure btrfs_is_empty_uuid(u8 *uuid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_UUID_SIZE; i++) अणु
		अगर (uuid[i])
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल noअंतरभूत पूर्णांक create_subvol(काष्ठा inode *dir,
				  काष्ठा dentry *dentry,
				  स्थिर अक्षर *name, पूर्णांक namelen,
				  काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_root *new_root;
	काष्ठा btrfs_block_rsv block_rsv;
	काष्ठा बारpec64 cur_समय = current_समय(dir);
	काष्ठा inode *inode;
	पूर्णांक ret;
	पूर्णांक err;
	dev_t anon_dev = 0;
	u64 objectid;
	u64 index = 0;

	root_item = kzalloc(माप(*root_item), GFP_KERNEL);
	अगर (!root_item)
		वापस -ENOMEM;

	ret = btrfs_get_मुक्त_objectid(fs_info->tree_root, &objectid);
	अगर (ret)
		जाओ fail_मुक्त;

	ret = get_anon_bdev(&anon_dev);
	अगर (ret < 0)
		जाओ fail_मुक्त;

	/*
	 * Don't create subvolume whose level is not zero. Or qgroup will be
	 * screwed up since it assumes subvolume qgroup's level to be 0.
	 */
	अगर (btrfs_qgroup_level(objectid)) अणु
		ret = -ENOSPC;
		जाओ fail_मुक्त;
	पूर्ण

	btrfs_init_block_rsv(&block_rsv, BTRFS_BLOCK_RSV_TEMP);
	/*
	 * The same as the snapshot creation, please see the comment
	 * of create_snapshot().
	 */
	ret = btrfs_subvolume_reserve_metadata(root, &block_rsv, 8, false);
	अगर (ret)
		जाओ fail_मुक्त;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		btrfs_subvolume_release_metadata(root, &block_rsv);
		जाओ fail_मुक्त;
	पूर्ण
	trans->block_rsv = &block_rsv;
	trans->bytes_reserved = block_rsv.size;

	ret = btrfs_qgroup_inherit(trans, 0, objectid, inherit);
	अगर (ret)
		जाओ fail;

	leaf = btrfs_alloc_tree_block(trans, root, 0, objectid, शून्य, 0, 0, 0,
				      BTRFS_NESTING_NORMAL);
	अगर (IS_ERR(leaf)) अणु
		ret = PTR_ERR(leaf);
		जाओ fail;
	पूर्ण

	btrfs_mark_buffer_dirty(leaf);

	inode_item = &root_item->inode;
	btrfs_set_stack_inode_generation(inode_item, 1);
	btrfs_set_stack_inode_size(inode_item, 3);
	btrfs_set_stack_inode_nlink(inode_item, 1);
	btrfs_set_stack_inode_nbytes(inode_item,
				     fs_info->nodesize);
	btrfs_set_stack_inode_mode(inode_item, S_IFसूची | 0755);

	btrfs_set_root_flags(root_item, 0);
	btrfs_set_root_limit(root_item, 0);
	btrfs_set_stack_inode_flags(inode_item, BTRFS_INODE_ROOT_ITEM_INIT);

	btrfs_set_root_bytenr(root_item, leaf->start);
	btrfs_set_root_generation(root_item, trans->transid);
	btrfs_set_root_level(root_item, 0);
	btrfs_set_root_refs(root_item, 1);
	btrfs_set_root_used(root_item, leaf->len);
	btrfs_set_root_last_snapshot(root_item, 0);

	btrfs_set_root_generation_v2(root_item,
			btrfs_root_generation(root_item));
	generate_अक्रमom_guid(root_item->uuid);
	btrfs_set_stack_बारpec_sec(&root_item->oसमय, cur_समय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&root_item->oसमय, cur_समय.tv_nsec);
	root_item->स_समय = root_item->oसमय;
	btrfs_set_root_ctransid(root_item, trans->transid);
	btrfs_set_root_otransid(root_item, trans->transid);

	btrfs_tree_unlock(leaf);

	btrfs_set_root_dirid(root_item, BTRFS_FIRST_FREE_OBJECTID);

	key.objectid = objectid;
	key.offset = 0;
	key.type = BTRFS_ROOT_ITEM_KEY;
	ret = btrfs_insert_root(trans, fs_info->tree_root, &key,
				root_item);
	अगर (ret) अणु
		/*
		 * Since we करोn't पात the transaction in this हाल, मुक्त the
		 * tree block so that we करोn't leak space and leave the
		 * fileप्रणाली in an inconsistent state (an extent item in the
		 * extent tree without backreferences). Also no need to have
		 * the tree block locked since it is not in any tree at this
		 * poपूर्णांक, so no other task can find it and use it.
		 */
		btrfs_मुक्त_tree_block(trans, root, leaf, 0, 1);
		मुक्त_extent_buffer(leaf);
		जाओ fail;
	पूर्ण

	मुक्त_extent_buffer(leaf);
	leaf = शून्य;

	key.offset = (u64)-1;
	new_root = btrfs_get_new_fs_root(fs_info, objectid, anon_dev);
	अगर (IS_ERR(new_root)) अणु
		मुक्त_anon_bdev(anon_dev);
		ret = PTR_ERR(new_root);
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	/* Freeing will be करोne in btrfs_put_root() of new_root */
	anon_dev = 0;

	ret = btrfs_record_root_in_trans(trans, new_root);
	अगर (ret) अणु
		btrfs_put_root(new_root);
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_create_subvol_root(trans, new_root, root);
	btrfs_put_root(new_root);
	अगर (ret) अणु
		/* We potentially lose an unused inode item here */
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	/*
	 * insert the directory item
	 */
	ret = btrfs_set_inode_index(BTRFS_I(dir), &index);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_insert_dir_item(trans, name, namelen, BTRFS_I(dir), &key,
				    BTRFS_FT_सूची, index);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	btrfs_i_size_ग_लिखो(BTRFS_I(dir), dir->i_size + namelen * 2);
	ret = btrfs_update_inode(trans, root, BTRFS_I(dir));
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_add_root_ref(trans, objectid, root->root_key.objectid,
				 btrfs_ino(BTRFS_I(dir)), index, name, namelen);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_uuid_tree_add(trans, root_item->uuid,
				  BTRFS_UUID_KEY_SUBVOL, objectid);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);

fail:
	kमुक्त(root_item);
	trans->block_rsv = शून्य;
	trans->bytes_reserved = 0;
	btrfs_subvolume_release_metadata(root, &block_rsv);

	err = btrfs_commit_transaction(trans);
	अगर (err && !ret)
		ret = err;

	अगर (!ret) अणु
		inode = btrfs_lookup_dentry(dir, dentry);
		अगर (IS_ERR(inode))
			वापस PTR_ERR(inode);
		d_instantiate(dentry, inode);
	पूर्ण
	वापस ret;

fail_मुक्त:
	अगर (anon_dev)
		मुक्त_anon_bdev(anon_dev);
	kमुक्त(root_item);
	वापस ret;
पूर्ण

अटल पूर्णांक create_snapshot(काष्ठा btrfs_root *root, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, bool पढ़ोonly,
			   काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा inode *inode;
	काष्ठा btrfs_pending_snapshot *pending_snapshot;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		वापस -EINVAL;

	अगर (atomic_पढ़ो(&root->nr_swapfiles)) अणु
		btrfs_warn(fs_info,
			   "cannot snapshot subvolume with active swapfile");
		वापस -ETXTBSY;
	पूर्ण

	pending_snapshot = kzalloc(माप(*pending_snapshot), GFP_KERNEL);
	अगर (!pending_snapshot)
		वापस -ENOMEM;

	ret = get_anon_bdev(&pending_snapshot->anon_dev);
	अगर (ret < 0)
		जाओ मुक्त_pending;
	pending_snapshot->root_item = kzalloc(माप(काष्ठा btrfs_root_item),
			GFP_KERNEL);
	pending_snapshot->path = btrfs_alloc_path();
	अगर (!pending_snapshot->root_item || !pending_snapshot->path) अणु
		ret = -ENOMEM;
		जाओ मुक्त_pending;
	पूर्ण

	btrfs_init_block_rsv(&pending_snapshot->block_rsv,
			     BTRFS_BLOCK_RSV_TEMP);
	/*
	 * 1 - parent dir inode
	 * 2 - dir entries
	 * 1 - root item
	 * 2 - root ref/backref
	 * 1 - root of snapshot
	 * 1 - UUID item
	 */
	ret = btrfs_subvolume_reserve_metadata(BTRFS_I(dir)->root,
					&pending_snapshot->block_rsv, 8,
					false);
	अगर (ret)
		जाओ मुक्त_pending;

	pending_snapshot->dentry = dentry;
	pending_snapshot->root = root;
	pending_snapshot->पढ़ोonly = पढ़ोonly;
	pending_snapshot->dir = dir;
	pending_snapshot->inherit = inherit;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ fail;
	पूर्ण

	spin_lock(&fs_info->trans_lock);
	list_add(&pending_snapshot->list,
		 &trans->transaction->pending_snapshots);
	spin_unlock(&fs_info->trans_lock);

	ret = btrfs_commit_transaction(trans);
	अगर (ret)
		जाओ fail;

	ret = pending_snapshot->error;
	अगर (ret)
		जाओ fail;

	ret = btrfs_orphan_cleanup(pending_snapshot->snap);
	अगर (ret)
		जाओ fail;

	inode = btrfs_lookup_dentry(d_inode(dentry->d_parent), dentry);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ fail;
	पूर्ण

	d_instantiate(dentry, inode);
	ret = 0;
	pending_snapshot->anon_dev = 0;
fail:
	/* Prevent द्विगुन मुक्तing of anon_dev */
	अगर (ret && pending_snapshot->snap)
		pending_snapshot->snap->anon_dev = 0;
	btrfs_put_root(pending_snapshot->snap);
	btrfs_subvolume_release_metadata(root, &pending_snapshot->block_rsv);
मुक्त_pending:
	अगर (pending_snapshot->anon_dev)
		मुक्त_anon_bdev(pending_snapshot->anon_dev);
	kमुक्त(pending_snapshot->root_item);
	btrfs_मुक्त_path(pending_snapshot->path);
	kमुक्त(pending_snapshot);

	वापस ret;
पूर्ण

/*  copy of may_delete in fs/namei.c()
 *	Check whether we can हटाओ a link victim from directory dir, check
 *  whether the type of victim is right.
 *  1. We can't करो it अगर dir is पढ़ो-only (करोne in permission())
 *  2. We should have ग_लिखो and exec permissions on dir
 *  3. We can't हटाओ anything from append-only dir
 *  4. We can't करो anything with immutable dir (करोne in permission())
 *  5. If the sticky bit on dir is set we should either
 *	a. be owner of dir, or
 *	b. be owner of victim, or
 *	c. have CAP_FOWNER capability
 *  6. If the victim is append-only or immutable we can't करो anything with
 *     links poपूर्णांकing to it.
 *  7. If we were asked to हटाओ a directory and victim isn't one - ENOTसूची.
 *  8. If we were asked to हटाओ a non-directory and victim isn't one - EISसूची.
 *  9. We can't हटाओ a root or mountpoपूर्णांक.
 * 10. We करोn't allow removal of NFS sillyrenamed files; it's handled by
 *     nfs_async_unlink().
 */

अटल पूर्णांक btrfs_may_delete(काष्ठा inode *dir, काष्ठा dentry *victim, पूर्णांक isdir)
अणु
	पूर्णांक error;

	अगर (d_really_is_negative(victim))
		वापस -ENOENT;

	BUG_ON(d_inode(victim->d_parent) != dir);
	audit_inode_child(dir, victim, AUDIT_TYPE_CHILD_DELETE);

	error = inode_permission(&init_user_ns, dir, MAY_WRITE | MAY_EXEC);
	अगर (error)
		वापस error;
	अगर (IS_APPEND(dir))
		वापस -EPERM;
	अगर (check_sticky(&init_user_ns, dir, d_inode(victim)) ||
	    IS_APPEND(d_inode(victim)) || IS_IMMUTABLE(d_inode(victim)) ||
	    IS_SWAPखाता(d_inode(victim)))
		वापस -EPERM;
	अगर (isdir) अणु
		अगर (!d_is_dir(victim))
			वापस -ENOTसूची;
		अगर (IS_ROOT(victim))
			वापस -EBUSY;
	पूर्ण अन्यथा अगर (d_is_dir(victim))
		वापस -EISसूची;
	अगर (IS_DEADसूची(dir))
		वापस -ENOENT;
	अगर (victim->d_flags & DCACHE_NFSFS_RENAMED)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/* copy of may_create in fs/namei.c() */
अटल अंतरभूत पूर्णांक btrfs_may_create(काष्ठा inode *dir, काष्ठा dentry *child)
अणु
	अगर (d_really_is_positive(child))
		वापस -EEXIST;
	अगर (IS_DEADसूची(dir))
		वापस -ENOENT;
	वापस inode_permission(&init_user_ns, dir, MAY_WRITE | MAY_EXEC);
पूर्ण

/*
 * Create a new subvolume below @parent.  This is largely modeled after
 * sys_सूची_गढ़ोat and vfs_सूची_गढ़ो, but we only करो a single component lookup
 * inside this fileप्रणाली so it's quite a bit simpler.
 */
अटल noअंतरभूत पूर्णांक btrfs_mksubvol(स्थिर काष्ठा path *parent,
				   स्थिर अक्षर *name, पूर्णांक namelen,
				   काष्ठा btrfs_root *snap_src,
				   bool पढ़ोonly,
				   काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	काष्ठा inode *dir = d_inode(parent->dentry);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा dentry *dentry;
	पूर्णांक error;

	error = करोwn_ग_लिखो_समाप्तable_nested(&dir->i_rwsem, I_MUTEX_PARENT);
	अगर (error == -EINTR)
		वापस error;

	dentry = lookup_one_len(name, parent->dentry, namelen);
	error = PTR_ERR(dentry);
	अगर (IS_ERR(dentry))
		जाओ out_unlock;

	error = btrfs_may_create(dir, dentry);
	अगर (error)
		जाओ out_dput;

	/*
	 * even अगर this name करोesn't exist, we may get hash collisions.
	 * check क्रम them now when we can safely fail
	 */
	error = btrfs_check_dir_item_collision(BTRFS_I(dir)->root,
					       dir->i_ino, name,
					       namelen);
	अगर (error)
		जाओ out_dput;

	करोwn_पढ़ो(&fs_info->subvol_sem);

	अगर (btrfs_root_refs(&BTRFS_I(dir)->root->root_item) == 0)
		जाओ out_up_पढ़ो;

	अगर (snap_src)
		error = create_snapshot(snap_src, dir, dentry, पढ़ोonly, inherit);
	अन्यथा
		error = create_subvol(dir, dentry, name, namelen, inherit);

	अगर (!error)
		fsnotअगरy_सूची_गढ़ो(dir, dentry);
out_up_पढ़ो:
	up_पढ़ो(&fs_info->subvol_sem);
out_dput:
	dput(dentry);
out_unlock:
	btrfs_inode_unlock(dir, 0);
	वापस error;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_mksnapshot(स्थिर काष्ठा path *parent,
				   स्थिर अक्षर *name, पूर्णांक namelen,
				   काष्ठा btrfs_root *root,
				   bool पढ़ोonly,
				   काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	पूर्णांक ret;
	bool snapshot_क्रमce_cow = false;

	/*
	 * Force new buffered ग_लिखोs to reserve space even when NOCOW is
	 * possible. This is to aव्योम later ग_लिखोback (running dealloc) to
	 * fallback to COW mode and unexpectedly fail with ENOSPC.
	 */
	btrfs_drew_पढ़ो_lock(&root->snapshot_lock);

	ret = btrfs_start_delalloc_snapshot(root, false);
	अगर (ret)
		जाओ out;

	/*
	 * All previous ग_लिखोs have started ग_लिखोback in NOCOW mode, so now
	 * we क्रमce future ग_लिखोs to fallback to COW mode during snapshot
	 * creation.
	 */
	atomic_inc(&root->snapshot_क्रमce_cow);
	snapshot_क्रमce_cow = true;

	btrfs_रुको_ordered_extents(root, U64_MAX, 0, (u64)-1);

	ret = btrfs_mksubvol(parent, name, namelen,
			     root, पढ़ोonly, inherit);
out:
	अगर (snapshot_क्रमce_cow)
		atomic_dec(&root->snapshot_क्रमce_cow);
	btrfs_drew_पढ़ो_unlock(&root->snapshot_lock);
	वापस ret;
पूर्ण

/*
 * When we're defragging a range, we don't want to kick it off again
 * अगर it is really just रुकोing क्रम delalloc to send it करोwn.
 * If we find a nice big extent or delalloc range क्रम the bytes in the
 * file you want to defrag, we वापस 0 to let you know to skip this
 * part of the file
 */
अटल पूर्णांक check_defrag_in_cache(काष्ठा inode *inode, u64 offset, u32 thresh)
अणु
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_map *em = शून्य;
	काष्ठा extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	u64 end;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, offset, PAGE_SIZE);
	पढ़ो_unlock(&em_tree->lock);

	अगर (em) अणु
		end = extent_map_end(em);
		मुक्त_extent_map(em);
		अगर (end - offset > thresh)
			वापस 0;
	पूर्ण
	/* अगर we alपढ़ोy have a nice delalloc here, just stop */
	thresh /= 2;
	end = count_range_bits(io_tree, &offset, offset + thresh,
			       thresh, EXTENT_DELALLOC, 1);
	अगर (end >= thresh)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * helper function to walk through a file and find extents
 * newer than a specअगरic transid, and smaller than thresh.
 *
 * This is used by the defragging code to find new and small
 * extents
 */
अटल पूर्णांक find_new_extents(काष्ठा btrfs_root *root,
			    काष्ठा inode *inode, u64 newer_than,
			    u64 *off, u32 thresh)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key min_key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_file_extent_item *extent;
	पूर्णांक type;
	पूर्णांक ret;
	u64 ino = btrfs_ino(BTRFS_I(inode));

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	min_key.objectid = ino;
	min_key.type = BTRFS_EXTENT_DATA_KEY;
	min_key.offset = *off;

	जबतक (1) अणु
		ret = btrfs_search_क्रमward(root, &min_key, path, newer_than);
		अगर (ret != 0)
			जाओ none;
process_slot:
		अगर (min_key.objectid != ino)
			जाओ none;
		अगर (min_key.type != BTRFS_EXTENT_DATA_KEY)
			जाओ none;

		leaf = path->nodes[0];
		extent = btrfs_item_ptr(leaf, path->slots[0],
					काष्ठा btrfs_file_extent_item);

		type = btrfs_file_extent_type(leaf, extent);
		अगर (type == BTRFS_खाता_EXTENT_REG &&
		    btrfs_file_extent_num_bytes(leaf, extent) < thresh &&
		    check_defrag_in_cache(inode, min_key.offset, thresh)) अणु
			*off = min_key.offset;
			btrfs_मुक्त_path(path);
			वापस 0;
		पूर्ण

		path->slots[0]++;
		अगर (path->slots[0] < btrfs_header_nritems(leaf)) अणु
			btrfs_item_key_to_cpu(leaf, &min_key, path->slots[0]);
			जाओ process_slot;
		पूर्ण

		अगर (min_key.offset == (u64)-1)
			जाओ none;

		min_key.offset++;
		btrfs_release_path(path);
	पूर्ण
none:
	btrfs_मुक्त_path(path);
	वापस -ENOENT;
पूर्ण

अटल काष्ठा extent_map *defrag_lookup_extent(काष्ठा inode *inode, u64 start)
अणु
	काष्ठा extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_map *em;
	u64 len = PAGE_SIZE;

	/*
	 * hopefully we have this extent in the tree alपढ़ोy, try without
	 * the full extent lock
	 */
	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, start, len);
	पढ़ो_unlock(&em_tree->lock);

	अगर (!em) अणु
		काष्ठा extent_state *cached = शून्य;
		u64 end = start + len - 1;

		/* get the big lock and पढ़ो metadata off disk */
		lock_extent_bits(io_tree, start, end, &cached);
		em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, start, len);
		unlock_extent_cached(io_tree, start, end, &cached);

		अगर (IS_ERR(em))
			वापस शून्य;
	पूर्ण

	वापस em;
पूर्ण

अटल bool defrag_check_next_extent(काष्ठा inode *inode, काष्ठा extent_map *em)
अणु
	काष्ठा extent_map *next;
	bool ret = true;

	/* this is the last extent */
	अगर (em->start + em->len >= i_size_पढ़ो(inode))
		वापस false;

	next = defrag_lookup_extent(inode, em->start + em->len);
	अगर (!next || next->block_start >= EXTENT_MAP_LAST_BYTE)
		ret = false;
	अन्यथा अगर ((em->block_start + em->block_len == next->block_start) &&
		 (em->block_len > SZ_128K && next->block_len > SZ_128K))
		ret = false;

	मुक्त_extent_map(next);
	वापस ret;
पूर्ण

अटल पूर्णांक should_defrag_range(काष्ठा inode *inode, u64 start, u32 thresh,
			       u64 *last_len, u64 *skip, u64 *defrag_end,
			       पूर्णांक compress)
अणु
	काष्ठा extent_map *em;
	पूर्णांक ret = 1;
	bool next_mergeable = true;
	bool prev_mergeable = true;

	/*
	 * make sure that once we start defragging an extent, we keep on
	 * defragging it
	 */
	अगर (start < *defrag_end)
		वापस 1;

	*skip = 0;

	em = defrag_lookup_extent(inode, start);
	अगर (!em)
		वापस 0;

	/* this will cover holes, and अंतरभूत extents */
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!*defrag_end)
		prev_mergeable = false;

	next_mergeable = defrag_check_next_extent(inode, em);
	/*
	 * we hit a real extent, अगर it is big or the next extent is not a
	 * real extent, करोn't bother defragging it
	 */
	अगर (!compress && (*last_len == 0 || *last_len >= thresh) &&
	    (em->len >= thresh || (!next_mergeable && !prev_mergeable)))
		ret = 0;
out:
	/*
	 * last_len ends up being a counter of how many bytes we've defragged.
	 * every समय we choose not to defrag an extent, we reset *last_len
	 * so that the next tiny extent will क्रमce a defrag.
	 *
	 * The end result of this is that tiny extents beक्रमe a single big
	 * extent will क्रमce at least part of that big extent to be defragged.
	 */
	अगर (ret) अणु
		*defrag_end = extent_map_end(em);
	पूर्ण अन्यथा अणु
		*last_len = 0;
		*skip = extent_map_end(em);
		*defrag_end = 0;
	पूर्ण

	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

/*
 * it करोesn't करो much good to defrag one or two pages
 * at a समय.  This pulls in a nice chunk of pages
 * to COW and defrag.
 *
 * It also makes sure the delalloc code has enough
 * dirty data to aव्योम making new small extents as part
 * of the defrag
 *
 * It's a good idea to start RA on this range
 * beक्रमe calling this.
 */
अटल पूर्णांक cluster_pages_क्रम_defrag(काष्ठा inode *inode,
				    काष्ठा page **pages,
				    अचिन्हित दीर्घ start_index,
				    अचिन्हित दीर्घ num_pages)
अणु
	अचिन्हित दीर्घ file_end;
	u64 isize = i_size_पढ़ो(inode);
	u64 page_start;
	u64 page_end;
	u64 page_cnt;
	u64 start = (u64)start_index << PAGE_SHIFT;
	u64 search_start;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक i_करोne;
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_io_tree *tree;
	काष्ठा extent_changeset *data_reserved = शून्य;
	gfp_t mask = btrfs_alloc_ग_लिखो_mask(inode->i_mapping);

	file_end = (isize - 1) >> PAGE_SHIFT;
	अगर (!isize || start_index > file_end)
		वापस 0;

	page_cnt = min_t(u64, (u64)num_pages, (u64)file_end - start_index + 1);

	ret = btrfs_delalloc_reserve_space(BTRFS_I(inode), &data_reserved,
			start, page_cnt << PAGE_SHIFT);
	अगर (ret)
		वापस ret;
	i_करोne = 0;
	tree = &BTRFS_I(inode)->io_tree;

	/* step one, lock all the pages */
	क्रम (i = 0; i < page_cnt; i++) अणु
		काष्ठा page *page;
again:
		page = find_or_create_page(inode->i_mapping,
					   start_index + i, mask);
		अगर (!page)
			अवरोध;

		ret = set_page_extent_mapped(page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			अवरोध;
		पूर्ण

		page_start = page_offset(page);
		page_end = page_start + PAGE_SIZE - 1;
		जबतक (1) अणु
			lock_extent_bits(tree, page_start, page_end,
					 &cached_state);
			ordered = btrfs_lookup_ordered_extent(BTRFS_I(inode),
							      page_start);
			unlock_extent_cached(tree, page_start, page_end,
					     &cached_state);
			अगर (!ordered)
				अवरोध;

			unlock_page(page);
			btrfs_start_ordered_extent(ordered, 1);
			btrfs_put_ordered_extent(ordered);
			lock_page(page);
			/*
			 * we unlocked the page above, so we need check अगर
			 * it was released or not.
			 */
			अगर (page->mapping != inode->i_mapping) अणु
				unlock_page(page);
				put_page(page);
				जाओ again;
			पूर्ण
		पूर्ण

		अगर (!PageUptodate(page)) अणु
			btrfs_पढ़ोpage(शून्य, page);
			lock_page(page);
			अगर (!PageUptodate(page)) अणु
				unlock_page(page);
				put_page(page);
				ret = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (page->mapping != inode->i_mapping) अणु
			unlock_page(page);
			put_page(page);
			जाओ again;
		पूर्ण

		pages[i] = page;
		i_करोne++;
	पूर्ण
	अगर (!i_करोne || ret)
		जाओ out;

	अगर (!(inode->i_sb->s_flags & SB_ACTIVE))
		जाओ out;

	/*
	 * so now we have a nice दीर्घ stream of locked
	 * and up to date pages, lets रुको on them
	 */
	क्रम (i = 0; i < i_करोne; i++)
		रुको_on_page_ग_लिखोback(pages[i]);

	page_start = page_offset(pages[0]);
	page_end = page_offset(pages[i_करोne - 1]) + PAGE_SIZE;

	lock_extent_bits(&BTRFS_I(inode)->io_tree,
			 page_start, page_end - 1, &cached_state);

	/*
	 * When defragmenting we skip ranges that have holes or अंतरभूत extents,
	 * (check should_defrag_range()), to aव्योम unnecessary IO and wasting
	 * space. At btrfs_defrag_file(), we check अगर a range should be defragged
	 * beक्रमe locking the inode and then, अगर it should, we trigger a sync
	 * page cache पढ़ोahead - we lock the inode only after that to aव्योम
	 * blocking क्रम too दीर्घ other tasks that possibly want to operate on
	 * other file ranges. But beक्रमe we were able to get the inode lock,
	 * some other task may have punched a hole in the range, or we may have
	 * now an अंतरभूत extent, in which हाल we should not defrag. So check
	 * क्रम that here, where we have the inode and the range locked, and bail
	 * out अगर that happened.
	 */
	search_start = page_start;
	जबतक (search_start < page_end) अणु
		काष्ठा extent_map *em;

		em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, search_start,
				      page_end - search_start);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out_unlock_range;
		पूर्ण
		अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
			मुक्त_extent_map(em);
			/* Ok, 0 means we did not defrag anything */
			ret = 0;
			जाओ out_unlock_range;
		पूर्ण
		search_start = extent_map_end(em);
		मुक्त_extent_map(em);
	पूर्ण

	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start,
			  page_end - 1, EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING |
			  EXTENT_DEFRAG, 0, 0, &cached_state);

	अगर (i_करोne != page_cnt) अणु
		spin_lock(&BTRFS_I(inode)->lock);
		btrfs_mod_outstanding_extents(BTRFS_I(inode), 1);
		spin_unlock(&BTRFS_I(inode)->lock);
		btrfs_delalloc_release_space(BTRFS_I(inode), data_reserved,
				start, (page_cnt - i_करोne) << PAGE_SHIFT, true);
	पूर्ण


	set_extent_defrag(&BTRFS_I(inode)->io_tree, page_start, page_end - 1,
			  &cached_state);

	unlock_extent_cached(&BTRFS_I(inode)->io_tree,
			     page_start, page_end - 1, &cached_state);

	क्रम (i = 0; i < i_करोne; i++) अणु
		clear_page_dirty_क्रम_io(pages[i]);
		ClearPageChecked(pages[i]);
		set_page_dirty(pages[i]);
		unlock_page(pages[i]);
		put_page(pages[i]);
	पूर्ण
	btrfs_delalloc_release_extents(BTRFS_I(inode), page_cnt << PAGE_SHIFT);
	extent_changeset_मुक्त(data_reserved);
	वापस i_करोne;

out_unlock_range:
	unlock_extent_cached(&BTRFS_I(inode)->io_tree,
			     page_start, page_end - 1, &cached_state);
out:
	क्रम (i = 0; i < i_करोne; i++) अणु
		unlock_page(pages[i]);
		put_page(pages[i]);
	पूर्ण
	btrfs_delalloc_release_space(BTRFS_I(inode), data_reserved,
			start, page_cnt << PAGE_SHIFT, true);
	btrfs_delalloc_release_extents(BTRFS_I(inode), page_cnt << PAGE_SHIFT);
	extent_changeset_मुक्त(data_reserved);
	वापस ret;

पूर्ण

पूर्णांक btrfs_defrag_file(काष्ठा inode *inode, काष्ठा file *file,
		      काष्ठा btrfs_ioctl_defrag_range_args *range,
		      u64 newer_than, अचिन्हित दीर्घ max_to_defrag)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा file_ra_state *ra = शून्य;
	अचिन्हित दीर्घ last_index;
	u64 isize = i_size_पढ़ो(inode);
	u64 last_len = 0;
	u64 skip = 0;
	u64 defrag_end = 0;
	u64 newer_off = range->start;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ ra_index = 0;
	पूर्णांक ret;
	पूर्णांक defrag_count = 0;
	पूर्णांक compress_type = BTRFS_COMPRESS_ZLIB;
	u32 extent_thresh = range->extent_thresh;
	अचिन्हित दीर्घ max_cluster = SZ_256K >> PAGE_SHIFT;
	अचिन्हित दीर्घ cluster = max_cluster;
	u64 new_align = ~((u64)SZ_128K - 1);
	काष्ठा page **pages = शून्य;
	bool करो_compress = range->flags & BTRFS_DEFRAG_RANGE_COMPRESS;

	अगर (isize == 0)
		वापस 0;

	अगर (range->start >= isize)
		वापस -EINVAL;

	अगर (करो_compress) अणु
		अगर (range->compress_type >= BTRFS_NR_COMPRESS_TYPES)
			वापस -EINVAL;
		अगर (range->compress_type)
			compress_type = range->compress_type;
	पूर्ण

	अगर (extent_thresh == 0)
		extent_thresh = SZ_256K;

	/*
	 * If we were not given a file, allocate a पढ़ोahead context. As
	 * पढ़ोahead is just an optimization, defrag will work without it so
	 * we करोn't error out.
	 */
	अगर (!file) अणु
		ra = kzalloc(माप(*ra), GFP_KERNEL);
		अगर (ra)
			file_ra_state_init(ra, inode->i_mapping);
	पूर्ण अन्यथा अणु
		ra = &file->f_ra;
	पूर्ण

	pages = kदो_स्मृति_array(max_cluster, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		ret = -ENOMEM;
		जाओ out_ra;
	पूर्ण

	/* find the last page to defrag */
	अगर (range->start + range->len > range->start) अणु
		last_index = min_t(u64, isize - 1,
			 range->start + range->len - 1) >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		last_index = (isize - 1) >> PAGE_SHIFT;
	पूर्ण

	अगर (newer_than) अणु
		ret = find_new_extents(root, inode, newer_than,
				       &newer_off, SZ_64K);
		अगर (!ret) अणु
			range->start = newer_off;
			/*
			 * we always align our defrag to help keep
			 * the extents in the file evenly spaced
			 */
			i = (newer_off & new_align) >> PAGE_SHIFT;
		पूर्ण अन्यथा
			जाओ out_ra;
	पूर्ण अन्यथा अणु
		i = range->start >> PAGE_SHIFT;
	पूर्ण
	अगर (!max_to_defrag)
		max_to_defrag = last_index - i + 1;

	/*
	 * make ग_लिखोback starts from i, so the defrag range can be
	 * written sequentially.
	 */
	अगर (i < inode->i_mapping->ग_लिखोback_index)
		inode->i_mapping->ग_लिखोback_index = i;

	जबतक (i <= last_index && defrag_count < max_to_defrag &&
	       (i < DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE))) अणु
		/*
		 * make sure we stop running अगर someone unmounts
		 * the FS
		 */
		अगर (!(inode->i_sb->s_flags & SB_ACTIVE))
			अवरोध;

		अगर (btrfs_defrag_cancelled(fs_info)) अणु
			btrfs_debug(fs_info, "defrag_file cancelled");
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (!should_defrag_range(inode, (u64)i << PAGE_SHIFT,
					 extent_thresh, &last_len, &skip,
					 &defrag_end, करो_compress))अणु
			अचिन्हित दीर्घ next;
			/*
			 * the should_defrag function tells us how much to skip
			 * bump our counter by the suggested amount
			 */
			next = DIV_ROUND_UP(skip, PAGE_SIZE);
			i = max(i + 1, next);
			जारी;
		पूर्ण

		अगर (!newer_than) अणु
			cluster = (PAGE_ALIGN(defrag_end) >>
				   PAGE_SHIFT) - i;
			cluster = min(cluster, max_cluster);
		पूर्ण अन्यथा अणु
			cluster = max_cluster;
		पूर्ण

		अगर (i + cluster > ra_index) अणु
			ra_index = max(i, ra_index);
			अगर (ra)
				page_cache_sync_पढ़ोahead(inode->i_mapping, ra,
						file, ra_index, cluster);
			ra_index += cluster;
		पूर्ण

		btrfs_inode_lock(inode, 0);
		अगर (IS_SWAPखाता(inode)) अणु
			ret = -ETXTBSY;
		पूर्ण अन्यथा अणु
			अगर (करो_compress)
				BTRFS_I(inode)->defrag_compress = compress_type;
			ret = cluster_pages_क्रम_defrag(inode, pages, i, cluster);
		पूर्ण
		अगर (ret < 0) अणु
			btrfs_inode_unlock(inode, 0);
			जाओ out_ra;
		पूर्ण

		defrag_count += ret;
		balance_dirty_pages_ratelimited(inode->i_mapping);
		btrfs_inode_unlock(inode, 0);

		अगर (newer_than) अणु
			अगर (newer_off == (u64)-1)
				अवरोध;

			अगर (ret > 0)
				i += ret;

			newer_off = max(newer_off + 1,
					(u64)i << PAGE_SHIFT);

			ret = find_new_extents(root, inode, newer_than,
					       &newer_off, SZ_64K);
			अगर (!ret) अणु
				range->start = newer_off;
				i = (newer_off & new_align) >> PAGE_SHIFT;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ret > 0) अणु
				i += ret;
				last_len += ret << PAGE_SHIFT;
			पूर्ण अन्यथा अणु
				i++;
				last_len = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((range->flags & BTRFS_DEFRAG_RANGE_START_IO)) अणु
		filemap_flush(inode->i_mapping);
		अगर (test_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
			     &BTRFS_I(inode)->runसमय_flags))
			filemap_flush(inode->i_mapping);
	पूर्ण

	अगर (range->compress_type == BTRFS_COMPRESS_LZO) अणु
		btrfs_set_fs_incompat(fs_info, COMPRESS_LZO);
	पूर्ण अन्यथा अगर (range->compress_type == BTRFS_COMPRESS_ZSTD) अणु
		btrfs_set_fs_incompat(fs_info, COMPRESS_ZSTD);
	पूर्ण

	ret = defrag_count;

out_ra:
	अगर (करो_compress) अणु
		btrfs_inode_lock(inode, 0);
		BTRFS_I(inode)->defrag_compress = BTRFS_COMPRESS_NONE;
		btrfs_inode_unlock(inode, 0);
	पूर्ण
	अगर (!file)
		kमुक्त(ra);
	kमुक्त(pages);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_resize(काष्ठा file *file,
					व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 new_size;
	u64 old_size;
	u64 devid = 1;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_ioctl_vol_args *vol_args;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_device *device = शून्य;
	अक्षर *sizestr;
	अक्षर *retptr;
	अक्षर *devstr = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक mod = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_RESIZE)) अणु
		mnt_drop_ग_लिखो_file(file);
		वापस BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
	पूर्ण

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args)) अणु
		ret = PTR_ERR(vol_args);
		जाओ out;
	पूर्ण

	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';

	sizestr = vol_args->name;
	devstr = म_अक्षर(sizestr, ':');
	अगर (devstr) अणु
		sizestr = devstr + 1;
		*devstr = '\0';
		devstr = vol_args->name;
		ret = kम_से_अदीर्घl(devstr, 10, &devid);
		अगर (ret)
			जाओ out_मुक्त;
		अगर (!devid) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		btrfs_info(fs_info, "resizing devid %llu", devid);
	पूर्ण

	device = btrfs_find_device(fs_info->fs_devices, devid, शून्य, शून्य);
	अगर (!device) अणु
		btrfs_info(fs_info, "resizer unable to find device %llu",
			   devid);
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
		btrfs_info(fs_info,
			   "resizer unable to apply on readonly device %llu",
		       devid);
		ret = -EPERM;
		जाओ out_मुक्त;
	पूर्ण

	अगर (!म_भेद(sizestr, "max"))
		new_size = device->bdev->bd_inode->i_size;
	अन्यथा अणु
		अगर (sizestr[0] == '-') अणु
			mod = -1;
			sizestr++;
		पूर्ण अन्यथा अगर (sizestr[0] == '+') अणु
			mod = 1;
			sizestr++;
		पूर्ण
		new_size = memparse(sizestr, &retptr);
		अगर (*retptr != '\0' || new_size == 0) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	अगर (test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state)) अणु
		ret = -EPERM;
		जाओ out_मुक्त;
	पूर्ण

	old_size = btrfs_device_get_total_bytes(device);

	अगर (mod < 0) अणु
		अगर (new_size > old_size) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		new_size = old_size - new_size;
	पूर्ण अन्यथा अगर (mod > 0) अणु
		अगर (new_size > ULदीर्घ_उच्च - old_size) अणु
			ret = -दुस्फल;
			जाओ out_मुक्त;
		पूर्ण
		new_size = old_size + new_size;
	पूर्ण

	अगर (new_size < SZ_256M) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	अगर (new_size > device->bdev->bd_inode->i_size) अणु
		ret = -EFBIG;
		जाओ out_मुक्त;
	पूर्ण

	new_size = round_करोwn(new_size, fs_info->sectorsize);

	अगर (new_size > old_size) अणु
		trans = btrfs_start_transaction(root, 0);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			जाओ out_मुक्त;
		पूर्ण
		ret = btrfs_grow_device(trans, device, new_size);
		btrfs_commit_transaction(trans);
	पूर्ण अन्यथा अगर (new_size < old_size) अणु
		ret = btrfs_shrink_device(device, new_size);
	पूर्ण /* equal, nothing need to करो */

	अगर (ret == 0 && new_size != old_size)
		btrfs_info_in_rcu(fs_info,
			"resize device %s (devid %llu) from %llu to %llu",
			rcu_str_deref(device->name), device->devid,
			old_size, new_size);
out_मुक्त:
	kमुक्त(vol_args);
out:
	btrfs_exclop_finish(fs_info);
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक __btrfs_ioctl_snap_create(काष्ठा file *file,
				स्थिर अक्षर *name, अचिन्हित दीर्घ fd, पूर्णांक subvol,
				bool पढ़ोonly,
				काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	पूर्णांक namelen;
	पूर्णांक ret = 0;

	अगर (!S_ISसूची(file_inode(file)->i_mode))
		वापस -ENOTसूची;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		जाओ out;

	namelen = म_माप(name);
	अगर (म_अक्षर(name, '/')) अणु
		ret = -EINVAL;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (name[0] == '.' &&
	   (namelen == 1 || (name[1] == '.' && namelen == 2))) अणु
		ret = -EEXIST;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (subvol) अणु
		ret = btrfs_mksubvol(&file->f_path, name, namelen,
				     शून्य, पढ़ोonly, inherit);
	पूर्ण अन्यथा अणु
		काष्ठा fd src = fdget(fd);
		काष्ठा inode *src_inode;
		अगर (!src.file) अणु
			ret = -EINVAL;
			जाओ out_drop_ग_लिखो;
		पूर्ण

		src_inode = file_inode(src.file);
		अगर (src_inode->i_sb != file_inode(file)->i_sb) अणु
			btrfs_info(BTRFS_I(file_inode(file))->root->fs_info,
				   "Snapshot src from another FS");
			ret = -EXDEV;
		पूर्ण अन्यथा अगर (!inode_owner_or_capable(&init_user_ns, src_inode)) अणु
			/*
			 * Subvolume creation is not restricted, but snapshots
			 * are limited to own subvolumes only
			 */
			ret = -EPERM;
		पूर्ण अन्यथा अणु
			ret = btrfs_mksnapshot(&file->f_path, name, namelen,
					     BTRFS_I(src_inode)->root,
					     पढ़ोonly, inherit);
		पूर्ण
		fdput(src);
	पूर्ण
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
out:
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_snap_create(काष्ठा file *file,
					    व्योम __user *arg, पूर्णांक subvol)
अणु
	काष्ठा btrfs_ioctl_vol_args *vol_args;
	पूर्णांक ret;

	अगर (!S_ISसूची(file_inode(file)->i_mode))
		वापस -ENOTसूची;

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args))
		वापस PTR_ERR(vol_args);
	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';

	ret = __btrfs_ioctl_snap_create(file, vol_args->name, vol_args->fd,
					subvol, false, शून्य);

	kमुक्त(vol_args);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_snap_create_v2(काष्ठा file *file,
					       व्योम __user *arg, पूर्णांक subvol)
अणु
	काष्ठा btrfs_ioctl_vol_args_v2 *vol_args;
	पूर्णांक ret;
	bool पढ़ोonly = false;
	काष्ठा btrfs_qgroup_inherit *inherit = शून्य;

	अगर (!S_ISसूची(file_inode(file)->i_mode))
		वापस -ENOTसूची;

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args))
		वापस PTR_ERR(vol_args);
	vol_args->name[BTRFS_SUBVOL_NAME_MAX] = '\0';

	अगर (vol_args->flags & ~BTRFS_SUBVOL_CREATE_ARGS_MASK) अणु
		ret = -EOPNOTSUPP;
		जाओ मुक्त_args;
	पूर्ण

	अगर (vol_args->flags & BTRFS_SUBVOL_RDONLY)
		पढ़ोonly = true;
	अगर (vol_args->flags & BTRFS_SUBVOL_QGROUP_INHERIT) अणु
		u64 nums;

		अगर (vol_args->size < माप(*inherit) ||
		    vol_args->size > PAGE_SIZE) अणु
			ret = -EINVAL;
			जाओ मुक्त_args;
		पूर्ण
		inherit = memdup_user(vol_args->qgroup_inherit, vol_args->size);
		अगर (IS_ERR(inherit)) अणु
			ret = PTR_ERR(inherit);
			जाओ मुक्त_args;
		पूर्ण

		अगर (inherit->num_qgroups > PAGE_SIZE ||
		    inherit->num_ref_copies > PAGE_SIZE ||
		    inherit->num_excl_copies > PAGE_SIZE) अणु
			ret = -EINVAL;
			जाओ मुक्त_inherit;
		पूर्ण

		nums = inherit->num_qgroups + 2 * inherit->num_ref_copies +
		       2 * inherit->num_excl_copies;
		अगर (vol_args->size != काष्ठा_size(inherit, qgroups, nums)) अणु
			ret = -EINVAL;
			जाओ मुक्त_inherit;
		पूर्ण
	पूर्ण

	ret = __btrfs_ioctl_snap_create(file, vol_args->name, vol_args->fd,
					subvol, पढ़ोonly, inherit);
	अगर (ret)
		जाओ मुक्त_inherit;
मुक्त_inherit:
	kमुक्त(inherit);
मुक्त_args:
	kमुक्त(vol_args);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_subvol_getflags(काष्ठा file *file,
						व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक ret = 0;
	u64 flags = 0;

	अगर (btrfs_ino(BTRFS_I(inode)) != BTRFS_FIRST_FREE_OBJECTID)
		वापस -EINVAL;

	करोwn_पढ़ो(&fs_info->subvol_sem);
	अगर (btrfs_root_पढ़ोonly(root))
		flags |= BTRFS_SUBVOL_RDONLY;
	up_पढ़ो(&fs_info->subvol_sem);

	अगर (copy_to_user(arg, &flags, माप(flags)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_subvol_setflags(काष्ठा file *file,
					      व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	u64 root_flags;
	u64 flags;
	पूर्णांक ret = 0;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		जाओ out;

	अगर (btrfs_ino(BTRFS_I(inode)) != BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = -EINVAL;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (copy_from_user(&flags, arg, माप(flags))) अणु
		ret = -EFAULT;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (flags & ~BTRFS_SUBVOL_RDONLY) अणु
		ret = -EOPNOTSUPP;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	करोwn_ग_लिखो(&fs_info->subvol_sem);

	/* nothing to करो */
	अगर (!!(flags & BTRFS_SUBVOL_RDONLY) == btrfs_root_पढ़ोonly(root))
		जाओ out_drop_sem;

	root_flags = btrfs_root_flags(&root->root_item);
	अगर (flags & BTRFS_SUBVOL_RDONLY) अणु
		btrfs_set_root_flags(&root->root_item,
				     root_flags | BTRFS_ROOT_SUBVOL_RDONLY);
	पूर्ण अन्यथा अणु
		/*
		 * Block RO -> RW transition अगर this subvolume is involved in
		 * send
		 */
		spin_lock(&root->root_item_lock);
		अगर (root->send_in_progress == 0) अणु
			btrfs_set_root_flags(&root->root_item,
				     root_flags & ~BTRFS_ROOT_SUBVOL_RDONLY);
			spin_unlock(&root->root_item_lock);
		पूर्ण अन्यथा अणु
			spin_unlock(&root->root_item_lock);
			btrfs_warn(fs_info,
				   "Attempt to set subvolume %llu read-write during send",
				   root->root_key.objectid);
			ret = -EPERM;
			जाओ out_drop_sem;
		पूर्ण
	पूर्ण

	trans = btrfs_start_transaction(root, 1);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_reset;
	पूर्ण

	ret = btrfs_update_root(trans, fs_info->tree_root,
				&root->root_key, &root->root_item);
	अगर (ret < 0) अणु
		btrfs_end_transaction(trans);
		जाओ out_reset;
	पूर्ण

	ret = btrfs_commit_transaction(trans);

out_reset:
	अगर (ret)
		btrfs_set_root_flags(&root->root_item, root_flags);
out_drop_sem:
	up_ग_लिखो(&fs_info->subvol_sem);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
out:
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक key_in_sk(काष्ठा btrfs_key *key,
			      काष्ठा btrfs_ioctl_search_key *sk)
अणु
	काष्ठा btrfs_key test;
	पूर्णांक ret;

	test.objectid = sk->min_objectid;
	test.type = sk->min_type;
	test.offset = sk->min_offset;

	ret = btrfs_comp_cpu_keys(key, &test);
	अगर (ret < 0)
		वापस 0;

	test.objectid = sk->max_objectid;
	test.type = sk->max_type;
	test.offset = sk->max_offset;

	ret = btrfs_comp_cpu_keys(key, &test);
	अगर (ret > 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल noअंतरभूत पूर्णांक copy_to_sk(काष्ठा btrfs_path *path,
			       काष्ठा btrfs_key *key,
			       काष्ठा btrfs_ioctl_search_key *sk,
			       माप_प्रकार *buf_size,
			       अक्षर __user *ubuf,
			       अचिन्हित दीर्घ *sk_offset,
			       पूर्णांक *num_found)
अणु
	u64 found_transid;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_ioctl_search_header sh;
	काष्ठा btrfs_key test;
	अचिन्हित दीर्घ item_off;
	अचिन्हित दीर्घ item_len;
	पूर्णांक nritems;
	पूर्णांक i;
	पूर्णांक slot;
	पूर्णांक ret = 0;

	leaf = path->nodes[0];
	slot = path->slots[0];
	nritems = btrfs_header_nritems(leaf);

	अगर (btrfs_header_generation(leaf) > sk->max_transid) अणु
		i = nritems;
		जाओ advance_key;
	पूर्ण
	found_transid = btrfs_header_generation(leaf);

	क्रम (i = slot; i < nritems; i++) अणु
		item_off = btrfs_item_ptr_offset(leaf, i);
		item_len = btrfs_item_size_nr(leaf, i);

		btrfs_item_key_to_cpu(leaf, key, i);
		अगर (!key_in_sk(key, sk))
			जारी;

		अगर (माप(sh) + item_len > *buf_size) अणु
			अगर (*num_found) अणु
				ret = 1;
				जाओ out;
			पूर्ण

			/*
			 * वापस one empty item back क्रम v1, which करोes not
			 * handle -EOVERFLOW
			 */

			*buf_size = माप(sh) + item_len;
			item_len = 0;
			ret = -EOVERFLOW;
		पूर्ण

		अगर (माप(sh) + item_len + *sk_offset > *buf_size) अणु
			ret = 1;
			जाओ out;
		पूर्ण

		sh.objectid = key->objectid;
		sh.offset = key->offset;
		sh.type = key->type;
		sh.len = item_len;
		sh.transid = found_transid;

		/*
		 * Copy search result header. If we fault then loop again so we
		 * can fault in the pages and -EFAULT there अगर there's a
		 * problem. Otherwise we'll fault and then copy the buffer in
		 * properly this next समय through
		 */
		अगर (copy_to_user_nofault(ubuf + *sk_offset, &sh, माप(sh))) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		*sk_offset += माप(sh);

		अगर (item_len) अणु
			अक्षर __user *up = ubuf + *sk_offset;
			/*
			 * Copy the item, same behavior as above, but reset the
			 * * sk_offset so we copy the full thing again.
			 */
			अगर (पढ़ो_extent_buffer_to_user_nofault(leaf, up,
						item_off, item_len)) अणु
				ret = 0;
				*sk_offset -= माप(sh);
				जाओ out;
			पूर्ण

			*sk_offset += item_len;
		पूर्ण
		(*num_found)++;

		अगर (ret) /* -EOVERFLOW from above */
			जाओ out;

		अगर (*num_found >= sk->nr_items) अणु
			ret = 1;
			जाओ out;
		पूर्ण
	पूर्ण
advance_key:
	ret = 0;
	test.objectid = sk->max_objectid;
	test.type = sk->max_type;
	test.offset = sk->max_offset;
	अगर (btrfs_comp_cpu_keys(key, &test) >= 0)
		ret = 1;
	अन्यथा अगर (key->offset < (u64)-1)
		key->offset++;
	अन्यथा अगर (key->type < (u8)-1) अणु
		key->offset = 0;
		key->type++;
	पूर्ण अन्यथा अगर (key->objectid < (u64)-1) अणु
		key->offset = 0;
		key->type = 0;
		key->objectid++;
	पूर्ण अन्यथा
		ret = 1;
out:
	/*
	 *  0: all items from this leaf copied, जारी with next
	 *  1: * more items can be copied, but unused buffer is too small
	 *     * all items were found
	 *     Either way, it will stops the loop which iterates to the next
	 *     leaf
	 *  -EOVERFLOW: item was to large क्रम buffer
	 *  -EFAULT: could not copy extent buffer back to userspace
	 */
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक search_ioctl(काष्ठा inode *inode,
				 काष्ठा btrfs_ioctl_search_key *sk,
				 माप_प्रकार *buf_size,
				 अक्षर __user *ubuf)
अणु
	काष्ठा btrfs_fs_info *info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	पूर्णांक num_found = 0;
	अचिन्हित दीर्घ sk_offset = 0;

	अगर (*buf_size < माप(काष्ठा btrfs_ioctl_search_header)) अणु
		*buf_size = माप(काष्ठा btrfs_ioctl_search_header);
		वापस -EOVERFLOW;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	अगर (sk->tree_id == 0) अणु
		/* search the root of the inode that was passed */
		root = btrfs_grab_root(BTRFS_I(inode)->root);
	पूर्ण अन्यथा अणु
		root = btrfs_get_fs_root(info, sk->tree_id, true);
		अगर (IS_ERR(root)) अणु
			btrfs_मुक्त_path(path);
			वापस PTR_ERR(root);
		पूर्ण
	पूर्ण

	key.objectid = sk->min_objectid;
	key.type = sk->min_type;
	key.offset = sk->min_offset;

	जबतक (1) अणु
		ret = fault_in_pages_ग_लिखोable(ubuf + sk_offset,
					       *buf_size - sk_offset);
		अगर (ret)
			अवरोध;

		ret = btrfs_search_क्रमward(root, &key, path, sk->min_transid);
		अगर (ret != 0) अणु
			अगर (ret > 0)
				ret = 0;
			जाओ err;
		पूर्ण
		ret = copy_to_sk(path, &key, sk, buf_size, ubuf,
				 &sk_offset, &num_found);
		btrfs_release_path(path);
		अगर (ret)
			अवरोध;

	पूर्ण
	अगर (ret > 0)
		ret = 0;
err:
	sk->nr_items = num_found;
	btrfs_put_root(root);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_tree_search(काष्ठा file *file,
					   व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_search_args __user *uargs;
	काष्ठा btrfs_ioctl_search_key sk;
	काष्ठा inode *inode;
	पूर्णांक ret;
	माप_प्रकार buf_size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	uargs = (काष्ठा btrfs_ioctl_search_args __user *)argp;

	अगर (copy_from_user(&sk, &uargs->key, माप(sk)))
		वापस -EFAULT;

	buf_size = माप(uargs->buf);

	inode = file_inode(file);
	ret = search_ioctl(inode, &sk, &buf_size, uargs->buf);

	/*
	 * In the origin implementation an overflow is handled by वापसing a
	 * search header with a len of zero, so reset ret.
	 */
	अगर (ret == -EOVERFLOW)
		ret = 0;

	अगर (ret == 0 && copy_to_user(&uargs->key, &sk, माप(sk)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_tree_search_v2(काष्ठा file *file,
					       व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_search_args_v2 __user *uarg;
	काष्ठा btrfs_ioctl_search_args_v2 args;
	काष्ठा inode *inode;
	पूर्णांक ret;
	माप_प्रकार buf_size;
	स्थिर माप_प्रकार buf_limit = SZ_16M;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/* copy search header and buffer size */
	uarg = (काष्ठा btrfs_ioctl_search_args_v2 __user *)argp;
	अगर (copy_from_user(&args, uarg, माप(args)))
		वापस -EFAULT;

	buf_size = args.buf_size;

	/* limit result size to 16MB */
	अगर (buf_size > buf_limit)
		buf_size = buf_limit;

	inode = file_inode(file);
	ret = search_ioctl(inode, &args.key, &buf_size,
			   (अक्षर __user *)(&uarg->buf[0]));
	अगर (ret == 0 && copy_to_user(&uarg->key, &args.key, माप(args.key)))
		ret = -EFAULT;
	अन्यथा अगर (ret == -EOVERFLOW &&
		copy_to_user(&uarg->buf_size, &buf_size, माप(buf_size)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

/*
 * Search INODE_REFs to identअगरy path name of 'dirid' directory
 * in a 'tree_id' tree. and sets path name to 'name'.
 */
अटल noअंतरभूत पूर्णांक btrfs_search_path_in_tree(काष्ठा btrfs_fs_info *info,
				u64 tree_id, u64 dirid, अक्षर *name)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	अक्षर *ptr;
	पूर्णांक ret = -1;
	पूर्णांक slot;
	पूर्णांक len;
	पूर्णांक total_len = 0;
	काष्ठा btrfs_inode_ref *iref;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_path *path;

	अगर (dirid == BTRFS_FIRST_FREE_OBJECTID) अणु
		name[0]='\0';
		वापस 0;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ptr = &name[BTRFS_INO_LOOKUP_PATH_MAX - 1];

	root = btrfs_get_fs_root(info, tree_id, true);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		root = शून्य;
		जाओ out;
	पूर्ण

	key.objectid = dirid;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = (u64)-1;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			जाओ out;
		अन्यथा अगर (ret > 0) अणु
			ret = btrfs_previous_item(root, path, dirid,
						  BTRFS_INODE_REF_KEY);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0) अणु
				ret = -ENOENT;
				जाओ out;
			पूर्ण
		पूर्ण

		l = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(l, &key, slot);

		iref = btrfs_item_ptr(l, slot, काष्ठा btrfs_inode_ref);
		len = btrfs_inode_ref_name_len(l, iref);
		ptr -= len + 1;
		total_len += len + 1;
		अगर (ptr < name) अणु
			ret = -ENAMETOOLONG;
			जाओ out;
		पूर्ण

		*(ptr + len) = '/';
		पढ़ो_extent_buffer(l, ptr, (अचिन्हित दीर्घ)(iref + 1), len);

		अगर (key.offset == BTRFS_FIRST_FREE_OBJECTID)
			अवरोध;

		btrfs_release_path(path);
		key.objectid = key.offset;
		key.offset = (u64)-1;
		dirid = key.objectid;
	पूर्ण
	स_हटाओ(name, ptr, total_len);
	name[total_len] = '\0';
	ret = 0;
out:
	btrfs_put_root(root);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_search_path_in_tree_user(काष्ठा inode *inode,
				काष्ठा btrfs_ioctl_ino_lookup_user_args *args)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा btrfs_key upper_limit = BTRFS_I(inode)->location;
	u64 treeid = BTRFS_I(inode)->root->root_key.objectid;
	u64 dirid = args->dirid;
	अचिन्हित दीर्घ item_off;
	अचिन्हित दीर्घ item_len;
	काष्ठा btrfs_inode_ref *iref;
	काष्ठा btrfs_root_ref *rref;
	काष्ठा btrfs_root *root = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key, key2;
	काष्ठा extent_buffer *leaf;
	काष्ठा inode *temp_inode;
	अक्षर *ptr;
	पूर्णांक slot;
	पूर्णांक len;
	पूर्णांक total_len = 0;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * If the bottom subvolume करोes not exist directly under upper_limit,
	 * स्थिरruct the path in from the bottom up.
	 */
	अगर (dirid != upper_limit.objectid) अणु
		ptr = &args->path[BTRFS_INO_LOOKUP_USER_PATH_MAX - 1];

		root = btrfs_get_fs_root(fs_info, treeid, true);
		अगर (IS_ERR(root)) अणु
			ret = PTR_ERR(root);
			जाओ out;
		पूर्ण

		key.objectid = dirid;
		key.type = BTRFS_INODE_REF_KEY;
		key.offset = (u64)-1;
		जबतक (1) अणु
			ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
			अगर (ret < 0) अणु
				जाओ out_put;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = btrfs_previous_item(root, path, dirid,
							  BTRFS_INODE_REF_KEY);
				अगर (ret < 0) अणु
					जाओ out_put;
				पूर्ण अन्यथा अगर (ret > 0) अणु
					ret = -ENOENT;
					जाओ out_put;
				पूर्ण
			पूर्ण

			leaf = path->nodes[0];
			slot = path->slots[0];
			btrfs_item_key_to_cpu(leaf, &key, slot);

			iref = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_inode_ref);
			len = btrfs_inode_ref_name_len(leaf, iref);
			ptr -= len + 1;
			total_len += len + 1;
			अगर (ptr < args->path) अणु
				ret = -ENAMETOOLONG;
				जाओ out_put;
			पूर्ण

			*(ptr + len) = '/';
			पढ़ो_extent_buffer(leaf, ptr,
					(अचिन्हित दीर्घ)(iref + 1), len);

			/* Check the पढ़ो+exec permission of this directory */
			ret = btrfs_previous_item(root, path, dirid,
						  BTRFS_INODE_ITEM_KEY);
			अगर (ret < 0) अणु
				जाओ out_put;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = -ENOENT;
				जाओ out_put;
			पूर्ण

			leaf = path->nodes[0];
			slot = path->slots[0];
			btrfs_item_key_to_cpu(leaf, &key2, slot);
			अगर (key2.objectid != dirid) अणु
				ret = -ENOENT;
				जाओ out_put;
			पूर्ण

			temp_inode = btrfs_iget(sb, key2.objectid, root);
			अगर (IS_ERR(temp_inode)) अणु
				ret = PTR_ERR(temp_inode);
				जाओ out_put;
			पूर्ण
			ret = inode_permission(&init_user_ns, temp_inode,
					       MAY_READ | MAY_EXEC);
			iput(temp_inode);
			अगर (ret) अणु
				ret = -EACCES;
				जाओ out_put;
			पूर्ण

			अगर (key.offset == upper_limit.objectid)
				अवरोध;
			अगर (key.objectid == BTRFS_FIRST_FREE_OBJECTID) अणु
				ret = -EACCES;
				जाओ out_put;
			पूर्ण

			btrfs_release_path(path);
			key.objectid = key.offset;
			key.offset = (u64)-1;
			dirid = key.objectid;
		पूर्ण

		स_हटाओ(args->path, ptr, total_len);
		args->path[total_len] = '\0';
		btrfs_put_root(root);
		root = शून्य;
		btrfs_release_path(path);
	पूर्ण

	/* Get the bottom subvolume's name from ROOT_REF */
	key.objectid = treeid;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = args->treeid;
	ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	slot = path->slots[0];
	btrfs_item_key_to_cpu(leaf, &key, slot);

	item_off = btrfs_item_ptr_offset(leaf, slot);
	item_len = btrfs_item_size_nr(leaf, slot);
	/* Check अगर dirid in ROOT_REF corresponds to passed dirid */
	rref = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_root_ref);
	अगर (args->dirid != btrfs_root_ref_dirid(leaf, rref)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Copy subvolume's name */
	item_off += माप(काष्ठा btrfs_root_ref);
	item_len -= माप(काष्ठा btrfs_root_ref);
	पढ़ो_extent_buffer(leaf, args->name, item_off, item_len);
	args->name[item_len] = 0;

out_put:
	btrfs_put_root(root);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_ino_lookup(काष्ठा file *file,
					   व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_ino_lookup_args *args;
	काष्ठा inode *inode;
	पूर्णांक ret = 0;

	args = memdup_user(argp, माप(*args));
	अगर (IS_ERR(args))
		वापस PTR_ERR(args);

	inode = file_inode(file);

	/*
	 * Unprivileged query to obtain the containing subvolume root id. The
	 * path is reset so it's consistent with btrfs_search_path_in_tree.
	 */
	अगर (args->treeid == 0)
		args->treeid = BTRFS_I(inode)->root->root_key.objectid;

	अगर (args->objectid == BTRFS_FIRST_FREE_OBJECTID) अणु
		args->name[0] = 0;
		जाओ out;
	पूर्ण

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	ret = btrfs_search_path_in_tree(BTRFS_I(inode)->root->fs_info,
					args->treeid, args->objectid,
					args->name);

out:
	अगर (ret == 0 && copy_to_user(argp, args, माप(*args)))
		ret = -EFAULT;

	kमुक्त(args);
	वापस ret;
पूर्ण

/*
 * Version of ino_lookup ioctl (unprivileged)
 *
 * The मुख्य dअगरferences from ino_lookup ioctl are:
 *
 *   1. Read + Exec permission will be checked using inode_permission() during
 *      path स्थिरruction. -EACCES will be वापसed in हाल of failure.
 *   2. Path स्थिरruction will be stopped at the inode number which corresponds
 *      to the fd with which this ioctl is called. If स्थिरructed path करोes not
 *      exist under fd's inode, -EACCES will be वापसed.
 *   3. The name of bottom subvolume is also searched and filled.
 */
अटल पूर्णांक btrfs_ioctl_ino_lookup_user(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_ino_lookup_user_args *args;
	काष्ठा inode *inode;
	पूर्णांक ret;

	args = memdup_user(argp, माप(*args));
	अगर (IS_ERR(args))
		वापस PTR_ERR(args);

	inode = file_inode(file);

	अगर (args->dirid == BTRFS_FIRST_FREE_OBJECTID &&
	    BTRFS_I(inode)->location.objectid != BTRFS_FIRST_FREE_OBJECTID) अणु
		/*
		 * The subvolume करोes not exist under fd with which this is
		 * called
		 */
		kमुक्त(args);
		वापस -EACCES;
	पूर्ण

	ret = btrfs_search_path_in_tree_user(inode, args);

	अगर (ret == 0 && copy_to_user(argp, args, माप(*args)))
		ret = -EFAULT;

	kमुक्त(args);
	वापस ret;
पूर्ण

/* Get the subvolume inक्रमmation in BTRFS_ROOT_ITEM and BTRFS_ROOT_BACKREF */
अटल पूर्णांक btrfs_ioctl_get_subvol_info(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_get_subvol_info_args *subvol_info;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_root_ref *rref;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ item_off;
	अचिन्हित दीर्घ item_len;
	काष्ठा inode *inode;
	पूर्णांक slot;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	subvol_info = kzalloc(माप(*subvol_info), GFP_KERNEL);
	अगर (!subvol_info) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	inode = file_inode(file);
	fs_info = BTRFS_I(inode)->root->fs_info;

	/* Get root_item of inode's subvolume */
	key.objectid = BTRFS_I(inode)->root->root_key.objectid;
	root = btrfs_get_fs_root(fs_info, key.objectid, true);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ out_मुक्त;
	पूर्ण
	root_item = &root->root_item;

	subvol_info->treeid = key.objectid;

	subvol_info->generation = btrfs_root_generation(root_item);
	subvol_info->flags = btrfs_root_flags(root_item);

	स_नकल(subvol_info->uuid, root_item->uuid, BTRFS_UUID_SIZE);
	स_नकल(subvol_info->parent_uuid, root_item->parent_uuid,
						    BTRFS_UUID_SIZE);
	स_नकल(subvol_info->received_uuid, root_item->received_uuid,
						    BTRFS_UUID_SIZE);

	subvol_info->ctransid = btrfs_root_ctransid(root_item);
	subvol_info->स_समय.sec = btrfs_stack_बारpec_sec(&root_item->स_समय);
	subvol_info->स_समय.nsec = btrfs_stack_बारpec_nsec(&root_item->स_समय);

	subvol_info->otransid = btrfs_root_otransid(root_item);
	subvol_info->oसमय.sec = btrfs_stack_बारpec_sec(&root_item->oसमय);
	subvol_info->oसमय.nsec = btrfs_stack_बारpec_nsec(&root_item->oसमय);

	subvol_info->stransid = btrfs_root_stransid(root_item);
	subvol_info->sसमय.sec = btrfs_stack_बारpec_sec(&root_item->sसमय);
	subvol_info->sसमय.nsec = btrfs_stack_बारpec_nsec(&root_item->sसमय);

	subvol_info->rtransid = btrfs_root_rtransid(root_item);
	subvol_info->rसमय.sec = btrfs_stack_बारpec_sec(&root_item->rसमय);
	subvol_info->rसमय.nsec = btrfs_stack_बारpec_nsec(&root_item->rसमय);

	अगर (key.objectid != BTRFS_FS_TREE_OBJECTID) अणु
		/* Search root tree क्रम ROOT_BACKREF of this subvolume */
		key.type = BTRFS_ROOT_BACKREF_KEY;
		key.offset = 0;
		ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (path->slots[0] >=
			   btrfs_header_nritems(path->nodes[0])) अणु
			ret = btrfs_next_leaf(fs_info->tree_root, path);
			अगर (ret < 0) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = -EUCLEAN;
				जाओ out;
			पूर्ण
		पूर्ण

		leaf = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid == subvol_info->treeid &&
		    key.type == BTRFS_ROOT_BACKREF_KEY) अणु
			subvol_info->parent_id = key.offset;

			rref = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_root_ref);
			subvol_info->dirid = btrfs_root_ref_dirid(leaf, rref);

			item_off = btrfs_item_ptr_offset(leaf, slot)
					+ माप(काष्ठा btrfs_root_ref);
			item_len = btrfs_item_size_nr(leaf, slot)
					- माप(काष्ठा btrfs_root_ref);
			पढ़ो_extent_buffer(leaf, subvol_info->name,
					   item_off, item_len);
		पूर्ण अन्यथा अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(argp, subvol_info, माप(*subvol_info)))
		ret = -EFAULT;

out:
	btrfs_put_root(root);
out_मुक्त:
	btrfs_मुक्त_path(path);
	kमुक्त(subvol_info);
	वापस ret;
पूर्ण

/*
 * Return ROOT_REF inक्रमmation of the subvolume containing this inode
 * except the subvolume name.
 */
अटल पूर्णांक btrfs_ioctl_get_subvol_rootref(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा btrfs_ioctl_get_subvol_rootref_args *rootrefs;
	काष्ठा btrfs_root_ref *rref;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा inode *inode;
	u64 objectid;
	पूर्णांक slot;
	पूर्णांक ret;
	u8 found;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	rootrefs = memdup_user(argp, माप(*rootrefs));
	अगर (IS_ERR(rootrefs)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(rootrefs);
	पूर्ण

	inode = file_inode(file);
	root = BTRFS_I(inode)->root->fs_info->tree_root;
	objectid = BTRFS_I(inode)->root->root_key.objectid;

	key.objectid = objectid;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = rootrefs->min_treeid;
	found = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (path->slots[0] >=
		   btrfs_header_nritems(path->nodes[0])) अणु
		ret = btrfs_next_leaf(root, path);
		अगर (ret < 0) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण
	जबतक (1) अणु
		leaf = path->nodes[0];
		slot = path->slots[0];

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid != objectid || key.type != BTRFS_ROOT_REF_KEY) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		अगर (found == BTRFS_MAX_ROOTREF_BUFFER_NUM) अणु
			ret = -EOVERFLOW;
			जाओ out;
		पूर्ण

		rref = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_root_ref);
		rootrefs->rootref[found].treeid = key.offset;
		rootrefs->rootref[found].dirid =
				  btrfs_root_ref_dirid(leaf, rref);
		found++;

		ret = btrfs_next_item(root, path);
		अगर (ret < 0) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (!ret || ret == -EOVERFLOW) अणु
		rootrefs->num_items = found;
		/* update min_treeid क्रम next search */
		अगर (found)
			rootrefs->min_treeid =
				rootrefs->rootref[found - 1].treeid + 1;
		अगर (copy_to_user(argp, rootrefs, माप(*rootrefs)))
			ret = -EFAULT;
	पूर्ण

	kमुक्त(rootrefs);
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_ioctl_snap_destroy(काष्ठा file *file,
					     व्योम __user *arg,
					     bool destroy_v2)
अणु
	काष्ठा dentry *parent = file->f_path.dentry;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(parent->d_sb);
	काष्ठा dentry *dentry;
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा inode *inode;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_root *dest = शून्य;
	काष्ठा btrfs_ioctl_vol_args *vol_args = शून्य;
	काष्ठा btrfs_ioctl_vol_args_v2 *vol_args2 = शून्य;
	अक्षर *subvol_name, *subvol_name_ptr = शून्य;
	पूर्णांक subvol_namelen;
	पूर्णांक err = 0;
	bool destroy_parent = false;

	अगर (destroy_v2) अणु
		vol_args2 = memdup_user(arg, माप(*vol_args2));
		अगर (IS_ERR(vol_args2))
			वापस PTR_ERR(vol_args2);

		अगर (vol_args2->flags & ~BTRFS_SUBVOL_DELETE_ARGS_MASK) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		/*
		 * If SPEC_BY_ID is not set, we are looking क्रम the subvolume by
		 * name, same as v1 currently करोes.
		 */
		अगर (!(vol_args2->flags & BTRFS_SUBVOL_SPEC_BY_ID)) अणु
			vol_args2->name[BTRFS_SUBVOL_NAME_MAX] = 0;
			subvol_name = vol_args2->name;

			err = mnt_want_ग_लिखो_file(file);
			अगर (err)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (vol_args2->subvolid < BTRFS_FIRST_FREE_OBJECTID) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			err = mnt_want_ग_लिखो_file(file);
			अगर (err)
				जाओ out;

			dentry = btrfs_get_dentry(fs_info->sb,
					BTRFS_FIRST_FREE_OBJECTID,
					vol_args2->subvolid, 0, 0);
			अगर (IS_ERR(dentry)) अणु
				err = PTR_ERR(dentry);
				जाओ out_drop_ग_लिखो;
			पूर्ण

			/*
			 * Change the शेष parent since the subvolume being
			 * deleted can be outside of the current mount poपूर्णांक.
			 */
			parent = btrfs_get_parent(dentry);

			/*
			 * At this poपूर्णांक dentry->d_name can poपूर्णांक to '/' अगर the
			 * subvolume we want to destroy is outsite of the
			 * current mount poपूर्णांक, so we need to release the
			 * current dentry and execute the lookup to वापस a new
			 * one with ->d_name poपूर्णांकing to the
			 * <mount poपूर्णांक>/subvol_name.
			 */
			dput(dentry);
			अगर (IS_ERR(parent)) अणु
				err = PTR_ERR(parent);
				जाओ out_drop_ग_लिखो;
			पूर्ण
			dir = d_inode(parent);

			/*
			 * If v2 was used with SPEC_BY_ID, a new parent was
			 * allocated since the subvolume can be outside of the
			 * current mount poपूर्णांक. Later on we need to release this
			 * new parent dentry.
			 */
			destroy_parent = true;

			subvol_name_ptr = btrfs_get_subvol_name_from_objectid(
						fs_info, vol_args2->subvolid);
			अगर (IS_ERR(subvol_name_ptr)) अणु
				err = PTR_ERR(subvol_name_ptr);
				जाओ मुक्त_parent;
			पूर्ण
			/* subvol_name_ptr is alपढ़ोy शून्य termined */
			subvol_name = (अक्षर *)kbasename(subvol_name_ptr);
		पूर्ण
	पूर्ण अन्यथा अणु
		vol_args = memdup_user(arg, माप(*vol_args));
		अगर (IS_ERR(vol_args))
			वापस PTR_ERR(vol_args);

		vol_args->name[BTRFS_PATH_NAME_MAX] = 0;
		subvol_name = vol_args->name;

		err = mnt_want_ग_लिखो_file(file);
		अगर (err)
			जाओ out;
	पूर्ण

	subvol_namelen = म_माप(subvol_name);

	अगर (म_अक्षर(subvol_name, '/') ||
	    म_भेदन(subvol_name, "..", subvol_namelen) == 0) अणु
		err = -EINVAL;
		जाओ मुक्त_subvol_name;
	पूर्ण

	अगर (!S_ISसूची(dir->i_mode)) अणु
		err = -ENOTसूची;
		जाओ मुक्त_subvol_name;
	पूर्ण

	err = करोwn_ग_लिखो_समाप्तable_nested(&dir->i_rwsem, I_MUTEX_PARENT);
	अगर (err == -EINTR)
		जाओ मुक्त_subvol_name;
	dentry = lookup_one_len(subvol_name, parent, subvol_namelen);
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ out_unlock_dir;
	पूर्ण

	अगर (d_really_is_negative(dentry)) अणु
		err = -ENOENT;
		जाओ out_dput;
	पूर्ण

	inode = d_inode(dentry);
	dest = BTRFS_I(inode)->root;
	अगर (!capable(CAP_SYS_ADMIN)) अणु
		/*
		 * Regular user.  Only allow this with a special mount
		 * option, when the user has ग_लिखो+exec access to the
		 * subvol root, and when सूची_हटाओ(2) would have been
		 * allowed.
		 *
		 * Note that this is _not_ check that the subvol is
		 * empty or करोesn't contain data that we wouldn't
		 * otherwise be able to delete.
		 *
		 * Users who want to delete empty subvols should try
		 * सूची_हटाओ(2).
		 */
		err = -EPERM;
		अगर (!btrfs_test_opt(fs_info, USER_SUBVOL_RM_ALLOWED))
			जाओ out_dput;

		/*
		 * Do not allow deletion अगर the parent dir is the same
		 * as the dir to be deleted.  That means the ioctl
		 * must be called on the dentry referencing the root
		 * of the subvol, not a अक्रमom directory contained
		 * within it.
		 */
		err = -EINVAL;
		अगर (root == dest)
			जाओ out_dput;

		err = inode_permission(&init_user_ns, inode,
				       MAY_WRITE | MAY_EXEC);
		अगर (err)
			जाओ out_dput;
	पूर्ण

	/* check अगर subvolume may be deleted by a user */
	err = btrfs_may_delete(dir, dentry, 1);
	अगर (err)
		जाओ out_dput;

	अगर (btrfs_ino(BTRFS_I(inode)) != BTRFS_FIRST_FREE_OBJECTID) अणु
		err = -EINVAL;
		जाओ out_dput;
	पूर्ण

	btrfs_inode_lock(inode, 0);
	err = btrfs_delete_subvolume(dir, dentry);
	btrfs_inode_unlock(inode, 0);
	अगर (!err) अणु
		fsnotअगरy_सूची_हटाओ(dir, dentry);
		d_delete(dentry);
	पूर्ण

out_dput:
	dput(dentry);
out_unlock_dir:
	btrfs_inode_unlock(dir, 0);
मुक्त_subvol_name:
	kमुक्त(subvol_name_ptr);
मुक्त_parent:
	अगर (destroy_parent)
		dput(parent);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
out:
	kमुक्त(vol_args2);
	kमुक्त(vol_args);
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_ioctl_defrag(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_ioctl_defrag_range_args *range;
	पूर्णांक ret;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	अगर (btrfs_root_पढ़ोonly(root)) अणु
		ret = -EROFS;
		जाओ out;
	पूर्ण

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFसूची:
		अगर (!capable(CAP_SYS_ADMIN)) अणु
			ret = -EPERM;
			जाओ out;
		पूर्ण
		ret = btrfs_defrag_root(root);
		अवरोध;
	हाल S_IFREG:
		/*
		 * Note that this करोes not check the file descriptor क्रम ग_लिखो
		 * access. This prevents defragmenting executables that are
		 * running and allows defrag on files खोलो in पढ़ो-only mode.
		 */
		अगर (!capable(CAP_SYS_ADMIN) &&
		    inode_permission(&init_user_ns, inode, MAY_WRITE)) अणु
			ret = -EPERM;
			जाओ out;
		पूर्ण

		range = kzalloc(माप(*range), GFP_KERNEL);
		अगर (!range) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (argp) अणु
			अगर (copy_from_user(range, argp,
					   माप(*range))) अणु
				ret = -EFAULT;
				kमुक्त(range);
				जाओ out;
			पूर्ण
			/* compression requires us to start the IO */
			अगर ((range->flags & BTRFS_DEFRAG_RANGE_COMPRESS)) अणु
				range->flags |= BTRFS_DEFRAG_RANGE_START_IO;
				range->extent_thresh = (u32)-1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* the rest are all set to zero by kzalloc */
			range->len = (u64)-1;
		पूर्ण
		ret = btrfs_defrag_file(file_inode(file), file,
					range, BTRFS_OLDEST_GENERATION, 0);
		अगर (ret > 0)
			ret = 0;
		kमुक्त(range);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
out:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_add_dev(काष्ठा btrfs_fs_info *fs_info, व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_vol_args *vol_args;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_DEV_ADD))
		वापस BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args)) अणु
		ret = PTR_ERR(vol_args);
		जाओ out;
	पूर्ण

	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';
	ret = btrfs_init_new_device(fs_info, vol_args->name);

	अगर (!ret)
		btrfs_info(fs_info, "disk added %s", vol_args->name);

	kमुक्त(vol_args);
out:
	btrfs_exclop_finish(fs_info);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_rm_dev_v2(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_ioctl_vol_args_v2 *vol_args;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args)) अणु
		ret = PTR_ERR(vol_args);
		जाओ err_drop;
	पूर्ण

	अगर (vol_args->flags & ~BTRFS_DEVICE_REMOVE_ARGS_MASK) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_DEV_REMOVE)) अणु
		ret = BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
		जाओ out;
	पूर्ण

	अगर (vol_args->flags & BTRFS_DEVICE_SPEC_BY_ID) अणु
		ret = btrfs_rm_device(fs_info, शून्य, vol_args->devid);
	पूर्ण अन्यथा अणु
		vol_args->name[BTRFS_SUBVOL_NAME_MAX] = '\0';
		ret = btrfs_rm_device(fs_info, vol_args->name, 0);
	पूर्ण
	btrfs_exclop_finish(fs_info);

	अगर (!ret) अणु
		अगर (vol_args->flags & BTRFS_DEVICE_SPEC_BY_ID)
			btrfs_info(fs_info, "device deleted: id %llu",
					vol_args->devid);
		अन्यथा
			btrfs_info(fs_info, "device deleted: %s",
					vol_args->name);
	पूर्ण
out:
	kमुक्त(vol_args);
err_drop:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_rm_dev(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_ioctl_vol_args *vol_args;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_DEV_REMOVE)) अणु
		ret = BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	vol_args = memdup_user(arg, माप(*vol_args));
	अगर (IS_ERR(vol_args)) अणु
		ret = PTR_ERR(vol_args);
		जाओ out;
	पूर्ण

	vol_args->name[BTRFS_PATH_NAME_MAX] = '\0';
	ret = btrfs_rm_device(fs_info, vol_args->name, 0);

	अगर (!ret)
		btrfs_info(fs_info, "disk deleted %s", vol_args->name);
	kमुक्त(vol_args);
out:
	btrfs_exclop_finish(fs_info);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);

	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_fs_info(काष्ठा btrfs_fs_info *fs_info,
				व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_fs_info_args *fi_args;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u64 flags_in;
	पूर्णांक ret = 0;

	fi_args = memdup_user(arg, माप(*fi_args));
	अगर (IS_ERR(fi_args))
		वापस PTR_ERR(fi_args);

	flags_in = fi_args->flags;
	स_रखो(fi_args, 0, माप(*fi_args));

	rcu_पढ़ो_lock();
	fi_args->num_devices = fs_devices->num_devices;

	list_क्रम_each_entry_rcu(device, &fs_devices->devices, dev_list) अणु
		अगर (device->devid > fi_args->max_id)
			fi_args->max_id = device->devid;
	पूर्ण
	rcu_पढ़ो_unlock();

	स_नकल(&fi_args->fsid, fs_devices->fsid, माप(fi_args->fsid));
	fi_args->nodesize = fs_info->nodesize;
	fi_args->sectorsize = fs_info->sectorsize;
	fi_args->clone_alignment = fs_info->sectorsize;

	अगर (flags_in & BTRFS_FS_INFO_FLAG_CSUM_INFO) अणु
		fi_args->csum_type = btrfs_super_csum_type(fs_info->super_copy);
		fi_args->csum_size = btrfs_super_csum_size(fs_info->super_copy);
		fi_args->flags |= BTRFS_FS_INFO_FLAG_CSUM_INFO;
	पूर्ण

	अगर (flags_in & BTRFS_FS_INFO_FLAG_GENERATION) अणु
		fi_args->generation = fs_info->generation;
		fi_args->flags |= BTRFS_FS_INFO_FLAG_GENERATION;
	पूर्ण

	अगर (flags_in & BTRFS_FS_INFO_FLAG_METADATA_UUID) अणु
		स_नकल(&fi_args->metadata_uuid, fs_devices->metadata_uuid,
		       माप(fi_args->metadata_uuid));
		fi_args->flags |= BTRFS_FS_INFO_FLAG_METADATA_UUID;
	पूर्ण

	अगर (copy_to_user(arg, fi_args, माप(*fi_args)))
		ret = -EFAULT;

	kमुक्त(fi_args);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_dev_info(काष्ठा btrfs_fs_info *fs_info,
				 व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_dev_info_args *di_args;
	काष्ठा btrfs_device *dev;
	पूर्णांक ret = 0;
	अक्षर *s_uuid = शून्य;

	di_args = memdup_user(arg, माप(*di_args));
	अगर (IS_ERR(di_args))
		वापस PTR_ERR(di_args);

	अगर (!btrfs_is_empty_uuid(di_args->uuid))
		s_uuid = di_args->uuid;

	rcu_पढ़ो_lock();
	dev = btrfs_find_device(fs_info->fs_devices, di_args->devid, s_uuid,
				शून्य);

	अगर (!dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	di_args->devid = dev->devid;
	di_args->bytes_used = btrfs_device_get_bytes_used(dev);
	di_args->total_bytes = btrfs_device_get_total_bytes(dev);
	स_नकल(di_args->uuid, dev->uuid, माप(di_args->uuid));
	अगर (dev->name) अणु
		म_नकलन(di_args->path, rcu_str_deref(dev->name),
				माप(di_args->path) - 1);
		di_args->path[माप(di_args->path) - 1] = 0;
	पूर्ण अन्यथा अणु
		di_args->path[0] = '\0';
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	अगर (ret == 0 && copy_to_user(arg, di_args, माप(*di_args)))
		ret = -EFAULT;

	kमुक्त(di_args);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_शेष_subvol(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_root *new_root;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_disk_key disk_key;
	u64 objectid = 0;
	u64 dir_id;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	अगर (copy_from_user(&objectid, argp, माप(objectid))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!objectid)
		objectid = BTRFS_FS_TREE_OBJECTID;

	new_root = btrfs_get_fs_root(fs_info, objectid, true);
	अगर (IS_ERR(new_root)) अणु
		ret = PTR_ERR(new_root);
		जाओ out;
	पूर्ण
	अगर (!is_fstree(new_root->root_key.objectid)) अणु
		ret = -ENOENT;
		जाओ out_मुक्त;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	trans = btrfs_start_transaction(root, 1);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_मुक्त;
	पूर्ण

	dir_id = btrfs_super_root_dir(fs_info->super_copy);
	di = btrfs_lookup_dir_item(trans, fs_info->tree_root, path,
				   dir_id, "default", 7, 1);
	अगर (IS_ERR_OR_शून्य(di)) अणु
		btrfs_release_path(path);
		btrfs_end_transaction(trans);
		btrfs_err(fs_info,
			  "Umm, you don't have the default diritem, this isn't going to work");
		ret = -ENOENT;
		जाओ out_मुक्त;
	पूर्ण

	btrfs_cpu_key_to_disk(&disk_key, &new_root->root_key);
	btrfs_set_dir_item_key(path->nodes[0], di, &disk_key);
	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_release_path(path);

	btrfs_set_fs_incompat(fs_info, DEFAULT_SUBVOL);
	btrfs_end_transaction(trans);
out_मुक्त:
	btrfs_put_root(new_root);
	btrfs_मुक्त_path(path);
out:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल व्योम get_block_group_info(काष्ठा list_head *groups_list,
				 काष्ठा btrfs_ioctl_space_info *space)
अणु
	काष्ठा btrfs_block_group *block_group;

	space->total_bytes = 0;
	space->used_bytes = 0;
	space->flags = 0;
	list_क्रम_each_entry(block_group, groups_list, list) अणु
		space->flags = block_group->flags;
		space->total_bytes += block_group->length;
		space->used_bytes += block_group->used;
	पूर्ण
पूर्ण

अटल दीर्घ btrfs_ioctl_space_info(काष्ठा btrfs_fs_info *fs_info,
				   व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_space_args space_args;
	काष्ठा btrfs_ioctl_space_info space;
	काष्ठा btrfs_ioctl_space_info *dest;
	काष्ठा btrfs_ioctl_space_info *dest_orig;
	काष्ठा btrfs_ioctl_space_info __user *user_dest;
	काष्ठा btrfs_space_info *info;
	अटल स्थिर u64 types[] = अणु
		BTRFS_BLOCK_GROUP_DATA,
		BTRFS_BLOCK_GROUP_SYSTEM,
		BTRFS_BLOCK_GROUP_METADATA,
		BTRFS_BLOCK_GROUP_DATA | BTRFS_BLOCK_GROUP_METADATA
	पूर्ण;
	पूर्णांक num_types = 4;
	पूर्णांक alloc_size;
	पूर्णांक ret = 0;
	u64 slot_count = 0;
	पूर्णांक i, c;

	अगर (copy_from_user(&space_args,
			   (काष्ठा btrfs_ioctl_space_args __user *)arg,
			   माप(space_args)))
		वापस -EFAULT;

	क्रम (i = 0; i < num_types; i++) अणु
		काष्ठा btrfs_space_info *पंचांगp;

		info = शून्य;
		list_क्रम_each_entry(पंचांगp, &fs_info->space_info, list) अणु
			अगर (पंचांगp->flags == types[i]) अणु
				info = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!info)
			जारी;

		करोwn_पढ़ो(&info->groups_sem);
		क्रम (c = 0; c < BTRFS_NR_RAID_TYPES; c++) अणु
			अगर (!list_empty(&info->block_groups[c]))
				slot_count++;
		पूर्ण
		up_पढ़ो(&info->groups_sem);
	पूर्ण

	/*
	 * Global block reserve, exported as a space_info
	 */
	slot_count++;

	/* space_slots == 0 means they are asking क्रम a count */
	अगर (space_args.space_slots == 0) अणु
		space_args.total_spaces = slot_count;
		जाओ out;
	पूर्ण

	slot_count = min_t(u64, space_args.space_slots, slot_count);

	alloc_size = माप(*dest) * slot_count;

	/* we generally have at most 6 or so space infos, one क्रम each raid
	 * level.  So, a whole page should be more than enough क्रम everyone
	 */
	अगर (alloc_size > PAGE_SIZE)
		वापस -ENOMEM;

	space_args.total_spaces = 0;
	dest = kदो_स्मृति(alloc_size, GFP_KERNEL);
	अगर (!dest)
		वापस -ENOMEM;
	dest_orig = dest;

	/* now we have a buffer to copy पूर्णांकo */
	क्रम (i = 0; i < num_types; i++) अणु
		काष्ठा btrfs_space_info *पंचांगp;

		अगर (!slot_count)
			अवरोध;

		info = शून्य;
		list_क्रम_each_entry(पंचांगp, &fs_info->space_info, list) अणु
			अगर (पंचांगp->flags == types[i]) अणु
				info = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!info)
			जारी;
		करोwn_पढ़ो(&info->groups_sem);
		क्रम (c = 0; c < BTRFS_NR_RAID_TYPES; c++) अणु
			अगर (!list_empty(&info->block_groups[c])) अणु
				get_block_group_info(&info->block_groups[c],
						     &space);
				स_नकल(dest, &space, माप(space));
				dest++;
				space_args.total_spaces++;
				slot_count--;
			पूर्ण
			अगर (!slot_count)
				अवरोध;
		पूर्ण
		up_पढ़ो(&info->groups_sem);
	पूर्ण

	/*
	 * Add global block reserve
	 */
	अगर (slot_count) अणु
		काष्ठा btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;

		spin_lock(&block_rsv->lock);
		space.total_bytes = block_rsv->size;
		space.used_bytes = block_rsv->size - block_rsv->reserved;
		spin_unlock(&block_rsv->lock);
		space.flags = BTRFS_SPACE_INFO_GLOBAL_RSV;
		स_नकल(dest, &space, माप(space));
		space_args.total_spaces++;
	पूर्ण

	user_dest = (काष्ठा btrfs_ioctl_space_info __user *)
		(arg + माप(काष्ठा btrfs_ioctl_space_args));

	अगर (copy_to_user(user_dest, dest_orig, alloc_size))
		ret = -EFAULT;

	kमुक्त(dest_orig);
out:
	अगर (ret == 0 && copy_to_user(arg, &space_args, माप(space_args)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल noअंतरभूत दीर्घ btrfs_ioctl_start_sync(काष्ठा btrfs_root *root,
					    व्योम __user *argp)
अणु
	काष्ठा btrfs_trans_handle *trans;
	u64 transid;
	पूर्णांक ret;

	trans = btrfs_attach_transaction_barrier(root);
	अगर (IS_ERR(trans)) अणु
		अगर (PTR_ERR(trans) != -ENOENT)
			वापस PTR_ERR(trans);

		/* No running transaction, करोn't bother */
		transid = root->fs_info->last_trans_committed;
		जाओ out;
	पूर्ण
	transid = trans->transid;
	ret = btrfs_commit_transaction_async(trans, 0);
	अगर (ret) अणु
		btrfs_end_transaction(trans);
		वापस ret;
	पूर्ण
out:
	अगर (argp)
		अगर (copy_to_user(argp, &transid, माप(transid)))
			वापस -EFAULT;
	वापस 0;
पूर्ण

अटल noअंतरभूत दीर्घ btrfs_ioctl_रुको_sync(काष्ठा btrfs_fs_info *fs_info,
					   व्योम __user *argp)
अणु
	u64 transid;

	अगर (argp) अणु
		अगर (copy_from_user(&transid, argp, माप(transid)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		transid = 0;  /* current trans */
	पूर्ण
	वापस btrfs_रुको_क्रम_commit(fs_info, transid);
पूर्ण

अटल दीर्घ btrfs_ioctl_scrub(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(file_inode(file)->i_sb);
	काष्ठा btrfs_ioctl_scrub_args *sa;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa))
		वापस PTR_ERR(sa);

	अगर (!(sa->flags & BTRFS_SCRUB_READONLY)) अणु
		ret = mnt_want_ग_लिखो_file(file);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = btrfs_scrub_dev(fs_info, sa->devid, sa->start, sa->end,
			      &sa->progress, sa->flags & BTRFS_SCRUB_READONLY,
			      0);

	/*
	 * Copy scrub args to user space even अगर btrfs_scrub_dev() वापसed an
	 * error. This is important as it allows user space to know how much
	 * progress scrub has करोne. For example, अगर scrub is canceled we get
	 * -ECANCELED from btrfs_scrub_dev() and वापस that error back to user
	 * space. Later user space can inspect the progress from the काष्ठाure
	 * btrfs_ioctl_scrub_args and resume scrub from where it left off
	 * previously (btrfs-progs करोes this).
	 * If we fail to copy the btrfs_ioctl_scrub_args काष्ठाure to user space
	 * then वापस -EFAULT to संकेत the काष्ठाure was not copied or it may
	 * be corrupt and unreliable due to a partial copy.
	 */
	अगर (copy_to_user(arg, sa, माप(*sa)))
		ret = -EFAULT;

	अगर (!(sa->flags & BTRFS_SCRUB_READONLY))
		mnt_drop_ग_लिखो_file(file);
out:
	kमुक्त(sa);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_scrub_cancel(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस btrfs_scrub_cancel(fs_info);
पूर्ण

अटल दीर्घ btrfs_ioctl_scrub_progress(काष्ठा btrfs_fs_info *fs_info,
				       व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_scrub_args *sa;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa))
		वापस PTR_ERR(sa);

	ret = btrfs_scrub_progress(fs_info, sa->devid, &sa->progress);

	अगर (ret == 0 && copy_to_user(arg, sa, माप(*sa)))
		ret = -EFAULT;

	kमुक्त(sa);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_get_dev_stats(काष्ठा btrfs_fs_info *fs_info,
				      व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_get_dev_stats *sa;
	पूर्णांक ret;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa))
		वापस PTR_ERR(sa);

	अगर ((sa->flags & BTRFS_DEV_STATS_RESET) && !capable(CAP_SYS_ADMIN)) अणु
		kमुक्त(sa);
		वापस -EPERM;
	पूर्ण

	ret = btrfs_get_dev_stats(fs_info, sa);

	अगर (ret == 0 && copy_to_user(arg, sa, माप(*sa)))
		ret = -EFAULT;

	kमुक्त(sa);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_dev_replace(काष्ठा btrfs_fs_info *fs_info,
				    व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_dev_replace_args *p;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	p = memdup_user(arg, माप(*p));
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	चयन (p->cmd) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_CMD_START:
		अगर (sb_rकरोnly(fs_info->sb)) अणु
			ret = -EROFS;
			जाओ out;
		पूर्ण
		अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_DEV_REPLACE)) अणु
			ret = BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
		पूर्ण अन्यथा अणु
			ret = btrfs_dev_replace_by_ioctl(fs_info, p);
			btrfs_exclop_finish(fs_info);
		पूर्ण
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_CMD_STATUS:
		btrfs_dev_replace_status(fs_info, p);
		ret = 0;
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_CMD_CANCEL:
		p->result = btrfs_dev_replace_cancel(fs_info);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर ((ret == 0 || ret == -ECANCELED) && copy_to_user(arg, p, माप(*p)))
		ret = -EFAULT;
out:
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_ino_to_path(काष्ठा btrfs_root *root, व्योम __user *arg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	u64 rel_ptr;
	पूर्णांक size;
	काष्ठा btrfs_ioctl_ino_path_args *ipa = शून्य;
	काष्ठा inode_fs_paths *ipath = शून्य;
	काष्ठा btrfs_path *path;

	अगर (!capable(CAP_DAC_READ_SEARCH))
		वापस -EPERM;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ipa = memdup_user(arg, माप(*ipa));
	अगर (IS_ERR(ipa)) अणु
		ret = PTR_ERR(ipa);
		ipa = शून्य;
		जाओ out;
	पूर्ण

	size = min_t(u32, ipa->size, 4096);
	ipath = init_ipath(size, root, path);
	अगर (IS_ERR(ipath)) अणु
		ret = PTR_ERR(ipath);
		ipath = शून्य;
		जाओ out;
	पूर्ण

	ret = paths_from_inode(ipa->inum, ipath);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < ipath->fspath->elem_cnt; ++i) अणु
		rel_ptr = ipath->fspath->val[i] -
			  (u64)(अचिन्हित दीर्घ)ipath->fspath->val;
		ipath->fspath->val[i] = rel_ptr;
	पूर्ण

	ret = copy_to_user((व्योम __user *)(अचिन्हित दीर्घ)ipa->fspath,
			   ipath->fspath, size);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	मुक्त_ipath(ipath);
	kमुक्त(ipa);

	वापस ret;
पूर्ण

अटल पूर्णांक build_ino_list(u64 inum, u64 offset, u64 root, व्योम *ctx)
अणु
	काष्ठा btrfs_data_container *inodes = ctx;
	स्थिर माप_प्रकार c = 3 * माप(u64);

	अगर (inodes->bytes_left >= c) अणु
		inodes->bytes_left -= c;
		inodes->val[inodes->elem_cnt] = inum;
		inodes->val[inodes->elem_cnt + 1] = offset;
		inodes->val[inodes->elem_cnt + 2] = root;
		inodes->elem_cnt += 3;
	पूर्ण अन्यथा अणु
		inodes->bytes_missing += c - inodes->bytes_left;
		inodes->bytes_left = 0;
		inodes->elem_missed += 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ btrfs_ioctl_logical_to_ino(काष्ठा btrfs_fs_info *fs_info,
					व्योम __user *arg, पूर्णांक version)
अणु
	पूर्णांक ret = 0;
	पूर्णांक size;
	काष्ठा btrfs_ioctl_logical_ino_args *loi;
	काष्ठा btrfs_data_container *inodes = शून्य;
	काष्ठा btrfs_path *path = शून्य;
	bool ignore_offset;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	loi = memdup_user(arg, माप(*loi));
	अगर (IS_ERR(loi))
		वापस PTR_ERR(loi);

	अगर (version == 1) अणु
		ignore_offset = false;
		size = min_t(u32, loi->size, SZ_64K);
	पूर्ण अन्यथा अणु
		/* All reserved bits must be 0 क्रम now */
		अगर (स_प्रथम_inv(loi->reserved, 0, माप(loi->reserved))) अणु
			ret = -EINVAL;
			जाओ out_loi;
		पूर्ण
		/* Only accept flags we have defined so far */
		अगर (loi->flags & ~(BTRFS_LOGICAL_INO_ARGS_IGNORE_OFFSET)) अणु
			ret = -EINVAL;
			जाओ out_loi;
		पूर्ण
		ignore_offset = loi->flags & BTRFS_LOGICAL_INO_ARGS_IGNORE_OFFSET;
		size = min_t(u32, loi->size, SZ_16M);
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	inodes = init_data_container(size);
	अगर (IS_ERR(inodes)) अणु
		ret = PTR_ERR(inodes);
		inodes = शून्य;
		जाओ out;
	पूर्ण

	ret = iterate_inodes_from_logical(loi->logical, fs_info, path,
					  build_ino_list, inodes, ignore_offset);
	अगर (ret == -EINVAL)
		ret = -ENOENT;
	अगर (ret < 0)
		जाओ out;

	ret = copy_to_user((व्योम __user *)(अचिन्हित दीर्घ)loi->inodes, inodes,
			   size);
	अगर (ret)
		ret = -EFAULT;

out:
	btrfs_मुक्त_path(path);
	kvमुक्त(inodes);
out_loi:
	kमुक्त(loi);

	वापस ret;
पूर्ण

व्योम btrfs_update_ioctl_balance_args(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा btrfs_ioctl_balance_args *bargs)
अणु
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;

	bargs->flags = bctl->flags;

	अगर (test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags))
		bargs->state |= BTRFS_BALANCE_STATE_RUNNING;
	अगर (atomic_पढ़ो(&fs_info->balance_छोड़ो_req))
		bargs->state |= BTRFS_BALANCE_STATE_PAUSE_REQ;
	अगर (atomic_पढ़ो(&fs_info->balance_cancel_req))
		bargs->state |= BTRFS_BALANCE_STATE_CANCEL_REQ;

	स_नकल(&bargs->data, &bctl->data, माप(bargs->data));
	स_नकल(&bargs->meta, &bctl->meta, माप(bargs->meta));
	स_नकल(&bargs->sys, &bctl->sys, माप(bargs->sys));

	spin_lock(&fs_info->balance_lock);
	स_नकल(&bargs->stat, &bctl->stat, माप(bargs->stat));
	spin_unlock(&fs_info->balance_lock);
पूर्ण

अटल दीर्घ btrfs_ioctl_balance(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(file_inode(file))->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_ioctl_balance_args *bargs;
	काष्ठा btrfs_balance_control *bctl;
	bool need_unlock; /* क्रम mut. excl. ops lock */
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

again:
	अगर (btrfs_exclop_start(fs_info, BTRFS_EXCLOP_BALANCE)) अणु
		mutex_lock(&fs_info->balance_mutex);
		need_unlock = true;
		जाओ locked;
	पूर्ण

	/*
	 * mut. excl. ops lock is locked.  Three possibilities:
	 *   (1) some other op is running
	 *   (2) balance is running
	 *   (3) balance is छोड़ोd -- special हाल (think resume)
	 */
	mutex_lock(&fs_info->balance_mutex);
	अगर (fs_info->balance_ctl) अणु
		/* this is either (2) or (3) */
		अगर (!test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) अणु
			mutex_unlock(&fs_info->balance_mutex);
			/*
			 * Lock released to allow other रुकोers to जारी,
			 * we'll reexamine the status again.
			 */
			mutex_lock(&fs_info->balance_mutex);

			अगर (fs_info->balance_ctl &&
			    !test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) अणु
				/* this is (3) */
				need_unlock = false;
				जाओ locked;
			पूर्ण

			mutex_unlock(&fs_info->balance_mutex);
			जाओ again;
		पूर्ण अन्यथा अणु
			/* this is (2) */
			mutex_unlock(&fs_info->balance_mutex);
			ret = -EINPROGRESS;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this is (1) */
		mutex_unlock(&fs_info->balance_mutex);
		ret = BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
		जाओ out;
	पूर्ण

locked:

	अगर (arg) अणु
		bargs = memdup_user(arg, माप(*bargs));
		अगर (IS_ERR(bargs)) अणु
			ret = PTR_ERR(bargs);
			जाओ out_unlock;
		पूर्ण

		अगर (bargs->flags & BTRFS_BALANCE_RESUME) अणु
			अगर (!fs_info->balance_ctl) अणु
				ret = -ENOTCONN;
				जाओ out_bargs;
			पूर्ण

			bctl = fs_info->balance_ctl;
			spin_lock(&fs_info->balance_lock);
			bctl->flags |= BTRFS_BALANCE_RESUME;
			spin_unlock(&fs_info->balance_lock);

			जाओ करो_balance;
		पूर्ण
	पूर्ण अन्यथा अणु
		bargs = शून्य;
	पूर्ण

	अगर (fs_info->balance_ctl) अणु
		ret = -EINPROGRESS;
		जाओ out_bargs;
	पूर्ण

	bctl = kzalloc(माप(*bctl), GFP_KERNEL);
	अगर (!bctl) अणु
		ret = -ENOMEM;
		जाओ out_bargs;
	पूर्ण

	अगर (arg) अणु
		स_नकल(&bctl->data, &bargs->data, माप(bctl->data));
		स_नकल(&bctl->meta, &bargs->meta, माप(bctl->meta));
		स_नकल(&bctl->sys, &bargs->sys, माप(bctl->sys));

		bctl->flags = bargs->flags;
	पूर्ण अन्यथा अणु
		/* balance everything - no filters */
		bctl->flags |= BTRFS_BALANCE_TYPE_MASK;
	पूर्ण

	अगर (bctl->flags & ~(BTRFS_BALANCE_ARGS_MASK | BTRFS_BALANCE_TYPE_MASK)) अणु
		ret = -EINVAL;
		जाओ out_bctl;
	पूर्ण

करो_balance:
	/*
	 * Ownership of bctl and exclusive operation goes to btrfs_balance.
	 * bctl is मुक्तd in reset_balance_state, or, अगर restriper was छोड़ोd
	 * all the way until unmount, in मुक्त_fs_info.  The flag should be
	 * cleared after reset_balance_state.
	 */
	need_unlock = false;

	ret = btrfs_balance(fs_info, bctl, bargs);
	bctl = शून्य;

	अगर ((ret == 0 || ret == -ECANCELED) && arg) अणु
		अगर (copy_to_user(arg, bargs, माप(*bargs)))
			ret = -EFAULT;
	पूर्ण

out_bctl:
	kमुक्त(bctl);
out_bargs:
	kमुक्त(bargs);
out_unlock:
	mutex_unlock(&fs_info->balance_mutex);
	अगर (need_unlock)
		btrfs_exclop_finish(fs_info);
out:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_balance_ctl(काष्ठा btrfs_fs_info *fs_info, पूर्णांक cmd)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल BTRFS_BALANCE_CTL_PAUSE:
		वापस btrfs_छोड़ो_balance(fs_info);
	हाल BTRFS_BALANCE_CTL_CANCEL:
		वापस btrfs_cancel_balance(fs_info);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ btrfs_ioctl_balance_progress(काष्ठा btrfs_fs_info *fs_info,
					 व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_balance_args *bargs;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	mutex_lock(&fs_info->balance_mutex);
	अगर (!fs_info->balance_ctl) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	bargs = kzalloc(माप(*bargs), GFP_KERNEL);
	अगर (!bargs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	btrfs_update_ioctl_balance_args(fs_info, bargs);

	अगर (copy_to_user(arg, bargs, माप(*bargs)))
		ret = -EFAULT;

	kमुक्त(bargs);
out:
	mutex_unlock(&fs_info->balance_mutex);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_quota_ctl(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_ioctl_quota_ctl_args *sa;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa)) अणु
		ret = PTR_ERR(sa);
		जाओ drop_ग_लिखो;
	पूर्ण

	करोwn_ग_लिखो(&fs_info->subvol_sem);

	चयन (sa->cmd) अणु
	हाल BTRFS_QUOTA_CTL_ENABLE:
		ret = btrfs_quota_enable(fs_info);
		अवरोध;
	हाल BTRFS_QUOTA_CTL_DISABLE:
		ret = btrfs_quota_disable(fs_info);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	kमुक्त(sa);
	up_ग_लिखो(&fs_info->subvol_sem);
drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_qgroup_assign(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_ioctl_qgroup_assign_args *sa;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa)) अणु
		ret = PTR_ERR(sa);
		जाओ drop_ग_लिखो;
	पूर्ण

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	अगर (sa->assign) अणु
		ret = btrfs_add_qgroup_relation(trans, sa->src, sa->dst);
	पूर्ण अन्यथा अणु
		ret = btrfs_del_qgroup_relation(trans, sa->src, sa->dst);
	पूर्ण

	/* update qgroup status and info */
	err = btrfs_run_qgroups(trans);
	अगर (err < 0)
		btrfs_handle_fs_error(fs_info, err,
				      "failed to update qgroup status and info");
	err = btrfs_end_transaction(trans);
	अगर (err && !ret)
		ret = err;

out:
	kमुक्त(sa);
drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_qgroup_create(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_ioctl_qgroup_create_args *sa;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa)) अणु
		ret = PTR_ERR(sa);
		जाओ drop_ग_लिखो;
	पूर्ण

	अगर (!sa->qgroupid) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	अगर (sa->create) अणु
		ret = btrfs_create_qgroup(trans, sa->qgroupid);
	पूर्ण अन्यथा अणु
		ret = btrfs_हटाओ_qgroup(trans, sa->qgroupid);
	पूर्ण

	err = btrfs_end_transaction(trans);
	अगर (err && !ret)
		ret = err;

out:
	kमुक्त(sa);
drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_qgroup_limit(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_ioctl_qgroup_limit_args *sa;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;
	पूर्णांक err;
	u64 qgroupid;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa)) अणु
		ret = PTR_ERR(sa);
		जाओ drop_ग_लिखो;
	पूर्ण

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	qgroupid = sa->qgroupid;
	अगर (!qgroupid) अणु
		/* take the current subvol as qgroup */
		qgroupid = root->root_key.objectid;
	पूर्ण

	ret = btrfs_limit_qgroup(trans, qgroupid, &sa->lim);

	err = btrfs_end_transaction(trans);
	अगर (err && !ret)
		ret = err;

out:
	kमुक्त(sa);
drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_quota_rescan(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_ioctl_quota_rescan_args *qsa;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	qsa = memdup_user(arg, माप(*qsa));
	अगर (IS_ERR(qsa)) अणु
		ret = PTR_ERR(qsa);
		जाओ drop_ग_लिखो;
	पूर्ण

	अगर (qsa->flags) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = btrfs_qgroup_rescan(fs_info);

out:
	kमुक्त(qsa);
drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_quota_rescan_status(काष्ठा btrfs_fs_info *fs_info,
						व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_quota_rescan_args *qsa;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	qsa = kzalloc(माप(*qsa), GFP_KERNEL);
	अगर (!qsa)
		वापस -ENOMEM;

	अगर (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN) अणु
		qsa->flags = 1;
		qsa->progress = fs_info->qgroup_rescan_progress.objectid;
	पूर्ण

	अगर (copy_to_user(arg, qsa, माप(*qsa)))
		ret = -EFAULT;

	kमुक्त(qsa);
	वापस ret;
पूर्ण

अटल दीर्घ btrfs_ioctl_quota_rescan_रुको(काष्ठा btrfs_fs_info *fs_info,
						व्योम __user *arg)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस btrfs_qgroup_रुको_क्रम_completion(fs_info, true);
पूर्ण

अटल दीर्घ _btrfs_ioctl_set_received_subvol(काष्ठा file *file,
					    काष्ठा btrfs_ioctl_received_subvol_args *sa)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_root_item *root_item = &root->root_item;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा बारpec64 ct = current_समय(inode);
	पूर्णांक ret = 0;
	पूर्णांक received_uuid_changed;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret < 0)
		वापस ret;

	करोwn_ग_लिखो(&fs_info->subvol_sem);

	अगर (btrfs_ino(BTRFS_I(inode)) != BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (btrfs_root_पढ़ोonly(root)) अणु
		ret = -EROFS;
		जाओ out;
	पूर्ण

	/*
	 * 1 - root item
	 * 2 - uuid items (received uuid + subvol uuid)
	 */
	trans = btrfs_start_transaction(root, 3);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out;
	पूर्ण

	sa->rtransid = trans->transid;
	sa->rसमय.sec = ct.tv_sec;
	sa->rसमय.nsec = ct.tv_nsec;

	received_uuid_changed = स_भेद(root_item->received_uuid, sa->uuid,
				       BTRFS_UUID_SIZE);
	अगर (received_uuid_changed &&
	    !btrfs_is_empty_uuid(root_item->received_uuid)) अणु
		ret = btrfs_uuid_tree_हटाओ(trans, root_item->received_uuid,
					  BTRFS_UUID_KEY_RECEIVED_SUBVOL,
					  root->root_key.objectid);
		अगर (ret && ret != -ENOENT) अणु
		        btrfs_पात_transaction(trans, ret);
		        btrfs_end_transaction(trans);
		        जाओ out;
		पूर्ण
	पूर्ण
	स_नकल(root_item->received_uuid, sa->uuid, BTRFS_UUID_SIZE);
	btrfs_set_root_stransid(root_item, sa->stransid);
	btrfs_set_root_rtransid(root_item, sa->rtransid);
	btrfs_set_stack_बारpec_sec(&root_item->sसमय, sa->sसमय.sec);
	btrfs_set_stack_बारpec_nsec(&root_item->sसमय, sa->sसमय.nsec);
	btrfs_set_stack_बारpec_sec(&root_item->rसमय, sa->rसमय.sec);
	btrfs_set_stack_बारpec_nsec(&root_item->rसमय, sa->rसमय.nsec);

	ret = btrfs_update_root(trans, fs_info->tree_root,
				&root->root_key, &root->root_item);
	अगर (ret < 0) अणु
		btrfs_end_transaction(trans);
		जाओ out;
	पूर्ण
	अगर (received_uuid_changed && !btrfs_is_empty_uuid(sa->uuid)) अणु
		ret = btrfs_uuid_tree_add(trans, sa->uuid,
					  BTRFS_UUID_KEY_RECEIVED_SUBVOL,
					  root->root_key.objectid);
		अगर (ret < 0 && ret != -EEXIST) अणु
			btrfs_पात_transaction(trans, ret);
			btrfs_end_transaction(trans);
			जाओ out;
		पूर्ण
	पूर्ण
	ret = btrfs_commit_transaction(trans);
out:
	up_ग_लिखो(&fs_info->subvol_sem);
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल दीर्घ btrfs_ioctl_set_received_subvol_32(काष्ठा file *file,
						व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_received_subvol_args_32 *args32 = शून्य;
	काष्ठा btrfs_ioctl_received_subvol_args *args64 = शून्य;
	पूर्णांक ret = 0;

	args32 = memdup_user(arg, माप(*args32));
	अगर (IS_ERR(args32))
		वापस PTR_ERR(args32);

	args64 = kदो_स्मृति(माप(*args64), GFP_KERNEL);
	अगर (!args64) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(args64->uuid, args32->uuid, BTRFS_UUID_SIZE);
	args64->stransid = args32->stransid;
	args64->rtransid = args32->rtransid;
	args64->sसमय.sec = args32->sसमय.sec;
	args64->sसमय.nsec = args32->sसमय.nsec;
	args64->rसमय.sec = args32->rसमय.sec;
	args64->rसमय.nsec = args32->rसमय.nsec;
	args64->flags = args32->flags;

	ret = _btrfs_ioctl_set_received_subvol(file, args64);
	अगर (ret)
		जाओ out;

	स_नकल(args32->uuid, args64->uuid, BTRFS_UUID_SIZE);
	args32->stransid = args64->stransid;
	args32->rtransid = args64->rtransid;
	args32->sसमय.sec = args64->sसमय.sec;
	args32->sसमय.nsec = args64->sसमय.nsec;
	args32->rसमय.sec = args64->rसमय.sec;
	args32->rसमय.nsec = args64->rसमय.nsec;
	args32->flags = args64->flags;

	ret = copy_to_user(arg, args32, माप(*args32));
	अगर (ret)
		ret = -EFAULT;

out:
	kमुक्त(args32);
	kमुक्त(args64);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ btrfs_ioctl_set_received_subvol(काष्ठा file *file,
					    व्योम __user *arg)
अणु
	काष्ठा btrfs_ioctl_received_subvol_args *sa = शून्य;
	पूर्णांक ret = 0;

	sa = memdup_user(arg, माप(*sa));
	अगर (IS_ERR(sa))
		वापस PTR_ERR(sa);

	ret = _btrfs_ioctl_set_received_subvol(file, sa);

	अगर (ret)
		जाओ out;

	ret = copy_to_user(arg, sa, माप(*sa));
	अगर (ret)
		ret = -EFAULT;

out:
	kमुक्त(sa);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_ioctl_get_fslabel(काष्ठा btrfs_fs_info *fs_info,
					व्योम __user *arg)
अणु
	माप_प्रकार len;
	पूर्णांक ret;
	अक्षर label[BTRFS_LABEL_SIZE];

	spin_lock(&fs_info->super_lock);
	स_नकल(label, fs_info->super_copy->label, BTRFS_LABEL_SIZE);
	spin_unlock(&fs_info->super_lock);

	len = strnlen(label, BTRFS_LABEL_SIZE);

	अगर (len == BTRFS_LABEL_SIZE) अणु
		btrfs_warn(fs_info,
			   "label is too long, return the first %zu bytes",
			   --len);
	पूर्ण

	ret = copy_to_user(arg, label, len);

	वापस ret ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक btrfs_ioctl_set_fslabel(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_super_block *super_block = fs_info->super_copy;
	काष्ठा btrfs_trans_handle *trans;
	अक्षर label[BTRFS_LABEL_SIZE];
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(label, arg, माप(label)))
		वापस -EFAULT;

	अगर (strnlen(label, BTRFS_LABEL_SIZE) == BTRFS_LABEL_SIZE) अणु
		btrfs_err(fs_info,
			  "unable to set label with more than %d bytes",
			  BTRFS_LABEL_SIZE - 1);
		वापस -EINVAL;
	पूर्ण

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_unlock;
	पूर्ण

	spin_lock(&fs_info->super_lock);
	म_नकल(super_block->label, label);
	spin_unlock(&fs_info->super_lock);
	ret = btrfs_commit_transaction(trans);

out_unlock:
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

#घोषणा INIT_FEATURE_FLAGS(suffix) \
	अणु .compat_flags = BTRFS_FEATURE_COMPAT_##suffix, \
	  .compat_ro_flags = BTRFS_FEATURE_COMPAT_RO_##suffix, \
	  .incompat_flags = BTRFS_FEATURE_INCOMPAT_##suffix पूर्ण

पूर्णांक btrfs_ioctl_get_supported_features(व्योम __user *arg)
अणु
	अटल स्थिर काष्ठा btrfs_ioctl_feature_flags features[3] = अणु
		INIT_FEATURE_FLAGS(SUPP),
		INIT_FEATURE_FLAGS(SAFE_SET),
		INIT_FEATURE_FLAGS(SAFE_CLEAR)
	पूर्ण;

	अगर (copy_to_user(arg, &features, माप(features)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_ioctl_get_features(काष्ठा btrfs_fs_info *fs_info,
					व्योम __user *arg)
अणु
	काष्ठा btrfs_super_block *super_block = fs_info->super_copy;
	काष्ठा btrfs_ioctl_feature_flags features;

	features.compat_flags = btrfs_super_compat_flags(super_block);
	features.compat_ro_flags = btrfs_super_compat_ro_flags(super_block);
	features.incompat_flags = btrfs_super_incompat_flags(super_block);

	अगर (copy_to_user(arg, &features, माप(features)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक check_feature_bits(काष्ठा btrfs_fs_info *fs_info,
			      क्रमागत btrfs_feature_set set,
			      u64 change_mask, u64 flags, u64 supported_flags,
			      u64 safe_set, u64 safe_clear)
अणु
	स्थिर अक्षर *type = btrfs_feature_set_name(set);
	अक्षर *names;
	u64 disallowed, unsupported;
	u64 set_mask = flags & change_mask;
	u64 clear_mask = ~flags & change_mask;

	unsupported = set_mask & ~supported_flags;
	अगर (unsupported) अणु
		names = btrfs_prपूर्णांकable_features(set, unsupported);
		अगर (names) अणु
			btrfs_warn(fs_info,
				   "this kernel does not support the %s feature bit%s",
				   names, म_अक्षर(names, ',') ? "s" : "");
			kमुक्त(names);
		पूर्ण अन्यथा
			btrfs_warn(fs_info,
				   "this kernel does not support %s bits 0x%llx",
				   type, unsupported);
		वापस -EOPNOTSUPP;
	पूर्ण

	disallowed = set_mask & ~safe_set;
	अगर (disallowed) अणु
		names = btrfs_prपूर्णांकable_features(set, disallowed);
		अगर (names) अणु
			btrfs_warn(fs_info,
				   "can't set the %s feature bit%s while mounted",
				   names, म_अक्षर(names, ',') ? "s" : "");
			kमुक्त(names);
		पूर्ण अन्यथा
			btrfs_warn(fs_info,
				   "can't set %s bits 0x%llx while mounted",
				   type, disallowed);
		वापस -EPERM;
	पूर्ण

	disallowed = clear_mask & ~safe_clear;
	अगर (disallowed) अणु
		names = btrfs_prपूर्णांकable_features(set, disallowed);
		अगर (names) अणु
			btrfs_warn(fs_info,
				   "can't clear the %s feature bit%s while mounted",
				   names, म_अक्षर(names, ',') ? "s" : "");
			kमुक्त(names);
		पूर्ण अन्यथा
			btrfs_warn(fs_info,
				   "can't clear %s bits 0x%llx while mounted",
				   type, disallowed);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा check_feature(fs_info, change_mask, flags, mask_base)	\
check_feature_bits(fs_info, FEAT_##mask_base, change_mask, flags,	\
		   BTRFS_FEATURE_ ## mask_base ## _SUPP,	\
		   BTRFS_FEATURE_ ## mask_base ## _SAFE_SET,	\
		   BTRFS_FEATURE_ ## mask_base ## _SAFE_CLEAR)

अटल पूर्णांक btrfs_ioctl_set_features(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_super_block *super_block = fs_info->super_copy;
	काष्ठा btrfs_ioctl_feature_flags flags[2];
	काष्ठा btrfs_trans_handle *trans;
	u64 newflags;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(flags, arg, माप(flags)))
		वापस -EFAULT;

	/* Nothing to करो */
	अगर (!flags[0].compat_flags && !flags[0].compat_ro_flags &&
	    !flags[0].incompat_flags)
		वापस 0;

	ret = check_feature(fs_info, flags[0].compat_flags,
			    flags[1].compat_flags, COMPAT);
	अगर (ret)
		वापस ret;

	ret = check_feature(fs_info, flags[0].compat_ro_flags,
			    flags[1].compat_ro_flags, COMPAT_RO);
	अगर (ret)
		वापस ret;

	ret = check_feature(fs_info, flags[0].incompat_flags,
			    flags[1].incompat_flags, INCOMPAT);
	अगर (ret)
		वापस ret;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_drop_ग_लिखो;
	पूर्ण

	spin_lock(&fs_info->super_lock);
	newflags = btrfs_super_compat_flags(super_block);
	newflags |= flags[0].compat_flags & flags[1].compat_flags;
	newflags &= ~(flags[0].compat_flags & ~flags[1].compat_flags);
	btrfs_set_super_compat_flags(super_block, newflags);

	newflags = btrfs_super_compat_ro_flags(super_block);
	newflags |= flags[0].compat_ro_flags & flags[1].compat_ro_flags;
	newflags &= ~(flags[0].compat_ro_flags & ~flags[1].compat_ro_flags);
	btrfs_set_super_compat_ro_flags(super_block, newflags);

	newflags = btrfs_super_incompat_flags(super_block);
	newflags |= flags[0].incompat_flags & flags[1].incompat_flags;
	newflags &= ~(flags[0].incompat_flags & ~flags[1].incompat_flags);
	btrfs_set_super_incompat_flags(super_block, newflags);
	spin_unlock(&fs_info->super_lock);

	ret = btrfs_commit_transaction(trans);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(file);

	वापस ret;
पूर्ण

अटल पूर्णांक _btrfs_ioctl_send(काष्ठा file *file, व्योम __user *argp, bool compat)
अणु
	काष्ठा btrfs_ioctl_send_args *arg;
	पूर्णांक ret;

	अगर (compat) अणु
#अगर defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
		काष्ठा btrfs_ioctl_send_args_32 args32;

		ret = copy_from_user(&args32, argp, माप(args32));
		अगर (ret)
			वापस -EFAULT;
		arg = kzalloc(माप(*arg), GFP_KERNEL);
		अगर (!arg)
			वापस -ENOMEM;
		arg->send_fd = args32.send_fd;
		arg->clone_sources_count = args32.clone_sources_count;
		arg->clone_sources = compat_ptr(args32.clone_sources);
		arg->parent_root = args32.parent_root;
		arg->flags = args32.flags;
		स_नकल(arg->reserved, args32.reserved,
		       माप(args32.reserved));
#अन्यथा
		वापस -ENOTTY;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		arg = memdup_user(argp, माप(*arg));
		अगर (IS_ERR(arg))
			वापस PTR_ERR(arg);
	पूर्ण
	ret = btrfs_ioctl_send(file, arg);
	kमुक्त(arg);
	वापस ret;
पूर्ण

दीर्घ btrfs_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक
		cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल FS_IOC_GETVERSION:
		वापस btrfs_ioctl_getversion(file, argp);
	हाल FS_IOC_GETFSLABEL:
		वापस btrfs_ioctl_get_fslabel(fs_info, argp);
	हाल FS_IOC_SETFSLABEL:
		वापस btrfs_ioctl_set_fslabel(file, argp);
	हाल FITRIM:
		वापस btrfs_ioctl_fitrim(fs_info, argp);
	हाल BTRFS_IOC_SNAP_CREATE:
		वापस btrfs_ioctl_snap_create(file, argp, 0);
	हाल BTRFS_IOC_SNAP_CREATE_V2:
		वापस btrfs_ioctl_snap_create_v2(file, argp, 0);
	हाल BTRFS_IOC_SUBVOL_CREATE:
		वापस btrfs_ioctl_snap_create(file, argp, 1);
	हाल BTRFS_IOC_SUBVOL_CREATE_V2:
		वापस btrfs_ioctl_snap_create_v2(file, argp, 1);
	हाल BTRFS_IOC_SNAP_DESTROY:
		वापस btrfs_ioctl_snap_destroy(file, argp, false);
	हाल BTRFS_IOC_SNAP_DESTROY_V2:
		वापस btrfs_ioctl_snap_destroy(file, argp, true);
	हाल BTRFS_IOC_SUBVOL_GETFLAGS:
		वापस btrfs_ioctl_subvol_getflags(file, argp);
	हाल BTRFS_IOC_SUBVOL_SETFLAGS:
		वापस btrfs_ioctl_subvol_setflags(file, argp);
	हाल BTRFS_IOC_DEFAULT_SUBVOL:
		वापस btrfs_ioctl_शेष_subvol(file, argp);
	हाल BTRFS_IOC_DEFRAG:
		वापस btrfs_ioctl_defrag(file, शून्य);
	हाल BTRFS_IOC_DEFRAG_RANGE:
		वापस btrfs_ioctl_defrag(file, argp);
	हाल BTRFS_IOC_RESIZE:
		वापस btrfs_ioctl_resize(file, argp);
	हाल BTRFS_IOC_ADD_DEV:
		वापस btrfs_ioctl_add_dev(fs_info, argp);
	हाल BTRFS_IOC_RM_DEV:
		वापस btrfs_ioctl_rm_dev(file, argp);
	हाल BTRFS_IOC_RM_DEV_V2:
		वापस btrfs_ioctl_rm_dev_v2(file, argp);
	हाल BTRFS_IOC_FS_INFO:
		वापस btrfs_ioctl_fs_info(fs_info, argp);
	हाल BTRFS_IOC_DEV_INFO:
		वापस btrfs_ioctl_dev_info(fs_info, argp);
	हाल BTRFS_IOC_BALANCE:
		वापस btrfs_ioctl_balance(file, शून्य);
	हाल BTRFS_IOC_TREE_SEARCH:
		वापस btrfs_ioctl_tree_search(file, argp);
	हाल BTRFS_IOC_TREE_SEARCH_V2:
		वापस btrfs_ioctl_tree_search_v2(file, argp);
	हाल BTRFS_IOC_INO_LOOKUP:
		वापस btrfs_ioctl_ino_lookup(file, argp);
	हाल BTRFS_IOC_INO_PATHS:
		वापस btrfs_ioctl_ino_to_path(root, argp);
	हाल BTRFS_IOC_LOGICAL_INO:
		वापस btrfs_ioctl_logical_to_ino(fs_info, argp, 1);
	हाल BTRFS_IOC_LOGICAL_INO_V2:
		वापस btrfs_ioctl_logical_to_ino(fs_info, argp, 2);
	हाल BTRFS_IOC_SPACE_INFO:
		वापस btrfs_ioctl_space_info(fs_info, argp);
	हाल BTRFS_IOC_SYNC: अणु
		पूर्णांक ret;

		ret = btrfs_start_delalloc_roots(fs_info, दीर्घ_उच्च, false);
		अगर (ret)
			वापस ret;
		ret = btrfs_sync_fs(inode->i_sb, 1);
		/*
		 * The transaction thपढ़ो may want to करो more work,
		 * namely it pokes the cleaner kthपढ़ो that will start
		 * processing uncleaned subvols.
		 */
		wake_up_process(fs_info->transaction_kthपढ़ो);
		वापस ret;
	पूर्ण
	हाल BTRFS_IOC_START_SYNC:
		वापस btrfs_ioctl_start_sync(root, argp);
	हाल BTRFS_IOC_WAIT_SYNC:
		वापस btrfs_ioctl_रुको_sync(fs_info, argp);
	हाल BTRFS_IOC_SCRUB:
		वापस btrfs_ioctl_scrub(file, argp);
	हाल BTRFS_IOC_SCRUB_CANCEL:
		वापस btrfs_ioctl_scrub_cancel(fs_info);
	हाल BTRFS_IOC_SCRUB_PROGRESS:
		वापस btrfs_ioctl_scrub_progress(fs_info, argp);
	हाल BTRFS_IOC_BALANCE_V2:
		वापस btrfs_ioctl_balance(file, argp);
	हाल BTRFS_IOC_BALANCE_CTL:
		वापस btrfs_ioctl_balance_ctl(fs_info, arg);
	हाल BTRFS_IOC_BALANCE_PROGRESS:
		वापस btrfs_ioctl_balance_progress(fs_info, argp);
	हाल BTRFS_IOC_SET_RECEIVED_SUBVOL:
		वापस btrfs_ioctl_set_received_subvol(file, argp);
#अगर_घोषित CONFIG_64BIT
	हाल BTRFS_IOC_SET_RECEIVED_SUBVOL_32:
		वापस btrfs_ioctl_set_received_subvol_32(file, argp);
#पूर्ण_अगर
	हाल BTRFS_IOC_SEND:
		वापस _btrfs_ioctl_send(file, argp, false);
#अगर defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
	हाल BTRFS_IOC_SEND_32:
		वापस _btrfs_ioctl_send(file, argp, true);
#पूर्ण_अगर
	हाल BTRFS_IOC_GET_DEV_STATS:
		वापस btrfs_ioctl_get_dev_stats(fs_info, argp);
	हाल BTRFS_IOC_QUOTA_CTL:
		वापस btrfs_ioctl_quota_ctl(file, argp);
	हाल BTRFS_IOC_QGROUP_ASSIGN:
		वापस btrfs_ioctl_qgroup_assign(file, argp);
	हाल BTRFS_IOC_QGROUP_CREATE:
		वापस btrfs_ioctl_qgroup_create(file, argp);
	हाल BTRFS_IOC_QGROUP_LIMIT:
		वापस btrfs_ioctl_qgroup_limit(file, argp);
	हाल BTRFS_IOC_QUOTA_RESCAN:
		वापस btrfs_ioctl_quota_rescan(file, argp);
	हाल BTRFS_IOC_QUOTA_RESCAN_STATUS:
		वापस btrfs_ioctl_quota_rescan_status(fs_info, argp);
	हाल BTRFS_IOC_QUOTA_RESCAN_WAIT:
		वापस btrfs_ioctl_quota_rescan_रुको(fs_info, argp);
	हाल BTRFS_IOC_DEV_REPLACE:
		वापस btrfs_ioctl_dev_replace(fs_info, argp);
	हाल BTRFS_IOC_GET_SUPPORTED_FEATURES:
		वापस btrfs_ioctl_get_supported_features(argp);
	हाल BTRFS_IOC_GET_FEATURES:
		वापस btrfs_ioctl_get_features(fs_info, argp);
	हाल BTRFS_IOC_SET_FEATURES:
		वापस btrfs_ioctl_set_features(file, argp);
	हाल BTRFS_IOC_GET_SUBVOL_INFO:
		वापस btrfs_ioctl_get_subvol_info(file, argp);
	हाल BTRFS_IOC_GET_SUBVOL_ROOTREF:
		वापस btrfs_ioctl_get_subvol_rootref(file, argp);
	हाल BTRFS_IOC_INO_LOOKUP_USER:
		वापस btrfs_ioctl_ino_lookup_user(file, argp);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ btrfs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	/*
	 * These all access 32-bit values anyway so no further
	 * handling is necessary.
	 */
	चयन (cmd) अणु
	हाल FS_IOC32_GETVERSION:
		cmd = FS_IOC_GETVERSION;
		अवरोध;
	पूर्ण

	वापस btrfs_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर
