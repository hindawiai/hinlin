<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/स्थिति.स
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_STAT_H
#घोषणा _XTENSA_STAT_H

#घोषणा STAT_HAVE_NSEC 1

काष्ठा stat अणु
	अचिन्हित दीर्घ	st_dev;
	अचिन्हित दीर्घ	st_ino;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित दीर्घ	st_rdev;
	दीर्घ		st_size;
	अचिन्हित दीर्घ	st_blksize;
	अचिन्हित दीर्घ	st_blocks;
	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;
	अचिन्हित दीर्घ	__unused4;
	अचिन्हित दीर्घ	__unused5;
पूर्ण;

काष्ठा stat64  अणु
	अचिन्हित दीर्घ दीर्घ st_dev;	/* Device */
	अचिन्हित दीर्घ दीर्घ st_ino;	/* File serial number */
	अचिन्हित पूर्णांक  st_mode;		/* File mode. */
	अचिन्हित पूर्णांक  st_nlink;		/* Link count. */
	अचिन्हित पूर्णांक  st_uid;		/* User ID of the file's owner. */
	अचिन्हित पूर्णांक  st_gid;		/* Group ID of the file's group. */
	अचिन्हित दीर्घ दीर्घ st_rdev;	/* Device number, अगर device. */
	दीर्घ दीर्घ st_size;		/* Size of file, in bytes. */
	अचिन्हित दीर्घ st_blksize;	/* Optimal block size क्रम I/O. */
	अचिन्हित दीर्घ __unused2;
	अचिन्हित दीर्घ दीर्घ st_blocks;	/* Number 512-byte blocks allocated. */
	अचिन्हित दीर्घ st_aसमय;		/* Time of last access. */
	अचिन्हित दीर्घ st_aसमय_nsec;
	अचिन्हित दीर्घ st_mसमय;		/* Time of last modअगरication. */
	अचिन्हित दीर्घ st_mसमय_nsec;
	अचिन्हित दीर्घ st_स_समय;		/* Time of last status change. */
	अचिन्हित दीर्घ st_स_समय_nsec;
	अचिन्हित दीर्घ __unused4;
	अचिन्हित दीर्घ __unused5;
पूर्ण;

#पूर्ण_अगर	/* _XTENSA_STAT_H */
