<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/nfs/file.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 */
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/mount.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_ssc.h>
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"

#समावेश "nfstrace.h"

#अगर_घोषित CONFIG_NFS_V4_2
#समावेश "nfs42.h"
#पूर्ण_अगर

#घोषणा NFSDBG_FACILITY		NFSDBG_खाता

अटल पूर्णांक
nfs4_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा dentry *dentry = file_dentry(filp);
	काष्ठा dentry *parent = शून्य;
	काष्ठा inode *dir;
	अचिन्हित खोलोflags = filp->f_flags;
	काष्ठा iattr attr;
	पूर्णांक err;

	/*
	 * If no cached dentry exists or अगर it's negative, NFSv4 handled the
	 * खोलोs in ->lookup() or ->create().
	 *
	 * We only get this far क्रम a cached positive dentry.  We skipped
	 * revalidation, so handle it here by dropping the dentry and वापसing
	 * -EOPENSTALE.  The VFS will retry the lookup/create/खोलो.
	 */

	dprपूर्णांकk("NFS: open file(%pd2)\n", dentry);

	err = nfs_check_flags(खोलोflags);
	अगर (err)
		वापस err;

	अगर ((खोलोflags & O_ACCMODE) == 3)
		वापस nfs_खोलो(inode, filp);

	/* We can't create new files here */
	खोलोflags &= ~(O_CREAT|O_EXCL);

	parent = dget_parent(dentry);
	dir = d_inode(parent);

	ctx = alloc_nfs_खोलो_context(file_dentry(filp), filp->f_mode, filp);
	err = PTR_ERR(ctx);
	अगर (IS_ERR(ctx))
		जाओ out;

	attr.ia_valid = ATTR_OPEN;
	अगर (खोलोflags & O_TRUNC) अणु
		attr.ia_valid |= ATTR_SIZE;
		attr.ia_size = 0;
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
	पूर्ण

	inode = NFS_PROTO(dir)->खोलो_context(dir, ctx, खोलोflags, &attr, शून्य);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		चयन (err) अणु
		शेष:
			जाओ out_put_ctx;
		हाल -ENOENT:
		हाल -ESTALE:
		हाल -EISसूची:
		हाल -ENOTसूची:
		हाल -ELOOP:
			जाओ out_drop;
		पूर्ण
	पूर्ण
	अगर (inode != d_inode(dentry))
		जाओ out_drop;

	nfs_file_set_खोलो_context(filp, ctx);
	nfs_fscache_खोलो_file(inode, filp);
	err = 0;

out_put_ctx:
	put_nfs_खोलो_context(ctx);
out:
	dput(parent);
	वापस err;

out_drop:
	d_drop(dentry);
	err = -EOPENSTALE;
	जाओ out_put_ctx;
पूर्ण

/*
 * Flush all dirty pages, and check क्रम ग_लिखो errors.
 */
अटल पूर्णांक
nfs4_file_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा inode	*inode = file_inode(file);
	errseq_t since;

	dprपूर्णांकk("NFS: flush(%pD2)\n", file);

	nfs_inc_stats(inode, NFSIOS_VFSFLUSH);
	अगर ((file->f_mode & FMODE_WRITE) == 0)
		वापस 0;

	/*
	 * If we're holding a write delegation, then check if we're required
	 * to flush the i/o on बंद. If not, then just start the i/o now.
	 */
	अगर (!nfs4_delegation_flush_on_बंद(inode))
		वापस filemap_fdataग_लिखो(file->f_mapping);

	/* Flush ग_लिखोs to the server and वापस any errors */
	since = filemap_sample_wb_err(file->f_mapping);
	nfs_wb_all(inode);
	वापस filemap_check_wb_err(file->f_mapping, since);
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_2
अटल sमाप_प्रकार __nfs4_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				      काष्ठा file *file_out, loff_t pos_out,
				      माप_प्रकार count, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nfs42_copy_notअगरy_res *cn_resp = शून्य;
	काष्ठा nl4_server *nss = शून्य;
	nfs4_stateid *cnrs = शून्य;
	sमाप_प्रकार ret;
	bool sync = false;

	/* Only offload copy अगर superblock is the same */
	अगर (file_in->f_op != &nfs4_file_operations)
		वापस -EXDEV;
	अगर (!nfs_server_capable(file_inode(file_out), NFS_CAP_COPY) ||
	    !nfs_server_capable(file_inode(file_in), NFS_CAP_COPY))
		वापस -EOPNOTSUPP;
	अगर (file_inode(file_in) == file_inode(file_out))
		वापस -EOPNOTSUPP;
	/* अगर the copy size अगर smaller than 2 RPC payloads, make it
	 * synchronous
	 */
	अगर (count <= 2 * NFS_SERVER(file_inode(file_in))->rsize)
		sync = true;
retry:
	अगर (!nfs42_files_from_same_server(file_in, file_out)) अणु
		/* क्रम पूर्णांकer copy, अगर copy size अगर smaller than 12 RPC
		 * payloads, fallback to traditional copy. There are
		 * 14 RPCs during an NFSv4.x mount between source/dest
		 * servers.
		 */
		अगर (sync ||
			count <= 14 * NFS_SERVER(file_inode(file_in))->rsize)
			वापस -EOPNOTSUPP;
		cn_resp = kzalloc(माप(काष्ठा nfs42_copy_notअगरy_res),
				GFP_NOFS);
		अगर (unlikely(cn_resp == शून्य))
			वापस -ENOMEM;

		ret = nfs42_proc_copy_notअगरy(file_in, file_out, cn_resp);
		अगर (ret) अणु
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		nss = &cn_resp->cnr_src;
		cnrs = &cn_resp->cnr_stateid;
	पूर्ण
	ret = nfs42_proc_copy(file_in, pos_in, file_out, pos_out, count,
				nss, cnrs, sync);
out:
	अगर (!nfs42_files_from_same_server(file_in, file_out))
		kमुक्त(cn_resp);
	अगर (ret == -EAGAIN)
		जाओ retry;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nfs4_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				    काष्ठा file *file_out, loff_t pos_out,
				    माप_प्रकार count, अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार ret;

	ret = __nfs4_copy_file_range(file_in, pos_in, file_out, pos_out, count,
				     flags);
	अगर (ret == -EOPNOTSUPP || ret == -EXDEV)
		ret = generic_copy_file_range(file_in, pos_in, file_out,
					      pos_out, count, flags);
	वापस ret;
पूर्ण

अटल loff_t nfs4_file_llseek(काष्ठा file *filep, loff_t offset, पूर्णांक whence)
अणु
	loff_t ret;

	चयन (whence) अणु
	हाल SEEK_HOLE:
	हाल SEEK_DATA:
		ret = nfs42_proc_llseek(filep, offset, whence);
		अगर (ret != -EOPNOTSUPP)
			वापस ret;
		fallthrough;
	शेष:
		वापस nfs_file_llseek(filep, offset, whence);
	पूर्ण
पूर्ण

अटल दीर्घ nfs42_fallocate(काष्ठा file *filep, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(filep);
	दीर्घ ret;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EOPNOTSUPP;

	अगर ((mode != 0) && (mode != (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE)))
		वापस -EOPNOTSUPP;

	ret = inode_newsize_ok(inode, offset + len);
	अगर (ret < 0)
		वापस ret;

	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		वापस nfs42_proc_deallocate(filep, offset, len);
	वापस nfs42_proc_allocate(filep, offset, len);
पूर्ण

अटल loff_t nfs42_remap_file_range(काष्ठा file *src_file, loff_t src_off,
		काष्ठा file *dst_file, loff_t dst_off, loff_t count,
		अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *dst_inode = file_inode(dst_file);
	काष्ठा nfs_server *server = NFS_SERVER(dst_inode);
	काष्ठा inode *src_inode = file_inode(src_file);
	अचिन्हित पूर्णांक bs = server->clone_blksize;
	bool same_inode = false;
	पूर्णांक ret;

	/* NFS करोes not support deduplication. */
	अगर (remap_flags & REMAP_खाता_DEDUP)
		वापस -EOPNOTSUPP;

	अगर (remap_flags & ~REMAP_खाता_ADVISORY)
		वापस -EINVAL;

	अगर (IS_SWAPखाता(dst_inode) || IS_SWAPखाता(src_inode))
		वापस -ETXTBSY;

	/* check alignment w.r.t. clone_blksize */
	ret = -EINVAL;
	अगर (bs) अणु
		अगर (!IS_ALIGNED(src_off, bs) || !IS_ALIGNED(dst_off, bs))
			जाओ out;
		अगर (!IS_ALIGNED(count, bs) && i_size_पढ़ो(src_inode) != (src_off + count))
			जाओ out;
	पूर्ण

	अगर (src_inode == dst_inode)
		same_inode = true;

	/* XXX: करो we lock at all? what अगर server needs CB_RECALL_LAYOUT? */
	अगर (same_inode) अणु
		inode_lock(src_inode);
	पूर्ण अन्यथा अगर (dst_inode < src_inode) अणु
		inode_lock_nested(dst_inode, I_MUTEX_PARENT);
		inode_lock_nested(src_inode, I_MUTEX_CHILD);
	पूर्ण अन्यथा अणु
		inode_lock_nested(src_inode, I_MUTEX_PARENT);
		inode_lock_nested(dst_inode, I_MUTEX_CHILD);
	पूर्ण

	/* flush all pending ग_लिखोs on both src and dst so that server
	 * has the latest data */
	ret = nfs_sync_inode(src_inode);
	अगर (ret)
		जाओ out_unlock;
	ret = nfs_sync_inode(dst_inode);
	अगर (ret)
		जाओ out_unlock;

	ret = nfs42_proc_clone(src_file, dst_file, src_off, dst_off, count);

	/* truncate inode page cache of the dst range so that future पढ़ोs can fetch
	 * new data from server */
	अगर (!ret)
		truncate_inode_pages_range(&dst_inode->i_data, dst_off, dst_off + count - 1);

out_unlock:
	अगर (same_inode) अणु
		inode_unlock(src_inode);
	पूर्ण अन्यथा अगर (dst_inode < src_inode) अणु
		inode_unlock(src_inode);
		inode_unlock(dst_inode);
	पूर्ण अन्यथा अणु
		inode_unlock(dst_inode);
		inode_unlock(src_inode);
	पूर्ण
out:
	वापस ret < 0 ? ret : count;
पूर्ण

अटल पूर्णांक पढ़ो_name_gen = 1;
#घोषणा SSC_READ_NAME_BODY "ssc_read_%d"

अटल काष्ठा file *__nfs42_ssc_खोलो(काष्ठा vfsmount *ss_mnt,
		काष्ठा nfs_fh *src_fh, nfs4_stateid *stateid)
अणु
	काष्ठा nfs_fattr fattr;
	काष्ठा file *filep, *res;
	काष्ठा nfs_server *server;
	काष्ठा inode *r_ino = शून्य;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state_owner *sp;
	अक्षर *पढ़ो_name = शून्य;
	पूर्णांक len, status = 0;

	server = NFS_SERVER(ss_mnt->mnt_root->d_inode);

	nfs_fattr_init(&fattr);

	status = nfs4_proc_getattr(server, src_fh, &fattr, शून्य, शून्य);
	अगर (status < 0) अणु
		res = ERR_PTR(status);
		जाओ out;
	पूर्ण

	res = ERR_PTR(-ENOMEM);
	len = म_माप(SSC_READ_NAME_BODY) + 16;
	पढ़ो_name = kzalloc(len, GFP_NOFS);
	अगर (पढ़ो_name == शून्य)
		जाओ out;
	snम_लिखो(पढ़ो_name, len, SSC_READ_NAME_BODY, पढ़ो_name_gen++);

	r_ino = nfs_fhget(ss_mnt->mnt_root->d_inode->i_sb, src_fh, &fattr,
			शून्य);
	अगर (IS_ERR(r_ino)) अणु
		res = ERR_CAST(r_ino);
		जाओ out_मुक्त_name;
	पूर्ण

	filep = alloc_file_pseuकरो(r_ino, ss_mnt, पढ़ो_name, FMODE_READ,
				     r_ino->i_fop);
	अगर (IS_ERR(filep)) अणु
		res = ERR_CAST(filep);
		जाओ out_मुक्त_name;
	पूर्ण
	filep->f_mode |= FMODE_READ;

	ctx = alloc_nfs_खोलो_context(filep->f_path.dentry, filep->f_mode,
					filep);
	अगर (IS_ERR(ctx)) अणु
		res = ERR_CAST(ctx);
		जाओ out_filep;
	पूर्ण

	res = ERR_PTR(-EINVAL);
	sp = nfs4_get_state_owner(server, ctx->cred, GFP_KERNEL);
	अगर (sp == शून्य)
		जाओ out_ctx;

	ctx->state = nfs4_get_खोलो_state(r_ino, sp);
	अगर (ctx->state == शून्य)
		जाओ out_stateowner;

	set_bit(NFS_SRV_SSC_COPY_STATE, &ctx->state->flags);
	स_नकल(&ctx->state->खोलो_stateid.other, &stateid->other,
	       NFS4_STATEID_OTHER_SIZE);
	update_खोलो_stateid(ctx->state, stateid, शून्य, filep->f_mode);
	set_bit(NFS_OPEN_STATE, &ctx->state->flags);

	nfs_file_set_खोलो_context(filep, ctx);
	put_nfs_खोलो_context(ctx);

	file_ra_state_init(&filep->f_ra, filep->f_mapping->host->i_mapping);
	res = filep;
out_मुक्त_name:
	kमुक्त(पढ़ो_name);
out:
	वापस res;
out_stateowner:
	nfs4_put_state_owner(sp);
out_ctx:
	put_nfs_खोलो_context(ctx);
out_filep:
	fput(filep);
	जाओ out_मुक्त_name;
पूर्ण

अटल व्योम __nfs42_ssc_बंद(काष्ठा file *filep)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(filep);

	ctx->state->flags = 0;
पूर्ण

अटल स्थिर काष्ठा nfs4_ssc_client_ops nfs4_ssc_clnt_ops_tbl = अणु
	.sco_खोलो = __nfs42_ssc_खोलो,
	.sco_बंद = __nfs42_ssc_बंद,
पूर्ण;

/**
 * nfs42_ssc_रेजिस्टर_ops - Wrapper to रेजिस्टर NFS_V4 ops in nfs_common
 *
 * Return values:
 *   None
 */
व्योम nfs42_ssc_रेजिस्टर_ops(व्योम)
अणु
	nfs42_ssc_रेजिस्टर(&nfs4_ssc_clnt_ops_tbl);
पूर्ण

/**
 * nfs42_ssc_unरेजिस्टर_ops - wrapper to un-रेजिस्टर NFS_V4 ops in nfs_common
 *
 * Return values:
 *   None.
 */
व्योम nfs42_ssc_unरेजिस्टर_ops(व्योम)
अणु
	nfs42_ssc_unरेजिस्टर(&nfs4_ssc_clnt_ops_tbl);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

स्थिर काष्ठा file_operations nfs4_file_operations = अणु
	.पढ़ो_iter	= nfs_file_पढ़ो,
	.ग_लिखो_iter	= nfs_file_ग_लिखो,
	.mmap		= nfs_file_mmap,
	.खोलो		= nfs4_file_खोलो,
	.flush		= nfs4_file_flush,
	.release	= nfs_file_release,
	.fsync		= nfs_file_fsync,
	.lock		= nfs_lock,
	.flock		= nfs_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.check_flags	= nfs_check_flags,
	.setlease	= simple_nosetlease,
#अगर_घोषित CONFIG_NFS_V4_2
	.copy_file_range = nfs4_copy_file_range,
	.llseek		= nfs4_file_llseek,
	.fallocate	= nfs42_fallocate,
	.remap_file_range = nfs42_remap_file_range,
#अन्यथा
	.llseek		= nfs_file_llseek,
#पूर्ण_अगर
पूर्ण;
