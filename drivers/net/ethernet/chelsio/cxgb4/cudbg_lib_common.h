<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CUDBG_LIB_COMMON_H__
#घोषणा __CUDBG_LIB_COMMON_H__

#घोषणा CUDBG_SIGNATURE 67856866 /* CUDB in ascii */

क्रमागत cudbg_dump_type अणु
	CUDBG_DUMP_TYPE_MINI = 1,
पूर्ण;

क्रमागत cudbg_compression_type अणु
	CUDBG_COMPRESSION_NONE = 1,
	CUDBG_COMPRESSION_ZLIB,
पूर्ण;

काष्ठा cudbg_hdr अणु
	u32 signature;
	u32 hdr_len;
	u16 major_ver;
	u16 minor_ver;
	u32 data_len;
	u32 hdr_flags;
	u16 max_entities;
	u8 chip_ver;
	u8 dump_type:3;
	u8 reserved1:1;
	u8 compress_type:4;
	u32 reserved[8];
पूर्ण;

काष्ठा cudbg_entity_hdr अणु
	u32 entity_type;
	u32 start_offset;
	u32 size;
	पूर्णांक hdr_flags;
	u32 sys_warn;
	u32 sys_err;
	u8 num_pad;
	u8 flag;             /* bit 0 is used to indicate ext data */
	u8 reserved1[2];
	u32 next_ext_offset; /* poपूर्णांकer to next extended entity meta data */
	u32 reserved[5];
पूर्ण;

काष्ठा cudbg_ver_hdr अणु
	u32 signature;
	u16 revision;
	u16 size;
पूर्ण;

काष्ठा cudbg_buffer अणु
	u32 size;
	u32 offset;
	अक्षर *data;
पूर्ण;

काष्ठा cudbg_error अणु
	पूर्णांक sys_err;
	पूर्णांक sys_warn;
	पूर्णांक app_err;
पूर्ण;

#घोषणा CDUMP_MAX_COMP_BUF_SIZE ((64 * 1024) - 1)
#घोषणा CUDBG_CHUNK_SIZE ((CDUMP_MAX_COMP_BUF_SIZE / 1024) * 1024)

पूर्णांक cudbg_get_buff(काष्ठा cudbg_init *pdbg_init,
		   काष्ठा cudbg_buffer *pdbg_buff, u32 size,
		   काष्ठा cudbg_buffer *pin_buff);
व्योम cudbg_put_buff(काष्ठा cudbg_init *pdbg_init,
		    काष्ठा cudbg_buffer *pin_buff);
व्योम cudbg_update_buff(काष्ठा cudbg_buffer *pin_buff,
		       काष्ठा cudbg_buffer *pout_buff);
#पूर्ण_अगर /* __CUDBG_LIB_COMMON_H__ */
