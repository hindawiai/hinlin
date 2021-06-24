<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/sock.h>

#समावेश "usbip_common.h"

#घोषणा DRIVER_AUTHOR "Takahiro Hirofuchi <hirofuchi@users.sourceforge.net>"
#घोषणा DRIVER_DESC "USB/IP Core"

#अगर_घोषित CONFIG_USBIP_DEBUG
अचिन्हित दीर्घ usbip_debug_flag = 0xffffffff;
#अन्यथा
अचिन्हित दीर्घ usbip_debug_flag;
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(usbip_debug_flag);
module_param(usbip_debug_flag, uदीर्घ, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(usbip_debug_flag, "debug flags (defined in usbip_common.h)");

/* FIXME */
काष्ठा device_attribute dev_attr_usbip_debug;
EXPORT_SYMBOL_GPL(dev_attr_usbip_debug);

अटल sमाप_प्रकार usbip_debug_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lx\n", usbip_debug_flag);
पूर्ण

अटल sमाप_प्रकार usbip_debug_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अगर (माला_पूछो(buf, "%lx", &usbip_debug_flag) != 1)
		वापस -EINVAL;
	वापस count;
पूर्ण
DEVICE_ATTR_RW(usbip_debug);

अटल व्योम usbip_dump_buffer(अक्षर *buff, पूर्णांक bufflen)
अणु
	prपूर्णांक_hex_dump(KERN_DEBUG, "usbip-core", DUMP_PREFIX_OFFSET, 16, 4,
		       buff, bufflen, false);
पूर्ण

अटल व्योम usbip_dump_pipe(अचिन्हित पूर्णांक p)
अणु
	अचिन्हित अक्षर type = usb_pipetype(p);
	अचिन्हित अक्षर ep   = usb_pipeendpoपूर्णांक(p);
	अचिन्हित अक्षर dev  = usb_pipedevice(p);
	अचिन्हित अक्षर dir  = usb_pipein(p);

	pr_debug("dev(%d) ep(%d) [%s] ", dev, ep, dir ? "IN" : "OUT");

	चयन (type) अणु
	हाल PIPE_ISOCHRONOUS:
		pr_debug("ISO\n");
		अवरोध;
	हाल PIPE_INTERRUPT:
		pr_debug("INT\n");
		अवरोध;
	हाल PIPE_CONTROL:
		pr_debug("CTRL\n");
		अवरोध;
	हाल PIPE_BULK:
		pr_debug("BULK\n");
		अवरोध;
	शेष:
		pr_debug("ERR\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usbip_dump_usb_device(काष्ठा usb_device *udev)
अणु
	काष्ठा device *dev = &udev->dev;
	पूर्णांक i;

	dev_dbg(dev, "       devnum(%d) devpath(%s) usb speed(%s)",
		udev->devnum, udev->devpath, usb_speed_string(udev->speed));

	pr_debug("tt hub ttport %d\n", udev->ttport);

	dev_dbg(dev, "                    ");
	क्रम (i = 0; i < 16; i++)
		pr_debug(" %2u", i);
	pr_debug("\n");

	dev_dbg(dev, "       toggle0(IN) :");
	क्रम (i = 0; i < 16; i++)
		pr_debug(" %2u", (udev->toggle[0] & (1 << i)) ? 1 : 0);
	pr_debug("\n");

	dev_dbg(dev, "       toggle1(OUT):");
	क्रम (i = 0; i < 16; i++)
		pr_debug(" %2u", (udev->toggle[1] & (1 << i)) ? 1 : 0);
	pr_debug("\n");

	dev_dbg(dev, "       epmaxp_in   :");
	क्रम (i = 0; i < 16; i++) अणु
		अगर (udev->ep_in[i])
			pr_debug(" %2u",
			    le16_to_cpu(udev->ep_in[i]->desc.wMaxPacketSize));
	पूर्ण
	pr_debug("\n");

	dev_dbg(dev, "       epmaxp_out  :");
	क्रम (i = 0; i < 16; i++) अणु
		अगर (udev->ep_out[i])
			pr_debug(" %2u",
			    le16_to_cpu(udev->ep_out[i]->desc.wMaxPacketSize));
	पूर्ण
	pr_debug("\n");

	dev_dbg(dev, "parent %s, bus %s\n", dev_name(&udev->parent->dev),
		udev->bus->bus_name);

	dev_dbg(dev, "have_langid %d, string_langid %d\n",
		udev->have_langid, udev->string_langid);

	dev_dbg(dev, "maxchild %d\n", udev->maxchild);
पूर्ण

अटल व्योम usbip_dump_request_type(__u8 rt)
अणु
	चयन (rt & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		pr_debug("DEVICE");
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		pr_debug("INTERF");
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		pr_debug("ENDPOI");
		अवरोध;
	हाल USB_RECIP_OTHER:
		pr_debug("OTHER ");
		अवरोध;
	शेष:
		pr_debug("------");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usbip_dump_usb_ctrlrequest(काष्ठा usb_ctrlrequest *cmd)
अणु
	अगर (!cmd) अणु
		pr_debug("       : null pointer\n");
		वापस;
	पूर्ण

	pr_debug("       ");
	pr_debug("bRequestType(%02X) bRequest(%02X) wValue(%04X) wIndex(%04X) wLength(%04X) ",
		 cmd->bRequestType, cmd->bRequest,
		 cmd->wValue, cmd->wIndex, cmd->wLength);
	pr_debug("\n       ");

	अगर ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		pr_debug("STANDARD ");
		चयन (cmd->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			pr_debug("GET_STATUS\n");
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			pr_debug("CLEAR_FEAT\n");
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			pr_debug("SET_FEAT\n");
			अवरोध;
		हाल USB_REQ_SET_ADDRESS:
			pr_debug("SET_ADDRRS\n");
			अवरोध;
		हाल USB_REQ_GET_DESCRIPTOR:
			pr_debug("GET_DESCRI\n");
			अवरोध;
		हाल USB_REQ_SET_DESCRIPTOR:
			pr_debug("SET_DESCRI\n");
			अवरोध;
		हाल USB_REQ_GET_CONFIGURATION:
			pr_debug("GET_CONFIG\n");
			अवरोध;
		हाल USB_REQ_SET_CONFIGURATION:
			pr_debug("SET_CONFIG\n");
			अवरोध;
		हाल USB_REQ_GET_INTERFACE:
			pr_debug("GET_INTERF\n");
			अवरोध;
		हाल USB_REQ_SET_INTERFACE:
			pr_debug("SET_INTERF\n");
			अवरोध;
		हाल USB_REQ_SYNCH_FRAME:
			pr_debug("SYNC_FRAME\n");
			अवरोध;
		शेष:
			pr_debug("REQ(%02X)\n", cmd->bRequest);
			अवरोध;
		पूर्ण
		usbip_dump_request_type(cmd->bRequestType);
	पूर्ण अन्यथा अगर ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_CLASS) अणु
		pr_debug("CLASS\n");
	पूर्ण अन्यथा अगर ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_VENDOR) अणु
		pr_debug("VENDOR\n");
	पूर्ण अन्यथा अगर ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_RESERVED) अणु
		pr_debug("RESERVED\n");
	पूर्ण
पूर्ण

व्योम usbip_dump_urb(काष्ठा urb *urb)
अणु
	काष्ठा device *dev;

	अगर (!urb) अणु
		pr_debug("urb: null pointer!!\n");
		वापस;
	पूर्ण

	अगर (!urb->dev) अणु
		pr_debug("urb->dev: null pointer!!\n");
		वापस;
	पूर्ण

	dev = &urb->dev->dev;

	usbip_dump_usb_device(urb->dev);

	dev_dbg(dev, "   pipe                  :%08x ", urb->pipe);

	usbip_dump_pipe(urb->pipe);

	dev_dbg(dev, "   status                :%d\n", urb->status);
	dev_dbg(dev, "   transfer_flags        :%08X\n", urb->transfer_flags);
	dev_dbg(dev, "   transfer_buffer_length:%d\n",
						urb->transfer_buffer_length);
	dev_dbg(dev, "   actual_length         :%d\n", urb->actual_length);

	अगर (urb->setup_packet && usb_pipetype(urb->pipe) == PIPE_CONTROL)
		usbip_dump_usb_ctrlrequest(
			(काष्ठा usb_ctrlrequest *)urb->setup_packet);

	dev_dbg(dev, "   start_frame           :%d\n", urb->start_frame);
	dev_dbg(dev, "   number_of_packets     :%d\n", urb->number_of_packets);
	dev_dbg(dev, "   interval              :%d\n", urb->पूर्णांकerval);
	dev_dbg(dev, "   error_count           :%d\n", urb->error_count);
पूर्ण
EXPORT_SYMBOL_GPL(usbip_dump_urb);

व्योम usbip_dump_header(काष्ठा usbip_header *pdu)
अणु
	pr_debug("BASE: cmd %u seq %u devid %u dir %u ep %u\n",
		 pdu->base.command,
		 pdu->base.seqnum,
		 pdu->base.devid,
		 pdu->base.direction,
		 pdu->base.ep);

	चयन (pdu->base.command) अणु
	हाल USBIP_CMD_SUBMIT:
		pr_debug("USBIP_CMD_SUBMIT: x_flags %u x_len %u sf %u #p %d iv %d\n",
			 pdu->u.cmd_submit.transfer_flags,
			 pdu->u.cmd_submit.transfer_buffer_length,
			 pdu->u.cmd_submit.start_frame,
			 pdu->u.cmd_submit.number_of_packets,
			 pdu->u.cmd_submit.पूर्णांकerval);
		अवरोध;
	हाल USBIP_CMD_UNLINK:
		pr_debug("USBIP_CMD_UNLINK: seq %u\n",
			 pdu->u.cmd_unlink.seqnum);
		अवरोध;
	हाल USBIP_RET_SUBMIT:
		pr_debug("USBIP_RET_SUBMIT: st %d al %u sf %d #p %d ec %d\n",
			 pdu->u.ret_submit.status,
			 pdu->u.ret_submit.actual_length,
			 pdu->u.ret_submit.start_frame,
			 pdu->u.ret_submit.number_of_packets,
			 pdu->u.ret_submit.error_count);
		अवरोध;
	हाल USBIP_RET_UNLINK:
		pr_debug("USBIP_RET_UNLINK: status %d\n",
			 pdu->u.ret_unlink.status);
		अवरोध;
	शेष:
		/* NOT REACHED */
		pr_err("unknown command\n");
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbip_dump_header);

/* Receive data over TCP/IP. */
पूर्णांक usbip_recv(काष्ठा socket *sock, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक result;
	काष्ठा kvec iov = अणु.iov_base = buf, .iov_len = sizeपूर्ण;
	काष्ठा msghdr msg = अणु.msg_flags = MSG_NOSIGNALपूर्ण;
	पूर्णांक total = 0;

	अगर (!sock || !buf || !size)
		वापस -EINVAL;

	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, size);

	usbip_dbg_xmit("enter\n");

	करो अणु
		sock->sk->sk_allocation = GFP_NOIO;

		result = sock_recvmsg(sock, &msg, MSG_WAITALL);
		अगर (result <= 0)
			जाओ err;

		total += result;
	पूर्ण जबतक (msg_data_left(&msg));

	अगर (usbip_dbg_flag_xmit) अणु
		pr_debug("receiving....\n");
		usbip_dump_buffer(buf, size);
		pr_debug("received, osize %d ret %d size %zd total %d\n",
			 size, result, msg_data_left(&msg), total);
	पूर्ण

	वापस total;

err:
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_recv);

/* there may be more हालs to tweak the flags. */
अटल अचिन्हित पूर्णांक tweak_transfer_flags(अचिन्हित पूर्णांक flags)
अणु
	flags &= ~URB_NO_TRANSFER_DMA_MAP;
	वापस flags;
पूर्ण

अटल व्योम usbip_pack_cmd_submit(काष्ठा usbip_header *pdu, काष्ठा urb *urb,
				  पूर्णांक pack)
अणु
	काष्ठा usbip_header_cmd_submit *spdu = &pdu->u.cmd_submit;

	/*
	 * Some members are not still implemented in usbip. I hope this issue
	 * will be discussed when usbip is ported to other operating प्रणालीs.
	 */
	अगर (pack) अणु
		spdu->transfer_flags =
			tweak_transfer_flags(urb->transfer_flags);
		spdu->transfer_buffer_length	= urb->transfer_buffer_length;
		spdu->start_frame		= urb->start_frame;
		spdu->number_of_packets		= urb->number_of_packets;
		spdu->पूर्णांकerval			= urb->पूर्णांकerval;
	पूर्ण अन्यथा  अणु
		urb->transfer_flags         = spdu->transfer_flags;
		urb->transfer_buffer_length = spdu->transfer_buffer_length;
		urb->start_frame            = spdu->start_frame;
		urb->number_of_packets      = spdu->number_of_packets;
		urb->पूर्णांकerval               = spdu->पूर्णांकerval;
	पूर्ण
पूर्ण

अटल व्योम usbip_pack_ret_submit(काष्ठा usbip_header *pdu, काष्ठा urb *urb,
				  पूर्णांक pack)
अणु
	काष्ठा usbip_header_ret_submit *rpdu = &pdu->u.ret_submit;

	अगर (pack) अणु
		rpdu->status		= urb->status;
		rpdu->actual_length	= urb->actual_length;
		rpdu->start_frame	= urb->start_frame;
		rpdu->number_of_packets = urb->number_of_packets;
		rpdu->error_count	= urb->error_count;
	पूर्ण अन्यथा अणु
		urb->status		= rpdu->status;
		urb->actual_length	= rpdu->actual_length;
		urb->start_frame	= rpdu->start_frame;
		urb->number_of_packets = rpdu->number_of_packets;
		urb->error_count	= rpdu->error_count;
	पूर्ण
पूर्ण

व्योम usbip_pack_pdu(काष्ठा usbip_header *pdu, काष्ठा urb *urb, पूर्णांक cmd,
		    पूर्णांक pack)
अणु
	चयन (cmd) अणु
	हाल USBIP_CMD_SUBMIT:
		usbip_pack_cmd_submit(pdu, urb, pack);
		अवरोध;
	हाल USBIP_RET_SUBMIT:
		usbip_pack_ret_submit(pdu, urb, pack);
		अवरोध;
	शेष:
		/* NOT REACHED */
		pr_err("unknown command\n");
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbip_pack_pdu);

अटल व्योम correct_endian_basic(काष्ठा usbip_header_basic *base, पूर्णांक send)
अणु
	अगर (send) अणु
		base->command	= cpu_to_be32(base->command);
		base->seqnum	= cpu_to_be32(base->seqnum);
		base->devid	= cpu_to_be32(base->devid);
		base->direction	= cpu_to_be32(base->direction);
		base->ep	= cpu_to_be32(base->ep);
	पूर्ण अन्यथा अणु
		base->command	= be32_to_cpu(base->command);
		base->seqnum	= be32_to_cpu(base->seqnum);
		base->devid	= be32_to_cpu(base->devid);
		base->direction	= be32_to_cpu(base->direction);
		base->ep	= be32_to_cpu(base->ep);
	पूर्ण
पूर्ण

अटल व्योम correct_endian_cmd_submit(काष्ठा usbip_header_cmd_submit *pdu,
				      पूर्णांक send)
अणु
	अगर (send) अणु
		pdu->transfer_flags = cpu_to_be32(pdu->transfer_flags);

		cpu_to_be32s(&pdu->transfer_buffer_length);
		cpu_to_be32s(&pdu->start_frame);
		cpu_to_be32s(&pdu->number_of_packets);
		cpu_to_be32s(&pdu->पूर्णांकerval);
	पूर्ण अन्यथा अणु
		pdu->transfer_flags = be32_to_cpu(pdu->transfer_flags);

		be32_to_cpus(&pdu->transfer_buffer_length);
		be32_to_cpus(&pdu->start_frame);
		be32_to_cpus(&pdu->number_of_packets);
		be32_to_cpus(&pdu->पूर्णांकerval);
	पूर्ण
पूर्ण

अटल व्योम correct_endian_ret_submit(काष्ठा usbip_header_ret_submit *pdu,
				      पूर्णांक send)
अणु
	अगर (send) अणु
		cpu_to_be32s(&pdu->status);
		cpu_to_be32s(&pdu->actual_length);
		cpu_to_be32s(&pdu->start_frame);
		cpu_to_be32s(&pdu->number_of_packets);
		cpu_to_be32s(&pdu->error_count);
	पूर्ण अन्यथा अणु
		be32_to_cpus(&pdu->status);
		be32_to_cpus(&pdu->actual_length);
		be32_to_cpus(&pdu->start_frame);
		be32_to_cpus(&pdu->number_of_packets);
		be32_to_cpus(&pdu->error_count);
	पूर्ण
पूर्ण

अटल व्योम correct_endian_cmd_unlink(काष्ठा usbip_header_cmd_unlink *pdu,
				      पूर्णांक send)
अणु
	अगर (send)
		pdu->seqnum = cpu_to_be32(pdu->seqnum);
	अन्यथा
		pdu->seqnum = be32_to_cpu(pdu->seqnum);
पूर्ण

अटल व्योम correct_endian_ret_unlink(काष्ठा usbip_header_ret_unlink *pdu,
				      पूर्णांक send)
अणु
	अगर (send)
		cpu_to_be32s(&pdu->status);
	अन्यथा
		be32_to_cpus(&pdu->status);
पूर्ण

व्योम usbip_header_correct_endian(काष्ठा usbip_header *pdu, पूर्णांक send)
अणु
	__u32 cmd = 0;

	अगर (send)
		cmd = pdu->base.command;

	correct_endian_basic(&pdu->base, send);

	अगर (!send)
		cmd = pdu->base.command;

	चयन (cmd) अणु
	हाल USBIP_CMD_SUBMIT:
		correct_endian_cmd_submit(&pdu->u.cmd_submit, send);
		अवरोध;
	हाल USBIP_RET_SUBMIT:
		correct_endian_ret_submit(&pdu->u.ret_submit, send);
		अवरोध;
	हाल USBIP_CMD_UNLINK:
		correct_endian_cmd_unlink(&pdu->u.cmd_unlink, send);
		अवरोध;
	हाल USBIP_RET_UNLINK:
		correct_endian_ret_unlink(&pdu->u.ret_unlink, send);
		अवरोध;
	शेष:
		/* NOT REACHED */
		pr_err("unknown command\n");
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbip_header_correct_endian);

अटल व्योम usbip_iso_packet_correct_endian(
		काष्ठा usbip_iso_packet_descriptor *iso, पूर्णांक send)
अणु
	/* करोes not need all members. but copy all simply. */
	अगर (send) अणु
		iso->offset	= cpu_to_be32(iso->offset);
		iso->length	= cpu_to_be32(iso->length);
		iso->status	= cpu_to_be32(iso->status);
		iso->actual_length = cpu_to_be32(iso->actual_length);
	पूर्ण अन्यथा अणु
		iso->offset	= be32_to_cpu(iso->offset);
		iso->length	= be32_to_cpu(iso->length);
		iso->status	= be32_to_cpu(iso->status);
		iso->actual_length = be32_to_cpu(iso->actual_length);
	पूर्ण
पूर्ण

अटल व्योम usbip_pack_iso(काष्ठा usbip_iso_packet_descriptor *iso,
			   काष्ठा usb_iso_packet_descriptor *uiso, पूर्णांक pack)
अणु
	अगर (pack) अणु
		iso->offset		= uiso->offset;
		iso->length		= uiso->length;
		iso->status		= uiso->status;
		iso->actual_length	= uiso->actual_length;
	पूर्ण अन्यथा अणु
		uiso->offset		= iso->offset;
		uiso->length		= iso->length;
		uiso->status		= iso->status;
		uiso->actual_length	= iso->actual_length;
	पूर्ण
पूर्ण

/* must मुक्त buffer */
काष्ठा usbip_iso_packet_descriptor*
usbip_alloc_iso_desc_pdu(काष्ठा urb *urb, sमाप_प्रकार *bufflen)
अणु
	काष्ठा usbip_iso_packet_descriptor *iso;
	पूर्णांक np = urb->number_of_packets;
	sमाप_प्रकार size = np * माप(*iso);
	पूर्णांक i;

	iso = kzalloc(size, GFP_KERNEL);
	अगर (!iso)
		वापस शून्य;

	क्रम (i = 0; i < np; i++) अणु
		usbip_pack_iso(&iso[i], &urb->iso_frame_desc[i], 1);
		usbip_iso_packet_correct_endian(&iso[i], 1);
	पूर्ण

	*bufflen = size;

	वापस iso;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_alloc_iso_desc_pdu);

/* some members of urb must be substituted beक्रमe. */
पूर्णांक usbip_recv_iso(काष्ठा usbip_device *ud, काष्ठा urb *urb)
अणु
	व्योम *buff;
	काष्ठा usbip_iso_packet_descriptor *iso;
	पूर्णांक np = urb->number_of_packets;
	पूर्णांक size = np * माप(*iso);
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक total_length = 0;

	अगर (!usb_pipeisoc(urb->pipe))
		वापस 0;

	/* my Bluetooth करोngle माला_लो ISO URBs which are np = 0 */
	अगर (np == 0)
		वापस 0;

	buff = kzalloc(size, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	ret = usbip_recv(ud->tcp_socket, buff, size);
	अगर (ret != size) अणु
		dev_err(&urb->dev->dev, "recv iso_frame_descriptor, %d\n",
			ret);
		kमुक्त(buff);

		अगर (ud->side == USBIP_STUB || ud->side == USBIP_VUDC)
			usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		अन्यथा
			usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);

		वापस -EPIPE;
	पूर्ण

	iso = (काष्ठा usbip_iso_packet_descriptor *) buff;
	क्रम (i = 0; i < np; i++) अणु
		usbip_iso_packet_correct_endian(&iso[i], 0);
		usbip_pack_iso(&iso[i], &urb->iso_frame_desc[i], 0);
		total_length += urb->iso_frame_desc[i].actual_length;
	पूर्ण

	kमुक्त(buff);

	अगर (total_length != urb->actual_length) अणु
		dev_err(&urb->dev->dev,
			"total length of iso packets %d not equal to actual length of buffer %d\n",
			total_length, urb->actual_length);

		अगर (ud->side == USBIP_STUB || ud->side == USBIP_VUDC)
			usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		अन्यथा
			usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);

		वापस -EPIPE;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_recv_iso);

/*
 * This functions restores the padding which was हटाओd क्रम optimizing
 * the bandwidth during transfer over tcp/ip
 *
 * buffer and iso packets need to be stored and be in propeper endian in urb
 * beक्रमe calling this function
 */
व्योम usbip_pad_iso(काष्ठा usbip_device *ud, काष्ठा urb *urb)
अणु
	पूर्णांक np = urb->number_of_packets;
	पूर्णांक i;
	पूर्णांक actualoffset = urb->actual_length;

	अगर (!usb_pipeisoc(urb->pipe))
		वापस;

	/* अगर no packets or length of data is 0, then nothing to unpack */
	अगर (np == 0 || urb->actual_length == 0)
		वापस;

	/*
	 * अगर actual_length is transfer_buffer_length then no padding is
	 * present.
	 */
	अगर (urb->actual_length == urb->transfer_buffer_length)
		वापस;

	/*
	 * loop over all packets from last to first (to prevent overwriting
	 * memory when padding) and move them पूर्णांकo the proper place
	 */
	क्रम (i = np-1; i > 0; i--) अणु
		actualoffset -= urb->iso_frame_desc[i].actual_length;
		स_हटाओ(urb->transfer_buffer + urb->iso_frame_desc[i].offset,
			urb->transfer_buffer + actualoffset,
			urb->iso_frame_desc[i].actual_length);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbip_pad_iso);

/* some members of urb must be substituted beक्रमe. */
पूर्णांक usbip_recv_xbuff(काष्ठा usbip_device *ud, काष्ठा urb *urb)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक ret = 0;
	पूर्णांक recv;
	पूर्णांक size;
	पूर्णांक copy;
	पूर्णांक i;

	अगर (ud->side == USBIP_STUB || ud->side == USBIP_VUDC) अणु
		/* the direction of urb must be OUT. */
		अगर (usb_pipein(urb->pipe))
			वापस 0;

		size = urb->transfer_buffer_length;
	पूर्ण अन्यथा अणु
		/* the direction of urb must be IN. */
		अगर (usb_pipeout(urb->pipe))
			वापस 0;

		size = urb->actual_length;
	पूर्ण

	/* no need to recv xbuff */
	अगर (!(size > 0))
		वापस 0;

	अगर (size > urb->transfer_buffer_length)
		/* should not happen, probably malicious packet */
		जाओ error;

	अगर (urb->num_sgs) अणु
		copy = size;
		क्रम_each_sg(urb->sg, sg, urb->num_sgs, i) अणु
			पूर्णांक recv_size;

			अगर (copy < sg->length)
				recv_size = copy;
			अन्यथा
				recv_size = sg->length;

			recv = usbip_recv(ud->tcp_socket, sg_virt(sg),
						recv_size);

			अगर (recv != recv_size)
				जाओ error;

			copy -= recv;
			ret += recv;

			अगर (!copy)
				अवरोध;
		पूर्ण

		अगर (ret != size)
			जाओ error;
	पूर्ण अन्यथा अणु
		ret = usbip_recv(ud->tcp_socket, urb->transfer_buffer, size);
		अगर (ret != size)
			जाओ error;
	पूर्ण

	वापस ret;

error:
	dev_err(&urb->dev->dev, "recv xbuf, %d\n", ret);
	अगर (ud->side == USBIP_STUB || ud->side == USBIP_VUDC)
		usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
	अन्यथा
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);

	वापस -EPIPE;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_recv_xbuff);

अटल पूर्णांक __init usbip_core_init(व्योम)
अणु
	वापस usbip_init_eh();
पूर्ण

अटल व्योम __निकास usbip_core_निकास(व्योम)
अणु
	usbip_finish_eh();
	वापस;
पूर्ण

module_init(usbip_core_init);
module_निकास(usbip_core_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
