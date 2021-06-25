<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_NIC_H
#घोषणा EFX_NIC_H

#समावेश "nic_common.h"
#समावेश "efx.h"

u32 efx_farch_fpga_ver(काष्ठा efx_nic *efx);

क्रमागत अणु
	PHY_TYPE_NONE = 0,
	PHY_TYPE_TXC43128 = 1,
	PHY_TYPE_88E1111 = 2,
	PHY_TYPE_SFX7101 = 3,
	PHY_TYPE_QT2022C2 = 4,
	PHY_TYPE_PM8358 = 6,
	PHY_TYPE_SFT9001A = 8,
	PHY_TYPE_QT2025C = 9,
	PHY_TYPE_SFT9001B = 10,
पूर्ण;

क्रमागत अणु
	SIENA_STAT_tx_bytes = GENERIC_STAT_COUNT,
	SIENA_STAT_tx_good_bytes,
	SIENA_STAT_tx_bad_bytes,
	SIENA_STAT_tx_packets,
	SIENA_STAT_tx_bad,
	SIENA_STAT_tx_छोड़ो,
	SIENA_STAT_tx_control,
	SIENA_STAT_tx_unicast,
	SIENA_STAT_tx_multicast,
	SIENA_STAT_tx_broadcast,
	SIENA_STAT_tx_lt64,
	SIENA_STAT_tx_64,
	SIENA_STAT_tx_65_to_127,
	SIENA_STAT_tx_128_to_255,
	SIENA_STAT_tx_256_to_511,
	SIENA_STAT_tx_512_to_1023,
	SIENA_STAT_tx_1024_to_15xx,
	SIENA_STAT_tx_15xx_to_jumbo,
	SIENA_STAT_tx_gtjumbo,
	SIENA_STAT_tx_collision,
	SIENA_STAT_tx_single_collision,
	SIENA_STAT_tx_multiple_collision,
	SIENA_STAT_tx_excessive_collision,
	SIENA_STAT_tx_deferred,
	SIENA_STAT_tx_late_collision,
	SIENA_STAT_tx_excessive_deferred,
	SIENA_STAT_tx_non_tcpudp,
	SIENA_STAT_tx_mac_src_error,
	SIENA_STAT_tx_ip_src_error,
	SIENA_STAT_rx_bytes,
	SIENA_STAT_rx_good_bytes,
	SIENA_STAT_rx_bad_bytes,
	SIENA_STAT_rx_packets,
	SIENA_STAT_rx_good,
	SIENA_STAT_rx_bad,
	SIENA_STAT_rx_छोड़ो,
	SIENA_STAT_rx_control,
	SIENA_STAT_rx_unicast,
	SIENA_STAT_rx_multicast,
	SIENA_STAT_rx_broadcast,
	SIENA_STAT_rx_lt64,
	SIENA_STAT_rx_64,
	SIENA_STAT_rx_65_to_127,
	SIENA_STAT_rx_128_to_255,
	SIENA_STAT_rx_256_to_511,
	SIENA_STAT_rx_512_to_1023,
	SIENA_STAT_rx_1024_to_15xx,
	SIENA_STAT_rx_15xx_to_jumbo,
	SIENA_STAT_rx_gtjumbo,
	SIENA_STAT_rx_bad_gtjumbo,
	SIENA_STAT_rx_overflow,
	SIENA_STAT_rx_false_carrier,
	SIENA_STAT_rx_symbol_error,
	SIENA_STAT_rx_align_error,
	SIENA_STAT_rx_length_error,
	SIENA_STAT_rx_पूर्णांकernal_error,
	SIENA_STAT_rx_nodesc_drop_cnt,
	SIENA_STAT_COUNT
पूर्ण;

/**
 * काष्ठा siena_nic_data - Siena NIC state
 * @efx: Poपूर्णांकer back to मुख्य पूर्णांकerface काष्ठाure
 * @wol_filter_id: Wake-on-LAN packet filter id
 * @stats: Hardware statistics
 * @vf: Array of &काष्ठा siena_vf objects
 * @vf_buftbl_base: The zeroth buffer table index used to back VF queues.
 * @vfdi_status: Common VFDI status page to be dmad to VF address space.
 * @local_addr_list: List of local addresses. Protected by %local_lock.
 * @local_page_list: List of DMA addressable pages used to broadcast
 *	%local_addr_list. Protected by %local_lock.
 * @local_lock: Mutex protecting %local_addr_list and %local_page_list.
 * @peer_work: Work item to broadcast peer addresses to VMs.
 */
काष्ठा siena_nic_data अणु
	काष्ठा efx_nic *efx;
	पूर्णांक wol_filter_id;
	u64 stats[SIENA_STAT_COUNT];
#अगर_घोषित CONFIG_SFC_SRIOV
	काष्ठा siena_vf *vf;
	काष्ठा efx_channel *vfdi_channel;
	अचिन्हित vf_buftbl_base;
	काष्ठा efx_buffer vfdi_status;
	काष्ठा list_head local_addr_list;
	काष्ठा list_head local_page_list;
	काष्ठा mutex local_lock;
	काष्ठा work_काष्ठा peer_work;
#पूर्ण_अगर
पूर्ण;

क्रमागत अणु
	EF10_STAT_port_tx_bytes = GENERIC_STAT_COUNT,
	EF10_STAT_port_tx_packets,
	EF10_STAT_port_tx_छोड़ो,
	EF10_STAT_port_tx_control,
	EF10_STAT_port_tx_unicast,
	EF10_STAT_port_tx_multicast,
	EF10_STAT_port_tx_broadcast,
	EF10_STAT_port_tx_lt64,
	EF10_STAT_port_tx_64,
	EF10_STAT_port_tx_65_to_127,
	EF10_STAT_port_tx_128_to_255,
	EF10_STAT_port_tx_256_to_511,
	EF10_STAT_port_tx_512_to_1023,
	EF10_STAT_port_tx_1024_to_15xx,
	EF10_STAT_port_tx_15xx_to_jumbo,
	EF10_STAT_port_rx_bytes,
	EF10_STAT_port_rx_bytes_minus_good_bytes,
	EF10_STAT_port_rx_good_bytes,
	EF10_STAT_port_rx_bad_bytes,
	EF10_STAT_port_rx_packets,
	EF10_STAT_port_rx_good,
	EF10_STAT_port_rx_bad,
	EF10_STAT_port_rx_छोड़ो,
	EF10_STAT_port_rx_control,
	EF10_STAT_port_rx_unicast,
	EF10_STAT_port_rx_multicast,
	EF10_STAT_port_rx_broadcast,
	EF10_STAT_port_rx_lt64,
	EF10_STAT_port_rx_64,
	EF10_STAT_port_rx_65_to_127,
	EF10_STAT_port_rx_128_to_255,
	EF10_STAT_port_rx_256_to_511,
	EF10_STAT_port_rx_512_to_1023,
	EF10_STAT_port_rx_1024_to_15xx,
	EF10_STAT_port_rx_15xx_to_jumbo,
	EF10_STAT_port_rx_gtjumbo,
	EF10_STAT_port_rx_bad_gtjumbo,
	EF10_STAT_port_rx_overflow,
	EF10_STAT_port_rx_align_error,
	EF10_STAT_port_rx_length_error,
	EF10_STAT_port_rx_nodesc_drops,
	EF10_STAT_port_rx_pm_trunc_bb_overflow,
	EF10_STAT_port_rx_pm_discard_bb_overflow,
	EF10_STAT_port_rx_pm_trunc_vfअगरo_full,
	EF10_STAT_port_rx_pm_discard_vfअगरo_full,
	EF10_STAT_port_rx_pm_trunc_qbb,
	EF10_STAT_port_rx_pm_discard_qbb,
	EF10_STAT_port_rx_pm_discard_mapping,
	EF10_STAT_port_rx_dp_q_disabled_packets,
	EF10_STAT_port_rx_dp_di_dropped_packets,
	EF10_STAT_port_rx_dp_streaming_packets,
	EF10_STAT_port_rx_dp_hlb_fetch,
	EF10_STAT_port_rx_dp_hlb_रुको,
	EF10_STAT_rx_unicast,
	EF10_STAT_rx_unicast_bytes,
	EF10_STAT_rx_multicast,
	EF10_STAT_rx_multicast_bytes,
	EF10_STAT_rx_broadcast,
	EF10_STAT_rx_broadcast_bytes,
	EF10_STAT_rx_bad,
	EF10_STAT_rx_bad_bytes,
	EF10_STAT_rx_overflow,
	EF10_STAT_tx_unicast,
	EF10_STAT_tx_unicast_bytes,
	EF10_STAT_tx_multicast,
	EF10_STAT_tx_multicast_bytes,
	EF10_STAT_tx_broadcast,
	EF10_STAT_tx_broadcast_bytes,
	EF10_STAT_tx_bad,
	EF10_STAT_tx_bad_bytes,
	EF10_STAT_tx_overflow,
	EF10_STAT_V1_COUNT,
	EF10_STAT_fec_uncorrected_errors = EF10_STAT_V1_COUNT,
	EF10_STAT_fec_corrected_errors,
	EF10_STAT_fec_corrected_symbols_lane0,
	EF10_STAT_fec_corrected_symbols_lane1,
	EF10_STAT_fec_corrected_symbols_lane2,
	EF10_STAT_fec_corrected_symbols_lane3,
	EF10_STAT_ctpio_vi_busy_fallback,
	EF10_STAT_ctpio_दीर्घ_ग_लिखो_success,
	EF10_STAT_ctpio_missing_dbell_fail,
	EF10_STAT_ctpio_overflow_fail,
	EF10_STAT_ctpio_underflow_fail,
	EF10_STAT_ctpio_समयout_fail,
	EF10_STAT_ctpio_noncontig_wr_fail,
	EF10_STAT_ctpio_frm_clobber_fail,
	EF10_STAT_ctpio_invalid_wr_fail,
	EF10_STAT_ctpio_vi_clobber_fallback,
	EF10_STAT_ctpio_unqualअगरied_fallback,
	EF10_STAT_ctpio_runt_fallback,
	EF10_STAT_ctpio_success,
	EF10_STAT_ctpio_fallback,
	EF10_STAT_ctpio_poison,
	EF10_STAT_ctpio_erase,
	EF10_STAT_COUNT
पूर्ण;

/* Maximum number of TX PIO buffers we may allocate to a function.
 * This matches the total number of buffers on each SFC9100-family
 * controller.
 */
#घोषणा EF10_TX_PIOBUF_COUNT 16

/**
 * काष्ठा efx_ef10_nic_data - EF10 architecture NIC state
 * @mcdi_buf: DMA buffer क्रम MCDI
 * @warm_boot_count: Last seen MC warm boot count
 * @vi_base: Absolute index of first VI in this function
 * @n_allocated_vis: Number of VIs allocated to this function
 * @n_piobufs: Number of PIO buffers allocated to this function
 * @wc_membase: Base address of ग_लिखो-combining mapping of the memory BAR
 * @pio_ग_लिखो_base: Base address क्रम writing PIO buffers
 * @pio_ग_लिखो_vi_base: Relative VI number क्रम @pio_ग_लिखो_base
 * @piobuf_handle: Handle of each PIO buffer allocated
 * @piobuf_size: size of a single PIO buffer
 * @must_restore_piobufs: Flag: PIO buffers have yet to be restored after MC
 *	reboot
 * @mc_stats: Scratch buffer क्रम converting statistics to the kernel's क्रमmat
 * @stats: Hardware statistics
 * @workaround_35388: Flag: firmware supports workaround क्रम bug 35388
 * @workaround_26807: Flag: firmware supports workaround क्रम bug 26807
 * @workaround_61265: Flag: firmware supports workaround क्रम bug 61265
 * @must_check_datapath_caps: Flag: @datapath_caps needs to be revalidated
 *	after MC reboot
 * @datapath_caps: Capabilities of datapath firmware (FLAGS1 field of
 *	%MC_CMD_GET_CAPABILITIES response)
 * @datapath_caps2: Further Capabilities of datapath firmware (FLAGS2 field of
 * %MC_CMD_GET_CAPABILITIES response)
 * @rx_dpcpu_fw_id: Firmware ID of the RxDPCPU
 * @tx_dpcpu_fw_id: Firmware ID of the TxDPCPU
 * @must_probe_vचयनing: Flag: vचयनing has yet to be setup after MC reboot
 * @pf_index: The number क्रम this PF, or the parent PF अगर this is a VF
#अगर_घोषित CONFIG_SFC_SRIOV
 * @vf: Poपूर्णांकer to VF data काष्ठाure
#पूर्ण_अगर
 * @vport_mac: The MAC address on the vport, only क्रम PFs; VFs will be zero
 * @vlan_list: List of VLANs added over the पूर्णांकerface. Serialised by vlan_lock.
 * @vlan_lock: Lock to serialize access to vlan_list.
 * @udp_tunnels: UDP tunnel port numbers and types.
 * @udp_tunnels_dirty: flag indicating a reboot occurred जबतक pushing
 *	@udp_tunnels to hardware and thus the push must be re-करोne.
 * @udp_tunnels_lock: Serialises ग_लिखोs to @udp_tunnels and @udp_tunnels_dirty.
 */
काष्ठा efx_ef10_nic_data अणु
	काष्ठा efx_buffer mcdi_buf;
	u16 warm_boot_count;
	अचिन्हित पूर्णांक vi_base;
	अचिन्हित पूर्णांक n_allocated_vis;
	अचिन्हित पूर्णांक n_piobufs;
	व्योम __iomem *wc_membase, *pio_ग_लिखो_base;
	अचिन्हित पूर्णांक pio_ग_लिखो_vi_base;
	अचिन्हित पूर्णांक piobuf_handle[EF10_TX_PIOBUF_COUNT];
	u16 piobuf_size;
	bool must_restore_piobufs;
	__le64 *mc_stats;
	u64 stats[EF10_STAT_COUNT];
	bool workaround_35388;
	bool workaround_26807;
	bool workaround_61265;
	bool must_check_datapath_caps;
	u32 datapath_caps;
	u32 datapath_caps2;
	अचिन्हित पूर्णांक rx_dpcpu_fw_id;
	अचिन्हित पूर्णांक tx_dpcpu_fw_id;
	bool must_probe_vचयनing;
	अचिन्हित पूर्णांक pf_index;
	u8 port_id[ETH_ALEN];
#अगर_घोषित CONFIG_SFC_SRIOV
	अचिन्हित पूर्णांक vf_index;
	काष्ठा ef10_vf *vf;
#पूर्ण_अगर
	u8 vport_mac[ETH_ALEN];
	काष्ठा list_head vlan_list;
	काष्ठा mutex vlan_lock;
	काष्ठा efx_udp_tunnel udp_tunnels[16];
	bool udp_tunnels_dirty;
	काष्ठा mutex udp_tunnels_lock;
	u64 licensed_features;
पूर्ण;

/* TSOv2 */
पूर्णांक efx_ef10_tx_tso_desc(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb,
			 bool *data_mapped);

पूर्णांक efx_init_sriov(व्योम);
व्योम efx_fini_sriov(व्योम);

बाह्य स्थिर काष्ठा efx_nic_type siena_a0_nic_type;
बाह्य स्थिर काष्ठा efx_nic_type efx_hunt_a0_nic_type;
बाह्य स्थिर काष्ठा efx_nic_type efx_hunt_a0_vf_nic_type;

पूर्णांक falcon_probe_board(काष्ठा efx_nic *efx, u16 revision_info);

/* Falcon/Siena queue operations */
पूर्णांक efx_farch_tx_probe(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_farch_tx_init(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_farch_tx_fini(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_farch_tx_हटाओ(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_farch_tx_ग_लिखो(काष्ठा efx_tx_queue *tx_queue);
अचिन्हित पूर्णांक efx_farch_tx_limit_len(काष्ठा efx_tx_queue *tx_queue,
				    dma_addr_t dma_addr, अचिन्हित पूर्णांक len);
पूर्णांक efx_farch_rx_probe(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_farch_rx_init(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_farch_rx_fini(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_farch_rx_हटाओ(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_farch_rx_ग_लिखो(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_farch_rx_defer_refill(काष्ठा efx_rx_queue *rx_queue);
पूर्णांक efx_farch_ev_probe(काष्ठा efx_channel *channel);
पूर्णांक efx_farch_ev_init(काष्ठा efx_channel *channel);
व्योम efx_farch_ev_fini(काष्ठा efx_channel *channel);
व्योम efx_farch_ev_हटाओ(काष्ठा efx_channel *channel);
पूर्णांक efx_farch_ev_process(काष्ठा efx_channel *channel, पूर्णांक quota);
व्योम efx_farch_ev_पढ़ो_ack(काष्ठा efx_channel *channel);
व्योम efx_farch_ev_test_generate(काष्ठा efx_channel *channel);

/* Falcon/Siena filter operations */
पूर्णांक efx_farch_filter_table_probe(काष्ठा efx_nic *efx);
व्योम efx_farch_filter_table_restore(काष्ठा efx_nic *efx);
व्योम efx_farch_filter_table_हटाओ(काष्ठा efx_nic *efx);
व्योम efx_farch_filter_update_rx_scatter(काष्ठा efx_nic *efx);
s32 efx_farch_filter_insert(काष्ठा efx_nic *efx, काष्ठा efx_filter_spec *spec,
			    bool replace);
पूर्णांक efx_farch_filter_हटाओ_safe(काष्ठा efx_nic *efx,
				 क्रमागत efx_filter_priority priority,
				 u32 filter_id);
पूर्णांक efx_farch_filter_get_safe(काष्ठा efx_nic *efx,
			      क्रमागत efx_filter_priority priority, u32 filter_id,
			      काष्ठा efx_filter_spec *);
पूर्णांक efx_farch_filter_clear_rx(काष्ठा efx_nic *efx,
			      क्रमागत efx_filter_priority priority);
u32 efx_farch_filter_count_rx_used(काष्ठा efx_nic *efx,
				   क्रमागत efx_filter_priority priority);
u32 efx_farch_filter_get_rx_id_limit(काष्ठा efx_nic *efx);
s32 efx_farch_filter_get_rx_ids(काष्ठा efx_nic *efx,
				क्रमागत efx_filter_priority priority, u32 *buf,
				u32 size);
#अगर_घोषित CONFIG_RFS_ACCEL
bool efx_farch_filter_rfs_expire_one(काष्ठा efx_nic *efx, u32 flow_id,
				     अचिन्हित पूर्णांक index);
#पूर्ण_अगर
व्योम efx_farch_filter_sync_rx_mode(काष्ठा efx_nic *efx);

/* Falcon/Siena पूर्णांकerrupts */
व्योम efx_farch_irq_enable_master(काष्ठा efx_nic *efx);
पूर्णांक efx_farch_irq_test_generate(काष्ठा efx_nic *efx);
व्योम efx_farch_irq_disable_master(काष्ठा efx_nic *efx);
irqवापस_t efx_farch_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t efx_farch_legacy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t efx_farch_fatal_पूर्णांकerrupt(काष्ठा efx_nic *efx);

/* Global Resources */
व्योम siena_prepare_flush(काष्ठा efx_nic *efx);
पूर्णांक efx_farch_fini_dmaq(काष्ठा efx_nic *efx);
व्योम efx_farch_finish_flr(काष्ठा efx_nic *efx);
व्योम siena_finish_flush(काष्ठा efx_nic *efx);
व्योम falcon_start_nic_stats(काष्ठा efx_nic *efx);
व्योम falcon_stop_nic_stats(काष्ठा efx_nic *efx);
पूर्णांक falcon_reset_xaui(काष्ठा efx_nic *efx);
व्योम efx_farch_dimension_resources(काष्ठा efx_nic *efx, अचिन्हित sram_lim_qw);
व्योम efx_farch_init_common(काष्ठा efx_nic *efx);
व्योम efx_farch_rx_push_indir_table(काष्ठा efx_nic *efx);
व्योम efx_farch_rx_pull_indir_table(काष्ठा efx_nic *efx);

/* Tests */
काष्ठा efx_farch_रेजिस्टर_test अणु
	अचिन्हित address;
	efx_oword_t mask;
पूर्ण;

पूर्णांक efx_farch_test_रेजिस्टरs(काष्ठा efx_nic *efx,
			     स्थिर काष्ठा efx_farch_रेजिस्टर_test *regs,
			     माप_प्रकार n_regs);

व्योम efx_farch_generate_event(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक evq,
			      efx_qword_t *event);

#पूर्ण_अगर /* EFX_NIC_H */
