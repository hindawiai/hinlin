<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __ISYS_DMA_GLOBAL_H_INCLUDED__
#घोषणा __ISYS_DMA_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

#घोषणा HIVE_ISYS2401_DMA_IBUF_DDR_CONN	0
#घोषणा HIVE_ISYS2401_DMA_IBUF_VMEM_CONN	1
#घोषणा _DMA_V2_ZERO_EXTEND		0
#घोषणा _DMA_V2_SIGN_EXTEND		1

#घोषणा _DMA_ZERO_EXTEND     _DMA_V2_ZERO_EXTEND
#घोषणा _DMA_SIGN_EXTEND     _DMA_V2_SIGN_EXTEND

/********************************************************
 *
 * DMA Port.
 *
 * The DMA port definition क्रम the input प्रणाली
 * 2401 DMA is the duplication of the DMA port
 * definition क्रम the CSS प्रणाली DMA. It is duplicated
 * here just as the temporal step beक्रमe the device library
 * is available. The device library is suppose to provide
 * the capability of reusing the control पूर्णांकerface of the
 * same device prototypes. The refactor team will work on
 * this, right?
 *
 ********************************************************/
प्रकार काष्ठा isys2401_dma_port_cfg_s isys2401_dma_port_cfg_t;
काष्ठा isys2401_dma_port_cfg_s अणु
	u32 stride;
	u32 elements;
	u32 cropping;
	u32 width;
पूर्ण;

/* end of DMA Port */

/************************************************
 *
 * DMA Device.
 *
 * The DMA device definition क्रम the input प्रणाली
 * 2401 DMA is the duplicattion of the DMA device
 * definition क्रम the CSS प्रणाली DMA. It is duplicated
 * here just as the temporal step beक्रमe the device library
 * is available. The device library is suppose to provide
 * the capability of reusing the control पूर्णांकerface of the
 * same device prototypes. The refactor team will work on
 * this, right?
 *
 ************************************************/
प्रकार क्रमागत अणु
	isys2401_dma_ibuf_to_ddr_connection	= HIVE_ISYS2401_DMA_IBUF_DDR_CONN,
	isys2401_dma_ibuf_to_vmem_connection	= HIVE_ISYS2401_DMA_IBUF_VMEM_CONN
पूर्ण isys2401_dma_connection;

प्रकार क्रमागत अणु
	isys2401_dma_zero_extension = _DMA_ZERO_EXTEND,
	isys2401_dma_sign_extension = _DMA_SIGN_EXTEND
पूर्ण isys2401_dma_extension;

प्रकार काष्ठा isys2401_dma_cfg_s isys2401_dma_cfg_t;
काष्ठा isys2401_dma_cfg_s अणु
	isys2401_dma_channel	channel;
	isys2401_dma_connection	connection;
	isys2401_dma_extension	extension;
	u32		height;
पूर्ण;

/* end of DMA Device */

/* isys2401_dma_channel limits per DMA ID */
बाह्य स्थिर isys2401_dma_channel
N_ISYS2401_DMA_CHANNEL_PROCS[N_ISYS2401_DMA_ID];

#पूर्ण_अगर /* __ISYS_DMA_GLOBAL_H_INCLUDED__ */
