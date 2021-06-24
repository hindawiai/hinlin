<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MULTIPATH_H
#घोषणा _MULTIPATH_H

काष्ठा multipath_info अणु
	काष्ठा md_rdev	*rdev;
पूर्ण;

काष्ठा mpconf अणु
	काष्ठा mddev			*mddev;
	काष्ठा multipath_info	*multipaths;
	पूर्णांक			raid_disks;
	spinlock_t		device_lock;
	काष्ठा list_head	retry_list;

	mempool_t		pool;
पूर्ण;

/*
 * this is our 'private' 'collective' MULTIPATH buffer head.
 * it contains inक्रमmation about what kind of IO operations were started
 * क्रम this MULTIPATH operation, and about their status:
 */

काष्ठा multipath_bh अणु
	काष्ठा mddev			*mddev;
	काष्ठा bio		*master_bio;
	काष्ठा bio		bio;
	पूर्णांक			path;
	काष्ठा list_head	retry_list;
पूर्ण;
#पूर्ण_अगर
