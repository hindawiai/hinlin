<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mount.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/statfs.h>
#समावेश <linux/compat.h>
#समावेश <linux/parser.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/namei.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/btrfs.h>
#समावेश "delayed-inode.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "print-tree.h"
#समावेश "props.h"
#समावेश "xattr.h"
#समावेश "volumes.h"
#समावेश "export.h"
#समावेश "compression.h"
#समावेश "rcu-string.h"
#समावेश "dev-replace.h"
#समावेश "free-space-cache.h"
#समावेश "backref.h"
#समावेश "space-info.h"
#समावेश "sysfs.h"
#समावेश "zoned.h"
#समावेश "tests/btrfs-tests.h"
#समावेश "block-group.h"
#समावेश "discard.h"
#समावेश "qgroup.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/btrfs.h>

अटल स्थिर काष्ठा super_operations btrfs_super_ops;

/*
 * Types क्रम mounting the शेष subvolume and a subvolume explicitly
 * requested by subvol=/path. That way the callchain is straightक्रमward and we
 * करोn't have to play tricks with the mount options and recursive calls to
 * btrfs_mount.
 *
 * The new btrfs_root_fs_type also servers as a tag क्रम the bdev_holder.
 */
अटल काष्ठा file_प्रणाली_type btrfs_fs_type;
अटल काष्ठा file_प्रणाली_type btrfs_root_fs_type;

अटल पूर्णांक btrfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);

/*
 * Generally the error codes correspond to their respective errors, but there
 * are a few special हालs.
 *
 * EUCLEAN: Any sort of corruption that we encounter.  The tree-checker क्रम
 *          instance will वापस EUCLEAN अगर any of the blocks are corrupted in
 *          a way that is problematic.  We want to reserve EUCLEAN क्रम these
 *          sort of corruptions.
 *
 * EROFS: If we check BTRFS_FS_STATE_ERROR and fail out with a वापस error, we
 *        need to use EROFS क्रम this हाल.  We will have no idea of the
 *        original failure, that will have been reported at the समय we tripped
 *        over the error.  Each subsequent error that करोesn't have any context
 *        of the original error should use EROFS when handling BTRFS_FS_STATE_ERROR.
 */
स्थिर अक्षर * __attribute_स्थिर__ btrfs_decode_error(पूर्णांक त्रुटि_सं)
अणु
	अक्षर *errstr = "unknown";

	चयन (त्रुटि_सं) अणु
	हाल -ENOENT:		/* -2 */
		errstr = "No such entry";
		अवरोध;
	हाल -EIO:		/* -5 */
		errstr = "IO failure";
		अवरोध;
	हाल -ENOMEM:		/* -12*/
		errstr = "Out of memory";
		अवरोध;
	हाल -EEXIST:		/* -17 */
		errstr = "Object already exists";
		अवरोध;
	हाल -ENOSPC:		/* -28 */
		errstr = "No space left";
		अवरोध;
	हाल -EROFS:		/* -30 */
		errstr = "Readonly filesystem";
		अवरोध;
	हाल -EOPNOTSUPP:	/* -95 */
		errstr = "Operation not supported";
		अवरोध;
	हाल -EUCLEAN:		/* -117 */
		errstr = "Filesystem corrupted";
		अवरोध;
	हाल -EDQUOT:		/* -122 */
		errstr = "Quota exceeded";
		अवरोध;
	पूर्ण

	वापस errstr;
पूर्ण

/*
 * __btrfs_handle_fs_error decodes expected errors from the caller and
 * invokes the appropriate error response.
 */
__cold
व्योम __btrfs_handle_fs_error(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *function,
		       अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा super_block *sb = fs_info->sb;
#अगर_घोषित CONFIG_PRINTK
	स्थिर अक्षर *errstr;
#पूर्ण_अगर

	/*
	 * Special हाल: अगर the error is EROFS, and we're alपढ़ोy
	 * under SB_RDONLY, then it is safe here.
	 */
	अगर (त्रुटि_सं == -EROFS && sb_rकरोnly(sb))
  		वापस;

#अगर_घोषित CONFIG_PRINTK
	errstr = btrfs_decode_error(त्रुटि_सं);
	अगर (fmt) अणु
		काष्ठा va_क्रमmat vaf;
		बहु_सूची args;

		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;

		pr_crit("BTRFS: error (device %s) in %s:%d: errno=%d %s (%pV)\n",
			sb->s_id, function, line, त्रुटि_सं, errstr, &vaf);
		बहु_पूर्ण(args);
	पूर्ण अन्यथा अणु
		pr_crit("BTRFS: error (device %s) in %s:%d: errno=%d %s\n",
			sb->s_id, function, line, त्रुटि_सं, errstr);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Today we only save the error info to memory.  Long term we'll
	 * also send it करोwn to the disk
	 */
	set_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state);

	/* Don't go through full error handling during mount */
	अगर (!(sb->s_flags & SB_BORN))
		वापस;

	अगर (sb_rकरोnly(sb))
		वापस;

	btrfs_discard_stop(fs_info);

	/* btrfs handle error by क्रमcing the fileप्रणाली पढ़ोonly */
	btrfs_set_sb_rकरोnly(sb);
	btrfs_info(fs_info, "forced readonly");
	/*
	 * Note that a running device replace operation is not canceled here
	 * although there is no way to update the progress. It would add the
	 * risk of a deadlock, thereक्रमe the canceling is omitted. The only
	 * penalty is that some I/O reमुख्यs active until the procedure
	 * completes. The next समय when the fileप्रणाली is mounted writable
	 * again, the device replace operation जारीs.
	 */
पूर्ण

#अगर_घोषित CONFIG_PRINTK
अटल स्थिर अक्षर * स्थिर logtypes[] = अणु
	"emergency",
	"alert",
	"critical",
	"error",
	"warning",
	"notice",
	"info",
	"debug",
पूर्ण;


/*
 * Use one ratelimit state per log level so that a flood of less important
 * messages करोesn't cause more important ones to be dropped.
 */
अटल काष्ठा ratelimit_state prपूर्णांकk_limits[] = अणु
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[0], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[1], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[2], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[3], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[4], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[5], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[6], DEFAULT_RATELIMIT_INTERVAL, 100),
	RATELIMIT_STATE_INIT(prपूर्णांकk_limits[7], DEFAULT_RATELIMIT_INTERVAL, 100),
पूर्ण;

व्योम __cold btrfs_prपूर्णांकk(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *fmt, ...)
अणु
	अक्षर lvl[PRINTK_MAX_SINGLE_HEADER_LEN + 1] = "\0";
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक kern_level;
	स्थिर अक्षर *type = logtypes[4];
	काष्ठा ratelimit_state *ratelimit = &prपूर्णांकk_limits[4];

	बहु_शुरू(args, fmt);

	जबतक ((kern_level = prपूर्णांकk_get_level(fmt)) != 0) अणु
		माप_प्रकार size = prपूर्णांकk_skip_level(fmt) - fmt;

		अगर (kern_level >= '0' && kern_level <= '7') अणु
			स_नकल(lvl, fmt,  size);
			lvl[size] = '\0';
			type = logtypes[kern_level - '0'];
			ratelimit = &prपूर्णांकk_limits[kern_level - '0'];
		पूर्ण
		fmt += size;
	पूर्ण

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (__ratelimit(ratelimit)) अणु
		अगर (fs_info)
			prपूर्णांकk("%sBTRFS %s (device %s): %pV\n", lvl, type,
				fs_info->sb->s_id, &vaf);
		अन्यथा
			prपूर्णांकk("%sBTRFS %s: %pV\n", lvl, type, &vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर

#अगर BITS_PER_LONG == 32
व्योम __cold btrfs_warn_32bit_limit(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!test_and_set_bit(BTRFS_FS_32BIT_WARN, &fs_info->flags)) अणु
		btrfs_warn(fs_info, "reaching 32bit limit for logical addresses");
		btrfs_warn(fs_info,
"due to page cache limit on 32bit systems, btrfs can't access metadata at or beyond %lluT",
			   BTRFS_32BIT_MAX_खाता_SIZE >> 40);
		btrfs_warn(fs_info,
			   "please consider upgrading to 64bit kernel/hardware");
	पूर्ण
पूर्ण

व्योम __cold btrfs_err_32bit_limit(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!test_and_set_bit(BTRFS_FS_32BIT_ERROR, &fs_info->flags)) अणु
		btrfs_err(fs_info, "reached 32bit limit for logical addresses");
		btrfs_err(fs_info,
"due to page cache limit on 32bit systems, metadata beyond %lluT can't be accessed",
			  BTRFS_32BIT_MAX_खाता_SIZE >> 40);
		btrfs_err(fs_info,
			   "please consider upgrading to 64bit kernel/hardware");
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * We only mark the transaction पातed and then set the file प्रणाली पढ़ो-only.
 * This will prevent new transactions from starting or trying to join this
 * one.
 *
 * This means that error recovery at the call site is limited to मुक्तing
 * any local memory allocations and passing the error code up without
 * further cleanup. The transaction should complete as it normally would
 * in the call path but will वापस -EIO.
 *
 * We'll complete the cleanup in btrfs_end_transaction and
 * btrfs_commit_transaction.
 */
__cold
व्योम __btrfs_पात_transaction(काष्ठा btrfs_trans_handle *trans,
			       स्थिर अक्षर *function,
			       अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;

	WRITE_ONCE(trans->पातed, त्रुटि_सं);
	/* Nothing used. The other thपढ़ोs that have joined this
	 * transaction may be able to जारी. */
	अगर (!trans->dirty && list_empty(&trans->new_bgs)) अणु
		स्थिर अक्षर *errstr;

		errstr = btrfs_decode_error(त्रुटि_सं);
		btrfs_warn(fs_info,
		           "%s:%d: Aborting unused transaction(%s).",
		           function, line, errstr);
		वापस;
	पूर्ण
	WRITE_ONCE(trans->transaction->पातed, त्रुटि_सं);
	/* Wake up anybody who may be रुकोing on this transaction */
	wake_up(&fs_info->transaction_रुको);
	wake_up(&fs_info->transaction_blocked_रुको);
	__btrfs_handle_fs_error(fs_info, function, line, त्रुटि_सं, शून्य);
पूर्ण
/*
 * __btrfs_panic decodes unexpected, fatal errors from the caller,
 * issues an alert, and either panics or BUGs, depending on mount options.
 */
__cold
व्योम __btrfs_panic(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *function,
		   अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...)
अणु
	अक्षर *s_id = "<unknown>";
	स्थिर अक्षर *errstr;
	काष्ठा va_क्रमmat vaf = अणु .fmt = fmt पूर्ण;
	बहु_सूची args;

	अगर (fs_info)
		s_id = fs_info->sb->s_id;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	errstr = btrfs_decode_error(त्रुटि_सं);
	अगर (fs_info && (btrfs_test_opt(fs_info, PANIC_ON_FATAL_ERROR)))
		panic(KERN_CRIT "BTRFS panic (device %s) in %s:%d: %pV (errno=%d %s)\n",
			s_id, function, line, &vaf, त्रुटि_सं, errstr);

	btrfs_crit(fs_info, "panic in %s:%d: %pV (errno=%d %s)",
		   function, line, &vaf, त्रुटि_सं, errstr);
	बहु_पूर्ण(args);
	/* Caller calls BUG() */
पूर्ण

अटल व्योम btrfs_put_super(काष्ठा super_block *sb)
अणु
	बंद_ctree(btrfs_sb(sb));
पूर्ण

क्रमागत अणु
	Opt_acl, Opt_noacl,
	Opt_clear_cache,
	Opt_commit_पूर्णांकerval,
	Opt_compress,
	Opt_compress_क्रमce,
	Opt_compress_क्रमce_type,
	Opt_compress_type,
	Opt_degraded,
	Opt_device,
	Opt_fatal_errors,
	Opt_flushoncommit, Opt_noflushoncommit,
	Opt_max_अंतरभूत,
	Opt_barrier, Opt_nobarrier,
	Opt_datacow, Opt_nodatacow,
	Opt_datasum, Opt_nodatasum,
	Opt_defrag, Opt_nodefrag,
	Opt_discard, Opt_nodiscard,
	Opt_discard_mode,
	Opt_norecovery,
	Opt_ratio,
	Opt_rescan_uuid_tree,
	Opt_skip_balance,
	Opt_space_cache, Opt_no_space_cache,
	Opt_space_cache_version,
	Opt_ssd, Opt_nossd,
	Opt_ssd_spपढ़ो, Opt_nossd_spपढ़ो,
	Opt_subvol,
	Opt_subvol_empty,
	Opt_subvolid,
	Opt_thपढ़ो_pool,
	Opt_treelog, Opt_notreelog,
	Opt_user_subvol_rm_allowed,

	/* Rescue options */
	Opt_rescue,
	Opt_usebackuproot,
	Opt_nologreplay,
	Opt_ignorebadroots,
	Opt_ignoredatacsums,
	Opt_rescue_all,

	/* Deprecated options */
	Opt_recovery,
	Opt_inode_cache, Opt_noinode_cache,

	/* Debugging options */
	Opt_check_पूर्णांकegrity,
	Opt_check_पूर्णांकegrity_including_extent_data,
	Opt_check_पूर्णांकegrity_prपूर्णांक_mask,
	Opt_enospc_debug, Opt_noenospc_debug,
#अगर_घोषित CONFIG_BTRFS_DEBUG
	Opt_fragment_data, Opt_fragment_metadata, Opt_fragment_all,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
	Opt_ref_verअगरy,
#पूर्ण_अगर
	Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_acl, "acl"पूर्ण,
	अणुOpt_noacl, "noacl"पूर्ण,
	अणुOpt_clear_cache, "clear_cache"पूर्ण,
	अणुOpt_commit_पूर्णांकerval, "commit=%u"पूर्ण,
	अणुOpt_compress, "compress"पूर्ण,
	अणुOpt_compress_type, "compress=%s"पूर्ण,
	अणुOpt_compress_क्रमce, "compress-force"पूर्ण,
	अणुOpt_compress_क्रमce_type, "compress-force=%s"पूर्ण,
	अणुOpt_degraded, "degraded"पूर्ण,
	अणुOpt_device, "device=%s"पूर्ण,
	अणुOpt_fatal_errors, "fatal_errors=%s"पूर्ण,
	अणुOpt_flushoncommit, "flushoncommit"पूर्ण,
	अणुOpt_noflushoncommit, "noflushoncommit"पूर्ण,
	अणुOpt_inode_cache, "inode_cache"पूर्ण,
	अणुOpt_noinode_cache, "noinode_cache"पूर्ण,
	अणुOpt_max_अंतरभूत, "max_inline=%s"पूर्ण,
	अणुOpt_barrier, "barrier"पूर्ण,
	अणुOpt_nobarrier, "nobarrier"पूर्ण,
	अणुOpt_datacow, "datacow"पूर्ण,
	अणुOpt_nodatacow, "nodatacow"पूर्ण,
	अणुOpt_datasum, "datasum"पूर्ण,
	अणुOpt_nodatasum, "nodatasum"पूर्ण,
	अणुOpt_defrag, "autodefrag"पूर्ण,
	अणुOpt_nodefrag, "noautodefrag"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_discard_mode, "discard=%s"पूर्ण,
	अणुOpt_nodiscard, "nodiscard"पूर्ण,
	अणुOpt_norecovery, "norecovery"पूर्ण,
	अणुOpt_ratio, "metadata_ratio=%u"पूर्ण,
	अणुOpt_rescan_uuid_tree, "rescan_uuid_tree"पूर्ण,
	अणुOpt_skip_balance, "skip_balance"पूर्ण,
	अणुOpt_space_cache, "space_cache"पूर्ण,
	अणुOpt_no_space_cache, "nospace_cache"पूर्ण,
	अणुOpt_space_cache_version, "space_cache=%s"पूर्ण,
	अणुOpt_ssd, "ssd"पूर्ण,
	अणुOpt_nossd, "nossd"पूर्ण,
	अणुOpt_ssd_spपढ़ो, "ssd_spread"पूर्ण,
	अणुOpt_nossd_spपढ़ो, "nossd_spread"पूर्ण,
	अणुOpt_subvol, "subvol=%s"पूर्ण,
	अणुOpt_subvol_empty, "subvol="पूर्ण,
	अणुOpt_subvolid, "subvolid=%s"पूर्ण,
	अणुOpt_thपढ़ो_pool, "thread_pool=%u"पूर्ण,
	अणुOpt_treelog, "treelog"पूर्ण,
	अणुOpt_notreelog, "notreelog"पूर्ण,
	अणुOpt_user_subvol_rm_allowed, "user_subvol_rm_allowed"पूर्ण,

	/* Rescue options */
	अणुOpt_rescue, "rescue=%s"पूर्ण,
	/* Deprecated, with alias rescue=nologreplay */
	अणुOpt_nologreplay, "nologreplay"पूर्ण,
	/* Deprecated, with alias rescue=usebackuproot */
	अणुOpt_usebackuproot, "usebackuproot"पूर्ण,

	/* Deprecated options */
	अणुOpt_recovery, "recovery"पूर्ण,

	/* Debugging options */
	अणुOpt_check_पूर्णांकegrity, "check_int"पूर्ण,
	अणुOpt_check_पूर्णांकegrity_including_extent_data, "check_int_data"पूर्ण,
	अणुOpt_check_पूर्णांकegrity_prपूर्णांक_mask, "check_int_print_mask=%u"पूर्ण,
	अणुOpt_enospc_debug, "enospc_debug"पूर्ण,
	अणुOpt_noenospc_debug, "noenospc_debug"पूर्ण,
#अगर_घोषित CONFIG_BTRFS_DEBUG
	अणुOpt_fragment_data, "fragment=data"पूर्ण,
	अणुOpt_fragment_metadata, "fragment=metadata"पूर्ण,
	अणुOpt_fragment_all, "fragment=all"पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
	अणुOpt_ref_verअगरy, "ref_verify"पूर्ण,
#पूर्ण_अगर
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल स्थिर match_table_t rescue_tokens = अणु
	अणुOpt_usebackuproot, "usebackuproot"पूर्ण,
	अणुOpt_nologreplay, "nologreplay"पूर्ण,
	अणुOpt_ignorebadroots, "ignorebadroots"पूर्ण,
	अणुOpt_ignorebadroots, "ibadroots"पूर्ण,
	अणुOpt_ignoredatacsums, "ignoredatacsums"पूर्ण,
	अणुOpt_ignoredatacsums, "idatacsums"पूर्ण,
	अणुOpt_rescue_all, "all"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल bool check_ro_option(काष्ठा btrfs_fs_info *fs_info, अचिन्हित दीर्घ opt,
			    स्थिर अक्षर *opt_name)
अणु
	अगर (fs_info->mount_opt & opt) अणु
		btrfs_err(fs_info, "%s must be used with ro mount option",
			  opt_name);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक parse_rescue_options(काष्ठा btrfs_fs_info *info, स्थिर अक्षर *options)
अणु
	अक्षर *opts;
	अक्षर *orig;
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = 0;

	opts = kstrdup(options, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;
	orig = opts;

	जबतक ((p = strsep(&opts, ":")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;
		token = match_token(p, rescue_tokens, args);
		चयन (token)अणु
		हाल Opt_usebackuproot:
			btrfs_info(info,
				   "trying to use backup root at mount time");
			btrfs_set_opt(info->mount_opt, USEBACKUPROOT);
			अवरोध;
		हाल Opt_nologreplay:
			btrfs_set_and_info(info, NOLOGREPLAY,
					   "disabling log replay at mount time");
			अवरोध;
		हाल Opt_ignorebadroots:
			btrfs_set_and_info(info, IGNOREBADROOTS,
					   "ignoring bad roots");
			अवरोध;
		हाल Opt_ignoredatacsums:
			btrfs_set_and_info(info, IGNOREDATACSUMS,
					   "ignoring data csums");
			अवरोध;
		हाल Opt_rescue_all:
			btrfs_info(info, "enabling all of the rescue options");
			btrfs_set_and_info(info, IGNOREDATACSUMS,
					   "ignoring data csums");
			btrfs_set_and_info(info, IGNOREBADROOTS,
					   "ignoring bad roots");
			btrfs_set_and_info(info, NOLOGREPLAY,
					   "disabling log replay at mount time");
			अवरोध;
		हाल Opt_err:
			btrfs_info(info, "unrecognized rescue option '%s'", p);
			ret = -EINVAL;
			जाओ out;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण
out:
	kमुक्त(orig);
	वापस ret;
पूर्ण

/*
 * Regular mount options parser.  Everything that is needed only when
 * पढ़ोing in a new superblock is parsed here.
 * XXX JDM: This needs to be cleaned up क्रम remount.
 */
पूर्णांक btrfs_parse_options(काष्ठा btrfs_fs_info *info, अक्षर *options,
			अचिन्हित दीर्घ new_flags)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *p, *num;
	पूर्णांक पूर्णांकarg;
	पूर्णांक ret = 0;
	अक्षर *compress_type;
	bool compress_क्रमce = false;
	क्रमागत btrfs_compression_type saved_compress_type;
	पूर्णांक saved_compress_level;
	bool saved_compress_क्रमce;
	पूर्णांक no_compress = 0;

	अगर (btrfs_fs_compat_ro(info, FREE_SPACE_TREE))
		btrfs_set_opt(info->mount_opt, FREE_SPACE_TREE);
	अन्यथा अगर (btrfs_मुक्त_space_cache_v1_active(info)) अणु
		अगर (btrfs_is_zoned(info)) अणु
			btrfs_info(info,
			"zoned: clearing existing space cache");
			btrfs_set_super_cache_generation(info->super_copy, 0);
		पूर्ण अन्यथा अणु
			btrfs_set_opt(info->mount_opt, SPACE_CACHE);
		पूर्ण
	पूर्ण

	/*
	 * Even the options are empty, we still need to करो extra check
	 * against new flags
	 */
	अगर (!options)
		जाओ check;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_degraded:
			btrfs_info(info, "allowing degraded mounts");
			btrfs_set_opt(info->mount_opt, DEGRADED);
			अवरोध;
		हाल Opt_subvol:
		हाल Opt_subvol_empty:
		हाल Opt_subvolid:
		हाल Opt_device:
			/*
			 * These are parsed by btrfs_parse_subvol_options or
			 * btrfs_parse_device_options and can be ignored here.
			 */
			अवरोध;
		हाल Opt_nodatasum:
			btrfs_set_and_info(info, NODATASUM,
					   "setting nodatasum");
			अवरोध;
		हाल Opt_datasum:
			अगर (btrfs_test_opt(info, NODATASUM)) अणु
				अगर (btrfs_test_opt(info, NODATACOW))
					btrfs_info(info,
						   "setting datasum, datacow enabled");
				अन्यथा
					btrfs_info(info, "setting datasum");
			पूर्ण
			btrfs_clear_opt(info->mount_opt, NODATACOW);
			btrfs_clear_opt(info->mount_opt, NODATASUM);
			अवरोध;
		हाल Opt_nodatacow:
			अगर (!btrfs_test_opt(info, NODATACOW)) अणु
				अगर (!btrfs_test_opt(info, COMPRESS) ||
				    !btrfs_test_opt(info, FORCE_COMPRESS)) अणु
					btrfs_info(info,
						   "setting nodatacow, compression disabled");
				पूर्ण अन्यथा अणु
					btrfs_info(info, "setting nodatacow");
				पूर्ण
			पूर्ण
			btrfs_clear_opt(info->mount_opt, COMPRESS);
			btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
			btrfs_set_opt(info->mount_opt, NODATACOW);
			btrfs_set_opt(info->mount_opt, NODATASUM);
			अवरोध;
		हाल Opt_datacow:
			btrfs_clear_and_info(info, NODATACOW,
					     "setting datacow");
			अवरोध;
		हाल Opt_compress_क्रमce:
		हाल Opt_compress_क्रमce_type:
			compress_क्रमce = true;
			fallthrough;
		हाल Opt_compress:
		हाल Opt_compress_type:
			saved_compress_type = btrfs_test_opt(info,
							     COMPRESS) ?
				info->compress_type : BTRFS_COMPRESS_NONE;
			saved_compress_क्रमce =
				btrfs_test_opt(info, FORCE_COMPRESS);
			saved_compress_level = info->compress_level;
			अगर (token == Opt_compress ||
			    token == Opt_compress_क्रमce ||
			    म_भेदन(args[0].from, "zlib", 4) == 0) अणु
				compress_type = "zlib";

				info->compress_type = BTRFS_COMPRESS_ZLIB;
				info->compress_level = BTRFS_ZLIB_DEFAULT_LEVEL;
				/*
				 * args[0] contains uninitialized data since
				 * क्रम these tokens we करोn't expect any
				 * parameter.
				 */
				अगर (token != Opt_compress &&
				    token != Opt_compress_क्रमce)
					info->compress_level =
					  btrfs_compress_str2level(
							BTRFS_COMPRESS_ZLIB,
							args[0].from + 4);
				btrfs_set_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, NODATACOW);
				btrfs_clear_opt(info->mount_opt, NODATASUM);
				no_compress = 0;
			पूर्ण अन्यथा अगर (म_भेदन(args[0].from, "lzo", 3) == 0) अणु
				compress_type = "lzo";
				info->compress_type = BTRFS_COMPRESS_LZO;
				info->compress_level = 0;
				btrfs_set_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, NODATACOW);
				btrfs_clear_opt(info->mount_opt, NODATASUM);
				btrfs_set_fs_incompat(info, COMPRESS_LZO);
				no_compress = 0;
			पूर्ण अन्यथा अगर (म_भेदन(args[0].from, "zstd", 4) == 0) अणु
				compress_type = "zstd";
				info->compress_type = BTRFS_COMPRESS_ZSTD;
				info->compress_level =
					btrfs_compress_str2level(
							 BTRFS_COMPRESS_ZSTD,
							 args[0].from + 4);
				btrfs_set_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, NODATACOW);
				btrfs_clear_opt(info->mount_opt, NODATASUM);
				btrfs_set_fs_incompat(info, COMPRESS_ZSTD);
				no_compress = 0;
			पूर्ण अन्यथा अगर (म_भेदन(args[0].from, "no", 2) == 0) अणु
				compress_type = "no";
				info->compress_level = 0;
				info->compress_type = 0;
				btrfs_clear_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
				compress_क्रमce = false;
				no_compress++;
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (compress_क्रमce) अणु
				btrfs_set_opt(info->mount_opt, FORCE_COMPRESS);
			पूर्ण अन्यथा अणु
				/*
				 * If we remount from compress-क्रमce=xxx to
				 * compress=xxx, we need clear FORCE_COMPRESS
				 * flag, otherwise, there is no way क्रम users
				 * to disable क्रमcible compression separately.
				 */
				btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
			पूर्ण
			अगर (no_compress == 1) अणु
				btrfs_info(info, "use no compression");
			पूर्ण अन्यथा अगर ((info->compress_type != saved_compress_type) ||
				   (compress_क्रमce != saved_compress_क्रमce) ||
				   (info->compress_level != saved_compress_level)) अणु
				btrfs_info(info, "%s %s compression, level %d",
					   (compress_क्रमce) ? "force" : "use",
					   compress_type, info->compress_level);
			पूर्ण
			compress_क्रमce = false;
			अवरोध;
		हाल Opt_ssd:
			btrfs_set_and_info(info, SSD,
					   "enabling ssd optimizations");
			btrfs_clear_opt(info->mount_opt, NOSSD);
			अवरोध;
		हाल Opt_ssd_spपढ़ो:
			btrfs_set_and_info(info, SSD,
					   "enabling ssd optimizations");
			btrfs_set_and_info(info, SSD_SPREAD,
					   "using spread ssd allocation scheme");
			btrfs_clear_opt(info->mount_opt, NOSSD);
			अवरोध;
		हाल Opt_nossd:
			btrfs_set_opt(info->mount_opt, NOSSD);
			btrfs_clear_and_info(info, SSD,
					     "not using ssd optimizations");
			fallthrough;
		हाल Opt_nossd_spपढ़ो:
			btrfs_clear_and_info(info, SSD_SPREAD,
					     "not using spread ssd allocation scheme");
			अवरोध;
		हाल Opt_barrier:
			btrfs_clear_and_info(info, NOBARRIER,
					     "turning on barriers");
			अवरोध;
		हाल Opt_nobarrier:
			btrfs_set_and_info(info, NOBARRIER,
					   "turning off barriers");
			अवरोध;
		हाल Opt_thपढ़ो_pool:
			ret = match_पूर्णांक(&args[0], &पूर्णांकarg);
			अगर (ret) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (पूर्णांकarg == 0) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			info->thपढ़ो_pool_size = पूर्णांकarg;
			अवरोध;
		हाल Opt_max_अंतरभूत:
			num = match_strdup(&args[0]);
			अगर (num) अणु
				info->max_अंतरभूत = memparse(num, शून्य);
				kमुक्त(num);

				अगर (info->max_अंतरभूत) अणु
					info->max_अंतरभूत = min_t(u64,
						info->max_अंतरभूत,
						info->sectorsize);
				पूर्ण
				btrfs_info(info, "max_inline at %llu",
					   info->max_अंतरभूत);
			पूर्ण अन्यथा अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_acl:
#अगर_घोषित CONFIG_BTRFS_FS_POSIX_ACL
			info->sb->s_flags |= SB_POSIXACL;
			अवरोध;
#अन्यथा
			btrfs_err(info, "support for ACL not compiled in!");
			ret = -EINVAL;
			जाओ out;
#पूर्ण_अगर
		हाल Opt_noacl:
			info->sb->s_flags &= ~SB_POSIXACL;
			अवरोध;
		हाल Opt_notreelog:
			btrfs_set_and_info(info, NOTREELOG,
					   "disabling tree log");
			अवरोध;
		हाल Opt_treelog:
			btrfs_clear_and_info(info, NOTREELOG,
					     "enabling tree log");
			अवरोध;
		हाल Opt_norecovery:
		हाल Opt_nologreplay:
			btrfs_warn(info,
		"'nologreplay' is deprecated, use 'rescue=nologreplay' instead");
			btrfs_set_and_info(info, NOLOGREPLAY,
					   "disabling log replay at mount time");
			अवरोध;
		हाल Opt_flushoncommit:
			btrfs_set_and_info(info, FLUSHONCOMMIT,
					   "turning on flush-on-commit");
			अवरोध;
		हाल Opt_noflushoncommit:
			btrfs_clear_and_info(info, FLUSHONCOMMIT,
					     "turning off flush-on-commit");
			अवरोध;
		हाल Opt_ratio:
			ret = match_पूर्णांक(&args[0], &पूर्णांकarg);
			अगर (ret)
				जाओ out;
			info->metadata_ratio = पूर्णांकarg;
			btrfs_info(info, "metadata ratio %u",
				   info->metadata_ratio);
			अवरोध;
		हाल Opt_discard:
		हाल Opt_discard_mode:
			अगर (token == Opt_discard ||
			    म_भेद(args[0].from, "sync") == 0) अणु
				btrfs_clear_opt(info->mount_opt, DISCARD_ASYNC);
				btrfs_set_and_info(info, DISCARD_SYNC,
						   "turning on sync discard");
			पूर्ण अन्यथा अगर (म_भेद(args[0].from, "async") == 0) अणु
				btrfs_clear_opt(info->mount_opt, DISCARD_SYNC);
				btrfs_set_and_info(info, DISCARD_ASYNC,
						   "turning on async discard");
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_nodiscard:
			btrfs_clear_and_info(info, DISCARD_SYNC,
					     "turning off discard");
			btrfs_clear_and_info(info, DISCARD_ASYNC,
					     "turning off async discard");
			अवरोध;
		हाल Opt_space_cache:
		हाल Opt_space_cache_version:
			अगर (token == Opt_space_cache ||
			    म_भेद(args[0].from, "v1") == 0) अणु
				btrfs_clear_opt(info->mount_opt,
						FREE_SPACE_TREE);
				btrfs_set_and_info(info, SPACE_CACHE,
					   "enabling disk space caching");
			पूर्ण अन्यथा अगर (म_भेद(args[0].from, "v2") == 0) अणु
				btrfs_clear_opt(info->mount_opt,
						SPACE_CACHE);
				btrfs_set_and_info(info, FREE_SPACE_TREE,
						   "enabling free space tree");
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_rescan_uuid_tree:
			btrfs_set_opt(info->mount_opt, RESCAN_UUID_TREE);
			अवरोध;
		हाल Opt_no_space_cache:
			अगर (btrfs_test_opt(info, SPACE_CACHE)) अणु
				btrfs_clear_and_info(info, SPACE_CACHE,
					     "disabling disk space caching");
			पूर्ण
			अगर (btrfs_test_opt(info, FREE_SPACE_TREE)) अणु
				btrfs_clear_and_info(info, FREE_SPACE_TREE,
					     "disabling free space tree");
			पूर्ण
			अवरोध;
		हाल Opt_inode_cache:
		हाल Opt_noinode_cache:
			btrfs_warn(info,
	"the 'inode_cache' option is deprecated and has no effect since 5.11");
			अवरोध;
		हाल Opt_clear_cache:
			btrfs_set_and_info(info, CLEAR_CACHE,
					   "force clearing of disk cache");
			अवरोध;
		हाल Opt_user_subvol_rm_allowed:
			btrfs_set_opt(info->mount_opt, USER_SUBVOL_RM_ALLOWED);
			अवरोध;
		हाल Opt_enospc_debug:
			btrfs_set_opt(info->mount_opt, ENOSPC_DEBUG);
			अवरोध;
		हाल Opt_noenospc_debug:
			btrfs_clear_opt(info->mount_opt, ENOSPC_DEBUG);
			अवरोध;
		हाल Opt_defrag:
			btrfs_set_and_info(info, AUTO_DEFRAG,
					   "enabling auto defrag");
			अवरोध;
		हाल Opt_nodefrag:
			btrfs_clear_and_info(info, AUTO_DEFRAG,
					     "disabling auto defrag");
			अवरोध;
		हाल Opt_recovery:
		हाल Opt_usebackuproot:
			btrfs_warn(info,
			"'%s' is deprecated, use 'rescue=usebackuproot' instead",
				   token == Opt_recovery ? "recovery" :
				   "usebackuproot");
			btrfs_info(info,
				   "trying to use backup root at mount time");
			btrfs_set_opt(info->mount_opt, USEBACKUPROOT);
			अवरोध;
		हाल Opt_skip_balance:
			btrfs_set_opt(info->mount_opt, SKIP_BALANCE);
			अवरोध;
#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
		हाल Opt_check_पूर्णांकegrity_including_extent_data:
			btrfs_info(info,
				   "enabling check integrity including extent data");
			btrfs_set_opt(info->mount_opt,
				      CHECK_INTEGRITY_INCLUDING_EXTENT_DATA);
			btrfs_set_opt(info->mount_opt, CHECK_INTEGRITY);
			अवरोध;
		हाल Opt_check_पूर्णांकegrity:
			btrfs_info(info, "enabling check integrity");
			btrfs_set_opt(info->mount_opt, CHECK_INTEGRITY);
			अवरोध;
		हाल Opt_check_पूर्णांकegrity_prपूर्णांक_mask:
			ret = match_पूर्णांक(&args[0], &पूर्णांकarg);
			अगर (ret)
				जाओ out;
			info->check_पूर्णांकegrity_prपूर्णांक_mask = पूर्णांकarg;
			btrfs_info(info, "check_integrity_print_mask 0x%x",
				   info->check_पूर्णांकegrity_prपूर्णांक_mask);
			अवरोध;
#अन्यथा
		हाल Opt_check_पूर्णांकegrity_including_extent_data:
		हाल Opt_check_पूर्णांकegrity:
		हाल Opt_check_पूर्णांकegrity_prपूर्णांक_mask:
			btrfs_err(info,
				  "support for check_integrity* not compiled in!");
			ret = -EINVAL;
			जाओ out;
#पूर्ण_अगर
		हाल Opt_fatal_errors:
			अगर (म_भेद(args[0].from, "panic") == 0)
				btrfs_set_opt(info->mount_opt,
					      PANIC_ON_FATAL_ERROR);
			अन्यथा अगर (म_भेद(args[0].from, "bug") == 0)
				btrfs_clear_opt(info->mount_opt,
					      PANIC_ON_FATAL_ERROR);
			अन्यथा अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_commit_पूर्णांकerval:
			पूर्णांकarg = 0;
			ret = match_पूर्णांक(&args[0], &पूर्णांकarg);
			अगर (ret)
				जाओ out;
			अगर (पूर्णांकarg == 0) अणु
				btrfs_info(info,
					   "using default commit interval %us",
					   BTRFS_DEFAULT_COMMIT_INTERVAL);
				पूर्णांकarg = BTRFS_DEFAULT_COMMIT_INTERVAL;
			पूर्ण अन्यथा अगर (पूर्णांकarg > 300) अणु
				btrfs_warn(info, "excessive commit interval %d",
					   पूर्णांकarg);
			पूर्ण
			info->commit_पूर्णांकerval = पूर्णांकarg;
			अवरोध;
		हाल Opt_rescue:
			ret = parse_rescue_options(info, args[0].from);
			अगर (ret < 0)
				जाओ out;
			अवरोध;
#अगर_घोषित CONFIG_BTRFS_DEBUG
		हाल Opt_fragment_all:
			btrfs_info(info, "fragmenting all space");
			btrfs_set_opt(info->mount_opt, FRAGMENT_DATA);
			btrfs_set_opt(info->mount_opt, FRAGMENT_METADATA);
			अवरोध;
		हाल Opt_fragment_metadata:
			btrfs_info(info, "fragmenting metadata");
			btrfs_set_opt(info->mount_opt,
				      FRAGMENT_METADATA);
			अवरोध;
		हाल Opt_fragment_data:
			btrfs_info(info, "fragmenting data");
			btrfs_set_opt(info->mount_opt, FRAGMENT_DATA);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
		हाल Opt_ref_verअगरy:
			btrfs_info(info, "doing ref verification");
			btrfs_set_opt(info->mount_opt, REF_VERIFY);
			अवरोध;
#पूर्ण_अगर
		हाल Opt_err:
			btrfs_err(info, "unrecognized mount option '%s'", p);
			ret = -EINVAL;
			जाओ out;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
check:
	/* We're read-only, don't have to check. */
	अगर (new_flags & SB_RDONLY)
		जाओ out;

	अगर (check_ro_option(info, BTRFS_MOUNT_NOLOGREPLAY, "nologreplay") ||
	    check_ro_option(info, BTRFS_MOUNT_IGNOREBADROOTS, "ignorebadroots") ||
	    check_ro_option(info, BTRFS_MOUNT_IGNOREDATACSUMS, "ignoredatacsums"))
		ret = -EINVAL;
out:
	अगर (btrfs_fs_compat_ro(info, FREE_SPACE_TREE) &&
	    !btrfs_test_opt(info, FREE_SPACE_TREE) &&
	    !btrfs_test_opt(info, CLEAR_CACHE)) अणु
		btrfs_err(info, "cannot disable free space tree");
		ret = -EINVAL;

	पूर्ण
	अगर (!ret)
		ret = btrfs_check_mountopts_zoned(info);
	अगर (!ret && btrfs_test_opt(info, SPACE_CACHE))
		btrfs_info(info, "disk space caching is enabled");
	अगर (!ret && btrfs_test_opt(info, FREE_SPACE_TREE))
		btrfs_info(info, "using free space tree");
	वापस ret;
पूर्ण

/*
 * Parse mount options that are required early in the mount process.
 *
 * All other options will be parsed on much later in the mount process and
 * only when we need to allocate a new super block.
 */
अटल पूर्णांक btrfs_parse_device_options(स्थिर अक्षर *options, भ_शेषe_t flags,
				      व्योम *holder)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *device_name, *opts, *orig, *p;
	काष्ठा btrfs_device *device = शून्य;
	पूर्णांक error = 0;

	lockdep_निश्चित_held(&uuid_mutex);

	अगर (!options)
		वापस 0;

	/*
	 * strsep changes the string, duplicate it because btrfs_parse_options
	 * माला_लो called later
	 */
	opts = kstrdup(options, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;
	orig = opts;

	जबतक ((p = strsep(&opts, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		अगर (token == Opt_device) अणु
			device_name = match_strdup(&args[0]);
			अगर (!device_name) अणु
				error = -ENOMEM;
				जाओ out;
			पूर्ण
			device = btrfs_scan_one_device(device_name, flags,
					holder);
			kमुक्त(device_name);
			अगर (IS_ERR(device)) अणु
				error = PTR_ERR(device);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(orig);
	वापस error;
पूर्ण

/*
 * Parse mount options that are related to subvolume id
 *
 * The value is later passed to mount_subvol()
 */
अटल पूर्णांक btrfs_parse_subvol_options(स्थिर अक्षर *options, अक्षर **subvol_name,
		u64 *subvol_objectid)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *opts, *orig, *p;
	पूर्णांक error = 0;
	u64 subvolid;

	अगर (!options)
		वापस 0;

	/*
	 * strsep changes the string, duplicate it because
	 * btrfs_parse_device_options माला_लो called later
	 */
	opts = kstrdup(options, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;
	orig = opts;

	जबतक ((p = strsep(&opts, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_subvol:
			kमुक्त(*subvol_name);
			*subvol_name = match_strdup(&args[0]);
			अगर (!*subvol_name) अणु
				error = -ENOMEM;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_subvolid:
			error = match_u64(&args[0], &subvolid);
			अगर (error)
				जाओ out;

			/* we want the original fs_tree */
			अगर (subvolid == 0)
				subvolid = BTRFS_FS_TREE_OBJECTID;

			*subvol_objectid = subvolid;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(orig);
	वापस error;
पूर्ण

अक्षर *btrfs_get_subvol_name_from_objectid(काष्ठा btrfs_fs_info *fs_info,
					  u64 subvol_objectid)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_root *fs_root = शून्य;
	काष्ठा btrfs_root_ref *root_ref;
	काष्ठा btrfs_inode_ref *inode_ref;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path = शून्य;
	अक्षर *name = शून्य, *ptr;
	u64 dirid;
	पूर्णांक len;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	name = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ptr = name + PATH_MAX - 1;
	ptr[0] = '\0';

	/*
	 * Walk up the subvolume trees in the tree of tree roots by root
	 * backrefs until we hit the top-level subvolume.
	 */
	जबतक (subvol_objectid != BTRFS_FS_TREE_OBJECTID) अणु
		key.objectid = subvol_objectid;
		key.type = BTRFS_ROOT_BACKREF_KEY;
		key.offset = (u64)-1;

		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			जाओ err;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			ret = btrfs_previous_item(root, path, subvol_objectid,
						  BTRFS_ROOT_BACKREF_KEY);
			अगर (ret < 0) अणु
				जाओ err;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = -ENOENT;
				जाओ err;
			पूर्ण
		पूर्ण

		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		subvol_objectid = key.offset;

		root_ref = btrfs_item_ptr(path->nodes[0], path->slots[0],
					  काष्ठा btrfs_root_ref);
		len = btrfs_root_ref_name_len(path->nodes[0], root_ref);
		ptr -= len + 1;
		अगर (ptr < name) अणु
			ret = -ENAMETOOLONG;
			जाओ err;
		पूर्ण
		पढ़ो_extent_buffer(path->nodes[0], ptr + 1,
				   (अचिन्हित दीर्घ)(root_ref + 1), len);
		ptr[0] = '/';
		dirid = btrfs_root_ref_dirid(path->nodes[0], root_ref);
		btrfs_release_path(path);

		fs_root = btrfs_get_fs_root(fs_info, subvol_objectid, true);
		अगर (IS_ERR(fs_root)) अणु
			ret = PTR_ERR(fs_root);
			fs_root = शून्य;
			जाओ err;
		पूर्ण

		/*
		 * Walk up the fileप्रणाली tree by inode refs until we hit the
		 * root directory.
		 */
		जबतक (dirid != BTRFS_FIRST_FREE_OBJECTID) अणु
			key.objectid = dirid;
			key.type = BTRFS_INODE_REF_KEY;
			key.offset = (u64)-1;

			ret = btrfs_search_slot(शून्य, fs_root, &key, path, 0, 0);
			अगर (ret < 0) अणु
				जाओ err;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = btrfs_previous_item(fs_root, path, dirid,
							  BTRFS_INODE_REF_KEY);
				अगर (ret < 0) अणु
					जाओ err;
				पूर्ण अन्यथा अगर (ret > 0) अणु
					ret = -ENOENT;
					जाओ err;
				पूर्ण
			पूर्ण

			btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
			dirid = key.offset;

			inode_ref = btrfs_item_ptr(path->nodes[0],
						   path->slots[0],
						   काष्ठा btrfs_inode_ref);
			len = btrfs_inode_ref_name_len(path->nodes[0],
						       inode_ref);
			ptr -= len + 1;
			अगर (ptr < name) अणु
				ret = -ENAMETOOLONG;
				जाओ err;
			पूर्ण
			पढ़ो_extent_buffer(path->nodes[0], ptr + 1,
					   (अचिन्हित दीर्घ)(inode_ref + 1), len);
			ptr[0] = '/';
			btrfs_release_path(path);
		पूर्ण
		btrfs_put_root(fs_root);
		fs_root = शून्य;
	पूर्ण

	btrfs_मुक्त_path(path);
	अगर (ptr == name + PATH_MAX - 1) अणु
		name[0] = '/';
		name[1] = '\0';
	पूर्ण अन्यथा अणु
		स_हटाओ(name, ptr, name + PATH_MAX - ptr);
	पूर्ण
	वापस name;

err:
	btrfs_put_root(fs_root);
	btrfs_मुक्त_path(path);
	kमुक्त(name);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक get_शेष_subvol_objectid(काष्ठा btrfs_fs_info *fs_info, u64 *objectid)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key location;
	u64 dir_id;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * Find the "default" dir item which poपूर्णांकs to the root item that we
	 * will mount by शेष अगर we haven't been given a specअगरic subvolume
	 * to mount.
	 */
	dir_id = btrfs_super_root_dir(fs_info->super_copy);
	di = btrfs_lookup_dir_item(शून्य, root, path, dir_id, "default", 7, 0);
	अगर (IS_ERR(di)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(di);
	पूर्ण
	अगर (!di) अणु
		/*
		 * Ok the शेष dir item isn't there.  This is weird since
		 * it's always been there, but don't freak out, just try and
		 * mount the top-level subvolume.
		 */
		btrfs_मुक्त_path(path);
		*objectid = BTRFS_FS_TREE_OBJECTID;
		वापस 0;
	पूर्ण

	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &location);
	btrfs_मुक्त_path(path);
	*objectid = location.objectid;
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_fill_super(काष्ठा super_block *sb,
			    काष्ठा btrfs_fs_devices *fs_devices,
			    व्योम *data)
अणु
	काष्ठा inode *inode;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	पूर्णांक err;

	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_magic = BTRFS_SUPER_MAGIC;
	sb->s_op = &btrfs_super_ops;
	sb->s_d_op = &btrfs_dentry_operations;
	sb->s_export_op = &btrfs_export_ops;
	sb->s_xattr = btrfs_xattr_handlers;
	sb->s_समय_gran = 1;
#अगर_घोषित CONFIG_BTRFS_FS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#पूर्ण_अगर
	sb->s_flags |= SB_I_VERSION;
	sb->s_अगरlags |= SB_I_CGROUPWB;

	err = super_setup_bdi(sb);
	अगर (err) अणु
		btrfs_err(fs_info, "super_setup_bdi failed");
		वापस err;
	पूर्ण

	err = खोलो_ctree(sb, fs_devices, (अक्षर *)data);
	अगर (err) अणु
		btrfs_err(fs_info, "open_ctree failed");
		वापस err;
	पूर्ण

	inode = btrfs_iget(sb, BTRFS_FIRST_FREE_OBJECTID, fs_info->fs_root);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ fail_बंद;
	पूर्ण

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root) अणु
		err = -ENOMEM;
		जाओ fail_बंद;
	पूर्ण

	cleancache_init_fs(sb);
	sb->s_flags |= SB_ACTIVE;
	वापस 0;

fail_बंद:
	बंद_ctree(fs_info);
	वापस err;
पूर्ण

पूर्णांक btrfs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	काष्ठा btrfs_root *root = fs_info->tree_root;

	trace_btrfs_sync_fs(fs_info, रुको);

	अगर (!रुको) अणु
		filemap_flush(fs_info->btree_inode->i_mapping);
		वापस 0;
	पूर्ण

	btrfs_रुको_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);

	trans = btrfs_attach_transaction_barrier(root);
	अगर (IS_ERR(trans)) अणु
		/* no transaction, करोn't bother */
		अगर (PTR_ERR(trans) == -ENOENT) अणु
			/*
			 * Exit unless we have some pending changes
			 * that need to go through commit
			 */
			अगर (fs_info->pending_changes == 0)
				वापस 0;
			/*
			 * A non-blocking test अगर the fs is frozen. We must not
			 * start a new transaction here otherwise a deadlock
			 * happens. The pending operations are delayed to the
			 * next commit after thawing.
			 */
			अगर (sb_start_ग_लिखो_trylock(sb))
				sb_end_ग_लिखो(sb);
			अन्यथा
				वापस 0;
			trans = btrfs_start_transaction(root, 0);
		पूर्ण
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);
	पूर्ण
	वापस btrfs_commit_transaction(trans);
पूर्ण

अटल व्योम prपूर्णांक_rescue_option(काष्ठा seq_file *seq, स्थिर अक्षर *s, bool *prपूर्णांकed)
अणु
	seq_म_लिखो(seq, "%s%s", (*prपूर्णांकed) ? ":" : ",rescue=", s);
	*prपूर्णांकed = true;
पूर्ण

अटल पूर्णांक btrfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_fs_info *info = btrfs_sb(dentry->d_sb);
	स्थिर अक्षर *compress_type;
	स्थिर अक्षर *subvol_name;
	bool prपूर्णांकed = false;

	अगर (btrfs_test_opt(info, DEGRADED))
		seq_माला_दो(seq, ",degraded");
	अगर (btrfs_test_opt(info, NODATASUM))
		seq_माला_दो(seq, ",nodatasum");
	अगर (btrfs_test_opt(info, NODATACOW))
		seq_माला_दो(seq, ",nodatacow");
	अगर (btrfs_test_opt(info, NOBARRIER))
		seq_माला_दो(seq, ",nobarrier");
	अगर (info->max_अंतरभूत != BTRFS_DEFAULT_MAX_INLINE)
		seq_म_लिखो(seq, ",max_inline=%llu", info->max_अंतरभूत);
	अगर (info->thपढ़ो_pool_size !=  min_t(अचिन्हित दीर्घ,
					     num_online_cpus() + 2, 8))
		seq_म_लिखो(seq, ",thread_pool=%u", info->thपढ़ो_pool_size);
	अगर (btrfs_test_opt(info, COMPRESS)) अणु
		compress_type = btrfs_compress_type2str(info->compress_type);
		अगर (btrfs_test_opt(info, FORCE_COMPRESS))
			seq_म_लिखो(seq, ",compress-force=%s", compress_type);
		अन्यथा
			seq_म_लिखो(seq, ",compress=%s", compress_type);
		अगर (info->compress_level)
			seq_म_लिखो(seq, ":%d", info->compress_level);
	पूर्ण
	अगर (btrfs_test_opt(info, NOSSD))
		seq_माला_दो(seq, ",nossd");
	अगर (btrfs_test_opt(info, SSD_SPREAD))
		seq_माला_दो(seq, ",ssd_spread");
	अन्यथा अगर (btrfs_test_opt(info, SSD))
		seq_माला_दो(seq, ",ssd");
	अगर (btrfs_test_opt(info, NOTREELOG))
		seq_माला_दो(seq, ",notreelog");
	अगर (btrfs_test_opt(info, NOLOGREPLAY))
		prपूर्णांक_rescue_option(seq, "nologreplay", &prपूर्णांकed);
	अगर (btrfs_test_opt(info, USEBACKUPROOT))
		prपूर्णांक_rescue_option(seq, "usebackuproot", &prपूर्णांकed);
	अगर (btrfs_test_opt(info, IGNOREBADROOTS))
		prपूर्णांक_rescue_option(seq, "ignorebadroots", &prपूर्णांकed);
	अगर (btrfs_test_opt(info, IGNOREDATACSUMS))
		prपूर्णांक_rescue_option(seq, "ignoredatacsums", &prपूर्णांकed);
	अगर (btrfs_test_opt(info, FLUSHONCOMMIT))
		seq_माला_दो(seq, ",flushoncommit");
	अगर (btrfs_test_opt(info, DISCARD_SYNC))
		seq_माला_दो(seq, ",discard");
	अगर (btrfs_test_opt(info, DISCARD_ASYNC))
		seq_माला_दो(seq, ",discard=async");
	अगर (!(info->sb->s_flags & SB_POSIXACL))
		seq_माला_दो(seq, ",noacl");
	अगर (btrfs_मुक्त_space_cache_v1_active(info))
		seq_माला_दो(seq, ",space_cache");
	अन्यथा अगर (btrfs_fs_compat_ro(info, FREE_SPACE_TREE))
		seq_माला_दो(seq, ",space_cache=v2");
	अन्यथा
		seq_माला_दो(seq, ",nospace_cache");
	अगर (btrfs_test_opt(info, RESCAN_UUID_TREE))
		seq_माला_दो(seq, ",rescan_uuid_tree");
	अगर (btrfs_test_opt(info, CLEAR_CACHE))
		seq_माला_दो(seq, ",clear_cache");
	अगर (btrfs_test_opt(info, USER_SUBVOL_RM_ALLOWED))
		seq_माला_दो(seq, ",user_subvol_rm_allowed");
	अगर (btrfs_test_opt(info, ENOSPC_DEBUG))
		seq_माला_दो(seq, ",enospc_debug");
	अगर (btrfs_test_opt(info, AUTO_DEFRAG))
		seq_माला_दो(seq, ",autodefrag");
	अगर (btrfs_test_opt(info, SKIP_BALANCE))
		seq_माला_दो(seq, ",skip_balance");
#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	अगर (btrfs_test_opt(info, CHECK_INTEGRITY_INCLUDING_EXTENT_DATA))
		seq_माला_दो(seq, ",check_int_data");
	अन्यथा अगर (btrfs_test_opt(info, CHECK_INTEGRITY))
		seq_माला_दो(seq, ",check_int");
	अगर (info->check_पूर्णांकegrity_prपूर्णांक_mask)
		seq_म_लिखो(seq, ",check_int_print_mask=%d",
				info->check_पूर्णांकegrity_prपूर्णांक_mask);
#पूर्ण_अगर
	अगर (info->metadata_ratio)
		seq_म_लिखो(seq, ",metadata_ratio=%u", info->metadata_ratio);
	अगर (btrfs_test_opt(info, PANIC_ON_FATAL_ERROR))
		seq_माला_दो(seq, ",fatal_errors=panic");
	अगर (info->commit_पूर्णांकerval != BTRFS_DEFAULT_COMMIT_INTERVAL)
		seq_म_लिखो(seq, ",commit=%u", info->commit_पूर्णांकerval);
#अगर_घोषित CONFIG_BTRFS_DEBUG
	अगर (btrfs_test_opt(info, FRAGMENT_DATA))
		seq_माला_दो(seq, ",fragment=data");
	अगर (btrfs_test_opt(info, FRAGMENT_METADATA))
		seq_माला_दो(seq, ",fragment=metadata");
#पूर्ण_अगर
	अगर (btrfs_test_opt(info, REF_VERIFY))
		seq_माला_दो(seq, ",ref_verify");
	seq_म_लिखो(seq, ",subvolid=%llu",
		  BTRFS_I(d_inode(dentry))->root->root_key.objectid);
	subvol_name = btrfs_get_subvol_name_from_objectid(info,
			BTRFS_I(d_inode(dentry))->root->root_key.objectid);
	अगर (!IS_ERR(subvol_name)) अणु
		seq_माला_दो(seq, ",subvol=");
		seq_escape(seq, subvol_name, " \t\n\\");
		kमुक्त(subvol_name);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_test_super(काष्ठा super_block *s, व्योम *data)
अणु
	काष्ठा btrfs_fs_info *p = data;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(s);

	वापस fs_info->fs_devices == p->fs_devices;
पूर्ण

अटल पूर्णांक btrfs_set_super(काष्ठा super_block *s, व्योम *data)
अणु
	पूर्णांक err = set_anon_super(s, data);
	अगर (!err)
		s->s_fs_info = data;
	वापस err;
पूर्ण

/*
 * subvolumes are identअगरied by ino 256
 */
अटल अंतरभूत पूर्णांक is_subvolume_inode(काष्ठा inode *inode)
अणु
	अगर (inode && inode->i_ino == BTRFS_FIRST_FREE_OBJECTID)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा dentry *mount_subvol(स्थिर अक्षर *subvol_name, u64 subvol_objectid,
				   काष्ठा vfsmount *mnt)
अणु
	काष्ठा dentry *root;
	पूर्णांक ret;

	अगर (!subvol_name) अणु
		अगर (!subvol_objectid) अणु
			ret = get_शेष_subvol_objectid(btrfs_sb(mnt->mnt_sb),
							  &subvol_objectid);
			अगर (ret) अणु
				root = ERR_PTR(ret);
				जाओ out;
			पूर्ण
		पूर्ण
		subvol_name = btrfs_get_subvol_name_from_objectid(
					btrfs_sb(mnt->mnt_sb), subvol_objectid);
		अगर (IS_ERR(subvol_name)) अणु
			root = ERR_CAST(subvol_name);
			subvol_name = शून्य;
			जाओ out;
		पूर्ण

	पूर्ण

	root = mount_subtree(mnt, subvol_name);
	/* mount_subtree() drops our reference on the vfsmount. */
	mnt = शून्य;

	अगर (!IS_ERR(root)) अणु
		काष्ठा super_block *s = root->d_sb;
		काष्ठा btrfs_fs_info *fs_info = btrfs_sb(s);
		काष्ठा inode *root_inode = d_inode(root);
		u64 root_objectid = BTRFS_I(root_inode)->root->root_key.objectid;

		ret = 0;
		अगर (!is_subvolume_inode(root_inode)) अणु
			btrfs_err(fs_info, "'%s' is not a valid subvolume",
			       subvol_name);
			ret = -EINVAL;
		पूर्ण
		अगर (subvol_objectid && root_objectid != subvol_objectid) अणु
			/*
			 * This will also catch a race condition where a
			 * subvolume which was passed by ID is नामd and
			 * another subvolume is नामd over the old location.
			 */
			btrfs_err(fs_info,
				  "subvol '%s' does not match subvolid %llu",
				  subvol_name, subvol_objectid);
			ret = -EINVAL;
		पूर्ण
		अगर (ret) अणु
			dput(root);
			root = ERR_PTR(ret);
			deactivate_locked_super(s);
		पूर्ण
	पूर्ण

out:
	mntput(mnt);
	kमुक्त(subvol_name);
	वापस root;
पूर्ण

/*
 * Find a superblock क्रम the given device / mount poपूर्णांक.
 *
 * Note: This is based on mount_bdev from fs/super.c with a few additions
 *       क्रम multiple device setup.  Make sure to keep it in sync.
 */
अटल काष्ठा dentry *btrfs_mount_root(काष्ठा file_प्रणाली_type *fs_type,
		पूर्णांक flags, स्थिर अक्षर *device_name, व्योम *data)
अणु
	काष्ठा block_device *bdev = शून्य;
	काष्ठा super_block *s;
	काष्ठा btrfs_device *device = शून्य;
	काष्ठा btrfs_fs_devices *fs_devices = शून्य;
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	व्योम *new_sec_opts = शून्य;
	भ_शेषe_t mode = FMODE_READ;
	पूर्णांक error = 0;

	अगर (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	अगर (data) अणु
		error = security_sb_eat_lsm_opts(data, &new_sec_opts);
		अगर (error)
			वापस ERR_PTR(error);
	पूर्ण

	/*
	 * Setup a dummy root and fs_info क्रम test/set super.  This is because
	 * we करोn't actually fill this stuff out until खोलो_ctree, but we need
	 * then खोलो_ctree will properly initialize the file प्रणाली specअगरic
	 * settings later.  btrfs_init_fs_info initializes the अटल elements
	 * of the fs_info (locks and such) to make cleanup easier अगर we find a
	 * superblock with our given fs_devices later on at sget() समय.
	 */
	fs_info = kvzalloc(माप(काष्ठा btrfs_fs_info), GFP_KERNEL);
	अगर (!fs_info) अणु
		error = -ENOMEM;
		जाओ error_sec_opts;
	पूर्ण
	btrfs_init_fs_info(fs_info);

	fs_info->super_copy = kzalloc(BTRFS_SUPER_INFO_SIZE, GFP_KERNEL);
	fs_info->super_क्रम_commit = kzalloc(BTRFS_SUPER_INFO_SIZE, GFP_KERNEL);
	अगर (!fs_info->super_copy || !fs_info->super_क्रम_commit) अणु
		error = -ENOMEM;
		जाओ error_fs_info;
	पूर्ण

	mutex_lock(&uuid_mutex);
	error = btrfs_parse_device_options(data, mode, fs_type);
	अगर (error) अणु
		mutex_unlock(&uuid_mutex);
		जाओ error_fs_info;
	पूर्ण

	device = btrfs_scan_one_device(device_name, mode, fs_type);
	अगर (IS_ERR(device)) अणु
		mutex_unlock(&uuid_mutex);
		error = PTR_ERR(device);
		जाओ error_fs_info;
	पूर्ण

	fs_devices = device->fs_devices;
	fs_info->fs_devices = fs_devices;

	error = btrfs_खोलो_devices(fs_devices, mode, fs_type);
	mutex_unlock(&uuid_mutex);
	अगर (error)
		जाओ error_fs_info;

	अगर (!(flags & SB_RDONLY) && fs_devices->rw_devices == 0) अणु
		error = -EACCES;
		जाओ error_बंद_devices;
	पूर्ण

	bdev = fs_devices->latest_bdev;
	s = sget(fs_type, btrfs_test_super, btrfs_set_super, flags | SB_NOSEC,
		 fs_info);
	अगर (IS_ERR(s)) अणु
		error = PTR_ERR(s);
		जाओ error_बंद_devices;
	पूर्ण

	अगर (s->s_root) अणु
		btrfs_बंद_devices(fs_devices);
		btrfs_मुक्त_fs_info(fs_info);
		अगर ((flags ^ s->s_flags) & SB_RDONLY)
			error = -EBUSY;
	पूर्ण अन्यथा अणु
		snम_लिखो(s->s_id, माप(s->s_id), "%pg", bdev);
		btrfs_sb(s)->bdev_holder = fs_type;
		अगर (!म_माला(crc32c_impl(), "generic"))
			set_bit(BTRFS_FS_CSUM_IMPL_FAST, &fs_info->flags);
		error = btrfs_fill_super(s, fs_devices, data);
	पूर्ण
	अगर (!error)
		error = security_sb_set_mnt_opts(s, new_sec_opts, 0, शून्य);
	security_मुक्त_mnt_opts(&new_sec_opts);
	अगर (error) अणु
		deactivate_locked_super(s);
		वापस ERR_PTR(error);
	पूर्ण

	वापस dget(s->s_root);

error_बंद_devices:
	btrfs_बंद_devices(fs_devices);
error_fs_info:
	btrfs_मुक्त_fs_info(fs_info);
error_sec_opts:
	security_मुक्त_mnt_opts(&new_sec_opts);
	वापस ERR_PTR(error);
पूर्ण

/*
 * Mount function which is called by VFS layer.
 *
 * In order to allow mounting a subvolume directly, btrfs uses mount_subtree()
 * which needs vfsmount* of device's root (/).  This means device's root has to
 * be mounted पूर्णांकernally in any हाल.
 *
 * Operation flow:
 *   1. Parse subvol id related options क्रम later use in mount_subvol().
 *
 *   2. Mount device's root (/) by calling vfs_kern_mount().
 *
 *      NOTE: vfs_kern_mount() is used by VFS to call btrfs_mount() in the
 *      first place. In order to aव्योम calling btrfs_mount() again, we use
 *      dअगरferent file_प्रणाली_type which is not रेजिस्टरed to VFS by
 *      रेजिस्टर_fileप्रणाली() (btrfs_root_fs_type). As a result,
 *      btrfs_mount_root() is called. The वापस value will be used by
 *      mount_subtree() in mount_subvol().
 *
 *   3. Call mount_subvol() to get the dentry of subvolume. Since there is
 *      "btrfs subvolume set-default", mount_subvol() is called always.
 */
अटल काष्ठा dentry *btrfs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
		स्थिर अक्षर *device_name, व्योम *data)
अणु
	काष्ठा vfsmount *mnt_root;
	काष्ठा dentry *root;
	अक्षर *subvol_name = शून्य;
	u64 subvol_objectid = 0;
	पूर्णांक error = 0;

	error = btrfs_parse_subvol_options(data, &subvol_name,
					&subvol_objectid);
	अगर (error) अणु
		kमुक्त(subvol_name);
		वापस ERR_PTR(error);
	पूर्ण

	/* mount device's root (/) */
	mnt_root = vfs_kern_mount(&btrfs_root_fs_type, flags, device_name, data);
	अगर (PTR_ERR_OR_ZERO(mnt_root) == -EBUSY) अणु
		अगर (flags & SB_RDONLY) अणु
			mnt_root = vfs_kern_mount(&btrfs_root_fs_type,
				flags & ~SB_RDONLY, device_name, data);
		पूर्ण अन्यथा अणु
			mnt_root = vfs_kern_mount(&btrfs_root_fs_type,
				flags | SB_RDONLY, device_name, data);
			अगर (IS_ERR(mnt_root)) अणु
				root = ERR_CAST(mnt_root);
				kमुक्त(subvol_name);
				जाओ out;
			पूर्ण

			करोwn_ग_लिखो(&mnt_root->mnt_sb->s_umount);
			error = btrfs_remount(mnt_root->mnt_sb, &flags, शून्य);
			up_ग_लिखो(&mnt_root->mnt_sb->s_umount);
			अगर (error < 0) अणु
				root = ERR_PTR(error);
				mntput(mnt_root);
				kमुक्त(subvol_name);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (IS_ERR(mnt_root)) अणु
		root = ERR_CAST(mnt_root);
		kमुक्त(subvol_name);
		जाओ out;
	पूर्ण

	/* mount_subvol() will मुक्त subvol_name and mnt_root */
	root = mount_subvol(subvol_name, subvol_objectid, mnt_root);

out:
	वापस root;
पूर्ण

अटल व्योम btrfs_reमाप_प्रकारhपढ़ो_pool(काष्ठा btrfs_fs_info *fs_info,
				     u32 new_pool_size, u32 old_pool_size)
अणु
	अगर (new_pool_size == old_pool_size)
		वापस;

	fs_info->thपढ़ो_pool_size = new_pool_size;

	btrfs_info(fs_info, "resize thread pool %d -> %d",
	       old_pool_size, new_pool_size);

	btrfs_workqueue_set_max(fs_info->workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->delalloc_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->caching_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_meta_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_meta_ग_लिखो_workers,
				new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_ग_लिखो_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_मुक्तspace_worker, new_pool_size);
	btrfs_workqueue_set_max(fs_info->delayed_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->पढ़ोahead_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->scrub_wr_completion_workers,
				new_pool_size);
पूर्ण

अटल अंतरभूत व्योम btrfs_remount_begin(काष्ठा btrfs_fs_info *fs_info,
				       अचिन्हित दीर्घ old_opts, पूर्णांक flags)
अणु
	अगर (btrfs_raw_test_opt(old_opts, AUTO_DEFRAG) &&
	    (!btrfs_raw_test_opt(fs_info->mount_opt, AUTO_DEFRAG) ||
	     (flags & SB_RDONLY))) अणु
		/* रुको क्रम any defraggers to finish */
		रुको_event(fs_info->transaction_रुको,
			   (atomic_पढ़ो(&fs_info->defrag_running) == 0));
		अगर (flags & SB_RDONLY)
			sync_fileप्रणाली(fs_info->sb);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_remount_cleanup(काष्ठा btrfs_fs_info *fs_info,
					 अचिन्हित दीर्घ old_opts)
अणु
	स्थिर bool cache_opt = btrfs_test_opt(fs_info, SPACE_CACHE);

	/*
	 * We need to cleanup all defragable inodes अगर the स्वतःdefragment is
	 * बंद or the fileप्रणाली is पढ़ो only.
	 */
	अगर (btrfs_raw_test_opt(old_opts, AUTO_DEFRAG) &&
	    (!btrfs_raw_test_opt(fs_info->mount_opt, AUTO_DEFRAG) || sb_rकरोnly(fs_info->sb))) अणु
		btrfs_cleanup_defrag_inodes(fs_info);
	पूर्ण

	/* If we toggled discard async */
	अगर (!btrfs_raw_test_opt(old_opts, DISCARD_ASYNC) &&
	    btrfs_test_opt(fs_info, DISCARD_ASYNC))
		btrfs_discard_resume(fs_info);
	अन्यथा अगर (btrfs_raw_test_opt(old_opts, DISCARD_ASYNC) &&
		 !btrfs_test_opt(fs_info, DISCARD_ASYNC))
		btrfs_discard_cleanup(fs_info);

	/* If we toggled space cache */
	अगर (cache_opt != btrfs_मुक्त_space_cache_v1_active(fs_info))
		btrfs_set_मुक्त_space_cache_v1_active(fs_info, cache_opt);
पूर्ण

अटल पूर्णांक btrfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	अचिन्हित old_flags = sb->s_flags;
	अचिन्हित दीर्घ old_opts = fs_info->mount_opt;
	अचिन्हित दीर्घ old_compress_type = fs_info->compress_type;
	u64 old_max_अंतरभूत = fs_info->max_अंतरभूत;
	u32 old_thपढ़ो_pool_size = fs_info->thपढ़ो_pool_size;
	u32 old_metadata_ratio = fs_info->metadata_ratio;
	पूर्णांक ret;

	sync_fileप्रणाली(sb);
	set_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state);

	अगर (data) अणु
		व्योम *new_sec_opts = शून्य;

		ret = security_sb_eat_lsm_opts(data, &new_sec_opts);
		अगर (!ret)
			ret = security_sb_remount(sb, new_sec_opts);
		security_मुक्त_mnt_opts(&new_sec_opts);
		अगर (ret)
			जाओ restore;
	पूर्ण

	ret = btrfs_parse_options(fs_info, data, *flags);
	अगर (ret)
		जाओ restore;

	btrfs_remount_begin(fs_info, old_opts, *flags);
	btrfs_reमाप_प्रकारhपढ़ो_pool(fs_info,
		fs_info->thपढ़ो_pool_size, old_thपढ़ो_pool_size);

	अगर ((bool)btrfs_test_opt(fs_info, FREE_SPACE_TREE) !=
	    (bool)btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE) &&
	    (!sb_rकरोnly(sb) || (*flags & SB_RDONLY))) अणु
		btrfs_warn(fs_info,
		"remount supports changing free space tree only from ro to rw");
		/* Make sure मुक्त space cache options match the state on disk */
		अगर (btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE)) अणु
			btrfs_set_opt(fs_info->mount_opt, FREE_SPACE_TREE);
			btrfs_clear_opt(fs_info->mount_opt, SPACE_CACHE);
		पूर्ण
		अगर (btrfs_मुक्त_space_cache_v1_active(fs_info)) अणु
			btrfs_clear_opt(fs_info->mount_opt, FREE_SPACE_TREE);
			btrfs_set_opt(fs_info->mount_opt, SPACE_CACHE);
		पूर्ण
	पूर्ण

	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		जाओ out;

	अगर (*flags & SB_RDONLY) अणु
		/*
		 * this also happens on 'umount -rf' or on shutकरोwn, when
		 * the fileप्रणाली is busy.
		 */
		cancel_work_sync(&fs_info->async_reclaim_work);
		cancel_work_sync(&fs_info->async_data_reclaim_work);

		btrfs_discard_cleanup(fs_info);

		/* रुको क्रम the uuid_scan task to finish */
		करोwn(&fs_info->uuid_tree_rescan_sem);
		/* aव्योम complains from lockdep et al. */
		up(&fs_info->uuid_tree_rescan_sem);

		btrfs_set_sb_rकरोnly(sb);

		/*
		 * Setting SB_RDONLY will put the cleaner thपढ़ो to
		 * sleep at the next loop अगर it's alपढ़ोy active.
		 * If it's already asleep, we'll leave unused block
		 * groups on disk until we're mounted पढ़ो-ग_लिखो again
		 * unless we clean them up here.
		 */
		btrfs_delete_unused_bgs(fs_info);

		/*
		 * The cleaner task could be alपढ़ोy running beक्रमe we set the
		 * flag BTRFS_FS_STATE_RO (and SB_RDONLY in the superblock).
		 * We must make sure that after we finish the remount, i.e. after
		 * we call btrfs_commit_super(), the cleaner can no दीर्घer start
		 * a transaction - either because it was dropping a dead root,
		 * running delayed iमाला_दो or deleting an unused block group (the
		 * cleaner picked a block group from the list of unused block
		 * groups beक्रमe we were able to in the previous call to
		 * btrfs_delete_unused_bgs()).
		 */
		रुको_on_bit(&fs_info->flags, BTRFS_FS_CLEANER_RUNNING,
			    TASK_UNINTERRUPTIBLE);

		/*
		 * We've set the superblock to RO mode, so we might have made
		 * the cleaner task sleep without running all pending delayed
		 * iमाला_दो. Go through all the delayed iमाला_दो here, so that अगर an
		 * unmount happens without remounting RW we करोn't end up at
		 * finishing बंद_ctree() with a non-empty list of delayed
		 * iमाला_दो.
		 */
		btrfs_run_delayed_iमाला_दो(fs_info);

		btrfs_dev_replace_suspend_क्रम_unmount(fs_info);
		btrfs_scrub_cancel(fs_info);
		btrfs_छोड़ो_balance(fs_info);

		/*
		 * Pause the qgroup rescan worker अगर it is running. We करोn't want
		 * it to be still running after we are in RO mode, as after that,
		 * by the समय we unmount, it might have left a transaction खोलो,
		 * so we would leak the transaction and/or crash.
		 */
		btrfs_qgroup_रुको_क्रम_completion(fs_info, false);

		ret = btrfs_commit_super(fs_info);
		अगर (ret)
			जाओ restore;
	पूर्ण अन्यथा अणु
		अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
			btrfs_err(fs_info,
				"Remounting read-write after error is not allowed");
			ret = -EINVAL;
			जाओ restore;
		पूर्ण
		अगर (fs_info->fs_devices->rw_devices == 0) अणु
			ret = -EACCES;
			जाओ restore;
		पूर्ण

		अगर (!btrfs_check_rw_degradable(fs_info, शून्य)) अणु
			btrfs_warn(fs_info,
		"too many missing devices, writable remount is not allowed");
			ret = -EACCES;
			जाओ restore;
		पूर्ण

		अगर (btrfs_super_log_root(fs_info->super_copy) != 0) अणु
			btrfs_warn(fs_info,
		"mount required to replay tree-log, cannot remount read-write");
			ret = -EINVAL;
			जाओ restore;
		पूर्ण
		अगर (fs_info->sectorsize < PAGE_SIZE) अणु
			btrfs_warn(fs_info,
	"read-write mount is not yet allowed for sectorsize %u page size %lu",
				   fs_info->sectorsize, PAGE_SIZE);
			ret = -EINVAL;
			जाओ restore;
		पूर्ण

		/*
		 * NOTE: when remounting with a change that करोes ग_लिखोs, करोn't
		 * put it anywhere above this poपूर्णांक, as we are not sure to be
		 * safe to ग_लिखो until we pass the above checks.
		 */
		ret = btrfs_start_pre_rw_mount(fs_info);
		अगर (ret)
			जाओ restore;

		btrfs_clear_sb_rकरोnly(sb);

		set_bit(BTRFS_FS_OPEN, &fs_info->flags);
	पूर्ण
out:
	/*
	 * We need to set SB_I_VERSION here otherwise it'll get cleared by VFS,
	 * since the असलence of the flag means it can be toggled off by remount.
	 */
	*flags |= SB_I_VERSION;

	wake_up_process(fs_info->transaction_kthपढ़ो);
	btrfs_remount_cleanup(fs_info, old_opts);
	btrfs_clear_oneshot_options(fs_info);
	clear_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state);

	वापस 0;

restore:
	/* We've hit an error - don't reset SB_RDONLY */
	अगर (sb_rकरोnly(sb))
		old_flags |= SB_RDONLY;
	अगर (!(old_flags & SB_RDONLY))
		clear_bit(BTRFS_FS_STATE_RO, &fs_info->fs_state);
	sb->s_flags = old_flags;
	fs_info->mount_opt = old_opts;
	fs_info->compress_type = old_compress_type;
	fs_info->max_अंतरभूत = old_max_अंतरभूत;
	btrfs_reमाप_प्रकारhपढ़ो_pool(fs_info,
		old_thपढ़ो_pool_size, fs_info->thपढ़ो_pool_size);
	fs_info->metadata_ratio = old_metadata_ratio;
	btrfs_remount_cleanup(fs_info, old_opts);
	clear_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state);

	वापस ret;
पूर्ण

/* Used to sort the devices by max_avail(descending sort) */
अटल अंतरभूत पूर्णांक btrfs_cmp_device_मुक्त_bytes(स्थिर व्योम *dev_info1,
				       स्थिर व्योम *dev_info2)
अणु
	अगर (((काष्ठा btrfs_device_info *)dev_info1)->max_avail >
	    ((काष्ठा btrfs_device_info *)dev_info2)->max_avail)
		वापस -1;
	अन्यथा अगर (((काष्ठा btrfs_device_info *)dev_info1)->max_avail <
		 ((काष्ठा btrfs_device_info *)dev_info2)->max_avail)
		वापस 1;
	अन्यथा
	वापस 0;
पूर्ण

/*
 * sort the devices by max_avail, in which max मुक्त extent size of each device
 * is stored.(Descending Sort)
 */
अटल अंतरभूत व्योम btrfs_descending_sort_devices(
					काष्ठा btrfs_device_info *devices,
					माप_प्रकार nr_devices)
अणु
	sort(devices, nr_devices, माप(काष्ठा btrfs_device_info),
	     btrfs_cmp_device_मुक्त_bytes, शून्य);
पूर्ण

/*
 * The helper to calc the मुक्त space on the devices that can be used to store
 * file data.
 */
अटल अंतरभूत पूर्णांक btrfs_calc_avail_data_space(काष्ठा btrfs_fs_info *fs_info,
					      u64 *मुक्त_bytes)
अणु
	काष्ठा btrfs_device_info *devices_info;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_device *device;
	u64 type;
	u64 avail_space;
	u64 min_stripe_size;
	पूर्णांक num_stripes = 1;
	पूर्णांक i = 0, nr_devices;
	स्थिर काष्ठा btrfs_raid_attr *rattr;

	/*
	 * We aren't under the device list lock, so this is racy-ish, but good
	 * enough क्रम our purposes.
	 */
	nr_devices = fs_info->fs_devices->खोलो_devices;
	अगर (!nr_devices) अणु
		smp_mb();
		nr_devices = fs_info->fs_devices->खोलो_devices;
		ASSERT(nr_devices);
		अगर (!nr_devices) अणु
			*मुक्त_bytes = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	devices_info = kदो_स्मृति_array(nr_devices, माप(*devices_info),
			       GFP_KERNEL);
	अगर (!devices_info)
		वापस -ENOMEM;

	/* calc min stripe number क्रम data space allocation */
	type = btrfs_data_alloc_profile(fs_info);
	rattr = &btrfs_raid_array[btrfs_bg_flags_to_raid_index(type)];

	अगर (type & BTRFS_BLOCK_GROUP_RAID0)
		num_stripes = nr_devices;
	अन्यथा अगर (type & BTRFS_BLOCK_GROUP_RAID1)
		num_stripes = 2;
	अन्यथा अगर (type & BTRFS_BLOCK_GROUP_RAID1C3)
		num_stripes = 3;
	अन्यथा अगर (type & BTRFS_BLOCK_GROUP_RAID1C4)
		num_stripes = 4;
	अन्यथा अगर (type & BTRFS_BLOCK_GROUP_RAID10)
		num_stripes = 4;

	/* Adjust क्रम more than 1 stripe per device */
	min_stripe_size = rattr->dev_stripes * BTRFS_STRIPE_LEN;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(device, &fs_devices->devices, dev_list) अणु
		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
						&device->dev_state) ||
		    !device->bdev ||
		    test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state))
			जारी;

		अगर (i >= nr_devices)
			अवरोध;

		avail_space = device->total_bytes - device->bytes_used;

		/* align with stripe_len */
		avail_space = roundकरोwn(avail_space, BTRFS_STRIPE_LEN);

		/*
		 * In order to aव्योम overwriting the superblock on the drive,
		 * btrfs starts at an offset of at least 1MB when करोing chunk
		 * allocation.
		 *
		 * This ensures we have at least min_stripe_size मुक्त space
		 * after excluding 1MB.
		 */
		अगर (avail_space <= SZ_1M + min_stripe_size)
			जारी;

		avail_space -= SZ_1M;

		devices_info[i].dev = device;
		devices_info[i].max_avail = avail_space;

		i++;
	पूर्ण
	rcu_पढ़ो_unlock();

	nr_devices = i;

	btrfs_descending_sort_devices(devices_info, nr_devices);

	i = nr_devices - 1;
	avail_space = 0;
	जबतक (nr_devices >= rattr->devs_min) अणु
		num_stripes = min(num_stripes, nr_devices);

		अगर (devices_info[i].max_avail >= min_stripe_size) अणु
			पूर्णांक j;
			u64 alloc_size;

			avail_space += devices_info[i].max_avail * num_stripes;
			alloc_size = devices_info[i].max_avail;
			क्रम (j = i + 1 - num_stripes; j <= i; j++)
				devices_info[j].max_avail -= alloc_size;
		पूर्ण
		i--;
		nr_devices--;
	पूर्ण

	kमुक्त(devices_info);
	*मुक्त_bytes = avail_space;
	वापस 0;
पूर्ण

/*
 * Calculate numbers क्रम 'df', pessimistic in हाल of mixed raid profiles.
 *
 * If there's a redundant raid level at DATA block groups, use the respective
 * multiplier to scale the sizes.
 *
 * Unused device space usage is based on simulating the chunk allocator
 * algorithm that respects the device sizes and order of allocations.  This is
 * a बंद approximation of the actual use but there are other factors that may
 * change the result (like a new metadata chunk).
 *
 * If metadata is exhausted, f_bavail will be 0.
 */
अटल पूर्णांक btrfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dentry->d_sb);
	काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
	काष्ठा btrfs_space_info *found;
	u64 total_used = 0;
	u64 total_मुक्त_data = 0;
	u64 total_मुक्त_meta = 0;
	u32 bits = fs_info->sectorsize_bits;
	__be32 *fsid = (__be32 *)fs_info->fs_devices->fsid;
	अचिन्हित factor = 1;
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;
	पूर्णांक ret;
	u64 thresh = 0;
	पूर्णांक mixed = 0;

	list_क्रम_each_entry(found, &fs_info->space_info, list) अणु
		अगर (found->flags & BTRFS_BLOCK_GROUP_DATA) अणु
			पूर्णांक i;

			total_मुक्त_data += found->disk_total - found->disk_used;
			total_मुक्त_data -=
				btrfs_account_ro_block_groups_मुक्त_space(found);

			क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++) अणु
				अगर (!list_empty(&found->block_groups[i]))
					factor = btrfs_bg_type_to_factor(
						btrfs_raid_array[i].bg_flag);
			पूर्ण
		पूर्ण

		/*
		 * Metadata in mixed block goup profiles are accounted in data
		 */
		अगर (!mixed && found->flags & BTRFS_BLOCK_GROUP_METADATA) अणु
			अगर (found->flags & BTRFS_BLOCK_GROUP_DATA)
				mixed = 1;
			अन्यथा
				total_मुक्त_meta += found->disk_total -
					found->disk_used;
		पूर्ण

		total_used += found->disk_used;
	पूर्ण

	buf->f_blocks = भाग_u64(btrfs_super_total_bytes(disk_super), factor);
	buf->f_blocks >>= bits;
	buf->f_bमुक्त = buf->f_blocks - (भाग_u64(total_used, factor) >> bits);

	/* Account global block reserve as used, it's in logical size alपढ़ोy */
	spin_lock(&block_rsv->lock);
	/* Mixed block groups accounting is not byte-accurate, aव्योम overflow */
	अगर (buf->f_bमुक्त >= block_rsv->size >> bits)
		buf->f_bमुक्त -= block_rsv->size >> bits;
	अन्यथा
		buf->f_bमुक्त = 0;
	spin_unlock(&block_rsv->lock);

	buf->f_bavail = भाग_u64(total_मुक्त_data, factor);
	ret = btrfs_calc_avail_data_space(fs_info, &total_मुक्त_data);
	अगर (ret)
		वापस ret;
	buf->f_bavail += भाग_u64(total_मुक्त_data, factor);
	buf->f_bavail = buf->f_bavail >> bits;

	/*
	 * We calculate the reमुख्यing metadata space minus global reserve. If
	 * this is (supposedly) smaller than zero, there's no space. But this
	 * करोes not hold in practice, the exhausted state happens where's still
	 * some positive delta. So we apply some guesswork and compare the
	 * delta to a 4M threshold.  (Practically observed delta was ~2M.)
	 *
	 * We probably cannot calculate the exact threshold value because this
	 * depends on the पूर्णांकernal reservations requested by various
	 * operations, so some operations that consume a few metadata will
	 * succeed even अगर the Avail is zero. But this is better than the other
	 * way around.
	 */
	thresh = SZ_4M;

	/*
	 * We only want to claim there's no available space अगर we can no दीर्घer
	 * allocate chunks क्रम our metadata profile and our global reserve will
	 * not fit in the मुक्त metadata space.  If we aren't ->full then we
	 * still can allocate chunks and thus are fine using the currently
	 * calculated f_bavail.
	 */
	अगर (!mixed && block_rsv->space_info->full &&
	    total_मुक्त_meta - thresh < block_rsv->size)
		buf->f_bavail = 0;

	buf->f_type = BTRFS_SUPER_MAGIC;
	buf->f_bsize = dentry->d_sb->s_blocksize;
	buf->f_namelen = BTRFS_NAME_LEN;

	/* We treat it as स्थिरant endianness (it करोesn't matter _which_)
	   because we want the fsid to come out the same whether mounted
	   on a big-endian or little-endian host */
	buf->f_fsid.val[0] = be32_to_cpu(fsid[0]) ^ be32_to_cpu(fsid[2]);
	buf->f_fsid.val[1] = be32_to_cpu(fsid[1]) ^ be32_to_cpu(fsid[3]);
	/* Mask in the root object ID too, to disambiguate subvols */
	buf->f_fsid.val[0] ^=
		BTRFS_I(d_inode(dentry))->root->root_key.objectid >> 32;
	buf->f_fsid.val[1] ^=
		BTRFS_I(d_inode(dentry))->root->root_key.objectid;

	वापस 0;
पूर्ण

अटल व्योम btrfs_समाप्त_super(काष्ठा super_block *sb)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	समाप्त_anon_super(sb);
	btrfs_मुक्त_fs_info(fs_info);
पूर्ण

अटल काष्ठा file_प्रणाली_type btrfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "btrfs",
	.mount		= btrfs_mount,
	.समाप्त_sb	= btrfs_समाप्त_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_BINARY_MOUNTDATA,
पूर्ण;

अटल काष्ठा file_प्रणाली_type btrfs_root_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "btrfs",
	.mount		= btrfs_mount_root,
	.समाप्त_sb	= btrfs_समाप्त_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_BINARY_MOUNTDATA,
पूर्ण;

MODULE_ALIAS_FS("btrfs");

अटल पूर्णांक btrfs_control_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * The control file's निजी_data is used to hold the
	 * transaction when it is started and is used to keep
	 * track of whether a transaction is alपढ़ोy in progress.
	 */
	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

/*
 * Used by /dev/btrfs-control क्रम devices ioctls.
 */
अटल दीर्घ btrfs_control_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा btrfs_ioctl_vol_args *vol;
	काष्ठा btrfs_device *device = शून्य;
	पूर्णांक ret = -ENOTTY;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	vol = memdup_user((व्योम __user *)arg, माप(*vol));
	अगर (IS_ERR(vol))
		वापस PTR_ERR(vol);
	vol->name[BTRFS_PATH_NAME_MAX] = '\0';

	चयन (cmd) अणु
	हाल BTRFS_IOC_SCAN_DEV:
		mutex_lock(&uuid_mutex);
		device = btrfs_scan_one_device(vol->name, FMODE_READ,
					       &btrfs_root_fs_type);
		ret = PTR_ERR_OR_ZERO(device);
		mutex_unlock(&uuid_mutex);
		अवरोध;
	हाल BTRFS_IOC_FORGET_DEV:
		ret = btrfs_क्रमget_devices(vol->name);
		अवरोध;
	हाल BTRFS_IOC_DEVICES_READY:
		mutex_lock(&uuid_mutex);
		device = btrfs_scan_one_device(vol->name, FMODE_READ,
					       &btrfs_root_fs_type);
		अगर (IS_ERR(device)) अणु
			mutex_unlock(&uuid_mutex);
			ret = PTR_ERR(device);
			अवरोध;
		पूर्ण
		ret = !(device->fs_devices->num_devices ==
			device->fs_devices->total_devices);
		mutex_unlock(&uuid_mutex);
		अवरोध;
	हाल BTRFS_IOC_GET_SUPPORTED_FEATURES:
		ret = btrfs_ioctl_get_supported_features((व्योम __user*)arg);
		अवरोध;
	पूर्ण

	kमुक्त(vol);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_मुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	काष्ठा btrfs_root *root = fs_info->tree_root;

	set_bit(BTRFS_FS_FROZEN, &fs_info->flags);
	/*
	 * We करोn't need a barrier here, we'll रुको क्रम any transaction that
	 * could be in progress on other thपढ़ोs (and करो delayed iमाला_दो that
	 * we want to aव्योम on a frozen fileप्रणाली), or करो the commit
	 * ourselves.
	 */
	trans = btrfs_attach_transaction_barrier(root);
	अगर (IS_ERR(trans)) अणु
		/* no transaction, करोn't bother */
		अगर (PTR_ERR(trans) == -ENOENT)
			वापस 0;
		वापस PTR_ERR(trans);
	पूर्ण
	वापस btrfs_commit_transaction(trans);
पूर्ण

अटल पूर्णांक btrfs_unमुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);

	clear_bit(BTRFS_FS_FROZEN, &fs_info->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_show_devname(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(root->d_sb);
	काष्ठा btrfs_device *dev, *first_dev = शून्य;

	/*
	 * Lightweight locking of the devices. We should not need
	 * device_list_mutex here as we only पढ़ो the device data and the list
	 * is रक्षित by RCU.  Even अगर a device is deleted during the list
	 * traversals, we'll get valid data, the मुक्तing callback will रुको at
	 * least until the rcu_पढ़ो_unlock.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(dev, &fs_info->fs_devices->devices, dev_list) अणु
		अगर (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state))
			जारी;
		अगर (!dev->name)
			जारी;
		अगर (!first_dev || dev->devid < first_dev->devid)
			first_dev = dev;
	पूर्ण

	अगर (first_dev)
		seq_escape(m, rcu_str_deref(first_dev->name), " \t\n\\");
	अन्यथा
		WARN_ON(1);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations btrfs_super_ops = अणु
	.drop_inode	= btrfs_drop_inode,
	.evict_inode	= btrfs_evict_inode,
	.put_super	= btrfs_put_super,
	.sync_fs	= btrfs_sync_fs,
	.show_options	= btrfs_show_options,
	.show_devname	= btrfs_show_devname,
	.alloc_inode	= btrfs_alloc_inode,
	.destroy_inode	= btrfs_destroy_inode,
	.मुक्त_inode	= btrfs_मुक्त_inode,
	.statfs		= btrfs_statfs,
	.remount_fs	= btrfs_remount,
	.मुक्तze_fs	= btrfs_मुक्तze,
	.unमुक्तze_fs	= btrfs_unमुक्तze,
पूर्ण;

अटल स्थिर काष्ठा file_operations btrfs_ctl_fops = अणु
	.खोलो = btrfs_control_खोलो,
	.unlocked_ioctl	 = btrfs_control_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.owner	 = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice btrfs_misc = अणु
	.minor		= BTRFS_MINOR,
	.name		= "btrfs-control",
	.fops		= &btrfs_ctl_fops
पूर्ण;

MODULE_ALIAS_MISCDEV(BTRFS_MINOR);
MODULE_ALIAS("devname:btrfs-control");

अटल पूर्णांक __init btrfs_पूर्णांकerface_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&btrfs_misc);
पूर्ण

अटल __cold व्योम btrfs_पूर्णांकerface_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&btrfs_misc);
पूर्ण

अटल व्योम __init btrfs_prपूर्णांक_mod_info(व्योम)
अणु
	अटल स्थिर अक्षर options[] = ""
#अगर_घोषित CONFIG_BTRFS_DEBUG
			", debug=on"
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_ASSERT
			", assert=on"
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
			", integrity-checker=on"
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
			", ref-verify=on"
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLK_DEV_ZONED
			", zoned=yes"
#अन्यथा
			", zoned=no"
#पूर्ण_अगर
			;
	pr_info("Btrfs loaded, crc32c=%s%s\n", crc32c_impl(), options);
पूर्ण

अटल पूर्णांक __init init_btrfs_fs(व्योम)
अणु
	पूर्णांक err;

	btrfs_props_init();

	err = btrfs_init_sysfs();
	अगर (err)
		वापस err;

	btrfs_init_compress();

	err = btrfs_init_cachep();
	अगर (err)
		जाओ मुक्त_compress;

	err = extent_io_init();
	अगर (err)
		जाओ मुक्त_cachep;

	err = extent_state_cache_init();
	अगर (err)
		जाओ मुक्त_extent_io;

	err = extent_map_init();
	अगर (err)
		जाओ मुक्त_extent_state_cache;

	err = ordered_data_init();
	अगर (err)
		जाओ मुक्त_extent_map;

	err = btrfs_delayed_inode_init();
	अगर (err)
		जाओ मुक्त_ordered_data;

	err = btrfs_स्वतः_defrag_init();
	अगर (err)
		जाओ मुक्त_delayed_inode;

	err = btrfs_delayed_ref_init();
	अगर (err)
		जाओ मुक्त_स्वतः_defrag;

	err = btrfs_prelim_ref_init();
	अगर (err)
		जाओ मुक्त_delayed_ref;

	err = btrfs_end_io_wq_init();
	अगर (err)
		जाओ मुक्त_prelim_ref;

	err = btrfs_पूर्णांकerface_init();
	अगर (err)
		जाओ मुक्त_end_io_wq;

	btrfs_prपूर्णांक_mod_info();

	err = btrfs_run_sanity_tests();
	अगर (err)
		जाओ unरेजिस्टर_ioctl;

	err = रेजिस्टर_fileप्रणाली(&btrfs_fs_type);
	अगर (err)
		जाओ unरेजिस्टर_ioctl;

	वापस 0;

unरेजिस्टर_ioctl:
	btrfs_पूर्णांकerface_निकास();
मुक्त_end_io_wq:
	btrfs_end_io_wq_निकास();
मुक्त_prelim_ref:
	btrfs_prelim_ref_निकास();
मुक्त_delayed_ref:
	btrfs_delayed_ref_निकास();
मुक्त_स्वतः_defrag:
	btrfs_स्वतः_defrag_निकास();
मुक्त_delayed_inode:
	btrfs_delayed_inode_निकास();
मुक्त_ordered_data:
	ordered_data_निकास();
मुक्त_extent_map:
	extent_map_निकास();
मुक्त_extent_state_cache:
	extent_state_cache_निकास();
मुक्त_extent_io:
	extent_io_निकास();
मुक्त_cachep:
	btrfs_destroy_cachep();
मुक्त_compress:
	btrfs_निकास_compress();
	btrfs_निकास_sysfs();

	वापस err;
पूर्ण

अटल व्योम __निकास निकास_btrfs_fs(व्योम)
अणु
	btrfs_destroy_cachep();
	btrfs_delayed_ref_निकास();
	btrfs_स्वतः_defrag_निकास();
	btrfs_delayed_inode_निकास();
	btrfs_prelim_ref_निकास();
	ordered_data_निकास();
	extent_map_निकास();
	extent_state_cache_निकास();
	extent_io_निकास();
	btrfs_पूर्णांकerface_निकास();
	btrfs_end_io_wq_निकास();
	unरेजिस्टर_fileप्रणाली(&btrfs_fs_type);
	btrfs_निकास_sysfs();
	btrfs_cleanup_fs_uuids();
	btrfs_निकास_compress();
पूर्ण

late_initcall(init_btrfs_fs);
module_निकास(निकास_btrfs_fs)

MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: crc32c");
MODULE_SOFTDEP("pre: xxhash64");
MODULE_SOFTDEP("pre: sha256");
MODULE_SOFTDEP("pre: blake2b-256");
