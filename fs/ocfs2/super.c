<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * super.c
 *
 * load/unload driver, mount/dismount volumes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/statfs.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/parser.h>
#समावेश <linux/crc32.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/संकेत.स>

#घोषणा CREATE_TRACE_POINTS
#समावेश "ocfs2_trace.h"

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

/* this should be the only file to include a version 1 header */
#समावेश "ocfs1_fs_compat.h"

#समावेश "alloc.h"
#समावेश "aops.h"
#समावेश "blockcheck.h"
#समावेश "dlmglue.h"
#समावेश "export.h"
#समावेश "extent_map.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "localalloc.h"
#समावेश "namei.h"
#समावेश "slot_map.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "xattr.h"
#समावेश "quota.h"
#समावेश "refcounttree.h"
#समावेश "suballoc.h"

#समावेश "buffer_head_io.h"
#समावेश "filecheck.h"

अटल काष्ठा kmem_cache *ocfs2_inode_cachep;
काष्ठा kmem_cache *ocfs2_dquot_cachep;
काष्ठा kmem_cache *ocfs2_qf_chunk_cachep;

अटल काष्ठा dentry *ocfs2_debugfs_root;

MODULE_AUTHOR("Oracle");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OCFS2 cluster file system");

काष्ठा mount_options
अणु
	अचिन्हित दीर्घ	commit_पूर्णांकerval;
	अचिन्हित दीर्घ	mount_opt;
	अचिन्हित पूर्णांक	aसमय_quantum;
	अचिन्हित लघु	slot;
	पूर्णांक		localalloc_opt;
	अचिन्हित पूर्णांक	resv_level;
	पूर्णांक		dir_resv_level;
	अक्षर		cluster_stack[OCFS2_STACK_LABEL_LEN + 1];
पूर्ण;

अटल पूर्णांक ocfs2_parse_options(काष्ठा super_block *sb, अक्षर *options,
			       काष्ठा mount_options *mopt,
			       पूर्णांक is_remount);
अटल पूर्णांक ocfs2_check_set_options(काष्ठा super_block *sb,
				   काष्ठा mount_options *options);
अटल पूर्णांक ocfs2_show_options(काष्ठा seq_file *s, काष्ठा dentry *root);
अटल व्योम ocfs2_put_super(काष्ठा super_block *sb);
अटल पूर्णांक ocfs2_mount_volume(काष्ठा super_block *sb);
अटल पूर्णांक ocfs2_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);
अटल व्योम ocfs2_dismount_volume(काष्ठा super_block *sb, पूर्णांक mnt_err);
अटल पूर्णांक ocfs2_initialize_mem_caches(व्योम);
अटल व्योम ocfs2_मुक्त_mem_caches(व्योम);
अटल व्योम ocfs2_delete_osb(काष्ठा ocfs2_super *osb);

अटल पूर्णांक ocfs2_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);

अटल पूर्णांक ocfs2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको);

अटल पूर्णांक ocfs2_init_global_प्रणाली_inodes(काष्ठा ocfs2_super *osb);
अटल पूर्णांक ocfs2_init_local_प्रणाली_inodes(काष्ठा ocfs2_super *osb);
अटल व्योम ocfs2_release_प्रणाली_inodes(काष्ठा ocfs2_super *osb);
अटल पूर्णांक ocfs2_check_volume(काष्ठा ocfs2_super *osb);
अटल पूर्णांक ocfs2_verअगरy_volume(काष्ठा ocfs2_dinode *di,
			       काष्ठा buffer_head *bh,
			       u32 sectsize,
			       काष्ठा ocfs2_blockcheck_stats *stats);
अटल पूर्णांक ocfs2_initialize_super(काष्ठा super_block *sb,
				  काष्ठा buffer_head *bh,
				  पूर्णांक sector_size,
				  काष्ठा ocfs2_blockcheck_stats *stats);
अटल पूर्णांक ocfs2_get_sector(काष्ठा super_block *sb,
			    काष्ठा buffer_head **bh,
			    पूर्णांक block,
			    पूर्णांक sect_size);
अटल काष्ठा inode *ocfs2_alloc_inode(काष्ठा super_block *sb);
अटल व्योम ocfs2_मुक्त_inode(काष्ठा inode *inode);
अटल पूर्णांक ocfs2_susp_quotas(काष्ठा ocfs2_super *osb, पूर्णांक unsuspend);
अटल पूर्णांक ocfs2_enable_quotas(काष्ठा ocfs2_super *osb);
अटल व्योम ocfs2_disable_quotas(काष्ठा ocfs2_super *osb);

अटल काष्ठा dquot **ocfs2_get_dquots(काष्ठा inode *inode)
अणु
	वापस OCFS2_I(inode)->i_dquot;
पूर्ण

अटल स्थिर काष्ठा super_operations ocfs2_sops = अणु
	.statfs		= ocfs2_statfs,
	.alloc_inode	= ocfs2_alloc_inode,
	.मुक्त_inode	= ocfs2_मुक्त_inode,
	.drop_inode	= ocfs2_drop_inode,
	.evict_inode	= ocfs2_evict_inode,
	.sync_fs	= ocfs2_sync_fs,
	.put_super	= ocfs2_put_super,
	.remount_fs	= ocfs2_remount,
	.show_options   = ocfs2_show_options,
	.quota_पढ़ो	= ocfs2_quota_पढ़ो,
	.quota_ग_लिखो	= ocfs2_quota_ग_लिखो,
	.get_dquots	= ocfs2_get_dquots,
पूर्ण;

क्रमागत अणु
	Opt_barrier,
	Opt_err_panic,
	Opt_err_ro,
	Opt_पूर्णांकr,
	Opt_noपूर्णांकr,
	Opt_hb_none,
	Opt_hb_local,
	Opt_hb_global,
	Opt_data_ordered,
	Opt_data_ग_लिखोback,
	Opt_aसमय_quantum,
	Opt_slot,
	Opt_commit,
	Opt_localalloc,
	Opt_localflocks,
	Opt_stack,
	Opt_user_xattr,
	Opt_nouser_xattr,
	Opt_inode64,
	Opt_acl,
	Opt_noacl,
	Opt_usrquota,
	Opt_grpquota,
	Opt_coherency_buffered,
	Opt_coherency_full,
	Opt_resv_level,
	Opt_dir_resv_level,
	Opt_journal_async_commit,
	Opt_err_cont,
	Opt_nocluster,
	Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_barrier, "barrier=%u"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_पूर्णांकr, "intr"पूर्ण,
	अणुOpt_noपूर्णांकr, "nointr"पूर्ण,
	अणुOpt_hb_none, OCFS2_HB_NONEपूर्ण,
	अणुOpt_hb_local, OCFS2_HB_LOCALपूर्ण,
	अणुOpt_hb_global, OCFS2_HB_GLOBALपूर्ण,
	अणुOpt_data_ordered, "data=ordered"पूर्ण,
	अणुOpt_data_ग_लिखोback, "data=writeback"पूर्ण,
	अणुOpt_aसमय_quantum, "atime_quantum=%u"पूर्ण,
	अणुOpt_slot, "preferred_slot=%u"पूर्ण,
	अणुOpt_commit, "commit=%u"पूर्ण,
	अणुOpt_localalloc, "localalloc=%d"पूर्ण,
	अणुOpt_localflocks, "localflocks"पूर्ण,
	अणुOpt_stack, "cluster_stack=%s"पूर्ण,
	अणुOpt_user_xattr, "user_xattr"पूर्ण,
	अणुOpt_nouser_xattr, "nouser_xattr"पूर्ण,
	अणुOpt_inode64, "inode64"पूर्ण,
	अणुOpt_acl, "acl"पूर्ण,
	अणुOpt_noacl, "noacl"पूर्ण,
	अणुOpt_usrquota, "usrquota"पूर्ण,
	अणुOpt_grpquota, "grpquota"पूर्ण,
	अणुOpt_coherency_buffered, "coherency=buffered"पूर्ण,
	अणुOpt_coherency_full, "coherency=full"पूर्ण,
	अणुOpt_resv_level, "resv_level=%u"पूर्ण,
	अणुOpt_dir_resv_level, "dir_resv_level=%u"पूर्ण,
	अणुOpt_journal_async_commit, "journal_async_commit"पूर्ण,
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_nocluster, "nocluster"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक ocfs2_osb_dump(काष्ठा ocfs2_super *osb, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा ocfs2_cluster_connection *cconn = osb->cconn;
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;
	काष्ठा ocfs2_orphan_scan *os = &osb->osb_orphan_scan;
	पूर्णांक i, out = 0;
	अचिन्हित दीर्घ flags;

	out += scnम_लिखो(buf + out, len - out,
			"%10s => Id: %-s  Uuid: %-s  Gen: 0x%X  Label: %-s\n",
			"Device", osb->dev_str, osb->uuid_str,
			osb->fs_generation, osb->vol_label);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => State: %d  Flags: 0x%lX\n", "Volume",
			atomic_पढ़ो(&osb->vol_state), osb->osb_flags);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => Block: %lu  Cluster: %d\n", "Sizes",
			osb->sb->s_blocksize, osb->s_clustersize);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => Compat: 0x%X  Incompat: 0x%X  "
			"ROcompat: 0x%X\n",
			"Features", osb->s_feature_compat,
			osb->s_feature_incompat, osb->s_feature_ro_compat);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => Opts: 0x%lX  AtimeQuanta: %u\n", "Mount",
			osb->s_mount_opt, osb->s_aसमय_quantum);

	अगर (cconn) अणु
		out += scnम_लिखो(buf + out, len - out,
				"%10s => Stack: %s  Name: %*s  "
				"Version: %d.%d\n", "Cluster",
				(*osb->osb_cluster_stack == '\0' ?
				 "o2cb" : osb->osb_cluster_stack),
				cconn->cc_namelen, cconn->cc_name,
				cconn->cc_version.pv_major,
				cconn->cc_version.pv_minor);
	पूर्ण

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	out += scnम_लिखो(buf + out, len - out,
			"%10s => Pid: %d  Count: %lu  WakeSeq: %lu  "
			"WorkSeq: %lu\n", "DownCnvt",
			(osb->dc_task ?  task_pid_nr(osb->dc_task) : -1),
			osb->blocked_lock_count, osb->dc_wake_sequence,
			osb->dc_work_sequence);
	spin_unlock_irqrestore(&osb->dc_task_lock, flags);

	spin_lock(&osb->osb_lock);
	out += scnम_लिखो(buf + out, len - out, "%10s => Pid: %d  Nodes:",
			"Recovery",
			(osb->recovery_thपढ़ो_task ?
			 task_pid_nr(osb->recovery_thपढ़ो_task) : -1));
	अगर (rm->rm_used == 0)
		out += scnम_लिखो(buf + out, len - out, " None\n");
	अन्यथा अणु
		क्रम (i = 0; i < rm->rm_used; i++)
			out += scnम_लिखो(buf + out, len - out, " %d",
					rm->rm_entries[i]);
		out += scnम_लिखो(buf + out, len - out, "\n");
	पूर्ण
	spin_unlock(&osb->osb_lock);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => Pid: %d  Interval: %lu\n", "Commit",
			(osb->commit_task ? task_pid_nr(osb->commit_task) : -1),
			osb->osb_commit_पूर्णांकerval);

	out += scnम_लिखो(buf + out, len - out,
			"%10s => State: %d  TxnId: %lu  NumTxns: %d\n",
			"Journal", osb->journal->j_state,
			osb->journal->j_trans_id,
			atomic_पढ़ो(&osb->journal->j_num_trans));

	out += scnम_लिखो(buf + out, len - out,
			"%10s => GlobalAllocs: %d  LocalAllocs: %d  "
			"SubAllocs: %d  LAWinMoves: %d  SAExtends: %d\n",
			"Stats",
			atomic_पढ़ो(&osb->alloc_stats.biपंचांगap_data),
			atomic_पढ़ो(&osb->alloc_stats.local_data),
			atomic_पढ़ो(&osb->alloc_stats.bg_allocs),
			atomic_पढ़ो(&osb->alloc_stats.moves),
			atomic_पढ़ो(&osb->alloc_stats.bg_extends));

	out += scnम_लिखो(buf + out, len - out,
			"%10s => State: %u  Descriptor: %llu  Size: %u bits  "
			"Default: %u bits\n",
			"LocalAlloc", osb->local_alloc_state,
			(अचिन्हित दीर्घ दीर्घ)osb->la_last_gd,
			osb->local_alloc_bits, osb->local_alloc_शेष_bits);

	spin_lock(&osb->osb_lock);
	out += scnम_लिखो(buf + out, len - out,
			"%10s => InodeSlot: %d  StolenInodes: %d, "
			"MetaSlot: %d  StolenMeta: %d\n", "Steal",
			osb->s_inode_steal_slot,
			atomic_पढ़ो(&osb->s_num_inodes_stolen),
			osb->s_meta_steal_slot,
			atomic_पढ़ो(&osb->s_num_meta_stolen));
	spin_unlock(&osb->osb_lock);

	out += scnम_लिखो(buf + out, len - out, "OrphanScan => ");
	out += scnम_लिखो(buf + out, len - out, "Local: %u  Global: %u ",
			os->os_count, os->os_seqno);
	out += scnम_लिखो(buf + out, len - out, " Last Scan: ");
	अगर (atomic_पढ़ो(&os->os_state) == ORPHAN_SCAN_INACTIVE)
		out += scnम_लिखो(buf + out, len - out, "Disabled\n");
	अन्यथा
		out += scnम_लिखो(buf + out, len - out, "%lu seconds ago\n",
				(अचिन्हित दीर्घ)(kसमय_get_seconds() - os->os_scanसमय));

	out += scnम_लिखो(buf + out, len - out, "%10s => %3s  %10s\n",
			"Slots", "Num", "RecoGen");
	क्रम (i = 0; i < osb->max_slots; ++i) अणु
		out += scnम_लिखो(buf + out, len - out,
				"%10s  %c %3d  %10d\n",
				" ",
				(i == osb->slot_num ? '*' : ' '),
				i, osb->slot_recovery_generations[i]);
	पूर्ण

	वापस out;
पूर्ण

अटल पूर्णांक ocfs2_osb_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_super *osb = inode->i_निजी;
	अक्षर *buf = शून्य;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		जाओ bail;

	i_size_ग_लिखो(inode, ocfs2_osb_dump(osb, buf, PAGE_SIZE));

	file->निजी_data = buf;

	वापस 0;
bail:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ocfs2_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ocfs2_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, file->निजी_data,
				       i_size_पढ़ो(file->f_mapping->host));
पूर्ण
#अन्यथा
अटल पूर्णांक ocfs2_osb_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण
अटल पूर्णांक ocfs2_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण
अटल sमाप_प्रकार ocfs2_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_DEBUG_FS */

अटल स्थिर काष्ठा file_operations ocfs2_osb_debug_fops = अणु
	.खोलो =		ocfs2_osb_debug_खोलो,
	.release =	ocfs2_debug_release,
	.पढ़ो =		ocfs2_debug_पढ़ो,
	.llseek =	generic_file_llseek,
पूर्ण;

अटल पूर्णांक ocfs2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	पूर्णांक status;
	tid_t target;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (रुको) अणु
		status = ocfs2_flush_truncate_log(osb);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण अन्यथा अणु
		ocfs2_schedule_truncate_log_flush(osb, 0);
	पूर्ण

	अगर (jbd2_journal_start_commit(osb->journal->j_journal,
				      &target)) अणु
		अगर (रुको)
			jbd2_log_रुको_commit(osb->journal->j_journal,
					     target);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_need_प्रणाली_inode(काष्ठा ocfs2_super *osb, पूर्णांक ino)
अणु
	अगर (!OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb, OCFS2_FEATURE_RO_COMPAT_USRQUOTA)
	    && (ino == USER_QUOTA_SYSTEM_INODE
		|| ino == LOCAL_USER_QUOTA_SYSTEM_INODE))
		वापस 0;
	अगर (!OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb, OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)
	    && (ino == GROUP_QUOTA_SYSTEM_INODE
		|| ino == LOCAL_GROUP_QUOTA_SYSTEM_INODE))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ocfs2_init_global_प्रणाली_inodes(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा inode *new = शून्य;
	पूर्णांक status = 0;
	पूर्णांक i;

	new = ocfs2_iget(osb, osb->root_blkno, OCFS2_FI_FLAG_SYSखाता, 0);
	अगर (IS_ERR(new)) अणु
		status = PTR_ERR(new);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	osb->root_inode = new;

	new = ocfs2_iget(osb, osb->प्रणाली_dir_blkno, OCFS2_FI_FLAG_SYSखाता, 0);
	अगर (IS_ERR(new)) अणु
		status = PTR_ERR(new);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	osb->sys_root_inode = new;

	क्रम (i = OCFS2_FIRST_ONLINE_SYSTEM_INODE;
	     i <= OCFS2_LAST_GLOBAL_SYSTEM_INODE; i++) अणु
		अगर (!ocfs2_need_प्रणाली_inode(osb, i))
			जारी;
		new = ocfs2_get_प्रणाली_file_inode(osb, i, osb->slot_num);
		अगर (!new) अणु
			ocfs2_release_प्रणाली_inodes(osb);
			status = ocfs2_is_soft_पढ़ोonly(osb) ? -EROFS : -EINVAL;
			mlog_त्रुटि_सं(status);
			mlog(ML_ERROR, "Unable to load system inode %d, "
			     "possibly corrupt fs?", i);
			जाओ bail;
		पूर्ण
		// the array now has one ref, so drop this one
		iput(new);
	पूर्ण

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_init_local_प्रणाली_inodes(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा inode *new = शून्य;
	पूर्णांक status = 0;
	पूर्णांक i;

	क्रम (i = OCFS2_LAST_GLOBAL_SYSTEM_INODE + 1;
	     i < NUM_SYSTEM_INODES;
	     i++) अणु
		अगर (!ocfs2_need_प्रणाली_inode(osb, i))
			जारी;
		new = ocfs2_get_प्रणाली_file_inode(osb, i, osb->slot_num);
		अगर (!new) अणु
			ocfs2_release_प्रणाली_inodes(osb);
			status = ocfs2_is_soft_पढ़ोonly(osb) ? -EROFS : -EINVAL;
			mlog(ML_ERROR, "status=%d, sysfile=%d, slot=%d\n",
			     status, i, osb->slot_num);
			जाओ bail;
		पूर्ण
		/* the array now has one ref, so drop this one */
		iput(new);
	पूर्ण

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम ocfs2_release_प्रणाली_inodes(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक i;
	काष्ठा inode *inode;

	क्रम (i = 0; i < NUM_GLOBAL_SYSTEM_INODES; i++) अणु
		inode = osb->global_प्रणाली_inodes[i];
		अगर (inode) अणु
			iput(inode);
			osb->global_प्रणाली_inodes[i] = शून्य;
		पूर्ण
	पूर्ण

	inode = osb->sys_root_inode;
	अगर (inode) अणु
		iput(inode);
		osb->sys_root_inode = शून्य;
	पूर्ण

	inode = osb->root_inode;
	अगर (inode) अणु
		iput(inode);
		osb->root_inode = शून्य;
	पूर्ण

	अगर (!osb->local_प्रणाली_inodes)
		वापस;

	क्रम (i = 0; i < NUM_LOCAL_SYSTEM_INODES * osb->max_slots; i++) अणु
		अगर (osb->local_प्रणाली_inodes[i]) अणु
			iput(osb->local_प्रणाली_inodes[i]);
			osb->local_प्रणाली_inodes[i] = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(osb->local_प्रणाली_inodes);
	osb->local_प्रणाली_inodes = शून्य;
पूर्ण

/* We're allocating fs objects, use GFP_NOFS */
अटल काष्ठा inode *ocfs2_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ocfs2_inode_info *oi;

	oi = kmem_cache_alloc(ocfs2_inode_cachep, GFP_NOFS);
	अगर (!oi)
		वापस शून्य;

	oi->i_sync_tid = 0;
	oi->i_datasync_tid = 0;
	स_रखो(&oi->i_dquot, 0, माप(oi->i_dquot));

	jbd2_journal_init_jbd_inode(&oi->ip_jinode, &oi->vfs_inode);
	वापस &oi->vfs_inode;
पूर्ण

अटल व्योम ocfs2_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(ocfs2_inode_cachep, OCFS2_I(inode));
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ ocfs2_max_file_offset(अचिन्हित पूर्णांक bbits,
						अचिन्हित पूर्णांक cbits)
अणु
	अचिन्हित पूर्णांक bytes = 1 << cbits;
	अचिन्हित पूर्णांक trim = bytes;
	अचिन्हित पूर्णांक bitshअगरt = 32;

	/*
	 * i_size and all block offsets in ocfs2 are always 64 bits
	 * wide. i_clusters is 32 bits, in cluster-sized units. So on
	 * 64 bit platक्रमms, cluster size will be the limiting factor.
	 */

#अगर BITS_PER_LONG == 32
	BUILD_BUG_ON(माप(sector_t) != 8);
	/*
	 * We might be limited by page cache size.
	 */
	अगर (bytes > PAGE_SIZE) अणु
		bytes = PAGE_SIZE;
		trim = 1;
		/*
		 * Shअगरt by 31 here so that we करोn't get larger than
		 * MAX_LFS_खाताSIZE
		 */
		bitshअगरt = 31;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Trim by a whole cluster when we can actually approach the
	 * on-disk limits. Otherwise we can overflow i_clusters when
	 * an extent start is at the max offset.
	 */
	वापस (((अचिन्हित दीर्घ दीर्घ)bytes) << bitshअगरt) - trim;
पूर्ण

अटल पूर्णांक ocfs2_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	पूर्णांक incompat_features;
	पूर्णांक ret = 0;
	काष्ठा mount_options parsed_options;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	u32 पंचांगp;

	sync_fileप्रणाली(sb);

	अगर (!ocfs2_parse_options(sb, data, &parsed_options, 1) ||
	    !ocfs2_check_set_options(sb, &parsed_options)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पंचांगp = OCFS2_MOUNT_NOCLUSTER;
	अगर ((osb->s_mount_opt & पंचांगp) != (parsed_options.mount_opt & पंचांगp)) अणु
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot change nocluster option on remount\n");
		जाओ out;
	पूर्ण

	पंचांगp = OCFS2_MOUNT_HB_LOCAL | OCFS2_MOUNT_HB_GLOBAL |
		OCFS2_MOUNT_HB_NONE;
	अगर ((osb->s_mount_opt & पंचांगp) != (parsed_options.mount_opt & पंचांगp)) अणु
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot change heartbeat mode on remount\n");
		जाओ out;
	पूर्ण

	अगर ((osb->s_mount_opt & OCFS2_MOUNT_DATA_WRITEBACK) !=
	    (parsed_options.mount_opt & OCFS2_MOUNT_DATA_WRITEBACK)) अणु
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot change data mode on remount\n");
		जाओ out;
	पूर्ण

	/* Probably करोn't want this on remount; it might
	 * mess with other nodes */
	अगर (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64) &&
	    (parsed_options.mount_opt & OCFS2_MOUNT_INODE64)) अणु
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot enable inode64 on remount\n");
		जाओ out;
	पूर्ण

	/* We're going to/from पढ़ोonly mode. */
	अगर ((bool)(*flags & SB_RDONLY) != sb_rकरोnly(sb)) अणु
		/* Disable quota accounting beक्रमe remounting RO */
		अगर (*flags & SB_RDONLY) अणु
			ret = ocfs2_susp_quotas(osb, 0);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		/* Lock here so the check of HARD_RO and the potential
		 * setting of SOFT_RO is atomic. */
		spin_lock(&osb->osb_lock);
		अगर (osb->osb_flags & OCFS2_OSB_HARD_RO) अणु
			mlog(ML_ERROR, "Remount on readonly device is forbidden.\n");
			ret = -EROFS;
			जाओ unlock_osb;
		पूर्ण

		अगर (*flags & SB_RDONLY) अणु
			sb->s_flags |= SB_RDONLY;
			osb->osb_flags |= OCFS2_OSB_SOFT_RO;
		पूर्ण अन्यथा अणु
			अगर (osb->osb_flags & OCFS2_OSB_ERROR_FS) अणु
				mlog(ML_ERROR, "Cannot remount RDWR "
				     "filesystem due to previous errors.\n");
				ret = -EROFS;
				जाओ unlock_osb;
			पूर्ण
			incompat_features = OCFS2_HAS_RO_COMPAT_FEATURE(sb, ~OCFS2_FEATURE_RO_COMPAT_SUPP);
			अगर (incompat_features) अणु
				mlog(ML_ERROR, "Cannot remount RDWR because "
				     "of unsupported optional features "
				     "(%x).\n", incompat_features);
				ret = -EINVAL;
				जाओ unlock_osb;
			पूर्ण
			sb->s_flags &= ~SB_RDONLY;
			osb->osb_flags &= ~OCFS2_OSB_SOFT_RO;
		पूर्ण
		trace_ocfs2_remount(sb->s_flags, osb->osb_flags, *flags);
unlock_osb:
		spin_unlock(&osb->osb_lock);
		/* Enable quota accounting after remounting RW */
		अगर (!ret && !(*flags & SB_RDONLY)) अणु
			अगर (sb_any_quota_suspended(sb))
				ret = ocfs2_susp_quotas(osb, 1);
			अन्यथा
				ret = ocfs2_enable_quotas(osb);
			अगर (ret < 0) अणु
				/* Return back changes... */
				spin_lock(&osb->osb_lock);
				sb->s_flags |= SB_RDONLY;
				osb->osb_flags |= OCFS2_OSB_SOFT_RO;
				spin_unlock(&osb->osb_lock);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		/* Only save off the new mount options in हाल of a successful
		 * remount. */
		osb->s_mount_opt = parsed_options.mount_opt;
		osb->s_aसमय_quantum = parsed_options.aसमय_quantum;
		osb->preferred_slot = parsed_options.slot;
		अगर (parsed_options.commit_पूर्णांकerval)
			osb->osb_commit_पूर्णांकerval = parsed_options.commit_पूर्णांकerval;

		अगर (!ocfs2_is_hard_पढ़ोonly(osb))
			ocfs2_set_journal_params(osb);

		sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
			((osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL) ?
							SB_POSIXACL : 0);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_sb_probe(काष्ठा super_block *sb,
			  काष्ठा buffer_head **bh,
			  पूर्णांक *sector_size,
			  काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	पूर्णांक status, पंचांगpstat;
	काष्ठा ocfs1_vol_disk_hdr *hdr;
	काष्ठा ocfs2_dinode *di;
	पूर्णांक blksize;

	*bh = शून्य;

	/* may be > 512 */
	*sector_size = bdev_logical_block_size(sb->s_bdev);
	अगर (*sector_size > OCFS2_MAX_BLOCKSIZE) अणु
		mlog(ML_ERROR, "Hardware sector size too large: %d (max=%d)\n",
		     *sector_size, OCFS2_MAX_BLOCKSIZE);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	/* Can this really happen? */
	अगर (*sector_size < OCFS2_MIN_BLOCKSIZE)
		*sector_size = OCFS2_MIN_BLOCKSIZE;

	/* check block zero क्रम old क्रमmat */
	status = ocfs2_get_sector(sb, bh, 0, *sector_size);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	hdr = (काष्ठा ocfs1_vol_disk_hdr *) (*bh)->b_data;
	अगर (hdr->major_version == OCFS1_MAJOR_VERSION) अणु
		mlog(ML_ERROR, "incompatible version: %u.%u\n",
		     hdr->major_version, hdr->minor_version);
		status = -EINVAL;
	पूर्ण
	अगर (स_भेद(hdr->signature, OCFS1_VOLUME_SIGNATURE,
		   म_माप(OCFS1_VOLUME_SIGNATURE)) == 0) अणु
		mlog(ML_ERROR, "incompatible volume signature: %8s\n",
		     hdr->signature);
		status = -EINVAL;
	पूर्ण
	brअन्यथा(*bh);
	*bh = शून्य;
	अगर (status < 0) अणु
		mlog(ML_ERROR, "This is an ocfs v1 filesystem which must be "
		     "upgraded before mounting with ocfs v2\n");
		जाओ bail;
	पूर्ण

	/*
	 * Now check at magic offset क्रम 512, 1024, 2048, 4096
	 * blocksizes.  4096 is the maximum blocksize because it is
	 * the minimum clustersize.
	 */
	status = -EINVAL;
	क्रम (blksize = *sector_size;
	     blksize <= OCFS2_MAX_BLOCKSIZE;
	     blksize <<= 1) अणु
		पंचांगpstat = ocfs2_get_sector(sb, bh,
					   OCFS2_SUPER_BLOCK_BLKNO,
					   blksize);
		अगर (पंचांगpstat < 0) अणु
			status = पंचांगpstat;
			mlog_त्रुटि_सं(status);
			अवरोध;
		पूर्ण
		di = (काष्ठा ocfs2_dinode *) (*bh)->b_data;
		स_रखो(stats, 0, माप(काष्ठा ocfs2_blockcheck_stats));
		spin_lock_init(&stats->b_lock);
		पंचांगpstat = ocfs2_verअगरy_volume(di, *bh, blksize, stats);
		अगर (पंचांगpstat < 0) अणु
			brअन्यथा(*bh);
			*bh = शून्य;
		पूर्ण
		अगर (पंचांगpstat != -EAGAIN) अणु
			status = पंचांगpstat;
			अवरोध;
		पूर्ण
	पूर्ण

bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_verअगरy_heartbeat(काष्ठा ocfs2_super *osb)
अणु
	u32 hb_enabled = OCFS2_MOUNT_HB_LOCAL | OCFS2_MOUNT_HB_GLOBAL;

	अगर (osb->s_mount_opt & hb_enabled) अणु
		अगर (ocfs2_mount_local(osb)) अणु
			mlog(ML_ERROR, "Cannot heartbeat on a locally "
			     "mounted device.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (ocfs2_userspace_stack(osb)) अणु
			mlog(ML_ERROR, "Userspace stack expected, but "
			     "o2cb heartbeat arguments passed to mount\n");
			वापस -EINVAL;
		पूर्ण
		अगर (((osb->s_mount_opt & OCFS2_MOUNT_HB_GLOBAL) &&
		     !ocfs2_cluster_o2cb_global_heartbeat(osb)) ||
		    ((osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL) &&
		     ocfs2_cluster_o2cb_global_heartbeat(osb))) अणु
			mlog(ML_ERROR, "Mismatching o2cb heartbeat modes\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!(osb->s_mount_opt & hb_enabled)) अणु
		अगर (!ocfs2_mount_local(osb) && !ocfs2_is_hard_पढ़ोonly(osb) &&
		    !ocfs2_userspace_stack(osb)) अणु
			mlog(ML_ERROR, "Heartbeat has to be started to mount "
			     "a read-write clustered device.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If we're using a userspace stack, mount should have passed
 * a name that matches the disk.  If not, mount should not
 * have passed a stack.
 */
अटल पूर्णांक ocfs2_verअगरy_userspace_stack(काष्ठा ocfs2_super *osb,
					काष्ठा mount_options *mopt)
अणु
	अगर (!ocfs2_userspace_stack(osb) && mopt->cluster_stack[0]) अणु
		mlog(ML_ERROR,
		     "cluster stack passed to mount, but this filesystem "
		     "does not support it\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ocfs2_userspace_stack(osb) &&
	    !(osb->s_mount_opt & OCFS2_MOUNT_NOCLUSTER) &&
	    म_भेदन(osb->osb_cluster_stack, mopt->cluster_stack,
		    OCFS2_STACK_LABEL_LEN)) अणु
		mlog(ML_ERROR,
		     "cluster stack passed to mount (\"%s\") does not "
		     "match the filesystem (\"%s\")\n",
		     mopt->cluster_stack,
		     osb->osb_cluster_stack);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_susp_quotas(काष्ठा ocfs2_super *osb, पूर्णांक unsuspend)
अणु
	पूर्णांक type;
	काष्ठा super_block *sb = osb->sb;
	अचिन्हित पूर्णांक feature[OCFS2_MAXQUOTAS] = अणु
					OCFS2_FEATURE_RO_COMPAT_USRQUOTA,
					OCFS2_FEATURE_RO_COMPAT_GRPQUOTAपूर्ण;
	पूर्णांक status = 0;

	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++) अणु
		अगर (!OCFS2_HAS_RO_COMPAT_FEATURE(sb, feature[type]))
			जारी;
		अगर (unsuspend)
			status = dquot_resume(sb, type);
		अन्यथा अणु
			काष्ठा ocfs2_mem_dqinfo *oinfo;

			/* Cancel periodic syncing beक्रमe suspending */
			oinfo = sb_dqinfo(sb, type)->dqi_priv;
			cancel_delayed_work_sync(&oinfo->dqi_sync_work);
			status = dquot_suspend(sb, type);
		पूर्ण
		अगर (status < 0)
			अवरोध;
	पूर्ण
	अगर (status < 0)
		mlog(ML_ERROR, "Failed to suspend/unsuspend quotas on "
		     "remount (error = %d).\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_enable_quotas(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा inode *inode[OCFS2_MAXQUOTAS] = अणु शून्य, शून्य पूर्ण;
	काष्ठा super_block *sb = osb->sb;
	अचिन्हित पूर्णांक feature[OCFS2_MAXQUOTAS] = अणु
					OCFS2_FEATURE_RO_COMPAT_USRQUOTA,
					OCFS2_FEATURE_RO_COMPAT_GRPQUOTAपूर्ण;
	अचिन्हित पूर्णांक ino[OCFS2_MAXQUOTAS] = अणु
					LOCAL_USER_QUOTA_SYSTEM_INODE,
					LOCAL_GROUP_QUOTA_SYSTEM_INODE पूर्ण;
	पूर्णांक status;
	पूर्णांक type;

	sb_dqopt(sb)->flags |= DQUOT_QUOTA_SYS_खाता | DQUOT_NEGATIVE_USAGE;
	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++) अणु
		अगर (!OCFS2_HAS_RO_COMPAT_FEATURE(sb, feature[type]))
			जारी;
		inode[type] = ocfs2_get_प्रणाली_file_inode(osb, ino[type],
							osb->slot_num);
		अगर (!inode[type]) अणु
			status = -ENOENT;
			जाओ out_quota_off;
		पूर्ण
		status = dquot_load_quota_inode(inode[type], type, QFMT_OCFS2,
						DQUOT_USAGE_ENABLED);
		अगर (status < 0)
			जाओ out_quota_off;
	पूर्ण

	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++)
		iput(inode[type]);
	वापस 0;
out_quota_off:
	ocfs2_disable_quotas(osb);
	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++)
		iput(inode[type]);
	mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम ocfs2_disable_quotas(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक type;
	काष्ठा inode *inode;
	काष्ठा super_block *sb = osb->sb;
	काष्ठा ocfs2_mem_dqinfo *oinfo;

	/* We mostly ignore errors in this function because there's not much
	 * we can करो when we see them */
	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++) अणु
		अगर (!sb_has_quota_loaded(sb, type))
			जारी;
		oinfo = sb_dqinfo(sb, type)->dqi_priv;
		cancel_delayed_work_sync(&oinfo->dqi_sync_work);
		inode = igrab(sb->s_dquot.files[type]);
		/* Turn off quotas. This will हटाओ all dquot काष्ठाures from
		 * memory and so they will be स्वतःmatically synced to global
		 * quota files */
		dquot_disable(sb, type, DQUOT_USAGE_ENABLED |
					DQUOT_LIMITS_ENABLED);
		iput(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा dentry *root;
	पूर्णांक status, sector_size;
	काष्ठा mount_options parsed_options;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_super *osb = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	अक्षर nodestr[12];
	काष्ठा ocfs2_blockcheck_stats stats;

	trace_ocfs2_fill_super(sb, data, silent);

	अगर (!ocfs2_parse_options(sb, data, &parsed_options, 0)) अणु
		status = -EINVAL;
		जाओ पढ़ो_super_error;
	पूर्ण

	/* probe क्रम superblock */
	status = ocfs2_sb_probe(sb, &bh, &sector_size, &stats);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "superblock probe failed!\n");
		जाओ पढ़ो_super_error;
	पूर्ण

	status = ocfs2_initialize_super(sb, bh, sector_size, &stats);
	osb = OCFS2_SB(sb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ पढ़ो_super_error;
	पूर्ण
	brअन्यथा(bh);
	bh = शून्य;

	अगर (!ocfs2_check_set_options(sb, &parsed_options)) अणु
		status = -EINVAL;
		जाओ पढ़ो_super_error;
	पूर्ण
	osb->s_mount_opt = parsed_options.mount_opt;
	osb->s_aसमय_quantum = parsed_options.aसमय_quantum;
	osb->preferred_slot = parsed_options.slot;
	osb->osb_commit_पूर्णांकerval = parsed_options.commit_पूर्णांकerval;

	ocfs2_la_set_sizes(osb, parsed_options.localalloc_opt);
	osb->osb_resv_level = parsed_options.resv_level;
	osb->osb_dir_resv_level = parsed_options.resv_level;
	अगर (parsed_options.dir_resv_level == -1)
		osb->osb_dir_resv_level = parsed_options.resv_level;
	अन्यथा
		osb->osb_dir_resv_level = parsed_options.dir_resv_level;

	status = ocfs2_verअगरy_userspace_stack(osb, &parsed_options);
	अगर (status)
		जाओ पढ़ो_super_error;

	sb->s_magic = OCFS2_SUPER_MAGIC;

	sb->s_flags = (sb->s_flags & ~(SB_POSIXACL | SB_NOSEC)) |
		((osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL) ? SB_POSIXACL : 0);

	/* Hard पढ़ोonly mode only अगर: bdev_पढ़ो_only, SB_RDONLY,
	 * heartbeat=none */
	अगर (bdev_पढ़ो_only(sb->s_bdev)) अणु
		अगर (!sb_rकरोnly(sb)) अणु
			status = -EACCES;
			mlog(ML_ERROR, "Readonly device detected but readonly "
			     "mount was not specified.\n");
			जाओ पढ़ो_super_error;
		पूर्ण

		/* You should not be able to start a local heartbeat
		 * on a पढ़ोonly device. */
		अगर (osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL) अणु
			status = -EROFS;
			mlog(ML_ERROR, "Local heartbeat specified on readonly "
			     "device.\n");
			जाओ पढ़ो_super_error;
		पूर्ण

		status = ocfs2_check_journals_nolocks(osb);
		अगर (status < 0) अणु
			अगर (status == -EROFS)
				mlog(ML_ERROR, "Recovery required on readonly "
				     "file system, but write access is "
				     "unavailable.\n");
			अन्यथा
				mlog_त्रुटि_सं(status);
			जाओ पढ़ो_super_error;
		पूर्ण

		ocfs2_set_ro_flag(osb, 1);

		prपूर्णांकk(KERN_NOTICE "ocfs2: Readonly device (%s) detected. "
		       "Cluster services will not be used for this mount. "
		       "Recovery will be skipped.\n", osb->dev_str);
	पूर्ण

	अगर (!ocfs2_is_hard_पढ़ोonly(osb)) अणु
		अगर (sb_rकरोnly(sb))
			ocfs2_set_ro_flag(osb, 0);
	पूर्ण

	status = ocfs2_verअगरy_heartbeat(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ पढ़ो_super_error;
	पूर्ण

	osb->osb_debug_root = debugfs_create_dir(osb->uuid_str,
						 ocfs2_debugfs_root);

	debugfs_create_file("fs_state", S_IFREG|S_IRUSR, osb->osb_debug_root,
			    osb, &ocfs2_osb_debug_fops);

	अगर (ocfs2_meta_ecc(osb))
		ocfs2_blockcheck_stats_debugfs_install( &osb->osb_ecc_stats,
							osb->osb_debug_root);

	status = ocfs2_mount_volume(sb);
	अगर (status < 0)
		जाओ पढ़ो_super_error;

	अगर (osb->root_inode)
		inode = igrab(osb->root_inode);

	अगर (!inode) अणु
		status = -EIO;
		mlog_त्रुटि_सं(status);
		जाओ पढ़ो_super_error;
	पूर्ण

	root = d_make_root(inode);
	अगर (!root) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ पढ़ो_super_error;
	पूर्ण

	sb->s_root = root;

	ocfs2_complete_mount_recovery(osb);

	osb->osb_dev_kset = kset_create_and_add(sb->s_id, शून्य,
						&ocfs2_kset->kobj);
	अगर (!osb->osb_dev_kset) अणु
		status = -ENOMEM;
		mlog(ML_ERROR, "Unable to create device kset %s.\n", sb->s_id);
		जाओ पढ़ो_super_error;
	पूर्ण

	/* Create filecheck sysfs related directories/files at
	 * /sys/fs/ocfs2/<devname>/filecheck */
	अगर (ocfs2_filecheck_create_sysfs(osb)) अणु
		status = -ENOMEM;
		mlog(ML_ERROR, "Unable to create filecheck sysfs directory at "
			"/sys/fs/ocfs2/%s/filecheck.\n", sb->s_id);
		जाओ पढ़ो_super_error;
	पूर्ण

	अगर (ocfs2_mount_local(osb))
		snम_लिखो(nodestr, माप(nodestr), "local");
	अन्यथा
		snम_लिखो(nodestr, माप(nodestr), "%u", osb->node_num);

	prपूर्णांकk(KERN_INFO "ocfs2: Mounting device (%s) on (node %s, slot %d) "
	       "with %s data mode.\n",
	       osb->dev_str, nodestr, osb->slot_num,
	       osb->s_mount_opt & OCFS2_MOUNT_DATA_WRITEBACK ? "writeback" :
	       "ordered");

	अगर ((osb->s_mount_opt & OCFS2_MOUNT_NOCLUSTER) &&
	   !(osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_LOCAL_MOUNT))
		prपूर्णांकk(KERN_NOTICE "ocfs2: The shared device (%s) is mounted "
		       "without cluster aware mode.\n", osb->dev_str);

	atomic_set(&osb->vol_state, VOLUME_MOUNTED);
	wake_up(&osb->osb_mount_event);

	/* Now we can initialize quotas because we can afक्रमd to रुको
	 * क्रम cluster locks recovery now. That also means that truncation
	 * log recovery can happen but that रुकोs क्रम proper quota setup */
	अगर (!sb_rकरोnly(sb)) अणु
		status = ocfs2_enable_quotas(osb);
		अगर (status < 0) अणु
			/* We have to err-out specially here because
			 * s_root is alपढ़ोy set */
			mlog_त्रुटि_सं(status);
			atomic_set(&osb->vol_state, VOLUME_DISABLED);
			wake_up(&osb->osb_mount_event);
			वापस status;
		पूर्ण
	पूर्ण

	ocfs2_complete_quota_recovery(osb);

	/* Now we wake up again क्रम processes रुकोing क्रम quotas */
	atomic_set(&osb->vol_state, VOLUME_MOUNTED_QUOTAS);
	wake_up(&osb->osb_mount_event);

	/* Start this when the mount is almost sure of being successful */
	ocfs2_orphan_scan_start(osb);

	वापस status;

पढ़ो_super_error:
	brअन्यथा(bh);

	अगर (status)
		mlog_त्रुटि_सं(status);

	अगर (osb) अणु
		atomic_set(&osb->vol_state, VOLUME_DISABLED);
		wake_up(&osb->osb_mount_event);
		ocfs2_dismount_volume(sb, 1);
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा dentry *ocfs2_mount(काष्ठा file_प्रणाली_type *fs_type,
			पूर्णांक flags,
			स्थिर अक्षर *dev_name,
			व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, ocfs2_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type ocfs2_fs_type = अणु
	.owner          = THIS_MODULE,
	.name           = "ocfs2",
	.mount          = ocfs2_mount,
	.समाप्त_sb        = समाप्त_block_super,
	.fs_flags       = FS_REQUIRES_DEV|FS_RENAME_DOES_D_MOVE,
	.next           = शून्य
पूर्ण;
MODULE_ALIAS_FS("ocfs2");

अटल पूर्णांक ocfs2_check_set_options(काष्ठा super_block *sb,
				   काष्ठा mount_options *options)
अणु
	अगर (options->mount_opt & OCFS2_MOUNT_USRQUOTA &&
	    !OCFS2_HAS_RO_COMPAT_FEATURE(sb,
					 OCFS2_FEATURE_RO_COMPAT_USRQUOTA)) अणु
		mlog(ML_ERROR, "User quotas were requested, but this "
		     "filesystem does not have the feature enabled.\n");
		वापस 0;
	पूर्ण
	अगर (options->mount_opt & OCFS2_MOUNT_GRPQUOTA &&
	    !OCFS2_HAS_RO_COMPAT_FEATURE(sb,
					 OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)) अणु
		mlog(ML_ERROR, "Group quotas were requested, but this "
		     "filesystem does not have the feature enabled.\n");
		वापस 0;
	पूर्ण
	अगर (options->mount_opt & OCFS2_MOUNT_POSIX_ACL &&
	    !OCFS2_HAS_INCOMPAT_FEATURE(sb, OCFS2_FEATURE_INCOMPAT_XATTR)) अणु
		mlog(ML_ERROR, "ACL support requested but extended attributes "
		     "feature is not enabled\n");
		वापस 0;
	पूर्ण
	/* No ACL setting specअगरied? Use XATTR feature... */
	अगर (!(options->mount_opt & (OCFS2_MOUNT_POSIX_ACL |
				    OCFS2_MOUNT_NO_POSIX_ACL))) अणु
		अगर (OCFS2_HAS_INCOMPAT_FEATURE(sb, OCFS2_FEATURE_INCOMPAT_XATTR))
			options->mount_opt |= OCFS2_MOUNT_POSIX_ACL;
		अन्यथा
			options->mount_opt |= OCFS2_MOUNT_NO_POSIX_ACL;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ocfs2_parse_options(काष्ठा super_block *sb,
			       अक्षर *options,
			       काष्ठा mount_options *mopt,
			       पूर्णांक is_remount)
अणु
	पूर्णांक status, user_stack = 0;
	अक्षर *p;
	u32 पंचांगp;
	पूर्णांक token, option;
	substring_t args[MAX_OPT_ARGS];

	trace_ocfs2_parse_options(is_remount, options ? options : "(none)");

	mopt->commit_पूर्णांकerval = 0;
	mopt->mount_opt = OCFS2_MOUNT_NOINTR;
	mopt->aसमय_quantum = OCFS2_DEFAULT_ATIME_QUANTUM;
	mopt->slot = OCFS2_INVALID_SLOT;
	mopt->localalloc_opt = -1;
	mopt->cluster_stack[0] = '\0';
	mopt->resv_level = OCFS2_DEFAULT_RESV_LEVEL;
	mopt->dir_resv_level = -1;

	अगर (!options) अणु
		status = 1;
		जाओ bail;
	पूर्ण

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_hb_local:
			mopt->mount_opt |= OCFS2_MOUNT_HB_LOCAL;
			अवरोध;
		हाल Opt_hb_none:
			mopt->mount_opt |= OCFS2_MOUNT_HB_NONE;
			अवरोध;
		हाल Opt_hb_global:
			mopt->mount_opt |= OCFS2_MOUNT_HB_GLOBAL;
			अवरोध;
		हाल Opt_barrier:
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option)
				mopt->mount_opt |= OCFS2_MOUNT_BARRIER;
			अन्यथा
				mopt->mount_opt &= ~OCFS2_MOUNT_BARRIER;
			अवरोध;
		हाल Opt_पूर्णांकr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOINTR;
			अवरोध;
		हाल Opt_noपूर्णांकr:
			mopt->mount_opt |= OCFS2_MOUNT_NOINTR;
			अवरोध;
		हाल Opt_err_panic:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_ROFS;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_PANIC;
			अवरोध;
		हाल Opt_err_ro:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_ROFS;
			अवरोध;
		हाल Opt_err_cont:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_ROFS;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_CONT;
			अवरोध;
		हाल Opt_data_ordered:
			mopt->mount_opt &= ~OCFS2_MOUNT_DATA_WRITEBACK;
			अवरोध;
		हाल Opt_data_ग_लिखोback:
			mopt->mount_opt |= OCFS2_MOUNT_DATA_WRITEBACK;
			अवरोध;
		हाल Opt_user_xattr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOUSERXATTR;
			अवरोध;
		हाल Opt_nouser_xattr:
			mopt->mount_opt |= OCFS2_MOUNT_NOUSERXATTR;
			अवरोध;
		हाल Opt_aसमय_quantum:
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option >= 0)
				mopt->aसमय_quantum = option;
			अवरोध;
		हाल Opt_slot:
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option)
				mopt->slot = (u16)option;
			अवरोध;
		हाल Opt_commit:
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option < 0)
				वापस 0;
			अगर (option == 0)
				option = JBD2_DEFAULT_MAX_COMMIT_AGE;
			mopt->commit_पूर्णांकerval = HZ * option;
			अवरोध;
		हाल Opt_localalloc:
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option >= 0)
				mopt->localalloc_opt = option;
			अवरोध;
		हाल Opt_localflocks:
			/*
			 * Changing this during remount could race
			 * flock() requests, or "unbalance" existing
			 * ones (e.g., a lock is taken in one mode but
			 * dropped in the other). If users care enough
			 * to flip locking modes during remount, we
			 * could add a "local" flag to inभागidual
			 * flock काष्ठाures क्रम proper tracking of
			 * state.
			 */
			अगर (!is_remount)
				mopt->mount_opt |= OCFS2_MOUNT_LOCALFLOCKS;
			अवरोध;
		हाल Opt_stack:
			/* Check both that the option we were passed
			 * is of the right length and that it is a proper
			 * string of the right length.
			 */
			अगर (((args[0].to - args[0].from) !=
			     OCFS2_STACK_LABEL_LEN) ||
			    (strnlen(args[0].from,
				     OCFS2_STACK_LABEL_LEN) !=
			     OCFS2_STACK_LABEL_LEN)) अणु
				mlog(ML_ERROR,
				     "Invalid cluster_stack option\n");
				status = 0;
				जाओ bail;
			पूर्ण
			स_नकल(mopt->cluster_stack, args[0].from,
			       OCFS2_STACK_LABEL_LEN);
			mopt->cluster_stack[OCFS2_STACK_LABEL_LEN] = '\0';
			/*
			 * Open code the स_भेद here as we करोn't have
			 * an osb to pass to
			 * ocfs2_userspace_stack().
			 */
			अगर (स_भेद(mopt->cluster_stack,
				   OCFS2_CLASSIC_CLUSTER_STACK,
				   OCFS2_STACK_LABEL_LEN))
				user_stack = 1;
			अवरोध;
		हाल Opt_inode64:
			mopt->mount_opt |= OCFS2_MOUNT_INODE64;
			अवरोध;
		हाल Opt_usrquota:
			mopt->mount_opt |= OCFS2_MOUNT_USRQUOTA;
			अवरोध;
		हाल Opt_grpquota:
			mopt->mount_opt |= OCFS2_MOUNT_GRPQUOTA;
			अवरोध;
		हाल Opt_coherency_buffered:
			mopt->mount_opt |= OCFS2_MOUNT_COHERENCY_BUFFERED;
			अवरोध;
		हाल Opt_coherency_full:
			mopt->mount_opt &= ~OCFS2_MOUNT_COHERENCY_BUFFERED;
			अवरोध;
		हाल Opt_acl:
			mopt->mount_opt |= OCFS2_MOUNT_POSIX_ACL;
			mopt->mount_opt &= ~OCFS2_MOUNT_NO_POSIX_ACL;
			अवरोध;
		हाल Opt_noacl:
			mopt->mount_opt |= OCFS2_MOUNT_NO_POSIX_ACL;
			mopt->mount_opt &= ~OCFS2_MOUNT_POSIX_ACL;
			अवरोध;
		हाल Opt_resv_level:
			अगर (is_remount)
				अवरोध;
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option >= OCFS2_MIN_RESV_LEVEL &&
			    option < OCFS2_MAX_RESV_LEVEL)
				mopt->resv_level = option;
			अवरोध;
		हाल Opt_dir_resv_level:
			अगर (is_remount)
				अवरोध;
			अगर (match_पूर्णांक(&args[0], &option)) अणु
				status = 0;
				जाओ bail;
			पूर्ण
			अगर (option >= OCFS2_MIN_RESV_LEVEL &&
			    option < OCFS2_MAX_RESV_LEVEL)
				mopt->dir_resv_level = option;
			अवरोध;
		हाल Opt_journal_async_commit:
			mopt->mount_opt |= OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT;
			अवरोध;
		हाल Opt_nocluster:
			mopt->mount_opt |= OCFS2_MOUNT_NOCLUSTER;
			अवरोध;
		शेष:
			mlog(ML_ERROR,
			     "Unrecognized mount option \"%s\" "
			     "or missing value\n", p);
			status = 0;
			जाओ bail;
		पूर्ण
	पूर्ण

	अगर (user_stack == 0) अणु
		/* Ensure only one heartbeat mode */
		पंचांगp = mopt->mount_opt & (OCFS2_MOUNT_HB_LOCAL |
					 OCFS2_MOUNT_HB_GLOBAL |
					 OCFS2_MOUNT_HB_NONE);
		अगर (hweight32(पंचांगp) != 1) अणु
			mlog(ML_ERROR, "Invalid heartbeat mount options\n");
			status = 0;
			जाओ bail;
		पूर्ण
	पूर्ण

	status = 1;

bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_show_options(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(root->d_sb);
	अचिन्हित दीर्घ opts = osb->s_mount_opt;
	अचिन्हित पूर्णांक local_alloc_megs;

	अगर (opts & (OCFS2_MOUNT_HB_LOCAL | OCFS2_MOUNT_HB_GLOBAL)) अणु
		seq_म_लिखो(s, ",_netdev");
		अगर (opts & OCFS2_MOUNT_HB_LOCAL)
			seq_म_लिखो(s, ",%s", OCFS2_HB_LOCAL);
		अन्यथा
			seq_म_लिखो(s, ",%s", OCFS2_HB_GLOBAL);
	पूर्ण अन्यथा
		seq_म_लिखो(s, ",%s", OCFS2_HB_NONE);

	अगर (opts & OCFS2_MOUNT_NOINTR)
		seq_म_लिखो(s, ",nointr");

	अगर (opts & OCFS2_MOUNT_DATA_WRITEBACK)
		seq_म_लिखो(s, ",data=writeback");
	अन्यथा
		seq_म_लिखो(s, ",data=ordered");

	अगर (opts & OCFS2_MOUNT_BARRIER)
		seq_म_लिखो(s, ",barrier=1");

	अगर (opts & OCFS2_MOUNT_ERRORS_PANIC)
		seq_म_लिखो(s, ",errors=panic");
	अन्यथा अगर (opts & OCFS2_MOUNT_ERRORS_CONT)
		seq_म_लिखो(s, ",errors=continue");
	अन्यथा
		seq_म_लिखो(s, ",errors=remount-ro");

	अगर (osb->preferred_slot != OCFS2_INVALID_SLOT)
		seq_म_लिखो(s, ",preferred_slot=%d", osb->preferred_slot);

	seq_म_लिखो(s, ",atime_quantum=%u", osb->s_aसमय_quantum);

	अगर (osb->osb_commit_पूर्णांकerval)
		seq_म_लिखो(s, ",commit=%u",
			   (अचिन्हित) (osb->osb_commit_पूर्णांकerval / HZ));

	local_alloc_megs = osb->local_alloc_bits >> (20 - osb->s_clustersize_bits);
	अगर (local_alloc_megs != ocfs2_la_शेष_mb(osb))
		seq_म_लिखो(s, ",localalloc=%d", local_alloc_megs);

	अगर (opts & OCFS2_MOUNT_LOCALFLOCKS)
		seq_म_लिखो(s, ",localflocks,");

	अगर (osb->osb_cluster_stack[0])
		seq_show_option_n(s, "cluster_stack", osb->osb_cluster_stack,
				  OCFS2_STACK_LABEL_LEN);
	अगर (opts & OCFS2_MOUNT_USRQUOTA)
		seq_म_लिखो(s, ",usrquota");
	अगर (opts & OCFS2_MOUNT_GRPQUOTA)
		seq_म_लिखो(s, ",grpquota");

	अगर (opts & OCFS2_MOUNT_COHERENCY_BUFFERED)
		seq_म_लिखो(s, ",coherency=buffered");
	अन्यथा
		seq_म_लिखो(s, ",coherency=full");

	अगर (opts & OCFS2_MOUNT_NOUSERXATTR)
		seq_म_लिखो(s, ",nouser_xattr");
	अन्यथा
		seq_म_लिखो(s, ",user_xattr");

	अगर (opts & OCFS2_MOUNT_INODE64)
		seq_म_लिखो(s, ",inode64");

	अगर (opts & OCFS2_MOUNT_POSIX_ACL)
		seq_म_लिखो(s, ",acl");
	अन्यथा
		seq_म_लिखो(s, ",noacl");

	अगर (osb->osb_resv_level != OCFS2_DEFAULT_RESV_LEVEL)
		seq_म_लिखो(s, ",resv_level=%d", osb->osb_resv_level);

	अगर (osb->osb_dir_resv_level != osb->osb_resv_level)
		seq_म_लिखो(s, ",dir_resv_level=%d", osb->osb_resv_level);

	अगर (opts & OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT)
		seq_म_लिखो(s, ",journal_async_commit");

	अगर (opts & OCFS2_MOUNT_NOCLUSTER)
		seq_म_लिखो(s, ",nocluster");

	वापस 0;
पूर्ण

अटल पूर्णांक __init ocfs2_init(व्योम)
अणु
	पूर्णांक status;

	status = init_ocfs2_uptodate_cache();
	अगर (status < 0)
		जाओ out1;

	status = ocfs2_initialize_mem_caches();
	अगर (status < 0)
		जाओ out2;

	ocfs2_debugfs_root = debugfs_create_dir("ocfs2", शून्य);

	ocfs2_set_locking_protocol();

	status = रेजिस्टर_quota_क्रमmat(&ocfs2_quota_क्रमmat);
	अगर (status < 0)
		जाओ out3;
	status = रेजिस्टर_fileप्रणाली(&ocfs2_fs_type);
	अगर (!status)
		वापस 0;

	unरेजिस्टर_quota_क्रमmat(&ocfs2_quota_क्रमmat);
out3:
	debugfs_हटाओ(ocfs2_debugfs_root);
	ocfs2_मुक्त_mem_caches();
out2:
	निकास_ocfs2_uptodate_cache();
out1:
	mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम __निकास ocfs2_निकास(व्योम)
अणु
	unरेजिस्टर_quota_क्रमmat(&ocfs2_quota_क्रमmat);

	debugfs_हटाओ(ocfs2_debugfs_root);

	ocfs2_मुक्त_mem_caches();

	unरेजिस्टर_fileप्रणाली(&ocfs2_fs_type);

	निकास_ocfs2_uptodate_cache();
पूर्ण

अटल व्योम ocfs2_put_super(काष्ठा super_block *sb)
अणु
	trace_ocfs2_put_super(sb);

	ocfs2_sync_blockdev(sb);
	ocfs2_dismount_volume(sb, 0);
पूर्ण

अटल पूर्णांक ocfs2_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा ocfs2_super *osb;
	u32 numbits, मुक्तbits;
	पूर्णांक status;
	काष्ठा ocfs2_dinode *bm_lock;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा inode *inode = शून्य;

	trace_ocfs2_statfs(dentry->d_sb, buf);

	osb = OCFS2_SB(dentry->d_sb);

	inode = ocfs2_get_प्रणाली_file_inode(osb,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT);
	अगर (!inode) अणु
		mlog(ML_ERROR, "failed to get bitmap inode\n");
		status = -EIO;
		जाओ bail;
	पूर्ण

	status = ocfs2_inode_lock(inode, &bh, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	bm_lock = (काष्ठा ocfs2_dinode *) bh->b_data;

	numbits = le32_to_cpu(bm_lock->id1.biपंचांगap1.i_total);
	मुक्तbits = numbits - le32_to_cpu(bm_lock->id1.biपंचांगap1.i_used);

	buf->f_type = OCFS2_SUPER_MAGIC;
	buf->f_bsize = dentry->d_sb->s_blocksize;
	buf->f_namelen = OCFS2_MAX_खाताNAME_LEN;
	buf->f_blocks = ((sector_t) numbits) *
			(osb->s_clustersize >> osb->sb->s_blocksize_bits);
	buf->f_bमुक्त = ((sector_t) मुक्तbits) *
		       (osb->s_clustersize >> osb->sb->s_blocksize_bits);
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_files = numbits;
	buf->f_fमुक्त = मुक्तbits;
	buf->f_fsid.val[0] = crc32_le(0, osb->uuid_str, OCFS2_VOL_UUID_LEN)
				& 0xFFFFFFFFUL;
	buf->f_fsid.val[1] = crc32_le(0, osb->uuid_str + OCFS2_VOL_UUID_LEN,
				OCFS2_VOL_UUID_LEN) & 0xFFFFFFFFUL;

	brअन्यथा(bh);

	ocfs2_inode_unlock(inode, 0);
	status = 0;
bail:
	iput(inode);

	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

अटल व्योम ocfs2_inode_init_once(व्योम *data)
अणु
	काष्ठा ocfs2_inode_info *oi = data;

	oi->ip_flags = 0;
	oi->ip_खोलो_count = 0;
	spin_lock_init(&oi->ip_lock);
	ocfs2_extent_map_init(&oi->vfs_inode);
	INIT_LIST_HEAD(&oi->ip_io_markers);
	INIT_LIST_HEAD(&oi->ip_unwritten_list);
	oi->ip_dir_start_lookup = 0;
	init_rwsem(&oi->ip_alloc_sem);
	init_rwsem(&oi->ip_xattr_sem);
	mutex_init(&oi->ip_io_mutex);

	oi->ip_blkno = 0ULL;
	oi->ip_clusters = 0;
	oi->ip_next_orphan = शून्य;

	ocfs2_resv_init_once(&oi->ip_la_data_resv);

	ocfs2_lock_res_init_once(&oi->ip_rw_lockres);
	ocfs2_lock_res_init_once(&oi->ip_inode_lockres);
	ocfs2_lock_res_init_once(&oi->ip_खोलो_lockres);

	ocfs2_metadata_cache_init(INODE_CACHE(&oi->vfs_inode),
				  &ocfs2_inode_caching_ops);

	inode_init_once(&oi->vfs_inode);
पूर्ण

अटल पूर्णांक ocfs2_initialize_mem_caches(व्योम)
अणु
	ocfs2_inode_cachep = kmem_cache_create("ocfs2_inode_cache",
				       माप(काष्ठा ocfs2_inode_info),
				       0,
				       (SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
				       ocfs2_inode_init_once);
	ocfs2_dquot_cachep = kmem_cache_create("ocfs2_dquot_cache",
					माप(काष्ठा ocfs2_dquot),
					0,
					(SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD),
					शून्य);
	ocfs2_qf_chunk_cachep = kmem_cache_create("ocfs2_qf_chunk_cache",
					माप(काष्ठा ocfs2_quota_chunk),
					0,
					(SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD),
					शून्य);
	अगर (!ocfs2_inode_cachep || !ocfs2_dquot_cachep ||
	    !ocfs2_qf_chunk_cachep) अणु
		kmem_cache_destroy(ocfs2_inode_cachep);
		kmem_cache_destroy(ocfs2_dquot_cachep);
		kmem_cache_destroy(ocfs2_qf_chunk_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ocfs2_मुक्त_mem_caches(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ocfs2_inode_cachep);
	ocfs2_inode_cachep = शून्य;

	kmem_cache_destroy(ocfs2_dquot_cachep);
	ocfs2_dquot_cachep = शून्य;

	kmem_cache_destroy(ocfs2_qf_chunk_cachep);
	ocfs2_qf_chunk_cachep = शून्य;
पूर्ण

अटल पूर्णांक ocfs2_get_sector(काष्ठा super_block *sb,
			    काष्ठा buffer_head **bh,
			    पूर्णांक block,
			    पूर्णांक sect_size)
अणु
	अगर (!sb_set_blocksize(sb, sect_size)) अणु
		mlog(ML_ERROR, "unable to set blocksize\n");
		वापस -EIO;
	पूर्ण

	*bh = sb_getblk(sb, block);
	अगर (!*bh) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण
	lock_buffer(*bh);
	अगर (!buffer_dirty(*bh))
		clear_buffer_uptodate(*bh);
	unlock_buffer(*bh);
	ll_rw_block(REQ_OP_READ, 0, 1, bh);
	रुको_on_buffer(*bh);
	अगर (!buffer_uptodate(*bh)) अणु
		mlog_त्रुटि_सं(-EIO);
		brअन्यथा(*bh);
		*bh = शून्य;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_mount_volume(काष्ठा super_block *sb)
अणु
	पूर्णांक status = 0;
	पूर्णांक unlock_super = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		जाओ leave;

	mutex_init(&osb->obs_trim_fs_mutex);

	status = ocfs2_dlm_init(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		अगर (status == -EBADR && ocfs2_userspace_stack(osb))
			mlog(ML_ERROR, "couldn't mount because cluster name on"
			" disk does not match the running cluster name.\n");
		जाओ leave;
	पूर्ण

	status = ocfs2_super_lock(osb, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण
	unlock_super = 1;

	/* This will load up the node map and add ourselves to it. */
	status = ocfs2_find_slot(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* load all node-local प्रणाली inodes */
	status = ocfs2_init_local_प्रणाली_inodes(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_check_volume(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_truncate_log_init(osb);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

leave:
	अगर (unlock_super)
		ocfs2_super_unlock(osb, 1);

	वापस status;
पूर्ण

अटल व्योम ocfs2_dismount_volume(काष्ठा super_block *sb, पूर्णांक mnt_err)
अणु
	पूर्णांक पंचांगp, hangup_needed = 0;
	काष्ठा ocfs2_super *osb = शून्य;
	अक्षर nodestr[12];

	trace_ocfs2_dismount_volume(sb);

	BUG_ON(!sb);
	osb = OCFS2_SB(sb);
	BUG_ON(!osb);

	/* Remove file check sysfs related directores/files,
	 * and रुको क्रम the pending file check operations */
	ocfs2_filecheck_हटाओ_sysfs(osb);

	kset_unरेजिस्टर(osb->osb_dev_kset);

	/* Orphan scan should be stopped as early as possible */
	ocfs2_orphan_scan_stop(osb);

	ocfs2_disable_quotas(osb);

	/* All dquots should be मुक्तd by now */
	WARN_ON(!llist_empty(&osb->dquot_drop_list));
	/* Wait क्रम worker to be करोne with the work काष्ठाure in osb */
	cancel_work_sync(&osb->dquot_drop_work);

	ocfs2_shutकरोwn_local_alloc(osb);

	ocfs2_truncate_log_shutकरोwn(osb);

	/* This will disable recovery and flush any recovery work. */
	ocfs2_recovery_निकास(osb);

	ocfs2_journal_shutकरोwn(osb);

	ocfs2_sync_blockdev(sb);

	ocfs2_purge_refcount_trees(osb);

	/* No cluster connection means we've failed during mount, so skip
	 * all the steps which depended on that to complete. */
	अगर (osb->cconn) अणु
		पंचांगp = ocfs2_super_lock(osb, 1);
		अगर (पंचांगp < 0) अणु
			mlog_त्रुटि_सं(पंचांगp);
			वापस;
		पूर्ण
	पूर्ण

	अगर (osb->slot_num != OCFS2_INVALID_SLOT)
		ocfs2_put_slot(osb);

	अगर (osb->cconn)
		ocfs2_super_unlock(osb, 1);

	ocfs2_release_प्रणाली_inodes(osb);

	/*
	 * If we're dismounting due to mount error, mount.ocfs2 will clean
	 * up heartbeat.  If we're a local mount, there is no heartbeat.
	 * If we failed beक्रमe we got a uuid_str yet, we can't stop
	 * heartbeat.  Otherwise, करो it.
	 */
	अगर (!mnt_err && !ocfs2_mount_local(osb) && osb->uuid_str &&
	    !ocfs2_is_hard_पढ़ोonly(osb))
		hangup_needed = 1;

	अगर (osb->cconn)
		ocfs2_dlm_shutकरोwn(osb, hangup_needed);

	ocfs2_blockcheck_stats_debugfs_हटाओ(&osb->osb_ecc_stats);
	debugfs_हटाओ_recursive(osb->osb_debug_root);

	अगर (hangup_needed)
		ocfs2_cluster_hangup(osb->uuid_str, म_माप(osb->uuid_str));

	atomic_set(&osb->vol_state, VOLUME_DISMOUNTED);

	अगर (ocfs2_mount_local(osb))
		snम_लिखो(nodestr, माप(nodestr), "local");
	अन्यथा
		snम_लिखो(nodestr, माप(nodestr), "%u", osb->node_num);

	prपूर्णांकk(KERN_INFO "ocfs2: Unmounting device (%s) on (node %s)\n",
	       osb->dev_str, nodestr);

	ocfs2_delete_osb(osb);
	kमुक्त(osb);
	sb->s_dev = 0;
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक ocfs2_setup_osb_uuid(काष्ठा ocfs2_super *osb, स्थिर अचिन्हित अक्षर *uuid,
				अचिन्हित uuid_bytes)
अणु
	पूर्णांक i, ret;
	अक्षर *ptr;

	BUG_ON(uuid_bytes != OCFS2_VOL_UUID_LEN);

	osb->uuid_str = kzalloc(OCFS2_VOL_UUID_LEN * 2 + 1, GFP_KERNEL);
	अगर (osb->uuid_str == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0, ptr = osb->uuid_str; i < OCFS2_VOL_UUID_LEN; i++) अणु
		/* prपूर्णांक with null */
		ret = snम_लिखो(ptr, 3, "%02X", uuid[i]);
		अगर (ret != 2) /* drop super cleans up */
			वापस -EINVAL;
		/* then only advance past the last अक्षर */
		ptr += 2;
	पूर्ण

	वापस 0;
पूर्ण

/* Make sure entire volume is addressable by our journal.  Requires
   osb_clusters_at_boot to be valid and क्रम the journal to have been
   initialized by ocfs2_journal_init(). */
अटल पूर्णांक ocfs2_journal_addressable(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status = 0;
	u64 max_block =
		ocfs2_clusters_to_blocks(osb->sb,
					 osb->osb_clusters_at_boot) - 1;

	/* 32-bit block number is always OK. */
	अगर (max_block <= (u32)~0ULL)
		जाओ out;

	/* Volume is "huge", so see अगर our journal is new enough to
	   support it. */
	अगर (!(OCFS2_HAS_COMPAT_FEATURE(osb->sb,
				       OCFS2_FEATURE_COMPAT_JBD2_SB) &&
	      jbd2_journal_check_used_features(osb->journal->j_journal, 0, 0,
					       JBD2_FEATURE_INCOMPAT_64BIT))) अणु
		mlog(ML_ERROR, "The journal cannot address the entire volume. "
		     "Enable the 'block64' journal option with tunefs.ocfs2");
		status = -EFBIG;
		जाओ out;
	पूर्ण

 out:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_initialize_super(काष्ठा super_block *sb,
				  काष्ठा buffer_head *bh,
				  पूर्णांक sector_size,
				  काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	पूर्णांक status;
	पूर्णांक i, cbits, bbits;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_journal *journal;
	काष्ठा ocfs2_super *osb;
	u64 total_blocks;

	osb = kzalloc(माप(काष्ठा ocfs2_super), GFP_KERNEL);
	अगर (!osb) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	sb->s_fs_info = osb;
	sb->s_op = &ocfs2_sops;
	sb->s_d_op = &ocfs2_dentry_ops;
	sb->s_export_op = &ocfs2_export_ops;
	sb->s_qcop = &dquot_quotactl_sysfile_ops;
	sb->dq_op = &ocfs2_quota_operations;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
	sb->s_xattr = ocfs2_xattr_handlers;
	sb->s_समय_gran = 1;
	sb->s_flags |= SB_NOATIME;
	/* this is needed to support O_LARGEखाता */
	cbits = le32_to_cpu(di->id2.i_super.s_clustersize_bits);
	bbits = le32_to_cpu(di->id2.i_super.s_blocksize_bits);
	sb->s_maxbytes = ocfs2_max_file_offset(bbits, cbits);
	स_नकल(&sb->s_uuid, di->id2.i_super.s_uuid,
	       माप(di->id2.i_super.s_uuid));

	osb->osb_dx_mask = (1 << (cbits - bbits)) - 1;

	क्रम (i = 0; i < 3; i++)
		osb->osb_dx_seed[i] = le32_to_cpu(di->id2.i_super.s_dx_seed[i]);
	osb->osb_dx_seed[3] = le32_to_cpu(di->id2.i_super.s_uuid_hash);

	osb->sb = sb;
	osb->s_sectsize_bits = blksize_bits(sector_size);
	BUG_ON(!osb->s_sectsize_bits);

	spin_lock_init(&osb->dc_task_lock);
	init_रुकोqueue_head(&osb->dc_event);
	osb->dc_work_sequence = 0;
	osb->dc_wake_sequence = 0;
	INIT_LIST_HEAD(&osb->blocked_lock_list);
	osb->blocked_lock_count = 0;
	spin_lock_init(&osb->osb_lock);
	spin_lock_init(&osb->osb_xattr_lock);
	ocfs2_init_steal_slots(osb);

	mutex_init(&osb->प्रणाली_file_mutex);

	atomic_set(&osb->alloc_stats.moves, 0);
	atomic_set(&osb->alloc_stats.local_data, 0);
	atomic_set(&osb->alloc_stats.biपंचांगap_data, 0);
	atomic_set(&osb->alloc_stats.bg_allocs, 0);
	atomic_set(&osb->alloc_stats.bg_extends, 0);

	/* Copy the blockcheck stats from the superblock probe */
	osb->osb_ecc_stats = *stats;

	ocfs2_init_node_maps(osb);

	snम_लिखो(osb->dev_str, माप(osb->dev_str), "%u,%u",
		 MAJOR(osb->sb->s_dev), MINOR(osb->sb->s_dev));

	osb->max_slots = le16_to_cpu(di->id2.i_super.s_max_slots);
	अगर (osb->max_slots > OCFS2_MAX_SLOTS || osb->max_slots == 0) अणु
		mlog(ML_ERROR, "Invalid number of node slots (%u)\n",
		     osb->max_slots);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	ocfs2_orphan_scan_init(osb);

	status = ocfs2_recovery_init(osb);
	अगर (status) अणु
		mlog(ML_ERROR, "Unable to initialize recovery state\n");
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	init_रुकोqueue_head(&osb->checkpoपूर्णांक_event);

	osb->s_aसमय_quantum = OCFS2_DEFAULT_ATIME_QUANTUM;

	osb->slot_num = OCFS2_INVALID_SLOT;

	osb->s_xattr_अंतरभूत_size = le16_to_cpu(
					di->id2.i_super.s_xattr_अंतरभूत_size);

	osb->local_alloc_state = OCFS2_LA_UNUSED;
	osb->local_alloc_bh = शून्य;
	INIT_DELAYED_WORK(&osb->la_enable_wq, ocfs2_la_enable_worker);

	init_रुकोqueue_head(&osb->osb_mount_event);

	status = ocfs2_resmap_init(osb, &osb->osb_la_resmap);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb->vol_label = kदो_स्मृति(OCFS2_MAX_VOL_LABEL_LEN, GFP_KERNEL);
	अगर (!osb->vol_label) अणु
		mlog(ML_ERROR, "unable to alloc vol label\n");
		status = -ENOMEM;
		जाओ bail;
	पूर्ण

	osb->slot_recovery_generations =
		kसुस्मृति(osb->max_slots, माप(*osb->slot_recovery_generations),
			GFP_KERNEL);
	अगर (!osb->slot_recovery_generations) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	init_रुकोqueue_head(&osb->osb_wipe_event);
	osb->osb_orphan_wipes = kसुस्मृति(osb->max_slots,
					माप(*osb->osb_orphan_wipes),
					GFP_KERNEL);
	अगर (!osb->osb_orphan_wipes) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb->osb_rf_lock_tree = RB_ROOT;

	osb->s_feature_compat =
		le32_to_cpu(OCFS2_RAW_SB(di)->s_feature_compat);
	osb->s_feature_ro_compat =
		le32_to_cpu(OCFS2_RAW_SB(di)->s_feature_ro_compat);
	osb->s_feature_incompat =
		le32_to_cpu(OCFS2_RAW_SB(di)->s_feature_incompat);

	अगर ((i = OCFS2_HAS_INCOMPAT_FEATURE(osb->sb, ~OCFS2_FEATURE_INCOMPAT_SUPP))) अणु
		mlog(ML_ERROR, "couldn't mount because of unsupported "
		     "optional features (%x).\n", i);
		status = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (!sb_rकरोnly(osb->sb) && (i = OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb, ~OCFS2_FEATURE_RO_COMPAT_SUPP))) अणु
		mlog(ML_ERROR, "couldn't mount RDWR because of "
		     "unsupported optional features (%x).\n", i);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (ocfs2_clusterinfo_valid(osb)) अणु
		osb->osb_stackflags =
			OCFS2_RAW_SB(di)->s_cluster_info.ci_stackflags;
		strlcpy(osb->osb_cluster_stack,
		       OCFS2_RAW_SB(di)->s_cluster_info.ci_stack,
		       OCFS2_STACK_LABEL_LEN + 1);
		अगर (म_माप(osb->osb_cluster_stack) != OCFS2_STACK_LABEL_LEN) अणु
			mlog(ML_ERROR,
			     "couldn't mount because of an invalid "
			     "cluster stack label (%s) \n",
			     osb->osb_cluster_stack);
			status = -EINVAL;
			जाओ bail;
		पूर्ण
		strlcpy(osb->osb_cluster_name,
			OCFS2_RAW_SB(di)->s_cluster_info.ci_cluster,
			OCFS2_CLUSTER_NAME_LEN + 1);
	पूर्ण अन्यथा अणु
		/* The empty string is identical with classic tools that
		 * करोn't know about s_cluster_info. */
		osb->osb_cluster_stack[0] = '\0';
	पूर्ण

	get_अक्रमom_bytes(&osb->s_next_generation, माप(u32));

	/* FIXME
	 * This should be करोne in ocfs2_journal_init(), but unknown
	 * ordering issues will cause the fileप्रणाली to crash.
	 * If anyone wants to figure out what part of the code
	 * refers to osb->journal beक्रमe ocfs2_journal_init() is run,
	 * be my guest.
	 */
	/* initialize our journal काष्ठाure */

	journal = kzalloc(माप(काष्ठा ocfs2_journal), GFP_KERNEL);
	अगर (!journal) अणु
		mlog(ML_ERROR, "unable to alloc journal\n");
		status = -ENOMEM;
		जाओ bail;
	पूर्ण
	osb->journal = journal;
	journal->j_osb = osb;

	atomic_set(&journal->j_num_trans, 0);
	init_rwsem(&journal->j_trans_barrier);
	init_रुकोqueue_head(&journal->j_checkpoपूर्णांकed);
	spin_lock_init(&journal->j_lock);
	journal->j_trans_id = (अचिन्हित दीर्घ) 1;
	INIT_LIST_HEAD(&journal->j_la_cleanups);
	INIT_WORK(&journal->j_recovery_work, ocfs2_complete_recovery);
	journal->j_state = OCFS2_JOURNAL_FREE;

	INIT_WORK(&osb->dquot_drop_work, ocfs2_drop_dquot_refs);
	init_llist_head(&osb->dquot_drop_list);

	/* get some pseuकरो स्थिरants क्रम clustersize bits */
	osb->s_clustersize_bits =
		le32_to_cpu(di->id2.i_super.s_clustersize_bits);
	osb->s_clustersize = 1 << osb->s_clustersize_bits;

	अगर (osb->s_clustersize < OCFS2_MIN_CLUSTERSIZE ||
	    osb->s_clustersize > OCFS2_MAX_CLUSTERSIZE) अणु
		mlog(ML_ERROR, "Volume has invalid cluster size (%d)\n",
		     osb->s_clustersize);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	total_blocks = ocfs2_clusters_to_blocks(osb->sb,
						le32_to_cpu(di->i_clusters));

	status = generic_check_addressable(osb->sb->s_blocksize_bits,
					   total_blocks);
	अगर (status) अणु
		mlog(ML_ERROR, "Volume too large "
		     "to mount safely on this system");
		status = -EFBIG;
		जाओ bail;
	पूर्ण

	अगर (ocfs2_setup_osb_uuid(osb, di->id2.i_super.s_uuid,
				 माप(di->id2.i_super.s_uuid))) अणु
		mlog(ML_ERROR, "Out of memory trying to setup our uuid.\n");
		status = -ENOMEM;
		जाओ bail;
	पूर्ण

	strlcpy(osb->vol_label, di->id2.i_super.s_label,
		OCFS2_MAX_VOL_LABEL_LEN);
	osb->root_blkno = le64_to_cpu(di->id2.i_super.s_root_blkno);
	osb->प्रणाली_dir_blkno = le64_to_cpu(di->id2.i_super.s_प्रणाली_dir_blkno);
	osb->first_cluster_group_blkno =
		le64_to_cpu(di->id2.i_super.s_first_cluster_group);
	osb->fs_generation = le32_to_cpu(di->i_fs_generation);
	osb->uuid_hash = le32_to_cpu(di->id2.i_super.s_uuid_hash);
	trace_ocfs2_initialize_super(osb->vol_label, osb->uuid_str,
				     (अचिन्हित दीर्घ दीर्घ)osb->root_blkno,
				     (अचिन्हित दीर्घ दीर्घ)osb->प्रणाली_dir_blkno,
				     osb->s_clustersize_bits);

	osb->osb_dlm_debug = ocfs2_new_dlm_debug();
	अगर (!osb->osb_dlm_debug) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	atomic_set(&osb->vol_state, VOLUME_INIT);

	/* load root, प्रणाली_dir, and all global प्रणाली inodes */
	status = ocfs2_init_global_प्रणाली_inodes(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/*
	 * global biपंचांगap
	 */
	inode = ocfs2_get_प्रणाली_file_inode(osb, GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT);
	अगर (!inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb->biपंचांगap_blkno = OCFS2_I(inode)->ip_blkno;
	osb->osb_clusters_at_boot = OCFS2_I(inode)->ip_clusters;
	iput(inode);

	osb->biपंचांगap_cpg = ocfs2_group_biपंचांगap_size(sb, 0,
				 osb->s_feature_incompat) * 8;

	status = ocfs2_init_slot_info(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	cleancache_init_shared_fs(sb);

	osb->ocfs2_wq = alloc_ordered_workqueue("ocfs2_wq", WQ_MEM_RECLAIM);
	अगर (!osb->ocfs2_wq) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
	पूर्ण

bail:
	वापस status;
पूर्ण

/*
 * will वापस: -EAGAIN अगर it is ok to keep searching क्रम superblocks
 *              -EINVAL अगर there is a bad superblock
 *              0 on success
 */
अटल पूर्णांक ocfs2_verअगरy_volume(काष्ठा ocfs2_dinode *di,
			       काष्ठा buffer_head *bh,
			       u32 blksz,
			       काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	पूर्णांक status = -EAGAIN;

	अगर (स_भेद(di->i_signature, OCFS2_SUPER_BLOCK_SIGNATURE,
		   म_माप(OCFS2_SUPER_BLOCK_SIGNATURE)) == 0) अणु
		/* We have to करो a raw check of the feature here */
		अगर (le32_to_cpu(di->id2.i_super.s_feature_incompat) &
		    OCFS2_FEATURE_INCOMPAT_META_ECC) अणु
			status = ocfs2_block_check_validate(bh->b_data,
							    bh->b_size,
							    &di->i_check,
							    stats);
			अगर (status)
				जाओ out;
		पूर्ण
		status = -EINVAL;
		अगर ((1 << le32_to_cpu(di->id2.i_super.s_blocksize_bits)) != blksz) अणु
			mlog(ML_ERROR, "found superblock with incorrect block "
			     "size: found %u, should be %u\n",
			     1 << le32_to_cpu(di->id2.i_super.s_blocksize_bits),
			       blksz);
		पूर्ण अन्यथा अगर (le16_to_cpu(di->id2.i_super.s_major_rev_level) !=
			   OCFS2_MAJOR_REV_LEVEL ||
			   le16_to_cpu(di->id2.i_super.s_minor_rev_level) !=
			   OCFS2_MINOR_REV_LEVEL) अणु
			mlog(ML_ERROR, "found superblock with bad version: "
			     "found %u.%u, should be %u.%u\n",
			     le16_to_cpu(di->id2.i_super.s_major_rev_level),
			     le16_to_cpu(di->id2.i_super.s_minor_rev_level),
			     OCFS2_MAJOR_REV_LEVEL,
			     OCFS2_MINOR_REV_LEVEL);
		पूर्ण अन्यथा अगर (bh->b_blocknr != le64_to_cpu(di->i_blkno)) अणु
			mlog(ML_ERROR, "bad block number on superblock: "
			     "found %llu, should be %llu\n",
			     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno),
			     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		पूर्ण अन्यथा अगर (le32_to_cpu(di->id2.i_super.s_clustersize_bits) < 12 ||
			    le32_to_cpu(di->id2.i_super.s_clustersize_bits) > 20) अणु
			mlog(ML_ERROR, "bad cluster size found: %u\n",
			     1 << le32_to_cpu(di->id2.i_super.s_clustersize_bits));
		पूर्ण अन्यथा अगर (!le64_to_cpu(di->id2.i_super.s_root_blkno)) अणु
			mlog(ML_ERROR, "bad root_blkno: 0\n");
		पूर्ण अन्यथा अगर (!le64_to_cpu(di->id2.i_super.s_प्रणाली_dir_blkno)) अणु
			mlog(ML_ERROR, "bad system_dir_blkno: 0\n");
		पूर्ण अन्यथा अगर (le16_to_cpu(di->id2.i_super.s_max_slots) > OCFS2_MAX_SLOTS) अणु
			mlog(ML_ERROR,
			     "Superblock slots found greater than file system "
			     "maximum: found %u, max %u\n",
			     le16_to_cpu(di->id2.i_super.s_max_slots),
			     OCFS2_MAX_SLOTS);
		पूर्ण अन्यथा अणु
			/* found it! */
			status = 0;
		पूर्ण
	पूर्ण

out:
	अगर (status && status != -EAGAIN)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_check_volume(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	पूर्णांक dirty;
	पूर्णांक local;
	काष्ठा ocfs2_dinode *local_alloc = शून्य; /* only used अगर we
						  * recover
						  * ourselves. */

	/* Init our journal object. */
	status = ocfs2_journal_init(osb->journal, &dirty);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "Could not initialize journal!\n");
		जाओ finally;
	पूर्ण

	/* Now that journal has been initialized, check to make sure
	   entire volume is addressable. */
	status = ocfs2_journal_addressable(osb);
	अगर (status)
		जाओ finally;

	/* If the journal was unmounted cleanly then we करोn't want to
	 * recover anything. Otherwise, journal_load will करो that
	 * dirty work क्रम us :) */
	अगर (!dirty) अणु
		status = ocfs2_journal_wipe(osb->journal, 0);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ finally;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_NOTICE "ocfs2: File system on device (%s) was not "
		       "unmounted cleanly, recovering it.\n", osb->dev_str);
	पूर्ण

	local = ocfs2_mount_local(osb);

	/* will play back anything left in the journal. */
	status = ocfs2_journal_load(osb->journal, local, dirty);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "ocfs2 journal load failed! %d\n", status);
		जाओ finally;
	पूर्ण

	अगर (osb->s_mount_opt & OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT)
		jbd2_journal_set_features(osb->journal->j_journal,
				JBD2_FEATURE_COMPAT_CHECKSUM, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	अन्यथा
		jbd2_journal_clear_features(osb->journal->j_journal,
				JBD2_FEATURE_COMPAT_CHECKSUM, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);

	अगर (dirty) अणु
		/* recover my local alloc अगर we didn't unmount cleanly. */
		status = ocfs2_begin_local_alloc_recovery(osb,
							  osb->slot_num,
							  &local_alloc);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ finally;
		पूर्ण
		/* we complete the recovery process after we've marked
		 * ourselves as mounted. */
	पूर्ण

	status = ocfs2_load_local_alloc(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ finally;
	पूर्ण

	अगर (dirty) अणु
		/* Recovery will be completed after we've mounted the
		 * rest of the volume. */
		osb->local_alloc_copy = local_alloc;
		local_alloc = शून्य;
	पूर्ण

	/* go through each journal, trylock it and अगर you get the
	 * lock, and it's marked as dirty, set the bit in the recover
	 * map and launch a recovery thपढ़ो क्रम it. */
	status = ocfs2_mark_dead_nodes(osb);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ finally;
	पूर्ण

	status = ocfs2_compute_replay_slots(osb);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

finally:
	kमुक्त(local_alloc);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * The routine माला_लो called from dismount or बंद whenever a dismount on
 * volume is requested and the osb खोलो count becomes 1.
 * It will हटाओ the osb from the global list and also मुक्त up all the
 * initialized resources and fileobject.
 */
अटल व्योम ocfs2_delete_osb(काष्ठा ocfs2_super *osb)
अणु
	/* This function assumes that the caller has the मुख्य osb resource */

	/* ocfs2_initializer_super have alपढ़ोy created this workqueue */
	अगर (osb->ocfs2_wq)
		destroy_workqueue(osb->ocfs2_wq);

	ocfs2_मुक्त_slot_info(osb);

	kमुक्त(osb->osb_orphan_wipes);
	kमुक्त(osb->slot_recovery_generations);
	/* FIXME
	 * This beदीर्घs in journal shutकरोwn, but because we have to
	 * allocate osb->journal at the start of ocfs2_initialize_osb(),
	 * we मुक्त it here.
	 */
	kमुक्त(osb->journal);
	kमुक्त(osb->local_alloc_copy);
	kमुक्त(osb->uuid_str);
	kमुक्त(osb->vol_label);
	ocfs2_put_dlm_debug(osb->osb_dlm_debug);
	स_रखो(osb, 0, माप(काष्ठा ocfs2_super));
पूर्ण

/* Depending on the mount option passed, perक्रमm one of the following:
 * Put OCFS2 पूर्णांकo a पढ़ोonly state (शेष)
 * Return EIO so that only the process errs
 * Fix the error as अगर fsck.ocfs2 -y
 * panic
 */
अटल पूर्णांक ocfs2_handle_error(काष्ठा super_block *sb)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	पूर्णांक rv = 0;

	ocfs2_set_osb_flag(osb, OCFS2_OSB_ERROR_FS);
	pr_crit("On-disk corruption discovered. "
		"Please run fsck.ocfs2 once the filesystem is unmounted.\n");

	अगर (osb->s_mount_opt & OCFS2_MOUNT_ERRORS_PANIC) अणु
		panic("OCFS2: (device %s): panic forced after error\n",
		      sb->s_id);
	पूर्ण अन्यथा अगर (osb->s_mount_opt & OCFS2_MOUNT_ERRORS_CONT) अणु
		pr_crit("OCFS2: Returning error to the calling process.\n");
		rv = -EIO;
	पूर्ण अन्यथा अणु /* शेष option */
		rv = -EROFS;
		अगर (sb_rकरोnly(sb) && (ocfs2_is_soft_पढ़ोonly(osb) || ocfs2_is_hard_पढ़ोonly(osb)))
			वापस rv;

		pr_crit("OCFS2: File system is now read-only.\n");
		sb->s_flags |= SB_RDONLY;
		ocfs2_set_ro_flag(osb, 0);
	पूर्ण

	वापस rv;
पूर्ण

पूर्णांक __ocfs2_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	/* Not using mlog here because we want to show the actual
	 * function the error came from. */
	prपूर्णांकk(KERN_CRIT "OCFS2: ERROR (device %s): %s: %pV",
	       sb->s_id, function, &vaf);

	बहु_पूर्ण(args);

	वापस ocfs2_handle_error(sb);
पूर्ण

/* Handle critical errors. This is पूर्णांकentionally more drastic than
 * ocfs2_handle_error, so we only use क्रम things like journal errors,
 * etc. */
व्योम __ocfs2_पात(काष्ठा super_block *sb, स्थिर अक्षर *function,
		   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_CRIT "OCFS2: abort (device %s): %s: %pV",
	       sb->s_id, function, &vaf);

	बहु_पूर्ण(args);

	/* We करोn't have the cluster support yet to go straight to
	 * hard पढ़ोonly in here. Until then, we want to keep
	 * ocfs2_पात() so that we can at least mark critical
	 * errors.
	 *
	 * TODO: This should पात the journal and alert other nodes
	 * that our slot needs recovery. */

	/* Force a panic(). This stinks, but it's better than letting
	 * things जारी without having a proper hard पढ़ोonly
	 * here. */
	अगर (!ocfs2_mount_local(OCFS2_SB(sb)))
		OCFS2_SB(sb)->s_mount_opt |= OCFS2_MOUNT_ERRORS_PANIC;
	ocfs2_handle_error(sb);
पूर्ण

/*
 * Void संकेत blockers, because in-kernel sigprocmask() only fails
 * when SIG_* is wrong.
 */
व्योम ocfs2_block_संकेतs(sigset_t *oldset)
अणु
	पूर्णांक rc;
	sigset_t blocked;

	sigfillset(&blocked);
	rc = sigprocmask(SIG_BLOCK, &blocked, oldset);
	BUG_ON(rc);
पूर्ण

व्योम ocfs2_unblock_संकेतs(sigset_t *oldset)
अणु
	पूर्णांक rc = sigprocmask(SIG_SETMASK, oldset, शून्य);
	BUG_ON(rc);
पूर्ण

module_init(ocfs2_init);
module_निकास(ocfs2_निकास);
