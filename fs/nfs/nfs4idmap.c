<शैली गुरु>
/*
 * fs/nfs/idmap.c
 *
 *  UID and GID to name mapping क्रम clients.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Marius Aamodt Eriksen <marius@umich.edu>
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
 */
#समावेश <linux/types.h>
#समावेश <linux/parser.h>
#समावेश <linux/fs.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_fs_sb.h>
#समावेश <linux/key.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>
#समावेश <keys/request_key_auth-type.h>
#समावेश <linux/module.h>
#समावेश <linux/user_namespace.h>

#समावेश "internal.h"
#समावेश "netns.h"
#समावेश "nfs4idmap.h"
#समावेश "nfs4trace.h"

#घोषणा NFS_अच_पूर्णांक_उच्चLEN 11

अटल स्थिर काष्ठा cred *id_resolver_cache;
अटल काष्ठा key_type key_type_id_resolver_legacy;

काष्ठा idmap_legacy_upcalldata अणु
	काष्ठा rpc_pipe_msg pipe_msg;
	काष्ठा idmap_msg idmap_msg;
	काष्ठा key	*authkey;
	काष्ठा idmap *idmap;
पूर्ण;

काष्ठा idmap अणु
	काष्ठा rpc_pipe_dir_object idmap_pकरो;
	काष्ठा rpc_pipe		*idmap_pipe;
	काष्ठा idmap_legacy_upcalldata *idmap_upcall_data;
	काष्ठा mutex		idmap_mutex;
	काष्ठा user_namespace	*user_ns;
पूर्ण;

अटल काष्ठा user_namespace *idmap_userns(स्थिर काष्ठा idmap *idmap)
अणु
	अगर (idmap && idmap->user_ns)
		वापस idmap->user_ns;
	वापस &init_user_ns;
पूर्ण

/**
 * nfs_fattr_init_names - initialise the nfs_fattr owner_name/group_name fields
 * @fattr: fully initialised काष्ठा nfs_fattr
 * @owner_name: owner name string cache
 * @group_name: group name string cache
 */
व्योम nfs_fattr_init_names(काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_string *owner_name,
		काष्ठा nfs4_string *group_name)
अणु
	fattr->owner_name = owner_name;
	fattr->group_name = group_name;
पूर्ण

अटल व्योम nfs_fattr_मुक्त_owner_name(काष्ठा nfs_fattr *fattr)
अणु
	fattr->valid &= ~NFS_ATTR_FATTR_OWNER_NAME;
	kमुक्त(fattr->owner_name->data);
पूर्ण

अटल व्योम nfs_fattr_मुक्त_group_name(काष्ठा nfs_fattr *fattr)
अणु
	fattr->valid &= ~NFS_ATTR_FATTR_GROUP_NAME;
	kमुक्त(fattr->group_name->data);
पूर्ण

अटल bool nfs_fattr_map_owner_name(काष्ठा nfs_server *server, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs4_string *owner = fattr->owner_name;
	kuid_t uid;

	अगर (!(fattr->valid & NFS_ATTR_FATTR_OWNER_NAME))
		वापस false;
	अगर (nfs_map_name_to_uid(server, owner->data, owner->len, &uid) == 0) अणु
		fattr->uid = uid;
		fattr->valid |= NFS_ATTR_FATTR_OWNER;
	पूर्ण
	वापस true;
पूर्ण

अटल bool nfs_fattr_map_group_name(काष्ठा nfs_server *server, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs4_string *group = fattr->group_name;
	kgid_t gid;

	अगर (!(fattr->valid & NFS_ATTR_FATTR_GROUP_NAME))
		वापस false;
	अगर (nfs_map_group_to_gid(server, group->data, group->len, &gid) == 0) अणु
		fattr->gid = gid;
		fattr->valid |= NFS_ATTR_FATTR_GROUP;
	पूर्ण
	वापस true;
पूर्ण

/**
 * nfs_fattr_मुक्त_names - मुक्त up the NFSv4 owner and group strings
 * @fattr: a fully initialised nfs_fattr काष्ठाure
 */
व्योम nfs_fattr_मुक्त_names(काष्ठा nfs_fattr *fattr)
अणु
	अगर (fattr->valid & NFS_ATTR_FATTR_OWNER_NAME)
		nfs_fattr_मुक्त_owner_name(fattr);
	अगर (fattr->valid & NFS_ATTR_FATTR_GROUP_NAME)
		nfs_fattr_मुक्त_group_name(fattr);
पूर्ण

/**
 * nfs_fattr_map_and_मुक्त_names - map owner/group strings पूर्णांकo uid/gid and मुक्त
 * @server: poपूर्णांकer to the fileप्रणाली nfs_server काष्ठाure
 * @fattr: a fully initialised nfs_fattr काष्ठाure
 *
 * This helper maps the cached NFSv4 owner/group strings in fattr पूर्णांकo
 * their numeric uid/gid equivalents, and then मुक्तs the cached strings.
 */
व्योम nfs_fattr_map_and_मुक्त_names(काष्ठा nfs_server *server, काष्ठा nfs_fattr *fattr)
अणु
	अगर (nfs_fattr_map_owner_name(server, fattr))
		nfs_fattr_मुक्त_owner_name(fattr);
	अगर (nfs_fattr_map_group_name(server, fattr))
		nfs_fattr_मुक्त_group_name(fattr);
पूर्ण

पूर्णांक nfs_map_string_to_numeric(स्थिर अक्षर *name, माप_प्रकार namelen, __u32 *res)
अणु
	अचिन्हित दीर्घ val;
	अक्षर buf[16];

	अगर (स_प्रथम(name, '@', namelen) != शून्य || namelen >= माप(buf))
		वापस 0;
	स_नकल(buf, name, namelen);
	buf[namelen] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val) != 0)
		वापस 0;
	*res = val;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_map_string_to_numeric);

अटल पूर्णांक nfs_map_numeric_to_string(__u32 id, अक्षर *buf, माप_प्रकार buflen)
अणु
	वापस snम_लिखो(buf, buflen, "%u", id);
पूर्ण

अटल काष्ठा key_type key_type_id_resolver = अणु
	.name		= "id_resolver",
	.preparse	= user_preparse,
	.मुक्त_preparse	= user_मुक्त_preparse,
	.instantiate	= generic_key_instantiate,
	.revoke		= user_revoke,
	.destroy	= user_destroy,
	.describe	= user_describe,
	.पढ़ो		= user_पढ़ो,
पूर्ण;

पूर्णांक nfs_idmap_init(व्योम)
अणु
	काष्ठा cred *cred;
	काष्ठा key *keyring;
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_NOTICE "NFS: Registering the %s key type\n",
		key_type_id_resolver.name);

	cred = prepare_kernel_cred(शून्य);
	अगर (!cred)
		वापस -ENOMEM;

	keyring = keyring_alloc(".id_resolver",
				GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ failed_put_cred;
	पूर्ण

	ret = रेजिस्टर_key_type(&key_type_id_resolver);
	अगर (ret < 0)
		जाओ failed_put_key;

	ret = रेजिस्टर_key_type(&key_type_id_resolver_legacy);
	अगर (ret < 0)
		जाओ failed_reg_legacy;

	set_bit(KEY_FLAG_ROOT_CAN_CLEAR, &keyring->flags);
	cred->thपढ़ो_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	id_resolver_cache = cred;
	वापस 0;

failed_reg_legacy:
	unरेजिस्टर_key_type(&key_type_id_resolver);
failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	वापस ret;
पूर्ण

व्योम nfs_idmap_quit(व्योम)
अणु
	key_revoke(id_resolver_cache->thपढ़ो_keyring);
	unरेजिस्टर_key_type(&key_type_id_resolver);
	unरेजिस्टर_key_type(&key_type_id_resolver_legacy);
	put_cred(id_resolver_cache);
पूर्ण

/*
 * Assemble the description to pass to request_key()
 * This function will allocate a new string and update dest to poपूर्णांक
 * at it.  The caller is responsible क्रम मुक्तing dest.
 *
 * On error 0 is वापसed.  Otherwise, the length of dest is वापसed.
 */
अटल sमाप_प्रकार nfs_idmap_get_desc(स्थिर अक्षर *name, माप_प्रकार namelen,
				स्थिर अक्षर *type, माप_प्रकार typelen, अक्षर **desc)
अणु
	अक्षर *cp;
	माप_प्रकार desclen = typelen + namelen + 2;

	*desc = kदो_स्मृति(desclen, GFP_KERNEL);
	अगर (!*desc)
		वापस -ENOMEM;

	cp = *desc;
	स_नकल(cp, type, typelen);
	cp += typelen;
	*cp++ = ':';

	स_नकल(cp, name, namelen);
	cp += namelen;
	*cp = '\0';
	वापस desclen;
पूर्ण

अटल काष्ठा key *nfs_idmap_request_key(स्थिर अक्षर *name, माप_प्रकार namelen,
					 स्थिर अक्षर *type, काष्ठा idmap *idmap)
अणु
	अक्षर *desc;
	काष्ठा key *rkey = ERR_PTR(-EAGAIN);
	sमाप_प्रकार ret;

	ret = nfs_idmap_get_desc(name, namelen, type, म_माप(type), &desc);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (!idmap->user_ns || idmap->user_ns == &init_user_ns)
		rkey = request_key(&key_type_id_resolver, desc, "");
	अगर (IS_ERR(rkey)) अणु
		mutex_lock(&idmap->idmap_mutex);
		rkey = request_key_with_auxdata(&key_type_id_resolver_legacy,
						desc, शून्य, "", 0, idmap);
		mutex_unlock(&idmap->idmap_mutex);
	पूर्ण
	अगर (!IS_ERR(rkey))
		set_bit(KEY_FLAG_ROOT_CAN_INVAL, &rkey->flags);

	kमुक्त(desc);
	वापस rkey;
पूर्ण

अटल sमाप_प्रकार nfs_idmap_get_key(स्थिर अक्षर *name, माप_प्रकार namelen,
				 स्थिर अक्षर *type, व्योम *data,
				 माप_प्रकार data_size, काष्ठा idmap *idmap)
अणु
	स्थिर काष्ठा cred *saved_cred;
	काष्ठा key *rkey;
	स्थिर काष्ठा user_key_payload *payload;
	sमाप_प्रकार ret;

	saved_cred = override_creds(id_resolver_cache);
	rkey = nfs_idmap_request_key(name, namelen, type, idmap);
	revert_creds(saved_cred);

	अगर (IS_ERR(rkey)) अणु
		ret = PTR_ERR(rkey);
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	rkey->perm |= KEY_USR_VIEW;

	ret = key_validate(rkey);
	अगर (ret < 0)
		जाओ out_up;

	payload = user_key_payload_rcu(rkey);
	अगर (IS_ERR_OR_शून्य(payload)) अणु
		ret = PTR_ERR(payload);
		जाओ out_up;
	पूर्ण

	ret = payload->datalen;
	अगर (ret > 0 && ret <= data_size)
		स_नकल(data, payload->data, ret);
	अन्यथा
		ret = -EINVAL;

out_up:
	rcu_पढ़ो_unlock();
	key_put(rkey);
out:
	वापस ret;
पूर्ण

/* ID -> Name */
अटल sमाप_प्रकार nfs_idmap_lookup_name(__u32 id, स्थिर अक्षर *type, अक्षर *buf,
				     माप_प्रकार buflen, काष्ठा idmap *idmap)
अणु
	अक्षर id_str[NFS_अच_पूर्णांक_उच्चLEN];
	पूर्णांक id_len;
	sमाप_प्रकार ret;

	id_len = nfs_map_numeric_to_string(id, id_str, माप(id_str));
	ret = nfs_idmap_get_key(id_str, id_len, type, buf, buflen, idmap);
	अगर (ret < 0)
		वापस -EINVAL;
	वापस ret;
पूर्ण

/* Name -> ID */
अटल पूर्णांक nfs_idmap_lookup_id(स्थिर अक्षर *name, माप_प्रकार namelen, स्थिर अक्षर *type,
			       __u32 *id, काष्ठा idmap *idmap)
अणु
	अक्षर id_str[NFS_अच_पूर्णांक_उच्चLEN];
	दीर्घ id_दीर्घ;
	sमाप_प्रकार data_size;
	पूर्णांक ret = 0;

	data_size = nfs_idmap_get_key(name, namelen, type, id_str, NFS_अच_पूर्णांक_उच्चLEN, idmap);
	अगर (data_size <= 0) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = kम_से_दीर्घ(id_str, 10, &id_दीर्घ);
		अगर (!ret)
			*id = (__u32)id_दीर्घ;
	पूर्ण
	वापस ret;
पूर्ण

/* idmap classic begins here */

क्रमागत अणु
	Opt_find_uid, Opt_find_gid, Opt_find_user, Opt_find_group, Opt_find_err
पूर्ण;

अटल स्थिर match_table_t nfs_idmap_tokens = अणु
	अणु Opt_find_uid, "uid:%s" पूर्ण,
	अणु Opt_find_gid, "gid:%s" पूर्ण,
	अणु Opt_find_user, "user:%s" पूर्ण,
	अणु Opt_find_group, "group:%s" पूर्ण,
	अणु Opt_find_err, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक nfs_idmap_legacy_upcall(काष्ठा key *, व्योम *);
अटल sमाप_प्रकार idmap_pipe_करोwncall(काष्ठा file *, स्थिर अक्षर __user *,
				   माप_प्रकार);
अटल व्योम idmap_release_pipe(काष्ठा inode *);
अटल व्योम idmap_pipe_destroy_msg(काष्ठा rpc_pipe_msg *);

अटल स्थिर काष्ठा rpc_pipe_ops idmap_upcall_ops = अणु
	.upcall		= rpc_pipe_generic_upcall,
	.करोwncall	= idmap_pipe_करोwncall,
	.release_pipe	= idmap_release_pipe,
	.destroy_msg	= idmap_pipe_destroy_msg,
पूर्ण;

अटल काष्ठा key_type key_type_id_resolver_legacy = अणु
	.name		= "id_legacy",
	.preparse	= user_preparse,
	.मुक्त_preparse	= user_मुक्त_preparse,
	.instantiate	= generic_key_instantiate,
	.revoke		= user_revoke,
	.destroy	= user_destroy,
	.describe	= user_describe,
	.पढ़ो		= user_पढ़ो,
	.request_key	= nfs_idmap_legacy_upcall,
पूर्ण;

अटल व्योम nfs_idmap_pipe_destroy(काष्ठा dentry *dir,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	काष्ठा idmap *idmap = pकरो->pकरो_data;
	काष्ठा rpc_pipe *pipe = idmap->idmap_pipe;

	अगर (pipe->dentry) अणु
		rpc_unlink(pipe->dentry);
		pipe->dentry = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक nfs_idmap_pipe_create(काष्ठा dentry *dir,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	काष्ठा idmap *idmap = pकरो->pकरो_data;
	काष्ठा rpc_pipe *pipe = idmap->idmap_pipe;
	काष्ठा dentry *dentry;

	dentry = rpc_mkpipe_dentry(dir, "idmap", idmap, pipe);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	pipe->dentry = dentry;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rpc_pipe_dir_object_ops nfs_idmap_pipe_dir_object_ops = अणु
	.create = nfs_idmap_pipe_create,
	.destroy = nfs_idmap_pipe_destroy,
पूर्ण;

पूर्णांक
nfs_idmap_new(काष्ठा nfs_client *clp)
अणु
	काष्ठा idmap *idmap;
	काष्ठा rpc_pipe *pipe;
	पूर्णांक error;

	idmap = kzalloc(माप(*idmap), GFP_KERNEL);
	अगर (idmap == शून्य)
		वापस -ENOMEM;

	mutex_init(&idmap->idmap_mutex);
	idmap->user_ns = get_user_ns(clp->cl_rpcclient->cl_cred->user_ns);

	rpc_init_pipe_dir_object(&idmap->idmap_pकरो,
			&nfs_idmap_pipe_dir_object_ops,
			idmap);

	pipe = rpc_mkpipe_data(&idmap_upcall_ops, 0);
	अगर (IS_ERR(pipe)) अणु
		error = PTR_ERR(pipe);
		जाओ err;
	पूर्ण
	idmap->idmap_pipe = pipe;

	error = rpc_add_pipe_dir_object(clp->cl_net,
			&clp->cl_rpcclient->cl_pipedir_objects,
			&idmap->idmap_pकरो);
	अगर (error)
		जाओ err_destroy_pipe;

	clp->cl_idmap = idmap;
	वापस 0;
err_destroy_pipe:
	rpc_destroy_pipe_data(idmap->idmap_pipe);
err:
	get_user_ns(idmap->user_ns);
	kमुक्त(idmap);
	वापस error;
पूर्ण

व्योम
nfs_idmap_delete(काष्ठा nfs_client *clp)
अणु
	काष्ठा idmap *idmap = clp->cl_idmap;

	अगर (!idmap)
		वापस;
	clp->cl_idmap = शून्य;
	rpc_हटाओ_pipe_dir_object(clp->cl_net,
			&clp->cl_rpcclient->cl_pipedir_objects,
			&idmap->idmap_pकरो);
	rpc_destroy_pipe_data(idmap->idmap_pipe);
	put_user_ns(idmap->user_ns);
	kमुक्त(idmap);
पूर्ण

अटल पूर्णांक nfs_idmap_prepare_message(अक्षर *desc, काष्ठा idmap *idmap,
				     काष्ठा idmap_msg *im,
				     काष्ठा rpc_pipe_msg *msg)
अणु
	substring_t substr;
	पूर्णांक token, ret;

	im->im_type = IDMAP_TYPE_GROUP;
	token = match_token(desc, nfs_idmap_tokens, &substr);

	चयन (token) अणु
	हाल Opt_find_uid:
		im->im_type = IDMAP_TYPE_USER;
		fallthrough;
	हाल Opt_find_gid:
		im->im_conv = IDMAP_CONV_NAMETOID;
		ret = match_strlcpy(im->im_name, &substr, IDMAP_NAMESZ);
		अवरोध;

	हाल Opt_find_user:
		im->im_type = IDMAP_TYPE_USER;
		fallthrough;
	हाल Opt_find_group:
		im->im_conv = IDMAP_CONV_IDTONAME;
		ret = match_पूर्णांक(&substr, &im->im_id);
		अगर (ret)
			जाओ out;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	msg->data = im;
	msg->len  = माप(काष्ठा idmap_msg);

out:
	वापस ret;
पूर्ण

अटल bool
nfs_idmap_prepare_pipe_upcall(काष्ठा idmap *idmap,
		काष्ठा idmap_legacy_upcalldata *data)
अणु
	अगर (idmap->idmap_upcall_data != शून्य) अणु
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण
	idmap->idmap_upcall_data = data;
	वापस true;
पूर्ण

अटल व्योम
nfs_idmap_complete_pipe_upcall_locked(काष्ठा idmap *idmap, पूर्णांक ret)
अणु
	काष्ठा key *authkey = idmap->idmap_upcall_data->authkey;

	kमुक्त(idmap->idmap_upcall_data);
	idmap->idmap_upcall_data = शून्य;
	complete_request_key(authkey, ret);
	key_put(authkey);
पूर्ण

अटल व्योम
nfs_idmap_पात_pipe_upcall(काष्ठा idmap *idmap, पूर्णांक ret)
अणु
	अगर (idmap->idmap_upcall_data != शून्य)
		nfs_idmap_complete_pipe_upcall_locked(idmap, ret);
पूर्ण

अटल पूर्णांक nfs_idmap_legacy_upcall(काष्ठा key *authkey, व्योम *aux)
अणु
	काष्ठा idmap_legacy_upcalldata *data;
	काष्ठा request_key_auth *rka = get_request_key_auth(authkey);
	काष्ठा rpc_pipe_msg *msg;
	काष्ठा idmap_msg *im;
	काष्ठा idmap *idmap = (काष्ठा idmap *)aux;
	काष्ठा key *key = rka->target_key;
	पूर्णांक ret = -ENOKEY;

	अगर (!aux)
		जाओ out1;

	/* msg and im are मुक्तd in idmap_pipe_destroy_msg */
	ret = -ENOMEM;
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ out1;

	msg = &data->pipe_msg;
	im = &data->idmap_msg;
	data->idmap = idmap;
	data->authkey = key_get(authkey);

	ret = nfs_idmap_prepare_message(key->description, idmap, im, msg);
	अगर (ret < 0)
		जाओ out2;

	ret = -EAGAIN;
	अगर (!nfs_idmap_prepare_pipe_upcall(idmap, data))
		जाओ out2;

	ret = rpc_queue_upcall(idmap->idmap_pipe, msg);
	अगर (ret < 0)
		nfs_idmap_पात_pipe_upcall(idmap, ret);

	वापस ret;
out2:
	kमुक्त(data);
out1:
	complete_request_key(authkey, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_idmap_instantiate(काष्ठा key *key, काष्ठा key *authkey, अक्षर *data, माप_प्रकार datalen)
अणु
	वापस key_instantiate_and_link(key, data, datalen,
					id_resolver_cache->thपढ़ो_keyring,
					authkey);
पूर्ण

अटल पूर्णांक nfs_idmap_पढ़ो_and_verअगरy_message(काष्ठा idmap_msg *im,
		काष्ठा idmap_msg *upcall,
		काष्ठा key *key, काष्ठा key *authkey)
अणु
	अक्षर id_str[NFS_अच_पूर्णांक_उच्चLEN];
	माप_प्रकार len;
	पूर्णांक ret = -ENOKEY;

	/* ret = -ENOKEY */
	अगर (upcall->im_type != im->im_type || upcall->im_conv != im->im_conv)
		जाओ out;
	चयन (im->im_conv) अणु
	हाल IDMAP_CONV_NAMETOID:
		अगर (म_भेद(upcall->im_name, im->im_name) != 0)
			अवरोध;
		/* Note: here we store the NUL terminator too */
		len = 1 + nfs_map_numeric_to_string(im->im_id, id_str,
						    माप(id_str));
		ret = nfs_idmap_instantiate(key, authkey, id_str, len);
		अवरोध;
	हाल IDMAP_CONV_IDTONAME:
		अगर (upcall->im_id != im->im_id)
			अवरोध;
		len = म_माप(im->im_name);
		ret = nfs_idmap_instantiate(key, authkey, im->im_name, len);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
idmap_pipe_करोwncall(काष्ठा file *filp, स्थिर अक्षर __user *src, माप_प्रकार mlen)
अणु
	काष्ठा request_key_auth *rka;
	काष्ठा rpc_inode *rpci = RPC_I(file_inode(filp));
	काष्ठा idmap *idmap = (काष्ठा idmap *)rpci->निजी;
	काष्ठा key *authkey;
	काष्ठा idmap_msg im;
	माप_प्रकार namelen_in;
	पूर्णांक ret = -ENOKEY;

	/* If instantiation is successful, anyone रुकोing क्रम key स्थिरruction
	 * will have been woken up and someone अन्यथा may now have used
	 * idmap_key_cons - so after this poपूर्णांक we may no दीर्घer touch it.
	 */
	अगर (idmap->idmap_upcall_data == शून्य)
		जाओ out_noupcall;

	authkey = idmap->idmap_upcall_data->authkey;
	rka = get_request_key_auth(authkey);

	अगर (mlen != माप(im)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(&im, src, mlen) != 0) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!(im.im_status & IDMAP_STATUS_SUCCESS)) अणु
		ret = -ENOKEY;
		जाओ out;
	पूर्ण

	namelen_in = strnlen(im.im_name, IDMAP_NAMESZ);
	अगर (namelen_in == 0 || namelen_in == IDMAP_NAMESZ) अणु
		ret = -EINVAL;
		जाओ out;
पूर्ण

	ret = nfs_idmap_पढ़ो_and_verअगरy_message(&im,
			&idmap->idmap_upcall_data->idmap_msg,
			rka->target_key, authkey);
	अगर (ret >= 0) अणु
		key_set_समयout(rka->target_key, nfs_idmap_cache_समयout);
		ret = mlen;
	पूर्ण

out:
	nfs_idmap_complete_pipe_upcall_locked(idmap, ret);
out_noupcall:
	वापस ret;
पूर्ण

अटल व्योम
idmap_pipe_destroy_msg(काष्ठा rpc_pipe_msg *msg)
अणु
	काष्ठा idmap_legacy_upcalldata *data = container_of(msg,
			काष्ठा idmap_legacy_upcalldata,
			pipe_msg);
	काष्ठा idmap *idmap = data->idmap;

	अगर (msg->त्रुटि_सं)
		nfs_idmap_पात_pipe_upcall(idmap, msg->त्रुटि_सं);
पूर्ण

अटल व्योम
idmap_release_pipe(काष्ठा inode *inode)
अणु
	काष्ठा rpc_inode *rpci = RPC_I(inode);
	काष्ठा idmap *idmap = (काष्ठा idmap *)rpci->निजी;

	nfs_idmap_पात_pipe_upcall(idmap, -EPIPE);
पूर्ण

पूर्णांक nfs_map_name_to_uid(स्थिर काष्ठा nfs_server *server, स्थिर अक्षर *name, माप_प्रकार namelen, kuid_t *uid)
अणु
	काष्ठा idmap *idmap = server->nfs_client->cl_idmap;
	__u32 id = -1;
	पूर्णांक ret = 0;

	अगर (!nfs_map_string_to_numeric(name, namelen, &id))
		ret = nfs_idmap_lookup_id(name, namelen, "uid", &id, idmap);
	अगर (ret == 0) अणु
		*uid = make_kuid(idmap_userns(idmap), id);
		अगर (!uid_valid(*uid))
			ret = -दुस्फल;
	पूर्ण
	trace_nfs4_map_name_to_uid(name, namelen, id, ret);
	वापस ret;
पूर्ण

पूर्णांक nfs_map_group_to_gid(स्थिर काष्ठा nfs_server *server, स्थिर अक्षर *name, माप_प्रकार namelen, kgid_t *gid)
अणु
	काष्ठा idmap *idmap = server->nfs_client->cl_idmap;
	__u32 id = -1;
	पूर्णांक ret = 0;

	अगर (!nfs_map_string_to_numeric(name, namelen, &id))
		ret = nfs_idmap_lookup_id(name, namelen, "gid", &id, idmap);
	अगर (ret == 0) अणु
		*gid = make_kgid(idmap_userns(idmap), id);
		अगर (!gid_valid(*gid))
			ret = -दुस्फल;
	पूर्ण
	trace_nfs4_map_group_to_gid(name, namelen, id, ret);
	वापस ret;
पूर्ण

पूर्णांक nfs_map_uid_to_name(स्थिर काष्ठा nfs_server *server, kuid_t uid, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा idmap *idmap = server->nfs_client->cl_idmap;
	पूर्णांक ret = -EINVAL;
	__u32 id;

	id = from_kuid_munged(idmap_userns(idmap), uid);
	अगर (!(server->caps & NFS_CAP_UIDGID_NOMAP))
		ret = nfs_idmap_lookup_name(id, "user", buf, buflen, idmap);
	अगर (ret < 0)
		ret = nfs_map_numeric_to_string(id, buf, buflen);
	trace_nfs4_map_uid_to_name(buf, ret, id, ret);
	वापस ret;
पूर्ण
पूर्णांक nfs_map_gid_to_group(स्थिर काष्ठा nfs_server *server, kgid_t gid, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा idmap *idmap = server->nfs_client->cl_idmap;
	पूर्णांक ret = -EINVAL;
	__u32 id;

	id = from_kgid_munged(idmap_userns(idmap), gid);
	अगर (!(server->caps & NFS_CAP_UIDGID_NOMAP))
		ret = nfs_idmap_lookup_name(id, "group", buf, buflen, idmap);
	अगर (ret < 0)
		ret = nfs_map_numeric_to_string(id, buf, buflen);
	trace_nfs4_map_gid_to_group(buf, ret, id, ret);
	वापस ret;
पूर्ण
