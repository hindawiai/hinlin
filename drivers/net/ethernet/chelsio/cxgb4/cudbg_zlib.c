<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2018 Chelsio Communications.  All rights reserved.
 */

#समावेश <linux/zlib.h>

#समावेश "cxgb4.h"
#समावेश "cudbg_if.h"
#समावेश "cudbg_lib_common.h"
#समावेश "cudbg_zlib.h"

अटल पूर्णांक cudbg_get_compress_hdr(काष्ठा cudbg_buffer *pdbg_buff,
				  काष्ठा cudbg_buffer *pin_buff)
अणु
	अगर (pdbg_buff->offset + माप(काष्ठा cudbg_compress_hdr) >
	    pdbg_buff->size)
		वापस CUDBG_STATUS_NO_MEM;

	pin_buff->data = (अक्षर *)pdbg_buff->data + pdbg_buff->offset;
	pin_buff->offset = 0;
	pin_buff->size = माप(काष्ठा cudbg_compress_hdr);
	pdbg_buff->offset += माप(काष्ठा cudbg_compress_hdr);
	वापस 0;
पूर्ण

पूर्णांक cudbg_compress_buff(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *pin_buff,
			काष्ठा cudbg_buffer *pout_buff)
अणु
	काष्ठा cudbg_buffer temp_buff = अणु 0 पूर्ण;
	काष्ठा z_stream_s compress_stream;
	काष्ठा cudbg_compress_hdr *c_hdr;
	पूर्णांक rc;

	/* Write compression header to output buffer beक्रमe compression */
	rc = cudbg_get_compress_hdr(pout_buff, &temp_buff);
	अगर (rc)
		वापस rc;

	c_hdr = (काष्ठा cudbg_compress_hdr *)temp_buff.data;
	c_hdr->compress_id = CUDBG_ZLIB_COMPRESS_ID;

	स_रखो(&compress_stream, 0, माप(काष्ठा z_stream_s));
	compress_stream.workspace = pdbg_init->workspace;
	rc = zlib_deflateInit2(&compress_stream, Z_DEFAULT_COMPRESSION,
			       Z_DEFLATED, CUDBG_ZLIB_WIN_BITS,
			       CUDBG_ZLIB_MEM_LVL, Z_DEFAULT_STRATEGY);
	अगर (rc != Z_OK)
		वापस CUDBG_SYSTEM_ERROR;

	compress_stream.next_in = pin_buff->data;
	compress_stream.avail_in = pin_buff->size;
	compress_stream.next_out = pout_buff->data + pout_buff->offset;
	compress_stream.avail_out = pout_buff->size - pout_buff->offset;

	rc = zlib_deflate(&compress_stream, Z_FINISH);
	अगर (rc != Z_STREAM_END)
		वापस CUDBG_SYSTEM_ERROR;

	rc = zlib_deflateEnd(&compress_stream);
	अगर (rc != Z_OK)
		वापस CUDBG_SYSTEM_ERROR;

	c_hdr->compress_size = compress_stream.total_out;
	c_hdr->decompress_size = pin_buff->size;
	pout_buff->offset += compress_stream.total_out;

	वापस 0;
पूर्ण
