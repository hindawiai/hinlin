<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "xattr.h"

#समावेश <trace/events/erofs.h>

काष्ठा erofs_qstr अणु
	स्थिर अचिन्हित अक्षर *name;
	स्थिर अचिन्हित अक्षर *end;
पूर्ण;

/* based on the end of qn is accurate and it must have the trailing '\0' */
अटल अंतरभूत पूर्णांक erofs_स_नामcmp(स्थिर काष्ठा erofs_qstr *qn,
				   स्थिर काष्ठा erofs_qstr *qd,
				   अचिन्हित पूर्णांक *matched)
अणु
	अचिन्हित पूर्णांक i = *matched;

	/*
	 * on-disk error, let's only BUG_ON in the debugging mode.
	 * otherwise, it will वापस 1 to just skip the invalid name
	 * and go on (in consideration of the lookup perक्रमmance).
	 */
	DBG_BUGON(qd->name > qd->end);

	/* qd could not have trailing '\0' */
	/* However it is असलolutely safe अगर < qd->end */
	जबतक (qd->name + i < qd->end && qd->name[i] != '\0') अणु
		अगर (qn->name[i] != qd->name[i]) अणु
			*matched = i;
			वापस qn->name[i] > qd->name[i] ? 1 : -1;
		पूर्ण
		++i;
	पूर्ण
	*matched = i;
	/* See comments in __d_alloc on the terminating NUL अक्षरacter */
	वापस qn->name[i] == '\0' ? 0 : 1;
पूर्ण

#घोषणा nameoff_from_disk(off, sz)	(le16_to_cpu(off) & ((sz) - 1))

अटल काष्ठा erofs_dirent *find_target_dirent(काष्ठा erofs_qstr *name,
					       u8 *data,
					       अचिन्हित पूर्णांक dirblksize,
					       स्थिर पूर्णांक ndirents)
अणु
	पूर्णांक head, back;
	अचिन्हित पूर्णांक startprfx, endprfx;
	काष्ठा erofs_dirent *स्थिर de = (काष्ठा erofs_dirent *)data;

	/* since the 1st dirent has been evaluated previously */
	head = 1;
	back = ndirents - 1;
	startprfx = endprfx = 0;

	जबतक (head <= back) अणु
		स्थिर पूर्णांक mid = head + (back - head) / 2;
		स्थिर पूर्णांक nameoff = nameoff_from_disk(de[mid].nameoff,
						      dirblksize);
		अचिन्हित पूर्णांक matched = min(startprfx, endprfx);
		काष्ठा erofs_qstr dname = अणु
			.name = data + nameoff,
			.end = mid >= ndirents - 1 ?
				data + dirblksize :
				data + nameoff_from_disk(de[mid + 1].nameoff,
							 dirblksize)
		पूर्ण;

		/* string comparison without alपढ़ोy matched prefix */
		पूर्णांक ret = erofs_स_नामcmp(name, &dname, &matched);

		अगर (!ret) अणु
			वापस de + mid;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			head = mid + 1;
			startprfx = matched;
		पूर्ण अन्यथा अणु
			back = mid - 1;
			endprfx = matched;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा page *find_target_block_classic(काष्ठा inode *dir,
					      काष्ठा erofs_qstr *name,
					      पूर्णांक *_ndirents)
अणु
	अचिन्हित पूर्णांक startprfx, endprfx;
	पूर्णांक head, back;
	काष्ठा address_space *स्थिर mapping = dir->i_mapping;
	काष्ठा page *candidate = ERR_PTR(-ENOENT);

	startprfx = endprfx = 0;
	head = 0;
	back = erofs_inode_datablocks(dir) - 1;

	जबतक (head <= back) अणु
		स्थिर पूर्णांक mid = head + (back - head) / 2;
		काष्ठा page *page = पढ़ो_mapping_page(mapping, mid, शून्य);

		अगर (!IS_ERR(page)) अणु
			काष्ठा erofs_dirent *de = kmap_atomic(page);
			स्थिर पूर्णांक nameoff = nameoff_from_disk(de->nameoff,
							      EROFS_BLKSIZ);
			स्थिर पूर्णांक ndirents = nameoff / माप(*de);
			पूर्णांक dअगरf;
			अचिन्हित पूर्णांक matched;
			काष्ठा erofs_qstr dname;

			अगर (!ndirents) अणु
				kunmap_atomic(de);
				put_page(page);
				erofs_err(dir->i_sb,
					  "corrupted dir block %d @ nid %llu",
					  mid, EROFS_I(dir)->nid);
				DBG_BUGON(1);
				page = ERR_PTR(-EFSCORRUPTED);
				जाओ out;
			पूर्ण

			matched = min(startprfx, endprfx);

			dname.name = (u8 *)de + nameoff;
			अगर (ndirents == 1)
				dname.end = (u8 *)de + EROFS_BLKSIZ;
			अन्यथा
				dname.end = (u8 *)de +
					nameoff_from_disk(de[1].nameoff,
							  EROFS_BLKSIZ);

			/* string comparison without alपढ़ोy matched prefix */
			dअगरf = erofs_स_नामcmp(name, &dname, &matched);
			kunmap_atomic(de);

			अगर (!dअगरf) अणु
				*_ndirents = 0;
				जाओ out;
			पूर्ण अन्यथा अगर (dअगरf > 0) अणु
				head = mid + 1;
				startprfx = matched;

				अगर (!IS_ERR(candidate))
					put_page(candidate);
				candidate = page;
				*_ndirents = ndirents;
			पूर्ण अन्यथा अणु
				put_page(page);

				back = mid - 1;
				endprfx = matched;
			पूर्ण
			जारी;
		पूर्ण
out:		/* मुक्त अगर the candidate is valid */
		अगर (!IS_ERR(candidate))
			put_page(candidate);
		वापस page;
	पूर्ण
	वापस candidate;
पूर्ण

पूर्णांक erofs_namei(काष्ठा inode *dir,
		काष्ठा qstr *name,
		erofs_nid_t *nid, अचिन्हित पूर्णांक *d_type)
अणु
	पूर्णांक ndirents;
	काष्ठा page *page;
	व्योम *data;
	काष्ठा erofs_dirent *de;
	काष्ठा erofs_qstr qn;

	अगर (!dir->i_size)
		वापस -ENOENT;

	qn.name = name->name;
	qn.end = name->name + name->len;

	ndirents = 0;
	page = find_target_block_classic(dir, &qn, &ndirents);

	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	data = kmap_atomic(page);
	/* the target page has been mapped */
	अगर (ndirents)
		de = find_target_dirent(&qn, data, EROFS_BLKSIZ, ndirents);
	अन्यथा
		de = (काष्ठा erofs_dirent *)data;

	अगर (!IS_ERR(de)) अणु
		*nid = le64_to_cpu(de->nid);
		*d_type = de->file_type;
	पूर्ण

	kunmap_atomic(data);
	put_page(page);

	वापस PTR_ERR_OR_ZERO(de);
पूर्ण

/* NOTE: i_mutex is alपढ़ोy held by vfs */
अटल काष्ठा dentry *erofs_lookup(काष्ठा inode *dir,
				   काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	erofs_nid_t nid;
	अचिन्हित पूर्णांक d_type;
	काष्ठा inode *inode;

	DBG_BUGON(!d_really_is_negative(dentry));
	/* dentry must be unhashed in lookup, no need to worry about */
	DBG_BUGON(!d_unhashed(dentry));

	trace_erofs_lookup(dir, dentry, flags);

	/* file name exceeds fs limit */
	अगर (dentry->d_name.len > EROFS_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	/* false uninitialized warnings on gcc 4.8.x */
	err = erofs_namei(dir, &dentry->d_name, &nid, &d_type);

	अगर (err == -ENOENT) अणु
		/* negative dentry */
		inode = शून्य;
	पूर्ण अन्यथा अगर (err) अणु
		inode = ERR_PTR(err);
	पूर्ण अन्यथा अणु
		erofs_dbg("%s, %pd (nid %llu) found, d_type %u", __func__,
			  dentry, nid, d_type);
		inode = erofs_iget(dir->i_sb, nid, d_type == FT_सूची);
	पूर्ण
	वापस d_splice_alias(inode, dentry);
पूर्ण

स्थिर काष्ठा inode_operations erofs_dir_iops = अणु
	.lookup = erofs_lookup,
	.getattr = erofs_getattr,
	.listxattr = erofs_listxattr,
	.get_acl = erofs_get_acl,
पूर्ण;

