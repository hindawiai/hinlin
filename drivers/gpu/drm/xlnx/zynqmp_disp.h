<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ZynqMP Display Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ZYNQMP_DISP_H_
#घोषणा _ZYNQMP_DISP_H_

#समावेश <linux/types.h>

/*
 * 3840x2160 is advertised as the maximum resolution, but almost any
 * resolutions under a 300Mhz pixel rate would work. Pick 4096x4096.
 */
#घोषणा ZYNQMP_DISP_MAX_WIDTH				4096
#घोषणा ZYNQMP_DISP_MAX_HEIGHT				4096

/* The DPDMA is limited to 44 bit addressing. */
#घोषणा ZYNQMP_DISP_MAX_DMA_BIT				44

काष्ठा device;
काष्ठा drm_device;
काष्ठा platक्रमm_device;
काष्ठा zynqmp_disp;
काष्ठा zynqmp_dpsub;

व्योम zynqmp_disp_handle_vblank(काष्ठा zynqmp_disp *disp);
bool zynqmp_disp_audio_enabled(काष्ठा zynqmp_disp *disp);
अचिन्हित पूर्णांक zynqmp_disp_get_audio_clk_rate(काष्ठा zynqmp_disp *disp);
uपूर्णांक32_t zynqmp_disp_get_crtc_mask(काष्ठा zynqmp_disp *disp);

पूर्णांक zynqmp_disp_drm_init(काष्ठा zynqmp_dpsub *dpsub);
पूर्णांक zynqmp_disp_probe(काष्ठा zynqmp_dpsub *dpsub, काष्ठा drm_device *drm);
व्योम zynqmp_disp_हटाओ(काष्ठा zynqmp_dpsub *dpsub);

#पूर्ण_अगर /* _ZYNQMP_DISP_H_ */
