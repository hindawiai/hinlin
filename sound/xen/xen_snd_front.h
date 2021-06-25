<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_SND_FRONT_H
#घोषणा __XEN_SND_FRONT_H

#समावेश "xen_snd_front_cfg.h"

काष्ठा xen_snd_front_card_info;
काष्ठा xen_snd_front_evtchnl;
काष्ठा xen_snd_front_evtchnl_pair;
काष्ठा xen_front_pgdir_shbuf;
काष्ठा xensnd_query_hw_param;

काष्ठा xen_snd_front_info अणु
	काष्ठा xenbus_device *xb_dev;

	काष्ठा xen_snd_front_card_info *card_info;

	पूर्णांक num_evt_pairs;
	काष्ठा xen_snd_front_evtchnl_pair *evt_pairs;

	काष्ठा xen_front_cfg_card cfg;
पूर्ण;

पूर्णांक xen_snd_front_stream_query_hw_param(काष्ठा xen_snd_front_evtchnl *evtchnl,
					काष्ठा xensnd_query_hw_param *hw_param_req,
					काष्ठा xensnd_query_hw_param *hw_param_resp);

पूर्णांक xen_snd_front_stream_prepare(काष्ठा xen_snd_front_evtchnl *evtchnl,
				 काष्ठा xen_front_pgdir_shbuf *shbuf,
				 u8 क्रमmat, अचिन्हित पूर्णांक channels,
				 अचिन्हित पूर्णांक rate, u32 buffer_sz,
				 u32 period_sz);

पूर्णांक xen_snd_front_stream_बंद(काष्ठा xen_snd_front_evtchnl *evtchnl);

पूर्णांक xen_snd_front_stream_ग_लिखो(काष्ठा xen_snd_front_evtchnl *evtchnl,
			       अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count);

पूर्णांक xen_snd_front_stream_पढ़ो(काष्ठा xen_snd_front_evtchnl *evtchnl,
			      अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count);

पूर्णांक xen_snd_front_stream_trigger(काष्ठा xen_snd_front_evtchnl *evtchnl,
				 पूर्णांक type);

#पूर्ण_अगर /* __XEN_SND_FRONT_H */
