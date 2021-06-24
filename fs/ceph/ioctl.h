<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_CEPH_IOCTL_H
#घोषणा FS_CEPH_IOCTL_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा CEPH_IOCTL_MAGIC 0x97

/*
 * CEPH_IOC_GET_LAYOUT - get file layout or dir layout policy
 * CEPH_IOC_SET_LAYOUT - set file layout
 * CEPH_IOC_SET_LAYOUT_POLICY - set dir layout policy
 *
 * The file layout specअगरies how file data is striped over objects in
 * the distributed object store, which object pool they beदीर्घ to (अगर
 * it dअगरfers from the शेष), and an optional 'preferred osd' to
 * store them on.
 *
 * Files get a new layout based on the policy set on the containing
 * directory or one of its ancestors.  The GET_LAYOUT ioctl will let
 * you examine the layout क्रम a file or the policy on a directory.
 *
 * SET_LAYOUT will let you set a layout on a newly created file.  This
 * only works immediately after the file is created and beक्रमe any
 * data is written to it.
 *
 * SET_LAYOUT_POLICY will let you set a layout policy (शेष layout)
 * on a directory that will apply to any new files created in that
 * directory (or any child directory that करोesn't specअगरy a layout of
 * its own).
 */

/* use u64 to align sanely on all archs */
काष्ठा ceph_ioctl_layout अणु
	__u64 stripe_unit, stripe_count, object_size;
	__u64 data_pool;

	/* obsolete.  new values ignored, always वापस -1 */
	__s64 preferred_osd;
पूर्ण;

#घोषणा CEPH_IOC_GET_LAYOUT _IOR(CEPH_IOCTL_MAGIC, 1,		\
				   काष्ठा ceph_ioctl_layout)
#घोषणा CEPH_IOC_SET_LAYOUT _IOW(CEPH_IOCTL_MAGIC, 2,		\
				   काष्ठा ceph_ioctl_layout)
#घोषणा CEPH_IOC_SET_LAYOUT_POLICY _IOW(CEPH_IOCTL_MAGIC, 5,	\
				   काष्ठा ceph_ioctl_layout)

/*
 * CEPH_IOC_GET_DATALOC - get location of file data in the cluster
 *
 * Extract identity, address of the OSD and object storing a given
 * file offset.
 */
काष्ठा ceph_ioctl_dataloc अणु
	__u64 file_offset;           /* in+out: file offset */
	__u64 object_offset;         /* out: offset in object */
	__u64 object_no;             /* out: object # */
	__u64 object_size;           /* out: object size */
	अक्षर object_name[64];        /* out: object name */
	__u64 block_offset;          /* out: offset in block */
	__u64 block_size;            /* out: block length */
	__s64 osd;                   /* out: osd # */
	काष्ठा sockaddr_storage osd_addr; /* out: osd address */
पूर्ण;

#घोषणा CEPH_IOC_GET_DATALOC _IOWR(CEPH_IOCTL_MAGIC, 3,	\
				   काष्ठा ceph_ioctl_dataloc)

/*
 * CEPH_IOC_LAZYIO - relax consistency
 *
 * Normally Ceph चयनes to synchronous IO when multiple clients have
 * the file खोलो (and or more क्रम ग_लिखो).  Reads and ग_लिखोs bypass the
 * page cache and go directly to the OSD.  Setting this flag on a file
 * descriptor will allow buffered IO क्रम this file in हालs where the
 * application knows it won't interfere with other nodes (or doesn't
 * care).
 */
#घोषणा CEPH_IOC_LAZYIO _IO(CEPH_IOCTL_MAGIC, 4)

/*
 * CEPH_IOC_SYNCIO - क्रमce synchronous IO
 *
 * This ioctl sets a file flag that क्रमces the synchronous IO that
 * bypasses the page cache, even अगर it is not necessary.  This is
 * essentially the opposite behavior of IOC_LAZYIO.  This क्रमces the
 * same पढ़ो/ग_लिखो path as a file खोलोed by multiple clients when one
 * or more of those clients is खोलोed क्रम ग_लिखो.
 *
 * Note that this type of sync IO takes a dअगरferent path than a file
 * खोलोed with O_SYNC/D_SYNC (ग_लिखोs hit the page cache and are
 * immediately flushed on page boundaries).  It is very similar to
 * O_सूचीECT (ग_लिखोs bypass the page cache) excep that O_सूचीECT ग_लिखोs
 * are not copied (user page must reमुख्य stable) and O_सूचीECT ग_लिखोs
 * have alignment restrictions (on the buffer and file offset).
 */
#घोषणा CEPH_IOC_SYNCIO _IO(CEPH_IOCTL_MAGIC, 5)

#पूर्ण_अगर
