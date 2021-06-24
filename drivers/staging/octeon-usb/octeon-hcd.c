<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Cavium Networks
 *
 * Some parts of the code were originally released under BSD license:
 *
 * Copyright (c) 2003-2010 Cavium Networks (support@cavium.com). All rights
 * reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary क्रमm must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the करोcumentation and/or other materials provided
 *     with the distribution.
 *
 *   * Neither the name of Cavium Networks nor the names of
 *     its contributors may be used to enकरोrse or promote products
 *     derived from this software without specअगरic prior written
 *     permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its associated
 * regulations, and may be subject to export or import regulations in other
 * countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION
 * OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 */

#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश "octeon-hcd.h"

/**
 * क्रमागत cvmx_usb_speed - the possible USB device speeds
 *
 * @CVMX_USB_SPEED_HIGH: Device is operation at 480Mbps
 * @CVMX_USB_SPEED_FULL: Device is operation at 12Mbps
 * @CVMX_USB_SPEED_LOW:  Device is operation at 1.5Mbps
 */
क्रमागत cvmx_usb_speed अणु
	CVMX_USB_SPEED_HIGH = 0,
	CVMX_USB_SPEED_FULL = 1,
	CVMX_USB_SPEED_LOW = 2,
पूर्ण;

/**
 * क्रमागत cvmx_usb_transfer - the possible USB transfer types
 *
 * @CVMX_USB_TRANSFER_CONTROL:	   USB transfer type control क्रम hub and status
 *				   transfers
 * @CVMX_USB_TRANSFER_ISOCHRONOUS: USB transfer type isochronous क्रम low
 *				   priority periodic transfers
 * @CVMX_USB_TRANSFER_BULK:	   USB transfer type bulk क्रम large low priority
 *				   transfers
 * @CVMX_USB_TRANSFER_INTERRUPT:   USB transfer type पूर्णांकerrupt क्रम high priority
 *				   periodic transfers
 */
क्रमागत cvmx_usb_transfer अणु
	CVMX_USB_TRANSFER_CONTROL = 0,
	CVMX_USB_TRANSFER_ISOCHRONOUS = 1,
	CVMX_USB_TRANSFER_BULK = 2,
	CVMX_USB_TRANSFER_INTERRUPT = 3,
पूर्ण;

/**
 * क्रमागत cvmx_usb_direction - the transfer directions
 *
 * @CVMX_USB_सूचीECTION_OUT: Data is transferring from Octeon to the device/host
 * @CVMX_USB_सूचीECTION_IN:  Data is transferring from the device/host to Octeon
 */
क्रमागत cvmx_usb_direction अणु
	CVMX_USB_सूचीECTION_OUT,
	CVMX_USB_सूचीECTION_IN,
पूर्ण;

/**
 * क्रमागत cvmx_usb_status - possible callback function status codes
 *
 * @CVMX_USB_STATUS_OK:		  The transaction / operation finished without
 *				  any errors
 * @CVMX_USB_STATUS_SHORT:	  FIXME: This is currently not implemented
 * @CVMX_USB_STATUS_CANCEL:	  The transaction was canceled जबतक in flight
 *				  by a user call to cvmx_usb_cancel
 * @CVMX_USB_STATUS_ERROR:	  The transaction पातed with an unexpected
 *				  error status
 * @CVMX_USB_STATUS_STALL:	  The transaction received a USB STALL response
 *				  from the device
 * @CVMX_USB_STATUS_XACTERR:	  The transaction failed with an error from the
 *				  device even after a number of retries
 * @CVMX_USB_STATUS_DATATGLERR:	  The transaction failed with a data toggle
 *				  error even after a number of retries
 * @CVMX_USB_STATUS_BABBLEERR:	  The transaction failed with a babble error
 * @CVMX_USB_STATUS_FRAMEERR:	  The transaction failed with a frame error
 *				  even after a number of retries
 */
क्रमागत cvmx_usb_status अणु
	CVMX_USB_STATUS_OK,
	CVMX_USB_STATUS_SHORT,
	CVMX_USB_STATUS_CANCEL,
	CVMX_USB_STATUS_ERROR,
	CVMX_USB_STATUS_STALL,
	CVMX_USB_STATUS_XACTERR,
	CVMX_USB_STATUS_DATATGLERR,
	CVMX_USB_STATUS_BABBLEERR,
	CVMX_USB_STATUS_FRAMEERR,
पूर्ण;

/**
 * काष्ठा cvmx_usb_port_status - the USB port status inक्रमmation
 *
 * @port_enabled:	1 = Usb port is enabled, 0 = disabled
 * @port_over_current:	1 = Over current detected, 0 = Over current not
 *			detected. Octeon करोesn't support over current detection.
 * @port_घातered:	1 = Port घातer is being supplied to the device, 0 =
 *			घातer is off. Octeon करोesn't support turning port घातer
 *			off.
 * @port_speed:		Current port speed.
 * @connected:		1 = A device is connected to the port, 0 = No device is
 *			connected.
 * @connect_change:	1 = Device connected state changed since the last set
 *			status call.
 */
काष्ठा cvmx_usb_port_status अणु
	u32 reserved			: 25;
	u32 port_enabled		: 1;
	u32 port_over_current		: 1;
	u32 port_घातered		: 1;
	क्रमागत cvmx_usb_speed port_speed	: 2;
	u32 connected			: 1;
	u32 connect_change		: 1;
पूर्ण;

/**
 * काष्ठा cvmx_usb_iso_packet - descriptor क्रम Isochronous packets
 *
 * @offset:	This is the offset in bytes पूर्णांकo the मुख्य buffer where this data
 *		is stored.
 * @length:	This is the length in bytes of the data.
 * @status:	This is the status of this inभागidual packet transfer.
 */
काष्ठा cvmx_usb_iso_packet अणु
	पूर्णांक offset;
	पूर्णांक length;
	क्रमागत cvmx_usb_status status;
पूर्ण;

/**
 * क्रमागत cvmx_usb_initialize_flags - flags used by the initialization function
 *
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_XI:    The USB port uses a 12MHz crystal
 *					      as घड़ी source at USB_XO and
 *					      USB_XI.
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND:   The USB port uses 12/24/48MHz 2.5V
 *					      board घड़ी source at USB_XO.
 *					      USB_XI should be tied to GND.
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_MHZ_MASK: Mask क्रम घड़ी speed field
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ:    Speed of reference घड़ी or
 *					      crystal
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ:    Speed of reference घड़ी
 * @CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ:    Speed of reference घड़ी
 * @CVMX_USB_INITIALIZE_FLAGS_NO_DMA:	      Disable DMA and used polled IO क्रम
 *					      data transfer use क्रम the USB
 */
क्रमागत cvmx_usb_initialize_flags अणु
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_XI		= 1 << 0,
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND		= 1 << 1,
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_MHZ_MASK	= 3 << 3,
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ		= 1 << 3,
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ		= 2 << 3,
	CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ		= 3 << 3,
	/* Bits 3-4 used to encode the घड़ी frequency */
	CVMX_USB_INITIALIZE_FLAGS_NO_DMA		= 1 << 5,
पूर्ण;

/**
 * क्रमागत cvmx_usb_pipe_flags - पूर्णांकernal flags क्रम a pipe.
 *
 * @CVMX_USB_PIPE_FLAGS_SCHEDULED: Used पूर्णांकernally to determine अगर a pipe is
 *				   actively using hardware.
 * @CVMX_USB_PIPE_FLAGS_NEED_PING: Used पूर्णांकernally to determine अगर a high speed
 *				   pipe is in the ping state.
 */
क्रमागत cvmx_usb_pipe_flags अणु
	CVMX_USB_PIPE_FLAGS_SCHEDULED	= 1 << 17,
	CVMX_USB_PIPE_FLAGS_NEED_PING	= 1 << 18,
पूर्ण;

/* Maximum number of बार to retry failed transactions */
#घोषणा MAX_RETRIES		3

/* Maximum number of hardware channels supported by the USB block */
#घोषणा MAX_CHANNELS		8

/*
 * The low level hardware can transfer a maximum of this number of bytes in each
 * transfer. The field is 19 bits wide
 */
#घोषणा MAX_TRANSFER_BYTES	((1 << 19) - 1)

/*
 * The low level hardware can transfer a maximum of this number of packets in
 * each transfer. The field is 10 bits wide
 */
#घोषणा MAX_TRANSFER_PACKETS	((1 << 10) - 1)

/**
 * Logical transactions may take numerous low level
 * transactions, especially when splits are concerned. This
 * क्रमागत represents all of the possible stages a transaction can
 * be in. Note that split completes are always even. This is so
 * the NAK handler can backup to the previous low level
 * transaction with a simple clearing of bit 0.
 */
क्रमागत cvmx_usb_stage अणु
	CVMX_USB_STAGE_NON_CONTROL,
	CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE,
	CVMX_USB_STAGE_SETUP,
	CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE,
	CVMX_USB_STAGE_DATA,
	CVMX_USB_STAGE_DATA_SPLIT_COMPLETE,
	CVMX_USB_STAGE_STATUS,
	CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE,
पूर्ण;

/**
 * काष्ठा cvmx_usb_transaction - describes each pending USB transaction
 *				 regardless of type. These are linked together
 *				 to क्रमm a list of pending requests क्रम a pipe.
 *
 * @node:		List node क्रम transactions in the pipe.
 * @type:		Type of transaction, duplicated of the pipe.
 * @flags:		State flags क्रम this transaction.
 * @buffer:		User's physical buffer address to पढ़ो/ग_लिखो.
 * @buffer_length:	Size of the user's buffer in bytes.
 * @control_header:	For control transactions, physical address of the 8
 *			byte standard header.
 * @iso_start_frame:	For ISO transactions, the starting frame number.
 * @iso_number_packets:	For ISO transactions, the number of packets in the
 *			request.
 * @iso_packets:	For ISO transactions, the sub packets in the request.
 * @actual_bytes:	Actual bytes transfer क्रम this transaction.
 * @stage:		For control transactions, the current stage.
 * @urb:		URB.
 */
काष्ठा cvmx_usb_transaction अणु
	काष्ठा list_head node;
	क्रमागत cvmx_usb_transfer type;
	u64 buffer;
	पूर्णांक buffer_length;
	u64 control_header;
	पूर्णांक iso_start_frame;
	पूर्णांक iso_number_packets;
	काष्ठा cvmx_usb_iso_packet *iso_packets;
	पूर्णांक xfersize;
	पूर्णांक pktcnt;
	पूर्णांक retries;
	पूर्णांक actual_bytes;
	क्रमागत cvmx_usb_stage stage;
	काष्ठा urb *urb;
पूर्ण;

/**
 * काष्ठा cvmx_usb_pipe - a pipe represents a भव connection between Octeon
 *			  and some USB device. It contains a list of pending
 *			  request to the device.
 *
 * @node:		List node क्रम pipe list
 * @next:		Pipe after this one in the list
 * @transactions:	List of pending transactions
 * @पूर्णांकerval:		For periodic pipes, the पूर्णांकerval between packets in
 *			frames
 * @next_tx_frame:	The next frame this pipe is allowed to transmit on
 * @flags:		State flags क्रम this pipe
 * @device_speed:	Speed of device connected to this pipe
 * @transfer_type:	Type of transaction supported by this pipe
 * @transfer_dir:	IN or OUT. Ignored क्रम Control
 * @multi_count:	Max packet in a row क्रम the device
 * @max_packet:		The device's maximum packet size in bytes
 * @device_addr:	USB device address at other end of pipe
 * @endpoपूर्णांक_num:	USB endpoपूर्णांक number at other end of pipe
 * @hub_device_addr:	Hub address this device is connected to
 * @hub_port:		Hub port this device is connected to
 * @pid_toggle:		This toggles between 0/1 on every packet send to track
 *			the data pid needed
 * @channel:		Hardware DMA channel क्रम this pipe
 * @split_sc_frame:	The low order bits of the frame number the split
 *			complete should be sent on
 */
काष्ठा cvmx_usb_pipe अणु
	काष्ठा list_head node;
	काष्ठा list_head transactions;
	u64 पूर्णांकerval;
	u64 next_tx_frame;
	क्रमागत cvmx_usb_pipe_flags flags;
	क्रमागत cvmx_usb_speed device_speed;
	क्रमागत cvmx_usb_transfer transfer_type;
	क्रमागत cvmx_usb_direction transfer_dir;
	पूर्णांक multi_count;
	u16 max_packet;
	u8 device_addr;
	u8 endpoपूर्णांक_num;
	u8 hub_device_addr;
	u8 hub_port;
	u8 pid_toggle;
	u8 channel;
	s8 split_sc_frame;
पूर्ण;

काष्ठा cvmx_usb_tx_fअगरo अणु
	काष्ठा अणु
		पूर्णांक channel;
		पूर्णांक size;
		u64 address;
	पूर्ण entry[MAX_CHANNELS + 1];
	पूर्णांक head;
	पूर्णांक tail;
पूर्ण;

/**
 * काष्ठा octeon_hcd - the state of the USB block
 *
 * lock:		   Serialization lock.
 * init_flags:		   Flags passed to initialize.
 * index:		   Which USB block this is क्रम.
 * idle_hardware_channels: Bit set क्रम every idle hardware channel.
 * usbcx_hprt:		   Stored port status so we करोn't need to पढ़ो a CSR to
 *			   determine splits.
 * pipe_क्रम_channel:	   Map channels to pipes.
 * pipe:		   Storage क्रम pipes.
 * indent:		   Used by debug output to indent functions.
 * port_status:		   Last port status used क्रम change notअगरication.
 * idle_pipes:		   List of खोलो pipes that have no transactions.
 * active_pipes:	   Active pipes indexed by transfer type.
 * frame_number:	   Increments every SOF पूर्णांकerrupt क्रम समय keeping.
 * active_split:	   Poपूर्णांकs to the current active split, or शून्य.
 */
काष्ठा octeon_hcd अणु
	spinlock_t lock; /* serialization lock */
	पूर्णांक init_flags;
	पूर्णांक index;
	पूर्णांक idle_hardware_channels;
	जोड़ cvmx_usbcx_hprt usbcx_hprt;
	काष्ठा cvmx_usb_pipe *pipe_क्रम_channel[MAX_CHANNELS];
	पूर्णांक indent;
	काष्ठा cvmx_usb_port_status port_status;
	काष्ठा list_head idle_pipes;
	काष्ठा list_head active_pipes[4];
	u64 frame_number;
	काष्ठा cvmx_usb_transaction *active_split;
	काष्ठा cvmx_usb_tx_fअगरo periodic;
	काष्ठा cvmx_usb_tx_fअगरo nonperiodic;
पूर्ण;

/*
 * This macro logically sets a single field in a CSR. It करोes the sequence
 * पढ़ो, modअगरy, and ग_लिखो
 */
#घोषणा USB_SET_FIELD32(address, _जोड़, field, value)		\
	करो अणु							\
		जोड़ _जोड़ c;					\
								\
		c.u32 = cvmx_usb_पढ़ो_csr32(usb, address);	\
		c.s.field = value;				\
		cvmx_usb_ग_लिखो_csr32(usb, address, c.u32);	\
	पूर्ण जबतक (0)

/* Returns the IO address to push/pop stuff data from the FIFOs */
#घोषणा USB_FIFO_ADDRESS(channel, usb_index) \
	(CVMX_USBCX_GOTGCTL(usb_index) + ((channel) + 1) * 0x1000)

/**
 * काष्ठा octeon_temp_buffer - a bounce buffer क्रम USB transfers
 * @orig_buffer: the original buffer passed by the USB stack
 * @data:	 the newly allocated temporary buffer (excluding meta-data)
 *
 * Both the DMA engine and FIFO mode will always transfer full 32-bit words. If
 * the buffer is too लघु, we need to allocate a temporary one, and this काष्ठा
 * represents it.
 */
काष्ठा octeon_temp_buffer अणु
	व्योम *orig_buffer;
	u8 data[];
पूर्ण;

अटल अंतरभूत काष्ठा usb_hcd *octeon_to_hcd(काष्ठा octeon_hcd *p)
अणु
	वापस container_of((व्योम *)p, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/**
 * octeon_alloc_temp_buffer - allocate a temporary buffer क्रम USB transfer
 *                            (अगर needed)
 * @urb:	URB.
 * @mem_flags:	Memory allocation flags.
 *
 * This function allocates a temporary bounce buffer whenever it's needed
 * due to HW limitations.
 */
अटल पूर्णांक octeon_alloc_temp_buffer(काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा octeon_temp_buffer *temp;

	अगर (urb->num_sgs || urb->sg ||
	    (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP) ||
	    !(urb->transfer_buffer_length % माप(u32)))
		वापस 0;

	temp = kदो_स्मृति(ALIGN(urb->transfer_buffer_length, माप(u32)) +
		       माप(*temp), mem_flags);
	अगर (!temp)
		वापस -ENOMEM;

	temp->orig_buffer = urb->transfer_buffer;
	अगर (usb_urb_dir_out(urb))
		स_नकल(temp->data, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = temp->data;
	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	वापस 0;
पूर्ण

/**
 * octeon_मुक्त_temp_buffer - मुक्त a temporary buffer used by USB transfers.
 * @urb: URB.
 *
 * Frees a buffer allocated by octeon_alloc_temp_buffer().
 */
अटल व्योम octeon_मुक्त_temp_buffer(काष्ठा urb *urb)
अणु
	काष्ठा octeon_temp_buffer *temp;
	माप_प्रकार length;

	अगर (!(urb->transfer_flags & URB_ALIGNED_TEMP_BUFFER))
		वापस;

	temp = container_of(urb->transfer_buffer, काष्ठा octeon_temp_buffer,
			    data);
	अगर (usb_urb_dir_in(urb)) अणु
		अगर (usb_pipeisoc(urb->pipe))
			length = urb->transfer_buffer_length;
		अन्यथा
			length = urb->actual_length;

		स_नकल(temp->orig_buffer, urb->transfer_buffer, length);
	पूर्ण
	urb->transfer_buffer = temp->orig_buffer;
	urb->transfer_flags &= ~URB_ALIGNED_TEMP_BUFFER;
	kमुक्त(temp);
पूर्ण

/**
 * octeon_map_urb_क्रम_dma - Octeon-specअगरic map_urb_क्रम_dma().
 * @hcd:	USB HCD काष्ठाure.
 * @urb:	URB.
 * @mem_flags:	Memory allocation flags.
 */
अटल पूर्णांक octeon_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				  gfp_t mem_flags)
अणु
	पूर्णांक ret;

	ret = octeon_alloc_temp_buffer(urb, mem_flags);
	अगर (ret)
		वापस ret;

	ret = usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
	अगर (ret)
		octeon_मुक्त_temp_buffer(urb);

	वापस ret;
पूर्ण

/**
 * octeon_unmap_urb_क्रम_dma - Octeon-specअगरic unmap_urb_क्रम_dma()
 * @hcd:	USB HCD काष्ठाure.
 * @urb:	URB.
 */
अटल व्योम octeon_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
	octeon_मुक्त_temp_buffer(urb);
पूर्ण

/**
 * Read a USB 32bit CSR. It perक्रमms the necessary address swizzle
 * क्रम 32bit CSRs and logs the value in a पढ़ोable क्रमmat अगर
 * debugging is on.
 *
 * @usb:     USB block this access is क्रम
 * @address: 64bit address to पढ़ो
 *
 * Returns: Result of the पढ़ो
 */
अटल अंतरभूत u32 cvmx_usb_पढ़ो_csr32(काष्ठा octeon_hcd *usb, u64 address)
अणु
	वापस cvmx_पढ़ो64_uपूर्णांक32(address ^ 4);
पूर्ण

/**
 * Write a USB 32bit CSR. It perक्रमms the necessary address
 * swizzle क्रम 32bit CSRs and logs the value in a पढ़ोable क्रमmat
 * अगर debugging is on.
 *
 * @usb:     USB block this access is क्रम
 * @address: 64bit address to ग_लिखो
 * @value:   Value to ग_लिखो
 */
अटल अंतरभूत व्योम cvmx_usb_ग_लिखो_csr32(काष्ठा octeon_hcd *usb,
					u64 address, u32 value)
अणु
	cvmx_ग_लिखो64_uपूर्णांक32(address ^ 4, value);
	cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
पूर्ण

/**
 * Return non zero अगर this pipe connects to a non HIGH speed
 * device through a high speed hub.
 *
 * @usb:    USB block this access is क्रम
 * @pipe:   Pipe to check
 *
 * Returns: Non zero अगर we need to करो split transactions
 */
अटल अंतरभूत पूर्णांक cvmx_usb_pipe_needs_split(काष्ठा octeon_hcd *usb,
					    काष्ठा cvmx_usb_pipe *pipe)
अणु
	वापस pipe->device_speed != CVMX_USB_SPEED_HIGH &&
	       usb->usbcx_hprt.s.prtspd == CVMX_USB_SPEED_HIGH;
पूर्ण

/**
 * Trivial utility function to वापस the correct PID क्रम a pipe
 *
 * @pipe:   pipe to check
 *
 * Returns: PID क्रम pipe
 */
अटल अंतरभूत पूर्णांक cvmx_usb_get_data_pid(काष्ठा cvmx_usb_pipe *pipe)
अणु
	अगर (pipe->pid_toggle)
		वापस 2; /* Data1 */
	वापस 0; /* Data0 */
पूर्ण

/* Loops through रेजिस्टर until txfflsh or rxfflsh become zero.*/
अटल पूर्णांक cvmx_रुको_tx_rx(काष्ठा octeon_hcd *usb, पूर्णांक fflsh_type)
अणु
	पूर्णांक result;
	u64 address = CVMX_USBCX_GRSTCTL(usb->index);
	u64 करोne = cvmx_get_cycle() + 100 *
		   (u64)octeon_get_घड़ी_rate / 1000000;
	जोड़ cvmx_usbcx_grstctl c;

	जबतक (1) अणु
		c.u32 = cvmx_usb_पढ़ो_csr32(usb, address);
		अगर (fflsh_type == 0 && c.s.txfflsh == 0) अणु
			result = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (fflsh_type == 1 && c.s.rxfflsh == 0) अणु
			result = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (cvmx_get_cycle() > करोne) अणु
			result = -1;
			अवरोध;
		पूर्ण

		__delay(100);
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम cvmx_fअगरo_setup(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbcx_ghwcfg3 usbcx_ghwcfg3;
	जोड़ cvmx_usbcx_gnptxfsiz npsiz;
	जोड़ cvmx_usbcx_hptxfsiz psiz;

	usbcx_ghwcfg3.u32 = cvmx_usb_पढ़ो_csr32(usb,
						CVMX_USBCX_GHWCFG3(usb->index));

	/*
	 * Program the USBC_GRXFSIZ रेजिस्टर to select the size of the receive
	 * FIFO (25%).
	 */
	USB_SET_FIELD32(CVMX_USBCX_GRXFSIZ(usb->index), cvmx_usbcx_grxfsiz,
			rxfdep, usbcx_ghwcfg3.s.dfअगरodepth / 4);

	/*
	 * Program the USBC_GNPTXFSIZ रेजिस्टर to select the size and the start
	 * address of the non-periodic transmit FIFO क्रम nonperiodic
	 * transactions (50%).
	 */
	npsiz.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index));
	npsiz.s.nptxfdep = usbcx_ghwcfg3.s.dfअगरodepth / 2;
	npsiz.s.nptxfstaddr = usbcx_ghwcfg3.s.dfअगरodepth / 4;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index), npsiz.u32);

	/*
	 * Program the USBC_HPTXFSIZ रेजिस्टर to select the size and start
	 * address of the periodic transmit FIFO क्रम periodic transactions
	 * (25%).
	 */
	psiz.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HPTXFSIZ(usb->index));
	psiz.s.ptxfsize = usbcx_ghwcfg3.s.dfअगरodepth / 4;
	psiz.s.ptxfstaddr = 3 * usbcx_ghwcfg3.s.dfअगरodepth / 4;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HPTXFSIZ(usb->index), psiz.u32);

	/* Flush all FIFOs */
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, txfnum, 0x10);
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, txfflsh, 1);
	cvmx_रुको_tx_rx(usb, 0);
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, rxfflsh, 1);
	cvmx_रुको_tx_rx(usb, 1);
पूर्ण

/**
 * Shutकरोwn a USB port after a call to cvmx_usb_initialize().
 * The port should be disabled with all pipes बंदd when this
 * function is called.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_shutकरोwn(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbnx_clk_ctl usbn_clk_ctl;

	/* Make sure all pipes are बंदd */
	अगर (!list_empty(&usb->idle_pipes) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_ISOCHRONOUS]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_INTERRUPT]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_CONTROL]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_BULK]))
		वापस -EBUSY;

	/* Disable the घड़ीs and put them in घातer on reset */
	usbn_clk_ctl.u64 = cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index));
	usbn_clk_ctl.s.enable = 1;
	usbn_clk_ctl.s.por = 1;
	usbn_clk_ctl.s.hclk_rst = 1;
	usbn_clk_ctl.s.prst = 0;
	usbn_clk_ctl.s.hrst = 0;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	वापस 0;
पूर्ण

/**
 * Initialize a USB port क्रम use. This must be called beक्रमe any
 * other access to the Octeon USB port is made. The port starts
 * off in the disabled state.
 *
 * @dev:	 Poपूर्णांकer to काष्ठा device क्रम logging purposes.
 * @usb:	 Poपूर्णांकer to काष्ठा octeon_hcd.
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_initialize(काष्ठा device *dev,
			       काष्ठा octeon_hcd *usb)
अणु
	पूर्णांक channel;
	पूर्णांक भागisor;
	पूर्णांक retries = 0;
	जोड़ cvmx_usbcx_hcfg usbcx_hcfg;
	जोड़ cvmx_usbnx_clk_ctl usbn_clk_ctl;
	जोड़ cvmx_usbcx_gपूर्णांकsts usbc_gपूर्णांकsts;
	जोड़ cvmx_usbcx_gahbcfg usbcx_gahbcfg;
	जोड़ cvmx_usbcx_gपूर्णांकmsk usbcx_gपूर्णांकmsk;
	जोड़ cvmx_usbcx_gusbcfg usbcx_gusbcfg;
	जोड़ cvmx_usbnx_usbp_ctl_status usbn_usbp_ctl_status;

retry:
	/*
	 * Power On Reset and PHY Initialization
	 *
	 * 1. Wait क्रम DCOK to निश्चित (nothing to करो)
	 *
	 * 2a. Write USBN0/1_CLK_CTL[POR] = 1 and
	 *     USBN0/1_CLK_CTL[HRST,PRST,HCLK_RST] = 0
	 */
	usbn_clk_ctl.u64 = cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index));
	usbn_clk_ctl.s.por = 1;
	usbn_clk_ctl.s.hrst = 0;
	usbn_clk_ctl.s.prst = 0;
	usbn_clk_ctl.s.hclk_rst = 0;
	usbn_clk_ctl.s.enable = 0;
	/*
	 * 2b. Select the USB reference घड़ी/crystal parameters by writing
	 *     appropriate values to USBN0/1_CLK_CTL[P_C_SEL, P_RTYPE, P_COM_ON]
	 */
	अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND) अणु
		/*
		 * The USB port uses 12/24/48MHz 2.5V board घड़ी
		 * source at USB_XO. USB_XI should be tied to GND.
		 * Most Octeon evaluation boards require this setting
		 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX) ||
		    OCTEON_IS_MODEL(OCTEON_CN56XX) ||
		    OCTEON_IS_MODEL(OCTEON_CN50XX))
			/* From CN56XX,CN50XX,CN31XX,CN30XX manuals */
			usbn_clk_ctl.s.p_rtype = 2; /* p_rclk=1 & p_xenbn=0 */
		अन्यथा
			/* From CN52XX manual */
			usbn_clk_ctl.s.p_rtype = 1;

		चयन (usb->init_flags &
			CVMX_USB_INITIALIZE_FLAGS_CLOCK_MHZ_MASK) अणु
		हाल CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ:
			usbn_clk_ctl.s.p_c_sel = 0;
			अवरोध;
		हाल CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ:
			usbn_clk_ctl.s.p_c_sel = 1;
			अवरोध;
		हाल CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ:
			usbn_clk_ctl.s.p_c_sel = 2;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The USB port uses a 12MHz crystal as घड़ी source
		 * at USB_XO and USB_XI
		 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX))
			/* From CN31XX,CN30XX manual */
			usbn_clk_ctl.s.p_rtype = 3; /* p_rclk=1 & p_xenbn=1 */
		अन्यथा
			/* From CN56XX,CN52XX,CN50XX manuals. */
			usbn_clk_ctl.s.p_rtype = 0;

		usbn_clk_ctl.s.p_c_sel = 0;
	पूर्ण
	/*
	 * 2c. Select the HCLK via writing USBN0/1_CLK_CTL[DIVIDE, DIVIDE2] and
	 *     setting USBN0/1_CLK_CTL[ENABLE] = 1. Divide the core घड़ी करोwn
	 *     such that USB is as बंद as possible to 125Mhz
	 */
	भागisor = DIV_ROUND_UP(octeon_get_घड़ी_rate(), 125000000);
	/* Lower than 4 करोesn't seem to work properly */
	अगर (भागisor < 4)
		भागisor = 4;
	usbn_clk_ctl.s.भागide = भागisor;
	usbn_clk_ctl.s.भागide2 = 0;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);

	/* 2d. Write USBN0/1_CLK_CTL[HCLK_RST] = 1 */
	usbn_clk_ctl.s.hclk_rst = 1;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	/* 2e.  Wait 64 core-घड़ी cycles क्रम HCLK to stabilize */
	__delay(64);
	/*
	 * 3. Program the घातer-on reset field in the USBN घड़ी-control
	 *    रेजिस्टर:
	 *    USBN_CLK_CTL[POR] = 0
	 */
	usbn_clk_ctl.s.por = 0;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	/* 4. Wait 1 ms क्रम PHY घड़ी to start */
	mdelay(1);
	/*
	 * 5. Program the Reset input from स्वतःmatic test equipment field in the
	 *    USBP control and status रेजिस्टर:
	 *    USBN_USBP_CTL_STATUS[ATE_RESET] = 1
	 */
	usbn_usbp_ctl_status.u64 =
		cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_USBP_CTL_STATUS(usb->index));
	usbn_usbp_ctl_status.s.ate_reset = 1;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_USBP_CTL_STATUS(usb->index),
			    usbn_usbp_ctl_status.u64);
	/* 6. Wait 10 cycles */
	__delay(10);
	/*
	 * 7. Clear ATE_RESET field in the USBN घड़ी-control रेजिस्टर:
	 *    USBN_USBP_CTL_STATUS[ATE_RESET] = 0
	 */
	usbn_usbp_ctl_status.s.ate_reset = 0;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_USBP_CTL_STATUS(usb->index),
			    usbn_usbp_ctl_status.u64);
	/*
	 * 8. Program the PHY reset field in the USBN घड़ी-control रेजिस्टर:
	 *    USBN_CLK_CTL[PRST] = 1
	 */
	usbn_clk_ctl.s.prst = 1;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	/*
	 * 9. Program the USBP control and status रेजिस्टर to select host or
	 *    device mode. USBN_USBP_CTL_STATUS[HST_MODE] = 0 क्रम host, = 1 क्रम
	 *    device
	 */
	usbn_usbp_ctl_status.s.hst_mode = 0;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_USBP_CTL_STATUS(usb->index),
			    usbn_usbp_ctl_status.u64);
	/* 10. Wait 1 us */
	udelay(1);
	/*
	 * 11. Program the hreset_n field in the USBN घड़ी-control रेजिस्टर:
	 *     USBN_CLK_CTL[HRST] = 1
	 */
	usbn_clk_ctl.s.hrst = 1;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	/* 12. Proceed to USB core initialization */
	usbn_clk_ctl.s.enable = 1;
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	udelay(1);

	/*
	 * USB Core Initialization
	 *
	 * 1. Read USBC_GHWCFG1, USBC_GHWCFG2, USBC_GHWCFG3, USBC_GHWCFG4 to
	 *    determine USB core configuration parameters.
	 *
	 *    Nothing needed
	 *
	 * 2. Program the following fields in the global AHB configuration
	 *    रेजिस्टर (USBC_GAHBCFG)
	 *    DMA mode, USBC_GAHBCFG[DMAEn]: 1 = DMA mode, 0 = slave mode
	 *    Burst length, USBC_GAHBCFG[HBSTLEN] = 0
	 *    Nonperiodic TxFIFO empty level (slave mode only),
	 *    USBC_GAHBCFG[NPTXFEMPLVL]
	 *    Periodic TxFIFO empty level (slave mode only),
	 *    USBC_GAHBCFG[PTXFEMPLVL]
	 *    Global पूर्णांकerrupt mask, USBC_GAHBCFG[GLBLINTRMSK] = 1
	 */
	usbcx_gahbcfg.u32 = 0;
	usbcx_gahbcfg.s.dmaen = !(usb->init_flags &
				  CVMX_USB_INITIALIZE_FLAGS_NO_DMA);
	usbcx_gahbcfg.s.hbstlen = 0;
	usbcx_gahbcfg.s.nptxfemplvl = 1;
	usbcx_gahbcfg.s.ptxfemplvl = 1;
	usbcx_gahbcfg.s.glblपूर्णांकrmsk = 1;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GAHBCFG(usb->index),
			     usbcx_gahbcfg.u32);

	/*
	 * 3. Program the following fields in USBC_GUSBCFG रेजिस्टर.
	 *    HS/FS समयout calibration, USBC_GUSBCFG[TOUTCAL] = 0
	 *    ULPI DDR select, USBC_GUSBCFG[DDRSEL] = 0
	 *    USB turnaround समय, USBC_GUSBCFG[USBTRDTIM] = 0x5
	 *    PHY low-घातer घड़ी select, USBC_GUSBCFG[PHYLPWRCLKSEL] = 0
	 */
	usbcx_gusbcfg.u32 = cvmx_usb_पढ़ो_csr32(usb,
						CVMX_USBCX_GUSBCFG(usb->index));
	usbcx_gusbcfg.s.toutcal = 0;
	usbcx_gusbcfg.s.ddrsel = 0;
	usbcx_gusbcfg.s.usbtrdtim = 0x5;
	usbcx_gusbcfg.s.phylpwrclksel = 0;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GUSBCFG(usb->index),
			     usbcx_gusbcfg.u32);

	/*
	 * 4. The software must unmask the following bits in the USBC_GINTMSK
	 *    रेजिस्टर.
	 *    OTG पूर्णांकerrupt mask, USBC_GINTMSK[OTGINTMSK] = 1
	 *    Mode mismatch पूर्णांकerrupt mask, USBC_GINTMSK[MODEMISMSK] = 1
	 */
	usbcx_gपूर्णांकmsk.u32 = cvmx_usb_पढ़ो_csr32(usb,
						CVMX_USBCX_GINTMSK(usb->index));
	usbcx_gपूर्णांकmsk.s.otgपूर्णांकmsk = 1;
	usbcx_gपूर्णांकmsk.s.modemismsk = 1;
	usbcx_gपूर्णांकmsk.s.hchपूर्णांकmsk = 1;
	usbcx_gपूर्णांकmsk.s.sofmsk = 0;
	/* We need RX FIFO पूर्णांकerrupts अगर we करोn't have DMA */
	अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
		usbcx_gपूर्णांकmsk.s.rxflvlmsk = 1;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GINTMSK(usb->index),
			     usbcx_gपूर्णांकmsk.u32);

	/*
	 * Disable all channel पूर्णांकerrupts. We'll enable them per channel later.
	 */
	क्रम (channel = 0; channel < 8; channel++)
		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCINTMSKX(channel, usb->index),
				     0);

	/*
	 * Host Port Initialization
	 *
	 * 1. Program the host-port पूर्णांकerrupt-mask field to unmask,
	 *    USBC_GINTMSK[PRTINT] = 1
	 */
	USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gपूर्णांकmsk, prtपूर्णांकmsk, 1);
	USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gपूर्णांकmsk, disconnपूर्णांकmsk, 1);

	/*
	 * 2. Program the USBC_HCFG रेजिस्टर to select full-speed host
	 *    or high-speed host.
	 */
	usbcx_hcfg.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HCFG(usb->index));
	usbcx_hcfg.s.fslssupp = 0;
	usbcx_hcfg.s.fslspclksel = 0;
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HCFG(usb->index), usbcx_hcfg.u32);

	cvmx_fअगरo_setup(usb);

	/*
	 * If the controller is getting port events right after the reset, it
	 * means the initialization failed. Try resetting the controller again
	 * in such हाल. This is seen to happen after cold boot on DSR-1000N.
	 */
	usbc_gपूर्णांकsts.u32 = cvmx_usb_पढ़ो_csr32(usb,
					       CVMX_USBCX_GINTSTS(usb->index));
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GINTSTS(usb->index),
			     usbc_gपूर्णांकsts.u32);
	dev_dbg(dev, "gintsts after reset: 0x%x\n", (पूर्णांक)usbc_gपूर्णांकsts.u32);
	अगर (!usbc_gपूर्णांकsts.s.disconnपूर्णांक && !usbc_gपूर्णांकsts.s.prtपूर्णांक)
		वापस 0;
	अगर (retries++ >= 5)
		वापस -EAGAIN;
	dev_info(dev, "controller reset failed (gintsts=0x%x) - retrying\n",
		 (पूर्णांक)usbc_gपूर्णांकsts.u32);
	msleep(50);
	cvmx_usb_shutकरोwn(usb);
	msleep(50);
	जाओ retry;
पूर्ण

/**
 * Reset a USB port. After this call succeeds, the USB port is
 * online and servicing requests.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 */
अटल व्योम cvmx_usb_reset_port(काष्ठा octeon_hcd *usb)
अणु
	usb->usbcx_hprt.u32 = cvmx_usb_पढ़ो_csr32(usb,
						  CVMX_USBCX_HPRT(usb->index));

	/* Program the port reset bit to start the reset process */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtrst, 1);

	/*
	 * Wait at least 50ms (high speed), or 10ms (full speed) क्रम the reset
	 * process to complete.
	 */
	mdelay(50);

	/* Program the port reset bit to 0, USBC_HPRT[PRTRST] = 0 */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtrst, 0);

	/*
	 * Read the port speed field to get the क्रमागतerated speed,
	 * USBC_HPRT[PRTSPD].
	 */
	usb->usbcx_hprt.u32 = cvmx_usb_पढ़ो_csr32(usb,
						  CVMX_USBCX_HPRT(usb->index));
पूर्ण

/**
 * Disable a USB port. After this call the USB port will not
 * generate data transfers and will not generate events.
 * Transactions in process will fail and call their
 * associated callbacks.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_disable(काष्ठा octeon_hcd *usb)
अणु
	/* Disable the port */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtena, 1);
	वापस 0;
पूर्ण

/**
 * Get the current state of the USB port. Use this call to
 * determine अगर the usb port has anything connected, is enabled,
 * or has some sort of error condition. The वापस value of this
 * call has "changed" bits to संकेत of the value of some fields
 * have changed between calls.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 *
 * Returns: Port status inक्रमmation
 */
अटल काष्ठा cvmx_usb_port_status cvmx_usb_get_status(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbcx_hprt usbc_hprt;
	काष्ठा cvmx_usb_port_status result;

	स_रखो(&result, 0, माप(result));

	usbc_hprt.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HPRT(usb->index));
	result.port_enabled = usbc_hprt.s.prtena;
	result.port_over_current = usbc_hprt.s.prtovrcurract;
	result.port_घातered = usbc_hprt.s.prtpwr;
	result.port_speed = usbc_hprt.s.prtspd;
	result.connected = usbc_hprt.s.prtconnsts;
	result.connect_change =
		result.connected != usb->port_status.connected;

	वापस result;
पूर्ण

/**
 * Open a भव pipe between the host and a USB device. A pipe
 * must be खोलोed beक्रमe data can be transferred between a device
 * and Octeon.
 *
 * @usb:	     USB device state populated by cvmx_usb_initialize().
 * @device_addr:
 *		     USB device address to खोलो the pipe to
 *		     (0-127).
 * @endpoपूर्णांक_num:
 *		     USB endpoपूर्णांक number to खोलो the pipe to
 *		     (0-15).
 * @device_speed:
 *		     The speed of the device the pipe is going
 *		     to. This must match the device's speed,
 *		     which may be dअगरferent than the port speed.
 * @max_packet:	     The maximum packet length the device can
 *		     transmit/receive (low speed=0-8, full
 *		     speed=0-1023, high speed=0-1024). This value
 *		     comes from the standard endpoपूर्णांक descriptor
 *		     field wMaxPacketSize bits <10:0>.
 * @transfer_type:
 *		     The type of transfer this pipe is क्रम.
 * @transfer_dir:
 *		     The direction the pipe is in. This is not
 *		     used क्रम control pipes.
 * @पूर्णांकerval:	     For ISOCHRONOUS and INTERRUPT transfers,
 *		     this is how often the transfer is scheduled
 *		     क्रम. All other transfers should specअगरy
 *		     zero. The units are in frames (8000/sec at
 *		     high speed, 1000/sec क्रम full speed).
 * @multi_count:
 *		     For high speed devices, this is the maximum
 *		     allowed number of packet per microframe.
 *		     Specअगरy zero क्रम non high speed devices. This
 *		     value comes from the standard endpoपूर्णांक descriptor
 *		     field wMaxPacketSize bits <12:11>.
 * @hub_device_addr:
 *		     Hub device address this device is connected
 *		     to. Devices connected directly to Octeon
 *		     use zero. This is only used when the device
 *		     is full/low speed behind a high speed hub.
 *		     The address will be of the high speed hub,
 *		     not and full speed hubs after it.
 * @hub_port:	     Which port on the hub the device is
 *		     connected. Use zero क्रम devices connected
 *		     directly to Octeon. Like hub_device_addr,
 *		     this is only used क्रम full/low speed
 *		     devices behind a high speed hub.
 *
 * Returns: A non-शून्य value is a pipe. शून्य means an error.
 */
अटल काष्ठा cvmx_usb_pipe *cvmx_usb_खोलो_pipe(काष्ठा octeon_hcd *usb,
						पूर्णांक device_addr,
						पूर्णांक endpoपूर्णांक_num,
						क्रमागत cvmx_usb_speed
							device_speed,
						पूर्णांक max_packet,
						क्रमागत cvmx_usb_transfer
							transfer_type,
						क्रमागत cvmx_usb_direction
							transfer_dir,
						पूर्णांक पूर्णांकerval, पूर्णांक multi_count,
						पूर्णांक hub_device_addr,
						पूर्णांक hub_port)
अणु
	काष्ठा cvmx_usb_pipe *pipe;

	pipe = kzalloc(माप(*pipe), GFP_ATOMIC);
	अगर (!pipe)
		वापस शून्य;
	अगर ((device_speed == CVMX_USB_SPEED_HIGH) &&
	    (transfer_dir == CVMX_USB_सूचीECTION_OUT) &&
	    (transfer_type == CVMX_USB_TRANSFER_BULK))
		pipe->flags |= CVMX_USB_PIPE_FLAGS_NEED_PING;
	pipe->device_addr = device_addr;
	pipe->endpoपूर्णांक_num = endpoपूर्णांक_num;
	pipe->device_speed = device_speed;
	pipe->max_packet = max_packet;
	pipe->transfer_type = transfer_type;
	pipe->transfer_dir = transfer_dir;
	INIT_LIST_HEAD(&pipe->transactions);

	/*
	 * All pipes use पूर्णांकerval to rate limit NAK processing. Force an
	 * पूर्णांकerval अगर one wasn't supplied
	 */
	अगर (!पूर्णांकerval)
		पूर्णांकerval = 1;
	अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
		pipe->पूर्णांकerval = पूर्णांकerval * 8;
		/* Force start splits to be schedule on uFrame 0 */
		pipe->next_tx_frame = ((usb->frame_number + 7) & ~7) +
					pipe->पूर्णांकerval;
	पूर्ण अन्यथा अणु
		pipe->पूर्णांकerval = पूर्णांकerval;
		pipe->next_tx_frame = usb->frame_number + pipe->पूर्णांकerval;
	पूर्ण
	pipe->multi_count = multi_count;
	pipe->hub_device_addr = hub_device_addr;
	pipe->hub_port = hub_port;
	pipe->pid_toggle = 0;
	pipe->split_sc_frame = -1;
	list_add_tail(&pipe->node, &usb->idle_pipes);

	/*
	 * We करोn't need to tell the hardware about this pipe yet since
	 * it करोesn't have any submitted requests
	 */

	वापस pipe;
पूर्ण

/**
 * Poll the RX FIFOs and हटाओ data as needed. This function is only used
 * in non DMA mode. It is very important that this function be called quickly
 * enough to prevent FIFO overflow.
 *
 * @usb:	USB device state populated by cvmx_usb_initialize().
 */
अटल व्योम cvmx_usb_poll_rx_fअगरo(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbcx_grxstsph rx_status;
	पूर्णांक channel;
	पूर्णांक bytes;
	u64 address;
	u32 *ptr;

	rx_status.u32 = cvmx_usb_पढ़ो_csr32(usb,
					    CVMX_USBCX_GRXSTSPH(usb->index));
	/* Only पढ़ो data अगर IN data is there */
	अगर (rx_status.s.pktsts != 2)
		वापस;
	/* Check अगर no data is available */
	अगर (!rx_status.s.bcnt)
		वापस;

	channel = rx_status.s.chnum;
	bytes = rx_status.s.bcnt;
	अगर (!bytes)
		वापस;

	/* Get where the DMA engine would have written this data */
	address = cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) +
				     channel * 8);

	ptr = cvmx_phys_to_ptr(address);
	cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) + channel * 8,
			    address + bytes);

	/* Loop writing the FIFO data क्रम this packet पूर्णांकo memory */
	जबतक (bytes > 0) अणु
		*ptr++ = cvmx_usb_पढ़ो_csr32(usb,
					USB_FIFO_ADDRESS(channel, usb->index));
		bytes -= 4;
	पूर्ण
	CVMX_SYNCW;
पूर्ण

/**
 * Fill the TX hardware fअगरo with data out of the software
 * fअगरos
 *
 * @usb:	    USB device state populated by cvmx_usb_initialize().
 * @fअगरo:	    Software fअगरo to use
 * @available:	    Amount of space in the hardware fअगरo
 *
 * Returns: Non zero अगर the hardware fअगरo was too small and needs
 *	    to be serviced again.
 */
अटल पूर्णांक cvmx_usb_fill_tx_hw(काष्ठा octeon_hcd *usb,
			       काष्ठा cvmx_usb_tx_fअगरo *fअगरo, पूर्णांक available)
अणु
	/*
	 * We're done either when there isn't anymore space or the software FIFO
	 * is empty
	 */
	जबतक (available && (fअगरo->head != fअगरo->tail)) अणु
		पूर्णांक i = fअगरo->tail;
		स्थिर u32 *ptr = cvmx_phys_to_ptr(fअगरo->entry[i].address);
		u64 csr_address = USB_FIFO_ADDRESS(fअगरo->entry[i].channel,
						   usb->index) ^ 4;
		पूर्णांक words = available;

		/* Limit the amount of data to what the SW fअगरo has */
		अगर (fअगरo->entry[i].size <= available) अणु
			words = fअगरo->entry[i].size;
			fअगरo->tail++;
			अगर (fअगरo->tail > MAX_CHANNELS)
				fअगरo->tail = 0;
		पूर्ण

		/* Update the next locations and counts */
		available -= words;
		fअगरo->entry[i].address += words * 4;
		fअगरo->entry[i].size -= words;

		/*
		 * Write the HW fअगरo data. The पढ़ो every three ग_लिखोs is due
		 * to an errata on CN3XXX chips
		 */
		जबतक (words > 3) अणु
			cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
			cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
			cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
			cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
			words -= 3;
		पूर्ण
		cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
		अगर (--words) अणु
			cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
			अगर (--words)
				cvmx_ग_लिखो64_uपूर्णांक32(csr_address, *ptr++);
		पूर्ण
		cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
	पूर्ण
	वापस fअगरo->head != fअगरo->tail;
पूर्ण

/**
 * Check the hardware FIFOs and fill them as needed
 *
 * @usb:	USB device state populated by cvmx_usb_initialize().
 */
अटल व्योम cvmx_usb_poll_tx_fअगरo(काष्ठा octeon_hcd *usb)
अणु
	अगर (usb->periodic.head != usb->periodic.tail) अणु
		जोड़ cvmx_usbcx_hptxsts tx_status;

		tx_status.u32 = cvmx_usb_पढ़ो_csr32(usb,
						    CVMX_USBCX_HPTXSTS(usb->index));
		अगर (cvmx_usb_fill_tx_hw(usb, &usb->periodic,
					tx_status.s.ptxfspcavail))
			USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gपूर्णांकmsk, ptxfempmsk, 1);
		अन्यथा
			USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gपूर्णांकmsk, ptxfempmsk, 0);
	पूर्ण

	अगर (usb->nonperiodic.head != usb->nonperiodic.tail) अणु
		जोड़ cvmx_usbcx_gnptxsts tx_status;

		tx_status.u32 = cvmx_usb_पढ़ो_csr32(usb,
						    CVMX_USBCX_GNPTXSTS(usb->index));
		अगर (cvmx_usb_fill_tx_hw(usb, &usb->nonperiodic,
					tx_status.s.nptxfspcavail))
			USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gपूर्णांकmsk, nptxfempmsk, 1);
		अन्यथा
			USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gपूर्णांकmsk, nptxfempmsk, 0);
	पूर्ण
पूर्ण

/**
 * Fill the TX FIFO with an outgoing packet
 *
 * @usb:	  USB device state populated by cvmx_usb_initialize().
 * @channel:	  Channel number to get packet from
 */
अटल व्योम cvmx_usb_fill_tx_fअगरo(काष्ठा octeon_hcd *usb, पूर्णांक channel)
अणु
	जोड़ cvmx_usbcx_hcअक्षरx hcअक्षर;
	जोड़ cvmx_usbcx_hcspltx usbc_hcsplt;
	जोड़ cvmx_usbcx_hctsizx usbc_hctsiz;
	काष्ठा cvmx_usb_tx_fअगरo *fअगरo;

	/* We only need to fill data on outbound channels */
	hcअक्षर.u32 = cvmx_usb_पढ़ो_csr32(usb,
					 CVMX_USBCX_HCCHARX(channel, usb->index));
	अगर (hcअक्षर.s.epdir != CVMX_USB_सूचीECTION_OUT)
		वापस;

	/* OUT Splits only have data on the start and not the complete */
	usbc_hcsplt.u32 = cvmx_usb_पढ़ो_csr32(usb,
					      CVMX_USBCX_HCSPLTX(channel, usb->index));
	अगर (usbc_hcsplt.s.spltena && usbc_hcsplt.s.compsplt)
		वापस;

	/*
	 * Find out how many bytes we need to fill and convert it पूर्णांकo 32bit
	 * words.
	 */
	usbc_hctsiz.u32 = cvmx_usb_पढ़ो_csr32(usb,
					      CVMX_USBCX_HCTSIZX(channel, usb->index));
	अगर (!usbc_hctsiz.s.xfersize)
		वापस;

	अगर ((hcअक्षर.s.eptype == CVMX_USB_TRANSFER_INTERRUPT) ||
	    (hcअक्षर.s.eptype == CVMX_USB_TRANSFER_ISOCHRONOUS))
		fअगरo = &usb->periodic;
	अन्यथा
		fअगरo = &usb->nonperiodic;

	fअगरo->entry[fअगरo->head].channel = channel;
	fअगरo->entry[fअगरo->head].address =
		cvmx_पढ़ो64_uपूर्णांक64(CVMX_USBNX_DMA0_OUTB_CHN0(usb->index) +
				   channel * 8);
	fअगरo->entry[fअगरo->head].size = (usbc_hctsiz.s.xfersize + 3) >> 2;
	fअगरo->head++;
	अगर (fअगरo->head > MAX_CHANNELS)
		fअगरo->head = 0;

	cvmx_usb_poll_tx_fअगरo(usb);
पूर्ण

/**
 * Perक्रमm channel specअगरic setup क्रम Control transactions. All
 * the generic stuff will alपढ़ोy have been करोne in cvmx_usb_start_channel().
 *
 * @usb:	  USB device state populated by cvmx_usb_initialize().
 * @channel:	  Channel to setup
 * @pipe:	  Pipe क्रम control transaction
 */
अटल व्योम cvmx_usb_start_channel_control(काष्ठा octeon_hcd *usb,
					   पूर्णांक channel,
					   काष्ठा cvmx_usb_pipe *pipe)
अणु
	काष्ठा usb_hcd *hcd = octeon_to_hcd(usb);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा cvmx_usb_transaction *transaction =
		list_first_entry(&pipe->transactions, typeof(*transaction),
				 node);
	काष्ठा usb_ctrlrequest *header =
		cvmx_phys_to_ptr(transaction->control_header);
	पूर्णांक bytes_to_transfer = transaction->buffer_length -
		transaction->actual_bytes;
	पूर्णांक packets_to_transfer;
	जोड़ cvmx_usbcx_hctsizx usbc_hctsiz;

	usbc_hctsiz.u32 = cvmx_usb_पढ़ो_csr32(usb,
					      CVMX_USBCX_HCTSIZX(channel, usb->index));

	चयन (transaction->stage) अणु
	हाल CVMX_USB_STAGE_NON_CONTROL:
	हाल CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE:
		dev_err(dev, "%s: ERROR - Non control stage\n", __func__);
		अवरोध;
	हाल CVMX_USB_STAGE_SETUP:
		usbc_hctsiz.s.pid = 3; /* Setup */
		bytes_to_transfer = माप(*header);
		/* All Control operations start with a setup going OUT */
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				CVMX_USB_सूचीECTION_OUT);
		/*
		 * Setup send the control header instead of the buffer data. The
		 * buffer data will be used in the next stage
		 */
		cvmx_ग_लिखो64_uपूर्णांक64(CVMX_USBNX_DMA0_OUTB_CHN0(usb->index) +
					channel * 8,
				    transaction->control_header);
		अवरोध;
	हाल CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE:
		usbc_hctsiz.s.pid = 3; /* Setup */
		bytes_to_transfer = 0;
		/* All Control operations start with a setup going OUT */
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				CVMX_USB_सूचीECTION_OUT);

		USB_SET_FIELD32(CVMX_USBCX_HCSPLTX(channel, usb->index),
				cvmx_usbcx_hcspltx, compsplt, 1);
		अवरोध;
	हाल CVMX_USB_STAGE_DATA:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			अगर (header->bRequestType & USB_सूची_IN)
				bytes_to_transfer = 0;
			अन्यथा अगर (bytes_to_transfer > pipe->max_packet)
				bytes_to_transfer = pipe->max_packet;
		पूर्ण
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				((header->bRequestType & USB_सूची_IN) ?
					CVMX_USB_सूचीECTION_IN :
					CVMX_USB_सूचीECTION_OUT));
		अवरोध;
	हाल CVMX_USB_STAGE_DATA_SPLIT_COMPLETE:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		अगर (!(header->bRequestType & USB_सूची_IN))
			bytes_to_transfer = 0;
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				((header->bRequestType & USB_सूची_IN) ?
					CVMX_USB_सूचीECTION_IN :
					CVMX_USB_सूचीECTION_OUT));
		USB_SET_FIELD32(CVMX_USBCX_HCSPLTX(channel, usb->index),
				cvmx_usbcx_hcspltx, compsplt, 1);
		अवरोध;
	हाल CVMX_USB_STAGE_STATUS:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		bytes_to_transfer = 0;
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				((header->bRequestType & USB_सूची_IN) ?
					CVMX_USB_सूचीECTION_OUT :
					CVMX_USB_सूचीECTION_IN));
		अवरोध;
	हाल CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		bytes_to_transfer = 0;
		USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
				cvmx_usbcx_hcअक्षरx, epdir,
				((header->bRequestType & USB_सूची_IN) ?
					CVMX_USB_सूचीECTION_OUT :
					CVMX_USB_सूचीECTION_IN));
		USB_SET_FIELD32(CVMX_USBCX_HCSPLTX(channel, usb->index),
				cvmx_usbcx_hcspltx, compsplt, 1);
		अवरोध;
	पूर्ण

	/*
	 * Make sure the transfer never exceeds the byte limit of the hardware.
	 * Further bytes will be sent as जारीd transactions
	 */
	अगर (bytes_to_transfer > MAX_TRANSFER_BYTES) अणु
		/* Round MAX_TRANSFER_BYTES to a multiple of out packet size */
		bytes_to_transfer = MAX_TRANSFER_BYTES / pipe->max_packet;
		bytes_to_transfer *= pipe->max_packet;
	पूर्ण

	/*
	 * Calculate the number of packets to transfer. If the length is zero
	 * we still need to transfer one packet
	 */
	packets_to_transfer = DIV_ROUND_UP(bytes_to_transfer,
					   pipe->max_packet);
	अगर (packets_to_transfer == 0) अणु
		packets_to_transfer = 1;
	पूर्ण अन्यथा अगर ((packets_to_transfer > 1) &&
			(usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)) अणु
		/*
		 * Limit to one packet when not using DMA. Channels must be
		 * restarted between every packet क्रम IN transactions, so there
		 * is no reason to करो multiple packets in a row
		 */
		packets_to_transfer = 1;
		bytes_to_transfer = packets_to_transfer * pipe->max_packet;
	पूर्ण अन्यथा अगर (packets_to_transfer > MAX_TRANSFER_PACKETS) अणु
		/*
		 * Limit the number of packet and data transferred to what the
		 * hardware can handle
		 */
		packets_to_transfer = MAX_TRANSFER_PACKETS;
		bytes_to_transfer = packets_to_transfer * pipe->max_packet;
	पूर्ण

	usbc_hctsiz.s.xfersize = bytes_to_transfer;
	usbc_hctsiz.s.pktcnt = packets_to_transfer;

	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HCTSIZX(channel, usb->index),
			     usbc_hctsiz.u32);
पूर्ण

/**
 * Start a channel to perक्रमm the pipe's head transaction
 *
 * @usb:	  USB device state populated by cvmx_usb_initialize().
 * @channel:	  Channel to setup
 * @pipe:	  Pipe to start
 */
अटल व्योम cvmx_usb_start_channel(काष्ठा octeon_hcd *usb, पूर्णांक channel,
				   काष्ठा cvmx_usb_pipe *pipe)
अणु
	काष्ठा cvmx_usb_transaction *transaction =
		list_first_entry(&pipe->transactions, typeof(*transaction),
				 node);

	/* Make sure all ग_लिखोs to the DMA region get flushed */
	CVMX_SYNCW;

	/* Attach the channel to the pipe */
	usb->pipe_क्रम_channel[channel] = pipe;
	pipe->channel = channel;
	pipe->flags |= CVMX_USB_PIPE_FLAGS_SCHEDULED;

	/* Mark this channel as in use */
	usb->idle_hardware_channels &= ~(1 << channel);

	/* Enable the channel पूर्णांकerrupt bits */
	अणु
		जोड़ cvmx_usbcx_hcपूर्णांकx usbc_hcपूर्णांक;
		जोड़ cvmx_usbcx_hcपूर्णांकmskx usbc_hcपूर्णांकmsk;
		जोड़ cvmx_usbcx_haपूर्णांकmsk usbc_haपूर्णांकmsk;

		/* Clear all channel status bits */
		usbc_hcपूर्णांक.u32 = cvmx_usb_पढ़ो_csr32(usb,
						     CVMX_USBCX_HCINTX(channel, usb->index));

		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCINTX(channel, usb->index),
				     usbc_hcपूर्णांक.u32);

		usbc_hcपूर्णांकmsk.u32 = 0;
		usbc_hcपूर्णांकmsk.s.chhltdmsk = 1;
		अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA) अणु
			/*
			 * Channels need these extra पूर्णांकerrupts when we aren't
			 * in DMA mode.
			 */
			usbc_hcपूर्णांकmsk.s.datatglerrmsk = 1;
			usbc_hcपूर्णांकmsk.s.frmovrunmsk = 1;
			usbc_hcपूर्णांकmsk.s.bblerrmsk = 1;
			usbc_hcपूर्णांकmsk.s.xacterrmsk = 1;
			अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
				/*
				 * Splits करोn't generate xfercompl, so we need
				 * ACK and NYET.
				 */
				usbc_hcपूर्णांकmsk.s.nyeपंचांगsk = 1;
				usbc_hcपूर्णांकmsk.s.ackmsk = 1;
			पूर्ण
			usbc_hcपूर्णांकmsk.s.nakmsk = 1;
			usbc_hcपूर्णांकmsk.s.stallmsk = 1;
			usbc_hcपूर्णांकmsk.s.xfercomplmsk = 1;
		पूर्ण
		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCINTMSKX(channel, usb->index),
				     usbc_hcपूर्णांकmsk.u32);

		/* Enable the channel पूर्णांकerrupt to propagate */
		usbc_haपूर्णांकmsk.u32 = cvmx_usb_पढ़ो_csr32(usb,
							CVMX_USBCX_HAINTMSK(usb->index));
		usbc_haपूर्णांकmsk.s.haपूर्णांकmsk |= 1 << channel;
		cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HAINTMSK(usb->index),
				     usbc_haपूर्णांकmsk.u32);
	पूर्ण

	/* Setup the location the DMA engine uses. */
	अणु
		u64 reg;
		u64 dma_address = transaction->buffer +
				  transaction->actual_bytes;

		अगर (transaction->type == CVMX_USB_TRANSFER_ISOCHRONOUS)
			dma_address = transaction->buffer +
					transaction->iso_packets[0].offset +
					transaction->actual_bytes;

		अगर (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT)
			reg = CVMX_USBNX_DMA0_OUTB_CHN0(usb->index);
		अन्यथा
			reg = CVMX_USBNX_DMA0_INB_CHN0(usb->index);
		cvmx_ग_लिखो64_uपूर्णांक64(reg + channel * 8, dma_address);
	पूर्ण

	/* Setup both the size of the transfer and the SPLIT अक्षरacteristics */
	अणु
		जोड़ cvmx_usbcx_hcspltx usbc_hcsplt = अणु.u32 = 0पूर्ण;
		जोड़ cvmx_usbcx_hctsizx usbc_hctsiz = अणु.u32 = 0पूर्ण;
		पूर्णांक packets_to_transfer;
		पूर्णांक bytes_to_transfer = transaction->buffer_length -
			transaction->actual_bytes;

		/*
		 * ISOCHRONOUS transactions store each inभागidual transfer size
		 * in the packet काष्ठाure, not the global buffer_length
		 */
		अगर (transaction->type == CVMX_USB_TRANSFER_ISOCHRONOUS)
			bytes_to_transfer =
				transaction->iso_packets[0].length -
				transaction->actual_bytes;

		/*
		 * We need to करो split transactions when we are talking to non
		 * high speed devices that are behind a high speed hub
		 */
		अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			/*
			 * On the start split phase (stage is even) record the
			 * frame number we will need to send the split complete.
			 * We only store the lower two bits since the समय ahead
			 * can only be two frames
			 */
			अगर ((transaction->stage & 1) == 0) अणु
				अगर (transaction->type == CVMX_USB_TRANSFER_BULK)
					pipe->split_sc_frame =
						(usb->frame_number + 1) & 0x7f;
				अन्यथा
					pipe->split_sc_frame =
						(usb->frame_number + 2) & 0x7f;
			पूर्ण अन्यथा अणु
				pipe->split_sc_frame = -1;
			पूर्ण

			usbc_hcsplt.s.spltena = 1;
			usbc_hcsplt.s.hubaddr = pipe->hub_device_addr;
			usbc_hcsplt.s.prtaddr = pipe->hub_port;
			usbc_hcsplt.s.compsplt = (transaction->stage ==
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE);

			/*
			 * SPLIT transactions can only ever transmit one data
			 * packet so limit the transfer size to the max packet
			 * size
			 */
			अगर (bytes_to_transfer > pipe->max_packet)
				bytes_to_transfer = pipe->max_packet;

			/*
			 * ISOCHRONOUS OUT splits are unique in that they limit
			 * data transfers to 188 byte chunks representing the
			 * begin/middle/end of the data or all
			 */
			अगर (!usbc_hcsplt.s.compsplt &&
			    (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT) &&
			    (pipe->transfer_type ==
			     CVMX_USB_TRANSFER_ISOCHRONOUS)) अणु
				/*
				 * Clear the split complete frame number as
				 * there isn't going to be a split complete
				 */
				pipe->split_sc_frame = -1;
				/*
				 * See अगर we've started this transfer and sent
				 * data
				 */
				अगर (transaction->actual_bytes == 0) अणु
					/*
					 * Nothing sent yet, this is either a
					 * begin or the entire payload
					 */
					अगर (bytes_to_transfer <= 188)
						/* Entire payload in one go */
						usbc_hcsplt.s.xactpos = 3;
					अन्यथा
						/* First part of payload */
						usbc_hcsplt.s.xactpos = 2;
				पूर्ण अन्यथा अणु
					/*
					 * Continuing the previous data, we must
					 * either be in the middle or at the end
					 */
					अगर (bytes_to_transfer <= 188)
						/* End of payload */
						usbc_hcsplt.s.xactpos = 1;
					अन्यथा
						/* Middle of payload */
						usbc_hcsplt.s.xactpos = 0;
				पूर्ण
				/*
				 * Again, the transfer size is limited to 188
				 * bytes
				 */
				अगर (bytes_to_transfer > 188)
					bytes_to_transfer = 188;
			पूर्ण
		पूर्ण

		/*
		 * Make sure the transfer never exceeds the byte limit of the
		 * hardware. Further bytes will be sent as जारीd
		 * transactions
		 */
		अगर (bytes_to_transfer > MAX_TRANSFER_BYTES) अणु
			/*
			 * Round MAX_TRANSFER_BYTES to a multiple of out packet
			 * size
			 */
			bytes_to_transfer = MAX_TRANSFER_BYTES /
				pipe->max_packet;
			bytes_to_transfer *= pipe->max_packet;
		पूर्ण

		/*
		 * Calculate the number of packets to transfer. If the length is
		 * zero we still need to transfer one packet
		 */
		packets_to_transfer =
			DIV_ROUND_UP(bytes_to_transfer, pipe->max_packet);
		अगर (packets_to_transfer == 0) अणु
			packets_to_transfer = 1;
		पूर्ण अन्यथा अगर ((packets_to_transfer > 1) &&
			   (usb->init_flags &
			    CVMX_USB_INITIALIZE_FLAGS_NO_DMA)) अणु
			/*
			 * Limit to one packet when not using DMA. Channels must
			 * be restarted between every packet क्रम IN
			 * transactions, so there is no reason to करो multiple
			 * packets in a row
			 */
			packets_to_transfer = 1;
			bytes_to_transfer = packets_to_transfer *
				pipe->max_packet;
		पूर्ण अन्यथा अगर (packets_to_transfer > MAX_TRANSFER_PACKETS) अणु
			/*
			 * Limit the number of packet and data transferred to
			 * what the hardware can handle
			 */
			packets_to_transfer = MAX_TRANSFER_PACKETS;
			bytes_to_transfer = packets_to_transfer *
				pipe->max_packet;
		पूर्ण

		usbc_hctsiz.s.xfersize = bytes_to_transfer;
		usbc_hctsiz.s.pktcnt = packets_to_transfer;

		/* Update the DATA0/DATA1 toggle */
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		/*
		 * High speed pipes may need a hardware ping beक्रमe they start
		 */
		अगर (pipe->flags & CVMX_USB_PIPE_FLAGS_NEED_PING)
			usbc_hctsiz.s.करोpng = 1;

		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCSPLTX(channel, usb->index),
				     usbc_hcsplt.u32);
		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCTSIZX(channel, usb->index),
				     usbc_hctsiz.u32);
	पूर्ण

	/* Setup the Host Channel Characteristics Register */
	अणु
		जोड़ cvmx_usbcx_hcअक्षरx usbc_hcअक्षर = अणु.u32 = 0पूर्ण;

		/*
		 * Set the startframe odd/even properly. This is only used क्रम
		 * periodic
		 */
		usbc_hcअक्षर.s.oddfrm = usb->frame_number & 1;

		/*
		 * Set the number of back to back packets allowed by this
		 * endpoपूर्णांक. Split transactions पूर्णांकerpret "ec" as the number of
		 * immediate retries of failure. These retries happen too
		 * quickly, so we disable these entirely क्रम splits
		 */
		अगर (cvmx_usb_pipe_needs_split(usb, pipe))
			usbc_hcअक्षर.s.ec = 1;
		अन्यथा अगर (pipe->multi_count < 1)
			usbc_hcअक्षर.s.ec = 1;
		अन्यथा अगर (pipe->multi_count > 3)
			usbc_hcअक्षर.s.ec = 3;
		अन्यथा
			usbc_hcअक्षर.s.ec = pipe->multi_count;

		/* Set the rest of the endpoपूर्णांक specअगरic settings */
		usbc_hcअक्षर.s.devaddr = pipe->device_addr;
		usbc_hcअक्षर.s.eptype = transaction->type;
		usbc_hcअक्षर.s.lspddev =
			(pipe->device_speed == CVMX_USB_SPEED_LOW);
		usbc_hcअक्षर.s.epdir = pipe->transfer_dir;
		usbc_hcअक्षर.s.epnum = pipe->endpoपूर्णांक_num;
		usbc_hcअक्षर.s.mps = pipe->max_packet;
		cvmx_usb_ग_लिखो_csr32(usb,
				     CVMX_USBCX_HCCHARX(channel, usb->index),
				     usbc_hcअक्षर.u32);
	पूर्ण

	/* Do transaction type specअगरic fixups as needed */
	चयन (transaction->type) अणु
	हाल CVMX_USB_TRANSFER_CONTROL:
		cvmx_usb_start_channel_control(usb, channel, pipe);
		अवरोध;
	हाल CVMX_USB_TRANSFER_BULK:
	हाल CVMX_USB_TRANSFER_INTERRUPT:
		अवरोध;
	हाल CVMX_USB_TRANSFER_ISOCHRONOUS:
		अगर (!cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			/*
			 * ISO transactions require dअगरferent PIDs depending on
			 * direction and how many packets are needed
			 */
			अगर (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT) अणु
				अगर (pipe->multi_count < 2) /* Need DATA0 */
					USB_SET_FIELD32(
						CVMX_USBCX_HCTSIZX(channel,
								   usb->index),
						cvmx_usbcx_hctsizx, pid, 0);
				अन्यथा /* Need MDATA */
					USB_SET_FIELD32(
						CVMX_USBCX_HCTSIZX(channel,
								   usb->index),
						cvmx_usbcx_hctsizx, pid, 3);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	अणु
		जोड़ cvmx_usbcx_hctsizx usbc_hctsiz = अणु .u32 =
			cvmx_usb_पढ़ो_csr32(usb,
					    CVMX_USBCX_HCTSIZX(channel,
							       usb->index))
		पूर्ण;
		transaction->xfersize = usbc_hctsiz.s.xfersize;
		transaction->pktcnt = usbc_hctsiz.s.pktcnt;
	पूर्ण
	/* Remember when we start a split transaction */
	अगर (cvmx_usb_pipe_needs_split(usb, pipe))
		usb->active_split = transaction;
	USB_SET_FIELD32(CVMX_USBCX_HCCHARX(channel, usb->index),
			cvmx_usbcx_hcअक्षरx, chena, 1);
	अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
		cvmx_usb_fill_tx_fअगरo(usb, channel);
पूर्ण

/**
 * Find a pipe that is पढ़ोy to be scheduled to hardware.
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @xfer_type:	 Transfer type
 *
 * Returns: Pipe or शून्य अगर none are पढ़ोy
 */
अटल काष्ठा cvmx_usb_pipe *cvmx_usb_find_पढ़ोy_pipe(काष्ठा octeon_hcd *usb,
						      क्रमागत cvmx_usb_transfer xfer_type)
अणु
	काष्ठा list_head *list = usb->active_pipes + xfer_type;
	u64 current_frame = usb->frame_number;
	काष्ठा cvmx_usb_pipe *pipe;

	list_क्रम_each_entry(pipe, list, node) अणु
		काष्ठा cvmx_usb_transaction *t =
			list_first_entry(&pipe->transactions, typeof(*t),
					 node);
		अगर (!(pipe->flags & CVMX_USB_PIPE_FLAGS_SCHEDULED) && t &&
		    (pipe->next_tx_frame <= current_frame) &&
		    ((pipe->split_sc_frame == -1) ||
		     ((((पूर्णांक)current_frame - pipe->split_sc_frame) & 0x7f) <
		      0x40)) &&
		    (!usb->active_split || (usb->active_split == t))) अणु
			prefetch(t);
			वापस pipe;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा cvmx_usb_pipe *cvmx_usb_next_pipe(काष्ठा octeon_hcd *usb,
						पूर्णांक is_sof)
अणु
	काष्ठा cvmx_usb_pipe *pipe;

	/* Find a pipe needing service. */
	अगर (is_sof) अणु
		/*
		 * Only process periodic pipes on SOF पूर्णांकerrupts. This way we
		 * are sure that the periodic data is sent in the beginning of
		 * the frame.
		 */
		pipe = cvmx_usb_find_पढ़ोy_pipe(usb,
						CVMX_USB_TRANSFER_ISOCHRONOUS);
		अगर (pipe)
			वापस pipe;
		pipe = cvmx_usb_find_पढ़ोy_pipe(usb,
						CVMX_USB_TRANSFER_INTERRUPT);
		अगर (pipe)
			वापस pipe;
	पूर्ण
	pipe = cvmx_usb_find_पढ़ोy_pipe(usb, CVMX_USB_TRANSFER_CONTROL);
	अगर (pipe)
		वापस pipe;
	वापस cvmx_usb_find_पढ़ोy_pipe(usb, CVMX_USB_TRANSFER_BULK);
पूर्ण

/**
 * Called whenever a pipe might need to be scheduled to the
 * hardware.
 *
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @is_sof:	 True अगर this schedule was called on a SOF पूर्णांकerrupt.
 */
अटल व्योम cvmx_usb_schedule(काष्ठा octeon_hcd *usb, पूर्णांक is_sof)
अणु
	पूर्णांक channel;
	काष्ठा cvmx_usb_pipe *pipe;
	पूर्णांक need_sof;
	क्रमागत cvmx_usb_transfer ttype;

	अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA) अणु
		/*
		 * Without DMA we need to be careful to not schedule something
		 * at the end of a frame and cause an overrun.
		 */
		जोड़ cvmx_usbcx_hfnum hfnum = अणु
			.u32 = cvmx_usb_पढ़ो_csr32(usb,
						CVMX_USBCX_HFNUM(usb->index))
		पूर्ण;

		जोड़ cvmx_usbcx_hfir hfir = अणु
			.u32 = cvmx_usb_पढ़ो_csr32(usb,
						CVMX_USBCX_HFIR(usb->index))
		पूर्ण;

		अगर (hfnum.s.frrem < hfir.s.frपूर्णांक / 4)
			जाओ करोne;
	पूर्ण

	जबतक (usb->idle_hardware_channels) अणु
		/* Find an idle channel */
		channel = __fls(usb->idle_hardware_channels);
		अगर (unlikely(channel > 7))
			अवरोध;

		pipe = cvmx_usb_next_pipe(usb, is_sof);
		अगर (!pipe)
			अवरोध;

		cvmx_usb_start_channel(usb, channel, pipe);
	पूर्ण

करोne:
	/*
	 * Only enable SOF पूर्णांकerrupts when we have transactions pending in the
	 * future that might need to be scheduled
	 */
	need_sof = 0;
	क्रम (ttype = CVMX_USB_TRANSFER_CONTROL;
	     ttype <= CVMX_USB_TRANSFER_INTERRUPT; ttype++) अणु
		list_क्रम_each_entry(pipe, &usb->active_pipes[ttype], node) अणु
			अगर (pipe->next_tx_frame > usb->frame_number) अणु
				need_sof = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	USB_SET_FIELD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gपूर्णांकmsk, sofmsk, need_sof);
पूर्ण

अटल व्योम octeon_usb_urb_complete_callback(काष्ठा octeon_hcd *usb,
					     क्रमागत cvmx_usb_status status,
					     काष्ठा cvmx_usb_pipe *pipe,
					     काष्ठा cvmx_usb_transaction
						*transaction,
					     पूर्णांक bytes_transferred,
					     काष्ठा urb *urb)
अणु
	काष्ठा usb_hcd *hcd = octeon_to_hcd(usb);
	काष्ठा device *dev = hcd->self.controller;

	अगर (likely(status == CVMX_USB_STATUS_OK))
		urb->actual_length = bytes_transferred;
	अन्यथा
		urb->actual_length = 0;

	urb->hcpriv = शून्य;

	/* For Isochronous transactions we need to update the URB packet status
	 * list from data in our निजी copy
	 */
	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		पूर्णांक i;
		/*
		 * The poपूर्णांकer to the निजी list is stored in the setup_packet
		 * field.
		 */
		काष्ठा cvmx_usb_iso_packet *iso_packet =
			(काष्ठा cvmx_usb_iso_packet *)urb->setup_packet;
		/* Recalculate the transfer size by adding up each packet */
		urb->actual_length = 0;
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अगर (iso_packet[i].status == CVMX_USB_STATUS_OK) अणु
				urb->iso_frame_desc[i].status = 0;
				urb->iso_frame_desc[i].actual_length =
					iso_packet[i].length;
				urb->actual_length +=
					urb->iso_frame_desc[i].actual_length;
			पूर्ण अन्यथा अणु
				dev_dbg(dev, "ISOCHRONOUS packet=%d of %d status=%d pipe=%p transaction=%p size=%d\n",
					i, urb->number_of_packets,
					iso_packet[i].status, pipe,
					transaction, iso_packet[i].length);
				urb->iso_frame_desc[i].status = -EREMOTEIO;
			पूर्ण
		पूर्ण
		/* Free the निजी list now that we करोn't need it anymore */
		kमुक्त(iso_packet);
		urb->setup_packet = शून्य;
	पूर्ण

	चयन (status) अणु
	हाल CVMX_USB_STATUS_OK:
		urb->status = 0;
		अवरोध;
	हाल CVMX_USB_STATUS_CANCEL:
		अगर (urb->status == 0)
			urb->status = -ENOENT;
		अवरोध;
	हाल CVMX_USB_STATUS_STALL:
		dev_dbg(dev, "status=stall pipe=%p transaction=%p size=%d\n",
			pipe, transaction, bytes_transferred);
		urb->status = -EPIPE;
		अवरोध;
	हाल CVMX_USB_STATUS_BABBLEERR:
		dev_dbg(dev, "status=babble pipe=%p transaction=%p size=%d\n",
			pipe, transaction, bytes_transferred);
		urb->status = -EPIPE;
		अवरोध;
	हाल CVMX_USB_STATUS_SHORT:
		dev_dbg(dev, "status=short pipe=%p transaction=%p size=%d\n",
			pipe, transaction, bytes_transferred);
		urb->status = -EREMOTEIO;
		अवरोध;
	हाल CVMX_USB_STATUS_ERROR:
	हाल CVMX_USB_STATUS_XACTERR:
	हाल CVMX_USB_STATUS_DATATGLERR:
	हाल CVMX_USB_STATUS_FRAMEERR:
		dev_dbg(dev, "status=%d pipe=%p transaction=%p size=%d\n",
			status, pipe, transaction, bytes_transferred);
		urb->status = -EPROTO;
		अवरोध;
	पूर्ण
	usb_hcd_unlink_urb_from_ep(octeon_to_hcd(usb), urb);
	spin_unlock(&usb->lock);
	usb_hcd_giveback_urb(octeon_to_hcd(usb), urb, urb->status);
	spin_lock(&usb->lock);
पूर्ण

/**
 * Signal the completion of a transaction and मुक्त it. The
 * transaction will be हटाओd from the pipe transaction list.
 *
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @pipe:	 Pipe the transaction is on
 * @transaction:
 *		 Transaction that completed
 * @complete_code:
 *		 Completion code
 */
अटल व्योम cvmx_usb_complete(काष्ठा octeon_hcd *usb,
			      काष्ठा cvmx_usb_pipe *pipe,
			      काष्ठा cvmx_usb_transaction *transaction,
			      क्रमागत cvmx_usb_status complete_code)
अणु
	/* If this was a split then clear our split in progress marker */
	अगर (usb->active_split == transaction)
		usb->active_split = शून्य;

	/*
	 * Isochronous transactions need extra processing as they might not be
	 * करोne after a single data transfer
	 */
	अगर (unlikely(transaction->type == CVMX_USB_TRANSFER_ISOCHRONOUS)) अणु
		/* Update the number of bytes transferred in this ISO packet */
		transaction->iso_packets[0].length = transaction->actual_bytes;
		transaction->iso_packets[0].status = complete_code;

		/*
		 * If there are more ISOs pending and we succeeded, schedule the
		 * next one
		 */
		अगर ((transaction->iso_number_packets > 1) &&
		    (complete_code == CVMX_USB_STATUS_OK)) अणु
			/* No bytes transferred क्रम this packet as of yet */
			transaction->actual_bytes = 0;
			/* One less ISO रुकोing to transfer */
			transaction->iso_number_packets--;
			/* Increment to the next location in our packet array */
			transaction->iso_packets++;
			transaction->stage = CVMX_USB_STAGE_NON_CONTROL;
			वापस;
		पूर्ण
	पूर्ण

	/* Remove the transaction from the pipe list */
	list_del(&transaction->node);
	अगर (list_empty(&pipe->transactions))
		list_move_tail(&pipe->node, &usb->idle_pipes);
	octeon_usb_urb_complete_callback(usb, complete_code, pipe,
					 transaction,
					 transaction->actual_bytes,
					 transaction->urb);
	kमुक्त(transaction);
पूर्ण

/**
 * Submit a usb transaction to a pipe. Called क्रम all types
 * of transactions.
 *
 * @usb:
 * @pipe:	    Which pipe to submit to.
 * @type:	    Transaction type
 * @buffer:	    User buffer क्रम the transaction
 * @buffer_length:
 *		    User buffer's length in bytes
 * @control_header:
 *		    For control transactions, the 8 byte standard header
 * @iso_start_frame:
 *		    For ISO transactions, the start frame
 * @iso_number_packets:
 *		    For ISO, the number of packet in the transaction.
 * @iso_packets:
 *		    A description of each ISO packet
 * @urb:	    URB क्रम the callback
 *
 * Returns: Transaction or शून्य on failure.
 */
अटल काष्ठा cvmx_usb_transaction *cvmx_usb_submit_transaction(
				काष्ठा octeon_hcd *usb,
				काष्ठा cvmx_usb_pipe *pipe,
				क्रमागत cvmx_usb_transfer type,
				u64 buffer,
				पूर्णांक buffer_length,
				u64 control_header,
				पूर्णांक iso_start_frame,
				पूर्णांक iso_number_packets,
				काष्ठा cvmx_usb_iso_packet *iso_packets,
				काष्ठा urb *urb)
अणु
	काष्ठा cvmx_usb_transaction *transaction;

	अगर (unlikely(pipe->transfer_type != type))
		वापस शून्य;

	transaction = kzalloc(माप(*transaction), GFP_ATOMIC);
	अगर (unlikely(!transaction))
		वापस शून्य;

	transaction->type = type;
	transaction->buffer = buffer;
	transaction->buffer_length = buffer_length;
	transaction->control_header = control_header;
	/* FIXME: This is not used, implement it. */
	transaction->iso_start_frame = iso_start_frame;
	transaction->iso_number_packets = iso_number_packets;
	transaction->iso_packets = iso_packets;
	transaction->urb = urb;
	अगर (transaction->type == CVMX_USB_TRANSFER_CONTROL)
		transaction->stage = CVMX_USB_STAGE_SETUP;
	अन्यथा
		transaction->stage = CVMX_USB_STAGE_NON_CONTROL;

	अगर (!list_empty(&pipe->transactions)) अणु
		list_add_tail(&transaction->node, &pipe->transactions);
	पूर्ण अन्यथा अणु
		list_add_tail(&transaction->node, &pipe->transactions);
		list_move_tail(&pipe->node,
			       &usb->active_pipes[pipe->transfer_type]);

		/*
		 * We may need to schedule the pipe अगर this was the head of the
		 * pipe.
		 */
		cvmx_usb_schedule(usb, 0);
	पूर्ण

	वापस transaction;
पूर्ण

/**
 * Call to submit a USB Bulk transfer to a pipe.
 *
 * @usb:	    USB device state populated by cvmx_usb_initialize().
 * @pipe:	    Handle to the pipe क्रम the transfer.
 * @urb:	    URB.
 *
 * Returns: A submitted transaction or शून्य on failure.
 */
अटल काष्ठा cvmx_usb_transaction *cvmx_usb_submit_bulk(
						काष्ठा octeon_hcd *usb,
						काष्ठा cvmx_usb_pipe *pipe,
						काष्ठा urb *urb)
अणु
	वापस cvmx_usb_submit_transaction(usb, pipe, CVMX_USB_TRANSFER_BULK,
					   urb->transfer_dma,
					   urb->transfer_buffer_length,
					   0, /* control_header */
					   0, /* iso_start_frame */
					   0, /* iso_number_packets */
					   शून्य, /* iso_packets */
					   urb);
पूर्ण

/**
 * Call to submit a USB Interrupt transfer to a pipe.
 *
 * @usb:	    USB device state populated by cvmx_usb_initialize().
 * @pipe:	    Handle to the pipe क्रम the transfer.
 * @urb:	    URB वापसed when the callback is called.
 *
 * Returns: A submitted transaction or शून्य on failure.
 */
अटल काष्ठा cvmx_usb_transaction *cvmx_usb_submit_पूर्णांकerrupt(
						काष्ठा octeon_hcd *usb,
						काष्ठा cvmx_usb_pipe *pipe,
						काष्ठा urb *urb)
अणु
	वापस cvmx_usb_submit_transaction(usb, pipe,
					   CVMX_USB_TRANSFER_INTERRUPT,
					   urb->transfer_dma,
					   urb->transfer_buffer_length,
					   0, /* control_header */
					   0, /* iso_start_frame */
					   0, /* iso_number_packets */
					   शून्य, /* iso_packets */
					   urb);
पूर्ण

/**
 * Call to submit a USB Control transfer to a pipe.
 *
 * @usb:	    USB device state populated by cvmx_usb_initialize().
 * @pipe:	    Handle to the pipe क्रम the transfer.
 * @urb:	    URB.
 *
 * Returns: A submitted transaction or शून्य on failure.
 */
अटल काष्ठा cvmx_usb_transaction *cvmx_usb_submit_control(
						काष्ठा octeon_hcd *usb,
						काष्ठा cvmx_usb_pipe *pipe,
						काष्ठा urb *urb)
अणु
	पूर्णांक buffer_length = urb->transfer_buffer_length;
	u64 control_header = urb->setup_dma;
	काष्ठा usb_ctrlrequest *header = cvmx_phys_to_ptr(control_header);

	अगर ((header->bRequestType & USB_सूची_IN) == 0)
		buffer_length = le16_to_cpu(header->wLength);

	वापस cvmx_usb_submit_transaction(usb, pipe,
					   CVMX_USB_TRANSFER_CONTROL,
					   urb->transfer_dma, buffer_length,
					   control_header,
					   0, /* iso_start_frame */
					   0, /* iso_number_packets */
					   शून्य, /* iso_packets */
					   urb);
पूर्ण

/**
 * Call to submit a USB Isochronous transfer to a pipe.
 *
 * @usb:	    USB device state populated by cvmx_usb_initialize().
 * @pipe:	    Handle to the pipe क्रम the transfer.
 * @urb:	    URB वापसed when the callback is called.
 *
 * Returns: A submitted transaction or शून्य on failure.
 */
अटल काष्ठा cvmx_usb_transaction *cvmx_usb_submit_isochronous(
						काष्ठा octeon_hcd *usb,
						काष्ठा cvmx_usb_pipe *pipe,
						काष्ठा urb *urb)
अणु
	काष्ठा cvmx_usb_iso_packet *packets;

	packets = (काष्ठा cvmx_usb_iso_packet *)urb->setup_packet;
	वापस cvmx_usb_submit_transaction(usb, pipe,
					   CVMX_USB_TRANSFER_ISOCHRONOUS,
					   urb->transfer_dma,
					   urb->transfer_buffer_length,
					   0, /* control_header */
					   urb->start_frame,
					   urb->number_of_packets,
					   packets, urb);
पूर्ण

/**
 * Cancel one outstanding request in a pipe. Canceling a request
 * can fail अगर the transaction has alपढ़ोy completed beक्रमe cancel
 * is called. Even after a successful cancel call, it may take
 * a frame or two क्रम the cvmx_usb_poll() function to call the
 * associated callback.
 *
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @pipe:	 Pipe to cancel requests in.
 * @transaction: Transaction to cancel, वापसed by the submit function.
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_cancel(काष्ठा octeon_hcd *usb,
			   काष्ठा cvmx_usb_pipe *pipe,
			   काष्ठा cvmx_usb_transaction *transaction)
अणु
	/*
	 * If the transaction is the HEAD of the queue and scheduled. We need to
	 * treat it special
	 */
	अगर (list_first_entry(&pipe->transactions, typeof(*transaction), node) ==
	    transaction && (pipe->flags & CVMX_USB_PIPE_FLAGS_SCHEDULED)) अणु
		जोड़ cvmx_usbcx_hcअक्षरx usbc_hcअक्षर;

		usb->pipe_क्रम_channel[pipe->channel] = शून्य;
		pipe->flags &= ~CVMX_USB_PIPE_FLAGS_SCHEDULED;

		CVMX_SYNCW;

		usbc_hcअक्षर.u32 = cvmx_usb_पढ़ो_csr32(usb,
						      CVMX_USBCX_HCCHARX(pipe->channel,
									 usb->index));
		/*
		 * If the channel isn't enabled then the transaction alपढ़ोy
		 * completed.
		 */
		अगर (usbc_hcअक्षर.s.chena) अणु
			usbc_hcअक्षर.s.chdis = 1;
			cvmx_usb_ग_लिखो_csr32(usb,
					     CVMX_USBCX_HCCHARX(pipe->channel,
								usb->index),
					     usbc_hcअक्षर.u32);
		पूर्ण
	पूर्ण
	cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_CANCEL);
	वापस 0;
पूर्ण

/**
 * Cancel all outstanding requests in a pipe. Logically all this
 * करोes is call cvmx_usb_cancel() in a loop.
 *
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @pipe:	 Pipe to cancel requests in.
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_cancel_all(काष्ठा octeon_hcd *usb,
			       काष्ठा cvmx_usb_pipe *pipe)
अणु
	काष्ठा cvmx_usb_transaction *transaction, *next;

	/* Simply loop through and attempt to cancel each transaction */
	list_क्रम_each_entry_safe(transaction, next, &pipe->transactions, node) अणु
		पूर्णांक result = cvmx_usb_cancel(usb, pipe, transaction);

		अगर (unlikely(result != 0))
			वापस result;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Close a pipe created with cvmx_usb_खोलो_pipe().
 *
 * @usb:	 USB device state populated by cvmx_usb_initialize().
 * @pipe:	 Pipe to बंद.
 *
 * Returns: 0 or a negative error code. EBUSY is वापसed अगर the pipe has
 *	    outstanding transfers.
 */
अटल पूर्णांक cvmx_usb_बंद_pipe(काष्ठा octeon_hcd *usb,
			       काष्ठा cvmx_usb_pipe *pipe)
अणु
	/* Fail अगर the pipe has pending transactions */
	अगर (!list_empty(&pipe->transactions))
		वापस -EBUSY;

	list_del(&pipe->node);
	kमुक्त(pipe);

	वापस 0;
पूर्ण

/**
 * Get the current USB protocol level frame number. The frame
 * number is always in the range of 0-0x7ff.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 *
 * Returns: USB frame number
 */
अटल पूर्णांक cvmx_usb_get_frame_number(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbcx_hfnum usbc_hfnum;

	usbc_hfnum.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HFNUM(usb->index));

	वापस usbc_hfnum.s.frnum;
पूर्ण

अटल व्योम cvmx_usb_transfer_control(काष्ठा octeon_hcd *usb,
				      काष्ठा cvmx_usb_pipe *pipe,
				      काष्ठा cvmx_usb_transaction *transaction,
				      जोड़ cvmx_usbcx_hcअक्षरx usbc_hcअक्षर,
				      पूर्णांक buffer_space_left,
				      पूर्णांक bytes_in_last_packet)
अणु
	चयन (transaction->stage) अणु
	हाल CVMX_USB_STAGE_NON_CONTROL:
	हाल CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE:
		/* This should be impossible */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_ERROR);
		अवरोध;
	हाल CVMX_USB_STAGE_SETUP:
		pipe->pid_toggle = 1;
		अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			transaction->stage =
				CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE;
		पूर्ण अन्यथा अणु
			काष्ठा usb_ctrlrequest *header =
				cvmx_phys_to_ptr(transaction->control_header);
			अगर (header->wLength)
				transaction->stage = CVMX_USB_STAGE_DATA;
			अन्यथा
				transaction->stage = CVMX_USB_STAGE_STATUS;
		पूर्ण
		अवरोध;
	हाल CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE:
		अणु
			काष्ठा usb_ctrlrequest *header =
				cvmx_phys_to_ptr(transaction->control_header);
			अगर (header->wLength)
				transaction->stage = CVMX_USB_STAGE_DATA;
			अन्यथा
				transaction->stage = CVMX_USB_STAGE_STATUS;
		पूर्ण
		अवरोध;
	हाल CVMX_USB_STAGE_DATA:
		अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			transaction->stage = CVMX_USB_STAGE_DATA_SPLIT_COMPLETE;
			/*
			 * For setup OUT data that are splits,
			 * the hardware करोesn't appear to count
			 * transferred data. Here we manually
			 * update the data transferred
			 */
			अगर (!usbc_hcअक्षर.s.epdir) अणु
				अगर (buffer_space_left < pipe->max_packet)
					transaction->actual_bytes +=
						buffer_space_left;
				अन्यथा
					transaction->actual_bytes +=
						pipe->max_packet;
			पूर्ण
		पूर्ण अन्यथा अगर ((buffer_space_left == 0) ||
			   (bytes_in_last_packet < pipe->max_packet)) अणु
			pipe->pid_toggle = 1;
			transaction->stage = CVMX_USB_STAGE_STATUS;
		पूर्ण
		अवरोध;
	हाल CVMX_USB_STAGE_DATA_SPLIT_COMPLETE:
		अगर ((buffer_space_left == 0) ||
		    (bytes_in_last_packet < pipe->max_packet)) अणु
			pipe->pid_toggle = 1;
			transaction->stage = CVMX_USB_STAGE_STATUS;
		पूर्ण अन्यथा अणु
			transaction->stage = CVMX_USB_STAGE_DATA;
		पूर्ण
		अवरोध;
	हाल CVMX_USB_STAGE_STATUS:
		अगर (cvmx_usb_pipe_needs_split(usb, pipe))
			transaction->stage =
				CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE;
		अन्यथा
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
		अवरोध;
	हाल CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE:
		cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_OK);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cvmx_usb_transfer_bulk(काष्ठा octeon_hcd *usb,
				   काष्ठा cvmx_usb_pipe *pipe,
				   काष्ठा cvmx_usb_transaction *transaction,
				   जोड़ cvmx_usbcx_hcपूर्णांकx usbc_hcपूर्णांक,
				   पूर्णांक buffer_space_left,
				   पूर्णांक bytes_in_last_packet)
अणु
	/*
	 * The only समय a bulk transfer isn't complete when it finishes with
	 * an ACK is during a split transaction. For splits we need to जारी
	 * the transfer अगर more data is needed.
	 */
	अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
		अगर (transaction->stage == CVMX_USB_STAGE_NON_CONTROL)
			transaction->stage =
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE;
		अन्यथा अगर (buffer_space_left &&
			 (bytes_in_last_packet == pipe->max_packet))
			transaction->stage = CVMX_USB_STAGE_NON_CONTROL;
		अन्यथा
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
	पूर्ण अन्यथा अणु
		अगर ((pipe->device_speed == CVMX_USB_SPEED_HIGH) &&
		    (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT) &&
		    (usbc_hcपूर्णांक.s.nak))
			pipe->flags |= CVMX_USB_PIPE_FLAGS_NEED_PING;
		अगर (!buffer_space_left ||
		    (bytes_in_last_packet < pipe->max_packet))
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
	पूर्ण
पूर्ण

अटल व्योम cvmx_usb_transfer_पूर्णांकr(काष्ठा octeon_hcd *usb,
				   काष्ठा cvmx_usb_pipe *pipe,
				   काष्ठा cvmx_usb_transaction *transaction,
				   पूर्णांक buffer_space_left,
				   पूर्णांक bytes_in_last_packet)
अणु
	अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
		अगर (transaction->stage == CVMX_USB_STAGE_NON_CONTROL) अणु
			transaction->stage =
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE;
		पूर्ण अन्यथा अगर (buffer_space_left &&
			   (bytes_in_last_packet == pipe->max_packet)) अणु
			transaction->stage = CVMX_USB_STAGE_NON_CONTROL;
		पूर्ण अन्यथा अणु
			pipe->next_tx_frame += pipe->पूर्णांकerval;
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
		पूर्ण
	पूर्ण अन्यथा अगर (!buffer_space_left ||
		   (bytes_in_last_packet < pipe->max_packet)) अणु
		pipe->next_tx_frame += pipe->पूर्णांकerval;
		cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_OK);
	पूर्ण
पूर्ण

अटल व्योम cvmx_usb_transfer_isoc(काष्ठा octeon_hcd *usb,
				   काष्ठा cvmx_usb_pipe *pipe,
				   काष्ठा cvmx_usb_transaction *transaction,
				   पूर्णांक buffer_space_left,
				   पूर्णांक bytes_in_last_packet,
				   पूर्णांक bytes_this_transfer)
अणु
	अगर (cvmx_usb_pipe_needs_split(usb, pipe)) अणु
		/*
		 * ISOCHRONOUS OUT splits करोn't require a complete split stage.
		 * Instead they use a sequence of begin OUT splits to transfer
		 * the data 188 bytes at a समय. Once the transfer is complete,
		 * the pipe sleeps until the next schedule पूर्णांकerval.
		 */
		अगर (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT) अणु
			/*
			 * If no space left or this wasn't a max size packet
			 * then this transfer is complete. Otherwise start it
			 * again to send the next 188 bytes
			 */
			अगर (!buffer_space_left || (bytes_this_transfer < 188)) अणु
				pipe->next_tx_frame += pipe->पूर्णांकerval;
				cvmx_usb_complete(usb, pipe, transaction,
						  CVMX_USB_STATUS_OK);
			पूर्ण
			वापस;
		पूर्ण
		अगर (transaction->stage ==
		    CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE) अणु
			/*
			 * We are in the incoming data phase. Keep getting data
			 * until we run out of space or get a small packet
			 */
			अगर ((buffer_space_left == 0) ||
			    (bytes_in_last_packet < pipe->max_packet)) अणु
				pipe->next_tx_frame += pipe->पूर्णांकerval;
				cvmx_usb_complete(usb, pipe, transaction,
						  CVMX_USB_STATUS_OK);
			पूर्ण
		पूर्ण अन्यथा अणु
			transaction->stage =
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE;
		पूर्ण
	पूर्ण अन्यथा अणु
		pipe->next_tx_frame += pipe->पूर्णांकerval;
		cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_OK);
	पूर्ण
पूर्ण

/**
 * Poll a channel क्रम status
 *
 * @usb:     USB device
 * @channel: Channel to poll
 *
 * Returns: Zero on success
 */
अटल पूर्णांक cvmx_usb_poll_channel(काष्ठा octeon_hcd *usb, पूर्णांक channel)
अणु
	काष्ठा usb_hcd *hcd = octeon_to_hcd(usb);
	काष्ठा device *dev = hcd->self.controller;
	जोड़ cvmx_usbcx_hcपूर्णांकx usbc_hcपूर्णांक;
	जोड़ cvmx_usbcx_hctsizx usbc_hctsiz;
	जोड़ cvmx_usbcx_hcअक्षरx usbc_hcअक्षर;
	काष्ठा cvmx_usb_pipe *pipe;
	काष्ठा cvmx_usb_transaction *transaction;
	पूर्णांक bytes_this_transfer;
	पूर्णांक bytes_in_last_packet;
	पूर्णांक packets_processed;
	पूर्णांक buffer_space_left;

	/* Read the पूर्णांकerrupt status bits क्रम the channel */
	usbc_hcपूर्णांक.u32 = cvmx_usb_पढ़ो_csr32(usb,
					     CVMX_USBCX_HCINTX(channel, usb->index));

	अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA) अणु
		usbc_hcअक्षर.u32 = cvmx_usb_पढ़ो_csr32(usb,
						      CVMX_USBCX_HCCHARX(channel,
									 usb->index));

		अगर (usbc_hcअक्षर.s.chena && usbc_hcअक्षर.s.chdis) अणु
			/*
			 * There seems to be a bug in CN31XX which can cause
			 * पूर्णांकerrupt IN transfers to get stuck until we करो a
			 * ग_लिखो of HCCHARX without changing things
			 */
			cvmx_usb_ग_लिखो_csr32(usb,
					     CVMX_USBCX_HCCHARX(channel,
								usb->index),
					     usbc_hcअक्षर.u32);
			वापस 0;
		पूर्ण

		/*
		 * In non DMA mode the channels करोn't halt themselves. We need
		 * to manually disable channels that are left running
		 */
		अगर (!usbc_hcपूर्णांक.s.chhltd) अणु
			अगर (usbc_hcअक्षर.s.chena) अणु
				जोड़ cvmx_usbcx_hcपूर्णांकmskx hcपूर्णांकmsk;
				/* Disable all पूर्णांकerrupts except CHHLTD */
				hcपूर्णांकmsk.u32 = 0;
				hcपूर्णांकmsk.s.chhltdmsk = 1;
				cvmx_usb_ग_लिखो_csr32(usb,
						     CVMX_USBCX_HCINTMSKX(channel, usb->index),
						     hcपूर्णांकmsk.u32);
				usbc_hcअक्षर.s.chdis = 1;
				cvmx_usb_ग_लिखो_csr32(usb,
						     CVMX_USBCX_HCCHARX(channel, usb->index),
						     usbc_hcअक्षर.u32);
				वापस 0;
			पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.xfercompl) अणु
				/*
				 * Successful IN/OUT with transfer complete.
				 * Channel halt isn't needed.
				 */
			पूर्ण अन्यथा अणु
				dev_err(dev, "USB%d: Channel %d interrupt without halt\n",
					usb->index, channel);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * There is are no पूर्णांकerrupts that we need to process when the
		 * channel is still running
		 */
		अगर (!usbc_hcपूर्णांक.s.chhltd)
			वापस 0;
	पूर्ण

	/* Disable the channel पूर्णांकerrupts now that it is करोne */
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HCINTMSKX(channel, usb->index), 0);
	usb->idle_hardware_channels |= (1 << channel);

	/* Make sure this channel is tied to a valid pipe */
	pipe = usb->pipe_क्रम_channel[channel];
	prefetch(pipe);
	अगर (!pipe)
		वापस 0;
	transaction = list_first_entry(&pipe->transactions,
				       typeof(*transaction),
				       node);
	prefetch(transaction);

	/*
	 * Disconnect this pipe from the HW channel. Later the schedule
	 * function will figure out which pipe needs to go
	 */
	usb->pipe_क्रम_channel[channel] = शून्य;
	pipe->flags &= ~CVMX_USB_PIPE_FLAGS_SCHEDULED;

	/*
	 * Read the channel config info so we can figure out how much data
	 * transferred
	 */
	usbc_hcअक्षर.u32 = cvmx_usb_पढ़ो_csr32(usb,
					      CVMX_USBCX_HCCHARX(channel, usb->index));
	usbc_hctsiz.u32 = cvmx_usb_पढ़ो_csr32(usb,
					      CVMX_USBCX_HCTSIZX(channel, usb->index));

	/*
	 * Calculating the number of bytes successfully transferred is dependent
	 * on the transfer direction
	 */
	packets_processed = transaction->pktcnt - usbc_hctsiz.s.pktcnt;
	अगर (usbc_hcअक्षर.s.epdir) अणु
		/*
		 * IN transactions are easy. For every byte received the
		 * hardware decrements xfersize. All we need to करो is subtract
		 * the current value of xfersize from its starting value and we
		 * know how many bytes were written to the buffer
		 */
		bytes_this_transfer = transaction->xfersize -
			usbc_hctsiz.s.xfersize;
	पूर्ण अन्यथा अणु
		/*
		 * OUT transaction करोn't decrement xfersize. Instead pktcnt is
		 * decremented on every successful packet send. The hardware
		 * करोes this when it receives an ACK, or NYET. If it करोesn't
		 * receive one of these responses pktcnt करोesn't change
		 */
		bytes_this_transfer = packets_processed * usbc_hcअक्षर.s.mps;
		/*
		 * The last packet may not be a full transfer अगर we didn't have
		 * enough data
		 */
		अगर (bytes_this_transfer > transaction->xfersize)
			bytes_this_transfer = transaction->xfersize;
	पूर्ण
	/* Figure out how many bytes were in the last packet of the transfer */
	अगर (packets_processed)
		bytes_in_last_packet = bytes_this_transfer -
			(packets_processed - 1) * usbc_hcअक्षर.s.mps;
	अन्यथा
		bytes_in_last_packet = bytes_this_transfer;

	/*
	 * As a special हाल, setup transactions output the setup header, not
	 * the user's data. For this reason we don't count setup data as bytes
	 * transferred
	 */
	अगर ((transaction->stage == CVMX_USB_STAGE_SETUP) ||
	    (transaction->stage == CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE))
		bytes_this_transfer = 0;

	/*
	 * Add the bytes transferred to the running total. It is important that
	 * bytes_this_transfer करोesn't count any data that needs to be
	 * retransmitted
	 */
	transaction->actual_bytes += bytes_this_transfer;
	अगर (transaction->type == CVMX_USB_TRANSFER_ISOCHRONOUS)
		buffer_space_left = transaction->iso_packets[0].length -
			transaction->actual_bytes;
	अन्यथा
		buffer_space_left = transaction->buffer_length -
			transaction->actual_bytes;

	/*
	 * We need to remember the PID toggle state क्रम the next transaction.
	 * The hardware alपढ़ोy updated it क्रम the next transaction
	 */
	pipe->pid_toggle = !(usbc_hctsiz.s.pid == 0);

	/*
	 * For high speed bulk out, assume the next transaction will need to करो
	 * a ping beक्रमe proceeding. If this isn't true the ACK processing below
	 * will clear this flag
	 */
	अगर ((pipe->device_speed == CVMX_USB_SPEED_HIGH) &&
	    (pipe->transfer_type == CVMX_USB_TRANSFER_BULK) &&
	    (pipe->transfer_dir == CVMX_USB_सूचीECTION_OUT))
		pipe->flags |= CVMX_USB_PIPE_FLAGS_NEED_PING;

	अगर (WARN_ON_ONCE(bytes_this_transfer < 0)) अणु
		/*
		 * In some rare हालs the DMA engine seems to get stuck and
		 * keeps substracting same byte count over and over again. In
		 * such हाल we just need to fail every transaction.
		 */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_ERROR);
		वापस 0;
	पूर्ण

	अगर (usbc_hcपूर्णांक.s.stall) अणु
		/*
		 * STALL as a response means this transaction cannot be
		 * completed because the device can't process transactions. Tell
		 * the user. Any data that was transferred will be counted on
		 * the actual bytes transferred
		 */
		pipe->pid_toggle = 0;
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_STALL);
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.xacterr) अणु
		/*
		 * XactErr as a response means the device संकेतed
		 * something wrong with the transfer. For example, PID
		 * toggle errors cause these.
		 */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_XACTERR);
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.bblerr) अणु
		/* Babble Error (BblErr) */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_BABBLEERR);
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.datatglerr) अणु
		/* Data toggle error */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_DATATGLERR);
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.nyet) अणु
		/*
		 * NYET as a response is only allowed in three हालs: as a
		 * response to a ping, as a response to a split transaction, and
		 * as a response to a bulk out. The ping हाल is handled by
		 * hardware, so we only have splits and bulk out
		 */
		अगर (!cvmx_usb_pipe_needs_split(usb, pipe)) अणु
			transaction->retries = 0;
			/*
			 * If there is more data to go then we need to try
			 * again. Otherwise this transaction is complete
			 */
			अगर ((buffer_space_left == 0) ||
			    (bytes_in_last_packet < pipe->max_packet))
				cvmx_usb_complete(usb, pipe,
						  transaction,
						  CVMX_USB_STATUS_OK);
		पूर्ण अन्यथा अणु
			/*
			 * Split transactions retry the split complete 4 बार
			 * then शुरुआत to the start split and करो the entire
			 * transactions again
			 */
			transaction->retries++;
			अगर ((transaction->retries & 0x3) == 0) अणु
				/*
				 * Rewind to the beginning of the transaction by
				 * anding off the split complete bit
				 */
				transaction->stage &= ~1;
				pipe->split_sc_frame = -1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.ack) अणु
		transaction->retries = 0;
		/*
		 * The ACK bit can only be checked after the other error bits.
		 * This is because a multi packet transfer may succeed in a
		 * number of packets and then get a dअगरferent response on the
		 * last packet. In this हाल both ACK and the last response bit
		 * will be set. If none of the other response bits is set, then
		 * the last packet must have been an ACK
		 *
		 * Since we got an ACK, we know we करोn't need to करो a ping on
		 * this pipe
		 */
		pipe->flags &= ~CVMX_USB_PIPE_FLAGS_NEED_PING;

		चयन (transaction->type) अणु
		हाल CVMX_USB_TRANSFER_CONTROL:
			cvmx_usb_transfer_control(usb, pipe, transaction,
						  usbc_hcअक्षर,
						  buffer_space_left,
						  bytes_in_last_packet);
			अवरोध;
		हाल CVMX_USB_TRANSFER_BULK:
			cvmx_usb_transfer_bulk(usb, pipe, transaction,
					       usbc_hcपूर्णांक, buffer_space_left,
					       bytes_in_last_packet);
			अवरोध;
		हाल CVMX_USB_TRANSFER_INTERRUPT:
			cvmx_usb_transfer_पूर्णांकr(usb, pipe, transaction,
					       buffer_space_left,
					       bytes_in_last_packet);
			अवरोध;
		हाल CVMX_USB_TRANSFER_ISOCHRONOUS:
			cvmx_usb_transfer_isoc(usb, pipe, transaction,
					       buffer_space_left,
					       bytes_in_last_packet,
					       bytes_this_transfer);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (usbc_hcपूर्णांक.s.nak) अणु
		/*
		 * If this was a split then clear our split in progress marker.
		 */
		अगर (usb->active_split == transaction)
			usb->active_split = शून्य;
		/*
		 * NAK as a response means the device couldn't accept the
		 * transaction, but it should be retried in the future. Rewind
		 * to the beginning of the transaction by anding off the split
		 * complete bit. Retry in the next पूर्णांकerval
		 */
		transaction->retries = 0;
		transaction->stage &= ~1;
		pipe->next_tx_frame += pipe->पूर्णांकerval;
		अगर (pipe->next_tx_frame < usb->frame_number)
			pipe->next_tx_frame = usb->frame_number +
				pipe->पूर्णांकerval -
				(usb->frame_number - pipe->next_tx_frame) %
				pipe->पूर्णांकerval;
	पूर्ण अन्यथा अणु
		काष्ठा cvmx_usb_port_status port;

		port = cvmx_usb_get_status(usb);
		अगर (port.port_enabled) अणु
			/* We'll retry the exact same transaction again */
			transaction->retries++;
		पूर्ण अन्यथा अणु
			/*
			 * We get channel halted पूर्णांकerrupts with no result bits
			 * sets when the cable is unplugged
			 */
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_ERROR);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम octeon_usb_port_callback(काष्ठा octeon_hcd *usb)
अणु
	spin_unlock(&usb->lock);
	usb_hcd_poll_rh_status(octeon_to_hcd(usb));
	spin_lock(&usb->lock);
पूर्ण

/**
 * Poll the USB block क्रम status and call all needed callback
 * handlers. This function is meant to be called in the पूर्णांकerrupt
 * handler क्रम the USB controller. It can also be called
 * periodically in a loop क्रम non-पूर्णांकerrupt based operation.
 *
 * @usb: USB device state populated by cvmx_usb_initialize().
 *
 * Returns: 0 or a negative error code.
 */
अटल पूर्णांक cvmx_usb_poll(काष्ठा octeon_hcd *usb)
अणु
	जोड़ cvmx_usbcx_hfnum usbc_hfnum;
	जोड़ cvmx_usbcx_gपूर्णांकsts usbc_gपूर्णांकsts;

	prefetch_range(usb, माप(*usb));

	/* Update the frame counter */
	usbc_hfnum.u32 = cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HFNUM(usb->index));
	अगर ((usb->frame_number & 0x3fff) > usbc_hfnum.s.frnum)
		usb->frame_number += 0x4000;
	usb->frame_number &= ~0x3fffull;
	usb->frame_number |= usbc_hfnum.s.frnum;

	/* Read the pending पूर्णांकerrupts */
	usbc_gपूर्णांकsts.u32 = cvmx_usb_पढ़ो_csr32(usb,
					       CVMX_USBCX_GINTSTS(usb->index));

	/* Clear the पूर्णांकerrupts now that we know about them */
	cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_GINTSTS(usb->index),
			     usbc_gपूर्णांकsts.u32);

	अगर (usbc_gपूर्णांकsts.s.rxflvl) अणु
		/*
		 * RxFIFO Non-Empty (RxFLvl)
		 * Indicates that there is at least one packet pending to be
		 * पढ़ो from the RxFIFO.
		 *
		 * In DMA mode this is handled by hardware
		 */
		अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
			cvmx_usb_poll_rx_fअगरo(usb);
	पूर्ण
	अगर (usbc_gपूर्णांकsts.s.ptxfemp || usbc_gपूर्णांकsts.s.nptxfemp) अणु
		/* Fill the Tx FIFOs when not in DMA mode */
		अगर (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
			cvmx_usb_poll_tx_fअगरo(usb);
	पूर्ण
	अगर (usbc_gपूर्णांकsts.s.disconnपूर्णांक || usbc_gपूर्णांकsts.s.prtपूर्णांक) अणु
		जोड़ cvmx_usbcx_hprt usbc_hprt;
		/*
		 * Disconnect Detected Interrupt (DisconnInt)
		 * Asserted when a device disconnect is detected.
		 *
		 * Host Port Interrupt (PrtInt)
		 * The core sets this bit to indicate a change in port status of
		 * one of the O2P USB core ports in Host mode. The application
		 * must पढ़ो the Host Port Control and Status (HPRT) रेजिस्टर to
		 * determine the exact event that caused this पूर्णांकerrupt. The
		 * application must clear the appropriate status bit in the Host
		 * Port Control and Status रेजिस्टर to clear this bit.
		 *
		 * Call the user's port callback
		 */
		octeon_usb_port_callback(usb);
		/* Clear the port change bits */
		usbc_hprt.u32 =
			cvmx_usb_पढ़ो_csr32(usb, CVMX_USBCX_HPRT(usb->index));
		usbc_hprt.s.prtena = 0;
		cvmx_usb_ग_लिखो_csr32(usb, CVMX_USBCX_HPRT(usb->index),
				     usbc_hprt.u32);
	पूर्ण
	अगर (usbc_gपूर्णांकsts.s.hchपूर्णांक) अणु
		/*
		 * Host Channels Interrupt (HChInt)
		 * The core sets this bit to indicate that an पूर्णांकerrupt is
		 * pending on one of the channels of the core (in Host mode).
		 * The application must पढ़ो the Host All Channels Interrupt
		 * (HAINT) रेजिस्टर to determine the exact number of the channel
		 * on which the पूर्णांकerrupt occurred, and then पढ़ो the
		 * corresponding Host Channel-n Interrupt (HCINTn) रेजिस्टर to
		 * determine the exact cause of the पूर्णांकerrupt. The application
		 * must clear the appropriate status bit in the HCINTn रेजिस्टर
		 * to clear this bit.
		 */
		जोड़ cvmx_usbcx_haपूर्णांक usbc_haपूर्णांक;

		usbc_haपूर्णांक.u32 = cvmx_usb_पढ़ो_csr32(usb,
						     CVMX_USBCX_HAINT(usb->index));
		जबतक (usbc_haपूर्णांक.u32) अणु
			पूर्णांक channel;

			channel = __fls(usbc_haपूर्णांक.u32);
			cvmx_usb_poll_channel(usb, channel);
			usbc_haपूर्णांक.u32 ^= 1 << channel;
		पूर्ण
	पूर्ण

	cvmx_usb_schedule(usb, usbc_gपूर्णांकsts.s.sof);

	वापस 0;
पूर्ण

/* convert between an HCD poपूर्णांकer and the corresponding काष्ठा octeon_hcd */
अटल अंतरभूत काष्ठा octeon_hcd *hcd_to_octeon(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा octeon_hcd *)(hcd->hcd_priv);
पूर्ण

अटल irqवापस_t octeon_usb_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb->lock, flags);
	cvmx_usb_poll(usb);
	spin_unlock_irqrestore(&usb->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक octeon_usb_start(काष्ठा usb_hcd *hcd)
अणु
	hcd->state = HC_STATE_RUNNING;
	वापस 0;
पूर्ण

अटल व्योम octeon_usb_stop(काष्ठा usb_hcd *hcd)
अणु
	hcd->state = HC_STATE_HALT;
पूर्ण

अटल पूर्णांक octeon_usb_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);

	वापस cvmx_usb_get_frame_number(usb);
पूर्ण

अटल पूर्णांक octeon_usb_urb_enqueue(काष्ठा usb_hcd *hcd,
				  काष्ठा urb *urb,
				  gfp_t mem_flags)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा cvmx_usb_transaction *transaction = शून्य;
	काष्ठा cvmx_usb_pipe *pipe;
	अचिन्हित दीर्घ flags;
	काष्ठा cvmx_usb_iso_packet *iso_packet;
	काष्ठा usb_host_endpoपूर्णांक *ep = urb->ep;
	पूर्णांक rc;

	urb->status = 0;
	spin_lock_irqsave(&usb->lock, flags);

	rc = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (rc) अणु
		spin_unlock_irqrestore(&usb->lock, flags);
		वापस rc;
	पूर्ण

	अगर (!ep->hcpriv) अणु
		क्रमागत cvmx_usb_transfer transfer_type;
		क्रमागत cvmx_usb_speed speed;
		पूर्णांक split_device = 0;
		पूर्णांक split_port = 0;

		चयन (usb_pipetype(urb->pipe)) अणु
		हाल PIPE_ISOCHRONOUS:
			transfer_type = CVMX_USB_TRANSFER_ISOCHRONOUS;
			अवरोध;
		हाल PIPE_INTERRUPT:
			transfer_type = CVMX_USB_TRANSFER_INTERRUPT;
			अवरोध;
		हाल PIPE_CONTROL:
			transfer_type = CVMX_USB_TRANSFER_CONTROL;
			अवरोध;
		शेष:
			transfer_type = CVMX_USB_TRANSFER_BULK;
			अवरोध;
		पूर्ण
		चयन (urb->dev->speed) अणु
		हाल USB_SPEED_LOW:
			speed = CVMX_USB_SPEED_LOW;
			अवरोध;
		हाल USB_SPEED_FULL:
			speed = CVMX_USB_SPEED_FULL;
			अवरोध;
		शेष:
			speed = CVMX_USB_SPEED_HIGH;
			अवरोध;
		पूर्ण
		/*
		 * For slow devices on high speed ports we need to find the hub
		 * that करोes the speed translation so we know where to send the
		 * split transactions.
		 */
		अगर (speed != CVMX_USB_SPEED_HIGH) अणु
			/*
			 * Start at this device and work our way up the usb
			 * tree.
			 */
			काष्ठा usb_device *dev = urb->dev;

			जबतक (dev->parent) अणु
				/*
				 * If our parent is high speed then he'll
				 * receive the splits.
				 */
				अगर (dev->parent->speed == USB_SPEED_HIGH) अणु
					split_device = dev->parent->devnum;
					split_port = dev->portnum;
					अवरोध;
				पूर्ण
				/*
				 * Move up the tree one level. If we make it all
				 * the way up the tree, then the port must not
				 * be in high speed mode and we करोn't need a
				 * split.
				 */
				dev = dev->parent;
			पूर्ण
		पूर्ण
		pipe = cvmx_usb_खोलो_pipe(usb, usb_pipedevice(urb->pipe),
					  usb_pipeendpoपूर्णांक(urb->pipe), speed,
					  le16_to_cpu(ep->desc.wMaxPacketSize)
					  & 0x7ff,
					  transfer_type,
					  usb_pipein(urb->pipe) ?
						CVMX_USB_सूचीECTION_IN :
						CVMX_USB_सूचीECTION_OUT,
					  urb->पूर्णांकerval,
					  (le16_to_cpu(ep->desc.wMaxPacketSize)
					   >> 11) & 0x3,
					  split_device, split_port);
		अगर (!pipe) अणु
			usb_hcd_unlink_urb_from_ep(hcd, urb);
			spin_unlock_irqrestore(&usb->lock, flags);
			dev_dbg(dev, "Failed to create pipe\n");
			वापस -ENOMEM;
		पूर्ण
		ep->hcpriv = pipe;
	पूर्ण अन्यथा अणु
		pipe = ep->hcpriv;
	पूर्ण

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_ISOCHRONOUS:
		dev_dbg(dev, "Submit isochronous to %d.%d\n",
			usb_pipedevice(urb->pipe),
			usb_pipeendpoपूर्णांक(urb->pipe));
		/*
		 * Allocate a काष्ठाure to use क्रम our निजी list of
		 * isochronous packets.
		 */
		iso_packet = kदो_स्मृति_array(urb->number_of_packets,
					   माप(काष्ठा cvmx_usb_iso_packet),
					   GFP_ATOMIC);
		अगर (iso_packet) अणु
			पूर्णांक i;
			/* Fill the list with the data from the URB */
			क्रम (i = 0; i < urb->number_of_packets; i++) अणु
				iso_packet[i].offset =
					urb->iso_frame_desc[i].offset;
				iso_packet[i].length =
					urb->iso_frame_desc[i].length;
				iso_packet[i].status = CVMX_USB_STATUS_ERROR;
			पूर्ण
			/*
			 * Store a poपूर्णांकer to the list in the URB setup_packet
			 * field. We know this currently isn't being used and
			 * this saves us a bunch of logic.
			 */
			urb->setup_packet = (अक्षर *)iso_packet;
			transaction = cvmx_usb_submit_isochronous(usb,
								  pipe, urb);
			/*
			 * If submit failed we need to मुक्त our निजी packet
			 * list.
			 */
			अगर (!transaction) अणु
				urb->setup_packet = शून्य;
				kमुक्त(iso_packet);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PIPE_INTERRUPT:
		dev_dbg(dev, "Submit interrupt to %d.%d\n",
			usb_pipedevice(urb->pipe),
			usb_pipeendpoपूर्णांक(urb->pipe));
		transaction = cvmx_usb_submit_पूर्णांकerrupt(usb, pipe, urb);
		अवरोध;
	हाल PIPE_CONTROL:
		dev_dbg(dev, "Submit control to %d.%d\n",
			usb_pipedevice(urb->pipe),
			usb_pipeendpoपूर्णांक(urb->pipe));
		transaction = cvmx_usb_submit_control(usb, pipe, urb);
		अवरोध;
	हाल PIPE_BULK:
		dev_dbg(dev, "Submit bulk to %d.%d\n",
			usb_pipedevice(urb->pipe),
			usb_pipeendpoपूर्णांक(urb->pipe));
		transaction = cvmx_usb_submit_bulk(usb, pipe, urb);
		अवरोध;
	पूर्ण
	अगर (!transaction) अणु
		usb_hcd_unlink_urb_from_ep(hcd, urb);
		spin_unlock_irqrestore(&usb->lock, flags);
		dev_dbg(dev, "Failed to submit\n");
		वापस -ENOMEM;
	पूर्ण
	urb->hcpriv = transaction;
	spin_unlock_irqrestore(&usb->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_usb_urb_dequeue(काष्ठा usb_hcd *hcd,
				  काष्ठा urb *urb,
				  पूर्णांक status)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!urb->dev)
		वापस -EINVAL;

	spin_lock_irqsave(&usb->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ out;

	urb->status = status;
	cvmx_usb_cancel(usb, urb->ep->hcpriv, urb->hcpriv);

out:
	spin_unlock_irqrestore(&usb->lock, flags);

	वापस rc;
पूर्ण

अटल व्योम octeon_usb_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
					काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा device *dev = hcd->self.controller;

	अगर (ep->hcpriv) अणु
		काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
		काष्ठा cvmx_usb_pipe *pipe = ep->hcpriv;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&usb->lock, flags);
		cvmx_usb_cancel_all(usb, pipe);
		अगर (cvmx_usb_बंद_pipe(usb, pipe))
			dev_dbg(dev, "Closing pipe %p failed\n", pipe);
		spin_unlock_irqrestore(&usb->lock, flags);
		ep->hcpriv = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_usb_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	काष्ठा cvmx_usb_port_status port_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb->lock, flags);
	port_status = cvmx_usb_get_status(usb);
	spin_unlock_irqrestore(&usb->lock, flags);
	buf[0] = port_status.connect_change << 1;

	वापस buf[0] != 0;
पूर्ण

अटल पूर्णांक octeon_usb_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
				  u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा cvmx_usb_port_status usb_port_status;
	पूर्णांक port_status;
	काष्ठा usb_hub_descriptor *desc;
	अचिन्हित दीर्घ flags;

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		dev_dbg(dev, "ClearHubFeature\n");
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* Nothing required here */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		dev_dbg(dev, "ClearPortFeature\n");
		अगर (wIndex != 1) अणु
			dev_dbg(dev, " INVALID\n");
			वापस -EINVAL;
		पूर्ण

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			dev_dbg(dev, " ENABLE\n");
			spin_lock_irqsave(&usb->lock, flags);
			cvmx_usb_disable(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(dev, " SUSPEND\n");
			/* Not supported on Octeon */
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(dev, " POWER\n");
			/* Not supported on Octeon */
			अवरोध;
		हाल USB_PORT_FEAT_INDICATOR:
			dev_dbg(dev, " INDICATOR\n");
			/* Port inidicator not supported */
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			dev_dbg(dev, " C_CONNECTION\n");
			/* Clears drivers पूर्णांकernal connect status change flag */
			spin_lock_irqsave(&usb->lock, flags);
			usb->port_status = cvmx_usb_get_status(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			dev_dbg(dev, " C_RESET\n");
			/*
			 * Clears the driver's पूर्णांकernal Port Reset Change flag.
			 */
			spin_lock_irqsave(&usb->lock, flags);
			usb->port_status = cvmx_usb_get_status(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			dev_dbg(dev, " C_ENABLE\n");
			/*
			 * Clears the driver's पूर्णांकernal Port Enable/Disable
			 * Change flag.
			 */
			spin_lock_irqsave(&usb->lock, flags);
			usb->port_status = cvmx_usb_get_status(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			dev_dbg(dev, " C_SUSPEND\n");
			/*
			 * Clears the driver's पूर्णांकernal Port Suspend Change
			 * flag, which is set when resume संकेतing on the host
			 * port is complete.
			 */
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(dev, " C_OVER_CURRENT\n");
			/* Clears the driver's overcurrent Change flag */
			spin_lock_irqsave(&usb->lock, flags);
			usb->port_status = cvmx_usb_get_status(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			अवरोध;
		शेष:
			dev_dbg(dev, " UNKNOWN\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		dev_dbg(dev, "GetHubDescriptor\n");
		desc = (काष्ठा usb_hub_descriptor *)buf;
		desc->bDescLength = 9;
		desc->bDescriptorType = 0x29;
		desc->bNbrPorts = 1;
		desc->wHubCharacteristics = cpu_to_le16(0x08);
		desc->bPwrOn2PwrGood = 1;
		desc->bHubContrCurrent = 0;
		desc->u.hs.DeviceRemovable[0] = 0;
		desc->u.hs.DeviceRemovable[1] = 0xff;
		अवरोध;
	हाल GetHubStatus:
		dev_dbg(dev, "GetHubStatus\n");
		*(__le32 *)buf = 0;
		अवरोध;
	हाल GetPortStatus:
		dev_dbg(dev, "GetPortStatus\n");
		अगर (wIndex != 1) अणु
			dev_dbg(dev, " INVALID\n");
			वापस -EINVAL;
		पूर्ण

		spin_lock_irqsave(&usb->lock, flags);
		usb_port_status = cvmx_usb_get_status(usb);
		spin_unlock_irqrestore(&usb->lock, flags);
		port_status = 0;

		अगर (usb_port_status.connect_change) अणु
			port_status |= (1 << USB_PORT_FEAT_C_CONNECTION);
			dev_dbg(dev, " C_CONNECTION\n");
		पूर्ण

		अगर (usb_port_status.port_enabled) अणु
			port_status |= (1 << USB_PORT_FEAT_C_ENABLE);
			dev_dbg(dev, " C_ENABLE\n");
		पूर्ण

		अगर (usb_port_status.connected) अणु
			port_status |= (1 << USB_PORT_FEAT_CONNECTION);
			dev_dbg(dev, " CONNECTION\n");
		पूर्ण

		अगर (usb_port_status.port_enabled) अणु
			port_status |= (1 << USB_PORT_FEAT_ENABLE);
			dev_dbg(dev, " ENABLE\n");
		पूर्ण

		अगर (usb_port_status.port_over_current) अणु
			port_status |= (1 << USB_PORT_FEAT_OVER_CURRENT);
			dev_dbg(dev, " OVER_CURRENT\n");
		पूर्ण

		अगर (usb_port_status.port_घातered) अणु
			port_status |= (1 << USB_PORT_FEAT_POWER);
			dev_dbg(dev, " POWER\n");
		पूर्ण

		अगर (usb_port_status.port_speed == CVMX_USB_SPEED_HIGH) अणु
			port_status |= USB_PORT_STAT_HIGH_SPEED;
			dev_dbg(dev, " HIGHSPEED\n");
		पूर्ण अन्यथा अगर (usb_port_status.port_speed == CVMX_USB_SPEED_LOW) अणु
			port_status |= (1 << USB_PORT_FEAT_LOWSPEED);
			dev_dbg(dev, " LOWSPEED\n");
		पूर्ण

		*((__le32 *)buf) = cpu_to_le32(port_status);
		अवरोध;
	हाल SetHubFeature:
		dev_dbg(dev, "SetHubFeature\n");
		/* No HUB features supported */
		अवरोध;
	हाल SetPortFeature:
		dev_dbg(dev, "SetPortFeature\n");
		अगर (wIndex != 1) अणु
			dev_dbg(dev, " INVALID\n");
			वापस -EINVAL;
		पूर्ण

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(dev, " SUSPEND\n");
			वापस -EINVAL;
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(dev, " POWER\n");
			/*
			 * Program the port घातer bit to drive VBUS on the USB.
			 */
			spin_lock_irqsave(&usb->lock, flags);
			USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index),
					cvmx_usbcx_hprt, prtpwr, 1);
			spin_unlock_irqrestore(&usb->lock, flags);
			वापस 0;
		हाल USB_PORT_FEAT_RESET:
			dev_dbg(dev, " RESET\n");
			spin_lock_irqsave(&usb->lock, flags);
			cvmx_usb_reset_port(usb);
			spin_unlock_irqrestore(&usb->lock, flags);
			वापस 0;
		हाल USB_PORT_FEAT_INDICATOR:
			dev_dbg(dev, " INDICATOR\n");
			/* Not supported */
			अवरोध;
		शेष:
			dev_dbg(dev, " UNKNOWN\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown root hub request\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver octeon_hc_driver = अणु
	.description		= "Octeon USB",
	.product_desc		= "Octeon Host Controller",
	.hcd_priv_size		= माप(काष्ठा octeon_hcd),
	.irq			= octeon_usb_irq,
	.flags			= HCD_MEMORY | HCD_DMA | HCD_USB2,
	.start			= octeon_usb_start,
	.stop			= octeon_usb_stop,
	.urb_enqueue		= octeon_usb_urb_enqueue,
	.urb_dequeue		= octeon_usb_urb_dequeue,
	.endpoपूर्णांक_disable	= octeon_usb_endpoपूर्णांक_disable,
	.get_frame_number	= octeon_usb_get_frame_number,
	.hub_status_data	= octeon_usb_hub_status_data,
	.hub_control		= octeon_usb_hub_control,
	.map_urb_क्रम_dma	= octeon_map_urb_क्रम_dma,
	.unmap_urb_क्रम_dma	= octeon_unmap_urb_क्रम_dma,
पूर्ण;

अटल पूर्णांक octeon_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	पूर्णांक initialize_flags;
	पूर्णांक usb_num;
	काष्ठा resource *res_mem;
	काष्ठा device_node *usbn_node;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा octeon_hcd *usb;
	काष्ठा usb_hcd *hcd;
	u32 घड़ी_rate = 48000000;
	bool is_crystal_घड़ी = false;
	स्थिर अक्षर *घड़ी_प्रकारype;
	पूर्णांक i;

	अगर (!dev->of_node) अणु
		dev_err(dev, "Error: empty of_node\n");
		वापस -ENXIO;
	पूर्ण
	usbn_node = dev->of_node->parent;

	i = of_property_पढ़ो_u32(usbn_node,
				 "clock-frequency", &घड़ी_rate);
	अगर (i)
		i = of_property_पढ़ो_u32(usbn_node,
					 "refclk-frequency", &घड़ी_rate);
	अगर (i) अणु
		dev_err(dev, "No USBN \"clock-frequency\"\n");
		वापस -ENXIO;
	पूर्ण
	चयन (घड़ी_rate) अणु
	हाल 12000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ;
		अवरोध;
	हाल 24000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ;
		अवरोध;
	हाल 48000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ;
		अवरोध;
	शेष:
		dev_err(dev, "Illegal USBN \"clock-frequency\" %u\n",
			घड़ी_rate);
		वापस -ENXIO;
	पूर्ण

	i = of_property_पढ़ो_string(usbn_node,
				    "cavium,refclk-type", &घड़ी_प्रकारype);
	अगर (i)
		i = of_property_पढ़ो_string(usbn_node,
					    "refclk-type", &घड़ी_प्रकारype);

	अगर (!i && म_भेद("crystal", घड़ी_प्रकारype) == 0)
		is_crystal_घड़ी = true;

	अगर (is_crystal_घड़ी)
		initialize_flags |= CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_XI;
	अन्यथा
		initialize_flags |= CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem) अणु
		dev_err(dev, "found no memory resource\n");
		वापस -ENXIO;
	पूर्ण
	usb_num = (res_mem->start >> 44) & 1;

	अगर (irq < 0) अणु
		/* Defective device tree, but we know how to fix it. */
		irq_hw_number_t hwirq = usb_num ? (1 << 6) + 17 : 56;

		irq = irq_create_mapping(शून्य, hwirq);
	पूर्ण

	/*
	 * Set the DMA mask to 64bits so we get buffers alपढ़ोy translated क्रम
	 * DMA.
	 */
	i = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (i)
		वापस i;

	/*
	 * Only cn52XX and cn56XX have DWC_OTG USB hardware and the
	 * IOB priority रेजिस्टरs.  Under heavy network load USB
	 * hardware can be starved by the IOB causing a crash.  Give
	 * it a priority boost अगर it has been रुकोing more than 400
	 * cycles to aव्योम this situation.
	 *
	 * Testing indicates that a cnt_val of 8192 is not sufficient,
	 * but no failures are seen with 4096.  We choose a value of
	 * 400 to give a safety factor of 10.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX) || OCTEON_IS_MODEL(OCTEON_CN56XX)) अणु
		जोड़ cvmx_iob_n2c_l2c_pri_cnt pri_cnt;

		pri_cnt.u64 = 0;
		pri_cnt.s.cnt_enb = 1;
		pri_cnt.s.cnt_val = 400;
		cvmx_ग_लिखो_csr(CVMX_IOB_N2C_L2C_PRI_CNT, pri_cnt.u64);
	पूर्ण

	hcd = usb_create_hcd(&octeon_hc_driver, dev, dev_name(dev));
	अगर (!hcd) अणु
		dev_dbg(dev, "Failed to allocate memory for HCD\n");
		वापस -1;
	पूर्ण
	hcd->uses_new_polling = 1;
	usb = (काष्ठा octeon_hcd *)hcd->hcd_priv;

	spin_lock_init(&usb->lock);

	usb->init_flags = initialize_flags;

	/* Initialize the USB state काष्ठाure */
	usb->index = usb_num;
	INIT_LIST_HEAD(&usb->idle_pipes);
	क्रम (i = 0; i < ARRAY_SIZE(usb->active_pipes); i++)
		INIT_LIST_HEAD(&usb->active_pipes[i]);

	/* Due to an errata, CN31XX करोesn't support DMA */
	अगर (OCTEON_IS_MODEL(OCTEON_CN31XX)) अणु
		usb->init_flags |= CVMX_USB_INITIALIZE_FLAGS_NO_DMA;
		/* Only use one channel with non DMA */
		usb->idle_hardware_channels = 0x1;
	पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX)) अणु
		/* CN5XXX have an errata with channel 3 */
		usb->idle_hardware_channels = 0xf7;
	पूर्ण अन्यथा अणु
		usb->idle_hardware_channels = 0xff;
	पूर्ण

	status = cvmx_usb_initialize(dev, usb);
	अगर (status) अणु
		dev_dbg(dev, "USB initialization failed with %d\n", status);
		usb_put_hcd(hcd);
		वापस -1;
	पूर्ण

	status = usb_add_hcd(hcd, irq, 0);
	अगर (status) अणु
		dev_dbg(dev, "USB add HCD failed with %d\n", status);
		usb_put_hcd(hcd);
		वापस -1;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);

	dev_info(dev, "Registered HCD for port %d on irq %d\n", usb_num, irq);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा octeon_hcd *usb = hcd_to_octeon(hcd);
	अचिन्हित दीर्घ flags;

	usb_हटाओ_hcd(hcd);
	spin_lock_irqsave(&usb->lock, flags);
	status = cvmx_usb_shutकरोwn(usb);
	spin_unlock_irqrestore(&usb->lock, flags);
	अगर (status)
		dev_dbg(dev, "USB shutdown failed with %d\n", status);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_usb_match[] = अणु
	अणु
		.compatible = "cavium,octeon-5750-usbc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_usb_match);

अटल काष्ठा platक्रमm_driver octeon_usb_driver = अणु
	.driver = अणु
		.name		= "octeon-hcd",
		.of_match_table = octeon_usb_match,
	पूर्ण,
	.probe      = octeon_usb_probe,
	.हटाओ     = octeon_usb_हटाओ,
पूर्ण;

अटल पूर्णांक __init octeon_usb_driver_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस 0;

	वापस platक्रमm_driver_रेजिस्टर(&octeon_usb_driver);
पूर्ण
module_init(octeon_usb_driver_init);

अटल व्योम __निकास octeon_usb_driver_निकास(व्योम)
अणु
	अगर (usb_disabled())
		वापस;

	platक्रमm_driver_unरेजिस्टर(&octeon_usb_driver);
पूर्ण
module_निकास(octeon_usb_driver_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cavium, Inc. <support@cavium.com>");
MODULE_DESCRIPTION("Cavium Inc. OCTEON USB Host driver.");
