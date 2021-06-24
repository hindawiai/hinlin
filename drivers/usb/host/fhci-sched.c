<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006, 2011.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) Logic Product Development, Inc. 2007
 *               Peter Barada <peterb@logicpd.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <यंत्र/fsl_gपंचांग.h>
#समावेश "fhci.h"

अटल व्योम recycle_frame(काष्ठा fhci_usb *usb, काष्ठा packet *pkt)
अणु
	pkt->data = शून्य;
	pkt->len = 0;
	pkt->status = USB_TD_OK;
	pkt->info = 0;
	pkt->priv_data = शून्य;

	cq_put(&usb->ep0->empty_frame_Q, pkt);
पूर्ण

/* confirm submitted packet */
व्योम fhci_transaction_confirm(काष्ठा fhci_usb *usb, काष्ठा packet *pkt)
अणु
	काष्ठा td *td;
	काष्ठा packet *td_pkt;
	काष्ठा ed *ed;
	u32 trans_len;
	bool td_करोne = false;

	td = fhci_हटाओ_td_from_frame(usb->actual_frame);
	td_pkt = td->pkt;
	trans_len = pkt->len;
	td->status = pkt->status;
	अगर (td->type == FHCI_TA_IN && td_pkt->info & PKT_DUMMY_PACKET) अणु
		अगर ((td->data + td->actual_len) && trans_len)
			स_नकल(td->data + td->actual_len, pkt->data,
			       trans_len);
		cq_put(&usb->ep0->dummy_packets_Q, pkt->data);
	पूर्ण

	recycle_frame(usb, pkt);

	ed = td->ed;
	अगर (ed->mode == FHCI_TF_ISO) अणु
		अगर (ed->td_list.next->next != &ed->td_list) अणु
			काष्ठा td *td_next =
			    list_entry(ed->td_list.next->next, काष्ठा td,
				       node);

			td_next->start_frame = usb->actual_frame->frame_num;
		पूर्ण
		td->actual_len = trans_len;
		td_करोne = true;
	पूर्ण अन्यथा अगर ((td->status & USB_TD_ERROR) &&
			!(td->status & USB_TD_TX_ER_NAK)) अणु
		/*
		 * There was an error on the transaction (but not NAK).
		 * If it is fatal error (data underrun, stall, bad pid or 3
		 * errors exceeded), mark this TD as करोne.
		 */
		अगर ((td->status & USB_TD_RX_DATA_UNDERUN) ||
				(td->status & USB_TD_TX_ER_STALL) ||
				(td->status & USB_TD_RX_ER_PID) ||
				(++td->error_cnt >= 3)) अणु
			ed->state = FHCI_ED_HALTED;
			td_करोne = true;

			अगर (td->status & USB_TD_RX_DATA_UNDERUN) अणु
				fhci_dbg(usb->fhci, "td err fu\n");
				td->toggle = !td->toggle;
				td->actual_len += trans_len;
			पूर्ण अन्यथा अणु
				fhci_dbg(usb->fhci, "td err f!u\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			fhci_dbg(usb->fhci, "td err !f\n");
			/* it is not a fatal error -retry this transaction */
			td->nak_cnt = 0;
			td->error_cnt++;
			td->status = USB_TD_OK;
		पूर्ण
	पूर्ण अन्यथा अगर (td->status & USB_TD_TX_ER_NAK) अणु
		/* there was a NAK response */
		fhci_vdbg(usb->fhci, "td nack\n");
		td->nak_cnt++;
		td->error_cnt = 0;
		td->status = USB_TD_OK;
	पूर्ण अन्यथा अणु
		/* there was no error on transaction */
		td->error_cnt = 0;
		td->nak_cnt = 0;
		td->toggle = !td->toggle;
		td->actual_len += trans_len;

		अगर (td->len == td->actual_len)
			td_करोne = true;
	पूर्ण

	अगर (td_करोne)
		fhci_move_td_from_ed_to_करोne_list(usb, ed);
पूर्ण

/*
 * Flush all transmitted packets from BDs
 * This routine is called when disabling the USB port to flush all
 * transmissions that are alपढ़ोy scheduled in the BDs
 */
व्योम fhci_flush_all_transmissions(काष्ठा fhci_usb *usb)
अणु
	u8 mode;
	काष्ठा td *td;

	mode = in_8(&usb->fhci->regs->usb_usmod);
	clrbits8(&usb->fhci->regs->usb_usmod, USB_MODE_EN);

	fhci_flush_bds(usb);

	जबतक ((td = fhci_peek_td_from_frame(usb->actual_frame)) != शून्य) अणु
		काष्ठा packet *pkt = td->pkt;

		pkt->status = USB_TD_TX_ER_TIMEOUT;
		fhci_transaction_confirm(usb, pkt);
	पूर्ण

	usb->actual_frame->frame_status = FRAME_END_TRANSMISSION;

	/* reset the event रेजिस्टर */
	out_be16(&usb->fhci->regs->usb_usber, 0xffff);
	/* enable the USB controller */
	out_8(&usb->fhci->regs->usb_usmod, mode | USB_MODE_EN);
पूर्ण

/*
 * This function क्रमms the packet and transmit the packet. This function
 * will handle all endpoपूर्णांक type:ISO,पूर्णांकerrupt,control and bulk
 */
अटल पूर्णांक add_packet(काष्ठा fhci_usb *usb, काष्ठा ed *ed, काष्ठा td *td)
अणु
	u32 fw_transaction_समय, len = 0;
	काष्ठा packet *pkt;
	u8 *data = शून्य;

	/* calcalate data address,len and toggle and then add the transaction */
	अगर (td->toggle == USB_TD_TOGGLE_CARRY)
		td->toggle = ed->toggle_carry;

	चयन (ed->mode) अणु
	हाल FHCI_TF_ISO:
		len = td->len;
		अगर (td->type != FHCI_TA_IN)
			data = td->data;
		अवरोध;
	हाल FHCI_TF_CTRL:
	हाल FHCI_TF_BULK:
		len = min(td->len - td->actual_len, ed->max_pkt_size);
		अगर (!((td->type == FHCI_TA_IN) &&
		      ((len + td->actual_len) == td->len)))
			data = td->data + td->actual_len;
		अवरोध;
	हाल FHCI_TF_INTR:
		len = min(td->len, ed->max_pkt_size);
		अगर (!((td->type == FHCI_TA_IN) &&
		      ((td->len + CRC_SIZE) >= ed->max_pkt_size)))
			data = td->data;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (usb->port_status == FHCI_PORT_FULL)
		fw_transaction_समय = (((len + PROTOCOL_OVERHEAD) * 11) >> 4);
	अन्यथा
		fw_transaction_समय = ((len + PROTOCOL_OVERHEAD) * 6);

	/* check अगर there's enough space in this frame to submit this TD */
	अगर (usb->actual_frame->total_bytes + len + PROTOCOL_OVERHEAD >=
			usb->max_bytes_per_frame) अणु
		fhci_vdbg(usb->fhci, "not enough space in this frame: "
			  "%d %d %d\n", usb->actual_frame->total_bytes, len,
			  usb->max_bytes_per_frame);
		वापस -1;
	पूर्ण

	/* check अगर there's enough समय in this frame to submit this TD */
	अगर (usb->actual_frame->frame_status != FRAME_IS_PREPARED &&
	    (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION ||
	     (fw_transaction_समय + usb->sw_transaction_समय >=
	      1000 - fhci_get_sof_समयr_count(usb)))) अणु
		fhci_dbg(usb->fhci, "not enough time in this frame\n");
		वापस -1;
	पूर्ण

	/* update frame object fields beक्रमe transmitting */
	pkt = cq_get(&usb->ep0->empty_frame_Q);
	अगर (!pkt) अणु
		fhci_dbg(usb->fhci, "there is no empty frame\n");
		वापस -1;
	पूर्ण
	td->pkt = pkt;

	pkt->info = 0;
	अगर (data == शून्य) अणु
		data = cq_get(&usb->ep0->dummy_packets_Q);
		BUG_ON(!data);
		pkt->info = PKT_DUMMY_PACKET;
	पूर्ण
	pkt->data = data;
	pkt->len = len;
	pkt->status = USB_TD_OK;
	/* update TD status field beक्रमe transmitting */
	td->status = USB_TD_INPROGRESS;
	/* update actual frame समय object with the actual transmission */
	usb->actual_frame->total_bytes += (len + PROTOCOL_OVERHEAD);
	fhci_add_td_to_frame(usb->actual_frame, td);

	अगर (usb->port_status != FHCI_PORT_FULL &&
			usb->port_status != FHCI_PORT_LOW) अणु
		pkt->status = USB_TD_TX_ER_TIMEOUT;
		pkt->len = 0;
		fhci_transaction_confirm(usb, pkt);
	पूर्ण अन्यथा अगर (fhci_host_transaction(usb, pkt, td->type, ed->dev_addr,
			ed->ep_addr, ed->mode, ed->speed, td->toggle)) अणु
		/* हटाओ TD from actual frame */
		list_del_init(&td->frame_lh);
		td->status = USB_TD_OK;
		अगर (pkt->info & PKT_DUMMY_PACKET)
			cq_put(&usb->ep0->dummy_packets_Q, pkt->data);
		recycle_frame(usb, pkt);
		usb->actual_frame->total_bytes -= (len + PROTOCOL_OVERHEAD);
		fhci_err(usb->fhci, "host transaction failed\n");
		वापस -1;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम move_head_to_tail(काष्ठा list_head *list)
अणु
	काष्ठा list_head *node = list->next;

	अगर (!list_empty(list)) अणु
		list_move_tail(node, list);
	पूर्ण
पूर्ण

/*
 * This function goes through the endpoपूर्णांक list and schedules the
 * transactions within this list
 */
अटल पूर्णांक scan_ed_list(काष्ठा fhci_usb *usb,
			काष्ठा list_head *list, क्रमागत fhci_tf_mode list_type)
अणु
	अटल स्थिर पूर्णांक frame_part[4] = अणु
		[FHCI_TF_CTRL] = MAX_BYTES_PER_FRAME,
		[FHCI_TF_ISO] = (MAX_BYTES_PER_FRAME *
				 MAX_PERIODIC_FRAME_USAGE) / 100,
		[FHCI_TF_BULK] = MAX_BYTES_PER_FRAME,
		[FHCI_TF_INTR] = (MAX_BYTES_PER_FRAME *
				  MAX_PERIODIC_FRAME_USAGE) / 100
	पूर्ण;
	काष्ठा ed *ed;
	काष्ठा td *td;
	पूर्णांक ans = 1;
	u32 save_transaction_समय = usb->sw_transaction_समय;

	list_क्रम_each_entry(ed, list, node) अणु
		td = ed->td_head;

		अगर (!td || td->status == USB_TD_INPROGRESS)
			जारी;

		अगर (ed->state != FHCI_ED_OPER) अणु
			अगर (ed->state == FHCI_ED_URB_DEL) अणु
				td->status = USB_TD_OK;
				fhci_move_td_from_ed_to_करोne_list(usb, ed);
				ed->state = FHCI_ED_SKIP;
			पूर्ण
			जारी;
		पूर्ण

		/*
		 * अगर it isn't पूर्णांकerrupt pipe or it is not iso pipe and the
		 * पूर्णांकerval समय passed
		 */
		अगर ((list_type == FHCI_TF_INTR || list_type == FHCI_TF_ISO) &&
				(((usb->actual_frame->frame_num -
				   td->start_frame) & 0x7ff) < td->पूर्णांकerval))
			जारी;

		अगर (add_packet(usb, ed, td) < 0)
			जारी;

		/* update समय stamps in the TD */
		td->start_frame = usb->actual_frame->frame_num;
		usb->sw_transaction_समय += save_transaction_समय;

		अगर (usb->actual_frame->total_bytes >=
					usb->max_bytes_per_frame) अणु
			usb->actual_frame->frame_status =
				FRAME_DATA_END_TRANSMISSION;
			fhci_push_dummy_bd(usb->ep0);
			ans = 0;
			अवरोध;
		पूर्ण

		अगर (usb->actual_frame->total_bytes >= frame_part[list_type])
			अवरोध;
	पूर्ण

	/* be fair to each ED(move list head around) */
	move_head_to_tail(list);
	usb->sw_transaction_समय = save_transaction_समय;

	वापस ans;
पूर्ण

अटल u32 rotate_frames(काष्ठा fhci_usb *usb)
अणु
	काष्ठा fhci_hcd *fhci = usb->fhci;

	अगर (!list_empty(&usb->actual_frame->tds_list)) अणु
		अगर ((((in_be16(&fhci->pram->frame_num) & 0x07ff) -
		      usb->actual_frame->frame_num) & 0x7ff) > 5)
			fhci_flush_actual_frame(usb);
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	usb->actual_frame->frame_status = FRAME_IS_PREPARED;
	usb->actual_frame->frame_num = in_be16(&fhci->pram->frame_num) & 0x7ff;
	usb->actual_frame->total_bytes = 0;

	वापस 0;
पूर्ण

/*
 * This function schedule the USB transaction and will process the
 * endpoपूर्णांक in the following order: iso, पूर्णांकerrupt, control and bulk.
 */
व्योम fhci_schedule_transactions(काष्ठा fhci_usb *usb)
अणु
	पूर्णांक left = 1;

	अगर (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION)
		अगर (rotate_frames(usb) != 0)
			वापस;

	अगर (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION)
		वापस;

	अगर (usb->actual_frame->total_bytes == 0) अणु
		/*
		 * schedule the next available ISO transfer
		 *or next stage of the ISO transfer
		 */
		scan_ed_list(usb, &usb->hc_list->iso_list, FHCI_TF_ISO);

		/*
		 * schedule the next available पूर्णांकerrupt transfer or
		 * the next stage of the पूर्णांकerrupt transfer
		 */
		scan_ed_list(usb, &usb->hc_list->पूर्णांकr_list, FHCI_TF_INTR);

		/*
		 * schedule the next available control transfer
		 * or the next stage of the control transfer
		 */
		left = scan_ed_list(usb, &usb->hc_list->ctrl_list,
				    FHCI_TF_CTRL);
	पूर्ण

	/*
	 * schedule the next available bulk transfer or the next stage of the
	 * bulk transfer
	 */
	अगर (left > 0)
		scan_ed_list(usb, &usb->hc_list->bulk_list, FHCI_TF_BULK);
पूर्ण

/* Handles SOF पूर्णांकerrupt */
अटल व्योम sof_पूर्णांकerrupt(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	अगर ((usb->port_status == FHCI_PORT_DISABLED) &&
	    (usb->vroot_hub->port.wPortStatus & USB_PORT_STAT_CONNECTION) &&
	    !(usb->vroot_hub->port.wPortChange & USB_PORT_STAT_C_CONNECTION)) अणु
		अगर (usb->vroot_hub->port.wPortStatus & USB_PORT_STAT_LOW_SPEED)
			usb->port_status = FHCI_PORT_LOW;
		अन्यथा
			usb->port_status = FHCI_PORT_FULL;
		/* Disable IDLE */
		usb->saved_msk &= ~USB_E_IDLE_MASK;
		out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);
	पूर्ण

	gपंचांग_set_exact_समयr16(fhci->समयr, usb->max_frame_usage, false);

	fhci_host_transmit_actual_frame(usb);
	usb->actual_frame->frame_status = FRAME_IS_TRANSMITTED;

	fhci_schedule_transactions(usb);
पूर्ण

/* Handles device disconnected पूर्णांकerrupt on port */
व्योम fhci_device_disconnected_पूर्णांकerrupt(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_usb_disable_पूर्णांकerrupt(usb);
	clrbits8(&usb->fhci->regs->usb_usmod, USB_MODE_LSS);
	usb->port_status = FHCI_PORT_DISABLED;

	fhci_stop_sof_समयr(fhci);

	/* Enable IDLE since we want to know अगर something comes aदीर्घ */
	usb->saved_msk |= USB_E_IDLE_MASK;
	out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);

	usb->vroot_hub->port.wPortStatus &= ~USB_PORT_STAT_CONNECTION;
	usb->vroot_hub->port.wPortChange |= USB_PORT_STAT_C_CONNECTION;
	usb->max_bytes_per_frame = 0;
	fhci_usb_enable_पूर्णांकerrupt(usb);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

/* detect a new device connected on the USB port */
व्योम fhci_device_connected_पूर्णांकerrupt(काष्ठा fhci_hcd *fhci)
अणु

	काष्ठा fhci_usb *usb = fhci->usb_lld;
	पूर्णांक state;
	पूर्णांक ret;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_usb_disable_पूर्णांकerrupt(usb);
	state = fhci_ioports_check_bus_state(fhci);

	/* low-speed device was connected to the USB port */
	अगर (state == 1) अणु
		ret = qe_usb_घड़ी_set(fhci->lowspeed_clk, USB_CLOCK >> 3);
		अगर (ret) अणु
			fhci_warn(fhci, "Low-Speed device is not supported, "
				  "try use BRGx\n");
			जाओ out;
		पूर्ण

		usb->port_status = FHCI_PORT_LOW;
		setbits8(&usb->fhci->regs->usb_usmod, USB_MODE_LSS);
		usb->vroot_hub->port.wPortStatus |=
		    (USB_PORT_STAT_LOW_SPEED |
		     USB_PORT_STAT_CONNECTION);
		usb->vroot_hub->port.wPortChange |=
		    USB_PORT_STAT_C_CONNECTION;
		usb->max_bytes_per_frame =
		    (MAX_BYTES_PER_FRAME >> 3) - 7;
		fhci_port_enable(usb);
	पूर्ण अन्यथा अगर (state == 2) अणु
		ret = qe_usb_घड़ी_set(fhci->fullspeed_clk, USB_CLOCK);
		अगर (ret) अणु
			fhci_warn(fhci, "Full-Speed device is not supported, "
				  "try use CLKx\n");
			जाओ out;
		पूर्ण

		usb->port_status = FHCI_PORT_FULL;
		clrbits8(&usb->fhci->regs->usb_usmod, USB_MODE_LSS);
		usb->vroot_hub->port.wPortStatus &=
		    ~USB_PORT_STAT_LOW_SPEED;
		usb->vroot_hub->port.wPortStatus |=
		    USB_PORT_STAT_CONNECTION;
		usb->vroot_hub->port.wPortChange |=
		    USB_PORT_STAT_C_CONNECTION;
		usb->max_bytes_per_frame = (MAX_BYTES_PER_FRAME - 15);
		fhci_port_enable(usb);
	पूर्ण
out:
	fhci_usb_enable_पूर्णांकerrupt(usb);
	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

irqवापस_t fhci_frame_limit_समयr_irq(पूर्णांक irq, व्योम *_hcd)
अणु
	काष्ठा usb_hcd *hcd = _hcd;
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	spin_lock(&fhci->lock);

	gपंचांग_set_exact_समयr16(fhci->समयr, 1000, false);

	अगर (usb->actual_frame->frame_status == FRAME_IS_TRANSMITTED) अणु
		usb->actual_frame->frame_status = FRAME_TIMER_END_TRANSMISSION;
		fhci_push_dummy_bd(usb->ep0);
	पूर्ण

	fhci_schedule_transactions(usb);

	spin_unlock(&fhci->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* Cancel transmission on the USB endpoपूर्णांक */
अटल व्योम पात_transmission(काष्ठा fhci_usb *usb)
अणु
	fhci_dbg(usb->fhci, "-> %s\n", __func__);
	/* issue stop Tx command */
	qe_issue_cmd(QE_USB_STOP_TX, QE_CR_SUBBLOCK_USB, EP_ZERO, 0);
	/* flush Tx FIFOs */
	out_8(&usb->fhci->regs->usb_uscom, USB_CMD_FLUSH_FIFO | EP_ZERO);
	udelay(1000);
	/* reset Tx BDs */
	fhci_flush_bds(usb);
	/* issue restart Tx command */
	qe_issue_cmd(QE_USB_RESTART_TX, QE_CR_SUBBLOCK_USB, EP_ZERO, 0);
	fhci_dbg(usb->fhci, "<- %s\n", __func__);
पूर्ण

irqवापस_t fhci_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	काष्ठा fhci_usb *usb;
	u16 usb_er = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fhci->lock, flags);

	usb = fhci->usb_lld;

	usb_er |= in_be16(&usb->fhci->regs->usb_usber) &
		  in_be16(&usb->fhci->regs->usb_usbmr);

	/* clear event bits क्रम next समय */
	out_be16(&usb->fhci->regs->usb_usber, usb_er);

	fhci_dbg_isr(fhci, usb_er);

	अगर (usb_er & USB_E_RESET_MASK) अणु
		अगर ((usb->port_status == FHCI_PORT_FULL) ||
				(usb->port_status == FHCI_PORT_LOW)) अणु
			fhci_device_disconnected_पूर्णांकerrupt(fhci);
			usb_er &= ~USB_E_IDLE_MASK;
		पूर्ण अन्यथा अगर (usb->port_status == FHCI_PORT_WAITING) अणु
			usb->port_status = FHCI_PORT_DISCONNECTING;

			/* Turn on IDLE since we want to disconnect */
			usb->saved_msk |= USB_E_IDLE_MASK;
			out_be16(&usb->fhci->regs->usb_usber,
				 usb->saved_msk);
		पूर्ण अन्यथा अगर (usb->port_status == FHCI_PORT_DISABLED) अणु
			अगर (fhci_ioports_check_bus_state(fhci) == 1)
				fhci_device_connected_पूर्णांकerrupt(fhci);
		पूर्ण
		usb_er &= ~USB_E_RESET_MASK;
	पूर्ण

	अगर (usb_er & USB_E_MSF_MASK) अणु
		पात_transmission(fhci->usb_lld);
		usb_er &= ~USB_E_MSF_MASK;
	पूर्ण

	अगर (usb_er & (USB_E_SOF_MASK | USB_E_SFT_MASK)) अणु
		sof_पूर्णांकerrupt(fhci);
		usb_er &= ~(USB_E_SOF_MASK | USB_E_SFT_MASK);
	पूर्ण

	अगर (usb_er & USB_E_TXB_MASK) अणु
		fhci_tx_conf_पूर्णांकerrupt(fhci->usb_lld);
		usb_er &= ~USB_E_TXB_MASK;
	पूर्ण

	अगर (usb_er & USB_E_TXE1_MASK) अणु
		fhci_tx_conf_पूर्णांकerrupt(fhci->usb_lld);
		usb_er &= ~USB_E_TXE1_MASK;
	पूर्ण

	अगर (usb_er & USB_E_IDLE_MASK) अणु
		अगर (usb->port_status == FHCI_PORT_DISABLED) अणु
			usb_er &= ~USB_E_RESET_MASK;
			fhci_device_connected_पूर्णांकerrupt(fhci);
		पूर्ण अन्यथा अगर (usb->port_status ==
				FHCI_PORT_DISCONNECTING) अणु
			/* XXX usb->port_status = FHCI_PORT_WAITING; */
			/* Disable IDLE */
			usb->saved_msk &= ~USB_E_IDLE_MASK;
			out_be16(&usb->fhci->regs->usb_usbmr,
				 usb->saved_msk);
		पूर्ण अन्यथा अणु
			fhci_dbg_isr(fhci, -1);
		पूर्ण

		usb_er &= ~USB_E_IDLE_MASK;
	पूर्ण

	spin_unlock_irqrestore(&fhci->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण


/*
 * Process normal completions(error or success) and clean the schedule.
 *
 * This is the मुख्य path क्रम handing urbs back to drivers. The only other patth
 * is process_del_list(),which unlinks URBs by scanning EDs,instead of scanning
 * the (re-reversed) करोne list as this करोes.
 */
अटल व्योम process_करोne_list(अचिन्हित दीर्घ data)
अणु
	काष्ठा urb *urb;
	काष्ठा ed *ed;
	काष्ठा td *td;
	काष्ठा urb_priv *urb_priv;
	काष्ठा fhci_hcd *fhci = (काष्ठा fhci_hcd *)data;

	disable_irq(fhci->समयr->irq);
	disable_irq(fhci_to_hcd(fhci)->irq);
	spin_lock(&fhci->lock);

	td = fhci_हटाओ_td_from_करोne_list(fhci->hc_list);
	जबतक (td != शून्य) अणु
		urb = td->urb;
		urb_priv = urb->hcpriv;
		ed = td->ed;

		/* update URB's length and status from TD */
		fhci_करोne_td(urb, td);
		urb_priv->tds_cnt++;

		/*
		 * अगर all this urb's TDs are करोne, call complete()
		 * Interrupt transfers are the onley special हाल:
		 * they are reissued,until "deleted" by usb_unlink_urb
		 * (real work करोne in a SOF पूर्णांकr, by process_del_list)
		 */
		अगर (urb_priv->tds_cnt == urb_priv->num_of_tds) अणु
			fhci_urb_complete_मुक्त(fhci, urb);
		पूर्ण अन्यथा अगर (urb_priv->state == URB_DEL &&
				ed->state == FHCI_ED_SKIP) अणु
			fhci_del_ed_list(fhci, ed);
			ed->state = FHCI_ED_OPER;
		पूर्ण अन्यथा अगर (ed->state == FHCI_ED_HALTED) अणु
			urb_priv->state = URB_DEL;
			ed->state = FHCI_ED_URB_DEL;
			fhci_del_ed_list(fhci, ed);
			ed->state = FHCI_ED_OPER;
		पूर्ण

		td = fhci_हटाओ_td_from_करोne_list(fhci->hc_list);
	पूर्ण

	spin_unlock(&fhci->lock);
	enable_irq(fhci->समयr->irq);
	enable_irq(fhci_to_hcd(fhci)->irq);
पूर्ण

DECLARE_TASKLET_OLD(fhci_tasklet, process_करोne_list);

/* transfer complted callback */
u32 fhci_transfer_confirm_callback(काष्ठा fhci_hcd *fhci)
अणु
	अगर (!fhci->process_करोne_task->state)
		tasklet_schedule(fhci->process_करोne_task);
	वापस 0;
पूर्ण

/*
 * adds urb to the endpoपूर्णांक descriptor list
 * arguments:
 * fhci		data काष्ठाure क्रम the Low level host controller
 * ep		USB Host endpoपूर्णांक data काष्ठाure
 * urb		USB request block data काष्ठाure
 */
व्योम fhci_queue_urb(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb)
अणु
	काष्ठा ed *ed = urb->ep->hcpriv;
	काष्ठा urb_priv *urb_priv = urb->hcpriv;
	u32 data_len = urb->transfer_buffer_length;
	पूर्णांक urb_state = 0;
	पूर्णांक toggle = 0;
	u8 *data;
	u16 cnt = 0;

	अगर (ed == शून्य) अणु
		ed = fhci_get_empty_ed(fhci);
		ed->dev_addr = usb_pipedevice(urb->pipe);
		ed->ep_addr = usb_pipeendpoपूर्णांक(urb->pipe);
		चयन (usb_pipetype(urb->pipe)) अणु
		हाल PIPE_CONTROL:
			ed->mode = FHCI_TF_CTRL;
			अवरोध;
		हाल PIPE_BULK:
			ed->mode = FHCI_TF_BULK;
			अवरोध;
		हाल PIPE_INTERRUPT:
			ed->mode = FHCI_TF_INTR;
			अवरोध;
		हाल PIPE_ISOCHRONOUS:
			ed->mode = FHCI_TF_ISO;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ed->speed = (urb->dev->speed == USB_SPEED_LOW) ?
			FHCI_LOW_SPEED : FHCI_FULL_SPEED;
		ed->max_pkt_size = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
		urb->ep->hcpriv = ed;
		fhci_dbg(fhci, "new ep speed=%d max_pkt_size=%d\n",
			 ed->speed, ed->max_pkt_size);
	पूर्ण

	/* क्रम ISO transfer calculate start frame index */
	अगर (ed->mode == FHCI_TF_ISO) अणु
		/* Ignore the possibility of underruns */
		urb->start_frame = ed->td_head ? ed->next_iso :
						 get_frame_num(fhci);
		ed->next_iso = (urb->start_frame + urb->पूर्णांकerval *
				urb->number_of_packets) & 0x07ff;
	पूर्ण

	/*
	 * OHCI handles the DATA toggle itself,we just use the USB
	 * toggle bits
	 */
	अगर (usb_gettoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			  usb_pipeout(urb->pipe)))
		toggle = USB_TD_TOGGLE_CARRY;
	अन्यथा अणु
		toggle = USB_TD_TOGGLE_DATA0;
		usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
			      usb_pipeout(urb->pipe), 1);
	पूर्ण

	urb_priv->tds_cnt = 0;
	urb_priv->ed = ed;
	अगर (data_len > 0)
		data = urb->transfer_buffer;
	अन्यथा
		data = शून्य;

	चयन (ed->mode) अणु
	हाल FHCI_TF_BULK:
		अगर (urb->transfer_flags & URB_ZERO_PACKET &&
				urb->transfer_buffer_length > 0 &&
				((urb->transfer_buffer_length %
				usb_endpoपूर्णांक_maxp(&urb->ep->desc)) == 0))
			urb_state = US_BULK0;
		जबतक (data_len > 4096) अणु
			fhci_td_fill(fhci, urb, urb_priv, ed, cnt,
				usb_pipeout(urb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				cnt ? USB_TD_TOGGLE_CARRY :
				      toggle,
				data, 4096, 0, 0, true);
			data += 4096;
			data_len -= 4096;
			cnt++;
		पूर्ण

		fhci_td_fill(fhci, urb, urb_priv, ed, cnt,
			usb_pipeout(urb->pipe) ? FHCI_TA_OUT : FHCI_TA_IN,
			cnt ? USB_TD_TOGGLE_CARRY : toggle,
			data, data_len, 0, 0, true);
		cnt++;

		अगर (urb->transfer_flags & URB_ZERO_PACKET &&
				cnt < urb_priv->num_of_tds) अणु
			fhci_td_fill(fhci, urb, urb_priv, ed, cnt,
				usb_pipeout(urb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGLE_CARRY, शून्य, 0, 0, 0, true);
			cnt++;
		पूर्ण
		अवरोध;
	हाल FHCI_TF_INTR:
		urb->start_frame = get_frame_num(fhci) + 1;
		fhci_td_fill(fhci, urb, urb_priv, ed, cnt++,
			usb_pipeout(urb->pipe) ? FHCI_TA_OUT : FHCI_TA_IN,
			USB_TD_TOGGLE_DATA0, data, data_len,
			urb->पूर्णांकerval, urb->start_frame, true);
		अवरोध;
	हाल FHCI_TF_CTRL:
		ed->dev_addr = usb_pipedevice(urb->pipe);
		ed->max_pkt_size = usb_endpoपूर्णांक_maxp(&urb->ep->desc);

		/* setup stage */
		fhci_td_fill(fhci, urb, urb_priv, ed, cnt++, FHCI_TA_SETUP,
			USB_TD_TOGGLE_DATA0, urb->setup_packet, 8, 0, 0, true);

		/* data stage */
		अगर (data_len > 0) अणु
			fhci_td_fill(fhci, urb, urb_priv, ed, cnt++,
				usb_pipeout(urb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGLE_DATA1, data, data_len, 0, 0,
				true);
		पूर्ण

		/* status stage */
		अगर (data_len > 0)
			fhci_td_fill(fhci, urb, urb_priv, ed, cnt++,
				(usb_pipeout(urb->pipe) ? FHCI_TA_IN :
							  FHCI_TA_OUT),
				USB_TD_TOGGLE_DATA1, data, 0, 0, 0, true);
		अन्यथा
			 fhci_td_fill(fhci, urb, urb_priv, ed, cnt++,
				FHCI_TA_IN,
				USB_TD_TOGGLE_DATA1, data, 0, 0, 0, true);

		urb_state = US_CTRL_SETUP;
		अवरोध;
	हाल FHCI_TF_ISO:
		क्रम (cnt = 0; cnt < urb->number_of_packets; cnt++) अणु
			u16 frame = urb->start_frame;

			/*
			 * FIXME scheduling should handle frame counter
			 * roll-around ... exotic हाल (and OHCI has
			 * a 2^16 iso range, vs other HCs max of 2^10)
			 */
			frame += cnt * urb->पूर्णांकerval;
			frame &= 0x07ff;
			fhci_td_fill(fhci, urb, urb_priv, ed, cnt,
				usb_pipeout(urb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGLE_DATA0,
				data + urb->iso_frame_desc[cnt].offset,
				urb->iso_frame_desc[cnt].length,
				urb->पूर्णांकerval, frame, true);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * set the state of URB
	 * control pipe:3 states -- setup,data,status
	 * पूर्णांकerrupt and bulk pipe:1 state -- data
	 */
	urb->pipe &= ~0x1f;
	urb->pipe |= urb_state & 0x1f;

	urb_priv->state = URB_INPROGRESS;

	अगर (!ed->td_head) अणु
		ed->state = FHCI_ED_OPER;
		चयन (ed->mode) अणु
		हाल FHCI_TF_CTRL:
			list_add(&ed->node, &fhci->hc_list->ctrl_list);
			अवरोध;
		हाल FHCI_TF_BULK:
			list_add(&ed->node, &fhci->hc_list->bulk_list);
			अवरोध;
		हाल FHCI_TF_INTR:
			list_add(&ed->node, &fhci->hc_list->पूर्णांकr_list);
			अवरोध;
		हाल FHCI_TF_ISO:
			list_add(&ed->node, &fhci->hc_list->iso_list);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	fhci_add_tds_to_ed(ed, urb_priv->tds, urb_priv->num_of_tds);
	fhci->active_urbs++;
पूर्ण
