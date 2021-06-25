<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * hcd.c - DesignWare HS OTG Controller host-mode routines
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file contains the core HCD code, and implements the Linux hc_driver
 * API
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>

#समावेश "core.h"
#समावेश "hcd.h"

/*
 * =========================================================================
 *  Host Core Layer Functions
 * =========================================================================
 */

/**
 * dwc2_enable_common_पूर्णांकerrupts() - Initializes the commmon पूर्णांकerrupts,
 * used in both device and host modes
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
अटल व्योम dwc2_enable_common_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 पूर्णांकmsk;

	/* Clear any pending OTG Interrupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GOTGINT);

	/* Clear any pending पूर्णांकerrupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Enable the पूर्णांकerrupts in the GINTMSK */
	पूर्णांकmsk = GINTSTS_MODEMIS | GINTSTS_OTGINT;

	अगर (!hsotg->params.host_dma)
		पूर्णांकmsk |= GINTSTS_RXFLVL;
	अगर (!hsotg->params.बाह्यal_id_pin_ctl)
		पूर्णांकmsk |= GINTSTS_CONIDSTSCHNG;

	पूर्णांकmsk |= GINTSTS_WKUPINT | GINTSTS_USBSUSP |
		  GINTSTS_SESSREQINT;

	अगर (dwc2_is_device_mode(hsotg) && hsotg->params.lpm)
		पूर्णांकmsk |= GINTSTS_LPMTRANRCVD;

	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, GINTMSK);
पूर्ण

अटल पूर्णांक dwc2_gahbcfg_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 ahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);

	चयन (hsotg->hw_params.arch) अणु
	हाल GHWCFG2_EXT_DMA_ARCH:
		dev_err(hsotg->dev, "External DMA Mode not supported\n");
		वापस -EINVAL;

	हाल GHWCFG2_INT_DMA_ARCH:
		dev_dbg(hsotg->dev, "Internal DMA Mode\n");
		अगर (hsotg->params.ahbcfg != -1) अणु
			ahbcfg &= GAHBCFG_CTRL_MASK;
			ahbcfg |= hsotg->params.ahbcfg &
				  ~GAHBCFG_CTRL_MASK;
		पूर्ण
		अवरोध;

	हाल GHWCFG2_SLAVE_ONLY_ARCH:
	शेष:
		dev_dbg(hsotg->dev, "Slave Only Mode\n");
		अवरोध;
	पूर्ण

	अगर (hsotg->params.host_dma)
		ahbcfg |= GAHBCFG_DMA_EN;
	अन्यथा
		hsotg->params.dma_desc_enable = false;

	dwc2_ग_लिखोl(hsotg, ahbcfg, GAHBCFG);

	वापस 0;
पूर्ण

अटल व्योम dwc2_gusbcfg_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 usbcfg;

	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	usbcfg &= ~(GUSBCFG_HNPCAP | GUSBCFG_SRPCAP);

	चयन (hsotg->hw_params.op_mode) अणु
	हाल GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		अगर (hsotg->params.otg_cap ==
				DWC2_CAP_PARAM_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_HNPCAP;
		अगर (hsotg->params.otg_cap !=
				DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_SRPCAP;
		अवरोध;

	हाल GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
	हाल GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
	हाल GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
		अगर (hsotg->params.otg_cap !=
				DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_SRPCAP;
		अवरोध;

	हाल GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE:
	हाल GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE:
	हाल GHWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST:
	शेष:
		अवरोध;
	पूर्ण

	dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);
पूर्ण

अटल पूर्णांक dwc2_vbus_supply_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->vbus_supply)
		वापस regulator_enable(hsotg->vbus_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_vbus_supply_निकास(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->vbus_supply)
		वापस regulator_disable(hsotg->vbus_supply);

	वापस 0;
पूर्ण

/**
 * dwc2_enable_host_पूर्णांकerrupts() - Enables the Host mode पूर्णांकerrupts
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_enable_host_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 पूर्णांकmsk;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	/* Disable all पूर्णांकerrupts */
	dwc2_ग_लिखोl(hsotg, 0, GINTMSK);
	dwc2_ग_लिखोl(hsotg, 0, HAINTMSK);

	/* Enable the common पूर्णांकerrupts */
	dwc2_enable_common_पूर्णांकerrupts(hsotg);

	/* Enable host mode पूर्णांकerrupts without disturbing common पूर्णांकerrupts */
	पूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	पूर्णांकmsk |= GINTSTS_DISCONNINT | GINTSTS_PRTINT | GINTSTS_HCHINT;
	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, GINTMSK);
पूर्ण

/**
 * dwc2_disable_host_पूर्णांकerrupts() - Disables the Host Mode पूर्णांकerrupts
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_disable_host_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 पूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);

	/* Disable host mode पूर्णांकerrupts without disturbing common पूर्णांकerrupts */
	पूर्णांकmsk &= ~(GINTSTS_SOF | GINTSTS_PRTINT | GINTSTS_HCHINT |
		    GINTSTS_PTXFEMP | GINTSTS_NPTXFEMP | GINTSTS_DISCONNINT);
	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, GINTMSK);
पूर्ण

/*
 * dwc2_calculate_dynamic_fअगरo() - Calculates the शेष fअगरo size
 * For प्रणाली that have a total fअगरo depth that is smaller than the शेष
 * RX + TX fअगरo size.
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_calculate_dynamic_fअगरo(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *params = &hsotg->params;
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	u32 rxfsiz, nptxfsiz, ptxfsiz, total_fअगरo_size;

	total_fअगरo_size = hw->total_fअगरo_size;
	rxfsiz = params->host_rx_fअगरo_size;
	nptxfsiz = params->host_nperio_tx_fअगरo_size;
	ptxfsiz = params->host_perio_tx_fअगरo_size;

	/*
	 * Will use Method 2 defined in the DWC2 spec: minimum FIFO depth
	 * allocation with support क्रम high bandwidth endpoपूर्णांकs. Synopsys
	 * defines MPS(Max Packet size) क्रम a periodic EP=1024, and क्रम
	 * non-periodic as 512.
	 */
	अगर (total_fअगरo_size < (rxfsiz + nptxfsiz + ptxfsiz)) अणु
		/*
		 * For Buffer DMA mode/Scatter Gather DMA mode
		 * 2 * ((Largest Packet size / 4) + 1 + 1) + n
		 * with n = number of host channel.
		 * 2 * ((1024/4) + 2) = 516
		 */
		rxfsiz = 516 + hw->host_channels;

		/*
		 * min non-periodic tx fअगरo depth
		 * 2 * (largest non-periodic USB packet used / 4)
		 * 2 * (512/4) = 256
		 */
		nptxfsiz = 256;

		/*
		 * min periodic tx fअगरo depth
		 * (largest packet size*MC)/4
		 * (1024 * 3)/4 = 768
		 */
		ptxfsiz = 768;

		params->host_rx_fअगरo_size = rxfsiz;
		params->host_nperio_tx_fअगरo_size = nptxfsiz;
		params->host_perio_tx_fअगरo_size = ptxfsiz;
	पूर्ण

	/*
	 * If the summation of RX, NPTX and PTX fअगरo sizes is still
	 * bigger than the total_fअगरo_size, then we have a problem.
	 *
	 * We won't be able to allocate as many endpoपूर्णांकs. Right now,
	 * we're just prपूर्णांकing an error message, but ideally this FIFO
	 * allocation algorithm would be improved in the future.
	 *
	 * FIXME improve this FIFO allocation algorithm.
	 */
	अगर (unlikely(total_fअगरo_size < (rxfsiz + nptxfsiz + ptxfsiz)))
		dev_err(hsotg->dev, "invalid fifo sizes\n");
पूर्ण

अटल व्योम dwc2_config_fअगरos(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *params = &hsotg->params;
	u32 nptxfsiz, hptxfsiz, dfअगरocfg, grxfsiz;

	अगर (!params->enable_dynamic_fअगरo)
		वापस;

	dwc2_calculate_dynamic_fअगरo(hsotg);

	/* Rx FIFO */
	grxfsiz = dwc2_पढ़ोl(hsotg, GRXFSIZ);
	dev_dbg(hsotg->dev, "initial grxfsiz=%08x\n", grxfsiz);
	grxfsiz &= ~GRXFSIZ_DEPTH_MASK;
	grxfsiz |= params->host_rx_fअगरo_size <<
		   GRXFSIZ_DEPTH_SHIFT & GRXFSIZ_DEPTH_MASK;
	dwc2_ग_लिखोl(hsotg, grxfsiz, GRXFSIZ);
	dev_dbg(hsotg->dev, "new grxfsiz=%08x\n",
		dwc2_पढ़ोl(hsotg, GRXFSIZ));

	/* Non-periodic Tx FIFO */
	dev_dbg(hsotg->dev, "initial gnptxfsiz=%08x\n",
		dwc2_पढ़ोl(hsotg, GNPTXFSIZ));
	nptxfsiz = params->host_nperio_tx_fअगरo_size <<
		   FIFOSIZE_DEPTH_SHIFT & FIFOSIZE_DEPTH_MASK;
	nptxfsiz |= params->host_rx_fअगरo_size <<
		    FIFOSIZE_STARTADDR_SHIFT & FIFOSIZE_STARTADDR_MASK;
	dwc2_ग_लिखोl(hsotg, nptxfsiz, GNPTXFSIZ);
	dev_dbg(hsotg->dev, "new gnptxfsiz=%08x\n",
		dwc2_पढ़ोl(hsotg, GNPTXFSIZ));

	/* Periodic Tx FIFO */
	dev_dbg(hsotg->dev, "initial hptxfsiz=%08x\n",
		dwc2_पढ़ोl(hsotg, HPTXFSIZ));
	hptxfsiz = params->host_perio_tx_fअगरo_size <<
		   FIFOSIZE_DEPTH_SHIFT & FIFOSIZE_DEPTH_MASK;
	hptxfsiz |= (params->host_rx_fअगरo_size +
		     params->host_nperio_tx_fअगरo_size) <<
		    FIFOSIZE_STARTADDR_SHIFT & FIFOSIZE_STARTADDR_MASK;
	dwc2_ग_लिखोl(hsotg, hptxfsiz, HPTXFSIZ);
	dev_dbg(hsotg->dev, "new hptxfsiz=%08x\n",
		dwc2_पढ़ोl(hsotg, HPTXFSIZ));

	अगर (hsotg->params.en_multiple_tx_fअगरo &&
	    hsotg->hw_params.snpsid >= DWC2_CORE_REV_2_91a) अणु
		/*
		 * This feature was implemented in 2.91a version
		 * Global DFIFOCFG calculation क्रम Host mode -
		 * include RxFIFO, NPTXFIFO and HPTXFIFO
		 */
		dfअगरocfg = dwc2_पढ़ोl(hsotg, GDFIFOCFG);
		dfअगरocfg &= ~GDFIFOCFG_EPINFOBASE_MASK;
		dfअगरocfg |= (params->host_rx_fअगरo_size +
			     params->host_nperio_tx_fअगरo_size +
			     params->host_perio_tx_fअगरo_size) <<
			    GDFIFOCFG_EPINFOBASE_SHIFT &
			    GDFIFOCFG_EPINFOBASE_MASK;
		dwc2_ग_लिखोl(hsotg, dfअगरocfg, GDFIFOCFG);
	पूर्ण
पूर्ण

/**
 * dwc2_calc_frame_पूर्णांकerval() - Calculates the correct frame Interval value क्रम
 * the HFIR रेजिस्टर according to PHY type and speed
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * NOTE: The caller can modअगरy the value of the HFIR रेजिस्टर only after the
 * Port Enable bit of the Host Port Control and Status रेजिस्टर (HPRT.EnaPort)
 * has been set
 */
u32 dwc2_calc_frame_पूर्णांकerval(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 usbcfg;
	u32 hprt0;
	पूर्णांक घड़ी = 60;	/* शेष value */

	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);

	अगर (!(usbcfg & GUSBCFG_PHYSEL) && (usbcfg & GUSBCFG_ULPI_UTMI_SEL) &&
	    !(usbcfg & GUSBCFG_PHYIF16))
		घड़ी = 60;
	अगर ((usbcfg & GUSBCFG_PHYSEL) && hsotg->hw_params.fs_phy_type ==
	    GHWCFG2_FS_PHY_TYPE_SHARED_ULPI)
		घड़ी = 48;
	अगर (!(usbcfg & GUSBCFG_PHY_LP_CLK_SEL) && !(usbcfg & GUSBCFG_PHYSEL) &&
	    !(usbcfg & GUSBCFG_ULPI_UTMI_SEL) && (usbcfg & GUSBCFG_PHYIF16))
		घड़ी = 30;
	अगर (!(usbcfg & GUSBCFG_PHY_LP_CLK_SEL) && !(usbcfg & GUSBCFG_PHYSEL) &&
	    !(usbcfg & GUSBCFG_ULPI_UTMI_SEL) && !(usbcfg & GUSBCFG_PHYIF16))
		घड़ी = 60;
	अगर ((usbcfg & GUSBCFG_PHY_LP_CLK_SEL) && !(usbcfg & GUSBCFG_PHYSEL) &&
	    !(usbcfg & GUSBCFG_ULPI_UTMI_SEL) && (usbcfg & GUSBCFG_PHYIF16))
		घड़ी = 48;
	अगर ((usbcfg & GUSBCFG_PHYSEL) && !(usbcfg & GUSBCFG_PHYIF16) &&
	    hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_SHARED_UTMI)
		घड़ी = 48;
	अगर ((usbcfg & GUSBCFG_PHYSEL) &&
	    hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED)
		घड़ी = 48;

	अगर ((hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT == HPRT0_SPD_HIGH_SPEED)
		/* High speed हाल */
		वापस 125 * घड़ी - 1;

	/* FS/LS हाल */
	वापस 1000 * घड़ी - 1;
पूर्ण

/**
 * dwc2_पढ़ो_packet() - Reads a packet from the Rx FIFO पूर्णांकo the destination
 * buffer
 *
 * @hsotg: Programming view of DWC_otg controller
 * @dest:    Destination buffer क्रम the packet
 * @bytes:   Number of bytes to copy to the destination
 */
व्योम dwc2_पढ़ो_packet(काष्ठा dwc2_hsotg *hsotg, u8 *dest, u16 bytes)
अणु
	u32 *data_buf = (u32 *)dest;
	पूर्णांक word_count = (bytes + 3) / 4;
	पूर्णांक i;

	/*
	 * Toकरो: Account क्रम the हाल where dest is not dword aligned. This
	 * requires पढ़ोing data from the FIFO पूर्णांकo a u32 temp buffer, then
	 * moving it पूर्णांकo the data buffer.
	 */

	dev_vdbg(hsotg->dev, "%s(%p,%p,%d)\n", __func__, hsotg, dest, bytes);

	क्रम (i = 0; i < word_count; i++, data_buf++)
		*data_buf = dwc2_पढ़ोl(hsotg, HCFIFO(0));
पूर्ण

/**
 * dwc2_dump_channel_info() - Prपूर्णांकs the state of a host channel
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Poपूर्णांकer to the channel to dump
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 *
 * NOTE: This function will be हटाओd once the peripheral controller code
 * is पूर्णांकegrated and the driver is stable
 */
अटल व्योम dwc2_dump_channel_info(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_host_chan *chan)
अणु
#अगर_घोषित VERBOSE_DEBUG
	पूर्णांक num_channels = hsotg->params.host_channels;
	काष्ठा dwc2_qh *qh;
	u32 hcअक्षर;
	u32 hcsplt;
	u32 hctsiz;
	u32 hc_dma;
	पूर्णांक i;

	अगर (!chan)
		वापस;

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));
	hcsplt = dwc2_पढ़ोl(hsotg, HCSPLT(chan->hc_num));
	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chan->hc_num));
	hc_dma = dwc2_पढ़ोl(hsotg, HCDMA(chan->hc_num));

	dev_dbg(hsotg->dev, "  Assigned to channel %p:\n", chan);
	dev_dbg(hsotg->dev, "    hcchar 0x%08x, hcsplt 0x%08x\n",
		hcअक्षर, hcsplt);
	dev_dbg(hsotg->dev, "    hctsiz 0x%08x, hc_dma 0x%08x\n",
		hctsiz, hc_dma);
	dev_dbg(hsotg->dev, "    dev_addr: %d, ep_num: %d, ep_is_in: %d\n",
		chan->dev_addr, chan->ep_num, chan->ep_is_in);
	dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
	dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
	dev_dbg(hsotg->dev, "    data_pid_start: %d\n", chan->data_pid_start);
	dev_dbg(hsotg->dev, "    xfer_started: %d\n", chan->xfer_started);
	dev_dbg(hsotg->dev, "    halt_status: %d\n", chan->halt_status);
	dev_dbg(hsotg->dev, "    xfer_buf: %p\n", chan->xfer_buf);
	dev_dbg(hsotg->dev, "    xfer_dma: %08lx\n",
		(अचिन्हित दीर्घ)chan->xfer_dma);
	dev_dbg(hsotg->dev, "    xfer_len: %d\n", chan->xfer_len);
	dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);
	dev_dbg(hsotg->dev, "  NP inactive sched:\n");
	list_क्रम_each_entry(qh, &hsotg->non_periodic_sched_inactive,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP waiting sched:\n");
	list_क्रम_each_entry(qh, &hsotg->non_periodic_sched_रुकोing,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP active sched:\n");
	list_क्रम_each_entry(qh, &hsotg->non_periodic_sched_active,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  Channels:\n");
	क्रम (i = 0; i < num_channels; i++) अणु
		काष्ठा dwc2_host_chan *chan = hsotg->hc_ptr_array[i];

		dev_dbg(hsotg->dev, "    %2d: %p\n", i, chan);
	पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */
पूर्ण

अटल पूर्णांक _dwc2_hcd_start(काष्ठा usb_hcd *hcd);

अटल व्योम dwc2_host_start(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	hcd->self.is_b_host = dwc2_hcd_is_b_host(hsotg);
	_dwc2_hcd_start(hcd);
पूर्ण

अटल व्योम dwc2_host_disconnect(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	hcd->self.is_b_host = 0;
पूर्ण

अटल व्योम dwc2_host_hub_info(काष्ठा dwc2_hsotg *hsotg, व्योम *context,
			       पूर्णांक *hub_addr, पूर्णांक *hub_port)
अणु
	काष्ठा urb *urb = context;

	अगर (urb->dev->tt)
		*hub_addr = urb->dev->tt->hub->devnum;
	अन्यथा
		*hub_addr = 0;
	*hub_port = urb->dev->ttport;
पूर्ण

/*
 * =========================================================================
 *  Low Level Host Channel Access Functions
 * =========================================================================
 */

अटल व्योम dwc2_hc_enable_slave_पूर्णांकs(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_host_chan *chan)
अणु
	u32 hcपूर्णांकmsk = HCINTMSK_CHHLTD;

	चयन (chan->ep_type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
		dev_vdbg(hsotg->dev, "control/bulk\n");
		hcपूर्णांकmsk |= HCINTMSK_XFERCOMPL;
		hcपूर्णांकmsk |= HCINTMSK_STALL;
		hcपूर्णांकmsk |= HCINTMSK_XACTERR;
		hcपूर्णांकmsk |= HCINTMSK_DATATGLERR;
		अगर (chan->ep_is_in) अणु
			hcपूर्णांकmsk |= HCINTMSK_BBLERR;
		पूर्ण अन्यथा अणु
			hcपूर्णांकmsk |= HCINTMSK_NAK;
			hcपूर्णांकmsk |= HCINTMSK_NYET;
			अगर (chan->करो_ping)
				hcपूर्णांकmsk |= HCINTMSK_ACK;
		पूर्ण

		अगर (chan->करो_split) अणु
			hcपूर्णांकmsk |= HCINTMSK_NAK;
			अगर (chan->complete_split)
				hcपूर्णांकmsk |= HCINTMSK_NYET;
			अन्यथा
				hcपूर्णांकmsk |= HCINTMSK_ACK;
		पूर्ण

		अगर (chan->error_state)
			hcपूर्णांकmsk |= HCINTMSK_ACK;
		अवरोध;

	हाल USB_ENDPOINT_XFER_INT:
		अगर (dbg_perio())
			dev_vdbg(hsotg->dev, "intr\n");
		hcपूर्णांकmsk |= HCINTMSK_XFERCOMPL;
		hcपूर्णांकmsk |= HCINTMSK_NAK;
		hcपूर्णांकmsk |= HCINTMSK_STALL;
		hcपूर्णांकmsk |= HCINTMSK_XACTERR;
		hcपूर्णांकmsk |= HCINTMSK_DATATGLERR;
		hcपूर्णांकmsk |= HCINTMSK_FRMOVRUN;

		अगर (chan->ep_is_in)
			hcपूर्णांकmsk |= HCINTMSK_BBLERR;
		अगर (chan->error_state)
			hcपूर्णांकmsk |= HCINTMSK_ACK;
		अगर (chan->करो_split) अणु
			अगर (chan->complete_split)
				hcपूर्णांकmsk |= HCINTMSK_NYET;
			अन्यथा
				hcपूर्णांकmsk |= HCINTMSK_ACK;
		पूर्ण
		अवरोध;

	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (dbg_perio())
			dev_vdbg(hsotg->dev, "isoc\n");
		hcपूर्णांकmsk |= HCINTMSK_XFERCOMPL;
		hcपूर्णांकmsk |= HCINTMSK_FRMOVRUN;
		hcपूर्णांकmsk |= HCINTMSK_ACK;

		अगर (chan->ep_is_in) अणु
			hcपूर्णांकmsk |= HCINTMSK_XACTERR;
			hcपूर्णांकmsk |= HCINTMSK_BBLERR;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(hsotg->dev, "## Unknown EP type ##\n");
		अवरोध;
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hcपूर्णांकmsk, HCINTMSK(chan->hc_num));
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcपूर्णांकmsk);
पूर्ण

अटल व्योम dwc2_hc_enable_dma_पूर्णांकs(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_host_chan *chan)
अणु
	u32 hcपूर्णांकmsk = HCINTMSK_CHHLTD;

	/*
	 * For Descriptor DMA mode core halts the channel on AHB error.
	 * Interrupt is not required.
	 */
	अगर (!hsotg->params.dma_desc_enable) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA disabled\n");
		hcपूर्णांकmsk |= HCINTMSK_AHBERR;
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA enabled\n");
		अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC)
			hcपूर्णांकmsk |= HCINTMSK_XFERCOMPL;
	पूर्ण

	अगर (chan->error_state && !chan->करो_split &&
	    chan->ep_type != USB_ENDPOINT_XFER_ISOC) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "setting ACK\n");
		hcपूर्णांकmsk |= HCINTMSK_ACK;
		अगर (chan->ep_is_in) अणु
			hcपूर्णांकmsk |= HCINTMSK_DATATGLERR;
			अगर (chan->ep_type != USB_ENDPOINT_XFER_INT)
				hcपूर्णांकmsk |= HCINTMSK_NAK;
		पूर्ण
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hcपूर्णांकmsk, HCINTMSK(chan->hc_num));
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcपूर्णांकmsk);
पूर्ण

अटल व्योम dwc2_hc_enable_पूर्णांकs(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_host_chan *chan)
अणु
	u32 पूर्णांकmsk;

	अगर (hsotg->params.host_dma) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabled\n");
		dwc2_hc_enable_dma_पूर्णांकs(hsotg, chan);
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA disabled\n");
		dwc2_hc_enable_slave_पूर्णांकs(hsotg, chan);
	पूर्ण

	/* Enable the top level host channel पूर्णांकerrupt */
	पूर्णांकmsk = dwc2_पढ़ोl(hsotg, HAINTMSK);
	पूर्णांकmsk |= 1 << chan->hc_num;
	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, HAINTMSK);
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HAINTMSK to %08x\n", पूर्णांकmsk);

	/* Make sure host channel पूर्णांकerrupts are enabled */
	पूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	पूर्णांकmsk |= GINTSTS_HCHINT;
	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, GINTMSK);
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set GINTMSK to %08x\n", पूर्णांकmsk);
पूर्ण

/**
 * dwc2_hc_init() - Prepares a host channel क्रम transferring packets to/from
 * a specअगरic endpoपूर्णांक
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel
 *
 * The HCCHARn रेजिस्टर is set up with the अक्षरacteristics specअगरied in chan.
 * Host channel पूर्णांकerrupts that may need to be serviced जबतक this transfer is
 * in progress are enabled.
 */
अटल व्योम dwc2_hc_init(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan)
अणु
	u8 hc_num = chan->hc_num;
	u32 hcपूर्णांकmsk;
	u32 hcअक्षर;
	u32 hcsplt = 0;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* Clear old पूर्णांकerrupt conditions क्रम this host channel */
	hcपूर्णांकmsk = 0xffffffff;
	hcपूर्णांकmsk &= ~HCINTMSK_RESERVED14_31;
	dwc2_ग_लिखोl(hsotg, hcपूर्णांकmsk, HCINT(hc_num));

	/* Enable channel पूर्णांकerrupts required क्रम this transfer */
	dwc2_hc_enable_पूर्णांकs(hsotg, chan);

	/*
	 * Program the HCCHARn रेजिस्टर with the endpoपूर्णांक अक्षरacteristics क्रम
	 * the current transfer
	 */
	hcअक्षर = chan->dev_addr << HCCHAR_DEVADDR_SHIFT & HCCHAR_DEVADDR_MASK;
	hcअक्षर |= chan->ep_num << HCCHAR_EPNUM_SHIFT & HCCHAR_EPNUM_MASK;
	अगर (chan->ep_is_in)
		hcअक्षर |= HCCHAR_EPसूची;
	अगर (chan->speed == USB_SPEED_LOW)
		hcअक्षर |= HCCHAR_LSPDDEV;
	hcअक्षर |= chan->ep_type << HCCHAR_EPTYPE_SHIFT & HCCHAR_EPTYPE_MASK;
	hcअक्षर |= chan->max_packet << HCCHAR_MPS_SHIFT & HCCHAR_MPS_MASK;
	dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(hc_num));
	अगर (dbg_hc(chan)) अणु
		dev_vdbg(hsotg->dev, "set HCCHAR(%d) to %08x\n",
			 hc_num, hcअक्षर);

		dev_vdbg(hsotg->dev, "%s: Channel %d\n",
			 __func__, hc_num);
		dev_vdbg(hsotg->dev, "	 Dev Addr: %d\n",
			 chan->dev_addr);
		dev_vdbg(hsotg->dev, "	 Ep Num: %d\n",
			 chan->ep_num);
		dev_vdbg(hsotg->dev, "	 Is In: %d\n",
			 chan->ep_is_in);
		dev_vdbg(hsotg->dev, "	 Is Low Speed: %d\n",
			 chan->speed == USB_SPEED_LOW);
		dev_vdbg(hsotg->dev, "	 Ep Type: %d\n",
			 chan->ep_type);
		dev_vdbg(hsotg->dev, "	 Max Pkt: %d\n",
			 chan->max_packet);
	पूर्ण

	/* Program the HCSPLT रेजिस्टर क्रम SPLITs */
	अगर (chan->करो_split) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev,
				 "Programming HC %d with split --> %s\n",
				 hc_num,
				 chan->complete_split ? "CSPLIT" : "SSPLIT");
		अगर (chan->complete_split)
			hcsplt |= HCSPLT_COMPSPLT;
		hcsplt |= chan->xact_pos << HCSPLT_XACTPOS_SHIFT &
			  HCSPLT_XACTPOS_MASK;
		hcsplt |= chan->hub_addr << HCSPLT_HUBADDR_SHIFT &
			  HCSPLT_HUBADDR_MASK;
		hcsplt |= chan->hub_port << HCSPLT_PRTADDR_SHIFT &
			  HCSPLT_PRTADDR_MASK;
		अगर (dbg_hc(chan)) अणु
			dev_vdbg(hsotg->dev, "	  comp split %d\n",
				 chan->complete_split);
			dev_vdbg(hsotg->dev, "	  xact pos %d\n",
				 chan->xact_pos);
			dev_vdbg(hsotg->dev, "	  hub addr %d\n",
				 chan->hub_addr);
			dev_vdbg(hsotg->dev, "	  hub port %d\n",
				 chan->hub_port);
			dev_vdbg(hsotg->dev, "	  is_in %d\n",
				 chan->ep_is_in);
			dev_vdbg(hsotg->dev, "	  Max Pkt %d\n",
				 chan->max_packet);
			dev_vdbg(hsotg->dev, "	  xferlen %d\n",
				 chan->xfer_len);
		पूर्ण
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hcsplt, HCSPLT(hc_num));
पूर्ण

/**
 * dwc2_hc_halt() - Attempts to halt a host channel
 *
 * @hsotg:       Controller रेजिस्टर पूर्णांकerface
 * @chan:        Host channel to halt
 * @halt_status: Reason क्रम halting the channel
 *
 * This function should only be called in Slave mode or to पात a transfer in
 * either Slave mode or DMA mode. Under normal circumstances in DMA mode, the
 * controller halts the channel when the transfer is complete or a condition
 * occurs that requires application पूर्णांकervention.
 *
 * In slave mode, checks क्रम a मुक्त request queue entry, then sets the Channel
 * Enable and Channel Disable bits of the Host Channel Characteristics
 * रेजिस्टर of the specअगरied channel to पूर्णांकiate the halt. If there is no मुक्त
 * request queue entry, sets only the Channel Disable bit of the HCCHARn
 * रेजिस्टर to flush requests क्रम this channel. In the latter हाल, sets a
 * flag to indicate that the host channel needs to be halted when a request
 * queue slot is खोलो.
 *
 * In DMA mode, always sets the Channel Enable and Channel Disable bits of the
 * HCCHARn रेजिस्टर. The controller ensures there is space in the request
 * queue beक्रमe submitting the halt request.
 *
 * Some समय may elapse beक्रमe the core flushes any posted requests क्रम this
 * host channel and halts. The Channel Halted पूर्णांकerrupt handler completes the
 * deactivation of the host channel.
 */
व्योम dwc2_hc_halt(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan,
		  क्रमागत dwc2_halt_status halt_status)
अणु
	u32 nptxsts, hptxsts, hcअक्षर;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * In buffer DMA or बाह्यal DMA mode channel can't be halted
	 * क्रम non-split periodic channels. At the end of the next
	 * uframe/frame (in the worst हाल), the core generates a channel
	 * halted and disables the channel स्वतःmatically.
	 */
	अगर ((hsotg->params.g_dma && !hsotg->params.g_dma_desc) ||
	    hsotg->hw_params.arch == GHWCFG2_EXT_DMA_ARCH) अणु
		अगर (!chan->करो_split &&
		    (chan->ep_type == USB_ENDPOINT_XFER_ISOC ||
		     chan->ep_type == USB_ENDPOINT_XFER_INT)) अणु
			dev_err(hsotg->dev, "%s() Channel can't be halted\n",
				__func__);
			वापस;
		पूर्ण
	पूर्ण

	अगर (halt_status == DWC2_HC_XFER_NO_HALT_STATUS)
		dev_err(hsotg->dev, "!!! halt_status = %d !!!\n", halt_status);

	अगर (halt_status == DWC2_HC_XFER_URB_DEQUEUE ||
	    halt_status == DWC2_HC_XFER_AHB_ERR) अणु
		/*
		 * Disable all channel पूर्णांकerrupts except Ch Halted. The QTD
		 * and QH state associated with this transfer has been cleared
		 * (in the हाल of URB_DEQUEUE), so the channel needs to be
		 * shut करोwn carefully to prevent crashes.
		 */
		u32 hcपूर्णांकmsk = HCINTMSK_CHHLTD;

		dev_vdbg(hsotg->dev, "dequeue/error\n");
		dwc2_ग_लिखोl(hsotg, hcपूर्णांकmsk, HCINTMSK(chan->hc_num));

		/*
		 * Make sure no other पूर्णांकerrupts besides halt are currently
		 * pending. Handling another पूर्णांकerrupt could cause a crash due
		 * to the QTD and QH state.
		 */
		dwc2_ग_लिखोl(hsotg, ~hcपूर्णांकmsk, HCINT(chan->hc_num));

		/*
		 * Make sure the halt status is set to URB_DEQUEUE or AHB_ERR
		 * even अगर the channel was alपढ़ोy halted क्रम some other
		 * reason
		 */
		chan->halt_status = halt_status;

		hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));
		अगर (!(hcअक्षर & HCCHAR_CHENA)) अणु
			/*
			 * The channel is either alपढ़ोy halted or it hasn't
			 * started yet. In DMA mode, the transfer may halt अगर
			 * it finishes normally or a condition occurs that
			 * requires driver पूर्णांकervention. Don't want to halt
			 * the channel again. In either Slave or DMA mode,
			 * it's possible that the transfer has been asचिन्हित
			 * to a channel, but not started yet when an URB is
			 * dequeued. Don't want to halt a channel that hasn't
			 * started yet.
			 */
			वापस;
		पूर्ण
	पूर्ण
	अगर (chan->halt_pending) अणु
		/*
		 * A halt has alपढ़ोy been issued क्रम this channel. This might
		 * happen when a transfer is पातed by a higher level in
		 * the stack.
		 */
		dev_vdbg(hsotg->dev,
			 "*** %s: Channel %d, chan->halt_pending already set ***\n",
			 __func__, chan->hc_num);
		वापस;
	पूर्ण

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));

	/* No need to set the bit in DDMA क्रम disabling the channel */
	/* TODO check it everywhere channel is disabled */
	अगर (!hsotg->params.dma_desc_enable) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA disabled\n");
		hcअक्षर |= HCCHAR_CHENA;
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_dbg(hsotg->dev, "desc DMA enabled\n");
	पूर्ण
	hcअक्षर |= HCCHAR_CHDIS;

	अगर (!hsotg->params.host_dma) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA not enabled\n");
		hcअक्षर |= HCCHAR_CHENA;

		/* Check क्रम space in the request queue to issue the halt */
		अगर (chan->ep_type == USB_ENDPOINT_XFER_CONTROL ||
		    chan->ep_type == USB_ENDPOINT_XFER_BULK) अणु
			dev_vdbg(hsotg->dev, "control/bulk\n");
			nptxsts = dwc2_पढ़ोl(hsotg, GNPTXSTS);
			अगर ((nptxsts & TXSTS_QSPCAVAIL_MASK) == 0) अणु
				dev_vdbg(hsotg->dev, "Disabling channel\n");
				hcअक्षर &= ~HCCHAR_CHENA;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (dbg_perio())
				dev_vdbg(hsotg->dev, "isoc/intr\n");
			hptxsts = dwc2_पढ़ोl(hsotg, HPTXSTS);
			अगर ((hptxsts & TXSTS_QSPCAVAIL_MASK) == 0 ||
			    hsotg->queuing_high_bandwidth) अणु
				अगर (dbg_perio())
					dev_vdbg(hsotg->dev, "Disabling channel\n");
				hcअक्षर &= ~HCCHAR_CHENA;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabled\n");
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(chan->hc_num));
	chan->halt_status = halt_status;

	अगर (hcअक्षर & HCCHAR_CHENA) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Channel enabled\n");
		chan->halt_pending = 1;
		chan->halt_on_queue = 0;
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Channel disabled\n");
		chan->halt_on_queue = 1;
	पूर्ण

	अगर (dbg_hc(chan)) अणु
		dev_vdbg(hsotg->dev, "%s: Channel %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 hcchar: 0x%08x\n",
			 hcअक्षर);
		dev_vdbg(hsotg->dev, "	 halt_pending: %d\n",
			 chan->halt_pending);
		dev_vdbg(hsotg->dev, "	 halt_on_queue: %d\n",
			 chan->halt_on_queue);
		dev_vdbg(hsotg->dev, "	 halt_status: %d\n",
			 chan->halt_status);
	पूर्ण
पूर्ण

/**
 * dwc2_hc_cleanup() - Clears the transfer state क्रम a host channel
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Identअगरies the host channel to clean up
 *
 * This function is normally called after a transfer is करोne and the host
 * channel is being released
 */
व्योम dwc2_hc_cleanup(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan)
अणु
	u32 hcपूर्णांकmsk;

	chan->xfer_started = 0;

	list_del_init(&chan->split_order_list_entry);

	/*
	 * Clear channel पूर्णांकerrupt enables and any unhandled channel पूर्णांकerrupt
	 * conditions
	 */
	dwc2_ग_लिखोl(hsotg, 0, HCINTMSK(chan->hc_num));
	hcपूर्णांकmsk = 0xffffffff;
	hcपूर्णांकmsk &= ~HCINTMSK_RESERVED14_31;
	dwc2_ग_लिखोl(hsotg, hcपूर्णांकmsk, HCINT(chan->hc_num));
पूर्ण

/**
 * dwc2_hc_set_even_odd_frame() - Sets the channel property that indicates in
 * which frame a periodic transfer should occur
 *
 * @hsotg:  Programming view of DWC_otg controller
 * @chan:   Identअगरies the host channel to set up and its properties
 * @hcअक्षर: Current value of the HCCHAR रेजिस्टर क्रम the specअगरied host channel
 *
 * This function has no effect on non-periodic transfers
 */
अटल व्योम dwc2_hc_set_even_odd_frame(काष्ठा dwc2_hsotg *hsotg,
				       काष्ठा dwc2_host_chan *chan, u32 *hcअक्षर)
अणु
	अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
	    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
		पूर्णांक host_speed;
		पूर्णांक xfer_ns;
		पूर्णांक xfer_us;
		पूर्णांक bytes_in_fअगरo;
		u16 fअगरo_space;
		u16 frame_number;
		u16 wire_frame;

		/*
		 * Try to figure out अगर we're an even or odd frame. If we set
		 * even and the current frame number is even the the transfer
		 * will happen immediately.  Similar अगर both are odd. If one is
		 * even and the other is odd then the transfer will happen when
		 * the frame number ticks.
		 *
		 * There's a bit of a balancing act to get this right.
		 * Someबार we may want to send data in the current frame (AK
		 * right away).  We might want to करो this अगर the frame number
		 * _just_ ticked, but we might also want to करो this in order
		 * to जारी a split transaction that happened late in a
		 * microframe (so we didn't know to queue the next transfer
		 * until the frame number had ticked).  The problem is that we
		 * need a lot of knowledge to know अगर there's actually still
		 * समय to send things or अगर it would be better to रुको until
		 * the next frame.
		 *
		 * We can look at how much समय is left in the current frame
		 * and make a guess about whether we'll have समय to transfer.
		 * We'll करो that.
		 */

		/* Get speed host is running at */
		host_speed = (chan->speed != USB_SPEED_HIGH &&
			      !chan->करो_split) ? chan->speed : USB_SPEED_HIGH;

		/* See how many bytes are in the periodic FIFO right now */
		fअगरo_space = (dwc2_पढ़ोl(hsotg, HPTXSTS) &
			      TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT;
		bytes_in_fअगरo = माप(u32) *
				(hsotg->params.host_perio_tx_fअगरo_size -
				 fअगरo_space);

		/*
		 * Roughly estimate bus समय क्रम everything in the periodic
		 * queue + our new transfer.  This is "rough" because we're
		 * using a function that makes takes पूर्णांकo account IN/OUT
		 * and INT/ISO and we're just slamming in one value क्रम all
		 * transfers.  This should be an over-estimate and that should
		 * be OK, but we can probably tighten it.
		 */
		xfer_ns = usb_calc_bus_समय(host_speed, false, false,
					    chan->xfer_len + bytes_in_fअगरo);
		xfer_us = NS_TO_US(xfer_ns);

		/* See what frame number we'll be at by the समय we finish */
		frame_number = dwc2_hcd_get_future_frame_number(hsotg, xfer_us);

		/* This is when we were scheduled to be on the wire */
		wire_frame = dwc2_frame_num_inc(chan->qh->next_active_frame, 1);

		/*
		 * If we'd finish _after_ the frame we're scheduled in then
		 * it's hopeless.  Just schedule right away and hope क्रम the
		 * best.  Note that it _might_ be wise to call back पूर्णांकo the
		 * scheduler to pick a better frame, but this is better than
		 * nothing.
		 */
		अगर (dwc2_frame_num_gt(frame_number, wire_frame)) अणु
			dwc2_sch_vdbg(hsotg,
				      "QH=%p EO MISS fr=%04x=>%04x (%+d)\n",
				      chan->qh, wire_frame, frame_number,
				      dwc2_frame_num_dec(frame_number,
							 wire_frame));
			wire_frame = frame_number;

			/*
			 * We picked a dअगरferent frame number; communicate this
			 * back to the scheduler so it करोesn't try to schedule
			 * another in the same frame.
			 *
			 * Remember that next_active_frame is 1 beक्रमe the wire
			 * frame.
			 */
			chan->qh->next_active_frame =
				dwc2_frame_num_dec(frame_number, 1);
		पूर्ण

		अगर (wire_frame & 1)
			*hcअक्षर |= HCCHAR_ODDFRM;
		अन्यथा
			*hcअक्षर &= ~HCCHAR_ODDFRM;
	पूर्ण
पूर्ण

अटल व्योम dwc2_set_pid_isoc(काष्ठा dwc2_host_chan *chan)
अणु
	/* Set up the initial PID क्रम the transfer */
	अगर (chan->speed == USB_SPEED_HIGH) अणु
		अगर (chan->ep_is_in) अणु
			अगर (chan->multi_count == 1)
				chan->data_pid_start = DWC2_HC_PID_DATA0;
			अन्यथा अगर (chan->multi_count == 2)
				chan->data_pid_start = DWC2_HC_PID_DATA1;
			अन्यथा
				chan->data_pid_start = DWC2_HC_PID_DATA2;
		पूर्ण अन्यथा अणु
			अगर (chan->multi_count == 1)
				chan->data_pid_start = DWC2_HC_PID_DATA0;
			अन्यथा
				chan->data_pid_start = DWC2_HC_PID_MDATA;
		पूर्ण
	पूर्ण अन्यथा अणु
		chan->data_pid_start = DWC2_HC_PID_DATA0;
	पूर्ण
पूर्ण

/**
 * dwc2_hc_ग_लिखो_packet() - Writes a packet पूर्णांकo the Tx FIFO associated with
 * the Host Channel
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel
 *
 * This function should only be called in Slave mode. For a channel associated
 * with a non-periodic EP, the non-periodic Tx FIFO is written. For a channel
 * associated with a periodic EP, the periodic Tx FIFO is written.
 *
 * Upon वापस the xfer_buf and xfer_count fields in chan are incremented by
 * the number of bytes written to the Tx FIFO.
 */
अटल व्योम dwc2_hc_ग_लिखो_packet(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan)
अणु
	u32 i;
	u32 reमुख्यing_count;
	u32 byte_count;
	u32 dword_count;
	u32 *data_buf = (u32 *)chan->xfer_buf;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	reमुख्यing_count = chan->xfer_len - chan->xfer_count;
	अगर (reमुख्यing_count > chan->max_packet)
		byte_count = chan->max_packet;
	अन्यथा
		byte_count = reमुख्यing_count;

	dword_count = (byte_count + 3) / 4;

	अगर (((अचिन्हित दीर्घ)data_buf & 0x3) == 0) अणु
		/* xfer_buf is DWORD aligned */
		क्रम (i = 0; i < dword_count; i++, data_buf++)
			dwc2_ग_लिखोl(hsotg, *data_buf, HCFIFO(chan->hc_num));
	पूर्ण अन्यथा अणु
		/* xfer_buf is not DWORD aligned */
		क्रम (i = 0; i < dword_count; i++, data_buf++) अणु
			u32 data = data_buf[0] | data_buf[1] << 8 |
				   data_buf[2] << 16 | data_buf[3] << 24;
			dwc2_ग_लिखोl(hsotg, data, HCFIFO(chan->hc_num));
		पूर्ण
	पूर्ण

	chan->xfer_count += byte_count;
	chan->xfer_buf += byte_count;
पूर्ण

/**
 * dwc2_hc_करो_ping() - Starts a PING transfer
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel
 *
 * This function should only be called in Slave mode. The Do Ping bit is set in
 * the HCTSIZ रेजिस्टर, then the channel is enabled.
 */
अटल व्योम dwc2_hc_करो_ping(काष्ठा dwc2_hsotg *hsotg,
			    काष्ठा dwc2_host_chan *chan)
अणु
	u32 hcअक्षर;
	u32 hctsiz;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s: Channel %d\n", __func__,
			 chan->hc_num);

	hctsiz = TSIZ_DOPNG;
	hctsiz |= 1 << TSIZ_PKTCNT_SHIFT;
	dwc2_ग_लिखोl(hsotg, hctsiz, HCTSIZ(chan->hc_num));

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));
	hcअक्षर |= HCCHAR_CHENA;
	hcअक्षर &= ~HCCHAR_CHDIS;
	dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(chan->hc_num));
पूर्ण

/**
 * dwc2_hc_start_transfer() - Does the setup क्रम a data transfer क्रम a host
 * channel and starts the transfer
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel. The xfer_len value
 *         may be reduced to accommodate the max widths of the XferSize and
 *         PktCnt fields in the HCTSIZn रेजिस्टर. The multi_count value may be
 *         changed to reflect the final xfer_len value.
 *
 * This function may be called in either Slave mode or DMA mode. In Slave mode,
 * the caller must ensure that there is sufficient space in the request queue
 * and Tx Data FIFO.
 *
 * For an OUT transfer in Slave mode, it loads a data packet पूर्णांकo the
 * appropriate FIFO. If necessary, additional data packets are loaded in the
 * Host ISR.
 *
 * For an IN transfer in Slave mode, a data packet is requested. The data
 * packets are unloaded from the Rx FIFO in the Host ISR. If necessary,
 * additional data packets are requested in the Host ISR.
 *
 * For a PING transfer in Slave mode, the Do Ping bit is set in the HCTSIZ
 * रेजिस्टर aदीर्घ with a packet count of 1 and the channel is enabled. This
 * causes a single PING transaction to occur. Other fields in HCTSIZ are
 * simply set to 0 since no data transfer occurs in this हाल.
 *
 * For a PING transfer in DMA mode, the HCTSIZ रेजिस्टर is initialized with
 * all the inक्रमmation required to perक्रमm the subsequent data transfer. In
 * addition, the Do Ping bit is set in the HCTSIZ रेजिस्टर. In this हाल, the
 * controller perक्रमms the entire PING protocol, then starts the data
 * transfer.
 */
अटल व्योम dwc2_hc_start_transfer(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_host_chan *chan)
अणु
	u32 max_hc_xfer_size = hsotg->params.max_transfer_size;
	u16 max_hc_pkt_count = hsotg->params.max_packet_count;
	u32 hcअक्षर;
	u32 hctsiz = 0;
	u16 num_packets;
	u32 ec_mc;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	अगर (chan->करो_ping) अणु
		अगर (!hsotg->params.host_dma) अणु
			अगर (dbg_hc(chan))
				dev_vdbg(hsotg->dev, "ping, no DMA\n");
			dwc2_hc_करो_ping(hsotg, chan);
			chan->xfer_started = 1;
			वापस;
		पूर्ण

		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "ping, DMA\n");

		hctsiz |= TSIZ_DOPNG;
	पूर्ण

	अगर (chan->करो_split) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "split\n");
		num_packets = 1;

		अगर (chan->complete_split && !chan->ep_is_in)
			/*
			 * For CSPLIT OUT Transfer, set the size to 0 so the
			 * core करोesn't expect any data written to the FIFO
			 */
			chan->xfer_len = 0;
		अन्यथा अगर (chan->ep_is_in || chan->xfer_len > chan->max_packet)
			chan->xfer_len = chan->max_packet;
		अन्यथा अगर (!chan->ep_is_in && chan->xfer_len > 188)
			chan->xfer_len = 188;

		hctsiz |= chan->xfer_len << TSIZ_XFERSIZE_SHIFT &
			  TSIZ_XFERSIZE_MASK;

		/* For split set ec_mc क्रम immediate retries */
		अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC)
			ec_mc = 3;
		अन्यथा
			ec_mc = 1;
	पूर्ण अन्यथा अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "no split\n");
		/*
		 * Ensure that the transfer length and packet count will fit
		 * in the widths allocated क्रम them in the HCTSIZn रेजिस्टर
		 */
		अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
			/*
			 * Make sure the transfer size is no larger than one
			 * (micro)frame's worth of data. (A check was करोne
			 * when the periodic transfer was accepted to ensure
			 * that a (micro)frame's worth of data can be
			 * programmed पूर्णांकo a channel.)
			 */
			u32 max_periodic_len =
				chan->multi_count * chan->max_packet;

			अगर (chan->xfer_len > max_periodic_len)
				chan->xfer_len = max_periodic_len;
		पूर्ण अन्यथा अगर (chan->xfer_len > max_hc_xfer_size) अणु
			/*
			 * Make sure that xfer_len is a multiple of max packet
			 * size
			 */
			chan->xfer_len =
				max_hc_xfer_size - chan->max_packet + 1;
		पूर्ण

		अगर (chan->xfer_len > 0) अणु
			num_packets = (chan->xfer_len + chan->max_packet - 1) /
					chan->max_packet;
			अगर (num_packets > max_hc_pkt_count) अणु
				num_packets = max_hc_pkt_count;
				chan->xfer_len = num_packets * chan->max_packet;
			पूर्ण अन्यथा अगर (chan->ep_is_in) अणु
				/*
				 * Always program an पूर्णांकegral # of max packets
				 * क्रम IN transfers.
				 * Note: This assumes that the input buffer is
				 * aligned and sized accordingly.
				 */
				chan->xfer_len = num_packets * chan->max_packet;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Need 1 packet क्रम transfer length of 0 */
			num_packets = 1;
		पूर्ण

		अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC)
			/*
			 * Make sure that the multi_count field matches the
			 * actual transfer length
			 */
			chan->multi_count = num_packets;

		अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC)
			dwc2_set_pid_isoc(chan);

		hctsiz |= chan->xfer_len << TSIZ_XFERSIZE_SHIFT &
			  TSIZ_XFERSIZE_MASK;

		/* The ec_mc माला_लो the multi_count क्रम non-split */
		ec_mc = chan->multi_count;
	पूर्ण

	chan->start_pkt_count = num_packets;
	hctsiz |= num_packets << TSIZ_PKTCNT_SHIFT & TSIZ_PKTCNT_MASK;
	hctsiz |= chan->data_pid_start << TSIZ_SC_MC_PID_SHIFT &
		  TSIZ_SC_MC_PID_MASK;
	dwc2_ग_लिखोl(hsotg, hctsiz, HCTSIZ(chan->hc_num));
	अगर (dbg_hc(chan)) अणु
		dev_vdbg(hsotg->dev, "Wrote %08x to HCTSIZ(%d)\n",
			 hctsiz, chan->hc_num);

		dev_vdbg(hsotg->dev, "%s: Channel %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 Xfer Size: %d\n",
			 (hctsiz & TSIZ_XFERSIZE_MASK) >>
			 TSIZ_XFERSIZE_SHIFT);
		dev_vdbg(hsotg->dev, "	 Num Pkts: %d\n",
			 (hctsiz & TSIZ_PKTCNT_MASK) >>
			 TSIZ_PKTCNT_SHIFT);
		dev_vdbg(hsotg->dev, "	 Start PID: %d\n",
			 (hctsiz & TSIZ_SC_MC_PID_MASK) >>
			 TSIZ_SC_MC_PID_SHIFT);
	पूर्ण

	अगर (hsotg->params.host_dma) अणु
		dma_addr_t dma_addr;

		अगर (chan->align_buf) अणु
			अगर (dbg_hc(chan))
				dev_vdbg(hsotg->dev, "align_buf\n");
			dma_addr = chan->align_buf;
		पूर्ण अन्यथा अणु
			dma_addr = chan->xfer_dma;
		पूर्ण
		dwc2_ग_लिखोl(hsotg, (u32)dma_addr, HCDMA(chan->hc_num));

		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Wrote %08lx to HCDMA(%d)\n",
				 (अचिन्हित दीर्घ)dma_addr, chan->hc_num);
	पूर्ण

	/* Start the split */
	अगर (chan->करो_split) अणु
		u32 hcsplt = dwc2_पढ़ोl(hsotg, HCSPLT(chan->hc_num));

		hcsplt |= HCSPLT_SPLTENA;
		dwc2_ग_लिखोl(hsotg, hcsplt, HCSPLT(chan->hc_num));
	पूर्ण

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));
	hcअक्षर &= ~HCCHAR_MULTICNT_MASK;
	hcअक्षर |= (ec_mc << HCCHAR_MULTICNT_SHIFT) & HCCHAR_MULTICNT_MASK;
	dwc2_hc_set_even_odd_frame(hsotg, chan, &hcअक्षर);

	अगर (hcअक्षर & HCCHAR_CHDIS)
		dev_warn(hsotg->dev,
			 "%s: chdis set, channel %d, hcchar 0x%08x\n",
			 __func__, chan->hc_num, hcअक्षर);

	/* Set host channel enable after all other setup is complete */
	hcअक्षर |= HCCHAR_CHENA;
	hcअक्षर &= ~HCCHAR_CHDIS;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "	 Multi Cnt: %d\n",
			 (hcअक्षर & HCCHAR_MULTICNT_MASK) >>
			 HCCHAR_MULTICNT_SHIFT);

	dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(chan->hc_num));
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wrote %08x to HCCHAR(%d)\n", hcअक्षर,
			 chan->hc_num);

	chan->xfer_started = 1;
	chan->requests++;

	अगर (!hsotg->params.host_dma &&
	    !chan->ep_is_in && chan->xfer_len > 0)
		/* Load OUT packet पूर्णांकo the appropriate Tx FIFO */
		dwc2_hc_ग_लिखो_packet(hsotg, chan);
पूर्ण

/**
 * dwc2_hc_start_transfer_ddma() - Does the setup क्रम a data transfer क्रम a
 * host channel and starts the transfer in Descriptor DMA mode
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel
 *
 * Initializes HCTSIZ रेजिस्टर. For a PING transfer the Do Ping bit is set.
 * Sets PID and NTD values. For periodic transfers initializes SCHED_INFO field
 * with micro-frame biपंचांगap.
 *
 * Initializes HCDMA रेजिस्टर with descriptor list address and CTD value then
 * starts the transfer via enabling the channel.
 */
व्योम dwc2_hc_start_transfer_ddma(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan)
अणु
	u32 hcअक्षर;
	u32 hctsiz = 0;

	अगर (chan->करो_ping)
		hctsiz |= TSIZ_DOPNG;

	अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC)
		dwc2_set_pid_isoc(chan);

	/* Packet Count and Xfer Size are not used in Descriptor DMA mode */
	hctsiz |= chan->data_pid_start << TSIZ_SC_MC_PID_SHIFT &
		  TSIZ_SC_MC_PID_MASK;

	/* 0 - 1 descriptor, 1 - 2 descriptors, etc */
	hctsiz |= (chan->ntd - 1) << TSIZ_NTD_SHIFT & TSIZ_NTD_MASK;

	/* Non-zero only क्रम high-speed पूर्णांकerrupt endpoपूर्णांकs */
	hctsiz |= chan->schinfo << TSIZ_SCHINFO_SHIFT & TSIZ_SCHINFO_MASK;

	अगर (dbg_hc(chan)) अणु
		dev_vdbg(hsotg->dev, "%s: Channel %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 Start PID: %d\n",
			 chan->data_pid_start);
		dev_vdbg(hsotg->dev, "	 NTD: %d\n", chan->ntd - 1);
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hctsiz, HCTSIZ(chan->hc_num));

	dma_sync_single_क्रम_device(hsotg->dev, chan->desc_list_addr,
				   chan->desc_list_sz, DMA_TO_DEVICE);

	dwc2_ग_लिखोl(hsotg, chan->desc_list_addr, HCDMA(chan->hc_num));

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wrote %pad to HCDMA(%d)\n",
			 &chan->desc_list_addr, chan->hc_num);

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));
	hcअक्षर &= ~HCCHAR_MULTICNT_MASK;
	hcअक्षर |= chan->multi_count << HCCHAR_MULTICNT_SHIFT &
		  HCCHAR_MULTICNT_MASK;

	अगर (hcअक्षर & HCCHAR_CHDIS)
		dev_warn(hsotg->dev,
			 "%s: chdis set, channel %d, hcchar 0x%08x\n",
			 __func__, chan->hc_num, hcअक्षर);

	/* Set host channel enable after all other setup is complete */
	hcअक्षर |= HCCHAR_CHENA;
	hcअक्षर &= ~HCCHAR_CHDIS;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "	 Multi Cnt: %d\n",
			 (hcअक्षर & HCCHAR_MULTICNT_MASK) >>
			 HCCHAR_MULTICNT_SHIFT);

	dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(chan->hc_num));
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wrote %08x to HCCHAR(%d)\n", hcअक्षर,
			 chan->hc_num);

	chan->xfer_started = 1;
	chan->requests++;
पूर्ण

/**
 * dwc2_hc_जारी_transfer() - Continues a data transfer that was started by
 * a previous call to dwc2_hc_start_transfer()
 *
 * @hsotg: Programming view of DWC_otg controller
 * @chan:  Inक्रमmation needed to initialize the host channel
 *
 * The caller must ensure there is sufficient space in the request queue and Tx
 * Data FIFO. This function should only be called in Slave mode. In DMA mode,
 * the controller acts स्वतःnomously to complete transfers programmed to a host
 * channel.
 *
 * For an OUT transfer, a new data packet is loaded पूर्णांकo the appropriate FIFO
 * अगर there is any data reमुख्यing to be queued. For an IN transfer, another
 * data packet is always requested. For the SETUP phase of a control transfer,
 * this function करोes nothing.
 *
 * Return: 1 अगर a new request is queued, 0 अगर no more requests are required
 * क्रम this transfer
 */
अटल पूर्णांक dwc2_hc_जारी_transfer(काष्ठा dwc2_hsotg *hsotg,
				     काष्ठा dwc2_host_chan *chan)
अणु
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s: Channel %d\n", __func__,
			 chan->hc_num);

	अगर (chan->करो_split)
		/* SPLITs always queue just once per channel */
		वापस 0;

	अगर (chan->data_pid_start == DWC2_HC_PID_SETUP)
		/* SETUPs are queued only once since they can't be NAK'd */
		वापस 0;

	अगर (chan->ep_is_in) अणु
		/*
		 * Always queue another request क्रम other IN transfers. If
		 * back-to-back INs are issued and NAKs are received क्रम both,
		 * the driver may still be processing the first NAK when the
		 * second NAK is received. When the पूर्णांकerrupt handler clears
		 * the NAK पूर्णांकerrupt क्रम the first NAK, the second NAK will
		 * not be seen. So we can't depend on the NAK पूर्णांकerrupt
		 * handler to requeue a NAK'd request. Instead, IN requests
		 * are issued each समय this function is called. When the
		 * transfer completes, the extra requests क्रम the channel will
		 * be flushed.
		 */
		u32 hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chan->hc_num));

		dwc2_hc_set_even_odd_frame(hsotg, chan, &hcअक्षर);
		hcअक्षर |= HCCHAR_CHENA;
		hcअक्षर &= ~HCCHAR_CHDIS;
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "	 IN xfer: hcchar = 0x%08x\n",
				 hcअक्षर);
		dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(chan->hc_num));
		chan->requests++;
		वापस 1;
	पूर्ण

	/* OUT transfers */

	अगर (chan->xfer_count < chan->xfer_len) अणु
		अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
			u32 hcअक्षर = dwc2_पढ़ोl(hsotg,
						HCCHAR(chan->hc_num));

			dwc2_hc_set_even_odd_frame(hsotg, chan,
						   &hcअक्षर);
		पूर्ण

		/* Load OUT packet पूर्णांकo the appropriate Tx FIFO */
		dwc2_hc_ग_लिखो_packet(hsotg, chan);
		chan->requests++;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * =========================================================================
 *  HCD
 * =========================================================================
 */

/*
 * Processes all the URBs in a single list of QHs. Completes them with
 * -ETIMEDOUT and मुक्तs the QTD.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल व्योम dwc2_समाप्त_urbs_in_qh_list(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा list_head *qh_list)
अणु
	काष्ठा dwc2_qh *qh, *qh_पंचांगp;
	काष्ठा dwc2_qtd *qtd, *qtd_पंचांगp;

	list_क्रम_each_entry_safe(qh, qh_पंचांगp, qh_list, qh_list_entry) अणु
		list_क्रम_each_entry_safe(qtd, qtd_पंचांगp, &qh->qtd_list,
					 qtd_list_entry) अणु
			dwc2_host_complete(hsotg, qtd, -ECONNRESET);
			dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dwc2_qh_list_मुक्त(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा list_head *qh_list)
अणु
	काष्ठा dwc2_qtd *qtd, *qtd_पंचांगp;
	काष्ठा dwc2_qh *qh, *qh_पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!qh_list->next)
		/* The list hasn't been initialized yet */
		वापस;

	spin_lock_irqsave(&hsotg->lock, flags);

	/* Ensure there are no QTDs or URBs left */
	dwc2_समाप्त_urbs_in_qh_list(hsotg, qh_list);

	list_क्रम_each_entry_safe(qh, qh_पंचांगp, qh_list, qh_list_entry) अणु
		dwc2_hcd_qh_unlink(hsotg, qh);

		/* Free each QTD in the QH's QTD list */
		list_क्रम_each_entry_safe(qtd, qtd_पंचांगp, &qh->qtd_list,
					 qtd_list_entry)
			dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);

		अगर (qh->channel && qh->channel->qh == qh)
			qh->channel->qh = शून्य;

		spin_unlock_irqrestore(&hsotg->lock, flags);
		dwc2_hcd_qh_मुक्त(hsotg, qh);
		spin_lock_irqsave(&hsotg->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

/*
 * Responds with an error status of -ETIMEDOUT to all URBs in the non-periodic
 * and periodic schedules. The QTD associated with each URB is हटाओd from
 * the schedule and मुक्तd. This function may be called when a disconnect is
 * detected or when the HCD is being stopped.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल व्योम dwc2_समाप्त_all_urbs(काष्ठा dwc2_hsotg *hsotg)
अणु
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_inactive);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_रुकोing);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_active);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_inactive);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_पढ़ोy);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_asचिन्हित);
	dwc2_समाप्त_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_queued);
पूर्ण

/**
 * dwc2_hcd_start() - Starts the HCD when चयनing to Host mode
 *
 * @hsotg: Poपूर्णांकer to काष्ठा dwc2_hsotg
 */
व्योम dwc2_hcd_start(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hprt0;

	अगर (hsotg->op_state == OTG_STATE_B_HOST) अणु
		/*
		 * Reset the port. During a HNP mode चयन the reset
		 * needs to occur within 1ms and have a duration of at
		 * least 50ms.
		 */
		hprt0 = dwc2_पढ़ो_hprt0(hsotg);
		hprt0 |= HPRT0_RST;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	पूर्ण

	queue_delayed_work(hsotg->wq_otg, &hsotg->start_work,
			   msecs_to_jअगरfies(50));
पूर्ण

/* Must be called with पूर्णांकerrupt disabled and spinlock held */
अटल व्योम dwc2_hcd_cleanup_channels(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक num_channels = hsotg->params.host_channels;
	काष्ठा dwc2_host_chan *channel;
	u32 hcअक्षर;
	पूर्णांक i;

	अगर (!hsotg->params.host_dma) अणु
		/* Flush out any channel requests in slave mode */
		क्रम (i = 0; i < num_channels; i++) अणु
			channel = hsotg->hc_ptr_array[i];
			अगर (!list_empty(&channel->hc_list_entry))
				जारी;
			hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(i));
			अगर (hcअक्षर & HCCHAR_CHENA) अणु
				hcअक्षर &= ~(HCCHAR_CHENA | HCCHAR_EPसूची);
				hcअक्षर |= HCCHAR_CHDIS;
				dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(i));
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_channels; i++) अणु
		channel = hsotg->hc_ptr_array[i];
		अगर (!list_empty(&channel->hc_list_entry))
			जारी;
		hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(i));
		अगर (hcअक्षर & HCCHAR_CHENA) अणु
			/* Halt the channel */
			hcअक्षर |= HCCHAR_CHDIS;
			dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(i));
		पूर्ण

		dwc2_hc_cleanup(hsotg, channel);
		list_add_tail(&channel->hc_list_entry, &hsotg->मुक्त_hc_list);
		/*
		 * Added क्रम Descriptor DMA to prevent channel द्विगुन cleanup in
		 * release_channel_ddma(), which is called from ep_disable when
		 * device disconnects
		 */
		channel->qh = शून्य;
	पूर्ण
	/* All channels have been मुक्तd, mark them available */
	अगर (hsotg->params.uframe_sched) अणु
		hsotg->available_host_channels =
			hsotg->params.host_channels;
	पूर्ण अन्यथा अणु
		hsotg->non_periodic_channels = 0;
		hsotg->periodic_channels = 0;
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_connect() - Handles connect of the HCD
 *
 * @hsotg: Poपूर्णांकer to काष्ठा dwc2_hsotg
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
व्योम dwc2_hcd_connect(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->lx_state != DWC2_L0)
		usb_hcd_resume_root_hub(hsotg->priv);

	hsotg->flags.b.port_connect_status_change = 1;
	hsotg->flags.b.port_connect_status = 1;
पूर्ण

/**
 * dwc2_hcd_disconnect() - Handles disconnect of the HCD
 *
 * @hsotg: Poपूर्णांकer to काष्ठा dwc2_hsotg
 * @क्रमce: If true, we won't try to reconnect even अगर we see device connected.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
व्योम dwc2_hcd_disconnect(काष्ठा dwc2_hsotg *hsotg, bool क्रमce)
अणु
	u32 पूर्णांकr;
	u32 hprt0;

	/* Set status flags क्रम the hub driver */
	hsotg->flags.b.port_connect_status_change = 1;
	hsotg->flags.b.port_connect_status = 0;

	/*
	 * Shutकरोwn any transfers in process by clearing the Tx FIFO Empty
	 * पूर्णांकerrupt mask and status bits and disabling subsequent host
	 * channel पूर्णांकerrupts.
	 */
	पूर्णांकr = dwc2_पढ़ोl(hsotg, GINTMSK);
	पूर्णांकr &= ~(GINTSTS_NPTXFEMP | GINTSTS_PTXFEMP | GINTSTS_HCHINT);
	dwc2_ग_लिखोl(hsotg, पूर्णांकr, GINTMSK);
	पूर्णांकr = GINTSTS_NPTXFEMP | GINTSTS_PTXFEMP | GINTSTS_HCHINT;
	dwc2_ग_लिखोl(hsotg, पूर्णांकr, GINTSTS);

	/*
	 * Turn off the vbus घातer only अगर the core has transitioned to device
	 * mode. If still in host mode, need to keep घातer on to detect a
	 * reconnection.
	 */
	अगर (dwc2_is_device_mode(hsotg)) अणु
		अगर (hsotg->op_state != OTG_STATE_A_SUSPEND) अणु
			dev_dbg(hsotg->dev, "Disconnect: PortPower off\n");
			dwc2_ग_लिखोl(hsotg, 0, HPRT0);
		पूर्ण

		dwc2_disable_host_पूर्णांकerrupts(hsotg);
	पूर्ण

	/* Respond with an error status to all URBs in the schedule */
	dwc2_समाप्त_all_urbs(hsotg);

	अगर (dwc2_is_host_mode(hsotg))
		/* Clean up any host channels that were in use */
		dwc2_hcd_cleanup_channels(hsotg);

	dwc2_host_disconnect(hsotg);

	/*
	 * Add an extra check here to see अगर we're actually connected but
	 * we करोn't have a detection पूर्णांकerrupt pending.  This can happen अगर:
	 *   1. hardware sees connect
	 *   2. hardware sees disconnect
	 *   3. hardware sees connect
	 *   4. dwc2_port_पूर्णांकr() - clears connect पूर्णांकerrupt
	 *   5. dwc2_handle_common_पूर्णांकr() - calls here
	 *
	 * Without the extra check here we will end calling disconnect
	 * and won't get any future पूर्णांकerrupts to handle the connect.
	 */
	अगर (!क्रमce) अणु
		hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
		अगर (!(hprt0 & HPRT0_CONNDET) && (hprt0 & HPRT0_CONNSTS))
			dwc2_hcd_connect(hsotg);
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_rem_wakeup() - Handles Remote Wakeup
 *
 * @hsotg: Poपूर्णांकer to काष्ठा dwc2_hsotg
 */
अटल व्योम dwc2_hcd_rem_wakeup(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->bus_suspended) अणु
		hsotg->flags.b.port_suspend_change = 1;
		usb_hcd_resume_root_hub(hsotg->priv);
	पूर्ण

	अगर (hsotg->lx_state == DWC2_L1)
		hsotg->flags.b.port_l1_change = 1;
पूर्ण

/**
 * dwc2_hcd_stop() - Halts the DWC_otg host mode operations in a clean manner
 *
 * @hsotg: Poपूर्णांकer to काष्ठा dwc2_hsotg
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
व्योम dwc2_hcd_stop(काष्ठा dwc2_hsotg *hsotg)
अणु
	dev_dbg(hsotg->dev, "DWC OTG HCD STOP\n");

	/*
	 * The root hub should be disconnected beक्रमe this function is called.
	 * The disconnect will clear the QTD lists (via ..._hcd_urb_dequeue)
	 * and the QH lists (via ..._hcd_endpoपूर्णांक_disable).
	 */

	/* Turn off all host-specअगरic पूर्णांकerrupts */
	dwc2_disable_host_पूर्णांकerrupts(hsotg);

	/* Turn off the vbus घातer */
	dev_dbg(hsotg->dev, "PortPower off\n");
	dwc2_ग_लिखोl(hsotg, 0, HPRT0);
पूर्ण

/* Caller must hold driver lock */
अटल पूर्णांक dwc2_hcd_urb_enqueue(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_hcd_urb *urb, काष्ठा dwc2_qh *qh,
				काष्ठा dwc2_qtd *qtd)
अणु
	u32 पूर्णांकr_mask;
	पूर्णांक retval;
	पूर्णांक dev_speed;

	अगर (!hsotg->flags.b.port_connect_status) अणु
		/* No दीर्घer connected */
		dev_err(hsotg->dev, "Not connected\n");
		वापस -ENODEV;
	पूर्ण

	dev_speed = dwc2_host_get_speed(hsotg, urb->priv);

	/* Some configurations cannot support LS traffic on a FS root port */
	अगर ((dev_speed == USB_SPEED_LOW) &&
	    (hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED) &&
	    (hsotg->hw_params.hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI)) अणु
		u32 hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
		u32 prtspd = (hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;

		अगर (prtspd == HPRT0_SPD_FULL_SPEED)
			वापस -ENODEV;
	पूर्ण

	अगर (!qtd)
		वापस -EINVAL;

	dwc2_hcd_qtd_init(qtd, urb);
	retval = dwc2_hcd_qtd_add(hsotg, qtd, qh);
	अगर (retval) अणु
		dev_err(hsotg->dev,
			"DWC OTG HCD URB Enqueue failed adding QTD. Error status %d\n",
			retval);
		वापस retval;
	पूर्ण

	पूर्णांकr_mask = dwc2_पढ़ोl(hsotg, GINTMSK);
	अगर (!(पूर्णांकr_mask & GINTSTS_SOF)) अणु
		क्रमागत dwc2_transaction_type tr_type;

		अगर (qtd->qh->ep_type == USB_ENDPOINT_XFER_BULK &&
		    !(qtd->urb->flags & URB_GIVEBACK_ASAP))
			/*
			 * Do not schedule SG transactions until qtd has
			 * URB_GIVEBACK_ASAP set
			 */
			वापस 0;

		tr_type = dwc2_hcd_select_transactions(hsotg);
		अगर (tr_type != DWC2_TRANSACTION_NONE)
			dwc2_hcd_queue_transactions(hsotg, tr_type);
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with पूर्णांकerrupt disabled and spinlock held */
अटल पूर्णांक dwc2_hcd_urb_dequeue(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_hcd_urb *urb)
अणु
	काष्ठा dwc2_qh *qh;
	काष्ठा dwc2_qtd *urb_qtd;

	urb_qtd = urb->qtd;
	अगर (!urb_qtd) अणु
		dev_dbg(hsotg->dev, "## Urb QTD is NULL ##\n");
		वापस -EINVAL;
	पूर्ण

	qh = urb_qtd->qh;
	अगर (!qh) अणु
		dev_dbg(hsotg->dev, "## Urb QTD QH is NULL ##\n");
		वापस -EINVAL;
	पूर्ण

	urb->priv = शून्य;

	अगर (urb_qtd->in_process && qh->channel) अणु
		dwc2_dump_channel_info(hsotg, qh->channel);

		/* The QTD is in process (it has been asचिन्हित to a channel) */
		अगर (hsotg->flags.b.port_connect_status)
			/*
			 * If still connected (i.e. in host mode), halt the
			 * channel so it can be used क्रम other transfers. If
			 * no दीर्घer connected, the host रेजिस्टरs can't be
			 * written to halt the channel since the core is in
			 * device mode.
			 */
			dwc2_hc_halt(hsotg, qh->channel,
				     DWC2_HC_XFER_URB_DEQUEUE);
	पूर्ण

	/*
	 * Free the QTD and clean up the associated QH. Leave the QH in the
	 * schedule अगर it has any reमुख्यing QTDs.
	 */
	अगर (!hsotg->params.dma_desc_enable) अणु
		u8 in_process = urb_qtd->in_process;

		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, urb_qtd, qh);
		अगर (in_process) अणु
			dwc2_hcd_qh_deactivate(hsotg, qh, 0);
			qh->channel = शून्य;
		पूर्ण अन्यथा अगर (list_empty(&qh->qtd_list)) अणु
			dwc2_hcd_qh_unlink(hsotg, qh);
		पूर्ण
	पूर्ण अन्यथा अणु
		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, urb_qtd, qh);
	पूर्ण

	वापस 0;
पूर्ण

/* Must NOT be called with पूर्णांकerrupt disabled or spinlock held */
अटल पूर्णांक dwc2_hcd_endpoपूर्णांक_disable(काष्ठा dwc2_hsotg *hsotg,
				     काष्ठा usb_host_endpoपूर्णांक *ep, पूर्णांक retry)
अणु
	काष्ठा dwc2_qtd *qtd, *qtd_पंचांगp;
	काष्ठा dwc2_qh *qh;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&hsotg->lock, flags);

	qh = ep->hcpriv;
	अगर (!qh) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	जबतक (!list_empty(&qh->qtd_list) && retry--) अणु
		अगर (retry == 0) अणु
			dev_err(hsotg->dev,
				"## timeout in dwc2_hcd_endpoint_disable() ##\n");
			rc = -EBUSY;
			जाओ err;
		पूर्ण

		spin_unlock_irqrestore(&hsotg->lock, flags);
		msleep(20);
		spin_lock_irqsave(&hsotg->lock, flags);
		qh = ep->hcpriv;
		अगर (!qh) अणु
			rc = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	dwc2_hcd_qh_unlink(hsotg, qh);

	/* Free each QTD in the QH's QTD list */
	list_क्रम_each_entry_safe(qtd, qtd_पंचांगp, &qh->qtd_list, qtd_list_entry)
		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);

	ep->hcpriv = शून्य;

	अगर (qh->channel && qh->channel->qh == qh)
		qh->channel->qh = शून्य;

	spin_unlock_irqrestore(&hsotg->lock, flags);

	dwc2_hcd_qh_मुक्त(hsotg, qh);

	वापस 0;

err:
	ep->hcpriv = शून्य;
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस rc;
पूर्ण

/* Must be called with पूर्णांकerrupt disabled and spinlock held */
अटल पूर्णांक dwc2_hcd_endpoपूर्णांक_reset(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_qh *qh = ep->hcpriv;

	अगर (!qh)
		वापस -EINVAL;

	qh->data_toggle = DWC2_HC_PID_DATA0;

	वापस 0;
पूर्ण

/**
 * dwc2_core_init() - Initializes the DWC_otg controller रेजिस्टरs and
 * prepares the core क्रम device mode or host mode operation
 *
 * @hsotg:         Programming view of the DWC_otg controller
 * @initial_setup: If true then this is the first init क्रम this instance.
 */
पूर्णांक dwc2_core_init(काष्ठा dwc2_hsotg *hsotg, bool initial_setup)
अणु
	u32 usbcfg, otgctl;
	पूर्णांक retval;

	dev_dbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);

	/* Set ULPI External VBUS bit अगर needed */
	usbcfg &= ~GUSBCFG_ULPI_EXT_VBUS_DRV;
	अगर (hsotg->params.phy_ulpi_ext_vbus)
		usbcfg |= GUSBCFG_ULPI_EXT_VBUS_DRV;

	/* Set बाह्यal TS Dline pulsing bit अगर needed */
	usbcfg &= ~GUSBCFG_TERMSELDLPULSE;
	अगर (hsotg->params.ts_dline)
		usbcfg |= GUSBCFG_TERMSELDLPULSE;

	dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

	/*
	 * Reset the Controller
	 *
	 * We only need to reset the controller अगर this is a re-init.
	 * For the first init we know क्रम sure that earlier code reset us (it
	 * needed to in order to properly detect various parameters).
	 */
	अगर (!initial_setup) अणु
		retval = dwc2_core_reset(hsotg, false);
		अगर (retval) अणु
			dev_err(hsotg->dev, "%s(): Reset failed, aborting\n",
				__func__);
			वापस retval;
		पूर्ण
	पूर्ण

	/*
	 * This needs to happen in FS mode beक्रमe any other programming occurs
	 */
	retval = dwc2_phy_init(hsotg, initial_setup);
	अगर (retval)
		वापस retval;

	/* Program the GAHBCFG Register */
	retval = dwc2_gahbcfg_init(hsotg);
	अगर (retval)
		वापस retval;

	/* Program the GUSBCFG रेजिस्टर */
	dwc2_gusbcfg_init(hsotg);

	/* Program the GOTGCTL रेजिस्टर */
	otgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	otgctl &= ~GOTGCTL_OTGVER;
	dwc2_ग_लिखोl(hsotg, otgctl, GOTGCTL);

	/* Clear the SRP success bit क्रम FS-I2c */
	hsotg->srp_success = 0;

	/* Enable common पूर्णांकerrupts */
	dwc2_enable_common_पूर्णांकerrupts(hsotg);

	/*
	 * Do device or host initialization based on mode during PCD and
	 * HCD initialization
	 */
	अगर (dwc2_is_host_mode(hsotg)) अणु
		dev_dbg(hsotg->dev, "Host Mode\n");
		hsotg->op_state = OTG_STATE_A_HOST;
	पूर्ण अन्यथा अणु
		dev_dbg(hsotg->dev, "Device Mode\n");
		hsotg->op_state = OTG_STATE_B_PERIPHERAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc2_core_host_init() - Initializes the DWC_otg controller रेजिस्टरs क्रम
 * Host mode
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * This function flushes the Tx and Rx FIFOs and flushes any entries in the
 * request queues. Host channels are reset to ensure that they are पढ़ोy क्रम
 * perक्रमming transfers.
 */
अटल व्योम dwc2_core_host_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hcfg, hfir, otgctl, usbcfg;

	dev_dbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	/* Set HS/FS Timeout Calibration to 7 (max available value).
	 * The number of PHY घड़ीs that the application programs in
	 * this field is added to the high/full speed पूर्णांकerpacket समयout
	 * duration in the core to account क्रम any additional delays
	 * पूर्णांकroduced by the PHY. This can be required, because the delay
	 * पूर्णांकroduced by the PHY in generating the linestate condition
	 * can vary from one PHY to another.
	 */
	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	usbcfg |= GUSBCFG_TOUTCAL(7);
	dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

	/* Restart the Phy Clock */
	dwc2_ग_लिखोl(hsotg, 0, PCGCTL);

	/* Initialize Host Configuration Register */
	dwc2_init_fs_ls_pclk_sel(hsotg);
	अगर (hsotg->params.speed == DWC2_SPEED_PARAM_FULL ||
	    hsotg->params.speed == DWC2_SPEED_PARAM_LOW) अणु
		hcfg = dwc2_पढ़ोl(hsotg, HCFG);
		hcfg |= HCFG_FSLSSUPP;
		dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
	पूर्ण

	/*
	 * This bit allows dynamic reloading of the HFIR रेजिस्टर during
	 * runसमय. This bit needs to be programmed during initial configuration
	 * and its value must not be changed during runसमय.
	 */
	अगर (hsotg->params.reload_ctl) अणु
		hfir = dwc2_पढ़ोl(hsotg, HFIR);
		hfir |= HFIR_RLDCTRL;
		dwc2_ग_लिखोl(hsotg, hfir, HFIR);
	पूर्ण

	अगर (hsotg->params.dma_desc_enable) अणु
		u32 op_mode = hsotg->hw_params.op_mode;

		अगर (hsotg->hw_params.snpsid < DWC2_CORE_REV_2_90a ||
		    !hsotg->hw_params.dma_desc_enable ||
		    op_mode == GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE ||
		    op_mode == GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE ||
		    op_mode == GHWCFG2_OP_MODE_UNDEFINED) अणु
			dev_err(hsotg->dev,
				"Hardware does not support descriptor DMA mode -\n");
			dev_err(hsotg->dev,
				"falling back to buffer DMA mode.\n");
			hsotg->params.dma_desc_enable = false;
		पूर्ण अन्यथा अणु
			hcfg = dwc2_पढ़ोl(hsotg, HCFG);
			hcfg |= HCFG_DESCDMA;
			dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
		पूर्ण
	पूर्ण

	/* Configure data FIFO sizes */
	dwc2_config_fअगरos(hsotg);

	/* TODO - check this */
	/* Clear Host Set HNP Enable in the OTG Control Register */
	otgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	otgctl &= ~GOTGCTL_HSTSETHNPEN;
	dwc2_ग_लिखोl(hsotg, otgctl, GOTGCTL);

	/* Make sure the FIFOs are flushed */
	dwc2_flush_tx_fअगरo(hsotg, 0x10 /* all TX FIFOs */);
	dwc2_flush_rx_fअगरo(hsotg);

	/* Clear Host Set HNP Enable in the OTG Control Register */
	otgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	otgctl &= ~GOTGCTL_HSTSETHNPEN;
	dwc2_ग_लिखोl(hsotg, otgctl, GOTGCTL);

	अगर (!hsotg->params.dma_desc_enable) अणु
		पूर्णांक num_channels, i;
		u32 hcअक्षर;

		/* Flush out any leftover queued requests */
		num_channels = hsotg->params.host_channels;
		क्रम (i = 0; i < num_channels; i++) अणु
			hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(i));
			अगर (hcअक्षर & HCCHAR_CHENA) अणु
				hcअक्षर &= ~HCCHAR_CHENA;
				hcअक्षर |= HCCHAR_CHDIS;
				hcअक्षर &= ~HCCHAR_EPसूची;
				dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(i));
			पूर्ण
		पूर्ण

		/* Halt all channels to put them पूर्णांकo a known state */
		क्रम (i = 0; i < num_channels; i++) अणु
			hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(i));
			अगर (hcअक्षर & HCCHAR_CHENA) अणु
				hcअक्षर |= HCCHAR_CHENA | HCCHAR_CHDIS;
				hcअक्षर &= ~HCCHAR_EPसूची;
				dwc2_ग_लिखोl(hsotg, hcअक्षर, HCCHAR(i));
				dev_dbg(hsotg->dev, "%s: Halt channel %d\n",
					__func__, i);

				अगर (dwc2_hsotg_रुको_bit_clear(hsotg, HCCHAR(i),
							      HCCHAR_CHENA,
							      1000)) अणु
					dev_warn(hsotg->dev,
						 "Unable to clear enable on channel %d\n",
						 i);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Enable ACG feature in host mode, अगर supported */
	dwc2_enable_acg(hsotg);

	/* Turn on the vbus घातer */
	dev_dbg(hsotg->dev, "Init: Port Power? op_state=%d\n", hsotg->op_state);
	अगर (hsotg->op_state == OTG_STATE_A_HOST) अणु
		u32 hprt0 = dwc2_पढ़ो_hprt0(hsotg);

		dev_dbg(hsotg->dev, "Init: Power Port (%d)\n",
			!!(hprt0 & HPRT0_PWR));
		अगर (!(hprt0 & HPRT0_PWR)) अणु
			hprt0 |= HPRT0_PWR;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
		पूर्ण
	पूर्ण

	dwc2_enable_host_पूर्णांकerrupts(hsotg);
पूर्ण

/*
 * Initializes dynamic portions of the DWC_otg HCD state
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल व्योम dwc2_hcd_reinit(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_host_chan *chan, *chan_पंचांगp;
	पूर्णांक num_channels;
	पूर्णांक i;

	hsotg->flags.d32 = 0;
	hsotg->non_periodic_qh_ptr = &hsotg->non_periodic_sched_active;

	अगर (hsotg->params.uframe_sched) अणु
		hsotg->available_host_channels =
			hsotg->params.host_channels;
	पूर्ण अन्यथा अणु
		hsotg->non_periodic_channels = 0;
		hsotg->periodic_channels = 0;
	पूर्ण

	/*
	 * Put all channels in the मुक्त channel list and clean up channel
	 * states
	 */
	list_क्रम_each_entry_safe(chan, chan_पंचांगp, &hsotg->मुक्त_hc_list,
				 hc_list_entry)
		list_del_init(&chan->hc_list_entry);

	num_channels = hsotg->params.host_channels;
	क्रम (i = 0; i < num_channels; i++) अणु
		chan = hsotg->hc_ptr_array[i];
		list_add_tail(&chan->hc_list_entry, &hsotg->मुक्त_hc_list);
		dwc2_hc_cleanup(hsotg, chan);
	पूर्ण

	/* Initialize the DWC core क्रम host mode operation */
	dwc2_core_host_init(hsotg);
पूर्ण

अटल व्योम dwc2_hc_init_split(काष्ठा dwc2_hsotg *hsotg,
			       काष्ठा dwc2_host_chan *chan,
			       काष्ठा dwc2_qtd *qtd, काष्ठा dwc2_hcd_urb *urb)
अणु
	पूर्णांक hub_addr, hub_port;

	chan->करो_split = 1;
	chan->xact_pos = qtd->isoc_split_pos;
	chan->complete_split = qtd->complete_split;
	dwc2_host_hub_info(hsotg, urb->priv, &hub_addr, &hub_port);
	chan->hub_addr = (u8)hub_addr;
	chan->hub_port = (u8)hub_port;
पूर्ण

अटल व्योम dwc2_hc_init_xfer(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_host_chan *chan,
			      काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;

	चयन (dwc2_hcd_get_pipe_type(&urb->pipe_info)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		chan->ep_type = USB_ENDPOINT_XFER_CONTROL;

		चयन (qtd->control_phase) अणु
		हाल DWC2_CONTROL_SETUP:
			dev_vdbg(hsotg->dev, "  Control setup transaction\n");
			chan->करो_ping = 0;
			chan->ep_is_in = 0;
			chan->data_pid_start = DWC2_HC_PID_SETUP;
			अगर (hsotg->params.host_dma)
				chan->xfer_dma = urb->setup_dma;
			अन्यथा
				chan->xfer_buf = urb->setup_packet;
			chan->xfer_len = 8;
			अवरोध;

		हाल DWC2_CONTROL_DATA:
			dev_vdbg(hsotg->dev, "  Control data transaction\n");
			chan->data_pid_start = qtd->data_toggle;
			अवरोध;

		हाल DWC2_CONTROL_STATUS:
			/*
			 * Direction is opposite of data direction or IN अगर no
			 * data
			 */
			dev_vdbg(hsotg->dev, "  Control status transaction\n");
			अगर (urb->length == 0)
				chan->ep_is_in = 1;
			अन्यथा
				chan->ep_is_in =
					dwc2_hcd_is_pipe_out(&urb->pipe_info);
			अगर (chan->ep_is_in)
				chan->करो_ping = 0;
			chan->data_pid_start = DWC2_HC_PID_DATA1;
			chan->xfer_len = 0;
			अगर (hsotg->params.host_dma)
				chan->xfer_dma = hsotg->status_buf_dma;
			अन्यथा
				chan->xfer_buf = hsotg->status_buf;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल USB_ENDPOINT_XFER_BULK:
		chan->ep_type = USB_ENDPOINT_XFER_BULK;
		अवरोध;

	हाल USB_ENDPOINT_XFER_INT:
		chan->ep_type = USB_ENDPOINT_XFER_INT;
		अवरोध;

	हाल USB_ENDPOINT_XFER_ISOC:
		chan->ep_type = USB_ENDPOINT_XFER_ISOC;
		अगर (hsotg->params.dma_desc_enable)
			अवरोध;

		frame_desc = &urb->iso_descs[qtd->isoc_frame_index];
		frame_desc->status = 0;

		अगर (hsotg->params.host_dma) अणु
			chan->xfer_dma = urb->dma;
			chan->xfer_dma += frame_desc->offset +
					qtd->isoc_split_offset;
		पूर्ण अन्यथा अणु
			chan->xfer_buf = urb->buf;
			chan->xfer_buf += frame_desc->offset +
					qtd->isoc_split_offset;
		पूर्ण

		chan->xfer_len = frame_desc->length - qtd->isoc_split_offset;

		अगर (chan->xact_pos == DWC2_HCSPLT_XACTPOS_ALL) अणु
			अगर (chan->xfer_len <= 188)
				chan->xact_pos = DWC2_HCSPLT_XACTPOS_ALL;
			अन्यथा
				chan->xact_pos = DWC2_HCSPLT_XACTPOS_BEGIN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dwc2_alloc_split_dma_aligned_buf(काष्ठा dwc2_hsotg *hsotg,
					    काष्ठा dwc2_qh *qh,
					    काष्ठा dwc2_host_chan *chan)
अणु
	अगर (!hsotg->unaligned_cache ||
	    chan->max_packet > DWC2_KMEM_UNALIGNED_BUF_SIZE)
		वापस -ENOMEM;

	अगर (!qh->dw_align_buf) अणु
		qh->dw_align_buf = kmem_cache_alloc(hsotg->unaligned_cache,
						    GFP_ATOMIC | GFP_DMA);
		अगर (!qh->dw_align_buf)
			वापस -ENOMEM;
	पूर्ण

	qh->dw_align_buf_dma = dma_map_single(hsotg->dev, qh->dw_align_buf,
					      DWC2_KMEM_UNALIGNED_BUF_SIZE,
					      DMA_FROM_DEVICE);

	अगर (dma_mapping_error(hsotg->dev, qh->dw_align_buf_dma)) अणु
		dev_err(hsotg->dev, "can't map align_buf\n");
		chan->align_buf = 0;
		वापस -EINVAL;
	पूर्ण

	chan->align_buf = qh->dw_align_buf_dma;
	वापस 0;
पूर्ण

#घोषणा DWC2_USB_DMA_ALIGN 4

अटल व्योम dwc2_मुक्त_dma_aligned_buffer(काष्ठा urb *urb)
अणु
	व्योम *stored_xfer_buffer;
	माप_प्रकार length;

	अगर (!(urb->transfer_flags & URB_ALIGNED_TEMP_BUFFER))
		वापस;

	/* Restore urb->transfer_buffer from the end of the allocated area */
	स_नकल(&stored_xfer_buffer,
	       PTR_ALIGN(urb->transfer_buffer + urb->transfer_buffer_length,
			 dma_get_cache_alignment()),
	       माप(urb->transfer_buffer));

	अगर (usb_urb_dir_in(urb)) अणु
		अगर (usb_pipeisoc(urb->pipe))
			length = urb->transfer_buffer_length;
		अन्यथा
			length = urb->actual_length;

		स_नकल(stored_xfer_buffer, urb->transfer_buffer, length);
	पूर्ण
	kमुक्त(urb->transfer_buffer);
	urb->transfer_buffer = stored_xfer_buffer;

	urb->transfer_flags &= ~URB_ALIGNED_TEMP_BUFFER;
पूर्ण

अटल पूर्णांक dwc2_alloc_dma_aligned_buffer(काष्ठा urb *urb, gfp_t mem_flags)
अणु
	व्योम *kदो_स्मृति_ptr;
	माप_प्रकार kदो_स्मृति_size;

	अगर (urb->num_sgs || urb->sg ||
	    urb->transfer_buffer_length == 0 ||
	    !((uपूर्णांकptr_t)urb->transfer_buffer & (DWC2_USB_DMA_ALIGN - 1)))
		वापस 0;

	/*
	 * Allocate a buffer with enough padding क्रम original transfer_buffer
	 * poपूर्णांकer. This allocation is guaranteed to be aligned properly क्रम
	 * DMA
	 */
	kदो_स्मृति_size = urb->transfer_buffer_length +
		(dma_get_cache_alignment() - 1) +
		माप(urb->transfer_buffer);

	kदो_स्मृति_ptr = kदो_स्मृति(kदो_स्मृति_size, mem_flags);
	अगर (!kदो_स्मृति_ptr)
		वापस -ENOMEM;

	/*
	 * Position value of original urb->transfer_buffer poपूर्णांकer to the end
	 * of allocation क्रम later referencing
	 */
	स_नकल(PTR_ALIGN(kदो_स्मृति_ptr + urb->transfer_buffer_length,
			 dma_get_cache_alignment()),
	       &urb->transfer_buffer, माप(urb->transfer_buffer));

	अगर (usb_urb_dir_out(urb))
		स_नकल(kदो_स्मृति_ptr, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = kदो_स्मृति_ptr;

	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				gfp_t mem_flags)
अणु
	पूर्णांक ret;

	/* We assume setup_dma is always aligned; warn अगर not */
	WARN_ON_ONCE(urb->setup_dma &&
		     (urb->setup_dma & (DWC2_USB_DMA_ALIGN - 1)));

	ret = dwc2_alloc_dma_aligned_buffer(urb, mem_flags);
	अगर (ret)
		वापस ret;

	ret = usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
	अगर (ret)
		dwc2_मुक्त_dma_aligned_buffer(urb);

	वापस ret;
पूर्ण

अटल व्योम dwc2_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
	dwc2_मुक्त_dma_aligned_buffer(urb);
पूर्ण

/**
 * dwc2_assign_and_init_hc() - Assigns transactions from a QTD to a मुक्त host
 * channel and initializes the host channel to perक्रमm the transactions. The
 * host channel is हटाओd from the मुक्त list.
 *
 * @hsotg: The HCD state काष्ठाure
 * @qh:    Transactions from the first QTD क्रम this QH are selected and asचिन्हित
 *         to a मुक्त host channel
 */
अटल पूर्णांक dwc2_assign_and_init_hc(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	काष्ठा dwc2_host_chan *chan;
	काष्ठा dwc2_hcd_urb *urb;
	काष्ठा dwc2_qtd *qtd;

	अगर (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s(%p,%p)\n", __func__, hsotg, qh);

	अगर (list_empty(&qh->qtd_list)) अणु
		dev_dbg(hsotg->dev, "No QTDs in QH list\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (list_empty(&hsotg->मुक्त_hc_list)) अणु
		dev_dbg(hsotg->dev, "No free channel to assign\n");
		वापस -ENOMEM;
	पूर्ण

	chan = list_first_entry(&hsotg->मुक्त_hc_list, काष्ठा dwc2_host_chan,
				hc_list_entry);

	/* Remove host channel from मुक्त list */
	list_del_init(&chan->hc_list_entry);

	qtd = list_first_entry(&qh->qtd_list, काष्ठा dwc2_qtd, qtd_list_entry);
	urb = qtd->urb;
	qh->channel = chan;
	qtd->in_process = 1;

	/*
	 * Use usb_pipedevice to determine device address. This address is
	 * 0 beक्रमe the SET_ADDRESS command and the correct address afterward.
	 */
	chan->dev_addr = dwc2_hcd_get_dev_addr(&urb->pipe_info);
	chan->ep_num = dwc2_hcd_get_ep_num(&urb->pipe_info);
	chan->speed = qh->dev_speed;
	chan->max_packet = qh->maxp;

	chan->xfer_started = 0;
	chan->halt_status = DWC2_HC_XFER_NO_HALT_STATUS;
	chan->error_state = (qtd->error_count > 0);
	chan->halt_on_queue = 0;
	chan->halt_pending = 0;
	chan->requests = 0;

	/*
	 * The following values may be modअगरied in the transfer type section
	 * below. The xfer_len value may be reduced when the transfer is
	 * started to accommodate the max widths of the XferSize and PktCnt
	 * fields in the HCTSIZn रेजिस्टर.
	 */

	chan->ep_is_in = (dwc2_hcd_is_pipe_in(&urb->pipe_info) != 0);
	अगर (chan->ep_is_in)
		chan->करो_ping = 0;
	अन्यथा
		chan->करो_ping = qh->ping_state;

	chan->data_pid_start = qh->data_toggle;
	chan->multi_count = 1;

	अगर (urb->actual_length > urb->length &&
	    !dwc2_hcd_is_pipe_in(&urb->pipe_info))
		urb->actual_length = urb->length;

	अगर (hsotg->params.host_dma)
		chan->xfer_dma = urb->dma + urb->actual_length;
	अन्यथा
		chan->xfer_buf = (u8 *)urb->buf + urb->actual_length;

	chan->xfer_len = urb->length - urb->actual_length;
	chan->xfer_count = 0;

	/* Set the split attributes अगर required */
	अगर (qh->करो_split)
		dwc2_hc_init_split(hsotg, chan, qtd, urb);
	अन्यथा
		chan->करो_split = 0;

	/* Set the transfer attributes */
	dwc2_hc_init_xfer(hsotg, chan, qtd);

	/* For non-dword aligned buffers */
	अगर (hsotg->params.host_dma && qh->करो_split &&
	    chan->ep_is_in && (chan->xfer_dma & 0x3)) अणु
		dev_vdbg(hsotg->dev, "Non-aligned buffer\n");
		अगर (dwc2_alloc_split_dma_aligned_buf(hsotg, qh, chan)) अणु
			dev_err(hsotg->dev,
				"Failed to allocate memory to handle non-aligned buffer\n");
			/* Add channel back to मुक्त list */
			chan->align_buf = 0;
			chan->multi_count = 0;
			list_add_tail(&chan->hc_list_entry,
				      &hsotg->मुक्त_hc_list);
			qtd->in_process = 0;
			qh->channel = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We assume that DMA is always aligned in non-split
		 * हाल or split out हाल. Warn अगर not.
		 */
		WARN_ON_ONCE(hsotg->params.host_dma &&
			     (chan->xfer_dma & 0x3));
		chan->align_buf = 0;
	पूर्ण

	अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
	    chan->ep_type == USB_ENDPOINT_XFER_ISOC)
		/*
		 * This value may be modअगरied when the transfer is started
		 * to reflect the actual transfer length
		 */
		chan->multi_count = qh->maxp_mult;

	अगर (hsotg->params.dma_desc_enable) अणु
		chan->desc_list_addr = qh->desc_list_dma;
		chan->desc_list_sz = qh->desc_list_sz;
	पूर्ण

	dwc2_hc_init(hsotg, chan);
	chan->qh = qh;

	वापस 0;
पूर्ण

/**
 * dwc2_hcd_select_transactions() - Selects transactions from the HCD transfer
 * schedule and assigns them to available host channels. Called from the HCD
 * पूर्णांकerrupt handler functions.
 *
 * @hsotg: The HCD state काष्ठाure
 *
 * Return: The types of new transactions that were asचिन्हित to host channels
 */
क्रमागत dwc2_transaction_type dwc2_hcd_select_transactions(
		काष्ठा dwc2_hsotg *hsotg)
अणु
	क्रमागत dwc2_transaction_type ret_val = DWC2_TRANSACTION_NONE;
	काष्ठा list_head *qh_ptr;
	काष्ठा dwc2_qh *qh;
	पूर्णांक num_channels;

#अगर_घोषित DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "  Select Transactions\n");
#पूर्ण_अगर

	/* Process entries in the periodic पढ़ोy list */
	qh_ptr = hsotg->periodic_sched_पढ़ोy.next;
	जबतक (qh_ptr != &hsotg->periodic_sched_पढ़ोy) अणु
		अगर (list_empty(&hsotg->मुक्त_hc_list))
			अवरोध;
		अगर (hsotg->params.uframe_sched) अणु
			अगर (hsotg->available_host_channels <= 1)
				अवरोध;
			hsotg->available_host_channels--;
		पूर्ण
		qh = list_entry(qh_ptr, काष्ठा dwc2_qh, qh_list_entry);
		अगर (dwc2_assign_and_init_hc(hsotg, qh))
			अवरोध;

		/*
		 * Move the QH from the periodic पढ़ोy schedule to the
		 * periodic asचिन्हित schedule
		 */
		qh_ptr = qh_ptr->next;
		list_move_tail(&qh->qh_list_entry,
			       &hsotg->periodic_sched_asचिन्हित);
		ret_val = DWC2_TRANSACTION_PERIODIC;
	पूर्ण

	/*
	 * Process entries in the inactive portion of the non-periodic
	 * schedule. Some मुक्त host channels may not be used अगर they are
	 * reserved क्रम periodic transfers.
	 */
	num_channels = hsotg->params.host_channels;
	qh_ptr = hsotg->non_periodic_sched_inactive.next;
	जबतक (qh_ptr != &hsotg->non_periodic_sched_inactive) अणु
		अगर (!hsotg->params.uframe_sched &&
		    hsotg->non_periodic_channels >= num_channels -
						hsotg->periodic_channels)
			अवरोध;
		अगर (list_empty(&hsotg->मुक्त_hc_list))
			अवरोध;
		qh = list_entry(qh_ptr, काष्ठा dwc2_qh, qh_list_entry);
		अगर (hsotg->params.uframe_sched) अणु
			अगर (hsotg->available_host_channels < 1)
				अवरोध;
			hsotg->available_host_channels--;
		पूर्ण

		अगर (dwc2_assign_and_init_hc(hsotg, qh))
			अवरोध;

		/*
		 * Move the QH from the non-periodic inactive schedule to the
		 * non-periodic active schedule
		 */
		qh_ptr = qh_ptr->next;
		list_move_tail(&qh->qh_list_entry,
			       &hsotg->non_periodic_sched_active);

		अगर (ret_val == DWC2_TRANSACTION_NONE)
			ret_val = DWC2_TRANSACTION_NON_PERIODIC;
		अन्यथा
			ret_val = DWC2_TRANSACTION_ALL;

		अगर (!hsotg->params.uframe_sched)
			hsotg->non_periodic_channels++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * dwc2_queue_transaction() - Attempts to queue a single transaction request क्रम
 * a host channel associated with either a periodic or non-periodic transfer
 *
 * @hsotg: The HCD state काष्ठाure
 * @chan:  Host channel descriptor associated with either a periodic or
 *         non-periodic transfer
 * @fअगरo_dwords_avail: Number of DWORDs available in the periodic Tx FIFO
 *                     क्रम periodic transfers or the non-periodic Tx FIFO
 *                     क्रम non-periodic transfers
 *
 * Return: 1 अगर a request is queued and more requests may be needed to
 * complete the transfer, 0 अगर no more requests are required क्रम this
 * transfer, -1 अगर there is insufficient space in the Tx FIFO
 *
 * This function assumes that there is space available in the appropriate
 * request queue. For an OUT transfer or SETUP transaction in Slave mode,
 * it checks whether space is available in the appropriate Tx FIFO.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल पूर्णांक dwc2_queue_transaction(काष्ठा dwc2_hsotg *hsotg,
				  काष्ठा dwc2_host_chan *chan,
				  u16 fअगरo_dwords_avail)
अणु
	पूर्णांक retval = 0;

	अगर (chan->करो_split)
		/* Put ourselves on the list to keep order straight */
		list_move_tail(&chan->split_order_list_entry,
			       &hsotg->split_order);

	अगर (hsotg->params.host_dma && chan->qh) अणु
		अगर (hsotg->params.dma_desc_enable) अणु
			अगर (!chan->xfer_started ||
			    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
				dwc2_hcd_start_xfer_ddma(hsotg, chan->qh);
				chan->qh->ping_state = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (!chan->xfer_started) अणु
			dwc2_hc_start_transfer(hsotg, chan);
			chan->qh->ping_state = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (chan->halt_pending) अणु
		/* Don't queue a request अगर the channel has been halted */
	पूर्ण अन्यथा अगर (chan->halt_on_queue) अणु
		dwc2_hc_halt(hsotg, chan, chan->halt_status);
	पूर्ण अन्यथा अगर (chan->करो_ping) अणु
		अगर (!chan->xfer_started)
			dwc2_hc_start_transfer(hsotg, chan);
	पूर्ण अन्यथा अगर (!chan->ep_is_in ||
		   chan->data_pid_start == DWC2_HC_PID_SETUP) अणु
		अगर ((fअगरo_dwords_avail * 4) >= chan->max_packet) अणु
			अगर (!chan->xfer_started) अणु
				dwc2_hc_start_transfer(hsotg, chan);
				retval = 1;
			पूर्ण अन्यथा अणु
				retval = dwc2_hc_जारी_transfer(hsotg, chan);
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!chan->xfer_started) अणु
			dwc2_hc_start_transfer(hsotg, chan);
			retval = 1;
		पूर्ण अन्यथा अणु
			retval = dwc2_hc_जारी_transfer(hsotg, chan);
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/*
 * Processes periodic channels क्रम the next frame and queues transactions क्रम
 * these channels to the DWC_otg controller. After queueing transactions, the
 * Periodic Tx FIFO Empty पूर्णांकerrupt is enabled अगर there are more transactions
 * to queue as Periodic Tx FIFO or request queue space becomes available.
 * Otherwise, the Periodic Tx FIFO Empty पूर्णांकerrupt is disabled.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल व्योम dwc2_process_periodic_channels(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा list_head *qh_ptr;
	काष्ठा dwc2_qh *qh;
	u32 tx_status;
	u32 fspcavail;
	u32 gपूर्णांकmsk;
	पूर्णांक status;
	bool no_queue_space = false;
	bool no_fअगरo_space = false;
	u32 qspcavail;

	/* If empty list then just adjust पूर्णांकerrupt enables */
	अगर (list_empty(&hsotg->periodic_sched_asचिन्हित))
		जाओ निकास;

	अगर (dbg_perio())
		dev_vdbg(hsotg->dev, "Queue periodic transactions\n");

	tx_status = dwc2_पढ़ोl(hsotg, HPTXSTS);
	qspcavail = (tx_status & TXSTS_QSPCAVAIL_MASK) >>
		    TXSTS_QSPCAVAIL_SHIFT;
	fspcavail = (tx_status & TXSTS_FSPCAVAIL_MASK) >>
		    TXSTS_FSPCAVAIL_SHIFT;

	अगर (dbg_perio()) अणु
		dev_vdbg(hsotg->dev, "  P Tx Req Queue Space Avail (before queue): %d\n",
			 qspcavail);
		dev_vdbg(hsotg->dev, "  P Tx FIFO Space Avail (before queue): %d\n",
			 fspcavail);
	पूर्ण

	qh_ptr = hsotg->periodic_sched_asचिन्हित.next;
	जबतक (qh_ptr != &hsotg->periodic_sched_asचिन्हित) अणु
		tx_status = dwc2_पढ़ोl(hsotg, HPTXSTS);
		qspcavail = (tx_status & TXSTS_QSPCAVAIL_MASK) >>
			    TXSTS_QSPCAVAIL_SHIFT;
		अगर (qspcavail == 0) अणु
			no_queue_space = true;
			अवरोध;
		पूर्ण

		qh = list_entry(qh_ptr, काष्ठा dwc2_qh, qh_list_entry);
		अगर (!qh->channel) अणु
			qh_ptr = qh_ptr->next;
			जारी;
		पूर्ण

		/* Make sure EP's TT buffer is clean beक्रमe queueing qtds */
		अगर (qh->tt_buffer_dirty) अणु
			qh_ptr = qh_ptr->next;
			जारी;
		पूर्ण

		/*
		 * Set a flag अगर we're queuing high-bandwidth in slave mode.
		 * The flag prevents any halts to get पूर्णांकo the request queue in
		 * the middle of multiple high-bandwidth packets getting queued.
		 */
		अगर (!hsotg->params.host_dma &&
		    qh->channel->multi_count > 1)
			hsotg->queuing_high_bandwidth = 1;

		fspcavail = (tx_status & TXSTS_FSPCAVAIL_MASK) >>
			    TXSTS_FSPCAVAIL_SHIFT;
		status = dwc2_queue_transaction(hsotg, qh->channel, fspcavail);
		अगर (status < 0) अणु
			no_fअगरo_space = true;
			अवरोध;
		पूर्ण

		/*
		 * In Slave mode, stay on the current transfer until there is
		 * nothing more to करो or the high-bandwidth request count is
		 * reached. In DMA mode, only need to queue one request. The
		 * controller स्वतःmatically handles multiple packets क्रम
		 * high-bandwidth transfers.
		 */
		अगर (hsotg->params.host_dma || status == 0 ||
		    qh->channel->requests == qh->channel->multi_count) अणु
			qh_ptr = qh_ptr->next;
			/*
			 * Move the QH from the periodic asचिन्हित schedule to
			 * the periodic queued schedule
			 */
			list_move_tail(&qh->qh_list_entry,
				       &hsotg->periodic_sched_queued);

			/* करोne queuing high bandwidth */
			hsotg->queuing_high_bandwidth = 0;
		पूर्ण
	पूर्ण

निकास:
	अगर (no_queue_space || no_fअगरo_space ||
	    (!hsotg->params.host_dma &&
	     !list_empty(&hsotg->periodic_sched_asचिन्हित))) अणु
		/*
		 * May need to queue more transactions as the request
		 * queue or Tx FIFO empties. Enable the periodic Tx
		 * FIFO empty पूर्णांकerrupt. (Always use the half-empty
		 * level to ensure that new requests are loaded as
		 * soon as possible.)
		 */
		gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
		अगर (!(gपूर्णांकmsk & GINTSTS_PTXFEMP)) अणु
			gपूर्णांकmsk |= GINTSTS_PTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Disable the Tx FIFO empty पूर्णांकerrupt since there are
		 * no more transactions that need to be queued right
		 * now. This function is called from पूर्णांकerrupt
		 * handlers to queue more transactions as transfer
		 * states change.
		 */
		gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
		अगर (gपूर्णांकmsk & GINTSTS_PTXFEMP) अणु
			gपूर्णांकmsk &= ~GINTSTS_PTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Processes active non-periodic channels and queues transactions क्रम these
 * channels to the DWC_otg controller. After queueing transactions, the NP Tx
 * FIFO Empty पूर्णांकerrupt is enabled अगर there are more transactions to queue as
 * NP Tx FIFO or request queue space becomes available. Otherwise, the NP Tx
 * FIFO Empty पूर्णांकerrupt is disabled.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
अटल व्योम dwc2_process_non_periodic_channels(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा list_head *orig_qh_ptr;
	काष्ठा dwc2_qh *qh;
	u32 tx_status;
	u32 qspcavail;
	u32 fspcavail;
	u32 gपूर्णांकmsk;
	पूर्णांक status;
	पूर्णांक no_queue_space = 0;
	पूर्णांक no_fअगरo_space = 0;
	पूर्णांक more_to_करो = 0;

	dev_vdbg(hsotg->dev, "Queue non-periodic transactions\n");

	tx_status = dwc2_पढ़ोl(hsotg, GNPTXSTS);
	qspcavail = (tx_status & TXSTS_QSPCAVAIL_MASK) >>
		    TXSTS_QSPCAVAIL_SHIFT;
	fspcavail = (tx_status & TXSTS_FSPCAVAIL_MASK) >>
		    TXSTS_FSPCAVAIL_SHIFT;
	dev_vdbg(hsotg->dev, "  NP Tx Req Queue Space Avail (before queue): %d\n",
		 qspcavail);
	dev_vdbg(hsotg->dev, "  NP Tx FIFO Space Avail (before queue): %d\n",
		 fspcavail);

	/*
	 * Keep track of the starting poपूर्णांक. Skip over the start-of-list
	 * entry.
	 */
	अगर (hsotg->non_periodic_qh_ptr == &hsotg->non_periodic_sched_active)
		hsotg->non_periodic_qh_ptr = hsotg->non_periodic_qh_ptr->next;
	orig_qh_ptr = hsotg->non_periodic_qh_ptr;

	/*
	 * Process once through the active list or until no more space is
	 * available in the request queue or the Tx FIFO
	 */
	करो अणु
		tx_status = dwc2_पढ़ोl(hsotg, GNPTXSTS);
		qspcavail = (tx_status & TXSTS_QSPCAVAIL_MASK) >>
			    TXSTS_QSPCAVAIL_SHIFT;
		अगर (!hsotg->params.host_dma && qspcavail == 0) अणु
			no_queue_space = 1;
			अवरोध;
		पूर्ण

		qh = list_entry(hsotg->non_periodic_qh_ptr, काष्ठा dwc2_qh,
				qh_list_entry);
		अगर (!qh->channel)
			जाओ next;

		/* Make sure EP's TT buffer is clean beक्रमe queueing qtds */
		अगर (qh->tt_buffer_dirty)
			जाओ next;

		fspcavail = (tx_status & TXSTS_FSPCAVAIL_MASK) >>
			    TXSTS_FSPCAVAIL_SHIFT;
		status = dwc2_queue_transaction(hsotg, qh->channel, fspcavail);

		अगर (status > 0) अणु
			more_to_करो = 1;
		पूर्ण अन्यथा अगर (status < 0) अणु
			no_fअगरo_space = 1;
			अवरोध;
		पूर्ण
next:
		/* Advance to next QH, skipping start-of-list entry */
		hsotg->non_periodic_qh_ptr = hsotg->non_periodic_qh_ptr->next;
		अगर (hsotg->non_periodic_qh_ptr ==
				&hsotg->non_periodic_sched_active)
			hsotg->non_periodic_qh_ptr =
					hsotg->non_periodic_qh_ptr->next;
	पूर्ण जबतक (hsotg->non_periodic_qh_ptr != orig_qh_ptr);

	अगर (!hsotg->params.host_dma) अणु
		tx_status = dwc2_पढ़ोl(hsotg, GNPTXSTS);
		qspcavail = (tx_status & TXSTS_QSPCAVAIL_MASK) >>
			    TXSTS_QSPCAVAIL_SHIFT;
		fspcavail = (tx_status & TXSTS_FSPCAVAIL_MASK) >>
			    TXSTS_FSPCAVAIL_SHIFT;
		dev_vdbg(hsotg->dev,
			 "  NP Tx Req Queue Space Avail (after queue): %d\n",
			 qspcavail);
		dev_vdbg(hsotg->dev,
			 "  NP Tx FIFO Space Avail (after queue): %d\n",
			 fspcavail);

		अगर (more_to_करो || no_queue_space || no_fअगरo_space) अणु
			/*
			 * May need to queue more transactions as the request
			 * queue or Tx FIFO empties. Enable the non-periodic
			 * Tx FIFO empty पूर्णांकerrupt. (Always use the half-empty
			 * level to ensure that new requests are loaded as
			 * soon as possible.)
			 */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk |= GINTSTS_NPTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण अन्यथा अणु
			/*
			 * Disable the Tx FIFO empty पूर्णांकerrupt since there are
			 * no more transactions that need to be queued right
			 * now. This function is called from पूर्णांकerrupt
			 * handlers to queue more transactions as transfer
			 * states change.
			 */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk &= ~GINTSTS_NPTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_queue_transactions() - Processes the currently active host channels
 * and queues transactions क्रम these channels to the DWC_otg controller. Called
 * from the HCD पूर्णांकerrupt handler functions.
 *
 * @hsotg:   The HCD state काष्ठाure
 * @tr_type: The type(s) of transactions to queue (non-periodic, periodic,
 *           or both)
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
व्योम dwc2_hcd_queue_transactions(काष्ठा dwc2_hsotg *hsotg,
				 क्रमागत dwc2_transaction_type tr_type)
अणु
#अगर_घोषित DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "Queue Transactions\n");
#पूर्ण_अगर
	/* Process host channels associated with periodic transfers */
	अगर (tr_type == DWC2_TRANSACTION_PERIODIC ||
	    tr_type == DWC2_TRANSACTION_ALL)
		dwc2_process_periodic_channels(hsotg);

	/* Process host channels associated with non-periodic transfers */
	अगर (tr_type == DWC2_TRANSACTION_NON_PERIODIC ||
	    tr_type == DWC2_TRANSACTION_ALL) अणु
		अगर (!list_empty(&hsotg->non_periodic_sched_active)) अणु
			dwc2_process_non_periodic_channels(hsotg);
		पूर्ण अन्यथा अणु
			/*
			 * Ensure NP Tx FIFO empty पूर्णांकerrupt is disabled when
			 * there are no non-periodic transfers to process
			 */
			u32 gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);

			gपूर्णांकmsk &= ~GINTSTS_NPTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dwc2_conn_id_status_change(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc2_hsotg *hsotg = container_of(work, काष्ठा dwc2_hsotg,
						wf_otg);
	u32 count = 0;
	u32 gotgctl;
	अचिन्हित दीर्घ flags;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	dev_dbg(hsotg->dev, "gotgctl=%0x\n", gotgctl);
	dev_dbg(hsotg->dev, "gotgctl.b.conidsts=%d\n",
		!!(gotgctl & GOTGCTL_CONID_B));

	/* B-Device connector (Device Mode) */
	अगर (gotgctl & GOTGCTL_CONID_B) अणु
		dwc2_vbus_supply_निकास(hsotg);
		/* Wait क्रम चयन to device mode */
		dev_dbg(hsotg->dev, "connId B\n");
		अगर (hsotg->bus_suspended) अणु
			dev_info(hsotg->dev,
				 "Do port resume before switching to device mode\n");
			dwc2_port_resume(hsotg);
		पूर्ण
		जबतक (!dwc2_is_device_mode(hsotg)) अणु
			dev_info(hsotg->dev,
				 "Waiting for Peripheral Mode, Mode=%s\n",
				 dwc2_is_host_mode(hsotg) ? "Host" :
				 "Peripheral");
			msleep(20);
			/*
			 * Someबार the initial GOTGCTRL पढ़ो is wrong, so
			 * check it again and jump to host mode अगर that was
			 * the हाल.
			 */
			gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
			अगर (!(gotgctl & GOTGCTL_CONID_B))
				जाओ host;
			अगर (++count > 250)
				अवरोध;
		पूर्ण
		अगर (count > 250)
			dev_err(hsotg->dev,
				"Connection id status change timed out\n");

		/*
		 * Exit Partial Power Down without restoring रेजिस्टरs.
		 * No need to check the वापस value as रेजिस्टरs
		 * are not being restored.
		 */
		अगर (hsotg->in_ppd && hsotg->lx_state == DWC2_L2)
			dwc2_निकास_partial_घातer_करोwn(hsotg, 0, false);

		hsotg->op_state = OTG_STATE_B_PERIPHERAL;
		dwc2_core_init(hsotg, false);
		dwc2_enable_global_पूर्णांकerrupts(hsotg);
		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_hsotg_core_init_disconnected(hsotg, false);
		spin_unlock_irqrestore(&hsotg->lock, flags);
		/* Enable ACG feature in device mode,अगर supported */
		dwc2_enable_acg(hsotg);
		dwc2_hsotg_core_connect(hsotg);
	पूर्ण अन्यथा अणु
host:
		/* A-Device connector (Host Mode) */
		dev_dbg(hsotg->dev, "connId A\n");
		जबतक (!dwc2_is_host_mode(hsotg)) अणु
			dev_info(hsotg->dev, "Waiting for Host Mode, Mode=%s\n",
				 dwc2_is_host_mode(hsotg) ?
				 "Host" : "Peripheral");
			msleep(20);
			अगर (++count > 250)
				अवरोध;
		पूर्ण
		अगर (count > 250)
			dev_err(hsotg->dev,
				"Connection id status change timed out\n");

		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_hsotg_disconnect(hsotg);
		spin_unlock_irqrestore(&hsotg->lock, flags);

		hsotg->op_state = OTG_STATE_A_HOST;
		/* Initialize the Core क्रम Host mode */
		dwc2_core_init(hsotg, false);
		dwc2_enable_global_पूर्णांकerrupts(hsotg);
		dwc2_hcd_start(hsotg);
	पूर्ण
पूर्ण

अटल व्योम dwc2_wakeup_detected(काष्ठा समयr_list *t)
अणु
	काष्ठा dwc2_hsotg *hsotg = from_समयr(hsotg, t, wkp_समयr);
	u32 hprt0;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * Clear the Resume after 70ms. (Need 20 ms minimum. Use 70 ms
	 * so that OPT tests pass with all PHYs.)
	 */
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	dev_dbg(hsotg->dev, "Resume: HPRT0=%0x\n", hprt0);
	hprt0 &= ~HPRT0_RES;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	dev_dbg(hsotg->dev, "Clear Resume: HPRT0=%0x\n",
		dwc2_पढ़ोl(hsotg, HPRT0));

	dwc2_hcd_rem_wakeup(hsotg);
	hsotg->bus_suspended = false;

	/* Change to L0 state */
	hsotg->lx_state = DWC2_L0;
पूर्ण

अटल पूर्णांक dwc2_host_is_b_hnp_enabled(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	वापस hcd->self.b_hnp_enable;
पूर्ण

/**
 * dwc2_port_suspend() - Put controller in suspend mode क्रम host.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @windex: The control request wIndex field
 *
 * Return: non-zero अगर failed to enter suspend mode क्रम host.
 *
 * This function is क्रम entering Host mode suspend.
 * Must NOT be called with पूर्णांकerrupt disabled or spinlock held.
 */
पूर्णांक dwc2_port_suspend(काष्ठा dwc2_hsotg *hsotg, u16 windex)
अणु
	अचिन्हित दीर्घ flags;
	u32 pcgctl;
	u32 gotgctl;
	पूर्णांक ret = 0;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	spin_lock_irqsave(&hsotg->lock, flags);

	अगर (windex == hsotg->otg_port && dwc2_host_is_b_hnp_enabled(hsotg)) अणु
		gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
		gotgctl |= GOTGCTL_HSTSETHNPEN;
		dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);
		hsotg->op_state = OTG_STATE_A_SUSPEND;
	पूर्ण

	चयन (hsotg->params.घातer_करोwn) अणु
	हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
		ret = dwc2_enter_partial_घातer_करोwn(hsotg);
		अगर (ret)
			dev_err(hsotg->dev,
				"enter partial_power_down failed.\n");
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
		/*
		 * Perक्रमm spin unlock and lock because in
		 * "dwc2_host_enter_hibernation()" function there is a spinlock
		 * logic which prevents servicing of any IRQ during entering
		 * hibernation.
		 */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		ret = dwc2_enter_hibernation(hsotg, 1);
		अगर (ret)
			dev_err(hsotg->dev, "enter hibernation failed.\n");
		spin_lock_irqsave(&hsotg->lock, flags);
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_NONE:
		/*
		 * If not hibernation nor partial घातer करोwn are supported,
		 * घड़ी gating is used to save घातer.
		 */
		dwc2_host_enter_घड़ी_gating(hsotg);
		अवरोध;
	पूर्ण

	/* For HNP the bus must be suspended क्रम at least 200ms */
	अगर (dwc2_host_is_b_hnp_enabled(hsotg)) अणु
		pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
		pcgctl &= ~PCGCTL_STOPPCLK;
		dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);

		spin_unlock_irqrestore(&hsotg->lock, flags);

		msleep(200);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&hsotg->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dwc2_port_resume() - Exit controller from suspend mode क्रम host.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Return: non-zero अगर failed to निकास suspend mode क्रम host.
 *
 * This function is क्रम निकासing Host mode suspend.
 * Must NOT be called with पूर्णांकerrupt disabled or spinlock held.
 */
पूर्णांक dwc2_port_resume(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hsotg->lock, flags);

	चयन (hsotg->params.घातer_करोwn) अणु
	हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
		ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 0, true);
		अगर (ret)
			dev_err(hsotg->dev,
				"exit partial_power_down failed.\n");
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
		/* Exit host hibernation. */
		ret = dwc2_निकास_hibernation(hsotg, 0, 0, 1);
		अगर (ret)
			dev_err(hsotg->dev, "exit hibernation failed.\n");
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_NONE:
		/*
		 * If not hibernation nor partial घातer करोwn are supported,
		 * port resume is करोne using the घड़ी gating programming flow.
		 */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		dwc2_host_निकास_घड़ी_gating(hsotg, 0);
		spin_lock_irqsave(&hsotg->lock, flags);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस ret;
पूर्ण

/* Handles hub class-specअगरic requests */
अटल पूर्णांक dwc2_hcd_hub_control(काष्ठा dwc2_hsotg *hsotg, u16 typereq,
				u16 wvalue, u16 windex, अक्षर *buf, u16 wlength)
अणु
	काष्ठा usb_hub_descriptor *hub_desc;
	पूर्णांक retval = 0;
	u32 hprt0;
	u32 port_status;
	u32 speed;
	u32 pcgctl;
	u32 pwr;

	चयन (typereq) अणु
	हाल ClearHubFeature:
		dev_dbg(hsotg->dev, "ClearHubFeature %1xh\n", wvalue);

		चयन (wvalue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* Nothing required here */
			अवरोध;

		शेष:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"ClearHubFeature request %1xh unknown\n",
				wvalue);
		पूर्ण
		अवरोध;

	हाल ClearPortFeature:
		अगर (wvalue != USB_PORT_FEAT_L1)
			अगर (!windex || windex > 1)
				जाओ error;
		चयन (wvalue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_ENABLE\n");
			hprt0 = dwc2_पढ़ो_hprt0(hsotg);
			hprt0 |= HPRT0_ENA;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
			अवरोध;

		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_SUSPEND\n");

			अगर (hsotg->bus_suspended)
				retval = dwc2_port_resume(hsotg);
			अवरोध;

		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_POWER\n");
			hprt0 = dwc2_पढ़ो_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			hprt0 &= ~HPRT0_PWR;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
			अगर (pwr)
				dwc2_vbus_supply_निकास(hsotg);
			अवरोध;

		हाल USB_PORT_FEAT_INDICATOR:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_INDICATOR\n");
			/* Port indicator not supported */
			अवरोध;

		हाल USB_PORT_FEAT_C_CONNECTION:
			/*
			 * Clears driver's पूर्णांकernal Connect Status Change flag
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_CONNECTION\n");
			hsotg->flags.b.port_connect_status_change = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_RESET:
			/* Clears driver's पूर्णांकernal Port Reset Change flag */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_RESET\n");
			hsotg->flags.b.port_reset_change = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_ENABLE:
			/*
			 * Clears the driver's पूर्णांकernal Port Enable/Disable
			 * Change flag
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_ENABLE\n");
			hsotg->flags.b.port_enable_change = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_SUSPEND:
			/*
			 * Clears the driver's पूर्णांकernal Port Suspend Change
			 * flag, which is set when resume संकेतing on the host
			 * port is complete
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_SUSPEND\n");
			hsotg->flags.b.port_suspend_change = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_PORT_L1:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_PORT_L1\n");
			hsotg->flags.b.port_l1_change = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_OVER_CURRENT\n");
			hsotg->flags.b.port_over_current_change = 0;
			अवरोध;

		शेष:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"ClearPortFeature request %1xh unknown or unsupported\n",
				wvalue);
		पूर्ण
		अवरोध;

	हाल GetHubDescriptor:
		dev_dbg(hsotg->dev, "GetHubDescriptor\n");
		hub_desc = (काष्ठा usb_hub_descriptor *)buf;
		hub_desc->bDescLength = 9;
		hub_desc->bDescriptorType = USB_DT_HUB;
		hub_desc->bNbrPorts = 1;
		hub_desc->wHubCharacteristics =
			cpu_to_le16(HUB_CHAR_COMMON_LPSM |
				    HUB_CHAR_INDV_PORT_OCPM);
		hub_desc->bPwrOn2PwrGood = 1;
		hub_desc->bHubContrCurrent = 0;
		hub_desc->u.hs.DeviceRemovable[0] = 0;
		hub_desc->u.hs.DeviceRemovable[1] = 0xff;
		अवरोध;

	हाल GetHubStatus:
		dev_dbg(hsotg->dev, "GetHubStatus\n");
		स_रखो(buf, 0, 4);
		अवरोध;

	हाल GetPortStatus:
		dev_vdbg(hsotg->dev,
			 "GetPortStatus wIndex=0x%04x flags=0x%08x\n", windex,
			 hsotg->flags.d32);
		अगर (!windex || windex > 1)
			जाओ error;

		port_status = 0;
		अगर (hsotg->flags.b.port_connect_status_change)
			port_status |= USB_PORT_STAT_C_CONNECTION << 16;
		अगर (hsotg->flags.b.port_enable_change)
			port_status |= USB_PORT_STAT_C_ENABLE << 16;
		अगर (hsotg->flags.b.port_suspend_change)
			port_status |= USB_PORT_STAT_C_SUSPEND << 16;
		अगर (hsotg->flags.b.port_l1_change)
			port_status |= USB_PORT_STAT_C_L1 << 16;
		अगर (hsotg->flags.b.port_reset_change)
			port_status |= USB_PORT_STAT_C_RESET << 16;
		अगर (hsotg->flags.b.port_over_current_change) अणु
			dev_warn(hsotg->dev, "Overcurrent change detected\n");
			port_status |= USB_PORT_STAT_C_OVERCURRENT << 16;
		पूर्ण

		अगर (!hsotg->flags.b.port_connect_status) अणु
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * वापस 0's क्रम the reमुख्यder of the port status
			 * since the port रेजिस्टर can't be पढ़ो अगर the core
			 * is in device mode.
			 */
			*(__le32 *)buf = cpu_to_le32(port_status);
			अवरोध;
		पूर्ण

		hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
		dev_vdbg(hsotg->dev, "  HPRT0: 0x%08x\n", hprt0);

		अगर (hprt0 & HPRT0_CONNSTS)
			port_status |= USB_PORT_STAT_CONNECTION;
		अगर (hprt0 & HPRT0_ENA)
			port_status |= USB_PORT_STAT_ENABLE;
		अगर (hprt0 & HPRT0_SUSP)
			port_status |= USB_PORT_STAT_SUSPEND;
		अगर (hprt0 & HPRT0_OVRCURRACT)
			port_status |= USB_PORT_STAT_OVERCURRENT;
		अगर (hprt0 & HPRT0_RST)
			port_status |= USB_PORT_STAT_RESET;
		अगर (hprt0 & HPRT0_PWR)
			port_status |= USB_PORT_STAT_POWER;

		speed = (hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;
		अगर (speed == HPRT0_SPD_HIGH_SPEED)
			port_status |= USB_PORT_STAT_HIGH_SPEED;
		अन्यथा अगर (speed == HPRT0_SPD_LOW_SPEED)
			port_status |= USB_PORT_STAT_LOW_SPEED;

		अगर (hprt0 & HPRT0_TSTCTL_MASK)
			port_status |= USB_PORT_STAT_TEST;
		/* USB_PORT_FEAT_INDICATOR unsupported always 0 */

		अगर (hsotg->params.dma_desc_fs_enable) अणु
			/*
			 * Enable descriptor DMA only अगर a full speed
			 * device is connected.
			 */
			अगर (hsotg->new_connection &&
			    ((port_status &
			      (USB_PORT_STAT_CONNECTION |
			       USB_PORT_STAT_HIGH_SPEED |
			       USB_PORT_STAT_LOW_SPEED)) ==
			       USB_PORT_STAT_CONNECTION)) अणु
				u32 hcfg;

				dev_info(hsotg->dev, "Enabling descriptor DMA mode\n");
				hsotg->params.dma_desc_enable = true;
				hcfg = dwc2_पढ़ोl(hsotg, HCFG);
				hcfg |= HCFG_DESCDMA;
				dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
				hsotg->new_connection = false;
			पूर्ण
		पूर्ण

		dev_vdbg(hsotg->dev, "port_status=%08x\n", port_status);
		*(__le32 *)buf = cpu_to_le32(port_status);
		अवरोध;

	हाल SetHubFeature:
		dev_dbg(hsotg->dev, "SetHubFeature\n");
		/* No HUB features supported */
		अवरोध;

	हाल SetPortFeature:
		dev_dbg(hsotg->dev, "SetPortFeature\n");
		अगर (wvalue != USB_PORT_FEAT_TEST && (!windex || windex > 1))
			जाओ error;

		अगर (!hsotg->flags.b.port_connect_status) अणु
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * वापस without करोing anything since the port
			 * रेजिस्टर can't be written अगर the core is in device
			 * mode.
			 */
			अवरोध;
		पूर्ण

		चयन (wvalue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_SUSPEND\n");
			अगर (windex != hsotg->otg_port)
				जाओ error;
			अगर (!hsotg->bus_suspended)
				retval = dwc2_port_suspend(hsotg, windex);
			अवरोध;

		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_POWER\n");
			hprt0 = dwc2_पढ़ो_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			hprt0 |= HPRT0_PWR;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
			अगर (!pwr)
				dwc2_vbus_supply_init(hsotg);
			अवरोध;

		हाल USB_PORT_FEAT_RESET:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_RESET\n");

			hprt0 = dwc2_पढ़ो_hprt0(hsotg);

			अगर (hsotg->hibernated) अणु
				retval = dwc2_निकास_hibernation(hsotg, 0, 1, 1);
				अगर (retval)
					dev_err(hsotg->dev,
						"exit hibernation failed\n");
			पूर्ण

			अगर (hsotg->in_ppd) अणु
				retval = dwc2_निकास_partial_घातer_करोwn(hsotg, 1,
								      true);
				अगर (retval)
					dev_err(hsotg->dev,
						"exit partial_power_down failed\n");
			पूर्ण

			अगर (hsotg->params.घातer_करोwn ==
			    DWC2_POWER_DOWN_PARAM_NONE && hsotg->bus_suspended)
				dwc2_host_निकास_घड़ी_gating(hsotg, 0);

			pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
			pcgctl &= ~(PCGCTL_ENBL_SLEEP_GATING | PCGCTL_STOPPCLK);
			dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
			/* ??? Original driver करोes this */
			dwc2_ग_लिखोl(hsotg, 0, PCGCTL);

			hprt0 = dwc2_पढ़ो_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			/* Clear suspend bit अगर resetting from suspend state */
			hprt0 &= ~HPRT0_SUSP;

			/*
			 * When B-Host the Port reset bit is set in the Start
			 * HCD Callback function, so that the reset is started
			 * within 1ms of the HNP success पूर्णांकerrupt
			 */
			अगर (!dwc2_hcd_is_b_host(hsotg)) अणु
				hprt0 |= HPRT0_PWR | HPRT0_RST;
				dev_dbg(hsotg->dev,
					"In host mode, hprt0=%08x\n", hprt0);
				dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
				अगर (!pwr)
					dwc2_vbus_supply_init(hsotg);
			पूर्ण

			/* Clear reset bit in 10ms (FS/LS) or 50ms (HS) */
			msleep(50);
			hprt0 &= ~HPRT0_RST;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
			hsotg->lx_state = DWC2_L0; /* Now back to On state */
			अवरोध;

		हाल USB_PORT_FEAT_INDICATOR:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_INDICATOR\n");
			/* Not supported */
			अवरोध;

		हाल USB_PORT_FEAT_TEST:
			hprt0 = dwc2_पढ़ो_hprt0(hsotg);
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_TEST\n");
			hprt0 &= ~HPRT0_TSTCTL_MASK;
			hprt0 |= (windex >> 8) << HPRT0_TSTCTL_SHIFT;
			dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
			अवरोध;

		शेष:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"SetPortFeature %1xh unknown or unsupported\n",
				wvalue);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
error:
		retval = -EINVAL;
		dev_dbg(hsotg->dev,
			"Unknown hub control request: %1xh wIndex: %1xh wValue: %1xh\n",
			typereq, windex, wvalue);
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक dwc2_hcd_is_status_changed(काष्ठा dwc2_hsotg *hsotg, पूर्णांक port)
अणु
	पूर्णांक retval;

	अगर (port != 1)
		वापस -EINVAL;

	retval = (hsotg->flags.b.port_connect_status_change ||
		  hsotg->flags.b.port_reset_change ||
		  hsotg->flags.b.port_enable_change ||
		  hsotg->flags.b.port_suspend_change ||
		  hsotg->flags.b.port_over_current_change);

	अगर (retval) अणु
		dev_dbg(hsotg->dev,
			"DWC OTG HCD HUB STATUS DATA: Root port status changed\n");
		dev_dbg(hsotg->dev, "  port_connect_status_change: %d\n",
			hsotg->flags.b.port_connect_status_change);
		dev_dbg(hsotg->dev, "  port_reset_change: %d\n",
			hsotg->flags.b.port_reset_change);
		dev_dbg(hsotg->dev, "  port_enable_change: %d\n",
			hsotg->flags.b.port_enable_change);
		dev_dbg(hsotg->dev, "  port_suspend_change: %d\n",
			hsotg->flags.b.port_suspend_change);
		dev_dbg(hsotg->dev, "  port_over_current_change: %d\n",
			hsotg->flags.b.port_over_current_change);
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक dwc2_hcd_get_frame_number(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hfnum = dwc2_पढ़ोl(hsotg, HFNUM);

#अगर_घोषित DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "DWC OTG HCD GET FRAME NUMBER %d\n",
		 (hfnum & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT);
#पूर्ण_अगर
	वापस (hfnum & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT;
पूर्ण

पूर्णांक dwc2_hcd_get_future_frame_number(काष्ठा dwc2_hsotg *hsotg, पूर्णांक us)
अणु
	u32 hprt = dwc2_पढ़ोl(hsotg, HPRT0);
	u32 hfir = dwc2_पढ़ोl(hsotg, HFIR);
	u32 hfnum = dwc2_पढ़ोl(hsotg, HFNUM);
	अचिन्हित पूर्णांक us_per_frame;
	अचिन्हित पूर्णांक frame_number;
	अचिन्हित पूर्णांक reमुख्यing;
	अचिन्हित पूर्णांक पूर्णांकerval;
	अचिन्हित पूर्णांक phy_clks;

	/* High speed has 125 us per (micro) frame; others are 1 ms per */
	us_per_frame = (hprt & HPRT0_SPD_MASK) ? 1000 : 125;

	/* Extract fields */
	frame_number = (hfnum & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT;
	reमुख्यing = (hfnum & HFNUM_FRREM_MASK) >> HFNUM_FRREM_SHIFT;
	पूर्णांकerval = (hfir & HFIR_FRINT_MASK) >> HFIR_FRINT_SHIFT;

	/*
	 * Number of phy घड़ीs since the last tick of the frame number after
	 * "us" has passed.
	 */
	phy_clks = (पूर्णांकerval - reमुख्यing) +
		   DIV_ROUND_UP(पूर्णांकerval * us, us_per_frame);

	वापस dwc2_frame_num_inc(frame_number, phy_clks / पूर्णांकerval);
पूर्ण

पूर्णांक dwc2_hcd_is_b_host(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस hsotg->op_state == OTG_STATE_B_HOST;
पूर्ण

अटल काष्ठा dwc2_hcd_urb *dwc2_hcd_urb_alloc(काष्ठा dwc2_hsotg *hsotg,
					       पूर्णांक iso_desc_count,
					       gfp_t mem_flags)
अणु
	काष्ठा dwc2_hcd_urb *urb;

	urb = kzalloc(काष्ठा_size(urb, iso_descs, iso_desc_count), mem_flags);
	अगर (urb)
		urb->packet_count = iso_desc_count;
	वापस urb;
पूर्ण

अटल व्योम dwc2_hcd_urb_set_pipeinfo(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_hcd_urb *urb, u8 dev_addr,
				      u8 ep_num, u8 ep_type, u8 ep_dir,
				      u16 maxp, u16 maxp_mult)
अणु
	अगर (dbg_perio() ||
	    ep_type == USB_ENDPOINT_XFER_BULK ||
	    ep_type == USB_ENDPOINT_XFER_CONTROL)
		dev_vdbg(hsotg->dev,
			 "addr=%d, ep_num=%d, ep_dir=%1x, ep_type=%1x, maxp=%d (%d mult)\n",
			 dev_addr, ep_num, ep_dir, ep_type, maxp, maxp_mult);
	urb->pipe_info.dev_addr = dev_addr;
	urb->pipe_info.ep_num = ep_num;
	urb->pipe_info.pipe_type = ep_type;
	urb->pipe_info.pipe_dir = ep_dir;
	urb->pipe_info.maxp = maxp;
	urb->pipe_info.maxp_mult = maxp_mult;
पूर्ण

/*
 * NOTE: This function will be हटाओd once the peripheral controller code
 * is पूर्णांकegrated and the driver is stable
 */
व्योम dwc2_hcd_dump_state(काष्ठा dwc2_hsotg *hsotg)
अणु
#अगर_घोषित DEBUG
	काष्ठा dwc2_host_chan *chan;
	काष्ठा dwc2_hcd_urb *urb;
	काष्ठा dwc2_qtd *qtd;
	पूर्णांक num_channels;
	u32 np_tx_status;
	u32 p_tx_status;
	पूर्णांक i;

	num_channels = hsotg->params.host_channels;
	dev_dbg(hsotg->dev, "\n");
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "HCD State:\n");
	dev_dbg(hsotg->dev, "  Num channels: %d\n", num_channels);

	क्रम (i = 0; i < num_channels; i++) अणु
		chan = hsotg->hc_ptr_array[i];
		dev_dbg(hsotg->dev, "  Channel %d:\n", i);
		dev_dbg(hsotg->dev,
			"    dev_addr: %d, ep_num: %d, ep_is_in: %d\n",
			chan->dev_addr, chan->ep_num, chan->ep_is_in);
		dev_dbg(hsotg->dev, "    speed: %d\n", chan->speed);
		dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
		dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
		dev_dbg(hsotg->dev, "    data_pid_start: %d\n",
			chan->data_pid_start);
		dev_dbg(hsotg->dev, "    multi_count: %d\n", chan->multi_count);
		dev_dbg(hsotg->dev, "    xfer_started: %d\n",
			chan->xfer_started);
		dev_dbg(hsotg->dev, "    xfer_buf: %p\n", chan->xfer_buf);
		dev_dbg(hsotg->dev, "    xfer_dma: %08lx\n",
			(अचिन्हित दीर्घ)chan->xfer_dma);
		dev_dbg(hsotg->dev, "    xfer_len: %d\n", chan->xfer_len);
		dev_dbg(hsotg->dev, "    xfer_count: %d\n", chan->xfer_count);
		dev_dbg(hsotg->dev, "    halt_on_queue: %d\n",
			chan->halt_on_queue);
		dev_dbg(hsotg->dev, "    halt_pending: %d\n",
			chan->halt_pending);
		dev_dbg(hsotg->dev, "    halt_status: %d\n", chan->halt_status);
		dev_dbg(hsotg->dev, "    do_split: %d\n", chan->करो_split);
		dev_dbg(hsotg->dev, "    complete_split: %d\n",
			chan->complete_split);
		dev_dbg(hsotg->dev, "    hub_addr: %d\n", chan->hub_addr);
		dev_dbg(hsotg->dev, "    hub_port: %d\n", chan->hub_port);
		dev_dbg(hsotg->dev, "    xact_pos: %d\n", chan->xact_pos);
		dev_dbg(hsotg->dev, "    requests: %d\n", chan->requests);
		dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);

		अगर (chan->xfer_started) अणु
			u32 hfnum, hcअक्षर, hctsiz, hcपूर्णांक, hcपूर्णांकmsk;

			hfnum = dwc2_पढ़ोl(hsotg, HFNUM);
			hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(i));
			hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(i));
			hcपूर्णांक = dwc2_पढ़ोl(hsotg, HCINT(i));
			hcपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HCINTMSK(i));
			dev_dbg(hsotg->dev, "    hfnum: 0x%08x\n", hfnum);
			dev_dbg(hsotg->dev, "    hcchar: 0x%08x\n", hcअक्षर);
			dev_dbg(hsotg->dev, "    hctsiz: 0x%08x\n", hctsiz);
			dev_dbg(hsotg->dev, "    hcint: 0x%08x\n", hcपूर्णांक);
			dev_dbg(hsotg->dev, "    hcintmsk: 0x%08x\n", hcपूर्णांकmsk);
		पूर्ण

		अगर (!(chan->xfer_started && chan->qh))
			जारी;

		list_क्रम_each_entry(qtd, &chan->qh->qtd_list, qtd_list_entry) अणु
			अगर (!qtd->in_process)
				अवरोध;
			urb = qtd->urb;
			dev_dbg(hsotg->dev, "    URB Info:\n");
			dev_dbg(hsotg->dev, "      qtd: %p, urb: %p\n",
				qtd, urb);
			अगर (urb) अणु
				dev_dbg(hsotg->dev,
					"      Dev: %d, EP: %d %s\n",
					dwc2_hcd_get_dev_addr(&urb->pipe_info),
					dwc2_hcd_get_ep_num(&urb->pipe_info),
					dwc2_hcd_is_pipe_in(&urb->pipe_info) ?
					"IN" : "OUT");
				dev_dbg(hsotg->dev,
					"      Max packet size: %d (%d mult)\n",
					dwc2_hcd_get_maxp(&urb->pipe_info),
					dwc2_hcd_get_maxp_mult(&urb->pipe_info));
				dev_dbg(hsotg->dev,
					"      transfer_buffer: %p\n",
					urb->buf);
				dev_dbg(hsotg->dev,
					"      transfer_dma: %08lx\n",
					(अचिन्हित दीर्घ)urb->dma);
				dev_dbg(hsotg->dev,
					"      transfer_buffer_length: %d\n",
					urb->length);
				dev_dbg(hsotg->dev, "      actual_length: %d\n",
					urb->actual_length);
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(hsotg->dev, "  non_periodic_channels: %d\n",
		hsotg->non_periodic_channels);
	dev_dbg(hsotg->dev, "  periodic_channels: %d\n",
		hsotg->periodic_channels);
	dev_dbg(hsotg->dev, "  periodic_usecs: %d\n", hsotg->periodic_usecs);
	np_tx_status = dwc2_पढ़ोl(hsotg, GNPTXSTS);
	dev_dbg(hsotg->dev, "  NP Tx Req Queue Space Avail: %d\n",
		(np_tx_status & TXSTS_QSPCAVAIL_MASK) >> TXSTS_QSPCAVAIL_SHIFT);
	dev_dbg(hsotg->dev, "  NP Tx FIFO Space Avail: %d\n",
		(np_tx_status & TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT);
	p_tx_status = dwc2_पढ़ोl(hsotg, HPTXSTS);
	dev_dbg(hsotg->dev, "  P Tx Req Queue Space Avail: %d\n",
		(p_tx_status & TXSTS_QSPCAVAIL_MASK) >> TXSTS_QSPCAVAIL_SHIFT);
	dev_dbg(hsotg->dev, "  P Tx FIFO Space Avail: %d\n",
		(p_tx_status & TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT);
	dwc2_dump_global_रेजिस्टरs(hsotg);
	dwc2_dump_host_रेजिस्टरs(hsotg);
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "\n");
#पूर्ण_अगर
पूर्ण

काष्ठा wrapper_priv_data अणु
	काष्ठा dwc2_hsotg *hsotg;
पूर्ण;

/* Gets the dwc2_hsotg from a usb_hcd */
अटल काष्ठा dwc2_hsotg *dwc2_hcd_to_hsotg(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा wrapper_priv_data *p;

	p = (काष्ठा wrapper_priv_data *)&hcd->hcd_priv;
	वापस p->hsotg;
पूर्ण

/**
 * dwc2_host_get_tt_info() - Get the dwc2_tt associated with context
 *
 * This will get the dwc2_tt काष्ठाure (and ttport) associated with the given
 * context (which is really just a काष्ठा urb poपूर्णांकer).
 *
 * The first समय this is called क्रम a given TT we allocate memory क्रम our
 * काष्ठाure.  When everyone is करोne and has called dwc2_host_put_tt_info()
 * then the refcount क्रम the काष्ठाure will go to 0 and we'll मुक्त it.
 *
 * @hsotg:     The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @context:   The priv poपूर्णांकer from a काष्ठा dwc2_hcd_urb.
 * @mem_flags: Flags क्रम allocating memory.
 * @ttport:    We'll return this device's port number here.  That's used to
 *             reference पूर्णांकo the biपंचांगap अगर we're on a multi_tt hub.
 *
 * Return: a poपूर्णांकer to a काष्ठा dwc2_tt.  Don't क्रमget to call
 *         dwc2_host_put_tt_info()!  Returns शून्य upon memory alloc failure.
 */

काष्ठा dwc2_tt *dwc2_host_get_tt_info(काष्ठा dwc2_hsotg *hsotg, व्योम *context,
				      gfp_t mem_flags, पूर्णांक *ttport)
अणु
	काष्ठा urb *urb = context;
	काष्ठा dwc2_tt *dwc_tt = शून्य;

	अगर (urb->dev->tt) अणु
		*ttport = urb->dev->ttport;

		dwc_tt = urb->dev->tt->hcpriv;
		अगर (!dwc_tt) अणु
			माप_प्रकार biपंचांगap_size;

			/*
			 * For single_tt we need one schedule.  For multi_tt
			 * we need one per port.
			 */
			biपंचांगap_size = DWC2_ELEMENTS_PER_LS_BITMAP *
				      माप(dwc_tt->periodic_biपंचांगaps[0]);
			अगर (urb->dev->tt->multi)
				biपंचांगap_size *= urb->dev->tt->hub->maxchild;

			dwc_tt = kzalloc(माप(*dwc_tt) + biपंचांगap_size,
					 mem_flags);
			अगर (!dwc_tt)
				वापस शून्य;

			dwc_tt->usb_tt = urb->dev->tt;
			dwc_tt->usb_tt->hcpriv = dwc_tt;
		पूर्ण

		dwc_tt->refcount++;
	पूर्ण

	वापस dwc_tt;
पूर्ण

/**
 * dwc2_host_put_tt_info() - Put the dwc2_tt from dwc2_host_get_tt_info()
 *
 * Frees resources allocated by dwc2_host_get_tt_info() अगर all current holders
 * of the काष्ठाure are करोne.
 *
 * It's OK to call this with शून्य.
 *
 * @hsotg:     The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @dwc_tt:    The poपूर्णांकer वापसed by dwc2_host_get_tt_info.
 */
व्योम dwc2_host_put_tt_info(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_tt *dwc_tt)
अणु
	/* Model kमुक्त and make put of शून्य a no-op */
	अगर (!dwc_tt)
		वापस;

	WARN_ON(dwc_tt->refcount < 1);

	dwc_tt->refcount--;
	अगर (!dwc_tt->refcount) अणु
		dwc_tt->usb_tt->hcpriv = शून्य;
		kमुक्त(dwc_tt);
	पूर्ण
पूर्ण

पूर्णांक dwc2_host_get_speed(काष्ठा dwc2_hsotg *hsotg, व्योम *context)
अणु
	काष्ठा urb *urb = context;

	वापस urb->dev->speed;
पूर्ण

अटल व्योम dwc2_allocate_bus_bandwidth(काष्ठा usb_hcd *hcd, u16 bw,
					काष्ठा urb *urb)
अणु
	काष्ठा usb_bus *bus = hcd_to_bus(hcd);

	अगर (urb->पूर्णांकerval)
		bus->bandwidth_allocated += bw / urb->पूर्णांकerval;
	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
		bus->bandwidth_isoc_reqs++;
	अन्यथा
		bus->bandwidth_पूर्णांक_reqs++;
पूर्ण

अटल व्योम dwc2_मुक्त_bus_bandwidth(काष्ठा usb_hcd *hcd, u16 bw,
				    काष्ठा urb *urb)
अणु
	काष्ठा usb_bus *bus = hcd_to_bus(hcd);

	अगर (urb->पूर्णांकerval)
		bus->bandwidth_allocated -= bw / urb->पूर्णांकerval;
	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
		bus->bandwidth_isoc_reqs--;
	अन्यथा
		bus->bandwidth_पूर्णांक_reqs--;
पूर्ण

/*
 * Sets the final status of an URB and वापसs it to the upper layer. Any
 * required cleanup of the URB is perक्रमmed.
 *
 * Must be called with पूर्णांकerrupt disabled and spinlock held
 */
व्योम dwc2_host_complete(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qtd *qtd,
			पूर्णांक status)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	अगर (!qtd) अणु
		dev_dbg(hsotg->dev, "## %s: qtd is NULL ##\n", __func__);
		वापस;
	पूर्ण

	अगर (!qtd->urb) अणु
		dev_dbg(hsotg->dev, "## %s: qtd->urb is NULL ##\n", __func__);
		वापस;
	पूर्ण

	urb = qtd->urb->priv;
	अगर (!urb) अणु
		dev_dbg(hsotg->dev, "## %s: urb->priv is NULL ##\n", __func__);
		वापस;
	पूर्ण

	urb->actual_length = dwc2_hcd_urb_get_actual_length(qtd->urb);

	अगर (dbg_urb(urb))
		dev_vdbg(hsotg->dev,
			 "%s: urb %p device %d ep %d-%s status %d actual %d\n",
			 __func__, urb, usb_pipedevice(urb->pipe),
			 usb_pipeendpoपूर्णांक(urb->pipe),
			 usb_pipein(urb->pipe) ? "IN" : "OUT", status,
			 urb->actual_length);

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		urb->error_count = dwc2_hcd_urb_get_error_count(qtd->urb);
		क्रम (i = 0; i < urb->number_of_packets; ++i) अणु
			urb->iso_frame_desc[i].actual_length =
				dwc2_hcd_urb_get_iso_desc_actual_length(
						qtd->urb, i);
			urb->iso_frame_desc[i].status =
				dwc2_hcd_urb_get_iso_desc_status(qtd->urb, i);
		पूर्ण
	पूर्ण

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS && dbg_perio()) अणु
		क्रम (i = 0; i < urb->number_of_packets; i++)
			dev_vdbg(hsotg->dev, " ISO Desc %d status %d\n",
				 i, urb->iso_frame_desc[i].status);
	पूर्ण

	urb->status = status;
	अगर (!status) अणु
		अगर ((urb->transfer_flags & URB_SHORT_NOT_OK) &&
		    urb->actual_length < urb->transfer_buffer_length)
			urb->status = -EREMOTEIO;
	पूर्ण

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS ||
	    usb_pipetype(urb->pipe) == PIPE_INTERRUPT) अणु
		काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;

		अगर (ep)
			dwc2_मुक्त_bus_bandwidth(dwc2_hsotg_to_hcd(hsotg),
					dwc2_hcd_get_ep_bandwidth(hsotg, ep),
					urb);
	पूर्ण

	usb_hcd_unlink_urb_from_ep(dwc2_hsotg_to_hcd(hsotg), urb);
	urb->hcpriv = शून्य;
	kमुक्त(qtd->urb);
	qtd->urb = शून्य;

	usb_hcd_giveback_urb(dwc2_hsotg_to_hcd(hsotg), urb, status);
पूर्ण

/*
 * Work queue function क्रम starting the HCD when A-Cable is connected
 */
अटल व्योम dwc2_hcd_start_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc2_hsotg *hsotg = container_of(work, काष्ठा dwc2_hsotg,
						start_work.work);

	dev_dbg(hsotg->dev, "%s() %p\n", __func__, hsotg);
	dwc2_host_start(hsotg);
पूर्ण

/*
 * Reset work queue function
 */
अटल व्योम dwc2_hcd_reset_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc2_hsotg *hsotg = container_of(work, काष्ठा dwc2_hsotg,
						reset_work.work);
	अचिन्हित दीर्घ flags;
	u32 hprt0;

	dev_dbg(hsotg->dev, "USB RESET function called\n");

	spin_lock_irqsave(&hsotg->lock, flags);

	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hprt0 &= ~HPRT0_RST;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	hsotg->flags.b.port_reset_change = 1;

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

अटल व्योम dwc2_hcd_phy_reset_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc2_hsotg *hsotg = container_of(work, काष्ठा dwc2_hsotg,
						phy_reset_work);
	पूर्णांक ret;

	ret = phy_reset(hsotg->phy);
	अगर (ret)
		dev_warn(hsotg->dev, "PHY reset failed\n");
पूर्ण

/*
 * =========================================================================
 *  Linux HC Driver Functions
 * =========================================================================
 */

/*
 * Initializes the DWC_otg controller and its root hub and prepares it क्रम host
 * mode operation. Activates the root port. Returns 0 on success and a negative
 * error code on failure.
 */
अटल पूर्णांक _dwc2_hcd_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	काष्ठा usb_bus *bus = hcd_to_bus(hcd);
	अचिन्हित दीर्घ flags;
	u32 hprt0;
	पूर्णांक ret;

	dev_dbg(hsotg->dev, "DWC OTG HCD START\n");

	spin_lock_irqsave(&hsotg->lock, flags);
	hsotg->lx_state = DWC2_L0;
	hcd->state = HC_STATE_RUNNING;
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	अगर (dwc2_is_device_mode(hsotg)) अणु
		spin_unlock_irqrestore(&hsotg->lock, flags);
		वापस 0;	/* why 0 ?? */
	पूर्ण

	dwc2_hcd_reinit(hsotg);

	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	/* Has vbus घातer been turned on in dwc2_core_host_init ? */
	अगर (hprt0 & HPRT0_PWR) अणु
		/* Enable बाह्यal vbus supply beक्रमe resuming root hub */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		ret = dwc2_vbus_supply_init(hsotg);
		अगर (ret)
			वापस ret;
		spin_lock_irqsave(&hsotg->lock, flags);
	पूर्ण

	/* Initialize and connect root hub अगर one is not alपढ़ोy attached */
	अगर (bus->root_hub) अणु
		dev_dbg(hsotg->dev, "DWC OTG HCD Has Root Hub\n");
		/* Inक्रमm the HUB driver to resume */
		usb_hcd_resume_root_hub(hcd);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस 0;
पूर्ण

/*
 * Halts the DWC_otg host mode operations in a clean manner. USB transfers are
 * stopped.
 */
अटल व्योम _dwc2_hcd_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	अचिन्हित दीर्घ flags;
	u32 hprt0;

	/* Turn off all host-specअगरic पूर्णांकerrupts */
	dwc2_disable_host_पूर्णांकerrupts(hsotg);

	/* Wait क्रम पूर्णांकerrupt processing to finish */
	synchronize_irq(hcd->irq);

	spin_lock_irqsave(&hsotg->lock, flags);
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	/* Ensure hcd is disconnected */
	dwc2_hcd_disconnect(hsotg, true);
	dwc2_hcd_stop(hsotg);
	hsotg->lx_state = DWC2_L3;
	hcd->state = HC_STATE_HALT;
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irqrestore(&hsotg->lock, flags);

	/* keep balanced supply init/निकास by checking HPRT0_PWR */
	अगर (hprt0 & HPRT0_PWR)
		dwc2_vbus_supply_निकास(hsotg);

	usleep_range(1000, 3000);
पूर्ण

अटल पूर्णांक _dwc2_hcd_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hsotg->lock, flags);

	अगर (dwc2_is_device_mode(hsotg))
		जाओ unlock;

	अगर (hsotg->lx_state != DWC2_L0)
		जाओ unlock;

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		जाओ unlock;

	अगर (hsotg->op_state == OTG_STATE_B_PERIPHERAL)
		जाओ unlock;

	अगर (hsotg->bus_suspended)
		जाओ skip_घातer_saving;

	अगर (hsotg->flags.b.port_connect_status == 0)
		जाओ skip_घातer_saving;

	चयन (hsotg->params.घातer_करोwn) अणु
	हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
		/* Enter partial_घातer_करोwn */
		ret = dwc2_enter_partial_घातer_करोwn(hsotg);
		अगर (ret)
			dev_err(hsotg->dev,
				"enter partial_power_down failed\n");
		/* After entering suspend, hardware is not accessible */
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
		/* Enter hibernation */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		ret = dwc2_enter_hibernation(hsotg, 1);
		अगर (ret)
			dev_err(hsotg->dev, "enter hibernation failed\n");
		spin_lock_irqsave(&hsotg->lock, flags);

		/* After entering suspend, hardware is not accessible */
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_NONE:
		/*
		 * If not hibernation nor partial घातer करोwn are supported,
		 * घड़ी gating is used to save घातer.
		 */
		dwc2_host_enter_घड़ी_gating(hsotg);

		/* After entering suspend, hardware is not accessible */
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	शेष:
		जाओ skip_घातer_saving;
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);
	dwc2_vbus_supply_निकास(hsotg);
	spin_lock_irqsave(&hsotg->lock, flags);

	/* Ask phy to be suspended */
	अगर (!IS_ERR_OR_शून्य(hsotg->uphy)) अणु
		spin_unlock_irqrestore(&hsotg->lock, flags);
		usb_phy_set_suspend(hsotg->uphy, true);
		spin_lock_irqsave(&hsotg->lock, flags);
	पूर्ण

skip_घातer_saving:
	hsotg->lx_state = DWC2_L2;
unlock:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक _dwc2_hcd_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	अचिन्हित दीर्घ flags;
	u32 hprt0;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hsotg->lock, flags);

	अगर (dwc2_is_device_mode(hsotg))
		जाओ unlock;

	अगर (hsotg->lx_state != DWC2_L2)
		जाओ unlock;

	hprt0 = dwc2_पढ़ो_hprt0(hsotg);

	/*
	 * Added port connection status checking which prevents निकासing from
	 * Partial Power Down mode from _dwc2_hcd_resume() अगर not in Partial
	 * Power Down mode.
	 */
	अगर (hprt0 & HPRT0_CONNSTS) अणु
		hsotg->lx_state = DWC2_L0;
		जाओ unlock;
	पूर्ण

	चयन (hsotg->params.घातer_करोwn) अणु
	हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
		ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 0, true);
		अगर (ret)
			dev_err(hsotg->dev,
				"exit partial_power_down failed\n");
		/*
		 * Set HW accessible bit beक्रमe घातering on the controller
		 * since an पूर्णांकerrupt may rise.
		 */
		set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
		ret = dwc2_निकास_hibernation(hsotg, 0, 0, 1);
		अगर (ret)
			dev_err(hsotg->dev, "exit hibernation failed.\n");

		/*
		 * Set HW accessible bit beक्रमe घातering on the controller
		 * since an पूर्णांकerrupt may rise.
		 */
		set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_NONE:
		/*
		 * If not hibernation nor partial घातer करोwn are supported,
		 * port resume is करोne using the घड़ी gating programming flow.
		 */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		dwc2_host_निकास_घड़ी_gating(hsotg, 0);

		/*
		 * Initialize the Core क्रम Host mode, as after प्रणाली resume
		 * the global पूर्णांकerrupts are disabled.
		 */
		dwc2_core_init(hsotg, false);
		dwc2_enable_global_पूर्णांकerrupts(hsotg);
		dwc2_hcd_reinit(hsotg);
		spin_lock_irqsave(&hsotg->lock, flags);

		/*
		 * Set HW accessible bit beक्रमe घातering on the controller
		 * since an पूर्णांकerrupt may rise.
		 */
		set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
		अवरोध;
	शेष:
		hsotg->lx_state = DWC2_L0;
		जाओ unlock;
	पूर्ण

	/* Change Root port status, as port status change occurred after resume.*/
	hsotg->flags.b.port_suspend_change = 1;

	/*
	 * Enable घातer अगर not alपढ़ोy करोne.
	 * This must not be spinlocked since duration
	 * of this call is unknown.
	 */
	अगर (!IS_ERR_OR_शून्य(hsotg->uphy)) अणु
		spin_unlock_irqrestore(&hsotg->lock, flags);
		usb_phy_set_suspend(hsotg->uphy, false);
		spin_lock_irqsave(&hsotg->lock, flags);
	पूर्ण

	/* Enable बाह्यal vbus supply after resuming the port. */
	spin_unlock_irqrestore(&hsotg->lock, flags);
	dwc2_vbus_supply_init(hsotg);

	/* Wait क्रम controller to correctly update D+/D- level */
	usleep_range(3000, 5000);
	spin_lock_irqsave(&hsotg->lock, flags);

	/*
	 * Clear Port Enable and Port Status changes.
	 * Enable Port Power.
	 */
	dwc2_ग_लिखोl(hsotg, HPRT0_PWR | HPRT0_CONNDET |
			HPRT0_ENACHG, HPRT0);

	/* Wait क्रम controller to detect Port Connect */
	spin_unlock_irqrestore(&hsotg->lock, flags);
	usleep_range(5000, 7000);
	spin_lock_irqsave(&hsotg->lock, flags);
unlock:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस ret;
पूर्ण

/* Returns the current frame number */
अटल पूर्णांक _dwc2_hcd_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	वापस dwc2_hcd_get_frame_number(hsotg);
पूर्ण

अटल व्योम dwc2_dump_urb_info(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
			       अक्षर *fn_name)
अणु
#अगर_घोषित VERBOSE_DEBUG
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	अक्षर *pipetype = शून्य;
	अक्षर *speed = शून्य;

	dev_vdbg(hsotg->dev, "%s, urb %p\n", fn_name, urb);
	dev_vdbg(hsotg->dev, "  Device address: %d\n",
		 usb_pipedevice(urb->pipe));
	dev_vdbg(hsotg->dev, "  Endpoint: %d, %s\n",
		 usb_pipeendpoपूर्णांक(urb->pipe),
		 usb_pipein(urb->pipe) ? "IN" : "OUT");

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
		pipetype = "CONTROL";
		अवरोध;
	हाल PIPE_BULK:
		pipetype = "BULK";
		अवरोध;
	हाल PIPE_INTERRUPT:
		pipetype = "INTERRUPT";
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		pipetype = "ISOCHRONOUS";
		अवरोध;
	पूर्ण

	dev_vdbg(hsotg->dev, "  Endpoint type: %s %s (%s)\n", pipetype,
		 usb_urb_dir_in(urb) ? "IN" : "OUT", usb_pipein(urb->pipe) ?
		 "IN" : "OUT");

	चयन (urb->dev->speed) अणु
	हाल USB_SPEED_HIGH:
		speed = "HIGH";
		अवरोध;
	हाल USB_SPEED_FULL:
		speed = "FULL";
		अवरोध;
	हाल USB_SPEED_LOW:
		speed = "LOW";
		अवरोध;
	शेष:
		speed = "UNKNOWN";
		अवरोध;
	पूर्ण

	dev_vdbg(hsotg->dev, "  Speed: %s\n", speed);
	dev_vdbg(hsotg->dev, "  Max packet size: %d (%d mult)\n",
		 usb_endpoपूर्णांक_maxp(&urb->ep->desc),
		 usb_endpoपूर्णांक_maxp_mult(&urb->ep->desc));

	dev_vdbg(hsotg->dev, "  Data buffer length: %d\n",
		 urb->transfer_buffer_length);
	dev_vdbg(hsotg->dev, "  Transfer buffer: %p, Transfer DMA: %08lx\n",
		 urb->transfer_buffer, (अचिन्हित दीर्घ)urb->transfer_dma);
	dev_vdbg(hsotg->dev, "  Setup buffer: %p, Setup DMA: %08lx\n",
		 urb->setup_packet, (अचिन्हित दीर्घ)urb->setup_dma);
	dev_vdbg(hsotg->dev, "  Interval: %d\n", urb->पूर्णांकerval);

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		पूर्णांक i;

		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			dev_vdbg(hsotg->dev, "  ISO Desc %d:\n", i);
			dev_vdbg(hsotg->dev, "    offset: %d, length %d\n",
				 urb->iso_frame_desc[i].offset,
				 urb->iso_frame_desc[i].length);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Starts processing a USB transfer request specअगरied by a USB Request Block
 * (URB). mem_flags indicates the type of memory allocation to use जबतक
 * processing this URB.
 */
अटल पूर्णांक _dwc2_hcd_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				 gfp_t mem_flags)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;
	काष्ठा dwc2_hcd_urb *dwc2_urb;
	पूर्णांक i;
	पूर्णांक retval;
	पूर्णांक alloc_bandwidth = 0;
	u8 ep_type = 0;
	u32 tflags = 0;
	व्योम *buf;
	अचिन्हित दीर्घ flags;
	काष्ठा dwc2_qh *qh;
	bool qh_allocated = false;
	काष्ठा dwc2_qtd *qtd;
	काष्ठा dwc2_gregs_backup *gr;

	gr = &hsotg->gr_backup;

	अगर (dbg_urb(urb)) अणु
		dev_vdbg(hsotg->dev, "DWC OTG HCD URB Enqueue\n");
		dwc2_dump_urb_info(hcd, urb, "urb_enqueue");
	पूर्ण

	अगर (hsotg->hibernated) अणु
		अगर (gr->gotgctl & GOTGCTL_CURMODE_HOST)
			retval = dwc2_निकास_hibernation(hsotg, 0, 0, 1);
		अन्यथा
			retval = dwc2_निकास_hibernation(hsotg, 0, 0, 0);

		अगर (retval)
			dev_err(hsotg->dev,
				"exit hibernation failed.\n");
	पूर्ण

	अगर (hsotg->in_ppd) अणु
		retval = dwc2_निकास_partial_घातer_करोwn(hsotg, 0, true);
		अगर (retval)
			dev_err(hsotg->dev,
				"exit partial_power_down failed\n");
	पूर्ण

	अगर (hsotg->params.घातer_करोwn == DWC2_POWER_DOWN_PARAM_NONE &&
	    hsotg->bus_suspended) अणु
		अगर (dwc2_is_device_mode(hsotg))
			dwc2_gadget_निकास_घड़ी_gating(hsotg, 0);
		अन्यथा
			dwc2_host_निकास_घड़ी_gating(hsotg, 0);
	पूर्ण

	अगर (!ep)
		वापस -EINVAL;

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS ||
	    usb_pipetype(urb->pipe) == PIPE_INTERRUPT) अणु
		spin_lock_irqsave(&hsotg->lock, flags);
		अगर (!dwc2_hcd_is_bandwidth_allocated(hsotg, ep))
			alloc_bandwidth = 1;
		spin_unlock_irqrestore(&hsotg->lock, flags);
	पूर्ण

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
		ep_type = USB_ENDPOINT_XFER_CONTROL;
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		ep_type = USB_ENDPOINT_XFER_ISOC;
		अवरोध;
	हाल PIPE_BULK:
		ep_type = USB_ENDPOINT_XFER_BULK;
		अवरोध;
	हाल PIPE_INTERRUPT:
		ep_type = USB_ENDPOINT_XFER_INT;
		अवरोध;
	पूर्ण

	dwc2_urb = dwc2_hcd_urb_alloc(hsotg, urb->number_of_packets,
				      mem_flags);
	अगर (!dwc2_urb)
		वापस -ENOMEM;

	dwc2_hcd_urb_set_pipeinfo(hsotg, dwc2_urb, usb_pipedevice(urb->pipe),
				  usb_pipeendpoपूर्णांक(urb->pipe), ep_type,
				  usb_pipein(urb->pipe),
				  usb_endpoपूर्णांक_maxp(&ep->desc),
				  usb_endpoपूर्णांक_maxp_mult(&ep->desc));

	buf = urb->transfer_buffer;

	अगर (hcd_uses_dma(hcd)) अणु
		अगर (!buf && (urb->transfer_dma & 3)) अणु
			dev_err(hsotg->dev,
				"%s: unaligned transfer with no transfer_buffer",
				__func__);
			retval = -EINVAL;
			जाओ fail0;
		पूर्ण
	पूर्ण

	अगर (!(urb->transfer_flags & URB_NO_INTERRUPT))
		tflags |= URB_GIVEBACK_ASAP;
	अगर (urb->transfer_flags & URB_ZERO_PACKET)
		tflags |= URB_SEND_ZERO_PACKET;

	dwc2_urb->priv = urb;
	dwc2_urb->buf = buf;
	dwc2_urb->dma = urb->transfer_dma;
	dwc2_urb->length = urb->transfer_buffer_length;
	dwc2_urb->setup_packet = urb->setup_packet;
	dwc2_urb->setup_dma = urb->setup_dma;
	dwc2_urb->flags = tflags;
	dwc2_urb->पूर्णांकerval = urb->पूर्णांकerval;
	dwc2_urb->status = -EINPROGRESS;

	क्रम (i = 0; i < urb->number_of_packets; ++i)
		dwc2_hcd_urb_set_iso_desc_params(dwc2_urb, i,
						 urb->iso_frame_desc[i].offset,
						 urb->iso_frame_desc[i].length);

	urb->hcpriv = dwc2_urb;
	qh = (काष्ठा dwc2_qh *)ep->hcpriv;
	/* Create QH क्रम the endpoपूर्णांक अगर it करोesn't exist */
	अगर (!qh) अणु
		qh = dwc2_hcd_qh_create(hsotg, dwc2_urb, mem_flags);
		अगर (!qh) अणु
			retval = -ENOMEM;
			जाओ fail0;
		पूर्ण
		ep->hcpriv = qh;
		qh_allocated = true;
	पूर्ण

	qtd = kzalloc(माप(*qtd), mem_flags);
	अगर (!qtd) अणु
		retval = -ENOMEM;
		जाओ fail1;
	पूर्ण

	spin_lock_irqsave(&hsotg->lock, flags);
	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval)
		जाओ fail2;

	retval = dwc2_hcd_urb_enqueue(hsotg, dwc2_urb, qh, qtd);
	अगर (retval)
		जाओ fail3;

	अगर (alloc_bandwidth) अणु
		dwc2_allocate_bus_bandwidth(hcd,
				dwc2_hcd_get_ep_bandwidth(hsotg, ep),
				urb);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस 0;

fail3:
	dwc2_urb->priv = शून्य;
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	अगर (qh_allocated && qh->channel && qh->channel->qh == qh)
		qh->channel->qh = शून्य;
fail2:
	spin_unlock_irqrestore(&hsotg->lock, flags);
	urb->hcpriv = शून्य;
	kमुक्त(qtd);
fail1:
	अगर (qh_allocated) अणु
		काष्ठा dwc2_qtd *qtd2, *qtd2_पंचांगp;

		ep->hcpriv = शून्य;
		dwc2_hcd_qh_unlink(hsotg, qh);
		/* Free each QTD in the QH's QTD list */
		list_क्रम_each_entry_safe(qtd2, qtd2_पंचांगp, &qh->qtd_list,
					 qtd_list_entry)
			dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd2, qh);
		dwc2_hcd_qh_मुक्त(hsotg, qh);
	पूर्ण
fail0:
	kमुक्त(dwc2_urb);

	वापस retval;
पूर्ण

/*
 * Aborts/cancels a USB transfer request. Always वापसs 0 to indicate success.
 */
अटल पूर्णांक _dwc2_hcd_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				 पूर्णांक status)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	dev_dbg(hsotg->dev, "DWC OTG HCD URB Dequeue\n");
	dwc2_dump_urb_info(hcd, urb, "urb_dequeue");

	spin_lock_irqsave(&hsotg->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ out;

	अगर (!urb->hcpriv) अणु
		dev_dbg(hsotg->dev, "## urb->hcpriv is NULL ##\n");
		जाओ out;
	पूर्ण

	rc = dwc2_hcd_urb_dequeue(hsotg, urb->hcpriv);

	usb_hcd_unlink_urb_from_ep(hcd, urb);

	kमुक्त(urb->hcpriv);
	urb->hcpriv = शून्य;

	/* Higher layer software sets URB status */
	spin_unlock(&hsotg->lock);
	usb_hcd_giveback_urb(hcd, urb, status);
	spin_lock(&hsotg->lock);

	dev_dbg(hsotg->dev, "Called usb_hcd_giveback_urb()\n");
	dev_dbg(hsotg->dev, "  urb->status = %d\n", urb->status);
out:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस rc;
पूर्ण

/*
 * Frees resources in the DWC_otg controller related to a given endpoपूर्णांक. Also
 * clears state in the HCD related to the endpoपूर्णांक. Any URBs क्रम the endpoपूर्णांक
 * must alपढ़ोy be dequeued.
 */
अटल व्योम _dwc2_hcd_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				       काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	dev_dbg(hsotg->dev,
		"DWC OTG HCD EP DISABLE: bEndpointAddress=0x%02x, ep->hcpriv=%p\n",
		ep->desc.bEndpoपूर्णांकAddress, ep->hcpriv);
	dwc2_hcd_endpoपूर्णांक_disable(hsotg, ep, 250);
पूर्ण

/*
 * Resets endpoपूर्णांक specअगरic parameter values, in current version used to reset
 * the data toggle (as a WA). This function can be called from usb_clear_halt
 * routine.
 */
अटल व्योम _dwc2_hcd_endpoपूर्णांक_reset(काष्ठा usb_hcd *hcd,
				     काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	अचिन्हित दीर्घ flags;

	dev_dbg(hsotg->dev,
		"DWC OTG HCD EP RESET: bEndpointAddress=0x%02x\n",
		ep->desc.bEndpoपूर्णांकAddress);

	spin_lock_irqsave(&hsotg->lock, flags);
	dwc2_hcd_endpoपूर्णांक_reset(hsotg, ep);
	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

/*
 * Handles host mode पूर्णांकerrupts क्रम the DWC_otg controller. Returns IRQ_NONE अगर
 * there was no पूर्णांकerrupt to handle. Returns IRQ_HANDLED अगर there was a valid
 * पूर्णांकerrupt.
 *
 * This function is called by the USB core when an पूर्णांकerrupt occurs
 */
अटल irqवापस_t _dwc2_hcd_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	वापस dwc2_handle_hcd_पूर्णांकr(hsotg);
पूर्ण

/*
 * Creates Status Change biपंचांगap क्रम the root hub and root port. The biपंचांगap is
 * वापसed in buf. Bit 0 is the status change indicator क्रम the root hub. Bit 1
 * is the status change indicator क्रम the single root port. Returns 1 अगर either
 * change indicator is 1, otherwise वापसs 0.
 */
अटल पूर्णांक _dwc2_hcd_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	buf[0] = dwc2_hcd_is_status_changed(hsotg, 1) << 1;
	वापस buf[0] != 0;
पूर्ण

/* Handles hub class-specअगरic requests */
अटल पूर्णांक _dwc2_hcd_hub_control(काष्ठा usb_hcd *hcd, u16 typereq, u16 wvalue,
				 u16 windex, अक्षर *buf, u16 wlength)
अणु
	पूर्णांक retval = dwc2_hcd_hub_control(dwc2_hcd_to_hsotg(hcd), typereq,
					  wvalue, windex, buf, wlength);
	वापस retval;
पूर्ण

/* Handles hub TT buffer clear completions */
अटल व्योम _dwc2_hcd_clear_tt_buffer_complete(काष्ठा usb_hcd *hcd,
					       काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	काष्ठा dwc2_qh *qh;
	अचिन्हित दीर्घ flags;

	qh = ep->hcpriv;
	अगर (!qh)
		वापस;

	spin_lock_irqsave(&hsotg->lock, flags);
	qh->tt_buffer_dirty = 0;

	अगर (hsotg->flags.b.port_connect_status)
		dwc2_hcd_queue_transactions(hsotg, DWC2_TRANSACTION_ALL);

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

/*
 * HPRT0_SPD_HIGH_SPEED: high speed
 * HPRT0_SPD_FULL_SPEED: full speed
 */
अटल व्योम dwc2_change_bus_speed(काष्ठा usb_hcd *hcd, पूर्णांक speed)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	अगर (hsotg->params.speed == speed)
		वापस;

	hsotg->params.speed = speed;
	queue_work(hsotg->wq_otg, &hsotg->wf_otg);
पूर्ण

अटल व्योम dwc2_मुक्त_dev(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	अगर (!hsotg->params.change_speed_quirk)
		वापस;

	/*
	 * On removal, set speed to शेष high-speed.
	 */
	अगर (udev->parent && udev->parent->speed > USB_SPEED_UNKNOWN &&
	    udev->parent->speed < USB_SPEED_HIGH) अणु
		dev_info(hsotg->dev, "Set speed to default high-speed\n");
		dwc2_change_bus_speed(hcd, HPRT0_SPD_HIGH_SPEED);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc2_reset_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	अगर (!hsotg->params.change_speed_quirk)
		वापस 0;

	अगर (udev->speed == USB_SPEED_HIGH) अणु
		dev_info(hsotg->dev, "Set speed to high-speed\n");
		dwc2_change_bus_speed(hcd, HPRT0_SPD_HIGH_SPEED);
	पूर्ण अन्यथा अगर ((udev->speed == USB_SPEED_FULL ||
				udev->speed == USB_SPEED_LOW)) अणु
		/*
		 * Change speed setting to full-speed अगर there's
		 * a full-speed or low-speed device plugged in.
		 */
		dev_info(hsotg->dev, "Set speed to full-speed\n");
		dwc2_change_bus_speed(hcd, HPRT0_SPD_FULL_SPEED);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hc_driver dwc2_hc_driver = अणु
	.description = "dwc2_hsotg",
	.product_desc = "DWC OTG Controller",
	.hcd_priv_size = माप(काष्ठा wrapper_priv_data),

	.irq = _dwc2_hcd_irq,
	.flags = HCD_MEMORY | HCD_USB2 | HCD_BH,

	.start = _dwc2_hcd_start,
	.stop = _dwc2_hcd_stop,
	.urb_enqueue = _dwc2_hcd_urb_enqueue,
	.urb_dequeue = _dwc2_hcd_urb_dequeue,
	.endpoपूर्णांक_disable = _dwc2_hcd_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset = _dwc2_hcd_endpoपूर्णांक_reset,
	.get_frame_number = _dwc2_hcd_get_frame_number,

	.hub_status_data = _dwc2_hcd_hub_status_data,
	.hub_control = _dwc2_hcd_hub_control,
	.clear_tt_buffer_complete = _dwc2_hcd_clear_tt_buffer_complete,

	.bus_suspend = _dwc2_hcd_suspend,
	.bus_resume = _dwc2_hcd_resume,

	.map_urb_क्रम_dma	= dwc2_map_urb_क्रम_dma,
	.unmap_urb_क्रम_dma	= dwc2_unmap_urb_क्रम_dma,
पूर्ण;

/*
 * Frees secondary storage associated with the dwc2_hsotg काष्ठाure contained
 * in the काष्ठा usb_hcd field
 */
अटल व्योम dwc2_hcd_मुक्त(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 ahbcfg;
	u32 dctl;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "DWC OTG HCD FREE\n");

	/* Free memory क्रम QH/QTD lists */
	dwc2_qh_list_मुक्त(hsotg, &hsotg->non_periodic_sched_inactive);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->non_periodic_sched_रुकोing);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->non_periodic_sched_active);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->periodic_sched_inactive);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->periodic_sched_पढ़ोy);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->periodic_sched_asचिन्हित);
	dwc2_qh_list_मुक्त(hsotg, &hsotg->periodic_sched_queued);

	/* Free memory क्रम the host channels */
	क्रम (i = 0; i < MAX_EPS_CHANNELS; i++) अणु
		काष्ठा dwc2_host_chan *chan = hsotg->hc_ptr_array[i];

		अगर (chan) अणु
			dev_dbg(hsotg->dev, "HCD Free channel #%i, chan=%p\n",
				i, chan);
			hsotg->hc_ptr_array[i] = शून्य;
			kमुक्त(chan);
		पूर्ण
	पूर्ण

	अगर (hsotg->params.host_dma) अणु
		अगर (hsotg->status_buf) अणु
			dma_मुक्त_coherent(hsotg->dev, DWC2_HCD_STATUS_BUF_SIZE,
					  hsotg->status_buf,
					  hsotg->status_buf_dma);
			hsotg->status_buf = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(hsotg->status_buf);
		hsotg->status_buf = शून्य;
	पूर्ण

	ahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);

	/* Disable all पूर्णांकerrupts */
	ahbcfg &= ~GAHBCFG_GLBL_INTR_EN;
	dwc2_ग_लिखोl(hsotg, ahbcfg, GAHBCFG);
	dwc2_ग_लिखोl(hsotg, 0, GINTMSK);

	अगर (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a) अणु
		dctl = dwc2_पढ़ोl(hsotg, DCTL);
		dctl |= DCTL_SFTDISCON;
		dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	पूर्ण

	अगर (hsotg->wq_otg) अणु
		अगर (!cancel_work_sync(&hsotg->wf_otg))
			flush_workqueue(hsotg->wq_otg);
		destroy_workqueue(hsotg->wq_otg);
	पूर्ण

	cancel_work_sync(&hsotg->phy_reset_work);

	del_समयr(&hsotg->wkp_समयr);
पूर्ण

अटल व्योम dwc2_hcd_release(काष्ठा dwc2_hsotg *hsotg)
अणु
	/* Turn off all host-specअगरic पूर्णांकerrupts */
	dwc2_disable_host_पूर्णांकerrupts(hsotg);

	dwc2_hcd_मुक्त(hsotg);
पूर्ण

/*
 * Initializes the HCD. This function allocates memory क्रम and initializes the
 * अटल parts of the usb_hcd and dwc2_hsotg काष्ठाures. It also रेजिस्टरs the
 * USB bus with the core and calls the hc_driver->start() function. It वापसs
 * a negative error on failure.
 */
पूर्णांक dwc2_hcd_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(hsotg->dev);
	काष्ठा resource *res;
	काष्ठा usb_hcd *hcd;
	काष्ठा dwc2_host_chan *channel;
	u32 hcfg;
	पूर्णांक i, num_channels;
	पूर्णांक retval;

	अगर (usb_disabled())
		वापस -ENODEV;

	dev_dbg(hsotg->dev, "DWC OTG HCD INIT\n");

	retval = -ENOMEM;

	hcfg = dwc2_पढ़ोl(hsotg, HCFG);
	dev_dbg(hsotg->dev, "hcfg=%08x\n", hcfg);

#अगर_घोषित CONFIG_USB_DWC2_TRACK_MISSED_SOFS
	hsotg->frame_num_array = kसुस्मृति(FRAME_NUM_ARRAY_SIZE,
					 माप(*hsotg->frame_num_array),
					 GFP_KERNEL);
	अगर (!hsotg->frame_num_array)
		जाओ error1;
	hsotg->last_frame_num_array =
		kसुस्मृति(FRAME_NUM_ARRAY_SIZE,
			माप(*hsotg->last_frame_num_array), GFP_KERNEL);
	अगर (!hsotg->last_frame_num_array)
		जाओ error1;
#पूर्ण_अगर
	hsotg->last_frame_num = HFNUM_MAX_FRNUM;

	/* Check अगर the bus driver or platक्रमm code has setup a dma_mask */
	अगर (hsotg->params.host_dma &&
	    !hsotg->dev->dma_mask) अणु
		dev_warn(hsotg->dev,
			 "dma_mask not set, disabling DMA\n");
		hsotg->params.host_dma = false;
		hsotg->params.dma_desc_enable = false;
	पूर्ण

	/* Set device flags indicating whether the HCD supports DMA */
	अगर (hsotg->params.host_dma) अणु
		अगर (dma_set_mask(hsotg->dev, DMA_BIT_MASK(32)) < 0)
			dev_warn(hsotg->dev, "can't set DMA mask\n");
		अगर (dma_set_coherent_mask(hsotg->dev, DMA_BIT_MASK(32)) < 0)
			dev_warn(hsotg->dev, "can't set coherent DMA mask\n");
	पूर्ण

	अगर (hsotg->params.change_speed_quirk) अणु
		dwc2_hc_driver.मुक्त_dev = dwc2_मुक्त_dev;
		dwc2_hc_driver.reset_device = dwc2_reset_device;
	पूर्ण

	अगर (hsotg->params.host_dma)
		dwc2_hc_driver.flags |= HCD_DMA;

	hcd = usb_create_hcd(&dwc2_hc_driver, hsotg->dev, dev_name(hsotg->dev));
	अगर (!hcd)
		जाओ error1;

	hcd->has_tt = 1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	((काष्ठा wrapper_priv_data *)&hcd->hcd_priv)->hsotg = hsotg;
	hsotg->priv = hcd;

	/*
	 * Disable the global पूर्णांकerrupt until all the पूर्णांकerrupt handlers are
	 * installed
	 */
	dwc2_disable_global_पूर्णांकerrupts(hsotg);

	/* Initialize the DWC_otg core, and select the Phy type */
	retval = dwc2_core_init(hsotg, true);
	अगर (retval)
		जाओ error2;

	/* Create new workqueue and init work */
	retval = -ENOMEM;
	hsotg->wq_otg = alloc_ordered_workqueue("dwc2", 0);
	अगर (!hsotg->wq_otg) अणु
		dev_err(hsotg->dev, "Failed to create workqueue\n");
		जाओ error2;
	पूर्ण
	INIT_WORK(&hsotg->wf_otg, dwc2_conn_id_status_change);

	समयr_setup(&hsotg->wkp_समयr, dwc2_wakeup_detected, 0);

	/* Initialize the non-periodic schedule */
	INIT_LIST_HEAD(&hsotg->non_periodic_sched_inactive);
	INIT_LIST_HEAD(&hsotg->non_periodic_sched_रुकोing);
	INIT_LIST_HEAD(&hsotg->non_periodic_sched_active);

	/* Initialize the periodic schedule */
	INIT_LIST_HEAD(&hsotg->periodic_sched_inactive);
	INIT_LIST_HEAD(&hsotg->periodic_sched_पढ़ोy);
	INIT_LIST_HEAD(&hsotg->periodic_sched_asचिन्हित);
	INIT_LIST_HEAD(&hsotg->periodic_sched_queued);

	INIT_LIST_HEAD(&hsotg->split_order);

	/*
	 * Create a host channel descriptor क्रम each host channel implemented
	 * in the controller. Initialize the channel descriptor array.
	 */
	INIT_LIST_HEAD(&hsotg->मुक्त_hc_list);
	num_channels = hsotg->params.host_channels;
	स_रखो(&hsotg->hc_ptr_array[0], 0, माप(hsotg->hc_ptr_array));

	क्रम (i = 0; i < num_channels; i++) अणु
		channel = kzalloc(माप(*channel), GFP_KERNEL);
		अगर (!channel)
			जाओ error3;
		channel->hc_num = i;
		INIT_LIST_HEAD(&channel->split_order_list_entry);
		hsotg->hc_ptr_array[i] = channel;
	पूर्ण

	/* Initialize work */
	INIT_DELAYED_WORK(&hsotg->start_work, dwc2_hcd_start_func);
	INIT_DELAYED_WORK(&hsotg->reset_work, dwc2_hcd_reset_func);
	INIT_WORK(&hsotg->phy_reset_work, dwc2_hcd_phy_reset_func);

	/*
	 * Allocate space क्रम storing data on status transactions. Normally no
	 * data is sent, but this space acts as a bit bucket. This must be
	 * करोne after usb_add_hcd since that function allocates the DMA buffer
	 * pool.
	 */
	अगर (hsotg->params.host_dma)
		hsotg->status_buf = dma_alloc_coherent(hsotg->dev,
					DWC2_HCD_STATUS_BUF_SIZE,
					&hsotg->status_buf_dma, GFP_KERNEL);
	अन्यथा
		hsotg->status_buf = kzalloc(DWC2_HCD_STATUS_BUF_SIZE,
					  GFP_KERNEL);

	अगर (!hsotg->status_buf)
		जाओ error3;

	/*
	 * Create kmem caches to handle descriptor buffers in descriptor
	 * DMA mode.
	 * Alignment must be set to 512 bytes.
	 */
	अगर (hsotg->params.dma_desc_enable ||
	    hsotg->params.dma_desc_fs_enable) अणु
		hsotg->desc_gen_cache = kmem_cache_create("dwc2-gen-desc",
				माप(काष्ठा dwc2_dma_desc) *
				MAX_DMA_DESC_NUM_GENERIC, 512, SLAB_CACHE_DMA,
				शून्य);
		अगर (!hsotg->desc_gen_cache) अणु
			dev_err(hsotg->dev,
				"unable to create dwc2 generic desc cache\n");

			/*
			 * Disable descriptor dma mode since it will not be
			 * usable.
			 */
			hsotg->params.dma_desc_enable = false;
			hsotg->params.dma_desc_fs_enable = false;
		पूर्ण

		hsotg->desc_hsisoc_cache = kmem_cache_create("dwc2-hsisoc-desc",
				माप(काष्ठा dwc2_dma_desc) *
				MAX_DMA_DESC_NUM_HS_ISOC, 512, 0, शून्य);
		अगर (!hsotg->desc_hsisoc_cache) अणु
			dev_err(hsotg->dev,
				"unable to create dwc2 hs isoc desc cache\n");

			kmem_cache_destroy(hsotg->desc_gen_cache);

			/*
			 * Disable descriptor dma mode since it will not be
			 * usable.
			 */
			hsotg->params.dma_desc_enable = false;
			hsotg->params.dma_desc_fs_enable = false;
		पूर्ण
	पूर्ण

	अगर (hsotg->params.host_dma) अणु
		/*
		 * Create kmem caches to handle non-aligned buffer
		 * in Buffer DMA mode.
		 */
		hsotg->unaligned_cache = kmem_cache_create("dwc2-unaligned-dma",
						DWC2_KMEM_UNALIGNED_BUF_SIZE, 4,
						SLAB_CACHE_DMA, शून्य);
		अगर (!hsotg->unaligned_cache)
			dev_err(hsotg->dev,
				"unable to create dwc2 unaligned cache\n");
	पूर्ण

	hsotg->otg_port = 1;
	hsotg->frame_list = शून्य;
	hsotg->frame_list_dma = 0;
	hsotg->periodic_qh_count = 0;

	/* Initiate lx_state to L3 disconnected state */
	hsotg->lx_state = DWC2_L3;

	hcd->self.otg_port = hsotg->otg_port;

	/* Don't support SG list at this poपूर्णांक */
	hcd->self.sg_tablesize = 0;

	अगर (!IS_ERR_OR_शून्य(hsotg->uphy))
		otg_set_host(hsotg->uphy->otg, &hcd->self);

	/*
	 * Finish generic HCD initialization and start the HCD. This function
	 * allocates the DMA buffer pool, रेजिस्टरs the USB bus, requests the
	 * IRQ line, and calls hcd_start method.
	 */
	retval = usb_add_hcd(hcd, hsotg->irq, IRQF_SHARED);
	अगर (retval < 0)
		जाओ error4;

	device_wakeup_enable(hcd->self.controller);

	dwc2_hcd_dump_state(hsotg);

	dwc2_enable_global_पूर्णांकerrupts(hsotg);

	वापस 0;

error4:
	kmem_cache_destroy(hsotg->unaligned_cache);
	kmem_cache_destroy(hsotg->desc_hsisoc_cache);
	kmem_cache_destroy(hsotg->desc_gen_cache);
error3:
	dwc2_hcd_release(hsotg);
error2:
	usb_put_hcd(hcd);
error1:

#अगर_घोषित CONFIG_USB_DWC2_TRACK_MISSED_SOFS
	kमुक्त(hsotg->last_frame_num_array);
	kमुक्त(hsotg->frame_num_array);
#पूर्ण_अगर

	dev_err(hsotg->dev, "%s() FAILED, returning %d\n", __func__, retval);
	वापस retval;
पूर्ण

/*
 * Removes the HCD.
 * Frees memory and resources associated with the HCD and deरेजिस्टरs the bus.
 */
व्योम dwc2_hcd_हटाओ(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_hcd *hcd;

	dev_dbg(hsotg->dev, "DWC OTG HCD REMOVE\n");

	hcd = dwc2_hsotg_to_hcd(hsotg);
	dev_dbg(hsotg->dev, "hsotg->hcd = %p\n", hcd);

	अगर (!hcd) अणु
		dev_dbg(hsotg->dev, "%s: dwc2_hsotg_to_hcd(hsotg) NULL!\n",
			__func__);
		वापस;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(hsotg->uphy))
		otg_set_host(hsotg->uphy->otg, शून्य);

	usb_हटाओ_hcd(hcd);
	hsotg->priv = शून्य;

	kmem_cache_destroy(hsotg->unaligned_cache);
	kmem_cache_destroy(hsotg->desc_hsisoc_cache);
	kmem_cache_destroy(hsotg->desc_gen_cache);

	dwc2_hcd_release(hsotg);
	usb_put_hcd(hcd);

#अगर_घोषित CONFIG_USB_DWC2_TRACK_MISSED_SOFS
	kमुक्त(hsotg->last_frame_num_array);
	kमुक्त(hsotg->frame_num_array);
#पूर्ण_अगर
पूर्ण

/**
 * dwc2_backup_host_रेजिस्टरs() - Backup controller host रेजिस्टरs.
 * When suspending usb bus, रेजिस्टरs needs to be backuped
 * अगर controller घातer is disabled once suspended.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_backup_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hregs_backup *hr;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Backup Host regs */
	hr = &hsotg->hr_backup;
	hr->hcfg = dwc2_पढ़ोl(hsotg, HCFG);
	hr->haपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HAINTMSK);
	क्रम (i = 0; i < hsotg->params.host_channels; ++i)
		hr->hcपूर्णांकmsk[i] = dwc2_पढ़ोl(hsotg, HCINTMSK(i));

	hr->hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hr->hfir = dwc2_पढ़ोl(hsotg, HFIR);
	hr->hptxfsiz = dwc2_पढ़ोl(hsotg, HPTXFSIZ);
	hr->valid = true;

	वापस 0;
पूर्ण

/**
 * dwc2_restore_host_रेजिस्टरs() - Restore controller host रेजिस्टरs.
 * When resuming usb bus, device रेजिस्टरs needs to be restored
 * अगर controller घातer were disabled.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_restore_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hregs_backup *hr;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Restore host regs */
	hr = &hsotg->hr_backup;
	अगर (!hr->valid) अणु
		dev_err(hsotg->dev, "%s: no host registers to restore\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	hr->valid = false;

	dwc2_ग_लिखोl(hsotg, hr->hcfg, HCFG);
	dwc2_ग_लिखोl(hsotg, hr->haपूर्णांकmsk, HAINTMSK);

	क्रम (i = 0; i < hsotg->params.host_channels; ++i)
		dwc2_ग_लिखोl(hsotg, hr->hcपूर्णांकmsk[i], HCINTMSK(i));

	dwc2_ग_लिखोl(hsotg, hr->hprt0, HPRT0);
	dwc2_ग_लिखोl(hsotg, hr->hfir, HFIR);
	dwc2_ग_लिखोl(hsotg, hr->hptxfsiz, HPTXFSIZ);
	hsotg->frame_number = 0;

	वापस 0;
पूर्ण

/**
 * dwc2_host_enter_hibernation() - Put controller in Hibernation.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_host_enter_hibernation(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 hprt0;
	u32 pcgcctl;
	u32 gusbcfg;
	u32 gpwrdn;

	dev_dbg(hsotg->dev, "Preparing host for hibernation\n");
	ret = dwc2_backup_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup global registers\n",
			__func__);
		वापस ret;
	पूर्ण
	ret = dwc2_backup_host_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup host registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Enter USB Suspend Mode */
	hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
	hprt0 |= HPRT0_SUSP;
	hprt0 &= ~HPRT0_ENA;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

	/* Wait क्रम the HPRT0.PrtSusp रेजिस्टर field to be set */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, HPRT0, HPRT0_SUSP, 5000))
		dev_warn(hsotg->dev, "Suspend wasn't generated\n");

	/*
	 * We need to disable पूर्णांकerrupts to prevent servicing of any IRQ
	 * during going to hibernation
	 */
	spin_lock_irqsave(&hsotg->lock, flags);
	hsotg->lx_state = DWC2_L2;

	gusbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	अगर (gusbcfg & GUSBCFG_ULPI_UTMI_SEL) अणु
		/* ULPI पूर्णांकerface */
		/* Suspend the Phy Clock */
		pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
		pcgcctl |= PCGCTL_STOPPCLK;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);

		gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
		gpwrdn |= GPWRDN_PMUACTV;
		dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
		udelay(10);
	पूर्ण अन्यथा अणु
		/* UTMI+ Interface */
		gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
		gpwrdn |= GPWRDN_PMUACTV;
		dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
		udelay(10);

		pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
		pcgcctl |= PCGCTL_STOPPCLK;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);
	पूर्ण

	/* Enable पूर्णांकerrupts from wake up logic */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PMUINTSEL;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Unmask host mode पूर्णांकerrupts in GPWRDN */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_DISCONN_DET_MSK;
	gpwrdn |= GPWRDN_LNSTSCHG_MSK;
	gpwrdn |= GPWRDN_STS_CHGINT_MSK;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Enable Power Down Clamp */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PWRDNCLMP;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Switch off VDD */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PWRDNSWTCH;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);

	hsotg->hibernated = 1;
	hsotg->bus_suspended = 1;
	dev_dbg(hsotg->dev, "Host hibernation completed\n");
	spin_unlock_irqrestore(&hsotg->lock, flags);
	वापस ret;
पूर्ण

/*
 * dwc2_host_निकास_hibernation()
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether resume is initiated by Device or Host.
 * @param reset: indicates whether resume is initiated by Reset.
 *
 * Return: non-zero अगर failed to enter to hibernation.
 *
 * This function is क्रम निकासing from Host mode hibernation by
 * Host Initiated Resume/Reset and Device Initiated Remote-Wakeup.
 */
पूर्णांक dwc2_host_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
			       पूर्णांक reset)
अणु
	u32 gpwrdn;
	u32 hprt0;
	पूर्णांक ret = 0;
	काष्ठा dwc2_gregs_backup *gr;
	काष्ठा dwc2_hregs_backup *hr;

	gr = &hsotg->gr_backup;
	hr = &hsotg->hr_backup;

	dev_dbg(hsotg->dev,
		"%s: called with rem_wakeup = %d reset = %d\n",
		__func__, rem_wakeup, reset);

	dwc2_hib_restore_common(hsotg, rem_wakeup, 1);
	hsotg->hibernated = 0;

	/*
	 * This step is not described in functional spec but अगर not रुको क्रम
	 * this delay, mismatch पूर्णांकerrupts occurred because just after restore
	 * core is in Device mode(gपूर्णांकsts.curmode == 0)
	 */
	mdelay(100);

	/* Clear all pending पूर्णांकerupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* De-निश्चित Restore */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_RESTORE;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Restore GUSBCFG, HCFG */
	dwc2_ग_लिखोl(hsotg, gr->gusbcfg, GUSBCFG);
	dwc2_ग_लिखोl(hsotg, hr->hcfg, HCFG);

	/* De-निश्चित Wakeup Logic */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PMUACTV;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	hprt0 = hr->hprt0;
	hprt0 |= HPRT0_PWR;
	hprt0 &= ~HPRT0_ENA;
	hprt0 &= ~HPRT0_SUSP;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

	hprt0 = hr->hprt0;
	hprt0 |= HPRT0_PWR;
	hprt0 &= ~HPRT0_ENA;
	hprt0 &= ~HPRT0_SUSP;

	अगर (reset) अणु
		hprt0 |= HPRT0_RST;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

		/* Wait क्रम Resume समय and then program HPRT again */
		mdelay(60);
		hprt0 &= ~HPRT0_RST;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	पूर्ण अन्यथा अणु
		hprt0 |= HPRT0_RES;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

		/* Wait क्रम Resume समय and then program HPRT again */
		mdelay(100);
		hprt0 &= ~HPRT0_RES;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	पूर्ण
	/* Clear all पूर्णांकerrupt status */
	hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
	hprt0 |= HPRT0_CONNDET;
	hprt0 |= HPRT0_ENACHG;
	hprt0 &= ~HPRT0_ENA;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

	hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);

	/* Clear all pending पूर्णांकerupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Restore global रेजिस्टरs */
	ret = dwc2_restore_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to restore registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Restore host रेजिस्टरs */
	ret = dwc2_restore_host_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to restore host registers\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर (rem_wakeup) अणु
		dwc2_hcd_rem_wakeup(hsotg);
		/*
		 * Change "port_connect_status_change" flag to re-क्रमागतerate,
		 * because after निकास from hibernation port connection status
		 * is not detected.
		 */
		hsotg->flags.b.port_connect_status_change = 1;
	पूर्ण

	hsotg->hibernated = 0;
	hsotg->bus_suspended = 0;
	hsotg->lx_state = DWC2_L0;
	dev_dbg(hsotg->dev, "Host hibernation restore complete\n");
	वापस ret;
पूर्ण

bool dwc2_host_can_घातeroff_phy(काष्ठा dwc2_hsotg *dwc2)
अणु
	काष्ठा usb_device *root_hub = dwc2_hsotg_to_hcd(dwc2)->self.root_hub;

	/* If the controller isn't allowed to wakeup then we can घातer off. */
	अगर (!device_may_wakeup(dwc2->dev))
		वापस true;

	/*
	 * We करोn't want to घातer off the PHY अगर something under the
	 * root hub has wakeup enabled.
	 */
	अगर (usb_wakeup_enabled_descendants(root_hub))
		वापस false;

	/* No reason to keep the PHY घातered, so allow घातeroff */
	वापस true;
पूर्ण

/**
 * dwc2_host_enter_partial_घातer_करोwn() - Put controller in partial
 * घातer करोwn.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Return: non-zero अगर failed to enter host partial घातer करोwn.
 *
 * This function is क्रम entering Host mode partial घातer करोwn.
 */
पूर्णांक dwc2_host_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 pcgcctl;
	u32 hprt0;
	पूर्णांक ret = 0;

	dev_dbg(hsotg->dev, "Entering host partial power down started.\n");

	/* Put this port in suspend mode. */
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hprt0 |= HPRT0_SUSP;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	udelay(5);

	/* Wait क्रम the HPRT0.PrtSusp रेजिस्टर field to be set */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, HPRT0, HPRT0_SUSP, 3000))
		dev_warn(hsotg->dev, "Suspend wasn't generated\n");

	/* Backup all रेजिस्टरs */
	ret = dwc2_backup_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup global registers\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = dwc2_backup_host_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup host registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/*
	 * Clear any pending पूर्णांकerrupts since dwc2 will not be able to
	 * clear them after entering partial_घातer_करोwn.
	 */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Put the controller in low घातer state */
	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);

	pcgcctl |= PCGCTL_PWRCLMP;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl |= PCGCTL_RSTPDWNMODULE;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl |= PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	/* Set in_ppd flag to 1 as here core enters suspend. */
	hsotg->in_ppd = 1;
	hsotg->lx_state = DWC2_L2;
	hsotg->bus_suspended = true;

	dev_dbg(hsotg->dev, "Entering host partial power down completed.\n");

	वापस ret;
पूर्ण

/*
 * dwc2_host_निकास_partial_घातer_करोwn() - Exit controller from host partial
 * घातer करोwn.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether resume is initiated by Reset.
 * @restore: indicates whether need to restore the रेजिस्टरs or not.
 *
 * Return: non-zero अगर failed to निकास host partial घातer करोwn.
 *
 * This function is क्रम निकासing from Host mode partial घातer करोwn.
 */
पूर्णांक dwc2_host_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
				      पूर्णांक rem_wakeup, bool restore)
अणु
	u32 pcgcctl;
	पूर्णांक ret = 0;
	u32 hprt0;

	dev_dbg(hsotg->dev, "Exiting host partial power down started.\n");

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_PWRCLMP;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_RSTPDWNMODULE;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	udelay(100);
	अगर (restore) अणु
		ret = dwc2_restore_global_रेजिस्टरs(hsotg);
		अगर (ret) अणु
			dev_err(hsotg->dev, "%s: failed to restore registers\n",
				__func__);
			वापस ret;
		पूर्ण

		ret = dwc2_restore_host_रेजिस्टरs(hsotg);
		अगर (ret) अणु
			dev_err(hsotg->dev, "%s: failed to restore host registers\n",
				__func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Drive resume संकेतing and निकास suspend mode on the port. */
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hprt0 |= HPRT0_RES;
	hprt0 &= ~HPRT0_SUSP;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	udelay(5);

	अगर (!rem_wakeup) अणु
		/* Stop driveing resume संकेतing on the port. */
		hprt0 = dwc2_पढ़ो_hprt0(hsotg);
		hprt0 &= ~HPRT0_RES;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

		hsotg->bus_suspended = false;
	पूर्ण अन्यथा अणु
		/* Turn on the port घातer bit. */
		hprt0 = dwc2_पढ़ो_hprt0(hsotg);
		hprt0 |= HPRT0_PWR;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

		/* Connect hcd. */
		dwc2_hcd_connect(hsotg);

		mod_समयr(&hsotg->wkp_समयr,
			  jअगरfies + msecs_to_jअगरfies(71));
	पूर्ण

	/* Set lx_state to and in_ppd to 0 as here core निकासs from suspend. */
	hsotg->in_ppd = 0;
	hsotg->lx_state = DWC2_L0;

	dev_dbg(hsotg->dev, "Exiting host partial power down completed.\n");
	वापस ret;
पूर्ण

/**
 * dwc2_host_enter_घड़ी_gating() - Put controller in घड़ी gating.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * This function is क्रम entering Host mode घड़ी gating.
 */
व्योम dwc2_host_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hprt0;
	u32 pcgctl;

	dev_dbg(hsotg->dev, "Entering host clock gating.\n");

	/* Put this port in suspend mode. */
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hprt0 |= HPRT0_SUSP;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

	/* Set the Phy Clock bit as suspend is received. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl |= PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	/* Set the Gate hclk as suspend is received. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl |= PCGCTL_GATEHCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	hsotg->bus_suspended = true;
	hsotg->lx_state = DWC2_L2;
पूर्ण

/**
 * dwc2_host_निकास_घड़ी_gating() - Exit controller from घड़ी gating.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether resume is initiated by remote wakeup
 *
 * This function is क्रम निकासing Host mode घड़ी gating.
 */
व्योम dwc2_host_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup)
अणु
	u32 hprt0;
	u32 pcgctl;

	dev_dbg(hsotg->dev, "Exiting host clock gating.\n");

	/* Clear the Gate hclk. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl &= ~PCGCTL_GATEHCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	/* Phy Clock bit. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl &= ~PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	/* Drive resume संकेतing and निकास suspend mode on the port. */
	hprt0 = dwc2_पढ़ो_hprt0(hsotg);
	hprt0 |= HPRT0_RES;
	hprt0 &= ~HPRT0_SUSP;
	dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	udelay(5);

	अगर (!rem_wakeup) अणु
		/* In हाल of port resume need to रुको क्रम 40 ms */
		msleep(USB_RESUME_TIMEOUT);

		/* Stop driveing resume संकेतing on the port. */
		hprt0 = dwc2_पढ़ो_hprt0(hsotg);
		hprt0 &= ~HPRT0_RES;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);

		hsotg->bus_suspended = false;
		hsotg->lx_state = DWC2_L0;
	पूर्ण अन्यथा अणु
		mod_समयr(&hsotg->wkp_समयr,
			  jअगरfies + msecs_to_jअगरfies(71));
	पूर्ण
पूर्ण
