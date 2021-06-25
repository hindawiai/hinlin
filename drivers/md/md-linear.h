<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINEAR_H
#घोषणा _LINEAR_H

काष्ठा dev_info अणु
	काष्ठा md_rdev	*rdev;
	sector_t	end_sector;
पूर्ण;

काष्ठा linear_conf
अणु
	काष्ठा rcu_head		rcu;
	sector_t		array_sectors;
	पूर्णांक			raid_disks; /* a copy of mddev->raid_disks */
	काष्ठा dev_info		disks[];
पूर्ण;
#पूर्ण_अगर
