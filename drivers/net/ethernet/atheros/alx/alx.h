<शैली गुरु>
/*
 * Copyright (c) 2013 Johannes Berg <johannes@sipsolutions.net>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _ALX_H_
#घोषणा _ALX_H_

#समावेश <linux/types.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश "hw.h"

#घोषणा ALX_WATCHDOG_TIME   (5 * HZ)

काष्ठा alx_buffer अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(size);
पूर्ण;

काष्ठा alx_rx_queue अणु
	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	काष्ठा alx_napi *np;

	काष्ठा alx_rrd *rrd;
	dma_addr_t rrd_dma;

	काष्ठा alx_rfd *rfd;
	dma_addr_t rfd_dma;

	काष्ठा alx_buffer *bufs;

	u16 count;
	u16 ग_लिखो_idx, पढ़ो_idx;
	u16 rrd_पढ़ो_idx;
	u16 queue_idx;
पूर्ण;
#घोषणा ALX_RX_ALLOC_THRESH	32

काष्ठा alx_tx_queue अणु
	काष्ठा net_device *netdev;
	काष्ठा device *dev;

	काष्ठा alx_txd *tpd;
	dma_addr_t tpd_dma;

	काष्ठा alx_buffer *bufs;

	u16 count;
	u16 ग_लिखो_idx, पढ़ो_idx;
	u16 queue_idx;
	u16 p_reg, c_reg;
पूर्ण;

#घोषणा ALX_DEFAULT_TX_WORK 128

क्रमागत alx_device_quirks अणु
	ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG = BIT(0),
पूर्ण;

काष्ठा alx_napi अणु
	काष्ठा napi_काष्ठा	napi;
	काष्ठा alx_priv		*alx;
	काष्ठा alx_rx_queue	*rxq;
	काष्ठा alx_tx_queue	*txq;
	पूर्णांक			vec_idx;
	u32			vec_mask;
	अक्षर			irq_lbl[IFNAMSIZ + 8];
पूर्ण;

#घोषणा ALX_MAX_NAPIS 8

काष्ठा alx_priv अणु
	काष्ठा net_device *dev;

	काष्ठा alx_hw hw;

	/* msi-x vectors */
	पूर्णांक num_vec;

	/* all descriptor memory */
	काष्ठा अणु
		dma_addr_t dma;
		व्योम *virt;
		अचिन्हित पूर्णांक size;
	पूर्ण descmem;

	काष्ठा alx_napi *qnapi[ALX_MAX_NAPIS];
	पूर्णांक num_txq;
	पूर्णांक num_rxq;
	पूर्णांक num_napi;

	/* protect पूर्णांक_mask updates */
	spinlock_t irq_lock;
	u32 पूर्णांक_mask;

	अचिन्हित पूर्णांक tx_ringsz;
	अचिन्हित पूर्णांक rx_ringsz;
	अचिन्हित पूर्णांक rxbuf_size;

	काष्ठा work_काष्ठा link_check_wk;
	काष्ठा work_काष्ठा reset_wk;

	u16 msg_enable;

	/* protects hw.stats */
	spinlock_t stats_lock;
पूर्ण;

बाह्य स्थिर काष्ठा ethtool_ops alx_ethtool_ops;

#पूर्ण_अगर
