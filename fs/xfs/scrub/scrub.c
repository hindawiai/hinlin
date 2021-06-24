<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_scrub.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"
#समावेश "scrub/repair.h"
#समावेश "scrub/health.h"

/*
 * Online Scrub and Repair
 *
 * Traditionally, XFS (the kernel driver) did not know how to check or
 * repair on-disk data काष्ठाures.  That task was left to the xfs_check
 * and xfs_repair tools, both of which require taking the fileप्रणाली
 * offline क्रम a thorough but समय consuming examination.  Online
 * scrub & repair, on the other hand, enables us to check the metadata
 * क्रम obvious errors जबतक carefully stepping around the fileप्रणाली's
 * ongoing operations, locking rules, etc.
 *
 * Given that most XFS metadata consist of records stored in a btree,
 * most of the checking functions iterate the btree blocks themselves
 * looking क्रम irregularities.  When a record block is encountered, each
 * record can be checked क्रम obviously bad values.  Record values can
 * also be cross-referenced against other btrees to look क्रम potential
 * misunderstandings between pieces of metadata.
 *
 * It is expected that the checkers responsible क्रम per-AG metadata
 * काष्ठाures will lock the AG headers (AGI, AGF, AGFL), iterate the
 * metadata काष्ठाure, and perक्रमm any relevant cross-referencing beक्रमe
 * unlocking the AG and वापसing the results to userspace.  These
 * scrubbers must not keep an AG locked क्रम too दीर्घ to aव्योम tying up
 * the block and inode allocators.
 *
 * Block maps and b-trees rooted in an inode present a special challenge
 * because they can involve extents from any AG.  The general scrubber
 * काष्ठाure of lock -> check -> xref -> unlock still holds, but AG
 * locking order rules /must/ be obeyed to aव्योम deadlocks.  The
 * ordering rule, of course, is that we must lock in increasing AG
 * order.  Helper functions are provided to track which AG headers we've
 * alपढ़ोy locked.  If we detect an imminent locking order violation, we
 * can संकेत a potential deadlock, in which हाल the scrubber can jump
 * out to the top level, lock all the AGs in order, and retry the scrub.
 *
 * For file data (directories, extended attributes, symlinks) scrub, we
 * can simply lock the inode and walk the data.  For btree data
 * (directories and attributes) we follow the same btree-scrubbing
 * strategy outlined previously to check the records.
 *
 * We use a bit of trickery with transactions to aव्योम buffer deadlocks
 * अगर there is a cycle in the metadata.  The basic problem is that
 * travelling करोwn a btree involves locking the current buffer at each
 * tree level.  If a poपूर्णांकer should somehow poपूर्णांक back to a buffer that
 * we've alपढ़ोy examined, we will deadlock due to the second buffer
 * locking attempt.  Note however that grabbing a buffer in transaction
 * context links the locked buffer to the transaction.  If we try to
 * re-grab the buffer in the context of the same transaction, we aव्योम
 * the second lock attempt and जारी.  Between the verअगरier and the
 * scrubber, something will notice that something is amiss and report
 * the corruption.  Thereक्रमe, each scrubber will allocate an empty
 * transaction, attach buffers to it, and cancel the transaction at the
 * end of the scrub run.  Cancelling a non-dirty transaction simply
 * unlocks the buffers.
 *
 * There are four pieces of data that scrub can communicate to
 * userspace.  The first is the error code (त्रुटि_सं), which can be used to
 * communicate operational errors in perक्रमming the scrub.  There are
 * also three flags that can be set in the scrub context.  If the data
 * काष्ठाure itself is corrupt, the CORRUPT flag will be set.  If
 * the metadata is correct but otherwise suboptimal, the PREEN flag
 * will be set.
 *
 * We perक्रमm secondary validation of fileप्रणाली metadata by
 * cross-referencing every record with all other available metadata.
 * For example, क्रम block mapping extents, we verअगरy that there are no
 * records in the मुक्त space and inode btrees corresponding to that
 * space extent and that there is a corresponding entry in the reverse
 * mapping btree.  Inconsistent metadata is noted by setting the
 * XCORRUPT flag; btree query function errors are noted by setting the
 * XFAIL flag and deleting the cursor to prevent further attempts to
 * cross-reference with a defective btree.
 *
 * If a piece of metadata proves corrupt or suboptimal, the userspace
 * program can ask the kernel to apply some tender loving care (TLC) to
 * the metadata object by setting the REPAIR flag and re-calling the
 * scrub ioctl.  "Corruption" is defined by metadata violating the
 * on-disk specअगरication; operations cannot जारी अगर the violation is
 * left untreated.  It is possible क्रम XFS to जारी अगर an object is
 * "suboptimal", however perक्रमmance may be degraded.  Repairs are
 * usually perक्रमmed by rebuilding the metadata entirely out of
 * redundant metadata.  Optimizing, on the other hand, can someबार be
 * करोne without rebuilding entire काष्ठाures.
 *
 * Generally speaking, the repair code has the following code काष्ठाure:
 * Lock -> scrub -> repair -> commit -> re-lock -> re-scrub -> unlock.
 * The first check helps us figure out अगर we need to rebuild or simply
 * optimize the काष्ठाure so that the rebuild knows what to करो.  The
 * second check evaluates the completeness of the repair; that is what
 * is reported to userspace.
 *
 * A quick note on symbol prefixes:
 * - "xfs_" are general XFS symbols.
 * - "xchk_" are symbols related to metadata checking.
 * - "xrep_" are symbols related to metadata repair.
 * - "xfs_scrub_" are symbols that tie online fsck to the rest of XFS.
 */

/*
 * Scrub probe -- userspace uses this to probe अगर we're willing to scrub
 * or repair a given mountpoपूर्णांक.  This will be used by xfs_scrub to
 * probe the kernel's abilities to scrub (and repair) the metadata.  We
 * करो this by validating the ioctl inमाला_दो from userspace, preparing the
 * fileप्रणाली क्रम a scrub (or a repair) operation, and immediately
 * वापसing to userspace.  Userspace can use the वापसed त्रुटि_सं and
 * काष्ठाure state to decide (in broad terms) अगर scrub/repair are
 * supported by the running kernel.
 */
अटल पूर्णांक
xchk_probe(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error = 0;

	अगर (xchk_should_terminate(sc, &error))
		वापस error;

	वापस 0;
पूर्ण

/* Scrub setup and tearकरोwn */

/* Free all the resources and finish the transactions. */
STATIC पूर्णांक
xchk_tearकरोwn(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			error)
अणु
	काष्ठा xfs_inode	*ip_in = XFS_I(file_inode(sc->file));

	xchk_ag_मुक्त(sc, &sc->sa);
	अगर (sc->tp) अणु
		अगर (error == 0 && (sc->sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR))
			error = xfs_trans_commit(sc->tp);
		अन्यथा
			xfs_trans_cancel(sc->tp);
		sc->tp = शून्य;
	पूर्ण
	अगर (sc->ip) अणु
		अगर (sc->ilock_flags)
			xfs_iunlock(sc->ip, sc->ilock_flags);
		अगर (sc->ip != ip_in &&
		    !xfs_पूर्णांकernal_inum(sc->mp, sc->ip->i_ino))
			xfs_irele(sc->ip);
		sc->ip = शून्य;
	पूर्ण
	अगर (sc->sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR)
		mnt_drop_ग_लिखो_file(sc->file);
	अगर (sc->flags & XCHK_REAPING_DISABLED)
		xchk_start_reaping(sc);
	अगर (sc->flags & XCHK_HAS_QUOTAOFFLOCK) अणु
		mutex_unlock(&sc->mp->m_quotainfo->qi_quotaofflock);
		sc->flags &= ~XCHK_HAS_QUOTAOFFLOCK;
	पूर्ण
	अगर (sc->buf) अणु
		kmem_मुक्त(sc->buf);
		sc->buf = शून्य;
	पूर्ण
	वापस error;
पूर्ण

/* Scrubbing dispatch. */

अटल स्थिर काष्ठा xchk_meta_ops meta_scrub_ops[] = अणु
	[XFS_SCRUB_TYPE_PROBE] = अणु	/* ioctl presence test */
		.type	= ST_NONE,
		.setup	= xchk_setup_fs,
		.scrub	= xchk_probe,
		.repair = xrep_probe,
	पूर्ण,
	[XFS_SCRUB_TYPE_SB] = अणु		/* superblock */
		.type	= ST_PERAG,
		.setup	= xchk_setup_fs,
		.scrub	= xchk_superblock,
		.repair	= xrep_superblock,
	पूर्ण,
	[XFS_SCRUB_TYPE_AGF] = अणु	/* agf */
		.type	= ST_PERAG,
		.setup	= xchk_setup_fs,
		.scrub	= xchk_agf,
		.repair	= xrep_agf,
	पूर्ण,
	[XFS_SCRUB_TYPE_AGFL]= अणु	/* agfl */
		.type	= ST_PERAG,
		.setup	= xchk_setup_fs,
		.scrub	= xchk_agfl,
		.repair	= xrep_agfl,
	पूर्ण,
	[XFS_SCRUB_TYPE_AGI] = अणु	/* agi */
		.type	= ST_PERAG,
		.setup	= xchk_setup_fs,
		.scrub	= xchk_agi,
		.repair	= xrep_agi,
	पूर्ण,
	[XFS_SCRUB_TYPE_BNOBT] = अणु	/* bnobt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_allocbt,
		.scrub	= xchk_bnobt,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_CNTBT] = अणु	/* cntbt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_allocbt,
		.scrub	= xchk_cntbt,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_INOBT] = अणु	/* inobt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_iallocbt,
		.scrub	= xchk_inobt,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_FINOBT] = अणु	/* finobt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_iallocbt,
		.scrub	= xchk_finobt,
		.has	= xfs_sb_version_hasfinobt,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_RMAPBT] = अणु	/* rmapbt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_rmapbt,
		.scrub	= xchk_rmapbt,
		.has	= xfs_sb_version_hasrmapbt,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_REFCNTBT] = अणु	/* refcountbt */
		.type	= ST_PERAG,
		.setup	= xchk_setup_ag_refcountbt,
		.scrub	= xchk_refcountbt,
		.has	= xfs_sb_version_hasreflink,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_INODE] = अणु	/* inode record */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode,
		.scrub	= xchk_inode,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_BMBTD] = अणु	/* inode data विभाजन */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scrub	= xchk_bmap_data,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_BMBTA] = अणु	/* inode attr विभाजन */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scrub	= xchk_bmap_attr,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_BMBTC] = अणु	/* inode CoW विभाजन */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scrub	= xchk_bmap_cow,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_सूची] = अणु	/* directory */
		.type	= ST_INODE,
		.setup	= xchk_setup_directory,
		.scrub	= xchk_directory,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_XATTR] = अणु	/* extended attributes */
		.type	= ST_INODE,
		.setup	= xchk_setup_xattr,
		.scrub	= xchk_xattr,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_SYMLINK] = अणु	/* symbolic link */
		.type	= ST_INODE,
		.setup	= xchk_setup_symlink,
		.scrub	= xchk_symlink,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_PARENT] = अणु	/* parent poपूर्णांकers */
		.type	= ST_INODE,
		.setup	= xchk_setup_parent,
		.scrub	= xchk_parent,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_RTBITMAP] = अणु	/* realसमय biपंचांगap */
		.type	= ST_FS,
		.setup	= xchk_setup_rt,
		.scrub	= xchk_rtbiपंचांगap,
		.has	= xfs_sb_version_hasrealसमय,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_RTSUM] = अणु	/* realसमय summary */
		.type	= ST_FS,
		.setup	= xchk_setup_rt,
		.scrub	= xchk_rtsummary,
		.has	= xfs_sb_version_hasrealसमय,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_UQUOTA] = अणु	/* user quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scrub	= xchk_quota,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_GQUOTA] = अणु	/* group quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scrub	= xchk_quota,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_PQUOTA] = अणु	/* project quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scrub	= xchk_quota,
		.repair	= xrep_notsupported,
	पूर्ण,
	[XFS_SCRUB_TYPE_FSCOUNTERS] = अणु	/* fs summary counters */
		.type	= ST_FS,
		.setup	= xchk_setup_fscounters,
		.scrub	= xchk_fscounters,
		.repair	= xrep_notsupported,
	पूर्ण,
पूर्ण;

/* This isn't a stable feature, warn once per day. */
अटल अंतरभूत व्योम
xchk_experimental_warning(
	काष्ठा xfs_mount	*mp)
अणु
	अटल काष्ठा ratelimit_state scrub_warning = RATELIMIT_STATE_INIT(
			"xchk_warning", 86400 * HZ, 1);
	ratelimit_set_flags(&scrub_warning, RATELIMIT_MSG_ON_RELEASE);

	अगर (__ratelimit(&scrub_warning))
		xfs_alert(mp,
"EXPERIMENTAL online scrub feature in use. Use at your own risk!");
पूर्ण

अटल पूर्णांक
xchk_validate_inमाला_दो(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_scrub_metadata	*sm)
अणु
	पूर्णांक				error;
	स्थिर काष्ठा xchk_meta_ops	*ops;

	error = -EINVAL;
	/* Check our inमाला_दो. */
	sm->sm_flags &= ~XFS_SCRUB_FLAGS_OUT;
	अगर (sm->sm_flags & ~XFS_SCRUB_FLAGS_IN)
		जाओ out;
	/* sm_reserved[] must be zero */
	अगर (स_प्रथम_inv(sm->sm_reserved, 0, माप(sm->sm_reserved)))
		जाओ out;

	error = -ENOENT;
	/* Do we know about this type of metadata? */
	अगर (sm->sm_type >= XFS_SCRUB_TYPE_NR)
		जाओ out;
	ops = &meta_scrub_ops[sm->sm_type];
	अगर (ops->setup == शून्य || ops->scrub == शून्य)
		जाओ out;
	/* Does this fs even support this type of metadata? */
	अगर (ops->has && !ops->has(&mp->m_sb))
		जाओ out;

	error = -EINVAL;
	/* restricting fields must be appropriate क्रम type */
	चयन (ops->type) अणु
	हाल ST_NONE:
	हाल ST_FS:
		अगर (sm->sm_ino || sm->sm_gen || sm->sm_agno)
			जाओ out;
		अवरोध;
	हाल ST_PERAG:
		अगर (sm->sm_ino || sm->sm_gen ||
		    sm->sm_agno >= mp->m_sb.sb_agcount)
			जाओ out;
		अवरोध;
	हाल ST_INODE:
		अगर (sm->sm_agno || (sm->sm_gen && !sm->sm_ino))
			जाओ out;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	/*
	 * We only want to repair पढ़ो-ग_लिखो v5+ fileप्रणालीs.  Defer the check
	 * क्रम ops->repair until after our scrub confirms that we need to
	 * perक्रमm repairs so that we aव्योम failing due to not supporting
	 * repairing an object that करोesn't need repairs.
	 */
	अगर (sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR) अणु
		error = -EOPNOTSUPP;
		अगर (!xfs_sb_version_hascrc(&mp->m_sb))
			जाओ out;

		error = -EROFS;
		अगर (mp->m_flags & XFS_MOUNT_RDONLY)
			जाओ out;
	पूर्ण

	error = 0;
out:
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_XFS_ONLINE_REPAIR
अटल अंतरभूत व्योम xchk_posपंचांगortem(काष्ठा xfs_scrub *sc)
अणु
	/*
	 * Userspace asked us to repair something, we repaired it, rescanned
	 * it, and the rescan says it's still broken.  Scream about this in
	 * the प्रणाली logs.
	 */
	अगर ((sc->sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR) &&
	    (sc->sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
				 XFS_SCRUB_OFLAG_XCORRUPT)))
		xrep_failure(sc->mp);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xchk_posपंचांगortem(काष्ठा xfs_scrub *sc)
अणु
	/*
	 * Userspace asked us to scrub something, it's broken, and we have no
	 * way of fixing it.  Scream in the logs.
	 */
	अगर (sc->sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
				XFS_SCRUB_OFLAG_XCORRUPT))
		xfs_alert_ratelimited(sc->mp,
				"Corruption detected during scrub.");
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_ONLINE_REPAIR */

/* Dispatch metadata scrubbing. */
पूर्णांक
xfs_scrub_metadata(
	काष्ठा file			*file,
	काष्ठा xfs_scrub_metadata	*sm)
अणु
	काष्ठा xfs_scrub		sc = अणु
		.file			= file,
		.sm			= sm,
		.sa			= अणु
			.agno		= शून्यAGNUMBER,
		पूर्ण,
	पूर्ण;
	काष्ठा xfs_mount		*mp = XFS_I(file_inode(file))->i_mount;
	पूर्णांक				error = 0;

	sc.mp = mp;

	BUILD_BUG_ON(माप(meta_scrub_ops) !=
		(माप(काष्ठा xchk_meta_ops) * XFS_SCRUB_TYPE_NR));

	trace_xchk_start(XFS_I(file_inode(file)), sm, error);

	/* Forbidden अगर we are shut करोwn or mounted norecovery. */
	error = -ESHUTDOWN;
	अगर (XFS_FORCED_SHUTDOWN(mp))
		जाओ out;
	error = -ENOTRECOVERABLE;
	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY)
		जाओ out;

	error = xchk_validate_inमाला_दो(mp, sm);
	अगर (error)
		जाओ out;

	xchk_experimental_warning(mp);

	sc.ops = &meta_scrub_ops[sm->sm_type];
	sc.sick_mask = xchk_health_mask_क्रम_scrub_type(sm->sm_type);
retry_op:
	/*
	 * When repairs are allowed, prevent मुक्तzing or पढ़ोonly remount जबतक
	 * scrub is running with a real transaction.
	 */
	अगर (sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR) अणु
		error = mnt_want_ग_लिखो_file(sc.file);
		अगर (error)
			जाओ out;
	पूर्ण

	/* Set up क्रम the operation. */
	error = sc.ops->setup(&sc);
	अगर (error)
		जाओ out_tearकरोwn;

	/* Scrub क्रम errors. */
	error = sc.ops->scrub(&sc);
	अगर (!(sc.flags & XCHK_TRY_HARDER) && error == -EDEADLOCK) अणु
		/*
		 * Scrubbers वापस -EDEADLOCK to mean 'try harder'.
		 * Tear करोwn everything we hold, then set up again with
		 * preparation क्रम worst-हाल scenarios.
		 */
		error = xchk_tearकरोwn(&sc, 0);
		अगर (error)
			जाओ out;
		sc.flags |= XCHK_TRY_HARDER;
		जाओ retry_op;
	पूर्ण अन्यथा अगर (error || (sm->sm_flags & XFS_SCRUB_OFLAG_INCOMPLETE))
		जाओ out_tearकरोwn;

	xchk_update_health(&sc);

	अगर ((sc.sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR) &&
	    !(sc.flags & XREP_ALREADY_FIXED)) अणु
		bool needs_fix;

		/* Let debug users क्रमce us पूर्णांकo the repair routines. */
		अगर (XFS_TEST_ERROR(false, mp, XFS_ERRTAG_FORCE_SCRUB_REPAIR))
			sc.sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;

		needs_fix = (sc.sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
						XFS_SCRUB_OFLAG_XCORRUPT |
						XFS_SCRUB_OFLAG_PREEN));
		/*
		 * If userspace asked क्रम a repair but it wasn't necessary,
		 * report that back to userspace.
		 */
		अगर (!needs_fix) अणु
			sc.sm->sm_flags |= XFS_SCRUB_OFLAG_NO_REPAIR_NEEDED;
			जाओ out_nofix;
		पूर्ण

		/*
		 * If it's broken, userspace wants us to fix it, and we haven't
		 * alपढ़ोy tried to fix it, then attempt a repair.
		 */
		error = xrep_attempt(&sc);
		अगर (error == -EAGAIN) अणु
			/*
			 * Either the repair function succeeded or it couldn't
			 * get all the resources it needs; either way, we go
			 * back to the beginning and call the scrub function.
			 */
			error = xchk_tearकरोwn(&sc, 0);
			अगर (error) अणु
				xrep_failure(mp);
				जाओ out;
			पूर्ण
			जाओ retry_op;
		पूर्ण
	पूर्ण

out_nofix:
	xchk_posपंचांगortem(&sc);
out_tearकरोwn:
	error = xchk_tearकरोwn(&sc, error);
out:
	trace_xchk_करोne(XFS_I(file_inode(file)), sm, error);
	अगर (error == -EFSCORRUPTED || error == -EFSBADCRC) अणु
		sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
		error = 0;
	पूर्ण
	वापस error;
पूर्ण
