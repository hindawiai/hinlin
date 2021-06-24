<शैली गुरु>
/* -*- linux-c -*- */

/* fs/reiserfs/procfs.c */

/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

/* proc info support a la one created by Sizअगर@Botik.RU क्रम PGC */

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश "reiserfs.h"
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/blkdev.h>

/*
 * LOCKING:
 *
 * These guys are evicted from procfs as the very first step in ->समाप्त_sb().
 *
 */

अटल पूर्णांक show_version(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	अक्षर *क्रमmat;

	अगर (REISERFS_SB(sb)->s_properties & (1 << REISERFS_3_6)) अणु
		क्रमmat = "3.6";
	पूर्ण अन्यथा अगर (REISERFS_SB(sb)->s_properties & (1 << REISERFS_3_5)) अणु
		क्रमmat = "3.5";
	पूर्ण अन्यथा अणु
		क्रमmat = "unknown";
	पूर्ण

	seq_म_लिखो(m, "%s format\twith checks %s\n", क्रमmat,
#अगर defined( CONFIG_REISERFS_CHECK )
		   "on"
#अन्यथा
		   "off"
#पूर्ण_अगर
	    );
	वापस 0;
पूर्ण

#घोषणा SF( x ) ( r -> x )
#घोषणा SFP( x ) SF( s_proc_info_data.x )
#घोषणा SFPL( x ) SFP( x[ level ] )
#घोषणा SFPF( x ) SFP( scan_biपंचांगap.x )
#घोषणा SFPJ( x ) SFP( journal.x )

#घोषणा D2C( x ) le16_to_cpu( x )
#घोषणा D4C( x ) le32_to_cpu( x )
#घोषणा DF( x ) D2C( rs -> s_v1.x )
#घोषणा DFL( x ) D4C( rs -> s_v1.x )

#घोषणा objectid_map( s, rs ) (old_क्रमmat_only (s) ?				\
                         (__le32 *)((काष्ठा reiserfs_super_block_v1 *)rs + 1) :	\
			 (__le32 *)(rs + 1))
#घोषणा MAP( i ) D4C( objectid_map( sb, rs )[ i ] )

#घोषणा DJF( x ) le32_to_cpu( rs -> x )
#घोषणा DJP( x ) le32_to_cpu( jp -> x )
#घोषणा JF( x ) ( r -> s_journal -> x )

अटल पूर्णांक show_super(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *r = REISERFS_SB(sb);

	seq_म_लिखो(m, "state: \t%s\n"
		   "mount options: \t%s%s%s%s%s%s%s%s%s%s%s\n"
		   "gen. counter: \t%i\n"
		   "s_disk_reads: \t%i\n"
		   "s_disk_writes: \t%i\n"
		   "s_fix_nodes: \t%i\n"
		   "s_do_balance: \t%i\n"
		   "s_unneeded_left_neighbor: \t%i\n"
		   "s_good_search_by_key_reada: \t%i\n"
		   "s_bmaps: \t%i\n"
		   "s_bmaps_without_search: \t%i\n"
		   "s_direct2indirect: \t%i\n"
		   "s_indirect2direct: \t%i\n"
		   "\n"
		   "max_hash_collisions: \t%i\n"
		   "breads: \t%lu\n"
		   "bread_misses: \t%lu\n"
		   "search_by_key: \t%lu\n"
		   "search_by_key_fs_changed: \t%lu\n"
		   "search_by_key_restarted: \t%lu\n"
		   "insert_item_restarted: \t%lu\n"
		   "paste_into_item_restarted: \t%lu\n"
		   "cut_from_item_restarted: \t%lu\n"
		   "delete_solid_item_restarted: \t%lu\n"
		   "delete_item_restarted: \t%lu\n"
		   "leaked_oid: \t%lu\n"
		   "leaves_removable: \t%lu\n",
		   SF(s_mount_state) == REISERFS_VALID_FS ?
		   "REISERFS_VALID_FS" : "REISERFS_ERROR_FS",
		   reiserfs_r5_hash(sb) ? "FORCE_R5 " : "",
		   reiserfs_rupasov_hash(sb) ? "FORCE_RUPASOV " : "",
		   reiserfs_tea_hash(sb) ? "FORCE_TEA " : "",
		   reiserfs_hash_detect(sb) ? "DETECT_HASH " : "",
		   reiserfs_no_border(sb) ? "NO_BORDER " : "BORDER ",
		   reiserfs_no_unhashed_relocation(sb) ?
		   "NO_UNHASHED_RELOCATION " : "",
		   reiserfs_hashed_relocation(sb) ? "UNHASHED_RELOCATION " : "",
		   reiserfs_test4(sb) ? "TEST4 " : "",
		   have_large_tails(sb) ? "TAILS " : have_small_tails(sb) ?
		   "SMALL_TAILS " : "NO_TAILS ",
		   replay_only(sb) ? "REPLAY_ONLY " : "",
		   convert_reiserfs(sb) ? "CONV " : "",
		   atomic_पढ़ो(&r->s_generation_counter),
		   SF(s_disk_पढ़ोs), SF(s_disk_ग_लिखोs), SF(s_fix_nodes),
		   SF(s_करो_balance), SF(s_unneeded_left_neighbor),
		   SF(s_good_search_by_key_पढ़ोa), SF(s_bmaps),
		   SF(s_bmaps_without_search), SF(s_direct2indirect),
		   SF(s_indirect2direct), SFP(max_hash_collisions), SFP(bपढ़ोs),
		   SFP(bपढ़ो_miss), SFP(search_by_key),
		   SFP(search_by_key_fs_changed), SFP(search_by_key_restarted),
		   SFP(insert_item_restarted), SFP(paste_पूर्णांकo_item_restarted),
		   SFP(cut_from_item_restarted),
		   SFP(delete_solid_item_restarted), SFP(delete_item_restarted),
		   SFP(leaked_oid), SFP(leaves_removable));

	वापस 0;
पूर्ण

अटल पूर्णांक show_per_level(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *r = REISERFS_SB(sb);
	पूर्णांक level;

	seq_म_लिखो(m, "level\t"
		   "     balances"
		   " [sbk:  reads"
		   "   fs_changed"
		   "   restarted]"
		   "   free space"
		   "        items"
		   "   can_remove"
		   "         lnum"
		   "         rnum"
		   "       lbytes"
		   "       rbytes"
		   "     get_neig"
		   " get_neig_res" "  need_l_neig" "  need_r_neig" "\n");

	क्रम (level = 0; level < MAX_HEIGHT; ++level) अणु
		seq_म_लिखो(m, "%i\t"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12li"
			   " %12li"
			   " %12li"
			   " %12li"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   "\n",
			   level,
			   SFPL(balance_at),
			   SFPL(sbk_पढ़ो_at),
			   SFPL(sbk_fs_changed),
			   SFPL(sbk_restarted),
			   SFPL(मुक्त_at),
			   SFPL(items_at),
			   SFPL(can_node_be_हटाओd),
			   SFPL(lnum),
			   SFPL(rnum),
			   SFPL(lbytes),
			   SFPL(rbytes),
			   SFPL(get_neighbors),
			   SFPL(get_neighbors_restart),
			   SFPL(need_l_neighbor), SFPL(need_r_neighbor)
		    );
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक show_biपंचांगap(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *r = REISERFS_SB(sb);

	seq_म_लिखो(m, "free_block: %lu\n"
		   "  scan_bitmap:"
		   "          wait"
		   "          bmap"
		   "         retry"
		   "        stolen"
		   "  journal_hint"
		   "journal_nohint"
		   "\n"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   "\n",
		   SFP(मुक्त_block),
		   SFPF(call),
		   SFPF(रुको),
		   SFPF(bmap),
		   SFPF(retry),
		   SFPF(stolen),
		   SFPF(in_journal_hपूर्णांक), SFPF(in_journal_nohपूर्णांक));

	वापस 0;
पूर्ण

अटल पूर्णांक show_on_disk_super(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *sb_info = REISERFS_SB(sb);
	काष्ठा reiserfs_super_block *rs = sb_info->s_rs;
	पूर्णांक hash_code = DFL(s_hash_function_code);
	__u32 flags = DJF(s_flags);

	seq_म_लिखो(m, "block_count: \t%i\n"
		   "free_blocks: \t%i\n"
		   "root_block: \t%i\n"
		   "blocksize: \t%i\n"
		   "oid_maxsize: \t%i\n"
		   "oid_cursize: \t%i\n"
		   "umount_state: \t%i\n"
		   "magic: \t%10.10s\n"
		   "fs_state: \t%i\n"
		   "hash: \t%s\n"
		   "tree_height: \t%i\n"
		   "bmap_nr: \t%i\n"
		   "version: \t%i\n"
		   "flags: \t%x[%s]\n"
		   "reserved_for_journal: \t%i\n",
		   DFL(s_block_count),
		   DFL(s_मुक्त_blocks),
		   DFL(s_root_block),
		   DF(s_blocksize),
		   DF(s_oid_maxsize),
		   DF(s_oid_cursize),
		   DF(s_umount_state),
		   rs->s_v1.s_magic,
		   DF(s_fs_state),
		   hash_code == TEA_HASH ? "tea" :
		   (hash_code == YURA_HASH) ? "rupasov" :
		   (hash_code == R5_HASH) ? "r5" :
		   (hash_code == UNSET_HASH) ? "unset" : "unknown",
		   DF(s_tree_height),
		   DF(s_bmap_nr),
		   DF(s_version), flags, (flags & reiserfs_attrs_cleared)
		   ? "attrs_cleared" : "", DF(s_reserved_क्रम_journal));

	वापस 0;
पूर्ण

अटल पूर्णांक show_oidmap(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *sb_info = REISERFS_SB(sb);
	काष्ठा reiserfs_super_block *rs = sb_info->s_rs;
	अचिन्हित पूर्णांक mapsize = le16_to_cpu(rs->s_v1.s_oid_cursize);
	अचिन्हित दीर्घ total_used = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mapsize; ++i) अणु
		__u32 right;

		right = (i == mapsize - 1) ? MAX_KEY_OBJECTID : MAP(i + 1);
		seq_म_लिखो(m, "%s: [ %x .. %x )\n",
			   (i & 1) ? "free" : "used", MAP(i), right);
		अगर (!(i & 1)) अणु
			total_used += right - MAP(i);
		पूर्ण
	पूर्ण
#अगर defined( REISERFS_USE_OIDMAPF )
	अगर (sb_info->oidmap.use_file && (sb_info->oidmap.mapf != शून्य)) अणु
		loff_t size = file_inode(sb_info->oidmap.mapf)->i_size;
		total_used += size / माप(reiserfs_oidपूर्णांकerval_d_t);
	पूर्ण
#पूर्ण_अगर
	seq_म_लिखो(m, "total: \t%i [%i/%i] used: %lu [exact]\n",
		   mapsize,
		   mapsize, le16_to_cpu(rs->s_v1.s_oid_maxsize), total_used);
	वापस 0;
पूर्ण

अटल समय64_t kसमय_mono_to_real_seconds(समय64_t mono)
अणु
	kसमय_प्रकार kt = kसमय_set(mono, NSEC_PER_SEC/2);

	वापस kसमय_भागns(kसमय_mono_to_real(kt), NSEC_PER_SEC);
पूर्ण

अटल पूर्णांक show_journal(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा super_block *sb = m->निजी;
	काष्ठा reiserfs_sb_info *r = REISERFS_SB(sb);
	काष्ठा reiserfs_super_block *rs = r->s_rs;
	काष्ठा journal_params *jp = &rs->s_v1.s_journal;

	seq_म_लिखो(m,		/* on-disk fields */
		   "jp_journal_1st_block: \t%i\n"
		   "jp_journal_dev: \t%pg[%x]\n"
		   "jp_journal_size: \t%i\n"
		   "jp_journal_trans_max: \t%i\n"
		   "jp_journal_magic: \t%i\n"
		   "jp_journal_max_batch: \t%i\n"
		   "jp_journal_max_commit_age: \t%i\n"
		   "jp_journal_max_trans_age: \t%i\n"
		   /* incore fields */
		   "j_1st_reserved_block: \t%i\n"
		   "j_state: \t%li\n"
		   "j_trans_id: \t%u\n"
		   "j_mount_id: \t%lu\n"
		   "j_start: \t%lu\n"
		   "j_len: \t%lu\n"
		   "j_len_alloc: \t%lu\n"
		   "j_wcount: \t%i\n"
		   "j_bcount: \t%lu\n"
		   "j_first_unflushed_offset: \t%lu\n"
		   "j_last_flush_trans_id: \t%u\n"
		   "j_trans_start_time: \t%lli\n"
		   "j_list_bitmap_index: \t%i\n"
		   "j_must_wait: \t%i\n"
		   "j_next_full_flush: \t%i\n"
		   "j_next_async_flush: \t%i\n"
		   "j_cnode_used: \t%i\n" "j_cnode_free: \t%i\n" "\n"
		   /* reiserfs_proc_info_data_t.journal fields */
		   "in_journal: \t%12lu\n"
		   "in_journal_bitmap: \t%12lu\n"
		   "in_journal_reusable: \t%12lu\n"
		   "lock_journal: \t%12lu\n"
		   "lock_journal_wait: \t%12lu\n"
		   "journal_begin: \t%12lu\n"
		   "journal_relock_writers: \t%12lu\n"
		   "journal_relock_wcount: \t%12lu\n"
		   "mark_dirty: \t%12lu\n"
		   "mark_dirty_already: \t%12lu\n"
		   "mark_dirty_notjournal: \t%12lu\n"
		   "restore_prepared: \t%12lu\n"
		   "prepare: \t%12lu\n"
		   "prepare_retry: \t%12lu\n",
		   DJP(jp_journal_1st_block),
		   SB_JOURNAL(sb)->j_dev_bd,
		   DJP(jp_journal_dev),
		   DJP(jp_journal_size),
		   DJP(jp_journal_trans_max),
		   DJP(jp_journal_magic),
		   DJP(jp_journal_max_batch),
		   SB_JOURNAL(sb)->j_max_commit_age,
		   DJP(jp_journal_max_trans_age),
		   JF(j_1st_reserved_block),
		   JF(j_state),
		   JF(j_trans_id),
		   JF(j_mount_id),
		   JF(j_start),
		   JF(j_len),
		   JF(j_len_alloc),
		   atomic_पढ़ो(&r->s_journal->j_wcount),
		   JF(j_bcount),
		   JF(j_first_unflushed_offset),
		   JF(j_last_flush_trans_id),
		   kसमय_mono_to_real_seconds(JF(j_trans_start_समय)),
		   JF(j_list_biपंचांगap_index),
		   JF(j_must_रुको),
		   JF(j_next_full_flush),
		   JF(j_next_async_flush),
		   JF(j_cnode_used),
		   JF(j_cnode_मुक्त),
		   SFPJ(in_journal),
		   SFPJ(in_journal_biपंचांगap),
		   SFPJ(in_journal_reusable),
		   SFPJ(lock_journal),
		   SFPJ(lock_journal_रुको),
		   SFPJ(journal_being),
		   SFPJ(journal_relock_ग_लिखोrs),
		   SFPJ(journal_relock_wcount),
		   SFPJ(mark_dirty),
		   SFPJ(mark_dirty_alपढ़ोy),
		   SFPJ(mark_dirty_notjournal),
		   SFPJ(restore_prepared), SFPJ(prepare), SFPJ(prepare_retry)
	    );
	वापस 0;
पूर्ण

अटल काष्ठा proc_dir_entry *proc_info_root = शून्य;
अटल स्थिर अक्षर proc_info_root_name[] = "fs/reiserfs";

अटल व्योम add_file(काष्ठा super_block *sb, अक्षर *name,
		     पूर्णांक (*func) (काष्ठा seq_file *, व्योम *))
अणु
	proc_create_single_data(name, 0, REISERFS_SB(sb)->procdir, func, sb);
पूर्ण

पूर्णांक reiserfs_proc_info_init(काष्ठा super_block *sb)
अणु
	अक्षर b[BDEVNAME_SIZE];
	अक्षर *s;

	/* Some block devices use /'s */
	strlcpy(b, sb->s_id, BDEVNAME_SIZE);
	s = म_अक्षर(b, '/');
	अगर (s)
		*s = '!';

	spin_lock_init(&__PINFO(sb).lock);
	REISERFS_SB(sb)->procdir = proc_सूची_गढ़ो_data(b, 0, proc_info_root, sb);
	अगर (REISERFS_SB(sb)->procdir) अणु
		add_file(sb, "version", show_version);
		add_file(sb, "super", show_super);
		add_file(sb, "per-level", show_per_level);
		add_file(sb, "bitmap", show_biपंचांगap);
		add_file(sb, "on-disk-super", show_on_disk_super);
		add_file(sb, "oidmap", show_oidmap);
		add_file(sb, "journal", show_journal);
		वापस 0;
	पूर्ण
	reiserfs_warning(sb, "cannot create /proc/%s/%s",
			 proc_info_root_name, b);
	वापस 1;
पूर्ण

पूर्णांक reiserfs_proc_info_करोne(काष्ठा super_block *sb)
अणु
	काष्ठा proc_dir_entry *de = REISERFS_SB(sb)->procdir;
	अगर (de) अणु
		अक्षर b[BDEVNAME_SIZE];
		अक्षर *s;

		/* Some block devices use /'s */
		strlcpy(b, sb->s_id, BDEVNAME_SIZE);
		s = म_अक्षर(b, '/');
		अगर (s)
			*s = '!';

		हटाओ_proc_subtree(b, proc_info_root);
		REISERFS_SB(sb)->procdir = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक reiserfs_proc_info_global_init(व्योम)
अणु
	अगर (proc_info_root == शून्य) अणु
		proc_info_root = proc_सूची_गढ़ो(proc_info_root_name, शून्य);
		अगर (!proc_info_root) अणु
			reiserfs_warning(शून्य, "cannot create /proc/%s",
					 proc_info_root_name);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक reiserfs_proc_info_global_करोne(व्योम)
अणु
	अगर (proc_info_root != शून्य) अणु
		proc_info_root = शून्य;
		हटाओ_proc_entry(proc_info_root_name, शून्य);
	पूर्ण
	वापस 0;
पूर्ण
/*
 * Revision 1.1.8.2  2001/07/15 17:08:42  god
 *  . use get_super() in procfs.c
 *  . हटाओ हटाओ_save_link() from reiserfs_करो_truncate()
 *
 * I accept terms and conditions stated in the Legal Agreement
 * (available at http://www.namesys.com/legalese.hपंचांगl)
 *
 * Revision 1.1.8.1  2001/07/11 16:48:50  god
 * proc info support
 *
 * I accept terms and conditions stated in the Legal Agreement
 * (available at http://www.namesys.com/legalese.hपंचांगl)
 *
 */
