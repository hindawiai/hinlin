<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
  File: linux/reiserfs_xattr.h
*/

#अगर_अघोषित _LINUX_REISERFS_XATTR_H
#घोषणा _LINUX_REISERFS_XATTR_H

#समावेश <linux/types.h>

/* Magic value in header */
#घोषणा REISERFS_XATTR_MAGIC 0x52465841	/* "RFXA" */

काष्ठा reiserfs_xattr_header अणु
	__le32 h_magic;		/* magic number क्रम identअगरication */
	__le32 h_hash;		/* hash of the value */
पूर्ण;

काष्ठा reiserfs_security_handle अणु
	स्थिर अक्षर *name;
	व्योम *value;
	माप_प्रकार length;
पूर्ण;

#पूर्ण_अगर  /*  _LINUX_REISERFS_XATTR_H  */
