<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_INT_H
#घोषणा _QED_INT_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश "qed.h"

/* Fields of IGU PF CONFIGURATION REGISTER */
#घोषणा IGU_PF_CONF_FUNC_EN       (0x1 << 0)    /* function enable        */
#घोषणा IGU_PF_CONF_MSI_MSIX_EN   (0x1 << 1)    /* MSI/MSIX enable        */
#घोषणा IGU_PF_CONF_INT_LINE_EN   (0x1 << 2)    /* INT enable             */
#घोषणा IGU_PF_CONF_ATTN_BIT_EN   (0x1 << 3)    /* attention enable       */
#घोषणा IGU_PF_CONF_SINGLE_ISR_EN (0x1 << 4)    /* single ISR mode enable */
#घोषणा IGU_PF_CONF_SIMD_MODE     (0x1 << 5)    /* simd all ones mode     */
/* Fields of IGU VF CONFIGURATION REGISTER */
#घोषणा IGU_VF_CONF_FUNC_EN        (0x1 << 0)	/* function enable        */
#घोषणा IGU_VF_CONF_MSI_MSIX_EN    (0x1 << 1)	/* MSI/MSIX enable        */
#घोषणा IGU_VF_CONF_SINGLE_ISR_EN  (0x1 << 4)	/* single ISR mode enable */
#घोषणा IGU_VF_CONF_PARENT_MASK    (0xF)	/* Parent PF              */
#घोषणा IGU_VF_CONF_PARENT_SHIFT   5		/* Parent PF              */

/* Igu control commands
 */
क्रमागत igu_ctrl_cmd अणु
	IGU_CTRL_CMD_TYPE_RD,
	IGU_CTRL_CMD_TYPE_WR,
	MAX_IGU_CTRL_CMD
पूर्ण;

/* Control रेजिस्टर क्रम the IGU command रेजिस्टर
 */
काष्ठा igu_ctrl_reg अणु
	u32 ctrl_data;
#घोषणा IGU_CTRL_REG_FID_MASK           0xFFFF  /* Opaque_FID	 */
#घोषणा IGU_CTRL_REG_FID_SHIFT          0
#घोषणा IGU_CTRL_REG_PXP_ADDR_MASK      0xFFF   /* Command address */
#घोषणा IGU_CTRL_REG_PXP_ADDR_SHIFT     16
#घोषणा IGU_CTRL_REG_RESERVED_MASK      0x1
#घोषणा IGU_CTRL_REG_RESERVED_SHIFT     28
#घोषणा IGU_CTRL_REG_TYPE_MASK          0x1 /* use क्रमागत igu_ctrl_cmd */
#घोषणा IGU_CTRL_REG_TYPE_SHIFT         31
पूर्ण;

क्रमागत qed_coalescing_fsm अणु
	QED_COAL_RX_STATE_MACHINE,
	QED_COAL_TX_STATE_MACHINE
पूर्ण;

/**
 * @brief qed_पूर्णांक_igu_enable_पूर्णांक - enable device पूर्णांकerrupts
 *
 * @param p_hwfn
 * @param p_ptt
 * @param पूर्णांक_mode - पूर्णांकerrupt mode to use
 */
व्योम qed_पूर्णांक_igu_enable_पूर्णांक(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    क्रमागत qed_पूर्णांक_mode पूर्णांक_mode);

/**
 * @brief qed_पूर्णांक_igu_disable_पूर्णांक - disable device पूर्णांकerrupts
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_पूर्णांक_igu_disable_पूर्णांक(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_पूर्णांक_igu_पढ़ो_sisr_reg - Reads the single isr multiple dpc
 *        रेजिस्टर from igu.
 *
 * @param p_hwfn
 *
 * @वापस u64
 */
u64 qed_पूर्णांक_igu_पढ़ो_sisr_reg(काष्ठा qed_hwfn *p_hwfn);

#घोषणा QED_SP_SB_ID 0xffff
/**
 * @brief qed_पूर्णांक_sb_init - Initializes the sb_info काष्ठाure.
 *
 * once the काष्ठाure is initialized it can be passed to sb related functions.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param sb_info	poपूर्णांकs to an uninitialized (but
 *			allocated) sb_info काष्ठाure
 * @param sb_virt_addr
 * @param sb_phy_addr
 * @param sb_id	the sb_id to be used (zero based in driver)
 *			should use QED_SP_SB_ID क्रम SP Status block
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_sb_init(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_sb_info *sb_info,
		    व्योम *sb_virt_addr,
		    dma_addr_t sb_phy_addr,
		    u16 sb_id);
/**
 * @brief qed_पूर्णांक_sb_setup - Setup the sb.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param sb_info	initialized sb_info काष्ठाure
 */
व्योम qed_पूर्णांक_sb_setup(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      काष्ठा qed_sb_info *sb_info);

/**
 * @brief qed_पूर्णांक_sb_release - releases the sb_info काष्ठाure.
 *
 * once the काष्ठाure is released, it's memory can be मुक्तd
 *
 * @param p_hwfn
 * @param sb_info	poपूर्णांकs to an allocated sb_info काष्ठाure
 * @param sb_id		the sb_id to be used (zero based in driver)
 *			should never be equal to QED_SP_SB_ID
 *			(SP Status block)
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_sb_release(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_sb_info *sb_info,
		       u16 sb_id);

/**
 * @brief qed_पूर्णांक_sp_dpc - To be called when an पूर्णांकerrupt is received on the
 *        शेष status block.
 *
 * @param p_hwfn - poपूर्णांकer to hwfn
 *
 */
व्योम qed_पूर्णांक_sp_dpc(काष्ठा tasklet_काष्ठा *t);

/**
 * @brief qed_पूर्णांक_get_num_sbs - get the number of status
 *        blocks configured क्रम this funciton in the igu.
 *
 * @param p_hwfn
 * @param p_sb_cnt_info
 *
 * @वापस पूर्णांक - number of status blocks configured
 */
व्योम qed_पूर्णांक_get_num_sbs(काष्ठा qed_hwfn	*p_hwfn,
			 काष्ठा qed_sb_cnt_info *p_sb_cnt_info);

/**
 * @brief qed_पूर्णांक_disable_post_isr_release - perक्रमms the cleanup post ISR
 *        release. The API need to be called after releasing all slowpath IRQs
 *        of the device.
 *
 * @param cdev
 *
 */
व्योम qed_पूर्णांक_disable_post_isr_release(काष्ठा qed_dev *cdev);

/**
 * @brief qed_पूर्णांक_attn_clr_enable - sets whether the general behavior is
 *        preventing attentions from being reनिश्चितed, or following the
 *        attributes of the specअगरic attention.
 *
 * @param cdev
 * @param clr_enable
 *
 */
व्योम qed_पूर्णांक_attn_clr_enable(काष्ठा qed_dev *cdev, bool clr_enable);

/**
 * @brief - Doorbell Recovery handler.
 *          Run करोorbell recovery in हाल of PF overflow (and flush DORQ अगर
 *          needed).
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_db_rec_handler(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

#घोषणा QED_CAU_DEF_RX_TIMER_RES 0
#घोषणा QED_CAU_DEF_TX_TIMER_RES 0

#घोषणा QED_SB_ATT_IDX  0x0001
#घोषणा QED_SB_EVENT_MASK       0x0003

#घोषणा SB_ALIGNED_SIZE(p_hwfn)	\
	ALIGNED_TYPE_SIZE(काष्ठा status_block_e4, p_hwfn)

#घोषणा QED_SB_INVALID_IDX      0xffff

काष्ठा qed_igu_block अणु
	u8 status;
#घोषणा QED_IGU_STATUS_FREE     0x01
#घोषणा QED_IGU_STATUS_VALID    0x02
#घोषणा QED_IGU_STATUS_PF       0x04
#घोषणा QED_IGU_STATUS_DSB      0x08

	u8 vector_number;
	u8 function_id;
	u8 is_pf;

	/* Index inside IGU [meant क्रम back reference] */
	u16 igu_sb_id;

	काष्ठा qed_sb_info *sb_info;
पूर्ण;

काष्ठा qed_igu_info अणु
	काष्ठा qed_igu_block entry[MAX_TOT_SB_PER_PATH];
	u16 igu_dsb_id;

	काष्ठा qed_sb_cnt_info usage;

	bool b_allow_pf_vf_change;
पूर्ण;

/**
 * @brief - Make sure the IGU CAM reflects the resources provided by MFW
 *
 * @param p_hwfn
 * @param p_ptt
 */
पूर्णांक qed_पूर्णांक_igu_reset_cam(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief Translate the weakly-defined client sb-id पूर्णांकo an IGU sb-id
 *
 * @param p_hwfn
 * @param sb_id - user provided sb_id
 *
 * @वापस an index inside IGU CAM where the SB resides
 */
u16 qed_get_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 sb_id);

/**
 * @brief वापस a poपूर्णांकer to an unused valid SB
 *
 * @param p_hwfn
 * @param b_is_pf - true अगरf we want a SB beदीर्घing to a PF
 *
 * @वापस poपूर्णांक to an igu_block, शून्य अगर none is available
 */
काष्ठा qed_igu_block *qed_get_igu_मुक्त_sb(काष्ठा qed_hwfn *p_hwfn,
					  bool b_is_pf);

व्योम qed_पूर्णांक_igu_init_pure_rt(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      bool b_set,
			      bool b_slowpath);

व्योम qed_पूर्णांक_igu_init_rt(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_पूर्णांक_igu_पढ़ो_cam - Reads the IGU CAM.
 *	This function needs to be called during hardware
 *	prepare. It पढ़ोs the info from igu cam to know which
 *	status block is the शेष / base status block etc.
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_igu_पढ़ो_cam(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt);

प्रकार पूर्णांक (*qed_पूर्णांक_comp_cb_t)(काष्ठा qed_hwfn *p_hwfn,
				 व्योम *cookie);
/**
 * @brief qed_पूर्णांक_रेजिस्टर_cb - Register callback func क्रम
 *      slowhwfn statusblock.
 *
 *	Every protocol that uses the slowhwfn status block
 *	should रेजिस्टर a callback function that will be called
 *	once there is an update of the sp status block.
 *
 * @param p_hwfn
 * @param comp_cb - function to be called when there is an
 *                  पूर्णांकerrupt on the sp sb
 *
 * @param cookie  - passed to the callback function
 * @param sb_idx  - OUT parameter which gives the chosen index
 *                  क्रम this protocol.
 * @param p_fw_cons  - poपूर्णांकer to the actual address of the
 *                     consumer क्रम this protocol.
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_रेजिस्टर_cb(काष्ठा qed_hwfn *p_hwfn,
			qed_पूर्णांक_comp_cb_t comp_cb,
			व्योम *cookie,
			u8 *sb_idx,
			__le16 **p_fw_cons);

/**
 * @brief qed_पूर्णांक_unरेजिस्टर_cb - Unरेजिस्टरs callback
 *      function from sp sb.
 *      Partner of qed_पूर्णांक_रेजिस्टर_cb -> should be called
 *      when no दीर्घer required.
 *
 * @param p_hwfn
 * @param pi
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_unरेजिस्टर_cb(काष्ठा qed_hwfn *p_hwfn,
			  u8 pi);

/**
 * @brief qed_पूर्णांक_get_sp_sb_id - Get the slowhwfn sb id.
 *
 * @param p_hwfn
 *
 * @वापस u16
 */
u16 qed_पूर्णांक_get_sp_sb_id(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief Status block cleanup. Should be called क्रम each status
 *        block that will be used -> both PF / VF
 *
 * @param p_hwfn
 * @param p_ptt
 * @param igu_sb_id	- igu status block id
 * @param opaque	- opaque fid of the sb owner.
 * @param b_set		- set(1) / clear(0)
 */
व्योम qed_पूर्णांक_igu_init_pure_rt_single(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     u16 igu_sb_id,
				     u16 opaque,
				     bool b_set);

/**
 * @brief qed_पूर्णांक_cau_conf - configure cau क्रम a given status
 *        block
 *
 * @param p_hwfn
 * @param ptt
 * @param sb_phys
 * @param igu_sb_id
 * @param vf_number
 * @param vf_valid
 */
व्योम qed_पूर्णांक_cau_conf_sb(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 dma_addr_t sb_phys,
			 u16 igu_sb_id,
			 u16 vf_number,
			 u8 vf_valid);

/**
 * @brief qed_पूर्णांक_alloc
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_alloc(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_पूर्णांक_मुक्त
 *
 * @param p_hwfn
 */
व्योम qed_पूर्णांक_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_पूर्णांक_setup
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_पूर्णांक_setup(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt);

/**
 * @brief - Enable Interrupt & Attention क्रम hw function
 *
 * @param p_hwfn
 * @param p_ptt
 * @param पूर्णांक_mode
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_पूर्णांक_igu_enable(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		       क्रमागत qed_पूर्णांक_mode पूर्णांक_mode);

/**
 * @brief - Initialize CAU status block entry
 *
 * @param p_hwfn
 * @param p_sb_entry
 * @param pf_id
 * @param vf_number
 * @param vf_valid
 */
व्योम qed_init_cau_sb_entry(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा cau_sb_entry *p_sb_entry,
			   u8 pf_id,
			   u16 vf_number,
			   u8 vf_valid);

पूर्णांक qed_पूर्णांक_set_समयr_res(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			  u8 समयr_res, u16 sb_id, bool tx);

#घोषणा QED_MAPPING_MEMORY_SIZE(dev)	(NUM_OF_SBS(dev))

पूर्णांक qed_pglueb_rbc_attn_handler(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
				bool hw_init);

#पूर्ण_अगर
