<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************
 *
 *     kaweth.c - driver क्रम KL5KUSB101 based USB->Ethernet
 *
 *     (c) 2000 Interlan Communications
 *     (c) 2000 Stephane Alnet
 *     (C) 2001 Brad Hards
 *     (C) 2002 Oliver Neukum
 *
 *     Original author: The Zapman <zapman@पूर्णांकerlan.net>
 *     Inspired by, and much credit goes to Michael Rothwell
 *     <rothwell@पूर्णांकerlan.net> क्रम the test equipment, help, and patience
 *     Based off of (and with thanks to) Petko Manolov's pegaus.c driver.
 *     Also many thanks to Joel Silverman and Ed Surprenant at Kawasaki
 *     क्रम providing the firmware and driver resources.
 *
 ****************************************************************/

/* TODO:
 * Develop test procedures क्रम USB net पूर्णांकerfaces
 * Run test procedures
 * Fix bugs from previous two steps
 * Snoop other OSs क्रम any tricks we're not करोing
 * Reduce arbitrary समयouts
 * Smart multicast support
 * Temporary MAC change support
 * Tunable SOFs parameter - ioctl()?
 * Ethernet stats collection
 * Code क्रमmatting improvements
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/रुको.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

#अघोषित DEBUG

#घोषणा KAWETH_MTU			1514
#घोषणा KAWETH_BUF_SIZE			1664
#घोषणा KAWETH_TX_TIMEOUT		(5 * HZ)
#घोषणा KAWETH_SCRATCH_SIZE		32
#घोषणा KAWETH_FIRMWARE_BUF_SIZE	4096
#घोषणा KAWETH_CONTROL_TIMEOUT		(30000)

#घोषणा KAWETH_STATUS_BROKEN		0x0000001
#घोषणा KAWETH_STATUS_CLOSING		0x0000002
#घोषणा KAWETH_STATUS_SUSPENDING	0x0000004

#घोषणा KAWETH_STATUS_BLOCKED (KAWETH_STATUS_CLOSING | KAWETH_STATUS_SUSPENDING)

#घोषणा KAWETH_PACKET_FILTER_PROMISCUOUS	0x01
#घोषणा KAWETH_PACKET_FILTER_ALL_MULTICAST	0x02
#घोषणा KAWETH_PACKET_FILTER_सूचीECTED		0x04
#घोषणा KAWETH_PACKET_FILTER_BROADCAST		0x08
#घोषणा KAWETH_PACKET_FILTER_MULTICAST		0x10

/* Table 7 */
#घोषणा KAWETH_COMMAND_GET_ETHERNET_DESC	0x00
#घोषणा KAWETH_COMMAND_MULTICAST_FILTERS        0x01
#घोषणा KAWETH_COMMAND_SET_PACKET_FILTER	0x02
#घोषणा KAWETH_COMMAND_STATISTICS               0x03
#घोषणा KAWETH_COMMAND_SET_TEMP_MAC     	0x06
#घोषणा KAWETH_COMMAND_GET_TEMP_MAC             0x07
#घोषणा KAWETH_COMMAND_SET_URB_SIZE		0x08
#घोषणा KAWETH_COMMAND_SET_SOFS_WAIT		0x09
#घोषणा KAWETH_COMMAND_SCAN			0xFF

#घोषणा KAWETH_SOFS_TO_WAIT			0x05

#घोषणा INTBUFFERSIZE				4

#घोषणा STATE_OFFSET				0
#घोषणा STATE_MASK				0x40
#घोषणा	STATE_SHIFT				5

#घोषणा IS_BLOCKED(s) (s & KAWETH_STATUS_BLOCKED)


MODULE_AUTHOR("Michael Zappe <zapman@interlan.net>, Stephane Alnet <stephane@u-picardie.fr>, Brad Hards <bhards@bigpond.net.au> and Oliver Neukum <oliver@neukum.org>");
MODULE_DESCRIPTION("KL5USB101 USB Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("kaweth/new_code.bin");
MODULE_FIRMWARE("kaweth/new_code_fix.bin");
MODULE_FIRMWARE("kaweth/trigger_code.bin");
MODULE_FIRMWARE("kaweth/trigger_code_fix.bin");

अटल स्थिर अक्षर driver_name[] = "kaweth";

अटल पूर्णांक kaweth_probe(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id	/* from id_table */
	);
अटल व्योम kaweth_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
अटल पूर्णांक kaweth_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
अटल पूर्णांक kaweth_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/****************************************************************
 *     usb_device_id
 ****************************************************************/
अटल स्थिर काष्ठा usb_device_id usb_klsi_table[] = अणु
	अणु USB_DEVICE(0x03e8, 0x0008) पूर्ण, /* AOX Endpoपूर्णांकs USB Ethernet */
	अणु USB_DEVICE(0x04bb, 0x0901) पूर्ण, /* I-O DATA USB-ET/T */
	अणु USB_DEVICE(0x0506, 0x03e8) पूर्ण, /* 3Com 3C19250 */
	अणु USB_DEVICE(0x0506, 0x11f8) पूर्ण, /* 3Com 3C460 */
	अणु USB_DEVICE(0x0557, 0x2002) पूर्ण, /* ATEN USB Ethernet */
	अणु USB_DEVICE(0x0557, 0x4000) पूर्ण, /* D-Link DSB-650C */
	अणु USB_DEVICE(0x0565, 0x0002) पूर्ण, /* Peracom Enet */
	अणु USB_DEVICE(0x0565, 0x0003) पूर्ण, /* Optus@Home UEP1045A */
	अणु USB_DEVICE(0x0565, 0x0005) पूर्ण, /* Peracom Enet2 */
	अणु USB_DEVICE(0x05e9, 0x0008) पूर्ण, /* KLSI KL5KUSB101B */
	अणु USB_DEVICE(0x05e9, 0x0009) पूर्ण, /* KLSI KL5KUSB101B (Board change) */
	अणु USB_DEVICE(0x066b, 0x2202) पूर्ण, /* Linksys USB10T */
	अणु USB_DEVICE(0x06e1, 0x0008) पूर्ण, /* ADS USB-10BT */
	अणु USB_DEVICE(0x06e1, 0x0009) पूर्ण, /* ADS USB-10BT */
	अणु USB_DEVICE(0x0707, 0x0100) पूर्ण, /* SMC 2202USB */
	अणु USB_DEVICE(0x07aa, 0x0001) पूर्ण, /* Correga K.K. */
	अणु USB_DEVICE(0x07b8, 0x4000) पूर्ण, /* D-Link DU-E10 */
	अणु USB_DEVICE(0x07c9, 0xb010) पूर्ण, /* Allied Telesyn AT-USB10 USB Ethernet Adapter */
	अणु USB_DEVICE(0x0846, 0x1001) पूर्ण, /* NetGear EA-101 */
	अणु USB_DEVICE(0x0846, 0x1002) पूर्ण, /* NetGear EA-101 */
	अणु USB_DEVICE(0x085a, 0x0008) पूर्ण, /* PortGear Ethernet Adapter */
	अणु USB_DEVICE(0x085a, 0x0009) पूर्ण, /* PortGear Ethernet Adapter */
	अणु USB_DEVICE(0x087d, 0x5704) पूर्ण, /* Jaton USB Ethernet Device Adapter */
	अणु USB_DEVICE(0x0951, 0x0008) पूर्ण, /* Kingston Technology USB Ethernet Adapter */
	अणु USB_DEVICE(0x095a, 0x3003) पूर्ण, /* Portsmith Express Ethernet Adapter */
	अणु USB_DEVICE(0x10bd, 0x1427) पूर्ण, /* ASANTE USB To Ethernet Adapter */
	अणु USB_DEVICE(0x1342, 0x0204) पूर्ण, /* Mobility USB-Ethernet Adapter */
	अणु USB_DEVICE(0x13d2, 0x0400) पूर्ण, /* Shark Pocket Adapter */
	अणु USB_DEVICE(0x1485, 0x0001) पूर्ण,	/* Silicom U2E */
	अणु USB_DEVICE(0x1485, 0x0002) पूर्ण, /* Psion Dacom Gold Port Ethernet */
	अणु USB_DEVICE(0x1645, 0x0005) पूर्ण, /* Entrega E45 */
	अणु USB_DEVICE(0x1645, 0x0008) पूर्ण, /* Entrega USB Ethernet Adapter */
	अणु USB_DEVICE(0x1645, 0x8005) पूर्ण, /* PortGear Ethernet Adapter */
	अणु USB_DEVICE(0x1668, 0x0323) पूर्ण, /* Actiontec USB Ethernet */
	अणु USB_DEVICE(0x2001, 0x4000) पूर्ण, /* D-link DSB-650C */
	अणुपूर्ण /* Null terminator */
पूर्ण;

MODULE_DEVICE_TABLE (usb, usb_klsi_table);

/****************************************************************
 *     kaweth_driver
 ****************************************************************/
अटल काष्ठा usb_driver kaweth_driver = अणु
	.name =		driver_name,
	.probe =	kaweth_probe,
	.disconnect =	kaweth_disconnect,
	.suspend =	kaweth_suspend,
	.resume =	kaweth_resume,
	.id_table =     usb_klsi_table,
	.supports_स्वतःsuspend =	1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

प्रकार __u8 eth_addr_t[6];

/****************************************************************
 *     usb_eth_dev
 ****************************************************************/
काष्ठा usb_eth_dev अणु
	अक्षर *name;
	__u16 venकरोr;
	__u16 device;
	व्योम *pdata;
पूर्ण;

/****************************************************************
 *     kaweth_ethernet_configuration
 *     Refer Table 8
 ****************************************************************/
काष्ठा kaweth_ethernet_configuration
अणु
	__u8 size;
	__u8 reserved1;
	__u8 reserved2;
	eth_addr_t hw_addr;
	__u32 statistics_mask;
	__le16 segment_size;
	__u16 max_multicast_filters;
	__u8 reserved3;
पूर्ण __packed;

/****************************************************************
 *     kaweth_device
 ****************************************************************/
काष्ठा kaweth_device
अणु
	spinlock_t device_lock;

	__u32 status;
	पूर्णांक end;
	पूर्णांक suspend_lowmem_rx;
	पूर्णांक suspend_lowmem_ctrl;
	पूर्णांक linkstate;
	पूर्णांक खोलोed;
	काष्ठा delayed_work lowmem_work;

	काष्ठा usb_device *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा net_device *net;
	रुको_queue_head_t term_रुको;

	काष्ठा urb *rx_urb;
	काष्ठा urb *tx_urb;
	काष्ठा urb *irq_urb;

	dma_addr_t पूर्णांकbufferhandle;
	__u8 *पूर्णांकbuffer;
	dma_addr_t rxbufferhandle;
	__u8 *rx_buf;

	
	काष्ठा sk_buff *tx_skb;

	__u8 *firmware_buf;
	__u8 scratch[KAWETH_SCRATCH_SIZE];
	__u16 packet_filter_biपंचांगap;

	काष्ठा kaweth_ethernet_configuration configuration;
पूर्ण;

/****************************************************************
 *     kaweth_पढ़ो_configuration
 ****************************************************************/
अटल पूर्णांक kaweth_पढ़ो_configuration(काष्ठा kaweth_device *kaweth)
अणु
	वापस usb_control_msg(kaweth->dev, usb_rcvctrlpipe(kaweth->dev, 0),
				KAWETH_COMMAND_GET_ETHERNET_DESC,
				USB_TYPE_VENDOR | USB_सूची_IN | USB_RECIP_DEVICE,
				0, 0,
				&kaweth->configuration,
				माप(kaweth->configuration),
				KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_set_urb_size
 ****************************************************************/
अटल पूर्णांक kaweth_set_urb_size(काष्ठा kaweth_device *kaweth, __u16 urb_size)
अणु
	netdev_dbg(kaweth->net, "Setting URB size to %d\n", (अचिन्हित)urb_size);

	वापस usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_URB_SIZE,
			       USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			       urb_size, 0,
			       &kaweth->scratch, 0,
			       KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_set_sofs_रुको
 ****************************************************************/
अटल पूर्णांक kaweth_set_sofs_रुको(काष्ठा kaweth_device *kaweth, __u16 sofs_रुको)
अणु
	netdev_dbg(kaweth->net, "Set SOFS wait to %d\n", (अचिन्हित)sofs_रुको);

	वापस usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_SOFS_WAIT,
			       USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			       sofs_रुको, 0,
			       &kaweth->scratch, 0,
			       KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_set_receive_filter
 ****************************************************************/
अटल पूर्णांक kaweth_set_receive_filter(काष्ठा kaweth_device *kaweth,
				     __u16 receive_filter)
अणु
	netdev_dbg(kaweth->net, "Set receive filter to %d\n",
		   (अचिन्हित)receive_filter);

	वापस usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_PACKET_FILTER,
			       USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			       receive_filter, 0,
			       &kaweth->scratch, 0,
			       KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_करोwnload_firmware
 ****************************************************************/
अटल पूर्णांक kaweth_करोwnload_firmware(काष्ठा kaweth_device *kaweth,
				    स्थिर अक्षर *fwname,
				    __u8 पूर्णांकerrupt,
				    __u8 type)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक data_len;
	पूर्णांक ret;

	ret = request_firmware(&fw, fwname, &kaweth->dev->dev);
	अगर (ret) अणु
		dev_err(&kaweth->पूर्णांकf->dev, "Firmware request failed\n");
		वापस ret;
	पूर्ण

	अगर (fw->size > KAWETH_FIRMWARE_BUF_SIZE) अणु
		dev_err(&kaweth->पूर्णांकf->dev, "Firmware too big: %zu\n",
			fw->size);
		release_firmware(fw);
		वापस -ENOSPC;
	पूर्ण
	data_len = fw->size;
	स_नकल(kaweth->firmware_buf, fw->data, fw->size);

	release_firmware(fw);

	kaweth->firmware_buf[2] = (data_len & 0xFF) - 7;
	kaweth->firmware_buf[3] = data_len >> 8;
	kaweth->firmware_buf[4] = type;
	kaweth->firmware_buf[5] = पूर्णांकerrupt;

	netdev_dbg(kaweth->net, "High: %i, Low:%i\n", kaweth->firmware_buf[3],
		   kaweth->firmware_buf[2]);

	netdev_dbg(kaweth->net,
		   "Downloading firmware at %p to kaweth device at %p\n",
		   kaweth->firmware_buf, kaweth);
	netdev_dbg(kaweth->net, "Firmware length: %d\n", data_len);

	वापस usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SCAN,
			      USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			      0, 0,
			      kaweth->firmware_buf, data_len,
			      KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_trigger_firmware
 ****************************************************************/
अटल पूर्णांक kaweth_trigger_firmware(काष्ठा kaweth_device *kaweth,
				   __u8 पूर्णांकerrupt)
अणु
	kaweth->firmware_buf[0] = 0xB6;
	kaweth->firmware_buf[1] = 0xC3;
	kaweth->firmware_buf[2] = 0x01;
	kaweth->firmware_buf[3] = 0x00;
	kaweth->firmware_buf[4] = 0x06;
	kaweth->firmware_buf[5] = पूर्णांकerrupt;
	kaweth->firmware_buf[6] = 0x00;
	kaweth->firmware_buf[7] = 0x00;

	वापस usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SCAN,
			       USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			       0, 0,
			       (व्योम *)kaweth->firmware_buf, 8,
			       KAWETH_CONTROL_TIMEOUT);
पूर्ण

/****************************************************************
 *     kaweth_reset
 ****************************************************************/
अटल पूर्णांक kaweth_reset(काष्ठा kaweth_device *kaweth)
अणु
	पूर्णांक result;

	result = usb_reset_configuration(kaweth->dev);
	mdelay(10);

	netdev_dbg(kaweth->net, "kaweth_reset() returns %d.\n", result);

	वापस result;
पूर्ण

अटल व्योम kaweth_usb_receive(काष्ठा urb *);
अटल पूर्णांक kaweth_resubmit_rx_urb(काष्ठा kaweth_device *, gfp_t);

/****************************************************************
	पूर्णांक_callback
*****************************************************************/

अटल व्योम kaweth_resubmit_पूर्णांक_urb(काष्ठा kaweth_device *kaweth, gfp_t mf)
अणु
	पूर्णांक status;

	status = usb_submit_urb (kaweth->irq_urb, mf);
	अगर (unlikely(status == -ENOMEM)) अणु
		kaweth->suspend_lowmem_ctrl = 1;
		schedule_delayed_work(&kaweth->lowmem_work, HZ/4);
	पूर्ण अन्यथा अणु
		kaweth->suspend_lowmem_ctrl = 0;
	पूर्ण

	अगर (status)
		dev_err(&kaweth->पूर्णांकf->dev,
			"can't resubmit intr, %s-%s, status %d\n",
			kaweth->dev->bus->bus_name,
			kaweth->dev->devpath, status);
पूर्ण

अटल व्योम पूर्णांक_callback(काष्ठा urb *u)
अणु
	काष्ठा kaweth_device *kaweth = u->context;
	पूर्णांक act_state;
	पूर्णांक status = u->status;

	चयन (status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	/* -EPIPE:  should clear the halt */
	शेष:		/* error */
		जाओ resubmit;
	पूर्ण

	/* we check the link state to report changes */
	अगर (kaweth->linkstate != (act_state = ( kaweth->पूर्णांकbuffer[STATE_OFFSET] | STATE_MASK) >> STATE_SHIFT)) अणु
		अगर (act_state)
			netअगर_carrier_on(kaweth->net);
		अन्यथा
			netअगर_carrier_off(kaweth->net);

		kaweth->linkstate = act_state;
	पूर्ण
resubmit:
	kaweth_resubmit_पूर्णांक_urb(kaweth, GFP_ATOMIC);
पूर्ण

अटल व्योम kaweth_resubmit_tl(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kaweth_device *kaweth =
		container_of(work, काष्ठा kaweth_device, lowmem_work.work);

	अगर (IS_BLOCKED(kaweth->status))
		वापस;

	अगर (kaweth->suspend_lowmem_rx)
		kaweth_resubmit_rx_urb(kaweth, GFP_NOIO);

	अगर (kaweth->suspend_lowmem_ctrl)
		kaweth_resubmit_पूर्णांक_urb(kaweth, GFP_NOIO);
पूर्ण


/****************************************************************
 *     kaweth_resubmit_rx_urb
 ****************************************************************/
अटल पूर्णांक kaweth_resubmit_rx_urb(काष्ठा kaweth_device *kaweth,
						gfp_t mem_flags)
अणु
	पूर्णांक result;

	usb_fill_bulk_urb(kaweth->rx_urb,
		      kaweth->dev,
		      usb_rcvbulkpipe(kaweth->dev, 1),
		      kaweth->rx_buf,
		      KAWETH_BUF_SIZE,
		      kaweth_usb_receive,
		      kaweth);
	kaweth->rx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	kaweth->rx_urb->transfer_dma = kaweth->rxbufferhandle;

	अगर((result = usb_submit_urb(kaweth->rx_urb, mem_flags))) अणु
		अगर (result == -ENOMEM) अणु
			kaweth->suspend_lowmem_rx = 1;
			schedule_delayed_work(&kaweth->lowmem_work, HZ/4);
		पूर्ण
		dev_err(&kaweth->पूर्णांकf->dev, "resubmitting rx_urb %d failed\n",
			result);
	पूर्ण अन्यथा अणु
		kaweth->suspend_lowmem_rx = 0;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम kaweth_async_set_rx_mode(काष्ठा kaweth_device *kaweth,
				     bool may_sleep);

/****************************************************************
 *     kaweth_usb_receive
 ****************************************************************/
अटल व्योम kaweth_usb_receive(काष्ठा urb *urb)
अणु
	काष्ठा device *dev = &urb->dev->dev;
	काष्ठा kaweth_device *kaweth = urb->context;
	काष्ठा net_device *net = kaweth->net;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = urb->actual_length;
	पूर्णांक count2 = urb->transfer_buffer_length;

	__u16 pkt_len = le16_to_cpup((__le16 *)kaweth->rx_buf);

	काष्ठा sk_buff *skb;

	अगर (unlikely(status == -EPIPE)) अणु
		net->stats.rx_errors++;
		kaweth->end = 1;
		wake_up(&kaweth->term_रुको);
		dev_dbg(dev, "Status was -EPIPE.\n");
		वापस;
	पूर्ण
	अगर (unlikely(status == -ECONNRESET || status == -ESHUTDOWN)) अणु
		/* we are समाप्तed - set a flag and wake the disconnect handler */
		kaweth->end = 1;
		wake_up(&kaweth->term_रुको);
		dev_dbg(dev, "Status was -ECONNRESET or -ESHUTDOWN.\n");
		वापस;
	पूर्ण
	अगर (unlikely(status == -EPROTO || status == -ETIME ||
		     status == -EILSEQ)) अणु
		net->stats.rx_errors++;
		dev_dbg(dev, "Status was -EPROTO, -ETIME, or -EILSEQ.\n");
		वापस;
	पूर्ण
	अगर (unlikely(status == -EOVERFLOW)) अणु
		net->stats.rx_errors++;
		dev_dbg(dev, "Status was -EOVERFLOW.\n");
	पूर्ण
	spin_lock_irqsave(&kaweth->device_lock, flags);
	अगर (IS_BLOCKED(kaweth->status)) अणु
		spin_unlock_irqrestore(&kaweth->device_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	अगर(status && status != -EREMOTEIO && count != 1) अणु
		dev_err(&kaweth->पूर्णांकf->dev,
			"%s RX status: %d count: %d packet_len: %d\n",
			net->name, status, count, (पूर्णांक)pkt_len);
		kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                वापस;
	पूर्ण

	अगर(kaweth->net && (count > 2)) अणु
		अगर(pkt_len > (count - 2)) अणु
			dev_err(&kaweth->पूर्णांकf->dev,
				"Packet length too long for USB frame (pkt_len: %x, count: %x)\n",
				pkt_len, count);
			dev_err(&kaweth->पूर्णांकf->dev, "Packet len & 2047: %x\n",
				pkt_len & 2047);
			dev_err(&kaweth->पूर्णांकf->dev, "Count 2: %x\n", count2);
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        वापस;
                पूर्ण

		अगर(!(skb = dev_alloc_skb(pkt_len+2))) अणु
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        वापस;
		पूर्ण

		skb_reserve(skb, 2);    /* Align IP on 16 byte boundaries */

		skb_copy_to_linear_data(skb, kaweth->rx_buf + 2, pkt_len);

		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, net);

		netअगर_rx(skb);

		net->stats.rx_packets++;
		net->stats.rx_bytes += pkt_len;
	पूर्ण

	kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
पूर्ण

/****************************************************************
 *     kaweth_खोलो
 ****************************************************************/
अटल पूर्णांक kaweth_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(net);
	पूर्णांक res;

	res = usb_स्वतःpm_get_पूर्णांकerface(kaweth->पूर्णांकf);
	अगर (res) अणु
		dev_err(&kaweth->पूर्णांकf->dev, "Interface cannot be resumed.\n");
		वापस -EIO;
	पूर्ण
	res = kaweth_resubmit_rx_urb(kaweth, GFP_KERNEL);
	अगर (res)
		जाओ err_out;

	usb_fill_पूर्णांक_urb(
		kaweth->irq_urb,
		kaweth->dev,
		usb_rcvपूर्णांकpipe(kaweth->dev, 3),
		kaweth->पूर्णांकbuffer,
		INTBUFFERSIZE,
		पूर्णांक_callback,
		kaweth,
		250); /* overriding the descriptor */
	kaweth->irq_urb->transfer_dma = kaweth->पूर्णांकbufferhandle;
	kaweth->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	res = usb_submit_urb(kaweth->irq_urb, GFP_KERNEL);
	अगर (res) अणु
		usb_समाप्त_urb(kaweth->rx_urb);
		जाओ err_out;
	पूर्ण
	kaweth->खोलोed = 1;

	netअगर_start_queue(net);

	kaweth_async_set_rx_mode(kaweth, true);
	वापस 0;

err_out:
	usb_स्वतःpm_put_पूर्णांकerface(kaweth->पूर्णांकf);
	वापस -EIO;
पूर्ण

/****************************************************************
 *     kaweth_समाप्त_urbs
 ****************************************************************/
अटल व्योम kaweth_समाप्त_urbs(काष्ठा kaweth_device *kaweth)
अणु
	usb_समाप्त_urb(kaweth->irq_urb);
	usb_समाप्त_urb(kaweth->rx_urb);
	usb_समाप्त_urb(kaweth->tx_urb);

	cancel_delayed_work_sync(&kaweth->lowmem_work);

	/* a scheduled work may have resubmitted,
	   we hit them again */
	usb_समाप्त_urb(kaweth->irq_urb);
	usb_समाप्त_urb(kaweth->rx_urb);
पूर्ण

/****************************************************************
 *     kaweth_बंद
 ****************************************************************/
अटल पूर्णांक kaweth_बंद(काष्ठा net_device *net)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(net);

	netअगर_stop_queue(net);
	kaweth->खोलोed = 0;

	kaweth->status |= KAWETH_STATUS_CLOSING;

	kaweth_समाप्त_urbs(kaweth);

	kaweth->status &= ~KAWETH_STATUS_CLOSING;

	usb_स्वतःpm_put_पूर्णांकerface(kaweth->पूर्णांकf);

	वापस 0;
पूर्ण

अटल u32 kaweth_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(dev);

	वापस kaweth->linkstate;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_link	= kaweth_get_link
पूर्ण;

/****************************************************************
 *     kaweth_usb_transmit_complete
 ****************************************************************/
अटल व्योम kaweth_usb_transmit_complete(काष्ठा urb *urb)
अणु
	काष्ठा kaweth_device *kaweth = urb->context;
	काष्ठा sk_buff *skb = kaweth->tx_skb;
	पूर्णांक status = urb->status;

	अगर (unlikely(status != 0))
		अगर (status != -ENOENT)
			dev_dbg(&urb->dev->dev, "%s: TX status %d.\n",
				kaweth->net->name, status);

	netअगर_wake_queue(kaweth->net);
	dev_kमुक्त_skb_irq(skb);
पूर्ण

/****************************************************************
 *     kaweth_start_xmit
 ****************************************************************/
अटल netdev_tx_t kaweth_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *net)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(net);
	__le16 *निजी_header;

	पूर्णांक res;

	spin_lock_irq(&kaweth->device_lock);

	kaweth_async_set_rx_mode(kaweth, false);
	netअगर_stop_queue(net);
	अगर (IS_BLOCKED(kaweth->status)) अणु
		जाओ skip;
	पूर्ण

	/* We now decide whether we can put our special header पूर्णांकo the sk_buff */
	अगर (skb_cow_head(skb, 2)) अणु
		net->stats.tx_errors++;
		netअगर_start_queue(net);
		spin_unlock_irq(&kaweth->device_lock);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	निजी_header = __skb_push(skb, 2);
	*निजी_header = cpu_to_le16(skb->len-2);
	kaweth->tx_skb = skb;

	usb_fill_bulk_urb(kaweth->tx_urb,
		      kaweth->dev,
		      usb_sndbulkpipe(kaweth->dev, 2),
		      निजी_header,
		      skb->len,
		      kaweth_usb_transmit_complete,
		      kaweth);
	kaweth->end = 0;

	अगर((res = usb_submit_urb(kaweth->tx_urb, GFP_ATOMIC)))
	अणु
		dev_warn(&net->dev, "kaweth failed tx_urb %d\n", res);
skip:
		net->stats.tx_errors++;

		netअगर_start_queue(net);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
	अन्यथा
	अणु
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->len;
	पूर्ण

	spin_unlock_irq(&kaweth->device_lock);

	वापस NETDEV_TX_OK;
पूर्ण

/****************************************************************
 *     kaweth_set_rx_mode
 ****************************************************************/
अटल व्योम kaweth_set_rx_mode(काष्ठा net_device *net)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(net);

	__u16 packet_filter_biपंचांगap = KAWETH_PACKET_FILTER_सूचीECTED |
                                     KAWETH_PACKET_FILTER_BROADCAST |
		                     KAWETH_PACKET_FILTER_MULTICAST;

	netdev_dbg(net, "Setting Rx mode to %d\n", packet_filter_biपंचांगap);

	netअगर_stop_queue(net);

	अगर (net->flags & IFF_PROMISC) अणु
		packet_filter_biपंचांगap |= KAWETH_PACKET_FILTER_PROMISCUOUS;
	पूर्ण
	अन्यथा अगर (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI)) अणु
		packet_filter_biपंचांगap |= KAWETH_PACKET_FILTER_ALL_MULTICAST;
	पूर्ण

	kaweth->packet_filter_biपंचांगap = packet_filter_biपंचांगap;
	netअगर_wake_queue(net);
पूर्ण

/****************************************************************
 *     kaweth_async_set_rx_mode
 ****************************************************************/
अटल व्योम kaweth_async_set_rx_mode(काष्ठा kaweth_device *kaweth,
				     bool may_sleep)
अणु
	पूर्णांक ret;
	__u16 packet_filter_biपंचांगap = kaweth->packet_filter_biपंचांगap;

	kaweth->packet_filter_biपंचांगap = 0;
	अगर (packet_filter_biपंचांगap == 0)
		वापस;

	अगर (!may_sleep)
		वापस;

	ret = usb_control_msg(kaweth->dev, usb_sndctrlpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SET_PACKET_FILTER,
			      USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			      packet_filter_biपंचांगap, 0,
			      &kaweth->scratch, 0,
			      KAWETH_CONTROL_TIMEOUT);
	अगर (ret < 0)
		dev_err(&kaweth->पूर्णांकf->dev, "Failed to set Rx mode: %d\n",
			ret);
	अन्यथा
		netdev_dbg(kaweth->net, "Set Rx mode to %d\n",
			   packet_filter_biपंचांगap);
पूर्ण

/****************************************************************
 *     kaweth_tx_समयout
 ****************************************************************/
अटल व्योम kaweth_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा kaweth_device *kaweth = netdev_priv(net);

	dev_warn(&net->dev, "%s: Tx timed out. Resetting.\n", net->name);
	net->stats.tx_errors++;
	netअगर_trans_update(net);

	usb_unlink_urb(kaweth->tx_urb);
पूर्ण

/****************************************************************
 *     kaweth_suspend
 ****************************************************************/
अटल पूर्णांक kaweth_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा kaweth_device *kaweth = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kaweth->device_lock, flags);
	kaweth->status |= KAWETH_STATUS_SUSPENDING;
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	kaweth_समाप्त_urbs(kaweth);
	वापस 0;
पूर्ण

/****************************************************************
 *     kaweth_resume
 ****************************************************************/
अटल पूर्णांक kaweth_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा kaweth_device *kaweth = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kaweth->device_lock, flags);
	kaweth->status &= ~KAWETH_STATUS_SUSPENDING;
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	अगर (!kaweth->खोलोed)
		वापस 0;
	kaweth_resubmit_rx_urb(kaweth, GFP_NOIO);
	kaweth_resubmit_पूर्णांक_urb(kaweth, GFP_NOIO);

	वापस 0;
पूर्ण

/****************************************************************
 *     kaweth_probe
 ****************************************************************/


अटल स्थिर काष्ठा net_device_ops kaweth_netdev_ops = अणु
	.nकरो_खोलो =			kaweth_खोलो,
	.nकरो_stop =			kaweth_बंद,
	.nकरो_start_xmit =		kaweth_start_xmit,
	.nकरो_tx_समयout =		kaweth_tx_समयout,
	.nकरो_set_rx_mode =		kaweth_set_rx_mode,
	.nकरो_set_mac_address =		eth_mac_addr,
	.nकरो_validate_addr =		eth_validate_addr,
पूर्ण;

अटल पूर्णांक kaweth_probe(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id      /* from id_table */
	)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा kaweth_device *kaweth;
	काष्ठा net_device *netdev;
	स्थिर eth_addr_t bcast_addr = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	पूर्णांक result = 0;
	पूर्णांक rv = -EIO;

	dev_dbg(dev,
		"Kawasaki Device Probe (Device number:%d): 0x%4.4x:0x%4.4x:0x%4.4x\n",
		udev->devnum, le16_to_cpu(udev->descriptor.idVenकरोr),
		le16_to_cpu(udev->descriptor.idProduct),
		le16_to_cpu(udev->descriptor.bcdDevice));

	dev_dbg(dev, "Device at %p\n", udev);

	dev_dbg(dev, "Descriptor length: %x type: %x\n",
		(पूर्णांक)udev->descriptor.bLength,
		(पूर्णांक)udev->descriptor.bDescriptorType);

	netdev = alloc_etherdev(माप(*kaweth));
	अगर (!netdev)
		वापस -ENOMEM;

	kaweth = netdev_priv(netdev);
	kaweth->dev = udev;
	kaweth->net = netdev;
	kaweth->पूर्णांकf = पूर्णांकf;

	spin_lock_init(&kaweth->device_lock);
	init_रुकोqueue_head(&kaweth->term_रुको);

	dev_dbg(dev, "Resetting.\n");

	kaweth_reset(kaweth);

	/*
	 * If high byte of bcdDevice is nonzero, firmware is alपढ़ोy
	 * करोwnloaded. Don't try to do it again, or we'll hang the device.
	 */

	अगर (le16_to_cpu(udev->descriptor.bcdDevice) >> 8) अणु
		dev_info(dev, "Firmware present in device.\n");
	पूर्ण अन्यथा अणु
		/* Download the firmware */
		dev_info(dev, "Downloading firmware...\n");
		kaweth->firmware_buf = (__u8 *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!kaweth->firmware_buf) अणु
			rv = -ENOMEM;
			जाओ err_मुक्त_netdev;
		पूर्ण
		अगर ((result = kaweth_करोwnload_firmware(kaweth,
						      "kaweth/new_code.bin",
						      100,
						      2)) < 0) अणु
			dev_err(dev, "Error downloading firmware (%d)\n",
				result);
			जाओ err_fw;
		पूर्ण

		अगर ((result = kaweth_करोwnload_firmware(kaweth,
						      "kaweth/new_code_fix.bin",
						      100,
						      3)) < 0) अणु
			dev_err(dev, "Error downloading firmware fix (%d)\n",
				result);
			जाओ err_fw;
		पूर्ण

		अगर ((result = kaweth_करोwnload_firmware(kaweth,
						      "kaweth/trigger_code.bin",
						      126,
						      2)) < 0) अणु
			dev_err(dev, "Error downloading trigger code (%d)\n",
				result);
			जाओ err_fw;

		पूर्ण

		अगर ((result = kaweth_करोwnload_firmware(kaweth,
						      "kaweth/trigger_code_fix.bin",
						      126,
						      3)) < 0) अणु
			dev_err(dev, "Error downloading trigger code fix (%d)\n", result);
			जाओ err_fw;
		पूर्ण


		अगर ((result = kaweth_trigger_firmware(kaweth, 126)) < 0) अणु
			dev_err(dev, "Error triggering firmware (%d)\n", result);
			जाओ err_fw;
		पूर्ण

		/* Device will now disappear क्रम a moment...  */
		dev_info(dev, "Firmware loaded.  I'll be back...\n");
err_fw:
		मुक्त_page((अचिन्हित दीर्घ)kaweth->firmware_buf);
		मुक्त_netdev(netdev);
		वापस -EIO;
	पूर्ण

	result = kaweth_पढ़ो_configuration(kaweth);

	अगर(result < 0) अणु
		dev_err(dev, "Error reading configuration (%d), no net device created\n", result);
		जाओ err_मुक्त_netdev;
	पूर्ण

	dev_info(dev, "Statistics collection: %x\n", kaweth->configuration.statistics_mask);
	dev_info(dev, "Multicast filter limit: %x\n", kaweth->configuration.max_multicast_filters & ((1 << 15) - 1));
	dev_info(dev, "MTU: %d\n", le16_to_cpu(kaweth->configuration.segment_size));
	dev_info(dev, "Read MAC address %pM\n", kaweth->configuration.hw_addr);

	अगर(!स_भेद(&kaweth->configuration.hw_addr,
                   &bcast_addr,
		   माप(bcast_addr))) अणु
		dev_err(dev, "Firmware not functioning properly, no net device created\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	अगर(kaweth_set_urb_size(kaweth, KAWETH_BUF_SIZE) < 0) अणु
		dev_dbg(dev, "Error setting URB size\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	अगर(kaweth_set_sofs_रुको(kaweth, KAWETH_SOFS_TO_WAIT) < 0) अणु
		dev_err(dev, "Error setting SOFS wait\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	result = kaweth_set_receive_filter(kaweth,
                                           KAWETH_PACKET_FILTER_सूचीECTED |
                                           KAWETH_PACKET_FILTER_BROADCAST |
                                           KAWETH_PACKET_FILTER_MULTICAST);

	अगर(result < 0) अणु
		dev_err(dev, "Error setting receive filter\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	dev_dbg(dev, "Initializing net device.\n");

	kaweth->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!kaweth->tx_urb)
		जाओ err_मुक्त_netdev;
	kaweth->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!kaweth->rx_urb)
		जाओ err_only_tx;
	kaweth->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!kaweth->irq_urb)
		जाओ err_tx_and_rx;

	kaweth->पूर्णांकbuffer = usb_alloc_coherent(	kaweth->dev,
						INTBUFFERSIZE,
						GFP_KERNEL,
						&kaweth->पूर्णांकbufferhandle);
	अगर (!kaweth->पूर्णांकbuffer)
		जाओ err_tx_and_rx_and_irq;
	kaweth->rx_buf = usb_alloc_coherent(	kaweth->dev,
						KAWETH_BUF_SIZE,
						GFP_KERNEL,
						&kaweth->rxbufferhandle);
	अगर (!kaweth->rx_buf)
		जाओ err_all_but_rxbuf;

	स_नकल(netdev->broadcast, &bcast_addr, माप(bcast_addr));
	स_नकल(netdev->dev_addr, &kaweth->configuration.hw_addr,
               माप(kaweth->configuration.hw_addr));

	netdev->netdev_ops = &kaweth_netdev_ops;
	netdev->watchकरोg_समयo = KAWETH_TX_TIMEOUT;
	netdev->mtu = le16_to_cpu(kaweth->configuration.segment_size);
	netdev->ethtool_ops = &ops;

	/* kaweth is zeroed as part of alloc_netdev */
	INIT_DELAYED_WORK(&kaweth->lowmem_work, kaweth_resubmit_tl);
	usb_set_पूर्णांकfdata(पूर्णांकf, kaweth);

	SET_NETDEV_DEV(netdev, dev);
	अगर (रेजिस्टर_netdev(netdev) != 0) अणु
		dev_err(dev, "Error registering netdev.\n");
		जाओ err_पूर्णांकfdata;
	पूर्ण

	dev_info(dev, "kaweth interface created at %s\n",
		 kaweth->net->name);

	वापस 0;

err_पूर्णांकfdata:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_मुक्त_coherent(kaweth->dev, KAWETH_BUF_SIZE, (व्योम *)kaweth->rx_buf, kaweth->rxbufferhandle);
err_all_but_rxbuf:
	usb_मुक्त_coherent(kaweth->dev, INTBUFFERSIZE, (व्योम *)kaweth->पूर्णांकbuffer, kaweth->पूर्णांकbufferhandle);
err_tx_and_rx_and_irq:
	usb_मुक्त_urb(kaweth->irq_urb);
err_tx_and_rx:
	usb_मुक्त_urb(kaweth->rx_urb);
err_only_tx:
	usb_मुक्त_urb(kaweth->tx_urb);
err_मुक्त_netdev:
	मुक्त_netdev(netdev);

	वापस rv;
पूर्ण

/****************************************************************
 *     kaweth_disconnect
 ****************************************************************/
अटल व्योम kaweth_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा kaweth_device *kaweth = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (!kaweth) अणु
		dev_warn(&पूर्णांकf->dev, "unregistering non-existent device\n");
		वापस;
	पूर्ण
	netdev = kaweth->net;

	netdev_dbg(kaweth->net, "Unregistering net device\n");
	unरेजिस्टर_netdev(netdev);

	usb_मुक्त_urb(kaweth->rx_urb);
	usb_मुक्त_urb(kaweth->tx_urb);
	usb_मुक्त_urb(kaweth->irq_urb);

	usb_मुक्त_coherent(kaweth->dev, KAWETH_BUF_SIZE, (व्योम *)kaweth->rx_buf, kaweth->rxbufferhandle);
	usb_मुक्त_coherent(kaweth->dev, INTBUFFERSIZE, (व्योम *)kaweth->पूर्णांकbuffer, kaweth->पूर्णांकbufferhandle);

	मुक्त_netdev(netdev);
पूर्ण


module_usb_driver(kaweth_driver);
