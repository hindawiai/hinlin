<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_SND_FRONT_CFG_H
#घोषणा __XEN_SND_FRONT_CFG_H

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

काष्ठा xen_snd_front_info;

काष्ठा xen_front_cfg_stream अणु
	पूर्णांक index;
	अक्षर *xenstore_path;
	काष्ठा snd_pcm_hardware pcm_hw;
पूर्ण;

काष्ठा xen_front_cfg_pcm_instance अणु
	अक्षर name[80];
	पूर्णांक device_id;
	काष्ठा snd_pcm_hardware pcm_hw;
	पूर्णांक  num_streams_pb;
	काष्ठा xen_front_cfg_stream *streams_pb;
	पूर्णांक  num_streams_cap;
	काष्ठा xen_front_cfg_stream *streams_cap;
पूर्ण;

काष्ठा xen_front_cfg_card अणु
	अक्षर name_लघु[32];
	अक्षर name_दीर्घ[80];
	काष्ठा snd_pcm_hardware pcm_hw;
	पूर्णांक num_pcm_instances;
	काष्ठा xen_front_cfg_pcm_instance *pcm_instances;
पूर्ण;

पूर्णांक xen_snd_front_cfg_card(काष्ठा xen_snd_front_info *front_info,
			   पूर्णांक *stream_cnt);

#पूर्ण_अगर /* __XEN_SND_FRONT_CFG_H */
