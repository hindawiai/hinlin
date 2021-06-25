<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_attr_sf.h"
#समावेश "xfs_attr_remote.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_log.h"


/*
 * xfs_attr_leaf.c
 *
 * Routines to implement leaf blocks of attributes as Btrees of hashed names.
 */

/*========================================================================
 * Function prototypes क्रम the kernel.
 *========================================================================*/

/*
 * Routines used क्रम growing the Btree.
 */
STATIC पूर्णांक xfs_attr3_leaf_create(काष्ठा xfs_da_args *args,
				 xfs_dablk_t which_block, काष्ठा xfs_buf **bpp);
STATIC पूर्णांक xfs_attr3_leaf_add_work(काष्ठा xfs_buf *leaf_buffer,
				   काष्ठा xfs_attr3_icleaf_hdr *ichdr,
				   काष्ठा xfs_da_args *args, पूर्णांक मुक्तmap_index);
STATIC व्योम xfs_attr3_leaf_compact(काष्ठा xfs_da_args *args,
				   काष्ठा xfs_attr3_icleaf_hdr *ichdr,
				   काष्ठा xfs_buf *leaf_buffer);
STATIC व्योम xfs_attr3_leaf_rebalance(xfs_da_state_t *state,
						   xfs_da_state_blk_t *blk1,
						   xfs_da_state_blk_t *blk2);
STATIC पूर्णांक xfs_attr3_leaf_figure_balance(xfs_da_state_t *state,
			xfs_da_state_blk_t *leaf_blk_1,
			काष्ठा xfs_attr3_icleaf_hdr *ichdr1,
			xfs_da_state_blk_t *leaf_blk_2,
			काष्ठा xfs_attr3_icleaf_hdr *ichdr2,
			पूर्णांक *number_entries_in_blk1,
			पूर्णांक *number_usedbytes_in_blk1);

/*
 * Utility routines.
 */
STATIC व्योम xfs_attr3_leaf_moveents(काष्ठा xfs_da_args *args,
			काष्ठा xfs_attr_leafblock *src_leaf,
			काष्ठा xfs_attr3_icleaf_hdr *src_ichdr, पूर्णांक src_start,
			काष्ठा xfs_attr_leafblock *dst_leaf,
			काष्ठा xfs_attr3_icleaf_hdr *dst_ichdr, पूर्णांक dst_start,
			पूर्णांक move_count);
STATIC पूर्णांक xfs_attr_leaf_entsize(xfs_attr_leafblock_t *leaf, पूर्णांक index);

/*
 * attr3 block 'firstused' conversion helpers.
 *
 * firstused refers to the offset of the first used byte of the nameval region
 * of an attr leaf block. The region starts at the tail of the block and expands
 * backwards towards the middle. As such, firstused is initialized to the block
 * size क्रम an empty leaf block and is reduced from there.
 *
 * The attr3 block size is pegged to the fsb size and the maximum fsb is 64k.
 * The in-core firstused field is 32-bit and thus supports the maximum fsb size.
 * The on-disk field is only 16-bit, however, and overflows at 64k. Since this
 * only occurs at exactly 64k, we use zero as a magic on-disk value to represent
 * the attr block size. The following helpers manage the conversion between the
 * in-core and on-disk क्रमmats.
 */

अटल व्योम
xfs_attr3_leaf_firstused_from_disk(
	काष्ठा xfs_da_geometry		*geo,
	काष्ठा xfs_attr3_icleaf_hdr	*to,
	काष्ठा xfs_attr_leafblock	*from)
अणु
	काष्ठा xfs_attr3_leaf_hdr	*hdr3;

	अगर (from->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC)) अणु
		hdr3 = (काष्ठा xfs_attr3_leaf_hdr *) from;
		to->firstused = be16_to_cpu(hdr3->firstused);
	पूर्ण अन्यथा अणु
		to->firstused = be16_to_cpu(from->hdr.firstused);
	पूर्ण

	/*
	 * Convert from the magic fsb size value to actual blocksize. This
	 * should only occur क्रम empty blocks when the block size overflows
	 * 16-bits.
	 */
	अगर (to->firstused == XFS_ATTR3_LEAF_शून्यOFF) अणु
		ASSERT(!to->count && !to->usedbytes);
		ASSERT(geo->blksize > अच_लघु_उच्च);
		to->firstused = geo->blksize;
	पूर्ण
पूर्ण

अटल व्योम
xfs_attr3_leaf_firstused_to_disk(
	काष्ठा xfs_da_geometry		*geo,
	काष्ठा xfs_attr_leafblock	*to,
	काष्ठा xfs_attr3_icleaf_hdr	*from)
अणु
	काष्ठा xfs_attr3_leaf_hdr	*hdr3;
	uपूर्णांक32_t			firstused;

	/* magic value should only be seen on disk */
	ASSERT(from->firstused != XFS_ATTR3_LEAF_शून्यOFF);

	/*
	 * Scale करोwn the 32-bit in-core firstused value to the 16-bit on-disk
	 * value. This only overflows at the max supported value of 64k. Use the
	 * magic on-disk value to represent block size in this हाल.
	 */
	firstused = from->firstused;
	अगर (firstused > अच_लघु_उच्च) अणु
		ASSERT(from->firstused == geo->blksize);
		firstused = XFS_ATTR3_LEAF_शून्यOFF;
	पूर्ण

	अगर (from->magic == XFS_ATTR3_LEAF_MAGIC) अणु
		hdr3 = (काष्ठा xfs_attr3_leaf_hdr *) to;
		hdr3->firstused = cpu_to_be16(firstused);
	पूर्ण अन्यथा अणु
		to->hdr.firstused = cpu_to_be16(firstused);
	पूर्ण
पूर्ण

व्योम
xfs_attr3_leaf_hdr_from_disk(
	काष्ठा xfs_da_geometry		*geo,
	काष्ठा xfs_attr3_icleaf_hdr	*to,
	काष्ठा xfs_attr_leafblock	*from)
अणु
	पूर्णांक	i;

	ASSERT(from->hdr.info.magic == cpu_to_be16(XFS_ATTR_LEAF_MAGIC) ||
	       from->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC));

	अगर (from->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC)) अणु
		काष्ठा xfs_attr3_leaf_hdr *hdr3 = (काष्ठा xfs_attr3_leaf_hdr *)from;

		to->क्रमw = be32_to_cpu(hdr3->info.hdr.क्रमw);
		to->back = be32_to_cpu(hdr3->info.hdr.back);
		to->magic = be16_to_cpu(hdr3->info.hdr.magic);
		to->count = be16_to_cpu(hdr3->count);
		to->usedbytes = be16_to_cpu(hdr3->usedbytes);
		xfs_attr3_leaf_firstused_from_disk(geo, to, from);
		to->holes = hdr3->holes;

		क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
			to->मुक्तmap[i].base = be16_to_cpu(hdr3->मुक्तmap[i].base);
			to->मुक्तmap[i].size = be16_to_cpu(hdr3->मुक्तmap[i].size);
		पूर्ण
		वापस;
	पूर्ण
	to->क्रमw = be32_to_cpu(from->hdr.info.क्रमw);
	to->back = be32_to_cpu(from->hdr.info.back);
	to->magic = be16_to_cpu(from->hdr.info.magic);
	to->count = be16_to_cpu(from->hdr.count);
	to->usedbytes = be16_to_cpu(from->hdr.usedbytes);
	xfs_attr3_leaf_firstused_from_disk(geo, to, from);
	to->holes = from->hdr.holes;

	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		to->मुक्तmap[i].base = be16_to_cpu(from->hdr.मुक्तmap[i].base);
		to->मुक्तmap[i].size = be16_to_cpu(from->hdr.मुक्तmap[i].size);
	पूर्ण
पूर्ण

व्योम
xfs_attr3_leaf_hdr_to_disk(
	काष्ठा xfs_da_geometry		*geo,
	काष्ठा xfs_attr_leafblock	*to,
	काष्ठा xfs_attr3_icleaf_hdr	*from)
अणु
	पूर्णांक				i;

	ASSERT(from->magic == XFS_ATTR_LEAF_MAGIC ||
	       from->magic == XFS_ATTR3_LEAF_MAGIC);

	अगर (from->magic == XFS_ATTR3_LEAF_MAGIC) अणु
		काष्ठा xfs_attr3_leaf_hdr *hdr3 = (काष्ठा xfs_attr3_leaf_hdr *)to;

		hdr3->info.hdr.क्रमw = cpu_to_be32(from->क्रमw);
		hdr3->info.hdr.back = cpu_to_be32(from->back);
		hdr3->info.hdr.magic = cpu_to_be16(from->magic);
		hdr3->count = cpu_to_be16(from->count);
		hdr3->usedbytes = cpu_to_be16(from->usedbytes);
		xfs_attr3_leaf_firstused_to_disk(geo, to, from);
		hdr3->holes = from->holes;
		hdr3->pad1 = 0;

		क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
			hdr3->मुक्तmap[i].base = cpu_to_be16(from->मुक्तmap[i].base);
			hdr3->मुक्तmap[i].size = cpu_to_be16(from->मुक्तmap[i].size);
		पूर्ण
		वापस;
	पूर्ण
	to->hdr.info.क्रमw = cpu_to_be32(from->क्रमw);
	to->hdr.info.back = cpu_to_be32(from->back);
	to->hdr.info.magic = cpu_to_be16(from->magic);
	to->hdr.count = cpu_to_be16(from->count);
	to->hdr.usedbytes = cpu_to_be16(from->usedbytes);
	xfs_attr3_leaf_firstused_to_disk(geo, to, from);
	to->hdr.holes = from->holes;
	to->hdr.pad1 = 0;

	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		to->hdr.मुक्तmap[i].base = cpu_to_be16(from->मुक्तmap[i].base);
		to->hdr.मुक्तmap[i].size = cpu_to_be16(from->मुक्तmap[i].size);
	पूर्ण
पूर्ण

अटल xfs_failaddr_t
xfs_attr3_leaf_verअगरy_entry(
	काष्ठा xfs_mount			*mp,
	अक्षर					*buf_end,
	काष्ठा xfs_attr_leafblock		*leaf,
	काष्ठा xfs_attr3_icleaf_hdr		*leafhdr,
	काष्ठा xfs_attr_leaf_entry		*ent,
	पूर्णांक					idx,
	__u32					*last_hashval)
अणु
	काष्ठा xfs_attr_leaf_name_local		*lentry;
	काष्ठा xfs_attr_leaf_name_remote	*rentry;
	अक्षर					*name_end;
	अचिन्हित पूर्णांक				nameidx;
	अचिन्हित पूर्णांक				namesize;
	__u32					hashval;

	/* hash order check */
	hashval = be32_to_cpu(ent->hashval);
	अगर (hashval < *last_hashval)
		वापस __this_address;
	*last_hashval = hashval;

	nameidx = be16_to_cpu(ent->nameidx);
	अगर (nameidx < leafhdr->firstused || nameidx >= mp->m_attr_geo->blksize)
		वापस __this_address;

	/*
	 * Check the name inक्रमmation.  The namelen fields are u8 so we can't
	 * possibly exceed the maximum name length of 255 bytes.
	 */
	अगर (ent->flags & XFS_ATTR_LOCAL) अणु
		lentry = xfs_attr3_leaf_name_local(leaf, idx);
		namesize = xfs_attr_leaf_entsize_local(lentry->namelen,
				be16_to_cpu(lentry->valuelen));
		name_end = (अक्षर *)lentry + namesize;
		अगर (lentry->namelen == 0)
			वापस __this_address;
	पूर्ण अन्यथा अणु
		rentry = xfs_attr3_leaf_name_remote(leaf, idx);
		namesize = xfs_attr_leaf_entsize_remote(rentry->namelen);
		name_end = (अक्षर *)rentry + namesize;
		अगर (rentry->namelen == 0)
			वापस __this_address;
		अगर (!(ent->flags & XFS_ATTR_INCOMPLETE) &&
		    rentry->valueblk == 0)
			वापस __this_address;
	पूर्ण

	अगर (name_end > buf_end)
		वापस __this_address;

	वापस शून्य;
पूर्ण

अटल xfs_failaddr_t
xfs_attr3_leaf_verअगरy(
	काष्ठा xfs_buf			*bp)
अणु
	काष्ठा xfs_attr3_icleaf_hdr	ichdr;
	काष्ठा xfs_mount		*mp = bp->b_mount;
	काष्ठा xfs_attr_leafblock	*leaf = bp->b_addr;
	काष्ठा xfs_attr_leaf_entry	*entries;
	काष्ठा xfs_attr_leaf_entry	*ent;
	अक्षर				*buf_end;
	uपूर्णांक32_t			end;	/* must be 32bit - see below */
	__u32				last_hashval = 0;
	पूर्णांक				i;
	xfs_failaddr_t			fa;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, leaf);

	fa = xfs_da3_blkinfo_verअगरy(bp, bp->b_addr);
	अगर (fa)
		वापस fa;

	/*
	 * firstused is the block offset of the first name info काष्ठाure.
	 * Make sure it करोesn't go off the block or crash पूर्णांकo the header.
	 */
	अगर (ichdr.firstused > mp->m_attr_geo->blksize)
		वापस __this_address;
	अगर (ichdr.firstused < xfs_attr3_leaf_hdr_size(leaf))
		वापस __this_address;

	/* Make sure the entries array करोesn't crash पूर्णांकo the name info. */
	entries = xfs_attr3_leaf_entryp(bp->b_addr);
	अगर ((अक्षर *)&entries[ichdr.count] >
	    (अक्षर *)bp->b_addr + ichdr.firstused)
		वापस __this_address;

	/*
	 * NOTE: This verअगरier historically failed empty leaf buffers because
	 * we expect the विभाजन to be in another क्रमmat. Empty attr विभाजन क्रमmat
	 * conversions are possible during xattr set, however, and क्रमmat
	 * conversion is not atomic with the xattr set that triggers it. We
	 * cannot assume leaf blocks are non-empty until that is addressed.
	*/
	buf_end = (अक्षर *)bp->b_addr + mp->m_attr_geo->blksize;
	क्रम (i = 0, ent = entries; i < ichdr.count; ent++, i++) अणु
		fa = xfs_attr3_leaf_verअगरy_entry(mp, buf_end, leaf, &ichdr,
				ent, i, &last_hashval);
		अगर (fa)
			वापस fa;
	पूर्ण

	/*
	 * Quickly check the मुक्तmap inक्रमmation.  Attribute data has to be
	 * aligned to 4-byte boundaries, and likewise क्रम the मुक्त space.
	 *
	 * Note that क्रम 64k block size fileप्रणालीs, the मुक्तmap entries cannot
	 * overflow as they are only be16 fields. However, when checking end
	 * poपूर्णांकer of the मुक्तmap, we have to be careful to detect overflows and
	 * so use uपूर्णांक32_t क्रम those checks.
	 */
	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		अगर (ichdr.मुक्तmap[i].base > mp->m_attr_geo->blksize)
			वापस __this_address;
		अगर (ichdr.मुक्तmap[i].base & 0x3)
			वापस __this_address;
		अगर (ichdr.मुक्तmap[i].size > mp->m_attr_geo->blksize)
			वापस __this_address;
		अगर (ichdr.मुक्तmap[i].size & 0x3)
			वापस __this_address;

		/* be care of 16 bit overflows here */
		end = (uपूर्णांक32_t)ichdr.मुक्तmap[i].base + ichdr.मुक्तmap[i].size;
		अगर (end < ichdr.मुक्तmap[i].base)
			वापस __this_address;
		अगर (end > mp->m_attr_geo->blksize)
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_attr3_leaf_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_attr3_leaf_hdr *hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_attr3_leaf_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->info.lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_ATTR3_LEAF_CRC_OFF);
पूर्ण

/*
 * leaf/node क्रमmat detection on trees is sketchy, so a node पढ़ो can be करोne on
 * leaf level blocks when detection identअगरies the tree as a node क्रमmat tree
 * incorrectly. In this हाल, we need to swap the verअगरier to match the correct
 * क्रमmat of the block being पढ़ो.
 */
अटल व्योम
xfs_attr3_leaf_पढ़ो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	     !xfs_buf_verअगरy_cksum(bp, XFS_ATTR3_LEAF_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_attr3_leaf_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_attr3_leaf_buf_ops = अणु
	.name = "xfs_attr3_leaf",
	.magic16 = अणु cpu_to_be16(XFS_ATTR_LEAF_MAGIC),
		     cpu_to_be16(XFS_ATTR3_LEAF_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_attr3_leaf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_attr3_leaf_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_attr3_leaf_verअगरy,
पूर्ण;

पूर्णांक
xfs_attr3_leaf_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	काष्ठा xfs_buf		**bpp)
अणु
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, bno, 0, bpp, XFS_ATTR_FORK,
			&xfs_attr3_leaf_buf_ops);
	अगर (!err && tp && *bpp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_ATTR_LEAF_BUF);
	वापस err;
पूर्ण

/*========================================================================
 * Namespace helper routines
 *========================================================================*/

अटल bool
xfs_attr_match(
	काष्ठा xfs_da_args	*args,
	uपूर्णांक8_t			namelen,
	अचिन्हित अक्षर		*name,
	पूर्णांक			flags)
अणु
	अगर (args->namelen != namelen)
		वापस false;
	अगर (स_भेद(args->name, name, namelen) != 0)
		वापस false;
	/*
	 * If we are looking क्रम incomplete entries, show only those, अन्यथा only
	 * show complete entries.
	 */
	अगर (args->attr_filter !=
	    (flags & (XFS_ATTR_NSP_ONDISK_MASK | XFS_ATTR_INCOMPLETE)))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक
xfs_attr_copy_value(
	काष्ठा xfs_da_args	*args,
	अचिन्हित अक्षर		*value,
	पूर्णांक			valuelen)
अणु
	/*
	 * No copy अगर all we have to करो is get the length
	 */
	अगर (!args->valuelen) अणु
		args->valuelen = valuelen;
		वापस 0;
	पूर्ण

	/*
	 * No copy अगर the length of the existing buffer is too small
	 */
	अगर (args->valuelen < valuelen) अणु
		args->valuelen = valuelen;
		वापस -दुस्फल;
	पूर्ण

	अगर (!args->value) अणु
		args->value = kmem_alloc_large(valuelen, KM_NOLOCKDEP);
		अगर (!args->value)
			वापस -ENOMEM;
	पूर्ण
	args->valuelen = valuelen;

	/* remote block xattr requires IO क्रम copy-in */
	अगर (args->rmtblkno)
		वापस xfs_attr_rmtval_get(args);

	/*
	 * This is to prevent a GCC warning because the remote xattr हाल
	 * करोesn't have a value to pass in. In that हाल, we never reach here,
	 * but GCC can't work that out and so throws a "passing शून्य to
	 * स_नकल" warning.
	 */
	अगर (!value)
		वापस -EINVAL;
	स_नकल(args->value, value, valuelen);
	वापस 0;
पूर्ण

/*========================================================================
 * External routines when attribute विभाजन size < XFS_LITINO(mp).
 *========================================================================*/

/*
 * Query whether the total requested number of attr विभाजन bytes of extended
 * attribute space will be able to fit अंतरभूत.
 *
 * Returns zero अगर not, अन्यथा the i_विभाजनoff विभाजन offset to be used in the
 * literal area क्रम attribute data once the new bytes have been added.
 *
 * i_विभाजनoff must be 8 byte aligned, hence is stored as a >>3 value;
 * special हाल क्रम dev/uuid inodes, they have fixed size data विभाजनs.
 */
पूर्णांक
xfs_attr_लघुक्रमm_bytesfit(
	काष्ठा xfs_inode	*dp,
	पूर्णांक			bytes)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक64_t			dsize;
	पूर्णांक			minविभाजनoff;
	पूर्णांक			maxविभाजनoff;
	पूर्णांक			offset;

	/*
	 * Check अगर the new size could fit at all first:
	 */
	अगर (bytes > XFS_LITINO(mp))
		वापस 0;

	/* rounded करोwn */
	offset = (XFS_LITINO(mp) - bytes) >> 3;

	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_DEV) अणु
		minविभाजनoff = roundup(माप(xfs_dev_t), 8) >> 3;
		वापस (offset >= minविभाजनoff) ? minविभाजनoff : 0;
	पूर्ण

	/*
	 * If the requested numbers of bytes is smaller or equal to the
	 * current attribute विभाजन size we can always proceed.
	 *
	 * Note that अगर_bytes in the data विभाजन might actually be larger than
	 * the current data विभाजन size is due to delalloc extents. In that
	 * हाल either the extent count will go करोwn when they are converted
	 * to real extents, or the delalloc conversion will take care of the
	 * literal area rebalancing.
	 */
	अगर (bytes <= XFS_IFORK_ASIZE(dp))
		वापस dp->i_विभाजनoff;

	/*
	 * For attr2 we can try to move the विभाजनoff अगर there is space in the
	 * literal area, but क्रम the old क्रमmat we are करोne अगर there is no
	 * space in the fixed attribute विभाजन.
	 */
	अगर (!(mp->m_flags & XFS_MOUNT_ATTR2))
		वापस 0;

	dsize = dp->i_df.अगर_bytes;

	चयन (dp->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		/*
		 * If there is no attr विभाजन and the data विभाजन is extents, 
		 * determine अगर creating the शेष attr विभाजन will result
		 * in the extents क्रमm migrating to btree. If so, the
		 * minimum offset only needs to be the space required क्रम
		 * the btree root.
		 */
		अगर (!dp->i_विभाजनoff && dp->i_df.अगर_bytes >
		    xfs_शेष_attroffset(dp))
			dsize = XFS_BMDR_SPACE_CALC(MINDBTPTRS);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		/*
		 * If we have a data btree then keep विभाजनoff अगर we have one,
		 * otherwise we are adding a new attr, so then we set
		 * minविभाजनoff to where the btree root can finish so we have
		 * plenty of room क्रम attrs
		 */
		अगर (dp->i_विभाजनoff) अणु
			अगर (offset < dp->i_विभाजनoff)
				वापस 0;
			वापस dp->i_विभाजनoff;
		पूर्ण
		dsize = XFS_BMAP_BROOT_SPACE(mp, dp->i_df.अगर_broot);
		अवरोध;
	पूर्ण

	/*
	 * A data विभाजन btree root must have space क्रम at least
	 * MINDBTPTRS key/ptr pairs अगर the data विभाजन is small or empty.
	 */
	minविभाजनoff = max_t(पूर्णांक64_t, dsize, XFS_BMDR_SPACE_CALC(MINDBTPTRS));
	minविभाजनoff = roundup(minविभाजनoff, 8) >> 3;

	/* attr विभाजन btree root can have at least this many key/ptr pairs */
	maxविभाजनoff = XFS_LITINO(mp) - XFS_BMDR_SPACE_CALC(MINABTPTRS);
	maxविभाजनoff = maxविभाजनoff >> 3;	/* rounded करोwn */

	अगर (offset >= maxविभाजनoff)
		वापस maxविभाजनoff;
	अगर (offset >= minविभाजनoff)
		वापस offset;
	वापस 0;
पूर्ण

/*
 * Switch on the ATTR2 superblock bit (implies also FEATURES2)
 */
STATIC व्योम
xfs_sbversion_add_attr2(xfs_mount_t *mp, xfs_trans_t *tp)
अणु
	अगर ((mp->m_flags & XFS_MOUNT_ATTR2) &&
	    !(xfs_sb_version_hasattr2(&mp->m_sb))) अणु
		spin_lock(&mp->m_sb_lock);
		अगर (!xfs_sb_version_hasattr2(&mp->m_sb)) अणु
			xfs_sb_version_addattr2(&mp->m_sb);
			spin_unlock(&mp->m_sb_lock);
			xfs_log_sb(tp);
		पूर्ण अन्यथा
			spin_unlock(&mp->m_sb_lock);
	पूर्ण
पूर्ण

/*
 * Create the initial contents of a लघुक्रमm attribute list.
 */
व्योम
xfs_attr_लघुक्रमm_create(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_अगरork	*अगरp = dp->i_afp;
	काष्ठा xfs_attr_sf_hdr	*hdr;

	trace_xfs_attr_sf_create(args);

	ASSERT(अगरp->अगर_bytes == 0);
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS)
		अगरp->अगर_क्रमmat = XFS_DINODE_FMT_LOCAL;
	xfs_idata_पुनः_स्मृति(dp, माप(*hdr), XFS_ATTR_FORK);
	hdr = (काष्ठा xfs_attr_sf_hdr *)अगरp->अगर_u1.अगर_data;
	स_रखो(hdr, 0, माप(*hdr));
	hdr->totsize = cpu_to_be16(माप(*hdr));
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_ADATA);
पूर्ण

/*
 * Return -EEXIST अगर attr is found, or -ENOATTR अगर not
 * args:  args containing attribute name and namelen
 * sfep:  If not null, poपूर्णांकer will be set to the last attr entry found on
	  -EEXIST.  On -ENOATTR poपूर्णांकer is left at the last entry in the list
 * basep: If not null, poपूर्णांकer is set to the byte offset of the entry in the
 *	  list on -EEXIST.  On -ENOATTR, poपूर्णांकer is left at the byte offset of
 *	  the last entry in the list
 */
पूर्णांक
xfs_attr_sf_findname(
	काष्ठा xfs_da_args	 *args,
	काष्ठा xfs_attr_sf_entry **sfep,
	अचिन्हित पूर्णांक		 *basep)
अणु
	काष्ठा xfs_attr_लघुक्रमm *sf;
	काष्ठा xfs_attr_sf_entry *sfe;
	अचिन्हित पूर्णांक		base = माप(काष्ठा xfs_attr_sf_hdr);
	पूर्णांक			size = 0;
	पूर्णांक			end;
	पूर्णांक			i;

	sf = (काष्ठा xfs_attr_लघुक्रमm *)args->dp->i_afp->अगर_u1.अगर_data;
	sfe = &sf->list[0];
	end = sf->hdr.count;
	क्रम (i = 0; i < end; sfe = xfs_attr_sf_nextentry(sfe),
			     base += size, i++) अणु
		size = xfs_attr_sf_entsize(sfe);
		अगर (!xfs_attr_match(args, sfe->namelen, sfe->nameval,
				    sfe->flags))
			जारी;
		अवरोध;
	पूर्ण

	अगर (sfep != शून्य)
		*sfep = sfe;

	अगर (basep != शून्य)
		*basep = base;

	अगर (i == end)
		वापस -ENOATTR;
	वापस -EEXIST;
पूर्ण

/*
 * Add a name/value pair to the लघुक्रमm attribute list.
 * Overflow from the inode has alपढ़ोy been checked क्रम.
 */
व्योम
xfs_attr_लघुक्रमm_add(
	काष्ठा xfs_da_args		*args,
	पूर्णांक				विभाजनoff)
अणु
	काष्ठा xfs_attr_लघुक्रमm	*sf;
	काष्ठा xfs_attr_sf_entry	*sfe;
	पूर्णांक				offset, size;
	काष्ठा xfs_mount		*mp;
	काष्ठा xfs_inode		*dp;
	काष्ठा xfs_अगरork		*अगरp;

	trace_xfs_attr_sf_add(args);

	dp = args->dp;
	mp = dp->i_mount;
	dp->i_विभाजनoff = विभाजनoff;

	अगरp = dp->i_afp;
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)अगरp->अगर_u1.अगर_data;
	अगर (xfs_attr_sf_findname(args, &sfe, शून्य) == -EEXIST)
		ASSERT(0);

	offset = (अक्षर *)sfe - (अक्षर *)sf;
	size = xfs_attr_sf_entsize_byname(args->namelen, args->valuelen);
	xfs_idata_पुनः_स्मृति(dp, size, XFS_ATTR_FORK);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)अगरp->अगर_u1.अगर_data;
	sfe = (काष्ठा xfs_attr_sf_entry *)((अक्षर *)sf + offset);

	sfe->namelen = args->namelen;
	sfe->valuelen = args->valuelen;
	sfe->flags = args->attr_filter;
	स_नकल(sfe->nameval, args->name, args->namelen);
	स_नकल(&sfe->nameval[args->namelen], args->value, args->valuelen);
	sf->hdr.count++;
	be16_add_cpu(&sf->hdr.totsize, size);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_ADATA);

	xfs_sbversion_add_attr2(mp, args->trans);
पूर्ण

/*
 * After the last attribute is हटाओd revert to original inode क्रमmat,
 * making all literal area available to the data विभाजन once more.
 */
व्योम
xfs_attr_विभाजन_हटाओ(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_trans	*tp)
अणु
	ASSERT(ip->i_afp->अगर_nextents == 0);

	xfs_idestroy_विभाजन(ip->i_afp);
	kmem_cache_मुक्त(xfs_अगरork_zone, ip->i_afp);
	ip->i_afp = शून्य;
	ip->i_विभाजनoff = 0;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
पूर्ण

/*
 * Remove an attribute from the लघुक्रमm attribute list काष्ठाure.
 */
पूर्णांक
xfs_attr_लघुक्रमm_हटाओ(
	काष्ठा xfs_da_args		*args)
अणु
	काष्ठा xfs_attr_लघुक्रमm	*sf;
	काष्ठा xfs_attr_sf_entry	*sfe;
	पूर्णांक				size = 0, end, totsize;
	अचिन्हित पूर्णांक			base;
	काष्ठा xfs_mount		*mp;
	काष्ठा xfs_inode		*dp;
	पूर्णांक				error;

	trace_xfs_attr_sf_हटाओ(args);

	dp = args->dp;
	mp = dp->i_mount;
	sf = (काष्ठा xfs_attr_लघुक्रमm *)dp->i_afp->अगर_u1.अगर_data;

	error = xfs_attr_sf_findname(args, &sfe, &base);
	अगर (error != -EEXIST)
		वापस error;
	size = xfs_attr_sf_entsize(sfe);

	/*
	 * Fix up the attribute विभाजन data, covering the hole
	 */
	end = base + size;
	totsize = be16_to_cpu(sf->hdr.totsize);
	अगर (end != totsize)
		स_हटाओ(&((अक्षर *)sf)[base], &((अक्षर *)sf)[end], totsize - end);
	sf->hdr.count--;
	be16_add_cpu(&sf->hdr.totsize, -size);

	/*
	 * Fix up the start offset of the attribute विभाजन
	 */
	totsize -= size;
	अगर (totsize == माप(xfs_attr_sf_hdr_t) &&
	    (mp->m_flags & XFS_MOUNT_ATTR2) &&
	    (dp->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE) &&
	    !(args->op_flags & XFS_DA_OP_ADDNAME)) अणु
		xfs_attr_विभाजन_हटाओ(dp, args->trans);
	पूर्ण अन्यथा अणु
		xfs_idata_पुनः_स्मृति(dp, -size, XFS_ATTR_FORK);
		dp->i_विभाजनoff = xfs_attr_लघुक्रमm_bytesfit(dp, totsize);
		ASSERT(dp->i_विभाजनoff);
		ASSERT(totsize > माप(xfs_attr_sf_hdr_t) ||
				(args->op_flags & XFS_DA_OP_ADDNAME) ||
				!(mp->m_flags & XFS_MOUNT_ATTR2) ||
				dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_BTREE);
		xfs_trans_log_inode(args->trans, dp,
					XFS_ILOG_CORE | XFS_ILOG_ADATA);
	पूर्ण

	xfs_sbversion_add_attr2(mp, args->trans);

	वापस 0;
पूर्ण

/*
 * Look up a name in a लघुक्रमm attribute list काष्ठाure.
 */
/*ARGSUSED*/
पूर्णांक
xfs_attr_लघुक्रमm_lookup(xfs_da_args_t *args)
अणु
	काष्ठा xfs_attr_लघुक्रमm *sf;
	काष्ठा xfs_attr_sf_entry *sfe;
	पूर्णांक i;
	काष्ठा xfs_अगरork *अगरp;

	trace_xfs_attr_sf_lookup(args);

	अगरp = args->dp->i_afp;
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)अगरp->अगर_u1.अगर_data;
	sfe = &sf->list[0];
	क्रम (i = 0; i < sf->hdr.count;
				sfe = xfs_attr_sf_nextentry(sfe), i++) अणु
		अगर (xfs_attr_match(args, sfe->namelen, sfe->nameval,
				sfe->flags))
			वापस -EEXIST;
	पूर्ण
	वापस -ENOATTR;
पूर्ण

/*
 * Retrieve the attribute value and length.
 *
 * If args->valuelen is zero, only the length needs to be वापसed.  Unlike a
 * lookup, we only वापस an error अगर the attribute करोes not exist or we can't
 * retrieve the value.
 */
पूर्णांक
xfs_attr_लघुक्रमm_getvalue(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_लघुक्रमm *sf;
	काष्ठा xfs_attr_sf_entry *sfe;
	पूर्णांक			i;

	ASSERT(args->dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)args->dp->i_afp->अगर_u1.अगर_data;
	sfe = &sf->list[0];
	क्रम (i = 0; i < sf->hdr.count;
				sfe = xfs_attr_sf_nextentry(sfe), i++) अणु
		अगर (xfs_attr_match(args, sfe->namelen, sfe->nameval,
				sfe->flags))
			वापस xfs_attr_copy_value(args,
				&sfe->nameval[args->namelen], sfe->valuelen);
	पूर्ण
	वापस -ENOATTR;
पूर्ण

/*
 * Convert from using the लघुक्रमm to the leaf.  On success, वापस the
 * buffer so that we can keep it locked until we're totally करोne with it.
 */
पूर्णांक
xfs_attr_लघुक्रमm_to_leaf(
	काष्ठा xfs_da_args		*args,
	काष्ठा xfs_buf			**leaf_bp)
अणु
	काष्ठा xfs_inode		*dp;
	काष्ठा xfs_attr_लघुक्रमm	*sf;
	काष्ठा xfs_attr_sf_entry	*sfe;
	काष्ठा xfs_da_args		nargs;
	अक्षर				*पंचांगpbuffer;
	पूर्णांक				error, i, size;
	xfs_dablk_t			blkno;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_अगरork		*अगरp;

	trace_xfs_attr_sf_to_leaf(args);

	dp = args->dp;
	अगरp = dp->i_afp;
	sf = (काष्ठा xfs_attr_लघुक्रमm *)अगरp->अगर_u1.अगर_data;
	size = be16_to_cpu(sf->hdr.totsize);
	पंचांगpbuffer = kmem_alloc(size, 0);
	ASSERT(पंचांगpbuffer != शून्य);
	स_नकल(पंचांगpbuffer, अगरp->अगर_u1.अगर_data, size);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)पंचांगpbuffer;

	xfs_idata_पुनः_स्मृति(dp, -size, XFS_ATTR_FORK);
	xfs_bmap_local_to_extents_empty(args->trans, dp, XFS_ATTR_FORK);

	bp = शून्य;
	error = xfs_da_grow_inode(args, &blkno);
	अगर (error)
		जाओ out;

	ASSERT(blkno == 0);
	error = xfs_attr3_leaf_create(args, blkno, &bp);
	अगर (error)
		जाओ out;

	स_रखो((अक्षर *)&nargs, 0, माप(nargs));
	nargs.dp = dp;
	nargs.geo = args->geo;
	nargs.total = args->total;
	nargs.whichविभाजन = XFS_ATTR_FORK;
	nargs.trans = args->trans;
	nargs.op_flags = XFS_DA_OP_OKNOENT;

	sfe = &sf->list[0];
	क्रम (i = 0; i < sf->hdr.count; i++) अणु
		nargs.name = sfe->nameval;
		nargs.namelen = sfe->namelen;
		nargs.value = &sfe->nameval[nargs.namelen];
		nargs.valuelen = sfe->valuelen;
		nargs.hashval = xfs_da_hashname(sfe->nameval,
						sfe->namelen);
		nargs.attr_filter = sfe->flags & XFS_ATTR_NSP_ONDISK_MASK;
		error = xfs_attr3_leaf_lookup_पूर्णांक(bp, &nargs); /* set a->index */
		ASSERT(error == -ENOATTR);
		error = xfs_attr3_leaf_add(bp, &nargs);
		ASSERT(error != -ENOSPC);
		अगर (error)
			जाओ out;
		sfe = xfs_attr_sf_nextentry(sfe);
	पूर्ण
	error = 0;
	*leaf_bp = bp;
out:
	kmem_मुक्त(पंचांगpbuffer);
	वापस error;
पूर्ण

/*
 * Check a leaf attribute block to see अगर all the entries would fit पूर्णांकo
 * a लघुक्रमm attribute list.
 */
पूर्णांक
xfs_attr_लघुक्रमm_allfit(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_inode	*dp)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr_leaf_entry *entry;
	xfs_attr_leaf_name_local_t *name_loc;
	काष्ठा xfs_attr3_icleaf_hdr leafhdr;
	पूर्णांक			bytes;
	पूर्णांक			i;
	काष्ठा xfs_mount	*mp = bp->b_mount;

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &leafhdr, leaf);
	entry = xfs_attr3_leaf_entryp(leaf);

	bytes = माप(काष्ठा xfs_attr_sf_hdr);
	क्रम (i = 0; i < leafhdr.count; entry++, i++) अणु
		अगर (entry->flags & XFS_ATTR_INCOMPLETE)
			जारी;		/* करोn't copy partial entries */
		अगर (!(entry->flags & XFS_ATTR_LOCAL))
			वापस 0;
		name_loc = xfs_attr3_leaf_name_local(leaf, i);
		अगर (name_loc->namelen >= XFS_ATTR_SF_ENTSIZE_MAX)
			वापस 0;
		अगर (be16_to_cpu(name_loc->valuelen) >= XFS_ATTR_SF_ENTSIZE_MAX)
			वापस 0;
		bytes += xfs_attr_sf_entsize_byname(name_loc->namelen,
					be16_to_cpu(name_loc->valuelen));
	पूर्ण
	अगर ((dp->i_mount->m_flags & XFS_MOUNT_ATTR2) &&
	    (dp->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE) &&
	    (bytes == माप(काष्ठा xfs_attr_sf_hdr)))
		वापस -1;
	वापस xfs_attr_लघुक्रमm_bytesfit(dp, bytes);
पूर्ण

/* Verअगरy the consistency of an अंतरभूत attribute विभाजन. */
xfs_failaddr_t
xfs_attr_लघुक्रमm_verअगरy(
	काष्ठा xfs_inode		*ip)
अणु
	काष्ठा xfs_attr_लघुक्रमm	*sfp;
	काष्ठा xfs_attr_sf_entry	*sfep;
	काष्ठा xfs_attr_sf_entry	*next_sfep;
	अक्षर				*endp;
	काष्ठा xfs_अगरork		*अगरp;
	पूर्णांक				i;
	पूर्णांक64_t				size;

	ASSERT(ip->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	अगरp = XFS_IFORK_PTR(ip, XFS_ATTR_FORK);
	sfp = (काष्ठा xfs_attr_लघुक्रमm *)अगरp->अगर_u1.अगर_data;
	size = अगरp->अगर_bytes;

	/*
	 * Give up अगर the attribute is way too लघु.
	 */
	अगर (size < माप(काष्ठा xfs_attr_sf_hdr))
		वापस __this_address;

	endp = (अक्षर *)sfp + size;

	/* Check all reported entries */
	sfep = &sfp->list[0];
	क्रम (i = 0; i < sfp->hdr.count; i++) अणु
		/*
		 * काष्ठा xfs_attr_sf_entry has a variable length.
		 * Check the fixed-offset parts of the काष्ठाure are
		 * within the data buffer.
		 * xfs_attr_sf_entry is defined with a 1-byte variable
		 * array at the end, so we must subtract that off.
		 */
		अगर (((अक्षर *)sfep + माप(*sfep)) >= endp)
			वापस __this_address;

		/* Don't allow names with known bad length. */
		अगर (sfep->namelen == 0)
			वापस __this_address;

		/*
		 * Check that the variable-length part of the काष्ठाure is
		 * within the data buffer.  The next entry starts after the
		 * name component, so nextentry is an acceptable test.
		 */
		next_sfep = xfs_attr_sf_nextentry(sfep);
		अगर ((अक्षर *)next_sfep > endp)
			वापस __this_address;

		/*
		 * Check क्रम unknown flags.  Short क्रमm करोesn't support
		 * the incomplete or local bits, so we can use the namespace
		 * mask here.
		 */
		अगर (sfep->flags & ~XFS_ATTR_NSP_ONDISK_MASK)
			वापस __this_address;

		/*
		 * Check क्रम invalid namespace combinations.  We only allow
		 * one namespace flag per xattr, so we can just count the
		 * bits (i.e. hweight) here.
		 */
		अगर (hweight8(sfep->flags & XFS_ATTR_NSP_ONDISK_MASK) > 1)
			वापस __this_address;

		sfep = next_sfep;
	पूर्ण
	अगर ((व्योम *)sfep != (व्योम *)endp)
		वापस __this_address;

	वापस शून्य;
पूर्ण

/*
 * Convert a leaf attribute list to लघुक्रमm attribute list
 */
पूर्णांक
xfs_attr3_leaf_to_लघुक्रमm(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da_args	*args,
	पूर्णांक			विभाजनoff)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_name_local *name_loc;
	काष्ठा xfs_da_args	nargs;
	काष्ठा xfs_inode	*dp = args->dp;
	अक्षर			*पंचांगpbuffer;
	पूर्णांक			error;
	पूर्णांक			i;

	trace_xfs_attr_leaf_to_sf(args);

	पंचांगpbuffer = kmem_alloc(args->geo->blksize, 0);
	अगर (!पंचांगpbuffer)
		वापस -ENOMEM;

	स_नकल(पंचांगpbuffer, bp->b_addr, args->geo->blksize);

	leaf = (xfs_attr_leafblock_t *)पंचांगpbuffer;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	entry = xfs_attr3_leaf_entryp(leaf);

	/* XXX (dgc): buffer is about to be marked stale - why zero it? */
	स_रखो(bp->b_addr, 0, args->geo->blksize);

	/*
	 * Clean out the prior contents of the attribute list.
	 */
	error = xfs_da_shrink_inode(args, 0, bp);
	अगर (error)
		जाओ out;

	अगर (विभाजनoff == -1) अणु
		ASSERT(dp->i_mount->m_flags & XFS_MOUNT_ATTR2);
		ASSERT(dp->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE);
		xfs_attr_विभाजन_हटाओ(dp, args->trans);
		जाओ out;
	पूर्ण

	xfs_attr_लघुक्रमm_create(args);

	/*
	 * Copy the attributes
	 */
	स_रखो((अक्षर *)&nargs, 0, माप(nargs));
	nargs.geo = args->geo;
	nargs.dp = dp;
	nargs.total = args->total;
	nargs.whichविभाजन = XFS_ATTR_FORK;
	nargs.trans = args->trans;
	nargs.op_flags = XFS_DA_OP_OKNOENT;

	क्रम (i = 0; i < ichdr.count; entry++, i++) अणु
		अगर (entry->flags & XFS_ATTR_INCOMPLETE)
			जारी;	/* करोn't copy partial entries */
		अगर (!entry->nameidx)
			जारी;
		ASSERT(entry->flags & XFS_ATTR_LOCAL);
		name_loc = xfs_attr3_leaf_name_local(leaf, i);
		nargs.name = name_loc->nameval;
		nargs.namelen = name_loc->namelen;
		nargs.value = &name_loc->nameval[nargs.namelen];
		nargs.valuelen = be16_to_cpu(name_loc->valuelen);
		nargs.hashval = be32_to_cpu(entry->hashval);
		nargs.attr_filter = entry->flags & XFS_ATTR_NSP_ONDISK_MASK;
		xfs_attr_लघुक्रमm_add(&nargs, विभाजनoff);
	पूर्ण
	error = 0;

out:
	kmem_मुक्त(पंचांगpbuffer);
	वापस error;
पूर्ण

/*
 * Convert from using a single leaf to a root node and a leaf.
 */
पूर्णांक
xfs_attr3_leaf_to_node(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr icleafhdr;
	काष्ठा xfs_attr_leaf_entry *entries;
	काष्ठा xfs_da3_icnode_hdr icnodehdr;
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp1 = शून्य;
	काष्ठा xfs_buf		*bp2 = शून्य;
	xfs_dablk_t		blkno;
	पूर्णांक			error;

	trace_xfs_attr_leaf_to_node(args);

	error = xfs_da_grow_inode(args, &blkno);
	अगर (error)
		जाओ out;
	error = xfs_attr3_leaf_पढ़ो(args->trans, dp, 0, &bp1);
	अगर (error)
		जाओ out;

	error = xfs_da_get_buf(args->trans, dp, blkno, &bp2, XFS_ATTR_FORK);
	अगर (error)
		जाओ out;

	/* copy leaf to new buffer, update identअगरiers */
	xfs_trans_buf_set_type(args->trans, bp2, XFS_BLFT_ATTR_LEAF_BUF);
	bp2->b_ops = bp1->b_ops;
	स_नकल(bp2->b_addr, bp1->b_addr, args->geo->blksize);
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_da3_blkinfo *hdr3 = bp2->b_addr;
		hdr3->blkno = cpu_to_be64(bp2->b_bn);
	पूर्ण
	xfs_trans_log_buf(args->trans, bp2, 0, args->geo->blksize - 1);

	/*
	 * Set up the new root node.
	 */
	error = xfs_da3_node_create(args, 0, 1, &bp1, XFS_ATTR_FORK);
	अगर (error)
		जाओ out;
	node = bp1->b_addr;
	xfs_da3_node_hdr_from_disk(mp, &icnodehdr, node);

	leaf = bp2->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &icleafhdr, leaf);
	entries = xfs_attr3_leaf_entryp(leaf);

	/* both on-disk, करोn't endian-flip twice */
	icnodehdr.btree[0].hashval = entries[icleafhdr.count - 1].hashval;
	icnodehdr.btree[0].beक्रमe = cpu_to_be32(blkno);
	icnodehdr.count = 1;
	xfs_da3_node_hdr_to_disk(dp->i_mount, node, &icnodehdr);
	xfs_trans_log_buf(args->trans, bp1, 0, args->geo->blksize - 1);
	error = 0;
out:
	वापस error;
पूर्ण

/*========================================================================
 * Routines used क्रम growing the Btree.
 *========================================================================*/

/*
 * Create the initial contents of a leaf attribute list
 * or a leaf in a node attribute list.
 */
STATIC पूर्णांक
xfs_attr3_leaf_create(
	काष्ठा xfs_da_args	*args,
	xfs_dablk_t		blkno,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	trace_xfs_attr_leaf_create(args);

	error = xfs_da_get_buf(args->trans, args->dp, blkno, &bp,
					    XFS_ATTR_FORK);
	अगर (error)
		वापस error;
	bp->b_ops = &xfs_attr3_leaf_buf_ops;
	xfs_trans_buf_set_type(args->trans, bp, XFS_BLFT_ATTR_LEAF_BUF);
	leaf = bp->b_addr;
	स_रखो(leaf, 0, args->geo->blksize);

	स_रखो(&ichdr, 0, माप(ichdr));
	ichdr.firstused = args->geo->blksize;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_da3_blkinfo *hdr3 = bp->b_addr;

		ichdr.magic = XFS_ATTR3_LEAF_MAGIC;

		hdr3->blkno = cpu_to_be64(bp->b_bn);
		hdr3->owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->uuid, &mp->m_sb.sb_meta_uuid);

		ichdr.मुक्तmap[0].base = माप(काष्ठा xfs_attr3_leaf_hdr);
	पूर्ण अन्यथा अणु
		ichdr.magic = XFS_ATTR_LEAF_MAGIC;
		ichdr.मुक्तmap[0].base = माप(काष्ठा xfs_attr_leaf_hdr);
	पूर्ण
	ichdr.मुक्तmap[0].size = ichdr.firstused - ichdr.मुक्तmap[0].base;

	xfs_attr3_leaf_hdr_to_disk(args->geo, leaf, &ichdr);
	xfs_trans_log_buf(args->trans, bp, 0, args->geo->blksize - 1);

	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Split the leaf node, rebalance, then add the new entry.
 */
पूर्णांक
xfs_attr3_leaf_split(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*oldblk,
	काष्ठा xfs_da_state_blk	*newblk)
अणु
	xfs_dablk_t blkno;
	पूर्णांक error;

	trace_xfs_attr_leaf_split(state->args);

	/*
	 * Allocate space क्रम a new leaf node.
	 */
	ASSERT(oldblk->magic == XFS_ATTR_LEAF_MAGIC);
	error = xfs_da_grow_inode(state->args, &blkno);
	अगर (error)
		वापस error;
	error = xfs_attr3_leaf_create(state->args, blkno, &newblk->bp);
	अगर (error)
		वापस error;
	newblk->blkno = blkno;
	newblk->magic = XFS_ATTR_LEAF_MAGIC;

	/*
	 * Rebalance the entries across the two leaves.
	 * NOTE: rebalance() currently depends on the 2nd block being empty.
	 */
	xfs_attr3_leaf_rebalance(state, oldblk, newblk);
	error = xfs_da3_blk_link(state, oldblk, newblk);
	अगर (error)
		वापस error;

	/*
	 * Save info on "old" attribute क्रम "atomic rename" ops, leaf_add()
	 * modअगरies the index/blkno/rmtblk/rmtblkcnt fields to show the
	 * "new" attrs info.  Will need the "old" info to हटाओ it later.
	 *
	 * Insert the "new" entry in the correct block.
	 */
	अगर (state->inleaf) अणु
		trace_xfs_attr_leaf_add_old(state->args);
		error = xfs_attr3_leaf_add(oldblk->bp, state->args);
	पूर्ण अन्यथा अणु
		trace_xfs_attr_leaf_add_new(state->args);
		error = xfs_attr3_leaf_add(newblk->bp, state->args);
	पूर्ण

	/*
	 * Update last hashval in each block since we added the name.
	 */
	oldblk->hashval = xfs_attr_leaf_lasthash(oldblk->bp, शून्य);
	newblk->hashval = xfs_attr_leaf_lasthash(newblk->bp, शून्य);
	वापस error;
पूर्ण

/*
 * Add a name to the leaf attribute list काष्ठाure.
 */
पूर्णांक
xfs_attr3_leaf_add(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	पूर्णांक			tablesize;
	पूर्णांक			entsize;
	पूर्णांक			sum;
	पूर्णांक			पंचांगp;
	पूर्णांक			i;

	trace_xfs_attr_leaf_add(args);

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(args->index >= 0 && args->index <= ichdr.count);
	entsize = xfs_attr_leaf_newentsize(args, शून्य);

	/*
	 * Search through मुक्तmap क्रम first-fit on new name length.
	 * (may need to figure in size of entry काष्ठा too)
	 */
	tablesize = (ichdr.count + 1) * माप(xfs_attr_leaf_entry_t)
					+ xfs_attr3_leaf_hdr_size(leaf);
	क्रम (sum = 0, i = XFS_ATTR_LEAF_MAPSIZE - 1; i >= 0; i--) अणु
		अगर (tablesize > ichdr.firstused) अणु
			sum += ichdr.मुक्तmap[i].size;
			जारी;
		पूर्ण
		अगर (!ichdr.मुक्तmap[i].size)
			जारी;	/* no space in this map */
		पंचांगp = entsize;
		अगर (ichdr.मुक्तmap[i].base < ichdr.firstused)
			पंचांगp += माप(xfs_attr_leaf_entry_t);
		अगर (ichdr.मुक्तmap[i].size >= पंचांगp) अणु
			पंचांगp = xfs_attr3_leaf_add_work(bp, &ichdr, args, i);
			जाओ out_log_hdr;
		पूर्ण
		sum += ichdr.मुक्तmap[i].size;
	पूर्ण

	/*
	 * If there are no holes in the address space of the block,
	 * and we करोn't have enough मुक्तspace, then compaction will करो us
	 * no good and we should just give up.
	 */
	अगर (!ichdr.holes && sum < entsize)
		वापस -ENOSPC;

	/*
	 * Compact the entries to coalesce मुक्त space.
	 * This may change the hdr->count via dropping INCOMPLETE entries.
	 */
	xfs_attr3_leaf_compact(args, &ichdr, bp);

	/*
	 * After compaction, the block is guaranteed to have only one
	 * मुक्त region, in मुक्तmap[0].  If it is not big enough, give up.
	 */
	अगर (ichdr.मुक्तmap[0].size < (entsize + माप(xfs_attr_leaf_entry_t))) अणु
		पंचांगp = -ENOSPC;
		जाओ out_log_hdr;
	पूर्ण

	पंचांगp = xfs_attr3_leaf_add_work(bp, &ichdr, args, 0);

out_log_hdr:
	xfs_attr3_leaf_hdr_to_disk(args->geo, leaf, &ichdr);
	xfs_trans_log_buf(args->trans, bp,
		XFS_DA_LOGRANGE(leaf, &leaf->hdr,
				xfs_attr3_leaf_hdr_size(leaf)));
	वापस पंचांगp;
पूर्ण

/*
 * Add a name to a leaf attribute list काष्ठाure.
 */
STATIC पूर्णांक
xfs_attr3_leaf_add_work(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_attr3_icleaf_hdr *ichdr,
	काष्ठा xfs_da_args	*args,
	पूर्णांक			mapindex)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_name_local *name_loc;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	काष्ठा xfs_mount	*mp;
	पूर्णांक			पंचांगp;
	पूर्णांक			i;

	trace_xfs_attr_leaf_add_work(args);

	leaf = bp->b_addr;
	ASSERT(mapindex >= 0 && mapindex < XFS_ATTR_LEAF_MAPSIZE);
	ASSERT(args->index >= 0 && args->index <= ichdr->count);

	/*
	 * Force खोलो some space in the entry array and fill it in.
	 */
	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];
	अगर (args->index < ichdr->count) अणु
		पंचांगp  = ichdr->count - args->index;
		पंचांगp *= माप(xfs_attr_leaf_entry_t);
		स_हटाओ(entry + 1, entry, पंचांगp);
		xfs_trans_log_buf(args->trans, bp,
		    XFS_DA_LOGRANGE(leaf, entry, पंचांगp + माप(*entry)));
	पूर्ण
	ichdr->count++;

	/*
	 * Allocate space क्रम the new string (at the end of the run).
	 */
	mp = args->trans->t_mountp;
	ASSERT(ichdr->मुक्तmap[mapindex].base < args->geo->blksize);
	ASSERT((ichdr->मुक्तmap[mapindex].base & 0x3) == 0);
	ASSERT(ichdr->मुक्तmap[mapindex].size >=
		xfs_attr_leaf_newentsize(args, शून्य));
	ASSERT(ichdr->मुक्तmap[mapindex].size < args->geo->blksize);
	ASSERT((ichdr->मुक्तmap[mapindex].size & 0x3) == 0);

	ichdr->मुक्तmap[mapindex].size -= xfs_attr_leaf_newentsize(args, &पंचांगp);

	entry->nameidx = cpu_to_be16(ichdr->मुक्तmap[mapindex].base +
				     ichdr->मुक्तmap[mapindex].size);
	entry->hashval = cpu_to_be32(args->hashval);
	entry->flags = args->attr_filter;
	अगर (पंचांगp)
		entry->flags |= XFS_ATTR_LOCAL;
	अगर (args->op_flags & XFS_DA_OP_RENAME) अणु
		entry->flags |= XFS_ATTR_INCOMPLETE;
		अगर ((args->blkno2 == args->blkno) &&
		    (args->index2 <= args->index)) अणु
			args->index2++;
		पूर्ण
	पूर्ण
	xfs_trans_log_buf(args->trans, bp,
			  XFS_DA_LOGRANGE(leaf, entry, माप(*entry)));
	ASSERT((args->index == 0) ||
	       (be32_to_cpu(entry->hashval) >= be32_to_cpu((entry-1)->hashval)));
	ASSERT((args->index == ichdr->count - 1) ||
	       (be32_to_cpu(entry->hashval) <= be32_to_cpu((entry+1)->hashval)));

	/*
	 * For "remote" attribute values, simply note that we need to
	 * allocate space क्रम the "remote" value.  We can't actually
	 * allocate the extents in this transaction, and we can't decide
	 * which blocks they should be as we might allocate more blocks
	 * as part of this transaction (a split operation क्रम example).
	 */
	अगर (entry->flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf, args->index);
		name_loc->namelen = args->namelen;
		name_loc->valuelen = cpu_to_be16(args->valuelen);
		स_नकल((अक्षर *)name_loc->nameval, args->name, args->namelen);
		स_नकल((अक्षर *)&name_loc->nameval[args->namelen], args->value,
				   be16_to_cpu(name_loc->valuelen));
	पूर्ण अन्यथा अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		name_rmt->namelen = args->namelen;
		स_नकल((अक्षर *)name_rmt->name, args->name, args->namelen);
		entry->flags |= XFS_ATTR_INCOMPLETE;
		/* just in हाल */
		name_rmt->valuelen = 0;
		name_rmt->valueblk = 0;
		args->rmtblkno = 1;
		args->rmtblkcnt = xfs_attr3_rmt_blocks(mp, args->valuelen);
		args->rmtvaluelen = args->valuelen;
	पूर्ण
	xfs_trans_log_buf(args->trans, bp,
	     XFS_DA_LOGRANGE(leaf, xfs_attr3_leaf_name(leaf, args->index),
				   xfs_attr_leaf_entsize(leaf, args->index)));

	/*
	 * Update the control info क्रम this leaf node
	 */
	अगर (be16_to_cpu(entry->nameidx) < ichdr->firstused)
		ichdr->firstused = be16_to_cpu(entry->nameidx);

	ASSERT(ichdr->firstused >= ichdr->count * माप(xfs_attr_leaf_entry_t)
					+ xfs_attr3_leaf_hdr_size(leaf));
	पंचांगp = (ichdr->count - 1) * माप(xfs_attr_leaf_entry_t)
					+ xfs_attr3_leaf_hdr_size(leaf);

	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		अगर (ichdr->मुक्तmap[i].base == पंचांगp) अणु
			ichdr->मुक्तmap[i].base += माप(xfs_attr_leaf_entry_t);
			ichdr->मुक्तmap[i].size -=
				min_t(uपूर्णांक16_t, ichdr->मुक्तmap[i].size,
						माप(xfs_attr_leaf_entry_t));
		पूर्ण
	पूर्ण
	ichdr->usedbytes += xfs_attr_leaf_entsize(leaf, args->index);
	वापस 0;
पूर्ण

/*
 * Garbage collect a leaf attribute list block by copying it to a new buffer.
 */
STATIC व्योम
xfs_attr3_leaf_compact(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_attr3_icleaf_hdr *ichdr_dst,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_attr_leafblock *leaf_src;
	काष्ठा xfs_attr_leafblock *leaf_dst;
	काष्ठा xfs_attr3_icleaf_hdr ichdr_src;
	काष्ठा xfs_trans	*trans = args->trans;
	अक्षर			*पंचांगpbuffer;

	trace_xfs_attr_leaf_compact(args);

	पंचांगpbuffer = kmem_alloc(args->geo->blksize, 0);
	स_नकल(पंचांगpbuffer, bp->b_addr, args->geo->blksize);
	स_रखो(bp->b_addr, 0, args->geo->blksize);
	leaf_src = (xfs_attr_leafblock_t *)पंचांगpbuffer;
	leaf_dst = bp->b_addr;

	/*
	 * Copy the on-disk header back पूर्णांकo the destination buffer to ensure
	 * all the inक्रमmation in the header that is not part of the incore
	 * header काष्ठाure is preserved.
	 */
	स_नकल(bp->b_addr, पंचांगpbuffer, xfs_attr3_leaf_hdr_size(leaf_src));

	/* Initialise the incore headers */
	ichdr_src = *ichdr_dst;	/* काष्ठा copy */
	ichdr_dst->firstused = args->geo->blksize;
	ichdr_dst->usedbytes = 0;
	ichdr_dst->count = 0;
	ichdr_dst->holes = 0;
	ichdr_dst->मुक्तmap[0].base = xfs_attr3_leaf_hdr_size(leaf_src);
	ichdr_dst->मुक्तmap[0].size = ichdr_dst->firstused -
						ichdr_dst->मुक्तmap[0].base;

	/* ग_लिखो the header back to initialise the underlying buffer */
	xfs_attr3_leaf_hdr_to_disk(args->geo, leaf_dst, ichdr_dst);

	/*
	 * Copy all entry's in the same (sorted) order,
	 * but allocate name/value pairs packed and in sequence.
	 */
	xfs_attr3_leaf_moveents(args, leaf_src, &ichdr_src, 0,
				leaf_dst, ichdr_dst, 0, ichdr_src.count);
	/*
	 * this logs the entire buffer, but the caller must ग_लिखो the header
	 * back to the buffer when it is finished modअगरying it.
	 */
	xfs_trans_log_buf(trans, bp, 0, args->geo->blksize - 1);

	kmem_मुक्त(पंचांगpbuffer);
पूर्ण

/*
 * Compare two leaf blocks "order".
 * Return 0 unless leaf2 should go beक्रमe leaf1.
 */
अटल पूर्णांक
xfs_attr3_leaf_order(
	काष्ठा xfs_buf	*leaf1_bp,
	काष्ठा xfs_attr3_icleaf_hdr *leaf1hdr,
	काष्ठा xfs_buf	*leaf2_bp,
	काष्ठा xfs_attr3_icleaf_hdr *leaf2hdr)
अणु
	काष्ठा xfs_attr_leaf_entry *entries1;
	काष्ठा xfs_attr_leaf_entry *entries2;

	entries1 = xfs_attr3_leaf_entryp(leaf1_bp->b_addr);
	entries2 = xfs_attr3_leaf_entryp(leaf2_bp->b_addr);
	अगर (leaf1hdr->count > 0 && leaf2hdr->count > 0 &&
	    ((be32_to_cpu(entries2[0].hashval) <
	      be32_to_cpu(entries1[0].hashval)) ||
	     (be32_to_cpu(entries2[leaf2hdr->count - 1].hashval) <
	      be32_to_cpu(entries1[leaf1hdr->count - 1].hashval)))) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
xfs_attr_leaf_order(
	काष्ठा xfs_buf	*leaf1_bp,
	काष्ठा xfs_buf	*leaf2_bp)
अणु
	काष्ठा xfs_attr3_icleaf_hdr ichdr1;
	काष्ठा xfs_attr3_icleaf_hdr ichdr2;
	काष्ठा xfs_mount *mp = leaf1_bp->b_mount;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr1, leaf1_bp->b_addr);
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr2, leaf2_bp->b_addr);
	वापस xfs_attr3_leaf_order(leaf1_bp, &ichdr1, leaf2_bp, &ichdr2);
पूर्ण

/*
 * Redistribute the attribute list entries between two leaf nodes,
 * taking पूर्णांकo account the size of the new entry.
 *
 * NOTE: अगर new block is empty, then it will get the upper half of the
 * old block.  At present, all (one) callers pass in an empty second block.
 *
 * This code adjusts the args->index/blkno and args->index2/blkno2 fields
 * to match what it is करोing in splitting the attribute leaf block.  Those
 * values are used in "atomic rename" operations on attributes.  Note that
 * the "new" and "old" values can end up in dअगरferent blocks.
 */
STATIC व्योम
xfs_attr3_leaf_rebalance(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*blk1,
	काष्ठा xfs_da_state_blk	*blk2)
अणु
	काष्ठा xfs_da_args	*args;
	काष्ठा xfs_attr_leafblock *leaf1;
	काष्ठा xfs_attr_leafblock *leaf2;
	काष्ठा xfs_attr3_icleaf_hdr ichdr1;
	काष्ठा xfs_attr3_icleaf_hdr ichdr2;
	काष्ठा xfs_attr_leaf_entry *entries1;
	काष्ठा xfs_attr_leaf_entry *entries2;
	पूर्णांक			count;
	पूर्णांक			totallen;
	पूर्णांक			max;
	पूर्णांक			space;
	पूर्णांक			swap;

	/*
	 * Set up environment.
	 */
	ASSERT(blk1->magic == XFS_ATTR_LEAF_MAGIC);
	ASSERT(blk2->magic == XFS_ATTR_LEAF_MAGIC);
	leaf1 = blk1->bp->b_addr;
	leaf2 = blk2->bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr1, leaf1);
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr2, leaf2);
	ASSERT(ichdr2.count == 0);
	args = state->args;

	trace_xfs_attr_leaf_rebalance(args);

	/*
	 * Check ordering of blocks, reverse अगर it makes things simpler.
	 *
	 * NOTE: Given that all (current) callers pass in an empty
	 * second block, this code should never set "swap".
	 */
	swap = 0;
	अगर (xfs_attr3_leaf_order(blk1->bp, &ichdr1, blk2->bp, &ichdr2)) अणु
		swap(blk1, blk2);

		/* swap काष्ठाures rather than reconverting them */
		swap(ichdr1, ichdr2);

		leaf1 = blk1->bp->b_addr;
		leaf2 = blk2->bp->b_addr;
		swap = 1;
	पूर्ण

	/*
	 * Examine entries until we reduce the असलolute dअगरference in
	 * byte usage between the two blocks to a minimum.  Then get
	 * the direction to copy and the number of elements to move.
	 *
	 * "inleaf" is true अगर the new entry should be inserted पूर्णांकo blk1.
	 * If "swap" is also true, then reverse the sense of "inleaf".
	 */
	state->inleaf = xfs_attr3_leaf_figure_balance(state, blk1, &ichdr1,
						      blk2, &ichdr2,
						      &count, &totallen);
	अगर (swap)
		state->inleaf = !state->inleaf;

	/*
	 * Move any entries required from leaf to leaf:
	 */
	अगर (count < ichdr1.count) अणु
		/*
		 * Figure the total bytes to be added to the destination leaf.
		 */
		/* number entries being moved */
		count = ichdr1.count - count;
		space  = ichdr1.usedbytes - totallen;
		space += count * माप(xfs_attr_leaf_entry_t);

		/*
		 * leaf2 is the destination, compact it अगर it looks tight.
		 */
		max  = ichdr2.firstused - xfs_attr3_leaf_hdr_size(leaf1);
		max -= ichdr2.count * माप(xfs_attr_leaf_entry_t);
		अगर (space > max)
			xfs_attr3_leaf_compact(args, &ichdr2, blk2->bp);

		/*
		 * Move high entries from leaf1 to low end of leaf2.
		 */
		xfs_attr3_leaf_moveents(args, leaf1, &ichdr1,
				ichdr1.count - count, leaf2, &ichdr2, 0, count);

	पूर्ण अन्यथा अगर (count > ichdr1.count) अणु
		/*
		 * I निश्चित that since all callers pass in an empty
		 * second buffer, this code should never execute.
		 */
		ASSERT(0);

		/*
		 * Figure the total bytes to be added to the destination leaf.
		 */
		/* number entries being moved */
		count -= ichdr1.count;
		space  = totallen - ichdr1.usedbytes;
		space += count * माप(xfs_attr_leaf_entry_t);

		/*
		 * leaf1 is the destination, compact it अगर it looks tight.
		 */
		max  = ichdr1.firstused - xfs_attr3_leaf_hdr_size(leaf1);
		max -= ichdr1.count * माप(xfs_attr_leaf_entry_t);
		अगर (space > max)
			xfs_attr3_leaf_compact(args, &ichdr1, blk1->bp);

		/*
		 * Move low entries from leaf2 to high end of leaf1.
		 */
		xfs_attr3_leaf_moveents(args, leaf2, &ichdr2, 0, leaf1, &ichdr1,
					ichdr1.count, count);
	पूर्ण

	xfs_attr3_leaf_hdr_to_disk(state->args->geo, leaf1, &ichdr1);
	xfs_attr3_leaf_hdr_to_disk(state->args->geo, leaf2, &ichdr2);
	xfs_trans_log_buf(args->trans, blk1->bp, 0, args->geo->blksize - 1);
	xfs_trans_log_buf(args->trans, blk2->bp, 0, args->geo->blksize - 1);

	/*
	 * Copy out last hashval in each block क्रम B-tree code.
	 */
	entries1 = xfs_attr3_leaf_entryp(leaf1);
	entries2 = xfs_attr3_leaf_entryp(leaf2);
	blk1->hashval = be32_to_cpu(entries1[ichdr1.count - 1].hashval);
	blk2->hashval = be32_to_cpu(entries2[ichdr2.count - 1].hashval);

	/*
	 * Adjust the expected index क्रम insertion.
	 * NOTE: this code depends on the (current) situation that the
	 * second block was originally empty.
	 *
	 * If the insertion poपूर्णांक moved to the 2nd block, we must adjust
	 * the index.  We must also track the entry just following the
	 * new entry क्रम use in an "atomic rename" operation, that entry
	 * is always the "old" entry and the "new" entry is what we are
	 * inserting.  The index/blkno fields refer to the "old" entry,
	 * जबतक the index2/blkno2 fields refer to the "new" entry.
	 */
	अगर (blk1->index > ichdr1.count) अणु
		ASSERT(state->inleaf == 0);
		blk2->index = blk1->index - ichdr1.count;
		args->index = args->index2 = blk2->index;
		args->blkno = args->blkno2 = blk2->blkno;
	पूर्ण अन्यथा अगर (blk1->index == ichdr1.count) अणु
		अगर (state->inleaf) अणु
			args->index = blk1->index;
			args->blkno = blk1->blkno;
			args->index2 = 0;
			args->blkno2 = blk2->blkno;
		पूर्ण अन्यथा अणु
			/*
			 * On a द्विगुन leaf split, the original attr location
			 * is alपढ़ोy stored in blkno2/index2, so करोn't
			 * overग_लिखो it overwise we corrupt the tree.
			 */
			blk2->index = blk1->index - ichdr1.count;
			args->index = blk2->index;
			args->blkno = blk2->blkno;
			अगर (!state->extravalid) अणु
				/*
				 * set the new attr location to match the old
				 * one and let the higher level split code
				 * decide where in the leaf to place it.
				 */
				args->index2 = blk2->index;
				args->blkno2 = blk2->blkno;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ASSERT(state->inleaf == 1);
		args->index = args->index2 = blk1->index;
		args->blkno = args->blkno2 = blk1->blkno;
	पूर्ण
पूर्ण

/*
 * Examine entries until we reduce the असलolute dअगरference in
 * byte usage between the two blocks to a minimum.
 * GROT: Is this really necessary?  With other than a 512 byte blocksize,
 * GROT: there will always be enough room in either block क्रम a new entry.
 * GROT: Do a द्विगुन-split क्रम this हाल?
 */
STATIC पूर्णांक
xfs_attr3_leaf_figure_balance(
	काष्ठा xfs_da_state		*state,
	काष्ठा xfs_da_state_blk		*blk1,
	काष्ठा xfs_attr3_icleaf_hdr	*ichdr1,
	काष्ठा xfs_da_state_blk		*blk2,
	काष्ठा xfs_attr3_icleaf_hdr	*ichdr2,
	पूर्णांक				*countarg,
	पूर्णांक				*usedbytesarg)
अणु
	काष्ठा xfs_attr_leafblock	*leaf1 = blk1->bp->b_addr;
	काष्ठा xfs_attr_leafblock	*leaf2 = blk2->bp->b_addr;
	काष्ठा xfs_attr_leaf_entry	*entry;
	पूर्णांक				count;
	पूर्णांक				max;
	पूर्णांक				index;
	पूर्णांक				totallen = 0;
	पूर्णांक				half;
	पूर्णांक				lastdelta;
	पूर्णांक				foundit = 0;
	पूर्णांक				पंचांगp;

	/*
	 * Examine entries until we reduce the असलolute dअगरference in
	 * byte usage between the two blocks to a minimum.
	 */
	max = ichdr1->count + ichdr2->count;
	half = (max + 1) * माप(*entry);
	half += ichdr1->usedbytes + ichdr2->usedbytes +
			xfs_attr_leaf_newentsize(state->args, शून्य);
	half /= 2;
	lastdelta = state->args->geo->blksize;
	entry = xfs_attr3_leaf_entryp(leaf1);
	क्रम (count = index = 0; count < max; entry++, index++, count++) अणु

#घोषणा XFS_ATTR_ABS(A)	(((A) < 0) ? -(A) : (A))
		/*
		 * The new entry is in the first block, account क्रम it.
		 */
		अगर (count == blk1->index) अणु
			पंचांगp = totallen + माप(*entry) +
				xfs_attr_leaf_newentsize(state->args, शून्य);
			अगर (XFS_ATTR_ABS(half - पंचांगp) > lastdelta)
				अवरोध;
			lastdelta = XFS_ATTR_ABS(half - पंचांगp);
			totallen = पंचांगp;
			foundit = 1;
		पूर्ण

		/*
		 * Wrap around पूर्णांकo the second block अगर necessary.
		 */
		अगर (count == ichdr1->count) अणु
			leaf1 = leaf2;
			entry = xfs_attr3_leaf_entryp(leaf1);
			index = 0;
		पूर्ण

		/*
		 * Figure out अगर next leaf entry would be too much.
		 */
		पंचांगp = totallen + माप(*entry) + xfs_attr_leaf_entsize(leaf1,
									index);
		अगर (XFS_ATTR_ABS(half - पंचांगp) > lastdelta)
			अवरोध;
		lastdelta = XFS_ATTR_ABS(half - पंचांगp);
		totallen = पंचांगp;
#अघोषित XFS_ATTR_ABS
	पूर्ण

	/*
	 * Calculate the number of usedbytes that will end up in lower block.
	 * If new entry not in lower block, fix up the count.
	 */
	totallen -= count * माप(*entry);
	अगर (foundit) अणु
		totallen -= माप(*entry) +
				xfs_attr_leaf_newentsize(state->args, शून्य);
	पूर्ण

	*countarg = count;
	*usedbytesarg = totallen;
	वापस foundit;
पूर्ण

/*========================================================================
 * Routines used क्रम shrinking the Btree.
 *========================================================================*/

/*
 * Check a leaf block and its neighbors to see अगर the block should be
 * collapsed पूर्णांकo one or the other neighbor.  Always keep the block
 * with the smaller block number.
 * If the current block is over 50% full, करोn't try to join it, वापस 0.
 * If the block is empty, fill in the state काष्ठाure and वापस 2.
 * If it can be collapsed, fill in the state काष्ठाure and वापस 1.
 * If nothing can be करोne, वापस 0.
 *
 * GROT: allow क्रम INCOMPLETE entries in calculation.
 */
पूर्णांक
xfs_attr3_leaf_toosmall(
	काष्ठा xfs_da_state	*state,
	पूर्णांक			*action)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_buf		*bp;
	xfs_dablk_t		blkno;
	पूर्णांक			bytes;
	पूर्णांक			क्रमward;
	पूर्णांक			error;
	पूर्णांक			retval;
	पूर्णांक			i;

	trace_xfs_attr_leaf_toosmall(state->args);

	/*
	 * Check क्रम the degenerate हाल of the block being over 50% full.
	 * If so, it's not worth even looking to see अगर we might be able
	 * to coalesce with a sibling.
	 */
	blk = &state->path.blk[ state->path.active-1 ];
	leaf = blk->bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr, leaf);
	bytes = xfs_attr3_leaf_hdr_size(leaf) +
		ichdr.count * माप(xfs_attr_leaf_entry_t) +
		ichdr.usedbytes;
	अगर (bytes > (state->args->geo->blksize >> 1)) अणु
		*action = 0;	/* blk over 50%, करोn't try to join */
		वापस 0;
	पूर्ण

	/*
	 * Check क्रम the degenerate हाल of the block being empty.
	 * If the block is empty, we'll simply delete it, no need to
	 * coalesce it with a sibling block.  We choose (arbitrarily)
	 * to merge with the क्रमward block unless it is शून्य.
	 */
	अगर (ichdr.count == 0) अणु
		/*
		 * Make altpath poपूर्णांक to the block we want to keep and
		 * path poपूर्णांक to the block we want to drop (this one).
		 */
		क्रमward = (ichdr.क्रमw != 0);
		स_नकल(&state->altpath, &state->path, माप(state->path));
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward,
						 0, &retval);
		अगर (error)
			वापस error;
		अगर (retval) अणु
			*action = 0;
		पूर्ण अन्यथा अणु
			*action = 2;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Examine each sibling block to see अगर we can coalesce with
	 * at least 25% मुक्त space to spare.  We need to figure out
	 * whether to merge with the क्रमward or the backward block.
	 * We prefer coalescing with the lower numbered sibling so as
	 * to shrink an attribute list over समय.
	 */
	/* start with smaller blk num */
	क्रमward = ichdr.क्रमw < ichdr.back;
	क्रम (i = 0; i < 2; क्रमward = !क्रमward, i++) अणु
		काष्ठा xfs_attr3_icleaf_hdr ichdr2;
		अगर (क्रमward)
			blkno = ichdr.क्रमw;
		अन्यथा
			blkno = ichdr.back;
		अगर (blkno == 0)
			जारी;
		error = xfs_attr3_leaf_पढ़ो(state->args->trans, state->args->dp,
					blkno, &bp);
		अगर (error)
			वापस error;

		xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr2, bp->b_addr);

		bytes = state->args->geo->blksize -
			(state->args->geo->blksize >> 2) -
			ichdr.usedbytes - ichdr2.usedbytes -
			((ichdr.count + ichdr2.count) *
					माप(xfs_attr_leaf_entry_t)) -
			xfs_attr3_leaf_hdr_size(leaf);

		xfs_trans_brअन्यथा(state->args->trans, bp);
		अगर (bytes >= 0)
			अवरोध;	/* fits with at least 25% to spare */
	पूर्ण
	अगर (i >= 2) अणु
		*action = 0;
		वापस 0;
	पूर्ण

	/*
	 * Make altpath poपूर्णांक to the block we want to keep (the lower
	 * numbered block) and path poपूर्णांक to the block we want to drop.
	 */
	स_नकल(&state->altpath, &state->path, माप(state->path));
	अगर (blkno < blk->blkno) अणु
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward,
						 0, &retval);
	पूर्ण अन्यथा अणु
		error = xfs_da3_path_shअगरt(state, &state->path, क्रमward,
						 0, &retval);
	पूर्ण
	अगर (error)
		वापस error;
	अगर (retval) अणु
		*action = 0;
	पूर्ण अन्यथा अणु
		*action = 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remove a name from the leaf attribute list काष्ठाure.
 *
 * Return 1 अगर leaf is less than 37% full, 0 अगर >= 37% full.
 * If two leaves are 37% full, when combined they will leave 25% मुक्त.
 */
पूर्णांक
xfs_attr3_leaf_हटाओ(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_attr_leaf_entry *entry;
	पूर्णांक			beक्रमe;
	पूर्णांक			after;
	पूर्णांक			smallest;
	पूर्णांक			entsize;
	पूर्णांक			tablesize;
	पूर्णांक			पंचांगp;
	पूर्णांक			i;

	trace_xfs_attr_leaf_हटाओ(args);

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);

	ASSERT(ichdr.count > 0 && ichdr.count < args->geo->blksize / 8);
	ASSERT(args->index >= 0 && args->index < ichdr.count);
	ASSERT(ichdr.firstused >= ichdr.count * माप(*entry) +
					xfs_attr3_leaf_hdr_size(leaf));

	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];

	ASSERT(be16_to_cpu(entry->nameidx) >= ichdr.firstused);
	ASSERT(be16_to_cpu(entry->nameidx) < args->geo->blksize);

	/*
	 * Scan through मुक्त region table:
	 *    check क्रम adjacency of मुक्त'd entry with an existing one,
	 *    find smallest मुक्त region in हाल we need to replace it,
	 *    adjust any map that borders the entry table,
	 */
	tablesize = ichdr.count * माप(xfs_attr_leaf_entry_t)
					+ xfs_attr3_leaf_hdr_size(leaf);
	पंचांगp = ichdr.मुक्तmap[0].size;
	beक्रमe = after = -1;
	smallest = XFS_ATTR_LEAF_MAPSIZE - 1;
	entsize = xfs_attr_leaf_entsize(leaf, args->index);
	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		ASSERT(ichdr.मुक्तmap[i].base < args->geo->blksize);
		ASSERT(ichdr.मुक्तmap[i].size < args->geo->blksize);
		अगर (ichdr.मुक्तmap[i].base == tablesize) अणु
			ichdr.मुक्तmap[i].base -= माप(xfs_attr_leaf_entry_t);
			ichdr.मुक्तmap[i].size += माप(xfs_attr_leaf_entry_t);
		पूर्ण

		अगर (ichdr.मुक्तmap[i].base + ichdr.मुक्तmap[i].size ==
				be16_to_cpu(entry->nameidx)) अणु
			beक्रमe = i;
		पूर्ण अन्यथा अगर (ichdr.मुक्तmap[i].base ==
				(be16_to_cpu(entry->nameidx) + entsize)) अणु
			after = i;
		पूर्ण अन्यथा अगर (ichdr.मुक्तmap[i].size < पंचांगp) अणु
			पंचांगp = ichdr.मुक्तmap[i].size;
			smallest = i;
		पूर्ण
	पूर्ण

	/*
	 * Coalesce adjacent मुक्तmap regions,
	 * or replace the smallest region.
	 */
	अगर ((beक्रमe >= 0) || (after >= 0)) अणु
		अगर ((beक्रमe >= 0) && (after >= 0)) अणु
			ichdr.मुक्तmap[beक्रमe].size += entsize;
			ichdr.मुक्तmap[beक्रमe].size += ichdr.मुक्तmap[after].size;
			ichdr.मुक्तmap[after].base = 0;
			ichdr.मुक्तmap[after].size = 0;
		पूर्ण अन्यथा अगर (beक्रमe >= 0) अणु
			ichdr.मुक्तmap[beक्रमe].size += entsize;
		पूर्ण अन्यथा अणु
			ichdr.मुक्तmap[after].base = be16_to_cpu(entry->nameidx);
			ichdr.मुक्तmap[after].size += entsize;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Replace smallest region (अगर it is smaller than मुक्त'd entry)
		 */
		अगर (ichdr.मुक्तmap[smallest].size < entsize) अणु
			ichdr.मुक्तmap[smallest].base = be16_to_cpu(entry->nameidx);
			ichdr.मुक्तmap[smallest].size = entsize;
		पूर्ण
	पूर्ण

	/*
	 * Did we हटाओ the first entry?
	 */
	अगर (be16_to_cpu(entry->nameidx) == ichdr.firstused)
		smallest = 1;
	अन्यथा
		smallest = 0;

	/*
	 * Compress the reमुख्यing entries and zero out the हटाओd stuff.
	 */
	स_रखो(xfs_attr3_leaf_name(leaf, args->index), 0, entsize);
	ichdr.usedbytes -= entsize;
	xfs_trans_log_buf(args->trans, bp,
	     XFS_DA_LOGRANGE(leaf, xfs_attr3_leaf_name(leaf, args->index),
				   entsize));

	पंचांगp = (ichdr.count - args->index) * माप(xfs_attr_leaf_entry_t);
	स_हटाओ(entry, entry + 1, पंचांगp);
	ichdr.count--;
	xfs_trans_log_buf(args->trans, bp,
	    XFS_DA_LOGRANGE(leaf, entry, पंचांगp + माप(xfs_attr_leaf_entry_t)));

	entry = &xfs_attr3_leaf_entryp(leaf)[ichdr.count];
	स_रखो(entry, 0, माप(xfs_attr_leaf_entry_t));

	/*
	 * If we हटाओd the first entry, re-find the first used byte
	 * in the name area.  Note that अगर the entry was the "firstused",
	 * then we करोn't have a "hole" in our block resulting from
	 * removing the name.
	 */
	अगर (smallest) अणु
		पंचांगp = args->geo->blksize;
		entry = xfs_attr3_leaf_entryp(leaf);
		क्रम (i = ichdr.count - 1; i >= 0; entry++, i--) अणु
			ASSERT(be16_to_cpu(entry->nameidx) >= ichdr.firstused);
			ASSERT(be16_to_cpu(entry->nameidx) < args->geo->blksize);

			अगर (be16_to_cpu(entry->nameidx) < पंचांगp)
				पंचांगp = be16_to_cpu(entry->nameidx);
		पूर्ण
		ichdr.firstused = पंचांगp;
		ASSERT(ichdr.firstused != 0);
	पूर्ण अन्यथा अणु
		ichdr.holes = 1;	/* mark as needing compaction */
	पूर्ण
	xfs_attr3_leaf_hdr_to_disk(args->geo, leaf, &ichdr);
	xfs_trans_log_buf(args->trans, bp,
			  XFS_DA_LOGRANGE(leaf, &leaf->hdr,
					  xfs_attr3_leaf_hdr_size(leaf)));

	/*
	 * Check अगर leaf is less than 50% full, caller may want to
	 * "join" the leaf with a sibling अगर so.
	 */
	पंचांगp = ichdr.usedbytes + xfs_attr3_leaf_hdr_size(leaf) +
	      ichdr.count * माप(xfs_attr_leaf_entry_t);

	वापस पंचांगp < args->geo->magicpct; /* leaf is < 37% full */
पूर्ण

/*
 * Move all the attribute list entries from drop_leaf पूर्णांकo save_leaf.
 */
व्योम
xfs_attr3_leaf_unbalance(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*drop_blk,
	काष्ठा xfs_da_state_blk	*save_blk)
अणु
	काष्ठा xfs_attr_leafblock *drop_leaf = drop_blk->bp->b_addr;
	काष्ठा xfs_attr_leafblock *save_leaf = save_blk->bp->b_addr;
	काष्ठा xfs_attr3_icleaf_hdr drophdr;
	काष्ठा xfs_attr3_icleaf_hdr savehdr;
	काष्ठा xfs_attr_leaf_entry *entry;

	trace_xfs_attr_leaf_unbalance(state->args);

	drop_leaf = drop_blk->bp->b_addr;
	save_leaf = save_blk->bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &drophdr, drop_leaf);
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &savehdr, save_leaf);
	entry = xfs_attr3_leaf_entryp(drop_leaf);

	/*
	 * Save last hashval from dying block क्रम later Btree fixup.
	 */
	drop_blk->hashval = be32_to_cpu(entry[drophdr.count - 1].hashval);

	/*
	 * Check अगर we need a temp buffer, or can we करो it in place.
	 * Note that we करोn't check "leaf" क्रम holes because we will
	 * always be dropping it, toosmall() decided that क्रम us alपढ़ोy.
	 */
	अगर (savehdr.holes == 0) अणु
		/*
		 * dest leaf has no holes, so we add there.  May need
		 * to make some room in the entry array.
		 */
		अगर (xfs_attr3_leaf_order(save_blk->bp, &savehdr,
					 drop_blk->bp, &drophdr)) अणु
			xfs_attr3_leaf_moveents(state->args,
						drop_leaf, &drophdr, 0,
						save_leaf, &savehdr, 0,
						drophdr.count);
		पूर्ण अन्यथा अणु
			xfs_attr3_leaf_moveents(state->args,
						drop_leaf, &drophdr, 0,
						save_leaf, &savehdr,
						savehdr.count, drophdr.count);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Destination has holes, so we make a temporary copy
		 * of the leaf and add them both to that.
		 */
		काष्ठा xfs_attr_leafblock *पंचांगp_leaf;
		काष्ठा xfs_attr3_icleaf_hdr पंचांगphdr;

		पंचांगp_leaf = kmem_zalloc(state->args->geo->blksize, 0);

		/*
		 * Copy the header पूर्णांकo the temp leaf so that all the stuff
		 * not in the incore header is present and माला_लो copied back in
		 * once we've moved all the entries.
		 */
		स_नकल(पंचांगp_leaf, save_leaf, xfs_attr3_leaf_hdr_size(save_leaf));

		स_रखो(&पंचांगphdr, 0, माप(पंचांगphdr));
		पंचांगphdr.magic = savehdr.magic;
		पंचांगphdr.क्रमw = savehdr.क्रमw;
		पंचांगphdr.back = savehdr.back;
		पंचांगphdr.firstused = state->args->geo->blksize;

		/* ग_लिखो the header to the temp buffer to initialise it */
		xfs_attr3_leaf_hdr_to_disk(state->args->geo, पंचांगp_leaf, &पंचांगphdr);

		अगर (xfs_attr3_leaf_order(save_blk->bp, &savehdr,
					 drop_blk->bp, &drophdr)) अणु
			xfs_attr3_leaf_moveents(state->args,
						drop_leaf, &drophdr, 0,
						पंचांगp_leaf, &पंचांगphdr, 0,
						drophdr.count);
			xfs_attr3_leaf_moveents(state->args,
						save_leaf, &savehdr, 0,
						पंचांगp_leaf, &पंचांगphdr, पंचांगphdr.count,
						savehdr.count);
		पूर्ण अन्यथा अणु
			xfs_attr3_leaf_moveents(state->args,
						save_leaf, &savehdr, 0,
						पंचांगp_leaf, &पंचांगphdr, 0,
						savehdr.count);
			xfs_attr3_leaf_moveents(state->args,
						drop_leaf, &drophdr, 0,
						पंचांगp_leaf, &पंचांगphdr, पंचांगphdr.count,
						drophdr.count);
		पूर्ण
		स_नकल(save_leaf, पंचांगp_leaf, state->args->geo->blksize);
		savehdr = पंचांगphdr; /* काष्ठा copy */
		kmem_मुक्त(पंचांगp_leaf);
	पूर्ण

	xfs_attr3_leaf_hdr_to_disk(state->args->geo, save_leaf, &savehdr);
	xfs_trans_log_buf(state->args->trans, save_blk->bp, 0,
					   state->args->geo->blksize - 1);

	/*
	 * Copy out last hashval in each block क्रम B-tree code.
	 */
	entry = xfs_attr3_leaf_entryp(save_leaf);
	save_blk->hashval = be32_to_cpu(entry[savehdr.count - 1].hashval);
पूर्ण

/*========================================================================
 * Routines used क्रम finding things in the Btree.
 *========================================================================*/

/*
 * Look up a name in a leaf attribute list काष्ठाure.
 * This is the पूर्णांकernal routine, it uses the caller's buffer.
 *
 * Note that duplicate keys are allowed, but only check within the
 * current leaf node.  The Btree code must check in adjacent leaf nodes.
 *
 * Return in args->index the index पूर्णांकo the entry[] array of either
 * the found entry, or where the entry should have been (insert beक्रमe
 * that entry).
 *
 * Don't change the args->value unless we find the attribute.
 */
पूर्णांक
xfs_attr3_leaf_lookup_पूर्णांक(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_entry *entries;
	काष्ठा xfs_attr_leaf_name_local *name_loc;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	xfs_dahash_t		hashval;
	पूर्णांक			probe;
	पूर्णांक			span;

	trace_xfs_attr_leaf_lookup(args);

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	entries = xfs_attr3_leaf_entryp(leaf);
	अगर (ichdr.count >= args->geo->blksize / 8) अणु
		xfs_buf_mark_corrupt(bp);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Binary search.  (note: small blocks will skip this loop)
	 */
	hashval = args->hashval;
	probe = span = ichdr.count / 2;
	क्रम (entry = &entries[probe]; span > 4; entry = &entries[probe]) अणु
		span /= 2;
		अगर (be32_to_cpu(entry->hashval) < hashval)
			probe += span;
		अन्यथा अगर (be32_to_cpu(entry->hashval) > hashval)
			probe -= span;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!(probe >= 0 && (!ichdr.count || probe < ichdr.count))) अणु
		xfs_buf_mark_corrupt(bp);
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (!(span <= 4 || be32_to_cpu(entry->hashval) == hashval)) अणु
		xfs_buf_mark_corrupt(bp);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Since we may have duplicate hashval's, find the first matching
	 * hashval in the leaf.
	 */
	जबतक (probe > 0 && be32_to_cpu(entry->hashval) >= hashval) अणु
		entry--;
		probe--;
	पूर्ण
	जबतक (probe < ichdr.count &&
	       be32_to_cpu(entry->hashval) < hashval) अणु
		entry++;
		probe++;
	पूर्ण
	अगर (probe == ichdr.count || be32_to_cpu(entry->hashval) != hashval) अणु
		args->index = probe;
		वापस -ENOATTR;
	पूर्ण

	/*
	 * Duplicate keys may be present, so search all of them क्रम a match.
	 */
	क्रम (; probe < ichdr.count && (be32_to_cpu(entry->hashval) == hashval);
			entry++, probe++) अणु
/*
 * GROT: Add code to हटाओ incomplete entries.
 */
		अगर (entry->flags & XFS_ATTR_LOCAL) अणु
			name_loc = xfs_attr3_leaf_name_local(leaf, probe);
			अगर (!xfs_attr_match(args, name_loc->namelen,
					name_loc->nameval, entry->flags))
				जारी;
			args->index = probe;
			वापस -EEXIST;
		पूर्ण अन्यथा अणु
			name_rmt = xfs_attr3_leaf_name_remote(leaf, probe);
			अगर (!xfs_attr_match(args, name_rmt->namelen,
					name_rmt->name, entry->flags))
				जारी;
			args->index = probe;
			args->rmtvaluelen = be32_to_cpu(name_rmt->valuelen);
			args->rmtblkno = be32_to_cpu(name_rmt->valueblk);
			args->rmtblkcnt = xfs_attr3_rmt_blocks(
							args->dp->i_mount,
							args->rmtvaluelen);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	args->index = probe;
	वापस -ENOATTR;
पूर्ण

/*
 * Get the value associated with an attribute name from a leaf attribute
 * list काष्ठाure.
 *
 * If args->valuelen is zero, only the length needs to be वापसed.  Unlike a
 * lookup, we only वापस an error अगर the attribute करोes not exist or we can't
 * retrieve the value.
 */
पूर्णांक
xfs_attr3_leaf_getvalue(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_name_local *name_loc;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(ichdr.count < args->geo->blksize / 8);
	ASSERT(args->index < ichdr.count);

	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];
	अगर (entry->flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf, args->index);
		ASSERT(name_loc->namelen == args->namelen);
		ASSERT(स_भेद(args->name, name_loc->nameval, args->namelen) == 0);
		वापस xfs_attr_copy_value(args,
					&name_loc->nameval[args->namelen],
					be16_to_cpu(name_loc->valuelen));
	पूर्ण

	name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
	ASSERT(name_rmt->namelen == args->namelen);
	ASSERT(स_भेद(args->name, name_rmt->name, args->namelen) == 0);
	args->rmtvaluelen = be32_to_cpu(name_rmt->valuelen);
	args->rmtblkno = be32_to_cpu(name_rmt->valueblk);
	args->rmtblkcnt = xfs_attr3_rmt_blocks(args->dp->i_mount,
					       args->rmtvaluelen);
	वापस xfs_attr_copy_value(args, शून्य, args->rmtvaluelen);
पूर्ण

/*========================================================================
 * Utility routines.
 *========================================================================*/

/*
 * Move the indicated entries from one leaf to another.
 * NOTE: this routine modअगरies both source and destination leaves.
 */
/*ARGSUSED*/
STATIC व्योम
xfs_attr3_leaf_moveents(
	काष्ठा xfs_da_args		*args,
	काष्ठा xfs_attr_leafblock	*leaf_s,
	काष्ठा xfs_attr3_icleaf_hdr	*ichdr_s,
	पूर्णांक				start_s,
	काष्ठा xfs_attr_leafblock	*leaf_d,
	काष्ठा xfs_attr3_icleaf_hdr	*ichdr_d,
	पूर्णांक				start_d,
	पूर्णांक				count)
अणु
	काष्ठा xfs_attr_leaf_entry	*entry_s;
	काष्ठा xfs_attr_leaf_entry	*entry_d;
	पूर्णांक				desti;
	पूर्णांक				पंचांगp;
	पूर्णांक				i;

	/*
	 * Check क्रम nothing to करो.
	 */
	अगर (count == 0)
		वापस;

	/*
	 * Set up environment.
	 */
	ASSERT(ichdr_s->magic == XFS_ATTR_LEAF_MAGIC ||
	       ichdr_s->magic == XFS_ATTR3_LEAF_MAGIC);
	ASSERT(ichdr_s->magic == ichdr_d->magic);
	ASSERT(ichdr_s->count > 0 && ichdr_s->count < args->geo->blksize / 8);
	ASSERT(ichdr_s->firstused >= (ichdr_s->count * माप(*entry_s))
					+ xfs_attr3_leaf_hdr_size(leaf_s));
	ASSERT(ichdr_d->count < args->geo->blksize / 8);
	ASSERT(ichdr_d->firstused >= (ichdr_d->count * माप(*entry_d))
					+ xfs_attr3_leaf_hdr_size(leaf_d));

	ASSERT(start_s < ichdr_s->count);
	ASSERT(start_d <= ichdr_d->count);
	ASSERT(count <= ichdr_s->count);


	/*
	 * Move the entries in the destination leaf up to make a hole?
	 */
	अगर (start_d < ichdr_d->count) अणु
		पंचांगp  = ichdr_d->count - start_d;
		पंचांगp *= माप(xfs_attr_leaf_entry_t);
		entry_s = &xfs_attr3_leaf_entryp(leaf_d)[start_d];
		entry_d = &xfs_attr3_leaf_entryp(leaf_d)[start_d + count];
		स_हटाओ(entry_d, entry_s, पंचांगp);
	पूर्ण

	/*
	 * Copy all entry's in the same (sorted) order,
	 * but allocate attribute info packed and in sequence.
	 */
	entry_s = &xfs_attr3_leaf_entryp(leaf_s)[start_s];
	entry_d = &xfs_attr3_leaf_entryp(leaf_d)[start_d];
	desti = start_d;
	क्रम (i = 0; i < count; entry_s++, entry_d++, desti++, i++) अणु
		ASSERT(be16_to_cpu(entry_s->nameidx) >= ichdr_s->firstused);
		पंचांगp = xfs_attr_leaf_entsize(leaf_s, start_s + i);
#अगर_घोषित GROT
		/*
		 * Code to drop INCOMPLETE entries.  Dअगरficult to use as we
		 * may also need to change the insertion index.  Code turned
		 * off क्रम 6.2, should be revisited later.
		 */
		अगर (entry_s->flags & XFS_ATTR_INCOMPLETE) अणु /* skip partials? */
			स_रखो(xfs_attr3_leaf_name(leaf_s, start_s + i), 0, पंचांगp);
			ichdr_s->usedbytes -= पंचांगp;
			ichdr_s->count -= 1;
			entry_d--;	/* to compensate क्रम ++ in loop hdr */
			desti--;
			अगर ((start_s + i) < offset)
				result++;	/* insertion index adjusपंचांगent */
		पूर्ण अन्यथा अणु
#पूर्ण_अगर /* GROT */
			ichdr_d->firstused -= पंचांगp;
			/* both on-disk, करोn't endian flip twice */
			entry_d->hashval = entry_s->hashval;
			entry_d->nameidx = cpu_to_be16(ichdr_d->firstused);
			entry_d->flags = entry_s->flags;
			ASSERT(be16_to_cpu(entry_d->nameidx) + पंचांगp
							<= args->geo->blksize);
			स_हटाओ(xfs_attr3_leaf_name(leaf_d, desti),
				xfs_attr3_leaf_name(leaf_s, start_s + i), पंचांगp);
			ASSERT(be16_to_cpu(entry_s->nameidx) + पंचांगp
							<= args->geo->blksize);
			स_रखो(xfs_attr3_leaf_name(leaf_s, start_s + i), 0, पंचांगp);
			ichdr_s->usedbytes -= पंचांगp;
			ichdr_d->usedbytes += पंचांगp;
			ichdr_s->count -= 1;
			ichdr_d->count += 1;
			पंचांगp = ichdr_d->count * माप(xfs_attr_leaf_entry_t)
					+ xfs_attr3_leaf_hdr_size(leaf_d);
			ASSERT(ichdr_d->firstused >= पंचांगp);
#अगर_घोषित GROT
		पूर्ण
#पूर्ण_अगर /* GROT */
	पूर्ण

	/*
	 * Zero out the entries we just copied.
	 */
	अगर (start_s == ichdr_s->count) अणु
		पंचांगp = count * माप(xfs_attr_leaf_entry_t);
		entry_s = &xfs_attr3_leaf_entryp(leaf_s)[start_s];
		ASSERT(((अक्षर *)entry_s + पंचांगp) <=
		       ((अक्षर *)leaf_s + args->geo->blksize));
		स_रखो(entry_s, 0, पंचांगp);
	पूर्ण अन्यथा अणु
		/*
		 * Move the reमुख्यing entries करोwn to fill the hole,
		 * then zero the entries at the top.
		 */
		पंचांगp  = (ichdr_s->count - count) * माप(xfs_attr_leaf_entry_t);
		entry_s = &xfs_attr3_leaf_entryp(leaf_s)[start_s + count];
		entry_d = &xfs_attr3_leaf_entryp(leaf_s)[start_s];
		स_हटाओ(entry_d, entry_s, पंचांगp);

		पंचांगp = count * माप(xfs_attr_leaf_entry_t);
		entry_s = &xfs_attr3_leaf_entryp(leaf_s)[ichdr_s->count];
		ASSERT(((अक्षर *)entry_s + पंचांगp) <=
		       ((अक्षर *)leaf_s + args->geo->blksize));
		स_रखो(entry_s, 0, पंचांगp);
	पूर्ण

	/*
	 * Fill in the मुक्तmap inक्रमmation
	 */
	ichdr_d->मुक्तmap[0].base = xfs_attr3_leaf_hdr_size(leaf_d);
	ichdr_d->मुक्तmap[0].base += ichdr_d->count * माप(xfs_attr_leaf_entry_t);
	ichdr_d->मुक्तmap[0].size = ichdr_d->firstused - ichdr_d->मुक्तmap[0].base;
	ichdr_d->मुक्तmap[1].base = 0;
	ichdr_d->मुक्तmap[2].base = 0;
	ichdr_d->मुक्तmap[1].size = 0;
	ichdr_d->मुक्तmap[2].size = 0;
	ichdr_s->holes = 1;	/* leaf may not be compact */
पूर्ण

/*
 * Pick up the last hashvalue from a leaf block.
 */
xfs_dahash_t
xfs_attr_leaf_lasthash(
	काष्ठा xfs_buf	*bp,
	पूर्णांक		*count)
अणु
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	काष्ठा xfs_attr_leaf_entry *entries;
	काष्ठा xfs_mount *mp = bp->b_mount;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, bp->b_addr);
	entries = xfs_attr3_leaf_entryp(bp->b_addr);
	अगर (count)
		*count = ichdr.count;
	अगर (!ichdr.count)
		वापस 0;
	वापस be32_to_cpu(entries[ichdr.count - 1].hashval);
पूर्ण

/*
 * Calculate the number of bytes used to store the indicated attribute
 * (whether local or remote only calculate bytes in this block).
 */
STATIC पूर्णांक
xfs_attr_leaf_entsize(xfs_attr_leafblock_t *leaf, पूर्णांक index)
अणु
	काष्ठा xfs_attr_leaf_entry *entries;
	xfs_attr_leaf_name_local_t *name_loc;
	xfs_attr_leaf_name_remote_t *name_rmt;
	पूर्णांक size;

	entries = xfs_attr3_leaf_entryp(leaf);
	अगर (entries[index].flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf, index);
		size = xfs_attr_leaf_entsize_local(name_loc->namelen,
						   be16_to_cpu(name_loc->valuelen));
	पूर्ण अन्यथा अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf, index);
		size = xfs_attr_leaf_entsize_remote(name_rmt->namelen);
	पूर्ण
	वापस size;
पूर्ण

/*
 * Calculate the number of bytes that would be required to store the new
 * attribute (whether local or remote only calculate bytes in this block).
 * This routine decides as a side effect whether the attribute will be
 * a "local" or a "remote" attribute.
 */
पूर्णांक
xfs_attr_leaf_newentsize(
	काष्ठा xfs_da_args	*args,
	पूर्णांक			*local)
अणु
	पूर्णांक			size;

	size = xfs_attr_leaf_entsize_local(args->namelen, args->valuelen);
	अगर (size < xfs_attr_leaf_entsize_local_max(args->geo->blksize)) अणु
		अगर (local)
			*local = 1;
		वापस size;
	पूर्ण
	अगर (local)
		*local = 0;
	वापस xfs_attr_leaf_entsize_remote(args->namelen);
पूर्ण


/*========================================================================
 * Manage the INCOMPLETE flag in a leaf entry
 *========================================================================*/

/*
 * Clear the INCOMPLETE flag on an entry in a leaf block.
 */
पूर्णांक
xfs_attr3_leaf_clearflag(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
#अगर_घोषित DEBUG
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
	xfs_attr_leaf_name_local_t *name_loc;
	पूर्णांक namelen;
	अक्षर *name;
#पूर्ण_अगर /* DEBUG */

	trace_xfs_attr_leaf_clearflag(args);
	/*
	 * Set up the operation.
	 */
	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, args->blkno, &bp);
	अगर (error)
		वापस error;

	leaf = bp->b_addr;
	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];
	ASSERT(entry->flags & XFS_ATTR_INCOMPLETE);

#अगर_घोषित DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(args->index < ichdr.count);
	ASSERT(args->index >= 0);

	अगर (entry->flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf, args->index);
		namelen = name_loc->namelen;
		name = (अक्षर *)name_loc->nameval;
	पूर्ण अन्यथा अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		namelen = name_rmt->namelen;
		name = (अक्षर *)name_rmt->name;
	पूर्ण
	ASSERT(be32_to_cpu(entry->hashval) == args->hashval);
	ASSERT(namelen == args->namelen);
	ASSERT(स_भेद(name, args->name, namelen) == 0);
#पूर्ण_अगर /* DEBUG */

	entry->flags &= ~XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, entry, माप(*entry)));

	अगर (args->rmtblkno) अणु
		ASSERT((entry->flags & XFS_ATTR_LOCAL) == 0);
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		name_rmt->valueblk = cpu_to_be32(args->rmtblkno);
		name_rmt->valuelen = cpu_to_be32(args->rmtvaluelen);
		xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, name_rmt, माप(*name_rmt)));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set the INCOMPLETE flag on an entry in a leaf block.
 */
पूर्णांक
xfs_attr3_leaf_setflag(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf;
	काष्ठा xfs_attr_leaf_entry *entry;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	काष्ठा xfs_buf		*bp;
	पूर्णांक error;
#अगर_घोषित DEBUG
	काष्ठा xfs_attr3_icleaf_hdr ichdr;
#पूर्ण_अगर

	trace_xfs_attr_leaf_setflag(args);

	/*
	 * Set up the operation.
	 */
	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, args->blkno, &bp);
	अगर (error)
		वापस error;

	leaf = bp->b_addr;
#अगर_घोषित DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(args->index < ichdr.count);
	ASSERT(args->index >= 0);
#पूर्ण_अगर
	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];

	ASSERT((entry->flags & XFS_ATTR_INCOMPLETE) == 0);
	entry->flags |= XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp,
			XFS_DA_LOGRANGE(leaf, entry, माप(*entry)));
	अगर ((entry->flags & XFS_ATTR_LOCAL) == 0) अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, name_rmt, माप(*name_rmt)));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * In a single transaction, clear the INCOMPLETE flag on the leaf entry
 * given by args->blkno/index and set the INCOMPLETE flag on the leaf
 * entry given by args->blkno2/index2.
 *
 * Note that they could be in dअगरferent blocks, or in the same block.
 */
पूर्णांक
xfs_attr3_leaf_flipflags(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_attr_leafblock *leaf1;
	काष्ठा xfs_attr_leafblock *leaf2;
	काष्ठा xfs_attr_leaf_entry *entry1;
	काष्ठा xfs_attr_leaf_entry *entry2;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	काष्ठा xfs_buf		*bp1;
	काष्ठा xfs_buf		*bp2;
	पूर्णांक error;
#अगर_घोषित DEBUG
	काष्ठा xfs_attr3_icleaf_hdr ichdr1;
	काष्ठा xfs_attr3_icleaf_hdr ichdr2;
	xfs_attr_leaf_name_local_t *name_loc;
	पूर्णांक namelen1, namelen2;
	अक्षर *name1, *name2;
#पूर्ण_अगर /* DEBUG */

	trace_xfs_attr_leaf_flipflags(args);

	/*
	 * Read the block containing the "old" attr
	 */
	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, args->blkno, &bp1);
	अगर (error)
		वापस error;

	/*
	 * Read the block containing the "new" attr, अगर it is dअगरferent
	 */
	अगर (args->blkno2 != args->blkno) अणु
		error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, args->blkno2,
					   &bp2);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		bp2 = bp1;
	पूर्ण

	leaf1 = bp1->b_addr;
	entry1 = &xfs_attr3_leaf_entryp(leaf1)[args->index];

	leaf2 = bp2->b_addr;
	entry2 = &xfs_attr3_leaf_entryp(leaf2)[args->index2];

#अगर_घोषित DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr1, leaf1);
	ASSERT(args->index < ichdr1.count);
	ASSERT(args->index >= 0);

	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr2, leaf2);
	ASSERT(args->index2 < ichdr2.count);
	ASSERT(args->index2 >= 0);

	अगर (entry1->flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf1, args->index);
		namelen1 = name_loc->namelen;
		name1 = (अक्षर *)name_loc->nameval;
	पूर्ण अन्यथा अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf1, args->index);
		namelen1 = name_rmt->namelen;
		name1 = (अक्षर *)name_rmt->name;
	पूर्ण
	अगर (entry2->flags & XFS_ATTR_LOCAL) अणु
		name_loc = xfs_attr3_leaf_name_local(leaf2, args->index2);
		namelen2 = name_loc->namelen;
		name2 = (अक्षर *)name_loc->nameval;
	पूर्ण अन्यथा अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf2, args->index2);
		namelen2 = name_rmt->namelen;
		name2 = (अक्षर *)name_rmt->name;
	पूर्ण
	ASSERT(be32_to_cpu(entry1->hashval) == be32_to_cpu(entry2->hashval));
	ASSERT(namelen1 == namelen2);
	ASSERT(स_भेद(name1, name2, namelen1) == 0);
#पूर्ण_अगर /* DEBUG */

	ASSERT(entry1->flags & XFS_ATTR_INCOMPLETE);
	ASSERT((entry2->flags & XFS_ATTR_INCOMPLETE) == 0);

	entry1->flags &= ~XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp1,
			  XFS_DA_LOGRANGE(leaf1, entry1, माप(*entry1)));
	अगर (args->rmtblkno) अणु
		ASSERT((entry1->flags & XFS_ATTR_LOCAL) == 0);
		name_rmt = xfs_attr3_leaf_name_remote(leaf1, args->index);
		name_rmt->valueblk = cpu_to_be32(args->rmtblkno);
		name_rmt->valuelen = cpu_to_be32(args->rmtvaluelen);
		xfs_trans_log_buf(args->trans, bp1,
			 XFS_DA_LOGRANGE(leaf1, name_rmt, माप(*name_rmt)));
	पूर्ण

	entry2->flags |= XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp2,
			  XFS_DA_LOGRANGE(leaf2, entry2, माप(*entry2)));
	अगर ((entry2->flags & XFS_ATTR_LOCAL) == 0) अणु
		name_rmt = xfs_attr3_leaf_name_remote(leaf2, args->index2);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_trans_log_buf(args->trans, bp2,
			 XFS_DA_LOGRANGE(leaf2, name_rmt, माप(*name_rmt)));
	पूर्ण

	वापस 0;
पूर्ण
