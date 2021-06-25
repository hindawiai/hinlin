<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/dir_fplus.c
 *
 *  Copyright (C) 1997-1999 Russell King
 */
#समावेश "adfs.h"
#समावेश "dir_fplus.h"

/* Return the byte offset to directory entry pos */
अटल अचिन्हित पूर्णांक adfs_fplus_offset(स्थिर काष्ठा adfs_bigdirheader *h,
				      अचिन्हित पूर्णांक pos)
अणु
	वापस दुरत्व(काष्ठा adfs_bigdirheader, bigस_नाम) +
	       ALIGN(le32_to_cpu(h->bigस_नामlen), 4) +
	       pos * माप(काष्ठा adfs_bigdirentry);
पूर्ण

अटल पूर्णांक adfs_fplus_validate_header(स्थिर काष्ठा adfs_bigdirheader *h)
अणु
	अचिन्हित पूर्णांक size = le32_to_cpu(h->bigdirsize);
	अचिन्हित पूर्णांक len;

	अगर (h->bigdirversion[0] != 0 || h->bigdirversion[1] != 0 ||
	    h->bigdirversion[2] != 0 ||
	    h->bigdirstartname != cpu_to_le32(BIGसूचीSTARTNAME) ||
	    !size || size & 2047 || size > SZ_4M)
		वापस -EIO;

	size -= माप(काष्ठा adfs_bigdirtail) +
		दुरत्व(काष्ठा adfs_bigdirheader, bigस_नाम);

	/* Check that bigस_नामlen fits within the directory */
	len = ALIGN(le32_to_cpu(h->bigस_नामlen), 4);
	अगर (len > size)
		वापस -EIO;

	size -= len;

	/* Check that bigस_नामsize fits within the directory */
	len = le32_to_cpu(h->bigस_नामsize);
	अगर (len > size)
		वापस -EIO;

	size -= len;

	/*
	 * Aव्योम भागision, we know that असलolute maximum number of entries
	 * can not be so large to cause overflow of the multiplication below.
	 */
	len = le32_to_cpu(h->bigdirentries);
	अगर (len > SZ_4M / माप(काष्ठा adfs_bigdirentry) ||
	    len * माप(काष्ठा adfs_bigdirentry) > size)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक adfs_fplus_validate_tail(स्थिर काष्ठा adfs_bigdirheader *h,
				    स्थिर काष्ठा adfs_bigdirtail *t)
अणु
	अगर (t->bigdirendname != cpu_to_le32(BIGसूचीENDNAME) ||
	    t->bigdirendmasseq != h->starपंचांगasseq ||
	    t->reserved[0] != 0 || t->reserved[1] != 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल u8 adfs_fplus_checkbyte(काष्ठा adfs_dir *dir)
अणु
	काष्ठा adfs_bigdirheader *h = dir->bighead;
	काष्ठा adfs_bigdirtail *t = dir->bigtail;
	अचिन्हित पूर्णांक end, bs, bi, i;
	__le32 *bp;
	u32 dircheck;

	end = adfs_fplus_offset(h, le32_to_cpu(h->bigdirentries)) +
		le32_to_cpu(h->bigस_नामsize);

	/* Accumulate the contents of the header, entries and names */
	क्रम (dircheck = 0, bi = 0; end; bi++) अणु
		bp = (व्योम *)dir->bhs[bi]->b_data;
		bs = dir->bhs[bi]->b_size;
		अगर (bs > end)
			bs = end;

		क्रम (i = 0; i < bs; i += माप(u32))
			dircheck = ror32(dircheck, 13) ^ le32_to_cpup(bp++);

		end -= bs;
	पूर्ण

	/* Accumulate the contents of the tail except क्रम the check byte */
	dircheck = ror32(dircheck, 13) ^ le32_to_cpu(t->bigdirendname);
	dircheck = ror32(dircheck, 13) ^ t->bigdirendmasseq;
	dircheck = ror32(dircheck, 13) ^ t->reserved[0];
	dircheck = ror32(dircheck, 13) ^ t->reserved[1];

	वापस dircheck ^ dircheck >> 8 ^ dircheck >> 16 ^ dircheck >> 24;
पूर्ण

अटल पूर्णांक adfs_fplus_पढ़ो(काष्ठा super_block *sb, u32 indaddr,
			   अचिन्हित पूर्णांक size, काष्ठा adfs_dir *dir)
अणु
	काष्ठा adfs_bigdirheader *h;
	काष्ठा adfs_bigdirtail *t;
	अचिन्हित पूर्णांक dirsize;
	पूर्णांक ret;

	/* Read first buffer */
	ret = adfs_dir_पढ़ो_buffers(sb, indaddr, sb->s_blocksize, dir);
	अगर (ret)
		वापस ret;

	dir->bighead = h = (व्योम *)dir->bhs[0]->b_data;
	ret = adfs_fplus_validate_header(h);
	अगर (ret) अणु
		adfs_error(sb, "dir %06x has malformed header", indaddr);
		जाओ out;
	पूर्ण

	dirsize = le32_to_cpu(h->bigdirsize);
	अगर (size && dirsize != size) अणु
		adfs_msg(sb, KERN_WARNING,
			 "dir %06x header size %X does not match directory size %X",
			 indaddr, dirsize, size);
	पूर्ण

	/* Read reमुख्यing buffers */
	ret = adfs_dir_पढ़ो_buffers(sb, indaddr, dirsize, dir);
	अगर (ret)
		वापस ret;

	dir->bigtail = t = (काष्ठा adfs_bigdirtail *)
		(dir->bhs[dir->nr_buffers - 1]->b_data + (sb->s_blocksize - 8));

	ret = adfs_fplus_validate_tail(h, t);
	अगर (ret) अणु
		adfs_error(sb, "dir %06x has malformed tail", indaddr);
		जाओ out;
	पूर्ण

	अगर (adfs_fplus_checkbyte(dir) != t->bigdircheckbyte) अणु
		adfs_error(sb, "dir %06x checkbyte mismatch\n", indaddr);
		जाओ out;
	पूर्ण

	dir->parent_id = le32_to_cpu(h->bigdirparent);
	वापस 0;

out:
	adfs_dir_rअन्यथा(dir);

	वापस ret;
पूर्ण

अटल पूर्णांक
adfs_fplus_setpos(काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक fpos)
अणु
	पूर्णांक ret = -ENOENT;

	अगर (fpos <= le32_to_cpu(dir->bighead->bigdirentries)) अणु
		dir->pos = fpos;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
adfs_fplus_getnext(काष्ठा adfs_dir *dir, काष्ठा object_info *obj)
अणु
	काष्ठा adfs_bigdirheader *h = dir->bighead;
	काष्ठा adfs_bigdirentry bde;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret;

	अगर (dir->pos >= le32_to_cpu(h->bigdirentries))
		वापस -ENOENT;

	offset = adfs_fplus_offset(h, dir->pos);

	ret = adfs_dir_copyfrom(&bde, dir, offset,
				माप(काष्ठा adfs_bigdirentry));
	अगर (ret)
		वापस ret;

	obj->loadaddr = le32_to_cpu(bde.bigdirload);
	obj->execaddr = le32_to_cpu(bde.bigdirexec);
	obj->size     = le32_to_cpu(bde.bigdirlen);
	obj->indaddr  = le32_to_cpu(bde.bigdirindaddr);
	obj->attr     = le32_to_cpu(bde.bigdirattr);
	obj->name_len = le32_to_cpu(bde.bigdirobnamelen);

	offset = adfs_fplus_offset(h, le32_to_cpu(h->bigdirentries));
	offset += le32_to_cpu(bde.bigdirobnameptr);

	ret = adfs_dir_copyfrom(obj->name, dir, offset, obj->name_len);
	अगर (ret)
		वापस ret;

	adfs_object_fixup(dir, obj);

	dir->pos += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक adfs_fplus_iterate(काष्ठा adfs_dir *dir, काष्ठा dir_context *ctx)
अणु
	काष्ठा object_info obj;

	अगर ((ctx->pos - 2) >> 32)
		वापस 0;

	अगर (adfs_fplus_setpos(dir, ctx->pos - 2))
		वापस 0;

	जबतक (!adfs_fplus_getnext(dir, &obj)) अणु
		अगर (!dir_emit(ctx, obj.name, obj.name_len,
			      obj.indaddr, DT_UNKNOWN))
			अवरोध;
		ctx->pos++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adfs_fplus_update(काष्ठा adfs_dir *dir, काष्ठा object_info *obj)
अणु
	काष्ठा adfs_bigdirheader *h = dir->bighead;
	काष्ठा adfs_bigdirentry bde;
	पूर्णांक offset, end, ret;

	offset = adfs_fplus_offset(h, 0) - माप(bde);
	end = adfs_fplus_offset(h, le32_to_cpu(h->bigdirentries));

	करो अणु
		offset += माप(bde);
		अगर (offset >= end) अणु
			adfs_error(dir->sb, "unable to locate entry to update");
			वापस -ENOENT;
		पूर्ण
		ret = adfs_dir_copyfrom(&bde, dir, offset, माप(bde));
		अगर (ret) अणु
			adfs_error(dir->sb, "error reading directory entry");
			वापस -ENOENT;
		पूर्ण
	पूर्ण जबतक (le32_to_cpu(bde.bigdirindaddr) != obj->indaddr);

	bde.bigdirload    = cpu_to_le32(obj->loadaddr);
	bde.bigdirexec    = cpu_to_le32(obj->execaddr);
	bde.bigdirlen     = cpu_to_le32(obj->size);
	bde.bigdirindaddr = cpu_to_le32(obj->indaddr);
	bde.bigdirattr    = cpu_to_le32(obj->attr);

	वापस adfs_dir_copyto(dir, offset, &bde, माप(bde));
पूर्ण

अटल पूर्णांक adfs_fplus_commit(काष्ठा adfs_dir *dir)
अणु
	पूर्णांक ret;

	/* Increment directory sequence number */
	dir->bighead->starपंचांगasseq += 1;
	dir->bigtail->bigdirendmasseq += 1;

	/* Update directory check byte */
	dir->bigtail->bigdircheckbyte = adfs_fplus_checkbyte(dir);

	/* Make sure the directory still validates correctly */
	ret = adfs_fplus_validate_header(dir->bighead);
	अगर (ret == 0)
		ret = adfs_fplus_validate_tail(dir->bighead, dir->bigtail);

	वापस ret;
पूर्ण

स्थिर काष्ठा adfs_dir_ops adfs_fplus_dir_ops = अणु
	.पढ़ो		= adfs_fplus_पढ़ो,
	.iterate	= adfs_fplus_iterate,
	.setpos		= adfs_fplus_setpos,
	.getnext	= adfs_fplus_getnext,
	.update		= adfs_fplus_update,
	.commit		= adfs_fplus_commit,
पूर्ण;
