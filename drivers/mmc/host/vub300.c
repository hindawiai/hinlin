<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote VUB300 SDIO/SDmem Host Controller Driver
 *
 * Copyright (C) 2010 Elan Digital Systems Limited
 *
 * based on USB Skeleton driver - 2.2
 *
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * VUB300: is a USB 2.0 client device with a single SDIO/SDmem/MMC slot
 *         Any SDIO/SDmem/MMC device plugged पूर्णांकo the VUB300 will appear,
 *         by virtue of this driver, to have been plugged पूर्णांकo a local
 *         SDIO host controller, similar to, say, a PCI Ricoh controller
 *         This is because this kernel device driver is both a USB 2.0
 *         client device driver AND an MMC host controller driver. Thus
 *         अगर there is an existing driver क्रम the inserted SDIO/SDmem/MMC
 *         device then that driver will be used by the kernel to manage
 *         the device in exactly the same fashion as अगर it had been
 *         directly plugged पूर्णांकo, say, a local pci bus Ricoh controller
 *
 * RANT: this driver was written using a display 128x48 - converting it
 *       to a line width of 80 makes it very dअगरficult to support. In
 *       particular functions have been broken करोwn पूर्णांकo sub functions
 *       and the original meaningful names have been लघुened पूर्णांकo
 *       cryptic ones.
 *       The problem is that executing a fragment of code subject to
 *       two conditions means an indentation of 24, thus leaving only
 *       56 अक्षरacters क्रम a C statement. And that is quite ridiculous!
 *
 * Data types: data passed to/from the VUB300 is fixed to a number of
 *             bits and driver data fields reflect that limit by using
 *             u8, u16, u32
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/firmware.h>
#समावेश <linux/scatterlist.h>

काष्ठा host_controller_info अणु
	u8 info_size;
	u16 firmware_version;
	u8 number_of_ports;
पूर्ण __packed;

#घोषणा FIRMWARE_BLOCK_BOUNDARY 1024
काष्ठा sd_command_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u8 command_type; /* Bit7 - Rd/Wr */
	u8 command_index;
	u8 transfer_size[4]; /* ReadSize + ReadSize */
	u8 response_type;
	u8 arguments[4];
	u8 block_count[2];
	u8 block_size[2];
	u8 block_boundary[2];
	u8 reserved[44]; /* to pad out to 64 bytes */
पूर्ण __packed;

काष्ठा sd_irqpoll_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u8 command_type; /* Bit7 - Rd/Wr */
	u8 padding[16]; /* करोn't ask why !! */
	u8 poll_समयout_msb;
	u8 poll_समयout_lsb;
	u8 reserved[42]; /* to pad out to 64 bytes */
पूर्ण __packed;

काष्ठा sd_common_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
पूर्ण __packed;

काष्ठा sd_response_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u8 command_type;
	u8 command_index;
	u8 command_response[];
पूर्ण __packed;

काष्ठा sd_status_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u16 port_flags;
	u32 sdio_घड़ी;
	u16 host_header_size;
	u16 func_header_size;
	u16 ctrl_header_size;
पूर्ण __packed;

काष्ठा sd_error_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u8 error_code;
पूर्ण __packed;

काष्ठा sd_पूर्णांकerrupt_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
पूर्ण __packed;

काष्ठा offload_रेजिस्टरs_access अणु
	u8 command_byte[4];
	u8 Respond_Byte[4];
पूर्ण __packed;

#घोषणा INTERRUPT_REGISTER_ACCESSES 15
काष्ठा sd_offloaded_पूर्णांकerrupt अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	काष्ठा offload_रेजिस्टरs_access reg[INTERRUPT_REGISTER_ACCESSES];
पूर्ण __packed;

काष्ठा sd_रेजिस्टर_header अणु
	u8 header_size;
	u8 header_type;
	u8 port_number;
	u8 command_type;
	u8 command_index;
	u8 command_response[6];
पूर्ण __packed;

#घोषणा PIGGYBACK_REGISTER_ACCESSES 14
काष्ठा sd_offloaded_piggyback अणु
	काष्ठा sd_रेजिस्टर_header sdio;
	काष्ठा offload_रेजिस्टरs_access reg[PIGGYBACK_REGISTER_ACCESSES];
पूर्ण __packed;

जोड़ sd_response अणु
	काष्ठा sd_common_header common;
	काष्ठा sd_status_header status;
	काष्ठा sd_error_header error;
	काष्ठा sd_पूर्णांकerrupt_header पूर्णांकerrupt;
	काष्ठा sd_response_header response;
	काष्ठा sd_offloaded_पूर्णांकerrupt irq;
	काष्ठा sd_offloaded_piggyback pig;
पूर्ण __packed;

जोड़ sd_command अणु
	काष्ठा sd_command_header head;
	काष्ठा sd_irqpoll_header poll;
पूर्ण __packed;

क्रमागत SD_RESPONSE_TYPE अणु
	SDRT_UNSPECIFIED = 0,
	SDRT_NONE,
	SDRT_1,
	SDRT_1B,
	SDRT_2,
	SDRT_3,
	SDRT_4,
	SDRT_5,
	SDRT_5B,
	SDRT_6,
	SDRT_7,
पूर्ण;

#घोषणा RESPONSE_INTERRUPT			0x01
#घोषणा RESPONSE_ERROR				0x02
#घोषणा RESPONSE_STATUS				0x03
#घोषणा RESPONSE_IRQ_DISABLED			0x05
#घोषणा RESPONSE_IRQ_ENABLED			0x06
#घोषणा RESPONSE_PIGGYBACKED			0x07
#घोषणा RESPONSE_NO_INTERRUPT			0x08
#घोषणा RESPONSE_PIG_DISABLED			0x09
#घोषणा RESPONSE_PIG_ENABLED			0x0A
#घोषणा SD_ERROR_1BIT_TIMEOUT			0x01
#घोषणा SD_ERROR_4BIT_TIMEOUT			0x02
#घोषणा SD_ERROR_1BIT_CRC_WRONG			0x03
#घोषणा SD_ERROR_4BIT_CRC_WRONG			0x04
#घोषणा SD_ERROR_1BIT_CRC_ERROR			0x05
#घोषणा SD_ERROR_4BIT_CRC_ERROR			0x06
#घोषणा SD_ERROR_NO_CMD_ENDBIT			0x07
#घोषणा SD_ERROR_NO_1BIT_DATEND			0x08
#घोषणा SD_ERROR_NO_4BIT_DATEND			0x09
#घोषणा SD_ERROR_1BIT_UNEXPECTED_TIMEOUT	0x0A
#घोषणा SD_ERROR_4BIT_UNEXPECTED_TIMEOUT	0x0B
#घोषणा SD_ERROR_ILLEGAL_COMMAND		0x0C
#घोषणा SD_ERROR_NO_DEVICE			0x0D
#घोषणा SD_ERROR_TRANSFER_LENGTH		0x0E
#घोषणा SD_ERROR_1BIT_DATA_TIMEOUT		0x0F
#घोषणा SD_ERROR_4BIT_DATA_TIMEOUT		0x10
#घोषणा SD_ERROR_ILLEGAL_STATE			0x11
#घोषणा SD_ERROR_UNKNOWN_ERROR			0x12
#घोषणा SD_ERROR_RESERVED_ERROR			0x13
#घोषणा SD_ERROR_INVALID_FUNCTION		0x14
#घोषणा SD_ERROR_OUT_OF_RANGE			0x15
#घोषणा SD_ERROR_STAT_CMD			0x16
#घोषणा SD_ERROR_STAT_DATA			0x17
#घोषणा SD_ERROR_STAT_CMD_TIMEOUT		0x18
#घोषणा SD_ERROR_SDCRDY_STUCK			0x19
#घोषणा SD_ERROR_UNHANDLED			0x1A
#घोषणा SD_ERROR_OVERRUN			0x1B
#घोषणा SD_ERROR_PIO_TIMEOUT			0x1C

#घोषणा FUN(c) (0x000007 & (c->arg>>28))
#घोषणा REG(c) (0x01FFFF & (c->arg>>9))

अटल bool limit_speed_to_24_MHz;
module_param(limit_speed_to_24_MHz, bool, 0644);
MODULE_PARM_DESC(limit_speed_to_24_MHz, "Limit Max SDIO Clock Speed to 24 MHz");

अटल bool pad_input_to_usb_pkt;
module_param(pad_input_to_usb_pkt, bool, 0644);
MODULE_PARM_DESC(pad_input_to_usb_pkt,
		 "Pad USB data input transfers to whole USB Packet");

अटल bool disable_offload_processing;
module_param(disable_offload_processing, bool, 0644);
MODULE_PARM_DESC(disable_offload_processing, "Disable Offload Processing");

अटल bool क्रमce_1_bit_data_xfers;
module_param(क्रमce_1_bit_data_xfers, bool, 0644);
MODULE_PARM_DESC(क्रमce_1_bit_data_xfers,
		 "Force SDIO Data Transfers to 1-bit Mode");

अटल bool क्रमce_polling_क्रम_irqs;
module_param(क्रमce_polling_क्रम_irqs, bool, 0644);
MODULE_PARM_DESC(क्रमce_polling_क्रम_irqs, "Force Polling for SDIO interrupts");

अटल पूर्णांक firmware_irqpoll_समयout = 1024;
module_param(firmware_irqpoll_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(firmware_irqpoll_समयout, "VUB300 firmware irqpoll timeout");

अटल पूर्णांक क्रमce_max_req_size = 128;
module_param(क्रमce_max_req_size, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_max_req_size, "set max request size in kBytes");

#अगर_घोषित SMSC_DEVELOPMENT_BOARD
अटल पूर्णांक firmware_rom_रुको_states = 0x04;
#अन्यथा
अटल पूर्णांक firmware_rom_रुको_states = 0x1C;
#पूर्ण_अगर

module_param(firmware_rom_रुको_states, पूर्णांक, 0644);
MODULE_PARM_DESC(firmware_rom_रुको_states,
		 "ROM wait states byte=RRRIIEEE (Reserved Internal External)");

#घोषणा ELAN_VENDOR_ID		0x2201
#घोषणा VUB300_VENDOR_ID	0x0424
#घोषणा VUB300_PRODUCT_ID	0x012C
अटल स्थिर काष्ठा usb_device_id vub300_table[] = अणु
	अणुUSB_DEVICE(ELAN_VENDOR_ID, VUB300_PRODUCT_ID)पूर्ण,
	अणुUSB_DEVICE(VUB300_VENDOR_ID, VUB300_PRODUCT_ID)पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, vub300_table);

अटल काष्ठा workqueue_काष्ठा *cmndworkqueue;
अटल काष्ठा workqueue_काष्ठा *pollworkqueue;
अटल काष्ठा workqueue_काष्ठा *deadworkqueue;

अटल अंतरभूत पूर्णांक पूर्णांकerface_to_InterfaceNumber(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	अगर (!पूर्णांकerface)
		वापस -1;
	अगर (!पूर्णांकerface->cur_altsetting)
		वापस -1;
	वापस पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
पूर्ण

काष्ठा sdio_रेजिस्टर अणु
	अचिन्हित func_num:3;
	अचिन्हित sdio_reg:17;
	अचिन्हित activate:1;
	अचिन्हित prepared:1;
	अचिन्हित regvalue:8;
	अचिन्हित response:8;
	अचिन्हित sparebit:26;
पूर्ण;

काष्ठा vub300_mmc_host अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा kref kref;
	काष्ठा mutex cmd_mutex;
	काष्ठा mutex irq_mutex;
	अक्षर vub_name[3 + (9 * 8) + 4 + 1]; /* max of 7 sdio fn's */
	u8 cmnd_out_ep; /* EndPoपूर्णांक क्रम commands */
	u8 cmnd_res_ep; /* EndPoपूर्णांक क्रम responses */
	u8 data_out_ep; /* EndPoपूर्णांक क्रम out data */
	u8 data_inp_ep; /* EndPoपूर्णांक क्रम inp data */
	bool card_घातered;
	bool card_present;
	bool पढ़ो_only;
	bool large_usb_packets;
	bool app_spec; /* ApplicationSpecअगरic */
	bool irq_enabled; /* by the MMC CORE */
	bool irq_disabled; /* in the firmware */
	अचिन्हित bus_width:4;
	u8 total_offload_count;
	u8 dynamic_रेजिस्टर_count;
	u8 resp_len;
	u32 datasize;
	पूर्णांक errors;
	पूर्णांक usb_transport_fail;
	पूर्णांक usb_समयd_out;
	पूर्णांक irqs_queued;
	काष्ठा sdio_रेजिस्टर sdio_रेजिस्टर[16];
	काष्ठा offload_पूर्णांकerrupt_function_रेजिस्टर अणु
#घोषणा MAXREGBITS 4
#घोषणा MAXREGS (1<<MAXREGBITS)
#घोषणा MAXREGMASK (MAXREGS-1)
		u8 offload_count;
		u32 offload_poपूर्णांक;
		काष्ठा offload_रेजिस्टरs_access reg[MAXREGS];
	पूर्ण fn[8];
	u16 fbs[8]; /* Function Block Size */
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_request *req;
	काष्ठा mmc_data *data;
	काष्ठा mmc_host *mmc;
	काष्ठा urb *urb;
	काष्ठा urb *command_out_urb;
	काष्ठा urb *command_res_urb;
	काष्ठा completion command_complete;
	काष्ठा completion irqpoll_complete;
	जोड़ sd_command cmnd;
	जोड़ sd_response resp;
	काष्ठा समयr_list sg_transfer_समयr;
	काष्ठा usb_sg_request sg_request;
	काष्ठा समयr_list inactivity_समयr;
	काष्ठा work_काष्ठा deadwork;
	काष्ठा work_काष्ठा cmndwork;
	काष्ठा delayed_work pollwork;
	काष्ठा host_controller_info hc_info;
	काष्ठा sd_status_header प्रणाली_port_status;
	u8 padded_buffer[64];
पूर्ण;

#घोषणा kref_to_vub300_mmc_host(d) container_of(d, काष्ठा vub300_mmc_host, kref)
#घोषणा SET_TRANSFER_PSEUDOCODE		21
#घोषणा SET_INTERRUPT_PSEUDOCODE	20
#घोषणा SET_FAILURE_MODE		18
#घोषणा SET_ROM_WAIT_STATES		16
#घोषणा SET_IRQ_ENABLE			13
#घोषणा SET_CLOCK_SPEED			11
#घोषणा SET_FUNCTION_BLOCK_SIZE		9
#घोषणा SET_SD_DATA_MODE		6
#घोषणा SET_SD_POWER			4
#घोषणा ENTER_DFU_MODE			3
#घोषणा GET_HC_INF0			1
#घोषणा GET_SYSTEM_PORT_STATUS		0

अटल व्योम vub300_delete(काष्ठा kref *kref)
अणु				/* kref callback - softirq */
	काष्ठा vub300_mmc_host *vub300 = kref_to_vub300_mmc_host(kref);
	काष्ठा mmc_host *mmc = vub300->mmc;
	usb_मुक्त_urb(vub300->command_out_urb);
	vub300->command_out_urb = शून्य;
	usb_मुक्त_urb(vub300->command_res_urb);
	vub300->command_res_urb = शून्य;
	usb_put_dev(vub300->udev);
	mmc_मुक्त_host(mmc);
	/*
	 * and hence also मुक्तs vub300
	 * which is contained at the end of काष्ठा mmc
	 */
पूर्ण

अटल व्योम vub300_queue_cmnd_work(काष्ठा vub300_mmc_host *vub300)
अणु
	kref_get(&vub300->kref);
	अगर (queue_work(cmndworkqueue, &vub300->cmndwork)) अणु
		/*
		 * then the cmndworkqueue was not previously
		 * running and the above get ref is obvious
		 * required and will be put when the thपढ़ो
		 * terminates by a specअगरic call
		 */
	पूर्ण अन्यथा अणु
		/*
		 * the cmndworkqueue was alपढ़ोy running from
		 * a previous invocation and thus to keep the
		 * kref counts correct we must unकरो the get
		 */
		kref_put(&vub300->kref, vub300_delete);
	पूर्ण
पूर्ण

अटल व्योम vub300_queue_poll_work(काष्ठा vub300_mmc_host *vub300, पूर्णांक delay)
अणु
	kref_get(&vub300->kref);
	अगर (queue_delayed_work(pollworkqueue, &vub300->pollwork, delay)) अणु
		/*
		 * then the pollworkqueue was not previously
		 * running and the above get ref is obvious
		 * required and will be put when the thपढ़ो
		 * terminates by a specअगरic call
		 */
	पूर्ण अन्यथा अणु
		/*
		 * the pollworkqueue was alपढ़ोy running from
		 * a previous invocation and thus to keep the
		 * kref counts correct we must unकरो the get
		 */
		kref_put(&vub300->kref, vub300_delete);
	पूर्ण
पूर्ण

अटल व्योम vub300_queue_dead_work(काष्ठा vub300_mmc_host *vub300)
अणु
	kref_get(&vub300->kref);
	अगर (queue_work(deadworkqueue, &vub300->deadwork)) अणु
		/*
		 * then the deadworkqueue was not previously
		 * running and the above get ref is obvious
		 * required and will be put when the thपढ़ो
		 * terminates by a specअगरic call
		 */
	पूर्ण अन्यथा अणु
		/*
		 * the deadworkqueue was alपढ़ोy running from
		 * a previous invocation and thus to keep the
		 * kref counts correct we must unकरो the get
		 */
		kref_put(&vub300->kref, vub300_delete);
	पूर्ण
पूर्ण

अटल व्योम irqpoll_res_completed(काष्ठा urb *urb)
अणु				/* urb completion handler - hardirq */
	काष्ठा vub300_mmc_host *vub300 = (काष्ठा vub300_mmc_host *)urb->context;
	अगर (urb->status)
		vub300->usb_transport_fail = urb->status;
	complete(&vub300->irqpoll_complete);
पूर्ण

अटल व्योम irqpoll_out_completed(काष्ठा urb *urb)
अणु				/* urb completion handler - hardirq */
	काष्ठा vub300_mmc_host *vub300 = (काष्ठा vub300_mmc_host *)urb->context;
	अगर (urb->status) अणु
		vub300->usb_transport_fail = urb->status;
		complete(&vub300->irqpoll_complete);
		वापस;
	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक pipe =
			usb_rcvbulkpipe(vub300->udev, vub300->cmnd_res_ep);
		usb_fill_bulk_urb(vub300->command_res_urb, vub300->udev, pipe,
				  &vub300->resp, माप(vub300->resp),
				  irqpoll_res_completed, vub300);
		vub300->command_res_urb->actual_length = 0;
		ret = usb_submit_urb(vub300->command_res_urb, GFP_ATOMIC);
		अगर (ret) अणु
			vub300->usb_transport_fail = ret;
			complete(&vub300->irqpoll_complete);
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल व्योम send_irqpoll(काष्ठा vub300_mmc_host *vub300)
अणु
	/* cmd_mutex is held by vub300_pollwork_thपढ़ो */
	पूर्णांक retval;
	पूर्णांक समयout = 0xFFFF & (0x0001FFFF - firmware_irqpoll_समयout);
	vub300->cmnd.poll.header_size = 22;
	vub300->cmnd.poll.header_type = 1;
	vub300->cmnd.poll.port_number = 0;
	vub300->cmnd.poll.command_type = 2;
	vub300->cmnd.poll.poll_समयout_lsb = 0xFF & (अचिन्हित)समयout;
	vub300->cmnd.poll.poll_समयout_msb = 0xFF & (अचिन्हित)(समयout >> 8);
	usb_fill_bulk_urb(vub300->command_out_urb, vub300->udev,
			  usb_sndbulkpipe(vub300->udev, vub300->cmnd_out_ep)
			  , &vub300->cmnd, माप(vub300->cmnd)
			  , irqpoll_out_completed, vub300);
	retval = usb_submit_urb(vub300->command_out_urb, GFP_KERNEL);
	अगर (0 > retval) अणु
		vub300->usb_transport_fail = retval;
		vub300_queue_poll_work(vub300, 1);
		complete(&vub300->irqpoll_complete);
		वापस;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

अटल व्योम new_प्रणाली_port_status(काष्ठा vub300_mmc_host *vub300)
अणु
	पूर्णांक old_card_present = vub300->card_present;
	पूर्णांक new_card_present =
		(0x0001 & vub300->प्रणाली_port_status.port_flags) ? 1 : 0;
	vub300->पढ़ो_only =
		(0x0010 & vub300->प्रणाली_port_status.port_flags) ? 1 : 0;
	अगर (new_card_present && !old_card_present) अणु
		dev_info(&vub300->udev->dev, "card just inserted\n");
		vub300->card_present = 1;
		vub300->bus_width = 0;
		अगर (disable_offload_processing)
			म_नकलन(vub300->vub_name, "EMPTY Processing Disabled",
				माप(vub300->vub_name));
		अन्यथा
			vub300->vub_name[0] = 0;
		mmc_detect_change(vub300->mmc, 1);
	पूर्ण अन्यथा अगर (!new_card_present && old_card_present) अणु
		dev_info(&vub300->udev->dev, "card just ejected\n");
		vub300->card_present = 0;
		mmc_detect_change(vub300->mmc, 0);
	पूर्ण अन्यथा अणु
		/* no change */
	पूर्ण
पूर्ण

अटल व्योम __add_offloaded_reg_to_fअगरo(काष्ठा vub300_mmc_host *vub300,
					काष्ठा offload_रेजिस्टरs_access
					*रेजिस्टर_access, u8 func)
अणु
	u8 r = vub300->fn[func].offload_poपूर्णांक + vub300->fn[func].offload_count;
	स_नकल(&vub300->fn[func].reg[MAXREGMASK & r], रेजिस्टर_access,
	       माप(काष्ठा offload_रेजिस्टरs_access));
	vub300->fn[func].offload_count += 1;
	vub300->total_offload_count += 1;
पूर्ण

अटल व्योम add_offloaded_reg(काष्ठा vub300_mmc_host *vub300,
			      काष्ठा offload_रेजिस्टरs_access *रेजिस्टर_access)
अणु
	u32 Register = ((0x03 & रेजिस्टर_access->command_byte[0]) << 15)
			| ((0xFF & रेजिस्टर_access->command_byte[1]) << 7)
			| ((0xFE & रेजिस्टर_access->command_byte[2]) >> 1);
	u8 func = ((0x70 & रेजिस्टर_access->command_byte[0]) >> 4);
	u8 regs = vub300->dynamic_रेजिस्टर_count;
	u8 i = 0;
	जबतक (0 < regs-- && 1 == vub300->sdio_रेजिस्टर[i].activate) अणु
		अगर (vub300->sdio_रेजिस्टर[i].func_num == func &&
		    vub300->sdio_रेजिस्टर[i].sdio_reg == Register) अणु
			अगर (vub300->sdio_रेजिस्टर[i].prepared == 0)
				vub300->sdio_रेजिस्टर[i].prepared = 1;
			vub300->sdio_रेजिस्टर[i].response =
				रेजिस्टर_access->Respond_Byte[2];
			vub300->sdio_रेजिस्टर[i].regvalue =
				रेजिस्टर_access->Respond_Byte[3];
			वापस;
		पूर्ण अन्यथा अणु
			i += 1;
			जारी;
		पूर्ण
	पूर्ण
	__add_offloaded_reg_to_fअगरo(vub300, रेजिस्टर_access, func);
पूर्ण

अटल व्योम check_vub300_port_status(काष्ठा vub300_mmc_host *vub300)
अणु
	/*
	 * cmd_mutex is held by vub300_pollwork_thपढ़ो,
	 * vub300_deadwork_thपढ़ो or vub300_cmndwork_thपढ़ो
	 */
	पूर्णांक retval;
	retval =
		usb_control_msg(vub300->udev, usb_rcvctrlpipe(vub300->udev, 0),
				GET_SYSTEM_PORT_STATUS,
				USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, &vub300->प्रणाली_port_status,
				माप(vub300->प्रणाली_port_status), HZ);
	अगर (माप(vub300->प्रणाली_port_status) == retval)
		new_प्रणाली_port_status(vub300);
पूर्ण

अटल व्योम __vub300_irqpoll_response(काष्ठा vub300_mmc_host *vub300)
अणु
	/* cmd_mutex is held by vub300_pollwork_thपढ़ो */
	अगर (vub300->command_res_urb->actual_length == 0)
		वापस;

	चयन (vub300->resp.common.header_type) अणु
	हाल RESPONSE_INTERRUPT:
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irq_enabled)
			mmc_संकेत_sdio_irq(vub300->mmc);
		अन्यथा
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 1;
		mutex_unlock(&vub300->irq_mutex);
		अवरोध;
	हाल RESPONSE_ERROR:
		अगर (vub300->resp.error.error_code == SD_ERROR_NO_DEVICE)
			check_vub300_port_status(vub300);
		अवरोध;
	हाल RESPONSE_STATUS:
		vub300->प्रणाली_port_status = vub300->resp.status;
		new_प्रणाली_port_status(vub300);
		अगर (!vub300->card_present)
			vub300_queue_poll_work(vub300, HZ / 5);
		अवरोध;
	हाल RESPONSE_IRQ_DISABLED:
	अणु
		पूर्णांक offloaded_data_length = vub300->resp.common.header_size - 3;
		पूर्णांक रेजिस्टर_count = offloaded_data_length >> 3;
		पूर्णांक ri = 0;
		जबतक (रेजिस्टर_count--) अणु
			add_offloaded_reg(vub300, &vub300->resp.irq.reg[ri]);
			ri += 1;
		पूर्ण
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irq_enabled)
			mmc_संकेत_sdio_irq(vub300->mmc);
		अन्यथा
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 1;
		mutex_unlock(&vub300->irq_mutex);
		अवरोध;
	पूर्ण
	हाल RESPONSE_IRQ_ENABLED:
	अणु
		पूर्णांक offloaded_data_length = vub300->resp.common.header_size - 3;
		पूर्णांक रेजिस्टर_count = offloaded_data_length >> 3;
		पूर्णांक ri = 0;
		जबतक (रेजिस्टर_count--) अणु
			add_offloaded_reg(vub300, &vub300->resp.irq.reg[ri]);
			ri += 1;
		पूर्ण
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irq_enabled)
			mmc_संकेत_sdio_irq(vub300->mmc);
		अन्यथा
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 0;
		mutex_unlock(&vub300->irq_mutex);
		अवरोध;
	पूर्ण
	हाल RESPONSE_NO_INTERRUPT:
		vub300_queue_poll_work(vub300, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __करो_poll(काष्ठा vub300_mmc_host *vub300)
अणु
	/* cmd_mutex is held by vub300_pollwork_thपढ़ो */
	अचिन्हित दीर्घ commretval;
	mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
	init_completion(&vub300->irqpoll_complete);
	send_irqpoll(vub300);
	commretval = रुको_क्रम_completion_समयout(&vub300->irqpoll_complete,
						 msecs_to_jअगरfies(500));
	अगर (vub300->usb_transport_fail) अणु
		/* no need to करो anything */
	पूर्ण अन्यथा अगर (commretval == 0) अणु
		vub300->usb_समयd_out = 1;
		usb_समाप्त_urb(vub300->command_out_urb);
		usb_समाप्त_urb(vub300->command_res_urb);
	पूर्ण अन्यथा अणु /* commretval > 0 */
		__vub300_irqpoll_response(vub300);
	पूर्ण
पूर्ण

/* this thपढ़ो runs only when the driver
 * is trying to poll the device क्रम an IRQ
 */
अटल व्योम vub300_pollwork_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = container_of(work,
			      काष्ठा vub300_mmc_host, pollwork.work);
	अगर (!vub300->पूर्णांकerface) अणु
		kref_put(&vub300->kref, vub300_delete);
		वापस;
	पूर्ण
	mutex_lock(&vub300->cmd_mutex);
	अगर (vub300->cmd) अणु
		vub300_queue_poll_work(vub300, 1);
	पूर्ण अन्यथा अगर (!vub300->card_present) अणु
		/* no need to करो anything */
	पूर्ण अन्यथा अणु /* vub300->card_present */
		mutex_lock(&vub300->irq_mutex);
		अगर (!vub300->irq_enabled) अणु
			mutex_unlock(&vub300->irq_mutex);
		पूर्ण अन्यथा अगर (vub300->irqs_queued) अणु
			vub300->irqs_queued -= 1;
			mmc_संकेत_sdio_irq(vub300->mmc);
			mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
			mutex_unlock(&vub300->irq_mutex);
		पूर्ण अन्यथा अणु /* NOT vub300->irqs_queued */
			mutex_unlock(&vub300->irq_mutex);
			__करो_poll(vub300);
		पूर्ण
	पूर्ण
	mutex_unlock(&vub300->cmd_mutex);
	kref_put(&vub300->kref, vub300_delete);
पूर्ण

अटल व्योम vub300_deadwork_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 =
		container_of(work, काष्ठा vub300_mmc_host, deadwork);
	अगर (!vub300->पूर्णांकerface) अणु
		kref_put(&vub300->kref, vub300_delete);
		वापस;
	पूर्ण
	mutex_lock(&vub300->cmd_mutex);
	अगर (vub300->cmd) अणु
		/*
		 * a command got in as the inactivity
		 * समयr expired - so we just let the
		 * processing of the command show अगर
		 * the device is dead
		 */
	पूर्ण अन्यथा अगर (vub300->card_present) अणु
		check_vub300_port_status(vub300);
	पूर्ण अन्यथा अगर (vub300->mmc && vub300->mmc->card) अणु
		/*
		 * the MMC core must not have responded
		 * to the previous indication - lets
		 * hope that it eventually करोes so we
		 * will just ignore this क्रम now
		 */
	पूर्ण अन्यथा अणु
		check_vub300_port_status(vub300);
	पूर्ण
	mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
	mutex_unlock(&vub300->cmd_mutex);
	kref_put(&vub300->kref, vub300_delete);
पूर्ण

अटल व्योम vub300_inactivity_समयr_expired(काष्ठा समयr_list *t)
अणु				/* softirq */
	काष्ठा vub300_mmc_host *vub300 = from_समयr(vub300, t,
						    inactivity_समयr);
	अगर (!vub300->पूर्णांकerface) अणु
		kref_put(&vub300->kref, vub300_delete);
	पूर्ण अन्यथा अगर (vub300->cmd) अणु
		mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
	पूर्ण अन्यथा अणु
		vub300_queue_dead_work(vub300);
		mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
	पूर्ण
पूर्ण

अटल पूर्णांक vub300_response_error(u8 error_code)
अणु
	चयन (error_code) अणु
	हाल SD_ERROR_PIO_TIMEOUT:
	हाल SD_ERROR_1BIT_TIMEOUT:
	हाल SD_ERROR_4BIT_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल SD_ERROR_STAT_DATA:
	हाल SD_ERROR_OVERRUN:
	हाल SD_ERROR_STAT_CMD:
	हाल SD_ERROR_STAT_CMD_TIMEOUT:
	हाल SD_ERROR_SDCRDY_STUCK:
	हाल SD_ERROR_UNHANDLED:
	हाल SD_ERROR_1BIT_CRC_WRONG:
	हाल SD_ERROR_4BIT_CRC_WRONG:
	हाल SD_ERROR_1BIT_CRC_ERROR:
	हाल SD_ERROR_4BIT_CRC_ERROR:
	हाल SD_ERROR_NO_CMD_ENDBIT:
	हाल SD_ERROR_NO_1BIT_DATEND:
	हाल SD_ERROR_NO_4BIT_DATEND:
	हाल SD_ERROR_1BIT_DATA_TIMEOUT:
	हाल SD_ERROR_4BIT_DATA_TIMEOUT:
	हाल SD_ERROR_1BIT_UNEXPECTED_TIMEOUT:
	हाल SD_ERROR_4BIT_UNEXPECTED_TIMEOUT:
		वापस -EILSEQ;
	हाल 33:
		वापस -EILSEQ;
	हाल SD_ERROR_ILLEGAL_COMMAND:
		वापस -EINVAL;
	हाल SD_ERROR_NO_DEVICE:
		वापस -ENOMEDIUM;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल व्योम command_res_completed(काष्ठा urb *urb)
अणु				/* urb completion handler - hardirq */
	काष्ठा vub300_mmc_host *vub300 = (काष्ठा vub300_mmc_host *)urb->context;
	अगर (urb->status) अणु
		/* we have to let the initiator handle the error */
	पूर्ण अन्यथा अगर (vub300->command_res_urb->actual_length == 0) अणु
		/*
		 * we have seen this happen once or twice and
		 * we suspect a buggy USB host controller
		 */
	पूर्ण अन्यथा अगर (!vub300->data) अणु
		/* this means that the command (typically CMD52) succeeded */
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type != 0x02) अणु
		/*
		 * this is an error response from the VUB300 chip
		 * and we let the initiator handle it
		 */
	पूर्ण अन्यथा अगर (vub300->urb) अणु
		vub300->cmd->error =
			vub300_response_error(vub300->resp.error.error_code);
		usb_unlink_urb(vub300->urb);
	पूर्ण अन्यथा अणु
		vub300->cmd->error =
			vub300_response_error(vub300->resp.error.error_code);
		usb_sg_cancel(&vub300->sg_request);
	पूर्ण
	complete(&vub300->command_complete);	/* got_response_in */
पूर्ण

अटल व्योम command_out_completed(काष्ठा urb *urb)
अणु				/* urb completion handler - hardirq */
	काष्ठा vub300_mmc_host *vub300 = (काष्ठा vub300_mmc_host *)urb->context;
	अगर (urb->status) अणु
		complete(&vub300->command_complete);
	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक pipe =
			usb_rcvbulkpipe(vub300->udev, vub300->cmnd_res_ep);
		usb_fill_bulk_urb(vub300->command_res_urb, vub300->udev, pipe,
				  &vub300->resp, माप(vub300->resp),
				  command_res_completed, vub300);
		vub300->command_res_urb->actual_length = 0;
		ret = usb_submit_urb(vub300->command_res_urb, GFP_ATOMIC);
		अगर (ret == 0) अणु
			/*
			 * the urb completion handler will call
			 * our completion handler
			 */
		पूर्ण अन्यथा अणु
			/*
			 * and thus we only call it directly
			 * when it will not be called
			 */
			complete(&vub300->command_complete);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * the STUFF bits are masked out क्रम the comparisons
 */
अटल व्योम snoop_block_size_and_bus_width(काष्ठा vub300_mmc_host *vub300,
					   u32 cmd_arg)
अणु
	अगर ((0xFBFFFE00 & cmd_arg) == 0x80022200)
		vub300->fbs[1] = (cmd_arg << 8) | (0x00FF & vub300->fbs[1]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80022000)
		vub300->fbs[1] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[1]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80042200)
		vub300->fbs[2] = (cmd_arg << 8) | (0x00FF & vub300->fbs[2]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80042000)
		vub300->fbs[2] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[2]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80062200)
		vub300->fbs[3] = (cmd_arg << 8) | (0x00FF & vub300->fbs[3]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80062000)
		vub300->fbs[3] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[3]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80082200)
		vub300->fbs[4] = (cmd_arg << 8) | (0x00FF & vub300->fbs[4]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x80082000)
		vub300->fbs[4] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[4]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800A2200)
		vub300->fbs[5] = (cmd_arg << 8) | (0x00FF & vub300->fbs[5]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800A2000)
		vub300->fbs[5] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[5]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800C2200)
		vub300->fbs[6] = (cmd_arg << 8) | (0x00FF & vub300->fbs[6]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800C2000)
		vub300->fbs[6] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[6]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800E2200)
		vub300->fbs[7] = (cmd_arg << 8) | (0x00FF & vub300->fbs[7]);
	अन्यथा अगर ((0xFBFFFE00 & cmd_arg) == 0x800E2000)
		vub300->fbs[7] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[7]);
	अन्यथा अगर ((0xFBFFFE03 & cmd_arg) == 0x80000E00)
		vub300->bus_width = 1;
	अन्यथा अगर ((0xFBFFFE03 & cmd_arg) == 0x80000E02)
		vub300->bus_width = 4;
पूर्ण

अटल व्योम send_command(काष्ठा vub300_mmc_host *vub300)
अणु
	/* cmd_mutex is held by vub300_cmndwork_thपढ़ो */
	काष्ठा mmc_command *cmd = vub300->cmd;
	काष्ठा mmc_data *data = vub300->data;
	पूर्णांक retval;
	पूर्णांक i;
	u8 response_type;
	अगर (vub300->app_spec) अणु
		चयन (cmd->opcode) अणु
		हाल 6:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अगर (0x00000000 == (0x00000003 & cmd->arg))
				vub300->bus_width = 1;
			अन्यथा अगर (0x00000002 == (0x00000003 & cmd->arg))
				vub300->bus_width = 4;
			अन्यथा
				dev_err(&vub300->udev->dev,
					"unexpected ACMD6 bus_width=%d\n",
					0x00000003 & cmd->arg);
			अवरोध;
		हाल 13:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 22:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 23:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 41:
			response_type = SDRT_3;
			vub300->resp_len = 6;
			अवरोध;
		हाल 42:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 51:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 55:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		शेष:
			vub300->resp_len = 0;
			cmd->error = -EINVAL;
			complete(&vub300->command_complete);
			वापस;
		पूर्ण
		vub300->app_spec = 0;
	पूर्ण अन्यथा अणु
		चयन (cmd->opcode) अणु
		हाल 0:
			response_type = SDRT_NONE;
			vub300->resp_len = 0;
			अवरोध;
		हाल 1:
			response_type = SDRT_3;
			vub300->resp_len = 6;
			अवरोध;
		हाल 2:
			response_type = SDRT_2;
			vub300->resp_len = 17;
			अवरोध;
		हाल 3:
			response_type = SDRT_6;
			vub300->resp_len = 6;
			अवरोध;
		हाल 4:
			response_type = SDRT_NONE;
			vub300->resp_len = 0;
			अवरोध;
		हाल 5:
			response_type = SDRT_4;
			vub300->resp_len = 6;
			अवरोध;
		हाल 6:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 7:
			response_type = SDRT_1B;
			vub300->resp_len = 6;
			अवरोध;
		हाल 8:
			response_type = SDRT_7;
			vub300->resp_len = 6;
			अवरोध;
		हाल 9:
			response_type = SDRT_2;
			vub300->resp_len = 17;
			अवरोध;
		हाल 10:
			response_type = SDRT_2;
			vub300->resp_len = 17;
			अवरोध;
		हाल 12:
			response_type = SDRT_1B;
			vub300->resp_len = 6;
			अवरोध;
		हाल 13:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 15:
			response_type = SDRT_NONE;
			vub300->resp_len = 0;
			अवरोध;
		हाल 16:
			क्रम (i = 0; i < ARRAY_SIZE(vub300->fbs); i++)
				vub300->fbs[i] = 0xFFFF & cmd->arg;
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 17:
		हाल 18:
		हाल 24:
		हाल 25:
		हाल 27:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 28:
		हाल 29:
			response_type = SDRT_1B;
			vub300->resp_len = 6;
			अवरोध;
		हाल 30:
		हाल 32:
		हाल 33:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 38:
			response_type = SDRT_1B;
			vub300->resp_len = 6;
			अवरोध;
		हाल 42:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		हाल 52:
			response_type = SDRT_5;
			vub300->resp_len = 6;
			snoop_block_size_and_bus_width(vub300, cmd->arg);
			अवरोध;
		हाल 53:
			response_type = SDRT_5;
			vub300->resp_len = 6;
			अवरोध;
		हाल 55:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			vub300->app_spec = 1;
			अवरोध;
		हाल 56:
			response_type = SDRT_1;
			vub300->resp_len = 6;
			अवरोध;
		शेष:
			vub300->resp_len = 0;
			cmd->error = -EINVAL;
			complete(&vub300->command_complete);
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * it is a shame that we can not use "sizeof(struct sd_command_header)"
	 * this is because the packet _must_ be padded to 64 bytes
	 */
	vub300->cmnd.head.header_size = 20;
	vub300->cmnd.head.header_type = 0x00;
	vub300->cmnd.head.port_number = 0; /* "0" means port 1 */
	vub300->cmnd.head.command_type = 0x00; /* standard पढ़ो command */
	vub300->cmnd.head.response_type = response_type;
	vub300->cmnd.head.command_index = cmd->opcode;
	vub300->cmnd.head.arguments[0] = cmd->arg >> 24;
	vub300->cmnd.head.arguments[1] = cmd->arg >> 16;
	vub300->cmnd.head.arguments[2] = cmd->arg >> 8;
	vub300->cmnd.head.arguments[3] = cmd->arg >> 0;
	अगर (cmd->opcode == 52) अणु
		पूर्णांक fn = 0x7 & (cmd->arg >> 28);
		vub300->cmnd.head.block_count[0] = 0;
		vub300->cmnd.head.block_count[1] = 0;
		vub300->cmnd.head.block_size[0] = (vub300->fbs[fn] >> 8) & 0xFF;
		vub300->cmnd.head.block_size[1] = (vub300->fbs[fn] >> 0) & 0xFF;
		vub300->cmnd.head.command_type = 0x00;
		vub300->cmnd.head.transfer_size[0] = 0;
		vub300->cmnd.head.transfer_size[1] = 0;
		vub300->cmnd.head.transfer_size[2] = 0;
		vub300->cmnd.head.transfer_size[3] = 0;
	पूर्ण अन्यथा अगर (!data) अणु
		vub300->cmnd.head.block_count[0] = 0;
		vub300->cmnd.head.block_count[1] = 0;
		vub300->cmnd.head.block_size[0] = (vub300->fbs[0] >> 8) & 0xFF;
		vub300->cmnd.head.block_size[1] = (vub300->fbs[0] >> 0) & 0xFF;
		vub300->cmnd.head.command_type = 0x00;
		vub300->cmnd.head.transfer_size[0] = 0;
		vub300->cmnd.head.transfer_size[1] = 0;
		vub300->cmnd.head.transfer_size[2] = 0;
		vub300->cmnd.head.transfer_size[3] = 0;
	पूर्ण अन्यथा अगर (cmd->opcode == 53) अणु
		पूर्णांक fn = 0x7 & (cmd->arg >> 28);
		अगर (0x08 & vub300->cmnd.head.arguments[0]) अणु /* BLOCK MODE */
			vub300->cmnd.head.block_count[0] =
				(data->blocks >> 8) & 0xFF;
			vub300->cmnd.head.block_count[1] =
				(data->blocks >> 0) & 0xFF;
			vub300->cmnd.head.block_size[0] =
				(data->blksz >> 8) & 0xFF;
			vub300->cmnd.head.block_size[1] =
				(data->blksz >> 0) & 0xFF;
		पूर्ण अन्यथा अणु	/* BYTE MODE */
			vub300->cmnd.head.block_count[0] = 0;
			vub300->cmnd.head.block_count[1] = 0;
			vub300->cmnd.head.block_size[0] =
				(vub300->datasize >> 8) & 0xFF;
			vub300->cmnd.head.block_size[1] =
				(vub300->datasize >> 0) & 0xFF;
		पूर्ण
		vub300->cmnd.head.command_type =
			(MMC_DATA_READ & data->flags) ? 0x00 : 0x80;
		vub300->cmnd.head.transfer_size[0] =
			(vub300->datasize >> 24) & 0xFF;
		vub300->cmnd.head.transfer_size[1] =
			(vub300->datasize >> 16) & 0xFF;
		vub300->cmnd.head.transfer_size[2] =
			(vub300->datasize >> 8) & 0xFF;
		vub300->cmnd.head.transfer_size[3] =
			(vub300->datasize >> 0) & 0xFF;
		अगर (vub300->datasize < vub300->fbs[fn]) अणु
			vub300->cmnd.head.block_count[0] = 0;
			vub300->cmnd.head.block_count[1] = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		vub300->cmnd.head.block_count[0] = (data->blocks >> 8) & 0xFF;
		vub300->cmnd.head.block_count[1] = (data->blocks >> 0) & 0xFF;
		vub300->cmnd.head.block_size[0] = (data->blksz >> 8) & 0xFF;
		vub300->cmnd.head.block_size[1] = (data->blksz >> 0) & 0xFF;
		vub300->cmnd.head.command_type =
			(MMC_DATA_READ & data->flags) ? 0x00 : 0x80;
		vub300->cmnd.head.transfer_size[0] =
			(vub300->datasize >> 24) & 0xFF;
		vub300->cmnd.head.transfer_size[1] =
			(vub300->datasize >> 16) & 0xFF;
		vub300->cmnd.head.transfer_size[2] =
			(vub300->datasize >> 8) & 0xFF;
		vub300->cmnd.head.transfer_size[3] =
			(vub300->datasize >> 0) & 0xFF;
		अगर (vub300->datasize < vub300->fbs[0]) अणु
			vub300->cmnd.head.block_count[0] = 0;
			vub300->cmnd.head.block_count[1] = 0;
		पूर्ण
	पूर्ण
	अगर (vub300->cmnd.head.block_size[0] || vub300->cmnd.head.block_size[1]) अणु
		u16 block_size = vub300->cmnd.head.block_size[1] |
			(vub300->cmnd.head.block_size[0] << 8);
		u16 block_boundary = FIRMWARE_BLOCK_BOUNDARY -
			(FIRMWARE_BLOCK_BOUNDARY % block_size);
		vub300->cmnd.head.block_boundary[0] =
			(block_boundary >> 8) & 0xFF;
		vub300->cmnd.head.block_boundary[1] =
			(block_boundary >> 0) & 0xFF;
	पूर्ण अन्यथा अणु
		vub300->cmnd.head.block_boundary[0] = 0;
		vub300->cmnd.head.block_boundary[1] = 0;
	पूर्ण
	usb_fill_bulk_urb(vub300->command_out_urb, vub300->udev,
			  usb_sndbulkpipe(vub300->udev, vub300->cmnd_out_ep),
			  &vub300->cmnd, माप(vub300->cmnd),
			  command_out_completed, vub300);
	retval = usb_submit_urb(vub300->command_out_urb, GFP_KERNEL);
	अगर (retval < 0) अणु
		cmd->error = retval;
		complete(&vub300->command_complete);
		वापस;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

/*
 * समयr callback runs in atomic mode
 *       so it cannot call usb_समाप्त_urb()
 */
अटल व्योम vub300_sg_समयd_out(काष्ठा समयr_list *t)
अणु
	काष्ठा vub300_mmc_host *vub300 = from_समयr(vub300, t,
						    sg_transfer_समयr);
	vub300->usb_समयd_out = 1;
	usb_sg_cancel(&vub300->sg_request);
	usb_unlink_urb(vub300->command_out_urb);
	usb_unlink_urb(vub300->command_res_urb);
पूर्ण

अटल u16 roundup_to_multiple_of_64(u16 number)
अणु
	वापस 0xFFC0 & (0x3F + number);
पूर्ण

/*
 * this is a separate function to solve the 80 column width restriction
 */
अटल व्योम __करोwnload_offload_pseuकरोcode(काष्ठा vub300_mmc_host *vub300,
					  स्थिर काष्ठा firmware *fw)
अणु
	u8 रेजिस्टर_count = 0;
	u16 ts = 0;
	u16 पूर्णांकerrupt_size = 0;
	स्थिर u8 *data = fw->data;
	पूर्णांक size = fw->size;
	u8 c;
	dev_info(&vub300->udev->dev, "using %s for SDIO offload processing\n",
		 vub300->vub_name);
	करो अणु
		c = *data++;
	पूर्ण जबतक (size-- && c); /* skip comment */
	dev_info(&vub300->udev->dev, "using offload firmware %s %s\n", fw->data,
		 vub300->vub_name);
	अगर (size < 4) अणु
		dev_err(&vub300->udev->dev,
			"corrupt offload pseudocode in firmware %s\n",
			vub300->vub_name);
		म_नकलन(vub300->vub_name, "corrupt offload pseudocode",
			माप(vub300->vub_name));
		वापस;
	पूर्ण
	पूर्णांकerrupt_size += *data++;
	size -= 1;
	पूर्णांकerrupt_size <<= 8;
	पूर्णांकerrupt_size += *data++;
	size -= 1;
	अगर (पूर्णांकerrupt_size < size) अणु
		u16 xfer_length = roundup_to_multiple_of_64(पूर्णांकerrupt_size);
		u8 *xfer_buffer = kदो_स्मृति(xfer_length, GFP_KERNEL);
		अगर (xfer_buffer) अणु
			पूर्णांक retval;
			स_नकल(xfer_buffer, data, पूर्णांकerrupt_size);
			स_रखो(xfer_buffer + पूर्णांकerrupt_size, 0,
			       xfer_length - पूर्णांकerrupt_size);
			size -= पूर्णांकerrupt_size;
			data += पूर्णांकerrupt_size;
			retval =
				usb_control_msg(vub300->udev,
						usb_sndctrlpipe(vub300->udev, 0),
						SET_INTERRUPT_PSEUDOCODE,
						USB_सूची_OUT | USB_TYPE_VENDOR |
						USB_RECIP_DEVICE, 0x0000, 0x0000,
						xfer_buffer, xfer_length, HZ);
			kमुक्त(xfer_buffer);
			अगर (retval < 0)
				जाओ copy_error_message;
		पूर्ण अन्यथा अणु
			dev_err(&vub300->udev->dev,
				"not enough memory for xfer buffer to send"
				" INTERRUPT_PSEUDOCODE for %s %s\n", fw->data,
				vub300->vub_name);
			म_नकलन(vub300->vub_name,
				"SDIO interrupt pseudocode download failed",
				माप(vub300->vub_name));
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&vub300->udev->dev,
			"corrupt interrupt pseudocode in firmware %s %s\n",
			fw->data, vub300->vub_name);
		म_नकलन(vub300->vub_name, "corrupt interrupt pseudocode",
			माप(vub300->vub_name));
		वापस;
	पूर्ण
	ts += *data++;
	size -= 1;
	ts <<= 8;
	ts += *data++;
	size -= 1;
	अगर (ts < size) अणु
		u16 xfer_length = roundup_to_multiple_of_64(ts);
		u8 *xfer_buffer = kदो_स्मृति(xfer_length, GFP_KERNEL);
		अगर (xfer_buffer) अणु
			पूर्णांक retval;
			स_नकल(xfer_buffer, data, ts);
			स_रखो(xfer_buffer + ts, 0,
			       xfer_length - ts);
			size -= ts;
			data += ts;
			retval =
				usb_control_msg(vub300->udev,
						usb_sndctrlpipe(vub300->udev, 0),
						SET_TRANSFER_PSEUDOCODE,
						USB_सूची_OUT | USB_TYPE_VENDOR |
						USB_RECIP_DEVICE, 0x0000, 0x0000,
						xfer_buffer, xfer_length, HZ);
			kमुक्त(xfer_buffer);
			अगर (retval < 0)
				जाओ copy_error_message;
		पूर्ण अन्यथा अणु
			dev_err(&vub300->udev->dev,
				"not enough memory for xfer buffer to send"
				" TRANSFER_PSEUDOCODE for %s %s\n", fw->data,
				vub300->vub_name);
			म_नकलन(vub300->vub_name,
				"SDIO transfer pseudocode download failed",
				माप(vub300->vub_name));
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&vub300->udev->dev,
			"corrupt transfer pseudocode in firmware %s %s\n",
			fw->data, vub300->vub_name);
		म_नकलन(vub300->vub_name, "corrupt transfer pseudocode",
			माप(vub300->vub_name));
		वापस;
	पूर्ण
	रेजिस्टर_count += *data++;
	size -= 1;
	अगर (रेजिस्टर_count * 4 == size) अणु
		पूर्णांक I = vub300->dynamic_रेजिस्टर_count = रेजिस्टर_count;
		पूर्णांक i = 0;
		जबतक (I--) अणु
			अचिन्हित पूर्णांक func_num = 0;
			vub300->sdio_रेजिस्टर[i].func_num = *data++;
			size -= 1;
			func_num += *data++;
			size -= 1;
			func_num <<= 8;
			func_num += *data++;
			size -= 1;
			func_num <<= 8;
			func_num += *data++;
			size -= 1;
			vub300->sdio_रेजिस्टर[i].sdio_reg = func_num;
			vub300->sdio_रेजिस्टर[i].activate = 1;
			vub300->sdio_रेजिस्टर[i].prepared = 0;
			i += 1;
		पूर्ण
		dev_info(&vub300->udev->dev,
			 "initialized %d dynamic pseudocode registers\n",
			 vub300->dynamic_रेजिस्टर_count);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&vub300->udev->dev,
			"corrupt dynamic registers in firmware %s\n",
			vub300->vub_name);
		म_नकलन(vub300->vub_name, "corrupt dynamic registers",
			माप(vub300->vub_name));
		वापस;
	पूर्ण

	वापस;

copy_error_message:
	म_नकलन(vub300->vub_name, "SDIO pseudocode download failed",
		माप(vub300->vub_name));
पूर्ण

/*
 * अगर the binary containing the EMPTY PseuकरोCode can not be found
 * vub300->vub_name is set anyway in order to prevent an स्वतःmatic retry
 */
अटल व्योम करोwnload_offload_pseuकरोcode(काष्ठा vub300_mmc_host *vub300)
अणु
	काष्ठा mmc_card *card = vub300->mmc->card;
	पूर्णांक sdio_funcs = card->sdio_funcs;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक l = snम_लिखो(vub300->vub_name, माप(vub300->vub_name),
			 "vub_%04X%04X", card->cis.venकरोr, card->cis.device);
	पूर्णांक n = 0;
	पूर्णांक retval;
	क्रम (n = 0; n < sdio_funcs; n++) अणु
		काष्ठा sdio_func *sf = card->sdio_func[n];
		l += scnम_लिखो(vub300->vub_name + l,
			      माप(vub300->vub_name) - l, "_%04X%04X",
			      sf->venकरोr, sf->device);
	पूर्ण
	snम_लिखो(vub300->vub_name + l, माप(vub300->vub_name) - l, ".bin");
	dev_info(&vub300->udev->dev, "requesting offload firmware %s\n",
		 vub300->vub_name);
	retval = request_firmware(&fw, vub300->vub_name, &card->dev);
	अगर (retval < 0) अणु
		म_नकलन(vub300->vub_name, "vub_default.bin",
			माप(vub300->vub_name));
		retval = request_firmware(&fw, vub300->vub_name, &card->dev);
		अगर (retval < 0) अणु
			म_नकलन(vub300->vub_name,
				"no SDIO offload firmware found",
				माप(vub300->vub_name));
		पूर्ण अन्यथा अणु
			__करोwnload_offload_pseuकरोcode(vub300, fw);
			release_firmware(fw);
		पूर्ण
	पूर्ण अन्यथा अणु
		__करोwnload_offload_pseuकरोcode(vub300, fw);
		release_firmware(fw);
	पूर्ण
पूर्ण

अटल व्योम vub300_usb_bulk_msg_completion(काष्ठा urb *urb)
अणु				/* urb completion handler - hardirq */
	complete((काष्ठा completion *)urb->context);
पूर्ण

अटल पूर्णांक vub300_usb_bulk_msg(काष्ठा vub300_mmc_host *vub300,
			       अचिन्हित पूर्णांक pipe, व्योम *data, पूर्णांक len,
			       पूर्णांक *actual_length, पूर्णांक समयout_msecs)
अणु
	/* cmd_mutex is held by vub300_cmndwork_thपढ़ो */
	काष्ठा usb_device *usb_dev = vub300->udev;
	काष्ठा completion करोne;
	पूर्णांक retval;
	vub300->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!vub300->urb)
		वापस -ENOMEM;
	usb_fill_bulk_urb(vub300->urb, usb_dev, pipe, data, len,
			  vub300_usb_bulk_msg_completion, शून्य);
	init_completion(&करोne);
	vub300->urb->context = &करोne;
	vub300->urb->actual_length = 0;
	retval = usb_submit_urb(vub300->urb, GFP_KERNEL);
	अगर (unlikely(retval))
		जाओ out;
	अगर (!रुको_क्रम_completion_समयout
	    (&करोne, msecs_to_jअगरfies(समयout_msecs))) अणु
		retval = -ETIMEDOUT;
		usb_समाप्त_urb(vub300->urb);
	पूर्ण अन्यथा अणु
		retval = vub300->urb->status;
	पूर्ण
out:
	*actual_length = vub300->urb->actual_length;
	usb_मुक्त_urb(vub300->urb);
	vub300->urb = शून्य;
	वापस retval;
पूर्ण

अटल पूर्णांक __command_पढ़ो_data(काष्ठा vub300_mmc_host *vub300,
			       काष्ठा mmc_command *cmd, काष्ठा mmc_data *data)
अणु
	/* cmd_mutex is held by vub300_cmndwork_thपढ़ो */
	पूर्णांक linear_length = vub300->datasize;
	पूर्णांक padded_length = vub300->large_usb_packets ?
		((511 + linear_length) >> 9) << 9 :
		((63 + linear_length) >> 6) << 6;
	अगर ((padded_length == linear_length) || !pad_input_to_usb_pkt) अणु
		पूर्णांक result;
		अचिन्हित pipe;
		pipe = usb_rcvbulkpipe(vub300->udev, vub300->data_inp_ep);
		result = usb_sg_init(&vub300->sg_request, vub300->udev,
				     pipe, 0, data->sg,
				     data->sg_len, 0, GFP_KERNEL);
		अगर (result < 0) अणु
			usb_unlink_urb(vub300->command_out_urb);
			usb_unlink_urb(vub300->command_res_urb);
			cmd->error = result;
			data->bytes_xfered = 0;
			वापस 0;
		पूर्ण अन्यथा अणु
			vub300->sg_transfer_समयr.expires =
				jअगरfies + msecs_to_jअगरfies(2000 +
						  (linear_length / 16384));
			add_समयr(&vub300->sg_transfer_समयr);
			usb_sg_रुको(&vub300->sg_request);
			del_समयr(&vub300->sg_transfer_समयr);
			अगर (vub300->sg_request.status < 0) अणु
				cmd->error = vub300->sg_request.status;
				data->bytes_xfered = 0;
				वापस 0;
			पूर्ण अन्यथा अणु
				data->bytes_xfered = vub300->datasize;
				वापस linear_length;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 *buf = kदो_स्मृति(padded_length, GFP_KERNEL);
		अगर (buf) अणु
			पूर्णांक result;
			अचिन्हित pipe = usb_rcvbulkpipe(vub300->udev,
							vub300->data_inp_ep);
			पूर्णांक actual_length = 0;
			result = vub300_usb_bulk_msg(vub300, pipe, buf,
					     padded_length, &actual_length,
					     2000 + (padded_length / 16384));
			अगर (result < 0) अणु
				cmd->error = result;
				data->bytes_xfered = 0;
				kमुक्त(buf);
				वापस 0;
			पूर्ण अन्यथा अगर (actual_length < linear_length) अणु
				cmd->error = -EREMOTEIO;
				data->bytes_xfered = 0;
				kमुक्त(buf);
				वापस 0;
			पूर्ण अन्यथा अणु
				sg_copy_from_buffer(data->sg, data->sg_len, buf,
						    linear_length);
				kमुक्त(buf);
				data->bytes_xfered = vub300->datasize;
				वापस linear_length;
			पूर्ण
		पूर्ण अन्यथा अणु
			cmd->error = -ENOMEM;
			data->bytes_xfered = 0;
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __command_ग_लिखो_data(काष्ठा vub300_mmc_host *vub300,
				काष्ठा mmc_command *cmd, काष्ठा mmc_data *data)
अणु
	/* cmd_mutex is held by vub300_cmndwork_thपढ़ो */
	अचिन्हित pipe = usb_sndbulkpipe(vub300->udev, vub300->data_out_ep);
	पूर्णांक linear_length = vub300->datasize;
	पूर्णांक modulo_64_length = linear_length & 0x003F;
	पूर्णांक modulo_512_length = linear_length & 0x01FF;
	अगर (linear_length < 64) अणु
		पूर्णांक result;
		पूर्णांक actual_length;
		sg_copy_to_buffer(data->sg, data->sg_len,
				  vub300->padded_buffer,
				  माप(vub300->padded_buffer));
		स_रखो(vub300->padded_buffer + linear_length, 0,
		       माप(vub300->padded_buffer) - linear_length);
		result = vub300_usb_bulk_msg(vub300, pipe, vub300->padded_buffer,
					     माप(vub300->padded_buffer),
					     &actual_length, 2000 +
					     (माप(vub300->padded_buffer) /
					      16384));
		अगर (result < 0) अणु
			cmd->error = result;
			data->bytes_xfered = 0;
		पूर्ण अन्यथा अणु
			data->bytes_xfered = vub300->datasize;
		पूर्ण
	पूर्ण अन्यथा अगर ((!vub300->large_usb_packets && (0 < modulo_64_length)) ||
		    (vub300->large_usb_packets && (64 > modulo_512_length))
		) अणु		/* करोn't you just love these work-rounds */
		पूर्णांक padded_length = ((63 + linear_length) >> 6) << 6;
		u8 *buf = kदो_स्मृति(padded_length, GFP_KERNEL);
		अगर (buf) अणु
			पूर्णांक result;
			पूर्णांक actual_length;
			sg_copy_to_buffer(data->sg, data->sg_len, buf,
					  padded_length);
			स_रखो(buf + linear_length, 0,
			       padded_length - linear_length);
			result =
				vub300_usb_bulk_msg(vub300, pipe, buf,
						    padded_length, &actual_length,
						    2000 + padded_length / 16384);
			kमुक्त(buf);
			अगर (result < 0) अणु
				cmd->error = result;
				data->bytes_xfered = 0;
			पूर्ण अन्यथा अणु
				data->bytes_xfered = vub300->datasize;
			पूर्ण
		पूर्ण अन्यथा अणु
			cmd->error = -ENOMEM;
			data->bytes_xfered = 0;
		पूर्ण
	पूर्ण अन्यथा अणु		/* no data padding required */
		पूर्णांक result;
		अचिन्हित अक्षर buf[64 * 4];
		sg_copy_to_buffer(data->sg, data->sg_len, buf, माप(buf));
		result = usb_sg_init(&vub300->sg_request, vub300->udev,
				     pipe, 0, data->sg,
				     data->sg_len, 0, GFP_KERNEL);
		अगर (result < 0) अणु
			usb_unlink_urb(vub300->command_out_urb);
			usb_unlink_urb(vub300->command_res_urb);
			cmd->error = result;
			data->bytes_xfered = 0;
		पूर्ण अन्यथा अणु
			vub300->sg_transfer_समयr.expires =
				jअगरfies + msecs_to_jअगरfies(2000 +
							   linear_length / 16384);
			add_समयr(&vub300->sg_transfer_समयr);
			usb_sg_रुको(&vub300->sg_request);
			अगर (cmd->error) अणु
				data->bytes_xfered = 0;
			पूर्ण अन्यथा अणु
				del_समयr(&vub300->sg_transfer_समयr);
				अगर (vub300->sg_request.status < 0) अणु
					cmd->error = vub300->sg_request.status;
					data->bytes_xfered = 0;
				पूर्ण अन्यथा अणु
					data->bytes_xfered = vub300->datasize;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस linear_length;
पूर्ण

अटल व्योम __vub300_command_response(काष्ठा vub300_mmc_host *vub300,
				      काष्ठा mmc_command *cmd,
				      काष्ठा mmc_data *data, पूर्णांक data_length)
अणु
	/* cmd_mutex is held by vub300_cmndwork_thपढ़ो */
	दीर्घ respretval;
	पूर्णांक msec_समयout = 1000 + data_length / 4;
	respretval =
		रुको_क्रम_completion_समयout(&vub300->command_complete,
					    msecs_to_jअगरfies(msec_समयout));
	अगर (respretval == 0) अणु /* TIMED OUT */
		/* we करोn't know which of "out" and "res" अगर any failed */
		पूर्णांक result;
		vub300->usb_समयd_out = 1;
		usb_समाप्त_urb(vub300->command_out_urb);
		usb_समाप्त_urb(vub300->command_res_urb);
		cmd->error = -ETIMEDOUT;
		result = usb_lock_device_क्रम_reset(vub300->udev,
						   vub300->पूर्णांकerface);
		अगर (result == 0) अणु
			result = usb_reset_device(vub300->udev);
			usb_unlock_device(vub300->udev);
		पूर्ण
	पूर्ण अन्यथा अगर (respretval < 0) अणु
		/* we करोn't know which of "out" and "res" अगर any failed */
		usb_समाप्त_urb(vub300->command_out_urb);
		usb_समाप्त_urb(vub300->command_res_urb);
		cmd->error = respretval;
	पूर्ण अन्यथा अगर (cmd->error) अणु
		/*
		 * the error occurred sending the command
		 * or receiving the response
		 */
	पूर्ण अन्यथा अगर (vub300->command_out_urb->status) अणु
		vub300->usb_transport_fail = vub300->command_out_urb->status;
		cmd->error = -EPROTO == vub300->command_out_urb->status ?
			-ESHUTDOWN : vub300->command_out_urb->status;
	पूर्ण अन्यथा अगर (vub300->command_res_urb->status) अणु
		vub300->usb_transport_fail = vub300->command_res_urb->status;
		cmd->error = -EPROTO == vub300->command_res_urb->status ?
			-ESHUTDOWN : vub300->command_res_urb->status;
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type == 0x00) अणु
		/*
		 * the command completed successfully
		 * and there was no piggybacked data
		 */
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type == RESPONSE_ERROR) अणु
		cmd->error =
			vub300_response_error(vub300->resp.error.error_code);
		अगर (vub300->data)
			usb_sg_cancel(&vub300->sg_request);
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type == RESPONSE_PIGGYBACKED) अणु
		पूर्णांक offloaded_data_length =
			vub300->resp.common.header_size -
			माप(काष्ठा sd_रेजिस्टर_header);
		पूर्णांक रेजिस्टर_count = offloaded_data_length >> 3;
		पूर्णांक ri = 0;
		जबतक (रेजिस्टर_count--) अणु
			add_offloaded_reg(vub300, &vub300->resp.pig.reg[ri]);
			ri += 1;
		पूर्ण
		vub300->resp.common.header_size =
			माप(काष्ठा sd_रेजिस्टर_header);
		vub300->resp.common.header_type = 0x00;
		cmd->error = 0;
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type == RESPONSE_PIG_DISABLED) अणु
		पूर्णांक offloaded_data_length =
			vub300->resp.common.header_size -
			माप(काष्ठा sd_रेजिस्टर_header);
		पूर्णांक रेजिस्टर_count = offloaded_data_length >> 3;
		पूर्णांक ri = 0;
		जबतक (रेजिस्टर_count--) अणु
			add_offloaded_reg(vub300, &vub300->resp.pig.reg[ri]);
			ri += 1;
		पूर्ण
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irqs_queued) अणु
			vub300->irqs_queued += 1;
		पूर्ण अन्यथा अगर (vub300->irq_enabled) अणु
			vub300->irqs_queued += 1;
			vub300_queue_poll_work(vub300, 0);
		पूर्ण अन्यथा अणु
			vub300->irqs_queued += 1;
		पूर्ण
		vub300->irq_disabled = 1;
		mutex_unlock(&vub300->irq_mutex);
		vub300->resp.common.header_size =
			माप(काष्ठा sd_रेजिस्टर_header);
		vub300->resp.common.header_type = 0x00;
		cmd->error = 0;
	पूर्ण अन्यथा अगर (vub300->resp.common.header_type == RESPONSE_PIG_ENABLED) अणु
		पूर्णांक offloaded_data_length =
			vub300->resp.common.header_size -
			माप(काष्ठा sd_रेजिस्टर_header);
		पूर्णांक रेजिस्टर_count = offloaded_data_length >> 3;
		पूर्णांक ri = 0;
		जबतक (रेजिस्टर_count--) अणु
			add_offloaded_reg(vub300, &vub300->resp.pig.reg[ri]);
			ri += 1;
		पूर्ण
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irqs_queued) अणु
			vub300->irqs_queued += 1;
		पूर्ण अन्यथा अगर (vub300->irq_enabled) अणु
			vub300->irqs_queued += 1;
			vub300_queue_poll_work(vub300, 0);
		पूर्ण अन्यथा अणु
			vub300->irqs_queued += 1;
		पूर्ण
		vub300->irq_disabled = 0;
		mutex_unlock(&vub300->irq_mutex);
		vub300->resp.common.header_size =
			माप(काष्ठा sd_रेजिस्टर_header);
		vub300->resp.common.header_type = 0x00;
		cmd->error = 0;
	पूर्ण अन्यथा अणु
		cmd->error = -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम स्थिरruct_request_response(काष्ठा vub300_mmc_host *vub300,
				       काष्ठा mmc_command *cmd)
अणु
	पूर्णांक resp_len = vub300->resp_len;
	पूर्णांक less_cmd = (17 == resp_len) ? resp_len : resp_len - 1;
	पूर्णांक bytes = 3 & less_cmd;
	पूर्णांक words = less_cmd >> 2;
	u8 *r = vub300->resp.response.command_response;
	अगर (bytes == 3) अणु
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16)
			| (r[3 + (words << 2)] << 8);
	पूर्ण अन्यथा अगर (bytes == 2) अणु
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16);
	पूर्ण अन्यथा अगर (bytes == 1) अणु
		cmd->resp[words] = (r[1 + (words << 2)] << 24);
	पूर्ण
	जबतक (words-- > 0) अणु
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16)
			| (r[3 + (words << 2)] << 8)
			| (r[4 + (words << 2)] << 0);
	पूर्ण
	अगर ((cmd->opcode == 53) && (0x000000FF & cmd->resp[0]))
		cmd->resp[0] &= 0xFFFFFF00;
पूर्ण

/* this thपढ़ो runs only when there is an upper level command req outstanding */
अटल व्योम vub300_cmndwork_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vub300_mmc_host *vub300 =
		container_of(work, काष्ठा vub300_mmc_host, cmndwork);
	अगर (!vub300->पूर्णांकerface) अणु
		kref_put(&vub300->kref, vub300_delete);
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा mmc_request *req = vub300->req;
		काष्ठा mmc_command *cmd = vub300->cmd;
		काष्ठा mmc_data *data = vub300->data;
		पूर्णांक data_length;
		mutex_lock(&vub300->cmd_mutex);
		init_completion(&vub300->command_complete);
		अगर (likely(vub300->vub_name[0]) || !vub300->mmc->card) अणु
			/*
			 * the name of the EMPTY Pseuकरो firmware file
			 * is used as a flag to indicate that the file
			 * has been alपढ़ोy करोwnloaded to the VUB300 chip
			 */
		पूर्ण अन्यथा अगर (0 == vub300->mmc->card->sdio_funcs) अणु
			म_नकलन(vub300->vub_name, "SD memory device",
				माप(vub300->vub_name));
		पूर्ण अन्यथा अणु
			करोwnload_offload_pseuकरोcode(vub300);
		पूर्ण
		send_command(vub300);
		अगर (!data)
			data_length = 0;
		अन्यथा अगर (MMC_DATA_READ & data->flags)
			data_length = __command_पढ़ो_data(vub300, cmd, data);
		अन्यथा
			data_length = __command_ग_लिखो_data(vub300, cmd, data);
		__vub300_command_response(vub300, cmd, data, data_length);
		vub300->req = शून्य;
		vub300->cmd = शून्य;
		vub300->data = शून्य;
		अगर (cmd->error) अणु
			अगर (cmd->error == -ENOMEDIUM)
				check_vub300_port_status(vub300);
			mutex_unlock(&vub300->cmd_mutex);
			mmc_request_करोne(vub300->mmc, req);
			kref_put(&vub300->kref, vub300_delete);
			वापस;
		पूर्ण अन्यथा अणु
			स्थिरruct_request_response(vub300, cmd);
			vub300->resp_len = 0;
			mutex_unlock(&vub300->cmd_mutex);
			kref_put(&vub300->kref, vub300_delete);
			mmc_request_करोne(vub300->mmc, req);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक examine_cyclic_buffer(काष्ठा vub300_mmc_host *vub300,
				 काष्ठा mmc_command *cmd, u8 Function)
अणु
	/* cmd_mutex is held by vub300_mmc_request */
	u8 cmd0 = 0xFF & (cmd->arg >> 24);
	u8 cmd1 = 0xFF & (cmd->arg >> 16);
	u8 cmd2 = 0xFF & (cmd->arg >> 8);
	u8 cmd3 = 0xFF & (cmd->arg >> 0);
	पूर्णांक first = MAXREGMASK & vub300->fn[Function].offload_poपूर्णांक;
	काष्ठा offload_रेजिस्टरs_access *rf = &vub300->fn[Function].reg[first];
	अगर (cmd0 == rf->command_byte[0] &&
	    cmd1 == rf->command_byte[1] &&
	    cmd2 == rf->command_byte[2] &&
	    cmd3 == rf->command_byte[3]) अणु
		u8 checksum = 0x00;
		cmd->resp[1] = checksum << 24;
		cmd->resp[0] = (rf->Respond_Byte[0] << 24)
			| (rf->Respond_Byte[1] << 16)
			| (rf->Respond_Byte[2] << 8)
			| (rf->Respond_Byte[3] << 0);
		vub300->fn[Function].offload_poपूर्णांक += 1;
		vub300->fn[Function].offload_count -= 1;
		vub300->total_offload_count -= 1;
		वापस 1;
	पूर्ण अन्यथा अणु
		पूर्णांक delta = 1;	/* because it करोes not match the first one */
		u8 रेजिस्टर_count = vub300->fn[Function].offload_count - 1;
		u32 रेजिस्टर_poपूर्णांक = vub300->fn[Function].offload_poपूर्णांक + 1;
		जबतक (0 < रेजिस्टर_count) अणु
			पूर्णांक poपूर्णांक = MAXREGMASK & रेजिस्टर_poपूर्णांक;
			काष्ठा offload_रेजिस्टरs_access *r =
				&vub300->fn[Function].reg[poपूर्णांक];
			अगर (cmd0 == r->command_byte[0] &&
			    cmd1 == r->command_byte[1] &&
			    cmd2 == r->command_byte[2] &&
			    cmd3 == r->command_byte[3]) अणु
				u8 checksum = 0x00;
				cmd->resp[1] = checksum << 24;
				cmd->resp[0] = (r->Respond_Byte[0] << 24)
					| (r->Respond_Byte[1] << 16)
					| (r->Respond_Byte[2] << 8)
					| (r->Respond_Byte[3] << 0);
				vub300->fn[Function].offload_poपूर्णांक += delta;
				vub300->fn[Function].offload_count -= delta;
				vub300->total_offload_count -= delta;
				वापस 1;
			पूर्ण अन्यथा अणु
				रेजिस्टर_poपूर्णांक += 1;
				रेजिस्टर_count -= 1;
				delta += 1;
				जारी;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक satisfy_request_from_offloaded_data(काष्ठा vub300_mmc_host *vub300,
					       काष्ठा mmc_command *cmd)
अणु
	/* cmd_mutex is held by vub300_mmc_request */
	u8 regs = vub300->dynamic_रेजिस्टर_count;
	u8 i = 0;
	u8 func = FUN(cmd);
	u32 reg = REG(cmd);
	जबतक (0 < regs--) अणु
		अगर ((vub300->sdio_रेजिस्टर[i].func_num == func) &&
		    (vub300->sdio_रेजिस्टर[i].sdio_reg == reg)) अणु
			अगर (!vub300->sdio_रेजिस्टर[i].prepared) अणु
				वापस 0;
			पूर्ण अन्यथा अगर ((0x80000000 & cmd->arg) == 0x80000000) अणु
				/*
				 * a ग_लिखो to a dynamic रेजिस्टर
				 * nullअगरies our offloaded value
				 */
				vub300->sdio_रेजिस्टर[i].prepared = 0;
				वापस 0;
			पूर्ण अन्यथा अणु
				u8 checksum = 0x00;
				u8 rsp0 = 0x00;
				u8 rsp1 = 0x00;
				u8 rsp2 = vub300->sdio_रेजिस्टर[i].response;
				u8 rsp3 = vub300->sdio_रेजिस्टर[i].regvalue;
				vub300->sdio_रेजिस्टर[i].prepared = 0;
				cmd->resp[1] = checksum << 24;
				cmd->resp[0] = (rsp0 << 24)
					| (rsp1 << 16)
					| (rsp2 << 8)
					| (rsp3 << 0);
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			i += 1;
			जारी;
		पूर्ण
	पूर्ण
	अगर (vub300->total_offload_count == 0)
		वापस 0;
	अन्यथा अगर (vub300->fn[func].offload_count == 0)
		वापस 0;
	अन्यथा
		वापस examine_cyclic_buffer(vub300, cmd, func);
पूर्ण

अटल व्योम vub300_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु				/* NOT irq */
	काष्ठा mmc_command *cmd = req->cmd;
	काष्ठा vub300_mmc_host *vub300 = mmc_priv(mmc);
	अगर (!vub300->पूर्णांकerface) अणु
		cmd->error = -ESHUTDOWN;
		mmc_request_करोne(mmc, req);
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा mmc_data *data = req->data;
		अगर (!vub300->card_घातered) अणु
			cmd->error = -ENOMEDIUM;
			mmc_request_करोne(mmc, req);
			वापस;
		पूर्ण
		अगर (!vub300->card_present) अणु
			cmd->error = -ENOMEDIUM;
			mmc_request_करोne(mmc, req);
			वापस;
		पूर्ण
		अगर (vub300->usb_transport_fail) अणु
			cmd->error = vub300->usb_transport_fail;
			mmc_request_करोne(mmc, req);
			वापस;
		पूर्ण
		अगर (!vub300->पूर्णांकerface) अणु
			cmd->error = -ENODEV;
			mmc_request_करोne(mmc, req);
			वापस;
		पूर्ण
		kref_get(&vub300->kref);
		mutex_lock(&vub300->cmd_mutex);
		mod_समयr(&vub300->inactivity_समयr, jअगरfies + HZ);
		/*
		 * क्रम perक्रमmance we have to वापस immediately
		 * अगर the requested data has been offloaded
		 */
		अगर (cmd->opcode == 52 &&
		    satisfy_request_from_offloaded_data(vub300, cmd)) अणु
			cmd->error = 0;
			mutex_unlock(&vub300->cmd_mutex);
			kref_put(&vub300->kref, vub300_delete);
			mmc_request_करोne(mmc, req);
			वापस;
		पूर्ण अन्यथा अणु
			vub300->cmd = cmd;
			vub300->req = req;
			vub300->data = data;
			अगर (data)
				vub300->datasize = data->blksz * data->blocks;
			अन्यथा
				vub300->datasize = 0;
			vub300_queue_cmnd_work(vub300);
			mutex_unlock(&vub300->cmd_mutex);
			kref_put(&vub300->kref, vub300_delete);
			/*
			 * the kernel lock diagnostics complain
			 * अगर the cmd_mutex * is "passed on"
			 * to the cmndwork thपढ़ो,
			 * so we must release it now
			 * and re-acquire it in the cmndwork thपढ़ो
			 */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __set_घड़ी_speed(काष्ठा vub300_mmc_host *vub300, u8 buf[8],
			      काष्ठा mmc_ios *ios)
अणु
	पूर्णांक buf_array_size = 8; /* ARRAY_SIZE(buf) करोes not work !!! */
	पूर्णांक retval;
	u32 kHzClock;
	अगर (ios->घड़ी >= 48000000)
		kHzClock = 48000;
	अन्यथा अगर (ios->घड़ी >= 24000000)
		kHzClock = 24000;
	अन्यथा अगर (ios->घड़ी >= 20000000)
		kHzClock = 20000;
	अन्यथा अगर (ios->घड़ी >= 15000000)
		kHzClock = 15000;
	अन्यथा अगर (ios->घड़ी >= 200000)
		kHzClock = 200;
	अन्यथा
		kHzClock = 0;
	अणु
		पूर्णांक i;
		u64 c = kHzClock;
		क्रम (i = 0; i < buf_array_size; i++) अणु
			buf[i] = c;
			c >>= 8;
		पूर्ण
	पूर्ण
	retval =
		usb_control_msg(vub300->udev, usb_sndctrlpipe(vub300->udev, 0),
				SET_CLOCK_SPEED,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x00, 0x00, buf, buf_array_size, HZ);
	अगर (retval != 8) अणु
		dev_err(&vub300->udev->dev, "SET_CLOCK_SPEED"
			" %dkHz failed with retval=%d\n", kHzClock, retval);
	पूर्ण अन्यथा अणु
		dev_dbg(&vub300->udev->dev, "SET_CLOCK_SPEED"
			" %dkHz\n", kHzClock);
	पूर्ण
पूर्ण

अटल व्योम vub300_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = mmc_priv(mmc);
	अगर (!vub300->पूर्णांकerface)
		वापस;
	kref_get(&vub300->kref);
	mutex_lock(&vub300->cmd_mutex);
	अगर ((ios->घातer_mode == MMC_POWER_OFF) && vub300->card_घातered) अणु
		vub300->card_घातered = 0;
		usb_control_msg(vub300->udev, usb_sndctrlpipe(vub300->udev, 0),
				SET_SD_POWER,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, शून्य, 0, HZ);
		/* must रुको क्रम the VUB300 u-proc to boot up */
		msleep(600);
	पूर्ण अन्यथा अगर ((ios->घातer_mode == MMC_POWER_UP) && !vub300->card_घातered) अणु
		usb_control_msg(vub300->udev, usb_sndctrlpipe(vub300->udev, 0),
				SET_SD_POWER,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0001, 0x0000, शून्य, 0, HZ);
		msleep(600);
		vub300->card_घातered = 1;
	पूर्ण अन्यथा अगर (ios->घातer_mode == MMC_POWER_ON) अणु
		u8 *buf = kदो_स्मृति(8, GFP_KERNEL);
		अगर (buf) अणु
			__set_घड़ी_speed(vub300, buf, ios);
			kमुक्त(buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this should mean no change of state */
	पूर्ण
	mutex_unlock(&vub300->cmd_mutex);
	kref_put(&vub300->kref, vub300_delete);
पूर्ण

अटल पूर्णांक vub300_mmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा vub300_mmc_host *vub300 = mmc_priv(mmc);
	वापस vub300->पढ़ो_only;
पूर्ण

अटल व्योम vub300_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = mmc_priv(mmc);
	अगर (!vub300->पूर्णांकerface)
		वापस;
	kref_get(&vub300->kref);
	अगर (enable) अणु
		mutex_lock(&vub300->irq_mutex);
		अगर (vub300->irqs_queued) अणु
			vub300->irqs_queued -= 1;
			mmc_संकेत_sdio_irq(vub300->mmc);
		पूर्ण अन्यथा अगर (vub300->irq_disabled) अणु
			vub300->irq_disabled = 0;
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		पूर्ण अन्यथा अगर (vub300->irq_enabled) अणु
			/* this should not happen, so we will just ignore it */
		पूर्ण अन्यथा अणु
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		पूर्ण
		mutex_unlock(&vub300->irq_mutex);
	पूर्ण अन्यथा अणु
		vub300->irq_enabled = 0;
	पूर्ण
	kref_put(&vub300->kref, vub300_delete);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops vub300_mmc_ops = अणु
	.request = vub300_mmc_request,
	.set_ios = vub300_mmc_set_ios,
	.get_ro = vub300_mmc_get_ro,
	.enable_sdio_irq = vub300_enable_sdio_irq,
पूर्ण;

अटल पूर्णांक vub300_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			स्थिर काष्ठा usb_device_id *id)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_device *udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	पूर्णांक i;
	पूर्णांक retval = -ENOMEM;
	काष्ठा urb *command_out_urb;
	काष्ठा urb *command_res_urb;
	काष्ठा mmc_host *mmc;
	अक्षर manufacturer[48];
	अक्षर product[32];
	अक्षर serial_number[32];
	usb_string(udev, udev->descriptor.iManufacturer, manufacturer,
		   माप(manufacturer));
	usb_string(udev, udev->descriptor.iProduct, product, माप(product));
	usb_string(udev, udev->descriptor.iSerialNumber, serial_number,
		   माप(serial_number));
	dev_info(&udev->dev, "probing VID:PID(%04X:%04X) %s %s %s\n",
		 le16_to_cpu(udev->descriptor.idVenकरोr),
		 le16_to_cpu(udev->descriptor.idProduct),
		 manufacturer, product, serial_number);
	command_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!command_out_urb) अणु
		retval = -ENOMEM;
		जाओ error0;
	पूर्ण
	command_res_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!command_res_urb) अणु
		retval = -ENOMEM;
		जाओ error1;
	पूर्ण
	/* this also allocates memory क्रम our VUB300 mmc host device */
	mmc = mmc_alloc_host(माप(काष्ठा vub300_mmc_host), &udev->dev);
	अगर (!mmc) अणु
		retval = -ENOMEM;
		dev_err(&udev->dev, "not enough memory for the mmc_host\n");
		जाओ error4;
	पूर्ण
	/* MMC core transfer sizes tunable parameters */
	mmc->caps = 0;
	अगर (!क्रमce_1_bit_data_xfers)
		mmc->caps |= MMC_CAP_4_BIT_DATA;
	अगर (!क्रमce_polling_क्रम_irqs)
		mmc->caps |= MMC_CAP_SDIO_IRQ;
	mmc->caps &= ~MMC_CAP_NEEDS_POLL;
	/*
	 * MMC_CAP_NEEDS_POLL causes core.c:mmc_rescan() to poll
	 * क्रम devices which results in spurious CMD7's being
	 * issued which stops some SDIO cards from working
	 */
	अगर (limit_speed_to_24_MHz) अणु
		mmc->caps |= MMC_CAP_MMC_HIGHSPEED;
		mmc->caps |= MMC_CAP_SD_HIGHSPEED;
		mmc->f_max = 24000000;
		dev_info(&udev->dev, "limiting SDIO speed to 24_MHz\n");
	पूर्ण अन्यथा अणु
		mmc->caps |= MMC_CAP_MMC_HIGHSPEED;
		mmc->caps |= MMC_CAP_SD_HIGHSPEED;
		mmc->f_max = 48000000;
	पूर्ण
	mmc->f_min = 200000;
	mmc->max_blk_count = 511;
	mmc->max_blk_size = 512;
	mmc->max_segs = 128;
	अगर (क्रमce_max_req_size)
		mmc->max_req_size = क्रमce_max_req_size * 1024;
	अन्यथा
		mmc->max_req_size = 64 * 1024;
	mmc->max_seg_size = mmc->max_req_size;
	mmc->ocr_avail = 0;
	mmc->ocr_avail |= MMC_VDD_165_195;
	mmc->ocr_avail |= MMC_VDD_20_21;
	mmc->ocr_avail |= MMC_VDD_21_22;
	mmc->ocr_avail |= MMC_VDD_22_23;
	mmc->ocr_avail |= MMC_VDD_23_24;
	mmc->ocr_avail |= MMC_VDD_24_25;
	mmc->ocr_avail |= MMC_VDD_25_26;
	mmc->ocr_avail |= MMC_VDD_26_27;
	mmc->ocr_avail |= MMC_VDD_27_28;
	mmc->ocr_avail |= MMC_VDD_28_29;
	mmc->ocr_avail |= MMC_VDD_29_30;
	mmc->ocr_avail |= MMC_VDD_30_31;
	mmc->ocr_avail |= MMC_VDD_31_32;
	mmc->ocr_avail |= MMC_VDD_32_33;
	mmc->ocr_avail |= MMC_VDD_33_34;
	mmc->ocr_avail |= MMC_VDD_34_35;
	mmc->ocr_avail |= MMC_VDD_35_36;
	mmc->ops = &vub300_mmc_ops;
	vub300 = mmc_priv(mmc);
	vub300->mmc = mmc;
	vub300->card_घातered = 0;
	vub300->bus_width = 0;
	vub300->cmnd.head.block_size[0] = 0x00;
	vub300->cmnd.head.block_size[1] = 0x00;
	vub300->app_spec = 0;
	mutex_init(&vub300->cmd_mutex);
	mutex_init(&vub300->irq_mutex);
	vub300->command_out_urb = command_out_urb;
	vub300->command_res_urb = command_res_urb;
	vub300->usb_समयd_out = 0;
	vub300->dynamic_रेजिस्टर_count = 0;

	क्रम (i = 0; i < ARRAY_SIZE(vub300->fn); i++) अणु
		vub300->fn[i].offload_poपूर्णांक = 0;
		vub300->fn[i].offload_count = 0;
	पूर्ण

	vub300->total_offload_count = 0;
	vub300->irq_enabled = 0;
	vub300->irq_disabled = 0;
	vub300->irqs_queued = 0;

	क्रम (i = 0; i < ARRAY_SIZE(vub300->sdio_रेजिस्टर); i++)
		vub300->sdio_रेजिस्टर[i++].activate = 0;

	vub300->udev = udev;
	vub300->पूर्णांकerface = पूर्णांकerface;
	vub300->cmnd_res_ep = 0;
	vub300->cmnd_out_ep = 0;
	vub300->data_inp_ep = 0;
	vub300->data_out_ep = 0;

	क्रम (i = 0; i < ARRAY_SIZE(vub300->fbs); i++)
		vub300->fbs[i] = 512;

	/*
	 *      set up the endpoपूर्णांक inक्रमmation
	 *
	 * use the first pair of bulk-in and bulk-out
	 *     endpoपूर्णांकs क्रम Command/Response+Interrupt
	 *
	 * use the second pair of bulk-in and bulk-out
	 *     endpoपूर्णांकs क्रम Data In/Out
	 */
	vub300->large_usb_packets = 0;
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक =
			&अगरace_desc->endpoपूर्णांक[i].desc;
		dev_info(&vub300->udev->dev,
			 "vub300 testing %s EndPoint(%d) %02X\n",
			 usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक) ? "BULK IN" :
			 usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक) ? "BULK OUT" :
			 "UNKNOWN", i, endpoपूर्णांक->bEndpoपूर्णांकAddress);
		अगर (endpoपूर्णांक->wMaxPacketSize > 64)
			vub300->large_usb_packets = 1;
		अगर (usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			अगर (!vub300->cmnd_res_ep) अणु
				vub300->cmnd_res_ep =
					endpoपूर्णांक->bEndpoपूर्णांकAddress;
			पूर्ण अन्यथा अगर (!vub300->data_inp_ep) अणु
				vub300->data_inp_ep =
					endpoपूर्णांक->bEndpoपूर्णांकAddress;
			पूर्ण अन्यथा अणु
				dev_warn(&vub300->udev->dev,
					 "ignoring"
					 " unexpected bulk_in endpoint");
			पूर्ण
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक)) अणु
			अगर (!vub300->cmnd_out_ep) अणु
				vub300->cmnd_out_ep =
					endpoपूर्णांक->bEndpoपूर्णांकAddress;
			पूर्ण अन्यथा अगर (!vub300->data_out_ep) अणु
				vub300->data_out_ep =
					endpoपूर्णांक->bEndpoपूर्णांकAddress;
			पूर्ण अन्यथा अणु
				dev_warn(&vub300->udev->dev,
					 "ignoring"
					 " unexpected bulk_out endpoint");
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&vub300->udev->dev,
				 "vub300 ignoring EndPoint(%d) %02X", i,
				 endpoपूर्णांक->bEndpoपूर्णांकAddress);
		पूर्ण
	पूर्ण
	अगर (vub300->cmnd_res_ep && vub300->cmnd_out_ep &&
	    vub300->data_inp_ep && vub300->data_out_ep) अणु
		dev_info(&vub300->udev->dev,
			 "vub300 %s packets"
			 " using EndPoints %02X %02X %02X %02X\n",
			 vub300->large_usb_packets ? "LARGE" : "SMALL",
			 vub300->cmnd_out_ep, vub300->cmnd_res_ep,
			 vub300->data_out_ep, vub300->data_inp_ep);
		/* we have the expected EndPoपूर्णांकs */
	पूर्ण अन्यथा अणु
		dev_err(&vub300->udev->dev,
		    "Could not find two sets of bulk-in/out endpoint pairs\n");
		retval = -EINVAL;
		जाओ error5;
	पूर्ण
	retval =
		usb_control_msg(vub300->udev, usb_rcvctrlpipe(vub300->udev, 0),
				GET_HC_INF0,
				USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, &vub300->hc_info,
				माप(vub300->hc_info), HZ);
	अगर (retval < 0)
		जाओ error5;
	retval =
		usb_control_msg(vub300->udev, usb_rcvctrlpipe(vub300->udev, 0),
				SET_ROM_WAIT_STATES,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				firmware_rom_रुको_states, 0x0000, शून्य, 0, HZ);
	अगर (retval < 0)
		जाओ error5;
	dev_info(&vub300->udev->dev,
		 "operating_mode = %s %s %d MHz %s %d byte USB packets\n",
		 (mmc->caps & MMC_CAP_SDIO_IRQ) ? "IRQs" : "POLL",
		 (mmc->caps & MMC_CAP_4_BIT_DATA) ? "4-bit" : "1-bit",
		 mmc->f_max / 1000000,
		 pad_input_to_usb_pkt ? "padding input data to" : "with",
		 vub300->large_usb_packets ? 512 : 64);
	retval =
		usb_control_msg(vub300->udev, usb_rcvctrlpipe(vub300->udev, 0),
				GET_SYSTEM_PORT_STATUS,
				USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, &vub300->प्रणाली_port_status,
				माप(vub300->प्रणाली_port_status), HZ);
	अगर (retval < 0) अणु
		जाओ error4;
	पूर्ण अन्यथा अगर (माप(vub300->प्रणाली_port_status) == retval) अणु
		vub300->card_present =
			(0x0001 & vub300->प्रणाली_port_status.port_flags) ? 1 : 0;
		vub300->पढ़ो_only =
			(0x0010 & vub300->प्रणाली_port_status.port_flags) ? 1 : 0;
	पूर्ण अन्यथा अणु
		जाओ error4;
	पूर्ण
	usb_set_पूर्णांकfdata(पूर्णांकerface, vub300);
	INIT_DELAYED_WORK(&vub300->pollwork, vub300_pollwork_thपढ़ो);
	INIT_WORK(&vub300->cmndwork, vub300_cmndwork_thपढ़ो);
	INIT_WORK(&vub300->deadwork, vub300_deadwork_thपढ़ो);
	kref_init(&vub300->kref);
	समयr_setup(&vub300->sg_transfer_समयr, vub300_sg_समयd_out, 0);
	kref_get(&vub300->kref);
	समयr_setup(&vub300->inactivity_समयr,
		    vub300_inactivity_समयr_expired, 0);
	vub300->inactivity_समयr.expires = jअगरfies + HZ;
	add_समयr(&vub300->inactivity_समयr);
	अगर (vub300->card_present)
		dev_info(&vub300->udev->dev,
			 "USB vub300 remote SDIO host controller[%d]"
			 "connected with SD/SDIO card inserted\n",
			 पूर्णांकerface_to_InterfaceNumber(पूर्णांकerface));
	अन्यथा
		dev_info(&vub300->udev->dev,
			 "USB vub300 remote SDIO host controller[%d]"
			 "connected with no SD/SDIO card inserted\n",
			 पूर्णांकerface_to_InterfaceNumber(पूर्णांकerface));
	mmc_add_host(mmc);
	वापस 0;
error5:
	mmc_मुक्त_host(mmc);
	/*
	 * and hence also मुक्तs vub300
	 * which is contained at the end of काष्ठा mmc
	 */
error4:
	usb_मुक्त_urb(command_res_urb);
error1:
	usb_मुक्त_urb(command_out_urb);
error0:
	usb_put_dev(udev);
	वापस retval;
पूर्ण

अटल व्योम vub300_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!vub300 || !vub300->mmc) अणु
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा mmc_host *mmc = vub300->mmc;
		अगर (!vub300->mmc) अणु
			वापस;
		पूर्ण अन्यथा अणु
			पूर्णांक अगरnum = पूर्णांकerface_to_InterfaceNumber(पूर्णांकerface);
			usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
			/* prevent more I/O from starting */
			vub300->पूर्णांकerface = शून्य;
			kref_put(&vub300->kref, vub300_delete);
			mmc_हटाओ_host(mmc);
			pr_info("USB vub300 remote SDIO host controller[%d]"
				" now disconnected", अगरnum);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक vub300_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vub300_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा vub300_suspend शून्य
#घोषणा vub300_resume शून्य
#पूर्ण_अगर
अटल पूर्णांक vub300_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = usb_get_पूर्णांकfdata(पूर्णांकf);
	mutex_lock(&vub300->cmd_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vub300_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु				/* NOT irq */
	काष्ठा vub300_mmc_host *vub300 = usb_get_पूर्णांकfdata(पूर्णांकf);
	/* we are sure no URBs are active - no locking needed */
	vub300->errors = -EPIPE;
	mutex_unlock(&vub300->cmd_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver vub300_driver = अणु
	.name = "vub300",
	.probe = vub300_probe,
	.disconnect = vub300_disconnect,
	.suspend = vub300_suspend,
	.resume = vub300_resume,
	.pre_reset = vub300_pre_reset,
	.post_reset = vub300_post_reset,
	.id_table = vub300_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

अटल पूर्णांक __init vub300_init(व्योम)
अणु				/* NOT irq */
	पूर्णांक result;

	pr_info("VUB300 Driver rom wait states = %02X irqpoll timeout = %04X",
		firmware_rom_रुको_states, 0x0FFFF & firmware_irqpoll_समयout);
	cmndworkqueue = create_singlethपढ़ो_workqueue("kvub300c");
	अगर (!cmndworkqueue) अणु
		pr_err("not enough memory for the REQUEST workqueue");
		result = -ENOMEM;
		जाओ out1;
	पूर्ण
	pollworkqueue = create_singlethपढ़ो_workqueue("kvub300p");
	अगर (!pollworkqueue) अणु
		pr_err("not enough memory for the IRQPOLL workqueue");
		result = -ENOMEM;
		जाओ out2;
	पूर्ण
	deadworkqueue = create_singlethपढ़ो_workqueue("kvub300d");
	अगर (!deadworkqueue) अणु
		pr_err("not enough memory for the EXPIRED workqueue");
		result = -ENOMEM;
		जाओ out3;
	पूर्ण
	result = usb_रेजिस्टर(&vub300_driver);
	अगर (result) अणु
		pr_err("usb_register failed. Error number %d", result);
		जाओ out4;
	पूर्ण
	वापस 0;
out4:
	destroy_workqueue(deadworkqueue);
out3:
	destroy_workqueue(pollworkqueue);
out2:
	destroy_workqueue(cmndworkqueue);
out1:
	वापस result;
पूर्ण

अटल व्योम __निकास vub300_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&vub300_driver);
	flush_workqueue(cmndworkqueue);
	flush_workqueue(pollworkqueue);
	flush_workqueue(deadworkqueue);
	destroy_workqueue(cmndworkqueue);
	destroy_workqueue(pollworkqueue);
	destroy_workqueue(deadworkqueue);
पूर्ण

module_init(vub300_init);
module_निकास(vub300_निकास);

MODULE_AUTHOR("Tony Olech <tony.olech@elandigitalsystems.com>");
MODULE_DESCRIPTION("VUB300 USB to SD/MMC/SDIO adapter driver");
MODULE_LICENSE("GPL");
