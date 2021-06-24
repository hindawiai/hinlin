<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

/* This file just defines debugging masks to be used with the gossip
 * logging utility.  All debugging masks क्रम ORANGEFS are kept here to make
 * sure we करोn't have collisions.
 */

#अगर_अघोषित __ORANGEFS_DEBUG_H
#घोषणा __ORANGEFS_DEBUG_H

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#पूर्ण_अगर

#घोषणा	GOSSIP_NO_DEBUG			(__u64)0

#घोषणा GOSSIP_SUPER_DEBUG		((__u64)1 << 0)
#घोषणा GOSSIP_INODE_DEBUG		((__u64)1 << 1)
#घोषणा GOSSIP_खाता_DEBUG		((__u64)1 << 2)
#घोषणा GOSSIP_सूची_DEBUG		((__u64)1 << 3)
#घोषणा GOSSIP_UTILS_DEBUG		((__u64)1 << 4)
#घोषणा GOSSIP_WAIT_DEBUG		((__u64)1 << 5)
#घोषणा GOSSIP_ACL_DEBUG		((__u64)1 << 6)
#घोषणा GOSSIP_DCACHE_DEBUG		((__u64)1 << 7)
#घोषणा GOSSIP_DEV_DEBUG		((__u64)1 << 8)
#घोषणा GOSSIP_NAME_DEBUG		((__u64)1 << 9)
#घोषणा GOSSIP_BUFMAP_DEBUG		((__u64)1 << 10)
#घोषणा GOSSIP_CACHE_DEBUG		((__u64)1 << 11)
#घोषणा GOSSIP_DEBUGFS_DEBUG		((__u64)1 << 12)
#घोषणा GOSSIP_XATTR_DEBUG		((__u64)1 << 13)
#घोषणा GOSSIP_INIT_DEBUG		((__u64)1 << 14)
#घोषणा GOSSIP_SYSFS_DEBUG		((__u64)1 << 15)

#घोषणा GOSSIP_MAX_NR                 16
#घोषणा GOSSIP_MAX_DEBUG              (((__u64)1 << GOSSIP_MAX_NR) - 1)

/* a निजी पूर्णांकernal type */
काष्ठा __keyword_mask_s अणु
	स्थिर अक्षर *keyword;
	__u64 mask_val;
पूर्ण;

/*
 * Map all kmod keywords to kmod debug masks here. Keep this
 * काष्ठाure "packed":
 *
 *   "all" is always last...
 *
 *   keyword     mask_val     index
 *     foo          1           0
 *     bar          2           1
 *     baz          4           2
 *     qux          8           3
 *      .           .           .
 */
अटल काष्ठा __keyword_mask_s s_kmod_keyword_mask_map[] = अणु
	अणु"super", GOSSIP_SUPER_DEBUGपूर्ण,
	अणु"inode", GOSSIP_INODE_DEBUGपूर्ण,
	अणु"file", GOSSIP_खाता_DEBUGपूर्ण,
	अणु"dir", GOSSIP_सूची_DEBUGपूर्ण,
	अणु"utils", GOSSIP_UTILS_DEBUGपूर्ण,
	अणु"wait", GOSSIP_WAIT_DEBUGपूर्ण,
	अणु"acl", GOSSIP_ACL_DEBUGपूर्ण,
	अणु"dcache", GOSSIP_DCACHE_DEBUGपूर्ण,
	अणु"dev", GOSSIP_DEV_DEBUGपूर्ण,
	अणु"name", GOSSIP_NAME_DEBUGपूर्ण,
	अणु"bufmap", GOSSIP_BUFMAP_DEBUGपूर्ण,
	अणु"cache", GOSSIP_CACHE_DEBUGपूर्ण,
	अणु"debugfs", GOSSIP_DEBUGFS_DEBUGपूर्ण,
	अणु"xattr", GOSSIP_XATTR_DEBUGपूर्ण,
	अणु"init", GOSSIP_INIT_DEBUGपूर्ण,
	अणु"sysfs", GOSSIP_SYSFS_DEBUGपूर्ण,
	अणु"none", GOSSIP_NO_DEBUGपूर्ण,
	अणु"all", GOSSIP_MAX_DEBUGपूर्ण
पूर्ण;

अटल स्थिर पूर्णांक num_kmod_keyword_mask_map = (पूर्णांक)
	(ARRAY_SIZE(s_kmod_keyword_mask_map));

#पूर्ण_अगर /* __ORANGEFS_DEBUG_H */
