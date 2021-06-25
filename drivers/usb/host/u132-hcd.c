<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Host Controller Driver क्रम the Elan Digital Systems U132 adapter
*
* Copyright(C) 2006 Elan Digital Systems Limited
* http://www.elandigitalप्रणालीs.com
*
* Author and Maपूर्णांकainer - Tony Olech - Elan Digital Systems
* tony.olech@elandigitalप्रणालीs.com
*
* This driver was written by Tony Olech(tony.olech@elandigitalप्रणालीs.com)
* based on various USB host drivers in the 2.6.15 linux kernel
* with स्थिरant reference to the 3rd Edition of Linux Device Drivers
* published by O'Reilly
*
* The U132 adapter is a USB to CardBus adapter specअगरically deचिन्हित
* क्रम PC cards that contain an OHCI host controller. Typical PC cards
* are the Orange Mobile 3G Option GlobeTrotter Fusion card.
*
* The U132 adapter will *NOT *work with PC cards that करो not contain
* an OHCI controller. A simple way to test whether a PC card has an
* OHCI controller as an पूर्णांकerface is to insert the PC card directly
* पूर्णांकo a laptop(or desktop) with a CardBus slot and अगर "lspci" shows
* a new USB controller and "lsusb -v" shows a new OHCI Host Controller
* then there is a good chance that the U132 adapter will support the
* PC card.(you also need the specअगरic client driver क्रम the PC card)
*
* Please inक्रमm the Author and Maपूर्णांकainer about any PC cards that
* contain OHCI Host Controller and work when directly connected to
* an embedded CardBus slot but करो not work when they are connected
* via an ELAN U132 adapter.
*
*/
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>

	/* FIXME ohci.h is ONLY क्रम पूर्णांकernal use by the OHCI driver.
	 * If you're going to try stuff like this, you need to split
	 * out shareable stuff (रेजिस्टर declarations?) पूर्णांकo its own
	 * file, maybe name <linux/usb/ohci.h>
	 */

#समावेश "ohci.h"
#घोषणा OHCI_CONTROL_INIT OHCI_CTRL_CBSR
#घोषणा OHCI_INTR_INIT (OHCI_INTR_MIE | OHCI_INTR_UE | OHCI_INTR_RD | \
	OHCI_INTR_WDH)
MODULE_AUTHOR("Tony Olech - Elan Digital Systems Limited");
MODULE_DESCRIPTION("U132 USB Host Controller Driver");
MODULE_LICENSE("GPL");
#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v;module_param(n, पूर्णांक, 0444)
INT_MODULE_PARM(testing, 0);
/* Some boards misreport घातer चयनing/overcurrent*/
अटल bool distrust_firmware = true;
module_param(distrust_firmware, bool, 0);
MODULE_PARM_DESC(distrust_firmware, "true to distrust firmware power/overcurrent"
	"t setup");
अटल DECLARE_WAIT_QUEUE_HEAD(u132_hcd_रुको);
/*
* u132_module_lock exists to protect access to global variables
*
*/
अटल DEFINE_MUTEX(u132_module_lock);
अटल पूर्णांक u132_निकासing;
अटल पूर्णांक u132_instances;
/*
* end of the global variables रक्षित by u132_module_lock
*/
अटल काष्ठा workqueue_काष्ठा *workqueue;
#घोषणा MAX_U132_PORTS 7
#घोषणा MAX_U132_ADDRS 128
#घोषणा MAX_U132_UDEVS 4
#घोषणा MAX_U132_ENDPS 100
#घोषणा MAX_U132_RINGS 4
अटल स्थिर अक्षर *cc_to_text[16] = अणु
	"No Error ",
	"CRC Error ",
	"Bit Stuff ",
	"Data Togg ",
	"Stall ",
	"DevNotResp ",
	"PIDCheck ",
	"UnExpPID ",
	"DataOver ",
	"DataUnder ",
	"(for hw) ",
	"(for hw) ",
	"BufferOver ",
	"BuffUnder ",
	"(for HCD) ",
	"(for HCD) "
पूर्ण;
काष्ठा u132_port अणु
	काष्ठा u132 *u132;
	पूर्णांक reset;
	पूर्णांक enable;
	पूर्णांक घातer;
	पूर्णांक Status;
पूर्ण;
काष्ठा u132_addr अणु
	u8 address;
पूर्ण;
काष्ठा u132_udev अणु
	काष्ठा kref kref;
	काष्ठा usb_device *usb_device;
	u8 क्रमागतeration;
	u8 udev_number;
	u8 usb_addr;
	u8 portnumber;
	u8 endp_number_in[16];
	u8 endp_number_out[16];
पूर्ण;
#घोषणा ENDP_QUEUE_SHIFT 3
#घोषणा ENDP_QUEUE_SIZE (1<<ENDP_QUEUE_SHIFT)
#घोषणा ENDP_QUEUE_MASK (ENDP_QUEUE_SIZE-1)
काष्ठा u132_urbq अणु
	काष्ठा list_head urb_more;
	काष्ठा urb *urb;
पूर्ण;
काष्ठा u132_spin अणु
	spinlock_t slock;
पूर्ण;
काष्ठा u132_endp अणु
	काष्ठा kref kref;
	u8 udev_number;
	u8 endp_number;
	u8 usb_addr;
	u8 usb_endp;
	काष्ठा u132 *u132;
	काष्ठा list_head endp_ring;
	काष्ठा u132_ring *ring;
	अचिन्हित toggle_bits:2;
	अचिन्हित active:1;
	अचिन्हित delayed:1;
	अचिन्हित input:1;
	अचिन्हित output:1;
	अचिन्हित pipetype:2;
	अचिन्हित dequeueing:1;
	अचिन्हित edset_flush:1;
	अचिन्हित spare_bits:14;
	अचिन्हित दीर्घ jअगरfies;
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा u132_spin queue_lock;
	u16 queue_size;
	u16 queue_last;
	u16 queue_next;
	काष्ठा urb *urb_list[ENDP_QUEUE_SIZE];
	काष्ठा list_head urb_more;
	काष्ठा delayed_work scheduler;
पूर्ण;
काष्ठा u132_ring अणु
	अचिन्हित in_use:1;
	अचिन्हित length:7;
	u8 number;
	काष्ठा u132 *u132;
	काष्ठा u132_endp *curr_endp;
	काष्ठा delayed_work scheduler;
पूर्ण;
काष्ठा u132 अणु
	काष्ठा kref kref;
	काष्ठा mutex sw_lock;
	काष्ठा mutex scheduler_lock;
	काष्ठा u132_platक्रमm_data *board;
	काष्ठा platक्रमm_device *platक्रमm_dev;
	काष्ठा u132_ring ring[MAX_U132_RINGS];
	पूर्णांक sequence_num;
	पूर्णांक going;
	पूर्णांक घातer;
	पूर्णांक reset;
	पूर्णांक num_ports;
	u32 hc_control;
	u32 hc_fmपूर्णांकerval;
	u32 hc_roothub_status;
	u32 hc_roothub_a;
	u32 hc_roothub_portstatus[MAX_ROOT_PORTS];
	पूर्णांक flags;
	अचिन्हित दीर्घ next_statechange;
	काष्ठा delayed_work monitor;
	पूर्णांक num_endpoपूर्णांकs;
	काष्ठा u132_addr addr[MAX_U132_ADDRS];
	काष्ठा u132_udev udev[MAX_U132_UDEVS];
	काष्ठा u132_port port[MAX_U132_PORTS];
	काष्ठा u132_endp *endp[MAX_U132_ENDPS];
पूर्ण;

/*
* these cannot be अंतरभूतs because we need the काष्ठाure offset!!
* Does anyone have a better way?????
*/
#घोषणा ftdi_पढ़ो_pcimem(pdev, member, data) usb_ftdi_elan_पढ़ो_pcimem(pdev, \
	दुरत्व(काष्ठा ohci_regs, member), 0, data);
#घोषणा ftdi_ग_लिखो_pcimem(pdev, member, data) usb_ftdi_elan_ग_लिखो_pcimem(pdev, \
	दुरत्व(काष्ठा ohci_regs, member), 0, data)
#घोषणा u132_पढ़ो_pcimem(u132, member, data) \
	usb_ftdi_elan_पढ़ो_pcimem(u132->platक्रमm_dev, दुरत्व(काष्ठा \
	ohci_regs, member), 0, data)
#घोषणा u132_ग_लिखो_pcimem(u132, member, data) \
	usb_ftdi_elan_ग_लिखो_pcimem(u132->platक्रमm_dev, दुरत्व(काष्ठा \
	ohci_regs, member), 0, data)
अटल अंतरभूत काष्ठा u132 *udev_to_u132(काष्ठा u132_udev *udev)
अणु
	u8 udev_number = udev->udev_number;
	वापस container_of(udev, काष्ठा u132, udev[udev_number]);
पूर्ण

अटल अंतरभूत काष्ठा u132 *hcd_to_u132(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा u132 *)(hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *u132_to_hcd(काष्ठा u132 *u132)
अणु
	वापस container_of((व्योम *)u132, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल अंतरभूत व्योम u132_disable(काष्ठा u132 *u132)
अणु
	u132_to_hcd(u132)->state = HC_STATE_HALT;
पूर्ण


#घोषणा kref_to_u132(d) container_of(d, काष्ठा u132, kref)
#घोषणा kref_to_u132_endp(d) container_of(d, काष्ठा u132_endp, kref)
#घोषणा kref_to_u132_udev(d) container_of(d, काष्ठा u132_udev, kref)
#समावेश "../misc/usb_u132.h"
अटल स्थिर अक्षर hcd_name[] = "u132_hcd";
#घोषणा PORT_C_MASK ((USB_PORT_STAT_C_CONNECTION | USB_PORT_STAT_C_ENABLE | \
	USB_PORT_STAT_C_SUSPEND | USB_PORT_STAT_C_OVERCURRENT | \
	USB_PORT_STAT_C_RESET) << 16)
अटल व्योम u132_hcd_delete(काष्ठा kref *kref)
अणु
	काष्ठा u132 *u132 = kref_to_u132(kref);
	काष्ठा platक्रमm_device *pdev = u132->platक्रमm_dev;
	काष्ठा usb_hcd *hcd = u132_to_hcd(u132);
	u132->going += 1;
	mutex_lock(&u132_module_lock);
	u132_instances -= 1;
	mutex_unlock(&u132_module_lock);
	dev_warn(&u132->platक्रमm_dev->dev, "FREEING the hcd=%p and thus the u13"
		"2=%p going=%d pdev=%p\n", hcd, u132, u132->going, pdev);
	usb_put_hcd(hcd);
पूर्ण

अटल अंतरभूत व्योम u132_u132_put_kref(काष्ठा u132 *u132)
अणु
	kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल अंतरभूत व्योम u132_u132_init_kref(काष्ठा u132 *u132)
अणु
	kref_init(&u132->kref);
पूर्ण

अटल व्योम u132_udev_delete(काष्ठा kref *kref)
अणु
	काष्ठा u132_udev *udev = kref_to_u132_udev(kref);
	udev->udev_number = 0;
	udev->usb_device = शून्य;
	udev->usb_addr = 0;
	udev->क्रमागतeration = 0;
पूर्ण

अटल अंतरभूत व्योम u132_udev_put_kref(काष्ठा u132 *u132, काष्ठा u132_udev *udev)
अणु
	kref_put(&udev->kref, u132_udev_delete);
पूर्ण

अटल अंतरभूत व्योम u132_udev_get_kref(काष्ठा u132 *u132, काष्ठा u132_udev *udev)
अणु
	kref_get(&udev->kref);
पूर्ण

अटल अंतरभूत व्योम u132_udev_init_kref(काष्ठा u132 *u132,
	काष्ठा u132_udev *udev)
अणु
	kref_init(&udev->kref);
पूर्ण

अटल अंतरभूत व्योम u132_ring_put_kref(काष्ठा u132 *u132, काष्ठा u132_ring *ring)
अणु
	kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल व्योम u132_ring_requeue_work(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	अचिन्हित पूर्णांक delta)
अणु
	अगर (delta > 0) अणु
		अगर (queue_delayed_work(workqueue, &ring->scheduler, delta))
			वापस;
	पूर्ण अन्यथा अगर (queue_delayed_work(workqueue, &ring->scheduler, 0))
		वापस;
	kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल व्योम u132_ring_queue_work(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	अचिन्हित पूर्णांक delta)
अणु
	kref_get(&u132->kref);
	u132_ring_requeue_work(u132, ring, delta);
पूर्ण

अटल व्योम u132_ring_cancel_work(काष्ठा u132 *u132, काष्ठा u132_ring *ring)
अणु
	अगर (cancel_delayed_work(&ring->scheduler))
		kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल व्योम u132_endp_delete(काष्ठा kref *kref)
अणु
	काष्ठा u132_endp *endp = kref_to_u132_endp(kref);
	काष्ठा u132 *u132 = endp->u132;
	u8 usb_addr = endp->usb_addr;
	u8 usb_endp = endp->usb_endp;
	u8 address = u132->addr[usb_addr].address;
	काष्ठा u132_udev *udev = &u132->udev[address];
	u8 endp_number = endp->endp_number;
	काष्ठा usb_host_endpoपूर्णांक *hep = endp->hep;
	काष्ठा u132_ring *ring = endp->ring;
	काष्ठा list_head *head = &endp->endp_ring;
	ring->length -= 1;
	अगर (endp == ring->curr_endp) अणु
		अगर (list_empty(head)) अणु
			ring->curr_endp = शून्य;
			list_del(head);
		पूर्ण अन्यथा अणु
			काष्ठा u132_endp *next_endp = list_entry(head->next,
				काष्ठा u132_endp, endp_ring);
			ring->curr_endp = next_endp;
			list_del(head);
		पूर्ण
	पूर्ण अन्यथा
		list_del(head);
	अगर (endp->input) अणु
		udev->endp_number_in[usb_endp] = 0;
		u132_udev_put_kref(u132, udev);
	पूर्ण
	अगर (endp->output) अणु
		udev->endp_number_out[usb_endp] = 0;
		u132_udev_put_kref(u132, udev);
	पूर्ण
	u132->endp[endp_number - 1] = शून्य;
	hep->hcpriv = शून्य;
	kमुक्त(endp);
	u132_u132_put_kref(u132);
पूर्ण

अटल अंतरभूत व्योम u132_endp_put_kref(काष्ठा u132 *u132, काष्ठा u132_endp *endp)
अणु
	kref_put(&endp->kref, u132_endp_delete);
पूर्ण

अटल अंतरभूत व्योम u132_endp_get_kref(काष्ठा u132 *u132, काष्ठा u132_endp *endp)
अणु
	kref_get(&endp->kref);
पूर्ण

अटल अंतरभूत व्योम u132_endp_init_kref(काष्ठा u132 *u132,
	काष्ठा u132_endp *endp)
अणु
	kref_init(&endp->kref);
	kref_get(&u132->kref);
पूर्ण

अटल व्योम u132_endp_queue_work(काष्ठा u132 *u132, काष्ठा u132_endp *endp,
	अचिन्हित पूर्णांक delta)
अणु
	अगर (queue_delayed_work(workqueue, &endp->scheduler, delta))
		kref_get(&endp->kref);
पूर्ण

अटल व्योम u132_endp_cancel_work(काष्ठा u132 *u132, काष्ठा u132_endp *endp)
अणु
	अगर (cancel_delayed_work(&endp->scheduler))
		kref_put(&endp->kref, u132_endp_delete);
पूर्ण

अटल अंतरभूत व्योम u132_monitor_put_kref(काष्ठा u132 *u132)
अणु
	kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल व्योम u132_monitor_queue_work(काष्ठा u132 *u132, अचिन्हित पूर्णांक delta)
अणु
	अगर (queue_delayed_work(workqueue, &u132->monitor, delta))
		kref_get(&u132->kref);
पूर्ण

अटल व्योम u132_monitor_requeue_work(काष्ठा u132 *u132, अचिन्हित पूर्णांक delta)
अणु
	अगर (!queue_delayed_work(workqueue, &u132->monitor, delta))
		kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल व्योम u132_monitor_cancel_work(काष्ठा u132 *u132)
अणु
	अगर (cancel_delayed_work(&u132->monitor))
		kref_put(&u132->kref, u132_hcd_delete);
पूर्ण

अटल पूर्णांक पढ़ो_roothub_info(काष्ठा u132 *u132)
अणु
	u32 revision;
	पूर्णांक retval;
	retval = u132_पढ़ो_pcimem(u132, revision, &revision);
	अगर (retval) अणु
		dev_err(&u132->platक्रमm_dev->dev, "error %d accessing device co"
			"ntrol\n", retval);
		वापस retval;
	पूर्ण अन्यथा अगर ((revision & 0xFF) == 0x10) अणु
	पूर्ण अन्यथा अगर ((revision & 0xFF) == 0x11) अणु
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "device revision is not valid"
			" %08X\n", revision);
		वापस -ENODEV;
	पूर्ण
	retval = u132_पढ़ो_pcimem(u132, control, &u132->hc_control);
	अगर (retval) अणु
		dev_err(&u132->platक्रमm_dev->dev, "error %d accessing device co"
			"ntrol\n", retval);
		वापस retval;
	पूर्ण
	retval = u132_पढ़ो_pcimem(u132, roothub.status,
		&u132->hc_roothub_status);
	अगर (retval) अणु
		dev_err(&u132->platक्रमm_dev->dev, "error %d accessing device re"
			"g roothub.status\n", retval);
		वापस retval;
	पूर्ण
	retval = u132_पढ़ो_pcimem(u132, roothub.a, &u132->hc_roothub_a);
	अगर (retval) अणु
		dev_err(&u132->platक्रमm_dev->dev, "error %d accessing device re"
			"g roothub.a\n", retval);
		वापस retval;
	पूर्ण
	अणु
		पूर्णांक I = u132->num_ports;
		पूर्णांक i = 0;
		जबतक (I-- > 0) अणु
			retval = u132_पढ़ो_pcimem(u132, roothub.portstatus[i],
				&u132->hc_roothub_portstatus[i]);
			अगर (retval) अणु
				dev_err(&u132->platक्रमm_dev->dev, "error %d acc"
					"essing device roothub.portstatus[%d]\n"
					, retval, i);
				वापस retval;
			पूर्ण अन्यथा
				i += 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम u132_hcd_monitor_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा u132 *u132 = container_of(work, काष्ठा u132, monitor.work);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		u132_monitor_put_kref(u132);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		u132_monitor_put_kref(u132);
		वापस;
	पूर्ण अन्यथा अणु
		पूर्णांक retval;
		mutex_lock(&u132->sw_lock);
		retval = पढ़ो_roothub_info(u132);
		अगर (retval) अणु
			काष्ठा usb_hcd *hcd = u132_to_hcd(u132);
			u132_disable(u132);
			u132->going = 1;
			mutex_unlock(&u132->sw_lock);
			usb_hc_died(hcd);
			ftdi_elan_gone_away(u132->platक्रमm_dev);
			u132_monitor_put_kref(u132);
			वापस;
		पूर्ण अन्यथा अणु
			u132_monitor_requeue_work(u132, 500);
			mutex_unlock(&u132->sw_lock);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_giveback_urb(काष्ठा u132 *u132, काष्ठा u132_endp *endp,
	काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा u132_ring *ring;
	अचिन्हित दीर्घ irqs;
	काष्ठा usb_hcd *hcd = u132_to_hcd(u132);
	urb->error_count = 0;
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	endp->queue_next += 1;
	अगर (ENDP_QUEUE_SIZE > --endp->queue_size) अणु
		endp->active = 0;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
	पूर्ण अन्यथा अणु
		काष्ठा list_head *next = endp->urb_more.next;
		काष्ठा u132_urbq *urbq = list_entry(next, काष्ठा u132_urbq,
			urb_more);
		list_del(next);
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] =
			urbq->urb;
		endp->active = 0;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kमुक्त(urbq);
	पूर्ण
	mutex_lock(&u132->scheduler_lock);
	ring = endp->ring;
	ring->in_use = 0;
	u132_ring_cancel_work(u132, ring);
	u132_ring_queue_work(u132, ring, 0);
	mutex_unlock(&u132->scheduler_lock);
	u132_endp_put_kref(u132, endp);
	usb_hcd_giveback_urb(hcd, urb, status);
पूर्ण

अटल व्योम u132_hcd_क्रमget_urb(काष्ठा u132 *u132, काष्ठा u132_endp *endp,
	काष्ठा urb *urb, पूर्णांक status)
अणु
	u132_endp_put_kref(u132, endp);
पूर्ण

अटल व्योम u132_hcd_abanकरोn_urb(काष्ठा u132 *u132, काष्ठा u132_endp *endp,
	काष्ठा urb *urb, पूर्णांक status)
अणु
	अचिन्हित दीर्घ irqs;
	काष्ठा usb_hcd *hcd = u132_to_hcd(u132);
	urb->error_count = 0;
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	endp->queue_next += 1;
	अगर (ENDP_QUEUE_SIZE > --endp->queue_size) अणु
		endp->active = 0;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
	पूर्ण अन्यथा अणु
		काष्ठा list_head *next = endp->urb_more.next;
		काष्ठा u132_urbq *urbq = list_entry(next, काष्ठा u132_urbq,
			urb_more);
		list_del(next);
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] =
			urbq->urb;
		endp->active = 0;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kमुक्त(urbq);
	पूर्ण
	usb_hcd_giveback_urb(hcd, urb, status);
पूर्ण

अटल अंतरभूत पूर्णांक edset_input(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	काष्ठा u132_endp *endp, काष्ठा urb *urb, u8 address, u8 toggle_bits,
	व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
	पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
	 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	वापस usb_ftdi_elan_edset_input(u132->platक्रमm_dev, ring->number, endp,
		 urb, address, endp->usb_endp, toggle_bits, callback);
पूर्ण

अटल अंतरभूत पूर्णांक edset_setup(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	काष्ठा u132_endp *endp, काष्ठा urb *urb, u8 address, u8 toggle_bits,
	व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
	पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
	 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	वापस usb_ftdi_elan_edset_setup(u132->platक्रमm_dev, ring->number, endp,
		 urb, address, endp->usb_endp, toggle_bits, callback);
पूर्ण

अटल अंतरभूत पूर्णांक edset_single(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	काष्ठा u132_endp *endp, काष्ठा urb *urb, u8 address, u8 toggle_bits,
	व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
	पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
	 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	वापस usb_ftdi_elan_edset_single(u132->platक्रमm_dev, ring->number,
		endp, urb, address, endp->usb_endp, toggle_bits, callback);
पूर्ण

अटल अंतरभूत पूर्णांक edset_output(काष्ठा u132 *u132, काष्ठा u132_ring *ring,
	काष्ठा u132_endp *endp, काष्ठा urb *urb, u8 address, u8 toggle_bits,
	व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
	पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
	 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	वापस usb_ftdi_elan_edset_output(u132->platक्रमm_dev, ring->number,
		endp, urb, address, endp->usb_endp, toggle_bits, callback);
पूर्ण


/*
* must not LOCK sw_lock
*
*/
अटल व्योम u132_hcd_पूर्णांकerrupt_recv(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	काष्ठा u132_udev *udev = &u132->udev[address];
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		काष्ठा u132_ring *ring = endp->ring;
		u8 *u = urb->transfer_buffer + urb->actual_length;
		u8 *b = buf;
		पूर्णांक L = len;

		जबतक (L-- > 0)
			*u++ = *b++;

		urb->actual_length += len;
		अगर ((condition_code == TD_CC_NOERROR) &&
			(urb->transfer_buffer_length > urb->actual_length)) अणु
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			अगर (urb->actual_length > 0) अणु
				पूर्णांक retval;
				mutex_unlock(&u132->scheduler_lock);
				retval = edset_single(u132, ring, endp, urb,
					address, endp->toggle_bits,
					u132_hcd_पूर्णांकerrupt_recv);
				अगर (retval != 0)
					u132_hcd_giveback_urb(u132, endp, urb,
						retval);
			पूर्ण अन्यथा अणु
				ring->in_use = 0;
				endp->active = 0;
				endp->jअगरfies = jअगरfies +
					msecs_to_jअगरfies(urb->पूर्णांकerval);
				u132_ring_cancel_work(u132, ring);
				u132_ring_queue_work(u132, ring, 0);
				mutex_unlock(&u132->scheduler_lock);
				u132_endp_put_kref(u132, endp);
			पूर्ण
			वापस;
		पूर्ण अन्यथा अगर ((condition_code == TD_DATAUNDERRUN) &&
			((urb->transfer_flags & URB_SHORT_NOT_OK) == 0)) अणु
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb, 0);
			वापस;
		पूर्ण अन्यथा अणु
			अगर (condition_code == TD_CC_NOERROR) अणु
				endp->toggle_bits = toggle_bits;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 1 & toggle_bits);
			पूर्ण अन्यथा अगर (condition_code == TD_CC_STALL) अणु
				endp->toggle_bits = 0x2;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 0);
			पूर्ण अन्यथा अणु
				endp->toggle_bits = 0x2;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 0);
				dev_err(&u132->platक्रमm_dev->dev, "urb=%p givin"
					"g back INTERRUPT %s\n", urb,
					cc_to_text[condition_code]);
			पूर्ण
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_bulk_output_sent(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		काष्ठा u132_ring *ring = endp->ring;
		urb->actual_length += len;
		endp->toggle_bits = toggle_bits;
		अगर (urb->transfer_buffer_length > urb->actual_length) अणु
			पूर्णांक retval;
			mutex_unlock(&u132->scheduler_lock);
			retval = edset_output(u132, ring, endp, urb, address,
				endp->toggle_bits, u132_hcd_bulk_output_sent);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अणु
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb, 0);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_bulk_input_recv(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	काष्ठा u132_udev *udev = &u132->udev[address];
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		काष्ठा u132_ring *ring = endp->ring;
		u8 *u = urb->transfer_buffer + urb->actual_length;
		u8 *b = buf;
		पूर्णांक L = len;

		जबतक (L-- > 0)
			*u++ = *b++;

		urb->actual_length += len;
		अगर ((condition_code == TD_CC_NOERROR) &&
			(urb->transfer_buffer_length > urb->actual_length)) अणु
			पूर्णांक retval;
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_input(u132->platक्रमm_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, endp->toggle_bits,
				u132_hcd_bulk_input_recv);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अगर (condition_code == TD_CC_NOERROR) अणु
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण अन्यथा अगर ((condition_code == TD_DATAUNDERRUN) &&
			((urb->transfer_flags & URB_SHORT_NOT_OK) == 0)) अणु
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb, 0);
			वापस;
		पूर्ण अन्यथा अगर (condition_code == TD_DATAUNDERRUN) अणु
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			dev_warn(&u132->platक्रमm_dev->dev, "urb=%p(SHORT NOT OK"
				") giving back BULK IN %s\n", urb,
				cc_to_text[condition_code]);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb, 0);
			वापस;
		पूर्ण अन्यथा अगर (condition_code == TD_CC_STALL) अणु
			endp->toggle_bits = 0x2;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0, 0);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण अन्यथा अणु
			endp->toggle_bits = 0x2;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0, 0);
			dev_err(&u132->platक्रमm_dev->dev, "urb=%p giving back B"
				"ULK IN code=%d %s\n", urb, condition_code,
				cc_to_text[condition_code]);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_configure_empty_sent(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_configure_input_recv(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		काष्ठा u132_ring *ring = endp->ring;
		u8 *u = urb->transfer_buffer;
		u8 *b = buf;
		पूर्णांक L = len;

		जबतक (L-- > 0)
			*u++ = *b++;

		urb->actual_length = len;
		अगर ((condition_code == TD_CC_NOERROR) || ((condition_code ==
			TD_DATAUNDERRUN) && ((urb->transfer_flags &
			URB_SHORT_NOT_OK) == 0))) अणु
			पूर्णांक retval;
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_empty(u132->platक्रमm_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, 0x3,
				u132_hcd_configure_empty_sent);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अगर (condition_code == TD_CC_STALL) अणु
			mutex_unlock(&u132->scheduler_lock);
			dev_warn(&u132->platक्रमm_dev->dev, "giving back SETUP I"
				"NPUT STALL urb %p\n", urb);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण अन्यथा अणु
			mutex_unlock(&u132->scheduler_lock);
			dev_err(&u132->platक्रमm_dev->dev, "giving back SETUP IN"
				"PUT %s urb %p\n", cc_to_text[condition_code],
				urb);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_configure_empty_recv(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_configure_setup_sent(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		अगर (usb_pipein(urb->pipe)) अणु
			पूर्णांक retval;
			काष्ठा u132_ring *ring = endp->ring;
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_input(u132->platक्रमm_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, 0,
				u132_hcd_configure_input_recv);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अणु
			पूर्णांक retval;
			काष्ठा u132_ring *ring = endp->ring;
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_input(u132->platक्रमm_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, 0,
				u132_hcd_configure_empty_recv);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_क्रमागतeration_empty_recv(व्योम *data, काष्ठा urb *urb,
	u8 *buf, पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	काष्ठा u132_udev *udev = &u132->udev[address];
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		u132->addr[0].address = 0;
		endp->usb_addr = udev->usb_addr;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_क्रमागतeration_address_sent(व्योम *data, काष्ठा urb *urb,
	u8 *buf, पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		पूर्णांक retval;
		काष्ठा u132_ring *ring = endp->ring;
		mutex_unlock(&u132->scheduler_lock);
		retval = usb_ftdi_elan_edset_input(u132->platक्रमm_dev,
			ring->number, endp, urb, 0, endp->usb_endp, 0,
			u132_hcd_क्रमागतeration_empty_recv);
		अगर (retval != 0)
			u132_hcd_giveback_urb(u132, endp, urb, retval);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_initial_empty_sent(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_initial_input_recv(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		पूर्णांक retval;
		काष्ठा u132_ring *ring = endp->ring;
		u8 *u = urb->transfer_buffer;
		u8 *b = buf;
		पूर्णांक L = len;

		जबतक (L-- > 0)
			*u++ = *b++;

		urb->actual_length = len;
		mutex_unlock(&u132->scheduler_lock);
		retval = usb_ftdi_elan_edset_empty(u132->platक्रमm_dev,
			ring->number, endp, urb, address, endp->usb_endp, 0x3,
			u132_hcd_initial_empty_sent);
		अगर (retval != 0)
			u132_hcd_giveback_urb(u132, endp, urb, retval);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_initial_setup_sent(व्योम *data, काष्ठा urb *urb, u8 *buf,
	पूर्णांक len, पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
	पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null)
अणु
	काष्ठा u132_endp *endp = data;
	काष्ठा u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	mutex_lock(&u132->scheduler_lock);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_क्रमget_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (endp->dequeueing) अणु
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		वापस;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		वापस;
	पूर्ण अन्यथा अगर (!urb->unlinked) अणु
		पूर्णांक retval;
		काष्ठा u132_ring *ring = endp->ring;
		mutex_unlock(&u132->scheduler_lock);
		retval = usb_ftdi_elan_edset_input(u132->platक्रमm_dev,
			ring->number, endp, urb, address, endp->usb_endp, 0,
			u132_hcd_initial_input_recv);
		अगर (retval != 0)
			u132_hcd_giveback_urb(u132, endp, urb, retval);
		वापस;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		वापस;
	पूर्ण
पूर्ण

/*
* this work function is only executed from the work queue
*
*/
अटल व्योम u132_hcd_ring_work_scheduler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा u132_ring *ring =
		container_of(work, काष्ठा u132_ring, scheduler.work);
	काष्ठा u132 *u132 = ring->u132;
	mutex_lock(&u132->scheduler_lock);
	अगर (ring->in_use) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_ring_put_kref(u132, ring);
		वापस;
	पूर्ण अन्यथा अगर (ring->curr_endp) अणु
		काष्ठा u132_endp *endp, *last_endp = ring->curr_endp;
		अचिन्हित दीर्घ wakeup = 0;
		list_क्रम_each_entry(endp, &last_endp->endp_ring, endp_ring) अणु
			अगर (endp->queue_next == endp->queue_last) अणु
			पूर्ण अन्यथा अगर ((endp->delayed == 0)
				|| समय_after_eq(jअगरfies, endp->jअगरfies)) अणु
				ring->curr_endp = endp;
				u132_endp_cancel_work(u132, last_endp);
				u132_endp_queue_work(u132, last_endp, 0);
				mutex_unlock(&u132->scheduler_lock);
				u132_ring_put_kref(u132, ring);
				वापस;
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ delta = endp->jअगरfies - jअगरfies;
				अगर (delta > wakeup)
					wakeup = delta;
			पूर्ण
		पूर्ण
		अगर (last_endp->queue_next == last_endp->queue_last) अणु
		पूर्ण अन्यथा अगर ((last_endp->delayed == 0) || समय_after_eq(jअगरfies,
			last_endp->jअगरfies)) अणु
			u132_endp_cancel_work(u132, last_endp);
			u132_endp_queue_work(u132, last_endp, 0);
			mutex_unlock(&u132->scheduler_lock);
			u132_ring_put_kref(u132, ring);
			वापस;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ delta = last_endp->jअगरfies - jअगरfies;
			अगर (delta > wakeup)
				wakeup = delta;
		पूर्ण
		अगर (wakeup > 0) अणु
			u132_ring_requeue_work(u132, ring, wakeup);
			mutex_unlock(&u132->scheduler_lock);
			वापस;
		पूर्ण अन्यथा अणु
			mutex_unlock(&u132->scheduler_lock);
			u132_ring_put_kref(u132, ring);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_ring_put_kref(u132, ring);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u132_hcd_endp_work_scheduler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा u132_ring *ring;
	काष्ठा u132_endp *endp =
		container_of(work, काष्ठा u132_endp, scheduler.work);
	काष्ठा u132 *u132 = endp->u132;
	mutex_lock(&u132->scheduler_lock);
	ring = endp->ring;
	अगर (endp->edset_flush) अणु
		endp->edset_flush = 0;
		अगर (endp->dequeueing)
			usb_ftdi_elan_edset_flush(u132->platक्रमm_dev,
				ring->number, endp);
		mutex_unlock(&u132->scheduler_lock);
		u132_endp_put_kref(u132, endp);
		वापस;
	पूर्ण अन्यथा अगर (endp->active) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_endp_put_kref(u132, endp);
		वापस;
	पूर्ण अन्यथा अगर (ring->in_use) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_endp_put_kref(u132, endp);
		वापस;
	पूर्ण अन्यथा अगर (endp->queue_next == endp->queue_last) अणु
		mutex_unlock(&u132->scheduler_lock);
		u132_endp_put_kref(u132, endp);
		वापस;
	पूर्ण अन्यथा अगर (endp->pipetype == PIPE_INTERRUPT) अणु
		u8 address = u132->addr[endp->usb_addr].address;
		अगर (ring->in_use) अणु
			mutex_unlock(&u132->scheduler_lock);
			u132_endp_put_kref(u132, endp);
			वापस;
		पूर्ण अन्यथा अणु
			पूर्णांक retval;
			काष्ठा urb *urb = endp->urb_list[ENDP_QUEUE_MASK &
				endp->queue_next];
			endp->active = 1;
			ring->curr_endp = endp;
			ring->in_use = 1;
			mutex_unlock(&u132->scheduler_lock);
			retval = edset_single(u132, ring, endp, urb, address,
				endp->toggle_bits, u132_hcd_पूर्णांकerrupt_recv);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (endp->pipetype == PIPE_CONTROL) अणु
		u8 address = u132->addr[endp->usb_addr].address;
		अगर (ring->in_use) अणु
			mutex_unlock(&u132->scheduler_lock);
			u132_endp_put_kref(u132, endp);
			वापस;
		पूर्ण अन्यथा अगर (address == 0) अणु
			पूर्णांक retval;
			काष्ठा urb *urb = endp->urb_list[ENDP_QUEUE_MASK &
				endp->queue_next];
			endp->active = 1;
			ring->curr_endp = endp;
			ring->in_use = 1;
			mutex_unlock(&u132->scheduler_lock);
			retval = edset_setup(u132, ring, endp, urb, address,
				0x2, u132_hcd_initial_setup_sent);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अगर (endp->usb_addr == 0) अणु
			पूर्णांक retval;
			काष्ठा urb *urb = endp->urb_list[ENDP_QUEUE_MASK &
				endp->queue_next];
			endp->active = 1;
			ring->curr_endp = endp;
			ring->in_use = 1;
			mutex_unlock(&u132->scheduler_lock);
			retval = edset_setup(u132, ring, endp, urb, 0, 0x2,
				u132_hcd_क्रमागतeration_address_sent);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण अन्यथा अणु
			पूर्णांक retval;
			काष्ठा urb *urb = endp->urb_list[ENDP_QUEUE_MASK &
				endp->queue_next];
			address = u132->addr[endp->usb_addr].address;
			endp->active = 1;
			ring->curr_endp = endp;
			ring->in_use = 1;
			mutex_unlock(&u132->scheduler_lock);
			retval = edset_setup(u132, ring, endp, urb, address,
				0x2, u132_hcd_configure_setup_sent);
			अगर (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (endp->input) अणु
			u8 address = u132->addr[endp->usb_addr].address;
			अगर (ring->in_use) अणु
				mutex_unlock(&u132->scheduler_lock);
				u132_endp_put_kref(u132, endp);
				वापस;
			पूर्ण अन्यथा अणु
				पूर्णांक retval;
				काष्ठा urb *urb = endp->urb_list[
					ENDP_QUEUE_MASK & endp->queue_next];
				endp->active = 1;
				ring->curr_endp = endp;
				ring->in_use = 1;
				mutex_unlock(&u132->scheduler_lock);
				retval = edset_input(u132, ring, endp, urb,
					address, endp->toggle_bits,
					u132_hcd_bulk_input_recv);
				अगर (retval == 0) अणु
				पूर्ण अन्यथा
					u132_hcd_giveback_urb(u132, endp, urb,
						retval);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु	/* output pipe */
			u8 address = u132->addr[endp->usb_addr].address;
			अगर (ring->in_use) अणु
				mutex_unlock(&u132->scheduler_lock);
				u132_endp_put_kref(u132, endp);
				वापस;
			पूर्ण अन्यथा अणु
				पूर्णांक retval;
				काष्ठा urb *urb = endp->urb_list[
					ENDP_QUEUE_MASK & endp->queue_next];
				endp->active = 1;
				ring->curr_endp = endp;
				ring->in_use = 1;
				mutex_unlock(&u132->scheduler_lock);
				retval = edset_output(u132, ring, endp, urb,
					address, endp->toggle_bits,
					u132_hcd_bulk_output_sent);
				अगर (retval == 0) अणु
				पूर्ण अन्यथा
					u132_hcd_giveback_urb(u132, endp, urb,
						retval);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#अगर_घोषित CONFIG_PM

अटल व्योम port_घातer(काष्ठा u132 *u132, पूर्णांक pn, पूर्णांक is_on)
अणु
	u132->port[pn].घातer = is_on;
पूर्ण

#पूर्ण_अगर

अटल व्योम u132_घातer(काष्ठा u132 *u132, पूर्णांक is_on)
अणु
	काष्ठा usb_hcd *hcd = u132_to_hcd(u132)
		;	/* hub is inactive unless the port is घातered */
	अगर (is_on) अणु
		अगर (u132->घातer)
			वापस;
		u132->घातer = 1;
	पूर्ण अन्यथा अणु
		u132->घातer = 0;
		hcd->state = HC_STATE_HALT;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_periodic_reinit(काष्ठा u132 *u132)
अणु
	पूर्णांक retval;
	u32 fi = u132->hc_fmपूर्णांकerval & 0x03fff;
	u32 fit;
	u32 fmपूर्णांकerval;
	retval = u132_पढ़ो_pcimem(u132, fmपूर्णांकerval, &fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	fit = fmपूर्णांकerval & FIT;
	retval = u132_ग_लिखो_pcimem(u132, fmपूर्णांकerval,
		(fit ^ FIT) | u132->hc_fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	वापस u132_ग_लिखो_pcimem(u132, periodicstart,
	       ((9 * fi) / 10) & 0x3fff);
पूर्ण

अटल अक्षर *hcfs2string(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल OHCI_USB_RESET:
		वापस "reset";
	हाल OHCI_USB_RESUME:
		वापस "resume";
	हाल OHCI_USB_OPER:
		वापस "operational";
	हाल OHCI_USB_SUSPEND:
		वापस "suspend";
	पूर्ण
	वापस "?";
पूर्ण

अटल पूर्णांक u132_init(काष्ठा u132 *u132)
अणु
	पूर्णांक retval;
	u32 control;
	u132_disable(u132);
	u132->next_statechange = jअगरfies;
	retval = u132_ग_लिखो_pcimem(u132, पूर्णांकrdisable, OHCI_INTR_MIE);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, control, &control);
	अगर (retval)
		वापस retval;
	अगर (u132->num_ports == 0) अणु
		u32 rh_a = -1;
		retval = u132_पढ़ो_pcimem(u132, roothub.a, &rh_a);
		अगर (retval)
			वापस retval;
		u132->num_ports = rh_a & RH_A_NDP;
		retval = पढ़ो_roothub_info(u132);
		अगर (retval)
			वापस retval;
	पूर्ण
	अगर (u132->num_ports > MAX_U132_PORTS)
		वापस -EINVAL;

	वापस 0;
पूर्ण


/* Start an OHCI controller, set the BUS operational
* resets USB and controller
* enable पूर्णांकerrupts
*/
अटल पूर्णांक u132_run(काष्ठा u132 *u132)
अणु
	पूर्णांक retval;
	u32 control;
	u32 status;
	u32 fmपूर्णांकerval;
	u32 periodicstart;
	u32 cmdstatus;
	u32 roothub_a;
	पूर्णांक mask = OHCI_INTR_INIT;
	पूर्णांक first = u132->hc_fmपूर्णांकerval == 0;
	पूर्णांक sleep_समय = 0;
	पूर्णांक reset_समयout = 30;	/* ... allow extra समय */
	u132_disable(u132);
	अगर (first) अणु
		u32 temp;
		retval = u132_पढ़ो_pcimem(u132, fmपूर्णांकerval, &temp);
		अगर (retval)
			वापस retval;
		u132->hc_fmपूर्णांकerval = temp & 0x3fff;
		u132->hc_fmपूर्णांकerval |= FSMP(u132->hc_fmपूर्णांकerval) << 16;
	पूर्ण
	retval = u132_पढ़ो_pcimem(u132, control, &u132->hc_control);
	अगर (retval)
		वापस retval;
	dev_info(&u132->platक्रमm_dev->dev, "resetting from state '%s', control "
		"= %08X\n", hcfs2string(u132->hc_control & OHCI_CTRL_HCFS),
		u132->hc_control);
	चयन (u132->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_OPER:
		sleep_समय = 0;
		अवरोध;
	हाल OHCI_USB_SUSPEND:
	हाल OHCI_USB_RESUME:
		u132->hc_control &= OHCI_CTRL_RWC;
		u132->hc_control |= OHCI_USB_RESUME;
		sleep_समय = 10;
		अवरोध;
	शेष:
		u132->hc_control &= OHCI_CTRL_RWC;
		u132->hc_control |= OHCI_USB_RESET;
		sleep_समय = 50;
		अवरोध;
	पूर्ण
	retval = u132_ग_लिखो_pcimem(u132, control, u132->hc_control);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, control, &control);
	अगर (retval)
		वापस retval;
	msleep(sleep_समय);
	retval = u132_पढ़ो_pcimem(u132, roothub.a, &roothub_a);
	अगर (retval)
		वापस retval;
	अगर (!(roothub_a & RH_A_NPS)) अणु
		पूर्णांक temp;	/* घातer करोwn each port */
		क्रम (temp = 0; temp < u132->num_ports; temp++) अणु
			retval = u132_ग_लिखो_pcimem(u132,
				roothub.portstatus[temp], RH_PS_LSDA);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण
	retval = u132_पढ़ो_pcimem(u132, control, &control);
	अगर (retval)
		वापस retval;
retry:
	retval = u132_पढ़ो_pcimem(u132, cmdstatus, &status);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, cmdstatus, OHCI_HCR);
	अगर (retval)
		वापस retval;
extra:	अणु
		retval = u132_पढ़ो_pcimem(u132, cmdstatus, &status);
		अगर (retval)
			वापस retval;
		अगर (0 != (status & OHCI_HCR)) अणु
			अगर (--reset_समयout == 0) अणु
				dev_err(&u132->platक्रमm_dev->dev, "USB HC reset"
					" timed out!\n");
				वापस -ENODEV;
			पूर्ण अन्यथा अणु
				msleep(5);
				जाओ extra;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (u132->flags & OHCI_QUIRK_INITRESET) अणु
		retval = u132_ग_लिखो_pcimem(u132, control, u132->hc_control);
		अगर (retval)
			वापस retval;
		retval = u132_पढ़ो_pcimem(u132, control, &control);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = u132_ग_लिखो_pcimem(u132, ed_controlhead, 0x00000000);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, ed_bulkhead, 0x11000000);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, hcca, 0x00000000);
	अगर (retval)
		वापस retval;
	retval = u132_periodic_reinit(u132);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, fmपूर्णांकerval, &fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, periodicstart, &periodicstart);
	अगर (retval)
		वापस retval;
	अगर (0 == (fmपूर्णांकerval & 0x3fff0000) || 0 == periodicstart) अणु
		अगर (!(u132->flags & OHCI_QUIRK_INITRESET)) अणु
			u132->flags |= OHCI_QUIRK_INITRESET;
			जाओ retry;
		पूर्ण अन्यथा
			dev_err(&u132->platक्रमm_dev->dev, "init err(%08x %04x)"
				"\n", fmपूर्णांकerval, periodicstart);
	पूर्ण			/* start controller operations */
	u132->hc_control &= OHCI_CTRL_RWC;
	u132->hc_control |= OHCI_CONTROL_INIT | OHCI_CTRL_BLE | OHCI_USB_OPER;
	retval = u132_ग_लिखो_pcimem(u132, control, u132->hc_control);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, cmdstatus, OHCI_BLF);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, cmdstatus, &cmdstatus);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, control, &control);
	अगर (retval)
		वापस retval;
	u132_to_hcd(u132)->state = HC_STATE_RUNNING;
	retval = u132_ग_लिखो_pcimem(u132, roothub.status, RH_HS_DRWE);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, पूर्णांकrstatus, mask);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, पूर्णांकrdisable,
		OHCI_INTR_MIE | OHCI_INTR_OC | OHCI_INTR_RHSC | OHCI_INTR_FNO |
		OHCI_INTR_UE | OHCI_INTR_RD | OHCI_INTR_SF | OHCI_INTR_WDH |
		OHCI_INTR_SO);
	अगर (retval)
		वापस retval;	/* handle root hub init quirks ... */
	retval = u132_पढ़ो_pcimem(u132, roothub.a, &roothub_a);
	अगर (retval)
		वापस retval;
	roothub_a &= ~(RH_A_PSM | RH_A_OCPM);
	अगर (u132->flags & OHCI_QUIRK_SUPERIO) अणु
		roothub_a |= RH_A_NOCP;
		roothub_a &= ~(RH_A_POTPGT | RH_A_NPS);
		retval = u132_ग_लिखो_pcimem(u132, roothub.a, roothub_a);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अगर ((u132->flags & OHCI_QUIRK_AMD756) || distrust_firmware) अणु
		roothub_a |= RH_A_NPS;
		retval = u132_ग_लिखो_pcimem(u132, roothub.a, roothub_a);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = u132_ग_लिखो_pcimem(u132, roothub.status, RH_HS_LPSC);
	अगर (retval)
		वापस retval;
	retval = u132_ग_लिखो_pcimem(u132, roothub.b,
		(roothub_a & RH_A_NPS) ? 0 : RH_B_PPCM);
	अगर (retval)
		वापस retval;
	retval = u132_पढ़ो_pcimem(u132, control, &control);
	अगर (retval)
		वापस retval;
	mdelay((roothub_a >> 23) & 0x1fe);
	u132_to_hcd(u132)->state = HC_STATE_RUNNING;
	वापस 0;
पूर्ण

अटल व्योम u132_hcd_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "u132 device %p(hcd=%p) has b"
			"een removed %d\n", u132, hcd, u132->going);
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device hcd=%p is being remov"
			"ed\n", hcd);
	पूर्ण अन्यथा अणु
		mutex_lock(&u132->sw_lock);
		msleep(100);
		u132_घातer(u132, 0);
		mutex_unlock(&u132->sw_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक u132_hcd_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अगर (hcd->self.controller) अणु
		पूर्णांक retval;
		काष्ठा platक्रमm_device *pdev =
			to_platक्रमm_device(hcd->self.controller);
		u16 venकरोr = ((काष्ठा u132_platक्रमm_data *)
			dev_get_platdata(&pdev->dev))->venकरोr;
		u16 device = ((काष्ठा u132_platक्रमm_data *)
			dev_get_platdata(&pdev->dev))->device;
		mutex_lock(&u132->sw_lock);
		msleep(10);
		अगर (venकरोr == PCI_VENDOR_ID_AMD && device == 0x740c) अणु
			u132->flags = OHCI_QUIRK_AMD756;
		पूर्ण अन्यथा अगर (venकरोr == PCI_VENDOR_ID_OPTI && device == 0xc861) अणु
			dev_err(&u132->platक्रमm_dev->dev, "WARNING: OPTi workar"
				"ounds unavailable\n");
		पूर्ण अन्यथा अगर (venकरोr == PCI_VENDOR_ID_COMPAQ && device == 0xa0f8)
			u132->flags |= OHCI_QUIRK_ZFMICRO;
		retval = u132_run(u132);
		अगर (retval) अणु
			u132_disable(u132);
			u132->going = 1;
		पूर्ण
		msleep(100);
		mutex_unlock(&u132->sw_lock);
		वापस retval;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "platform_device missing\n");
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_hcd_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		पूर्णांक retval;
		mutex_lock(&u132->sw_lock);
		retval = u132_init(u132);
		अगर (retval) अणु
			u132_disable(u132);
			u132->going = 1;
		पूर्ण
		mutex_unlock(&u132->sw_lock);
		वापस retval;
	पूर्ण
पूर्ण

अटल पूर्णांक create_endpoपूर्णांक_and_queue_पूर्णांक(काष्ठा u132 *u132,
	काष्ठा u132_udev *udev, काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, u8 usb_addr, u8 usb_endp, u8 address,
	gfp_t mem_flags)
अणु
	काष्ठा u132_ring *ring;
	अचिन्हित दीर्घ irqs;
	पूर्णांक rc;
	u8 endp_number;
	काष्ठा u132_endp *endp = kदो_स्मृति(माप(काष्ठा u132_endp), mem_flags);

	अगर (!endp)
		वापस -ENOMEM;

	spin_lock_init(&endp->queue_lock.slock);
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	rc = usb_hcd_link_urb_to_ep(u132_to_hcd(u132), urb);
	अगर (rc) अणु
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kमुक्त(endp);
		वापस rc;
	पूर्ण

	endp_number = ++u132->num_endpoपूर्णांकs;
	urb->ep->hcpriv = u132->endp[endp_number - 1] = endp;
	INIT_DELAYED_WORK(&endp->scheduler, u132_hcd_endp_work_scheduler);
	INIT_LIST_HEAD(&endp->urb_more);
	ring = endp->ring = &u132->ring[0];
	अगर (ring->curr_endp) अणु
		list_add_tail(&endp->endp_ring, &ring->curr_endp->endp_ring);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&endp->endp_ring);
		ring->curr_endp = endp;
	पूर्ण
	ring->length += 1;
	endp->dequeueing = 0;
	endp->edset_flush = 0;
	endp->active = 0;
	endp->delayed = 0;
	endp->endp_number = endp_number;
	endp->u132 = u132;
	endp->hep = urb->ep;
	endp->pipetype = usb_pipetype(urb->pipe);
	u132_endp_init_kref(u132, endp);
	अगर (usb_pipein(urb->pipe)) अणु
		endp->toggle_bits = 0x2;
		usb_settoggle(udev->usb_device, usb_endp, 0, 0);
		endp->input = 1;
		endp->output = 0;
		udev->endp_number_in[usb_endp] = endp_number;
		u132_udev_get_kref(u132, udev);
	पूर्ण अन्यथा अणु
		endp->toggle_bits = 0x2;
		usb_settoggle(udev->usb_device, usb_endp, 1, 0);
		endp->input = 0;
		endp->output = 1;
		udev->endp_number_out[usb_endp] = endp_number;
		u132_udev_get_kref(u132, udev);
	पूर्ण
	urb->hcpriv = u132;
	endp->delayed = 1;
	endp->jअगरfies = jअगरfies + msecs_to_jअगरfies(urb->पूर्णांकerval);
	endp->udev_number = address;
	endp->usb_addr = usb_addr;
	endp->usb_endp = usb_endp;
	endp->queue_size = 1;
	endp->queue_last = 0;
	endp->queue_next = 0;
	endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
	spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
	u132_endp_queue_work(u132, endp, msecs_to_jअगरfies(urb->पूर्णांकerval));
	वापस 0;
पूर्ण

अटल पूर्णांक queue_पूर्णांक_on_old_endpoपूर्णांक(काष्ठा u132 *u132,
	काष्ठा u132_udev *udev, काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, काष्ठा u132_endp *endp, u8 usb_addr,
	u8 usb_endp, u8 address)
अणु
	urb->hcpriv = u132;
	endp->delayed = 1;
	endp->jअगरfies = jअगरfies + msecs_to_jअगरfies(urb->पूर्णांकerval);
	अगर (endp->queue_size++ < ENDP_QUEUE_SIZE) अणु
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
	पूर्ण अन्यथा अणु
		काष्ठा u132_urbq *urbq = kदो_स्मृति(माप(काष्ठा u132_urbq),
			GFP_ATOMIC);
		अगर (urbq == शून्य) अणु
			endp->queue_size -= 1;
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			list_add_tail(&urbq->urb_more, &endp->urb_more);
			urbq->urb = urb;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_endpoपूर्णांक_and_queue_bulk(काष्ठा u132 *u132,
	काष्ठा u132_udev *udev, काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, u8 usb_addr, u8 usb_endp, u8 address,
	gfp_t mem_flags)
अणु
	पूर्णांक ring_number;
	काष्ठा u132_ring *ring;
	अचिन्हित दीर्घ irqs;
	पूर्णांक rc;
	u8 endp_number;
	काष्ठा u132_endp *endp = kदो_स्मृति(माप(काष्ठा u132_endp), mem_flags);

	अगर (!endp)
		वापस -ENOMEM;

	spin_lock_init(&endp->queue_lock.slock);
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	rc = usb_hcd_link_urb_to_ep(u132_to_hcd(u132), urb);
	अगर (rc) अणु
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kमुक्त(endp);
		वापस rc;
	पूर्ण

	endp_number = ++u132->num_endpoपूर्णांकs;
	urb->ep->hcpriv = u132->endp[endp_number - 1] = endp;
	INIT_DELAYED_WORK(&endp->scheduler, u132_hcd_endp_work_scheduler);
	INIT_LIST_HEAD(&endp->urb_more);
	endp->dequeueing = 0;
	endp->edset_flush = 0;
	endp->active = 0;
	endp->delayed = 0;
	endp->endp_number = endp_number;
	endp->u132 = u132;
	endp->hep = urb->ep;
	endp->pipetype = usb_pipetype(urb->pipe);
	u132_endp_init_kref(u132, endp);
	अगर (usb_pipein(urb->pipe)) अणु
		endp->toggle_bits = 0x2;
		usb_settoggle(udev->usb_device, usb_endp, 0, 0);
		ring_number = 3;
		endp->input = 1;
		endp->output = 0;
		udev->endp_number_in[usb_endp] = endp_number;
		u132_udev_get_kref(u132, udev);
	पूर्ण अन्यथा अणु
		endp->toggle_bits = 0x2;
		usb_settoggle(udev->usb_device, usb_endp, 1, 0);
		ring_number = 2;
		endp->input = 0;
		endp->output = 1;
		udev->endp_number_out[usb_endp] = endp_number;
		u132_udev_get_kref(u132, udev);
	पूर्ण
	ring = endp->ring = &u132->ring[ring_number - 1];
	अगर (ring->curr_endp) अणु
		list_add_tail(&endp->endp_ring, &ring->curr_endp->endp_ring);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&endp->endp_ring);
		ring->curr_endp = endp;
	पूर्ण
	ring->length += 1;
	urb->hcpriv = u132;
	endp->udev_number = address;
	endp->usb_addr = usb_addr;
	endp->usb_endp = usb_endp;
	endp->queue_size = 1;
	endp->queue_last = 0;
	endp->queue_next = 0;
	endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
	spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
	u132_endp_queue_work(u132, endp, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक queue_bulk_on_old_endpoपूर्णांक(काष्ठा u132 *u132, काष्ठा u132_udev *udev,
	काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, काष्ठा u132_endp *endp, u8 usb_addr,
	u8 usb_endp, u8 address)
अणु
	urb->hcpriv = u132;
	अगर (endp->queue_size++ < ENDP_QUEUE_SIZE) अणु
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
	पूर्ण अन्यथा अणु
		काष्ठा u132_urbq *urbq = kदो_स्मृति(माप(काष्ठा u132_urbq),
			GFP_ATOMIC);
		अगर (urbq == शून्य) अणु
			endp->queue_size -= 1;
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			list_add_tail(&urbq->urb_more, &endp->urb_more);
			urbq->urb = urb;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_endpoपूर्णांक_and_queue_control(काष्ठा u132 *u132,
	काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, u8 usb_addr, u8 usb_endp,
	gfp_t mem_flags)
अणु
	काष्ठा u132_ring *ring;
	अचिन्हित दीर्घ irqs;
	पूर्णांक rc;
	u8 endp_number;
	काष्ठा u132_endp *endp = kदो_स्मृति(माप(काष्ठा u132_endp), mem_flags);

	अगर (!endp)
		वापस -ENOMEM;

	spin_lock_init(&endp->queue_lock.slock);
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	rc = usb_hcd_link_urb_to_ep(u132_to_hcd(u132), urb);
	अगर (rc) अणु
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kमुक्त(endp);
		वापस rc;
	पूर्ण

	endp_number = ++u132->num_endpoपूर्णांकs;
	urb->ep->hcpriv = u132->endp[endp_number - 1] = endp;
	INIT_DELAYED_WORK(&endp->scheduler, u132_hcd_endp_work_scheduler);
	INIT_LIST_HEAD(&endp->urb_more);
	ring = endp->ring = &u132->ring[0];
	अगर (ring->curr_endp) अणु
		list_add_tail(&endp->endp_ring, &ring->curr_endp->endp_ring);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&endp->endp_ring);
		ring->curr_endp = endp;
	पूर्ण
	ring->length += 1;
	endp->dequeueing = 0;
	endp->edset_flush = 0;
	endp->active = 0;
	endp->delayed = 0;
	endp->endp_number = endp_number;
	endp->u132 = u132;
	endp->hep = urb->ep;
	u132_endp_init_kref(u132, endp);
	u132_endp_get_kref(u132, endp);
	अगर (usb_addr == 0) अणु
		u8 address = u132->addr[usb_addr].address;
		काष्ठा u132_udev *udev = &u132->udev[address];
		endp->udev_number = address;
		endp->usb_addr = usb_addr;
		endp->usb_endp = usb_endp;
		endp->input = 1;
		endp->output = 1;
		endp->pipetype = usb_pipetype(urb->pipe);
		u132_udev_init_kref(u132, udev);
		u132_udev_get_kref(u132, udev);
		udev->endp_number_in[usb_endp] = endp_number;
		udev->endp_number_out[usb_endp] = endp_number;
		urb->hcpriv = u132;
		endp->queue_size = 1;
		endp->queue_last = 0;
		endp->queue_next = 0;
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		u132_endp_queue_work(u132, endp, 0);
		वापस 0;
	पूर्ण अन्यथा अणु		/*(usb_addr > 0) */
		u8 address = u132->addr[usb_addr].address;
		काष्ठा u132_udev *udev = &u132->udev[address];
		endp->udev_number = address;
		endp->usb_addr = usb_addr;
		endp->usb_endp = usb_endp;
		endp->input = 1;
		endp->output = 1;
		endp->pipetype = usb_pipetype(urb->pipe);
		u132_udev_get_kref(u132, udev);
		udev->क्रमागतeration = 2;
		udev->endp_number_in[usb_endp] = endp_number;
		udev->endp_number_out[usb_endp] = endp_number;
		urb->hcpriv = u132;
		endp->queue_size = 1;
		endp->queue_last = 0;
		endp->queue_next = 0;
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		u132_endp_queue_work(u132, endp, 0);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक queue_control_on_old_endpoपूर्णांक(काष्ठा u132 *u132,
	काष्ठा urb *urb,
	काष्ठा usb_device *usb_dev, काष्ठा u132_endp *endp, u8 usb_addr,
	u8 usb_endp)
अणु
	अगर (usb_addr == 0) अणु
		अगर (usb_pipein(urb->pipe)) अणु
			urb->hcpriv = u132;
			अगर (endp->queue_size++ < ENDP_QUEUE_SIZE) अणु
				endp->urb_list[ENDP_QUEUE_MASK &
					endp->queue_last++] = urb;
			पूर्ण अन्यथा अणु
				काष्ठा u132_urbq *urbq =
					kदो_स्मृति(माप(काष्ठा u132_urbq),
					GFP_ATOMIC);
				अगर (urbq == शून्य) अणु
					endp->queue_size -= 1;
					वापस -ENOMEM;
				पूर्ण अन्यथा अणु
					list_add_tail(&urbq->urb_more,
						&endp->urb_more);
					urbq->urb = urb;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अणु	/* usb_pipeout(urb->pipe) */
			काष्ठा u132_addr *addr = &u132->addr[usb_dev->devnum];
			पूर्णांक I = MAX_U132_UDEVS;
			पूर्णांक i = 0;
			जबतक (--I > 0) अणु
				काष्ठा u132_udev *udev = &u132->udev[++i];
				अगर (udev->usb_device) अणु
					जारी;
				पूर्ण अन्यथा अणु
					udev->क्रमागतeration = 1;
					u132->addr[0].address = i;
					endp->udev_number = i;
					udev->udev_number = i;
					udev->usb_addr = usb_dev->devnum;
					u132_udev_init_kref(u132, udev);
					udev->endp_number_in[usb_endp] =
						endp->endp_number;
					u132_udev_get_kref(u132, udev);
					udev->endp_number_out[usb_endp] =
						endp->endp_number;
					udev->usb_device = usb_dev;
					((u8 *) (urb->setup_packet))[2] =
						addr->address = i;
					u132_udev_get_kref(u132, udev);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (I == 0) अणु
				dev_err(&u132->platक्रमm_dev->dev, "run out of d"
					"evice space\n");
				वापस -EINVAL;
			पूर्ण
			urb->hcpriv = u132;
			अगर (endp->queue_size++ < ENDP_QUEUE_SIZE) अणु
				endp->urb_list[ENDP_QUEUE_MASK &
					endp->queue_last++] = urb;
			पूर्ण अन्यथा अणु
				काष्ठा u132_urbq *urbq =
					kदो_स्मृति(माप(काष्ठा u132_urbq),
					GFP_ATOMIC);
				अगर (urbq == शून्य) अणु
					endp->queue_size -= 1;
					वापस -ENOMEM;
				पूर्ण अन्यथा अणु
					list_add_tail(&urbq->urb_more,
						&endp->urb_more);
					urbq->urb = urb;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु		/*(usb_addr > 0) */
		u8 address = u132->addr[usb_addr].address;
		काष्ठा u132_udev *udev = &u132->udev[address];
		urb->hcpriv = u132;
		अगर (udev->क्रमागतeration != 2)
			udev->क्रमागतeration = 2;
		अगर (endp->queue_size++ < ENDP_QUEUE_SIZE) अणु
			endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] =
				urb;
		पूर्ण अन्यथा अणु
			काष्ठा u132_urbq *urbq =
				kदो_स्मृति(माप(काष्ठा u132_urbq), GFP_ATOMIC);
			अगर (urbq == शून्य) अणु
				endp->queue_size -= 1;
				वापस -ENOMEM;
			पूर्ण अन्यथा अणु
				list_add_tail(&urbq->urb_more, &endp->urb_more);
				urbq->urb = urb;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		gfp_t mem_flags)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (irqs_disabled()) अणु
		अगर (gfpflags_allow_blocking(mem_flags)) अणु
			prपूर्णांकk(KERN_ERR "invalid context for function that might sleep\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		u8 usb_addr = usb_pipedevice(urb->pipe);
		u8 usb_endp = usb_pipeendpoपूर्णांक(urb->pipe);
		काष्ठा usb_device *usb_dev = urb->dev;
		अगर (usb_pipetype(urb->pipe) == PIPE_INTERRUPT) अणु
			u8 address = u132->addr[usb_addr].address;
			काष्ठा u132_udev *udev = &u132->udev[address];
			काष्ठा u132_endp *endp = urb->ep->hcpriv;
			urb->actual_length = 0;
			अगर (endp) अणु
				अचिन्हित दीर्घ irqs;
				पूर्णांक retval;
				spin_lock_irqsave(&endp->queue_lock.slock,
					irqs);
				retval = usb_hcd_link_urb_to_ep(hcd, urb);
				अगर (retval == 0) अणु
					retval = queue_पूर्णांक_on_old_endpoपूर्णांक(
							u132, udev, urb,
							usb_dev, endp,
							usb_addr, usb_endp,
							address);
					अगर (retval)
						usb_hcd_unlink_urb_from_ep(
	hcd, urb);
				पूर्ण
				spin_unlock_irqrestore(&endp->queue_lock.slock,
					irqs);
				अगर (retval) अणु
					वापस retval;
				पूर्ण अन्यथा अणु
					u132_endp_queue_work(u132, endp,
						msecs_to_jअगरfies(urb->पूर्णांकerval))
						;
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा अगर (u132->num_endpoपूर्णांकs == MAX_U132_ENDPS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अणु	/*(endp == शून्य) */
				वापस create_endpoपूर्णांक_and_queue_पूर्णांक(u132, udev,
						urb, usb_dev, usb_addr,
						usb_endp, address, mem_flags);
			पूर्ण
		पूर्ण अन्यथा अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
			dev_err(&u132->platक्रमm_dev->dev, "the hardware does no"
				"t support PIPE_ISOCHRONOUS\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (usb_pipetype(urb->pipe) == PIPE_BULK) अणु
			u8 address = u132->addr[usb_addr].address;
			काष्ठा u132_udev *udev = &u132->udev[address];
			काष्ठा u132_endp *endp = urb->ep->hcpriv;
			urb->actual_length = 0;
			अगर (endp) अणु
				अचिन्हित दीर्घ irqs;
				पूर्णांक retval;
				spin_lock_irqsave(&endp->queue_lock.slock,
					irqs);
				retval = usb_hcd_link_urb_to_ep(hcd, urb);
				अगर (retval == 0) अणु
					retval = queue_bulk_on_old_endpoपूर्णांक(
							u132, udev, urb,
							usb_dev, endp,
							usb_addr, usb_endp,
							address);
					अगर (retval)
						usb_hcd_unlink_urb_from_ep(
	hcd, urb);
				पूर्ण
				spin_unlock_irqrestore(&endp->queue_lock.slock,
					irqs);
				अगर (retval) अणु
					वापस retval;
				पूर्ण अन्यथा अणु
					u132_endp_queue_work(u132, endp, 0);
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा अगर (u132->num_endpoपूर्णांकs == MAX_U132_ENDPS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा
				वापस create_endpoपूर्णांक_and_queue_bulk(u132,
					udev, urb, usb_dev, usb_addr,
					usb_endp, address, mem_flags);
		पूर्ण अन्यथा अणु
			काष्ठा u132_endp *endp = urb->ep->hcpriv;
			u16 urb_size = 8;
			u8 *b = urb->setup_packet;
			पूर्णांक i = 0;
			अक्षर data[30 * 3 + 4];
			अक्षर *d = data;
			पूर्णांक m = (माप(data) - 1) / 3;
			पूर्णांक l = 0;
			data[0] = 0;
			जबतक (urb_size-- > 0) अणु
				अगर (i > m) अणु
				पूर्ण अन्यथा अगर (i++ < m) अणु
					पूर्णांक w = प्र_लिखो(d, " %02X", *b++);
					d += w;
					l += w;
				पूर्ण अन्यथा
					d += प्र_लिखो(d, " ..");
			पूर्ण
			अगर (endp) अणु
				अचिन्हित दीर्घ irqs;
				पूर्णांक retval;
				spin_lock_irqsave(&endp->queue_lock.slock,
					irqs);
				retval = usb_hcd_link_urb_to_ep(hcd, urb);
				अगर (retval == 0) अणु
					retval = queue_control_on_old_endpoपूर्णांक(
							u132, urb, usb_dev,
							endp, usb_addr,
							usb_endp);
					अगर (retval)
						usb_hcd_unlink_urb_from_ep(
								hcd, urb);
				पूर्ण
				spin_unlock_irqrestore(&endp->queue_lock.slock,
					irqs);
				अगर (retval) अणु
					वापस retval;
				पूर्ण अन्यथा अणु
					u132_endp_queue_work(u132, endp, 0);
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा अगर (u132->num_endpoपूर्णांकs == MAX_U132_ENDPS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा
				वापस create_endpoपूर्णांक_and_queue_control(u132,
					urb, usb_dev, usb_addr, usb_endp,
					mem_flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dequeue_from_overflow_chain(काष्ठा u132 *u132,
	काष्ठा u132_endp *endp, काष्ठा urb *urb)
अणु
	काष्ठा u132_urbq *urbq;

	list_क्रम_each_entry(urbq, &endp->urb_more, urb_more) अणु
		अगर (urbq->urb == urb) अणु
			काष्ठा usb_hcd *hcd = u132_to_hcd(u132);
			list_del(&urbq->urb_more);
			endp->queue_size -= 1;
			urb->error_count = 0;
			usb_hcd_giveback_urb(hcd, urb, 0);
			वापस 0;
		पूर्ण अन्यथा
			जारी;
	पूर्ण
	dev_err(&u132->platक्रमm_dev->dev, "urb=%p not found in endp[%d]=%p ring"
		"[%d] %c%c usb_endp=%d usb_addr=%d size=%d next=%04X last=%04X"
		"\n", urb, endp->endp_number, endp, endp->ring->number,
		endp->input ? 'I' : ' ', endp->output ? 'O' : ' ',
		endp->usb_endp, endp->usb_addr, endp->queue_size,
		endp->queue_next, endp->queue_last);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक u132_endp_urb_dequeue(काष्ठा u132 *u132, काष्ठा u132_endp *endp,
		काष्ठा urb *urb, पूर्णांक status)
अणु
	अचिन्हित दीर्घ irqs;
	पूर्णांक rc;

	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	rc = usb_hcd_check_unlink_urb(u132_to_hcd(u132), urb, status);
	अगर (rc) अणु
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		वापस rc;
	पूर्ण
	अगर (endp->queue_size == 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "urb=%p not found in endp[%d]"
			"=%p ring[%d] %c%c usb_endp=%d usb_addr=%d\n", urb,
			endp->endp_number, endp, endp->ring->number,
			endp->input ? 'I' : ' ', endp->output ? 'O' : ' ',
			endp->usb_endp, endp->usb_addr);
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		वापस -EINVAL;
	पूर्ण
	अगर (urb == endp->urb_list[ENDP_QUEUE_MASK & endp->queue_next]) अणु
		अगर (endp->active) अणु
			endp->dequeueing = 1;
			endp->edset_flush = 1;
			u132_endp_queue_work(u132, endp, 0);
			spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
			वापस 0;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
			u132_hcd_abanकरोn_urb(u132, endp, urb, status);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		u16 queue_list = 0;
		u16 queue_size = endp->queue_size;
		u16 queue_scan = endp->queue_next;
		काष्ठा urb **urb_slot = शून्य;
		जबतक (++queue_list < ENDP_QUEUE_SIZE && --queue_size > 0) अणु
			अगर (urb == endp->urb_list[ENDP_QUEUE_MASK &
				++queue_scan]) अणु
				urb_slot = &endp->urb_list[ENDP_QUEUE_MASK &
					queue_scan];
				अवरोध;
			पूर्ण अन्यथा
				जारी;
		पूर्ण
		जबतक (++queue_list < ENDP_QUEUE_SIZE && --queue_size > 0) अणु
			*urb_slot = endp->urb_list[ENDP_QUEUE_MASK &
				++queue_scan];
			urb_slot = &endp->urb_list[ENDP_QUEUE_MASK &
				queue_scan];
		पूर्ण
		अगर (urb_slot) अणु
			काष्ठा usb_hcd *hcd = u132_to_hcd(u132);

			usb_hcd_unlink_urb_from_ep(hcd, urb);
			endp->queue_size -= 1;
			अगर (list_empty(&endp->urb_more)) अणु
				spin_unlock_irqrestore(&endp->queue_lock.slock,
					irqs);
			पूर्ण अन्यथा अणु
				काष्ठा list_head *next = endp->urb_more.next;
				काष्ठा u132_urbq *urbq = list_entry(next,
					काष्ठा u132_urbq, urb_more);
				list_del(next);
				*urb_slot = urbq->urb;
				spin_unlock_irqrestore(&endp->queue_lock.slock,
					irqs);
				kमुक्त(urbq);
			पूर्ण
			urb->error_count = 0;
			usb_hcd_giveback_urb(hcd, urb, status);
			वापस 0;
		पूर्ण अन्यथा अगर (list_empty(&endp->urb_more)) अणु
			dev_err(&u132->platक्रमm_dev->dev, "urb=%p not found in "
				"endp[%d]=%p ring[%d] %c%c usb_endp=%d usb_addr"
				"=%d size=%d next=%04X last=%04X\n", urb,
				endp->endp_number, endp, endp->ring->number,
				endp->input ? 'I' : ' ',
				endp->output ? 'O' : ' ', endp->usb_endp,
				endp->usb_addr, endp->queue_size,
				endp->queue_next, endp->queue_last);
			spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			पूर्णांक retval;

			usb_hcd_unlink_urb_from_ep(u132_to_hcd(u132), urb);
			retval = dequeue_from_overflow_chain(u132, endp,
				urb);
			spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
			वापस retval;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक u132_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 2) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		u8 usb_addr = usb_pipedevice(urb->pipe);
		u8 usb_endp = usb_pipeendpoपूर्णांक(urb->pipe);
		u8 address = u132->addr[usb_addr].address;
		काष्ठा u132_udev *udev = &u132->udev[address];
		अगर (usb_pipein(urb->pipe)) अणु
			u8 endp_number = udev->endp_number_in[usb_endp];
			काष्ठा u132_endp *endp = u132->endp[endp_number - 1];
			वापस u132_endp_urb_dequeue(u132, endp, urb, status);
		पूर्ण अन्यथा अणु
			u8 endp_number = udev->endp_number_out[usb_endp];
			काष्ठा u132_endp *endp = u132->endp[endp_number - 1];
			वापस u132_endp_urb_dequeue(u132, endp, urb, status);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम u132_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
	काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 2) अणु
		dev_err(&u132->platक्रमm_dev->dev, "u132 device %p(hcd=%p hep=%p"
			") has been removed %d\n", u132, hcd, hep,
			u132->going);
	पूर्ण अन्यथा अणु
		काष्ठा u132_endp *endp = hep->hcpriv;
		अगर (endp)
			u132_endp_put_kref(u132, endp);
	पूर्ण
पूर्ण

अटल पूर्णांक u132_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		dev_err(&u132->platक्रमm_dev->dev, "TODO: u132_get_frame\n");
		mdelay(100);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_roothub_descriptor(काष्ठा u132 *u132,
	काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक retval;
	u16 temp;
	u32 rh_a = -1;
	u32 rh_b = -1;
	retval = u132_पढ़ो_pcimem(u132, roothub.a, &rh_a);
	अगर (retval)
		वापस retval;
	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = (rh_a & RH_A_POTPGT) >> 24;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = u132->num_ports;
	temp = 1 + (u132->num_ports / 8);
	desc->bDescLength = 7 + 2 * temp;
	temp = HUB_CHAR_COMMON_LPSM | HUB_CHAR_COMMON_OCPM;
	अगर (rh_a & RH_A_NPS)
		temp |= HUB_CHAR_NO_LPSM;
	अगर (rh_a & RH_A_PSM)
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	अगर (rh_a & RH_A_NOCP)
		temp |= HUB_CHAR_NO_OCPM;
	अन्यथा अगर (rh_a & RH_A_OCPM)
		temp |= HUB_CHAR_INDV_PORT_OCPM;
	desc->wHubCharacteristics = cpu_to_le16(temp);
	retval = u132_पढ़ो_pcimem(u132, roothub.b, &rh_b);
	अगर (retval)
		वापस retval;
	स_रखो(desc->u.hs.DeviceRemovable, 0xff,
			माप(desc->u.hs.DeviceRemovable));
	desc->u.hs.DeviceRemovable[0] = rh_b & RH_B_DR;
	अगर (u132->num_ports > 7) अणु
		desc->u.hs.DeviceRemovable[1] = (rh_b & RH_B_DR) >> 8;
		desc->u.hs.DeviceRemovable[2] = 0xff;
	पूर्ण अन्यथा
		desc->u.hs.DeviceRemovable[1] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक u132_roothub_status(काष्ठा u132 *u132, __le32 *desc)
अणु
	u32 rh_status = -1;
	पूर्णांक ret_status = u132_पढ़ो_pcimem(u132, roothub.status, &rh_status);
	*desc = cpu_to_le32(rh_status);
	वापस ret_status;
पूर्ण

अटल पूर्णांक u132_roothub_portstatus(काष्ठा u132 *u132, __le32 *desc, u16 wIndex)
अणु
	अगर (wIndex == 0 || wIndex > u132->num_ports) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		पूर्णांक port = wIndex - 1;
		u32 rh_portstatus = -1;
		पूर्णांक ret_portstatus = u132_पढ़ो_pcimem(u132,
			roothub.portstatus[port], &rh_portstatus);
		*desc = cpu_to_le32(rh_portstatus);
		अगर (*(u16 *) (desc + 2)) अणु
			dev_info(&u132->platक्रमm_dev->dev, "Port %d Status Chan"
				"ge = %08X\n", port, *desc);
		पूर्ण
		वापस ret_portstatus;
	पूर्ण
पूर्ण


/* this समयr value might be venकरोr-specअगरic ... */
#घोषणा PORT_RESET_HW_MSEC 10
#घोषणा PORT_RESET_MSEC 10
/* wrap-aware logic morphed from <linux/jअगरfies.h> */
#घोषणा tick_beक्रमe(t1, t2) ((s16)(((s16)(t1))-((s16)(t2))) < 0)
अटल पूर्णांक u132_roothub_portreset(काष्ठा u132 *u132, पूर्णांक port_index)
अणु
	पूर्णांक retval;
	u32 fmnumber;
	u16 now;
	u16 reset_करोne;
	retval = u132_पढ़ो_pcimem(u132, fmnumber, &fmnumber);
	अगर (retval)
		वापस retval;
	now = fmnumber;
	reset_करोne = now + PORT_RESET_MSEC;
	करो अणु
		u32 portstat;
		करो अणु
			retval = u132_पढ़ो_pcimem(u132,
				roothub.portstatus[port_index], &portstat);
			अगर (retval)
				वापस retval;
			अगर (RH_PS_PRS & portstat)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण जबतक (tick_beक्रमe(now, reset_करोne));
		अगर (RH_PS_PRS & portstat)
			वापस -ENODEV;
		अगर (RH_PS_CCS & portstat) अणु
			अगर (RH_PS_PRSC & portstat) अणु
				retval = u132_ग_लिखो_pcimem(u132,
					roothub.portstatus[port_index],
					RH_PS_PRSC);
				अगर (retval)
					वापस retval;
			पूर्ण
		पूर्ण अन्यथा
			अवरोध;	/* start the next reset,
				sleep till it's probably करोne */
		retval = u132_ग_लिखो_pcimem(u132, roothub.portstatus[port_index],
			 RH_PS_PRS);
		अगर (retval)
			वापस retval;
		msleep(PORT_RESET_HW_MSEC);
		retval = u132_पढ़ो_pcimem(u132, fmnumber, &fmnumber);
		अगर (retval)
			वापस retval;
		now = fmnumber;
	पूर्ण जबतक (tick_beक्रमe(now, reset_करोne));
	वापस 0;
पूर्ण

अटल पूर्णांक u132_roothub_setportfeature(काष्ठा u132 *u132, u16 wValue,
	u16 wIndex)
अणु
	अगर (wIndex == 0 || wIndex > u132->num_ports) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		पूर्णांक port_index = wIndex - 1;
		काष्ठा u132_port *port = &u132->port[port_index];
		port->Status &= ~(1 << wValue);
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			वापस u132_ग_लिखो_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PSS);
		हाल USB_PORT_FEAT_POWER:
			वापस u132_ग_लिखो_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PPS);
		हाल USB_PORT_FEAT_RESET:
			वापस u132_roothub_portreset(u132, port_index);
		शेष:
			वापस -EPIPE;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक u132_roothub_clearportfeature(काष्ठा u132 *u132, u16 wValue,
	u16 wIndex)
अणु
	अगर (wIndex == 0 || wIndex > u132->num_ports) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		पूर्णांक port_index = wIndex - 1;
		u32 temp;
		काष्ठा u132_port *port = &u132->port[port_index];
		port->Status &= ~(1 << wValue);
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			temp = RH_PS_CCS;
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			temp = RH_PS_PESC;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			temp = RH_PS_POCI;
			अगर ((u132->hc_control & OHCI_CTRL_HCFS)
				!= OHCI_USB_OPER) अणु
				dev_err(&u132->platक्रमm_dev->dev, "TODO resume_"
					"root_hub\n");
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			temp = RH_PS_PSSC;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			temp = RH_PS_LSDA;
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			temp = RH_PS_CSC;
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			temp = RH_PS_OCIC;
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			temp = RH_PS_PRSC;
			अवरोध;
		शेष:
			वापस -EPIPE;
		पूर्ण
		वापस u132_ग_लिखो_pcimem(u132, roothub.portstatus[port_index],
		       temp);
	पूर्ण
पूर्ण


/* the भव root hub समयr IRQ checks क्रम hub status*/
अटल पूर्णांक u132_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device hcd=%p has been remov"
			"ed %d\n", hcd, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device hcd=%p is being remov"
			"ed\n", hcd);
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		पूर्णांक i, changed = 0, length = 1;
		अगर (u132->flags & OHCI_QUIRK_AMD756) अणु
			अगर ((u132->hc_roothub_a & RH_A_NDP) > MAX_ROOT_PORTS) अणु
				dev_err(&u132->platक्रमm_dev->dev, "bogus NDP, r"
					"ereads as NDP=%d\n",
					u132->hc_roothub_a & RH_A_NDP);
				जाओ करोne;
			पूर्ण
		पूर्ण
		अगर (u132->hc_roothub_status & (RH_HS_LPSC | RH_HS_OCIC))
			buf[0] = changed = 1;
		अन्यथा
			buf[0] = 0;
		अगर (u132->num_ports > 7) अणु
			buf[1] = 0;
			length++;
		पूर्ण
		क्रम (i = 0; i < u132->num_ports; i++) अणु
			अगर (u132->hc_roothub_portstatus[i] & (RH_PS_CSC |
				RH_PS_PESC | RH_PS_PSSC | RH_PS_OCIC |
				RH_PS_PRSC)) अणु
				changed = 1;
				अगर (i < 7)
					buf[0] |= 1 << (i + 1);
				अन्यथा
					buf[1] |= 1 << (i - 7);
				जारी;
			पूर्ण
			अगर (!(u132->hc_roothub_portstatus[i] & RH_PS_CCS))
				जारी;

			अगर ((u132->hc_roothub_portstatus[i] & RH_PS_PSS))
				जारी;
		पूर्ण
करोne:
		वापस changed ? length : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
	u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = 0;
		mutex_lock(&u132->sw_lock);
		चयन (typeReq) अणु
		हाल ClearHubFeature:
			चयन (wValue) अणु
			हाल C_HUB_OVER_CURRENT:
			हाल C_HUB_LOCAL_POWER:
				अवरोध;
			शेष:
				जाओ stall;
			पूर्ण
			अवरोध;
		हाल SetHubFeature:
			चयन (wValue) अणु
			हाल C_HUB_OVER_CURRENT:
			हाल C_HUB_LOCAL_POWER:
				अवरोध;
			शेष:
				जाओ stall;
			पूर्ण
			अवरोध;
		हाल ClearPortFeature:अणु
				retval = u132_roothub_clearportfeature(u132,
					wValue, wIndex);
				अगर (retval)
					जाओ error;
				अवरोध;
			पूर्ण
		हाल GetHubDescriptor:अणु
				retval = u132_roothub_descriptor(u132,
					(काष्ठा usb_hub_descriptor *)buf);
				अगर (retval)
					जाओ error;
				अवरोध;
			पूर्ण
		हाल GetHubStatus:अणु
				retval = u132_roothub_status(u132,
					(__le32 *) buf);
				अगर (retval)
					जाओ error;
				अवरोध;
			पूर्ण
		हाल GetPortStatus:अणु
				retval = u132_roothub_portstatus(u132,
					(__le32 *) buf, wIndex);
				अगर (retval)
					जाओ error;
				अवरोध;
			पूर्ण
		हाल SetPortFeature:अणु
				retval = u132_roothub_setportfeature(u132,
					wValue, wIndex);
				अगर (retval)
					जाओ error;
				अवरोध;
			पूर्ण
		शेष:
			जाओ stall;
		error:
			u132_disable(u132);
			u132->going = 1;
			अवरोध;
		stall:
			retval = -EPIPE;
			अवरोध;
		पूर्ण
		mutex_unlock(&u132->sw_lock);
		वापस retval;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_start_port_reset(काष्ठा usb_hcd *hcd, अचिन्हित port_num)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक u132_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक u132_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

#अन्यथा
#घोषणा u132_bus_suspend शून्य
#घोषणा u132_bus_resume शून्य
#पूर्ण_अगर
अटल स्थिर काष्ठा hc_driver u132_hc_driver = अणु
	.description = hcd_name,
	.hcd_priv_size = माप(काष्ठा u132),
	.irq = शून्य,
	.flags = HCD_USB11 | HCD_MEMORY,
	.reset = u132_hcd_reset,
	.start = u132_hcd_start,
	.stop = u132_hcd_stop,
	.urb_enqueue = u132_urb_enqueue,
	.urb_dequeue = u132_urb_dequeue,
	.endpoपूर्णांक_disable = u132_endpoपूर्णांक_disable,
	.get_frame_number = u132_get_frame,
	.hub_status_data = u132_hub_status_data,
	.hub_control = u132_hub_control,
	.bus_suspend = u132_bus_suspend,
	.bus_resume = u132_bus_resume,
	.start_port_reset = u132_start_port_reset,
पूर्ण;

/*
* This function may be called by the USB core whilst the "usb_all_devices_rwsem"
* is held क्रम writing, thus this module must not call usb_हटाओ_hcd()
* synchronously - but instead should immediately stop activity to the
* device and asynchronously call usb_हटाओ_hcd()
*/
अटल पूर्णांक u132_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	अगर (hcd) अणु
		काष्ठा u132 *u132 = hcd_to_u132(hcd);
		अगर (u132->going++ > 1) अणु
			dev_err(&u132->platक्रमm_dev->dev, "already being remove"
				"d\n");
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			पूर्णांक rings = MAX_U132_RINGS;
			पूर्णांक endps = MAX_U132_ENDPS;
			dev_err(&u132->platक्रमm_dev->dev, "removing device u132"
				".%d\n", u132->sequence_num);
			msleep(100);
			mutex_lock(&u132->sw_lock);
			u132_monitor_cancel_work(u132);
			जबतक (rings-- > 0) अणु
				काष्ठा u132_ring *ring = &u132->ring[rings];
				u132_ring_cancel_work(u132, ring);
			पूर्ण
			जबतक (endps-- > 0) अणु
				काष्ठा u132_endp *endp = u132->endp[endps];
				अगर (endp)
					u132_endp_cancel_work(u132, endp);
			पूर्ण
			u132->going += 1;
			prपूर्णांकk(KERN_INFO "removing device u132.%d\n",
				u132->sequence_num);
			mutex_unlock(&u132->sw_lock);
			usb_हटाओ_hcd(hcd);
			u132_u132_put_kref(u132);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल व्योम u132_initialise(काष्ठा u132 *u132, काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rings = MAX_U132_RINGS;
	पूर्णांक ports = MAX_U132_PORTS;
	पूर्णांक addrs = MAX_U132_ADDRS;
	पूर्णांक udevs = MAX_U132_UDEVS;
	पूर्णांक endps = MAX_U132_ENDPS;
	u132->board = dev_get_platdata(&pdev->dev);
	u132->platक्रमm_dev = pdev;
	u132->घातer = 0;
	u132->reset = 0;
	mutex_init(&u132->sw_lock);
	mutex_init(&u132->scheduler_lock);
	जबतक (rings-- > 0) अणु
		काष्ठा u132_ring *ring = &u132->ring[rings];
		ring->u132 = u132;
		ring->number = rings + 1;
		ring->length = 0;
		ring->curr_endp = शून्य;
		INIT_DELAYED_WORK(&ring->scheduler,
				  u132_hcd_ring_work_scheduler);
	पूर्ण
	mutex_lock(&u132->sw_lock);
	INIT_DELAYED_WORK(&u132->monitor, u132_hcd_monitor_work);
	जबतक (ports-- > 0) अणु
		काष्ठा u132_port *port = &u132->port[ports];
		port->u132 = u132;
		port->reset = 0;
		port->enable = 0;
		port->घातer = 0;
		port->Status = 0;
	पूर्ण
	जबतक (addrs-- > 0) अणु
		काष्ठा u132_addr *addr = &u132->addr[addrs];
		addr->address = 0;
	पूर्ण
	जबतक (udevs-- > 0) अणु
		काष्ठा u132_udev *udev = &u132->udev[udevs];
		पूर्णांक i = ARRAY_SIZE(udev->endp_number_in);
		पूर्णांक o = ARRAY_SIZE(udev->endp_number_out);
		udev->usb_device = शून्य;
		udev->udev_number = 0;
		udev->usb_addr = 0;
		udev->portnumber = 0;
		जबतक (i-- > 0)
			udev->endp_number_in[i] = 0;

		जबतक (o-- > 0)
			udev->endp_number_out[o] = 0;

	पूर्ण
	जबतक (endps-- > 0)
		u132->endp[endps] = शून्य;

	mutex_unlock(&u132->sw_lock);
पूर्ण

अटल पूर्णांक u132_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;
	पूर्णांक retval;
	u32 control;
	u32 rh_a = -1;

	msleep(100);
	अगर (u132_निकासing > 0)
		वापस -ENODEV;

	retval = ftdi_ग_लिखो_pcimem(pdev, पूर्णांकrdisable, OHCI_INTR_MIE);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(pdev, control, &control);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(pdev, roothub.a, &rh_a);
	अगर (retval)
		वापस retval;

	hcd = usb_create_hcd(&u132_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		prपूर्णांकk(KERN_ERR "failed to create the usb hcd struct for U132\n"
			);
		ftdi_elan_gone_away(pdev);
		वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		काष्ठा u132 *u132 = hcd_to_u132(hcd);
		retval = 0;
		hcd->rsrc_start = 0;
		mutex_lock(&u132_module_lock);
		u132->sequence_num = ++u132_instances;
		mutex_unlock(&u132_module_lock);
		u132_u132_init_kref(u132);
		u132_initialise(u132, pdev);
		hcd->product_desc = "ELAN U132 Host Controller";
		retval = usb_add_hcd(hcd, 0, 0);
		अगर (retval != 0) अणु
			dev_err(&u132->platक्रमm_dev->dev, "init error %d\n",
				retval);
			u132_u132_put_kref(u132);
			वापस retval;
		पूर्ण अन्यथा अणु
			device_wakeup_enable(hcd->self.controller);
			u132_monitor_queue_work(u132, 100);
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_PM
/*
 * क्रम this device there's no useful distinction between the controller
 * and its root hub.
 */
अटल पूर्णांक u132_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = 0, ports;

		चयन (state.event) अणु
		हाल PM_EVENT_FREEZE:
			retval = u132_bus_suspend(hcd);
			अवरोध;
		हाल PM_EVENT_SUSPEND:
		हाल PM_EVENT_HIBERNATE:
			ports = MAX_U132_PORTS;
			जबतक (ports-- > 0) अणु
				port_घातer(u132, ports, 0);
			पूर्ण
			अवरोध;
		पूर्ण
		वापस retval;
	पूर्ण
पूर्ण

अटल पूर्णांक u132_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा u132 *u132 = hcd_to_u132(hcd);
	अगर (u132->going > 1) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device has been removed %d\n"
			, u132->going);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (u132->going > 0) अणु
		dev_err(&u132->platक्रमm_dev->dev, "device is being removed\n");
		वापस -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = 0;
		अगर (!u132->port[0].घातer) अणु
			पूर्णांक ports = MAX_U132_PORTS;
			जबतक (ports-- > 0) अणु
				port_घातer(u132, ports, 1);
			पूर्ण
			retval = 0;
		पूर्ण अन्यथा अणु
			retval = u132_bus_resume(hcd);
		पूर्ण
		वापस retval;
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा u132_suspend शून्य
#घोषणा u132_resume शून्य
#पूर्ण_अगर
/*
* this driver is loaded explicitly by ftdi_u132
*
* the platक्रमm_driver काष्ठा is अटल because it is per type of module
*/
अटल काष्ठा platक्रमm_driver u132_platक्रमm_driver = अणु
	.probe = u132_probe,
	.हटाओ = u132_हटाओ,
	.suspend = u132_suspend,
	.resume = u132_resume,
	.driver = अणु
		   .name = hcd_name,
		   पूर्ण,
पूर्ण;
अटल पूर्णांक __init u132_hcd_init(व्योम)
अणु
	पूर्णांक retval;
	u132_instances = 0;
	u132_निकासing = 0;
	अगर (usb_disabled())
		वापस -ENODEV;
	prपूर्णांकk(KERN_INFO "driver %s\n", hcd_name);
	workqueue = create_singlethपढ़ो_workqueue("u132");
	अगर (!workqueue)
		वापस -ENOMEM;
	retval = platक्रमm_driver_रेजिस्टर(&u132_platक्रमm_driver);
	अगर (retval)
		destroy_workqueue(workqueue);

	वापस retval;
पूर्ण


module_init(u132_hcd_init);
अटल व्योम __निकास u132_hcd_निकास(व्योम)
अणु
	mutex_lock(&u132_module_lock);
	u132_निकासing += 1;
	mutex_unlock(&u132_module_lock);
	platक्रमm_driver_unरेजिस्टर(&u132_platक्रमm_driver);
	prपूर्णांकk(KERN_INFO "u132-hcd driver deregistered\n");
	रुको_event(u132_hcd_रुको, u132_instances == 0);
	flush_workqueue(workqueue);
	destroy_workqueue(workqueue);
पूर्ण


module_निकास(u132_hcd_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:u132_hcd");
