<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA v0 core
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#अगर_अघोषित _DW_EDMA_V0_CORE_H
#घोषणा _DW_EDMA_V0_CORE_H

#समावेश <linux/dma/edma.h>

/* eDMA management callbacks */
व्योम dw_edma_v0_core_off(काष्ठा dw_edma *chan);
u16 dw_edma_v0_core_ch_count(काष्ठा dw_edma *chan, क्रमागत dw_edma_dir dir);
क्रमागत dma_status dw_edma_v0_core_ch_status(काष्ठा dw_edma_chan *chan);
व्योम dw_edma_v0_core_clear_करोne_पूर्णांक(काष्ठा dw_edma_chan *chan);
व्योम dw_edma_v0_core_clear_पात_पूर्णांक(काष्ठा dw_edma_chan *chan);
u32 dw_edma_v0_core_status_करोne_पूर्णांक(काष्ठा dw_edma *chan, क्रमागत dw_edma_dir dir);
u32 dw_edma_v0_core_status_पात_पूर्णांक(काष्ठा dw_edma *chan, क्रमागत dw_edma_dir dir);
व्योम dw_edma_v0_core_start(काष्ठा dw_edma_chunk *chunk, bool first);
पूर्णांक dw_edma_v0_core_device_config(काष्ठा dw_edma_chan *chan);
/* eDMA debug fs callbacks */
व्योम dw_edma_v0_core_debugfs_on(काष्ठा dw_edma_chip *chip);
व्योम dw_edma_v0_core_debugfs_off(काष्ठा dw_edma_chip *chip);

#पूर्ण_अगर /* _DW_EDMA_V0_CORE_H */
