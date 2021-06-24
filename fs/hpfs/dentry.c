<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/dentry.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  dcache operations
 */

#समावेश "hpfs_fn.h"

/*
 * Note: the dentry argument is the parent dentry.
 */

अटल पूर्णांक hpfs_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	अचिन्हित दीर्घ	 hash;
	पूर्णांक		 i;
	अचिन्हित l = qstr->len;

	अगर (l == 1) अगर (qstr->name[0]=='.') जाओ x;
	अगर (l == 2) अगर (qstr->name[0]=='.' || qstr->name[1]=='.') जाओ x;
	hpfs_adjust_length(qstr->name, &l);
	/*अगर (hpfs_chk_name(qstr->name,&l))*/
		/*वापस -ENAMETOOLONG;*/
		/*वापस -ENOENT;*/
	x:

	hash = init_name_hash(dentry);
	क्रम (i = 0; i < l; i++)
		hash = partial_name_hash(hpfs_upहाल(hpfs_sb(dentry->d_sb)->sb_cp_table,qstr->name[i]), hash);
	qstr->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

अटल पूर्णांक hpfs_compare_dentry(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	अचिन्हित al = len;
	अचिन्हित bl = name->len;

	hpfs_adjust_length(str, &al);
	/*hpfs_adjust_length(b->name, &bl);*/

	/*
	 * 'str' is the nane of an alपढ़ोy existing dentry, so the name
	 * must be valid. 'name' must be validated first.
	 */

	अगर (hpfs_chk_name(name->name, &bl))
		वापस 1;
	अगर (hpfs_compare_names(dentry->d_sb, str, al, name->name, bl, 0))
		वापस 1;
	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations hpfs_dentry_operations = अणु
	.d_hash		= hpfs_hash_dentry,
	.d_compare	= hpfs_compare_dentry,
पूर्ण;
