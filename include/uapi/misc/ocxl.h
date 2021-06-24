<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* Copyright 2017 IBM Corp. */
#अगर_अघोषित _UAPI_MISC_OCXL_H
#घोषणा _UAPI_MISC_OCXL_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

क्रमागत ocxl_event_type अणु
	OCXL_AFU_EVENT_XSL_FAULT_ERROR = 0,
पूर्ण;

#घोषणा OCXL_KERNEL_EVENT_FLAG_LAST 0x0001  /* This is the last event pending */

काष्ठा ocxl_kernel_event_header अणु
	__u16 type;
	__u16 flags;
	__u32 reserved;
पूर्ण;

काष्ठा ocxl_kernel_event_xsl_fault_error अणु
	__u64 addr;
	__u64 dsisr;
	__u64 count;
	__u64 reserved;
पूर्ण;

काष्ठा ocxl_ioctl_attach अणु
	__u64 amr;
	__u64 reserved1;
	__u64 reserved2;
	__u64 reserved3;
पूर्ण;

काष्ठा ocxl_ioctl_metadata अणु
	__u16 version; /* काष्ठा version, always backwards compatible */

	/* Version 0 fields */
	__u8  afu_version_major;
	__u8  afu_version_minor;
	__u32 pasid;		/* PASID asचिन्हित to the current context */

	__u64 pp_mmio_size;	/* Per PASID MMIO size */
	__u64 global_mmio_size;

	/* End version 0 fields */

	__u64 reserved[13]; /* Total of 16*u64 */
पूर्ण;

काष्ठा ocxl_ioctl_p9_रुको अणु
	__u16 thपढ़ो_id; /* The thपढ़ो ID required to wake this thपढ़ो */
	__u16 reserved1;
	__u32 reserved2;
	__u64 reserved3[3];
पूर्ण;

#घोषणा OCXL_IOCTL_FEATURES_FLAGS0_P9_WAIT	0x01
काष्ठा ocxl_ioctl_features अणु
	__u64 flags[4];
पूर्ण;

काष्ठा ocxl_ioctl_irq_fd अणु
	__u64 irq_offset;
	__s32 eventfd;
	__u32 reserved;
पूर्ण;

/* ioctl numbers */
#घोषणा OCXL_MAGIC 0xCA
/* AFU devices */
#घोषणा OCXL_IOCTL_ATTACH	_IOW(OCXL_MAGIC, 0x10, काष्ठा ocxl_ioctl_attach)
#घोषणा OCXL_IOCTL_IRQ_ALLOC	_IOR(OCXL_MAGIC, 0x11, __u64)
#घोषणा OCXL_IOCTL_IRQ_FREE	_IOW(OCXL_MAGIC, 0x12, __u64)
#घोषणा OCXL_IOCTL_IRQ_SET_FD	_IOW(OCXL_MAGIC, 0x13, काष्ठा ocxl_ioctl_irq_fd)
#घोषणा OCXL_IOCTL_GET_METADATA _IOR(OCXL_MAGIC, 0x14, काष्ठा ocxl_ioctl_metadata)
#घोषणा OCXL_IOCTL_ENABLE_P9_WAIT	_IOR(OCXL_MAGIC, 0x15, काष्ठा ocxl_ioctl_p9_रुको)
#घोषणा OCXL_IOCTL_GET_FEATURES _IOR(OCXL_MAGIC, 0x16, काष्ठा ocxl_ioctl_features)

#पूर्ण_अगर /* _UAPI_MISC_OCXL_H */
