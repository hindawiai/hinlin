<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश "internal.h"
#समावेश "nfs3_fs.h"

#अगर_घोषित CONFIG_NFS_V3_ACL
अटल काष्ठा rpc_stat		nfsacl_rpcstat = अणु &nfsacl_program पूर्ण;
अटल स्थिर काष्ठा rpc_version *nfsacl_version[] = अणु
	[3]			= &nfsacl_version3,
पूर्ण;

स्थिर काष्ठा rpc_program nfsacl_program = अणु
	.name			= "nfsacl",
	.number			= NFS_ACL_PROGRAM,
	.nrvers			= ARRAY_SIZE(nfsacl_version),
	.version		= nfsacl_version,
	.stats			= &nfsacl_rpcstat,
पूर्ण;

/*
 * Initialise an NFSv3 ACL client connection
 */
अटल व्योम nfs_init_server_aclclient(काष्ठा nfs_server *server)
अणु
	अगर (server->flags & NFS_MOUNT_NOACL)
		जाओ out_noacl;

	server->client_acl = rpc_bind_new_program(server->client, &nfsacl_program, 3);
	अगर (IS_ERR(server->client_acl))
		जाओ out_noacl;

	/* No errors! Assume that Sun nfsacls are supported */
	server->caps |= NFS_CAP_ACLS;
	वापस;

out_noacl:
	server->caps &= ~NFS_CAP_ACLS;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nfs_init_server_aclclient(काष्ठा nfs_server *server)
अणु
	server->flags &= ~NFS_MOUNT_NOACL;
	server->caps &= ~NFS_CAP_ACLS;
पूर्ण
#पूर्ण_अगर

काष्ठा nfs_server *nfs3_create_server(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_server *server = nfs_create_server(fc);

	/* Create a client RPC handle क्रम the NFS v3 ACL management पूर्णांकerface */
	अगर (!IS_ERR(server))
		nfs_init_server_aclclient(server);
	वापस server;
पूर्ण

काष्ठा nfs_server *nfs3_clone_server(काष्ठा nfs_server *source,
				     काष्ठा nfs_fh *fh,
				     काष्ठा nfs_fattr *fattr,
				     rpc_authflavor_t flavor)
अणु
	काष्ठा nfs_server *server = nfs_clone_server(source, fh, fattr, flavor);
	अगर (!IS_ERR(server) && !IS_ERR(source->client_acl))
		nfs_init_server_aclclient(server);
	वापस server;
पूर्ण

/*
 * Set up a pNFS Data Server client over NFSv3.
 *
 * Return any existing nfs_client that matches server address,port,version
 * and minorversion.
 *
 * For a new nfs_client, use a soft mount (शेष), a low retrans and a
 * low समयout पूर्णांकerval so that अगर a connection is lost, we retry through
 * the MDS.
 */
काष्ठा nfs_client *nfs3_set_ds_client(काष्ठा nfs_server *mds_srv,
		स्थिर काष्ठा sockaddr *ds_addr, पूर्णांक ds_addrlen,
		पूर्णांक ds_proto, अचिन्हित पूर्णांक ds_समयo, अचिन्हित पूर्णांक ds_retrans)
अणु
	काष्ठा rpc_समयout ds_समयout;
	काष्ठा nfs_client *mds_clp = mds_srv->nfs_client;
	काष्ठा nfs_client_initdata cl_init = अणु
		.addr = ds_addr,
		.addrlen = ds_addrlen,
		.nodename = mds_clp->cl_rpcclient->cl_nodename,
		.ip_addr = mds_clp->cl_ipaddr,
		.nfs_mod = &nfs_v3,
		.proto = ds_proto,
		.net = mds_clp->cl_net,
		.समयparms = &ds_समयout,
		.cred = mds_srv->cred,
	पूर्ण;
	काष्ठा nfs_client *clp;
	अक्षर buf[INET6_ADDRSTRLEN + 1];

	/* fake a hostname because lockd wants it */
	अगर (rpc_ntop(ds_addr, buf, माप(buf)) <= 0)
		वापस ERR_PTR(-EINVAL);
	cl_init.hostname = buf;

	अगर (mds_clp->cl_nconnect > 1 && ds_proto == XPRT_TRANSPORT_TCP)
		cl_init.nconnect = mds_clp->cl_nconnect;

	अगर (mds_srv->flags & NFS_MOUNT_NORESVPORT)
		__set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);

	__set_bit(NFS_CS_NOPING, &cl_init.init_flags);
	__set_bit(NFS_CS_DS, &cl_init.init_flags);

	/* Use the MDS nfs_client cl_ipaddr. */
	nfs_init_समयout_values(&ds_समयout, ds_proto, ds_समयo, ds_retrans);
	clp = nfs_get_client(&cl_init);

	वापस clp;
पूर्ण
EXPORT_SYMBOL_GPL(nfs3_set_ds_client);
