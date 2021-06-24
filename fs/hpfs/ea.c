<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/ea.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  handling extended attributes
 */

#समावेश "hpfs_fn.h"

/* Remove बाह्यal extended attributes. ano specअगरies whether a is a 
   direct sector where eas starts or an anode */

व्योम hpfs_ea_ext_हटाओ(काष्ठा super_block *s, secno a, पूर्णांक ano, अचिन्हित len)
अणु
	अचिन्हित pos = 0;
	जबतक (pos < len) अणु
		अक्षर ex[4 + 255 + 1 + 8];
		काष्ठा extended_attribute *ea = (काष्ठा extended_attribute *)ex;
		अगर (pos + 4 > len) अणु
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			वापस;
		पूर्ण
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos, 4, ex)) वापस;
		अगर (ea_indirect(ea)) अणु
			अगर (ea_valuelen(ea) != 8) अणु
				hpfs_error(s, "ea_indirect(ea) set while ea->valuelen!=8, %s %08x, pos %08x",
					ano ? "anode" : "sectors", a, pos);
				वापस;
			पूर्ण
			अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4, ea->namelen + 9, ex+4))
				वापस;
			hpfs_ea_हटाओ(s, ea_sec(ea), ea_in_anode(ea), ea_len(ea));
		पूर्ण
		pos += ea->namelen + ea_valuelen(ea) + 5;
	पूर्ण
	अगर (!ano) hpfs_मुक्त_sectors(s, a, (len+511) >> 9);
	अन्यथा अणु
		काष्ठा buffer_head *bh;
		काष्ठा anode *anode;
		अगर ((anode = hpfs_map_anode(s, a, &bh))) अणु
			hpfs_हटाओ_btree(s, &anode->btree);
			brअन्यथा(bh);
			hpfs_मुक्त_sectors(s, a, 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर *get_indirect_ea(काष्ठा super_block *s, पूर्णांक ano, secno a, पूर्णांक size)
अणु
	अक्षर *ret;
	अगर (!(ret = kदो_स्मृति(size + 1, GFP_NOFS))) अणु
		pr_err("out of memory for EA\n");
		वापस शून्य;
	पूर्ण
	अगर (hpfs_ea_पढ़ो(s, a, ano, 0, size, ret)) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण
	ret[size] = 0;
	वापस ret;
पूर्ण

अटल व्योम set_indirect_ea(काष्ठा super_block *s, पूर्णांक ano, secno a,
			    स्थिर अक्षर *data, पूर्णांक size)
अणु
	hpfs_ea_ग_लिखो(s, a, ano, 0, size, data);
पूर्ण

/* Read an extended attribute named 'key' पूर्णांकo the provided buffer */

पूर्णांक hpfs_पढ़ो_ea(काष्ठा super_block *s, काष्ठा fnode *fnode, अक्षर *key,
		अक्षर *buf, पूर्णांक size)
अणु
	अचिन्हित pos;
	पूर्णांक ano, len;
	secno a;
	अक्षर ex[4 + 255 + 1 + 8];
	काष्ठा extended_attribute *ea;
	काष्ठा extended_attribute *ea_end = fnode_end_ea(fnode);
	क्रम (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea))
				जाओ indirect;
			अगर (ea_valuelen(ea) >= size)
				वापस -EINVAL;
			स_नकल(buf, ea_data(ea), ea_valuelen(ea));
			buf[ea_valuelen(ea)] = 0;
			वापस 0;
		पूर्ण
	a = le32_to_cpu(fnode->ea_secno);
	len = le32_to_cpu(fnode->ea_size_l);
	ano = fnode_in_anode(fnode);
	pos = 0;
	जबतक (pos < len) अणु
		ea = (काष्ठा extended_attribute *)ex;
		अगर (pos + 4 > len) अणु
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			वापस -EIO;
		पूर्ण
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos, 4, ex)) वापस -EIO;
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4, ea->namelen + 1 + (ea_indirect(ea) ? 8 : 0), ex + 4))
			वापस -EIO;
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea))
				जाओ indirect;
			अगर (ea_valuelen(ea) >= size)
				वापस -EINVAL;
			अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4 + ea->namelen + 1, ea_valuelen(ea), buf))
				वापस -EIO;
			buf[ea_valuelen(ea)] = 0;
			वापस 0;
		पूर्ण
		pos += ea->namelen + ea_valuelen(ea) + 5;
	पूर्ण
	वापस -ENOENT;
indirect:
	अगर (ea_len(ea) >= size)
		वापस -EINVAL;
	अगर (hpfs_ea_पढ़ो(s, ea_sec(ea), ea_in_anode(ea), 0, ea_len(ea), buf))
		वापस -EIO;
	buf[ea_len(ea)] = 0;
	वापस 0;
पूर्ण

/* Read an extended attribute named 'key' */
अक्षर *hpfs_get_ea(काष्ठा super_block *s, काष्ठा fnode *fnode, अक्षर *key, पूर्णांक *size)
अणु
	अक्षर *ret;
	अचिन्हित pos;
	पूर्णांक ano, len;
	secno a;
	काष्ठा extended_attribute *ea;
	काष्ठा extended_attribute *ea_end = fnode_end_ea(fnode);
	क्रम (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea))
				वापस get_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), *size = ea_len(ea));
			अगर (!(ret = kदो_स्मृति((*size = ea_valuelen(ea)) + 1, GFP_NOFS))) अणु
				pr_err("out of memory for EA\n");
				वापस शून्य;
			पूर्ण
			स_नकल(ret, ea_data(ea), ea_valuelen(ea));
			ret[ea_valuelen(ea)] = 0;
			वापस ret;
		पूर्ण
	a = le32_to_cpu(fnode->ea_secno);
	len = le32_to_cpu(fnode->ea_size_l);
	ano = fnode_in_anode(fnode);
	pos = 0;
	जबतक (pos < len) अणु
		अक्षर ex[4 + 255 + 1 + 8];
		ea = (काष्ठा extended_attribute *)ex;
		अगर (pos + 4 > len) अणु
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			वापस शून्य;
		पूर्ण
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos, 4, ex)) वापस शून्य;
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4, ea->namelen + 1 + (ea_indirect(ea) ? 8 : 0), ex + 4))
			वापस शून्य;
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea))
				वापस get_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), *size = ea_len(ea));
			अगर (!(ret = kदो_स्मृति((*size = ea_valuelen(ea)) + 1, GFP_NOFS))) अणु
				pr_err("out of memory for EA\n");
				वापस शून्य;
			पूर्ण
			अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4 + ea->namelen + 1, ea_valuelen(ea), ret)) अणु
				kमुक्त(ret);
				वापस शून्य;
			पूर्ण
			ret[ea_valuelen(ea)] = 0;
			वापस ret;
		पूर्ण
		pos += ea->namelen + ea_valuelen(ea) + 5;
	पूर्ण
	वापस शून्य;
पूर्ण

/* 
 * Update or create extended attribute 'key' with value 'data'. Note that
 * when this ea exists, it MUST have the same size as size of data.
 * This driver can't change sizes of eas ('cause I just don't need it).
 */

व्योम hpfs_set_ea(काष्ठा inode *inode, काष्ठा fnode *fnode, स्थिर अक्षर *key,
		 स्थिर अक्षर *data, पूर्णांक size)
अणु
	fnode_secno fno = inode->i_ino;
	काष्ठा super_block *s = inode->i_sb;
	अचिन्हित pos;
	पूर्णांक ano, len;
	secno a;
	अचिन्हित अक्षर h[4];
	काष्ठा extended_attribute *ea;
	काष्ठा extended_attribute *ea_end = fnode_end_ea(fnode);
	क्रम (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea)) अणु
				अगर (ea_len(ea) == size)
					set_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), data, size);
			पूर्ण अन्यथा अगर (ea_valuelen(ea) == size) अणु
				स_नकल(ea_data(ea), data, size);
			पूर्ण
			वापस;
		पूर्ण
	a = le32_to_cpu(fnode->ea_secno);
	len = le32_to_cpu(fnode->ea_size_l);
	ano = fnode_in_anode(fnode);
	pos = 0;
	जबतक (pos < len) अणु
		अक्षर ex[4 + 255 + 1 + 8];
		ea = (काष्ठा extended_attribute *)ex;
		अगर (pos + 4 > len) अणु
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			वापस;
		पूर्ण
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos, 4, ex)) वापस;
		अगर (hpfs_ea_पढ़ो(s, a, ano, pos + 4, ea->namelen + 1 + (ea_indirect(ea) ? 8 : 0), ex + 4))
			वापस;
		अगर (!म_भेद(ea->name, key)) अणु
			अगर (ea_indirect(ea)) अणु
				अगर (ea_len(ea) == size)
					set_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), data, size);
			पूर्ण
			अन्यथा अणु
				अगर (ea_valuelen(ea) == size)
					hpfs_ea_ग_लिखो(s, a, ano, pos + 4 + ea->namelen + 1, size, data);
			पूर्ण
			वापस;
		पूर्ण
		pos += ea->namelen + ea_valuelen(ea) + 5;
	पूर्ण
	अगर (!le16_to_cpu(fnode->ea_offs)) अणु
		/*अगर (le16_to_cpu(fnode->ea_size_s)) अणु
			hpfs_error(s, "fnode %08x: ea_size_s == %03x, ea_offs == 0",
				inode->i_ino, le16_to_cpu(fnode->ea_size_s));
			वापस;
		पूर्ण*/
		fnode->ea_offs = cpu_to_le16(0xc4);
	पूर्ण
	अगर (le16_to_cpu(fnode->ea_offs) < 0xc4 || le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s) > 0x200) अणु
		hpfs_error(s, "fnode %08lx: ea_offs == %03x, ea_size_s == %03x",
			(अचिन्हित दीर्घ)inode->i_ino,
			le16_to_cpu(fnode->ea_offs), le16_to_cpu(fnode->ea_size_s));
		वापस;
	पूर्ण
	अगर ((le16_to_cpu(fnode->ea_size_s) || !le32_to_cpu(fnode->ea_size_l)) &&
	     le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s) + म_माप(key) + size + 5 <= 0x200) अणु
		ea = fnode_end_ea(fnode);
		*(अक्षर *)ea = 0;
		ea->namelen = म_माप(key);
		ea->valuelen_lo = size;
		ea->valuelen_hi = size >> 8;
		म_नकल(ea->name, key);
		स_नकल(ea_data(ea), data, size);
		fnode->ea_size_s = cpu_to_le16(le16_to_cpu(fnode->ea_size_s) + म_माप(key) + size + 5);
		जाओ ret;
	पूर्ण
	/* Most the code here is 99.9993422% unused. I hope there are no bugs.
	   But what .. HPFS.IFS has also bugs in ea management. */
	अगर (le16_to_cpu(fnode->ea_size_s) && !le32_to_cpu(fnode->ea_size_l)) अणु
		secno n;
		काष्ठा buffer_head *bh;
		अक्षर *data;
		अगर (!(n = hpfs_alloc_sector(s, fno, 1, 0))) वापस;
		अगर (!(data = hpfs_get_sector(s, n, &bh))) अणु
			hpfs_मुक्त_sectors(s, n, 1);
			वापस;
		पूर्ण
		स_नकल(data, fnode_ea(fnode), le16_to_cpu(fnode->ea_size_s));
		fnode->ea_size_l = cpu_to_le32(le16_to_cpu(fnode->ea_size_s));
		fnode->ea_size_s = cpu_to_le16(0);
		fnode->ea_secno = cpu_to_le32(n);
		fnode->flags &= ~FNODE_anode;
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
	पूर्ण
	pos = le32_to_cpu(fnode->ea_size_l) + 5 + म_माप(key) + size;
	len = (le32_to_cpu(fnode->ea_size_l) + 511) >> 9;
	अगर (pos >= 30000) जाओ bail;
	जबतक (((pos + 511) >> 9) > len) अणु
		अगर (!len) अणु
			secno q = hpfs_alloc_sector(s, fno, 1, 0);
			अगर (!q) जाओ bail;
			fnode->ea_secno = cpu_to_le32(q);
			fnode->flags &= ~FNODE_anode;
			len++;
		पूर्ण अन्यथा अगर (!fnode_in_anode(fnode)) अणु
			अगर (hpfs_alloc_अगर_possible(s, le32_to_cpu(fnode->ea_secno) + len)) अणु
				len++;
			पूर्ण अन्यथा अणु
				/* Aargh... करोn't know how to create ea anodes :-( */
				/*काष्ठा buffer_head *bh;
				काष्ठा anode *anode;
				anode_secno a_s;
				अगर (!(anode = hpfs_alloc_anode(s, fno, &a_s, &bh)))
					जाओ bail;
				anode->up = cpu_to_le32(fno);
				anode->btree.fnode_parent = 1;
				anode->btree.n_मुक्त_nodes--;
				anode->btree.n_used_nodes++;
				anode->btree.first_मुक्त = cpu_to_le16(le16_to_cpu(anode->btree.first_मुक्त) + 12);
				anode->u.बाह्यal[0].disk_secno = cpu_to_le32(le32_to_cpu(fnode->ea_secno));
				anode->u.बाह्यal[0].file_secno = cpu_to_le32(0);
				anode->u.बाह्यal[0].length = cpu_to_le32(len);
				mark_buffer_dirty(bh);
				brअन्यथा(bh);
				fnode->flags |= FNODE_anode;
				fnode->ea_secno = cpu_to_le32(a_s);*/
				secno new_sec;
				पूर्णांक i;
				अगर (!(new_sec = hpfs_alloc_sector(s, fno, 1, 1 - ((pos + 511) >> 9))))
					जाओ bail;
				क्रम (i = 0; i < len; i++) अणु
					काष्ठा buffer_head *bh1, *bh2;
					व्योम *b1, *b2;
					अगर (!(b1 = hpfs_map_sector(s, le32_to_cpu(fnode->ea_secno) + i, &bh1, len - i - 1))) अणु
						hpfs_मुक्त_sectors(s, new_sec, (pos + 511) >> 9);
						जाओ bail;
					पूर्ण
					अगर (!(b2 = hpfs_get_sector(s, new_sec + i, &bh2))) अणु
						brअन्यथा(bh1);
						hpfs_मुक्त_sectors(s, new_sec, (pos + 511) >> 9);
						जाओ bail;
					पूर्ण
					स_नकल(b2, b1, 512);
					brअन्यथा(bh1);
					mark_buffer_dirty(bh2);
					brअन्यथा(bh2);
				पूर्ण
				hpfs_मुक्त_sectors(s, le32_to_cpu(fnode->ea_secno), len);
				fnode->ea_secno = cpu_to_le32(new_sec);
				len = (pos + 511) >> 9;
			पूर्ण
		पूर्ण
		अगर (fnode_in_anode(fnode)) अणु
			अगर (hpfs_add_sector_to_btree(s, le32_to_cpu(fnode->ea_secno),
						     0, len) != -1) अणु
				len++;
			पूर्ण अन्यथा अणु
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण
	h[0] = 0;
	h[1] = म_माप(key);
	h[2] = size & 0xff;
	h[3] = size >> 8;
	अगर (hpfs_ea_ग_लिखो(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l), 4, h)) जाओ bail;
	अगर (hpfs_ea_ग_लिखो(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l) + 4, h[1] + 1, key)) जाओ bail;
	अगर (hpfs_ea_ग_लिखो(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l) + 5 + h[1], size, data)) जाओ bail;
	fnode->ea_size_l = cpu_to_le32(pos);
	ret:
	hpfs_i(inode)->i_ea_size += 5 + म_माप(key) + size;
	वापस;
	bail:
	अगर (le32_to_cpu(fnode->ea_secno))
		अगर (fnode_in_anode(fnode)) hpfs_truncate_btree(s, le32_to_cpu(fnode->ea_secno), 1, (le32_to_cpu(fnode->ea_size_l) + 511) >> 9);
		अन्यथा hpfs_मुक्त_sectors(s, le32_to_cpu(fnode->ea_secno) + ((le32_to_cpu(fnode->ea_size_l) + 511) >> 9), len - ((le32_to_cpu(fnode->ea_size_l) + 511) >> 9));
	अन्यथा fnode->ea_secno = fnode->ea_size_l = cpu_to_le32(0);
पूर्ण
	
