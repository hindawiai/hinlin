<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    camera.h - PXA camera driver header file

    Copyright (C) 2003, Intel Corporation
    Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>

*/

#अगर_अघोषित __ASM_ARCH_CAMERA_H_
#घोषणा __ASM_ARCH_CAMERA_H_

#घोषणा PXA_CAMERA_MASTER	1
#घोषणा PXA_CAMERA_DATAWIDTH_4	2
#घोषणा PXA_CAMERA_DATAWIDTH_5	4
#घोषणा PXA_CAMERA_DATAWIDTH_8	8
#घोषणा PXA_CAMERA_DATAWIDTH_9	0x10
#घोषणा PXA_CAMERA_DATAWIDTH_10	0x20
#घोषणा PXA_CAMERA_PCLK_EN	0x40
#घोषणा PXA_CAMERA_MCLK_EN	0x80
#घोषणा PXA_CAMERA_PCP		0x100
#घोषणा PXA_CAMERA_HSP		0x200
#घोषणा PXA_CAMERA_VSP		0x400

काष्ठा pxacamera_platक्रमm_data अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mclk_10khz;
	पूर्णांक sensor_i2c_adapter_id;
	पूर्णांक sensor_i2c_address;
पूर्ण;

बाह्य व्योम pxa_set_camera_info(काष्ठा pxacamera_platक्रमm_data *);

#पूर्ण_अगर /* __ASM_ARCH_CAMERA_H_ */
