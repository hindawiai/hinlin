<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

/*
 * Firmware file क्रमmat .
 */

#अगर_अघोषित __INCLUDE_UAPI_SOF_FW_H__
#घोषणा __INCLUDE_UAPI_SOF_FW_H__

#समावेश <linux/types.h>

#घोषणा SND_SOF_FW_SIG_SIZE	4
#घोषणा SND_SOF_FW_ABI		1
#घोषणा SND_SOF_FW_SIG		"Reef"

/*
 * Firmware module is made up of 1 . N blocks of dअगरferent types. The
 * Block header is used to determine where and how block is to be copied in the
 * DSP/host memory space.
 */
क्रमागत snd_sof_fw_blk_type अणु
	SOF_FW_BLK_TYPE_INVALID	= -1,
	SOF_FW_BLK_TYPE_START	= 0,
	SOF_FW_BLK_TYPE_RSRVD0	= SOF_FW_BLK_TYPE_START,
	SOF_FW_BLK_TYPE_IRAM	= 1,	/* local inकाष्ठाion RAM */
	SOF_FW_BLK_TYPE_DRAM	= 2,	/* local data RAM */
	SOF_FW_BLK_TYPE_SRAM	= 3,	/* प्रणाली RAM */
	SOF_FW_BLK_TYPE_ROM	= 4,
	SOF_FW_BLK_TYPE_IMR	= 5,
	SOF_FW_BLK_TYPE_RSRVD6	= 6,
	SOF_FW_BLK_TYPE_RSRVD7	= 7,
	SOF_FW_BLK_TYPE_RSRVD8	= 8,
	SOF_FW_BLK_TYPE_RSRVD9	= 9,
	SOF_FW_BLK_TYPE_RSRVD10	= 10,
	SOF_FW_BLK_TYPE_RSRVD11	= 11,
	SOF_FW_BLK_TYPE_RSRVD12	= 12,
	SOF_FW_BLK_TYPE_RSRVD13	= 13,
	SOF_FW_BLK_TYPE_RSRVD14	= 14,
	/* use SOF_FW_BLK_TYPE_RSVRDX क्रम new block types */
	SOF_FW_BLK_TYPE_NUM
पूर्ण;

काष्ठा snd_sof_blk_hdr अणु
	क्रमागत snd_sof_fw_blk_type type;
	__u32 size;		/* bytes minus this header */
	__u32 offset;		/* offset from base */
पूर्ण __packed;

/*
 * Firmware file is made up of 1 .. N dअगरferent modules types. The module
 * type is used to determine how to load and parse the module.
 */
क्रमागत snd_sof_fw_mod_type अणु
	SOF_FW_BASE	= 0,	/* base firmware image */
	SOF_FW_MODULE	= 1,	/* firmware module */
पूर्ण;

काष्ठा snd_sof_mod_hdr अणु
	क्रमागत snd_sof_fw_mod_type type;
	__u32 size;		/* bytes minus this header */
	__u32 num_blocks;	/* number of blocks */
पूर्ण __packed;

/*
 * Firmware file header.
 */
काष्ठा snd_sof_fw_header अणु
	अचिन्हित अक्षर sig[SND_SOF_FW_SIG_SIZE]; /* "Reef" */
	__u32 file_size;	/* size of file minus this header */
	__u32 num_modules;	/* number of modules */
	__u32 abi;		/* version of header क्रमmat */
पूर्ण __packed;

#पूर्ण_अगर
