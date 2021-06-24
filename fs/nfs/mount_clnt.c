<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * In-kernel MOUNT protocol client
 *
 * Copyright (C) 1997, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uपन.स>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/nfs_fs.h>
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY	NFSDBG_MOUNT

/*
 * Defined by RFC 1094, section A.3; and RFC 1813, section 5.1.4
 */
#घोषणा MNTPATHLEN		(1024)

/*
 * XDR data type sizes
 */
#घोषणा encode_dirpath_sz	(1 + XDR_QUADLEN(MNTPATHLEN))
#घोषणा MNT_status_sz		(1)
#घोषणा MNT_fhandle_sz		XDR_QUADLEN(NFS2_FHSIZE)
#घोषणा MNT_fhandlev3_sz	XDR_QUADLEN(NFS3_FHSIZE)
#घोषणा MNT_authflav3_sz	(1 + NFS_MAX_SECFLAVORS)

/*
 * XDR argument and result sizes
 */
#घोषणा MNT_enc_dirpath_sz	encode_dirpath_sz
#घोषणा MNT_dec_mountres_sz	(MNT_status_sz + MNT_fhandle_sz)
#घोषणा MNT_dec_mountres3_sz	(MNT_status_sz + MNT_fhandlev3_sz + \
				 MNT_authflav3_sz)

/*
 * Defined by RFC 1094, section A.5
 */
क्रमागत अणु
	MOUNTPROC_शून्य		= 0,
	MOUNTPROC_MNT		= 1,
	MOUNTPROC_DUMP		= 2,
	MOUNTPROC_UMNT		= 3,
	MOUNTPROC_UMNTALL	= 4,
	MOUNTPROC_EXPORT	= 5,
पूर्ण;

/*
 * Defined by RFC 1813, section 5.2
 */
क्रमागत अणु
	MOUNTPROC3_शून्य		= 0,
	MOUNTPROC3_MNT		= 1,
	MOUNTPROC3_DUMP		= 2,
	MOUNTPROC3_UMNT		= 3,
	MOUNTPROC3_UMNTALL	= 4,
	MOUNTPROC3_EXPORT	= 5,
पूर्ण;

अटल स्थिर काष्ठा rpc_program mnt_program;

/*
 * Defined by OpenGroup XNFS Version 3W, chapter 8
 */
क्रमागत mountstat अणु
	MNT_OK			= 0,
	MNT_EPERM		= 1,
	MNT_ENOENT		= 2,
	MNT_EACCES		= 13,
	MNT_EINVAL		= 22,
पूर्ण;

अटल काष्ठा अणु
	u32 status;
	पूर्णांक त्रुटि_सं;
पूर्ण mnt_errtbl[] = अणु
	अणु .status = MNT_OK,			.त्रुटि_सं = 0,		पूर्ण,
	अणु .status = MNT_EPERM,			.त्रुटि_सं = -EPERM,	पूर्ण,
	अणु .status = MNT_ENOENT,			.त्रुटि_सं = -ENOENT,	पूर्ण,
	अणु .status = MNT_EACCES,			.त्रुटि_सं = -EACCES,	पूर्ण,
	अणु .status = MNT_EINVAL,			.त्रुटि_सं = -EINVAL,	पूर्ण,
पूर्ण;

/*
 * Defined by RFC 1813, section 5.1.5
 */
क्रमागत mountstat3 अणु
	MNT3_OK			= 0,		/* no error */
	MNT3ERR_PERM		= 1,		/* Not owner */
	MNT3ERR_NOENT		= 2,		/* No such file or directory */
	MNT3ERR_IO		= 5,		/* I/O error */
	MNT3ERR_ACCES		= 13,		/* Permission denied */
	MNT3ERR_NOTसूची		= 20,		/* Not a directory */
	MNT3ERR_INVAL		= 22,		/* Invalid argument */
	MNT3ERR_NAMETOOLONG	= 63,		/* Filename too दीर्घ */
	MNT3ERR_NOTSUPP		= 10004,	/* Operation not supported */
	MNT3ERR_SERVERFAULT	= 10006,	/* A failure on the server */
पूर्ण;

अटल काष्ठा अणु
	u32 status;
	पूर्णांक त्रुटि_सं;
पूर्ण mnt3_errtbl[] = अणु
	अणु .status = MNT3_OK,			.त्रुटि_सं = 0,		पूर्ण,
	अणु .status = MNT3ERR_PERM,		.त्रुटि_सं = -EPERM,	पूर्ण,
	अणु .status = MNT3ERR_NOENT,		.त्रुटि_सं = -ENOENT,	पूर्ण,
	अणु .status = MNT3ERR_IO,			.त्रुटि_सं = -EIO,		पूर्ण,
	अणु .status = MNT3ERR_ACCES,		.त्रुटि_सं = -EACCES,	पूर्ण,
	अणु .status = MNT3ERR_NOTसूची,		.त्रुटि_सं = -ENOTसूची,	पूर्ण,
	अणु .status = MNT3ERR_INVAL,		.त्रुटि_सं = -EINVAL,	पूर्ण,
	अणु .status = MNT3ERR_NAMETOOLONG,	.त्रुटि_सं = -ENAMETOOLONG,	पूर्ण,
	अणु .status = MNT3ERR_NOTSUPP,		.त्रुटि_सं = -ENOTSUPP,	पूर्ण,
	अणु .status = MNT3ERR_SERVERFAULT,	.त्रुटि_सं = -EREMOTEIO,	पूर्ण,
पूर्ण;

काष्ठा mountres अणु
	पूर्णांक त्रुटि_सं;
	काष्ठा nfs_fh *fh;
	अचिन्हित पूर्णांक *auth_count;
	rpc_authflavor_t *auth_flavors;
पूर्ण;

काष्ठा mnt_fhstatus अणु
	u32 status;
	काष्ठा nfs_fh *fh;
पूर्ण;

/**
 * nfs_mount - Obtain an NFS file handle क्रम the given host and path
 * @info: poपूर्णांकer to mount request arguments
 * @समयo: deciseconds the mount रुकोs क्रम a response beक्रमe it retries
 * @retrans: number of बार the mount retries a request
 *
 * Uses समयout parameters specअगरied by caller. On successful वापस, the
 * auth_flavs list and auth_flav_len will be populated with the list from the
 * server or a faked-up list अगर the server didn't provide one.
 */
पूर्णांक nfs_mount(काष्ठा nfs_mount_request *info, पूर्णांक समयo, पूर्णांक retrans)
अणु
	काष्ठा rpc_समयout mnt_समयout;
	काष्ठा mountres	result = अणु
		.fh		= info->fh,
		.auth_count	= info->auth_flav_len,
		.auth_flavors	= info->auth_flavs,
	पूर्ण;
	काष्ठा rpc_message msg	= अणु
		.rpc_argp	= info->dirpath,
		.rpc_resp	= &result,
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= info->net,
		.protocol	= info->protocol,
		.address	= info->sap,
		.addrsize	= info->salen,
		.समयout	= &mnt_समयout,
		.servername	= info->hostname,
		.program	= &mnt_program,
		.version	= info->version,
		.authflavor	= RPC_AUTH_UNIX,
		.cred		= current_cred(),
	पूर्ण;
	काष्ठा rpc_clnt		*mnt_clnt;
	पूर्णांक			status;

	dprपूर्णांकk("NFS: sending MNT request for %s:%s\n",
		(info->hostname ? info->hostname : "server"),
			info->dirpath);

	अगर (म_माप(info->dirpath) > MNTPATHLEN)
		वापस -ENAMETOOLONG;

	अगर (info->noresvport)
		args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;

	nfs_init_समयout_values(&mnt_समयout, info->protocol, समयo, retrans);
	mnt_clnt = rpc_create(&args);
	अगर (IS_ERR(mnt_clnt))
		जाओ out_clnt_err;

	अगर (info->version == NFS_MNT3_VERSION)
		msg.rpc_proc = &mnt_clnt->cl_procinfo[MOUNTPROC3_MNT];
	अन्यथा
		msg.rpc_proc = &mnt_clnt->cl_procinfo[MOUNTPROC_MNT];

	status = rpc_call_sync(mnt_clnt, &msg, RPC_TASK_SOFT|RPC_TASK_TIMEOUT);
	rpc_shutकरोwn_client(mnt_clnt);

	अगर (status < 0)
		जाओ out_call_err;
	अगर (result.त्रुटि_सं != 0)
		जाओ out_mnt_err;

	dprपूर्णांकk("NFS: MNT request succeeded\n");
	status = 0;

	/*
	 * If the server didn't provide a flavor list, allow the
	 * client to try any flavor.
	 */
	अगर (info->version != NFS_MNT3_VERSION || *info->auth_flav_len == 0) अणु
		dprपूर्णांकk("NFS: Faking up auth_flavs list\n");
		info->auth_flavs[0] = RPC_AUTH_शून्य;
		*info->auth_flav_len = 1;
	पूर्ण
out:
	वापस status;

out_clnt_err:
	status = PTR_ERR(mnt_clnt);
	dprपूर्णांकk("NFS: failed to create MNT RPC client, status=%d\n", status);
	जाओ out;

out_call_err:
	dprपूर्णांकk("NFS: MNT request failed, status=%d\n", status);
	जाओ out;

out_mnt_err:
	dprपूर्णांकk("NFS: MNT server returned result %d\n", result.त्रुटि_सं);
	status = result.त्रुटि_सं;
	जाओ out;
पूर्ण

/**
 * nfs_umount - Notअगरy a server that we have unmounted this export
 * @info: poपूर्णांकer to umount request arguments
 *
 * MOUNTPROC_UMNT is advisory, so we set a लघु समयout, and always
 * use UDP.
 */
व्योम nfs_umount(स्थिर काष्ठा nfs_mount_request *info)
अणु
	अटल स्थिर काष्ठा rpc_समयout nfs_umnt_समयout = अणु
		.to_initval = 1 * HZ,
		.to_maxval = 3 * HZ,
		.to_retries = 2,
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= info->net,
		.protocol	= IPPROTO_UDP,
		.address	= info->sap,
		.addrsize	= info->salen,
		.समयout	= &nfs_umnt_समयout,
		.servername	= info->hostname,
		.program	= &mnt_program,
		.version	= info->version,
		.authflavor	= RPC_AUTH_UNIX,
		.flags		= RPC_CLNT_CREATE_NOPING,
		.cred		= current_cred(),
	पूर्ण;
	काष्ठा rpc_message msg	= अणु
		.rpc_argp	= info->dirpath,
	पूर्ण;
	काष्ठा rpc_clnt *clnt;
	पूर्णांक status;

	अगर (म_माप(info->dirpath) > MNTPATHLEN)
		वापस;

	अगर (info->noresvport)
		args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;

	clnt = rpc_create(&args);
	अगर (IS_ERR(clnt))
		जाओ out_clnt_err;

	dprपूर्णांकk("NFS: sending UMNT request for %s:%s\n",
		(info->hostname ? info->hostname : "server"), info->dirpath);

	अगर (info->version == NFS_MNT3_VERSION)
		msg.rpc_proc = &clnt->cl_procinfo[MOUNTPROC3_UMNT];
	अन्यथा
		msg.rpc_proc = &clnt->cl_procinfo[MOUNTPROC_UMNT];

	status = rpc_call_sync(clnt, &msg, 0);
	rpc_shutकरोwn_client(clnt);

	अगर (unlikely(status < 0))
		जाओ out_call_err;

	वापस;

out_clnt_err:
	dprपूर्णांकk("NFS: failed to create UMNT RPC client, status=%ld\n",
			PTR_ERR(clnt));
	वापस;

out_call_err:
	dprपूर्णांकk("NFS: UMNT request failed, status=%d\n", status);
पूर्ण

/*
 * XDR encode/decode functions क्रम MOUNT
 */

अटल व्योम encode_mntdirpath(काष्ठा xdr_stream *xdr, स्थिर अक्षर *pathname)
अणु
	स्थिर u32 pathname_len = म_माप(pathname);
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + pathname_len);
	xdr_encode_opaque(p, pathname, pathname_len);
पूर्ण

अटल व्योम mnt_xdr_enc_dirpath(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *dirpath)
अणु
	encode_mntdirpath(xdr, dirpath);
पूर्ण

/*
 * RFC 1094: "A non-zero status indicates some sort of error.  In this
 * हाल, the status is a UNIX error number."  This can be problematic
 * अगर the server and client use dअगरferent त्रुटि_सं values क्रम the same
 * error.
 *
 * However, the OpenGroup XNFS spec provides a simple mapping that is
 * independent of local त्रुटि_सं values on the server and the client.
 */
अटल पूर्णांक decode_status(काष्ठा xdr_stream *xdr, काष्ठा mountres *res)
अणु
	अचिन्हित पूर्णांक i;
	u32 status;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;
	status = be32_to_cpup(p);

	क्रम (i = 0; i < ARRAY_SIZE(mnt_errtbl); i++) अणु
		अगर (mnt_errtbl[i].status == status) अणु
			res->त्रुटि_सं = mnt_errtbl[i].त्रुटि_सं;
			वापस 0;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("NFS: unrecognized MNT status code: %u\n", status);
	res->त्रुटि_सं = -EACCES;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_fhandle(काष्ठा xdr_stream *xdr, काष्ठा mountres *res)
अणु
	काष्ठा nfs_fh *fh = res->fh;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS2_FHSIZE);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	fh->size = NFS2_FHSIZE;
	स_नकल(fh->data, p, NFS2_FHSIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक mnt_xdr_dec_mountres(काष्ठा rpc_rqst *req,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा mountres *res = data;
	पूर्णांक status;

	status = decode_status(xdr, res);
	अगर (unlikely(status != 0 || res->त्रुटि_सं != 0))
		वापस status;
	वापस decode_fhandle(xdr, res);
पूर्ण

अटल पूर्णांक decode_fhs_status(काष्ठा xdr_stream *xdr, काष्ठा mountres *res)
अणु
	अचिन्हित पूर्णांक i;
	u32 status;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;
	status = be32_to_cpup(p);

	क्रम (i = 0; i < ARRAY_SIZE(mnt3_errtbl); i++) अणु
		अगर (mnt3_errtbl[i].status == status) अणु
			res->त्रुटि_सं = mnt3_errtbl[i].त्रुटि_सं;
			वापस 0;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("NFS: unrecognized MNT3 status code: %u\n", status);
	res->त्रुटि_सं = -EACCES;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_fhandle3(काष्ठा xdr_stream *xdr, काष्ठा mountres *res)
अणु
	काष्ठा nfs_fh *fh = res->fh;
	u32 size;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	size = be32_to_cpup(p);
	अगर (size > NFS3_FHSIZE || size == 0)
		वापस -EIO;

	p = xdr_अंतरभूत_decode(xdr, size);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	fh->size = size;
	स_नकल(fh->data, p, size);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_auth_flavors(काष्ठा xdr_stream *xdr, काष्ठा mountres *res)
अणु
	rpc_authflavor_t *flavors = res->auth_flavors;
	अचिन्हित पूर्णांक *count = res->auth_count;
	u32 entries, i;
	__be32 *p;

	अगर (*count == 0)
		वापस 0;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;
	entries = be32_to_cpup(p);
	dprपूर्णांकk("NFS: received %u auth flavors\n", entries);
	अगर (entries > NFS_MAX_SECFLAVORS)
		entries = NFS_MAX_SECFLAVORS;

	p = xdr_अंतरभूत_decode(xdr, 4 * entries);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	अगर (entries > *count)
		entries = *count;

	क्रम (i = 0; i < entries; i++) अणु
		flavors[i] = be32_to_cpup(p++);
		dprपूर्णांकk("NFS:   auth flavor[%u]: %d\n", i, flavors[i]);
	पूर्ण
	*count = i;

	वापस 0;
पूर्ण

अटल पूर्णांक mnt_xdr_dec_mountres3(काष्ठा rpc_rqst *req,
				 काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा mountres *res = data;
	पूर्णांक status;

	status = decode_fhs_status(xdr, res);
	अगर (unlikely(status != 0 || res->त्रुटि_सं != 0))
		वापस status;
	status = decode_fhandle3(xdr, res);
	अगर (unlikely(status != 0)) अणु
		res->त्रुटि_सं = -EBADHANDLE;
		वापस 0;
	पूर्ण
	वापस decode_auth_flavors(xdr, res);
पूर्ण

अटल स्थिर काष्ठा rpc_procinfo mnt_procedures[] = अणु
	[MOUNTPROC_MNT] = अणु
		.p_proc		= MOUNTPROC_MNT,
		.p_encode	= mnt_xdr_enc_dirpath,
		.p_decode	= mnt_xdr_dec_mountres,
		.p_arglen	= MNT_enc_dirpath_sz,
		.p_replen	= MNT_dec_mountres_sz,
		.p_statidx	= MOUNTPROC_MNT,
		.p_name		= "MOUNT",
	पूर्ण,
	[MOUNTPROC_UMNT] = अणु
		.p_proc		= MOUNTPROC_UMNT,
		.p_encode	= mnt_xdr_enc_dirpath,
		.p_arglen	= MNT_enc_dirpath_sz,
		.p_statidx	= MOUNTPROC_UMNT,
		.p_name		= "UMOUNT",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpc_procinfo mnt3_procedures[] = अणु
	[MOUNTPROC3_MNT] = अणु
		.p_proc		= MOUNTPROC3_MNT,
		.p_encode	= mnt_xdr_enc_dirpath,
		.p_decode	= mnt_xdr_dec_mountres3,
		.p_arglen	= MNT_enc_dirpath_sz,
		.p_replen	= MNT_dec_mountres3_sz,
		.p_statidx	= MOUNTPROC3_MNT,
		.p_name		= "MOUNT",
	पूर्ण,
	[MOUNTPROC3_UMNT] = अणु
		.p_proc		= MOUNTPROC3_UMNT,
		.p_encode	= mnt_xdr_enc_dirpath,
		.p_arglen	= MNT_enc_dirpath_sz,
		.p_statidx	= MOUNTPROC3_UMNT,
		.p_name		= "UMOUNT",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक mnt_counts[ARRAY_SIZE(mnt_procedures)];
अटल स्थिर काष्ठा rpc_version mnt_version1 = अणु
	.number		= 1,
	.nrprocs	= ARRAY_SIZE(mnt_procedures),
	.procs		= mnt_procedures,
	.counts		= mnt_counts,
पूर्ण;

अटल अचिन्हित पूर्णांक mnt3_counts[ARRAY_SIZE(mnt3_procedures)];
अटल स्थिर काष्ठा rpc_version mnt_version3 = अणु
	.number		= 3,
	.nrprocs	= ARRAY_SIZE(mnt3_procedures),
	.procs		= mnt3_procedures,
	.counts		= mnt3_counts,
पूर्ण;

अटल स्थिर काष्ठा rpc_version *mnt_version[] = अणु
	शून्य,
	&mnt_version1,
	शून्य,
	&mnt_version3,
पूर्ण;

अटल काष्ठा rpc_stat mnt_stats;

अटल स्थिर काष्ठा rpc_program mnt_program = अणु
	.name		= "mount",
	.number		= NFS_MNT_PROGRAM,
	.nrvers		= ARRAY_SIZE(mnt_version),
	.version	= mnt_version,
	.stats		= &mnt_stats,
पूर्ण;
