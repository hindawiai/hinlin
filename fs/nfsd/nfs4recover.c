<शैली गुरु>
/*
*  Copyright (c) 2004 The Regents of the University of Michigan.
*  Copyright (c) 2012 Jeff Layton <jlayton@redhat.com>
*  All rights reserved.
*
*  Andy Adamson <andros@citi.umich.edu>
*
*  Redistribution and use in source and binary क्रमms, with or without
*  modअगरication, are permitted provided that the following conditions
*  are met:
*
*  1. Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary क्रमm must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     करोcumentation and/or other materials provided with the distribution.
*  3. Neither the name of the University nor the names of its
*     contributors may be used to enकरोrse or promote products derived
*     from this software without specअगरic prior written permission.
*
*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
*  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#समावेश <crypto/hash.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfsd/cld.h>

#समावेश "nfsd.h"
#समावेश "state.h"
#समावेश "vfs.h"
#समावेश "netns.h"

#घोषणा NFSDDBG_FACILITY                NFSDDBG_PROC

/* Declarations */
काष्ठा nfsd4_client_tracking_ops अणु
	पूर्णांक (*init)(काष्ठा net *);
	व्योम (*निकास)(काष्ठा net *);
	व्योम (*create)(काष्ठा nfs4_client *);
	व्योम (*हटाओ)(काष्ठा nfs4_client *);
	पूर्णांक (*check)(काष्ठा nfs4_client *);
	व्योम (*grace_करोne)(काष्ठा nfsd_net *);
	uपूर्णांक8_t version;
	माप_प्रकार msglen;
पूर्ण;

अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_cld_tracking_ops;
अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_cld_tracking_ops_v2;

/* Globals */
अटल अक्षर user_recovery_स_नाम[PATH_MAX] = "/var/lib/nfs/v4recovery";

अटल पूर्णांक
nfs4_save_creds(स्थिर काष्ठा cred **original_creds)
अणु
	काष्ठा cred *new;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	new->fsuid = GLOBAL_ROOT_UID;
	new->fsgid = GLOBAL_ROOT_GID;
	*original_creds = override_creds(new);
	put_cred(new);
	वापस 0;
पूर्ण

अटल व्योम
nfs4_reset_creds(स्थिर काष्ठा cred *original)
अणु
	revert_creds(original);
पूर्ण

अटल व्योम
md5_to_hex(अक्षर *out, अक्षर *md5)
अणु
	पूर्णांक i;

	क्रम (i=0; i<16; i++) अणु
		अचिन्हित अक्षर c = md5[i];

		*out++ = '0' + ((c&0xf0)>>4) + (c>=0xa0)*('a'-'9'-1);
		*out++ = '0' + (c&0x0f) + ((c&0x0f)>=0x0a)*('a'-'9'-1);
	पूर्ण
	*out = '\0';
पूर्ण

अटल पूर्णांक
nfs4_make_rec_clidname(अक्षर *dname, स्थिर काष्ठा xdr_netobj *clname)
अणु
	काष्ठा xdr_netobj cksum;
	काष्ठा crypto_shash *tfm;
	पूर्णांक status;

	dprपूर्णांकk("NFSD: nfs4_make_rec_clidname for %.*s\n",
			clname->len, clname->data);
	tfm = crypto_alloc_shash("md5", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		status = PTR_ERR(tfm);
		जाओ out_no_tfm;
	पूर्ण

	cksum.len = crypto_shash_digestsize(tfm);
	cksum.data = kदो_स्मृति(cksum.len, GFP_KERNEL);
	अगर (cksum.data == शून्य) अणु
		status = -ENOMEM;
 		जाओ out;
	पूर्ण

	status = crypto_shash_tfm_digest(tfm, clname->data, clname->len,
					 cksum.data);
	अगर (status)
		जाओ out;

	md5_to_hex(dname, cksum.data);

	status = 0;
out:
	kमुक्त(cksum.data);
	crypto_मुक्त_shash(tfm);
out_no_tfm:
	वापस status;
पूर्ण

/*
 * If we had an error generating the recdir name क्रम the legacy tracker
 * then warn the admin. If the error करोesn't appear to be transient,
 * then disable recovery tracking.
 */
अटल व्योम
legacy_recdir_name_error(काष्ठा nfs4_client *clp, पूर्णांक error)
अणु
	prपूर्णांकk(KERN_ERR "NFSD: unable to generate recoverydir "
			"name (%d).\n", error);

	/*
	 * अगर the algorithm just करोesn't exist, then disable the recovery
	 * tracker altogether. The crypto libs will generally वापस this अगर
	 * FIPS is enabled as well.
	 */
	अगर (error == -ENOENT) अणु
		prपूर्णांकk(KERN_ERR "NFSD: disabling legacy clientid tracking. "
			"Reboot recovery will not function correctly!\n");
		nfsd4_client_tracking_निकास(clp->net);
	पूर्ण
पूर्ण

अटल व्योम
__nfsd4_create_reclaim_record_grace(काष्ठा nfs4_client *clp,
		स्थिर अक्षर *dname, पूर्णांक len, काष्ठा nfsd_net *nn)
अणु
	काष्ठा xdr_netobj name;
	काष्ठा xdr_netobj princhash = अणु .len = 0, .data = शून्य पूर्ण;
	काष्ठा nfs4_client_reclaim *crp;

	name.data = kmemdup(dname, len, GFP_KERNEL);
	अगर (!name.data) अणु
		dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
			__func__);
		वापस;
	पूर्ण
	name.len = len;
	crp = nfs4_client_to_reclaim(name, princhash, nn);
	अगर (!crp) अणु
		kमुक्त(name.data);
		वापस;
	पूर्ण
	crp->cr_clp = clp;
पूर्ण

अटल व्योम
nfsd4_create_clid_dir(काष्ठा nfs4_client *clp)
अणु
	स्थिर काष्ठा cred *original_cred;
	अक्षर dname[HEXसूची_LEN];
	काष्ठा dentry *dir, *dentry;
	पूर्णांक status;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (test_and_set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;
	अगर (!nn->rec_file)
		वापस;

	status = nfs4_make_rec_clidname(dname, &clp->cl_name);
	अगर (status)
		वापस legacy_recdir_name_error(clp, status);

	status = nfs4_save_creds(&original_cred);
	अगर (status < 0)
		वापस;

	status = mnt_want_ग_लिखो_file(nn->rec_file);
	अगर (status)
		जाओ out_creds;

	dir = nn->rec_file->f_path.dentry;
	/* lock the parent */
	inode_lock(d_inode(dir));

	dentry = lookup_one_len(dname, dir, HEXसूची_LEN-1);
	अगर (IS_ERR(dentry)) अणु
		status = PTR_ERR(dentry);
		जाओ out_unlock;
	पूर्ण
	अगर (d_really_is_positive(dentry))
		/*
		 * In the 4.1 हाल, where we're called from
		 * reclaim_complete(), records from the previous reboot
		 * may still be left, so this is OK.
		 *
		 * In the 4.0 हाल, we should never get here; but we may
		 * as well be क्रमgiving and just succeed silently.
		 */
		जाओ out_put;
	status = vfs_सूची_गढ़ो(&init_user_ns, d_inode(dir), dentry, S_IRWXU);
out_put:
	dput(dentry);
out_unlock:
	inode_unlock(d_inode(dir));
	अगर (status == 0) अणु
		अगर (nn->in_grace)
			__nfsd4_create_reclaim_record_grace(clp, dname,
					HEXसूची_LEN, nn);
		vfs_fsync(nn->rec_file, 0);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "NFSD: failed to write recovery record"
				" (err %d); please check that %s exists"
				" and is writeable", status,
				user_recovery_स_नाम);
	पूर्ण
	mnt_drop_ग_लिखो_file(nn->rec_file);
out_creds:
	nfs4_reset_creds(original_cred);
पूर्ण

प्रकार पूर्णांक (recdir_func)(काष्ठा dentry *, काष्ठा dentry *, काष्ठा nfsd_net *);

काष्ठा name_list अणु
	अक्षर name[HEXसूची_LEN];
	काष्ठा list_head list;
पूर्ण;

काष्ठा nfs4_dir_ctx अणु
	काष्ठा dir_context ctx;
	काष्ठा list_head names;
पूर्ण;

अटल पूर्णांक
nfsd4_build_namelist(काष्ठा dir_context *__ctx, स्थिर अक्षर *name, पूर्णांक namlen,
		loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा nfs4_dir_ctx *ctx =
		container_of(__ctx, काष्ठा nfs4_dir_ctx, ctx);
	काष्ठा name_list *entry;

	अगर (namlen != HEXसूची_LEN - 1)
		वापस 0;
	entry = kदो_स्मृति(माप(काष्ठा name_list), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस -ENOMEM;
	स_नकल(entry->name, name, HEXसूची_LEN - 1);
	entry->name[HEXसूची_LEN - 1] = '\0';
	list_add(&entry->list, &ctx->names);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfsd4_list_rec_dir(recdir_func *f, काष्ठा nfsd_net *nn)
अणु
	स्थिर काष्ठा cred *original_cred;
	काष्ठा dentry *dir = nn->rec_file->f_path.dentry;
	काष्ठा nfs4_dir_ctx ctx = अणु
		.ctx.actor = nfsd4_build_namelist,
		.names = LIST_HEAD_INIT(ctx.names)
	पूर्ण;
	काष्ठा name_list *entry, *पंचांगp;
	पूर्णांक status;

	status = nfs4_save_creds(&original_cred);
	अगर (status < 0)
		वापस status;

	status = vfs_llseek(nn->rec_file, 0, शुरू_से);
	अगर (status < 0) अणु
		nfs4_reset_creds(original_cred);
		वापस status;
	पूर्ण

	status = iterate_dir(nn->rec_file, &ctx.ctx);
	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);

	list_क्रम_each_entry_safe(entry, पंचांगp, &ctx.names, list) अणु
		अगर (!status) अणु
			काष्ठा dentry *dentry;
			dentry = lookup_one_len(entry->name, dir, HEXसूची_LEN-1);
			अगर (IS_ERR(dentry)) अणु
				status = PTR_ERR(dentry);
				अवरोध;
			पूर्ण
			status = f(dir, dentry, nn);
			dput(dentry);
		पूर्ण
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	inode_unlock(d_inode(dir));
	nfs4_reset_creds(original_cred);

	list_क्रम_each_entry_safe(entry, पंचांगp, &ctx.names, list) अणु
		dprपूर्णांकk("NFSD: %s. Left entry %s\n", __func__, entry->name);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक
nfsd4_unlink_clid_dir(अक्षर *name, पूर्णांक namlen, काष्ठा nfsd_net *nn)
अणु
	काष्ठा dentry *dir, *dentry;
	पूर्णांक status;

	dprपूर्णांकk("NFSD: nfsd4_unlink_clid_dir. name %.*s\n", namlen, name);

	dir = nn->rec_file->f_path.dentry;
	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);
	dentry = lookup_one_len(name, dir, namlen);
	अगर (IS_ERR(dentry)) अणु
		status = PTR_ERR(dentry);
		जाओ out_unlock;
	पूर्ण
	status = -ENOENT;
	अगर (d_really_is_negative(dentry))
		जाओ out;
	status = vfs_सूची_हटाओ(&init_user_ns, d_inode(dir), dentry);
out:
	dput(dentry);
out_unlock:
	inode_unlock(d_inode(dir));
	वापस status;
पूर्ण

अटल व्योम
__nfsd4_हटाओ_reclaim_record_grace(स्थिर अक्षर *dname, पूर्णांक len,
		काष्ठा nfsd_net *nn)
अणु
	काष्ठा xdr_netobj name;
	काष्ठा nfs4_client_reclaim *crp;

	name.data = kmemdup(dname, len, GFP_KERNEL);
	अगर (!name.data) अणु
		dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
			__func__);
		वापस;
	पूर्ण
	name.len = len;
	crp = nfsd4_find_reclaim_client(name, nn);
	kमुक्त(name.data);
	अगर (crp)
		nfs4_हटाओ_reclaim_record(crp, nn);
पूर्ण

अटल व्योम
nfsd4_हटाओ_clid_dir(काष्ठा nfs4_client *clp)
अणु
	स्थिर काष्ठा cred *original_cred;
	अक्षर dname[HEXसूची_LEN];
	पूर्णांक status;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (!nn->rec_file || !test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	status = nfs4_make_rec_clidname(dname, &clp->cl_name);
	अगर (status)
		वापस legacy_recdir_name_error(clp, status);

	status = mnt_want_ग_लिखो_file(nn->rec_file);
	अगर (status)
		जाओ out;
	clear_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);

	status = nfs4_save_creds(&original_cred);
	अगर (status < 0)
		जाओ out_drop_ग_लिखो;

	status = nfsd4_unlink_clid_dir(dname, HEXसूची_LEN-1, nn);
	nfs4_reset_creds(original_cred);
	अगर (status == 0) अणु
		vfs_fsync(nn->rec_file, 0);
		अगर (nn->in_grace)
			__nfsd4_हटाओ_reclaim_record_grace(dname,
					HEXसूची_LEN, nn);
	पूर्ण
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(nn->rec_file);
out:
	अगर (status)
		prपूर्णांकk("NFSD: Failed to remove expired client state directory"
				" %.*s\n", HEXसूची_LEN, dname);
पूर्ण

अटल पूर्णांक
purge_old(काष्ठा dentry *parent, काष्ठा dentry *child, काष्ठा nfsd_net *nn)
अणु
	पूर्णांक status;
	काष्ठा xdr_netobj name;

	अगर (child->d_name.len != HEXसूची_LEN - 1) अणु
		prपूर्णांकk("%s: illegal name %pd in recovery directory\n",
				__func__, child);
		/* Keep trying; maybe the others are OK: */
		वापस 0;
	पूर्ण
	name.data = kmemdup_nul(child->d_name.name, child->d_name.len, GFP_KERNEL);
	अगर (!name.data) अणु
		dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
			__func__);
		जाओ out;
	पूर्ण
	name.len = HEXसूची_LEN;
	अगर (nfs4_has_reclaimed_state(name, nn))
		जाओ out_मुक्त;

	status = vfs_सूची_हटाओ(&init_user_ns, d_inode(parent), child);
	अगर (status)
		prपूर्णांकk("failed to remove client recovery directory %pd\n",
				child);
out_मुक्त:
	kमुक्त(name.data);
out:
	/* Keep trying, success or failure: */
	वापस 0;
पूर्ण

अटल व्योम
nfsd4_recdir_purge_old(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक status;

	nn->in_grace = false;
	अगर (!nn->rec_file)
		वापस;
	status = mnt_want_ग_लिखो_file(nn->rec_file);
	अगर (status)
		जाओ out;
	status = nfsd4_list_rec_dir(purge_old, nn);
	अगर (status == 0)
		vfs_fsync(nn->rec_file, 0);
	mnt_drop_ग_लिखो_file(nn->rec_file);
out:
	nfs4_release_reclaim(nn);
	अगर (status)
		prपूर्णांकk("nfsd4: failed to purge old clients from recovery"
			" directory %pD\n", nn->rec_file);
पूर्ण

अटल पूर्णांक
load_recdir(काष्ठा dentry *parent, काष्ठा dentry *child, काष्ठा nfsd_net *nn)
अणु
	काष्ठा xdr_netobj name;
	काष्ठा xdr_netobj princhash = अणु .len = 0, .data = शून्य पूर्ण;

	अगर (child->d_name.len != HEXसूची_LEN - 1) अणु
		prपूर्णांकk("%s: illegal name %pd in recovery directory\n",
				__func__, child);
		/* Keep trying; maybe the others are OK: */
		वापस 0;
	पूर्ण
	name.data = kmemdup_nul(child->d_name.name, child->d_name.len, GFP_KERNEL);
	अगर (!name.data) अणु
		dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
			__func__);
		जाओ out;
	पूर्ण
	name.len = HEXसूची_LEN;
	अगर (!nfs4_client_to_reclaim(name, princhash, nn))
		kमुक्त(name.data);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
nfsd4_recdir_load(काष्ठा net *net) अणु
	पूर्णांक status;
	काष्ठा nfsd_net *nn =  net_generic(net, nfsd_net_id);

	अगर (!nn->rec_file)
		वापस 0;

	status = nfsd4_list_rec_dir(load_recdir, nn);
	अगर (status)
		prपूर्णांकk("nfsd4: failed loading clients from recovery"
			" directory %pD\n", nn->rec_file);
	वापस status;
पूर्ण

/*
 * Hold reference to the recovery directory.
 */

अटल पूर्णांक
nfsd4_init_recdir(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	स्थिर काष्ठा cred *original_cred;
	पूर्णांक status;

	prपूर्णांकk("NFSD: Using %s as the NFSv4 state recovery directory\n",
			user_recovery_स_नाम);

	BUG_ON(nn->rec_file);

	status = nfs4_save_creds(&original_cred);
	अगर (status < 0) अणु
		prपूर्णांकk("NFSD: Unable to change credentials to find recovery"
		       " directory: error %d\n",
		       status);
		वापस status;
	पूर्ण

	nn->rec_file = filp_खोलो(user_recovery_स_नाम, O_RDONLY | O_सूचीECTORY, 0);
	अगर (IS_ERR(nn->rec_file)) अणु
		prपूर्णांकk("NFSD: unable to find recovery directory %s\n",
				user_recovery_स_नाम);
		status = PTR_ERR(nn->rec_file);
		nn->rec_file = शून्य;
	पूर्ण

	nfs4_reset_creds(original_cred);
	अगर (!status)
		nn->in_grace = true;
	वापस status;
पूर्ण

अटल व्योम
nfsd4_shutकरोwn_recdir(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (!nn->rec_file)
		वापस;
	fput(nn->rec_file);
	nn->rec_file = शून्य;
पूर्ण

अटल पूर्णांक
nfs4_legacy_state_init(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक i;

	nn->reclaim_str_hashtbl = kदो_स्मृति_array(CLIENT_HASH_SIZE,
						माप(काष्ठा list_head),
						GFP_KERNEL);
	अगर (!nn->reclaim_str_hashtbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nn->reclaim_str_hashtbl[i]);
	nn->reclaim_str_hashtbl_size = 0;

	वापस 0;
पूर्ण

अटल व्योम
nfs4_legacy_state_shutकरोwn(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	kमुक्त(nn->reclaim_str_hashtbl);
पूर्ण

अटल पूर्णांक
nfsd4_load_reboot_recovery_data(काष्ठा net *net)
अणु
	पूर्णांक status;

	status = nfsd4_init_recdir(net);
	अगर (status)
		वापस status;

	status = nfsd4_recdir_load(net);
	अगर (status)
		nfsd4_shutकरोwn_recdir(net);

	वापस status;
पूर्ण

अटल पूर्णांक
nfsd4_legacy_tracking_init(काष्ठा net *net)
अणु
	पूर्णांक status;

	/* XXX: The legacy code won't work in a container */
	अगर (net != &init_net) अणु
		pr_warn("NFSD: attempt to initialize legacy client tracking in a container ignored.\n");
		वापस -EINVAL;
	पूर्ण

	status = nfs4_legacy_state_init(net);
	अगर (status)
		वापस status;

	status = nfsd4_load_reboot_recovery_data(net);
	अगर (status)
		जाओ err;
	pr_info("NFSD: Using legacy client tracking operations.\n");
	वापस 0;

err:
	nfs4_legacy_state_shutकरोwn(net);
	वापस status;
पूर्ण

अटल व्योम
nfsd4_legacy_tracking_निकास(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfs4_release_reclaim(nn);
	nfsd4_shutकरोwn_recdir(net);
	nfs4_legacy_state_shutकरोwn(net);
पूर्ण

/*
 * Change the NFSv4 recovery directory to recdir.
 */
पूर्णांक
nfs4_reset_recoverydir(अक्षर *recdir)
अणु
	पूर्णांक status;
	काष्ठा path path;

	status = kern_path(recdir, LOOKUP_FOLLOW, &path);
	अगर (status)
		वापस status;
	status = -ENOTसूची;
	अगर (d_is_dir(path.dentry)) अणु
		म_नकल(user_recovery_स_नाम, recdir);
		status = 0;
	पूर्ण
	path_put(&path);
	वापस status;
पूर्ण

अक्षर *
nfs4_recoverydir(व्योम)
अणु
	वापस user_recovery_स_नाम;
पूर्ण

अटल पूर्णांक
nfsd4_check_legacy_client(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक status;
	अक्षर dname[HEXसूची_LEN];
	काष्ठा nfs4_client_reclaim *crp;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा xdr_netobj name;

	/* did we alपढ़ोy find that this client is stable? */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस 0;

	status = nfs4_make_rec_clidname(dname, &clp->cl_name);
	अगर (status) अणु
		legacy_recdir_name_error(clp, status);
		वापस status;
	पूर्ण

	/* look क्रम it in the reclaim hashtable otherwise */
	name.data = kmemdup(dname, HEXसूची_LEN, GFP_KERNEL);
	अगर (!name.data) अणु
		dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
			__func__);
		जाओ out_enoent;
	पूर्ण
	name.len = HEXसूची_LEN;
	crp = nfsd4_find_reclaim_client(name, nn);
	kमुक्त(name.data);
	अगर (crp) अणु
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
		crp->cr_clp = clp;
		वापस 0;
	पूर्ण

out_enoent:
	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_legacy_tracking_ops = अणु
	.init		= nfsd4_legacy_tracking_init,
	.निकास		= nfsd4_legacy_tracking_निकास,
	.create		= nfsd4_create_clid_dir,
	.हटाओ		= nfsd4_हटाओ_clid_dir,
	.check		= nfsd4_check_legacy_client,
	.grace_करोne	= nfsd4_recdir_purge_old,
	.version	= 1,
	.msglen		= 0,
पूर्ण;

/* Globals */
#घोषणा NFSD_PIPE_सूची		"nfsd"
#घोषणा NFSD_CLD_PIPE		"cld"

/* per-net-ns काष्ठाure क्रम holding cld upcall info */
काष्ठा cld_net अणु
	काष्ठा rpc_pipe		*cn_pipe;
	spinlock_t		 cn_lock;
	काष्ठा list_head	 cn_list;
	अचिन्हित पूर्णांक		 cn_xid;
	bool			 cn_has_legacy;
	काष्ठा crypto_shash	*cn_tfm;
पूर्ण;

काष्ठा cld_upcall अणु
	काष्ठा list_head	 cu_list;
	काष्ठा cld_net		*cu_net;
	काष्ठा completion	 cu_करोne;
	जोड़ अणु
		काष्ठा cld_msg_hdr	 cu_hdr;
		काष्ठा cld_msg		 cu_msg;
		काष्ठा cld_msg_v2	 cu_msg_v2;
	पूर्ण cu_u;
पूर्ण;

अटल पूर्णांक
__cld_pipe_upcall(काष्ठा rpc_pipe *pipe, व्योम *cmsg, काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret;
	काष्ठा rpc_pipe_msg msg;
	काष्ठा cld_upcall *cup = container_of(cmsg, काष्ठा cld_upcall, cu_u);

	स_रखो(&msg, 0, माप(msg));
	msg.data = cmsg;
	msg.len = nn->client_tracking_ops->msglen;

	ret = rpc_queue_upcall(pipe, &msg);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण

	रुको_क्रम_completion(&cup->cu_करोne);

	अगर (msg.त्रुटि_सं < 0)
		ret = msg.त्रुटि_सं;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक
cld_pipe_upcall(काष्ठा rpc_pipe *pipe, व्योम *cmsg, काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret;

	/*
	 * -EAGAIN occurs when pipe is बंदd and reखोलोed जबतक there are
	 *  upcalls queued.
	 */
	करो अणु
		ret = __cld_pipe_upcall(pipe, cmsg, nn);
	पूर्ण जबतक (ret == -EAGAIN);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
__cld_pipe_inprogress_करोwncall(स्थिर काष्ठा cld_msg_v2 __user *cmsg,
		काष्ठा nfsd_net *nn)
अणु
	uपूर्णांक8_t cmd, princhashlen;
	काष्ठा xdr_netobj name, princhash = अणु .len = 0, .data = शून्य पूर्ण;
	uपूर्णांक16_t namelen;
	काष्ठा cld_net *cn = nn->cld_net;

	अगर (get_user(cmd, &cmsg->cm_cmd)) अणु
		dprपूर्णांकk("%s: error when copying cmd from userspace", __func__);
		वापस -EFAULT;
	पूर्ण
	अगर (cmd == Cld_GraceStart) अणु
		अगर (nn->client_tracking_ops->version >= 2) अणु
			स्थिर काष्ठा cld_clntinfo __user *ci;

			ci = &cmsg->cm_u.cm_clntinfo;
			अगर (get_user(namelen, &ci->cc_name.cn_len))
				वापस -EFAULT;
			name.data = memdup_user(&ci->cc_name.cn_id, namelen);
			अगर (IS_ERR_OR_शून्य(name.data))
				वापस -EFAULT;
			name.len = namelen;
			get_user(princhashlen, &ci->cc_princhash.cp_len);
			अगर (princhashlen > 0) अणु
				princhash.data = memdup_user(
						&ci->cc_princhash.cp_data,
						princhashlen);
				अगर (IS_ERR_OR_शून्य(princhash.data))
					वापस -EFAULT;
				princhash.len = princhashlen;
			पूर्ण अन्यथा
				princhash.len = 0;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा cld_name __user *cnm;

			cnm = &cmsg->cm_u.cm_name;
			अगर (get_user(namelen, &cnm->cn_len))
				वापस -EFAULT;
			name.data = memdup_user(&cnm->cn_id, namelen);
			अगर (IS_ERR_OR_शून्य(name.data))
				वापस -EFAULT;
			name.len = namelen;
		पूर्ण
		अगर (name.len > 5 && स_भेद(name.data, "hash:", 5) == 0) अणु
			name.len = name.len - 5;
			स_हटाओ(name.data, name.data + 5, name.len);
			cn->cn_has_legacy = true;
		पूर्ण
		अगर (!nfs4_client_to_reclaim(name, princhash, nn)) अणु
			kमुक्त(name.data);
			kमुक्त(princhash.data);
			वापस -EFAULT;
		पूर्ण
		वापस nn->client_tracking_ops->msglen;
	पूर्ण
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार
cld_pipe_करोwncall(काष्ठा file *filp, स्थिर अक्षर __user *src, माप_प्रकार mlen)
अणु
	काष्ठा cld_upcall *पंचांगp, *cup;
	काष्ठा cld_msg_hdr __user *hdr = (काष्ठा cld_msg_hdr __user *)src;
	काष्ठा cld_msg_v2 __user *cmsg = (काष्ठा cld_msg_v2 __user *)src;
	uपूर्णांक32_t xid;
	काष्ठा nfsd_net *nn = net_generic(file_inode(filp)->i_sb->s_fs_info,
						nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;
	पूर्णांक16_t status;

	अगर (mlen != nn->client_tracking_ops->msglen) अणु
		dprपूर्णांकk("%s: got %zu bytes, expected %zu\n", __func__, mlen,
			nn->client_tracking_ops->msglen);
		वापस -EINVAL;
	पूर्ण

	/* copy just the xid so we can try to find that */
	अगर (copy_from_user(&xid, &hdr->cm_xid, माप(xid)) != 0) अणु
		dprपूर्णांकk("%s: error when copying xid from userspace", __func__);
		वापस -EFAULT;
	पूर्ण

	/*
	 * copy the status so we know whether to हटाओ the upcall from the
	 * list (क्रम -EINPROGRESS, we just want to make sure the xid is
	 * valid, not हटाओ the upcall from the list)
	 */
	अगर (get_user(status, &hdr->cm_status)) अणु
		dprपूर्णांकk("%s: error when copying status from userspace", __func__);
		वापस -EFAULT;
	पूर्ण

	/* walk the list and find corresponding xid */
	cup = शून्य;
	spin_lock(&cn->cn_lock);
	list_क्रम_each_entry(पंचांगp, &cn->cn_list, cu_list) अणु
		अगर (get_unaligned(&पंचांगp->cu_u.cu_hdr.cm_xid) == xid) अणु
			cup = पंचांगp;
			अगर (status != -EINPROGRESS)
				list_del_init(&cup->cu_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cn->cn_lock);

	/* couldn't find upcall? */
	अगर (!cup) अणु
		dprपूर्णांकk("%s: couldn't find upcall -- xid=%u\n", __func__, xid);
		वापस -EINVAL;
	पूर्ण

	अगर (status == -EINPROGRESS)
		वापस __cld_pipe_inprogress_करोwncall(cmsg, nn);

	अगर (copy_from_user(&cup->cu_u.cu_msg_v2, src, mlen) != 0)
		वापस -EFAULT;

	complete(&cup->cu_करोne);
	वापस mlen;
पूर्ण

अटल व्योम
cld_pipe_destroy_msg(काष्ठा rpc_pipe_msg *msg)
अणु
	काष्ठा cld_msg *cmsg = msg->data;
	काष्ठा cld_upcall *cup = container_of(cmsg, काष्ठा cld_upcall,
						 cu_u.cu_msg);

	/* त्रुटि_सं >= 0 means we got a करोwncall */
	अगर (msg->त्रुटि_सं >= 0)
		वापस;

	complete(&cup->cu_करोne);
पूर्ण

अटल स्थिर काष्ठा rpc_pipe_ops cld_upcall_ops = अणु
	.upcall		= rpc_pipe_generic_upcall,
	.करोwncall	= cld_pipe_करोwncall,
	.destroy_msg	= cld_pipe_destroy_msg,
पूर्ण;

अटल काष्ठा dentry *
nfsd4_cld_रेजिस्टर_sb(काष्ठा super_block *sb, काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा dentry *dir, *dentry;

	dir = rpc_d_lookup_sb(sb, NFSD_PIPE_सूची);
	अगर (dir == शून्य)
		वापस ERR_PTR(-ENOENT);
	dentry = rpc_mkpipe_dentry(dir, NFSD_CLD_PIPE, शून्य, pipe);
	dput(dir);
	वापस dentry;
पूर्ण

अटल व्योम
nfsd4_cld_unरेजिस्टर_sb(काष्ठा rpc_pipe *pipe)
अणु
	अगर (pipe->dentry)
		rpc_unlink(pipe->dentry);
पूर्ण

अटल काष्ठा dentry *
nfsd4_cld_रेजिस्टर_net(काष्ठा net *net, काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा super_block *sb;
	काष्ठा dentry *dentry;

	sb = rpc_get_sb_net(net);
	अगर (!sb)
		वापस शून्य;
	dentry = nfsd4_cld_रेजिस्टर_sb(sb, pipe);
	rpc_put_sb_net(net);
	वापस dentry;
पूर्ण

अटल व्योम
nfsd4_cld_unरेजिस्टर_net(काष्ठा net *net, काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा super_block *sb;

	sb = rpc_get_sb_net(net);
	अगर (sb) अणु
		nfsd4_cld_unरेजिस्टर_sb(pipe);
		rpc_put_sb_net(net);
	पूर्ण
पूर्ण

/* Initialize rpc_pipefs pipe क्रम communication with client tracking daemon */
अटल पूर्णांक
__nfsd4_init_cld_pipe(काष्ठा net *net)
अणु
	पूर्णांक ret;
	काष्ठा dentry *dentry;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा cld_net *cn;

	अगर (nn->cld_net)
		वापस 0;

	cn = kzalloc(माप(*cn), GFP_KERNEL);
	अगर (!cn) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	cn->cn_pipe = rpc_mkpipe_data(&cld_upcall_ops, RPC_PIPE_WAIT_FOR_OPEN);
	अगर (IS_ERR(cn->cn_pipe)) अणु
		ret = PTR_ERR(cn->cn_pipe);
		जाओ err;
	पूर्ण
	spin_lock_init(&cn->cn_lock);
	INIT_LIST_HEAD(&cn->cn_list);

	dentry = nfsd4_cld_रेजिस्टर_net(net, cn->cn_pipe);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ err_destroy_data;
	पूर्ण

	cn->cn_pipe->dentry = dentry;
	cn->cn_has_legacy = false;
	nn->cld_net = cn;
	वापस 0;

err_destroy_data:
	rpc_destroy_pipe_data(cn->cn_pipe);
err:
	kमुक्त(cn);
	prपूर्णांकk(KERN_ERR "NFSD: unable to create nfsdcld upcall pipe (%d)\n",
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nfsd4_init_cld_pipe(काष्ठा net *net)
अणु
	पूर्णांक status;

	status = __nfsd4_init_cld_pipe(net);
	अगर (!status)
		pr_info("NFSD: Using old nfsdcld client tracking operations.\n");
	वापस status;
पूर्ण

अटल व्योम
nfsd4_हटाओ_cld_pipe(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;

	nfsd4_cld_unरेजिस्टर_net(net, cn->cn_pipe);
	rpc_destroy_pipe_data(cn->cn_pipe);
	अगर (cn->cn_tfm)
		crypto_मुक्त_shash(cn->cn_tfm);
	kमुक्त(nn->cld_net);
	nn->cld_net = शून्य;
पूर्ण

अटल काष्ठा cld_upcall *
alloc_cld_upcall(काष्ठा nfsd_net *nn)
अणु
	काष्ठा cld_upcall *new, *पंचांगp;
	काष्ठा cld_net *cn = nn->cld_net;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस new;

	/* FIXME: hard cap on number in flight? */
restart_search:
	spin_lock(&cn->cn_lock);
	list_क्रम_each_entry(पंचांगp, &cn->cn_list, cu_list) अणु
		अगर (पंचांगp->cu_u.cu_msg.cm_xid == cn->cn_xid) अणु
			cn->cn_xid++;
			spin_unlock(&cn->cn_lock);
			जाओ restart_search;
		पूर्ण
	पूर्ण
	init_completion(&new->cu_करोne);
	new->cu_u.cu_msg.cm_vers = nn->client_tracking_ops->version;
	put_unaligned(cn->cn_xid++, &new->cu_u.cu_msg.cm_xid);
	new->cu_net = cn;
	list_add(&new->cu_list, &cn->cn_list);
	spin_unlock(&cn->cn_lock);

	dprपूर्णांकk("%s: allocated xid %u\n", __func__, new->cu_u.cu_msg.cm_xid);

	वापस new;
पूर्ण

अटल व्योम
मुक्त_cld_upcall(काष्ठा cld_upcall *victim)
अणु
	काष्ठा cld_net *cn = victim->cu_net;

	spin_lock(&cn->cn_lock);
	list_del(&victim->cu_list);
	spin_unlock(&cn->cn_lock);
	kमुक्त(victim);
पूर्ण

/* Ask daemon to create a new record */
अटल व्योम
nfsd4_cld_create(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;

	/* Don't upcall if it's alपढ़ोy stored */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_Create;
	cup->cu_u.cu_msg.cm_u.cm_name.cn_len = clp->cl_name.len;
	स_नकल(cup->cu_u.cu_msg.cm_u.cm_name.cn_id, clp->cl_name.data,
			clp->cl_name.len);

	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret) अणु
		ret = cup->cu_u.cu_msg.cm_status;
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	पूर्ण

	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		prपूर्णांकk(KERN_ERR "NFSD: Unable to create client "
				"record on stable storage: %d\n", ret);
पूर्ण

/* Ask daemon to create a new record */
अटल व्योम
nfsd4_cld_create_v2(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;
	काष्ठा cld_msg_v2 *cmsg;
	काष्ठा crypto_shash *tfm = cn->cn_tfm;
	काष्ठा xdr_netobj cksum;
	अक्षर *principal = शून्य;

	/* Don't upcall if it's alपढ़ोy stored */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cmsg = &cup->cu_u.cu_msg_v2;
	cmsg->cm_cmd = Cld_Create;
	cmsg->cm_u.cm_clntinfo.cc_name.cn_len = clp->cl_name.len;
	स_नकल(cmsg->cm_u.cm_clntinfo.cc_name.cn_id, clp->cl_name.data,
			clp->cl_name.len);
	अगर (clp->cl_cred.cr_raw_principal)
		principal = clp->cl_cred.cr_raw_principal;
	अन्यथा अगर (clp->cl_cred.cr_principal)
		principal = clp->cl_cred.cr_principal;
	अगर (principal) अणु
		cksum.len = crypto_shash_digestsize(tfm);
		cksum.data = kदो_स्मृति(cksum.len, GFP_KERNEL);
		अगर (cksum.data == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = crypto_shash_tfm_digest(tfm, principal, म_माप(principal),
					      cksum.data);
		अगर (ret) अणु
			kमुक्त(cksum.data);
			जाओ out;
		पूर्ण
		cmsg->cm_u.cm_clntinfo.cc_princhash.cp_len = cksum.len;
		स_नकल(cmsg->cm_u.cm_clntinfo.cc_princhash.cp_data,
		       cksum.data, cksum.len);
		kमुक्त(cksum.data);
	पूर्ण अन्यथा
		cmsg->cm_u.cm_clntinfo.cc_princhash.cp_len = 0;

	ret = cld_pipe_upcall(cn->cn_pipe, cmsg, nn);
	अगर (!ret) अणु
		ret = cmsg->cm_status;
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	पूर्ण

out:
	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		pr_err("NFSD: Unable to create client record on stable storage: %d\n",
				ret);
पूर्ण

/* Ask daemon to create a new record */
अटल व्योम
nfsd4_cld_हटाओ(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;

	/* Don't upcall if it's alपढ़ोy हटाओd */
	अगर (!test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_Remove;
	cup->cu_u.cu_msg.cm_u.cm_name.cn_len = clp->cl_name.len;
	स_नकल(cup->cu_u.cu_msg.cm_u.cm_name.cn_id, clp->cl_name.data,
			clp->cl_name.len);

	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret) अणु
		ret = cup->cu_u.cu_msg.cm_status;
		clear_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	पूर्ण

	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		prपूर्णांकk(KERN_ERR "NFSD: Unable to remove client "
				"record from stable storage: %d\n", ret);
पूर्ण

/*
 * For older nfsdcld's that करो not allow us to "slurp" the clients
 * from the tracking database during startup.
 *
 * Check क्रम presence of a record, and update its बारtamp
 */
अटल पूर्णांक
nfsd4_cld_check_v0(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;

	/* Don't upcall अगर one was alपढ़ोy stored during this grace pd */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस 0;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		prपूर्णांकk(KERN_ERR "NFSD: Unable to check client record on "
				"stable storage: %d\n", -ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_Check;
	cup->cu_u.cu_msg.cm_u.cm_name.cn_len = clp->cl_name.len;
	स_नकल(cup->cu_u.cu_msg.cm_u.cm_name.cn_id, clp->cl_name.data,
			clp->cl_name.len);

	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret) अणु
		ret = cup->cu_u.cu_msg.cm_status;
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	पूर्ण

	मुक्त_cld_upcall(cup);
	वापस ret;
पूर्ण

/*
 * For newer nfsdcld's that allow us to "slurp" the clients
 * from the tracking database during startup.
 *
 * Check क्रम presence of a record in the reclaim_str_hashtbl
 */
अटल पूर्णांक
nfsd4_cld_check(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_client_reclaim *crp;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;
	पूर्णांक status;
	अक्षर dname[HEXसूची_LEN];
	काष्ठा xdr_netobj name;

	/* did we alपढ़ोy find that this client is stable? */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस 0;

	/* look क्रम it in the reclaim hashtable otherwise */
	crp = nfsd4_find_reclaim_client(clp->cl_name, nn);
	अगर (crp)
		जाओ found;

	अगर (cn->cn_has_legacy) अणु
		status = nfs4_make_rec_clidname(dname, &clp->cl_name);
		अगर (status)
			वापस -ENOENT;

		name.data = kmemdup(dname, HEXसूची_LEN, GFP_KERNEL);
		अगर (!name.data) अणु
			dprपूर्णांकk("%s: failed to allocate memory for name.data!\n",
				__func__);
			वापस -ENOENT;
		पूर्ण
		name.len = HEXसूची_LEN;
		crp = nfsd4_find_reclaim_client(name, nn);
		kमुक्त(name.data);
		अगर (crp)
			जाओ found;

	पूर्ण
	वापस -ENOENT;
found:
	crp->cr_clp = clp;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfsd4_cld_check_v2(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_client_reclaim *crp;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;
	पूर्णांक status;
	अक्षर dname[HEXसूची_LEN];
	काष्ठा xdr_netobj name;
	काष्ठा crypto_shash *tfm = cn->cn_tfm;
	काष्ठा xdr_netobj cksum;
	अक्षर *principal = शून्य;

	/* did we alपढ़ोy find that this client is stable? */
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस 0;

	/* look क्रम it in the reclaim hashtable otherwise */
	crp = nfsd4_find_reclaim_client(clp->cl_name, nn);
	अगर (crp)
		जाओ found;

	अगर (cn->cn_has_legacy) अणु
		status = nfs4_make_rec_clidname(dname, &clp->cl_name);
		अगर (status)
			वापस -ENOENT;

		name.data = kmemdup(dname, HEXसूची_LEN, GFP_KERNEL);
		अगर (!name.data) अणु
			dprपूर्णांकk("%s: failed to allocate memory for name.data\n",
					__func__);
			वापस -ENOENT;
		पूर्ण
		name.len = HEXसूची_LEN;
		crp = nfsd4_find_reclaim_client(name, nn);
		kमुक्त(name.data);
		अगर (crp)
			जाओ found;

	पूर्ण
	वापस -ENOENT;
found:
	अगर (crp->cr_princhash.len) अणु
		अगर (clp->cl_cred.cr_raw_principal)
			principal = clp->cl_cred.cr_raw_principal;
		अन्यथा अगर (clp->cl_cred.cr_principal)
			principal = clp->cl_cred.cr_principal;
		अगर (principal == शून्य)
			वापस -ENOENT;
		cksum.len = crypto_shash_digestsize(tfm);
		cksum.data = kदो_स्मृति(cksum.len, GFP_KERNEL);
		अगर (cksum.data == शून्य)
			वापस -ENOENT;
		status = crypto_shash_tfm_digest(tfm, principal,
						 म_माप(principal), cksum.data);
		अगर (status) अणु
			kमुक्त(cksum.data);
			वापस -ENOENT;
		पूर्ण
		अगर (स_भेद(crp->cr_princhash.data, cksum.data,
				crp->cr_princhash.len)) अणु
			kमुक्त(cksum.data);
			वापस -ENOENT;
		पूर्ण
		kमुक्त(cksum.data);
	पूर्ण
	crp->cr_clp = clp;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfsd4_cld_grace_start(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा cld_net *cn = nn->cld_net;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_GraceStart;
	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret)
		ret = cup->cu_u.cu_msg.cm_status;

	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		dprपूर्णांकk("%s: Unable to get clients from userspace: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

/* For older nfsdcld's that need cm_graceसमय */
अटल व्योम
nfsd4_cld_grace_करोne_v0(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा cld_net *cn = nn->cld_net;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_GraceDone;
	cup->cu_u.cu_msg.cm_u.cm_graceसमय = nn->boot_समय;
	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret)
		ret = cup->cu_u.cu_msg.cm_status;

	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		prपूर्णांकk(KERN_ERR "NFSD: Unable to end grace period: %d\n", ret);
पूर्ण

/*
 * For newer nfsdcld's that करो not need cm_graceसमय.  We also need to call
 * nfs4_release_reclaim() to clear out the reclaim_str_hashtbl.
 */
अटल व्योम
nfsd4_cld_grace_करोne(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret;
	काष्ठा cld_upcall *cup;
	काष्ठा cld_net *cn = nn->cld_net;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cup->cu_u.cu_msg.cm_cmd = Cld_GraceDone;
	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret)
		ret = cup->cu_u.cu_msg.cm_status;

	मुक्त_cld_upcall(cup);
out_err:
	nfs4_release_reclaim(nn);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "NFSD: Unable to end grace period: %d\n", ret);
पूर्ण

अटल पूर्णांक
nfs4_cld_state_init(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक i;

	nn->reclaim_str_hashtbl = kदो_स्मृति_array(CLIENT_HASH_SIZE,
						माप(काष्ठा list_head),
						GFP_KERNEL);
	अगर (!nn->reclaim_str_hashtbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nn->reclaim_str_hashtbl[i]);
	nn->reclaim_str_hashtbl_size = 0;
	nn->track_reclaim_completes = true;
	atomic_set(&nn->nr_reclaim_complete, 0);

	वापस 0;
पूर्ण

अटल व्योम
nfs4_cld_state_shutकरोwn(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nn->track_reclaim_completes = false;
	kमुक्त(nn->reclaim_str_hashtbl);
पूर्ण

अटल bool
cld_running(काष्ठा nfsd_net *nn)
अणु
	काष्ठा cld_net *cn = nn->cld_net;
	काष्ठा rpc_pipe *pipe = cn->cn_pipe;

	वापस pipe->nपढ़ोers || pipe->nग_लिखोrs;
पूर्ण

अटल पूर्णांक
nfsd4_cld_get_version(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक ret = 0;
	काष्ठा cld_upcall *cup;
	काष्ठा cld_net *cn = nn->cld_net;
	uपूर्णांक8_t version;

	cup = alloc_cld_upcall(nn);
	अगर (!cup) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण
	cup->cu_u.cu_msg.cm_cmd = Cld_GetVersion;
	ret = cld_pipe_upcall(cn->cn_pipe, &cup->cu_u.cu_msg, nn);
	अगर (!ret) अणु
		ret = cup->cu_u.cu_msg.cm_status;
		अगर (ret)
			जाओ out_मुक्त;
		version = cup->cu_u.cu_msg.cm_u.cm_version;
		dprपूर्णांकk("%s: userspace returned version %u\n",
				__func__, version);
		अगर (version < 1)
			version = 1;
		अन्यथा अगर (version > CLD_UPCALL_VERSION)
			version = CLD_UPCALL_VERSION;

		चयन (version) अणु
		हाल 1:
			nn->client_tracking_ops = &nfsd4_cld_tracking_ops;
			अवरोध;
		हाल 2:
			nn->client_tracking_ops = &nfsd4_cld_tracking_ops_v2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
out_मुक्त:
	मुक्त_cld_upcall(cup);
out_err:
	अगर (ret)
		dprपूर्णांकk("%s: Unable to get version from userspace: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nfsd4_cld_tracking_init(काष्ठा net *net)
अणु
	पूर्णांक status;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	bool running;
	पूर्णांक retries = 10;
	काष्ठा crypto_shash *tfm;

	status = nfs4_cld_state_init(net);
	अगर (status)
		वापस status;

	status = __nfsd4_init_cld_pipe(net);
	अगर (status)
		जाओ err_shutकरोwn;

	/*
	 * rpc pipe upcalls take 30 seconds to समय out, so we करोn't want to
	 * queue an upcall unless we know that nfsdcld is running (because we
	 * want this to fail fast so that nfsd4_client_tracking_init() can try
	 * the next client tracking method).  nfsdcld should alपढ़ोy be running
	 * beक्रमe nfsd is started, so the रुको here is क्रम nfsdcld to खोलो the
	 * pipefs file we just created.
	 */
	जबतक (!(running = cld_running(nn)) && retries--)
		msleep(100);

	अगर (!running) अणु
		status = -ETIMEDOUT;
		जाओ err_हटाओ;
	पूर्ण
	tfm = crypto_alloc_shash("sha256", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		status = PTR_ERR(tfm);
		जाओ err_हटाओ;
	पूर्ण
	nn->cld_net->cn_tfm = tfm;

	status = nfsd4_cld_get_version(nn);
	अगर (status == -EOPNOTSUPP)
		pr_warn("NFSD: nfsdcld GetVersion upcall failed. Please upgrade nfsdcld.\n");

	status = nfsd4_cld_grace_start(nn);
	अगर (status) अणु
		अगर (status == -EOPNOTSUPP)
			pr_warn("NFSD: nfsdcld GraceStart upcall failed. Please upgrade nfsdcld.\n");
		nfs4_release_reclaim(nn);
		जाओ err_हटाओ;
	पूर्ण अन्यथा
		pr_info("NFSD: Using nfsdcld client tracking operations.\n");
	वापस 0;

err_हटाओ:
	nfsd4_हटाओ_cld_pipe(net);
err_shutकरोwn:
	nfs4_cld_state_shutकरोwn(net);
	वापस status;
पूर्ण

अटल व्योम
nfsd4_cld_tracking_निकास(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfs4_release_reclaim(nn);
	nfsd4_हटाओ_cld_pipe(net);
	nfs4_cld_state_shutकरोwn(net);
पूर्ण

/* For older nfsdcld's */
अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_cld_tracking_ops_v0 = अणु
	.init		= nfsd4_init_cld_pipe,
	.निकास		= nfsd4_हटाओ_cld_pipe,
	.create		= nfsd4_cld_create,
	.हटाओ		= nfsd4_cld_हटाओ,
	.check		= nfsd4_cld_check_v0,
	.grace_करोne	= nfsd4_cld_grace_करोne_v0,
	.version	= 1,
	.msglen		= माप(काष्ठा cld_msg),
पूर्ण;

/* For newer nfsdcld's */
अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_cld_tracking_ops = अणु
	.init		= nfsd4_cld_tracking_init,
	.निकास		= nfsd4_cld_tracking_निकास,
	.create		= nfsd4_cld_create,
	.हटाओ		= nfsd4_cld_हटाओ,
	.check		= nfsd4_cld_check,
	.grace_करोne	= nfsd4_cld_grace_करोne,
	.version	= 1,
	.msglen		= माप(काष्ठा cld_msg),
पूर्ण;

/* v2 create/check ops include the principal, अगर available */
अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_cld_tracking_ops_v2 = अणु
	.init		= nfsd4_cld_tracking_init,
	.निकास		= nfsd4_cld_tracking_निकास,
	.create		= nfsd4_cld_create_v2,
	.हटाओ		= nfsd4_cld_हटाओ,
	.check		= nfsd4_cld_check_v2,
	.grace_करोne	= nfsd4_cld_grace_करोne,
	.version	= 2,
	.msglen		= माप(काष्ठा cld_msg_v2),
पूर्ण;

/* upcall via usermodehelper */
अटल अक्षर cltrack_prog[PATH_MAX] = "/sbin/nfsdcltrack";
module_param_string(cltrack_prog, cltrack_prog, माप(cltrack_prog),
			S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(cltrack_prog, "Path to the nfsdcltrack upcall program");

अटल bool cltrack_legacy_disable;
module_param(cltrack_legacy_disable, bool, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(cltrack_legacy_disable,
		"Disable legacy recoverydir conversion. Default: false");

#घोषणा LEGACY_TOPसूची_ENV_PREFIX "NFSDCLTRACK_LEGACY_TOPDIR="
#घोषणा LEGACY_RECसूची_ENV_PREFIX "NFSDCLTRACK_LEGACY_RECDIR="
#घोषणा HAS_SESSION_ENV_PREFIX "NFSDCLTRACK_CLIENT_HAS_SESSION="
#घोषणा GRACE_START_ENV_PREFIX "NFSDCLTRACK_GRACE_START="

अटल अक्षर *
nfsd4_cltrack_legacy_topdir(व्योम)
अणु
	पूर्णांक copied;
	माप_प्रकार len;
	अक्षर *result;

	अगर (cltrack_legacy_disable)
		वापस शून्य;

	len = म_माप(LEGACY_TOPसूची_ENV_PREFIX) +
		म_माप(nfs4_recoverydir()) + 1;

	result = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!result)
		वापस result;

	copied = snम_लिखो(result, len, LEGACY_TOPसूची_ENV_PREFIX "%s",
				nfs4_recoverydir());
	अगर (copied >= len) अणु
		/* just वापस nothing अगर output was truncated */
		kमुक्त(result);
		वापस शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल अक्षर *
nfsd4_cltrack_legacy_recdir(स्थिर काष्ठा xdr_netobj *name)
अणु
	पूर्णांक copied;
	माप_प्रकार len;
	अक्षर *result;

	अगर (cltrack_legacy_disable)
		वापस शून्य;

	/* +1 is क्रम '/' between "topdir" and "recdir" */
	len = म_माप(LEGACY_RECसूची_ENV_PREFIX) +
		म_माप(nfs4_recoverydir()) + 1 + HEXसूची_LEN;

	result = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!result)
		वापस result;

	copied = snम_लिखो(result, len, LEGACY_RECसूची_ENV_PREFIX "%s/",
				nfs4_recoverydir());
	अगर (copied > (len - HEXसूची_LEN)) अणु
		/* just वापस nothing अगर output will be truncated */
		kमुक्त(result);
		वापस शून्य;
	पूर्ण

	copied = nfs4_make_rec_clidname(result + copied, name);
	अगर (copied) अणु
		kमुक्त(result);
		वापस शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल अक्षर *
nfsd4_cltrack_client_has_session(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक copied;
	माप_प्रकार len;
	अक्षर *result;

	/* prefix + Y/N अक्षरacter + terminating शून्य */
	len = म_माप(HAS_SESSION_ENV_PREFIX) + 1 + 1;

	result = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!result)
		वापस result;

	copied = snम_लिखो(result, len, HAS_SESSION_ENV_PREFIX "%c",
				clp->cl_minorversion ? 'Y' : 'N');
	अगर (copied >= len) अणु
		/* just वापस nothing अगर output was truncated */
		kमुक्त(result);
		वापस शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल अक्षर *
nfsd4_cltrack_grace_start(समय64_t grace_start)
अणु
	पूर्णांक copied;
	माप_प्रकार len;
	अक्षर *result;

	/* prefix + max width of पूर्णांक64_t string + terminating शून्य */
	len = म_माप(GRACE_START_ENV_PREFIX) + 22 + 1;

	result = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!result)
		वापस result;

	copied = snम_लिखो(result, len, GRACE_START_ENV_PREFIX "%lld",
				grace_start);
	अगर (copied >= len) अणु
		/* just वापस nothing अगर output was truncated */
		kमुक्त(result);
		वापस शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक
nfsd4_umh_cltrack_upcall(अक्षर *cmd, अक्षर *arg, अक्षर *env0, अक्षर *env1)
अणु
	अक्षर *envp[3];
	अक्षर *argv[4];
	पूर्णांक ret;

	अगर (unlikely(!cltrack_prog[0])) अणु
		dprपूर्णांकk("%s: cltrack_prog is disabled\n", __func__);
		वापस -EACCES;
	पूर्ण

	dprपूर्णांकk("%s: cmd: %s\n", __func__, cmd);
	dprपूर्णांकk("%s: arg: %s\n", __func__, arg ? arg : "(null)");
	dprपूर्णांकk("%s: env0: %s\n", __func__, env0 ? env0 : "(null)");
	dprपूर्णांकk("%s: env1: %s\n", __func__, env1 ? env1 : "(null)");

	envp[0] = env0;
	envp[1] = env1;
	envp[2] = शून्य;

	argv[0] = (अक्षर *)cltrack_prog;
	argv[1] = cmd;
	argv[2] = arg;
	argv[3] = शून्य;

	ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	/*
	 * Disable the upcall mechanism अगर we're getting an ENOENT or EACCES
	 * error. The admin can re-enable it on the fly by using sysfs
	 * once the problem has been fixed.
	 */
	अगर (ret == -ENOENT || ret == -EACCES) अणु
		dprपूर्णांकk("NFSD: %s was not found or isn't executable (%d). "
			"Setting cltrack_prog to blank string!",
			cltrack_prog, ret);
		cltrack_prog[0] = '\0';
	पूर्ण
	dprपूर्णांकk("%s: %s return value: %d\n", __func__, cltrack_prog, ret);

	वापस ret;
पूर्ण

अटल अक्षर *
bin_to_hex_dup(स्थिर अचिन्हित अक्षर *src, पूर्णांक srclen)
अणु
	अक्षर *buf;

	/* +1 क्रम terminating शून्य */
	buf = kzalloc((srclen * 2) + 1, GFP_KERNEL);
	अगर (!buf)
		वापस buf;

	bin2hex(buf, src, srclen);
	वापस buf;
पूर्ण

अटल पूर्णांक
nfsd4_umh_cltrack_init(काष्ठा net *net)
अणु
	पूर्णांक ret;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	अक्षर *grace_start = nfsd4_cltrack_grace_start(nn->boot_समय);

	/* XXX: The usermode helper s not working in container yet. */
	अगर (net != &init_net) अणु
		pr_warn("NFSD: attempt to initialize umh client tracking in a container ignored.\n");
		kमुक्त(grace_start);
		वापस -EINVAL;
	पूर्ण

	ret = nfsd4_umh_cltrack_upcall("init", शून्य, grace_start, शून्य);
	kमुक्त(grace_start);
	अगर (!ret)
		pr_info("NFSD: Using UMH upcall client tracking operations.\n");
	वापस ret;
पूर्ण

अटल व्योम
nfsd4_cltrack_upcall_lock(काष्ठा nfs4_client *clp)
अणु
	रुको_on_bit_lock(&clp->cl_flags, NFSD4_CLIENT_UPCALL_LOCK,
			 TASK_UNINTERRUPTIBLE);
पूर्ण

अटल व्योम
nfsd4_cltrack_upcall_unlock(काष्ठा nfs4_client *clp)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(NFSD4_CLIENT_UPCALL_LOCK, &clp->cl_flags);
	smp_mb__after_atomic();
	wake_up_bit(&clp->cl_flags, NFSD4_CLIENT_UPCALL_LOCK);
पूर्ण

अटल व्योम
nfsd4_umh_cltrack_create(काष्ठा nfs4_client *clp)
अणु
	अक्षर *hexid, *has_session, *grace_start;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	/*
	 * With v4.0 clients, there's little dअगरference in outcome between a
	 * create and check operation, and we can end up calling पूर्णांकo this
	 * function multiple बार per client (once क्रम each खोलोowner). So,
	 * क्रम v4.0 clients skip upcalling once the client has been recorded
	 * on stable storage.
	 *
	 * For v4.1+ clients, the outcome of the two operations is dअगरferent,
	 * so we must ensure that we upcall क्रम the create operation. v4.1+
	 * clients call this on RECLAIM_COMPLETE though, so we should only end
	 * up करोing a single create upcall per client.
	 */
	अगर (clp->cl_minorversion == 0 &&
	    test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	hexid = bin_to_hex_dup(clp->cl_name.data, clp->cl_name.len);
	अगर (!hexid) अणु
		dprपूर्णांकk("%s: can't allocate memory for upcall!\n", __func__);
		वापस;
	पूर्ण

	has_session = nfsd4_cltrack_client_has_session(clp);
	grace_start = nfsd4_cltrack_grace_start(nn->boot_समय);

	nfsd4_cltrack_upcall_lock(clp);
	अगर (!nfsd4_umh_cltrack_upcall("create", hexid, has_session, grace_start))
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	nfsd4_cltrack_upcall_unlock(clp);

	kमुक्त(has_session);
	kमुक्त(grace_start);
	kमुक्त(hexid);
पूर्ण

अटल व्योम
nfsd4_umh_cltrack_हटाओ(काष्ठा nfs4_client *clp)
अणु
	अक्षर *hexid;

	अगर (!test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस;

	hexid = bin_to_hex_dup(clp->cl_name.data, clp->cl_name.len);
	अगर (!hexid) अणु
		dprपूर्णांकk("%s: can't allocate memory for upcall!\n", __func__);
		वापस;
	पूर्ण

	nfsd4_cltrack_upcall_lock(clp);
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags) &&
	    nfsd4_umh_cltrack_upcall("remove", hexid, शून्य, शून्य) == 0)
		clear_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	nfsd4_cltrack_upcall_unlock(clp);

	kमुक्त(hexid);
पूर्ण

अटल पूर्णांक
nfsd4_umh_cltrack_check(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक ret;
	अक्षर *hexid, *has_session, *legacy;

	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		वापस 0;

	hexid = bin_to_hex_dup(clp->cl_name.data, clp->cl_name.len);
	अगर (!hexid) अणु
		dprपूर्णांकk("%s: can't allocate memory for upcall!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	has_session = nfsd4_cltrack_client_has_session(clp);
	legacy = nfsd4_cltrack_legacy_recdir(&clp->cl_name);

	nfsd4_cltrack_upcall_lock(clp);
	अगर (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags)) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = nfsd4_umh_cltrack_upcall("check", hexid, has_session, legacy);
		अगर (ret == 0)
			set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
	पूर्ण
	nfsd4_cltrack_upcall_unlock(clp);
	kमुक्त(has_session);
	kमुक्त(legacy);
	kमुक्त(hexid);

	वापस ret;
पूर्ण

अटल व्योम
nfsd4_umh_cltrack_grace_करोne(काष्ठा nfsd_net *nn)
अणु
	अक्षर *legacy;
	अक्षर बारtr[22]; /* FIXME: better way to determine max size? */

	प्र_लिखो(बारtr, "%lld", nn->boot_समय);
	legacy = nfsd4_cltrack_legacy_topdir();
	nfsd4_umh_cltrack_upcall("gracedone", बारtr, legacy, शून्य);
	kमुक्त(legacy);
पूर्ण

अटल स्थिर काष्ठा nfsd4_client_tracking_ops nfsd4_umh_tracking_ops = अणु
	.init		= nfsd4_umh_cltrack_init,
	.निकास		= शून्य,
	.create		= nfsd4_umh_cltrack_create,
	.हटाओ		= nfsd4_umh_cltrack_हटाओ,
	.check		= nfsd4_umh_cltrack_check,
	.grace_करोne	= nfsd4_umh_cltrack_grace_करोne,
	.version	= 1,
	.msglen		= 0,
पूर्ण;

पूर्णांक
nfsd4_client_tracking_init(काष्ठा net *net)
अणु
	पूर्णांक status;
	काष्ठा path path;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	/* just run the init अगर it the method is alपढ़ोy decided */
	अगर (nn->client_tracking_ops)
		जाओ करो_init;

	/* First, try to use nfsdcld */
	nn->client_tracking_ops = &nfsd4_cld_tracking_ops;
	status = nn->client_tracking_ops->init(net);
	अगर (!status)
		वापस status;
	अगर (status != -ETIMEDOUT) अणु
		nn->client_tracking_ops = &nfsd4_cld_tracking_ops_v0;
		status = nn->client_tracking_ops->init(net);
		अगर (!status)
			वापस status;
	पूर्ण

	/*
	 * Next, try the UMH upcall.
	 */
	nn->client_tracking_ops = &nfsd4_umh_tracking_ops;
	status = nn->client_tracking_ops->init(net);
	अगर (!status)
		वापस status;

	/*
	 * Finally, See अगर the recoverydir exists and is a directory.
	 * If it is, then use the legacy ops.
	 */
	nn->client_tracking_ops = &nfsd4_legacy_tracking_ops;
	status = kern_path(nfs4_recoverydir(), LOOKUP_FOLLOW, &path);
	अगर (!status) अणु
		status = d_is_dir(path.dentry);
		path_put(&path);
		अगर (!status) अणु
			status = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

करो_init:
	status = nn->client_tracking_ops->init(net);
out:
	अगर (status) अणु
		prपूर्णांकk(KERN_WARNING "NFSD: Unable to initialize client "
				    "recovery tracking! (%d)\n", status);
		nn->client_tracking_ops = शून्य;
	पूर्ण
	वापस status;
पूर्ण

व्योम
nfsd4_client_tracking_निकास(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (nn->client_tracking_ops) अणु
		अगर (nn->client_tracking_ops->निकास)
			nn->client_tracking_ops->निकास(net);
		nn->client_tracking_ops = शून्य;
	पूर्ण
पूर्ण

व्योम
nfsd4_client_record_create(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (nn->client_tracking_ops)
		nn->client_tracking_ops->create(clp);
पूर्ण

व्योम
nfsd4_client_record_हटाओ(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (nn->client_tracking_ops)
		nn->client_tracking_ops->हटाओ(clp);
पूर्ण

पूर्णांक
nfsd4_client_record_check(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (nn->client_tracking_ops)
		वापस nn->client_tracking_ops->check(clp);

	वापस -EOPNOTSUPP;
पूर्ण

व्योम
nfsd4_record_grace_करोne(काष्ठा nfsd_net *nn)
अणु
	अगर (nn->client_tracking_ops)
		nn->client_tracking_ops->grace_करोne(nn);
पूर्ण

अटल पूर्णांक
rpc_pipefs_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा super_block *sb = ptr;
	काष्ठा net *net = sb->s_fs_info;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा cld_net *cn = nn->cld_net;
	काष्ठा dentry *dentry;
	पूर्णांक ret = 0;

	अगर (!try_module_get(THIS_MODULE))
		वापस 0;

	अगर (!cn) अणु
		module_put(THIS_MODULE);
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल RPC_PIPEFS_MOUNT:
		dentry = nfsd4_cld_रेजिस्टर_sb(sb, cn->cn_pipe);
		अगर (IS_ERR(dentry)) अणु
			ret = PTR_ERR(dentry);
			अवरोध;
		पूर्ण
		cn->cn_pipe->dentry = dentry;
		अवरोध;
	हाल RPC_PIPEFS_UMOUNT:
		अगर (cn->cn_pipe->dentry)
			nfsd4_cld_unरेजिस्टर_sb(cn->cn_pipe);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block nfsd4_cld_block = अणु
	.notअगरier_call = rpc_pipefs_event,
पूर्ण;

पूर्णांक
रेजिस्टर_cld_notअगरier(व्योम)
अणु
	वापस rpc_pipefs_notअगरier_रेजिस्टर(&nfsd4_cld_block);
पूर्ण

व्योम
unरेजिस्टर_cld_notअगरier(व्योम)
अणु
	rpc_pipefs_notअगरier_unरेजिस्टर(&nfsd4_cld_block);
पूर्ण
