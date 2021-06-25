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

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

#समावेश "common.h"
#समावेश "zip_inflate.h"

अटल पूर्णांक prepare_inflate_zcmd(काष्ठा zip_operation *zip_ops,
				काष्ठा zip_state *s, जोड़ zip_inst_s *zip_cmd)
अणु
	जोड़ zip_zres_s *result_ptr = &s->result;

	स_रखो(zip_cmd, 0, माप(s->zip_cmd));
	स_रखो(result_ptr, 0, माप(s->result));

	/* IWORD#0 */

	/* Decompression History Gather list - no gather list */
	zip_cmd->s.hg = 0;
	/* For decompression, CE must be 0x0. */
	zip_cmd->s.ce = 0;
	/* For decompression, SS must be 0x0. */
	zip_cmd->s.ss = 0;
	/* For decompression, SF should always be set. */
	zip_cmd->s.sf = 1;

	/* Begin File */
	अगर (zip_ops->begin_file == 0)
		zip_cmd->s.bf = 0;
	अन्यथा
		zip_cmd->s.bf = 1;

	zip_cmd->s.ef = 1;
	/* 0: क्रम Deflate decompression, 3: क्रम LZS decompression */
	zip_cmd->s.cc = zip_ops->ccode;

	/* IWORD #1*/

	/* adler checksum */
	zip_cmd->s.adlercrc32 = zip_ops->csum;

	/*
	 * HISTORYLENGTH must be 0x0 क्रम any ZIP decompress operation.
	 * History data is added to a decompression operation via IWORD3.
	 */
	zip_cmd->s.historylength = 0;
	zip_cmd->s.ds = 0;

	/* IWORD # 8 and 9 - Output poपूर्णांकer */
	zip_cmd->s.out_ptr_addr.s.addr  = __pa(zip_ops->output);
	zip_cmd->s.out_ptr_ctl.s.length = zip_ops->output_len;

	/* Maximum number of output-stream bytes that can be written */
	zip_cmd->s.totaloutputlength    = zip_ops->output_len;

	zip_dbg("Data Direct Input case ");

	/* IWORD # 6 and 7 - input poपूर्णांकer */
	zip_cmd->s.dg = 0;
	zip_cmd->s.inp_ptr_addr.s.addr  = __pa((u8 *)zip_ops->input);
	zip_cmd->s.inp_ptr_ctl.s.length = zip_ops->input_len;

	/* IWORD # 10 and 11 - Result poपूर्णांकer */
	zip_cmd->s.res_ptr_addr.s.addr = __pa(result_ptr);

	/* Clearing completion code */
	result_ptr->s.compcode = 0;

	/* Returning 0 क्रम समय being.*/
	वापस 0;
पूर्ण

/**
 * zip_inflate - API to offload inflate operation to hardware
 * @zip_ops: Poपूर्णांकer to zip operation काष्ठाure
 * @s:       Poपूर्णांकer to the काष्ठाure representing zip state
 * @zip_dev: Poपूर्णांकer to zip device काष्ठाure
 *
 * This function prepares the zip inflate command and submits it to the zip
 * engine क्रम processing.
 *
 * Return: 0 अगर successful or error code
 */
पूर्णांक zip_inflate(काष्ठा zip_operation *zip_ops, काष्ठा zip_state *s,
		काष्ठा zip_device *zip_dev)
अणु
	जोड़ zip_inst_s *zip_cmd    = &s->zip_cmd;
	जोड़ zip_zres_s  *result_ptr = &s->result;
	u32 queue;

	/* Prepare inflate zip command */
	prepare_inflate_zcmd(zip_ops, s, zip_cmd);

	atomic64_add(zip_ops->input_len, &zip_dev->stats.decomp_in_bytes);

	/* Load inflate command to zip queue and ring the करोorbell */
	queue = zip_load_instr(zip_cmd, zip_dev);

	/* Decompression requests submitted stats update */
	atomic64_inc(&zip_dev->stats.decomp_req_submit);

	/* Wait क्रम completion or error */
	zip_poll_result(result_ptr);

	/* Decompression requests completed stats update */
	atomic64_inc(&zip_dev->stats.decomp_req_complete);

	zip_ops->compcode = result_ptr->s.compcode;
	चयन (zip_ops->compcode) अणु
	हाल ZIP_CMD_NOTDONE:
		zip_dbg("Zip Instruction not yet completed\n");
		वापस ZIP_ERROR;

	हाल ZIP_CMD_SUCCESS:
		zip_dbg("Zip Instruction completed successfully\n");
		अवरोध;

	हाल ZIP_CMD_DYNAMIC_STOP:
		zip_dbg(" Dynamic stop Initiated\n");
		अवरोध;

	शेष:
		zip_dbg("Instruction failed. Code = %d\n", zip_ops->compcode);
		atomic64_inc(&zip_dev->stats.decomp_bad_reqs);
		zip_update_cmd_bufs(zip_dev, queue);
		वापस ZIP_ERROR;
	पूर्ण

	zip_update_cmd_bufs(zip_dev, queue);

	अगर ((zip_ops->ccode == 3) && (zip_ops->flush == 4) &&
	    (zip_ops->compcode != ZIP_CMD_DYNAMIC_STOP))
		result_ptr->s.ef = 1;

	zip_ops->csum = result_ptr->s.adler32;

	atomic64_add(result_ptr->s.totalbyteswritten,
		     &zip_dev->stats.decomp_out_bytes);

	अगर (zip_ops->output_len < result_ptr->s.totalbyteswritten) अणु
		zip_err("output_len (%d) < total bytes written (%d)\n",
			zip_ops->output_len, result_ptr->s.totalbyteswritten);
		zip_ops->output_len = 0;
	पूर्ण अन्यथा अणु
		zip_ops->output_len = result_ptr->s.totalbyteswritten;
	पूर्ण

	zip_ops->bytes_पढ़ो = result_ptr->s.totalbytesपढ़ो;
	zip_ops->bits_processed = result_ptr->s.totalbitsprocessed;
	zip_ops->end_file = result_ptr->s.ef;
	अगर (zip_ops->end_file) अणु
		चयन (zip_ops->क्रमmat) अणु
		हाल RAW_FORMAT:
			zip_dbg("RAW Format: %d ", zip_ops->क्रमmat);
			/* Get checksum from engine */
			zip_ops->csum = result_ptr->s.adler32;
			अवरोध;

		हाल ZLIB_FORMAT:
			zip_dbg("ZLIB Format: %d ", zip_ops->क्रमmat);
			zip_ops->csum = result_ptr->s.adler32;
			अवरोध;

		हाल GZIP_FORMAT:
			zip_dbg("GZIP Format: %d ", zip_ops->क्रमmat);
			zip_ops->csum = result_ptr->s.crc32;
			अवरोध;

		हाल LZS_FORMAT:
			zip_dbg("LZS Format: %d ", zip_ops->क्रमmat);
			अवरोध;

		शेष:
			zip_err("Format error:%d\n", zip_ops->क्रमmat);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
