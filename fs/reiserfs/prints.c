<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश "reiserfs.h"
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>

#समावेश <मानकतर्क.स>

अटल अक्षर error_buf[1024];
अटल अक्षर fmt_buf[1024];
अटल अक्षर off_buf[80];

अटल अक्षर *reiserfs_cpu_offset(काष्ठा cpu_key *key)
अणु
	अगर (cpu_key_k_type(key) == TYPE_सूचीENTRY)
		प्र_लिखो(off_buf, "%llu(%llu)",
			(अचिन्हित दीर्घ दीर्घ)
			GET_HASH_VALUE(cpu_key_k_offset(key)),
			(अचिन्हित दीर्घ दीर्घ)
			GET_GENERATION_NUMBER(cpu_key_k_offset(key)));
	अन्यथा
		प्र_लिखो(off_buf, "0x%Lx",
			(अचिन्हित दीर्घ दीर्घ)cpu_key_k_offset(key));
	वापस off_buf;
पूर्ण

अटल अक्षर *le_offset(काष्ठा reiserfs_key *key)
अणु
	पूर्णांक version;

	version = le_key_version(key);
	अगर (le_key_k_type(version, key) == TYPE_सूचीENTRY)
		प्र_लिखो(off_buf, "%llu(%llu)",
			(अचिन्हित दीर्घ दीर्घ)
			GET_HASH_VALUE(le_key_k_offset(version, key)),
			(अचिन्हित दीर्घ दीर्घ)
			GET_GENERATION_NUMBER(le_key_k_offset(version, key)));
	अन्यथा
		प्र_लिखो(off_buf, "0x%Lx",
			(अचिन्हित दीर्घ दीर्घ)le_key_k_offset(version, key));
	वापस off_buf;
पूर्ण

अटल अक्षर *cpu_type(काष्ठा cpu_key *key)
अणु
	अगर (cpu_key_k_type(key) == TYPE_STAT_DATA)
		वापस "SD";
	अगर (cpu_key_k_type(key) == TYPE_सूचीENTRY)
		वापस "DIR";
	अगर (cpu_key_k_type(key) == TYPE_सूचीECT)
		वापस "DIRECT";
	अगर (cpu_key_k_type(key) == TYPE_INसूचीECT)
		वापस "IND";
	वापस "UNKNOWN";
पूर्ण

अटल अक्षर *le_type(काष्ठा reiserfs_key *key)
अणु
	पूर्णांक version;

	version = le_key_version(key);

	अगर (le_key_k_type(version, key) == TYPE_STAT_DATA)
		वापस "SD";
	अगर (le_key_k_type(version, key) == TYPE_सूचीENTRY)
		वापस "DIR";
	अगर (le_key_k_type(version, key) == TYPE_सूचीECT)
		वापस "DIRECT";
	अगर (le_key_k_type(version, key) == TYPE_INसूचीECT)
		वापस "IND";
	वापस "UNKNOWN";
पूर्ण

/* %k */
अटल पूर्णांक scnम_लिखो_le_key(अक्षर *buf, माप_प्रकार size, काष्ठा reiserfs_key *key)
अणु
	अगर (key)
		वापस scnम_लिखो(buf, size, "[%d %d %s %s]",
				 le32_to_cpu(key->k_dir_id),
				 le32_to_cpu(key->k_objectid), le_offset(key),
				 le_type(key));
	अन्यथा
		वापस scnम_लिखो(buf, size, "[NULL]");
पूर्ण

/* %K */
अटल पूर्णांक scnम_लिखो_cpu_key(अक्षर *buf, माप_प्रकार size, काष्ठा cpu_key *key)
अणु
	अगर (key)
		वापस scnम_लिखो(buf, size, "[%d %d %s %s]",
				 key->on_disk_key.k_dir_id,
				 key->on_disk_key.k_objectid,
				 reiserfs_cpu_offset(key), cpu_type(key));
	अन्यथा
		वापस scnम_लिखो(buf, size, "[NULL]");
पूर्ण

अटल पूर्णांक scnम_लिखो_de_head(अक्षर *buf, माप_प्रकार size,
			     काष्ठा reiserfs_de_head *deh)
अणु
	अगर (deh)
		वापस scnम_लिखो(buf, size,
				 "[offset=%d dir_id=%d objectid=%d location=%d state=%04x]",
				 deh_offset(deh), deh_dir_id(deh),
				 deh_objectid(deh), deh_location(deh),
				 deh_state(deh));
	अन्यथा
		वापस scnम_लिखो(buf, size, "[NULL]");

पूर्ण

अटल पूर्णांक scnम_लिखो_item_head(अक्षर *buf, माप_प्रकार size, काष्ठा item_head *ih)
अणु
	अगर (ih) अणु
		अक्षर *p = buf;
		अक्षर * स्थिर end = buf + size;

		p += scnम_लिखो(p, end - p, "%s",
			       (ih_version(ih) == KEY_FORMAT_3_6) ?
			       "*3.6* " : "*3.5*");

		p += scnम_लिखो_le_key(p, end - p, &ih->ih_key);

		p += scnम_लिखो(p, end - p,
			       ", item_len %d, item_location %d, free_space(entry_count) %d",
			       ih_item_len(ih), ih_location(ih),
			       ih_मुक्त_space(ih));
		वापस p - buf;
	पूर्ण अन्यथा
		वापस scnम_लिखो(buf, size, "[NULL]");
पूर्ण

अटल पूर्णांक scnम_लिखो_direntry(अक्षर *buf, माप_प्रकार size,
			      काष्ठा reiserfs_dir_entry *de)
अणु
	अक्षर name[20];

	स_नकल(name, de->de_name, de->de_namelen > 19 ? 19 : de->de_namelen);
	name[de->de_namelen > 19 ? 19 : de->de_namelen] = 0;
	वापस scnम_लिखो(buf, size, "\"%s\"==>[%d %d]",
			 name, de->de_dir_id, de->de_objectid);
पूर्ण

अटल पूर्णांक scnम_लिखो_block_head(अक्षर *buf, माप_प्रकार size, काष्ठा buffer_head *bh)
अणु
	वापस scnम_लिखो(buf, size,
			 "level=%d, nr_items=%d, free_space=%d rdkey ",
			 B_LEVEL(bh), B_NR_ITEMS(bh), B_FREE_SPACE(bh));
पूर्ण

अटल पूर्णांक scnम_लिखो_buffer_head(अक्षर *buf, माप_प्रकार size, काष्ठा buffer_head *bh)
अणु
	वापस scnम_लिखो(buf, size,
			 "dev %pg, size %zd, blocknr %llu, count %d, state 0x%lx, page %p, (%s, %s, %s)",
			 bh->b_bdev, bh->b_size,
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 atomic_पढ़ो(&(bh->b_count)),
			 bh->b_state, bh->b_page,
			 buffer_uptodate(bh) ? "UPTODATE" : "!UPTODATE",
			 buffer_dirty(bh) ? "DIRTY" : "CLEAN",
			 buffer_locked(bh) ? "LOCKED" : "UNLOCKED");
पूर्ण

अटल पूर्णांक scnम_लिखो_disk_child(अक्षर *buf, माप_प्रकार size, काष्ठा disk_child *dc)
अणु
	वापस scnम_लिखो(buf, size, "[dc_number=%d, dc_size=%u]",
			 dc_block_number(dc), dc_size(dc));
पूर्ण

अटल अक्षर *is_there_reiserfs_काष्ठा(अक्षर *fmt, पूर्णांक *what)
अणु
	अक्षर *k = fmt;

	जबतक ((k = म_अक्षर(k, '%')) != शून्य) अणु
		अगर (k[1] == 'k' || k[1] == 'K' || k[1] == 'h' || k[1] == 't' ||
		    k[1] == 'z' || k[1] == 'b' || k[1] == 'y' || k[1] == 'a') अणु
			*what = k[1];
			अवरोध;
		पूर्ण
		k++;
	पूर्ण
	वापस k;
पूर्ण

/*
 * debugging reiserfs we used to prपूर्णांक out a lot of dअगरferent
 * variables, like keys, item headers, buffer heads etc. Values of
 * most fields matter. So it took a दीर्घ समय just to ग_लिखो
 * appropriative prपूर्णांकk. With this reiserfs_warning you can use क्रमmat
 * specअगरication क्रम complex काष्ठाures like you used to करो with
 * म_लिखोs क्रम पूर्णांकegers, द्विगुनs and poपूर्णांकers. For instance, to prपूर्णांक
 * out key काष्ठाure you have to ग_लिखो just:
 * reiserfs_warning ("bad key %k", key);
 * instead of
 * prपूर्णांकk ("bad key %lu %lu %lu %lu", key->k_dir_id, key->k_objectid,
 *         key->k_offset, key->k_uniqueness);
 */
अटल DEFINE_SPINLOCK(error_lock);
अटल व्योम prepare_error_buf(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	अक्षर *fmt1 = fmt_buf;
	अक्षर *k;
	अक्षर *p = error_buf;
	अक्षर * स्थिर end = &error_buf[माप(error_buf)];
	पूर्णांक what;

	spin_lock(&error_lock);

	अगर (WARN_ON(strscpy(fmt_buf, fmt, माप(fmt_buf)) < 0)) अणु
		strscpy(error_buf, "format string too long", end - error_buf);
		जाओ out_unlock;
	पूर्ण

	जबतक ((k = is_there_reiserfs_काष्ठा(fmt1, &what)) != शून्य) अणु
		*k = 0;

		p += vscnम_लिखो(p, end - p, fmt1, args);

		चयन (what) अणु
		हाल 'k':
			p += scnम_लिखो_le_key(p, end - p,
					      बहु_तर्क(args, काष्ठा reiserfs_key *));
			अवरोध;
		हाल 'K':
			p += scnम_लिखो_cpu_key(p, end - p,
					       बहु_तर्क(args, काष्ठा cpu_key *));
			अवरोध;
		हाल 'h':
			p += scnम_लिखो_item_head(p, end - p,
						 बहु_तर्क(args, काष्ठा item_head *));
			अवरोध;
		हाल 't':
			p += scnम_लिखो_direntry(p, end - p,
						बहु_तर्क(args, काष्ठा reiserfs_dir_entry *));
			अवरोध;
		हाल 'y':
			p += scnम_लिखो_disk_child(p, end - p,
						  बहु_तर्क(args, काष्ठा disk_child *));
			अवरोध;
		हाल 'z':
			p += scnम_लिखो_block_head(p, end - p,
						  बहु_तर्क(args, काष्ठा buffer_head *));
			अवरोध;
		हाल 'b':
			p += scnम_लिखो_buffer_head(p, end - p,
						   बहु_तर्क(args, काष्ठा buffer_head *));
			अवरोध;
		हाल 'a':
			p += scnम_लिखो_de_head(p, end - p,
					       बहु_तर्क(args, काष्ठा reiserfs_de_head *));
			अवरोध;
		पूर्ण

		fmt1 = k + 2;
	पूर्ण
	p += vscnम_लिखो(p, end - p, fmt1, args);
out_unlock:
	spin_unlock(&error_lock);

पूर्ण

/*
 * in addition to usual conversion specअगरiers this accepts reiserfs
 * specअगरic conversion specअगरiers:
 * %k to prपूर्णांक little endian key,
 * %K to prपूर्णांक cpu key,
 * %h to prपूर्णांक item_head,
 * %t to prपूर्णांक directory entry
 * %z to prपूर्णांक block head (arg must be काष्ठा buffer_head *
 * %b to prपूर्णांक buffer_head
 */

#घोषणा करो_reiserfs_warning(fmt)\
अणु\
    बहु_सूची args;\
    बहु_शुरू( args, fmt );\
    prepare_error_buf( fmt, args );\
    बहु_पूर्ण( args );\
पूर्ण

व्योम __reiserfs_warning(काष्ठा super_block *sb, स्थिर अक्षर *id,
			 स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);
	अगर (sb)
		prपूर्णांकk(KERN_WARNING "REISERFS warning (device %s): %s%s%s: "
		       "%s\n", sb->s_id, id ? id : "", id ? " " : "",
		       function, error_buf);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "REISERFS warning: %s%s%s: %s\n",
		       id ? id : "", id ? " " : "", function, error_buf);
पूर्ण

/* No newline.. reiserfs_info calls can be followed by prपूर्णांकk's */
व्योम reiserfs_info(काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);
	अगर (sb)
		prपूर्णांकk(KERN_NOTICE "REISERFS (device %s): %s",
		       sb->s_id, error_buf);
	अन्यथा
		prपूर्णांकk(KERN_NOTICE "REISERFS %s:", error_buf);
पूर्ण

/* No newline.. reiserfs_prपूर्णांकk calls can be followed by prपूर्णांकk's */
अटल व्योम reiserfs_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);
	prपूर्णांकk(error_buf);
पूर्ण

व्योम reiserfs_debug(काष्ठा super_block *s, पूर्णांक level, स्थिर अक्षर *fmt, ...)
अणु
#अगर_घोषित CONFIG_REISERFS_CHECK
	करो_reiserfs_warning(fmt);
	अगर (s)
		prपूर्णांकk(KERN_DEBUG "REISERFS debug (device %s): %s\n",
		       s->s_id, error_buf);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "REISERFS debug: %s\n", error_buf);
#पूर्ण_अगर
पूर्ण

/*
 * The क्रमmat:
 *
 *          मुख्यtainer-errorid: [function-name:] message
 *
 *   where errorid is unique to the मुख्यtainer and function-name is
 *   optional, is recommended, so that anyone can easily find the bug
 *   with a simple grep क्रम the लघु to type string
 *   मुख्यtainer-errorid.  Don't bother with reusing errorids, there are
 *   lots of numbers out there.
 *
 *   Example:
 *
 *   reiserfs_panic(
 *     p_sb, "reiser-29: reiserfs_new_blocknrs: "
 *     "one of search_start or rn(%d) is equal to MAX_B_NUM,"
 *     "which means that we are optimizing location based on the "
 *     "bogus location of a temp buffer (%p).",
 *     rn, bh
 *   );
 *
 *   Regular panic()s someबार clear the screen beक्रमe the message can
 *   be पढ़ो, thus the need क्रम the जबतक loop.
 *
 *   Numbering scheme क्रम panic used by Vladimir and Anम_से_दy( Hans completely
 *   ignores this scheme, and considers it poपूर्णांकless complनिकासy):
 *
 *   panics in reiserfs_fs.h have numbers from 1000 to 1999
 *   super.c			2000 to 2999
 *   preserve.c (unused)	3000 to 3999
 *   biपंचांगap.c			4000 to 4999
 *   stree.c			5000 to 5999
 *   prपूर्णांकs.c			6000 to 6999
 *   namei.c			7000 to 7999
 *   fix_nodes.c		8000 to 8999
 *   dir.c			9000 to 9999
 *   lbalance.c			10000 to 10999
 *   ibalance.c			11000 to 11999 not पढ़ोy
 *   करो_balan.c			12000 to 12999
 *   inode.c			13000 to 13999
 *   file.c			14000 to 14999
 *   objectid.c			15000 - 15999
 *   buffer.c			16000 - 16999
 *   symlink.c			17000 - 17999
 *
 *  .  */

व्योम __reiserfs_panic(काष्ठा super_block *sb, स्थिर अक्षर *id,
		      स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);

#अगर_घोषित CONFIG_REISERFS_CHECK
	dump_stack();
#पूर्ण_अगर
	अगर (sb)
		prपूर्णांकk(KERN_WARNING "REISERFS panic (device %s): %s%s%s: %s\n",
		      sb->s_id, id ? id : "", id ? " " : "",
		      function, error_buf);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "REISERFS panic: %s%s%s: %s\n",
		      id ? id : "", id ? " " : "", function, error_buf);
	BUG();
पूर्ण

व्योम __reiserfs_error(काष्ठा super_block *sb, स्थिर अक्षर *id,
		      स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);

	BUG_ON(sb == शून्य);

	अगर (reiserfs_error_panic(sb))
		__reiserfs_panic(sb, id, function, error_buf);

	अगर (id && id[0])
		prपूर्णांकk(KERN_CRIT "REISERFS error (device %s): %s %s: %s\n",
		       sb->s_id, id, function, error_buf);
	अन्यथा
		prपूर्णांकk(KERN_CRIT "REISERFS error (device %s): %s: %s\n",
		       sb->s_id, function, error_buf);

	अगर (sb_rकरोnly(sb))
		वापस;

	reiserfs_info(sb, "Remounting filesystem read-only\n");
	sb->s_flags |= SB_RDONLY;
	reiserfs_पात_journal(sb, -EIO);
पूर्ण

व्योम reiserfs_पात(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...)
अणु
	करो_reiserfs_warning(fmt);

	अगर (reiserfs_error_panic(sb)) अणु
		panic(KERN_CRIT "REISERFS panic (device %s): %s\n", sb->s_id,
		      error_buf);
	पूर्ण

	अगर (reiserfs_is_journal_पातed(SB_JOURNAL(sb)))
		वापस;

	prपूर्णांकk(KERN_CRIT "REISERFS abort (device %s): %s\n", sb->s_id,
	       error_buf);

	sb->s_flags |= SB_RDONLY;
	reiserfs_पात_journal(sb, त्रुटि_सं);
पूर्ण

/*
 * this prपूर्णांकs पूर्णांकernal nodes (4 keys/items in line) (dc_number,
 * dc_size)[k_dirid, k_objectid, k_offset, k_uniqueness](dc_number,
 * dc_size)...
 */
अटल पूर्णांक prपूर्णांक_पूर्णांकernal(काष्ठा buffer_head *bh, पूर्णांक first, पूर्णांक last)
अणु
	काष्ठा reiserfs_key *key;
	काष्ठा disk_child *dc;
	पूर्णांक i;
	पूर्णांक from, to;

	अगर (!B_IS_KEYS_LEVEL(bh))
		वापस 1;

	check_पूर्णांकernal(bh);

	अगर (first == -1) अणु
		from = 0;
		to = B_NR_ITEMS(bh);
	पूर्ण अन्यथा अणु
		from = first;
		to = last < B_NR_ITEMS(bh) ? last : B_NR_ITEMS(bh);
	पूर्ण

	reiserfs_prपूर्णांकk("INTERNAL NODE (%ld) contains %z\n", bh->b_blocknr, bh);

	dc = B_N_CHILD(bh, from);
	reiserfs_prपूर्णांकk("PTR %d: %y ", from, dc);

	क्रम (i = from, key = पूर्णांकernal_key(bh, from), dc++; i < to;
	     i++, key++, dc++) अणु
		reiserfs_prपूर्णांकk("KEY %d: %k PTR %d: %y ", i, key, i + 1, dc);
		अगर (i && i % 4 == 0)
			prपूर्णांकk("\n");
	पूर्ण
	prपूर्णांकk("\n");
	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_leaf(काष्ठा buffer_head *bh, पूर्णांक prपूर्णांक_mode, पूर्णांक first,
		      पूर्णांक last)
अणु
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;
	पूर्णांक i, nr;
	पूर्णांक from, to;

	अगर (!B_IS_ITEMS_LEVEL(bh))
		वापस 1;

	check_leaf(bh);

	blkh = B_BLK_HEAD(bh);
	ih = item_head(bh, 0);
	nr = blkh_nr_item(blkh);

	prपूर्णांकk
	    ("\n===================================================================\n");
	reiserfs_prपूर्णांकk("LEAF NODE (%ld) contains %z\n", bh->b_blocknr, bh);

	अगर (!(prपूर्णांक_mode & PRINT_LEAF_ITEMS)) अणु
		reiserfs_prपूर्णांकk("FIRST ITEM_KEY: %k, LAST ITEM KEY: %k\n",
				&(ih->ih_key), &((ih + nr - 1)->ih_key));
		वापस 0;
	पूर्ण

	अगर (first < 0 || first > nr - 1)
		from = 0;
	अन्यथा
		from = first;

	अगर (last < 0 || last > nr)
		to = nr;
	अन्यथा
		to = last;

	ih += from;
	prपूर्णांकk
	    ("-------------------------------------------------------------------------------\n");
	prपूर्णांकk
	    ("|##|   type    |           key           | ilen | free_space | version | loc  |\n");
	क्रम (i = from; i < to; i++, ih++) अणु
		prपूर्णांकk
		    ("-------------------------------------------------------------------------------\n");
		reiserfs_prपूर्णांकk("|%2d| %h |\n", i, ih);
		अगर (prपूर्णांक_mode & PRINT_LEAF_ITEMS)
			op_prपूर्णांक_item(ih, ih_item_body(bh, ih));
	पूर्ण

	prपूर्णांकk
	    ("===================================================================\n");

	वापस 0;
पूर्ण

अक्षर *reiserfs_hashname(पूर्णांक code)
अणु
	अगर (code == YURA_HASH)
		वापस "rupasov";
	अगर (code == TEA_HASH)
		वापस "tea";
	अगर (code == R5_HASH)
		वापस "r5";

	वापस "unknown";
पूर्ण

/* वापस 1 अगर this is not super block */
अटल पूर्णांक prपूर्णांक_super_block(काष्ठा buffer_head *bh)
अणु
	काष्ठा reiserfs_super_block *rs =
	    (काष्ठा reiserfs_super_block *)(bh->b_data);
	पूर्णांक skipped, data_blocks;
	अक्षर *version;

	अगर (is_reiserfs_3_5(rs)) अणु
		version = "3.5";
	पूर्ण अन्यथा अगर (is_reiserfs_3_6(rs)) अणु
		version = "3.6";
	पूर्ण अन्यथा अगर (is_reiserfs_jr(rs)) अणु
		version = ((sb_version(rs) == REISERFS_VERSION_2) ?
			   "3.6" : "3.5");
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण

	prपूर्णांकk("%pg\'s super block is in block %llu\n", bh->b_bdev,
	       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
	prपूर्णांकk("Reiserfs version %s\n", version);
	prपूर्णांकk("Block count %u\n", sb_block_count(rs));
	prपूर्णांकk("Blocksize %d\n", sb_blocksize(rs));
	prपूर्णांकk("Free blocks %u\n", sb_मुक्त_blocks(rs));
	/*
	 * FIXME: this would be confusing अगर
	 * someone stores reiserfs super block in some data block ;)
//    skipped = (bh->b_blocknr * bh->b_size) / sb_blocksize(rs);
	 */
	skipped = bh->b_blocknr;
	data_blocks = sb_block_count(rs) - skipped - 1 - sb_bmap_nr(rs) -
	    (!is_reiserfs_jr(rs) ? sb_jp_journal_size(rs) +
	     1 : sb_reserved_क्रम_journal(rs)) - sb_मुक्त_blocks(rs);
	prपूर्णांकk
	    ("Busy blocks (skipped %d, bitmaps - %d, journal (or reserved) blocks - %d\n"
	     "1 super block, %d data blocks\n", skipped, sb_bmap_nr(rs),
	     (!is_reiserfs_jr(rs) ? (sb_jp_journal_size(rs) + 1) :
	      sb_reserved_क्रम_journal(rs)), data_blocks);
	prपूर्णांकk("Root block %u\n", sb_root_block(rs));
	prपूर्णांकk("Journal block (first) %d\n", sb_jp_journal_1st_block(rs));
	prपूर्णांकk("Journal dev %d\n", sb_jp_journal_dev(rs));
	prपूर्णांकk("Journal orig size %d\n", sb_jp_journal_size(rs));
	prपूर्णांकk("FS state %d\n", sb_fs_state(rs));
	prपूर्णांकk("Hash function \"%s\"\n",
	       reiserfs_hashname(sb_hash_function_code(rs)));

	prपूर्णांकk("Tree height %d\n", sb_tree_height(rs));
	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_desc_block(काष्ठा buffer_head *bh)
अणु
	काष्ठा reiserfs_journal_desc *desc;

	अगर (स_भेद(get_journal_desc_magic(bh), JOURNAL_DESC_MAGIC, 8))
		वापस 1;

	desc = (काष्ठा reiserfs_journal_desc *)(bh->b_data);
	prपूर्णांकk("Desc block %llu (j_trans_id %d, j_mount_id %d, j_len %d)",
	       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, get_desc_trans_id(desc),
	       get_desc_mount_id(desc), get_desc_trans_len(desc));

	वापस 0;
पूर्ण
/* ..., पूर्णांक prपूर्णांक_mode, पूर्णांक first, पूर्णांक last) */
व्योम prपूर्णांक_block(काष्ठा buffer_head *bh, ...)
अणु
	बहु_सूची args;
	पूर्णांक mode, first, last;

	अगर (!bh) अणु
		prपूर्णांकk("print_block: buffer is NULL\n");
		वापस;
	पूर्ण

	बहु_शुरू(args, bh);

	mode = बहु_तर्क(args, पूर्णांक);
	first = बहु_तर्क(args, पूर्णांक);
	last = बहु_तर्क(args, पूर्णांक);
	अगर (prपूर्णांक_leaf(bh, mode, first, last))
		अगर (prपूर्णांक_पूर्णांकernal(bh, first, last))
			अगर (prपूर्णांक_super_block(bh))
				अगर (prपूर्णांक_desc_block(bh))
					prपूर्णांकk
					    ("Block %llu contains unformatted data\n",
					     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	बहु_पूर्ण(args);
पूर्ण

अटल अक्षर prपूर्णांक_tb_buf[2048];

/* this stores initial state of tree balance in the prपूर्णांक_tb_buf */
व्योम store_prपूर्णांक_tb(काष्ठा tree_balance *tb)
अणु
	पूर्णांक h = 0;
	पूर्णांक i;
	काष्ठा buffer_head *tbSh, *tbFh;

	अगर (!tb)
		वापस;

	प्र_लिखो(prपूर्णांक_tb_buf, "\n"
		"BALANCING %d\n"
		"MODE=%c, ITEM_POS=%d POS_IN_ITEM=%d\n"
		"=====================================================================\n"
		"* h *    S    *    L    *    R    *   F   *   FL  *   FR  *  CFL  *  CFR  *\n",
		REISERFS_SB(tb->tb_sb)->s_करो_balance,
		tb->tb_mode, PATH_LAST_POSITION(tb->tb_path),
		tb->tb_path->pos_in_item);

	क्रम (h = 0; h < ARRAY_SIZE(tb->insert_size); h++) अणु
		अगर (PATH_H_PATH_OFFSET(tb->tb_path, h) <=
		    tb->tb_path->path_length
		    && PATH_H_PATH_OFFSET(tb->tb_path,
					  h) > ILLEGAL_PATH_ELEMENT_OFFSET) अणु
			tbSh = PATH_H_PBUFFER(tb->tb_path, h);
			tbFh = PATH_H_PPARENT(tb->tb_path, h);
		पूर्ण अन्यथा अणु
			tbSh = शून्य;
			tbFh = शून्य;
		पूर्ण
		प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
			"* %d * %3lld(%2d) * %3lld(%2d) * %3lld(%2d) * %5lld * %5lld * %5lld * %5lld * %5lld *\n",
			h,
			(tbSh) ? (दीर्घ दीर्घ)(tbSh->b_blocknr) : (-1LL),
			(tbSh) ? atomic_पढ़ो(&tbSh->b_count) : -1,
			(tb->L[h]) ? (दीर्घ दीर्घ)(tb->L[h]->b_blocknr) : (-1LL),
			(tb->L[h]) ? atomic_पढ़ो(&tb->L[h]->b_count) : -1,
			(tb->R[h]) ? (दीर्घ दीर्घ)(tb->R[h]->b_blocknr) : (-1LL),
			(tb->R[h]) ? atomic_पढ़ो(&tb->R[h]->b_count) : -1,
			(tbFh) ? (दीर्घ दीर्घ)(tbFh->b_blocknr) : (-1LL),
			(tb->FL[h]) ? (दीर्घ दीर्घ)(tb->FL[h]->
						  b_blocknr) : (-1LL),
			(tb->FR[h]) ? (दीर्घ दीर्घ)(tb->FR[h]->
						  b_blocknr) : (-1LL),
			(tb->CFL[h]) ? (दीर्घ दीर्घ)(tb->CFL[h]->
						   b_blocknr) : (-1LL),
			(tb->CFR[h]) ? (दीर्घ दीर्घ)(tb->CFR[h]->
						   b_blocknr) : (-1LL));
	पूर्ण

	प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
		"=====================================================================\n"
		"* h * size * ln * lb * rn * rb * blkn * s0 * s1 * s1b * s2 * s2b * curb * lk * rk *\n"
		"* 0 * %4d * %2d * %2d * %2d * %2d * %4d * %2d * %2d * %3d * %2d * %3d * %4d * %2d * %2d *\n",
		tb->insert_size[0], tb->lnum[0], tb->lbytes, tb->rnum[0],
		tb->rbytes, tb->blknum[0], tb->s0num, tb->snum[0],
		tb->sbytes[0], tb->snum[1], tb->sbytes[1],
		tb->cur_blknum, tb->lkey[0], tb->rkey[0]);

	/* this prपूर्णांकs balance parameters क्रम non-leaf levels */
	h = 0;
	करो अणु
		h++;
		प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
			"* %d * %4d * %2d *    * %2d *    * %2d *\n",
			h, tb->insert_size[h], tb->lnum[h], tb->rnum[h],
			tb->blknum[h]);
	पूर्ण जबतक (tb->insert_size[h]);

	प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
		"=====================================================================\n"
		"FEB list: ");

	/* prपूर्णांक FEB list (list of buffers in क्रमm (bh (b_blocknr, b_count), that will be used क्रम new nodes) */
	h = 0;
	क्रम (i = 0; i < ARRAY_SIZE(tb->FEB); i++)
		प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
			"%p (%llu %d)%s", tb->FEB[i],
			tb->FEB[i] ? (अचिन्हित दीर्घ दीर्घ)tb->FEB[i]->
			b_blocknr : 0ULL,
			tb->FEB[i] ? atomic_पढ़ो(&tb->FEB[i]->b_count) : 0,
			(i == ARRAY_SIZE(tb->FEB) - 1) ? "\n" : ", ");

	प्र_लिखो(prपूर्णांक_tb_buf + म_माप(prपूर्णांक_tb_buf),
		"======================== the end ====================================\n");
पूर्ण

व्योम prपूर्णांक_cur_tb(अक्षर *mes)
अणु
	prपूर्णांकk("%s\n%s", mes, prपूर्णांक_tb_buf);
पूर्ण

अटल व्योम check_leaf_block_head(काष्ठा buffer_head *bh)
अणु
	काष्ठा block_head *blkh;
	पूर्णांक nr;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	अगर (nr > (bh->b_size - BLKH_SIZE) / IH_SIZE)
		reiserfs_panic(शून्य, "vs-6010", "invalid item number %z",
			       bh);
	अगर (blkh_मुक्त_space(blkh) > bh->b_size - BLKH_SIZE - IH_SIZE * nr)
		reiserfs_panic(शून्य, "vs-6020", "invalid free space %z",
			       bh);

पूर्ण

अटल व्योम check_पूर्णांकernal_block_head(काष्ठा buffer_head *bh)
अणु
	अगर (!(B_LEVEL(bh) > DISK_LEAF_NODE_LEVEL && B_LEVEL(bh) <= MAX_HEIGHT))
		reiserfs_panic(शून्य, "vs-6025", "invalid level %z", bh);

	अगर (B_NR_ITEMS(bh) > (bh->b_size - BLKH_SIZE) / IH_SIZE)
		reiserfs_panic(शून्य, "vs-6030", "invalid item number %z", bh);

	अगर (B_FREE_SPACE(bh) !=
	    bh->b_size - BLKH_SIZE - KEY_SIZE * B_NR_ITEMS(bh) -
	    DC_SIZE * (B_NR_ITEMS(bh) + 1))
		reiserfs_panic(शून्य, "vs-6040", "invalid free space %z", bh);

पूर्ण

व्योम check_leaf(काष्ठा buffer_head *bh)
अणु
	पूर्णांक i;
	काष्ठा item_head *ih;

	अगर (!bh)
		वापस;
	check_leaf_block_head(bh);
	क्रम (i = 0, ih = item_head(bh, 0); i < B_NR_ITEMS(bh); i++, ih++)
		op_check_item(ih, ih_item_body(bh, ih));
पूर्ण

व्योम check_पूर्णांकernal(काष्ठा buffer_head *bh)
अणु
	अगर (!bh)
		वापस;
	check_पूर्णांकernal_block_head(bh);
पूर्ण

व्योम prपूर्णांक_statistics(काष्ठा super_block *s)
अणु

	/*
	   prपूर्णांकk ("reiserfs_put_super: session statistics: balances %d, fix_nodes %d, \
	   bmap with search %d, without %d, dir2ind %d, ind2dir %d\न",
	   REISERFS_SB(s)->s_करो_balance, REISERFS_SB(s)->s_fix_nodes,
	   REISERFS_SB(s)->s_bmaps, REISERFS_SB(s)->s_bmaps_without_search,
	   REISERFS_SB(s)->s_direct2indirect, REISERFS_SB(s)->s_indirect2direct);
	 */

पूर्ण
