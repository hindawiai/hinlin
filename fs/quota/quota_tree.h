<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Definitions of काष्ठाures क्रम vfsv0 quota क्रमmat
 */

#अगर_अघोषित _LINUX_QUOTA_TREE_H
#घोषणा _LINUX_QUOTA_TREE_H

#समावेश <linux/types.h>
#समावेश <linux/quota.h>

/*
 *  Structure of header of block with quota काष्ठाures. It is padded to 16 bytes so
 *  there will be space क्रम exactly 21 quota-entries in a block
 */
काष्ठा qt_disk_dqdbheader अणु
	__le32 dqdh_next_मुक्त;	/* Number of next block with मुक्त entry */
	__le32 dqdh_prev_मुक्त;	/* Number of previous block with मुक्त entry */
	__le16 dqdh_entries;	/* Number of valid entries in block */
	__le16 dqdh_pad1;
	__le32 dqdh_pad2;
पूर्ण;

#घोषणा QT_TREखातापूर्णF	1		/* Offset of tree in file in blocks */

#पूर्ण_अगर /* _LINUX_QUOTAIO_TREE_H */
