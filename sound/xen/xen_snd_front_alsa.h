<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_SND_FRONT_ALSA_H
#घोषणा __XEN_SND_FRONT_ALSA_H

काष्ठा xen_snd_front_info;

पूर्णांक xen_snd_front_alsa_init(काष्ठा xen_snd_front_info *front_info);

व्योम xen_snd_front_alsa_fini(काष्ठा xen_snd_front_info *front_info);

व्योम xen_snd_front_alsa_handle_cur_pos(काष्ठा xen_snd_front_evtchnl *evtchnl,
				       u64 pos_bytes);

#पूर्ण_अगर /* __XEN_SND_FRONT_ALSA_H */
