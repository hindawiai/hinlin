<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/dir_f.c
 *
 * Copyright (C) 1997-1999 Russell King
 *
 *  E and F क्रमmat directory handling
 */
#समावेश "adfs.h"
#समावेश "dir_f.h"

/*
 * Read an (unaligned) value of length 1..4 bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक adfs_पढ़ोval(अचिन्हित अक्षर *p, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक val = 0;

	चयन (len) अणु
	हाल 4:		val |= p[3] << 24;
		fallthrough;
	हाल 3:		val |= p[2] << 16;
		fallthrough;
	हाल 2:		val |= p[1] << 8;
		fallthrough;
	शेष:	val |= p[0];
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत व्योम adfs_ग_लिखोval(अचिन्हित अक्षर *p, पूर्णांक len, अचिन्हित पूर्णांक val)
अणु
	चयन (len) अणु
	हाल 4:		p[3] = val >> 24;
		fallthrough;
	हाल 3:		p[2] = val >> 16;
		fallthrough;
	हाल 2:		p[1] = val >> 8;
		fallthrough;
	शेष:	p[0] = val;
	पूर्ण
पूर्ण

#घोषणा ror13(v) ((v >> 13) | (v << 19))

#घोषणा dir_u8(idx)				\
	(अणु पूर्णांक _buf = idx >> blocksize_bits;	\
	   पूर्णांक _off = idx - (_buf << blocksize_bits);\
	  *(u8 *)(bh[_buf]->b_data + _off);	\
	पूर्ण)

#घोषणा dir_u32(idx)				\
	(अणु पूर्णांक _buf = idx >> blocksize_bits;	\
	   पूर्णांक _off = idx - (_buf << blocksize_bits);\
	  *(__le32 *)(bh[_buf]->b_data + _off);	\
	पूर्ण)

#घोषणा bufoff(_bh,_idx)			\
	(अणु पूर्णांक _buf = _idx >> blocksize_bits;	\
	   पूर्णांक _off = _idx - (_buf << blocksize_bits);\
	  (व्योम *)(_bh[_buf]->b_data + _off);	\
	पूर्ण)

/*
 * There are some algorithms that are nice in
 * assembler, but a bitch in C...  This is one
 * of them.
 */
अटल u8
adfs_dir_checkbyte(स्थिर काष्ठा adfs_dir *dir)
अणु
	काष्ठा buffer_head * स्थिर *bh = dir->bh;
	स्थिर पूर्णांक blocksize_bits = dir->sb->s_blocksize_bits;
	जोड़ अणु __le32 *ptr32; u8 *ptr8; पूर्ण ptr, end;
	u32 dircheck = 0;
	पूर्णांक last = 5 - 26;
	पूर्णांक i = 0;

	/*
	 * Accumulate each word up to the last whole
	 * word of the last directory entry.  This
	 * can spपढ़ो across several buffer heads.
	 */
	करो अणु
		last += 26;
		करो अणु
			dircheck = le32_to_cpu(dir_u32(i)) ^ ror13(dircheck);

			i += माप(u32);
		पूर्ण जबतक (i < (last & ~3));
	पूर्ण जबतक (dir_u8(last) != 0);

	/*
	 * Accumulate the last few bytes.  These
	 * bytes will be within the same bh.
	 */
	अगर (i != last) अणु
		ptr.ptr8 = bufoff(bh, i);
		end.ptr8 = ptr.ptr8 + last - i;

		करो अणु
			dircheck = *ptr.ptr8++ ^ ror13(dircheck);
		पूर्ण जबतक (ptr.ptr8 < end.ptr8);
	पूर्ण

	/*
	 * The directory tail is in the final bh
	 * Note that contary to the RISC OS PRMs,
	 * the first few bytes are NOT included
	 * in the check.  All bytes are in the
	 * same bh.
	 */
	ptr.ptr8 = bufoff(bh, 2008);
	end.ptr8 = ptr.ptr8 + 36;

	करो अणु
		__le32 v = *ptr.ptr32++;
		dircheck = le32_to_cpu(v) ^ ror13(dircheck);
	पूर्ण जबतक (ptr.ptr32 < end.ptr32);

	वापस (dircheck ^ (dircheck >> 8) ^ (dircheck >> 16) ^ (dircheck >> 24)) & 0xff;
पूर्ण

अटल पूर्णांक adfs_f_validate(काष्ठा adfs_dir *dir)
अणु
	काष्ठा adfs_dirheader *head = dir->dirhead;
	काष्ठा adfs_newdirtail *tail = dir->newtail;

	अगर (head->starपंचांगasseq != tail->endmasseq ||
	    tail->dirlasपंचांगask || tail->reserved[0] || tail->reserved[1] ||
	    (स_भेद(&head->startname, "Nick", 4) &&
	     स_भेद(&head->startname, "Hugo", 4)) ||
	    स_भेद(&head->startname, &tail->endname, 4) ||
	    adfs_dir_checkbyte(dir) != tail->dircheckbyte)
		वापस -EIO;

	वापस 0;
पूर्ण

/* Read and check that a directory is valid */
अटल पूर्णांक adfs_f_पढ़ो(काष्ठा super_block *sb, u32 indaddr, अचिन्हित पूर्णांक size,
		       काष्ठा adfs_dir *dir)
अणु
	स्थिर अचिन्हित पूर्णांक blocksize_bits = sb->s_blocksize_bits;
	पूर्णांक ret;

	अगर (size && size != ADFS_NEWसूची_SIZE)
		वापस -EIO;

	ret = adfs_dir_पढ़ो_buffers(sb, indaddr, ADFS_NEWसूची_SIZE, dir);
	अगर (ret)
		वापस ret;

	dir->dirhead = bufoff(dir->bh, 0);
	dir->newtail = bufoff(dir->bh, 2007);

	अगर (adfs_f_validate(dir))
		जाओ bad_dir;

	dir->parent_id = adfs_पढ़ोval(dir->newtail->dirparent, 3);

	वापस 0;

bad_dir:
	adfs_error(sb, "dir %06x is corrupted", indaddr);
	adfs_dir_rअन्यथा(dir);

	वापस -EIO;
पूर्ण

/*
 * convert a disk-based directory entry to a Linux ADFS directory entry
 */
अटल अंतरभूत व्योम
adfs_dir2obj(काष्ठा adfs_dir *dir, काष्ठा object_info *obj,
	काष्ठा adfs_direntry *de)
अणु
	अचिन्हित पूर्णांक name_len;

	क्रम (name_len = 0; name_len < ADFS_F_NAME_LEN; name_len++) अणु
		अगर (de->dirobname[name_len] < ' ')
			अवरोध;

		obj->name[name_len] = de->dirobname[name_len];
	पूर्ण

	obj->name_len =	name_len;
	obj->indaddr  = adfs_पढ़ोval(de->dirinddiscadd, 3);
	obj->loadaddr = adfs_पढ़ोval(de->dirload, 4);
	obj->execaddr = adfs_पढ़ोval(de->direxec, 4);
	obj->size     = adfs_पढ़ोval(de->dirlen,  4);
	obj->attr     = de->newdiratts;

	adfs_object_fixup(dir, obj);
पूर्ण

/*
 * convert a Linux ADFS directory entry to a disk-based directory entry
 */
अटल अंतरभूत व्योम
adfs_obj2dir(काष्ठा adfs_direntry *de, काष्ठा object_info *obj)
अणु
	adfs_ग_लिखोval(de->dirinddiscadd, 3, obj->indaddr);
	adfs_ग_लिखोval(de->dirload, 4, obj->loadaddr);
	adfs_ग_लिखोval(de->direxec, 4, obj->execaddr);
	adfs_ग_लिखोval(de->dirlen,  4, obj->size);
	de->newdiratts = obj->attr;
पूर्ण

/*
 * get a directory entry.  Note that the caller is responsible
 * क्रम holding the relevant locks.
 */
अटल पूर्णांक
__adfs_dir_get(काष्ठा adfs_dir *dir, पूर्णांक pos, काष्ठा object_info *obj)
अणु
	काष्ठा adfs_direntry de;
	पूर्णांक ret;

	ret = adfs_dir_copyfrom(&de, dir, pos, 26);
	अगर (ret)
		वापस ret;

	अगर (!de.dirobname[0])
		वापस -ENOENT;

	adfs_dir2obj(dir, obj, &de);

	वापस 0;
पूर्ण

अटल पूर्णांक
adfs_f_setpos(काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक fpos)
अणु
	अगर (fpos >= ADFS_NUM_सूची_ENTRIES)
		वापस -ENOENT;

	dir->pos = 5 + fpos * 26;
	वापस 0;
पूर्ण

अटल पूर्णांक
adfs_f_getnext(काष्ठा adfs_dir *dir, काष्ठा object_info *obj)
अणु
	अचिन्हित पूर्णांक ret;

	ret = __adfs_dir_get(dir, dir->pos, obj);
	अगर (ret == 0)
		dir->pos += 26;

	वापस ret;
पूर्ण

अटल पूर्णांक adfs_f_iterate(काष्ठा adfs_dir *dir, काष्ठा dir_context *ctx)
अणु
	काष्ठा object_info obj;
	पूर्णांक pos = 5 + (ctx->pos - 2) * 26;

	जबतक (ctx->pos < 2 + ADFS_NUM_सूची_ENTRIES) अणु
		अगर (__adfs_dir_get(dir, pos, &obj))
			अवरोध;
		अगर (!dir_emit(ctx, obj.name, obj.name_len,
			      obj.indaddr, DT_UNKNOWN))
			अवरोध;
		pos += 26;
		ctx->pos++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adfs_f_update(काष्ठा adfs_dir *dir, काष्ठा object_info *obj)
अणु
	काष्ठा adfs_direntry de;
	पूर्णांक offset, ret;

	offset = 5 - (पूर्णांक)माप(de);

	करो अणु
		offset += माप(de);
		ret = adfs_dir_copyfrom(&de, dir, offset, माप(de));
		अगर (ret) अणु
			adfs_error(dir->sb, "error reading directory entry");
			वापस -ENOENT;
		पूर्ण
		अगर (!de.dirobname[0]) अणु
			adfs_error(dir->sb, "unable to locate entry to update");
			वापस -ENOENT;
		पूर्ण
	पूर्ण जबतक (adfs_पढ़ोval(de.dirinddiscadd, 3) != obj->indaddr);

	/* Update the directory entry with the new object state */
	adfs_obj2dir(&de, obj);

	/* Write the directory entry back to the directory */
	वापस adfs_dir_copyto(dir, offset, &de, 26);
पूर्ण

अटल पूर्णांक adfs_f_commit(काष्ठा adfs_dir *dir)
अणु
	पूर्णांक ret;

	/* Increment directory sequence number */
	dir->dirhead->starपंचांगasseq += 1;
	dir->newtail->endmasseq += 1;

	/* Update directory check byte */
	dir->newtail->dircheckbyte = adfs_dir_checkbyte(dir);

	/* Make sure the directory still validates correctly */
	ret = adfs_f_validate(dir);
	अगर (ret)
		adfs_msg(dir->sb, KERN_ERR, "error: update broke directory");

	वापस ret;
पूर्ण

स्थिर काष्ठा adfs_dir_ops adfs_f_dir_ops = अणु
	.पढ़ो		= adfs_f_पढ़ो,
	.iterate	= adfs_f_iterate,
	.setpos		= adfs_f_setpos,
	.getnext	= adfs_f_getnext,
	.update		= adfs_f_update,
	.commit		= adfs_f_commit,
पूर्ण;
