<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-radio-tx.h - radio transmitter support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_RADIO_TX_H_
#घोषणा _VIVID_RADIO_TX_H_

sमाप_प्रकार vivid_radio_tx_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
__poll_t vivid_radio_tx_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको);

पूर्णांक vidioc_g_modulator(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_modulator *a);
पूर्णांक vidioc_s_modulator(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_modulator *a);

#पूर्ण_अगर
