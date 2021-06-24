<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "omfs.h"

अचिन्हित दीर्घ omfs_count_मुक्त(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ sum = 0;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	पूर्णांक nbits = sb->s_blocksize * 8;

	क्रम (i = 0; i < sbi->s_imap_size; i++)
		sum += nbits - biपंचांगap_weight(sbi->s_imap[i], nbits);

	वापस sum;
पूर्ण

/*
 *  Counts the run of zero bits starting at bit up to max.
 *  It handles the हाल where a run might spill over a buffer.
 *  Called with biपंचांगap lock.
 */
अटल पूर्णांक count_run(अचिन्हित दीर्घ **addr, पूर्णांक nbits,
		पूर्णांक addrlen, पूर्णांक bit, पूर्णांक max)
अणु
	पूर्णांक count = 0;
	पूर्णांक x;

	क्रम (; addrlen > 0; addrlen--, addr++) अणु
		x = find_next_bit(*addr, nbits, bit);
		count += x - bit;

		अगर (x < nbits || count > max)
			वापस min(count, max);

		bit = 0;
	पूर्ण
	वापस min(count, max);
पूर्ण

/*
 * Sets or clears the run of count bits starting with bit.
 * Called with biपंचांगap lock.
 */
अटल पूर्णांक set_run(काष्ठा super_block *sb, पूर्णांक map,
		पूर्णांक nbits, पूर्णांक bit, पूर्णांक count, पूर्णांक set)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा buffer_head *bh;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);

 	err = -ENOMEM;
	bh = sb_bपढ़ो(sb, clus_to_blk(sbi, sbi->s_biपंचांगap_ino) + map);
	अगर (!bh)
		जाओ out;

	क्रम (i = 0; i < count; i++, bit++) अणु
		अगर (bit >= nbits) अणु
			bit = 0;
			map++;

			mark_buffer_dirty(bh);
			brअन्यथा(bh);
			bh = sb_bपढ़ो(sb,
				clus_to_blk(sbi, sbi->s_biपंचांगap_ino) + map);
			अगर (!bh)
				जाओ out;
		पूर्ण
		अगर (set) अणु
			set_bit(bit, sbi->s_imap[map]);
			set_bit(bit, (अचिन्हित दीर्घ *)bh->b_data);
		पूर्ण अन्यथा अणु
			clear_bit(bit, sbi->s_imap[map]);
			clear_bit(bit, (अचिन्हित दीर्घ *)bh->b_data);
		पूर्ण
	पूर्ण
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	err = 0;
out:
	वापस err;
पूर्ण

/*
 * Tries to allocate exactly one block.  Returns true अगर successful.
 */
पूर्णांक omfs_allocate_block(काष्ठा super_block *sb, u64 block)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	पूर्णांक bits_per_entry = 8 * sb->s_blocksize;
	अचिन्हित पूर्णांक map, bit;
	पूर्णांक ret = 0;
	u64 पंचांगp;

	पंचांगp = block;
	bit = करो_भाग(पंचांगp, bits_per_entry);
	map = पंचांगp;

	mutex_lock(&sbi->s_biपंचांगap_lock);
	अगर (map >= sbi->s_imap_size || test_and_set_bit(bit, sbi->s_imap[map]))
		जाओ out;

	अगर (sbi->s_biपंचांगap_ino > 0) अणु
		bh = sb_bपढ़ो(sb, clus_to_blk(sbi, sbi->s_biपंचांगap_ino) + map);
		अगर (!bh)
			जाओ out;

		set_bit(bit, (अचिन्हित दीर्घ *)bh->b_data);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
	पूर्ण
	ret = 1;
out:
	mutex_unlock(&sbi->s_biपंचांगap_lock);
	वापस ret;
पूर्ण


/*
 *  Tries to allocate a set of blocks.	The request size depends on the
 *  type: क्रम inodes, we must allocate sbi->s_mirrors blocks, and क्रम file
 *  blocks, we try to allocate sbi->s_clustersize, but can always get away
 *  with just one block.
 */
पूर्णांक omfs_allocate_range(काष्ठा super_block *sb,
			पूर्णांक min_request,
			पूर्णांक max_request,
			u64 *वापस_block,
			पूर्णांक *वापस_size)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	पूर्णांक bits_per_entry = 8 * sb->s_blocksize;
	पूर्णांक ret = 0;
	पूर्णांक i, run, bit;

	mutex_lock(&sbi->s_biपंचांगap_lock);
	क्रम (i = 0; i < sbi->s_imap_size; i++) अणु
		bit = 0;
		जबतक (bit < bits_per_entry) अणु
			bit = find_next_zero_bit(sbi->s_imap[i], bits_per_entry,
				bit);

			अगर (bit == bits_per_entry)
				अवरोध;

			run = count_run(&sbi->s_imap[i], bits_per_entry,
				sbi->s_imap_size-i, bit, max_request);

			अगर (run >= min_request)
				जाओ found;
			bit += run;
		पूर्ण
	पूर्ण
	ret = -ENOSPC;
	जाओ out;

found:
	*वापस_block = (u64) i * bits_per_entry + bit;
	*वापस_size = run;
	ret = set_run(sb, i, bits_per_entry, bit, run, 1);

out:
	mutex_unlock(&sbi->s_biपंचांगap_lock);
	वापस ret;
पूर्ण

/*
 * Clears count bits starting at a given block.
 */
पूर्णांक omfs_clear_range(काष्ठा super_block *sb, u64 block, पूर्णांक count)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	पूर्णांक bits_per_entry = 8 * sb->s_blocksize;
	u64 पंचांगp;
	अचिन्हित पूर्णांक map, bit;
	पूर्णांक ret;

	पंचांगp = block;
	bit = करो_भाग(पंचांगp, bits_per_entry);
	map = पंचांगp;

	अगर (map >= sbi->s_imap_size)
		वापस 0;

	mutex_lock(&sbi->s_biपंचांगap_lock);
	ret = set_run(sb, map, bits_per_entry, bit, count, 0);
	mutex_unlock(&sbi->s_biपंचांगap_lock);
	वापस ret;
पूर्ण
