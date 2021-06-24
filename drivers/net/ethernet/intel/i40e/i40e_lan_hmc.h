<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_LAN_HMC_H_
#घोषणा _I40E_LAN_HMC_H_

/* क्रमward-declare the HW काष्ठा क्रम the compiler */
काष्ठा i40e_hw;

/* HMC element context inक्रमmation */

/* Rx queue context data
 *
 * The sizes of the variables may be larger than needed due to crossing byte
 * boundaries. If we करो not have the width of the variable set to the correct
 * size then we could end up shअगरting bits off the top of the variable when the
 * variable is at the top of a byte and crosses over पूर्णांकo the next byte.
 */
काष्ठा i40e_hmc_obj_rxq अणु
	u16 head;
	u16 cpuid; /* bigger than needed, see above क्रम reason */
	u64 base;
	u16 qlen;
#घोषणा I40E_RXQ_CTX_DBUFF_SHIFT 7
	u16 dbuff; /* bigger than needed, see above क्रम reason */
#घोषणा I40E_RXQ_CTX_HBUFF_SHIFT 6
	u16 hbuff; /* bigger than needed, see above क्रम reason */
	u8  dtype;
	u8  dsize;
	u8  crcstrip;
	u8  fc_ena;
	u8  l2tsel;
	u8  hsplit_0;
	u8  hsplit_1;
	u8  showiv;
	u32 rxmax; /* bigger than needed, see above क्रम reason */
	u8  tphrdesc_ena;
	u8  tphwdesc_ena;
	u8  tphdata_ena;
	u8  tphhead_ena;
	u16 lrxqthresh; /* bigger than needed, see above क्रम reason */
	u8  prefena;	/* NOTE: normally must be set to 1 at init */
पूर्ण;

/* Tx queue context data
*
* The sizes of the variables may be larger than needed due to crossing byte
* boundaries. If we करो not have the width of the variable set to the correct
* size then we could end up shअगरting bits off the top of the variable when the
* variable is at the top of a byte and crosses over पूर्णांकo the next byte.
*/
काष्ठा i40e_hmc_obj_txq अणु
	u16 head;
	u8  new_context;
	u64 base;
	u8  fc_ena;
	u8  बारync_ena;
	u8  fd_ena;
	u8  alt_vlan_ena;
	u16 thead_wb;
	u8  cpuid;
	u8  head_wb_ena;
	u16 qlen;
	u8  tphrdesc_ena;
	u8  tphrpacket_ena;
	u8  tphwdesc_ena;
	u64 head_wb_addr;
	u32 crc;
	u16 rdylist;
	u8  rdylist_act;
पूर्ण;

/* क्रम hsplit_0 field of Rx HMC context */
क्रमागत i40e_hmc_obj_rx_hsplit_0 अणु
	I40E_HMC_OBJ_RX_HSPLIT_0_NO_SPLIT      = 0,
	I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_L2      = 1,
	I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_IP      = 2,
	I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_TCP_UDP = 4,
	I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_SCTP    = 8,
पूर्ण;

/* fcoe_cntx and fcoe_filt are क्रम debugging purpose only */
काष्ठा i40e_hmc_obj_fcoe_cntx अणु
	u32 rsv[32];
पूर्ण;

काष्ठा i40e_hmc_obj_fcoe_filt अणु
	u32 rsv[8];
पूर्ण;

/* Context sizes क्रम LAN objects */
क्रमागत i40e_hmc_lan_object_size अणु
	I40E_HMC_LAN_OBJ_SZ_8   = 0x3,
	I40E_HMC_LAN_OBJ_SZ_16  = 0x4,
	I40E_HMC_LAN_OBJ_SZ_32  = 0x5,
	I40E_HMC_LAN_OBJ_SZ_64  = 0x6,
	I40E_HMC_LAN_OBJ_SZ_128 = 0x7,
	I40E_HMC_LAN_OBJ_SZ_256 = 0x8,
	I40E_HMC_LAN_OBJ_SZ_512 = 0x9,
पूर्ण;

#घोषणा I40E_HMC_L2OBJ_BASE_ALIGNMENT 512
#घोषणा I40E_HMC_OBJ_SIZE_TXQ         128
#घोषणा I40E_HMC_OBJ_SIZE_RXQ         32
#घोषणा I40E_HMC_OBJ_SIZE_FCOE_CNTX   64
#घोषणा I40E_HMC_OBJ_SIZE_FCOE_FILT   64

क्रमागत i40e_hmc_lan_rsrc_type अणु
	I40E_HMC_LAN_FULL  = 0,
	I40E_HMC_LAN_TX    = 1,
	I40E_HMC_LAN_RX    = 2,
	I40E_HMC_FCOE_CTX  = 3,
	I40E_HMC_FCOE_FILT = 4,
	I40E_HMC_LAN_MAX   = 5
पूर्ण;

क्रमागत i40e_hmc_model अणु
	I40E_HMC_MODEL_सूचीECT_PREFERRED = 0,
	I40E_HMC_MODEL_सूचीECT_ONLY      = 1,
	I40E_HMC_MODEL_PAGED_ONLY       = 2,
	I40E_HMC_MODEL_UNKNOWN,
पूर्ण;

काष्ठा i40e_hmc_lan_create_obj_info अणु
	काष्ठा i40e_hmc_info *hmc_info;
	u32 rsrc_type;
	u32 start_idx;
	u32 count;
	क्रमागत i40e_sd_entry_type entry_type;
	u64 direct_mode_sz;
पूर्ण;

काष्ठा i40e_hmc_lan_delete_obj_info अणु
	काष्ठा i40e_hmc_info *hmc_info;
	u32 rsrc_type;
	u32 start_idx;
	u32 count;
पूर्ण;

i40e_status i40e_init_lan_hmc(काष्ठा i40e_hw *hw, u32 txq_num,
					u32 rxq_num, u32 fcoe_cntx_num,
					u32 fcoe_filt_num);
i40e_status i40e_configure_lan_hmc(काष्ठा i40e_hw *hw,
					     क्रमागत i40e_hmc_model model);
i40e_status i40e_shutकरोwn_lan_hmc(काष्ठा i40e_hw *hw);

i40e_status i40e_clear_lan_tx_queue_context(काष्ठा i40e_hw *hw,
						      u16 queue);
i40e_status i40e_set_lan_tx_queue_context(काष्ठा i40e_hw *hw,
						    u16 queue,
						    काष्ठा i40e_hmc_obj_txq *s);
i40e_status i40e_clear_lan_rx_queue_context(काष्ठा i40e_hw *hw,
						      u16 queue);
i40e_status i40e_set_lan_rx_queue_context(काष्ठा i40e_hw *hw,
						    u16 queue,
						    काष्ठा i40e_hmc_obj_rxq *s);

#पूर्ण_अगर /* _I40E_LAN_HMC_H_ */
