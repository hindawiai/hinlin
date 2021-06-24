<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/nfs2xdr.c
 *
 * XDR functions to encode/decode NFS RPC arguments and results.
 *
 * Copyright (C) 1992, 1993, 1994  Rick Sladkey
 * Copyright (C) 1996 Olaf Kirch
 * 04 Aug 1998  Ion Badulescu <ionut@cs.columbia.edu>
 * 		FIFO's need special handling in NFSv2
 */

#समावेश <linux/param.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs_fs.h>
#समावेश "nfstrace.h"
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_XDR

/* Mapping from NFS error code to "errno" error code. */
#घोषणा त्रुटि_सं_NFSERR_IO		EIO

/*
 * Declare the space requirements क्रम NFS arguments and replies as
 * number of 32bit-words
 */
#घोषणा NFS_pagepad_sz		(1) /* Page padding */
#घोषणा NFS_fhandle_sz		(8)
#घोषणा NFS_sattr_sz		(8)
#घोषणा NFS_filename_sz		(1+(NFS2_MAXNAMLEN>>2))
#घोषणा NFS_path_sz		(1+(NFS2_MAXPATHLEN>>2))
#घोषणा NFS_fattr_sz		(17)
#घोषणा NFS_info_sz		(5)
#घोषणा NFS_entry_sz		(NFS_filename_sz+3)

#घोषणा NFS_diropargs_sz	(NFS_fhandle_sz+NFS_filename_sz)
#घोषणा NFS_हटाओargs_sz	(NFS_fhandle_sz+NFS_filename_sz)
#घोषणा NFS_sattrargs_sz	(NFS_fhandle_sz+NFS_sattr_sz)
#घोषणा NFS_पढ़ोlinkargs_sz	(NFS_fhandle_sz)
#घोषणा NFS_पढ़ोargs_sz		(NFS_fhandle_sz+3)
#घोषणा NFS_ग_लिखोargs_sz	(NFS_fhandle_sz+4)
#घोषणा NFS_createargs_sz	(NFS_diropargs_sz+NFS_sattr_sz)
#घोषणा NFS_नामargs_sz	(NFS_diropargs_sz+NFS_diropargs_sz)
#घोषणा NFS_linkargs_sz		(NFS_fhandle_sz+NFS_diropargs_sz)
#घोषणा NFS_symlinkargs_sz	(NFS_diropargs_sz+1+NFS_sattr_sz)
#घोषणा NFS_सूची_पढ़ोargs_sz	(NFS_fhandle_sz+2)

#घोषणा NFS_attrstat_sz		(1+NFS_fattr_sz)
#घोषणा NFS_diropres_sz		(1+NFS_fhandle_sz+NFS_fattr_sz)
#घोषणा NFS_पढ़ोlinkres_sz	(2+NFS_pagepad_sz)
#घोषणा NFS_पढ़ोres_sz		(1+NFS_fattr_sz+1+NFS_pagepad_sz)
#घोषणा NFS_ग_लिखोres_sz         (NFS_attrstat_sz)
#घोषणा NFS_stat_sz		(1)
#घोषणा NFS_सूची_पढ़ोres_sz	(1+NFS_pagepad_sz)
#घोषणा NFS_statfsres_sz	(1+NFS_info_sz)

अटल पूर्णांक nfs_stat_to_त्रुटि_सं(क्रमागत nfs_stat);

/*
 * Encode/decode NFSv2 basic data types
 *
 * Basic NFSv2 data types are defined in section 2.3 of RFC 1094:
 * "NFS: Network File System Protocol Specification".
 *
 * Not all basic data types have their own encoding and decoding
 * functions.  For run-समय efficiency, some data types are encoded
 * or decoded अंतरभूत.
 */

अटल काष्ठा user_namespace *rpc_userns(स्थिर काष्ठा rpc_clnt *clnt)
अणु
	अगर (clnt && clnt->cl_cred)
		वापस clnt->cl_cred->user_ns;
	वापस &init_user_ns;
पूर्ण

अटल काष्ठा user_namespace *rpc_rqst_userns(स्थिर काष्ठा rpc_rqst *rqstp)
अणु
	अगर (rqstp->rq_task)
		वापस rpc_userns(rqstp->rq_task->tk_client);
	वापस &init_user_ns;
पूर्ण

/*
 *	प्रकार opaque	nfsdata<>;
 */
अटल पूर्णांक decode_nfsdata(काष्ठा xdr_stream *xdr, काष्ठा nfs_pgio_res *result)
अणु
	u32 recvd, count;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	count = be32_to_cpup(p);
	recvd = xdr_पढ़ो_pages(xdr, count);
	अगर (unlikely(count > recvd))
		जाओ out_cheating;
out:
	result->eof = 0;	/* NFSv2 करोes not pass खातापूर्ण flag on the wire. */
	result->count = count;
	वापस count;
out_cheating:
	dprपूर्णांकk("NFS: server cheating in read result: "
		"count %u > recvd %u\n", count, recvd);
	count = recvd;
	जाओ out;
पूर्ण

/*
 *	क्रमागत stat अणु
 *		NFS_OK = 0,
 *		NFSERR_PERM = 1,
 *		NFSERR_NOENT = 2,
 *		NFSERR_IO = 5,
 *		NFSERR_NXIO = 6,
 *		NFSERR_ACCES = 13,
 *		NFSERR_EXIST = 17,
 *		NFSERR_NODEV = 19,
 *		NFSERR_NOTसूची = 20,
 *		NFSERR_ISसूची = 21,
 *		NFSERR_FBIG = 27,
 *		NFSERR_NOSPC = 28,
 *		NFSERR_ROFS = 30,
 *		NFSERR_NAMETOOLONG = 63,
 *		NFSERR_NOTEMPTY = 66,
 *		NFSERR_DQUOT = 69,
 *		NFSERR_STALE = 70,
 *		NFSERR_WFLUSH = 99
 *	पूर्ण;
 */
अटल पूर्णांक decode_stat(काष्ठा xdr_stream *xdr, क्रमागत nfs_stat *status)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (unlikely(*p != cpu_to_be32(NFS_OK)))
		जाओ out_status;
	*status = 0;
	वापस 0;
out_status:
	*status = be32_to_cpup(p);
	trace_nfs_xdr_status(xdr, (पूर्णांक)*status);
	वापस 0;
पूर्ण

/*
 * 2.3.2.  ftype
 *
 *	क्रमागत ftype अणु
 *		NFNON = 0,
 *		NFREG = 1,
 *		NFसूची = 2,
 *		NFBLK = 3,
 *		NFCHR = 4,
 *		NFLNK = 5
 *	पूर्ण;
 *
 */
अटल __be32 *xdr_decode_ftype(__be32 *p, u32 *type)
अणु
	*type = be32_to_cpup(p++);
	अगर (unlikely(*type > NF2FIFO))
		*type = NFBAD;
	वापस p;
पूर्ण

/*
 * 2.3.3.  fhandle
 *
 *	प्रकार opaque fhandle[FHSIZE];
 */
अटल व्योम encode_fhandle(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS2_FHSIZE);
	स_नकल(p, fh->data, NFS2_FHSIZE);
पूर्ण

अटल पूर्णांक decode_fhandle(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS2_FHSIZE);
	अगर (unlikely(!p))
		वापस -EIO;
	fh->size = NFS2_FHSIZE;
	स_नकल(fh->data, p, NFS2_FHSIZE);
	वापस 0;
पूर्ण

/*
 * 2.3.4.  समयval
 *
 *	काष्ठा समयval अणु
 *		अचिन्हित पूर्णांक seconds;
 *		अचिन्हित पूर्णांक useconds;
 *	पूर्ण;
 */
अटल __be32 *xdr_encode_समय(__be32 *p, स्थिर काष्ठा बारpec64 *समयp)
अणु
	*p++ = cpu_to_be32((u32)समयp->tv_sec);
	अगर (समयp->tv_nsec != 0)
		*p++ = cpu_to_be32(समयp->tv_nsec / NSEC_PER_USEC);
	अन्यथा
		*p++ = cpu_to_be32(0);
	वापस p;
पूर्ण

/*
 * Passing the invalid value useconds=1000000 is a Sun convention क्रम
 * "set to current server time".  It's needed to make permissions checks
 * क्रम the "touch" program across v2 mounts to Solaris and Irix servers
 * work correctly.  See description of sattr in section 6.1 of "NFS
 * Illustrated" by Brent Callaghan, Addison-Wesley, ISBN 0-201-32750-5.
 */
अटल __be32 *xdr_encode_current_server_समय(__be32 *p,
					      स्थिर काष्ठा बारpec64 *समयp)
अणु
	*p++ = cpu_to_be32(समयp->tv_sec);
	*p++ = cpu_to_be32(1000000);
	वापस p;
पूर्ण

अटल __be32 *xdr_decode_समय(__be32 *p, काष्ठा बारpec64 *समयp)
अणु
	समयp->tv_sec = be32_to_cpup(p++);
	समयp->tv_nsec = be32_to_cpup(p++) * NSEC_PER_USEC;
	वापस p;
पूर्ण

/*
 * 2.3.5.  fattr
 *
 *	काष्ठा fattr अणु
 *		ftype		type;
 *		अचिन्हित पूर्णांक	mode;
 *		अचिन्हित पूर्णांक	nlink;
 *		अचिन्हित पूर्णांक	uid;
 *		अचिन्हित पूर्णांक	gid;
 *		अचिन्हित पूर्णांक	size;
 *		अचिन्हित पूर्णांक	blocksize;
 *		अचिन्हित पूर्णांक	rdev;
 *		अचिन्हित पूर्णांक	blocks;
 *		अचिन्हित पूर्णांक	fsid;
 *		अचिन्हित पूर्णांक	fileid;
 *		समयval		aसमय;
 *		समयval		mसमय;
 *		समयval		स_समय;
 *	पूर्ण;
 *
 */
अटल पूर्णांक decode_fattr(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा user_namespace *userns)
अणु
	u32 rdev, type;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS_fattr_sz << 2);
	अगर (unlikely(!p))
		वापस -EIO;

	fattr->valid |= NFS_ATTR_FATTR_V2;

	p = xdr_decode_ftype(p, &type);

	fattr->mode = be32_to_cpup(p++);
	fattr->nlink = be32_to_cpup(p++);
	fattr->uid = make_kuid(userns, be32_to_cpup(p++));
	अगर (!uid_valid(fattr->uid))
		जाओ out_uid;
	fattr->gid = make_kgid(userns, be32_to_cpup(p++));
	अगर (!gid_valid(fattr->gid))
		जाओ out_gid;
		
	fattr->size = be32_to_cpup(p++);
	fattr->du.nfs2.blocksize = be32_to_cpup(p++);

	rdev = be32_to_cpup(p++);
	fattr->rdev = new_decode_dev(rdev);
	अगर (type == (u32)NFCHR && rdev == (u32)NFS2_FIFO_DEV) अणु
		fattr->mode = (fattr->mode & ~S_IFMT) | S_IFIFO;
		fattr->rdev = 0;
	पूर्ण

	fattr->du.nfs2.blocks = be32_to_cpup(p++);
	fattr->fsid.major = be32_to_cpup(p++);
	fattr->fsid.minor = 0;
	fattr->fileid = be32_to_cpup(p++);

	p = xdr_decode_समय(p, &fattr->aसमय);
	p = xdr_decode_समय(p, &fattr->mसमय);
	xdr_decode_समय(p, &fattr->स_समय);
	fattr->change_attr = nfs_बारpec_to_change_attr(&fattr->स_समय);

	वापस 0;
out_uid:
	dprपूर्णांकk("NFS: returned invalid uid\n");
	वापस -EINVAL;
out_gid:
	dprपूर्णांकk("NFS: returned invalid gid\n");
	वापस -EINVAL;
पूर्ण

/*
 * 2.3.6.  sattr
 *
 *	काष्ठा sattr अणु
 *		अचिन्हित पूर्णांक	mode;
 *		अचिन्हित पूर्णांक	uid;
 *		अचिन्हित पूर्णांक	gid;
 *		अचिन्हित पूर्णांक	size;
 *		समयval		aसमय;
 *		समयval		mसमय;
 *	पूर्ण;
 */

#घोषणा NFS2_SATTR_NOT_SET	(0xffffffff)

अटल __be32 *xdr_समय_not_set(__be32 *p)
अणु
	*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	वापस p;
पूर्ण

अटल व्योम encode_sattr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा iattr *attr,
		काष्ठा user_namespace *userns)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS_sattr_sz << 2);

	अगर (attr->ia_valid & ATTR_MODE)
		*p++ = cpu_to_be32(attr->ia_mode);
	अन्यथा
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	अगर (attr->ia_valid & ATTR_UID)
		*p++ = cpu_to_be32(from_kuid_munged(userns, attr->ia_uid));
	अन्यथा
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	अगर (attr->ia_valid & ATTR_GID)
		*p++ = cpu_to_be32(from_kgid_munged(userns, attr->ia_gid));
	अन्यथा
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	अगर (attr->ia_valid & ATTR_SIZE)
		*p++ = cpu_to_be32((u32)attr->ia_size);
	अन्यथा
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);

	अगर (attr->ia_valid & ATTR_ATIME_SET)
		p = xdr_encode_समय(p, &attr->ia_aसमय);
	अन्यथा अगर (attr->ia_valid & ATTR_ATIME)
		p = xdr_encode_current_server_समय(p, &attr->ia_aसमय);
	अन्यथा
		p = xdr_समय_not_set(p);
	अगर (attr->ia_valid & ATTR_MTIME_SET)
		xdr_encode_समय(p, &attr->ia_mसमय);
	अन्यथा अगर (attr->ia_valid & ATTR_MTIME)
		xdr_encode_current_server_समय(p, &attr->ia_mसमय);
	अन्यथा
		xdr_समय_not_set(p);
पूर्ण

/*
 * 2.3.7.  filename
 *
 *	प्रकार string filename<MAXNAMLEN>;
 */
अटल व्योम encode_filename(काष्ठा xdr_stream *xdr,
			    स्थिर अक्षर *name, u32 length)
अणु
	__be32 *p;

	WARN_ON_ONCE(length > NFS2_MAXNAMLEN);
	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, name, length);
पूर्ण

अटल पूर्णांक decode_filename_अंतरभूत(काष्ठा xdr_stream *xdr,
				  स्थिर अक्षर **name, u32 *length)
अणु
	__be32 *p;
	u32 count;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	count = be32_to_cpup(p);
	अगर (count > NFS3_MAXNAMLEN)
		जाओ out_nametooदीर्घ;
	p = xdr_अंतरभूत_decode(xdr, count);
	अगर (unlikely(!p))
		वापस -EIO;
	*name = (स्थिर अक्षर *)p;
	*length = count;
	वापस 0;
out_nametooदीर्घ:
	dprपूर्णांकk("NFS: returned filename too long: %u\n", count);
	वापस -ENAMETOOLONG;
पूर्ण

/*
 * 2.3.8.  path
 *
 *	प्रकार string path<MAXPATHLEN>;
 */
अटल व्योम encode_path(काष्ठा xdr_stream *xdr, काष्ठा page **pages, u32 length)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(length);
	xdr_ग_लिखो_pages(xdr, pages, 0, length);
पूर्ण

अटल पूर्णांक decode_path(काष्ठा xdr_stream *xdr)
अणु
	u32 length, recvd;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	length = be32_to_cpup(p);
	अगर (unlikely(length >= xdr->buf->page_len || length > NFS_MAXPATHLEN))
		जाओ out_size;
	recvd = xdr_पढ़ो_pages(xdr, length);
	अगर (unlikely(length > recvd))
		जाओ out_cheating;
	xdr_terminate_string(xdr->buf, length);
	वापस 0;
out_size:
	dprपूर्णांकk("NFS: returned pathname too long: %u\n", length);
	वापस -ENAMETOOLONG;
out_cheating:
	dprपूर्णांकk("NFS: server cheating in pathname result: "
		"length %u > received %u\n", length, recvd);
	वापस -EIO;
पूर्ण

/*
 * 2.3.9.  attrstat
 *
 *	जोड़ attrstat चयन (stat status) अणु
 *	हाल NFS_OK:
 *		fattr attributes;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक decode_attrstat(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *result,
			   __u32 *op_status,
			   काष्ठा user_namespace *userns)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (op_status)
		*op_status = status;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_fattr(xdr, result, userns);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 2.3.10.  diropargs
 *
 *	काष्ठा diropargs अणु
 *		fhandle  dir;
 *		filename name;
 *	पूर्ण;
 */
अटल व्योम encode_diropargs(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh,
			     स्थिर अक्षर *name, u32 length)
अणु
	encode_fhandle(xdr, fh);
	encode_filename(xdr, name, length);
पूर्ण

/*
 * 2.3.11.  diropres
 *
 *	जोड़ diropres चयन (stat status) अणु
 *	हाल NFS_OK:
 *		काष्ठा अणु
 *			fhandle file;
 *			fattr   attributes;
 *		पूर्ण diropok;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक decode_diropok(काष्ठा xdr_stream *xdr, काष्ठा nfs_diropok *result,
		काष्ठा user_namespace *userns)
अणु
	पूर्णांक error;

	error = decode_fhandle(xdr, result->fh);
	अगर (unlikely(error))
		जाओ out;
	error = decode_fattr(xdr, result->fattr, userns);
out:
	वापस error;
पूर्ण

अटल पूर्णांक decode_diropres(काष्ठा xdr_stream *xdr, काष्ठा nfs_diropok *result,
		काष्ठा user_namespace *userns)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_diropok(xdr, result, userns);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण


/*
 * NFSv2 XDR encode functions
 *
 * NFSv2 argument types are defined in section 2.2 of RFC 1094:
 * "NFS: Network File System Protocol Specification".
 */

अटल व्योम nfs2_xdr_enc_fhandle(काष्ठा rpc_rqst *req,
				 काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_fh *fh = data;

	encode_fhandle(xdr, fh);
पूर्ण

/*
 * 2.2.3.  sattrargs
 *
 *	काष्ठा sattrargs अणु
 *		fhandle file;
 *		sattr attributes;
 *	पूर्ण;
 */
अटल व्योम nfs2_xdr_enc_sattrargs(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_sattrargs *args = data;

	encode_fhandle(xdr, args->fh);
	encode_sattr(xdr, args->sattr, rpc_rqst_userns(req));
पूर्ण

अटल व्योम nfs2_xdr_enc_diropargs(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_diropargs *args = data;

	encode_diropargs(xdr, args->fh, args->name, args->len);
पूर्ण

अटल व्योम nfs2_xdr_enc_पढ़ोlinkargs(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_पढ़ोlinkargs *args = data;

	encode_fhandle(xdr, args->fh);
	rpc_prepare_reply_pages(req, args->pages, args->pgbase, args->pglen,
				NFS_पढ़ोlinkres_sz - NFS_pagepad_sz);
पूर्ण

/*
 * 2.2.7.  पढ़ोargs
 *
 *	काष्ठा पढ़ोargs अणु
 *		fhandle file;
 *		अचिन्हित offset;
 *		अचिन्हित count;
 *		अचिन्हित totalcount;
 *	पूर्ण;
 */
अटल व्योम encode_पढ़ोargs(काष्ठा xdr_stream *xdr,
			    स्थिर काष्ठा nfs_pgio_args *args)
अणु
	u32 offset = args->offset;
	u32 count = args->count;
	__be32 *p;

	encode_fhandle(xdr, args->fh);

	p = xdr_reserve_space(xdr, 4 + 4 + 4);
	*p++ = cpu_to_be32(offset);
	*p++ = cpu_to_be32(count);
	*p = cpu_to_be32(count);
पूर्ण

अटल व्योम nfs2_xdr_enc_पढ़ोargs(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;

	encode_पढ़ोargs(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, args->pgbase, args->count,
				NFS_पढ़ोres_sz - NFS_pagepad_sz);
	req->rq_rcv_buf.flags |= XDRBUF_READ;
पूर्ण

/*
 * 2.2.9.  ग_लिखोargs
 *
 *	काष्ठा ग_लिखोargs अणु
 *		fhandle file;
 *		अचिन्हित beginoffset;
 *		अचिन्हित offset;
 *		अचिन्हित totalcount;
 *		nfsdata data;
 *	पूर्ण;
 */
अटल व्योम encode_ग_लिखोargs(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs_pgio_args *args)
अणु
	u32 offset = args->offset;
	u32 count = args->count;
	__be32 *p;

	encode_fhandle(xdr, args->fh);

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4);
	*p++ = cpu_to_be32(offset);
	*p++ = cpu_to_be32(offset);
	*p++ = cpu_to_be32(count);

	/* nfsdata */
	*p = cpu_to_be32(count);
	xdr_ग_लिखो_pages(xdr, args->pages, args->pgbase, count);
पूर्ण

अटल व्योम nfs2_xdr_enc_ग_लिखोargs(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;

	encode_ग_लिखोargs(xdr, args);
	xdr->buf->flags |= XDRBUF_WRITE;
पूर्ण

/*
 * 2.2.10.  createargs
 *
 *	काष्ठा createargs अणु
 *		diropargs where;
 *		sattr attributes;
 *	पूर्ण;
 */
अटल व्योम nfs2_xdr_enc_createargs(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_createargs *args = data;

	encode_diropargs(xdr, args->fh, args->name, args->len);
	encode_sattr(xdr, args->sattr, rpc_rqst_userns(req));
पूर्ण

अटल व्योम nfs2_xdr_enc_हटाओargs(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_हटाओargs *args = data;

	encode_diropargs(xdr, args->fh, args->name.name, args->name.len);
पूर्ण

/*
 * 2.2.12.  नामargs
 *
 *	काष्ठा नामargs अणु
 *		diropargs from;
 *		diropargs to;
 *	पूर्ण;
 */
अटल व्योम nfs2_xdr_enc_नामargs(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_नामargs *args = data;
	स्थिर काष्ठा qstr *old = args->old_name;
	स्थिर काष्ठा qstr *new = args->new_name;

	encode_diropargs(xdr, args->old_dir, old->name, old->len);
	encode_diropargs(xdr, args->new_dir, new->name, new->len);
पूर्ण

/*
 * 2.2.13.  linkargs
 *
 *	काष्ठा linkargs अणु
 *		fhandle from;
 *		diropargs to;
 *	पूर्ण;
 */
अटल व्योम nfs2_xdr_enc_linkargs(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_linkargs *args = data;

	encode_fhandle(xdr, args->fromfh);
	encode_diropargs(xdr, args->tofh, args->toname, args->tolen);
पूर्ण

/*
 * 2.2.14.  symlinkargs
 *
 *	काष्ठा symlinkargs अणु
 *		diropargs from;
 *		path to;
 *		sattr attributes;
 *	पूर्ण;
 */
अटल व्योम nfs2_xdr_enc_symlinkargs(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_symlinkargs *args = data;

	encode_diropargs(xdr, args->fromfh, args->fromname, args->fromlen);
	encode_path(xdr, args->pages, args->pathlen);
	encode_sattr(xdr, args->sattr, rpc_rqst_userns(req));
पूर्ण

/*
 * 2.2.17.  सूची_पढ़ोargs
 *
 *	काष्ठा सूची_पढ़ोargs अणु
 *		fhandle dir;
 *		nfscookie cookie;
 *		अचिन्हित count;
 *	पूर्ण;
 */
अटल व्योम encode_सूची_पढ़ोargs(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs_सूची_पढ़ोargs *args)
अणु
	__be32 *p;

	encode_fhandle(xdr, args->fh);

	p = xdr_reserve_space(xdr, 4 + 4);
	*p++ = cpu_to_be32(args->cookie);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम nfs2_xdr_enc_सूची_पढ़ोargs(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_सूची_पढ़ोargs *args = data;

	encode_सूची_पढ़ोargs(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, 0, args->count,
				NFS_सूची_पढ़ोres_sz - NFS_pagepad_sz);
पूर्ण

/*
 * NFSv2 XDR decode functions
 *
 * NFSv2 result types are defined in section 2.2 of RFC 1094:
 * "NFS: Network File System Protocol Specification".
 */

अटल पूर्णांक nfs2_xdr_dec_stat(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			     व्योम *__unused)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS_OK)
		जाओ out_शेष;
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण

अटल पूर्णांक nfs2_xdr_dec_attrstat(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *result)
अणु
	वापस decode_attrstat(xdr, result, शून्य, rpc_rqst_userns(req));
पूर्ण

अटल पूर्णांक nfs2_xdr_dec_diropres(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *result)
अणु
	वापस decode_diropres(xdr, result, rpc_rqst_userns(req));
पूर्ण

/*
 * 2.2.6.  पढ़ोlinkres
 *
 *	जोड़ पढ़ोlinkres चयन (stat status) अणु
 *	हाल NFS_OK:
 *		path data;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक nfs2_xdr_dec_पढ़ोlinkres(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr, व्योम *__unused)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_path(xdr);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 2.2.7.  पढ़ोres
 *
 *	जोड़ पढ़ोres चयन (stat status) अणु
 *	हाल NFS_OK:
 *		fattr attributes;
 *		nfsdata data;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक nfs2_xdr_dec_पढ़ोres(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nfs_pgio_res *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	result->op_status = status;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_fattr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	error = decode_nfsdata(xdr, result);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण

अटल पूर्णांक nfs2_xdr_dec_ग_लिखोres(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs_pgio_res *result = data;

	/* All NFSv2 ग_लिखोs are "file sync" ग_लिखोs */
	result->verf->committed = NFS_खाता_SYNC;
	वापस decode_attrstat(xdr, result->fattr, &result->op_status,
			rpc_rqst_userns(req));
पूर्ण

/**
 * nfs2_decode_dirent - Decode a single NFSv2 directory entry stored in
 *                      the local page cache.
 * @xdr: XDR stream where entry resides
 * @entry: buffer to fill in with entry data
 * @plus: boolean indicating whether this should be a सूची_पढ़ोplus entry
 *
 * Returns zero अगर successful, otherwise a negative त्रुटि_सं value is
 * वापसed.
 *
 * This function is not invoked during READसूची reply decoding, but
 * rather whenever an application invokes the getdents(2) प्रणाली call
 * on a directory alपढ़ोy in our cache.
 *
 * 2.2.17.  entry
 *
 *	काष्ठा entry अणु
 *		अचिन्हित	fileid;
 *		filename	name;
 *		nfscookie	cookie;
 *		entry		*nextentry;
 *	पूर्ण;
 */
पूर्णांक nfs2_decode_dirent(काष्ठा xdr_stream *xdr, काष्ठा nfs_entry *entry,
		       bool plus)
अणु
	__be32 *p;
	पूर्णांक error;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	अगर (*p++ == xdr_zero) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EAGAIN;
		अगर (*p++ == xdr_zero)
			वापस -EAGAIN;
		entry->eof = 1;
		वापस -EBADCOOKIE;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	entry->ino = be32_to_cpup(p);

	error = decode_filename_अंतरभूत(xdr, &entry->name, &entry->len);
	अगर (unlikely(error))
		वापस error;

	/*
	 * The type (size and byte order) of nfscookie isn't defined in
	 * RFC 1094.  This implementation assumes that it's an XDR uपूर्णांक32.
	 */
	entry->prev_cookie = entry->cookie;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	entry->cookie = be32_to_cpup(p);

	entry->d_type = DT_UNKNOWN;

	वापस 0;
पूर्ण

/*
 * 2.2.17.  सूची_पढ़ोres
 *
 *	जोड़ सूची_पढ़ोres चयन (stat status) अणु
 *	हाल NFS_OK:
 *		काष्ठा अणु
 *			entry *entries;
 *			bool eof;
 *		पूर्ण सूची_पढ़ोok;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 * Read the directory contents पूर्णांकo the page cache, but करोn't
 * touch them.  The actual decoding is करोne by nfs2_decode_dirent()
 * during subsequent nfs_सूची_पढ़ो() calls.
 */
अटल पूर्णांक decode_सूची_पढ़ोok(काष्ठा xdr_stream *xdr)
अणु
	वापस xdr_पढ़ो_pages(xdr, xdr->buf->page_len);
पूर्ण

अटल पूर्णांक nfs2_xdr_dec_सूची_पढ़ोres(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr, व्योम *__unused)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_सूची_पढ़ोok(xdr);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 2.2.18.  statfsres
 *
 *	जोड़ statfsres (stat status) अणु
 *	हाल NFS_OK:
 *		काष्ठा अणु
 *			अचिन्हित tsize;
 *			अचिन्हित bsize;
 *			अचिन्हित blocks;
 *			अचिन्हित bमुक्त;
 *			अचिन्हित bavail;
 *		पूर्ण info;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक decode_info(काष्ठा xdr_stream *xdr, काष्ठा nfs2_fsstat *result)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS_info_sz << 2);
	अगर (unlikely(!p))
		वापस -EIO;
	result->tsize  = be32_to_cpup(p++);
	result->bsize  = be32_to_cpup(p++);
	result->blocks = be32_to_cpup(p++);
	result->bमुक्त  = be32_to_cpup(p++);
	result->bavail = be32_to_cpup(p);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs2_xdr_dec_statfsres(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_stat(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS_OK)
		जाओ out_शेष;
	error = decode_info(xdr, result);
out:
	वापस error;
out_शेष:
	वापस nfs_stat_to_त्रुटि_सं(status);
पूर्ण


/*
 * We need to translate between nfs status वापस values and
 * the local त्रुटि_सं values which may not be the same.
 */
अटल स्थिर काष्ठा अणु
	पूर्णांक stat;
	पूर्णांक त्रुटि_सं;
पूर्ण nfs_errtbl[] = अणु
	अणु NFS_OK,		0		पूर्ण,
	अणु NFSERR_PERM,		-EPERM		पूर्ण,
	अणु NFSERR_NOENT,		-ENOENT		पूर्ण,
	अणु NFSERR_IO,		-त्रुटि_सं_NFSERR_IOपूर्ण,
	अणु NFSERR_NXIO,		-ENXIO		पूर्ण,
/*	अणु NFSERR_EAGAIN,	-EAGAIN		पूर्ण, */
	अणु NFSERR_ACCES,		-EACCES		पूर्ण,
	अणु NFSERR_EXIST,		-EEXIST		पूर्ण,
	अणु NFSERR_XDEV,		-EXDEV		पूर्ण,
	अणु NFSERR_NODEV,		-ENODEV		पूर्ण,
	अणु NFSERR_NOTसूची,	-ENOTसूची	पूर्ण,
	अणु NFSERR_ISसूची,		-EISसूची		पूर्ण,
	अणु NFSERR_INVAL,		-EINVAL		पूर्ण,
	अणु NFSERR_FBIG,		-EFBIG		पूर्ण,
	अणु NFSERR_NOSPC,		-ENOSPC		पूर्ण,
	अणु NFSERR_ROFS,		-EROFS		पूर्ण,
	अणु NFSERR_MLINK,		-EMLINK		पूर्ण,
	अणु NFSERR_NAMETOOLONG,	-ENAMETOOLONG	पूर्ण,
	अणु NFSERR_NOTEMPTY,	-ENOTEMPTY	पूर्ण,
	अणु NFSERR_DQUOT,		-EDQUOT		पूर्ण,
	अणु NFSERR_STALE,		-ESTALE		पूर्ण,
	अणु NFSERR_REMOTE,	-EREMOTE	पूर्ण,
#अगर_घोषित EWFLUSH
	अणु NFSERR_WFLUSH,	-EWFLUSH	पूर्ण,
#पूर्ण_अगर
	अणु NFSERR_BADHANDLE,	-EBADHANDLE	पूर्ण,
	अणु NFSERR_NOT_SYNC,	-ENOTSYNC	पूर्ण,
	अणु NFSERR_BAD_COOKIE,	-EBADCOOKIE	पूर्ण,
	अणु NFSERR_NOTSUPP,	-ENOTSUPP	पूर्ण,
	अणु NFSERR_TOOSMALL,	-ETOOSMALL	पूर्ण,
	अणु NFSERR_SERVERFAULT,	-EREMOTEIO	पूर्ण,
	अणु NFSERR_BADTYPE,	-EBADTYPE	पूर्ण,
	अणु NFSERR_JUKEBOX,	-EJUKEBOX	पूर्ण,
	अणु -1,			-EIO		पूर्ण
पूर्ण;

/**
 * nfs_stat_to_त्रुटि_सं - convert an NFS status code to a local त्रुटि_सं
 * @status: NFS status code to convert
 *
 * Returns a local त्रुटि_सं value, or -EIO अगर the NFS status code is
 * not recognized.  This function is used joपूर्णांकly by NFSv2 and NFSv3.
 */
अटल पूर्णांक nfs_stat_to_त्रुटि_सं(क्रमागत nfs_stat status)
अणु
	पूर्णांक i;

	क्रम (i = 0; nfs_errtbl[i].stat != -1; i++) अणु
		अगर (nfs_errtbl[i].stat == (पूर्णांक)status)
			वापस nfs_errtbl[i].त्रुटि_सं;
	पूर्ण
	dprपूर्णांकk("NFS: Unrecognized nfs status value: %u\n", status);
	वापस nfs_errtbl[i].त्रुटि_सं;
पूर्ण

#घोषणा PROC(proc, argtype, restype, समयr)				\
[NFSPROC_##proc] = अणु							\
	.p_proc	    =  NFSPROC_##proc,					\
	.p_encode   =  nfs2_xdr_enc_##argtype,				\
	.p_decode   =  nfs2_xdr_dec_##restype,				\
	.p_arglen   =  NFS_##argtype##_sz,				\
	.p_replen   =  NFS_##restype##_sz,				\
	.p_समयr    =  समयr,						\
	.p_statidx  =  NFSPROC_##proc,					\
	.p_name     =  #proc,						\
	पूर्ण
स्थिर काष्ठा rpc_procinfo nfs_procedures[] = अणु
	PROC(GETATTR,	fhandle,	attrstat,	1),
	PROC(SETATTR,	sattrargs,	attrstat,	0),
	PROC(LOOKUP,	diropargs,	diropres,	2),
	PROC(READLINK,	पढ़ोlinkargs,	पढ़ोlinkres,	3),
	PROC(READ,	पढ़ोargs,	पढ़ोres,	3),
	PROC(WRITE,	ग_लिखोargs,	ग_लिखोres,	4),
	PROC(CREATE,	createargs,	diropres,	0),
	PROC(REMOVE,	हटाओargs,	stat,		0),
	PROC(RENAME,	नामargs,	stat,		0),
	PROC(LINK,	linkargs,	stat,		0),
	PROC(SYMLINK,	symlinkargs,	stat,		0),
	PROC(MKसूची,	createargs,	diropres,	0),
	PROC(RMसूची,	diropargs,	stat,		0),
	PROC(READसूची,	सूची_पढ़ोargs,	सूची_पढ़ोres,	3),
	PROC(STATFS,	fhandle,	statfsres,	0),
पूर्ण;

अटल अचिन्हित पूर्णांक nfs_version2_counts[ARRAY_SIZE(nfs_procedures)];
स्थिर काष्ठा rpc_version nfs_version2 = अणु
	.number			= 2,
	.nrprocs		= ARRAY_SIZE(nfs_procedures),
	.procs			= nfs_procedures,
	.counts			= nfs_version2_counts,
पूर्ण;
