<शैली गुरु>
/*
 *  Common NFSv4 ACL handling definitions.
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

#अगर_अघोषित LINUX_NFS4_ACL_H
#घोषणा LINUX_NFS4_ACL_H

काष्ठा nfs4_acl;
काष्ठा svc_fh;
काष्ठा svc_rqst;

पूर्णांक nfs4_acl_bytes(पूर्णांक entries);
पूर्णांक nfs4_acl_get_whotype(अक्षर *, u32);
__be32 nfs4_acl_ग_लिखो_who(काष्ठा xdr_stream *xdr, पूर्णांक who);

पूर्णांक nfsd4_get_nfs4_acl(काष्ठा svc_rqst *rqstp, काष्ठा dentry *dentry,
		काष्ठा nfs4_acl **acl);
__be32 nfsd4_set_nfs4_acl(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा nfs4_acl *acl);

#पूर्ण_अगर /* LINUX_NFS4_ACL_H */
