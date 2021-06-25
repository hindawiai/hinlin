<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright 1996, 1997, 1998 Hans Reiser, see reiserfs/README क्रम licensing and copyright details
 */
#अगर_अघोषित _LINUX_REISER_FS_H
#घोषणा _LINUX_REISER_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/*
 *  include/linux/reiser_fs.h
 *
 *  Reiser File System स्थिरants and काष्ठाures
 *
 */

/* ioctl's command */
#घोषणा REISERFS_IOC_UNPACK		_IOW(0xCD,1,दीर्घ)
/* define following flags to be the same as in ext2, so that chattr(1),
   lsattr(1) will work with us. */
#घोषणा REISERFS_IOC_GETFLAGS		FS_IOC_GETFLAGS
#घोषणा REISERFS_IOC_SETFLAGS		FS_IOC_SETFLAGS
#घोषणा REISERFS_IOC_GETVERSION		FS_IOC_GETVERSION
#घोषणा REISERFS_IOC_SETVERSION		FS_IOC_SETVERSION

#पूर्ण_अगर				/* _LINUX_REISER_FS_H */
