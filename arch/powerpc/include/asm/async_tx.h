<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 DENX Software Engineering.
 *
 * Author: Yuri Tikhonov <yur@emcraft.com>
 */
#अगर_अघोषित _ASM_POWERPC_ASYNC_TX_H_
#घोषणा _ASM_POWERPC_ASYNC_TX_H_

#अगर defined(CONFIG_440SPe) || defined(CONFIG_440SP)
बाह्य काष्ठा dma_chan *
ppc440spe_async_tx_find_best_channel(क्रमागत dma_transaction_type cap,
	काष्ठा page **dst_lst, पूर्णांक dst_cnt, काष्ठा page **src_lst,
	पूर्णांक src_cnt, माप_प्रकार src_sz);

#घोषणा async_tx_find_channel(dep, cap, dst_lst, dst_cnt, src_lst, \
			      src_cnt, src_sz) \
	ppc440spe_async_tx_find_best_channel(cap, dst_lst, dst_cnt, src_lst, \
					     src_cnt, src_sz)
#अन्यथा

#घोषणा async_tx_find_channel(dep, type, dst, dst_count, src, src_count, len) \
	__async_tx_find_channel(dep, type)

काष्ठा dma_chan *
__async_tx_find_channel(काष्ठा async_submit_ctl *submit,
			क्रमागत dma_transaction_type tx_type);

#पूर्ण_अगर

#पूर्ण_अगर
