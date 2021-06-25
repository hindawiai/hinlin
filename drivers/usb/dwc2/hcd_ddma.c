<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * hcd_ddma.c - DesignWare HS OTG Controller descriptor DMA routines
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
 * This file contains the Descriptor DMA implementation क्रम Host mode
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

अटल u16 dwc2_frame_list_idx(u16 frame)
अणु
	वापस frame & (FRLISTEN_64_SIZE - 1);
पूर्ण

अटल u16 dwc2_desclist_idx_inc(u16 idx, u16 inc, u8 speed)
अणु
	वापस (idx + inc) &
		((speed == USB_SPEED_HIGH ? MAX_DMA_DESC_NUM_HS_ISOC :
		  MAX_DMA_DESC_NUM_GENERIC) - 1);
पूर्ण

अटल u16 dwc2_desclist_idx_dec(u16 idx, u16 inc, u8 speed)
अणु
	वापस (idx - inc) &
		((speed == USB_SPEED_HIGH ? MAX_DMA_DESC_NUM_HS_ISOC :
		  MAX_DMA_DESC_NUM_GENERIC) - 1);
पूर्ण

अटल u16 dwc2_max_desc_num(काष्ठा dwc2_qh *qh)
अणु
	वापस (qh->ep_type == USB_ENDPOINT_XFER_ISOC &&
		qh->dev_speed == USB_SPEED_HIGH) ?
		MAX_DMA_DESC_NUM_HS_ISOC : MAX_DMA_DESC_NUM_GENERIC;
पूर्ण

अटल u16 dwc2_frame_incr_val(काष्ठा dwc2_qh *qh)
अणु
	वापस qh->dev_speed == USB_SPEED_HIGH ?
	       (qh->host_पूर्णांकerval + 8 - 1) / 8 : qh->host_पूर्णांकerval;
पूर्ण

अटल पूर्णांक dwc2_desc_list_alloc(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
				gfp_t flags)
अणु
	काष्ठा kmem_cache *desc_cache;

	अगर (qh->ep_type == USB_ENDPOINT_XFER_ISOC &&
	    qh->dev_speed == USB_SPEED_HIGH)
		desc_cache = hsotg->desc_hsisoc_cache;
	अन्यथा
		desc_cache = hsotg->desc_gen_cache;

	qh->desc_list_sz = माप(काष्ठा dwc2_dma_desc) *
						dwc2_max_desc_num(qh);

	qh->desc_list = kmem_cache_zalloc(desc_cache, flags | GFP_DMA);
	अगर (!qh->desc_list)
		वापस -ENOMEM;

	qh->desc_list_dma = dma_map_single(hsotg->dev, qh->desc_list,
					   qh->desc_list_sz,
					   DMA_TO_DEVICE);

	qh->n_bytes = kसुस्मृति(dwc2_max_desc_num(qh), माप(u32), flags);
	अगर (!qh->n_bytes) अणु
		dma_unmap_single(hsotg->dev, qh->desc_list_dma,
				 qh->desc_list_sz,
				 DMA_FROM_DEVICE);
		kmem_cache_मुक्त(desc_cache, qh->desc_list);
		qh->desc_list = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc2_desc_list_मुक्त(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	काष्ठा kmem_cache *desc_cache;

	अगर (qh->ep_type == USB_ENDPOINT_XFER_ISOC &&
	    qh->dev_speed == USB_SPEED_HIGH)
		desc_cache = hsotg->desc_hsisoc_cache;
	अन्यथा
		desc_cache = hsotg->desc_gen_cache;

	अगर (qh->desc_list) अणु
		dma_unmap_single(hsotg->dev, qh->desc_list_dma,
				 qh->desc_list_sz, DMA_FROM_DEVICE);
		kmem_cache_मुक्त(desc_cache, qh->desc_list);
		qh->desc_list = शून्य;
	पूर्ण

	kमुक्त(qh->n_bytes);
	qh->n_bytes = शून्य;
पूर्ण

अटल पूर्णांक dwc2_frame_list_alloc(काष्ठा dwc2_hsotg *hsotg, gfp_t mem_flags)
अणु
	अगर (hsotg->frame_list)
		वापस 0;

	hsotg->frame_list_sz = 4 * FRLISTEN_64_SIZE;
	hsotg->frame_list = kzalloc(hsotg->frame_list_sz, GFP_ATOMIC | GFP_DMA);
	अगर (!hsotg->frame_list)
		वापस -ENOMEM;

	hsotg->frame_list_dma = dma_map_single(hsotg->dev, hsotg->frame_list,
					       hsotg->frame_list_sz,
					       DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल व्योम dwc2_frame_list_मुक्त(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	अगर (!hsotg->frame_list) अणु
		spin_unlock_irqrestore(&hsotg->lock, flags);
		वापस;
	पूर्ण

	dma_unmap_single(hsotg->dev, hsotg->frame_list_dma,
			 hsotg->frame_list_sz, DMA_FROM_DEVICE);

	kमुक्त(hsotg->frame_list);
	hsotg->frame_list = शून्य;

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

अटल व्योम dwc2_per_sched_enable(काष्ठा dwc2_hsotg *hsotg, u32 fr_list_en)
अणु
	u32 hcfg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	hcfg = dwc2_पढ़ोl(hsotg, HCFG);
	अगर (hcfg & HCFG_PERSCHEDENA) अणु
		/* alपढ़ोy enabled */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		वापस;
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hsotg->frame_list_dma, HFLBADDR);

	hcfg &= ~HCFG_FRLISTEN_MASK;
	hcfg |= fr_list_en | HCFG_PERSCHEDENA;
	dev_vdbg(hsotg->dev, "Enabling Periodic schedule\n");
	dwc2_ग_लिखोl(hsotg, hcfg, HCFG);

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

अटल व्योम dwc2_per_sched_disable(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hcfg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	hcfg = dwc2_पढ़ोl(hsotg, HCFG);
	अगर (!(hcfg & HCFG_PERSCHEDENA)) अणु
		/* alपढ़ोy disabled */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		वापस;
	पूर्ण

	hcfg &= ~HCFG_PERSCHEDENA;
	dev_vdbg(hsotg->dev, "Disabling Periodic schedule\n");
	dwc2_ग_लिखोl(hsotg, hcfg, HCFG);

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

/*
 * Activates/Deactivates FrameList entries क्रम the channel based on endpoपूर्णांक
 * servicing period
 */
अटल व्योम dwc2_update_frame_list(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
				   पूर्णांक enable)
अणु
	काष्ठा dwc2_host_chan *chan;
	u16 i, j, inc;

	अगर (!hsotg) अणु
		pr_err("hsotg = %p\n", hsotg);
		वापस;
	पूर्ण

	अगर (!qh->channel) अणु
		dev_err(hsotg->dev, "qh->channel = %p\n", qh->channel);
		वापस;
	पूर्ण

	अगर (!hsotg->frame_list) अणु
		dev_err(hsotg->dev, "hsotg->frame_list = %p\n",
			hsotg->frame_list);
		वापस;
	पूर्ण

	chan = qh->channel;
	inc = dwc2_frame_incr_val(qh);
	अगर (qh->ep_type == USB_ENDPOINT_XFER_ISOC)
		i = dwc2_frame_list_idx(qh->next_active_frame);
	अन्यथा
		i = 0;

	j = i;
	करो अणु
		अगर (enable)
			hsotg->frame_list[j] |= 1 << chan->hc_num;
		अन्यथा
			hsotg->frame_list[j] &= ~(1 << chan->hc_num);
		j = (j + inc) & (FRLISTEN_64_SIZE - 1);
	पूर्ण जबतक (j != i);

	/*
	 * Sync frame list since controller will access it अगर periodic
	 * channel is currently enabled.
	 */
	dma_sync_single_क्रम_device(hsotg->dev,
				   hsotg->frame_list_dma,
				   hsotg->frame_list_sz,
				   DMA_TO_DEVICE);

	अगर (!enable)
		वापस;

	chan->schinfo = 0;
	अगर (chan->speed == USB_SPEED_HIGH && qh->host_पूर्णांकerval) अणु
		j = 1;
		/* TODO - check this */
		inc = (8 + qh->host_पूर्णांकerval - 1) / qh->host_पूर्णांकerval;
		क्रम (i = 0; i < inc; i++) अणु
			chan->schinfo |= j;
			j = j << qh->host_पूर्णांकerval;
		पूर्ण
	पूर्ण अन्यथा अणु
		chan->schinfo = 0xff;
	पूर्ण
पूर्ण

अटल व्योम dwc2_release_channel_ddma(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_qh *qh)
अणु
	काष्ठा dwc2_host_chan *chan = qh->channel;

	अगर (dwc2_qh_is_non_per(qh)) अणु
		अगर (hsotg->params.uframe_sched)
			hsotg->available_host_channels++;
		अन्यथा
			hsotg->non_periodic_channels--;
	पूर्ण अन्यथा अणु
		dwc2_update_frame_list(hsotg, qh, 0);
		hsotg->available_host_channels++;
	पूर्ण

	/*
	 * The condition is added to prevent द्विगुन cleanup try in हाल of
	 * device disconnect. See channel cleanup in dwc2_hcd_disconnect().
	 */
	अगर (chan->qh) अणु
		अगर (!list_empty(&chan->hc_list_entry))
			list_del(&chan->hc_list_entry);
		dwc2_hc_cleanup(hsotg, chan);
		list_add_tail(&chan->hc_list_entry, &hsotg->मुक्त_hc_list);
		chan->qh = शून्य;
	पूर्ण

	qh->channel = शून्य;
	qh->ntd = 0;

	अगर (qh->desc_list)
		स_रखो(qh->desc_list, 0, माप(काष्ठा dwc2_dma_desc) *
		       dwc2_max_desc_num(qh));
पूर्ण

/**
 * dwc2_hcd_qh_init_ddma() - Initializes a QH काष्ठाure's Descriptor DMA
 * related members
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    The QH to init
 * @mem_flags: Indicates the type of memory allocation
 *
 * Return: 0 अगर successful, negative error code otherwise
 *
 * Allocates memory क्रम the descriptor list. For the first periodic QH,
 * allocates memory क्रम the FrameList and enables periodic scheduling.
 */
पूर्णांक dwc2_hcd_qh_init_ddma(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			  gfp_t mem_flags)
अणु
	पूर्णांक retval;

	अगर (qh->करो_split) अणु
		dev_err(hsotg->dev,
			"SPLIT Transfers are not supported in Descriptor DMA mode.\n");
		retval = -EINVAL;
		जाओ err0;
	पूर्ण

	retval = dwc2_desc_list_alloc(hsotg, qh, mem_flags);
	अगर (retval)
		जाओ err0;

	अगर (qh->ep_type == USB_ENDPOINT_XFER_ISOC ||
	    qh->ep_type == USB_ENDPOINT_XFER_INT) अणु
		अगर (!hsotg->frame_list) अणु
			retval = dwc2_frame_list_alloc(hsotg, mem_flags);
			अगर (retval)
				जाओ err1;
			/* Enable periodic schedule on first periodic QH */
			dwc2_per_sched_enable(hsotg, HCFG_FRLISTEN_64);
		पूर्ण
	पूर्ण

	qh->ntd = 0;
	वापस 0;

err1:
	dwc2_desc_list_मुक्त(hsotg, qh);
err0:
	वापस retval;
पूर्ण

/**
 * dwc2_hcd_qh_मुक्त_ddma() - Frees a QH काष्ठाure's Descriptor DMA related
 * members
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    The QH to मुक्त
 *
 * Frees descriptor list memory associated with the QH. If QH is periodic and
 * the last, मुक्तs FrameList memory and disables periodic scheduling.
 */
व्योम dwc2_hcd_qh_मुक्त_ddma(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	अचिन्हित दीर्घ flags;

	dwc2_desc_list_मुक्त(hsotg, qh);

	/*
	 * Channel still asचिन्हित due to some reasons.
	 * Seen on Isoc URB dequeue. Channel halted but no subsequent
	 * ChHalted पूर्णांकerrupt to release the channel. Afterwards
	 * when it comes here from endpoपूर्णांक disable routine
	 * channel reमुख्यs asचिन्हित.
	 */
	spin_lock_irqsave(&hsotg->lock, flags);
	अगर (qh->channel)
		dwc2_release_channel_ddma(hsotg, qh);
	spin_unlock_irqrestore(&hsotg->lock, flags);

	अगर ((qh->ep_type == USB_ENDPOINT_XFER_ISOC ||
	     qh->ep_type == USB_ENDPOINT_XFER_INT) &&
	    (hsotg->params.uframe_sched ||
	     !hsotg->periodic_channels) && hsotg->frame_list) अणु
		dwc2_per_sched_disable(hsotg);
		dwc2_frame_list_मुक्त(hsotg);
	पूर्ण
पूर्ण

अटल u8 dwc2_frame_to_desc_idx(काष्ठा dwc2_qh *qh, u16 frame_idx)
अणु
	अगर (qh->dev_speed == USB_SPEED_HIGH)
		/* Descriptor set (8 descriptors) index which is 8-aligned */
		वापस (frame_idx & ((MAX_DMA_DESC_NUM_HS_ISOC / 8) - 1)) * 8;
	अन्यथा
		वापस frame_idx & (MAX_DMA_DESC_NUM_GENERIC - 1);
पूर्ण

/*
 * Determine starting frame क्रम Isochronous transfer.
 * Few frames skipped to prevent race condition with HC.
 */
अटल u16 dwc2_calc_starting_frame(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh, u16 *skip_frames)
अणु
	u16 frame;

	hsotg->frame_number = dwc2_hcd_get_frame_number(hsotg);

	/*
	 * next_active_frame is always frame number (not uFrame) both in FS
	 * and HS!
	 */

	/*
	 * skip_frames is used to limit activated descriptors number
	 * to aव्योम the situation when HC services the last activated
	 * descriptor firstly.
	 * Example क्रम FS:
	 * Current frame is 1, scheduled frame is 3. Since HC always fetches
	 * the descriptor corresponding to curr_frame+1, the descriptor
	 * corresponding to frame 2 will be fetched. If the number of
	 * descriptors is max=64 (or greather) the list will be fully programmed
	 * with Active descriptors and it is possible हाल (rare) that the
	 * latest descriptor(considering rollback) corresponding to frame 2 will
	 * be serviced first. HS हाल is more probable because, in fact, up to
	 * 11 uframes (16 in the code) may be skipped.
	 */
	अगर (qh->dev_speed == USB_SPEED_HIGH) अणु
		/*
		 * Consider uframe counter also, to start xfer asap. If half of
		 * the frame elapsed skip 2 frames otherwise just 1 frame.
		 * Starting descriptor index must be 8-aligned, so अगर the
		 * current frame is near to complete the next one is skipped as
		 * well.
		 */
		अगर (dwc2_micro_frame_num(hsotg->frame_number) >= 5) अणु
			*skip_frames = 2 * 8;
			frame = dwc2_frame_num_inc(hsotg->frame_number,
						   *skip_frames);
		पूर्ण अन्यथा अणु
			*skip_frames = 1 * 8;
			frame = dwc2_frame_num_inc(hsotg->frame_number,
						   *skip_frames);
		पूर्ण

		frame = dwc2_full_frame_num(frame);
	पूर्ण अन्यथा अणु
		/*
		 * Two frames are skipped क्रम FS - the current and the next.
		 * But क्रम descriptor programming, 1 frame (descriptor) is
		 * enough, see example above.
		 */
		*skip_frames = 1;
		frame = dwc2_frame_num_inc(hsotg->frame_number, 2);
	पूर्ण

	वापस frame;
पूर्ण

/*
 * Calculate initial descriptor index क्रम isochronous transfer based on
 * scheduled frame
 */
अटल u16 dwc2_recalc_initial_desc_idx(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_qh *qh)
अणु
	u16 frame, fr_idx, fr_idx_पंचांगp, skip_frames;

	/*
	 * With current ISOC processing algorithm the channel is being released
	 * when no more QTDs in the list (qh->ntd == 0). Thus this function is
	 * called only when qh->ntd == 0 and qh->channel == 0.
	 *
	 * So qh->channel != शून्य branch is not used and just not हटाओd from
	 * the source file. It is required क्रम another possible approach which
	 * is, करो not disable and release the channel when ISOC session
	 * completed, just move QH to inactive schedule until new QTD arrives.
	 * On new QTD, the QH moved back to 'ready' schedule, starting frame and
	 * thereक्रमe starting desc_index are recalculated. In this हाल channel
	 * is released only on ep_disable.
	 */

	/*
	 * Calculate starting descriptor index. For INTERRUPT endpoपूर्णांक it is
	 * always 0.
	 */
	अगर (qh->channel) अणु
		frame = dwc2_calc_starting_frame(hsotg, qh, &skip_frames);
		/*
		 * Calculate initial descriptor index based on FrameList current
		 * biपंचांगap and servicing period
		 */
		fr_idx_पंचांगp = dwc2_frame_list_idx(frame);
		fr_idx = (FRLISTEN_64_SIZE +
			  dwc2_frame_list_idx(qh->next_active_frame) -
			  fr_idx_पंचांगp) % dwc2_frame_incr_val(qh);
		fr_idx = (fr_idx + fr_idx_पंचांगp) % FRLISTEN_64_SIZE;
	पूर्ण अन्यथा अणु
		qh->next_active_frame = dwc2_calc_starting_frame(hsotg, qh,
							   &skip_frames);
		fr_idx = dwc2_frame_list_idx(qh->next_active_frame);
	पूर्ण

	qh->td_first = qh->td_last = dwc2_frame_to_desc_idx(qh, fr_idx);

	वापस skip_frames;
पूर्ण

#घोषणा ISOC_URB_GIVEBACK_ASAP

#घोषणा MAX_ISOC_XFER_SIZE_FS	1023
#घोषणा MAX_ISOC_XFER_SIZE_HS	3072
#घोषणा DESCNUM_THRESHOLD	4

अटल व्योम dwc2_fill_host_isoc_dma_desc(काष्ठा dwc2_hsotg *hsotg,
					 काष्ठा dwc2_qtd *qtd,
					 काष्ठा dwc2_qh *qh, u32 max_xfer_size,
					 u16 idx)
अणु
	काष्ठा dwc2_dma_desc *dma_desc = &qh->desc_list[idx];
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;

	स_रखो(dma_desc, 0, माप(*dma_desc));
	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index_last];

	अगर (frame_desc->length > max_xfer_size)
		qh->n_bytes[idx] = max_xfer_size;
	अन्यथा
		qh->n_bytes[idx] = frame_desc->length;

	dma_desc->buf = (u32)(qtd->urb->dma + frame_desc->offset);
	dma_desc->status = qh->n_bytes[idx] << HOST_DMA_ISOC_NBYTES_SHIFT &
			   HOST_DMA_ISOC_NBYTES_MASK;

	/* Set active bit */
	dma_desc->status |= HOST_DMA_A;

	qh->ntd++;
	qtd->isoc_frame_index_last++;

#अगर_घोषित ISOC_URB_GIVEBACK_ASAP
	/* Set IOC क्रम each descriptor corresponding to last frame of URB */
	अगर (qtd->isoc_frame_index_last == qtd->urb->packet_count)
		dma_desc->status |= HOST_DMA_IOC;
#पूर्ण_अगर

	dma_sync_single_क्रम_device(hsotg->dev,
				   qh->desc_list_dma +
			(idx * माप(काष्ठा dwc2_dma_desc)),
			माप(काष्ठा dwc2_dma_desc),
			DMA_TO_DEVICE);
पूर्ण

अटल व्योम dwc2_init_isoc_dma_desc(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh, u16 skip_frames)
अणु
	काष्ठा dwc2_qtd *qtd;
	u32 max_xfer_size;
	u16 idx, inc, n_desc = 0, ntd_max = 0;
	u16 cur_idx;
	u16 next_idx;

	idx = qh->td_last;
	inc = qh->host_पूर्णांकerval;
	hsotg->frame_number = dwc2_hcd_get_frame_number(hsotg);
	cur_idx = dwc2_frame_list_idx(hsotg->frame_number);
	next_idx = dwc2_desclist_idx_inc(qh->td_last, inc, qh->dev_speed);

	/*
	 * Ensure current frame number didn't overstep last scheduled
	 * descriptor. If it happens, the only way to recover is to move
	 * qh->td_last to current frame number + 1.
	 * So that next isoc descriptor will be scheduled on frame number + 1
	 * and not on a past frame.
	 */
	अगर (dwc2_frame_idx_num_gt(cur_idx, next_idx) || (cur_idx == next_idx)) अणु
		अगर (inc < 32) अणु
			dev_vdbg(hsotg->dev,
				 "current frame number overstep last descriptor\n");
			qh->td_last = dwc2_desclist_idx_inc(cur_idx, inc,
							    qh->dev_speed);
			idx = qh->td_last;
		पूर्ण
	पूर्ण

	अगर (qh->host_पूर्णांकerval) अणु
		ntd_max = (dwc2_max_desc_num(qh) + qh->host_पूर्णांकerval - 1) /
				qh->host_पूर्णांकerval;
		अगर (skip_frames && !qh->channel)
			ntd_max -= skip_frames / qh->host_पूर्णांकerval;
	पूर्ण

	max_xfer_size = qh->dev_speed == USB_SPEED_HIGH ?
			MAX_ISOC_XFER_SIZE_HS : MAX_ISOC_XFER_SIZE_FS;

	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list_entry) अणु
		अगर (qtd->in_process &&
		    qtd->isoc_frame_index_last ==
		    qtd->urb->packet_count)
			जारी;

		qtd->isoc_td_first = idx;
		जबतक (qh->ntd < ntd_max && qtd->isoc_frame_index_last <
						qtd->urb->packet_count) अणु
			dwc2_fill_host_isoc_dma_desc(hsotg, qtd, qh,
						     max_xfer_size, idx);
			idx = dwc2_desclist_idx_inc(idx, inc, qh->dev_speed);
			n_desc++;
		पूर्ण
		qtd->isoc_td_last = idx;
		qtd->in_process = 1;
	पूर्ण

	qh->td_last = idx;

#अगर_घोषित ISOC_URB_GIVEBACK_ASAP
	/* Set IOC क्रम last descriptor अगर descriptor list is full */
	अगर (qh->ntd == ntd_max) अणु
		idx = dwc2_desclist_idx_dec(qh->td_last, inc, qh->dev_speed);
		qh->desc_list[idx].status |= HOST_DMA_IOC;
		dma_sync_single_क्रम_device(hsotg->dev,
					   qh->desc_list_dma + (idx *
					   माप(काष्ठा dwc2_dma_desc)),
					   माप(काष्ठा dwc2_dma_desc),
					   DMA_TO_DEVICE);
	पूर्ण
#अन्यथा
	/*
	 * Set IOC bit only क्रम one descriptor. Always try to be ahead of HW
	 * processing, i.e. on IOC generation driver activates next descriptor
	 * but core जारीs to process descriptors following the one with IOC
	 * set.
	 */

	अगर (n_desc > DESCNUM_THRESHOLD)
		/*
		 * Move IOC "up". Required even अगर there is only one QTD
		 * in the list, because QTDs might जारी to be queued,
		 * but during the activation it was only one queued.
		 * Actually more than one QTD might be in the list अगर this
		 * function called from XferCompletion - QTDs was queued during
		 * HW processing of the previous descriptor chunk.
		 */
		idx = dwc2_desclist_idx_dec(idx, inc * ((qh->ntd + 1) / 2),
					    qh->dev_speed);
	अन्यथा
		/*
		 * Set the IOC क्रम the latest descriptor अगर either number of
		 * descriptors is not greater than threshold or no more new
		 * descriptors activated
		 */
		idx = dwc2_desclist_idx_dec(qh->td_last, inc, qh->dev_speed);

	qh->desc_list[idx].status |= HOST_DMA_IOC;
	dma_sync_single_क्रम_device(hsotg->dev,
				   qh->desc_list_dma +
				   (idx * माप(काष्ठा dwc2_dma_desc)),
				   माप(काष्ठा dwc2_dma_desc),
				   DMA_TO_DEVICE);
#पूर्ण_अगर
पूर्ण

अटल व्योम dwc2_fill_host_dma_desc(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_host_chan *chan,
				    काष्ठा dwc2_qtd *qtd, काष्ठा dwc2_qh *qh,
				    पूर्णांक n_desc)
अणु
	काष्ठा dwc2_dma_desc *dma_desc = &qh->desc_list[n_desc];
	पूर्णांक len = chan->xfer_len;

	अगर (len > HOST_DMA_NBYTES_LIMIT - (chan->max_packet - 1))
		len = HOST_DMA_NBYTES_LIMIT - (chan->max_packet - 1);

	अगर (chan->ep_is_in) अणु
		पूर्णांक num_packets;

		अगर (len > 0 && chan->max_packet)
			num_packets = (len + chan->max_packet - 1)
					/ chan->max_packet;
		अन्यथा
			/* Need 1 packet क्रम transfer length of 0 */
			num_packets = 1;

		/* Always program an पूर्णांकegral # of packets क्रम IN transfers */
		len = num_packets * chan->max_packet;
	पूर्ण

	dma_desc->status = len << HOST_DMA_NBYTES_SHIFT & HOST_DMA_NBYTES_MASK;
	qh->n_bytes[n_desc] = len;

	अगर (qh->ep_type == USB_ENDPOINT_XFER_CONTROL &&
	    qtd->control_phase == DWC2_CONTROL_SETUP)
		dma_desc->status |= HOST_DMA_SUP;

	dma_desc->buf = (u32)chan->xfer_dma;

	dma_sync_single_क्रम_device(hsotg->dev,
				   qh->desc_list_dma +
				   (n_desc * माप(काष्ठा dwc2_dma_desc)),
				   माप(काष्ठा dwc2_dma_desc),
				   DMA_TO_DEVICE);

	/*
	 * Last (or only) descriptor of IN transfer with actual size less
	 * than MaxPacket
	 */
	अगर (len > chan->xfer_len) अणु
		chan->xfer_len = 0;
	पूर्ण अन्यथा अणु
		chan->xfer_dma += len;
		chan->xfer_len -= len;
	पूर्ण
पूर्ण

अटल व्योम dwc2_init_non_isoc_dma_desc(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_qh *qh)
अणु
	काष्ठा dwc2_qtd *qtd;
	काष्ठा dwc2_host_chan *chan = qh->channel;
	पूर्णांक n_desc = 0;

	dev_vdbg(hsotg->dev, "%s(): qh=%p dma=%08lx len=%d\n", __func__, qh,
		 (अचिन्हित दीर्घ)chan->xfer_dma, chan->xfer_len);

	/*
	 * Start with chan->xfer_dma initialized in assign_and_init_hc(), then
	 * अगर SG transfer consists of multiple URBs, this poपूर्णांकer is re-asचिन्हित
	 * to the buffer of the currently processed QTD. For non-SG request
	 * there is always one QTD active.
	 */

	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list_entry) अणु
		dev_vdbg(hsotg->dev, "qtd=%p\n", qtd);

		अगर (n_desc) अणु
			/* SG request - more than 1 QTD */
			chan->xfer_dma = qtd->urb->dma +
					qtd->urb->actual_length;
			chan->xfer_len = qtd->urb->length -
					qtd->urb->actual_length;
			dev_vdbg(hsotg->dev, "buf=%08lx len=%d\n",
				 (अचिन्हित दीर्घ)chan->xfer_dma, chan->xfer_len);
		पूर्ण

		qtd->n_desc = 0;
		करो अणु
			अगर (n_desc > 1) अणु
				qh->desc_list[n_desc - 1].status |= HOST_DMA_A;
				dev_vdbg(hsotg->dev,
					 "set A bit in desc %d (%p)\n",
					 n_desc - 1,
					 &qh->desc_list[n_desc - 1]);
				dma_sync_single_क्रम_device(hsotg->dev,
							   qh->desc_list_dma +
					((n_desc - 1) *
					माप(काष्ठा dwc2_dma_desc)),
					माप(काष्ठा dwc2_dma_desc),
					DMA_TO_DEVICE);
			पूर्ण
			dwc2_fill_host_dma_desc(hsotg, chan, qtd, qh, n_desc);
			dev_vdbg(hsotg->dev,
				 "desc %d (%p) buf=%08x status=%08x\n",
				 n_desc, &qh->desc_list[n_desc],
				 qh->desc_list[n_desc].buf,
				 qh->desc_list[n_desc].status);
			qtd->n_desc++;
			n_desc++;
		पूर्ण जबतक (chan->xfer_len > 0 &&
			 n_desc != MAX_DMA_DESC_NUM_GENERIC);

		dev_vdbg(hsotg->dev, "n_desc=%d\n", n_desc);
		qtd->in_process = 1;
		अगर (qh->ep_type == USB_ENDPOINT_XFER_CONTROL)
			अवरोध;
		अगर (n_desc == MAX_DMA_DESC_NUM_GENERIC)
			अवरोध;
	पूर्ण

	अगर (n_desc) अणु
		qh->desc_list[n_desc - 1].status |=
				HOST_DMA_IOC | HOST_DMA_EOL | HOST_DMA_A;
		dev_vdbg(hsotg->dev, "set IOC/EOL/A bits in desc %d (%p)\n",
			 n_desc - 1, &qh->desc_list[n_desc - 1]);
		dma_sync_single_क्रम_device(hsotg->dev,
					   qh->desc_list_dma + (n_desc - 1) *
					   माप(काष्ठा dwc2_dma_desc),
					   माप(काष्ठा dwc2_dma_desc),
					   DMA_TO_DEVICE);
		अगर (n_desc > 1) अणु
			qh->desc_list[0].status |= HOST_DMA_A;
			dev_vdbg(hsotg->dev, "set A bit in desc 0 (%p)\n",
				 &qh->desc_list[0]);
			dma_sync_single_क्रम_device(hsotg->dev,
						   qh->desc_list_dma,
					माप(काष्ठा dwc2_dma_desc),
					DMA_TO_DEVICE);
		पूर्ण
		chan->ntd = n_desc;
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_start_xfer_ddma() - Starts a transfer in Descriptor DMA mode
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    The QH to init
 *
 * Return: 0 अगर successful, negative error code otherwise
 *
 * For Control and Bulk endpoपूर्णांकs, initializes descriptor list and starts the
 * transfer. For Interrupt and Isochronous endpoपूर्णांकs, initializes descriptor
 * list then updates FrameList, marking appropriate entries as active.
 *
 * For Isochronous endpoपूर्णांकs the starting descriptor index is calculated based
 * on the scheduled frame, but only on the first transfer descriptor within a
 * session. Then the transfer is started via enabling the channel.
 *
 * For Isochronous endpoपूर्णांकs the channel is not halted on XferComplete
 * पूर्णांकerrupt so reमुख्यs asचिन्हित to the endpoपूर्णांक(QH) until session is करोne.
 */
व्योम dwc2_hcd_start_xfer_ddma(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	/* Channel is alपढ़ोy asचिन्हित */
	काष्ठा dwc2_host_chan *chan = qh->channel;
	u16 skip_frames = 0;

	चयन (chan->ep_type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
		dwc2_init_non_isoc_dma_desc(hsotg, qh);
		dwc2_hc_start_transfer_ddma(hsotg, chan);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		dwc2_init_non_isoc_dma_desc(hsotg, qh);
		dwc2_update_frame_list(hsotg, qh, 1);
		dwc2_hc_start_transfer_ddma(hsotg, chan);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (!qh->ntd)
			skip_frames = dwc2_recalc_initial_desc_idx(hsotg, qh);
		dwc2_init_isoc_dma_desc(hsotg, qh, skip_frames);

		अगर (!chan->xfer_started) अणु
			dwc2_update_frame_list(hsotg, qh, 1);

			/*
			 * Always set to max, instead of actual size. Otherwise
			 * ntd will be changed with channel being enabled. Not
			 * recommended.
			 */
			chan->ntd = dwc2_max_desc_num(qh);

			/* Enable channel only once क्रम ISOC */
			dwc2_hc_start_transfer_ddma(hsotg, chan);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा DWC2_CMPL_DONE		1
#घोषणा DWC2_CMPL_STOP		2

अटल पूर्णांक dwc2_cmpl_host_isoc_dma_desc(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_host_chan *chan,
					काष्ठा dwc2_qtd *qtd,
					काष्ठा dwc2_qh *qh, u16 idx)
अणु
	काष्ठा dwc2_dma_desc *dma_desc;
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;
	u16 reमुख्य = 0;
	पूर्णांक rc = 0;

	अगर (!qtd->urb)
		वापस -EINVAL;

	dma_sync_single_क्रम_cpu(hsotg->dev, qh->desc_list_dma + (idx *
				माप(काष्ठा dwc2_dma_desc)),
				माप(काष्ठा dwc2_dma_desc),
				DMA_FROM_DEVICE);

	dma_desc = &qh->desc_list[idx];

	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index_last];
	dma_desc->buf = (u32)(qtd->urb->dma + frame_desc->offset);
	अगर (chan->ep_is_in)
		reमुख्य = (dma_desc->status & HOST_DMA_ISOC_NBYTES_MASK) >>
			 HOST_DMA_ISOC_NBYTES_SHIFT;

	अगर ((dma_desc->status & HOST_DMA_STS_MASK) == HOST_DMA_STS_PKTERR) अणु
		/*
		 * XactError, or unable to complete all the transactions
		 * in the scheduled micro-frame/frame, both indicated by
		 * HOST_DMA_STS_PKTERR
		 */
		qtd->urb->error_count++;
		frame_desc->actual_length = qh->n_bytes[idx] - reमुख्य;
		frame_desc->status = -EPROTO;
	पूर्ण अन्यथा अणु
		/* Success */
		frame_desc->actual_length = qh->n_bytes[idx] - reमुख्य;
		frame_desc->status = 0;
	पूर्ण

	अगर (++qtd->isoc_frame_index == qtd->urb->packet_count) अणु
		/*
		 * urb->status is not used क्रम isoc transfers here. The
		 * inभागidual frame_desc status are used instead.
		 */
		dwc2_host_complete(hsotg, qtd, 0);
		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);

		/*
		 * This check is necessary because urb_dequeue can be called
		 * from urb complete callback (sound driver क्रम example). All
		 * pending URBs are dequeued there, so no need क्रम further
		 * processing.
		 */
		अगर (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE)
			वापस -1;
		rc = DWC2_CMPL_DONE;
	पूर्ण

	qh->ntd--;

	/* Stop अगर IOC requested descriptor reached */
	अगर (dma_desc->status & HOST_DMA_IOC)
		rc = DWC2_CMPL_STOP;

	वापस rc;
पूर्ण

अटल व्योम dwc2_complete_isoc_xfer_ddma(काष्ठा dwc2_hsotg *hsotg,
					 काष्ठा dwc2_host_chan *chan,
					 क्रमागत dwc2_halt_status halt_status)
अणु
	काष्ठा dwc2_hcd_iso_packet_desc *frame_desc;
	काष्ठा dwc2_qtd *qtd, *qtd_पंचांगp;
	काष्ठा dwc2_qh *qh;
	u16 idx;
	पूर्णांक rc;

	qh = chan->qh;
	idx = qh->td_first;

	अगर (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE) अणु
		list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list_entry)
			qtd->in_process = 0;
		वापस;
	पूर्ण

	अगर (halt_status == DWC2_HC_XFER_AHB_ERR ||
	    halt_status == DWC2_HC_XFER_BABBLE_ERR) अणु
		/*
		 * Channel is halted in these error हालs, considered as serious
		 * issues.
		 * Complete all URBs marking all frames as failed, irrespective
		 * whether some of the descriptors (frames) succeeded or not.
		 * Pass error code to completion routine as well, to update
		 * urb->status, some of class drivers might use it to stop
		 * queing transfer requests.
		 */
		पूर्णांक err = halt_status == DWC2_HC_XFER_AHB_ERR ?
			  -EIO : -EOVERFLOW;

		list_क्रम_each_entry_safe(qtd, qtd_पंचांगp, &qh->qtd_list,
					 qtd_list_entry) अणु
			अगर (qtd->urb) अणु
				क्रम (idx = 0; idx < qtd->urb->packet_count;
				     idx++) अणु
					frame_desc = &qtd->urb->iso_descs[idx];
					frame_desc->status = err;
				पूर्ण

				dwc2_host_complete(hsotg, qtd, err);
			पूर्ण

			dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);
		पूर्ण

		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(qtd, qtd_पंचांगp, &qh->qtd_list, qtd_list_entry) अणु
		अगर (!qtd->in_process)
			अवरोध;

		/*
		 * Ensure idx corresponds to descriptor where first urb of this
		 * qtd was added. In fact, during isoc desc init, dwc2 may skip
		 * an index अगर current frame number is alपढ़ोy over this index.
		 */
		अगर (idx != qtd->isoc_td_first) अणु
			dev_vdbg(hsotg->dev,
				 "try to complete %d instead of %d\n",
				 idx, qtd->isoc_td_first);
			idx = qtd->isoc_td_first;
		पूर्ण

		करो अणु
			काष्ठा dwc2_qtd *qtd_next;
			u16 cur_idx;

			rc = dwc2_cmpl_host_isoc_dma_desc(hsotg, chan, qtd, qh,
							  idx);
			अगर (rc < 0)
				वापस;
			idx = dwc2_desclist_idx_inc(idx, qh->host_पूर्णांकerval,
						    chan->speed);
			अगर (!rc)
				जारी;

			अगर (rc == DWC2_CMPL_DONE)
				अवरोध;

			/* rc == DWC2_CMPL_STOP */

			अगर (qh->host_पूर्णांकerval >= 32)
				जाओ stop_scan;

			qh->td_first = idx;
			cur_idx = dwc2_frame_list_idx(hsotg->frame_number);
			qtd_next = list_first_entry(&qh->qtd_list,
						    काष्ठा dwc2_qtd,
						    qtd_list_entry);
			अगर (dwc2_frame_idx_num_gt(cur_idx,
						  qtd_next->isoc_td_last))
				अवरोध;

			जाओ stop_scan;

		पूर्ण जबतक (idx != qh->td_first);
	पूर्ण

stop_scan:
	qh->td_first = idx;
पूर्ण

अटल पूर्णांक dwc2_update_non_isoc_urb_state_ddma(काष्ठा dwc2_hsotg *hsotg,
					       काष्ठा dwc2_host_chan *chan,
					काष्ठा dwc2_qtd *qtd,
					काष्ठा dwc2_dma_desc *dma_desc,
					क्रमागत dwc2_halt_status halt_status,
					u32 n_bytes, पूर्णांक *xfer_करोne)
अणु
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	u16 reमुख्य = 0;

	अगर (chan->ep_is_in)
		reमुख्य = (dma_desc->status & HOST_DMA_NBYTES_MASK) >>
			 HOST_DMA_NBYTES_SHIFT;

	dev_vdbg(hsotg->dev, "remain=%d dwc2_urb=%p\n", reमुख्य, urb);

	अगर (halt_status == DWC2_HC_XFER_AHB_ERR) अणु
		dev_err(hsotg->dev, "EIO\n");
		urb->status = -EIO;
		वापस 1;
	पूर्ण

	अगर ((dma_desc->status & HOST_DMA_STS_MASK) == HOST_DMA_STS_PKTERR) अणु
		चयन (halt_status) अणु
		हाल DWC2_HC_XFER_STALL:
			dev_vdbg(hsotg->dev, "Stall\n");
			urb->status = -EPIPE;
			अवरोध;
		हाल DWC2_HC_XFER_BABBLE_ERR:
			dev_err(hsotg->dev, "Babble\n");
			urb->status = -EOVERFLOW;
			अवरोध;
		हाल DWC2_HC_XFER_XACT_ERR:
			dev_err(hsotg->dev, "XactErr\n");
			urb->status = -EPROTO;
			अवरोध;
		शेष:
			dev_err(hsotg->dev,
				"%s: Unhandled descriptor error status (%d)\n",
				__func__, halt_status);
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण

	अगर (dma_desc->status & HOST_DMA_A) अणु
		dev_vdbg(hsotg->dev,
			 "Active descriptor encountered on channel %d\n",
			 chan->hc_num);
		वापस 0;
	पूर्ण

	अगर (chan->ep_type == USB_ENDPOINT_XFER_CONTROL) अणु
		अगर (qtd->control_phase == DWC2_CONTROL_DATA) अणु
			urb->actual_length += n_bytes - reमुख्य;
			अगर (reमुख्य || urb->actual_length >= urb->length) अणु
				/*
				 * For Control Data stage करो not set urb->status
				 * to 0, to prevent URB callback. Set it when
				 * Status phase is करोne. See below.
				 */
				*xfer_करोne = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (qtd->control_phase == DWC2_CONTROL_STATUS) अणु
			urb->status = 0;
			*xfer_करोne = 1;
		पूर्ण
		/* No handling क्रम SETUP stage */
	पूर्ण अन्यथा अणु
		/* BULK and INTR */
		urb->actual_length += n_bytes - reमुख्य;
		dev_vdbg(hsotg->dev, "length=%d actual=%d\n", urb->length,
			 urb->actual_length);
		अगर (reमुख्य || urb->actual_length >= urb->length) अणु
			urb->status = 0;
			*xfer_करोne = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_process_non_isoc_desc(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_host_chan *chan,
				      पूर्णांक chnum, काष्ठा dwc2_qtd *qtd,
				      पूर्णांक desc_num,
				      क्रमागत dwc2_halt_status halt_status,
				      पूर्णांक *xfer_करोne)
अणु
	काष्ठा dwc2_qh *qh = chan->qh;
	काष्ठा dwc2_hcd_urb *urb = qtd->urb;
	काष्ठा dwc2_dma_desc *dma_desc;
	u32 n_bytes;
	पूर्णांक failed;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	अगर (!urb)
		वापस -EINVAL;

	dma_sync_single_क्रम_cpu(hsotg->dev,
				qh->desc_list_dma + (desc_num *
				माप(काष्ठा dwc2_dma_desc)),
				माप(काष्ठा dwc2_dma_desc),
				DMA_FROM_DEVICE);

	dma_desc = &qh->desc_list[desc_num];
	n_bytes = qh->n_bytes[desc_num];
	dev_vdbg(hsotg->dev,
		 "qtd=%p dwc2_urb=%p desc_num=%d desc=%p n_bytes=%d\n",
		 qtd, urb, desc_num, dma_desc, n_bytes);
	failed = dwc2_update_non_isoc_urb_state_ddma(hsotg, chan, qtd, dma_desc,
						     halt_status, n_bytes,
						     xfer_करोne);
	अगर (failed || (*xfer_करोne && urb->status != -EINPROGRESS)) अणु
		dwc2_host_complete(hsotg, qtd, urb->status);
		dwc2_hcd_qtd_unlink_and_मुक्त(hsotg, qtd, qh);
		dev_vdbg(hsotg->dev, "failed=%1x xfer_done=%1x\n",
			 failed, *xfer_करोne);
		वापस failed;
	पूर्ण

	अगर (qh->ep_type == USB_ENDPOINT_XFER_CONTROL) अणु
		चयन (qtd->control_phase) अणु
		हाल DWC2_CONTROL_SETUP:
			अगर (urb->length > 0)
				qtd->control_phase = DWC2_CONTROL_DATA;
			अन्यथा
				qtd->control_phase = DWC2_CONTROL_STATUS;
			dev_vdbg(hsotg->dev,
				 "  Control setup transaction done\n");
			अवरोध;
		हाल DWC2_CONTROL_DATA:
			अगर (*xfer_करोne) अणु
				qtd->control_phase = DWC2_CONTROL_STATUS;
				dev_vdbg(hsotg->dev,
					 "  Control data transfer done\n");
			पूर्ण अन्यथा अगर (desc_num + 1 == qtd->n_desc) अणु
				/*
				 * Last descriptor क्रम Control data stage which
				 * is not completed yet
				 */
				dwc2_hcd_save_data_toggle(hsotg, chan, chnum,
							  qtd);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc2_complete_non_isoc_xfer_ddma(काष्ठा dwc2_hsotg *hsotg,
					     काष्ठा dwc2_host_chan *chan,
					     पूर्णांक chnum,
					     क्रमागत dwc2_halt_status halt_status)
अणु
	काष्ठा list_head *qtd_item, *qtd_पंचांगp;
	काष्ठा dwc2_qh *qh = chan->qh;
	काष्ठा dwc2_qtd *qtd = शून्य;
	पूर्णांक xfer_करोne;
	पूर्णांक desc_num = 0;

	अगर (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE) अणु
		list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list_entry)
			qtd->in_process = 0;
		वापस;
	पूर्ण

	list_क्रम_each_safe(qtd_item, qtd_पंचांगp, &qh->qtd_list) अणु
		पूर्णांक i;
		पूर्णांक qtd_desc_count;

		qtd = list_entry(qtd_item, काष्ठा dwc2_qtd, qtd_list_entry);
		xfer_करोne = 0;
		qtd_desc_count = qtd->n_desc;

		क्रम (i = 0; i < qtd_desc_count; i++) अणु
			अगर (dwc2_process_non_isoc_desc(hsotg, chan, chnum, qtd,
						       desc_num, halt_status,
						       &xfer_करोne)) अणु
				qtd = शून्य;
				जाओ stop_scan;
			पूर्ण

			desc_num++;
		पूर्ण
	पूर्ण

stop_scan:
	अगर (qh->ep_type != USB_ENDPOINT_XFER_CONTROL) अणु
		/*
		 * Resetting the data toggle क्रम bulk and पूर्णांकerrupt endpoपूर्णांकs
		 * in हाल of stall. See handle_hc_stall_पूर्णांकr().
		 */
		अगर (halt_status == DWC2_HC_XFER_STALL)
			qh->data_toggle = DWC2_HC_PID_DATA0;
		अन्यथा
			dwc2_hcd_save_data_toggle(hsotg, chan, chnum, शून्य);
	पूर्ण

	अगर (halt_status == DWC2_HC_XFER_COMPLETE) अणु
		अगर (chan->hcपूर्णांक & HCINTMSK_NYET) अणु
			/*
			 * Got a NYET on the last transaction of the transfer.
			 * It means that the endpoपूर्णांक should be in the PING
			 * state at the beginning of the next transfer.
			 */
			qh->ping_state = 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_complete_xfer_ddma() - Scans the descriptor list, updates URB's
 * status and calls completion routine क्रम the URB अगर it's करोne. Called from
 * पूर्णांकerrupt handlers.
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller
 * @chan:        Host channel the transfer is completed on
 * @chnum:       Index of Host channel रेजिस्टरs
 * @halt_status: Reason the channel is being halted or just XferComplete
 *               क्रम isochronous transfers
 *
 * Releases the channel to be used by other transfers.
 * In हाल of Isochronous endpoपूर्णांक the channel is not halted until the end of
 * the session, i.e. QTD list is empty.
 * If periodic channel released the FrameList is updated accordingly.
 * Calls transaction selection routines to activate pending transfers.
 */
व्योम dwc2_hcd_complete_xfer_ddma(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				 क्रमागत dwc2_halt_status halt_status)
अणु
	काष्ठा dwc2_qh *qh = chan->qh;
	पूर्णांक जारी_isoc_xfer = 0;
	क्रमागत dwc2_transaction_type tr_type;

	अगर (chan->ep_type == USB_ENDPOINT_XFER_ISOC) अणु
		dwc2_complete_isoc_xfer_ddma(hsotg, chan, halt_status);

		/* Release the channel अगर halted or session completed */
		अगर (halt_status != DWC2_HC_XFER_COMPLETE ||
		    list_empty(&qh->qtd_list)) अणु
			काष्ठा dwc2_qtd *qtd, *qtd_पंचांगp;

			/*
			 * Kill all reमुख्यings QTDs since channel has been
			 * halted.
			 */
			list_क्रम_each_entry_safe(qtd, qtd_पंचांगp,
						 &qh->qtd_list,
						 qtd_list_entry) अणु
				dwc2_host_complete(hsotg, qtd,
						   -ECONNRESET);
				dwc2_hcd_qtd_unlink_and_मुक्त(hsotg,
							     qtd, qh);
			पूर्ण

			/* Halt the channel अगर session completed */
			अगर (halt_status == DWC2_HC_XFER_COMPLETE)
				dwc2_hc_halt(hsotg, chan, halt_status);
			dwc2_release_channel_ddma(hsotg, qh);
			dwc2_hcd_qh_unlink(hsotg, qh);
		पूर्ण अन्यथा अणु
			/* Keep in asचिन्हित schedule to जारी transfer */
			list_move_tail(&qh->qh_list_entry,
				       &hsotg->periodic_sched_asचिन्हित);
			/*
			 * If channel has been halted during giveback of urb
			 * then prevent any new scheduling.
			 */
			अगर (!chan->halt_status)
				जारी_isoc_xfer = 1;
		पूर्ण
		/*
		 * Toकरो: Consider the हाल when period exceeds FrameList size.
		 * Frame Rollover पूर्णांकerrupt should be used.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * Scan descriptor list to complete the URB(s), then release
		 * the channel
		 */
		dwc2_complete_non_isoc_xfer_ddma(hsotg, chan, chnum,
						 halt_status);
		dwc2_release_channel_ddma(hsotg, qh);
		dwc2_hcd_qh_unlink(hsotg, qh);

		अगर (!list_empty(&qh->qtd_list)) अणु
			/*
			 * Add back to inactive non-periodic schedule on normal
			 * completion
			 */
			dwc2_hcd_qh_add(hsotg, qh);
		पूर्ण
	पूर्ण

	tr_type = dwc2_hcd_select_transactions(hsotg);
	अगर (tr_type != DWC2_TRANSACTION_NONE || जारी_isoc_xfer) अणु
		अगर (जारी_isoc_xfer) अणु
			अगर (tr_type == DWC2_TRANSACTION_NONE)
				tr_type = DWC2_TRANSACTION_PERIODIC;
			अन्यथा अगर (tr_type == DWC2_TRANSACTION_NON_PERIODIC)
				tr_type = DWC2_TRANSACTION_ALL;
		पूर्ण
		dwc2_hcd_queue_transactions(hsotg, tr_type);
	पूर्ण
पूर्ण
