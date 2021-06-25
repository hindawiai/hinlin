<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/super.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/statfs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/parser.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/quota.h>
#समावेश <linux/unicode.h>
#समावेश <linux/part_स्थिति.स>
#समावेश <linux/zstd.h>
#समावेश <linux/lz4.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "xattr.h"
#समावेश "gc.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/f2fs.h>

अटल काष्ठा kmem_cache *f2fs_inode_cachep;

#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION

स्थिर अक्षर *f2fs_fault_name[FAULT_MAX] = अणु
	[FAULT_KMALLOC]		= "kmalloc",
	[FAULT_KVMALLOC]	= "kvmalloc",
	[FAULT_PAGE_ALLOC]	= "page alloc",
	[FAULT_PAGE_GET]	= "page get",
	[FAULT_ALLOC_NID]	= "alloc nid",
	[FAULT_ORPHAN]		= "orphan",
	[FAULT_BLOCK]		= "no more block",
	[FAULT_सूची_DEPTH]	= "too big dir depth",
	[FAULT_EVICT_INODE]	= "evict_inode fail",
	[FAULT_TRUNCATE]	= "truncate fail",
	[FAULT_READ_IO]		= "read IO error",
	[FAULT_CHECKPOINT]	= "checkpoint error",
	[FAULT_DISCARD]		= "discard error",
	[FAULT_WRITE_IO]	= "write IO error",
पूर्ण;

व्योम f2fs_build_fault_attr(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक rate,
							अचिन्हित पूर्णांक type)
अणु
	काष्ठा f2fs_fault_info *ffi = &F2FS_OPTION(sbi).fault_info;

	अगर (rate) अणु
		atomic_set(&ffi->inject_ops, 0);
		ffi->inject_rate = rate;
	पूर्ण

	अगर (type)
		ffi->inject_type = type;

	अगर (!rate && !type)
		स_रखो(ffi, 0, माप(काष्ठा f2fs_fault_info));
पूर्ण
#पूर्ण_अगर

/* f2fs-wide shrinker description */
अटल काष्ठा shrinker f2fs_shrinker_info = अणु
	.scan_objects = f2fs_shrink_scan,
	.count_objects = f2fs_shrink_count,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

क्रमागत अणु
	Opt_gc_background,
	Opt_disable_roll_क्रमward,
	Opt_norecovery,
	Opt_discard,
	Opt_nodiscard,
	Opt_noheap,
	Opt_heap,
	Opt_user_xattr,
	Opt_nouser_xattr,
	Opt_acl,
	Opt_noacl,
	Opt_active_logs,
	Opt_disable_ext_identअगरy,
	Opt_अंतरभूत_xattr,
	Opt_noअंतरभूत_xattr,
	Opt_अंतरभूत_xattr_size,
	Opt_अंतरभूत_data,
	Opt_अंतरभूत_dentry,
	Opt_noअंतरभूत_dentry,
	Opt_flush_merge,
	Opt_noflush_merge,
	Opt_nobarrier,
	Opt_fastboot,
	Opt_extent_cache,
	Opt_noextent_cache,
	Opt_noअंतरभूत_data,
	Opt_data_flush,
	Opt_reserve_root,
	Opt_resgid,
	Opt_resuid,
	Opt_mode,
	Opt_io_size_bits,
	Opt_fault_injection,
	Opt_fault_type,
	Opt_lazyसमय,
	Opt_nolazyसमय,
	Opt_quota,
	Opt_noquota,
	Opt_usrquota,
	Opt_grpquota,
	Opt_prjquota,
	Opt_usrjquota,
	Opt_grpjquota,
	Opt_prjjquota,
	Opt_offusrjquota,
	Opt_offgrpjquota,
	Opt_offprjjquota,
	Opt_jqfmt_vfsold,
	Opt_jqfmt_vfsv0,
	Opt_jqfmt_vfsv1,
	Opt_whपूर्णांक,
	Opt_alloc,
	Opt_fsync,
	Opt_test_dummy_encryption,
	Opt_अंतरभूतcrypt,
	Opt_checkpoपूर्णांक_disable,
	Opt_checkpoपूर्णांक_disable_cap,
	Opt_checkpoपूर्णांक_disable_cap_perc,
	Opt_checkpoपूर्णांक_enable,
	Opt_checkpoपूर्णांक_merge,
	Opt_nocheckpoपूर्णांक_merge,
	Opt_compress_algorithm,
	Opt_compress_log_size,
	Opt_compress_extension,
	Opt_compress_chksum,
	Opt_compress_mode,
	Opt_atgc,
	Opt_gc_merge,
	Opt_nogc_merge,
	Opt_err,
पूर्ण;

अटल match_table_t f2fs_tokens = अणु
	अणुOpt_gc_background, "background_gc=%s"पूर्ण,
	अणुOpt_disable_roll_क्रमward, "disable_roll_forward"पूर्ण,
	अणुOpt_norecovery, "norecovery"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_nodiscard, "nodiscard"पूर्ण,
	अणुOpt_noheap, "no_heap"पूर्ण,
	अणुOpt_heap, "heap"पूर्ण,
	अणुOpt_user_xattr, "user_xattr"पूर्ण,
	अणुOpt_nouser_xattr, "nouser_xattr"पूर्ण,
	अणुOpt_acl, "acl"पूर्ण,
	अणुOpt_noacl, "noacl"पूर्ण,
	अणुOpt_active_logs, "active_logs=%u"पूर्ण,
	अणुOpt_disable_ext_identअगरy, "disable_ext_identify"पूर्ण,
	अणुOpt_अंतरभूत_xattr, "inline_xattr"पूर्ण,
	अणुOpt_noअंतरभूत_xattr, "noinline_xattr"पूर्ण,
	अणुOpt_अंतरभूत_xattr_size, "inline_xattr_size=%u"पूर्ण,
	अणुOpt_अंतरभूत_data, "inline_data"पूर्ण,
	अणुOpt_अंतरभूत_dentry, "inline_dentry"पूर्ण,
	अणुOpt_noअंतरभूत_dentry, "noinline_dentry"पूर्ण,
	अणुOpt_flush_merge, "flush_merge"पूर्ण,
	अणुOpt_noflush_merge, "noflush_merge"पूर्ण,
	अणुOpt_nobarrier, "nobarrier"पूर्ण,
	अणुOpt_fastboot, "fastboot"पूर्ण,
	अणुOpt_extent_cache, "extent_cache"पूर्ण,
	अणुOpt_noextent_cache, "noextent_cache"पूर्ण,
	अणुOpt_noअंतरभूत_data, "noinline_data"पूर्ण,
	अणुOpt_data_flush, "data_flush"पूर्ण,
	अणुOpt_reserve_root, "reserve_root=%u"पूर्ण,
	अणुOpt_resgid, "resgid=%u"पूर्ण,
	अणुOpt_resuid, "resuid=%u"पूर्ण,
	अणुOpt_mode, "mode=%s"पूर्ण,
	अणुOpt_io_size_bits, "io_bits=%u"पूर्ण,
	अणुOpt_fault_injection, "fault_injection=%u"पूर्ण,
	अणुOpt_fault_type, "fault_type=%u"पूर्ण,
	अणुOpt_lazyसमय, "lazytime"पूर्ण,
	अणुOpt_nolazyसमय, "nolazytime"पूर्ण,
	अणुOpt_quota, "quota"पूर्ण,
	अणुOpt_noquota, "noquota"पूर्ण,
	अणुOpt_usrquota, "usrquota"पूर्ण,
	अणुOpt_grpquota, "grpquota"पूर्ण,
	अणुOpt_prjquota, "prjquota"पूर्ण,
	अणुOpt_usrjquota, "usrjquota=%s"पूर्ण,
	अणुOpt_grpjquota, "grpjquota=%s"पूर्ण,
	अणुOpt_prjjquota, "prjjquota=%s"पूर्ण,
	अणुOpt_offusrjquota, "usrjquota="पूर्ण,
	अणुOpt_offgrpjquota, "grpjquota="पूर्ण,
	अणुOpt_offprjjquota, "prjjquota="पूर्ण,
	अणुOpt_jqfmt_vfsold, "jqfmt=vfsold"पूर्ण,
	अणुOpt_jqfmt_vfsv0, "jqfmt=vfsv0"पूर्ण,
	अणुOpt_jqfmt_vfsv1, "jqfmt=vfsv1"पूर्ण,
	अणुOpt_whपूर्णांक, "whint_mode=%s"पूर्ण,
	अणुOpt_alloc, "alloc_mode=%s"पूर्ण,
	अणुOpt_fsync, "fsync_mode=%s"पूर्ण,
	अणुOpt_test_dummy_encryption, "test_dummy_encryption=%s"पूर्ण,
	अणुOpt_test_dummy_encryption, "test_dummy_encryption"पूर्ण,
	अणुOpt_अंतरभूतcrypt, "inlinecrypt"पूर्ण,
	अणुOpt_checkpoपूर्णांक_disable, "checkpoint=disable"पूर्ण,
	अणुOpt_checkpoपूर्णांक_disable_cap, "checkpoint=disable:%u"पूर्ण,
	अणुOpt_checkpoपूर्णांक_disable_cap_perc, "checkpoint=disable:%u%%"पूर्ण,
	अणुOpt_checkpoपूर्णांक_enable, "checkpoint=enable"पूर्ण,
	अणुOpt_checkpoपूर्णांक_merge, "checkpoint_merge"पूर्ण,
	अणुOpt_nocheckpoपूर्णांक_merge, "nocheckpoint_merge"पूर्ण,
	अणुOpt_compress_algorithm, "compress_algorithm=%s"पूर्ण,
	अणुOpt_compress_log_size, "compress_log_size=%u"पूर्ण,
	अणुOpt_compress_extension, "compress_extension=%s"पूर्ण,
	अणुOpt_compress_chksum, "compress_chksum"पूर्ण,
	अणुOpt_compress_mode, "compress_mode=%s"पूर्ण,
	अणुOpt_atgc, "atgc"पूर्ण,
	अणुOpt_gc_merge, "gc_merge"पूर्ण,
	अणुOpt_nogc_merge, "nogc_merge"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

व्योम f2fs_prपूर्णांकk(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक level;

	बहु_शुरू(args, fmt);

	level = prपूर्णांकk_get_level(fmt);
	vaf.fmt = prपूर्णांकk_skip_level(fmt);
	vaf.va = &args;
	prपूर्णांकk("%c%cF2FS-fs (%s): %pV\n",
	       KERN_SOH_ASCII, level, sbi->sb->s_id, &vaf);

	बहु_पूर्ण(args);
पूर्ण

#अगर_घोषित CONFIG_UNICODE
अटल स्थिर काष्ठा f2fs_sb_encodings अणु
	__u16 magic;
	अक्षर *name;
	अक्षर *version;
पूर्ण f2fs_sb_encoding_map[] = अणु
	अणुF2FS_ENC_UTF8_12_1, "utf8", "12.1.0"पूर्ण,
पूर्ण;

अटल पूर्णांक f2fs_sb_पढ़ो_encoding(स्थिर काष्ठा f2fs_super_block *sb,
				 स्थिर काष्ठा f2fs_sb_encodings **encoding,
				 __u16 *flags)
अणु
	__u16 magic = le16_to_cpu(sb->s_encoding);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(f2fs_sb_encoding_map); i++)
		अगर (magic == f2fs_sb_encoding_map[i].magic)
			अवरोध;

	अगर (i >= ARRAY_SIZE(f2fs_sb_encoding_map))
		वापस -EINVAL;

	*encoding = &f2fs_sb_encoding_map[i];
	*flags = le16_to_cpu(sb->s_encoding_flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम limit_reserve_root(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t limit = min((sbi->user_block_count << 1) / 1000,
			sbi->user_block_count - sbi->reserved_blocks);

	/* limit is 0.2% */
	अगर (test_opt(sbi, RESERVE_ROOT) &&
			F2FS_OPTION(sbi).root_reserved_blocks > limit) अणु
		F2FS_OPTION(sbi).root_reserved_blocks = limit;
		f2fs_info(sbi, "Reduce reserved blocks for root = %u",
			  F2FS_OPTION(sbi).root_reserved_blocks);
	पूर्ण
	अगर (!test_opt(sbi, RESERVE_ROOT) &&
		(!uid_eq(F2FS_OPTION(sbi).s_resuid,
				make_kuid(&init_user_ns, F2FS_DEF_RESUID)) ||
		!gid_eq(F2FS_OPTION(sbi).s_resgid,
				make_kgid(&init_user_ns, F2FS_DEF_RESGID))))
		f2fs_info(sbi, "Ignore s_resuid=%u, s_resgid=%u w/o reserve_root",
			  from_kuid_munged(&init_user_ns,
					   F2FS_OPTION(sbi).s_resuid),
			  from_kgid_munged(&init_user_ns,
					   F2FS_OPTION(sbi).s_resgid));
पूर्ण

अटल अंतरभूत व्योम adjust_unusable_cap_perc(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (!F2FS_OPTION(sbi).unusable_cap_perc)
		वापस;

	अगर (F2FS_OPTION(sbi).unusable_cap_perc == 100)
		F2FS_OPTION(sbi).unusable_cap = sbi->user_block_count;
	अन्यथा
		F2FS_OPTION(sbi).unusable_cap = (sbi->user_block_count / 100) *
					F2FS_OPTION(sbi).unusable_cap_perc;

	f2fs_info(sbi, "Adjust unusable cap for checkpoint=disable = %u / %u%%",
			F2FS_OPTION(sbi).unusable_cap,
			F2FS_OPTION(sbi).unusable_cap_perc);
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा f2fs_inode_info *fi = (काष्ठा f2fs_inode_info *) foo;

	inode_init_once(&fi->vfs_inode);
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल स्थिर अक्षर * स्थिर quotatypes[] = INITQFNAMES;
#घोषणा QTYPE2NAME(t) (quotatypes[t])
अटल पूर्णांक f2fs_set_qf_name(काष्ठा super_block *sb, पूर्णांक qtype,
							substring_t *args)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	अक्षर *qname;
	पूर्णांक ret = -EINVAL;

	अगर (sb_any_quota_loaded(sb) && !F2FS_OPTION(sbi).s_qf_names[qtype]) अणु
		f2fs_err(sbi, "Cannot change journaled quota options when quota turned on");
		वापस -EINVAL;
	पूर्ण
	अगर (f2fs_sb_has_quota_ino(sbi)) अणु
		f2fs_info(sbi, "QUOTA feature is enabled, so ignore qf_name");
		वापस 0;
	पूर्ण

	qname = match_strdup(args);
	अगर (!qname) अणु
		f2fs_err(sbi, "Not enough memory for storing quotafile name");
		वापस -ENOMEM;
	पूर्ण
	अगर (F2FS_OPTION(sbi).s_qf_names[qtype]) अणु
		अगर (म_भेद(F2FS_OPTION(sbi).s_qf_names[qtype], qname) == 0)
			ret = 0;
		अन्यथा
			f2fs_err(sbi, "%s quota file already specified",
				 QTYPE2NAME(qtype));
		जाओ errout;
	पूर्ण
	अगर (म_अक्षर(qname, '/')) अणु
		f2fs_err(sbi, "quotafile must be on filesystem root");
		जाओ errout;
	पूर्ण
	F2FS_OPTION(sbi).s_qf_names[qtype] = qname;
	set_opt(sbi, QUOTA);
	वापस 0;
errout:
	kमुक्त(qname);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_clear_qf_name(काष्ठा super_block *sb, पूर्णांक qtype)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);

	अगर (sb_any_quota_loaded(sb) && F2FS_OPTION(sbi).s_qf_names[qtype]) अणु
		f2fs_err(sbi, "Cannot change journaled quota options when quota turned on");
		वापस -EINVAL;
	पूर्ण
	kमुक्त(F2FS_OPTION(sbi).s_qf_names[qtype]);
	F2FS_OPTION(sbi).s_qf_names[qtype] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_check_quota_options(काष्ठा f2fs_sb_info *sbi)
अणु
	/*
	 * We करो the test below only क्रम project quotas. 'usrquota' and
	 * 'grpquota' mount options are allowed even without quota feature
	 * to support legacy quotas in quota files.
	 */
	अगर (test_opt(sbi, PRJQUOTA) && !f2fs_sb_has_project_quota(sbi)) अणु
		f2fs_err(sbi, "Project quota feature not enabled. Cannot enable project quota enforcement.");
		वापस -1;
	पूर्ण
	अगर (F2FS_OPTION(sbi).s_qf_names[USRQUOTA] ||
			F2FS_OPTION(sbi).s_qf_names[GRPQUOTA] ||
			F2FS_OPTION(sbi).s_qf_names[PRJQUOTA]) अणु
		अगर (test_opt(sbi, USRQUOTA) &&
				F2FS_OPTION(sbi).s_qf_names[USRQUOTA])
			clear_opt(sbi, USRQUOTA);

		अगर (test_opt(sbi, GRPQUOTA) &&
				F2FS_OPTION(sbi).s_qf_names[GRPQUOTA])
			clear_opt(sbi, GRPQUOTA);

		अगर (test_opt(sbi, PRJQUOTA) &&
				F2FS_OPTION(sbi).s_qf_names[PRJQUOTA])
			clear_opt(sbi, PRJQUOTA);

		अगर (test_opt(sbi, GRPQUOTA) || test_opt(sbi, USRQUOTA) ||
				test_opt(sbi, PRJQUOTA)) अणु
			f2fs_err(sbi, "old and new quota format mixing");
			वापस -1;
		पूर्ण

		अगर (!F2FS_OPTION(sbi).s_jquota_fmt) अणु
			f2fs_err(sbi, "journaled quota format not specified");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (f2fs_sb_has_quota_ino(sbi) && F2FS_OPTION(sbi).s_jquota_fmt) अणु
		f2fs_info(sbi, "QUOTA feature is enabled, so ignore jquota_fmt");
		F2FS_OPTION(sbi).s_jquota_fmt = 0;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक f2fs_set_test_dummy_encryption(काष्ठा super_block *sb,
					  स्थिर अक्षर *opt,
					  स्थिर substring_t *arg,
					  bool is_remount)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
#अगर_घोषित CONFIG_FS_ENCRYPTION
	पूर्णांक err;

	अगर (!f2fs_sb_has_encrypt(sbi)) अणु
		f2fs_err(sbi, "Encrypt feature is off");
		वापस -EINVAL;
	पूर्ण

	/*
	 * This mount option is just क्रम testing, and it's not worthजबतक to
	 * implement the extra complनिकासy (e.g. RCU protection) that would be
	 * needed to allow it to be set or changed during remount.  We करो allow
	 * it to be specअगरied during remount, but only अगर there is no change.
	 */
	अगर (is_remount && !F2FS_OPTION(sbi).dummy_enc_policy.policy) अणु
		f2fs_warn(sbi, "Can't set test_dummy_encryption on remount");
		वापस -EINVAL;
	पूर्ण
	err = fscrypt_set_test_dummy_encryption(
		sb, arg->from, &F2FS_OPTION(sbi).dummy_enc_policy);
	अगर (err) अणु
		अगर (err == -EEXIST)
			f2fs_warn(sbi,
				  "Can't change test_dummy_encryption on remount");
		अन्यथा अगर (err == -EINVAL)
			f2fs_warn(sbi, "Value of option \"%s\" is unrecognized",
				  opt);
		अन्यथा
			f2fs_warn(sbi, "Error processing option \"%s\" [%d]",
				  opt, err);
		वापस -EINVAL;
	पूर्ण
	f2fs_warn(sbi, "Test dummy encryption mode enabled");
#अन्यथा
	f2fs_warn(sbi, "Test dummy encryption mount option ignored");
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
#अगर_घोषित CONFIG_F2FS_FS_LZ4
अटल पूर्णांक f2fs_set_lz4hc_level(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *str)
अणु
#अगर_घोषित CONFIG_F2FS_FS_LZ4HC
	अचिन्हित पूर्णांक level;
#पूर्ण_अगर

	अगर (म_माप(str) == 3) अणु
		F2FS_OPTION(sbi).compress_level = 0;
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_LZ4HC
	str += 3;

	अगर (str[0] != ':') अणु
		f2fs_info(sbi, "wrong format, e.g. <alg_name>:<compr_level>");
		वापस -EINVAL;
	पूर्ण
	अगर (kstrtouपूर्णांक(str + 1, 10, &level))
		वापस -EINVAL;

	अगर (level < LZ4HC_MIN_CLEVEL || level > LZ4HC_MAX_CLEVEL) अणु
		f2fs_info(sbi, "invalid lz4hc compress level: %d", level);
		वापस -EINVAL;
	पूर्ण

	F2FS_OPTION(sbi).compress_level = level;
	वापस 0;
#अन्यथा
	f2fs_info(sbi, "kernel doesn't support lz4hc compression");
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_F2FS_FS_ZSTD
अटल पूर्णांक f2fs_set_zstd_level(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक level;
	पूर्णांक len = 4;

	अगर (म_माप(str) == len) अणु
		F2FS_OPTION(sbi).compress_level = 0;
		वापस 0;
	पूर्ण

	str += len;

	अगर (str[0] != ':') अणु
		f2fs_info(sbi, "wrong format, e.g. <alg_name>:<compr_level>");
		वापस -EINVAL;
	पूर्ण
	अगर (kstrtouपूर्णांक(str + 1, 10, &level))
		वापस -EINVAL;

	अगर (!level || level > ZSTD_maxCLevel()) अणु
		f2fs_info(sbi, "invalid zstd compress level: %d", level);
		वापस -EINVAL;
	पूर्ण

	F2FS_OPTION(sbi).compress_level = level;
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक parse_options(काष्ठा super_block *sb, अक्षर *options, bool is_remount)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	substring_t args[MAX_OPT_ARGS];
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अचिन्हित अक्षर (*ext)[F2FS_EXTENSION_LEN];
	पूर्णांक ext_cnt;
#पूर्ण_अगर
	अक्षर *p, *name;
	पूर्णांक arg = 0;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक ret;

	अगर (!options)
		वापस 0;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;
		/*
		 * Initialize args काष्ठा so we know whether arg was
		 * found; some options take optional arguments.
		 */
		args[0].to = args[0].from = शून्य;
		token = match_token(p, f2fs_tokens, args);

		चयन (token) अणु
		हाल Opt_gc_background:
			name = match_strdup(&args[0]);

			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "on")) अणु
				F2FS_OPTION(sbi).bggc_mode = BGGC_MODE_ON;
			पूर्ण अन्यथा अगर (!म_भेद(name, "off")) अणु
				F2FS_OPTION(sbi).bggc_mode = BGGC_MODE_OFF;
			पूर्ण अन्यथा अगर (!म_भेद(name, "sync")) अणु
				F2FS_OPTION(sbi).bggc_mode = BGGC_MODE_SYNC;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_disable_roll_क्रमward:
			set_opt(sbi, DISABLE_ROLL_FORWARD);
			अवरोध;
		हाल Opt_norecovery:
			/* this option mounts f2fs with ro */
			set_opt(sbi, NORECOVERY);
			अगर (!f2fs_पढ़ोonly(sb))
				वापस -EINVAL;
			अवरोध;
		हाल Opt_discard:
			set_opt(sbi, DISCARD);
			अवरोध;
		हाल Opt_nodiscard:
			अगर (f2fs_sb_has_blkzoned(sbi)) अणु
				f2fs_warn(sbi, "discard is required for zoned block devices");
				वापस -EINVAL;
			पूर्ण
			clear_opt(sbi, DISCARD);
			अवरोध;
		हाल Opt_noheap:
			set_opt(sbi, NOHEAP);
			अवरोध;
		हाल Opt_heap:
			clear_opt(sbi, NOHEAP);
			अवरोध;
#अगर_घोषित CONFIG_F2FS_FS_XATTR
		हाल Opt_user_xattr:
			set_opt(sbi, XATTR_USER);
			अवरोध;
		हाल Opt_nouser_xattr:
			clear_opt(sbi, XATTR_USER);
			अवरोध;
		हाल Opt_अंतरभूत_xattr:
			set_opt(sbi, INLINE_XATTR);
			अवरोध;
		हाल Opt_noअंतरभूत_xattr:
			clear_opt(sbi, INLINE_XATTR);
			अवरोध;
		हाल Opt_अंतरभूत_xattr_size:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			set_opt(sbi, INLINE_XATTR_SIZE);
			F2FS_OPTION(sbi).अंतरभूत_xattr_size = arg;
			अवरोध;
#अन्यथा
		हाल Opt_user_xattr:
			f2fs_info(sbi, "user_xattr options not supported");
			अवरोध;
		हाल Opt_nouser_xattr:
			f2fs_info(sbi, "nouser_xattr options not supported");
			अवरोध;
		हाल Opt_अंतरभूत_xattr:
			f2fs_info(sbi, "inline_xattr options not supported");
			अवरोध;
		हाल Opt_noअंतरभूत_xattr:
			f2fs_info(sbi, "noinline_xattr options not supported");
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
		हाल Opt_acl:
			set_opt(sbi, POSIX_ACL);
			अवरोध;
		हाल Opt_noacl:
			clear_opt(sbi, POSIX_ACL);
			अवरोध;
#अन्यथा
		हाल Opt_acl:
			f2fs_info(sbi, "acl options not supported");
			अवरोध;
		हाल Opt_noacl:
			f2fs_info(sbi, "noacl options not supported");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_active_logs:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			अगर (arg != 2 && arg != 4 &&
				arg != NR_CURSEG_PERSIST_TYPE)
				वापस -EINVAL;
			F2FS_OPTION(sbi).active_logs = arg;
			अवरोध;
		हाल Opt_disable_ext_identअगरy:
			set_opt(sbi, DISABLE_EXT_IDENTIFY);
			अवरोध;
		हाल Opt_अंतरभूत_data:
			set_opt(sbi, INLINE_DATA);
			अवरोध;
		हाल Opt_अंतरभूत_dentry:
			set_opt(sbi, INLINE_DENTRY);
			अवरोध;
		हाल Opt_noअंतरभूत_dentry:
			clear_opt(sbi, INLINE_DENTRY);
			अवरोध;
		हाल Opt_flush_merge:
			set_opt(sbi, FLUSH_MERGE);
			अवरोध;
		हाल Opt_noflush_merge:
			clear_opt(sbi, FLUSH_MERGE);
			अवरोध;
		हाल Opt_nobarrier:
			set_opt(sbi, NOBARRIER);
			अवरोध;
		हाल Opt_fastboot:
			set_opt(sbi, FASTBOOT);
			अवरोध;
		हाल Opt_extent_cache:
			set_opt(sbi, EXTENT_CACHE);
			अवरोध;
		हाल Opt_noextent_cache:
			clear_opt(sbi, EXTENT_CACHE);
			अवरोध;
		हाल Opt_noअंतरभूत_data:
			clear_opt(sbi, INLINE_DATA);
			अवरोध;
		हाल Opt_data_flush:
			set_opt(sbi, DATA_FLUSH);
			अवरोध;
		हाल Opt_reserve_root:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			अगर (test_opt(sbi, RESERVE_ROOT)) अणु
				f2fs_info(sbi, "Preserve previous reserve_root=%u",
					  F2FS_OPTION(sbi).root_reserved_blocks);
			पूर्ण अन्यथा अणु
				F2FS_OPTION(sbi).root_reserved_blocks = arg;
				set_opt(sbi, RESERVE_ROOT);
			पूर्ण
			अवरोध;
		हाल Opt_resuid:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			uid = make_kuid(current_user_ns(), arg);
			अगर (!uid_valid(uid)) अणु
				f2fs_err(sbi, "Invalid uid value %d", arg);
				वापस -EINVAL;
			पूर्ण
			F2FS_OPTION(sbi).s_resuid = uid;
			अवरोध;
		हाल Opt_resgid:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			gid = make_kgid(current_user_ns(), arg);
			अगर (!gid_valid(gid)) अणु
				f2fs_err(sbi, "Invalid gid value %d", arg);
				वापस -EINVAL;
			पूर्ण
			F2FS_OPTION(sbi).s_resgid = gid;
			अवरोध;
		हाल Opt_mode:
			name = match_strdup(&args[0]);

			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "adaptive")) अणु
				अगर (f2fs_sb_has_blkzoned(sbi)) अणु
					f2fs_warn(sbi, "adaptive mode is not allowed with zoned block device feature");
					kमुक्त(name);
					वापस -EINVAL;
				पूर्ण
				F2FS_OPTION(sbi).fs_mode = FS_MODE_ADAPTIVE;
			पूर्ण अन्यथा अगर (!म_भेद(name, "lfs")) अणु
				F2FS_OPTION(sbi).fs_mode = FS_MODE_LFS;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_io_size_bits:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			अगर (arg <= 0 || arg > __ilog2_u32(BIO_MAX_VECS)) अणु
				f2fs_warn(sbi, "Not support %d, larger than %d",
					  1 << arg, BIO_MAX_VECS);
				वापस -EINVAL;
			पूर्ण
			F2FS_OPTION(sbi).ग_लिखो_io_size_bits = arg;
			अवरोध;
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
		हाल Opt_fault_injection:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			f2fs_build_fault_attr(sbi, arg, F2FS_ALL_FAULT_TYPE);
			set_opt(sbi, FAULT_INJECTION);
			अवरोध;

		हाल Opt_fault_type:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			f2fs_build_fault_attr(sbi, 0, arg);
			set_opt(sbi, FAULT_INJECTION);
			अवरोध;
#अन्यथा
		हाल Opt_fault_injection:
			f2fs_info(sbi, "fault_injection options not supported");
			अवरोध;

		हाल Opt_fault_type:
			f2fs_info(sbi, "fault_type options not supported");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_lazyसमय:
			sb->s_flags |= SB_LAZYTIME;
			अवरोध;
		हाल Opt_nolazyसमय:
			sb->s_flags &= ~SB_LAZYTIME;
			अवरोध;
#अगर_घोषित CONFIG_QUOTA
		हाल Opt_quota:
		हाल Opt_usrquota:
			set_opt(sbi, USRQUOTA);
			अवरोध;
		हाल Opt_grpquota:
			set_opt(sbi, GRPQUOTA);
			अवरोध;
		हाल Opt_prjquota:
			set_opt(sbi, PRJQUOTA);
			अवरोध;
		हाल Opt_usrjquota:
			ret = f2fs_set_qf_name(sb, USRQUOTA, &args[0]);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_grpjquota:
			ret = f2fs_set_qf_name(sb, GRPQUOTA, &args[0]);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_prjjquota:
			ret = f2fs_set_qf_name(sb, PRJQUOTA, &args[0]);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_offusrjquota:
			ret = f2fs_clear_qf_name(sb, USRQUOTA);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_offgrpjquota:
			ret = f2fs_clear_qf_name(sb, GRPQUOTA);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_offprjjquota:
			ret = f2fs_clear_qf_name(sb, PRJQUOTA);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_jqfmt_vfsold:
			F2FS_OPTION(sbi).s_jquota_fmt = QFMT_VFS_OLD;
			अवरोध;
		हाल Opt_jqfmt_vfsv0:
			F2FS_OPTION(sbi).s_jquota_fmt = QFMT_VFS_V0;
			अवरोध;
		हाल Opt_jqfmt_vfsv1:
			F2FS_OPTION(sbi).s_jquota_fmt = QFMT_VFS_V1;
			अवरोध;
		हाल Opt_noquota:
			clear_opt(sbi, QUOTA);
			clear_opt(sbi, USRQUOTA);
			clear_opt(sbi, GRPQUOTA);
			clear_opt(sbi, PRJQUOTA);
			अवरोध;
#अन्यथा
		हाल Opt_quota:
		हाल Opt_usrquota:
		हाल Opt_grpquota:
		हाल Opt_prjquota:
		हाल Opt_usrjquota:
		हाल Opt_grpjquota:
		हाल Opt_prjjquota:
		हाल Opt_offusrjquota:
		हाल Opt_offgrpjquota:
		हाल Opt_offprjjquota:
		हाल Opt_jqfmt_vfsold:
		हाल Opt_jqfmt_vfsv0:
		हाल Opt_jqfmt_vfsv1:
		हाल Opt_noquota:
			f2fs_info(sbi, "quota operations not supported");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_whपूर्णांक:
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "user-based")) अणु
				F2FS_OPTION(sbi).whपूर्णांक_mode = WHINT_MODE_USER;
			पूर्ण अन्यथा अगर (!म_भेद(name, "off")) अणु
				F2FS_OPTION(sbi).whपूर्णांक_mode = WHINT_MODE_OFF;
			पूर्ण अन्यथा अगर (!म_भेद(name, "fs-based")) अणु
				F2FS_OPTION(sbi).whपूर्णांक_mode = WHINT_MODE_FS;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_alloc:
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;

			अगर (!म_भेद(name, "default")) अणु
				F2FS_OPTION(sbi).alloc_mode = ALLOC_MODE_DEFAULT;
			पूर्ण अन्यथा अगर (!म_भेद(name, "reuse")) अणु
				F2FS_OPTION(sbi).alloc_mode = ALLOC_MODE_REUSE;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_fsync:
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "posix")) अणु
				F2FS_OPTION(sbi).fsync_mode = FSYNC_MODE_POSIX;
			पूर्ण अन्यथा अगर (!म_भेद(name, "strict")) अणु
				F2FS_OPTION(sbi).fsync_mode = FSYNC_MODE_STRICT;
			पूर्ण अन्यथा अगर (!म_भेद(name, "nobarrier")) अणु
				F2FS_OPTION(sbi).fsync_mode =
							FSYNC_MODE_NOBARRIER;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_test_dummy_encryption:
			ret = f2fs_set_test_dummy_encryption(sb, p, &args[0],
							     is_remount);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल Opt_अंतरभूतcrypt:
#अगर_घोषित CONFIG_FS_ENCRYPTION_INLINE_CRYPT
			sb->s_flags |= SB_INLINECRYPT;
#अन्यथा
			f2fs_info(sbi, "inline encryption not supported");
#पूर्ण_अगर
			अवरोध;
		हाल Opt_checkpoपूर्णांक_disable_cap_perc:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			अगर (arg < 0 || arg > 100)
				वापस -EINVAL;
			F2FS_OPTION(sbi).unusable_cap_perc = arg;
			set_opt(sbi, DISABLE_CHECKPOINT);
			अवरोध;
		हाल Opt_checkpoपूर्णांक_disable_cap:
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			F2FS_OPTION(sbi).unusable_cap = arg;
			set_opt(sbi, DISABLE_CHECKPOINT);
			अवरोध;
		हाल Opt_checkpoपूर्णांक_disable:
			set_opt(sbi, DISABLE_CHECKPOINT);
			अवरोध;
		हाल Opt_checkpoपूर्णांक_enable:
			clear_opt(sbi, DISABLE_CHECKPOINT);
			अवरोध;
		हाल Opt_checkpoपूर्णांक_merge:
			set_opt(sbi, MERGE_CHECKPOINT);
			अवरोध;
		हाल Opt_nocheckpoपूर्णांक_merge:
			clear_opt(sbi, MERGE_CHECKPOINT);
			अवरोध;
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
		हाल Opt_compress_algorithm:
			अगर (!f2fs_sb_has_compression(sbi)) अणु
				f2fs_info(sbi, "Image doesn't support compression");
				अवरोध;
			पूर्ण
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "lzo")) अणु
#अगर_घोषित CONFIG_F2FS_FS_LZO
				F2FS_OPTION(sbi).compress_level = 0;
				F2FS_OPTION(sbi).compress_algorithm =
								COMPRESS_LZO;
#अन्यथा
				f2fs_info(sbi, "kernel doesn't support lzo compression");
#पूर्ण_अगर
			पूर्ण अन्यथा अगर (!म_भेदन(name, "lz4", 3)) अणु
#अगर_घोषित CONFIG_F2FS_FS_LZ4
				ret = f2fs_set_lz4hc_level(sbi, name);
				अगर (ret) अणु
					kमुक्त(name);
					वापस -EINVAL;
				पूर्ण
				F2FS_OPTION(sbi).compress_algorithm =
								COMPRESS_LZ4;
#अन्यथा
				f2fs_info(sbi, "kernel doesn't support lz4 compression");
#पूर्ण_अगर
			पूर्ण अन्यथा अगर (!म_भेदन(name, "zstd", 4)) अणु
#अगर_घोषित CONFIG_F2FS_FS_ZSTD
				ret = f2fs_set_zstd_level(sbi, name);
				अगर (ret) अणु
					kमुक्त(name);
					वापस -EINVAL;
				पूर्ण
				F2FS_OPTION(sbi).compress_algorithm =
								COMPRESS_ZSTD;
#अन्यथा
				f2fs_info(sbi, "kernel doesn't support zstd compression");
#पूर्ण_अगर
			पूर्ण अन्यथा अगर (!म_भेद(name, "lzo-rle")) अणु
#अगर_घोषित CONFIG_F2FS_FS_LZORLE
				F2FS_OPTION(sbi).compress_level = 0;
				F2FS_OPTION(sbi).compress_algorithm =
								COMPRESS_LZORLE;
#अन्यथा
				f2fs_info(sbi, "kernel doesn't support lzorle compression");
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
		हाल Opt_compress_log_size:
			अगर (!f2fs_sb_has_compression(sbi)) अणु
				f2fs_info(sbi, "Image doesn't support compression");
				अवरोध;
			पूर्ण
			अगर (args->from && match_पूर्णांक(args, &arg))
				वापस -EINVAL;
			अगर (arg < MIN_COMPRESS_LOG_SIZE ||
				arg > MAX_COMPRESS_LOG_SIZE) अणु
				f2fs_err(sbi,
					"Compress cluster log size is out of range");
				वापस -EINVAL;
			पूर्ण
			F2FS_OPTION(sbi).compress_log_size = arg;
			अवरोध;
		हाल Opt_compress_extension:
			अगर (!f2fs_sb_has_compression(sbi)) अणु
				f2fs_info(sbi, "Image doesn't support compression");
				अवरोध;
			पूर्ण
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;

			ext = F2FS_OPTION(sbi).extensions;
			ext_cnt = F2FS_OPTION(sbi).compress_ext_cnt;

			अगर (म_माप(name) >= F2FS_EXTENSION_LEN ||
				ext_cnt >= COMPRESS_EXT_NUM) अणु
				f2fs_err(sbi,
					"invalid extension length/number");
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण

			म_नकल(ext[ext_cnt], name);
			F2FS_OPTION(sbi).compress_ext_cnt++;
			kमुक्त(name);
			अवरोध;
		हाल Opt_compress_chksum:
			F2FS_OPTION(sbi).compress_chksum = true;
			अवरोध;
		हाल Opt_compress_mode:
			name = match_strdup(&args[0]);
			अगर (!name)
				वापस -ENOMEM;
			अगर (!म_भेद(name, "fs")) अणु
				F2FS_OPTION(sbi).compress_mode = COMPR_MODE_FS;
			पूर्ण अन्यथा अगर (!म_भेद(name, "user")) अणु
				F2FS_OPTION(sbi).compress_mode = COMPR_MODE_USER;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				वापस -EINVAL;
			पूर्ण
			kमुक्त(name);
			अवरोध;
#अन्यथा
		हाल Opt_compress_algorithm:
		हाल Opt_compress_log_size:
		हाल Opt_compress_extension:
		हाल Opt_compress_chksum:
		हाल Opt_compress_mode:
			f2fs_info(sbi, "compression options not supported");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_atgc:
			set_opt(sbi, ATGC);
			अवरोध;
		हाल Opt_gc_merge:
			set_opt(sbi, GC_MERGE);
			अवरोध;
		हाल Opt_nogc_merge:
			clear_opt(sbi, GC_MERGE);
			अवरोध;
		शेष:
			f2fs_err(sbi, "Unrecognized mount option \"%s\" or missing value",
				 p);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_QUOTA
	अगर (f2fs_check_quota_options(sbi))
		वापस -EINVAL;
#अन्यथा
	अगर (f2fs_sb_has_quota_ino(sbi) && !f2fs_पढ़ोonly(sbi->sb)) अणु
		f2fs_info(sbi, "Filesystem with quota feature cannot be mounted RDWR without CONFIG_QUOTA");
		वापस -EINVAL;
	पूर्ण
	अगर (f2fs_sb_has_project_quota(sbi) && !f2fs_पढ़ोonly(sbi->sb)) अणु
		f2fs_err(sbi, "Filesystem with project quota feature cannot be mounted RDWR without CONFIG_QUOTA");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_UNICODE
	अगर (f2fs_sb_has_हालfold(sbi)) अणु
		f2fs_err(sbi,
			"Filesystem with casefold feature cannot be mounted without CONFIG_UNICODE");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	/*
	 * The BLKZONED feature indicates that the drive was क्रमmatted with
	 * zone alignment optimization. This is optional क्रम host-aware
	 * devices, but mandatory क्रम host-managed zoned block devices.
	 */
#अगर_अघोषित CONFIG_BLK_DEV_ZONED
	अगर (f2fs_sb_has_blkzoned(sbi)) अणु
		f2fs_err(sbi, "Zoned block device support is not enabled");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	अगर (F2FS_IO_SIZE_BITS(sbi) && !f2fs_lfs_mode(sbi)) अणु
		f2fs_err(sbi, "Should set mode=lfs with %uKB-sized IO",
			 F2FS_IO_SIZE_KB(sbi));
		वापस -EINVAL;
	पूर्ण

	अगर (test_opt(sbi, INLINE_XATTR_SIZE)) अणु
		पूर्णांक min_size, max_size;

		अगर (!f2fs_sb_has_extra_attr(sbi) ||
			!f2fs_sb_has_flexible_अंतरभूत_xattr(sbi)) अणु
			f2fs_err(sbi, "extra_attr or flexible_inline_xattr feature is off");
			वापस -EINVAL;
		पूर्ण
		अगर (!test_opt(sbi, INLINE_XATTR)) अणु
			f2fs_err(sbi, "inline_xattr_size option should be set with inline_xattr option");
			वापस -EINVAL;
		पूर्ण

		min_size = माप(काष्ठा f2fs_xattr_header) / माप(__le32);
		max_size = MAX_INLINE_XATTR_SIZE;

		अगर (F2FS_OPTION(sbi).अंतरभूत_xattr_size < min_size ||
				F2FS_OPTION(sbi).अंतरभूत_xattr_size > max_size) अणु
			f2fs_err(sbi, "inline xattr size is out of range: %d ~ %d",
				 min_size, max_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (test_opt(sbi, DISABLE_CHECKPOINT) && f2fs_lfs_mode(sbi)) अणु
		f2fs_err(sbi, "LFS not compatible with checkpoint=disable\n");
		वापस -EINVAL;
	पूर्ण

	/* Not pass करोwn ग_लिखो hपूर्णांकs अगर the number of active logs is lesser
	 * than NR_CURSEG_PERSIST_TYPE.
	 */
	अगर (F2FS_OPTION(sbi).active_logs != NR_CURSEG_TYPE)
		F2FS_OPTION(sbi).whपूर्णांक_mode = WHINT_MODE_OFF;
	वापस 0;
पूर्ण

अटल काष्ठा inode *f2fs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा f2fs_inode_info *fi;

	fi = kmem_cache_alloc(f2fs_inode_cachep, GFP_F2FS_ZERO);
	अगर (!fi)
		वापस शून्य;

	init_once((व्योम *) fi);

	/* Initialize f2fs-specअगरic inode info */
	atomic_set(&fi->dirty_pages, 0);
	atomic_set(&fi->i_compr_blocks, 0);
	init_rwsem(&fi->i_sem);
	spin_lock_init(&fi->i_size_lock);
	INIT_LIST_HEAD(&fi->dirty_list);
	INIT_LIST_HEAD(&fi->gdirty_list);
	INIT_LIST_HEAD(&fi->inmem_ilist);
	INIT_LIST_HEAD(&fi->inmem_pages);
	mutex_init(&fi->inmem_lock);
	init_rwsem(&fi->i_gc_rwsem[READ]);
	init_rwsem(&fi->i_gc_rwsem[WRITE]);
	init_rwsem(&fi->i_mmap_sem);
	init_rwsem(&fi->i_xattr_sem);

	/* Will be used by directory only */
	fi->i_dir_level = F2FS_SB(sb)->dir_level;

	वापस &fi->vfs_inode;
पूर्ण

अटल पूर्णांक f2fs_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक ret;

	/*
	 * during fileप्रणाली shutकरोwn, अगर checkpoपूर्णांक is disabled,
	 * drop useless meta/node dirty pages.
	 */
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		अगर (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi)) अणु
			trace_f2fs_drop_inode(inode, 1);
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * This is to aव्योम a deadlock condition like below.
	 * ग_लिखोback_single_inode(inode)
	 *  - f2fs_ग_लिखो_data_page
	 *    - f2fs_gc -> iput -> evict
	 *       - inode_रुको_क्रम_ग_लिखोback(inode)
	 */
	अगर ((!inode_unhashed(inode) && inode->i_state & I_SYNC)) अणु
		अगर (!inode->i_nlink && !is_bad_inode(inode)) अणु
			/* to aव्योम evict_inode call simultaneously */
			atomic_inc(&inode->i_count);
			spin_unlock(&inode->i_lock);

			/* some reमुख्यed atomic pages should discarded */
			अगर (f2fs_is_atomic_file(inode))
				f2fs_drop_inmem_pages(inode);

			/* should reमुख्य fi->extent_tree क्रम ग_लिखोpage */
			f2fs_destroy_extent_node(inode);

			sb_start_पूर्णांकग_लिखो(inode->i_sb);
			f2fs_i_size_ग_लिखो(inode, 0);

			f2fs_submit_merged_ग_लिखो_cond(F2FS_I_SB(inode),
					inode, शून्य, 0, DATA);
			truncate_inode_pages_final(inode->i_mapping);

			अगर (F2FS_HAS_BLOCKS(inode))
				f2fs_truncate(inode);

			sb_end_पूर्णांकग_लिखो(inode->i_sb);

			spin_lock(&inode->i_lock);
			atomic_dec(&inode->i_count);
		पूर्ण
		trace_f2fs_drop_inode(inode, 0);
		वापस 0;
	पूर्ण
	ret = generic_drop_inode(inode);
	अगर (!ret)
		ret = fscrypt_drop_inode(inode);
	trace_f2fs_drop_inode(inode, ret);
	वापस ret;
पूर्ण

पूर्णांक f2fs_inode_dirtied(काष्ठा inode *inode, bool sync)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक ret = 0;

	spin_lock(&sbi->inode_lock[सूचीTY_META]);
	अगर (is_inode_flag_set(inode, FI_सूचीTY_INODE)) अणु
		ret = 1;
	पूर्ण अन्यथा अणु
		set_inode_flag(inode, FI_सूचीTY_INODE);
		stat_inc_dirty_inode(sbi, सूचीTY_META);
	पूर्ण
	अगर (sync && list_empty(&F2FS_I(inode)->gdirty_list)) अणु
		list_add_tail(&F2FS_I(inode)->gdirty_list,
				&sbi->inode_list[सूचीTY_META]);
		inc_page_count(sbi, F2FS_सूचीTY_IMETA);
	पूर्ण
	spin_unlock(&sbi->inode_lock[सूचीTY_META]);
	वापस ret;
पूर्ण

व्योम f2fs_inode_synced(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	spin_lock(&sbi->inode_lock[सूचीTY_META]);
	अगर (!is_inode_flag_set(inode, FI_सूचीTY_INODE)) अणु
		spin_unlock(&sbi->inode_lock[सूचीTY_META]);
		वापस;
	पूर्ण
	अगर (!list_empty(&F2FS_I(inode)->gdirty_list)) अणु
		list_del_init(&F2FS_I(inode)->gdirty_list);
		dec_page_count(sbi, F2FS_सूचीTY_IMETA);
	पूर्ण
	clear_inode_flag(inode, FI_सूचीTY_INODE);
	clear_inode_flag(inode, FI_AUTO_RECOVER);
	stat_dec_dirty_inode(F2FS_I_SB(inode), सूचीTY_META);
	spin_unlock(&sbi->inode_lock[सूचीTY_META]);
पूर्ण

/*
 * f2fs_dirty_inode() is called from __mark_inode_dirty()
 *
 * We should call set_dirty_inode to ग_लिखो the dirty inode through ग_लिखो_inode.
 */
अटल व्योम f2fs_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	अगर (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		वापस;

	अगर (is_inode_flag_set(inode, FI_AUTO_RECOVER))
		clear_inode_flag(inode, FI_AUTO_RECOVER);

	f2fs_inode_dirtied(inode, false);
पूर्ण

अटल व्योम f2fs_मुक्त_inode(काष्ठा inode *inode)
अणु
	fscrypt_मुक्त_inode(inode);
	kmem_cache_मुक्त(f2fs_inode_cachep, F2FS_I(inode));
पूर्ण

अटल व्योम destroy_percpu_info(काष्ठा f2fs_sb_info *sbi)
अणु
	percpu_counter_destroy(&sbi->alloc_valid_block_count);
	percpu_counter_destroy(&sbi->total_valid_inode_count);
पूर्ण

अटल व्योम destroy_device_list(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sbi->s_ndevs; i++) अणु
		blkdev_put(FDEV(i).bdev, FMODE_EXCL);
#अगर_घोषित CONFIG_BLK_DEV_ZONED
		kvमुक्त(FDEV(i).blkz_seq);
		kमुक्त(FDEV(i).zone_capacity_blocks);
#पूर्ण_अगर
	पूर्ण
	kvमुक्त(sbi->devs);
पूर्ण

अटल व्योम f2fs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक i;
	bool dropped;

	/* unरेजिस्टर procfs/sysfs entries in advance to aव्योम race हाल */
	f2fs_unरेजिस्टर_sysfs(sbi);

	f2fs_quota_off_umount(sb);

	/* prevent reमुख्यing shrinker jobs */
	mutex_lock(&sbi->umount_mutex);

	/*
	 * flush all issued checkpoपूर्णांकs and stop checkpoपूर्णांक issue thपढ़ो.
	 * after then, all checkpoपूर्णांकs should be करोne by each process context.
	 */
	f2fs_stop_ckpt_thपढ़ो(sbi);

	/*
	 * We करोn't need to करो checkpoपूर्णांक when superblock is clean.
	 * But, the previous checkpoपूर्णांक was not करोne by umount, it needs to करो
	 * clean checkpoपूर्णांक again.
	 */
	अगर ((is_sbi_flag_set(sbi, SBI_IS_सूचीTY) ||
			!is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG))) अणु
		काष्ठा cp_control cpc = अणु
			.reason = CP_UMOUNT,
		पूर्ण;
		f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	पूर्ण

	/* be sure to रुको क्रम any on-going discard commands */
	dropped = f2fs_issue_discard_समयout(sbi);

	अगर ((f2fs_hw_support_discard(sbi) || f2fs_hw_should_discard(sbi)) &&
					!sbi->discard_blks && !dropped) अणु
		काष्ठा cp_control cpc = अणु
			.reason = CP_UMOUNT | CP_TRIMMED,
		पूर्ण;
		f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	पूर्ण

	/*
	 * normally superblock is clean, so we need to release this.
	 * In addition, EIO will skip करो checkpoपूर्णांक, we need this as well.
	 */
	f2fs_release_ino_entry(sbi, true);

	f2fs_leave_shrinker(sbi);
	mutex_unlock(&sbi->umount_mutex);

	/* our cp_error हाल, we can रुको क्रम any ग_लिखोback page */
	f2fs_flush_merged_ग_लिखोs(sbi);

	f2fs_रुको_on_all_pages(sbi, F2FS_WB_CP_DATA);

	f2fs_bug_on(sbi, sbi->fsync_node_num);

	iput(sbi->node_inode);
	sbi->node_inode = शून्य;

	iput(sbi->meta_inode);
	sbi->meta_inode = शून्य;

	/*
	 * iput() can update stat inक्रमmation, अगर f2fs_ग_लिखो_checkpoपूर्णांक()
	 * above failed with error.
	 */
	f2fs_destroy_stats(sbi);

	/* destroy f2fs पूर्णांकernal modules */
	f2fs_destroy_node_manager(sbi);
	f2fs_destroy_segment_manager(sbi);

	f2fs_destroy_post_पढ़ो_wq(sbi);

	kvमुक्त(sbi->ckpt);

	sb->s_fs_info = शून्य;
	अगर (sbi->s_chksum_driver)
		crypto_मुक्त_shash(sbi->s_chksum_driver);
	kमुक्त(sbi->raw_super);

	destroy_device_list(sbi);
	f2fs_destroy_page_array_cache(sbi);
	f2fs_destroy_xattr_caches(sbi);
	mempool_destroy(sbi->ग_लिखो_io_dummy);
#अगर_घोषित CONFIG_QUOTA
	क्रम (i = 0; i < MAXQUOTAS; i++)
		kमुक्त(F2FS_OPTION(sbi).s_qf_names[i]);
#पूर्ण_अगर
	fscrypt_मुक्त_dummy_policy(&F2FS_OPTION(sbi).dummy_enc_policy);
	destroy_percpu_info(sbi);
	क्रम (i = 0; i < NR_PAGE_TYPE; i++)
		kvमुक्त(sbi->ग_लिखो_io[i]);
#अगर_घोषित CONFIG_UNICODE
	utf8_unload(sb->s_encoding);
#पूर्ण_अगर
	kमुक्त(sbi);
पूर्ण

पूर्णांक f2fs_sync_fs(काष्ठा super_block *sb, पूर्णांक sync)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक err = 0;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस 0;
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस 0;

	trace_f2fs_sync_fs(sb, sync);

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		वापस -EAGAIN;

	अगर (sync)
		err = f2fs_issue_checkpoपूर्णांक(sbi);

	वापस err;
पूर्ण

अटल पूर्णांक f2fs_मुक्तze(काष्ठा super_block *sb)
अणु
	अगर (f2fs_पढ़ोonly(sb))
		वापस 0;

	/* IO error happened beक्रमe */
	अगर (unlikely(f2fs_cp_error(F2FS_SB(sb))))
		वापस -EIO;

	/* must be clean, since sync_fileप्रणाली() was alपढ़ोy called */
	अगर (is_sbi_flag_set(F2FS_SB(sb), SBI_IS_सूचीTY))
		वापस -EINVAL;

	/* ensure no checkpoपूर्णांक required */
	अगर (!llist_empty(&F2FS_SB(sb)->cprc_info.issue_list))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_unमुक्तze(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक f2fs_statfs_project(काष्ठा super_block *sb,
				kprojid_t projid, काष्ठा kstatfs *buf)
अणु
	काष्ठा kqid qid;
	काष्ठा dquot *dquot;
	u64 limit;
	u64 curblock;

	qid = make_kqid_projid(projid);
	dquot = dqget(sb, qid);
	अगर (IS_ERR(dquot))
		वापस PTR_ERR(dquot);
	spin_lock(&dquot->dq_dqb_lock);

	limit = min_not_zero(dquot->dq_dqb.dqb_bsoftlimit,
					dquot->dq_dqb.dqb_bhardlimit);
	अगर (limit)
		limit >>= sb->s_blocksize_bits;

	अगर (limit && buf->f_blocks > limit) अणु
		curblock = (dquot->dq_dqb.dqb_curspace +
			    dquot->dq_dqb.dqb_rsvspace) >> sb->s_blocksize_bits;
		buf->f_blocks = limit;
		buf->f_bमुक्त = buf->f_bavail =
			(buf->f_blocks > curblock) ?
			 (buf->f_blocks - curblock) : 0;
	पूर्ण

	limit = min_not_zero(dquot->dq_dqb.dqb_isoftlimit,
					dquot->dq_dqb.dqb_ihardlimit);

	अगर (limit && buf->f_files > limit) अणु
		buf->f_files = limit;
		buf->f_fमुक्त =
			(buf->f_files > dquot->dq_dqb.dqb_curinodes) ?
			 (buf->f_files - dquot->dq_dqb.dqb_curinodes) : 0;
	पूर्ण

	spin_unlock(&dquot->dq_dqb_lock);
	dqput(dquot);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक f2fs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	block_t total_count, user_block_count, start_count;
	u64 avail_node_count;

	total_count = le64_to_cpu(sbi->raw_super->block_count);
	user_block_count = sbi->user_block_count;
	start_count = le32_to_cpu(sbi->raw_super->segment0_blkaddr);
	buf->f_type = F2FS_SUPER_MAGIC;
	buf->f_bsize = sbi->blocksize;

	buf->f_blocks = total_count - start_count;
	buf->f_bमुक्त = user_block_count - valid_user_blocks(sbi) -
						sbi->current_reserved_blocks;

	spin_lock(&sbi->stat_lock);
	अगर (unlikely(buf->f_bमुक्त <= sbi->unusable_block_count))
		buf->f_bमुक्त = 0;
	अन्यथा
		buf->f_bमुक्त -= sbi->unusable_block_count;
	spin_unlock(&sbi->stat_lock);

	अगर (buf->f_bमुक्त > F2FS_OPTION(sbi).root_reserved_blocks)
		buf->f_bavail = buf->f_bमुक्त -
				F2FS_OPTION(sbi).root_reserved_blocks;
	अन्यथा
		buf->f_bavail = 0;

	avail_node_count = sbi->total_node_count - F2FS_RESERVED_NODE_NUM;

	अगर (avail_node_count > user_block_count) अणु
		buf->f_files = user_block_count;
		buf->f_fमुक्त = buf->f_bavail;
	पूर्ण अन्यथा अणु
		buf->f_files = avail_node_count;
		buf->f_fमुक्त = min(avail_node_count - valid_node_count(sbi),
					buf->f_bavail);
	पूर्ण

	buf->f_namelen = F2FS_NAME_LEN;
	buf->f_fsid    = u64_to_fsid(id);

#अगर_घोषित CONFIG_QUOTA
	अगर (is_inode_flag_set(dentry->d_inode, FI_PROJ_INHERIT) &&
			sb_has_quota_limits_enabled(sb, PRJQUOTA)) अणु
		f2fs_statfs_project(sb, F2FS_I(dentry->d_inode)->i_projid, buf);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम f2fs_show_quota_options(काष्ठा seq_file *seq,
					   काष्ठा super_block *sb)
अणु
#अगर_घोषित CONFIG_QUOTA
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);

	अगर (F2FS_OPTION(sbi).s_jquota_fmt) अणु
		अक्षर *fmtname = "";

		चयन (F2FS_OPTION(sbi).s_jquota_fmt) अणु
		हाल QFMT_VFS_OLD:
			fmtname = "vfsold";
			अवरोध;
		हाल QFMT_VFS_V0:
			fmtname = "vfsv0";
			अवरोध;
		हाल QFMT_VFS_V1:
			fmtname = "vfsv1";
			अवरोध;
		पूर्ण
		seq_म_लिखो(seq, ",jqfmt=%s", fmtname);
	पूर्ण

	अगर (F2FS_OPTION(sbi).s_qf_names[USRQUOTA])
		seq_show_option(seq, "usrjquota",
			F2FS_OPTION(sbi).s_qf_names[USRQUOTA]);

	अगर (F2FS_OPTION(sbi).s_qf_names[GRPQUOTA])
		seq_show_option(seq, "grpjquota",
			F2FS_OPTION(sbi).s_qf_names[GRPQUOTA]);

	अगर (F2FS_OPTION(sbi).s_qf_names[PRJQUOTA])
		seq_show_option(seq, "prjjquota",
			F2FS_OPTION(sbi).s_qf_names[PRJQUOTA]);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
अटल अंतरभूत व्योम f2fs_show_compress_options(काष्ठा seq_file *seq,
							काष्ठा super_block *sb)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	अक्षर *algtype = "";
	पूर्णांक i;

	अगर (!f2fs_sb_has_compression(sbi))
		वापस;

	चयन (F2FS_OPTION(sbi).compress_algorithm) अणु
	हाल COMPRESS_LZO:
		algtype = "lzo";
		अवरोध;
	हाल COMPRESS_LZ4:
		algtype = "lz4";
		अवरोध;
	हाल COMPRESS_ZSTD:
		algtype = "zstd";
		अवरोध;
	हाल COMPRESS_LZORLE:
		algtype = "lzo-rle";
		अवरोध;
	पूर्ण
	seq_म_लिखो(seq, ",compress_algorithm=%s", algtype);

	अगर (F2FS_OPTION(sbi).compress_level)
		seq_म_लिखो(seq, ":%d", F2FS_OPTION(sbi).compress_level);

	seq_म_लिखो(seq, ",compress_log_size=%u",
			F2FS_OPTION(sbi).compress_log_size);

	क्रम (i = 0; i < F2FS_OPTION(sbi).compress_ext_cnt; i++) अणु
		seq_म_लिखो(seq, ",compress_extension=%s",
			F2FS_OPTION(sbi).extensions[i]);
	पूर्ण

	अगर (F2FS_OPTION(sbi).compress_chksum)
		seq_माला_दो(seq, ",compress_chksum");

	अगर (F2FS_OPTION(sbi).compress_mode == COMPR_MODE_FS)
		seq_म_लिखो(seq, ",compress_mode=%s", "fs");
	अन्यथा अगर (F2FS_OPTION(sbi).compress_mode == COMPR_MODE_USER)
		seq_म_लिखो(seq, ",compress_mode=%s", "user");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक f2fs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(root->d_sb);

	अगर (F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_SYNC)
		seq_म_लिखो(seq, ",background_gc=%s", "sync");
	अन्यथा अगर (F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_ON)
		seq_म_लिखो(seq, ",background_gc=%s", "on");
	अन्यथा अगर (F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_OFF)
		seq_म_लिखो(seq, ",background_gc=%s", "off");

	अगर (test_opt(sbi, GC_MERGE))
		seq_माला_दो(seq, ",gc_merge");

	अगर (test_opt(sbi, DISABLE_ROLL_FORWARD))
		seq_माला_दो(seq, ",disable_roll_forward");
	अगर (test_opt(sbi, NORECOVERY))
		seq_माला_दो(seq, ",norecovery");
	अगर (test_opt(sbi, DISCARD))
		seq_माला_दो(seq, ",discard");
	अन्यथा
		seq_माला_दो(seq, ",nodiscard");
	अगर (test_opt(sbi, NOHEAP))
		seq_माला_दो(seq, ",no_heap");
	अन्यथा
		seq_माला_दो(seq, ",heap");
#अगर_घोषित CONFIG_F2FS_FS_XATTR
	अगर (test_opt(sbi, XATTR_USER))
		seq_माला_दो(seq, ",user_xattr");
	अन्यथा
		seq_माला_दो(seq, ",nouser_xattr");
	अगर (test_opt(sbi, INLINE_XATTR))
		seq_माला_दो(seq, ",inline_xattr");
	अन्यथा
		seq_माला_दो(seq, ",noinline_xattr");
	अगर (test_opt(sbi, INLINE_XATTR_SIZE))
		seq_म_लिखो(seq, ",inline_xattr_size=%u",
					F2FS_OPTION(sbi).अंतरभूत_xattr_size);
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
	अगर (test_opt(sbi, POSIX_ACL))
		seq_माला_दो(seq, ",acl");
	अन्यथा
		seq_माला_दो(seq, ",noacl");
#पूर्ण_अगर
	अगर (test_opt(sbi, DISABLE_EXT_IDENTIFY))
		seq_माला_दो(seq, ",disable_ext_identify");
	अगर (test_opt(sbi, INLINE_DATA))
		seq_माला_दो(seq, ",inline_data");
	अन्यथा
		seq_माला_दो(seq, ",noinline_data");
	अगर (test_opt(sbi, INLINE_DENTRY))
		seq_माला_दो(seq, ",inline_dentry");
	अन्यथा
		seq_माला_दो(seq, ",noinline_dentry");
	अगर (!f2fs_पढ़ोonly(sbi->sb) && test_opt(sbi, FLUSH_MERGE))
		seq_माला_दो(seq, ",flush_merge");
	अगर (test_opt(sbi, NOBARRIER))
		seq_माला_दो(seq, ",nobarrier");
	अगर (test_opt(sbi, FASTBOOT))
		seq_माला_दो(seq, ",fastboot");
	अगर (test_opt(sbi, EXTENT_CACHE))
		seq_माला_दो(seq, ",extent_cache");
	अन्यथा
		seq_माला_दो(seq, ",noextent_cache");
	अगर (test_opt(sbi, DATA_FLUSH))
		seq_माला_दो(seq, ",data_flush");

	seq_माला_दो(seq, ",mode=");
	अगर (F2FS_OPTION(sbi).fs_mode == FS_MODE_ADAPTIVE)
		seq_माला_दो(seq, "adaptive");
	अन्यथा अगर (F2FS_OPTION(sbi).fs_mode == FS_MODE_LFS)
		seq_माला_दो(seq, "lfs");
	seq_म_लिखो(seq, ",active_logs=%u", F2FS_OPTION(sbi).active_logs);
	अगर (test_opt(sbi, RESERVE_ROOT))
		seq_म_लिखो(seq, ",reserve_root=%u,resuid=%u,resgid=%u",
				F2FS_OPTION(sbi).root_reserved_blocks,
				from_kuid_munged(&init_user_ns,
					F2FS_OPTION(sbi).s_resuid),
				from_kgid_munged(&init_user_ns,
					F2FS_OPTION(sbi).s_resgid));
	अगर (F2FS_IO_SIZE_BITS(sbi))
		seq_म_लिखो(seq, ",io_bits=%u",
				F2FS_OPTION(sbi).ग_लिखो_io_size_bits);
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	अगर (test_opt(sbi, FAULT_INJECTION)) अणु
		seq_म_लिखो(seq, ",fault_injection=%u",
				F2FS_OPTION(sbi).fault_info.inject_rate);
		seq_म_लिखो(seq, ",fault_type=%u",
				F2FS_OPTION(sbi).fault_info.inject_type);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_QUOTA
	अगर (test_opt(sbi, QUOTA))
		seq_माला_दो(seq, ",quota");
	अगर (test_opt(sbi, USRQUOTA))
		seq_माला_दो(seq, ",usrquota");
	अगर (test_opt(sbi, GRPQUOTA))
		seq_माला_दो(seq, ",grpquota");
	अगर (test_opt(sbi, PRJQUOTA))
		seq_माला_दो(seq, ",prjquota");
#पूर्ण_अगर
	f2fs_show_quota_options(seq, sbi->sb);
	अगर (F2FS_OPTION(sbi).whपूर्णांक_mode == WHINT_MODE_USER)
		seq_म_लिखो(seq, ",whint_mode=%s", "user-based");
	अन्यथा अगर (F2FS_OPTION(sbi).whपूर्णांक_mode == WHINT_MODE_FS)
		seq_म_लिखो(seq, ",whint_mode=%s", "fs-based");

	fscrypt_show_test_dummy_encryption(seq, ',', sbi->sb);

	अगर (sbi->sb->s_flags & SB_INLINECRYPT)
		seq_माला_दो(seq, ",inlinecrypt");

	अगर (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_DEFAULT)
		seq_म_लिखो(seq, ",alloc_mode=%s", "default");
	अन्यथा अगर (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_REUSE)
		seq_म_लिखो(seq, ",alloc_mode=%s", "reuse");

	अगर (test_opt(sbi, DISABLE_CHECKPOINT))
		seq_म_लिखो(seq, ",checkpoint=disable:%u",
				F2FS_OPTION(sbi).unusable_cap);
	अगर (test_opt(sbi, MERGE_CHECKPOINT))
		seq_माला_दो(seq, ",checkpoint_merge");
	अन्यथा
		seq_माला_दो(seq, ",nocheckpoint_merge");
	अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_POSIX)
		seq_म_लिखो(seq, ",fsync_mode=%s", "posix");
	अन्यथा अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT)
		seq_म_लिखो(seq, ",fsync_mode=%s", "strict");
	अन्यथा अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_NOBARRIER)
		seq_म_लिखो(seq, ",fsync_mode=%s", "nobarrier");

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	f2fs_show_compress_options(seq, sbi->sb);
#पूर्ण_अगर

	अगर (test_opt(sbi, ATGC))
		seq_माला_दो(seq, ",atgc");
	वापस 0;
पूर्ण

अटल व्योम शेष_options(काष्ठा f2fs_sb_info *sbi)
अणु
	/* init some FS parameters */
	F2FS_OPTION(sbi).active_logs = NR_CURSEG_PERSIST_TYPE;
	F2FS_OPTION(sbi).अंतरभूत_xattr_size = DEFAULT_INLINE_XATTR_ADDRS;
	F2FS_OPTION(sbi).whपूर्णांक_mode = WHINT_MODE_OFF;
	F2FS_OPTION(sbi).alloc_mode = ALLOC_MODE_DEFAULT;
	F2FS_OPTION(sbi).fsync_mode = FSYNC_MODE_POSIX;
	F2FS_OPTION(sbi).s_resuid = make_kuid(&init_user_ns, F2FS_DEF_RESUID);
	F2FS_OPTION(sbi).s_resgid = make_kgid(&init_user_ns, F2FS_DEF_RESGID);
	F2FS_OPTION(sbi).compress_algorithm = COMPRESS_LZ4;
	F2FS_OPTION(sbi).compress_log_size = MIN_COMPRESS_LOG_SIZE;
	F2FS_OPTION(sbi).compress_ext_cnt = 0;
	F2FS_OPTION(sbi).compress_mode = COMPR_MODE_FS;
	F2FS_OPTION(sbi).bggc_mode = BGGC_MODE_ON;

	sbi->sb->s_flags &= ~SB_INLINECRYPT;

	set_opt(sbi, INLINE_XATTR);
	set_opt(sbi, INLINE_DATA);
	set_opt(sbi, INLINE_DENTRY);
	set_opt(sbi, EXTENT_CACHE);
	set_opt(sbi, NOHEAP);
	clear_opt(sbi, DISABLE_CHECKPOINT);
	set_opt(sbi, MERGE_CHECKPOINT);
	F2FS_OPTION(sbi).unusable_cap = 0;
	sbi->sb->s_flags |= SB_LAZYTIME;
	set_opt(sbi, FLUSH_MERGE);
	set_opt(sbi, DISCARD);
	अगर (f2fs_sb_has_blkzoned(sbi))
		F2FS_OPTION(sbi).fs_mode = FS_MODE_LFS;
	अन्यथा
		F2FS_OPTION(sbi).fs_mode = FS_MODE_ADAPTIVE;

#अगर_घोषित CONFIG_F2FS_FS_XATTR
	set_opt(sbi, XATTR_USER);
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
	set_opt(sbi, POSIX_ACL);
#पूर्ण_अगर

	f2fs_build_fault_attr(sbi, 0, 0);
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक f2fs_enable_quotas(काष्ठा super_block *sb);
#पूर्ण_अगर

अटल पूर्णांक f2fs_disable_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित पूर्णांक s_flags = sbi->sb->s_flags;
	काष्ठा cp_control cpc;
	पूर्णांक err = 0;
	पूर्णांक ret;
	block_t unusable;

	अगर (s_flags & SB_RDONLY) अणु
		f2fs_err(sbi, "checkpoint=disable on readonly fs");
		वापस -EINVAL;
	पूर्ण
	sbi->sb->s_flags |= SB_ACTIVE;

	f2fs_update_समय(sbi, DISABLE_TIME);

	जबतक (!f2fs_समय_over(sbi, DISABLE_TIME)) अणु
		करोwn_ग_लिखो(&sbi->gc_lock);
		err = f2fs_gc(sbi, true, false, false, शून्य_SEGNO);
		अगर (err == -ENODATA) अणु
			err = 0;
			अवरोध;
		पूर्ण
		अगर (err && err != -EAGAIN)
			अवरोध;
	पूर्ण

	ret = sync_fileप्रणाली(sbi->sb);
	अगर (ret || err) अणु
		err = ret ? ret : err;
		जाओ restore_flag;
	पूर्ण

	unusable = f2fs_get_unusable_blocks(sbi);
	अगर (f2fs_disable_cp_again(sbi, unusable)) अणु
		err = -EAGAIN;
		जाओ restore_flag;
	पूर्ण

	करोwn_ग_लिखो(&sbi->gc_lock);
	cpc.reason = CP_PAUSE;
	set_sbi_flag(sbi, SBI_CP_DISABLED);
	err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	अगर (err)
		जाओ out_unlock;

	spin_lock(&sbi->stat_lock);
	sbi->unusable_block_count = unusable;
	spin_unlock(&sbi->stat_lock);

out_unlock:
	up_ग_लिखो(&sbi->gc_lock);
restore_flag:
	sbi->sb->s_flags = s_flags;	/* Restore SB_RDONLY status */
	वापस err;
पूर्ण

अटल व्योम f2fs_enable_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi)
अणु
	/* we should flush all the data to keep data consistency */
	sync_inodes_sb(sbi->sb);

	करोwn_ग_लिखो(&sbi->gc_lock);
	f2fs_dirty_to_preमुक्त(sbi);

	clear_sbi_flag(sbi, SBI_CP_DISABLED);
	set_sbi_flag(sbi, SBI_IS_सूचीTY);
	up_ग_लिखो(&sbi->gc_lock);

	f2fs_sync_fs(sbi->sb, 1);
पूर्ण

अटल पूर्णांक f2fs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	काष्ठा f2fs_mount_info org_mount_opt;
	अचिन्हित दीर्घ old_sb_flags;
	पूर्णांक err;
	bool need_restart_gc = false, need_stop_gc = false;
	bool need_restart_ckpt = false, need_stop_ckpt = false;
	bool need_restart_flush = false, need_stop_flush = false;
	bool no_extent_cache = !test_opt(sbi, EXTENT_CACHE);
	bool disable_checkpoपूर्णांक = test_opt(sbi, DISABLE_CHECKPOINT);
	bool no_io_align = !F2FS_IO_ALIGNED(sbi);
	bool no_atgc = !test_opt(sbi, ATGC);
	bool checkpoपूर्णांक_changed;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक i, j;
#पूर्ण_अगर

	/*
	 * Save the old mount options in हाल we
	 * need to restore them.
	 */
	org_mount_opt = sbi->mount_opt;
	old_sb_flags = sb->s_flags;

#अगर_घोषित CONFIG_QUOTA
	org_mount_opt.s_jquota_fmt = F2FS_OPTION(sbi).s_jquota_fmt;
	क्रम (i = 0; i < MAXQUOTAS; i++) अणु
		अगर (F2FS_OPTION(sbi).s_qf_names[i]) अणु
			org_mount_opt.s_qf_names[i] =
				kstrdup(F2FS_OPTION(sbi).s_qf_names[i],
				GFP_KERNEL);
			अगर (!org_mount_opt.s_qf_names[i]) अणु
				क्रम (j = 0; j < i; j++)
					kमुक्त(org_mount_opt.s_qf_names[j]);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			org_mount_opt.s_qf_names[i] = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* recover superblocks we couldn't ग_लिखो due to previous RO mount */
	अगर (!(*flags & SB_RDONLY) && is_sbi_flag_set(sbi, SBI_NEED_SB_WRITE)) अणु
		err = f2fs_commit_super(sbi, false);
		f2fs_info(sbi, "Try to recover all the superblocks, ret: %d",
			  err);
		अगर (!err)
			clear_sbi_flag(sbi, SBI_NEED_SB_WRITE);
	पूर्ण

	शेष_options(sbi);

	/* parse mount options */
	err = parse_options(sb, data, true);
	अगर (err)
		जाओ restore_opts;
	checkpoपूर्णांक_changed =
			disable_checkpoपूर्णांक != test_opt(sbi, DISABLE_CHECKPOINT);

	/*
	 * Previous and new state of fileप्रणाली is RO,
	 * so skip checking GC and FLUSH_MERGE conditions.
	 */
	अगर (f2fs_पढ़ोonly(sb) && (*flags & SB_RDONLY))
		जाओ skip;

#अगर_घोषित CONFIG_QUOTA
	अगर (!f2fs_पढ़ोonly(sb) && (*flags & SB_RDONLY)) अणु
		err = dquot_suspend(sb, -1);
		अगर (err < 0)
			जाओ restore_opts;
	पूर्ण अन्यथा अगर (f2fs_पढ़ोonly(sb) && !(*flags & SB_RDONLY)) अणु
		/* dquot_resume needs RW */
		sb->s_flags &= ~SB_RDONLY;
		अगर (sb_any_quota_suspended(sb)) अणु
			dquot_resume(sb, -1);
		पूर्ण अन्यथा अगर (f2fs_sb_has_quota_ino(sbi)) अणु
			err = f2fs_enable_quotas(sb);
			अगर (err)
				जाओ restore_opts;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* disallow enable atgc dynamically */
	अगर (no_atgc == !!test_opt(sbi, ATGC)) अणु
		err = -EINVAL;
		f2fs_warn(sbi, "switch atgc option is not allowed");
		जाओ restore_opts;
	पूर्ण

	/* disallow enable/disable extent_cache dynamically */
	अगर (no_extent_cache == !!test_opt(sbi, EXTENT_CACHE)) अणु
		err = -EINVAL;
		f2fs_warn(sbi, "switch extent_cache option is not allowed");
		जाओ restore_opts;
	पूर्ण

	अगर (no_io_align == !!F2FS_IO_ALIGNED(sbi)) अणु
		err = -EINVAL;
		f2fs_warn(sbi, "switch io_bits option is not allowed");
		जाओ restore_opts;
	पूर्ण

	अगर ((*flags & SB_RDONLY) && test_opt(sbi, DISABLE_CHECKPOINT)) अणु
		err = -EINVAL;
		f2fs_warn(sbi, "disabling checkpoint not compatible with read-only");
		जाओ restore_opts;
	पूर्ण

	/*
	 * We stop the GC thपढ़ो अगर FS is mounted as RO
	 * or अगर background_gc = off is passed in mount
	 * option. Also sync the fileप्रणाली.
	 */
	अगर ((*flags & SB_RDONLY) ||
			(F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_OFF &&
			!test_opt(sbi, GC_MERGE))) अणु
		अगर (sbi->gc_thपढ़ो) अणु
			f2fs_stop_gc_thपढ़ो(sbi);
			need_restart_gc = true;
		पूर्ण
	पूर्ण अन्यथा अगर (!sbi->gc_thपढ़ो) अणु
		err = f2fs_start_gc_thपढ़ो(sbi);
		अगर (err)
			जाओ restore_opts;
		need_stop_gc = true;
	पूर्ण

	अगर (*flags & SB_RDONLY ||
		F2FS_OPTION(sbi).whपूर्णांक_mode != org_mount_opt.whपूर्णांक_mode) अणु
		sync_inodes_sb(sb);

		set_sbi_flag(sbi, SBI_IS_सूचीTY);
		set_sbi_flag(sbi, SBI_IS_CLOSE);
		f2fs_sync_fs(sb, 1);
		clear_sbi_flag(sbi, SBI_IS_CLOSE);
	पूर्ण

	अगर ((*flags & SB_RDONLY) || test_opt(sbi, DISABLE_CHECKPOINT) ||
			!test_opt(sbi, MERGE_CHECKPOINT)) अणु
		f2fs_stop_ckpt_thपढ़ो(sbi);
		need_restart_ckpt = true;
	पूर्ण अन्यथा अणु
		err = f2fs_start_ckpt_thपढ़ो(sbi);
		अगर (err) अणु
			f2fs_err(sbi,
			    "Failed to start F2FS issue_checkpoint_thread (%d)",
			    err);
			जाओ restore_gc;
		पूर्ण
		need_stop_ckpt = true;
	पूर्ण

	/*
	 * We stop issue flush thपढ़ो अगर FS is mounted as RO
	 * or अगर flush_merge is not passed in mount option.
	 */
	अगर ((*flags & SB_RDONLY) || !test_opt(sbi, FLUSH_MERGE)) अणु
		clear_opt(sbi, FLUSH_MERGE);
		f2fs_destroy_flush_cmd_control(sbi, false);
		need_restart_flush = true;
	पूर्ण अन्यथा अणु
		err = f2fs_create_flush_cmd_control(sbi);
		अगर (err)
			जाओ restore_ckpt;
		need_stop_flush = true;
	पूर्ण

	अगर (checkpoपूर्णांक_changed) अणु
		अगर (test_opt(sbi, DISABLE_CHECKPOINT)) अणु
			err = f2fs_disable_checkpoपूर्णांक(sbi);
			अगर (err)
				जाओ restore_flush;
		पूर्ण अन्यथा अणु
			f2fs_enable_checkpoपूर्णांक(sbi);
		पूर्ण
	पूर्ण

skip:
#अगर_घोषित CONFIG_QUOTA
	/* Release old quota file names */
	क्रम (i = 0; i < MAXQUOTAS; i++)
		kमुक्त(org_mount_opt.s_qf_names[i]);
#पूर्ण_अगर
	/* Update the POSIXACL Flag */
	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sbi, POSIX_ACL) ? SB_POSIXACL : 0);

	limit_reserve_root(sbi);
	adjust_unusable_cap_perc(sbi);
	*flags = (*flags & ~SB_LAZYTIME) | (sb->s_flags & SB_LAZYTIME);
	वापस 0;
restore_flush:
	अगर (need_restart_flush) अणु
		अगर (f2fs_create_flush_cmd_control(sbi))
			f2fs_warn(sbi, "background flush thread has stopped");
	पूर्ण अन्यथा अगर (need_stop_flush) अणु
		clear_opt(sbi, FLUSH_MERGE);
		f2fs_destroy_flush_cmd_control(sbi, false);
	पूर्ण
restore_ckpt:
	अगर (need_restart_ckpt) अणु
		अगर (f2fs_start_ckpt_thपढ़ो(sbi))
			f2fs_warn(sbi, "background ckpt thread has stopped");
	पूर्ण अन्यथा अगर (need_stop_ckpt) अणु
		f2fs_stop_ckpt_thपढ़ो(sbi);
	पूर्ण
restore_gc:
	अगर (need_restart_gc) अणु
		अगर (f2fs_start_gc_thपढ़ो(sbi))
			f2fs_warn(sbi, "background gc thread has stopped");
	पूर्ण अन्यथा अगर (need_stop_gc) अणु
		f2fs_stop_gc_thपढ़ो(sbi);
	पूर्ण
restore_opts:
#अगर_घोषित CONFIG_QUOTA
	F2FS_OPTION(sbi).s_jquota_fmt = org_mount_opt.s_jquota_fmt;
	क्रम (i = 0; i < MAXQUOTAS; i++) अणु
		kमुक्त(F2FS_OPTION(sbi).s_qf_names[i]);
		F2FS_OPTION(sbi).s_qf_names[i] = org_mount_opt.s_qf_names[i];
	पूर्ण
#पूर्ण_अगर
	sbi->mount_opt = org_mount_opt;
	sb->s_flags = old_sb_flags;
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
/* Read data from quotafile */
अटल sमाप_प्रकार f2fs_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			       माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	काष्ठा address_space *mapping = inode->i_mapping;
	block_t blkidx = F2FS_BYTES_TO_BLK(off);
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	पूर्णांक tocopy;
	माप_प्रकार toपढ़ो;
	loff_t i_size = i_size_पढ़ो(inode);
	काष्ठा page *page;
	अक्षर *kaddr;

	अगर (off > i_size)
		वापस 0;

	अगर (off + len > i_size)
		len = i_size - off;
	toपढ़ो = len;
	जबतक (toपढ़ो > 0) अणु
		tocopy = min_t(अचिन्हित दीर्घ, sb->s_blocksize - offset, toपढ़ो);
repeat:
		page = पढ़ो_cache_page_gfp(mapping, blkidx, GFP_NOFS);
		अगर (IS_ERR(page)) अणु
			अगर (PTR_ERR(page) == -ENOMEM) अणु
				congestion_रुको(BLK_RW_ASYNC,
						DEFAULT_IO_TIMEOUT);
				जाओ repeat;
			पूर्ण
			set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);
			वापस PTR_ERR(page);
		पूर्ण

		lock_page(page);

		अगर (unlikely(page->mapping != mapping)) अणु
			f2fs_put_page(page, 1);
			जाओ repeat;
		पूर्ण
		अगर (unlikely(!PageUptodate(page))) अणु
			f2fs_put_page(page, 1);
			set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);
			वापस -EIO;
		पूर्ण

		kaddr = kmap_atomic(page);
		स_नकल(data, kaddr + offset, tocopy);
		kunmap_atomic(kaddr);
		f2fs_put_page(page, 1);

		offset = 0;
		toपढ़ो -= tocopy;
		data += tocopy;
		blkidx++;
	पूर्ण
	वापस len;
पूर्ण

/* Write to quotafile */
अटल sमाप_प्रकार f2fs_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
				स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	काष्ठा address_space *mapping = inode->i_mapping;
	स्थिर काष्ठा address_space_operations *a_ops = mapping->a_ops;
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	माप_प्रकार toग_लिखो = len;
	काष्ठा page *page;
	व्योम *fsdata = शून्य;
	अक्षर *kaddr;
	पूर्णांक err = 0;
	पूर्णांक tocopy;

	जबतक (toग_लिखो > 0) अणु
		tocopy = min_t(अचिन्हित दीर्घ, sb->s_blocksize - offset,
								toग_लिखो);
retry:
		err = a_ops->ग_लिखो_begin(शून्य, mapping, off, tocopy, 0,
							&page, &fsdata);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOMEM) अणु
				congestion_रुको(BLK_RW_ASYNC,
						DEFAULT_IO_TIMEOUT);
				जाओ retry;
			पूर्ण
			set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);
			अवरोध;
		पूर्ण

		kaddr = kmap_atomic(page);
		स_नकल(kaddr + offset, data, tocopy);
		kunmap_atomic(kaddr);
		flush_dcache_page(page);

		a_ops->ग_लिखो_end(शून्य, mapping, off, tocopy, tocopy,
						page, fsdata);
		offset = 0;
		toग_लिखो -= tocopy;
		off += tocopy;
		data += tocopy;
		cond_resched();
	पूर्ण

	अगर (len == toग_लिखो)
		वापस err;
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	f2fs_mark_inode_dirty_sync(inode, false);
	वापस len - toग_लिखो;
पूर्ण

अटल काष्ठा dquot **f2fs_get_dquots(काष्ठा inode *inode)
अणु
	वापस F2FS_I(inode)->i_dquot;
पूर्ण

अटल qमाप_प्रकार *f2fs_get_reserved_space(काष्ठा inode *inode)
अणु
	वापस &F2FS_I(inode)->i_reserved_quota;
पूर्ण

अटल पूर्णांक f2fs_quota_on_mount(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अगर (is_set_ckpt_flags(sbi, CP_QUOTA_NEED_FSCK_FLAG)) अणु
		f2fs_err(sbi, "quota sysfile may be corrupted, skip loading it");
		वापस 0;
	पूर्ण

	वापस dquot_quota_on_mount(sbi->sb, F2FS_OPTION(sbi).s_qf_names[type],
					F2FS_OPTION(sbi).s_jquota_fmt, type);
पूर्ण

पूर्णांक f2fs_enable_quota_files(काष्ठा f2fs_sb_info *sbi, bool rकरोnly)
अणु
	पूर्णांक enabled = 0;
	पूर्णांक i, err;

	अगर (f2fs_sb_has_quota_ino(sbi) && rकरोnly) अणु
		err = f2fs_enable_quotas(sbi->sb);
		अगर (err) अणु
			f2fs_err(sbi, "Cannot turn on quota_ino: %d", err);
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < MAXQUOTAS; i++) अणु
		अगर (F2FS_OPTION(sbi).s_qf_names[i]) अणु
			err = f2fs_quota_on_mount(sbi, i);
			अगर (!err) अणु
				enabled = 1;
				जारी;
			पूर्ण
			f2fs_err(sbi, "Cannot turn on quotas: %d on %d",
				 err, i);
		पूर्ण
	पूर्ण
	वापस enabled;
पूर्ण

अटल पूर्णांक f2fs_quota_enable(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *qf_inode;
	अचिन्हित दीर्घ qf_inum;
	पूर्णांक err;

	BUG_ON(!f2fs_sb_has_quota_ino(F2FS_SB(sb)));

	qf_inum = f2fs_qf_ino(sb, type);
	अगर (!qf_inum)
		वापस -EPERM;

	qf_inode = f2fs_iget(sb, qf_inum);
	अगर (IS_ERR(qf_inode)) अणु
		f2fs_err(F2FS_SB(sb), "Bad quota inode %u:%lu", type, qf_inum);
		वापस PTR_ERR(qf_inode);
	पूर्ण

	/* Don't account quota क्रम quota files to aव्योम recursion */
	qf_inode->i_flags |= S_NOQUOTA;
	err = dquot_load_quota_inode(qf_inode, type, क्रमmat_id, flags);
	iput(qf_inode);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_enable_quotas(काष्ठा super_block *sb)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक type, err = 0;
	अचिन्हित दीर्घ qf_inum;
	bool quota_mopt[MAXQUOTAS] = अणु
		test_opt(sbi, USRQUOTA),
		test_opt(sbi, GRPQUOTA),
		test_opt(sbi, PRJQUOTA),
	पूर्ण;

	अगर (is_set_ckpt_flags(F2FS_SB(sb), CP_QUOTA_NEED_FSCK_FLAG)) अणु
		f2fs_err(sbi, "quota file may be corrupted, skip loading it");
		वापस 0;
	पूर्ण

	sb_dqopt(sb)->flags |= DQUOT_QUOTA_SYS_खाता;

	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		qf_inum = f2fs_qf_ino(sb, type);
		अगर (qf_inum) अणु
			err = f2fs_quota_enable(sb, type, QFMT_VFS_V1,
				DQUOT_USAGE_ENABLED |
				(quota_mopt[type] ? DQUOT_LIMITS_ENABLED : 0));
			अगर (err) अणु
				f2fs_err(sbi, "Failed to enable quota tracking (type=%d, err=%d). Please run fsck to fix.",
					 type, err);
				क्रम (type--; type >= 0; type--)
					dquot_quota_off(sb, type);
				set_sbi_flag(F2FS_SB(sb),
						SBI_QUOTA_NEED_REPAIR);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक f2fs_quota_sync(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक cnt;
	पूर्णांक ret;

	/*
	 * करो_quotactl
	 *  f2fs_quota_sync
	 *  करोwn_पढ़ो(quota_sem)
	 *  dquot_ग_लिखोback_dquots()
	 *  f2fs_dquot_commit
	 *                            block_operation
	 *                            करोwn_पढ़ो(quota_sem)
	 */
	f2fs_lock_op(sbi);

	करोwn_पढ़ो(&sbi->quota_sem);
	ret = dquot_ग_लिखोback_dquots(sb, type);
	अगर (ret)
		जाओ out;

	/*
	 * Now when everything is written we can discard the pagecache so
	 * that userspace sees the changes.
	 */
	क्रम (cnt = 0; cnt < MAXQUOTAS; cnt++) अणु
		काष्ठा address_space *mapping;

		अगर (type != -1 && cnt != type)
			जारी;
		अगर (!sb_has_quota_active(sb, cnt))
			जारी;

		mapping = dqopt->files[cnt]->i_mapping;

		ret = filemap_fdataग_लिखो(mapping);
		अगर (ret)
			जाओ out;

		/* अगर we are using journalled quota */
		अगर (is_journalled_quota(sbi))
			जारी;

		ret = filemap_fdataरुको(mapping);
		अगर (ret)
			set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);

		inode_lock(dqopt->files[cnt]);
		truncate_inode_pages(&dqopt->files[cnt]->i_data, 0);
		inode_unlock(dqopt->files[cnt]);
	पूर्ण
out:
	अगर (ret)
		set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);
	up_पढ़ो(&sbi->quota_sem);
	f2fs_unlock_op(sbi);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
							स्थिर काष्ठा path *path)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	/* अगर quota sysfile exists, deny enabling quota with specअगरic file */
	अगर (f2fs_sb_has_quota_ino(F2FS_SB(sb))) अणु
		f2fs_err(F2FS_SB(sb), "quota sysfile already exists");
		वापस -EBUSY;
	पूर्ण

	err = f2fs_quota_sync(sb, type);
	अगर (err)
		वापस err;

	err = dquot_quota_on(sb, type, क्रमmat_id, path);
	अगर (err)
		वापस err;

	inode = d_inode(path->dentry);

	inode_lock(inode);
	F2FS_I(inode)->i_flags |= F2FS_NOATIME_FL | F2FS_IMMUTABLE_FL;
	f2fs_set_inode_flags(inode);
	inode_unlock(inode);
	f2fs_mark_inode_dirty_sync(inode, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __f2fs_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	पूर्णांक err;

	अगर (!inode || !igrab(inode))
		वापस dquot_quota_off(sb, type);

	err = f2fs_quota_sync(sb, type);
	अगर (err)
		जाओ out_put;

	err = dquot_quota_off(sb, type);
	अगर (err || f2fs_sb_has_quota_ino(F2FS_SB(sb)))
		जाओ out_put;

	inode_lock(inode);
	F2FS_I(inode)->i_flags &= ~(F2FS_NOATIME_FL | F2FS_IMMUTABLE_FL);
	f2fs_set_inode_flags(inode);
	inode_unlock(inode);
	f2fs_mark_inode_dirty_sync(inode, false);
out_put:
	iput(inode);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक err;

	err = __f2fs_quota_off(sb, type);

	/*
	 * quotactl can shutकरोwn journalled quota, result in inconsistence
	 * between quota record and fs data by following updates, tag the
	 * flag to let fsck be aware of it.
	 */
	अगर (is_journalled_quota(sbi))
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	वापस err;
पूर्ण

व्योम f2fs_quota_off_umount(काष्ठा super_block *sb)
अणु
	पूर्णांक type;
	पूर्णांक err;

	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		err = __f2fs_quota_off(sb, type);
		अगर (err) अणु
			पूर्णांक ret = dquot_quota_off(sb, type);

			f2fs_err(F2FS_SB(sb), "Fail to turn off disk quota (type: %d, err: %d, ret:%d), Please run fsck to fix it.",
				 type, err, ret);
			set_sbi_flag(F2FS_SB(sb), SBI_QUOTA_NEED_REPAIR);
		पूर्ण
	पूर्ण
	/*
	 * In हाल of checkpoपूर्णांक=disable, we must flush quota blocks.
	 * This can cause शून्य exception क्रम node_inode in end_io, since
	 * put_super alपढ़ोy dropped it.
	 */
	sync_fileप्रणाली(sb);
पूर्ण

अटल व्योम f2fs_truncate_quota_inode_pages(काष्ठा super_block *sb)
अणु
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	पूर्णांक type;

	क्रम (type = 0; type < MAXQUOTAS; type++) अणु
		अगर (!dqopt->files[type])
			जारी;
		f2fs_inode_synced(dqopt->files[type]);
	पूर्ण
पूर्ण

अटल पूर्णांक f2fs_dquot_commit(काष्ठा dquot *dquot)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(dquot->dq_sb);
	पूर्णांक ret;

	करोwn_पढ़ो_nested(&sbi->quota_sem, SINGLE_DEPTH_NESTING);
	ret = dquot_commit(dquot);
	अगर (ret < 0)
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	up_पढ़ो(&sbi->quota_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_dquot_acquire(काष्ठा dquot *dquot)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(dquot->dq_sb);
	पूर्णांक ret;

	करोwn_पढ़ो(&sbi->quota_sem);
	ret = dquot_acquire(dquot);
	अगर (ret < 0)
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	up_पढ़ो(&sbi->quota_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_dquot_release(काष्ठा dquot *dquot)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(dquot->dq_sb);
	पूर्णांक ret = dquot_release(dquot);

	अगर (ret < 0)
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_dquot_mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	काष्ठा super_block *sb = dquot->dq_sb;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक ret = dquot_mark_dquot_dirty(dquot);

	/* अगर we are using journalled quota */
	अगर (is_journalled_quota(sbi))
		set_sbi_flag(sbi, SBI_QUOTA_NEED_FLUSH);

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_dquot_commit_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक ret = dquot_commit_info(sb, type);

	अगर (ret < 0)
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_get_projid(काष्ठा inode *inode, kprojid_t *projid)
अणु
	*projid = F2FS_I(inode)->i_projid;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dquot_operations f2fs_quota_operations = अणु
	.get_reserved_space = f2fs_get_reserved_space,
	.ग_लिखो_dquot	= f2fs_dquot_commit,
	.acquire_dquot	= f2fs_dquot_acquire,
	.release_dquot	= f2fs_dquot_release,
	.mark_dirty	= f2fs_dquot_mark_dquot_dirty,
	.ग_लिखो_info	= f2fs_dquot_commit_info,
	.alloc_dquot	= dquot_alloc,
	.destroy_dquot	= dquot_destroy,
	.get_projid	= f2fs_get_projid,
	.get_next_id	= dquot_get_next_id,
पूर्ण;

अटल स्थिर काष्ठा quotactl_ops f2fs_quotactl_ops = अणु
	.quota_on	= f2fs_quota_on,
	.quota_off	= f2fs_quota_off,
	.quota_sync	= f2fs_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqblk	= dquot_get_dqblk,
	.set_dqblk	= dquot_set_dqblk,
	.get_nextdqblk	= dquot_get_next_dqblk,
पूर्ण;
#अन्यथा
पूर्णांक f2fs_quota_sync(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस 0;
पूर्ण

व्योम f2fs_quota_off_umount(काष्ठा super_block *sb)
अणु
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा super_operations f2fs_sops = अणु
	.alloc_inode	= f2fs_alloc_inode,
	.मुक्त_inode	= f2fs_मुक्त_inode,
	.drop_inode	= f2fs_drop_inode,
	.ग_लिखो_inode	= f2fs_ग_लिखो_inode,
	.dirty_inode	= f2fs_dirty_inode,
	.show_options	= f2fs_show_options,
#अगर_घोषित CONFIG_QUOTA
	.quota_पढ़ो	= f2fs_quota_पढ़ो,
	.quota_ग_लिखो	= f2fs_quota_ग_लिखो,
	.get_dquots	= f2fs_get_dquots,
#पूर्ण_अगर
	.evict_inode	= f2fs_evict_inode,
	.put_super	= f2fs_put_super,
	.sync_fs	= f2fs_sync_fs,
	.मुक्तze_fs	= f2fs_मुक्तze,
	.unमुक्तze_fs	= f2fs_unमुक्तze,
	.statfs		= f2fs_statfs,
	.remount_fs	= f2fs_remount,
पूर्ण;

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल पूर्णांक f2fs_get_context(काष्ठा inode *inode, व्योम *ctx, माप_प्रकार len)
अणु
	वापस f2fs_getxattr(inode, F2FS_XATTR_INDEX_ENCRYPTION,
				F2FS_XATTR_NAME_ENCRYPTION_CONTEXT,
				ctx, len, शून्य);
पूर्ण

अटल पूर्णांक f2fs_set_context(काष्ठा inode *inode, स्थिर व्योम *ctx, माप_प्रकार len,
							व्योम *fs_data)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	/*
	 * Encrypting the root directory is not allowed because fsck
	 * expects lost+found directory to exist and reमुख्य unencrypted
	 * अगर LOST_FOUND feature is enabled.
	 *
	 */
	अगर (f2fs_sb_has_lost_found(sbi) &&
			inode->i_ino == F2FS_ROOT_INO(sbi))
		वापस -EPERM;

	वापस f2fs_setxattr(inode, F2FS_XATTR_INDEX_ENCRYPTION,
				F2FS_XATTR_NAME_ENCRYPTION_CONTEXT,
				ctx, len, fs_data, XATTR_CREATE);
पूर्ण

अटल स्थिर जोड़ fscrypt_policy *f2fs_get_dummy_policy(काष्ठा super_block *sb)
अणु
	वापस F2FS_OPTION(F2FS_SB(sb)).dummy_enc_policy.policy;
पूर्ण

अटल bool f2fs_has_stable_inodes(काष्ठा super_block *sb)
अणु
	वापस true;
पूर्ण

अटल व्योम f2fs_get_ino_and_lblk_bits(काष्ठा super_block *sb,
				       पूर्णांक *ino_bits_ret, पूर्णांक *lblk_bits_ret)
अणु
	*ino_bits_ret = 8 * माप(nid_t);
	*lblk_bits_ret = 8 * माप(block_t);
पूर्ण

अटल पूर्णांक f2fs_get_num_devices(काष्ठा super_block *sb)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);

	अगर (f2fs_is_multi_device(sbi))
		वापस sbi->s_ndevs;
	वापस 1;
पूर्ण

अटल व्योम f2fs_get_devices(काष्ठा super_block *sb,
			     काष्ठा request_queue **devs)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	पूर्णांक i;

	क्रम (i = 0; i < sbi->s_ndevs; i++)
		devs[i] = bdev_get_queue(FDEV(i).bdev);
पूर्ण

अटल स्थिर काष्ठा fscrypt_operations f2fs_cryptops = अणु
	.key_prefix		= "f2fs:",
	.get_context		= f2fs_get_context,
	.set_context		= f2fs_set_context,
	.get_dummy_policy	= f2fs_get_dummy_policy,
	.empty_dir		= f2fs_empty_dir,
	.max_namelen		= F2FS_NAME_LEN,
	.has_stable_inodes	= f2fs_has_stable_inodes,
	.get_ino_and_lblk_bits	= f2fs_get_ino_and_lblk_bits,
	.get_num_devices	= f2fs_get_num_devices,
	.get_devices		= f2fs_get_devices,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा inode *f2fs_nfs_get_inode(काष्ठा super_block *sb,
		u64 ino, u32 generation)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	काष्ठा inode *inode;

	अगर (f2fs_check_nid_range(sbi, ino))
		वापस ERR_PTR(-ESTALE);

	/*
	 * f2fs_iget isn't quite right अगर the inode is currently unallocated!
	 * However f2fs_iget currently करोes appropriate checks to handle stale
	 * inodes so everything is OK.
	 */
	inode = f2fs_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (unlikely(generation && inode->i_generation != generation)) अणु
		/* we didn't find the right inode.. */
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा dentry *f2fs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    f2fs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *f2fs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    f2fs_nfs_get_inode);
पूर्ण

अटल स्थिर काष्ठा export_operations f2fs_export_ops = अणु
	.fh_to_dentry = f2fs_fh_to_dentry,
	.fh_to_parent = f2fs_fh_to_parent,
	.get_parent = f2fs_get_parent,
पूर्ण;

loff_t max_file_blocks(काष्ठा inode *inode)
अणु
	loff_t result = 0;
	loff_t leaf_count;

	/*
	 * note: previously, result is equal to (DEF_ADDRS_PER_INODE -
	 * DEFAULT_INLINE_XATTR_ADDRS), but now f2fs try to reserve more
	 * space in inode.i_addr, it will be more safe to reassign
	 * result as zero.
	 */

	अगर (inode && f2fs_compressed_file(inode))
		leaf_count = ADDRS_PER_BLOCK(inode);
	अन्यथा
		leaf_count = DEF_ADDRS_PER_BLOCK;

	/* two direct node blocks */
	result += (leaf_count * 2);

	/* two indirect node blocks */
	leaf_count *= NIDS_PER_BLOCK;
	result += (leaf_count * 2);

	/* one द्विगुन indirect node block */
	leaf_count *= NIDS_PER_BLOCK;
	result += leaf_count;

	वापस result;
पूर्ण

अटल पूर्णांक __f2fs_commit_super(काष्ठा buffer_head *bh,
			काष्ठा f2fs_super_block *super)
अणु
	lock_buffer(bh);
	अगर (super)
		स_नकल(bh->b_data + F2FS_SUPER_OFFSET, super, माप(*super));
	set_buffer_dirty(bh);
	unlock_buffer(bh);

	/* it's rare हाल, we can करो fua all the समय */
	वापस __sync_dirty_buffer(bh, REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
पूर्ण

अटल अंतरभूत bool sanity_check_area_boundary(काष्ठा f2fs_sb_info *sbi,
					काष्ठा buffer_head *bh)
अणु
	काष्ठा f2fs_super_block *raw_super = (काष्ठा f2fs_super_block *)
					(bh->b_data + F2FS_SUPER_OFFSET);
	काष्ठा super_block *sb = sbi->sb;
	u32 segment0_blkaddr = le32_to_cpu(raw_super->segment0_blkaddr);
	u32 cp_blkaddr = le32_to_cpu(raw_super->cp_blkaddr);
	u32 sit_blkaddr = le32_to_cpu(raw_super->sit_blkaddr);
	u32 nat_blkaddr = le32_to_cpu(raw_super->nat_blkaddr);
	u32 ssa_blkaddr = le32_to_cpu(raw_super->ssa_blkaddr);
	u32 मुख्य_blkaddr = le32_to_cpu(raw_super->मुख्य_blkaddr);
	u32 segment_count_ckpt = le32_to_cpu(raw_super->segment_count_ckpt);
	u32 segment_count_sit = le32_to_cpu(raw_super->segment_count_sit);
	u32 segment_count_nat = le32_to_cpu(raw_super->segment_count_nat);
	u32 segment_count_ssa = le32_to_cpu(raw_super->segment_count_ssa);
	u32 segment_count_मुख्य = le32_to_cpu(raw_super->segment_count_मुख्य);
	u32 segment_count = le32_to_cpu(raw_super->segment_count);
	u32 log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	u64 मुख्य_end_blkaddr = मुख्य_blkaddr +
				(segment_count_मुख्य << log_blocks_per_seg);
	u64 seg_end_blkaddr = segment0_blkaddr +
				(segment_count << log_blocks_per_seg);

	अगर (segment0_blkaddr != cp_blkaddr) अणु
		f2fs_info(sbi, "Mismatch start address, segment0(%u) cp_blkaddr(%u)",
			  segment0_blkaddr, cp_blkaddr);
		वापस true;
	पूर्ण

	अगर (cp_blkaddr + (segment_count_ckpt << log_blocks_per_seg) !=
							sit_blkaddr) अणु
		f2fs_info(sbi, "Wrong CP boundary, start(%u) end(%u) blocks(%u)",
			  cp_blkaddr, sit_blkaddr,
			  segment_count_ckpt << log_blocks_per_seg);
		वापस true;
	पूर्ण

	अगर (sit_blkaddr + (segment_count_sit << log_blocks_per_seg) !=
							nat_blkaddr) अणु
		f2fs_info(sbi, "Wrong SIT boundary, start(%u) end(%u) blocks(%u)",
			  sit_blkaddr, nat_blkaddr,
			  segment_count_sit << log_blocks_per_seg);
		वापस true;
	पूर्ण

	अगर (nat_blkaddr + (segment_count_nat << log_blocks_per_seg) !=
							ssa_blkaddr) अणु
		f2fs_info(sbi, "Wrong NAT boundary, start(%u) end(%u) blocks(%u)",
			  nat_blkaddr, ssa_blkaddr,
			  segment_count_nat << log_blocks_per_seg);
		वापस true;
	पूर्ण

	अगर (ssa_blkaddr + (segment_count_ssa << log_blocks_per_seg) !=
							मुख्य_blkaddr) अणु
		f2fs_info(sbi, "Wrong SSA boundary, start(%u) end(%u) blocks(%u)",
			  ssa_blkaddr, मुख्य_blkaddr,
			  segment_count_ssa << log_blocks_per_seg);
		वापस true;
	पूर्ण

	अगर (मुख्य_end_blkaddr > seg_end_blkaddr) अणु
		f2fs_info(sbi, "Wrong MAIN_AREA boundary, start(%u) end(%llu) block(%u)",
			  मुख्य_blkaddr, seg_end_blkaddr,
			  segment_count_मुख्य << log_blocks_per_seg);
		वापस true;
	पूर्ण अन्यथा अगर (मुख्य_end_blkaddr < seg_end_blkaddr) अणु
		पूर्णांक err = 0;
		अक्षर *res;

		/* fix in-memory inक्रमmation all the समय */
		raw_super->segment_count = cpu_to_le32((मुख्य_end_blkaddr -
				segment0_blkaddr) >> log_blocks_per_seg);

		अगर (f2fs_पढ़ोonly(sb) || bdev_पढ़ो_only(sb->s_bdev)) अणु
			set_sbi_flag(sbi, SBI_NEED_SB_WRITE);
			res = "internally";
		पूर्ण अन्यथा अणु
			err = __f2fs_commit_super(bh, शून्य);
			res = err ? "failed" : "done";
		पूर्ण
		f2fs_info(sbi, "Fix alignment : %s, start(%u) end(%llu) block(%u)",
			  res, मुख्य_blkaddr, seg_end_blkaddr,
			  segment_count_मुख्य << log_blocks_per_seg);
		अगर (err)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक sanity_check_raw_super(काष्ठा f2fs_sb_info *sbi,
				काष्ठा buffer_head *bh)
अणु
	block_t segment_count, segs_per_sec, secs_per_zone, segment_count_मुख्य;
	block_t total_sections, blocks_per_seg;
	काष्ठा f2fs_super_block *raw_super = (काष्ठा f2fs_super_block *)
					(bh->b_data + F2FS_SUPER_OFFSET);
	माप_प्रकार crc_offset = 0;
	__u32 crc = 0;

	अगर (le32_to_cpu(raw_super->magic) != F2FS_SUPER_MAGIC) अणु
		f2fs_info(sbi, "Magic Mismatch, valid(0x%x) - read(0x%x)",
			  F2FS_SUPER_MAGIC, le32_to_cpu(raw_super->magic));
		वापस -EINVAL;
	पूर्ण

	/* Check checksum_offset and crc in superblock */
	अगर (__F2FS_HAS_FEATURE(raw_super, F2FS_FEATURE_SB_CHKSUM)) अणु
		crc_offset = le32_to_cpu(raw_super->checksum_offset);
		अगर (crc_offset !=
			दुरत्व(काष्ठा f2fs_super_block, crc)) अणु
			f2fs_info(sbi, "Invalid SB checksum offset: %zu",
				  crc_offset);
			वापस -EFSCORRUPTED;
		पूर्ण
		crc = le32_to_cpu(raw_super->crc);
		अगर (!f2fs_crc_valid(sbi, crc, raw_super, crc_offset)) अणु
			f2fs_info(sbi, "Invalid SB checksum value: %u", crc);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	/* Currently, support only 4KB block size */
	अगर (le32_to_cpu(raw_super->log_blocksize) != F2FS_BLKSIZE_BITS) अणु
		f2fs_info(sbi, "Invalid log_blocksize (%u), supports only %u",
			  le32_to_cpu(raw_super->log_blocksize),
			  F2FS_BLKSIZE_BITS);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* check log blocks per segment */
	अगर (le32_to_cpu(raw_super->log_blocks_per_seg) != 9) अणु
		f2fs_info(sbi, "Invalid log blocks per segment (%u)",
			  le32_to_cpu(raw_super->log_blocks_per_seg));
		वापस -EFSCORRUPTED;
	पूर्ण

	/* Currently, support 512/1024/2048/4096 bytes sector size */
	अगर (le32_to_cpu(raw_super->log_sectorsize) >
				F2FS_MAX_LOG_SECTOR_SIZE ||
		le32_to_cpu(raw_super->log_sectorsize) <
				F2FS_MIN_LOG_SECTOR_SIZE) अणु
		f2fs_info(sbi, "Invalid log sectorsize (%u)",
			  le32_to_cpu(raw_super->log_sectorsize));
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (le32_to_cpu(raw_super->log_sectors_per_block) +
		le32_to_cpu(raw_super->log_sectorsize) !=
			F2FS_MAX_LOG_SECTOR_SIZE) अणु
		f2fs_info(sbi, "Invalid log sectors per block(%u) log sectorsize(%u)",
			  le32_to_cpu(raw_super->log_sectors_per_block),
			  le32_to_cpu(raw_super->log_sectorsize));
		वापस -EFSCORRUPTED;
	पूर्ण

	segment_count = le32_to_cpu(raw_super->segment_count);
	segment_count_मुख्य = le32_to_cpu(raw_super->segment_count_मुख्य);
	segs_per_sec = le32_to_cpu(raw_super->segs_per_sec);
	secs_per_zone = le32_to_cpu(raw_super->secs_per_zone);
	total_sections = le32_to_cpu(raw_super->section_count);

	/* blocks_per_seg should be 512, given the above check */
	blocks_per_seg = 1 << le32_to_cpu(raw_super->log_blocks_per_seg);

	अगर (segment_count > F2FS_MAX_SEGMENT ||
				segment_count < F2FS_MIN_SEGMENTS) अणु
		f2fs_info(sbi, "Invalid segment count (%u)", segment_count);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (total_sections > segment_count_मुख्य || total_sections < 1 ||
			segs_per_sec > segment_count || !segs_per_sec) अणु
		f2fs_info(sbi, "Invalid segment/section count (%u, %u x %u)",
			  segment_count, total_sections, segs_per_sec);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (segment_count_मुख्य != total_sections * segs_per_sec) अणु
		f2fs_info(sbi, "Invalid segment/section count (%u != %u * %u)",
			  segment_count_मुख्य, total_sections, segs_per_sec);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर ((segment_count / segs_per_sec) < total_sections) अणु
		f2fs_info(sbi, "Small segment_count (%u < %u * %u)",
			  segment_count, segs_per_sec, total_sections);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (segment_count > (le64_to_cpu(raw_super->block_count) >> 9)) अणु
		f2fs_info(sbi, "Wrong segment_count / block_count (%u > %llu)",
			  segment_count, le64_to_cpu(raw_super->block_count));
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (RDEV(0).path[0]) अणु
		block_t dev_seg_count = le32_to_cpu(RDEV(0).total_segments);
		पूर्णांक i = 1;

		जबतक (i < MAX_DEVICES && RDEV(i).path[0]) अणु
			dev_seg_count += le32_to_cpu(RDEV(i).total_segments);
			i++;
		पूर्ण
		अगर (segment_count != dev_seg_count) अणु
			f2fs_info(sbi, "Segment count (%u) mismatch with total segments from devices (%u)",
					segment_count, dev_seg_count);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__F2FS_HAS_FEATURE(raw_super, F2FS_FEATURE_BLKZONED) &&
					!bdev_is_zoned(sbi->sb->s_bdev)) अणु
			f2fs_info(sbi, "Zoned block device path is missing");
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	अगर (secs_per_zone > total_sections || !secs_per_zone) अणु
		f2fs_info(sbi, "Wrong secs_per_zone / total_sections (%u, %u)",
			  secs_per_zone, total_sections);
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (le32_to_cpu(raw_super->extension_count) > F2FS_MAX_EXTENSION ||
			raw_super->hot_ext_count > F2FS_MAX_EXTENSION ||
			(le32_to_cpu(raw_super->extension_count) +
			raw_super->hot_ext_count) > F2FS_MAX_EXTENSION) अणु
		f2fs_info(sbi, "Corrupted extension count (%u + %u > %u)",
			  le32_to_cpu(raw_super->extension_count),
			  raw_super->hot_ext_count,
			  F2FS_MAX_EXTENSION);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (le32_to_cpu(raw_super->cp_payload) >
				(blocks_per_seg - F2FS_CP_PACKS)) अणु
		f2fs_info(sbi, "Insane cp_payload (%u > %u)",
			  le32_to_cpu(raw_super->cp_payload),
			  blocks_per_seg - F2FS_CP_PACKS);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* check reserved ino info */
	अगर (le32_to_cpu(raw_super->node_ino) != 1 ||
		le32_to_cpu(raw_super->meta_ino) != 2 ||
		le32_to_cpu(raw_super->root_ino) != 3) अणु
		f2fs_info(sbi, "Invalid Fs Meta Ino: node(%u) meta(%u) root(%u)",
			  le32_to_cpu(raw_super->node_ino),
			  le32_to_cpu(raw_super->meta_ino),
			  le32_to_cpu(raw_super->root_ino));
		वापस -EFSCORRUPTED;
	पूर्ण

	/* check CP/SIT/NAT/SSA/MAIN_AREA area boundary */
	अगर (sanity_check_area_boundary(sbi, bh))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

पूर्णांक f2fs_sanity_check_ckpt(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित पूर्णांक total, fsmeta;
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	अचिन्हित पूर्णांक ovp_segments, reserved_segments;
	अचिन्हित पूर्णांक मुख्य_segs, blocks_per_seg;
	अचिन्हित पूर्णांक sit_segs, nat_segs;
	अचिन्हित पूर्णांक sit_biपंचांगap_size, nat_biपंचांगap_size;
	अचिन्हित पूर्णांक log_blocks_per_seg;
	अचिन्हित पूर्णांक segment_count_मुख्य;
	अचिन्हित पूर्णांक cp_pack_start_sum, cp_payload;
	block_t user_block_count, valid_user_blocks;
	block_t avail_node_count, valid_node_count;
	पूर्णांक i, j;

	total = le32_to_cpu(raw_super->segment_count);
	fsmeta = le32_to_cpu(raw_super->segment_count_ckpt);
	sit_segs = le32_to_cpu(raw_super->segment_count_sit);
	fsmeta += sit_segs;
	nat_segs = le32_to_cpu(raw_super->segment_count_nat);
	fsmeta += nat_segs;
	fsmeta += le32_to_cpu(ckpt->rsvd_segment_count);
	fsmeta += le32_to_cpu(raw_super->segment_count_ssa);

	अगर (unlikely(fsmeta >= total))
		वापस 1;

	ovp_segments = le32_to_cpu(ckpt->overprov_segment_count);
	reserved_segments = le32_to_cpu(ckpt->rsvd_segment_count);

	अगर (unlikely(fsmeta < F2FS_MIN_META_SEGMENTS ||
			ovp_segments == 0 || reserved_segments == 0)) अणु
		f2fs_err(sbi, "Wrong layout: check mkfs.f2fs version");
		वापस 1;
	पूर्ण

	user_block_count = le64_to_cpu(ckpt->user_block_count);
	segment_count_मुख्य = le32_to_cpu(raw_super->segment_count_मुख्य);
	log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	अगर (!user_block_count || user_block_count >=
			segment_count_मुख्य << log_blocks_per_seg) अणु
		f2fs_err(sbi, "Wrong user_block_count: %u",
			 user_block_count);
		वापस 1;
	पूर्ण

	valid_user_blocks = le64_to_cpu(ckpt->valid_block_count);
	अगर (valid_user_blocks > user_block_count) अणु
		f2fs_err(sbi, "Wrong valid_user_blocks: %u, user_block_count: %u",
			 valid_user_blocks, user_block_count);
		वापस 1;
	पूर्ण

	valid_node_count = le32_to_cpu(ckpt->valid_node_count);
	avail_node_count = sbi->total_node_count - F2FS_RESERVED_NODE_NUM;
	अगर (valid_node_count > avail_node_count) अणु
		f2fs_err(sbi, "Wrong valid_node_count: %u, avail_node_count: %u",
			 valid_node_count, avail_node_count);
		वापस 1;
	पूर्ण

	मुख्य_segs = le32_to_cpu(raw_super->segment_count_मुख्य);
	blocks_per_seg = sbi->blocks_per_seg;

	क्रम (i = 0; i < NR_CURSEG_NODE_TYPE; i++) अणु
		अगर (le32_to_cpu(ckpt->cur_node_segno[i]) >= मुख्य_segs ||
			le16_to_cpu(ckpt->cur_node_blkoff[i]) >= blocks_per_seg)
			वापस 1;
		क्रम (j = i + 1; j < NR_CURSEG_NODE_TYPE; j++) अणु
			अगर (le32_to_cpu(ckpt->cur_node_segno[i]) ==
				le32_to_cpu(ckpt->cur_node_segno[j])) अणु
				f2fs_err(sbi, "Node segment (%u, %u) has the same segno: %u",
					 i, j,
					 le32_to_cpu(ckpt->cur_node_segno[i]));
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NR_CURSEG_DATA_TYPE; i++) अणु
		अगर (le32_to_cpu(ckpt->cur_data_segno[i]) >= मुख्य_segs ||
			le16_to_cpu(ckpt->cur_data_blkoff[i]) >= blocks_per_seg)
			वापस 1;
		क्रम (j = i + 1; j < NR_CURSEG_DATA_TYPE; j++) अणु
			अगर (le32_to_cpu(ckpt->cur_data_segno[i]) ==
				le32_to_cpu(ckpt->cur_data_segno[j])) अणु
				f2fs_err(sbi, "Data segment (%u, %u) has the same segno: %u",
					 i, j,
					 le32_to_cpu(ckpt->cur_data_segno[i]));
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NR_CURSEG_NODE_TYPE; i++) अणु
		क्रम (j = 0; j < NR_CURSEG_DATA_TYPE; j++) अणु
			अगर (le32_to_cpu(ckpt->cur_node_segno[i]) ==
				le32_to_cpu(ckpt->cur_data_segno[j])) अणु
				f2fs_err(sbi, "Node segment (%u) and Data segment (%u) has the same segno: %u",
					 i, j,
					 le32_to_cpu(ckpt->cur_node_segno[i]));
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	sit_biपंचांगap_size = le32_to_cpu(ckpt->sit_ver_biपंचांगap_bytesize);
	nat_biपंचांगap_size = le32_to_cpu(ckpt->nat_ver_biपंचांगap_bytesize);

	अगर (sit_biपंचांगap_size != ((sit_segs / 2) << log_blocks_per_seg) / 8 ||
		nat_biपंचांगap_size != ((nat_segs / 2) << log_blocks_per_seg) / 8) अणु
		f2fs_err(sbi, "Wrong bitmap size: sit: %u, nat:%u",
			 sit_biपंचांगap_size, nat_biपंचांगap_size);
		वापस 1;
	पूर्ण

	cp_pack_start_sum = __start_sum_addr(sbi);
	cp_payload = __cp_payload(sbi);
	अगर (cp_pack_start_sum < cp_payload + 1 ||
		cp_pack_start_sum > blocks_per_seg - 1 -
			NR_CURSEG_PERSIST_TYPE) अणु
		f2fs_err(sbi, "Wrong cp_pack_start_sum: %u",
			 cp_pack_start_sum);
		वापस 1;
	पूर्ण

	अगर (__is_set_ckpt_flags(ckpt, CP_LARGE_NAT_BITMAP_FLAG) &&
		le32_to_cpu(ckpt->checksum_offset) != CP_MIN_CHKSUM_OFFSET) अणु
		f2fs_warn(sbi, "using deprecated layout of large_nat_bitmap, "
			  "please run fsck v1.13.0 or higher to repair, chksum_offset: %u, "
			  "fixed with patch: \"f2fs-tools: relocate chksum_offset for large_nat_bitmap feature\"",
			  le32_to_cpu(ckpt->checksum_offset));
		वापस 1;
	पूर्ण

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		f2fs_err(sbi, "A bug case: need to run fsck");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_sb_info(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *raw_super = sbi->raw_super;
	पूर्णांक i;

	sbi->log_sectors_per_block =
		le32_to_cpu(raw_super->log_sectors_per_block);
	sbi->log_blocksize = le32_to_cpu(raw_super->log_blocksize);
	sbi->blocksize = 1 << sbi->log_blocksize;
	sbi->log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	sbi->blocks_per_seg = 1 << sbi->log_blocks_per_seg;
	sbi->segs_per_sec = le32_to_cpu(raw_super->segs_per_sec);
	sbi->secs_per_zone = le32_to_cpu(raw_super->secs_per_zone);
	sbi->total_sections = le32_to_cpu(raw_super->section_count);
	sbi->total_node_count =
		(le32_to_cpu(raw_super->segment_count_nat) / 2)
			* sbi->blocks_per_seg * NAT_ENTRY_PER_BLOCK;
	F2FS_ROOT_INO(sbi) = le32_to_cpu(raw_super->root_ino);
	F2FS_NODE_INO(sbi) = le32_to_cpu(raw_super->node_ino);
	F2FS_META_INO(sbi) = le32_to_cpu(raw_super->meta_ino);
	sbi->cur_victim_sec = शून्य_SECNO;
	sbi->next_victim_seg[BG_GC] = शून्य_SEGNO;
	sbi->next_victim_seg[FG_GC] = शून्य_SEGNO;
	sbi->max_victim_search = DEF_MAX_VICTIM_SEARCH;
	sbi->migration_granularity = sbi->segs_per_sec;

	sbi->dir_level = DEF_सूची_LEVEL;
	sbi->पूर्णांकerval_समय[CP_TIME] = DEF_CP_INTERVAL;
	sbi->पूर्णांकerval_समय[REQ_TIME] = DEF_IDLE_INTERVAL;
	sbi->पूर्णांकerval_समय[DISCARD_TIME] = DEF_IDLE_INTERVAL;
	sbi->पूर्णांकerval_समय[GC_TIME] = DEF_IDLE_INTERVAL;
	sbi->पूर्णांकerval_समय[DISABLE_TIME] = DEF_DISABLE_INTERVAL;
	sbi->पूर्णांकerval_समय[UMOUNT_DISCARD_TIMEOUT] =
				DEF_UMOUNT_DISCARD_TIMEOUT;
	clear_sbi_flag(sbi, SBI_NEED_FSCK);

	क्रम (i = 0; i < NR_COUNT_TYPE; i++)
		atomic_set(&sbi->nr_pages[i], 0);

	क्रम (i = 0; i < META; i++)
		atomic_set(&sbi->wb_sync_req[i], 0);

	INIT_LIST_HEAD(&sbi->s_list);
	mutex_init(&sbi->umount_mutex);
	init_rwsem(&sbi->io_order_lock);
	spin_lock_init(&sbi->cp_lock);

	sbi->dirty_device = 0;
	spin_lock_init(&sbi->dev_lock);

	init_rwsem(&sbi->sb_lock);
	init_rwsem(&sbi->pin_sem);
पूर्ण

अटल पूर्णांक init_percpu_info(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक err;

	err = percpu_counter_init(&sbi->alloc_valid_block_count, 0, GFP_KERNEL);
	अगर (err)
		वापस err;

	err = percpu_counter_init(&sbi->total_valid_inode_count, 0,
								GFP_KERNEL);
	अगर (err)
		percpu_counter_destroy(&sbi->alloc_valid_block_count);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED

काष्ठा f2fs_report_zones_args अणु
	काष्ठा f2fs_dev_info *dev;
	bool zone_cap_mismatch;
पूर्ण;

अटल पूर्णांक f2fs_report_zone_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
			      व्योम *data)
अणु
	काष्ठा f2fs_report_zones_args *rz_args = data;

	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस 0;

	set_bit(idx, rz_args->dev->blkz_seq);
	rz_args->dev->zone_capacity_blocks[idx] = zone->capacity >>
						F2FS_LOG_SECTORS_PER_BLOCK;
	अगर (zone->len != zone->capacity && !rz_args->zone_cap_mismatch)
		rz_args->zone_cap_mismatch = true;

	वापस 0;
पूर्ण

अटल पूर्णांक init_blkz_info(काष्ठा f2fs_sb_info *sbi, पूर्णांक devi)
अणु
	काष्ठा block_device *bdev = FDEV(devi).bdev;
	sector_t nr_sectors = bdev_nr_sectors(bdev);
	काष्ठा f2fs_report_zones_args rep_zone_arg;
	पूर्णांक ret;

	अगर (!f2fs_sb_has_blkzoned(sbi))
		वापस 0;

	अगर (sbi->blocks_per_blkz && sbi->blocks_per_blkz !=
				SECTOR_TO_BLOCK(bdev_zone_sectors(bdev)))
		वापस -EINVAL;
	sbi->blocks_per_blkz = SECTOR_TO_BLOCK(bdev_zone_sectors(bdev));
	अगर (sbi->log_blocks_per_blkz && sbi->log_blocks_per_blkz !=
				__ilog2_u32(sbi->blocks_per_blkz))
		वापस -EINVAL;
	sbi->log_blocks_per_blkz = __ilog2_u32(sbi->blocks_per_blkz);
	FDEV(devi).nr_blkz = SECTOR_TO_BLOCK(nr_sectors) >>
					sbi->log_blocks_per_blkz;
	अगर (nr_sectors & (bdev_zone_sectors(bdev) - 1))
		FDEV(devi).nr_blkz++;

	FDEV(devi).blkz_seq = f2fs_kvzalloc(sbi,
					BITS_TO_LONGS(FDEV(devi).nr_blkz)
					* माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
	अगर (!FDEV(devi).blkz_seq)
		वापस -ENOMEM;

	/* Get block zones type and zone-capacity */
	FDEV(devi).zone_capacity_blocks = f2fs_kzalloc(sbi,
					FDEV(devi).nr_blkz * माप(block_t),
					GFP_KERNEL);
	अगर (!FDEV(devi).zone_capacity_blocks)
		वापस -ENOMEM;

	rep_zone_arg.dev = &FDEV(devi);
	rep_zone_arg.zone_cap_mismatch = false;

	ret = blkdev_report_zones(bdev, 0, BLK_ALL_ZONES, f2fs_report_zone_cb,
				  &rep_zone_arg);
	अगर (ret < 0)
		वापस ret;

	अगर (!rep_zone_arg.zone_cap_mismatch) अणु
		kमुक्त(FDEV(devi).zone_capacity_blocks);
		FDEV(devi).zone_capacity_blocks = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Read f2fs raw super block.
 * Because we have two copies of super block, so पढ़ो both of them
 * to get the first valid one. If any one of them is broken, we pass
 * them recovery flag back to the caller.
 */
अटल पूर्णांक पढ़ो_raw_super_block(काष्ठा f2fs_sb_info *sbi,
			काष्ठा f2fs_super_block **raw_super,
			पूर्णांक *valid_super_block, पूर्णांक *recovery)
अणु
	काष्ठा super_block *sb = sbi->sb;
	पूर्णांक block;
	काष्ठा buffer_head *bh;
	काष्ठा f2fs_super_block *super;
	पूर्णांक err = 0;

	super = kzalloc(माप(काष्ठा f2fs_super_block), GFP_KERNEL);
	अगर (!super)
		वापस -ENOMEM;

	क्रम (block = 0; block < 2; block++) अणु
		bh = sb_bपढ़ो(sb, block);
		अगर (!bh) अणु
			f2fs_err(sbi, "Unable to read %dth superblock",
				 block + 1);
			err = -EIO;
			*recovery = 1;
			जारी;
		पूर्ण

		/* sanity checking of raw super */
		err = sanity_check_raw_super(sbi, bh);
		अगर (err) अणु
			f2fs_err(sbi, "Can't find valid F2FS filesystem in %dth superblock",
				 block + 1);
			brअन्यथा(bh);
			*recovery = 1;
			जारी;
		पूर्ण

		अगर (!*raw_super) अणु
			स_नकल(super, bh->b_data + F2FS_SUPER_OFFSET,
							माप(*super));
			*valid_super_block = block;
			*raw_super = super;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण

	/* No valid superblock */
	अगर (!*raw_super)
		kमुक्त(super);
	अन्यथा
		err = 0;

	वापस err;
पूर्ण

पूर्णांक f2fs_commit_super(काष्ठा f2fs_sb_info *sbi, bool recover)
अणु
	काष्ठा buffer_head *bh;
	__u32 crc = 0;
	पूर्णांक err;

	अगर ((recover && f2fs_पढ़ोonly(sbi->sb)) ||
				bdev_पढ़ो_only(sbi->sb->s_bdev)) अणु
		set_sbi_flag(sbi, SBI_NEED_SB_WRITE);
		वापस -EROFS;
	पूर्ण

	/* we should update superblock crc here */
	अगर (!recover && f2fs_sb_has_sb_chksum(sbi)) अणु
		crc = f2fs_crc32(sbi, F2FS_RAW_SUPER(sbi),
				दुरत्व(काष्ठा f2fs_super_block, crc));
		F2FS_RAW_SUPER(sbi)->crc = cpu_to_le32(crc);
	पूर्ण

	/* ग_लिखो back-up superblock first */
	bh = sb_bपढ़ो(sbi->sb, sbi->valid_super_block ? 0 : 1);
	अगर (!bh)
		वापस -EIO;
	err = __f2fs_commit_super(bh, F2FS_RAW_SUPER(sbi));
	brअन्यथा(bh);

	/* अगर we are in recovery path, skip writing valid superblock */
	अगर (recover || err)
		वापस err;

	/* ग_लिखो current valid superblock */
	bh = sb_bपढ़ो(sbi->sb, sbi->valid_super_block);
	अगर (!bh)
		वापस -EIO;
	err = __f2fs_commit_super(bh, F2FS_RAW_SUPER(sbi));
	brअन्यथा(bh);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_scan_devices(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	अचिन्हित पूर्णांक max_devices = MAX_DEVICES;
	पूर्णांक i;

	/* Initialize single device inक्रमmation */
	अगर (!RDEV(0).path[0]) अणु
		अगर (!bdev_is_zoned(sbi->sb->s_bdev))
			वापस 0;
		max_devices = 1;
	पूर्ण

	/*
	 * Initialize multiple devices inक्रमmation, or single
	 * zoned block device inक्रमmation.
	 */
	sbi->devs = f2fs_kzalloc(sbi,
				 array_size(max_devices,
					    माप(काष्ठा f2fs_dev_info)),
				 GFP_KERNEL);
	अगर (!sbi->devs)
		वापस -ENOMEM;

	क्रम (i = 0; i < max_devices; i++) अणु

		अगर (i > 0 && !RDEV(i).path[0])
			अवरोध;

		अगर (max_devices == 1) अणु
			/* Single zoned block device mount */
			FDEV(0).bdev =
				blkdev_get_by_dev(sbi->sb->s_bdev->bd_dev,
					sbi->sb->s_mode, sbi->sb->s_type);
		पूर्ण अन्यथा अणु
			/* Multi-device mount */
			स_नकल(FDEV(i).path, RDEV(i).path, MAX_PATH_LEN);
			FDEV(i).total_segments =
				le32_to_cpu(RDEV(i).total_segments);
			अगर (i == 0) अणु
				FDEV(i).start_blk = 0;
				FDEV(i).end_blk = FDEV(i).start_blk +
				    (FDEV(i).total_segments <<
				    sbi->log_blocks_per_seg) - 1 +
				    le32_to_cpu(raw_super->segment0_blkaddr);
			पूर्ण अन्यथा अणु
				FDEV(i).start_blk = FDEV(i - 1).end_blk + 1;
				FDEV(i).end_blk = FDEV(i).start_blk +
					(FDEV(i).total_segments <<
					sbi->log_blocks_per_seg) - 1;
			पूर्ण
			FDEV(i).bdev = blkdev_get_by_path(FDEV(i).path,
					sbi->sb->s_mode, sbi->sb->s_type);
		पूर्ण
		अगर (IS_ERR(FDEV(i).bdev))
			वापस PTR_ERR(FDEV(i).bdev);

		/* to release errored devices */
		sbi->s_ndevs = i + 1;

#अगर_घोषित CONFIG_BLK_DEV_ZONED
		अगर (bdev_zoned_model(FDEV(i).bdev) == BLK_ZONED_HM &&
				!f2fs_sb_has_blkzoned(sbi)) अणु
			f2fs_err(sbi, "Zoned block device feature not enabled\n");
			वापस -EINVAL;
		पूर्ण
		अगर (bdev_zoned_model(FDEV(i).bdev) != BLK_ZONED_NONE) अणु
			अगर (init_blkz_info(sbi, i)) अणु
				f2fs_err(sbi, "Failed to initialize F2FS blkzone information");
				वापस -EINVAL;
			पूर्ण
			अगर (max_devices == 1)
				अवरोध;
			f2fs_info(sbi, "Mount Device [%2d]: %20s, %8u, %8x - %8x (zone: %s)",
				  i, FDEV(i).path,
				  FDEV(i).total_segments,
				  FDEV(i).start_blk, FDEV(i).end_blk,
				  bdev_zoned_model(FDEV(i).bdev) == BLK_ZONED_HA ?
				  "Host-aware" : "Host-managed");
			जारी;
		पूर्ण
#पूर्ण_अगर
		f2fs_info(sbi, "Mount Device [%2d]: %20s, %8u, %8x - %8x",
			  i, FDEV(i).path,
			  FDEV(i).total_segments,
			  FDEV(i).start_blk, FDEV(i).end_blk);
	पूर्ण
	f2fs_info(sbi,
		  "IO Block Size: %8d KB", F2FS_IO_SIZE_KB(sbi));
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_setup_हालfold(काष्ठा f2fs_sb_info *sbi)
अणु
#अगर_घोषित CONFIG_UNICODE
	अगर (f2fs_sb_has_हालfold(sbi) && !sbi->sb->s_encoding) अणु
		स्थिर काष्ठा f2fs_sb_encodings *encoding_info;
		काष्ठा unicode_map *encoding;
		__u16 encoding_flags;

		अगर (f2fs_sb_पढ़ो_encoding(sbi->raw_super, &encoding_info,
					  &encoding_flags)) अणु
			f2fs_err(sbi,
				 "Encoding requested by superblock is unknown");
			वापस -EINVAL;
		पूर्ण

		encoding = utf8_load(encoding_info->version);
		अगर (IS_ERR(encoding)) अणु
			f2fs_err(sbi,
				 "can't mount with superblock charset: %s-%s "
				 "not supported by the kernel. flags: 0x%x.",
				 encoding_info->name, encoding_info->version,
				 encoding_flags);
			वापस PTR_ERR(encoding);
		पूर्ण
		f2fs_info(sbi, "Using encoding defined by superblock: "
			 "%s-%s with flags 0x%hx", encoding_info->name,
			 encoding_info->version?:"\b", encoding_flags);

		sbi->sb->s_encoding = encoding;
		sbi->sb->s_encoding_flags = encoding_flags;
	पूर्ण
#अन्यथा
	अगर (f2fs_sb_has_हालfold(sbi)) अणु
		f2fs_err(sbi, "Filesystem with casefold feature cannot be mounted without CONFIG_UNICODE");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम f2fs_tuning_parameters(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_sm_info *sm_i = SM_I(sbi);

	/* adjust parameters according to the volume size */
	अगर (sm_i->मुख्य_segments <= SMALL_VOLUME_SEGMENTS) अणु
		F2FS_OPTION(sbi).alloc_mode = ALLOC_MODE_REUSE;
		sm_i->dcc_info->discard_granularity = 1;
		sm_i->ipu_policy = 1 << F2FS_IPU_FORCE;
	पूर्ण

	sbi->सूची_पढ़ो_ra = 1;
पूर्ण

अटल पूर्णांक f2fs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा f2fs_sb_info *sbi;
	काष्ठा f2fs_super_block *raw_super;
	काष्ठा inode *root;
	पूर्णांक err;
	bool skip_recovery = false, need_fsck = false;
	अक्षर *options = शून्य;
	पूर्णांक recovery, i, valid_super_block;
	काष्ठा curseg_info *seg_i;
	पूर्णांक retry_cnt = 1;

try_onemore:
	err = -EINVAL;
	raw_super = शून्य;
	valid_super_block = -1;
	recovery = 0;

	/* allocate memory क्रम f2fs-specअगरic super block info */
	sbi = kzalloc(माप(काष्ठा f2fs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sbi->sb = sb;

	/* Load the checksum driver */
	sbi->s_chksum_driver = crypto_alloc_shash("crc32", 0, 0);
	अगर (IS_ERR(sbi->s_chksum_driver)) अणु
		f2fs_err(sbi, "Cannot load crc32 driver.");
		err = PTR_ERR(sbi->s_chksum_driver);
		sbi->s_chksum_driver = शून्य;
		जाओ मुक्त_sbi;
	पूर्ण

	/* set a block size */
	अगर (unlikely(!sb_set_blocksize(sb, F2FS_BLKSIZE))) अणु
		f2fs_err(sbi, "unable to set blocksize");
		जाओ मुक्त_sbi;
	पूर्ण

	err = पढ़ो_raw_super_block(sbi, &raw_super, &valid_super_block,
								&recovery);
	अगर (err)
		जाओ मुक्त_sbi;

	sb->s_fs_info = sbi;
	sbi->raw_super = raw_super;

	/* precompute checksum seed क्रम metadata */
	अगर (f2fs_sb_has_inode_chksum(sbi))
		sbi->s_chksum_seed = f2fs_chksum(sbi, ~0, raw_super->uuid,
						माप(raw_super->uuid));

	शेष_options(sbi);
	/* parse mount options */
	options = kstrdup((स्थिर अक्षर *)data, GFP_KERNEL);
	अगर (data && !options) अणु
		err = -ENOMEM;
		जाओ मुक्त_sb_buf;
	पूर्ण

	err = parse_options(sb, options, false);
	अगर (err)
		जाओ मुक्त_options;

	sb->s_maxbytes = max_file_blocks(शून्य) <<
				le32_to_cpu(raw_super->log_blocksize);
	sb->s_max_links = F2FS_LINK_MAX;

	err = f2fs_setup_हालfold(sbi);
	अगर (err)
		जाओ मुक्त_options;

#अगर_घोषित CONFIG_QUOTA
	sb->dq_op = &f2fs_quota_operations;
	sb->s_qcop = &f2fs_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP | QTYPE_MASK_PRJ;

	अगर (f2fs_sb_has_quota_ino(sbi)) अणु
		क्रम (i = 0; i < MAXQUOTAS; i++) अणु
			अगर (f2fs_qf_ino(sbi->sb, i))
				sbi->nquota_files++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	sb->s_op = &f2fs_sops;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	sb->s_cop = &f2fs_cryptops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
	sb->s_vop = &f2fs_verityops;
#पूर्ण_अगर
	sb->s_xattr = f2fs_xattr_handlers;
	sb->s_export_op = &f2fs_export_ops;
	sb->s_magic = F2FS_SUPER_MAGIC;
	sb->s_समय_gran = 1;
	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sbi, POSIX_ACL) ? SB_POSIXACL : 0);
	स_नकल(&sb->s_uuid, raw_super->uuid, माप(raw_super->uuid));
	sb->s_अगरlags |= SB_I_CGROUPWB;

	/* init f2fs-specअगरic super block info */
	sbi->valid_super_block = valid_super_block;
	init_rwsem(&sbi->gc_lock);
	mutex_init(&sbi->ग_लिखोpages);
	init_rwsem(&sbi->cp_global_sem);
	init_rwsem(&sbi->node_ग_लिखो);
	init_rwsem(&sbi->node_change);

	/* disallow all the data/node/meta page ग_लिखोs */
	set_sbi_flag(sbi, SBI_POR_DOING);
	spin_lock_init(&sbi->stat_lock);

	/* init iostat info */
	spin_lock_init(&sbi->iostat_lock);
	sbi->iostat_enable = false;
	sbi->iostat_period_ms = DEFAULT_IOSTAT_PERIOD_MS;

	क्रम (i = 0; i < NR_PAGE_TYPE; i++) अणु
		पूर्णांक n = (i == META) ? 1 : NR_TEMP_TYPE;
		पूर्णांक j;

		sbi->ग_लिखो_io[i] =
			f2fs_kदो_स्मृति(sbi,
				     array_size(n,
						माप(काष्ठा f2fs_bio_info)),
				     GFP_KERNEL);
		अगर (!sbi->ग_लिखो_io[i]) अणु
			err = -ENOMEM;
			जाओ मुक्त_bio_info;
		पूर्ण

		क्रम (j = HOT; j < n; j++) अणु
			init_rwsem(&sbi->ग_लिखो_io[i][j].io_rwsem);
			sbi->ग_लिखो_io[i][j].sbi = sbi;
			sbi->ग_लिखो_io[i][j].bio = शून्य;
			spin_lock_init(&sbi->ग_लिखो_io[i][j].io_lock);
			INIT_LIST_HEAD(&sbi->ग_लिखो_io[i][j].io_list);
			INIT_LIST_HEAD(&sbi->ग_लिखो_io[i][j].bio_list);
			init_rwsem(&sbi->ग_लिखो_io[i][j].bio_list_lock);
		पूर्ण
	पूर्ण

	init_rwsem(&sbi->cp_rwsem);
	init_rwsem(&sbi->quota_sem);
	init_रुकोqueue_head(&sbi->cp_रुको);
	init_sb_info(sbi);

	err = init_percpu_info(sbi);
	अगर (err)
		जाओ मुक्त_bio_info;

	अगर (F2FS_IO_ALIGNED(sbi)) अणु
		sbi->ग_लिखो_io_dummy =
			mempool_create_page_pool(2 * (F2FS_IO_SIZE(sbi) - 1), 0);
		अगर (!sbi->ग_लिखो_io_dummy) अणु
			err = -ENOMEM;
			जाओ मुक्त_percpu;
		पूर्ण
	पूर्ण

	/* init per sbi slab cache */
	err = f2fs_init_xattr_caches(sbi);
	अगर (err)
		जाओ मुक्त_io_dummy;
	err = f2fs_init_page_array_cache(sbi);
	अगर (err)
		जाओ मुक्त_xattr_cache;

	/* get an inode क्रम meta space */
	sbi->meta_inode = f2fs_iget(sb, F2FS_META_INO(sbi));
	अगर (IS_ERR(sbi->meta_inode)) अणु
		f2fs_err(sbi, "Failed to read F2FS meta data inode");
		err = PTR_ERR(sbi->meta_inode);
		जाओ मुक्त_page_array_cache;
	पूर्ण

	err = f2fs_get_valid_checkpoपूर्णांक(sbi);
	अगर (err) अणु
		f2fs_err(sbi, "Failed to get valid F2FS checkpoint");
		जाओ मुक्त_meta_inode;
	पूर्ण

	अगर (__is_set_ckpt_flags(F2FS_CKPT(sbi), CP_QUOTA_NEED_FSCK_FLAG))
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	अगर (__is_set_ckpt_flags(F2FS_CKPT(sbi), CP_DISABLED_QUICK_FLAG)) अणु
		set_sbi_flag(sbi, SBI_CP_DISABLED_QUICK);
		sbi->पूर्णांकerval_समय[DISABLE_TIME] = DEF_DISABLE_QUICK_INTERVAL;
	पूर्ण

	अगर (__is_set_ckpt_flags(F2FS_CKPT(sbi), CP_FSCK_FLAG))
		set_sbi_flag(sbi, SBI_NEED_FSCK);

	/* Initialize device list */
	err = f2fs_scan_devices(sbi);
	अगर (err) अणु
		f2fs_err(sbi, "Failed to find devices");
		जाओ मुक्त_devices;
	पूर्ण

	err = f2fs_init_post_पढ़ो_wq(sbi);
	अगर (err) अणु
		f2fs_err(sbi, "Failed to initialize post read workqueue");
		जाओ मुक्त_devices;
	पूर्ण

	sbi->total_valid_node_count =
				le32_to_cpu(sbi->ckpt->valid_node_count);
	percpu_counter_set(&sbi->total_valid_inode_count,
				le32_to_cpu(sbi->ckpt->valid_inode_count));
	sbi->user_block_count = le64_to_cpu(sbi->ckpt->user_block_count);
	sbi->total_valid_block_count =
				le64_to_cpu(sbi->ckpt->valid_block_count);
	sbi->last_valid_block_count = sbi->total_valid_block_count;
	sbi->reserved_blocks = 0;
	sbi->current_reserved_blocks = 0;
	limit_reserve_root(sbi);
	adjust_unusable_cap_perc(sbi);

	क्रम (i = 0; i < NR_INODE_TYPE; i++) अणु
		INIT_LIST_HEAD(&sbi->inode_list[i]);
		spin_lock_init(&sbi->inode_lock[i]);
	पूर्ण
	mutex_init(&sbi->flush_lock);

	f2fs_init_extent_cache_info(sbi);

	f2fs_init_ino_entry_info(sbi);

	f2fs_init_fsync_node_info(sbi);

	/* setup checkpoपूर्णांक request control and start checkpoपूर्णांक issue thपढ़ो */
	f2fs_init_ckpt_req_control(sbi);
	अगर (!f2fs_पढ़ोonly(sb) && !test_opt(sbi, DISABLE_CHECKPOINT) &&
			test_opt(sbi, MERGE_CHECKPOINT)) अणु
		err = f2fs_start_ckpt_thपढ़ो(sbi);
		अगर (err) अणु
			f2fs_err(sbi,
			    "Failed to start F2FS issue_checkpoint_thread (%d)",
			    err);
			जाओ stop_ckpt_thपढ़ो;
		पूर्ण
	पूर्ण

	/* setup f2fs पूर्णांकernal modules */
	err = f2fs_build_segment_manager(sbi);
	अगर (err) अणु
		f2fs_err(sbi, "Failed to initialize F2FS segment manager (%d)",
			 err);
		जाओ मुक्त_sm;
	पूर्ण
	err = f2fs_build_node_manager(sbi);
	अगर (err) अणु
		f2fs_err(sbi, "Failed to initialize F2FS node manager (%d)",
			 err);
		जाओ मुक्त_nm;
	पूर्ण

	/* For ग_लिखो statistics */
	sbi->sectors_written_start = f2fs_get_sectors_written(sbi);

	/* Read accumulated ग_लिखो IO statistics अगर exists */
	seg_i = CURSEG_I(sbi, CURSEG_HOT_NODE);
	अगर (__exist_node_summaries(sbi))
		sbi->kbytes_written =
			le64_to_cpu(seg_i->journal->info.kbytes_written);

	f2fs_build_gc_manager(sbi);

	err = f2fs_build_stats(sbi);
	अगर (err)
		जाओ मुक्त_nm;

	/* get an inode क्रम node space */
	sbi->node_inode = f2fs_iget(sb, F2FS_NODE_INO(sbi));
	अगर (IS_ERR(sbi->node_inode)) अणु
		f2fs_err(sbi, "Failed to read node inode");
		err = PTR_ERR(sbi->node_inode);
		जाओ मुक्त_stats;
	पूर्ण

	/* पढ़ो root inode and dentry */
	root = f2fs_iget(sb, F2FS_ROOT_INO(sbi));
	अगर (IS_ERR(root)) अणु
		f2fs_err(sbi, "Failed to read root inode");
		err = PTR_ERR(root);
		जाओ मुक्त_node_inode;
	पूर्ण
	अगर (!S_ISसूची(root->i_mode) || !root->i_blocks ||
			!root->i_size || !root->i_nlink) अणु
		iput(root);
		err = -EINVAL;
		जाओ मुक्त_node_inode;
	पूर्ण

	sb->s_root = d_make_root(root); /* allocate root dentry */
	अगर (!sb->s_root) अणु
		err = -ENOMEM;
		जाओ मुक्त_node_inode;
	पूर्ण

	err = f2fs_रेजिस्टर_sysfs(sbi);
	अगर (err)
		जाओ मुक्त_root_inode;

#अगर_घोषित CONFIG_QUOTA
	/* Enable quota usage during mount */
	अगर (f2fs_sb_has_quota_ino(sbi) && !f2fs_पढ़ोonly(sb)) अणु
		err = f2fs_enable_quotas(sb);
		अगर (err)
			f2fs_err(sbi, "Cannot turn on quotas: error %d", err);
	पूर्ण
#पूर्ण_अगर
	/* अगर there are any orphan inodes, मुक्त them */
	err = f2fs_recover_orphan_inodes(sbi);
	अगर (err)
		जाओ मुक्त_meta;

	अगर (unlikely(is_set_ckpt_flags(sbi, CP_DISABLED_FLAG)))
		जाओ reset_checkpoपूर्णांक;

	/* recover fsynced data */
	अगर (!test_opt(sbi, DISABLE_ROLL_FORWARD) &&
			!test_opt(sbi, NORECOVERY)) अणु
		/*
		 * mount should be failed, when device has पढ़ोonly mode, and
		 * previous checkpoपूर्णांक was not करोne by clean प्रणाली shutकरोwn.
		 */
		अगर (f2fs_hw_is_पढ़ोonly(sbi)) अणु
			अगर (!is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG)) अणु
				err = f2fs_recover_fsync_data(sbi, true);
				अगर (err > 0) अणु
					err = -EROFS;
					f2fs_err(sbi, "Need to recover fsync data, but "
						"write access unavailable, please try "
						"mount w/ disable_roll_forward or norecovery");
				पूर्ण
				अगर (err < 0)
					जाओ मुक्त_meta;
			पूर्ण
			f2fs_info(sbi, "write access unavailable, skipping recovery");
			जाओ reset_checkpoपूर्णांक;
		पूर्ण

		अगर (need_fsck)
			set_sbi_flag(sbi, SBI_NEED_FSCK);

		अगर (skip_recovery)
			जाओ reset_checkpoपूर्णांक;

		err = f2fs_recover_fsync_data(sbi, false);
		अगर (err < 0) अणु
			अगर (err != -ENOMEM)
				skip_recovery = true;
			need_fsck = true;
			f2fs_err(sbi, "Cannot recover all fsync data errno=%d",
				 err);
			जाओ मुक्त_meta;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = f2fs_recover_fsync_data(sbi, true);

		अगर (!f2fs_पढ़ोonly(sb) && err > 0) अणु
			err = -EINVAL;
			f2fs_err(sbi, "Need to recover fsync data");
			जाओ मुक्त_meta;
		पूर्ण
	पूर्ण

	/*
	 * If the f2fs is not पढ़ोonly and fsync data recovery succeeds,
	 * check zoned block devices' ग_लिखो poपूर्णांकer consistency.
	 */
	अगर (!err && !f2fs_पढ़ोonly(sb) && f2fs_sb_has_blkzoned(sbi)) अणु
		err = f2fs_check_ग_लिखो_poपूर्णांकer(sbi);
		अगर (err)
			जाओ मुक्त_meta;
	पूर्ण

reset_checkpoपूर्णांक:
	f2fs_init_inmem_curseg(sbi);

	/* f2fs_recover_fsync_data() cleared this alपढ़ोy */
	clear_sbi_flag(sbi, SBI_POR_DOING);

	अगर (test_opt(sbi, DISABLE_CHECKPOINT)) अणु
		err = f2fs_disable_checkpoपूर्णांक(sbi);
		अगर (err)
			जाओ sync_मुक्त_meta;
	पूर्ण अन्यथा अगर (is_set_ckpt_flags(sbi, CP_DISABLED_FLAG)) अणु
		f2fs_enable_checkpoपूर्णांक(sbi);
	पूर्ण

	/*
	 * If fileप्रणाली is not mounted as पढ़ो-only then
	 * करो start the gc_thपढ़ो.
	 */
	अगर ((F2FS_OPTION(sbi).bggc_mode != BGGC_MODE_OFF ||
		test_opt(sbi, GC_MERGE)) && !f2fs_पढ़ोonly(sb)) अणु
		/* After POR, we can run background GC thपढ़ो.*/
		err = f2fs_start_gc_thपढ़ो(sbi);
		अगर (err)
			जाओ sync_मुक्त_meta;
	पूर्ण
	kvमुक्त(options);

	/* recover broken superblock */
	अगर (recovery) अणु
		err = f2fs_commit_super(sbi, true);
		f2fs_info(sbi, "Try to recover %dth superblock, ret: %d",
			  sbi->valid_super_block ? 1 : 2, err);
	पूर्ण

	f2fs_join_shrinker(sbi);

	f2fs_tuning_parameters(sbi);

	f2fs_notice(sbi, "Mounted with checkpoint version = %llx",
		    cur_cp_version(F2FS_CKPT(sbi)));
	f2fs_update_समय(sbi, CP_TIME);
	f2fs_update_समय(sbi, REQ_TIME);
	clear_sbi_flag(sbi, SBI_CP_DISABLED_QUICK);
	वापस 0;

sync_मुक्त_meta:
	/* safe to flush all the data */
	sync_fileप्रणाली(sbi->sb);
	retry_cnt = 0;

मुक्त_meta:
#अगर_घोषित CONFIG_QUOTA
	f2fs_truncate_quota_inode_pages(sb);
	अगर (f2fs_sb_has_quota_ino(sbi) && !f2fs_पढ़ोonly(sb))
		f2fs_quota_off_umount(sbi->sb);
#पूर्ण_अगर
	/*
	 * Some dirty meta pages can be produced by f2fs_recover_orphan_inodes()
	 * failed by EIO. Then, iput(node_inode) can trigger balance_fs_bg()
	 * followed by f2fs_ग_लिखो_checkpoपूर्णांक() through f2fs_ग_लिखो_node_pages(), which
	 * falls पूर्णांकo an infinite loop in f2fs_sync_meta_pages().
	 */
	truncate_inode_pages_final(META_MAPPING(sbi));
	/* evict some inodes being cached by GC */
	evict_inodes(sb);
	f2fs_unरेजिस्टर_sysfs(sbi);
मुक्त_root_inode:
	dput(sb->s_root);
	sb->s_root = शून्य;
मुक्त_node_inode:
	f2fs_release_ino_entry(sbi, true);
	truncate_inode_pages_final(NODE_MAPPING(sbi));
	iput(sbi->node_inode);
	sbi->node_inode = शून्य;
मुक्त_stats:
	f2fs_destroy_stats(sbi);
मुक्त_nm:
	f2fs_destroy_node_manager(sbi);
मुक्त_sm:
	f2fs_destroy_segment_manager(sbi);
	f2fs_destroy_post_पढ़ो_wq(sbi);
stop_ckpt_thपढ़ो:
	f2fs_stop_ckpt_thपढ़ो(sbi);
मुक्त_devices:
	destroy_device_list(sbi);
	kvमुक्त(sbi->ckpt);
मुक्त_meta_inode:
	make_bad_inode(sbi->meta_inode);
	iput(sbi->meta_inode);
	sbi->meta_inode = शून्य;
मुक्त_page_array_cache:
	f2fs_destroy_page_array_cache(sbi);
मुक्त_xattr_cache:
	f2fs_destroy_xattr_caches(sbi);
मुक्त_io_dummy:
	mempool_destroy(sbi->ग_लिखो_io_dummy);
मुक्त_percpu:
	destroy_percpu_info(sbi);
मुक्त_bio_info:
	क्रम (i = 0; i < NR_PAGE_TYPE; i++)
		kvमुक्त(sbi->ग_लिखो_io[i]);

#अगर_घोषित CONFIG_UNICODE
	utf8_unload(sb->s_encoding);
	sb->s_encoding = शून्य;
#पूर्ण_अगर
मुक्त_options:
#अगर_घोषित CONFIG_QUOTA
	क्रम (i = 0; i < MAXQUOTAS; i++)
		kमुक्त(F2FS_OPTION(sbi).s_qf_names[i]);
#पूर्ण_अगर
	fscrypt_मुक्त_dummy_policy(&F2FS_OPTION(sbi).dummy_enc_policy);
	kvमुक्त(options);
मुक्त_sb_buf:
	kमुक्त(raw_super);
मुक्त_sbi:
	अगर (sbi->s_chksum_driver)
		crypto_मुक्त_shash(sbi->s_chksum_driver);
	kमुक्त(sbi);

	/* give only one another chance */
	अगर (retry_cnt > 0 && skip_recovery) अणु
		retry_cnt--;
		shrink_dcache_sb(sb);
		जाओ try_onemore;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा dentry *f2fs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
			स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, f2fs_fill_super);
पूर्ण

अटल व्योम समाप्त_f2fs_super(काष्ठा super_block *sb)
अणु
	अगर (sb->s_root) अणु
		काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);

		set_sbi_flag(sbi, SBI_IS_CLOSE);
		f2fs_stop_gc_thपढ़ो(sbi);
		f2fs_stop_discard_thपढ़ो(sbi);

		अगर (is_sbi_flag_set(sbi, SBI_IS_सूचीTY) ||
				!is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG)) अणु
			काष्ठा cp_control cpc = अणु
				.reason = CP_UMOUNT,
			पूर्ण;
			f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
		पूर्ण

		अगर (is_sbi_flag_set(sbi, SBI_IS_RECOVERED) && f2fs_पढ़ोonly(sb))
			sb->s_flags &= ~SB_RDONLY;
	पूर्ण
	समाप्त_block_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type f2fs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "f2fs",
	.mount		= f2fs_mount,
	.समाप्त_sb	= समाप्त_f2fs_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("f2fs");

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	f2fs_inode_cachep = kmem_cache_create("f2fs_inode_cache",
			माप(काष्ठा f2fs_inode_info), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_ACCOUNT, शून्य);
	अगर (!f2fs_inode_cachep)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(f2fs_inode_cachep);
पूर्ण

अटल पूर्णांक __init init_f2fs_fs(व्योम)
अणु
	पूर्णांक err;

	अगर (PAGE_SIZE != F2FS_BLKSIZE) अणु
		prपूर्णांकk("F2FS not supported on PAGE_SIZE(%lu) != %d\n",
				PAGE_SIZE, F2FS_BLKSIZE);
		वापस -EINVAL;
	पूर्ण

	err = init_inodecache();
	अगर (err)
		जाओ fail;
	err = f2fs_create_node_manager_caches();
	अगर (err)
		जाओ मुक्त_inodecache;
	err = f2fs_create_segment_manager_caches();
	अगर (err)
		जाओ मुक्त_node_manager_caches;
	err = f2fs_create_checkpoपूर्णांक_caches();
	अगर (err)
		जाओ मुक्त_segment_manager_caches;
	err = f2fs_create_extent_cache();
	अगर (err)
		जाओ मुक्त_checkpoपूर्णांक_caches;
	err = f2fs_create_garbage_collection_cache();
	अगर (err)
		जाओ मुक्त_extent_cache;
	err = f2fs_init_sysfs();
	अगर (err)
		जाओ मुक्त_garbage_collection_cache;
	err = रेजिस्टर_shrinker(&f2fs_shrinker_info);
	अगर (err)
		जाओ मुक्त_sysfs;
	err = रेजिस्टर_fileप्रणाली(&f2fs_fs_type);
	अगर (err)
		जाओ मुक्त_shrinker;
	f2fs_create_root_stats();
	err = f2fs_init_post_पढ़ो_processing();
	अगर (err)
		जाओ मुक्त_root_stats;
	err = f2fs_init_bio_entry_cache();
	अगर (err)
		जाओ मुक्त_post_पढ़ो;
	err = f2fs_init_bioset();
	अगर (err)
		जाओ मुक्त_bio_enrty_cache;
	err = f2fs_init_compress_mempool();
	अगर (err)
		जाओ मुक्त_bioset;
	err = f2fs_init_compress_cache();
	अगर (err)
		जाओ मुक्त_compress_mempool;
	वापस 0;
मुक्त_compress_mempool:
	f2fs_destroy_compress_mempool();
मुक्त_bioset:
	f2fs_destroy_bioset();
मुक्त_bio_enrty_cache:
	f2fs_destroy_bio_entry_cache();
मुक्त_post_पढ़ो:
	f2fs_destroy_post_पढ़ो_processing();
मुक्त_root_stats:
	f2fs_destroy_root_stats();
	unरेजिस्टर_fileप्रणाली(&f2fs_fs_type);
मुक्त_shrinker:
	unरेजिस्टर_shrinker(&f2fs_shrinker_info);
मुक्त_sysfs:
	f2fs_निकास_sysfs();
मुक्त_garbage_collection_cache:
	f2fs_destroy_garbage_collection_cache();
मुक्त_extent_cache:
	f2fs_destroy_extent_cache();
मुक्त_checkpoपूर्णांक_caches:
	f2fs_destroy_checkpoपूर्णांक_caches();
मुक्त_segment_manager_caches:
	f2fs_destroy_segment_manager_caches();
मुक्त_node_manager_caches:
	f2fs_destroy_node_manager_caches();
मुक्त_inodecache:
	destroy_inodecache();
fail:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_f2fs_fs(व्योम)
अणु
	f2fs_destroy_compress_cache();
	f2fs_destroy_compress_mempool();
	f2fs_destroy_bioset();
	f2fs_destroy_bio_entry_cache();
	f2fs_destroy_post_पढ़ो_processing();
	f2fs_destroy_root_stats();
	unरेजिस्टर_fileप्रणाली(&f2fs_fs_type);
	unरेजिस्टर_shrinker(&f2fs_shrinker_info);
	f2fs_निकास_sysfs();
	f2fs_destroy_garbage_collection_cache();
	f2fs_destroy_extent_cache();
	f2fs_destroy_checkpoपूर्णांक_caches();
	f2fs_destroy_segment_manager_caches();
	f2fs_destroy_node_manager_caches();
	destroy_inodecache();
पूर्ण

module_init(init_f2fs_fs)
module_निकास(निकास_f2fs_fs)

MODULE_AUTHOR("Samsung Electronics's Praesto Team");
MODULE_DESCRIPTION("Flash Friendly File System");
MODULE_LICENSE("GPL");

