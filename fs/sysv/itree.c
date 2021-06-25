<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/itree.c
 *
 *  Handling of indirect blocks' trees.
 *  AV, Sep--Dec 2000
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/mount.h>
#समावेश <linux/माला.स>
#समावेश "sysv.h"

क्रमागत अणुसूचीECT = 10, DEPTH = 4पूर्ण;	/* Have triple indirect */

अटल अंतरभूत व्योम dirty_indirect(काष्ठा buffer_head *bh, काष्ठा inode *inode)
अणु
	mark_buffer_dirty_inode(bh, inode);
	अगर (IS_SYNC(inode))
		sync_dirty_buffer(bh);
पूर्ण

अटल पूर्णांक block_to_path(काष्ठा inode *inode, दीर्घ block, पूर्णांक offsets[DEPTH])
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	पूर्णांक ptrs_bits = sbi->s_ind_per_block_bits;
	अचिन्हित दीर्घ	indirect_blocks = sbi->s_ind_per_block,
			द्विगुन_blocks = sbi->s_ind_per_block_2;
	पूर्णांक n = 0;

	अगर (block < 0) अणु
		prपूर्णांकk("sysv_block_map: block < 0\n");
	पूर्ण अन्यथा अगर (block < सूचीECT) अणु
		offsets[n++] = block;
	पूर्ण अन्यथा अगर ( (block -= सूचीECT) < indirect_blocks) अणु
		offsets[n++] = सूचीECT;
		offsets[n++] = block;
	पूर्ण अन्यथा अगर ((block -= indirect_blocks) < द्विगुन_blocks) अणु
		offsets[n++] = सूचीECT+1;
		offsets[n++] = block >> ptrs_bits;
		offsets[n++] = block & (indirect_blocks - 1);
	पूर्ण अन्यथा अगर (((block -= द्विगुन_blocks) >> (ptrs_bits * 2)) < indirect_blocks) अणु
		offsets[n++] = सूचीECT+2;
		offsets[n++] = block >> (ptrs_bits * 2);
		offsets[n++] = (block >> ptrs_bits) & (indirect_blocks - 1);
		offsets[n++] = block & (indirect_blocks - 1);
	पूर्ण अन्यथा अणु
		/* nothing */;
	पूर्ण
	वापस n;
पूर्ण

अटल अंतरभूत पूर्णांक block_to_cpu(काष्ठा sysv_sb_info *sbi, sysv_zone_t nr)
अणु
	वापस sbi->s_block_base + fs32_to_cpu(sbi, nr);
पूर्ण

प्रकार काष्ठा अणु
	sysv_zone_t     *p;
	sysv_zone_t     key;
	काष्ठा buffer_head *bh;
पूर्ण Indirect;

अटल DEFINE_RWLOCK(poपूर्णांकers_lock);

अटल अंतरभूत व्योम add_chain(Indirect *p, काष्ठा buffer_head *bh, sysv_zone_t *v)
अणु
	p->key = *(p->p = v);
	p->bh = bh;
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_chain(Indirect *from, Indirect *to)
अणु
	जबतक (from <= to && from->key == *from->p)
		from++;
	वापस (from > to);
पूर्ण

अटल अंतरभूत sysv_zone_t *block_end(काष्ठा buffer_head *bh)
अणु
	वापस (sysv_zone_t*)((अक्षर*)bh->b_data + bh->b_size);
पूर्ण

/*
 * Requires पढ़ो_lock(&poपूर्णांकers_lock) or ग_लिखो_lock(&poपूर्णांकers_lock)
 */
अटल Indirect *get_branch(काष्ठा inode *inode,
			    पूर्णांक depth,
			    पूर्णांक offsets[],
			    Indirect chain[],
			    पूर्णांक *err)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	Indirect *p = chain;
	काष्ठा buffer_head *bh;

	*err = 0;
	add_chain(chain, शून्य, SYSV_I(inode)->i_data + *offsets);
	अगर (!p->key)
		जाओ no_block;
	जबतक (--depth) अणु
		पूर्णांक block = block_to_cpu(SYSV_SB(sb), p->key);
		bh = sb_bपढ़ो(sb, block);
		अगर (!bh)
			जाओ failure;
		अगर (!verअगरy_chain(chain, p))
			जाओ changed;
		add_chain(++p, bh, (sysv_zone_t*)bh->b_data + *++offsets);
		अगर (!p->key)
			जाओ no_block;
	पूर्ण
	वापस शून्य;

changed:
	brअन्यथा(bh);
	*err = -EAGAIN;
	जाओ no_block;
failure:
	*err = -EIO;
no_block:
	वापस p;
पूर्ण

अटल पूर्णांक alloc_branch(काष्ठा inode *inode,
			पूर्णांक num,
			पूर्णांक *offsets,
			Indirect *branch)
अणु
	पूर्णांक blocksize = inode->i_sb->s_blocksize;
	पूर्णांक n = 0;
	पूर्णांक i;

	branch[0].key = sysv_new_block(inode->i_sb);
	अगर (branch[0].key) क्रम (n = 1; n < num; n++) अणु
		काष्ठा buffer_head *bh;
		पूर्णांक parent;
		/* Allocate the next block */
		branch[n].key = sysv_new_block(inode->i_sb);
		अगर (!branch[n].key)
			अवरोध;
		/*
		 * Get buffer_head क्रम parent block, zero it out and set 
		 * the poपूर्णांकer to new one, then send parent to disk.
		 */
		parent = block_to_cpu(SYSV_SB(inode->i_sb), branch[n-1].key);
		bh = sb_getblk(inode->i_sb, parent);
		lock_buffer(bh);
		स_रखो(bh->b_data, 0, blocksize);
		branch[n].bh = bh;
		branch[n].p = (sysv_zone_t*) bh->b_data + offsets[n];
		*branch[n].p = branch[n].key;
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		dirty_indirect(bh, inode);
	पूर्ण
	अगर (n == num)
		वापस 0;

	/* Allocation failed, मुक्त what we alपढ़ोy allocated */
	क्रम (i = 1; i < n; i++)
		bक्रमget(branch[i].bh);
	क्रम (i = 0; i < n; i++)
		sysv_मुक्त_block(inode->i_sb, branch[i].key);
	वापस -ENOSPC;
पूर्ण

अटल अंतरभूत पूर्णांक splice_branch(काष्ठा inode *inode,
				Indirect chain[],
				Indirect *where,
				पूर्णांक num)
अणु
	पूर्णांक i;

	/* Verअगरy that place we are splicing to is still there and vacant */
	ग_लिखो_lock(&poपूर्णांकers_lock);
	अगर (!verअगरy_chain(chain, where-1) || *where->p)
		जाओ changed;
	*where->p = where->key;
	ग_लिखो_unlock(&poपूर्णांकers_lock);

	inode->i_स_समय = current_समय(inode);

	/* had we spliced it onto indirect block? */
	अगर (where->bh)
		dirty_indirect(where->bh, inode);

	अगर (IS_SYNC(inode))
		sysv_sync_inode(inode);
	अन्यथा
		mark_inode_dirty(inode);
	वापस 0;

changed:
	ग_लिखो_unlock(&poपूर्णांकers_lock);
	क्रम (i = 1; i < num; i++)
		bक्रमget(where[i].bh);
	क्रम (i = 0; i < num; i++)
		sysv_मुक्त_block(inode->i_sb, where[i].key);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक get_block(काष्ठा inode *inode, sector_t iblock, काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक err = -EIO;
	पूर्णांक offsets[DEPTH];
	Indirect chain[DEPTH];
	काष्ठा super_block *sb = inode->i_sb;
	Indirect *partial;
	पूर्णांक left;
	पूर्णांक depth = block_to_path(inode, iblock, offsets);

	अगर (depth == 0)
		जाओ out;

reपढ़ो:
	पढ़ो_lock(&poपूर्णांकers_lock);
	partial = get_branch(inode, depth, offsets, chain, &err);
	पढ़ो_unlock(&poपूर्णांकers_lock);

	/* Simplest हाल - block found, no allocation needed */
	अगर (!partial) अणु
got_it:
		map_bh(bh_result, sb, block_to_cpu(SYSV_SB(sb),
					chain[depth-1].key));
		/* Clean up and निकास */
		partial = chain+depth-1; /* the whole chain */
		जाओ cleanup;
	पूर्ण

	/* Next simple हाल - plain lookup or failed पढ़ो of indirect block */
	अगर (!create || err == -EIO) अणु
cleanup:
		जबतक (partial > chain) अणु
			brअन्यथा(partial->bh);
			partial--;
		पूर्ण
out:
		वापस err;
	पूर्ण

	/*
	 * Indirect block might be हटाओd by truncate जबतक we were
	 * पढ़ोing it. Handling of that हाल (क्रमget what we've got and
	 * reपढ़ो) is taken out of the मुख्य path.
	 */
	अगर (err == -EAGAIN)
		जाओ changed;

	left = (chain + depth) - partial;
	err = alloc_branch(inode, left, offsets+(partial-chain), partial);
	अगर (err)
		जाओ cleanup;

	अगर (splice_branch(inode, chain, partial, left) < 0)
		जाओ changed;

	set_buffer_new(bh_result);
	जाओ got_it;

changed:
	जबतक (partial > chain) अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
	जाओ reपढ़ो;
पूर्ण

अटल अंतरभूत पूर्णांक all_zeroes(sysv_zone_t *p, sysv_zone_t *q)
अणु
	जबतक (p < q)
		अगर (*p++)
			वापस 0;
	वापस 1;
पूर्ण

अटल Indirect *find_shared(काष्ठा inode *inode,
				पूर्णांक depth,
				पूर्णांक offsets[],
				Indirect chain[],
				sysv_zone_t *top)
अणु
	Indirect *partial, *p;
	पूर्णांक k, err;

	*top = 0;
	क्रम (k = depth; k > 1 && !offsets[k-1]; k--)
		;

	ग_लिखो_lock(&poपूर्णांकers_lock);
	partial = get_branch(inode, k, offsets, chain, &err);
	अगर (!partial)
		partial = chain + k-1;
	/*
	 * If the branch acquired continuation since we've looked at it -
	 * fine, it should all survive and (new) top करोesn't beदीर्घ to us.
	 */
	अगर (!partial->key && *partial->p) अणु
		ग_लिखो_unlock(&poपूर्णांकers_lock);
		जाओ no_top;
	पूर्ण
	क्रम (p=partial; p>chain && all_zeroes((sysv_zone_t*)p->bh->b_data,p->p); p--)
		;
	/*
	 * OK, we've found the last block that must survive. The rest of our
	 * branch should be detached beक्रमe unlocking. However, अगर that rest
	 * of branch is all ours and करोes not grow immediately from the inode
	 * it's easier to cheat and just decrement partial->p.
	 */
	अगर (p == chain + k - 1 && p > chain) अणु
		p->p--;
	पूर्ण अन्यथा अणु
		*top = *p->p;
		*p->p = 0;
	पूर्ण
	ग_लिखो_unlock(&poपूर्णांकers_lock);

	जबतक (partial > p) अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
no_top:
	वापस partial;
पूर्ण

अटल अंतरभूत व्योम मुक्त_data(काष्ठा inode *inode, sysv_zone_t *p, sysv_zone_t *q)
अणु
	क्रम ( ; p < q ; p++) अणु
		sysv_zone_t nr = *p;
		अगर (nr) अणु
			*p = 0;
			sysv_मुक्त_block(inode->i_sb, nr);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_branches(काष्ठा inode *inode, sysv_zone_t *p, sysv_zone_t *q, पूर्णांक depth)
अणु
	काष्ठा buffer_head * bh;
	काष्ठा super_block *sb = inode->i_sb;

	अगर (depth--) अणु
		क्रम ( ; p < q ; p++) अणु
			पूर्णांक block;
			sysv_zone_t nr = *p;
			अगर (!nr)
				जारी;
			*p = 0;
			block = block_to_cpu(SYSV_SB(sb), nr);
			bh = sb_bपढ़ो(sb, block);
			अगर (!bh)
				जारी;
			मुक्त_branches(inode, (sysv_zone_t*)bh->b_data,
					block_end(bh), depth);
			bक्रमget(bh);
			sysv_मुक्त_block(sb, nr);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण अन्यथा
		मुक्त_data(inode, p, q);
पूर्ण

व्योम sysv_truncate (काष्ठा inode * inode)
अणु
	sysv_zone_t *i_data = SYSV_I(inode)->i_data;
	पूर्णांक offsets[DEPTH];
	Indirect chain[DEPTH];
	Indirect *partial;
	sysv_zone_t nr = 0;
	पूर्णांक n;
	दीर्घ iblock;
	अचिन्हित blocksize;

	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)))
		वापस;

	blocksize = inode->i_sb->s_blocksize;
	iblock = (inode->i_size + blocksize-1)
					>> inode->i_sb->s_blocksize_bits;

	block_truncate_page(inode->i_mapping, inode->i_size, get_block);

	n = block_to_path(inode, iblock, offsets);
	अगर (n == 0)
		वापस;

	अगर (n == 1) अणु
		मुक्त_data(inode, i_data+offsets[0], i_data + सूचीECT);
		जाओ करो_indirects;
	पूर्ण

	partial = find_shared(inode, n, offsets, chain, &nr);
	/* Kill the top of shared branch (alपढ़ोy detached) */
	अगर (nr) अणु
		अगर (partial == chain)
			mark_inode_dirty(inode);
		अन्यथा
			dirty_indirect(partial->bh, inode);
		मुक्त_branches(inode, &nr, &nr+1, (chain+n-1) - partial);
	पूर्ण
	/* Clear the ends of indirect blocks on the shared branch */
	जबतक (partial > chain) अणु
		मुक्त_branches(inode, partial->p + 1, block_end(partial->bh),
				(chain+n-1) - partial);
		dirty_indirect(partial->bh, inode);
		brअन्यथा (partial->bh);
		partial--;
	पूर्ण
करो_indirects:
	/* Kill the reमुख्यing (whole) subtrees (== subtrees deeper than...) */
	जबतक (n < DEPTH) अणु
		nr = i_data[सूचीECT + n - 1];
		अगर (nr) अणु
			i_data[सूचीECT + n - 1] = 0;
			mark_inode_dirty(inode);
			मुक्त_branches(inode, &nr, &nr+1, n);
		पूर्ण
		n++;
	पूर्ण
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode))
		sysv_sync_inode (inode);
	अन्यथा
		mark_inode_dirty(inode);
पूर्ण

अटल अचिन्हित sysv_nblocks(काष्ठा super_block *s, loff_t size)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(s);
	पूर्णांक ptrs_bits = sbi->s_ind_per_block_bits;
	अचिन्हित blocks, res, direct = सूचीECT, i = DEPTH;
	blocks = (size + s->s_blocksize - 1) >> s->s_blocksize_bits;
	res = blocks;
	जबतक (--i && blocks > direct) अणु
		blocks = ((blocks - direct - 1) >> ptrs_bits) + 1;
		res += blocks;
		direct = 1;
	पूर्ण
	वापस blocks;
पूर्ण

पूर्णांक sysv_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *s = path->dentry->d_sb;
	generic_fillattr(&init_user_ns, d_inode(path->dentry), stat);
	stat->blocks = (s->s_blocksize / 512) * sysv_nblocks(s, stat->size);
	stat->blksize = s->s_blocksize;
	वापस 0;
पूर्ण

अटल पूर्णांक sysv_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page,get_block,wbc);
पूर्ण

अटल पूर्णांक sysv_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page,get_block);
पूर्ण

पूर्णांक sysv_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	वापस __block_ग_लिखो_begin(page, pos, len, get_block);
पूर्ण

अटल व्योम sysv_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		sysv_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक sysv_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep, get_block);
	अगर (unlikely(ret))
		sysv_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t sysv_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,get_block);
पूर्ण

स्थिर काष्ठा address_space_operations sysv_aops = अणु
	.पढ़ोpage = sysv_पढ़ोpage,
	.ग_लिखोpage = sysv_ग_लिखोpage,
	.ग_लिखो_begin = sysv_ग_लिखो_begin,
	.ग_लिखो_end = generic_ग_लिखो_end,
	.bmap = sysv_bmap
पूर्ण;
