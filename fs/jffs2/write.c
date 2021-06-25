<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mtd/mtd.h>
#समावेश "nodelist.h"
#समावेश "compr.h"


पूर्णांक jffs2_करो_new_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
		       uपूर्णांक32_t mode, काष्ठा jffs2_raw_inode *ri)
अणु
	काष्ठा jffs2_inode_cache *ic;

	ic = jffs2_alloc_inode_cache();
	अगर (!ic) अणु
		वापस -ENOMEM;
	पूर्ण

	स_रखो(ic, 0, माप(*ic));

	f->inocache = ic;
	f->inocache->pino_nlink = 1; /* Will be overwritten लघुly क्रम directories */
	f->inocache->nodes = (काष्ठा jffs2_raw_node_ref *)f->inocache;
	f->inocache->state = INO_STATE_PRESENT;

	jffs2_add_ino_cache(c, f->inocache);
	jffs2_dbg(1, "%s(): Assigned ino# %d\n", __func__, f->inocache->ino);
	ri->ino = cpu_to_je32(f->inocache->ino);

	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(PAD(माप(*ri)));
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4));
	ri->mode = cpu_to_jemode(mode);

	f->highest_version = 1;
	ri->version = cpu_to_je32(f->highest_version);

	वापस 0;
पूर्ण

/* jffs2_ग_लिखो_dnode - given a raw_inode, allocate a full_dnode क्रम it,
   ग_लिखो it to the flash, link it पूर्णांकo the existing inode/fragment list */

काष्ठा jffs2_full_dnode *jffs2_ग_लिखो_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
					   काष्ठा jffs2_raw_inode *ri, स्थिर अचिन्हित अक्षर *data,
					   uपूर्णांक32_t datalen, पूर्णांक alloc_mode)

अणु
	काष्ठा jffs2_full_dnode *fn;
	माप_प्रकार retlen;
	uपूर्णांक32_t flash_ofs;
	काष्ठा kvec vecs[2];
	पूर्णांक ret;
	पूर्णांक retried = 0;
	अचिन्हित दीर्घ cnt = 2;

	D1(अगर(je32_to_cpu(ri->hdr_crc) != crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4)) अणु
		pr_crit("Eep. CRC not correct in jffs2_write_dnode()\n");
		BUG();
	पूर्ण
	   );
	vecs[0].iov_base = ri;
	vecs[0].iov_len = माप(*ri);
	vecs[1].iov_base = (अचिन्हित अक्षर *)data;
	vecs[1].iov_len = datalen;

	अगर (je32_to_cpu(ri->totlen) != माप(*ri) + datalen) अणु
		pr_warn("%s(): ri->totlen (0x%08x) != sizeof(*ri) (0x%08zx) + datalen (0x%08x)\n",
			__func__, je32_to_cpu(ri->totlen),
			माप(*ri), datalen);
	पूर्ण

	fn = jffs2_alloc_full_dnode();
	अगर (!fn)
		वापस ERR_PTR(-ENOMEM);

	/* check number of valid vecs */
	अगर (!datalen || !data)
		cnt = 1;
 retry:
	flash_ofs = ग_लिखो_ofs(c);

	jffs2_dbg_preग_लिखो_paranoia_check(c, flash_ofs, vecs[0].iov_len + vecs[1].iov_len);

	अगर ((alloc_mode!=ALLOC_GC) && (je32_to_cpu(ri->version) < f->highest_version)) अणु
		BUG_ON(!retried);
		jffs2_dbg(1, "%s(): dnode_version %d, highest version %d -> updating dnode\n",
			  __func__,
			  je32_to_cpu(ri->version), f->highest_version);
		ri->version = cpu_to_je32(++f->highest_version);
		ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));
	पूर्ण

	ret = jffs2_flash_ग_लिखोv(c, vecs, cnt, flash_ofs, &retlen,
				 (alloc_mode==ALLOC_GC)?0:f->inocache->ino);

	अगर (ret || (retlen != माप(*ri) + datalen)) अणु
		pr_notice("Write of %zd bytes at 0x%08x failed. returned %d, retlen %zd\n",
			  माप(*ri) + datalen, flash_ofs, ret, retlen);

		/* Mark the space as dirtied */
		अगर (retlen) अणु
			/* Don't change raw->size to match retlen. We may have
			   written the node header alपढ़ोy, and only the data will
			   seem corrupted, in which हाल the scan would skip over
			   any node we ग_लिखो beक्रमe the original पूर्णांकended end of
			   this node */
			jffs2_add_physical_node_ref(c, flash_ofs | REF_OBSOLETE, PAD(माप(*ri)+datalen), शून्य);
		पूर्ण अन्यथा अणु
			pr_notice("Not marking the space at 0x%08x as dirty because the flash driver returned retlen zero\n",
				  flash_ofs);
		पूर्ण
		अगर (!retried && alloc_mode != ALLOC_NORETRY) अणु
			/* Try to पुनः_स्मृतिate space and retry */
			uपूर्णांक32_t dummy;
			काष्ठा jffs2_eraseblock *jeb = &c->blocks[flash_ofs / c->sector_size];

			retried = 1;

			jffs2_dbg(1, "Retrying failed write.\n");

			jffs2_dbg_acct_sanity_check(c,jeb);
			jffs2_dbg_acct_paranoia_check(c, jeb);

			अगर (alloc_mode == ALLOC_GC) अणु
				ret = jffs2_reserve_space_gc(c, माप(*ri) + datalen, &dummy,
							     JFFS2_SUMMARY_INODE_SIZE);
			पूर्ण अन्यथा अणु
				/* Locking pain */
				mutex_unlock(&f->sem);
				jffs2_complete_reservation(c);

				ret = jffs2_reserve_space(c, माप(*ri) + datalen, &dummy,
							  alloc_mode, JFFS2_SUMMARY_INODE_SIZE);
				mutex_lock(&f->sem);
			पूर्ण

			अगर (!ret) अणु
				flash_ofs = ग_लिखो_ofs(c);
				jffs2_dbg(1, "Allocated space at 0x%08x to retry failed write.\n",
					  flash_ofs);

				jffs2_dbg_acct_sanity_check(c,jeb);
				jffs2_dbg_acct_paranoia_check(c, jeb);

				जाओ retry;
			पूर्ण
			jffs2_dbg(1, "Failed to allocate space to retry failed write: %d!\n",
				  ret);
		पूर्ण
		/* Release the full_dnode which is now useless, and वापस */
		jffs2_मुक्त_full_dnode(fn);
		वापस ERR_PTR(ret?ret:-EIO);
	पूर्ण
	/* Mark the space used */
	/* If node covers at least a whole page, or अगर it starts at the
	   beginning of a page and runs to the end of the file, or अगर
	   it's a hole node, mark it REF_PRISTINE, अन्यथा REF_NORMAL.
	*/
	अगर ((je32_to_cpu(ri->dsize) >= PAGE_SIZE) ||
	    ( ((je32_to_cpu(ri->offset)&(PAGE_SIZE-1))==0) &&
	      (je32_to_cpu(ri->dsize)+je32_to_cpu(ri->offset) ==  je32_to_cpu(ri->isize)))) अणु
		flash_ofs |= REF_PRISTINE;
	पूर्ण अन्यथा अणु
		flash_ofs |= REF_NORMAL;
	पूर्ण
	fn->raw = jffs2_add_physical_node_ref(c, flash_ofs, PAD(माप(*ri)+datalen), f->inocache);
	अगर (IS_ERR(fn->raw)) अणु
		व्योम *hold_err = fn->raw;
		/* Release the full_dnode which is now useless, and वापस */
		jffs2_मुक्त_full_dnode(fn);
		वापस ERR_CAST(hold_err);
	पूर्ण
	fn->ofs = je32_to_cpu(ri->offset);
	fn->size = je32_to_cpu(ri->dsize);
	fn->frags = 0;

	jffs2_dbg(1, "jffs2_write_dnode wrote node at 0x%08x(%d) with dsize 0x%x, csize 0x%x, node_crc 0x%08x, data_crc 0x%08x, totlen 0x%08x\n",
		  flash_ofs & ~3, flash_ofs & 3, je32_to_cpu(ri->dsize),
		  je32_to_cpu(ri->csize), je32_to_cpu(ri->node_crc),
		  je32_to_cpu(ri->data_crc), je32_to_cpu(ri->totlen));

	अगर (retried) अणु
		jffs2_dbg_acct_sanity_check(c,शून्य);
	पूर्ण

	वापस fn;
पूर्ण

काष्ठा jffs2_full_dirent *jffs2_ग_लिखो_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
					     काष्ठा jffs2_raw_dirent *rd, स्थिर अचिन्हित अक्षर *name,
					     uपूर्णांक32_t namelen, पूर्णांक alloc_mode)
अणु
	काष्ठा jffs2_full_dirent *fd;
	माप_प्रकार retlen;
	काष्ठा kvec vecs[2];
	uपूर्णांक32_t flash_ofs;
	पूर्णांक retried = 0;
	पूर्णांक ret;

	jffs2_dbg(1, "%s(ino #%u, name at *0x%p \"%s\"->ino #%u, name_crc 0x%08x)\n",
		  __func__,
		  je32_to_cpu(rd->pino), name, name, je32_to_cpu(rd->ino),
		  je32_to_cpu(rd->name_crc));

	D1(अगर(je32_to_cpu(rd->hdr_crc) != crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4)) अणु
		pr_crit("Eep. CRC not correct in jffs2_write_dirent()\n");
		BUG();
	   पूर्ण);

	अगर (strnlen(name, namelen) != namelen) अणु
		/* This should never happen, but seems to have करोne on at least one
		   occasion: https://dev.laptop.org/ticket/4184 */
		pr_crit("Error in jffs2_write_dirent() -- name contains zero bytes!\n");
		pr_crit("Directory inode #%u, name at *0x%p \"%s\"->ino #%u, name_crc 0x%08x\n",
			je32_to_cpu(rd->pino), name, name, je32_to_cpu(rd->ino),
			je32_to_cpu(rd->name_crc));
		WARN_ON(1);
		वापस ERR_PTR(-EIO);
	पूर्ण

	vecs[0].iov_base = rd;
	vecs[0].iov_len = माप(*rd);
	vecs[1].iov_base = (अचिन्हित अक्षर *)name;
	vecs[1].iov_len = namelen;

	fd = jffs2_alloc_full_dirent(namelen+1);
	अगर (!fd)
		वापस ERR_PTR(-ENOMEM);

	fd->version = je32_to_cpu(rd->version);
	fd->ino = je32_to_cpu(rd->ino);
	fd->nhash = full_name_hash(शून्य, name, namelen);
	fd->type = rd->type;
	स_नकल(fd->name, name, namelen);
	fd->name[namelen]=0;

 retry:
	flash_ofs = ग_लिखो_ofs(c);

	jffs2_dbg_preग_लिखो_paranoia_check(c, flash_ofs, vecs[0].iov_len + vecs[1].iov_len);

	अगर ((alloc_mode!=ALLOC_GC) && (je32_to_cpu(rd->version) < f->highest_version)) अणु
		BUG_ON(!retried);
		jffs2_dbg(1, "%s(): dirent_version %d, highest version %d -> updating dirent\n",
			  __func__,
			  je32_to_cpu(rd->version), f->highest_version);
		rd->version = cpu_to_je32(++f->highest_version);
		fd->version = je32_to_cpu(rd->version);
		rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	पूर्ण

	ret = jffs2_flash_ग_लिखोv(c, vecs, 2, flash_ofs, &retlen,
				 (alloc_mode==ALLOC_GC)?0:je32_to_cpu(rd->pino));
	अगर (ret || (retlen != माप(*rd) + namelen)) अणु
		pr_notice("Write of %zd bytes at 0x%08x failed. returned %d, retlen %zd\n",
			  माप(*rd) + namelen, flash_ofs, ret, retlen);
		/* Mark the space as dirtied */
		अगर (retlen) अणु
			jffs2_add_physical_node_ref(c, flash_ofs | REF_OBSOLETE, PAD(माप(*rd)+namelen), शून्य);
		पूर्ण अन्यथा अणु
			pr_notice("Not marking the space at 0x%08x as dirty because the flash driver returned retlen zero\n",
				  flash_ofs);
		पूर्ण
		अगर (!retried) अणु
			/* Try to पुनः_स्मृतिate space and retry */
			uपूर्णांक32_t dummy;
			काष्ठा jffs2_eraseblock *jeb = &c->blocks[flash_ofs / c->sector_size];

			retried = 1;

			jffs2_dbg(1, "Retrying failed write.\n");

			jffs2_dbg_acct_sanity_check(c,jeb);
			jffs2_dbg_acct_paranoia_check(c, jeb);

			अगर (alloc_mode == ALLOC_GC) अणु
				ret = jffs2_reserve_space_gc(c, माप(*rd) + namelen, &dummy,
							     JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
			पूर्ण अन्यथा अणु
				/* Locking pain */
				mutex_unlock(&f->sem);
				jffs2_complete_reservation(c);

				ret = jffs2_reserve_space(c, माप(*rd) + namelen, &dummy,
							  alloc_mode, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
				mutex_lock(&f->sem);
			पूर्ण

			अगर (!ret) अणु
				flash_ofs = ग_लिखो_ofs(c);
				jffs2_dbg(1, "Allocated space at 0x%08x to retry failed write\n",
					  flash_ofs);
				jffs2_dbg_acct_sanity_check(c,jeb);
				jffs2_dbg_acct_paranoia_check(c, jeb);
				जाओ retry;
			पूर्ण
			jffs2_dbg(1, "Failed to allocate space to retry failed write: %d!\n",
				  ret);
		पूर्ण
		/* Release the full_dnode which is now useless, and वापस */
		jffs2_मुक्त_full_dirent(fd);
		वापस ERR_PTR(ret?ret:-EIO);
	पूर्ण
	/* Mark the space used */
	fd->raw = jffs2_add_physical_node_ref(c, flash_ofs | dirent_node_state(rd),
					      PAD(माप(*rd)+namelen), f->inocache);
	अगर (IS_ERR(fd->raw)) अणु
		व्योम *hold_err = fd->raw;
		/* Release the full_dirent which is now useless, and वापस */
		jffs2_मुक्त_full_dirent(fd);
		वापस ERR_CAST(hold_err);
	पूर्ण

	अगर (retried) अणु
		jffs2_dbg_acct_sanity_check(c,शून्य);
	पूर्ण

	वापस fd;
पूर्ण

/* The OS-specअगरic code fills in the metadata in the jffs2_raw_inode क्रम us, so that
   we करोn't have to go digging in काष्ठा inode or its equivalent. It should set:
   mode, uid, gid, (starting)isize, aसमय, स_समय, mसमय */
पूर्णांक jffs2_ग_लिखो_inode_range(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			    काष्ठा jffs2_raw_inode *ri, अचिन्हित अक्षर *buf,
			    uपूर्णांक32_t offset, uपूर्णांक32_t ग_लिखोlen, uपूर्णांक32_t *retlen)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t writtenlen = 0;

	jffs2_dbg(1, "%s(): Ino #%u, ofs 0x%x, len 0x%x\n",
		  __func__, f->inocache->ino, offset, ग_लिखोlen);

	जबतक(ग_लिखोlen) अणु
		काष्ठा jffs2_full_dnode *fn;
		अचिन्हित अक्षर *comprbuf = शून्य;
		uपूर्णांक16_t comprtype = JFFS2_COMPR_NONE;
		uपूर्णांक32_t alloclen;
		uपूर्णांक32_t datalen, cdatalen;
		पूर्णांक retried = 0;

	retry:
		jffs2_dbg(2, "jffs2_commit_write() loop: 0x%x to write to 0x%x\n",
			  ग_लिखोlen, offset);

		ret = jffs2_reserve_space(c, माप(*ri) + JFFS2_MIN_DATA_LEN,
					&alloclen, ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);
		अगर (ret) अणु
			jffs2_dbg(1, "jffs2_reserve_space returned %d\n", ret);
			अवरोध;
		पूर्ण
		mutex_lock(&f->sem);
		datalen = min_t(uपूर्णांक32_t, ग_लिखोlen,
				PAGE_SIZE - (offset & (PAGE_SIZE-1)));
		cdatalen = min_t(uपूर्णांक32_t, alloclen - माप(*ri), datalen);

		comprtype = jffs2_compress(c, f, buf, &comprbuf, &datalen, &cdatalen);

		ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		ri->totlen = cpu_to_je32(माप(*ri) + cdatalen);
		ri->hdr_crc = cpu_to_je32(crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4));

		ri->ino = cpu_to_je32(f->inocache->ino);
		ri->version = cpu_to_je32(++f->highest_version);
		ri->isize = cpu_to_je32(max(je32_to_cpu(ri->isize), offset + datalen));
		ri->offset = cpu_to_je32(offset);
		ri->csize = cpu_to_je32(cdatalen);
		ri->dsize = cpu_to_je32(datalen);
		ri->compr = comprtype & 0xff;
		ri->usercompr = (comprtype >> 8 ) & 0xff;
		ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));
		ri->data_crc = cpu_to_je32(crc32(0, comprbuf, cdatalen));

		fn = jffs2_ग_लिखो_dnode(c, f, ri, comprbuf, cdatalen, ALLOC_NORETRY);

		jffs2_मुक्त_comprbuf(comprbuf, buf);

		अगर (IS_ERR(fn)) अणु
			ret = PTR_ERR(fn);
			mutex_unlock(&f->sem);
			jffs2_complete_reservation(c);
			अगर (!retried) अणु
				/* Write error to be retried */
				retried = 1;
				jffs2_dbg(1, "Retrying node write in jffs2_write_inode_range()\n");
				जाओ retry;
			पूर्ण
			अवरोध;
		पूर्ण
		ret = jffs2_add_full_dnode_to_inode(c, f, fn);
		अगर (f->metadata) अणु
			jffs2_mark_node_obsolete(c, f->metadata->raw);
			jffs2_मुक्त_full_dnode(f->metadata);
			f->metadata = शून्य;
		पूर्ण
		अगर (ret) अणु
			/* Eep */
			jffs2_dbg(1, "Eep. add_full_dnode_to_inode() failed in commit_write, returned %d\n",
				  ret);
			jffs2_mark_node_obsolete(c, fn->raw);
			jffs2_मुक्त_full_dnode(fn);

			mutex_unlock(&f->sem);
			jffs2_complete_reservation(c);
			अवरोध;
		पूर्ण
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		अगर (!datalen) अणु
			pr_warn("Eep. We didn't actually write any data in jffs2_write_inode_range()\n");
			ret = -EIO;
			अवरोध;
		पूर्ण
		jffs2_dbg(1, "increasing writtenlen by %d\n", datalen);
		writtenlen += datalen;
		offset += datalen;
		ग_लिखोlen -= datalen;
		buf += datalen;
	पूर्ण
	*retlen = writtenlen;
	वापस ret;
पूर्ण

पूर्णांक jffs2_करो_create(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f,
		    काष्ठा jffs2_inode_info *f, काष्ठा jffs2_raw_inode *ri,
		    स्थिर काष्ठा qstr *qstr)
अणु
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dnode *fn;
	काष्ठा jffs2_full_dirent *fd;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	/* Try to reserve enough space क्रम both node and dirent.
	 * Just the node will करो क्रम now, though
	 */
	ret = jffs2_reserve_space(c, माप(*ri), &alloclen, ALLOC_NORMAL,
				JFFS2_SUMMARY_INODE_SIZE);
	jffs2_dbg(1, "%s(): reserved 0x%x bytes\n", __func__, alloclen);
	अगर (ret)
		वापस ret;

	mutex_lock(&f->sem);

	ri->data_crc = cpu_to_je32(0);
	ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));

	fn = jffs2_ग_लिखो_dnode(c, f, ri, शून्य, 0, ALLOC_NORMAL);

	jffs2_dbg(1, "jffs2_do_create created file with mode 0x%x\n",
		  jemode_to_cpu(ri->mode));

	अगर (IS_ERR(fn)) अणु
		jffs2_dbg(1, "jffs2_write_dnode() failed\n");
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		वापस PTR_ERR(fn);
	पूर्ण
	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data ग_लिखो
	*/
	f->metadata = fn;

	mutex_unlock(&f->sem);
	jffs2_complete_reservation(c);

	ret = jffs2_init_security(&f->vfs_inode, &dir_f->vfs_inode, qstr);
	अगर (ret)
		वापस ret;
	ret = jffs2_init_acl_post(&f->vfs_inode);
	अगर (ret)
		वापस ret;

	ret = jffs2_reserve_space(c, माप(*rd)+qstr->len, &alloclen,
				ALLOC_NORMAL, JFFS2_SUMMARY_सूचीENT_SIZE(qstr->len));

	अगर (ret) अणु
		/* Eep. */
		jffs2_dbg(1, "jffs2_reserve_space() for dirent failed\n");
		वापस ret;
	पूर्ण

	rd = jffs2_alloc_raw_dirent();
	अगर (!rd) अणु
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd->totlen = cpu_to_je32(माप(*rd) + qstr->len);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_f->inocache->ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = ri->ino;
	rd->mस_समय = ri->स_समय;
	rd->nsize = qstr->len;
	rd->type = DT_REG;
	rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, qstr->name, qstr->len));

	fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, qstr->name, qstr->len, ALLOC_NORMAL);

	jffs2_मुक्त_raw_dirent(rd);

	अगर (IS_ERR(fd)) अणु
		/* dirent failed to ग_लिखो. Delete the inode normally
		   as अगर it were the final unlink() */
		jffs2_complete_reservation(c);
		mutex_unlock(&dir_f->sem);
		वापस PTR_ERR(fd);
	पूर्ण

	/* Link the fd पूर्णांकo the inode's list, obsoleting an old
	   one अगर necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	jffs2_complete_reservation(c);
	mutex_unlock(&dir_f->sem);

	वापस 0;
पूर्ण


पूर्णांक jffs2_करो_unlink(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f,
		    स्थिर अक्षर *name, पूर्णांक namelen, काष्ठा jffs2_inode_info *dead_f,
		    uपूर्णांक32_t समय)
अणु
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dirent *fd;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	अगर (!jffs2_can_mark_obsolete(c)) अणु
		/* We can't mark stuff obsolete on the medium. We need to ग_लिखो a deletion dirent */

		rd = jffs2_alloc_raw_dirent();
		अगर (!rd)
			वापस -ENOMEM;

		ret = jffs2_reserve_space(c, माप(*rd)+namelen, &alloclen,
					ALLOC_DELETION, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
		अगर (ret) अणु
			jffs2_मुक्त_raw_dirent(rd);
			वापस ret;
		पूर्ण

		mutex_lock(&dir_f->sem);

		/* Build a deletion node */
		rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
		rd->totlen = cpu_to_je32(माप(*rd) + namelen);
		rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

		rd->pino = cpu_to_je32(dir_f->inocache->ino);
		rd->version = cpu_to_je32(++dir_f->highest_version);
		rd->ino = cpu_to_je32(0);
		rd->mस_समय = cpu_to_je32(समय);
		rd->nsize = namelen;
		rd->type = DT_UNKNOWN;
		rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
		rd->name_crc = cpu_to_je32(crc32(0, name, namelen));

		fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, name, namelen, ALLOC_DELETION);

		jffs2_मुक्त_raw_dirent(rd);

		अगर (IS_ERR(fd)) अणु
			jffs2_complete_reservation(c);
			mutex_unlock(&dir_f->sem);
			वापस PTR_ERR(fd);
		पूर्ण

		/* File it. This will mark the old one obsolete. */
		jffs2_add_fd_to_list(c, fd, &dir_f->dents);
		mutex_unlock(&dir_f->sem);
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t nhash = full_name_hash(शून्य, name, namelen);

		fd = dir_f->dents;
		/* We करोn't actually want to reserve any space, but we करो
		   want to be holding the alloc_sem when we ग_लिखो to flash */
		mutex_lock(&c->alloc_sem);
		mutex_lock(&dir_f->sem);

		क्रम (fd = dir_f->dents; fd; fd = fd->next) अणु
			अगर (fd->nhash == nhash &&
			    !स_भेद(fd->name, name, namelen) &&
			    !fd->name[namelen]) अणु

				jffs2_dbg(1, "Marking old dirent node (ino #%u) @%08x obsolete\n",
					  fd->ino, ref_offset(fd->raw));
				jffs2_mark_node_obsolete(c, fd->raw);
				/* We करोn't want to हटाओ it from the list immediately,
				   because that screws up getdents()/seek() semantics even
				   more than they're screwed alपढ़ोy. Turn it पूर्णांकo a
				   node-less deletion dirent instead -- a placeholder */
				fd->raw = शून्य;
				fd->ino = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&dir_f->sem);
	पूर्ण

	/* dead_f is शून्य अगर this was a नाम not a real unlink */
	/* Also catch the !f->inocache हाल, where there was a dirent
	   poपूर्णांकing to an inode which didn't exist. */
	अगर (dead_f && dead_f->inocache) अणु

		mutex_lock(&dead_f->sem);

		अगर (S_ISसूची(OFNI_EDONI_2SFFJ(dead_f)->i_mode)) अणु
			जबतक (dead_f->dents) अणु
				/* There can be only deleted ones */
				fd = dead_f->dents;

				dead_f->dents = fd->next;

				अगर (fd->ino) अणु
					pr_warn("Deleting inode #%u with active dentry \"%s\"->ino #%u\n",
						dead_f->inocache->ino,
						fd->name, fd->ino);
				पूर्ण अन्यथा अणु
					jffs2_dbg(1, "Removing deletion dirent for \"%s\" from dir ino #%u\n",
						  fd->name,
						  dead_f->inocache->ino);
				पूर्ण
				अगर (fd->raw)
					jffs2_mark_node_obsolete(c, fd->raw);
				jffs2_मुक्त_full_dirent(fd);
			पूर्ण
			dead_f->inocache->pino_nlink = 0;
		पूर्ण अन्यथा
			dead_f->inocache->pino_nlink--;
		/* NB: Caller must set inode nlink अगर appropriate */
		mutex_unlock(&dead_f->sem);
	पूर्ण

	jffs2_complete_reservation(c);

	वापस 0;
पूर्ण


पूर्णांक jffs2_करो_link (काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f, uपूर्णांक32_t ino, uपूर्णांक8_t type, स्थिर अक्षर *name, पूर्णांक namelen, uपूर्णांक32_t समय)
अणु
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dirent *fd;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	rd = jffs2_alloc_raw_dirent();
	अगर (!rd)
		वापस -ENOMEM;

	ret = jffs2_reserve_space(c, माप(*rd)+namelen, &alloclen,
				ALLOC_NORMAL, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
	अगर (ret) अणु
		jffs2_मुक्त_raw_dirent(rd);
		वापस ret;
	पूर्ण

	mutex_lock(&dir_f->sem);

	/* Build a deletion node */
	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd->totlen = cpu_to_je32(माप(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_f->inocache->ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(ino);
	rd->mस_समय = cpu_to_je32(समय);
	rd->nsize = namelen;

	rd->type = type;

	rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, name, namelen));

	fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, name, namelen, ALLOC_NORMAL);

	jffs2_मुक्त_raw_dirent(rd);

	अगर (IS_ERR(fd)) अणु
		jffs2_complete_reservation(c);
		mutex_unlock(&dir_f->sem);
		वापस PTR_ERR(fd);
	पूर्ण

	/* File it. This will mark the old one obsolete. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	jffs2_complete_reservation(c);
	mutex_unlock(&dir_f->sem);

	वापस 0;
पूर्ण
