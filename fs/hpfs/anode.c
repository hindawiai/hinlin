<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/anode.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  handling HPFS anode tree that contains file allocation info
 */

#समावेश "hpfs_fn.h"

/* Find a sector in allocation tree */

secno hpfs_bplus_lookup(काष्ठा super_block *s, काष्ठा inode *inode,
		   काष्ठा bplus_header *btree, अचिन्हित sec,
		   काष्ठा buffer_head *bh)
अणु
	anode_secno a = -1;
	काष्ठा anode *anode;
	पूर्णांक i;
	पूर्णांक c1, c2 = 0;
	go_करोwn:
	अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_stop_cycles(s, a, &c1, &c2, "hpfs_bplus_lookup")) वापस -1;
	अगर (bp_पूर्णांकernal(btree)) अणु
		क्रम (i = 0; i < btree->n_used_nodes; i++)
			अगर (le32_to_cpu(btree->u.पूर्णांकernal[i].file_secno) > sec) अणु
				a = le32_to_cpu(btree->u.पूर्णांकernal[i].करोwn);
				brअन्यथा(bh);
				अगर (!(anode = hpfs_map_anode(s, a, &bh))) वापस -1;
				btree = &anode->btree;
				जाओ go_करोwn;
			पूर्ण
		hpfs_error(s, "sector %08x not found in internal anode %08x", sec, a);
		brअन्यथा(bh);
		वापस -1;
	पूर्ण
	क्रम (i = 0; i < btree->n_used_nodes; i++)
		अगर (le32_to_cpu(btree->u.बाह्यal[i].file_secno) <= sec &&
		    le32_to_cpu(btree->u.बाह्यal[i].file_secno) + le32_to_cpu(btree->u.बाह्यal[i].length) > sec) अणु
			a = le32_to_cpu(btree->u.बाह्यal[i].disk_secno) + sec - le32_to_cpu(btree->u.बाह्यal[i].file_secno);
			अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_chk_sectors(s, a, 1, "data")) अणु
				brअन्यथा(bh);
				वापस -1;
			पूर्ण
			अगर (inode) अणु
				काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
				hpfs_inode->i_file_sec = le32_to_cpu(btree->u.बाह्यal[i].file_secno);
				hpfs_inode->i_disk_sec = le32_to_cpu(btree->u.बाह्यal[i].disk_secno);
				hpfs_inode->i_n_secs = le32_to_cpu(btree->u.बाह्यal[i].length);
			पूर्ण
			brअन्यथा(bh);
			वापस a;
		पूर्ण
	hpfs_error(s, "sector %08x not found in external anode %08x", sec, a);
	brअन्यथा(bh);
	वापस -1;
पूर्ण

/* Add a sector to tree */

secno hpfs_add_sector_to_btree(काष्ठा super_block *s, secno node, पूर्णांक fnod, अचिन्हित fsecno)
अणु
	काष्ठा bplus_header *btree;
	काष्ठा anode *anode = शून्य, *ranode = शून्य;
	काष्ठा fnode *fnode;
	anode_secno a, na = -1, ra, up = -1;
	secno se;
	काष्ठा buffer_head *bh, *bh1, *bh2;
	पूर्णांक n;
	अचिन्हित fs;
	पूर्णांक c1, c2 = 0;
	अगर (fnod) अणु
		अगर (!(fnode = hpfs_map_fnode(s, node, &bh))) वापस -1;
		btree = &fnode->btree;
	पूर्ण अन्यथा अणु
		अगर (!(anode = hpfs_map_anode(s, node, &bh))) वापस -1;
		btree = &anode->btree;
	पूर्ण
	a = node;
	go_करोwn:
	अगर ((n = btree->n_used_nodes - 1) < -!!fnod) अणु
		hpfs_error(s, "anode %08x has no entries", a);
		brअन्यथा(bh);
		वापस -1;
	पूर्ण
	अगर (bp_पूर्णांकernal(btree)) अणु
		a = le32_to_cpu(btree->u.पूर्णांकernal[n].करोwn);
		btree->u.पूर्णांकernal[n].file_secno = cpu_to_le32(-1);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
		अगर (hpfs_sb(s)->sb_chk)
			अगर (hpfs_stop_cycles(s, a, &c1, &c2, "hpfs_add_sector_to_btree #1")) वापस -1;
		अगर (!(anode = hpfs_map_anode(s, a, &bh))) वापस -1;
		btree = &anode->btree;
		जाओ go_करोwn;
	पूर्ण
	अगर (n >= 0) अणु
		अगर (le32_to_cpu(btree->u.बाह्यal[n].file_secno) + le32_to_cpu(btree->u.बाह्यal[n].length) != fsecno) अणु
			hpfs_error(s, "allocated size %08x, trying to add sector %08x, %cnode %08x",
				le32_to_cpu(btree->u.बाह्यal[n].file_secno) + le32_to_cpu(btree->u.बाह्यal[n].length), fsecno,
				fnod?'f':'a', node);
			brअन्यथा(bh);
			वापस -1;
		पूर्ण
		अगर (hpfs_alloc_अगर_possible(s, se = le32_to_cpu(btree->u.बाह्यal[n].disk_secno) + le32_to_cpu(btree->u.बाह्यal[n].length))) अणु
			le32_add_cpu(&btree->u.बाह्यal[n].length, 1);
			mark_buffer_dirty(bh);
			brअन्यथा(bh);
			वापस se;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (fsecno) अणु
			hpfs_error(s, "empty file %08x, trying to add sector %08x", node, fsecno);
			brअन्यथा(bh);
			वापस -1;
		पूर्ण
		se = !fnod ? node : (node + 16384) & ~16383;
	पूर्ण	
	अगर (!(se = hpfs_alloc_sector(s, se, 1, fsecno*ALLOC_M>ALLOC_FWD_MAX ? ALLOC_FWD_MAX : fsecno*ALLOC_M<ALLOC_FWD_MIN ? ALLOC_FWD_MIN : fsecno*ALLOC_M))) अणु
		brअन्यथा(bh);
		वापस -1;
	पूर्ण
	fs = n < 0 ? 0 : le32_to_cpu(btree->u.बाह्यal[n].file_secno) + le32_to_cpu(btree->u.बाह्यal[n].length);
	अगर (!btree->n_मुक्त_nodes) अणु
		up = a != node ? le32_to_cpu(anode->up) : -1;
		अगर (!(anode = hpfs_alloc_anode(s, a, &na, &bh1))) अणु
			brअन्यथा(bh);
			hpfs_मुक्त_sectors(s, se, 1);
			वापस -1;
		पूर्ण
		अगर (a == node && fnod) अणु
			anode->up = cpu_to_le32(node);
			anode->btree.flags |= BP_fnode_parent;
			anode->btree.n_used_nodes = btree->n_used_nodes;
			anode->btree.first_मुक्त = btree->first_मुक्त;
			anode->btree.n_मुक्त_nodes = 40 - anode->btree.n_used_nodes;
			स_नकल(&anode->u, &btree->u, btree->n_used_nodes * 12);
			btree->flags |= BP_पूर्णांकernal;
			btree->n_मुक्त_nodes = 11;
			btree->n_used_nodes = 1;
			btree->first_मुक्त = cpu_to_le16((अक्षर *)&(btree->u.पूर्णांकernal[1]) - (अक्षर *)btree);
			btree->u.पूर्णांकernal[0].file_secno = cpu_to_le32(-1);
			btree->u.पूर्णांकernal[0].करोwn = cpu_to_le32(na);
			mark_buffer_dirty(bh);
		पूर्ण अन्यथा अगर (!(ranode = hpfs_alloc_anode(s, /*a*/0, &ra, &bh2))) अणु
			brअन्यथा(bh);
			brअन्यथा(bh1);
			hpfs_मुक्त_sectors(s, se, 1);
			hpfs_मुक्त_sectors(s, na, 1);
			वापस -1;
		पूर्ण
		brअन्यथा(bh);
		bh = bh1;
		btree = &anode->btree;
	पूर्ण
	btree->n_मुक्त_nodes--; n = btree->n_used_nodes++;
	le16_add_cpu(&btree->first_मुक्त, 12);
	btree->u.बाह्यal[n].disk_secno = cpu_to_le32(se);
	btree->u.बाह्यal[n].file_secno = cpu_to_le32(fs);
	btree->u.बाह्यal[n].length = cpu_to_le32(1);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	अगर ((a == node && fnod) || na == -1) वापस se;
	c2 = 0;
	जबतक (up != (anode_secno)-1) अणु
		काष्ठा anode *new_anode;
		अगर (hpfs_sb(s)->sb_chk)
			अगर (hpfs_stop_cycles(s, up, &c1, &c2, "hpfs_add_sector_to_btree #2")) वापस -1;
		अगर (up != node || !fnod) अणु
			अगर (!(anode = hpfs_map_anode(s, up, &bh))) वापस -1;
			btree = &anode->btree;
		पूर्ण अन्यथा अणु
			अगर (!(fnode = hpfs_map_fnode(s, up, &bh))) वापस -1;
			btree = &fnode->btree;
		पूर्ण
		अगर (btree->n_मुक्त_nodes) अणु
			btree->n_मुक्त_nodes--; n = btree->n_used_nodes++;
			le16_add_cpu(&btree->first_मुक्त, 8);
			btree->u.पूर्णांकernal[n].file_secno = cpu_to_le32(-1);
			btree->u.पूर्णांकernal[n].करोwn = cpu_to_le32(na);
			btree->u.पूर्णांकernal[n-1].file_secno = cpu_to_le32(fs);
			mark_buffer_dirty(bh);
			brअन्यथा(bh);
			brअन्यथा(bh2);
			hpfs_मुक्त_sectors(s, ra, 1);
			अगर ((anode = hpfs_map_anode(s, na, &bh))) अणु
				anode->up = cpu_to_le32(up);
				अगर (up == node && fnod)
					anode->btree.flags |= BP_fnode_parent;
				अन्यथा
					anode->btree.flags &= ~BP_fnode_parent;
				mark_buffer_dirty(bh);
				brअन्यथा(bh);
			पूर्ण
			वापस se;
		पूर्ण
		up = up != node ? le32_to_cpu(anode->up) : -1;
		btree->u.पूर्णांकernal[btree->n_used_nodes - 1].file_secno = cpu_to_le32(/*fs*/-1);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
		a = na;
		अगर ((new_anode = hpfs_alloc_anode(s, a, &na, &bh))) अणु
			anode = new_anode;
			/*anode->up = cpu_to_le32(up != -1 ? up : ra);*/
			anode->btree.flags |= BP_पूर्णांकernal;
			anode->btree.n_used_nodes = 1;
			anode->btree.n_मुक्त_nodes = 59;
			anode->btree.first_मुक्त = cpu_to_le16(16);
			anode->btree.u.पूर्णांकernal[0].करोwn = cpu_to_le32(a);
			anode->btree.u.पूर्णांकernal[0].file_secno = cpu_to_le32(-1);
			mark_buffer_dirty(bh);
			brअन्यथा(bh);
			अगर ((anode = hpfs_map_anode(s, a, &bh))) अणु
				anode->up = cpu_to_le32(na);
				mark_buffer_dirty(bh);
				brअन्यथा(bh);
			पूर्ण
		पूर्ण अन्यथा na = a;
	पूर्ण
	अगर ((anode = hpfs_map_anode(s, na, &bh))) अणु
		anode->up = cpu_to_le32(node);
		अगर (fnod)
			anode->btree.flags |= BP_fnode_parent;
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
	पूर्ण
	अगर (!fnod) अणु
		अगर (!(anode = hpfs_map_anode(s, node, &bh))) अणु
			brअन्यथा(bh2);
			वापस -1;
		पूर्ण
		btree = &anode->btree;
	पूर्ण अन्यथा अणु
		अगर (!(fnode = hpfs_map_fnode(s, node, &bh))) अणु
			brअन्यथा(bh2);
			वापस -1;
		पूर्ण
		btree = &fnode->btree;
	पूर्ण
	ranode->up = cpu_to_le32(node);
	स_नकल(&ranode->btree, btree, le16_to_cpu(btree->first_मुक्त));
	अगर (fnod)
		ranode->btree.flags |= BP_fnode_parent;
	ranode->btree.n_मुक्त_nodes = (bp_पूर्णांकernal(&ranode->btree) ? 60 : 40) - ranode->btree.n_used_nodes;
	अगर (bp_पूर्णांकernal(&ranode->btree)) क्रम (n = 0; n < ranode->btree.n_used_nodes; n++) अणु
		काष्ठा anode *unode;
		अगर ((unode = hpfs_map_anode(s, le32_to_cpu(ranode->u.पूर्णांकernal[n].करोwn), &bh1))) अणु
			unode->up = cpu_to_le32(ra);
			unode->btree.flags &= ~BP_fnode_parent;
			mark_buffer_dirty(bh1);
			brअन्यथा(bh1);
		पूर्ण
	पूर्ण
	btree->flags |= BP_पूर्णांकernal;
	btree->n_मुक्त_nodes = fnod ? 10 : 58;
	btree->n_used_nodes = 2;
	btree->first_मुक्त = cpu_to_le16((अक्षर *)&btree->u.पूर्णांकernal[2] - (अक्षर *)btree);
	btree->u.पूर्णांकernal[0].file_secno = cpu_to_le32(fs);
	btree->u.पूर्णांकernal[0].करोwn = cpu_to_le32(ra);
	btree->u.पूर्णांकernal[1].file_secno = cpu_to_le32(-1);
	btree->u.पूर्णांकernal[1].करोwn = cpu_to_le32(na);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	mark_buffer_dirty(bh2);
	brअन्यथा(bh2);
	वापस se;
पूर्ण

/*
 * Remove allocation tree. Recursion would look much nicer but
 * I want to aव्योम it because it can cause stack overflow.
 */

व्योम hpfs_हटाओ_btree(काष्ठा super_block *s, काष्ठा bplus_header *btree)
अणु
	काष्ठा bplus_header *btree1 = btree;
	काष्ठा anode *anode = शून्य;
	anode_secno ano = 0, oano;
	काष्ठा buffer_head *bh;
	पूर्णांक level = 0;
	पूर्णांक pos = 0;
	पूर्णांक i;
	पूर्णांक c1, c2 = 0;
	पूर्णांक d1, d2;
	go_करोwn:
	d2 = 0;
	जबतक (bp_पूर्णांकernal(btree1)) अणु
		ano = le32_to_cpu(btree1->u.पूर्णांकernal[pos].करोwn);
		अगर (level) brअन्यथा(bh);
		अगर (hpfs_sb(s)->sb_chk)
			अगर (hpfs_stop_cycles(s, ano, &d1, &d2, "hpfs_remove_btree #1"))
				वापस;
		अगर (!(anode = hpfs_map_anode(s, ano, &bh))) वापस;
		btree1 = &anode->btree;
		level++;
		pos = 0;
	पूर्ण
	क्रम (i = 0; i < btree1->n_used_nodes; i++)
		hpfs_मुक्त_sectors(s, le32_to_cpu(btree1->u.बाह्यal[i].disk_secno), le32_to_cpu(btree1->u.बाह्यal[i].length));
	go_up:
	अगर (!level) वापस;
	brअन्यथा(bh);
	अगर (hpfs_sb(s)->sb_chk)
		अगर (hpfs_stop_cycles(s, ano, &c1, &c2, "hpfs_remove_btree #2")) वापस;
	hpfs_मुक्त_sectors(s, ano, 1);
	oano = ano;
	ano = le32_to_cpu(anode->up);
	अगर (--level) अणु
		अगर (!(anode = hpfs_map_anode(s, ano, &bh))) वापस;
		btree1 = &anode->btree;
	पूर्ण अन्यथा btree1 = btree;
	क्रम (i = 0; i < btree1->n_used_nodes; i++) अणु
		अगर (le32_to_cpu(btree1->u.पूर्णांकernal[i].करोwn) == oano) अणु
			अगर ((pos = i + 1) < btree1->n_used_nodes)
				जाओ go_करोwn;
			अन्यथा
				जाओ go_up;
		पूर्ण
	पूर्ण
	hpfs_error(s,
		   "reference to anode %08x not found in anode %08x "
		   "(probably bad up pointer)",
		   oano, level ? ano : -1);
	अगर (level)
		brअन्यथा(bh);
पूर्ण

/* Just a wrapper around hpfs_bplus_lookup .. used क्रम पढ़ोing eas */

अटल secno anode_lookup(काष्ठा super_block *s, anode_secno a, अचिन्हित sec)
अणु
	काष्ठा anode *anode;
	काष्ठा buffer_head *bh;
	अगर (!(anode = hpfs_map_anode(s, a, &bh))) वापस -1;
	वापस hpfs_bplus_lookup(s, शून्य, &anode->btree, sec, bh);
पूर्ण

पूर्णांक hpfs_ea_पढ़ो(काष्ठा super_block *s, secno a, पूर्णांक ano, अचिन्हित pos,
	    अचिन्हित len, अक्षर *buf)
अणु
	काष्ठा buffer_head *bh;
	अक्षर *data;
	secno sec;
	अचिन्हित l;
	जबतक (len) अणु
		अगर (ano) अणु
			अगर ((sec = anode_lookup(s, a, pos >> 9)) == -1)
				वापस -1;
		पूर्ण अन्यथा sec = a + (pos >> 9);
		अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_chk_sectors(s, sec, 1, "ea #1")) वापस -1;
		अगर (!(data = hpfs_map_sector(s, sec, &bh, (len - 1) >> 9)))
			वापस -1;
		l = 0x200 - (pos & 0x1ff); अगर (l > len) l = len;
		स_नकल(buf, data + (pos & 0x1ff), l);
		brअन्यथा(bh);
		buf += l; pos += l; len -= l;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hpfs_ea_ग_लिखो(काष्ठा super_block *s, secno a, पूर्णांक ano, अचिन्हित pos,
	     अचिन्हित len, स्थिर अक्षर *buf)
अणु
	काष्ठा buffer_head *bh;
	अक्षर *data;
	secno sec;
	अचिन्हित l;
	जबतक (len) अणु
		अगर (ano) अणु
			अगर ((sec = anode_lookup(s, a, pos >> 9)) == -1)
				वापस -1;
		पूर्ण अन्यथा sec = a + (pos >> 9);
		अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_chk_sectors(s, sec, 1, "ea #2")) वापस -1;
		अगर (!(data = hpfs_map_sector(s, sec, &bh, (len - 1) >> 9)))
			वापस -1;
		l = 0x200 - (pos & 0x1ff); अगर (l > len) l = len;
		स_नकल(data + (pos & 0x1ff), buf, l);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
		buf += l; pos += l; len -= l;
	पूर्ण
	वापस 0;
पूर्ण

व्योम hpfs_ea_हटाओ(काष्ठा super_block *s, secno a, पूर्णांक ano, अचिन्हित len)
अणु
	काष्ठा anode *anode;
	काष्ठा buffer_head *bh;
	अगर (ano) अणु
		अगर (!(anode = hpfs_map_anode(s, a, &bh))) वापस;
		hpfs_हटाओ_btree(s, &anode->btree);
		brअन्यथा(bh);
		hpfs_मुक्त_sectors(s, a, 1);
	पूर्ण अन्यथा hpfs_मुक्त_sectors(s, a, (len + 511) >> 9);
पूर्ण

/* Truncate allocation tree. Doesn't join anodes - I hope it doesn't matter */

व्योम hpfs_truncate_btree(काष्ठा super_block *s, secno f, पूर्णांक fno, अचिन्हित secs)
अणु
	काष्ठा fnode *fnode;
	काष्ठा anode *anode;
	काष्ठा buffer_head *bh;
	काष्ठा bplus_header *btree;
	anode_secno node = f;
	पूर्णांक i, j, nodes;
	पूर्णांक c1, c2 = 0;
	अगर (fno) अणु
		अगर (!(fnode = hpfs_map_fnode(s, f, &bh))) वापस;
		btree = &fnode->btree;
	पूर्ण अन्यथा अणु
		अगर (!(anode = hpfs_map_anode(s, f, &bh))) वापस;
		btree = &anode->btree;
	पूर्ण
	अगर (!secs) अणु
		hpfs_हटाओ_btree(s, btree);
		अगर (fno) अणु
			btree->n_मुक्त_nodes = 8;
			btree->n_used_nodes = 0;
			btree->first_मुक्त = cpu_to_le16(8);
			btree->flags &= ~BP_पूर्णांकernal;
			mark_buffer_dirty(bh);
		पूर्ण अन्यथा hpfs_मुक्त_sectors(s, f, 1);
		brअन्यथा(bh);
		वापस;
	पूर्ण
	जबतक (bp_पूर्णांकernal(btree)) अणु
		nodes = btree->n_used_nodes + btree->n_मुक्त_nodes;
		क्रम (i = 0; i < btree->n_used_nodes; i++)
			अगर (le32_to_cpu(btree->u.पूर्णांकernal[i].file_secno) >= secs) जाओ f;
		brअन्यथा(bh);
		hpfs_error(s, "internal btree %08x doesn't end with -1", node);
		वापस;
		f:
		क्रम (j = i + 1; j < btree->n_used_nodes; j++)
			hpfs_ea_हटाओ(s, le32_to_cpu(btree->u.पूर्णांकernal[j].करोwn), 1, 0);
		btree->n_used_nodes = i + 1;
		btree->n_मुक्त_nodes = nodes - btree->n_used_nodes;
		btree->first_मुक्त = cpu_to_le16(8 + 8 * btree->n_used_nodes);
		mark_buffer_dirty(bh);
		अगर (btree->u.पूर्णांकernal[i].file_secno == cpu_to_le32(secs)) अणु
			brअन्यथा(bh);
			वापस;
		पूर्ण
		node = le32_to_cpu(btree->u.पूर्णांकernal[i].करोwn);
		brअन्यथा(bh);
		अगर (hpfs_sb(s)->sb_chk)
			अगर (hpfs_stop_cycles(s, node, &c1, &c2, "hpfs_truncate_btree"))
				वापस;
		अगर (!(anode = hpfs_map_anode(s, node, &bh))) वापस;
		btree = &anode->btree;
	पूर्ण	
	nodes = btree->n_used_nodes + btree->n_मुक्त_nodes;
	क्रम (i = 0; i < btree->n_used_nodes; i++)
		अगर (le32_to_cpu(btree->u.बाह्यal[i].file_secno) + le32_to_cpu(btree->u.बाह्यal[i].length) >= secs) जाओ ff;
	brअन्यथा(bh);
	वापस;
	ff:
	अगर (secs <= le32_to_cpu(btree->u.बाह्यal[i].file_secno)) अणु
		hpfs_error(s, "there is an allocation error in file %08x, sector %08x", f, secs);
		अगर (i) i--;
	पूर्ण
	अन्यथा अगर (le32_to_cpu(btree->u.बाह्यal[i].file_secno) + le32_to_cpu(btree->u.बाह्यal[i].length) > secs) अणु
		hpfs_मुक्त_sectors(s, le32_to_cpu(btree->u.बाह्यal[i].disk_secno) + secs -
			le32_to_cpu(btree->u.बाह्यal[i].file_secno), le32_to_cpu(btree->u.बाह्यal[i].length)
			- secs + le32_to_cpu(btree->u.बाह्यal[i].file_secno)); /* I hope gcc optimizes this :-) */
		btree->u.बाह्यal[i].length = cpu_to_le32(secs - le32_to_cpu(btree->u.बाह्यal[i].file_secno));
	पूर्ण
	क्रम (j = i + 1; j < btree->n_used_nodes; j++)
		hpfs_मुक्त_sectors(s, le32_to_cpu(btree->u.बाह्यal[j].disk_secno), le32_to_cpu(btree->u.बाह्यal[j].length));
	btree->n_used_nodes = i + 1;
	btree->n_मुक्त_nodes = nodes - btree->n_used_nodes;
	btree->first_मुक्त = cpu_to_le16(8 + 12 * btree->n_used_nodes);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
पूर्ण

/* Remove file or directory and it's eas - note that directory must
   be empty when this is called. */

व्योम hpfs_हटाओ_fnode(काष्ठा super_block *s, fnode_secno fno)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	काष्ठा extended_attribute *ea;
	काष्ठा extended_attribute *ea_end;
	अगर (!(fnode = hpfs_map_fnode(s, fno, &bh))) वापस;
	अगर (!fnode_is_dir(fnode)) hpfs_हटाओ_btree(s, &fnode->btree);
	अन्यथा hpfs_हटाओ_dtree(s, le32_to_cpu(fnode->u.बाह्यal[0].disk_secno));
	ea_end = fnode_end_ea(fnode);
	क्रम (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		अगर (ea_indirect(ea))
			hpfs_ea_हटाओ(s, ea_sec(ea), ea_in_anode(ea), ea_len(ea));
	hpfs_ea_ext_हटाओ(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l));
	brअन्यथा(bh);
	hpfs_मुक्त_sectors(s, fno, 1);
पूर्ण
