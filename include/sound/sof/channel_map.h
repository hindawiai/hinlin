<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2019 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __IPC_CHANNEL_MAP_H__
#घोषणा __IPC_CHANNEL_MAP_H__

#समावेश <uapi/sound/sof/header.h>
#समावेश <sound/sof/header.h>

/**
 * \मrief Channel map, specअगरies transक्रमmation of one-to-many or many-to-one.
 *
 * In हाल of one-to-many specअगरies how the output channels are computed out of
 * a single source channel,
 * in हाल of many-to-one specअगरies how a single target channel is computed
 * from a multichannel input stream.
 *
 * Channel index specअगरies position of the channel in the stream on the 'one'
 * side.
 *
 * Ext ID is the identअगरier of बाह्यal part of the transक्रमmation. Depending
 * on the context, it may be pipeline ID, dai ID, ...
 *
 * Channel mask describes which channels are taken पूर्णांकo account on the "many"
 * side. Bit[i] set to 1 means that i-th channel is used क्रम computation
 * (either as source or as a target).
 *
 * Channel mask is followed by array of coefficients in Q2.30 क्रमmat,
 * one per each channel set in the mask (left to right, LS bit set in the
 * mask corresponds to ch_coeffs[0]).
 */
काष्ठा sof_ipc_channel_map अणु
	uपूर्णांक32_t ch_index;
	uपूर्णांक32_t ext_id;
	uपूर्णांक32_t ch_mask;
	uपूर्णांक32_t reserved;
	पूर्णांक32_t ch_coeffs[0];
पूर्ण __packed;

/**
 * \मrief Complete map क्रम each channel of a multichannel stream.
 *
 * num_ch_map Specअगरies number of items in the ch_map.
 * More than one transक्रमmation per a single channel is allowed (in हाल
 * multiple बाह्यal entities are transक्रमmed).
 * A channel may be skipped in the transक्रमmation list, then it is filled
 * with 0's by the transक्रमmation function.
 */
काष्ठा sof_ipc_stream_map अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t num_ch_map;
	uपूर्णांक32_t reserved[3];
	काष्ठा sof_ipc_channel_map ch_map[0];
पूर्ण __packed;

#पूर्ण_अगर /* __IPC_CHANNEL_MAP_H__ */
