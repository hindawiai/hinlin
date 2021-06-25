<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * hcd_पूर्णांकr.c - DesignWare HS OTG Controller host-mode पूर्णांकerrupt handling
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
 * This file contains the पूर्णांकerrupt handlers क्रम Host mode
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>

#समावेश "core.h"
#समावेश "hcd.h"

/*
 * If we get this many NAKs on a split transaction we'll slow करोwn
 * retransmission.  A 1 here means delay after the first NAK.
 */
#घोषणा DWC2_NAKS_BEFORE_DELAY		3

/* This function is क्रम debug only */
अटल व्योम dwc2_track_missed_sofs(काष्ठा dwc2_hsotg *hsotg)
अणु
	u16 curr_frame_number = hsotg->frame_number;
	u16 expected = dwc2_frame_num_inc(hsotg->last_frame_num, 1);

	अगर (expected != curr_frame_number)
		dwc2_sch_vdbg(hsotg, "MISSED SOF %04x != %04x\n",
			      expected, curr_frame_number);

#अगर_घोषित CONFIG_USB_DWC2_TRACK_MISSED_SOFS
	अगर (hsotg->frame_num_idx < FRAME_NUM_ARRAY_SIZE) अणु
		अगर (expected != curr_frame_number) अणु
			hsotg->frame_num_array[hsotg->frame_num_idx] =
					curr_frame_number;
			hsotg->last_frame_num_array[hsotg->frame_num_idx] =
					hsotg->last_frame_num;
			hsotg->frame_num_idx++;
		पूर्ण
	पूर्ण अन्यथा अगर (!hsotg->dumped_frame_num_array) अणु
		पूर्णांक i;

		dev_info(hsotg->dev, "Frame     Last Frame\n");
		dev_info(hsotg->dev, "-----     ----------\n");
		क्रम (i = 0; i < FRAME_NUM_ARRAY_SIZE; i++) अणु
			dev_info(hsotg->dev, "0x%04x    0x%04x\n",
				 hsotg->frame_num_array[i],
				 hsotg->last_frame_num_array[i]);
		पूर्ण
		hsotg->dumped_frame_num_array = 1;
	पूर्ण
#पूर्ण_अगर
	hsotg->last_frame_num = curr_frame_number;
पूर्ण

अटल व्योम dwc2_hc_handle_tt_clear(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_host_chan *chan,
				    काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा usb_device *root_hub = dwc2_hsotg_to_hcd(hsotg)->self.root_hub;
	काष्ठा urb *usb_urb;

	अगर (!chan->qh)
		वापस;

	अगर (chan->qh->dev_speed == USB_SPEED_HIGH)
		वापस;

	अगर (!qtd->urb)
		वापस;

	usb_urb = qtd->urb->priv;
	अगर (!usb_urb || !usb_urb->dev || !usb_urb->dev->tt)
		वापस;

	/*
	 * The root hub करोesn't really have a TT, but Linux thinks it
	 * करोes because how could you have a "high speed hub" that
	 * directly talks directly to low speed devices without a TT?
	 * It's all lies.  Lies, I tell you.
	 */
	अगर (usb_urb->dev->tt->hub == root_hub)
		वापस;

	अगर (qtd->urb->status != -EPIPE && qtd->urb->status != -EREMOTEIO) अणु
		chan->qh->tt_buffer_dirty = 1;
		अगर (usb_hub_clear_tt_buffer(usb_urb))
			/* Clear failed; let's hope things work anyway */
			chan->qh->tt_buffer_dirty = 0;
	पूर्ण
पूर्ण

/*
 * Handles the start-of-frame पूर्णांकerrupt in host mode. Non-periodic
 * transactions may be queued to the DWC_otg controller क्रम the current
 * (micro)frame. Periodic transactions may be queued to the controller
 * क्रम the next (micro)frame.
 */
अटल व्योम dwc2_sof_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा list_head *qh_entry;
	काष्ठा dwc2_qh *qh;
	क्रमागत dwc2_transaction_type tr_type;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_SOF, GINTSTS);

#अगर_घोषित DEBUG_SOF
	dev_vdbg(hsotg->dev, "--Start of Frame Interrupt--\n");
#पूर्ण_अगर

	hsotg->frame_number = dwc2_hcd_get_frame_number(hsotg);

	dwc2_track_missed_sofs(hsotg);

	/* Determine whether any periodic QHs should be executed */
	qh_entry = hsotg->periodic_sched_inactive.next;
	जबतक (qh_entry != &hsotg->periodic_sched_inactive) अणु
		qh = list_entry(qh_entry, काष्ठा dwc2_qh, qh_list_entry);
		qh_entry = qh_entry->next;
		अगर (dwc2_frame_num_le(qh->next_active_frame,
				      hsotg->frame_number)) अणु
			dwc2_sch_vdbg(hsotg, "QH=%p ready fn=%04x, nxt=%04x\n",
				      qh, hsotg->frame_number,
				      qh->next_active_frame);

			/*
			 * Move QH to the पढ़ोy list to be executed next
			 * (micro)frame
			 */
			list_move_tail(&qh->qh_list_entry,
				       &hsotg->periodic_sched_पढ़ोy);
		पूर्ण
	पूर्ण
	tr_type = dwc2_hcd_select_transactions(hsotg);
	अगर (tr_type != DWC2_TRANSACTION_NONE)
		dwc2_hcd_queue_transactions(hsotg, tr_type);
पूर्ण

/*
 * Handles the Rx FIFO Level Interrupt, which indicates that there is
 * at least one packet in the Rx FIFO. The packets are moved from the FIFO to
 * memory अगर the DWC_otg controller is operating in Slave mode.
 */
अटल व्योम dwc2_rx_fअगरo_level_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 grxsts, chnum, bcnt, dpid, pktsts;
	काष्ठा dwc2_host_chan *chan;

	अगर (dbg_perio())
		dev_vdbg(hsotg->dev, "--RxFIFO Level Interrupt--\n");

	grxsts = dwc2_पढ़ोl(hsotg, GRXSTSP);
	chnum = (grxsts & GRXSTS_HCHNUM_MASK) >> GRXSTS_HCHNUM_SHIFT;
	chan = hsotg->hc_ptr_array[chnum];
	अगर (!chan) अणु
		dev_err(hsotg->dev, "Unable to get corresponding channel\n");
		वापस;
	पूर्ण

	bcnt = (grxsts & GRXSTS_BYTECNT_MASK) >> GRXSTS_BYTECNT_SHIFT;
	dpid = (grxsts & GRXSTS_DPID_MASK) >> GRXSTS_DPID_SHIFT;
	pktsts = (grxsts & GRXSTS_PKTSTS_MASK) >> GRXSTS_PKTSTS_SHIFT;

	/* Packet Status */
	अगर (dbg_perio()) अणु
		dev_vdbg(hsotg->dev, "    Ch num = %d\n", chnum);
		dev_vdbg(hsotg->dev, "    Count = %d\n", bcnt);
		dev_vdbg(hsotg->dev, "    DPID = %d, chan.dpid = %d\n", dpid,
			 chan->data_pid_start);
		dev_vdbg(hsotg->dev, "    PStatus = %d\n", pktsts);
	पूर्ण

	चयन (pktsts) अणु
	हाल GRXSTS_PKTSTS_HCHIN:
		/* Read the data पूर्णांकo the host buffer */
		अगर (bcnt > 0) अणु
			dwc2_पढ़ो_packet(hsotg, chan->xfer_buf, bcnt);

			/* Update the HC fields क्रम the next packet received */
			chan->xfer_count += bcnt;
			chan->xfer_buf += bcnt;
		पूर्ण
		अवरोध;
	हाल GRXSTS_PKTSTS_HCHIN_XFER_COMP:
	हाल GRXSTS_PKTSTS_DATATOGGLEERR:
	हाल GRXSTS_PKTSTS_HCHHALTED:
		/* Handled in पूर्णांकerrupt, just ignore data */
		अवरोध;
	शेष:
		dev_err(hsotg->dev,
			"RxFIFO Level Interrupt: Unknown status %d\n", pktsts);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This पूर्णांकerrupt occurs when the non-periodic Tx FIFO is half-empty. More
 * data packets may be written to the FIFO क्रम OUT transfers. More requests
 * may be written to the non-periodic request queue क्रम IN transfers. This
 * पूर्णांकerrupt is enabled only in Slave mode.
 */
अटल व्योम dwc2_np_tx_fअगरo_empty_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	dev_vdbg(hsotg->dev, "--Non-Periodic TxFIFO Empty Interrupt--\n");
	dwc2_hcd_queue_transactions(hsotg, DWC2_TRANSACTION_NON_PERIODIC);
पूर्ण

/*
 * This पूर्णांकerrupt occurs when the periodic Tx FIFO is half-empty. More data
 * packets may be written to the FIFO क्रम OUT transfers. More requests may be
 * written to the periodic request queue क्रम IN transfers. This पूर्णांकerrupt is
 * enabled only in Slave mode.
 */
अटल व्योम dwc2_perio_tx_fअगरo_empty_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (dbg_perio())
		dev_vdbg(hsotg->dev, "--Periodic TxFIFO Empty Interrupt--\n");
	dwc2_hcd_queue_transactions(hsotg, DWC2_TRANSACTION_PERIODIC);
पूर्ण

अटल व्योम dwc2_hprt0_enable(काष्ठा dwc2_hsotg *hsotg, u32 hprt0,
			      u32 *hprt0_modअगरy)
अणु
	काष्ठा dwc2_core_params *params = &hsotg->params;
	पूर्णांक करो_reset = 0;
	u32 usbcfg;
	u32 prtspd;
	u32 hcfg;
	u32 fslspclksel;
	u32 hfir;

	dev_vdbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	/* Every समय when port enables calculate HFIR.FrInterval */
	hfir = dwc2_पढ़ोl(hsotg, HFIR);
	hfir &= ~HFIR_FRINT_MASK;
	hfir |= dwc2_calc_frame_पूर्णांकerval(hsotg) << HFIR_FRINT_SHIFT &
		HFIR_FRINT_MASK;
	dwc2_ग_लिखोl(hsotg, hfir, HFIR);

	/* Check अगर we need to adjust the PHY घड़ी speed क्रम low घातer */
	अगर (!params->host_support_fs_ls_low_घातer) अणु
		/* Port has been enabled, set the reset change flag */
		hsotg->flags.b.port_reset_change = 1;
		वापस;
	पूर्ण

	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	prtspd = (hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;

	अगर (prtspd == HPRT0_SPD_LOW_SPEED || prtspd == HPRT0_SPD_FULL_SPEED) अणु
		/* Low घातer */
		अगर (!(usbcfg & GUSBCFG_PHY_LP_CLK_SEL)) अणु
			/* Set PHY low घातer घड़ी select क्रम FS/LS devices */
			usbcfg |= GUSBCFG_PHY_LP_CLK_SEL;
			dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);
			करो_reset = 1;
		पूर्ण

		hcfg = dwc2_पढ़ोl(hsotg, HCFG);
		fslspclksel = (hcfg & HCFG_FSLSPCLKSEL_MASK) >>
			      HCFG_FSLSPCLKSEL_SHIFT;

		अगर (prtspd == HPRT0_SPD_LOW_SPEED &&
		    params->host_ls_low_घातer_phy_clk) अणु
			/* 6 MHZ */
			dev_vdbg(hsotg->dev,
				 "FS_PHY programming HCFG to 6 MHz\n");
			अगर (fslspclksel != HCFG_FSLSPCLKSEL_6_MHZ) अणु
				fslspclksel = HCFG_FSLSPCLKSEL_6_MHZ;
				hcfg &= ~HCFG_FSLSPCLKSEL_MASK;
				hcfg |= fslspclksel << HCFG_FSLSPCLKSEL_SHIFT;
				dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
				करो_reset = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* 48 MHZ */
			dev_vdbg(hsotg->dev,
				 "FS_PHY programming HCFG to 48 MHz\n");
			अगर (fslspclksel != HCFG_FSLSPCLKSEL_48_MHZ) अणु
				fslspclksel = HCFG_FSLSPCLKSEL_48_MHZ;
				hcfg &= ~HCFG_FSLSPCLKSEL_MASK;
				hcfg |= fslspclksel << HCFG_FSLSPCLKSEL_SHIFT;
				dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
				करो_reset = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Not low घातer */
		अगर (usbcfg & GUSBCFG_PHY_LP_CLK_SEL) अणु
			usbcfg &= ~GUSBCFG_PHY_LP_CLK_SEL;
			dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);
			करो_reset = 1;
		पूर्ण
	पूर्ण

	अगर (करो_reset) अणु
		*hprt0_modअगरy |= HPRT0_RST;
		dwc2_ग_लिखोl(hsotg, *hprt0_modअगरy, HPRT0);
		queue_delayed_work(hsotg->wq_otg, &hsotg->reset_work,
				   msecs_to_jअगरfies(60));
	पूर्ण अन्यथा अणु
		/* Port has been enabled, set the reset change flag */
		hsotg->flags.b.port_reset_change = 1;
	पूर्ण
पूर्ण

/*
 * There are multiple conditions that can cause a port पूर्णांकerrupt. This function
 * determines which पूर्णांकerrupt conditions have occurred and handles them
 * appropriately.
 */
अटल व्योम dwc2_port_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hprt0;
	u32 hprt0_modअगरy;

	dev_vdbg(hsotg->dev, "--Port Interrupt--\n");

	hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);
	hprt0_modअगरy = hprt0;

	/*
	 * Clear appropriate bits in HPRT0 to clear the पूर्णांकerrupt bit in
	 * GINTSTS
	 */
	hprt0_modअगरy &= ~(HPRT0_ENA | HPRT0_CONNDET | HPRT0_ENACHG |
			  HPRT0_OVRCURRCHG);

	/*
	 * Port Connect Detected
	 * Set flag and clear अगर detected
	 */
	अगर (hprt0 & HPRT0_CONNDET) अणु
		dwc2_ग_लिखोl(hsotg, hprt0_modअगरy | HPRT0_CONNDET, HPRT0);

		dev_vdbg(hsotg->dev,
			 "--Port Interrupt HPRT0=0x%08x Port Connect Detected--\n",
			 hprt0);
		dwc2_hcd_connect(hsotg);

		/*
		 * The Hub driver निश्चितs a reset when it sees port connect
		 * status change flag
		 */
	पूर्ण

	/*
	 * Port Enable Changed
	 * Clear अगर detected - Set पूर्णांकernal flag अगर disabled
	 */
	अगर (hprt0 & HPRT0_ENACHG) अणु
		dwc2_ग_लिखोl(hsotg, hprt0_modअगरy | HPRT0_ENACHG, HPRT0);
		dev_vdbg(hsotg->dev,
			 "  --Port Interrupt HPRT0=0x%08x Port Enable Changed (now %d)--\n",
			 hprt0, !!(hprt0 & HPRT0_ENA));
		अगर (hprt0 & HPRT0_ENA) अणु
			hsotg->new_connection = true;
			dwc2_hprt0_enable(hsotg, hprt0, &hprt0_modअगरy);
		पूर्ण अन्यथा अणु
			hsotg->flags.b.port_enable_change = 1;
			अगर (hsotg->params.dma_desc_fs_enable) अणु
				u32 hcfg;

				hsotg->params.dma_desc_enable = false;
				hsotg->new_connection = false;
				hcfg = dwc2_पढ़ोl(hsotg, HCFG);
				hcfg &= ~HCFG_DESCDMA;
				dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Overcurrent Change Interrupt */
	अगर (hprt0 & HPRT0_OVRCURRCHG) अणु
		dwc2_ग_लिखोl(hsotg, hprt0_modअगरy | HPRT0_OVRCURRCHG,
			    HPRT0);
		dev_vdbg(hsotg->dev,
			 "  --Port Interrupt HPRT0=0x%08x Port Overcurrent Changed--\n",
			 hprt0);
		hsotg->flags.b.port_over_current_change = 1;
	पूर्ण
पूर्ण

/*
 * Gets the actual length of a transfer after the transfer halts. halt_status
 * holds the reason क्रम the halt.
 *
 * For IN transfers where halt_status is DWC2_HC_XFER_COMPLETE, *लघु_पढ़ो
 * is set to 1 upon वापस अगर less than the requested number of bytes were
 * transferred. लघु_पढ़ो may also be शून्य on entry, in which हाल it reमुख्यs
 * unchanged.
 */
अटल u32 dwc2_get_actual_xfer_length(काष्ठा dwc2_hsotg *hsotg,
				       काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				       काष्ठा dwc2_qtd *qtd,
				       क्रमागत dwc2_halt_status halt_status,
				       पूर्णांक *लघु_पढ़ो)
अणु
	u32 hctsiz, count, length;

	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));

	अगर (halt_status == DWC2_HC_XFER_COMPLETE) अणु
		अगर (chan->ep_is_in) अणु
			count = (hctsiz & TSIZ_XFERSIZE_MASK) >>
				TSIZ_XFERSIZE_SHIFT;
			length = chan->xfer_len - count;
			अगर (लघु_पढ़ो)
				*लघु_पढ़ो = (count != 0);
		पूर्ण अन्यथा अगर (chan->qh->करो_split) अणु
			length = qtd->ssplit_out_xfer_count;
		पूर्ण अन्यथा अणु
			length = chan->xfer_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Must use the hctsiz.pktcnt field to determine how much data
		 * has been transferred. This field reflects the number of
		 * packets that have been transferred via the USB. This is
		 * always an पूर्णांकegral number of packets अगर the transfer was
		 * halted beक्रमe its normal completion. (Can't use the
		 * hctsiz.xfersize field because that reflects the number of
		 * bytes transferred via the AHB, not the USB).
		 */
		count = (hctsiz & TSIZ_PKTCNT_MASK) >> TSIZ_PKTCNT_SHIFT;
		length = (chan->start_pkt_count - count) * chan->max_packet;
	पूर्ण

	वापस length;
पूर्ण

/**
 * dwc2_update_urb_state() - Updates the state of the URB after a Transfer
 * Complete पूर्णांकerrupt on the host channel. Updates the actual_length field
 * of the URB based on the number of bytes transferred via the host channel.
 * Sets the URB status अगर the data transfer is finished.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @chan: Programming view of host channel
 * @chnum: Channel number
 * @urb: Processing URB
 * @qtd: Queue transfer descriptor
 *
 * Return: 1 अगर the data transfer specअगरied by the URB is completely finished,
 * 0 otherwise
 */
अटल पूर्णांक dwc2_update_urb_state(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				 काष्ठा dwc2_hcd_urb *urb,
				 काष्ठा dwc2_qtd *qtd)
अणु
	u32 hctsiz;
	पूर्णांक xfer_करोne = 0;
	पूर्णांक लघु_पढ़ो = 0;
	पूर्णांक xfer_length = dwc2_get_actual_xfer_length(hsotg, chan, chnum, qtd,
						      DWC2_HC_XFER_COMPLETE,
						      &लघु_पढ़ो);

	अगर (urb->actual_length + xfer_length > urb->length) अणु
		dev_dbg(hsotg->dev, "%s(): trimming xfer length\n", __func__);
		xfer_length = urb->length - urb->actual_length;
	पूर्ण

	dev_vdbg(hsotg->dev, "urb->actual_length=%d xfer_length=%d\n",
		 urb->actual_length, xfer_length);
	urb->actual_length += xfer_length;

	अगर (xfer_length && chan->ep_type == USB_ENDPOINT_XFER_BULK &&
	    (urb->flags & URB_SEND_ZERO_PACKET) &&
	    urb->actual_length >= urb->length &&
	    !(urb->length % chan->max_packet)) अणु
		xfer_करोne = 0;
	पूर्ण अन्यथा अगर (लघु_पढ़ो || urb->actual_length >= urb->length) अणु
		xfer_करोne = 1;
		urb->status = 0;
	पूर्ण

	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
	dev_vdbg(hsotg->dev, "DWC_otg: %s: %s, channel %d\n",
		 __func__, (chan->ep_is_in ? "IN" : "OUT"), chnum);
	dev_vdbg(hsotg->dev, "  chan->xfer_len %d\n", chan->xfer_len);
	dev_vdbg(hsotg->dev, "  hctsiz.xfersize %d\n",
		 (hctsiz & TSIZ_XFERSIZE_MASK) >> TSIZ_XFERSIZE_SHIFT);
	dev_vdbg(hsotg->dev, "  urb->transfer_buffer_length %d\n", urb->length);
	dev_vdbg(hsotg->dev, "  urb->actual_length %d\n", urb->actual_length);
	dev_vdbg(hsotg->dev, "  short_read %d, xfer_done %d\n", लघु_पढ़ो,
		 xfer_करोne);

	वापस xfer_करोne;
पूर्ण

/*
 * Save the starting data toggle क्रम the next transfer. The data toggle is
 * saved in the QH क्रम non-control transfers and it's saved in the QTD क्रम
 * control transfers.
 */
व्योम dwc2_hcd_save_data_toggle(काष्ठा dwc2_hsotg *hsotg,
			       काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
			       काष्ठा dwc2_qtd *qtd)
अणु
	u32 hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
	u32 pid = (hctsiz & TSIZ_SC_MC_PID_MASK) >> TSIZ_SC_MC_PID_SHIFT;

	अगर (chan->ep_type != USB_ENDPOINT_XFER_CONTROL) अणु
		अगर (WARN(!chan || !chan->qh,
			 "chan->qh must be specified for non-control eps\n"))
			वापस;

		अगर (pid == TSIZ_SC_MC_PID_DATA0)
			chan->qh->data_toggle = DWC2_HC_PID_DATA0;
		अन्यथा
			chan->qh->data_toggle = DWC2_HC_PID_DATA1;
	पूर्ण अन्यथा अणु
		अगर (WARN(!qtd,
			 "qtd must be specified for control eps\n"))
			वापस;

		अगर (pid == TSIZ_SC_MC_PID_DATA0)
			qtd->data_toggle = DWC2_HC_PID_DATA0;
		अन्यथा
			qtd->data_toggle = DWC2_HC_PID_DATA1;
	पूर्ण
पूर्ण

/**
 * dwc2_update_isoc_urb_state() - Updates the state of an Isochronous URB when
 * the transfer is stopped क्रम any reason. The fields of the current entry in
 * the frame descriptor array are set based on the transfer state and the input
 * halt_status. Completes the Isochronous URB अगर all the URB frames have been
 * completed.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @chan: Programming view of host channel
 * @chnum: Channel number
 * @halt_status: Reason क्रम halting a host channel
 * @qtd: Queue transfer descriptor
 *
 * Return: DWC2_HC_XFER_COMPLETE अगर there are more frames reमुख्यing to be
 * transferred in the URB. Otherwise वापस DWC2_HC_XFER_URB_COMPLETE.
 */
अटल क्रमागत dwc2_halt_status dwc2_update_isoc_urb_state(
		काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan,
		पूर्णांक chnum, काष्ठा dwc2_qtd *qtd,
		क्रमागत dwc2_halt_status halt_status)
अणु
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;

	अगर (!urb)
		वापस DWC2_HC_XFER_NO_HALT_STATUS;

	frame_desc = &urb->iso_descs[qtd->isoc_frame_index];

	चयन (halt_status) अणु
	हाल DWC2_HC_XFER_COMPLETE:
		frame_desc->status = 0;
		frame_desc->actual_length = dwc2_get_actual_xfer_length(hsotg,
					chan, chnum, qtd, halt_status, शून्य);
		अवरोध;
	हाल DWC2_HC_XFER_FRAME_OVERRUN:
		urb->error_count++;
		अगर (chan->ep_is_in)
			frame_desc->status = -ENOSR;
		अन्यथा
			frame_desc->status = -ECOMM;
		frame_desc->actual_length = 0;
		अवरोध;
	हाल DWC2_HC_XFER_BABBLE_ERR:
		urb->error_count++;
		frame_desc->status = -EOVERFLOW;
		/* Don't need to update actual_length in this हाल */
		अवरोध;
	हाल DWC2_HC_XFER_XACT_ERR:
		urb->error_count++;
		frame_desc->status = -EPROTO;
		frame_desc->actual_length = dwc2_get_actual_xfer_length(hsotg,
					chan, chnum, qtd, halt_status, शून्य);

		/* Skip whole frame */
		अगर (chan->qh->करो_split &&
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC && chan->ep_is_in &&
		    hsotg->params.host_dma) अणु
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
		पूर्ण

		अवरोध;
	शेष:
		dev_err(hsotg->dev, "Unhandled halt_status (%d)\n",
			halt_status);
		अवरोध;
	पूर्ण

	अगर (++qtd->isoc_frame_index == urb->packet_count) अणु
		/*
		 * urb->status is not used क्रम isoc transfers. The inभागidual
		 * frame_desc statuses are used instead.
		 */
		dwc2_host_complete(hsotg, qtd, 0);
		halt_status = DWC2_HC_XFER_URB_COMPLETE;
	पूर्ण अन्यथा अणु
		halt_status = DWC2_HC_XFER_COMPLETE;
	पूर्ण

	वापस halt_status;
पूर्ण

/*
 * Frees the first QTD in the QH's list अगर मुक्त_qtd is 1. For non-periodic
 * QHs, हटाओs the QH from the active non-periodic schedule. If any QTDs are
 * still linked to the QH, the QH is added to the end of the inactive
 * non-periodic schedule. For periodic QHs, हटाओs the QH from the periodic
 * schedule अगर no more QTDs are linked to the QH.
 */
अटल व्योम dwc2_deactivate_qh(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			       पूर्णांक मुक्त_qtd)
अणु
	पूर्णांक जारी_split = 0;
	काष्ठा dwc2_qtd *qtd;

	अगर (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "  %s(%p,%p,%d)\n", __func__,
			 hsotg, qh, मुक्त_qtd);

	अगर (list_empty(&qh->qtd_list)) अणु
		dev_dbg(hsotg->dev, "## QTD list empty ##\n");
		जाओ no_qtd;
	पूर्ण

	qtd = list_first_entry(&qh->qtd_list, काष्ठा dwc2_qtd, qtd_list_entry);

	अगर (qtd->complete_split)
		जारी_split = 1;
	अन्यथा अगर (qtd->isoc_split_pos == DWC2_HCSPLT_XACTPOS_MID ||
		 qtd->isoc_split_pos == DWC2_HCSPLT_XACTPOS_END)
		जारी_split = 1;

	अगर (मुक्त_qtd) अणु
		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);
		जारी_split = 0;
	पूर्ण

no_qtd:
	qh->channel = शून्य;
	dwc2_hcd_qh_deactivate(hsotg, qh, जारी_split);
पूर्ण

/**
 * dwc2_release_channel() - Releases a host channel क्रम use by other transfers
 *
 * @hsotg:       The HCD state काष्ठाure
 * @chan:        The host channel to release
 * @qtd:         The QTD associated with the host channel. This QTD may be
 *               मुक्तd अगर the transfer is complete or an error has occurred.
 * @halt_status: Reason the channel is being released. This status
 *               determines the actions taken by this function.
 *
 * Also attempts to select and queue more transactions since at least one host
 * channel is available.
 */
अटल व्योम dwc2_release_channel(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan,
				 काष्ठा dwc2_qtd *qtd,
				 क्रमागत dwc2_halt_status halt_status)
अणु
	क्रमागत dwc2_transaction_type tr_type;
	u32 haपूर्णांकmsk;
	पूर्णांक मुक्त_qtd = 0;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "  %s: channel %d, halt_status %d\n",
			 __func__, chan->hc_num, halt_status);

	चयन (halt_status) अणु
	हाल DWC2_HC_XFER_URB_COMPLETE:
		मुक्त_qtd = 1;
		अवरोध;
	हाल DWC2_HC_XFER_AHB_ERR:
	हाल DWC2_HC_XFER_STALL:
	हाल DWC2_HC_XFER_BABBLE_ERR:
		मुक्त_qtd = 1;
		अवरोध;
	हाल DWC2_HC_XFER_XACT_ERR:
		अगर (qtd && qtd->error_count >= 3) अणु
			dev_vdbg(hsotg->dev,
				 "  Complete URB with transaction error\n");
			मुक्त_qtd = 1;
			dwc2_host_complete(hsotg, qtd, -EPROTO);
		पूर्ण
		अवरोध;
	हाल DWC2_HC_XFER_URB_DEQUEUE:
		/*
		 * The QTD has alपढ़ोy been हटाओd and the QH has been
		 * deactivated. Don't want to करो anything except release the
		 * host channel and try to queue more transfers.
		 */
		जाओ cleanup;
	हाल DWC2_HC_XFER_PERIODIC_INCOMPLETE:
		dev_vdbg(hsotg->dev, "  Complete URB with I/O error\n");
		मुक्त_qtd = 1;
		dwc2_host_complete(hsotg, qtd, -EIO);
		अवरोध;
	हाल DWC2_HC_XFER_NO_HALT_STATUS:
	शेष:
		अवरोध;
	पूर्ण

	dwc2_deactivate_qh(hsotg, chan->qh, मुक्त_qtd);

cleanup:
	/*
	 * Release the host channel क्रम use by other transfers. The cleanup
	 * function clears the channel पूर्णांकerrupt enables and conditions, so
	 * there's no need to clear the Channel Halted पूर्णांकerrupt separately.
	 */
	अगर (!list_empty(&chan->hc_list_entry))
		list_del(&chan->hc_list_entry);
	dwc2_hc_cleanup(hsotg, chan);
	list_add_tail(&chan->hc_list_entry, &hsotg->मुक्त_hc_list);

	अगर (hsotg->params.uframe_sched) अणु
		hsotg->available_host_channels++;
	पूर्ण अन्यथा अणु
		चयन (chan->ep_type) अणु
		हाल USB_ENDPOINT_XFER_CONTROL:
		हाल USB_ENDPOINT_XFER_BULK:
			hsotg->non_periodic_channels--;
			अवरोध;
		शेष:
			/*
			 * Don't release reservations क्रम periodic channels
			 * here. That's करोne when a periodic transfer is
			 * descheduled (i.e. when the QH is हटाओd from the
			 * periodic schedule).
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	haपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HAINTMSK);
	haपूर्णांकmsk &= ~(1 << chan->hc_num);
	dwc2_ग_लिखोl(hsotg, haपूर्णांकmsk, HAINTMSK);

	/* Try to queue more transfers now that there's a मुक्त channel */
	tr_type = dwc2_hcd_select_transactions(hsotg);
	अगर (tr_type != DWC2_TRANSACTION_NONE)
		dwc2_hcd_queue_transactions(hsotg, tr_type);
पूर्ण

/*
 * Halts a host channel. If the channel cannot be halted immediately because
 * the request queue is full, this function ensures that the FIFO empty
 * पूर्णांकerrupt क्रम the appropriate queue is enabled so that the halt request can
 * be queued when there is space in the request queue.
 *
 * This function may also be called in DMA mode. In that हाल, the channel is
 * simply released since the core always halts the channel स्वतःmatically in
 * DMA mode.
 */
अटल व्योम dwc2_halt_channel(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_host_chan *chan, काष्ठा dwc2_qtd *qtd,
			      क्रमागत dwc2_halt_status halt_status)
अणु
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	अगर (hsotg->params.host_dma) अणु
		अगर (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabled\n");
		dwc2_release_channel(hsotg, chan, qtd, halt_status);
		वापस;
	पूर्ण

	/* Slave mode processing */
	dwc2_hc_halt(hsotg, chan, halt_status);

	अगर (chan->halt_on_queue) अणु
		u32 gपूर्णांकmsk;

		dev_vdbg(hsotg->dev, "Halt on queue\n");
		अगर (chan->ep_type == USB_ENDPOINT_XFER_CONTROL ||
		    chan->ep_type == USB_ENDPOINT_XFER_BULK) अणु
			dev_vdbg(hsotg->dev, "control/bulk\n");
			/*
			 * Make sure the Non-periodic Tx FIFO empty पूर्णांकerrupt
			 * is enabled so that the non-periodic schedule will
			 * be processed
			 */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk |= GINTSTS_NPTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण अन्यथा अणु
			dev_vdbg(hsotg->dev, "isoc/intr\n");
			/*
			 * Move the QH from the periodic queued schedule to
			 * the periodic asचिन्हित schedule. This allows the
			 * halt to be queued when the periodic schedule is
			 * processed.
			 */
			list_move_tail(&chan->qh->qh_list_entry,
				       &hsotg->periodic_sched_asचिन्हित);

			/*
			 * Make sure the Periodic Tx FIFO Empty पूर्णांकerrupt is
			 * enabled so that the periodic schedule will be
			 * processed
			 */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk |= GINTSTS_PTXFEMP;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Perक्रमms common cleanup क्रम non-periodic transfers after a Transfer
 * Complete पूर्णांकerrupt. This function should be called after any endpoपूर्णांक type
 * specअगरic handling is finished to release the host channel.
 */
अटल व्योम dwc2_complete_non_periodic_xfer(काष्ठा dwc2_hsotg *hsotg,
					    काष्ठा dwc2_host_chan *chan,
					    पूर्णांक chnum, काष्ठा dwc2_qtd *qtd,
					    क्रमागत dwc2_halt_status halt_status)
अणु
	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	qtd->error_count = 0;

	अगर (chan->hcपूर्णांक & HCINTMSK_NYET) अणु
		/*
		 * Got a NYET on the last transaction of the transfer. This
		 * means that the endpoपूर्णांक should be in the PING state at the
		 * beginning of the next transfer.
		 */
		dev_vdbg(hsotg->dev, "got NYET\n");
		chan->qh->ping_state = 1;
	पूर्ण

	/*
	 * Always halt and release the host channel to make it available क्रम
	 * more transfers. There may still be more phases क्रम a control
	 * transfer or more data packets क्रम a bulk transfer at this poपूर्णांक,
	 * but the host channel is still halted. A channel will be reasचिन्हित
	 * to the transfer when the non-periodic schedule is processed after
	 * the channel is released. This allows transactions to be queued
	 * properly via dwc2_hcd_queue_transactions, which also enables the
	 * Tx FIFO Empty पूर्णांकerrupt अगर necessary.
	 */
	अगर (chan->ep_is_in) अणु
		/*
		 * IN transfers in Slave mode require an explicit disable to
		 * halt the channel. (In DMA mode, this call simply releases
		 * the channel.)
		 */
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
	पूर्ण अन्यथा अणु
		/*
		 * The channel is स्वतःmatically disabled by the core क्रम OUT
		 * transfers in Slave mode
		 */
		dwc2_release_channel(hsotg, chan, qtd, halt_status);
	पूर्ण
पूर्ण

/*
 * Perक्रमms common cleanup क्रम periodic transfers after a Transfer Complete
 * पूर्णांकerrupt. This function should be called after any endpoपूर्णांक type specअगरic
 * handling is finished to release the host channel.
 */
अटल व्योम dwc2_complete_periodic_xfer(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
					काष्ठा dwc2_qtd *qtd,
					क्रमागत dwc2_halt_status halt_status)
अणु
	u32 hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));

	qtd->error_count = 0;

	अगर (!chan->ep_is_in || (hctsiz & TSIZ_PKTCNT_MASK) == 0)
		/* Core halts channel in these हालs */
		dwc2_release_channel(hsotg, chan, qtd, halt_status);
	अन्यथा
		/* Flush any outstanding requests from the Tx queue */
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
पूर्ण

अटल पूर्णांक dwc2_xfercomp_isoc_split_in(काष्ठा dwc2_hsotg *hsotg,
				       काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				       काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;
	u32 len;
	u32 hctsiz;
	u32 pid;

	अगर (!qtd->urb)
		वापस 0;

	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index];
	len = dwc2_get_actual_xfer_length(hsotg, chan, chnum, qtd,
					  DWC2_HC_XFER_COMPLETE, शून्य);
	अगर (!len && !qtd->isoc_split_offset) अणु
		qtd->complete_split = 0;
		वापस 0;
	पूर्ण

	frame_desc->actual_length += len;

	अगर (chan->align_buf) अणु
		dev_vdbg(hsotg->dev, "non-aligned buffer\n");
		dma_unmap_single(hsotg->dev, chan->qh->dw_align_buf_dma,
				 DWC2_KMEM_UNALIGNED_BUF_SIZE, DMA_FROM_DEVICE);
		स_नकल(qtd->urb->buf + (chan->xfer_dma - qtd->urb->dma),
		       chan->qh->dw_align_buf, len);
	पूर्ण

	qtd->isoc_split_offset += len;

	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
	pid = (hctsiz & TSIZ_SC_MC_PID_MASK) >> TSIZ_SC_MC_PID_SHIFT;

	अगर (frame_desc->actual_length >= frame_desc->length || pid == 0) अणु
		frame_desc->status = 0;
		qtd->isoc_frame_index++;
		qtd->complete_split = 0;
		qtd->isoc_split_offset = 0;
	पूर्ण

	अगर (qtd->isoc_frame_index == qtd->urb->packet_count) अणु
		dwc2_host_complete(hsotg, qtd, 0);
		dwc2_release_channel(hsotg, chan, qtd,
				     DWC2_HC_XFER_URB_COMPLETE);
	पूर्ण अन्यथा अणु
		dwc2_release_channel(hsotg, chan, qtd,
				     DWC2_HC_XFER_NO_HALT_STATUS);
	पूर्ण

	वापस 1;	/* Indicates that channel released */
पूर्ण

/*
 * Handles a host channel Transfer Complete पूर्णांकerrupt. This handler may be
 * called in either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_xfercomp_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				  काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				  काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	क्रमागत dwc2_halt_status halt_status = DWC2_HC_XFER_COMPLETE;
	पूर्णांक pipe_type;
	पूर्णांक urb_xfer_करोne;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev,
			 "--Host Channel %d Interrupt: Transfer Complete--\n",
			 chnum);

	अगर (!urb)
		जाओ handle_xfercomp_करोne;

	pipe_type = dwc2_hcd_get_pipe_type(&urb->pipe_info);

	अगर (hsotg->params.dma_desc_enable) अणु
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum, halt_status);
		अगर (pipe_type == USB_ENDPOINT_XFER_ISOC)
			/* Do not disable the पूर्णांकerrupt, just clear it */
			वापस;
		जाओ handle_xfercomp_करोne;
	पूर्ण

	/* Handle xfer complete on CSPLIT */
	अगर (chan->qh->करो_split) अणु
		अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC && chan->ep_is_in &&
		    hsotg->params.host_dma) अणु
			अगर (qtd->complete_split &&
			    dwc2_xfercomp_isoc_split_in(hsotg, chan, chnum,
							qtd))
				जाओ handle_xfercomp_करोne;
		पूर्ण अन्यथा अणु
			qtd->complete_split = 0;
		पूर्ण
	पूर्ण

	/* Update the QTD and URB states */
	चयन (pipe_type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		चयन (qtd->control_phase) अणु
		हाल DWC2_CONTROL_SETUP:
			अगर (urb->length > 0)
				qtd->control_phase = DWC2_CONTROL_DATA;
			अन्यथा
				qtd->control_phase = DWC2_CONTROL_STATUS;
			dev_vdbg(hsotg->dev,
				 "  Control setup transaction done\n");
			halt_status = DWC2_HC_XFER_COMPLETE;
			अवरोध;
		हाल DWC2_CONTROL_DATA:
			urb_xfer_करोne = dwc2_update_urb_state(hsotg, chan,
							      chnum, urb, qtd);
			अगर (urb_xfer_करोne) अणु
				qtd->control_phase = DWC2_CONTROL_STATUS;
				dev_vdbg(hsotg->dev,
					 "  Control data transfer done\n");
			पूर्ण अन्यथा अणु
				dwc2_hcd_save_data_toggle(hsotg, chan, chnum,
							  qtd);
			पूर्ण
			halt_status = DWC2_HC_XFER_COMPLETE;
			अवरोध;
		हाल DWC2_CONTROL_STATUS:
			dev_vdbg(hsotg->dev, "  Control transfer complete\n");
			अगर (urb->status == -EINPROGRESS)
				urb->status = 0;
			dwc2_host_complete(hsotg, qtd, urb->status);
			halt_status = DWC2_HC_XFER_URB_COMPLETE;
			अवरोध;
		पूर्ण

		dwc2_complete_non_periodic_xfer(hsotg, chan, chnum, qtd,
						halt_status);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		dev_vdbg(hsotg->dev, "  Bulk transfer complete\n");
		urb_xfer_करोne = dwc2_update_urb_state(hsotg, chan, chnum, urb,
						      qtd);
		अगर (urb_xfer_करोne) अणु
			dwc2_host_complete(hsotg, qtd, urb->status);
			halt_status = DWC2_HC_XFER_URB_COMPLETE;
		पूर्ण अन्यथा अणु
			halt_status = DWC2_HC_XFER_COMPLETE;
		पूर्ण

		dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
		dwc2_complete_non_periodic_xfer(hsotg, chan, chnum, qtd,
						halt_status);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		dev_vdbg(hsotg->dev, "  Interrupt transfer complete\n");
		urb_xfer_करोne = dwc2_update_urb_state(hsotg, chan, chnum, urb,
						      qtd);

		/*
		 * Interrupt URB is करोne on the first transfer complete
		 * पूर्णांकerrupt
		 */
		अगर (urb_xfer_करोne) अणु
			dwc2_host_complete(hsotg, qtd, urb->status);
			halt_status = DWC2_HC_XFER_URB_COMPLETE;
		पूर्ण अन्यथा अणु
			halt_status = DWC2_HC_XFER_COMPLETE;
		पूर्ण

		dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
		dwc2_complete_periodic_xfer(hsotg, chan, chnum, qtd,
					    halt_status);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (dbg_perio())
			dev_vdbg(hsotg->dev, "  Isochronous transfer complete\n");
		अगर (qtd->isoc_split_pos == DWC2_HCSPLT_XACTPOS_ALL)
			halt_status = dwc2_update_isoc_urb_state(hsotg, chan,
							chnum, qtd,
							DWC2_HC_XFER_COMPLETE);
		dwc2_complete_periodic_xfer(hsotg, chan, chnum, qtd,
					    halt_status);
		अवरोध;
	पूर्ण

handle_xfercomp_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_XFERCOMPL);
पूर्ण

/*
 * Handles a host channel STALL पूर्णांकerrupt. This handler may be called in
 * either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_stall_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
			       काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
			       काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	पूर्णांक pipe_type;

	dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: STALL Received--\n",
		chnum);

	अगर (hsotg->params.dma_desc_enable) अणु
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_STALL);
		जाओ handle_stall_करोne;
	पूर्ण

	अगर (!urb)
		जाओ handle_stall_halt;

	pipe_type = dwc2_hcd_get_pipe_type(&urb->pipe_info);

	अगर (pipe_type == USB_ENDPOINT_XFER_CONTROL)
		dwc2_host_complete(hsotg, qtd, -EPIPE);

	अगर (pipe_type == USB_ENDPOINT_XFER_BULK ||
	    pipe_type == USB_ENDPOINT_XFER_INT) अणु
		dwc2_host_complete(hsotg, qtd, -EPIPE);
		/*
		 * USB protocol requires resetting the data toggle क्रम bulk
		 * and पूर्णांकerrupt endpoपूर्णांकs when a CLEAR_FEATURE(ENDPOINT_HALT)
		 * setup command is issued to the endpoपूर्णांक. Anticipate the
		 * CLEAR_FEATURE command since a STALL has occurred and reset
		 * the data toggle now.
		 */
		chan->qh->data_toggle = 0;
	पूर्ण

handle_stall_halt:
	dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_STALL);

handle_stall_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_STALL);
पूर्ण

/*
 * Updates the state of the URB when a transfer has been stopped due to an
 * abnormal condition beक्रमe the transfer completes. Modअगरies the
 * actual_length field of the URB to reflect the number of bytes that have
 * actually been transferred via the host channel.
 */
अटल व्योम dwc2_update_urb_state_abn(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				      काष्ठा dwc2_hcd_urb *urb,
				      काष्ठा dwc2_qtd *qtd,
				      क्रमागत dwc2_halt_status halt_status)
अणु
	u32 xfer_length = dwc2_get_actual_xfer_length(hsotg, chan, chnum,
						      qtd, halt_status, शून्य);
	u32 hctsiz;

	अगर (urb->actual_length + xfer_length > urb->length) अणु
		dev_warn(hsotg->dev, "%s(): trimming xfer length\n", __func__);
		xfer_length = urb->length - urb->actual_length;
	पूर्ण

	urb->actual_length += xfer_length;

	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
	dev_vdbg(hsotg->dev, "DWC_otg: %s: %s, channel %d\n",
		 __func__, (chan->ep_is_in ? "IN" : "OUT"), chnum);
	dev_vdbg(hsotg->dev, "  chan->start_pkt_count %d\n",
		 chan->start_pkt_count);
	dev_vdbg(hsotg->dev, "  hctsiz.pktcnt %d\n",
		 (hctsiz & TSIZ_PKTCNT_MASK) >> TSIZ_PKTCNT_SHIFT);
	dev_vdbg(hsotg->dev, "  chan->max_packet %d\n", chan->max_packet);
	dev_vdbg(hsotg->dev, "  bytes_transferred %d\n",
		 xfer_length);
	dev_vdbg(hsotg->dev, "  urb->actual_length %d\n",
		 urb->actual_length);
	dev_vdbg(hsotg->dev, "  urb->transfer_buffer_length %d\n",
		 urb->length);
पूर्ण

/*
 * Handles a host channel NAK पूर्णांकerrupt. This handler may be called in either
 * DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_nak_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
			     काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
			     काष्ठा dwc2_qtd *qtd)
अणु
	अगर (!qtd) अणु
		dev_dbg(hsotg->dev, "%s: qtd is NULL\n", __func__);
		वापस;
	पूर्ण

	अगर (!qtd->urb) अणु
		dev_dbg(hsotg->dev, "%s: qtd->urb is NULL\n", __func__);
		वापस;
	पूर्ण

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: NAK Received--\n",
			 chnum);

	/*
	 * Handle NAK क्रम IN/OUT SSPLIT/CSPLIT transfers, bulk, control, and
	 * पूर्णांकerrupt. Re-start the SSPLIT transfer.
	 *
	 * Normally क्रम non-periodic transfers we'll retry right away, but to
	 * aव्योम पूर्णांकerrupt storms we'll wait before retrying if we've got
	 * several NAKs. If we didn't do this we'd retry directly from the
	 * पूर्णांकerrupt handler and could end up quickly getting another
	 * पूर्णांकerrupt (another NAK), which we'd retry. Note that we करो not
	 * delay retries क्रम IN parts of control requests, as those are expected
	 * to complete fairly quickly, and अगर we delay them we risk confusing
	 * the device and cause it issue STALL.
	 *
	 * Note that in DMA mode software only माला_लो involved to re-send NAKed
	 * transfers क्रम split transactions, so we only need to apply this
	 * delaying logic when handling splits. In non-DMA mode presumably we
	 * might want a similar delay अगर someone can demonstrate this problem
	 * affects that code path too.
	 */
	अगर (chan->करो_split) अणु
		अगर (chan->complete_split)
			qtd->error_count = 0;
		qtd->complete_split = 0;
		qtd->num_naks++;
		qtd->qh->want_रुको = qtd->num_naks >= DWC2_NAKS_BEFORE_DELAY &&
				!(chan->ep_type == USB_ENDPOINT_XFER_CONTROL &&
				  chan->ep_is_in);
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NAK);
		जाओ handle_nak_करोne;
	पूर्ण

	चयन (dwc2_hcd_get_pipe_type(&qtd->urb->pipe_info)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (hsotg->params.host_dma && chan->ep_is_in) अणु
			/*
			 * NAK पूर्णांकerrupts are enabled on bulk/control IN
			 * transfers in DMA mode क्रम the sole purpose of
			 * resetting the error count after a transaction error
			 * occurs. The core will जारी transferring data.
			 */
			qtd->error_count = 0;
			अवरोध;
		पूर्ण

		/*
		 * NAK पूर्णांकerrupts normally occur during OUT transfers in DMA
		 * or Slave mode. For IN transfers, more requests will be
		 * queued as request queue space is available.
		 */
		qtd->error_count = 0;

		अगर (!chan->qh->ping_state) अणु
			dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb,
						  qtd, DWC2_HC_XFER_NAK);
			dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);

			अगर (chan->speed == USB_SPEED_HIGH)
				chan->qh->ping_state = 1;
		पूर्ण

		/*
		 * Halt the channel so the transfer can be re-started from
		 * the appropriate poपूर्णांक or the PING protocol will
		 * start/जारी
		 */
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NAK);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		qtd->error_count = 0;
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NAK);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* Should never get called क्रम isochronous transfers */
		dev_err(hsotg->dev, "NACK interrupt for ISOC transfer\n");
		अवरोध;
	पूर्ण

handle_nak_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_NAK);
पूर्ण

/*
 * Handles a host channel ACK पूर्णांकerrupt. This पूर्णांकerrupt is enabled when
 * perक्रमming the PING protocol in Slave mode, when errors occur during
 * either Slave mode or DMA mode, and during Start Split transactions.
 */
अटल व्योम dwc2_hc_ack_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
			     काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
			     काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: ACK Received--\n",
			 chnum);

	अगर (chan->करो_split) अणु
		/* Handle ACK on SSPLIT. ACK should not occur in CSPLIT. */
		अगर (!chan->ep_is_in &&
		    chan->data_pid_start != DWC2_HC_PID_SETUP)
			qtd->ssplit_out_xfer_count = chan->xfer_len;

		अगर (chan->ep_type != USB_ENDPOINT_XFER_ISOC || chan->ep_is_in) अणु
			qtd->complete_split = 1;
			dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_ACK);
		पूर्ण अन्यथा अणु
			/* ISOC OUT */
			चयन (chan->xact_pos) अणु
			हाल DWC2_HCSPLT_XACTPOS_ALL:
				अवरोध;
			हाल DWC2_HCSPLT_XACTPOS_END:
				qtd->isoc_split_pos = DWC2_HCSPLT_XACTPOS_ALL;
				qtd->isoc_split_offset = 0;
				अवरोध;
			हाल DWC2_HCSPLT_XACTPOS_BEGIN:
			हाल DWC2_HCSPLT_XACTPOS_MID:
				/*
				 * For BEGIN or MID, calculate the length क्रम
				 * the next microframe to determine the correct
				 * SSPLIT token, either MID or END
				 */
				frame_desc = &qtd->urb->iso_descs[
						qtd->isoc_frame_index];
				qtd->isoc_split_offset += 188;

				अगर (frame_desc->length - qtd->isoc_split_offset
							<= 188)
					qtd->isoc_split_pos =
							DWC2_HCSPLT_XACTPOS_END;
				अन्यथा
					qtd->isoc_split_pos =
							DWC2_HCSPLT_XACTPOS_MID;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		qtd->error_count = 0;

		अगर (chan->qh->ping_state) अणु
			chan->qh->ping_state = 0;
			/*
			 * Halt the channel so the transfer can be re-started
			 * from the appropriate poपूर्णांक. This only happens in
			 * Slave mode. In DMA mode, the ping_state is cleared
			 * when the transfer is started because the core
			 * स्वतःmatically executes the PING, then the transfer.
			 */
			dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_ACK);
		पूर्ण
	पूर्ण

	/*
	 * If the ACK occurred when _not_ in the PING state, let the channel
	 * जारी transferring data after clearing the error count
	 */
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_ACK);
पूर्ण

/*
 * Handles a host channel NYET पूर्णांकerrupt. This पूर्णांकerrupt should only occur on
 * Bulk and Control OUT endpoपूर्णांकs and क्रम complete split transactions. If a
 * NYET occurs at the same समय as a Transfer Complete पूर्णांकerrupt, it is
 * handled in the xfercomp पूर्णांकerrupt handler, not here. This handler may be
 * called in either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_nyet_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
			      काष्ठा dwc2_qtd *qtd)
अणु
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: NYET Received--\n",
			 chnum);

	/*
	 * NYET on CSPLIT
	 * re-करो the CSPLIT immediately on non-periodic
	 */
	अगर (chan->करो_split && chan->complete_split) अणु
		अगर (chan->ep_is_in && chan->ep_type == USB_ENDPOINT_XFER_ISOC &&
		    hsotg->params.host_dma) अणु
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
			qtd->isoc_frame_index++;
			अगर (qtd->urb &&
			    qtd->isoc_frame_index == qtd->urb->packet_count) अणु
				dwc2_host_complete(hsotg, qtd, 0);
				dwc2_release_channel(hsotg, chan, qtd,
						     DWC2_HC_XFER_URB_COMPLETE);
			पूर्ण अन्यथा अणु
				dwc2_release_channel(hsotg, chan, qtd,
						DWC2_HC_XFER_NO_HALT_STATUS);
			पूर्ण
			जाओ handle_nyet_करोne;
		पूर्ण

		अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
			काष्ठा dwc2_qh *qh = chan->qh;
			bool past_end;

			अगर (!hsotg->params.uframe_sched) अणु
				पूर्णांक frnum = dwc2_hcd_get_frame_number(hsotg);

				/* Don't have num_hs_transfers; simple logic */
				past_end = dwc2_full_frame_num(frnum) !=
				     dwc2_full_frame_num(qh->next_active_frame);
			पूर्ण अन्यथा अणु
				पूर्णांक end_frnum;

				/*
				 * Figure out the end frame based on
				 * schedule.
				 *
				 * We करोn't want to go on trying again
				 * and again क्रमever. Let's stop when
				 * we've करोne all the transfers that
				 * were scheduled.
				 *
				 * We're going to be comparing
				 * start_active_frame and
				 * next_active_frame, both of which
				 * are 1 beक्रमe the समय the packet
				 * goes on the wire, so that cancels
				 * out. Basically अगर had 1 transfer
				 * and we saw 1 NYET then we're करोne.
				 * We're getting a NYET here so अगर
				 * next >= (start + num_transfers)
				 * we're करोne. The complनिकासy is that
				 * क्रम all but ISOC_OUT we skip one
				 * slot.
				 */
				end_frnum = dwc2_frame_num_inc(
					qh->start_active_frame,
					qh->num_hs_transfers);

				अगर (qh->ep_type != USB_ENDPOINT_XFER_ISOC ||
				    qh->ep_is_in)
					end_frnum =
					       dwc2_frame_num_inc(end_frnum, 1);

				past_end = dwc2_frame_num_le(
					end_frnum, qh->next_active_frame);
			पूर्ण

			अगर (past_end) अणु
				/* Treat this as a transaction error. */
#अगर 0
				/*
				 * Toकरो: Fix प्रणाली perक्रमmance so this can
				 * be treated as an error. Right now complete
				 * splits cannot be scheduled precisely enough
				 * due to other प्रणाली activity, so this error
				 * occurs regularly in Slave mode.
				 */
				qtd->error_count++;
#पूर्ण_अगर
				qtd->complete_split = 0;
				dwc2_halt_channel(hsotg, chan, qtd,
						  DWC2_HC_XFER_XACT_ERR);
				/* Toकरो: add support क्रम isoc release */
				जाओ handle_nyet_करोne;
			पूर्ण
		पूर्ण

		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NYET);
		जाओ handle_nyet_करोne;
	पूर्ण

	chan->qh->ping_state = 1;
	qtd->error_count = 0;

	dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb, qtd,
				  DWC2_HC_XFER_NYET);
	dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);

	/*
	 * Halt the channel and re-start the transfer so the PING protocol
	 * will start
	 */
	dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NYET);

handle_nyet_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_NYET);
पूर्ण

/*
 * Handles a host channel babble पूर्णांकerrupt. This handler may be called in
 * either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_babble_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				काष्ठा dwc2_qtd *qtd)
अणु
	dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: Babble Error--\n",
		chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	अगर (hsotg->params.dma_desc_enable) अणु
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_BABBLE_ERR);
		जाओ disable_पूर्णांक;
	पूर्ण

	अगर (chan->ep_type != USB_ENDPOINT_XFER_ISOC) अणु
		dwc2_host_complete(hsotg, qtd, -EOVERFLOW);
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_BABBLE_ERR);
	पूर्ण अन्यथा अणु
		क्रमागत dwc2_halt_status halt_status;

		halt_status = dwc2_update_isoc_urb_state(hsotg, chan, chnum,
						qtd, DWC2_HC_XFER_BABBLE_ERR);
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
	पूर्ण

disable_पूर्णांक:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_BBLERR);
पूर्ण

/*
 * Handles a host channel AHB error पूर्णांकerrupt. This handler is only called in
 * DMA mode.
 */
अटल व्योम dwc2_hc_ahberr_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				काष्ठा dwc2_qtd *qtd)
अणु
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	अक्षर *pipetype, *speed;
	u32 hcअक्षर;
	u32 hcsplt;
	u32 hctsiz;
	u32 hc_dma;

	dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: AHB Error--\n",
		chnum);

	अगर (!urb)
		जाओ handle_ahberr_halt;

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chnum));
	hcsplt = dwc2_पढ़ोl(hsotg, HCSPLT(chnum));
	hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
	hc_dma = dwc2_पढ़ोl(hsotg, HCDMA(chnum));

	dev_err(hsotg->dev, "AHB ERROR, Channel %d\n", chnum);
	dev_err(hsotg->dev, "  hcchar 0x%08x, hcsplt 0x%08x\n", hcअक्षर, hcsplt);
	dev_err(hsotg->dev, "  hctsiz 0x%08x, hc_dma 0x%08x\n", hctsiz, hc_dma);
	dev_err(hsotg->dev, "  Device address: %d\n",
		dwc2_hcd_get_dev_addr(&urb->pipe_info));
	dev_err(hsotg->dev, "  Endpoint: %d, %s\n",
		dwc2_hcd_get_ep_num(&urb->pipe_info),
		dwc2_hcd_is_pipe_in(&urb->pipe_info) ? "IN" : "OUT");

	चयन (dwc2_hcd_get_pipe_type(&urb->pipe_info)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		pipetype = "CONTROL";
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		pipetype = "BULK";
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		pipetype = "INTERRUPT";
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		pipetype = "ISOCHRONOUS";
		अवरोध;
	शेष:
		pipetype = "UNKNOWN";
		अवरोध;
	पूर्ण

	dev_err(hsotg->dev, "  Endpoint type: %s\n", pipetype);

	चयन (chan->speed) अणु
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

	dev_err(hsotg->dev, "  Speed: %s\n", speed);

	dev_err(hsotg->dev, "  Max packet size: %d (mult %d)\n",
		dwc2_hcd_get_maxp(&urb->pipe_info),
		dwc2_hcd_get_maxp_mult(&urb->pipe_info));
	dev_err(hsotg->dev, "  Data buffer length: %d\n", urb->length);
	dev_err(hsotg->dev, "  Transfer buffer: %p, Transfer DMA: %08lx\n",
		urb->buf, (अचिन्हित दीर्घ)urb->dma);
	dev_err(hsotg->dev, "  Setup buffer: %p, Setup DMA: %08lx\n",
		urb->setup_packet, (अचिन्हित दीर्घ)urb->setup_dma);
	dev_err(hsotg->dev, "  Interval: %d\n", urb->पूर्णांकerval);

	/* Core halts the channel क्रम Descriptor DMA mode */
	अगर (hsotg->params.dma_desc_enable) अणु
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_AHB_ERR);
		जाओ handle_ahberr_करोne;
	पूर्ण

	dwc2_host_complete(hsotg, qtd, -EIO);

handle_ahberr_halt:
	/*
	 * Force a channel halt. Don't call dwc2_halt_channel because that won't
	 * ग_लिखो to the HCCHARn रेजिस्टर in DMA mode to क्रमce the halt.
	 */
	dwc2_hc_halt(hsotg, chan, DWC2_HC_XFER_AHB_ERR);

handle_ahberr_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_AHBERR);
पूर्ण

/*
 * Handles a host channel transaction error पूर्णांकerrupt. This handler may be
 * called in either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_xacterr_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				 काष्ठा dwc2_qtd *qtd)
अणु
	dev_dbg(hsotg->dev,
		"--Host Channel %d Interrupt: Transaction Error--\n", chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	अगर (hsotg->params.dma_desc_enable) अणु
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_XACT_ERR);
		जाओ handle_xacterr_करोne;
	पूर्ण

	चयन (dwc2_hcd_get_pipe_type(&qtd->urb->pipe_info)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
		qtd->error_count++;
		अगर (!chan->qh->ping_state) अणु
			dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb,
						  qtd, DWC2_HC_XFER_XACT_ERR);
			dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
			अगर (!chan->ep_is_in && chan->speed == USB_SPEED_HIGH)
				chan->qh->ping_state = 1;
		पूर्ण

		/*
		 * Halt the channel so the transfer can be re-started from
		 * the appropriate poपूर्णांक or the PING protocol will start
		 */
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_XACT_ERR);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		qtd->error_count++;
		अगर (chan->करो_split && chan->complete_split)
			qtd->complete_split = 0;
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_XACT_ERR);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अणु
			क्रमागत dwc2_halt_status halt_status;

			halt_status = dwc2_update_isoc_urb_state(hsotg, chan,
					 chnum, qtd, DWC2_HC_XFER_XACT_ERR);
			dwc2_halt_channel(hsotg, chan, qtd, halt_status);
		पूर्ण
		अवरोध;
	पूर्ण

handle_xacterr_करोne:
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_XACTERR);
पूर्ण

/*
 * Handles a host channel frame overrun पूर्णांकerrupt. This handler may be called
 * in either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_frmovrun_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				  काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				  काष्ठा dwc2_qtd *qtd)
अणु
	क्रमागत dwc2_halt_status halt_status;

	अगर (dbg_hc(chan))
		dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: Frame Overrun--\n",
			chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	चयन (dwc2_hcd_get_pipe_type(&qtd->urb->pipe_info)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_FRAME_OVERRUN);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		halt_status = dwc2_update_isoc_urb_state(hsotg, chan, chnum,
					qtd, DWC2_HC_XFER_FRAME_OVERRUN);
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
		अवरोध;
	पूर्ण

	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_FRMOVRUN);
पूर्ण

/*
 * Handles a host channel data toggle error पूर्णांकerrupt. This handler may be
 * called in either DMA mode or Slave mode.
 */
अटल व्योम dwc2_hc_datatglerr_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				    काष्ठा dwc2_qtd *qtd)
अणु
	dev_dbg(hsotg->dev,
		"--Host Channel %d Interrupt: Data Toggle Error--\n", chnum);

	अगर (chan->ep_is_in)
		qtd->error_count = 0;
	अन्यथा
		dev_err(hsotg->dev,
			"Data Toggle Error on OUT transfer, channel %d\n",
			chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);
	disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_DATATGLERR);
पूर्ण

/*
 * For debug only. It checks that a valid halt status is set and that
 * HCCHARn.chdis is clear. If there's a problem, corrective action is
 * taken and a warning is issued.
 *
 * Return: true अगर halt status is ok, false otherwise
 */
अटल bool dwc2_halt_status_ok(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				काष्ठा dwc2_qtd *qtd)
अणु
#अगर_घोषित DEBUG
	u32 hcअक्षर;
	u32 hctsiz;
	u32 hcपूर्णांकmsk;
	u32 hcsplt;

	अगर (chan->halt_status == DWC2_HC_XFER_NO_HALT_STATUS) अणु
		/*
		 * This code is here only as a check. This condition should
		 * never happen. Ignore the halt अगर it करोes occur.
		 */
		hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chnum));
		hctsiz = dwc2_पढ़ोl(hsotg, HCTSIZ(chnum));
		hcपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HCINTMSK(chnum));
		hcsplt = dwc2_पढ़ोl(hsotg, HCSPLT(chnum));
		dev_dbg(hsotg->dev,
			"%s: chan->halt_status DWC2_HC_XFER_NO_HALT_STATUS,\n",
			 __func__);
		dev_dbg(hsotg->dev,
			"channel %d, hcchar 0x%08x, hctsiz 0x%08x,\n",
			chnum, hcअक्षर, hctsiz);
		dev_dbg(hsotg->dev,
			"hcint 0x%08x, hcintmsk 0x%08x, hcsplt 0x%08x,\n",
			chan->hcपूर्णांक, hcपूर्णांकmsk, hcsplt);
		अगर (qtd)
			dev_dbg(hsotg->dev, "qtd->complete_split %d\n",
				qtd->complete_split);
		dev_warn(hsotg->dev,
			 "%s: no halt status, channel %d, ignoring interrupt\n",
			 __func__, chnum);
		वापस false;
	पूर्ण

	/*
	 * This code is here only as a check. hcअक्षर.chdis should never be set
	 * when the halt पूर्णांकerrupt occurs. Halt the channel again अगर it करोes
	 * occur.
	 */
	hcअक्षर = dwc2_पढ़ोl(hsotg, HCCHAR(chnum));
	अगर (hcअक्षर & HCCHAR_CHDIS) अणु
		dev_warn(hsotg->dev,
			 "%s: hcchar.chdis set unexpectedly, hcchar 0x%08x, trying to halt again\n",
			 __func__, hcअक्षर);
		chan->halt_pending = 0;
		dwc2_halt_channel(hsotg, chan, qtd, chan->halt_status);
		वापस false;
	पूर्ण
#पूर्ण_अगर

	वापस true;
पूर्ण

/*
 * Handles a host Channel Halted पूर्णांकerrupt in DMA mode. This handler
 * determines the reason the channel halted and proceeds accordingly.
 */
अटल व्योम dwc2_hc_chhltd_पूर्णांकr_dma(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				    काष्ठा dwc2_qtd *qtd)
अणु
	u32 hcपूर्णांकmsk;
	पूर्णांक out_nak_enh = 0;

	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev,
			 "--Host Channel %d Interrupt: DMA Channel Halted--\n",
			 chnum);

	/*
	 * For core with OUT NAK enhancement, the flow क्रम high-speed
	 * CONTROL/BULK OUT is handled a little dअगरferently
	 */
	अगर (hsotg->hw_params.snpsid >= DWC2_CORE_REV_2_71a) अणु
		अगर (chan->speed == USB_SPEED_HIGH && !chan->ep_is_in &&
		    (chan->ep_type == USB_ENDPOINT_XFER_CONTROL ||
		     chan->ep_type == USB_ENDPOINT_XFER_BULK)) अणु
			out_nak_enh = 1;
		पूर्ण
	पूर्ण

	अगर (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE ||
	    (chan->halt_status == DWC2_HC_XFER_AHB_ERR &&
	     !hsotg->params.dma_desc_enable)) अणु
		अगर (hsotg->params.dma_desc_enable)
			dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
						    chan->halt_status);
		अन्यथा
			/*
			 * Just release the channel. A dequeue can happen on a
			 * transfer समयout. In the हाल of an AHB Error, the
			 * channel was क्रमced to halt because there's no way to
			 * gracefully recover.
			 */
			dwc2_release_channel(hsotg, chan, qtd,
					     chan->halt_status);
		वापस;
	पूर्ण

	hcपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HCINTMSK(chnum));

	अगर (chan->hcपूर्णांक & HCINTMSK_XFERCOMPL) अणु
		/*
		 * Toकरो: This is here because of a possible hardware bug. Spec
		 * says that on SPLIT-ISOC OUT transfers in DMA mode that a HALT
		 * पूर्णांकerrupt w/ACK bit set should occur, but I only see the
		 * XFERCOMP bit, even with it masked out. This is a workaround
		 * क्रम that behavior. Should fix this when hardware is fixed.
		 */
		अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC && !chan->ep_is_in)
			dwc2_hc_ack_पूर्णांकr(hsotg, chan, chnum, qtd);
		dwc2_hc_xfercomp_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर (chan->hcपूर्णांक & HCINTMSK_STALL) अणु
		dwc2_hc_stall_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर ((chan->hcपूर्णांक & HCINTMSK_XACTERR) &&
		   !hsotg->params.dma_desc_enable) अणु
		अगर (out_nak_enh) अणु
			अगर (chan->hcपूर्णांक &
			    (HCINTMSK_NYET | HCINTMSK_NAK | HCINTMSK_ACK)) अणु
				dev_vdbg(hsotg->dev,
					 "XactErr with NYET/NAK/ACK\n");
				qtd->error_count = 0;
			पूर्ण अन्यथा अणु
				dev_vdbg(hsotg->dev,
					 "XactErr without NYET/NAK/ACK\n");
			पूर्ण
		पूर्ण

		/*
		 * Must handle xacterr beक्रमe nak or ack. Could get a xacterr
		 * at the same समय as either of these on a BULK/CONTROL OUT
		 * that started with a PING. The xacterr takes precedence.
		 */
		dwc2_hc_xacterr_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर ((chan->hcपूर्णांक & HCINTMSK_XCS_XACT) &&
		   hsotg->params.dma_desc_enable) अणु
		dwc2_hc_xacterr_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर ((chan->hcपूर्णांक & HCINTMSK_AHBERR) &&
		   hsotg->params.dma_desc_enable) अणु
		dwc2_hc_ahberr_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर (chan->hcपूर्णांक & HCINTMSK_BBLERR) अणु
		dwc2_hc_babble_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर (chan->hcपूर्णांक & HCINTMSK_FRMOVRUN) अणु
		dwc2_hc_frmovrun_पूर्णांकr(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अगर (!out_nak_enh) अणु
		अगर (chan->hcपूर्णांक & HCINTMSK_NYET) अणु
			/*
			 * Must handle nyet beक्रमe nak or ack. Could get a nyet
			 * at the same समय as either of those on a BULK/CONTROL
			 * OUT that started with a PING. The nyet takes
			 * precedence.
			 */
			dwc2_hc_nyet_पूर्णांकr(hsotg, chan, chnum, qtd);
		पूर्ण अन्यथा अगर ((chan->hcपूर्णांक & HCINTMSK_NAK) &&
			   !(hcपूर्णांकmsk & HCINTMSK_NAK)) अणु
			/*
			 * If nak is not masked, it's because a non-split IN
			 * transfer is in an error state. In that हाल, the nak
			 * is handled by the nak पूर्णांकerrupt handler, not here.
			 * Handle nak here क्रम BULK/CONTROL OUT transfers, which
			 * halt on a NAK to allow शुरुआतing the buffer poपूर्णांकer.
			 */
			dwc2_hc_nak_पूर्णांकr(hsotg, chan, chnum, qtd);
		पूर्ण अन्यथा अगर ((chan->hcपूर्णांक & HCINTMSK_ACK) &&
			   !(hcपूर्णांकmsk & HCINTMSK_ACK)) अणु
			/*
			 * If ack is not masked, it's because a non-split IN
			 * transfer is in an error state. In that हाल, the ack
			 * is handled by the ack पूर्णांकerrupt handler, not here.
			 * Handle ack here क्रम split transfers. Start splits
			 * halt on ACK.
			 */
			dwc2_hc_ack_पूर्णांकr(hsotg, chan, chnum, qtd);
		पूर्ण अन्यथा अणु
			अगर (chan->ep_type == USB_ENDPOINT_XFER_INT ||
			    chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
				/*
				 * A periodic transfer halted with no other
				 * channel पूर्णांकerrupts set. Assume it was halted
				 * by the core because it could not be completed
				 * in its scheduled (micro)frame.
				 */
				dev_dbg(hsotg->dev,
					"%s: Halt channel %d (assume incomplete periodic transfer)\n",
					__func__, chnum);
				dwc2_halt_channel(hsotg, chan, qtd,
					DWC2_HC_XFER_PERIODIC_INCOMPLETE);
			पूर्ण अन्यथा अणु
				dev_err(hsotg->dev,
					"%s: Channel %d - ChHltd set, but reason is unknown\n",
					__func__, chnum);
				dev_err(hsotg->dev,
					"hcint 0x%08x, intsts 0x%08x\n",
					chan->hcपूर्णांक,
					dwc2_पढ़ोl(hsotg, GINTSTS));
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(hsotg->dev,
			 "NYET/NAK/ACK/other in non-error case, 0x%08x\n",
			 chan->hcपूर्णांक);
error:
		/* Failthrough: use 3-strikes rule */
		qtd->error_count++;
		dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb,
					  qtd, DWC2_HC_XFER_XACT_ERR);
		/*
		 * We can get here after a completed transaction
		 * (urb->actual_length >= urb->length) which was not reported
		 * as completed. If that is the हाल, and we करो not पात
		 * the transfer, a transfer of size 0 will be enqueued
		 * subsequently. If urb->actual_length is not DMA-aligned,
		 * the buffer will then poपूर्णांक to an unaligned address, and
		 * the resulting behavior is undefined. Bail out in that
		 * situation.
		 */
		अगर (qtd->urb->actual_length >= qtd->urb->length)
			qtd->error_count = 3;
		dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_XACT_ERR);
	पूर्ण
पूर्ण

/*
 * Handles a host channel Channel Halted पूर्णांकerrupt
 *
 * In slave mode, this handler is called only when the driver specअगरically
 * requests a halt. This occurs during handling other host channel पूर्णांकerrupts
 * (e.g. nak, xacterr, stall, nyet, etc.).
 *
 * In DMA mode, this is the पूर्णांकerrupt that occurs when the core has finished
 * processing a transfer on a channel. Other host channel पूर्णांकerrupts (except
 * ahberr) are disabled in DMA mode.
 */
अटल व्योम dwc2_hc_chhltd_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg,
				काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				काष्ठा dwc2_qtd *qtd)
अणु
	अगर (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: Channel Halted--\n",
			 chnum);

	अगर (hsotg->params.host_dma) अणु
		dwc2_hc_chhltd_पूर्णांकr_dma(hsotg, chan, chnum, qtd);
	पूर्ण अन्यथा अणु
		अगर (!dwc2_halt_status_ok(hsotg, chan, chnum, qtd))
			वापस;
		dwc2_release_channel(hsotg, chan, qtd, chan->halt_status);
	पूर्ण
पूर्ण

/*
 * Check अगर the given qtd is still the top of the list (and thus valid).
 *
 * If dwc2_hcd_qtd_unlink_and_मुक्त() has been called since we grabbed
 * the qtd from the top of the list, this will वापस false (otherwise true).
 */
अटल bool dwc2_check_qtd_still_ok(काष्ठा dwc2_qtd *qtd, काष्ठा dwc2_qh *qh)
अणु
	काष्ठा dwc2_qtd *cur_head;

	अगर (!qh)
		वापस false;

	cur_head = list_first_entry(&qh->qtd_list, काष्ठा dwc2_qtd,
				    qtd_list_entry);
	वापस (cur_head == qtd);
पूर्ण

/* Handles पूर्णांकerrupt क्रम a specअगरic Host Channel */
अटल व्योम dwc2_hc_n_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg, पूर्णांक chnum)
अणु
	काष्ठा dwc2_qtd *qtd;
	काष्ठा dwc2_host_chan *chan;
	u32 hcपूर्णांक, hcपूर्णांकmsk;

	chan = hsotg->hc_ptr_array[chnum];

	hcपूर्णांक = dwc2_पढ़ोl(hsotg, HCINT(chnum));
	hcपूर्णांकmsk = dwc2_पढ़ोl(hsotg, HCINTMSK(chnum));
	अगर (!chan) अणु
		dev_err(hsotg->dev, "## hc_ptr_array for channel is NULL ##\n");
		dwc2_ग_लिखोl(hsotg, hcपूर्णांक, HCINT(chnum));
		वापस;
	पूर्ण

	अगर (dbg_hc(chan)) अणु
		dev_vdbg(hsotg->dev, "--Host Channel Interrupt--, Channel %d\n",
			 chnum);
		dev_vdbg(hsotg->dev,
			 "  hcint 0x%08x, hcintmsk 0x%08x, hcint&hcintmsk 0x%08x\n",
			 hcपूर्णांक, hcपूर्णांकmsk, hcपूर्णांक & hcपूर्णांकmsk);
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hcपूर्णांक, HCINT(chnum));

	/*
	 * If we got an पूर्णांकerrupt after someone called
	 * dwc2_hcd_endpoपूर्णांक_disable() we करोn't want to crash below
	 */
	अगर (!chan->qh) अणु
		dev_warn(hsotg->dev, "Interrupt on disabled channel\n");
		वापस;
	पूर्ण

	chan->hcपूर्णांक = hcपूर्णांक;
	hcपूर्णांक &= hcपूर्णांकmsk;

	/*
	 * If the channel was halted due to a dequeue, the qtd list might
	 * be empty or at least the first entry will not be the active qtd.
	 * In this हाल, take a लघुcut and just release the channel.
	 */
	अगर (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE) अणु
		/*
		 * If the channel was halted, this should be the only
		 * पूर्णांकerrupt unmasked
		 */
		WARN_ON(hcपूर्णांक != HCINTMSK_CHHLTD);
		अगर (hsotg->params.dma_desc_enable)
			dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
						    chan->halt_status);
		अन्यथा
			dwc2_release_channel(hsotg, chan, शून्य,
					     chan->halt_status);
		वापस;
	पूर्ण

	अगर (list_empty(&chan->qh->qtd_list)) अणु
		/*
		 * TODO: Will this ever happen with the
		 * DWC2_HC_XFER_URB_DEQUEUE handling above?
		 */
		dev_dbg(hsotg->dev, "## no QTD queued for channel %d ##\n",
			chnum);
		dev_dbg(hsotg->dev,
			"  hcint 0x%08x, hcintmsk 0x%08x, hcint&hcintmsk 0x%08x\n",
			chan->hcपूर्णांक, hcपूर्णांकmsk, hcपूर्णांक);
		chan->halt_status = DWC2_HC_XFER_NO_HALT_STATUS;
		disable_hc_पूर्णांक(hsotg, chnum, HCINTMSK_CHHLTD);
		chan->hcपूर्णांक = 0;
		वापस;
	पूर्ण

	qtd = list_first_entry(&chan->qh->qtd_list, काष्ठा dwc2_qtd,
			       qtd_list_entry);

	अगर (!hsotg->params.host_dma) अणु
		अगर ((hcपूर्णांक & HCINTMSK_CHHLTD) && hcपूर्णांक != HCINTMSK_CHHLTD)
			hcपूर्णांक &= ~HCINTMSK_CHHLTD;
	पूर्ण

	अगर (hcपूर्णांक & HCINTMSK_XFERCOMPL) अणु
		dwc2_hc_xfercomp_पूर्णांकr(hsotg, chan, chnum, qtd);
		/*
		 * If NYET occurred at same समय as Xfer Complete, the NYET is
		 * handled by the Xfer Complete पूर्णांकerrupt handler. Don't want
		 * to call the NYET पूर्णांकerrupt handler in this हाल.
		 */
		hcपूर्णांक &= ~HCINTMSK_NYET;
	पूर्ण

	अगर (hcपूर्णांक & HCINTMSK_CHHLTD) अणु
		dwc2_hc_chhltd_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_AHBERR) अणु
		dwc2_hc_ahberr_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_STALL) अणु
		dwc2_hc_stall_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_NAK) अणु
		dwc2_hc_nak_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_ACK) अणु
		dwc2_hc_ack_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_NYET) अणु
		dwc2_hc_nyet_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_XACTERR) अणु
		dwc2_hc_xacterr_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_BBLERR) अणु
		dwc2_hc_babble_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_FRMOVRUN) अणु
		dwc2_hc_frmovrun_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण
	अगर (hcपूर्णांक & HCINTMSK_DATATGLERR) अणु
		dwc2_hc_datatglerr_पूर्णांकr(hsotg, chan, chnum, qtd);
		अगर (!dwc2_check_qtd_still_ok(qtd, chan->qh))
			जाओ निकास;
	पूर्ण

निकास:
	chan->hcपूर्णांक = 0;
पूर्ण

/*
 * This पूर्णांकerrupt indicates that one or more host channels has a pending
 * पूर्णांकerrupt. There are multiple conditions that can cause each host channel
 * पूर्णांकerrupt. This function determines which conditions have occurred क्रम each
 * host channel पूर्णांकerrupt and handles them appropriately.
 */
अटल व्योम dwc2_hc_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 haपूर्णांक;
	पूर्णांक i;
	काष्ठा dwc2_host_chan *chan, *chan_पंचांगp;

	haपूर्णांक = dwc2_पढ़ोl(hsotg, HAINT);
	अगर (dbg_perio()) अणु
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

		dev_vdbg(hsotg->dev, "HAINT=%08x\n", haपूर्णांक);
	पूर्ण

	/*
	 * According to USB 2.0 spec section 11.18.8, a host must
	 * issue complete-split transactions in a microframe क्रम a
	 * set of full-/low-speed endpoपूर्णांकs in the same relative
	 * order as the start-splits were issued in a microframe क्रम.
	 */
	list_क्रम_each_entry_safe(chan, chan_पंचांगp, &hsotg->split_order,
				 split_order_list_entry) अणु
		पूर्णांक hc_num = chan->hc_num;

		अगर (haपूर्णांक & (1 << hc_num)) अणु
			dwc2_hc_n_पूर्णांकr(hsotg, hc_num);
			haपूर्णांक &= ~(1 << hc_num);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < hsotg->params.host_channels; i++) अणु
		अगर (haपूर्णांक & (1 << i))
			dwc2_hc_n_पूर्णांकr(hsotg, i);
	पूर्ण
पूर्ण

/* This function handles पूर्णांकerrupts क्रम the HCD */
irqवापस_t dwc2_handle_hcd_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts, dbg_gपूर्णांकsts;
	irqवापस_t retval = IRQ_NONE;

	अगर (!dwc2_is_controller_alive(hsotg)) अणु
		dev_warn(hsotg->dev, "Controller is dead\n");
		वापस retval;
	पूर्ण

	spin_lock(&hsotg->lock);

	/* Check अगर HOST Mode */
	अगर (dwc2_is_host_mode(hsotg)) अणु
		gपूर्णांकsts = dwc2_पढ़ो_core_पूर्णांकr(hsotg);
		अगर (!gपूर्णांकsts) अणु
			spin_unlock(&hsotg->lock);
			वापस retval;
		पूर्ण

		retval = IRQ_HANDLED;

		dbg_gपूर्णांकsts = gपूर्णांकsts;
#अगर_अघोषित DEBUG_SOF
		dbg_gपूर्णांकsts &= ~GINTSTS_SOF;
#पूर्ण_अगर
		अगर (!dbg_perio())
			dbg_gपूर्णांकsts &= ~(GINTSTS_HCHINT | GINTSTS_RXFLVL |
					 GINTSTS_PTXFEMP);

		/* Only prपूर्णांक अगर there are any non-suppressed पूर्णांकerrupts left */
		अगर (dbg_gपूर्णांकsts)
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD Interrupt Detected gintsts&gintmsk=0x%08x\n",
				 gपूर्णांकsts);

		अगर (gपूर्णांकsts & GINTSTS_SOF)
			dwc2_sof_पूर्णांकr(hsotg);
		अगर (gपूर्णांकsts & GINTSTS_RXFLVL)
			dwc2_rx_fअगरo_level_पूर्णांकr(hsotg);
		अगर (gपूर्णांकsts & GINTSTS_NPTXFEMP)
			dwc2_np_tx_fअगरo_empty_पूर्णांकr(hsotg);
		अगर (gपूर्णांकsts & GINTSTS_PRTINT)
			dwc2_port_पूर्णांकr(hsotg);
		अगर (gपूर्णांकsts & GINTSTS_HCHINT)
			dwc2_hc_पूर्णांकr(hsotg);
		अगर (gपूर्णांकsts & GINTSTS_PTXFEMP)
			dwc2_perio_tx_fअगरo_empty_पूर्णांकr(hsotg);

		अगर (dbg_gपूर्णांकsts) अणु
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD Finished Servicing Interrupts\n");
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD gintsts=0x%08x gintmsk=0x%08x\n",
				 dwc2_पढ़ोl(hsotg, GINTSTS),
				 dwc2_पढ़ोl(hsotg, GINTMSK));
		पूर्ण
	पूर्ण

	spin_unlock(&hsotg->lock);

	वापस retval;
पूर्ण
