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
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "fhci.h"

अटल व्योम init_td(काष्ठा td *td)
अणु
	स_रखो(td, 0, माप(*td));
	INIT_LIST_HEAD(&td->node);
	INIT_LIST_HEAD(&td->frame_lh);
पूर्ण

अटल व्योम init_ed(काष्ठा ed *ed)
अणु
	स_रखो(ed, 0, माप(*ed));
	INIT_LIST_HEAD(&ed->td_list);
	INIT_LIST_HEAD(&ed->node);
पूर्ण

अटल काष्ठा td *get_empty_td(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा td *td;

	अगर (!list_empty(&fhci->empty_tds)) अणु
		td = list_entry(fhci->empty_tds.next, काष्ठा td, node);
		list_del(fhci->empty_tds.next);
	पूर्ण अन्यथा अणु
		td = kदो_स्मृति(माप(*td), GFP_ATOMIC);
		अगर (!td)
			fhci_err(fhci, "No memory to allocate to TD\n");
		अन्यथा
			init_td(td);
	पूर्ण

	वापस td;
पूर्ण

व्योम fhci_recycle_empty_td(काष्ठा fhci_hcd *fhci, काष्ठा td *td)
अणु
	init_td(td);
	list_add(&td->node, &fhci->empty_tds);
पूर्ण

काष्ठा ed *fhci_get_empty_ed(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा ed *ed;

	अगर (!list_empty(&fhci->empty_eds)) अणु
		ed = list_entry(fhci->empty_eds.next, काष्ठा ed, node);
		list_del(fhci->empty_eds.next);
	पूर्ण अन्यथा अणु
		ed = kदो_स्मृति(माप(*ed), GFP_ATOMIC);
		अगर (!ed)
			fhci_err(fhci, "No memory to allocate to ED\n");
		अन्यथा
			init_ed(ed);
	पूर्ण

	वापस ed;
पूर्ण

व्योम fhci_recycle_empty_ed(काष्ठा fhci_hcd *fhci, काष्ठा ed *ed)
अणु
	init_ed(ed);
	list_add(&ed->node, &fhci->empty_eds);
पूर्ण

काष्ठा td *fhci_td_fill(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb,
			काष्ठा urb_priv *urb_priv, काष्ठा ed *ed, u16 index,
			क्रमागत fhci_ta_type type, पूर्णांक toggle, u8 *data, u32 len,
			u16 पूर्णांकerval, u16 start_frame, bool ioc)
अणु
	काष्ठा td *td = get_empty_td(fhci);

	अगर (!td)
		वापस शून्य;

	td->urb = urb;
	td->ed = ed;
	td->type = type;
	td->toggle = toggle;
	td->data = data;
	td->len = len;
	td->iso_index = index;
	td->पूर्णांकerval = पूर्णांकerval;
	td->start_frame = start_frame;
	td->ioc = ioc;
	td->status = USB_TD_OK;

	urb_priv->tds[index] = td;

	वापस td;
पूर्ण
