<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_GENERIC_H
#घोषणा _SCSI_GENERIC_H

#समावेश <linux/compiler.h>

/*
 * History:
 *  Started: Aug 9 by Lawrence Foard (entropy@world.std.com), to allow user
 *   process control of SCSI devices.
 *  Development Sponsored by Killy Corp. NY NY
 *
 * Original driver (sg.h):
 *       Copyright (C) 1992 Lawrence Foard
 * Version 2 and 3 extensions to driver:
 *	Copyright (C) 1998 - 2014 Douglas Gilbert
 *
 *  Version: 3.5.36 (20140603)
 *  This version is क्रम 2.6 and 3 series kernels.
 *
 * Documentation
 * =============
 * A web site क्रम the SG device driver can be found at:
 *	http://sg.danny.cz/sg  [alternatively check the MAINTAINERS file]
 * The करोcumentation क्रम the sg version 3 driver can be found at:
 *	http://sg.danny.cz/sg/p/sg_v3_ho.hपंचांगl
 * Also see: <kernel_source>/Documentation/scsi/scsi-generic.rst
 *
 * For utility and test programs see: http://sg.danny.cz/sg/sg3_utils.hपंचांगl
 */

#अगर_घोषित __KERNEL__
बाह्य पूर्णांक sg_big_buff; /* क्रम sysctl */
#पूर्ण_अगर


प्रकार काष्ठा sg_iovec /* same काष्ठाure as used by पढ़ोv() Linux प्रणाली */
अणु                       /* call. It defines one scatter-gather element. */
    व्योम __user *iov_base;      /* Starting address  */
    माप_प्रकार iov_len;             /* Length in bytes  */
पूर्ण sg_iovec_t;


प्रकार काष्ठा sg_io_hdr
अणु
    पूर्णांक पूर्णांकerface_id;           /* [i] 'S' क्रम SCSI generic (required) */
    पूर्णांक dxfer_direction;        /* [i] data transfer direction  */
    अचिन्हित अक्षर cmd_len;      /* [i] SCSI command length */
    अचिन्हित अक्षर mx_sb_len;    /* [i] max length to ग_लिखो to sbp */
    अचिन्हित लघु iovec_count; /* [i] 0 implies no scatter gather */
    अचिन्हित पूर्णांक dxfer_len;     /* [i] byte count of data transfer */
    व्योम __user *dxferp;	/* [i], [*io] poपूर्णांकs to data transfer memory
					      or scatter gather list */
    अचिन्हित अक्षर __user *cmdp; /* [i], [*i] poपूर्णांकs to command to perक्रमm */
    व्योम __user *sbp;		/* [i], [*o] poपूर्णांकs to sense_buffer memory */
    अचिन्हित पूर्णांक समयout;       /* [i] MAX_UINT->no समयout (unit: millisec) */
    अचिन्हित पूर्णांक flags;         /* [i] 0 -> शेष, see SG_FLAG... */
    पूर्णांक pack_id;                /* [i->o] unused पूर्णांकernally (normally) */
    व्योम __user * usr_ptr;      /* [i->o] unused पूर्णांकernally */
    अचिन्हित अक्षर status;       /* [o] scsi status */
    अचिन्हित अक्षर masked_status;/* [o] shअगरted, masked scsi status */
    अचिन्हित अक्षर msg_status;   /* [o] messaging level data (optional) */
    अचिन्हित अक्षर sb_len_wr;    /* [o] byte count actually written to sbp */
    अचिन्हित लघु host_status; /* [o] errors from host adapter */
    अचिन्हित लघु driver_status;/* [o] errors from software driver */
    पूर्णांक resid;                  /* [o] dxfer_len - actual_transferred */
    अचिन्हित पूर्णांक duration;      /* [o] समय taken by cmd (unit: millisec) */
    अचिन्हित पूर्णांक info;          /* [o] auxiliary inक्रमmation */
पूर्ण sg_io_hdr_t;  /* 64 bytes दीर्घ (on i386) */

#अगर defined(__KERNEL__)
#समावेश <linux/compat.h>

काष्ठा compat_sg_io_hdr अणु
	compat_पूर्णांक_t पूर्णांकerface_id;	/* [i] 'S' क्रम SCSI generic (required) */
	compat_पूर्णांक_t dxfer_direction;	/* [i] data transfer direction  */
	अचिन्हित अक्षर cmd_len;		/* [i] SCSI command length ( <= 16 bytes) */
	अचिन्हित अक्षर mx_sb_len;	/* [i] max length to ग_लिखो to sbp */
	अचिन्हित लघु iovec_count;	/* [i] 0 implies no scatter gather */
	compat_uपूर्णांक_t dxfer_len;	/* [i] byte count of data transfer */
	compat_uपूर्णांक_t dxferp;		/* [i], [*io] poपूर्णांकs to data transfer memory
						or scatter gather list */
	compat_uptr_t cmdp;		/* [i], [*i] poपूर्णांकs to command to perक्रमm */
	compat_uptr_t sbp;		/* [i], [*o] poपूर्णांकs to sense_buffer memory */
	compat_uपूर्णांक_t समयout;		/* [i] MAX_UINT->no समयout (unit: millisec) */
	compat_uपूर्णांक_t flags;		/* [i] 0 -> शेष, see SG_FLAG... */
	compat_पूर्णांक_t pack_id;		/* [i->o] unused पूर्णांकernally (normally) */
	compat_uptr_t usr_ptr;		/* [i->o] unused पूर्णांकernally */
	अचिन्हित अक्षर status;		/* [o] scsi status */
	अचिन्हित अक्षर masked_status;	/* [o] shअगरted, masked scsi status */
	अचिन्हित अक्षर msg_status;	/* [o] messaging level data (optional) */
	अचिन्हित अक्षर sb_len_wr;	/* [o] byte count actually written to sbp */
	अचिन्हित लघु host_status;	/* [o] errors from host adapter */
	अचिन्हित लघु driver_status;	/* [o] errors from software driver */
	compat_पूर्णांक_t resid;		/* [o] dxfer_len - actual_transferred */
	compat_uपूर्णांक_t duration;		/* [o] समय taken by cmd (unit: millisec) */
	compat_uपूर्णांक_t info;		/* [o] auxiliary inक्रमmation */
पूर्ण;
#पूर्ण_अगर

#घोषणा SG_INTERFACE_ID_ORIG 'S'

/* Use negative values to flag dअगरference from original sg_header काष्ठाure */
#घोषणा SG_DXFER_NONE (-1)      /* e.g. a SCSI Test Unit Ready command */
#घोषणा SG_DXFER_TO_DEV (-2)    /* e.g. a SCSI WRITE command */
#घोषणा SG_DXFER_FROM_DEV (-3)  /* e.g. a SCSI READ command */
#घोषणा SG_DXFER_TO_FROM_DEV (-4) /* treated like SG_DXFER_FROM_DEV with the
				   additional property than during indirect
				   IO the user buffer is copied पूर्णांकo the
				   kernel buffers beक्रमe the transfer */
#घोषणा SG_DXFER_UNKNOWN (-5)   /* Unknown data direction */

/* following flag values can be "or"-ed together */
#घोषणा SG_FLAG_सूचीECT_IO 1     /* शेष is indirect IO */
#घोषणा SG_FLAG_UNUSED_LUN_INHIBIT 2   /* शेष is overग_लिखो lun in SCSI */
				/* command block (when <= SCSI_2) */
#घोषणा SG_FLAG_MMAP_IO 4       /* request memory mapped IO */
#घोषणा SG_FLAG_NO_DXFER 0x10000 /* no transfer of kernel buffers to/from */
				/* user space (debug indirect IO) */
/* शेषs:: क्रम sg driver: Q_AT_HEAD; क्रम block layer: Q_AT_TAIL */
#घोषणा SG_FLAG_Q_AT_TAIL 0x10
#घोषणा SG_FLAG_Q_AT_HEAD 0x20

/* following 'info' values are "or"-ed together */
#घोषणा SG_INFO_OK_MASK 0x1
#घोषणा SG_INFO_OK 0x0          /* no sense, host nor driver "noise" */
#घोषणा SG_INFO_CHECK 0x1       /* something abnormal happened */

#घोषणा SG_INFO_सूचीECT_IO_MASK 0x6
#घोषणा SG_INFO_INसूचीECT_IO 0x0 /* data xfer via kernel buffers (or no xfer) */
#घोषणा SG_INFO_सूचीECT_IO 0x2   /* direct IO requested and perक्रमmed */
#घोषणा SG_INFO_MIXED_IO 0x4    /* part direct, part indirect IO */


प्रकार काष्ठा sg_scsi_id अणु /* used by SG_GET_SCSI_ID ioctl() */
    पूर्णांक host_no;        /* as in "scsi<n>" where 'n' is one of 0, 1, 2 etc */
    पूर्णांक channel;
    पूर्णांक scsi_id;        /* scsi id of target device */
    पूर्णांक lun;
    पूर्णांक scsi_type;      /* TYPE_... defined in scsi/scsi.h */
    लघु h_cmd_per_lun;/* host (adapter) maximum commands per lun */
    लघु d_queue_depth;/* device (or adapter) maximum queue length */
    पूर्णांक unused[2];      /* probably find a good use, set 0 क्रम now */
पूर्ण sg_scsi_id_t; /* 32 bytes दीर्घ on i386 */

प्रकार काष्ठा sg_req_info अणु /* used by SG_GET_REQUEST_TABLE ioctl() */
    अक्षर req_state;     /* 0 -> not used, 1 -> written, 2 -> पढ़ोy to पढ़ो */
    अक्षर orphan;        /* 0 -> normal request, 1 -> from पूर्णांकerruped SG_IO */
    अक्षर sg_io_owned;   /* 0 -> complete with पढ़ो(), 1 -> owned by SG_IO */
    अक्षर problem;       /* 0 -> no problem detected, 1 -> error to report */
    पूर्णांक pack_id;        /* pack_id associated with request */
    व्योम __user *usr_ptr;     /* user provided poपूर्णांकer (in new पूर्णांकerface) */
    अचिन्हित पूर्णांक duration; /* millisecs elapsed since written (req_state==1)
			      or request duration (req_state==2) */
    पूर्णांक unused;
पूर्ण sg_req_info_t; /* 20 bytes दीर्घ on i386 */


/* IOCTLs: Those ioctls that are relevant to the SG 3.x drivers follow.
 [Those that only apply to the SG 2.x drivers are at the end of the file.]
 (_GET_s yield result via 'int *' 3rd argument unless otherwise indicated) */

#घोषणा SG_EMULATED_HOST 0x2203 /* true क्रम emulated host adapter (ATAPI) */

/* Used to configure SCSI command transक्रमmation layer क्रम ATAPI devices */
/* Only supported by the ide-scsi driver */
#घोषणा SG_SET_TRANSFORM 0x2204 /* N.B. 3rd arg is not poपूर्णांकer but value: */
		      /* 3rd arg = 0 to disable transक्रमm, 1 to enable it */
#घोषणा SG_GET_TRANSFORM 0x2205

#घोषणा SG_SET_RESERVED_SIZE 0x2275  /* request a new reserved buffer size */
#घोषणा SG_GET_RESERVED_SIZE 0x2272  /* actual size of reserved buffer */

/* The following ioctl has a 'sg_scsi_id_t *' object as its 3rd argument. */
#घोषणा SG_GET_SCSI_ID 0x2276   /* Yields fd's bus, chan, dev, lun + type */
/* SCSI id inक्रमmation can also be obtained from SCSI_IOCTL_GET_IDLUN */

/* Override host setting and always DMA using low memory ( <16MB on i386) */
#घोषणा SG_SET_FORCE_LOW_DMA 0x2279  /* 0-> use adapter setting, 1-> क्रमce */
#घोषणा SG_GET_LOW_DMA 0x227a   /* 0-> use all ram क्रम dma; 1-> low dma ram */

/* When SG_SET_FORCE_PACK_ID set to 1, pack_id is input to पढ़ो() which
   tries to fetch a packet with a matching pack_id, रुकोs, or वापसs EAGAIN.
   If pack_id is -1 then पढ़ो oldest रुकोing. When ...FORCE_PACK_ID set to 0
   then pack_id ignored by पढ़ो() and oldest पढ़ोable fetched. */
#घोषणा SG_SET_FORCE_PACK_ID 0x227b
#घोषणा SG_GET_PACK_ID 0x227c /* Yields oldest पढ़ोable pack_id (or -1) */

#घोषणा SG_GET_NUM_WAITING 0x227d /* Number of commands aरुकोing पढ़ो() */

/* Yields max scatter gather tablesize allowed by current host adapter */
#घोषणा SG_GET_SG_TABLESIZE 0x227F  /* 0 implies can't करो scatter gather */

#घोषणा SG_GET_VERSION_NUM 0x2282 /* Example: version 2.1.34 yields 20134 */

/* Returns -EBUSY अगर occupied. 3rd argument poपूर्णांकer to पूर्णांक (see next) */
#घोषणा SG_SCSI_RESET 0x2284
/* Associated values that can be given to SG_SCSI_RESET follow.
 * SG_SCSI_RESET_NO_ESCALATE may be OR-ed to the _DEVICE, _TARGET, _BUS
 * or _HOST reset value so only that action is attempted. */
#घोषणा		SG_SCSI_RESET_NOTHING	0
#घोषणा		SG_SCSI_RESET_DEVICE	1
#घोषणा		SG_SCSI_RESET_BUS	2
#घोषणा		SG_SCSI_RESET_HOST	3
#घोषणा		SG_SCSI_RESET_TARGET	4
#घोषणा		SG_SCSI_RESET_NO_ESCALATE	0x100

/* synchronous SCSI command ioctl, (only in version 3 पूर्णांकerface) */
#घोषणा SG_IO 0x2285   /* similar effect as ग_लिखो() followed by पढ़ो() */

#घोषणा SG_GET_REQUEST_TABLE 0x2286   /* yields table of active requests */

/* How to treat EINTR during SG_IO ioctl(), only in SG 3.x series */
#घोषणा SG_SET_KEEP_ORPHAN 0x2287 /* 1 -> hold क्रम पढ़ो(), 0 -> drop (def) */
#घोषणा SG_GET_KEEP_ORPHAN 0x2288

/* yields scsi midlevel's access_count क्रम this SCSI device */
#घोषणा SG_GET_ACCESS_COUNT 0x2289  


#घोषणा SG_SCATTER_SZ (8 * 4096)
/* Largest size (in bytes) a single scatter-gather list element can have.
   The value used by the driver is 'max(SG_SCATTER_SZ, PAGE_SIZE)'.
   This value should be a घातer of 2 (and may be rounded up पूर्णांकernally).
   If scatter-gather is not supported by adapter then this value is the
   largest data block that can be पढ़ो/written by a single scsi command. */

#घोषणा SG_DEFAULT_RETRIES 0

/* Defaults, commented अगर they dअगरfer from original sg driver */
#घोषणा SG_DEF_FORCE_PACK_ID 0
#घोषणा SG_DEF_KEEP_ORPHAN 0
#घोषणा SG_DEF_RESERVED_SIZE SG_SCATTER_SZ /* load समय option */

/* maximum outstanding requests, ग_लिखो() yields गलत_तर्क अगर exceeded */
#घोषणा SG_MAX_QUEUE 16

#घोषणा SG_BIG_BUFF SG_DEF_RESERVED_SIZE    /* क्रम backward compatibility */

/* Alternate style type names, "..._t" variants preferred */
प्रकार काष्ठा sg_io_hdr Sg_io_hdr;
प्रकार काष्ठा sg_io_vec Sg_io_vec;
प्रकार काष्ठा sg_scsi_id Sg_scsi_id;
प्रकार काष्ठा sg_req_info Sg_req_info;


/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
/*   The older SG पूर्णांकerface based on the 'sg_header' काष्ठाure follows.   */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

#घोषणा SG_MAX_SENSE 16   /* this only applies to the sg_header पूर्णांकerface */

काष्ठा sg_header
अणु
    पूर्णांक pack_len;    /* [o] reply_len (ie useless), ignored as input */
    पूर्णांक reply_len;   /* [i] max length of expected reply (inc. sg_header) */
    पूर्णांक pack_id;     /* [io] id number of packet (use पूर्णांकs >= 0) */
    पूर्णांक result;      /* [o] 0==ok, अन्यथा (+ve) Unix त्रुटि_सं (best ignored) */
    अचिन्हित पूर्णांक twelve_byte:1;
	/* [i] Force 12 byte command length क्रम group 6 & 7 commands  */
    अचिन्हित पूर्णांक target_status:5;   /* [o] scsi status from target */
    अचिन्हित पूर्णांक host_status:8;     /* [o] host status (see "DID" codes) */
    अचिन्हित पूर्णांक driver_status:8;   /* [o] driver status+suggestion */
    अचिन्हित पूर्णांक other_flags:10;    /* unused */
    अचिन्हित अक्षर sense_buffer[SG_MAX_SENSE]; /* [o] Output in 3 हालs:
	   when target_status is CHECK_CONDITION or
	   when target_status is COMMAND_TERMINATED or
	   when (driver_status & DRIVER_SENSE) is true. */
पूर्ण;      /* This काष्ठाure is 36 bytes दीर्घ on i386 */


/* IOCTLs: The following are not required (or ignored) when the sg_io_hdr_t
	   पूर्णांकerface is used. They are kept क्रम backward compatibility with
	   the original and version 2 drivers. */

#घोषणा SG_SET_TIMEOUT 0x2201  /* unit: jअगरfies (10ms on i386) */
#घोषणा SG_GET_TIMEOUT 0x2202  /* yield समयout as _वापस_ value */

/* Get/set command queuing state per fd (शेष is SG_DEF_COMMAND_Q.
   Each समय a sg_io_hdr_t object is seen on this file descriptor, this
   command queuing flag is set on (overriding the previous setting). */
#घोषणा SG_GET_COMMAND_Q 0x2270   /* Yields 0 (queuing off) or 1 (on) */
#घोषणा SG_SET_COMMAND_Q 0x2271   /* Change queuing state with 0 or 1 */

/* Turn on/off error sense trace (1 and 0 respectively, शेष is off).
   Try using: "# cat /proc/scsi/sg/debug" instead in the v3 driver */
#घोषणा SG_SET_DEBUG 0x227e    /* 0 -> turn off debug */

#घोषणा SG_NEXT_CMD_LEN 0x2283  /* override SCSI command length with given
		   number on the next ग_लिखो() on this file descriptor */


/* Defaults, commented अगर they dअगरfer from original sg driver */
#अगर_घोषित __KERNEL__
#घोषणा SG_DEFAULT_TIMEOUT_USER	(60*USER_HZ) /* HZ == 'jiffies in 1 second' */
#अन्यथा
#घोषणा SG_DEFAULT_TIMEOUT	(60*HZ)	     /* HZ == 'jiffies in 1 second' */
#पूर्ण_अगर

#घोषणा SG_DEF_COMMAND_Q 0     /* command queuing is always on when
				  the new पूर्णांकerface is used */
#घोषणा SG_DEF_UNDERRUN_FLAG 0

#पूर्ण_अगर
