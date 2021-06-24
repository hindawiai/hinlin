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

#अगर_अघोषित __COMMON_H__
#घोषणा __COMMON_H__

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

/* Device specअगरic zlib function definitions */
#समावेश "zip_device.h"

/* ZIP device definitions */
#समावेश "zip_main.h"

/* ZIP memory allocation/deallocation related definitions */
#समावेश "zip_mem.h"

/* Device specअगरic काष्ठाure definitions */
#समावेश "zip_regs.h"

#घोषणा ZIP_ERROR    -1

#घोषणा ZIP_FLUSH_FINISH  4

#घोषणा RAW_FORMAT		0  /* क्रम rawpipe */
#घोषणा ZLIB_FORMAT		1  /* क्रम zpipe */
#घोषणा GZIP_FORMAT		2  /* क्रम gzpipe */
#घोषणा LZS_FORMAT		3  /* क्रम lzspipe */

/* Max number of ZIP devices supported */
#घोषणा MAX_ZIP_DEVICES		2

/* Configures the number of zip queues to be used */
#घोषणा ZIP_NUM_QUEUES		2

#घोषणा DYNAMIC_STOP_EXCESS	1024

/* Maximum buffer sizes in direct mode */
#घोषणा MAX_INPUT_BUFFER_SIZE   (64 * 1024)
#घोषणा MAX_OUTPUT_BUFFER_SIZE  (64 * 1024)

/**
 * काष्ठा zip_operation - common data काष्ठाure क्रम comp and decomp operations
 * @input:               Next input byte is पढ़ो from here
 * @output:              Next output byte written here
 * @ctx_addr:            Inflate context buffer address
 * @history:             Poपूर्णांकer to the history buffer
 * @input_len:           Number of bytes available at next_in
 * @input_total_len:     Total number of input bytes पढ़ो
 * @output_len:          Reमुख्यing मुक्त space at next_out
 * @output_total_len:    Total number of bytes output so far
 * @csum:                Checksum value of the uncompressed data
 * @flush:               Flush flag
 * @क्रमmat:              Format (depends on stream's wrap)
 * @speed:               Speed depends on stream's level
 * @ccode:               Compression code ( stream's strategy)
 * @lzs_flag:            Flag क्रम LZS support
 * @begin_file:          Beginning of file indication क्रम inflate
 * @history_len:         Size of the history data
 * @end_file:            Ending of the file indication क्रम inflate
 * @compcode:            Completion status of the ZIP invocation
 * @bytes_पढ़ो:          Input bytes पढ़ो in current inकाष्ठाion
 * @bits_processed:      Total bits processed क्रम entire file
 * @मापptr:           To distinguish between ILP32 and LP64
 * @मापzops:          Optional just क्रम padding
 *
 * This काष्ठाure is used to मुख्यtain the required meta data क्रम the
 * comp and decomp operations.
 */
काष्ठा zip_operation अणु
	u8    *input;
	u8    *output;
	u64   ctx_addr;
	u64   history;

	u32   input_len;
	u32   input_total_len;

	u32   output_len;
	u32   output_total_len;

	u32   csum;
	u32   flush;

	u32   क्रमmat;
	u32   speed;
	u32   ccode;
	u32   lzs_flag;

	u32   begin_file;
	u32   history_len;

	u32   end_file;
	u32   compcode;
	u32   bytes_पढ़ो;
	u32   bits_processed;

	u32   मापptr;
	u32   मापzops;
पूर्ण;

अटल अंतरभूत पूर्णांक zip_poll_result(जोड़ zip_zres_s *result)
अणु
	पूर्णांक retries = 1000;

	जबतक (!result->s.compcode) अणु
		अगर (!--retries) अणु
			pr_err("ZIP ERR: request timed out");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(10);
		/*
		 * Force re-पढ़ोing of compcode which is updated
		 * by the ZIP coprocessor.
		 */
		rmb();
	पूर्ण
	वापस 0;
पूर्ण

/* error messages */
#घोषणा zip_err(fmt, args...) pr_err("ZIP ERR:%s():%d: " \
			      fmt "\n", __func__, __LINE__, ## args)

#अगर_घोषित MSG_ENABLE
/* Enable all messages */
#घोषणा zip_msg(fmt, args...) pr_info("ZIP_MSG:" fmt "\n", ## args)
#अन्यथा
#घोषणा zip_msg(fmt, args...)
#पूर्ण_अगर

#अगर defined(ZIP_DEBUG_ENABLE) && defined(MSG_ENABLE)

#अगर_घोषित DEBUG_LEVEL

#घोषणा खाता_NAME (म_खोजप(__खाता__, '/') ? strrchr(__FILE__, '/') + 1 : \
	म_खोजप(__खाता__, '\\') ? strrchr(__FILE__, '\\') + 1 : __खाता__)

#अगर DEBUG_LEVEL >= 4

#घोषणा zip_dbg(fmt, args...) pr_info("ZIP DBG: %s: %s() : %d: " \
			      fmt "\n", खाता_NAME, __func__, __LINE__, ## args)

#या_अगर DEBUG_LEVEL >= 3

#घोषणा zip_dbg(fmt, args...) pr_info("ZIP DBG: %s: %s() : %d: " \
			      fmt "\n", खाता_NAME, __func__, __LINE__, ## args)

#या_अगर DEBUG_LEVEL >= 2

#घोषणा zip_dbg(fmt, args...) pr_info("ZIP DBG: %s() : %d: " \
			      fmt "\n", __func__, __LINE__, ## args)

#अन्यथा

#घोषणा zip_dbg(fmt, args...) pr_info("ZIP DBG:" fmt "\n", ## args)

#पूर्ण_अगर /* DEBUG LEVEL >=4 */

#अन्यथा

#घोषणा zip_dbg(fmt, args...) pr_info("ZIP DBG:" fmt "\n", ## args)

#पूर्ण_अगर /* DEBUG_LEVEL */
#अन्यथा

#घोषणा zip_dbg(fmt, args...)

#पूर्ण_अगर /* ZIP_DEBUG_ENABLE && MSG_ENABLE*/

#पूर्ण_अगर
