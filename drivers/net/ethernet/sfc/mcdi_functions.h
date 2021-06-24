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
#अगर_अघोषित EFX_MCDI_FUNCTIONS_H
#घोषणा EFX_MCDI_FUNCTIONS_H

पूर्णांक efx_mcdi_alloc_vis(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक min_vis,
		       अचिन्हित पूर्णांक max_vis, अचिन्हित पूर्णांक *vi_base,
		       अचिन्हित पूर्णांक *allocated_vis);
पूर्णांक efx_mcdi_मुक्त_vis(काष्ठा efx_nic *efx);

पूर्णांक efx_mcdi_ev_probe(काष्ठा efx_channel *channel);
पूर्णांक efx_mcdi_ev_init(काष्ठा efx_channel *channel, bool v1_cut_thru, bool v2);
व्योम efx_mcdi_ev_हटाओ(काष्ठा efx_channel *channel);
व्योम efx_mcdi_ev_fini(काष्ठा efx_channel *channel);
पूर्णांक efx_mcdi_tx_init(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_mcdi_tx_हटाओ(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_mcdi_tx_fini(काष्ठा efx_tx_queue *tx_queue);
पूर्णांक efx_mcdi_rx_probe(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_mcdi_rx_init(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_mcdi_rx_हटाओ(काष्ठा efx_rx_queue *rx_queue);
व्योम efx_mcdi_rx_fini(काष्ठा efx_rx_queue *rx_queue);
पूर्णांक efx_fini_dmaq(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_winकरोw_mode_to_stride(काष्ठा efx_nic *efx, u8 vi_winकरोw_mode);
पूर्णांक efx_get_pf_index(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *pf_index);

#पूर्ण_अगर
