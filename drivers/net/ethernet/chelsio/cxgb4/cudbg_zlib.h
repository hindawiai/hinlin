<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2018 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CUDBG_ZLIB_H__
#घोषणा __CUDBG_ZLIB_H__

#समावेश <linux/zlib.h>

#घोषणा CUDBG_ZLIB_COMPRESS_ID 17
#घोषणा CUDBG_ZLIB_WIN_BITS 12
#घोषणा CUDBG_ZLIB_MEM_LVL 4

काष्ठा cudbg_compress_hdr अणु
	u32 compress_id;
	u64 decompress_size;
	u64 compress_size;
	u64 rsvd[32];
पूर्ण;

अटल अंतरभूत पूर्णांक cudbg_get_workspace_size(व्योम)
अणु
	वापस zlib_deflate_workspacesize(CUDBG_ZLIB_WIN_BITS,
					  CUDBG_ZLIB_MEM_LVL);
पूर्ण

पूर्णांक cudbg_compress_buff(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *pin_buff,
			काष्ठा cudbg_buffer *pout_buff);
#पूर्ण_अगर /* __CUDBG_ZLIB_H__ */
