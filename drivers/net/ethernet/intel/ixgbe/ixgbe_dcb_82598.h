<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _DCB_82598_CONFIG_H_
#घोषणा _DCB_82598_CONFIG_H_

/* DCB रेजिस्टर definitions */

#घोषणा IXGBE_DPMCS_MTSOS_SHIFT 16
#घोषणा IXGBE_DPMCS_TDPAC       0x00000001 /* 0 Round Robin, 1 DFP - Deficit Fixed Priority */
#घोषणा IXGBE_DPMCS_TRM         0x00000010 /* Transmit Recycle Mode */
#घोषणा IXGBE_DPMCS_ARBDIS      0x00000040 /* DCB arbiter disable */
#घोषणा IXGBE_DPMCS_TSOEF       0x00080000 /* TSO Expand Factor: 0=x4, 1=x2 */

#घोषणा IXGBE_RUPPBMR_MQA       0x80000000 /* Enable UP to queue mapping */

#घोषणा IXGBE_RT2CR_MCL_SHIFT   12 /* Offset to Max Credit Limit setting */
#घोषणा IXGBE_RT2CR_LSP         0x80000000 /* LSP enable bit */

#घोषणा IXGBE_RDRXCTL_MPBEN     0x00000010 /* DMA config क्रम multiple packet buffers enable */
#घोषणा IXGBE_RDRXCTL_MCEN      0x00000040 /* DMA config क्रम multiple cores (RSS) enable */

#घोषणा IXGBE_TDTQ2TCCR_MCL_SHIFT   12
#घोषणा IXGBE_TDTQ2TCCR_BWG_SHIFT   9
#घोषणा IXGBE_TDTQ2TCCR_GSP     0x40000000
#घोषणा IXGBE_TDTQ2TCCR_LSP     0x80000000

#घोषणा IXGBE_TDPT2TCCR_MCL_SHIFT   12
#घोषणा IXGBE_TDPT2TCCR_BWG_SHIFT   9
#घोषणा IXGBE_TDPT2TCCR_GSP     0x40000000
#घोषणा IXGBE_TDPT2TCCR_LSP     0x80000000

#घोषणा IXGBE_PDPMCS_TPPAC      0x00000020 /* 0 Round Robin, 1 क्रम DFP - Deficit Fixed Priority */
#घोषणा IXGBE_PDPMCS_ARBDIS     0x00000040 /* Arbiter disable */
#घोषणा IXGBE_PDPMCS_TRM        0x00000100 /* Transmit Recycle Mode enable */

#घोषणा IXGBE_DTXCTL_ENDBUBD    0x00000004 /* Enable DBU buffer भागision */

#घोषणा IXGBE_TXPBSIZE_40KB     0x0000A000 /* 40KB Packet Buffer */
#घोषणा IXGBE_RXPBSIZE_48KB     0x0000C000 /* 48KB Packet Buffer */
#घोषणा IXGBE_RXPBSIZE_64KB     0x00010000 /* 64KB Packet Buffer */
#घोषणा IXGBE_RXPBSIZE_80KB     0x00014000 /* 80KB Packet Buffer */

#घोषणा IXGBE_RDRXCTL_RDMTS_1_2 0x00000000

/* DCB hardware-specअगरic driver APIs */

/* DCB PFC functions */
s32 ixgbe_dcb_config_pfc_82598(काष्ठा ixgbe_hw *, u8 pfc_en);

/* DCB hw initialization */
s32 ixgbe_dcb_config_rx_arbiter_82598(काष्ठा ixgbe_hw *hw,
					u16 *refill,
					u16 *max,
					u8 *prio_type);

s32 ixgbe_dcb_config_tx_desc_arbiter_82598(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type);

s32 ixgbe_dcb_config_tx_data_arbiter_82598(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type);

s32 ixgbe_dcb_hw_config_82598(काष्ठा ixgbe_hw *hw, u8 pfc_en, u16 *refill,
			      u16 *max, u8 *bwg_id, u8 *prio_type);

#पूर्ण_अगर /* _DCB_82598_CONFIG_H */
