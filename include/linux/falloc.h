<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FALLOC_H_
#घोषणा _FALLOC_H_

#समावेश <uapi/linux/fभाग.स>


/*
 * Space reservation ioctls and argument काष्ठाure
 * are deचिन्हित to be compatible with the legacy XFS ioctls.
 */
काष्ठा space_resv अणु
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start;
	__s64		l_len;		/* len == 0 means until end of file */
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserved area */
पूर्ण;

#घोषणा FS_IOC_RESVSP		_IOW('X', 40, काष्ठा space_resv)
#घोषणा FS_IOC_UNRESVSP		_IOW('X', 41, काष्ठा space_resv)
#घोषणा FS_IOC_RESVSP64		_IOW('X', 42, काष्ठा space_resv)
#घोषणा FS_IOC_UNRESVSP64	_IOW('X', 43, काष्ठा space_resv)
#घोषणा FS_IOC_ZERO_RANGE	_IOW('X', 57, काष्ठा space_resv)

#घोषणा	FALLOC_FL_SUPPORTED_MASK	(FALLOC_FL_KEEP_SIZE |		\
					 FALLOC_FL_PUNCH_HOLE |		\
					 FALLOC_FL_COLLAPSE_RANGE |	\
					 FALLOC_FL_ZERO_RANGE |		\
					 FALLOC_FL_INSERT_RANGE |	\
					 FALLOC_FL_UNSHARE_RANGE)

/* on ia32 l_start is on a 32-bit boundary */
#अगर defined(CONFIG_X86_64)
काष्ठा space_resv_32 अणु
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start	__attribute__((packed));
			/* len == 0 means until end of file */
	__s64		l_len __attribute__((packed));
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserve area */
पूर्ण;

#घोषणा FS_IOC_RESVSP_32	_IOW ('X', 40, काष्ठा space_resv_32)
#घोषणा FS_IOC_UNRESVSP_32	_IOW ('X', 41, काष्ठा space_resv_32)
#घोषणा FS_IOC_RESVSP64_32	_IOW ('X', 42, काष्ठा space_resv_32)
#घोषणा FS_IOC_UNRESVSP64_32	_IOW ('X', 43, काष्ठा space_resv_32)
#घोषणा FS_IOC_ZERO_RANGE_32	_IOW ('X', 57, काष्ठा space_resv_32)

#पूर्ण_अगर

#पूर्ण_अगर /* _FALLOC_H_ */
