<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) Tino Reiअक्षरdt, 2012
 */
#अगर_अघोषित _H_JFS_DISCARD
#घोषणा _H_JFS_DISCARD

काष्ठा fstrim_range;

बाह्य व्योम jfs_issue_discard(काष्ठा inode *ip, u64 blkno, u64 nblocks);
बाह्य पूर्णांक jfs_ioc_trim(काष्ठा inode *ip, काष्ठा fstrim_range *range);

#पूर्ण_अगर /* _H_JFS_DISCARD */
