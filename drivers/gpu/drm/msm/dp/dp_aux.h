<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_AUX_H_
#घोषणा _DP_AUX_H_

#समावेश "dp_catalog.h"
#समावेश <drm/drm_dp_helper.h>

#घोषणा DP_AUX_ERR_NONE		0
#घोषणा DP_AUX_ERR_ADDR		-1
#घोषणा DP_AUX_ERR_TOUT		-2
#घोषणा DP_AUX_ERR_NACK		-3
#घोषणा DP_AUX_ERR_DEFER	-4
#घोषणा DP_AUX_ERR_NACK_DEFER	-5
#घोषणा DP_AUX_ERR_PHY		-6

पूर्णांक dp_aux_रेजिस्टर(काष्ठा drm_dp_aux *dp_aux);
व्योम dp_aux_unरेजिस्टर(काष्ठा drm_dp_aux *dp_aux);
व्योम dp_aux_isr(काष्ठा drm_dp_aux *dp_aux);
व्योम dp_aux_init(काष्ठा drm_dp_aux *dp_aux);
व्योम dp_aux_deinit(काष्ठा drm_dp_aux *dp_aux);
व्योम dp_aux_reconfig(काष्ठा drm_dp_aux *dp_aux);

काष्ठा drm_dp_aux *dp_aux_get(काष्ठा device *dev, काष्ठा dp_catalog *catalog);
व्योम dp_aux_put(काष्ठा drm_dp_aux *aux);

#पूर्ण_अगर /*__DP_AUX_H_*/
