<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */
#अगर_अघोषित _MTK_CEC_H
#घोषणा _MTK_CEC_H

#समावेश <linux/types.h>

काष्ठा device;

व्योम mtk_cec_set_hpd_event(काष्ठा device *dev,
			   व्योम (*hotplug_event)(bool hpd, काष्ठा device *dev),
			   काष्ठा device *hdmi_dev);
bool mtk_cec_hpd_high(काष्ठा device *dev);

#पूर्ण_अगर /* _MTK_CEC_H */
