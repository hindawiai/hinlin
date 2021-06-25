<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File: linux/nfsacl.h
 *
 * (C) 2003 Andreas Gruenbacher <agruen@suse.de>
 */
#अगर_अघोषित __LINUX_NFSACL_H
#घोषणा __LINUX_NFSACL_H


#समावेश <linux/posix_acl.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <uapi/linux/nfsacl.h>

/* Maximum number of ACL entries over NFS */
#घोषणा NFS_ACL_MAX_ENTRIES	1024

#घोषणा NFSACL_MAXWORDS		(2*(2+3*NFS_ACL_MAX_ENTRIES))
#घोषणा NFSACL_MAXPAGES		((2*(8+12*NFS_ACL_MAX_ENTRIES) + PAGE_SIZE-1) \
				 >> PAGE_SHIFT)

#घोषणा NFS_ACL_MAX_ENTRIES_INLINE	(5)
#घोषणा NFS_ACL_INLINE_बफ_मानE	((2*(2+3*NFS_ACL_MAX_ENTRIES_INLINE)) << 2)

अटल अंतरभूत अचिन्हित पूर्णांक
nfsacl_size(काष्ठा posix_acl *acl_access, काष्ठा posix_acl *acl_शेष)
अणु
	अचिन्हित पूर्णांक w = 16;
	w += max(acl_access ? (पूर्णांक)acl_access->a_count : 3, 4) * 12;
	अगर (acl_शेष)
		w += max((पूर्णांक)acl_शेष->a_count, 4) * 12;
	वापस w;
पूर्ण

बाह्य पूर्णांक
nfsacl_encode(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, काष्ठा inode *inode,
	      काष्ठा posix_acl *acl, पूर्णांक encode_entries, पूर्णांक typeflag);
बाह्य पूर्णांक
nfsacl_decode(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *aclcnt,
	      काष्ठा posix_acl **pacl);
बाह्य bool
nfs_stream_decode_acl(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक *aclcnt,
		      काष्ठा posix_acl **pacl);
बाह्य bool
nfs_stream_encode_acl(काष्ठा xdr_stream *xdr, काष्ठा inode *inode,
		      काष्ठा posix_acl *acl, पूर्णांक encode_entries, पूर्णांक typeflag);

#पूर्ण_अगर  /* __LINUX_NFSACL_H */
