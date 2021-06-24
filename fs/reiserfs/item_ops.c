<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/समय.स>
#समावेश "reiserfs.h"

/*
 * this contains item handlers क्रम old item types: sd, direct,
 * indirect, directory
 */

/*
 * and where are the comments? how about saying where we can find an
 * explanation of each item handler method? -Hans
 */

/* stat data functions */
अटल पूर्णांक sd_bytes_number(काष्ठा item_head *ih, पूर्णांक block_size)
अणु
	वापस 0;
पूर्ण

अटल व्योम sd_decrement_key(काष्ठा cpu_key *key)
अणु
	key->on_disk_key.k_objectid--;
	set_cpu_key_k_type(key, TYPE_ANY);
	set_cpu_key_k_offset(key, (loff_t)(~0ULL >> 1));
पूर्ण

अटल पूर्णांक sd_is_left_mergeable(काष्ठा reiserfs_key *key, अचिन्हित दीर्घ bsize)
अणु
	वापस 0;
पूर्ण

अटल व्योम sd_prपूर्णांक_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	prपूर्णांकk("\tmode | size | nlinks | first direct | mtime\n");
	अगर (stat_data_v1(ih)) अणु
		काष्ठा stat_data_v1 *sd = (काष्ठा stat_data_v1 *)item;

		prपूर्णांकk("\t0%-6o | %6u | %2u | %d | %u\n", sd_v1_mode(sd),
		       sd_v1_size(sd), sd_v1_nlink(sd),
		       sd_v1_first_direct_byte(sd),
		       sd_v1_mसमय(sd));
	पूर्ण अन्यथा अणु
		काष्ठा stat_data *sd = (काष्ठा stat_data *)item;

		prपूर्णांकk("\t0%-6o | %6llu | %2u | %d | %u\n", sd_v2_mode(sd),
		       (अचिन्हित दीर्घ दीर्घ)sd_v2_size(sd), sd_v2_nlink(sd),
		       sd_v2_rdev(sd), sd_v2_mसमय(sd));
	पूर्ण
पूर्ण

अटल व्योम sd_check_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	/* unused */
पूर्ण

अटल पूर्णांक sd_create_vi(काष्ठा भव_node *vn,
			काष्ठा भव_item *vi,
			पूर्णांक is_affected, पूर्णांक insert_size)
अणु
	vi->vi_index = TYPE_STAT_DATA;
	वापस 0;
पूर्ण

अटल पूर्णांक sd_check_left(काष्ठा भव_item *vi, पूर्णांक मुक्त,
			 पूर्णांक start_skip, पूर्णांक end_skip)
अणु
	BUG_ON(start_skip || end_skip);
	वापस -1;
पूर्ण

अटल पूर्णांक sd_check_right(काष्ठा भव_item *vi, पूर्णांक मुक्त)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक sd_part_size(काष्ठा भव_item *vi, पूर्णांक first, पूर्णांक count)
अणु
	BUG_ON(count);
	वापस 0;
पूर्ण

अटल पूर्णांक sd_unit_num(काष्ठा भव_item *vi)
अणु
	वापस vi->vi_item_len - IH_SIZE;
पूर्ण

अटल व्योम sd_prपूर्णांक_vi(काष्ठा भव_item *vi)
अणु
	reiserfs_warning(शून्य, "reiserfs-16100",
			 "STATDATA, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
पूर्ण

अटल काष्ठा item_operations stat_data_ops = अणु
	.bytes_number = sd_bytes_number,
	.decrement_key = sd_decrement_key,
	.is_left_mergeable = sd_is_left_mergeable,
	.prपूर्णांक_item = sd_prपूर्णांक_item,
	.check_item = sd_check_item,

	.create_vi = sd_create_vi,
	.check_left = sd_check_left,
	.check_right = sd_check_right,
	.part_size = sd_part_size,
	.unit_num = sd_unit_num,
	.prपूर्णांक_vi = sd_prपूर्णांक_vi
पूर्ण;

/* direct item functions */
अटल पूर्णांक direct_bytes_number(काष्ठा item_head *ih, पूर्णांक block_size)
अणु
	वापस ih_item_len(ih);
पूर्ण

/* FIXME: this should probably चयन to indirect as well */
अटल व्योम direct_decrement_key(काष्ठा cpu_key *key)
अणु
	cpu_key_k_offset_dec(key);
	अगर (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
पूर्ण

अटल पूर्णांक direct_is_left_mergeable(काष्ठा reiserfs_key *key,
				    अचिन्हित दीर्घ bsize)
अणु
	पूर्णांक version = le_key_version(key);
	वापस ((le_key_k_offset(version, key) & (bsize - 1)) != 1);
पूर्ण

अटल व्योम direct_prपूर्णांक_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	पूर्णांक j = 0;

/*    वापस; */
	prपूर्णांकk("\"");
	जबतक (j < ih_item_len(ih))
		prपूर्णांकk("%c", item[j++]);
	prपूर्णांकk("\"\n");
पूर्ण

अटल व्योम direct_check_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	/* unused */
पूर्ण

अटल पूर्णांक direct_create_vi(काष्ठा भव_node *vn,
			    काष्ठा भव_item *vi,
			    पूर्णांक is_affected, पूर्णांक insert_size)
अणु
	vi->vi_index = TYPE_सूचीECT;
	वापस 0;
पूर्ण

अटल पूर्णांक direct_check_left(काष्ठा भव_item *vi, पूर्णांक मुक्त,
			     पूर्णांक start_skip, पूर्णांक end_skip)
अणु
	पूर्णांक bytes;

	bytes = मुक्त - मुक्त % 8;
	वापस bytes ? : -1;
पूर्ण

अटल पूर्णांक direct_check_right(काष्ठा भव_item *vi, पूर्णांक मुक्त)
अणु
	वापस direct_check_left(vi, मुक्त, 0, 0);
पूर्ण

अटल पूर्णांक direct_part_size(काष्ठा भव_item *vi, पूर्णांक first, पूर्णांक count)
अणु
	वापस count;
पूर्ण

अटल पूर्णांक direct_unit_num(काष्ठा भव_item *vi)
अणु
	वापस vi->vi_item_len - IH_SIZE;
पूर्ण

अटल व्योम direct_prपूर्णांक_vi(काष्ठा भव_item *vi)
अणु
	reiserfs_warning(शून्य, "reiserfs-16101",
			 "DIRECT, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
पूर्ण

अटल काष्ठा item_operations direct_ops = अणु
	.bytes_number = direct_bytes_number,
	.decrement_key = direct_decrement_key,
	.is_left_mergeable = direct_is_left_mergeable,
	.prपूर्णांक_item = direct_prपूर्णांक_item,
	.check_item = direct_check_item,

	.create_vi = direct_create_vi,
	.check_left = direct_check_left,
	.check_right = direct_check_right,
	.part_size = direct_part_size,
	.unit_num = direct_unit_num,
	.prपूर्णांक_vi = direct_prपूर्णांक_vi
पूर्ण;

/* indirect item functions */
अटल पूर्णांक indirect_bytes_number(काष्ठा item_head *ih, पूर्णांक block_size)
अणु
	वापस ih_item_len(ih) / UNFM_P_SIZE * block_size;
पूर्ण

/* decrease offset, अगर it becomes 0, change type to stat data */
अटल व्योम indirect_decrement_key(काष्ठा cpu_key *key)
अणु
	cpu_key_k_offset_dec(key);
	अगर (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
पूर्ण

/* अगर it is not first item of the body, then it is mergeable */
अटल पूर्णांक indirect_is_left_mergeable(काष्ठा reiserfs_key *key,
				      अचिन्हित दीर्घ bsize)
अणु
	पूर्णांक version = le_key_version(key);
	वापस (le_key_k_offset(version, key) != 1);
पूर्ण

/* prपूर्णांकing of indirect item */
अटल व्योम start_new_sequence(__u32 * start, पूर्णांक *len, __u32 new)
अणु
	*start = new;
	*len = 1;
पूर्ण

अटल पूर्णांक sequence_finished(__u32 start, पूर्णांक *len, __u32 new)
अणु
	अगर (start == पूर्णांक_उच्च)
		वापस 1;

	अगर (start == 0 && new == 0) अणु
		(*len)++;
		वापस 0;
	पूर्ण
	अगर (start != 0 && (start + *len) == new) अणु
		(*len)++;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम prपूर्णांक_sequence(__u32 start, पूर्णांक len)
अणु
	अगर (start == पूर्णांक_उच्च)
		वापस;

	अगर (len == 1)
		prपूर्णांकk(" %d", start);
	अन्यथा
		prपूर्णांकk(" %d(%d)", start, len);
पूर्ण

अटल व्योम indirect_prपूर्णांक_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	पूर्णांक j;
	__le32 *unp;
	__u32 prev = पूर्णांक_उच्च;
	पूर्णांक num = 0;

	unp = (__le32 *) item;

	अगर (ih_item_len(ih) % UNFM_P_SIZE)
		reiserfs_warning(शून्य, "reiserfs-16102", "invalid item len");

	prपूर्णांकk("%d pointers\n[ ", (पूर्णांक)I_UNFM_NUM(ih));
	क्रम (j = 0; j < I_UNFM_NUM(ih); j++) अणु
		अगर (sequence_finished(prev, &num, get_block_num(unp, j))) अणु
			prपूर्णांक_sequence(prev, num);
			start_new_sequence(&prev, &num, get_block_num(unp, j));
		पूर्ण
	पूर्ण
	prपूर्णांक_sequence(prev, num);
	prपूर्णांकk("]\n");
पूर्ण

अटल व्योम indirect_check_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	/* unused */
पूर्ण

अटल पूर्णांक indirect_create_vi(काष्ठा भव_node *vn,
			      काष्ठा भव_item *vi,
			      पूर्णांक is_affected, पूर्णांक insert_size)
अणु
	vi->vi_index = TYPE_INसूचीECT;
	वापस 0;
पूर्ण

अटल पूर्णांक indirect_check_left(काष्ठा भव_item *vi, पूर्णांक मुक्त,
			       पूर्णांक start_skip, पूर्णांक end_skip)
अणु
	पूर्णांक bytes;

	bytes = मुक्त - मुक्त % UNFM_P_SIZE;
	वापस bytes ? : -1;
पूर्ण

अटल पूर्णांक indirect_check_right(काष्ठा भव_item *vi, पूर्णांक मुक्त)
अणु
	वापस indirect_check_left(vi, मुक्त, 0, 0);
पूर्ण

/*
 * वापस size in bytes of 'units' units. If first == 0 - calculate
 * from the head (left), otherwise - from tail (right)
 */
अटल पूर्णांक indirect_part_size(काष्ठा भव_item *vi, पूर्णांक first, पूर्णांक units)
अणु
	/* unit of indirect item is byte (yet) */
	वापस units;
पूर्ण

अटल पूर्णांक indirect_unit_num(काष्ठा भव_item *vi)
अणु
	/* unit of indirect item is byte (yet) */
	वापस vi->vi_item_len - IH_SIZE;
पूर्ण

अटल व्योम indirect_prपूर्णांक_vi(काष्ठा भव_item *vi)
अणु
	reiserfs_warning(शून्य, "reiserfs-16103",
			 "INDIRECT, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
पूर्ण

अटल काष्ठा item_operations indirect_ops = अणु
	.bytes_number = indirect_bytes_number,
	.decrement_key = indirect_decrement_key,
	.is_left_mergeable = indirect_is_left_mergeable,
	.prपूर्णांक_item = indirect_prपूर्णांक_item,
	.check_item = indirect_check_item,

	.create_vi = indirect_create_vi,
	.check_left = indirect_check_left,
	.check_right = indirect_check_right,
	.part_size = indirect_part_size,
	.unit_num = indirect_unit_num,
	.prपूर्णांक_vi = indirect_prपूर्णांक_vi
पूर्ण;

/* direntry functions */
अटल पूर्णांक direntry_bytes_number(काष्ठा item_head *ih, पूर्णांक block_size)
अणु
	reiserfs_warning(शून्य, "vs-16090",
			 "bytes number is asked for direntry");
	वापस 0;
पूर्ण

अटल व्योम direntry_decrement_key(काष्ठा cpu_key *key)
अणु
	cpu_key_k_offset_dec(key);
	अगर (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
पूर्ण

अटल पूर्णांक direntry_is_left_mergeable(काष्ठा reiserfs_key *key,
				      अचिन्हित दीर्घ bsize)
अणु
	अगर (le32_to_cpu(key->u.k_offset_v1.k_offset) == DOT_OFFSET)
		वापस 0;
	वापस 1;

पूर्ण

अटल व्योम direntry_prपूर्णांक_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	पूर्णांक i;
	पूर्णांक namelen;
	काष्ठा reiserfs_de_head *deh;
	अक्षर *name;
	अटल अक्षर namebuf[80];

	prपूर्णांकk("\n # %-15s%-30s%-15s%-15s%-15s\n", "Name",
	       "Key of pointed object", "Hash", "Gen number", "Status");

	deh = (काष्ठा reiserfs_de_head *)item;

	क्रम (i = 0; i < ih_entry_count(ih); i++, deh++) अणु
		namelen =
		    (i ? (deh_location(deh - 1)) : ih_item_len(ih)) -
		    deh_location(deh);
		name = item + deh_location(deh);
		अगर (name[namelen - 1] == 0)
			namelen = म_माप(name);
		namebuf[0] = '"';
		अगर (namelen > माप(namebuf) - 3) अणु
			म_नकलन(namebuf + 1, name, माप(namebuf) - 3);
			namebuf[माप(namebuf) - 2] = '"';
			namebuf[माप(namebuf) - 1] = 0;
		पूर्ण अन्यथा अणु
			स_नकल(namebuf + 1, name, namelen);
			namebuf[namelen + 1] = '"';
			namebuf[namelen + 2] = 0;
		पूर्ण

		prपूर्णांकk("%d:  %-15s%-15d%-15d%-15lld%-15lld(%s)\n",
		       i, namebuf,
		       deh_dir_id(deh), deh_objectid(deh),
		       GET_HASH_VALUE(deh_offset(deh)),
		       GET_GENERATION_NUMBER((deh_offset(deh))),
		       (de_hidden(deh)) ? "HIDDEN" : "VISIBLE");
	पूर्ण
पूर्ण

अटल व्योम direntry_check_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	पूर्णांक i;
	काष्ठा reiserfs_de_head *deh;

	/* unused */
	deh = (काष्ठा reiserfs_de_head *)item;
	क्रम (i = 0; i < ih_entry_count(ih); i++, deh++) अणु
		;
	पूर्ण
पूर्ण

#घोषणा सूचीENTRY_VI_FIRST_सूचीENTRY_ITEM 1

/*
 * function वापसs old entry number in directory item in real node
 * using new entry number in भव item in भव node
 */
अटल अंतरभूत पूर्णांक old_entry_num(पूर्णांक is_affected, पूर्णांक भव_entry_num,
				पूर्णांक pos_in_item, पूर्णांक mode)
अणु
	अगर (mode == M_INSERT || mode == M_DELETE)
		वापस भव_entry_num;

	अगर (!is_affected)
		/* cut or paste is applied to another item */
		वापस भव_entry_num;

	अगर (भव_entry_num < pos_in_item)
		वापस भव_entry_num;

	अगर (mode == M_CUT)
		वापस भव_entry_num + 1;

	RFALSE(mode != M_PASTE || भव_entry_num == 0,
	       "vs-8015: old_entry_num: mode must be M_PASTE (mode = \'%c\'",
	       mode);

	वापस भव_entry_num - 1;
पूर्ण

/*
 * Create an array of sizes of directory entries क्रम भव
 * item. Return space used by an item. FIXME: no control over
 * consuming of space used by this item handler
 */
अटल पूर्णांक direntry_create_vi(काष्ठा भव_node *vn,
			      काष्ठा भव_item *vi,
			      पूर्णांक is_affected, पूर्णांक insert_size)
अणु
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;
	पूर्णांक i, j;
	पूर्णांक size = माप(काष्ठा direntry_uarea);
	काष्ठा reiserfs_de_head *deh;

	vi->vi_index = TYPE_सूचीENTRY;

	BUG_ON(!(vi->vi_ih) || !vi->vi_item);

	dir_u->flags = 0;
	अगर (le_ih_k_offset(vi->vi_ih) == DOT_OFFSET)
		dir_u->flags |= सूचीENTRY_VI_FIRST_सूचीENTRY_ITEM;

	deh = (काष्ठा reiserfs_de_head *)(vi->vi_item);

	/* भव directory item have this amount of entry after */
	dir_u->entry_count = ih_entry_count(vi->vi_ih) +
	    ((is_affected) ? ((vn->vn_mode == M_CUT) ? -1 :
			      (vn->vn_mode == M_PASTE ? 1 : 0)) : 0);

	क्रम (i = 0; i < dir_u->entry_count; i++) अणु
		j = old_entry_num(is_affected, i, vn->vn_pos_in_item,
				  vn->vn_mode);
		dir_u->entry_sizes[i] =
		    (j ? deh_location(&deh[j - 1]) : ih_item_len(vi->vi_ih)) -
		    deh_location(&deh[j]) + DEH_SIZE;
	पूर्ण

	size += (dir_u->entry_count * माप(लघु));

	/* set size of pasted entry */
	अगर (is_affected && vn->vn_mode == M_PASTE)
		dir_u->entry_sizes[vn->vn_pos_in_item] = insert_size;

#अगर_घोषित CONFIG_REISERFS_CHECK
	/* compare total size of entries with item length */
	अणु
		पूर्णांक k, l;

		l = 0;
		क्रम (k = 0; k < dir_u->entry_count; k++)
			l += dir_u->entry_sizes[k];

		अगर (l + IH_SIZE != vi->vi_item_len +
		    ((is_affected
		      && (vn->vn_mode == M_PASTE
			  || vn->vn_mode == M_CUT)) ? insert_size : 0)) अणु
			reiserfs_panic(शून्य, "vs-8025", "(mode==%c, "
				       "insert_size==%d), invalid length of "
				       "directory item",
				       vn->vn_mode, insert_size);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस size;

पूर्ण

/*
 * वापस number of entries which may fit पूर्णांकo specअगरied amount of
 * मुक्त space, or -1 अगर मुक्त space is not enough even क्रम 1 entry
 */
अटल पूर्णांक direntry_check_left(काष्ठा भव_item *vi, पूर्णांक मुक्त,
			       पूर्णांक start_skip, पूर्णांक end_skip)
अणु
	पूर्णांक i;
	पूर्णांक entries = 0;
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;

	क्रम (i = start_skip; i < dir_u->entry_count - end_skip; i++) अणु
		/* i-th entry करोesn't fit पूर्णांकo the reमुख्यing मुक्त space */
		अगर (dir_u->entry_sizes[i] > मुक्त)
			अवरोध;

		मुक्त -= dir_u->entry_sizes[i];
		entries++;
	पूर्ण

	अगर (entries == dir_u->entry_count) अणु
		reiserfs_panic(शून्य, "item_ops-1",
			       "free space %d, entry_count %d", मुक्त,
			       dir_u->entry_count);
	पूर्ण

	/* "." and ".." can not be separated from each other */
	अगर (start_skip == 0 && (dir_u->flags & सूचीENTRY_VI_FIRST_सूचीENTRY_ITEM)
	    && entries < 2)
		entries = 0;

	वापस entries ? : -1;
पूर्ण

अटल पूर्णांक direntry_check_right(काष्ठा भव_item *vi, पूर्णांक मुक्त)
अणु
	पूर्णांक i;
	पूर्णांक entries = 0;
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;

	क्रम (i = dir_u->entry_count - 1; i >= 0; i--) अणु
		/* i-th entry करोesn't fit पूर्णांकo the reमुख्यing मुक्त space */
		अगर (dir_u->entry_sizes[i] > मुक्त)
			अवरोध;

		मुक्त -= dir_u->entry_sizes[i];
		entries++;
	पूर्ण
	BUG_ON(entries == dir_u->entry_count);

	/* "." and ".." can not be separated from each other */
	अगर ((dir_u->flags & सूचीENTRY_VI_FIRST_सूचीENTRY_ITEM)
	    && entries > dir_u->entry_count - 2)
		entries = dir_u->entry_count - 2;

	वापस entries ? : -1;
पूर्ण

/* sum of entry sizes between from-th and to-th entries including both edges */
अटल पूर्णांक direntry_part_size(काष्ठा भव_item *vi, पूर्णांक first, पूर्णांक count)
अणु
	पूर्णांक i, retval;
	पूर्णांक from, to;
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;

	retval = 0;
	अगर (first == 0)
		from = 0;
	अन्यथा
		from = dir_u->entry_count - count;
	to = from + count - 1;

	क्रम (i = from; i <= to; i++)
		retval += dir_u->entry_sizes[i];

	वापस retval;
पूर्ण

अटल पूर्णांक direntry_unit_num(काष्ठा भव_item *vi)
अणु
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;

	वापस dir_u->entry_count;
पूर्ण

अटल व्योम direntry_prपूर्णांक_vi(काष्ठा भव_item *vi)
अणु
	पूर्णांक i;
	काष्ठा direntry_uarea *dir_u = vi->vi_uarea;

	reiserfs_warning(शून्य, "reiserfs-16104",
			 "DIRENTRY, index %d, type 0x%x, %h, flags 0x%x",
			 vi->vi_index, vi->vi_type, vi->vi_ih, dir_u->flags);
	prपूर्णांकk("%d entries: ", dir_u->entry_count);
	क्रम (i = 0; i < dir_u->entry_count; i++)
		prपूर्णांकk("%d ", dir_u->entry_sizes[i]);
	prपूर्णांकk("\n");
पूर्ण

अटल काष्ठा item_operations direntry_ops = अणु
	.bytes_number = direntry_bytes_number,
	.decrement_key = direntry_decrement_key,
	.is_left_mergeable = direntry_is_left_mergeable,
	.prपूर्णांक_item = direntry_prपूर्णांक_item,
	.check_item = direntry_check_item,

	.create_vi = direntry_create_vi,
	.check_left = direntry_check_left,
	.check_right = direntry_check_right,
	.part_size = direntry_part_size,
	.unit_num = direntry_unit_num,
	.prपूर्णांक_vi = direntry_prपूर्णांक_vi
पूर्ण;

/* Error catching functions to catch errors caused by incorrect item types. */
अटल पूर्णांक errcatch_bytes_number(काष्ठा item_head *ih, पूर्णांक block_size)
अणु
	reiserfs_warning(शून्य, "green-16001",
			 "Invalid item type observed, run fsck ASAP");
	वापस 0;
पूर्ण

अटल व्योम errcatch_decrement_key(काष्ठा cpu_key *key)
अणु
	reiserfs_warning(शून्य, "green-16002",
			 "Invalid item type observed, run fsck ASAP");
पूर्ण

अटल पूर्णांक errcatch_is_left_mergeable(काष्ठा reiserfs_key *key,
				      अचिन्हित दीर्घ bsize)
अणु
	reiserfs_warning(शून्य, "green-16003",
			 "Invalid item type observed, run fsck ASAP");
	वापस 0;
पूर्ण

अटल व्योम errcatch_prपूर्णांक_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	reiserfs_warning(शून्य, "green-16004",
			 "Invalid item type observed, run fsck ASAP");
पूर्ण

अटल व्योम errcatch_check_item(काष्ठा item_head *ih, अक्षर *item)
अणु
	reiserfs_warning(शून्य, "green-16005",
			 "Invalid item type observed, run fsck ASAP");
पूर्ण

अटल पूर्णांक errcatch_create_vi(काष्ठा भव_node *vn,
			      काष्ठा भव_item *vi,
			      पूर्णांक is_affected, पूर्णांक insert_size)
अणु
	reiserfs_warning(शून्य, "green-16006",
			 "Invalid item type observed, run fsck ASAP");
	/*
	 * We might वापस -1 here as well, but it won't help as
	 * create_भव_node() from where this operation is called
	 * from is of वापस type व्योम.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक errcatch_check_left(काष्ठा भव_item *vi, पूर्णांक मुक्त,
			       पूर्णांक start_skip, पूर्णांक end_skip)
अणु
	reiserfs_warning(शून्य, "green-16007",
			 "Invalid item type observed, run fsck ASAP");
	वापस -1;
पूर्ण

अटल पूर्णांक errcatch_check_right(काष्ठा भव_item *vi, पूर्णांक मुक्त)
अणु
	reiserfs_warning(शून्य, "green-16008",
			 "Invalid item type observed, run fsck ASAP");
	वापस -1;
पूर्ण

अटल पूर्णांक errcatch_part_size(काष्ठा भव_item *vi, पूर्णांक first, पूर्णांक count)
अणु
	reiserfs_warning(शून्य, "green-16009",
			 "Invalid item type observed, run fsck ASAP");
	वापस 0;
पूर्ण

अटल पूर्णांक errcatch_unit_num(काष्ठा भव_item *vi)
अणु
	reiserfs_warning(शून्य, "green-16010",
			 "Invalid item type observed, run fsck ASAP");
	वापस 0;
पूर्ण

अटल व्योम errcatch_prपूर्णांक_vi(काष्ठा भव_item *vi)
अणु
	reiserfs_warning(शून्य, "green-16011",
			 "Invalid item type observed, run fsck ASAP");
पूर्ण

अटल काष्ठा item_operations errcatch_ops = अणु
	.bytes_number = errcatch_bytes_number,
	.decrement_key = errcatch_decrement_key,
	.is_left_mergeable = errcatch_is_left_mergeable,
	.prपूर्णांक_item = errcatch_prपूर्णांक_item,
	.check_item = errcatch_check_item,

	.create_vi = errcatch_create_vi,
	.check_left = errcatch_check_left,
	.check_right = errcatch_check_right,
	.part_size = errcatch_part_size,
	.unit_num = errcatch_unit_num,
	.prपूर्णांक_vi = errcatch_prपूर्णांक_vi
पूर्ण;

#अगर ! (TYPE_STAT_DATA == 0 && TYPE_INसूचीECT == 1 && TYPE_सूचीECT == 2 && TYPE_सूचीENTRY == 3)
#त्रुटि Item types must use disk-क्रमmat asचिन्हित values.
#पूर्ण_अगर

काष्ठा item_operations *item_ops[TYPE_ANY + 1] = अणु
	&stat_data_ops,
	&indirect_ops,
	&direct_ops,
	&direntry_ops,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	&errcatch_ops		/* This is to catch errors with invalid type (15th entry क्रम TYPE_ANY) */
पूर्ण;
