<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_HAL_TX_H
#घोषणा ATH11K_HAL_TX_H

#समावेश "hal_desc.h"
#समावेश "core.h"

#घोषणा HAL_TX_ADDRX_EN			1
#घोषणा HAL_TX_ADDRY_EN			2

#घोषणा HAL_TX_ADDR_SEARCH_DEFAULT	0
#घोषणा HAL_TX_ADDR_SEARCH_INDEX	1

काष्ठा hal_tx_info अणु
	u16 meta_data_flags; /* %HAL_TCL_DATA_CMD_INFO0_META_ */
	u8 ring_id;
	u32 desc_id;
	क्रमागत hal_tcl_desc_type type;
	क्रमागत hal_tcl_encap_type encap_type;
	dma_addr_t paddr;
	u32 data_len;
	u32 pkt_offset;
	क्रमागत hal_encrypt_type encrypt_type;
	u32 flags0; /* %HAL_TCL_DATA_CMD_INFO1_ */
	u32 flags1; /* %HAL_TCL_DATA_CMD_INFO2_ */
	u16 addr_search_flags; /* %HAL_TCL_DATA_CMD_INFO0_ADDR(X/Y)_ */
	u16 bss_ast_hash;
	u16 bss_ast_idx;
	u8 tid;
	u8 search_type; /* %HAL_TX_ADDR_SEARCH_ */
	u8 lmac_id;
	u8 dscp_tid_tbl_idx;
	bool enable_mesh;
पूर्ण;

/* TODO: Check अगर the actual desc macros can be used instead */
#घोषणा HAL_TX_STATUS_FLAGS_FIRST_MSDU		BIT(0)
#घोषणा HAL_TX_STATUS_FLAGS_LAST_MSDU		BIT(1)
#घोषणा HAL_TX_STATUS_FLAGS_MSDU_IN_AMSDU	BIT(2)
#घोषणा HAL_TX_STATUS_FLAGS_RATE_STATS_VALID	BIT(3)
#घोषणा HAL_TX_STATUS_FLAGS_RATE_LDPC		BIT(4)
#घोषणा HAL_TX_STATUS_FLAGS_RATE_STBC		BIT(5)
#घोषणा HAL_TX_STATUS_FLAGS_OFDMA		BIT(6)

#घोषणा HAL_TX_STATUS_DESC_LEN		माप(काष्ठा hal_wbm_release_ring)

/* Tx status parsed from srng desc */
काष्ठा hal_tx_status अणु
	क्रमागत hal_wbm_rel_src_module buf_rel_source;
	क्रमागत hal_wbm_tqm_rel_reason status;
	u8 ack_rssi;
	u32 flags; /* %HAL_TX_STATUS_FLAGS_ */
	u32 ppdu_id;
	u8 try_cnt;
	u8 tid;
	u16 peer_id;
	u32 rate_stats;
पूर्ण;

व्योम ath11k_hal_tx_cmd_desc_setup(काष्ठा ath11k_base *ab, व्योम *cmd,
				  काष्ठा hal_tx_info *ti);
व्योम ath11k_hal_tx_set_dscp_tid_map(काष्ठा ath11k_base *ab, पूर्णांक id);
पूर्णांक ath11k_hal_reo_cmd_send(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
			    क्रमागत hal_reo_cmd_type type,
			    काष्ठा ath11k_hal_reo_cmd *cmd);
व्योम ath11k_hal_tx_init_data_ring(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng *srng);
#पूर्ण_अगर
