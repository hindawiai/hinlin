<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_VMCORE_H
#घोषणा _UAPI_VMCORE_H

#समावेश <linux/types.h>

#घोषणा VMCOREDD_NOTE_NAME "LINUX"
#घोषणा VMCOREDD_MAX_NAME_BYTES 44

काष्ठा vmcoredd_header अणु
	__u32 n_namesz; /* Name size */
	__u32 n_descsz; /* Content size */
	__u32 n_type;   /* NT_VMCOREDD */
	__u8 name[8];   /* LINUX\0\0\0 */
	__u8 dump_name[VMCOREDD_MAX_NAME_BYTES]; /* Device dump's name */
पूर्ण;

#पूर्ण_अगर /* _UAPI_VMCORE_H */
