<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/lockd/svcsubs.c
 *
 * Various support routines क्रम the NLM server.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/lockd/share.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <uapi/linux/nfs2.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_SVCSUBS


/*
 * Global file hash table
 */
#घोषणा खाता_HASH_BITS		7
#घोषणा खाता_NRHASH		(1<<खाता_HASH_BITS)
अटल काष्ठा hlist_head	nlm_files[खाता_NRHASH];
अटल DEFINE_MUTEX(nlm_file_mutex);

#अगर_घोषित CONFIG_SUNRPC_DEBUG
अटल अंतरभूत व्योम nlm_debug_prपूर्णांक_fh(अक्षर *msg, काष्ठा nfs_fh *f)
अणु
	u32 *fhp = (u32*)f->data;

	/* prपूर्णांक the first 32 bytes of the fh */
	dprपूर्णांकk("lockd: %s (%08x %08x %08x %08x %08x %08x %08x %08x)\n",
		msg, fhp[0], fhp[1], fhp[2], fhp[3],
		fhp[4], fhp[5], fhp[6], fhp[7]);
पूर्ण

अटल अंतरभूत व्योम nlm_debug_prपूर्णांक_file(अक्षर *msg, काष्ठा nlm_file *file)
अणु
	काष्ठा inode *inode = locks_inode(file->f_file);

	dprपूर्णांकk("lockd: %s %s/%ld\n",
		msg, inode->i_sb->s_id, inode->i_ino);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nlm_debug_prपूर्णांक_fh(अक्षर *msg, काष्ठा nfs_fh *f)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम nlm_debug_prपूर्णांक_file(अक्षर *msg, काष्ठा nlm_file *file)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक file_hash(काष्ठा nfs_fh *f)
अणु
	अचिन्हित पूर्णांक पंचांगp=0;
	पूर्णांक i;
	क्रम (i=0; i<NFS2_FHSIZE;i++)
		पंचांगp += f->data[i];
	वापस पंचांगp & (खाता_NRHASH - 1);
पूर्ण

/*
 * Lookup file info. If it करोesn't exist, create a file info काष्ठा
 * and खोलो a (VFS) file क्रम the given inode.
 *
 * FIXME:
 * Note that we खोलो the file O_RDONLY even when creating ग_लिखो locks.
 * This is not quite right, but क्रम now, we assume the client perक्रमms
 * the proper R/W checking.
 */
__be32
nlm_lookup_file(काष्ठा svc_rqst *rqstp, काष्ठा nlm_file **result,
					काष्ठा nfs_fh *f)
अणु
	काष्ठा nlm_file	*file;
	अचिन्हित पूर्णांक	hash;
	__be32		nfserr;

	nlm_debug_prपूर्णांक_fh("nlm_lookup_file", f);

	hash = file_hash(f);

	/* Lock file table */
	mutex_lock(&nlm_file_mutex);

	hlist_क्रम_each_entry(file, &nlm_files[hash], f_list)
		अगर (!nfs_compare_fh(&file->f_handle, f))
			जाओ found;

	nlm_debug_prपूर्णांक_fh("creating file for", f);

	nfserr = nlm_lck_denied_nolocks;
	file = kzalloc(माप(*file), GFP_KERNEL);
	अगर (!file)
		जाओ out_unlock;

	स_नकल(&file->f_handle, f, माप(काष्ठा nfs_fh));
	mutex_init(&file->f_mutex);
	INIT_HLIST_NODE(&file->f_list);
	INIT_LIST_HEAD(&file->f_blocks);

	/* Open the file. Note that this must not sleep क्रम too दीर्घ, अन्यथा
	 * we would lock up lockd:-) So no NFS re-exports, folks.
	 *
	 * We have to make sure we have the right credential to खोलो
	 * the file.
	 */
	अगर ((nfserr = nlmsvc_ops->ख_खोलो(rqstp, f, &file->f_file)) != 0) अणु
		dprपूर्णांकk("lockd: open failed (error %d)\n", nfserr);
		जाओ out_मुक्त;
	पूर्ण

	hlist_add_head(&file->f_list, &nlm_files[hash]);

found:
	dprपूर्णांकk("lockd: found file %p (count %d)\n", file, file->f_count);
	*result = file;
	file->f_count++;
	nfserr = 0;

out_unlock:
	mutex_unlock(&nlm_file_mutex);
	वापस nfserr;

out_मुक्त:
	kमुक्त(file);
	जाओ out_unlock;
पूर्ण

/*
 * Delete a file after having released all locks, blocks and shares
 */
अटल अंतरभूत व्योम
nlm_delete_file(काष्ठा nlm_file *file)
अणु
	nlm_debug_prपूर्णांक_file("closing file", file);
	अगर (!hlist_unhashed(&file->f_list)) अणु
		hlist_del(&file->f_list);
		nlmsvc_ops->ख_बंद(file->f_file);
		kमुक्त(file);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "lockd: attempt to release unknown file!\n");
	पूर्ण
पूर्ण

/*
 * Loop over all locks on the given file and perक्रमm the specअगरied
 * action.
 */
अटल पूर्णांक
nlm_traverse_locks(काष्ठा nlm_host *host, काष्ठा nlm_file *file,
			nlm_host_match_fn_t match)
अणु
	काष्ठा inode	 *inode = nlmsvc_file_inode(file);
	काष्ठा file_lock *fl;
	काष्ठा file_lock_context *flctx = inode->i_flctx;
	काष्ठा nlm_host	 *lockhost;

	अगर (!flctx || list_empty_careful(&flctx->flc_posix))
		वापस 0;
again:
	file->f_locks = 0;
	spin_lock(&flctx->flc_lock);
	list_क्रम_each_entry(fl, &flctx->flc_posix, fl_list) अणु
		अगर (fl->fl_lmops != &nlmsvc_lock_operations)
			जारी;

		/* update current lock count */
		file->f_locks++;

		lockhost = ((काष्ठा nlm_lockowner *)fl->fl_owner)->host;
		अगर (match(lockhost, host)) अणु
			काष्ठा file_lock lock = *fl;

			spin_unlock(&flctx->flc_lock);
			lock.fl_type  = F_UNLCK;
			lock.fl_start = 0;
			lock.fl_end   = OFFSET_MAX;
			अगर (vfs_lock_file(file->f_file, F_SETLK, &lock, शून्य) < 0) अणु
				prपूर्णांकk("lockd: unlock failure in %s:%d\n",
						__खाता__, __LINE__);
				वापस 1;
			पूर्ण
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock(&flctx->flc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
nlmsvc_always_match(व्योम *dummy1, काष्ठा nlm_host *dummy2)
अणु
	वापस 1;
पूर्ण

/*
 * Inspect a single file
 */
अटल अंतरभूत पूर्णांक
nlm_inspect_file(काष्ठा nlm_host *host, काष्ठा nlm_file *file, nlm_host_match_fn_t match)
अणु
	nlmsvc_traverse_blocks(host, file, match);
	nlmsvc_traverse_shares(host, file, match);
	वापस nlm_traverse_locks(host, file, match);
पूर्ण

/*
 * Quick check whether there are still any locks, blocks or
 * shares on a given file.
 */
अटल अंतरभूत पूर्णांक
nlm_file_inuse(काष्ठा nlm_file *file)
अणु
	काष्ठा inode	 *inode = nlmsvc_file_inode(file);
	काष्ठा file_lock *fl;
	काष्ठा file_lock_context *flctx = inode->i_flctx;

	अगर (file->f_count || !list_empty(&file->f_blocks) || file->f_shares)
		वापस 1;

	अगर (flctx && !list_empty_careful(&flctx->flc_posix)) अणु
		spin_lock(&flctx->flc_lock);
		list_क्रम_each_entry(fl, &flctx->flc_posix, fl_list) अणु
			अगर (fl->fl_lmops == &nlmsvc_lock_operations) अणु
				spin_unlock(&flctx->flc_lock);
				वापस 1;
			पूर्ण
		पूर्ण
		spin_unlock(&flctx->flc_lock);
	पूर्ण
	file->f_locks = 0;
	वापस 0;
पूर्ण

/*
 * Loop over all files in the file table.
 */
अटल पूर्णांक
nlm_traverse_files(व्योम *data, nlm_host_match_fn_t match,
		पूर्णांक (*is_failover_file)(व्योम *data, काष्ठा nlm_file *file))
अणु
	काष्ठा hlist_node *next;
	काष्ठा nlm_file	*file;
	पूर्णांक i, ret = 0;

	mutex_lock(&nlm_file_mutex);
	क्रम (i = 0; i < खाता_NRHASH; i++) अणु
		hlist_क्रम_each_entry_safe(file, next, &nlm_files[i], f_list) अणु
			अगर (is_failover_file && !is_failover_file(data, file))
				जारी;
			file->f_count++;
			mutex_unlock(&nlm_file_mutex);

			/* Traverse locks, blocks and shares of this file
			 * and update file->f_locks count */
			अगर (nlm_inspect_file(data, file, match))
				ret = 1;

			mutex_lock(&nlm_file_mutex);
			file->f_count--;
			/* No more references to this file. Let go of it. */
			अगर (list_empty(&file->f_blocks) && !file->f_locks
			 && !file->f_shares && !file->f_count) अणु
				hlist_del(&file->f_list);
				nlmsvc_ops->ख_बंद(file->f_file);
				kमुक्त(file);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&nlm_file_mutex);
	वापस ret;
पूर्ण

/*
 * Release file. If there are no more remote locks on this file,
 * बंद it and मुक्त the handle.
 *
 * Note that we can't करो proper reference counting without major
 * contortions because the code in fs/locks.c creates, deletes and
 * splits locks without notअगरication. Our only way is to walk the
 * entire lock list each समय we हटाओ a lock.
 */
व्योम
nlm_release_file(काष्ठा nlm_file *file)
अणु
	dprपूर्णांकk("lockd: nlm_release_file(%p, ct = %d)\n",
				file, file->f_count);

	/* Lock file table */
	mutex_lock(&nlm_file_mutex);

	/* If there are no more locks etc, delete the file */
	अगर (--file->f_count == 0 && !nlm_file_inuse(file))
		nlm_delete_file(file);

	mutex_unlock(&nlm_file_mutex);
पूर्ण

/*
 * Helpers function क्रम resource traversal
 *
 * nlmsvc_mark_host:
 *	used by the garbage collector; simply sets h_inuse only क्रम those
 *	hosts, which passed network check.
 *	Always वापसs 0.
 *
 * nlmsvc_same_host:
 *	वापसs 1 अगरf the two hosts match. Used to release
 *	all resources bound to a specअगरic host.
 *
 * nlmsvc_is_client:
 *	वापसs 1 अगरf the host is a client.
 *	Used by nlmsvc_invalidate_all
 */

अटल पूर्णांक
nlmsvc_mark_host(व्योम *data, काष्ठा nlm_host *hपूर्णांक)
अणु
	काष्ठा nlm_host *host = data;

	अगर ((hपूर्णांक->net == शून्य) ||
	    (host->net == hपूर्णांक->net))
		host->h_inuse = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
nlmsvc_same_host(व्योम *data, काष्ठा nlm_host *other)
अणु
	काष्ठा nlm_host *host = data;

	वापस host == other;
पूर्ण

अटल पूर्णांक
nlmsvc_is_client(व्योम *data, काष्ठा nlm_host *dummy)
अणु
	काष्ठा nlm_host *host = data;

	अगर (host->h_server) अणु
		/* we are destroying locks even though the client
		 * hasn't asked us too, so don't unmonitor the
		 * client
		 */
		अगर (host->h_nsmhandle)
			host->h_nsmhandle->sm_sticky = 1;
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

/*
 * Mark all hosts that still hold resources
 */
व्योम
nlmsvc_mark_resources(काष्ठा net *net)
अणु
	काष्ठा nlm_host hपूर्णांक;

	dprपूर्णांकk("lockd: %s for net %x\n", __func__, net ? net->ns.inum : 0);
	hपूर्णांक.net = net;
	nlm_traverse_files(&hपूर्णांक, nlmsvc_mark_host, शून्य);
पूर्ण

/*
 * Release all resources held by the given client
 */
व्योम
nlmsvc_मुक्त_host_resources(काष्ठा nlm_host *host)
अणु
	dprपूर्णांकk("lockd: nlmsvc_free_host_resources\n");

	अगर (nlm_traverse_files(host, nlmsvc_same_host, शून्य)) अणु
		prपूर्णांकk(KERN_WARNING
			"lockd: couldn't remove all locks held by %s\n",
			host->h_name);
		BUG();
	पूर्ण
पूर्ण

/**
 * nlmsvc_invalidate_all - हटाओ all locks held क्रम clients
 *
 * Release all locks held by NFS clients.
 *
 */
व्योम
nlmsvc_invalidate_all(व्योम)
अणु
	/*
	 * Previously, the code would call
	 * nlmsvc_मुक्त_host_resources क्रम each client in
	 * turn, which is about as inefficient as it माला_लो.
	 * Now we just करो it once in nlm_traverse_files.
	 */
	nlm_traverse_files(शून्य, nlmsvc_is_client, शून्य);
पूर्ण

अटल पूर्णांक
nlmsvc_match_sb(व्योम *datap, काष्ठा nlm_file *file)
अणु
	काष्ठा super_block *sb = datap;

	वापस sb == locks_inode(file->f_file)->i_sb;
पूर्ण

/**
 * nlmsvc_unlock_all_by_sb - release locks held on this file प्रणाली
 * @sb: super block
 *
 * Release all locks held by clients accessing this file प्रणाली.
 */
पूर्णांक
nlmsvc_unlock_all_by_sb(काष्ठा super_block *sb)
अणु
	पूर्णांक ret;

	ret = nlm_traverse_files(sb, nlmsvc_always_match, nlmsvc_match_sb);
	वापस ret ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(nlmsvc_unlock_all_by_sb);

अटल पूर्णांक
nlmsvc_match_ip(व्योम *datap, काष्ठा nlm_host *host)
अणु
	वापस rpc_cmp_addr(nlm_srcaddr(host), datap);
पूर्ण

/**
 * nlmsvc_unlock_all_by_ip - release local locks by IP address
 * @server_addr: server's IP address as seen by clients
 *
 * Release all locks held by clients accessing this host
 * via the passed in IP address.
 */
पूर्णांक
nlmsvc_unlock_all_by_ip(काष्ठा sockaddr *server_addr)
अणु
	पूर्णांक ret;

	ret = nlm_traverse_files(server_addr, nlmsvc_match_ip, शून्य);
	वापस ret ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(nlmsvc_unlock_all_by_ip);
