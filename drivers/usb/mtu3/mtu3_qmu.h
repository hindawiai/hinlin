<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtu3_qmu.h - Queue Management Unit driver header
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#अगर_अघोषित __MTK_QMU_H__
#घोषणा __MTK_QMU_H__

#घोषणा MAX_GPD_NUM		64
#घोषणा QMU_GPD_SIZE		(माप(काष्ठा qmu_gpd))
#घोषणा QMU_GPD_RING_SIZE	(MAX_GPD_NUM * QMU_GPD_SIZE)

#घोषणा GPD_BUF_SIZE		65532
#घोषणा GPD_BUF_SIZE_EL		1048572

व्योम mtu3_qmu_stop(काष्ठा mtu3_ep *mep);
पूर्णांक mtu3_qmu_start(काष्ठा mtu3_ep *mep);
व्योम mtu3_qmu_resume(काष्ठा mtu3_ep *mep);
व्योम mtu3_qmu_flush(काष्ठा mtu3_ep *mep);

व्योम mtu3_insert_gpd(काष्ठा mtu3_ep *mep, काष्ठा mtu3_request *mreq);
पूर्णांक mtu3_prepare_transfer(काष्ठा mtu3_ep *mep);

पूर्णांक mtu3_gpd_ring_alloc(काष्ठा mtu3_ep *mep);
व्योम mtu3_gpd_ring_मुक्त(काष्ठा mtu3_ep *mep);

irqवापस_t mtu3_qmu_isr(काष्ठा mtu3 *mtu);
पूर्णांक mtu3_qmu_init(काष्ठा mtu3 *mtu);
व्योम mtu3_qmu_निकास(काष्ठा mtu3 *mtu);

#पूर्ण_अगर
