<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/alloc.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  HPFS biपंचांगap operations
 */

#समावेश "hpfs_fn.h"

अटल व्योम hpfs_claim_alloc(काष्ठा super_block *s, secno sec)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (sbi->sb_n_मुक्त != (अचिन्हित)-1) अणु
		अगर (unlikely(!sbi->sb_n_मुक्त)) अणु
			hpfs_error(s, "free count underflow, allocating sector %08x", sec);
			sbi->sb_n_मुक्त = -1;
			वापस;
		पूर्ण
		sbi->sb_n_मुक्त--;
	पूर्ण
पूर्ण

अटल व्योम hpfs_claim_मुक्त(काष्ठा super_block *s, secno sec)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (sbi->sb_n_मुक्त != (अचिन्हित)-1) अणु
		अगर (unlikely(sbi->sb_n_मुक्त >= sbi->sb_fs_size)) अणु
			hpfs_error(s, "free count overflow, freeing sector %08x", sec);
			sbi->sb_n_मुक्त = -1;
			वापस;
		पूर्ण
		sbi->sb_n_मुक्त++;
	पूर्ण
पूर्ण

अटल व्योम hpfs_claim_dirband_alloc(काष्ठा super_block *s, secno sec)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (sbi->sb_n_मुक्त_dnodes != (अचिन्हित)-1) अणु
		अगर (unlikely(!sbi->sb_n_मुक्त_dnodes)) अणु
			hpfs_error(s, "dirband free count underflow, allocating sector %08x", sec);
			sbi->sb_n_मुक्त_dnodes = -1;
			वापस;
		पूर्ण
		sbi->sb_n_मुक्त_dnodes--;
	पूर्ण
पूर्ण

अटल व्योम hpfs_claim_dirband_मुक्त(काष्ठा super_block *s, secno sec)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (sbi->sb_n_मुक्त_dnodes != (अचिन्हित)-1) अणु
		अगर (unlikely(sbi->sb_n_मुक्त_dnodes >= sbi->sb_dirband_size / 4)) अणु
			hpfs_error(s, "dirband free count overflow, freeing sector %08x", sec);
			sbi->sb_n_मुक्त_dnodes = -1;
			वापस;
		पूर्ण
		sbi->sb_n_मुक्त_dnodes++;
	पूर्ण
पूर्ण

/*
 * Check अगर a sector is allocated in biपंचांगap
 * This is really slow. Turned on only अगर chk==2
 */

अटल पूर्णांक chk_अगर_allocated(काष्ठा super_block *s, secno sec, अक्षर *msg)
अणु
	काष्ठा quad_buffer_head qbh;
	__le32 *bmp;
	अगर (!(bmp = hpfs_map_biपंचांगap(s, sec >> 14, &qbh, "chk"))) जाओ fail;
	अगर ((le32_to_cpu(bmp[(sec & 0x3fff) >> 5]) >> (sec & 0x1f)) & 1) अणु
		hpfs_error(s, "sector '%s' - %08x not allocated in bitmap", msg, sec);
		जाओ fail1;
	पूर्ण
	hpfs_brअन्यथा4(&qbh);
	अगर (sec >= hpfs_sb(s)->sb_dirband_start && sec < hpfs_sb(s)->sb_dirband_start + hpfs_sb(s)->sb_dirband_size) अणु
		अचिन्हित ssec = (sec - hpfs_sb(s)->sb_dirband_start) / 4;
		अगर (!(bmp = hpfs_map_dnode_biपंचांगap(s, &qbh))) जाओ fail;
		अगर ((le32_to_cpu(bmp[ssec >> 5]) >> (ssec & 0x1f)) & 1) अणु
			hpfs_error(s, "sector '%s' - %08x not allocated in directory bitmap", msg, sec);
			जाओ fail1;
		पूर्ण
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
	वापस 0;
	fail1:
	hpfs_brअन्यथा4(&qbh);
	fail:
	वापस 1;
पूर्ण

/*
 * Check अगर sector(s) have proper number and additionally check अगर they're
 * allocated in biपंचांगap.
 */
	
पूर्णांक hpfs_chk_sectors(काष्ठा super_block *s, secno start, पूर्णांक len, अक्षर *msg)
अणु
	अगर (start + len < start || start < 0x12 ||
	    start + len > hpfs_sb(s)->sb_fs_size) अणु
	    	hpfs_error(s, "sector(s) '%s' badly placed at %08x", msg, start);
		वापस 1;
	पूर्ण
	अगर (hpfs_sb(s)->sb_chk>=2) अणु
		पूर्णांक i;
		क्रम (i = 0; i < len; i++)
			अगर (chk_अगर_allocated(s, start + i, msg)) वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल secno alloc_in_bmp(काष्ठा super_block *s, secno near, अचिन्हित n, अचिन्हित क्रमward)
अणु
	काष्ठा quad_buffer_head qbh;
	__le32 *bmp;
	अचिन्हित bs = near & ~0x3fff;
	अचिन्हित nr = (near & 0x3fff) & ~(n - 1);
	/*अचिन्हित mnr;*/
	अचिन्हित i, q;
	पूर्णांक a, b;
	secno ret = 0;
	अगर (n != 1 && n != 4) अणु
		hpfs_error(s, "Bad allocation size: %d", n);
		वापस 0;
	पूर्ण
	अगर (bs != ~0x3fff) अणु
		अगर (!(bmp = hpfs_map_biपंचांगap(s, near >> 14, &qbh, "aib"))) जाओ uls;
	पूर्ण अन्यथा अणु
		अगर (!(bmp = hpfs_map_dnode_biपंचांगap(s, &qbh))) जाओ uls;
	पूर्ण
	अगर (!tstbits(bmp, nr, n + क्रमward)) अणु
		ret = bs + nr;
		जाओ rt;
	पूर्ण
	q = nr + n; b = 0;
	जबतक ((a = tstbits(bmp, q, n + क्रमward)) != 0) अणु
		q += a;
		अगर (n != 1) q = ((q-1)&~(n-1))+n;
		अगर (!b) अणु
			अगर (q>>5 != nr>>5) अणु
				b = 1;
				q = nr & 0x1f;
			पूर्ण
		पूर्ण अन्यथा अगर (q > nr) अवरोध;
	पूर्ण
	अगर (!a) अणु
		ret = bs + q;
		जाओ rt;
	पूर्ण
	nr >>= 5;
	/*क्रम (i = nr + 1; i != nr; i++, i &= 0x1ff) */
	i = nr;
	करो अणु
		अगर (!le32_to_cpu(bmp[i])) जाओ cont;
		अगर (n + क्रमward >= 0x3f && le32_to_cpu(bmp[i]) != 0xffffffff) जाओ cont;
		q = i<<5;
		अगर (i > 0) अणु
			अचिन्हित k = le32_to_cpu(bmp[i-1]);
			जबतक (k & 0x80000000) अणु
				q--; k <<= 1;
			पूर्ण
		पूर्ण
		अगर (n != 1) q = ((q-1)&~(n-1))+n;
		जबतक ((a = tstbits(bmp, q, n + क्रमward)) != 0) अणु
			q += a;
			अगर (n != 1) q = ((q-1)&~(n-1))+n;
			अगर (q>>5 > i) अवरोध;
		पूर्ण
		अगर (!a) अणु
			ret = bs + q;
			जाओ rt;
		पूर्ण
		cont:
		i++, i &= 0x1ff;
	पूर्ण जबतक (i != nr);
	rt:
	अगर (ret) अणु
		अगर (hpfs_sb(s)->sb_chk && ((ret >> 14) != (bs >> 14) || (le32_to_cpu(bmp[(ret & 0x3fff) >> 5]) | ~(((1 << n) - 1) << (ret & 0x1f))) != 0xffffffff)) अणु
			hpfs_error(s, "Allocation doesn't work! Wanted %d, allocated at %08x", n, ret);
			ret = 0;
			जाओ b;
		पूर्ण
		bmp[(ret & 0x3fff) >> 5] &= cpu_to_le32(~(((1 << n) - 1) << (ret & 0x1f)));
		hpfs_mark_4buffers_dirty(&qbh);
	पूर्ण
	b:
	hpfs_brअन्यथा4(&qbh);
	uls:
	वापस ret;
पूर्ण

/*
 * Allocation strategy:	1) search place near the sector specअगरied
 *			2) search biपंचांगap where मुक्त sectors last found
 *			3) search all biपंचांगaps
 *			4) search all biपंचांगaps ignoring number of pre-allocated
 *				sectors
 */

secno hpfs_alloc_sector(काष्ठा super_block *s, secno near, अचिन्हित n, पूर्णांक क्रमward)
अणु
	secno sec;
	पूर्णांक i;
	अचिन्हित n_bmps;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	पूर्णांक f_p = 0;
	पूर्णांक near_bmp;
	अगर (क्रमward < 0) अणु
		क्रमward = -क्रमward;
		f_p = 1;
	पूर्ण
	n_bmps = (sbi->sb_fs_size + 0x4000 - 1) >> 14;
	अगर (near && near < sbi->sb_fs_size) अणु
		अगर ((sec = alloc_in_bmp(s, near, n, f_p ? क्रमward : क्रमward/4))) जाओ ret;
		near_bmp = near >> 14;
	पूर्ण अन्यथा near_bmp = n_bmps / 2;
	/*
	अगर (b != -1) अणु
		अगर ((sec = alloc_in_bmp(s, b<<14, n, f_p ? क्रमward : क्रमward/2))) अणु
			b &= 0x0fffffff;
			जाओ ret;
		पूर्ण
		अगर (b > 0x10000000) अगर ((sec = alloc_in_bmp(s, (b&0xfffffff)<<14, n, f_p ? क्रमward : 0))) जाओ ret;
	*/
	अगर (!f_p) अगर (क्रमward > sbi->sb_max_fwd_alloc) क्रमward = sbi->sb_max_fwd_alloc;
	less_fwd:
	क्रम (i = 0; i < n_bmps; i++) अणु
		अगर (near_bmp+i < n_bmps && ((sec = alloc_in_bmp(s, (near_bmp+i) << 14, n, क्रमward)))) अणु
			sbi->sb_c_biपंचांगap = near_bmp+i;
			जाओ ret;
		पूर्ण	
		अगर (!क्रमward) अणु
			अगर (near_bmp-i-1 >= 0 && ((sec = alloc_in_bmp(s, (near_bmp-i-1) << 14, n, क्रमward)))) अणु
				sbi->sb_c_biपंचांगap = near_bmp-i-1;
				जाओ ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (near_bmp+i >= n_bmps && ((sec = alloc_in_bmp(s, (near_bmp+i-n_bmps) << 14, n, क्रमward)))) अणु
				sbi->sb_c_biपंचांगap = near_bmp+i-n_bmps;
				जाओ ret;
			पूर्ण
		पूर्ण
		अगर (i == 1 && sbi->sb_c_biपंचांगap != -1 && ((sec = alloc_in_bmp(s, (sbi->sb_c_biपंचांगap) << 14, n, क्रमward)))) अणु
			जाओ ret;
		पूर्ण
	पूर्ण
	अगर (!f_p) अणु
		अगर (क्रमward) अणु
			sbi->sb_max_fwd_alloc = क्रमward * 3 / 4;
			क्रमward /= 2;
			जाओ less_fwd;
		पूर्ण
	पूर्ण
	sec = 0;
	ret:
	अगर (sec) अणु
		i = 0;
		करो
			hpfs_claim_alloc(s, sec + i);
		जबतक (unlikely(++i < n));
	पूर्ण
	अगर (sec && f_p) अणु
		क्रम (i = 0; i < क्रमward; i++) अणु
			अगर (!hpfs_alloc_अगर_possible(s, sec + n + i)) अणु
				hpfs_error(s, "Prealloc doesn't work! Wanted %d, allocated at %08x, can't allocate %d", क्रमward, sec, i);
				sec = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस sec;
पूर्ण

अटल secno alloc_in_dirband(काष्ठा super_block *s, secno near)
अणु
	अचिन्हित nr = near;
	secno sec;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (nr < sbi->sb_dirband_start)
		nr = sbi->sb_dirband_start;
	अगर (nr >= sbi->sb_dirband_start + sbi->sb_dirband_size)
		nr = sbi->sb_dirband_start + sbi->sb_dirband_size - 4;
	nr -= sbi->sb_dirband_start;
	nr >>= 2;
	sec = alloc_in_bmp(s, (~0x3fff) | nr, 1, 0);
	अगर (!sec) वापस 0;
	hpfs_claim_dirband_alloc(s, sec);
	वापस ((sec & 0x3fff) << 2) + sbi->sb_dirband_start;
पूर्ण

/* Alloc sector अगर it's मुक्त */

पूर्णांक hpfs_alloc_अगर_possible(काष्ठा super_block *s, secno sec)
अणु
	काष्ठा quad_buffer_head qbh;
	__le32 *bmp;
	अगर (!(bmp = hpfs_map_biपंचांगap(s, sec >> 14, &qbh, "aip"))) जाओ end;
	अगर (le32_to_cpu(bmp[(sec & 0x3fff) >> 5]) & (1 << (sec & 0x1f))) अणु
		bmp[(sec & 0x3fff) >> 5] &= cpu_to_le32(~(1 << (sec & 0x1f)));
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		hpfs_claim_alloc(s, sec);
		वापस 1;
	पूर्ण
	hpfs_brअन्यथा4(&qbh);
	end:
	वापस 0;
पूर्ण

/* Free sectors in biपंचांगaps */

व्योम hpfs_मुक्त_sectors(काष्ठा super_block *s, secno sec, अचिन्हित n)
अणु
	काष्ठा quad_buffer_head qbh;
	__le32 *bmp;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	/*pr_info("2 - ");*/
	अगर (!n) वापस;
	अगर (sec < 0x12) अणु
		hpfs_error(s, "Trying to free reserved sector %08x", sec);
		वापस;
	पूर्ण
	sbi->sb_max_fwd_alloc += n > 0xffff ? 0xffff : n;
	अगर (sbi->sb_max_fwd_alloc > 0xffffff) sbi->sb_max_fwd_alloc = 0xffffff;
	new_map:
	अगर (!(bmp = hpfs_map_biपंचांगap(s, sec >> 14, &qbh, "free"))) अणु
		वापस;
	पूर्ण	
	new_tst:
	अगर ((le32_to_cpu(bmp[(sec & 0x3fff) >> 5]) >> (sec & 0x1f) & 1)) अणु
		hpfs_error(s, "sector %08x not allocated", sec);
		hpfs_brअन्यथा4(&qbh);
		वापस;
	पूर्ण
	bmp[(sec & 0x3fff) >> 5] |= cpu_to_le32(1 << (sec & 0x1f));
	hpfs_claim_मुक्त(s, sec);
	अगर (!--n) अणु
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		वापस;
	पूर्ण	
	अगर (!(++sec & 0x3fff)) अणु
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		जाओ new_map;
	पूर्ण
	जाओ new_tst;
पूर्ण

/*
 * Check अगर there are at least n मुक्त dnodes on the fileप्रणाली.
 * Called beक्रमe adding to dnode. If we run out of space जबतक
 * splitting dnodes, it would corrupt dnode tree.
 */

पूर्णांक hpfs_check_मुक्त_dnodes(काष्ठा super_block *s, पूर्णांक n)
अणु
	पूर्णांक n_bmps = (hpfs_sb(s)->sb_fs_size + 0x4000 - 1) >> 14;
	पूर्णांक b = hpfs_sb(s)->sb_c_biपंचांगap & 0x0fffffff;
	पूर्णांक i, j;
	__le32 *bmp;
	काष्ठा quad_buffer_head qbh;
	अगर ((bmp = hpfs_map_dnode_biपंचांगap(s, &qbh))) अणु
		क्रम (j = 0; j < 512; j++) अणु
			अचिन्हित k;
			अगर (!le32_to_cpu(bmp[j])) जारी;
			क्रम (k = le32_to_cpu(bmp[j]); k; k >>= 1) अगर (k & 1) अगर (!--n) अणु
				hpfs_brअन्यथा4(&qbh);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	hpfs_brअन्यथा4(&qbh);
	i = 0;
	अगर (hpfs_sb(s)->sb_c_biपंचांगap != -1) अणु
		bmp = hpfs_map_biपंचांगap(s, b, &qbh, "chkdn1");
		जाओ chk_bmp;
	पूर्ण
	chk_next:
	अगर (i == b) i++;
	अगर (i >= n_bmps) वापस 1;
	bmp = hpfs_map_biपंचांगap(s, i, &qbh, "chkdn2");
	chk_bmp:
	अगर (bmp) अणु
		क्रम (j = 0; j < 512; j++) अणु
			u32 k;
			अगर (!le32_to_cpu(bmp[j])) जारी;
			क्रम (k = 0xf; k; k <<= 4)
				अगर ((le32_to_cpu(bmp[j]) & k) == k) अणु
					अगर (!--n) अणु
						hpfs_brअन्यथा4(&qbh);
						वापस 0;
					पूर्ण
				पूर्ण
		पूर्ण
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
	i++;
	जाओ chk_next;
पूर्ण

व्योम hpfs_मुक्त_dnode(काष्ठा super_block *s, dnode_secno dno)
अणु
	अगर (hpfs_sb(s)->sb_chk) अगर (dno & 3) अणु
		hpfs_error(s, "hpfs_free_dnode: dnode %08x not aligned", dno);
		वापस;
	पूर्ण
	अगर (dno < hpfs_sb(s)->sb_dirband_start ||
	    dno >= hpfs_sb(s)->sb_dirband_start + hpfs_sb(s)->sb_dirband_size) अणु
		hpfs_मुक्त_sectors(s, dno, 4);
	पूर्ण अन्यथा अणु
		काष्ठा quad_buffer_head qbh;
		__le32 *bmp;
		अचिन्हित ssec = (dno - hpfs_sb(s)->sb_dirband_start) / 4;
		अगर (!(bmp = hpfs_map_dnode_biपंचांगap(s, &qbh))) अणु
			वापस;
		पूर्ण
		bmp[ssec >> 5] |= cpu_to_le32(1 << (ssec & 0x1f));
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		hpfs_claim_dirband_मुक्त(s, dno);
	पूर्ण
पूर्ण

काष्ठा dnode *hpfs_alloc_dnode(काष्ठा super_block *s, secno near,
			 dnode_secno *dno, काष्ठा quad_buffer_head *qbh)
अणु
	काष्ठा dnode *d;
	अगर (hpfs_get_मुक्त_dnodes(s) > FREE_DNODES_ADD) अणु
		अगर (!(*dno = alloc_in_dirband(s, near)))
			अगर (!(*dno = hpfs_alloc_sector(s, near, 4, 0))) वापस शून्य;
	पूर्ण अन्यथा अणु
		अगर (!(*dno = hpfs_alloc_sector(s, near, 4, 0)))
			अगर (!(*dno = alloc_in_dirband(s, near))) वापस शून्य;
	पूर्ण
	अगर (!(d = hpfs_get_4sectors(s, *dno, qbh))) अणु
		hpfs_मुक्त_dnode(s, *dno);
		वापस शून्य;
	पूर्ण
	स_रखो(d, 0, 2048);
	d->magic = cpu_to_le32(DNODE_MAGIC);
	d->first_मुक्त = cpu_to_le32(52);
	d->dirent[0] = 32;
	d->dirent[2] = 8;
	d->dirent[30] = 1;
	d->dirent[31] = 255;
	d->self = cpu_to_le32(*dno);
	वापस d;
पूर्ण

काष्ठा fnode *hpfs_alloc_fnode(काष्ठा super_block *s, secno near, fnode_secno *fno,
			  काष्ठा buffer_head **bh)
अणु
	काष्ठा fnode *f;
	अगर (!(*fno = hpfs_alloc_sector(s, near, 1, FNODE_ALLOC_FWD))) वापस शून्य;
	अगर (!(f = hpfs_get_sector(s, *fno, bh))) अणु
		hpfs_मुक्त_sectors(s, *fno, 1);
		वापस शून्य;
	पूर्ण	
	स_रखो(f, 0, 512);
	f->magic = cpu_to_le32(FNODE_MAGIC);
	f->ea_offs = cpu_to_le16(0xc4);
	f->btree.n_मुक्त_nodes = 8;
	f->btree.first_मुक्त = cpu_to_le16(8);
	वापस f;
पूर्ण

काष्ठा anode *hpfs_alloc_anode(काष्ठा super_block *s, secno near, anode_secno *ano,
			  काष्ठा buffer_head **bh)
अणु
	काष्ठा anode *a;
	अगर (!(*ano = hpfs_alloc_sector(s, near, 1, ANODE_ALLOC_FWD))) वापस शून्य;
	अगर (!(a = hpfs_get_sector(s, *ano, bh))) अणु
		hpfs_मुक्त_sectors(s, *ano, 1);
		वापस शून्य;
	पूर्ण
	स_रखो(a, 0, 512);
	a->magic = cpu_to_le32(ANODE_MAGIC);
	a->self = cpu_to_le32(*ano);
	a->btree.n_मुक्त_nodes = 40;
	a->btree.n_used_nodes = 0;
	a->btree.first_मुक्त = cpu_to_le16(8);
	वापस a;
पूर्ण

अटल अचिन्हित find_run(__le32 *bmp, अचिन्हित *idx)
अणु
	अचिन्हित len;
	जबतक (tstbits(bmp, *idx, 1)) अणु
		(*idx)++;
		अगर (unlikely(*idx >= 0x4000))
			वापस 0;
	पूर्ण
	len = 1;
	जबतक (!tstbits(bmp, *idx + len, 1))
		len++;
	वापस len;
पूर्ण

अटल पूर्णांक करो_trim(काष्ठा super_block *s, secno start, अचिन्हित len, secno limit_start, secno limit_end, अचिन्हित minlen, अचिन्हित *result)
अणु
	पूर्णांक err;
	secno end;
	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;
	end = start + len;
	अगर (start < limit_start)
		start = limit_start;
	अगर (end > limit_end)
		end = limit_end;
	अगर (start >= end)
		वापस 0;
	अगर (end - start < minlen)
		वापस 0;
	err = sb_issue_discard(s, start, end - start, GFP_NOFS, 0);
	अगर (err)
		वापस err;
	*result += end - start;
	वापस 0;
पूर्ण

पूर्णांक hpfs_trim_fs(काष्ठा super_block *s, u64 start, u64 end, u64 minlen, अचिन्हित *result)
अणु
	पूर्णांक err = 0;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अचिन्हित idx, len, start_bmp, end_bmp;
	__le32 *bmp;
	काष्ठा quad_buffer_head qbh;

	*result = 0;
	अगर (!end || end > sbi->sb_fs_size)
		end = sbi->sb_fs_size;
	अगर (start >= sbi->sb_fs_size)
		वापस 0;
	अगर (minlen > 0x4000)
		वापस 0;
	अगर (start < sbi->sb_dirband_start + sbi->sb_dirband_size && end > sbi->sb_dirband_start) अणु
		hpfs_lock(s);
		अगर (sb_rकरोnly(s)) अणु
			err = -EROFS;
			जाओ unlock_1;
		पूर्ण
		अगर (!(bmp = hpfs_map_dnode_biपंचांगap(s, &qbh))) अणु
			err = -EIO;
			जाओ unlock_1;
		पूर्ण
		idx = 0;
		जबतक ((len = find_run(bmp, &idx)) && !err) अणु
			err = करो_trim(s, sbi->sb_dirband_start + idx * 4, len * 4, start, end, minlen, result);
			idx += len;
		पूर्ण
		hpfs_brअन्यथा4(&qbh);
unlock_1:
		hpfs_unlock(s);
	पूर्ण
	start_bmp = start >> 14;
	end_bmp = (end + 0x3fff) >> 14;
	जबतक (start_bmp < end_bmp && !err) अणु
		hpfs_lock(s);
		अगर (sb_rकरोnly(s)) अणु
			err = -EROFS;
			जाओ unlock_2;
		पूर्ण
		अगर (!(bmp = hpfs_map_biपंचांगap(s, start_bmp, &qbh, "trim"))) अणु
			err = -EIO;
			जाओ unlock_2;
		पूर्ण
		idx = 0;
		जबतक ((len = find_run(bmp, &idx)) && !err) अणु
			err = करो_trim(s, (start_bmp << 14) + idx, len, start, end, minlen, result);
			idx += len;
		पूर्ण
		hpfs_brअन्यथा4(&qbh);
unlock_2:
		hpfs_unlock(s);
		start_bmp++;
	पूर्ण
	वापस err;
पूर्ण
