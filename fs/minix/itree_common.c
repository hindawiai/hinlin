<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Generic part */

प्रकार काष्ठा अणु
	block_t	*p;
	block_t	key;
	काष्ठा buffer_head *bh;
पूर्ण Indirect;

अटल DEFINE_RWLOCK(poपूर्णांकers_lock);

अटल अंतरभूत व्योम add_chain(Indirect *p, काष्ठा buffer_head *bh, block_t *v)
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

अटल अंतरभूत block_t *block_end(काष्ठा buffer_head *bh)
अणु
	वापस (block_t *)((अक्षर*)bh->b_data + bh->b_size);
पूर्ण

अटल अंतरभूत Indirect *get_branch(काष्ठा inode *inode,
					पूर्णांक depth,
					पूर्णांक *offsets,
					Indirect chain[DEPTH],
					पूर्णांक *err)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	Indirect *p = chain;
	काष्ठा buffer_head *bh;

	*err = 0;
	/* i_data is not going away, no lock needed */
	add_chain (chain, शून्य, i_data(inode) + *offsets);
	अगर (!p->key)
		जाओ no_block;
	जबतक (--depth) अणु
		bh = sb_bपढ़ो(sb, block_to_cpu(p->key));
		अगर (!bh)
			जाओ failure;
		पढ़ो_lock(&poपूर्णांकers_lock);
		अगर (!verअगरy_chain(chain, p))
			जाओ changed;
		add_chain(++p, bh, (block_t *)bh->b_data + *++offsets);
		पढ़ो_unlock(&poपूर्णांकers_lock);
		अगर (!p->key)
			जाओ no_block;
	पूर्ण
	वापस शून्य;

changed:
	पढ़ो_unlock(&poपूर्णांकers_lock);
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
	पूर्णांक n = 0;
	पूर्णांक i;
	पूर्णांक parent = minix_new_block(inode);
	पूर्णांक err = -ENOSPC;

	branch[0].key = cpu_to_block(parent);
	अगर (parent) क्रम (n = 1; n < num; n++) अणु
		काष्ठा buffer_head *bh;
		/* Allocate the next block */
		पूर्णांक nr = minix_new_block(inode);
		अगर (!nr)
			अवरोध;
		branch[n].key = cpu_to_block(nr);
		bh = sb_getblk(inode->i_sb, parent);
		अगर (!bh) अणु
			minix_मुक्त_block(inode, nr);
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		lock_buffer(bh);
		स_रखो(bh->b_data, 0, bh->b_size);
		branch[n].bh = bh;
		branch[n].p = (block_t*) bh->b_data + offsets[n];
		*branch[n].p = branch[n].key;
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		mark_buffer_dirty_inode(bh, inode);
		parent = nr;
	पूर्ण
	अगर (n == num)
		वापस 0;

	/* Allocation failed, मुक्त what we alपढ़ोy allocated */
	क्रम (i = 1; i < n; i++)
		bक्रमget(branch[i].bh);
	क्रम (i = 0; i < n; i++)
		minix_मुक्त_block(inode, block_to_cpu(branch[i].key));
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक splice_branch(काष्ठा inode *inode,
				     Indirect chain[DEPTH],
				     Indirect *where,
				     पूर्णांक num)
अणु
	पूर्णांक i;

	ग_लिखो_lock(&poपूर्णांकers_lock);

	/* Verअगरy that place we are splicing to is still there and vacant */
	अगर (!verअगरy_chain(chain, where-1) || *where->p)
		जाओ changed;

	*where->p = where->key;

	ग_लिखो_unlock(&poपूर्णांकers_lock);

	/* We are करोne with atomic stuff, now करो the rest of housekeeping */

	inode->i_स_समय = current_समय(inode);

	/* had we spliced it onto indirect block? */
	अगर (where->bh)
		mark_buffer_dirty_inode(where->bh, inode);

	mark_inode_dirty(inode);
	वापस 0;

changed:
	ग_लिखो_unlock(&poपूर्णांकers_lock);
	क्रम (i = 1; i < num; i++)
		bक्रमget(where[i].bh);
	क्रम (i = 0; i < num; i++)
		minix_मुक्त_block(inode, block_to_cpu(where[i].key));
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक get_block(काष्ठा inode * inode, sector_t block,
			काष्ठा buffer_head *bh, पूर्णांक create)
अणु
	पूर्णांक err = -EIO;
	पूर्णांक offsets[DEPTH];
	Indirect chain[DEPTH];
	Indirect *partial;
	पूर्णांक left;
	पूर्णांक depth = block_to_path(inode, block, offsets);

	अगर (depth == 0)
		जाओ out;

reपढ़ो:
	partial = get_branch(inode, depth, offsets, chain, &err);

	/* Simplest हाल - block found, no allocation needed */
	अगर (!partial) अणु
got_it:
		map_bh(bh, inode->i_sb, block_to_cpu(chain[depth-1].key));
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

	set_buffer_new(bh);
	जाओ got_it;

changed:
	जबतक (partial > chain) अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
	जाओ reपढ़ो;
पूर्ण

अटल अंतरभूत पूर्णांक all_zeroes(block_t *p, block_t *q)
अणु
	जबतक (p < q)
		अगर (*p++)
			वापस 0;
	वापस 1;
पूर्ण

अटल Indirect *find_shared(काष्ठा inode *inode,
				पूर्णांक depth,
				पूर्णांक offsets[DEPTH],
				Indirect chain[DEPTH],
				block_t *top)
अणु
	Indirect *partial, *p;
	पूर्णांक k, err;

	*top = 0;
	क्रम (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	partial = get_branch(inode, k, offsets, chain, &err);

	ग_लिखो_lock(&poपूर्णांकers_lock);
	अगर (!partial)
		partial = chain + k-1;
	अगर (!partial->key && *partial->p) अणु
		ग_लिखो_unlock(&poपूर्णांकers_lock);
		जाओ no_top;
	पूर्ण
	क्रम (p=partial;p>chain && all_zeroes((block_t*)p->bh->b_data,p->p);p--)
		;
	अगर (p == chain + k - 1 && p > chain) अणु
		p->p--;
	पूर्ण अन्यथा अणु
		*top = *p->p;
		*p->p = 0;
	पूर्ण
	ग_लिखो_unlock(&poपूर्णांकers_lock);

	जबतक(partial > p)
	अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
no_top:
	वापस partial;
पूर्ण

अटल अंतरभूत व्योम मुक्त_data(काष्ठा inode *inode, block_t *p, block_t *q)
अणु
	अचिन्हित दीर्घ nr;

	क्रम ( ; p < q ; p++) अणु
		nr = block_to_cpu(*p);
		अगर (nr) अणु
			*p = 0;
			minix_मुक्त_block(inode, nr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_branches(काष्ठा inode *inode, block_t *p, block_t *q, पूर्णांक depth)
अणु
	काष्ठा buffer_head * bh;
	अचिन्हित दीर्घ nr;

	अगर (depth--) अणु
		क्रम ( ; p < q ; p++) अणु
			nr = block_to_cpu(*p);
			अगर (!nr)
				जारी;
			*p = 0;
			bh = sb_bपढ़ो(inode->i_sb, nr);
			अगर (!bh)
				जारी;
			मुक्त_branches(inode, (block_t*)bh->b_data,
				      block_end(bh), depth);
			bक्रमget(bh);
			minix_मुक्त_block(inode, nr);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण अन्यथा
		मुक्त_data(inode, p, q);
पूर्ण

अटल अंतरभूत व्योम truncate (काष्ठा inode * inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	block_t *idata = i_data(inode);
	पूर्णांक offsets[DEPTH];
	Indirect chain[DEPTH];
	Indirect *partial;
	block_t nr = 0;
	पूर्णांक n;
	पूर्णांक first_whole;
	दीर्घ iblock;

	iblock = (inode->i_size + sb->s_blocksize -1) >> sb->s_blocksize_bits;
	block_truncate_page(inode->i_mapping, inode->i_size, get_block);

	n = block_to_path(inode, iblock, offsets);
	अगर (!n)
		वापस;

	अगर (n == 1) अणु
		मुक्त_data(inode, idata+offsets[0], idata + सूचीECT);
		first_whole = 0;
		जाओ करो_indirects;
	पूर्ण

	first_whole = offsets[0] + 1 - सूचीECT;
	partial = find_shared(inode, n, offsets, chain, &nr);
	अगर (nr) अणु
		अगर (partial == chain)
			mark_inode_dirty(inode);
		अन्यथा
			mark_buffer_dirty_inode(partial->bh, inode);
		मुक्त_branches(inode, &nr, &nr+1, (chain+n-1) - partial);
	पूर्ण
	/* Clear the ends of indirect blocks on the shared branch */
	जबतक (partial > chain) अणु
		मुक्त_branches(inode, partial->p + 1, block_end(partial->bh),
				(chain+n-1) - partial);
		mark_buffer_dirty_inode(partial->bh, inode);
		brअन्यथा (partial->bh);
		partial--;
	पूर्ण
करो_indirects:
	/* Kill the reमुख्यing (whole) subtrees */
	जबतक (first_whole < DEPTH-1) अणु
		nr = idata[सूचीECT+first_whole];
		अगर (nr) अणु
			idata[सूचीECT+first_whole] = 0;
			mark_inode_dirty(inode);
			मुक्त_branches(inode, &nr, &nr+1, first_whole+1);
		पूर्ण
		first_whole++;
	पूर्ण
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
पूर्ण

अटल अंतरभूत अचिन्हित nblocks(loff_t size, काष्ठा super_block *sb)
अणु
	पूर्णांक k = sb->s_blocksize_bits - 10;
	अचिन्हित blocks, res, direct = सूचीECT, i = DEPTH;
	blocks = (size + sb->s_blocksize - 1) >> (BLOCK_SIZE_BITS + k);
	res = blocks;
	जबतक (--i && blocks > direct) अणु
		blocks -= direct;
		blocks += sb->s_blocksize/माप(block_t) - 1;
		blocks /= sb->s_blocksize/माप(block_t);
		res += blocks;
		direct = 1;
	पूर्ण
	वापस res;
पूर्ण
