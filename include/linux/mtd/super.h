<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* MTD-based superblock handling
 *
 * Copyright तऊ 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित __MTD_SUPER_H__
#घोषणा __MTD_SUPER_H__

#अगर_घोषित __KERNEL__

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>

बाह्य पूर्णांक get_tree_mtd(काष्ठा fs_context *fc,
		     पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				       काष्ठा fs_context *fc));
बाह्य व्योम समाप्त_mtd_super(काष्ठा super_block *sb);


#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __MTD_SUPER_H__ */
