<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* MTD-based superblock management
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc. All Rights Reserved.
 * Copyright तऊ 2001-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Written by:  David Howells <dhowells@redhat.com>
 *              David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/mtd/super.h>
#समावेश <linux/namei.h>
#समावेश <linux/export.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/major.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fs_context.h>
#समावेश "mtdcore.h"

/*
 * compare superblocks to see अगर they're equivalent
 * - they are अगर the underlying MTD device is the same
 */
अटल पूर्णांक mtd_test_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा mtd_info *mtd = fc->sget_key;

	अगर (sb->s_mtd == fc->sget_key) अणु
		pr_debug("MTDSB: Match on device %d (\"%s\")\n",
			 mtd->index, mtd->name);
		वापस 1;
	पूर्ण

	pr_debug("MTDSB: No match, device %d (\"%s\"), device %d (\"%s\")\n",
		 sb->s_mtd->index, sb->s_mtd->name, mtd->index, mtd->name);
	वापस 0;
पूर्ण

/*
 * mark the superblock by the MTD device it is using
 * - set the device number to be the correct MTD block device क्रम pesuperstence
 *   of NFS exports
 */
अटल पूर्णांक mtd_set_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	sb->s_mtd = fc->sget_key;
	sb->s_dev = MKDEV(MTD_BLOCK_MAJOR, sb->s_mtd->index);
	sb->s_bdi = bdi_get(mtd_bdi);
	वापस 0;
पूर्ण

/*
 * get a superblock on an MTD-backed fileप्रणाली
 */
अटल पूर्णांक mtd_get_sb(काष्ठा fs_context *fc,
		      काष्ठा mtd_info *mtd,
		      पूर्णांक (*fill_super)(काष्ठा super_block *,
					काष्ठा fs_context *))
अणु
	काष्ठा super_block *sb;
	पूर्णांक ret;

	fc->sget_key = mtd;
	sb = sget_fc(fc, mtd_test_super, mtd_set_super);
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);

	अगर (sb->s_root) अणु
		/* new mountpoपूर्णांक क्रम an alपढ़ोy mounted superblock */
		pr_debug("MTDSB: Device %d (\"%s\") is already mounted\n",
			 mtd->index, mtd->name);
		put_mtd_device(mtd);
	पूर्ण अन्यथा अणु
		/* fresh new superblock */
		pr_debug("MTDSB: New superblock for device %d (\"%s\")\n",
			 mtd->index, mtd->name);

		ret = fill_super(sb, fc);
		अगर (ret < 0)
			जाओ error_sb;

		sb->s_flags |= SB_ACTIVE;
	पूर्ण

	BUG_ON(fc->root);
	fc->root = dget(sb->s_root);
	वापस 0;

error_sb:
	deactivate_locked_super(sb);
	वापस ret;
पूर्ण

/*
 * get a superblock on an MTD-backed fileप्रणाली by MTD device number
 */
अटल पूर्णांक mtd_get_sb_by_nr(काष्ठा fs_context *fc, पूर्णांक mtdnr,
			    पूर्णांक (*fill_super)(काष्ठा super_block *,
					      काष्ठा fs_context *))
अणु
	काष्ठा mtd_info *mtd;

	mtd = get_mtd_device(शून्य, mtdnr);
	अगर (IS_ERR(mtd)) अणु
		errorf(fc, "MTDSB: Device #%u doesn't appear to exist\n", mtdnr);
		वापस PTR_ERR(mtd);
	पूर्ण

	वापस mtd_get_sb(fc, mtd, fill_super);
पूर्ण

/**
 * get_tree_mtd - Get a superblock based on a single MTD device
 * @fc: The fileप्रणाली context holding the parameters
 * @fill_super: Helper to initialise a new superblock
 */
पूर्णांक get_tree_mtd(काष्ठा fs_context *fc,
	      पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				काष्ठा fs_context *fc))
अणु
#अगर_घोषित CONFIG_BLOCK
	dev_t dev;
	पूर्णांक ret;
#पूर्ण_अगर
	पूर्णांक mtdnr;

	अगर (!fc->source)
		वापस invalf(fc, "No source specified");

	pr_debug("MTDSB: dev_name \"%s\"\n", fc->source);

	/* the preferred way of mounting in future; especially when
	 * CONFIG_BLOCK=n - we specअगरy the underlying MTD device by number or
	 * by name, so that we करोn't require block device support to be present
	 * in the kernel.
	 */
	अगर (fc->source[0] == 'm' &&
	    fc->source[1] == 't' &&
	    fc->source[2] == 'd') अणु
		अगर (fc->source[3] == ':') अणु
			काष्ठा mtd_info *mtd;

			/* mount by MTD device name */
			pr_debug("MTDSB: mtd:%%s, name \"%s\"\n",
				 fc->source + 4);

			mtd = get_mtd_device_nm(fc->source + 4);
			अगर (!IS_ERR(mtd))
				वापस mtd_get_sb(fc, mtd, fill_super);

			errorf(fc, "MTD: MTD device with name \"%s\" not found",
			       fc->source + 4);

		पूर्ण अन्यथा अगर (है_अंक(fc->source[3])) अणु
			/* mount by MTD device number name */
			अक्षर *endptr;

			mtdnr = simple_म_से_अदीर्घ(fc->source + 3, &endptr, 0);
			अगर (!*endptr) अणु
				/* It was a valid number */
				pr_debug("MTDSB: mtd%%d, mtdnr %d\n", mtdnr);
				वापस mtd_get_sb_by_nr(fc, mtdnr, fill_super);
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_BLOCK
	/* try the old way - the hack where we allowed users to mount
	 * /dev/mtdblock$(n) but didn't actually _use_ the blockdev
	 */
	ret = lookup_bdev(fc->source, &dev);
	अगर (ret) अणु
		errorf(fc, "MTD: Couldn't look up '%s': %d", fc->source, ret);
		वापस ret;
	पूर्ण
	pr_debug("MTDSB: lookup_bdev() returned 0\n");

	अगर (MAJOR(dev) == MTD_BLOCK_MAJOR)
		वापस mtd_get_sb_by_nr(fc, MINOR(dev), fill_super);

#पूर्ण_अगर /* CONFIG_BLOCK */

	अगर (!(fc->sb_flags & SB_SILENT))
		errorf(fc, "MTD: Attempt to mount non-MTD device \"%s\"",
		       fc->source);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(get_tree_mtd);

/*
 * destroy an MTD-based superblock
 */
व्योम समाप्त_mtd_super(काष्ठा super_block *sb)
अणु
	generic_shutकरोwn_super(sb);
	put_mtd_device(sb->s_mtd);
	sb->s_mtd = शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(समाप्त_mtd_super);
