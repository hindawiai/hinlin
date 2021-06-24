<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006.
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
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "fhci.h"

/* maps the hardware error code to the USB error code */
अटल पूर्णांक status_to_error(u32 status)
अणु
	अगर (status == USB_TD_OK)
		वापस 0;
	अन्यथा अगर (status & USB_TD_RX_ER_CRC)
		वापस -EILSEQ;
	अन्यथा अगर (status & USB_TD_RX_ER_NONOCT)
		वापस -EPROTO;
	अन्यथा अगर (status & USB_TD_RX_ER_OVERUN)
		वापस -ECOMM;
	अन्यथा अगर (status & USB_TD_RX_ER_BITSTUFF)
		वापस -EPROTO;
	अन्यथा अगर (status & USB_TD_RX_ER_PID)
		वापस -EILSEQ;
	अन्यथा अगर (status & (USB_TD_TX_ER_NAK | USB_TD_TX_ER_TIMEOUT))
		वापस -ETIMEDOUT;
	अन्यथा अगर (status & USB_TD_TX_ER_STALL)
		वापस -EPIPE;
	अन्यथा अगर (status & USB_TD_TX_ER_UNDERUN)
		वापस -ENOSR;
	अन्यथा अगर (status & USB_TD_RX_DATA_UNDERUN)
		वापस -EREMOTEIO;
	अन्यथा अगर (status & USB_TD_RX_DATA_OVERUN)
		वापस -EOVERFLOW;
	अन्यथा
		वापस -EINVAL;
पूर्ण

व्योम fhci_add_td_to_frame(काष्ठा fhci_समय_frame *frame, काष्ठा td *td)
अणु
	list_add_tail(&td->frame_lh, &frame->tds_list);
पूर्ण

व्योम fhci_add_tds_to_ed(काष्ठा ed *ed, काष्ठा td **td_list, पूर्णांक number)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < number; i++) अणु
		काष्ठा td *td = td_list[i];
		list_add_tail(&td->node, &ed->td_list);
	पूर्ण
	अगर (ed->td_head == शून्य)
		ed->td_head = td_list[0];
पूर्ण

अटल काष्ठा td *peek_td_from_ed(काष्ठा ed *ed)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&ed->td_list))
		td = list_entry(ed->td_list.next, काष्ठा td, node);
	अन्यथा
		td = शून्य;

	वापस td;
पूर्ण

काष्ठा td *fhci_हटाओ_td_from_frame(काष्ठा fhci_समय_frame *frame)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&frame->tds_list)) अणु
		td = list_entry(frame->tds_list.next, काष्ठा td, frame_lh);
		list_del_init(frame->tds_list.next);
	पूर्ण अन्यथा
		td = शून्य;

	वापस td;
पूर्ण

काष्ठा td *fhci_peek_td_from_frame(काष्ठा fhci_समय_frame *frame)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&frame->tds_list))
		td = list_entry(frame->tds_list.next, काष्ठा td, frame_lh);
	अन्यथा
		td = शून्य;

	वापस td;
पूर्ण

काष्ठा td *fhci_हटाओ_td_from_ed(काष्ठा ed *ed)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&ed->td_list)) अणु
		td = list_entry(ed->td_list.next, काष्ठा td, node);
		list_del_init(ed->td_list.next);

		/* अगर this TD was the ED's head, find next TD */
		अगर (!list_empty(&ed->td_list))
			ed->td_head = list_entry(ed->td_list.next, काष्ठा td,
						 node);
		अन्यथा
			ed->td_head = शून्य;
	पूर्ण अन्यथा
		td = शून्य;

	वापस td;
पूर्ण

काष्ठा td *fhci_हटाओ_td_from_करोne_list(काष्ठा fhci_controller_list *p_list)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&p_list->करोne_list)) अणु
		td = list_entry(p_list->करोne_list.next, काष्ठा td, node);
		list_del_init(p_list->करोne_list.next);
	पूर्ण अन्यथा
		td = शून्य;

	वापस td;
पूर्ण

व्योम fhci_move_td_from_ed_to_करोne_list(काष्ठा fhci_usb *usb, काष्ठा ed *ed)
अणु
	काष्ठा td *td;

	td = ed->td_head;
	list_del_init(&td->node);

	/* If this TD was the ED's head,find next TD */
	अगर (!list_empty(&ed->td_list))
		ed->td_head = list_entry(ed->td_list.next, काष्ठा td, node);
	अन्यथा अणु
		ed->td_head = शून्य;
		ed->state = FHCI_ED_SKIP;
	पूर्ण
	ed->toggle_carry = td->toggle;
	list_add_tail(&td->node, &usb->hc_list->करोne_list);
	अगर (td->ioc)
		usb->transfer_confirm(usb->fhci);
पूर्ण

/* मुक्त करोne FHCI URB resource such as ED and TD */
अटल व्योम मुक्त_urb_priv(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb)
अणु
	पूर्णांक i;
	काष्ठा urb_priv *urb_priv = urb->hcpriv;
	काष्ठा ed *ed = urb_priv->ed;

	क्रम (i = 0; i < urb_priv->num_of_tds; i++) अणु
		list_del_init(&urb_priv->tds[i]->node);
		fhci_recycle_empty_td(fhci, urb_priv->tds[i]);
	पूर्ण

	/* अगर this TD was the ED's head,find the next TD */
	अगर (!list_empty(&ed->td_list))
		ed->td_head = list_entry(ed->td_list.next, काष्ठा td, node);
	अन्यथा
		ed->td_head = शून्य;

	kमुक्त(urb_priv->tds);
	kमुक्त(urb_priv);
	urb->hcpriv = शून्य;

	/* अगर this TD was the ED's head,find next TD */
	अगर (ed->td_head == शून्य)
		list_del_init(&ed->node);
	fhci->active_urbs--;
पूर्ण

/* this routine called to complete and मुक्त करोne URB */
व्योम fhci_urb_complete_मुक्त(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb)
अणु
	मुक्त_urb_priv(fhci, urb);

	अगर (urb->status == -EINPROGRESS) अणु
		अगर (urb->actual_length != urb->transfer_buffer_length &&
				urb->transfer_flags & URB_SHORT_NOT_OK)
			urb->status = -EREMOTEIO;
		अन्यथा
			urb->status = 0;
	पूर्ण

	usb_hcd_unlink_urb_from_ep(fhci_to_hcd(fhci), urb);

	spin_unlock(&fhci->lock);

	usb_hcd_giveback_urb(fhci_to_hcd(fhci), urb, urb->status);

	spin_lock(&fhci->lock);
पूर्ण

/*
 * caculate transfer length/stats and update the urb
 * Precondition: irqsafe(only क्रम urb-?status locking)
 */
व्योम fhci_करोne_td(काष्ठा urb *urb, काष्ठा td *td)
अणु
	काष्ठा ed *ed = td->ed;
	u32 cc = td->status;

	/* ISO...drivers see per-TD length/status */
	अगर (ed->mode == FHCI_TF_ISO) अणु
		u32 len;
		अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK &&
				cc == USB_TD_RX_DATA_UNDERUN))
			cc = USB_TD_OK;

		अगर (usb_pipeout(urb->pipe))
			len = urb->iso_frame_desc[td->iso_index].length;
		अन्यथा
			len = td->actual_len;

		urb->actual_length += len;
		urb->iso_frame_desc[td->iso_index].actual_length = len;
		urb->iso_frame_desc[td->iso_index].status =
			status_to_error(cc);
	पूर्ण

	/* BULK,INT,CONTROL... drivers see aggregate length/status,
	 * except that "setup" bytes aren't counted and "short" transfers
	 * might not be reported as errors.
	 */
	अन्यथा अणु
		अगर (td->error_cnt >= 3)
			urb->error_count = 3;

		/* control endpoपूर्णांक only have soft stalls */

		/* update packet status अगर needed(लघु may be ok) */
		अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK) &&
				cc == USB_TD_RX_DATA_UNDERUN) अणु
			ed->state = FHCI_ED_OPER;
			cc = USB_TD_OK;
		पूर्ण
		अगर (cc != USB_TD_OK) अणु
			अगर (urb->status == -EINPROGRESS)
				urb->status = status_to_error(cc);
		पूर्ण

		/* count all non-empty packets except control SETUP packet */
		अगर (td->type != FHCI_TA_SETUP || td->iso_index != 0)
			urb->actual_length += td->actual_len;
	पूर्ण
पूर्ण

/* there are some pedning request to unlink */
व्योम fhci_del_ed_list(काष्ठा fhci_hcd *fhci, काष्ठा ed *ed)
अणु
	काष्ठा td *td = peek_td_from_ed(ed);
	काष्ठा urb *urb = td->urb;
	काष्ठा urb_priv *urb_priv = urb->hcpriv;

	अगर (urb_priv->state == URB_DEL) अणु
		td = fhci_हटाओ_td_from_ed(ed);
		/* HC may have partly processed this TD */
		अगर (td->status != USB_TD_INPROGRESS)
			fhci_करोne_td(urb, td);

		/* URB is करोne;clean up */
		अगर (++(urb_priv->tds_cnt) == urb_priv->num_of_tds)
			fhci_urb_complete_मुक्त(fhci, urb);
	पूर्ण
पूर्ण
