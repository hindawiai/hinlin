<शैली गुरु>
/*
 * fs/nfs/nfs4idmap.h
 *
 *  UID and GID to name mapping क्रम clients.
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
#अगर_अघोषित NFS_IDMAP_H
#घोषणा NFS_IDMAP_H

#समावेश <linux/uidgid.h>
#समावेश <uapi/linux/nfs_idmap.h>


/* Forward declaration to make this header independent of others */
काष्ठा nfs_client;
काष्ठा nfs_server;
काष्ठा nfs_fattr;
काष्ठा nfs4_string;

पूर्णांक nfs_idmap_init(व्योम);
व्योम nfs_idmap_quit(व्योम);
पूर्णांक nfs_idmap_new(काष्ठा nfs_client *);
व्योम nfs_idmap_delete(काष्ठा nfs_client *);

व्योम nfs_fattr_init_names(काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_string *owner_name,
		काष्ठा nfs4_string *group_name);
व्योम nfs_fattr_मुक्त_names(काष्ठा nfs_fattr *);
व्योम nfs_fattr_map_and_मुक्त_names(काष्ठा nfs_server *, काष्ठा nfs_fattr *);

पूर्णांक nfs_map_name_to_uid(स्थिर काष्ठा nfs_server *, स्थिर अक्षर *, माप_प्रकार, kuid_t *);
पूर्णांक nfs_map_group_to_gid(स्थिर काष्ठा nfs_server *, स्थिर अक्षर *, माप_प्रकार, kgid_t *);
पूर्णांक nfs_map_uid_to_name(स्थिर काष्ठा nfs_server *, kuid_t, अक्षर *, माप_प्रकार);
पूर्णांक nfs_map_gid_to_group(स्थिर काष्ठा nfs_server *, kgid_t, अक्षर *, माप_प्रकार);

पूर्णांक nfs_map_string_to_numeric(स्थिर अक्षर *name, माप_प्रकार namelen, __u32 *res);

बाह्य अचिन्हित पूर्णांक nfs_idmap_cache_समयout;
#पूर्ण_अगर /* NFS_IDMAP_H */
