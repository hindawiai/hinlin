<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/fat/misc.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *  22/11/2000 - Fixed fat_date_unix2करोs क्रम dates earlier than 01/01/1980
 *		 and date_करोs2unix क्रम date==0 by Igor Zhbanov(bsg@uniyar.ac.ru)
 */

#समावेश "fat.h"
#समावेश <linux/iversion.h>

/*
 * fat_fs_error reports a file प्रणाली problem that might indicate fa data
 * corruption/inconsistency. Depending on 'errors' mount option the
 * panic() is called, or error message is prपूर्णांकed FAT and nothing is करोne,
 * or fileप्रणाली is remounted पढ़ो-only (शेष behavior).
 * In हाल the file प्रणाली is remounted पढ़ो-only, it can be made writable
 * again by remounting it.
 */
व्योम __fat_fs_error(काष्ठा super_block *sb, पूर्णांक report, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा fat_mount_options *opts = &MSDOS_SB(sb)->options;
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;

	अगर (report) अणु
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		fat_msg(sb, KERN_ERR, "error, %pV", &vaf);
		बहु_पूर्ण(args);
	पूर्ण

	अगर (opts->errors == FAT_ERRORS_PANIC)
		panic("FAT-fs (%s): fs panic from previous error\n", sb->s_id);
	अन्यथा अगर (opts->errors == FAT_ERRORS_RO && !sb_rकरोnly(sb)) अणु
		sb->s_flags |= SB_RDONLY;
		fat_msg(sb, KERN_ERR, "Filesystem has been set read-only");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__fat_fs_error);

/**
 * fat_msg() - prपूर्णांक preक्रमmated FAT specअगरic messages. Every thing what is
 * not fat_fs_error() should be fat_msg().
 */
व्योम fat_msg(काष्ठा super_block *sb, स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk("%sFAT-fs (%s): %pV\n", level, sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/* Flushes the number of मुक्त clusters on FAT32 */
/* XXX: Need to ग_लिखो one per FSINFO block.  Currently only ग_लिखोs 1 */
पूर्णांक fat_clusters_flush(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh;
	काष्ठा fat_boot_fsinfo *fsinfo;

	अगर (!is_fat32(sbi))
		वापस 0;

	bh = sb_bपढ़ो(sb, sbi->fsinfo_sector);
	अगर (bh == शून्य) अणु
		fat_msg(sb, KERN_ERR, "bread failed in fat_clusters_flush");
		वापस -EIO;
	पूर्ण

	fsinfo = (काष्ठा fat_boot_fsinfo *)bh->b_data;
	/* Sanity check */
	अगर (!IS_FSINFO(fsinfo)) अणु
		fat_msg(sb, KERN_ERR, "Invalid FSINFO signature: "
		       "0x%08x, 0x%08x (sector = %lu)",
		       le32_to_cpu(fsinfo->signature1),
		       le32_to_cpu(fsinfo->signature2),
		       sbi->fsinfo_sector);
	पूर्ण अन्यथा अणु
		अगर (sbi->मुक्त_clusters != -1)
			fsinfo->मुक्त_clusters = cpu_to_le32(sbi->मुक्त_clusters);
		अगर (sbi->prev_मुक्त != -1)
			fsinfo->next_cluster = cpu_to_le32(sbi->prev_मुक्त);
		mark_buffer_dirty(bh);
	पूर्ण
	brअन्यथा(bh);

	वापस 0;
पूर्ण

/*
 * fat_chain_add() adds a new cluster to the chain of clusters represented
 * by inode.
 */
पूर्णांक fat_chain_add(काष्ठा inode *inode, पूर्णांक new_dclus, पूर्णांक nr_cluster)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक ret, new_fclus, last;

	/*
	 * We must locate the last cluster of the file to add this new
	 * one (new_dclus) to the end of the link list (the FAT).
	 */
	last = new_fclus = 0;
	अगर (MSDOS_I(inode)->i_start) अणु
		पूर्णांक fclus, dclus;

		ret = fat_get_cluster(inode, FAT_ENT_खातापूर्ण, &fclus, &dclus);
		अगर (ret < 0)
			वापस ret;
		new_fclus = fclus + 1;
		last = dclus;
	पूर्ण

	/* add new one to the last of the cluster chain */
	अगर (last) अणु
		काष्ठा fat_entry fatent;

		fatent_init(&fatent);
		ret = fat_ent_पढ़ो(inode, &fatent, last);
		अगर (ret >= 0) अणु
			पूर्णांक रुको = inode_needs_sync(inode);
			ret = fat_ent_ग_लिखो(inode, &fatent, new_dclus, रुको);
			fatent_brअन्यथा(&fatent);
		पूर्ण
		अगर (ret < 0)
			वापस ret;
		/*
		 * FIXME:Although we can add this cache, fat_cache_add() is
		 * assuming to be called after linear search with fat_cache_id.
		 */
//		fat_cache_add(inode, new_fclus, new_dclus);
	पूर्ण अन्यथा अणु
		MSDOS_I(inode)->i_start = new_dclus;
		MSDOS_I(inode)->i_logstart = new_dclus;
		/*
		 * Since generic_ग_लिखो_sync() synchronizes regular files later,
		 * we sync here only directories.
		 */
		अगर (S_ISसूची(inode->i_mode) && IS_सूचीSYNC(inode)) अणु
			ret = fat_sync_inode(inode);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा
			mark_inode_dirty(inode);
	पूर्ण
	अगर (new_fclus != (inode->i_blocks >> (sbi->cluster_bits - 9))) अणु
		fat_fs_error(sb, "clusters badly computed (%d != %llu)",
			     new_fclus,
			     (llu)(inode->i_blocks >> (sbi->cluster_bits - 9)));
		fat_cache_inval_inode(inode);
	पूर्ण
	inode->i_blocks += nr_cluster << (sbi->cluster_bits - 9);

	वापस 0;
पूर्ण

/*
 * The epoch of FAT बारtamp is 1980.
 *     :  bits :     value
 * date:  0 -  4: day	(1 -  31)
 * date:  5 -  8: month	(1 -  12)
 * date:  9 - 15: year	(0 - 127) from 1980
 * समय:  0 -  4: sec	(0 -  29) 2sec counts
 * समय:  5 - 10: min	(0 -  59)
 * समय: 11 - 15: hour	(0 -  23)
 */
#घोषणा SECS_PER_MIN	60
#घोषणा SECS_PER_HOUR	(60 * 60)
#घोषणा SECS_PER_DAY	(SECS_PER_HOUR * 24)
/* days between 1.1.70 and 1.1.80 (2 leap days) */
#घोषणा DAYS_DELTA	(365 * 10 + 2)
/* 120 (2100 - 1980) isn't leap year */
#घोषणा YEAR_2100	120
#घोषणा IS_LEAP_YEAR(y)	(!((y) & 3) && (y) != YEAR_2100)

/* Linear day numbers of the respective 1sts in non-leap years. */
अटल दीर्घ days_in_year[] = अणु
	/* Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec */
	0,   0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 0, 0, 0,
पूर्ण;

अटल अंतरभूत पूर्णांक fat_tz_offset(काष्ठा msकरोs_sb_info *sbi)
अणु
	वापस (sbi->options.tz_set ?
	       -sbi->options.समय_offset :
	       sys_tz.tz_minuteswest) * SECS_PER_MIN;
पूर्ण

/* Convert a FAT समय/date pair to a UNIX date (seconds since 1 1 70). */
व्योम fat_समय_fat2unix(काष्ठा msकरोs_sb_info *sbi, काष्ठा बारpec64 *ts,
		       __le16 __समय, __le16 __date, u8 समय_cs)
अणु
	u16 समय = le16_to_cpu(__समय), date = le16_to_cpu(__date);
	समय64_t second;
	दीर्घ day, leap_day, month, year;

	year  = date >> 9;
	month = max(1, (date >> 5) & 0xf);
	day   = max(1, date & 0x1f) - 1;

	leap_day = (year + 3) / 4;
	अगर (year > YEAR_2100)		/* 2100 isn't leap year */
		leap_day--;
	अगर (IS_LEAP_YEAR(year) && month > 2)
		leap_day++;

	second =  (समय & 0x1f) << 1;
	second += ((समय >> 5) & 0x3f) * SECS_PER_MIN;
	second += (समय >> 11) * SECS_PER_HOUR;
	second += (समय64_t)(year * 365 + leap_day
		   + days_in_year[month] + day
		   + DAYS_DELTA) * SECS_PER_DAY;

	second += fat_tz_offset(sbi);

	अगर (समय_cs) अणु
		ts->tv_sec = second + (समय_cs / 100);
		ts->tv_nsec = (समय_cs % 100) * 10000000;
	पूर्ण अन्यथा अणु
		ts->tv_sec = second;
		ts->tv_nsec = 0;
	पूर्ण
पूर्ण

/* Convert linear UNIX date to a FAT समय/date pair. */
व्योम fat_समय_unix2fat(काष्ठा msकरोs_sb_info *sbi, काष्ठा बारpec64 *ts,
		       __le16 *समय, __le16 *date, u8 *समय_cs)
अणु
	काष्ठा पंचांग पंचांग;
	समय64_to_पंचांग(ts->tv_sec, -fat_tz_offset(sbi), &पंचांग);

	/*  FAT can only support year between 1980 to 2107 */
	अगर (पंचांग.पंचांग_year < 1980 - 1900) अणु
		*समय = 0;
		*date = cpu_to_le16((0 << 9) | (1 << 5) | 1);
		अगर (समय_cs)
			*समय_cs = 0;
		वापस;
	पूर्ण
	अगर (पंचांग.पंचांग_year > 2107 - 1900) अणु
		*समय = cpu_to_le16((23 << 11) | (59 << 5) | 29);
		*date = cpu_to_le16((127 << 9) | (12 << 5) | 31);
		अगर (समय_cs)
			*समय_cs = 199;
		वापस;
	पूर्ण

	/* from 1900 -> from 1980 */
	पंचांग.पंचांग_year -= 80;
	/* 0~11 -> 1~12 */
	पंचांग.पंचांग_mon++;
	/* 0~59 -> 0~29(2sec counts) */
	पंचांग.पंचांग_sec >>= 1;

	*समय = cpu_to_le16(पंचांग.पंचांग_hour << 11 | पंचांग.पंचांग_min << 5 | पंचांग.पंचांग_sec);
	*date = cpu_to_le16(पंचांग.पंचांग_year << 9 | पंचांग.पंचांग_mon << 5 | पंचांग.पंचांग_mday);
	अगर (समय_cs)
		*समय_cs = (ts->tv_sec & 1) * 100 + ts->tv_nsec / 10000000;
पूर्ण
EXPORT_SYMBOL_GPL(fat_समय_unix2fat);

अटल अंतरभूत काष्ठा बारpec64 fat_बारpec64_trunc_2secs(काष्ठा बारpec64 ts)
अणु
	वापस (काष्ठा बारpec64)अणु ts.tv_sec & ~1ULL, 0 पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा बारpec64 fat_बारpec64_trunc_10ms(काष्ठा बारpec64 ts)
अणु
	अगर (ts.tv_nsec)
		ts.tv_nsec -= ts.tv_nsec % 10000000UL;
	वापस ts;
पूर्ण

/*
 * truncate the various बार with appropriate granularity:
 *   root inode:
 *     all बार always 0
 *   all other inodes:
 *     mसमय - 2 seconds
 *     स_समय
 *       msकरोs - 2 seconds
 *       vfat  - 10 milliseconds
 *     aसमय - 24 hours (00:00:00 in local समयzone)
 */
पूर्णांक fat_truncate_समय(काष्ठा inode *inode, काष्ठा बारpec64 *now, पूर्णांक flags)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	काष्ठा बारpec64 ts;

	अगर (inode->i_ino == MSDOS_ROOT_INO)
		वापस 0;

	अगर (now == शून्य) अणु
		now = &ts;
		ts = current_समय(inode);
	पूर्ण

	अगर (flags & S_ATIME) अणु
		/* to स_स्थानीय */
		समय64_t seconds = now->tv_sec - fat_tz_offset(sbi);
		s32 reमुख्यder;

		भाग_s64_rem(seconds, SECS_PER_DAY, &reमुख्यder);
		/* to day boundary, and back to unix समय */
		seconds = seconds + fat_tz_offset(sbi) - reमुख्यder;

		inode->i_aसमय = (काष्ठा बारpec64)अणु seconds, 0 पूर्ण;
	पूर्ण
	अगर (flags & S_CTIME) अणु
		अगर (sbi->options.isvfat)
			inode->i_स_समय = fat_बारpec64_trunc_10ms(*now);
		अन्यथा
			inode->i_स_समय = fat_बारpec64_trunc_2secs(*now);
	पूर्ण
	अगर (flags & S_MTIME)
		inode->i_mसमय = fat_बारpec64_trunc_2secs(*now);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fat_truncate_समय);

पूर्णांक fat_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *now, पूर्णांक flags)
अणु
	पूर्णांक dirty_flags = 0;

	अगर (inode->i_ino == MSDOS_ROOT_INO)
		वापस 0;

	अगर (flags & (S_ATIME | S_CTIME | S_MTIME)) अणु
		fat_truncate_समय(inode, now, flags);
		अगर (inode->i_sb->s_flags & SB_LAZYTIME)
			dirty_flags |= I_सूचीTY_TIME;
		अन्यथा
			dirty_flags |= I_सूचीTY_SYNC;
	पूर्ण

	अगर ((flags & S_VERSION) && inode_maybe_inc_iversion(inode, false))
		dirty_flags |= I_सूचीTY_SYNC;

	__mark_inode_dirty(inode, dirty_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fat_update_समय);

पूर्णांक fat_sync_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr_bhs)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < nr_bhs; i++)
		ग_लिखो_dirty_buffer(bhs[i], 0);

	क्रम (i = 0; i < nr_bhs; i++) अणु
		रुको_on_buffer(bhs[i]);
		अगर (!err && !buffer_uptodate(bhs[i]))
			err = -EIO;
	पूर्ण
	वापस err;
पूर्ण
