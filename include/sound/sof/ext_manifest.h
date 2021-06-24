<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 */

/*
 * Extended manअगरest is a place to store metadata about firmware, known during
 * compilation समय - क्रम example firmware version or used compiler.
 * Given inक्रमmation are पढ़ो on host side beक्रमe firmware startup.
 * This part of output binary is not चिन्हित.
 */

#अगर_अघोषित __SOF_FIRMWARE_EXT_MANIFEST_H__
#घोषणा __SOF_FIRMWARE_EXT_MANIFEST_H__

#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <sound/sof/info.h>

/* In ASCII `XMan` */
#घोषणा SOF_EXT_MAN_MAGIC_NUMBER	0x6e614d58

/* Build u32 number in क्रमmat MMmmmppp */
#घोषणा SOF_EXT_MAN_BUILD_VERSION(MAJOR, MINOR, PATH) ((uपूर्णांक32_t)( \
	((MAJOR) << 24) | \
	((MINOR) << 12) | \
	(PATH)))

/* check extended manअगरest version consistency */
#घोषणा SOF_EXT_MAN_VERSION_INCOMPATIBLE(host_ver, cli_ver) ( \
	((host_ver) & GENMASK(31, 24)) != \
	((cli_ver) & GENMASK(31, 24)))

/* used extended manअगरest header version */
#घोषणा SOF_EXT_MAN_VERSION		SOF_EXT_MAN_BUILD_VERSION(1, 0, 0)

/* extended manअगरest header, deleting any field अवरोधs backward compatibility */
काष्ठा sof_ext_man_header अणु
	uपूर्णांक32_t magic;		/*< identअगरication number, */
				/*< EXT_MAN_MAGIC_NUMBER */
	uपूर्णांक32_t full_size;	/*< [bytes] full size of ext_man, */
				/*< (header + content + padding) */
	uपूर्णांक32_t header_size;	/*< [bytes] makes header extensionable, */
				/*< after append new field to ext_man header */
				/*< then backward compatible won't be lost */
	uपूर्णांक32_t header_version; /*< value of EXT_MAN_VERSION */
				/*< not related with following content */

	/* just after this header should be list of ext_man_elem_* elements */
पूर्ण __packed;

/* Now define extended manअगरest elements */

/* Extended manअगरest elements types */
क्रमागत sof_ext_man_elem_type अणु
	SOF_EXT_MAN_ELEM_FW_VERSION		= 0,
	SOF_EXT_MAN_ELEM_WINDOW			= 1,
	SOF_EXT_MAN_ELEM_CC_VERSION		= 2,
	SOF_EXT_MAN_ELEM_DBG_ABI		= 4,
	SOF_EXT_MAN_ELEM_CONFIG_DATA		= 5, /**< ABI3.17 */
	SOF_EXT_MAN_ELEM_PLATFORM_CONFIG_DATA   = 6,
पूर्ण;

/* extended manअगरest element header */
काष्ठा sof_ext_man_elem_header अणु
	uपूर्णांक32_t type;		/*< SOF_EXT_MAN_ELEM_ */
	uपूर्णांक32_t size;		/*< in bytes, including header size */

	/* just after this header should be type dependent content */
पूर्ण __packed;

/* FW version */
काष्ठा sof_ext_man_fw_version अणु
	काष्ठा sof_ext_man_elem_header hdr;
	/* use sof_ipc काष्ठा because of code re-use */
	काष्ठा sof_ipc_fw_version version;
	uपूर्णांक32_t flags;
पूर्ण __packed;

/* extended data memory winकरोws क्रम IPC, trace and debug */
काष्ठा sof_ext_man_winकरोw अणु
	काष्ठा sof_ext_man_elem_header hdr;
	/* use sof_ipc काष्ठा because of code re-use */
	काष्ठा sof_ipc_winकरोw ipc_winकरोw;
पूर्ण __packed;

/* Used C compiler description */
काष्ठा sof_ext_man_cc_version अणु
	काष्ठा sof_ext_man_elem_header hdr;
	/* use sof_ipc काष्ठा because of code re-use */
	काष्ठा sof_ipc_cc_version cc_version;
पूर्ण __packed;

काष्ठा ext_man_dbg_abi अणु
	काष्ठा sof_ext_man_elem_header hdr;
	/* use sof_ipc काष्ठा because of code re-use */
	काष्ठा sof_ipc_user_abi_version dbg_abi;
पूर्ण __packed;

/* EXT_MAN_ELEM_CONFIG_DATA elements identअगरicators, ABI3.17 */
क्रमागत config_elem_type अणु
	SOF_EXT_MAN_CONFIG_EMPTY		= 0,
	SOF_EXT_MAN_CONFIG_IPC_MSG_SIZE		= 1,
	SOF_EXT_MAN_CONFIG_MEMORY_USAGE_SCAN	= 2, /**< ABI 3.18 */
पूर्ण;

काष्ठा sof_config_elem अणु
	uपूर्णांक32_t token;
	uपूर्णांक32_t value;
पूर्ण __packed;

/* firmware configuration inक्रमmation */
काष्ठा sof_ext_man_config_data अणु
	काष्ठा sof_ext_man_elem_header hdr;

	काष्ठा sof_config_elem elems[];
पूर्ण __packed;

#पूर्ण_अगर /* __SOF_FIRMWARE_EXT_MANIFEST_H__ */
