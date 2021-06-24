<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * super.c - NTFS kernel super block handling. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2012 Anton Altaparmakov and Tuxera Inc.
 * Copyright (c) 2001,2002 Riअक्षरd Russon
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>	/* For bdev_logical_block_size(). */
#समावेश <linux/backing-dev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "sysctl.h"
#समावेश "logfile.h"
#समावेश "quota.h"
#समावेश "usnjrnl.h"
#समावेश "dir.h"
#समावेश "debug.h"
#समावेश "index.h"
#समावेश "inode.h"
#समावेश "aops.h"
#समावेश "layout.h"
#समावेश "malloc.h"
#समावेश "ntfs.h"

/* Number of mounted fileप्रणालीs which have compression enabled. */
अटल अचिन्हित दीर्घ ntfs_nr_compression_users;

/* A global शेष upहाल table and a corresponding reference count. */
अटल ntfsअक्षर *शेष_upहाल;
अटल अचिन्हित दीर्घ ntfs_nr_upहाल_users;

/* Error स्थिरants/strings used in inode.c::ntfs_show_options(). */
प्रकार क्रमागत अणु
	/* One of these must be present, शेष is ON_ERRORS_CONTINUE. */
	ON_ERRORS_PANIC			= 0x01,
	ON_ERRORS_REMOUNT_RO		= 0x02,
	ON_ERRORS_CONTINUE		= 0x04,
	/* Optional, can be combined with any of the above. */
	ON_ERRORS_RECOVER		= 0x10,
पूर्ण ON_ERRORS_ACTIONS;

स्थिर option_t on_errors_arr[] = अणु
	अणु ON_ERRORS_PANIC,	"panic" पूर्ण,
	अणु ON_ERRORS_REMOUNT_RO,	"remount-ro", पूर्ण,
	अणु ON_ERRORS_CONTINUE,	"continue", पूर्ण,
	अणु ON_ERRORS_RECOVER,	"recover" पूर्ण,
	अणु 0,			शून्य पूर्ण
पूर्ण;

/**
 * simple_getbool -
 *
 * Copied from old ntfs driver (which copied from vfat driver).
 */
अटल पूर्णांक simple_getbool(अक्षर *s, bool *setval)
अणु
	अगर (s) अणु
		अगर (!म_भेद(s, "1") || !म_भेद(s, "yes") || !म_भेद(s, "true"))
			*setval = true;
		अन्यथा अगर (!म_भेद(s, "0") || !म_भेद(s, "no") ||
							!म_भेद(s, "false"))
			*setval = false;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा
		*setval = true;
	वापस 1;
पूर्ण

/**
 * parse_options - parse the (re)mount options
 * @vol:	ntfs volume
 * @opt:	string containing the (re)mount options
 *
 * Parse the recognized options in @opt क्रम the ntfs volume described by @vol.
 */
अटल bool parse_options(ntfs_volume *vol, अक्षर *opt)
अणु
	अक्षर *p, *v, *ov;
	अटल अक्षर *utf8 = "utf8";
	पूर्णांक errors = 0, sloppy = 0;
	kuid_t uid = INVALID_UID;
	kgid_t gid = INVALID_GID;
	umode_t fmask = (umode_t)-1, dmask = (umode_t)-1;
	पूर्णांक mft_zone_multiplier = -1, on_errors = -1;
	पूर्णांक show_sys_files = -1, हाल_sensitive = -1, disable_sparse = -1;
	काष्ठा nls_table *nls_map = शून्य, *old_nls;

	/* I am lazy... (-8 */
#घोषणा NTFS_GETOPT_WITH_DEFAULT(option, variable, शेष_value)	\
	अगर (!म_भेद(p, option)) अणु					\
		अगर (!v || !*v)						\
			variable = शेष_value;			\
		अन्यथा अणु							\
			variable = simple_म_से_अदीर्घ(ov = v, &v, 0);	\
			अगर (*v)						\
				जाओ needs_val;				\
		पूर्ण							\
	पूर्ण
#घोषणा NTFS_GETOPT(option, variable)					\
	अगर (!म_भेद(p, option)) अणु					\
		अगर (!v || !*v)						\
			जाओ needs_arg;					\
		variable = simple_म_से_अदीर्घ(ov = v, &v, 0);		\
		अगर (*v)							\
			जाओ needs_val;					\
	पूर्ण
#घोषणा NTFS_GETOPT_UID(option, variable)				\
	अगर (!म_भेद(p, option)) अणु					\
		uid_t uid_value;					\
		अगर (!v || !*v)						\
			जाओ needs_arg;					\
		uid_value = simple_म_से_अदीर्घ(ov = v, &v, 0);		\
		अगर (*v)							\
			जाओ needs_val;					\
		variable = make_kuid(current_user_ns(), uid_value);	\
		अगर (!uid_valid(variable))				\
			जाओ needs_val;					\
	पूर्ण
#घोषणा NTFS_GETOPT_GID(option, variable)				\
	अगर (!म_भेद(p, option)) अणु					\
		gid_t gid_value;					\
		अगर (!v || !*v)						\
			जाओ needs_arg;					\
		gid_value = simple_म_से_अदीर्घ(ov = v, &v, 0);		\
		अगर (*v)							\
			जाओ needs_val;					\
		variable = make_kgid(current_user_ns(), gid_value);	\
		अगर (!gid_valid(variable))				\
			जाओ needs_val;					\
	पूर्ण
#घोषणा NTFS_GETOPT_OCTAL(option, variable)				\
	अगर (!म_भेद(p, option)) अणु					\
		अगर (!v || !*v)						\
			जाओ needs_arg;					\
		variable = simple_म_से_अदीर्घ(ov = v, &v, 8);		\
		अगर (*v)							\
			जाओ needs_val;					\
	पूर्ण
#घोषणा NTFS_GETOPT_BOOL(option, variable)				\
	अगर (!म_भेद(p, option)) अणु					\
		bool val;						\
		अगर (!simple_getbool(v, &val))				\
			जाओ needs_bool;				\
		variable = val;						\
	पूर्ण
#घोषणा NTFS_GETOPT_OPTIONS_ARRAY(option, variable, opt_array)		\
	अगर (!म_भेद(p, option)) अणु					\
		पूर्णांक _i;							\
		अगर (!v || !*v)						\
			जाओ needs_arg;					\
		ov = v;							\
		अगर (variable == -1)					\
			variable = 0;					\
		क्रम (_i = 0; opt_array[_i].str && *opt_array[_i].str; _i++) \
			अगर (!म_भेद(opt_array[_i].str, v)) अणु		\
				variable |= opt_array[_i].val;		\
				अवरोध;					\
			पूर्ण						\
		अगर (!opt_array[_i].str || !*opt_array[_i].str)		\
			जाओ needs_val;					\
	पूर्ण
	अगर (!opt || !*opt)
		जाओ no_mount_options;
	ntfs_debug("Entering with mount options string: %s", opt);
	जबतक ((p = strsep(&opt, ","))) अणु
		अगर ((v = म_अक्षर(p, '=')))
			*v++ = 0;
		NTFS_GETOPT_UID("uid", uid)
		अन्यथा NTFS_GETOPT_GID("gid", gid)
		अन्यथा NTFS_GETOPT_OCTAL("umask", fmask = dmask)
		अन्यथा NTFS_GETOPT_OCTAL("fmask", fmask)
		अन्यथा NTFS_GETOPT_OCTAL("dmask", dmask)
		अन्यथा NTFS_GETOPT("mft_zone_multiplier", mft_zone_multiplier)
		अन्यथा NTFS_GETOPT_WITH_DEFAULT("sloppy", sloppy, true)
		अन्यथा NTFS_GETOPT_BOOL("show_sys_files", show_sys_files)
		अन्यथा NTFS_GETOPT_BOOL("case_sensitive", हाल_sensitive)
		अन्यथा NTFS_GETOPT_BOOL("disable_sparse", disable_sparse)
		अन्यथा NTFS_GETOPT_OPTIONS_ARRAY("errors", on_errors,
				on_errors_arr)
		अन्यथा अगर (!म_भेद(p, "posix") || !म_भेद(p, "show_inodes"))
			ntfs_warning(vol->sb, "Ignoring obsolete option %s.",
					p);
		अन्यथा अगर (!म_भेद(p, "nls") || !म_भेद(p, "iocharset")) अणु
			अगर (!म_भेद(p, "iocharset"))
				ntfs_warning(vol->sb, "Option iocharset is "
						"deprecated. Please use "
						"option nls=<charsetname> in "
						"the future.");
			अगर (!v || !*v)
				जाओ needs_arg;
use_utf8:
			old_nls = nls_map;
			nls_map = load_nls(v);
			अगर (!nls_map) अणु
				अगर (!old_nls) अणु
					ntfs_error(vol->sb, "NLS character set "
							"%s not found.", v);
					वापस false;
				पूर्ण
				ntfs_error(vol->sb, "NLS character set %s not "
						"found. Using previous one %s.",
						v, old_nls->अक्षरset);
				nls_map = old_nls;
			पूर्ण अन्यथा /* nls_map */ अणु
				unload_nls(old_nls);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(p, "utf8")) अणु
			bool val = false;
			ntfs_warning(vol->sb, "Option utf8 is no longer "
				   "supported, using option nls=utf8. Please "
				   "use option nls=utf8 in the future and "
				   "make sure utf8 is compiled either as a "
				   "module or into the kernel.");
			अगर (!v || !*v)
				val = true;
			अन्यथा अगर (!simple_getbool(v, &val))
				जाओ needs_bool;
			अगर (val) अणु
				v = utf8;
				जाओ use_utf8;
			पूर्ण
		पूर्ण अन्यथा अणु
			ntfs_error(vol->sb, "Unrecognized mount option %s.", p);
			अगर (errors < पूर्णांक_उच्च)
				errors++;
		पूर्ण
#अघोषित NTFS_GETOPT_OPTIONS_ARRAY
#अघोषित NTFS_GETOPT_BOOL
#अघोषित NTFS_GETOPT
#अघोषित NTFS_GETOPT_WITH_DEFAULT
	पूर्ण
no_mount_options:
	अगर (errors && !sloppy)
		वापस false;
	अगर (sloppy)
		ntfs_warning(vol->sb, "Sloppy option given. Ignoring "
				"unrecognized mount option(s) and continuing.");
	/* Keep this first! */
	अगर (on_errors != -1) अणु
		अगर (!on_errors) अणु
			ntfs_error(vol->sb, "Invalid errors option argument "
					"or bug in options parser.");
			वापस false;
		पूर्ण
	पूर्ण
	अगर (nls_map) अणु
		अगर (vol->nls_map && vol->nls_map != nls_map) अणु
			ntfs_error(vol->sb, "Cannot change NLS character set "
					"on remount.");
			वापस false;
		पूर्ण /* अन्यथा (!vol->nls_map) */
		ntfs_debug("Using NLS character set %s.", nls_map->अक्षरset);
		vol->nls_map = nls_map;
	पूर्ण अन्यथा /* (!nls_map) */ अणु
		अगर (!vol->nls_map) अणु
			vol->nls_map = load_nls_शेष();
			अगर (!vol->nls_map) अणु
				ntfs_error(vol->sb, "Failed to load default "
						"NLS character set.");
				वापस false;
			पूर्ण
			ntfs_debug("Using default NLS character set (%s).",
					vol->nls_map->अक्षरset);
		पूर्ण
	पूर्ण
	अगर (mft_zone_multiplier != -1) अणु
		अगर (vol->mft_zone_multiplier && vol->mft_zone_multiplier !=
				mft_zone_multiplier) अणु
			ntfs_error(vol->sb, "Cannot change mft_zone_multiplier "
					"on remount.");
			वापस false;
		पूर्ण
		अगर (mft_zone_multiplier < 1 || mft_zone_multiplier > 4) अणु
			ntfs_error(vol->sb, "Invalid mft_zone_multiplier. "
					"Using default value, i.e. 1.");
			mft_zone_multiplier = 1;
		पूर्ण
		vol->mft_zone_multiplier = mft_zone_multiplier;
	पूर्ण
	अगर (!vol->mft_zone_multiplier)
		vol->mft_zone_multiplier = 1;
	अगर (on_errors != -1)
		vol->on_errors = on_errors;
	अगर (!vol->on_errors || vol->on_errors == ON_ERRORS_RECOVER)
		vol->on_errors |= ON_ERRORS_CONTINUE;
	अगर (uid_valid(uid))
		vol->uid = uid;
	अगर (gid_valid(gid))
		vol->gid = gid;
	अगर (fmask != (umode_t)-1)
		vol->fmask = fmask;
	अगर (dmask != (umode_t)-1)
		vol->dmask = dmask;
	अगर (show_sys_files != -1) अणु
		अगर (show_sys_files)
			NVolSetShowSystemFiles(vol);
		अन्यथा
			NVolClearShowSystemFiles(vol);
	पूर्ण
	अगर (हाल_sensitive != -1) अणु
		अगर (हाल_sensitive)
			NVolSetCaseSensitive(vol);
		अन्यथा
			NVolClearCaseSensitive(vol);
	पूर्ण
	अगर (disable_sparse != -1) अणु
		अगर (disable_sparse)
			NVolClearSparseEnabled(vol);
		अन्यथा अणु
			अगर (!NVolSparseEnabled(vol) &&
					vol->major_ver && vol->major_ver < 3)
				ntfs_warning(vol->sb, "Not enabling sparse "
						"support due to NTFS volume "
						"version %i.%i (need at least "
						"version 3.0).", vol->major_ver,
						vol->minor_ver);
			अन्यथा
				NVolSetSparseEnabled(vol);
		पूर्ण
	पूर्ण
	वापस true;
needs_arg:
	ntfs_error(vol->sb, "The %s option requires an argument.", p);
	वापस false;
needs_bool:
	ntfs_error(vol->sb, "The %s option requires a boolean argument.", p);
	वापस false;
needs_val:
	ntfs_error(vol->sb, "Invalid %s option argument: %s", p, ov);
	वापस false;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * ntfs_ग_लिखो_volume_flags - ग_लिखो new flags to the volume inक्रमmation flags
 * @vol:	ntfs volume on which to modअगरy the flags
 * @flags:	new flags value क्रम the volume inक्रमmation flags
 *
 * Internal function.  You probably want to use ntfs_अणुset,clearपूर्ण_volume_flags()
 * instead (see below).
 *
 * Replace the volume inक्रमmation flags on the volume @vol with the value
 * supplied in @flags.  Note, this overग_लिखोs the volume inक्रमmation flags, so
 * make sure to combine the flags you want to modअगरy with the old flags and use
 * the result when calling ntfs_ग_लिखो_volume_flags().
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_ग_लिखो_volume_flags(ntfs_volume *vol, स्थिर VOLUME_FLAGS flags)
अणु
	ntfs_inode *ni = NTFS_I(vol->vol_ino);
	MFT_RECORD *m;
	VOLUME_INFORMATION *vi;
	ntfs_attr_search_ctx *ctx;
	पूर्णांक err;

	ntfs_debug("Entering, old flags = 0x%x, new flags = 0x%x.",
			le16_to_cpu(vol->vol_flags), le16_to_cpu(flags));
	अगर (vol->vol_flags == flags)
		जाओ करोne;
	BUG_ON(!ni);
	m = map_mft_record(ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ put_unm_err_out;
	पूर्ण
	err = ntfs_attr_lookup(AT_VOLUME_INFORMATION, शून्य, 0, 0, 0, शून्य, 0,
			ctx);
	अगर (err)
		जाओ put_unm_err_out;
	vi = (VOLUME_INFORMATION*)((u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	vol->vol_flags = vi->flags = flags;
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ni);
करोne:
	ntfs_debug("Done.");
	वापस 0;
put_unm_err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ni);
err_out:
	ntfs_error(vol->sb, "Failed with error code %i.", -err);
	वापस err;
पूर्ण

/**
 * ntfs_set_volume_flags - set bits in the volume inक्रमmation flags
 * @vol:	ntfs volume on which to modअगरy the flags
 * @flags:	flags to set on the volume
 *
 * Set the bits in @flags in the volume inक्रमmation flags on the volume @vol.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_set_volume_flags(ntfs_volume *vol, VOLUME_FLAGS flags)
अणु
	flags &= VOLUME_FLAGS_MASK;
	वापस ntfs_ग_लिखो_volume_flags(vol, vol->vol_flags | flags);
पूर्ण

/**
 * ntfs_clear_volume_flags - clear bits in the volume inक्रमmation flags
 * @vol:	ntfs volume on which to modअगरy the flags
 * @flags:	flags to clear on the volume
 *
 * Clear the bits in @flags in the volume inक्रमmation flags on the volume @vol.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_clear_volume_flags(ntfs_volume *vol, VOLUME_FLAGS flags)
अणु
	flags &= VOLUME_FLAGS_MASK;
	flags = vol->vol_flags & cpu_to_le16(~le16_to_cpu(flags));
	वापस ntfs_ग_लिखो_volume_flags(vol, flags);
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

/**
 * ntfs_remount - change the mount options of a mounted ntfs fileप्रणाली
 * @sb:		superblock of mounted ntfs fileप्रणाली
 * @flags:	remount flags
 * @opt:	remount options string
 *
 * Change the mount options of an alपढ़ोy mounted ntfs fileप्रणाली.
 *
 * NOTE:  The VFS sets the @sb->s_flags remount flags to @flags after
 * ntfs_remount() वापसs successfully (i.e. वापसs 0).  Otherwise,
 * @sb->s_flags are not changed.
 */
अटल पूर्णांक ntfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *opt)
अणु
	ntfs_volume *vol = NTFS_SB(sb);

	ntfs_debug("Entering with remount options string: %s", opt);

	sync_fileप्रणाली(sb);

#अगर_अघोषित NTFS_RW
	/* For पढ़ो-only compiled driver, enक्रमce पढ़ो-only flag. */
	*flags |= SB_RDONLY;
#अन्यथा /* NTFS_RW */
	/*
	 * For the पढ़ो-ग_लिखो compiled driver, अगर we are remounting पढ़ो-ग_लिखो,
	 * make sure there are no volume errors and that no unsupported volume
	 * flags are set.  Also, empty the logfile journal as it would become
	 * stale as soon as something is written to the volume and mark the
	 * volume dirty so that chkdsk is run अगर the volume is not umounted
	 * cleanly.  Finally, mark the quotas out of date so Winकरोws rescans
	 * the volume on boot and updates them.
	 *
	 * When remounting पढ़ो-only, mark the volume clean अगर no volume errors
	 * have occurred.
	 */
	अगर (sb_rकरोnly(sb) && !(*flags & SB_RDONLY)) अणु
		अटल स्थिर अक्षर *es = ".  Cannot remount read-write.";

		/* Remounting पढ़ो-ग_लिखो. */
		अगर (NVolErrors(vol)) अणु
			ntfs_error(sb, "Volume has errors and is read-only%s",
					es);
			वापस -EROFS;
		पूर्ण
		अगर (vol->vol_flags & VOLUME_IS_सूचीTY) अणु
			ntfs_error(sb, "Volume is dirty and read-only%s", es);
			वापस -EROFS;
		पूर्ण
		अगर (vol->vol_flags & VOLUME_MODIFIED_BY_CHKDSK) अणु
			ntfs_error(sb, "Volume has been modified by chkdsk "
					"and is read-only%s", es);
			वापस -EROFS;
		पूर्ण
		अगर (vol->vol_flags & VOLUME_MUST_MOUNT_RO_MASK) अणु
			ntfs_error(sb, "Volume has unsupported flags set "
					"(0x%x) and is read-only%s",
					(अचिन्हित)le16_to_cpu(vol->vol_flags),
					es);
			वापस -EROFS;
		पूर्ण
		अगर (ntfs_set_volume_flags(vol, VOLUME_IS_सूचीTY)) अणु
			ntfs_error(sb, "Failed to set dirty bit in volume "
					"information flags%s", es);
			वापस -EROFS;
		पूर्ण
#अगर 0
		// TODO: Enable this code once we start modअगरying anything that
		//	 is dअगरferent between NTFS 1.2 and 3.x...
		/* Set NT4 compatibility flag on newer NTFS version volumes. */
		अगर ((vol->major_ver > 1)) अणु
			अगर (ntfs_set_volume_flags(vol, VOLUME_MOUNTED_ON_NT4)) अणु
				ntfs_error(sb, "Failed to set NT4 "
						"compatibility flag%s", es);
				NVolSetErrors(vol);
				वापस -EROFS;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अगर (!ntfs_empty_logfile(vol->logfile_ino)) अणु
			ntfs_error(sb, "Failed to empty journal $LogFile%s",
					es);
			NVolSetErrors(vol);
			वापस -EROFS;
		पूर्ण
		अगर (!ntfs_mark_quotas_out_of_date(vol)) अणु
			ntfs_error(sb, "Failed to mark quotas out of date%s",
					es);
			NVolSetErrors(vol);
			वापस -EROFS;
		पूर्ण
		अगर (!ntfs_stamp_usnjrnl(vol)) अणु
			ntfs_error(sb, "Failed to stamp transaction log "
					"($UsnJrnl)%s", es);
			NVolSetErrors(vol);
			वापस -EROFS;
		पूर्ण
	पूर्ण अन्यथा अगर (!sb_rकरोnly(sb) && (*flags & SB_RDONLY)) अणु
		/* Remounting पढ़ो-only. */
		अगर (!NVolErrors(vol)) अणु
			अगर (ntfs_clear_volume_flags(vol, VOLUME_IS_सूचीTY))
				ntfs_warning(sb, "Failed to clear dirty bit "
						"in volume information "
						"flags.  Run chkdsk.");
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */

	// TODO: Deal with *flags.

	अगर (!parse_options(vol, opt))
		वापस -EINVAL;

	ntfs_debug("Done.");
	वापस 0;
पूर्ण

/**
 * is_boot_sector_ntfs - check whether a boot sector is a valid NTFS boot sector
 * @sb:		Super block of the device to which @b beदीर्घs.
 * @b:		Boot sector of device @sb to check.
 * @silent:	If 'true', all output will be silenced.
 *
 * is_boot_sector_ntfs() checks whether the boot sector @b is a valid NTFS boot
 * sector. Returns 'true' if it is valid and 'false' अगर not.
 *
 * @sb is only needed क्रम warning/error output, i.e. it can be शून्य when silent
 * is 'true'.
 */
अटल bool is_boot_sector_ntfs(स्थिर काष्ठा super_block *sb,
		स्थिर NTFS_BOOT_SECTOR *b, स्थिर bool silent)
अणु
	/*
	 * Check that checksum == sum of u32 values from b to the checksum
	 * field.  If checksum is zero, no checking is करोne.  We will work when
	 * the checksum test fails, since some utilities update the boot sector
	 * ignoring the checksum which leaves the checksum out-of-date.  We
	 * report a warning अगर this is the हाल.
	 */
	अगर ((व्योम*)b < (व्योम*)&b->checksum && b->checksum && !silent) अणु
		le32 *u;
		u32 i;

		क्रम (i = 0, u = (le32*)b; u < (le32*)(&b->checksum); ++u)
			i += le32_to_cpup(u);
		अगर (le32_to_cpu(b->checksum) != i)
			ntfs_warning(sb, "Invalid boot sector checksum.");
	पूर्ण
	/* Check OEMidentअगरier is "NTFS    " */
	अगर (b->oem_id != magicNTFS)
		जाओ not_ntfs;
	/* Check bytes per sector value is between 256 and 4096. */
	अगर (le16_to_cpu(b->bpb.bytes_per_sector) < 0x100 ||
			le16_to_cpu(b->bpb.bytes_per_sector) > 0x1000)
		जाओ not_ntfs;
	/* Check sectors per cluster value is valid. */
	चयन (b->bpb.sectors_per_cluster) अणु
	हाल 1: हाल 2: हाल 4: हाल 8: हाल 16: हाल 32: हाल 64: हाल 128:
		अवरोध;
	शेष:
		जाओ not_ntfs;
	पूर्ण
	/* Check the cluster size is not above the maximum (64kiB). */
	अगर ((u32)le16_to_cpu(b->bpb.bytes_per_sector) *
			b->bpb.sectors_per_cluster > NTFS_MAX_CLUSTER_SIZE)
		जाओ not_ntfs;
	/* Check reserved/unused fields are really zero. */
	अगर (le16_to_cpu(b->bpb.reserved_sectors) ||
			le16_to_cpu(b->bpb.root_entries) ||
			le16_to_cpu(b->bpb.sectors) ||
			le16_to_cpu(b->bpb.sectors_per_fat) ||
			le32_to_cpu(b->bpb.large_sectors) || b->bpb.fats)
		जाओ not_ntfs;
	/* Check clusters per file mft record value is valid. */
	अगर ((u8)b->clusters_per_mft_record < 0xe1 ||
			(u8)b->clusters_per_mft_record > 0xf7)
		चयन (b->clusters_per_mft_record) अणु
		हाल 1: हाल 2: हाल 4: हाल 8: हाल 16: हाल 32: हाल 64:
			अवरोध;
		शेष:
			जाओ not_ntfs;
		पूर्ण
	/* Check clusters per index block value is valid. */
	अगर ((u8)b->clusters_per_index_record < 0xe1 ||
			(u8)b->clusters_per_index_record > 0xf7)
		चयन (b->clusters_per_index_record) अणु
		हाल 1: हाल 2: हाल 4: हाल 8: हाल 16: हाल 32: हाल 64:
			अवरोध;
		शेष:
			जाओ not_ntfs;
		पूर्ण
	/*
	 * Check क्रम valid end of sector marker. We will work without it, but
	 * many BIOSes will refuse to boot from a bootsector अगर the magic is
	 * incorrect, so we emit a warning.
	 */
	अगर (!silent && b->end_of_sector_marker != cpu_to_le16(0xaa55))
		ntfs_warning(sb, "Invalid end of sector marker.");
	वापस true;
not_ntfs:
	वापस false;
पूर्ण

/**
 * पढ़ो_ntfs_boot_sector - पढ़ो the NTFS boot sector of a device
 * @sb:		super block of device to पढ़ो the boot sector from
 * @silent:	अगर true, suppress all output
 *
 * Reads the boot sector from the device and validates it. If that fails, tries
 * to पढ़ो the backup boot sector, first from the end of the device a-la NT4 and
 * later and then from the middle of the device a-la NT3.51 and beक्रमe.
 *
 * If a valid boot sector is found but it is not the primary boot sector, we
 * repair the primary boot sector silently (unless the device is पढ़ो-only or
 * the primary boot sector is not accessible).
 *
 * NOTE: To call this function, @sb must have the fields s_dev, the ntfs super
 * block (u.ntfs_sb), nr_blocks and the device flags (s_flags) initialized
 * to their respective values.
 *
 * Return the unlocked buffer head containing the boot sector or शून्य on error.
 */
अटल काष्ठा buffer_head *पढ़ो_ntfs_boot_sector(काष्ठा super_block *sb,
		स्थिर पूर्णांक silent)
अणु
	स्थिर अक्षर *पढ़ो_err_str = "Unable to read %s boot sector.";
	काष्ठा buffer_head *bh_primary, *bh_backup;
	sector_t nr_blocks = NTFS_SB(sb)->nr_blocks;

	/* Try to पढ़ो primary boot sector. */
	अगर ((bh_primary = sb_bपढ़ो(sb, 0))) अणु
		अगर (is_boot_sector_ntfs(sb, (NTFS_BOOT_SECTOR*)
				bh_primary->b_data, silent))
			वापस bh_primary;
		अगर (!silent)
			ntfs_error(sb, "Primary boot sector is invalid.");
	पूर्ण अन्यथा अगर (!silent)
		ntfs_error(sb, पढ़ो_err_str, "primary");
	अगर (!(NTFS_SB(sb)->on_errors & ON_ERRORS_RECOVER)) अणु
		अगर (bh_primary)
			brअन्यथा(bh_primary);
		अगर (!silent)
			ntfs_error(sb, "Mount option errors=recover not used. "
					"Aborting without trying to recover.");
		वापस शून्य;
	पूर्ण
	/* Try to पढ़ो NT4+ backup boot sector. */
	अगर ((bh_backup = sb_bपढ़ो(sb, nr_blocks - 1))) अणु
		अगर (is_boot_sector_ntfs(sb, (NTFS_BOOT_SECTOR*)
				bh_backup->b_data, silent))
			जाओ hotfix_primary_boot_sector;
		brअन्यथा(bh_backup);
	पूर्ण अन्यथा अगर (!silent)
		ntfs_error(sb, पढ़ो_err_str, "backup");
	/* Try to पढ़ो NT3.51- backup boot sector. */
	अगर ((bh_backup = sb_bपढ़ो(sb, nr_blocks >> 1))) अणु
		अगर (is_boot_sector_ntfs(sb, (NTFS_BOOT_SECTOR*)
				bh_backup->b_data, silent))
			जाओ hotfix_primary_boot_sector;
		अगर (!silent)
			ntfs_error(sb, "Could not find a valid backup boot "
					"sector.");
		brअन्यथा(bh_backup);
	पूर्ण अन्यथा अगर (!silent)
		ntfs_error(sb, पढ़ो_err_str, "backup");
	/* We failed. Cleanup and वापस. */
	अगर (bh_primary)
		brअन्यथा(bh_primary);
	वापस शून्य;
hotfix_primary_boot_sector:
	अगर (bh_primary) अणु
		/*
		 * If we managed to पढ़ो sector zero and the volume is not
		 * पढ़ो-only, copy the found, valid backup boot sector to the
		 * primary boot sector.  Note we only copy the actual boot
		 * sector काष्ठाure, not the actual whole device sector as that
		 * may be bigger and would potentially damage the $Boot प्रणाली
		 * file (FIXME: Would be nice to know अगर the backup boot sector
		 * on a large sector device contains the whole boot loader or
		 * just the first 512 bytes).
		 */
		अगर (!sb_rकरोnly(sb)) अणु
			ntfs_warning(sb, "Hot-fix: Recovering invalid primary "
					"boot sector from backup copy.");
			स_नकल(bh_primary->b_data, bh_backup->b_data,
					NTFS_BLOCK_SIZE);
			mark_buffer_dirty(bh_primary);
			sync_dirty_buffer(bh_primary);
			अगर (buffer_uptodate(bh_primary)) अणु
				brअन्यथा(bh_backup);
				वापस bh_primary;
			पूर्ण
			ntfs_error(sb, "Hot-fix: Device write error while "
					"recovering primary boot sector.");
		पूर्ण अन्यथा अणु
			ntfs_warning(sb, "Hot-fix: Recovery of primary boot "
					"sector failed: Read-only mount.");
		पूर्ण
		brअन्यथा(bh_primary);
	पूर्ण
	ntfs_warning(sb, "Using backup boot sector.");
	वापस bh_backup;
पूर्ण

/**
 * parse_ntfs_boot_sector - parse the boot sector and store the data in @vol
 * @vol:	volume काष्ठाure to initialise with data from boot sector
 * @b:		boot sector to parse
 *
 * Parse the ntfs boot sector @b and store all imporant inक्रमmation therein in
 * the ntfs super block @vol.  Return 'true' on success and 'false' on error.
 */
अटल bool parse_ntfs_boot_sector(ntfs_volume *vol, स्थिर NTFS_BOOT_SECTOR *b)
अणु
	अचिन्हित पूर्णांक sectors_per_cluster_bits, nr_hidden_sects;
	पूर्णांक clusters_per_mft_record, clusters_per_index_record;
	s64 ll;

	vol->sector_size = le16_to_cpu(b->bpb.bytes_per_sector);
	vol->sector_size_bits = ffs(vol->sector_size) - 1;
	ntfs_debug("vol->sector_size = %i (0x%x)", vol->sector_size,
			vol->sector_size);
	ntfs_debug("vol->sector_size_bits = %i (0x%x)", vol->sector_size_bits,
			vol->sector_size_bits);
	अगर (vol->sector_size < vol->sb->s_blocksize) अणु
		ntfs_error(vol->sb, "Sector size (%i) is smaller than the "
				"device block size (%lu).  This is not "
				"supported.  Sorry.", vol->sector_size,
				vol->sb->s_blocksize);
		वापस false;
	पूर्ण
	ntfs_debug("sectors_per_cluster = 0x%x", b->bpb.sectors_per_cluster);
	sectors_per_cluster_bits = ffs(b->bpb.sectors_per_cluster) - 1;
	ntfs_debug("sectors_per_cluster_bits = 0x%x",
			sectors_per_cluster_bits);
	nr_hidden_sects = le32_to_cpu(b->bpb.hidden_sectors);
	ntfs_debug("number of hidden sectors = 0x%x", nr_hidden_sects);
	vol->cluster_size = vol->sector_size << sectors_per_cluster_bits;
	vol->cluster_size_mask = vol->cluster_size - 1;
	vol->cluster_size_bits = ffs(vol->cluster_size) - 1;
	ntfs_debug("vol->cluster_size = %i (0x%x)", vol->cluster_size,
			vol->cluster_size);
	ntfs_debug("vol->cluster_size_mask = 0x%x", vol->cluster_size_mask);
	ntfs_debug("vol->cluster_size_bits = %i", vol->cluster_size_bits);
	अगर (vol->cluster_size < vol->sector_size) अणु
		ntfs_error(vol->sb, "Cluster size (%i) is smaller than the "
				"sector size (%i).  This is not supported.  "
				"Sorry.", vol->cluster_size, vol->sector_size);
		वापस false;
	पूर्ण
	clusters_per_mft_record = b->clusters_per_mft_record;
	ntfs_debug("clusters_per_mft_record = %i (0x%x)",
			clusters_per_mft_record, clusters_per_mft_record);
	अगर (clusters_per_mft_record > 0)
		vol->mft_record_size = vol->cluster_size <<
				(ffs(clusters_per_mft_record) - 1);
	अन्यथा
		/*
		 * When mft_record_size < cluster_size, clusters_per_mft_record
		 * = -log2(mft_record_size) bytes. mft_record_size normaly is
		 * 1024 bytes, which is encoded as 0xF6 (-10 in decimal).
		 */
		vol->mft_record_size = 1 << -clusters_per_mft_record;
	vol->mft_record_size_mask = vol->mft_record_size - 1;
	vol->mft_record_size_bits = ffs(vol->mft_record_size) - 1;
	ntfs_debug("vol->mft_record_size = %i (0x%x)", vol->mft_record_size,
			vol->mft_record_size);
	ntfs_debug("vol->mft_record_size_mask = 0x%x",
			vol->mft_record_size_mask);
	ntfs_debug("vol->mft_record_size_bits = %i (0x%x)",
			vol->mft_record_size_bits, vol->mft_record_size_bits);
	/*
	 * We cannot support mft record sizes above the PAGE_SIZE since
	 * we store $MFT/$DATA, the table of mft records in the page cache.
	 */
	अगर (vol->mft_record_size > PAGE_SIZE) अणु
		ntfs_error(vol->sb, "Mft record size (%i) exceeds the "
				"PAGE_SIZE on your system (%lu).  "
				"This is not supported.  Sorry.",
				vol->mft_record_size, PAGE_SIZE);
		वापस false;
	पूर्ण
	/* We cannot support mft record sizes below the sector size. */
	अगर (vol->mft_record_size < vol->sector_size) अणु
		ntfs_error(vol->sb, "Mft record size (%i) is smaller than the "
				"sector size (%i).  This is not supported.  "
				"Sorry.", vol->mft_record_size,
				vol->sector_size);
		वापस false;
	पूर्ण
	clusters_per_index_record = b->clusters_per_index_record;
	ntfs_debug("clusters_per_index_record = %i (0x%x)",
			clusters_per_index_record, clusters_per_index_record);
	अगर (clusters_per_index_record > 0)
		vol->index_record_size = vol->cluster_size <<
				(ffs(clusters_per_index_record) - 1);
	अन्यथा
		/*
		 * When index_record_size < cluster_size,
		 * clusters_per_index_record = -log2(index_record_size) bytes.
		 * index_record_size normaly equals 4096 bytes, which is
		 * encoded as 0xF4 (-12 in decimal).
		 */
		vol->index_record_size = 1 << -clusters_per_index_record;
	vol->index_record_size_mask = vol->index_record_size - 1;
	vol->index_record_size_bits = ffs(vol->index_record_size) - 1;
	ntfs_debug("vol->index_record_size = %i (0x%x)",
			vol->index_record_size, vol->index_record_size);
	ntfs_debug("vol->index_record_size_mask = 0x%x",
			vol->index_record_size_mask);
	ntfs_debug("vol->index_record_size_bits = %i (0x%x)",
			vol->index_record_size_bits,
			vol->index_record_size_bits);
	/* We cannot support index record sizes below the sector size. */
	अगर (vol->index_record_size < vol->sector_size) अणु
		ntfs_error(vol->sb, "Index record size (%i) is smaller than "
				"the sector size (%i).  This is not "
				"supported.  Sorry.", vol->index_record_size,
				vol->sector_size);
		वापस false;
	पूर्ण
	/*
	 * Get the size of the volume in clusters and check क्रम 64-bit-ness.
	 * Winकरोws currently only uses 32 bits to save the clusters so we करो
	 * the same as it is much faster on 32-bit CPUs.
	 */
	ll = sle64_to_cpu(b->number_of_sectors) >> sectors_per_cluster_bits;
	अगर ((u64)ll >= 1ULL << 32) अणु
		ntfs_error(vol->sb, "Cannot handle 64-bit clusters.  Sorry.");
		वापस false;
	पूर्ण
	vol->nr_clusters = ll;
	ntfs_debug("vol->nr_clusters = 0x%llx", (दीर्घ दीर्घ)vol->nr_clusters);
	/*
	 * On an architecture where अचिन्हित दीर्घ is 32-bits, we restrict the
	 * volume size to 2TiB (2^41). On a 64-bit architecture, the compiler
	 * will hopefully optimize the whole check away.
	 */
	अगर (माप(अचिन्हित दीर्घ) < 8) अणु
		अगर ((ll << vol->cluster_size_bits) >= (1ULL << 41)) अणु
			ntfs_error(vol->sb, "Volume size (%lluTiB) is too "
					"large for this architecture.  "
					"Maximum supported is 2TiB.  Sorry.",
					(अचिन्हित दीर्घ दीर्घ)ll >> (40 -
					vol->cluster_size_bits));
			वापस false;
		पूर्ण
	पूर्ण
	ll = sle64_to_cpu(b->mft_lcn);
	अगर (ll >= vol->nr_clusters) अणु
		ntfs_error(vol->sb, "MFT LCN (%lli, 0x%llx) is beyond end of "
				"volume.  Weird.", (अचिन्हित दीर्घ दीर्घ)ll,
				(अचिन्हित दीर्घ दीर्घ)ll);
		वापस false;
	पूर्ण
	vol->mft_lcn = ll;
	ntfs_debug("vol->mft_lcn = 0x%llx", (दीर्घ दीर्घ)vol->mft_lcn);
	ll = sle64_to_cpu(b->mfपंचांगirr_lcn);
	अगर (ll >= vol->nr_clusters) अणु
		ntfs_error(vol->sb, "MFTMirr LCN (%lli, 0x%llx) is beyond end "
				"of volume.  Weird.", (अचिन्हित दीर्घ दीर्घ)ll,
				(अचिन्हित दीर्घ दीर्घ)ll);
		वापस false;
	पूर्ण
	vol->mfपंचांगirr_lcn = ll;
	ntfs_debug("vol->mftmirr_lcn = 0x%llx", (दीर्घ दीर्घ)vol->mfपंचांगirr_lcn);
#अगर_घोषित NTFS_RW
	/*
	 * Work out the size of the mft mirror in number of mft records. If the
	 * cluster size is less than or equal to the size taken by four mft
	 * records, the mft mirror stores the first four mft records. If the
	 * cluster size is bigger than the size taken by four mft records, the
	 * mft mirror contains as many mft records as will fit पूर्णांकo one
	 * cluster.
	 */
	अगर (vol->cluster_size <= (4 << vol->mft_record_size_bits))
		vol->mfपंचांगirr_size = 4;
	अन्यथा
		vol->mfपंचांगirr_size = vol->cluster_size >>
				vol->mft_record_size_bits;
	ntfs_debug("vol->mftmirr_size = %i", vol->mfपंचांगirr_size);
#पूर्ण_अगर /* NTFS_RW */
	vol->serial_no = le64_to_cpu(b->volume_serial_number);
	ntfs_debug("vol->serial_no = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->serial_no);
	वापस true;
पूर्ण

/**
 * ntfs_setup_allocators - initialize the cluster and mft allocators
 * @vol:	volume काष्ठाure क्रम which to setup the allocators
 *
 * Setup the cluster (lcn) and mft allocators to the starting values.
 */
अटल व्योम ntfs_setup_allocators(ntfs_volume *vol)
अणु
#अगर_घोषित NTFS_RW
	LCN mft_zone_size, mft_lcn;
#पूर्ण_अगर /* NTFS_RW */

	ntfs_debug("vol->mft_zone_multiplier = 0x%x",
			vol->mft_zone_multiplier);
#अगर_घोषित NTFS_RW
	/* Determine the size of the MFT zone. */
	mft_zone_size = vol->nr_clusters;
	चयन (vol->mft_zone_multiplier) अणु  /* % of volume size in clusters */
	हाल 4:
		mft_zone_size >>= 1;			/* 50%   */
		अवरोध;
	हाल 3:
		mft_zone_size = (mft_zone_size +
				(mft_zone_size >> 1)) >> 2;	/* 37.5% */
		अवरोध;
	हाल 2:
		mft_zone_size >>= 2;			/* 25%   */
		अवरोध;
	/* हाल 1: */
	शेष:
		mft_zone_size >>= 3;			/* 12.5% */
		अवरोध;
	पूर्ण
	/* Setup the mft zone. */
	vol->mft_zone_start = vol->mft_zone_pos = vol->mft_lcn;
	ntfs_debug("vol->mft_zone_pos = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_pos);
	/*
	 * Calculate the mft_lcn क्रम an unmodअगरied NTFS volume (see mkntfs
	 * source) and अगर the actual mft_lcn is in the expected place or even
	 * further to the front of the volume, extend the mft_zone to cover the
	 * beginning of the volume as well.  This is in order to protect the
	 * area reserved क्रम the mft biपंचांगap as well within the mft_zone itself.
	 * On non-standard volumes we करो not protect it as the overhead would
	 * be higher than the speed increase we would get by करोing it.
	 */
	mft_lcn = (8192 + 2 * vol->cluster_size - 1) / vol->cluster_size;
	अगर (mft_lcn * vol->cluster_size < 16 * 1024)
		mft_lcn = (16 * 1024 + vol->cluster_size - 1) /
				vol->cluster_size;
	अगर (vol->mft_zone_start <= mft_lcn)
		vol->mft_zone_start = 0;
	ntfs_debug("vol->mft_zone_start = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_start);
	/*
	 * Need to cap the mft zone on non-standard volumes so that it करोes
	 * not poपूर्णांक outside the boundaries of the volume.  We करो this by
	 * halving the zone size until we are inside the volume.
	 */
	vol->mft_zone_end = vol->mft_lcn + mft_zone_size;
	जबतक (vol->mft_zone_end >= vol->nr_clusters) अणु
		mft_zone_size >>= 1;
		vol->mft_zone_end = vol->mft_lcn + mft_zone_size;
	पूर्ण
	ntfs_debug("vol->mft_zone_end = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_end);
	/*
	 * Set the current position within each data zone to the start of the
	 * respective zone.
	 */
	vol->data1_zone_pos = vol->mft_zone_end;
	ntfs_debug("vol->data1_zone_pos = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->data1_zone_pos);
	vol->data2_zone_pos = 0;
	ntfs_debug("vol->data2_zone_pos = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->data2_zone_pos);

	/* Set the mft data allocation position to mft record 24. */
	vol->mft_data_pos = 24;
	ntfs_debug("vol->mft_data_pos = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)vol->mft_data_pos);
#पूर्ण_अगर /* NTFS_RW */
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * load_and_init_mft_mirror - load and setup the mft mirror inode क्रम a volume
 * @vol:	ntfs super block describing device whose mft mirror to load
 *
 * Return 'true' on success or 'false' on error.
 */
अटल bool load_and_init_mft_mirror(ntfs_volume *vol)
अणु
	काष्ठा inode *पंचांगp_ino;
	ntfs_inode *पंचांगp_ni;

	ntfs_debug("Entering.");
	/* Get mft mirror inode. */
	पंचांगp_ino = ntfs_iget(vol->sb, खाता_MFTMirr);
	अगर (IS_ERR(पंचांगp_ino) || is_bad_inode(पंचांगp_ino)) अणु
		अगर (!IS_ERR(पंचांगp_ino))
			iput(पंचांगp_ino);
		/* Caller will display error message. */
		वापस false;
	पूर्ण
	/*
	 * Re-initialize some specअगरics about $MFTMirr's inode as
	 * ntfs_पढ़ो_inode() will have set up the शेष ones.
	 */
	/* Set uid and gid to root. */
	पंचांगp_ino->i_uid = GLOBAL_ROOT_UID;
	पंचांगp_ino->i_gid = GLOBAL_ROOT_GID;
	/* Regular file.  No access क्रम anyone. */
	पंचांगp_ino->i_mode = S_IFREG;
	/* No VFS initiated operations allowed क्रम $MFTMirr. */
	पंचांगp_ino->i_op = &ntfs_empty_inode_ops;
	पंचांगp_ino->i_fop = &ntfs_empty_file_ops;
	/* Put in our special address space operations. */
	पंचांगp_ino->i_mapping->a_ops = &ntfs_mst_aops;
	पंचांगp_ni = NTFS_I(पंचांगp_ino);
	/* The $MFTMirr, like the $MFT is multi sector transfer रक्षित. */
	NInoSetMstProtected(पंचांगp_ni);
	NInoSetSparseDisabled(पंचांगp_ni);
	/*
	 * Set up our little cheat allowing us to reuse the async पढ़ो io
	 * completion handler क्रम directories.
	 */
	पंचांगp_ni->itype.index.block_size = vol->mft_record_size;
	पंचांगp_ni->itype.index.block_size_bits = vol->mft_record_size_bits;
	vol->mfपंचांगirr_ino = पंचांगp_ino;
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * check_mft_mirror - compare contents of the mft mirror with the mft
 * @vol:	ntfs super block describing device whose mft mirror to check
 *
 * Return 'true' on success or 'false' on error.
 *
 * Note, this function also results in the mft mirror runlist being completely
 * mapped पूर्णांकo memory.  The mft mirror ग_लिखो code requires this and will BUG()
 * should it find an unmapped runlist element.
 */
अटल bool check_mft_mirror(ntfs_volume *vol)
अणु
	काष्ठा super_block *sb = vol->sb;
	ntfs_inode *mirr_ni;
	काष्ठा page *mft_page, *mirr_page;
	u8 *kmft, *kmirr;
	runlist_element *rl, rl2[2];
	pgoff_t index;
	पूर्णांक mrecs_per_page, i;

	ntfs_debug("Entering.");
	/* Compare contents of $MFT and $MFTMirr. */
	mrecs_per_page = PAGE_SIZE / vol->mft_record_size;
	BUG_ON(!mrecs_per_page);
	BUG_ON(!vol->mfपंचांगirr_size);
	mft_page = mirr_page = शून्य;
	kmft = kmirr = शून्य;
	index = i = 0;
	करो अणु
		u32 bytes;

		/* Switch pages अगर necessary. */
		अगर (!(i % mrecs_per_page)) अणु
			अगर (index) अणु
				ntfs_unmap_page(mft_page);
				ntfs_unmap_page(mirr_page);
			पूर्ण
			/* Get the $MFT page. */
			mft_page = ntfs_map_page(vol->mft_ino->i_mapping,
					index);
			अगर (IS_ERR(mft_page)) अणु
				ntfs_error(sb, "Failed to read $MFT.");
				वापस false;
			पूर्ण
			kmft = page_address(mft_page);
			/* Get the $MFTMirr page. */
			mirr_page = ntfs_map_page(vol->mfपंचांगirr_ino->i_mapping,
					index);
			अगर (IS_ERR(mirr_page)) अणु
				ntfs_error(sb, "Failed to read $MFTMirr.");
				जाओ mft_unmap_out;
			पूर्ण
			kmirr = page_address(mirr_page);
			++index;
		पूर्ण
		/* Do not check the record अगर it is not in use. */
		अगर (((MFT_RECORD*)kmft)->flags & MFT_RECORD_IN_USE) अणु
			/* Make sure the record is ok. */
			अगर (ntfs_is_baad_recordp((le32*)kmft)) अणु
				ntfs_error(sb, "Incomplete multi sector "
						"transfer detected in mft "
						"record %i.", i);
mm_unmap_out:
				ntfs_unmap_page(mirr_page);
mft_unmap_out:
				ntfs_unmap_page(mft_page);
				वापस false;
			पूर्ण
		पूर्ण
		/* Do not check the mirror record अगर it is not in use. */
		अगर (((MFT_RECORD*)kmirr)->flags & MFT_RECORD_IN_USE) अणु
			अगर (ntfs_is_baad_recordp((le32*)kmirr)) अणु
				ntfs_error(sb, "Incomplete multi sector "
						"transfer detected in mft "
						"mirror record %i.", i);
				जाओ mm_unmap_out;
			पूर्ण
		पूर्ण
		/* Get the amount of data in the current record. */
		bytes = le32_to_cpu(((MFT_RECORD*)kmft)->bytes_in_use);
		अगर (bytes < माप(MFT_RECORD_OLD) ||
				bytes > vol->mft_record_size ||
				ntfs_is_baad_recordp((le32*)kmft)) अणु
			bytes = le32_to_cpu(((MFT_RECORD*)kmirr)->bytes_in_use);
			अगर (bytes < माप(MFT_RECORD_OLD) ||
					bytes > vol->mft_record_size ||
					ntfs_is_baad_recordp((le32*)kmirr))
				bytes = vol->mft_record_size;
		पूर्ण
		/* Compare the two records. */
		अगर (स_भेद(kmft, kmirr, bytes)) अणु
			ntfs_error(sb, "$MFT and $MFTMirr (record %i) do not "
					"match.  Run ntfsfix or chkdsk.", i);
			जाओ mm_unmap_out;
		पूर्ण
		kmft += vol->mft_record_size;
		kmirr += vol->mft_record_size;
	पूर्ण जबतक (++i < vol->mfपंचांगirr_size);
	/* Release the last pages. */
	ntfs_unmap_page(mft_page);
	ntfs_unmap_page(mirr_page);

	/* Conकाष्ठा the mft mirror runlist by hand. */
	rl2[0].vcn = 0;
	rl2[0].lcn = vol->mfपंचांगirr_lcn;
	rl2[0].length = (vol->mfपंचांगirr_size * vol->mft_record_size +
			vol->cluster_size - 1) / vol->cluster_size;
	rl2[1].vcn = rl2[0].length;
	rl2[1].lcn = LCN_ENOENT;
	rl2[1].length = 0;
	/*
	 * Because we have just पढ़ो all of the mft mirror, we know we have
	 * mapped the full runlist क्रम it.
	 */
	mirr_ni = NTFS_I(vol->mfपंचांगirr_ino);
	करोwn_पढ़ो(&mirr_ni->runlist.lock);
	rl = mirr_ni->runlist.rl;
	/* Compare the two runlists.  They must be identical. */
	i = 0;
	करो अणु
		अगर (rl2[i].vcn != rl[i].vcn || rl2[i].lcn != rl[i].lcn ||
				rl2[i].length != rl[i].length) अणु
			ntfs_error(sb, "$MFTMirr location mismatch.  "
					"Run chkdsk.");
			up_पढ़ो(&mirr_ni->runlist.lock);
			वापस false;
		पूर्ण
	पूर्ण जबतक (rl2[i++].length);
	up_पढ़ो(&mirr_ni->runlist.lock);
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * load_and_check_logfile - load and check the logfile inode क्रम a volume
 * @vol:	ntfs super block describing device whose logfile to load
 *
 * Return 'true' on success or 'false' on error.
 */
अटल bool load_and_check_logfile(ntfs_volume *vol,
		RESTART_PAGE_HEADER **rp)
अणु
	काष्ठा inode *पंचांगp_ino;

	ntfs_debug("Entering.");
	पंचांगp_ino = ntfs_iget(vol->sb, खाता_LogFile);
	अगर (IS_ERR(पंचांगp_ino) || is_bad_inode(पंचांगp_ino)) अणु
		अगर (!IS_ERR(पंचांगp_ino))
			iput(पंचांगp_ino);
		/* Caller will display error message. */
		वापस false;
	पूर्ण
	अगर (!ntfs_check_logfile(पंचांगp_ino, rp)) अणु
		iput(पंचांगp_ino);
		/* ntfs_check_logfile() will have displayed error output. */
		वापस false;
	पूर्ण
	NInoSetSparseDisabled(NTFS_I(पंचांगp_ino));
	vol->logfile_ino = पंचांगp_ino;
	ntfs_debug("Done.");
	वापस true;
पूर्ण

#घोषणा NTFS_HIBERFIL_HEADER_SIZE	4096

/**
 * check_winकरोws_hibernation_status - check अगर Winकरोws is suspended on a volume
 * @vol:	ntfs super block of device to check
 *
 * Check अगर Winकरोws is hibernated on the ntfs volume @vol.  This is करोne by
 * looking क्रम the file hiberfil.sys in the root directory of the volume.  If
 * the file is not present Winकरोws is definitely not suspended.
 *
 * If hiberfil.sys exists and is less than 4kiB in size it means Winकरोws is
 * definitely suspended (this volume is not the प्रणाली volume).  Caveat:  on a
 * प्रणाली with many volumes it is possible that the < 4kiB check is bogus but
 * क्रम now this should करो fine.
 *
 * If hiberfil.sys exists and is larger than 4kiB in size, we need to पढ़ो the
 * hiberfil header (which is the first 4kiB).  If this begins with "hibr",
 * Winकरोws is definitely suspended.  If it is completely full of zeroes,
 * Winकरोws is definitely not hibernated.  Any other हाल is treated as अगर
 * Winकरोws is suspended.  This caters क्रम the above mentioned caveat of a
 * प्रणाली with many volumes where no "hibr" magic would be present and there is
 * no zero header.
 *
 * Return 0 अगर Winकरोws is not hibernated on the volume, >0 अगर Winकरोws is
 * hibernated on the volume, and -त्रुटि_सं on error.
 */
अटल पूर्णांक check_winकरोws_hibernation_status(ntfs_volume *vol)
अणु
	MFT_REF mref;
	काष्ठा inode *vi;
	काष्ठा page *page;
	u32 *kaddr, *kend;
	ntfs_name *name = शून्य;
	पूर्णांक ret = 1;
	अटल स्थिर ntfsअक्षर hiberfil[13] = अणु cpu_to_le16('h'),
			cpu_to_le16('i'), cpu_to_le16('b'),
			cpu_to_le16('e'), cpu_to_le16('r'),
			cpu_to_le16('f'), cpu_to_le16('i'),
			cpu_to_le16('l'), cpu_to_le16('.'),
			cpu_to_le16('s'), cpu_to_le16('y'),
			cpu_to_le16('s'), 0 पूर्ण;

	ntfs_debug("Entering.");
	/*
	 * Find the inode number क्रम the hibernation file by looking up the
	 * filename hiberfil.sys in the root directory.
	 */
	inode_lock(vol->root_ino);
	mref = ntfs_lookup_inode_by_name(NTFS_I(vol->root_ino), hiberfil, 12,
			&name);
	inode_unlock(vol->root_ino);
	अगर (IS_ERR_MREF(mref)) अणु
		ret = MREF_ERR(mref);
		/* If the file करोes not exist, Winकरोws is not hibernated. */
		अगर (ret == -ENOENT) अणु
			ntfs_debug("hiberfil.sys not present.  Windows is not "
					"hibernated on the volume.");
			वापस 0;
		पूर्ण
		/* A real error occurred. */
		ntfs_error(vol->sb, "Failed to find inode number for "
				"hiberfil.sys.");
		वापस ret;
	पूर्ण
	/* We करो not care क्रम the type of match that was found. */
	kमुक्त(name);
	/* Get the inode. */
	vi = ntfs_iget(vol->sb, MREF(mref));
	अगर (IS_ERR(vi) || is_bad_inode(vi)) अणु
		अगर (!IS_ERR(vi))
			iput(vi);
		ntfs_error(vol->sb, "Failed to load hiberfil.sys.");
		वापस IS_ERR(vi) ? PTR_ERR(vi) : -EIO;
	पूर्ण
	अगर (unlikely(i_size_पढ़ो(vi) < NTFS_HIBERFIL_HEADER_SIZE)) अणु
		ntfs_debug("hiberfil.sys is smaller than 4kiB (0x%llx).  "
				"Windows is hibernated on the volume.  This "
				"is not the system volume.", i_size_पढ़ो(vi));
		जाओ iput_out;
	पूर्ण
	page = ntfs_map_page(vi->i_mapping, 0);
	अगर (IS_ERR(page)) अणु
		ntfs_error(vol->sb, "Failed to read from hiberfil.sys.");
		ret = PTR_ERR(page);
		जाओ iput_out;
	पूर्ण
	kaddr = (u32*)page_address(page);
	अगर (*(le32*)kaddr == cpu_to_le32(0x72626968)/*'hibr'*/) अणु
		ntfs_debug("Magic \"hibr\" found in hiberfil.sys.  Windows is "
				"hibernated on the volume.  This is the "
				"system volume.");
		जाओ unm_iput_out;
	पूर्ण
	kend = kaddr + NTFS_HIBERFIL_HEADER_SIZE/माप(*kaddr);
	करो अणु
		अगर (unlikely(*kaddr)) अणु
			ntfs_debug("hiberfil.sys is larger than 4kiB "
					"(0x%llx), does not contain the "
					"\"hibr\" magic, and does not have a "
					"zero header.  Windows is hibernated "
					"on the volume.  This is not the "
					"system volume.", i_size_पढ़ो(vi));
			जाओ unm_iput_out;
		पूर्ण
	पूर्ण जबतक (++kaddr < kend);
	ntfs_debug("hiberfil.sys contains a zero header.  Windows is not "
			"hibernated on the volume.  This is the system "
			"volume.");
	ret = 0;
unm_iput_out:
	ntfs_unmap_page(page);
iput_out:
	iput(vi);
	वापस ret;
पूर्ण

/**
 * load_and_init_quota - load and setup the quota file क्रम a volume अगर present
 * @vol:	ntfs super block describing device whose quota file to load
 *
 * Return 'true' on success or 'false' on error.  If $Quota is not present, we
 * leave vol->quota_ino as शून्य and वापस success.
 */
अटल bool load_and_init_quota(ntfs_volume *vol)
अणु
	MFT_REF mref;
	काष्ठा inode *पंचांगp_ino;
	ntfs_name *name = शून्य;
	अटल स्थिर ntfsअक्षर Quota[7] = अणु cpu_to_le16('$'),
			cpu_to_le16('Q'), cpu_to_le16('u'),
			cpu_to_le16('o'), cpu_to_le16('t'),
			cpu_to_le16('a'), 0 पूर्ण;
	अटल ntfsअक्षर Q[3] = अणु cpu_to_le16('$'),
			cpu_to_le16('Q'), 0 पूर्ण;

	ntfs_debug("Entering.");
	/*
	 * Find the inode number क्रम the quota file by looking up the filename
	 * $Quota in the extended प्रणाली files directory $Extend.
	 */
	inode_lock(vol->extend_ino);
	mref = ntfs_lookup_inode_by_name(NTFS_I(vol->extend_ino), Quota, 6,
			&name);
	inode_unlock(vol->extend_ino);
	अगर (IS_ERR_MREF(mref)) अणु
		/*
		 * If the file करोes not exist, quotas are disabled and have
		 * never been enabled on this volume, just वापस success.
		 */
		अगर (MREF_ERR(mref) == -ENOENT) अणु
			ntfs_debug("$Quota not present.  Volume does not have "
					"quotas enabled.");
			/*
			 * No need to try to set quotas out of date अगर they are
			 * not enabled.
			 */
			NVolSetQuotaOutOfDate(vol);
			वापस true;
		पूर्ण
		/* A real error occurred. */
		ntfs_error(vol->sb, "Failed to find inode number for $Quota.");
		वापस false;
	पूर्ण
	/* We करो not care क्रम the type of match that was found. */
	kमुक्त(name);
	/* Get the inode. */
	पंचांगp_ino = ntfs_iget(vol->sb, MREF(mref));
	अगर (IS_ERR(पंचांगp_ino) || is_bad_inode(पंचांगp_ino)) अणु
		अगर (!IS_ERR(पंचांगp_ino))
			iput(पंचांगp_ino);
		ntfs_error(vol->sb, "Failed to load $Quota.");
		वापस false;
	पूर्ण
	vol->quota_ino = पंचांगp_ino;
	/* Get the $Q index allocation attribute. */
	पंचांगp_ino = ntfs_index_iget(vol->quota_ino, Q, 2);
	अगर (IS_ERR(पंचांगp_ino)) अणु
		ntfs_error(vol->sb, "Failed to load $Quota/$Q index.");
		वापस false;
	पूर्ण
	vol->quota_q_ino = पंचांगp_ino;
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * load_and_init_usnjrnl - load and setup the transaction log अगर present
 * @vol:	ntfs super block describing device whose usnjrnl file to load
 *
 * Return 'true' on success or 'false' on error.
 *
 * If $UsnJrnl is not present or in the process of being disabled, we set
 * NVolUsnJrnlStamped() and वापस success.
 *
 * If the $UsnJrnl $DATA/$J attribute has a size equal to the lowest valid usn,
 * i.e. transaction logging has only just been enabled or the journal has been
 * stamped and nothing has been logged since, we also set NVolUsnJrnlStamped()
 * and वापस success.
 */
अटल bool load_and_init_usnjrnl(ntfs_volume *vol)
अणु
	MFT_REF mref;
	काष्ठा inode *पंचांगp_ino;
	ntfs_inode *पंचांगp_ni;
	काष्ठा page *page;
	ntfs_name *name = शून्य;
	USN_HEADER *uh;
	अटल स्थिर ntfsअक्षर UsnJrnl[9] = अणु cpu_to_le16('$'),
			cpu_to_le16('U'), cpu_to_le16('s'),
			cpu_to_le16('n'), cpu_to_le16('J'),
			cpu_to_le16('r'), cpu_to_le16('n'),
			cpu_to_le16('l'), 0 पूर्ण;
	अटल ntfsअक्षर Max[5] = अणु cpu_to_le16('$'),
			cpu_to_le16('M'), cpu_to_le16('a'),
			cpu_to_le16('x'), 0 पूर्ण;
	अटल ntfsअक्षर J[3] = अणु cpu_to_le16('$'),
			cpu_to_le16('J'), 0 पूर्ण;

	ntfs_debug("Entering.");
	/*
	 * Find the inode number क्रम the transaction log file by looking up the
	 * filename $UsnJrnl in the extended प्रणाली files directory $Extend.
	 */
	inode_lock(vol->extend_ino);
	mref = ntfs_lookup_inode_by_name(NTFS_I(vol->extend_ino), UsnJrnl, 8,
			&name);
	inode_unlock(vol->extend_ino);
	अगर (IS_ERR_MREF(mref)) अणु
		/*
		 * If the file करोes not exist, transaction logging is disabled,
		 * just वापस success.
		 */
		अगर (MREF_ERR(mref) == -ENOENT) अणु
			ntfs_debug("$UsnJrnl not present.  Volume does not "
					"have transaction logging enabled.");
not_enabled:
			/*
			 * No need to try to stamp the transaction log अगर
			 * transaction logging is not enabled.
			 */
			NVolSetUsnJrnlStamped(vol);
			वापस true;
		पूर्ण
		/* A real error occurred. */
		ntfs_error(vol->sb, "Failed to find inode number for "
				"$UsnJrnl.");
		वापस false;
	पूर्ण
	/* We करो not care क्रम the type of match that was found. */
	kमुक्त(name);
	/* Get the inode. */
	पंचांगp_ino = ntfs_iget(vol->sb, MREF(mref));
	अगर (IS_ERR(पंचांगp_ino) || unlikely(is_bad_inode(पंचांगp_ino))) अणु
		अगर (!IS_ERR(पंचांगp_ino))
			iput(पंचांगp_ino);
		ntfs_error(vol->sb, "Failed to load $UsnJrnl.");
		वापस false;
	पूर्ण
	vol->usnjrnl_ino = पंचांगp_ino;
	/*
	 * If the transaction log is in the process of being deleted, we can
	 * ignore it.
	 */
	अगर (unlikely(vol->vol_flags & VOLUME_DELETE_USN_UNDERWAY)) अणु
		ntfs_debug("$UsnJrnl in the process of being disabled.  "
				"Volume does not have transaction logging "
				"enabled.");
		जाओ not_enabled;
	पूर्ण
	/* Get the $DATA/$Max attribute. */
	पंचांगp_ino = ntfs_attr_iget(vol->usnjrnl_ino, AT_DATA, Max, 4);
	अगर (IS_ERR(पंचांगp_ino)) अणु
		ntfs_error(vol->sb, "Failed to load $UsnJrnl/$DATA/$Max "
				"attribute.");
		वापस false;
	पूर्ण
	vol->usnjrnl_max_ino = पंचांगp_ino;
	अगर (unlikely(i_size_पढ़ो(पंचांगp_ino) < माप(USN_HEADER))) अणु
		ntfs_error(vol->sb, "Found corrupt $UsnJrnl/$DATA/$Max "
				"attribute (size is 0x%llx but should be at "
				"least 0x%zx bytes).", i_size_पढ़ो(पंचांगp_ino),
				माप(USN_HEADER));
		वापस false;
	पूर्ण
	/* Get the $DATA/$J attribute. */
	पंचांगp_ino = ntfs_attr_iget(vol->usnjrnl_ino, AT_DATA, J, 2);
	अगर (IS_ERR(पंचांगp_ino)) अणु
		ntfs_error(vol->sb, "Failed to load $UsnJrnl/$DATA/$J "
				"attribute.");
		वापस false;
	पूर्ण
	vol->usnjrnl_j_ino = पंचांगp_ino;
	/* Verअगरy $J is non-resident and sparse. */
	पंचांगp_ni = NTFS_I(vol->usnjrnl_j_ino);
	अगर (unlikely(!NInoNonResident(पंचांगp_ni) || !NInoSparse(पंचांगp_ni))) अणु
		ntfs_error(vol->sb, "$UsnJrnl/$DATA/$J attribute is resident "
				"and/or not sparse.");
		वापस false;
	पूर्ण
	/* Read the USN_HEADER from $DATA/$Max. */
	page = ntfs_map_page(vol->usnjrnl_max_ino->i_mapping, 0);
	अगर (IS_ERR(page)) अणु
		ntfs_error(vol->sb, "Failed to read from $UsnJrnl/$DATA/$Max "
				"attribute.");
		वापस false;
	पूर्ण
	uh = (USN_HEADER*)page_address(page);
	/* Sanity check the $Max. */
	अगर (unlikely(sle64_to_cpu(uh->allocation_delta) >
			sle64_to_cpu(uh->maximum_size))) अणु
		ntfs_error(vol->sb, "Allocation delta (0x%llx) exceeds "
				"maximum size (0x%llx).  $UsnJrnl is corrupt.",
				(दीर्घ दीर्घ)sle64_to_cpu(uh->allocation_delta),
				(दीर्घ दीर्घ)sle64_to_cpu(uh->maximum_size));
		ntfs_unmap_page(page);
		वापस false;
	पूर्ण
	/*
	 * If the transaction log has been stamped and nothing has been written
	 * to it since, we करो not need to stamp it.
	 */
	अगर (unlikely(sle64_to_cpu(uh->lowest_valid_usn) >=
			i_size_पढ़ो(vol->usnjrnl_j_ino))) अणु
		अगर (likely(sle64_to_cpu(uh->lowest_valid_usn) ==
				i_size_पढ़ो(vol->usnjrnl_j_ino))) अणु
			ntfs_unmap_page(page);
			ntfs_debug("$UsnJrnl is enabled but nothing has been "
					"logged since it was last stamped.  "
					"Treating this as if the volume does "
					"not have transaction logging "
					"enabled.");
			जाओ not_enabled;
		पूर्ण
		ntfs_error(vol->sb, "$UsnJrnl has lowest valid usn (0x%llx) "
				"which is out of bounds (0x%llx).  $UsnJrnl "
				"is corrupt.",
				(दीर्घ दीर्घ)sle64_to_cpu(uh->lowest_valid_usn),
				i_size_पढ़ो(vol->usnjrnl_j_ino));
		ntfs_unmap_page(page);
		वापस false;
	पूर्ण
	ntfs_unmap_page(page);
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * load_and_init_attrdef - load the attribute definitions table क्रम a volume
 * @vol:	ntfs super block describing device whose attrdef to load
 *
 * Return 'true' on success or 'false' on error.
 */
अटल bool load_and_init_attrdef(ntfs_volume *vol)
अणु
	loff_t i_size;
	काष्ठा super_block *sb = vol->sb;
	काष्ठा inode *ino;
	काष्ठा page *page;
	pgoff_t index, max_index;
	अचिन्हित पूर्णांक size;

	ntfs_debug("Entering.");
	/* Read attrdef table and setup vol->attrdef and vol->attrdef_size. */
	ino = ntfs_iget(sb, खाता_AttrDef);
	अगर (IS_ERR(ino) || is_bad_inode(ino)) अणु
		अगर (!IS_ERR(ino))
			iput(ino);
		जाओ failed;
	पूर्ण
	NInoSetSparseDisabled(NTFS_I(ino));
	/* The size of खाता_AttrDef must be above 0 and fit inside 31 bits. */
	i_size = i_size_पढ़ो(ino);
	अगर (i_size <= 0 || i_size > 0x7fffffff)
		जाओ iput_failed;
	vol->attrdef = (ATTR_DEF*)ntfs_दो_स्मृति_nofs(i_size);
	अगर (!vol->attrdef)
		जाओ iput_failed;
	index = 0;
	max_index = i_size >> PAGE_SHIFT;
	size = PAGE_SIZE;
	जबतक (index < max_index) अणु
		/* Read the attrdef table and copy it पूर्णांकo the linear buffer. */
पढ़ो_partial_attrdef_page:
		page = ntfs_map_page(ino->i_mapping, index);
		अगर (IS_ERR(page))
			जाओ मुक्त_iput_failed;
		स_नकल((u8*)vol->attrdef + (index++ << PAGE_SHIFT),
				page_address(page), size);
		ntfs_unmap_page(page);
	पूर्ण;
	अगर (size == PAGE_SIZE) अणु
		size = i_size & ~PAGE_MASK;
		अगर (size)
			जाओ पढ़ो_partial_attrdef_page;
	पूर्ण
	vol->attrdef_size = i_size;
	ntfs_debug("Read %llu bytes from $AttrDef.", i_size);
	iput(ino);
	वापस true;
मुक्त_iput_failed:
	ntfs_मुक्त(vol->attrdef);
	vol->attrdef = शून्य;
iput_failed:
	iput(ino);
failed:
	ntfs_error(sb, "Failed to initialize attribute definition table.");
	वापस false;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

/**
 * load_and_init_upहाल - load the upहाल table क्रम an ntfs volume
 * @vol:	ntfs super block describing device whose upहाल to load
 *
 * Return 'true' on success or 'false' on error.
 */
अटल bool load_and_init_upहाल(ntfs_volume *vol)
अणु
	loff_t i_size;
	काष्ठा super_block *sb = vol->sb;
	काष्ठा inode *ino;
	काष्ठा page *page;
	pgoff_t index, max_index;
	अचिन्हित पूर्णांक size;
	पूर्णांक i, max;

	ntfs_debug("Entering.");
	/* Read upहाल table and setup vol->upहाल and vol->upहाल_len. */
	ino = ntfs_iget(sb, खाता_UpCase);
	अगर (IS_ERR(ino) || is_bad_inode(ino)) अणु
		अगर (!IS_ERR(ino))
			iput(ino);
		जाओ upहाल_failed;
	पूर्ण
	/*
	 * The upहाल size must not be above 64k Unicode अक्षरacters, must not
	 * be zero and must be a multiple of माप(ntfsअक्षर).
	 */
	i_size = i_size_पढ़ो(ino);
	अगर (!i_size || i_size & (माप(ntfsअक्षर) - 1) ||
			i_size > 64ULL * 1024 * माप(ntfsअक्षर))
		जाओ iput_upहाल_failed;
	vol->upहाल = (ntfsअक्षर*)ntfs_दो_स्मृति_nofs(i_size);
	अगर (!vol->upहाल)
		जाओ iput_upहाल_failed;
	index = 0;
	max_index = i_size >> PAGE_SHIFT;
	size = PAGE_SIZE;
	जबतक (index < max_index) अणु
		/* Read the upहाल table and copy it पूर्णांकo the linear buffer. */
पढ़ो_partial_upहाल_page:
		page = ntfs_map_page(ino->i_mapping, index);
		अगर (IS_ERR(page))
			जाओ iput_upहाल_failed;
		स_नकल((अक्षर*)vol->upहाल + (index++ << PAGE_SHIFT),
				page_address(page), size);
		ntfs_unmap_page(page);
	पूर्ण;
	अगर (size == PAGE_SIZE) अणु
		size = i_size & ~PAGE_MASK;
		अगर (size)
			जाओ पढ़ो_partial_upहाल_page;
	पूर्ण
	vol->upहाल_len = i_size >> UCHAR_T_SIZE_BITS;
	ntfs_debug("Read %llu bytes from $UpCase (expected %zu bytes).",
			i_size, 64 * 1024 * माप(ntfsअक्षर));
	iput(ino);
	mutex_lock(&ntfs_lock);
	अगर (!शेष_upहाल) अणु
		ntfs_debug("Using volume specified $UpCase since default is "
				"not present.");
		mutex_unlock(&ntfs_lock);
		वापस true;
	पूर्ण
	max = शेष_upहाल_len;
	अगर (max > vol->upहाल_len)
		max = vol->upहाल_len;
	क्रम (i = 0; i < max; i++)
		अगर (vol->upहाल[i] != शेष_upहाल[i])
			अवरोध;
	अगर (i == max) अणु
		ntfs_मुक्त(vol->upहाल);
		vol->upहाल = शेष_upहाल;
		vol->upहाल_len = max;
		ntfs_nr_upहाल_users++;
		mutex_unlock(&ntfs_lock);
		ntfs_debug("Volume specified $UpCase matches default. Using "
				"default.");
		वापस true;
	पूर्ण
	mutex_unlock(&ntfs_lock);
	ntfs_debug("Using volume specified $UpCase since it does not match "
			"the default.");
	वापस true;
iput_upहाल_failed:
	iput(ino);
	ntfs_मुक्त(vol->upहाल);
	vol->upहाल = शून्य;
upहाल_failed:
	mutex_lock(&ntfs_lock);
	अगर (शेष_upहाल) अणु
		vol->upहाल = शेष_upहाल;
		vol->upहाल_len = शेष_upहाल_len;
		ntfs_nr_upहाल_users++;
		mutex_unlock(&ntfs_lock);
		ntfs_error(sb, "Failed to load $UpCase from the volume. Using "
				"default.");
		वापस true;
	पूर्ण
	mutex_unlock(&ntfs_lock);
	ntfs_error(sb, "Failed to initialize upcase table.");
	वापस false;
पूर्ण

/*
 * The lcn and mft biपंचांगap inodes are NTFS-पूर्णांकernal inodes with
 * their own special locking rules:
 */
अटल काष्ठा lock_class_key
	lcnbmp_runlist_lock_key, lcnbmp_mrec_lock_key,
	mftbmp_runlist_lock_key, mftbmp_mrec_lock_key;

/**
 * load_प्रणाली_files - खोलो the प्रणाली files using normal functions
 * @vol:	ntfs super block describing device whose प्रणाली files to load
 *
 * Open the प्रणाली files with normal access functions and complete setting up
 * the ntfs super block @vol.
 *
 * Return 'true' on success or 'false' on error.
 */
अटल bool load_प्रणाली_files(ntfs_volume *vol)
अणु
	काष्ठा super_block *sb = vol->sb;
	MFT_RECORD *m;
	VOLUME_INFORMATION *vi;
	ntfs_attr_search_ctx *ctx;
#अगर_घोषित NTFS_RW
	RESTART_PAGE_HEADER *rp;
	पूर्णांक err;
#पूर्ण_अगर /* NTFS_RW */

	ntfs_debug("Entering.");
#अगर_घोषित NTFS_RW
	/* Get mft mirror inode compare the contents of $MFT and $MFTMirr. */
	अगर (!load_and_init_mft_mirror(vol) || !check_mft_mirror(vol)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to load $MFTMirr";
		अटल स्थिर अक्षर *es2 = "$MFTMirr does not match $MFT";
		अटल स्थिर अक्षर *es3 = ".  Run ntfsfix and/or chkdsk.";

		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						!vol->mfपंचांगirr_ino ? es1 : es2,
						es3);
				जाओ iput_mirr_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s",
					!vol->mfपंचांगirr_ino ? es1 : es2, es3);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s",
					!vol->mfपंचांगirr_ino ? es1 : es2, es3);
		/* This will prevent a पढ़ो-ग_लिखो remount. */
		NVolSetErrors(vol);
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */
	/* Get mft biपंचांगap attribute inode. */
	vol->mftbmp_ino = ntfs_attr_iget(vol->mft_ino, AT_BITMAP, शून्य, 0);
	अगर (IS_ERR(vol->mftbmp_ino)) अणु
		ntfs_error(sb, "Failed to load $MFT/$BITMAP attribute.");
		जाओ iput_mirr_err_out;
	पूर्ण
	lockdep_set_class(&NTFS_I(vol->mftbmp_ino)->runlist.lock,
			   &mftbmp_runlist_lock_key);
	lockdep_set_class(&NTFS_I(vol->mftbmp_ino)->mrec_lock,
			   &mftbmp_mrec_lock_key);
	/* Read upहाल table and setup @vol->upहाल and @vol->upहाल_len. */
	अगर (!load_and_init_upहाल(vol))
		जाओ iput_mftbmp_err_out;
#अगर_घोषित NTFS_RW
	/*
	 * Read attribute definitions table and setup @vol->attrdef and
	 * @vol->attrdef_size.
	 */
	अगर (!load_and_init_attrdef(vol))
		जाओ iput_upहाल_err_out;
#पूर्ण_अगर /* NTFS_RW */
	/*
	 * Get the cluster allocation biपंचांगap inode and verअगरy the size, no
	 * need क्रम any locking at this stage as we are alपढ़ोy running
	 * exclusively as we are mount in progress task.
	 */
	vol->lcnbmp_ino = ntfs_iget(sb, खाता_Biपंचांगap);
	अगर (IS_ERR(vol->lcnbmp_ino) || is_bad_inode(vol->lcnbmp_ino)) अणु
		अगर (!IS_ERR(vol->lcnbmp_ino))
			iput(vol->lcnbmp_ino);
		जाओ biपंचांगap_failed;
	पूर्ण
	lockdep_set_class(&NTFS_I(vol->lcnbmp_ino)->runlist.lock,
			   &lcnbmp_runlist_lock_key);
	lockdep_set_class(&NTFS_I(vol->lcnbmp_ino)->mrec_lock,
			   &lcnbmp_mrec_lock_key);

	NInoSetSparseDisabled(NTFS_I(vol->lcnbmp_ino));
	अगर ((vol->nr_clusters + 7) >> 3 > i_size_पढ़ो(vol->lcnbmp_ino)) अणु
		iput(vol->lcnbmp_ino);
biपंचांगap_failed:
		ntfs_error(sb, "Failed to load $Bitmap.");
		जाओ iput_attrdef_err_out;
	पूर्ण
	/*
	 * Get the volume inode and setup our cache of the volume flags and
	 * version.
	 */
	vol->vol_ino = ntfs_iget(sb, खाता_Volume);
	अगर (IS_ERR(vol->vol_ino) || is_bad_inode(vol->vol_ino)) अणु
		अगर (!IS_ERR(vol->vol_ino))
			iput(vol->vol_ino);
volume_failed:
		ntfs_error(sb, "Failed to load $Volume.");
		जाओ iput_lcnbmp_err_out;
	पूर्ण
	m = map_mft_record(NTFS_I(vol->vol_ino));
	अगर (IS_ERR(m)) अणु
iput_volume_failed:
		iput(vol->vol_ino);
		जाओ volume_failed;
	पूर्ण
	अगर (!(ctx = ntfs_attr_get_search_ctx(NTFS_I(vol->vol_ino), m))) अणु
		ntfs_error(sb, "Failed to get attribute search context.");
		जाओ get_ctx_vol_failed;
	पूर्ण
	अगर (ntfs_attr_lookup(AT_VOLUME_INFORMATION, शून्य, 0, 0, 0, शून्य, 0,
			ctx) || ctx->attr->non_resident || ctx->attr->flags) अणु
err_put_vol:
		ntfs_attr_put_search_ctx(ctx);
get_ctx_vol_failed:
		unmap_mft_record(NTFS_I(vol->vol_ino));
		जाओ iput_volume_failed;
	पूर्ण
	vi = (VOLUME_INFORMATION*)((अक्षर*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	/* Some bounds checks. */
	अगर ((u8*)vi < (u8*)ctx->attr || (u8*)vi +
			le32_to_cpu(ctx->attr->data.resident.value_length) >
			(u8*)ctx->attr + le32_to_cpu(ctx->attr->length))
		जाओ err_put_vol;
	/* Copy the volume flags and version to the ntfs_volume काष्ठाure. */
	vol->vol_flags = vi->flags;
	vol->major_ver = vi->major_ver;
	vol->minor_ver = vi->minor_ver;
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(NTFS_I(vol->vol_ino));
	pr_info("volume version %i.%i.\n", vol->major_ver,
			vol->minor_ver);
	अगर (vol->major_ver < 3 && NVolSparseEnabled(vol)) अणु
		ntfs_warning(vol->sb, "Disabling sparse support due to NTFS "
				"volume version %i.%i (need at least version "
				"3.0).", vol->major_ver, vol->minor_ver);
		NVolClearSparseEnabled(vol);
	पूर्ण
#अगर_घोषित NTFS_RW
	/* Make sure that no unsupported volume flags are set. */
	अगर (vol->vol_flags & VOLUME_MUST_MOUNT_RO_MASK) अणु
		अटल स्थिर अक्षर *es1a = "Volume is dirty";
		अटल स्थिर अक्षर *es1b = "Volume has been modified by chkdsk";
		अटल स्थिर अक्षर *es1c = "Volume has unsupported flags set";
		अटल स्थिर अक्षर *es2a = ".  Run chkdsk and mount in Windows.";
		अटल स्थिर अक्षर *es2b = ".  Mount in Windows.";
		स्थिर अक्षर *es1, *es2;

		es2 = es2a;
		अगर (vol->vol_flags & VOLUME_IS_सूचीTY)
			es1 = es1a;
		अन्यथा अगर (vol->vol_flags & VOLUME_MODIFIED_BY_CHKDSK) अणु
			es1 = es1b;
			es2 = es2b;
		पूर्ण अन्यथा अणु
			es1 = es1c;
			ntfs_warning(sb, "Unsupported volume flags 0x%x "
					"encountered.",
					(अचिन्हित)le16_to_cpu(vol->vol_flags));
		पूर्ण
		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				जाओ iput_vol_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/*
		 * Do not set NVolErrors() because ntfs_remount() re-checks the
		 * flags which we need to करो in हाल any flags have changed.
		 */
	पूर्ण
	/*
	 * Get the inode क्रम the logfile, check it and determine अगर the volume
	 * was shutकरोwn cleanly.
	 */
	rp = शून्य;
	अगर (!load_and_check_logfile(vol, &rp) ||
			!ntfs_is_logfile_clean(vol->logfile_ino, rp)) अणु
		अटल स्थिर अक्षर *es1a = "Failed to load $LogFile";
		अटल स्थिर अक्षर *es1b = "$LogFile is not clean";
		अटल स्थिर अक्षर *es2 = ".  Mount in Windows.";
		स्थिर अक्षर *es1;

		es1 = !vol->logfile_ino ? es1a : es1b;
		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				अगर (vol->logfile_ino) अणु
					BUG_ON(!rp);
					ntfs_मुक्त(rp);
				पूर्ण
				जाओ iput_logfile_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a पढ़ो-ग_लिखो remount. */
		NVolSetErrors(vol);
	पूर्ण
	ntfs_मुक्त(rp);
#पूर्ण_अगर /* NTFS_RW */
	/* Get the root directory inode so we can करो path lookups. */
	vol->root_ino = ntfs_iget(sb, खाता_root);
	अगर (IS_ERR(vol->root_ino) || is_bad_inode(vol->root_ino)) अणु
		अगर (!IS_ERR(vol->root_ino))
			iput(vol->root_ino);
		ntfs_error(sb, "Failed to load root directory.");
		जाओ iput_logfile_err_out;
	पूर्ण
#अगर_घोषित NTFS_RW
	/*
	 * Check अगर Winकरोws is suspended to disk on the target volume.  If it
	 * is hibernated, we must not ग_लिखो *anything* to the disk so set
	 * NVolErrors() without setting the dirty volume flag and mount
	 * पढ़ो-only.  This will prevent पढ़ो-ग_लिखो remounting and it will also
	 * prevent all ग_लिखोs.
	 */
	err = check_winकरोws_hibernation_status(vol);
	अगर (unlikely(err)) अणु
		अटल स्थिर अक्षर *es1a = "Failed to determine if Windows is "
				"hibernated";
		अटल स्थिर अक्षर *es1b = "Windows is hibernated";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";
		स्थिर अक्षर *es1;

		es1 = err < 0 ? es1a : es1b;
		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				जाओ iput_root_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a पढ़ो-ग_लिखो remount. */
		NVolSetErrors(vol);
	पूर्ण
	/* If (still) a पढ़ो-ग_लिखो mount, mark the volume dirty. */
	अगर (!sb_rकरोnly(sb) && ntfs_set_volume_flags(vol, VOLUME_IS_सूचीTY)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to set dirty bit in volume "
				"information flags";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* Convert to a पढ़ो-only mount. */
		अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) अणु
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			जाओ iput_root_err_out;
		पूर्ण
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		/*
		 * Do not set NVolErrors() because ntfs_remount() might manage
		 * to set the dirty flag in which हाल all would be well.
		 */
	पूर्ण
#अगर 0
	// TODO: Enable this code once we start modअगरying anything that is
	//	 dअगरferent between NTFS 1.2 and 3.x...
	/*
	 * If (still) a पढ़ो-ग_लिखो mount, set the NT4 compatibility flag on
	 * newer NTFS version volumes.
	 */
	अगर (!(sb->s_flags & SB_RDONLY) && (vol->major_ver > 1) &&
			ntfs_set_volume_flags(vol, VOLUME_MOUNTED_ON_NT4)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to set NT4 compatibility flag";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* Convert to a पढ़ो-only mount. */
		अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) अणु
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			जाओ iput_root_err_out;
		पूर्ण
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	पूर्ण
#पूर्ण_अगर
	/* If (still) a पढ़ो-ग_लिखो mount, empty the logfile. */
	अगर (!sb_rकरोnly(sb) && !ntfs_empty_logfile(vol->logfile_ino)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to empty $LogFile";
		अटल स्थिर अक्षर *es2 = ".  Mount in Windows.";

		/* Convert to a पढ़ो-only mount. */
		अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) अणु
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			जाओ iput_root_err_out;
		पूर्ण
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */
	/* If on NTFS versions beक्रमe 3.0, we are करोne. */
	अगर (unlikely(vol->major_ver < 3))
		वापस true;
	/* NTFS 3.0+ specअगरic initialization. */
	/* Get the security descriptors inode. */
	vol->secure_ino = ntfs_iget(sb, खाता_Secure);
	अगर (IS_ERR(vol->secure_ino) || is_bad_inode(vol->secure_ino)) अणु
		अगर (!IS_ERR(vol->secure_ino))
			iput(vol->secure_ino);
		ntfs_error(sb, "Failed to load $Secure.");
		जाओ iput_root_err_out;
	पूर्ण
	// TODO: Initialize security.
	/* Get the extended प्रणाली files' directory inode. */
	vol->extend_ino = ntfs_iget(sb, खाता_Extend);
	अगर (IS_ERR(vol->extend_ino) || is_bad_inode(vol->extend_ino)) अणु
		अगर (!IS_ERR(vol->extend_ino))
			iput(vol->extend_ino);
		ntfs_error(sb, "Failed to load $Extend.");
		जाओ iput_sec_err_out;
	पूर्ण
#अगर_घोषित NTFS_RW
	/* Find the quota file, load it अगर present, and set it up. */
	अगर (!load_and_init_quota(vol)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to load $Quota";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				जाओ iput_quota_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a पढ़ो-ग_लिखो remount. */
		NVolSetErrors(vol);
	पूर्ण
	/* If (still) a पढ़ो-ग_लिखो mount, mark the quotas out of date. */
	अगर (!sb_rकरोnly(sb) && !ntfs_mark_quotas_out_of_date(vol)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to mark quotas out of date";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* Convert to a पढ़ो-only mount. */
		अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) अणु
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			जाओ iput_quota_err_out;
		पूर्ण
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	पूर्ण
	/*
	 * Find the transaction log file ($UsnJrnl), load it अगर present, check
	 * it, and set it up.
	 */
	अगर (!load_and_init_usnjrnl(vol)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to load $UsnJrnl";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* If a पढ़ो-ग_लिखो mount, convert it to a पढ़ो-only mount. */
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) अणु
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				जाओ iput_usnjrnl_err_out;
			पूर्ण
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		पूर्ण अन्यथा
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a पढ़ो-ग_लिखो remount. */
		NVolSetErrors(vol);
	पूर्ण
	/* If (still) a पढ़ो-ग_लिखो mount, stamp the transaction log. */
	अगर (!sb_rकरोnly(sb) && !ntfs_stamp_usnjrnl(vol)) अणु
		अटल स्थिर अक्षर *es1 = "Failed to stamp transaction log "
				"($UsnJrnl)";
		अटल स्थिर अक्षर *es2 = ".  Run chkdsk.";

		/* Convert to a पढ़ो-only mount. */
		अगर (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) अणु
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			जाओ iput_usnjrnl_err_out;
		पूर्ण
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */
	वापस true;
#अगर_घोषित NTFS_RW
iput_usnjrnl_err_out:
	iput(vol->usnjrnl_j_ino);
	iput(vol->usnjrnl_max_ino);
	iput(vol->usnjrnl_ino);
iput_quota_err_out:
	iput(vol->quota_q_ino);
	iput(vol->quota_ino);
	iput(vol->extend_ino);
#पूर्ण_अगर /* NTFS_RW */
iput_sec_err_out:
	iput(vol->secure_ino);
iput_root_err_out:
	iput(vol->root_ino);
iput_logfile_err_out:
#अगर_घोषित NTFS_RW
	iput(vol->logfile_ino);
iput_vol_err_out:
#पूर्ण_अगर /* NTFS_RW */
	iput(vol->vol_ino);
iput_lcnbmp_err_out:
	iput(vol->lcnbmp_ino);
iput_attrdef_err_out:
	vol->attrdef_size = 0;
	अगर (vol->attrdef) अणु
		ntfs_मुक्त(vol->attrdef);
		vol->attrdef = शून्य;
	पूर्ण
#अगर_घोषित NTFS_RW
iput_upहाल_err_out:
#पूर्ण_अगर /* NTFS_RW */
	vol->upहाल_len = 0;
	mutex_lock(&ntfs_lock);
	अगर (vol->upहाल == शेष_upहाल) अणु
		ntfs_nr_upहाल_users--;
		vol->upहाल = शून्य;
	पूर्ण
	mutex_unlock(&ntfs_lock);
	अगर (vol->upहाल) अणु
		ntfs_मुक्त(vol->upहाल);
		vol->upहाल = शून्य;
	पूर्ण
iput_mftbmp_err_out:
	iput(vol->mftbmp_ino);
iput_mirr_err_out:
#अगर_घोषित NTFS_RW
	iput(vol->mfपंचांगirr_ino);
#पूर्ण_अगर /* NTFS_RW */
	वापस false;
पूर्ण

/**
 * ntfs_put_super - called by the vfs to unmount a volume
 * @sb:		vfs superblock of volume to unmount
 *
 * ntfs_put_super() is called by the VFS (from fs/super.c::करो_umount()) when
 * the volume is being unmounted (umount प्रणाली call has been invoked) and it
 * releases all inodes and memory beदीर्घing to the NTFS specअगरic part of the
 * super block.
 */
अटल व्योम ntfs_put_super(काष्ठा super_block *sb)
अणु
	ntfs_volume *vol = NTFS_SB(sb);

	ntfs_debug("Entering.");

#अगर_घोषित NTFS_RW
	/*
	 * Commit all inodes जबतक they are still खोलो in हाल some of them
	 * cause others to be dirtied.
	 */
	ntfs_commit_inode(vol->vol_ino);

	/* NTFS 3.0+ specअगरic. */
	अगर (vol->major_ver >= 3) अणु
		अगर (vol->usnjrnl_j_ino)
			ntfs_commit_inode(vol->usnjrnl_j_ino);
		अगर (vol->usnjrnl_max_ino)
			ntfs_commit_inode(vol->usnjrnl_max_ino);
		अगर (vol->usnjrnl_ino)
			ntfs_commit_inode(vol->usnjrnl_ino);
		अगर (vol->quota_q_ino)
			ntfs_commit_inode(vol->quota_q_ino);
		अगर (vol->quota_ino)
			ntfs_commit_inode(vol->quota_ino);
		अगर (vol->extend_ino)
			ntfs_commit_inode(vol->extend_ino);
		अगर (vol->secure_ino)
			ntfs_commit_inode(vol->secure_ino);
	पूर्ण

	ntfs_commit_inode(vol->root_ino);

	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	ntfs_commit_inode(vol->lcnbmp_ino);
	up_ग_लिखो(&vol->lcnbmp_lock);

	करोwn_ग_लिखो(&vol->mftbmp_lock);
	ntfs_commit_inode(vol->mftbmp_ino);
	up_ग_लिखो(&vol->mftbmp_lock);

	अगर (vol->logfile_ino)
		ntfs_commit_inode(vol->logfile_ino);

	अगर (vol->mfपंचांगirr_ino)
		ntfs_commit_inode(vol->mfपंचांगirr_ino);
	ntfs_commit_inode(vol->mft_ino);

	/*
	 * If a पढ़ो-ग_लिखो mount and no volume errors have occurred, mark the
	 * volume clean.  Also, re-commit all affected inodes.
	 */
	अगर (!sb_rकरोnly(sb)) अणु
		अगर (!NVolErrors(vol)) अणु
			अगर (ntfs_clear_volume_flags(vol, VOLUME_IS_सूचीTY))
				ntfs_warning(sb, "Failed to clear dirty bit "
						"in volume information "
						"flags.  Run chkdsk.");
			ntfs_commit_inode(vol->vol_ino);
			ntfs_commit_inode(vol->root_ino);
			अगर (vol->mfपंचांगirr_ino)
				ntfs_commit_inode(vol->mfपंचांगirr_ino);
			ntfs_commit_inode(vol->mft_ino);
		पूर्ण अन्यथा अणु
			ntfs_warning(sb, "Volume has errors.  Leaving volume "
					"marked dirty.  Run chkdsk.");
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */

	iput(vol->vol_ino);
	vol->vol_ino = शून्य;

	/* NTFS 3.0+ specअगरic clean up. */
	अगर (vol->major_ver >= 3) अणु
#अगर_घोषित NTFS_RW
		अगर (vol->usnjrnl_j_ino) अणु
			iput(vol->usnjrnl_j_ino);
			vol->usnjrnl_j_ino = शून्य;
		पूर्ण
		अगर (vol->usnjrnl_max_ino) अणु
			iput(vol->usnjrnl_max_ino);
			vol->usnjrnl_max_ino = शून्य;
		पूर्ण
		अगर (vol->usnjrnl_ino) अणु
			iput(vol->usnjrnl_ino);
			vol->usnjrnl_ino = शून्य;
		पूर्ण
		अगर (vol->quota_q_ino) अणु
			iput(vol->quota_q_ino);
			vol->quota_q_ino = शून्य;
		पूर्ण
		अगर (vol->quota_ino) अणु
			iput(vol->quota_ino);
			vol->quota_ino = शून्य;
		पूर्ण
#पूर्ण_अगर /* NTFS_RW */
		अगर (vol->extend_ino) अणु
			iput(vol->extend_ino);
			vol->extend_ino = शून्य;
		पूर्ण
		अगर (vol->secure_ino) अणु
			iput(vol->secure_ino);
			vol->secure_ino = शून्य;
		पूर्ण
	पूर्ण

	iput(vol->root_ino);
	vol->root_ino = शून्य;

	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	iput(vol->lcnbmp_ino);
	vol->lcnbmp_ino = शून्य;
	up_ग_लिखो(&vol->lcnbmp_lock);

	करोwn_ग_लिखो(&vol->mftbmp_lock);
	iput(vol->mftbmp_ino);
	vol->mftbmp_ino = शून्य;
	up_ग_लिखो(&vol->mftbmp_lock);

#अगर_घोषित NTFS_RW
	अगर (vol->logfile_ino) अणु
		iput(vol->logfile_ino);
		vol->logfile_ino = शून्य;
	पूर्ण
	अगर (vol->mfपंचांगirr_ino) अणु
		/* Re-commit the mft mirror and mft just in हाल. */
		ntfs_commit_inode(vol->mfपंचांगirr_ino);
		ntfs_commit_inode(vol->mft_ino);
		iput(vol->mfपंचांगirr_ino);
		vol->mfपंचांगirr_ino = शून्य;
	पूर्ण
	/*
	 * We should have no dirty inodes left, due to
	 * mft.c::ntfs_mft_ग_लिखोpage() cleaning all the dirty pages as
	 * the underlying mft records are written out and cleaned.
	 */
	ntfs_commit_inode(vol->mft_ino);
	ग_लिखो_inode_now(vol->mft_ino, 1);
#पूर्ण_अगर /* NTFS_RW */

	iput(vol->mft_ino);
	vol->mft_ino = शून्य;

	/* Throw away the table of attribute definitions. */
	vol->attrdef_size = 0;
	अगर (vol->attrdef) अणु
		ntfs_मुक्त(vol->attrdef);
		vol->attrdef = शून्य;
	पूर्ण
	vol->upहाल_len = 0;
	/*
	 * Destroy the global शेष upहाल table अगर necessary.  Also decrease
	 * the number of upहाल users अगर we are a user.
	 */
	mutex_lock(&ntfs_lock);
	अगर (vol->upहाल == शेष_upहाल) अणु
		ntfs_nr_upहाल_users--;
		vol->upहाल = शून्य;
	पूर्ण
	अगर (!ntfs_nr_upहाल_users && शेष_upहाल) अणु
		ntfs_मुक्त(शेष_upहाल);
		शेष_upहाल = शून्य;
	पूर्ण
	अगर (vol->cluster_size <= 4096 && !--ntfs_nr_compression_users)
		मुक्त_compression_buffers();
	mutex_unlock(&ntfs_lock);
	अगर (vol->upहाल) अणु
		ntfs_मुक्त(vol->upहाल);
		vol->upहाल = शून्य;
	पूर्ण

	unload_nls(vol->nls_map);

	sb->s_fs_info = शून्य;
	kमुक्त(vol);
पूर्ण

/**
 * get_nr_मुक्त_clusters - वापस the number of मुक्त clusters on a volume
 * @vol:	ntfs volume क्रम which to obtain मुक्त cluster count
 *
 * Calculate the number of मुक्त clusters on the mounted NTFS volume @vol. We
 * actually calculate the number of clusters in use instead because this
 * allows us to not care about partial pages as these will be just zero filled
 * and hence not be counted as allocated clusters.
 *
 * The only particularity is that clusters beyond the end of the logical ntfs
 * volume will be marked as allocated to prevent errors which means we have to
 * discount those at the end. This is important as the cluster biपंचांगap always
 * has a size in multiples of 8 bytes, i.e. up to 63 clusters could be outside
 * the logical volume and marked in use when they are not as they करो not exist.
 *
 * If any pages cannot be पढ़ो we assume all clusters in the erroring pages are
 * in use. This means we वापस an underestimate on errors which is better than
 * an overestimate.
 */
अटल s64 get_nr_मुक्त_clusters(ntfs_volume *vol)
अणु
	s64 nr_मुक्त = vol->nr_clusters;
	काष्ठा address_space *mapping = vol->lcnbmp_ino->i_mapping;
	काष्ठा page *page;
	pgoff_t index, max_index;

	ntfs_debug("Entering.");
	/* Serialize accesses to the cluster biपंचांगap. */
	करोwn_पढ़ो(&vol->lcnbmp_lock);
	/*
	 * Convert the number of bits पूर्णांकo bytes rounded up, then convert पूर्णांकo
	 * multiples of PAGE_SIZE, rounding up so that अगर we have one
	 * full and one partial page max_index = 2.
	 */
	max_index = (((vol->nr_clusters + 7) >> 3) + PAGE_SIZE - 1) >>
			PAGE_SHIFT;
	/* Use multiples of 4 bytes, thus max_size is PAGE_SIZE / 4. */
	ntfs_debug("Reading $Bitmap, max_index = 0x%lx, max_size = 0x%lx.",
			max_index, PAGE_SIZE / 4);
	क्रम (index = 0; index < max_index; index++) अणु
		अचिन्हित दीर्घ *kaddr;

		/*
		 * Read the page from page cache, getting it from backing store
		 * अगर necessary, and increment the use count.
		 */
		page = पढ़ो_mapping_page(mapping, index, शून्य);
		/* Ignore pages which errored synchronously. */
		अगर (IS_ERR(page)) अणु
			ntfs_debug("read_mapping_page() error. Skipping "
					"page (index 0x%lx).", index);
			nr_मुक्त -= PAGE_SIZE * 8;
			जारी;
		पूर्ण
		kaddr = kmap_atomic(page);
		/*
		 * Subtract the number of set bits. If this
		 * is the last page and it is partial we करोn't really care as
		 * it just means we करो a little extra work but it won't affect
		 * the result as all out of range bytes are set to zero by
		 * ntfs_पढ़ोpage().
		 */
		nr_मुक्त -= biपंचांगap_weight(kaddr,
					PAGE_SIZE * BITS_PER_BYTE);
		kunmap_atomic(kaddr);
		put_page(page);
	पूर्ण
	ntfs_debug("Finished reading $Bitmap, last index = 0x%lx.", index - 1);
	/*
	 * Fixup क्रम eventual bits outside logical ntfs volume (see function
	 * description above).
	 */
	अगर (vol->nr_clusters & 63)
		nr_मुक्त += 64 - (vol->nr_clusters & 63);
	up_पढ़ो(&vol->lcnbmp_lock);
	/* If errors occurred we may well have gone below zero, fix this. */
	अगर (nr_मुक्त < 0)
		nr_मुक्त = 0;
	ntfs_debug("Exiting.");
	वापस nr_मुक्त;
पूर्ण

/**
 * __get_nr_मुक्त_mft_records - वापस the number of मुक्त inodes on a volume
 * @vol:	ntfs volume क्रम which to obtain मुक्त inode count
 * @nr_मुक्त:	number of mft records in fileप्रणाली
 * @max_index:	maximum number of pages containing set bits
 *
 * Calculate the number of मुक्त mft records (inodes) on the mounted NTFS
 * volume @vol. We actually calculate the number of mft records in use instead
 * because this allows us to not care about partial pages as these will be just
 * zero filled and hence not be counted as allocated mft record.
 *
 * If any pages cannot be पढ़ो we assume all mft records in the erroring pages
 * are in use. This means we वापस an underestimate on errors which is better
 * than an overestimate.
 *
 * NOTE: Caller must hold mftbmp_lock rw_semaphore क्रम पढ़ोing or writing.
 */
अटल अचिन्हित दीर्घ __get_nr_मुक्त_mft_records(ntfs_volume *vol,
		s64 nr_मुक्त, स्थिर pgoff_t max_index)
अणु
	काष्ठा address_space *mapping = vol->mftbmp_ino->i_mapping;
	काष्ठा page *page;
	pgoff_t index;

	ntfs_debug("Entering.");
	/* Use multiples of 4 bytes, thus max_size is PAGE_SIZE / 4. */
	ntfs_debug("Reading $MFT/$BITMAP, max_index = 0x%lx, max_size = "
			"0x%lx.", max_index, PAGE_SIZE / 4);
	क्रम (index = 0; index < max_index; index++) अणु
		अचिन्हित दीर्घ *kaddr;

		/*
		 * Read the page from page cache, getting it from backing store
		 * अगर necessary, and increment the use count.
		 */
		page = पढ़ो_mapping_page(mapping, index, शून्य);
		/* Ignore pages which errored synchronously. */
		अगर (IS_ERR(page)) अणु
			ntfs_debug("read_mapping_page() error. Skipping "
					"page (index 0x%lx).", index);
			nr_मुक्त -= PAGE_SIZE * 8;
			जारी;
		पूर्ण
		kaddr = kmap_atomic(page);
		/*
		 * Subtract the number of set bits. If this
		 * is the last page and it is partial we करोn't really care as
		 * it just means we करो a little extra work but it won't affect
		 * the result as all out of range bytes are set to zero by
		 * ntfs_पढ़ोpage().
		 */
		nr_मुक्त -= biपंचांगap_weight(kaddr,
					PAGE_SIZE * BITS_PER_BYTE);
		kunmap_atomic(kaddr);
		put_page(page);
	पूर्ण
	ntfs_debug("Finished reading $MFT/$BITMAP, last index = 0x%lx.",
			index - 1);
	/* If errors occurred we may well have gone below zero, fix this. */
	अगर (nr_मुक्त < 0)
		nr_मुक्त = 0;
	ntfs_debug("Exiting.");
	वापस nr_मुक्त;
पूर्ण

/**
 * ntfs_statfs - वापस inक्रमmation about mounted NTFS volume
 * @dentry:	dentry from mounted volume
 * @sfs:	statfs काष्ठाure in which to वापस the inक्रमmation
 *
 * Return inक्रमmation about the mounted NTFS volume @dentry in the statfs काष्ठाure
 * poपूर्णांकed to by @sfs (this is initialized with zeros beक्रमe ntfs_statfs is
 * called). We पूर्णांकerpret the values to be correct of the moment in समय at
 * which we are called. Most values are variable otherwise and this isn't just
 * the मुक्त values but the totals as well. For example we can increase the
 * total number of file nodes अगर we run out and we can keep करोing this until
 * there is no more space on the volume left at all.
 *
 * Called from vfs_statfs which is used to handle the statfs, ख_स्थितिfs, and
 * ustat प्रणाली calls.
 *
 * Return 0 on success or -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *sfs)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	s64 size;
	ntfs_volume *vol = NTFS_SB(sb);
	ntfs_inode *mft_ni = NTFS_I(vol->mft_ino);
	pgoff_t max_index;
	अचिन्हित दीर्घ flags;

	ntfs_debug("Entering.");
	/* Type of fileप्रणाली. */
	sfs->f_type   = NTFS_SB_MAGIC;
	/* Optimal transfer block size. */
	sfs->f_bsize  = PAGE_SIZE;
	/*
	 * Total data blocks in fileप्रणाली in units of f_bsize and since
	 * inodes are also stored in data blocs ($MFT is a file) this is just
	 * the total clusters.
	 */
	sfs->f_blocks = vol->nr_clusters << vol->cluster_size_bits >>
				PAGE_SHIFT;
	/* Free data blocks in fileप्रणाली in units of f_bsize. */
	size	      = get_nr_मुक्त_clusters(vol) << vol->cluster_size_bits >>
				PAGE_SHIFT;
	अगर (size < 0LL)
		size = 0LL;
	/* Free blocks avail to non-superuser, same as above on NTFS. */
	sfs->f_bavail = sfs->f_bमुक्त = size;
	/* Serialize accesses to the inode biपंचांगap. */
	करोwn_पढ़ो(&vol->mftbmp_lock);
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	size = i_size_पढ़ो(vol->mft_ino) >> vol->mft_record_size_bits;
	/*
	 * Convert the maximum number of set bits पूर्णांकo bytes rounded up, then
	 * convert पूर्णांकo multiples of PAGE_SIZE, rounding up so that अगर we
	 * have one full and one partial page max_index = 2.
	 */
	max_index = ((((mft_ni->initialized_size >> vol->mft_record_size_bits)
			+ 7) >> 3) + PAGE_SIZE - 1) >> PAGE_SHIFT;
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	/* Number of inodes in fileप्रणाली (at this poपूर्णांक in समय). */
	sfs->f_files = size;
	/* Free inodes in fs (based on current total count). */
	sfs->f_fमुक्त = __get_nr_मुक्त_mft_records(vol, size, max_index);
	up_पढ़ो(&vol->mftbmp_lock);
	/*
	 * File प्रणाली id. This is extremely *nix flavour dependent and even
	 * within Linux itself all fs करो their own thing. I पूर्णांकerpret this to
	 * mean a unique id associated with the mounted fs and not the id
	 * associated with the fileप्रणाली driver, the latter is alपढ़ोy given
	 * by the fileप्रणाली type in sfs->f_type. Thus we use the 64-bit
	 * volume serial number splitting it पूर्णांकo two 32-bit parts. We enter
	 * the least signअगरicant 32-bits in f_fsid[0] and the most signअगरicant
	 * 32-bits in f_fsid[1].
	 */
	sfs->f_fsid = u64_to_fsid(vol->serial_no);
	/* Maximum length of filenames. */
	sfs->f_namelen	   = NTFS_MAX_NAME_LEN;
	वापस 0;
पूर्ण

#अगर_घोषित NTFS_RW
अटल पूर्णांक ntfs_ग_लिखो_inode(काष्ठा inode *vi, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __ntfs_ग_लिखो_inode(vi, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण
#पूर्ण_अगर

/**
 * The complete super operations.
 */
अटल स्थिर काष्ठा super_operations ntfs_sops = अणु
	.alloc_inode	= ntfs_alloc_big_inode,	  /* VFS: Allocate new inode. */
	.मुक्त_inode	= ntfs_मुक्त_big_inode, /* VFS: Deallocate inode. */
#अगर_घोषित NTFS_RW
	.ग_लिखो_inode	= ntfs_ग_लिखो_inode,	/* VFS: Write dirty inode to
						   disk. */
#पूर्ण_अगर /* NTFS_RW */
	.put_super	= ntfs_put_super,	/* Syscall: umount. */
	.statfs		= ntfs_statfs,		/* Syscall: statfs */
	.remount_fs	= ntfs_remount,		/* Syscall: mount -o remount. */
	.evict_inode	= ntfs_evict_big_inode,	/* VFS: Called when an inode is
						   हटाओd from memory. */
	.show_options	= ntfs_show_options,	/* Show mount options in
						   proc. */
पूर्ण;

/**
 * ntfs_fill_super - mount an ntfs fileप्रणाली
 * @sb:		super block of ntfs fileप्रणाली to mount
 * @opt:	string containing the mount options
 * @silent:	silence error output
 *
 * ntfs_fill_super() is called by the VFS to mount the device described by @sb
 * with the mount otions in @data with the NTFS fileप्रणाली.
 *
 * If @silent is true, reमुख्य silent even अगर errors are detected. This is used
 * during bootup, when the kernel tries to mount the root fileप्रणाली with all
 * रेजिस्टरed fileप्रणालीs one after the other until one succeeds. This implies
 * that all fileप्रणालीs except the correct one will quite correctly and
 * expectedly वापस an error, but nobody wants to see error messages when in
 * fact this is what is supposed to happen.
 *
 * NOTE: @sb->s_flags contains the mount options flags.
 */
अटल पूर्णांक ntfs_fill_super(काष्ठा super_block *sb, व्योम *opt, स्थिर पूर्णांक silent)
अणु
	ntfs_volume *vol;
	काष्ठा buffer_head *bh;
	काष्ठा inode *पंचांगp_ino;
	पूर्णांक blocksize, result;

	/*
	 * We करो a pretty dअगरficult piece of bootstrap by पढ़ोing the
	 * MFT (and other metadata) from disk पूर्णांकo memory. We'll only
	 * release this metadata during umount, so the locking patterns
	 * observed during bootstrap करो not count. So turn off the
	 * observation of locking patterns (strictly क्रम this context
	 * only) जबतक mounting NTFS. [The validator is still active
	 * otherwise, even क्रम this context: it will क्रम example record
	 * lock class registrations.]
	 */
	lockdep_off();
	ntfs_debug("Entering.");
#अगर_अघोषित NTFS_RW
	sb->s_flags |= SB_RDONLY;
#पूर्ण_अगर /* ! NTFS_RW */
	/* Allocate a new ntfs_volume and place it in sb->s_fs_info. */
	sb->s_fs_info = kदो_स्मृति(माप(ntfs_volume), GFP_NOFS);
	vol = NTFS_SB(sb);
	अगर (!vol) अणु
		अगर (!silent)
			ntfs_error(sb, "Allocation of NTFS volume structure "
					"failed. Aborting mount...");
		lockdep_on();
		वापस -ENOMEM;
	पूर्ण
	/* Initialize ntfs_volume काष्ठाure. */
	*vol = (ntfs_volume) अणु
		.sb = sb,
		/*
		 * Default is group and other करोn't have any access to files or
		 * directories जबतक owner has full access. Further, files by
		 * शेष are not executable but directories are of course
		 * browseable.
		 */
		.fmask = 0177,
		.dmask = 0077,
	पूर्ण;
	init_rwsem(&vol->mftbmp_lock);
	init_rwsem(&vol->lcnbmp_lock);

	/* By शेष, enable sparse support. */
	NVolSetSparseEnabled(vol);

	/* Important to get the mount options dealt with now. */
	अगर (!parse_options(vol, (अक्षर*)opt))
		जाओ err_out_now;

	/* We support sector sizes up to the PAGE_SIZE. */
	अगर (bdev_logical_block_size(sb->s_bdev) > PAGE_SIZE) अणु
		अगर (!silent)
			ntfs_error(sb, "Device has unsupported sector size "
					"(%i).  The maximum supported sector "
					"size on this architecture is %lu "
					"bytes.",
					bdev_logical_block_size(sb->s_bdev),
					PAGE_SIZE);
		जाओ err_out_now;
	पूर्ण
	/*
	 * Setup the device access block size to NTFS_BLOCK_SIZE or the hard
	 * sector size, whichever is bigger.
	 */
	blocksize = sb_min_blocksize(sb, NTFS_BLOCK_SIZE);
	अगर (blocksize < NTFS_BLOCK_SIZE) अणु
		अगर (!silent)
			ntfs_error(sb, "Unable to set device block size.");
		जाओ err_out_now;
	पूर्ण
	BUG_ON(blocksize != sb->s_blocksize);
	ntfs_debug("Set device block size to %i bytes (block size bits %i).",
			blocksize, sb->s_blocksize_bits);
	/* Determine the size of the device in units of block_size bytes. */
	अगर (!i_size_पढ़ो(sb->s_bdev->bd_inode)) अणु
		अगर (!silent)
			ntfs_error(sb, "Unable to determine device size.");
		जाओ err_out_now;
	पूर्ण
	vol->nr_blocks = i_size_पढ़ो(sb->s_bdev->bd_inode) >>
			sb->s_blocksize_bits;
	/* Read the boot sector and वापस unlocked buffer head to it. */
	अगर (!(bh = पढ़ो_ntfs_boot_sector(sb, silent))) अणु
		अगर (!silent)
			ntfs_error(sb, "Not an NTFS volume.");
		जाओ err_out_now;
	पूर्ण
	/*
	 * Extract the data from the boot sector and setup the ntfs volume
	 * using it.
	 */
	result = parse_ntfs_boot_sector(vol, (NTFS_BOOT_SECTOR*)bh->b_data);
	brअन्यथा(bh);
	अगर (!result) अणु
		अगर (!silent)
			ntfs_error(sb, "Unsupported NTFS filesystem.");
		जाओ err_out_now;
	पूर्ण
	/*
	 * If the boot sector indicates a sector size bigger than the current
	 * device block size, चयन the device block size to the sector size.
	 * TODO: It may be possible to support this हाल even when the set
	 * below fails, we would just be अवरोधing up the i/o क्रम each sector
	 * पूर्णांकo multiple blocks क्रम i/o purposes but otherwise it should just
	 * work.  However it is safer to leave disabled until someone hits this
	 * error message and then we can get them to try it without the setting
	 * so we know क्रम sure that it works.
	 */
	अगर (vol->sector_size > blocksize) अणु
		blocksize = sb_set_blocksize(sb, vol->sector_size);
		अगर (blocksize != vol->sector_size) अणु
			अगर (!silent)
				ntfs_error(sb, "Unable to set device block "
						"size to sector size (%i).",
						vol->sector_size);
			जाओ err_out_now;
		पूर्ण
		BUG_ON(blocksize != sb->s_blocksize);
		vol->nr_blocks = i_size_पढ़ो(sb->s_bdev->bd_inode) >>
				sb->s_blocksize_bits;
		ntfs_debug("Changed device block size to %i bytes (block size "
				"bits %i) to match volume sector size.",
				blocksize, sb->s_blocksize_bits);
	पूर्ण
	/* Initialize the cluster and mft allocators. */
	ntfs_setup_allocators(vol);
	/* Setup reमुख्यing fields in the super block. */
	sb->s_magic = NTFS_SB_MAGIC;
	/*
	 * Ntfs allows 63 bits क्रम the file size, i.e. correct would be:
	 *	sb->s_maxbytes = ~0ULL >> 1;
	 * But the kernel uses a दीर्घ as the page cache page index which on
	 * 32-bit architectures is only 32-bits. MAX_LFS_खाताSIZE is kernel
	 * defined to the maximum the page cache page index can cope with
	 * without overflowing the index or to 2^63 - 1, whichever is smaller.
	 */
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	/* Ntfs measures समय in 100ns पूर्णांकervals. */
	sb->s_समय_gran = 100;
	/*
	 * Now load the metadata required क्रम the page cache and our address
	 * space operations to function. We करो this by setting up a specialised
	 * पढ़ो_inode method and then just calling the normal iget() to obtain
	 * the inode क्रम $MFT which is sufficient to allow our normal inode
	 * operations and associated address space operations to function.
	 */
	sb->s_op = &ntfs_sops;
	पंचांगp_ino = new_inode(sb);
	अगर (!पंचांगp_ino) अणु
		अगर (!silent)
			ntfs_error(sb, "Failed to load essential metadata.");
		जाओ err_out_now;
	पूर्ण
	पंचांगp_ino->i_ino = खाता_MFT;
	insert_inode_hash(पंचांगp_ino);
	अगर (ntfs_पढ़ो_inode_mount(पंचांगp_ino) < 0) अणु
		अगर (!silent)
			ntfs_error(sb, "Failed to load essential metadata.");
		जाओ iput_पंचांगp_ino_err_out_now;
	पूर्ण
	mutex_lock(&ntfs_lock);
	/*
	 * The current mount is a compression user अगर the cluster size is
	 * less than or equal 4kiB.
	 */
	अगर (vol->cluster_size <= 4096 && !ntfs_nr_compression_users++) अणु
		result = allocate_compression_buffers();
		अगर (result) अणु
			ntfs_error(शून्य, "Failed to allocate buffers "
					"for compression engine.");
			ntfs_nr_compression_users--;
			mutex_unlock(&ntfs_lock);
			जाओ iput_पंचांगp_ino_err_out_now;
		पूर्ण
	पूर्ण
	/*
	 * Generate the global शेष upहाल table अगर necessary.  Also
	 * temporarily increment the number of upहाल users to aव्योम race
	 * conditions with concurrent (u)mounts.
	 */
	अगर (!शेष_upहाल)
		शेष_upहाल = generate_शेष_upहाल();
	ntfs_nr_upहाल_users++;
	mutex_unlock(&ntfs_lock);
	/*
	 * From now on, ignore @silent parameter. If we fail below this line,
	 * it will be due to a corrupt fs or a प्रणाली error, so we report it.
	 */
	/*
	 * Open the प्रणाली files with normal access functions and complete
	 * setting up the ntfs super block.
	 */
	अगर (!load_प्रणाली_files(vol)) अणु
		ntfs_error(sb, "Failed to load system files.");
		जाओ unl_upहाल_iput_पंचांगp_ino_err_out_now;
	पूर्ण

	/* We grab a reference, simulating an ntfs_iget(). */
	ihold(vol->root_ino);
	अगर ((sb->s_root = d_make_root(vol->root_ino))) अणु
		ntfs_debug("Exiting, status successful.");
		/* Release the शेष upहाल अगर it has no users. */
		mutex_lock(&ntfs_lock);
		अगर (!--ntfs_nr_upहाल_users && शेष_upहाल) अणु
			ntfs_मुक्त(शेष_upहाल);
			शेष_upहाल = शून्य;
		पूर्ण
		mutex_unlock(&ntfs_lock);
		sb->s_export_op = &ntfs_export_ops;
		lockdep_on();
		वापस 0;
	पूर्ण
	ntfs_error(sb, "Failed to allocate root directory.");
	/* Clean up after the successful load_प्रणाली_files() call from above. */
	// TODO: Use ntfs_put_super() instead of repeating all this code...
	// FIXME: Should mark the volume clean as the error is most likely
	// 	  -ENOMEM.
	iput(vol->vol_ino);
	vol->vol_ino = शून्य;
	/* NTFS 3.0+ specअगरic clean up. */
	अगर (vol->major_ver >= 3) अणु
#अगर_घोषित NTFS_RW
		अगर (vol->usnjrnl_j_ino) अणु
			iput(vol->usnjrnl_j_ino);
			vol->usnjrnl_j_ino = शून्य;
		पूर्ण
		अगर (vol->usnjrnl_max_ino) अणु
			iput(vol->usnjrnl_max_ino);
			vol->usnjrnl_max_ino = शून्य;
		पूर्ण
		अगर (vol->usnjrnl_ino) अणु
			iput(vol->usnjrnl_ino);
			vol->usnjrnl_ino = शून्य;
		पूर्ण
		अगर (vol->quota_q_ino) अणु
			iput(vol->quota_q_ino);
			vol->quota_q_ino = शून्य;
		पूर्ण
		अगर (vol->quota_ino) अणु
			iput(vol->quota_ino);
			vol->quota_ino = शून्य;
		पूर्ण
#पूर्ण_अगर /* NTFS_RW */
		अगर (vol->extend_ino) अणु
			iput(vol->extend_ino);
			vol->extend_ino = शून्य;
		पूर्ण
		अगर (vol->secure_ino) अणु
			iput(vol->secure_ino);
			vol->secure_ino = शून्य;
		पूर्ण
	पूर्ण
	iput(vol->root_ino);
	vol->root_ino = शून्य;
	iput(vol->lcnbmp_ino);
	vol->lcnbmp_ino = शून्य;
	iput(vol->mftbmp_ino);
	vol->mftbmp_ino = शून्य;
#अगर_घोषित NTFS_RW
	अगर (vol->logfile_ino) अणु
		iput(vol->logfile_ino);
		vol->logfile_ino = शून्य;
	पूर्ण
	अगर (vol->mfपंचांगirr_ino) अणु
		iput(vol->mfपंचांगirr_ino);
		vol->mfपंचांगirr_ino = शून्य;
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */
	/* Throw away the table of attribute definitions. */
	vol->attrdef_size = 0;
	अगर (vol->attrdef) अणु
		ntfs_मुक्त(vol->attrdef);
		vol->attrdef = शून्य;
	पूर्ण
	vol->upहाल_len = 0;
	mutex_lock(&ntfs_lock);
	अगर (vol->upहाल == शेष_upहाल) अणु
		ntfs_nr_upहाल_users--;
		vol->upहाल = शून्य;
	पूर्ण
	mutex_unlock(&ntfs_lock);
	अगर (vol->upहाल) अणु
		ntfs_मुक्त(vol->upहाल);
		vol->upहाल = शून्य;
	पूर्ण
	अगर (vol->nls_map) अणु
		unload_nls(vol->nls_map);
		vol->nls_map = शून्य;
	पूर्ण
	/* Error निकास code path. */
unl_upहाल_iput_पंचांगp_ino_err_out_now:
	/*
	 * Decrease the number of upहाल users and destroy the global शेष
	 * upहाल table अगर necessary.
	 */
	mutex_lock(&ntfs_lock);
	अगर (!--ntfs_nr_upहाल_users && शेष_upहाल) अणु
		ntfs_मुक्त(शेष_upहाल);
		शेष_upहाल = शून्य;
	पूर्ण
	अगर (vol->cluster_size <= 4096 && !--ntfs_nr_compression_users)
		मुक्त_compression_buffers();
	mutex_unlock(&ntfs_lock);
iput_पंचांगp_ino_err_out_now:
	iput(पंचांगp_ino);
	अगर (vol->mft_ino && vol->mft_ino != पंचांगp_ino)
		iput(vol->mft_ino);
	vol->mft_ino = शून्य;
	/* Errors at this stage are irrelevant. */
err_out_now:
	sb->s_fs_info = शून्य;
	kमुक्त(vol);
	ntfs_debug("Failed, returning -EINVAL.");
	lockdep_on();
	वापस -EINVAL;
पूर्ण

/*
 * This is a slab cache to optimize allocations and deallocations of Unicode
 * strings of the maximum length allowed by NTFS, which is NTFS_MAX_NAME_LEN
 * (255) Unicode अक्षरacters + a terminating शून्य Unicode अक्षरacter.
 */
काष्ठा kmem_cache *ntfs_name_cache;

/* Slab caches क्रम efficient allocation/deallocation of inodes. */
काष्ठा kmem_cache *ntfs_inode_cache;
काष्ठा kmem_cache *ntfs_big_inode_cache;

/* Init once स्थिरructor क्रम the inode slab cache. */
अटल व्योम ntfs_big_inode_init_once(व्योम *foo)
अणु
	ntfs_inode *ni = (ntfs_inode *)foo;

	inode_init_once(VFS_I(ni));
पूर्ण

/*
 * Slab caches to optimize allocations and deallocations of attribute search
 * contexts and index contexts, respectively.
 */
काष्ठा kmem_cache *ntfs_attr_ctx_cache;
काष्ठा kmem_cache *ntfs_index_ctx_cache;

/* Driver wide mutex. */
DEFINE_MUTEX(ntfs_lock);

अटल काष्ठा dentry *ntfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, ntfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type ntfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ntfs",
	.mount		= ntfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("ntfs");

/* Stable names क्रम the slab caches. */
अटल स्थिर अक्षर ntfs_index_ctx_cache_name[] = "ntfs_index_ctx_cache";
अटल स्थिर अक्षर ntfs_attr_ctx_cache_name[] = "ntfs_attr_ctx_cache";
अटल स्थिर अक्षर ntfs_name_cache_name[] = "ntfs_name_cache";
अटल स्थिर अक्षर ntfs_inode_cache_name[] = "ntfs_inode_cache";
अटल स्थिर अक्षर ntfs_big_inode_cache_name[] = "ntfs_big_inode_cache";

अटल पूर्णांक __init init_ntfs_fs(व्योम)
अणु
	पूर्णांक err = 0;

	/* This may be ugly but it results in pretty output so who cares. (-8 */
	pr_info("driver " NTFS_VERSION " [Flags: R/"
#अगर_घोषित NTFS_RW
			"W"
#अन्यथा
			"O"
#पूर्ण_अगर
#अगर_घोषित DEBUG
			" DEBUG"
#पूर्ण_अगर
#अगर_घोषित MODULE
			" MODULE"
#पूर्ण_अगर
			"].\n");

	ntfs_debug("Debug messages are enabled.");

	ntfs_index_ctx_cache = kmem_cache_create(ntfs_index_ctx_cache_name,
			माप(ntfs_index_context), 0 /* offset */,
			SLAB_HWCACHE_ALIGN, शून्य /* ctor */);
	अगर (!ntfs_index_ctx_cache) अणु
		pr_crit("Failed to create %s!\n", ntfs_index_ctx_cache_name);
		जाओ ictx_err_out;
	पूर्ण
	ntfs_attr_ctx_cache = kmem_cache_create(ntfs_attr_ctx_cache_name,
			माप(ntfs_attr_search_ctx), 0 /* offset */,
			SLAB_HWCACHE_ALIGN, शून्य /* ctor */);
	अगर (!ntfs_attr_ctx_cache) अणु
		pr_crit("NTFS: Failed to create %s!\n",
			ntfs_attr_ctx_cache_name);
		जाओ actx_err_out;
	पूर्ण

	ntfs_name_cache = kmem_cache_create(ntfs_name_cache_name,
			(NTFS_MAX_NAME_LEN+1) * माप(ntfsअक्षर), 0,
			SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ntfs_name_cache) अणु
		pr_crit("Failed to create %s!\n", ntfs_name_cache_name);
		जाओ name_err_out;
	पूर्ण

	ntfs_inode_cache = kmem_cache_create(ntfs_inode_cache_name,
			माप(ntfs_inode), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD, शून्य);
	अगर (!ntfs_inode_cache) अणु
		pr_crit("Failed to create %s!\n", ntfs_inode_cache_name);
		जाओ inode_err_out;
	पूर्ण

	ntfs_big_inode_cache = kmem_cache_create(ntfs_big_inode_cache_name,
			माप(big_ntfs_inode), 0,
			SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
			SLAB_ACCOUNT, ntfs_big_inode_init_once);
	अगर (!ntfs_big_inode_cache) अणु
		pr_crit("Failed to create %s!\n", ntfs_big_inode_cache_name);
		जाओ big_inode_err_out;
	पूर्ण

	/* Register the ntfs sysctls. */
	err = ntfs_sysctl(1);
	अगर (err) अणु
		pr_crit("Failed to register NTFS sysctls!\n");
		जाओ sysctl_err_out;
	पूर्ण

	err = रेजिस्टर_fileप्रणाली(&ntfs_fs_type);
	अगर (!err) अणु
		ntfs_debug("NTFS driver registered successfully.");
		वापस 0; /* Success! */
	पूर्ण
	pr_crit("Failed to register NTFS filesystem driver!\n");

	/* Unरेजिस्टर the ntfs sysctls. */
	ntfs_sysctl(0);
sysctl_err_out:
	kmem_cache_destroy(ntfs_big_inode_cache);
big_inode_err_out:
	kmem_cache_destroy(ntfs_inode_cache);
inode_err_out:
	kmem_cache_destroy(ntfs_name_cache);
name_err_out:
	kmem_cache_destroy(ntfs_attr_ctx_cache);
actx_err_out:
	kmem_cache_destroy(ntfs_index_ctx_cache);
ictx_err_out:
	अगर (!err) अणु
		pr_crit("Aborting NTFS filesystem driver registration...\n");
		err = -ENOMEM;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_ntfs_fs(व्योम)
अणु
	ntfs_debug("Unregistering NTFS driver.");

	unरेजिस्टर_fileप्रणाली(&ntfs_fs_type);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ntfs_big_inode_cache);
	kmem_cache_destroy(ntfs_inode_cache);
	kmem_cache_destroy(ntfs_name_cache);
	kmem_cache_destroy(ntfs_attr_ctx_cache);
	kmem_cache_destroy(ntfs_index_ctx_cache);
	/* Unरेजिस्टर the ntfs sysctls. */
	ntfs_sysctl(0);
पूर्ण

MODULE_AUTHOR("Anton Altaparmakov <anton@tuxera.com>");
MODULE_DESCRIPTION("NTFS 1.2/3.x driver - Copyright (c) 2001-2014 Anton Altaparmakov and Tuxera Inc.");
MODULE_VERSION(NTFS_VERSION);
MODULE_LICENSE("GPL");
#अगर_घोषित DEBUG
module_param(debug_msgs, bपूर्णांक, 0);
MODULE_PARM_DESC(debug_msgs, "Enable debug messages.");
#पूर्ण_अगर

module_init(init_ntfs_fs)
module_निकास(निकास_ntfs_fs)
