<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/sysfs.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Theoकरोre Ts'o (tytso@mit.edu)
 *
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/part_स्थिति.स>

#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"

प्रकार क्रमागत अणु
	attr_noop,
	attr_delayed_allocation_blocks,
	attr_session_ग_लिखो_kbytes,
	attr_lअगरeसमय_ग_लिखो_kbytes,
	attr_reserved_clusters,
	attr_sra_exceeded_retry_limit,
	attr_inode_पढ़ोahead,
	attr_trigger_test_error,
	attr_first_error_समय,
	attr_last_error_समय,
	attr_feature,
	attr_poपूर्णांकer_ui,
	attr_poपूर्णांकer_ul,
	attr_poपूर्णांकer_u64,
	attr_poपूर्णांकer_u8,
	attr_poपूर्णांकer_string,
	attr_poपूर्णांकer_atomic,
	attr_journal_task,
पूर्ण attr_id_t;

प्रकार क्रमागत अणु
	ptr_explicit,
	ptr_ext4_sb_info_offset,
	ptr_ext4_super_block_offset,
पूर्ण attr_ptr_t;

अटल स्थिर अक्षर proc_स_नाम[] = "fs/ext4";
अटल काष्ठा proc_dir_entry *ext4_proc_root;

काष्ठा ext4_attr अणु
	काष्ठा attribute attr;
	लघु attr_id;
	लघु attr_ptr;
	अचिन्हित लघु attr_size;
	जोड़ अणु
		पूर्णांक offset;
		व्योम *explicit_ptr;
	पूर्ण u;
पूर्ण;

अटल sमाप_प्रकार session_ग_लिखो_kbytes_show(काष्ठा ext4_sb_info *sbi, अक्षर *buf)
अणु
	काष्ठा super_block *sb = sbi->s_buddy_cache->i_sb;

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n",
			(part_stat_पढ़ो(sb->s_bdev, sectors[STAT_WRITE]) -
			 sbi->s_sectors_written_start) >> 1);
पूर्ण

अटल sमाप_प्रकार lअगरeसमय_ग_लिखो_kbytes_show(काष्ठा ext4_sb_info *sbi, अक्षर *buf)
अणु
	काष्ठा super_block *sb = sbi->s_buddy_cache->i_sb;

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)(sbi->s_kbytes_written +
			((part_stat_पढ़ो(sb->s_bdev, sectors[STAT_WRITE]) -
			  EXT4_SB(sb)->s_sectors_written_start) >> 1)));
पूर्ण

अटल sमाप_प्रकार inode_पढ़ोahead_blks_store(काष्ठा ext4_sb_info *sbi,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(skip_spaces(buf), 0, &t);
	अगर (ret)
		वापस ret;

	अगर (t && (!is_घातer_of_2(t) || t > 0x40000000))
		वापस -EINVAL;

	sbi->s_inode_पढ़ोahead_blks = t;
	वापस count;
पूर्ण

अटल sमाप_प्रकार reserved_clusters_store(काष्ठा ext4_sb_info *sbi,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	ext4_fsblk_t clusters = (ext4_blocks_count(sbi->s_es) >>
				 sbi->s_cluster_bits);
	पूर्णांक ret;

	ret = kम_से_अदीर्घl(skip_spaces(buf), 0, &val);
	अगर (ret || val >= clusters)
		वापस -EINVAL;

	atomic64_set(&sbi->s_resv_clusters, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार trigger_test_error(काष्ठा ext4_sb_info *sbi,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक len = count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (len && buf[len-1] == '\n')
		len--;

	अगर (len)
		ext4_error(sbi->s_sb, "%.*s", len, buf);
	वापस count;
पूर्ण

अटल sमाप_प्रकार journal_task_show(काष्ठा ext4_sb_info *sbi, अक्षर *buf)
अणु
	अगर (!sbi->s_journal)
		वापस snम_लिखो(buf, PAGE_SIZE, "<none>\n");
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			task_pid_vnr(sbi->s_journal->j_task));
पूर्ण

#घोषणा EXT4_ATTR(_name,_mode,_id)					\
अटल काष्ठा ext4_attr ext4_attr_##_name = अणु				\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,		\
	.attr_id = attr_##_id,						\
पूर्ण

#घोषणा EXT4_ATTR_FUNC(_name,_mode)  EXT4_ATTR(_name,_mode,_name)

#घोषणा EXT4_ATTR_FEATURE(_name)   EXT4_ATTR(_name, 0444, feature)

#घोषणा EXT4_ATTR_OFFSET(_name,_mode,_id,_काष्ठा,_elname)	\
अटल काष्ठा ext4_attr ext4_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.attr_id = attr_##_id,					\
	.attr_ptr = ptr_##_काष्ठा##_offset,			\
	.u = अणु							\
		.offset = दुरत्व(काष्ठा _काष्ठा, _elname),\
	पूर्ण,							\
पूर्ण

#घोषणा EXT4_ATTR_STRING(_name,_mode,_size,_काष्ठा,_elname)	\
अटल काष्ठा ext4_attr ext4_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.attr_id = attr_poपूर्णांकer_string,				\
	.attr_size = _size,					\
	.attr_ptr = ptr_##_काष्ठा##_offset,			\
	.u = अणु							\
		.offset = दुरत्व(काष्ठा _काष्ठा, _elname),\
	पूर्ण,							\
पूर्ण

#घोषणा EXT4_RO_ATTR_ES_UI(_name,_elname)				\
	EXT4_ATTR_OFFSET(_name, 0444, poपूर्णांकer_ui, ext4_super_block, _elname)

#घोषणा EXT4_RO_ATTR_ES_U8(_name,_elname)				\
	EXT4_ATTR_OFFSET(_name, 0444, poपूर्णांकer_u8, ext4_super_block, _elname)

#घोषणा EXT4_RO_ATTR_ES_U64(_name,_elname)				\
	EXT4_ATTR_OFFSET(_name, 0444, poपूर्णांकer_u64, ext4_super_block, _elname)

#घोषणा EXT4_RO_ATTR_ES_STRING(_name,_elname,_size)			\
	EXT4_ATTR_STRING(_name, 0444, _size, ext4_super_block, _elname)

#घोषणा EXT4_RW_ATTR_SBI_UI(_name,_elname)	\
	EXT4_ATTR_OFFSET(_name, 0644, poपूर्णांकer_ui, ext4_sb_info, _elname)

#घोषणा EXT4_RW_ATTR_SBI_UL(_name,_elname)	\
	EXT4_ATTR_OFFSET(_name, 0644, poपूर्णांकer_ul, ext4_sb_info, _elname)

#घोषणा EXT4_RO_ATTR_SBI_ATOMIC(_name,_elname)	\
	EXT4_ATTR_OFFSET(_name, 0444, poपूर्णांकer_atomic, ext4_sb_info, _elname)

#घोषणा EXT4_ATTR_PTR(_name,_mode,_id,_ptr) \
अटल काष्ठा ext4_attr ext4_attr_##_name = अणु			\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.attr_id = attr_##_id,					\
	.attr_ptr = ptr_explicit,				\
	.u = अणु							\
		.explicit_ptr = _ptr,				\
	पूर्ण,							\
पूर्ण

#घोषणा ATTR_LIST(name) &ext4_attr_##name.attr

EXT4_ATTR_FUNC(delayed_allocation_blocks, 0444);
EXT4_ATTR_FUNC(session_ग_लिखो_kbytes, 0444);
EXT4_ATTR_FUNC(lअगरeसमय_ग_लिखो_kbytes, 0444);
EXT4_ATTR_FUNC(reserved_clusters, 0644);
EXT4_ATTR_FUNC(sra_exceeded_retry_limit, 0444);

EXT4_ATTR_OFFSET(inode_पढ़ोahead_blks, 0644, inode_पढ़ोahead,
		 ext4_sb_info, s_inode_पढ़ोahead_blks);
EXT4_RW_ATTR_SBI_UI(inode_goal, s_inode_goal);
EXT4_RW_ATTR_SBI_UI(mb_stats, s_mb_stats);
EXT4_RW_ATTR_SBI_UI(mb_max_to_scan, s_mb_max_to_scan);
EXT4_RW_ATTR_SBI_UI(mb_min_to_scan, s_mb_min_to_scan);
EXT4_RW_ATTR_SBI_UI(mb_order2_req, s_mb_order2_reqs);
EXT4_RW_ATTR_SBI_UI(mb_stream_req, s_mb_stream_request);
EXT4_RW_ATTR_SBI_UI(mb_group_pपुनः_स्मृति, s_mb_group_pपुनः_स्मृति);
EXT4_RW_ATTR_SBI_UI(mb_max_inode_pपुनः_स्मृति, s_mb_max_inode_pपुनः_स्मृति);
EXT4_RW_ATTR_SBI_UI(mb_max_linear_groups, s_mb_max_linear_groups);
EXT4_RW_ATTR_SBI_UI(extent_max_zeroout_kb, s_extent_max_zeroout_kb);
EXT4_ATTR(trigger_fs_error, 0200, trigger_test_error);
EXT4_RW_ATTR_SBI_UI(err_ratelimit_पूर्णांकerval_ms, s_err_ratelimit_state.पूर्णांकerval);
EXT4_RW_ATTR_SBI_UI(err_ratelimit_burst, s_err_ratelimit_state.burst);
EXT4_RW_ATTR_SBI_UI(warning_ratelimit_पूर्णांकerval_ms, s_warning_ratelimit_state.पूर्णांकerval);
EXT4_RW_ATTR_SBI_UI(warning_ratelimit_burst, s_warning_ratelimit_state.burst);
EXT4_RW_ATTR_SBI_UI(msg_ratelimit_पूर्णांकerval_ms, s_msg_ratelimit_state.पूर्णांकerval);
EXT4_RW_ATTR_SBI_UI(msg_ratelimit_burst, s_msg_ratelimit_state.burst);
#अगर_घोषित CONFIG_EXT4_DEBUG
EXT4_RW_ATTR_SBI_UL(simulate_fail, s_simulate_fail);
#पूर्ण_अगर
EXT4_RO_ATTR_SBI_ATOMIC(warning_count, s_warning_count);
EXT4_RO_ATTR_SBI_ATOMIC(msg_count, s_msg_count);
EXT4_RO_ATTR_ES_UI(errors_count, s_error_count);
EXT4_RO_ATTR_ES_U8(first_error_errcode, s_first_error_errcode);
EXT4_RO_ATTR_ES_U8(last_error_errcode, s_last_error_errcode);
EXT4_RO_ATTR_ES_UI(first_error_ino, s_first_error_ino);
EXT4_RO_ATTR_ES_UI(last_error_ino, s_last_error_ino);
EXT4_RO_ATTR_ES_U64(first_error_block, s_first_error_block);
EXT4_RO_ATTR_ES_U64(last_error_block, s_last_error_block);
EXT4_RO_ATTR_ES_UI(first_error_line, s_first_error_line);
EXT4_RO_ATTR_ES_UI(last_error_line, s_last_error_line);
EXT4_RO_ATTR_ES_STRING(first_error_func, s_first_error_func, 32);
EXT4_RO_ATTR_ES_STRING(last_error_func, s_last_error_func, 32);
EXT4_ATTR(first_error_समय, 0444, first_error_समय);
EXT4_ATTR(last_error_समय, 0444, last_error_समय);
EXT4_ATTR(journal_task, 0444, journal_task);
EXT4_RW_ATTR_SBI_UI(mb_prefetch, s_mb_prefetch);
EXT4_RW_ATTR_SBI_UI(mb_prefetch_limit, s_mb_prefetch_limit);

अटल अचिन्हित पूर्णांक old_bump_val = 128;
EXT4_ATTR_PTR(max_ग_लिखोback_mb_bump, 0444, poपूर्णांकer_ui, &old_bump_val);

अटल काष्ठा attribute *ext4_attrs[] = अणु
	ATTR_LIST(delayed_allocation_blocks),
	ATTR_LIST(session_ग_लिखो_kbytes),
	ATTR_LIST(lअगरeसमय_ग_लिखो_kbytes),
	ATTR_LIST(reserved_clusters),
	ATTR_LIST(sra_exceeded_retry_limit),
	ATTR_LIST(inode_पढ़ोahead_blks),
	ATTR_LIST(inode_goal),
	ATTR_LIST(mb_stats),
	ATTR_LIST(mb_max_to_scan),
	ATTR_LIST(mb_min_to_scan),
	ATTR_LIST(mb_order2_req),
	ATTR_LIST(mb_stream_req),
	ATTR_LIST(mb_group_pपुनः_स्मृति),
	ATTR_LIST(mb_max_inode_pपुनः_स्मृति),
	ATTR_LIST(mb_max_linear_groups),
	ATTR_LIST(max_ग_लिखोback_mb_bump),
	ATTR_LIST(extent_max_zeroout_kb),
	ATTR_LIST(trigger_fs_error),
	ATTR_LIST(err_ratelimit_पूर्णांकerval_ms),
	ATTR_LIST(err_ratelimit_burst),
	ATTR_LIST(warning_ratelimit_पूर्णांकerval_ms),
	ATTR_LIST(warning_ratelimit_burst),
	ATTR_LIST(msg_ratelimit_पूर्णांकerval_ms),
	ATTR_LIST(msg_ratelimit_burst),
	ATTR_LIST(errors_count),
	ATTR_LIST(warning_count),
	ATTR_LIST(msg_count),
	ATTR_LIST(first_error_ino),
	ATTR_LIST(last_error_ino),
	ATTR_LIST(first_error_block),
	ATTR_LIST(last_error_block),
	ATTR_LIST(first_error_line),
	ATTR_LIST(last_error_line),
	ATTR_LIST(first_error_func),
	ATTR_LIST(last_error_func),
	ATTR_LIST(first_error_errcode),
	ATTR_LIST(last_error_errcode),
	ATTR_LIST(first_error_समय),
	ATTR_LIST(last_error_समय),
	ATTR_LIST(journal_task),
#अगर_घोषित CONFIG_EXT4_DEBUG
	ATTR_LIST(simulate_fail),
#पूर्ण_अगर
	ATTR_LIST(mb_prefetch),
	ATTR_LIST(mb_prefetch_limit),
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ext4);

/* Features this copy of ext4 supports */
EXT4_ATTR_FEATURE(lazy_itable_init);
EXT4_ATTR_FEATURE(batched_discard);
EXT4_ATTR_FEATURE(meta_bg_resize);
#अगर_घोषित CONFIG_FS_ENCRYPTION
EXT4_ATTR_FEATURE(encryption);
EXT4_ATTR_FEATURE(test_dummy_encryption_v2);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
EXT4_ATTR_FEATURE(हालfold);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
EXT4_ATTR_FEATURE(verity);
#पूर्ण_अगर
EXT4_ATTR_FEATURE(metadata_csum_seed);
EXT4_ATTR_FEATURE(fast_commit);
#अगर defined(CONFIG_UNICODE) && defined(CONFIG_FS_ENCRYPTION)
EXT4_ATTR_FEATURE(encrypted_हालfold);
#पूर्ण_अगर

अटल काष्ठा attribute *ext4_feat_attrs[] = अणु
	ATTR_LIST(lazy_itable_init),
	ATTR_LIST(batched_discard),
	ATTR_LIST(meta_bg_resize),
#अगर_घोषित CONFIG_FS_ENCRYPTION
	ATTR_LIST(encryption),
	ATTR_LIST(test_dummy_encryption_v2),
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	ATTR_LIST(हालfold),
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
	ATTR_LIST(verity),
#पूर्ण_अगर
	ATTR_LIST(metadata_csum_seed),
	ATTR_LIST(fast_commit),
#अगर defined(CONFIG_UNICODE) && defined(CONFIG_FS_ENCRYPTION)
	ATTR_LIST(encrypted_हालfold),
#पूर्ण_अगर
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ext4_feat);

अटल व्योम *calc_ptr(काष्ठा ext4_attr *a, काष्ठा ext4_sb_info *sbi)
अणु
	चयन (a->attr_ptr) अणु
	हाल ptr_explicit:
		वापस a->u.explicit_ptr;
	हाल ptr_ext4_sb_info_offset:
		वापस (व्योम *) (((अक्षर *) sbi) + a->u.offset);
	हाल ptr_ext4_super_block_offset:
		वापस (व्योम *) (((अक्षर *) sbi->s_es) + a->u.offset);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार __prपूर्णांक_tstamp(अक्षर *buf, __le32 lo, __u8 hi)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%lld\n",
			((समय64_t)hi << 32) + le32_to_cpu(lo));
पूर्ण

#घोषणा prपूर्णांक_tstamp(buf, es, tstamp) \
	__prपूर्णांक_tstamp(buf, (es)->tstamp, (es)->tstamp ## _hi)

अटल sमाप_प्रकार ext4_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा ext4_sb_info *sbi = container_of(kobj, काष्ठा ext4_sb_info,
						s_kobj);
	काष्ठा ext4_attr *a = container_of(attr, काष्ठा ext4_attr, attr);
	व्योम *ptr = calc_ptr(a, sbi);

	चयन (a->attr_id) अणु
	हाल attr_delayed_allocation_blocks:
		वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
				(s64) EXT4_C2B(sbi,
		       percpu_counter_sum(&sbi->s_dirtyclusters_counter)));
	हाल attr_session_ग_लिखो_kbytes:
		वापस session_ग_लिखो_kbytes_show(sbi, buf);
	हाल attr_lअगरeसमय_ग_लिखो_kbytes:
		वापस lअगरeसमय_ग_लिखो_kbytes_show(sbi, buf);
	हाल attr_reserved_clusters:
		वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
				(अचिन्हित दीर्घ दीर्घ)
				atomic64_पढ़ो(&sbi->s_resv_clusters));
	हाल attr_sra_exceeded_retry_limit:
		वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
				(अचिन्हित दीर्घ दीर्घ)
			percpu_counter_sum(&sbi->s_sra_exceeded_retry_limit));
	हाल attr_inode_पढ़ोahead:
	हाल attr_poपूर्णांकer_ui:
		अगर (!ptr)
			वापस 0;
		अगर (a->attr_ptr == ptr_ext4_super_block_offset)
			वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
					le32_to_cpup(ptr));
		अन्यथा
			वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
					*((अचिन्हित पूर्णांक *) ptr));
	हाल attr_poपूर्णांकer_ul:
		अगर (!ptr)
			वापस 0;
		वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n",
				*((अचिन्हित दीर्घ *) ptr));
	हाल attr_poपूर्णांकer_u8:
		अगर (!ptr)
			वापस 0;
		वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
				*((अचिन्हित अक्षर *) ptr));
	हाल attr_poपूर्णांकer_u64:
		अगर (!ptr)
			वापस 0;
		अगर (a->attr_ptr == ptr_ext4_super_block_offset)
			वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
					le64_to_cpup(ptr));
		अन्यथा
			वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
					*((अचिन्हित दीर्घ दीर्घ *) ptr));
	हाल attr_poपूर्णांकer_string:
		अगर (!ptr)
			वापस 0;
		वापस snम_लिखो(buf, PAGE_SIZE, "%.*s\n", a->attr_size,
				(अक्षर *) ptr);
	हाल attr_poपूर्णांकer_atomic:
		अगर (!ptr)
			वापस 0;
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
				atomic_पढ़ो((atomic_t *) ptr));
	हाल attr_feature:
		वापस snम_लिखो(buf, PAGE_SIZE, "supported\n");
	हाल attr_first_error_समय:
		वापस prपूर्णांक_tstamp(buf, sbi->s_es, s_first_error_समय);
	हाल attr_last_error_समय:
		वापस prपूर्णांक_tstamp(buf, sbi->s_es, s_last_error_समय);
	हाल attr_journal_task:
		वापस journal_task_show(sbi, buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ext4_attr_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ext4_sb_info *sbi = container_of(kobj, काष्ठा ext4_sb_info,
						s_kobj);
	काष्ठा ext4_attr *a = container_of(attr, काष्ठा ext4_attr, attr);
	व्योम *ptr = calc_ptr(a, sbi);
	अचिन्हित दीर्घ t;
	पूर्णांक ret;

	चयन (a->attr_id) अणु
	हाल attr_reserved_clusters:
		वापस reserved_clusters_store(sbi, buf, len);
	हाल attr_poपूर्णांकer_ui:
		अगर (!ptr)
			वापस 0;
		ret = kम_से_अदीर्घ(skip_spaces(buf), 0, &t);
		अगर (ret)
			वापस ret;
		अगर (a->attr_ptr == ptr_ext4_super_block_offset)
			*((__le32 *) ptr) = cpu_to_le32(t);
		अन्यथा
			*((अचिन्हित पूर्णांक *) ptr) = t;
		वापस len;
	हाल attr_poपूर्णांकer_ul:
		अगर (!ptr)
			वापस 0;
		ret = kम_से_अदीर्घ(skip_spaces(buf), 0, &t);
		अगर (ret)
			वापस ret;
		*((अचिन्हित दीर्घ *) ptr) = t;
		वापस len;
	हाल attr_inode_पढ़ोahead:
		वापस inode_पढ़ोahead_blks_store(sbi, buf, len);
	हाल attr_trigger_test_error:
		वापस trigger_test_error(sbi, buf, len);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ext4_sb_release(काष्ठा kobject *kobj)
अणु
	काष्ठा ext4_sb_info *sbi = container_of(kobj, काष्ठा ext4_sb_info,
						s_kobj);
	complete(&sbi->s_kobj_unरेजिस्टर);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops ext4_attr_ops = अणु
	.show	= ext4_attr_show,
	.store	= ext4_attr_store,
पूर्ण;

अटल काष्ठा kobj_type ext4_sb_ktype = अणु
	.शेष_groups = ext4_groups,
	.sysfs_ops	= &ext4_attr_ops,
	.release	= ext4_sb_release,
पूर्ण;

अटल काष्ठा kobj_type ext4_feat_ktype = अणु
	.शेष_groups = ext4_feat_groups,
	.sysfs_ops	= &ext4_attr_ops,
	.release	= (व्योम (*)(काष्ठा kobject *))kमुक्त,
पूर्ण;

अटल काष्ठा kobject *ext4_root;

अटल काष्ठा kobject *ext4_feat;

पूर्णांक ext4_रेजिस्टर_sysfs(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक err;

	init_completion(&sbi->s_kobj_unरेजिस्टर);
	err = kobject_init_and_add(&sbi->s_kobj, &ext4_sb_ktype, ext4_root,
				   "%s", sb->s_id);
	अगर (err) अणु
		kobject_put(&sbi->s_kobj);
		रुको_क्रम_completion(&sbi->s_kobj_unरेजिस्टर);
		वापस err;
	पूर्ण

	अगर (ext4_proc_root)
		sbi->s_proc = proc_सूची_गढ़ो(sb->s_id, ext4_proc_root);
	अगर (sbi->s_proc) अणु
		proc_create_single_data("options", S_IRUGO, sbi->s_proc,
				ext4_seq_options_show, sb);
		proc_create_single_data("es_shrinker_info", S_IRUGO,
				sbi->s_proc, ext4_seq_es_shrinker_info_show,
				sb);
		proc_create_single_data("fc_info", 0444, sbi->s_proc,
					ext4_fc_info_show, sb);
		proc_create_seq_data("mb_groups", S_IRUGO, sbi->s_proc,
				&ext4_mb_seq_groups_ops, sb);
		proc_create_single_data("mb_stats", 0444, sbi->s_proc,
				ext4_seq_mb_stats_show, sb);
		proc_create_seq_data("mb_structs_summary", 0444, sbi->s_proc,
				&ext4_mb_seq_काष्ठाs_summary_ops, sb);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ext4_unरेजिस्टर_sysfs(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (sbi->s_proc)
		हटाओ_proc_subtree(sb->s_id, ext4_proc_root);
	kobject_del(&sbi->s_kobj);
पूर्ण

पूर्णांक __init ext4_init_sysfs(व्योम)
अणु
	पूर्णांक ret;

	ext4_root = kobject_create_and_add("ext4", fs_kobj);
	अगर (!ext4_root)
		वापस -ENOMEM;

	ext4_feat = kzalloc(माप(*ext4_feat), GFP_KERNEL);
	अगर (!ext4_feat) अणु
		ret = -ENOMEM;
		जाओ root_err;
	पूर्ण

	ret = kobject_init_and_add(ext4_feat, &ext4_feat_ktype,
				   ext4_root, "features");
	अगर (ret)
		जाओ feat_err;

	ext4_proc_root = proc_सूची_गढ़ो(proc_स_नाम, शून्य);
	वापस ret;

feat_err:
	kobject_put(ext4_feat);
	ext4_feat = शून्य;
root_err:
	kobject_put(ext4_root);
	ext4_root = शून्य;
	वापस ret;
पूर्ण

व्योम ext4_निकास_sysfs(व्योम)
अणु
	kobject_put(ext4_feat);
	ext4_feat = शून्य;
	kobject_put(ext4_root);
	ext4_root = शून्य;
	हटाओ_proc_entry(proc_स_नाम, शून्य);
	ext4_proc_root = शून्य;
पूर्ण

