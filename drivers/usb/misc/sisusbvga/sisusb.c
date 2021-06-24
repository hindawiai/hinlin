<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * sisusb - usb kernel driver क्रम SiS315(E) based USB2VGA करोngles
 *
 * Main part
 *
 * Copyright (C) 2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, this code is licensed under the
 * terms of the GPL v2.
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary क्रमms, with or without
 * * modअगरication, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary क्रमm must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    करोcumentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to enकरोrse or promote products
 * *    derived from this software without specअगरic psisusbr written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESSED OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "sisusb.h"
#समावेश "sisusb_init.h"

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
#समावेश <linux/font.h>
#पूर्ण_अगर

#घोषणा SISUSB_DONTSYNC

/* Forward declarations / clean-up routines */

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
अटल पूर्णांक sisusb_first_vc;
अटल पूर्णांक sisusb_last_vc;
module_param_named(first, sisusb_first_vc, पूर्णांक, 0);
module_param_named(last, sisusb_last_vc, पूर्णांक, 0);
MODULE_PARM_DESC(first, "Number of first console to take over (1 - MAX_NR_CONSOLES)");
MODULE_PARM_DESC(last, "Number of last console to take over (1 - MAX_NR_CONSOLES)");
#पूर्ण_अगर

अटल काष्ठा usb_driver sisusb_driver;

अटल व्योम sisusb_मुक्त_buffers(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUMOBUFS; i++) अणु
		kमुक्त(sisusb->obuf[i]);
		sisusb->obuf[i] = शून्य;
	पूर्ण
	kमुक्त(sisusb->ibuf);
	sisusb->ibuf = शून्य;
पूर्ण

अटल व्योम sisusb_मुक्त_urbs(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUMOBUFS; i++) अणु
		usb_मुक्त_urb(sisusb->sisurbout[i]);
		sisusb->sisurbout[i] = शून्य;
	पूर्ण
	usb_मुक्त_urb(sisusb->sisurbin);
	sisusb->sisurbin = शून्य;
पूर्ण

/* Level 0: USB transport layer */

/* 1. out-bulks */

/* out-urb management */

/* Return 1 अगर all मुक्त, 0 otherwise */
अटल पूर्णांक sisusb_all_मुक्त(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sisusb->numobufs; i++) अणु

		अगर (sisusb->urbstatus[i] & SU_URB_BUSY)
			वापस 0;

	पूर्ण

	वापस 1;
पूर्ण

/* Kill all busy URBs */
अटल व्योम sisusb_समाप्त_all_busy(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	अगर (sisusb_all_मुक्त(sisusb))
		वापस;

	क्रम (i = 0; i < sisusb->numobufs; i++) अणु

		अगर (sisusb->urbstatus[i] & SU_URB_BUSY)
			usb_समाप्त_urb(sisusb->sisurbout[i]);

	पूर्ण
पूर्ण

/* Return 1 अगर ok, 0 अगर error (not all complete within समयout) */
अटल पूर्णांक sisusb_रुको_all_out_complete(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक समयout = 5 * HZ, i = 1;

	रुको_event_समयout(sisusb->रुको_q, (i = sisusb_all_मुक्त(sisusb)),
			समयout);

	वापस i;
पूर्ण

अटल पूर्णांक sisusb_outurb_available(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sisusb->numobufs; i++) अणु

		अगर ((sisusb->urbstatus[i] & (SU_URB_BUSY|SU_URB_ALLOC)) == 0)
			वापस i;

	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक sisusb_get_मुक्त_outbuf(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i, समयout = 5 * HZ;

	रुको_event_समयout(sisusb->रुको_q,
			((i = sisusb_outurb_available(sisusb)) >= 0), समयout);

	वापस i;
पूर्ण

अटल पूर्णांक sisusb_alloc_outbuf(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	i = sisusb_outurb_available(sisusb);

	अगर (i >= 0)
		sisusb->urbstatus[i] |= SU_URB_ALLOC;

	वापस i;
पूर्ण

अटल व्योम sisusb_मुक्त_outbuf(काष्ठा sisusb_usb_data *sisusb, पूर्णांक index)
अणु
	अगर ((index >= 0) && (index < sisusb->numobufs))
		sisusb->urbstatus[index] &= ~SU_URB_ALLOC;
पूर्ण

/* completion callback */

अटल व्योम sisusb_bulk_completeout(काष्ठा urb *urb)
अणु
	काष्ठा sisusb_urb_context *context = urb->context;
	काष्ठा sisusb_usb_data *sisusb;

	अगर (!context)
		वापस;

	sisusb = context->sisusb;

	अगर (!sisusb || !sisusb->sisusb_dev || !sisusb->present)
		वापस;

#अगर_अघोषित SISUSB_DONTSYNC
	अगर (context->actual_length)
		*(context->actual_length) += urb->actual_length;
#पूर्ण_अगर

	sisusb->urbstatus[context->urbindex] &= ~SU_URB_BUSY;
	wake_up(&sisusb->रुको_q);
पूर्ण

अटल पूर्णांक sisusb_bulkout_msg(काष्ठा sisusb_usb_data *sisusb, पूर्णांक index,
		अचिन्हित पूर्णांक pipe, व्योम *data, पूर्णांक len, पूर्णांक *actual_length,
		पूर्णांक समयout, अचिन्हित पूर्णांक tflags)
अणु
	काष्ठा urb *urb = sisusb->sisurbout[index];
	पूर्णांक retval, byteswritten = 0;

	/* Set up URB */
	urb->transfer_flags = 0;

	usb_fill_bulk_urb(urb, sisusb->sisusb_dev, pipe, data, len,
			sisusb_bulk_completeout,
			&sisusb->urbout_context[index]);

	urb->transfer_flags |= tflags;
	urb->actual_length = 0;

	/* Set up context */
	sisusb->urbout_context[index].actual_length = (समयout) ?
			शून्य : actual_length;

	/* Declare this urb/buffer in use */
	sisusb->urbstatus[index] |= SU_URB_BUSY;

	/* Submit URB */
	retval = usb_submit_urb(urb, GFP_KERNEL);

	/* If OK, and अगर समयout > 0, रुको क्रम completion */
	अगर ((retval == 0) && समयout) अणु
		रुको_event_समयout(sisusb->रुको_q,
				(!(sisusb->urbstatus[index] & SU_URB_BUSY)),
				समयout);
		अगर (sisusb->urbstatus[index] & SU_URB_BUSY) अणु
			/* URB समयd out... समाप्त it and report error */
			usb_समाप्त_urb(urb);
			retval = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			/* Otherwise, report urb status */
			retval = urb->status;
			byteswritten = urb->actual_length;
		पूर्ण
	पूर्ण

	अगर (actual_length)
		*actual_length = byteswritten;

	वापस retval;
पूर्ण

/* 2. in-bulks */

/* completion callback */

अटल व्योम sisusb_bulk_completein(काष्ठा urb *urb)
अणु
	काष्ठा sisusb_usb_data *sisusb = urb->context;

	अगर (!sisusb || !sisusb->sisusb_dev || !sisusb->present)
		वापस;

	sisusb->completein = 1;
	wake_up(&sisusb->रुको_q);
पूर्ण

अटल पूर्णांक sisusb_bulkin_msg(काष्ठा sisusb_usb_data *sisusb,
		अचिन्हित पूर्णांक pipe, व्योम *data, पूर्णांक len,
		पूर्णांक *actual_length, पूर्णांक समयout, अचिन्हित पूर्णांक tflags)
अणु
	काष्ठा urb *urb = sisusb->sisurbin;
	पूर्णांक retval, पढ़ोbytes = 0;

	urb->transfer_flags = 0;

	usb_fill_bulk_urb(urb, sisusb->sisusb_dev, pipe, data, len,
			sisusb_bulk_completein, sisusb);

	urb->transfer_flags |= tflags;
	urb->actual_length = 0;

	sisusb->completein = 0;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval == 0) अणु
		रुको_event_समयout(sisusb->रुको_q, sisusb->completein, समयout);
		अगर (!sisusb->completein) अणु
			/* URB समयd out... समाप्त it and report error */
			usb_समाप्त_urb(urb);
			retval = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			/* URB completed within समयout */
			retval = urb->status;
			पढ़ोbytes = urb->actual_length;
		पूर्ण
	पूर्ण

	अगर (actual_length)
		*actual_length = पढ़ोbytes;

	वापस retval;
पूर्ण


/* Level 1:  */

/* Send a bulk message of variable size
 *
 * To copy the data from userspace, give poपूर्णांकer to "userbuffer",
 * to copy from (non-DMA) kernel memory, give "kernbuffer". If
 * both of these are शून्य, it is assumed, that the transfer
 * buffer "sisusb->obuf[index]" is set up with the data to send.
 * Index is ignored अगर either kernbuffer or userbuffer is set.
 * If async is nonzero, URBs will be sent without रुकोing क्रम
 * completion of the previous URB.
 *
 * (वापस 0 on success)
 */

अटल पूर्णांक sisusb_send_bulk_msg(काष्ठा sisusb_usb_data *sisusb, पूर्णांक ep, पूर्णांक len,
		अक्षर *kernbuffer, स्थिर अक्षर __user *userbuffer, पूर्णांक index,
		sमाप_प्रकार *bytes_written, अचिन्हित पूर्णांक tflags, पूर्णांक async)
अणु
	पूर्णांक result = 0, retry, count = len;
	पूर्णांक passsize, thispass, transferred_len = 0;
	पूर्णांक fromuser = (userbuffer != शून्य) ? 1 : 0;
	पूर्णांक fromkern = (kernbuffer != शून्य) ? 1 : 0;
	अचिन्हित पूर्णांक pipe;
	अक्षर *buffer;

	(*bytes_written) = 0;

	/* Sanity check */
	अगर (!sisusb || !sisusb->present || !sisusb->sisusb_dev)
		वापस -ENODEV;

	/* If we copy data from kernel or userspace, क्रमce the
	 * allocation of a buffer/urb. If we have the data in
	 * the transfer buffer[index] alपढ़ोy, reuse the buffer/URB
	 * अगर the length is > buffer size. (So, transmitting
	 * large data amounts directly from the transfer buffer
	 * treats the buffer as a ring buffer. However, we need
	 * to sync in this हाल.)
	 */
	अगर (fromuser || fromkern)
		index = -1;
	अन्यथा अगर (len > sisusb->obufsize)
		async = 0;

	pipe = usb_sndbulkpipe(sisusb->sisusb_dev, ep);

	करो अणु
		passsize = thispass = (sisusb->obufsize < count) ?
				sisusb->obufsize : count;

		अगर (index < 0)
			index = sisusb_get_मुक्त_outbuf(sisusb);

		अगर (index < 0)
			वापस -EIO;

		buffer = sisusb->obuf[index];

		अगर (fromuser) अणु

			अगर (copy_from_user(buffer, userbuffer, passsize))
				वापस -EFAULT;

			userbuffer += passsize;

		पूर्ण अन्यथा अगर (fromkern) अणु

			स_नकल(buffer, kernbuffer, passsize);
			kernbuffer += passsize;

		पूर्ण

		retry = 5;
		जबतक (thispass) अणु

			अगर (!sisusb->sisusb_dev)
				वापस -ENODEV;

			result = sisusb_bulkout_msg(sisusb, index, pipe,
					buffer, thispass, &transferred_len,
					async ? 0 : 5 * HZ, tflags);

			अगर (result == -ETIMEDOUT) अणु

				/* Will not happen अगर async */
				अगर (!retry--)
					वापस -ETIME;

				जारी;
			पूर्ण

			अगर ((result == 0) && !async && transferred_len) अणु

				thispass -= transferred_len;
				buffer += transferred_len;

			पूर्ण अन्यथा
				अवरोध;
		पूर्ण

		अगर (result)
			वापस result;

		(*bytes_written) += passsize;
		count            -= passsize;

		/* Force new allocation in next iteration */
		अगर (fromuser || fromkern)
			index = -1;

	पूर्ण जबतक (count > 0);

	अगर (async) अणु
#अगर_घोषित SISUSB_DONTSYNC
		(*bytes_written) = len;
		/* Some URBs/buffers might be busy */
#अन्यथा
		sisusb_रुको_all_out_complete(sisusb);
		(*bytes_written) = transferred_len;
		/* All URBs and all buffers are available */
#पूर्ण_अगर
	पूर्ण

	वापस ((*bytes_written) == len) ? 0 : -EIO;
पूर्ण

/* Receive a bulk message of variable size
 *
 * To copy the data to userspace, give poपूर्णांकer to "userbuffer",
 * to copy to kernel memory, give "kernbuffer". One of them
 * MUST be set. (There is no technique क्रम letting the caller
 * पढ़ो directly from the ibuf.)
 *
 */

अटल पूर्णांक sisusb_recv_bulk_msg(काष्ठा sisusb_usb_data *sisusb, पूर्णांक ep, पूर्णांक len,
		व्योम *kernbuffer, अक्षर __user *userbuffer, sमाप_प्रकार *bytes_पढ़ो,
		अचिन्हित पूर्णांक tflags)
अणु
	पूर्णांक result = 0, retry, count = len;
	पूर्णांक bufsize, thispass, transferred_len;
	अचिन्हित पूर्णांक pipe;
	अक्षर *buffer;

	(*bytes_पढ़ो) = 0;

	/* Sanity check */
	अगर (!sisusb || !sisusb->present || !sisusb->sisusb_dev)
		वापस -ENODEV;

	pipe = usb_rcvbulkpipe(sisusb->sisusb_dev, ep);
	buffer = sisusb->ibuf;
	bufsize = sisusb->ibufsize;

	retry = 5;

#अगर_घोषित SISUSB_DONTSYNC
	अगर (!(sisusb_रुको_all_out_complete(sisusb)))
		वापस -EIO;
#पूर्ण_अगर

	जबतक (count > 0) अणु

		अगर (!sisusb->sisusb_dev)
			वापस -ENODEV;

		thispass = (bufsize < count) ? bufsize : count;

		result = sisusb_bulkin_msg(sisusb, pipe, buffer, thispass,
				&transferred_len, 5 * HZ, tflags);

		अगर (transferred_len)
			thispass = transferred_len;

		अन्यथा अगर (result == -ETIMEDOUT) अणु

			अगर (!retry--)
				वापस -ETIME;

			जारी;

		पूर्ण अन्यथा
			वापस -EIO;


		अगर (thispass) अणु

			(*bytes_पढ़ो) += thispass;
			count         -= thispass;

			अगर (userbuffer) अणु

				अगर (copy_to_user(userbuffer, buffer, thispass))
					वापस -EFAULT;

				userbuffer += thispass;

			पूर्ण अन्यथा अणु

				स_नकल(kernbuffer, buffer, thispass);
				kernbuffer += thispass;

			पूर्ण

		पूर्ण

	पूर्ण

	वापस ((*bytes_पढ़ो) == len) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक sisusb_send_packet(काष्ठा sisusb_usb_data *sisusb, पूर्णांक len,
		काष्ठा sisusb_packet *packet)
अणु
	पूर्णांक ret;
	sमाप_प्रकार bytes_transferred = 0;
	__le32 पंचांगp;

	अगर (len == 6)
		packet->data = 0;

#अगर_घोषित SISUSB_DONTSYNC
	अगर (!(sisusb_रुको_all_out_complete(sisusb)))
		वापस 1;
#पूर्ण_अगर

	/* Eventually correct endianness */
	SISUSB_CORRECT_ENDIANNESS_PACKET(packet);

	/* 1. send the packet */
	ret = sisusb_send_bulk_msg(sisusb, SISUSB_EP_GFX_OUT, len,
			(अक्षर *)packet, शून्य, 0, &bytes_transferred, 0, 0);

	अगर ((ret == 0) && (len == 6)) अणु

		/* 2. अगर packet len == 6, it means we पढ़ो, so रुको क्रम 32bit
		 *    वापस value and ग_लिखो it to packet->data
		 */
		ret = sisusb_recv_bulk_msg(sisusb, SISUSB_EP_GFX_IN, 4,
				(अक्षर *)&पंचांगp, शून्य, &bytes_transferred, 0);

		packet->data = le32_to_cpu(पंचांगp);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_send_bridge_packet(काष्ठा sisusb_usb_data *sisusb, पूर्णांक len,
		काष्ठा sisusb_packet *packet, अचिन्हित पूर्णांक tflags)
अणु
	पूर्णांक ret;
	sमाप_प्रकार bytes_transferred = 0;
	__le32 पंचांगp;

	अगर (len == 6)
		packet->data = 0;

#अगर_घोषित SISUSB_DONTSYNC
	अगर (!(sisusb_रुको_all_out_complete(sisusb)))
		वापस 1;
#पूर्ण_अगर

	/* Eventually correct endianness */
	SISUSB_CORRECT_ENDIANNESS_PACKET(packet);

	/* 1. send the packet */
	ret = sisusb_send_bulk_msg(sisusb, SISUSB_EP_BRIDGE_OUT, len,
			(अक्षर *)packet, शून्य, 0, &bytes_transferred, tflags, 0);

	अगर ((ret == 0) && (len == 6)) अणु

		/* 2. अगर packet len == 6, it means we पढ़ो, so रुको क्रम 32bit
		 *    वापस value and ग_लिखो it to packet->data
		 */
		ret = sisusb_recv_bulk_msg(sisusb, SISUSB_EP_BRIDGE_IN, 4,
				(अक्षर *)&पंचांगp, शून्य, &bytes_transferred, 0);

		packet->data = le32_to_cpu(पंचांगp);
	पूर्ण

	वापस ret;
पूर्ण

/* access video memory and mmio (वापस 0 on success) */

/* Low level */

/* The following routines assume being used to transfer byte, word,
 * दीर्घ etc.
 * This means that
 *   - the ग_लिखो routines expect "data" in machine endianness क्रमmat.
 *     The data will be converted to leXX in sisusb_xxx_packet.
 *   - the पढ़ो routines can expect पढ़ो data in machine-endianess.
 */

अटल पूर्णांक sisusb_ग_लिखो_memio_byte(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u8 data)
अणु
	काष्ठा sisusb_packet packet;

	packet.header  = (1 << (addr & 3)) | (type << 6);
	packet.address = addr & ~3;
	packet.data    = data << ((addr & 3) << 3);
	वापस sisusb_send_packet(sisusb, 10, &packet);
पूर्ण

अटल पूर्णांक sisusb_ग_लिखो_memio_word(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u16 data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header = (type << 6) | 0x0003;
		packet.data   = (u32)data;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 1:
		packet.header = (type << 6) | 0x0006;
		packet.data   = (u32)data << 8;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 2:
		packet.header = (type << 6) | 0x000c;
		packet.data   = (u32)data << 16;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 3:
		packet.header = (type << 6) | 0x0008;
		packet.data   = (u32)data << 24;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		packet.data   = (u32)data >> 8;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_ग_लिखो_memio_24bit(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u32 data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header  = (type << 6) | 0x0007;
		packet.data    = data & 0x00ffffff;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 1:
		packet.header  = (type << 6) | 0x000e;
		packet.data    = data << 8;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 2:
		packet.header  = (type << 6) | 0x000c;
		packet.data    = data << 16;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		packet.data    = (data >> 16) & 0x00ff;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 3:
		packet.header  = (type << 6) | 0x0008;
		packet.data    = data << 24;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0003;
		packet.address = (addr & ~3) + 4;
		packet.data    = (data >> 8) & 0xffff;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_ग_लिखो_memio_दीर्घ(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u32 data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header  = (type << 6) | 0x000f;
		packet.data    = data;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 1:
		packet.header  = (type << 6) | 0x000e;
		packet.data    = data << 8;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 24;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 2:
		packet.header  = (type << 6) | 0x000c;
		packet.data    = data << 16;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0003;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 16;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
		अवरोध;
	हाल 3:
		packet.header  = (type << 6) | 0x0008;
		packet.data    = data << 24;
		ret = sisusb_send_packet(sisusb, 10, &packet);
		packet.header  = (type << 6) | 0x0007;
		packet.address = (addr & ~3) + 4;
		packet.data    = data >> 8;
		ret |= sisusb_send_packet(sisusb, 10, &packet);
	पूर्ण

	वापस ret;
पूर्ण

/* The xxx_bulk routines copy a buffer of variable size. They treat the
 * buffer as अक्षरs, thereक्रमe lsb/msb has to be corrected अगर using the
 * byte/word/दीर्घ/etc routines क्रम speed-up
 *
 * If data is from userland, set "userbuffer" (and clear "kernbuffer"),
 * अगर data is in kernel space, set "kernbuffer" (and clear "userbuffer");
 * अगर neither "kernbuffer" nor "userbuffer" are given, it is assumed
 * that the data alपढ़ोy is in the transfer buffer "sisusb->obuf[index]".
 */

अटल पूर्णांक sisusb_ग_लिखो_mem_bulk(काष्ठा sisusb_usb_data *sisusb, u32 addr,
		अक्षर *kernbuffer, पूर्णांक length, स्थिर अक्षर __user *userbuffer,
		पूर्णांक index, sमाप_प्रकार *bytes_written)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक  ret = 0;
	अटल पूर्णांक msgcount;
	u8   swap8, fromkern = kernbuffer ? 1 : 0;
	u16  swap16;
	u32  swap32, flag = (length >> 28) & 1;
	u8 buf[4];

	/* अगर neither kernbuffer not userbuffer are given, assume
	 * data in obuf
	 */
	अगर (!fromkern && !userbuffer)
		kernbuffer = sisusb->obuf[index];

	(*bytes_written = 0);

	length &= 0x00ffffff;

	जबतक (length) अणु
		चयन (length) अणु
		हाल 1:
			अगर (userbuffer) अणु
				अगर (get_user(swap8, (u8 __user *)userbuffer))
					वापस -EFAULT;
			पूर्ण अन्यथा
				swap8 = kernbuffer[0];

			ret = sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_MEM,
					addr, swap8);

			अगर (!ret)
				(*bytes_written)++;

			वापस ret;

		हाल 2:
			अगर (userbuffer) अणु
				अगर (get_user(swap16, (u16 __user *)userbuffer))
					वापस -EFAULT;
			पूर्ण अन्यथा
				swap16 = *((u16 *)kernbuffer);

			ret = sisusb_ग_लिखो_memio_word(sisusb, SISUSB_TYPE_MEM,
					addr, swap16);

			अगर (!ret)
				(*bytes_written) += 2;

			वापस ret;

		हाल 3:
			अगर (userbuffer) अणु
				अगर (copy_from_user(&buf, userbuffer, 3))
					वापस -EFAULT;
#अगर_घोषित __BIG_ENDIAN
				swap32 = (buf[0] << 16) |
					 (buf[1] <<  8) |
					 buf[2];
#अन्यथा
				swap32 = (buf[2] << 16) |
					 (buf[1] <<  8) |
					 buf[0];
#पूर्ण_अगर
			पूर्ण अन्यथा
#अगर_घोषित __BIG_ENDIAN
				swap32 = (kernbuffer[0] << 16) |
					 (kernbuffer[1] <<  8) |
					 kernbuffer[2];
#अन्यथा
				swap32 = (kernbuffer[2] << 16) |
					 (kernbuffer[1] <<  8) |
					 kernbuffer[0];
#पूर्ण_अगर

			ret = sisusb_ग_लिखो_memio_24bit(sisusb, SISUSB_TYPE_MEM,
					addr, swap32);

			अगर (!ret)
				(*bytes_written) += 3;

			वापस ret;

		हाल 4:
			अगर (userbuffer) अणु
				अगर (get_user(swap32, (u32 __user *)userbuffer))
					वापस -EFAULT;
			पूर्ण अन्यथा
				swap32 = *((u32 *)kernbuffer);

			ret = sisusb_ग_लिखो_memio_दीर्घ(sisusb, SISUSB_TYPE_MEM,
					addr, swap32);
			अगर (!ret)
				(*bytes_written) += 4;

			वापस ret;

		शेष:
			अगर ((length & ~3) > 0x10000) अणु

				packet.header  = 0x001f;
				packet.address = 0x000001d4;
				packet.data    = addr;
				ret = sisusb_send_bridge_packet(sisusb, 10,
						&packet, 0);
				packet.header  = 0x001f;
				packet.address = 0x000001d0;
				packet.data    = (length & ~3);
				ret |= sisusb_send_bridge_packet(sisusb, 10,
						&packet, 0);
				packet.header  = 0x001f;
				packet.address = 0x000001c0;
				packet.data    = flag | 0x16;
				ret |= sisusb_send_bridge_packet(sisusb, 10,
						&packet, 0);
				अगर (userbuffer) अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_LBULK_OUT,
							(length & ~3),
							शून्य, userbuffer, 0,
							bytes_written, 0, 1);
					userbuffer += (*bytes_written);
				पूर्ण अन्यथा अगर (fromkern) अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_LBULK_OUT,
							(length & ~3),
							kernbuffer, शून्य, 0,
							bytes_written, 0, 1);
					kernbuffer += (*bytes_written);
				पूर्ण अन्यथा अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_LBULK_OUT,
							(length & ~3),
							शून्य, शून्य, index,
							bytes_written, 0, 1);
					kernbuffer += ((*bytes_written) &
							(sisusb->obufsize-1));
				पूर्ण

			पूर्ण अन्यथा अणु

				packet.header  = 0x001f;
				packet.address = 0x00000194;
				packet.data    = addr;
				ret = sisusb_send_bridge_packet(sisusb, 10,
						&packet, 0);
				packet.header  = 0x001f;
				packet.address = 0x00000190;
				packet.data    = (length & ~3);
				ret |= sisusb_send_bridge_packet(sisusb, 10,
						&packet, 0);
				अगर (sisusb->flagb0 != 0x16) अणु
					packet.header  = 0x001f;
					packet.address = 0x00000180;
					packet.data    = flag | 0x16;
					ret |= sisusb_send_bridge_packet(sisusb,
							10, &packet, 0);
					sisusb->flagb0 = 0x16;
				पूर्ण
				अगर (userbuffer) अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_BULK_OUT,
							(length & ~3),
							शून्य, userbuffer, 0,
							bytes_written, 0, 1);
					userbuffer += (*bytes_written);
				पूर्ण अन्यथा अगर (fromkern) अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_BULK_OUT,
							(length & ~3),
							kernbuffer, शून्य, 0,
							bytes_written, 0, 1);
					kernbuffer += (*bytes_written);
				पूर्ण अन्यथा अणु
					ret |= sisusb_send_bulk_msg(sisusb,
							SISUSB_EP_GFX_BULK_OUT,
							(length & ~3),
							शून्य, शून्य, index,
							bytes_written, 0, 1);
					kernbuffer += ((*bytes_written) &
							(sisusb->obufsize-1));
				पूर्ण
			पूर्ण
			अगर (ret) अणु
				msgcount++;
				अगर (msgcount < 500)
					dev_err(&sisusb->sisusb_dev->dev,
							"Wrote %zd of %d bytes, error %d\n",
							*bytes_written, length,
							ret);
				अन्यथा अगर (msgcount == 500)
					dev_err(&sisusb->sisusb_dev->dev,
							"Too many errors, logging stopped\n");
			पूर्ण
			addr += (*bytes_written);
			length -= (*bytes_written);
		पूर्ण

		अगर (ret)
			अवरोध;

	पूर्ण

	वापस ret ? -EIO : 0;
पूर्ण

/* Remember: Read data in packet is in machine-endianess! So क्रम
 * byte, word, 24bit, दीर्घ no endian correction is necessary.
 */

अटल पूर्णांक sisusb_पढ़ो_memio_byte(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u8 *data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret;

	CLEARPACKET(&packet);
	packet.header  = (1 << (addr & 3)) | (type << 6);
	packet.address = addr & ~3;
	ret = sisusb_send_packet(sisusb, 6, &packet);
	*data = (u8)(packet.data >> ((addr & 3) << 3));
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_पढ़ो_memio_word(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u16 *data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	CLEARPACKET(&packet);

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header = (type << 6) | 0x0003;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data);
		अवरोध;
	हाल 1:
		packet.header = (type << 6) | 0x0006;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 8);
		अवरोध;
	हाल 2:
		packet.header = (type << 6) | 0x000c;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 16);
		अवरोध;
	हाल 3:
		packet.header = (type << 6) | 0x0008;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 24);
		packet.header = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (u16)(packet.data << 8);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_पढ़ो_memio_24bit(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u32 *data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header  = (type << 6) | 0x0007;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data & 0x00ffffff;
		अवरोध;
	हाल 1:
		packet.header  = (type << 6) | 0x000e;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 8;
		अवरोध;
	हाल 2:
		packet.header  = (type << 6) | 0x000c;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 16;
		packet.header  = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= ((packet.data & 0xff) << 16);
		अवरोध;
	हाल 3:
		packet.header  = (type << 6) | 0x0008;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 24;
		packet.header  = (type << 6) | 0x0003;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= ((packet.data & 0xffff) << 8);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_पढ़ो_memio_दीर्घ(काष्ठा sisusb_usb_data *sisusb, पूर्णांक type,
		u32 addr, u32 *data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret = 0;

	packet.address = addr & ~3;

	चयन (addr & 3) अणु
	हाल 0:
		packet.header  = (type << 6) | 0x000f;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data;
		अवरोध;
	हाल 1:
		packet.header  = (type << 6) | 0x000e;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 8;
		packet.header  = (type << 6) | 0x0001;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 24);
		अवरोध;
	हाल 2:
		packet.header  = (type << 6) | 0x000c;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 16;
		packet.header  = (type << 6) | 0x0003;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 16);
		अवरोध;
	हाल 3:
		packet.header  = (type << 6) | 0x0008;
		ret = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 24;
		packet.header  = (type << 6) | 0x0007;
		packet.address = (addr & ~3) + 4;
		ret |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 8);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_पढ़ो_mem_bulk(काष्ठा sisusb_usb_data *sisusb, u32 addr,
		अक्षर *kernbuffer, पूर्णांक length, अक्षर __user *userbuffer,
		sमाप_प्रकार *bytes_पढ़ो)
अणु
	पूर्णांक ret = 0;
	अक्षर buf[4];
	u16 swap16;
	u32 swap32;

	(*bytes_पढ़ो = 0);

	length &= 0x00ffffff;

	जबतक (length) अणु
		चयन (length) अणु
		हाल 1:
			ret |= sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_MEM,
					addr, &buf[0]);
			अगर (!ret) अणु
				(*bytes_पढ़ो)++;
				अगर (userbuffer) अणु
					अगर (put_user(buf[0], (u8 __user *)userbuffer))
						वापस -EFAULT;
				पूर्ण अन्यथा
					kernbuffer[0] = buf[0];
			पूर्ण
			वापस ret;

		हाल 2:
			ret |= sisusb_पढ़ो_memio_word(sisusb, SISUSB_TYPE_MEM,
					addr, &swap16);
			अगर (!ret) अणु
				(*bytes_पढ़ो) += 2;
				अगर (userbuffer) अणु
					अगर (put_user(swap16, (u16 __user *)userbuffer))
						वापस -EFAULT;
				पूर्ण अन्यथा अणु
					*((u16 *)kernbuffer) = swap16;
				पूर्ण
			पूर्ण
			वापस ret;

		हाल 3:
			ret |= sisusb_पढ़ो_memio_24bit(sisusb, SISUSB_TYPE_MEM,
					addr, &swap32);
			अगर (!ret) अणु
				(*bytes_पढ़ो) += 3;
#अगर_घोषित __BIG_ENDIAN
				buf[0] = (swap32 >> 16) & 0xff;
				buf[1] = (swap32 >> 8) & 0xff;
				buf[2] = swap32 & 0xff;
#अन्यथा
				buf[2] = (swap32 >> 16) & 0xff;
				buf[1] = (swap32 >> 8) & 0xff;
				buf[0] = swap32 & 0xff;
#पूर्ण_अगर
				अगर (userbuffer) अणु
					अगर (copy_to_user(userbuffer,
							&buf[0], 3))
						वापस -EFAULT;
				पूर्ण अन्यथा अणु
					kernbuffer[0] = buf[0];
					kernbuffer[1] = buf[1];
					kernbuffer[2] = buf[2];
				पूर्ण
			पूर्ण
			वापस ret;

		शेष:
			ret |= sisusb_पढ़ो_memio_दीर्घ(sisusb, SISUSB_TYPE_MEM,
					addr, &swap32);
			अगर (!ret) अणु
				(*bytes_पढ़ो) += 4;
				अगर (userbuffer) अणु
					अगर (put_user(swap32, (u32 __user *)userbuffer))
						वापस -EFAULT;

					userbuffer += 4;
				पूर्ण अन्यथा अणु
					*((u32 *)kernbuffer) = swap32;
					kernbuffer += 4;
				पूर्ण
				addr += 4;
				length -= 4;
			पूर्ण
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* High level: Gfx (indexed) रेजिस्टर access */

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
पूर्णांक sisusb_setreg(काष्ठा sisusb_usb_data *sisusb, u32 port, u8 data)
अणु
	वापस sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port, data);
पूर्ण

पूर्णांक sisusb_getreg(काष्ठा sisusb_usb_data *sisusb, u32 port, u8 *data)
अणु
	वापस sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO, port, data);
पूर्ण
#पूर्ण_अगर

पूर्णांक sisusb_setidxreg(काष्ठा sisusb_usb_data *sisusb, u32 port,
		u8 index, u8 data)
अणु
	पूर्णांक ret;

	ret = sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port, index);
	ret |= sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, data);
	वापस ret;
पूर्ण

पूर्णांक sisusb_getidxreg(काष्ठा sisusb_usb_data *sisusb, u32 port,
		u8 index, u8 *data)
अणु
	पूर्णांक ret;

	ret = sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port, index);
	ret |= sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, data);
	वापस ret;
पूर्ण

पूर्णांक sisusb_setidxreganकरोr(काष्ठा sisusb_usb_data *sisusb, u32 port, u8 idx,
		u8 myand, u8 myor)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port, idx);
	ret |= sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, &पंचांगp);
	पंचांगp &= myand;
	पंचांगp |= myor;
	ret |= sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_setidxregmask(काष्ठा sisusb_usb_data *sisusb,
		u32 port, u8 idx, u8 data, u8 mask)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port, idx);
	ret |= sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, &पंचांगp);
	पंचांगp &= ~(mask);
	पंचांगp |= (data & mask);
	ret |= sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, पंचांगp);
	वापस ret;
पूर्ण

पूर्णांक sisusb_setidxregor(काष्ठा sisusb_usb_data *sisusb, u32 port,
		u8 index, u8 myor)
अणु
	वापस sisusb_setidxreganकरोr(sisusb, port, index, 0xff, myor);
पूर्ण

पूर्णांक sisusb_setidxregand(काष्ठा sisusb_usb_data *sisusb, u32 port,
		u8 idx, u8 myand)
अणु
	वापस sisusb_setidxreganकरोr(sisusb, port, idx, myand, 0x00);
पूर्ण

/* Write/पढ़ो video ram */

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
पूर्णांक sisusb_ग_लिखोb(काष्ठा sisusb_usb_data *sisusb, u32 adr, u8 data)
अणु
	वापस sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_MEM, adr, data);
पूर्ण

पूर्णांक sisusb_पढ़ोb(काष्ठा sisusb_usb_data *sisusb, u32 adr, u8 *data)
अणु
	वापस sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_MEM, adr, data);
पूर्ण

पूर्णांक sisusb_copy_memory(काष्ठा sisusb_usb_data *sisusb, u8 *src,
		u32 dest, पूर्णांक length)
अणु
	माप_प्रकार dummy;

	वापस sisusb_ग_लिखो_mem_bulk(sisusb, dest, src, length,
			शून्य, 0, &dummy);
पूर्ण

#अगर_घोषित SISUSBENDIANTEST
अटल पूर्णांक sisusb_पढ़ो_memory(काष्ठा sisusb_usb_data *sisusb, अक्षर *dest,
		u32 src, पूर्णांक length)
अणु
	माप_प्रकार dummy;

	वापस sisusb_पढ़ो_mem_bulk(sisusb, src, dest, length,
			शून्य, &dummy);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित SISUSBENDIANTEST
अटल व्योम sisusb_testपढ़ोग_लिखो(काष्ठा sisusb_usb_data *sisusb)
अणु
	अटल u8 srcbuffer[] = अणु 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 पूर्ण;
	अक्षर destbuffer[10];
	पूर्णांक i, j;

	sisusb_copy_memory(sisusb, srcbuffer, sisusb->vrambase, 7);

	क्रम (i = 1; i <= 7; i++) अणु
		dev_dbg(&sisusb->sisusb_dev->dev,
				"sisusb: rwtest %d bytes\n", i);
		sisusb_पढ़ो_memory(sisusb, destbuffer, sisusb->vrambase, i);
		क्रम (j = 0; j < i; j++) अणु
			dev_dbg(&sisusb->sisusb_dev->dev,
					"rwtest read[%d] = %x\n",
					j, destbuffer[j]);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* access pci config रेजिस्टरs (reg numbers 0, 4, 8, etc) */

अटल पूर्णांक sisusb_ग_लिखो_pci_config(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक regnum, u32 data)
अणु
	काष्ठा sisusb_packet packet;

	packet.header = 0x008f;
	packet.address = regnum | 0x10000;
	packet.data = data;
	वापस sisusb_send_packet(sisusb, 10, &packet);
पूर्ण

अटल पूर्णांक sisusb_पढ़ो_pci_config(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक regnum, u32 *data)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret;

	packet.header = 0x008f;
	packet.address = (u32)regnum | 0x10000;
	ret = sisusb_send_packet(sisusb, 6, &packet);
	*data = packet.data;
	वापस ret;
पूर्ण

/* Clear video RAM */

अटल पूर्णांक sisusb_clear_vram(काष्ठा sisusb_usb_data *sisusb,
		u32 address, पूर्णांक length)
अणु
	पूर्णांक ret, i;
	sमाप_प्रकार j;

	अगर (address < sisusb->vrambase)
		वापस 1;

	अगर (address >= sisusb->vrambase + sisusb->vramsize)
		वापस 1;

	अगर (address + length > sisusb->vrambase + sisusb->vramsize)
		length = sisusb->vrambase + sisusb->vramsize - address;

	अगर (length <= 0)
		वापस 0;

	/* allocate मुक्त buffer/urb and clear the buffer */
	i = sisusb_alloc_outbuf(sisusb);
	अगर (i < 0)
		वापस -EBUSY;

	स_रखो(sisusb->obuf[i], 0, sisusb->obufsize);

	/* We can ग_लिखो a length > buffer size here. The buffer
	 * data will simply be re-used (like a ring-buffer).
	 */
	ret = sisusb_ग_लिखो_mem_bulk(sisusb, address, शून्य, length, शून्य, i, &j);

	/* Free the buffer/urb */
	sisusb_मुक्त_outbuf(sisusb, i);

	वापस ret;
पूर्ण

/* Initialize the graphics core (वापस 0 on success)
 * This resets the graphics hardware and माला_दो it पूर्णांकo
 * a defined mode (640x480@60Hz)
 */

#घोषणा GETREG(r, d) sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO, r, d)
#घोषणा SETREG(r, d) sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_IO, r, d)
#घोषणा SETIREG(r, i, d) sisusb_setidxreg(sisusb, r, i, d)
#घोषणा GETIREG(r, i, d) sisusb_getidxreg(sisusb, r, i, d)
#घोषणा SETIREGOR(r, i, o) sisusb_setidxregor(sisusb, r, i, o)
#घोषणा SETIREGAND(r, i, a) sisusb_setidxregand(sisusb, r, i, a)
#घोषणा SETIREGANDOR(r, i, a, o) sisusb_setidxreganकरोr(sisusb, r, i, a, o)
#घोषणा READL(a, d) sisusb_पढ़ो_memio_दीर्घ(sisusb, SISUSB_TYPE_MEM, a, d)
#घोषणा WRITEL(a, d) sisusb_ग_लिखो_memio_दीर्घ(sisusb, SISUSB_TYPE_MEM, a, d)
#घोषणा READB(a, d) sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_MEM, a, d)
#घोषणा WRITEB(a, d) sisusb_ग_लिखो_memio_byte(sisusb, SISUSB_TYPE_MEM, a, d)

अटल पूर्णांक sisusb_triggersr16(काष्ठा sisusb_usb_data *sisusb, u8 ramtype)
अणु
	पूर्णांक ret;
	u8 पंचांगp8;

	ret = GETIREG(SISSR, 0x16, &पंचांगp8);
	अगर (ramtype <= 1) अणु
		पंचांगp8 &= 0x3f;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 |= 0x80;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
	पूर्ण अन्यथा अणु
		पंचांगp8 |= 0xc0;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 |= 0x80;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 |= 0xd0;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
		पंचांगp8 |= 0xa0;
		ret |= SETIREG(SISSR, 0x16, पंचांगp8);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_getbuswidth(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक *bw, पूर्णांक *chab)
अणु
	पूर्णांक ret;
	u8  ramtype, करोne = 0;
	u32 t0, t1, t2, t3;
	u32 ramptr = SISUSB_PCI_MEMBASE;

	ret = GETIREG(SISSR, 0x3a, &ramtype);
	ramtype &= 3;

	ret |= SETIREG(SISSR, 0x13, 0x00);

	अगर (ramtype <= 1) अणु
		ret |= SETIREG(SISSR, 0x14, 0x12);
		ret |= SETIREGAND(SISSR, 0x15, 0xef);
	पूर्ण अन्यथा अणु
		ret |= SETIREG(SISSR, 0x14, 0x02);
	पूर्ण

	ret |= sisusb_triggersr16(sisusb, ramtype);
	ret |= WRITEL(ramptr +  0, 0x01234567);
	ret |= WRITEL(ramptr +  4, 0x456789ab);
	ret |= WRITEL(ramptr +  8, 0x89abcdef);
	ret |= WRITEL(ramptr + 12, 0xcdef0123);
	ret |= WRITEL(ramptr + 16, 0x55555555);
	ret |= WRITEL(ramptr + 20, 0x55555555);
	ret |= WRITEL(ramptr + 24, 0xffffffff);
	ret |= WRITEL(ramptr + 28, 0xffffffff);
	ret |= READL(ramptr +  0, &t0);
	ret |= READL(ramptr +  4, &t1);
	ret |= READL(ramptr +  8, &t2);
	ret |= READL(ramptr + 12, &t3);

	अगर (ramtype <= 1) अणु

		*chab = 0; *bw = 64;

		अगर ((t3 != 0xcdef0123) || (t2 != 0x89abcdef)) अणु
			अगर ((t1 == 0x456789ab) && (t0 == 0x01234567)) अणु
				*chab = 0; *bw = 64;
				ret |= SETIREGAND(SISSR, 0x14, 0xfd);
			पूर्ण
		पूर्ण
		अगर ((t1 != 0x456789ab) || (t0 != 0x01234567)) अणु
			*chab = 1; *bw = 64;
			ret |= SETIREGANDOR(SISSR, 0x14, 0xfc, 0x01);

			ret |= sisusb_triggersr16(sisusb, ramtype);
			ret |= WRITEL(ramptr +  0, 0x89abcdef);
			ret |= WRITEL(ramptr +  4, 0xcdef0123);
			ret |= WRITEL(ramptr +  8, 0x55555555);
			ret |= WRITEL(ramptr + 12, 0x55555555);
			ret |= WRITEL(ramptr + 16, 0xaaaaaaaa);
			ret |= WRITEL(ramptr + 20, 0xaaaaaaaa);
			ret |= READL(ramptr +  4, &t1);

			अगर (t1 != 0xcdef0123) अणु
				*bw = 32;
				ret |= SETIREGOR(SISSR, 0x15, 0x10);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु

		*chab = 0; *bw = 64;	/* शेष: cha, bw = 64 */

		करोne = 0;

		अगर (t1 == 0x456789ab) अणु
			अगर (t0 == 0x01234567) अणु
				*chab = 0; *bw = 64;
				करोne = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (t0 == 0x01234567) अणु
				*chab = 0; *bw = 32;
				ret |= SETIREG(SISSR, 0x14, 0x00);
				करोne = 1;
			पूर्ण
		पूर्ण

		अगर (!करोne) अणु
			ret |= SETIREG(SISSR, 0x14, 0x03);
			ret |= sisusb_triggersr16(sisusb, ramtype);

			ret |= WRITEL(ramptr +  0, 0x01234567);
			ret |= WRITEL(ramptr +  4, 0x456789ab);
			ret |= WRITEL(ramptr +  8, 0x89abcdef);
			ret |= WRITEL(ramptr + 12, 0xcdef0123);
			ret |= WRITEL(ramptr + 16, 0x55555555);
			ret |= WRITEL(ramptr + 20, 0x55555555);
			ret |= WRITEL(ramptr + 24, 0xffffffff);
			ret |= WRITEL(ramptr + 28, 0xffffffff);
			ret |= READL(ramptr +  0, &t0);
			ret |= READL(ramptr +  4, &t1);

			अगर (t1 == 0x456789ab) अणु
				अगर (t0 == 0x01234567) अणु
					*chab = 1; *bw = 64;
					वापस ret;
				पूर्ण /* अन्यथा error */
			पूर्ण अन्यथा अणु
				अगर (t0 == 0x01234567) अणु
					*chab = 1; *bw = 32;
					ret |= SETIREG(SISSR, 0x14, 0x01);
				पूर्ण /* अन्यथा error */
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_verअगरy_mclk(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक ret = 0;
	u32 ramptr = SISUSB_PCI_MEMBASE;
	u8 पंचांगp1, पंचांगp2, i, j;

	ret |= WRITEB(ramptr, 0xaa);
	ret |= WRITEB(ramptr + 16, 0x55);
	ret |= READB(ramptr, &पंचांगp1);
	ret |= READB(ramptr + 16, &पंचांगp2);
	अगर ((पंचांगp1 != 0xaa) || (पंचांगp2 != 0x55)) अणु
		क्रम (i = 0, j = 16; i < 2; i++, j += 16) अणु
			ret |= GETIREG(SISSR, 0x21, &पंचांगp1);
			ret |= SETIREGAND(SISSR, 0x21, (पंचांगp1 & 0xfb));
			ret |= SETIREGOR(SISSR, 0x3c, 0x01);  /* not on 330 */
			ret |= SETIREGAND(SISSR, 0x3c, 0xfe); /* not on 330 */
			ret |= SETIREG(SISSR, 0x21, पंचांगp1);
			ret |= WRITEB(ramptr + 16 + j, j);
			ret |= READB(ramptr + 16 + j, &पंचांगp1);
			अगर (पंचांगp1 == j) अणु
				ret |= WRITEB(ramptr + j, j);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_set_rank(काष्ठा sisusb_usb_data *sisusb, पूर्णांक *iret,
		पूर्णांक index, u8 rankno, u8 chab, स्थिर u8 dramtype[][5], पूर्णांक bw)
अणु
	पूर्णांक ret = 0, ranksize;
	u8 पंचांगp;

	*iret = 0;

	अगर ((rankno == 2) && (dramtype[index][0] == 2))
		वापस ret;

	ranksize = dramtype[index][3] / 2 * bw / 32;

	अगर ((ranksize * rankno) > 128)
		वापस ret;

	पंचांगp = 0;
	जबतक ((ranksize >>= 1) > 0)
		पंचांगp += 0x10;

	पंचांगp |= ((rankno - 1) << 2);
	पंचांगp |= ((bw / 64) & 0x02);
	पंचांगp |= (chab & 0x01);

	ret = SETIREG(SISSR, 0x14, पंचांगp);
	ret |= sisusb_triggersr16(sisusb, 0); /* sic! */

	*iret = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_check_rbc(काष्ठा sisusb_usb_data *sisusb, पूर्णांक *iret,
		u32 inc, पूर्णांक testn)
अणु
	पूर्णांक ret = 0, i;
	u32 j, पंचांगp;

	*iret = 0;

	क्रम (i = 0, j = 0; i < testn; i++) अणु
		ret |= WRITEL(sisusb->vrambase + j, j);
		j += inc;
	पूर्ण

	क्रम (i = 0, j = 0; i < testn; i++) अणु
		ret |= READL(sisusb->vrambase + j, &पंचांगp);
		अगर (पंचांगp != j)
			वापस ret;

		j += inc;
	पूर्ण

	*iret = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_check_ranks(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक *iret, पूर्णांक rankno, पूर्णांक idx, पूर्णांक bw, स्थिर u8 rtype[][5])
अणु
	पूर्णांक ret = 0, i, i2ret;
	u32 inc;

	*iret = 0;

	क्रम (i = rankno; i >= 1; i--) अणु
		inc = 1 << (rtype[idx][2] + rtype[idx][1] + rtype[idx][0] +
				bw / 64 + i);
		ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 2);
		अगर (!i2ret)
			वापस ret;
	पूर्ण

	inc = 1 << (rtype[idx][2] + bw / 64 + 2);
	ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 4);
	अगर (!i2ret)
		वापस ret;

	inc = 1 << (10 + bw / 64);
	ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 2);
	अगर (!i2ret)
		वापस ret;

	*iret = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_get_sdram_size(काष्ठा sisusb_usb_data *sisusb, पूर्णांक *iret,
		पूर्णांक bw, पूर्णांक chab)
अणु
	पूर्णांक ret = 0, i2ret = 0, i, j;
	अटल स्थिर u8 sdramtype[13][5] = अणु
		अणु 2, 12, 9, 64, 0x35 पूर्ण,
		अणु 1, 13, 9, 64, 0x44 पूर्ण,
		अणु 2, 12, 8, 32, 0x31 पूर्ण,
		अणु 2, 11, 9, 32, 0x25 पूर्ण,
		अणु 1, 12, 9, 32, 0x34 पूर्ण,
		अणु 1, 13, 8, 32, 0x40 पूर्ण,
		अणु 2, 11, 8, 16, 0x21 पूर्ण,
		अणु 1, 12, 8, 16, 0x30 पूर्ण,
		अणु 1, 11, 9, 16, 0x24 पूर्ण,
		अणु 1, 11, 8,  8, 0x20 पूर्ण,
		अणु 2,  9, 8,  4, 0x01 पूर्ण,
		अणु 1, 10, 8,  4, 0x10 पूर्ण,
		अणु 1,  9, 8,  2, 0x00 पूर्ण
	पूर्ण;

	*iret = 1; /* error */

	क्रम (i = 0; i < 13; i++) अणु
		ret |= SETIREGANDOR(SISSR, 0x13, 0x80, sdramtype[i][4]);
		क्रम (j = 2; j > 0; j--) अणु
			ret |= sisusb_set_rank(sisusb, &i2ret, i, j, chab,
					sdramtype, bw);
			अगर (!i2ret)
				जारी;

			ret |= sisusb_check_ranks(sisusb, &i2ret, j, i, bw,
					sdramtype);
			अगर (i2ret) अणु
				*iret = 0;	/* ram size found */
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_setup_screen(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक clrall, पूर्णांक drwfr)
अणु
	पूर्णांक ret = 0;
	u32 address;
	पूर्णांक i, length, modex, modey, bpp;

	modex = 640; modey = 480; bpp = 2;

	address = sisusb->vrambase;	/* Clear video ram */

	अगर (clrall)
		length = sisusb->vramsize;
	अन्यथा
		length = modex * bpp * modey;

	ret = sisusb_clear_vram(sisusb, address, length);

	अगर (!ret && drwfr) अणु
		क्रम (i = 0; i < modex; i++) अणु
			address = sisusb->vrambase + (i * bpp);
			ret |= sisusb_ग_लिखो_memio_word(sisusb, SISUSB_TYPE_MEM,
					address, 0xf100);
			address += (modex * (modey-1) * bpp);
			ret |= sisusb_ग_लिखो_memio_word(sisusb, SISUSB_TYPE_MEM,
					address, 0xf100);
		पूर्ण
		क्रम (i = 0; i < modey; i++) अणु
			address = sisusb->vrambase + ((i * modex) * bpp);
			ret |= sisusb_ग_लिखो_memio_word(sisusb, SISUSB_TYPE_MEM,
					address, 0xf100);
			address += ((modex - 1) * bpp);
			ret |= sisusb_ग_लिखो_memio_word(sisusb, SISUSB_TYPE_MEM,
					address, 0xf100);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sisusb_set_शेष_mode(काष्ठा sisusb_usb_data *sisusb,
		पूर्णांक touchengines)
अणु
	पूर्णांक i, j, modex, bpp, du;
	u8 sr31, cr63, पंचांगp8;
	अटल स्थिर अक्षर attrdata[] = अणु
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x01, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर अक्षर crtcrdata[] = अणु
		0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0x0b, 0x3e,
		0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xea, 0x8c, 0xdf, 0x28, 0x40, 0xe7, 0x04, 0xa3,
		0xff
	पूर्ण;
	अटल स्थिर अक्षर grcdata[] = अणु
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0f,
		0xff
	पूर्ण;
	अटल स्थिर अक्षर crtcdata[] = अणु
		0x5f, 0x4f, 0x4f, 0x83, 0x55, 0x81, 0x0b, 0x3e,
		0xe9, 0x8b, 0xdf, 0xe8, 0x0c, 0x00, 0x00, 0x05,
		0x00
	पूर्ण;

	modex = 640; bpp = 2;

	GETIREG(SISSR, 0x31, &sr31);
	GETIREG(SISCR, 0x63, &cr63);
	SETIREGOR(SISSR, 0x01, 0x20);
	SETIREG(SISCR, 0x63, cr63 & 0xbf);
	SETIREGOR(SISCR, 0x17, 0x80);
	SETIREGOR(SISSR, 0x1f, 0x04);
	SETIREGAND(SISSR, 0x07, 0xfb);
	SETIREG(SISSR, 0x00, 0x03);	/* seq */
	SETIREG(SISSR, 0x01, 0x21);
	SETIREG(SISSR, 0x02, 0x0f);
	SETIREG(SISSR, 0x03, 0x00);
	SETIREG(SISSR, 0x04, 0x0e);
	SETREG(SISMISCW, 0x23);		/* misc */
	क्रम (i = 0; i <= 0x18; i++) अणु	/* crtc */
		SETIREG(SISCR, i, crtcrdata[i]);
	पूर्ण
	क्रम (i = 0; i <= 0x13; i++) अणु	/* att */
		GETREG(SISINPSTAT, &पंचांगp8);
		SETREG(SISAR, i);
		SETREG(SISAR, attrdata[i]);
	पूर्ण
	GETREG(SISINPSTAT, &पंचांगp8);
	SETREG(SISAR, 0x14);
	SETREG(SISAR, 0x00);
	GETREG(SISINPSTAT, &पंचांगp8);
	SETREG(SISAR, 0x20);
	GETREG(SISINPSTAT, &पंचांगp8);
	क्रम (i = 0; i <= 0x08; i++) अणु	/* grc */
		SETIREG(SISGR, i, grcdata[i]);
	पूर्ण
	SETIREGAND(SISGR, 0x05, 0xbf);
	क्रम (i = 0x0A; i <= 0x0E; i++) अणु	/* clr ext */
		SETIREG(SISSR, i, 0x00);
	पूर्ण
	SETIREGAND(SISSR, 0x37, 0xfe);
	SETREG(SISMISCW, 0xef);		/* sync */
	SETIREG(SISCR, 0x11, 0x00);	/* crtc */
	क्रम (j = 0x00, i = 0; i <= 7; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	क्रम (j = 0x10; i <= 10; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	क्रम (j = 0x15; i <= 12; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	क्रम (j = 0x0A; i <= 15; i++, j++)
		SETIREG(SISSR, j, crtcdata[i]);

	SETIREG(SISSR, 0x0E, (crtcdata[16] & 0xE0));
	SETIREGANDOR(SISCR, 0x09, 0x5f, ((crtcdata[16] & 0x01) << 5));
	SETIREG(SISCR, 0x14, 0x4f);
	du = (modex / 16) * (bpp * 2);	/* offset/pitch */
	SETIREGANDOR(SISSR, 0x0e, 0xf0, ((du >> 8) & 0x0f));
	SETIREG(SISCR, 0x13, (du & 0xff));
	du <<= 5;
	पंचांगp8 = du >> 8;
	SETIREG(SISSR, 0x10, पंचांगp8);
	SETIREG(SISSR, 0x31, 0x00);	/* VCLK */
	SETIREG(SISSR, 0x2b, 0x1b);
	SETIREG(SISSR, 0x2c, 0xe1);
	SETIREG(SISSR, 0x2d, 0x01);
	SETIREGAND(SISSR, 0x3d, 0xfe);	/* FIFO */
	SETIREG(SISSR, 0x08, 0xae);
	SETIREGAND(SISSR, 0x09, 0xf0);
	SETIREG(SISSR, 0x08, 0x34);
	SETIREGOR(SISSR, 0x3d, 0x01);
	SETIREGAND(SISSR, 0x1f, 0x3f);	/* mode regs */
	SETIREGANDOR(SISSR, 0x06, 0xc0, 0x0a);
	SETIREG(SISCR, 0x19, 0x00);
	SETIREGAND(SISCR, 0x1a, 0xfc);
	SETIREGAND(SISSR, 0x0f, 0xb7);
	SETIREGAND(SISSR, 0x31, 0xfb);
	SETIREGANDOR(SISSR, 0x21, 0x1f, 0xa0);
	SETIREGAND(SISSR, 0x32, 0xf3);
	SETIREGANDOR(SISSR, 0x07, 0xf8, 0x03);
	SETIREG(SISCR, 0x52, 0x6c);

	SETIREG(SISCR, 0x0d, 0x00);	/* adjust frame */
	SETIREG(SISCR, 0x0c, 0x00);
	SETIREG(SISSR, 0x0d, 0x00);
	SETIREGAND(SISSR, 0x37, 0xfe);

	SETIREG(SISCR, 0x32, 0x20);
	SETIREGAND(SISSR, 0x01, 0xdf);	/* enable display */
	SETIREG(SISCR, 0x63, (cr63 & 0xbf));
	SETIREG(SISSR, 0x31, (sr31 & 0xfb));

	अगर (touchengines) अणु
		SETIREG(SISSR, 0x20, 0xa1);	/* enable engines */
		SETIREGOR(SISSR, 0x1e, 0x5a);

		SETIREG(SISSR, 0x26, 0x01);	/* disable cmdqueue */
		SETIREG(SISSR, 0x27, 0x1f);
		SETIREG(SISSR, 0x26, 0x00);
	पूर्ण

	SETIREG(SISCR, 0x34, 0x44);	/* we just set std mode #44 */
पूर्ण

अटल पूर्णांक sisusb_init_gfxcore(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक ret = 0, i, j, bw, chab, iret, retry = 3;
	u8 पंचांगp8, ramtype;
	u32 पंचांगp32;
	अटल स्थिर अक्षर mclktable[] = अणु
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	पूर्ण;
	अटल स्थिर अक्षर eclktable[] = अणु
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	पूर्ण;
	अटल स्थिर अक्षर ramtypetable1[] = अणु
		0x00, 0x04, 0x60, 0x60,
		0x0f, 0x0f, 0x1f, 0x1f,
		0xba, 0xba, 0xba, 0xba,
		0xa9, 0xa9, 0xac, 0xac,
		0xa0, 0xa0, 0xa0, 0xa8,
		0x00, 0x00, 0x02, 0x02,
		0x30, 0x30, 0x40, 0x40
	पूर्ण;
	अटल स्थिर अक्षर ramtypetable2[] = अणु
		0x77, 0x77, 0x44, 0x44,
		0x77, 0x77, 0x44, 0x44,
		0x00, 0x00, 0x00, 0x00,
		0x5b, 0x5b, 0xab, 0xab,
		0x00, 0x00, 0xf0, 0xf8
	पूर्ण;

	जबतक (retry--) अणु

		/* Enable VGA */
		ret = GETREG(SISVGAEN, &पंचांगp8);
		ret |= SETREG(SISVGAEN, (पंचांगp8 | 0x01));

		/* Enable GPU access to VRAM */
		ret |= GETREG(SISMISCR, &पंचांगp8);
		ret |= SETREG(SISMISCW, (पंचांगp8 | 0x01));

		अगर (ret)
			जारी;

		/* Reset रेजिस्टरs */
		ret |= SETIREGAND(SISCR, 0x5b, 0xdf);
		ret |= SETIREG(SISSR, 0x05, 0x86);
		ret |= SETIREGOR(SISSR, 0x20, 0x01);

		ret |= SETREG(SISMISCW, 0x67);

		क्रम (i = 0x06; i <= 0x1f; i++)
			ret |= SETIREG(SISSR, i, 0x00);

		क्रम (i = 0x21; i <= 0x27; i++)
			ret |= SETIREG(SISSR, i, 0x00);

		क्रम (i = 0x31; i <= 0x3d; i++)
			ret |= SETIREG(SISSR, i, 0x00);

		क्रम (i = 0x12; i <= 0x1b; i++)
			ret |= SETIREG(SISSR, i, 0x00);

		क्रम (i = 0x79; i <= 0x7c; i++)
			ret |= SETIREG(SISCR, i, 0x00);

		अगर (ret)
			जारी;

		ret |= SETIREG(SISCR, 0x63, 0x80);

		ret |= GETIREG(SISSR, 0x3a, &ramtype);
		ramtype &= 0x03;

		ret |= SETIREG(SISSR, 0x28, mclktable[ramtype * 4]);
		ret |= SETIREG(SISSR, 0x29, mclktable[(ramtype * 4) + 1]);
		ret |= SETIREG(SISSR, 0x2a, mclktable[(ramtype * 4) + 2]);

		ret |= SETIREG(SISSR, 0x2e, eclktable[ramtype * 4]);
		ret |= SETIREG(SISSR, 0x2f, eclktable[(ramtype * 4) + 1]);
		ret |= SETIREG(SISSR, 0x30, eclktable[(ramtype * 4) + 2]);

		ret |= SETIREG(SISSR, 0x07, 0x18);
		ret |= SETIREG(SISSR, 0x11, 0x0f);

		अगर (ret)
			जारी;

		क्रम (i = 0x15, j = 0; i <= 0x1b; i++, j++) अणु
			ret |= SETIREG(SISSR, i,
					ramtypetable1[(j*4) + ramtype]);
		पूर्ण
		क्रम (i = 0x40, j = 0; i <= 0x44; i++, j++) अणु
			ret |= SETIREG(SISCR, i,
					ramtypetable2[(j*4) + ramtype]);
		पूर्ण

		ret |= SETIREG(SISCR, 0x49, 0xaa);

		ret |= SETIREG(SISSR, 0x1f, 0x00);
		ret |= SETIREG(SISSR, 0x20, 0xa0);
		ret |= SETIREG(SISSR, 0x23, 0xf6);
		ret |= SETIREG(SISSR, 0x24, 0x0d);
		ret |= SETIREG(SISSR, 0x25, 0x33);

		ret |= SETIREG(SISSR, 0x11, 0x0f);

		ret |= SETIREGOR(SISPART1, 0x2f, 0x01);

		ret |= SETIREGAND(SISCAP, 0x3f, 0xef);

		अगर (ret)
			जारी;

		ret |= SETIREG(SISPART1, 0x00, 0x00);

		ret |= GETIREG(SISSR, 0x13, &पंचांगp8);
		पंचांगp8 >>= 4;

		ret |= SETIREG(SISPART1, 0x02, 0x00);
		ret |= SETIREG(SISPART1, 0x2e, 0x08);

		ret |= sisusb_पढ़ो_pci_config(sisusb, 0x50, &पंचांगp32);
		पंचांगp32 &= 0x00f00000;
		पंचांगp8 = (पंचांगp32 == 0x100000) ? 0x33 : 0x03;
		ret |= SETIREG(SISSR, 0x25, पंचांगp8);
		पंचांगp8 = (पंचांगp32 == 0x100000) ? 0xaa : 0x88;
		ret |= SETIREG(SISCR, 0x49, पंचांगp8);

		ret |= SETIREG(SISSR, 0x27, 0x1f);
		ret |= SETIREG(SISSR, 0x31, 0x00);
		ret |= SETIREG(SISSR, 0x32, 0x11);
		ret |= SETIREG(SISSR, 0x33, 0x00);

		अगर (ret)
			जारी;

		ret |= SETIREG(SISCR, 0x83, 0x00);

		sisusb_set_शेष_mode(sisusb, 0);

		ret |= SETIREGAND(SISSR, 0x21, 0xdf);
		ret |= SETIREGOR(SISSR, 0x01, 0x20);
		ret |= SETIREGOR(SISSR, 0x16, 0x0f);

		ret |= sisusb_triggersr16(sisusb, ramtype);

		/* Disable refresh */
		ret |= SETIREGAND(SISSR, 0x17, 0xf8);
		ret |= SETIREGOR(SISSR, 0x19, 0x03);

		ret |= sisusb_getbuswidth(sisusb, &bw, &chab);
		ret |= sisusb_verअगरy_mclk(sisusb);

		अगर (ramtype <= 1) अणु
			ret |= sisusb_get_sdram_size(sisusb, &iret, bw, chab);
			अगर (iret) अणु
				dev_err(&sisusb->sisusb_dev->dev,
						"RAM size detection failed, assuming 8MB video RAM\n");
				ret |= SETIREG(SISSR, 0x14, 0x31);
				/* TODO */
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(&sisusb->sisusb_dev->dev,
					"DDR RAM device found, assuming 8MB video RAM\n");
			ret |= SETIREG(SISSR, 0x14, 0x31);
			/* *** TODO *** */
		पूर्ण

		/* Enable refresh */
		ret |= SETIREG(SISSR, 0x16, ramtypetable1[4 + ramtype]);
		ret |= SETIREG(SISSR, 0x17, ramtypetable1[8 + ramtype]);
		ret |= SETIREG(SISSR, 0x19, ramtypetable1[16 + ramtype]);

		ret |= SETIREGOR(SISSR, 0x21, 0x20);

		ret |= SETIREG(SISSR, 0x22, 0xfb);
		ret |= SETIREG(SISSR, 0x21, 0xa5);

		अगर (ret == 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अघोषित SETREG
#अघोषित GETREG
#अघोषित SETIREG
#अघोषित GETIREG
#अघोषित SETIREGOR
#अघोषित SETIREGAND
#अघोषित SETIREGANDOR
#अघोषित READL
#अघोषित WRITEL

अटल व्योम sisusb_get_ramconfig(काष्ठा sisusb_usb_data *sisusb)
अणु
	u8 पंचांगp8, पंचांगp82, ramtype;
	पूर्णांक bw = 0;
	अक्षर *ramtypetext1 = शून्य;
	अटल स्थिर अक्षर ram_datarate[4] = अणु'S', 'S', 'D', 'D'पूर्ण;
	अटल स्थिर अक्षर ram_dynamictype[4] = अणु'D', 'G', 'D', 'G'पूर्ण;
	अटल स्थिर पूर्णांक busSDR[4]  = अणु64, 64, 128, 128पूर्ण;
	अटल स्थिर पूर्णांक busDDR[4]  = अणु32, 32,  64,  64पूर्ण;
	अटल स्थिर पूर्णांक busDDRA[4] = अणु64+32, 64+32, (64+32)*2, (64+32)*2पूर्ण;

	sisusb_getidxreg(sisusb, SISSR, 0x14, &पंचांगp8);
	sisusb_getidxreg(sisusb, SISSR, 0x15, &पंचांगp82);
	sisusb_getidxreg(sisusb, SISSR, 0x3a, &ramtype);
	sisusb->vramsize = (1 << ((पंचांगp8 & 0xf0) >> 4)) * 1024 * 1024;
	ramtype &= 0x03;
	चयन ((पंचांगp8 >> 2) & 0x03) अणु
	हाल 0:
		ramtypetext1 = "1 ch/1 r";
		अगर (पंचांगp82 & 0x10)
			bw = 32;
		अन्यथा
			bw = busSDR[(पंचांगp8 & 0x03)];

		अवरोध;
	हाल 1:
		ramtypetext1 = "1 ch/2 r";
		sisusb->vramsize <<= 1;
		bw = busSDR[(पंचांगp8 & 0x03)];
		अवरोध;
	हाल 2:
		ramtypetext1 = "asymmetric";
		sisusb->vramsize += sisusb->vramsize/2;
		bw = busDDRA[(पंचांगp8 & 0x03)];
		अवरोध;
	हाल 3:
		ramtypetext1 = "2 channel";
		sisusb->vramsize <<= 1;
		bw = busDDR[(पंचांगp8 & 0x03)];
		अवरोध;
	पूर्ण

	dev_info(&sisusb->sisusb_dev->dev,
			"%dMB %s %cDR S%cRAM, bus width %d\n",
			sisusb->vramsize >> 20, ramtypetext1,
			ram_datarate[ramtype], ram_dynamictype[ramtype], bw);
पूर्ण

अटल पूर्णांक sisusb_करो_init_gfxdevice(काष्ठा sisusb_usb_data *sisusb)
अणु
	काष्ठा sisusb_packet packet;
	पूर्णांक ret;
	u32 पंचांगp32;

	/* Do some magic */
	packet.header  = 0x001f;
	packet.address = 0x00000324;
	packet.data    = 0x00000004;
	ret = sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000364;
	packet.data    = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000384;
	packet.data    = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000100;
	packet.data    = 0x00000700;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x000f;
	packet.address = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 6, &packet, 0);
	packet.data |= 0x17;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	/* Init BAR 0 (VRAM) */
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x10, &पंचांगp32);
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x10, 0xfffffff0);
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x10, &पंचांगp32);
	पंचांगp32 &= 0x0f;
	पंचांगp32 |= SISUSB_PCI_MEMBASE;
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x10, पंचांगp32);

	/* Init BAR 1 (MMIO) */
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x14, &पंचांगp32);
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x14, 0xfffffff0);
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x14, &पंचांगp32);
	पंचांगp32 &= 0x0f;
	पंचांगp32 |= SISUSB_PCI_MMIOBASE;
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x14, पंचांगp32);

	/* Init BAR 2 (i/o ports) */
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x18, &पंचांगp32);
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x18, 0xfffffff0);
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x18, &पंचांगp32);
	पंचांगp32 &= 0x0f;
	पंचांगp32 |= SISUSB_PCI_IOPORTBASE;
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x18, पंचांगp32);

	/* Enable memory and i/o access */
	ret |= sisusb_पढ़ो_pci_config(sisusb, 0x04, &पंचांगp32);
	पंचांगp32 |= 0x3;
	ret |= sisusb_ग_लिखो_pci_config(sisusb, 0x04, पंचांगp32);

	अगर (ret == 0) अणु
		/* Some further magic */
		packet.header  = 0x001f;
		packet.address = 0x00000050;
		packet.data    = 0x000000ff;
		ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);
	पूर्ण

	वापस ret;
पूर्ण

/* Initialize the graphics device (वापस 0 on success)
 * This initializes the net2280 as well as the PCI रेजिस्टरs
 * of the graphics board.
 */

अटल पूर्णांक sisusb_init_gfxdevice(काष्ठा sisusb_usb_data *sisusb, पूर्णांक initscreen)
अणु
	पूर्णांक ret = 0, test = 0;
	u32 पंचांगp32;

	अगर (sisusb->devinit == 1) अणु
		/* Read PCI BARs and see अगर they have been set up */
		ret |= sisusb_पढ़ो_pci_config(sisusb, 0x10, &पंचांगp32);
		अगर (ret)
			वापस ret;

		अगर ((पंचांगp32 & 0xfffffff0) == SISUSB_PCI_MEMBASE)
			test++;

		ret |= sisusb_पढ़ो_pci_config(sisusb, 0x14, &पंचांगp32);
		अगर (ret)
			वापस ret;

		अगर ((पंचांगp32 & 0xfffffff0) == SISUSB_PCI_MMIOBASE)
			test++;

		ret |= sisusb_पढ़ो_pci_config(sisusb, 0x18, &पंचांगp32);
		अगर (ret)
			वापस ret;

		अगर ((पंचांगp32 & 0xfffffff0) == SISUSB_PCI_IOPORTBASE)
			test++;
	पूर्ण

	/* No? So reset the device */
	अगर ((sisusb->devinit == 0) || (test != 3)) अणु

		ret |= sisusb_करो_init_gfxdevice(sisusb);

		अगर (ret == 0)
			sisusb->devinit = 1;

	पूर्ण

	अगर (sisusb->devinit) अणु
		/* Initialize the graphics core */
		अगर (sisusb_init_gfxcore(sisusb) == 0) अणु
			sisusb->gfxinit = 1;
			sisusb_get_ramconfig(sisusb);
			sisusb_set_शेष_mode(sisusb, 1);
			ret |= sisusb_setup_screen(sisusb, 1, initscreen);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_USB_SISUSBVGA_CON

/* Set up शेष text mode:
 * - Set text mode (0x03)
 * - Upload शेष font
 * - Upload user font (अगर available)
 */

पूर्णांक sisusb_reset_text_mode(काष्ठा sisusb_usb_data *sisusb, पूर्णांक init)
अणु
	पूर्णांक ret = 0, slot = sisusb->font_slot, i;
	स्थिर काष्ठा font_desc *myfont;
	u8 *tempbuf;
	u16 *tempbufb;
	अटल स्थिर अक्षर bootstring[] =
		"SiSUSB VGA text console, (C) 2005 Thomas Winischhofer.";
	अटल स्थिर अक्षर bootlogo[] = "(o_ //\\ V_/_";

	/* sisusb->lock is करोwn */

	अगर (!sisusb->SiS_Pr)
		वापस 1;

	sisusb->SiS_Pr->IOAddress = SISUSB_PCI_IOPORTBASE + 0x30;
	sisusb->SiS_Pr->sisusb = (व्योम *)sisusb;

	/* Set mode 0x03 */
	SiSUSBSetMode(sisusb->SiS_Pr, 0x03);

	myfont = find_font("VGA8x16");
	अगर (!myfont)
		वापस 1;

	tempbuf = vदो_स्मृति(8192);
	अगर (!tempbuf)
		वापस 1;

	क्रम (i = 0; i < 256; i++)
		स_नकल(tempbuf + (i * 32), myfont->data + (i * 16), 16);

	/* Upload शेष font */
	ret = sisusbcon_करो_font_op(sisusb, 1, 0, tempbuf, 8192,
			0, 1, शून्य, 16, 0);

	vमुक्त(tempbuf);

	/* Upload user font (and reset current slot) */
	अगर (sisusb->font_backup) अणु
		ret |= sisusbcon_करो_font_op(sisusb, 1, 2, sisusb->font_backup,
				8192, sisusb->font_backup_512, 1, शून्य,
				sisusb->font_backup_height, 0);
		अगर (slot != 2)
			sisusbcon_करो_font_op(sisusb, 1, 0, शून्य, 0, 0, 1,
					शून्य, 16, 0);
	पूर्ण

	अगर (init && !sisusb->scrbuf) अणु

		tempbuf = vदो_स्मृति(8192);
		अगर (tempbuf) अणु

			i = 4096;
			tempbufb = (u16 *)tempbuf;
			जबतक (i--)
				*(tempbufb++) = 0x0720;

			i = 0;
			tempbufb = (u16 *)tempbuf;
			जबतक (bootlogo[i]) अणु
				*(tempbufb++) = 0x0700 | bootlogo[i++];
				अगर (!(i % 4))
					tempbufb += 76;
			पूर्ण

			i = 0;
			tempbufb = (u16 *)tempbuf + 6;
			जबतक (bootstring[i])
				*(tempbufb++) = 0x0700 | bootstring[i++];

			ret |= sisusb_copy_memory(sisusb, tempbuf,
					sisusb->vrambase, 8192);

			vमुक्त(tempbuf);

		पूर्ण

	पूर्ण अन्यथा अगर (sisusb->scrbuf) अणु
		ret |= sisusb_copy_memory(sisusb, (u8 *)sisusb->scrbuf,
				sisusb->vrambase, sisusb->scrbuf_size);
	पूर्ण

	अगर (sisusb->sisusb_cursor_size_from >= 0 &&
			sisusb->sisusb_cursor_माप_प्रकारo >= 0) अणु
		sisusb_setidxreg(sisusb, SISCR, 0x0a,
				sisusb->sisusb_cursor_size_from);
		sisusb_setidxreganकरोr(sisusb, SISCR, 0x0b, 0xe0,
				sisusb->sisusb_cursor_माप_प्रकारo);
	पूर्ण अन्यथा अणु
		sisusb_setidxreg(sisusb, SISCR, 0x0a, 0x2d);
		sisusb_setidxreg(sisusb, SISCR, 0x0b, 0x0e);
		sisusb->sisusb_cursor_माप_प्रकारo = -1;
	पूर्ण

	slot = sisusb->sisusb_cursor_loc;
	अगर (slot < 0)
		slot = 0;

	sisusb->sisusb_cursor_loc = -1;
	sisusb->bad_cursor_pos = 1;

	sisusb_set_cursor(sisusb, slot);

	sisusb_setidxreg(sisusb, SISCR, 0x0c, (sisusb->cur_start_addr >> 8));
	sisusb_setidxreg(sisusb, SISCR, 0x0d, (sisusb->cur_start_addr & 0xff));

	sisusb->texपंचांगodedestroyed = 0;

	/* sisusb->lock is करोwn */

	वापस ret;
पूर्ण

#पूर्ण_अगर

/* fops */

अटल पूर्णांक sisusb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&sisusb_driver, subminor);
	अगर (!पूर्णांकerface)
		वापस -ENODEV;

	sisusb = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	अगर (!sisusb->present || !sisusb->पढ़ोy) अणु
		mutex_unlock(&sisusb->lock);
		वापस -ENODEV;
	पूर्ण

	अगर (sisusb->isखोलो) अणु
		mutex_unlock(&sisusb->lock);
		वापस -EBUSY;
	पूर्ण

	अगर (!sisusb->devinit) अणु
		अगर (sisusb->sisusb_dev->speed == USB_SPEED_HIGH ||
				sisusb->sisusb_dev->speed >= USB_SPEED_SUPER) अणु
			अगर (sisusb_init_gfxdevice(sisusb, 0)) अणु
				mutex_unlock(&sisusb->lock);
				dev_err(&sisusb->sisusb_dev->dev,
						"Failed to initialize device\n");
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा अणु
			mutex_unlock(&sisusb->lock);
			dev_err(&sisusb->sisusb_dev->dev,
					"Device not attached to USB 2.0 hub\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Increment usage count क्रम our sisusb */
	kref_get(&sisusb->kref);

	sisusb->isखोलो = 1;

	file->निजी_data = sisusb;

	mutex_unlock(&sisusb->lock);

	वापस 0;
पूर्ण

व्योम sisusb_delete(काष्ठा kref *kref)
अणु
	काष्ठा sisusb_usb_data *sisusb = to_sisusb_dev(kref);

	अगर (!sisusb)
		वापस;

	usb_put_dev(sisusb->sisusb_dev);

	sisusb->sisusb_dev = शून्य;
	sisusb_मुक्त_buffers(sisusb);
	sisusb_मुक्त_urbs(sisusb);
#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	kमुक्त(sisusb->SiS_Pr);
#पूर्ण_अगर
	kमुक्त(sisusb);
पूर्ण

अटल पूर्णांक sisusb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	sisusb = file->निजी_data;
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	अगर (sisusb->present) अणु
		/* Wait क्रम all URBs to finish अगर device still present */
		अगर (!sisusb_रुको_all_out_complete(sisusb))
			sisusb_समाप्त_all_busy(sisusb);
	पूर्ण

	sisusb->isखोलो = 0;
	file->निजी_data = शून्य;

	mutex_unlock(&sisusb->lock);

	/* decrement the usage count on our device */
	kref_put(&sisusb->kref, sisusb_delete);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sisusb_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	sमाप_प्रकार bytes_पढ़ो = 0;
	पूर्णांक त्रुटि_सं = 0;
	u8 buf8;
	u16 buf16;
	u32 buf32, address;

	sisusb = file->निजी_data;
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	अगर (!sisusb->present || !sisusb->पढ़ोy || !sisusb->sisusb_dev) अणु
		mutex_unlock(&sisusb->lock);
		वापस -ENODEV;
	पूर्ण

	अगर ((*ppos) >= SISUSB_PCI_PSEUDO_IOPORTBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_IOPORTBASE + 128) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_IOPORTBASE +
				SISUSB_PCI_IOPORTBASE;

		/* Read i/o ports
		 * Byte, word and दीर्घ(32) can be पढ़ो. As this
		 * emulates inX inकाष्ठाions, the data वापसed is
		 * in machine-endianness.
		 */
		चयन (count) अणु
		हाल 1:
			अगर (sisusb_पढ़ो_memio_byte(sisusb, SISUSB_TYPE_IO,
					address, &buf8))
				त्रुटि_सं = -EIO;
			अन्यथा अगर (put_user(buf8, (u8 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा
				bytes_पढ़ो = 1;

			अवरोध;

		हाल 2:
			अगर (sisusb_पढ़ो_memio_word(sisusb, SISUSB_TYPE_IO,
					address, &buf16))
				त्रुटि_सं = -EIO;
			अन्यथा अगर (put_user(buf16, (u16 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा
				bytes_पढ़ो = 2;

			अवरोध;

		हाल 4:
			अगर (sisusb_पढ़ो_memio_दीर्घ(sisusb, SISUSB_TYPE_IO,
					address, &buf32))
				त्रुटि_सं = -EIO;
			अन्यथा अगर (put_user(buf32, (u32 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा
				bytes_पढ़ो = 4;

			अवरोध;

		शेष:
			त्रुटि_सं = -EIO;

		पूर्ण

	पूर्ण अन्यथा अगर ((*ppos) >= SISUSB_PCI_PSEUDO_MEMBASE && (*ppos) <
			SISUSB_PCI_PSEUDO_MEMBASE + sisusb->vramsize) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;

		/* Read video ram
		 * Remember: Data delivered is never endian-corrected
		 */
		त्रुटि_सं = sisusb_पढ़ो_mem_bulk(sisusb, address,
				शून्य, count, buffer, &bytes_पढ़ो);

		अगर (bytes_पढ़ो)
			त्रुटि_सं = bytes_पढ़ो;

	पूर्ण अन्यथा  अगर ((*ppos) >= SISUSB_PCI_PSEUDO_MMIOBASE &&
				(*ppos) <  SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOSIZE) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOBASE;

		/* Read MMIO
		 * Remember: Data delivered is never endian-corrected
		 */
		त्रुटि_सं = sisusb_पढ़ो_mem_bulk(sisusb, address,
				शून्य, count, buffer, &bytes_पढ़ो);

		अगर (bytes_पढ़ो)
			त्रुटि_सं = bytes_पढ़ो;

	पूर्ण अन्यथा  अगर ((*ppos) >= SISUSB_PCI_PSEUDO_PCIBASE &&
			(*ppos) <= SISUSB_PCI_PSEUDO_PCIBASE + 0x5c) अणु

		अगर (count != 4) अणु
			mutex_unlock(&sisusb->lock);
			वापस -EINVAL;
		पूर्ण

		address = (*ppos) - SISUSB_PCI_PSEUDO_PCIBASE;

		/* Read PCI config रेजिस्टर
		 * Return value delivered in machine endianness.
		 */
		अगर (sisusb_पढ़ो_pci_config(sisusb, address, &buf32))
			त्रुटि_सं = -EIO;
		अन्यथा अगर (put_user(buf32, (u32 __user *)buffer))
			त्रुटि_सं = -EFAULT;
		अन्यथा
			bytes_पढ़ो = 4;

	पूर्ण अन्यथा अणु

		त्रुटि_सं = -EBADFD;

	पूर्ण

	(*ppos) += bytes_पढ़ो;

	mutex_unlock(&sisusb->lock);

	वापस त्रुटि_सं ? त्रुटि_सं : bytes_पढ़ो;
पूर्ण

अटल sमाप_प्रकार sisusb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक त्रुटि_सं = 0;
	sमाप_प्रकार bytes_written = 0;
	u8 buf8;
	u16 buf16;
	u32 buf32, address;

	sisusb = file->निजी_data;
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	अगर (!sisusb->present || !sisusb->पढ़ोy || !sisusb->sisusb_dev) अणु
		mutex_unlock(&sisusb->lock);
		वापस -ENODEV;
	पूर्ण

	अगर ((*ppos) >= SISUSB_PCI_PSEUDO_IOPORTBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_IOPORTBASE + 128) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_IOPORTBASE +
				SISUSB_PCI_IOPORTBASE;

		/* Write i/o ports
		 * Byte, word and दीर्घ(32) can be written. As this
		 * emulates outX inकाष्ठाions, the data is expected
		 * in machine-endianness.
		 */
		चयन (count) अणु
		हाल 1:
			अगर (get_user(buf8, (u8 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा अगर (sisusb_ग_लिखो_memio_byte(sisusb,
					SISUSB_TYPE_IO, address, buf8))
				त्रुटि_सं = -EIO;
			अन्यथा
				bytes_written = 1;

			अवरोध;

		हाल 2:
			अगर (get_user(buf16, (u16 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा अगर (sisusb_ग_लिखो_memio_word(sisusb,
					SISUSB_TYPE_IO, address, buf16))
				त्रुटि_सं = -EIO;
			अन्यथा
				bytes_written = 2;

			अवरोध;

		हाल 4:
			अगर (get_user(buf32, (u32 __user *)buffer))
				त्रुटि_सं = -EFAULT;
			अन्यथा अगर (sisusb_ग_लिखो_memio_दीर्घ(sisusb,
					SISUSB_TYPE_IO, address, buf32))
				त्रुटि_सं = -EIO;
			अन्यथा
				bytes_written = 4;

			अवरोध;

		शेष:
			त्रुटि_सं = -EIO;
		पूर्ण

	पूर्ण अन्यथा अगर ((*ppos) >= SISUSB_PCI_PSEUDO_MEMBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_MEMBASE +
			sisusb->vramsize) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;

		/* Write video ram.
		 * Buffer is copied 1:1, thereक्रमe, on big-endian
		 * machines, the data must be swapped by userland
		 * in advance (अगर applicable; no swapping in 8bpp
		 * mode or अगर YUV data is being transferred).
		 */
		त्रुटि_सं = sisusb_ग_लिखो_mem_bulk(sisusb, address, शून्य,
				count, buffer, 0, &bytes_written);

		अगर (bytes_written)
			त्रुटि_सं = bytes_written;

	पूर्ण अन्यथा  अगर ((*ppos) >= SISUSB_PCI_PSEUDO_MMIOBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_MMIOBASE +
			SISUSB_PCI_MMIOSIZE) अणु

		address = (*ppos) - SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOBASE;

		/* Write MMIO.
		 * Buffer is copied 1:1, thereक्रमe, on big-endian
		 * machines, the data must be swapped by userland
		 * in advance.
		 */
		त्रुटि_सं = sisusb_ग_लिखो_mem_bulk(sisusb, address, शून्य,
				count, buffer, 0, &bytes_written);

		अगर (bytes_written)
			त्रुटि_सं = bytes_written;

	पूर्ण अन्यथा  अगर ((*ppos) >= SISUSB_PCI_PSEUDO_PCIBASE &&
				(*ppos) <= SISUSB_PCI_PSEUDO_PCIBASE +
				SISUSB_PCI_PCONFSIZE) अणु

		अगर (count != 4) अणु
			mutex_unlock(&sisusb->lock);
			वापस -EINVAL;
		पूर्ण

		address = (*ppos) - SISUSB_PCI_PSEUDO_PCIBASE;

		/* Write PCI config रेजिस्टर.
		 * Given value expected in machine endianness.
		 */
		अगर (get_user(buf32, (u32 __user *)buffer))
			त्रुटि_सं = -EFAULT;
		अन्यथा अगर (sisusb_ग_लिखो_pci_config(sisusb, address, buf32))
			त्रुटि_सं = -EIO;
		अन्यथा
			bytes_written = 4;


	पूर्ण अन्यथा अणु

		/* Error */
		त्रुटि_सं = -EBADFD;

	पूर्ण

	(*ppos) += bytes_written;

	mutex_unlock(&sisusb->lock);

	वापस त्रुटि_सं ? त्रुटि_सं : bytes_written;
पूर्ण

अटल loff_t sisusb_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	loff_t ret;

	sisusb = file->निजी_data;
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	अगर (!sisusb->present || !sisusb->पढ़ोy || !sisusb->sisusb_dev) अणु
		mutex_unlock(&sisusb->lock);
		वापस -ENODEV;
	पूर्ण

	ret = no_seek_end_llseek(file, offset, orig);

	mutex_unlock(&sisusb->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sisusb_handle_command(काष्ठा sisusb_usb_data *sisusb,
		काष्ठा sisusb_command *y, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक	retval, length;
	u32	port, address;

	/* All our commands require the device
	 * to be initialized.
	 */
	अगर (!sisusb->devinit)
		वापस -ENODEV;

	port = y->data3 -
		SISUSB_PCI_PSEUDO_IOPORTBASE +
		SISUSB_PCI_IOPORTBASE;

	चयन (y->operation) अणु
	हाल SUCMD_GET:
		retval = sisusb_getidxreg(sisusb, port, y->data0, &y->data1);
		अगर (!retval) अणु
			अगर (copy_to_user((व्योम __user *)arg, y, माप(*y)))
				retval = -EFAULT;
		पूर्ण
		अवरोध;

	हाल SUCMD_SET:
		retval = sisusb_setidxreg(sisusb, port, y->data0, y->data1);
		अवरोध;

	हाल SUCMD_SETOR:
		retval = sisusb_setidxregor(sisusb, port, y->data0, y->data1);
		अवरोध;

	हाल SUCMD_SETAND:
		retval = sisusb_setidxregand(sisusb, port, y->data0, y->data1);
		अवरोध;

	हाल SUCMD_SETANDOR:
		retval = sisusb_setidxreganकरोr(sisusb, port, y->data0,
				y->data1, y->data2);
		अवरोध;

	हाल SUCMD_SETMASK:
		retval = sisusb_setidxregmask(sisusb, port, y->data0,
				y->data1, y->data2);
		अवरोध;

	हाल SUCMD_CLRSCR:
		/* Gfx core must be initialized */
		अगर (!sisusb->gfxinit)
			वापस -ENODEV;

		length = (y->data0 << 16) | (y->data1 << 8) | y->data2;
		address = y->data3 - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;
		retval = sisusb_clear_vram(sisusb, address, length);
		अवरोध;

	हाल SUCMD_HANDLETEXTMODE:
		retval = 0;
#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
		/* Gfx core must be initialized, SiS_Pr must exist */
		अगर (!sisusb->gfxinit || !sisusb->SiS_Pr)
			वापस -ENODEV;

		चयन (y->data0) अणु
		हाल 0:
			retval = sisusb_reset_text_mode(sisusb, 0);
			अवरोध;
		हाल 1:
			sisusb->texपंचांगodedestroyed = 1;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अवरोध;

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	हाल SUCMD_SETMODE:
		/* Gfx core must be initialized, SiS_Pr must exist */
		अगर (!sisusb->gfxinit || !sisusb->SiS_Pr)
			वापस -ENODEV;

		retval = 0;

		sisusb->SiS_Pr->IOAddress = SISUSB_PCI_IOPORTBASE + 0x30;
		sisusb->SiS_Pr->sisusb = (व्योम *)sisusb;

		अगर (SiSUSBSetMode(sisusb->SiS_Pr, y->data3))
			retval = -EINVAL;

		अवरोध;

	हाल SUCMD_SETVESAMODE:
		/* Gfx core must be initialized, SiS_Pr must exist */
		अगर (!sisusb->gfxinit || !sisusb->SiS_Pr)
			वापस -ENODEV;

		retval = 0;

		sisusb->SiS_Pr->IOAddress = SISUSB_PCI_IOPORTBASE + 0x30;
		sisusb->SiS_Pr->sisusb = (व्योम *)sisusb;

		अगर (SiSUSBSetVESAMode(sisusb->SiS_Pr, y->data3))
			retval = -EINVAL;

		अवरोध;
#पूर्ण_अगर

	शेष:
		retval = -EINVAL;
	पूर्ण

	अगर (retval > 0)
		retval = -EIO;

	वापस retval;
पूर्ण

अटल दीर्घ sisusb_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	काष्ठा sisusb_info x;
	काष्ठा sisusb_command y;
	दीर्घ retval = 0;
	u32 __user *argp = (u32 __user *)arg;

	sisusb = file->निजी_data;
	अगर (!sisusb)
		वापस -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	अगर (!sisusb->present || !sisusb->पढ़ोy || !sisusb->sisusb_dev) अणु
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	चयन (cmd) अणु
	हाल SISUSB_GET_CONFIG_SIZE:

		अगर (put_user(माप(x), argp))
			retval = -EFAULT;

		अवरोध;

	हाल SISUSB_GET_CONFIG:

		x.sisusb_id = SISUSB_ID;
		x.sisusb_version = SISUSB_VERSION;
		x.sisusb_revision = SISUSB_REVISION;
		x.sisusb_patchlevel = SISUSB_PATCHLEVEL;
		x.sisusb_gfxinit = sisusb->gfxinit;
		x.sisusb_vrambase = SISUSB_PCI_PSEUDO_MEMBASE;
		x.sisusb_mmiobase = SISUSB_PCI_PSEUDO_MMIOBASE;
		x.sisusb_iobase = SISUSB_PCI_PSEUDO_IOPORTBASE;
		x.sisusb_pcibase = SISUSB_PCI_PSEUDO_PCIBASE;
		x.sisusb_vramsize = sisusb->vramsize;
		x.sisusb_minor = sisusb->minor;
		x.sisusb_fbdevactive = 0;
#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
		x.sisusb_conactive  = sisusb->haveconsole ? 1 : 0;
#अन्यथा
		x.sisusb_conactive  = 0;
#पूर्ण_अगर
		स_रखो(x.sisusb_reserved, 0, माप(x.sisusb_reserved));

		अगर (copy_to_user((व्योम __user *)arg, &x, माप(x)))
			retval = -EFAULT;

		अवरोध;

	हाल SISUSB_COMMAND:

		अगर (copy_from_user(&y, (व्योम __user *)arg, माप(y)))
			retval = -EFAULT;
		अन्यथा
			retval = sisusb_handle_command(sisusb, &y, arg);

		अवरोध;

	शेष:
		retval = -ENOTTY;
		अवरोध;
	पूर्ण

err_out:
	mutex_unlock(&sisusb->lock);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ sisusb_compat_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SISUSB_GET_CONFIG_SIZE:
	हाल SISUSB_GET_CONFIG:
	हाल SISUSB_COMMAND:
		वापस sisusb_ioctl(f, cmd, arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations usb_sisusb_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		sisusb_खोलो,
	.release =	sisusb_release,
	.पढ़ो =		sisusb_पढ़ो,
	.ग_लिखो =	sisusb_ग_लिखो,
	.llseek =	sisusb_lseek,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = sisusb_compat_ioctl,
#पूर्ण_अगर
	.unlocked_ioctl = sisusb_ioctl
पूर्ण;

अटल काष्ठा usb_class_driver usb_sisusb_class = अणु
	.name =		"sisusbvga%d",
	.fops =		&usb_sisusb_fops,
	.minor_base =	SISUSB_MINOR
पूर्ण;

अटल पूर्णांक sisusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक retval = 0, i;

	dev_info(&dev->dev, "USB2VGA dongle found at address %d\n",
			dev->devnum);

	/* Allocate memory क्रम our निजी */
	sisusb = kzalloc(माप(*sisusb), GFP_KERNEL);
	अगर (!sisusb)
		वापस -ENOMEM;

	kref_init(&sisusb->kref);

	mutex_init(&(sisusb->lock));

	sisusb->sisusb_dev = dev;
	sisusb->vrambase   = SISUSB_PCI_MEMBASE;
	sisusb->mmiobase   = SISUSB_PCI_MMIOBASE;
	sisusb->mmiosize   = SISUSB_PCI_MMIOSIZE;
	sisusb->ioportbase = SISUSB_PCI_IOPORTBASE;
	/* Everything अन्यथा is zero */

	/* Register device */
	retval = usb_रेजिस्टर_dev(पूर्णांकf, &usb_sisusb_class);
	अगर (retval) अणु
		dev_err(&sisusb->sisusb_dev->dev,
				"Failed to get a minor for device %d\n",
				dev->devnum);
		retval = -ENODEV;
		जाओ error_1;
	पूर्ण

	sisusb->minor = पूर्णांकf->minor;

	/* Allocate buffers */
	sisusb->ibufsize = SISUSB_IBUF_SIZE;
	sisusb->ibuf = kदो_स्मृति(SISUSB_IBUF_SIZE, GFP_KERNEL);
	अगर (!sisusb->ibuf) अणु
		retval = -ENOMEM;
		जाओ error_2;
	पूर्ण

	sisusb->numobufs = 0;
	sisusb->obufsize = SISUSB_OBUF_SIZE;
	क्रम (i = 0; i < NUMOBUFS; i++) अणु
		sisusb->obuf[i] = kदो_स्मृति(SISUSB_OBUF_SIZE, GFP_KERNEL);
		अगर (!sisusb->obuf[i]) अणु
			अगर (i == 0) अणु
				retval = -ENOMEM;
				जाओ error_3;
			पूर्ण
			अवरोध;
		पूर्ण
		sisusb->numobufs++;
	पूर्ण

	/* Allocate URBs */
	sisusb->sisurbin = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!sisusb->sisurbin) अणु
		retval = -ENOMEM;
		जाओ error_3;
	पूर्ण
	sisusb->completein = 1;

	क्रम (i = 0; i < sisusb->numobufs; i++) अणु
		sisusb->sisurbout[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!sisusb->sisurbout[i]) अणु
			retval = -ENOMEM;
			जाओ error_4;
		पूर्ण
		sisusb->urbout_context[i].sisusb = (व्योम *)sisusb;
		sisusb->urbout_context[i].urbindex = i;
		sisusb->urbstatus[i] = 0;
	पूर्ण

	dev_info(&sisusb->sisusb_dev->dev, "Allocated %d output buffers\n",
			sisusb->numobufs);

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	/* Allocate our SiS_Pr */
	sisusb->SiS_Pr = kदो_स्मृति(माप(काष्ठा SiS_Private), GFP_KERNEL);
	अगर (!sisusb->SiS_Pr) अणु
		retval = -ENOMEM;
		जाओ error_4;
	पूर्ण
#पूर्ण_अगर

	/* Do reमुख्यing init stuff */

	init_रुकोqueue_head(&sisusb->रुको_q);

	usb_set_पूर्णांकfdata(पूर्णांकf, sisusb);

	usb_get_dev(sisusb->sisusb_dev);

	sisusb->present = 1;

	अगर (dev->speed == USB_SPEED_HIGH || dev->speed >= USB_SPEED_SUPER) अणु
		पूर्णांक initscreen = 1;
#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
		अगर (sisusb_first_vc > 0 && sisusb_last_vc > 0 &&
				sisusb_first_vc <= sisusb_last_vc &&
				sisusb_last_vc <= MAX_NR_CONSOLES)
			initscreen = 0;
#पूर्ण_अगर
		अगर (sisusb_init_gfxdevice(sisusb, initscreen))
			dev_err(&sisusb->sisusb_dev->dev,
					"Failed to early initialize device\n");

	पूर्ण अन्यथा
		dev_info(&sisusb->sisusb_dev->dev,
				"Not attached to USB 2.0 hub, deferring init\n");

	sisusb->पढ़ोy = 1;

#अगर_घोषित SISUSBENDIANTEST
	dev_dbg(&sisusb->sisusb_dev->dev, "*** RWTEST ***\n");
	sisusb_testपढ़ोग_लिखो(sisusb);
	dev_dbg(&sisusb->sisusb_dev->dev, "*** RWTEST END ***\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	sisusb_console_init(sisusb, sisusb_first_vc, sisusb_last_vc);
#पूर्ण_अगर

	वापस 0;

error_4:
	sisusb_मुक्त_urbs(sisusb);
error_3:
	sisusb_मुक्त_buffers(sisusb);
error_2:
	usb_deरेजिस्टर_dev(पूर्णांकf, &usb_sisusb_class);
error_1:
	kमुक्त(sisusb);
	वापस retval;
पूर्ण

अटल व्योम sisusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	/* This should *not* happen */
	sisusb = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!sisusb)
		वापस;

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	sisusb_console_निकास(sisusb);
#पूर्ण_अगर

	usb_deरेजिस्टर_dev(पूर्णांकf, &usb_sisusb_class);

	mutex_lock(&sisusb->lock);

	/* Wait क्रम all URBs to complete and समाप्त them in हाल (MUST करो) */
	अगर (!sisusb_रुको_all_out_complete(sisusb))
		sisusb_समाप्त_all_busy(sisusb);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	sisusb->present = 0;
	sisusb->पढ़ोy = 0;

	mutex_unlock(&sisusb->lock);

	/* decrement our usage count */
	kref_put(&sisusb->kref, sisusb_delete);
पूर्ण

अटल स्थिर काष्ठा usb_device_id sisusb_table[] = अणु
	अणु USB_DEVICE(0x0711, 0x0550) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0900) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0901) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0902) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0903) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0918) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0920) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x0950) पूर्ण,
	अणु USB_DEVICE(0x0711, 0x5200) पूर्ण,
	अणु USB_DEVICE(0x182d, 0x021c) पूर्ण,
	अणु USB_DEVICE(0x182d, 0x0269) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, sisusb_table);

अटल काष्ठा usb_driver sisusb_driver = अणु
	.name =		"sisusb",
	.probe =	sisusb_probe,
	.disconnect =	sisusb_disconnect,
	.id_table =	sisusb_table,
पूर्ण;

अटल पूर्णांक __init usb_sisusb_init(व्योम)
अणु

#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	sisusb_init_concode();
#पूर्ण_अगर

	वापस usb_रेजिस्टर(&sisusb_driver);
पूर्ण

अटल व्योम __निकास usb_sisusb_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&sisusb_driver);
पूर्ण

module_init(usb_sisusb_init);
module_निकास(usb_sisusb_निकास);

MODULE_AUTHOR("Thomas Winischhofer <thomas@winischhofer.net>");
MODULE_DESCRIPTION("sisusbvga - Driver for Net2280/SiS315-based USB2VGA dongles");
MODULE_LICENSE("GPL");

