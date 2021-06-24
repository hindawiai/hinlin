<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* no-block.c: implementation of routines required क्रम non-BLOCK configuration
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>

अटल पूर्णांक no_blkdev_खोलो(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	वापस -ENODEV;
पूर्ण

स्थिर काष्ठा file_operations def_blk_fops = अणु
	.खोलो		= no_blkdev_खोलो,
	.llseek		= noop_llseek,
पूर्ण;
