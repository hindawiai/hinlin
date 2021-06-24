<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * direct.h - NILFS direct block poपूर्णांकer.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_सूचीECT_H
#घोषणा _NILFS_सूचीECT_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश "bmap.h"


#घोषणा NILFS_सूचीECT_NBLOCKS	(NILFS_BMAP_SIZE / माप(__le64) - 1)
#घोषणा NILFS_सूचीECT_KEY_MIN	0
#घोषणा NILFS_सूचीECT_KEY_MAX	(NILFS_सूचीECT_NBLOCKS - 1)


पूर्णांक nilfs_direct_init(काष्ठा nilfs_bmap *);
पूर्णांक nilfs_direct_delete_and_convert(काष्ठा nilfs_bmap *, __u64, __u64 *,
				    __u64 *, पूर्णांक);


#पूर्ण_अगर	/* _NILFS_सूचीECT_H */
