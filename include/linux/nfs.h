<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NFS protocol definitions
 *
 * This file contains स्थिरants mostly क्रम Version 2 of the protocol,
 * but also has a couple of NFSv3 bits in (notably the error codes).
 */
#अगर_अघोषित _LINUX_NFS_H
#घोषणा _LINUX_NFS_H

#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/माला.स>
#समावेश <uapi/linux/nfs.h>

/*
 * This is the kernel NFS client file handle representation
 */
#घोषणा NFS_MAXFHSIZE		128
काष्ठा nfs_fh अणु
	अचिन्हित लघु		size;
	अचिन्हित अक्षर		data[NFS_MAXFHSIZE];
पूर्ण;

/*
 * Returns a zero अगरf the size and data fields match.
 * Checks only "size" bytes in the data field.
 */
अटल अंतरभूत पूर्णांक nfs_compare_fh(स्थिर काष्ठा nfs_fh *a, स्थिर काष्ठा nfs_fh *b)
अणु
	वापस a->size != b->size || स_भेद(a->data, b->data, a->size) != 0;
पूर्ण

अटल अंतरभूत व्योम nfs_copy_fh(काष्ठा nfs_fh *target, स्थिर काष्ठा nfs_fh *source)
अणु
	target->size = source->size;
	स_नकल(target->data, source->data, source->size);
पूर्ण


/*
 * This is really a general kernel स्थिरant, but since nothing like
 * this is defined in the kernel headers, I have to करो it here.
 */
#घोषणा NFS_OFFSET_MAX		((__s64)((~(__u64)0) >> 1))


क्रमागत nfs3_stable_how अणु
	NFS_UNSTABLE = 0,
	NFS_DATA_SYNC = 1,
	NFS_खाता_SYNC = 2,

	/* used by direct.c to mark verf as invalid */
	NFS_INVALID_STABLE_HOW = -1
पूर्ण;
#पूर्ण_अगर /* _LINUX_NFS_H */
