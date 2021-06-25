<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -*- linux-c -*- --------------------------------------------------------- *
 *
 * linux/include/linux/devpts_fs.h
 *
 *  Copyright 1998-2004 H. Peter Anvin -- All Rights Reserved
 *
 * ------------------------------------------------------------------------- */

#अगर_अघोषित _LINUX_DEVPTS_FS_H
#घोषणा _LINUX_DEVPTS_FS_H

#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_UNIX98_PTYS

काष्ठा pts_fs_info;

काष्ठा vfsmount *devpts_mntget(काष्ठा file *, काष्ठा pts_fs_info *);
काष्ठा pts_fs_info *devpts_acquire(काष्ठा file *);
व्योम devpts_release(काष्ठा pts_fs_info *);

पूर्णांक devpts_new_index(काष्ठा pts_fs_info *);
व्योम devpts_समाप्त_index(काष्ठा pts_fs_info *, पूर्णांक);

/* mknod in devpts */
काष्ठा dentry *devpts_pty_new(काष्ठा pts_fs_info *, पूर्णांक, व्योम *);
/* get निजी काष्ठाure */
व्योम *devpts_get_priv(काष्ठा dentry *);
/* unlink */
व्योम devpts_pty_समाप्त(काष्ठा dentry *);

/* in pty.c */
पूर्णांक pपंचांग_खोलो_peer(काष्ठा file *master, काष्ठा tty_काष्ठा *tty, पूर्णांक flags);

#अन्यथा
अटल अंतरभूत पूर्णांक
pपंचांग_खोलो_peer(काष्ठा file *master, काष्ठा tty_काष्ठा *tty, पूर्णांक flags)
अणु
	वापस -EIO;
पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर /* _LINUX_DEVPTS_FS_H */
