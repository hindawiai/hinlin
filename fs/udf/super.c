<शैली गुरु>
/*
 * super.c
 *
 * PURPOSE
 *  Super block routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * DESCRIPTION
 *  OSTA-UDF(पंचांग) = Optical Storage Technology Association
 *  Universal Disk Format.
 *
 *  This code is based on version 2.00 of the UDF specअगरication,
 *  and revision 3 of the ECMA 167 standard [equivalent to ISO 13346].
 *    http://www.osta.org/
 *    https://www.ecma.ch/
 *    https://www.iso.org/
 *
 * COPYRIGHT
 *  This file is distributed under the terms of the GNU General Public
 *  License (GPL). Copies of the GPL can be obtained from:
 *    ftp://prep.ai.mit.edu/pub/gnu/GPL
 *  Each contributing author retains all rights to their own work.
 *
 *  (C) 1998 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 2000 Stelias Computing Inc
 *
 * HISTORY
 *
 *  09/24/98 dgb  changed to allow compiling outside of kernel, and
 *                added some debugging.
 *  10/01/98 dgb  updated to allow (some) possibility of compiling w/2.0.34
 *  10/16/98      attempting some multi-session support
 *  10/17/98      added मुक्तspace count क्रम "df"
 *  11/11/98 gr   added novrs option
 *  11/26/98 dgb  added fileset,anchor mount options
 *  12/06/98 blf  really hosed things royally. vat/sparing support. sequenced
 *                vol descs. rewrote option handling based on isofs
 *  12/20/98      find the मुक्त space biपंचांगap (अगर it exists)
 */

#समावेश "udfdecl.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/cdrom.h>
#समावेश <linux/nls.h>
#समावेश <linux/vfs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "udf_sb.h"
#समावेश "udf_i.h"

#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>

क्रमागत अणु
	VDS_POS_PRIMARY_VOL_DESC,
	VDS_POS_UNALLOC_SPACE_DESC,
	VDS_POS_LOGICAL_VOL_DESC,
	VDS_POS_IMP_USE_VOL_DESC,
	VDS_POS_LENGTH
पूर्ण;

#घोषणा VSD_FIRST_SECTOR_OFFSET		32768
#घोषणा VSD_MAX_SECTOR_OFFSET		0x800000

/*
 * Maximum number of Terminating Descriptor / Logical Volume Integrity
 * Descriptor redirections. The chosen numbers are arbitrary - just that we
 * hopefully करोn't limit any real use of rewritten inode on ग_लिखो-once media
 * but aव्योम looping क्रम too दीर्घ on corrupted media.
 */
#घोषणा UDF_MAX_TD_NESTING 64
#घोषणा UDF_MAX_LVID_NESTING 1000

क्रमागत अणु UDF_MAX_LINKS = 0xffff पूर्ण;

/* These are the "meat" - everything अन्यथा is stuffing */
अटल पूर्णांक udf_fill_super(काष्ठा super_block *, व्योम *, पूर्णांक);
अटल व्योम udf_put_super(काष्ठा super_block *);
अटल पूर्णांक udf_sync_fs(काष्ठा super_block *, पूर्णांक);
अटल पूर्णांक udf_remount_fs(काष्ठा super_block *, पूर्णांक *, अक्षर *);
अटल व्योम udf_load_logicalvolपूर्णांक(काष्ठा super_block *, काष्ठा kernel_extent_ad);
अटल व्योम udf_खोलो_lvid(काष्ठा super_block *);
अटल व्योम udf_बंद_lvid(काष्ठा super_block *);
अटल अचिन्हित पूर्णांक udf_count_मुक्त(काष्ठा super_block *);
अटल पूर्णांक udf_statfs(काष्ठा dentry *, काष्ठा kstatfs *);
अटल पूर्णांक udf_show_options(काष्ठा seq_file *, काष्ठा dentry *);

काष्ठा logicalVolIntegrityDescImpUse *udf_sb_lvidiu(काष्ठा super_block *sb)
अणु
	काष्ठा logicalVolIntegrityDesc *lvid;
	अचिन्हित पूर्णांक partnum;
	अचिन्हित पूर्णांक offset;

	अगर (!UDF_SB(sb)->s_lvid_bh)
		वापस शून्य;
	lvid = (काष्ठा logicalVolIntegrityDesc *)UDF_SB(sb)->s_lvid_bh->b_data;
	partnum = le32_to_cpu(lvid->numOfPartitions);
	अगर ((sb->s_blocksize - माप(काष्ठा logicalVolIntegrityDescImpUse) -
	     दुरत्व(काष्ठा logicalVolIntegrityDesc, impUse)) /
	     (2 * माप(uपूर्णांक32_t)) < partnum) अणु
		udf_err(sb, "Logical volume integrity descriptor corrupted "
			"(numOfPartitions = %u)!\n", partnum);
		वापस शून्य;
	पूर्ण
	/* The offset is to skip मुक्तSpaceTable and sizeTable arrays */
	offset = partnum * 2 * माप(uपूर्णांक32_t);
	वापस (काष्ठा logicalVolIntegrityDescImpUse *)&(lvid->impUse[offset]);
पूर्ण

/* UDF fileप्रणाली type */
अटल काष्ठा dentry *udf_mount(काष्ठा file_प्रणाली_type *fs_type,
		      पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, udf_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type udf_fstype = अणु
	.owner		= THIS_MODULE,
	.name		= "udf",
	.mount		= udf_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("udf");

अटल काष्ठा kmem_cache *udf_inode_cachep;

अटल काष्ठा inode *udf_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा udf_inode_info *ei;
	ei = kmem_cache_alloc(udf_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;

	ei->i_unique = 0;
	ei->i_lenExtents = 0;
	ei->i_lenStreams = 0;
	ei->i_next_alloc_block = 0;
	ei->i_next_alloc_goal = 0;
	ei->i_strat4096 = 0;
	ei->i_streamdir = 0;
	init_rwsem(&ei->i_data_sem);
	ei->cached_extent.lstart = -1;
	spin_lock_init(&ei->i_extent_cache_lock);

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम udf_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(udf_inode_cachep, UDF_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा udf_inode_info *ei = (काष्ठा udf_inode_info *)foo;

	ei->i_data = शून्य;
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	udf_inode_cachep = kmem_cache_create("udf_inode_cache",
					     माप(काष्ठा udf_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT |
						 SLAB_MEM_SPREAD |
						 SLAB_ACCOUNT),
					     init_once);
	अगर (!udf_inode_cachep)
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
	kmem_cache_destroy(udf_inode_cachep);
पूर्ण

/* Superblock operations */
अटल स्थिर काष्ठा super_operations udf_sb_ops = अणु
	.alloc_inode	= udf_alloc_inode,
	.मुक्त_inode	= udf_मुक्त_in_core_inode,
	.ग_लिखो_inode	= udf_ग_लिखो_inode,
	.evict_inode	= udf_evict_inode,
	.put_super	= udf_put_super,
	.sync_fs	= udf_sync_fs,
	.statfs		= udf_statfs,
	.remount_fs	= udf_remount_fs,
	.show_options	= udf_show_options,
पूर्ण;

काष्ठा udf_options अणु
	अचिन्हित अक्षर novrs;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक session;
	अचिन्हित पूर्णांक lastblock;
	अचिन्हित पूर्णांक anchor;
	अचिन्हित पूर्णांक flags;
	umode_t umask;
	kgid_t gid;
	kuid_t uid;
	umode_t भ_शेषe;
	umode_t dmode;
	काष्ठा nls_table *nls_map;
पूर्ण;

अटल पूर्णांक __init init_udf_fs(व्योम)
अणु
	पूर्णांक err;

	err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&udf_fstype);
	अगर (err)
		जाओ out;

	वापस 0;

out:
	destroy_inodecache();

out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_udf_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&udf_fstype);
	destroy_inodecache();
पूर्ण

अटल पूर्णांक udf_sb_alloc_partition_maps(काष्ठा super_block *sb, u32 count)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);

	sbi->s_parपंचांगaps = kसुस्मृति(count, माप(*sbi->s_parपंचांगaps), GFP_KERNEL);
	अगर (!sbi->s_parपंचांगaps) अणु
		sbi->s_partitions = 0;
		वापस -ENOMEM;
	पूर्ण

	sbi->s_partitions = count;
	वापस 0;
पूर्ण

अटल व्योम udf_sb_मुक्त_biपंचांगap(काष्ठा udf_biपंचांगap *biपंचांगap)
अणु
	पूर्णांक i;
	पूर्णांक nr_groups = biपंचांगap->s_nr_groups;

	क्रम (i = 0; i < nr_groups; i++)
		brअन्यथा(biपंचांगap->s_block_biपंचांगap[i]);

	kvमुक्त(biपंचांगap);
पूर्ण

अटल व्योम udf_मुक्त_partition(काष्ठा udf_part_map *map)
अणु
	पूर्णांक i;
	काष्ठा udf_meta_data *mdata;

	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		iput(map->s_uspace.s_table);
	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		udf_sb_मुक्त_biपंचांगap(map->s_uspace.s_biपंचांगap);
	अगर (map->s_partition_type == UDF_SPARABLE_MAP15)
		क्रम (i = 0; i < 4; i++)
			brअन्यथा(map->s_type_specअगरic.s_sparing.s_spar_map[i]);
	अन्यथा अगर (map->s_partition_type == UDF_METADATA_MAP25) अणु
		mdata = &map->s_type_specअगरic.s_metadata;
		iput(mdata->s_metadata_fe);
		mdata->s_metadata_fe = शून्य;

		iput(mdata->s_mirror_fe);
		mdata->s_mirror_fe = शून्य;

		iput(mdata->s_biपंचांगap_fe);
		mdata->s_biपंचांगap_fe = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udf_sb_मुक्त_partitions(काष्ठा super_block *sb)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक i;

	अगर (!sbi->s_parपंचांगaps)
		वापस;
	क्रम (i = 0; i < sbi->s_partitions; i++)
		udf_मुक्त_partition(&sbi->s_parपंचांगaps[i]);
	kमुक्त(sbi->s_parपंचांगaps);
	sbi->s_parपंचांगaps = शून्य;
पूर्ण

अटल पूर्णांक udf_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);

	अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_STRICT))
		seq_माला_दो(seq, ",nostrict");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_BLOCKSIZE_SET))
		seq_म_लिखो(seq, ",bs=%lu", sb->s_blocksize);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UNHIDE))
		seq_माला_दो(seq, ",unhide");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UNDELETE))
		seq_माला_दो(seq, ",undelete");
	अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_USE_AD_IN_ICB))
		seq_माला_दो(seq, ",noadinicb");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_USE_SHORT_AD))
		seq_माला_दो(seq, ",shortad");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UID_FORGET))
		seq_माला_दो(seq, ",uid=forget");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_GID_FORGET))
		seq_माला_दो(seq, ",gid=forget");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UID_SET))
		seq_म_लिखो(seq, ",uid=%u", from_kuid(&init_user_ns, sbi->s_uid));
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_GID_SET))
		seq_म_लिखो(seq, ",gid=%u", from_kgid(&init_user_ns, sbi->s_gid));
	अगर (sbi->s_umask != 0)
		seq_म_लिखो(seq, ",umask=%ho", sbi->s_umask);
	अगर (sbi->s_भ_शेषe != UDF_INVALID_MODE)
		seq_म_लिखो(seq, ",mode=%ho", sbi->s_भ_शेषe);
	अगर (sbi->s_dmode != UDF_INVALID_MODE)
		seq_म_लिखो(seq, ",dmode=%ho", sbi->s_dmode);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_SESSION_SET))
		seq_म_लिखो(seq, ",session=%d", sbi->s_session);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_LASTBLOCK_SET))
		seq_म_लिखो(seq, ",lastblock=%u", sbi->s_last_block);
	अगर (sbi->s_anchor != 0)
		seq_म_लिखो(seq, ",anchor=%u", sbi->s_anchor);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UTF8))
		seq_माला_दो(seq, ",utf8");
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP) && sbi->s_nls_map)
		seq_म_लिखो(seq, ",iocharset=%s", sbi->s_nls_map->अक्षरset);

	वापस 0;
पूर्ण

/*
 * udf_parse_options
 *
 * PURPOSE
 *	Parse mount options.
 *
 * DESCRIPTION
 *	The following mount options are supported:
 *
 *	gid=		Set the शेष group.
 *	umask=		Set the शेष umask.
 *	mode=		Set the शेष file permissions.
 *	dmode=		Set the शेष directory permissions.
 *	uid=		Set the शेष user.
 *	bs=		Set the block size.
 *	unhide		Show otherwise hidden files.
 *	undelete	Show deleted files in lists.
 *	adinicb		Embed data in the inode (शेष)
 *	noadinicb	Don't embed data in the inode
 *	लघुad		Use लघु ad's
 *	दीर्घad		Use दीर्घ ad's (शेष)
 *	nostrict	Unset strict conक्रमmance
 *	ioअक्षरset=	Set the NLS अक्षरacter set
 *
 *	The reमुख्यing are क्रम debugging and disaster recovery:
 *
 *	novrs		Skip volume sequence recognition
 *
 *	The following expect a offset from 0.
 *
 *	session=	Set the CDROM session (शेष= last session)
 *	anchor=		Override standard anchor location. (शेष= 256)
 *	volume=		Override the VolumeDesc location. (unused)
 *	partition=	Override the PartitionDesc location. (unused)
 *	lastblock=	Set the last block of the fileप्रणाली/
 *
 *	The following expect a offset from the partition root.
 *
 *	fileset=	Override the fileset block location. (unused)
 *	rootdir=	Override the root directory location. (unused)
 *		WARNING: overriding the rootdir to a non-directory may
 *		yield highly unpredictable results.
 *
 * PRE-CONDITIONS
 *	options		Poपूर्णांकer to mount options string.
 *	uopts		Poपूर्णांकer to mount options variable.
 *
 * POST-CONDITIONS
 *	<वापस>	1	Mount options parsed okay.
 *	<वापस>	0	Error parsing mount options.
 *
 * HISTORY
 *	July 1, 1997 - Andrew E. Mileski
 *	Written, tested, and released.
 */

क्रमागत अणु
	Opt_novrs, Opt_nostrict, Opt_bs, Opt_unhide, Opt_undelete,
	Opt_noadinicb, Opt_adinicb, Opt_लघुad, Opt_दीर्घad,
	Opt_gid, Opt_uid, Opt_umask, Opt_session, Opt_lastblock,
	Opt_anchor, Opt_volume, Opt_partition, Opt_fileset,
	Opt_rootdir, Opt_utf8, Opt_ioअक्षरset,
	Opt_err, Opt_uक्रमget, Opt_uignore, Opt_gक्रमget, Opt_gignore,
	Opt_भ_शेषe, Opt_dmode
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_novrs,	"novrs"पूर्ण,
	अणुOpt_nostrict,	"nostrict"पूर्ण,
	अणुOpt_bs,	"bs=%u"पूर्ण,
	अणुOpt_unhide,	"unhide"पूर्ण,
	अणुOpt_undelete,	"undelete"पूर्ण,
	अणुOpt_noadinicb,	"noadinicb"पूर्ण,
	अणुOpt_adinicb,	"adinicb"पूर्ण,
	अणुOpt_लघुad,	"shortad"पूर्ण,
	अणुOpt_दीर्घad,	"longad"पूर्ण,
	अणुOpt_uक्रमget,	"uid=forget"पूर्ण,
	अणुOpt_uignore,	"uid=ignore"पूर्ण,
	अणुOpt_gक्रमget,	"gid=forget"पूर्ण,
	अणुOpt_gignore,	"gid=ignore"पूर्ण,
	अणुOpt_gid,	"gid=%u"पूर्ण,
	अणुOpt_uid,	"uid=%u"पूर्ण,
	अणुOpt_umask,	"umask=%o"पूर्ण,
	अणुOpt_session,	"session=%u"पूर्ण,
	अणुOpt_lastblock,	"lastblock=%u"पूर्ण,
	अणुOpt_anchor,	"anchor=%u"पूर्ण,
	अणुOpt_volume,	"volume=%u"पूर्ण,
	अणुOpt_partition,	"partition=%u"पूर्ण,
	अणुOpt_fileset,	"fileset=%u"पूर्ण,
	अणुOpt_rootdir,	"rootdir=%u"पूर्ण,
	अणुOpt_utf8,	"utf8"पूर्ण,
	अणुOpt_ioअक्षरset,	"iocharset=%s"पूर्ण,
	अणुOpt_भ_शेषe,     "mode=%o"पूर्ण,
	अणुOpt_dmode,     "dmode=%o"पूर्ण,
	अणुOpt_err,	शून्यपूर्ण
पूर्ण;

अटल पूर्णांक udf_parse_options(अक्षर *options, काष्ठा udf_options *uopt,
			     bool remount)
अणु
	अक्षर *p;
	पूर्णांक option;
	अचिन्हित पूर्णांक uv;

	uopt->novrs = 0;
	uopt->session = 0xFFFFFFFF;
	uopt->lastblock = 0;
	uopt->anchor = 0;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अचिन्हित n;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_novrs:
			uopt->novrs = 1;
			अवरोध;
		हाल Opt_bs:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			n = option;
			अगर (n != 512 && n != 1024 && n != 2048 && n != 4096)
				वापस 0;
			uopt->blocksize = n;
			uopt->flags |= (1 << UDF_FLAG_BLOCKSIZE_SET);
			अवरोध;
		हाल Opt_unhide:
			uopt->flags |= (1 << UDF_FLAG_UNHIDE);
			अवरोध;
		हाल Opt_undelete:
			uopt->flags |= (1 << UDF_FLAG_UNDELETE);
			अवरोध;
		हाल Opt_noadinicb:
			uopt->flags &= ~(1 << UDF_FLAG_USE_AD_IN_ICB);
			अवरोध;
		हाल Opt_adinicb:
			uopt->flags |= (1 << UDF_FLAG_USE_AD_IN_ICB);
			अवरोध;
		हाल Opt_लघुad:
			uopt->flags |= (1 << UDF_FLAG_USE_SHORT_AD);
			अवरोध;
		हाल Opt_दीर्घad:
			uopt->flags &= ~(1 << UDF_FLAG_USE_SHORT_AD);
			अवरोध;
		हाल Opt_gid:
			अगर (match_uपूर्णांक(args, &uv))
				वापस 0;
			uopt->gid = make_kgid(current_user_ns(), uv);
			अगर (!gid_valid(uopt->gid))
				वापस 0;
			uopt->flags |= (1 << UDF_FLAG_GID_SET);
			अवरोध;
		हाल Opt_uid:
			अगर (match_uपूर्णांक(args, &uv))
				वापस 0;
			uopt->uid = make_kuid(current_user_ns(), uv);
			अगर (!uid_valid(uopt->uid))
				वापस 0;
			uopt->flags |= (1 << UDF_FLAG_UID_SET);
			अवरोध;
		हाल Opt_umask:
			अगर (match_octal(args, &option))
				वापस 0;
			uopt->umask = option;
			अवरोध;
		हाल Opt_nostrict:
			uopt->flags &= ~(1 << UDF_FLAG_STRICT);
			अवरोध;
		हाल Opt_session:
			अगर (match_पूर्णांक(args, &option))
				वापस 0;
			uopt->session = option;
			अगर (!remount)
				uopt->flags |= (1 << UDF_FLAG_SESSION_SET);
			अवरोध;
		हाल Opt_lastblock:
			अगर (match_पूर्णांक(args, &option))
				वापस 0;
			uopt->lastblock = option;
			अगर (!remount)
				uopt->flags |= (1 << UDF_FLAG_LASTBLOCK_SET);
			अवरोध;
		हाल Opt_anchor:
			अगर (match_पूर्णांक(args, &option))
				वापस 0;
			uopt->anchor = option;
			अवरोध;
		हाल Opt_volume:
		हाल Opt_partition:
		हाल Opt_fileset:
		हाल Opt_rootdir:
			/* Ignored (never implemented properly) */
			अवरोध;
		हाल Opt_utf8:
			uopt->flags |= (1 << UDF_FLAG_UTF8);
			अवरोध;
		हाल Opt_ioअक्षरset:
			अगर (!remount) अणु
				अगर (uopt->nls_map)
					unload_nls(uopt->nls_map);
				/*
				 * load_nls() failure is handled later in
				 * udf_fill_super() after all options are
				 * parsed.
				 */
				uopt->nls_map = load_nls(args[0].from);
				uopt->flags |= (1 << UDF_FLAG_NLS_MAP);
			पूर्ण
			अवरोध;
		हाल Opt_uक्रमget:
			uopt->flags |= (1 << UDF_FLAG_UID_FORGET);
			अवरोध;
		हाल Opt_uignore:
		हाल Opt_gignore:
			/* These options are superseeded by uid=<number> */
			अवरोध;
		हाल Opt_gक्रमget:
			uopt->flags |= (1 << UDF_FLAG_GID_FORGET);
			अवरोध;
		हाल Opt_भ_शेषe:
			अगर (match_octal(args, &option))
				वापस 0;
			uopt->भ_शेषe = option & 0777;
			अवरोध;
		हाल Opt_dmode:
			अगर (match_octal(args, &option))
				वापस 0;
			uopt->dmode = option & 0777;
			अवरोध;
		शेष:
			pr_err("bad mount option \"%s\" or missing value\n", p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक udf_remount_fs(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *options)
अणु
	काष्ठा udf_options uopt;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक error = 0;

	अगर (!(*flags & SB_RDONLY) && UDF_QUERY_FLAG(sb, UDF_FLAG_RW_INCOMPAT))
		वापस -EACCES;

	sync_fileप्रणाली(sb);

	uopt.flags = sbi->s_flags;
	uopt.uid   = sbi->s_uid;
	uopt.gid   = sbi->s_gid;
	uopt.umask = sbi->s_umask;
	uopt.भ_शेषe = sbi->s_भ_शेषe;
	uopt.dmode = sbi->s_dmode;
	uopt.nls_map = शून्य;

	अगर (!udf_parse_options(options, &uopt, true))
		वापस -EINVAL;

	ग_लिखो_lock(&sbi->s_cred_lock);
	sbi->s_flags = uopt.flags;
	sbi->s_uid   = uopt.uid;
	sbi->s_gid   = uopt.gid;
	sbi->s_umask = uopt.umask;
	sbi->s_भ_शेषe = uopt.भ_शेषe;
	sbi->s_dmode = uopt.dmode;
	ग_लिखो_unlock(&sbi->s_cred_lock);

	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		जाओ out_unlock;

	अगर (*flags & SB_RDONLY)
		udf_बंद_lvid(sb);
	अन्यथा
		udf_खोलो_lvid(sb);

out_unlock:
	वापस error;
पूर्ण

/*
 * Check VSD descriptor. Returns -1 in हाल we are at the end of volume
 * recognition area, 0 अगर the descriptor is valid but non-पूर्णांकeresting, 1 अगर
 * we found one of NSR descriptors we are looking क्रम.
 */
अटल पूर्णांक identअगरy_vsd(स्थिर काष्ठा volStructDesc *vsd)
अणु
	पूर्णांक ret = 0;

	अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_CD001, VSD_STD_ID_LEN)) अणु
		चयन (vsd->काष्ठाType) अणु
		हाल 0:
			udf_debug("ISO9660 Boot Record found\n");
			अवरोध;
		हाल 1:
			udf_debug("ISO9660 Primary Volume Descriptor found\n");
			अवरोध;
		हाल 2:
			udf_debug("ISO9660 Supplementary Volume Descriptor found\n");
			अवरोध;
		हाल 3:
			udf_debug("ISO9660 Volume Partition Descriptor found\n");
			अवरोध;
		हाल 255:
			udf_debug("ISO9660 Volume Descriptor Set Terminator found\n");
			अवरोध;
		शेष:
			udf_debug("ISO9660 VRS (%u) found\n", vsd->काष्ठाType);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_BEA01, VSD_STD_ID_LEN))
		; /* ret = 0 */
	अन्यथा अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_NSR02, VSD_STD_ID_LEN))
		ret = 1;
	अन्यथा अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_NSR03, VSD_STD_ID_LEN))
		ret = 1;
	अन्यथा अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_BOOT2, VSD_STD_ID_LEN))
		; /* ret = 0 */
	अन्यथा अगर (!स_भेद(vsd->stdIdent, VSD_STD_ID_CDW02, VSD_STD_ID_LEN))
		; /* ret = 0 */
	अन्यथा अणु
		/* TEA01 or invalid id : end of volume recognition area */
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Check Volume Structure Descriptors (ECMA 167 2/9.1)
 * We also check any "CD-ROM Volume Descriptor Set" (ECMA 167 2/8.3.1)
 * @वापस   1 अगर NSR02 or NSR03 found,
 *	    -1 अगर first sector पढ़ो error, 0 otherwise
 */
अटल पूर्णांक udf_check_vsd(काष्ठा super_block *sb)
अणु
	काष्ठा volStructDesc *vsd = शून्य;
	loff_t sector = VSD_FIRST_SECTOR_OFFSET;
	पूर्णांक sectorsize;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक nsr = 0;
	काष्ठा udf_sb_info *sbi;
	loff_t session_offset;

	sbi = UDF_SB(sb);
	अगर (sb->s_blocksize < माप(काष्ठा volStructDesc))
		sectorsize = माप(काष्ठा volStructDesc);
	अन्यथा
		sectorsize = sb->s_blocksize;

	session_offset = (loff_t)sbi->s_session << sb->s_blocksize_bits;
	sector += session_offset;

	udf_debug("Starting at sector %u (%lu byte sectors)\n",
		  (अचिन्हित पूर्णांक)(sector >> sb->s_blocksize_bits),
		  sb->s_blocksize);
	/* Process the sequence (अगर applicable). The hard limit on the sector
	 * offset is arbitrary, hopefully large enough so that all valid UDF
	 * fileप्रणालीs will be recognised. There is no mention of an upper
	 * bound to the size of the volume recognition area in the standard.
	 *  The limit will prevent the code to पढ़ो all the sectors of a
	 * specially crafted image (like a bluray disc full of CD001 sectors),
	 * potentially causing minutes or even hours of unपूर्णांकerruptible I/O
	 * activity. This actually happened with uninitialised SSD partitions
	 * (all 0xFF) beक्रमe the check क्रम the limit and all valid IDs were
	 * added */
	क्रम (; !nsr && sector < VSD_MAX_SECTOR_OFFSET; sector += sectorsize) अणु
		/* Read a block */
		bh = udf_tपढ़ो(sb, sector >> sb->s_blocksize_bits);
		अगर (!bh)
			अवरोध;

		vsd = (काष्ठा volStructDesc *)(bh->b_data +
					      (sector & (sb->s_blocksize - 1)));
		nsr = identअगरy_vsd(vsd);
		/* Found NSR or end? */
		अगर (nsr) अणु
			brअन्यथा(bh);
			अवरोध;
		पूर्ण
		/*
		 * Special handling क्रम improperly क्रमmatted VRS (e.g., Win10)
		 * where components are separated by 2048 bytes even though
		 * sectors are 4K
		 */
		अगर (sb->s_blocksize == 4096) अणु
			nsr = identअगरy_vsd(vsd + 1);
			/* Ignore unknown IDs... */
			अगर (nsr < 0)
				nsr = 0;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण

	अगर (nsr > 0)
		वापस 1;
	अन्यथा अगर (!bh && sector - session_offset == VSD_FIRST_SECTOR_OFFSET)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक udf_verअगरy_करोमुख्य_identअगरier(काष्ठा super_block *sb,
					काष्ठा regid *ident, अक्षर *dname)
अणु
	काष्ठा करोमुख्यIdentSuffix *suffix;

	अगर (स_भेद(ident->ident, UDF_ID_COMPLIANT, म_माप(UDF_ID_COMPLIANT))) अणु
		udf_warn(sb, "Not OSTA UDF compliant %s descriptor.\n", dname);
		जाओ क्रमce_ro;
	पूर्ण
	अगर (ident->flags & ENTITYID_FLAGS_सूचीTY) अणु
		udf_warn(sb, "Possibly not OSTA UDF compliant %s descriptor.\n",
			 dname);
		जाओ क्रमce_ro;
	पूर्ण
	suffix = (काष्ठा करोमुख्यIdentSuffix *)ident->identSuffix;
	अगर ((suffix->करोमुख्यFlags & DOMAIN_FLAGS_HARD_WRITE_PROTECT) ||
	    (suffix->करोमुख्यFlags & DOMAIN_FLAGS_SOFT_WRITE_PROTECT)) अणु
		अगर (!sb_rकरोnly(sb)) अणु
			udf_warn(sb, "Descriptor for %s marked write protected."
				 " Forcing read only mount.\n", dname);
		पूर्ण
		जाओ क्रमce_ro;
	पूर्ण
	वापस 0;

क्रमce_ro:
	अगर (!sb_rकरोnly(sb))
		वापस -EACCES;
	UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
	वापस 0;
पूर्ण

अटल पूर्णांक udf_load_fileset(काष्ठा super_block *sb, काष्ठा fileSetDesc *fset,
			    काष्ठा kernel_lb_addr *root)
अणु
	पूर्णांक ret;

	ret = udf_verअगरy_करोमुख्य_identअगरier(sb, &fset->करोमुख्यIdent, "file set");
	अगर (ret < 0)
		वापस ret;

	*root = lelb_to_cpu(fset->rootDirectoryICB.extLocation);
	UDF_SB(sb)->s_serial_number = le16_to_cpu(fset->descTag.tagSerialNum);

	udf_debug("Rootdir at block=%u, partition=%u\n",
		  root->logicalBlockNum, root->partitionReferenceNum);
	वापस 0;
पूर्ण

अटल पूर्णांक udf_find_fileset(काष्ठा super_block *sb,
			    काष्ठा kernel_lb_addr *fileset,
			    काष्ठा kernel_lb_addr *root)
अणु
	काष्ठा buffer_head *bh = शून्य;
	uपूर्णांक16_t ident;
	पूर्णांक ret;

	अगर (fileset->logicalBlockNum == 0xFFFFFFFF &&
	    fileset->partitionReferenceNum == 0xFFFF)
		वापस -EINVAL;

	bh = udf_पढ़ो_ptagged(sb, fileset, 0, &ident);
	अगर (!bh)
		वापस -EIO;
	अगर (ident != TAG_IDENT_FSD) अणु
		brअन्यथा(bh);
		वापस -EINVAL;
	पूर्ण

	udf_debug("Fileset at block=%u, partition=%u\n",
		  fileset->logicalBlockNum, fileset->partitionReferenceNum);

	UDF_SB(sb)->s_partition = fileset->partitionReferenceNum;
	ret = udf_load_fileset(sb, (काष्ठा fileSetDesc *)bh->b_data, root);
	brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * Load primary Volume Descriptor Sequence
 *
 * Return <0 on error, 0 on success. -EAGAIN is special meaning next sequence
 * should be tried.
 */
अटल पूर्णांक udf_load_pvoldesc(काष्ठा super_block *sb, sector_t block)
अणु
	काष्ठा primaryVolDesc *pvoldesc;
	uपूर्णांक8_t *outstr;
	काष्ठा buffer_head *bh;
	uपूर्णांक16_t ident;
	पूर्णांक ret;
	काष्ठा बारtamp *ts;

	outstr = kदो_स्मृति(128, GFP_NOFS);
	अगर (!outstr)
		वापस -ENOMEM;

	bh = udf_पढ़ो_tagged(sb, block, block, &ident);
	अगर (!bh) अणु
		ret = -EAGAIN;
		जाओ out2;
	पूर्ण

	अगर (ident != TAG_IDENT_PVD) अणु
		ret = -EIO;
		जाओ out_bh;
	पूर्ण

	pvoldesc = (काष्ठा primaryVolDesc *)bh->b_data;

	udf_disk_stamp_to_समय(&UDF_SB(sb)->s_record_समय,
			      pvoldesc->recordingDateAndTime);
	ts = &pvoldesc->recordingDateAndTime;
	udf_debug("recording time %04u/%02u/%02u %02u:%02u (%x)\n",
		  le16_to_cpu(ts->year), ts->month, ts->day, ts->hour,
		  ts->minute, le16_to_cpu(ts->typeAndTimezone));

	ret = udf_dstrCS0toChar(sb, outstr, 31, pvoldesc->volIdent, 32);
	अगर (ret < 0) अणु
		म_नकल(UDF_SB(sb)->s_volume_ident, "InvalidName");
		pr_warn("incorrect volume identification, setting to "
			"'InvalidName'\n");
	पूर्ण अन्यथा अणु
		म_नकलन(UDF_SB(sb)->s_volume_ident, outstr, ret);
	पूर्ण
	udf_debug("volIdent[] = '%s'\n", UDF_SB(sb)->s_volume_ident);

	ret = udf_dstrCS0toChar(sb, outstr, 127, pvoldesc->volSetIdent, 128);
	अगर (ret < 0) अणु
		ret = 0;
		जाओ out_bh;
	पूर्ण
	outstr[ret] = 0;
	udf_debug("volSetIdent[] = '%s'\n", outstr);

	ret = 0;
out_bh:
	brअन्यथा(bh);
out2:
	kमुक्त(outstr);
	वापस ret;
पूर्ण

काष्ठा inode *udf_find_metadata_inode_efe(काष्ठा super_block *sb,
					u32 meta_file_loc, u32 partition_ref)
अणु
	काष्ठा kernel_lb_addr addr;
	काष्ठा inode *metadata_fe;

	addr.logicalBlockNum = meta_file_loc;
	addr.partitionReferenceNum = partition_ref;

	metadata_fe = udf_iget_special(sb, &addr);

	अगर (IS_ERR(metadata_fe)) अणु
		udf_warn(sb, "metadata inode efe not found\n");
		वापस metadata_fe;
	पूर्ण
	अगर (UDF_I(metadata_fe)->i_alloc_type != ICBTAG_FLAG_AD_SHORT) अणु
		udf_warn(sb, "metadata inode efe does not have short allocation descriptors!\n");
		iput(metadata_fe);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस metadata_fe;
पूर्ण

अटल पूर्णांक udf_load_metadata_files(काष्ठा super_block *sb, पूर्णांक partition,
				   पूर्णांक type1_index)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	काष्ठा udf_meta_data *mdata;
	काष्ठा kernel_lb_addr addr;
	काष्ठा inode *fe;

	map = &sbi->s_parपंचांगaps[partition];
	mdata = &map->s_type_specअगरic.s_metadata;
	mdata->s_phys_partition_ref = type1_index;

	/* metadata address */
	udf_debug("Metadata file location: block = %u part = %u\n",
		  mdata->s_meta_file_loc, mdata->s_phys_partition_ref);

	fe = udf_find_metadata_inode_efe(sb, mdata->s_meta_file_loc,
					 mdata->s_phys_partition_ref);
	अगर (IS_ERR(fe)) अणु
		/* mirror file entry */
		udf_debug("Mirror metadata file location: block = %u part = %u\n",
			  mdata->s_mirror_file_loc, mdata->s_phys_partition_ref);

		fe = udf_find_metadata_inode_efe(sb, mdata->s_mirror_file_loc,
						 mdata->s_phys_partition_ref);

		अगर (IS_ERR(fe)) अणु
			udf_err(sb, "Both metadata and mirror metadata inode efe can not found\n");
			वापस PTR_ERR(fe);
		पूर्ण
		mdata->s_mirror_fe = fe;
	पूर्ण अन्यथा
		mdata->s_metadata_fe = fe;


	/*
	 * biपंचांगap file entry
	 * Note:
	 * Load only अगर biपंचांगap file location dअगरfers from 0xFFFFFFFF (DCN-5102)
	*/
	अगर (mdata->s_biपंचांगap_file_loc != 0xFFFFFFFF) अणु
		addr.logicalBlockNum = mdata->s_biपंचांगap_file_loc;
		addr.partitionReferenceNum = mdata->s_phys_partition_ref;

		udf_debug("Bitmap file location: block = %u part = %u\n",
			  addr.logicalBlockNum, addr.partitionReferenceNum);

		fe = udf_iget_special(sb, &addr);
		अगर (IS_ERR(fe)) अणु
			अगर (sb_rकरोnly(sb))
				udf_warn(sb, "bitmap inode efe not found but it's ok since the disc is mounted read-only\n");
			अन्यथा अणु
				udf_err(sb, "bitmap inode efe not found and attempted read-write mount\n");
				वापस PTR_ERR(fe);
			पूर्ण
		पूर्ण अन्यथा
			mdata->s_biपंचांगap_fe = fe;
	पूर्ण

	udf_debug("udf_load_metadata_files Ok\n");
	वापस 0;
पूर्ण

पूर्णांक udf_compute_nr_groups(काष्ठा super_block *sb, u32 partition)
अणु
	काष्ठा udf_part_map *map = &UDF_SB(sb)->s_parपंचांगaps[partition];
	वापस DIV_ROUND_UP(map->s_partition_len +
			    (माप(काष्ठा spaceBiपंचांगapDesc) << 3),
			    sb->s_blocksize * 8);
पूर्ण

अटल काष्ठा udf_biपंचांगap *udf_sb_alloc_biपंचांगap(काष्ठा super_block *sb, u32 index)
अणु
	काष्ठा udf_biपंचांगap *biपंचांगap;
	पूर्णांक nr_groups = udf_compute_nr_groups(sb, index);

	biपंचांगap = kvzalloc(काष्ठा_size(biपंचांगap, s_block_biपंचांगap, nr_groups),
			  GFP_KERNEL);
	अगर (!biपंचांगap)
		वापस शून्य;

	biपंचांगap->s_nr_groups = nr_groups;
	वापस biपंचांगap;
पूर्ण

अटल पूर्णांक check_partition_desc(काष्ठा super_block *sb,
				काष्ठा partitionDesc *p,
				काष्ठा udf_part_map *map)
अणु
	bool umap, utable, fmap, ftable;
	काष्ठा partitionHeaderDesc *phd;

	चयन (le32_to_cpu(p->accessType)) अणु
	हाल PD_ACCESS_TYPE_READ_ONLY:
	हाल PD_ACCESS_TYPE_WRITE_ONCE:
	हाल PD_ACCESS_TYPE_NONE:
		जाओ क्रमce_ro;
	पूर्ण

	/* No Partition Header Descriptor? */
	अगर (म_भेद(p->partitionContents.ident, PD_PARTITION_CONTENTS_NSR02) &&
	    म_भेद(p->partitionContents.ident, PD_PARTITION_CONTENTS_NSR03))
		जाओ क्रमce_ro;

	phd = (काष्ठा partitionHeaderDesc *)p->partitionContentsUse;
	utable = phd->unallocSpaceTable.extLength;
	umap = phd->unallocSpaceBiपंचांगap.extLength;
	ftable = phd->मुक्तdSpaceTable.extLength;
	fmap = phd->मुक्तdSpaceBiपंचांगap.extLength;

	/* No allocation info? */
	अगर (!utable && !umap && !ftable && !fmap)
		जाओ क्रमce_ro;

	/* We करोn't support blocks that require erasing beक्रमe overग_लिखो */
	अगर (ftable || fmap)
		जाओ क्रमce_ro;
	/* UDF 2.60: 2.3.3 - no mixing of tables & biपंचांगaps, no VAT. */
	अगर (utable && umap)
		जाओ क्रमce_ro;

	अगर (map->s_partition_type == UDF_VIRTUAL_MAP15 ||
	    map->s_partition_type == UDF_VIRTUAL_MAP20 ||
	    map->s_partition_type == UDF_METADATA_MAP25)
		जाओ क्रमce_ro;

	वापस 0;
क्रमce_ro:
	अगर (!sb_rकरोnly(sb))
		वापस -EACCES;
	UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
	वापस 0;
पूर्ण

अटल पूर्णांक udf_fill_partdesc_info(काष्ठा super_block *sb,
		काष्ठा partitionDesc *p, पूर्णांक p_index)
अणु
	काष्ठा udf_part_map *map;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा partitionHeaderDesc *phd;
	पूर्णांक err;

	map = &sbi->s_parपंचांगaps[p_index];

	map->s_partition_len = le32_to_cpu(p->partitionLength); /* blocks */
	map->s_partition_root = le32_to_cpu(p->partitionStartingLocation);

	अगर (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_READ_ONLY))
		map->s_partition_flags |= UDF_PART_FLAG_READ_ONLY;
	अगर (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_WRITE_ONCE))
		map->s_partition_flags |= UDF_PART_FLAG_WRITE_ONCE;
	अगर (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_REWRITABLE))
		map->s_partition_flags |= UDF_PART_FLAG_REWRITABLE;
	अगर (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_OVERWRITABLE))
		map->s_partition_flags |= UDF_PART_FLAG_OVERWRITABLE;

	udf_debug("Partition (%d type %x) starts at physical %u, block length %u\n",
		  p_index, map->s_partition_type,
		  map->s_partition_root, map->s_partition_len);

	err = check_partition_desc(sb, p, map);
	अगर (err)
		वापस err;

	/*
	 * Skip loading allocation info it we cannot ever ग_लिखो to the fs.
	 * This is a correctness thing as we may have decided to क्रमce ro mount
	 * to aव्योम allocation info we करोn't support.
	 */
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_RW_INCOMPAT))
		वापस 0;

	phd = (काष्ठा partitionHeaderDesc *)p->partitionContentsUse;
	अगर (phd->unallocSpaceTable.extLength) अणु
		काष्ठा kernel_lb_addr loc = अणु
			.logicalBlockNum = le32_to_cpu(
				phd->unallocSpaceTable.extPosition),
			.partitionReferenceNum = p_index,
		पूर्ण;
		काष्ठा inode *inode;

		inode = udf_iget_special(sb, &loc);
		अगर (IS_ERR(inode)) अणु
			udf_debug("cannot load unallocSpaceTable (part %d)\n",
				  p_index);
			वापस PTR_ERR(inode);
		पूर्ण
		map->s_uspace.s_table = inode;
		map->s_partition_flags |= UDF_PART_FLAG_UNALLOC_TABLE;
		udf_debug("unallocSpaceTable (part %d) @ %lu\n",
			  p_index, map->s_uspace.s_table->i_ino);
	पूर्ण

	अगर (phd->unallocSpaceBiपंचांगap.extLength) अणु
		काष्ठा udf_biपंचांगap *biपंचांगap = udf_sb_alloc_biपंचांगap(sb, p_index);
		अगर (!biपंचांगap)
			वापस -ENOMEM;
		map->s_uspace.s_biपंचांगap = biपंचांगap;
		biपंचांगap->s_extPosition = le32_to_cpu(
				phd->unallocSpaceBiपंचांगap.extPosition);
		map->s_partition_flags |= UDF_PART_FLAG_UNALLOC_BITMAP;
		udf_debug("unallocSpaceBitmap (part %d) @ %u\n",
			  p_index, biपंचांगap->s_extPosition);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम udf_find_vat_block(काष्ठा super_block *sb, पूर्णांक p_index,
			       पूर्णांक type1_index, sector_t start_block)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map = &sbi->s_parपंचांगaps[p_index];
	sector_t vat_block;
	काष्ठा kernel_lb_addr ino;
	काष्ठा inode *inode;

	/*
	 * VAT file entry is in the last recorded block. Some broken disks have
	 * it a few blocks beक्रमe so try a bit harder...
	 */
	ino.partitionReferenceNum = type1_index;
	क्रम (vat_block = start_block;
	     vat_block >= map->s_partition_root &&
	     vat_block >= start_block - 3; vat_block--) अणु
		ino.logicalBlockNum = vat_block - map->s_partition_root;
		inode = udf_iget_special(sb, &ino);
		अगर (!IS_ERR(inode)) अणु
			sbi->s_vat_inode = inode;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक udf_load_vat(काष्ठा super_block *sb, पूर्णांक p_index, पूर्णांक type1_index)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map = &sbi->s_parपंचांगaps[p_index];
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा udf_inode_info *vati;
	uपूर्णांक32_t pos;
	काष्ठा भवAllocationTable20 *vat20;
	sector_t blocks = i_size_पढ़ो(sb->s_bdev->bd_inode) >>
			  sb->s_blocksize_bits;

	udf_find_vat_block(sb, p_index, type1_index, sbi->s_last_block);
	अगर (!sbi->s_vat_inode &&
	    sbi->s_last_block != blocks - 1) अणु
		pr_notice("Failed to read VAT inode from the last recorded block (%lu), retrying with the last block of the device (%lu).\n",
			  (अचिन्हित दीर्घ)sbi->s_last_block,
			  (अचिन्हित दीर्घ)blocks - 1);
		udf_find_vat_block(sb, p_index, type1_index, blocks - 1);
	पूर्ण
	अगर (!sbi->s_vat_inode)
		वापस -EIO;

	अगर (map->s_partition_type == UDF_VIRTUAL_MAP15) अणु
		map->s_type_specअगरic.s_भव.s_start_offset = 0;
		map->s_type_specअगरic.s_भव.s_num_entries =
			(sbi->s_vat_inode->i_size - 36) >> 2;
	पूर्ण अन्यथा अगर (map->s_partition_type == UDF_VIRTUAL_MAP20) अणु
		vati = UDF_I(sbi->s_vat_inode);
		अगर (vati->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
			pos = udf_block_map(sbi->s_vat_inode, 0);
			bh = sb_bपढ़ो(sb, pos);
			अगर (!bh)
				वापस -EIO;
			vat20 = (काष्ठा भवAllocationTable20 *)bh->b_data;
		पूर्ण अन्यथा अणु
			vat20 = (काष्ठा भवAllocationTable20 *)
							vati->i_data;
		पूर्ण

		map->s_type_specअगरic.s_भव.s_start_offset =
			le16_to_cpu(vat20->lengthHeader);
		map->s_type_specअगरic.s_भव.s_num_entries =
			(sbi->s_vat_inode->i_size -
				map->s_type_specअगरic.s_भव.
					s_start_offset) >> 2;
		brअन्यथा(bh);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Load partition descriptor block
 *
 * Returns <0 on error, 0 on success, -EAGAIN is special - try next descriptor
 * sequence.
 */
अटल पूर्णांक udf_load_partdesc(काष्ठा super_block *sb, sector_t block)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा partitionDesc *p;
	काष्ठा udf_part_map *map;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक i, type1_idx;
	uपूर्णांक16_t partitionNumber;
	uपूर्णांक16_t ident;
	पूर्णांक ret;

	bh = udf_पढ़ो_tagged(sb, block, block, &ident);
	अगर (!bh)
		वापस -EAGAIN;
	अगर (ident != TAG_IDENT_PD) अणु
		ret = 0;
		जाओ out_bh;
	पूर्ण

	p = (काष्ठा partitionDesc *)bh->b_data;
	partitionNumber = le16_to_cpu(p->partitionNumber);

	/* First scan क्रम TYPE1 and SPARABLE partitions */
	क्रम (i = 0; i < sbi->s_partitions; i++) अणु
		map = &sbi->s_parपंचांगaps[i];
		udf_debug("Searching map: (%u == %u)\n",
			  map->s_partition_num, partitionNumber);
		अगर (map->s_partition_num == partitionNumber &&
		    (map->s_partition_type == UDF_TYPE1_MAP15 ||
		     map->s_partition_type == UDF_SPARABLE_MAP15))
			अवरोध;
	पूर्ण

	अगर (i >= sbi->s_partitions) अणु
		udf_debug("Partition (%u) not found in partition map\n",
			  partitionNumber);
		ret = 0;
		जाओ out_bh;
	पूर्ण

	ret = udf_fill_partdesc_info(sb, p, i);
	अगर (ret < 0)
		जाओ out_bh;

	/*
	 * Now rescan क्रम VIRTUAL or METADATA partitions when SPARABLE and
	 * PHYSICAL partitions are alपढ़ोy set up
	 */
	type1_idx = i;
	map = शून्य; /* supress 'maybe used uninitialized' warning */
	क्रम (i = 0; i < sbi->s_partitions; i++) अणु
		map = &sbi->s_parपंचांगaps[i];

		अगर (map->s_partition_num == partitionNumber &&
		    (map->s_partition_type == UDF_VIRTUAL_MAP15 ||
		     map->s_partition_type == UDF_VIRTUAL_MAP20 ||
		     map->s_partition_type == UDF_METADATA_MAP25))
			अवरोध;
	पूर्ण

	अगर (i >= sbi->s_partitions) अणु
		ret = 0;
		जाओ out_bh;
	पूर्ण

	ret = udf_fill_partdesc_info(sb, p, i);
	अगर (ret < 0)
		जाओ out_bh;

	अगर (map->s_partition_type == UDF_METADATA_MAP25) अणु
		ret = udf_load_metadata_files(sb, i, type1_idx);
		अगर (ret < 0) अणु
			udf_err(sb, "error loading MetaData partition map %d\n",
				i);
			जाओ out_bh;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If we have a partition with भव map, we करोn't handle
		 * writing to it (we overग_लिखो blocks instead of relocating
		 * them).
		 */
		अगर (!sb_rकरोnly(sb)) अणु
			ret = -EACCES;
			जाओ out_bh;
		पूर्ण
		UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
		ret = udf_load_vat(sb, i, type1_idx);
		अगर (ret < 0)
			जाओ out_bh;
	पूर्ण
	ret = 0;
out_bh:
	/* In हाल loading failed, we handle cleanup in udf_fill_super */
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल पूर्णांक udf_load_sparable_map(काष्ठा super_block *sb,
				 काष्ठा udf_part_map *map,
				 काष्ठा sparablePartitionMap *spm)
अणु
	uपूर्णांक32_t loc;
	uपूर्णांक16_t ident;
	काष्ठा sparingTable *st;
	काष्ठा udf_sparing_data *sdata = &map->s_type_specअगरic.s_sparing;
	पूर्णांक i;
	काष्ठा buffer_head *bh;

	map->s_partition_type = UDF_SPARABLE_MAP15;
	sdata->s_packet_len = le16_to_cpu(spm->packetLength);
	अगर (!is_घातer_of_2(sdata->s_packet_len)) अणु
		udf_err(sb, "error loading logical volume descriptor: "
			"Invalid packet length %u\n",
			(अचिन्हित)sdata->s_packet_len);
		वापस -EIO;
	पूर्ण
	अगर (spm->numSparingTables > 4) अणु
		udf_err(sb, "error loading logical volume descriptor: "
			"Too many sparing tables (%d)\n",
			(पूर्णांक)spm->numSparingTables);
		वापस -EIO;
	पूर्ण
	अगर (le32_to_cpu(spm->sizeSparingTable) > sb->s_blocksize) अणु
		udf_err(sb, "error loading logical volume descriptor: "
			"Too big sparing table size (%u)\n",
			le32_to_cpu(spm->sizeSparingTable));
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < spm->numSparingTables; i++) अणु
		loc = le32_to_cpu(spm->locSparingTable[i]);
		bh = udf_पढ़ो_tagged(sb, loc, loc, &ident);
		अगर (!bh)
			जारी;

		st = (काष्ठा sparingTable *)bh->b_data;
		अगर (ident != 0 ||
		    म_भेदन(st->sparingIdent.ident, UDF_ID_SPARING,
			    म_माप(UDF_ID_SPARING)) ||
		    माप(*st) + le16_to_cpu(st->पुनः_स्मृतिationTableLen) >
							sb->s_blocksize) अणु
			brअन्यथा(bh);
			जारी;
		पूर्ण

		sdata->s_spar_map[i] = bh;
	पूर्ण
	map->s_partition_func = udf_get_pblock_spar15;
	वापस 0;
पूर्ण

अटल पूर्णांक udf_load_logicalvol(काष्ठा super_block *sb, sector_t block,
			       काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा logicalVolDesc *lvd;
	पूर्णांक i, offset;
	uपूर्णांक8_t type;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा genericPartitionMap *gpm;
	uपूर्णांक16_t ident;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक table_len;
	पूर्णांक ret;

	bh = udf_पढ़ो_tagged(sb, block, block, &ident);
	अगर (!bh)
		वापस -EAGAIN;
	BUG_ON(ident != TAG_IDENT_LVD);
	lvd = (काष्ठा logicalVolDesc *)bh->b_data;
	table_len = le32_to_cpu(lvd->mapTableLength);
	अगर (table_len > sb->s_blocksize - माप(*lvd)) अणु
		udf_err(sb, "error loading logical volume descriptor: "
			"Partition table too long (%u > %lu)\n", table_len,
			sb->s_blocksize - माप(*lvd));
		ret = -EIO;
		जाओ out_bh;
	पूर्ण

	ret = udf_verअगरy_करोमुख्य_identअगरier(sb, &lvd->करोमुख्यIdent,
					   "logical volume");
	अगर (ret)
		जाओ out_bh;
	ret = udf_sb_alloc_partition_maps(sb, le32_to_cpu(lvd->numPartitionMaps));
	अगर (ret)
		जाओ out_bh;

	क्रम (i = 0, offset = 0;
	     i < sbi->s_partitions && offset < table_len;
	     i++, offset += gpm->partitionMapLength) अणु
		काष्ठा udf_part_map *map = &sbi->s_parपंचांगaps[i];
		gpm = (काष्ठा genericPartitionMap *)
				&(lvd->partitionMaps[offset]);
		type = gpm->partitionMapType;
		अगर (type == 1) अणु
			काष्ठा genericPartitionMap1 *gpm1 =
				(काष्ठा genericPartitionMap1 *)gpm;
			map->s_partition_type = UDF_TYPE1_MAP15;
			map->s_volumeseqnum = le16_to_cpu(gpm1->volSeqNum);
			map->s_partition_num = le16_to_cpu(gpm1->partitionNum);
			map->s_partition_func = शून्य;
		पूर्ण अन्यथा अगर (type == 2) अणु
			काष्ठा udfPartitionMap2 *upm2 =
						(काष्ठा udfPartitionMap2 *)gpm;
			अगर (!म_भेदन(upm2->partIdent.ident, UDF_ID_VIRTUAL,
						म_माप(UDF_ID_VIRTUAL))) अणु
				u16 suf =
					le16_to_cpu(((__le16 *)upm2->partIdent.
							identSuffix)[0]);
				अगर (suf < 0x0200) अणु
					map->s_partition_type =
							UDF_VIRTUAL_MAP15;
					map->s_partition_func =
							udf_get_pblock_virt15;
				पूर्ण अन्यथा अणु
					map->s_partition_type =
							UDF_VIRTUAL_MAP20;
					map->s_partition_func =
							udf_get_pblock_virt20;
				पूर्ण
			पूर्ण अन्यथा अगर (!म_भेदन(upm2->partIdent.ident,
						UDF_ID_SPARABLE,
						म_माप(UDF_ID_SPARABLE))) अणु
				ret = udf_load_sparable_map(sb, map,
					(काष्ठा sparablePartitionMap *)gpm);
				अगर (ret < 0)
					जाओ out_bh;
			पूर्ण अन्यथा अगर (!म_भेदन(upm2->partIdent.ident,
						UDF_ID_METADATA,
						म_माप(UDF_ID_METADATA))) अणु
				काष्ठा udf_meta_data *mdata =
					&map->s_type_specअगरic.s_metadata;
				काष्ठा metadataPartitionMap *mdm =
						(काष्ठा metadataPartitionMap *)
						&(lvd->partitionMaps[offset]);
				udf_debug("Parsing Logical vol part %d type %u  id=%s\n",
					  i, type, UDF_ID_METADATA);

				map->s_partition_type = UDF_METADATA_MAP25;
				map->s_partition_func = udf_get_pblock_meta25;

				mdata->s_meta_file_loc   =
					le32_to_cpu(mdm->metadataFileLoc);
				mdata->s_mirror_file_loc =
					le32_to_cpu(mdm->metadataMirrorFileLoc);
				mdata->s_biपंचांगap_file_loc =
					le32_to_cpu(mdm->metadataBiपंचांगapFileLoc);
				mdata->s_alloc_unit_size =
					le32_to_cpu(mdm->allocUnitSize);
				mdata->s_align_unit_size =
					le16_to_cpu(mdm->alignUnitSize);
				अगर (mdm->flags & 0x01)
					mdata->s_flags |= MF_DUPLICATE_MD;

				udf_debug("Metadata Ident suffix=0x%x\n",
					  le16_to_cpu(*(__le16 *)
						      mdm->partIdent.identSuffix));
				udf_debug("Metadata part num=%u\n",
					  le16_to_cpu(mdm->partitionNum));
				udf_debug("Metadata part alloc unit size=%u\n",
					  le32_to_cpu(mdm->allocUnitSize));
				udf_debug("Metadata file loc=%u\n",
					  le32_to_cpu(mdm->metadataFileLoc));
				udf_debug("Mirror file loc=%u\n",
					  le32_to_cpu(mdm->metadataMirrorFileLoc));
				udf_debug("Bitmap file loc=%u\n",
					  le32_to_cpu(mdm->metadataBiपंचांगapFileLoc));
				udf_debug("Flags: %d %u\n",
					  mdata->s_flags, mdm->flags);
			पूर्ण अन्यथा अणु
				udf_debug("Unknown ident: %s\n",
					  upm2->partIdent.ident);
				जारी;
			पूर्ण
			map->s_volumeseqnum = le16_to_cpu(upm2->volSeqNum);
			map->s_partition_num = le16_to_cpu(upm2->partitionNum);
		पूर्ण
		udf_debug("Partition (%d:%u) type %u on volume %u\n",
			  i, map->s_partition_num, type, map->s_volumeseqnum);
	पूर्ण

	अगर (fileset) अणु
		काष्ठा दीर्घ_ad *la = (काष्ठा दीर्घ_ad *)&(lvd->logicalVolContentsUse[0]);

		*fileset = lelb_to_cpu(la->extLocation);
		udf_debug("FileSet found in LogicalVolDesc at block=%u, partition=%u\n",
			  fileset->logicalBlockNum,
			  fileset->partitionReferenceNum);
	पूर्ण
	अगर (lvd->पूर्णांकegritySeqExt.extLength)
		udf_load_logicalvolपूर्णांक(sb, leea_to_cpu(lvd->पूर्णांकegritySeqExt));
	ret = 0;

	अगर (!sbi->s_lvid_bh) अणु
		/* We can't generate unique IDs without a valid LVID */
		अगर (sb_rकरोnly(sb)) अणु
			UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
		पूर्ण अन्यथा अणु
			udf_warn(sb, "Damaged or missing LVID, forcing "
				     "readonly mount\n");
			ret = -EACCES;
		पूर्ण
	पूर्ण
out_bh:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * Find the prevailing Logical Volume Integrity Descriptor.
 */
अटल व्योम udf_load_logicalvolपूर्णांक(काष्ठा super_block *sb, काष्ठा kernel_extent_ad loc)
अणु
	काष्ठा buffer_head *bh, *final_bh;
	uपूर्णांक16_t ident;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा logicalVolIntegrityDesc *lvid;
	पूर्णांक indirections = 0;

	जबतक (++indirections <= UDF_MAX_LVID_NESTING) अणु
		final_bh = शून्य;
		जबतक (loc.extLength > 0 &&
			(bh = udf_पढ़ो_tagged(sb, loc.extLocation,
					loc.extLocation, &ident))) अणु
			अगर (ident != TAG_IDENT_LVID) अणु
				brअन्यथा(bh);
				अवरोध;
			पूर्ण

			brअन्यथा(final_bh);
			final_bh = bh;

			loc.extLength -= sb->s_blocksize;
			loc.extLocation++;
		पूर्ण

		अगर (!final_bh)
			वापस;

		brअन्यथा(sbi->s_lvid_bh);
		sbi->s_lvid_bh = final_bh;

		lvid = (काष्ठा logicalVolIntegrityDesc *)final_bh->b_data;
		अगर (lvid->nextIntegrityExt.extLength == 0)
			वापस;

		loc = leea_to_cpu(lvid->nextIntegrityExt);
	पूर्ण

	udf_warn(sb, "Too many LVID indirections (max %u), ignoring.\n",
		UDF_MAX_LVID_NESTING);
	brअन्यथा(sbi->s_lvid_bh);
	sbi->s_lvid_bh = शून्य;
पूर्ण

/*
 * Step क्रम पुनः_स्मृतिation of table of partition descriptor sequence numbers.
 * Must be घातer of 2.
 */
#घोषणा PART_DESC_ALLOC_STEP 32

काष्ठा part_desc_seq_scan_data अणु
	काष्ठा udf_vds_record rec;
	u32 partnum;
पूर्ण;

काष्ठा desc_seq_scan_data अणु
	काष्ठा udf_vds_record vds[VDS_POS_LENGTH];
	अचिन्हित पूर्णांक size_part_descs;
	अचिन्हित पूर्णांक num_part_descs;
	काष्ठा part_desc_seq_scan_data *part_descs_loc;
पूर्ण;

अटल काष्ठा udf_vds_record *handle_partition_descriptor(
				काष्ठा buffer_head *bh,
				काष्ठा desc_seq_scan_data *data)
अणु
	काष्ठा partitionDesc *desc = (काष्ठा partitionDesc *)bh->b_data;
	पूर्णांक partnum;
	पूर्णांक i;

	partnum = le16_to_cpu(desc->partitionNumber);
	क्रम (i = 0; i < data->num_part_descs; i++)
		अगर (partnum == data->part_descs_loc[i].partnum)
			वापस &(data->part_descs_loc[i].rec);
	अगर (data->num_part_descs >= data->size_part_descs) अणु
		काष्ठा part_desc_seq_scan_data *new_loc;
		अचिन्हित पूर्णांक new_size = ALIGN(partnum, PART_DESC_ALLOC_STEP);

		new_loc = kसुस्मृति(new_size, माप(*new_loc), GFP_KERNEL);
		अगर (!new_loc)
			वापस ERR_PTR(-ENOMEM);
		स_नकल(new_loc, data->part_descs_loc,
		       data->size_part_descs * माप(*new_loc));
		kमुक्त(data->part_descs_loc);
		data->part_descs_loc = new_loc;
		data->size_part_descs = new_size;
	पूर्ण
	वापस &(data->part_descs_loc[data->num_part_descs++].rec);
पूर्ण


अटल काष्ठा udf_vds_record *get_volume_descriptor_record(uपूर्णांक16_t ident,
		काष्ठा buffer_head *bh, काष्ठा desc_seq_scan_data *data)
अणु
	चयन (ident) अणु
	हाल TAG_IDENT_PVD: /* ISO 13346 3/10.1 */
		वापस &(data->vds[VDS_POS_PRIMARY_VOL_DESC]);
	हाल TAG_IDENT_IUVD: /* ISO 13346 3/10.4 */
		वापस &(data->vds[VDS_POS_IMP_USE_VOL_DESC]);
	हाल TAG_IDENT_LVD: /* ISO 13346 3/10.6 */
		वापस &(data->vds[VDS_POS_LOGICAL_VOL_DESC]);
	हाल TAG_IDENT_USD: /* ISO 13346 3/10.8 */
		वापस &(data->vds[VDS_POS_UNALLOC_SPACE_DESC]);
	हाल TAG_IDENT_PD: /* ISO 13346 3/10.5 */
		वापस handle_partition_descriptor(bh, data);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Process a मुख्य/reserve volume descriptor sequence.
 *   @block		First block of first extent of the sequence.
 *   @lastblock		Lastblock of first extent of the sequence.
 *   @fileset		There we store extent containing root fileset
 *
 * Returns <0 on error, 0 on success. -EAGAIN is special - try next descriptor
 * sequence
 */
अटल noअंतरभूत पूर्णांक udf_process_sequence(
		काष्ठा super_block *sb,
		sector_t block, sector_t lastblock,
		काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा udf_vds_record *curr;
	काष्ठा generic_desc *gd;
	काष्ठा volDescPtr *vdp;
	bool करोne = false;
	uपूर्णांक32_t vdsn;
	uपूर्णांक16_t ident;
	पूर्णांक ret;
	अचिन्हित पूर्णांक indirections = 0;
	काष्ठा desc_seq_scan_data data;
	अचिन्हित पूर्णांक i;

	स_रखो(data.vds, 0, माप(काष्ठा udf_vds_record) * VDS_POS_LENGTH);
	data.size_part_descs = PART_DESC_ALLOC_STEP;
	data.num_part_descs = 0;
	data.part_descs_loc = kसुस्मृति(data.size_part_descs,
				      माप(*data.part_descs_loc),
				      GFP_KERNEL);
	अगर (!data.part_descs_loc)
		वापस -ENOMEM;

	/*
	 * Read the मुख्य descriptor sequence and find which descriptors
	 * are in it.
	 */
	क्रम (; (!करोne && block <= lastblock); block++) अणु
		bh = udf_पढ़ो_tagged(sb, block, block, &ident);
		अगर (!bh)
			अवरोध;

		/* Process each descriptor (ISO 13346 3/8.3-8.4) */
		gd = (काष्ठा generic_desc *)bh->b_data;
		vdsn = le32_to_cpu(gd->volDescSeqNum);
		चयन (ident) अणु
		हाल TAG_IDENT_VDP: /* ISO 13346 3/10.3 */
			अगर (++indirections > UDF_MAX_TD_NESTING) अणु
				udf_err(sb, "too many Volume Descriptor "
					"Pointers (max %u supported)\n",
					UDF_MAX_TD_NESTING);
				brअन्यथा(bh);
				ret = -EIO;
				जाओ out;
			पूर्ण

			vdp = (काष्ठा volDescPtr *)bh->b_data;
			block = le32_to_cpu(vdp->nextVolDescSeqExt.extLocation);
			lastblock = le32_to_cpu(
				vdp->nextVolDescSeqExt.extLength) >>
				sb->s_blocksize_bits;
			lastblock += block - 1;
			/* For loop is going to increment 'block' again */
			block--;
			अवरोध;
		हाल TAG_IDENT_PVD: /* ISO 13346 3/10.1 */
		हाल TAG_IDENT_IUVD: /* ISO 13346 3/10.4 */
		हाल TAG_IDENT_LVD: /* ISO 13346 3/10.6 */
		हाल TAG_IDENT_USD: /* ISO 13346 3/10.8 */
		हाल TAG_IDENT_PD: /* ISO 13346 3/10.5 */
			curr = get_volume_descriptor_record(ident, bh, &data);
			अगर (IS_ERR(curr)) अणु
				brअन्यथा(bh);
				ret = PTR_ERR(curr);
				जाओ out;
			पूर्ण
			/* Descriptor we करोn't care about? */
			अगर (!curr)
				अवरोध;
			अगर (vdsn >= curr->volDescSeqNum) अणु
				curr->volDescSeqNum = vdsn;
				curr->block = block;
			पूर्ण
			अवरोध;
		हाल TAG_IDENT_TD: /* ISO 13346 3/10.9 */
			करोne = true;
			अवरोध;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	/*
	 * Now पढ़ो पूर्णांकeresting descriptors again and process them
	 * in a suitable order
	 */
	अगर (!data.vds[VDS_POS_PRIMARY_VOL_DESC].block) अणु
		udf_err(sb, "Primary Volume Descriptor not found!\n");
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	ret = udf_load_pvoldesc(sb, data.vds[VDS_POS_PRIMARY_VOL_DESC].block);
	अगर (ret < 0)
		जाओ out;

	अगर (data.vds[VDS_POS_LOGICAL_VOL_DESC].block) अणु
		ret = udf_load_logicalvol(sb,
				data.vds[VDS_POS_LOGICAL_VOL_DESC].block,
				fileset);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Now handle prevailing Partition Descriptors */
	क्रम (i = 0; i < data.num_part_descs; i++) अणु
		ret = udf_load_partdesc(sb, data.part_descs_loc[i].rec.block);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	ret = 0;
out:
	kमुक्त(data.part_descs_loc);
	वापस ret;
पूर्ण

/*
 * Load Volume Descriptor Sequence described by anchor in bh
 *
 * Returns <0 on error, 0 on success
 */
अटल पूर्णांक udf_load_sequence(काष्ठा super_block *sb, काष्ठा buffer_head *bh,
			     काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा anchorVolDescPtr *anchor;
	sector_t मुख्य_s, मुख्य_e, reserve_s, reserve_e;
	पूर्णांक ret;

	anchor = (काष्ठा anchorVolDescPtr *)bh->b_data;

	/* Locate the मुख्य sequence */
	मुख्य_s = le32_to_cpu(anchor->मुख्यVolDescSeqExt.extLocation);
	मुख्य_e = le32_to_cpu(anchor->मुख्यVolDescSeqExt.extLength);
	मुख्य_e = मुख्य_e >> sb->s_blocksize_bits;
	मुख्य_e += मुख्य_s - 1;

	/* Locate the reserve sequence */
	reserve_s = le32_to_cpu(anchor->reserveVolDescSeqExt.extLocation);
	reserve_e = le32_to_cpu(anchor->reserveVolDescSeqExt.extLength);
	reserve_e = reserve_e >> sb->s_blocksize_bits;
	reserve_e += reserve_s - 1;

	/* Process the मुख्य & reserve sequences */
	/* responsible क्रम finding the PartitionDesc(s) */
	ret = udf_process_sequence(sb, मुख्य_s, मुख्य_e, fileset);
	अगर (ret != -EAGAIN)
		वापस ret;
	udf_sb_मुक्त_partitions(sb);
	ret = udf_process_sequence(sb, reserve_s, reserve_e, fileset);
	अगर (ret < 0) अणु
		udf_sb_मुक्त_partitions(sb);
		/* No sequence was OK, वापस -EIO */
		अगर (ret == -EAGAIN)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Check whether there is an anchor block in the given block and
 * load Volume Descriptor Sequence अगर so.
 *
 * Returns <0 on error, 0 on success, -EAGAIN is special - try next anchor
 * block
 */
अटल पूर्णांक udf_check_anchor_block(काष्ठा super_block *sb, sector_t block,
				  काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा buffer_head *bh;
	uपूर्णांक16_t ident;
	पूर्णांक ret;

	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_VARCONV) &&
	    udf_fixed_to_variable(block) >=
	    i_size_पढ़ो(sb->s_bdev->bd_inode) >> sb->s_blocksize_bits)
		वापस -EAGAIN;

	bh = udf_पढ़ो_tagged(sb, block, block, &ident);
	अगर (!bh)
		वापस -EAGAIN;
	अगर (ident != TAG_IDENT_AVDP) अणु
		brअन्यथा(bh);
		वापस -EAGAIN;
	पूर्ण
	ret = udf_load_sequence(sb, bh, fileset);
	brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * Search क्रम an anchor volume descriptor poपूर्णांकer.
 *
 * Returns < 0 on error, 0 on success. -EAGAIN is special - try next set
 * of anchors.
 */
अटल पूर्णांक udf_scan_anchors(काष्ठा super_block *sb, sector_t *lastblock,
			    काष्ठा kernel_lb_addr *fileset)
अणु
	sector_t last[6];
	पूर्णांक i;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक last_count = 0;
	पूर्णांक ret;

	/* First try user provided anchor */
	अगर (sbi->s_anchor) अणु
		ret = udf_check_anchor_block(sb, sbi->s_anchor, fileset);
		अगर (ret != -EAGAIN)
			वापस ret;
	पूर्ण
	/*
	 * according to spec, anchor is in either:
	 *     block 256
	 *     lastblock-256
	 *     lastblock
	 *  however, अगर the disc isn't बंदd, it could be 512.
	 */
	ret = udf_check_anchor_block(sb, sbi->s_session + 256, fileset);
	अगर (ret != -EAGAIN)
		वापस ret;
	/*
	 * The trouble is which block is the last one. Drives often misreport
	 * this so we try various possibilities.
	 */
	last[last_count++] = *lastblock;
	अगर (*lastblock >= 1)
		last[last_count++] = *lastblock - 1;
	last[last_count++] = *lastblock + 1;
	अगर (*lastblock >= 2)
		last[last_count++] = *lastblock - 2;
	अगर (*lastblock >= 150)
		last[last_count++] = *lastblock - 150;
	अगर (*lastblock >= 152)
		last[last_count++] = *lastblock - 152;

	क्रम (i = 0; i < last_count; i++) अणु
		अगर (last[i] >= i_size_पढ़ो(sb->s_bdev->bd_inode) >>
				sb->s_blocksize_bits)
			जारी;
		ret = udf_check_anchor_block(sb, last[i], fileset);
		अगर (ret != -EAGAIN) अणु
			अगर (!ret)
				*lastblock = last[i];
			वापस ret;
		पूर्ण
		अगर (last[i] < 256)
			जारी;
		ret = udf_check_anchor_block(sb, last[i] - 256, fileset);
		अगर (ret != -EAGAIN) अणु
			अगर (!ret)
				*lastblock = last[i];
			वापस ret;
		पूर्ण
	पूर्ण

	/* Finally try block 512 in हाल media is खोलो */
	वापस udf_check_anchor_block(sb, sbi->s_session + 512, fileset);
पूर्ण

/*
 * Find an anchor volume descriptor and load Volume Descriptor Sequence from
 * area specअगरied by it. The function expects sbi->s_lastblock to be the last
 * block on the media.
 *
 * Return <0 on error, 0 अगर anchor found. -EAGAIN is special meaning anchor
 * was not found.
 */
अटल पूर्णांक udf_find_anchor(काष्ठा super_block *sb,
			   काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	sector_t lastblock = sbi->s_last_block;
	पूर्णांक ret;

	ret = udf_scan_anchors(sb, &lastblock, fileset);
	अगर (ret != -EAGAIN)
		जाओ out;

	/* No anchor found? Try VARCONV conversion of block numbers */
	UDF_SET_FLAG(sb, UDF_FLAG_VARCONV);
	lastblock = udf_variable_to_fixed(sbi->s_last_block);
	/* Firstly, we try to not convert number of the last block */
	ret = udf_scan_anchors(sb, &lastblock, fileset);
	अगर (ret != -EAGAIN)
		जाओ out;

	lastblock = sbi->s_last_block;
	/* Secondly, we try with converted number of the last block */
	ret = udf_scan_anchors(sb, &lastblock, fileset);
	अगर (ret < 0) अणु
		/* VARCONV didn't help. Clear it. */
		UDF_CLEAR_FLAG(sb, UDF_FLAG_VARCONV);
	पूर्ण
out:
	अगर (ret == 0)
		sbi->s_last_block = lastblock;
	वापस ret;
पूर्ण

/*
 * Check Volume Structure Descriptor, find Anchor block and load Volume
 * Descriptor Sequence.
 *
 * Returns < 0 on error, 0 on success. -EAGAIN is special meaning anchor
 * block was not found.
 */
अटल पूर्णांक udf_load_vrs(काष्ठा super_block *sb, काष्ठा udf_options *uopt,
			पूर्णांक silent, काष्ठा kernel_lb_addr *fileset)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक nsr = 0;
	पूर्णांक ret;

	अगर (!sb_set_blocksize(sb, uopt->blocksize)) अणु
		अगर (!silent)
			udf_warn(sb, "Bad block size\n");
		वापस -EINVAL;
	पूर्ण
	sbi->s_last_block = uopt->lastblock;
	अगर (!uopt->novrs) अणु
		/* Check that it is NSR02 compliant */
		nsr = udf_check_vsd(sb);
		अगर (!nsr) अणु
			अगर (!silent)
				udf_warn(sb, "No VRS found\n");
			वापस -EINVAL;
		पूर्ण
		अगर (nsr == -1)
			udf_debug("Failed to read sector at offset %d. "
				  "Assuming open disc. Skipping validity "
				  "check\n", VSD_FIRST_SECTOR_OFFSET);
		अगर (!sbi->s_last_block)
			sbi->s_last_block = udf_get_last_block(sb);
	पूर्ण अन्यथा अणु
		udf_debug("Validity check skipped because of novrs option\n");
	पूर्ण

	/* Look क्रम anchor block and load Volume Descriptor Sequence */
	sbi->s_anchor = uopt->anchor;
	ret = udf_find_anchor(sb, fileset);
	अगर (ret < 0) अणु
		अगर (!silent && ret == -EAGAIN)
			udf_warn(sb, "No anchor found\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम udf_finalize_lvid(काष्ठा logicalVolIntegrityDesc *lvid)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_real_ts64(&ts);
	udf_समय_प्रकारo_disk_stamp(&lvid->recordingDateAndTime, ts);
	lvid->descTag.descCRC = cpu_to_le16(
		crc_itu_t(0, (अक्षर *)lvid + माप(काष्ठा tag),
			le16_to_cpu(lvid->descTag.descCRCLength)));
	lvid->descTag.tagChecksum = udf_tag_checksum(&lvid->descTag);
पूर्ण

अटल व्योम udf_खोलो_lvid(काष्ठा super_block *sb)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा buffer_head *bh = sbi->s_lvid_bh;
	काष्ठा logicalVolIntegrityDesc *lvid;
	काष्ठा logicalVolIntegrityDescImpUse *lvidiu;

	अगर (!bh)
		वापस;
	lvid = (काष्ठा logicalVolIntegrityDesc *)bh->b_data;
	lvidiu = udf_sb_lvidiu(sb);
	अगर (!lvidiu)
		वापस;

	mutex_lock(&sbi->s_alloc_mutex);
	lvidiu->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
	lvidiu->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
	अगर (le32_to_cpu(lvid->पूर्णांकegrityType) == LVID_INTEGRITY_TYPE_CLOSE)
		lvid->पूर्णांकegrityType = cpu_to_le32(LVID_INTEGRITY_TYPE_OPEN);
	अन्यथा
		UDF_SET_FLAG(sb, UDF_FLAG_INCONSISTENT);

	udf_finalize_lvid(lvid);
	mark_buffer_dirty(bh);
	sbi->s_lvid_dirty = 0;
	mutex_unlock(&sbi->s_alloc_mutex);
	/* Make खोलोing of fileप्रणाली visible on the media immediately */
	sync_dirty_buffer(bh);
पूर्ण

अटल व्योम udf_बंद_lvid(काष्ठा super_block *sb)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा buffer_head *bh = sbi->s_lvid_bh;
	काष्ठा logicalVolIntegrityDesc *lvid;
	काष्ठा logicalVolIntegrityDescImpUse *lvidiu;

	अगर (!bh)
		वापस;
	lvid = (काष्ठा logicalVolIntegrityDesc *)bh->b_data;
	lvidiu = udf_sb_lvidiu(sb);
	अगर (!lvidiu)
		वापस;

	mutex_lock(&sbi->s_alloc_mutex);
	lvidiu->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
	lvidiu->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
	अगर (UDF_MAX_WRITE_VERSION > le16_to_cpu(lvidiu->maxUDFWriteRev))
		lvidiu->maxUDFWriteRev = cpu_to_le16(UDF_MAX_WRITE_VERSION);
	अगर (sbi->s_udfrev > le16_to_cpu(lvidiu->minUDFReadRev))
		lvidiu->minUDFReadRev = cpu_to_le16(sbi->s_udfrev);
	अगर (sbi->s_udfrev > le16_to_cpu(lvidiu->minUDFWriteRev))
		lvidiu->minUDFWriteRev = cpu_to_le16(sbi->s_udfrev);
	अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_INCONSISTENT))
		lvid->पूर्णांकegrityType = cpu_to_le32(LVID_INTEGRITY_TYPE_CLOSE);

	/*
	 * We set buffer uptodate unconditionally here to aव्योम spurious
	 * warnings from mark_buffer_dirty() when previous EIO has marked
	 * the buffer as !uptodate
	 */
	set_buffer_uptodate(bh);
	udf_finalize_lvid(lvid);
	mark_buffer_dirty(bh);
	sbi->s_lvid_dirty = 0;
	mutex_unlock(&sbi->s_alloc_mutex);
	/* Make closing of fileप्रणाली visible on the media immediately */
	sync_dirty_buffer(bh);
पूर्ण

u64 lvid_get_unique_id(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा logicalVolIntegrityDesc *lvid;
	काष्ठा logicalVolHeaderDesc *lvhd;
	u64 uniqueID;
	u64 ret;

	bh = sbi->s_lvid_bh;
	अगर (!bh)
		वापस 0;

	lvid = (काष्ठा logicalVolIntegrityDesc *)bh->b_data;
	lvhd = (काष्ठा logicalVolHeaderDesc *)lvid->logicalVolContentsUse;

	mutex_lock(&sbi->s_alloc_mutex);
	ret = uniqueID = le64_to_cpu(lvhd->uniqueID);
	अगर (!(++uniqueID & 0xFFFFFFFF))
		uniqueID += 16;
	lvhd->uniqueID = cpu_to_le64(uniqueID);
	udf_updated_lvid(sb);
	mutex_unlock(&sbi->s_alloc_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक udf_fill_super(काष्ठा super_block *sb, व्योम *options, पूर्णांक silent)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा inode *inode = शून्य;
	काष्ठा udf_options uopt;
	काष्ठा kernel_lb_addr rootdir, fileset;
	काष्ठा udf_sb_info *sbi;
	bool lvid_खोलो = false;

	uopt.flags = (1 << UDF_FLAG_USE_AD_IN_ICB) | (1 << UDF_FLAG_STRICT);
	/* By शेष we'll use overflow[ug]id when UDF inode [ug]id == -1 */
	uopt.uid = make_kuid(current_user_ns(), overflowuid);
	uopt.gid = make_kgid(current_user_ns(), overflowgid);
	uopt.umask = 0;
	uopt.भ_शेषe = UDF_INVALID_MODE;
	uopt.dmode = UDF_INVALID_MODE;
	uopt.nls_map = शून्य;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sb->s_fs_info = sbi;

	mutex_init(&sbi->s_alloc_mutex);

	अगर (!udf_parse_options((अक्षर *)options, &uopt, false))
		जाओ parse_options_failure;

	अगर (uopt.flags & (1 << UDF_FLAG_UTF8) &&
	    uopt.flags & (1 << UDF_FLAG_NLS_MAP)) अणु
		udf_err(sb, "utf8 cannot be combined with iocharset\n");
		जाओ parse_options_failure;
	पूर्ण
	अगर ((uopt.flags & (1 << UDF_FLAG_NLS_MAP)) && !uopt.nls_map) अणु
		uopt.nls_map = load_nls_शेष();
		अगर (!uopt.nls_map)
			uopt.flags &= ~(1 << UDF_FLAG_NLS_MAP);
		अन्यथा
			udf_debug("Using default NLS map\n");
	पूर्ण
	अगर (!(uopt.flags & (1 << UDF_FLAG_NLS_MAP)))
		uopt.flags |= (1 << UDF_FLAG_UTF8);

	fileset.logicalBlockNum = 0xFFFFFFFF;
	fileset.partitionReferenceNum = 0xFFFF;

	sbi->s_flags = uopt.flags;
	sbi->s_uid = uopt.uid;
	sbi->s_gid = uopt.gid;
	sbi->s_umask = uopt.umask;
	sbi->s_भ_शेषe = uopt.भ_शेषe;
	sbi->s_dmode = uopt.dmode;
	sbi->s_nls_map = uopt.nls_map;
	rwlock_init(&sbi->s_cred_lock);

	अगर (uopt.session == 0xFFFFFFFF)
		sbi->s_session = udf_get_last_session(sb);
	अन्यथा
		sbi->s_session = uopt.session;

	udf_debug("Multi-session=%d\n", sbi->s_session);

	/* Fill in the rest of the superblock */
	sb->s_op = &udf_sb_ops;
	sb->s_export_op = &udf_export_ops;

	sb->s_magic = UDF_SUPER_MAGIC;
	sb->s_समय_gran = 1000;

	अगर (uopt.flags & (1 << UDF_FLAG_BLOCKSIZE_SET)) अणु
		ret = udf_load_vrs(sb, &uopt, silent, &fileset);
	पूर्ण अन्यथा अणु
		uopt.blocksize = bdev_logical_block_size(sb->s_bdev);
		जबतक (uopt.blocksize <= 4096) अणु
			ret = udf_load_vrs(sb, &uopt, silent, &fileset);
			अगर (ret < 0) अणु
				अगर (!silent && ret != -EACCES) अणु
					pr_notice("Scanning with blocksize %u failed\n",
						  uopt.blocksize);
				पूर्ण
				brअन्यथा(sbi->s_lvid_bh);
				sbi->s_lvid_bh = शून्य;
				/*
				 * EACCES is special - we want to propagate to
				 * upper layers that we cannot handle RW mount.
				 */
				अगर (ret == -EACCES)
					अवरोध;
			पूर्ण अन्यथा
				अवरोध;

			uopt.blocksize <<= 1;
		पूर्ण
	पूर्ण
	अगर (ret < 0) अणु
		अगर (ret == -EAGAIN) अणु
			udf_warn(sb, "No partition found (1)\n");
			ret = -EINVAL;
		पूर्ण
		जाओ error_out;
	पूर्ण

	udf_debug("Lastblock=%u\n", sbi->s_last_block);

	अगर (sbi->s_lvid_bh) अणु
		काष्ठा logicalVolIntegrityDescImpUse *lvidiu =
							udf_sb_lvidiu(sb);
		uपूर्णांक16_t minUDFReadRev;
		uपूर्णांक16_t minUDFWriteRev;

		अगर (!lvidiu) अणु
			ret = -EINVAL;
			जाओ error_out;
		पूर्ण
		minUDFReadRev = le16_to_cpu(lvidiu->minUDFReadRev);
		minUDFWriteRev = le16_to_cpu(lvidiu->minUDFWriteRev);
		अगर (minUDFReadRev > UDF_MAX_READ_VERSION) अणु
			udf_err(sb, "minUDFReadRev=%x (max is %x)\n",
				minUDFReadRev,
				UDF_MAX_READ_VERSION);
			ret = -EINVAL;
			जाओ error_out;
		पूर्ण अन्यथा अगर (minUDFWriteRev > UDF_MAX_WRITE_VERSION) अणु
			अगर (!sb_rकरोnly(sb)) अणु
				ret = -EACCES;
				जाओ error_out;
			पूर्ण
			UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
		पूर्ण

		sbi->s_udfrev = minUDFWriteRev;

		अगर (minUDFReadRev >= UDF_VERS_USE_EXTENDED_FE)
			UDF_SET_FLAG(sb, UDF_FLAG_USE_EXTENDED_FE);
		अगर (minUDFReadRev >= UDF_VERS_USE_STREAMS)
			UDF_SET_FLAG(sb, UDF_FLAG_USE_STREAMS);
	पूर्ण

	अगर (!sbi->s_partitions) अणु
		udf_warn(sb, "No partition found (2)\n");
		ret = -EINVAL;
		जाओ error_out;
	पूर्ण

	अगर (sbi->s_parपंचांगaps[sbi->s_partition].s_partition_flags &
			UDF_PART_FLAG_READ_ONLY) अणु
		अगर (!sb_rकरोnly(sb)) अणु
			ret = -EACCES;
			जाओ error_out;
		पूर्ण
		UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
	पूर्ण

	ret = udf_find_fileset(sb, &fileset, &rootdir);
	अगर (ret < 0) अणु
		udf_warn(sb, "No fileset found\n");
		जाओ error_out;
	पूर्ण

	अगर (!silent) अणु
		काष्ठा बारtamp ts;
		udf_समय_प्रकारo_disk_stamp(&ts, sbi->s_record_समय);
		udf_info("Mounting volume '%s', timestamp %04u/%02u/%02u %02u:%02u (%x)\n",
			 sbi->s_volume_ident,
			 le16_to_cpu(ts.year), ts.month, ts.day,
			 ts.hour, ts.minute, le16_to_cpu(ts.typeAndTimezone));
	पूर्ण
	अगर (!sb_rकरोnly(sb)) अणु
		udf_खोलो_lvid(sb);
		lvid_खोलो = true;
	पूर्ण

	/* Assign the root inode */
	/* assign inodes by physical block number */
	/* perhaps it's not extensible enough, but क्रम now ... */
	inode = udf_iget(sb, &rootdir);
	अगर (IS_ERR(inode)) अणु
		udf_err(sb, "Error in udf_iget, block=%u, partition=%u\n",
		       rootdir.logicalBlockNum, rootdir.partitionReferenceNum);
		ret = PTR_ERR(inode);
		जाओ error_out;
	पूर्ण

	/* Allocate a dentry क्रम the root inode */
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root) अणु
		udf_err(sb, "Couldn't allocate root dentry\n");
		ret = -ENOMEM;
		जाओ error_out;
	पूर्ण
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_max_links = UDF_MAX_LINKS;
	वापस 0;

error_out:
	iput(sbi->s_vat_inode);
parse_options_failure:
	अगर (uopt.nls_map)
		unload_nls(uopt.nls_map);
	अगर (lvid_खोलो)
		udf_बंद_lvid(sb);
	brअन्यथा(sbi->s_lvid_bh);
	udf_sb_मुक्त_partitions(sb);
	kमुक्त(sbi);
	sb->s_fs_info = शून्य;

	वापस ret;
पूर्ण

व्योम _udf_err(काष्ठा super_block *sb, स्थिर अक्षर *function,
	      स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("error (device %s): %s: %pV", sb->s_id, function, &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम _udf_warn(काष्ठा super_block *sb, स्थिर अक्षर *function,
	       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_warn("warning (device %s): %s: %pV", sb->s_id, function, &vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल व्योम udf_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा udf_sb_info *sbi;

	sbi = UDF_SB(sb);

	iput(sbi->s_vat_inode);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP))
		unload_nls(sbi->s_nls_map);
	अगर (!sb_rकरोnly(sb))
		udf_बंद_lvid(sb);
	brअन्यथा(sbi->s_lvid_bh);
	udf_sb_मुक्त_partitions(sb);
	mutex_destroy(&sbi->s_alloc_mutex);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक udf_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);

	mutex_lock(&sbi->s_alloc_mutex);
	अगर (sbi->s_lvid_dirty) अणु
		काष्ठा buffer_head *bh = sbi->s_lvid_bh;
		काष्ठा logicalVolIntegrityDesc *lvid;

		lvid = (काष्ठा logicalVolIntegrityDesc *)bh->b_data;
		udf_finalize_lvid(lvid);

		/*
		 * Blockdevice will be synced later so we करोn't have to submit
		 * the buffer क्रम IO
		 */
		mark_buffer_dirty(bh);
		sbi->s_lvid_dirty = 0;
	पूर्ण
	mutex_unlock(&sbi->s_alloc_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक udf_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा logicalVolIntegrityDescImpUse *lvidiu;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	lvidiu = udf_sb_lvidiu(sb);
	buf->f_type = UDF_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->s_parपंचांगaps[sbi->s_partition].s_partition_len;
	buf->f_bमुक्त = udf_count_मुक्त(sb);
	buf->f_bavail = buf->f_bमुक्त;
	/*
	 * Let's pretend each free block is also a free 'inode' since UDF करोes
	 * not have separate pपुनः_स्मृतिated table of inodes.
	 */
	buf->f_files = (lvidiu != शून्य ? (le32_to_cpu(lvidiu->numFiles) +
					  le32_to_cpu(lvidiu->numDirs)) : 0)
			+ buf->f_bमुक्त;
	buf->f_fमुक्त = buf->f_bमुक्त;
	buf->f_namelen = UDF_NAME_LEN;
	buf->f_fsid = u64_to_fsid(id);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक udf_count_मुक्त_biपंचांगap(काष्ठा super_block *sb,
					  काष्ठा udf_biपंचांगap *biपंचांगap)
अणु
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित पूर्णांक accum = 0;
	पूर्णांक index;
	udf_pblk_t block = 0, newblock;
	काष्ठा kernel_lb_addr loc;
	uपूर्णांक32_t bytes;
	uपूर्णांक8_t *ptr;
	uपूर्णांक16_t ident;
	काष्ठा spaceBiपंचांगapDesc *bm;

	loc.logicalBlockNum = biपंचांगap->s_extPosition;
	loc.partitionReferenceNum = UDF_SB(sb)->s_partition;
	bh = udf_पढ़ो_ptagged(sb, &loc, 0, &ident);

	अगर (!bh) अणु
		udf_err(sb, "udf_count_free failed\n");
		जाओ out;
	पूर्ण अन्यथा अगर (ident != TAG_IDENT_SBD) अणु
		brअन्यथा(bh);
		udf_err(sb, "udf_count_free failed\n");
		जाओ out;
	पूर्ण

	bm = (काष्ठा spaceBiपंचांगapDesc *)bh->b_data;
	bytes = le32_to_cpu(bm->numOfBytes);
	index = माप(काष्ठा spaceBiपंचांगapDesc); /* offset in first block only */
	ptr = (uपूर्णांक8_t *)bh->b_data;

	जबतक (bytes > 0) अणु
		u32 cur_bytes = min_t(u32, bytes, sb->s_blocksize - index);
		accum += biपंचांगap_weight((स्थिर अचिन्हित दीर्घ *)(ptr + index),
					cur_bytes * 8);
		bytes -= cur_bytes;
		अगर (bytes) अणु
			brअन्यथा(bh);
			newblock = udf_get_lb_pblock(sb, &loc, ++block);
			bh = udf_tपढ़ो(sb, newblock);
			अगर (!bh) अणु
				udf_debug("read failed\n");
				जाओ out;
			पूर्ण
			index = 0;
			ptr = (uपूर्णांक8_t *)bh->b_data;
		पूर्ण
	पूर्ण
	brअन्यथा(bh);
out:
	वापस accum;
पूर्ण

अटल अचिन्हित पूर्णांक udf_count_मुक्त_table(काष्ठा super_block *sb,
					 काष्ठा inode *table)
अणु
	अचिन्हित पूर्णांक accum = 0;
	uपूर्णांक32_t elen;
	काष्ठा kernel_lb_addr eloc;
	पूर्णांक8_t etype;
	काष्ठा extent_position epos;

	mutex_lock(&UDF_SB(sb)->s_alloc_mutex);
	epos.block = UDF_I(table)->i_location;
	epos.offset = माप(काष्ठा unallocSpaceEntry);
	epos.bh = शून्य;

	जबतक ((etype = udf_next_aext(table, &epos, &eloc, &elen, 1)) != -1)
		accum += (elen >> table->i_sb->s_blocksize_bits);

	brअन्यथा(epos.bh);
	mutex_unlock(&UDF_SB(sb)->s_alloc_mutex);

	वापस accum;
पूर्ण

अटल अचिन्हित पूर्णांक udf_count_मुक्त(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक accum = 0;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	अचिन्हित पूर्णांक part = sbi->s_partition;
	पूर्णांक ptype = sbi->s_parपंचांगaps[part].s_partition_type;

	अगर (ptype == UDF_METADATA_MAP25) अणु
		part = sbi->s_parपंचांगaps[part].s_type_specअगरic.s_metadata.
							s_phys_partition_ref;
	पूर्ण अन्यथा अगर (ptype == UDF_VIRTUAL_MAP15 || ptype == UDF_VIRTUAL_MAP20) अणु
		/*
		 * Fileप्रणालीs with VAT are append-only and we cannot ग_लिखो to
 		 * them. Let's just report 0 here.
		 */
		वापस 0;
	पूर्ण

	अगर (sbi->s_lvid_bh) अणु
		काष्ठा logicalVolIntegrityDesc *lvid =
			(काष्ठा logicalVolIntegrityDesc *)
			sbi->s_lvid_bh->b_data;
		अगर (le32_to_cpu(lvid->numOfPartitions) > part) अणु
			accum = le32_to_cpu(
					lvid->मुक्तSpaceTable[part]);
			अगर (accum == 0xFFFFFFFF)
				accum = 0;
		पूर्ण
	पूर्ण

	अगर (accum)
		वापस accum;

	map = &sbi->s_parपंचांगaps[part];
	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP) अणु
		accum += udf_count_मुक्त_biपंचांगap(sb,
					       map->s_uspace.s_biपंचांगap);
	पूर्ण
	अगर (accum)
		वापस accum;

	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE) अणु
		accum += udf_count_मुक्त_table(sb,
					      map->s_uspace.s_table);
	पूर्ण
	वापस accum;
पूर्ण

MODULE_AUTHOR("Ben Fennema");
MODULE_DESCRIPTION("Universal Disk Format Filesystem");
MODULE_LICENSE("GPL");
module_init(init_udf_fs)
module_निकास(निकास_udf_fs)
