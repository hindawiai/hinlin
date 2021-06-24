<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/dnode.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  handling directory dnode tree - adding, deleteing & searching क्रम dirents
 */

#समावेश "hpfs_fn.h"

अटल loff_t get_pos(काष्ठा dnode *d, काष्ठा hpfs_dirent *fde)
अणु
	काष्ठा hpfs_dirent *de;
	काष्ठा hpfs_dirent *de_end = dnode_end_de(d);
	पूर्णांक i = 1;
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) अणु
		अगर (de == fde) वापस ((loff_t) le32_to_cpu(d->self) << 4) | (loff_t)i;
		i++;
	पूर्ण
	pr_info("%s(): not_found\n", __func__);
	वापस ((loff_t)le32_to_cpu(d->self) << 4) | (loff_t)1;
पूर्ण

पूर्णांक hpfs_add_pos(काष्ठा inode *inode, loff_t *pos)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	पूर्णांक i = 0;
	loff_t **ppos;

	अगर (hpfs_inode->i_rddir_off)
		क्रम (; hpfs_inode->i_rddir_off[i]; i++)
			अगर (hpfs_inode->i_rddir_off[i] == pos)
				वापस 0;
	अगर (!(i&0x0f)) अणु
		ppos = kदो_स्मृति_array(i + 0x11, माप(loff_t *), GFP_NOFS);
		अगर (!ppos) अणु
			pr_err("out of memory for position list\n");
			वापस -ENOMEM;
		पूर्ण
		अगर (hpfs_inode->i_rddir_off) अणु
			स_नकल(ppos, hpfs_inode->i_rddir_off, i * माप(loff_t));
			kमुक्त(hpfs_inode->i_rddir_off);
		पूर्ण
		hpfs_inode->i_rddir_off = ppos;
	पूर्ण
	hpfs_inode->i_rddir_off[i] = pos;
	hpfs_inode->i_rddir_off[i + 1] = शून्य;
	वापस 0;
पूर्ण

व्योम hpfs_del_pos(काष्ठा inode *inode, loff_t *pos)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	loff_t **i, **j;

	अगर (!hpfs_inode->i_rddir_off) जाओ not_f;
	क्रम (i = hpfs_inode->i_rddir_off; *i; i++) अगर (*i == pos) जाओ fnd;
	जाओ not_f;
	fnd:
	क्रम (j = i + 1; *j; j++) ;
	*i = *(j - 1);
	*(j - 1) = शून्य;
	अगर (j - 1 == hpfs_inode->i_rddir_off) अणु
		kमुक्त(hpfs_inode->i_rddir_off);
		hpfs_inode->i_rddir_off = शून्य;
	पूर्ण
	वापस;
	not_f:
	/*pr_warn("position pointer %p->%08x not found\n",
		  pos, (पूर्णांक)*pos);*/
	वापस;
पूर्ण

अटल व्योम क्रम_all_poss(काष्ठा inode *inode, व्योम (*f)(loff_t *, loff_t, loff_t),
			 loff_t p1, loff_t p2)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	loff_t **i;

	अगर (!hpfs_inode->i_rddir_off) वापस;
	क्रम (i = hpfs_inode->i_rddir_off; *i; i++) (*f)(*i, p1, p2);
	वापस;
पूर्ण

अटल व्योम hpfs_pos_subst(loff_t *p, loff_t f, loff_t t)
अणु
	अगर (*p == f) *p = t;
पूर्ण

/*व्योम hpfs_hpfs_pos_substd(loff_t *p, loff_t f, loff_t t)
अणु
	अगर ((*p & ~0x3f) == (f & ~0x3f)) *p = (t & ~0x3f) | (*p & 0x3f);
पूर्ण*/

अटल व्योम hpfs_pos_ins(loff_t *p, loff_t d, loff_t c)
अणु
	अगर ((*p & ~0x3f) == (d & ~0x3f) && (*p & 0x3f) >= (d & 0x3f)) अणु
		पूर्णांक n = (*p & 0x3f) + c;
		अगर (n > 0x3f)
			pr_err("%s(): %08x + %d\n",
				__func__, (पूर्णांक)*p, (पूर्णांक)c >> 8);
		अन्यथा
			*p = (*p & ~0x3f) | n;
	पूर्ण
पूर्ण

अटल व्योम hpfs_pos_del(loff_t *p, loff_t d, loff_t c)
अणु
	अगर ((*p & ~0x3f) == (d & ~0x3f) && (*p & 0x3f) >= (d & 0x3f)) अणु
		पूर्णांक n = (*p & 0x3f) - c;
		अगर (n < 1)
			pr_err("%s(): %08x - %d\n",
				__func__, (पूर्णांक)*p, (पूर्णांक)c >> 8);
		अन्यथा
			*p = (*p & ~0x3f) | n;
	पूर्ण
पूर्ण

अटल काष्ठा hpfs_dirent *dnode_pre_last_de(काष्ठा dnode *d)
अणु
	काष्ठा hpfs_dirent *de, *de_end, *dee = शून्य, *deee = शून्य;
	de_end = dnode_end_de(d);
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) अणु
		deee = dee; dee = de;
	पूर्ण	
	वापस deee;
पूर्ण

अटल काष्ठा hpfs_dirent *dnode_last_de(काष्ठा dnode *d)
अणु
	काष्ठा hpfs_dirent *de, *de_end, *dee = शून्य;
	de_end = dnode_end_de(d);
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) अणु
		dee = de;
	पूर्ण	
	वापस dee;
पूर्ण

अटल व्योम set_last_poपूर्णांकer(काष्ठा super_block *s, काष्ठा dnode *d, dnode_secno ptr)
अणु
	काष्ठा hpfs_dirent *de;
	अगर (!(de = dnode_last_de(d))) अणु
		hpfs_error(s, "set_last_pointer: empty dnode %08x", le32_to_cpu(d->self));
		वापस;
	पूर्ण
	अगर (hpfs_sb(s)->sb_chk) अणु
		अगर (de->करोwn) अणु
			hpfs_error(s, "set_last_pointer: dnode %08x has already last pointer %08x",
				le32_to_cpu(d->self), de_करोwn_poपूर्णांकer(de));
			वापस;
		पूर्ण
		अगर (le16_to_cpu(de->length) != 32) अणु
			hpfs_error(s, "set_last_pointer: bad last dirent in dnode %08x", le32_to_cpu(d->self));
			वापस;
		पूर्ण
	पूर्ण
	अगर (ptr) अणु
		le32_add_cpu(&d->first_मुक्त, 4);
		अगर (le32_to_cpu(d->first_मुक्त) > 2048) अणु
			hpfs_error(s, "set_last_pointer: too long dnode %08x", le32_to_cpu(d->self));
			le32_add_cpu(&d->first_मुक्त, -4);
			वापस;
		पूर्ण
		de->length = cpu_to_le16(36);
		de->करोwn = 1;
		*(__le32 *)((अक्षर *)de + 32) = cpu_to_le32(ptr);
	पूर्ण
पूर्ण

/* Add an entry to dnode and करोn't care अगर it grows over 2048 bytes */

काष्ठा hpfs_dirent *hpfs_add_de(काष्ठा super_block *s, काष्ठा dnode *d,
				स्थिर अचिन्हित अक्षर *name,
				अचिन्हित namelen, secno करोwn_ptr)
अणु
	काष्ठा hpfs_dirent *de;
	काष्ठा hpfs_dirent *de_end = dnode_end_de(d);
	अचिन्हित d_size = de_size(namelen, करोwn_ptr);
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) अणु
		पूर्णांक c = hpfs_compare_names(s, name, namelen, de->name, de->namelen, de->last);
		अगर (!c) अणु
			hpfs_error(s, "name (%c,%d) already exists in dnode %08x", *name, namelen, le32_to_cpu(d->self));
			वापस शून्य;
		पूर्ण
		अगर (c < 0) अवरोध;
	पूर्ण
	स_हटाओ((अक्षर *)de + d_size, de, (अक्षर *)de_end - (अक्षर *)de);
	स_रखो(de, 0, d_size);
	अगर (करोwn_ptr) अणु
		*(__le32 *)((अक्षर *)de + d_size - 4) = cpu_to_le32(करोwn_ptr);
		de->करोwn = 1;
	पूर्ण
	de->length = cpu_to_le16(d_size);
	de->not_8x3 = hpfs_is_name_दीर्घ(name, namelen);
	de->namelen = namelen;
	स_नकल(de->name, name, namelen);
	le32_add_cpu(&d->first_मुक्त, d_size);
	वापस de;
पूर्ण

/* Delete dirent and करोn't care about its subtree */

अटल व्योम hpfs_delete_de(काष्ठा super_block *s, काष्ठा dnode *d,
			   काष्ठा hpfs_dirent *de)
अणु
	अगर (de->last) अणु
		hpfs_error(s, "attempt to delete last dirent in dnode %08x", le32_to_cpu(d->self));
		वापस;
	पूर्ण
	d->first_मुक्त = cpu_to_le32(le32_to_cpu(d->first_मुक्त) - le16_to_cpu(de->length));
	स_हटाओ(de, de_next_de(de), le32_to_cpu(d->first_मुक्त) + (अक्षर *)d - (अक्षर *)de);
पूर्ण

अटल व्योम fix_up_ptrs(काष्ठा super_block *s, काष्ठा dnode *d)
अणु
	काष्ठा hpfs_dirent *de;
	काष्ठा hpfs_dirent *de_end = dnode_end_de(d);
	dnode_secno dno = le32_to_cpu(d->self);
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de))
		अगर (de->करोwn) अणु
			काष्ठा quad_buffer_head qbh;
			काष्ठा dnode *dd;
			अगर ((dd = hpfs_map_dnode(s, de_करोwn_poपूर्णांकer(de), &qbh))) अणु
				अगर (le32_to_cpu(dd->up) != dno || dd->root_dnode) अणु
					dd->up = cpu_to_le32(dno);
					dd->root_dnode = 0;
					hpfs_mark_4buffers_dirty(&qbh);
				पूर्ण
				hpfs_brअन्यथा4(&qbh);
			पूर्ण
		पूर्ण
पूर्ण

/* Add an entry to dnode and करो dnode splitting अगर required */

अटल पूर्णांक hpfs_add_to_dnode(काष्ठा inode *i, dnode_secno dno,
			     स्थिर अचिन्हित अक्षर *name, अचिन्हित namelen,
			     काष्ठा hpfs_dirent *new_de, dnode_secno करोwn_ptr)
अणु
	काष्ठा quad_buffer_head qbh, qbh1, qbh2;
	काष्ठा dnode *d, *ad, *rd, *nd = शून्य;
	dnode_secno adno, rdno;
	काष्ठा hpfs_dirent *de;
	काष्ठा hpfs_dirent nde;
	अचिन्हित अक्षर *nname;
	पूर्णांक h;
	पूर्णांक pos;
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	पूर्णांक c1, c2 = 0;
	अगर (!(nname = kदो_स्मृति(256, GFP_NOFS))) अणु
		pr_err("out of memory, can't add to dnode\n");
		वापस 1;
	पूर्ण
	go_up:
	अगर (namelen >= 256) अणु
		hpfs_error(i->i_sb, "%s(): namelen == %d", __func__, namelen);
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 1;
	पूर्ण
	अगर (!(d = hpfs_map_dnode(i->i_sb, dno, &qbh))) अणु
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 1;
	पूर्ण
	go_up_a:
	अगर (hpfs_sb(i->i_sb)->sb_chk)
		अगर (hpfs_stop_cycles(i->i_sb, dno, &c1, &c2, "hpfs_add_to_dnode")) अणु
			hpfs_brअन्यथा4(&qbh);
			kमुक्त(nd);
			kमुक्त(nname);
			वापस 1;
		पूर्ण
	अगर (le32_to_cpu(d->first_मुक्त) + de_size(namelen, करोwn_ptr) <= 2048) अणु
		loff_t t;
		copy_de(de=hpfs_add_de(i->i_sb, d, name, namelen, करोwn_ptr), new_de);
		t = get_pos(d, de);
		क्रम_all_poss(i, hpfs_pos_ins, t, 1);
		क्रम_all_poss(i, hpfs_pos_subst, 4, t);
		क्रम_all_poss(i, hpfs_pos_subst, 5, t + 1);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 0;
	पूर्ण
	अगर (!nd) अगर (!(nd = kदो_स्मृति(0x924, GFP_NOFS))) अणु
		/* 0x924 is a max size of dnode after adding a dirent with
		   max name length. We alloc this only once. There must
		   not be any error जबतक splitting dnodes, otherwise the
		   whole directory, not only file we're adding, would
		   be lost. */
		pr_err("out of memory for dnode splitting\n");
		hpfs_brअन्यथा4(&qbh);
		kमुक्त(nname);
		वापस 1;
	पूर्ण	
	स_नकल(nd, d, le32_to_cpu(d->first_मुक्त));
	copy_de(de = hpfs_add_de(i->i_sb, nd, name, namelen, करोwn_ptr), new_de);
	क्रम_all_poss(i, hpfs_pos_ins, get_pos(nd, de), 1);
	h = ((अक्षर *)dnode_last_de(nd) - (अक्षर *)nd) / 2 + 10;
	अगर (!(ad = hpfs_alloc_dnode(i->i_sb, le32_to_cpu(d->up), &adno, &qbh1))) अणु
		hpfs_error(i->i_sb, "unable to alloc dnode - dnode tree will be corrupted");
		hpfs_brअन्यथा4(&qbh);
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 1;
	पूर्ण
	i->i_size += 2048;
	i->i_blocks += 4;
	pos = 1;
	क्रम (de = dnode_first_de(nd); (अक्षर *)de_next_de(de) - (अक्षर *)nd < h; de = de_next_de(de)) अणु
		copy_de(hpfs_add_de(i->i_sb, ad, de->name, de->namelen, de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0), de);
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | pos, ((loff_t)adno << 4) | pos);
		pos++;
	पूर्ण
	copy_de(new_de = &nde, de);
	स_नकल(nname, de->name, de->namelen);
	name = nname;
	namelen = de->namelen;
	क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | pos, 4);
	करोwn_ptr = adno;
	set_last_poपूर्णांकer(i->i_sb, ad, de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0);
	de = de_next_de(de);
	स_हटाओ((अक्षर *)nd + 20, de, le32_to_cpu(nd->first_मुक्त) + (अक्षर *)nd - (अक्षर *)de);
	le32_add_cpu(&nd->first_मुक्त, -((अक्षर *)de - (अक्षर *)nd - 20));
	स_नकल(d, nd, le32_to_cpu(nd->first_मुक्त));
	क्रम_all_poss(i, hpfs_pos_del, (loff_t)dno << 4, pos);
	fix_up_ptrs(i->i_sb, ad);
	अगर (!d->root_dnode) अणु
		ad->up = d->up;
		dno = le32_to_cpu(ad->up);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		hpfs_mark_4buffers_dirty(&qbh1);
		hpfs_brअन्यथा4(&qbh1);
		जाओ go_up;
	पूर्ण
	अगर (!(rd = hpfs_alloc_dnode(i->i_sb, le32_to_cpu(d->up), &rdno, &qbh2))) अणु
		hpfs_error(i->i_sb, "unable to alloc dnode - dnode tree will be corrupted");
		hpfs_brअन्यथा4(&qbh);
		hpfs_brअन्यथा4(&qbh1);
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 1;
	पूर्ण
	i->i_size += 2048;
	i->i_blocks += 4;
	rd->root_dnode = 1;
	rd->up = d->up;
	अगर (!(fnode = hpfs_map_fnode(i->i_sb, le32_to_cpu(d->up), &bh))) अणु
		hpfs_मुक्त_dnode(i->i_sb, rdno);
		hpfs_brअन्यथा4(&qbh);
		hpfs_brअन्यथा4(&qbh1);
		hpfs_brअन्यथा4(&qbh2);
		kमुक्त(nd);
		kमुक्त(nname);
		वापस 1;
	पूर्ण
	fnode->u.बाह्यal[0].disk_secno = cpu_to_le32(rdno);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	hpfs_i(i)->i_dno = rdno;
	d->up = ad->up = cpu_to_le32(rdno);
	d->root_dnode = ad->root_dnode = 0;
	hpfs_mark_4buffers_dirty(&qbh);
	hpfs_brअन्यथा4(&qbh);
	hpfs_mark_4buffers_dirty(&qbh1);
	hpfs_brअन्यथा4(&qbh1);
	qbh = qbh2;
	set_last_poपूर्णांकer(i->i_sb, rd, dno);
	dno = rdno;
	d = rd;
	जाओ go_up_a;
पूर्ण

/*
 * Add an entry to directory btree.
 * I hate such crazy directory काष्ठाure.
 * It's easy to पढ़ो but terrible to ग_लिखो.
 * I wrote this directory code 4 बार.
 * I hope, now it's finally bug-मुक्त.
 */

पूर्णांक hpfs_add_dirent(काष्ठा inode *i,
		    स्थिर अचिन्हित अक्षर *name, अचिन्हित namelen,
		    काष्ठा hpfs_dirent *new_de)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	काष्ठा dnode *d;
	काष्ठा hpfs_dirent *de, *de_end;
	काष्ठा quad_buffer_head qbh;
	dnode_secno dno;
	पूर्णांक c;
	पूर्णांक c1, c2 = 0;
	dno = hpfs_inode->i_dno;
	करोwn:
	अगर (hpfs_sb(i->i_sb)->sb_chk)
		अगर (hpfs_stop_cycles(i->i_sb, dno, &c1, &c2, "hpfs_add_dirent")) वापस 1;
	अगर (!(d = hpfs_map_dnode(i->i_sb, dno, &qbh))) वापस 1;
	de_end = dnode_end_de(d);
	क्रम (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) अणु
		अगर (!(c = hpfs_compare_names(i->i_sb, name, namelen, de->name, de->namelen, de->last))) अणु
			hpfs_brअन्यथा4(&qbh);
			वापस -1;
		पूर्ण	
		अगर (c < 0) अणु
			अगर (de->करोwn) अणु
				dno = de_करोwn_poपूर्णांकer(de);
				hpfs_brअन्यथा4(&qbh);
				जाओ करोwn;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	hpfs_brअन्यथा4(&qbh);
	अगर (hpfs_check_मुक्त_dnodes(i->i_sb, FREE_DNODES_ADD)) अणु
		c = 1;
		जाओ ret;
	पूर्ण	
	c = hpfs_add_to_dnode(i, dno, name, namelen, new_de, 0);
	ret:
	वापस c;
पूर्ण

/* 
 * Find dirent with higher name in 'from' subtree and move it to 'to' dnode.
 * Return the dnode we moved from (to be checked later अगर it's empty)
 */

अटल secno move_to_top(काष्ठा inode *i, dnode_secno from, dnode_secno to)
अणु
	dnode_secno dno, ddno;
	dnode_secno chk_up = to;
	काष्ठा dnode *dnode;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de, *nde;
	पूर्णांक a;
	loff_t t;
	पूर्णांक c1, c2 = 0;
	dno = from;
	जबतक (1) अणु
		अगर (hpfs_sb(i->i_sb)->sb_chk)
			अगर (hpfs_stop_cycles(i->i_sb, dno, &c1, &c2, "move_to_top"))
				वापस 0;
		अगर (!(dnode = hpfs_map_dnode(i->i_sb, dno, &qbh))) वापस 0;
		अगर (hpfs_sb(i->i_sb)->sb_chk) अणु
			अगर (le32_to_cpu(dnode->up) != chk_up) अणु
				hpfs_error(i->i_sb, "move_to_top: up pointer from %08x should be %08x, is %08x",
					dno, chk_up, le32_to_cpu(dnode->up));
				hpfs_brअन्यथा4(&qbh);
				वापस 0;
			पूर्ण
			chk_up = dno;
		पूर्ण
		अगर (!(de = dnode_last_de(dnode))) अणु
			hpfs_error(i->i_sb, "move_to_top: dnode %08x has no last de", dno);
			hpfs_brअन्यथा4(&qbh);
			वापस 0;
		पूर्ण
		अगर (!de->करोwn) अवरोध;
		dno = de_करोwn_poपूर्णांकer(de);
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
	जबतक (!(de = dnode_pre_last_de(dnode))) अणु
		dnode_secno up = le32_to_cpu(dnode->up);
		hpfs_brअन्यथा4(&qbh);
		hpfs_मुक्त_dnode(i->i_sb, dno);
		i->i_size -= 2048;
		i->i_blocks -= 4;
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | 1, 5);
		अगर (up == to) वापस to;
		अगर (!(dnode = hpfs_map_dnode(i->i_sb, up, &qbh))) वापस 0;
		अगर (dnode->root_dnode) अणु
			hpfs_error(i->i_sb, "move_to_top: got to root_dnode while moving from %08x to %08x", from, to);
			hpfs_brअन्यथा4(&qbh);
			वापस 0;
		पूर्ण
		de = dnode_last_de(dnode);
		अगर (!de || !de->करोwn) अणु
			hpfs_error(i->i_sb, "move_to_top: dnode %08x doesn't point down to %08x", up, dno);
			hpfs_brअन्यथा4(&qbh);
			वापस 0;
		पूर्ण
		le32_add_cpu(&dnode->first_मुक्त, -4);
		le16_add_cpu(&de->length, -4);
		de->करोwn = 0;
		hpfs_mark_4buffers_dirty(&qbh);
		dno = up;
	पूर्ण
	t = get_pos(dnode, de);
	क्रम_all_poss(i, hpfs_pos_subst, t, 4);
	क्रम_all_poss(i, hpfs_pos_subst, t + 1, 5);
	अगर (!(nde = kदो_स्मृति(le16_to_cpu(de->length), GFP_NOFS))) अणु
		hpfs_error(i->i_sb, "out of memory for dirent - directory will be corrupted");
		hpfs_brअन्यथा4(&qbh);
		वापस 0;
	पूर्ण
	स_नकल(nde, de, le16_to_cpu(de->length));
	ddno = de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0;
	hpfs_delete_de(i->i_sb, dnode, de);
	set_last_poपूर्णांकer(i->i_sb, dnode, ddno);
	hpfs_mark_4buffers_dirty(&qbh);
	hpfs_brअन्यथा4(&qbh);
	a = hpfs_add_to_dnode(i, to, nde->name, nde->namelen, nde, from);
	kमुक्त(nde);
	अगर (a) वापस 0;
	वापस dno;
पूर्ण

/* 
 * Check अगर a dnode is empty and delete it from the tree
 * (chkdsk करोesn't like empty dnodes)
 */

अटल व्योम delete_empty_dnode(काष्ठा inode *i, dnode_secno dno)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	काष्ठा quad_buffer_head qbh;
	काष्ठा dnode *dnode;
	dnode_secno करोwn, up, nकरोwn;
	पूर्णांक p;
	काष्ठा hpfs_dirent *de;
	पूर्णांक c1, c2 = 0;
	try_it_again:
	अगर (hpfs_stop_cycles(i->i_sb, dno, &c1, &c2, "delete_empty_dnode")) वापस;
	अगर (!(dnode = hpfs_map_dnode(i->i_sb, dno, &qbh))) वापस;
	अगर (le32_to_cpu(dnode->first_मुक्त) > 56) जाओ end;
	अगर (le32_to_cpu(dnode->first_मुक्त) == 52 || le32_to_cpu(dnode->first_मुक्त) == 56) अणु
		काष्ठा hpfs_dirent *de_end;
		पूर्णांक root = dnode->root_dnode;
		up = le32_to_cpu(dnode->up);
		de = dnode_first_de(dnode);
		करोwn = de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0;
		अगर (hpfs_sb(i->i_sb)->sb_chk) अगर (root && !करोwn) अणु
			hpfs_error(i->i_sb, "delete_empty_dnode: root dnode %08x is empty", dno);
			जाओ end;
		पूर्ण
		hpfs_brअन्यथा4(&qbh);
		hpfs_मुक्त_dnode(i->i_sb, dno);
		i->i_size -= 2048;
		i->i_blocks -= 4;
		अगर (root) अणु
			काष्ठा fnode *fnode;
			काष्ठा buffer_head *bh;
			काष्ठा dnode *d1;
			काष्ठा quad_buffer_head qbh1;
			अगर (hpfs_sb(i->i_sb)->sb_chk)
				अगर (up != i->i_ino) अणु
					hpfs_error(i->i_sb,
						   "bad pointer to fnode, dnode %08x, pointing to %08x, should be %08lx",
						   dno, up,
						   (अचिन्हित दीर्घ)i->i_ino);
					वापस;
				पूर्ण
			अगर ((d1 = hpfs_map_dnode(i->i_sb, करोwn, &qbh1))) अणु
				d1->up = cpu_to_le32(up);
				d1->root_dnode = 1;
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brअन्यथा4(&qbh1);
			पूर्ण
			अगर ((fnode = hpfs_map_fnode(i->i_sb, up, &bh))) अणु
				fnode->u.बाह्यal[0].disk_secno = cpu_to_le32(करोwn);
				mark_buffer_dirty(bh);
				brअन्यथा(bh);
			पूर्ण
			hpfs_inode->i_dno = करोwn;
			क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | 1, (loff_t) 12);
			वापस;
		पूर्ण
		अगर (!(dnode = hpfs_map_dnode(i->i_sb, up, &qbh))) वापस;
		p = 1;
		de_end = dnode_end_de(dnode);
		क्रम (de = dnode_first_de(dnode); de < de_end; de = de_next_de(de), p++)
			अगर (de->करोwn) अगर (de_करोwn_poपूर्णांकer(de) == dno) जाओ fnd;
		hpfs_error(i->i_sb, "delete_empty_dnode: pointer to dnode %08x not found in dnode %08x", dno, up);
		जाओ end;
		fnd:
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | 1, ((loff_t)up << 4) | p);
		अगर (!करोwn) अणु
			de->करोwn = 0;
			le16_add_cpu(&de->length, -4);
			le32_add_cpu(&dnode->first_मुक्त, -4);
			स_हटाओ(de_next_de(de), (अक्षर *)de_next_de(de) + 4,
				(अक्षर *)dnode + le32_to_cpu(dnode->first_मुक्त) - (अक्षर *)de_next_de(de));
		पूर्ण अन्यथा अणु
			काष्ठा dnode *d1;
			काष्ठा quad_buffer_head qbh1;
			*(dnode_secno *) ((व्योम *) de + le16_to_cpu(de->length) - 4) = करोwn;
			अगर ((d1 = hpfs_map_dnode(i->i_sb, करोwn, &qbh1))) अणु
				d1->up = cpu_to_le32(up);
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brअन्यथा4(&qbh1);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hpfs_error(i->i_sb, "delete_empty_dnode: dnode %08x, first_free == %03x", dno, le32_to_cpu(dnode->first_मुक्त));
		जाओ end;
	पूर्ण

	अगर (!de->last) अणु
		काष्ठा hpfs_dirent *de_next = de_next_de(de);
		काष्ठा hpfs_dirent *de_cp;
		काष्ठा dnode *d1;
		काष्ठा quad_buffer_head qbh1;
		अगर (!de_next->करोwn) जाओ endm;
		nकरोwn = de_करोwn_poपूर्णांकer(de_next);
		अगर (!(de_cp = kदो_स्मृति(le16_to_cpu(de->length), GFP_NOFS))) अणु
			pr_err("out of memory for dtree balancing\n");
			जाओ endm;
		पूर्ण
		स_नकल(de_cp, de, le16_to_cpu(de->length));
		hpfs_delete_de(i->i_sb, dnode, de);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | p, 4);
		क्रम_all_poss(i, hpfs_pos_del, ((loff_t)up << 4) | p, 1);
		अगर (de_cp->करोwn) अगर ((d1 = hpfs_map_dnode(i->i_sb, de_करोwn_poपूर्णांकer(de_cp), &qbh1))) अणु
			d1->up = cpu_to_le32(nकरोwn);
			hpfs_mark_4buffers_dirty(&qbh1);
			hpfs_brअन्यथा4(&qbh1);
		पूर्ण
		hpfs_add_to_dnode(i, nकरोwn, de_cp->name, de_cp->namelen, de_cp, de_cp->करोwn ? de_करोwn_poपूर्णांकer(de_cp) : 0);
		/*pr_info("UP-TO-DNODE: %08x (ndown = %08x, down = %08x, dno = %08x)\n",
		  up, nकरोwn, करोwn, dno);*/
		dno = up;
		kमुक्त(de_cp);
		जाओ try_it_again;
	पूर्ण अन्यथा अणु
		काष्ठा hpfs_dirent *de_prev = dnode_pre_last_de(dnode);
		काष्ठा hpfs_dirent *de_cp;
		काष्ठा dnode *d1;
		काष्ठा quad_buffer_head qbh1;
		dnode_secno dlp;
		अगर (!de_prev) अणु
			hpfs_error(i->i_sb, "delete_empty_dnode: empty dnode %08x", up);
			hpfs_mark_4buffers_dirty(&qbh);
			hpfs_brअन्यथा4(&qbh);
			dno = up;
			जाओ try_it_again;
		पूर्ण
		अगर (!de_prev->करोwn) जाओ endm;
		nकरोwn = de_करोwn_poपूर्णांकer(de_prev);
		अगर ((d1 = hpfs_map_dnode(i->i_sb, nकरोwn, &qbh1))) अणु
			काष्ठा hpfs_dirent *del = dnode_last_de(d1);
			dlp = del->करोwn ? de_करोwn_poपूर्णांकer(del) : 0;
			अगर (!dlp && करोwn) अणु
				अगर (le32_to_cpu(d1->first_मुक्त) > 2044) अणु
					अगर (hpfs_sb(i->i_sb)->sb_chk >= 2) अणु
						pr_err("unbalanced dnode tree, see hpfs.txt 4 more info\n");
						pr_err("terminating balancing operation\n");
					पूर्ण
					hpfs_brअन्यथा4(&qbh1);
					जाओ endm;
				पूर्ण
				अगर (hpfs_sb(i->i_sb)->sb_chk >= 2) अणु
					pr_err("unbalanced dnode tree, see hpfs.txt 4 more info\n");
					pr_err("goin'on\n");
				पूर्ण
				le16_add_cpu(&del->length, 4);
				del->करोwn = 1;
				le32_add_cpu(&d1->first_मुक्त, 4);
			पूर्ण
			अगर (dlp && !करोwn) अणु
				le16_add_cpu(&del->length, -4);
				del->करोwn = 0;
				le32_add_cpu(&d1->first_मुक्त, -4);
			पूर्ण अन्यथा अगर (करोwn)
				*(__le32 *) ((व्योम *) del + le16_to_cpu(del->length) - 4) = cpu_to_le32(करोwn);
		पूर्ण अन्यथा जाओ endm;
		अगर (!(de_cp = kदो_स्मृति(le16_to_cpu(de_prev->length), GFP_NOFS))) अणु
			pr_err("out of memory for dtree balancing\n");
			hpfs_brअन्यथा4(&qbh1);
			जाओ endm;
		पूर्ण
		hpfs_mark_4buffers_dirty(&qbh1);
		hpfs_brअन्यथा4(&qbh1);
		स_नकल(de_cp, de_prev, le16_to_cpu(de_prev->length));
		hpfs_delete_de(i->i_sb, dnode, de_prev);
		अगर (!de_prev->करोwn) अणु
			le16_add_cpu(&de_prev->length, 4);
			de_prev->करोwn = 1;
			le32_add_cpu(&dnode->first_मुक्त, 4);
		पूर्ण
		*(__le32 *) ((व्योम *) de_prev + le16_to_cpu(de_prev->length) - 4) = cpu_to_le32(nकरोwn);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | (p - 1), 4);
		क्रम_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | p, ((loff_t)up << 4) | (p - 1));
		अगर (करोwn) अगर ((d1 = hpfs_map_dnode(i->i_sb, de_करोwn_poपूर्णांकer(de), &qbh1))) अणु
			d1->up = cpu_to_le32(nकरोwn);
			hpfs_mark_4buffers_dirty(&qbh1);
			hpfs_brअन्यथा4(&qbh1);
		पूर्ण
		hpfs_add_to_dnode(i, nकरोwn, de_cp->name, de_cp->namelen, de_cp, dlp);
		dno = up;
		kमुक्त(de_cp);
		जाओ try_it_again;
	पूर्ण
	endm:
	hpfs_mark_4buffers_dirty(&qbh);
	end:
	hpfs_brअन्यथा4(&qbh);
पूर्ण


/* Delete dirent from directory */

पूर्णांक hpfs_हटाओ_dirent(काष्ठा inode *i, dnode_secno dno, काष्ठा hpfs_dirent *de,
		       काष्ठा quad_buffer_head *qbh, पूर्णांक depth)
अणु
	काष्ठा dnode *dnode = qbh->data;
	dnode_secno करोwn = 0;
	loff_t t;
	अगर (de->first || de->last) अणु
		hpfs_error(i->i_sb, "hpfs_remove_dirent: attempt to delete first or last dirent in dnode %08x", dno);
		hpfs_brअन्यथा4(qbh);
		वापस 1;
	पूर्ण
	अगर (de->करोwn) करोwn = de_करोwn_poपूर्णांकer(de);
	अगर (depth && (de->करोwn || (de == dnode_first_de(dnode) && de_next_de(de)->last))) अणु
		अगर (hpfs_check_मुक्त_dnodes(i->i_sb, FREE_DNODES_DEL)) अणु
			hpfs_brअन्यथा4(qbh);
			वापस 2;
		पूर्ण
	पूर्ण
	क्रम_all_poss(i, hpfs_pos_del, (t = get_pos(dnode, de)) + 1, 1);
	hpfs_delete_de(i->i_sb, dnode, de);
	hpfs_mark_4buffers_dirty(qbh);
	hpfs_brअन्यथा4(qbh);
	अगर (करोwn) अणु
		dnode_secno a = move_to_top(i, करोwn, dno);
		क्रम_all_poss(i, hpfs_pos_subst, 5, t);
		अगर (a) delete_empty_dnode(i, a);
		वापस !a;
	पूर्ण
	delete_empty_dnode(i, dno);
	वापस 0;
पूर्ण

व्योम hpfs_count_dnodes(काष्ठा super_block *s, dnode_secno dno, पूर्णांक *n_dnodes,
		       पूर्णांक *n_subdirs, पूर्णांक *n_items)
अणु
	काष्ठा dnode *dnode;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	dnode_secno ptr, odno = 0;
	पूर्णांक c1, c2 = 0;
	पूर्णांक d1, d2 = 0;
	go_करोwn:
	अगर (n_dnodes) (*n_dnodes)++;
	अगर (hpfs_sb(s)->sb_chk)
		अगर (hpfs_stop_cycles(s, dno, &c1, &c2, "hpfs_count_dnodes #1")) वापस;
	ptr = 0;
	go_up:
	अगर (!(dnode = hpfs_map_dnode(s, dno, &qbh))) वापस;
	अगर (hpfs_sb(s)->sb_chk) अगर (odno && odno != -1 && le32_to_cpu(dnode->up) != odno)
		hpfs_error(s, "hpfs_count_dnodes: bad up pointer; dnode %08x, down %08x points to %08x", odno, dno, le32_to_cpu(dnode->up));
	de = dnode_first_de(dnode);
	अगर (ptr) जबतक(1) अणु
		अगर (de->करोwn) अगर (de_करोwn_poपूर्णांकer(de) == ptr) जाओ process_de;
		अगर (de->last) अणु
			hpfs_brअन्यथा4(&qbh);
			hpfs_error(s, "hpfs_count_dnodes: pointer to dnode %08x not found in dnode %08x, got here from %08x",
				ptr, dno, odno);
			वापस;
		पूर्ण
		de = de_next_de(de);
	पूर्ण
	next_de:
	अगर (de->करोwn) अणु
		odno = dno;
		dno = de_करोwn_poपूर्णांकer(de);
		hpfs_brअन्यथा4(&qbh);
		जाओ go_करोwn;
	पूर्ण
	process_de:
	अगर (!de->first && !de->last && de->directory && n_subdirs) (*n_subdirs)++;
	अगर (!de->first && !de->last && n_items) (*n_items)++;
	अगर ((de = de_next_de(de)) < dnode_end_de(dnode)) जाओ next_de;
	ptr = dno;
	dno = le32_to_cpu(dnode->up);
	अगर (dnode->root_dnode) अणु
		hpfs_brअन्यथा4(&qbh);
		वापस;
	पूर्ण
	hpfs_brअन्यथा4(&qbh);
	अगर (hpfs_sb(s)->sb_chk)
		अगर (hpfs_stop_cycles(s, ptr, &d1, &d2, "hpfs_count_dnodes #2")) वापस;
	odno = -1;
	जाओ go_up;
पूर्ण

अटल काष्ठा hpfs_dirent *map_nth_dirent(काष्ठा super_block *s, dnode_secno dno, पूर्णांक n,
					  काष्ठा quad_buffer_head *qbh, काष्ठा dnode **dn)
अणु
	पूर्णांक i;
	काष्ठा hpfs_dirent *de, *de_end;
	काष्ठा dnode *dnode;
	dnode = hpfs_map_dnode(s, dno, qbh);
	अगर (!dnode) वापस शून्य;
	अगर (dn) *dn=dnode;
	de = dnode_first_de(dnode);
	de_end = dnode_end_de(dnode);
	क्रम (i = 1; de < de_end; i++, de = de_next_de(de)) अणु
		अगर (i == n) अणु
			वापस de;
		पूर्ण	
		अगर (de->last) अवरोध;
	पूर्ण
	hpfs_brअन्यथा4(qbh);
	hpfs_error(s, "map_nth_dirent: n too high; dnode = %08x, requested %08x", dno, n);
	वापस शून्य;
पूर्ण

dnode_secno hpfs_de_as_करोwn_as_possible(काष्ठा super_block *s, dnode_secno dno)
अणु
	काष्ठा quad_buffer_head qbh;
	dnode_secno d = dno;
	dnode_secno up = 0;
	काष्ठा hpfs_dirent *de;
	पूर्णांक c1, c2 = 0;

	again:
	अगर (hpfs_sb(s)->sb_chk)
		अगर (hpfs_stop_cycles(s, d, &c1, &c2, "hpfs_de_as_down_as_possible"))
			वापस d;
	अगर (!(de = map_nth_dirent(s, d, 1, &qbh, शून्य))) वापस dno;
	अगर (hpfs_sb(s)->sb_chk)
		अगर (up && le32_to_cpu(((काष्ठा dnode *)qbh.data)->up) != up)
			hpfs_error(s, "hpfs_de_as_down_as_possible: bad up pointer; dnode %08x, down %08x points to %08x", up, d, le32_to_cpu(((काष्ठा dnode *)qbh.data)->up));
	अगर (!de->करोwn) अणु
		hpfs_brअन्यथा4(&qbh);
		वापस d;
	पूर्ण
	up = d;
	d = de_करोwn_poपूर्णांकer(de);
	hpfs_brअन्यथा4(&qbh);
	जाओ again;
पूर्ण

काष्ठा hpfs_dirent *map_pos_dirent(काष्ठा inode *inode, loff_t *posp,
				   काष्ठा quad_buffer_head *qbh)
अणु
	loff_t pos;
	अचिन्हित c;
	dnode_secno dno;
	काष्ठा hpfs_dirent *de, *d;
	काष्ठा hpfs_dirent *up_de;
	काष्ठा hpfs_dirent *end_up_de;
	काष्ठा dnode *dnode;
	काष्ठा dnode *up_dnode;
	काष्ठा quad_buffer_head qbh0;

	pos = *posp;
	dno = pos >> 6 << 2;
	pos &= 077;
	अगर (!(de = map_nth_dirent(inode->i_sb, dno, pos, qbh, &dnode)))
		जाओ bail;

	/* Going to the next dirent */
	अगर ((d = de_next_de(de)) < dnode_end_de(dnode)) अणु
		अगर (!(++*posp & 077)) अणु
			hpfs_error(inode->i_sb,
				"map_pos_dirent: pos crossed dnode boundary; pos = %08llx",
				(अचिन्हित दीर्घ दीर्घ)*posp);
			जाओ bail;
		पूर्ण
		/* We're going करोwn the tree */
		अगर (d->करोwn) अणु
			*posp = ((loff_t) hpfs_de_as_करोwn_as_possible(inode->i_sb, de_करोwn_poपूर्णांकer(d)) << 4) + 1;
		पूर्ण
	
		वापस de;
	पूर्ण

	/* Going up */
	अगर (dnode->root_dnode) जाओ bail;

	अगर (!(up_dnode = hpfs_map_dnode(inode->i_sb, le32_to_cpu(dnode->up), &qbh0)))
		जाओ bail;

	end_up_de = dnode_end_de(up_dnode);
	c = 0;
	क्रम (up_de = dnode_first_de(up_dnode); up_de < end_up_de;
	     up_de = de_next_de(up_de)) अणु
		अगर (!(++c & 077)) hpfs_error(inode->i_sb,
			"map_pos_dirent: pos crossed dnode boundary; dnode = %08x", le32_to_cpu(dnode->up));
		अगर (up_de->करोwn && de_करोwn_poपूर्णांकer(up_de) == dno) अणु
			*posp = ((loff_t) le32_to_cpu(dnode->up) << 4) + c;
			hpfs_brअन्यथा4(&qbh0);
			वापस de;
		पूर्ण
	पूर्ण
	
	hpfs_error(inode->i_sb, "map_pos_dirent: pointer to dnode %08x not found in parent dnode %08x",
		dno, le32_to_cpu(dnode->up));
	hpfs_brअन्यथा4(&qbh0);
	
	bail:
	*posp = 12;
	वापस de;
पूर्ण

/* Find a dirent in tree */

काष्ठा hpfs_dirent *map_dirent(काष्ठा inode *inode, dnode_secno dno,
			       स्थिर अचिन्हित अक्षर *name, अचिन्हित len,
			       dnode_secno *dd, काष्ठा quad_buffer_head *qbh)
अणु
	काष्ठा dnode *dnode;
	काष्ठा hpfs_dirent *de;
	काष्ठा hpfs_dirent *de_end;
	पूर्णांक c1, c2 = 0;

	अगर (!S_ISसूची(inode->i_mode)) hpfs_error(inode->i_sb, "map_dirent: not a directory\n");
	again:
	अगर (hpfs_sb(inode->i_sb)->sb_chk)
		अगर (hpfs_stop_cycles(inode->i_sb, dno, &c1, &c2, "map_dirent")) वापस शून्य;
	अगर (!(dnode = hpfs_map_dnode(inode->i_sb, dno, qbh))) वापस शून्य;
	
	de_end = dnode_end_de(dnode);
	क्रम (de = dnode_first_de(dnode); de < de_end; de = de_next_de(de)) अणु
		पूर्णांक t = hpfs_compare_names(inode->i_sb, name, len, de->name, de->namelen, de->last);
		अगर (!t) अणु
			अगर (dd) *dd = dno;
			वापस de;
		पूर्ण
		अगर (t < 0) अणु
			अगर (de->करोwn) अणु
				dno = de_करोwn_poपूर्णांकer(de);
				hpfs_brअन्यथा4(qbh);
				जाओ again;
			पूर्ण
		अवरोध;
		पूर्ण
	पूर्ण
	hpfs_brअन्यथा4(qbh);
	वापस शून्य;
पूर्ण

/*
 * Remove empty directory. In normal हालs it is only one dnode with two
 * entries, but we must handle also such obscure हालs when it's a tree
 * of empty dnodes.
 */

व्योम hpfs_हटाओ_dtree(काष्ठा super_block *s, dnode_secno dno)
अणु
	काष्ठा quad_buffer_head qbh;
	काष्ठा dnode *dnode;
	काष्ठा hpfs_dirent *de;
	dnode_secno d1, d2, rdno = dno;
	जबतक (1) अणु
		अगर (!(dnode = hpfs_map_dnode(s, dno, &qbh))) वापस;
		de = dnode_first_de(dnode);
		अगर (de->last) अणु
			अगर (de->करोwn) d1 = de_करोwn_poपूर्णांकer(de);
			अन्यथा जाओ error;
			hpfs_brअन्यथा4(&qbh);
			hpfs_मुक्त_dnode(s, dno);
			dno = d1;
		पूर्ण अन्यथा अवरोध;
	पूर्ण
	अगर (!de->first) जाओ error;
	d1 = de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0;
	de = de_next_de(de);
	अगर (!de->last) जाओ error;
	d2 = de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0;
	hpfs_brअन्यथा4(&qbh);
	hpfs_मुक्त_dnode(s, dno);
	करो अणु
		जबतक (d1) अणु
			अगर (!(dnode = hpfs_map_dnode(s, dno = d1, &qbh))) वापस;
			de = dnode_first_de(dnode);
			अगर (!de->last) जाओ error;
			d1 = de->करोwn ? de_करोwn_poपूर्णांकer(de) : 0;
			hpfs_brअन्यथा4(&qbh);
			hpfs_मुक्त_dnode(s, dno);
		पूर्ण
		d1 = d2;
		d2 = 0;
	पूर्ण जबतक (d1);
	वापस;
	error:
	hpfs_brअन्यथा4(&qbh);
	hpfs_मुक्त_dnode(s, dno);
	hpfs_error(s, "directory %08x is corrupted or not empty", rdno);
पूर्ण

/* 
 * Find dirent क्रम specअगरied fnode. Use truncated 15-अक्षर name in fnode as
 * a help क्रम searching.
 */

काष्ठा hpfs_dirent *map_fnode_dirent(काष्ठा super_block *s, fnode_secno fno,
				     काष्ठा fnode *f, काष्ठा quad_buffer_head *qbh)
अणु
	अचिन्हित अक्षर *name1;
	अचिन्हित अक्षर *name2;
	पूर्णांक name1len, name2len;
	काष्ठा dnode *d;
	dnode_secno dno, करोwnd;
	काष्ठा fnode *upf;
	काष्ठा buffer_head *bh;
	काष्ठा hpfs_dirent *de, *de_end;
	पूर्णांक c;
	पूर्णांक c1, c2 = 0;
	पूर्णांक d1, d2 = 0;
	name1 = f->name;
	अगर (!(name2 = kदो_स्मृति(256, GFP_NOFS))) अणु
		pr_err("out of memory, can't map dirent\n");
		वापस शून्य;
	पूर्ण
	अगर (f->len <= 15)
		स_नकल(name2, name1, name1len = name2len = f->len);
	अन्यथा अणु
		स_नकल(name2, name1, 15);
		स_रखो(name2 + 15, 0xff, 256 - 15);
		/*name2[15] = 0xff;*/
		name1len = 15; name2len = 256;
	पूर्ण
	अगर (!(upf = hpfs_map_fnode(s, le32_to_cpu(f->up), &bh))) अणु
		kमुक्त(name2);
		वापस शून्य;
	पूर्ण	
	अगर (!fnode_is_dir(upf)) अणु
		brअन्यथा(bh);
		hpfs_error(s, "fnode %08x has non-directory parent %08x", fno, le32_to_cpu(f->up));
		kमुक्त(name2);
		वापस शून्य;
	पूर्ण
	dno = le32_to_cpu(upf->u.बाह्यal[0].disk_secno);
	brअन्यथा(bh);
	go_करोwn:
	करोwnd = 0;
	go_up:
	अगर (!(d = hpfs_map_dnode(s, dno, qbh))) अणु
		kमुक्त(name2);
		वापस शून्य;
	पूर्ण
	de_end = dnode_end_de(d);
	de = dnode_first_de(d);
	अगर (करोwnd) अणु
		जबतक (de < de_end) अणु
			अगर (de->करोwn) अगर (de_करोwn_poपूर्णांकer(de) == करोwnd) जाओ f;
			de = de_next_de(de);
		पूर्ण
		hpfs_error(s, "pointer to dnode %08x not found in dnode %08x", करोwnd, dno);
		hpfs_brअन्यथा4(qbh);
		kमुक्त(name2);
		वापस शून्य;
	पूर्ण
	next_de:
	अगर (le32_to_cpu(de->fnode) == fno) अणु
		kमुक्त(name2);
		वापस de;
	पूर्ण
	c = hpfs_compare_names(s, name1, name1len, de->name, de->namelen, de->last);
	अगर (c < 0 && de->करोwn) अणु
		dno = de_करोwn_poपूर्णांकer(de);
		hpfs_brअन्यथा4(qbh);
		अगर (hpfs_sb(s)->sb_chk)
			अगर (hpfs_stop_cycles(s, dno, &c1, &c2, "map_fnode_dirent #1")) अणु
				kमुक्त(name2);
				वापस शून्य;
		पूर्ण
		जाओ go_करोwn;
	पूर्ण
	f:
	अगर (le32_to_cpu(de->fnode) == fno) अणु
		kमुक्त(name2);
		वापस de;
	पूर्ण
	c = hpfs_compare_names(s, name2, name2len, de->name, de->namelen, de->last);
	अगर (c < 0 && !de->last) जाओ not_found;
	अगर ((de = de_next_de(de)) < de_end) जाओ next_de;
	अगर (d->root_dnode) जाओ not_found;
	करोwnd = dno;
	dno = le32_to_cpu(d->up);
	hpfs_brअन्यथा4(qbh);
	अगर (hpfs_sb(s)->sb_chk)
		अगर (hpfs_stop_cycles(s, करोwnd, &d1, &d2, "map_fnode_dirent #2")) अणु
			kमुक्त(name2);
			वापस शून्य;
		पूर्ण
	जाओ go_up;
	not_found:
	hpfs_brअन्यथा4(qbh);
	hpfs_error(s, "dirent for fnode %08x not found", fno);
	kमुक्त(name2);
	वापस शून्य;
पूर्ण
