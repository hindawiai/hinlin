<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <net/vxlan.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल अचिन्हित पूर्णांक ecc_sec_info_threshold = 10;
अटल अचिन्हित पूर्णांक ecc_sec_warn_threshold = 10000;
अटल अचिन्हित पूर्णांक ecc_sec_period = 600;
अटल अचिन्हित पूर्णांक ecc_ded_threshold = 2;
अटल अचिन्हित पूर्णांक ecc_ded_period = 600;

#अगर_घोषित CONFIG_AMD_XGBE_HAVE_ECC
/* Only expose the ECC parameters अगर supported */
module_param(ecc_sec_info_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(ecc_sec_info_threshold,
		 " ECC corrected error informational threshold setting");

module_param(ecc_sec_warn_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(ecc_sec_warn_threshold,
		 " ECC corrected error warning threshold setting");

module_param(ecc_sec_period, uपूर्णांक, 0644);
MODULE_PARM_DESC(ecc_sec_period, " ECC corrected error period (in seconds)");

module_param(ecc_ded_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(ecc_ded_threshold, " ECC detected error threshold setting");

module_param(ecc_ded_period, uपूर्णांक, 0644);
MODULE_PARM_DESC(ecc_ded_period, " ECC detected error period (in seconds)");
#पूर्ण_अगर

अटल पूर्णांक xgbe_one_poll(काष्ठा napi_काष्ठा *, पूर्णांक);
अटल पूर्णांक xgbe_all_poll(काष्ठा napi_काष्ठा *, पूर्णांक);
अटल व्योम xgbe_stop(काष्ठा xgbe_prv_data *);

अटल व्योम *xgbe_alloc_node(माप_प्रकार size, पूर्णांक node)
अणु
	व्योम *mem;

	mem = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!mem)
		mem = kzalloc(size, GFP_KERNEL);

	वापस mem;
पूर्ण

अटल व्योम xgbe_मुक्त_channels(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->channel); i++) अणु
		अगर (!pdata->channel[i])
			जारी;

		kमुक्त(pdata->channel[i]->rx_ring);
		kमुक्त(pdata->channel[i]->tx_ring);
		kमुक्त(pdata->channel[i]);

		pdata->channel[i] = शून्य;
	पूर्ण

	pdata->channel_count = 0;
पूर्ण

अटल पूर्णांक xgbe_alloc_channels(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	काष्ठा xgbe_ring *ring;
	अचिन्हित पूर्णांक count, i;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक node;

	count = max_t(अचिन्हित पूर्णांक, pdata->tx_ring_count, pdata->rx_ring_count);
	क्रम (i = 0; i < count; i++) अणु
		/* Attempt to use a CPU on the node the device is on */
		cpu = cpumask_local_spपढ़ो(i, dev_to_node(pdata->dev));

		/* Set the allocation node based on the वापसed CPU */
		node = cpu_to_node(cpu);

		channel = xgbe_alloc_node(माप(*channel), node);
		अगर (!channel)
			जाओ err_mem;
		pdata->channel[i] = channel;

		snम_लिखो(channel->name, माप(channel->name), "channel-%u", i);
		channel->pdata = pdata;
		channel->queue_index = i;
		channel->dma_regs = pdata->xgmac_regs + DMA_CH_BASE +
				    (DMA_CH_INC * i);
		channel->node = node;
		cpumask_set_cpu(cpu, &channel->affinity_mask);

		अगर (pdata->per_channel_irq)
			channel->dma_irq = pdata->channel_irq[i];

		अगर (i < pdata->tx_ring_count) अणु
			ring = xgbe_alloc_node(माप(*ring), node);
			अगर (!ring)
				जाओ err_mem;

			spin_lock_init(&ring->lock);
			ring->node = node;

			channel->tx_ring = ring;
		पूर्ण

		अगर (i < pdata->rx_ring_count) अणु
			ring = xgbe_alloc_node(माप(*ring), node);
			अगर (!ring)
				जाओ err_mem;

			spin_lock_init(&ring->lock);
			ring->node = node;

			channel->rx_ring = ring;
		पूर्ण

		netअगर_dbg(pdata, drv, pdata->netdev,
			  "%s: cpu=%u, node=%d\n", channel->name, cpu, node);

		netअगर_dbg(pdata, drv, pdata->netdev,
			  "%s: dma_regs=%p, dma_irq=%d, tx=%p, rx=%p\n",
			  channel->name, channel->dma_regs, channel->dma_irq,
			  channel->tx_ring, channel->rx_ring);
	पूर्ण

	pdata->channel_count = count;

	वापस 0;

err_mem:
	xgbe_मुक्त_channels(pdata);

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xgbe_tx_avail_desc(काष्ठा xgbe_ring *ring)
अणु
	वापस (ring->rdesc_count - (ring->cur - ring->dirty));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xgbe_rx_dirty_desc(काष्ठा xgbe_ring *ring)
अणु
	वापस (ring->cur - ring->dirty);
पूर्ण

अटल पूर्णांक xgbe_maybe_stop_tx_queue(काष्ठा xgbe_channel *channel,
				    काष्ठा xgbe_ring *ring, अचिन्हित पूर्णांक count)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;

	अगर (count > xgbe_tx_avail_desc(ring)) अणु
		netअगर_info(pdata, drv, pdata->netdev,
			   "Tx queue stopped, not enough descriptors available\n");
		netअगर_stop_subqueue(pdata->netdev, channel->queue_index);
		ring->tx.queue_stopped = 1;

		/* If we haven't notअगरied the hardware because of xmit_more
		 * support, tell it now
		 */
		अगर (ring->tx.xmit_more)
			pdata->hw_अगर.tx_start_xmit(channel, ring);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_calc_rx_buf_size(काष्ठा net_device *netdev, अचिन्हित पूर्णांक mtu)
अणु
	अचिन्हित पूर्णांक rx_buf_size;

	rx_buf_size = mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	rx_buf_size = clamp_val(rx_buf_size, XGBE_RX_MIN_BUF_SIZE, PAGE_SIZE);

	rx_buf_size = (rx_buf_size + XGBE_RX_BUF_ALIGN - 1) &
		      ~(XGBE_RX_BUF_ALIGN - 1);

	वापस rx_buf_size;
पूर्ण

अटल व्योम xgbe_enable_rx_tx_पूर्णांक(काष्ठा xgbe_prv_data *pdata,
				  काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	क्रमागत xgbe_पूर्णांक पूर्णांक_id;

	अगर (channel->tx_ring && channel->rx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_TI_RI;
	अन्यथा अगर (channel->tx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_TI;
	अन्यथा अगर (channel->rx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_RI;
	अन्यथा
		वापस;

	hw_अगर->enable_पूर्णांक(channel, पूर्णांक_id);
पूर्ण

अटल व्योम xgbe_enable_rx_tx_पूर्णांकs(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++)
		xgbe_enable_rx_tx_पूर्णांक(pdata, pdata->channel[i]);
पूर्ण

अटल व्योम xgbe_disable_rx_tx_पूर्णांक(काष्ठा xgbe_prv_data *pdata,
				   काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	क्रमागत xgbe_पूर्णांक पूर्णांक_id;

	अगर (channel->tx_ring && channel->rx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_TI_RI;
	अन्यथा अगर (channel->tx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_TI;
	अन्यथा अगर (channel->rx_ring)
		पूर्णांक_id = XGMAC_INT_DMA_CH_SR_RI;
	अन्यथा
		वापस;

	hw_अगर->disable_पूर्णांक(channel, पूर्णांक_id);
पूर्ण

अटल व्योम xgbe_disable_rx_tx_पूर्णांकs(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++)
		xgbe_disable_rx_tx_पूर्णांक(pdata, pdata->channel[i]);
पूर्ण

अटल bool xgbe_ecc_sec(काष्ठा xgbe_prv_data *pdata, अचिन्हित दीर्घ *period,
			 अचिन्हित पूर्णांक *count, स्थिर अक्षर *area)
अणु
	अगर (समय_beक्रमe(jअगरfies, *period)) अणु
		(*count)++;
	पूर्ण अन्यथा अणु
		*period = jअगरfies + (ecc_sec_period * HZ);
		*count = 1;
	पूर्ण

	अगर (*count > ecc_sec_info_threshold)
		dev_warn_once(pdata->dev,
			      "%s ECC corrected errors exceed informational threshold\n",
			      area);

	अगर (*count > ecc_sec_warn_threshold) अणु
		dev_warn_once(pdata->dev,
			      "%s ECC corrected errors exceed warning threshold\n",
			      area);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool xgbe_ecc_ded(काष्ठा xgbe_prv_data *pdata, अचिन्हित दीर्घ *period,
			 अचिन्हित पूर्णांक *count, स्थिर अक्षर *area)
अणु
	अगर (समय_beक्रमe(jअगरfies, *period)) अणु
		(*count)++;
	पूर्ण अन्यथा अणु
		*period = jअगरfies + (ecc_ded_period * HZ);
		*count = 1;
	पूर्ण

	अगर (*count > ecc_ded_threshold) अणु
		netdev_alert(pdata->netdev,
			     "%s ECC detected errors exceed threshold\n",
			     area);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम xgbe_ecc_isr_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xgbe_prv_data *pdata = from_tasklet(pdata, t, tasklet_ecc);
	अचिन्हित पूर्णांक ecc_isr;
	bool stop = false;

	/* Mask status with only the पूर्णांकerrupts we care about */
	ecc_isr = XP_IOREAD(pdata, XP_ECC_ISR);
	ecc_isr &= XP_IOREAD(pdata, XP_ECC_IER);
	netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "ECC_ISR=%#010x\n", ecc_isr);

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, TX_DED)) अणु
		stop |= xgbe_ecc_ded(pdata, &pdata->tx_ded_period,
				     &pdata->tx_ded_count, "TX fifo");
	पूर्ण

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, RX_DED)) अणु
		stop |= xgbe_ecc_ded(pdata, &pdata->rx_ded_period,
				     &pdata->rx_ded_count, "RX fifo");
	पूर्ण

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, DESC_DED)) अणु
		stop |= xgbe_ecc_ded(pdata, &pdata->desc_ded_period,
				     &pdata->desc_ded_count,
				     "descriptor cache");
	पूर्ण

	अगर (stop) अणु
		pdata->hw_अगर.disable_ecc_ded(pdata);
		schedule_work(&pdata->stopdev_work);
		जाओ out;
	पूर्ण

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, TX_SEC)) अणु
		अगर (xgbe_ecc_sec(pdata, &pdata->tx_sec_period,
				 &pdata->tx_sec_count, "TX fifo"))
			pdata->hw_अगर.disable_ecc_sec(pdata, XGBE_ECC_SEC_TX);
	पूर्ण

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, RX_SEC))
		अगर (xgbe_ecc_sec(pdata, &pdata->rx_sec_period,
				 &pdata->rx_sec_count, "RX fifo"))
			pdata->hw_अगर.disable_ecc_sec(pdata, XGBE_ECC_SEC_RX);

	अगर (XP_GET_BITS(ecc_isr, XP_ECC_ISR, DESC_SEC))
		अगर (xgbe_ecc_sec(pdata, &pdata->desc_sec_period,
				 &pdata->desc_sec_count, "descriptor cache"))
			pdata->hw_अगर.disable_ecc_sec(pdata, XGBE_ECC_SEC_DESC);

out:
	/* Clear all ECC पूर्णांकerrupts */
	XP_IOWRITE(pdata, XP_ECC_ISR, ecc_isr);

	/* Reissue पूर्णांकerrupt अगर status is not clear */
	अगर (pdata->vdata->irq_reissue_support)
		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 1);
पूर्ण

अटल irqवापस_t xgbe_ecc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgbe_prv_data *pdata = data;

	अगर (pdata->isr_as_tasklet)
		tasklet_schedule(&pdata->tasklet_ecc);
	अन्यथा
		xgbe_ecc_isr_task(&pdata->tasklet_ecc);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xgbe_isr_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xgbe_prv_data *pdata = from_tasklet(pdata, t, tasklet_dev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक dma_isr, dma_ch_isr;
	अचिन्हित पूर्णांक mac_isr, mac_tssr, mac_mdioisr;
	अचिन्हित पूर्णांक i;

	/* The DMA पूर्णांकerrupt status रेजिस्टर also reports MAC and MTL
	 * पूर्णांकerrupts. So क्रम polling mode, we just need to check क्रम
	 * this रेजिस्टर to be non-zero
	 */
	dma_isr = XGMAC_IOREAD(pdata, DMA_ISR);
	अगर (!dma_isr)
		जाओ isr_करोne;

	netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "DMA_ISR=%#010x\n", dma_isr);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!(dma_isr & (1 << i)))
			जारी;

		channel = pdata->channel[i];

		dma_ch_isr = XGMAC_DMA_IOREAD(channel, DMA_CH_SR);
		netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "DMA_CH%u_ISR=%#010x\n",
			  i, dma_ch_isr);

		/* The TI or RI पूर्णांकerrupt bits may still be set even अगर using
		 * per channel DMA पूर्णांकerrupts. Check to be sure those are not
		 * enabled beक्रमe using the निजी data napi काष्ठाure.
		 */
		अगर (!pdata->per_channel_irq &&
		    (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, TI) ||
		     XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RI))) अणु
			अगर (napi_schedule_prep(&pdata->napi)) अणु
				/* Disable Tx and Rx पूर्णांकerrupts */
				xgbe_disable_rx_tx_पूर्णांकs(pdata);

				/* Turn on polling */
				__napi_schedule(&pdata->napi);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Don't clear Rx/Tx status अगर करोing per channel DMA
			 * पूर्णांकerrupts, these will be cleared by the ISR क्रम
			 * per channel DMA पूर्णांकerrupts.
			 */
			XGMAC_SET_BITS(dma_ch_isr, DMA_CH_SR, TI, 0);
			XGMAC_SET_BITS(dma_ch_isr, DMA_CH_SR, RI, 0);
		पूर्ण

		अगर (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RBU))
			pdata->ext_stats.rx_buffer_unavailable++;

		/* Restart the device on a Fatal Bus Error */
		अगर (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, FBE))
			schedule_work(&pdata->restart_work);

		/* Clear पूर्णांकerrupt संकेतs */
		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_ch_isr);
	पूर्ण

	अगर (XGMAC_GET_BITS(dma_isr, DMA_ISR, MACIS)) अणु
		mac_isr = XGMAC_IOREAD(pdata, MAC_ISR);

		netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "MAC_ISR=%#010x\n",
			  mac_isr);

		अगर (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCTXIS))
			hw_अगर->tx_mmc_पूर्णांक(pdata);

		अगर (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCRXIS))
			hw_अगर->rx_mmc_पूर्णांक(pdata);

		अगर (XGMAC_GET_BITS(mac_isr, MAC_ISR, TSIS)) अणु
			mac_tssr = XGMAC_IOREAD(pdata, MAC_TSSR);

			netअगर_dbg(pdata, पूर्णांकr, pdata->netdev,
				  "MAC_TSSR=%#010x\n", mac_tssr);

			अगर (XGMAC_GET_BITS(mac_tssr, MAC_TSSR, TXTSC)) अणु
				/* Read Tx Timestamp to clear पूर्णांकerrupt */
				pdata->tx_tstamp =
					hw_अगर->get_tx_tstamp(pdata);
				queue_work(pdata->dev_workqueue,
					   &pdata->tx_tstamp_work);
			पूर्ण
		पूर्ण

		अगर (XGMAC_GET_BITS(mac_isr, MAC_ISR, SMI)) अणु
			mac_mdioisr = XGMAC_IOREAD(pdata, MAC_MDIOISR);

			netअगर_dbg(pdata, पूर्णांकr, pdata->netdev,
				  "MAC_MDIOISR=%#010x\n", mac_mdioisr);

			अगर (XGMAC_GET_BITS(mac_mdioisr, MAC_MDIOISR,
					   SNGLCOMPINT))
				complete(&pdata->mdio_complete);
		पूर्ण
	पूर्ण

isr_करोne:
	/* If there is not a separate AN irq, handle it here */
	अगर (pdata->dev_irq == pdata->an_irq)
		pdata->phy_अगर.an_isr(pdata);

	/* If there is not a separate ECC irq, handle it here */
	अगर (pdata->vdata->ecc_support && (pdata->dev_irq == pdata->ecc_irq))
		xgbe_ecc_isr_task(&pdata->tasklet_ecc);

	/* If there is not a separate I2C irq, handle it here */
	अगर (pdata->vdata->i2c_support && (pdata->dev_irq == pdata->i2c_irq))
		pdata->i2c_अगर.i2c_isr(pdata);

	/* Reissue पूर्णांकerrupt अगर status is not clear */
	अगर (pdata->vdata->irq_reissue_support) अणु
		अचिन्हित पूर्णांक reissue_mask;

		reissue_mask = 1 << 0;
		अगर (!pdata->per_channel_irq)
			reissue_mask |= 0xffff << 4;

		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, reissue_mask);
	पूर्ण
पूर्ण

अटल irqवापस_t xgbe_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgbe_prv_data *pdata = data;

	अगर (pdata->isr_as_tasklet)
		tasklet_schedule(&pdata->tasklet_dev);
	अन्यथा
		xgbe_isr_task(&pdata->tasklet_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xgbe_dma_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgbe_channel *channel = data;
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	अचिन्हित पूर्णांक dma_status;

	/* Per channel DMA पूर्णांकerrupts are enabled, so we use the per
	 * channel napi काष्ठाure and not the निजी data napi काष्ठाure
	 */
	अगर (napi_schedule_prep(&channel->napi)) अणु
		/* Disable Tx and Rx पूर्णांकerrupts */
		अगर (pdata->channel_irq_mode)
			xgbe_disable_rx_tx_पूर्णांक(pdata, channel);
		अन्यथा
			disable_irq_nosync(channel->dma_irq);

		/* Turn on polling */
		__napi_schedule_irqoff(&channel->napi);
	पूर्ण

	/* Clear Tx/Rx संकेतs */
	dma_status = 0;
	XGMAC_SET_BITS(dma_status, DMA_CH_SR, TI, 1);
	XGMAC_SET_BITS(dma_status, DMA_CH_SR, RI, 1);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xgbe_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा xgbe_channel *channel = from_समयr(channel, t, tx_समयr);
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा napi_काष्ठा *napi;

	DBGPR("-->xgbe_tx_timer\n");

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	अगर (napi_schedule_prep(napi)) अणु
		/* Disable Tx and Rx पूर्णांकerrupts */
		अगर (pdata->per_channel_irq)
			अगर (pdata->channel_irq_mode)
				xgbe_disable_rx_tx_पूर्णांक(pdata, channel);
			अन्यथा
				disable_irq_nosync(channel->dma_irq);
		अन्यथा
			xgbe_disable_rx_tx_पूर्णांकs(pdata);

		/* Turn on polling */
		__napi_schedule(napi);
	पूर्ण

	channel->tx_समयr_active = 0;

	DBGPR("<--xgbe_tx_timer\n");
पूर्ण

अटल व्योम xgbe_service(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   service_work);

	pdata->phy_अगर.phy_status(pdata);
पूर्ण

अटल व्योम xgbe_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा xgbe_prv_data *pdata = from_समयr(pdata, t, service_समयr);

	queue_work(pdata->dev_workqueue, &pdata->service_work);

	mod_समयr(&pdata->service_समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम xgbe_init_समयrs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	समयr_setup(&pdata->service_समयr, xgbe_service_समयr, 0);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		अगर (!channel->tx_ring)
			अवरोध;

		समयr_setup(&channel->tx_समयr, xgbe_tx_समयr, 0);
	पूर्ण
पूर्ण

अटल व्योम xgbe_start_समयrs(काष्ठा xgbe_prv_data *pdata)
अणु
	mod_समयr(&pdata->service_समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम xgbe_stop_समयrs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	del_समयr_sync(&pdata->service_समयr);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		अगर (!channel->tx_ring)
			अवरोध;

		del_समयr_sync(&channel->tx_समयr);
	पूर्ण
पूर्ण

व्योम xgbe_get_all_hw_features(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक mac_hfr0, mac_hfr1, mac_hfr2;
	काष्ठा xgbe_hw_features *hw_feat = &pdata->hw_feat;

	mac_hfr0 = XGMAC_IOREAD(pdata, MAC_HWF0R);
	mac_hfr1 = XGMAC_IOREAD(pdata, MAC_HWF1R);
	mac_hfr2 = XGMAC_IOREAD(pdata, MAC_HWF2R);

	स_रखो(hw_feat, 0, माप(*hw_feat));

	hw_feat->version = XGMAC_IOREAD(pdata, MAC_VR);

	/* Hardware feature रेजिस्टर 0 */
	hw_feat->gmii        = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, GMIISEL);
	hw_feat->vlhash      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, VLHASH);
	hw_feat->sma         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SMASEL);
	hw_feat->rwk         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RWKSEL);
	hw_feat->mgk         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MGKSEL);
	hw_feat->mmc         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MMCSEL);
	hw_feat->aoe         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, ARPOFFSEL);
	hw_feat->ts          = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSEL);
	hw_feat->eee         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, EEESEL);
	hw_feat->tx_coe      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TXCOESEL);
	hw_feat->rx_coe      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RXCOESEL);
	hw_feat->addn_mac    = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R,
					      ADDMACADRSEL);
	hw_feat->ts_src      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSTSSEL);
	hw_feat->sa_vlan_ins = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SAVLANINS);
	hw_feat->vxn         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, VXN);

	/* Hardware feature रेजिस्टर 1 */
	hw_feat->rx_fअगरo_size  = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						RXFIFOSIZE);
	hw_feat->tx_fअगरo_size  = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						TXFIFOSIZE);
	hw_feat->adv_ts_hi     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, ADVTHWORD);
	hw_feat->dma_width     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, ADDR64);
	hw_feat->dcb           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DCBEN);
	hw_feat->sph           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, SPHEN);
	hw_feat->tso           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, TSOEN);
	hw_feat->dma_debug     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DBGMEMA);
	hw_feat->rss           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, RSSEN);
	hw_feat->tc_cnt	       = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, NUMTC);
	hw_feat->hash_table_size = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  HASHTBLSZ);
	hw_feat->l3l4_filter_num = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  L3L4FNUM);

	/* Hardware feature रेजिस्टर 2 */
	hw_feat->rx_q_cnt     = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXQCNT);
	hw_feat->tx_q_cnt     = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXQCNT);
	hw_feat->rx_ch_cnt    = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXCHCNT);
	hw_feat->tx_ch_cnt    = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXCHCNT);
	hw_feat->pps_out_num  = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, PPSOUTNUM);
	hw_feat->aux_snap_num = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, AUXSNAPNUM);

	/* Translate the Hash Table size पूर्णांकo actual number */
	चयन (hw_feat->hash_table_size) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		hw_feat->hash_table_size = 64;
		अवरोध;
	हाल 2:
		hw_feat->hash_table_size = 128;
		अवरोध;
	हाल 3:
		hw_feat->hash_table_size = 256;
		अवरोध;
	पूर्ण

	/* Translate the address width setting पूर्णांकo actual number */
	चयन (hw_feat->dma_width) अणु
	हाल 0:
		hw_feat->dma_width = 32;
		अवरोध;
	हाल 1:
		hw_feat->dma_width = 40;
		अवरोध;
	हाल 2:
		hw_feat->dma_width = 48;
		अवरोध;
	शेष:
		hw_feat->dma_width = 32;
	पूर्ण

	/* The Queue, Channel and TC counts are zero based so increment them
	 * to get the actual number
	 */
	hw_feat->rx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->rx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;

	/* Translate the fअगरo sizes पूर्णांकo actual numbers */
	hw_feat->rx_fअगरo_size = 1 << (hw_feat->rx_fअगरo_size + 7);
	hw_feat->tx_fअगरo_size = 1 << (hw_feat->tx_fअगरo_size + 7);

	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "Hardware features:\n");

		/* Hardware feature रेजिस्टर 0 */
		dev_dbg(pdata->dev, "  1GbE support              : %s\n",
			hw_feat->gmii ? "yes" : "no");
		dev_dbg(pdata->dev, "  VLAN hash filter          : %s\n",
			hw_feat->vlhash ? "yes" : "no");
		dev_dbg(pdata->dev, "  MDIO interface            : %s\n",
			hw_feat->sma ? "yes" : "no");
		dev_dbg(pdata->dev, "  Wake-up packet support    : %s\n",
			hw_feat->rwk ? "yes" : "no");
		dev_dbg(pdata->dev, "  Magic packet support      : %s\n",
			hw_feat->mgk ? "yes" : "no");
		dev_dbg(pdata->dev, "  Management counters       : %s\n",
			hw_feat->mmc ? "yes" : "no");
		dev_dbg(pdata->dev, "  ARP offload               : %s\n",
			hw_feat->aoe ? "yes" : "no");
		dev_dbg(pdata->dev, "  IEEE 1588-2008 Timestamp  : %s\n",
			hw_feat->ts ? "yes" : "no");
		dev_dbg(pdata->dev, "  Energy Efficient Ethernet : %s\n",
			hw_feat->eee ? "yes" : "no");
		dev_dbg(pdata->dev, "  TX checksum offload       : %s\n",
			hw_feat->tx_coe ? "yes" : "no");
		dev_dbg(pdata->dev, "  RX checksum offload       : %s\n",
			hw_feat->rx_coe ? "yes" : "no");
		dev_dbg(pdata->dev, "  Additional MAC addresses  : %u\n",
			hw_feat->addn_mac);
		dev_dbg(pdata->dev, "  Timestamp source          : %s\n",
			(hw_feat->ts_src == 1) ? "internal" :
			(hw_feat->ts_src == 2) ? "external" :
			(hw_feat->ts_src == 3) ? "internal/external" : "n/a");
		dev_dbg(pdata->dev, "  SA/VLAN insertion         : %s\n",
			hw_feat->sa_vlan_ins ? "yes" : "no");
		dev_dbg(pdata->dev, "  VXLAN/NVGRE support       : %s\n",
			hw_feat->vxn ? "yes" : "no");

		/* Hardware feature रेजिस्टर 1 */
		dev_dbg(pdata->dev, "  RX fifo size              : %u\n",
			hw_feat->rx_fअगरo_size);
		dev_dbg(pdata->dev, "  TX fifo size              : %u\n",
			hw_feat->tx_fअगरo_size);
		dev_dbg(pdata->dev, "  IEEE 1588 high word       : %s\n",
			hw_feat->adv_ts_hi ? "yes" : "no");
		dev_dbg(pdata->dev, "  DMA width                 : %u\n",
			hw_feat->dma_width);
		dev_dbg(pdata->dev, "  Data Center Bridging      : %s\n",
			hw_feat->dcb ? "yes" : "no");
		dev_dbg(pdata->dev, "  Split header              : %s\n",
			hw_feat->sph ? "yes" : "no");
		dev_dbg(pdata->dev, "  TCP Segmentation Offload  : %s\n",
			hw_feat->tso ? "yes" : "no");
		dev_dbg(pdata->dev, "  Debug memory interface    : %s\n",
			hw_feat->dma_debug ? "yes" : "no");
		dev_dbg(pdata->dev, "  Receive Side Scaling      : %s\n",
			hw_feat->rss ? "yes" : "no");
		dev_dbg(pdata->dev, "  Traffic Class count       : %u\n",
			hw_feat->tc_cnt);
		dev_dbg(pdata->dev, "  Hash table size           : %u\n",
			hw_feat->hash_table_size);
		dev_dbg(pdata->dev, "  L3/L4 Filters             : %u\n",
			hw_feat->l3l4_filter_num);

		/* Hardware feature रेजिस्टर 2 */
		dev_dbg(pdata->dev, "  RX queue count            : %u\n",
			hw_feat->rx_q_cnt);
		dev_dbg(pdata->dev, "  TX queue count            : %u\n",
			hw_feat->tx_q_cnt);
		dev_dbg(pdata->dev, "  RX DMA channel count      : %u\n",
			hw_feat->rx_ch_cnt);
		dev_dbg(pdata->dev, "  TX DMA channel count      : %u\n",
			hw_feat->rx_ch_cnt);
		dev_dbg(pdata->dev, "  PPS outputs               : %u\n",
			hw_feat->pps_out_num);
		dev_dbg(pdata->dev, "  Auxiliary snapshot inputs : %u\n",
			hw_feat->aux_snap_num);
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_vxlan_set_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			       अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	pdata->vxlan_port = be16_to_cpu(ti->port);
	pdata->hw_अगर.enable_vxlan(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_vxlan_unset_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
				 अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	pdata->hw_अगर.disable_vxlan(pdata);
	pdata->vxlan_port = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info xgbe_udp_tunnels = अणु
	.set_port	= xgbe_vxlan_set_port,
	.unset_port	= xgbe_vxlan_unset_port,
	.flags		= UDP_TUNNEL_NIC_INFO_OPEN_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा udp_tunnel_nic_info *xgbe_get_udp_tunnel_info(व्योम)
अणु
	वापस &xgbe_udp_tunnels;
पूर्ण

अटल व्योम xgbe_napi_enable(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक add)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (pdata->per_channel_irq) अणु
		क्रम (i = 0; i < pdata->channel_count; i++) अणु
			channel = pdata->channel[i];
			अगर (add)
				netअगर_napi_add(pdata->netdev, &channel->napi,
					       xgbe_one_poll, NAPI_POLL_WEIGHT);

			napi_enable(&channel->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (add)
			netअगर_napi_add(pdata->netdev, &pdata->napi,
				       xgbe_all_poll, NAPI_POLL_WEIGHT);

		napi_enable(&pdata->napi);
	पूर्ण
पूर्ण

अटल व्योम xgbe_napi_disable(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक del)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (pdata->per_channel_irq) अणु
		क्रम (i = 0; i < pdata->channel_count; i++) अणु
			channel = pdata->channel[i];
			napi_disable(&channel->napi);

			अगर (del)
				netअगर_napi_del(&channel->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_disable(&pdata->napi);

		अगर (del)
			netअगर_napi_del(&pdata->napi);
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_request_irqs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	tasklet_setup(&pdata->tasklet_dev, xgbe_isr_task);
	tasklet_setup(&pdata->tasklet_ecc, xgbe_ecc_isr_task);

	ret = devm_request_irq(pdata->dev, pdata->dev_irq, xgbe_isr, 0,
			       netdev_name(netdev), pdata);
	अगर (ret) अणु
		netdev_alert(netdev, "error requesting irq %d\n",
			     pdata->dev_irq);
		वापस ret;
	पूर्ण

	अगर (pdata->vdata->ecc_support && (pdata->dev_irq != pdata->ecc_irq)) अणु
		ret = devm_request_irq(pdata->dev, pdata->ecc_irq, xgbe_ecc_isr,
				       0, pdata->ecc_name, pdata);
		अगर (ret) अणु
			netdev_alert(netdev, "error requesting ecc irq %d\n",
				     pdata->ecc_irq);
			जाओ err_dev_irq;
		पूर्ण
	पूर्ण

	अगर (!pdata->per_channel_irq)
		वापस 0;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		snम_लिखो(channel->dma_irq_name,
			 माप(channel->dma_irq_name) - 1,
			 "%s-TxRx-%u", netdev_name(netdev),
			 channel->queue_index);

		ret = devm_request_irq(pdata->dev, channel->dma_irq,
				       xgbe_dma_isr, 0,
				       channel->dma_irq_name, channel);
		अगर (ret) अणु
			netdev_alert(netdev, "error requesting irq %d\n",
				     channel->dma_irq);
			जाओ err_dma_irq;
		पूर्ण

		irq_set_affinity_hपूर्णांक(channel->dma_irq,
				      &channel->affinity_mask);
	पूर्ण

	वापस 0;

err_dma_irq:
	/* Using an अचिन्हित पूर्णांक, 'i' will go to अच_पूर्णांक_उच्च and निकास */
	क्रम (i--; i < pdata->channel_count; i--) अणु
		channel = pdata->channel[i];

		irq_set_affinity_hपूर्णांक(channel->dma_irq, शून्य);
		devm_मुक्त_irq(pdata->dev, channel->dma_irq, channel);
	पूर्ण

	अगर (pdata->vdata->ecc_support && (pdata->dev_irq != pdata->ecc_irq))
		devm_मुक्त_irq(pdata->dev, pdata->ecc_irq, pdata);

err_dev_irq:
	devm_मुक्त_irq(pdata->dev, pdata->dev_irq, pdata);

	वापस ret;
पूर्ण

अटल व्योम xgbe_मुक्त_irqs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	devm_मुक्त_irq(pdata->dev, pdata->dev_irq, pdata);

	अगर (pdata->vdata->ecc_support && (pdata->dev_irq != pdata->ecc_irq))
		devm_मुक्त_irq(pdata->dev, pdata->ecc_irq, pdata);

	अगर (!pdata->per_channel_irq)
		वापस;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];

		irq_set_affinity_hपूर्णांक(channel->dma_irq, शून्य);
		devm_मुक्त_irq(pdata->dev, channel->dma_irq, channel);
	पूर्ण
पूर्ण

व्योम xgbe_init_tx_coalesce(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;

	DBGPR("-->xgbe_init_tx_coalesce\n");

	pdata->tx_usecs = XGMAC_INIT_DMA_TX_USECS;
	pdata->tx_frames = XGMAC_INIT_DMA_TX_FRAMES;

	hw_अगर->config_tx_coalesce(pdata);

	DBGPR("<--xgbe_init_tx_coalesce\n");
पूर्ण

व्योम xgbe_init_rx_coalesce(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;

	DBGPR("-->xgbe_init_rx_coalesce\n");

	pdata->rx_riwt = hw_अगर->usec_to_riwt(pdata, XGMAC_INIT_DMA_RX_USECS);
	pdata->rx_usecs = XGMAC_INIT_DMA_RX_USECS;
	pdata->rx_frames = XGMAC_INIT_DMA_RX_FRAMES;

	hw_अगर->config_rx_coalesce(pdata);

	DBGPR("<--xgbe_init_rx_coalesce\n");
पूर्ण

अटल व्योम xgbe_मुक्त_tx_data(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा xgbe_ring *ring;
	काष्ठा xgbe_ring_data *rdata;
	अचिन्हित पूर्णांक i, j;

	DBGPR("-->xgbe_free_tx_data\n");

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		ring = pdata->channel[i]->tx_ring;
		अगर (!ring)
			अवरोध;

		क्रम (j = 0; j < ring->rdesc_count; j++) अणु
			rdata = XGBE_GET_DESC_DATA(ring, j);
			desc_अगर->unmap_rdata(pdata, rdata);
		पूर्ण
	पूर्ण

	DBGPR("<--xgbe_free_tx_data\n");
पूर्ण

अटल व्योम xgbe_मुक्त_rx_data(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा xgbe_ring *ring;
	काष्ठा xgbe_ring_data *rdata;
	अचिन्हित पूर्णांक i, j;

	DBGPR("-->xgbe_free_rx_data\n");

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		ring = pdata->channel[i]->rx_ring;
		अगर (!ring)
			अवरोध;

		क्रम (j = 0; j < ring->rdesc_count; j++) अणु
			rdata = XGBE_GET_DESC_DATA(ring, j);
			desc_अगर->unmap_rdata(pdata, rdata);
		पूर्ण
	पूर्ण

	DBGPR("<--xgbe_free_rx_data\n");
पूर्ण

अटल पूर्णांक xgbe_phy_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	pdata->phy_link = -1;
	pdata->phy_speed = SPEED_UNKNOWN;

	वापस pdata->phy_अगर.phy_reset(pdata);
पूर्ण

पूर्णांक xgbe_घातerकरोwn(काष्ठा net_device *netdev, अचिन्हित पूर्णांक caller)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	अचिन्हित दीर्घ flags;

	DBGPR("-->xgbe_powerdown\n");

	अगर (!netअगर_running(netdev) ||
	    (caller == XGMAC_IOCTL_CONTEXT && pdata->घातer_करोwn)) अणु
		netdev_alert(netdev, "Device is already powered down\n");
		DBGPR("<--xgbe_powerdown\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pdata->lock, flags);

	अगर (caller == XGMAC_DRIVER_CONTEXT)
		netअगर_device_detach(netdev);

	netअगर_tx_stop_all_queues(netdev);

	xgbe_stop_समयrs(pdata);
	flush_workqueue(pdata->dev_workqueue);

	hw_अगर->घातerकरोwn_tx(pdata);
	hw_अगर->घातerकरोwn_rx(pdata);

	xgbe_napi_disable(pdata, 0);

	pdata->घातer_करोwn = 1;

	spin_unlock_irqrestore(&pdata->lock, flags);

	DBGPR("<--xgbe_powerdown\n");

	वापस 0;
पूर्ण

पूर्णांक xgbe_घातerup(काष्ठा net_device *netdev, अचिन्हित पूर्णांक caller)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	अचिन्हित दीर्घ flags;

	DBGPR("-->xgbe_powerup\n");

	अगर (!netअगर_running(netdev) ||
	    (caller == XGMAC_IOCTL_CONTEXT && !pdata->घातer_करोwn)) अणु
		netdev_alert(netdev, "Device is already powered up\n");
		DBGPR("<--xgbe_powerup\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pdata->lock, flags);

	pdata->घातer_करोwn = 0;

	xgbe_napi_enable(pdata, 0);

	hw_अगर->घातerup_tx(pdata);
	hw_अगर->घातerup_rx(pdata);

	अगर (caller == XGMAC_DRIVER_CONTEXT)
		netअगर_device_attach(netdev);

	netअगर_tx_start_all_queues(netdev);

	xgbe_start_समयrs(pdata);

	spin_unlock_irqrestore(&pdata->lock, flags);

	DBGPR("<--xgbe_powerup\n");

	वापस 0;
पूर्ण

अटल व्योम xgbe_मुक्त_memory(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;

	/* Free the ring descriptors and buffers */
	desc_अगर->मुक्त_ring_resources(pdata);

	/* Free the channel and ring काष्ठाures */
	xgbe_मुक्त_channels(pdata);
पूर्ण

अटल पूर्णांक xgbe_alloc_memory(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret;

	अगर (pdata->new_tx_ring_count) अणु
		pdata->tx_ring_count = pdata->new_tx_ring_count;
		pdata->tx_q_count = pdata->tx_ring_count;
		pdata->new_tx_ring_count = 0;
	पूर्ण

	अगर (pdata->new_rx_ring_count) अणु
		pdata->rx_ring_count = pdata->new_rx_ring_count;
		pdata->new_rx_ring_count = 0;
	पूर्ण

	/* Calculate the Rx buffer size beक्रमe allocating rings */
	pdata->rx_buf_size = xgbe_calc_rx_buf_size(netdev, netdev->mtu);

	/* Allocate the channel and ring काष्ठाures */
	ret = xgbe_alloc_channels(pdata);
	अगर (ret)
		वापस ret;

	/* Allocate the ring descriptors and buffers */
	ret = desc_अगर->alloc_ring_resources(pdata);
	अगर (ret)
		जाओ err_channels;

	/* Initialize the service and Tx समयrs */
	xgbe_init_समयrs(pdata);

	वापस 0;

err_channels:
	xgbe_मुक्त_memory(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_start(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_phy_अगर *phy_अगर = &pdata->phy_अगर;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Set the number of queues */
	ret = netअगर_set_real_num_tx_queues(netdev, pdata->tx_ring_count);
	अगर (ret) अणु
		netdev_err(netdev, "error setting real tx queue count\n");
		वापस ret;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(netdev, pdata->rx_ring_count);
	अगर (ret) अणु
		netdev_err(netdev, "error setting real rx queue count\n");
		वापस ret;
	पूर्ण

	/* Set RSS lookup table data क्रम programming */
	क्रम (i = 0; i < XGBE_RSS_MAX_TABLE_SIZE; i++)
		XGMAC_SET_BITS(pdata->rss_table[i], MAC_RSSDR, DMCH,
			       i % pdata->rx_ring_count);

	ret = hw_अगर->init(pdata);
	अगर (ret)
		वापस ret;

	xgbe_napi_enable(pdata, 1);

	ret = xgbe_request_irqs(pdata);
	अगर (ret)
		जाओ err_napi;

	ret = phy_अगर->phy_start(pdata);
	अगर (ret)
		जाओ err_irqs;

	hw_अगर->enable_tx(pdata);
	hw_अगर->enable_rx(pdata);

	udp_tunnel_nic_reset_ntf(netdev);

	netअगर_tx_start_all_queues(netdev);

	xgbe_start_समयrs(pdata);
	queue_work(pdata->dev_workqueue, &pdata->service_work);

	clear_bit(XGBE_STOPPED, &pdata->dev_state);

	वापस 0;

err_irqs:
	xgbe_मुक्त_irqs(pdata);

err_napi:
	xgbe_napi_disable(pdata, 1);

	hw_अगर->निकास(pdata);

	वापस ret;
पूर्ण

अटल व्योम xgbe_stop(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_phy_अगर *phy_अगर = &pdata->phy_अगर;
	काष्ठा xgbe_channel *channel;
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_queue *txq;
	अचिन्हित पूर्णांक i;

	DBGPR("-->xgbe_stop\n");

	अगर (test_bit(XGBE_STOPPED, &pdata->dev_state))
		वापस;

	netअगर_tx_stop_all_queues(netdev);
	netअगर_carrier_off(pdata->netdev);

	xgbe_stop_समयrs(pdata);
	flush_workqueue(pdata->dev_workqueue);

	xgbe_vxlan_unset_port(netdev, 0, 0, शून्य);

	hw_अगर->disable_tx(pdata);
	hw_अगर->disable_rx(pdata);

	phy_अगर->phy_stop(pdata);

	xgbe_मुक्त_irqs(pdata);

	xgbe_napi_disable(pdata, 1);

	hw_अगर->निकास(pdata);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		अगर (!channel->tx_ring)
			जारी;

		txq = netdev_get_tx_queue(netdev, channel->queue_index);
		netdev_tx_reset_queue(txq);
	पूर्ण

	set_bit(XGBE_STOPPED, &pdata->dev_state);

	DBGPR("<--xgbe_stop\n");
पूर्ण

अटल व्योम xgbe_stopdev(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   stopdev_work);

	rtnl_lock();

	xgbe_stop(pdata);

	xgbe_मुक्त_tx_data(pdata);
	xgbe_मुक्त_rx_data(pdata);

	rtnl_unlock();

	netdev_alert(pdata->netdev, "device stopped\n");
पूर्ण

व्योम xgbe_full_restart_dev(काष्ठा xgbe_prv_data *pdata)
अणु
	/* If not running, "restart" will happen on खोलो */
	अगर (!netअगर_running(pdata->netdev))
		वापस;

	xgbe_stop(pdata);

	xgbe_मुक्त_memory(pdata);
	xgbe_alloc_memory(pdata);

	xgbe_start(pdata);
पूर्ण

व्योम xgbe_restart_dev(काष्ठा xgbe_prv_data *pdata)
अणु
	/* If not running, "restart" will happen on खोलो */
	अगर (!netअगर_running(pdata->netdev))
		वापस;

	xgbe_stop(pdata);

	xgbe_मुक्त_tx_data(pdata);
	xgbe_मुक्त_rx_data(pdata);

	xgbe_start(pdata);
पूर्ण

अटल व्योम xgbe_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   restart_work);

	rtnl_lock();

	xgbe_restart_dev(pdata);

	rtnl_unlock();
पूर्ण

अटल व्योम xgbe_tx_tstamp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   tx_tstamp_work);
	काष्ठा skb_shared_hwtstamps hwtstamps;
	u64 nsec;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->tstamp_lock, flags);
	अगर (!pdata->tx_tstamp_skb)
		जाओ unlock;

	अगर (pdata->tx_tstamp) अणु
		nsec = समयcounter_cyc2समय(&pdata->tstamp_tc,
					    pdata->tx_tstamp);

		स_रखो(&hwtstamps, 0, माप(hwtstamps));
		hwtstamps.hwtstamp = ns_to_kसमय(nsec);
		skb_tstamp_tx(pdata->tx_tstamp_skb, &hwtstamps);
	पूर्ण

	dev_kमुक्त_skb_any(pdata->tx_tstamp_skb);

	pdata->tx_tstamp_skb = शून्य;

unlock:
	spin_unlock_irqrestore(&pdata->tstamp_lock, flags);
पूर्ण

अटल पूर्णांक xgbe_get_hwtstamp_settings(काष्ठा xgbe_prv_data *pdata,
				      काष्ठा अगरreq *अगरreq)
अणु
	अगर (copy_to_user(अगरreq->अगरr_data, &pdata->tstamp_config,
			 माप(pdata->tstamp_config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_hwtstamp_settings(काष्ठा xgbe_prv_data *pdata,
				      काष्ठा अगरreq *अगरreq)
अणु
	काष्ठा hwtstamp_config config;
	अचिन्हित पूर्णांक mac_tscr;

	अगर (copy_from_user(&config, अगरreq->अगरr_data, माप(config)))
		वापस -EFAULT;

	अगर (config.flags)
		वापस -EINVAL;

	mac_tscr = 0;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		अवरोध;

	हाल HWTSTAMP_TX_ON:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;

	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENALL, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2, UDP, any kind of event packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		fallthrough;	/* to PTP v1, UDP, any kind of event packet */
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, SNAPTYPSEL, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2, UDP, Sync packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		fallthrough;	/* to PTP v1, UDP, Sync packet */
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2, UDP, Delay_req packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		fallthrough;	/* to PTP v1, UDP, Delay_req packet */
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSMSTRENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* 802.AS1, Ethernet, any kind of event packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, SNAPTYPSEL, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* 802.AS1, Ethernet, Sync packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* 802.AS1, Ethernet, Delay_req packet */
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSMSTRENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2/802.AS1, any layer, any kind of event packet */
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, SNAPTYPSEL, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2/802.AS1, any layer, Sync packet */
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	/* PTP v2/802.AS1, any layer, Delay_req packet */
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSVER2ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSMSTRENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSENA, 1);
		अवरोध;

	शेष:
		वापस -दुस्फल;
	पूर्ण

	pdata->hw_अगर.config_tstamp(pdata, mac_tscr);

	स_नकल(&pdata->tstamp_config, &config, माप(config));

	वापस 0;
पूर्ण

अटल व्योम xgbe_prep_tx_tstamp(काष्ठा xgbe_prv_data *pdata,
				काष्ठा sk_buff *skb,
				काष्ठा xgbe_packet_data *packet)
अणु
	अचिन्हित दीर्घ flags;

	अगर (XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES, PTP)) अणु
		spin_lock_irqsave(&pdata->tstamp_lock, flags);
		अगर (pdata->tx_tstamp_skb) अणु
			/* Another बारtamp in progress, ignore this one */
			XGMAC_SET_BITS(packet->attributes,
				       TX_PACKET_ATTRIBUTES, PTP, 0);
		पूर्ण अन्यथा अणु
			pdata->tx_tstamp_skb = skb_get(skb);
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		पूर्ण
		spin_unlock_irqrestore(&pdata->tstamp_lock, flags);
	पूर्ण

	skb_tx_बारtamp(skb);
पूर्ण

अटल व्योम xgbe_prep_vlan(काष्ठा sk_buff *skb, काष्ठा xgbe_packet_data *packet)
अणु
	अगर (skb_vlan_tag_present(skb))
		packet->vlan_ctag = skb_vlan_tag_get(skb);
पूर्ण

अटल पूर्णांक xgbe_prep_tso(काष्ठा sk_buff *skb, काष्ठा xgbe_packet_data *packet)
अणु
	पूर्णांक ret;

	अगर (!XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			    TSO_ENABLE))
		वापस 0;

	ret = skb_cow_head(skb, 0);
	अगर (ret)
		वापस ret;

	अगर (XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES, VXLAN)) अणु
		packet->header_len = skb_inner_transport_offset(skb) +
				     inner_tcp_hdrlen(skb);
		packet->tcp_header_len = inner_tcp_hdrlen(skb);
	पूर्ण अन्यथा अणु
		packet->header_len = skb_transport_offset(skb) +
				     tcp_hdrlen(skb);
		packet->tcp_header_len = tcp_hdrlen(skb);
	पूर्ण
	packet->tcp_payload_len = skb->len - packet->header_len;
	packet->mss = skb_shinfo(skb)->gso_size;

	DBGPR("  packet->header_len=%u\n", packet->header_len);
	DBGPR("  packet->tcp_header_len=%u, packet->tcp_payload_len=%u\n",
	      packet->tcp_header_len, packet->tcp_payload_len);
	DBGPR("  packet->mss=%u\n", packet->mss);

	/* Update the number of packets that will ultimately be transmitted
	 * aदीर्घ with the extra bytes क्रम each extra packet
	 */
	packet->tx_packets = skb_shinfo(skb)->gso_segs;
	packet->tx_bytes += (packet->tx_packets - 1) * packet->header_len;

	वापस 0;
पूर्ण

अटल bool xgbe_is_vxlan(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->encapsulation)
		वापस false;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस false;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		अगर (ip_hdr(skb)->protocol != IPPROTO_UDP)
			वापस false;
		अवरोध;

	हाल htons(ETH_P_IPV6):
		अगर (ipv6_hdr(skb)->nexthdr != IPPROTO_UDP)
			वापस false;
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	    skb->inner_protocol != htons(ETH_P_TEB) ||
	    (skb_inner_mac_header(skb) - skb_transport_header(skb) !=
	     माप(काष्ठा udphdr) + माप(काष्ठा vxlanhdr)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक xgbe_is_tso(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	DBGPR("  TSO packet to be processed\n");

	वापस 1;
पूर्ण

अटल व्योम xgbe_packet_info(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा xgbe_ring *ring, काष्ठा sk_buff *skb,
			     काष्ठा xgbe_packet_data *packet)
अणु
	skb_frag_t *frag;
	अचिन्हित पूर्णांक context_desc;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक i;

	packet->skb = skb;

	context_desc = 0;
	packet->rdesc_count = 0;

	packet->tx_packets = 1;
	packet->tx_bytes = skb->len;

	अगर (xgbe_is_tso(skb)) अणु
		/* TSO requires an extra descriptor अगर mss is dअगरferent */
		अगर (skb_shinfo(skb)->gso_size != ring->tx.cur_mss) अणु
			context_desc = 1;
			packet->rdesc_count++;
		पूर्ण

		/* TSO requires an extra descriptor क्रम TSO header */
		packet->rdesc_count++;

		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       TSO_ENABLE, 1);
		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       CSUM_ENABLE, 1);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       CSUM_ENABLE, 1);

	अगर (xgbe_is_vxlan(skb))
		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       VXLAN, 1);

	अगर (skb_vlan_tag_present(skb)) अणु
		/* VLAN requires an extra descriptor अगर tag is dअगरferent */
		अगर (skb_vlan_tag_get(skb) != ring->tx.cur_vlan_ctag)
			/* We can share with the TSO context descriptor */
			अगर (!context_desc) अणु
				context_desc = 1;
				packet->rdesc_count++;
			पूर्ण

		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       VLAN_CTAG, 1);
	पूर्ण

	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    (pdata->tstamp_config.tx_type == HWTSTAMP_TX_ON))
		XGMAC_SET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       PTP, 1);

	क्रम (len = skb_headlen(skb); len;) अणु
		packet->rdesc_count++;
		len -= min_t(अचिन्हित पूर्णांक, len, XGBE_TX_MAX_BUF_SIZE);
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		क्रम (len = skb_frag_size(frag); len; ) अणु
			packet->rdesc_count++;
			len -= min_t(अचिन्हित पूर्णांक, len, XGBE_TX_MAX_BUF_SIZE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	पूर्णांक ret;

	/* Create the various names based on netdev name */
	snम_लिखो(pdata->an_name, माप(pdata->an_name) - 1, "%s-pcs",
		 netdev_name(netdev));

	snम_लिखो(pdata->ecc_name, माप(pdata->ecc_name) - 1, "%s-ecc",
		 netdev_name(netdev));

	snम_लिखो(pdata->i2c_name, माप(pdata->i2c_name) - 1, "%s-i2c",
		 netdev_name(netdev));

	/* Create workqueues */
	pdata->dev_workqueue =
		create_singlethपढ़ो_workqueue(netdev_name(netdev));
	अगर (!pdata->dev_workqueue) अणु
		netdev_err(netdev, "device workqueue creation failed\n");
		वापस -ENOMEM;
	पूर्ण

	pdata->an_workqueue =
		create_singlethपढ़ो_workqueue(pdata->an_name);
	अगर (!pdata->an_workqueue) अणु
		netdev_err(netdev, "phy workqueue creation failed\n");
		ret = -ENOMEM;
		जाओ err_dev_wq;
	पूर्ण

	/* Reset the phy settings */
	ret = xgbe_phy_reset(pdata);
	अगर (ret)
		जाओ err_an_wq;

	/* Enable the घड़ीs */
	ret = clk_prepare_enable(pdata->sysclk);
	अगर (ret) अणु
		netdev_alert(netdev, "dma clk_prepare_enable failed\n");
		जाओ err_an_wq;
	पूर्ण

	ret = clk_prepare_enable(pdata->ptpclk);
	अगर (ret) अणु
		netdev_alert(netdev, "ptp clk_prepare_enable failed\n");
		जाओ err_sysclk;
	पूर्ण

	INIT_WORK(&pdata->service_work, xgbe_service);
	INIT_WORK(&pdata->restart_work, xgbe_restart);
	INIT_WORK(&pdata->stopdev_work, xgbe_stopdev);
	INIT_WORK(&pdata->tx_tstamp_work, xgbe_tx_tstamp);

	ret = xgbe_alloc_memory(pdata);
	अगर (ret)
		जाओ err_ptpclk;

	ret = xgbe_start(pdata);
	अगर (ret)
		जाओ err_mem;

	clear_bit(XGBE_DOWN, &pdata->dev_state);

	वापस 0;

err_mem:
	xgbe_मुक्त_memory(pdata);

err_ptpclk:
	clk_disable_unprepare(pdata->ptpclk);

err_sysclk:
	clk_disable_unprepare(pdata->sysclk);

err_an_wq:
	destroy_workqueue(pdata->an_workqueue);

err_dev_wq:
	destroy_workqueue(pdata->dev_workqueue);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	/* Stop the device */
	xgbe_stop(pdata);

	xgbe_मुक्त_memory(pdata);

	/* Disable the घड़ीs */
	clk_disable_unprepare(pdata->ptpclk);
	clk_disable_unprepare(pdata->sysclk);

	flush_workqueue(pdata->an_workqueue);
	destroy_workqueue(pdata->an_workqueue);

	flush_workqueue(pdata->dev_workqueue);
	destroy_workqueue(pdata->dev_workqueue);

	set_bit(XGBE_DOWN, &pdata->dev_state);

	वापस 0;
पूर्ण

अटल netdev_tx_t xgbe_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा xgbe_channel *channel;
	काष्ठा xgbe_ring *ring;
	काष्ठा xgbe_packet_data *packet;
	काष्ठा netdev_queue *txq;
	netdev_tx_t ret;

	DBGPR("-->xgbe_xmit: skb->len = %d\n", skb->len);

	channel = pdata->channel[skb->queue_mapping];
	txq = netdev_get_tx_queue(netdev, channel->queue_index);
	ring = channel->tx_ring;
	packet = &ring->packet_data;

	ret = NETDEV_TX_OK;

	अगर (skb->len == 0) अणु
		netअगर_err(pdata, tx_err, netdev,
			  "empty skb received from stack\n");
		dev_kमुक्त_skb_any(skb);
		जाओ tx_netdev_वापस;
	पूर्ण

	/* Calculate preliminary packet info */
	स_रखो(packet, 0, माप(*packet));
	xgbe_packet_info(pdata, ring, skb, packet);

	/* Check that there are enough descriptors available */
	ret = xgbe_maybe_stop_tx_queue(channel, ring, packet->rdesc_count);
	अगर (ret)
		जाओ tx_netdev_वापस;

	ret = xgbe_prep_tso(skb, packet);
	अगर (ret) अणु
		netअगर_err(pdata, tx_err, netdev,
			  "error processing TSO packet\n");
		dev_kमुक्त_skb_any(skb);
		जाओ tx_netdev_वापस;
	पूर्ण
	xgbe_prep_vlan(skb, packet);

	अगर (!desc_अगर->map_tx_skb(channel, skb)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ tx_netdev_वापस;
	पूर्ण

	xgbe_prep_tx_tstamp(pdata, skb, packet);

	/* Report on the actual number of bytes (to be) sent */
	netdev_tx_sent_queue(txq, packet->tx_bytes);

	/* Configure required descriptor fields क्रम transmission */
	hw_अगर->dev_xmit(channel);

	अगर (netअगर_msg_pktdata(pdata))
		xgbe_prपूर्णांक_pkt(netdev, skb, true);

	/* Stop the queue in advance अगर there may not be enough descriptors */
	xgbe_maybe_stop_tx_queue(channel, ring, XGBE_TX_MAX_DESCS);

	ret = NETDEV_TX_OK;

tx_netdev_वापस:
	वापस ret;
पूर्ण

अटल व्योम xgbe_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;

	DBGPR("-->xgbe_set_rx_mode\n");

	hw_अगर->config_rx_mode(pdata);

	DBGPR("<--xgbe_set_rx_mode\n");
पूर्ण

अटल पूर्णांक xgbe_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा sockaddr *saddr = addr;

	DBGPR("-->xgbe_set_mac_address\n");

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, saddr->sa_data, netdev->addr_len);

	hw_अगर->set_mac_address(pdata, netdev->dev_addr);

	DBGPR("<--xgbe_set_mac_address\n");

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरreq, पूर्णांक cmd)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
		ret = xgbe_get_hwtstamp_settings(pdata, अगरreq);
		अवरोध;

	हाल SIOCSHWTSTAMP:
		ret = xgbe_set_hwtstamp_settings(pdata, अगरreq);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	पूर्णांक ret;

	DBGPR("-->xgbe_change_mtu\n");

	ret = xgbe_calc_rx_buf_size(netdev, mtu);
	अगर (ret < 0)
		वापस ret;

	pdata->rx_buf_size = ret;
	netdev->mtu = mtu;

	xgbe_restart_dev(pdata);

	DBGPR("<--xgbe_change_mtu\n");

	वापस 0;
पूर्ण

अटल व्योम xgbe_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	netdev_warn(netdev, "tx timeout, device restarting\n");
	schedule_work(&pdata->restart_work);
पूर्ण

अटल व्योम xgbe_get_stats64(काष्ठा net_device *netdev,
			     काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_mmc_stats *pstats = &pdata->mmc_stats;

	DBGPR("-->%s\n", __func__);

	pdata->hw_अगर.पढ़ो_mmc_stats(pdata);

	s->rx_packets = pstats->rxframecount_gb;
	s->rx_bytes = pstats->rxoctetcount_gb;
	s->rx_errors = pstats->rxframecount_gb -
		       pstats->rxbroadcastframes_g -
		       pstats->rxmulticastframes_g -
		       pstats->rxunicastframes_g;
	s->multicast = pstats->rxmulticastframes_g;
	s->rx_length_errors = pstats->rxlengtherror;
	s->rx_crc_errors = pstats->rxcrcerror;
	s->rx_fअगरo_errors = pstats->rxfअगरooverflow;

	s->tx_packets = pstats->txframecount_gb;
	s->tx_bytes = pstats->txoctetcount_gb;
	s->tx_errors = pstats->txframecount_gb - pstats->txframecount_g;
	s->tx_dropped = netdev->stats.tx_dropped;

	DBGPR("<--%s\n", __func__);
पूर्ण

अटल पूर्णांक xgbe_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto,
				u16 vid)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;

	DBGPR("-->%s\n", __func__);

	set_bit(vid, pdata->active_vlans);
	hw_अगर->update_vlan_hash_table(pdata);

	DBGPR("<--%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto,
				 u16 vid)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;

	DBGPR("-->%s\n", __func__);

	clear_bit(vid, pdata->active_vlans);
	hw_अगर->update_vlan_hash_table(pdata);

	DBGPR("<--%s\n", __func__);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम xgbe_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	DBGPR("-->xgbe_poll_controller\n");

	अगर (pdata->per_channel_irq) अणु
		क्रम (i = 0; i < pdata->channel_count; i++) अणु
			channel = pdata->channel[i];
			xgbe_dma_isr(channel->dma_irq, channel);
		पूर्ण
	पूर्ण अन्यथा अणु
		disable_irq(pdata->dev_irq);
		xgbe_isr(pdata->dev_irq, pdata);
		enable_irq(pdata->dev_irq);
	पूर्ण

	DBGPR("<--xgbe_poll_controller\n");
पूर्ण
#पूर्ण_अगर /* End CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक xgbe_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
			 व्योम *type_data)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	u8 tc;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	tc = mqprio->num_tc;

	अगर (tc > pdata->hw_feat.tc_cnt)
		वापस -EINVAL;

	pdata->num_tcs = tc;
	pdata->hw_अगर.config_tc(pdata);

	वापस 0;
पूर्ण

अटल netdev_features_t xgbe_fix_features(काष्ठा net_device *netdev,
					   netdev_features_t features)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	netdev_features_t vxlan_base;

	vxlan_base = NETIF_F_GSO_UDP_TUNNEL | NETIF_F_RX_UDP_TUNNEL_PORT;

	अगर (!pdata->hw_feat.vxn)
		वापस features;

	/* VXLAN CSUM requires VXLAN base */
	अगर ((features & NETIF_F_GSO_UDP_TUNNEL_CSUM) &&
	    !(features & NETIF_F_GSO_UDP_TUNNEL)) अणु
		netdev_notice(netdev,
			      "forcing tx udp tunnel support\n");
		features |= NETIF_F_GSO_UDP_TUNNEL;
	पूर्ण

	/* Can't करो one without करोing the other */
	अगर ((features & vxlan_base) != vxlan_base) अणु
		netdev_notice(netdev,
			      "forcing both tx and rx udp tunnel support\n");
		features |= vxlan_base;
	पूर्ण

	अगर (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) अणु
		अगर (!(features & NETIF_F_GSO_UDP_TUNNEL_CSUM)) अणु
			netdev_notice(netdev,
				      "forcing tx udp tunnel checksumming on\n");
			features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (features & NETIF_F_GSO_UDP_TUNNEL_CSUM) अणु
			netdev_notice(netdev,
				      "forcing tx udp tunnel checksumming off\n");
			features &= ~NETIF_F_GSO_UDP_TUNNEL_CSUM;
		पूर्ण
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक xgbe_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	netdev_features_t rxhash, rxcsum, rxvlan, rxvlan_filter;
	पूर्णांक ret = 0;

	rxhash = pdata->netdev_features & NETIF_F_RXHASH;
	rxcsum = pdata->netdev_features & NETIF_F_RXCSUM;
	rxvlan = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_RX;
	rxvlan_filter = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर ((features & NETIF_F_RXHASH) && !rxhash)
		ret = hw_अगर->enable_rss(pdata);
	अन्यथा अगर (!(features & NETIF_F_RXHASH) && rxhash)
		ret = hw_अगर->disable_rss(pdata);
	अगर (ret)
		वापस ret;

	अगर ((features & NETIF_F_RXCSUM) && !rxcsum)
		hw_अगर->enable_rx_csum(pdata);
	अन्यथा अगर (!(features & NETIF_F_RXCSUM) && rxcsum)
		hw_अगर->disable_rx_csum(pdata);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_RX) && !rxvlan)
		hw_अगर->enable_rx_vlan_stripping(pdata);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_RX) && rxvlan)
		hw_अगर->disable_rx_vlan_stripping(pdata);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_FILTER) && !rxvlan_filter)
		hw_अगर->enable_rx_vlan_filtering(pdata);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) && rxvlan_filter)
		hw_अगर->disable_rx_vlan_filtering(pdata);

	pdata->netdev_features = features;

	DBGPR("<--xgbe_set_features\n");

	वापस 0;
पूर्ण

अटल netdev_features_t xgbe_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *netdev,
					     netdev_features_t features)
अणु
	features = vlan_features_check(skb, features);
	features = vxlan_features_check(skb, features);

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xgbe_netdev_ops = अणु
	.nकरो_खोलो		= xgbe_खोलो,
	.nकरो_stop		= xgbe_बंद,
	.nकरो_start_xmit		= xgbe_xmit,
	.nकरो_set_rx_mode	= xgbe_set_rx_mode,
	.nकरो_set_mac_address	= xgbe_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= xgbe_ioctl,
	.nकरो_change_mtu		= xgbe_change_mtu,
	.nकरो_tx_समयout		= xgbe_tx_समयout,
	.nकरो_get_stats64	= xgbe_get_stats64,
	.nकरो_vlan_rx_add_vid	= xgbe_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= xgbe_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= xgbe_poll_controller,
#पूर्ण_अगर
	.nकरो_setup_tc		= xgbe_setup_tc,
	.nकरो_fix_features	= xgbe_fix_features,
	.nकरो_set_features	= xgbe_set_features,
	.nकरो_features_check	= xgbe_features_check,
पूर्ण;

स्थिर काष्ठा net_device_ops *xgbe_get_netdev_ops(व्योम)
अणु
	वापस &xgbe_netdev_ops;
पूर्ण

अटल व्योम xgbe_rx_refresh(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा xgbe_ring *ring = channel->rx_ring;
	काष्ठा xgbe_ring_data *rdata;

	जबतक (ring->dirty != ring->cur) अणु
		rdata = XGBE_GET_DESC_DATA(ring, ring->dirty);

		/* Reset rdata values */
		desc_अगर->unmap_rdata(pdata, rdata);

		अगर (desc_अगर->map_rx_buffer(pdata, ring, rdata))
			अवरोध;

		hw_अगर->rx_desc_reset(pdata, rdata, ring->dirty);

		ring->dirty++;
	पूर्ण

	/* Make sure everything is written beक्रमe the रेजिस्टर ग_लिखो */
	wmb();

	/* Update the Rx Tail Poपूर्णांकer Register with address of
	 * the last cleaned entry */
	rdata = XGBE_GET_DESC_DATA(ring, ring->dirty - 1);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));
पूर्ण

अटल काष्ठा sk_buff *xgbe_create_skb(काष्ठा xgbe_prv_data *pdata,
				       काष्ठा napi_काष्ठा *napi,
				       काष्ठा xgbe_ring_data *rdata,
				       अचिन्हित पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	u8 *packet;

	skb = napi_alloc_skb(napi, rdata->rx.hdr.dma_len);
	अगर (!skb)
		वापस शून्य;

	/* Pull in the header buffer which may contain just the header
	 * or the header plus data
	 */
	dma_sync_single_range_क्रम_cpu(pdata->dev, rdata->rx.hdr.dma_base,
				      rdata->rx.hdr.dma_off,
				      rdata->rx.hdr.dma_len, DMA_FROM_DEVICE);

	packet = page_address(rdata->rx.hdr.pa.pages) +
		 rdata->rx.hdr.pa.pages_offset;
	skb_copy_to_linear_data(skb, packet, len);
	skb_put(skb, len);

	वापस skb;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_rx_buf1_len(काष्ठा xgbe_ring_data *rdata,
				     काष्ठा xgbe_packet_data *packet)
अणु
	/* Always zero अगर not the first descriptor */
	अगर (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, FIRST))
		वापस 0;

	/* First descriptor with split header, वापस header length */
	अगर (rdata->rx.hdr_len)
		वापस rdata->rx.hdr_len;

	/* First descriptor but not the last descriptor and no split header,
	 * so the full buffer was used
	 */
	अगर (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, LAST))
		वापस rdata->rx.hdr.dma_len;

	/* First descriptor and last descriptor and no split header, so
	 * calculate how much of the buffer was used
	 */
	वापस min_t(अचिन्हित पूर्णांक, rdata->rx.hdr.dma_len, rdata->rx.len);
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_rx_buf2_len(काष्ठा xgbe_ring_data *rdata,
				     काष्ठा xgbe_packet_data *packet,
				     अचिन्हित पूर्णांक len)
अणु
	/* Always the full buffer अगर not the last descriptor */
	अगर (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, LAST))
		वापस rdata->rx.buf.dma_len;

	/* Last descriptor so calculate how much of the buffer was used
	 * क्रम the last bit of data
	 */
	वापस rdata->rx.len - len;
पूर्ण

अटल पूर्णांक xgbe_tx_poll(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	काष्ठा xgbe_ring *ring = channel->tx_ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_queue *txq;
	पूर्णांक processed = 0;
	अचिन्हित पूर्णांक tx_packets = 0, tx_bytes = 0;
	अचिन्हित पूर्णांक cur;

	DBGPR("-->xgbe_tx_poll\n");

	/* Nothing to करो अगर there isn't a Tx ring क्रम this channel */
	अगर (!ring)
		वापस 0;

	cur = ring->cur;

	/* Be sure we get ring->cur beक्रमe accessing descriptor data */
	smp_rmb();

	txq = netdev_get_tx_queue(netdev, channel->queue_index);

	जबतक ((processed < XGBE_TX_DESC_MAX_PROC) &&
	       (ring->dirty != cur)) अणु
		rdata = XGBE_GET_DESC_DATA(ring, ring->dirty);
		rdesc = rdata->rdesc;

		अगर (!hw_अगर->tx_complete(rdesc))
			अवरोध;

		/* Make sure descriptor fields are पढ़ो after पढ़ोing the OWN
		 * bit */
		dma_rmb();

		अगर (netअगर_msg_tx_करोne(pdata))
			xgbe_dump_tx_desc(pdata, ring, ring->dirty, 1, 0);

		अगर (hw_अगर->is_last_desc(rdesc)) अणु
			tx_packets += rdata->tx.packets;
			tx_bytes += rdata->tx.bytes;
		पूर्ण

		/* Free the SKB and reset the descriptor क्रम re-use */
		desc_अगर->unmap_rdata(pdata, rdata);
		hw_अगर->tx_desc_reset(rdata);

		processed++;
		ring->dirty++;
	पूर्ण

	अगर (!processed)
		वापस 0;

	netdev_tx_completed_queue(txq, tx_packets, tx_bytes);

	अगर ((ring->tx.queue_stopped == 1) &&
	    (xgbe_tx_avail_desc(ring) > XGBE_TX_DESC_MIN_FREE)) अणु
		ring->tx.queue_stopped = 0;
		netअगर_tx_wake_queue(txq);
	पूर्ण

	DBGPR("<--xgbe_tx_poll: processed=%d\n", processed);

	वापस processed;
पूर्ण

अटल पूर्णांक xgbe_rx_poll(काष्ठा xgbe_channel *channel, पूर्णांक budget)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_ring *ring = channel->rx_ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_packet_data *packet;
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *hwtstamps;
	अचिन्हित पूर्णांक last, error, context_next, context;
	अचिन्हित पूर्णांक len, buf1_len, buf2_len, max_len;
	अचिन्हित पूर्णांक received = 0;
	पूर्णांक packet_count = 0;

	DBGPR("-->xgbe_rx_poll: budget=%d\n", budget);

	/* Nothing to करो अगर there isn't a Rx ring क्रम this channel */
	अगर (!ring)
		वापस 0;

	last = 0;
	context_next = 0;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	packet = &ring->packet_data;
	जबतक (packet_count < budget) अणु
		DBGPR("  cur = %d\n", ring->cur);

		/* First समय in loop see अगर we need to restore state */
		अगर (!received && rdata->state_saved) अणु
			skb = rdata->state.skb;
			error = rdata->state.error;
			len = rdata->state.len;
		पूर्ण अन्यथा अणु
			स_रखो(packet, 0, माप(*packet));
			skb = शून्य;
			error = 0;
			len = 0;
		पूर्ण

पढ़ो_again:
		rdata = XGBE_GET_DESC_DATA(ring, ring->cur);

		अगर (xgbe_rx_dirty_desc(ring) > (XGBE_RX_DESC_CNT >> 3))
			xgbe_rx_refresh(channel);

		अगर (hw_अगर->dev_पढ़ो(channel))
			अवरोध;

		received++;
		ring->cur++;

		last = XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				      LAST);
		context_next = XGMAC_GET_BITS(packet->attributes,
					      RX_PACKET_ATTRIBUTES,
					      CONTEXT_NEXT);
		context = XGMAC_GET_BITS(packet->attributes,
					 RX_PACKET_ATTRIBUTES,
					 CONTEXT);

		/* Earlier error, just drain the reमुख्यing data */
		अगर ((!last || context_next) && error)
			जाओ पढ़ो_again;

		अगर (error || packet->errors) अणु
			अगर (packet->errors)
				netअगर_err(pdata, rx_err, netdev,
					  "error in received packet\n");
			dev_kमुक्त_skb(skb);
			जाओ next_packet;
		पूर्ण

		अगर (!context) अणु
			/* Get the data length in the descriptor buffers */
			buf1_len = xgbe_rx_buf1_len(rdata, packet);
			len += buf1_len;
			buf2_len = xgbe_rx_buf2_len(rdata, packet, len);
			len += buf2_len;

			अगर (!skb) अणु
				skb = xgbe_create_skb(pdata, napi, rdata,
						      buf1_len);
				अगर (!skb) अणु
					error = 1;
					जाओ skip_data;
				पूर्ण
			पूर्ण

			अगर (buf2_len) अणु
				dma_sync_single_range_क्रम_cpu(pdata->dev,
							rdata->rx.buf.dma_base,
							rdata->rx.buf.dma_off,
							rdata->rx.buf.dma_len,
							DMA_FROM_DEVICE);

				skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
						rdata->rx.buf.pa.pages,
						rdata->rx.buf.pa.pages_offset,
						buf2_len,
						rdata->rx.buf.dma_len);
				rdata->rx.buf.pa.pages = शून्य;
			पूर्ण
		पूर्ण

skip_data:
		अगर (!last || context_next)
			जाओ पढ़ो_again;

		अगर (!skb)
			जाओ next_packet;

		/* Be sure we करोn't exceed the configured MTU */
		max_len = netdev->mtu + ETH_HLEN;
		अगर (!(netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    (skb->protocol == htons(ETH_P_8021Q)))
			max_len += VLAN_HLEN;

		अगर (skb->len > max_len) अणु
			netअगर_err(pdata, rx_err, netdev,
				  "packet length exceeds configured MTU\n");
			dev_kमुक्त_skb(skb);
			जाओ next_packet;
		पूर्ण

		अगर (netअगर_msg_pktdata(pdata))
			xgbe_prपूर्णांक_pkt(netdev, skb, false);

		skb_checksum_none_निश्चित(skb);
		अगर (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, CSUM_DONE))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		अगर (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, TNP)) अणु
			skb->encapsulation = 1;

			अगर (XGMAC_GET_BITS(packet->attributes,
					   RX_PACKET_ATTRIBUTES, TNPCSUM_DONE))
				skb->csum_level = 1;
		पूर्ण

		अगर (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, VLAN_CTAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       packet->vlan_ctag);

		अगर (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, RX_TSTAMP)) अणु
			u64 nsec;

			nsec = समयcounter_cyc2समय(&pdata->tstamp_tc,
						    packet->rx_tstamp);
			hwtstamps = skb_hwtstamps(skb);
			hwtstamps->hwtstamp = ns_to_kसमय(nsec);
		पूर्ण

		अगर (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, RSS_HASH))
			skb_set_hash(skb, packet->rss_hash,
				     packet->rss_hash_type);

		skb->dev = netdev;
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, channel->queue_index);

		napi_gro_receive(napi, skb);

next_packet:
		packet_count++;
	पूर्ण

	/* Check अगर we need to save state beक्रमe leaving */
	अगर (received && (!last || context_next)) अणु
		rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
		rdata->state_saved = 1;
		rdata->state.skb = skb;
		rdata->state.len = len;
		rdata->state.error = error;
	पूर्ण

	DBGPR("<--xgbe_rx_poll: packet_count = %d\n", packet_count);

	वापस packet_count;
पूर्ण

अटल पूर्णांक xgbe_one_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xgbe_channel *channel = container_of(napi, काष्ठा xgbe_channel,
						    napi);
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	पूर्णांक processed = 0;

	DBGPR("-->xgbe_one_poll: budget=%d\n", budget);

	/* Cleanup Tx ring first */
	xgbe_tx_poll(channel);

	/* Process Rx ring next */
	processed = xgbe_rx_poll(channel, budget);

	/* If we processed everything, we are करोne */
	अगर ((processed < budget) && napi_complete_करोne(napi, processed)) अणु
		/* Enable Tx and Rx पूर्णांकerrupts */
		अगर (pdata->channel_irq_mode)
			xgbe_enable_rx_tx_पूर्णांक(pdata, channel);
		अन्यथा
			enable_irq(channel->dma_irq);
	पूर्ण

	DBGPR("<--xgbe_one_poll: received = %d\n", processed);

	वापस processed;
पूर्ण

अटल पूर्णांक xgbe_all_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(napi, काष्ठा xgbe_prv_data,
						   napi);
	काष्ठा xgbe_channel *channel;
	पूर्णांक ring_budget;
	पूर्णांक processed, last_processed;
	अचिन्हित पूर्णांक i;

	DBGPR("-->xgbe_all_poll: budget=%d\n", budget);

	processed = 0;
	ring_budget = budget / pdata->rx_ring_count;
	करो अणु
		last_processed = processed;

		क्रम (i = 0; i < pdata->channel_count; i++) अणु
			channel = pdata->channel[i];

			/* Cleanup Tx ring first */
			xgbe_tx_poll(channel);

			/* Process Rx ring next */
			अगर (ring_budget > (budget - processed))
				ring_budget = budget - processed;
			processed += xgbe_rx_poll(channel, ring_budget);
		पूर्ण
	पूर्ण जबतक ((processed < budget) && (processed != last_processed));

	/* If we processed everything, we are करोne */
	अगर ((processed < budget) && napi_complete_करोne(napi, processed)) अणु
		/* Enable Tx and Rx पूर्णांकerrupts */
		xgbe_enable_rx_tx_पूर्णांकs(pdata);
	पूर्ण

	DBGPR("<--xgbe_all_poll: received = %d\n", processed);

	वापस processed;
पूर्ण

व्योम xgbe_dump_tx_desc(काष्ठा xgbe_prv_data *pdata, काष्ठा xgbe_ring *ring,
		       अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक flag)
अणु
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;

	जबतक (count--) अणु
		rdata = XGBE_GET_DESC_DATA(ring, idx);
		rdesc = rdata->rdesc;
		netdev_dbg(pdata->netdev,
			   "TX_NORMAL_DESC[%d %s] = %08x:%08x:%08x:%08x\n", idx,
			   (flag == 1) ? "QUEUED FOR TX" : "TX BY DEVICE",
			   le32_to_cpu(rdesc->desc0),
			   le32_to_cpu(rdesc->desc1),
			   le32_to_cpu(rdesc->desc2),
			   le32_to_cpu(rdesc->desc3));
		idx++;
	पूर्ण
पूर्ण

व्योम xgbe_dump_rx_desc(काष्ठा xgbe_prv_data *pdata, काष्ठा xgbe_ring *ring,
		       अचिन्हित पूर्णांक idx)
अणु
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;

	rdata = XGBE_GET_DESC_DATA(ring, idx);
	rdesc = rdata->rdesc;
	netdev_dbg(pdata->netdev,
		   "RX_NORMAL_DESC[%d RX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx, le32_to_cpu(rdesc->desc0), le32_to_cpu(rdesc->desc1),
		   le32_to_cpu(rdesc->desc2), le32_to_cpu(rdesc->desc3));
पूर्ण

व्योम xgbe_prपूर्णांक_pkt(काष्ठा net_device *netdev, काष्ठा sk_buff *skb, bool tx_rx)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	अचिन्हित अक्षर buffer[128];
	अचिन्हित पूर्णांक i;

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");

	netdev_dbg(netdev, "%s packet of %d bytes\n",
		   (tx_rx ? "TX" : "RX"), skb->len);

	netdev_dbg(netdev, "Dst MAC addr: %pM\n", eth->h_dest);
	netdev_dbg(netdev, "Src MAC addr: %pM\n", eth->h_source);
	netdev_dbg(netdev, "Protocol: %#06hx\n", ntohs(eth->h_proto));

	क्रम (i = 0; i < skb->len; i += 32) अणु
		अचिन्हित पूर्णांक len = min(skb->len - i, 32U);

		hex_dump_to_buffer(&skb->data[i], len, 32, 1,
				   buffer, माप(buffer), false);
		netdev_dbg(netdev, "  %#06x: %s\n", i, buffer);
	पूर्ण

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");
पूर्ण
