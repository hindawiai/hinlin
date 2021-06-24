<शैली गुरु>
/*
 *  linux/fs/hfs/biपंचांगap.c
 *
 * Copyright (C) 1996-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * Based on GPLed code Copyright (C) 1995  Michael Dreher
 *
 * This file contains the code to modअगरy the volume biपंचांगap:
 * search/set/clear bits.
 */

#समावेश "hfs_fs.h"

/*
 * hfs_find_zero_bit()
 *
 * Description:
 *  Given a block of memory, its length in bits, and a starting bit number,
 *  determine the number of the first zero bits (in left-to-right ordering)
 *  in that range.
 *
 *  Returns >= 'size' अगर no zero bits are found in the range.
 *
 *  Accesses memory in 32-bit aligned chunks of 32-bits and thus
 *  may पढ़ो beyond the 'size'th bit.
 */
अटल u32 hfs_find_set_zero_bits(__be32 *biपंचांगap, u32 size, u32 offset, u32 *max)
अणु
	__be32 *curr, *end;
	u32 mask, start, len, n;
	__be32 val;
	पूर्णांक i;

	len = *max;
	अगर (!len)
		वापस size;

	curr = biपंचांगap + (offset / 32);
	end = biपंचांगap + ((size + 31) / 32);

	/* scan the first partial u32 क्रम zero bits */
	val = *curr;
	अगर (~val) अणु
		n = be32_to_cpu(val);
		i = offset % 32;
		mask = (1U << 31) >> i;
		क्रम (; i < 32; mask >>= 1, i++) अणु
			अगर (!(n & mask))
				जाओ found;
		पूर्ण
	पूर्ण

	/* scan complete u32s क्रम the first zero bit */
	जबतक (++curr < end) अणु
		val = *curr;
		अगर (~val) अणु
			n = be32_to_cpu(val);
			mask = 1 << 31;
			क्रम (i = 0; i < 32; mask >>= 1, i++) अणु
				अगर (!(n & mask))
					जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस size;

found:
	start = (curr - biपंचांगap) * 32 + i;
	अगर (start >= size)
		वापस start;
	/* करो any partial u32 at the start */
	len = min(size - start, len);
	जबतक (1) अणु
		n |= mask;
		अगर (++i >= 32)
			अवरोध;
		mask >>= 1;
		अगर (!--len || n & mask)
			जाओ करोne;
	पूर्ण
	अगर (!--len)
		जाओ करोne;
	*curr++ = cpu_to_be32(n);
	/* करो full u32s */
	जबतक (1) अणु
		n = be32_to_cpu(*curr);
		अगर (len < 32)
			अवरोध;
		अगर (n) अणु
			len = 32;
			अवरोध;
		पूर्ण
		*curr++ = cpu_to_be32(0xffffffff);
		len -= 32;
	पूर्ण
	/* करो any partial u32 at end */
	mask = 1U << 31;
	क्रम (i = 0; i < len; i++) अणु
		अगर (n & mask)
			अवरोध;
		n |= mask;
		mask >>= 1;
	पूर्ण
करोne:
	*curr = cpu_to_be32(n);
	*max = (curr - biपंचांगap) * 32 + i - start;
	वापस start;
पूर्ण

/*
 * hfs_vbm_search_मुक्त()
 *
 * Description:
 *   Search क्रम 'num_bits' consecutive cleared bits in the biपंचांगap blocks of
 *   the hfs MDB. 'mdb' had better be locked or the वापसed range
 *   may be no दीर्घer मुक्त, when this functions वापसs!
 *   XXX Currently the search starts from bit 0, but it should start with
 *   the bit number stored in 's_alloc_ptr' of the MDB.
 * Input Variable(s):
 *   काष्ठा hfs_mdb *mdb: Poपूर्णांकer to the hfs MDB
 *   u16 *num_bits: Poपूर्णांकer to the number of cleared bits
 *     to search क्रम
 * Output Variable(s):
 *   u16 *num_bits: The number of consecutive clear bits of the
 *     वापसed range. If the biपंचांगap is fragmented, this will be less than
 *     requested and it will be zero, when the disk is full.
 * Returns:
 *   The number of the first bit of the range of cleared bits which has been
 *   found. When 'num_bits' is zero, this is invalid!
 * Preconditions:
 *   'mdb' poपूर्णांकs to a "valid" (काष्ठा hfs_mdb).
 *   'num_bits' poपूर्णांकs to a variable of type (u16), which contains
 *	the number of cleared bits to find.
 * Postconditions:
 *   'num_bits' is set to the length of the found sequence.
 */
u32 hfs_vbm_search_मुक्त(काष्ठा super_block *sb, u32 goal, u32 *num_bits)
अणु
	व्योम *biपंचांगap;
	u32 pos;

	/* make sure we have actual work to perक्रमm */
	अगर (!*num_bits)
		वापस 0;

	mutex_lock(&HFS_SB(sb)->biपंचांगap_lock);
	biपंचांगap = HFS_SB(sb)->biपंचांगap;

	pos = hfs_find_set_zero_bits(biपंचांगap, HFS_SB(sb)->fs_ablocks, goal, num_bits);
	अगर (pos >= HFS_SB(sb)->fs_ablocks) अणु
		अगर (goal)
			pos = hfs_find_set_zero_bits(biपंचांगap, goal, 0, num_bits);
		अगर (pos >= HFS_SB(sb)->fs_ablocks) अणु
			*num_bits = pos = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	hfs_dbg(BITMAP, "alloc_bits: %u,%u\n", pos, *num_bits);
	HFS_SB(sb)->मुक्त_ablocks -= *num_bits;
	hfs_biपंचांगap_dirty(sb);
out:
	mutex_unlock(&HFS_SB(sb)->biपंचांगap_lock);
	वापस pos;
पूर्ण


/*
 * hfs_clear_vbm_bits()
 *
 * Description:
 *   Clear the requested bits in the volume biपंचांगap of the hfs fileप्रणाली
 * Input Variable(s):
 *   काष्ठा hfs_mdb *mdb: Poपूर्णांकer to the hfs MDB
 *   u16 start: The offset of the first bit
 *   u16 count: The number of bits
 * Output Variable(s):
 *   None
 * Returns:
 *    0: no error
 *   -1: One of the bits was alपढ़ोy clear.  This is a strange
 *	 error and when it happens, the fileप्रणाली must be repaired!
 *   -2: One or more of the bits are out of range of the biपंचांगap.
 * Preconditions:
 *   'mdb' poपूर्णांकs to a "valid" (काष्ठा hfs_mdb).
 * Postconditions:
 *   Starting with bit number 'start', 'count' bits in the volume biपंचांगap
 *   are cleared. The affected biपंचांगap blocks are marked "dirty", the मुक्त
 *   block count of the MDB is updated and the MDB is marked dirty.
 */
पूर्णांक hfs_clear_vbm_bits(काष्ठा super_block *sb, u16 start, u16 count)
अणु
	__be32 *curr;
	u32 mask;
	पूर्णांक i, len;

	/* is there any actual work to be करोne? */
	अगर (!count)
		वापस 0;

	hfs_dbg(BITMAP, "clear_bits: %u,%u\n", start, count);
	/* are all of the bits in range? */
	अगर ((start + count) > HFS_SB(sb)->fs_ablocks)
		वापस -2;

	mutex_lock(&HFS_SB(sb)->biपंचांगap_lock);
	/* biपंचांगap is always on a 32-bit boundary */
	curr = HFS_SB(sb)->biपंचांगap + (start / 32);
	len = count;

	/* करो any partial u32 at the start */
	i = start % 32;
	अगर (i) अणु
		पूर्णांक j = 32 - i;
		mask = 0xffffffffU << j;
		अगर (j > count) अणु
			mask |= 0xffffffffU >> (i + count);
			*curr &= cpu_to_be32(mask);
			जाओ out;
		पूर्ण
		*curr++ &= cpu_to_be32(mask);
		count -= j;
	पूर्ण

	/* करो full u32s */
	जबतक (count >= 32) अणु
		*curr++ = 0;
		count -= 32;
	पूर्ण
	/* करो any partial u32 at end */
	अगर (count) अणु
		mask = 0xffffffffU >> count;
		*curr &= cpu_to_be32(mask);
	पूर्ण
out:
	HFS_SB(sb)->मुक्त_ablocks += len;
	mutex_unlock(&HFS_SB(sb)->biपंचांगap_lock);
	hfs_biपंचांगap_dirty(sb);

	वापस 0;
पूर्ण
