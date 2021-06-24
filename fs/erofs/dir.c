<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "internal.h"

अटल व्योम debug_one_dentry(अचिन्हित अक्षर d_type, स्थिर अक्षर *de_name,
			     अचिन्हित पूर्णांक de_namelen)
अणु
#अगर_घोषित CONFIG_EROFS_FS_DEBUG
	/* since the on-disk name could not have the trailing '\0' */
	अचिन्हित अक्षर dbg_namebuf[EROFS_NAME_LEN + 1];

	स_नकल(dbg_namebuf, de_name, de_namelen);
	dbg_namebuf[de_namelen] = '\0';

	erofs_dbg("found dirent %s de_len %u d_type %d", dbg_namebuf,
		  de_namelen, d_type);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक erofs_fill_dentries(काष्ठा inode *dir, काष्ठा dir_context *ctx,
			       व्योम *dentry_blk, अचिन्हित पूर्णांक *ofs,
			       अचिन्हित पूर्णांक nameoff, अचिन्हित पूर्णांक maxsize)
अणु
	काष्ठा erofs_dirent *de = dentry_blk + *ofs;
	स्थिर काष्ठा erofs_dirent *end = dentry_blk + nameoff;

	जबतक (de < end) अणु
		स्थिर अक्षर *de_name;
		अचिन्हित पूर्णांक de_namelen;
		अचिन्हित अक्षर d_type;

		d_type = fs_ftype_to_dtype(de->file_type);

		nameoff = le16_to_cpu(de->nameoff);
		de_name = (अक्षर *)dentry_blk + nameoff;

		/* the last dirent in the block? */
		अगर (de + 1 >= end)
			de_namelen = strnlen(de_name, maxsize - nameoff);
		अन्यथा
			de_namelen = le16_to_cpu(de[1].nameoff) - nameoff;

		/* a corrupted entry is found */
		अगर (nameoff + de_namelen > maxsize ||
		    de_namelen > EROFS_NAME_LEN) अणु
			erofs_err(dir->i_sb, "bogus dirent @ nid %llu",
				  EROFS_I(dir)->nid);
			DBG_BUGON(1);
			वापस -EFSCORRUPTED;
		पूर्ण

		debug_one_dentry(d_type, de_name, de_namelen);
		अगर (!dir_emit(ctx, de_name, de_namelen,
			      le64_to_cpu(de->nid), d_type))
			/* stopped by some reason */
			वापस 1;
		++de;
		*ofs += माप(काष्ठा erofs_dirent);
	पूर्ण
	*ofs = maxsize;
	वापस 0;
पूर्ण

अटल पूर्णांक erofs_सूची_पढ़ो(काष्ठा file *f, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *dir = file_inode(f);
	काष्ठा address_space *mapping = dir->i_mapping;
	स्थिर माप_प्रकार dirsize = i_size_पढ़ो(dir);
	अचिन्हित पूर्णांक i = ctx->pos / EROFS_BLKSIZ;
	अचिन्हित पूर्णांक ofs = ctx->pos % EROFS_BLKSIZ;
	पूर्णांक err = 0;
	bool initial = true;

	जबतक (ctx->pos < dirsize) अणु
		काष्ठा page *dentry_page;
		काष्ठा erofs_dirent *de;
		अचिन्हित पूर्णांक nameoff, maxsize;

		dentry_page = पढ़ो_mapping_page(mapping, i, शून्य);
		अगर (dentry_page == ERR_PTR(-ENOMEM)) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण अन्यथा अगर (IS_ERR(dentry_page)) अणु
			erofs_err(dir->i_sb,
				  "fail to readdir of logical block %u of nid %llu",
				  i, EROFS_I(dir)->nid);
			err = -EFSCORRUPTED;
			अवरोध;
		पूर्ण

		de = (काष्ठा erofs_dirent *)kmap(dentry_page);

		nameoff = le16_to_cpu(de->nameoff);

		अगर (nameoff < माप(काष्ठा erofs_dirent) ||
		    nameoff >= PAGE_SIZE) अणु
			erofs_err(dir->i_sb,
				  "invalid de[0].nameoff %u @ nid %llu",
				  nameoff, EROFS_I(dir)->nid);
			err = -EFSCORRUPTED;
			जाओ skip_this;
		पूर्ण

		maxsize = min_t(अचिन्हित पूर्णांक,
				dirsize - ctx->pos + ofs, PAGE_SIZE);

		/* search dirents at the arbitrary position */
		अगर (initial) अणु
			initial = false;

			ofs = roundup(ofs, माप(काष्ठा erofs_dirent));
			अगर (ofs >= nameoff)
				जाओ skip_this;
		पूर्ण

		err = erofs_fill_dentries(dir, ctx, de, &ofs,
					  nameoff, maxsize);
skip_this:
		kunmap(dentry_page);

		put_page(dentry_page);

		ctx->pos = blknr_to_addr(i) + ofs;

		अगर (err)
			अवरोध;
		++i;
		ofs = 0;
	पूर्ण
	वापस err < 0 ? err : 0;
पूर्ण

स्थिर काष्ठा file_operations erofs_dir_fops = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= erofs_सूची_पढ़ो,
पूर्ण;

