<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Crypto driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित __CHCR_CORE_H__
#घोषणा __CHCR_CORE_H__

#समावेश <crypto/algapi.h>
#समावेश <net/tls.h>
#समावेश "t4_hw.h"
#समावेश "cxgb4.h"
#समावेश "t4_msg.h"
#समावेश "cxgb4_uld.h"

#घोषणा DRV_MODULE_NAME "chcr"
#घोषणा DRV_DESC "Chelsio T6 Crypto Co-processor Driver"

#घोषणा MAX_PENDING_REQ_TO_HW 20
#घोषणा CHCR_TEST_RESPONSE_TIMEOUT 1000
#घोषणा WQ_DETACH_TM	(msecs_to_jअगरfies(50))
#घोषणा PAD_ERROR_BIT		1
#घोषणा CHK_PAD_ERR_BIT(x)	(((x) >> PAD_ERROR_BIT) & 1)

#घोषणा MAC_ERROR_BIT		0
#घोषणा CHK_MAC_ERR_BIT(x)	(((x) >> MAC_ERROR_BIT) & 1)
#घोषणा MAX_SALT                4
#घोषणा CIP_WR_MIN_LEN (माप(काष्ठा chcr_wr) + \
		    माप(काष्ठा cpl_rx_phys_dsgl) + \
		    माप(काष्ठा ulptx_sgl) + 16) //IV

#घोषणा HASH_WR_MIN_LEN (माप(काष्ठा chcr_wr) + \
			DUMMY_BYTES + \
		    माप(काष्ठा ulptx_sgl))
काष्ठा uld_ctx;

काष्ठा _key_ctx अणु
	__be32 ctx_hdr;
	u8 salt[MAX_SALT];
	__be64 iv_to_auth;
	अचिन्हित अक्षर key[];
पूर्ण;

#घोषणा WQ_RETRY	5
काष्ठा chcr_driver_data अणु
	काष्ठा list_head act_dev;
	काष्ठा list_head inact_dev;
	atomic_t dev_count;
	काष्ठा mutex drv_mutex;
	काष्ठा uld_ctx *last_dev;
पूर्ण;

क्रमागत chcr_state अणु
	CHCR_INIT = 0,
	CHCR_ATTACH,
	CHCR_DETACH,
पूर्ण;
काष्ठा chcr_wr अणु
	काष्ठा fw_crypto_lookaside_wr wreq;
	काष्ठा ulp_txpkt ulptx;
	काष्ठा ulptx_idata sc_imm;
	काष्ठा cpl_tx_sec_pdu sec_cpl;
	काष्ठा _key_ctx key_ctx;
पूर्ण;

काष्ठा chcr_dev अणु
	spinlock_t lock_chcr_dev;
	क्रमागत chcr_state state;
	atomic_t inflight;
	पूर्णांक wqretry;
	काष्ठा delayed_work detach_work;
	काष्ठा completion detach_comp;
पूर्ण;

काष्ठा uld_ctx अणु
	काष्ठा list_head entry;
	काष्ठा cxgb4_lld_info lldi;
	काष्ठा chcr_dev dev;
पूर्ण;

/*
 *      sgl_len - calculates the size of an SGL of the given capacity
 *      @n: the number of SGL entries
 *      Calculates the number of flits needed क्रम a scatter/gather list that
 *      can hold the given number of entries.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sgl_len(अचिन्हित पूर्णांक n)
अणु
	n--;
	वापस (3 * n) / 2 + (n & 1) + 2;
पूर्ण

अटल अंतरभूत व्योम *padap(काष्ठा chcr_dev *dev)
अणु
	काष्ठा uld_ctx *u_ctx = container_of(dev, काष्ठा uld_ctx, dev);

	वापस pci_get_drvdata(u_ctx->lldi.pdev);
पूर्ण

काष्ठा uld_ctx *assign_chcr_device(व्योम);
पूर्णांक chcr_send_wr(काष्ठा sk_buff *skb);
पूर्णांक start_crypto(व्योम);
पूर्णांक stop_crypto(व्योम);
पूर्णांक chcr_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
			स्थिर काष्ठा pkt_gl *pgl);
पूर्णांक chcr_uld_tx_handler(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक chcr_handle_resp(काष्ठा crypto_async_request *req, अचिन्हित अक्षर *input,
		     पूर्णांक err);
#पूर्ण_अगर /* __CHCR_CORE_H__ */
