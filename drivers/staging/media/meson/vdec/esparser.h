<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_ESPARSER_H_
#घोषणा __MESON_VDEC_ESPARSER_H_

#समावेश <linux/platक्रमm_device.h>

#समावेश "vdec.h"

पूर्णांक esparser_init(काष्ठा platक्रमm_device *pdev, काष्ठा amvdec_core *core);
पूर्णांक esparser_घातer_up(काष्ठा amvdec_session *sess);

/**
 * esparser_queue_eos() - ग_लिखो End Of Stream sequence to the ESPARSER
 *
 * @core vdec core काष्ठा
 */
पूर्णांक esparser_queue_eos(काष्ठा amvdec_core *core, स्थिर u8 *data, u32 len);

/**
 * esparser_queue_all_src() - work handler that ग_लिखोs as many src buffers
 * as possible to the ESPARSER
 */
व्योम esparser_queue_all_src(काष्ठा work_काष्ठा *work);

#घोषणा ESPARSER_MIN_PACKET_SIZE SZ_4K

#पूर्ण_अगर
