<शैली गुरु>
/*
 *  Mapping of UID to name and vice versa.
 *
 *  Copyright (c) 2002, 2003 The Regents of the University of
 *  Michigan.  All rights reserved.
> *
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

#अगर_अघोषित LINUX_NFSD_IDMAP_H
#घोषणा LINUX_NFSD_IDMAP_H

#समावेश <linux/in.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/nfs_idmap.h>

#अगर_घोषित CONFIG_NFSD_V4
पूर्णांक nfsd_idmap_init(काष्ठा net *);
व्योम nfsd_idmap_shutकरोwn(काष्ठा net *);
#अन्यथा
अटल अंतरभूत पूर्णांक nfsd_idmap_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nfsd_idmap_shutकरोwn(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

__be32 nfsd_map_name_to_uid(काष्ठा svc_rqst *, स्थिर अक्षर *, माप_प्रकार, kuid_t *);
__be32 nfsd_map_name_to_gid(काष्ठा svc_rqst *, स्थिर अक्षर *, माप_प्रकार, kgid_t *);
__be32 nfsd4_encode_user(काष्ठा xdr_stream *, काष्ठा svc_rqst *, kuid_t);
__be32 nfsd4_encode_group(काष्ठा xdr_stream *, काष्ठा svc_rqst *, kgid_t);

#पूर्ण_अगर /* LINUX_NFSD_IDMAP_H */
