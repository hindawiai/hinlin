<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Xilinx DMA Engine drivers support header file
 *
 * Copyright (C) 2010-2014 Xilinx, Inc. All rights reserved.
 */

#अगर_अघोषित __DMA_XILINX_DMA_H
#घोषणा __DMA_XILINX_DMA_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>

/**
 * काष्ठा xilinx_vdma_config - VDMA Configuration काष्ठाure
 * @frm_dly: Frame delay
 * @gen_lock: Whether in gen-lock mode
 * @master: Master that it syncs to
 * @frm_cnt_en: Enable frame count enable
 * @park: Whether wants to park
 * @park_frm: Frame to park on
 * @coalesc: Interrupt coalescing threshold
 * @delay: Delay counter
 * @reset: Reset Channel
 * @ext_fsync: External Frame Sync source
 * @vflip_en:  Vertical Flip enable
 */
काष्ठा xilinx_vdma_config अणु
	पूर्णांक frm_dly;
	पूर्णांक gen_lock;
	पूर्णांक master;
	पूर्णांक frm_cnt_en;
	पूर्णांक park;
	पूर्णांक park_frm;
	पूर्णांक coalesc;
	पूर्णांक delay;
	पूर्णांक reset;
	पूर्णांक ext_fsync;
	bool vflip_en;
पूर्ण;

पूर्णांक xilinx_vdma_channel_set_config(काष्ठा dma_chan *dchan,
					काष्ठा xilinx_vdma_config *cfg);

#पूर्ण_अगर
