<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_DEV_API_H
#घोषणा _QED_DEV_API_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qed_int.h"

/**
 * @brief qed_init_dp - initialize the debug level
 *
 * @param cdev
 * @param dp_module
 * @param dp_level
 */
व्योम qed_init_dp(काष्ठा qed_dev *cdev,
		 u32 dp_module,
		 u8 dp_level);

/**
 * @brief qed_init_काष्ठा - initialize the device काष्ठाure to
 *        its शेषs
 *
 * @param cdev
 */
व्योम qed_init_काष्ठा(काष्ठा qed_dev *cdev);

/**
 * @brief qed_resc_मुक्त -
 *
 * @param cdev
 */
व्योम qed_resc_मुक्त(काष्ठा qed_dev *cdev);

/**
 * @brief qed_resc_alloc -
 *
 * @param cdev
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_resc_alloc(काष्ठा qed_dev *cdev);

/**
 * @brief qed_resc_setup -
 *
 * @param cdev
 */
व्योम qed_resc_setup(काष्ठा qed_dev *cdev);

क्रमागत qed_override_क्रमce_load अणु
	QED_OVERRIDE_FORCE_LOAD_NONE,
	QED_OVERRIDE_FORCE_LOAD_ALWAYS,
	QED_OVERRIDE_FORCE_LOAD_NEVER,
पूर्ण;

काष्ठा qed_drv_load_params अणु
	/* Indicates whether the driver is running over a crash kernel.
	 * As part of the load request, this will be used क्रम providing the
	 * driver role to the MFW.
	 * In हाल of a crash kernel over PDA - this should be set to false.
	 */
	bool is_crash_kernel;

	/* The समयout value that the MFW should use when locking the engine क्रम
	 * the driver load process.
	 * A value of '0' means the default value, and '255' means no समयout.
	 */
	u8 mfw_समयout_val;
#घोषणा QED_LOAD_REQ_LOCK_TO_DEFAULT    0
#घोषणा QED_LOAD_REQ_LOCK_TO_NONE       255

	/* Aव्योम engine reset when first PF loads on it */
	bool aव्योम_eng_reset;

	/* Allow overriding the शेष क्रमce load behavior */
	क्रमागत qed_override_क्रमce_load override_क्रमce_load;
पूर्ण;

काष्ठा qed_hw_init_params अणु
	/* Tunneling parameters */
	काष्ठा qed_tunnel_info *p_tunn;

	bool b_hw_start;

	/* Interrupt mode [msix, पूर्णांकa, etc.] to use */
	क्रमागत qed_पूर्णांक_mode पूर्णांक_mode;

	/* NPAR tx चयनing to be used क्रम vports क्रम tx-चयनing */
	bool allow_npar_tx_चयन;

	/* Binary fw data poपूर्णांकer in binary fw file */
	स्थिर u8 *bin_fw_data;

	/* Driver load parameters */
	काष्ठा qed_drv_load_params *p_drv_load_params;
पूर्ण;

/**
 * @brief qed_hw_init -
 *
 * @param cdev
 * @param p_params
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_hw_init(काष्ठा qed_dev *cdev, काष्ठा qed_hw_init_params *p_params);

/**
 * @brief qed_hw_समयrs_stop_all - stop the समयrs HW block
 *
 * @param cdev
 *
 * @वापस व्योम
 */
व्योम qed_hw_समयrs_stop_all(काष्ठा qed_dev *cdev);

/**
 * @brief qed_hw_stop -
 *
 * @param cdev
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_hw_stop(काष्ठा qed_dev *cdev);

/**
 * @brief qed_hw_stop_fastpath -should be called inहाल
 *		slowpath is still required क्रम the device,
 *		but fastpath is not.
 *
 * @param cdev
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_hw_stop_fastpath(काष्ठा qed_dev *cdev);

/**
 * @brief qed_hw_start_fastpath -restart fastpath traffic,
 *		only अगर hw_stop_fastpath was called
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_hw_start_fastpath(काष्ठा qed_hwfn *p_hwfn);


/**
 * @brief qed_hw_prepare -
 *
 * @param cdev
 * @param personality - personality to initialize
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_hw_prepare(काष्ठा qed_dev *cdev,
		   पूर्णांक personality);

/**
 * @brief qed_hw_हटाओ -
 *
 * @param cdev
 */
व्योम qed_hw_हटाओ(काष्ठा qed_dev *cdev);

/**
 * @brief qed_ptt_acquire - Allocate a PTT winकरोw
 *
 * Should be called at the entry poपूर्णांक to the driver (at the beginning of an
 * exported function)
 *
 * @param p_hwfn
 *
 * @वापस काष्ठा qed_ptt
 */
काष्ठा qed_ptt *qed_ptt_acquire(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ptt_release - Release PTT Winकरोw
 *
 * Should be called at the end of a flow - at the end of the function that
 * acquired the PTT.
 *
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_ptt_release(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt);
व्योम qed_reset_vport_stats(काष्ठा qed_dev *cdev);

क्रमागत qed_dmae_address_type_t अणु
	QED_DMAE_ADDRESS_HOST_VIRT,
	QED_DMAE_ADDRESS_HOST_PHYS,
	QED_DMAE_ADDRESS_GRC
पूर्ण;

/**
 * @brief qed_dmae_host2grc - copy data from source addr to
 * dmae रेजिस्टरs using the given ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param source_addr
 * @param grc_addr (dmae_data_offset)
 * @param size_in_dwords
 * @param p_params (शेष parameters will be used in हाल of शून्य)
 */
पूर्णांक
qed_dmae_host2grc(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt,
		  u64 source_addr,
		  u32 grc_addr,
		  u32 size_in_dwords,
		  काष्ठा qed_dmae_params *p_params);

 /**
 * @brief qed_dmae_grc2host - Read data from dmae data offset
 * to source address using the given ptt
 *
 * @param p_ptt
 * @param grc_addr (dmae_data_offset)
 * @param dest_addr
 * @param size_in_dwords
 * @param p_params (शेष parameters will be used in हाल of शून्य)
 */
पूर्णांक qed_dmae_grc2host(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		      u32 grc_addr, dma_addr_t dest_addr, u32 size_in_dwords,
		      काष्ठा qed_dmae_params *p_params);

/**
 * @brief qed_dmae_host2host - copy data from to source address
 * to a destination adress (क्रम SRIOV) using the given ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param source_addr
 * @param dest_addr
 * @param size_in_dwords
 * @param p_params (शेष parameters will be used in हाल of शून्य)
 */
पूर्णांक qed_dmae_host2host(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       dma_addr_t source_addr,
		       dma_addr_t dest_addr,
		       u32 size_in_dwords, काष्ठा qed_dmae_params *p_params);

पूर्णांक qed_chain_alloc(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain,
		    काष्ठा qed_chain_init_params *params);
व्योम qed_chain_मुक्त(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain);

/**
 * @@brief qed_fw_l2_queue - Get असलolute L2 queue ID
 *
 *  @param p_hwfn
 *  @param src_id - relative to p_hwfn
 *  @param dst_id - असलolute per engine
 *
 *  @वापस पूर्णांक
 */
पूर्णांक qed_fw_l2_queue(काष्ठा qed_hwfn *p_hwfn,
		    u16 src_id,
		    u16 *dst_id);

/**
 * @@brief qed_fw_vport - Get असलolute vport ID
 *
 *  @param p_hwfn
 *  @param src_id - relative to p_hwfn
 *  @param dst_id - असलolute per engine
 *
 *  @वापस पूर्णांक
 */
पूर्णांक qed_fw_vport(काष्ठा qed_hwfn *p_hwfn,
		 u8 src_id,
		 u8 *dst_id);

/**
 * @@brief qed_fw_rss_eng - Get असलolute RSS engine ID
 *
 *  @param p_hwfn
 *  @param src_id - relative to p_hwfn
 *  @param dst_id - असलolute per engine
 *
 *  @वापस पूर्णांक
 */
पूर्णांक qed_fw_rss_eng(काष्ठा qed_hwfn *p_hwfn,
		   u8 src_id,
		   u8 *dst_id);

/**
 * @brief qed_llh_get_num_ppfid - Return the allocated number of LLH filter
 *	banks that are allocated to the PF.
 *
 * @param cdev
 *
 * @वापस u8 - Number of LLH filter banks
 */
u8 qed_llh_get_num_ppfid(काष्ठा qed_dev *cdev);

क्रमागत qed_eng अणु
	QED_ENG0,
	QED_ENG1,
	QED_BOTH_ENG,
पूर्ण;

/**
 * @brief qed_llh_set_ppfid_affinity - Set the engine affinity क्रम the given
 *	LLH filter bank.
 *
 * @param cdev
 * @param ppfid - relative within the allocated ppfids ('0' is the शेष one).
 * @param eng
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_llh_set_ppfid_affinity(काष्ठा qed_dev *cdev,
			       u8 ppfid, क्रमागत qed_eng eng);

/**
 * @brief qed_llh_set_roce_affinity - Set the RoCE engine affinity
 *
 * @param cdev
 * @param eng
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_llh_set_roce_affinity(काष्ठा qed_dev *cdev, क्रमागत qed_eng eng);

/**
 * @brief qed_llh_add_mac_filter - Add a LLH MAC filter पूर्णांकo the given filter
 *	bank.
 *
 * @param cdev
 * @param ppfid - relative within the allocated ppfids ('0' is the शेष one).
 * @param mac_addr - MAC to add
 */
पूर्णांक qed_llh_add_mac_filter(काष्ठा qed_dev *cdev,
			   u8 ppfid, u8 mac_addr[ETH_ALEN]);

/**
 * @brief qed_llh_हटाओ_mac_filter - Remove a LLH MAC filter from the given
 *	filter bank.
 *
 * @param p_ptt
 * @param p_filter - MAC to हटाओ
 */
व्योम qed_llh_हटाओ_mac_filter(काष्ठा qed_dev *cdev,
			       u8 ppfid, u8 mac_addr[ETH_ALEN]);

क्रमागत qed_llh_prot_filter_type_t अणु
	QED_LLH_FILTER_ETHERTYPE,
	QED_LLH_FILTER_TCP_SRC_PORT,
	QED_LLH_FILTER_TCP_DEST_PORT,
	QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT,
	QED_LLH_FILTER_UDP_SRC_PORT,
	QED_LLH_FILTER_UDP_DEST_PORT,
	QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT
पूर्ण;

/**
 * @brief qed_llh_add_protocol_filter - Add a LLH protocol filter पूर्णांकo the
 *	given filter bank.
 *
 * @param cdev
 * @param ppfid - relative within the allocated ppfids ('0' is the शेष one).
 * @param type - type of filters and comparing
 * @param source_port_or_eth_type - source port or ethertype to add
 * @param dest_port - destination port to add
 * @param type - type of filters and comparing
 */
पूर्णांक
qed_llh_add_protocol_filter(काष्ठा qed_dev *cdev,
			    u8 ppfid,
			    क्रमागत qed_llh_prot_filter_type_t type,
			    u16 source_port_or_eth_type, u16 dest_port);

/**
 * @brief qed_llh_हटाओ_protocol_filter - Remove a LLH protocol filter from
 *	the given filter bank.
 *
 * @param cdev
 * @param ppfid - relative within the allocated ppfids ('0' is the शेष one).
 * @param type - type of filters and comparing
 * @param source_port_or_eth_type - source port or ethertype to add
 * @param dest_port - destination port to add
 */
व्योम
qed_llh_हटाओ_protocol_filter(काष्ठा qed_dev *cdev,
			       u8 ppfid,
			       क्रमागत qed_llh_prot_filter_type_t type,
			       u16 source_port_or_eth_type, u16 dest_port);

/**
 * *@brief Cleanup of previous driver reमुख्यs prior to load
 *
 * @param p_hwfn
 * @param p_ptt
 * @param id - For PF, engine-relative. For VF, PF-relative.
 * @param is_vf - true अगरf cleanup is made क्रम a VF.
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_final_cleanup(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, u16 id, bool is_vf);

/**
 * @brief qed_get_queue_coalesce - Retrieve coalesce value क्रम a given queue.
 *
 * @param p_hwfn
 * @param p_coal - store coalesce value पढ़ो from the hardware.
 * @param p_handle
 *
 * @वापस पूर्णांक
 **/
पूर्णांक qed_get_queue_coalesce(काष्ठा qed_hwfn *p_hwfn, u16 *coal, व्योम *handle);

/**
 * @brief qed_set_queue_coalesce - Configure coalesce parameters क्रम Rx and
 *    Tx queue. The fact that we can configure coalescing to up to 511, but on
 *    varying accuracy [the bigger the value the less accurate] up to a mistake
 *    of 3usec क्रम the highest values.
 *    While the API allows setting coalescing per-qid, all queues sharing a SB
 *    should be in same range [i.e., either 0-0x7f, 0x80-0xff or 0x100-0x1ff]
 *    otherwise configuration would अवरोध.
 *
 *
 * @param rx_coal - Rx Coalesce value in micro seconds.
 * @param tx_coal - TX Coalesce value in micro seconds.
 * @param p_handle
 *
 * @वापस पूर्णांक
 **/
पूर्णांक
qed_set_queue_coalesce(u16 rx_coal, u16 tx_coal, व्योम *p_handle);

/**
 * @brief qed_pglueb_set_pfid_enable - Enable or disable PCI BUS MASTER
 *
 * @param p_hwfn
 * @param p_ptt
 * @param b_enable - true/false
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_pglueb_set_pfid_enable(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt, bool b_enable);

/**
 * @brief db_recovery_add - add करोorbell inक्रमmation to the करोorbell
 * recovery mechanism.
 *
 * @param cdev
 * @param db_addr - करोorbell address
 * @param db_data - address of where db_data is stored
 * @param db_width - करोorbell is 32b pr 64b
 * @param db_space - करोorbell recovery addresses are user or kernel space
 */
पूर्णांक qed_db_recovery_add(काष्ठा qed_dev *cdev,
			व्योम __iomem *db_addr,
			व्योम *db_data,
			क्रमागत qed_db_rec_width db_width,
			क्रमागत qed_db_rec_space db_space);

/**
 * @brief db_recovery_del - हटाओ करोorbell inक्रमmation from the करोorbell
 * recovery mechanism. db_data serves as key (db_addr is not unique).
 *
 * @param cdev
 * @param db_addr - करोorbell address
 * @param db_data - address where db_data is stored. Serves as key क्रम the
 *                  entry to delete.
 */
पूर्णांक qed_db_recovery_del(काष्ठा qed_dev *cdev,
			व्योम __iomem *db_addr, व्योम *db_data);


स्थिर अक्षर *qed_hw_get_resc_name(क्रमागत qed_resources res_id);
#पूर्ण_अगर
