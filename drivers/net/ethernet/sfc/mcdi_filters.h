<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */
#अगर_अघोषित EFX_MCDI_FILTERS_H
#घोषणा EFX_MCDI_FILTERS_H

#समावेश "net_driver.h"
#समावेश "filter.h"
#समावेश "mcdi_pcol.h"

#घोषणा EFX_EF10_FILTER_DEV_UC_MAX	32
#घोषणा EFX_EF10_FILTER_DEV_MC_MAX	256

क्रमागत efx_mcdi_filter_शेष_filters अणु
	EFX_EF10_BCAST,
	EFX_EF10_UCDEF,
	EFX_EF10_MCDEF,
	EFX_EF10_VXLAN4_UCDEF,
	EFX_EF10_VXLAN4_MCDEF,
	EFX_EF10_VXLAN6_UCDEF,
	EFX_EF10_VXLAN6_MCDEF,
	EFX_EF10_NVGRE4_UCDEF,
	EFX_EF10_NVGRE4_MCDEF,
	EFX_EF10_NVGRE6_UCDEF,
	EFX_EF10_NVGRE6_MCDEF,
	EFX_EF10_GENEVE4_UCDEF,
	EFX_EF10_GENEVE4_MCDEF,
	EFX_EF10_GENEVE6_UCDEF,
	EFX_EF10_GENEVE6_MCDEF,

	EFX_EF10_NUM_DEFAULT_FILTERS
पूर्ण;

/* Per-VLAN filters inक्रमmation */
काष्ठा efx_mcdi_filter_vlan अणु
	काष्ठा list_head list;
	u16 vid;
	u16 uc[EFX_EF10_FILTER_DEV_UC_MAX];
	u16 mc[EFX_EF10_FILTER_DEV_MC_MAX];
	u16 शेष_filters[EFX_EF10_NUM_DEFAULT_FILTERS];
पूर्ण;

काष्ठा efx_mcdi_dev_addr अणु
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा efx_mcdi_filter_table अणु
/* The MCDI match masks supported by this fw & hw, in order of priority */
	u32 rx_match_mcdi_flags[
		MC_CMD_GET_PARSER_DISP_INFO_OUT_SUPPORTED_MATCHES_MAXNUM * 2];
	अचिन्हित पूर्णांक rx_match_count;
	/* Our RSS context is exclusive (as opposed to shared) */
	bool rx_rss_context_exclusive;

	काष्ठा rw_semaphore lock; /* Protects entries */
	काष्ठा अणु
		अचिन्हित दीर्घ spec;	/* poपूर्णांकer to spec plus flag bits */
/* AUTO_OLD is used to mark and sweep MAC filters क्रम the device address lists. */
/* unused flag	1UL */
#घोषणा EFX_EF10_FILTER_FLAG_AUTO_OLD	2UL
#घोषणा EFX_EF10_FILTER_FLAGS		3UL
		u64 handle;		/* firmware handle */
	पूर्ण *entry;
/* Shaकरोw of net_device address lists, guarded by mac_lock */
	काष्ठा efx_mcdi_dev_addr dev_uc_list[EFX_EF10_FILTER_DEV_UC_MAX];
	काष्ठा efx_mcdi_dev_addr dev_mc_list[EFX_EF10_FILTER_DEV_MC_MAX];
	पूर्णांक dev_uc_count;
	पूर्णांक dev_mc_count;
	bool uc_promisc;
	bool mc_promisc;
/* Whether in multicast promiscuous mode when last changed */
	bool mc_promisc_last;
	bool mc_overflow; /* Too many MC addrs; should always imply mc_promisc */
	/* RSS contexts have yet to be restored after MC reboot */
	bool must_restore_rss_contexts;
	/* filters have yet to be restored after MC reboot */
	bool must_restore_filters;
	/* Multicast filter chaining allows less-specअगरic filters to receive
	 * multicast packets that matched more-specअगरic filters.  Early EF10
	 * firmware didn't support this (SF bug 26807); अगर mc_chaining == false
	 * then we still subscribe the dev_mc_list even when mc_promisc to
	 * prevent another VI stealing the traffic.
	 */
	bool mc_chaining;
	bool vlan_filter;
	काष्ठा list_head vlan_list;
पूर्ण;

पूर्णांक efx_mcdi_filter_table_probe(काष्ठा efx_nic *efx, bool multicast_chaining);
व्योम efx_mcdi_filter_table_करोwn(काष्ठा efx_nic *efx);
व्योम efx_mcdi_filter_table_हटाओ(काष्ठा efx_nic *efx);
व्योम efx_mcdi_filter_table_restore(काष्ठा efx_nic *efx);

व्योम efx_mcdi_filter_table_reset_mc_allocations(काष्ठा efx_nic *efx);

/*
 * The filter table(s) are managed by firmware and we have ग_लिखो-only
 * access.  When removing filters we must identअगरy them to the
 * firmware by a 64-bit handle, but this is too wide क्रम Linux kernel
 * पूर्णांकerfaces (32-bit क्रम RX NFC, 16-bit क्रम RFS).  Also, we need to
 * be able to tell in advance whether a requested insertion will
 * replace an existing filter.  Thereक्रमe we मुख्यtain a software hash
 * table, which should be at least as large as the hardware hash
 * table.
 *
 * Huntington has a single 8K filter table shared between all filter
 * types and both ports.
 */
#घोषणा EFX_MCDI_FILTER_TBL_ROWS 8192

bool efx_mcdi_filter_match_supported(काष्ठा efx_mcdi_filter_table *table,
				     bool encap,
				     क्रमागत efx_filter_match_flags match_flags);

व्योम efx_mcdi_filter_sync_rx_mode(काष्ठा efx_nic *efx);
s32 efx_mcdi_filter_insert(काष्ठा efx_nic *efx, काष्ठा efx_filter_spec *spec,
			   bool replace_equal);
पूर्णांक efx_mcdi_filter_हटाओ_safe(काष्ठा efx_nic *efx,
				क्रमागत efx_filter_priority priority,
				u32 filter_id);
पूर्णांक efx_mcdi_filter_get_safe(काष्ठा efx_nic *efx,
			     क्रमागत efx_filter_priority priority,
			     u32 filter_id, काष्ठा efx_filter_spec *spec);

u32 efx_mcdi_filter_count_rx_used(काष्ठा efx_nic *efx,
				  क्रमागत efx_filter_priority priority);
पूर्णांक efx_mcdi_filter_clear_rx(काष्ठा efx_nic *efx,
			     क्रमागत efx_filter_priority priority);
u32 efx_mcdi_filter_get_rx_id_limit(काष्ठा efx_nic *efx);
s32 efx_mcdi_filter_get_rx_ids(काष्ठा efx_nic *efx,
			       क्रमागत efx_filter_priority priority,
			       u32 *buf, u32 size);

व्योम efx_mcdi_filter_cleanup_vlans(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_filter_add_vlan(काष्ठा efx_nic *efx, u16 vid);
काष्ठा efx_mcdi_filter_vlan *efx_mcdi_filter_find_vlan(काष्ठा efx_nic *efx, u16 vid);
व्योम efx_mcdi_filter_del_vlan(काष्ठा efx_nic *efx, u16 vid);

व्योम efx_mcdi_rx_मुक्त_indir_table(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_rx_push_rss_context_config(काष्ठा efx_nic *efx,
					काष्ठा efx_rss_context *ctx,
					स्थिर u32 *rx_indir_table,
					स्थिर u8 *key);
पूर्णांक efx_mcdi_pf_rx_push_rss_config(काष्ठा efx_nic *efx, bool user,
				   स्थिर u32 *rx_indir_table,
				   स्थिर u8 *key);
पूर्णांक efx_mcdi_vf_rx_push_rss_config(काष्ठा efx_nic *efx, bool user,
				   स्थिर u32 *rx_indir_table
				   __attribute__ ((unused)),
				   स्थिर u8 *key
				   __attribute__ ((unused)));
पूर्णांक efx_mcdi_push_शेष_indir_table(काष्ठा efx_nic *efx,
				      अचिन्हित पूर्णांक rss_spपढ़ो);
पूर्णांक efx_mcdi_rx_pull_rss_config(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_rx_pull_rss_context_config(काष्ठा efx_nic *efx,
					काष्ठा efx_rss_context *ctx);
पूर्णांक efx_mcdi_get_rss_context_flags(काष्ठा efx_nic *efx, u32 context,
				   u32 *flags);
व्योम efx_mcdi_set_rss_context_flags(काष्ठा efx_nic *efx,
				    काष्ठा efx_rss_context *ctx);
व्योम efx_mcdi_rx_restore_rss_contexts(काष्ठा efx_nic *efx);

अटल अंतरभूत व्योम efx_mcdi_update_rx_scatter(काष्ठा efx_nic *efx)
अणु
	/* no need to करो anything here */
पूर्ण

bool efx_mcdi_filter_rfs_expire_one(काष्ठा efx_nic *efx, u32 flow_id,
				    अचिन्हित पूर्णांक filter_idx);

#पूर्ण_अगर
