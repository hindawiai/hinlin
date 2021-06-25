<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __UNIX_DIAG_H__
#घोषणा __UNIX_DIAG_H__

#समावेश <linux/types.h>

काष्ठा unix_diag_req अणु
	__u8	sdiag_family;
	__u8	sdiag_protocol;
	__u16	pad;
	__u32	udiag_states;
	__u32	udiag_ino;
	__u32	udiag_show;
	__u32	udiag_cookie[2];
पूर्ण;

#घोषणा UDIAG_SHOW_NAME		0x00000001	/* show name (not path) */
#घोषणा UDIAG_SHOW_VFS		0x00000002	/* show VFS inode info */
#घोषणा UDIAG_SHOW_PEER		0x00000004	/* show peer socket info */
#घोषणा UDIAG_SHOW_ICONS	0x00000008	/* show pending connections */
#घोषणा UDIAG_SHOW_RQLEN	0x00000010	/* show skb receive queue len */
#घोषणा UDIAG_SHOW_MEMINFO	0x00000020	/* show memory info of a socket */
#घोषणा UDIAG_SHOW_UID		0x00000040	/* show socket's UID */

काष्ठा unix_diag_msg अणु
	__u8	udiag_family;
	__u8	udiag_type;
	__u8	udiag_state;
	__u8	pad;

	__u32	udiag_ino;
	__u32	udiag_cookie[2];
पूर्ण;

क्रमागत अणु
	/* UNIX_DIAG_NONE, standard nl API requires this attribute!  */
	UNIX_DIAG_NAME,
	UNIX_DIAG_VFS,
	UNIX_DIAG_PEER,
	UNIX_DIAG_ICONS,
	UNIX_DIAG_RQLEN,
	UNIX_DIAG_MEMINFO,
	UNIX_DIAG_SHUTDOWN,
	UNIX_DIAG_UID,

	__UNIX_DIAG_MAX,
पूर्ण;

#घोषणा UNIX_DIAG_MAX (__UNIX_DIAG_MAX - 1)

काष्ठा unix_diag_vfs अणु
	__u32	udiag_vfs_ino;
	__u32	udiag_vfs_dev;
पूर्ण;

काष्ठा unix_diag_rqlen अणु
	__u32	udiag_rqueue;
	__u32	udiag_wqueue;
पूर्ण;

#पूर्ण_अगर
