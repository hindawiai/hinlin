<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the code क्रम a 'channel' असलtraction.
 *
 * When vidtv boots, it will create some hardcoded channels.
 * Their services will be concatenated to populate the SDT.
 * Their programs will be concatenated to populate the PAT
 * Their events will be concatenated to populate the EIT
 * For each program in the PAT, a PMT section will be created
 * The PMT section क्रम a channel will be asचिन्हित its streams.
 * Every stream will have its corresponding encoder polled to produce TS packets
 * These packets may be पूर्णांकerleaved by the mux and then delivered to the bridge
 *
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_CHANNEL_H
#घोषणा VIDTV_CHANNEL_H

#समावेश <linux/types.h>

#समावेश "vidtv_encoder.h"
#समावेश "vidtv_mux.h"
#समावेश "vidtv_psi.h"

/**
 * काष्ठा vidtv_channel - A 'channel' असलtraction
 *
 * When vidtv boots, it will create some hardcoded channels.
 * Their services will be concatenated to populate the SDT.
 * Their programs will be concatenated to populate the PAT
 * For each program in the PAT, a PMT section will be created
 * The PMT section क्रम a channel will be asचिन्हित its streams.
 * Every stream will have its corresponding encoder polled to produce TS packets
 * These packets may be पूर्णांकerleaved by the mux and then delivered to the bridge
 *
 * @name: name of the channel
 * @transport_stream_id: a number to identअगरy the TS, chosen at will.
 * @service: A _single_ service. Will be concatenated पूर्णांकo the SDT.
 * @program_num: The link between PAT, PMT and SDT.
 * @program: A _single_ program with one or more streams associated with it.
 * Will be concatenated पूर्णांकo the PAT.
 * @streams: A stream loop used to populate the PMT section क्रम 'program'
 * @encoders: A encoder loop. There must be one encoder क्रम each stream.
 * @events: Optional event inक्रमmation. This will feed पूर्णांकo the EIT.
 * @next: Optionally chain this channel.
 */
काष्ठा vidtv_channel अणु
	अक्षर *name;
	u16 transport_stream_id;
	काष्ठा vidtv_psi_table_sdt_service *service;
	u16 program_num;
	काष्ठा vidtv_psi_table_pat_program *program;
	काष्ठा vidtv_psi_table_pmt_stream *streams;
	काष्ठा vidtv_encoder *encoders;
	काष्ठा vidtv_psi_table_eit_event *events;
	काष्ठा vidtv_channel *next;
पूर्ण;

/**
 * vidtv_channel_si_init - Init the PSI tables from the channels in the mux
 * @m: The mux containing the channels.
 */
पूर्णांक vidtv_channel_si_init(काष्ठा vidtv_mux *m);
व्योम vidtv_channel_si_destroy(काष्ठा vidtv_mux *m);

/**
 * vidtv_channels_init - Init hardcoded, fake 'channels'.
 * @m: The mux to store the channels पूर्णांकo.
 */
पूर्णांक vidtv_channels_init(काष्ठा vidtv_mux *m);
काष्ठा vidtv_channel
*vidtv_channel_s302m_init(काष्ठा vidtv_channel *head, u16 transport_stream_id);
व्योम vidtv_channels_destroy(काष्ठा vidtv_mux *m);

#पूर्ण_अगर //VIDTV_CHANNEL_H
