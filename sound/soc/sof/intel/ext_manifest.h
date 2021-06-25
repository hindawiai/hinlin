<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 */

/*
 * Intel extended manअगरest is a extra place to store Intel cavs specअगरic
 * metadata about firmware, क्रम example LPRO/HPRO configuration is
 * Intel cavs specअगरic. This part of output binary is not चिन्हित.
 */

#अगर_अघोषित __INTEL_CAVS_EXT_MANIFEST_H__
#घोषणा __INTEL_CAVS_EXT_MANIFEST_H__

#समावेश <sound/sof/ext_manअगरest.h>

/* EXT_MAN_ELEM_PLATFORM_CONFIG_DATA elements identअगरicators */
क्रमागत sof_cavs_config_elem_type अणु
	SOF_EXT_MAN_CAVS_CONFIG_EMPTY		= 0,
	SOF_EXT_MAN_CAVS_CONFIG_CAVS_LPRO	= 1,
	SOF_EXT_MAN_CAVS_CONFIG_OUTBOX_SIZE	= 2,
	SOF_EXT_MAN_CAVS_CONFIG_INBOX_SIZE	= 3,
पूर्ण;

/* EXT_MAN_ELEM_PLATFORM_CONFIG_DATA elements */
काष्ठा sof_ext_man_cavs_config_data अणु
	काष्ठा sof_ext_man_elem_header hdr;

	काष्ठा sof_config_elem elems[];
पूर्ण __packed;

#पूर्ण_अगर /* __INTEL_CAVS_EXT_MANIFEST_H__ */
