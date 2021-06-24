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
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "fhci.h"

#घोषणा DUMMY_BD_BUFFER  0xdeadbeef
#घोषणा DUMMY2_BD_BUFFER 0xbaadf00d

/* Transaction Descriptors bits */
#घोषणा TD_R		0x8000 /* पढ़ोy bit */
#घोषणा TD_W		0x2000 /* wrap bit */
#घोषणा TD_I		0x1000 /* पूर्णांकerrupt on completion */
#घोषणा TD_L		0x0800 /* last */
#घोषणा TD_TC		0x0400 /* transmit CRC */
#घोषणा TD_CNF		0x0200 /* CNF - Must be always 1 */
#घोषणा TD_LSP		0x0100 /* Low-speed transaction */
#घोषणा TD_PID		0x00c0 /* packet id */
#घोषणा TD_RXER		0x0020 /* Rx error or not */

#घोषणा TD_NAK		0x0010 /* No ack. */
#घोषणा TD_STAL		0x0008 /* Stall received */
#घोषणा TD_TO		0x0004 /* समय out */
#घोषणा TD_UN		0x0002 /* underrun */
#घोषणा TD_NO		0x0010 /* Rx Non Octet Aligned Packet */
#घोषणा TD_AB		0x0008 /* Frame Aborted */
#घोषणा TD_CR		0x0004 /* CRC Error */
#घोषणा TD_OV		0x0002 /* Overrun */
#घोषणा TD_BOV		0x0001 /* Buffer Overrun */

#घोषणा TD_ERRORS	(TD_NAK | TD_STAL | TD_TO | TD_UN | \
			 TD_NO | TD_AB | TD_CR | TD_OV | TD_BOV)

#घोषणा TD_PID_DATA0	0x0080 /* Data 0 toggle */
#घोषणा TD_PID_DATA1	0x00c0 /* Data 1 toggle */
#घोषणा TD_PID_TOGGLE	0x00c0 /* Data 0/1 toggle mask */

#घोषणा TD_TOK_SETUP	0x0000
#घोषणा TD_TOK_OUT	0x4000
#घोषणा TD_TOK_IN	0x8000
#घोषणा TD_ISO		0x1000
#घोषणा TD_ENDP		0x0780
#घोषणा TD_ADDR		0x007f

#घोषणा TD_ENDP_SHIFT 7

काष्ठा usb_td अणु
	__be16 status;
	__be16 length;
	__be32 buf_ptr;
	__be16 extra;
	__be16 reserved;
पूर्ण;

अटल काष्ठा usb_td __iomem *next_bd(काष्ठा usb_td __iomem *base,
				      काष्ठा usb_td __iomem *td,
				      u16 status)
अणु
	अगर (status & TD_W)
		वापस base;
	अन्यथा
		वापस ++td;
पूर्ण

व्योम fhci_push_dummy_bd(काष्ठा endpoपूर्णांक *ep)
अणु
	अगर (!ep->alपढ़ोy_pushed_dummy_bd) अणु
		u16 td_status = in_be16(&ep->empty_td->status);

		out_be32(&ep->empty_td->buf_ptr, DUMMY_BD_BUFFER);
		/* get the next TD in the ring */
		ep->empty_td = next_bd(ep->td_base, ep->empty_td, td_status);
		ep->alपढ़ोy_pushed_dummy_bd = true;
	पूर्ण
पूर्ण

/* destroy an USB endpoपूर्णांक */
व्योम fhci_ep0_मुक्त(काष्ठा fhci_usb *usb)
अणु
	काष्ठा endpoपूर्णांक *ep;
	पूर्णांक size;

	ep = usb->ep0;
	अगर (ep) अणु
		अगर (ep->td_base)
			cpm_muram_मुक्त(cpm_muram_offset(ep->td_base));

		अगर (kfअगरo_initialized(&ep->conf_frame_Q)) अणु
			size = cq_howmany(&ep->conf_frame_Q);
			क्रम (; size; size--) अणु
				काष्ठा packet *pkt = cq_get(&ep->conf_frame_Q);

				kमुक्त(pkt);
			पूर्ण
			cq_delete(&ep->conf_frame_Q);
		पूर्ण

		अगर (kfअगरo_initialized(&ep->empty_frame_Q)) अणु
			size = cq_howmany(&ep->empty_frame_Q);
			क्रम (; size; size--) अणु
				काष्ठा packet *pkt = cq_get(&ep->empty_frame_Q);

				kमुक्त(pkt);
			पूर्ण
			cq_delete(&ep->empty_frame_Q);
		पूर्ण

		अगर (kfअगरo_initialized(&ep->dummy_packets_Q)) अणु
			size = cq_howmany(&ep->dummy_packets_Q);
			क्रम (; size; size--) अणु
				u8 *buff = cq_get(&ep->dummy_packets_Q);

				kमुक्त(buff);
			पूर्ण
			cq_delete(&ep->dummy_packets_Q);
		पूर्ण

		kमुक्त(ep);
		usb->ep0 = शून्य;
	पूर्ण
पूर्ण

/*
 * create the endpoपूर्णांक काष्ठाure
 *
 * arguments:
 * usb		A poपूर्णांकer to the data काष्ठाure of the USB
 * data_mem	The data memory partition(BUS)
 * ring_len	TD ring length
 */
u32 fhci_create_ep(काष्ठा fhci_usb *usb, क्रमागत fhci_mem_alloc data_mem,
			   u32 ring_len)
अणु
	काष्ठा endpoपूर्णांक *ep;
	काष्ठा usb_td __iomem *td;
	अचिन्हित दीर्घ ep_offset;
	अक्षर *err_क्रम = "endpoint PRAM";
	पूर्णांक ep_mem_size;
	u32 i;

	/* we need at least 3 TDs in the ring */
	अगर (!(ring_len > 2)) अणु
		fhci_err(usb->fhci, "illegal TD ring length parameters\n");
		वापस -EINVAL;
	पूर्ण

	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep_mem_size = ring_len * माप(*td) + माप(काष्ठा fhci_ep_pram);
	ep_offset = cpm_muram_alloc(ep_mem_size, 32);
	अगर (IS_ERR_VALUE(ep_offset))
		जाओ err;
	ep->td_base = cpm_muram_addr(ep_offset);

	/* zero all queue poपूर्णांकers */
	अगर (cq_new(&ep->conf_frame_Q, ring_len + 2) ||
	    cq_new(&ep->empty_frame_Q, ring_len + 2) ||
	    cq_new(&ep->dummy_packets_Q, ring_len + 2)) अणु
		err_क्रम = "frame_queues";
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < (ring_len + 1); i++) अणु
		काष्ठा packet *pkt;
		u8 *buff;

		pkt = kदो_स्मृति(माप(*pkt), GFP_KERNEL);
		अगर (!pkt) अणु
			err_क्रम = "frame";
			जाओ err;
		पूर्ण

		buff = kदो_स्मृति_array(1028, माप(*buff), GFP_KERNEL);
		अगर (!buff) अणु
			kमुक्त(pkt);
			err_क्रम = "buffer";
			जाओ err;
		पूर्ण
		cq_put(&ep->empty_frame_Q, pkt);
		cq_put(&ep->dummy_packets_Q, buff);
	पूर्ण

	/* we put the endpoपूर्णांक parameter RAM right behind the TD ring */
	ep->ep_pram_ptr = (व्योम __iomem *)ep->td_base + माप(*td) * ring_len;

	ep->conf_td = ep->td_base;
	ep->empty_td = ep->td_base;

	ep->alपढ़ोy_pushed_dummy_bd = false;

	/* initialize tds */
	td = ep->td_base;
	क्रम (i = 0; i < ring_len; i++) अणु
		out_be32(&td->buf_ptr, 0);
		out_be16(&td->status, 0);
		out_be16(&td->length, 0);
		out_be16(&td->extra, 0);
		td++;
	पूर्ण
	td--;
	out_be16(&td->status, TD_W); /* क्रम last TD set Wrap bit */
	out_be16(&td->length, 0);

	/* endpoपूर्णांक काष्ठाure has been created */
	usb->ep0 = ep;

	वापस 0;
err:
	fhci_ep0_मुक्त(usb);
	kमुक्त(ep);
	fhci_err(usb->fhci, "no memory for the %s\n", err_क्रम);
	वापस -ENOMEM;
पूर्ण

/*
 * initialize the endpoपूर्णांक रेजिस्टर according to the given parameters
 *
 * artuments:
 * usb		A poपूर्णांकer to the data strucutre of the USB
 * ep		A poपूर्णांकer to the endpoपूर्णांक काष्ठाre
 * data_mem	The data memory partition(BUS)
 */
व्योम fhci_init_ep_रेजिस्टरs(काष्ठा fhci_usb *usb, काष्ठा endpoपूर्णांक *ep,
			    क्रमागत fhci_mem_alloc data_mem)
अणु
	u8 rt;

	/* set the endpoपूर्णांक रेजिस्टरs according to the endpoपूर्णांक */
	out_be16(&usb->fhci->regs->usb_usep[0],
		 USB_TRANS_CTR | USB_EP_MF | USB_EP_RTE);
	out_be16(&usb->fhci->pram->ep_ptr[0],
		 cpm_muram_offset(ep->ep_pram_ptr));

	rt = (BUS_MODE_BO_BE | BUS_MODE_GBL);
#अगर_घोषित MULTI_DATA_BUS
	अगर (data_mem == MEM_SECONDARY)
		rt |= BUS_MODE_DTB;
#पूर्ण_अगर
	out_8(&ep->ep_pram_ptr->rx_func_code, rt);
	out_8(&ep->ep_pram_ptr->tx_func_code, rt);
	out_be16(&ep->ep_pram_ptr->rx_buff_len, 1028);
	out_be16(&ep->ep_pram_ptr->rx_base, 0);
	out_be16(&ep->ep_pram_ptr->tx_base, cpm_muram_offset(ep->td_base));
	out_be16(&ep->ep_pram_ptr->rx_bd_ptr, 0);
	out_be16(&ep->ep_pram_ptr->tx_bd_ptr, cpm_muram_offset(ep->td_base));
	out_be32(&ep->ep_pram_ptr->tx_state, 0);
पूर्ण

/*
 * Collect the submitted frames and inक्रमm the application about them
 * It is also preparing the TDs क्रम new frames. If the Tx पूर्णांकerrupts
 * are disabled, the application should call that routine to get
 * confirmation about the submitted frames. Otherwise, the routine is
 * called from the पूर्णांकerrupt service routine during the Tx पूर्णांकerrupt.
 * In that हाल the application is inक्रमmed by calling the application
 * specअगरic 'fhci_transaction_confirm' routine
 */
अटल व्योम fhci_td_transaction_confirm(काष्ठा fhci_usb *usb)
अणु
	काष्ठा endpoपूर्णांक *ep = usb->ep0;
	काष्ठा packet *pkt;
	काष्ठा usb_td __iomem *td;
	u16 extra_data;
	u16 td_status;
	u16 td_length;
	u32 buf;

	/*
	 * collect transmitted BDs from the chip. The routine clears all BDs
	 * with R bit = 0 and the poपूर्णांकer to data buffer is not शून्य, that is
	 * BDs which poपूर्णांक to the transmitted data buffer
	 */
	जबतक (1) अणु
		td = ep->conf_td;
		td_status = in_be16(&td->status);
		td_length = in_be16(&td->length);
		buf = in_be32(&td->buf_ptr);
		extra_data = in_be16(&td->extra);

		/* check अगर the TD is empty */
		अगर (!(!(td_status & TD_R) && ((td_status & ~TD_W) || buf)))
			अवरोध;
		/* check अगर it is a dummy buffer */
		अन्यथा अगर ((buf == DUMMY_BD_BUFFER) && !(td_status & ~TD_W))
			अवरोध;

		/* mark TD as empty */
		clrbits16(&td->status, ~TD_W);
		out_be16(&td->length, 0);
		out_be32(&td->buf_ptr, 0);
		out_be16(&td->extra, 0);
		/* advance the TD poपूर्णांकer */
		ep->conf_td = next_bd(ep->td_base, ep->conf_td, td_status);

		/* check अगर it is a dummy buffer(type2) */
		अगर ((buf == DUMMY2_BD_BUFFER) && !(td_status & ~TD_W))
			जारी;

		pkt = cq_get(&ep->conf_frame_Q);
		अगर (!pkt)
			fhci_err(usb->fhci, "no frame to confirm\n");

		अगर (td_status & TD_ERRORS) अणु
			अगर (td_status & TD_RXER) अणु
				अगर (td_status & TD_CR)
					pkt->status = USB_TD_RX_ER_CRC;
				अन्यथा अगर (td_status & TD_AB)
					pkt->status = USB_TD_RX_ER_BITSTUFF;
				अन्यथा अगर (td_status & TD_OV)
					pkt->status = USB_TD_RX_ER_OVERUN;
				अन्यथा अगर (td_status & TD_BOV)
					pkt->status = USB_TD_RX_DATA_OVERUN;
				अन्यथा अगर (td_status & TD_NO)
					pkt->status = USB_TD_RX_ER_NONOCT;
				अन्यथा
					fhci_err(usb->fhci, "illegal error "
						 "occurred\n");
			पूर्ण अन्यथा अगर (td_status & TD_NAK)
				pkt->status = USB_TD_TX_ER_NAK;
			अन्यथा अगर (td_status & TD_TO)
				pkt->status = USB_TD_TX_ER_TIMEOUT;
			अन्यथा अगर (td_status & TD_UN)
				pkt->status = USB_TD_TX_ER_UNDERUN;
			अन्यथा अगर (td_status & TD_STAL)
				pkt->status = USB_TD_TX_ER_STALL;
			अन्यथा
				fhci_err(usb->fhci, "illegal error occurred\n");
		पूर्ण अन्यथा अगर ((extra_data & TD_TOK_IN) &&
				pkt->len > td_length - CRC_SIZE) अणु
			pkt->status = USB_TD_RX_DATA_UNDERUN;
		पूर्ण

		अगर (extra_data & TD_TOK_IN)
			pkt->len = td_length - CRC_SIZE;
		अन्यथा अगर (pkt->info & PKT_ZLP)
			pkt->len = 0;
		अन्यथा
			pkt->len = td_length;

		fhci_transaction_confirm(usb, pkt);
	पूर्ण
पूर्ण

/*
 * Submitting a data frame to a specअगरied endpoपूर्णांक of a USB device
 * The frame is put in the driver's transmit queue क्रम this endpoपूर्णांक
 *
 * Arguments:
 * usb          A poपूर्णांकer to the USB काष्ठाure
 * pkt          A poपूर्णांकer to the user frame काष्ठाure
 * trans_type   Transaction tyep - IN,OUT or SETUP
 * dest_addr    Device address - 0~127
 * dest_ep      Endpoपूर्णांक number of the device - 0~16
 * trans_mode   Pipe type - ISO,Interrupt,bulk or control
 * dest_speed   USB speed - Low speed or FULL speed
 * data_toggle  Data sequence toggle - 0 or 1
 */
u32 fhci_host_transaction(काष्ठा fhci_usb *usb,
			  काष्ठा packet *pkt,
			  क्रमागत fhci_ta_type trans_type,
			  u8 dest_addr,
			  u8 dest_ep,
			  क्रमागत fhci_tf_mode trans_mode,
			  क्रमागत fhci_speed dest_speed, u8 data_toggle)
अणु
	काष्ठा endpoपूर्णांक *ep = usb->ep0;
	काष्ठा usb_td __iomem *td;
	u16 extra_data;
	u16 td_status;

	fhci_usb_disable_पूर्णांकerrupt(usb);
	/* start from the next BD that should be filled */
	td = ep->empty_td;
	td_status = in_be16(&td->status);

	अगर (td_status & TD_R && in_be16(&td->length)) अणु
		/* अगर the TD is not मुक्त */
		fhci_usb_enable_पूर्णांकerrupt(usb);
		वापस -1;
	पूर्ण

	/* get the next TD in the ring */
	ep->empty_td = next_bd(ep->td_base, ep->empty_td, td_status);
	fhci_usb_enable_पूर्णांकerrupt(usb);
	pkt->priv_data = td;
	out_be32(&td->buf_ptr, virt_to_phys(pkt->data));
	/* sets up transaction parameters - addr,endp,dir,and type */
	extra_data = (dest_ep << TD_ENDP_SHIFT) | dest_addr;
	चयन (trans_type) अणु
	हाल FHCI_TA_IN:
		extra_data |= TD_TOK_IN;
		अवरोध;
	हाल FHCI_TA_OUT:
		extra_data |= TD_TOK_OUT;
		अवरोध;
	हाल FHCI_TA_SETUP:
		extra_data |= TD_TOK_SETUP;
		अवरोध;
	पूर्ण
	अगर (trans_mode == FHCI_TF_ISO)
		extra_data |= TD_ISO;
	out_be16(&td->extra, extra_data);

	/* sets up the buffer descriptor */
	td_status = ((td_status & TD_W) | TD_R | TD_L | TD_I | TD_CNF);
	अगर (!(pkt->info & PKT_NO_CRC))
		td_status |= TD_TC;

	चयन (trans_type) अणु
	हाल FHCI_TA_IN:
		अगर (data_toggle)
			pkt->info |= PKT_PID_DATA1;
		अन्यथा
			pkt->info |= PKT_PID_DATA0;
		अवरोध;
	शेष:
		अगर (data_toggle) अणु
			td_status |= TD_PID_DATA1;
			pkt->info |= PKT_PID_DATA1;
		पूर्ण अन्यथा अणु
			td_status |= TD_PID_DATA0;
			pkt->info |= PKT_PID_DATA0;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर ((dest_speed == FHCI_LOW_SPEED) &&
	    (usb->port_status == FHCI_PORT_FULL))
		td_status |= TD_LSP;

	out_be16(&td->status, td_status);

	/* set up buffer length */
	अगर (trans_type == FHCI_TA_IN)
		out_be16(&td->length, pkt->len + CRC_SIZE);
	अन्यथा
		out_be16(&td->length, pkt->len);

	/* put the frame to the confirmation queue */
	cq_put(&ep->conf_frame_Q, pkt);

	अगर (cq_howmany(&ep->conf_frame_Q) == 1)
		out_8(&usb->fhci->regs->usb_uscom, USB_CMD_STR_FIFO);

	वापस 0;
पूर्ण

/* Reset the Tx BD ring */
व्योम fhci_flush_bds(काष्ठा fhci_usb *usb)
अणु
	u16 td_status;
	काष्ठा usb_td __iomem *td;
	काष्ठा endpoपूर्णांक *ep = usb->ep0;

	td = ep->td_base;
	जबतक (1) अणु
		td_status = in_be16(&td->status);
		in_be32(&td->buf_ptr);
		in_be16(&td->extra);

		/* अगर the TD is not empty - we'll confirm it as Timeout */
		अगर (td_status & TD_R)
			out_be16(&td->status, (td_status & ~TD_R) | TD_TO);
		/* अगर this TD is dummy - let's skip this TD */
		अन्यथा अगर (in_be32(&td->buf_ptr) == DUMMY_BD_BUFFER)
			out_be32(&td->buf_ptr, DUMMY2_BD_BUFFER);
		/* अगर this is the last TD - अवरोध */
		अगर (td_status & TD_W)
			अवरोध;

		td++;
	पूर्ण

	fhci_td_transaction_confirm(usb);

	td = ep->td_base;
	करो अणु
		out_be16(&td->status, 0);
		out_be16(&td->length, 0);
		out_be32(&td->buf_ptr, 0);
		out_be16(&td->extra, 0);
		td++;
	पूर्ण जबतक (!(in_be16(&td->status) & TD_W));
	out_be16(&td->status, TD_W); /* क्रम last TD set Wrap bit */
	out_be16(&td->length, 0);
	out_be32(&td->buf_ptr, 0);
	out_be16(&td->extra, 0);

	out_be16(&ep->ep_pram_ptr->tx_bd_ptr,
		 in_be16(&ep->ep_pram_ptr->tx_base));
	out_be32(&ep->ep_pram_ptr->tx_state, 0);
	out_be16(&ep->ep_pram_ptr->tx_cnt, 0);
	ep->empty_td = ep->td_base;
	ep->conf_td = ep->td_base;
पूर्ण

/*
 * Flush all transmitted packets from TDs in the actual frame.
 * This routine is called when something wrong with the controller and
 * we want to get rid of the actual frame and start again next frame
 */
व्योम fhci_flush_actual_frame(काष्ठा fhci_usb *usb)
अणु
	u8 mode;
	u16 tb_ptr;
	u16 td_status;
	u32 buf_ptr;
	काष्ठा usb_td __iomem *td;
	काष्ठा endpoपूर्णांक *ep = usb->ep0;

	/* disable the USB controller */
	mode = in_8(&usb->fhci->regs->usb_usmod);
	out_8(&usb->fhci->regs->usb_usmod, mode & ~USB_MODE_EN);

	tb_ptr = in_be16(&ep->ep_pram_ptr->tx_bd_ptr);
	td = cpm_muram_addr(tb_ptr);
	td_status = in_be16(&td->status);
	buf_ptr = in_be32(&td->buf_ptr);
	in_be16(&td->extra);
	करो अणु
		अगर (td_status & TD_R) अणु
			out_be16(&td->status, (td_status & ~TD_R) | TD_TO);
		पूर्ण अन्यथा अणु
			out_be32(&td->buf_ptr, 0);
			ep->alपढ़ोy_pushed_dummy_bd = false;
			अवरोध;
		पूर्ण

		/* advance the TD poपूर्णांकer */
		td = next_bd(ep->td_base, td, td_status);
		td_status = in_be16(&td->status);
		buf_ptr = in_be32(&td->buf_ptr);
		in_be16(&td->extra);
	पूर्ण जबतक ((td_status & TD_R) || buf_ptr);

	fhci_td_transaction_confirm(usb);

	out_be16(&ep->ep_pram_ptr->tx_bd_ptr,
		 in_be16(&ep->ep_pram_ptr->tx_base));
	out_be32(&ep->ep_pram_ptr->tx_state, 0);
	out_be16(&ep->ep_pram_ptr->tx_cnt, 0);
	ep->empty_td = ep->td_base;
	ep->conf_td = ep->td_base;

	usb->actual_frame->frame_status = FRAME_TIMER_END_TRANSMISSION;

	/* reset the event रेजिस्टर */
	out_be16(&usb->fhci->regs->usb_usber, 0xffff);
	/* enable the USB controller */
	out_8(&usb->fhci->regs->usb_usmod, mode | USB_MODE_EN);
पूर्ण

/* handles Tx confirm and Tx error पूर्णांकerrupt */
व्योम fhci_tx_conf_पूर्णांकerrupt(काष्ठा fhci_usb *usb)
अणु
	fhci_td_transaction_confirm(usb);

	/*
	 * Schedule another transaction to this frame only अगर we have
	 * alपढ़ोy confirmed all transaction in the frame.
	 */
	अगर (((fhci_get_sof_समयr_count(usb) < usb->max_frame_usage) ||
	     (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION)) &&
	    (list_empty(&usb->actual_frame->tds_list)))
		fhci_schedule_transactions(usb);
पूर्ण

व्योम fhci_host_transmit_actual_frame(काष्ठा fhci_usb *usb)
अणु
	u16 tb_ptr;
	u16 td_status;
	काष्ठा usb_td __iomem *td;
	काष्ठा endpoपूर्णांक *ep = usb->ep0;

	tb_ptr = in_be16(&ep->ep_pram_ptr->tx_bd_ptr);
	td = cpm_muram_addr(tb_ptr);

	अगर (in_be32(&td->buf_ptr) == DUMMY_BD_BUFFER) अणु
		काष्ठा usb_td __iomem *old_td = td;

		ep->alपढ़ोy_pushed_dummy_bd = false;
		td_status = in_be16(&td->status);
		/* माला_लो the next TD in the ring */
		td = next_bd(ep->td_base, td, td_status);
		tb_ptr = cpm_muram_offset(td);
		out_be16(&ep->ep_pram_ptr->tx_bd_ptr, tb_ptr);

		/* start transmit only अगर we have something in the TDs */
		अगर (in_be16(&td->status) & TD_R)
			out_8(&usb->fhci->regs->usb_uscom, USB_CMD_STR_FIFO);

		अगर (in_be32(&ep->conf_td->buf_ptr) == DUMMY_BD_BUFFER) अणु
			out_be32(&old_td->buf_ptr, 0);
			ep->conf_td = next_bd(ep->td_base, ep->conf_td,
					      td_status);
		पूर्ण अन्यथा अणु
			out_be32(&old_td->buf_ptr, DUMMY2_BD_BUFFER);
		पूर्ण
	पूर्ण
पूर्ण
