<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/9p/vfs_dir.c
 *
 * This file contains vfs directory ops क्रम the 9P2000 protocol.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/inet.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/uपन.स>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"

/**
 * काष्ठा p9_rdir - सूची_पढ़ो accounting
 * @head: start offset of current dirपढ़ो buffer
 * @tail: end offset of current dirपढ़ो buffer
 * @buf: dirपढ़ो buffer
 *
 * निजी काष्ठाure क्रम keeping track of सूची_पढ़ो
 * allocated on demand
 */

काष्ठा p9_rdir अणु
	पूर्णांक head;
	पूर्णांक tail;
	uपूर्णांक8_t buf[];
पूर्ण;

/**
 * dt_type - वापस file type
 * @mistat: mistat काष्ठाure
 *
 */

अटल अंतरभूत पूर्णांक dt_type(काष्ठा p9_wstat *mistat)
अणु
	अचिन्हित दीर्घ perm = mistat->mode;
	पूर्णांक rettype = DT_REG;

	अगर (perm & P9_DMसूची)
		rettype = DT_सूची;
	अगर (perm & P9_DMSYMLINK)
		rettype = DT_LNK;

	वापस rettype;
पूर्ण

/**
 * v9fs_alloc_rdir_buf - Allocate buffer used क्रम पढ़ो and सूची_पढ़ो
 * @filp: खोलोed file काष्ठाure
 * @buflen: Length in bytes of buffer to allocate
 *
 */

अटल काष्ठा p9_rdir *v9fs_alloc_rdir_buf(काष्ठा file *filp, पूर्णांक buflen)
अणु
	काष्ठा p9_fid *fid = filp->निजी_data;
	अगर (!fid->rdir)
		fid->rdir = kzalloc(माप(काष्ठा p9_rdir) + buflen, GFP_KERNEL);
	वापस fid->rdir;
पूर्ण

/**
 * v9fs_dir_सूची_पढ़ो - iterate through a directory
 * @file: खोलोed file काष्ठाure
 * @ctx: actor we feed the entries to
 *
 */

अटल पूर्णांक v9fs_dir_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	bool over;
	काष्ठा p9_wstat st;
	पूर्णांक err = 0;
	काष्ठा p9_fid *fid;
	पूर्णांक buflen;
	काष्ठा p9_rdir *rdir;
	काष्ठा kvec kvec;

	p9_debug(P9_DEBUG_VFS, "name %pD\n", file);
	fid = file->निजी_data;

	buflen = fid->clnt->msize - P9_IOHDRSZ;

	rdir = v9fs_alloc_rdir_buf(file, buflen);
	अगर (!rdir)
		वापस -ENOMEM;
	kvec.iov_base = rdir->buf;
	kvec.iov_len = buflen;

	जबतक (1) अणु
		अगर (rdir->tail == rdir->head) अणु
			काष्ठा iov_iter to;
			पूर्णांक n;
			iov_iter_kvec(&to, READ, &kvec, 1, buflen);
			n = p9_client_पढ़ो(file->निजी_data, ctx->pos, &to,
					   &err);
			अगर (err)
				वापस err;
			अगर (n == 0)
				वापस 0;

			rdir->head = 0;
			rdir->tail = n;
		पूर्ण
		जबतक (rdir->head < rdir->tail) अणु
			err = p9stat_पढ़ो(fid->clnt, rdir->buf + rdir->head,
					  rdir->tail - rdir->head, &st);
			अगर (err <= 0) अणु
				p9_debug(P9_DEBUG_VFS, "returned %d\n", err);
				वापस -EIO;
			पूर्ण

			over = !dir_emit(ctx, st.name, म_माप(st.name),
					 v9fs_qid2ino(&st.qid), dt_type(&st));
			p9stat_मुक्त(&st);
			अगर (over)
				वापस 0;

			rdir->head += err;
			ctx->pos += err;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * v9fs_dir_सूची_पढ़ो_करोtl - iterate through a directory
 * @file: खोलोed file काष्ठाure
 * @ctx: actor we feed the entries to
 *
 */
अटल पूर्णांक v9fs_dir_सूची_पढ़ो_करोtl(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक err = 0;
	काष्ठा p9_fid *fid;
	पूर्णांक buflen;
	काष्ठा p9_rdir *rdir;
	काष्ठा p9_dirent curdirent;

	p9_debug(P9_DEBUG_VFS, "name %pD\n", file);
	fid = file->निजी_data;

	buflen = fid->clnt->msize - P9_READसूचीHDRSZ;

	rdir = v9fs_alloc_rdir_buf(file, buflen);
	अगर (!rdir)
		वापस -ENOMEM;

	जबतक (1) अणु
		अगर (rdir->tail == rdir->head) अणु
			err = p9_client_सूची_पढ़ो(fid, rdir->buf, buflen,
						ctx->pos);
			अगर (err <= 0)
				वापस err;

			rdir->head = 0;
			rdir->tail = err;
		पूर्ण

		जबतक (rdir->head < rdir->tail) अणु

			err = p9dirent_पढ़ो(fid->clnt, rdir->buf + rdir->head,
					    rdir->tail - rdir->head,
					    &curdirent);
			अगर (err < 0) अणु
				p9_debug(P9_DEBUG_VFS, "returned %d\n", err);
				वापस -EIO;
			पूर्ण

			अगर (!dir_emit(ctx, curdirent.d_name,
				      म_माप(curdirent.d_name),
				      v9fs_qid2ino(&curdirent.qid),
				      curdirent.d_type))
				वापस 0;

			ctx->pos = curdirent.d_off;
			rdir->head += err;
		पूर्ण
	पूर्ण
पूर्ण


/**
 * v9fs_dir_release - बंद a directory
 * @inode: inode of the directory
 * @filp: file poपूर्णांकer to a directory
 *
 */

पूर्णांक v9fs_dir_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा p9_fid *fid;

	fid = filp->निजी_data;
	p9_debug(P9_DEBUG_VFS, "inode: %p filp: %p fid: %d\n",
		 inode, filp, fid ? fid->fid : -1);
	अगर (fid) अणु
		spin_lock(&inode->i_lock);
		hlist_del(&fid->ilist);
		spin_unlock(&inode->i_lock);
		p9_client_clunk(fid);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations v9fs_dir_operations = अणु
	.पढ़ो = generic_पढ़ो_dir,
	.llseek = generic_file_llseek,
	.iterate_shared = v9fs_dir_सूची_पढ़ो,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_dir_operations_करोtl = अणु
	.पढ़ो = generic_पढ़ो_dir,
	.llseek = generic_file_llseek,
	.iterate_shared = v9fs_dir_सूची_पढ़ो_करोtl,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
        .fsync = v9fs_file_fsync_करोtl,
पूर्ण;
