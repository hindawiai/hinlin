<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000, 2001, 2002 Broadcom Corporation
 */
#अगर_अघोषित CFE_API_INT_H
#घोषणा CFE_API_INT_H

/*
 * Constants.
 */
#घोषणा CFE_CMD_FW_GETINFO	0
#घोषणा CFE_CMD_FW_RESTART	1
#घोषणा CFE_CMD_FW_BOOT		2
#घोषणा CFE_CMD_FW_CPUCTL	3
#घोषणा CFE_CMD_FW_GETTIME      4
#घोषणा CFE_CMD_FW_MEMENUM	5
#घोषणा CFE_CMD_FW_FLUSHCACHE	6

#घोषणा CFE_CMD_DEV_GETHANDLE	9
#घोषणा CFE_CMD_DEV_ENUM	10
#घोषणा CFE_CMD_DEV_OPEN	11
#घोषणा CFE_CMD_DEV_INPSTAT	12
#घोषणा CFE_CMD_DEV_READ	13
#घोषणा CFE_CMD_DEV_WRITE	14
#घोषणा CFE_CMD_DEV_IOCTL	15
#घोषणा CFE_CMD_DEV_CLOSE	16
#घोषणा CFE_CMD_DEV_GETINFO	17

#घोषणा CFE_CMD_ENV_ENUM	20
#घोषणा CFE_CMD_ENV_GET		22
#घोषणा CFE_CMD_ENV_SET		23
#घोषणा CFE_CMD_ENV_DEL		24

#घोषणा CFE_CMD_MAX		32

#घोषणा CFE_CMD_VENDOR_USE	0x8000	/* codes above this are क्रम customer use */

/*
 * Structures.
 */

/* eeek, चिन्हित "pointers" */
प्रकार s64 cfe_xptr_t;

काष्ठा xiocb_buffer अणु
	u64 buf_offset;		/* offset on device (bytes) */
	cfe_xptr_t  buf_ptr;		/* poपूर्णांकer to a buffer */
	u64 buf_length;		/* length of this buffer */
	u64 buf_retlen;		/* वापसed length (क्रम पढ़ो ops) */
	u64 buf_ioctlcmd;	/* IOCTL command (used only क्रम IOCTLs) */
पूर्ण;

काष्ठा xiocb_inpstat अणु
	u64 inp_status;		/* 1 means input available */
पूर्ण;

काष्ठा xiocb_envbuf अणु
	s64 क्रमागत_idx;		/* 0-based क्रमागतeration index */
	cfe_xptr_t name_ptr;		/* name string buffer */
	s64 name_length;		/* size of name buffer */
	cfe_xptr_t val_ptr;		/* value string buffer */
	s64 val_length;		/* size of value string buffer */
पूर्ण;

काष्ठा xiocb_cpuctl अणु
	u64 cpu_number;		/* cpu number to control */
	u64 cpu_command;	/* command to issue to CPU */
	u64 start_addr;		/* CPU start address */
	u64 gp_val;		/* starting GP value */
	u64 sp_val;		/* starting SP value */
	u64 a1_val;		/* starting A1 value */
पूर्ण;

काष्ठा xiocb_समय अणु
	s64 ticks;		/* current समय in ticks */
पूर्ण;

काष्ठा xiocb_निकासstatअणु
	s64 status;
पूर्ण;

काष्ठा xiocb_meminfo अणु
	s64 mi_idx;		/* 0-based क्रमागतeration index */
	s64 mi_type;		/* type of memory block */
	u64 mi_addr;		/* physical start address */
	u64 mi_size;		/* block size */
पूर्ण;

काष्ठा xiocb_fwinfo अणु
	s64 fwi_version;		/* major, minor, eco version */
	s64 fwi_totalmem;	/* total installed mem */
	s64 fwi_flags;		/* various flags */
	s64 fwi_boardid;		/* board ID */
	s64 fwi_bootarea_va;	/* VA of boot area */
	s64 fwi_bootarea_pa;	/* PA of boot area */
	s64 fwi_bootarea_size;	/* size of boot area */
	s64 fwi_reserved1;
	s64 fwi_reserved2;
	s64 fwi_reserved3;
पूर्ण;

काष्ठा cfe_xiocb अणु
	u64 xiocb_fcode;	/* IOCB function code */
	s64 xiocb_status;	/* वापस status */
	s64 xiocb_handle;	/* file/device handle */
	u64 xiocb_flags;	/* flags क्रम this IOCB */
	u64 xiocb_psize;	/* size of parameter list */
	जोड़ अणु
		/* buffer parameters */
		काष्ठा xiocb_buffer xiocb_buffer;

		/* input status parameters */
		काष्ठा xiocb_inpstat xiocb_inpstat;

		/* environment function parameters */
		काष्ठा xiocb_envbuf xiocb_envbuf;

		/* CPU control parameters */
		काष्ठा xiocb_cpuctl xiocb_cpuctl;

		/* समयr parameters */
		काष्ठा xiocb_समय xiocb_समय;

		/* memory arena info parameters */
		काष्ठा xiocb_meminfo xiocb_meminfo;

		/* firmware inक्रमmation */
		काष्ठा xiocb_fwinfo xiocb_fwinfo;

		/* Exit Status */
		काष्ठा xiocb_निकासstat xiocb_निकासstat;
	पूर्ण plist;
पूर्ण;

#पूर्ण_अगर /* CFE_API_INT_H */
