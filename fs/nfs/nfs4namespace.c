<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/nfs4namespace.c
 *
 * Copyright (C) 2005 Trond Myklebust <Trond.Myklebust@netapp.com>
 * - Modअगरied by David Howells <dhowells@redhat.com>
 *
 * NFSv4 namespace
 */

#समावेश <linux/module.h>
#समावेश <linux/dcache.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/vfs.h>
#समावेश <linux/inet.h>
#समावेश "internal.h"
#समावेश "nfs4_fs.h"
#समावेश "nfs.h"
#समावेश "dns_resolve.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

/*
 * Work out the length that an NFSv4 path would render to as a standard posix
 * path, with a leading slash but no terminating slash.
 */
अटल sमाप_प्रकार nfs4_pathname_len(स्थिर काष्ठा nfs4_pathname *pathname)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < pathname->ncomponents; i++) अणु
		स्थिर काष्ठा nfs4_string *component = &pathname->components[i];

		अगर (component->len > NAME_MAX)
			जाओ too_दीर्घ;
		len += 1 + component->len; /* Adding "/foo" */
		अगर (len > PATH_MAX)
			जाओ too_दीर्घ;
	पूर्ण
	वापस len;

too_दीर्घ:
	वापस -ENAMETOOLONG;
पूर्ण

/*
 * Convert the NFSv4 pathname components पूर्णांकo a standard posix path.
 */
अटल अक्षर *nfs4_pathname_string(स्थिर काष्ठा nfs4_pathname *pathname,
				  अचिन्हित लघु *_len)
अणु
	sमाप_प्रकार len;
	अक्षर *buf, *p;
	पूर्णांक i;

	len = nfs4_pathname_len(pathname);
	अगर (len < 0)
		वापस ERR_PTR(len);
	*_len = len;

	p = buf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < pathname->ncomponents; i++) अणु
		स्थिर काष्ठा nfs4_string *component = &pathname->components[i];

		*p++ = '/';
		स_नकल(p, component->data, component->len);
		p += component->len;
	पूर्ण

	*p = 0;
	वापस buf;
पूर्ण

/*
 * वापस the path component of "<server>:<path>"
 *  nfspath - the "<server>:<path>" string
 *  end - one past the last अक्षर that could contain "<server>:"
 * वापसs शून्य on failure
 */
अटल अक्षर *nfs_path_component(स्थिर अक्षर *nfspath, स्थिर अक्षर *end)
अणु
	अक्षर *p;

	अगर (*nfspath == '[') अणु
		/* parse [] escaped IPv6 addrs */
		p = म_अक्षर(nfspath, ']');
		अगर (p != शून्य && ++p < end && *p == ':')
			वापस p + 1;
	पूर्ण अन्यथा अणु
		/* otherwise split on first colon */
		p = म_अक्षर(nfspath, ':');
		अगर (p != शून्य && p < end)
			वापस p + 1;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Determine the mount path as a string
 */
अटल अक्षर *nfs4_path(काष्ठा dentry *dentry, अक्षर *buffer, sमाप_प्रकार buflen)
अणु
	अक्षर *limit;
	अक्षर *path = nfs_path(&limit, dentry, buffer, buflen,
			      NFS_PATH_CANONICAL);
	अगर (!IS_ERR(path)) अणु
		अक्षर *path_component = nfs_path_component(path, limit);
		अगर (path_component)
			वापस path_component;
	पूर्ण
	वापस path;
पूर्ण

/*
 * Check that fs_locations::fs_root [RFC3530 6.3] is a prefix क्रम what we
 * believe to be the server path to this dentry
 */
अटल पूर्णांक nfs4_validate_fspath(काष्ठा dentry *dentry,
				स्थिर काष्ठा nfs4_fs_locations *locations,
				काष्ठा nfs_fs_context *ctx)
अणु
	स्थिर अक्षर *path;
	अक्षर *fs_path;
	अचिन्हित लघु len;
	अक्षर *buf;
	पूर्णांक n;

	buf = kदो_स्मृति(4096, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	path = nfs4_path(dentry, buf, 4096);
	अगर (IS_ERR(path)) अणु
		kमुक्त(buf);
		वापस PTR_ERR(path);
	पूर्ण

	fs_path = nfs4_pathname_string(&locations->fs_path, &len);
	अगर (IS_ERR(fs_path)) अणु
		kमुक्त(buf);
		वापस PTR_ERR(fs_path);
	पूर्ण

	n = म_भेदन(path, fs_path, len);
	kमुक्त(buf);
	kमुक्त(fs_path);
	अगर (n != 0) अणु
		dprपूर्णांकk("%s: path %s does not begin with fsroot %s\n",
			__func__, path, ctx->nfs_server.export_path);
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार nfs_parse_server_name(अक्षर *string, माप_प्रकार len,
		काष्ठा sockaddr *sa, माप_प्रकार salen, काष्ठा net *net)
अणु
	sमाप_प्रकार ret;

	ret = rpc_pton(net, string, len, sa, salen);
	अगर (ret == 0) अणु
		ret = nfs_dns_resolve_name(net, string, len, sa, salen);
		अगर (ret < 0)
			ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nfs_find_best_sec - Find a security mechanism supported locally
 * @clnt: poपूर्णांकer to rpc_clnt
 * @server: NFS server काष्ठा
 * @flavors: List of security tuples वापसed by SECINFO procedure
 *
 * Return an rpc client that uses the first security mechanism in
 * "flavors" that is locally supported.  The "flavors" array
 * is searched in the order वापसed from the server, per RFC 3530
 * recommendation and each flavor is checked क्रम membership in the
 * sec= mount option list अगर it exists.
 *
 * Return -EPERM अगर no matching flavor is found in the array.
 *
 * Please call rpc_shutकरोwn_client() when you are करोne with this rpc client.
 *
 */
अटल काष्ठा rpc_clnt *nfs_find_best_sec(काष्ठा rpc_clnt *clnt,
					  काष्ठा nfs_server *server,
					  काष्ठा nfs4_secinfo_flavors *flavors)
अणु
	rpc_authflavor_t pflavor;
	काष्ठा nfs4_secinfo4 *secinfo;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < flavors->num_flavors; i++) अणु
		secinfo = &flavors->flavors[i];

		चयन (secinfo->flavor) अणु
		हाल RPC_AUTH_शून्य:
		हाल RPC_AUTH_UNIX:
		हाल RPC_AUTH_GSS:
			pflavor = rpcauth_get_pseuकरोflavor(secinfo->flavor,
							&secinfo->flavor_info);
			/* करोes the pseuकरोflavor match a sec= mount opt? */
			अगर (pflavor != RPC_AUTH_MAXFLAVOR &&
			    nfs_auth_info_match(&server->auth_info, pflavor)) अणु
				काष्ठा rpc_clnt *new;
				काष्ठा rpc_cred *cred;

				/* Cloning creates an rpc_auth क्रम the flavor */
				new = rpc_clone_client_set_auth(clnt, pflavor);
				अगर (IS_ERR(new))
					जारी;
				/**
				* Check that the user actually can use the
				* flavor. This is mostly क्रम RPC_AUTH_GSS
				* where cr_init obtains a gss context
				*/
				cred = rpcauth_lookupcred(new->cl_auth, 0);
				अगर (IS_ERR(cred)) अणु
					rpc_shutकरोwn_client(new);
					जारी;
				पूर्ण
				put_rpccred(cred);
				वापस new;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ERR_PTR(-EPERM);
पूर्ण

/**
 * nfs4_negotiate_security - in response to an NFS4ERR_WRONGSEC on lookup,
 * वापस an rpc_clnt that uses the best available security flavor with
 * respect to the secinfo flavor list and the sec= mount options.
 *
 * @clnt: RPC client to clone
 * @inode: directory inode
 * @name: lookup name
 *
 * Please call rpc_shutकरोwn_client() when you are करोne with this rpc client.
 */
काष्ठा rpc_clnt *
nfs4_negotiate_security(काष्ठा rpc_clnt *clnt, काष्ठा inode *inode,
					स्थिर काष्ठा qstr *name)
अणु
	काष्ठा page *page;
	काष्ठा nfs4_secinfo_flavors *flavors;
	काष्ठा rpc_clnt *new;
	पूर्णांक err;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	flavors = page_address(page);

	err = nfs4_proc_secinfo(inode, name, flavors);
	अगर (err < 0) अणु
		new = ERR_PTR(err);
		जाओ out;
	पूर्ण

	new = nfs_find_best_sec(clnt, NFS_SERVER(inode), flavors);

out:
	put_page(page);
	वापस new;
पूर्ण

अटल पूर्णांक try_location(काष्ठा fs_context *fc,
			स्थिर काष्ठा nfs4_fs_location *location)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	अचिन्हित पूर्णांक len, s;
	अक्षर *export_path, *source, *p;
	पूर्णांक ret = -ENOENT;

	/* Allocate a buffer big enough to hold any of the hostnames plus a
	 * terminating अक्षर and also a buffer big enough to hold the hostname
	 * plus a colon plus the path.
	 */
	len = 0;
	क्रम (s = 0; s < location->nservers; s++) अणु
		स्थिर काष्ठा nfs4_string *buf = &location->servers[s];
		अगर (buf->len > len)
			len = buf->len;
	पूर्ण

	kमुक्त(ctx->nfs_server.hostname);
	ctx->nfs_server.hostname = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!ctx->nfs_server.hostname)
		वापस -ENOMEM;

	export_path = nfs4_pathname_string(&location->rootpath,
					   &ctx->nfs_server.export_path_len);
	अगर (IS_ERR(export_path))
		वापस PTR_ERR(export_path);

	kमुक्त(ctx->nfs_server.export_path);
	ctx->nfs_server.export_path = export_path;

	source = kदो_स्मृति(len + 1 + ctx->nfs_server.export_path_len + 1,
			 GFP_KERNEL);
	अगर (!source)
		वापस -ENOMEM;

	kमुक्त(fc->source);
	fc->source = source;
	क्रम (s = 0; s < location->nservers; s++) अणु
		स्थिर काष्ठा nfs4_string *buf = &location->servers[s];

		अगर (स_प्रथम(buf->data, IPV6_SCOPE_DELIMITER, buf->len))
			जारी;

		ctx->nfs_server.addrlen =
			nfs_parse_server_name(buf->data, buf->len,
					      &ctx->nfs_server.address,
					      माप(ctx->nfs_server._address),
					      fc->net_ns);
		अगर (ctx->nfs_server.addrlen == 0)
			जारी;

		rpc_set_port(&ctx->nfs_server.address, NFS_PORT);

		स_नकल(ctx->nfs_server.hostname, buf->data, buf->len);
		ctx->nfs_server.hostname[buf->len] = '\0';

		p = source;
		स_नकल(p, buf->data, buf->len);
		p += buf->len;
		*p++ = ':';
		स_नकल(p, ctx->nfs_server.export_path, ctx->nfs_server.export_path_len);
		p += ctx->nfs_server.export_path_len;
		*p = 0;

		ret = nfs4_get_referral_tree(fc);
		अगर (ret == 0)
			वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nfs_follow_referral - set up mountpoपूर्णांक when hitting a referral on moved error
 * @fc: poपूर्णांकer to काष्ठा nfs_fs_context
 * @locations: array of NFSv4 server location inक्रमmation
 *
 */
अटल पूर्णांक nfs_follow_referral(काष्ठा fs_context *fc,
			       स्थिर काष्ठा nfs4_fs_locations *locations)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	पूर्णांक loc, error;

	अगर (locations == शून्य || locations->nlocations <= 0)
		वापस -ENOENT;

	dprपूर्णांकk("%s: referral at %pd2\n", __func__, ctx->clone_data.dentry);

	/* Ensure fs path is a prefix of current dentry path */
	error = nfs4_validate_fspath(ctx->clone_data.dentry, locations, ctx);
	अगर (error < 0)
		वापस error;

	error = -ENOENT;
	क्रम (loc = 0; loc < locations->nlocations; loc++) अणु
		स्थिर काष्ठा nfs4_fs_location *location = &locations->locations[loc];

		अगर (location == शून्य || location->nservers <= 0 ||
		    location->rootpath.ncomponents == 0)
			जारी;

		error = try_location(fc, location);
		अगर (error == 0)
			वापस 0;
	पूर्ण

	वापस error;
पूर्ण

/*
 * nfs_करो_refmount - handle crossing a referral on server
 * @dentry - dentry of referral
 *
 */
अटल पूर्णांक nfs_करो_refmount(काष्ठा fs_context *fc, काष्ठा rpc_clnt *client)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा dentry *dentry, *parent;
	काष्ठा nfs4_fs_locations *fs_locations = शून्य;
	काष्ठा page *page;
	पूर्णांक err = -ENOMEM;

	/* BUG_ON(IS_ROOT(dentry)); */
	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	fs_locations = kदो_स्मृति(माप(काष्ठा nfs4_fs_locations), GFP_KERNEL);
	अगर (!fs_locations)
		जाओ out_मुक्त;

	/* Get locations */
	dentry = ctx->clone_data.dentry;
	parent = dget_parent(dentry);
	dprपूर्णांकk("%s: getting locations for %pd2\n",
		__func__, dentry);

	err = nfs4_proc_fs_locations(client, d_inode(parent), &dentry->d_name, fs_locations, page);
	dput(parent);
	अगर (err != 0)
		जाओ out_मुक्त_2;

	err = -ENOENT;
	अगर (fs_locations->nlocations <= 0 ||
	    fs_locations->fs_path.ncomponents <= 0)
		जाओ out_मुक्त_2;

	err = nfs_follow_referral(fc, fs_locations);
out_मुक्त_2:
	kमुक्त(fs_locations);
out_मुक्त:
	__मुक्त_page(page);
	वापस err;
पूर्ण

पूर्णांक nfs4_submount(काष्ठा fs_context *fc, काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा dentry *dentry = ctx->clone_data.dentry;
	काष्ठा dentry *parent = dget_parent(dentry);
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा rpc_clnt *client;
	पूर्णांक ret;

	/* Look it up again to get its attributes and sec flavor */
	client = nfs4_proc_lookup_mountpoपूर्णांक(dir, dentry, ctx->mntfh,
					     ctx->clone_data.fattr);
	dput(parent);
	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	ctx->selected_flavor = client->cl_auth->au_flavor;
	अगर (ctx->clone_data.fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) अणु
		ret = nfs_करो_refmount(fc, client);
	पूर्ण अन्यथा अणु
		ret = nfs_करो_submount(fc);
	पूर्ण

	rpc_shutकरोwn_client(client);
	वापस ret;
पूर्ण

/*
 * Try one location from the fs_locations array.
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
अटल पूर्णांक nfs4_try_replacing_one_location(काष्ठा nfs_server *server,
		अक्षर *page, अक्षर *page2,
		स्थिर काष्ठा nfs4_fs_location *location)
अणु
	स्थिर माप_प्रकार addr_bufsize = माप(काष्ठा sockaddr_storage);
	काष्ठा net *net = rpc_net_ns(server->client);
	काष्ठा sockaddr *sap;
	अचिन्हित पूर्णांक s;
	माप_प्रकार salen;
	पूर्णांक error;

	sap = kदो_स्मृति(addr_bufsize, GFP_KERNEL);
	अगर (sap == शून्य)
		वापस -ENOMEM;

	error = -ENOENT;
	क्रम (s = 0; s < location->nservers; s++) अणु
		स्थिर काष्ठा nfs4_string *buf = &location->servers[s];
		अक्षर *hostname;

		अगर (buf->len <= 0 || buf->len > PAGE_SIZE)
			जारी;

		अगर (स_प्रथम(buf->data, IPV6_SCOPE_DELIMITER, buf->len) != शून्य)
			जारी;

		salen = nfs_parse_server_name(buf->data, buf->len,
						sap, addr_bufsize, net);
		अगर (salen == 0)
			जारी;
		rpc_set_port(sap, NFS_PORT);

		error = -ENOMEM;
		hostname = kmemdup_nul(buf->data, buf->len, GFP_KERNEL);
		अगर (hostname == शून्य)
			अवरोध;

		error = nfs4_update_server(server, hostname, sap, salen, net);
		kमुक्त(hostname);
		अगर (error == 0)
			अवरोध;
	पूर्ण

	kमुक्त(sap);
	वापस error;
पूर्ण

/**
 * nfs4_replace_transport - set up transport to destination server
 *
 * @server: export being migrated
 * @locations: fs_locations array
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 *
 * The client tries all the entries in the "locations" array, in the
 * order वापसed by the server, until one works or the end of the
 * array is reached.
 */
पूर्णांक nfs4_replace_transport(काष्ठा nfs_server *server,
			   स्थिर काष्ठा nfs4_fs_locations *locations)
अणु
	अक्षर *page = शून्य, *page2 = शून्य;
	पूर्णांक loc, error;

	error = -ENOENT;
	अगर (locations == शून्य || locations->nlocations <= 0)
		जाओ out;

	error = -ENOMEM;
	page = (अक्षर *) __get_मुक्त_page(GFP_USER);
	अगर (!page)
		जाओ out;
	page2 = (अक्षर *) __get_मुक्त_page(GFP_USER);
	अगर (!page2)
		जाओ out;

	क्रम (loc = 0; loc < locations->nlocations; loc++) अणु
		स्थिर काष्ठा nfs4_fs_location *location =
						&locations->locations[loc];

		अगर (location == शून्य || location->nservers <= 0 ||
		    location->rootpath.ncomponents == 0)
			जारी;

		error = nfs4_try_replacing_one_location(server, page,
							page2, location);
		अगर (error == 0)
			अवरोध;
	पूर्ण

out:
	मुक्त_page((अचिन्हित दीर्घ)page);
	मुक्त_page((अचिन्हित दीर्घ)page2);
	वापस error;
पूर्ण
