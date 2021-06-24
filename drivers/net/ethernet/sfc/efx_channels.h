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

#अगर_अघोषित EFX_CHANNELS_H
#घोषणा EFX_CHANNELS_H

बाह्य अचिन्हित पूर्णांक efx_पूर्णांकerrupt_mode;
बाह्य अचिन्हित पूर्णांक rss_cpus;

पूर्णांक efx_probe_पूर्णांकerrupts(काष्ठा efx_nic *efx);
व्योम efx_हटाओ_पूर्णांकerrupts(काष्ठा efx_nic *efx);
पूर्णांक efx_soft_enable_पूर्णांकerrupts(काष्ठा efx_nic *efx);
व्योम efx_soft_disable_पूर्णांकerrupts(काष्ठा efx_nic *efx);
पूर्णांक efx_enable_पूर्णांकerrupts(काष्ठा efx_nic *efx);
व्योम efx_disable_पूर्णांकerrupts(काष्ठा efx_nic *efx);

व्योम efx_set_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx);
व्योम efx_clear_पूर्णांकerrupt_affinity(काष्ठा efx_nic *efx);

पूर्णांक efx_probe_eventq(काष्ठा efx_channel *channel);
पूर्णांक efx_init_eventq(काष्ठा efx_channel *channel);
व्योम efx_start_eventq(काष्ठा efx_channel *channel);
व्योम efx_stop_eventq(काष्ठा efx_channel *channel);
व्योम efx_fini_eventq(काष्ठा efx_channel *channel);
व्योम efx_हटाओ_eventq(काष्ठा efx_channel *channel);

पूर्णांक efx_पुनः_स्मृति_channels(काष्ठा efx_nic *efx, u32 rxq_entries, u32 txq_entries);
व्योम efx_get_channel_name(काष्ठा efx_channel *channel, अक्षर *buf, माप_प्रकार len);
व्योम efx_set_channel_names(काष्ठा efx_nic *efx);
पूर्णांक efx_init_channels(काष्ठा efx_nic *efx);
पूर्णांक efx_probe_channels(काष्ठा efx_nic *efx);
पूर्णांक efx_set_channels(काष्ठा efx_nic *efx);
bool efx_शेष_channel_want_txqs(काष्ठा efx_channel *channel);
व्योम efx_हटाओ_channel(काष्ठा efx_channel *channel);
व्योम efx_हटाओ_channels(काष्ठा efx_nic *efx);
व्योम efx_fini_channels(काष्ठा efx_nic *efx);
काष्ठा efx_channel *efx_copy_channel(स्थिर काष्ठा efx_channel *old_channel);
व्योम efx_start_channels(काष्ठा efx_nic *efx);
व्योम efx_stop_channels(काष्ठा efx_nic *efx);

व्योम efx_init_napi_channel(काष्ठा efx_channel *channel);
व्योम efx_init_napi(काष्ठा efx_nic *efx);
व्योम efx_fini_napi_channel(काष्ठा efx_channel *channel);
व्योम efx_fini_napi(काष्ठा efx_nic *efx);

पूर्णांक efx_channel_dummy_op_पूर्णांक(काष्ठा efx_channel *channel);
व्योम efx_channel_dummy_op_व्योम(काष्ठा efx_channel *channel);

#पूर्ण_अगर
