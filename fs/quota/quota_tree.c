<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	vfsv0 quota IO operations on file
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/dqblk_v2.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/quotaops.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "quota_tree.h"

MODULE_AUTHOR("Jan Kara");
MODULE_DESCRIPTION("Quota trie support");
MODULE_LICENSE("GPL");

#घोषणा __QUOTA_QT_PARANOIA

अटल पूर्णांक __get_index(काष्ठा qtree_mem_dqinfo *info, qid_t id, पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक epb = info->dqi_usable_bs >> 2;

	depth = info->dqi_qtree_depth - depth - 1;
	जबतक (depth--)
		id /= epb;
	वापस id % epb;
पूर्ण

अटल पूर्णांक get_index(काष्ठा qtree_mem_dqinfo *info, काष्ठा kqid qid, पूर्णांक depth)
अणु
	qid_t id = from_kqid(&init_user_ns, qid);

	वापस __get_index(info, id, depth);
पूर्ण

/* Number of entries in one blocks */
अटल पूर्णांक qtree_dqstr_in_blk(काष्ठा qtree_mem_dqinfo *info)
अणु
	वापस (info->dqi_usable_bs - माप(काष्ठा qt_disk_dqdbheader))
	       / info->dqi_entry_size;
पूर्ण

अटल अक्षर *getdqbuf(माप_प्रकार size)
अणु
	अक्षर *buf = kदो_स्मृति(size, GFP_NOFS);
	अगर (!buf)
		prपूर्णांकk(KERN_WARNING
		       "VFS: Not enough memory for quota buffers.\n");
	वापस buf;
पूर्ण

अटल sमाप_प्रकार पढ़ो_blk(काष्ठा qtree_mem_dqinfo *info, uपूर्णांक blk, अक्षर *buf)
अणु
	काष्ठा super_block *sb = info->dqi_sb;

	स_रखो(buf, 0, info->dqi_usable_bs);
	वापस sb->s_op->quota_पढ़ो(sb, info->dqi_type, buf,
	       info->dqi_usable_bs, (loff_t)blk << info->dqi_blocksize_bits);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_blk(काष्ठा qtree_mem_dqinfo *info, uपूर्णांक blk, अक्षर *buf)
अणु
	काष्ठा super_block *sb = info->dqi_sb;
	sमाप_प्रकार ret;

	ret = sb->s_op->quota_ग_लिखो(sb, info->dqi_type, buf,
	       info->dqi_usable_bs, (loff_t)blk << info->dqi_blocksize_bits);
	अगर (ret != info->dqi_usable_bs) अणु
		quota_error(sb, "dquota write failed");
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/* Remove empty block from list and वापस it */
अटल पूर्णांक get_मुक्त_dqblk(काष्ठा qtree_mem_dqinfo *info)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	काष्ठा qt_disk_dqdbheader *dh = (काष्ठा qt_disk_dqdbheader *)buf;
	पूर्णांक ret, blk;

	अगर (!buf)
		वापस -ENOMEM;
	अगर (info->dqi_मुक्त_blk) अणु
		blk = info->dqi_मुक्त_blk;
		ret = पढ़ो_blk(info, blk, buf);
		अगर (ret < 0)
			जाओ out_buf;
		info->dqi_मुक्त_blk = le32_to_cpu(dh->dqdh_next_मुक्त);
	पूर्ण
	अन्यथा अणु
		स_रखो(buf, 0, info->dqi_usable_bs);
		/* Assure block allocation... */
		ret = ग_लिखो_blk(info, info->dqi_blocks, buf);
		अगर (ret < 0)
			जाओ out_buf;
		blk = info->dqi_blocks++;
	पूर्ण
	mark_info_dirty(info->dqi_sb, info->dqi_type);
	ret = blk;
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Insert empty block to the list */
अटल पूर्णांक put_मुक्त_dqblk(काष्ठा qtree_mem_dqinfo *info, अक्षर *buf, uपूर्णांक blk)
अणु
	काष्ठा qt_disk_dqdbheader *dh = (काष्ठा qt_disk_dqdbheader *)buf;
	पूर्णांक err;

	dh->dqdh_next_मुक्त = cpu_to_le32(info->dqi_मुक्त_blk);
	dh->dqdh_prev_मुक्त = cpu_to_le32(0);
	dh->dqdh_entries = cpu_to_le16(0);
	err = ग_लिखो_blk(info, blk, buf);
	अगर (err < 0)
		वापस err;
	info->dqi_मुक्त_blk = blk;
	mark_info_dirty(info->dqi_sb, info->dqi_type);
	वापस 0;
पूर्ण

/* Remove given block from the list of blocks with मुक्त entries */
अटल पूर्णांक हटाओ_मुक्त_dqentry(काष्ठा qtree_mem_dqinfo *info, अक्षर *buf,
			       uपूर्णांक blk)
अणु
	अक्षर *पंचांगpbuf = getdqbuf(info->dqi_usable_bs);
	काष्ठा qt_disk_dqdbheader *dh = (काष्ठा qt_disk_dqdbheader *)buf;
	uपूर्णांक nextblk = le32_to_cpu(dh->dqdh_next_मुक्त);
	uपूर्णांक prevblk = le32_to_cpu(dh->dqdh_prev_मुक्त);
	पूर्णांक err;

	अगर (!पंचांगpbuf)
		वापस -ENOMEM;
	अगर (nextblk) अणु
		err = पढ़ो_blk(info, nextblk, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
		((काष्ठा qt_disk_dqdbheader *)पंचांगpbuf)->dqdh_prev_मुक्त =
							dh->dqdh_prev_मुक्त;
		err = ग_लिखो_blk(info, nextblk, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
	पूर्ण
	अगर (prevblk) अणु
		err = पढ़ो_blk(info, prevblk, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
		((काष्ठा qt_disk_dqdbheader *)पंचांगpbuf)->dqdh_next_मुक्त =
							dh->dqdh_next_मुक्त;
		err = ग_लिखो_blk(info, prevblk, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
	पूर्ण अन्यथा अणु
		info->dqi_मुक्त_entry = nextblk;
		mark_info_dirty(info->dqi_sb, info->dqi_type);
	पूर्ण
	kमुक्त(पंचांगpbuf);
	dh->dqdh_next_मुक्त = dh->dqdh_prev_मुक्त = cpu_to_le32(0);
	/* No matter whether ग_लिखो succeeds block is out of list */
	अगर (ग_लिखो_blk(info, blk, buf) < 0)
		quota_error(info->dqi_sb, "Can't write block (%u) "
			    "with free entries", blk);
	वापस 0;
out_buf:
	kमुक्त(पंचांगpbuf);
	वापस err;
पूर्ण

/* Insert given block to the beginning of list with मुक्त entries */
अटल पूर्णांक insert_मुक्त_dqentry(काष्ठा qtree_mem_dqinfo *info, अक्षर *buf,
			       uपूर्णांक blk)
अणु
	अक्षर *पंचांगpbuf = getdqbuf(info->dqi_usable_bs);
	काष्ठा qt_disk_dqdbheader *dh = (काष्ठा qt_disk_dqdbheader *)buf;
	पूर्णांक err;

	अगर (!पंचांगpbuf)
		वापस -ENOMEM;
	dh->dqdh_next_मुक्त = cpu_to_le32(info->dqi_मुक्त_entry);
	dh->dqdh_prev_मुक्त = cpu_to_le32(0);
	err = ग_लिखो_blk(info, blk, buf);
	अगर (err < 0)
		जाओ out_buf;
	अगर (info->dqi_मुक्त_entry) अणु
		err = पढ़ो_blk(info, info->dqi_मुक्त_entry, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
		((काष्ठा qt_disk_dqdbheader *)पंचांगpbuf)->dqdh_prev_मुक्त =
							cpu_to_le32(blk);
		err = ग_लिखो_blk(info, info->dqi_मुक्त_entry, पंचांगpbuf);
		अगर (err < 0)
			जाओ out_buf;
	पूर्ण
	kमुक्त(पंचांगpbuf);
	info->dqi_मुक्त_entry = blk;
	mark_info_dirty(info->dqi_sb, info->dqi_type);
	वापस 0;
out_buf:
	kमुक्त(पंचांगpbuf);
	वापस err;
पूर्ण

/* Is the entry in the block मुक्त? */
पूर्णांक qtree_entry_unused(काष्ठा qtree_mem_dqinfo *info, अक्षर *disk)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < info->dqi_entry_size; i++)
		अगर (disk[i])
			वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(qtree_entry_unused);

/* Find space क्रम dquot */
अटल uपूर्णांक find_मुक्त_dqentry(काष्ठा qtree_mem_dqinfo *info,
			      काष्ठा dquot *dquot, पूर्णांक *err)
अणु
	uपूर्णांक blk, i;
	काष्ठा qt_disk_dqdbheader *dh;
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	अक्षर *ddquot;

	*err = 0;
	अगर (!buf) अणु
		*err = -ENOMEM;
		वापस 0;
	पूर्ण
	dh = (काष्ठा qt_disk_dqdbheader *)buf;
	अगर (info->dqi_मुक्त_entry) अणु
		blk = info->dqi_मुक्त_entry;
		*err = पढ़ो_blk(info, blk, buf);
		अगर (*err < 0)
			जाओ out_buf;
	पूर्ण अन्यथा अणु
		blk = get_मुक्त_dqblk(info);
		अगर ((पूर्णांक)blk < 0) अणु
			*err = blk;
			kमुक्त(buf);
			वापस 0;
		पूर्ण
		स_रखो(buf, 0, info->dqi_usable_bs);
		/* This is enough as the block is alपढ़ोy zeroed and the entry
		 * list is empty... */
		info->dqi_मुक्त_entry = blk;
		mark_info_dirty(dquot->dq_sb, dquot->dq_id.type);
	पूर्ण
	/* Block will be full? */
	अगर (le16_to_cpu(dh->dqdh_entries) + 1 >= qtree_dqstr_in_blk(info)) अणु
		*err = हटाओ_मुक्त_dqentry(info, buf, blk);
		अगर (*err < 0) अणु
			quota_error(dquot->dq_sb, "Can't remove block (%u) "
				    "from entry free list", blk);
			जाओ out_buf;
		पूर्ण
	पूर्ण
	le16_add_cpu(&dh->dqdh_entries, 1);
	/* Find मुक्त काष्ठाure in block */
	ddquot = buf + माप(काष्ठा qt_disk_dqdbheader);
	क्रम (i = 0; i < qtree_dqstr_in_blk(info); i++) अणु
		अगर (qtree_entry_unused(info, ddquot))
			अवरोध;
		ddquot += info->dqi_entry_size;
	पूर्ण
#अगर_घोषित __QUOTA_QT_PARANOIA
	अगर (i == qtree_dqstr_in_blk(info)) अणु
		quota_error(dquot->dq_sb, "Data block full but it shouldn't");
		*err = -EIO;
		जाओ out_buf;
	पूर्ण
#पूर्ण_अगर
	*err = ग_लिखो_blk(info, blk, buf);
	अगर (*err < 0) अणु
		quota_error(dquot->dq_sb, "Can't write quota data block %u",
			    blk);
		जाओ out_buf;
	पूर्ण
	dquot->dq_off = ((loff_t)blk << info->dqi_blocksize_bits) +
			माप(काष्ठा qt_disk_dqdbheader) +
			i * info->dqi_entry_size;
	kमुक्त(buf);
	वापस blk;
out_buf:
	kमुक्त(buf);
	वापस 0;
पूर्ण

/* Insert reference to काष्ठाure पूर्णांकo the trie */
अटल पूर्णांक करो_insert_tree(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot,
			  uपूर्णांक *treeblk, पूर्णांक depth)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	पूर्णांक ret = 0, newson = 0, newact = 0;
	__le32 *ref;
	uपूर्णांक newblk;

	अगर (!buf)
		वापस -ENOMEM;
	अगर (!*treeblk) अणु
		ret = get_मुक्त_dqblk(info);
		अगर (ret < 0)
			जाओ out_buf;
		*treeblk = ret;
		स_रखो(buf, 0, info->dqi_usable_bs);
		newact = 1;
	पूर्ण अन्यथा अणु
		ret = पढ़ो_blk(info, *treeblk, buf);
		अगर (ret < 0) अणु
			quota_error(dquot->dq_sb, "Can't read tree quota "
				    "block %u", *treeblk);
			जाओ out_buf;
		पूर्ण
	पूर्ण
	ref = (__le32 *)buf;
	newblk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	अगर (!newblk)
		newson = 1;
	अगर (depth == info->dqi_qtree_depth - 1) अणु
#अगर_घोषित __QUOTA_QT_PARANOIA
		अगर (newblk) अणु
			quota_error(dquot->dq_sb, "Inserting already present "
				    "quota entry (block %u)",
				    le32_to_cpu(ref[get_index(info,
						dquot->dq_id, depth)]));
			ret = -EIO;
			जाओ out_buf;
		पूर्ण
#पूर्ण_अगर
		newblk = find_मुक्त_dqentry(info, dquot, &ret);
	पूर्ण अन्यथा अणु
		ret = करो_insert_tree(info, dquot, &newblk, depth+1);
	पूर्ण
	अगर (newson && ret >= 0) अणु
		ref[get_index(info, dquot->dq_id, depth)] =
							cpu_to_le32(newblk);
		ret = ग_लिखो_blk(info, *treeblk, buf);
	पूर्ण अन्यथा अगर (newact && ret < 0) अणु
		put_मुक्त_dqblk(info, buf, *treeblk);
	पूर्ण
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Wrapper क्रम inserting quota काष्ठाure पूर्णांकo tree */
अटल अंतरभूत पूर्णांक dq_insert_tree(काष्ठा qtree_mem_dqinfo *info,
				 काष्ठा dquot *dquot)
अणु
	पूर्णांक पंचांगp = QT_TREखातापूर्णF;

#अगर_घोषित __QUOTA_QT_PARANOIA
	अगर (info->dqi_blocks <= QT_TREखातापूर्णF) अणु
		quota_error(dquot->dq_sb, "Quota tree root isn't allocated!");
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर
	वापस करो_insert_tree(info, dquot, &पंचांगp, 0);
पूर्ण

/*
 * We करोn't have to be afraid of deadlocks as we never have quotas on quota
 * files...
 */
पूर्णांक qtree_ग_लिखो_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot)
अणु
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा super_block *sb = dquot->dq_sb;
	sमाप_प्रकार ret;
	अक्षर *ddquot = getdqbuf(info->dqi_entry_size);

	अगर (!ddquot)
		वापस -ENOMEM;

	/* dq_off is guarded by dqio_sem */
	अगर (!dquot->dq_off) अणु
		ret = dq_insert_tree(info, dquot);
		अगर (ret < 0) अणु
			quota_error(sb, "Error %zd occurred while creating "
				    "quota", ret);
			kमुक्त(ddquot);
			वापस ret;
		पूर्ण
	पूर्ण
	spin_lock(&dquot->dq_dqb_lock);
	info->dqi_ops->mem2disk_dqblk(ddquot, dquot);
	spin_unlock(&dquot->dq_dqb_lock);
	ret = sb->s_op->quota_ग_लिखो(sb, type, ddquot, info->dqi_entry_size,
				    dquot->dq_off);
	अगर (ret != info->dqi_entry_size) अणु
		quota_error(sb, "dquota write failed");
		अगर (ret >= 0)
			ret = -ENOSPC;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
	dqstats_inc(DQST_WRITES);
	kमुक्त(ddquot);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qtree_ग_लिखो_dquot);

/* Free dquot entry in data block */
अटल पूर्णांक मुक्त_dqentry(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot,
			uपूर्णांक blk)
अणु
	काष्ठा qt_disk_dqdbheader *dh;
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	पूर्णांक ret = 0;

	अगर (!buf)
		वापस -ENOMEM;
	अगर (dquot->dq_off >> info->dqi_blocksize_bits != blk) अणु
		quota_error(dquot->dq_sb, "Quota structure has offset to "
			"other block (%u) than it should (%u)", blk,
			(uपूर्णांक)(dquot->dq_off >> info->dqi_blocksize_bits));
		जाओ out_buf;
	पूर्ण
	ret = पढ़ो_blk(info, blk, buf);
	अगर (ret < 0) अणु
		quota_error(dquot->dq_sb, "Can't read quota data block %u",
			    blk);
		जाओ out_buf;
	पूर्ण
	dh = (काष्ठा qt_disk_dqdbheader *)buf;
	le16_add_cpu(&dh->dqdh_entries, -1);
	अगर (!le16_to_cpu(dh->dqdh_entries)) अणु	/* Block got मुक्त? */
		ret = हटाओ_मुक्त_dqentry(info, buf, blk);
		अगर (ret >= 0)
			ret = put_मुक्त_dqblk(info, buf, blk);
		अगर (ret < 0) अणु
			quota_error(dquot->dq_sb, "Can't move quota data block "
				    "(%u) to free list", blk);
			जाओ out_buf;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(buf +
		       (dquot->dq_off & ((1 << info->dqi_blocksize_bits) - 1)),
		       0, info->dqi_entry_size);
		अगर (le16_to_cpu(dh->dqdh_entries) ==
		    qtree_dqstr_in_blk(info) - 1) अणु
			/* Insert will ग_लिखो block itself */
			ret = insert_मुक्त_dqentry(info, buf, blk);
			अगर (ret < 0) अणु
				quota_error(dquot->dq_sb, "Can't insert quota "
				    "data block (%u) to free entry list", blk);
				जाओ out_buf;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = ग_लिखो_blk(info, blk, buf);
			अगर (ret < 0) अणु
				quota_error(dquot->dq_sb, "Can't write quota "
					    "data block %u", blk);
				जाओ out_buf;
			पूर्ण
		पूर्ण
	पूर्ण
	dquot->dq_off = 0;	/* Quota is now unattached */
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Remove reference to dquot from tree */
अटल पूर्णांक हटाओ_tree(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot,
		       uपूर्णांक *blk, पूर्णांक depth)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	पूर्णांक ret = 0;
	uपूर्णांक newblk;
	__le32 *ref = (__le32 *)buf;

	अगर (!buf)
		वापस -ENOMEM;
	ret = पढ़ो_blk(info, *blk, buf);
	अगर (ret < 0) अणु
		quota_error(dquot->dq_sb, "Can't read quota data block %u",
			    *blk);
		जाओ out_buf;
	पूर्ण
	newblk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	अगर (depth == info->dqi_qtree_depth - 1) अणु
		ret = मुक्त_dqentry(info, dquot, newblk);
		newblk = 0;
	पूर्ण अन्यथा अणु
		ret = हटाओ_tree(info, dquot, &newblk, depth+1);
	पूर्ण
	अगर (ret >= 0 && !newblk) अणु
		पूर्णांक i;
		ref[get_index(info, dquot->dq_id, depth)] = cpu_to_le32(0);
		/* Block got empty? */
		क्रम (i = 0; i < (info->dqi_usable_bs >> 2) && !ref[i]; i++)
			;
		/* Don't put the root block पूर्णांकo the मुक्त block list */
		अगर (i == (info->dqi_usable_bs >> 2)
		    && *blk != QT_TREखातापूर्णF) अणु
			put_मुक्त_dqblk(info, buf, *blk);
			*blk = 0;
		पूर्ण अन्यथा अणु
			ret = ग_लिखो_blk(info, *blk, buf);
			अगर (ret < 0)
				quota_error(dquot->dq_sb,
					    "Can't write quota tree block %u",
					    *blk);
		पूर्ण
	पूर्ण
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Delete dquot from tree */
पूर्णांक qtree_delete_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot)
अणु
	uपूर्णांक पंचांगp = QT_TREखातापूर्णF;

	अगर (!dquot->dq_off)	/* Even not allocated? */
		वापस 0;
	वापस हटाओ_tree(info, dquot, &पंचांगp, 0);
पूर्ण
EXPORT_SYMBOL(qtree_delete_dquot);

/* Find entry in block */
अटल loff_t find_block_dqentry(काष्ठा qtree_mem_dqinfo *info,
				 काष्ठा dquot *dquot, uपूर्णांक blk)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	loff_t ret = 0;
	पूर्णांक i;
	अक्षर *ddquot;

	अगर (!buf)
		वापस -ENOMEM;
	ret = पढ़ो_blk(info, blk, buf);
	अगर (ret < 0) अणु
		quota_error(dquot->dq_sb, "Can't read quota tree "
			    "block %u", blk);
		जाओ out_buf;
	पूर्ण
	ddquot = buf + माप(काष्ठा qt_disk_dqdbheader);
	क्रम (i = 0; i < qtree_dqstr_in_blk(info); i++) अणु
		अगर (info->dqi_ops->is_id(ddquot, dquot))
			अवरोध;
		ddquot += info->dqi_entry_size;
	पूर्ण
	अगर (i == qtree_dqstr_in_blk(info)) अणु
		quota_error(dquot->dq_sb,
			    "Quota for id %u referenced but not present",
			    from_kqid(&init_user_ns, dquot->dq_id));
		ret = -EIO;
		जाओ out_buf;
	पूर्ण अन्यथा अणु
		ret = ((loff_t)blk << info->dqi_blocksize_bits) + माप(काष्ठा
		  qt_disk_dqdbheader) + i * info->dqi_entry_size;
	पूर्ण
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Find entry क्रम given id in the tree */
अटल loff_t find_tree_dqentry(काष्ठा qtree_mem_dqinfo *info,
				काष्ठा dquot *dquot, uपूर्णांक blk, पूर्णांक depth)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	loff_t ret = 0;
	__le32 *ref = (__le32 *)buf;

	अगर (!buf)
		वापस -ENOMEM;
	ret = पढ़ो_blk(info, blk, buf);
	अगर (ret < 0) अणु
		quota_error(dquot->dq_sb, "Can't read quota tree block %u",
			    blk);
		जाओ out_buf;
	पूर्ण
	ret = 0;
	blk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	अगर (!blk)	/* No reference? */
		जाओ out_buf;
	अगर (depth < info->dqi_qtree_depth - 1)
		ret = find_tree_dqentry(info, dquot, blk, depth+1);
	अन्यथा
		ret = find_block_dqentry(info, dquot, blk);
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Find entry क्रम given id in the tree - wrapper function */
अटल अंतरभूत loff_t find_dqentry(काष्ठा qtree_mem_dqinfo *info,
				  काष्ठा dquot *dquot)
अणु
	वापस find_tree_dqentry(info, dquot, QT_TREखातापूर्णF, 0);
पूर्ण

पूर्णांक qtree_पढ़ो_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot)
अणु
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा super_block *sb = dquot->dq_sb;
	loff_t offset;
	अक्षर *ddquot;
	पूर्णांक ret = 0;

#अगर_घोषित __QUOTA_QT_PARANOIA
	/* Invalidated quota? */
	अगर (!sb_dqopt(dquot->dq_sb)->files[type]) अणु
		quota_error(sb, "Quota invalidated while reading!");
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर
	/* Do we know offset of the dquot entry in the quota file? */
	अगर (!dquot->dq_off) अणु
		offset = find_dqentry(info, dquot);
		अगर (offset <= 0) अणु	/* Entry not present? */
			अगर (offset < 0)
				quota_error(sb,"Can't read quota structure "
					    "for id %u",
					    from_kqid(&init_user_ns,
						      dquot->dq_id));
			dquot->dq_off = 0;
			set_bit(DQ_FAKE_B, &dquot->dq_flags);
			स_रखो(&dquot->dq_dqb, 0, माप(काष्ठा mem_dqblk));
			ret = offset;
			जाओ out;
		पूर्ण
		dquot->dq_off = offset;
	पूर्ण
	ddquot = getdqbuf(info->dqi_entry_size);
	अगर (!ddquot)
		वापस -ENOMEM;
	ret = sb->s_op->quota_पढ़ो(sb, type, ddquot, info->dqi_entry_size,
				   dquot->dq_off);
	अगर (ret != info->dqi_entry_size) अणु
		अगर (ret >= 0)
			ret = -EIO;
		quota_error(sb, "Error while reading quota structure for id %u",
			    from_kqid(&init_user_ns, dquot->dq_id));
		set_bit(DQ_FAKE_B, &dquot->dq_flags);
		स_रखो(&dquot->dq_dqb, 0, माप(काष्ठा mem_dqblk));
		kमुक्त(ddquot);
		जाओ out;
	पूर्ण
	spin_lock(&dquot->dq_dqb_lock);
	info->dqi_ops->disk2mem_dqblk(dquot, ddquot);
	अगर (!dquot->dq_dqb.dqb_bhardlimit &&
	    !dquot->dq_dqb.dqb_bsoftlimit &&
	    !dquot->dq_dqb.dqb_ihardlimit &&
	    !dquot->dq_dqb.dqb_isoftlimit)
		set_bit(DQ_FAKE_B, &dquot->dq_flags);
	spin_unlock(&dquot->dq_dqb_lock);
	kमुक्त(ddquot);
out:
	dqstats_inc(DQST_READS);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qtree_पढ़ो_dquot);

/* Check whether dquot should not be deleted. We know we are
 * the only one operating on dquot (thanks to dq_lock) */
पूर्णांक qtree_release_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot)
अणु
	अगर (test_bit(DQ_FAKE_B, &dquot->dq_flags) &&
	    !(dquot->dq_dqb.dqb_curinodes | dquot->dq_dqb.dqb_curspace))
		वापस qtree_delete_dquot(info, dquot);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qtree_release_dquot);

अटल पूर्णांक find_next_id(काष्ठा qtree_mem_dqinfo *info, qid_t *id,
			अचिन्हित पूर्णांक blk, पूर्णांक depth)
अणु
	अक्षर *buf = getdqbuf(info->dqi_usable_bs);
	__le32 *ref = (__le32 *)buf;
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक epb = info->dqi_usable_bs >> 2;
	अचिन्हित पूर्णांक level_inc = 1;
	पूर्णांक i;

	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = depth; i < info->dqi_qtree_depth - 1; i++)
		level_inc *= epb;

	ret = पढ़ो_blk(info, blk, buf);
	अगर (ret < 0) अणु
		quota_error(info->dqi_sb,
			    "Can't read quota tree block %u", blk);
		जाओ out_buf;
	पूर्ण
	क्रम (i = __get_index(info, *id, depth); i < epb; i++) अणु
		अगर (ref[i] == cpu_to_le32(0)) अणु
			*id += level_inc;
			जारी;
		पूर्ण
		अगर (depth == info->dqi_qtree_depth - 1) अणु
			ret = 0;
			जाओ out_buf;
		पूर्ण
		ret = find_next_id(info, id, le32_to_cpu(ref[i]), depth + 1);
		अगर (ret != -ENOENT)
			अवरोध;
	पूर्ण
	अगर (i == epb) अणु
		ret = -ENOENT;
		जाओ out_buf;
	पूर्ण
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक qtree_get_next_id(काष्ठा qtree_mem_dqinfo *info, काष्ठा kqid *qid)
अणु
	qid_t id = from_kqid(&init_user_ns, *qid);
	पूर्णांक ret;

	ret = find_next_id(info, &id, QT_TREखातापूर्णF, 0);
	अगर (ret < 0)
		वापस ret;
	*qid = make_kqid(&init_user_ns, qid->type, id);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qtree_get_next_id);
