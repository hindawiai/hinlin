<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#अगर_अघोषित __ALTERA_MSGDMA_H__
#घोषणा __ALTERA_MSGDMA_H__

व्योम msgdma_reset(काष्ठा altera_tse_निजी *);
व्योम msgdma_enable_txirq(काष्ठा altera_tse_निजी *);
व्योम msgdma_enable_rxirq(काष्ठा altera_tse_निजी *);
व्योम msgdma_disable_rxirq(काष्ठा altera_tse_निजी *);
व्योम msgdma_disable_txirq(काष्ठा altera_tse_निजी *);
व्योम msgdma_clear_rxirq(काष्ठा altera_tse_निजी *);
व्योम msgdma_clear_txirq(काष्ठा altera_tse_निजी *);
u32 msgdma_tx_completions(काष्ठा altera_tse_निजी *);
व्योम msgdma_add_rx_desc(काष्ठा altera_tse_निजी *, काष्ठा tse_buffer *);
पूर्णांक msgdma_tx_buffer(काष्ठा altera_tse_निजी *, काष्ठा tse_buffer *);
u32 msgdma_rx_status(काष्ठा altera_tse_निजी *);
पूर्णांक msgdma_initialize(काष्ठा altera_tse_निजी *);
व्योम msgdma_uninitialize(काष्ठा altera_tse_निजी *);
व्योम msgdma_start_rxdma(काष्ठा altera_tse_निजी *);

#पूर्ण_अगर /*  __ALTERA_MSGDMA_H__ */
