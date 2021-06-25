<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ZynqMP DisplayPort Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ZYNQMP_DP_H_
#घोषणा _ZYNQMP_DP_H_

काष्ठा drm_device;
काष्ठा platक्रमm_device;
काष्ठा zynqmp_dp;
काष्ठा zynqmp_dpsub;

व्योम zynqmp_dp_enable_vblank(काष्ठा zynqmp_dp *dp);
व्योम zynqmp_dp_disable_vblank(काष्ठा zynqmp_dp *dp);

पूर्णांक zynqmp_dp_drm_init(काष्ठा zynqmp_dpsub *dpsub);
पूर्णांक zynqmp_dp_probe(काष्ठा zynqmp_dpsub *dpsub, काष्ठा drm_device *drm);
व्योम zynqmp_dp_हटाओ(काष्ठा zynqmp_dpsub *dpsub);

#पूर्ण_अगर /* _ZYNQMP_DP_H_ */
