<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-radio-rx.h - radio receiver support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_RADIO_RX_H_
#घोषणा _VIVID_RADIO_RX_H_

sमाप_प्रकार vivid_radio_rx_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
__poll_t vivid_radio_rx_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको);

पूर्णांक vivid_radio_rx_क्रमागत_freq_bands(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency_band *band);
पूर्णांक vivid_radio_rx_s_hw_freq_seek(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_hw_freq_seek *a);
पूर्णांक vivid_radio_rx_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt);
पूर्णांक vivid_radio_rx_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt);

#पूर्ण_अगर
