<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/nfs3xdr.c
 *
 * XDR functions to encode/decode NFSv3 RPC arguments and results.
 *
 * Copyright (C) 1996, 1997 Olaf Kirch
 */

#समावेश <linux/param.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfsacl.h>
#समावेश "nfstrace.h"
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_XDR

/* Mapping from NFS error code to "errno" error code. */
#घोषणा त्रुटि_सं_NFSERR_IO		EIO

/*
 * Declare the space requirements क्रम NFS arguments and replies as
 * number of 32bit-words
 */
#घोषणा NFS3_pagepad_sz		(1) /* Page padding */
#घोषणा NFS3_fhandle_sz		(1+16)
#घोषणा NFS3_fh_sz		(NFS3_fhandle_sz)	/* लघुhand */
#घोषणा NFS3_post_op_fh_sz	(1+NFS3_fh_sz)
#घोषणा NFS3_sattr_sz		(15)
#घोषणा NFS3_filename_sz	(1+(NFS3_MAXNAMLEN>>2))
#घोषणा NFS3_path_sz		(1+(NFS3_MAXPATHLEN>>2))
#घोषणा NFS3_fattr_sz		(21)
#घोषणा NFS3_cookieverf_sz	(NFS3_COOKIEVERFSIZE>>2)
#घोषणा NFS3_wcc_attr_sz	(6)
#घोषणा NFS3_pre_op_attr_sz	(1+NFS3_wcc_attr_sz)
#घोषणा NFS3_post_op_attr_sz	(1+NFS3_fattr_sz)
#घोषणा NFS3_wcc_data_sz	(NFS3_pre_op_attr_sz+NFS3_post_op_attr_sz)
#घोषणा NFS3_diropargs_sz	(NFS3_fh_sz+NFS3_filename_sz)

#घोषणा NFS3_getattrargs_sz	(NFS3_fh_sz)
#घोषणा NFS3_setattrargs_sz	(NFS3_fh_sz+NFS3_sattr_sz+3)
#घोषणा NFS3_lookupargs_sz	(NFS3_fh_sz+NFS3_filename_sz)
#घोषणा NFS3_accessargs_sz	(NFS3_fh_sz+1)
#घोषणा NFS3_पढ़ोlinkargs_sz	(NFS3_fh_sz)
#घोषणा NFS3_पढ़ोargs_sz	(NFS3_fh_sz+3)
#घोषणा NFS3_ग_लिखोargs_sz	(NFS3_fh_sz+5)
#घोषणा NFS3_createargs_sz	(NFS3_diropargs_sz+NFS3_sattr_sz)
#घोषणा NFS3_सूची_गढ़ोargs_sz	(NFS3_diropargs_sz+NFS3_sattr_sz)
#घोषणा NFS3_symlinkargs_sz	(NFS3_diropargs_sz+1+NFS3_sattr_sz)
#घोषणा NFS3_mknodargs_sz	(NFS3_diropargs_sz+2+NFS3_sattr_sz)
#घोषणा NFS3_हटाओargs_sz	(NFS3_fh_sz+NFS3_filename_sz)
#घोषणा NFS3_नामargs_sz	(NFS3_diropargs_sz+NFS3_diropargs_sz)
#घोषणा NFS3_linkargs_sz		(NFS3_fh_sz+NFS3_diropargs_sz)
#घोषणा NFS3_सूची_पढ़ोargs_sz	(NFS3_fh_sz+NFS3_cookieverf_sz+3)
#घोषणा NFS3_सूची_पढ़ोplusargs_sz	(NFS3_fh_sz+NFS3_cookieverf_sz+4)
#घोषणा NFS3_commitargs_sz	(NFS3_fh_sz+3)

#घोषणा NFS3_getattrres_sz	(1+NFS3_fattr_sz)
#घोषणा NFS3_setattrres_sz	(1+NFS3_wcc_data_sz)
#घोषणा NFS3_हटाओres_sz	(NFS3_setattrres_sz)
#घोषणा NFS3_lookupres_sz	(1+NFS3_fh_sz+(2 * NFS3_post_op_attr_sz))
#घोषणा NFS3_accessres_sz	(1+NFS3_post_op_attr_sz+1)
#घोषणा NFS3_पढ़ोlinkres_sz	(1+NFS3_post_op_attr_sz+1+NFS3_pagepad_sz)
#घोषणा NFS3_पढ़ोres_sz		(1+NFS3_post_op_attr_sz+3+NFS3_pagepad_sz)
#घोषणा NFS3_ग_लिखोres_sz	(1+NFS3_wcc_data_sz+4)
#घोषणा NFS3_createres_sz	(1+NFS3_post_op_fh_sz+NFS3_post_op_attr_sz+NFS3_wcc_data_sz)
#घोषणा NFS3_नामres_sz	(1+(2 * NFS3_wcc_data_sz))
#घोषणा NFS3_linkres_sz		(1+NFS3_post_op_attr_sz+NFS3_wcc_data_sz)
#घोषणा NFS3_सूची_पढ़ोres_sz	(1+NFS3_post_op_attr_sz+2+NFS3_pagepad_sz)
#घोषणा NFS3_fsstatres_sz	(1+NFS3_post_op_attr_sz+13)
#घोषणा NFS3_fsinक्रमes_sz	(1+NFS3_post_op_attr_sz+12)
#घोषणा NFS3_pathconfres_sz	(1+NFS3_post_op_attr_sz+6)
#घोषणा NFS3_commitres_sz	(1+NFS3_wcc_data_sz+2)

#घोषणा ACL3_getaclargs_sz	(NFS3_fh_sz+1)
#घोषणा ACL3_setaclargs_sz	(NFS3_fh_sz+1+ \
				XDR_QUADLEN(NFS_ACL_INLINE_बफ_मानE))
#घोषणा ACL3_getaclres_sz	(1+NFS3_post_op_attr_sz+1+ \
				XDR_QUADLEN(NFS_ACL_INLINE_बफ_मानE)+\
				NFS3_pagepad_sz)
#घोषणा ACL3_setaclres_sz	(1+NFS3_post_op_attr_sz)

अटल पूर्णांक nfs3_stat_to_त्रुटि_सं(क्रमागत nfs_stat);

/*
 * Map file type to S_IFMT bits
 */
अटल स्थिर umode_t nfs_type2fmt[] = अणु
	[NF3BAD] = 0,
	[NF3REG] = S_IFREG,
	[NF3सूची] = S_IFसूची,
	[NF3BLK] = S_IFBLK,
	[NF3CHR] = S_IFCHR,
	[NF3LNK] = S_IFLNK,
	[NF3SOCK] = S_IFSOCK,
	[NF3FIFO] = S_IFIFO,
पूर्ण;

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
 * Encode/decode NFSv3 basic data types
 *
 * Basic NFSv3 data types are defined in section 2.5 of RFC 1813:
 * "NFS Version 3 Protocol Specification".
 *
 * Not all basic data types have their own encoding and decoding
 * functions.  For run-समय efficiency, some data types are encoded
 * or decoded अंतरभूत.
 */

अटल व्योम encode_uपूर्णांक32(काष्ठा xdr_stream *xdr, u32 value)
अणु
	__be32 *p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(value);
पूर्ण

अटल पूर्णांक decode_uपूर्णांक32(काष्ठा xdr_stream *xdr, u32 *value)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	*value = be32_to_cpup(p);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_uपूर्णांक64(काष्ठा xdr_stream *xdr, u64 *value)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	xdr_decode_hyper(p, value);
	वापस 0;
पूर्ण

/*
 * fileid3
 *
 *	प्रकार uपूर्णांक64 fileid3;
 */
अटल __be32 *xdr_decode_fileid3(__be32 *p, u64 *fileid)
अणु
	वापस xdr_decode_hyper(p, fileid);
पूर्ण

अटल पूर्णांक decode_fileid3(काष्ठा xdr_stream *xdr, u64 *fileid)
अणु
	वापस decode_uपूर्णांक64(xdr, fileid);
पूर्ण

/*
 * filename3
 *
 *	प्रकार string filename3<>;
 */
अटल व्योम encode_filename3(काष्ठा xdr_stream *xdr,
			     स्थिर अक्षर *name, u32 length)
अणु
	__be32 *p;

	WARN_ON_ONCE(length > NFS3_MAXNAMLEN);
	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, name, length);
पूर्ण

अटल पूर्णांक decode_अंतरभूत_filename3(काष्ठा xdr_stream *xdr,
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
 * nfspath3
 *
 *	प्रकार string nfspath3<>;
 */
अटल व्योम encode_nfspath3(काष्ठा xdr_stream *xdr, काष्ठा page **pages,
			    स्थिर u32 length)
अणु
	encode_uपूर्णांक32(xdr, length);
	xdr_ग_लिखो_pages(xdr, pages, 0, length);
पूर्ण

अटल पूर्णांक decode_nfspath3(काष्ठा xdr_stream *xdr)
अणु
	u32 recvd, count;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	count = be32_to_cpup(p);
	अगर (unlikely(count >= xdr->buf->page_len || count > NFS3_MAXPATHLEN))
		जाओ out_nametooदीर्घ;
	recvd = xdr_पढ़ो_pages(xdr, count);
	अगर (unlikely(count > recvd))
		जाओ out_cheating;
	xdr_terminate_string(xdr->buf, count);
	वापस 0;

out_nametooदीर्घ:
	dprपूर्णांकk("NFS: returned pathname too long: %u\n", count);
	वापस -ENAMETOOLONG;
out_cheating:
	dprपूर्णांकk("NFS: server cheating in pathname result: "
		"count %u > recvd %u\n", count, recvd);
	वापस -EIO;
पूर्ण

/*
 * cookie3
 *
 *	प्रकार uपूर्णांक64 cookie3
 */
अटल __be32 *xdr_encode_cookie3(__be32 *p, u64 cookie)
अणु
	वापस xdr_encode_hyper(p, cookie);
पूर्ण

अटल पूर्णांक decode_cookie3(काष्ठा xdr_stream *xdr, u64 *cookie)
अणु
	वापस decode_uपूर्णांक64(xdr, cookie);
पूर्ण

/*
 * cookieverf3
 *
 *	प्रकार opaque cookieverf3[NFS3_COOKIEVERFSIZE];
 */
अटल __be32 *xdr_encode_cookieverf3(__be32 *p, स्थिर __be32 *verअगरier)
अणु
	स_नकल(p, verअगरier, NFS3_COOKIEVERFSIZE);
	वापस p + XDR_QUADLEN(NFS3_COOKIEVERFSIZE);
पूर्ण

अटल पूर्णांक decode_cookieverf3(काष्ठा xdr_stream *xdr, __be32 *verअगरier)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS3_COOKIEVERFSIZE);
	अगर (unlikely(!p))
		वापस -EIO;
	स_नकल(verअगरier, p, NFS3_COOKIEVERFSIZE);
	वापस 0;
पूर्ण

/*
 * createverf3
 *
 *	प्रकार opaque createverf3[NFS3_CREATEVERFSIZE];
 */
अटल व्योम encode_createverf3(काष्ठा xdr_stream *xdr, स्थिर __be32 *verअगरier)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS3_CREATEVERFSIZE);
	स_नकल(p, verअगरier, NFS3_CREATEVERFSIZE);
पूर्ण

अटल पूर्णांक decode_ग_लिखोverf3(काष्ठा xdr_stream *xdr, काष्ठा nfs_ग_लिखो_verअगरier *verअगरier)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS3_WRITEVERFSIZE);
	अगर (unlikely(!p))
		वापस -EIO;
	स_नकल(verअगरier->data, p, NFS3_WRITEVERFSIZE);
	वापस 0;
पूर्ण

/*
 * size3
 *
 *	प्रकार uपूर्णांक64 size3;
 */
अटल __be32 *xdr_decode_size3(__be32 *p, u64 *size)
अणु
	वापस xdr_decode_hyper(p, size);
पूर्ण

/*
 * nfsstat3
 *
 *	क्रमागत nfsstat3 अणु
 *		NFS3_OK = 0,
 *		...
 *	पूर्ण
 */
#घोषणा NFS3_OK		NFS_OK

अटल पूर्णांक decode_nfsstat3(काष्ठा xdr_stream *xdr, क्रमागत nfs_stat *status)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (unlikely(*p != cpu_to_be32(NFS3_OK)))
		जाओ out_status;
	*status = 0;
	वापस 0;
out_status:
	*status = be32_to_cpup(p);
	trace_nfs_xdr_status(xdr, (पूर्णांक)*status);
	वापस 0;
पूर्ण

/*
 * ftype3
 *
 *	क्रमागत ftype3 अणु
 *		NF3REG	= 1,
 *		NF3सूची	= 2,
 *		NF3BLK	= 3,
 *		NF3CHR	= 4,
 *		NF3LNK	= 5,
 *		NF3SOCK	= 6,
 *		NF3FIFO	= 7
 *	पूर्ण;
 */
अटल व्योम encode_ftype3(काष्ठा xdr_stream *xdr, स्थिर u32 type)
अणु
	encode_uपूर्णांक32(xdr, type);
पूर्ण

अटल __be32 *xdr_decode_ftype3(__be32 *p, umode_t *mode)
अणु
	u32 type;

	type = be32_to_cpup(p++);
	अगर (type > NF3FIFO)
		type = NF3NON;
	*mode = nfs_type2fmt[type];
	वापस p;
पूर्ण

/*
 * specdata3
 *
 *     काष्ठा specdata3 अणु
 *             uपूर्णांक32  specdata1;
 *             uपूर्णांक32  specdata2;
 *     पूर्ण;
 */
अटल व्योम encode_specdata3(काष्ठा xdr_stream *xdr, स्थिर dev_t rdev)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 8);
	*p++ = cpu_to_be32(MAJOR(rdev));
	*p = cpu_to_be32(MINOR(rdev));
पूर्ण

अटल __be32 *xdr_decode_specdata3(__be32 *p, dev_t *rdev)
अणु
	अचिन्हित पूर्णांक major, minor;

	major = be32_to_cpup(p++);
	minor = be32_to_cpup(p++);
	*rdev = MKDEV(major, minor);
	अगर (MAJOR(*rdev) != major || MINOR(*rdev) != minor)
		*rdev = 0;
	वापस p;
पूर्ण

/*
 * nfs_fh3
 *
 *	काष्ठा nfs_fh3 अणु
 *		opaque       data<NFS3_FHSIZE>;
 *	पूर्ण;
 */
अटल व्योम encode_nfs_fh3(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh)
अणु
	__be32 *p;

	WARN_ON_ONCE(fh->size > NFS3_FHSIZE);
	p = xdr_reserve_space(xdr, 4 + fh->size);
	xdr_encode_opaque(p, fh->data, fh->size);
पूर्ण

अटल पूर्णांक decode_nfs_fh3(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	u32 length;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	length = be32_to_cpup(p++);
	अगर (unlikely(length > NFS3_FHSIZE || length == 0))
		जाओ out_toobig;
	p = xdr_अंतरभूत_decode(xdr, length);
	अगर (unlikely(!p))
		वापस -EIO;
	fh->size = length;
	स_नकल(fh->data, p, length);
	वापस 0;
out_toobig:
	trace_nfs_xdr_bad_filehandle(xdr, NFSERR_BADHANDLE);
	वापस -E2BIG;
पूर्ण

अटल व्योम zero_nfs_fh3(काष्ठा nfs_fh *fh)
अणु
	स_रखो(fh, 0, माप(*fh));
पूर्ण

/*
 * nfsसमय3
 *
 *	काष्ठा nfsसमय3 अणु
 *		uपूर्णांक32	seconds;
 *		uपूर्णांक32	nseconds;
 *	पूर्ण;
 */
अटल __be32 *xdr_encode_nfsसमय3(__be32 *p, स्थिर काष्ठा बारpec64 *समयp)
अणु
	*p++ = cpu_to_be32((u32)समयp->tv_sec);
	*p++ = cpu_to_be32(समयp->tv_nsec);
	वापस p;
पूर्ण

अटल __be32 *xdr_decode_nfsसमय3(__be32 *p, काष्ठा बारpec64 *समयp)
अणु
	समयp->tv_sec = be32_to_cpup(p++);
	समयp->tv_nsec = be32_to_cpup(p++);
	वापस p;
पूर्ण

/*
 * sattr3
 *
 *	क्रमागत समय_how अणु
 *		DONT_CHANGE		= 0,
 *		SET_TO_SERVER_TIME	= 1,
 *		SET_TO_CLIENT_TIME	= 2
 *	पूर्ण;
 *
 *	जोड़ set_mode3 चयन (bool set_it) अणु
 *	हाल TRUE:
 *		mode3	mode;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	जोड़ set_uid3 चयन (bool set_it) अणु
 *	हाल TRUE:
 *		uid3	uid;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	जोड़ set_gid3 चयन (bool set_it) अणु
 *	हाल TRUE:
 *		gid3	gid;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	जोड़ set_size3 चयन (bool set_it) अणु
 *	हाल TRUE:
 *		size3	size;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	जोड़ set_aसमय चयन (समय_how set_it) अणु
 *	हाल SET_TO_CLIENT_TIME:
 *		nfsसमय3	aसमय;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	जोड़ set_mसमय चयन (समय_how set_it) अणु
 *	हाल SET_TO_CLIENT_TIME:
 *		nfsसमय3  mसमय;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा sattr3 अणु
 *		set_mode3	mode;
 *		set_uid3	uid;
 *		set_gid3	gid;
 *		set_size3	size;
 *		set_aसमय	aसमय;
 *		set_mसमय	mसमय;
 *	पूर्ण;
 */
अटल व्योम encode_sattr3(काष्ठा xdr_stream *xdr, स्थिर काष्ठा iattr *attr,
		काष्ठा user_namespace *userns)
अणु
	u32 nbytes;
	__be32 *p;

	/*
	 * In order to make only a single xdr_reserve_space() call,
	 * pre-compute the total number of bytes to be reserved.
	 * Six boolean values, one क्रम each set_foo field, are always
	 * present in the encoded result, so start there.
	 */
	nbytes = 6 * 4;
	अगर (attr->ia_valid & ATTR_MODE)
		nbytes += 4;
	अगर (attr->ia_valid & ATTR_UID)
		nbytes += 4;
	अगर (attr->ia_valid & ATTR_GID)
		nbytes += 4;
	अगर (attr->ia_valid & ATTR_SIZE)
		nbytes += 8;
	अगर (attr->ia_valid & ATTR_ATIME_SET)
		nbytes += 8;
	अगर (attr->ia_valid & ATTR_MTIME_SET)
		nbytes += 8;
	p = xdr_reserve_space(xdr, nbytes);

	अगर (attr->ia_valid & ATTR_MODE) अणु
		*p++ = xdr_one;
		*p++ = cpu_to_be32(attr->ia_mode & S_IALLUGO);
	पूर्ण अन्यथा
		*p++ = xdr_zero;

	अगर (attr->ia_valid & ATTR_UID) अणु
		*p++ = xdr_one;
		*p++ = cpu_to_be32(from_kuid_munged(userns, attr->ia_uid));
	पूर्ण अन्यथा
		*p++ = xdr_zero;

	अगर (attr->ia_valid & ATTR_GID) अणु
		*p++ = xdr_one;
		*p++ = cpu_to_be32(from_kgid_munged(userns, attr->ia_gid));
	पूर्ण अन्यथा
		*p++ = xdr_zero;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		*p++ = xdr_one;
		p = xdr_encode_hyper(p, (u64)attr->ia_size);
	पूर्ण अन्यथा
		*p++ = xdr_zero;

	अगर (attr->ia_valid & ATTR_ATIME_SET) अणु
		*p++ = xdr_two;
		p = xdr_encode_nfsसमय3(p, &attr->ia_aसमय);
	पूर्ण अन्यथा अगर (attr->ia_valid & ATTR_ATIME) अणु
		*p++ = xdr_one;
	पूर्ण अन्यथा
		*p++ = xdr_zero;

	अगर (attr->ia_valid & ATTR_MTIME_SET) अणु
		*p++ = xdr_two;
		xdr_encode_nfsसमय3(p, &attr->ia_mसमय);
	पूर्ण अन्यथा अगर (attr->ia_valid & ATTR_MTIME) अणु
		*p = xdr_one;
	पूर्ण अन्यथा
		*p = xdr_zero;
पूर्ण

/*
 * fattr3
 *
 *	काष्ठा fattr3 अणु
 *		ftype3		type;
 *		mode3		mode;
 *		uपूर्णांक32		nlink;
 *		uid3		uid;
 *		gid3		gid;
 *		size3		size;
 *		size3		used;
 *		specdata3	rdev;
 *		uपूर्णांक64		fsid;
 *		fileid3		fileid;
 *		nfsसमय3	aसमय;
 *		nfsसमय3	mसमय;
 *		nfsसमय3	स_समय;
 *	पूर्ण;
 */
अटल पूर्णांक decode_fattr3(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा user_namespace *userns)
अणु
	umode_t भ_शेषe;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS3_fattr_sz << 2);
	अगर (unlikely(!p))
		वापस -EIO;

	p = xdr_decode_ftype3(p, &भ_शेषe);

	fattr->mode = (be32_to_cpup(p++) & ~S_IFMT) | भ_शेषe;
	fattr->nlink = be32_to_cpup(p++);
	fattr->uid = make_kuid(userns, be32_to_cpup(p++));
	अगर (!uid_valid(fattr->uid))
		जाओ out_uid;
	fattr->gid = make_kgid(userns, be32_to_cpup(p++));
	अगर (!gid_valid(fattr->gid))
		जाओ out_gid;

	p = xdr_decode_size3(p, &fattr->size);
	p = xdr_decode_size3(p, &fattr->du.nfs3.used);
	p = xdr_decode_specdata3(p, &fattr->rdev);

	p = xdr_decode_hyper(p, &fattr->fsid.major);
	fattr->fsid.minor = 0;

	p = xdr_decode_fileid3(p, &fattr->fileid);
	p = xdr_decode_nfsसमय3(p, &fattr->aसमय);
	p = xdr_decode_nfsसमय3(p, &fattr->mसमय);
	xdr_decode_nfsसमय3(p, &fattr->स_समय);
	fattr->change_attr = nfs_बारpec_to_change_attr(&fattr->स_समय);

	fattr->valid |= NFS_ATTR_FATTR_V3;
	वापस 0;
out_uid:
	dprपूर्णांकk("NFS: returned invalid uid\n");
	वापस -EINVAL;
out_gid:
	dprपूर्णांकk("NFS: returned invalid gid\n");
	वापस -EINVAL;
पूर्ण

/*
 * post_op_attr
 *
 *	जोड़ post_op_attr चयन (bool attributes_follow) अणु
 *	हाल TRUE:
 *		fattr3	attributes;
 *	हाल FALSE:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक decode_post_op_attr(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा user_namespace *userns)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (*p != xdr_zero)
		वापस decode_fattr3(xdr, fattr, userns);
	वापस 0;
पूर्ण

/*
 * wcc_attr
 *	काष्ठा wcc_attr अणु
 *		size3		size;
 *		nfsसमय3	mसमय;
 *		nfsसमय3	स_समय;
 *	पूर्ण;
 */
अटल पूर्णांक decode_wcc_attr(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS3_wcc_attr_sz << 2);
	अगर (unlikely(!p))
		वापस -EIO;

	fattr->valid |= NFS_ATTR_FATTR_PRESIZE
		| NFS_ATTR_FATTR_PRECHANGE
		| NFS_ATTR_FATTR_PREMTIME
		| NFS_ATTR_FATTR_PRECTIME;

	p = xdr_decode_size3(p, &fattr->pre_size);
	p = xdr_decode_nfsसमय3(p, &fattr->pre_mसमय);
	xdr_decode_nfsसमय3(p, &fattr->pre_स_समय);
	fattr->pre_change_attr = nfs_बारpec_to_change_attr(&fattr->pre_स_समय);

	वापस 0;
पूर्ण

/*
 * pre_op_attr
 *	जोड़ pre_op_attr चयन (bool attributes_follow) अणु
 *	हाल TRUE:
 *		wcc_attr	attributes;
 *	हाल FALSE:
 *		व्योम;
 *	पूर्ण;
 *
 * wcc_data
 *
 *	काष्ठा wcc_data अणु
 *		pre_op_attr	beक्रमe;
 *		post_op_attr	after;
 *	पूर्ण;
 */
अटल पूर्णांक decode_pre_op_attr(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (*p != xdr_zero)
		वापस decode_wcc_attr(xdr, fattr);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_wcc_data(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा user_namespace *userns)
अणु
	पूर्णांक error;

	error = decode_pre_op_attr(xdr, fattr);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, fattr, userns);
out:
	वापस error;
पूर्ण

/*
 * post_op_fh3
 *
 *	जोड़ post_op_fh3 चयन (bool handle_follows) अणु
 *	हाल TRUE:
 *		nfs_fh3  handle;
 *	हाल FALSE:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक decode_post_op_fh3(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	__be32 *p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (*p != xdr_zero)
		वापस decode_nfs_fh3(xdr, fh);
	zero_nfs_fh3(fh);
	वापस 0;
पूर्ण

/*
 * diropargs3
 *
 *	काष्ठा diropargs3 अणु
 *		nfs_fh3		dir;
 *		filename3	name;
 *	पूर्ण;
 */
अटल व्योम encode_diropargs3(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh,
			      स्थिर अक्षर *name, u32 length)
अणु
	encode_nfs_fh3(xdr, fh);
	encode_filename3(xdr, name, length);
पूर्ण


/*
 * NFSv3 XDR encode functions
 *
 * NFSv3 argument types are defined in section 3.3 of RFC 1813:
 * "NFS Version 3 Protocol Specification".
 */

/*
 * 3.3.1  GETATTR3args
 *
 *	काष्ठा GETATTR3args अणु
 *		nfs_fh3  object;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_getattr3args(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_fh *fh = data;

	encode_nfs_fh3(xdr, fh);
पूर्ण

/*
 * 3.3.2  SETATTR3args
 *
 *	जोड़ sattrguard3 चयन (bool check) अणु
 *	हाल TRUE:
 *		nfsसमय3  obj_स_समय;
 *	हाल FALSE:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा SETATTR3args अणु
 *		nfs_fh3		object;
 *		sattr3		new_attributes;
 *		sattrguard3	guard;
 *	पूर्ण;
 */
अटल व्योम encode_sattrguard3(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs3_sattrargs *args)
अणु
	__be32 *p;

	अगर (args->guard) अणु
		p = xdr_reserve_space(xdr, 4 + 8);
		*p++ = xdr_one;
		xdr_encode_nfsसमय3(p, &args->guardसमय);
	पूर्ण अन्यथा अणु
		p = xdr_reserve_space(xdr, 4);
		*p = xdr_zero;
	पूर्ण
पूर्ण

अटल व्योम nfs3_xdr_enc_setattr3args(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_sattrargs *args = data;
	encode_nfs_fh3(xdr, args->fh);
	encode_sattr3(xdr, args->sattr, rpc_rqst_userns(req));
	encode_sattrguard3(xdr, args);
पूर्ण

/*
 * 3.3.3  LOOKUP3args
 *
 *	काष्ठा LOOKUP3args अणु
 *		diropargs3  what;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_lookup3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_diropargs *args = data;

	encode_diropargs3(xdr, args->fh, args->name, args->len);
पूर्ण

/*
 * 3.3.4  ACCESS3args
 *
 *	काष्ठा ACCESS3args अणु
 *		nfs_fh3		object;
 *		uपूर्णांक32		access;
 *	पूर्ण;
 */
अटल व्योम encode_access3args(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs3_accessargs *args)
अणु
	encode_nfs_fh3(xdr, args->fh);
	encode_uपूर्णांक32(xdr, args->access);
पूर्ण

अटल व्योम nfs3_xdr_enc_access3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_accessargs *args = data;

	encode_access3args(xdr, args);
पूर्ण

/*
 * 3.3.5  READLINK3args
 *
 *	काष्ठा READLINK3args अणु
 *		nfs_fh3	symlink;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_पढ़ोlink3args(काष्ठा rpc_rqst *req,
				       काष्ठा xdr_stream *xdr,
				       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_पढ़ोlinkargs *args = data;

	encode_nfs_fh3(xdr, args->fh);
	rpc_prepare_reply_pages(req, args->pages, args->pgbase, args->pglen,
				NFS3_पढ़ोlinkres_sz - NFS3_pagepad_sz);
पूर्ण

/*
 * 3.3.6  READ3args
 *
 *	काष्ठा READ3args अणु
 *		nfs_fh3		file;
 *		offset3		offset;
 *		count3		count;
 *	पूर्ण;
 */
अटल व्योम encode_पढ़ो3args(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs_pgio_args *args)
अणु
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + 4);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम nfs3_xdr_enc_पढ़ो3args(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;
	अचिन्हित पूर्णांक replen = args->replen ? args->replen :
					     NFS3_पढ़ोres_sz - NFS3_pagepad_sz;

	encode_पढ़ो3args(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->count, replen);
	req->rq_rcv_buf.flags |= XDRBUF_READ;
पूर्ण

/*
 * 3.3.7  WRITE3args
 *
 *	क्रमागत stable_how अणु
 *		UNSTABLE  = 0,
 *		DATA_SYNC = 1,
 *		खाता_SYNC = 2
 *	पूर्ण;
 *
 *	काष्ठा WRITE3args अणु
 *		nfs_fh3		file;
 *		offset3		offset;
 *		count3		count;
 *		stable_how	stable;
 *		opaque		data<>;
 *	पूर्ण;
 */
अटल व्योम encode_ग_लिखो3args(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs_pgio_args *args)
अणु
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + 4 + 4 + 4);
	p = xdr_encode_hyper(p, args->offset);
	*p++ = cpu_to_be32(args->count);
	*p++ = cpu_to_be32(args->stable);
	*p = cpu_to_be32(args->count);
	xdr_ग_लिखो_pages(xdr, args->pages, args->pgbase, args->count);
पूर्ण

अटल व्योम nfs3_xdr_enc_ग_लिखो3args(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;

	encode_ग_लिखो3args(xdr, args);
	xdr->buf->flags |= XDRBUF_WRITE;
पूर्ण

/*
 * 3.3.8  CREATE3args
 *
 *	क्रमागत createmode3 अणु
 *		UNCHECKED = 0,
 *		GUARDED   = 1,
 *		EXCLUSIVE = 2
 *	पूर्ण;
 *
 *	जोड़ createhow3 चयन (createmode3 mode) अणु
 *	हाल UNCHECKED:
 *	हाल GUARDED:
 *		sattr3       obj_attributes;
 *	हाल EXCLUSIVE:
 *		createverf3  verf;
 *	पूर्ण;
 *
 *	काष्ठा CREATE3args अणु
 *		diropargs3	where;
 *		createhow3	how;
 *	पूर्ण;
 */
अटल व्योम encode_createhow3(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs3_createargs *args,
			      काष्ठा user_namespace *userns)
अणु
	encode_uपूर्णांक32(xdr, args->createmode);
	चयन (args->createmode) अणु
	हाल NFS3_CREATE_UNCHECKED:
	हाल NFS3_CREATE_GUARDED:
		encode_sattr3(xdr, args->sattr, userns);
		अवरोध;
	हाल NFS3_CREATE_EXCLUSIVE:
		encode_createverf3(xdr, args->verअगरier);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम nfs3_xdr_enc_create3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_createargs *args = data;

	encode_diropargs3(xdr, args->fh, args->name, args->len);
	encode_createhow3(xdr, args, rpc_rqst_userns(req));
पूर्ण

/*
 * 3.3.9  MKसूची3args
 *
 *	काष्ठा MKसूची3args अणु
 *		diropargs3	where;
 *		sattr3		attributes;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_सूची_गढ़ो3args(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_सूची_गढ़ोargs *args = data;

	encode_diropargs3(xdr, args->fh, args->name, args->len);
	encode_sattr3(xdr, args->sattr, rpc_rqst_userns(req));
पूर्ण

/*
 * 3.3.10  SYMLINK3args
 *
 *	काष्ठा symlinkdata3 अणु
 *		sattr3		symlink_attributes;
 *		nfspath3	symlink_data;
 *	पूर्ण;
 *
 *	काष्ठा SYMLINK3args अणु
 *		diropargs3	where;
 *		symlinkdata3	symlink;
 *	पूर्ण;
 */
अटल व्योम encode_symlinkdata3(काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data,
				काष्ठा user_namespace *userns)
अणु
	स्थिर काष्ठा nfs3_symlinkargs *args = data;

	encode_sattr3(xdr, args->sattr, userns);
	encode_nfspath3(xdr, args->pages, args->pathlen);
पूर्ण

अटल व्योम nfs3_xdr_enc_symlink3args(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_symlinkargs *args = data;

	encode_diropargs3(xdr, args->fromfh, args->fromname, args->fromlen);
	encode_symlinkdata3(xdr, args, rpc_rqst_userns(req));
	xdr->buf->flags |= XDRBUF_WRITE;
पूर्ण

/*
 * 3.3.11  MKNOD3args
 *
 *	काष्ठा devicedata3 अणु
 *		sattr3		dev_attributes;
 *		specdata3	spec;
 *	पूर्ण;
 *
 *	जोड़ mknoddata3 चयन (ftype3 type) अणु
 *	हाल NF3CHR:
 *	हाल NF3BLK:
 *		devicedata3	device;
 *	हाल NF3SOCK:
 *	हाल NF3FIFO:
 *		sattr3		pipe_attributes;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा MKNOD3args अणु
 *		diropargs3	where;
 *		mknoddata3	what;
 *	पूर्ण;
 */
अटल व्योम encode_devicedata3(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs3_mknodargs *args,
			       काष्ठा user_namespace *userns)
अणु
	encode_sattr3(xdr, args->sattr, userns);
	encode_specdata3(xdr, args->rdev);
पूर्ण

अटल व्योम encode_mknoddata3(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs3_mknodargs *args,
			      काष्ठा user_namespace *userns)
अणु
	encode_ftype3(xdr, args->type);
	चयन (args->type) अणु
	हाल NF3CHR:
	हाल NF3BLK:
		encode_devicedata3(xdr, args, userns);
		अवरोध;
	हाल NF3SOCK:
	हाल NF3FIFO:
		encode_sattr3(xdr, args->sattr, userns);
		अवरोध;
	हाल NF3REG:
	हाल NF3सूची:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम nfs3_xdr_enc_mknod3args(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_mknodargs *args = data;

	encode_diropargs3(xdr, args->fh, args->name, args->len);
	encode_mknoddata3(xdr, args, rpc_rqst_userns(req));
पूर्ण

/*
 * 3.3.12  REMOVE3args
 *
 *	काष्ठा REMOVE3args अणु
 *		diropargs3  object;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_हटाओ3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_हटाओargs *args = data;

	encode_diropargs3(xdr, args->fh, args->name.name, args->name.len);
पूर्ण

/*
 * 3.3.14  RENAME3args
 *
 *	काष्ठा RENAME3args अणु
 *		diropargs3	from;
 *		diropargs3	to;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_नाम3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_नामargs *args = data;
	स्थिर काष्ठा qstr *old = args->old_name;
	स्थिर काष्ठा qstr *new = args->new_name;

	encode_diropargs3(xdr, args->old_dir, old->name, old->len);
	encode_diropargs3(xdr, args->new_dir, new->name, new->len);
पूर्ण

/*
 * 3.3.15  LINK3args
 *
 *	काष्ठा LINK3args अणु
 *		nfs_fh3		file;
 *		diropargs3	link;
 *	पूर्ण;
 */
अटल व्योम nfs3_xdr_enc_link3args(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_linkargs *args = data;

	encode_nfs_fh3(xdr, args->fromfh);
	encode_diropargs3(xdr, args->tofh, args->toname, args->tolen);
पूर्ण

/*
 * 3.3.16  READसूची3args
 *
 *	काष्ठा READसूची3args अणु
 *		nfs_fh3		dir;
 *		cookie3		cookie;
 *		cookieverf3	cookieverf;
 *		count3		count;
 *	पूर्ण;
 */
अटल व्योम encode_सूची_पढ़ो3args(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा nfs3_सूची_पढ़ोargs *args)
अणु
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + NFS3_COOKIEVERFSIZE + 4);
	p = xdr_encode_cookie3(p, args->cookie);
	p = xdr_encode_cookieverf3(p, args->verf);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम nfs3_xdr_enc_सूची_पढ़ो3args(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_सूची_पढ़ोargs *args = data;

	encode_सूची_पढ़ो3args(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, 0, args->count,
				NFS3_सूची_पढ़ोres_sz - NFS3_pagepad_sz);
पूर्ण

/*
 * 3.3.17  READसूचीPLUS3args
 *
 *	काष्ठा READसूचीPLUS3args अणु
 *		nfs_fh3		dir;
 *		cookie3		cookie;
 *		cookieverf3	cookieverf;
 *		count3		dircount;
 *		count3		maxcount;
 *	पूर्ण;
 */
अटल व्योम encode_सूची_पढ़ोplus3args(काष्ठा xdr_stream *xdr,
				    स्थिर काष्ठा nfs3_सूची_पढ़ोargs *args)
अणु
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + NFS3_COOKIEVERFSIZE + 4 + 4);
	p = xdr_encode_cookie3(p, args->cookie);
	p = xdr_encode_cookieverf3(p, args->verf);

	/*
	 * सूची_पढ़ोplus: need dircount + buffer size.
	 * We just make sure we make dircount big enough
	 */
	*p++ = cpu_to_be32(args->count >> 3);

	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम nfs3_xdr_enc_सूची_पढ़ोplus3args(काष्ठा rpc_rqst *req,
					  काष्ठा xdr_stream *xdr,
					  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_सूची_पढ़ोargs *args = data;

	encode_सूची_पढ़ोplus3args(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, 0, args->count,
				NFS3_सूची_पढ़ोres_sz - NFS3_pagepad_sz);
पूर्ण

/*
 * 3.3.21  COMMIT3args
 *
 *	काष्ठा COMMIT3args अणु
 *		nfs_fh3		file;
 *		offset3		offset;
 *		count3		count;
 *	पूर्ण;
 */
अटल व्योम encode_commit3args(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs_commitargs *args)
अणु
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + 4);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम nfs3_xdr_enc_commit3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_commitargs *args = data;

	encode_commit3args(xdr, args);
पूर्ण

#अगर_घोषित CONFIG_NFS_V3_ACL

अटल व्योम nfs3_xdr_enc_getacl3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_getaclargs *args = data;

	encode_nfs_fh3(xdr, args->fh);
	encode_uपूर्णांक32(xdr, args->mask);
	अगर (args->mask & (NFS_ACL | NFS_DFACL)) अणु
		rpc_prepare_reply_pages(req, args->pages, 0,
					NFSACL_MAXPAGES << PAGE_SHIFT,
					ACL3_getaclres_sz - NFS3_pagepad_sz);
		req->rq_rcv_buf.flags |= XDRBUF_SPARSE_PAGES;
	पूर्ण
पूर्ण

अटल व्योम nfs3_xdr_enc_setacl3args(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs3_setaclargs *args = data;
	अचिन्हित पूर्णांक base;
	पूर्णांक error;

	encode_nfs_fh3(xdr, NFS_FH(args->inode));
	encode_uपूर्णांक32(xdr, args->mask);

	base = req->rq_slen;
	अगर (args->npages != 0)
		xdr_ग_लिखो_pages(xdr, args->pages, 0, args->len);
	अन्यथा
		xdr_reserve_space(xdr, args->len);

	error = nfsacl_encode(xdr->buf, base, args->inode,
			    (args->mask & NFS_ACL) ?
			    args->acl_access : शून्य, 1, 0);
	/* FIXME: this is just broken */
	BUG_ON(error < 0);
	error = nfsacl_encode(xdr->buf, base + error, args->inode,
			    (args->mask & NFS_DFACL) ?
			    args->acl_शेष : शून्य, 1,
			    NFS_ACL_DEFAULT);
	BUG_ON(error < 0);
पूर्ण

#पूर्ण_अगर  /* CONFIG_NFS_V3_ACL */

/*
 * NFSv3 XDR decode functions
 *
 * NFSv3 result types are defined in section 3.3 of RFC 1813:
 * "NFS Version 3 Protocol Specification".
 */

/*
 * 3.3.1  GETATTR3res
 *
 *	काष्ठा GETATTR3resok अणु
 *		fattr3		obj_attributes;
 *	पूर्ण;
 *
 *	जोड़ GETATTR3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		GETATTR3resok  resok;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_getattr3res(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_fattr3(xdr, result, rpc_rqst_userns(req));
out:
	वापस error;
out_शेष:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.2  SETATTR3res
 *
 *	काष्ठा SETATTR3resok अणु
 *		wcc_data  obj_wcc;
 *	पूर्ण;
 *
 *	काष्ठा SETATTR3resfail अणु
 *		wcc_data  obj_wcc;
 *	पूर्ण;
 *
 *	जोड़ SETATTR3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		SETATTR3resok   resok;
 *	शेष:
 *		SETATTR3resfail resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_setattr3res(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.3  LOOKUP3res
 *
 *	काष्ठा LOOKUP3resok अणु
 *		nfs_fh3		object;
 *		post_op_attr	obj_attributes;
 *		post_op_attr	dir_attributes;
 *	पूर्ण;
 *
 *	काष्ठा LOOKUP3resfail अणु
 *		post_op_attr	dir_attributes;
 *	पूर्ण;
 *
 *	जोड़ LOOKUP3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		LOOKUP3resok	resok;
 *	शेष:
 *		LOOKUP3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_lookup3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा user_namespace *userns = rpc_rqst_userns(req);
	काष्ठा nfs3_diropres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_nfs_fh3(xdr, result->fh);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->dir_attr, userns);
out:
	वापस error;
out_शेष:
	error = decode_post_op_attr(xdr, result->dir_attr, userns);
	अगर (unlikely(error))
		जाओ out;
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.4  ACCESS3res
 *
 *	काष्ठा ACCESS3resok अणु
 *		post_op_attr	obj_attributes;
 *		uपूर्णांक32		access;
 *	पूर्ण;
 *
 *	काष्ठा ACCESS3resfail अणु
 *		post_op_attr	obj_attributes;
 *	पूर्ण;
 *
 *	जोड़ ACCESS3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		ACCESS3resok	resok;
 *	शेष:
 *		ACCESS3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_access3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs3_accessres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_uपूर्णांक32(xdr, &result->access);
out:
	वापस error;
out_शेष:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.5  READLINK3res
 *
 *	काष्ठा READLINK3resok अणु
 *		post_op_attr	symlink_attributes;
 *		nfspath3	data;
 *	पूर्ण;
 *
 *	काष्ठा READLINK3resfail अणु
 *		post_op_attr	symlink_attributes;
 *	पूर्ण;
 *
 *	जोड़ READLINK3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		READLINK3resok	resok;
 *	शेष:
 *		READLINK3resfail resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_पढ़ोlink3res(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_nfspath3(xdr);
out:
	वापस error;
out_शेष:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.6  READ3res
 *
 *	काष्ठा READ3resok अणु
 *		post_op_attr	file_attributes;
 *		count3		count;
 *		bool		eof;
 *		opaque		data<>;
 *	पूर्ण;
 *
 *	काष्ठा READ3resfail अणु
 *		post_op_attr	file_attributes;
 *	पूर्ण;
 *
 *	जोड़ READ3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		READ3resok	resok;
 *	शेष:
 *		READ3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_पढ़ो3resok(काष्ठा xdr_stream *xdr,
			     काष्ठा nfs_pgio_res *result)
अणु
	u32 eof, count, ocount, recvd;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4 + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	count = be32_to_cpup(p++);
	eof = be32_to_cpup(p++);
	ocount = be32_to_cpup(p++);
	अगर (unlikely(ocount != count))
		जाओ out_mismatch;
	recvd = xdr_पढ़ो_pages(xdr, count);
	अगर (unlikely(count > recvd))
		जाओ out_cheating;
out:
	result->eof = eof;
	result->count = count;
	वापस count;
out_mismatch:
	dprपूर्णांकk("NFS: READ count doesn't match length of opaque: "
		"count %u != ocount %u\n", count, ocount);
	वापस -EIO;
out_cheating:
	dprपूर्णांकk("NFS: server cheating in read result: "
		"count %u > recvd %u\n", count, recvd);
	count = recvd;
	eof = 0;
	जाओ out;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_पढ़ो3res(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs_pgio_res *result = data;
	अचिन्हित पूर्णांक pos;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	pos = xdr_stream_pos(xdr);
	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	result->op_status = status;
	अगर (status != NFS3_OK)
		जाओ out_status;
	result->replen = 3 + ((xdr_stream_pos(xdr) - pos) >> 2);
	error = decode_पढ़ो3resok(xdr, result);
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.7  WRITE3res
 *
 *	क्रमागत stable_how अणु
 *		UNSTABLE  = 0,
 *		DATA_SYNC = 1,
 *		खाता_SYNC = 2
 *	पूर्ण;
 *
 *	काष्ठा WRITE3resok अणु
 *		wcc_data	file_wcc;
 *		count3		count;
 *		stable_how	committed;
 *		ग_लिखोverf3	verf;
 *	पूर्ण;
 *
 *	काष्ठा WRITE3resfail अणु
 *		wcc_data	file_wcc;
 *	पूर्ण;
 *
 *	जोड़ WRITE3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		WRITE3resok	resok;
 *	शेष:
 *		WRITE3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_ग_लिखो3resok(काष्ठा xdr_stream *xdr,
			      काष्ठा nfs_pgio_res *result)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	result->count = be32_to_cpup(p++);
	result->verf->committed = be32_to_cpup(p++);
	अगर (unlikely(result->verf->committed > NFS_खाता_SYNC))
		जाओ out_badvalue;
	अगर (decode_ग_लिखोverf3(xdr, &result->verf->verअगरier))
		वापस -EIO;
	वापस result->count;
out_badvalue:
	dprपूर्णांकk("NFS: bad stable_how value: %u\n", result->verf->committed);
	वापस -EIO;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_ग_लिखो3res(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  व्योम *data)
अणु
	काष्ठा nfs_pgio_res *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	result->op_status = status;
	अगर (status != NFS3_OK)
		जाओ out_status;
	error = decode_ग_लिखो3resok(xdr, result);
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.8  CREATE3res
 *
 *	काष्ठा CREATE3resok अणु
 *		post_op_fh3	obj;
 *		post_op_attr	obj_attributes;
 *		wcc_data	dir_wcc;
 *	पूर्ण;
 *
 *	काष्ठा CREATE3resfail अणु
 *		wcc_data	dir_wcc;
 *	पूर्ण;
 *
 *	जोड़ CREATE3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		CREATE3resok	resok;
 *	शेष:
 *		CREATE3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_create3resok(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs3_diropres *result,
			       काष्ठा user_namespace *userns)
अणु
	पूर्णांक error;

	error = decode_post_op_fh3(xdr, result->fh);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	/* The server isn't required to वापस a file handle.
	 * If it didn't, क्रमce the client to perक्रमm a LOOKUP
	 * to determine the correct file handle and attribute
	 * values क्रम the new object. */
	अगर (result->fh->size == 0)
		result->fattr->valid = 0;
	error = decode_wcc_data(xdr, result->dir_attr, userns);
out:
	वापस error;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_create3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा user_namespace *userns = rpc_rqst_userns(req);
	काष्ठा nfs3_diropres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_create3resok(xdr, result, userns);
out:
	वापस error;
out_शेष:
	error = decode_wcc_data(xdr, result->dir_attr, userns);
	अगर (unlikely(error))
		जाओ out;
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.12  REMOVE3res
 *
 *	काष्ठा REMOVE3resok अणु
 *		wcc_data    dir_wcc;
 *	पूर्ण;
 *
 *	काष्ठा REMOVE3resfail अणु
 *		wcc_data    dir_wcc;
 *	पूर्ण;
 *
 *	जोड़ REMOVE3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		REMOVE3resok   resok;
 *	शेष:
 *		REMOVE3resfail resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_हटाओ3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs_हटाओres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->dir_attr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.14  RENAME3res
 *
 *	काष्ठा RENAME3resok अणु
 *		wcc_data	fromdir_wcc;
 *		wcc_data	todir_wcc;
 *	पूर्ण;
 *
 *	काष्ठा RENAME3resfail अणु
 *		wcc_data	fromdir_wcc;
 *		wcc_data	todir_wcc;
 *	पूर्ण;
 *
 *	जोड़ RENAME3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		RENAME3resok   resok;
 *	शेष:
 *		RENAME3resfail resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_नाम3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा user_namespace *userns = rpc_rqst_userns(req);
	काष्ठा nfs_नामres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->old_fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->new_fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.15  LINK3res
 *
 *	काष्ठा LINK3resok अणु
 *		post_op_attr	file_attributes;
 *		wcc_data	linkdir_wcc;
 *	पूर्ण;
 *
 *	काष्ठा LINK3resfail अणु
 *		post_op_attr	file_attributes;
 *		wcc_data	linkdir_wcc;
 *	पूर्ण;
 *
 *	जोड़ LINK3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		LINK3resok	resok;
 *	शेष:
 *		LINK3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_link3res(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा user_namespace *userns = rpc_rqst_userns(req);
	काष्ठा nfs3_linkres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->dir_attr, userns);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/**
 * nfs3_decode_dirent - Decode a single NFSv3 directory entry stored in
 *			the local page cache
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
 * 3.3.16  entry3
 *
 *	काष्ठा entry3 अणु
 *		fileid3		fileid;
 *		filename3	name;
 *		cookie3		cookie;
 *		fhandle3	filehandle;
 *		post_op_attr3	attributes;
 *		entry3		*nextentry;
 *	पूर्ण;
 *
 * 3.3.17  entryplus3
 *	काष्ठा entryplus3 अणु
 *		fileid3		fileid;
 *		filename3	name;
 *		cookie3		cookie;
 *		post_op_attr	name_attributes;
 *		post_op_fh3	name_handle;
 *		entryplus3	*nextentry;
 *	पूर्ण;
 */
पूर्णांक nfs3_decode_dirent(काष्ठा xdr_stream *xdr, काष्ठा nfs_entry *entry,
		       bool plus)
अणु
	काष्ठा user_namespace *userns = rpc_userns(entry->server->client);
	काष्ठा nfs_entry old = *entry;
	__be32 *p;
	पूर्णांक error;
	u64 new_cookie;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	अगर (*p == xdr_zero) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EAGAIN;
		अगर (*p == xdr_zero)
			वापस -EAGAIN;
		entry->eof = 1;
		वापस -EBADCOOKIE;
	पूर्ण

	error = decode_fileid3(xdr, &entry->ino);
	अगर (unlikely(error))
		वापस error;

	error = decode_अंतरभूत_filename3(xdr, &entry->name, &entry->len);
	अगर (unlikely(error))
		वापस error;

	error = decode_cookie3(xdr, &new_cookie);
	अगर (unlikely(error))
		वापस error;

	entry->d_type = DT_UNKNOWN;

	अगर (plus) अणु
		entry->fattr->valid = 0;
		error = decode_post_op_attr(xdr, entry->fattr, userns);
		अगर (unlikely(error))
			वापस error;
		अगर (entry->fattr->valid & NFS_ATTR_FATTR_V3)
			entry->d_type = nfs_umode_to_dtype(entry->fattr->mode);

		अगर (entry->fattr->fileid != entry->ino) अणु
			entry->fattr->mounted_on_fileid = entry->ino;
			entry->fattr->valid |= NFS_ATTR_FATTR_MOUNTED_ON_खाताID;
		पूर्ण

		/* In fact, a post_op_fh3: */
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EAGAIN;
		अगर (*p != xdr_zero) अणु
			error = decode_nfs_fh3(xdr, entry->fh);
			अगर (unlikely(error)) अणु
				अगर (error == -E2BIG)
					जाओ out_truncated;
				वापस error;
			पूर्ण
		पूर्ण अन्यथा
			zero_nfs_fh3(entry->fh);
	पूर्ण

	entry->prev_cookie = entry->cookie;
	entry->cookie = new_cookie;

	वापस 0;

out_truncated:
	dprपूर्णांकk("NFS: directory entry contains invalid file handle\n");
	*entry = old;
	वापस -EAGAIN;
पूर्ण

/*
 * 3.3.16  READसूची3res
 *
 *	काष्ठा dirlist3 अणु
 *		entry3		*entries;
 *		bool		eof;
 *	पूर्ण;
 *
 *	काष्ठा READसूची3resok अणु
 *		post_op_attr	dir_attributes;
 *		cookieverf3	cookieverf;
 *		dirlist3	reply;
 *	पूर्ण;
 *
 *	काष्ठा READसूची3resfail अणु
 *		post_op_attr	dir_attributes;
 *	पूर्ण;
 *
 *	जोड़ READसूची3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		READसूची3resok	resok;
 *	शेष:
 *		READसूची3resfail	resfail;
 *	पूर्ण;
 *
 * Read the directory contents पूर्णांकo the page cache, but otherwise
 * करोn't touch them.  The actual decoding is करोne by nfs3_decode_entry()
 * during subsequent nfs_सूची_पढ़ो() calls.
 */
अटल पूर्णांक decode_dirlist3(काष्ठा xdr_stream *xdr)
अणु
	वापस xdr_पढ़ो_pages(xdr, xdr->buf->page_len);
पूर्ण

अटल पूर्णांक decode_सूची_पढ़ो3resok(काष्ठा xdr_stream *xdr,
				काष्ठा nfs3_सूची_पढ़ोres *result,
				काष्ठा user_namespace *userns)
अणु
	पूर्णांक error;

	error = decode_post_op_attr(xdr, result->dir_attr, userns);
	अगर (unlikely(error))
		जाओ out;
	/* XXX: करो we need to check अगर result->verf != शून्य ? */
	error = decode_cookieverf3(xdr, result->verf);
	अगर (unlikely(error))
		जाओ out;
	error = decode_dirlist3(xdr);
out:
	वापस error;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_सूची_पढ़ो3res(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs3_सूची_पढ़ोres *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_सूची_पढ़ो3resok(xdr, result, rpc_rqst_userns(req));
out:
	वापस error;
out_शेष:
	error = decode_post_op_attr(xdr, result->dir_attr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.18  FSSTAT3res
 *
 *	काष्ठा FSSTAT3resok अणु
 *		post_op_attr	obj_attributes;
 *		size3		tbytes;
 *		size3		fbytes;
 *		size3		abytes;
 *		size3		tfiles;
 *		size3		ffiles;
 *		size3		afiles;
 *		uपूर्णांक32		invarsec;
 *	पूर्ण;
 *
 *	काष्ठा FSSTAT3resfail अणु
 *		post_op_attr	obj_attributes;
 *	पूर्ण;
 *
 *	जोड़ FSSTAT3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		FSSTAT3resok	resok;
 *	शेष:
 *		FSSTAT3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_fsstat3resok(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs_fsstat *result)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 8 * 6 + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	p = xdr_decode_size3(p, &result->tbytes);
	p = xdr_decode_size3(p, &result->fbytes);
	p = xdr_decode_size3(p, &result->abytes);
	p = xdr_decode_size3(p, &result->tfiles);
	p = xdr_decode_size3(p, &result->ffiles);
	xdr_decode_size3(p, &result->afiles);
	/* ignore invarsec */
	वापस 0;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_fsstat3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs_fsstat *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
	error = decode_fsstat3resok(xdr, result);
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.19  FSINFO3res
 *
 *	काष्ठा FSINFO3resok अणु
 *		post_op_attr	obj_attributes;
 *		uपूर्णांक32		rपंचांगax;
 *		uपूर्णांक32		rtpref;
 *		uपूर्णांक32		rपंचांगult;
 *		uपूर्णांक32		wपंचांगax;
 *		uपूर्णांक32		wtpref;
 *		uपूर्णांक32		wपंचांगult;
 *		uपूर्णांक32		dtpref;
 *		size3		maxfilesize;
 *		nfsसमय3	समय_delta;
 *		uपूर्णांक32		properties;
 *	पूर्ण;
 *
 *	काष्ठा FSINFO3resfail अणु
 *		post_op_attr	obj_attributes;
 *	पूर्ण;
 *
 *	जोड़ FSINFO3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		FSINFO3resok	resok;
 *	शेष:
 *		FSINFO3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_fsinfo3resok(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs_fsinfo *result)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 * 7 + 8 + 8 + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	result->rपंचांगax  = be32_to_cpup(p++);
	result->rtpref = be32_to_cpup(p++);
	result->rपंचांगult = be32_to_cpup(p++);
	result->wपंचांगax  = be32_to_cpup(p++);
	result->wtpref = be32_to_cpup(p++);
	result->wपंचांगult = be32_to_cpup(p++);
	result->dtpref = be32_to_cpup(p++);
	p = xdr_decode_size3(p, &result->maxfilesize);
	xdr_decode_nfsसमय3(p, &result->समय_delta);

	/* ignore properties */
	result->lease_समय = 0;
	result->change_attr_type = NFS4_CHANGE_TYPE_IS_TIME_METADATA;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_fsinfo3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs_fsinfo *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
	error = decode_fsinfo3resok(xdr, result);
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.20  PATHCONF3res
 *
 *	काष्ठा PATHCONF3resok अणु
 *		post_op_attr	obj_attributes;
 *		uपूर्णांक32		linkmax;
 *		uपूर्णांक32		name_max;
 *		bool		no_trunc;
 *		bool		chown_restricted;
 *		bool		हाल_insensitive;
 *		bool		हाल_preserving;
 *	पूर्ण;
 *
 *	काष्ठा PATHCONF3resfail अणु
 *		post_op_attr	obj_attributes;
 *	पूर्ण;
 *
 *	जोड़ PATHCONF3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		PATHCONF3resok	resok;
 *	शेष:
 *		PATHCONF3resfail resfail;
 *	पूर्ण;
 */
अटल पूर्णांक decode_pathconf3resok(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs_pathconf *result)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 * 6);
	अगर (unlikely(!p))
		वापस -EIO;
	result->max_link = be32_to_cpup(p++);
	result->max_namelen = be32_to_cpup(p);
	/* ignore reमुख्यing fields */
	वापस 0;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_pathconf3res(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs_pathconf *result = data;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_status;
	error = decode_pathconf3resok(xdr, result);
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

/*
 * 3.3.21  COMMIT3res
 *
 *	काष्ठा COMMIT3resok अणु
 *		wcc_data	file_wcc;
 *		ग_लिखोverf3	verf;
 *	पूर्ण;
 *
 *	काष्ठा COMMIT3resfail अणु
 *		wcc_data	file_wcc;
 *	पूर्ण;
 *
 *	जोड़ COMMIT3res चयन (nfsstat3 status) अणु
 *	हाल NFS3_OK:
 *		COMMIT3resok	resok;
 *	शेष:
 *		COMMIT3resfail	resfail;
 *	पूर्ण;
 */
अटल पूर्णांक nfs3_xdr_dec_commit3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs_commitres *result = data;
	काष्ठा nfs_ग_लिखोverf *verf = result->verf;
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	error = decode_wcc_data(xdr, result->fattr, rpc_rqst_userns(req));
	अगर (unlikely(error))
		जाओ out;
	result->op_status = status;
	अगर (status != NFS3_OK)
		जाओ out_status;
	error = decode_ग_लिखोverf3(xdr, &verf->verअगरier);
	अगर (!error)
		verf->committed = NFS_खाता_SYNC;
out:
	वापस error;
out_status:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

#अगर_घोषित CONFIG_NFS_V3_ACL

अटल अंतरभूत पूर्णांक decode_getacl3resok(काष्ठा xdr_stream *xdr,
				      काष्ठा nfs3_getaclres *result,
				      काष्ठा user_namespace *userns)
अणु
	काष्ठा posix_acl **acl;
	अचिन्हित पूर्णांक *aclcnt;
	माप_प्रकार hdrlen;
	पूर्णांक error;

	error = decode_post_op_attr(xdr, result->fattr, userns);
	अगर (unlikely(error))
		जाओ out;
	error = decode_uपूर्णांक32(xdr, &result->mask);
	अगर (unlikely(error))
		जाओ out;
	error = -EINVAL;
	अगर (result->mask & ~(NFS_ACL|NFS_ACLCNT|NFS_DFACL|NFS_DFACLCNT))
		जाओ out;

	hdrlen = xdr_stream_pos(xdr);

	acl = शून्य;
	अगर (result->mask & NFS_ACL)
		acl = &result->acl_access;
	aclcnt = शून्य;
	अगर (result->mask & NFS_ACLCNT)
		aclcnt = &result->acl_access_count;
	error = nfsacl_decode(xdr->buf, hdrlen, aclcnt, acl);
	अगर (unlikely(error <= 0))
		जाओ out;

	acl = शून्य;
	अगर (result->mask & NFS_DFACL)
		acl = &result->acl_शेष;
	aclcnt = शून्य;
	अगर (result->mask & NFS_DFACLCNT)
		aclcnt = &result->acl_शेष_count;
	error = nfsacl_decode(xdr->buf, hdrlen + error, aclcnt, acl);
	अगर (unlikely(error <= 0))
		वापस error;
	error = 0;
out:
	वापस error;
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_getacl3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_getacl3resok(xdr, result, rpc_rqst_userns(req));
out:
	वापस error;
out_शेष:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

अटल पूर्णांक nfs3_xdr_dec_setacl3res(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   व्योम *result)
अणु
	क्रमागत nfs_stat status;
	पूर्णांक error;

	error = decode_nfsstat3(xdr, &status);
	अगर (unlikely(error))
		जाओ out;
	अगर (status != NFS3_OK)
		जाओ out_शेष;
	error = decode_post_op_attr(xdr, result, rpc_rqst_userns(req));
out:
	वापस error;
out_शेष:
	वापस nfs3_stat_to_त्रुटि_सं(status);
पूर्ण

#पूर्ण_अगर  /* CONFIG_NFS_V3_ACL */


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
 * nfs3_stat_to_त्रुटि_सं - convert an NFS status code to a local त्रुटि_सं
 * @status: NFS status code to convert
 *
 * Returns a local त्रुटि_सं value, or -EIO अगर the NFS status code is
 * not recognized.  This function is used joपूर्णांकly by NFSv2 and NFSv3.
 */
अटल पूर्णांक nfs3_stat_to_त्रुटि_सं(क्रमागत nfs_stat status)
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
[NFS3PROC_##proc] = अणु							\
	.p_proc      = NFS3PROC_##proc,					\
	.p_encode    = nfs3_xdr_enc_##argtype##3args,			\
	.p_decode    = nfs3_xdr_dec_##restype##3res,			\
	.p_arglen    = NFS3_##argtype##args_sz,				\
	.p_replen    = NFS3_##restype##res_sz,				\
	.p_समयr     = समयr,						\
	.p_statidx   = NFS3PROC_##proc,					\
	.p_name      = #proc,						\
	पूर्ण

स्थिर काष्ठा rpc_procinfo nfs3_procedures[] = अणु
	PROC(GETATTR,		getattr,	getattr,	1),
	PROC(SETATTR,		setattr,	setattr,	0),
	PROC(LOOKUP,		lookup,		lookup,		2),
	PROC(ACCESS,		access,		access,		1),
	PROC(READLINK,		पढ़ोlink,	पढ़ोlink,	3),
	PROC(READ,		पढ़ो,		पढ़ो,		3),
	PROC(WRITE,		ग_लिखो,		ग_लिखो,		4),
	PROC(CREATE,		create,		create,		0),
	PROC(MKसूची,		सूची_गढ़ो,		create,		0),
	PROC(SYMLINK,		symlink,	create,		0),
	PROC(MKNOD,		mknod,		create,		0),
	PROC(REMOVE,		हटाओ,		हटाओ,		0),
	PROC(RMसूची,		lookup,		setattr,	0),
	PROC(RENAME,		नाम,		नाम,		0),
	PROC(LINK,		link,		link,		0),
	PROC(READसूची,		सूची_पढ़ो,	सूची_पढ़ो,	3),
	PROC(READसूचीPLUS,	सूची_पढ़ोplus,	सूची_पढ़ो,	3),
	PROC(FSSTAT,		getattr,	fsstat,		0),
	PROC(FSINFO,		getattr,	fsinfo,		0),
	PROC(PATHCONF,		getattr,	pathconf,	0),
	PROC(COMMIT,		commit,		commit,		5),
पूर्ण;

अटल अचिन्हित पूर्णांक nfs_version3_counts[ARRAY_SIZE(nfs3_procedures)];
स्थिर काष्ठा rpc_version nfs_version3 = अणु
	.number			= 3,
	.nrprocs		= ARRAY_SIZE(nfs3_procedures),
	.procs			= nfs3_procedures,
	.counts			= nfs_version3_counts,
पूर्ण;

#अगर_घोषित CONFIG_NFS_V3_ACL
अटल स्थिर काष्ठा rpc_procinfo nfs3_acl_procedures[] = अणु
	[ACLPROC3_GETACL] = अणु
		.p_proc = ACLPROC3_GETACL,
		.p_encode = nfs3_xdr_enc_getacl3args,
		.p_decode = nfs3_xdr_dec_getacl3res,
		.p_arglen = ACL3_getaclargs_sz,
		.p_replen = ACL3_getaclres_sz,
		.p_समयr = 1,
		.p_name = "GETACL",
	पूर्ण,
	[ACLPROC3_SETACL] = अणु
		.p_proc = ACLPROC3_SETACL,
		.p_encode = nfs3_xdr_enc_setacl3args,
		.p_decode = nfs3_xdr_dec_setacl3res,
		.p_arglen = ACL3_setaclargs_sz,
		.p_replen = ACL3_setaclres_sz,
		.p_समयr = 0,
		.p_name = "SETACL",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfs3_acl_counts[ARRAY_SIZE(nfs3_acl_procedures)];
स्थिर काष्ठा rpc_version nfsacl_version3 = अणु
	.number			= 3,
	.nrprocs		= ARRAY_SIZE(nfs3_acl_procedures),
	.procs			= nfs3_acl_procedures,
	.counts			= nfs3_acl_counts,
पूर्ण;
#पूर्ण_अगर  /* CONFIG_NFS_V3_ACL */
