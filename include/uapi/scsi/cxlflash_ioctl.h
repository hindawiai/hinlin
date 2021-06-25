<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _CXLFLASH_IOCTL_H
#घोषणा _CXLFLASH_IOCTL_H

#समावेश <linux/types.h>

/*
 * Structure and definitions क्रम all CXL Flash ioctls
 */
#घोषणा CXLFLASH_WWID_LEN		16

/*
 * Structure and flag definitions CXL Flash superpipe ioctls
 */

#घोषणा DK_CXLFLASH_VERSION_0	0

काष्ठा dk_cxlflash_hdr अणु
	__u16 version;			/* Version data */
	__u16 rsvd[3];			/* Reserved क्रम future use */
	__u64 flags;			/* Input flags */
	__u64 वापस_flags;		/* Returned flags */
पूर्ण;

/*
 * Return flag definitions available to all superpipe ioctls
 *
 * Similar to the input flags, these are grown from the bottom-up with the
 * पूर्णांकention that ioctl-specअगरic वापस flag definitions would grow from the
 * top-करोwn, allowing the two sets to co-exist. While not required/enक्रमced
 * at this समय, this provides future flexibility.
 */
#घोषणा DK_CXLFLASH_ALL_PORTS_ACTIVE	0x0000000000000001ULL
#घोषणा DK_CXLFLASH_APP_CLOSE_ADAP_FD	0x0000000000000002ULL
#घोषणा DK_CXLFLASH_CONTEXT_SQ_CMD_MODE	0x0000000000000004ULL

/*
 * General Notes:
 * -------------
 * The 'context_id' field of all ioctl काष्ठाures contains the context
 * identअगरier क्रम a context in the lower 32-bits (upper 32-bits are not
 * to be used when identअगरying a context to the AFU). That said, the value
 * in its entirety (all 64-bits) is to be treated as an opaque cookie and
 * should be presented as such when issuing ioctls.
 */

/*
 * DK_CXLFLASH_ATTACH Notes:
 * ------------------------
 * Read/ग_लिखो access permissions are specअगरied via the O_RDONLY, O_WRONLY,
 * and O_RDWR flags defined in the fcntl.h header file.
 *
 * A valid adapter file descriptor (fd >= 0) is only वापसed on the initial
 * attach (successful) of a context. When a context is shared(reused), the user
 * is expected to alपढ़ोy 'know' the adapter file descriptor associated with the
 * context.
 */
#घोषणा DK_CXLFLASH_ATTACH_REUSE_CONTEXT	0x8000000000000000ULL

काष्ठा dk_cxlflash_attach अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 num_पूर्णांकerrupts;		/* Requested number of पूर्णांकerrupts */
	__u64 context_id;		/* Returned context */
	__u64 mmio_size;		/* Returned size of MMIO area */
	__u64 block_size;		/* Returned block size, in bytes */
	__u64 adap_fd;			/* Returned adapter file descriptor */
	__u64 last_lba;			/* Returned last LBA on the device */
	__u64 max_xfer;			/* Returned max transfer size, blocks */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

काष्ठा dk_cxlflash_detach अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context to detach */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

काष्ठा dk_cxlflash_udirect अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context to own physical resources */
	__u64 rsrc_handle;		/* Returned resource handle */
	__u64 last_lba;			/* Returned last LBA on the device */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

#घोषणा DK_CXLFLASH_UVIRTUAL_NEED_WRITE_SAME	0x8000000000000000ULL

काष्ठा dk_cxlflash_uभव अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context to own भव resources */
	__u64 lun_size;			/* Requested size, in 4K blocks */
	__u64 rsrc_handle;		/* Returned resource handle */
	__u64 last_lba;			/* Returned last LBA of LUN */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

काष्ठा dk_cxlflash_release अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context owning resources */
	__u64 rsrc_handle;		/* Resource handle to release */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

काष्ठा dk_cxlflash_resize अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context owning resources */
	__u64 rsrc_handle;		/* Resource handle of LUN to resize */
	__u64 req_size;			/* New requested size, in 4K blocks */
	__u64 last_lba;			/* Returned last LBA of LUN */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

काष्ठा dk_cxlflash_clone अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id_src;		/* Context to clone from */
	__u64 context_id_dst;		/* Context to clone to */
	__u64 adap_fd_src;		/* Source context adapter fd */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

#घोषणा DK_CXLFLASH_VERIFY_SENSE_LEN	18
#घोषणा DK_CXLFLASH_VERIFY_HINT_SENSE	0x8000000000000000ULL

काष्ठा dk_cxlflash_verअगरy अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 context_id;		/* Context owning resources to verअगरy */
	__u64 rsrc_handle;		/* Resource handle of LUN */
	__u64 hपूर्णांक;			/* Reasons क्रम verअगरy */
	__u64 last_lba;			/* Returned last LBA of device */
	__u8 sense_data[DK_CXLFLASH_VERIFY_SENSE_LEN]; /* SCSI sense data */
	__u8 pad[6];			/* Pad to next 8-byte boundary */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

#घोषणा DK_CXLFLASH_RECOVER_AFU_CONTEXT_RESET	0x8000000000000000ULL

काष्ठा dk_cxlflash_recover_afu अणु
	काष्ठा dk_cxlflash_hdr hdr;	/* Common fields */
	__u64 reason;			/* Reason क्रम recovery request */
	__u64 context_id;		/* Context to recover / updated ID */
	__u64 mmio_size;		/* Returned size of MMIO area */
	__u64 adap_fd;			/* Returned adapter file descriptor */
	__u64 reserved[8];		/* Reserved क्रम future use */
पूर्ण;

#घोषणा DK_CXLFLASH_MANAGE_LUN_WWID_LEN			CXLFLASH_WWID_LEN
#घोषणा DK_CXLFLASH_MANAGE_LUN_ENABLE_SUPERPIPE		0x8000000000000000ULL
#घोषणा DK_CXLFLASH_MANAGE_LUN_DISABLE_SUPERPIPE	0x4000000000000000ULL
#घोषणा DK_CXLFLASH_MANAGE_LUN_ALL_PORTS_ACCESSIBLE	0x2000000000000000ULL

काष्ठा dk_cxlflash_manage_lun अणु
	काष्ठा dk_cxlflash_hdr hdr;			/* Common fields */
	__u8 wwid[DK_CXLFLASH_MANAGE_LUN_WWID_LEN];	/* Page83 WWID, NAA-6 */
	__u64 reserved[8];				/* Rsvd, future use */
पूर्ण;

जोड़ cxlflash_ioctls अणु
	काष्ठा dk_cxlflash_attach attach;
	काष्ठा dk_cxlflash_detach detach;
	काष्ठा dk_cxlflash_udirect udirect;
	काष्ठा dk_cxlflash_uभव uभव;
	काष्ठा dk_cxlflash_release release;
	काष्ठा dk_cxlflash_resize resize;
	काष्ठा dk_cxlflash_clone clone;
	काष्ठा dk_cxlflash_verअगरy verअगरy;
	काष्ठा dk_cxlflash_recover_afu recover_afu;
	काष्ठा dk_cxlflash_manage_lun manage_lun;
पूर्ण;

#घोषणा MAX_CXLFLASH_IOCTL_SZ	(माप(जोड़ cxlflash_ioctls))

#घोषणा CXL_MAGIC 0xCA
#घोषणा CXL_IOWR(_n, _s)	_IOWR(CXL_MAGIC, _n, काष्ठा _s)

/*
 * CXL Flash superpipe ioctls start at base of the reserved CXL_MAGIC
 * region (0x80) and grow upwards.
 */
#घोषणा DK_CXLFLASH_ATTACH		CXL_IOWR(0x80, dk_cxlflash_attach)
#घोषणा DK_CXLFLASH_USER_सूचीECT		CXL_IOWR(0x81, dk_cxlflash_udirect)
#घोषणा DK_CXLFLASH_RELEASE		CXL_IOWR(0x82, dk_cxlflash_release)
#घोषणा DK_CXLFLASH_DETACH		CXL_IOWR(0x83, dk_cxlflash_detach)
#घोषणा DK_CXLFLASH_VERIFY		CXL_IOWR(0x84, dk_cxlflash_verअगरy)
#घोषणा DK_CXLFLASH_RECOVER_AFU		CXL_IOWR(0x85, dk_cxlflash_recover_afu)
#घोषणा DK_CXLFLASH_MANAGE_LUN		CXL_IOWR(0x86, dk_cxlflash_manage_lun)
#घोषणा DK_CXLFLASH_USER_VIRTUAL	CXL_IOWR(0x87, dk_cxlflash_uभव)
#घोषणा DK_CXLFLASH_VLUN_RESIZE		CXL_IOWR(0x88, dk_cxlflash_resize)
#घोषणा DK_CXLFLASH_VLUN_CLONE		CXL_IOWR(0x89, dk_cxlflash_clone)

/*
 * Structure and flag definitions CXL Flash host ioctls
 */

#घोषणा HT_CXLFLASH_VERSION_0  0

काष्ठा ht_cxlflash_hdr अणु
	__u16 version;		/* Version data */
	__u16 subcmd;		/* Sub-command */
	__u16 rsvd[2];		/* Reserved क्रम future use */
	__u64 flags;		/* Input flags */
	__u64 वापस_flags;	/* Returned flags */
पूर्ण;

/*
 * Input flag definitions available to all host ioctls
 *
 * These are grown from the bottom-up with the पूर्णांकention that ioctl-specअगरic
 * input flag definitions would grow from the top-करोwn, allowing the two sets
 * to co-exist. While not required/enक्रमced at this समय, this provides future
 * flexibility.
 */
#घोषणा HT_CXLFLASH_HOST_READ				0x0000000000000000ULL
#घोषणा HT_CXLFLASH_HOST_WRITE				0x0000000000000001ULL

#घोषणा HT_CXLFLASH_LUN_PROVISION_SUBCMD_CREATE_LUN	0x0001
#घोषणा HT_CXLFLASH_LUN_PROVISION_SUBCMD_DELETE_LUN	0x0002
#घोषणा HT_CXLFLASH_LUN_PROVISION_SUBCMD_QUERY_PORT	0x0003

काष्ठा ht_cxlflash_lun_provision अणु
	काष्ठा ht_cxlflash_hdr hdr; /* Common fields */
	__u16 port;		    /* Target port क्रम provision request */
	__u16 reserved16[3];	    /* Reserved क्रम future use */
	__u64 size;		    /* Size of LUN (4K blocks) */
	__u64 lun_id;		    /* SCSI LUN ID */
	__u8 wwid[CXLFLASH_WWID_LEN];/* Page83 WWID, NAA-6 */
	__u64 max_num_luns;	    /* Maximum number of LUNs provisioned */
	__u64 cur_num_luns;	    /* Current number of LUNs provisioned */
	__u64 max_cap_port;	    /* Total capacity क्रम port (4K blocks) */
	__u64 cur_cap_port;	    /* Current capacity क्रम port (4K blocks) */
	__u64 reserved[8];	    /* Reserved क्रम future use */
पूर्ण;

#घोषणा	HT_CXLFLASH_AFU_DEBUG_MAX_DATA_LEN		262144	/* 256K */
#घोषणा HT_CXLFLASH_AFU_DEBUG_SUBCMD_LEN		12
काष्ठा ht_cxlflash_afu_debug अणु
	काष्ठा ht_cxlflash_hdr hdr; /* Common fields */
	__u8 reserved8[4];	    /* Reserved क्रम future use */
	__u8 afu_subcmd[HT_CXLFLASH_AFU_DEBUG_SUBCMD_LEN]; /* AFU subcommand,
							    * (pass through)
							    */
	__u64 data_ea;		    /* Data buffer effective address */
	__u32 data_len;		    /* Data buffer length */
	__u32 reserved32;	    /* Reserved क्रम future use */
	__u64 reserved[8];	    /* Reserved क्रम future use */
पूर्ण;

जोड़ cxlflash_ht_ioctls अणु
	काष्ठा ht_cxlflash_lun_provision lun_provision;
	काष्ठा ht_cxlflash_afu_debug afu_debug;
पूर्ण;

#घोषणा MAX_HT_CXLFLASH_IOCTL_SZ	(माप(जोड़ cxlflash_ht_ioctls))

/*
 * CXL Flash host ioctls start at the top of the reserved CXL_MAGIC
 * region (0xBF) and grow करोwnwards.
 */
#घोषणा HT_CXLFLASH_LUN_PROVISION CXL_IOWR(0xBF, ht_cxlflash_lun_provision)
#घोषणा HT_CXLFLASH_AFU_DEBUG	  CXL_IOWR(0xBE, ht_cxlflash_afu_debug)


#पूर्ण_अगर /* अगरndef _CXLFLASH_IOCTL_H */
