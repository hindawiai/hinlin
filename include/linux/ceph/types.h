<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_TYPES_H
#घोषणा _FS_CEPH_TYPES_H

/* needed beक्रमe including ceph_fs.h */
#समावेश <linux/in.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/माला.स>

#समावेश <linux/ceph/ceph_fs.h>
#समावेश <linux/ceph/ceph_frag.h>
#समावेश <linux/ceph/ceph_hash.h>

/*
 * Identअगरy inodes by both their ino AND snapshot id (a u64).
 */
काष्ठा ceph_vino अणु
	u64 ino;
	u64 snap;
पूर्ण;


/* context क्रम the caps reservation mechanism */
काष्ठा ceph_cap_reservation अणु
	पूर्णांक count;
	पूर्णांक used;
पूर्ण;


#पूर्ण_अगर
