<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CXGB4_CUDBG_H__
#घोषणा __CXGB4_CUDBG_H__

#समावेश "cudbg_if.h"
#समावेश "cudbg_lib_common.h"
#समावेश "cudbg_entity.h"
#समावेश "cudbg_lib.h"

#घोषणा CUDBG_DUMP_BUFF_SIZE (32 * 1024 * 1024) /* 32 MB */
#घोषणा CUDBG_COMPRESS_BUFF_SIZE (4 * 1024 * 1024) /* 4 MB */

प्रकार पूर्णांक (*cudbg_collect_callback_t)(काष्ठा cudbg_init *pdbg_init,
					काष्ठा cudbg_buffer *dbg_buff,
					काष्ठा cudbg_error *cudbg_err);

काष्ठा cxgb4_collect_entity अणु
	क्रमागत cudbg_dbg_entity_type entity;
	cudbg_collect_callback_t collect_cb;
पूर्ण;

क्रमागत CXGB4_ETHTOOL_DUMP_FLAGS अणु
	CXGB4_ETH_DUMP_NONE = ETH_FW_DUMP_DISABLE,
	CXGB4_ETH_DUMP_MEM = (1 << 0), /* On-Chip Memory Dumps */
	CXGB4_ETH_DUMP_HW = (1 << 1), /* various FW and HW dumps */
	CXGB4_ETH_DUMP_FLASH = (1 << 2), /* Dump flash memory */
पूर्ण;

#घोषणा CXGB4_ETH_DUMP_ALL (CXGB4_ETH_DUMP_MEM | CXGB4_ETH_DUMP_HW)

u32 cxgb4_get_dump_length(काष्ठा adapter *adap, u32 flag);
पूर्णांक cxgb4_cudbg_collect(काष्ठा adapter *adap, व्योम *buf, u32 *buf_size,
			u32 flag);
व्योम cxgb4_init_ethtool_dump(काष्ठा adapter *adapter);
पूर्णांक cxgb4_cudbg_vmcore_add_dump(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_CUDBG_H__ */
