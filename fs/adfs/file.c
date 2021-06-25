<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/adfs/file.c
 *
 * Copyright (C) 1997-1999 Russell King
 * from:
 *
 *  linux/fs/ext2/file.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/file.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  adfs regular file handling primitives           
 */
#समावेश "adfs.h"

स्थिर काष्ठा file_operations adfs_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.mmap		= generic_file_mmap,
	.fsync		= generic_file_fsync,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

स्थिर काष्ठा inode_operations adfs_file_inode_operations = अणु
	.setattr	= adfs_notअगरy_change,
पूर्ण;
