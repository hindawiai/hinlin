<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-usb.c - covers the USB part
 * see flexcop.c क्रम copyright inक्रमmation
 */
#घोषणा FC_LOG_PREFIX "flexcop_usb"
#समावेश "flexcop-usb.h"
#समावेश "flexcop-common.h"

/* Version inक्रमmation */
#घोषणा DRIVER_VERSION "0.1"
#घोषणा DRIVER_NAME "Technisat/B2C2 FlexCop II/IIb/III Digital TV USB Driver"
#घोषणा DRIVER_AUTHOR "Patrick Boettcher <patrick.boettcher@posteo.de>"

/* debug */
#अगर_घोषित CONFIG_DVB_B2C2_FLEXCOP_DEBUG
#घोषणा dprपूर्णांकk(level, args...) \
	करो अणु अगर ((debug & (level))) prपूर्णांकk(args); पूर्ण जबतक (0)

#घोषणा debug_dump(b, l, method) करो अणु\
	पूर्णांक i; \
	क्रम (i = 0; i < l; i++) \
		method("%02x ", b[i]); \
	method("\n"); \
पूर्ण जबतक (0)

#घोषणा DEBSTATUS ""
#अन्यथा
#घोषणा dprपूर्णांकk(level, args...) no_prपूर्णांकk(args)
#घोषणा debug_dump(b, l, method) करो अणु पूर्ण जबतक (0)
#घोषणा DEBSTATUS " (debugging is not enabled)"
#पूर्ण_अगर

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,ts=2,ctrl=4,i2c=8,v8mem=16 (or-able))." DEBSTATUS);
#अघोषित DEBSTATUS

#घोषणा deb_info(args...) dprपूर्णांकk(0x01, args)
#घोषणा deb_ts(args...) dprपूर्णांकk(0x02, args)
#घोषणा deb_ctrl(args...) dprपूर्णांकk(0x04, args)
#घोषणा deb_i2c(args...) dprपूर्णांकk(0x08, args)
#घोषणा deb_v8(args...) dprपूर्णांकk(0x10, args)

/* JLP 111700: we will include the 1 bit gap between the upper and lower 3 bits
 * in the IBI address, to make the V8 code simpler.
 * PCI ADDRESS FORMAT: 0x71C -> 0000 0111 0001 1100 (the six bits used)
 *                  in general: 0000 0HHH 000L LL00
 * IBI ADDRESS FORMAT:                    RHHH BLLL
 *
 * where R is the पढ़ो(1)/ग_लिखो(0) bit, B is the busy bit
 * and HHH and LLL are the two sets of three bits from the PCI address.
 */
#घोषणा B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR(usPCI) (u8) \
	(((usPCI >> 2) & 0x07) + ((usPCI >> 4) & 0x70))
#घोषणा B2C2_FLEX_INTERNALADDR_TO_PCIOFFSET(ucAddr) (u16) \
	(((ucAddr & 0x07) << 2) + ((ucAddr & 0x70) << 4))

/*
 * DKT 020228
 * - क्रमget about this VENDOR_BUFFER_SIZE, पढ़ो and ग_लिखो रेजिस्टर
 *   deal with DWORD or 4 bytes, that should be should from now on
 * - from now on, we करोn't support anything older than firm 1.00
 *   I eliminated the ग_लिखो रेजिस्टर as a 2 trip of writing hi word and lo word
 *   and क्रमce this to ग_लिखो only 4 bytes at a समय.
 *   NOTE: this should work with all the firmware from 1.00 and newer
 */
अटल पूर्णांक flexcop_usb_पढ़ोग_लिखो_dw(काष्ठा flexcop_device *fc, u16 wRegOffsPCI, u32 *val, u8 पढ़ो)
अणु
	काष्ठा flexcop_usb *fc_usb = fc->bus_specअगरic;
	u8 request = पढ़ो ? B2C2_USB_READ_REG : B2C2_USB_WRITE_REG;
	u8 request_type = (पढ़ो ? USB_सूची_IN : USB_सूची_OUT) | USB_TYPE_VENDOR;
	u8 wAddress = B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR(wRegOffsPCI) |
		(पढ़ो ? 0x80 : 0);
	पूर्णांक ret;

	mutex_lock(&fc_usb->data_mutex);
	अगर (!पढ़ो)
		स_नकल(fc_usb->data, val, माप(*val));

	ret = usb_control_msg(fc_usb->udev,
			पढ़ो ? B2C2_USB_CTRL_PIPE_IN : B2C2_USB_CTRL_PIPE_OUT,
			request,
			request_type, /* 0xc0 पढ़ो or 0x40 ग_लिखो */
			wAddress,
			0,
			fc_usb->data,
			माप(u32),
			B2C2_WAIT_FOR_OPERATION_RDW * HZ);

	अगर (ret != माप(u32)) अणु
		err("error while %s dword from %d (%d).", पढ़ो ? "reading" :
				"writing", wAddress, wRegOffsPCI);
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण

	अगर (पढ़ो && ret >= 0)
		स_नकल(val, fc_usb->data, माप(*val));
	mutex_unlock(&fc_usb->data_mutex);

	वापस ret;
पूर्ण
/*
 * DKT 010817 - add support क्रम V8 memory पढ़ो/ग_लिखो and flash update
 */
अटल पूर्णांक flexcop_usb_v8_memory_req(काष्ठा flexcop_usb *fc_usb,
		flexcop_usb_request_t req, u8 page, u16 wAddress,
		u8 *pbBuffer, u32 buflen)
अणु
	u8 request_type = USB_TYPE_VENDOR;
	u16 wIndex;
	पूर्णांक nWaitTime, pipe, ret;
	wIndex = page << 8;

	अगर (buflen > माप(fc_usb->data)) अणु
		err("Buffer size bigger than max URB control message\n");
		वापस -EIO;
	पूर्ण

	चयन (req) अणु
	हाल B2C2_USB_READ_V8_MEM:
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8READ;
		request_type |= USB_सूची_IN;
		pipe = B2C2_USB_CTRL_PIPE_IN;
		अवरोध;
	हाल B2C2_USB_WRITE_V8_MEM:
		wIndex |= pbBuffer[0];
		request_type |= USB_सूची_OUT;
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8WRITE;
		pipe = B2C2_USB_CTRL_PIPE_OUT;
		अवरोध;
	हाल B2C2_USB_FLASH_BLOCK:
		request_type |= USB_सूची_OUT;
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8FLASH;
		pipe = B2C2_USB_CTRL_PIPE_OUT;
		अवरोध;
	शेष:
		deb_info("unsupported request for v8_mem_req %x.\n", req);
		वापस -EINVAL;
	पूर्ण
	deb_v8("v8mem: %02x %02x %04x %04x, len: %d\n", request_type, req,
			wAddress, wIndex, buflen);

	mutex_lock(&fc_usb->data_mutex);

	अगर ((request_type & USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT)
		स_नकल(fc_usb->data, pbBuffer, buflen);

	ret = usb_control_msg(fc_usb->udev, pipe,
			req,
			request_type,
			wAddress,
			wIndex,
			fc_usb->data,
			buflen,
			nWaitTime * HZ);
	अगर (ret != buflen)
		ret = -EIO;

	अगर (ret >= 0) अणु
		ret = 0;
		अगर ((request_type & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN)
			स_नकल(pbBuffer, fc_usb->data, buflen);
	पूर्ण

	mutex_unlock(&fc_usb->data_mutex);

	debug_dump(pbBuffer, ret, deb_v8);
	वापस ret;
पूर्ण

#घोषणा bytes_left_to_पढ़ो_on_page(paddr,buflen) \
	((V8_MEMORY_PAGE_SIZE - (paddr & V8_MEMORY_PAGE_MASK)) > buflen \
	 ? buflen : (V8_MEMORY_PAGE_SIZE - (paddr & V8_MEMORY_PAGE_MASK)))

अटल पूर्णांक flexcop_usb_memory_req(काष्ठा flexcop_usb *fc_usb,
		flexcop_usb_request_t req, flexcop_usb_mem_page_t page_start,
		u32 addr, पूर्णांक extended, u8 *buf, u32 len)
अणु
	पूर्णांक i,ret = 0;
	u16 wMax;
	u32 pagechunk = 0;

	चयन(req) अणु
	हाल B2C2_USB_READ_V8_MEM:
		wMax = USB_MEM_READ_MAX;
		अवरोध;
	हाल B2C2_USB_WRITE_V8_MEM:
		wMax = USB_MEM_WRITE_MAX;
		अवरोध;
	हाल B2C2_USB_FLASH_BLOCK:
		wMax = USB_FLASH_MAX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < len;) अणु
		pagechunk =
			wMax < bytes_left_to_पढ़ो_on_page(addr, len) ?
				wMax :
				bytes_left_to_पढ़ो_on_page(addr, len);
		deb_info("%x\n",
			(addr & V8_MEMORY_PAGE_MASK) |
				(V8_MEMORY_EXTENDED*extended));

		ret = flexcop_usb_v8_memory_req(fc_usb, req,
			page_start + (addr / V8_MEMORY_PAGE_SIZE),
			(addr & V8_MEMORY_PAGE_MASK) |
				(V8_MEMORY_EXTENDED*extended),
			&buf[i], pagechunk);

		अगर (ret < 0)
			वापस ret;
		addr += pagechunk;
		len -= pagechunk;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flexcop_usb_get_mac_addr(काष्ठा flexcop_device *fc, पूर्णांक extended)
अणु
	वापस flexcop_usb_memory_req(fc->bus_specअगरic, B2C2_USB_READ_V8_MEM,
		V8_MEMORY_PAGE_FLASH, 0x1f010, 1,
		fc->dvb_adapter.proposed_mac, 6);
पूर्ण

/* usb i2c stuff */
अटल पूर्णांक flexcop_usb_i2c_req(काष्ठा flexcop_i2c_adapter *i2c,
		flexcop_usb_request_t req, flexcop_usb_i2c_function_t func,
		u8 chipaddr, u8 addr, u8 *buf, u8 buflen)
अणु
	काष्ठा flexcop_usb *fc_usb = i2c->fc->bus_specअगरic;
	u16 wValue, wIndex;
	पूर्णांक nWaitTime, pipe, ret;
	u8 request_type = USB_TYPE_VENDOR;

	अगर (buflen > माप(fc_usb->data)) अणु
		err("Buffer size bigger than max URB control message\n");
		वापस -EIO;
	पूर्ण

	चयन (func) अणु
	हाल USB_FUNC_I2C_WRITE:
	हाल USB_FUNC_I2C_MULTIWRITE:
	हाल USB_FUNC_I2C_REPEATWRITE:
		/* DKT 020208 - add this to support special हाल of DiSEqC */
	हाल USB_FUNC_I2C_CHECKWRITE:
		pipe = B2C2_USB_CTRL_PIPE_OUT;
		nWaitTime = 2;
		request_type |= USB_सूची_OUT;
		अवरोध;
	हाल USB_FUNC_I2C_READ:
	हाल USB_FUNC_I2C_REPEATREAD:
		pipe = B2C2_USB_CTRL_PIPE_IN;
		nWaitTime = 2;
		request_type |= USB_सूची_IN;
		अवरोध;
	शेष:
		deb_info("unsupported function for i2c_req %x\n", func);
		वापस -EINVAL;
	पूर्ण
	wValue = (func << 8) | (i2c->port << 4);
	wIndex = (chipaddr << 8 ) | addr;

	deb_i2c("i2c %2d: %02x %02x %02x %02x %02x %02x\n",
			func, request_type, req,
			wValue & 0xff, wValue >> 8,
			wIndex & 0xff, wIndex >> 8);

	mutex_lock(&fc_usb->data_mutex);

	अगर ((request_type & USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT)
		स_नकल(fc_usb->data, buf, buflen);

	ret = usb_control_msg(fc_usb->udev, pipe,
			req,
			request_type,
			wValue,
			wIndex,
			fc_usb->data,
			buflen,
			nWaitTime * HZ);

	अगर (ret != buflen)
		ret = -EIO;

	अगर (ret >= 0) अणु
		ret = 0;
		अगर ((request_type & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN)
			स_नकल(buf, fc_usb->data, buflen);
	पूर्ण

	mutex_unlock(&fc_usb->data_mutex);

	वापस ret;
पूर्ण

/* actual bus specअगरic access functions,
   make sure prototype are/will be equal to pci */
अटल flexcop_ibi_value flexcop_usb_पढ़ो_ibi_reg(काष्ठा flexcop_device *fc,
	flexcop_ibi_रेजिस्टर reg)
अणु
	flexcop_ibi_value val;
	val.raw = 0;
	flexcop_usb_पढ़ोग_लिखो_dw(fc, reg, &val.raw, 1);
	वापस val;
पूर्ण

अटल पूर्णांक flexcop_usb_ग_लिखो_ibi_reg(काष्ठा flexcop_device *fc,
		flexcop_ibi_रेजिस्टर reg, flexcop_ibi_value val)
अणु
	वापस flexcop_usb_पढ़ोग_लिखो_dw(fc, reg, &val.raw, 0);
पूर्ण

अटल पूर्णांक flexcop_usb_i2c_request(काष्ठा flexcop_i2c_adapter *i2c,
		flexcop_access_op_t op, u8 chipaddr, u8 addr, u8 *buf, u16 len)
अणु
	अगर (op == FC_READ)
		वापस flexcop_usb_i2c_req(i2c, B2C2_USB_I2C_REQUEST,
				USB_FUNC_I2C_READ, chipaddr, addr, buf, len);
	अन्यथा
		वापस flexcop_usb_i2c_req(i2c, B2C2_USB_I2C_REQUEST,
				USB_FUNC_I2C_WRITE, chipaddr, addr, buf, len);
पूर्ण

अटल व्योम flexcop_usb_process_frame(काष्ठा flexcop_usb *fc_usb,
	u8 *buffer, पूर्णांक buffer_length)
अणु
	u8 *b;
	पूर्णांक l;

	deb_ts("tmp_buffer_length=%d, buffer_length=%d\n",
		fc_usb->पंचांगp_buffer_length, buffer_length);

	अगर (fc_usb->पंचांगp_buffer_length > 0) अणु
		स_नकल(fc_usb->पंचांगp_buffer+fc_usb->पंचांगp_buffer_length, buffer,
				buffer_length);
		fc_usb->पंचांगp_buffer_length += buffer_length;
		b = fc_usb->पंचांगp_buffer;
		l = fc_usb->पंचांगp_buffer_length;
	पूर्ण अन्यथा अणु
		b=buffer;
		l=buffer_length;
	पूर्ण

	जबतक (l >= 190) अणु
		अगर (*b == 0xff) अणु
			चयन (*(b+1) & 0x03) अणु
			हाल 0x01: /* media packet */
				अगर (*(b+2) == 0x47)
					flexcop_pass_dmx_packets(
							fc_usb->fc_dev, b+2, 1);
				अन्यथा
					deb_ts("not ts packet %*ph\n", 4, b+2);
				b += 190;
				l -= 190;
				अवरोध;
			शेष:
				deb_ts("wrong packet type\n");
				l = 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			deb_ts("wrong header\n");
			l = 0;
		पूर्ण
	पूर्ण

	अगर (l>0)
		स_नकल(fc_usb->पंचांगp_buffer, b, l);
	fc_usb->पंचांगp_buffer_length = l;
पूर्ण

अटल व्योम flexcop_usb_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा flexcop_usb *fc_usb = urb->context;
	पूर्णांक i;

	अगर (urb->actual_length > 0)
		deb_ts("urb completed, bufsize: %d actlen; %d\n",
			urb->transfer_buffer_length, urb->actual_length);

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		अगर (urb->iso_frame_desc[i].status < 0) अणु
			err("iso frame descriptor %d has an error: %d\n", i,
				urb->iso_frame_desc[i].status);
		पूर्ण अन्यथा
			अगर (urb->iso_frame_desc[i].actual_length > 0) अणु
				deb_ts("passed %d bytes to the demux\n",
					urb->iso_frame_desc[i].actual_length);

				flexcop_usb_process_frame(fc_usb,
					urb->transfer_buffer +
						urb->iso_frame_desc[i].offset,
					urb->iso_frame_desc[i].actual_length);
			पूर्ण
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण
	usb_submit_urb(urb,GFP_ATOMIC);
पूर्ण

अटल पूर्णांक flexcop_usb_stream_control(काष्ठा flexcop_device *fc, पूर्णांक onoff)
अणु
	/* submit/समाप्त iso packets */
	वापस 0;
पूर्ण

अटल व्योम flexcop_usb_transfer_निकास(काष्ठा flexcop_usb *fc_usb)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < B2C2_USB_NUM_ISO_URB; i++)
		अगर (fc_usb->iso_urb[i] != शून्य) अणु
			deb_ts("unlinking/killing urb no. %d\n",i);
			usb_समाप्त_urb(fc_usb->iso_urb[i]);
			usb_मुक्त_urb(fc_usb->iso_urb[i]);
		पूर्ण

	usb_मुक्त_coherent(fc_usb->udev, fc_usb->buffer_size,
			  fc_usb->iso_buffer, fc_usb->dma_addr);

पूर्ण

अटल पूर्णांक flexcop_usb_transfer_init(काष्ठा flexcop_usb *fc_usb)
अणु
	u16 frame_size = le16_to_cpu(
		fc_usb->uपूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc.wMaxPacketSize);
	पूर्णांक bufsize = B2C2_USB_NUM_ISO_URB * B2C2_USB_FRAMES_PER_ISO *
		frame_size, i, j, ret;
	पूर्णांक buffer_offset = 0;

	deb_ts("creating %d iso-urbs with %d frames each of %d bytes size = %d.\n",
	       B2C2_USB_NUM_ISO_URB,
			B2C2_USB_FRAMES_PER_ISO, frame_size, bufsize);

	fc_usb->iso_buffer = usb_alloc_coherent(fc_usb->udev,
			bufsize, GFP_KERNEL, &fc_usb->dma_addr);
	अगर (fc_usb->iso_buffer == शून्य)
		वापस -ENOMEM;

	स_रखो(fc_usb->iso_buffer, 0, bufsize);
	fc_usb->buffer_size = bufsize;

	/* creating iso urbs */
	क्रम (i = 0; i < B2C2_USB_NUM_ISO_URB; i++) अणु
		fc_usb->iso_urb[i] = usb_alloc_urb(B2C2_USB_FRAMES_PER_ISO,
			GFP_ATOMIC);
		अगर (fc_usb->iso_urb[i] == शून्य) अणु
			ret = -ENOMEM;
			जाओ urb_error;
		पूर्ण
	पूर्ण

	/* initialising and submitting iso urbs */
	क्रम (i = 0; i < B2C2_USB_NUM_ISO_URB; i++) अणु
		पूर्णांक frame_offset = 0;
		काष्ठा urb *urb = fc_usb->iso_urb[i];
		deb_ts("initializing and submitting urb no. %d (buf_offset: %d).\n",
		       i, buffer_offset);

		urb->dev = fc_usb->udev;
		urb->context = fc_usb;
		urb->complete = flexcop_usb_urb_complete;
		urb->pipe = B2C2_USB_DATA_PIPE;
		urb->transfer_flags = URB_ISO_ASAP;
		urb->पूर्णांकerval = 1;
		urb->number_of_packets = B2C2_USB_FRAMES_PER_ISO;
		urb->transfer_buffer_length = frame_size * B2C2_USB_FRAMES_PER_ISO;
		urb->transfer_buffer = fc_usb->iso_buffer + buffer_offset;

		buffer_offset += frame_size * B2C2_USB_FRAMES_PER_ISO;
		क्रम (j = 0; j < B2C2_USB_FRAMES_PER_ISO; j++) अणु
			deb_ts("urb no: %d, frame: %d, frame_offset: %d\n",
					i, j, frame_offset);
			urb->iso_frame_desc[j].offset = frame_offset;
			urb->iso_frame_desc[j].length = frame_size;
			frame_offset += frame_size;
		पूर्ण

		अगर ((ret = usb_submit_urb(fc_usb->iso_urb[i],GFP_ATOMIC))) अणु
			err("submitting urb %d failed with %d.", i, ret);
			जाओ urb_error;
		पूर्ण
		deb_ts("submitted urb no. %d.\n",i);
	पूर्ण

	/* SRAM */
	flexcop_sram_set_dest(fc_usb->fc_dev, FC_SRAM_DEST_MEDIA |
			FC_SRAM_DEST_NET | FC_SRAM_DEST_CAO | FC_SRAM_DEST_CAI,
			FC_SRAM_DEST_TARGET_WAN_USB);
	flexcop_wan_set_speed(fc_usb->fc_dev, FC_WAN_SPEED_8MBITS);
	flexcop_sram_ctrl(fc_usb->fc_dev, 1, 1, 1);
	वापस 0;

urb_error:
	flexcop_usb_transfer_निकास(fc_usb);
	वापस ret;
पूर्ण

अटल पूर्णांक flexcop_usb_init(काष्ठा flexcop_usb *fc_usb)
अणु
	/* use the alternate setting with the larges buffer */
	पूर्णांक ret = usb_set_पूर्णांकerface(fc_usb->udev, 0, 1);

	अगर (ret) अणु
		err("set interface failed.");
		वापस ret;
	पूर्ण

	अगर (fc_usb->uपूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;
	अगर (!usb_endpoपूर्णांक_is_isoc_in(&fc_usb->uपूर्णांकf->cur_altsetting->endpoपूर्णांक[1].desc))
		वापस -ENODEV;

	चयन (fc_usb->udev->speed) अणु
	हाल USB_SPEED_LOW:
		err("cannot handle USB speed because it is too slow.");
		वापस -ENODEV;
		अवरोध;
	हाल USB_SPEED_FULL:
		info("running at FULL speed.");
		अवरोध;
	हाल USB_SPEED_HIGH:
		info("running at HIGH speed.");
		अवरोध;
	हाल USB_SPEED_UNKNOWN:
	शेष:
		err("cannot handle USB speed because it is unknown.");
		वापस -ENODEV;
	पूर्ण
	usb_set_पूर्णांकfdata(fc_usb->uपूर्णांकf, fc_usb);
	वापस 0;
पूर्ण

अटल व्योम flexcop_usb_निकास(काष्ठा flexcop_usb *fc_usb)
अणु
	usb_set_पूर्णांकfdata(fc_usb->uपूर्णांकf, शून्य);
पूर्ण

अटल पूर्णांक flexcop_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा flexcop_usb *fc_usb = शून्य;
	काष्ठा flexcop_device *fc = शून्य;
	पूर्णांक ret;

	अगर ((fc = flexcop_device_kदो_स्मृति(माप(काष्ठा flexcop_usb))) == शून्य) अणु
		err("out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* general flexcop init */
	fc_usb = fc->bus_specअगरic;
	fc_usb->fc_dev = fc;
	mutex_init(&fc_usb->data_mutex);

	fc->पढ़ो_ibi_reg  = flexcop_usb_पढ़ो_ibi_reg;
	fc->ग_लिखो_ibi_reg = flexcop_usb_ग_लिखो_ibi_reg;
	fc->i2c_request = flexcop_usb_i2c_request;
	fc->get_mac_addr = flexcop_usb_get_mac_addr;

	fc->stream_control = flexcop_usb_stream_control;

	fc->pid_filtering = 1;
	fc->bus_type = FC_USB;

	fc->dev = &udev->dev;
	fc->owner = THIS_MODULE;

	/* bus specअगरic part */
	fc_usb->udev = udev;
	fc_usb->uपूर्णांकf = पूर्णांकf;
	अगर ((ret = flexcop_usb_init(fc_usb)) != 0)
		जाओ err_kमुक्त;

	/* init flexcop */
	अगर ((ret = flexcop_device_initialize(fc)) != 0)
		जाओ err_usb_निकास;

	/* xfer init */
	अगर ((ret = flexcop_usb_transfer_init(fc_usb)) != 0)
		जाओ err_fc_निकास;

	info("%s successfully initialized and connected.", DRIVER_NAME);
	वापस 0;

err_fc_निकास:
	flexcop_device_निकास(fc);
err_usb_निकास:
	flexcop_usb_निकास(fc_usb);
err_kमुक्त:
	flexcop_device_kमुक्त(fc);
	वापस ret;
पूर्ण

अटल व्योम flexcop_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा flexcop_usb *fc_usb = usb_get_पूर्णांकfdata(पूर्णांकf);
	flexcop_usb_transfer_निकास(fc_usb);
	flexcop_device_निकास(fc_usb->fc_dev);
	flexcop_usb_निकास(fc_usb);
	flexcop_device_kमुक्त(fc_usb->fc_dev);
	info("%s successfully deinitialized and disconnected.", DRIVER_NAME);
पूर्ण

अटल स्थिर काष्ठा usb_device_id flexcop_usb_table[] = अणु
	अणु USB_DEVICE(0x0af7, 0x0101) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (usb, flexcop_usb_table);

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver flexcop_usb_driver = अणु
	.name		= "b2c2_flexcop_usb",
	.probe		= flexcop_usb_probe,
	.disconnect = flexcop_usb_disconnect,
	.id_table	= flexcop_usb_table,
पूर्ण;

module_usb_driver(flexcop_usb_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_NAME);
MODULE_LICENSE("GPL");
