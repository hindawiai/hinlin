<शैली गुरु>
/*
 *  Server-side XDR क्रम NFSv4
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
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

#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/statfs.h>
#समावेश <linux/utsname.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/xattr.h>
#समावेश <uapi/linux/xattr.h>

#समावेश "idmap.h"
#समावेश "acl.h"
#समावेश "xdr4.h"
#समावेश "vfs.h"
#समावेश "state.h"
#समावेश "cache.h"
#समावेश "netns.h"
#समावेश "pnfs.h"
#समावेश "filecache.h"

#समावेश "trace.h"

#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
#समावेश <linux/security.h>
#पूर्ण_अगर


#घोषणा NFSDDBG_FACILITY		NFSDDBG_XDR

स्थिर u32 nfsd_suppattrs[3][3] = अणु
	अणुNFSD4_SUPPORTED_ATTRS_WORD0,
	 NFSD4_SUPPORTED_ATTRS_WORD1,
	 NFSD4_SUPPORTED_ATTRS_WORD2पूर्ण,

	अणुNFSD4_1_SUPPORTED_ATTRS_WORD0,
	 NFSD4_1_SUPPORTED_ATTRS_WORD1,
	 NFSD4_1_SUPPORTED_ATTRS_WORD2पूर्ण,

	अणुNFSD4_1_SUPPORTED_ATTRS_WORD0,
	 NFSD4_1_SUPPORTED_ATTRS_WORD1,
	 NFSD4_2_SUPPORTED_ATTRS_WORD2पूर्ण,
पूर्ण;

/*
 * As per referral draft, the fsid क्रम a referral MUST be dअगरferent from the fsid of the containing
 * directory in order to indicate to the client that a fileप्रणाली boundary is present
 * We use a fixed fsid क्रम a referral
 */
#घोषणा NFS4_REFERRAL_FSID_MAJOR	0x8000000ULL
#घोषणा NFS4_REFERRAL_FSID_MINOR	0x8000000ULL

अटल __be32
check_filename(अक्षर *str, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (len == 0)
		वापस nfserr_inval;
	अगर (len > NFS4_MAXNAMLEN)
		वापस nfserr_nametooदीर्घ;
	अगर (isकरोtent(str, len))
		वापस nfserr_badname;
	क्रम (i = 0; i < len; i++)
		अगर (str[i] == '/')
			वापस nfserr_badname;
	वापस 0;
पूर्ण

अटल पूर्णांक zero_clientid(clientid_t *clid)
अणु
	वापस (clid->cl_boot == 0) && (clid->cl_id == 0);
पूर्ण

/**
 * svcxdr_पंचांगpalloc - allocate memory to be मुक्तd after compound processing
 * @argp: NFSv4 compound argument काष्ठाure
 * @len: length of buffer to allocate
 *
 * Allocates a buffer of size @len to be मुक्तd when processing the compound
 * operation described in @argp finishes.
 */
अटल व्योम *
svcxdr_पंचांगpalloc(काष्ठा nfsd4_compoundargs *argp, u32 len)
अणु
	काष्ठा svcxdr_पंचांगpbuf *tb;

	tb = kदो_स्मृति(माप(*tb) + len, GFP_KERNEL);
	अगर (!tb)
		वापस शून्य;
	tb->next = argp->to_मुक्त;
	argp->to_मुक्त = tb;
	वापस tb->buf;
पूर्ण

/*
 * For xdr strings that need to be passed to other kernel api's
 * as null-terminated strings.
 *
 * Note null-terminating in place usually isn't safe since the
 * buffer might end on a page boundary.
 */
अटल अक्षर *
svcxdr_dupstr(काष्ठा nfsd4_compoundargs *argp, व्योम *buf, u32 len)
अणु
	अक्षर *p = svcxdr_पंचांगpalloc(argp, len + 1);

	अगर (!p)
		वापस शून्य;
	स_नकल(p, buf, len);
	p[len] = '\0';
	वापस p;
पूर्ण

अटल व्योम *
svcxdr_savemem(काष्ठा nfsd4_compoundargs *argp, __be32 *p, u32 len)
अणु
	__be32 *पंचांगp;

	/*
	 * The location of the decoded data item is stable,
	 * so @p is OK to use. This is the common हाल.
	 */
	अगर (p != argp->xdr->scratch.iov_base)
		वापस p;

	पंचांगp = svcxdr_पंचांगpalloc(argp, len);
	अगर (!पंचांगp)
		वापस शून्य;
	स_नकल(पंचांगp, p, len);
	वापस पंचांगp;
पूर्ण

/*
 * NFSv4 basic data type decoders
 */

/*
 * This helper handles variable-length opaques which beदीर्घ to protocol
 * elements that this implementation करोes not support.
 */
अटल __be32
nfsd4_decode_ignored_string(काष्ठा nfsd4_compoundargs *argp, u32 maxlen)
अणु
	u32 len;

	अगर (xdr_stream_decode_u32(argp->xdr, &len) < 0)
		वापस nfserr_bad_xdr;
	अगर (maxlen && len > maxlen)
		वापस nfserr_bad_xdr;
	अगर (!xdr_अंतरभूत_decode(argp->xdr, len))
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_opaque(काष्ठा nfsd4_compoundargs *argp, काष्ठा xdr_netobj *o)
अणु
	__be32 *p;
	u32 len;

	अगर (xdr_stream_decode_u32(argp->xdr, &len) < 0)
		वापस nfserr_bad_xdr;
	अगर (len == 0 || len > NFS4_OPAQUE_LIMIT)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, len);
	अगर (!p)
		वापस nfserr_bad_xdr;
	o->data = svcxdr_savemem(argp, p, len);
	अगर (!o->data)
		वापस nfserr_jukebox;
	o->len = len;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_component4(काष्ठा nfsd4_compoundargs *argp, अक्षर **namp, u32 *lenp)
अणु
	__be32 *p, status;

	अगर (xdr_stream_decode_u32(argp->xdr, lenp) < 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, *lenp);
	अगर (!p)
		वापस nfserr_bad_xdr;
	status = check_filename((अक्षर *)p, *lenp);
	अगर (status)
		वापस status;
	*namp = svcxdr_savemem(argp, p, *lenp);
	अगर (!*namp)
		वापस nfserr_jukebox;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_nfsसमय4(काष्ठा nfsd4_compoundargs *argp, काष्ठा बारpec64 *tv)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, XDR_UNIT * 3);
	अगर (!p)
		वापस nfserr_bad_xdr;
	p = xdr_decode_hyper(p, &tv->tv_sec);
	tv->tv_nsec = be32_to_cpup(p++);
	अगर (tv->tv_nsec >= (u32)1000000000)
		वापस nfserr_inval;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_verअगरier4(काष्ठा nfsd4_compoundargs *argp, nfs4_verअगरier *verf)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, NFS4_VERIFIER_SIZE);
	अगर (!p)
		वापस nfserr_bad_xdr;
	स_नकल(verf->data, p, माप(verf->data));
	वापस nfs_ok;
पूर्ण

/**
 * nfsd4_decode_biपंचांगap4 - Decode an NFSv4 biपंचांगap4
 * @argp: NFSv4 compound argument काष्ठाure
 * @bmval: poपूर्णांकer to an array of u32's to decode पूर्णांकo
 * @bmlen: size of the @bmval array
 *
 * The server needs to वापस nfs_ok rather than nfserr_bad_xdr when
 * encountering biपंचांगaps containing bits it करोes not recognize. This
 * includes bits in biपंचांगap words past WORDn, where WORDn is the last
 * biपंचांगap WORD the implementation currently supports. Thus we are
 * careful here to simply ignore bits in biपंचांगap words that this
 * implementation has yet to support explicitly.
 *
 * Return values:
 *   %nfs_ok: @bmval populated successfully
 *   %nfserr_bad_xdr: the encoded biपंचांगap was invalid
 */
अटल __be32
nfsd4_decode_biपंचांगap4(काष्ठा nfsd4_compoundargs *argp, u32 *bmval, u32 bmlen)
अणु
	u32 i, count;
	__be32 *p;

	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;
	/* request sanity */
	अगर (count > 1000)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, count << 2);
	अगर (!p)
		वापस nfserr_bad_xdr;
	i = 0;
	जबतक (i < count)
		bmval[i++] = be32_to_cpup(p++);
	जबतक (i < bmlen)
		bmval[i++] = 0;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_nfsace4(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfs4_ace *ace)
अणु
	__be32 *p, status;
	u32 length;

	अगर (xdr_stream_decode_u32(argp->xdr, &ace->type) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &ace->flag) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &ace->access_mask) < 0)
		वापस nfserr_bad_xdr;

	अगर (xdr_stream_decode_u32(argp->xdr, &length) < 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, length);
	अगर (!p)
		वापस nfserr_bad_xdr;
	ace->whotype = nfs4_acl_get_whotype((अक्षर *)p, length);
	अगर (ace->whotype != NFS4_ACL_WHO_NAMED)
		status = nfs_ok;
	अन्यथा अगर (ace->flag & NFS4_ACE_IDENTIFIER_GROUP)
		status = nfsd_map_name_to_gid(argp->rqstp,
				(अक्षर *)p, length, &ace->who_gid);
	अन्यथा
		status = nfsd_map_name_to_uid(argp->rqstp,
				(अक्षर *)p, length, &ace->who_uid);

	वापस status;
पूर्ण

/* A counted array of nfsace4's */
अटल noअंतरभूत __be32
nfsd4_decode_acl(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfs4_acl **acl)
अणु
	काष्ठा nfs4_ace *ace;
	__be32 status;
	u32 count;

	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;

	अगर (count > xdr_stream_reमुख्यing(argp->xdr) / 20)
		/*
		 * Even with 4-byte names there wouldn't be
		 * space क्रम that many aces; something fishy is
		 * going on:
		 */
		वापस nfserr_fbig;

	*acl = svcxdr_पंचांगpalloc(argp, nfs4_acl_bytes(count));
	अगर (*acl == शून्य)
		वापस nfserr_jukebox;

	(*acl)->naces = count;
	क्रम (ace = (*acl)->aces; ace < (*acl)->aces + count; ace++) अणु
		status = nfsd4_decode_nfsace4(argp, ace);
		अगर (status)
			वापस status;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल noअंतरभूत __be32
nfsd4_decode_security_label(काष्ठा nfsd4_compoundargs *argp,
			    काष्ठा xdr_netobj *label)
अणु
	u32 lfs, pi, length;
	__be32 *p;

	अगर (xdr_stream_decode_u32(argp->xdr, &lfs) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &pi) < 0)
		वापस nfserr_bad_xdr;

	अगर (xdr_stream_decode_u32(argp->xdr, &length) < 0)
		वापस nfserr_bad_xdr;
	अगर (length > NFS4_MAXLABELLEN)
		वापस nfserr_badlabel;
	p = xdr_अंतरभूत_decode(argp->xdr, length);
	अगर (!p)
		वापस nfserr_bad_xdr;
	label->len = length;
	label->data = svcxdr_dupstr(argp, p, length);
	अगर (!label->data)
		वापस nfserr_jukebox;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_fattr4(काष्ठा nfsd4_compoundargs *argp, u32 *bmval, u32 bmlen,
		    काष्ठा iattr *iattr, काष्ठा nfs4_acl **acl,
		    काष्ठा xdr_netobj *label, पूर्णांक *umask)
अणु
	अचिन्हित पूर्णांक starting_pos;
	u32 attrlist4_count;
	__be32 *p, status;

	iattr->ia_valid = 0;
	status = nfsd4_decode_biपंचांगap4(argp, bmval, bmlen);
	अगर (status)
		वापस nfserr_bad_xdr;

	अगर (bmval[0] & ~NFSD_WRITEABLE_ATTRS_WORD0
	    || bmval[1] & ~NFSD_WRITEABLE_ATTRS_WORD1
	    || bmval[2] & ~NFSD_WRITEABLE_ATTRS_WORD2) अणु
		अगर (nfsd_attrs_supported(argp->minorversion, bmval))
			वापस nfserr_inval;
		वापस nfserr_attrnotsupp;
	पूर्ण

	अगर (xdr_stream_decode_u32(argp->xdr, &attrlist4_count) < 0)
		वापस nfserr_bad_xdr;
	starting_pos = xdr_stream_pos(argp->xdr);

	अगर (bmval[0] & FATTR4_WORD0_SIZE) अणु
		u64 size;

		अगर (xdr_stream_decode_u64(argp->xdr, &size) < 0)
			वापस nfserr_bad_xdr;
		iattr->ia_size = size;
		iattr->ia_valid |= ATTR_SIZE;
	पूर्ण
	अगर (bmval[0] & FATTR4_WORD0_ACL) अणु
		status = nfsd4_decode_acl(argp, acl);
		अगर (status)
			वापस status;
	पूर्ण अन्यथा
		*acl = शून्य;
	अगर (bmval[1] & FATTR4_WORD1_MODE) अणु
		u32 mode;

		अगर (xdr_stream_decode_u32(argp->xdr, &mode) < 0)
			वापस nfserr_bad_xdr;
		iattr->ia_mode = mode;
		iattr->ia_mode &= (S_IFMT | S_IALLUGO);
		iattr->ia_valid |= ATTR_MODE;
	पूर्ण
	अगर (bmval[1] & FATTR4_WORD1_OWNER) अणु
		u32 length;

		अगर (xdr_stream_decode_u32(argp->xdr, &length) < 0)
			वापस nfserr_bad_xdr;
		p = xdr_अंतरभूत_decode(argp->xdr, length);
		अगर (!p)
			वापस nfserr_bad_xdr;
		status = nfsd_map_name_to_uid(argp->rqstp, (अक्षर *)p, length,
					      &iattr->ia_uid);
		अगर (status)
			वापस status;
		iattr->ia_valid |= ATTR_UID;
	पूर्ण
	अगर (bmval[1] & FATTR4_WORD1_OWNER_GROUP) अणु
		u32 length;

		अगर (xdr_stream_decode_u32(argp->xdr, &length) < 0)
			वापस nfserr_bad_xdr;
		p = xdr_अंतरभूत_decode(argp->xdr, length);
		अगर (!p)
			वापस nfserr_bad_xdr;
		status = nfsd_map_name_to_gid(argp->rqstp, (अक्षर *)p, length,
					      &iattr->ia_gid);
		अगर (status)
			वापस status;
		iattr->ia_valid |= ATTR_GID;
	पूर्ण
	अगर (bmval[1] & FATTR4_WORD1_TIME_ACCESS_SET) अणु
		u32 set_it;

		अगर (xdr_stream_decode_u32(argp->xdr, &set_it) < 0)
			वापस nfserr_bad_xdr;
		चयन (set_it) अणु
		हाल NFS4_SET_TO_CLIENT_TIME:
			status = nfsd4_decode_nfsसमय4(argp, &iattr->ia_aसमय);
			अगर (status)
				वापस status;
			iattr->ia_valid |= (ATTR_ATIME | ATTR_ATIME_SET);
			अवरोध;
		हाल NFS4_SET_TO_SERVER_TIME:
			iattr->ia_valid |= ATTR_ATIME;
			अवरोध;
		शेष:
			वापस nfserr_bad_xdr;
		पूर्ण
	पूर्ण
	अगर (bmval[1] & FATTR4_WORD1_TIME_MODIFY_SET) अणु
		u32 set_it;

		अगर (xdr_stream_decode_u32(argp->xdr, &set_it) < 0)
			वापस nfserr_bad_xdr;
		चयन (set_it) अणु
		हाल NFS4_SET_TO_CLIENT_TIME:
			status = nfsd4_decode_nfsसमय4(argp, &iattr->ia_mसमय);
			अगर (status)
				वापस status;
			iattr->ia_valid |= (ATTR_MTIME | ATTR_MTIME_SET);
			अवरोध;
		हाल NFS4_SET_TO_SERVER_TIME:
			iattr->ia_valid |= ATTR_MTIME;
			अवरोध;
		शेष:
			वापस nfserr_bad_xdr;
		पूर्ण
	पूर्ण
	label->len = 0;
	अगर (IS_ENABLED(CONFIG_NFSD_V4_SECURITY_LABEL) &&
	    bmval[2] & FATTR4_WORD2_SECURITY_LABEL) अणु
		status = nfsd4_decode_security_label(argp, label);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (bmval[2] & FATTR4_WORD2_MODE_UMASK) अणु
		u32 mode, mask;

		अगर (!umask)
			वापस nfserr_bad_xdr;
		अगर (xdr_stream_decode_u32(argp->xdr, &mode) < 0)
			वापस nfserr_bad_xdr;
		iattr->ia_mode = mode & (S_IFMT | S_IALLUGO);
		अगर (xdr_stream_decode_u32(argp->xdr, &mask) < 0)
			वापस nfserr_bad_xdr;
		*umask = mask & S_IRWXUGO;
		iattr->ia_valid |= ATTR_MODE;
	पूर्ण

	/* request sanity: did attrlist4 contain the expected number of words? */
	अगर (attrlist4_count != xdr_stream_pos(argp->xdr) - starting_pos)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_stateid4(काष्ठा nfsd4_compoundargs *argp, stateid_t *sid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, NFS4_STATEID_SIZE);
	अगर (!p)
		वापस nfserr_bad_xdr;
	sid->si_generation = be32_to_cpup(p++);
	स_नकल(&sid->si_opaque, p, माप(sid->si_opaque));
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_clientid4(काष्ठा nfsd4_compoundargs *argp, clientid_t *clientid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, माप(__be64));
	अगर (!p)
		वापस nfserr_bad_xdr;
	स_नकल(clientid, p, माप(*clientid));
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_state_owner4(काष्ठा nfsd4_compoundargs *argp,
			  clientid_t *clientid, काष्ठा xdr_netobj *owner)
अणु
	__be32 status;

	status = nfsd4_decode_clientid4(argp, clientid);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_opaque(argp, owner);
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
अटल __be32
nfsd4_decode_deviceid4(काष्ठा nfsd4_compoundargs *argp,
		       काष्ठा nfsd4_deviceid *devid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, NFS4_DEVICEID4_SIZE);
	अगर (!p)
		वापस nfserr_bad_xdr;
	स_नकल(devid, p, माप(*devid));
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_layoutupdate4(काष्ठा nfsd4_compoundargs *argp,
			   काष्ठा nfsd4_layoutcommit *lcp)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &lcp->lc_layout_type) < 0)
		वापस nfserr_bad_xdr;
	अगर (lcp->lc_layout_type < LAYOUT_NFSV4_1_खाताS)
		वापस nfserr_bad_xdr;
	अगर (lcp->lc_layout_type >= LAYOUT_TYPE_MAX)
		वापस nfserr_bad_xdr;

	अगर (xdr_stream_decode_u32(argp->xdr, &lcp->lc_up_len) < 0)
		वापस nfserr_bad_xdr;
	अगर (lcp->lc_up_len > 0) अणु
		lcp->lc_up_layout = xdr_अंतरभूत_decode(argp->xdr, lcp->lc_up_len);
		अगर (!lcp->lc_up_layout)
			वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_layoutवापस4(काष्ठा nfsd4_compoundargs *argp,
			   काष्ठा nfsd4_layoutवापस *lrp)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &lrp->lr_वापस_type) < 0)
		वापस nfserr_bad_xdr;
	चयन (lrp->lr_वापस_type) अणु
	हाल RETURN_खाता:
		अगर (xdr_stream_decode_u64(argp->xdr, &lrp->lr_seg.offset) < 0)
			वापस nfserr_bad_xdr;
		अगर (xdr_stream_decode_u64(argp->xdr, &lrp->lr_seg.length) < 0)
			वापस nfserr_bad_xdr;
		status = nfsd4_decode_stateid4(argp, &lrp->lr_sid);
		अगर (status)
			वापस status;
		अगर (xdr_stream_decode_u32(argp->xdr, &lrp->lrf_body_len) < 0)
			वापस nfserr_bad_xdr;
		अगर (lrp->lrf_body_len > 0) अणु
			lrp->lrf_body = xdr_अंतरभूत_decode(argp->xdr, lrp->lrf_body_len);
			अगर (!lrp->lrf_body)
				वापस nfserr_bad_xdr;
		पूर्ण
		अवरोध;
	हाल RETURN_FSID:
	हाल RETURN_ALL:
		lrp->lr_seg.offset = 0;
		lrp->lr_seg.length = NFS4_MAX_UINT64;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

अटल __be32
nfsd4_decode_sessionid4(काष्ठा nfsd4_compoundargs *argp,
			काष्ठा nfs4_sessionid *sessionid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, NFS4_MAX_SESSIONID_LEN);
	अगर (!p)
		वापस nfserr_bad_xdr;
	स_नकल(sessionid->data, p, माप(sessionid->data));
	वापस nfs_ok;
पूर्ण

/* Defined in Appendix A of RFC 5531 */
अटल __be32
nfsd4_decode_authsys_parms(काष्ठा nfsd4_compoundargs *argp,
			   काष्ठा nfsd4_cb_sec *cbs)
अणु
	u32 stamp, gidcount, uid, gid;
	__be32 *p, status;

	अगर (xdr_stream_decode_u32(argp->xdr, &stamp) < 0)
		वापस nfserr_bad_xdr;
	/* machine name */
	status = nfsd4_decode_ignored_string(argp, 255);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &uid) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &gid) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &gidcount) < 0)
		वापस nfserr_bad_xdr;
	अगर (gidcount > 16)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, gidcount << 2);
	अगर (!p)
		वापस nfserr_bad_xdr;
	अगर (cbs->flavor == (u32)(-1)) अणु
		काष्ठा user_namespace *userns = nfsd_user_namespace(argp->rqstp);

		kuid_t kuid = make_kuid(userns, uid);
		kgid_t kgid = make_kgid(userns, gid);
		अगर (uid_valid(kuid) && gid_valid(kgid)) अणु
			cbs->uid = kuid;
			cbs->gid = kgid;
			cbs->flavor = RPC_AUTH_UNIX;
		पूर्ण अन्यथा अणु
			dprपूर्णांकk("RPC_AUTH_UNIX with invalid uid or gid, ignoring!\n");
		पूर्ण
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_gss_cb_handles4(काष्ठा nfsd4_compoundargs *argp,
			     काष्ठा nfsd4_cb_sec *cbs)
अणु
	__be32 status;
	u32 service;

	dprपूर्णांकk("RPC_AUTH_GSS callback secflavor not supported!\n");

	अगर (xdr_stream_decode_u32(argp->xdr, &service) < 0)
		वापस nfserr_bad_xdr;
	अगर (service < RPC_GSS_SVC_NONE || service > RPC_GSS_SVC_PRIVACY)
		वापस nfserr_bad_xdr;
	/* gcbp_handle_from_server */
	status = nfsd4_decode_ignored_string(argp, 0);
	अगर (status)
		वापस status;
	/* gcbp_handle_from_client */
	status = nfsd4_decode_ignored_string(argp, 0);
	अगर (status)
		वापस status;

	वापस nfs_ok;
पूर्ण

/* a counted array of callback_sec_parms4 items */
अटल __be32
nfsd4_decode_cb_sec(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_cb_sec *cbs)
अणु
	u32 i, secflavor, nr_secflavs;
	__be32 status;

	/* callback_sec_params4 */
	अगर (xdr_stream_decode_u32(argp->xdr, &nr_secflavs) < 0)
		वापस nfserr_bad_xdr;
	अगर (nr_secflavs)
		cbs->flavor = (u32)(-1);
	अन्यथा
		/* Is this legal? Be generous, take it to mean AUTH_NONE: */
		cbs->flavor = 0;

	क्रम (i = 0; i < nr_secflavs; ++i) अणु
		अगर (xdr_stream_decode_u32(argp->xdr, &secflavor) < 0)
			वापस nfserr_bad_xdr;
		चयन (secflavor) अणु
		हाल RPC_AUTH_शून्य:
			/* व्योम */
			अगर (cbs->flavor == (u32)(-1))
				cbs->flavor = RPC_AUTH_शून्य;
			अवरोध;
		हाल RPC_AUTH_UNIX:
			status = nfsd4_decode_authsys_parms(argp, cbs);
			अगर (status)
				वापस status;
			अवरोध;
		हाल RPC_AUTH_GSS:
			status = nfsd4_decode_gss_cb_handles4(argp, cbs);
			अगर (status)
				वापस status;
			अवरोध;
		शेष:
			वापस nfserr_inval;
		पूर्ण
	पूर्ण

	वापस nfs_ok;
पूर्ण


/*
 * NFSv4 operation argument decoders
 */

अटल __be32
nfsd4_decode_access(काष्ठा nfsd4_compoundargs *argp,
		    काष्ठा nfsd4_access *access)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &access->ac_req_access) < 0)
		वापस nfserr_bad_xdr;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_बंद(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_बंद *बंद)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &बंद->cl_seqid) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_stateid4(argp, &बंद->cl_stateid);
पूर्ण


अटल __be32
nfsd4_decode_commit(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_commit *commit)
अणु
	अगर (xdr_stream_decode_u64(argp->xdr, &commit->co_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &commit->co_count) < 0)
		वापस nfserr_bad_xdr;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_create(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_create *create)
अणु
	__be32 *p, status;

	अगर (xdr_stream_decode_u32(argp->xdr, &create->cr_type) < 0)
		वापस nfserr_bad_xdr;
	चयन (create->cr_type) अणु
	हाल NF4LNK:
		अगर (xdr_stream_decode_u32(argp->xdr, &create->cr_datalen) < 0)
			वापस nfserr_bad_xdr;
		p = xdr_अंतरभूत_decode(argp->xdr, create->cr_datalen);
		अगर (!p)
			वापस nfserr_bad_xdr;
		create->cr_data = svcxdr_dupstr(argp, p, create->cr_datalen);
		अगर (!create->cr_data)
			वापस nfserr_jukebox;
		अवरोध;
	हाल NF4BLK:
	हाल NF4CHR:
		अगर (xdr_stream_decode_u32(argp->xdr, &create->cr_specdata1) < 0)
			वापस nfserr_bad_xdr;
		अगर (xdr_stream_decode_u32(argp->xdr, &create->cr_specdata2) < 0)
			वापस nfserr_bad_xdr;
		अवरोध;
	हाल NF4SOCK:
	हाल NF4FIFO:
	हाल NF4सूची:
	शेष:
		अवरोध;
	पूर्ण
	status = nfsd4_decode_component4(argp, &create->cr_name,
					 &create->cr_namelen);
	अगर (status)
		वापस status;
	status = nfsd4_decode_fattr4(argp, create->cr_bmval,
				    ARRAY_SIZE(create->cr_bmval),
				    &create->cr_iattr, &create->cr_acl,
				    &create->cr_label, &create->cr_umask);
	अगर (status)
		वापस status;

	वापस nfs_ok;
पूर्ण

अटल अंतरभूत __be32
nfsd4_decode_delegवापस(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_delegवापस *dr)
अणु
	वापस nfsd4_decode_stateid4(argp, &dr->dr_stateid);
पूर्ण

अटल अंतरभूत __be32
nfsd4_decode_getattr(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_getattr *getattr)
अणु
	वापस nfsd4_decode_biपंचांगap4(argp, getattr->ga_bmval,
				    ARRAY_SIZE(getattr->ga_bmval));
पूर्ण

अटल __be32
nfsd4_decode_link(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_link *link)
अणु
	वापस nfsd4_decode_component4(argp, &link->li_name, &link->li_namelen);
पूर्ण

अटल __be32
nfsd4_decode_खोलो_to_lock_owner4(काष्ठा nfsd4_compoundargs *argp,
				 काष्ठा nfsd4_lock *lock)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &lock->lk_new_खोलो_seqid) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_stateid4(argp, &lock->lk_new_खोलो_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &lock->lk_new_lock_seqid) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_state_owner4(argp, &lock->lk_new_clientid,
					 &lock->lk_new_owner);
पूर्ण

अटल __be32
nfsd4_decode_exist_lock_owner4(काष्ठा nfsd4_compoundargs *argp,
			       काष्ठा nfsd4_lock *lock)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &lock->lk_old_lock_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &lock->lk_old_lock_seqid) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_locker4(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_lock *lock)
अणु
	अगर (xdr_stream_decode_bool(argp->xdr, &lock->lk_is_new) < 0)
		वापस nfserr_bad_xdr;
	अगर (lock->lk_is_new)
		वापस nfsd4_decode_खोलो_to_lock_owner4(argp, lock);
	वापस nfsd4_decode_exist_lock_owner4(argp, lock);
पूर्ण

अटल __be32
nfsd4_decode_lock(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_lock *lock)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &lock->lk_type) < 0)
		वापस nfserr_bad_xdr;
	अगर ((lock->lk_type < NFS4_READ_LT) || (lock->lk_type > NFS4_WRITEW_LT))
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_bool(argp->xdr, &lock->lk_reclaim) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lock->lk_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lock->lk_length) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_locker4(argp, lock);
पूर्ण

अटल __be32
nfsd4_decode_lockt(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_lockt *lockt)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &lockt->lt_type) < 0)
		वापस nfserr_bad_xdr;
	अगर ((lockt->lt_type < NFS4_READ_LT) || (lockt->lt_type > NFS4_WRITEW_LT))
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lockt->lt_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lockt->lt_length) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_state_owner4(argp, &lockt->lt_clientid,
					 &lockt->lt_owner);
पूर्ण

अटल __be32
nfsd4_decode_locku(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_locku *locku)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &locku->lu_type) < 0)
		वापस nfserr_bad_xdr;
	अगर ((locku->lu_type < NFS4_READ_LT) || (locku->lu_type > NFS4_WRITEW_LT))
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &locku->lu_seqid) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_stateid4(argp, &locku->lu_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &locku->lu_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &locku->lu_length) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_lookup(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_lookup *lookup)
अणु
	वापस nfsd4_decode_component4(argp, &lookup->lo_name, &lookup->lo_len);
पूर्ण

अटल __be32
nfsd4_decode_createhow4(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो->op_createmode) < 0)
		वापस nfserr_bad_xdr;
	चयन (खोलो->op_createmode) अणु
	हाल NFS4_CREATE_UNCHECKED:
	हाल NFS4_CREATE_GUARDED:
		status = nfsd4_decode_fattr4(argp, खोलो->op_bmval,
					     ARRAY_SIZE(खोलो->op_bmval),
					     &खोलो->op_iattr, &खोलो->op_acl,
					     &खोलो->op_label, &खोलो->op_umask);
		अगर (status)
			वापस status;
		अवरोध;
	हाल NFS4_CREATE_EXCLUSIVE:
		status = nfsd4_decode_verअगरier4(argp, &खोलो->op_verf);
		अगर (status)
			वापस status;
		अवरोध;
	हाल NFS4_CREATE_EXCLUSIVE4_1:
		अगर (argp->minorversion < 1)
			वापस nfserr_bad_xdr;
		status = nfsd4_decode_verअगरier4(argp, &खोलो->op_verf);
		अगर (status)
			वापस status;
		status = nfsd4_decode_fattr4(argp, खोलो->op_bmval,
					     ARRAY_SIZE(खोलो->op_bmval),
					     &खोलो->op_iattr, &खोलो->op_acl,
					     &खोलो->op_label, &खोलो->op_umask);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_खोलोflag4(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो->op_create) < 0)
		वापस nfserr_bad_xdr;
	चयन (खोलो->op_create) अणु
	हाल NFS4_OPEN_NOCREATE:
		अवरोध;
	हाल NFS4_OPEN_CREATE:
		status = nfsd4_decode_createhow4(argp, खोलो);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_decode_share_access(काष्ठा nfsd4_compoundargs *argp, u32 *share_access, u32 *deleg_want, u32 *deleg_when)
अणु
	u32 w;

	अगर (xdr_stream_decode_u32(argp->xdr, &w) < 0)
		वापस nfserr_bad_xdr;
	*share_access = w & NFS4_SHARE_ACCESS_MASK;
	*deleg_want = w & NFS4_SHARE_WANT_MASK;
	अगर (deleg_when)
		*deleg_when = w & NFS4_SHARE_WHEN_MASK;

	चयन (w & NFS4_SHARE_ACCESS_MASK) अणु
	हाल NFS4_SHARE_ACCESS_READ:
	हाल NFS4_SHARE_ACCESS_WRITE:
	हाल NFS4_SHARE_ACCESS_BOTH:
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण
	w &= ~NFS4_SHARE_ACCESS_MASK;
	अगर (!w)
		वापस nfs_ok;
	अगर (!argp->minorversion)
		वापस nfserr_bad_xdr;
	चयन (w & NFS4_SHARE_WANT_MASK) अणु
	हाल NFS4_SHARE_WANT_NO_PREFERENCE:
	हाल NFS4_SHARE_WANT_READ_DELEG:
	हाल NFS4_SHARE_WANT_WRITE_DELEG:
	हाल NFS4_SHARE_WANT_ANY_DELEG:
	हाल NFS4_SHARE_WANT_NO_DELEG:
	हाल NFS4_SHARE_WANT_CANCEL:
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण
	w &= ~NFS4_SHARE_WANT_MASK;
	अगर (!w)
		वापस nfs_ok;

	अगर (!deleg_when)	/* खोलो_करोwngrade */
		वापस nfserr_inval;
	चयन (w) अणु
	हाल NFS4_SHARE_SIGNAL_DELEG_WHEN_RESRC_AVAIL:
	हाल NFS4_SHARE_PUSH_DELEG_WHEN_UNCONTENDED:
	हाल (NFS4_SHARE_SIGNAL_DELEG_WHEN_RESRC_AVAIL |
	      NFS4_SHARE_PUSH_DELEG_WHEN_UNCONTENDED):
		वापस nfs_ok;
	पूर्ण
	वापस nfserr_bad_xdr;
पूर्ण

अटल __be32 nfsd4_decode_share_deny(काष्ठा nfsd4_compoundargs *argp, u32 *x)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, x) < 0)
		वापस nfserr_bad_xdr;
	/* Note: unlike access bits, deny bits may be zero. */
	अगर (*x & ~NFS4_SHARE_DENY_BOTH)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_खोलो_claim4(काष्ठा nfsd4_compoundargs *argp,
			 काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो->op_claim_type) < 0)
		वापस nfserr_bad_xdr;
	चयन (खोलो->op_claim_type) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_DELEGATE_PREV:
		status = nfsd4_decode_component4(argp, &खोलो->op_fname,
						 &खोलो->op_fnamelen);
		अगर (status)
			वापस status;
		अवरोध;
	हाल NFS4_OPEN_CLAIM_PREVIOUS:
		अगर (xdr_stream_decode_u32(argp->xdr, &खोलो->op_delegate_type) < 0)
			वापस nfserr_bad_xdr;
		अवरोध;
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
		status = nfsd4_decode_stateid4(argp, &खोलो->op_delegate_stateid);
		अगर (status)
			वापस status;
		status = nfsd4_decode_component4(argp, &खोलो->op_fname,
						 &खोलो->op_fnamelen);
		अगर (status)
			वापस status;
		अवरोध;
	हाल NFS4_OPEN_CLAIM_FH:
	हाल NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		अगर (argp->minorversion < 1)
			वापस nfserr_bad_xdr;
		/* व्योम */
		अवरोध;
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		अगर (argp->minorversion < 1)
			वापस nfserr_bad_xdr;
		status = nfsd4_decode_stateid4(argp, &खोलो->op_delegate_stateid);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_खोलो(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status;
	u32 dummy;

	स_रखो(खोलो->op_bmval, 0, माप(खोलो->op_bmval));
	खोलो->op_iattr.ia_valid = 0;
	खोलो->op_खोलोowner = शून्य;

	खोलो->op_xdr_error = 0;
	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो->op_seqid) < 0)
		वापस nfserr_bad_xdr;
	/* deleg_want is ignored */
	status = nfsd4_decode_share_access(argp, &खोलो->op_share_access,
					   &खोलो->op_deleg_want, &dummy);
	अगर (status)
		वापस status;
	status = nfsd4_decode_share_deny(argp, &खोलो->op_share_deny);
	अगर (status)
		वापस status;
	status = nfsd4_decode_state_owner4(argp, &खोलो->op_clientid,
					   &खोलो->op_owner);
	अगर (status)
		वापस status;
	status = nfsd4_decode_खोलोflag4(argp, खोलो);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_खोलो_claim4(argp, खोलो);
पूर्ण

अटल __be32
nfsd4_decode_खोलो_confirm(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_खोलो_confirm *खोलो_conf)
अणु
	__be32 status;

	अगर (argp->minorversion >= 1)
		वापस nfserr_notsupp;

	status = nfsd4_decode_stateid4(argp, &खोलो_conf->oc_req_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो_conf->oc_seqid) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_खोलो_करोwngrade(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_खोलो_करोwngrade *खोलो_करोwn)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &खोलो_करोwn->od_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &खोलो_करोwn->od_seqid) < 0)
		वापस nfserr_bad_xdr;
	/* deleg_want is ignored */
	status = nfsd4_decode_share_access(argp, &खोलो_करोwn->od_share_access,
					   &खोलो_करोwn->od_deleg_want, शून्य);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_share_deny(argp, &खोलो_करोwn->od_share_deny);
पूर्ण

अटल __be32
nfsd4_decode_putfh(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_putfh *putfh)
अणु
	__be32 *p;

	अगर (xdr_stream_decode_u32(argp->xdr, &putfh->pf_fhlen) < 0)
		वापस nfserr_bad_xdr;
	अगर (putfh->pf_fhlen > NFS4_FHSIZE)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, putfh->pf_fhlen);
	अगर (!p)
		वापस nfserr_bad_xdr;
	putfh->pf_fhval = svcxdr_savemem(argp, p, putfh->pf_fhlen);
	अगर (!putfh->pf_fhval)
		वापस nfserr_jukebox;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_putpubfh(काष्ठा nfsd4_compoundargs *argp, व्योम *p)
अणु
	अगर (argp->minorversion == 0)
		वापस nfs_ok;
	वापस nfserr_notsupp;
पूर्ण

अटल __be32
nfsd4_decode_पढ़ो(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_पढ़ो *पढ़ो)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &पढ़ो->rd_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &पढ़ो->rd_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &पढ़ो->rd_length) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_सूची_पढ़ो(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_सूची_पढ़ो *सूची_पढ़ो)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u64(argp->xdr, &सूची_पढ़ो->rd_cookie) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_verअगरier4(argp, &सूची_पढ़ो->rd_verf);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &सूची_पढ़ो->rd_dircount) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &सूची_पढ़ो->rd_maxcount) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_uपूर्णांक32_array(argp->xdr, सूची_पढ़ो->rd_bmval,
					   ARRAY_SIZE(सूची_पढ़ो->rd_bmval)) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_हटाओ(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_हटाओ *हटाओ)
अणु
	वापस nfsd4_decode_component4(argp, &हटाओ->rm_name, &हटाओ->rm_namelen);
पूर्ण

अटल __be32
nfsd4_decode_नाम(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_नाम *नाम)
अणु
	__be32 status;

	status = nfsd4_decode_component4(argp, &नाम->rn_sname, &नाम->rn_snamelen);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_component4(argp, &नाम->rn_tname, &नाम->rn_tnamelen);
पूर्ण

अटल __be32
nfsd4_decode_renew(काष्ठा nfsd4_compoundargs *argp, clientid_t *clientid)
अणु
	वापस nfsd4_decode_clientid4(argp, clientid);
पूर्ण

अटल __be32
nfsd4_decode_secinfo(काष्ठा nfsd4_compoundargs *argp,
		     काष्ठा nfsd4_secinfo *secinfo)
अणु
	वापस nfsd4_decode_component4(argp, &secinfo->si_name, &secinfo->si_namelen);
पूर्ण

अटल __be32
nfsd4_decode_setattr(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_setattr *setattr)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &setattr->sa_stateid);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_fattr4(argp, setattr->sa_bmval,
				   ARRAY_SIZE(setattr->sa_bmval),
				   &setattr->sa_iattr, &setattr->sa_acl,
				   &setattr->sa_label, शून्य);
पूर्ण

अटल __be32
nfsd4_decode_setclientid(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_setclientid *setclientid)
अणु
	__be32 *p, status;

	अगर (argp->minorversion >= 1)
		वापस nfserr_notsupp;

	status = nfsd4_decode_verअगरier4(argp, &setclientid->se_verf);
	अगर (status)
		वापस status;
	status = nfsd4_decode_opaque(argp, &setclientid->se_name);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &setclientid->se_callback_prog) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &setclientid->se_callback_netid_len) < 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, setclientid->se_callback_netid_len);
	अगर (!p)
		वापस nfserr_bad_xdr;
	setclientid->se_callback_netid_val = svcxdr_savemem(argp, p,
						setclientid->se_callback_netid_len);
	अगर (!setclientid->se_callback_netid_val)
		वापस nfserr_jukebox;

	अगर (xdr_stream_decode_u32(argp->xdr, &setclientid->se_callback_addr_len) < 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, setclientid->se_callback_addr_len);
	अगर (!p)
		वापस nfserr_bad_xdr;
	setclientid->se_callback_addr_val = svcxdr_savemem(argp, p,
						setclientid->se_callback_addr_len);
	अगर (!setclientid->se_callback_addr_val)
		वापस nfserr_jukebox;
	अगर (xdr_stream_decode_u32(argp->xdr, &setclientid->se_callback_ident) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_setclientid_confirm(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_setclientid_confirm *scd_c)
अणु
	__be32 status;

	अगर (argp->minorversion >= 1)
		वापस nfserr_notsupp;

	status = nfsd4_decode_clientid4(argp, &scd_c->sc_clientid);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_verअगरier4(argp, &scd_c->sc_confirm);
पूर्ण

/* Also used क्रम NVERIFY */
अटल __be32
nfsd4_decode_verअगरy(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_verअगरy *verअगरy)
अणु
	__be32 *p, status;

	status = nfsd4_decode_biपंचांगap4(argp, verअगरy->ve_bmval,
				      ARRAY_SIZE(verअगरy->ve_bmval));
	अगर (status)
		वापस status;

	/* For convenience's sake, we compare raw xdr'd attributes in
	 * nfsd4_proc_verअगरy */

	अगर (xdr_stream_decode_u32(argp->xdr, &verअगरy->ve_attrlen) < 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, verअगरy->ve_attrlen);
	अगर (!p)
		वापस nfserr_bad_xdr;
	verअगरy->ve_attrval = svcxdr_savemem(argp, p, verअगरy->ve_attrlen);
	अगर (!verअगरy->ve_attrval)
		वापस nfserr_jukebox;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_ग_लिखो(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_ग_लिखो *ग_लिखो)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &ग_लिखो->wr_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &ग_लिखो->wr_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &ग_लिखो->wr_stable_how) < 0)
		वापस nfserr_bad_xdr;
	अगर (ग_लिखो->wr_stable_how > NFS_खाता_SYNC)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &ग_लिखो->wr_buflen) < 0)
		वापस nfserr_bad_xdr;
	अगर (!xdr_stream_subsegment(argp->xdr, &ग_लिखो->wr_payload, ग_लिखो->wr_buflen))
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_release_lockowner(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_release_lockowner *rlockowner)
अणु
	__be32 status;

	अगर (argp->minorversion >= 1)
		वापस nfserr_notsupp;

	status = nfsd4_decode_state_owner4(argp, &rlockowner->rl_clientid,
					   &rlockowner->rl_owner);
	अगर (status)
		वापस status;

	अगर (argp->minorversion && !zero_clientid(&rlockowner->rl_clientid))
		वापस nfserr_inval;

	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_decode_backchannel_ctl(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_backchannel_ctl *bc)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &bc->bc_cb_program) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_cb_sec(argp, &bc->bc_cb_sec);
पूर्ण

अटल __be32 nfsd4_decode_bind_conn_to_session(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_bind_conn_to_session *bcts)
अणु
	u32 use_conn_in_rdma_mode;
	__be32 status;

	status = nfsd4_decode_sessionid4(argp, &bcts->sessionid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &bcts->dir) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &use_conn_in_rdma_mode) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_state_protect_ops(काष्ठा nfsd4_compoundargs *argp,
			       काष्ठा nfsd4_exchange_id *exid)
अणु
	__be32 status;

	status = nfsd4_decode_biपंचांगap4(argp, exid->spo_must_enक्रमce,
				      ARRAY_SIZE(exid->spo_must_enक्रमce));
	अगर (status)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_biपंचांगap4(argp, exid->spo_must_allow,
				      ARRAY_SIZE(exid->spo_must_allow));
	अगर (status)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

/*
 * This implementation currently करोes not support SP4_SSV.
 * This decoder simply skips over these arguments.
 */
अटल noअंतरभूत __be32
nfsd4_decode_ssv_sp_parms(काष्ठा nfsd4_compoundargs *argp,
			  काष्ठा nfsd4_exchange_id *exid)
अणु
	u32 count, winकरोw, num_gss_handles;
	__be32 status;

	/* ssp_ops */
	status = nfsd4_decode_state_protect_ops(argp, exid);
	अगर (status)
		वापस status;

	/* ssp_hash_algs<> */
	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;
	जबतक (count--) अणु
		status = nfsd4_decode_ignored_string(argp, 0);
		अगर (status)
			वापस status;
	पूर्ण

	/* ssp_encr_algs<> */
	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;
	जबतक (count--) अणु
		status = nfsd4_decode_ignored_string(argp, 0);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (xdr_stream_decode_u32(argp->xdr, &winकरोw) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &num_gss_handles) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_state_protect4_a(काष्ठा nfsd4_compoundargs *argp,
			      काष्ठा nfsd4_exchange_id *exid)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &exid->spa_how) < 0)
		वापस nfserr_bad_xdr;
	चयन (exid->spa_how) अणु
	हाल SP4_NONE:
		अवरोध;
	हाल SP4_MACH_CRED:
		status = nfsd4_decode_state_protect_ops(argp, exid);
		अगर (status)
			वापस status;
		अवरोध;
	हाल SP4_SSV:
		status = nfsd4_decode_ssv_sp_parms(argp, exid);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_nfs_impl_id4(काष्ठा nfsd4_compoundargs *argp,
			  काष्ठा nfsd4_exchange_id *exid)
अणु
	__be32 status;
	u32 count;

	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;
	चयन (count) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		/* Note that RFC 8881 places no length limit on
		 * nii_करोमुख्य, but this implementation permits no
		 * more than NFS4_OPAQUE_LIMIT bytes */
		status = nfsd4_decode_opaque(argp, &exid->nii_करोमुख्य);
		अगर (status)
			वापस status;
		/* Note that RFC 8881 places no length limit on
		 * nii_name, but this implementation permits no
		 * more than NFS4_OPAQUE_LIMIT bytes */
		status = nfsd4_decode_opaque(argp, &exid->nii_name);
		अगर (status)
			वापस status;
		status = nfsd4_decode_nfsसमय4(argp, &exid->nii_समय);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_exchange_id(काष्ठा nfsd4_compoundargs *argp,
			 काष्ठा nfsd4_exchange_id *exid)
अणु
	__be32 status;

	status = nfsd4_decode_verअगरier4(argp, &exid->verअगरier);
	अगर (status)
		वापस status;
	status = nfsd4_decode_opaque(argp, &exid->clname);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &exid->flags) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_state_protect4_a(argp, exid);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_nfs_impl_id4(argp, exid);
पूर्ण

अटल __be32
nfsd4_decode_channel_attrs4(काष्ठा nfsd4_compoundargs *argp,
			    काष्ठा nfsd4_channel_attrs *ca)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(argp->xdr, XDR_UNIT * 7);
	अगर (!p)
		वापस nfserr_bad_xdr;

	/* headerpadsz is ignored */
	p++;
	ca->maxreq_sz = be32_to_cpup(p++);
	ca->maxresp_sz = be32_to_cpup(p++);
	ca->maxresp_cached = be32_to_cpup(p++);
	ca->maxops = be32_to_cpup(p++);
	ca->maxreqs = be32_to_cpup(p++);
	ca->nr_rdma_attrs = be32_to_cpup(p);
	चयन (ca->nr_rdma_attrs) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		अगर (xdr_stream_decode_u32(argp->xdr, &ca->rdma_attrs) < 0)
			वापस nfserr_bad_xdr;
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_create_session(काष्ठा nfsd4_compoundargs *argp,
			    काष्ठा nfsd4_create_session *sess)
अणु
	__be32 status;

	status = nfsd4_decode_clientid4(argp, &sess->clientid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &sess->seqid) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &sess->flags) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_channel_attrs4(argp, &sess->क्रमe_channel);
	अगर (status)
		वापस status;
	status = nfsd4_decode_channel_attrs4(argp, &sess->back_channel);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &sess->callback_prog) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_cb_sec(argp, &sess->cb_sec);
	अगर (status)
		वापस status;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_destroy_session(काष्ठा nfsd4_compoundargs *argp,
			     काष्ठा nfsd4_destroy_session *destroy_session)
अणु
	वापस nfsd4_decode_sessionid4(argp, &destroy_session->sessionid);
पूर्ण

अटल __be32
nfsd4_decode_मुक्त_stateid(काष्ठा nfsd4_compoundargs *argp,
			  काष्ठा nfsd4_मुक्त_stateid *मुक्त_stateid)
अणु
	वापस nfsd4_decode_stateid4(argp, &मुक्त_stateid->fr_stateid);
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
अटल __be32
nfsd4_decode_getdeviceinfo(काष्ठा nfsd4_compoundargs *argp,
		काष्ठा nfsd4_getdeviceinfo *gdev)
अणु
	__be32 status;

	status = nfsd4_decode_deviceid4(argp, &gdev->gd_devid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &gdev->gd_layout_type) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &gdev->gd_maxcount) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_uपूर्णांक32_array(argp->xdr,
					   &gdev->gd_notअगरy_types, 1) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_layoutcommit(काष्ठा nfsd4_compoundargs *argp,
			  काष्ठा nfsd4_layoutcommit *lcp)
अणु
	__be32 *p, status;

	अगर (xdr_stream_decode_u64(argp->xdr, &lcp->lc_seg.offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lcp->lc_seg.length) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_bool(argp->xdr, &lcp->lc_reclaim) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_stateid4(argp, &lcp->lc_sid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &lcp->lc_newoffset) < 0)
		वापस nfserr_bad_xdr;
	अगर (lcp->lc_newoffset) अणु
		अगर (xdr_stream_decode_u64(argp->xdr, &lcp->lc_last_wr) < 0)
			वापस nfserr_bad_xdr;
	पूर्ण अन्यथा
		lcp->lc_last_wr = 0;
	p = xdr_अंतरभूत_decode(argp->xdr, XDR_UNIT);
	अगर (!p)
		वापस nfserr_bad_xdr;
	अगर (xdr_item_is_present(p)) अणु
		status = nfsd4_decode_nfsसमय4(argp, &lcp->lc_mसमय);
		अगर (status)
			वापस status;
	पूर्ण अन्यथा अणु
		lcp->lc_mसमय.tv_nsec = UTIME_NOW;
	पूर्ण
	वापस nfsd4_decode_layoutupdate4(argp, lcp);
पूर्ण

अटल __be32
nfsd4_decode_layoutget(काष्ठा nfsd4_compoundargs *argp,
		काष्ठा nfsd4_layoutget *lgp)
अणु
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &lgp->lg_संकेत) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &lgp->lg_layout_type) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &lgp->lg_seg.iomode) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lgp->lg_seg.offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lgp->lg_seg.length) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &lgp->lg_minlength) < 0)
		वापस nfserr_bad_xdr;
	status = nfsd4_decode_stateid4(argp, &lgp->lg_sid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u32(argp->xdr, &lgp->lg_maxcount) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_layoutवापस(काष्ठा nfsd4_compoundargs *argp,
		काष्ठा nfsd4_layoutवापस *lrp)
अणु
	अगर (xdr_stream_decode_bool(argp->xdr, &lrp->lr_reclaim) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &lrp->lr_layout_type) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &lrp->lr_seg.iomode) < 0)
		वापस nfserr_bad_xdr;
	वापस nfsd4_decode_layoutवापस4(argp, lrp);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

अटल __be32 nfsd4_decode_secinfo_no_name(काष्ठा nfsd4_compoundargs *argp,
					   काष्ठा nfsd4_secinfo_no_name *sin)
अणु
	अगर (xdr_stream_decode_u32(argp->xdr, &sin->sin_style) < 0)
		वापस nfserr_bad_xdr;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_sequence(काष्ठा nfsd4_compoundargs *argp,
		      काष्ठा nfsd4_sequence *seq)
अणु
	__be32 *p, status;

	status = nfsd4_decode_sessionid4(argp, &seq->sessionid);
	अगर (status)
		वापस status;
	p = xdr_अंतरभूत_decode(argp->xdr, XDR_UNIT * 4);
	अगर (!p)
		वापस nfserr_bad_xdr;
	seq->seqid = be32_to_cpup(p++);
	seq->slotid = be32_to_cpup(p++);
	seq->maxslots = be32_to_cpup(p++);
	seq->cachethis = be32_to_cpup(p);

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_test_stateid(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_test_stateid *test_stateid)
अणु
	काष्ठा nfsd4_test_stateid_id *stateid;
	__be32 status;
	u32 i;

	अगर (xdr_stream_decode_u32(argp->xdr, &test_stateid->ts_num_ids) < 0)
		वापस nfserr_bad_xdr;

	INIT_LIST_HEAD(&test_stateid->ts_stateid_list);
	क्रम (i = 0; i < test_stateid->ts_num_ids; i++) अणु
		stateid = svcxdr_पंचांगpalloc(argp, माप(*stateid));
		अगर (!stateid)
			वापस nfsत्रुटि_सं(-ENOMEM);	/* XXX: not jukebox? */
		INIT_LIST_HEAD(&stateid->ts_id_list);
		list_add_tail(&stateid->ts_id_list, &test_stateid->ts_stateid_list);
		status = nfsd4_decode_stateid4(argp, &stateid->ts_id_stateid);
		अगर (status)
			वापस status;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_decode_destroy_clientid(काष्ठा nfsd4_compoundargs *argp,
					    काष्ठा nfsd4_destroy_clientid *dc)
अणु
	वापस nfsd4_decode_clientid4(argp, &dc->clientid);
पूर्ण

अटल __be32 nfsd4_decode_reclaim_complete(काष्ठा nfsd4_compoundargs *argp,
					    काष्ठा nfsd4_reclaim_complete *rc)
अणु
	अगर (xdr_stream_decode_bool(argp->xdr, &rc->rca_one_fs) < 0)
		वापस nfserr_bad_xdr;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_fallocate(काष्ठा nfsd4_compoundargs *argp,
		       काष्ठा nfsd4_fallocate *fallocate)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &fallocate->falloc_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &fallocate->falloc_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &fallocate->falloc_length) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_decode_nl4_server(काष्ठा nfsd4_compoundargs *argp,
				      काष्ठा nl4_server *ns)
अणु
	काष्ठा nfs42_netaddr *naddr;
	__be32 *p;

	अगर (xdr_stream_decode_u32(argp->xdr, &ns->nl4_type) < 0)
		वापस nfserr_bad_xdr;

	/* currently support क्रम 1 पूर्णांकer-server source server */
	चयन (ns->nl4_type) अणु
	हाल NL4_NETADDR:
		naddr = &ns->u.nl4_addr;

		अगर (xdr_stream_decode_u32(argp->xdr, &naddr->netid_len) < 0)
			वापस nfserr_bad_xdr;
		अगर (naddr->netid_len > RPCBIND_MAXNETIDLEN)
			वापस nfserr_bad_xdr;

		p = xdr_अंतरभूत_decode(argp->xdr, naddr->netid_len);
		अगर (!p)
			वापस nfserr_bad_xdr;
		स_नकल(naddr->netid, p, naddr->netid_len);

		अगर (xdr_stream_decode_u32(argp->xdr, &naddr->addr_len) < 0)
			वापस nfserr_bad_xdr;
		अगर (naddr->addr_len > RPCBIND_MAXUADDRLEN)
			वापस nfserr_bad_xdr;

		p = xdr_अंतरभूत_decode(argp->xdr, naddr->addr_len);
		अगर (!p)
			वापस nfserr_bad_xdr;
		स_नकल(naddr->addr, p, naddr->addr_len);
		अवरोध;
	शेष:
		वापस nfserr_bad_xdr;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_copy(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_copy *copy)
अणु
	काष्ठा nl4_server *ns_dummy;
	u32 consecutive, i, count;
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &copy->cp_src_stateid);
	अगर (status)
		वापस status;
	status = nfsd4_decode_stateid4(argp, &copy->cp_dst_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &copy->cp_src_pos) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &copy->cp_dst_pos) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &copy->cp_count) < 0)
		वापस nfserr_bad_xdr;
	/* ca_consecutive: we always करो consecutive copies */
	अगर (xdr_stream_decode_u32(argp->xdr, &consecutive) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &copy->cp_synchronous) < 0)
		वापस nfserr_bad_xdr;

	अगर (xdr_stream_decode_u32(argp->xdr, &count) < 0)
		वापस nfserr_bad_xdr;
	copy->cp_पूर्णांकra = false;
	अगर (count == 0) अणु /* पूर्णांकra-server copy */
		copy->cp_पूर्णांकra = true;
		वापस nfs_ok;
	पूर्ण

	/* decode all the supplied server addresses but use only the first */
	status = nfsd4_decode_nl4_server(argp, &copy->cp_src);
	अगर (status)
		वापस status;

	ns_dummy = kदो_स्मृति(माप(काष्ठा nl4_server), GFP_KERNEL);
	अगर (ns_dummy == शून्य)
		वापस nfsत्रुटि_सं(-ENOMEM);	/* XXX: jukebox? */
	क्रम (i = 0; i < count - 1; i++) अणु
		status = nfsd4_decode_nl4_server(argp, ns_dummy);
		अगर (status) अणु
			kमुक्त(ns_dummy);
			वापस status;
		पूर्ण
	पूर्ण
	kमुक्त(ns_dummy);

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_copy_notअगरy(काष्ठा nfsd4_compoundargs *argp,
			 काष्ठा nfsd4_copy_notअगरy *cn)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &cn->cpn_src_stateid);
	अगर (status)
		वापस status;
	वापस nfsd4_decode_nl4_server(argp, &cn->cpn_dst);
पूर्ण

अटल __be32
nfsd4_decode_offload_status(काष्ठा nfsd4_compoundargs *argp,
			    काष्ठा nfsd4_offload_status *os)
अणु
	वापस nfsd4_decode_stateid4(argp, &os->stateid);
पूर्ण

अटल __be32
nfsd4_decode_seek(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_seek *seek)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &seek->seek_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &seek->seek_offset) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u32(argp->xdr, &seek->seek_whence) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_clone(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_clone *clone)
अणु
	__be32 status;

	status = nfsd4_decode_stateid4(argp, &clone->cl_src_stateid);
	अगर (status)
		वापस status;
	status = nfsd4_decode_stateid4(argp, &clone->cl_dst_stateid);
	अगर (status)
		वापस status;
	अगर (xdr_stream_decode_u64(argp->xdr, &clone->cl_src_pos) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &clone->cl_dst_pos) < 0)
		वापस nfserr_bad_xdr;
	अगर (xdr_stream_decode_u64(argp->xdr, &clone->cl_count) < 0)
		वापस nfserr_bad_xdr;

	वापस nfs_ok;
पूर्ण

/*
 * XDR data that is more than PAGE_SIZE in size is normally part of a
 * पढ़ो or ग_लिखो. However, the size of extended attributes is limited
 * by the maximum request size, and then further limited by the underlying
 * fileप्रणाली limits. This can exceed PAGE_SIZE (currently, XATTR_SIZE_MAX
 * is 64k). Since there is no kvec- or page-based पूर्णांकerface to xattrs,
 * and we're not dealing with contiguous pages, we need to करो some copying.
 */

/*
 * Decode data पूर्णांकo buffer.
 */
अटल __be32
nfsd4_vbuf_from_vector(काष्ठा nfsd4_compoundargs *argp, काष्ठा xdr_buf *xdr,
		       अक्षर **bufp, u32 buflen)
अणु
	काष्ठा page **pages = xdr->pages;
	काष्ठा kvec *head = xdr->head;
	अक्षर *पंचांगp, *dp;
	u32 len;

	अगर (buflen <= head->iov_len) अणु
		/*
		 * We're in luck, the head has enough space. Just वापस
		 * the head, no need क्रम copying.
		 */
		*bufp = head->iov_base;
		वापस 0;
	पूर्ण

	पंचांगp = svcxdr_पंचांगpalloc(argp, buflen);
	अगर (पंचांगp == शून्य)
		वापस nfserr_jukebox;

	dp = पंचांगp;
	स_नकल(dp, head->iov_base, head->iov_len);
	buflen -= head->iov_len;
	dp += head->iov_len;

	जबतक (buflen > 0) अणु
		len = min_t(u32, buflen, PAGE_SIZE);
		स_नकल(dp, page_address(*pages), len);

		buflen -= len;
		dp += len;
		pages++;
	पूर्ण

	*bufp = पंचांगp;
	वापस 0;
पूर्ण

/*
 * Get a user extended attribute name from the XDR buffer.
 * It will not have the "user." prefix, so prepend it.
 * Lastly, check क्रम nul अक्षरacters in the name.
 */
अटल __be32
nfsd4_decode_xattr_name(काष्ठा nfsd4_compoundargs *argp, अक्षर **namep)
अणु
	अक्षर *name, *sp, *dp;
	u32 namelen, cnt;
	__be32 *p;

	अगर (xdr_stream_decode_u32(argp->xdr, &namelen) < 0)
		वापस nfserr_bad_xdr;
	अगर (namelen > (XATTR_NAME_MAX - XATTR_USER_PREFIX_LEN))
		वापस nfserr_nametooदीर्घ;
	अगर (namelen == 0)
		वापस nfserr_bad_xdr;
	p = xdr_अंतरभूत_decode(argp->xdr, namelen);
	अगर (!p)
		वापस nfserr_bad_xdr;
	name = svcxdr_पंचांगpalloc(argp, namelen + XATTR_USER_PREFIX_LEN + 1);
	अगर (!name)
		वापस nfserr_jukebox;
	स_नकल(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN);

	/*
	 * Copy the extended attribute name over जबतक checking क्रम 0
	 * अक्षरacters.
	 */
	sp = (अक्षर *)p;
	dp = name + XATTR_USER_PREFIX_LEN;
	cnt = namelen;

	जबतक (cnt-- > 0) अणु
		अगर (*sp == '\0')
			वापस nfserr_bad_xdr;
		*dp++ = *sp++;
	पूर्ण
	*dp = '\0';

	*namep = name;

	वापस nfs_ok;
पूर्ण

/*
 * A GETXATTR op request comes without a length specअगरier. We just set the
 * maximum length क्रम the reply based on XATTR_SIZE_MAX and the maximum
 * channel reply size. nfsd_getxattr will probe the length of the xattr,
 * check it against getxa_len, and allocate + वापस the value.
 */
अटल __be32
nfsd4_decode_getxattr(काष्ठा nfsd4_compoundargs *argp,
		      काष्ठा nfsd4_getxattr *getxattr)
अणु
	__be32 status;
	u32 maxcount;

	status = nfsd4_decode_xattr_name(argp, &getxattr->getxa_name);
	अगर (status)
		वापस status;

	maxcount = svc_max_payload(argp->rqstp);
	maxcount = min_t(u32, XATTR_SIZE_MAX, maxcount);

	getxattr->getxa_len = maxcount;

	वापस status;
पूर्ण

अटल __be32
nfsd4_decode_setxattr(काष्ठा nfsd4_compoundargs *argp,
		      काष्ठा nfsd4_setxattr *setxattr)
अणु
	u32 flags, maxcount, size;
	__be32 status;

	अगर (xdr_stream_decode_u32(argp->xdr, &flags) < 0)
		वापस nfserr_bad_xdr;

	अगर (flags > SETXATTR4_REPLACE)
		वापस nfserr_inval;
	setxattr->setxa_flags = flags;

	status = nfsd4_decode_xattr_name(argp, &setxattr->setxa_name);
	अगर (status)
		वापस status;

	maxcount = svc_max_payload(argp->rqstp);
	maxcount = min_t(u32, XATTR_SIZE_MAX, maxcount);

	अगर (xdr_stream_decode_u32(argp->xdr, &size) < 0)
		वापस nfserr_bad_xdr;
	अगर (size > maxcount)
		वापस nfserr_xattr2big;

	setxattr->setxa_len = size;
	अगर (size > 0) अणु
		काष्ठा xdr_buf payload;

		अगर (!xdr_stream_subsegment(argp->xdr, &payload, size))
			वापस nfserr_bad_xdr;
		status = nfsd4_vbuf_from_vector(argp, &payload,
						&setxattr->setxa_buf, size);
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_listxattrs(काष्ठा nfsd4_compoundargs *argp,
			काष्ठा nfsd4_listxattrs *listxattrs)
अणु
	u32 maxcount;

	अगर (xdr_stream_decode_u64(argp->xdr, &listxattrs->lsxa_cookie) < 0)
		वापस nfserr_bad_xdr;

	/*
	 * If the cookie  is too large to have even one user.x attribute
	 * plus trailing '\0' left in a maximum size buffer, it's invalid.
	 */
	अगर (listxattrs->lsxa_cookie >=
	    (XATTR_LIST_MAX / (XATTR_USER_PREFIX_LEN + 2)))
		वापस nfserr_badcookie;

	अगर (xdr_stream_decode_u32(argp->xdr, &maxcount) < 0)
		वापस nfserr_bad_xdr;
	अगर (maxcount < 8)
		/* Always need at least 2 words (length and one अक्षरacter) */
		वापस nfserr_inval;

	maxcount = min(maxcount, svc_max_payload(argp->rqstp));
	listxattrs->lsxa_maxcount = maxcount;

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_हटाओxattr(काष्ठा nfsd4_compoundargs *argp,
			 काष्ठा nfsd4_हटाओxattr *हटाओxattr)
अणु
	वापस nfsd4_decode_xattr_name(argp, &हटाओxattr->rmxa_name);
पूर्ण

अटल __be32
nfsd4_decode_noop(काष्ठा nfsd4_compoundargs *argp, व्योम *p)
अणु
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_decode_notsupp(काष्ठा nfsd4_compoundargs *argp, व्योम *p)
अणु
	वापस nfserr_notsupp;
पूर्ण

प्रकार __be32(*nfsd4_dec)(काष्ठा nfsd4_compoundargs *argp, व्योम *);

अटल स्थिर nfsd4_dec nfsd4_dec_ops[] = अणु
	[OP_ACCESS]		= (nfsd4_dec)nfsd4_decode_access,
	[OP_CLOSE]		= (nfsd4_dec)nfsd4_decode_बंद,
	[OP_COMMIT]		= (nfsd4_dec)nfsd4_decode_commit,
	[OP_CREATE]		= (nfsd4_dec)nfsd4_decode_create,
	[OP_DELEGPURGE]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_DELEGRETURN]	= (nfsd4_dec)nfsd4_decode_delegवापस,
	[OP_GETATTR]		= (nfsd4_dec)nfsd4_decode_getattr,
	[OP_GETFH]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_LINK]		= (nfsd4_dec)nfsd4_decode_link,
	[OP_LOCK]		= (nfsd4_dec)nfsd4_decode_lock,
	[OP_LOCKT]		= (nfsd4_dec)nfsd4_decode_lockt,
	[OP_LOCKU]		= (nfsd4_dec)nfsd4_decode_locku,
	[OP_LOOKUP]		= (nfsd4_dec)nfsd4_decode_lookup,
	[OP_LOOKUPP]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_NVERIFY]		= (nfsd4_dec)nfsd4_decode_verअगरy,
	[OP_OPEN]		= (nfsd4_dec)nfsd4_decode_खोलो,
	[OP_OPENATTR]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_OPEN_CONFIRM]	= (nfsd4_dec)nfsd4_decode_खोलो_confirm,
	[OP_OPEN_DOWNGRADE]	= (nfsd4_dec)nfsd4_decode_खोलो_करोwngrade,
	[OP_PUTFH]		= (nfsd4_dec)nfsd4_decode_putfh,
	[OP_PUTPUBFH]		= (nfsd4_dec)nfsd4_decode_putpubfh,
	[OP_PUTROOTFH]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_READ]		= (nfsd4_dec)nfsd4_decode_पढ़ो,
	[OP_READसूची]		= (nfsd4_dec)nfsd4_decode_सूची_पढ़ो,
	[OP_READLINK]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_REMOVE]		= (nfsd4_dec)nfsd4_decode_हटाओ,
	[OP_RENAME]		= (nfsd4_dec)nfsd4_decode_नाम,
	[OP_RENEW]		= (nfsd4_dec)nfsd4_decode_renew,
	[OP_RESTOREFH]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_SAVEFH]		= (nfsd4_dec)nfsd4_decode_noop,
	[OP_SECINFO]		= (nfsd4_dec)nfsd4_decode_secinfo,
	[OP_SETATTR]		= (nfsd4_dec)nfsd4_decode_setattr,
	[OP_SETCLIENTID]	= (nfsd4_dec)nfsd4_decode_setclientid,
	[OP_SETCLIENTID_CONFIRM] = (nfsd4_dec)nfsd4_decode_setclientid_confirm,
	[OP_VERIFY]		= (nfsd4_dec)nfsd4_decode_verअगरy,
	[OP_WRITE]		= (nfsd4_dec)nfsd4_decode_ग_लिखो,
	[OP_RELEASE_LOCKOWNER]	= (nfsd4_dec)nfsd4_decode_release_lockowner,

	/* new operations क्रम NFSv4.1 */
	[OP_BACKCHANNEL_CTL]	= (nfsd4_dec)nfsd4_decode_backchannel_ctl,
	[OP_BIND_CONN_TO_SESSION]= (nfsd4_dec)nfsd4_decode_bind_conn_to_session,
	[OP_EXCHANGE_ID]	= (nfsd4_dec)nfsd4_decode_exchange_id,
	[OP_CREATE_SESSION]	= (nfsd4_dec)nfsd4_decode_create_session,
	[OP_DESTROY_SESSION]	= (nfsd4_dec)nfsd4_decode_destroy_session,
	[OP_FREE_STATEID]	= (nfsd4_dec)nfsd4_decode_मुक्त_stateid,
	[OP_GET_सूची_DELEGATION]	= (nfsd4_dec)nfsd4_decode_notsupp,
#अगर_घोषित CONFIG_NFSD_PNFS
	[OP_GETDEVICEINFO]	= (nfsd4_dec)nfsd4_decode_getdeviceinfo,
	[OP_GETDEVICELIST]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTCOMMIT]	= (nfsd4_dec)nfsd4_decode_layoutcommit,
	[OP_LAYOUTGET]		= (nfsd4_dec)nfsd4_decode_layoutget,
	[OP_LAYOUTRETURN]	= (nfsd4_dec)nfsd4_decode_layoutवापस,
#अन्यथा
	[OP_GETDEVICEINFO]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_GETDEVICELIST]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTCOMMIT]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTGET]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTRETURN]	= (nfsd4_dec)nfsd4_decode_notsupp,
#पूर्ण_अगर
	[OP_SECINFO_NO_NAME]	= (nfsd4_dec)nfsd4_decode_secinfo_no_name,
	[OP_SEQUENCE]		= (nfsd4_dec)nfsd4_decode_sequence,
	[OP_SET_SSV]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_TEST_STATEID]	= (nfsd4_dec)nfsd4_decode_test_stateid,
	[OP_WANT_DELEGATION]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_DESTROY_CLIENTID]	= (nfsd4_dec)nfsd4_decode_destroy_clientid,
	[OP_RECLAIM_COMPLETE]	= (nfsd4_dec)nfsd4_decode_reclaim_complete,

	/* new operations क्रम NFSv4.2 */
	[OP_ALLOCATE]		= (nfsd4_dec)nfsd4_decode_fallocate,
	[OP_COPY]		= (nfsd4_dec)nfsd4_decode_copy,
	[OP_COPY_NOTIFY]	= (nfsd4_dec)nfsd4_decode_copy_notअगरy,
	[OP_DEALLOCATE]		= (nfsd4_dec)nfsd4_decode_fallocate,
	[OP_IO_ADVISE]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTERROR]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_LAYOUTSTATS]	= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_OFFLOAD_CANCEL]	= (nfsd4_dec)nfsd4_decode_offload_status,
	[OP_OFFLOAD_STATUS]	= (nfsd4_dec)nfsd4_decode_offload_status,
	[OP_READ_PLUS]		= (nfsd4_dec)nfsd4_decode_पढ़ो,
	[OP_SEEK]		= (nfsd4_dec)nfsd4_decode_seek,
	[OP_WRITE_SAME]		= (nfsd4_dec)nfsd4_decode_notsupp,
	[OP_CLONE]		= (nfsd4_dec)nfsd4_decode_clone,
	/* RFC 8276 extended atributes operations */
	[OP_GETXATTR]		= (nfsd4_dec)nfsd4_decode_getxattr,
	[OP_SETXATTR]		= (nfsd4_dec)nfsd4_decode_setxattr,
	[OP_LISTXATTRS]		= (nfsd4_dec)nfsd4_decode_listxattrs,
	[OP_REMOVEXATTR]	= (nfsd4_dec)nfsd4_decode_हटाओxattr,
पूर्ण;

अटल अंतरभूत bool
nfsd4_opnum_in_range(काष्ठा nfsd4_compoundargs *argp, काष्ठा nfsd4_op *op)
अणु
	अगर (op->opnum < FIRST_NFS4_OP)
		वापस false;
	अन्यथा अगर (argp->minorversion == 0 && op->opnum > LAST_NFS40_OP)
		वापस false;
	अन्यथा अगर (argp->minorversion == 1 && op->opnum > LAST_NFS41_OP)
		वापस false;
	अन्यथा अगर (argp->minorversion == 2 && op->opnum > LAST_NFS42_OP)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक
nfsd4_decode_compound(काष्ठा nfsd4_compoundargs *argp)
अणु
	काष्ठा nfsd4_op *op;
	bool cachethis = false;
	पूर्णांक auth_slack= argp->rqstp->rq_auth_slack;
	पूर्णांक max_reply = auth_slack + 8; /* opcnt, status */
	पूर्णांक पढ़ोcount = 0;
	पूर्णांक पढ़ोbytes = 0;
	__be32 *p;
	पूर्णांक i;

	अगर (xdr_stream_decode_u32(argp->xdr, &argp->taglen) < 0)
		वापस 0;
	max_reply += XDR_UNIT;
	argp->tag = शून्य;
	अगर (unlikely(argp->taglen)) अणु
		अगर (argp->taglen > NFSD4_MAX_TAGLEN)
			वापस 0;
		p = xdr_अंतरभूत_decode(argp->xdr, argp->taglen);
		अगर (!p)
			वापस 0;
		argp->tag = svcxdr_savemem(argp, p, argp->taglen);
		अगर (!argp->tag)
			वापस 0;
		max_reply += xdr_align_size(argp->taglen);
	पूर्ण

	अगर (xdr_stream_decode_u32(argp->xdr, &argp->minorversion) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(argp->xdr, &argp->opcnt) < 0)
		वापस 0;

	/*
	 * NFS4ERR_RESOURCE is a more helpful error than GARBAGE_ARGS
	 * here, so we वापस success at the xdr level so that
	 * nfsd4_proc can handle this is an NFS-level error.
	 */
	अगर (argp->opcnt > NFSD_MAX_OPS_PER_COMPOUND)
		वापस 1;

	अगर (argp->opcnt > ARRAY_SIZE(argp->iops)) अणु
		argp->ops = kzalloc(argp->opcnt * माप(*argp->ops), GFP_KERNEL);
		अगर (!argp->ops) अणु
			argp->ops = argp->iops;
			dprपूर्णांकk("nfsd: couldn't allocate room for COMPOUND\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (argp->minorversion > NFSD_SUPPORTED_MINOR_VERSION)
		argp->opcnt = 0;

	क्रम (i = 0; i < argp->opcnt; i++) अणु
		op = &argp->ops[i];
		op->replay = शून्य;

		अगर (xdr_stream_decode_u32(argp->xdr, &op->opnum) < 0)
			वापस 0;
		अगर (nfsd4_opnum_in_range(argp, op)) अणु
			op->status = nfsd4_dec_ops[op->opnum](argp, &op->u);
			अगर (op->status != nfs_ok)
				trace_nfsd_compound_decode_err(argp->rqstp,
							       argp->opcnt, i,
							       op->opnum,
							       op->status);
		पूर्ण अन्यथा अणु
			op->opnum = OP_ILLEGAL;
			op->status = nfserr_op_illegal;
		पूर्ण
		op->opdesc = OPDESC(op);
		/*
		 * We'll try to cache the result in the DRC अगर any one
		 * op in the compound wants to be cached:
		 */
		cachethis |= nfsd4_cache_this_op(op);

		अगर (op->opnum == OP_READ || op->opnum == OP_READ_PLUS) अणु
			पढ़ोcount++;
			पढ़ोbytes += nfsd4_max_reply(argp->rqstp, op);
		पूर्ण अन्यथा
			max_reply += nfsd4_max_reply(argp->rqstp, op);
		/*
		 * OP_LOCK and OP_LOCKT may वापस a conflicting lock.
		 * (Special हाल because it will just skip encoding this
		 * अगर it runs out of xdr buffer space, and it is the only
		 * operation that behaves this way.)
		 */
		अगर (op->opnum == OP_LOCK || op->opnum == OP_LOCKT)
			max_reply += NFS4_OPAQUE_LIMIT;

		अगर (op->status) अणु
			argp->opcnt = i+1;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Sessions make the DRC unnecessary: */
	अगर (argp->minorversion)
		cachethis = false;
	svc_reserve(argp->rqstp, max_reply + पढ़ोbytes);
	argp->rqstp->rq_cachetype = cachethis ? RC_REPLBUFF : RC_NOCACHE;

	अगर (पढ़ोcount > 1 || max_reply > PAGE_SIZE - auth_slack)
		clear_bit(RQ_SPLICE_OK, &argp->rqstp->rq_flags);

	वापस 1;
पूर्ण

अटल __be32 *encode_change(__be32 *p, काष्ठा kstat *stat, काष्ठा inode *inode,
			     काष्ठा svc_export *exp)
अणु
	अगर (exp->ex_flags & NFSEXP_V4ROOT) अणु
		*p++ = cpu_to_be32(convert_to_wallघड़ी(exp->cd->flush_समय));
		*p++ = 0;
	पूर्ण अन्यथा
		p = xdr_encode_hyper(p, nfsd4_change_attribute(stat, inode));
	वापस p;
पूर्ण

/*
 * स_समय (in NFSv4, समय_metadata) is not ग_लिखोable, and the client
 * करोesn't really care what resolution could theoretically be stored by
 * the fileप्रणाली.
 *
 * The client cares how बंद together changes can be जबतक still
 * guaranteeing स_समय changes.  For most fileप्रणालीs (which have
 * बारtamps with nanosecond fields) that is limited by the resolution
 * of the समय वापसed from current_समय() (which I'm assuming to be
 * 1/HZ).
 */
अटल __be32 *encode_समय_delta(__be32 *p, काष्ठा inode *inode)
अणु
	काष्ठा बारpec64 ts;
	u32 ns;

	ns = max_t(u32, NSEC_PER_SEC/HZ, inode->i_sb->s_समय_gran);
	ts = ns_to_बारpec64(ns);

	p = xdr_encode_hyper(p, ts.tv_sec);
	*p++ = cpu_to_be32(ts.tv_nsec);

	वापस p;
पूर्ण

अटल __be32 *encode_cinfo(__be32 *p, काष्ठा nfsd4_change_info *c)
अणु
	*p++ = cpu_to_be32(c->atomic);
	p = xdr_encode_hyper(p, c->beक्रमe_change);
	p = xdr_encode_hyper(p, c->after_change);
	वापस p;
पूर्ण

/* Encode as an array of strings the string given with components
 * separated @sep, escaped with esc_enter and esc_निकास.
 */
अटल __be32 nfsd4_encode_components_esc(काष्ठा xdr_stream *xdr, अक्षर sep,
					  अक्षर *components, अक्षर esc_enter,
					  अक्षर esc_निकास)
अणु
	__be32 *p;
	__be32 pathlen;
	पूर्णांक pathlen_offset;
	पूर्णांक म_माप, count=0;
	अक्षर *str, *end, *next;

	dprपूर्णांकk("nfsd4_encode_components(%s)\n", components);

	pathlen_offset = xdr->buf->len;
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	p++; /* We will fill this in with @count later */

	end = str = components;
	जबतक (*end) अणु
		bool found_esc = false;

		/* try to parse as esc_start, ..., esc_end, sep */
		अगर (*str == esc_enter) अणु
			क्रम (; *end && (*end != esc_निकास); end++)
				/* find esc_निकास or end of string */;
			next = end + 1;
			अगर (*end && (!*next || *next == sep)) अणु
				str++;
				found_esc = true;
			पूर्ण
		पूर्ण

		अगर (!found_esc)
			क्रम (; *end && (*end != sep); end++)
				/* find sep or end of string */;

		म_माप = end - str;
		अगर (म_माप) अणु
			p = xdr_reserve_space(xdr, म_माप + 4);
			अगर (!p)
				वापस nfserr_resource;
			p = xdr_encode_opaque(p, str, म_माप);
			count++;
		पूर्ण
		अन्यथा
			end++;
		अगर (found_esc)
			end = next;

		str = end;
	पूर्ण
	pathlen = htonl(count);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, pathlen_offset, &pathlen, 4);
	वापस 0;
पूर्ण

/* Encode as an array of strings the string given with components
 * separated @sep.
 */
अटल __be32 nfsd4_encode_components(काष्ठा xdr_stream *xdr, अक्षर sep,
				      अक्षर *components)
अणु
	वापस nfsd4_encode_components_esc(xdr, sep, components, 0, 0);
पूर्ण

/*
 * encode a location element of a fs_locations काष्ठाure
 */
अटल __be32 nfsd4_encode_fs_location4(काष्ठा xdr_stream *xdr,
					काष्ठा nfsd4_fs_location *location)
अणु
	__be32 status;

	status = nfsd4_encode_components_esc(xdr, ':', location->hosts,
						'[', ']');
	अगर (status)
		वापस status;
	status = nfsd4_encode_components(xdr, '/', location->path);
	अगर (status)
		वापस status;
	वापस 0;
पूर्ण

/*
 * Encode a path in RFC3530 'pathname4' क्रमmat
 */
अटल __be32 nfsd4_encode_path(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा path *root,
				स्थिर काष्ठा path *path)
अणु
	काष्ठा path cur = *path;
	__be32 *p;
	काष्ठा dentry **components = शून्य;
	अचिन्हित पूर्णांक ncomponents = 0;
	__be32 err = nfserr_jukebox;

	dprपूर्णांकk("nfsd4_encode_components(");

	path_get(&cur);
	/* First walk the path up to the nfsd root, and store the
	 * dentries/path components in an array.
	 */
	क्रम (;;) अणु
		अगर (path_equal(&cur, root))
			अवरोध;
		अगर (cur.dentry == cur.mnt->mnt_root) अणु
			अगर (follow_up(&cur))
				जारी;
			जाओ out_मुक्त;
		पूर्ण
		अगर ((ncomponents & 15) == 0) अणु
			काष्ठा dentry **new;
			new = kपुनः_स्मृति(components,
					माप(*new) * (ncomponents + 16),
					GFP_KERNEL);
			अगर (!new)
				जाओ out_मुक्त;
			components = new;
		पूर्ण
		components[ncomponents++] = cur.dentry;
		cur.dentry = dget_parent(cur.dentry);
	पूर्ण
	err = nfserr_resource;
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		जाओ out_मुक्त;
	*p++ = cpu_to_be32(ncomponents);

	जबतक (ncomponents) अणु
		काष्ठा dentry *dentry = components[ncomponents - 1];
		अचिन्हित पूर्णांक len;

		spin_lock(&dentry->d_lock);
		len = dentry->d_name.len;
		p = xdr_reserve_space(xdr, len + 4);
		अगर (!p) अणु
			spin_unlock(&dentry->d_lock);
			जाओ out_मुक्त;
		पूर्ण
		p = xdr_encode_opaque(p, dentry->d_name.name, len);
		dprपूर्णांकk("/%pd", dentry);
		spin_unlock(&dentry->d_lock);
		dput(dentry);
		ncomponents--;
	पूर्ण

	err = 0;
out_मुक्त:
	dprपूर्णांकk(")\n");
	जबतक (ncomponents)
		dput(components[--ncomponents]);
	kमुक्त(components);
	path_put(&cur);
	वापस err;
पूर्ण

अटल __be32 nfsd4_encode_fsloc_fsroot(काष्ठा xdr_stream *xdr,
			काष्ठा svc_rqst *rqstp, स्थिर काष्ठा path *path)
अणु
	काष्ठा svc_export *exp_ps;
	__be32 res;

	exp_ps = rqst_find_fsidzero_export(rqstp);
	अगर (IS_ERR(exp_ps))
		वापस nfsत्रुटि_सं(PTR_ERR(exp_ps));
	res = nfsd4_encode_path(xdr, &exp_ps->ex_path, path);
	exp_put(exp_ps);
	वापस res;
पूर्ण

/*
 *  encode a fs_locations काष्ठाure
 */
अटल __be32 nfsd4_encode_fs_locations(काष्ठा xdr_stream *xdr,
			काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp)
अणु
	__be32 status;
	पूर्णांक i;
	__be32 *p;
	काष्ठा nfsd4_fs_locations *fslocs = &exp->ex_fslocs;

	status = nfsd4_encode_fsloc_fsroot(xdr, rqstp, &exp->ex_path);
	अगर (status)
		वापस status;
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(fslocs->locations_count);
	क्रम (i=0; i<fslocs->locations_count; i++) अणु
		status = nfsd4_encode_fs_location4(xdr, &fslocs->locations[i]);
		अगर (status)
			वापस status;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 nfs4_file_type(umode_t mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFIFO:	वापस NF4FIFO;
	हाल S_IFCHR:	वापस NF4CHR;
	हाल S_IFसूची:	वापस NF4सूची;
	हाल S_IFBLK:	वापस NF4BLK;
	हाल S_IFLNK:	वापस NF4LNK;
	हाल S_IFREG:	वापस NF4REG;
	हाल S_IFSOCK:	वापस NF4SOCK;
	शेष:	वापस NF4BAD;
	पूर्ण
पूर्ण

अटल अंतरभूत __be32
nfsd4_encode_aclname(काष्ठा xdr_stream *xdr, काष्ठा svc_rqst *rqstp,
		     काष्ठा nfs4_ace *ace)
अणु
	अगर (ace->whotype != NFS4_ACL_WHO_NAMED)
		वापस nfs4_acl_ग_लिखो_who(xdr, ace->whotype);
	अन्यथा अगर (ace->flag & NFS4_ACE_IDENTIFIER_GROUP)
		वापस nfsd4_encode_group(xdr, rqstp, ace->who_gid);
	अन्यथा
		वापस nfsd4_encode_user(xdr, rqstp, ace->who_uid);
पूर्ण

अटल अंतरभूत __be32
nfsd4_encode_layout_types(काष्ठा xdr_stream *xdr, u32 layout_types)
अणु
	__be32		*p;
	अचिन्हित दीर्घ	i = hweight_दीर्घ(layout_types);

	p = xdr_reserve_space(xdr, 4 + 4 * i);
	अगर (!p)
		वापस nfserr_resource;

	*p++ = cpu_to_be32(i);

	क्रम (i = LAYOUT_NFSV4_1_खाताS; i < LAYOUT_TYPE_MAX; ++i)
		अगर (layout_types & (1 << i))
			*p++ = cpu_to_be32(i);

	वापस 0;
पूर्ण

#घोषणा WORD0_ABSENT_FS_ATTRS (FATTR4_WORD0_FS_LOCATIONS | FATTR4_WORD0_FSID | \
			      FATTR4_WORD0_RDATTR_ERROR)
#घोषणा WORD1_ABSENT_FS_ATTRS FATTR4_WORD1_MOUNTED_ON_खाताID
#घोषणा WORD2_ABSENT_FS_ATTRS 0

#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
अटल अंतरभूत __be32
nfsd4_encode_security_label(काष्ठा xdr_stream *xdr, काष्ठा svc_rqst *rqstp,
			    व्योम *context, पूर्णांक len)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, len + 4 + 4 + 4);
	अगर (!p)
		वापस nfserr_resource;

	/*
	 * For now we use a 0 here to indicate the null translation; in
	 * the future we may place a call to translation code here.
	 */
	*p++ = cpu_to_be32(0); /* lfs */
	*p++ = cpu_to_be32(0); /* pi */
	p = xdr_encode_opaque(p, context, len);
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत __be32
nfsd4_encode_security_label(काष्ठा xdr_stream *xdr, काष्ठा svc_rqst *rqstp,
			    व्योम *context, पूर्णांक len)
अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल __be32 fattr_handle_असलent_fs(u32 *bmval0, u32 *bmval1, u32 *bmval2, u32 *rdattr_err)
अणु
	/* As per referral draft:  */
	अगर (*bmval0 & ~WORD0_ABSENT_FS_ATTRS ||
	    *bmval1 & ~WORD1_ABSENT_FS_ATTRS) अणु
		अगर (*bmval0 & FATTR4_WORD0_RDATTR_ERROR ||
	            *bmval0 & FATTR4_WORD0_FS_LOCATIONS)
			*rdattr_err = NFSERR_MOVED;
		अन्यथा
			वापस nfserr_moved;
	पूर्ण
	*bmval0 &= WORD0_ABSENT_FS_ATTRS;
	*bmval1 &= WORD1_ABSENT_FS_ATTRS;
	*bmval2 &= WORD2_ABSENT_FS_ATTRS;
	वापस 0;
पूर्ण


अटल पूर्णांक get_parent_attributes(काष्ठा svc_export *exp, काष्ठा kstat *stat)
अणु
	काष्ठा path path = exp->ex_path;
	पूर्णांक err;

	path_get(&path);
	जबतक (follow_up(&path)) अणु
		अगर (path.dentry != path.mnt->mnt_root)
			अवरोध;
	पूर्ण
	err = vfs_getattr(&path, stat, STATX_BASIC_STATS, AT_STATX_SYNC_AS_STAT);
	path_put(&path);
	वापस err;
पूर्ण

अटल __be32
nfsd4_encode_biपंचांगap(काष्ठा xdr_stream *xdr, u32 bmval0, u32 bmval1, u32 bmval2)
अणु
	__be32 *p;

	अगर (bmval2) अणु
		p = xdr_reserve_space(xdr, 16);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(bmval0);
		*p++ = cpu_to_be32(bmval1);
		*p++ = cpu_to_be32(bmval2);
	पूर्ण अन्यथा अगर (bmval1) अणु
		p = xdr_reserve_space(xdr, 12);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(2);
		*p++ = cpu_to_be32(bmval0);
		*p++ = cpu_to_be32(bmval1);
	पूर्ण अन्यथा अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
		*p++ = cpu_to_be32(bmval0);
	पूर्ण

	वापस 0;
out_resource:
	वापस nfserr_resource;
पूर्ण

/*
 * Note: @fhp can be शून्य; in this हाल, we might have to compose the filehandle
 * ourselves.
 */
अटल __be32
nfsd4_encode_fattr(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp,
		काष्ठा svc_export *exp,
		काष्ठा dentry *dentry, u32 *bmval,
		काष्ठा svc_rqst *rqstp, पूर्णांक ignore_crossmnt)
अणु
	u32 bmval0 = bmval[0];
	u32 bmval1 = bmval[1];
	u32 bmval2 = bmval[2];
	काष्ठा kstat stat;
	काष्ठा svc_fh *tempfh = शून्य;
	काष्ठा kstatfs statfs;
	__be32 *p;
	पूर्णांक starting_len = xdr->buf->len;
	पूर्णांक attrlen_offset;
	__be32 attrlen;
	u32 dummy;
	u64 dummy64;
	u32 rdattr_err = 0;
	__be32 status;
	पूर्णांक err;
	काष्ठा nfs4_acl *acl = शून्य;
#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
	व्योम *context = शून्य;
	पूर्णांक contextlen;
#पूर्ण_अगर
	bool contextsupport = false;
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	u32 minorversion = resp->cstate.minorversion;
	काष्ठा path path = अणु
		.mnt	= exp->ex_path.mnt,
		.dentry	= dentry,
	पूर्ण;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	BUG_ON(bmval1 & NFSD_WRITEONLY_ATTRS_WORD1);
	BUG_ON(!nfsd_attrs_supported(minorversion, bmval));

	अगर (exp->ex_fslocs.migrated) अणु
		status = fattr_handle_असलent_fs(&bmval0, &bmval1, &bmval2, &rdattr_err);
		अगर (status)
			जाओ out;
	पूर्ण

	err = vfs_getattr(&path, &stat, STATX_BASIC_STATS, AT_STATX_SYNC_AS_STAT);
	अगर (err)
		जाओ out_nfserr;
	अगर ((bmval0 & (FATTR4_WORD0_खाताS_AVAIL | FATTR4_WORD0_खाताS_FREE |
			FATTR4_WORD0_खाताS_TOTAL | FATTR4_WORD0_MAXNAME)) ||
	    (bmval1 & (FATTR4_WORD1_SPACE_AVAIL | FATTR4_WORD1_SPACE_FREE |
		       FATTR4_WORD1_SPACE_TOTAL))) अणु
		err = vfs_statfs(&path, &statfs);
		अगर (err)
			जाओ out_nfserr;
	पूर्ण
	अगर ((bmval0 & (FATTR4_WORD0_खाताHANDLE | FATTR4_WORD0_FSID)) && !fhp) अणु
		tempfh = kदो_स्मृति(माप(काष्ठा svc_fh), GFP_KERNEL);
		status = nfserr_jukebox;
		अगर (!tempfh)
			जाओ out;
		fh_init(tempfh, NFS4_FHSIZE);
		status = fh_compose(tempfh, exp, dentry, शून्य);
		अगर (status)
			जाओ out;
		fhp = tempfh;
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_ACL) अणु
		err = nfsd4_get_nfs4_acl(rqstp, dentry, &acl);
		अगर (err == -EOPNOTSUPP)
			bmval0 &= ~FATTR4_WORD0_ACL;
		अन्यथा अगर (err == -EINVAL) अणु
			status = nfserr_attrnotsupp;
			जाओ out;
		पूर्ण अन्यथा अगर (err != 0)
			जाओ out_nfserr;
	पूर्ण

#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
	अगर ((bmval2 & FATTR4_WORD2_SECURITY_LABEL) ||
	     bmval0 & FATTR4_WORD0_SUPPORTED_ATTRS) अणु
		अगर (exp->ex_flags & NFSEXP_SECURITY_LABEL)
			err = security_inode_माला_लोecctx(d_inode(dentry),
						&context, &contextlen);
		अन्यथा
			err = -EOPNOTSUPP;
		contextsupport = (err == 0);
		अगर (bmval2 & FATTR4_WORD2_SECURITY_LABEL) अणु
			अगर (err == -EOPNOTSUPP)
				bmval2 &= ~FATTR4_WORD2_SECURITY_LABEL;
			अन्यथा अगर (err)
				जाओ out_nfserr;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_V4_SECURITY_LABEL */

	status = nfsd4_encode_biपंचांगap(xdr, bmval0, bmval1, bmval2);
	अगर (status)
		जाओ out;

	attrlen_offset = xdr->buf->len;
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		जाओ out_resource;
	p++;                /* to be backfilled later */

	अगर (bmval0 & FATTR4_WORD0_SUPPORTED_ATTRS) अणु
		u32 supp[3];

		स_नकल(supp, nfsd_suppattrs[minorversion], माप(supp));

		अगर (!IS_POSIXACL(dentry->d_inode))
			supp[0] &= ~FATTR4_WORD0_ACL;
		अगर (!contextsupport)
			supp[2] &= ~FATTR4_WORD2_SECURITY_LABEL;
		अगर (!supp[2]) अणु
			p = xdr_reserve_space(xdr, 12);
			अगर (!p)
				जाओ out_resource;
			*p++ = cpu_to_be32(2);
			*p++ = cpu_to_be32(supp[0]);
			*p++ = cpu_to_be32(supp[1]);
		पूर्ण अन्यथा अणु
			p = xdr_reserve_space(xdr, 16);
			अगर (!p)
				जाओ out_resource;
			*p++ = cpu_to_be32(3);
			*p++ = cpu_to_be32(supp[0]);
			*p++ = cpu_to_be32(supp[1]);
			*p++ = cpu_to_be32(supp[2]);
		पूर्ण
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_TYPE) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		dummy = nfs4_file_type(stat.mode);
		अगर (dummy == NF4BAD) अणु
			status = nfserr_serverfault;
			जाओ out;
		पूर्ण
		*p++ = cpu_to_be32(dummy);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_FH_EXPIRE_TYPE) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		अगर (exp->ex_flags & NFSEXP_NOSUBTREECHECK)
			*p++ = cpu_to_be32(NFS4_FH_PERSISTENT);
		अन्यथा
			*p++ = cpu_to_be32(NFS4_FH_PERSISTENT|
						NFS4_FH_VOL_RENAME);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_CHANGE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = encode_change(p, &stat, d_inode(dentry), exp);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_SIZE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, stat.size);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_LINK_SUPPORT) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_SYMLINK_SUPPORT) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_NAMED_ATTR) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(0);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_FSID) अणु
		p = xdr_reserve_space(xdr, 16);
		अगर (!p)
			जाओ out_resource;
		अगर (exp->ex_fslocs.migrated) अणु
			p = xdr_encode_hyper(p, NFS4_REFERRAL_FSID_MAJOR);
			p = xdr_encode_hyper(p, NFS4_REFERRAL_FSID_MINOR);
		पूर्ण अन्यथा चयन(fsid_source(fhp)) अणु
		हाल FSIDSOURCE_FSID:
			p = xdr_encode_hyper(p, (u64)exp->ex_fsid);
			p = xdr_encode_hyper(p, (u64)0);
			अवरोध;
		हाल FSIDSOURCE_DEV:
			*p++ = cpu_to_be32(0);
			*p++ = cpu_to_be32(MAJOR(stat.dev));
			*p++ = cpu_to_be32(0);
			*p++ = cpu_to_be32(MINOR(stat.dev));
			अवरोध;
		हाल FSIDSOURCE_UUID:
			p = xdr_encode_opaque_fixed(p, exp->ex_uuid,
								EX_UUID_LEN);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_UNIQUE_HANDLES) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(0);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_LEASE_TIME) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(nn->nfsd4_lease);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_RDATTR_ERROR) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(rdattr_err);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_ACL) अणु
		काष्ठा nfs4_ace *ace;

		अगर (acl == शून्य) अणु
			p = xdr_reserve_space(xdr, 4);
			अगर (!p)
				जाओ out_resource;

			*p++ = cpu_to_be32(0);
			जाओ out_acl;
		पूर्ण
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(acl->naces);

		क्रम (ace = acl->aces; ace < acl->aces + acl->naces; ace++) अणु
			p = xdr_reserve_space(xdr, 4*3);
			अगर (!p)
				जाओ out_resource;
			*p++ = cpu_to_be32(ace->type);
			*p++ = cpu_to_be32(ace->flag);
			*p++ = cpu_to_be32(ace->access_mask &
							NFS4_ACE_MASK_ALL);
			status = nfsd4_encode_aclname(xdr, rqstp, ace);
			अगर (status)
				जाओ out;
		पूर्ण
	पूर्ण
out_acl:
	अगर (bmval0 & FATTR4_WORD0_ACLSUPPORT) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(IS_POSIXACL(dentry->d_inode) ?
			ACL4_SUPPORT_ALLOW_ACL|ACL4_SUPPORT_DENY_ACL : 0);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_CANSETTIME) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_CASE_INSENSITIVE) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(0);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_CASE_PRESERVING) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_CHOWN_RESTRICTED) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_खाताHANDLE) अणु
		p = xdr_reserve_space(xdr, fhp->fh_handle.fh_size + 4);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_opaque(p, &fhp->fh_handle.fh_base,
					fhp->fh_handle.fh_size);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_खाताID) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, stat.ino);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_खाताS_AVAIL) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (u64) statfs.f_fमुक्त);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_खाताS_FREE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (u64) statfs.f_fमुक्त);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_खाताS_TOTAL) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (u64) statfs.f_files);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_FS_LOCATIONS) अणु
		status = nfsd4_encode_fs_locations(xdr, rqstp, exp);
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_HOMOGENEOUS) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_MAXखाताSIZE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, exp->ex_path.mnt->mnt_sb->s_maxbytes);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_MAXLINK) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(255);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_MAXNAME) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(statfs.f_namelen);
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_MAXREAD) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (u64) svc_max_payload(rqstp));
	पूर्ण
	अगर (bmval0 & FATTR4_WORD0_MAXWRITE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (u64) svc_max_payload(rqstp));
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_MODE) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(stat.mode & S_IALLUGO);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_NO_TRUNC) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(1);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_NUMLINKS) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(stat.nlink);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_OWNER) अणु
		status = nfsd4_encode_user(xdr, rqstp, stat.uid);
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_OWNER_GROUP) अणु
		status = nfsd4_encode_group(xdr, rqstp, stat.gid);
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_RAWDEV) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32((u32) MAJOR(stat.rdev));
		*p++ = cpu_to_be32((u32) MINOR(stat.rdev));
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_SPACE_AVAIL) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		dummy64 = (u64)statfs.f_bavail * (u64)statfs.f_bsize;
		p = xdr_encode_hyper(p, dummy64);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_SPACE_FREE) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		dummy64 = (u64)statfs.f_bमुक्त * (u64)statfs.f_bsize;
		p = xdr_encode_hyper(p, dummy64);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_SPACE_TOTAL) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		dummy64 = (u64)statfs.f_blocks * (u64)statfs.f_bsize;
		p = xdr_encode_hyper(p, dummy64);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_SPACE_USED) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			जाओ out_resource;
		dummy64 = (u64)stat.blocks << 9;
		p = xdr_encode_hyper(p, dummy64);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_TIME_ACCESS) अणु
		p = xdr_reserve_space(xdr, 12);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (s64)stat.aसमय.tv_sec);
		*p++ = cpu_to_be32(stat.aसमय.tv_nsec);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_TIME_DELTA) अणु
		p = xdr_reserve_space(xdr, 12);
		अगर (!p)
			जाओ out_resource;
		p = encode_समय_delta(p, d_inode(dentry));
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_TIME_METADATA) अणु
		p = xdr_reserve_space(xdr, 12);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (s64)stat.स_समय.tv_sec);
		*p++ = cpu_to_be32(stat.स_समय.tv_nsec);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_TIME_MODIFY) अणु
		p = xdr_reserve_space(xdr, 12);
		अगर (!p)
			जाओ out_resource;
		p = xdr_encode_hyper(p, (s64)stat.mसमय.tv_sec);
		*p++ = cpu_to_be32(stat.mसमय.tv_nsec);
	पूर्ण
	अगर (bmval1 & FATTR4_WORD1_MOUNTED_ON_खाताID) अणु
		काष्ठा kstat parent_stat;
		u64 ino = stat.ino;

		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
                	जाओ out_resource;
		/*
		 * Get parent's attributes अगर not ignoring crossmount
		 * and this is the root of a cross-mounted fileप्रणाली.
		 */
		अगर (ignore_crossmnt == 0 &&
		    dentry == exp->ex_path.mnt->mnt_root) अणु
			err = get_parent_attributes(exp, &parent_stat);
			अगर (err)
				जाओ out_nfserr;
			ino = parent_stat.ino;
		पूर्ण
		p = xdr_encode_hyper(p, ino);
	पूर्ण
#अगर_घोषित CONFIG_NFSD_PNFS
	अगर (bmval1 & FATTR4_WORD1_FS_LAYOUT_TYPES) अणु
		status = nfsd4_encode_layout_types(xdr, exp->ex_layout_types);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर (bmval2 & FATTR4_WORD2_LAYOUT_TYPES) अणु
		status = nfsd4_encode_layout_types(xdr, exp->ex_layout_types);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर (bmval2 & FATTR4_WORD2_LAYOUT_BLKSIZE) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		*p++ = cpu_to_be32(stat.blksize);
	पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */
	अगर (bmval2 & FATTR4_WORD2_SUPPATTR_EXCLCREAT) अणु
		u32 supp[3];

		स_नकल(supp, nfsd_suppattrs[minorversion], माप(supp));
		supp[0] &= NFSD_SUPPATTR_EXCLCREAT_WORD0;
		supp[1] &= NFSD_SUPPATTR_EXCLCREAT_WORD1;
		supp[2] &= NFSD_SUPPATTR_EXCLCREAT_WORD2;

		status = nfsd4_encode_biपंचांगap(xdr, supp[0], supp[1], supp[2]);
		अगर (status)
			जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
	अगर (bmval2 & FATTR4_WORD2_SECURITY_LABEL) अणु
		status = nfsd4_encode_security_label(xdr, rqstp, context,
								contextlen);
		अगर (status)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (bmval2 & FATTR4_WORD2_XATTR_SUPPORT) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			जाओ out_resource;
		err = xattr_supported_namespace(d_inode(dentry),
						XATTR_USER_PREFIX);
		*p++ = cpu_to_be32(err == 0);
	पूर्ण

	attrlen = htonl(xdr->buf->len - attrlen_offset - 4);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, attrlen_offset, &attrlen, 4);
	status = nfs_ok;

out:
#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
	अगर (context)
		security_release_secctx(context, contextlen);
#पूर्ण_अगर /* CONFIG_NFSD_V4_SECURITY_LABEL */
	kमुक्त(acl);
	अगर (tempfh) अणु
		fh_put(tempfh);
		kमुक्त(tempfh);
	पूर्ण
	अगर (status)
		xdr_truncate_encode(xdr, starting_len);
	वापस status;
out_nfserr:
	status = nfsत्रुटि_सं(err);
	जाओ out;
out_resource:
	status = nfserr_resource;
	जाओ out;
पूर्ण

अटल व्योम svcxdr_init_encode_from_buffer(काष्ठा xdr_stream *xdr,
				काष्ठा xdr_buf *buf, __be32 *p, पूर्णांक bytes)
अणु
	xdr->scratch.iov_len = 0;
	स_रखो(buf, 0, माप(काष्ठा xdr_buf));
	buf->head[0].iov_base = p;
	buf->head[0].iov_len = 0;
	buf->len = 0;
	xdr->buf = buf;
	xdr->iov = buf->head;
	xdr->p = p;
	xdr->end = (व्योम *)p + bytes;
	buf->buflen = bytes;
पूर्ण

__be32 nfsd4_encode_fattr_to_buf(__be32 **p, पूर्णांक words,
			काष्ठा svc_fh *fhp, काष्ठा svc_export *exp,
			काष्ठा dentry *dentry, u32 *bmval,
			काष्ठा svc_rqst *rqstp, पूर्णांक ignore_crossmnt)
अणु
	काष्ठा xdr_buf dummy;
	काष्ठा xdr_stream xdr;
	__be32 ret;

	svcxdr_init_encode_from_buffer(&xdr, &dummy, *p, words << 2);
	ret = nfsd4_encode_fattr(&xdr, fhp, exp, dentry, bmval, rqstp,
							ignore_crossmnt);
	*p = xdr.p;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक attributes_need_mount(u32 *bmval)
अणु
	अगर (bmval[0] & ~(FATTR4_WORD0_RDATTR_ERROR | FATTR4_WORD0_LEASE_TIME))
		वापस 1;
	अगर (bmval[1] & ~FATTR4_WORD1_MOUNTED_ON_खाताID)
		वापस 1;
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_dirent_fattr(काष्ठा xdr_stream *xdr, काष्ठा nfsd4_सूची_पढ़ो *cd,
			स्थिर अक्षर *name, पूर्णांक namlen)
अणु
	काष्ठा svc_export *exp = cd->rd_fhp->fh_export;
	काष्ठा dentry *dentry;
	__be32 nfserr;
	पूर्णांक ignore_crossmnt = 0;

	dentry = lookup_positive_unlocked(name, cd->rd_fhp->fh_dentry, namlen);
	अगर (IS_ERR(dentry))
		वापस nfsत्रुटि_सं(PTR_ERR(dentry));

	exp_get(exp);
	/*
	 * In the हाल of a mountpoपूर्णांक, the client may be asking क्रम
	 * attributes that are only properties of the underlying fileप्रणाली
	 * as opposed to the cross-mounted file प्रणाली. In such a हाल,
	 * we will not follow the cross mount and will fill the attribtutes
	 * directly from the mountpoपूर्णांक dentry.
	 */
	अगर (nfsd_mountpoपूर्णांक(dentry, exp)) अणु
		पूर्णांक err;

		अगर (!(exp->ex_flags & NFSEXP_V4ROOT)
				&& !attributes_need_mount(cd->rd_bmval)) अणु
			ignore_crossmnt = 1;
			जाओ out_encode;
		पूर्ण
		/*
		 * Why the heck aren't we just using nfsd_lookup??
		 * Dअगरferent "."/".." handling?  Something अन्यथा?
		 * At least, add a comment here to explain....
		 */
		err = nfsd_cross_mnt(cd->rd_rqstp, &dentry, &exp);
		अगर (err) अणु
			nfserr = nfsत्रुटि_सं(err);
			जाओ out_put;
		पूर्ण
		nfserr = check_nfsd_access(exp, cd->rd_rqstp);
		अगर (nfserr)
			जाओ out_put;

	पूर्ण
out_encode:
	nfserr = nfsd4_encode_fattr(xdr, शून्य, exp, dentry, cd->rd_bmval,
					cd->rd_rqstp, ignore_crossmnt);
out_put:
	dput(dentry);
	exp_put(exp);
	वापस nfserr;
पूर्ण

अटल __be32 *
nfsd4_encode_rdattr_error(काष्ठा xdr_stream *xdr, __be32 nfserr)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस शून्य;
	*p++ = htonl(2);
	*p++ = htonl(FATTR4_WORD0_RDATTR_ERROR); /* bmval0 */
	*p++ = htonl(0);			 /* bmval1 */

	*p++ = htonl(4);     /* attribute length */
	*p++ = nfserr;       /* no htonl */
	वापस p;
पूर्ण

अटल पूर्णांक
nfsd4_encode_dirent(व्योम *ccdv, स्थिर अक्षर *name, पूर्णांक namlen,
		    loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_cd *ccd = ccdv;
	काष्ठा nfsd4_सूची_पढ़ो *cd = container_of(ccd, काष्ठा nfsd4_सूची_पढ़ो, common);
	काष्ठा xdr_stream *xdr = cd->xdr;
	पूर्णांक start_offset = xdr->buf->len;
	पूर्णांक cookie_offset;
	u32 name_and_cookie;
	पूर्णांक entry_bytes;
	__be32 nfserr = nfserr_toosmall;
	__be64 wire_offset;
	__be32 *p;

	/* In nfsv4, "." and ".." never make it onto the wire.. */
	अगर (name && isकरोtent(name, namlen)) अणु
		cd->common.err = nfs_ok;
		वापस 0;
	पूर्ण

	अगर (cd->cookie_offset) अणु
		wire_offset = cpu_to_be64(offset);
		ग_लिखो_bytes_to_xdr_buf(xdr->buf, cd->cookie_offset,
							&wire_offset, 8);
	पूर्ण

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		जाओ fail;
	*p++ = xdr_one;                             /* mark entry present */
	cookie_offset = xdr->buf->len;
	p = xdr_reserve_space(xdr, 3*4 + namlen);
	अगर (!p)
		जाओ fail;
	p = xdr_encode_hyper(p, NFS_OFFSET_MAX);    /* offset of next entry */
	p = xdr_encode_array(p, name, namlen);      /* name length & name */

	nfserr = nfsd4_encode_dirent_fattr(xdr, cd, name, namlen);
	चयन (nfserr) अणु
	हाल nfs_ok:
		अवरोध;
	हाल nfserr_resource:
		nfserr = nfserr_toosmall;
		जाओ fail;
	हाल nfserr_noent:
		xdr_truncate_encode(xdr, start_offset);
		जाओ skip_entry;
	शेष:
		/*
		 * If the client requested the RDATTR_ERROR attribute,
		 * we stuff the error code पूर्णांकo this attribute
		 * and जारी.  If this attribute was not requested,
		 * then in accordance with the spec, we fail the
		 * entire READसूची operation(!)
		 */
		अगर (!(cd->rd_bmval[0] & FATTR4_WORD0_RDATTR_ERROR))
			जाओ fail;
		p = nfsd4_encode_rdattr_error(xdr, nfserr);
		अगर (p == शून्य) अणु
			nfserr = nfserr_toosmall;
			जाओ fail;
		पूर्ण
	पूर्ण
	nfserr = nfserr_toosmall;
	entry_bytes = xdr->buf->len - start_offset;
	अगर (entry_bytes > cd->rd_maxcount)
		जाओ fail;
	cd->rd_maxcount -= entry_bytes;
	/*
	 * RFC 3530 14.2.24 describes rd_dircount as only a "hint", so
	 * let's always let through the first entry, at least:
	 */
	अगर (!cd->rd_dircount)
		जाओ fail;
	name_and_cookie = 4 + 4 * XDR_QUADLEN(namlen) + 8;
	अगर (name_and_cookie > cd->rd_dircount && cd->cookie_offset)
		जाओ fail;
	cd->rd_dircount -= min(cd->rd_dircount, name_and_cookie);

	cd->cookie_offset = cookie_offset;
skip_entry:
	cd->common.err = nfs_ok;
	वापस 0;
fail:
	xdr_truncate_encode(xdr, start_offset);
	cd->common.err = nfserr;
	वापस -EINVAL;
पूर्ण

अटल __be32
nfsd4_encode_stateid(काष्ठा xdr_stream *xdr, stateid_t *sid)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, माप(stateid_t));
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(sid->si_generation);
	p = xdr_encode_opaque_fixed(p, &sid->si_opaque,
					माप(stateid_opaque_t));
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_access(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_access *access)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 8);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(access->ac_supported);
	*p++ = cpu_to_be32(access->ac_resp_access);
	वापस 0;
पूर्ण

अटल __be32 nfsd4_encode_bind_conn_to_session(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_bind_conn_to_session *bcts)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN + 8);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque_fixed(p, bcts->sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(bcts->dir);
	/* Upshअगरting from TCP to RDMA is not supported */
	*p++ = cpu_to_be32(0);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_बंद(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_बंद *बंद)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_encode_stateid(xdr, &बंद->cl_stateid);
पूर्ण


अटल __be32
nfsd4_encode_commit(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_commit *commit)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_VERIFIER_SIZE);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque_fixed(p, commit->co_verf.data,
						NFS4_VERIFIER_SIZE);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_create(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_create *create)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस nfserr_resource;
	encode_cinfo(p, &create->cr_cinfo);
	वापस nfsd4_encode_biपंचांगap(xdr, create->cr_bmval[0],
			create->cr_bmval[1], create->cr_bmval[2]);
पूर्ण

अटल __be32
nfsd4_encode_getattr(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_getattr *getattr)
अणु
	काष्ठा svc_fh *fhp = getattr->ga_fhp;
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_encode_fattr(xdr, fhp, fhp->fh_export, fhp->fh_dentry,
				    getattr->ga_bmval, resp->rqstp, 0);
पूर्ण

अटल __be32
nfsd4_encode_getfh(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा svc_fh **fhpp)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा svc_fh *fhp = *fhpp;
	अचिन्हित पूर्णांक len;
	__be32 *p;

	len = fhp->fh_handle.fh_size;
	p = xdr_reserve_space(xdr, len + 4);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque(p, &fhp->fh_handle.fh_base, len);
	वापस 0;
पूर्ण

/*
* Including all fields other than the name, a LOCK4denied काष्ठाure requires
*   8(clientid) + 4(namelen) + 8(offset) + 8(length) + 4(type) = 32 bytes.
*/
अटल __be32
nfsd4_encode_lock_denied(काष्ठा xdr_stream *xdr, काष्ठा nfsd4_lock_denied *ld)
अणु
	काष्ठा xdr_netobj *conf = &ld->ld_owner;
	__be32 *p;

again:
	p = xdr_reserve_space(xdr, 32 + XDR_LEN(conf->len));
	अगर (!p) अणु
		/*
		 * Don't fail to return the result just because we can't
		 * वापस the conflicting खोलो:
		 */
		अगर (conf->len) अणु
			kमुक्त(conf->data);
			conf->len = 0;
			conf->data = शून्य;
			जाओ again;
		पूर्ण
		वापस nfserr_resource;
	पूर्ण
	p = xdr_encode_hyper(p, ld->ld_start);
	p = xdr_encode_hyper(p, ld->ld_length);
	*p++ = cpu_to_be32(ld->ld_type);
	अगर (conf->len) अणु
		p = xdr_encode_opaque_fixed(p, &ld->ld_clientid, 8);
		p = xdr_encode_opaque(p, conf->data, conf->len);
		kमुक्त(conf->data);
	पूर्ण  अन्यथा अणु  /* non - nfsv4 lock in conflict, no clientid nor owner */
		p = xdr_encode_hyper(p, (u64)0); /* clientid */
		*p++ = cpu_to_be32(0); /* length of owner name */
	पूर्ण
	वापस nfserr_denied;
पूर्ण

अटल __be32
nfsd4_encode_lock(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_lock *lock)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	अगर (!nfserr)
		nfserr = nfsd4_encode_stateid(xdr, &lock->lk_resp_stateid);
	अन्यथा अगर (nfserr == nfserr_denied)
		nfserr = nfsd4_encode_lock_denied(xdr, &lock->lk_denied);

	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_lockt(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_lockt *lockt)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	अगर (nfserr == nfserr_denied)
		nfsd4_encode_lock_denied(xdr, &lockt->lt_denied);
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_locku(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_locku *locku)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_encode_stateid(xdr, &locku->lu_stateid);
पूर्ण


अटल __be32
nfsd4_encode_link(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_link *link)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस nfserr_resource;
	p = encode_cinfo(p, &link->li_cinfo);
	वापस 0;
पूर्ण


अटल __be32
nfsd4_encode_खोलो(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	nfserr = nfsd4_encode_stateid(xdr, &खोलो->op_stateid);
	अगर (nfserr)
		वापस nfserr;
	p = xdr_reserve_space(xdr, 24);
	अगर (!p)
		वापस nfserr_resource;
	p = encode_cinfo(p, &खोलो->op_cinfo);
	*p++ = cpu_to_be32(खोलो->op_rflags);

	nfserr = nfsd4_encode_biपंचांगap(xdr, खोलो->op_bmval[0], खोलो->op_bmval[1],
					खोलो->op_bmval[2]);
	अगर (nfserr)
		वापस nfserr;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;

	*p++ = cpu_to_be32(खोलो->op_delegate_type);
	चयन (खोलो->op_delegate_type) अणु
	हाल NFS4_OPEN_DELEGATE_NONE:
		अवरोध;
	हाल NFS4_OPEN_DELEGATE_READ:
		nfserr = nfsd4_encode_stateid(xdr, &खोलो->op_delegate_stateid);
		अगर (nfserr)
			वापस nfserr;
		p = xdr_reserve_space(xdr, 20);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(खोलो->op_recall);

		/*
		 * TODO: ACE's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);   /* XXX: is शून्य principal ok? */
		अवरोध;
	हाल NFS4_OPEN_DELEGATE_WRITE:
		nfserr = nfsd4_encode_stateid(xdr, &खोलो->op_delegate_stateid);
		अगर (nfserr)
			वापस nfserr;
		p = xdr_reserve_space(xdr, 32);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(0);

		/*
		 * TODO: space_limit's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_LIMIT_SIZE);
		*p++ = cpu_to_be32(~(u32)0);
		*p++ = cpu_to_be32(~(u32)0);

		/*
		 * TODO: ACE's in delegations
		 */
		*p++ = cpu_to_be32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);   /* XXX: is शून्य principal ok? */
		अवरोध;
	हाल NFS4_OPEN_DELEGATE_NONE_EXT: /* 4.1 */
		चयन (खोलो->op_why_no_deleg) अणु
		हाल WND4_CONTENTION:
		हाल WND4_RESOURCE:
			p = xdr_reserve_space(xdr, 8);
			अगर (!p)
				वापस nfserr_resource;
			*p++ = cpu_to_be32(खोलो->op_why_no_deleg);
			/* deleg संकेतing not supported yet: */
			*p++ = cpu_to_be32(0);
			अवरोध;
		शेष:
			p = xdr_reserve_space(xdr, 4);
			अगर (!p)
				वापस nfserr_resource;
			*p++ = cpu_to_be32(खोलो->op_why_no_deleg);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	/* XXX save filehandle here */
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_खोलो_confirm(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_खोलो_confirm *oc)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_encode_stateid(xdr, &oc->oc_resp_stateid);
पूर्ण

अटल __be32
nfsd4_encode_खोलो_करोwngrade(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_खोलो_करोwngrade *od)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_encode_stateid(xdr, &od->od_stateid);
पूर्ण

अटल __be32 nfsd4_encode_splice_पढ़ो(
				काष्ठा nfsd4_compoundres *resp,
				काष्ठा nfsd4_पढ़ो *पढ़ो,
				काष्ठा file *file, अचिन्हित दीर्घ maxcount)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा xdr_buf *buf = xdr->buf;
	पूर्णांक status, space_left;
	u32 eof;
	__be32 nfserr;
	__be32 *p = xdr->p - 2;

	/* Make sure there will be room क्रम padding अगर needed */
	अगर (xdr->end - xdr->p < 1)
		वापस nfserr_resource;

	nfserr = nfsd_splice_पढ़ो(पढ़ो->rd_rqstp, पढ़ो->rd_fhp,
				  file, पढ़ो->rd_offset, &maxcount, &eof);
	पढ़ो->rd_length = maxcount;
	अगर (nfserr)
		जाओ out_err;
	status = svc_encode_result_payload(पढ़ो->rd_rqstp,
					   buf->head[0].iov_len, maxcount);
	अगर (status) अणु
		nfserr = nfsत्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	*(p++) = htonl(eof);
	*(p++) = htonl(maxcount);

	buf->page_len = maxcount;
	buf->len += maxcount;
	xdr->page_ptr += (buf->page_base + maxcount + PAGE_SIZE - 1)
							/ PAGE_SIZE;

	/* Use rest of head क्रम padding and reमुख्यing ops: */
	buf->tail[0].iov_base = xdr->p;
	buf->tail[0].iov_len = 0;
	xdr->iov = buf->tail;
	अगर (maxcount&3) अणु
		पूर्णांक pad = 4 - (maxcount&3);

		*(xdr->p++) = 0;

		buf->tail[0].iov_base += maxcount&3;
		buf->tail[0].iov_len = pad;
		buf->len += pad;
	पूर्ण

	space_left = min_t(पूर्णांक, (व्योम *)xdr->end - (व्योम *)xdr->p,
				buf->buflen - buf->len);
	buf->buflen = buf->len + space_left;
	xdr->end = (__be32 *)((व्योम *)xdr->end + space_left);

	वापस 0;

out_err:
	/*
	 * nfsd_splice_actor may have alपढ़ोy messed with the
	 * page length; reset it so as not to confuse
	 * xdr_truncate_encode in our caller.
	 */
	buf->page_len = 0;
	वापस nfserr;
पूर्ण

अटल __be32 nfsd4_encode_पढ़ोv(काष्ठा nfsd4_compoundres *resp,
				 काष्ठा nfsd4_पढ़ो *पढ़ो,
				 काष्ठा file *file, अचिन्हित दीर्घ maxcount)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	u32 eof;
	पूर्णांक starting_len = xdr->buf->len - 8;
	__be32 nfserr;
	__be32 पंचांगp;
	पूर्णांक pad;

	पढ़ो->rd_vlen = xdr_reserve_space_vec(xdr, resp->rqstp->rq_vec, maxcount);
	अगर (पढ़ो->rd_vlen < 0)
		वापस nfserr_resource;

	nfserr = nfsd_पढ़ोv(resp->rqstp, पढ़ो->rd_fhp, file, पढ़ो->rd_offset,
			    resp->rqstp->rq_vec, पढ़ो->rd_vlen, &maxcount,
			    &eof);
	पढ़ो->rd_length = maxcount;
	अगर (nfserr)
		वापस nfserr;
	अगर (svc_encode_result_payload(resp->rqstp, starting_len + 8, maxcount))
		वापस nfserr_io;
	xdr_truncate_encode(xdr, starting_len + 8 + xdr_align_size(maxcount));

	पंचांगp = htonl(eof);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len    , &पंचांगp, 4);
	पंचांगp = htonl(maxcount);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 4, &पंचांगp, 4);

	पंचांगp = xdr_zero;
	pad = (maxcount&3) ? 4 - (maxcount&3) : 0;
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 8 + maxcount,
								&पंचांगp, pad);
	वापस 0;

पूर्ण

अटल __be32
nfsd4_encode_पढ़ो(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		  काष्ठा nfsd4_पढ़ो *पढ़ो)
अणु
	अचिन्हित दीर्घ maxcount;
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा file *file;
	पूर्णांक starting_len = xdr->buf->len;
	__be32 *p;

	अगर (nfserr)
		वापस nfserr;
	file = पढ़ो->rd_nf->nf_file;

	p = xdr_reserve_space(xdr, 8); /* eof flag and byte count */
	अगर (!p) अणु
		WARN_ON_ONCE(test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags));
		वापस nfserr_resource;
	पूर्ण
	अगर (resp->xdr->buf->page_len &&
	    test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags)) अणु
		WARN_ON_ONCE(1);
		वापस nfserr_resource;
	पूर्ण
	xdr_commit_encode(xdr);

	maxcount = svc_max_payload(resp->rqstp);
	maxcount = min_t(अचिन्हित दीर्घ, maxcount,
			 (xdr->buf->buflen - xdr->buf->len));
	maxcount = min_t(अचिन्हित दीर्घ, maxcount, पढ़ो->rd_length);

	अगर (file->f_op->splice_पढ़ो &&
	    test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags))
		nfserr = nfsd4_encode_splice_पढ़ो(resp, पढ़ो, file, maxcount);
	अन्यथा
		nfserr = nfsd4_encode_पढ़ोv(resp, पढ़ो, file, maxcount);

	अगर (nfserr)
		xdr_truncate_encode(xdr, starting_len);

	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_पढ़ोlink(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_पढ़ोlink *पढ़ोlink)
अणु
	पूर्णांक maxcount;
	__be32 wire_count;
	पूर्णांक zero = 0;
	काष्ठा xdr_stream *xdr = resp->xdr;
	पूर्णांक length_offset = xdr->buf->len;
	पूर्णांक status;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	maxcount = PAGE_SIZE;

	p = xdr_reserve_space(xdr, maxcount);
	अगर (!p)
		वापस nfserr_resource;
	/*
	 * XXX: By शेष, vfs_पढ़ोlink() will truncate symlinks अगर they
	 * would overflow the buffer.  Is this kosher in NFSv4?  If not, one
	 * easy fix is: अगर vfs_पढ़ोlink() precisely fills the buffer, assume
	 * that truncation occurred, and वापस NFS4ERR_RESOURCE.
	 */
	nfserr = nfsd_पढ़ोlink(पढ़ोlink->rl_rqstp, पढ़ोlink->rl_fhp,
						(अक्षर *)p, &maxcount);
	अगर (nfserr == nfserr_isdir)
		nfserr = nfserr_inval;
	अगर (nfserr)
		जाओ out_err;
	status = svc_encode_result_payload(पढ़ोlink->rl_rqstp, length_offset,
					   maxcount);
	अगर (status) अणु
		nfserr = nfsत्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	wire_count = htonl(maxcount);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, length_offset, &wire_count, 4);
	xdr_truncate_encode(xdr, length_offset + 4 + ALIGN(maxcount, 4));
	अगर (maxcount & 3)
		ग_लिखो_bytes_to_xdr_buf(xdr->buf, length_offset + 4 + maxcount,
						&zero, 4 - (maxcount&3));
	वापस 0;

out_err:
	xdr_truncate_encode(xdr, length_offset);
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_सूची_पढ़ो(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_सूची_पढ़ो *सूची_पढ़ो)
अणु
	पूर्णांक maxcount;
	पूर्णांक bytes_left;
	loff_t offset;
	__be64 wire_offset;
	काष्ठा xdr_stream *xdr = resp->xdr;
	पूर्णांक starting_len = xdr->buf->len;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_VERIFIER_SIZE);
	अगर (!p)
		वापस nfserr_resource;

	/* XXX: Following NFSv3, we ignore the READसूची verअगरier क्रम now. */
	*p++ = cpu_to_be32(0);
	*p++ = cpu_to_be32(0);
	xdr->buf->head[0].iov_len = (अक्षर *)xdr->p -
				    (अक्षर *)xdr->buf->head[0].iov_base;

	/*
	 * Number of bytes left क्रम directory entries allowing क्रम the
	 * final 8 bytes of the सूची_पढ़ो and a following failed op:
	 */
	bytes_left = xdr->buf->buflen - xdr->buf->len
			- COMPOUND_ERR_SLACK_SPACE - 8;
	अगर (bytes_left < 0) अणु
		nfserr = nfserr_resource;
		जाओ err_no_verf;
	पूर्ण
	maxcount = svc_max_payload(resp->rqstp);
	maxcount = min_t(u32, सूची_पढ़ो->rd_maxcount, maxcount);
	/*
	 * Note the rfc defines rd_maxcount as the size of the
	 * READसूची4resok काष्ठाure, which includes the verअगरier above
	 * and the 8 bytes encoded at the end of this function:
	 */
	अगर (maxcount < 16) अणु
		nfserr = nfserr_toosmall;
		जाओ err_no_verf;
	पूर्ण
	maxcount = min_t(पूर्णांक, maxcount-16, bytes_left);

	/* RFC 3530 14.2.24 allows us to ignore dircount when it's 0: */
	अगर (!सूची_पढ़ो->rd_dircount)
		सूची_पढ़ो->rd_dircount = svc_max_payload(resp->rqstp);

	सूची_पढ़ो->xdr = xdr;
	सूची_पढ़ो->rd_maxcount = maxcount;
	सूची_पढ़ो->common.err = 0;
	सूची_पढ़ो->cookie_offset = 0;

	offset = सूची_पढ़ो->rd_cookie;
	nfserr = nfsd_सूची_पढ़ो(सूची_पढ़ो->rd_rqstp, सूची_पढ़ो->rd_fhp,
			      &offset,
			      &सूची_पढ़ो->common, nfsd4_encode_dirent);
	अगर (nfserr == nfs_ok &&
	    सूची_पढ़ो->common.err == nfserr_toosmall &&
	    xdr->buf->len == starting_len + 8) अणु
		/* nothing encoded; which limit did we hit?: */
		अगर (maxcount - 16 < bytes_left)
			/* It was the fault of rd_maxcount: */
			nfserr = nfserr_toosmall;
		अन्यथा
			/* We ran out of buffer space: */
			nfserr = nfserr_resource;
	पूर्ण
	अगर (nfserr)
		जाओ err_no_verf;

	अगर (सूची_पढ़ो->cookie_offset) अणु
		wire_offset = cpu_to_be64(offset);
		ग_लिखो_bytes_to_xdr_buf(xdr->buf, सूची_पढ़ो->cookie_offset,
							&wire_offset, 8);
	पूर्ण

	p = xdr_reserve_space(xdr, 8);
	अगर (!p) अणु
		WARN_ON_ONCE(1);
		जाओ err_no_verf;
	पूर्ण
	*p++ = 0;	/* no more entries */
	*p++ = htonl(सूची_पढ़ो->common.err == nfserr_eof);

	वापस 0;
err_no_verf:
	xdr_truncate_encode(xdr, starting_len);
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_हटाओ(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_हटाओ *हटाओ)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस nfserr_resource;
	p = encode_cinfo(p, &हटाओ->rm_cinfo);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_नाम(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_नाम *नाम)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 40);
	अगर (!p)
		वापस nfserr_resource;
	p = encode_cinfo(p, &नाम->rn_sinfo);
	p = encode_cinfo(p, &नाम->rn_tinfo);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_करो_encode_secinfo(काष्ठा xdr_stream *xdr, काष्ठा svc_export *exp)
अणु
	u32 i, nflavs, supported;
	काष्ठा exp_flavor_info *flavs;
	काष्ठा exp_flavor_info def_flavs[2];
	__be32 *p, *flavorsp;
	अटल bool report = true;

	अगर (exp->ex_nflavors) अणु
		flavs = exp->ex_flavors;
		nflavs = exp->ex_nflavors;
	पूर्ण अन्यथा अणु /* Handling of some शेषs in असलence of real secinfo: */
		flavs = def_flavs;
		अगर (exp->ex_client->flavour->flavour == RPC_AUTH_UNIX) अणु
			nflavs = 2;
			flavs[0].pseuकरोflavor = RPC_AUTH_UNIX;
			flavs[1].pseuकरोflavor = RPC_AUTH_शून्य;
		पूर्ण अन्यथा अगर (exp->ex_client->flavour->flavour == RPC_AUTH_GSS) अणु
			nflavs = 1;
			flavs[0].pseuकरोflavor
					= svcauth_gss_flavor(exp->ex_client);
		पूर्ण अन्यथा अणु
			nflavs = 1;
			flavs[0].pseuकरोflavor
					= exp->ex_client->flavour->flavour;
		पूर्ण
	पूर्ण

	supported = 0;
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	flavorsp = p++;		/* to be backfilled later */

	क्रम (i = 0; i < nflavs; i++) अणु
		rpc_authflavor_t pf = flavs[i].pseuकरोflavor;
		काष्ठा rpcsec_gss_info info;

		अगर (rpcauth_get_gssinfo(pf, &info) == 0) अणु
			supported++;
			p = xdr_reserve_space(xdr, 4 + 4 +
					      XDR_LEN(info.oid.len) + 4 + 4);
			अगर (!p)
				वापस nfserr_resource;
			*p++ = cpu_to_be32(RPC_AUTH_GSS);
			p = xdr_encode_opaque(p,  info.oid.data, info.oid.len);
			*p++ = cpu_to_be32(info.qop);
			*p++ = cpu_to_be32(info.service);
		पूर्ण अन्यथा अगर (pf < RPC_AUTH_MAXFLAVOR) अणु
			supported++;
			p = xdr_reserve_space(xdr, 4);
			अगर (!p)
				वापस nfserr_resource;
			*p++ = cpu_to_be32(pf);
		पूर्ण अन्यथा अणु
			अगर (report)
				pr_warn("NFS: SECINFO: security flavor %u "
					"is not supported\n", pf);
		पूर्ण
	पूर्ण

	अगर (nflavs != supported)
		report = false;
	*flavorsp = htonl(supported);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_secinfo(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		     काष्ठा nfsd4_secinfo *secinfo)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_करो_encode_secinfo(xdr, secinfo->si_exp);
पूर्ण

अटल __be32
nfsd4_encode_secinfo_no_name(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		     काष्ठा nfsd4_secinfo_no_name *secinfo)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;

	वापस nfsd4_करो_encode_secinfo(xdr, secinfo->sin_exp);
पूर्ण

/*
 * The SETATTR encode routine is special -- it always encodes a biपंचांगap,
 * regardless of the error status.
 */
अटल __be32
nfsd4_encode_setattr(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_setattr *setattr)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 16);
	अगर (!p)
		वापस nfserr_resource;
	अगर (nfserr) अणु
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
	पूर्ण
	अन्यथा अणु
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(setattr->sa_bmval[0]);
		*p++ = cpu_to_be32(setattr->sa_bmval[1]);
		*p++ = cpu_to_be32(setattr->sa_bmval[2]);
	पूर्ण
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_setclientid(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_setclientid *scd)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	अगर (!nfserr) अणु
		p = xdr_reserve_space(xdr, 8 + NFS4_VERIFIER_SIZE);
		अगर (!p)
			वापस nfserr_resource;
		p = xdr_encode_opaque_fixed(p, &scd->se_clientid, 8);
		p = xdr_encode_opaque_fixed(p, &scd->se_confirm,
						NFS4_VERIFIER_SIZE);
	पूर्ण
	अन्यथा अगर (nfserr == nfserr_clid_inuse) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
	पूर्ण
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_ग_लिखो(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, काष्ठा nfsd4_ग_लिखो *ग_लिखो)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 16);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(ग_लिखो->wr_bytes_written);
	*p++ = cpu_to_be32(ग_लिखो->wr_how_written);
	p = xdr_encode_opaque_fixed(p, ग_लिखो->wr_verअगरier.data,
						NFS4_VERIFIER_SIZE);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_exchange_id(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			 काष्ठा nfsd4_exchange_id *exid)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;
	अक्षर *major_id;
	अक्षर *server_scope;
	पूर्णांक major_id_sz;
	पूर्णांक server_scope_sz;
	uपूर्णांक64_t minor_id = 0;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(resp->rqstp), nfsd_net_id);

	major_id = nn->nfsd_name;
	major_id_sz = म_माप(nn->nfsd_name);
	server_scope = nn->nfsd_name;
	server_scope_sz = म_माप(nn->nfsd_name);

	p = xdr_reserve_space(xdr,
		8 /* eir_clientid */ +
		4 /* eir_sequenceid */ +
		4 /* eir_flags */ +
		4 /* spr_how */);
	अगर (!p)
		वापस nfserr_resource;

	p = xdr_encode_opaque_fixed(p, &exid->clientid, 8);
	*p++ = cpu_to_be32(exid->seqid);
	*p++ = cpu_to_be32(exid->flags);

	*p++ = cpu_to_be32(exid->spa_how);

	चयन (exid->spa_how) अणु
	हाल SP4_NONE:
		अवरोध;
	हाल SP4_MACH_CRED:
		/* spo_must_enक्रमce biपंचांगap: */
		nfserr = nfsd4_encode_biपंचांगap(xdr,
					exid->spo_must_enक्रमce[0],
					exid->spo_must_enक्रमce[1],
					exid->spo_must_enक्रमce[2]);
		अगर (nfserr)
			वापस nfserr;
		/* spo_must_allow biपंचांगap: */
		nfserr = nfsd4_encode_biपंचांगap(xdr,
					exid->spo_must_allow[0],
					exid->spo_must_allow[1],
					exid->spo_must_allow[2]);
		अगर (nfserr)
			वापस nfserr;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	p = xdr_reserve_space(xdr,
		8 /* so_minor_id */ +
		4 /* so_major_id.len */ +
		(XDR_QUADLEN(major_id_sz) * 4) +
		4 /* eir_server_scope.len */ +
		(XDR_QUADLEN(server_scope_sz) * 4) +
		4 /* eir_server_impl_id.count (0) */);
	अगर (!p)
		वापस nfserr_resource;

	/* The server_owner काष्ठा */
	p = xdr_encode_hyper(p, minor_id);      /* Minor id */
	/* major id */
	p = xdr_encode_opaque(p, major_id, major_id_sz);

	/* Server scope */
	p = xdr_encode_opaque(p, server_scope, server_scope_sz);

	/* Implementation id */
	*p++ = cpu_to_be32(0);	/* zero length nfs_impl_id4 array */
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_create_session(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			    काष्ठा nfsd4_create_session *sess)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 24);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque_fixed(p, sess->sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(sess->seqid);
	*p++ = cpu_to_be32(sess->flags);

	p = xdr_reserve_space(xdr, 28);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(0); /* headerpadsz */
	*p++ = cpu_to_be32(sess->क्रमe_channel.maxreq_sz);
	*p++ = cpu_to_be32(sess->क्रमe_channel.maxresp_sz);
	*p++ = cpu_to_be32(sess->क्रमe_channel.maxresp_cached);
	*p++ = cpu_to_be32(sess->क्रमe_channel.maxops);
	*p++ = cpu_to_be32(sess->क्रमe_channel.maxreqs);
	*p++ = cpu_to_be32(sess->क्रमe_channel.nr_rdma_attrs);

	अगर (sess->क्रमe_channel.nr_rdma_attrs) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(sess->क्रमe_channel.rdma_attrs);
	पूर्ण

	p = xdr_reserve_space(xdr, 28);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(0); /* headerpadsz */
	*p++ = cpu_to_be32(sess->back_channel.maxreq_sz);
	*p++ = cpu_to_be32(sess->back_channel.maxresp_sz);
	*p++ = cpu_to_be32(sess->back_channel.maxresp_cached);
	*p++ = cpu_to_be32(sess->back_channel.maxops);
	*p++ = cpu_to_be32(sess->back_channel.maxreqs);
	*p++ = cpu_to_be32(sess->back_channel.nr_rdma_attrs);

	अगर (sess->back_channel.nr_rdma_attrs) अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(sess->back_channel.rdma_attrs);
	पूर्ण
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_sequence(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		      काष्ठा nfsd4_sequence *seq)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN + 20);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_opaque_fixed(p, seq->sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(seq->seqid);
	*p++ = cpu_to_be32(seq->slotid);
	/* Note slotid's are numbered from zero: */
	*p++ = cpu_to_be32(seq->maxslots - 1); /* sr_highest_slotid */
	*p++ = cpu_to_be32(seq->maxslots - 1); /* sr_target_highest_slotid */
	*p++ = cpu_to_be32(seq->status_flags);

	resp->cstate.data_offset = xdr->buf->len; /* DRC cache data poपूर्णांकer */
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_test_stateid(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			  काष्ठा nfsd4_test_stateid *test_stateid)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा nfsd4_test_stateid_id *stateid, *next;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + (4 * test_stateid->ts_num_ids));
	अगर (!p)
		वापस nfserr_resource;
	*p++ = htonl(test_stateid->ts_num_ids);

	list_क्रम_each_entry_safe(stateid, next, &test_stateid->ts_stateid_list, ts_id_list) अणु
		*p++ = stateid->ts_id_status;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
अटल __be32
nfsd4_encode_getdeviceinfo(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		काष्ठा nfsd4_getdeviceinfo *gdev)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	स्थिर काष्ठा nfsd4_layout_ops *ops;
	u32 starting_len = xdr->buf->len, needed_len;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;

	*p++ = cpu_to_be32(gdev->gd_layout_type);

	/* If maxcount is 0 then just update notअगरications */
	अगर (gdev->gd_maxcount != 0) अणु
		ops = nfsd4_layout_ops[gdev->gd_layout_type];
		nfserr = ops->encode_getdeviceinfo(xdr, gdev);
		अगर (nfserr) अणु
			/*
			 * We करोn't bother to burden the layout drivers with
			 * enक्रमcing gd_maxcount, just tell the client to
			 * come back with a bigger buffer अगर it's not enough.
			 */
			अगर (xdr->buf->len + 4 > gdev->gd_maxcount)
				जाओ toosmall;
			वापस nfserr;
		पूर्ण
	पूर्ण

	अगर (gdev->gd_notअगरy_types) अणु
		p = xdr_reserve_space(xdr, 4 + 4);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = cpu_to_be32(1);			/* biपंचांगap length */
		*p++ = cpu_to_be32(gdev->gd_notअगरy_types);
	पूर्ण अन्यथा अणु
		p = xdr_reserve_space(xdr, 4);
		अगर (!p)
			वापस nfserr_resource;
		*p++ = 0;
	पूर्ण

	वापस 0;
toosmall:
	dprपूर्णांकk("%s: maxcount too small\n", __func__);
	needed_len = xdr->buf->len + 4 /* notअगरications */;
	xdr_truncate_encode(xdr, starting_len);
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(needed_len);
	वापस nfserr_toosmall;
पूर्ण

अटल __be32
nfsd4_encode_layoutget(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		काष्ठा nfsd4_layoutget *lgp)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	स्थिर काष्ठा nfsd4_layout_ops *ops;
	__be32 *p;

	p = xdr_reserve_space(xdr, 36 + माप(stateid_opaque_t));
	अगर (!p)
		वापस nfserr_resource;

	*p++ = cpu_to_be32(1);	/* we always set वापस-on-बंद */
	*p++ = cpu_to_be32(lgp->lg_sid.si_generation);
	p = xdr_encode_opaque_fixed(p, &lgp->lg_sid.si_opaque,
				    माप(stateid_opaque_t));

	*p++ = cpu_to_be32(1);	/* we always वापस a single layout */
	p = xdr_encode_hyper(p, lgp->lg_seg.offset);
	p = xdr_encode_hyper(p, lgp->lg_seg.length);
	*p++ = cpu_to_be32(lgp->lg_seg.iomode);
	*p++ = cpu_to_be32(lgp->lg_layout_type);

	ops = nfsd4_layout_ops[lgp->lg_layout_type];
	वापस ops->encode_layoutget(xdr, lgp);
पूर्ण

अटल __be32
nfsd4_encode_layoutcommit(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			  काष्ठा nfsd4_layoutcommit *lcp)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(lcp->lc_size_chg);
	अगर (lcp->lc_size_chg) अणु
		p = xdr_reserve_space(xdr, 8);
		अगर (!p)
			वापस nfserr_resource;
		p = xdr_encode_hyper(p, lcp->lc_newsize);
	पूर्ण

	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_layoutवापस(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		काष्ठा nfsd4_layoutवापस *lrp)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;
	*p++ = cpu_to_be32(lrp->lrs_present);
	अगर (lrp->lrs_present)
		वापस nfsd4_encode_stateid(xdr, &lrp->lr_sid);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

अटल __be32
nfsd42_encode_ग_लिखो_res(काष्ठा nfsd4_compoundres *resp,
		काष्ठा nfsd42_ग_लिखो_res *ग_लिखो, bool sync)
अणु
	__be32 *p;
	p = xdr_reserve_space(resp->xdr, 4);
	अगर (!p)
		वापस nfserr_resource;

	अगर (sync)
		*p++ = cpu_to_be32(0);
	अन्यथा अणु
		__be32 nfserr;
		*p++ = cpu_to_be32(1);
		nfserr = nfsd4_encode_stateid(resp->xdr, &ग_लिखो->cb_stateid);
		अगर (nfserr)
			वापस nfserr;
	पूर्ण
	p = xdr_reserve_space(resp->xdr, 8 + 4 + NFS4_VERIFIER_SIZE);
	अगर (!p)
		वापस nfserr_resource;

	p = xdr_encode_hyper(p, ग_लिखो->wr_bytes_written);
	*p++ = cpu_to_be32(ग_लिखो->wr_stable_how);
	p = xdr_encode_opaque_fixed(p, ग_लिखो->wr_verअगरier.data,
				    NFS4_VERIFIER_SIZE);
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd42_encode_nl4_server(काष्ठा nfsd4_compoundres *resp, काष्ठा nl4_server *ns)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा nfs42_netaddr *addr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p++ = cpu_to_be32(ns->nl4_type);

	चयन (ns->nl4_type) अणु
	हाल NL4_NETADDR:
		addr = &ns->u.nl4_addr;

		/* netid_len, netid, uaddr_len, uaddr (port included
		 * in RPCBIND_MAXUADDRLEN)
		 */
		p = xdr_reserve_space(xdr,
			4 /* netid len */ +
			(XDR_QUADLEN(addr->netid_len) * 4) +
			4 /* uaddr len */ +
			(XDR_QUADLEN(addr->addr_len) * 4));
		अगर (!p)
			वापस nfserr_resource;

		*p++ = cpu_to_be32(addr->netid_len);
		p = xdr_encode_opaque_fixed(p, addr->netid,
					    addr->netid_len);
		*p++ = cpu_to_be32(addr->addr_len);
		p = xdr_encode_opaque_fixed(p, addr->addr,
					addr->addr_len);
		अवरोध;
	शेष:
		WARN_ON_ONCE(ns->nl4_type != NL4_NETADDR);
		वापस nfserr_inval;
	पूर्ण

	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_copy(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		  काष्ठा nfsd4_copy *copy)
अणु
	__be32 *p;

	nfserr = nfsd42_encode_ग_लिखो_res(resp, &copy->cp_res,
					 !!copy->cp_synchronous);
	अगर (nfserr)
		वापस nfserr;

	p = xdr_reserve_space(resp->xdr, 4 + 4);
	*p++ = xdr_one; /* cr_consecutive */
	*p++ = cpu_to_be32(copy->cp_synchronous);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_offload_status(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			    काष्ठा nfsd4_offload_status *os)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 8 + 4);
	अगर (!p)
		वापस nfserr_resource;
	p = xdr_encode_hyper(p, os->count);
	*p++ = cpu_to_be32(0);
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_पढ़ो_plus_data(काष्ठा nfsd4_compoundres *resp,
			    काष्ठा nfsd4_पढ़ो *पढ़ो,
			    अचिन्हित दीर्घ *maxcount, u32 *eof,
			    loff_t *pos)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा file *file = पढ़ो->rd_nf->nf_file;
	पूर्णांक starting_len = xdr->buf->len;
	loff_t hole_pos;
	__be32 nfserr;
	__be32 *p, पंचांगp;
	__be64 पंचांगp64;

	hole_pos = pos ? *pos : vfs_llseek(file, पढ़ो->rd_offset, SEEK_HOLE);
	अगर (hole_pos > पढ़ो->rd_offset)
		*maxcount = min_t(अचिन्हित दीर्घ, *maxcount, hole_pos - पढ़ो->rd_offset);
	*maxcount = min_t(अचिन्हित दीर्घ, *maxcount, (xdr->buf->buflen - xdr->buf->len));

	/* Content type, offset, byte count */
	p = xdr_reserve_space(xdr, 4 + 8 + 4);
	अगर (!p)
		वापस nfserr_resource;

	पढ़ो->rd_vlen = xdr_reserve_space_vec(xdr, resp->rqstp->rq_vec, *maxcount);
	अगर (पढ़ो->rd_vlen < 0)
		वापस nfserr_resource;

	nfserr = nfsd_पढ़ोv(resp->rqstp, पढ़ो->rd_fhp, file, पढ़ो->rd_offset,
			    resp->rqstp->rq_vec, पढ़ो->rd_vlen, maxcount, eof);
	अगर (nfserr)
		वापस nfserr;
	xdr_truncate_encode(xdr, starting_len + 16 + xdr_align_size(*maxcount));

	पंचांगp = htonl(NFS4_CONTENT_DATA);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len,      &पंचांगp,   4);
	पंचांगp64 = cpu_to_be64(पढ़ो->rd_offset);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 4,  &पंचांगp64, 8);
	पंचांगp = htonl(*maxcount);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 12, &पंचांगp,   4);

	पंचांगp = xdr_zero;
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 16 + *maxcount, &पंचांगp,
			       xdr_pad_size(*maxcount));
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_encode_पढ़ो_plus_hole(काष्ठा nfsd4_compoundres *resp,
			    काष्ठा nfsd4_पढ़ो *पढ़ो,
			    अचिन्हित दीर्घ *maxcount, u32 *eof)
अणु
	काष्ठा file *file = पढ़ो->rd_nf->nf_file;
	loff_t data_pos = vfs_llseek(file, पढ़ो->rd_offset, SEEK_DATA);
	loff_t f_size = i_size_पढ़ो(file_inode(file));
	अचिन्हित दीर्घ count;
	__be32 *p;

	अगर (data_pos == -ENXIO)
		data_pos = f_size;
	अन्यथा अगर (data_pos <= पढ़ो->rd_offset || (data_pos < f_size && data_pos % PAGE_SIZE))
		वापस nfsd4_encode_पढ़ो_plus_data(resp, पढ़ो, maxcount, eof, &f_size);
	count = data_pos - पढ़ो->rd_offset;

	/* Content type, offset, byte count */
	p = xdr_reserve_space(resp->xdr, 4 + 8 + 8);
	अगर (!p)
		वापस nfserr_resource;

	*p++ = htonl(NFS4_CONTENT_HOLE);
	 p   = xdr_encode_hyper(p, पढ़ो->rd_offset);
	 p   = xdr_encode_hyper(p, count);

	*eof = (पढ़ो->rd_offset + count) >= f_size;
	*maxcount = min_t(अचिन्हित दीर्घ, count, *maxcount);
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_encode_पढ़ो_plus(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		       काष्ठा nfsd4_पढ़ो *पढ़ो)
अणु
	अचिन्हित दीर्घ maxcount, count;
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा file *file;
	पूर्णांक starting_len = xdr->buf->len;
	पूर्णांक last_segment = xdr->buf->len;
	पूर्णांक segments = 0;
	__be32 *p, पंचांगp;
	bool is_data;
	loff_t pos;
	u32 eof;

	अगर (nfserr)
		वापस nfserr;
	file = पढ़ो->rd_nf->nf_file;

	/* eof flag, segment count */
	p = xdr_reserve_space(xdr, 4 + 4);
	अगर (!p)
		वापस nfserr_resource;
	xdr_commit_encode(xdr);

	maxcount = svc_max_payload(resp->rqstp);
	maxcount = min_t(अचिन्हित दीर्घ, maxcount,
			 (xdr->buf->buflen - xdr->buf->len));
	maxcount = min_t(अचिन्हित दीर्घ, maxcount, पढ़ो->rd_length);
	count    = maxcount;

	eof = पढ़ो->rd_offset >= i_size_पढ़ो(file_inode(file));
	अगर (eof)
		जाओ out;

	pos = vfs_llseek(file, पढ़ो->rd_offset, SEEK_HOLE);
	is_data = pos > पढ़ो->rd_offset;

	जबतक (count > 0 && !eof) अणु
		maxcount = count;
		अगर (is_data)
			nfserr = nfsd4_encode_पढ़ो_plus_data(resp, पढ़ो, &maxcount, &eof,
						segments == 0 ? &pos : शून्य);
		अन्यथा
			nfserr = nfsd4_encode_पढ़ो_plus_hole(resp, पढ़ो, &maxcount, &eof);
		अगर (nfserr)
			जाओ out;
		count -= maxcount;
		पढ़ो->rd_offset += maxcount;
		is_data = !is_data;
		last_segment = xdr->buf->len;
		segments++;
	पूर्ण

out:
	अगर (nfserr && segments == 0)
		xdr_truncate_encode(xdr, starting_len);
	अन्यथा अणु
		अगर (nfserr) अणु
			xdr_truncate_encode(xdr, last_segment);
			nfserr = nfs_ok;
			eof = 0;
		पूर्ण
		पंचांगp = htonl(eof);
		ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len,     &पंचांगp, 4);
		पंचांगp = htonl(segments);
		ग_लिखो_bytes_to_xdr_buf(xdr->buf, starting_len + 4, &पंचांगp, 4);
	पूर्ण

	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_encode_copy_notअगरy(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			 काष्ठा nfsd4_copy_notअगरy *cn)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	अगर (nfserr)
		वापस nfserr;

	/* 8 sec, 4 nsec */
	p = xdr_reserve_space(xdr, 12);
	अगर (!p)
		वापस nfserr_resource;

	/* cnr_lease_समय */
	p = xdr_encode_hyper(p, cn->cpn_sec);
	*p++ = cpu_to_be32(cn->cpn_nsec);

	/* cnr_stateid */
	nfserr = nfsd4_encode_stateid(xdr, &cn->cpn_cnr_stateid);
	अगर (nfserr)
		वापस nfserr;

	/* cnr_src.nl_nsvr */
	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;

	*p++ = cpu_to_be32(1);

	वापस nfsd42_encode_nl4_server(resp, &cn->cpn_src);
पूर्ण

अटल __be32
nfsd4_encode_seek(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		  काष्ठा nfsd4_seek *seek)
अणु
	__be32 *p;

	p = xdr_reserve_space(resp->xdr, 4 + 8);
	*p++ = cpu_to_be32(seek->seek_eof);
	p = xdr_encode_hyper(p, seek->seek_pos);

	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_noop(काष्ठा nfsd4_compoundres *resp, __be32 nfserr, व्योम *p)
अणु
	वापस nfserr;
पूर्ण

/*
 * Encode kदो_स्मृति-ed buffer in to XDR stream.
 */
अटल __be32
nfsd4_vbuf_to_stream(काष्ठा xdr_stream *xdr, अक्षर *buf, u32 buflen)
अणु
	u32 cplen;
	__be32 *p;

	cplen = min_t(अचिन्हित दीर्घ, buflen,
		      ((व्योम *)xdr->end - (व्योम *)xdr->p));
	p = xdr_reserve_space(xdr, cplen);
	अगर (!p)
		वापस nfserr_resource;

	स_नकल(p, buf, cplen);
	buf += cplen;
	buflen -= cplen;

	जबतक (buflen) अणु
		cplen = min_t(u32, buflen, PAGE_SIZE);
		p = xdr_reserve_space(xdr, cplen);
		अगर (!p)
			वापस nfserr_resource;

		स_नकल(p, buf, cplen);

		अगर (cplen < PAGE_SIZE) अणु
			/*
			 * We're done, with a length that wasn't page
			 * aligned, so possibly not word aligned. Pad
			 * any trailing bytes with 0.
			 */
			xdr_encode_opaque_fixed(p, शून्य, cplen);
			अवरोध;
		पूर्ण

		buflen -= PAGE_SIZE;
		buf += PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_getxattr(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		      काष्ठा nfsd4_getxattr *getxattr)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p, err;

	p = xdr_reserve_space(xdr, 4);
	अगर (!p)
		वापस nfserr_resource;

	*p = cpu_to_be32(getxattr->getxa_len);

	अगर (getxattr->getxa_len == 0)
		वापस 0;

	err = nfsd4_vbuf_to_stream(xdr, getxattr->getxa_buf,
				    getxattr->getxa_len);

	kvमुक्त(getxattr->getxa_buf);

	वापस err;
पूर्ण

अटल __be32
nfsd4_encode_setxattr(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
		      काष्ठा nfsd4_setxattr *setxattr)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस nfserr_resource;

	encode_cinfo(p, &setxattr->setxa_cinfo);

	वापस 0;
पूर्ण

/*
 * See अगर there are cookie values that can be rejected outright.
 */
अटल __be32
nfsd4_listxattr_validate_cookie(काष्ठा nfsd4_listxattrs *listxattrs,
				u32 *offsetp)
अणु
	u64 cookie = listxattrs->lsxa_cookie;

	/*
	 * If the cookie is larger than the maximum number we can fit
	 * in either the buffer we just got back from vfs_listxattr, or,
	 * XDR-encoded, in the वापस buffer, it's invalid.
	 */
	अगर (cookie > (listxattrs->lsxa_len) / (XATTR_USER_PREFIX_LEN + 2))
		वापस nfserr_badcookie;

	अगर (cookie > (listxattrs->lsxa_maxcount /
		      (XDR_QUADLEN(XATTR_USER_PREFIX_LEN + 2) + 4)))
		वापस nfserr_badcookie;

	*offsetp = (u32)cookie;
	वापस 0;
पूर्ण

अटल __be32
nfsd4_encode_listxattrs(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			काष्ठा nfsd4_listxattrs *listxattrs)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	u32 cookie_offset, count_offset, eof;
	u32 left, xdrleft, slen, count;
	u32 xdrlen, offset;
	u64 cookie;
	अक्षर *sp;
	__be32 status, पंचांगp;
	__be32 *p;
	u32 nuser;

	eof = 1;

	status = nfsd4_listxattr_validate_cookie(listxattrs, &offset);
	अगर (status)
		जाओ out;

	/*
	 * Reserve space क्रम the cookie and the name array count. Record
	 * the offsets to save them later.
	 */
	cookie_offset = xdr->buf->len;
	count_offset = cookie_offset + 8;
	p = xdr_reserve_space(xdr, 12);
	अगर (!p) अणु
		status = nfserr_resource;
		जाओ out;
	पूर्ण

	count = 0;
	left = listxattrs->lsxa_len;
	sp = listxattrs->lsxa_buf;
	nuser = 0;

	xdrleft = listxattrs->lsxa_maxcount;

	जबतक (left > 0 && xdrleft > 0) अणु
		slen = म_माप(sp);

		/*
		 * Check अगर this is a "user." attribute, skip it अगर not.
		 */
		अगर (म_भेदन(sp, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN))
			जाओ contloop;

		slen -= XATTR_USER_PREFIX_LEN;
		xdrlen = 4 + ((slen + 3) & ~3);
		अगर (xdrlen > xdrleft) अणु
			अगर (count == 0) अणु
				/*
				 * Can't even fit the first attribute name.
				 */
				status = nfserr_toosmall;
				जाओ out;
			पूर्ण
			eof = 0;
			जाओ wreof;
		पूर्ण

		left -= XATTR_USER_PREFIX_LEN;
		sp += XATTR_USER_PREFIX_LEN;
		अगर (nuser++ < offset)
			जाओ contloop;


		p = xdr_reserve_space(xdr, xdrlen);
		अगर (!p) अणु
			status = nfserr_resource;
			जाओ out;
		पूर्ण

		xdr_encode_opaque(p, sp, slen);

		xdrleft -= xdrlen;
		count++;
contloop:
		sp += slen + 1;
		left -= slen + 1;
	पूर्ण

	/*
	 * If there were user attributes to copy, but we didn't copy
	 * any, the offset was too large (e.g. the cookie was invalid).
	 */
	अगर (nuser > 0 && count == 0) अणु
		status = nfserr_badcookie;
		जाओ out;
	पूर्ण

wreof:
	p = xdr_reserve_space(xdr, 4);
	अगर (!p) अणु
		status = nfserr_resource;
		जाओ out;
	पूर्ण
	*p = cpu_to_be32(eof);

	cookie = offset + count;

	ग_लिखो_bytes_to_xdr_buf(xdr->buf, cookie_offset, &cookie, 8);
	पंचांगp = cpu_to_be32(count);
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, count_offset, &पंचांगp, 4);
out:
	अगर (listxattrs->lsxa_len)
		kvमुक्त(listxattrs->lsxa_buf);
	वापस status;
पूर्ण

अटल __be32
nfsd4_encode_हटाओxattr(काष्ठा nfsd4_compoundres *resp, __be32 nfserr,
			 काष्ठा nfsd4_हटाओxattr *हटाओxattr)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 20);
	अगर (!p)
		वापस nfserr_resource;

	p = encode_cinfo(p, &हटाओxattr->rmxa_cinfo);
	वापस 0;
पूर्ण

प्रकार __be32(* nfsd4_enc)(काष्ठा nfsd4_compoundres *, __be32, व्योम *);

/*
 * Note: nfsd4_enc_ops vector is shared क्रम v4.0 and v4.1
 * since we करोn't need to filter out obsolete ops as this is
 * करोne in the decoding phase.
 */
अटल स्थिर nfsd4_enc nfsd4_enc_ops[] = अणु
	[OP_ACCESS]		= (nfsd4_enc)nfsd4_encode_access,
	[OP_CLOSE]		= (nfsd4_enc)nfsd4_encode_बंद,
	[OP_COMMIT]		= (nfsd4_enc)nfsd4_encode_commit,
	[OP_CREATE]		= (nfsd4_enc)nfsd4_encode_create,
	[OP_DELEGPURGE]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_DELEGRETURN]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_GETATTR]		= (nfsd4_enc)nfsd4_encode_getattr,
	[OP_GETFH]		= (nfsd4_enc)nfsd4_encode_getfh,
	[OP_LINK]		= (nfsd4_enc)nfsd4_encode_link,
	[OP_LOCK]		= (nfsd4_enc)nfsd4_encode_lock,
	[OP_LOCKT]		= (nfsd4_enc)nfsd4_encode_lockt,
	[OP_LOCKU]		= (nfsd4_enc)nfsd4_encode_locku,
	[OP_LOOKUP]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LOOKUPP]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_NVERIFY]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_OPEN]		= (nfsd4_enc)nfsd4_encode_खोलो,
	[OP_OPENATTR]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_OPEN_CONFIRM]	= (nfsd4_enc)nfsd4_encode_खोलो_confirm,
	[OP_OPEN_DOWNGRADE]	= (nfsd4_enc)nfsd4_encode_खोलो_करोwngrade,
	[OP_PUTFH]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_PUTPUBFH]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_PUTROOTFH]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_READ]		= (nfsd4_enc)nfsd4_encode_पढ़ो,
	[OP_READसूची]		= (nfsd4_enc)nfsd4_encode_सूची_पढ़ो,
	[OP_READLINK]		= (nfsd4_enc)nfsd4_encode_पढ़ोlink,
	[OP_REMOVE]		= (nfsd4_enc)nfsd4_encode_हटाओ,
	[OP_RENAME]		= (nfsd4_enc)nfsd4_encode_नाम,
	[OP_RENEW]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_RESTOREFH]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_SAVEFH]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_SECINFO]		= (nfsd4_enc)nfsd4_encode_secinfo,
	[OP_SETATTR]		= (nfsd4_enc)nfsd4_encode_setattr,
	[OP_SETCLIENTID]	= (nfsd4_enc)nfsd4_encode_setclientid,
	[OP_SETCLIENTID_CONFIRM] = (nfsd4_enc)nfsd4_encode_noop,
	[OP_VERIFY]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_WRITE]		= (nfsd4_enc)nfsd4_encode_ग_लिखो,
	[OP_RELEASE_LOCKOWNER]	= (nfsd4_enc)nfsd4_encode_noop,

	/* NFSv4.1 operations */
	[OP_BACKCHANNEL_CTL]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_BIND_CONN_TO_SESSION] = (nfsd4_enc)nfsd4_encode_bind_conn_to_session,
	[OP_EXCHANGE_ID]	= (nfsd4_enc)nfsd4_encode_exchange_id,
	[OP_CREATE_SESSION]	= (nfsd4_enc)nfsd4_encode_create_session,
	[OP_DESTROY_SESSION]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_FREE_STATEID]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_GET_सूची_DELEGATION]	= (nfsd4_enc)nfsd4_encode_noop,
#अगर_घोषित CONFIG_NFSD_PNFS
	[OP_GETDEVICEINFO]	= (nfsd4_enc)nfsd4_encode_getdeviceinfo,
	[OP_GETDEVICELIST]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTCOMMIT]	= (nfsd4_enc)nfsd4_encode_layoutcommit,
	[OP_LAYOUTGET]		= (nfsd4_enc)nfsd4_encode_layoutget,
	[OP_LAYOUTRETURN]	= (nfsd4_enc)nfsd4_encode_layoutवापस,
#अन्यथा
	[OP_GETDEVICEINFO]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_GETDEVICELIST]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTCOMMIT]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTGET]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTRETURN]	= (nfsd4_enc)nfsd4_encode_noop,
#पूर्ण_अगर
	[OP_SECINFO_NO_NAME]	= (nfsd4_enc)nfsd4_encode_secinfo_no_name,
	[OP_SEQUENCE]		= (nfsd4_enc)nfsd4_encode_sequence,
	[OP_SET_SSV]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_TEST_STATEID]	= (nfsd4_enc)nfsd4_encode_test_stateid,
	[OP_WANT_DELEGATION]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_DESTROY_CLIENTID]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_RECLAIM_COMPLETE]	= (nfsd4_enc)nfsd4_encode_noop,

	/* NFSv4.2 operations */
	[OP_ALLOCATE]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_COPY]		= (nfsd4_enc)nfsd4_encode_copy,
	[OP_COPY_NOTIFY]	= (nfsd4_enc)nfsd4_encode_copy_notअगरy,
	[OP_DEALLOCATE]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_IO_ADVISE]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTERROR]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_LAYOUTSTATS]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_OFFLOAD_CANCEL]	= (nfsd4_enc)nfsd4_encode_noop,
	[OP_OFFLOAD_STATUS]	= (nfsd4_enc)nfsd4_encode_offload_status,
	[OP_READ_PLUS]		= (nfsd4_enc)nfsd4_encode_पढ़ो_plus,
	[OP_SEEK]		= (nfsd4_enc)nfsd4_encode_seek,
	[OP_WRITE_SAME]		= (nfsd4_enc)nfsd4_encode_noop,
	[OP_CLONE]		= (nfsd4_enc)nfsd4_encode_noop,

	/* RFC 8276 extended atributes operations */
	[OP_GETXATTR]		= (nfsd4_enc)nfsd4_encode_getxattr,
	[OP_SETXATTR]		= (nfsd4_enc)nfsd4_encode_setxattr,
	[OP_LISTXATTRS]		= (nfsd4_enc)nfsd4_encode_listxattrs,
	[OP_REMOVEXATTR]	= (nfsd4_enc)nfsd4_encode_हटाओxattr,
पूर्ण;

/*
 * Calculate whether we still have space to encode repsize bytes.
 * There are two considerations:
 *     - For NFS versions >=4.1, the size of the reply must stay within
 *       session limits
 *     - For all NFS versions, we must stay within limited pपुनः_स्मृतिated
 *       buffer space.
 *
 * This is called beक्रमe the operation is processed, so can only provide
 * an upper estimate.  For some nonidempotent operations (such as
 * getattr), it's not necessarily a problem अगर that estimate is wrong,
 * as we can fail it after processing without signअगरicant side effects.
 */
__be32 nfsd4_check_resp_size(काष्ठा nfsd4_compoundres *resp, u32 respsize)
अणु
	काष्ठा xdr_buf *buf = &resp->rqstp->rq_res;
	काष्ठा nfsd4_slot *slot = resp->cstate.slot;

	अगर (buf->len + respsize <= buf->buflen)
		वापस nfs_ok;
	अगर (!nfsd4_has_session(&resp->cstate))
		वापस nfserr_resource;
	अगर (slot->sl_flags & NFSD4_SLOT_CACHETHIS) अणु
		WARN_ON_ONCE(1);
		वापस nfserr_rep_too_big_to_cache;
	पूर्ण
	वापस nfserr_rep_too_big;
पूर्ण

व्योम
nfsd4_encode_operation(काष्ठा nfsd4_compoundres *resp, काष्ठा nfsd4_op *op)
अणु
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा nfs4_stateowner *so = resp->cstate.replay_owner;
	काष्ठा svc_rqst *rqstp = resp->rqstp;
	स्थिर काष्ठा nfsd4_operation *opdesc = op->opdesc;
	पूर्णांक post_err_offset;
	nfsd4_enc encoder;
	__be32 *p;

	p = xdr_reserve_space(xdr, 8);
	अगर (!p) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	*p++ = cpu_to_be32(op->opnum);
	post_err_offset = xdr->buf->len;

	अगर (op->opnum == OP_ILLEGAL)
		जाओ status;
	अगर (op->status && opdesc &&
			!(opdesc->op_flags & OP_NONTRIVIAL_ERROR_ENCODE))
		जाओ status;
	BUG_ON(op->opnum >= ARRAY_SIZE(nfsd4_enc_ops) ||
	       !nfsd4_enc_ops[op->opnum]);
	encoder = nfsd4_enc_ops[op->opnum];
	op->status = encoder(resp, op->status, &op->u);
	अगर (op->status)
		trace_nfsd_compound_encode_err(rqstp, op->opnum, op->status);
	अगर (opdesc && opdesc->op_release)
		opdesc->op_release(&op->u);
	xdr_commit_encode(xdr);

	/* nfsd4_check_resp_size guarantees enough room क्रम error status */
	अगर (!op->status) अणु
		पूर्णांक space_needed = 0;
		अगर (!nfsd4_last_compound_op(rqstp))
			space_needed = COMPOUND_ERR_SLACK_SPACE;
		op->status = nfsd4_check_resp_size(resp, space_needed);
	पूर्ण
	अगर (op->status == nfserr_resource && nfsd4_has_session(&resp->cstate)) अणु
		काष्ठा nfsd4_slot *slot = resp->cstate.slot;

		अगर (slot->sl_flags & NFSD4_SLOT_CACHETHIS)
			op->status = nfserr_rep_too_big_to_cache;
		अन्यथा
			op->status = nfserr_rep_too_big;
	पूर्ण
	अगर (op->status == nfserr_resource ||
	    op->status == nfserr_rep_too_big ||
	    op->status == nfserr_rep_too_big_to_cache) अणु
		/*
		 * The operation may have alपढ़ोy been encoded or
		 * partially encoded.  No op वापसs anything additional
		 * in the हाल of one of these three errors, so we can
		 * just truncate back to after the status.  But it's a
		 * bug अगर we had to करो this on a non-idempotent op:
		 */
		warn_on_nonidempotent_op(op);
		xdr_truncate_encode(xdr, post_err_offset);
	पूर्ण
	अगर (so) अणु
		पूर्णांक len = xdr->buf->len - post_err_offset;

		so->so_replay.rp_status = op->status;
		so->so_replay.rp_buflen = len;
		पढ़ो_bytes_from_xdr_buf(xdr->buf, post_err_offset,
						so->so_replay.rp_buf, len);
	पूर्ण
status:
	/* Note that op->status is alपढ़ोy in network byte order: */
	ग_लिखो_bytes_to_xdr_buf(xdr->buf, post_err_offset - 4, &op->status, 4);
पूर्ण

/* 
 * Encode the reply stored in the stateowner reply cache 
 * 
 * XDR note: करो not encode rp->rp_buflen: the buffer contains the
 * previously sent alपढ़ोy encoded operation.
 */
व्योम
nfsd4_encode_replay(काष्ठा xdr_stream *xdr, काष्ठा nfsd4_op *op)
अणु
	__be32 *p;
	काष्ठा nfs4_replay *rp = op->replay;

	p = xdr_reserve_space(xdr, 8 + rp->rp_buflen);
	अगर (!p) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	*p++ = cpu_to_be32(op->opnum);
	*p++ = rp->rp_status;  /* alपढ़ोy xdr'ed */

	p = xdr_encode_opaque_fixed(p, rp->rp_buf, rp->rp_buflen);
पूर्ण

व्योम nfsd4_release_compoundargs(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd4_compoundargs *args = rqstp->rq_argp;

	अगर (args->ops != args->iops) अणु
		kमुक्त(args->ops);
		args->ops = args->iops;
	पूर्ण
	जबतक (args->to_मुक्त) अणु
		काष्ठा svcxdr_पंचांगpbuf *tb = args->to_मुक्त;
		args->to_मुक्त = tb->next;
		kमुक्त(tb);
	पूर्ण
पूर्ण

पूर्णांक
nfs4svc_decode_compoundargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nfsd4_compoundargs *args = rqstp->rq_argp;

	/* svcxdr_पंचांगp_alloc */
	args->to_मुक्त = शून्य;

	args->xdr = &rqstp->rq_arg_stream;
	args->ops = args->iops;
	args->rqstp = rqstp;

	वापस nfsd4_decode_compound(args);
पूर्ण

पूर्णांक
nfs4svc_encode_compoundres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा xdr_buf *buf = resp->xdr->buf;

	WARN_ON_ONCE(buf->len != buf->head[0].iov_len + buf->page_len +
				 buf->tail[0].iov_len);

	*p = resp->cstate.status;

	rqstp->rq_next_page = resp->xdr->page_ptr + 1;

	p = resp->tagp;
	*p++ = htonl(resp->taglen);
	स_नकल(p, resp->tag, resp->taglen);
	p += XDR_QUADLEN(resp->taglen);
	*p++ = htonl(resp->opcnt);

	nfsd4_sequence_करोne(resp);
	वापस 1;
पूर्ण
