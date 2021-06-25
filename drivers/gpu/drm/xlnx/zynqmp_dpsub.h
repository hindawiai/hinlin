<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ZynqMP DPSUB Subप्रणाली Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ZYNQMP_DPSUB_H_
#घोषणा _ZYNQMP_DPSUB_H_

काष्ठा clk;
काष्ठा device;
काष्ठा drm_device;
काष्ठा zynqmp_disp;
काष्ठा zynqmp_dp;

क्रमागत zynqmp_dpsub_क्रमmat अणु
	ZYNQMP_DPSUB_FORMAT_RGB,
	ZYNQMP_DPSUB_FORMAT_YCRCB444,
	ZYNQMP_DPSUB_FORMAT_YCRCB422,
	ZYNQMP_DPSUB_FORMAT_YONLY,
पूर्ण;

/**
 * काष्ठा zynqmp_dpsub - ZynqMP DisplayPort Subप्रणाली
 * @drm: The DRM/KMS device
 * @dev: The physical device
 * @apb_clk: The APB घड़ी
 * @disp: The display controller
 * @dp: The DisplayPort controller
 * @dma_align: DMA alignment स्थिरraपूर्णांक (must be a घातer of 2)
 */
काष्ठा zynqmp_dpsub अणु
	काष्ठा drm_device drm;
	काष्ठा device *dev;

	काष्ठा clk *apb_clk;

	काष्ठा zynqmp_disp *disp;
	काष्ठा zynqmp_dp *dp;

	अचिन्हित पूर्णांक dma_align;
पूर्ण;

अटल अंतरभूत काष्ठा zynqmp_dpsub *to_zynqmp_dpsub(काष्ठा drm_device *drm)
अणु
	वापस container_of(drm, काष्ठा zynqmp_dpsub, drm);
पूर्ण

#पूर्ण_अगर /* _ZYNQMP_DPSUB_H_ */
