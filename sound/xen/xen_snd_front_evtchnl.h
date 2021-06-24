<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_SND_FRONT_EVTCHNL_H
#घोषणा __XEN_SND_FRONT_EVTCHNL_H

#समावेश <xen/पूर्णांकerface/io/sndअगर.h>

काष्ठा xen_snd_front_info;

#अगर_अघोषित GRANT_INVALID_REF
/*
 * FIXME: usage of grant reference 0 as invalid grant reference:
 * grant reference 0 is valid, but never exposed to a PV driver,
 * because of the fact it is alपढ़ोy in use/reserved by the PV console.
 */
#घोषणा GRANT_INVALID_REF	0
#पूर्ण_अगर

/* Timeout in ms to रुको क्रम backend to respond. */
#घोषणा VSND_WAIT_BACK_MS	3000

क्रमागत xen_snd_front_evtchnl_state अणु
	EVTCHNL_STATE_DISCONNECTED,
	EVTCHNL_STATE_CONNECTED,
पूर्ण;

क्रमागत xen_snd_front_evtchnl_type अणु
	EVTCHNL_TYPE_REQ,
	EVTCHNL_TYPE_EVT,
पूर्ण;

काष्ठा xen_snd_front_evtchnl अणु
	काष्ठा xen_snd_front_info *front_info;
	पूर्णांक gref;
	पूर्णांक port;
	पूर्णांक irq;
	पूर्णांक index;
	/* State of the event channel. */
	क्रमागत xen_snd_front_evtchnl_state state;
	क्रमागत xen_snd_front_evtchnl_type type;
	/* Either response id or incoming event id. */
	u16 evt_id;
	/* Next request id or next expected event id. */
	u16 evt_next_id;
	/* Shared ring access lock. */
	काष्ठा mutex ring_io_lock;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा xen_sndअगर_front_ring ring;
			काष्ठा completion completion;
			/* Serializer क्रम backend IO: request/response. */
			काष्ठा mutex req_io_lock;

			/* Latest response status. */
			पूर्णांक resp_status;
			जोड़ अणु
				काष्ठा xensnd_query_hw_param hw_param;
			पूर्ण resp;
		पूर्ण req;
		काष्ठा अणु
			काष्ठा xensnd_event_page *page;
			/* This is needed to handle XENSND_EVT_CUR_POS event. */
			काष्ठा snd_pcm_substream *substream;
		पूर्ण evt;
	पूर्ण u;
पूर्ण;

काष्ठा xen_snd_front_evtchnl_pair अणु
	काष्ठा xen_snd_front_evtchnl req;
	काष्ठा xen_snd_front_evtchnl evt;
पूर्ण;

पूर्णांक xen_snd_front_evtchnl_create_all(काष्ठा xen_snd_front_info *front_info,
				     पूर्णांक num_streams);

व्योम xen_snd_front_evtchnl_मुक्त_all(काष्ठा xen_snd_front_info *front_info);

पूर्णांक xen_snd_front_evtchnl_publish_all(काष्ठा xen_snd_front_info *front_info);

व्योम xen_snd_front_evtchnl_flush(काष्ठा xen_snd_front_evtchnl *evtchnl);

व्योम xen_snd_front_evtchnl_pair_set_connected(काष्ठा xen_snd_front_evtchnl_pair *evt_pair,
					      bool is_connected);

व्योम xen_snd_front_evtchnl_pair_clear(काष्ठा xen_snd_front_evtchnl_pair *evt_pair);

#पूर्ण_अगर /* __XEN_SND_FRONT_EVTCHNL_H */
