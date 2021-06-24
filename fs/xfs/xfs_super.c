<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_fsops.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_extfree_item.h"
#समावेश "xfs_mru_cache.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icreate_item.h"
#समावेश "xfs_filestream.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_sysfs.h"
#समावेश "xfs_ondisk.h"
#समावेश "xfs_rmap_item.h"
#समावेश "xfs_refcount_item.h"
#समावेश "xfs_bmap_item.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_pwork.h"

#समावेश <linux/magic.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>

अटल स्थिर काष्ठा super_operations xfs_super_operations;

अटल काष्ठा kset *xfs_kset;		/* top-level xfs sysfs dir */
#अगर_घोषित DEBUG
अटल काष्ठा xfs_kobj xfs_dbg_kobj;	/* global debug sysfs attrs */
#पूर्ण_अगर

क्रमागत xfs_dax_mode अणु
	XFS_DAX_INODE = 0,
	XFS_DAX_ALWAYS = 1,
	XFS_DAX_NEVER = 2,
पूर्ण;

अटल व्योम
xfs_mount_set_dax_mode(
	काष्ठा xfs_mount	*mp,
	क्रमागत xfs_dax_mode	mode)
अणु
	चयन (mode) अणु
	हाल XFS_DAX_INODE:
		mp->m_flags &= ~(XFS_MOUNT_DAX_ALWAYS | XFS_MOUNT_DAX_NEVER);
		अवरोध;
	हाल XFS_DAX_ALWAYS:
		mp->m_flags |= XFS_MOUNT_DAX_ALWAYS;
		mp->m_flags &= ~XFS_MOUNT_DAX_NEVER;
		अवरोध;
	हाल XFS_DAX_NEVER:
		mp->m_flags |= XFS_MOUNT_DAX_NEVER;
		mp->m_flags &= ~XFS_MOUNT_DAX_ALWAYS;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा स्थिरant_table dax_param_क्रमागतs[] = अणु
	अणु"inode",	XFS_DAX_INODE पूर्ण,
	अणु"always",	XFS_DAX_ALWAYS पूर्ण,
	अणु"never",	XFS_DAX_NEVER पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Table driven mount option parser.
 */
क्रमागत अणु
	Opt_logbufs, Opt_logbsize, Opt_logdev, Opt_rtdev,
	Opt_wsync, Opt_noalign, Opt_swalloc, Opt_sunit, Opt_swidth, Opt_nouuid,
	Opt_grpid, Opt_nogrpid, Opt_bsdgroups, Opt_sysvgroups,
	Opt_allocsize, Opt_norecovery, Opt_inode64, Opt_inode32, Opt_ikeep,
	Opt_noikeep, Opt_largeio, Opt_nolargeio, Opt_attr2, Opt_noattr2,
	Opt_filestreams, Opt_quota, Opt_noquota, Opt_usrquota, Opt_grpquota,
	Opt_prjquota, Opt_uquota, Opt_gquota, Opt_pquota,
	Opt_uqnoenक्रमce, Opt_gqnoenक्रमce, Opt_pqnoenक्रमce, Opt_qnoenक्रमce,
	Opt_discard, Opt_nodiscard, Opt_dax, Opt_dax_क्रमागत,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec xfs_fs_parameters[] = अणु
	fsparam_u32("logbufs",		Opt_logbufs),
	fsparam_string("logbsize",	Opt_logbsize),
	fsparam_string("logdev",	Opt_logdev),
	fsparam_string("rtdev",		Opt_rtdev),
	fsparam_flag("wsync",		Opt_wsync),
	fsparam_flag("noalign",		Opt_noalign),
	fsparam_flag("swalloc",		Opt_swalloc),
	fsparam_u32("sunit",		Opt_sunit),
	fsparam_u32("swidth",		Opt_swidth),
	fsparam_flag("nouuid",		Opt_nouuid),
	fsparam_flag("grpid",		Opt_grpid),
	fsparam_flag("nogrpid",		Opt_nogrpid),
	fsparam_flag("bsdgroups",	Opt_bsdgroups),
	fsparam_flag("sysvgroups",	Opt_sysvgroups),
	fsparam_string("allocsize",	Opt_allocsize),
	fsparam_flag("norecovery",	Opt_norecovery),
	fsparam_flag("inode64",		Opt_inode64),
	fsparam_flag("inode32",		Opt_inode32),
	fsparam_flag("ikeep",		Opt_ikeep),
	fsparam_flag("noikeep",		Opt_noikeep),
	fsparam_flag("largeio",		Opt_largeio),
	fsparam_flag("nolargeio",	Opt_nolargeio),
	fsparam_flag("attr2",		Opt_attr2),
	fsparam_flag("noattr2",		Opt_noattr2),
	fsparam_flag("filestreams",	Opt_filestreams),
	fsparam_flag("quota",		Opt_quota),
	fsparam_flag("noquota",		Opt_noquota),
	fsparam_flag("usrquota",	Opt_usrquota),
	fsparam_flag("grpquota",	Opt_grpquota),
	fsparam_flag("prjquota",	Opt_prjquota),
	fsparam_flag("uquota",		Opt_uquota),
	fsparam_flag("gquota",		Opt_gquota),
	fsparam_flag("pquota",		Opt_pquota),
	fsparam_flag("uqnoenforce",	Opt_uqnoenक्रमce),
	fsparam_flag("gqnoenforce",	Opt_gqnoenक्रमce),
	fsparam_flag("pqnoenforce",	Opt_pqnoenक्रमce),
	fsparam_flag("qnoenforce",	Opt_qnoenक्रमce),
	fsparam_flag("discard",		Opt_discard),
	fsparam_flag("nodiscard",	Opt_nodiscard),
	fsparam_flag("dax",		Opt_dax),
	fsparam_क्रमागत("dax",		Opt_dax_क्रमागत, dax_param_क्रमागतs),
	अणुपूर्ण
पूर्ण;

काष्ठा proc_xfs_info अणु
	uपूर्णांक64_t	flag;
	अक्षर		*str;
पूर्ण;

अटल पूर्णांक
xfs_fs_show_options(
	काष्ठा seq_file		*m,
	काष्ठा dentry		*root)
अणु
	अटल काष्ठा proc_xfs_info xfs_info_set[] = अणु
		/* the few simple ones we can get from the mount काष्ठा */
		अणु XFS_MOUNT_IKEEP,		",ikeep" पूर्ण,
		अणु XFS_MOUNT_WSYNC,		",wsync" पूर्ण,
		अणु XFS_MOUNT_NOALIGN,		",noalign" पूर्ण,
		अणु XFS_MOUNT_SWALLOC,		",swalloc" पूर्ण,
		अणु XFS_MOUNT_NOUUID,		",nouuid" पूर्ण,
		अणु XFS_MOUNT_NORECOVERY,		",norecovery" पूर्ण,
		अणु XFS_MOUNT_ATTR2,		",attr2" पूर्ण,
		अणु XFS_MOUNT_खाताSTREAMS,	",filestreams" पूर्ण,
		अणु XFS_MOUNT_GRPID,		",grpid" पूर्ण,
		अणु XFS_MOUNT_DISCARD,		",discard" पूर्ण,
		अणु XFS_MOUNT_LARGEIO,		",largeio" पूर्ण,
		अणु XFS_MOUNT_DAX_ALWAYS,		",dax=always" पूर्ण,
		अणु XFS_MOUNT_DAX_NEVER,		",dax=never" पूर्ण,
		अणु 0, शून्य पूर्ण
	पूर्ण;
	काष्ठा xfs_mount	*mp = XFS_M(root->d_sb);
	काष्ठा proc_xfs_info	*xfs_infop;

	क्रम (xfs_infop = xfs_info_set; xfs_infop->flag; xfs_infop++) अणु
		अगर (mp->m_flags & xfs_infop->flag)
			seq_माला_दो(m, xfs_infop->str);
	पूर्ण

	seq_म_लिखो(m, ",inode%d",
		(mp->m_flags & XFS_MOUNT_SMALL_INUMS) ? 32 : 64);

	अगर (mp->m_flags & XFS_MOUNT_ALLOCSIZE)
		seq_म_लिखो(m, ",allocsize=%dk",
			   (1 << mp->m_allocsize_log) >> 10);

	अगर (mp->m_logbufs > 0)
		seq_म_लिखो(m, ",logbufs=%d", mp->m_logbufs);
	अगर (mp->m_logbsize > 0)
		seq_म_लिखो(m, ",logbsize=%dk", mp->m_logbsize >> 10);

	अगर (mp->m_logname)
		seq_show_option(m, "logdev", mp->m_logname);
	अगर (mp->m_rtname)
		seq_show_option(m, "rtdev", mp->m_rtname);

	अगर (mp->m_dalign > 0)
		seq_म_लिखो(m, ",sunit=%d",
				(पूर्णांक)XFS_FSB_TO_BB(mp, mp->m_dalign));
	अगर (mp->m_swidth > 0)
		seq_म_लिखो(m, ",swidth=%d",
				(पूर्णांक)XFS_FSB_TO_BB(mp, mp->m_swidth));

	अगर (mp->m_qflags & XFS_UQUOTA_ACCT) अणु
		अगर (mp->m_qflags & XFS_UQUOTA_ENFD)
			seq_माला_दो(m, ",usrquota");
		अन्यथा
			seq_माला_दो(m, ",uqnoenforce");
	पूर्ण

	अगर (mp->m_qflags & XFS_PQUOTA_ACCT) अणु
		अगर (mp->m_qflags & XFS_PQUOTA_ENFD)
			seq_माला_दो(m, ",prjquota");
		अन्यथा
			seq_माला_दो(m, ",pqnoenforce");
	पूर्ण
	अगर (mp->m_qflags & XFS_GQUOTA_ACCT) अणु
		अगर (mp->m_qflags & XFS_GQUOTA_ENFD)
			seq_माला_दो(m, ",grpquota");
		अन्यथा
			seq_माला_दो(m, ",gqnoenforce");
	पूर्ण

	अगर (!(mp->m_qflags & XFS_ALL_QUOTA_ACCT))
		seq_माला_दो(m, ",noquota");

	वापस 0;
पूर्ण

/*
 * Set parameters क्रम inode allocation heuristics, taking पूर्णांकo account
 * fileप्रणाली size and inode32/inode64 mount options; i.e. specअगरically
 * whether or not XFS_MOUNT_SMALL_INUMS is set.
 *
 * Inode allocation patterns are altered only अगर inode32 is requested
 * (XFS_MOUNT_SMALL_INUMS), and the fileप्रणाली is sufficiently large.
 * If altered, XFS_MOUNT_32BITINODES is set as well.
 *
 * An agcount independent of that in the mount काष्ठाure is provided
 * because in the growfs हाल, mp->m_sb.sb_agcount is not yet updated
 * to the potentially higher ag count.
 *
 * Returns the maximum AG index which may contain inodes.
 */
xfs_agnumber_t
xfs_set_inode_alloc(
	काष्ठा xfs_mount *mp,
	xfs_agnumber_t	agcount)
अणु
	xfs_agnumber_t	index;
	xfs_agnumber_t	maxagi = 0;
	xfs_sb_t	*sbp = &mp->m_sb;
	xfs_agnumber_t	max_metadata;
	xfs_agino_t	agino;
	xfs_ino_t	ino;

	/*
	 * Calculate how much should be reserved क्रम inodes to meet
	 * the max inode percentage.  Used only क्रम inode32.
	 */
	अगर (M_IGEO(mp)->maxicount) अणु
		uपूर्णांक64_t	icount;

		icount = sbp->sb_dblocks * sbp->sb_imax_pct;
		करो_भाग(icount, 100);
		icount += sbp->sb_agblocks - 1;
		करो_भाग(icount, sbp->sb_agblocks);
		max_metadata = icount;
	पूर्ण अन्यथा अणु
		max_metadata = agcount;
	पूर्ण

	/* Get the last possible inode in the fileप्रणाली */
	agino =	XFS_AGB_TO_AGINO(mp, sbp->sb_agblocks - 1);
	ino = XFS_AGINO_TO_INO(mp, agcount - 1, agino);

	/*
	 * If user asked क्रम no more than 32-bit inodes, and the fs is
	 * sufficiently large, set XFS_MOUNT_32BITINODES अगर we must alter
	 * the allocator to accommodate the request.
	 */
	अगर ((mp->m_flags & XFS_MOUNT_SMALL_INUMS) && ino > XFS_MAXINUMBER_32)
		mp->m_flags |= XFS_MOUNT_32BITINODES;
	अन्यथा
		mp->m_flags &= ~XFS_MOUNT_32BITINODES;

	क्रम (index = 0; index < agcount; index++) अणु
		काष्ठा xfs_perag	*pag;

		ino = XFS_AGINO_TO_INO(mp, index, agino);

		pag = xfs_perag_get(mp, index);

		अगर (mp->m_flags & XFS_MOUNT_32BITINODES) अणु
			अगर (ino > XFS_MAXINUMBER_32) अणु
				pag->pagi_inodeok = 0;
				pag->pagf_metadata = 0;
			पूर्ण अन्यथा अणु
				pag->pagi_inodeok = 1;
				maxagi++;
				अगर (index < max_metadata)
					pag->pagf_metadata = 1;
				अन्यथा
					pag->pagf_metadata = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			pag->pagi_inodeok = 1;
			pag->pagf_metadata = 0;
		पूर्ण

		xfs_perag_put(pag);
	पूर्ण

	वापस (mp->m_flags & XFS_MOUNT_32BITINODES) ? maxagi : agcount;
पूर्ण

STATIC पूर्णांक
xfs_blkdev_get(
	xfs_mount_t		*mp,
	स्थिर अक्षर		*name,
	काष्ठा block_device	**bdevp)
अणु
	पूर्णांक			error = 0;

	*bdevp = blkdev_get_by_path(name, FMODE_READ|FMODE_WRITE|FMODE_EXCL,
				    mp);
	अगर (IS_ERR(*bdevp)) अणु
		error = PTR_ERR(*bdevp);
		xfs_warn(mp, "Invalid device [%s], error=%d", name, error);
	पूर्ण

	वापस error;
पूर्ण

STATIC व्योम
xfs_blkdev_put(
	काष्ठा block_device	*bdev)
अणु
	अगर (bdev)
		blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
पूर्ण

व्योम
xfs_blkdev_issue_flush(
	xfs_buftarg_t		*buftarg)
अणु
	blkdev_issue_flush(buftarg->bt_bdev);
पूर्ण

STATIC व्योम
xfs_बंद_devices(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा dax_device *dax_ddev = mp->m_ddev_targp->bt_daxdev;

	अगर (mp->m_logdev_targp && mp->m_logdev_targp != mp->m_ddev_targp) अणु
		काष्ठा block_device *logdev = mp->m_logdev_targp->bt_bdev;
		काष्ठा dax_device *dax_logdev = mp->m_logdev_targp->bt_daxdev;

		xfs_मुक्त_buftarg(mp->m_logdev_targp);
		xfs_blkdev_put(logdev);
		fs_put_dax(dax_logdev);
	पूर्ण
	अगर (mp->m_rtdev_targp) अणु
		काष्ठा block_device *rtdev = mp->m_rtdev_targp->bt_bdev;
		काष्ठा dax_device *dax_rtdev = mp->m_rtdev_targp->bt_daxdev;

		xfs_मुक्त_buftarg(mp->m_rtdev_targp);
		xfs_blkdev_put(rtdev);
		fs_put_dax(dax_rtdev);
	पूर्ण
	xfs_मुक्त_buftarg(mp->m_ddev_targp);
	fs_put_dax(dax_ddev);
पूर्ण

/*
 * The file प्रणाली configurations are:
 *	(1) device (partition) with data and पूर्णांकernal log
 *	(2) logical volume with data and log subvolumes.
 *	(3) logical volume with data, log, and realसमय subvolumes.
 *
 * We only have to handle खोलोing the log and realसमय volumes here अगर
 * they are present.  The data subvolume has alपढ़ोy been खोलोed by
 * get_sb_bdev() and is stored in sb->s_bdev.
 */
STATIC पूर्णांक
xfs_खोलो_devices(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा block_device	*ddev = mp->m_super->s_bdev;
	काष्ठा dax_device	*dax_ddev = fs_dax_get_by_bdev(ddev);
	काष्ठा dax_device	*dax_logdev = शून्य, *dax_rtdev = शून्य;
	काष्ठा block_device	*logdev = शून्य, *rtdev = शून्य;
	पूर्णांक			error;

	/*
	 * Open real समय and log devices - order is important.
	 */
	अगर (mp->m_logname) अणु
		error = xfs_blkdev_get(mp, mp->m_logname, &logdev);
		अगर (error)
			जाओ out;
		dax_logdev = fs_dax_get_by_bdev(logdev);
	पूर्ण

	अगर (mp->m_rtname) अणु
		error = xfs_blkdev_get(mp, mp->m_rtname, &rtdev);
		अगर (error)
			जाओ out_बंद_logdev;

		अगर (rtdev == ddev || rtdev == logdev) अणु
			xfs_warn(mp,
	"Cannot mount filesystem with identical rtdev and ddev/logdev.");
			error = -EINVAL;
			जाओ out_बंद_rtdev;
		पूर्ण
		dax_rtdev = fs_dax_get_by_bdev(rtdev);
	पूर्ण

	/*
	 * Setup xfs_mount buffer target poपूर्णांकers
	 */
	error = -ENOMEM;
	mp->m_ddev_targp = xfs_alloc_buftarg(mp, ddev, dax_ddev);
	अगर (!mp->m_ddev_targp)
		जाओ out_बंद_rtdev;

	अगर (rtdev) अणु
		mp->m_rtdev_targp = xfs_alloc_buftarg(mp, rtdev, dax_rtdev);
		अगर (!mp->m_rtdev_targp)
			जाओ out_मुक्त_ddev_targ;
	पूर्ण

	अगर (logdev && logdev != ddev) अणु
		mp->m_logdev_targp = xfs_alloc_buftarg(mp, logdev, dax_logdev);
		अगर (!mp->m_logdev_targp)
			जाओ out_मुक्त_rtdev_targ;
	पूर्ण अन्यथा अणु
		mp->m_logdev_targp = mp->m_ddev_targp;
	पूर्ण

	वापस 0;

 out_मुक्त_rtdev_targ:
	अगर (mp->m_rtdev_targp)
		xfs_मुक्त_buftarg(mp->m_rtdev_targp);
 out_मुक्त_ddev_targ:
	xfs_मुक्त_buftarg(mp->m_ddev_targp);
 out_बंद_rtdev:
	xfs_blkdev_put(rtdev);
	fs_put_dax(dax_rtdev);
 out_बंद_logdev:
	अगर (logdev && logdev != ddev) अणु
		xfs_blkdev_put(logdev);
		fs_put_dax(dax_logdev);
	पूर्ण
 out:
	fs_put_dax(dax_ddev);
	वापस error;
पूर्ण

/*
 * Setup xfs_mount buffer target poपूर्णांकers based on superblock
 */
STATIC पूर्णांक
xfs_setup_devices(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			error;

	error = xfs_setsize_buftarg(mp->m_ddev_targp, mp->m_sb.sb_sectsize);
	अगर (error)
		वापस error;

	अगर (mp->m_logdev_targp && mp->m_logdev_targp != mp->m_ddev_targp) अणु
		अचिन्हित पूर्णांक	log_sector_size = BBSIZE;

		अगर (xfs_sb_version_hassector(&mp->m_sb))
			log_sector_size = mp->m_sb.sb_logsectsize;
		error = xfs_setsize_buftarg(mp->m_logdev_targp,
					    log_sector_size);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (mp->m_rtdev_targp) अणु
		error = xfs_setsize_buftarg(mp->m_rtdev_targp,
					    mp->m_sb.sb_sectsize);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_init_mount_workqueues(
	काष्ठा xfs_mount	*mp)
अणु
	mp->m_buf_workqueue = alloc_workqueue("xfs-buf/%s",
			XFS_WQFLAGS(WQ_FREEZABLE | WQ_MEM_RECLAIM),
			1, mp->m_super->s_id);
	अगर (!mp->m_buf_workqueue)
		जाओ out;

	mp->m_unwritten_workqueue = alloc_workqueue("xfs-conv/%s",
			XFS_WQFLAGS(WQ_FREEZABLE | WQ_MEM_RECLAIM),
			0, mp->m_super->s_id);
	अगर (!mp->m_unwritten_workqueue)
		जाओ out_destroy_buf;

	mp->m_cil_workqueue = alloc_workqueue("xfs-cil/%s",
			XFS_WQFLAGS(WQ_FREEZABLE | WQ_MEM_RECLAIM | WQ_UNBOUND),
			0, mp->m_super->s_id);
	अगर (!mp->m_cil_workqueue)
		जाओ out_destroy_unwritten;

	mp->m_reclaim_workqueue = alloc_workqueue("xfs-reclaim/%s",
			XFS_WQFLAGS(WQ_FREEZABLE | WQ_MEM_RECLAIM),
			0, mp->m_super->s_id);
	अगर (!mp->m_reclaim_workqueue)
		जाओ out_destroy_cil;

	mp->m_gc_workqueue = alloc_workqueue("xfs-gc/%s",
			WQ_SYSFS | WQ_UNBOUND | WQ_FREEZABLE | WQ_MEM_RECLAIM,
			0, mp->m_super->s_id);
	अगर (!mp->m_gc_workqueue)
		जाओ out_destroy_reclaim;

	mp->m_sync_workqueue = alloc_workqueue("xfs-sync/%s",
			XFS_WQFLAGS(WQ_FREEZABLE), 0, mp->m_super->s_id);
	अगर (!mp->m_sync_workqueue)
		जाओ out_destroy_eofb;

	वापस 0;

out_destroy_eofb:
	destroy_workqueue(mp->m_gc_workqueue);
out_destroy_reclaim:
	destroy_workqueue(mp->m_reclaim_workqueue);
out_destroy_cil:
	destroy_workqueue(mp->m_cil_workqueue);
out_destroy_unwritten:
	destroy_workqueue(mp->m_unwritten_workqueue);
out_destroy_buf:
	destroy_workqueue(mp->m_buf_workqueue);
out:
	वापस -ENOMEM;
पूर्ण

STATIC व्योम
xfs_destroy_mount_workqueues(
	काष्ठा xfs_mount	*mp)
अणु
	destroy_workqueue(mp->m_sync_workqueue);
	destroy_workqueue(mp->m_gc_workqueue);
	destroy_workqueue(mp->m_reclaim_workqueue);
	destroy_workqueue(mp->m_cil_workqueue);
	destroy_workqueue(mp->m_unwritten_workqueue);
	destroy_workqueue(mp->m_buf_workqueue);
पूर्ण

अटल व्योम
xfs_flush_inodes_worker(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_mount	*mp = container_of(work, काष्ठा xfs_mount,
						   m_flush_inodes_work);
	काष्ठा super_block	*sb = mp->m_super;

	अगर (करोwn_पढ़ो_trylock(&sb->s_umount)) अणु
		sync_inodes_sb(sb);
		up_पढ़ो(&sb->s_umount);
	पूर्ण
पूर्ण

/*
 * Flush all dirty data to disk. Must not be called जबतक holding an XFS_ILOCK
 * or a page lock. We use sync_inodes_sb() here to ensure we block जबतक रुकोing
 * क्रम IO to complete so that we effectively throttle multiple callers to the
 * rate at which IO is completing.
 */
व्योम
xfs_flush_inodes(
	काष्ठा xfs_mount	*mp)
अणु
	/*
	 * If flush_work() वापसs true then that means we रुकोed क्रम a flush
	 * which was alपढ़ोy in progress.  Don't bother running another scan.
	 */
	अगर (flush_work(&mp->m_flush_inodes_work))
		वापस;

	queue_work(mp->m_sync_workqueue, &mp->m_flush_inodes_work);
	flush_work(&mp->m_flush_inodes_work);
पूर्ण

/* Catch misguided souls that try to use this पूर्णांकerface on XFS */
STATIC काष्ठा inode *
xfs_fs_alloc_inode(
	काष्ठा super_block	*sb)
अणु
	BUG();
	वापस शून्य;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम
xfs_check_delalloc(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_iext_cursor	icur;

	अगर (!अगरp || !xfs_iext_lookup_extent(ip, अगरp, 0, &icur, &got))
		वापस;
	करो अणु
		अगर (isnullstartblock(got.br_startblock)) अणु
			xfs_warn(ip->i_mount,
	"ino %llx %s fork has delalloc extent at [0x%llx:0x%llx]",
				ip->i_ino,
				whichविभाजन == XFS_DATA_FORK ? "data" : "cow",
				got.br_startoff, got.br_blockcount);
		पूर्ण
	पूर्ण जबतक (xfs_iext_next_extent(अगरp, &icur, &got));
पूर्ण
#अन्यथा
#घोषणा xfs_check_delalloc(ip, whichविभाजन)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Now that the generic code is guaranteed not to be accessing
 * the linux inode, we can inactivate and reclaim the inode.
 */
STATIC व्योम
xfs_fs_destroy_inode(
	काष्ठा inode		*inode)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);

	trace_xfs_destroy_inode(ip);

	ASSERT(!rwsem_is_locked(&inode->i_rwsem));
	XFS_STATS_INC(ip->i_mount, vn_rele);
	XFS_STATS_INC(ip->i_mount, vn_हटाओ);

	xfs_inactive(ip);

	अगर (!XFS_FORCED_SHUTDOWN(ip->i_mount) && ip->i_delayed_blks) अणु
		xfs_check_delalloc(ip, XFS_DATA_FORK);
		xfs_check_delalloc(ip, XFS_COW_FORK);
		ASSERT(0);
	पूर्ण

	XFS_STATS_INC(ip->i_mount, vn_reclaim);

	/*
	 * We should never get here with one of the reclaim flags alपढ़ोy set.
	 */
	ASSERT_ALWAYS(!xfs_अगरlags_test(ip, XFS_IRECLAIMABLE));
	ASSERT_ALWAYS(!xfs_अगरlags_test(ip, XFS_IRECLAIM));

	/*
	 * We always use background reclaim here because even अगर the inode is
	 * clean, it still may be under IO and hence we have रुको क्रम IO
	 * completion to occur beक्रमe we can reclaim the inode. The background
	 * reclaim path handles this more efficiently than we can here, so
	 * simply let background reclaim tear करोwn all inodes.
	 */
	xfs_inode_set_reclaim_tag(ip);
पूर्ण

अटल व्योम
xfs_fs_dirty_inode(
	काष्ठा inode			*inode,
	पूर्णांक				flag)
अणु
	काष्ठा xfs_inode		*ip = XFS_I(inode);
	काष्ठा xfs_mount		*mp = ip->i_mount;
	काष्ठा xfs_trans		*tp;

	अगर (!(inode->i_sb->s_flags & SB_LAZYTIME))
		वापस;
	अगर (flag != I_सूचीTY_SYNC || !(inode->i_state & I_सूचीTY_TIME))
		वापस;

	अगर (xfs_trans_alloc(mp, &M_RES(mp)->tr_fsyncts, 0, 0, 0, &tp))
		वापस;
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_TIMESTAMP);
	xfs_trans_commit(tp);
पूर्ण

/*
 * Slab object creation initialisation क्रम the XFS inode.
 * This covers only the idempotent fields in the XFS inode;
 * all other fields need to be initialised on allocation
 * from the slab. This aव्योमs the need to repeatedly initialise
 * fields in the xfs inode that left in the initialise state
 * when मुक्तing the inode.
 */
STATIC व्योम
xfs_fs_inode_init_once(
	व्योम			*inode)
अणु
	काष्ठा xfs_inode	*ip = inode;

	स_रखो(ip, 0, माप(काष्ठा xfs_inode));

	/* vfs inode */
	inode_init_once(VFS_I(ip));

	/* xfs inode */
	atomic_set(&ip->i_pincount, 0);
	spin_lock_init(&ip->i_flags_lock);

	mrlock_init(&ip->i_mmaplock, MRLOCK_ALLOW_EQUAL_PRI|MRLOCK_BARRIER,
		     "xfsino", ip->i_ino);
	mrlock_init(&ip->i_lock, MRLOCK_ALLOW_EQUAL_PRI|MRLOCK_BARRIER,
		     "xfsino", ip->i_ino);
पूर्ण

/*
 * We करो an unlocked check क्रम XFS_IDONTCACHE here because we are alपढ़ोy
 * serialised against cache hits here via the inode->i_lock and igrab() in
 * xfs_iget_cache_hit(). Hence a lookup that might clear this flag will not be
 * racing with us, and it aव्योमs needing to grab a spinlock here क्रम every inode
 * we drop the final reference on.
 */
STATIC पूर्णांक
xfs_fs_drop_inode(
	काष्ठा inode		*inode)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);

	/*
	 * If this unlinked inode is in the middle of recovery, करोn't
	 * drop the inode just yet; log recovery will take care of
	 * that.  See the comment क्रम this inode flag.
	 */
	अगर (ip->i_flags & XFS_IRECOVERY) अणु
		ASSERT(ip->i_mount->m_log->l_flags & XLOG_RECOVERY_NEEDED);
		वापस 0;
	पूर्ण

	वापस generic_drop_inode(inode);
पूर्ण

अटल व्योम
xfs_mount_मुक्त(
	काष्ठा xfs_mount	*mp)
अणु
	kमुक्त(mp->m_rtname);
	kमुक्त(mp->m_logname);
	kmem_मुक्त(mp);
पूर्ण

STATIC पूर्णांक
xfs_fs_sync_fs(
	काष्ठा super_block	*sb,
	पूर्णांक			रुको)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	/*
	 * Doing anything during the async pass would be counterproductive.
	 */
	अगर (!रुको)
		वापस 0;

	xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	अगर (laptop_mode) अणु
		/*
		 * The disk must be active because we're syncing.
		 * We schedule log work now (now that the disk is
		 * active) instead of later (when it might not be).
		 */
		flush_delayed_work(&mp->m_log->l_work);
	पूर्ण

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_fs_statfs(
	काष्ठा dentry		*dentry,
	काष्ठा kstatfs		*statp)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(dentry->d_sb);
	xfs_sb_t		*sbp = &mp->m_sb;
	काष्ठा xfs_inode	*ip = XFS_I(d_inode(dentry));
	uपूर्णांक64_t		fakeinos, id;
	uपूर्णांक64_t		icount;
	uपूर्णांक64_t		अगरree;
	uपूर्णांक64_t		fdblocks;
	xfs_extlen_t		lsize;
	पूर्णांक64_t			fमुक्त;

	statp->f_type = XFS_SUPER_MAGIC;
	statp->f_namelen = MAXNAMELEN - 1;

	id = huge_encode_dev(mp->m_ddev_targp->bt_dev);
	statp->f_fsid = u64_to_fsid(id);

	icount = percpu_counter_sum(&mp->m_icount);
	अगरree = percpu_counter_sum(&mp->m_अगरree);
	fdblocks = percpu_counter_sum(&mp->m_fdblocks);

	spin_lock(&mp->m_sb_lock);
	statp->f_bsize = sbp->sb_blocksize;
	lsize = sbp->sb_logstart ? sbp->sb_logblocks : 0;
	statp->f_blocks = sbp->sb_dblocks - lsize;
	spin_unlock(&mp->m_sb_lock);

	/* make sure statp->f_bमुक्त करोes not underflow */
	statp->f_bमुक्त = max_t(पूर्णांक64_t, fdblocks - mp->m_alloc_set_aside, 0);
	statp->f_bavail = statp->f_bमुक्त;

	fakeinos = XFS_FSB_TO_INO(mp, statp->f_bमुक्त);
	statp->f_files = min(icount + fakeinos, (uपूर्णांक64_t)XFS_MAXINUMBER);
	अगर (M_IGEO(mp)->maxicount)
		statp->f_files = min_t(typeof(statp->f_files),
					statp->f_files,
					M_IGEO(mp)->maxicount);

	/* If sb_icount overshot maxicount, report actual allocation */
	statp->f_files = max_t(typeof(statp->f_files),
					statp->f_files,
					sbp->sb_icount);

	/* make sure statp->f_fमुक्त करोes not underflow */
	fमुक्त = statp->f_files - (icount - अगरree);
	statp->f_fमुक्त = max_t(पूर्णांक64_t, fमुक्त, 0);


	अगर ((ip->i_dअगरlags & XFS_DIFLAG_PROJINHERIT) &&
	    ((mp->m_qflags & (XFS_PQUOTA_ACCT|XFS_PQUOTA_ENFD))) ==
			      (XFS_PQUOTA_ACCT|XFS_PQUOTA_ENFD))
		xfs_qm_statvfs(ip, statp);

	अगर (XFS_IS_REALTIME_MOUNT(mp) &&
	    (ip->i_dअगरlags & (XFS_DIFLAG_RTINHERIT | XFS_DIFLAG_REALTIME))) अणु
		statp->f_blocks = sbp->sb_rblocks;
		statp->f_bavail = statp->f_bमुक्त =
			sbp->sb_frextents * sbp->sb_rextsize;
	पूर्ण

	वापस 0;
पूर्ण

STATIC व्योम
xfs_save_resvblks(काष्ठा xfs_mount *mp)
अणु
	uपूर्णांक64_t resblks = 0;

	mp->m_resblks_save = mp->m_resblks;
	xfs_reserve_blocks(mp, &resblks, शून्य);
पूर्ण

STATIC व्योम
xfs_restore_resvblks(काष्ठा xfs_mount *mp)
अणु
	uपूर्णांक64_t resblks;

	अगर (mp->m_resblks_save) अणु
		resblks = mp->m_resblks_save;
		mp->m_resblks_save = 0;
	पूर्ण अन्यथा
		resblks = xfs_शेष_resblks(mp);

	xfs_reserve_blocks(mp, &resblks, शून्य);
पूर्ण

/*
 * Second stage of a मुक्तze. The data is alपढ़ोy frozen so we only
 * need to take care of the metadata. Once that's करोne sync the superblock
 * to the log to dirty it in हाल of a crash जबतक frozen. This ensures that we
 * will recover the unlinked inode lists on the next mount.
 */
STATIC पूर्णांक
xfs_fs_मुक्तze(
	काष्ठा super_block	*sb)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);
	अचिन्हित पूर्णांक		flags;
	पूर्णांक			ret;

	/*
	 * The fileप्रणाली is now frozen far enough that memory reclaim
	 * cannot safely operate on the fileप्रणाली. Hence we need to
	 * set a GFP_NOFS context here to aव्योम recursion deadlocks.
	 */
	flags = meदो_स्मृति_nofs_save();
	xfs_blockgc_stop(mp);
	xfs_save_resvblks(mp);
	ret = xfs_log_quiesce(mp);
	meदो_स्मृति_nofs_restore(flags);
	वापस ret;
पूर्ण

STATIC पूर्णांक
xfs_fs_unमुक्तze(
	काष्ठा super_block	*sb)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	xfs_restore_resvblks(mp);
	xfs_log_work_queue(mp);
	xfs_blockgc_start(mp);
	वापस 0;
पूर्ण

/*
 * This function fills in xfs_mount_t fields based on mount args.
 * Note: the superblock _has_ now been पढ़ो in.
 */
STATIC पूर्णांक
xfs_finish_flags(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			ronly = (mp->m_flags & XFS_MOUNT_RDONLY);

	/* Fail a mount where the logbuf is smaller than the log stripe */
	अगर (xfs_sb_version_haslogv2(&mp->m_sb)) अणु
		अगर (mp->m_logbsize <= 0 &&
		    mp->m_sb.sb_logsunit > XLOG_BIG_RECORD_BSIZE) अणु
			mp->m_logbsize = mp->m_sb.sb_logsunit;
		पूर्ण अन्यथा अगर (mp->m_logbsize > 0 &&
			   mp->m_logbsize < mp->m_sb.sb_logsunit) अणु
			xfs_warn(mp,
		"logbuf size must be greater than or equal to log stripe size");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fail a mount अगर the logbuf is larger than 32K */
		अगर (mp->m_logbsize > XLOG_BIG_RECORD_BSIZE) अणु
			xfs_warn(mp,
		"logbuf size for version 1 logs must be 16K or 32K");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * V5 fileप्रणालीs always use attr2 क्रमmat क्रम attributes.
	 */
	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    (mp->m_flags & XFS_MOUNT_NOATTR2)) अणु
		xfs_warn(mp, "Cannot mount a V5 filesystem as noattr2. "
			     "attr2 is always enabled for V5 filesystems.");
		वापस -EINVAL;
	पूर्ण

	/*
	 * mkfs'ed attr2 will turn on attr2 mount unless explicitly
	 * told by noattr2 to turn it off
	 */
	अगर (xfs_sb_version_hasattr2(&mp->m_sb) &&
	    !(mp->m_flags & XFS_MOUNT_NOATTR2))
		mp->m_flags |= XFS_MOUNT_ATTR2;

	/*
	 * prohibit r/w mounts of पढ़ो-only fileप्रणालीs
	 */
	अगर ((mp->m_sb.sb_flags & XFS_SBF_READONLY) && !ronly) अणु
		xfs_warn(mp,
			"cannot mount a read-only filesystem as read-write");
		वापस -EROFS;
	पूर्ण

	अगर ((mp->m_qflags & (XFS_GQUOTA_ACCT | XFS_GQUOTA_ACTIVE)) &&
	    (mp->m_qflags & (XFS_PQUOTA_ACCT | XFS_PQUOTA_ACTIVE)) &&
	    !xfs_sb_version_has_pquotino(&mp->m_sb)) अणु
		xfs_warn(mp,
		  "Super block does not support project and group quota together");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_init_percpu_counters(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक		error;

	error = percpu_counter_init(&mp->m_icount, 0, GFP_KERNEL);
	अगर (error)
		वापस -ENOMEM;

	error = percpu_counter_init(&mp->m_अगरree, 0, GFP_KERNEL);
	अगर (error)
		जाओ मुक्त_icount;

	error = percpu_counter_init(&mp->m_fdblocks, 0, GFP_KERNEL);
	अगर (error)
		जाओ मुक्त_अगरree;

	error = percpu_counter_init(&mp->m_delalloc_blks, 0, GFP_KERNEL);
	अगर (error)
		जाओ मुक्त_fdblocks;

	वापस 0;

मुक्त_fdblocks:
	percpu_counter_destroy(&mp->m_fdblocks);
मुक्त_अगरree:
	percpu_counter_destroy(&mp->m_अगरree);
मुक्त_icount:
	percpu_counter_destroy(&mp->m_icount);
	वापस -ENOMEM;
पूर्ण

व्योम
xfs_reinit_percpu_counters(
	काष्ठा xfs_mount	*mp)
अणु
	percpu_counter_set(&mp->m_icount, mp->m_sb.sb_icount);
	percpu_counter_set(&mp->m_अगरree, mp->m_sb.sb_अगरree);
	percpu_counter_set(&mp->m_fdblocks, mp->m_sb.sb_fdblocks);
पूर्ण

अटल व्योम
xfs_destroy_percpu_counters(
	काष्ठा xfs_mount	*mp)
अणु
	percpu_counter_destroy(&mp->m_icount);
	percpu_counter_destroy(&mp->m_अगरree);
	percpu_counter_destroy(&mp->m_fdblocks);
	ASSERT(XFS_FORCED_SHUTDOWN(mp) ||
	       percpu_counter_sum(&mp->m_delalloc_blks) == 0);
	percpu_counter_destroy(&mp->m_delalloc_blks);
पूर्ण

अटल व्योम
xfs_fs_put_super(
	काष्ठा super_block	*sb)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	/* अगर ->fill_super failed, we have no mount to tear करोwn */
	अगर (!sb->s_fs_info)
		वापस;

	xfs_notice(mp, "Unmounting Filesystem");
	xfs_filestream_unmount(mp);
	xfs_unmountfs(mp);

	xfs_मुक्तsb(mp);
	मुक्त_percpu(mp->m_stats.xs_stats);
	xfs_destroy_percpu_counters(mp);
	xfs_destroy_mount_workqueues(mp);
	xfs_बंद_devices(mp);

	sb->s_fs_info = शून्य;
	xfs_mount_मुक्त(mp);
पूर्ण

अटल दीर्घ
xfs_fs_nr_cached_objects(
	काष्ठा super_block	*sb,
	काष्ठा shrink_control	*sc)
अणु
	/* Paranoia: catch incorrect calls during mount setup or tearकरोwn */
	अगर (WARN_ON_ONCE(!sb->s_fs_info))
		वापस 0;
	वापस xfs_reclaim_inodes_count(XFS_M(sb));
पूर्ण

अटल दीर्घ
xfs_fs_मुक्त_cached_objects(
	काष्ठा super_block	*sb,
	काष्ठा shrink_control	*sc)
अणु
	वापस xfs_reclaim_inodes_nr(XFS_M(sb), sc->nr_to_scan);
पूर्ण

अटल स्थिर काष्ठा super_operations xfs_super_operations = अणु
	.alloc_inode		= xfs_fs_alloc_inode,
	.destroy_inode		= xfs_fs_destroy_inode,
	.dirty_inode		= xfs_fs_dirty_inode,
	.drop_inode		= xfs_fs_drop_inode,
	.put_super		= xfs_fs_put_super,
	.sync_fs		= xfs_fs_sync_fs,
	.मुक्तze_fs		= xfs_fs_मुक्तze,
	.unमुक्तze_fs		= xfs_fs_unमुक्तze,
	.statfs			= xfs_fs_statfs,
	.show_options		= xfs_fs_show_options,
	.nr_cached_objects	= xfs_fs_nr_cached_objects,
	.मुक्त_cached_objects	= xfs_fs_मुक्त_cached_objects,
पूर्ण;

अटल पूर्णांक
suffix_kstrtoपूर्णांक(
	स्थिर अक्षर	*s,
	अचिन्हित पूर्णांक	base,
	पूर्णांक		*res)
अणु
	पूर्णांक		last, shअगरt_left_factor = 0, _res;
	अक्षर		*value;
	पूर्णांक		ret = 0;

	value = kstrdup(s, GFP_KERNEL);
	अगर (!value)
		वापस -ENOMEM;

	last = म_माप(value) - 1;
	अगर (value[last] == 'K' || value[last] == 'k') अणु
		shअगरt_left_factor = 10;
		value[last] = '\0';
	पूर्ण
	अगर (value[last] == 'M' || value[last] == 'm') अणु
		shअगरt_left_factor = 20;
		value[last] = '\0';
	पूर्ण
	अगर (value[last] == 'G' || value[last] == 'g') अणु
		shअगरt_left_factor = 30;
		value[last] = '\0';
	पूर्ण

	अगर (kstrtoपूर्णांक(value, base, &_res))
		ret = -EINVAL;
	kमुक्त(value);
	*res = _res << shअगरt_left_factor;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
xfs_fs_warn_deprecated(
	काष्ठा fs_context	*fc,
	काष्ठा fs_parameter	*param,
	uपूर्णांक64_t		flag,
	bool			value)
अणु
	/* Don't prपूर्णांक the warning अगर reconfiguring and current mount poपूर्णांक
	 * alपढ़ोy had the flag set
	 */
	अगर ((fc->purpose & FS_CONTEXT_FOR_RECONFIGURE) &&
			!!(XFS_M(fc->root->d_sb)->m_flags & flag) == value)
		वापस;
	xfs_warn(fc->s_fs_info, "%s mount option is deprecated.", param->key);
पूर्ण

/*
 * Set mount state from a mount option.
 *
 * NOTE: mp->m_super is शून्य here!
 */
अटल पूर्णांक
xfs_fs_parse_param(
	काष्ठा fs_context	*fc,
	काष्ठा fs_parameter	*param)
अणु
	काष्ठा xfs_mount	*parsing_mp = fc->s_fs_info;
	काष्ठा fs_parse_result	result;
	पूर्णांक			size = 0;
	पूर्णांक			opt;

	opt = fs_parse(fc, xfs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_logbufs:
		parsing_mp->m_logbufs = result.uपूर्णांक_32;
		वापस 0;
	हाल Opt_logbsize:
		अगर (suffix_kstrtoपूर्णांक(param->string, 10, &parsing_mp->m_logbsize))
			वापस -EINVAL;
		वापस 0;
	हाल Opt_logdev:
		kमुक्त(parsing_mp->m_logname);
		parsing_mp->m_logname = kstrdup(param->string, GFP_KERNEL);
		अगर (!parsing_mp->m_logname)
			वापस -ENOMEM;
		वापस 0;
	हाल Opt_rtdev:
		kमुक्त(parsing_mp->m_rtname);
		parsing_mp->m_rtname = kstrdup(param->string, GFP_KERNEL);
		अगर (!parsing_mp->m_rtname)
			वापस -ENOMEM;
		वापस 0;
	हाल Opt_allocsize:
		अगर (suffix_kstrtoपूर्णांक(param->string, 10, &size))
			वापस -EINVAL;
		parsing_mp->m_allocsize_log = ffs(size) - 1;
		parsing_mp->m_flags |= XFS_MOUNT_ALLOCSIZE;
		वापस 0;
	हाल Opt_grpid:
	हाल Opt_bsdgroups:
		parsing_mp->m_flags |= XFS_MOUNT_GRPID;
		वापस 0;
	हाल Opt_nogrpid:
	हाल Opt_sysvgroups:
		parsing_mp->m_flags &= ~XFS_MOUNT_GRPID;
		वापस 0;
	हाल Opt_wsync:
		parsing_mp->m_flags |= XFS_MOUNT_WSYNC;
		वापस 0;
	हाल Opt_norecovery:
		parsing_mp->m_flags |= XFS_MOUNT_NORECOVERY;
		वापस 0;
	हाल Opt_noalign:
		parsing_mp->m_flags |= XFS_MOUNT_NOALIGN;
		वापस 0;
	हाल Opt_swalloc:
		parsing_mp->m_flags |= XFS_MOUNT_SWALLOC;
		वापस 0;
	हाल Opt_sunit:
		parsing_mp->m_dalign = result.uपूर्णांक_32;
		वापस 0;
	हाल Opt_swidth:
		parsing_mp->m_swidth = result.uपूर्णांक_32;
		वापस 0;
	हाल Opt_inode32:
		parsing_mp->m_flags |= XFS_MOUNT_SMALL_INUMS;
		वापस 0;
	हाल Opt_inode64:
		parsing_mp->m_flags &= ~XFS_MOUNT_SMALL_INUMS;
		वापस 0;
	हाल Opt_nouuid:
		parsing_mp->m_flags |= XFS_MOUNT_NOUUID;
		वापस 0;
	हाल Opt_largeio:
		parsing_mp->m_flags |= XFS_MOUNT_LARGEIO;
		वापस 0;
	हाल Opt_nolargeio:
		parsing_mp->m_flags &= ~XFS_MOUNT_LARGEIO;
		वापस 0;
	हाल Opt_filestreams:
		parsing_mp->m_flags |= XFS_MOUNT_खाताSTREAMS;
		वापस 0;
	हाल Opt_noquota:
		parsing_mp->m_qflags &= ~XFS_ALL_QUOTA_ACCT;
		parsing_mp->m_qflags &= ~XFS_ALL_QUOTA_ENFD;
		parsing_mp->m_qflags &= ~XFS_ALL_QUOTA_ACTIVE;
		वापस 0;
	हाल Opt_quota:
	हाल Opt_uquota:
	हाल Opt_usrquota:
		parsing_mp->m_qflags |= (XFS_UQUOTA_ACCT | XFS_UQUOTA_ACTIVE |
				 XFS_UQUOTA_ENFD);
		वापस 0;
	हाल Opt_qnoenक्रमce:
	हाल Opt_uqnoenक्रमce:
		parsing_mp->m_qflags |= (XFS_UQUOTA_ACCT | XFS_UQUOTA_ACTIVE);
		parsing_mp->m_qflags &= ~XFS_UQUOTA_ENFD;
		वापस 0;
	हाल Opt_pquota:
	हाल Opt_prjquota:
		parsing_mp->m_qflags |= (XFS_PQUOTA_ACCT | XFS_PQUOTA_ACTIVE |
				 XFS_PQUOTA_ENFD);
		वापस 0;
	हाल Opt_pqnoenक्रमce:
		parsing_mp->m_qflags |= (XFS_PQUOTA_ACCT | XFS_PQUOTA_ACTIVE);
		parsing_mp->m_qflags &= ~XFS_PQUOTA_ENFD;
		वापस 0;
	हाल Opt_gquota:
	हाल Opt_grpquota:
		parsing_mp->m_qflags |= (XFS_GQUOTA_ACCT | XFS_GQUOTA_ACTIVE |
				 XFS_GQUOTA_ENFD);
		वापस 0;
	हाल Opt_gqnoenक्रमce:
		parsing_mp->m_qflags |= (XFS_GQUOTA_ACCT | XFS_GQUOTA_ACTIVE);
		parsing_mp->m_qflags &= ~XFS_GQUOTA_ENFD;
		वापस 0;
	हाल Opt_discard:
		parsing_mp->m_flags |= XFS_MOUNT_DISCARD;
		वापस 0;
	हाल Opt_nodiscard:
		parsing_mp->m_flags &= ~XFS_MOUNT_DISCARD;
		वापस 0;
#अगर_घोषित CONFIG_FS_DAX
	हाल Opt_dax:
		xfs_mount_set_dax_mode(parsing_mp, XFS_DAX_ALWAYS);
		वापस 0;
	हाल Opt_dax_क्रमागत:
		xfs_mount_set_dax_mode(parsing_mp, result.uपूर्णांक_32);
		वापस 0;
#पूर्ण_अगर
	/* Following mount options will be हटाओd in September 2025 */
	हाल Opt_ikeep:
		xfs_fs_warn_deprecated(fc, param, XFS_MOUNT_IKEEP, true);
		parsing_mp->m_flags |= XFS_MOUNT_IKEEP;
		वापस 0;
	हाल Opt_noikeep:
		xfs_fs_warn_deprecated(fc, param, XFS_MOUNT_IKEEP, false);
		parsing_mp->m_flags &= ~XFS_MOUNT_IKEEP;
		वापस 0;
	हाल Opt_attr2:
		xfs_fs_warn_deprecated(fc, param, XFS_MOUNT_ATTR2, true);
		parsing_mp->m_flags |= XFS_MOUNT_ATTR2;
		वापस 0;
	हाल Opt_noattr2:
		xfs_fs_warn_deprecated(fc, param, XFS_MOUNT_NOATTR2, true);
		parsing_mp->m_flags &= ~XFS_MOUNT_ATTR2;
		parsing_mp->m_flags |= XFS_MOUNT_NOATTR2;
		वापस 0;
	शेष:
		xfs_warn(parsing_mp, "unknown mount option [%s].", param->key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_fs_validate_params(
	काष्ठा xfs_mount	*mp)
अणु
	/*
	 * no recovery flag requires a पढ़ो-only mount
	 */
	अगर ((mp->m_flags & XFS_MOUNT_NORECOVERY) &&
	    !(mp->m_flags & XFS_MOUNT_RDONLY)) अणु
		xfs_warn(mp, "no-recovery mounts must be read-only.");
		वापस -EINVAL;
	पूर्ण

	अगर ((mp->m_flags & XFS_MOUNT_NOALIGN) &&
	    (mp->m_dalign || mp->m_swidth)) अणु
		xfs_warn(mp,
	"sunit and swidth options incompatible with the noalign option");
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_XFS_QUOTA) && mp->m_qflags != 0) अणु
		xfs_warn(mp, "quota support not available in this kernel.");
		वापस -EINVAL;
	पूर्ण

	अगर ((mp->m_dalign && !mp->m_swidth) ||
	    (!mp->m_dalign && mp->m_swidth)) अणु
		xfs_warn(mp, "sunit and swidth must be specified together");
		वापस -EINVAL;
	पूर्ण

	अगर (mp->m_dalign && (mp->m_swidth % mp->m_dalign != 0)) अणु
		xfs_warn(mp,
	"stripe width (%d) must be a multiple of the stripe unit (%d)",
			mp->m_swidth, mp->m_dalign);
		वापस -EINVAL;
	पूर्ण

	अगर (mp->m_logbufs != -1 &&
	    mp->m_logbufs != 0 &&
	    (mp->m_logbufs < XLOG_MIN_ICLOGS ||
	     mp->m_logbufs > XLOG_MAX_ICLOGS)) अणु
		xfs_warn(mp, "invalid logbufs value: %d [not %d-%d]",
			mp->m_logbufs, XLOG_MIN_ICLOGS, XLOG_MAX_ICLOGS);
		वापस -EINVAL;
	पूर्ण

	अगर (mp->m_logbsize != -1 &&
	    mp->m_logbsize !=  0 &&
	    (mp->m_logbsize < XLOG_MIN_RECORD_BSIZE ||
	     mp->m_logbsize > XLOG_MAX_RECORD_BSIZE ||
	     !is_घातer_of_2(mp->m_logbsize))) अणु
		xfs_warn(mp,
			"invalid logbufsize: %d [not 16k,32k,64k,128k or 256k]",
			mp->m_logbsize);
		वापस -EINVAL;
	पूर्ण

	अगर ((mp->m_flags & XFS_MOUNT_ALLOCSIZE) &&
	    (mp->m_allocsize_log > XFS_MAX_IO_LOG ||
	     mp->m_allocsize_log < XFS_MIN_IO_LOG)) अणु
		xfs_warn(mp, "invalid log iosize: %d [not %d-%d]",
			mp->m_allocsize_log, XFS_MIN_IO_LOG, XFS_MAX_IO_LOG);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_fs_fill_super(
	काष्ठा super_block	*sb,
	काष्ठा fs_context	*fc)
अणु
	काष्ठा xfs_mount	*mp = sb->s_fs_info;
	काष्ठा inode		*root;
	पूर्णांक			flags = 0, error;

	mp->m_super = sb;

	error = xfs_fs_validate_params(mp);
	अगर (error)
		जाओ out_मुक्त_names;

	sb_min_blocksize(sb, BBSIZE);
	sb->s_xattr = xfs_xattr_handlers;
	sb->s_export_op = &xfs_export_operations;
#अगर_घोषित CONFIG_XFS_QUOTA
	sb->s_qcop = &xfs_quotactl_operations;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP | QTYPE_MASK_PRJ;
#पूर्ण_अगर
	sb->s_op = &xfs_super_operations;

	/*
	 * Delay mount work अगर the debug hook is set. This is debug
	 * instrumention to coordinate simulation of xfs mount failures with
	 * VFS superblock operations
	 */
	अगर (xfs_globals.mount_delay) अणु
		xfs_notice(mp, "Delaying mount for %d seconds.",
			xfs_globals.mount_delay);
		msleep(xfs_globals.mount_delay * 1000);
	पूर्ण

	अगर (fc->sb_flags & SB_SILENT)
		flags |= XFS_MFSI_QUIET;

	error = xfs_खोलो_devices(mp);
	अगर (error)
		जाओ out_मुक्त_names;

	error = xfs_init_mount_workqueues(mp);
	अगर (error)
		जाओ out_बंद_devices;

	error = xfs_init_percpu_counters(mp);
	अगर (error)
		जाओ out_destroy_workqueues;

	/* Allocate stats memory beक्रमe we करो operations that might use it */
	mp->m_stats.xs_stats = alloc_percpu(काष्ठा xfsstats);
	अगर (!mp->m_stats.xs_stats) अणु
		error = -ENOMEM;
		जाओ out_destroy_counters;
	पूर्ण

	error = xfs_पढ़ोsb(mp, flags);
	अगर (error)
		जाओ out_मुक्त_stats;

	error = xfs_finish_flags(mp);
	अगर (error)
		जाओ out_मुक्त_sb;

	error = xfs_setup_devices(mp);
	अगर (error)
		जाओ out_मुक्त_sb;

	/* V4 support is undergoing deprecation. */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb)) अणु
#अगर_घोषित CONFIG_XFS_SUPPORT_V4
		xfs_warn_once(mp,
	"Deprecated V4 format (crc=0) will not be supported after September 2030.");
#अन्यथा
		xfs_warn(mp,
	"Deprecated V4 format (crc=0) not supported by kernel.");
		error = -EINVAL;
		जाओ out_मुक्त_sb;
#पूर्ण_अगर
	पूर्ण

	/* Fileप्रणाली claims it needs repair, so refuse the mount. */
	अगर (xfs_sb_version_needsrepair(&mp->m_sb)) अणु
		xfs_warn(mp, "Filesystem needs repair.  Please run xfs_repair.");
		error = -EFSCORRUPTED;
		जाओ out_मुक्त_sb;
	पूर्ण

	/*
	 * Don't touch the fileप्रणाली अगर a user tool thinks it owns the primary
	 * superblock.  mkfs करोesn't clear the flag from secondary supers, so
	 * we करोn't check them at all.
	 */
	अगर (mp->m_sb.sb_inprogress) अणु
		xfs_warn(mp, "Offline file system operation in progress!");
		error = -EFSCORRUPTED;
		जाओ out_मुक्त_sb;
	पूर्ण

	/*
	 * Until this is fixed only page-sized or smaller data blocks work.
	 */
	अगर (mp->m_sb.sb_blocksize > PAGE_SIZE) अणु
		xfs_warn(mp,
		"File system with blocksize %d bytes. "
		"Only pagesize (%ld) or less will currently work.",
				mp->m_sb.sb_blocksize, PAGE_SIZE);
		error = -ENOSYS;
		जाओ out_मुक्त_sb;
	पूर्ण

	/* Ensure this fileप्रणाली fits in the page cache limits */
	अगर (xfs_sb_validate_fsb_count(&mp->m_sb, mp->m_sb.sb_dblocks) ||
	    xfs_sb_validate_fsb_count(&mp->m_sb, mp->m_sb.sb_rblocks)) अणु
		xfs_warn(mp,
		"file system too large to be mounted on this system.");
		error = -EFBIG;
		जाओ out_मुक्त_sb;
	पूर्ण

	/*
	 * XFS block mappings use 54 bits to store the logical block offset.
	 * This should suffice to handle the maximum file size that the VFS
	 * supports (currently 2^63 bytes on 64-bit and अच_दीर्घ_उच्च << PAGE_SHIFT
	 * bytes on 32-bit), but as XFS and VFS have gotten the s_maxbytes
	 * calculation wrong on 32-bit kernels in the past, we'll add a WARN_ON
	 * to check this निश्चितion.
	 *
	 * Aव्योम पूर्णांकeger overflow by comparing the maximum bmbt offset to the
	 * maximum pagecache offset in units of fs blocks.
	 */
	अगर (!xfs_verअगरy_fileoff(mp, XFS_B_TO_FSBT(mp, MAX_LFS_खाताSIZE))) अणु
		xfs_warn(mp,
"MAX_LFS_FILESIZE block offset (%llu) exceeds extent map maximum (%llu)!",
			 XFS_B_TO_FSBT(mp, MAX_LFS_खाताSIZE),
			 XFS_MAX_खाताOFF);
		error = -EINVAL;
		जाओ out_मुक्त_sb;
	पूर्ण

	error = xfs_filestream_mount(mp);
	अगर (error)
		जाओ out_मुक्त_sb;

	/*
	 * we must configure the block size in the superblock beक्रमe we run the
	 * full mount process as the mount process can lookup and cache inodes.
	 */
	sb->s_magic = XFS_SUPER_MAGIC;
	sb->s_blocksize = mp->m_sb.sb_blocksize;
	sb->s_blocksize_bits = ffs(sb->s_blocksize) - 1;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_max_links = XFS_MAXLINK;
	sb->s_समय_gran = 1;
	अगर (xfs_sb_version_hasbigसमय(&mp->m_sb)) अणु
		sb->s_समय_min = xfs_bigसमय_प्रकारo_unix(XFS_BIGTIME_TIME_MIN);
		sb->s_समय_max = xfs_bigसमय_प्रकारo_unix(XFS_BIGTIME_TIME_MAX);
	पूर्ण अन्यथा अणु
		sb->s_समय_min = XFS_LEGACY_TIME_MIN;
		sb->s_समय_max = XFS_LEGACY_TIME_MAX;
	पूर्ण
	trace_xfs_inode_बारtamp_range(mp, sb->s_समय_min, sb->s_समय_max);
	sb->s_अगरlags |= SB_I_CGROUPWB;

	set_posix_acl_flag(sb);

	/* version 5 superblocks support inode version counters. */
	अगर (XFS_SB_VERSION_NUM(&mp->m_sb) == XFS_SB_VERSION_5)
		sb->s_flags |= SB_I_VERSION;

	अगर (xfs_sb_version_hasbigसमय(&mp->m_sb))
		xfs_warn(mp,
 "EXPERIMENTAL big timestamp feature in use. Use at your own risk!");

	अगर (mp->m_flags & XFS_MOUNT_DAX_ALWAYS) अणु
		bool rtdev_is_dax = false, datadev_is_dax;

		xfs_warn(mp,
		"DAX enabled. Warning: EXPERIMENTAL, use at your own risk");

		datadev_is_dax = bdev_dax_supported(mp->m_ddev_targp->bt_bdev,
			sb->s_blocksize);
		अगर (mp->m_rtdev_targp)
			rtdev_is_dax = bdev_dax_supported(
				mp->m_rtdev_targp->bt_bdev, sb->s_blocksize);
		अगर (!rtdev_is_dax && !datadev_is_dax) अणु
			xfs_alert(mp,
			"DAX unsupported by block device. Turning off DAX.");
			xfs_mount_set_dax_mode(mp, XFS_DAX_NEVER);
		पूर्ण
		अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
			xfs_alert(mp,
		"DAX and reflink cannot be used together!");
			error = -EINVAL;
			जाओ out_filestream_unmount;
		पूर्ण
	पूर्ण

	अगर (mp->m_flags & XFS_MOUNT_DISCARD) अणु
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);

		अगर (!blk_queue_discard(q)) अणु
			xfs_warn(mp, "mounting with \"discard\" option, but "
					"the device does not support discard");
			mp->m_flags &= ~XFS_MOUNT_DISCARD;
		पूर्ण
	पूर्ण

	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		अगर (mp->m_sb.sb_rblocks) अणु
			xfs_alert(mp,
	"reflink not compatible with realtime device!");
			error = -EINVAL;
			जाओ out_filestream_unmount;
		पूर्ण

		अगर (xfs_globals.always_cow) अणु
			xfs_info(mp, "using DEBUG-only always_cow mode.");
			mp->m_always_cow = true;
		पूर्ण
	पूर्ण

	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb) && mp->m_sb.sb_rblocks) अणु
		xfs_alert(mp,
	"reverse mapping btree not compatible with realtime device!");
		error = -EINVAL;
		जाओ out_filestream_unmount;
	पूर्ण

	अगर (xfs_sb_version_hasinobtcounts(&mp->m_sb))
		xfs_warn(mp,
 "EXPERIMENTAL inode btree counters feature in use. Use at your own risk!");

	error = xfs_mountfs(mp);
	अगर (error)
		जाओ out_filestream_unmount;

	root = igrab(VFS_I(mp->m_rootip));
	अगर (!root) अणु
		error = -ENOENT;
		जाओ out_unmount;
	पूर्ण
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		error = -ENOMEM;
		जाओ out_unmount;
	पूर्ण

	वापस 0;

 out_filestream_unmount:
	xfs_filestream_unmount(mp);
 out_मुक्त_sb:
	xfs_मुक्तsb(mp);
 out_मुक्त_stats:
	मुक्त_percpu(mp->m_stats.xs_stats);
 out_destroy_counters:
	xfs_destroy_percpu_counters(mp);
 out_destroy_workqueues:
	xfs_destroy_mount_workqueues(mp);
 out_बंद_devices:
	xfs_बंद_devices(mp);
 out_मुक्त_names:
	sb->s_fs_info = शून्य;
	xfs_mount_मुक्त(mp);
	वापस error;

 out_unmount:
	xfs_filestream_unmount(mp);
	xfs_unmountfs(mp);
	जाओ out_मुक्त_sb;
पूर्ण

अटल पूर्णांक
xfs_fs_get_tree(
	काष्ठा fs_context	*fc)
अणु
	वापस get_tree_bdev(fc, xfs_fs_fill_super);
पूर्ण

अटल पूर्णांक
xfs_remount_rw(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	पूर्णांक error;

	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY) अणु
		xfs_warn(mp,
			"ro->rw transition prohibited on norecovery mount");
		वापस -EINVAL;
	पूर्ण

	अगर (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
	    xfs_sb_has_ro_compat_feature(sbp, XFS_SB_FEAT_RO_COMPAT_UNKNOWN)) अणु
		xfs_warn(mp,
	"ro->rw transition prohibited on unknown (0x%x) ro-compat filesystem",
			(sbp->sb_features_ro_compat &
				XFS_SB_FEAT_RO_COMPAT_UNKNOWN));
		वापस -EINVAL;
	पूर्ण

	mp->m_flags &= ~XFS_MOUNT_RDONLY;

	/*
	 * If this is the first remount to ग_लिखोable state we might have some
	 * superblock changes to update.
	 */
	अगर (mp->m_update_sb) अणु
		error = xfs_sync_sb(mp, false);
		अगर (error) अणु
			xfs_warn(mp, "failed to write sb changes");
			वापस error;
		पूर्ण
		mp->m_update_sb = false;
	पूर्ण

	/*
	 * Fill out the reserve pool अगर it is empty. Use the stashed value अगर
	 * it is non-zero, otherwise go with the शेष.
	 */
	xfs_restore_resvblks(mp);
	xfs_log_work_queue(mp);

	/* Recover any CoW blocks that never got remapped. */
	error = xfs_reflink_recover_cow(mp);
	अगर (error) अणु
		xfs_err(mp,
			"Error %d recovering leftover CoW allocations.", error);
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		वापस error;
	पूर्ण
	xfs_blockgc_start(mp);

	/* Create the per-AG metadata reservation pool .*/
	error = xfs_fs_reserve_ag_blocks(mp);
	अगर (error && error != -ENOSPC)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_remount_ro(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक error;

	/*
	 * Cancel background eofb scanning so it cannot race with the final
	 * log क्रमce+buftarg रुको and deadlock the remount.
	 */
	xfs_blockgc_stop(mp);

	/* Get rid of any leftover CoW reservations... */
	error = xfs_blockgc_मुक्त_space(mp, शून्य);
	अगर (error) अणु
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		वापस error;
	पूर्ण

	/* Free the per-AG metadata reservation pool. */
	error = xfs_fs_unreserve_ag_blocks(mp);
	अगर (error) अणु
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		वापस error;
	पूर्ण

	/*
	 * Beक्रमe we sync the metadata, we need to मुक्त up the reserve block
	 * pool so that the used block count in the superblock on disk is
	 * correct at the end of the remount. Stash the current* reserve pool
	 * size so that अगर we get remounted rw, we can वापस it to the same
	 * size.
	 */
	xfs_save_resvblks(mp);

	xfs_log_clean(mp);
	mp->m_flags |= XFS_MOUNT_RDONLY;

	वापस 0;
पूर्ण

/*
 * Logically we would वापस an error here to prevent users from believing
 * they might have changed mount options using remount which can't be changed.
 *
 * But unक्रमtunately mount(8) adds all options from mtab and fstab to the mount
 * arguments in some हालs so we can't blindly reject options, but have to
 * check क्रम each specअगरied option अगर it actually dअगरfers from the currently
 * set option and only reject it अगर that's the हाल.
 *
 * Until that is implemented we वापस success क्रम every remount request, and
 * silently ignore all options that we can't actually change.
 */
अटल पूर्णांक
xfs_fs_reconfigure(
	काष्ठा fs_context *fc)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(fc->root->d_sb);
	काष्ठा xfs_mount        *new_mp = fc->s_fs_info;
	xfs_sb_t		*sbp = &mp->m_sb;
	पूर्णांक			flags = fc->sb_flags;
	पूर्णांक			error;

	/* version 5 superblocks always support version counters. */
	अगर (XFS_SB_VERSION_NUM(&mp->m_sb) == XFS_SB_VERSION_5)
		fc->sb_flags |= SB_I_VERSION;

	error = xfs_fs_validate_params(new_mp);
	अगर (error)
		वापस error;

	sync_fileप्रणाली(mp->m_super);

	/* inode32 -> inode64 */
	अगर ((mp->m_flags & XFS_MOUNT_SMALL_INUMS) &&
	    !(new_mp->m_flags & XFS_MOUNT_SMALL_INUMS)) अणु
		mp->m_flags &= ~XFS_MOUNT_SMALL_INUMS;
		mp->m_maxagi = xfs_set_inode_alloc(mp, sbp->sb_agcount);
	पूर्ण

	/* inode64 -> inode32 */
	अगर (!(mp->m_flags & XFS_MOUNT_SMALL_INUMS) &&
	    (new_mp->m_flags & XFS_MOUNT_SMALL_INUMS)) अणु
		mp->m_flags |= XFS_MOUNT_SMALL_INUMS;
		mp->m_maxagi = xfs_set_inode_alloc(mp, sbp->sb_agcount);
	पूर्ण

	/* ro -> rw */
	अगर ((mp->m_flags & XFS_MOUNT_RDONLY) && !(flags & SB_RDONLY)) अणु
		error = xfs_remount_rw(mp);
		अगर (error)
			वापस error;
	पूर्ण

	/* rw -> ro */
	अगर (!(mp->m_flags & XFS_MOUNT_RDONLY) && (flags & SB_RDONLY)) अणु
		error = xfs_remount_ro(mp);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xfs_fs_मुक्त(
	काष्ठा fs_context	*fc)
अणु
	काष्ठा xfs_mount	*mp = fc->s_fs_info;

	/*
	 * mp is stored in the fs_context when it is initialized.
	 * mp is transferred to the superblock on a successful mount,
	 * but अगर an error occurs beक्रमe the transfer we have to मुक्त
	 * it here.
	 */
	अगर (mp)
		xfs_mount_मुक्त(mp);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations xfs_context_ops = अणु
	.parse_param = xfs_fs_parse_param,
	.get_tree    = xfs_fs_get_tree,
	.reconfigure = xfs_fs_reconfigure,
	.मुक्त        = xfs_fs_मुक्त,
पूर्ण;

अटल पूर्णांक xfs_init_fs_context(
	काष्ठा fs_context	*fc)
अणु
	काष्ठा xfs_mount	*mp;

	mp = kmem_alloc(माप(काष्ठा xfs_mount), KM_ZERO);
	अगर (!mp)
		वापस -ENOMEM;

	spin_lock_init(&mp->m_sb_lock);
	spin_lock_init(&mp->m_agirotor_lock);
	INIT_RADIX_TREE(&mp->m_perag_tree, GFP_ATOMIC);
	spin_lock_init(&mp->m_perag_lock);
	mutex_init(&mp->m_growlock);
	INIT_WORK(&mp->m_flush_inodes_work, xfs_flush_inodes_worker);
	INIT_DELAYED_WORK(&mp->m_reclaim_work, xfs_reclaim_worker);
	mp->m_kobj.kobject.kset = xfs_kset;
	/*
	 * We करोn't create the finobt per-ag space reservation until after log
	 * recovery, so we must set this to true so that an अगरree transaction
	 * started during log recovery will not depend on space reservations
	 * क्रम finobt expansion.
	 */
	mp->m_finobt_nores = true;

	/*
	 * These can be overridden by the mount option parsing.
	 */
	mp->m_logbufs = -1;
	mp->m_logbsize = -1;
	mp->m_allocsize_log = 16; /* 64k */

	/*
	 * Copy binary VFS mount flags we are पूर्णांकerested in.
	 */
	अगर (fc->sb_flags & SB_RDONLY)
		mp->m_flags |= XFS_MOUNT_RDONLY;
	अगर (fc->sb_flags & SB_सूचीSYNC)
		mp->m_flags |= XFS_MOUNT_सूचीSYNC;
	अगर (fc->sb_flags & SB_SYNCHRONOUS)
		mp->m_flags |= XFS_MOUNT_WSYNC;

	fc->s_fs_info = mp;
	fc->ops = &xfs_context_ops;

	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type xfs_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "xfs",
	.init_fs_context	= xfs_init_fs_context,
	.parameters		= xfs_fs_parameters,
	.समाप्त_sb		= समाप्त_block_super,
	.fs_flags		= FS_REQUIRES_DEV | FS_ALLOW_IDMAP,
पूर्ण;
MODULE_ALIAS_FS("xfs");

STATIC पूर्णांक __init
xfs_init_zones(व्योम)
अणु
	xfs_log_ticket_zone = kmem_cache_create("xfs_log_ticket",
						माप(काष्ठा xlog_ticket),
						0, 0, शून्य);
	अगर (!xfs_log_ticket_zone)
		जाओ out;

	xfs_bmap_मुक्त_item_zone = kmem_cache_create("xfs_bmap_free_item",
					माप(काष्ठा xfs_extent_मुक्त_item),
					0, 0, शून्य);
	अगर (!xfs_bmap_मुक्त_item_zone)
		जाओ out_destroy_log_ticket_zone;

	xfs_btree_cur_zone = kmem_cache_create("xfs_btree_cur",
					       माप(काष्ठा xfs_btree_cur),
					       0, 0, शून्य);
	अगर (!xfs_btree_cur_zone)
		जाओ out_destroy_bmap_मुक्त_item_zone;

	xfs_da_state_zone = kmem_cache_create("xfs_da_state",
					      माप(काष्ठा xfs_da_state),
					      0, 0, शून्य);
	अगर (!xfs_da_state_zone)
		जाओ out_destroy_btree_cur_zone;

	xfs_अगरork_zone = kmem_cache_create("xfs_ifork",
					   माप(काष्ठा xfs_अगरork),
					   0, 0, शून्य);
	अगर (!xfs_अगरork_zone)
		जाओ out_destroy_da_state_zone;

	xfs_trans_zone = kmem_cache_create("xfs_trans",
					   माप(काष्ठा xfs_trans),
					   0, 0, शून्य);
	अगर (!xfs_trans_zone)
		जाओ out_destroy_अगरork_zone;


	/*
	 * The size of the zone allocated buf log item is the maximum
	 * size possible under XFS.  This wastes a little bit of memory,
	 * but it is much faster.
	 */
	xfs_buf_item_zone = kmem_cache_create("xfs_buf_item",
					      माप(काष्ठा xfs_buf_log_item),
					      0, 0, शून्य);
	अगर (!xfs_buf_item_zone)
		जाओ out_destroy_trans_zone;

	xfs_efd_zone = kmem_cache_create("xfs_efd_item",
					(माप(काष्ठा xfs_efd_log_item) +
					(XFS_EFD_MAX_FAST_EXTENTS - 1) *
					माप(काष्ठा xfs_extent)),
					0, 0, शून्य);
	अगर (!xfs_efd_zone)
		जाओ out_destroy_buf_item_zone;

	xfs_efi_zone = kmem_cache_create("xfs_efi_item",
					 (माप(काष्ठा xfs_efi_log_item) +
					 (XFS_EFI_MAX_FAST_EXTENTS - 1) *
					 माप(काष्ठा xfs_extent)),
					 0, 0, शून्य);
	अगर (!xfs_efi_zone)
		जाओ out_destroy_efd_zone;

	xfs_inode_zone = kmem_cache_create("xfs_inode",
					   माप(काष्ठा xfs_inode), 0,
					   (SLAB_HWCACHE_ALIGN |
					    SLAB_RECLAIM_ACCOUNT |
					    SLAB_MEM_SPREAD | SLAB_ACCOUNT),
					   xfs_fs_inode_init_once);
	अगर (!xfs_inode_zone)
		जाओ out_destroy_efi_zone;

	xfs_ili_zone = kmem_cache_create("xfs_ili",
					 माप(काष्ठा xfs_inode_log_item), 0,
					 SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD,
					 शून्य);
	अगर (!xfs_ili_zone)
		जाओ out_destroy_inode_zone;

	xfs_icreate_zone = kmem_cache_create("xfs_icr",
					     माप(काष्ठा xfs_icreate_item),
					     0, 0, शून्य);
	अगर (!xfs_icreate_zone)
		जाओ out_destroy_ili_zone;

	xfs_rud_zone = kmem_cache_create("xfs_rud_item",
					 माप(काष्ठा xfs_rud_log_item),
					 0, 0, शून्य);
	अगर (!xfs_rud_zone)
		जाओ out_destroy_icreate_zone;

	xfs_rui_zone = kmem_cache_create("xfs_rui_item",
			xfs_rui_log_item_माप(XFS_RUI_MAX_FAST_EXTENTS),
			0, 0, शून्य);
	अगर (!xfs_rui_zone)
		जाओ out_destroy_rud_zone;

	xfs_cud_zone = kmem_cache_create("xfs_cud_item",
					 माप(काष्ठा xfs_cud_log_item),
					 0, 0, शून्य);
	अगर (!xfs_cud_zone)
		जाओ out_destroy_rui_zone;

	xfs_cui_zone = kmem_cache_create("xfs_cui_item",
			xfs_cui_log_item_माप(XFS_CUI_MAX_FAST_EXTENTS),
			0, 0, शून्य);
	अगर (!xfs_cui_zone)
		जाओ out_destroy_cud_zone;

	xfs_bud_zone = kmem_cache_create("xfs_bud_item",
					 माप(काष्ठा xfs_bud_log_item),
					 0, 0, शून्य);
	अगर (!xfs_bud_zone)
		जाओ out_destroy_cui_zone;

	xfs_bui_zone = kmem_cache_create("xfs_bui_item",
			xfs_bui_log_item_माप(XFS_BUI_MAX_FAST_EXTENTS),
			0, 0, शून्य);
	अगर (!xfs_bui_zone)
		जाओ out_destroy_bud_zone;

	वापस 0;

 out_destroy_bud_zone:
	kmem_cache_destroy(xfs_bud_zone);
 out_destroy_cui_zone:
	kmem_cache_destroy(xfs_cui_zone);
 out_destroy_cud_zone:
	kmem_cache_destroy(xfs_cud_zone);
 out_destroy_rui_zone:
	kmem_cache_destroy(xfs_rui_zone);
 out_destroy_rud_zone:
	kmem_cache_destroy(xfs_rud_zone);
 out_destroy_icreate_zone:
	kmem_cache_destroy(xfs_icreate_zone);
 out_destroy_ili_zone:
	kmem_cache_destroy(xfs_ili_zone);
 out_destroy_inode_zone:
	kmem_cache_destroy(xfs_inode_zone);
 out_destroy_efi_zone:
	kmem_cache_destroy(xfs_efi_zone);
 out_destroy_efd_zone:
	kmem_cache_destroy(xfs_efd_zone);
 out_destroy_buf_item_zone:
	kmem_cache_destroy(xfs_buf_item_zone);
 out_destroy_trans_zone:
	kmem_cache_destroy(xfs_trans_zone);
 out_destroy_अगरork_zone:
	kmem_cache_destroy(xfs_अगरork_zone);
 out_destroy_da_state_zone:
	kmem_cache_destroy(xfs_da_state_zone);
 out_destroy_btree_cur_zone:
	kmem_cache_destroy(xfs_btree_cur_zone);
 out_destroy_bmap_मुक्त_item_zone:
	kmem_cache_destroy(xfs_bmap_मुक्त_item_zone);
 out_destroy_log_ticket_zone:
	kmem_cache_destroy(xfs_log_ticket_zone);
 out:
	वापस -ENOMEM;
पूर्ण

STATIC व्योम
xfs_destroy_zones(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त are flushed beक्रमe we
	 * destroy caches.
	 */
	rcu_barrier();
	kmem_cache_destroy(xfs_bui_zone);
	kmem_cache_destroy(xfs_bud_zone);
	kmem_cache_destroy(xfs_cui_zone);
	kmem_cache_destroy(xfs_cud_zone);
	kmem_cache_destroy(xfs_rui_zone);
	kmem_cache_destroy(xfs_rud_zone);
	kmem_cache_destroy(xfs_icreate_zone);
	kmem_cache_destroy(xfs_ili_zone);
	kmem_cache_destroy(xfs_inode_zone);
	kmem_cache_destroy(xfs_efi_zone);
	kmem_cache_destroy(xfs_efd_zone);
	kmem_cache_destroy(xfs_buf_item_zone);
	kmem_cache_destroy(xfs_trans_zone);
	kmem_cache_destroy(xfs_अगरork_zone);
	kmem_cache_destroy(xfs_da_state_zone);
	kmem_cache_destroy(xfs_btree_cur_zone);
	kmem_cache_destroy(xfs_bmap_मुक्त_item_zone);
	kmem_cache_destroy(xfs_log_ticket_zone);
पूर्ण

STATIC पूर्णांक __init
xfs_init_workqueues(व्योम)
अणु
	/*
	 * The allocation workqueue can be used in memory reclaim situations
	 * (ग_लिखोpage path), and parallelism is only limited by the number of
	 * AGs in all the fileप्रणालीs mounted. Hence use the शेष large
	 * max_active value क्रम this workqueue.
	 */
	xfs_alloc_wq = alloc_workqueue("xfsalloc",
			XFS_WQFLAGS(WQ_MEM_RECLAIM | WQ_FREEZABLE), 0);
	अगर (!xfs_alloc_wq)
		वापस -ENOMEM;

	xfs_discard_wq = alloc_workqueue("xfsdiscard", XFS_WQFLAGS(WQ_UNBOUND),
			0);
	अगर (!xfs_discard_wq)
		जाओ out_मुक्त_alloc_wq;

	वापस 0;
out_मुक्त_alloc_wq:
	destroy_workqueue(xfs_alloc_wq);
	वापस -ENOMEM;
पूर्ण

STATIC व्योम
xfs_destroy_workqueues(व्योम)
अणु
	destroy_workqueue(xfs_discard_wq);
	destroy_workqueue(xfs_alloc_wq);
पूर्ण

STATIC पूर्णांक __init
init_xfs_fs(व्योम)
अणु
	पूर्णांक			error;

	xfs_check_ondisk_काष्ठाs();

	prपूर्णांकk(KERN_INFO XFS_VERSION_STRING " with "
			 XFS_BUILD_OPTIONS " enabled\n");

	xfs_dir_startup();

	error = xfs_init_zones();
	अगर (error)
		जाओ out;

	error = xfs_init_workqueues();
	अगर (error)
		जाओ out_destroy_zones;

	error = xfs_mru_cache_init();
	अगर (error)
		जाओ out_destroy_wq;

	error = xfs_buf_init();
	अगर (error)
		जाओ out_mru_cache_uninit;

	error = xfs_init_procfs();
	अगर (error)
		जाओ out_buf_terminate;

	error = xfs_sysctl_रेजिस्टर();
	अगर (error)
		जाओ out_cleanup_procfs;

	xfs_kset = kset_create_and_add("xfs", शून्य, fs_kobj);
	अगर (!xfs_kset) अणु
		error = -ENOMEM;
		जाओ out_sysctl_unरेजिस्टर;
	पूर्ण

	xfsstats.xs_kobj.kobject.kset = xfs_kset;

	xfsstats.xs_stats = alloc_percpu(काष्ठा xfsstats);
	अगर (!xfsstats.xs_stats) अणु
		error = -ENOMEM;
		जाओ out_kset_unरेजिस्टर;
	पूर्ण

	error = xfs_sysfs_init(&xfsstats.xs_kobj, &xfs_stats_ktype, शून्य,
			       "stats");
	अगर (error)
		जाओ out_मुक्त_stats;

#अगर_घोषित DEBUG
	xfs_dbg_kobj.kobject.kset = xfs_kset;
	error = xfs_sysfs_init(&xfs_dbg_kobj, &xfs_dbg_ktype, शून्य, "debug");
	अगर (error)
		जाओ out_हटाओ_stats_kobj;
#पूर्ण_अगर

	error = xfs_qm_init();
	अगर (error)
		जाओ out_हटाओ_dbg_kobj;

	error = रेजिस्टर_fileप्रणाली(&xfs_fs_type);
	अगर (error)
		जाओ out_qm_निकास;
	वापस 0;

 out_qm_निकास:
	xfs_qm_निकास();
 out_हटाओ_dbg_kobj:
#अगर_घोषित DEBUG
	xfs_sysfs_del(&xfs_dbg_kobj);
 out_हटाओ_stats_kobj:
#पूर्ण_अगर
	xfs_sysfs_del(&xfsstats.xs_kobj);
 out_मुक्त_stats:
	मुक्त_percpu(xfsstats.xs_stats);
 out_kset_unरेजिस्टर:
	kset_unरेजिस्टर(xfs_kset);
 out_sysctl_unरेजिस्टर:
	xfs_sysctl_unरेजिस्टर();
 out_cleanup_procfs:
	xfs_cleanup_procfs();
 out_buf_terminate:
	xfs_buf_terminate();
 out_mru_cache_uninit:
	xfs_mru_cache_uninit();
 out_destroy_wq:
	xfs_destroy_workqueues();
 out_destroy_zones:
	xfs_destroy_zones();
 out:
	वापस error;
पूर्ण

STATIC व्योम __निकास
निकास_xfs_fs(व्योम)
अणु
	xfs_qm_निकास();
	unरेजिस्टर_fileप्रणाली(&xfs_fs_type);
#अगर_घोषित DEBUG
	xfs_sysfs_del(&xfs_dbg_kobj);
#पूर्ण_अगर
	xfs_sysfs_del(&xfsstats.xs_kobj);
	मुक्त_percpu(xfsstats.xs_stats);
	kset_unरेजिस्टर(xfs_kset);
	xfs_sysctl_unरेजिस्टर();
	xfs_cleanup_procfs();
	xfs_buf_terminate();
	xfs_mru_cache_uninit();
	xfs_destroy_workqueues();
	xfs_destroy_zones();
	xfs_uuid_table_मुक्त();
पूर्ण

module_init(init_xfs_fs);
module_निकास(निकास_xfs_fs);

MODULE_AUTHOR("Silicon Graphics, Inc.");
MODULE_DESCRIPTION(XFS_VERSION_STRING " with " XFS_BUILD_OPTIONS " enabled");
MODULE_LICENSE("GPL");
