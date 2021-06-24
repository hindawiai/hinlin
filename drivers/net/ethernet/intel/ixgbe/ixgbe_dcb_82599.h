<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _DCB_82599_CONFIG_H_
#घोषणा _DCB_82599_CONFIG_H_

/* DCB रेजिस्टर definitions */
#घोषणा IXGBE_RTTDCS_TDPAC      0x00000001 /* 0 Round Robin,
					    * 1 WSP - Weighted Strict Priority
					    */
#घोषणा IXGBE_RTTDCS_VMPAC      0x00000002 /* 0 Round Robin,
					    * 1 WRR - Weighted Round Robin
					    */
#घोषणा IXGBE_RTTDCS_TDRM       0x00000010 /* Transmit Recycle Mode */
#घोषणा IXGBE_RTTDCS_ARBDIS     0x00000040 /* DCB arbiter disable */
#घोषणा IXGBE_RTTDCS_BDPM       0x00400000 /* Bypass Data Pipe - must clear! */
#घोषणा IXGBE_RTTDCS_BPBFSM     0x00800000 /* Bypass PB Free Space - must
					     * clear!
					     */
#घोषणा IXGBE_RTTDCS_SPEED_CHG  0x80000000 /* Link speed change */

/* Receive UP2TC mapping */
#घोषणा IXGBE_RTRUP2TC_UP_SHIFT 3
#घोषणा IXGBE_RTRUP2TC_UP_MASK	7
/* Transmit UP2TC mapping */
#घोषणा IXGBE_RTTUP2TC_UP_SHIFT 3

#घोषणा IXGBE_RTRPT4C_MCL_SHIFT 12 /* Offset to Max Credit Limit setting */
#घोषणा IXGBE_RTRPT4C_BWG_SHIFT 9  /* Offset to BWG index */
#घोषणा IXGBE_RTRPT4C_GSP       0x40000000 /* GSP enable bit */
#घोषणा IXGBE_RTRPT4C_LSP       0x80000000 /* LSP enable bit */

#घोषणा IXGBE_RDRXCTL_MPBEN     0x00000010 /* DMA config क्रम multiple packet
					    * buffers enable
					    */
#घोषणा IXGBE_RDRXCTL_MCEN      0x00000040 /* DMA config क्रम multiple cores
					    * (RSS) enable
					    */

/* RTRPCS Bit Masks */
#घोषणा IXGBE_RTRPCS_RRM        0x00000002 /* Receive Recycle Mode enable */
/* Receive Arbitration Control: 0 Round Robin, 1 DFP */
#घोषणा IXGBE_RTRPCS_RAC        0x00000004
#घोषणा IXGBE_RTRPCS_ARBDIS     0x00000040 /* Arbitration disable bit */

/* RTTDT2C Bit Masks */
#घोषणा IXGBE_RTTDT2C_MCL_SHIFT 12
#घोषणा IXGBE_RTTDT2C_BWG_SHIFT 9
#घोषणा IXGBE_RTTDT2C_GSP       0x40000000
#घोषणा IXGBE_RTTDT2C_LSP       0x80000000

#घोषणा IXGBE_RTTPT2C_MCL_SHIFT 12
#घोषणा IXGBE_RTTPT2C_BWG_SHIFT 9
#घोषणा IXGBE_RTTPT2C_GSP       0x40000000
#घोषणा IXGBE_RTTPT2C_LSP       0x80000000

/* RTTPCS Bit Masks */
#घोषणा IXGBE_RTTPCS_TPPAC      0x00000020 /* 0 Round Robin,
					    * 1 SP - Strict Priority
					    */
#घोषणा IXGBE_RTTPCS_ARBDIS     0x00000040 /* Arbiter disable */
#घोषणा IXGBE_RTTPCS_TPRM       0x00000100 /* Transmit Recycle Mode enable */
#घोषणा IXGBE_RTTPCS_ARBD_SHIFT 22
#घोषणा IXGBE_RTTPCS_ARBD_DCB   0x4        /* Arbitration delay in DCB mode */

/* SECTXMINIFG DCB */
#घोषणा IXGBE_SECTX_DCB		0x00001F00 /* DCB TX Buffer IFG */


/* DCB hardware-specअगरic driver APIs */

/* DCB PFC functions */
s32 ixgbe_dcb_config_pfc_82599(काष्ठा ixgbe_hw *hw, u8 pfc_en, u8 *prio_tc);

/* DCB hw initialization */
s32 ixgbe_dcb_config_rx_arbiter_82599(काष्ठा ixgbe_hw *hw,
					u16 *refill,
					u16 *max,
					u8 *bwg_id,
					u8 *prio_type,
					u8 *prio_tc);

s32 ixgbe_dcb_config_tx_desc_arbiter_82599(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type);

s32 ixgbe_dcb_config_tx_data_arbiter_82599(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type,
						u8 *prio_tc);

s32 ixgbe_dcb_hw_config_82599(काष्ठा ixgbe_hw *hw, u8 pfc_en, u16 *refill,
			      u16 *max, u8 *bwg_id, u8 *prio_type,
			      u8 *prio_tc);

#पूर्ण_अगर /* _DCB_82599_CONFIG_H */
