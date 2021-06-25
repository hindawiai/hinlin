<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f2fs sysfs पूर्णांकerface
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 * Copyright (c) 2017 Chao Yu <chao@kernel.org>
 */
#समावेश <linux/compiler.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/unicode.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/sysfs.h>

#समावेश "f2fs.h"
#समावेश "segment.h"
#समावेश "gc.h"
#समावेश <trace/events/f2fs.h>

अटल काष्ठा proc_dir_entry *f2fs_proc_root;

/* Sysfs support क्रम f2fs */
क्रमागत अणु
	GC_THREAD,	/* काष्ठा f2fs_gc_thपढ़ो */
	SM_INFO,	/* काष्ठा f2fs_sm_info */
	DCC_INFO,	/* काष्ठा discard_cmd_control */
	NM_INFO,	/* काष्ठा f2fs_nm_info */
	F2FS_SBI,	/* काष्ठा f2fs_sb_info */
#अगर_घोषित CONFIG_F2FS_STAT_FS
	STAT_INFO,	/* काष्ठा f2fs_stat_info */
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	FAULT_INFO_RATE,	/* काष्ठा f2fs_fault_info */
	FAULT_INFO_TYPE,	/* काष्ठा f2fs_fault_info */
#पूर्ण_अगर
	RESERVED_BLOCKS,	/* काष्ठा f2fs_sb_info */
	CPRC_INFO,	/* काष्ठा ckpt_req_control */
पूर्ण;

काष्ठा f2fs_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा f2fs_attr *, काष्ठा f2fs_sb_info *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा f2fs_attr *, काष्ठा f2fs_sb_info *,
			 स्थिर अक्षर *, माप_प्रकार);
	पूर्णांक काष्ठा_type;
	पूर्णांक offset;
	पूर्णांक id;
पूर्ण;

अटल sमाप_प्रकार f2fs_sbi_show(काष्ठा f2fs_attr *a,
			     काष्ठा f2fs_sb_info *sbi, अक्षर *buf);

अटल अचिन्हित अक्षर *__काष्ठा_ptr(काष्ठा f2fs_sb_info *sbi, पूर्णांक काष्ठा_type)
अणु
	अगर (काष्ठा_type == GC_THREAD)
		वापस (अचिन्हित अक्षर *)sbi->gc_thपढ़ो;
	अन्यथा अगर (काष्ठा_type == SM_INFO)
		वापस (अचिन्हित अक्षर *)SM_I(sbi);
	अन्यथा अगर (काष्ठा_type == DCC_INFO)
		वापस (अचिन्हित अक्षर *)SM_I(sbi)->dcc_info;
	अन्यथा अगर (काष्ठा_type == NM_INFO)
		वापस (अचिन्हित अक्षर *)NM_I(sbi);
	अन्यथा अगर (काष्ठा_type == F2FS_SBI || काष्ठा_type == RESERVED_BLOCKS)
		वापस (अचिन्हित अक्षर *)sbi;
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	अन्यथा अगर (काष्ठा_type == FAULT_INFO_RATE ||
					काष्ठा_type == FAULT_INFO_TYPE)
		वापस (अचिन्हित अक्षर *)&F2FS_OPTION(sbi).fault_info;
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_STAT_FS
	अन्यथा अगर (काष्ठा_type == STAT_INFO)
		वापस (अचिन्हित अक्षर *)F2FS_STAT(sbi);
#पूर्ण_अगर
	अन्यथा अगर (काष्ठा_type == CPRC_INFO)
		वापस (अचिन्हित अक्षर *)&sbi->cprc_info;
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार dirty_segments_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)(dirty_segments(sbi)));
पूर्ण

अटल sमाप_प्रकार मुक्त_segments_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)(मुक्त_segments(sbi)));
पूर्ण

अटल sमाप_प्रकार ovp_segments_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)(overprovision_segments(sbi)));
पूर्ण

अटल sमाप_प्रकार lअगरeसमय_ग_लिखो_kbytes_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)(sbi->kbytes_written +
			((f2fs_get_sectors_written(sbi) -
				sbi->sectors_written_start) >> 1)));
पूर्ण

अटल sमाप_प्रकार sb_status_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lx\n", sbi->s_flag);
पूर्ण

अटल sमाप_प्रकार features_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	पूर्णांक len = 0;

	अगर (f2fs_sb_has_encrypt(sbi))
		len += scnम_लिखो(buf, PAGE_SIZE - len, "%s",
						"encryption");
	अगर (f2fs_sb_has_blkzoned(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "blkzoned");
	अगर (f2fs_sb_has_extra_attr(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "extra_attr");
	अगर (f2fs_sb_has_project_quota(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "projquota");
	अगर (f2fs_sb_has_inode_chksum(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_checksum");
	अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "flexible_inline_xattr");
	अगर (f2fs_sb_has_quota_ino(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "quota_ino");
	अगर (f2fs_sb_has_inode_crसमय(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_crtime");
	अगर (f2fs_sb_has_lost_found(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "lost_found");
	अगर (f2fs_sb_has_verity(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "verity");
	अगर (f2fs_sb_has_sb_chksum(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "sb_checksum");
	अगर (f2fs_sb_has_हालfold(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "casefold");
	अगर (f2fs_sb_has_compression(sbi))
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "compression");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "pin_file");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार current_reserved_blocks_show(काष्ठा f2fs_attr *a,
					काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", sbi->current_reserved_blocks);
पूर्ण

अटल sमाप_प्रकार unusable_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	block_t unusable;

	अगर (test_opt(sbi, DISABLE_CHECKPOINT))
		unusable = sbi->unusable_block_count;
	अन्यथा
		unusable = f2fs_get_unusable_blocks(sbi);
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)unusable);
पूर्ण

अटल sमाप_प्रकार encoding_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
#अगर_घोषित CONFIG_UNICODE
	काष्ठा super_block *sb = sbi->sb;

	अगर (f2fs_sb_has_हालfold(sbi))
		वापस snम_लिखो(buf, PAGE_SIZE, "%s (%d.%d.%d)\n",
			sb->s_encoding->अक्षरset,
			(sb->s_encoding->version >> 16) & 0xff,
			(sb->s_encoding->version >> 8) & 0xff,
			sb->s_encoding->version & 0xff);
#पूर्ण_अगर
	वापस प्र_लिखो(buf, "(none)");
पूर्ण

अटल sमाप_प्रकार mounted_समय_sec_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu", SIT_I(sbi)->mounted_समय);
पूर्ण

#अगर_घोषित CONFIG_F2FS_STAT_FS
अटल sमाप_प्रकार moved_blocks_क्रमeground_show(काष्ठा f2fs_attr *a,
				काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);

	वापस प्र_लिखो(buf, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)(si->tot_blks -
			(si->bg_data_blks + si->bg_node_blks)));
पूर्ण

अटल sमाप_प्रकार moved_blocks_background_show(काष्ठा f2fs_attr *a,
				काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);

	वापस प्र_लिखो(buf, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)(si->bg_data_blks + si->bg_node_blks));
पूर्ण

अटल sमाप_प्रकार avg_vblocks_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);

	si->dirty_count = dirty_segments(sbi);
	f2fs_update_sit_info(sbi);
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)(si->avg_vblocks));
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार मुख्य_blkaddr_show(काष्ठा f2fs_attr *a,
				काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)MAIN_BLKADDR(sbi));
पूर्ण

अटल sमाप_प्रकार f2fs_sbi_show(काष्ठा f2fs_attr *a,
			काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	अचिन्हित अक्षर *ptr = शून्य;
	अचिन्हित पूर्णांक *ui;

	ptr = __काष्ठा_ptr(sbi, a->काष्ठा_type);
	अगर (!ptr)
		वापस -EINVAL;

	अगर (!म_भेद(a->attr.name, "extension_list")) अणु
		__u8 (*extlist)[F2FS_EXTENSION_LEN] =
					sbi->raw_super->extension_list;
		पूर्णांक cold_count = le32_to_cpu(sbi->raw_super->extension_count);
		पूर्णांक hot_count = sbi->raw_super->hot_ext_count;
		पूर्णांक len = 0, i;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
						"cold file extension:\n");
		क्रम (i = 0; i < cold_count; i++)
			len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s\n",
								extlist[i]);

		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
						"hot file extension:\n");
		क्रम (i = cold_count; i < cold_count + hot_count; i++)
			len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%s\n",
								extlist[i]);
		वापस len;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "ckpt_thread_ioprio")) अणु
		काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;
		पूर्णांक len = 0;
		पूर्णांक class = IOPRIO_PRIO_CLASS(cprc->ckpt_thपढ़ो_ioprio);
		पूर्णांक data = IOPRIO_PRIO_DATA(cprc->ckpt_thपढ़ो_ioprio);

		अगर (class == IOPRIO_CLASS_RT)
			len += scnम_लिखो(buf + len, PAGE_SIZE - len, "rt,");
		अन्यथा अगर (class == IOPRIO_CLASS_BE)
			len += scnम_लिखो(buf + len, PAGE_SIZE - len, "be,");
		अन्यथा
			वापस -EINVAL;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d\n", data);
		वापस len;
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (!म_भेद(a->attr.name, "compr_written_block"))
		वापस sysfs_emit(buf, "%llu\n", sbi->compr_written_block);

	अगर (!म_भेद(a->attr.name, "compr_saved_block"))
		वापस sysfs_emit(buf, "%llu\n", sbi->compr_saved_block);

	अगर (!म_भेद(a->attr.name, "compr_new_inode"))
		वापस sysfs_emit(buf, "%u\n", sbi->compr_new_inode);
#पूर्ण_अगर

	ui = (अचिन्हित पूर्णांक *)(ptr + a->offset);

	वापस प्र_लिखो(buf, "%u\n", *ui);
पूर्ण

अटल sमाप_प्रकार __sbi_store(काष्ठा f2fs_attr *a,
			काष्ठा f2fs_sb_info *sbi,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित अक्षर *ptr;
	अचिन्हित दीर्घ t;
	अचिन्हित पूर्णांक *ui;
	sमाप_प्रकार ret;

	ptr = __काष्ठा_ptr(sbi, a->काष्ठा_type);
	अगर (!ptr)
		वापस -EINVAL;

	अगर (!म_भेद(a->attr.name, "extension_list")) अणु
		स्थिर अक्षर *name = strim((अक्षर *)buf);
		bool set = true, hot;

		अगर (!म_भेदन(name, "[h]", 3))
			hot = true;
		अन्यथा अगर (!म_भेदन(name, "[c]", 3))
			hot = false;
		अन्यथा
			वापस -EINVAL;

		name += 3;

		अगर (*name == '!') अणु
			name++;
			set = false;
		पूर्ण

		अगर (म_माप(name) >= F2FS_EXTENSION_LEN)
			वापस -EINVAL;

		करोwn_ग_लिखो(&sbi->sb_lock);

		ret = f2fs_update_extension_list(sbi, name, hot, set);
		अगर (ret)
			जाओ out;

		ret = f2fs_commit_super(sbi, false);
		अगर (ret)
			f2fs_update_extension_list(sbi, name, hot, !set);
out:
		up_ग_लिखो(&sbi->sb_lock);
		वापस ret ? ret : count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "ckpt_thread_ioprio")) अणु
		स्थिर अक्षर *name = strim((अक्षर *)buf);
		काष्ठा ckpt_req_control *cprc = &sbi->cprc_info;
		पूर्णांक class;
		दीर्घ data;
		पूर्णांक ret;

		अगर (!म_भेदन(name, "rt,", 3))
			class = IOPRIO_CLASS_RT;
		अन्यथा अगर (!म_भेदन(name, "be,", 3))
			class = IOPRIO_CLASS_BE;
		अन्यथा
			वापस -EINVAL;

		name += 3;
		ret = kम_से_दीर्घ(name, 10, &data);
		अगर (ret)
			वापस ret;
		अगर (data >= IOPRIO_BE_NR || data < 0)
			वापस -EINVAL;

		cprc->ckpt_thपढ़ो_ioprio = IOPRIO_PRIO_VALUE(class, data);
		अगर (test_opt(sbi, MERGE_CHECKPOINT)) अणु
			ret = set_task_ioprio(cprc->f2fs_issue_ckpt,
					cprc->ckpt_thपढ़ो_ioprio);
			अगर (ret)
				वापस ret;
		पूर्ण

		वापस count;
	पूर्ण

	ui = (अचिन्हित पूर्णांक *)(ptr + a->offset);

	ret = kम_से_अदीर्घ(skip_spaces(buf), 0, &t);
	अगर (ret < 0)
		वापस ret;
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	अगर (a->काष्ठा_type == FAULT_INFO_TYPE && t >= (1 << FAULT_MAX))
		वापस -EINVAL;
	अगर (a->काष्ठा_type == FAULT_INFO_RATE && t >= अच_पूर्णांक_उच्च)
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (a->काष्ठा_type == RESERVED_BLOCKS) अणु
		spin_lock(&sbi->stat_lock);
		अगर (t > (अचिन्हित दीर्घ)(sbi->user_block_count -
				F2FS_OPTION(sbi).root_reserved_blocks)) अणु
			spin_unlock(&sbi->stat_lock);
			वापस -EINVAL;
		पूर्ण
		*ui = t;
		sbi->current_reserved_blocks = min(sbi->reserved_blocks,
				sbi->user_block_count - valid_user_blocks(sbi));
		spin_unlock(&sbi->stat_lock);
		वापस count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "discard_granularity")) अणु
		अगर (t == 0 || t > MAX_PLIST_NUM)
			वापस -EINVAL;
		अगर (t == *ui)
			वापस count;
		*ui = t;
		वापस count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "migration_granularity")) अणु
		अगर (t == 0 || t > sbi->segs_per_sec)
			वापस -EINVAL;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "trim_sections"))
		वापस -EINVAL;

	अगर (!म_भेद(a->attr.name, "gc_urgent")) अणु
		अगर (t == 0) अणु
			sbi->gc_mode = GC_NORMAL;
		पूर्ण अन्यथा अगर (t == 1) अणु
			sbi->gc_mode = GC_URGENT_HIGH;
			अगर (sbi->gc_thपढ़ो) अणु
				sbi->gc_thपढ़ो->gc_wake = 1;
				wake_up_पूर्णांकerruptible_all(
					&sbi->gc_thपढ़ो->gc_रुको_queue_head);
				wake_up_discard_thपढ़ो(sbi, true);
			पूर्ण
		पूर्ण अन्यथा अगर (t == 2) अणु
			sbi->gc_mode = GC_URGENT_LOW;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		वापस count;
	पूर्ण
	अगर (!म_भेद(a->attr.name, "gc_idle")) अणु
		अगर (t == GC_IDLE_CB) अणु
			sbi->gc_mode = GC_IDLE_CB;
		पूर्ण अन्यथा अगर (t == GC_IDLE_GREEDY) अणु
			sbi->gc_mode = GC_IDLE_GREEDY;
		पूर्ण अन्यथा अगर (t == GC_IDLE_AT) अणु
			अगर (!sbi->am.atgc_enabled)
				वापस -EINVAL;
			sbi->gc_mode = GC_AT;
		पूर्ण अन्यथा अणु
			sbi->gc_mode = GC_NORMAL;
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "iostat_enable")) अणु
		sbi->iostat_enable = !!t;
		अगर (!sbi->iostat_enable)
			f2fs_reset_iostat(sbi);
		वापस count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "iostat_period_ms")) अणु
		अगर (t < MIN_IOSTAT_PERIOD_MS || t > MAX_IOSTAT_PERIOD_MS)
			वापस -EINVAL;
		spin_lock(&sbi->iostat_lock);
		sbi->iostat_period_ms = (अचिन्हित पूर्णांक)t;
		spin_unlock(&sbi->iostat_lock);
		वापस count;
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (!म_भेद(a->attr.name, "compr_written_block") ||
		!म_भेद(a->attr.name, "compr_saved_block")) अणु
		अगर (t != 0)
			वापस -EINVAL;
		sbi->compr_written_block = 0;
		sbi->compr_saved_block = 0;
		वापस count;
	पूर्ण

	अगर (!म_भेद(a->attr.name, "compr_new_inode")) अणु
		अगर (t != 0)
			वापस -EINVAL;
		sbi->compr_new_inode = 0;
		वापस count;
	पूर्ण
#पूर्ण_अगर

	*ui = (अचिन्हित पूर्णांक)t;

	वापस count;
पूर्ण

अटल sमाप_प्रकार f2fs_sbi_store(काष्ठा f2fs_attr *a,
			काष्ठा f2fs_sb_info *sbi,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
	bool gc_entry = (!म_भेद(a->attr.name, "gc_urgent") ||
					a->काष्ठा_type == GC_THREAD);

	अगर (gc_entry) अणु
		अगर (!करोwn_पढ़ो_trylock(&sbi->sb->s_umount))
			वापस -EAGAIN;
	पूर्ण
	ret = __sbi_store(a, sbi, buf, count);
	अगर (gc_entry)
		up_पढ़ो(&sbi->sb->s_umount);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार f2fs_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
								s_kobj);
	काष्ठा f2fs_attr *a = container_of(attr, काष्ठा f2fs_attr, attr);

	वापस a->show ? a->show(a, sbi, buf) : 0;
पूर्ण

अटल sमाप_प्रकार f2fs_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
									s_kobj);
	काष्ठा f2fs_attr *a = container_of(attr, काष्ठा f2fs_attr, attr);

	वापस a->store ? a->store(a, sbi, buf, len) : 0;
पूर्ण

अटल व्योम f2fs_sb_release(काष्ठा kobject *kobj)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
								s_kobj);
	complete(&sbi->s_kobj_unरेजिस्टर);
पूर्ण

क्रमागत feat_id अणु
	FEAT_CRYPTO = 0,
	FEAT_BLKZONED,
	FEAT_ATOMIC_WRITE,
	FEAT_EXTRA_ATTR,
	FEAT_PROJECT_QUOTA,
	FEAT_INODE_CHECKSUM,
	FEAT_FLEXIBLE_INLINE_XATTR,
	FEAT_QUOTA_INO,
	FEAT_INODE_CRTIME,
	FEAT_LOST_FOUND,
	FEAT_VERITY,
	FEAT_SB_CHECKSUM,
	FEAT_CASEFOLD,
	FEAT_COMPRESSION,
	FEAT_TEST_DUMMY_ENCRYPTION_V2,
पूर्ण;

अटल sमाप_प्रकार f2fs_feature_show(काष्ठा f2fs_attr *a,
		काष्ठा f2fs_sb_info *sbi, अक्षर *buf)
अणु
	चयन (a->id) अणु
	हाल FEAT_CRYPTO:
	हाल FEAT_BLKZONED:
	हाल FEAT_ATOMIC_WRITE:
	हाल FEAT_EXTRA_ATTR:
	हाल FEAT_PROJECT_QUOTA:
	हाल FEAT_INODE_CHECKSUM:
	हाल FEAT_FLEXIBLE_INLINE_XATTR:
	हाल FEAT_QUOTA_INO:
	हाल FEAT_INODE_CRTIME:
	हाल FEAT_LOST_FOUND:
	हाल FEAT_VERITY:
	हाल FEAT_SB_CHECKSUM:
	हाल FEAT_CASEFOLD:
	हाल FEAT_COMPRESSION:
	हाल FEAT_TEST_DUMMY_ENCRYPTION_V2:
		वापस प्र_लिखो(buf, "supported\n");
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा F2FS_ATTR_OFFSET(_काष्ठा_type, _name, _mode, _show, _store, _offset) \
अटल काष्ठा f2fs_attr f2fs_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.show	= _show,					\
	.store	= _store,					\
	.काष्ठा_type = _काष्ठा_type,				\
	.offset = _offset					\
पूर्ण

#घोषणा F2FS_RW_ATTR(काष्ठा_type, काष्ठा_name, name, elname)	\
	F2FS_ATTR_OFFSET(काष्ठा_type, name, 0644,		\
		f2fs_sbi_show, f2fs_sbi_store,			\
		दुरत्व(काष्ठा काष्ठा_name, elname))

#घोषणा F2FS_GENERAL_RO_ATTR(name) \
अटल काष्ठा f2fs_attr f2fs_attr_##name = __ATTR(name, 0444, name##_show, शून्य)

#घोषणा F2FS_FEATURE_RO_ATTR(_name, _id)			\
अटल काष्ठा f2fs_attr f2fs_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = 0444 पूर्ण,	\
	.show	= f2fs_feature_show,				\
	.id	= _id,						\
पूर्ण

#घोषणा F2FS_STAT_ATTR(_काष्ठा_type, _काष्ठा_name, _name, _elname)	\
अटल काष्ठा f2fs_attr f2fs_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = 0444 पूर्ण,	\
	.show = f2fs_sbi_show,					\
	.काष्ठा_type = _काष्ठा_type,				\
	.offset = दुरत्व(काष्ठा _काष्ठा_name, _elname),       \
पूर्ण

F2FS_RW_ATTR(GC_THREAD, f2fs_gc_kthपढ़ो, gc_urgent_sleep_समय,
							urgent_sleep_समय);
F2FS_RW_ATTR(GC_THREAD, f2fs_gc_kthपढ़ो, gc_min_sleep_समय, min_sleep_समय);
F2FS_RW_ATTR(GC_THREAD, f2fs_gc_kthपढ़ो, gc_max_sleep_समय, max_sleep_समय);
F2FS_RW_ATTR(GC_THREAD, f2fs_gc_kthपढ़ो, gc_no_gc_sleep_समय, no_gc_sleep_समय);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, gc_idle, gc_mode);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, gc_urgent, gc_mode);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, reclaim_segments, rec_preमुक्त_segments);
F2FS_RW_ATTR(DCC_INFO, discard_cmd_control, max_small_discards, max_discards);
F2FS_RW_ATTR(DCC_INFO, discard_cmd_control, discard_granularity, discard_granularity);
F2FS_RW_ATTR(RESERVED_BLOCKS, f2fs_sb_info, reserved_blocks, reserved_blocks);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, batched_trim_sections, trim_sections);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, ipu_policy, ipu_policy);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, min_ipu_util, min_ipu_util);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, min_fsync_blocks, min_fsync_blocks);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, min_seq_blocks, min_seq_blocks);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, min_hot_blocks, min_hot_blocks);
F2FS_RW_ATTR(SM_INFO, f2fs_sm_info, min_ssr_sections, min_ssr_sections);
F2FS_RW_ATTR(NM_INFO, f2fs_nm_info, ram_thresh, ram_thresh);
F2FS_RW_ATTR(NM_INFO, f2fs_nm_info, ra_nid_pages, ra_nid_pages);
F2FS_RW_ATTR(NM_INFO, f2fs_nm_info, dirty_nats_ratio, dirty_nats_ratio);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, max_victim_search, max_victim_search);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, migration_granularity, migration_granularity);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, dir_level, dir_level);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, cp_पूर्णांकerval, पूर्णांकerval_समय[CP_TIME]);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, idle_पूर्णांकerval, पूर्णांकerval_समय[REQ_TIME]);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, discard_idle_पूर्णांकerval,
					पूर्णांकerval_समय[DISCARD_TIME]);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, gc_idle_पूर्णांकerval, पूर्णांकerval_समय[GC_TIME]);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info,
		umount_discard_समयout, पूर्णांकerval_समय[UMOUNT_DISCARD_TIMEOUT]);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, iostat_enable, iostat_enable);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, iostat_period_ms, iostat_period_ms);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, सूची_पढ़ो_ra, सूची_पढ़ो_ra);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, max_io_bytes, max_io_bytes);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, gc_pin_file_thresh, gc_pin_file_threshold);
F2FS_RW_ATTR(F2FS_SBI, f2fs_super_block, extension_list, extension_list);
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
F2FS_RW_ATTR(FAULT_INFO_RATE, f2fs_fault_info, inject_rate, inject_rate);
F2FS_RW_ATTR(FAULT_INFO_TYPE, f2fs_fault_info, inject_type, inject_type);
#पूर्ण_अगर
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, data_io_flag, data_io_flag);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, node_io_flag, node_io_flag);
F2FS_RW_ATTR(CPRC_INFO, ckpt_req_control, ckpt_thपढ़ो_ioprio, ckpt_thपढ़ो_ioprio);
F2FS_GENERAL_RO_ATTR(dirty_segments);
F2FS_GENERAL_RO_ATTR(मुक्त_segments);
F2FS_GENERAL_RO_ATTR(ovp_segments);
F2FS_GENERAL_RO_ATTR(lअगरeसमय_ग_लिखो_kbytes);
F2FS_GENERAL_RO_ATTR(features);
F2FS_GENERAL_RO_ATTR(current_reserved_blocks);
F2FS_GENERAL_RO_ATTR(unusable);
F2FS_GENERAL_RO_ATTR(encoding);
F2FS_GENERAL_RO_ATTR(mounted_समय_sec);
F2FS_GENERAL_RO_ATTR(मुख्य_blkaddr);
#अगर_घोषित CONFIG_F2FS_STAT_FS
F2FS_STAT_ATTR(STAT_INFO, f2fs_stat_info, cp_क्रमeground_calls, cp_count);
F2FS_STAT_ATTR(STAT_INFO, f2fs_stat_info, cp_background_calls, bg_cp_count);
F2FS_STAT_ATTR(STAT_INFO, f2fs_stat_info, gc_क्रमeground_calls, call_count);
F2FS_STAT_ATTR(STAT_INFO, f2fs_stat_info, gc_background_calls, bg_gc);
F2FS_GENERAL_RO_ATTR(moved_blocks_background);
F2FS_GENERAL_RO_ATTR(moved_blocks_क्रमeground);
F2FS_GENERAL_RO_ATTR(avg_vblocks);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FS_ENCRYPTION
F2FS_FEATURE_RO_ATTR(encryption, FEAT_CRYPTO);
F2FS_FEATURE_RO_ATTR(test_dummy_encryption_v2, FEAT_TEST_DUMMY_ENCRYPTION_V2);
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLK_DEV_ZONED
F2FS_FEATURE_RO_ATTR(block_zoned, FEAT_BLKZONED);
#पूर्ण_अगर
F2FS_FEATURE_RO_ATTR(atomic_ग_लिखो, FEAT_ATOMIC_WRITE);
F2FS_FEATURE_RO_ATTR(extra_attr, FEAT_EXTRA_ATTR);
F2FS_FEATURE_RO_ATTR(project_quota, FEAT_PROJECT_QUOTA);
F2FS_FEATURE_RO_ATTR(inode_checksum, FEAT_INODE_CHECKSUM);
F2FS_FEATURE_RO_ATTR(flexible_अंतरभूत_xattr, FEAT_FLEXIBLE_INLINE_XATTR);
F2FS_FEATURE_RO_ATTR(quota_ino, FEAT_QUOTA_INO);
F2FS_FEATURE_RO_ATTR(inode_crसमय, FEAT_INODE_CRTIME);
F2FS_FEATURE_RO_ATTR(lost_found, FEAT_LOST_FOUND);
#अगर_घोषित CONFIG_FS_VERITY
F2FS_FEATURE_RO_ATTR(verity, FEAT_VERITY);
#पूर्ण_अगर
F2FS_FEATURE_RO_ATTR(sb_checksum, FEAT_SB_CHECKSUM);
F2FS_FEATURE_RO_ATTR(हालfold, FEAT_CASEFOLD);
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
F2FS_FEATURE_RO_ATTR(compression, FEAT_COMPRESSION);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, compr_written_block, compr_written_block);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, compr_saved_block, compr_saved_block);
F2FS_RW_ATTR(F2FS_SBI, f2fs_sb_info, compr_new_inode, compr_new_inode);
#पूर्ण_अगर

#घोषणा ATTR_LIST(name) (&f2fs_attr_##name.attr)
अटल काष्ठा attribute *f2fs_attrs[] = अणु
	ATTR_LIST(gc_urgent_sleep_समय),
	ATTR_LIST(gc_min_sleep_समय),
	ATTR_LIST(gc_max_sleep_समय),
	ATTR_LIST(gc_no_gc_sleep_समय),
	ATTR_LIST(gc_idle),
	ATTR_LIST(gc_urgent),
	ATTR_LIST(reclaim_segments),
	ATTR_LIST(मुख्य_blkaddr),
	ATTR_LIST(max_small_discards),
	ATTR_LIST(discard_granularity),
	ATTR_LIST(batched_trim_sections),
	ATTR_LIST(ipu_policy),
	ATTR_LIST(min_ipu_util),
	ATTR_LIST(min_fsync_blocks),
	ATTR_LIST(min_seq_blocks),
	ATTR_LIST(min_hot_blocks),
	ATTR_LIST(min_ssr_sections),
	ATTR_LIST(max_victim_search),
	ATTR_LIST(migration_granularity),
	ATTR_LIST(dir_level),
	ATTR_LIST(ram_thresh),
	ATTR_LIST(ra_nid_pages),
	ATTR_LIST(dirty_nats_ratio),
	ATTR_LIST(cp_पूर्णांकerval),
	ATTR_LIST(idle_पूर्णांकerval),
	ATTR_LIST(discard_idle_पूर्णांकerval),
	ATTR_LIST(gc_idle_पूर्णांकerval),
	ATTR_LIST(umount_discard_समयout),
	ATTR_LIST(iostat_enable),
	ATTR_LIST(iostat_period_ms),
	ATTR_LIST(सूची_पढ़ो_ra),
	ATTR_LIST(max_io_bytes),
	ATTR_LIST(gc_pin_file_thresh),
	ATTR_LIST(extension_list),
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	ATTR_LIST(inject_rate),
	ATTR_LIST(inject_type),
#पूर्ण_अगर
	ATTR_LIST(data_io_flag),
	ATTR_LIST(node_io_flag),
	ATTR_LIST(ckpt_thपढ़ो_ioprio),
	ATTR_LIST(dirty_segments),
	ATTR_LIST(मुक्त_segments),
	ATTR_LIST(ovp_segments),
	ATTR_LIST(unusable),
	ATTR_LIST(lअगरeसमय_ग_लिखो_kbytes),
	ATTR_LIST(features),
	ATTR_LIST(reserved_blocks),
	ATTR_LIST(current_reserved_blocks),
	ATTR_LIST(encoding),
	ATTR_LIST(mounted_समय_sec),
#अगर_घोषित CONFIG_F2FS_STAT_FS
	ATTR_LIST(cp_क्रमeground_calls),
	ATTR_LIST(cp_background_calls),
	ATTR_LIST(gc_क्रमeground_calls),
	ATTR_LIST(gc_background_calls),
	ATTR_LIST(moved_blocks_क्रमeground),
	ATTR_LIST(moved_blocks_background),
	ATTR_LIST(avg_vblocks),
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	ATTR_LIST(compr_written_block),
	ATTR_LIST(compr_saved_block),
	ATTR_LIST(compr_new_inode),
#पूर्ण_अगर
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(f2fs);

अटल काष्ठा attribute *f2fs_feat_attrs[] = अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	ATTR_LIST(encryption),
	ATTR_LIST(test_dummy_encryption_v2),
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	ATTR_LIST(block_zoned),
#पूर्ण_अगर
	ATTR_LIST(atomic_ग_लिखो),
	ATTR_LIST(extra_attr),
	ATTR_LIST(project_quota),
	ATTR_LIST(inode_checksum),
	ATTR_LIST(flexible_अंतरभूत_xattr),
	ATTR_LIST(quota_ino),
	ATTR_LIST(inode_crसमय),
	ATTR_LIST(lost_found),
#अगर_घोषित CONFIG_FS_VERITY
	ATTR_LIST(verity),
#पूर्ण_अगर
	ATTR_LIST(sb_checksum),
	ATTR_LIST(हालfold),
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	ATTR_LIST(compression),
#पूर्ण_अगर
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(f2fs_feat);

F2FS_GENERAL_RO_ATTR(sb_status);
अटल काष्ठा attribute *f2fs_stat_attrs[] = अणु
	ATTR_LIST(sb_status),
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(f2fs_stat);

अटल स्थिर काष्ठा sysfs_ops f2fs_attr_ops = अणु
	.show	= f2fs_attr_show,
	.store	= f2fs_attr_store,
पूर्ण;

अटल काष्ठा kobj_type f2fs_sb_ktype = अणु
	.शेष_groups = f2fs_groups,
	.sysfs_ops	= &f2fs_attr_ops,
	.release	= f2fs_sb_release,
पूर्ण;

अटल काष्ठा kobj_type f2fs_ktype = अणु
	.sysfs_ops	= &f2fs_attr_ops,
पूर्ण;

अटल काष्ठा kset f2fs_kset = अणु
	.kobj	= अणु.ktype = &f2fs_ktypeपूर्ण,
पूर्ण;

अटल काष्ठा kobj_type f2fs_feat_ktype = अणु
	.शेष_groups = f2fs_feat_groups,
	.sysfs_ops	= &f2fs_attr_ops,
पूर्ण;

अटल काष्ठा kobject f2fs_feat = अणु
	.kset	= &f2fs_kset,
पूर्ण;

अटल sमाप_प्रकार f2fs_stat_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
								s_stat_kobj);
	काष्ठा f2fs_attr *a = container_of(attr, काष्ठा f2fs_attr, attr);

	वापस a->show ? a->show(a, sbi, buf) : 0;
पूर्ण

अटल sमाप_प्रकार f2fs_stat_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
								s_stat_kobj);
	काष्ठा f2fs_attr *a = container_of(attr, काष्ठा f2fs_attr, attr);

	वापस a->store ? a->store(a, sbi, buf, len) : 0;
पूर्ण

अटल व्योम f2fs_stat_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा f2fs_sb_info *sbi = container_of(kobj, काष्ठा f2fs_sb_info,
								s_stat_kobj);
	complete(&sbi->s_stat_kobj_unरेजिस्टर);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops f2fs_stat_attr_ops = अणु
	.show	= f2fs_stat_attr_show,
	.store	= f2fs_stat_attr_store,
पूर्ण;

अटल काष्ठा kobj_type f2fs_stat_ktype = अणु
	.शेष_groups = f2fs_stat_groups,
	.sysfs_ops	= &f2fs_stat_attr_ops,
	.release	= f2fs_stat_kobj_release,
पूर्ण;

अटल पूर्णांक __maybe_unused segment_info_seq_show(काष्ठा seq_file *seq,
						व्योम *offset)
अणु
	काष्ठा super_block *sb = seq->निजी;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	अचिन्हित पूर्णांक total_segs =
			le32_to_cpu(sbi->raw_super->segment_count_मुख्य);
	पूर्णांक i;

	seq_माला_दो(seq, "format: segment_type|valid_blocks\n"
		"segment_type(0:HD, 1:WD, 2:CD, 3:HN, 4:WN, 5:CN)\n");

	क्रम (i = 0; i < total_segs; i++) अणु
		काष्ठा seg_entry *se = get_seg_entry(sbi, i);

		अगर ((i % 10) == 0)
			seq_म_लिखो(seq, "%-10d", i);
		seq_म_लिखो(seq, "%d|%-3u", se->type, se->valid_blocks);
		अगर ((i % 10) == 9 || i == (total_segs - 1))
			seq_अ_दो(seq, '\n');
		अन्यथा
			seq_अ_दो(seq, ' ');
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused segment_bits_seq_show(काष्ठा seq_file *seq,
						व्योम *offset)
अणु
	काष्ठा super_block *sb = seq->निजी;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	अचिन्हित पूर्णांक total_segs =
			le32_to_cpu(sbi->raw_super->segment_count_मुख्य);
	पूर्णांक i, j;

	seq_माला_दो(seq, "format: segment_type|valid_blocks|bitmaps\n"
		"segment_type(0:HD, 1:WD, 2:CD, 3:HN, 4:WN, 5:CN)\n");

	क्रम (i = 0; i < total_segs; i++) अणु
		काष्ठा seg_entry *se = get_seg_entry(sbi, i);

		seq_म_लिखो(seq, "%-10d", i);
		seq_म_लिखो(seq, "%d|%-3u|", se->type, se->valid_blocks);
		क्रम (j = 0; j < SIT_VBLOCK_MAP_SIZE; j++)
			seq_म_लिखो(seq, " %.2x", se->cur_valid_map[j]);
		seq_अ_दो(seq, '\n');
	पूर्ण
	वापस 0;
पूर्ण

व्योम f2fs_record_iostat(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित दीर्घ दीर्घ iostat_dअगरf[NR_IO_TYPE];
	पूर्णांक i;

	अगर (समय_is_after_jअगरfies(sbi->iostat_next_period))
		वापस;

	/* Need द्विगुन check under the lock */
	spin_lock(&sbi->iostat_lock);
	अगर (समय_is_after_jअगरfies(sbi->iostat_next_period)) अणु
		spin_unlock(&sbi->iostat_lock);
		वापस;
	पूर्ण
	sbi->iostat_next_period = jअगरfies +
				msecs_to_jअगरfies(sbi->iostat_period_ms);

	क्रम (i = 0; i < NR_IO_TYPE; i++) अणु
		iostat_dअगरf[i] = sbi->rw_iostat[i] -
				sbi->prev_rw_iostat[i];
		sbi->prev_rw_iostat[i] = sbi->rw_iostat[i];
	पूर्ण
	spin_unlock(&sbi->iostat_lock);

	trace_f2fs_iostat(sbi, iostat_dअगरf);
पूर्ण

अटल पूर्णांक __maybe_unused iostat_info_seq_show(काष्ठा seq_file *seq,
					       व्योम *offset)
अणु
	काष्ठा super_block *sb = seq->निजी;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	समय64_t now = kसमय_get_real_seconds();

	अगर (!sbi->iostat_enable)
		वापस 0;

	seq_म_लिखो(seq, "time:		%-16llu\n", now);

	/* prपूर्णांक app ग_लिखो IOs */
	seq_माला_दो(seq, "[WRITE]\n");
	seq_म_लिखो(seq, "app buffered:	%-16llu\n",
				sbi->rw_iostat[APP_BUFFERED_IO]);
	seq_म_लिखो(seq, "app direct:	%-16llu\n",
				sbi->rw_iostat[APP_सूचीECT_IO]);
	seq_म_लिखो(seq, "app mapped:	%-16llu\n",
				sbi->rw_iostat[APP_MAPPED_IO]);

	/* prपूर्णांक fs ग_लिखो IOs */
	seq_म_लिखो(seq, "fs data:	%-16llu\n",
				sbi->rw_iostat[FS_DATA_IO]);
	seq_म_लिखो(seq, "fs node:	%-16llu\n",
				sbi->rw_iostat[FS_NODE_IO]);
	seq_म_लिखो(seq, "fs meta:	%-16llu\n",
				sbi->rw_iostat[FS_META_IO]);
	seq_म_लिखो(seq, "fs gc data:	%-16llu\n",
				sbi->rw_iostat[FS_GC_DATA_IO]);
	seq_म_लिखो(seq, "fs gc node:	%-16llu\n",
				sbi->rw_iostat[FS_GC_NODE_IO]);
	seq_म_लिखो(seq, "fs cp data:	%-16llu\n",
				sbi->rw_iostat[FS_CP_DATA_IO]);
	seq_म_लिखो(seq, "fs cp node:	%-16llu\n",
				sbi->rw_iostat[FS_CP_NODE_IO]);
	seq_म_लिखो(seq, "fs cp meta:	%-16llu\n",
				sbi->rw_iostat[FS_CP_META_IO]);

	/* prपूर्णांक app पढ़ो IOs */
	seq_माला_दो(seq, "[READ]\n");
	seq_म_लिखो(seq, "app buffered:	%-16llu\n",
				sbi->rw_iostat[APP_BUFFERED_READ_IO]);
	seq_म_लिखो(seq, "app direct:	%-16llu\n",
				sbi->rw_iostat[APP_सूचीECT_READ_IO]);
	seq_म_लिखो(seq, "app mapped:	%-16llu\n",
				sbi->rw_iostat[APP_MAPPED_READ_IO]);

	/* prपूर्णांक fs पढ़ो IOs */
	seq_म_लिखो(seq, "fs data:	%-16llu\n",
				sbi->rw_iostat[FS_DATA_READ_IO]);
	seq_म_लिखो(seq, "fs gc data:	%-16llu\n",
				sbi->rw_iostat[FS_GDATA_READ_IO]);
	seq_म_लिखो(seq, "fs compr_data:	%-16llu\n",
				sbi->rw_iostat[FS_CDATA_READ_IO]);
	seq_म_लिखो(seq, "fs node:	%-16llu\n",
				sbi->rw_iostat[FS_NODE_READ_IO]);
	seq_म_लिखो(seq, "fs meta:	%-16llu\n",
				sbi->rw_iostat[FS_META_READ_IO]);

	/* prपूर्णांक other IOs */
	seq_माला_दो(seq, "[OTHER]\n");
	seq_म_लिखो(seq, "fs discard:	%-16llu\n",
				sbi->rw_iostat[FS_DISCARD]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused victim_bits_seq_show(काष्ठा seq_file *seq,
						व्योम *offset)
अणु
	काष्ठा super_block *sb = seq->निजी;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	पूर्णांक i;

	seq_माला_दो(seq, "format: victim_secmap bitmaps\n");

	क्रम (i = 0; i < MAIN_SECS(sbi); i++) अणु
		अगर ((i % 10) == 0)
			seq_म_लिखो(seq, "%-10d", i);
		seq_म_लिखो(seq, "%d", test_bit(i, dirty_i->victim_secmap) ? 1 : 0);
		अगर ((i % 10) == 9 || i == (MAIN_SECS(sbi) - 1))
			seq_अ_दो(seq, '\n');
		अन्यथा
			seq_अ_दो(seq, ' ');
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init f2fs_init_sysfs(व्योम)
अणु
	पूर्णांक ret;

	kobject_set_name(&f2fs_kset.kobj, "f2fs");
	f2fs_kset.kobj.parent = fs_kobj;
	ret = kset_रेजिस्टर(&f2fs_kset);
	अगर (ret)
		वापस ret;

	ret = kobject_init_and_add(&f2fs_feat, &f2fs_feat_ktype,
				   शून्य, "features");
	अगर (ret) अणु
		kobject_put(&f2fs_feat);
		kset_unरेजिस्टर(&f2fs_kset);
	पूर्ण अन्यथा अणु
		f2fs_proc_root = proc_सूची_गढ़ो("fs/f2fs", शून्य);
	पूर्ण
	वापस ret;
पूर्ण

व्योम f2fs_निकास_sysfs(व्योम)
अणु
	kobject_put(&f2fs_feat);
	kset_unरेजिस्टर(&f2fs_kset);
	हटाओ_proc_entry("fs/f2fs", शून्य);
	f2fs_proc_root = शून्य;
पूर्ण

पूर्णांक f2fs_रेजिस्टर_sysfs(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा super_block *sb = sbi->sb;
	पूर्णांक err;

	sbi->s_kobj.kset = &f2fs_kset;
	init_completion(&sbi->s_kobj_unरेजिस्टर);
	err = kobject_init_and_add(&sbi->s_kobj, &f2fs_sb_ktype, शून्य,
				"%s", sb->s_id);
	अगर (err)
		जाओ put_sb_kobj;

	sbi->s_stat_kobj.kset = &f2fs_kset;
	init_completion(&sbi->s_stat_kobj_unरेजिस्टर);
	err = kobject_init_and_add(&sbi->s_stat_kobj, &f2fs_stat_ktype,
						&sbi->s_kobj, "stat");
	अगर (err)
		जाओ put_stat_kobj;

	अगर (f2fs_proc_root)
		sbi->s_proc = proc_सूची_गढ़ो(sb->s_id, f2fs_proc_root);

	अगर (sbi->s_proc) अणु
		proc_create_single_data("segment_info", S_IRUGO, sbi->s_proc,
				segment_info_seq_show, sb);
		proc_create_single_data("segment_bits", S_IRUGO, sbi->s_proc,
				segment_bits_seq_show, sb);
		proc_create_single_data("iostat_info", S_IRUGO, sbi->s_proc,
				iostat_info_seq_show, sb);
		proc_create_single_data("victim_bits", S_IRUGO, sbi->s_proc,
				victim_bits_seq_show, sb);
	पूर्ण
	वापस 0;
put_stat_kobj:
	kobject_put(&sbi->s_stat_kobj);
	रुको_क्रम_completion(&sbi->s_stat_kobj_unरेजिस्टर);
put_sb_kobj:
	kobject_put(&sbi->s_kobj);
	रुको_क्रम_completion(&sbi->s_kobj_unरेजिस्टर);
	वापस err;
पूर्ण

व्योम f2fs_unरेजिस्टर_sysfs(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (sbi->s_proc) अणु
		हटाओ_proc_entry("iostat_info", sbi->s_proc);
		हटाओ_proc_entry("segment_info", sbi->s_proc);
		हटाओ_proc_entry("segment_bits", sbi->s_proc);
		हटाओ_proc_entry("victim_bits", sbi->s_proc);
		हटाओ_proc_entry(sbi->sb->s_id, f2fs_proc_root);
	पूर्ण

	kobject_del(&sbi->s_stat_kobj);
	kobject_put(&sbi->s_stat_kobj);
	रुको_क्रम_completion(&sbi->s_stat_kobj_unरेजिस्टर);

	kobject_del(&sbi->s_kobj);
	kobject_put(&sbi->s_kobj);
	रुको_क्रम_completion(&sbi->s_kobj_unरेजिस्टर);
पूर्ण
