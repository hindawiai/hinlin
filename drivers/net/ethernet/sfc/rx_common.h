<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित EFX_RX_COMMON_H
#घोषणा EFX_RX_COMMON_H

/* Preferred number of descriptors to fill at once */
#घोषणा EFX_RX_PREFERRED_BATCH 8U

/* Each packet can consume up to उच्चमान(max_frame_len / buffer_size) buffers */
#घोषणा EFX_RX_MAX_FRAGS DIV_ROUND_UP(EFX_MAX_FRAME_LEN(EFX_MAX_MTU), \
				      EFX_RX_USR_BUF_SIZE)

अटल अंतरभूत u8 *efx_rx_buf_va(काष्ठा efx_rx_buffer *buf)
अणु
	वापस page_address(buf->page) + buf->page_offset;
पूर्ण

अटल अंतरभूत u32 efx_rx_buf_hash(काष्ठा efx_nic *efx, स्थिर u8 *eh)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस __le32_to_cpup((स्थिर __le32 *)(eh + efx->rx_packet_hash_offset));
#अन्यथा
	स्थिर u8 *data = eh + efx->rx_packet_hash_offset;

	वापस (u32)data[0]	  |
	       (u32)data[1] << 8  |
	       (u32)data[2] << 16 |
	       (u32)data[3] << 24;
#पूर्ण_अगर
पूर्ण

व्योम efx_rx_slow_fill(काष्ठा समयr_list *t);

व्योम efx_recycle_rx_pages(काष्ठा efx_channel *channel,
			  काष्ठा efx_rx_buffer *rx_buf,
			  अचिन्हित पूर्णांक n_frags);
व्योम efx_discard_rx_packet(काष्ठा efx_channel *channel,
			   काष्ठा efx_rx_buffer *rx_buf,
			   अचिन्हित पूर्णांक n_frags);

पूर्णांक efx_probe_rx_queue(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_init_rx_queue(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_fini_rx_queue(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_हटाओ_rx_queue(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_destroy_rx_queue(काष्ठा efx_rx_queue *rx_queue);

व्योम efx_init_rx_buffer(काष्ठा efx_rx_queue *rx_queue,
			काष्ठा page *page,
			अचिन्हित पूर्णांक page_offset,
			u16 flags);
व्योम efx_unmap_rx_buffer(काष्ठा efx_nic *efx, काष्ठा efx_rx_buffer *rx_buf);

अटल अंतरभूत व्योम efx_sync_rx_buffer(काष्ठा efx_nic *efx,
				      काष्ठा efx_rx_buffer *rx_buf,
				      अचिन्हित पूर्णांक len)
अणु
	dma_sync_single_क्रम_cpu(&efx->pci_dev->dev, rx_buf->dma_addr, len,
				DMA_FROM_DEVICE);
पूर्ण

व्योम efx_मुक्त_rx_buffers(काष्ठा efx_rx_queue *rx_queue,
			 काष्ठा efx_rx_buffer *rx_buf,
			 अचिन्हित पूर्णांक num_bufs);

व्योम efx_schedule_slow_fill(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_rx_config_page_split(काष्ठा efx_nic *efx);
व्योम efx_fast_push_rx_descriptors(काष्ठा efx_rx_queue *rx_queue, bool atomic);

व्योम
efx_rx_packet_gro(काष्ठा efx_channel *channel, काष्ठा efx_rx_buffer *rx_buf,
		  अचिन्हित पूर्णांक n_frags, u8 *eh, __wsum csum);

काष्ठा efx_rss_context *efx_alloc_rss_context_entry(काष्ठा efx_nic *efx);
काष्ठा efx_rss_context *efx_find_rss_context_entry(काष्ठा efx_nic *efx, u32 id);
व्योम efx_मुक्त_rss_context_entry(काष्ठा efx_rss_context *ctx);
व्योम efx_set_शेष_rx_indir_table(काष्ठा efx_nic *efx,
				    काष्ठा efx_rss_context *ctx);

bool efx_filter_is_mc_recipient(स्थिर काष्ठा efx_filter_spec *spec);
bool efx_filter_spec_equal(स्थिर काष्ठा efx_filter_spec *left,
			   स्थिर काष्ठा efx_filter_spec *right);
u32 efx_filter_spec_hash(स्थिर काष्ठा efx_filter_spec *spec);

#अगर_घोषित CONFIG_RFS_ACCEL
bool efx_rps_check_rule(काष्ठा efx_arfs_rule *rule, अचिन्हित पूर्णांक filter_idx,
			bool *क्रमce);
काष्ठा efx_arfs_rule *efx_rps_hash_find(काष्ठा efx_nic *efx,
					स्थिर काष्ठा efx_filter_spec *spec);
काष्ठा efx_arfs_rule *efx_rps_hash_add(काष्ठा efx_nic *efx,
				       स्थिर काष्ठा efx_filter_spec *spec,
				       bool *new);
व्योम efx_rps_hash_del(काष्ठा efx_nic *efx, स्थिर काष्ठा efx_filter_spec *spec);

पूर्णांक efx_filter_rfs(काष्ठा net_device *net_dev, स्थिर काष्ठा sk_buff *skb,
		   u16 rxq_index, u32 flow_id);
bool __efx_filter_rfs_expire(काष्ठा efx_channel *channel, अचिन्हित पूर्णांक quota);
#पूर्ण_अगर

पूर्णांक efx_probe_filters(काष्ठा efx_nic *efx);
व्योम efx_हटाओ_filters(काष्ठा efx_nic *efx);

#पूर्ण_अगर
