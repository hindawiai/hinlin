<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Veritas fileप्रणाली driver - fileप्रणाली to disk block mapping.
 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>

#समावेश "vxfs.h"
#समावेश "vxfs_inode.h"
#समावेश "vxfs_extern.h"


#अगर_घोषित DIAGNOSTIC
अटल व्योम
vxfs_typdump(काष्ठा vxfs_typed *typ)
अणु
	prपूर्णांकk(KERN_DEBUG "type=%Lu ", typ->vt_hdr >> VXFS_TYPED_TYPESHIFT);
	prपूर्णांकk("offset=%Lx ", typ->vt_hdr & VXFS_TYPED_OFFSETMASK);
	prपूर्णांकk("block=%x ", typ->vt_block);
	prपूर्णांकk("size=%x\n", typ->vt_size);
पूर्ण
#पूर्ण_अगर

/**
 * vxfs_bmap_ext4 - करो bmap क्रम ext4 extents
 * @ip:		poपूर्णांकer to the inode we करो bmap क्रम
 * @iblock:	logical block.
 *
 * Description:
 *   vxfs_bmap_ext4 perक्रमms the bmap operation क्रम inodes with
 *   ext4-style extents (which are much like the traditional UNIX
 *   inode organisation).
 *
 * Returns:
 *   The physical block number on success, अन्यथा Zero.
 */
अटल daddr_t
vxfs_bmap_ext4(काष्ठा inode *ip, दीर्घ bn)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	काष्ठा vxfs_inode_info *vip = VXFS_INO(ip);
	काष्ठा vxfs_sb_info *sbi = VXFS_SBI(sb);
	अचिन्हित दीर्घ bsize = sb->s_blocksize;
	u32 indsize = fs32_to_cpu(sbi, vip->vii_ext4.ve4_indsize);
	पूर्णांक i;

	अगर (indsize > sb->s_blocksize)
		जाओ fail_size;

	क्रम (i = 0; i < VXFS_NDADDR; i++) अणु
		काष्ठा direct *d = vip->vii_ext4.ve4_direct + i;
		अगर (bn >= 0 && bn < fs32_to_cpu(sbi, d->size))
			वापस (bn + fs32_to_cpu(sbi, d->extent));
		bn -= fs32_to_cpu(sbi, d->size);
	पूर्ण

	अगर ((bn / (indsize * indsize * bsize / 4)) == 0) अणु
		काष्ठा buffer_head *buf;
		daddr_t	bno;
		__fs32 *indir;

		buf = sb_bपढ़ो(sb,
			fs32_to_cpu(sbi, vip->vii_ext4.ve4_indir[0]));
		अगर (!buf || !buffer_mapped(buf))
			जाओ fail_buf;

		indir = (__fs32 *)buf->b_data;
		bno = fs32_to_cpu(sbi, indir[(bn / indsize) % (indsize * bn)]) +
			(bn % indsize);

		brअन्यथा(buf);
		वापस bno;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_WARNING "no matching indir?");

	वापस 0;

fail_size:
	prपूर्णांकk("vxfs: indirect extent too big!\n");
fail_buf:
	वापस 0;
पूर्ण

/**
 * vxfs_bmap_indir - recursion क्रम vxfs_bmap_typed
 * @ip:		poपूर्णांकer to the inode we करो bmap क्रम
 * @indir:	indirect block we start पढ़ोing at
 * @size:	size of the typed area to search
 * @block:	partially result from further searches
 *
 * Description:
 *   vxfs_bmap_indir पढ़ोs a &काष्ठा vxfs_typed at @indir
 *   and perक्रमms the type-defined action.
 *
 * Return Value:
 *   The physical block number on success, अन्यथा Zero.
 *
 * Note:
 *   Kernelstack is rare.  Unrecurse?
 */
अटल daddr_t
vxfs_bmap_indir(काष्ठा inode *ip, दीर्घ indir, पूर्णांक size, दीर्घ block)
अणु
	काष्ठा vxfs_sb_info		*sbi = VXFS_SBI(ip->i_sb);
	काष्ठा buffer_head		*bp = शून्य;
	daddr_t				pblock = 0;
	पूर्णांक				i;

	क्रम (i = 0; i < size * VXFS_TYPED_PER_BLOCK(ip->i_sb); i++) अणु
		काष्ठा vxfs_typed	*typ;
		पूर्णांक64_t			off;

		bp = sb_bपढ़ो(ip->i_sb,
				indir + (i / VXFS_TYPED_PER_BLOCK(ip->i_sb)));
		अगर (!bp || !buffer_mapped(bp))
			वापस 0;

		typ = ((काष्ठा vxfs_typed *)bp->b_data) +
			(i % VXFS_TYPED_PER_BLOCK(ip->i_sb));
		off = fs64_to_cpu(sbi, typ->vt_hdr) & VXFS_TYPED_OFFSETMASK;

		अगर (block < off) अणु
			brअन्यथा(bp);
			जारी;
		पूर्ण

		चयन ((u_पूर्णांक32_t)(fs64_to_cpu(sbi, typ->vt_hdr) >>
				VXFS_TYPED_TYPESHIFT)) अणु
		हाल VXFS_TYPED_INसूचीECT:
			pblock = vxfs_bmap_indir(ip,
					fs32_to_cpu(sbi, typ->vt_block),
					fs32_to_cpu(sbi, typ->vt_size),
					block - off);
			अगर (pblock == -2)
				अवरोध;
			जाओ out;
		हाल VXFS_TYPED_DATA:
			अगर ((block - off) >= fs32_to_cpu(sbi, typ->vt_size))
				अवरोध;
			pblock = fs32_to_cpu(sbi, typ->vt_block) + block - off;
			जाओ out;
		हाल VXFS_TYPED_INसूचीECT_DEV4:
		हाल VXFS_TYPED_DATA_DEV4: अणु
			काष्ठा vxfs_typed_dev4	*typ4 =
				(काष्ठा vxfs_typed_dev4 *)typ;

			prपूर्णांकk(KERN_INFO "\n\nTYPED_DEV4 detected!\n");
			prपूर्णांकk(KERN_INFO "block: %llu\tsize: %lld\tdev: %d\n",
			       fs64_to_cpu(sbi, typ4->vd4_block),
			       fs64_to_cpu(sbi, typ4->vd4_size),
			       fs32_to_cpu(sbi, typ4->vd4_dev));
			जाओ fail;
		पूर्ण
		शेष:
			prपूर्णांकk(KERN_ERR "%s:%d vt_hdr %llu\n", __func__,
				__LINE__, fs64_to_cpu(sbi, typ->vt_hdr));
			BUG();
		पूर्ण
		brअन्यथा(bp);
	पूर्ण

fail:
	pblock = 0;
out:
	brअन्यथा(bp);
	वापस (pblock);
पूर्ण

/**
 * vxfs_bmap_typed - bmap क्रम typed extents
 * @ip:		poपूर्णांकer to the inode we करो bmap क्रम
 * @iblock:	logical block
 *
 * Description:
 *   Perक्रमms the bmap operation क्रम typed extents.
 *
 * Return Value:
 *   The physical block number on success, अन्यथा Zero.
 */
अटल daddr_t
vxfs_bmap_typed(काष्ठा inode *ip, दीर्घ iblock)
अणु
	काष्ठा vxfs_inode_info		*vip = VXFS_INO(ip);
	काष्ठा vxfs_sb_info		*sbi = VXFS_SBI(ip->i_sb);
	daddr_t				pblock = 0;
	पूर्णांक				i;

	क्रम (i = 0; i < VXFS_NTYPED; i++) अणु
		काष्ठा vxfs_typed	*typ = vip->vii_org.typed + i;
		u64			hdr = fs64_to_cpu(sbi, typ->vt_hdr);
		पूर्णांक64_t			off = (hdr & VXFS_TYPED_OFFSETMASK);

#अगर_घोषित DIAGNOSTIC
		vxfs_typdump(typ);
#पूर्ण_अगर
		अगर (iblock < off)
			जारी;
		चयन ((u32)(hdr >> VXFS_TYPED_TYPESHIFT)) अणु
		हाल VXFS_TYPED_INसूचीECT:
			pblock = vxfs_bmap_indir(ip,
					fs32_to_cpu(sbi, typ->vt_block),
					fs32_to_cpu(sbi, typ->vt_size),
					iblock - off);
			अगर (pblock == -2)
				अवरोध;
			वापस (pblock);
		हाल VXFS_TYPED_DATA:
			अगर ((iblock - off) < fs32_to_cpu(sbi, typ->vt_size))
				वापस (fs32_to_cpu(sbi, typ->vt_block) +
						iblock - off);
			अवरोध;
		हाल VXFS_TYPED_INसूचीECT_DEV4:
		हाल VXFS_TYPED_DATA_DEV4: अणु
			काष्ठा vxfs_typed_dev4	*typ4 =
				(काष्ठा vxfs_typed_dev4 *)typ;

			prपूर्णांकk(KERN_INFO "\n\nTYPED_DEV4 detected!\n");
			prपूर्णांकk(KERN_INFO "block: %llu\tsize: %lld\tdev: %d\n",
			       fs64_to_cpu(sbi, typ4->vd4_block),
			       fs64_to_cpu(sbi, typ4->vd4_size),
			       fs32_to_cpu(sbi, typ4->vd4_dev));
			वापस 0;
		पूर्ण
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vxfs_bmap1 - vxfs-पूर्णांकernal bmap operation
 * @ip:			poपूर्णांकer to the inode we करो bmap क्रम
 * @iblock:		logical block
 *
 * Description:
 *   vxfs_bmap1 perfoms a logical to physical block mapping
 *   क्रम vxfs-पूर्णांकernal purposes.
 *
 * Return Value:
 *   The physical block number on success, अन्यथा Zero.
 */
daddr_t
vxfs_bmap1(काष्ठा inode *ip, दीर्घ iblock)
अणु
	काष्ठा vxfs_inode_info		*vip = VXFS_INO(ip);

	अगर (VXFS_ISEXT4(vip))
		वापस vxfs_bmap_ext4(ip, iblock);
	अगर (VXFS_ISTYPED(vip))
		वापस vxfs_bmap_typed(ip, iblock);
	अगर (VXFS_ISNONE(vip))
		जाओ unsupp;
	अगर (VXFS_ISIMMED(vip))
		जाओ unsupp;

	prपूर्णांकk(KERN_WARNING "vxfs: inode %ld has no valid orgtype (%x)\n",
			ip->i_ino, vip->vii_orgtype);
	BUG();

unsupp:
	prपूर्णांकk(KERN_WARNING "vxfs: inode %ld has an unsupported orgtype (%x)\n",
			ip->i_ino, vip->vii_orgtype);
	वापस 0;
पूर्ण
