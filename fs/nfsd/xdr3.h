<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * XDR types क्रम NFSv3 in nfsd.
 *
 * Copyright (C) 1996-1998, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_NFSD_XDR3_H
#घोषणा _LINUX_NFSD_XDR3_H

#समावेश "xdr.h"

काष्ठा nfsd3_sattrargs अणु
	काष्ठा svc_fh		fh;
	काष्ठा iattr		attrs;
	पूर्णांक			check_guard;
	समय64_t		guardसमय;
पूर्ण;

काष्ठा nfsd3_diropargs अणु
	काष्ठा svc_fh		fh;
	अक्षर *			name;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा nfsd3_accessargs अणु
	काष्ठा svc_fh		fh;
	__u32			access;
पूर्ण;

काष्ठा nfsd3_पढ़ोargs अणु
	काष्ठा svc_fh		fh;
	__u64			offset;
	__u32			count;
पूर्ण;

काष्ठा nfsd3_ग_लिखोargs अणु
	svc_fh			fh;
	__u64			offset;
	__u32			count;
	पूर्णांक			stable;
	__u32			len;
	काष्ठा kvec		first;
पूर्ण;

काष्ठा nfsd3_createargs अणु
	काष्ठा svc_fh		fh;
	अक्षर *			name;
	अचिन्हित पूर्णांक		len;
	पूर्णांक			createmode;
	काष्ठा iattr		attrs;
	__be32 *		verf;
पूर्ण;

काष्ठा nfsd3_mknodargs अणु
	काष्ठा svc_fh		fh;
	अक्षर *			name;
	अचिन्हित पूर्णांक		len;
	__u32			ftype;
	__u32			major, minor;
	काष्ठा iattr		attrs;
पूर्ण;

काष्ठा nfsd3_नामargs अणु
	काष्ठा svc_fh		ffh;
	अक्षर *			fname;
	अचिन्हित पूर्णांक		flen;
	काष्ठा svc_fh		tfh;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
पूर्ण;

काष्ठा nfsd3_linkargs अणु
	काष्ठा svc_fh		ffh;
	काष्ठा svc_fh		tfh;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
पूर्ण;

काष्ठा nfsd3_symlinkargs अणु
	काष्ठा svc_fh		ffh;
	अक्षर *			fname;
	अचिन्हित पूर्णांक		flen;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
	काष्ठा iattr		attrs;
	काष्ठा kvec		first;
पूर्ण;

काष्ठा nfsd3_सूची_पढ़ोargs अणु
	काष्ठा svc_fh		fh;
	__u64			cookie;
	__u32			count;
	__be32 *		verf;
पूर्ण;

काष्ठा nfsd3_commitargs अणु
	काष्ठा svc_fh		fh;
	__u64			offset;
	__u32			count;
पूर्ण;

काष्ठा nfsd3_getaclargs अणु
	काष्ठा svc_fh		fh;
	__u32			mask;
पूर्ण;

काष्ठा posix_acl;
काष्ठा nfsd3_setaclargs अणु
	काष्ठा svc_fh		fh;
	__u32			mask;
	काष्ठा posix_acl	*acl_access;
	काष्ठा posix_acl	*acl_शेष;
पूर्ण;

काष्ठा nfsd3_attrstat अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	काष्ठा kstat            stat;
पूर्ण;

/* LOOKUP, CREATE, MKसूची, SYMLINK, MKNOD */
काष्ठा nfsd3_diropres  अणु
	__be32			status;
	काष्ठा svc_fh		dirfh;
	काष्ठा svc_fh		fh;
पूर्ण;

काष्ठा nfsd3_accessres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	__u32			access;
	काष्ठा kstat		stat;
पूर्ण;

काष्ठा nfsd3_पढ़ोlinkres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	__u32			len;
	काष्ठा page		**pages;
पूर्ण;

काष्ठा nfsd3_पढ़ोres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	अचिन्हित दीर्घ		count;
	__u32			eof;
	काष्ठा page		**pages;
पूर्ण;

काष्ठा nfsd3_ग_लिखोres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	अचिन्हित दीर्घ		count;
	पूर्णांक			committed;
	__be32			verf[2];
पूर्ण;

काष्ठा nfsd3_नामres अणु
	__be32			status;
	काष्ठा svc_fh		ffh;
	काष्ठा svc_fh		tfh;
पूर्ण;

काष्ठा nfsd3_linkres अणु
	__be32			status;
	काष्ठा svc_fh		tfh;
	काष्ठा svc_fh		fh;
पूर्ण;

काष्ठा nfsd3_सूची_पढ़ोres अणु
	/* Components of the reply */
	__be32			status;
	काष्ठा svc_fh		fh;
	__be32			verf[2];

	/* Used to encode the reply's entry list */
	काष्ठा xdr_stream	xdr;
	काष्ठा xdr_buf		dirlist;
	काष्ठा svc_fh		scratch;
	काष्ठा सूची_पढ़ो_cd	common;
	अचिन्हित पूर्णांक		cookie_offset;
	काष्ठा svc_rqst *	rqstp;

पूर्ण;

काष्ठा nfsd3_fsstatres अणु
	__be32			status;
	काष्ठा kstatfs		stats;
	__u32			invarsec;
पूर्ण;

काष्ठा nfsd3_fsinक्रमes अणु
	__be32			status;
	__u32			f_rपंचांगax;
	__u32			f_rtpref;
	__u32			f_rपंचांगult;
	__u32			f_wपंचांगax;
	__u32			f_wtpref;
	__u32			f_wपंचांगult;
	__u32			f_dtpref;
	__u64			f_maxfilesize;
	__u32			f_properties;
पूर्ण;

काष्ठा nfsd3_pathconfres अणु
	__be32			status;
	__u32			p_link_max;
	__u32			p_name_max;
	__u32			p_no_trunc;
	__u32			p_chown_restricted;
	__u32			p_हाल_insensitive;
	__u32			p_हाल_preserving;
पूर्ण;

काष्ठा nfsd3_commitres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	__be32			verf[2];
पूर्ण;

काष्ठा nfsd3_getaclres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	पूर्णांक			mask;
	काष्ठा posix_acl	*acl_access;
	काष्ठा posix_acl	*acl_शेष;
	काष्ठा kstat		stat;
पूर्ण;

/* dummy type क्रम release */
काष्ठा nfsd3_fhandle_pair अणु
	__u32			dummy;
	काष्ठा svc_fh		fh1;
	काष्ठा svc_fh		fh2;
पूर्ण;

/*
 * Storage requirements क्रम XDR arguments and results.
 */
जोड़ nfsd3_xdrstore अणु
	काष्ठा nfsd3_sattrargs		sattrargs;
	काष्ठा nfsd3_diropargs		diropargs;
	काष्ठा nfsd3_पढ़ोargs		पढ़ोargs;
	काष्ठा nfsd3_ग_लिखोargs		ग_लिखोargs;
	काष्ठा nfsd3_createargs		createargs;
	काष्ठा nfsd3_नामargs		नामargs;
	काष्ठा nfsd3_linkargs		linkargs;
	काष्ठा nfsd3_symlinkargs	symlinkargs;
	काष्ठा nfsd3_सूची_पढ़ोargs	सूची_पढ़ोargs;
	काष्ठा nfsd3_diropres 		diropres;
	काष्ठा nfsd3_accessres		accessres;
	काष्ठा nfsd3_पढ़ोlinkres	पढ़ोlinkres;
	काष्ठा nfsd3_पढ़ोres		पढ़ोres;
	काष्ठा nfsd3_ग_लिखोres		ग_लिखोres;
	काष्ठा nfsd3_नामres		नामres;
	काष्ठा nfsd3_linkres		linkres;
	काष्ठा nfsd3_सूची_पढ़ोres		सूची_पढ़ोres;
	काष्ठा nfsd3_fsstatres		fsstatres;
	काष्ठा nfsd3_fsinक्रमes		fsinक्रमes;
	काष्ठा nfsd3_pathconfres	pathconfres;
	काष्ठा nfsd3_commitres		commitres;
	काष्ठा nfsd3_getaclres		getaclres;
पूर्ण;

#घोषणा NFS3_SVC_XDRSIZE		माप(जोड़ nfsd3_xdrstore)

पूर्णांक nfs3svc_decode_fhandleargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_sattrargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_diropargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_accessargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_पढ़ोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_ग_लिखोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_createargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_सूची_गढ़ोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_mknodargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_नामargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_linkargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_symlinkargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_सूची_पढ़ोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_सूची_पढ़ोplusargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_decode_commitargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_getattrres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_wccstat(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_lookupres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_accessres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_पढ़ोlinkres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_पढ़ोres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_ग_लिखोres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_createres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_नामres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_linkres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_सूची_पढ़ोres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_fsstatres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_fsinक्रमes(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_pathconfres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfs3svc_encode_commitres(काष्ठा svc_rqst *, __be32 *);

व्योम nfs3svc_release_fhandle(काष्ठा svc_rqst *);
व्योम nfs3svc_release_fhandle2(काष्ठा svc_rqst *);

व्योम nfs3svc_encode_cookie3(काष्ठा nfsd3_सूची_पढ़ोres *resp, u64 offset);
पूर्णांक nfs3svc_encode_entry3(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			  loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type);
पूर्णांक nfs3svc_encode_entryplus3(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			      loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type);
/* Helper functions क्रम NFSv3 ACL code */
bool svcxdr_decode_nfs_fh3(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp);
bool svcxdr_encode_nfsstat3(काष्ठा xdr_stream *xdr, __be32 status);
bool svcxdr_encode_post_op_attr(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा svc_fh *fhp);

#पूर्ण_अगर /* _LINUX_NFSD_XDR3_H */
