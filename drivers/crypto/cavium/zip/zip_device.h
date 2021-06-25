<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#अगर_अघोषित __ZIP_DEVICE_H__
#घोषणा __ZIP_DEVICE_H__

#समावेश <linux/types.h>
#समावेश "zip_main.h"

काष्ठा sg_info अणु
	/*
	 * Poपूर्णांकer to the input data when scatter_gather == 0 and
	 * poपूर्णांकer to the input gather list buffer when scatter_gather == 1
	 */
	जोड़ zip_zptr_s *gather;

	/*
	 * Poपूर्णांकer to the output data when scatter_gather == 0 and
	 * poपूर्णांकer to the output scatter list buffer when scatter_gather == 1
	 */
	जोड़ zip_zptr_s *scatter;

	/*
	 * Holds size of the output buffer poपूर्णांकed by scatter list
	 * when scatter_gather == 1
	 */
	u64 scatter_buf_size;

	/* क्रम gather data */
	u64 gather_enable;

	/* क्रम scatter data */
	u64 scatter_enable;

	/* Number of gather list poपूर्णांकers क्रम gather data */
	u32 gbuf_cnt;

	/* Number of scatter list poपूर्णांकers क्रम scatter data */
	u32 sbuf_cnt;

	/* Buffers allocation state */
	u8 alloc_state;
पूर्ण;

/**
 * काष्ठा zip_state - Structure representing the required inक्रमmation related
 *                    to a command
 * @zip_cmd: Poपूर्णांकer to zip inकाष्ठाion काष्ठाure
 * @result:  Poपूर्णांकer to zip result काष्ठाure
 * @ctx:     Context poपूर्णांकer क्रम inflate
 * @history: Decompression history poपूर्णांकer
 * @sginfo:  Scatter-gather info काष्ठाure
 */
काष्ठा zip_state अणु
	जोड़ zip_inst_s zip_cmd;
	जोड़ zip_zres_s result;
	जोड़ zip_zptr_s *ctx;
	जोड़ zip_zptr_s *history;
	काष्ठा sg_info   sginfo;
पूर्ण;

#घोषणा ZIP_CONTEXT_SIZE          2048
#घोषणा ZIP_INFLATE_HISTORY_SIZE  32768
#घोषणा ZIP_DEFLATE_HISTORY_SIZE  32768

#पूर्ण_अगर
