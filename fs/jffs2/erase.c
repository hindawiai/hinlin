<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/compiler.h>
#समावेश <linux/crc32.h>
#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश "nodelist.h"

अटल व्योम jffs2_erase_failed(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t bad_offset);
अटल व्योम jffs2_erase_succeeded(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
अटल व्योम jffs2_mark_erased_block(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);

अटल व्योम jffs2_erase_block(काष्ठा jffs2_sb_info *c,
			      काष्ठा jffs2_eraseblock *jeb)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t bad_offset;
#अगर_घोषित __ECOS
       ret = jffs2_flash_erase(c, jeb);
       अगर (!ret) अणु
	       jffs2_erase_succeeded(c, jeb);
	       वापस;
       पूर्ण
       bad_offset = jeb->offset;
#अन्यथा /* Linux */
	काष्ठा erase_info *instr;

	jffs2_dbg(1, "%s(): erase block %#08x (range %#08x-%#08x)\n",
		  __func__,
		  jeb->offset, jeb->offset, jeb->offset + c->sector_size);
	instr = kदो_स्मृति(माप(काष्ठा erase_info), GFP_KERNEL);
	अगर (!instr) अणु
		pr_warn("kmalloc for struct erase_info in jffs2_erase_block failed. Refiling block for later\n");
		mutex_lock(&c->erase_मुक्त_sem);
		spin_lock(&c->erase_completion_lock);
		list_move(&jeb->list, &c->erase_pending_list);
		c->erasing_size -= c->sector_size;
		c->dirty_size += c->sector_size;
		jeb->dirty_size = c->sector_size;
		spin_unlock(&c->erase_completion_lock);
		mutex_unlock(&c->erase_मुक्त_sem);
		वापस;
	पूर्ण

	स_रखो(instr, 0, माप(*instr));

	instr->addr = jeb->offset;
	instr->len = c->sector_size;

	ret = mtd_erase(c->mtd, instr);
	अगर (!ret) अणु
		jffs2_erase_succeeded(c, jeb);
		kमुक्त(instr);
		वापस;
	पूर्ण

	bad_offset = instr->fail_addr;
	kमुक्त(instr);
#पूर्ण_अगर /* __ECOS */

	अगर (ret == -ENOMEM || ret == -EAGAIN) अणु
		/* Erase failed immediately. Refile it on the list */
		jffs2_dbg(1, "Erase at 0x%08x failed: %d. Refiling on erase_pending_list\n",
			  jeb->offset, ret);
		mutex_lock(&c->erase_मुक्त_sem);
		spin_lock(&c->erase_completion_lock);
		list_move(&jeb->list, &c->erase_pending_list);
		c->erasing_size -= c->sector_size;
		c->dirty_size += c->sector_size;
		jeb->dirty_size = c->sector_size;
		spin_unlock(&c->erase_completion_lock);
		mutex_unlock(&c->erase_मुक्त_sem);
		वापस;
	पूर्ण

	अगर (ret == -EROFS)
		pr_warn("Erase at 0x%08x failed immediately: -EROFS. Is the sector locked?\n",
			jeb->offset);
	अन्यथा
		pr_warn("Erase at 0x%08x failed immediately: errno %d\n",
			jeb->offset, ret);

	jffs2_erase_failed(c, jeb, bad_offset);
पूर्ण

पूर्णांक jffs2_erase_pending_blocks(काष्ठा jffs2_sb_info *c, पूर्णांक count)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	पूर्णांक work_करोne = 0;

	mutex_lock(&c->erase_मुक्त_sem);

	spin_lock(&c->erase_completion_lock);

	जबतक (!list_empty(&c->erase_complete_list) ||
	       !list_empty(&c->erase_pending_list)) अणु

		अगर (!list_empty(&c->erase_complete_list)) अणु
			jeb = list_entry(c->erase_complete_list.next, काष्ठा jffs2_eraseblock, list);
			list_move(&jeb->list, &c->erase_checking_list);
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->erase_मुक्त_sem);
			jffs2_mark_erased_block(c, jeb);

			work_करोne++;
			अगर (!--count) अणु
				jffs2_dbg(1, "Count reached. jffs2_erase_pending_blocks leaving\n");
				जाओ करोne;
			पूर्ण

		पूर्ण अन्यथा अगर (!list_empty(&c->erase_pending_list)) अणु
			jeb = list_entry(c->erase_pending_list.next, काष्ठा jffs2_eraseblock, list);
			jffs2_dbg(1, "Starting erase of pending block 0x%08x\n",
				  jeb->offset);
			list_del(&jeb->list);
			c->erasing_size += c->sector_size;
			c->wasted_size -= jeb->wasted_size;
			c->मुक्त_size -= jeb->मुक्त_size;
			c->used_size -= jeb->used_size;
			c->dirty_size -= jeb->dirty_size;
			jeb->wasted_size = jeb->used_size = jeb->dirty_size = jeb->मुक्त_size = 0;
			jffs2_मुक्त_jeb_node_refs(c, jeb);
			list_add(&jeb->list, &c->erasing_list);
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->erase_मुक्त_sem);

			jffs2_erase_block(c, jeb);

		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण

		/* Be nice */
		cond_resched();
		mutex_lock(&c->erase_मुक्त_sem);
		spin_lock(&c->erase_completion_lock);
	पूर्ण

	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_मुक्त_sem);
 करोne:
	jffs2_dbg(1, "jffs2_erase_pending_blocks completed\n");
	वापस work_करोne;
पूर्ण

अटल व्योम jffs2_erase_succeeded(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	jffs2_dbg(1, "Erase completed successfully at 0x%08x\n", jeb->offset);
	mutex_lock(&c->erase_मुक्त_sem);
	spin_lock(&c->erase_completion_lock);
	list_move_tail(&jeb->list, &c->erase_complete_list);
	/* Wake the GC thपढ़ो to mark them clean */
	jffs2_garbage_collect_trigger(c);
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_मुक्त_sem);
	wake_up(&c->erase_रुको);
पूर्ण

अटल व्योम jffs2_erase_failed(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t bad_offset)
अणु
	/* For न_अंकD, अगर the failure did not occur at the device level क्रम a
	   specअगरic physical page, करोn't bother updating the bad block table. */
	अगर (jffs2_cleanmarker_oob(c) && (bad_offset != (uपूर्णांक32_t)MTD_FAIL_ADDR_UNKNOWN)) अणु
		/* We had a device-level failure to erase.  Let's see if we've
		   failed too many बार. */
		अगर (!jffs2_ग_लिखो_nand_badblock(c, jeb, bad_offset)) अणु
			/* We'd like to give this block another try. */
			mutex_lock(&c->erase_मुक्त_sem);
			spin_lock(&c->erase_completion_lock);
			list_move(&jeb->list, &c->erase_pending_list);
			c->erasing_size -= c->sector_size;
			c->dirty_size += c->sector_size;
			jeb->dirty_size = c->sector_size;
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->erase_मुक्त_sem);
			वापस;
		पूर्ण
	पूर्ण

	mutex_lock(&c->erase_मुक्त_sem);
	spin_lock(&c->erase_completion_lock);
	c->erasing_size -= c->sector_size;
	c->bad_size += c->sector_size;
	list_move(&jeb->list, &c->bad_list);
	c->nr_erasing_blocks--;
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_मुक्त_sem);
	wake_up(&c->erase_रुको);
पूर्ण

/* Hmmm. Maybe we should accept the extra space it takes and make
   this a standard करोubly-linked list? */
अटल अंतरभूत व्योम jffs2_हटाओ_node_refs_from_ino_list(काष्ठा jffs2_sb_info *c,
			काष्ठा jffs2_raw_node_ref *ref, काष्ठा jffs2_eraseblock *jeb)
अणु
	काष्ठा jffs2_inode_cache *ic = शून्य;
	काष्ठा jffs2_raw_node_ref **prev;

	prev = &ref->next_in_ino;

	/* Walk the inode's list once, removing any nodes from this eraseblock */
	जबतक (1) अणु
		अगर (!(*prev)->next_in_ino) अणु
			/* We're looking at the jffs2_inode_cache, which is
			   at the end of the linked list. Stash it and जारी
			   from the beginning of the list */
			ic = (काष्ठा jffs2_inode_cache *)(*prev);
			prev = &ic->nodes;
			जारी;
		पूर्ण

		अगर (SECTOR_ADDR((*prev)->flash_offset) == jeb->offset) अणु
			/* It's in the block we're erasing */
			काष्ठा jffs2_raw_node_ref *this;

			this = *prev;
			*prev = this->next_in_ino;
			this->next_in_ino = शून्य;

			अगर (this == ref)
				अवरोध;

			जारी;
		पूर्ण
		/* Not to be deleted. Skip */
		prev = &((*prev)->next_in_ino);
	पूर्ण

	/* PARANOIA */
	अगर (!ic) अणु
		JFFS2_WARNING("inode_cache/xattr_datum/xattr_ref"
			      " not found in remove_node_refs()!!\n");
		वापस;
	पूर्ण

	jffs2_dbg(1, "Removed nodes in range 0x%08x-0x%08x from ino #%u\n",
		  jeb->offset, jeb->offset + c->sector_size, ic->ino);

	D2(अणु
		पूर्णांक i=0;
		काष्ठा jffs2_raw_node_ref *this;
		prपूर्णांकk(KERN_DEBUG "After remove_node_refs_from_ino_list: \n");

		this = ic->nodes;

		prपूर्णांकk(KERN_DEBUG);
		जबतक(this) अणु
			pr_cont("0x%08x(%d)->",
			       ref_offset(this), ref_flags(this));
			अगर (++i == 5) अणु
				prपूर्णांकk(KERN_DEBUG);
				i=0;
			पूर्ण
			this = this->next_in_ino;
		पूर्ण
		pr_cont("\n");
	पूर्ण);

	चयन (ic->class) अणु
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
		हाल RAWNODE_CLASS_XATTR_DATUM:
			jffs2_release_xattr_datum(c, (काष्ठा jffs2_xattr_datum *)ic);
			अवरोध;
		हाल RAWNODE_CLASS_XATTR_REF:
			jffs2_release_xattr_ref(c, (काष्ठा jffs2_xattr_ref *)ic);
			अवरोध;
#पूर्ण_अगर
		शेष:
			अगर (ic->nodes == (व्योम *)ic && ic->pino_nlink == 0)
				jffs2_del_ino_cache(c, ic);
	पूर्ण
पूर्ण

व्योम jffs2_मुक्त_jeb_node_refs(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	काष्ठा jffs2_raw_node_ref *block, *ref;
	jffs2_dbg(1, "Freeing all node refs for eraseblock offset 0x%08x\n",
		  jeb->offset);

	block = ref = jeb->first_node;

	जबतक (ref) अणु
		अगर (ref->flash_offset == REF_LINK_NODE) अणु
			ref = ref->next_in_ino;
			jffs2_मुक्त_refblock(block);
			block = ref;
			जारी;
		पूर्ण
		अगर (ref->flash_offset != REF_EMPTY_NODE && ref->next_in_ino)
			jffs2_हटाओ_node_refs_from_ino_list(c, ref, jeb);
		/* अन्यथा it was a non-inode node or alपढ़ोy हटाओd, so करोn't bother */

		ref++;
	पूर्ण
	jeb->first_node = jeb->last_node = शून्य;
पूर्ण

अटल पूर्णांक jffs2_block_check_erase(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t *bad_offset)
अणु
	व्योम *ebuf;
	uपूर्णांक32_t ofs;
	माप_प्रकार retlen;
	पूर्णांक ret;
	अचिन्हित दीर्घ *wordebuf;

	ret = mtd_poपूर्णांक(c->mtd, jeb->offset, c->sector_size, &retlen,
			&ebuf, शून्य);
	अगर (ret != -EOPNOTSUPP) अणु
		अगर (ret) अणु
			jffs2_dbg(1, "MTD point failed %d\n", ret);
			जाओ करो_flash_पढ़ो;
		पूर्ण
		अगर (retlen < c->sector_size) अणु
			/* Don't muck about if it won't let us poपूर्णांक to the whole erase sector */
			jffs2_dbg(1, "MTD point returned len too short: 0x%zx\n",
				  retlen);
			mtd_unpoपूर्णांक(c->mtd, jeb->offset, retlen);
			जाओ करो_flash_पढ़ो;
		पूर्ण
		wordebuf = ebuf-माप(*wordebuf);
		retlen /= माप(*wordebuf);
		करो अणु
		   अगर (*++wordebuf != ~0)
			   अवरोध;
		पूर्ण जबतक(--retlen);
		mtd_unpoपूर्णांक(c->mtd, jeb->offset, c->sector_size);
		अगर (retlen) अणु
			pr_warn("Newly-erased block contained word 0x%lx at offset 0x%08tx\n",
				*wordebuf,
				jeb->offset +
				c->sector_size-retlen * माप(*wordebuf));
			वापस -EIO;
		पूर्ण
		वापस 0;
	पूर्ण
 करो_flash_पढ़ो:
	ebuf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!ebuf) अणु
		pr_warn("Failed to allocate page buffer for verifying erase at 0x%08x. Refiling\n",
			jeb->offset);
		वापस -EAGAIN;
	पूर्ण

	jffs2_dbg(1, "Verifying erase at 0x%08x\n", jeb->offset);

	क्रम (ofs = jeb->offset; ofs < jeb->offset + c->sector_size; ) अणु
		uपूर्णांक32_t पढ़ोlen = min((uपूर्णांक32_t)PAGE_SIZE, jeb->offset + c->sector_size - ofs);
		पूर्णांक i;

		*bad_offset = ofs;

		ret = mtd_पढ़ो(c->mtd, ofs, पढ़ोlen, &retlen, ebuf);
		अगर (ret) अणु
			pr_warn("Read of newly-erased block at 0x%08x failed: %d. Putting on bad_list\n",
				ofs, ret);
			ret = -EIO;
			जाओ fail;
		पूर्ण
		अगर (retlen != पढ़ोlen) अणु
			pr_warn("Short read from newly-erased block at 0x%08x. Wanted %d, got %zd\n",
				ofs, पढ़ोlen, retlen);
			ret = -EIO;
			जाओ fail;
		पूर्ण
		क्रम (i=0; i<पढ़ोlen; i += माप(अचिन्हित दीर्घ)) अणु
			/* It's OK. We know it's properly aligned */
			अचिन्हित दीर्घ *datum = ebuf + i;
			अगर (*datum + 1) अणु
				*bad_offset += i;
				pr_warn("Newly-erased block contained word 0x%lx at offset 0x%08x\n",
					*datum, *bad_offset);
				ret = -EIO;
				जाओ fail;
			पूर्ण
		पूर्ण
		ofs += पढ़ोlen;
		cond_resched();
	पूर्ण
	ret = 0;
fail:
	kमुक्त(ebuf);
	वापस ret;
पूर्ण

अटल व्योम jffs2_mark_erased_block(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb)
अणु
	माप_प्रकार retlen;
	पूर्णांक ret;
	uपूर्णांक32_t bad_offset;

	चयन (jffs2_block_check_erase(c, jeb, &bad_offset)) अणु
	हाल -EAGAIN:	जाओ refile;
	हाल -EIO:	जाओ filebad;
	पूर्ण

	/* Write the erase complete marker */
	jffs2_dbg(1, "Writing erased marker to block at 0x%08x\n", jeb->offset);
	bad_offset = jeb->offset;

	/* Cleanmarker in oob area or no cleanmarker at all ? */
	अगर (jffs2_cleanmarker_oob(c) || c->cleanmarker_size == 0) अणु

		अगर (jffs2_cleanmarker_oob(c)) अणु
			अगर (jffs2_ग_लिखो_nand_cleanmarker(c, jeb))
				जाओ filebad;
		पूर्ण
	पूर्ण अन्यथा अणु

		काष्ठा kvec vecs[1];
		काष्ठा jffs2_unknown_node marker = अणु
			.magic =	cpu_to_je16(JFFS2_MAGIC_BITMASK),
			.nodetype =	cpu_to_je16(JFFS2_NODETYPE_CLEANMARKER),
			.totlen =	cpu_to_je32(c->cleanmarker_size)
		पूर्ण;

		jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1);

		marker.hdr_crc = cpu_to_je32(crc32(0, &marker, माप(काष्ठा jffs2_unknown_node)-4));

		vecs[0].iov_base = (अचिन्हित अक्षर *) &marker;
		vecs[0].iov_len = माप(marker);
		ret = jffs2_flash_direct_ग_लिखोv(c, vecs, 1, jeb->offset, &retlen);

		अगर (ret || retlen != माप(marker)) अणु
			अगर (ret)
				pr_warn("Write clean marker to block at 0x%08x failed: %d\n",
				       jeb->offset, ret);
			अन्यथा
				pr_warn("Short write to newly-erased block at 0x%08x: Wanted %zd, got %zd\n",
				       jeb->offset, माप(marker), retlen);

			जाओ filebad;
		पूर्ण
	पूर्ण
	/* Everything अन्यथा got zeroed beक्रमe the erase */
	jeb->मुक्त_size = c->sector_size;

	mutex_lock(&c->erase_मुक्त_sem);
	spin_lock(&c->erase_completion_lock);

	c->erasing_size -= c->sector_size;
	c->मुक्त_size += c->sector_size;

	/* Account क्रम cleanmarker now, अगर it's in-band */
	अगर (c->cleanmarker_size && !jffs2_cleanmarker_oob(c))
		jffs2_link_node_ref(c, jeb, jeb->offset | REF_NORMAL, c->cleanmarker_size, शून्य);

	list_move_tail(&jeb->list, &c->मुक्त_list);
	c->nr_erasing_blocks--;
	c->nr_मुक्त_blocks++;

	jffs2_dbg_acct_sanity_check_nolock(c, jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_मुक्त_sem);
	wake_up(&c->erase_रुको);
	वापस;

filebad:
	jffs2_erase_failed(c, jeb, bad_offset);
	वापस;

refile:
	/* Stick it back on the list from whence it came and come back later */
	mutex_lock(&c->erase_मुक्त_sem);
	spin_lock(&c->erase_completion_lock);
	jffs2_garbage_collect_trigger(c);
	list_move(&jeb->list, &c->erase_complete_list);
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_मुक्त_sem);
	वापस;
पूर्ण
