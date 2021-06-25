<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/nfsacl.h>

#समावेश "internal.h"
#समावेश "nfs3_fs.h"

#घोषणा NFSDBG_FACILITY	NFSDBG_PROC

/*
 * nfs3_prepare_get_acl, nfs3_complete_get_acl, nfs3_पात_get_acl: Helpers क्रम
 * caching get_acl results in a race-मुक्त way.  See fs/posix_acl.c:get_acl()
 * क्रम explanations.
 */
अटल व्योम nfs3_prepare_get_acl(काष्ठा posix_acl **p)
अणु
	काष्ठा posix_acl *sentinel = uncached_acl_sentinel(current);

	अगर (cmpxchg(p, ACL_NOT_CACHED, sentinel) != ACL_NOT_CACHED) अणु
		/* Not the first पढ़ोer or sentinel alपढ़ोy in place. */
	पूर्ण
पूर्ण

अटल व्योम nfs3_complete_get_acl(काष्ठा posix_acl **p, काष्ठा posix_acl *acl)
अणु
	काष्ठा posix_acl *sentinel = uncached_acl_sentinel(current);

	/* Only cache the ACL अगर our sentinel is still in place. */
	posix_acl_dup(acl);
	अगर (cmpxchg(p, sentinel, acl) != sentinel)
		posix_acl_release(acl);
पूर्ण

अटल व्योम nfs3_पात_get_acl(काष्ठा posix_acl **p)
अणु
	काष्ठा posix_acl *sentinel = uncached_acl_sentinel(current);

	/* Remove our sentinel upon failure. */
	cmpxchg(p, sentinel, ACL_NOT_CACHED);
पूर्ण

काष्ठा posix_acl *nfs3_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा page *pages[NFSACL_MAXPAGES] = अणु पूर्ण;
	काष्ठा nfs3_getaclargs args = अणु
		.fh = NFS_FH(inode),
		/* The xdr layer may allocate pages here. */
		.pages = pages,
	पूर्ण;
	काष्ठा nfs3_getaclres res = अणु
		शून्य,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &args,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक status, count;

	अगर (!nfs_server_capable(inode, NFS_CAP_ACLS))
		वापस ERR_PTR(-EOPNOTSUPP);

	status = nfs_revalidate_inode(inode, NFS_INO_INVALID_CHANGE);
	अगर (status < 0)
		वापस ERR_PTR(status);

	/*
	 * Only get the access acl when explicitly requested: We करोn't
	 * need it क्रम access decisions, and only some applications use
	 * it. Applications which request the access acl first are not
	 * penalized from this optimization.
	 */
	अगर (type == ACL_TYPE_ACCESS)
		args.mask |= NFS_ACLCNT|NFS_ACL;
	अगर (S_ISसूची(inode->i_mode))
		args.mask |= NFS_DFACLCNT|NFS_DFACL;
	अगर (args.mask == 0)
		वापस शून्य;

	dprपूर्णांकk("NFS call getacl\n");
	msg.rpc_proc = &server->client_acl->cl_procinfo[ACLPROC3_GETACL];
	res.fattr = nfs_alloc_fattr();
	अगर (res.fattr == शून्य)
		वापस ERR_PTR(-ENOMEM);

	अगर (args.mask & NFS_ACL)
		nfs3_prepare_get_acl(&inode->i_acl);
	अगर (args.mask & NFS_DFACL)
		nfs3_prepare_get_acl(&inode->i_शेष_acl);

	status = rpc_call_sync(server->client_acl, &msg, 0);
	dprपूर्णांकk("NFS reply getacl: %d\n", status);

	/* pages may have been allocated at the xdr layer. */
	क्रम (count = 0; count < NFSACL_MAXPAGES && args.pages[count]; count++)
		__मुक्त_page(args.pages[count]);

	चयन (status) अणु
		हाल 0:
			status = nfs_refresh_inode(inode, res.fattr);
			अवरोध;
		हाल -EPFNOSUPPORT:
		हाल -EPROTONOSUPPORT:
			dprपूर्णांकk("NFS_V3_ACL extension not supported; disabling\n");
			server->caps &= ~NFS_CAP_ACLS;
			fallthrough;
		हाल -ENOTSUPP:
			status = -EOPNOTSUPP;
			जाओ getout;
		शेष:
			जाओ getout;
	पूर्ण
	अगर ((args.mask & res.mask) != args.mask) अणु
		status = -EIO;
		जाओ getout;
	पूर्ण

	अगर (res.acl_access != शून्य) अणु
		अगर ((posix_acl_equiv_mode(res.acl_access, शून्य) == 0) ||
		    res.acl_access->a_count == 0) अणु
			posix_acl_release(res.acl_access);
			res.acl_access = शून्य;
		पूर्ण
	पूर्ण

	अगर (res.mask & NFS_ACL)
		nfs3_complete_get_acl(&inode->i_acl, res.acl_access);
	अन्यथा
		क्रमget_cached_acl(inode, ACL_TYPE_ACCESS);

	अगर (res.mask & NFS_DFACL)
		nfs3_complete_get_acl(&inode->i_शेष_acl, res.acl_शेष);
	अन्यथा
		क्रमget_cached_acl(inode, ACL_TYPE_DEFAULT);

	nfs_मुक्त_fattr(res.fattr);
	अगर (type == ACL_TYPE_ACCESS) अणु
		posix_acl_release(res.acl_शेष);
		वापस res.acl_access;
	पूर्ण अन्यथा अणु
		posix_acl_release(res.acl_access);
		वापस res.acl_शेष;
	पूर्ण

getout:
	nfs3_पात_get_acl(&inode->i_acl);
	nfs3_पात_get_acl(&inode->i_शेष_acl);
	posix_acl_release(res.acl_access);
	posix_acl_release(res.acl_शेष);
	nfs_मुक्त_fattr(res.fattr);
	वापस ERR_PTR(status);
पूर्ण

अटल पूर्णांक __nfs3_proc_setacls(काष्ठा inode *inode, काष्ठा posix_acl *acl,
		काष्ठा posix_acl *dfacl)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_fattr *fattr;
	काष्ठा page *pages[NFSACL_MAXPAGES];
	काष्ठा nfs3_setaclargs args = अणु
		.inode = inode,
		.mask = NFS_ACL,
		.acl_access = acl,
		.pages = pages,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &args,
		.rpc_resp	= &fattr,
	पूर्ण;
	पूर्णांक status = 0;

	अगर (acl == शून्य && (!S_ISसूची(inode->i_mode) || dfacl == शून्य))
		जाओ out;

	status = -EOPNOTSUPP;
	अगर (!nfs_server_capable(inode, NFS_CAP_ACLS))
		जाओ out;

	/* We are करोing this here because XDR marshalling करोes not
	 * वापस any results, it BUGs. */
	status = -ENOSPC;
	अगर (acl != शून्य && acl->a_count > NFS_ACL_MAX_ENTRIES)
		जाओ out;
	अगर (dfacl != शून्य && dfacl->a_count > NFS_ACL_MAX_ENTRIES)
		जाओ out;
	अगर (S_ISसूची(inode->i_mode)) अणु
		args.mask |= NFS_DFACL;
		args.acl_शेष = dfacl;
		args.len = nfsacl_size(acl, dfacl);
	पूर्ण अन्यथा
		args.len = nfsacl_size(acl, शून्य);

	अगर (args.len > NFS_ACL_INLINE_बफ_मानE) अणु
		अचिन्हित पूर्णांक npages = 1 + ((args.len - 1) >> PAGE_SHIFT);

		status = -ENOMEM;
		करो अणु
			args.pages[args.npages] = alloc_page(GFP_KERNEL);
			अगर (args.pages[args.npages] == शून्य)
				जाओ out_मुक्तpages;
			args.npages++;
		पूर्ण जबतक (args.npages < npages);
	पूर्ण

	dprपूर्णांकk("NFS call setacl\n");
	status = -ENOMEM;
	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		जाओ out_मुक्तpages;

	msg.rpc_proc = &server->client_acl->cl_procinfo[ACLPROC3_SETACL];
	msg.rpc_resp = fattr;
	status = rpc_call_sync(server->client_acl, &msg, 0);
	nfs_access_zap_cache(inode);
	nfs_zap_acl_cache(inode);
	dprपूर्णांकk("NFS reply setacl: %d\n", status);

	चयन (status) अणु
		हाल 0:
			status = nfs_refresh_inode(inode, fattr);
			अवरोध;
		हाल -EPFNOSUPPORT:
		हाल -EPROTONOSUPPORT:
			dprपूर्णांकk("NFS_V3_ACL SETACL RPC not supported"
					"(will not retry)\n");
			server->caps &= ~NFS_CAP_ACLS;
			fallthrough;
		हाल -ENOTSUPP:
			status = -EOPNOTSUPP;
	पूर्ण
	nfs_मुक्त_fattr(fattr);
out_मुक्तpages:
	जबतक (args.npages != 0) अणु
		args.npages--;
		__मुक्त_page(args.pages[args.npages]);
	पूर्ण
out:
	वापस status;
पूर्ण

पूर्णांक nfs3_proc_setacls(काष्ठा inode *inode, काष्ठा posix_acl *acl,
		काष्ठा posix_acl *dfacl)
अणु
	पूर्णांक ret;
	ret = __nfs3_proc_setacls(inode, acl, dfacl);
	वापस (ret == -EOPNOTSUPP) ? 0 : ret;

पूर्ण

पूर्णांक nfs3_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	काष्ठा posix_acl *orig = acl, *dfacl = शून्य, *alloc;
	पूर्णांक status;

	अगर (S_ISसूची(inode->i_mode)) अणु
		चयन(type) अणु
		हाल ACL_TYPE_ACCESS:
			alloc = get_acl(inode, ACL_TYPE_DEFAULT);
			अगर (IS_ERR(alloc))
				जाओ fail;
			dfacl = alloc;
			अवरोध;

		हाल ACL_TYPE_DEFAULT:
			alloc = get_acl(inode, ACL_TYPE_ACCESS);
			अगर (IS_ERR(alloc))
				जाओ fail;
			dfacl = acl;
			acl = alloc;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (acl == शून्य) अणु
		alloc = posix_acl_from_mode(inode->i_mode, GFP_KERNEL);
		अगर (IS_ERR(alloc))
			जाओ fail;
		acl = alloc;
	पूर्ण
	status = __nfs3_proc_setacls(inode, acl, dfacl);
out:
	अगर (acl != orig)
		posix_acl_release(acl);
	अगर (dfacl != orig)
		posix_acl_release(dfacl);
	वापस status;

fail:
	status = PTR_ERR(alloc);
	जाओ out;
पूर्ण

स्थिर काष्ठा xattr_handler *nfs3_xattr_handlers[] = अणु
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
	शून्य,
पूर्ण;

अटल पूर्णांक
nfs3_list_one_acl(काष्ठा inode *inode, पूर्णांक type, स्थिर अक्षर *name, व्योम *data,
		माप_प्रकार size, sमाप_प्रकार *result)
अणु
	काष्ठा posix_acl *acl;
	अक्षर *p = data + *result;

	acl = get_acl(inode, type);
	अगर (IS_ERR_OR_शून्य(acl))
		वापस 0;

	posix_acl_release(acl);

	*result += म_माप(name);
	*result += 1;
	अगर (!size)
		वापस 0;
	अगर (*result > size)
		वापस -दुस्फल;

	म_नकल(p, name);
	वापस 0;
पूर्ण

sमाप_प्रकार
nfs3_listxattr(काष्ठा dentry *dentry, अक्षर *data, माप_प्रकार size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	sमाप_प्रकार result = 0;
	पूर्णांक error;

	error = nfs3_list_one_acl(inode, ACL_TYPE_ACCESS,
			XATTR_NAME_POSIX_ACL_ACCESS, data, size, &result);
	अगर (error)
		वापस error;

	error = nfs3_list_one_acl(inode, ACL_TYPE_DEFAULT,
			XATTR_NAME_POSIX_ACL_DEFAULT, data, size, &result);
	अगर (error)
		वापस error;
	वापस result;
पूर्ण
