<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nop (passthrough) Link Layer Control
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#समावेश <linux/types.h>

#समावेश "llc.h"

काष्ठा llc_nop अणु
	काष्ठा nfc_hci_dev *hdev;
	xmit_to_drv_t xmit_to_drv;
	rcv_to_hci_t rcv_to_hci;
	पूर्णांक tx_headroom;
	पूर्णांक tx_tailroom;
	llc_failure_t llc_failure;
पूर्ण;

अटल व्योम *llc_nop_init(काष्ठा nfc_hci_dev *hdev, xmit_to_drv_t xmit_to_drv,
			  rcv_to_hci_t rcv_to_hci, पूर्णांक tx_headroom,
			  पूर्णांक tx_tailroom, पूर्णांक *rx_headroom, पूर्णांक *rx_tailroom,
			  llc_failure_t llc_failure)
अणु
	काष्ठा llc_nop *llc_nop;

	*rx_headroom = 0;
	*rx_tailroom = 0;

	llc_nop = kzalloc(माप(काष्ठा llc_nop), GFP_KERNEL);
	अगर (llc_nop == शून्य)
		वापस शून्य;

	llc_nop->hdev = hdev;
	llc_nop->xmit_to_drv = xmit_to_drv;
	llc_nop->rcv_to_hci = rcv_to_hci;
	llc_nop->tx_headroom = tx_headroom;
	llc_nop->tx_tailroom = tx_tailroom;
	llc_nop->llc_failure = llc_failure;

	वापस llc_nop;
पूर्ण

अटल व्योम llc_nop_deinit(काष्ठा nfc_llc *llc)
अणु
	kमुक्त(nfc_llc_get_data(llc));
पूर्ण

अटल पूर्णांक llc_nop_start(काष्ठा nfc_llc *llc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक llc_nop_stop(काष्ठा nfc_llc *llc)
अणु
	वापस 0;
पूर्ण

अटल व्योम llc_nop_rcv_from_drv(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_nop *llc_nop = nfc_llc_get_data(llc);

	llc_nop->rcv_to_hci(llc_nop->hdev, skb);
पूर्ण

अटल पूर्णांक llc_nop_xmit_from_hci(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_nop *llc_nop = nfc_llc_get_data(llc);

	वापस llc_nop->xmit_to_drv(llc_nop->hdev, skb);
पूर्ण

अटल काष्ठा nfc_llc_ops llc_nop_ops = अणु
	.init = llc_nop_init,
	.deinit = llc_nop_deinit,
	.start = llc_nop_start,
	.stop = llc_nop_stop,
	.rcv_from_drv = llc_nop_rcv_from_drv,
	.xmit_from_hci = llc_nop_xmit_from_hci,
पूर्ण;

पूर्णांक nfc_llc_nop_रेजिस्टर(व्योम)
अणु
	वापस nfc_llc_रेजिस्टर(LLC_NOP_NAME, &llc_nop_ops);
पूर्ण
