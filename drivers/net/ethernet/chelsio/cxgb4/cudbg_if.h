<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CUDBG_IF_H__
#घोषणा __CUDBG_IF_H__

/* Error codes */
#घोषणा CUDBG_STATUS_NO_MEM -19
#घोषणा CUDBG_STATUS_ENTITY_NOT_FOUND -24
#घोषणा CUDBG_STATUS_NOT_IMPLEMENTED -28
#घोषणा CUDBG_SYSTEM_ERROR -29
#घोषणा CUDBG_STATUS_CCLK_NOT_DEFINED -32
#घोषणा CUDBG_STATUS_PARTIAL_DATA -41

#घोषणा CUDBG_MAJOR_VERSION 1
#घोषणा CUDBG_MINOR_VERSION 14

क्रमागत cudbg_dbg_entity_type अणु
	CUDBG_REG_DUMP = 1,
	CUDBG_DEV_LOG = 2,
	CUDBG_CIM_LA = 3,
	CUDBG_CIM_MA_LA = 4,
	CUDBG_CIM_QCFG = 5,
	CUDBG_CIM_IBQ_TP0 = 6,
	CUDBG_CIM_IBQ_TP1 = 7,
	CUDBG_CIM_IBQ_ULP = 8,
	CUDBG_CIM_IBQ_SGE0 = 9,
	CUDBG_CIM_IBQ_SGE1 = 10,
	CUDBG_CIM_IBQ_NCSI = 11,
	CUDBG_CIM_OBQ_ULP0 = 12,
	CUDBG_CIM_OBQ_ULP1 = 13,
	CUDBG_CIM_OBQ_ULP2 = 14,
	CUDBG_CIM_OBQ_ULP3 = 15,
	CUDBG_CIM_OBQ_SGE = 16,
	CUDBG_CIM_OBQ_NCSI = 17,
	CUDBG_EDC0 = 18,
	CUDBG_EDC1 = 19,
	CUDBG_MC0 = 20,
	CUDBG_MC1 = 21,
	CUDBG_RSS = 22,
	CUDBG_RSS_VF_CONF = 25,
	CUDBG_PATH_MTU = 27,
	CUDBG_PM_STATS = 30,
	CUDBG_HW_SCHED = 31,
	CUDBG_TP_INसूचीECT = 36,
	CUDBG_SGE_INसूचीECT = 37,
	CUDBG_ULPRX_LA = 41,
	CUDBG_TP_LA = 43,
	CUDBG_MEMINFO = 44,
	CUDBG_CIM_PIF_LA = 45,
	CUDBG_CLK = 46,
	CUDBG_CIM_OBQ_RXQ0 = 47,
	CUDBG_CIM_OBQ_RXQ1 = 48,
	CUDBG_PCIE_INसूचीECT = 50,
	CUDBG_PM_INसूचीECT = 51,
	CUDBG_TID_INFO = 54,
	CUDBG_PCIE_CONFIG = 55,
	CUDBG_DUMP_CONTEXT = 56,
	CUDBG_MPS_TCAM = 57,
	CUDBG_VPD_DATA = 58,
	CUDBG_LE_TCAM = 59,
	CUDBG_CCTRL = 60,
	CUDBG_MA_INसूचीECT = 61,
	CUDBG_ULPTX_LA = 62,
	CUDBG_UP_CIM_INसूचीECT = 64,
	CUDBG_PBT_TABLE = 65,
	CUDBG_MBOX_LOG = 66,
	CUDBG_HMA_INसूचीECT = 67,
	CUDBG_HMA = 68,
	CUDBG_QDESC = 70,
	CUDBG_FLASH = 71,
	CUDBG_MAX_ENTITY = 72,
पूर्ण;

काष्ठा cudbg_init अणु
	काष्ठा adapter *adap; /* Poपूर्णांकer to adapter काष्ठाure */
	व्योम *outbuf; /* Output buffer */
	u32 outbuf_size;  /* Output buffer size */
	u8 compress_type; /* Type of compression to use */
	व्योम *compress_buff; /* Compression buffer */
	u32 compress_buff_size; /* Compression buffer size */
	व्योम *workspace; /* Workspace क्रम zlib */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक cudbg_mbytes_to_bytes(अचिन्हित पूर्णांक size)
अणु
	वापस size * 1024 * 1024;
पूर्ण
#पूर्ण_अगर /* __CUDBG_IF_H__ */
