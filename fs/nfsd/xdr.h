<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* XDR types क्रम nfsd. This is मुख्यly a typing exercise. */

#अगर_अघोषित LINUX_NFSD_H
#घोषणा LINUX_NFSD_H

#समावेश <linux/vfs.h>
#समावेश "nfsd.h"
#समावेश "nfsfh.h"

काष्ठा nfsd_fhandle अणु
	काष्ठा svc_fh		fh;
पूर्ण;

काष्ठा nfsd_sattrargs अणु
	काष्ठा svc_fh		fh;
	काष्ठा iattr		attrs;
पूर्ण;

काष्ठा nfsd_diropargs अणु
	काष्ठा svc_fh		fh;
	अक्षर *			name;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा nfsd_पढ़ोargs अणु
	काष्ठा svc_fh		fh;
	__u32			offset;
	__u32			count;
पूर्ण;

काष्ठा nfsd_ग_लिखोargs अणु
	svc_fh			fh;
	__u32			offset;
	पूर्णांक			len;
	काष्ठा kvec		first;
पूर्ण;

काष्ठा nfsd_createargs अणु
	काष्ठा svc_fh		fh;
	अक्षर *			name;
	अचिन्हित पूर्णांक		len;
	काष्ठा iattr		attrs;
पूर्ण;

काष्ठा nfsd_नामargs अणु
	काष्ठा svc_fh		ffh;
	अक्षर *			fname;
	अचिन्हित पूर्णांक		flen;
	काष्ठा svc_fh		tfh;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
पूर्ण;

काष्ठा nfsd_linkargs अणु
	काष्ठा svc_fh		ffh;
	काष्ठा svc_fh		tfh;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
पूर्ण;

काष्ठा nfsd_symlinkargs अणु
	काष्ठा svc_fh		ffh;
	अक्षर *			fname;
	अचिन्हित पूर्णांक		flen;
	अक्षर *			tname;
	अचिन्हित पूर्णांक		tlen;
	काष्ठा iattr		attrs;
	काष्ठा kvec		first;
पूर्ण;

काष्ठा nfsd_सूची_पढ़ोargs अणु
	काष्ठा svc_fh		fh;
	__u32			cookie;
	__u32			count;
पूर्ण;

काष्ठा nfsd_stat अणु
	__be32			status;
पूर्ण;

काष्ठा nfsd_attrstat अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	काष्ठा kstat		stat;
पूर्ण;

काष्ठा nfsd_diropres  अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	काष्ठा kstat		stat;
पूर्ण;

काष्ठा nfsd_पढ़ोlinkres अणु
	__be32			status;
	पूर्णांक			len;
	काष्ठा page		*page;
पूर्ण;

काष्ठा nfsd_पढ़ोres अणु
	__be32			status;
	काष्ठा svc_fh		fh;
	अचिन्हित दीर्घ		count;
	काष्ठा kstat		stat;
	काष्ठा page		**pages;
पूर्ण;

काष्ठा nfsd_सूची_पढ़ोres अणु
	/* Components of the reply */
	__be32			status;

	पूर्णांक			count;

	/* Used to encode the reply's entry list */
	काष्ठा xdr_stream	xdr;
	काष्ठा xdr_buf		dirlist;
	काष्ठा सूची_पढ़ो_cd	common;
	अचिन्हित पूर्णांक		cookie_offset;
पूर्ण;

काष्ठा nfsd_statfsres अणु
	__be32			status;
	काष्ठा kstatfs		stats;
पूर्ण;

/*
 * Storage requirements क्रम XDR arguments and results.
 */
जोड़ nfsd_xdrstore अणु
	काष्ठा nfsd_sattrargs	sattr;
	काष्ठा nfsd_diropargs	dirop;
	काष्ठा nfsd_पढ़ोargs	पढ़ो;
	काष्ठा nfsd_ग_लिखोargs	ग_लिखो;
	काष्ठा nfsd_createargs	create;
	काष्ठा nfsd_नामargs	नाम;
	काष्ठा nfsd_linkargs	link;
	काष्ठा nfsd_symlinkargs	symlink;
	काष्ठा nfsd_सूची_पढ़ोargs	सूची_पढ़ो;
पूर्ण;

#घोषणा NFS2_SVC_XDRSIZE	माप(जोड़ nfsd_xdrstore)


पूर्णांक nfssvc_decode_fhandleargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_sattrargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_diropargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_पढ़ोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_ग_लिखोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_createargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_नामargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_linkargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_symlinkargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_decode_सूची_पढ़ोargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_statres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_attrstatres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_diropres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_पढ़ोlinkres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_पढ़ोres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_statfsres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक nfssvc_encode_सूची_पढ़ोres(काष्ठा svc_rqst *, __be32 *);

व्योम nfssvc_encode_nfscookie(काष्ठा nfsd_सूची_पढ़ोres *resp, u32 offset);
पूर्णांक nfssvc_encode_entry(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type);

व्योम nfssvc_release_attrstat(काष्ठा svc_rqst *rqstp);
व्योम nfssvc_release_diropres(काष्ठा svc_rqst *rqstp);
व्योम nfssvc_release_पढ़ोres(काष्ठा svc_rqst *rqstp);

/* Helper functions क्रम NFSv2 ACL code */
bool svcxdr_decode_fhandle(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp);
bool svcxdr_encode_stat(काष्ठा xdr_stream *xdr, __be32 status);
bool svcxdr_encode_fattr(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			 स्थिर काष्ठा svc_fh *fhp, स्थिर काष्ठा kstat *stat);

#पूर्ण_अगर /* LINUX_NFSD_H */
