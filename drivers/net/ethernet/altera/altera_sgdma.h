<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#अगर_अघोषित __ALTERA_SGDMA_H__
#घोषणा __ALTERA_SGDMA_H__

व्योम sgdma_reset(काष्ठा altera_tse_निजी *);
व्योम sgdma_enable_txirq(काष्ठा altera_tse_निजी *);
व्योम sgdma_enable_rxirq(काष्ठा altera_tse_निजी *);
व्योम sgdma_disable_rxirq(काष्ठा altera_tse_निजी *);
व्योम sgdma_disable_txirq(काष्ठा altera_tse_निजी *);
व्योम sgdma_clear_rxirq(काष्ठा altera_tse_निजी *);
व्योम sgdma_clear_txirq(काष्ठा altera_tse_निजी *);
पूर्णांक sgdma_tx_buffer(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *);
u32 sgdma_tx_completions(काष्ठा altera_tse_निजी *);
व्योम sgdma_add_rx_desc(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *);
व्योम sgdma_status(काष्ठा altera_tse_निजी *);
u32 sgdma_rx_status(काष्ठा altera_tse_निजी *);
पूर्णांक sgdma_initialize(काष्ठा altera_tse_निजी *);
व्योम sgdma_uninitialize(काष्ठा altera_tse_निजी *);
व्योम sgdma_start_rxdma(काष्ठा altera_tse_निजी *);

#पूर्ण_अगर /*  __ALTERA_SGDMA_H__ */
