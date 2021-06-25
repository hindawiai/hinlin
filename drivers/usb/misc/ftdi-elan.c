<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB FTDI client driver क्रम Elan Digital Systems's Uxxx adapters
 *
 * Copyright(C) 2006 Elan Digital Systems Limited
 * http://www.elandigitalप्रणालीs.com
 *
 * Author and Maपूर्णांकainer - Tony Olech - Elan Digital Systems
 * tony.olech@elandigitalप्रणालीs.com
 *
 * This driver was written by Tony Olech(tony.olech@elandigitalप्रणालीs.com)
 * based on various USB client drivers in the 2.6.15 linux kernel
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
MODULE_AUTHOR("Tony Olech");
MODULE_DESCRIPTION("FTDI ELAN driver");
MODULE_LICENSE("GPL");
#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v;module_param(n, पूर्णांक, 0444)
अटल bool distrust_firmware = 1;
module_param(distrust_firmware, bool, 0);
MODULE_PARM_DESC(distrust_firmware,
		 "true to distrust firmware power/overcurrent setup");
बाह्य काष्ठा platक्रमm_driver u132_platक्रमm_driver;
/*
 * ftdi_module_lock exists to protect access to global variables
 *
 */
अटल काष्ठा mutex ftdi_module_lock;
अटल पूर्णांक ftdi_instances = 0;
अटल काष्ठा list_head ftdi_अटल_list;
/*
 * end of the global variables रक्षित by ftdi_module_lock
 */
#समावेश "usb_u132.h"
#समावेश <यंत्र/पन.स>
#समावेश <linux/usb/hcd.h>

/* FIXME ohci.h is ONLY क्रम पूर्णांकernal use by the OHCI driver.
 * If you're going to try stuff like this, you need to split
 * out shareable stuff (रेजिस्टर declarations?) पूर्णांकo its own
 * file, maybe name <linux/usb/ohci.h>
 */

#समावेश "../host/ohci.h"
/* Define these values to match your devices*/
#घोषणा USB_FTDI_ELAN_VENDOR_ID 0x0403
#घोषणा USB_FTDI_ELAN_PRODUCT_ID 0xd6ea
/* table of devices that work with this driver*/
अटल स्थिर काष्ठा usb_device_id ftdi_elan_table[] = अणु
	अणुUSB_DEVICE(USB_FTDI_ELAN_VENDOR_ID, USB_FTDI_ELAN_PRODUCT_ID)पूर्ण,
	अणु /* Terminating entry */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, ftdi_elan_table);
/* only the jtag(firmware upgrade device) पूर्णांकerface requires
 * a device file and corresponding minor number, but the
 * पूर्णांकerface is created unconditionally - I suppose it could
 * be configured or not according to a module parameter.
 * But since we(now) require one पूर्णांकerface per device,
 * and since it unlikely that a normal installation would
 * require more than a couple of elan-ftdi devices, 8 seems
 * like a reasonable limit to have here, and अगर someone
 * really requires more than 8 devices, then they can frig the
 * code and recompile
 */
#घोषणा USB_FTDI_ELAN_MINOR_BASE 192
#घोषणा COMMAND_BITS 5
#घोषणा COMMAND_SIZE (1<<COMMAND_BITS)
#घोषणा COMMAND_MASK (COMMAND_SIZE-1)
काष्ठा u132_command अणु
	u8 header;
	u16 length;
	u8 address;
	u8 width;
	u32 value;
	पूर्णांक follows;
	व्योम *buffer;
पूर्ण;
#घोषणा RESPOND_BITS 5
#घोषणा RESPOND_SIZE (1<<RESPOND_BITS)
#घोषणा RESPOND_MASK (RESPOND_SIZE-1)
काष्ठा u132_respond अणु
	u8 header;
	u8 address;
	u32 *value;
	पूर्णांक *result;
	काष्ठा completion रुको_completion;
पूर्ण;
काष्ठा u132_target अणु
	व्योम *endp;
	काष्ठा urb *urb;
	पूर्णांक toggle_bits;
	पूर्णांक error_count;
	पूर्णांक condition_code;
	पूर्णांक repeat_number;
	पूर्णांक halted;
	पूर्णांक skipped;
	पूर्णांक actual;
	पूर्णांक non_null;
	पूर्णांक active;
	पूर्णांक abanकरोning;
	व्योम (*callback)(व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
			 पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code,
			 पूर्णांक repeat_number, पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual,
			 पूर्णांक non_null);
पूर्ण;
/* Structure to hold all of our device specअगरic stuff*/
काष्ठा usb_ftdi अणु
	काष्ठा list_head ftdi_list;
	काष्ठा mutex u132_lock;
	पूर्णांक command_next;
	पूर्णांक command_head;
	काष्ठा u132_command command[COMMAND_SIZE];
	पूर्णांक respond_next;
	पूर्णांक respond_head;
	काष्ठा u132_respond respond[RESPOND_SIZE];
	काष्ठा u132_target target[4];
	अक्षर device_name[16];
	अचिन्हित synchronized:1;
	अचिन्हित क्रमागतerated:1;
	अचिन्हित रेजिस्टरed:1;
	अचिन्हित initialized:1;
	अचिन्हित card_ejected:1;
	पूर्णांक function;
	पूर्णांक sequence_num;
	पूर्णांक disconnected;
	पूर्णांक gone_away;
	पूर्णांक stuck_status;
	पूर्णांक status_queue_delay;
	काष्ठा semaphore sw_lock;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_class_driver *class;
	काष्ठा delayed_work status_work;
	काष्ठा delayed_work command_work;
	काष्ठा delayed_work respond_work;
	काष्ठा u132_platक्रमm_data platक्रमm_data;
	काष्ठा resource resources[0];
	काष्ठा platक्रमm_device platक्रमm_dev;
	अचिन्हित अक्षर *bulk_in_buffer;
	माप_प्रकार bulk_in_size;
	माप_प्रकार bulk_in_last;
	माप_प्रकार bulk_in_left;
	__u8 bulk_in_endpoपूर्णांकAddr;
	__u8 bulk_out_endpoपूर्णांकAddr;
	काष्ठा kref kref;
	u32 controlreg;
	u8 response[4 + 1024];
	पूर्णांक expected;
	पूर्णांक received;
	पूर्णांक ed_found;
पूर्ण;
#घोषणा kref_to_usb_ftdi(d) container_of(d, काष्ठा usb_ftdi, kref)
#घोषणा platक्रमm_device_to_usb_ftdi(d) container_of(d, काष्ठा usb_ftdi, \
						    platक्रमm_dev)
अटल काष्ठा usb_driver ftdi_elan_driver;
अटल व्योम ftdi_elan_delete(काष्ठा kref *kref)
अणु
	काष्ठा usb_ftdi *ftdi = kref_to_usb_ftdi(kref);
	dev_warn(&ftdi->udev->dev, "FREEING ftdi=%p\n", ftdi);
	usb_put_dev(ftdi->udev);
	ftdi->disconnected += 1;
	mutex_lock(&ftdi_module_lock);
	list_del_init(&ftdi->ftdi_list);
	ftdi_instances -= 1;
	mutex_unlock(&ftdi_module_lock);
	kमुक्त(ftdi->bulk_in_buffer);
	ftdi->bulk_in_buffer = शून्य;
पूर्ण

अटल व्योम ftdi_elan_put_kref(काष्ठा usb_ftdi *ftdi)
अणु
	kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_elan_get_kref(काष्ठा usb_ftdi *ftdi)
अणु
	kref_get(&ftdi->kref);
पूर्ण

अटल व्योम ftdi_elan_init_kref(काष्ठा usb_ftdi *ftdi)
अणु
	kref_init(&ftdi->kref);
पूर्ण

अटल व्योम ftdi_status_requeue_work(काष्ठा usb_ftdi *ftdi, अचिन्हित पूर्णांक delta)
अणु
	अगर (!schedule_delayed_work(&ftdi->status_work, delta))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_status_queue_work(काष्ठा usb_ftdi *ftdi, अचिन्हित पूर्णांक delta)
अणु
	अगर (schedule_delayed_work(&ftdi->status_work, delta))
		kref_get(&ftdi->kref);
पूर्ण

अटल व्योम ftdi_status_cancel_work(काष्ठा usb_ftdi *ftdi)
अणु
	अगर (cancel_delayed_work_sync(&ftdi->status_work))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_command_requeue_work(काष्ठा usb_ftdi *ftdi, अचिन्हित पूर्णांक delta)
अणु
	अगर (!schedule_delayed_work(&ftdi->command_work, delta))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_command_queue_work(काष्ठा usb_ftdi *ftdi, अचिन्हित पूर्णांक delta)
अणु
	अगर (schedule_delayed_work(&ftdi->command_work, delta))
		kref_get(&ftdi->kref);
पूर्ण

अटल व्योम ftdi_command_cancel_work(काष्ठा usb_ftdi *ftdi)
अणु
	अगर (cancel_delayed_work_sync(&ftdi->command_work))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_response_requeue_work(काष्ठा usb_ftdi *ftdi,
				       अचिन्हित पूर्णांक delta)
अणु
	अगर (!schedule_delayed_work(&ftdi->respond_work, delta))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

अटल व्योम ftdi_respond_queue_work(काष्ठा usb_ftdi *ftdi, अचिन्हित पूर्णांक delta)
अणु
	अगर (schedule_delayed_work(&ftdi->respond_work, delta))
		kref_get(&ftdi->kref);
पूर्ण

अटल व्योम ftdi_response_cancel_work(काष्ठा usb_ftdi *ftdi)
अणु
	अगर (cancel_delayed_work_sync(&ftdi->respond_work))
		kref_put(&ftdi->kref, ftdi_elan_delete);
पूर्ण

व्योम ftdi_elan_gone_away(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	ftdi->gone_away += 1;
	ftdi_elan_put_kref(ftdi);
पूर्ण


EXPORT_SYMBOL_GPL(ftdi_elan_gone_away);
अटल व्योम ftdi_release_platक्रमm_dev(काष्ठा device *dev)
अणु
	dev->parent = शून्य;
पूर्ण

अटल व्योम ftdi_elan_करो_callback(काष्ठा usb_ftdi *ftdi,
				  काष्ठा u132_target *target, u8 *buffer, पूर्णांक length);
अटल व्योम ftdi_elan_kick_command_queue(काष्ठा usb_ftdi *ftdi);
अटल व्योम ftdi_elan_kick_respond_queue(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_setupOHCI(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_checkingPCI(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_क्रमागतeratePCI(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_synchronize(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_stuck_रुकोing(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_command_engine(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_respond_engine(काष्ठा usb_ftdi *ftdi);
अटल पूर्णांक ftdi_elan_hcd_init(काष्ठा usb_ftdi *ftdi)
अणु
	अगर (ftdi->platक्रमm_dev.dev.parent)
		वापस -EBUSY;

	ftdi_elan_get_kref(ftdi);
	ftdi->platक्रमm_data.potpg = 100;
	ftdi->platक्रमm_data.reset = शून्य;
	ftdi->platक्रमm_dev.id = ftdi->sequence_num;
	ftdi->platक्रमm_dev.resource = ftdi->resources;
	ftdi->platक्रमm_dev.num_resources = ARRAY_SIZE(ftdi->resources);
	ftdi->platक्रमm_dev.dev.platक्रमm_data = &ftdi->platक्रमm_data;
	ftdi->platक्रमm_dev.dev.parent = शून्य;
	ftdi->platक्रमm_dev.dev.release = ftdi_release_platक्रमm_dev;
	ftdi->platक्रमm_dev.dev.dma_mask = शून्य;
	snम_लिखो(ftdi->device_name, माप(ftdi->device_name), "u132_hcd");
	ftdi->platक्रमm_dev.name = ftdi->device_name;
	dev_info(&ftdi->udev->dev, "requesting module '%s'\n", "u132_hcd");
	request_module("u132_hcd");
	dev_info(&ftdi->udev->dev, "registering '%s'\n",
		 ftdi->platक्रमm_dev.name);

	वापस platक्रमm_device_रेजिस्टर(&ftdi->platक्रमm_dev);
पूर्ण

अटल व्योम ftdi_elan_abanकरोn_completions(काष्ठा usb_ftdi *ftdi)
अणु
	mutex_lock(&ftdi->u132_lock);
	जबतक (ftdi->respond_next > ftdi->respond_head) अणु
		काष्ठा u132_respond *respond = &ftdi->respond[RESPOND_MASK &
							      ftdi->respond_head++];
		*respond->result = -ESHUTDOWN;
		*respond->value = 0;
		complete(&respond->रुको_completion);
	पूर्ण
	mutex_unlock(&ftdi->u132_lock);
पूर्ण

अटल व्योम ftdi_elan_abanकरोn_tarमाला_लो(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक ed_number = 4;
	mutex_lock(&ftdi->u132_lock);
	जबतक (ed_number-- > 0) अणु
		काष्ठा u132_target *target = &ftdi->target[ed_number];
		अगर (target->active == 1) अणु
			target->condition_code = TD_DEVNOTRESP;
			mutex_unlock(&ftdi->u132_lock);
			ftdi_elan_करो_callback(ftdi, target, शून्य, 0);
			mutex_lock(&ftdi->u132_lock);
		पूर्ण
	पूर्ण
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	mutex_unlock(&ftdi->u132_lock);
पूर्ण

अटल व्योम ftdi_elan_flush_tarमाला_लो(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक ed_number = 4;
	mutex_lock(&ftdi->u132_lock);
	जबतक (ed_number-- > 0) अणु
		काष्ठा u132_target *target = &ftdi->target[ed_number];
		target->abanकरोning = 1;
	रुको_1:अगर (target->active == 1) अणु
			पूर्णांक command_size = ftdi->command_next -
				ftdi->command_head;
			अगर (command_size < COMMAND_SIZE) अणु
				काष्ठा u132_command *command = &ftdi->command[
					COMMAND_MASK & ftdi->command_next];
				command->header = 0x80 | (ed_number << 5) | 0x4;
				command->length = 0x00;
				command->address = 0x00;
				command->width = 0x00;
				command->follows = 0;
				command->value = 0;
				command->buffer = &command->value;
				ftdi->command_next += 1;
				ftdi_elan_kick_command_queue(ftdi);
			पूर्ण अन्यथा अणु
				mutex_unlock(&ftdi->u132_lock);
				msleep(100);
				mutex_lock(&ftdi->u132_lock);
				जाओ रुको_1;
			पूर्ण
		पूर्ण
	रुको_2:अगर (target->active == 1) अणु
			पूर्णांक command_size = ftdi->command_next -
				ftdi->command_head;
			अगर (command_size < COMMAND_SIZE) अणु
				काष्ठा u132_command *command = &ftdi->command[
					COMMAND_MASK & ftdi->command_next];
				command->header = 0x90 | (ed_number << 5);
				command->length = 0x00;
				command->address = 0x00;
				command->width = 0x00;
				command->follows = 0;
				command->value = 0;
				command->buffer = &command->value;
				ftdi->command_next += 1;
				ftdi_elan_kick_command_queue(ftdi);
			पूर्ण अन्यथा अणु
				mutex_unlock(&ftdi->u132_lock);
				msleep(100);
				mutex_lock(&ftdi->u132_lock);
				जाओ रुको_2;
			पूर्ण
		पूर्ण
	पूर्ण
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	mutex_unlock(&ftdi->u132_lock);
पूर्ण

अटल व्योम ftdi_elan_cancel_tarमाला_लो(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक ed_number = 4;
	mutex_lock(&ftdi->u132_lock);
	जबतक (ed_number-- > 0) अणु
		काष्ठा u132_target *target = &ftdi->target[ed_number];
		target->abanकरोning = 1;
	रुको:अगर (target->active == 1) अणु
			पूर्णांक command_size = ftdi->command_next -
				ftdi->command_head;
			अगर (command_size < COMMAND_SIZE) अणु
				काष्ठा u132_command *command = &ftdi->command[
					COMMAND_MASK & ftdi->command_next];
				command->header = 0x80 | (ed_number << 5) | 0x4;
				command->length = 0x00;
				command->address = 0x00;
				command->width = 0x00;
				command->follows = 0;
				command->value = 0;
				command->buffer = &command->value;
				ftdi->command_next += 1;
				ftdi_elan_kick_command_queue(ftdi);
			पूर्ण अन्यथा अणु
				mutex_unlock(&ftdi->u132_lock);
				msleep(100);
				mutex_lock(&ftdi->u132_lock);
				जाओ रुको;
			पूर्ण
		पूर्ण
	पूर्ण
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	mutex_unlock(&ftdi->u132_lock);
पूर्ण

अटल व्योम ftdi_elan_kick_command_queue(काष्ठा usb_ftdi *ftdi)
अणु
	ftdi_command_queue_work(ftdi, 0);
पूर्ण

अटल व्योम ftdi_elan_command_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_ftdi *ftdi =
		container_of(work, काष्ठा usb_ftdi, command_work.work);

	अगर (ftdi->disconnected > 0) अणु
		ftdi_elan_put_kref(ftdi);
		वापस;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = ftdi_elan_command_engine(ftdi);
		अगर (retval == -ESHUTDOWN) अणु
			ftdi->disconnected += 1;
		पूर्ण अन्यथा अगर (retval == -ENODEV) अणु
			ftdi->disconnected += 1;
		पूर्ण अन्यथा अगर (retval)
			dev_err(&ftdi->udev->dev, "command error %d\n", retval);
		ftdi_command_requeue_work(ftdi, msecs_to_jअगरfies(10));
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ftdi_elan_kick_respond_queue(काष्ठा usb_ftdi *ftdi)
अणु
	ftdi_respond_queue_work(ftdi, 0);
पूर्ण

अटल व्योम ftdi_elan_respond_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_ftdi *ftdi =
		container_of(work, काष्ठा usb_ftdi, respond_work.work);
	अगर (ftdi->disconnected > 0) अणु
		ftdi_elan_put_kref(ftdi);
		वापस;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = ftdi_elan_respond_engine(ftdi);
		अगर (retval == 0) अणु
		पूर्ण अन्यथा अगर (retval == -ESHUTDOWN) अणु
			ftdi->disconnected += 1;
		पूर्ण अन्यथा अगर (retval == -ENODEV) अणु
			ftdi->disconnected += 1;
		पूर्ण अन्यथा अगर (retval == -EILSEQ) अणु
			ftdi->disconnected += 1;
		पूर्ण अन्यथा अणु
			ftdi->disconnected += 1;
			dev_err(&ftdi->udev->dev, "respond error %d\n", retval);
		पूर्ण
		अगर (ftdi->disconnected > 0) अणु
			ftdi_elan_abanकरोn_completions(ftdi);
			ftdi_elan_abanकरोn_tarमाला_लो(ftdi);
		पूर्ण
		ftdi_response_requeue_work(ftdi, msecs_to_jअगरfies(10));
		वापस;
	पूर्ण
पूर्ण


/*
 * the sw_lock is initially held and will be मुक्तd
 * after the FTDI has been synchronized
 *
 */
अटल व्योम ftdi_elan_status_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_ftdi *ftdi =
		container_of(work, काष्ठा usb_ftdi, status_work.work);
	पूर्णांक work_delay_in_msec = 0;
	अगर (ftdi->disconnected > 0) अणु
		ftdi_elan_put_kref(ftdi);
		वापस;
	पूर्ण अन्यथा अगर (ftdi->synchronized == 0) अणु
		करोwn(&ftdi->sw_lock);
		अगर (ftdi_elan_synchronize(ftdi) == 0) अणु
			ftdi->synchronized = 1;
			ftdi_command_queue_work(ftdi, 1);
			ftdi_respond_queue_work(ftdi, 1);
			up(&ftdi->sw_lock);
			work_delay_in_msec = 100;
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "synchronize failed\n");
			up(&ftdi->sw_lock);
			work_delay_in_msec = 10 *1000;
		पूर्ण
	पूर्ण अन्यथा अगर (ftdi->stuck_status > 0) अणु
		अगर (ftdi_elan_stuck_रुकोing(ftdi) == 0) अणु
			ftdi->stuck_status = 0;
			ftdi->synchronized = 0;
		पूर्ण अन्यथा अगर ((ftdi->stuck_status++ % 60) == 1) अणु
			dev_err(&ftdi->udev->dev, "WRONG type of card inserted - please remove\n");
		पूर्ण अन्यथा
			dev_err(&ftdi->udev->dev, "WRONG type of card inserted - checked %d times\n",
				ftdi->stuck_status);
		work_delay_in_msec = 100;
	पूर्ण अन्यथा अगर (ftdi->क्रमागतerated == 0) अणु
		अगर (ftdi_elan_क्रमागतeratePCI(ftdi) == 0) अणु
			ftdi->क्रमागतerated = 1;
			work_delay_in_msec = 250;
		पूर्ण अन्यथा
			work_delay_in_msec = 1000;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		अगर (ftdi_elan_setupOHCI(ftdi) == 0) अणु
			ftdi->initialized = 1;
			work_delay_in_msec = 500;
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "initialized failed - trying again in 10 seconds\n");
			work_delay_in_msec = 1 *1000;
		पूर्ण
	पूर्ण अन्यथा अगर (ftdi->रेजिस्टरed == 0) अणु
		work_delay_in_msec = 10;
		अगर (ftdi_elan_hcd_init(ftdi) == 0) अणु
			ftdi->रेजिस्टरed = 1;
		पूर्ण अन्यथा
			dev_err(&ftdi->udev->dev, "register failed\n");
		work_delay_in_msec = 250;
	पूर्ण अन्यथा अणु
		अगर (ftdi_elan_checkingPCI(ftdi) == 0) अणु
			work_delay_in_msec = 250;
		पूर्ण अन्यथा अगर (ftdi->controlreg & 0x00400000) अणु
			अगर (ftdi->gone_away > 0) अणु
				dev_err(&ftdi->udev->dev, "PCI device eject confirmed platform_dev.dev.parent=%p platform_dev.dev=%p\n",
					ftdi->platक्रमm_dev.dev.parent,
					&ftdi->platक्रमm_dev.dev);
				platक्रमm_device_unरेजिस्टर(&ftdi->platक्रमm_dev);
				ftdi->platक्रमm_dev.dev.parent = शून्य;
				ftdi->रेजिस्टरed = 0;
				ftdi->क्रमागतerated = 0;
				ftdi->card_ejected = 0;
				ftdi->initialized = 0;
				ftdi->gone_away = 0;
			पूर्ण अन्यथा
				ftdi_elan_flush_tarमाला_लो(ftdi);
			work_delay_in_msec = 250;
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "PCI device has disappeared\n");
			ftdi_elan_cancel_tarमाला_लो(ftdi);
			work_delay_in_msec = 500;
			ftdi->क्रमागतerated = 0;
			ftdi->initialized = 0;
		पूर्ण
	पूर्ण
	अगर (ftdi->disconnected > 0) अणु
		ftdi_elan_put_kref(ftdi);
		वापस;
	पूर्ण अन्यथा अणु
		ftdi_status_requeue_work(ftdi,
					 msecs_to_jअगरfies(work_delay_in_msec));
		वापस;
	पूर्ण
पूर्ण


/*
 * file_operations क्रम the jtag पूर्णांकerface
 *
 * the usage count क्रम the device is incremented on खोलो()
 * and decremented on release()
 */
अटल पूर्णांक ftdi_elan_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक subminor;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	subminor = iminor(inode);
	पूर्णांकerface = usb_find_पूर्णांकerface(&ftdi_elan_driver, subminor);

	अगर (!पूर्णांकerface) अणु
		pr_err("can't find device for minor %d\n", subminor);
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		काष्ठा usb_ftdi *ftdi = usb_get_पूर्णांकfdata(पूर्णांकerface);
		अगर (!ftdi) अणु
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			अगर (करोwn_पूर्णांकerruptible(&ftdi->sw_lock)) अणु
				वापस -EINTR;
			पूर्ण अन्यथा अणु
				ftdi_elan_get_kref(ftdi);
				file->निजी_data = ftdi;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ftdi_elan_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_ftdi *ftdi = file->निजी_data;
	अगर (ftdi == शून्य)
		वापस -ENODEV;
	up(&ftdi->sw_lock);        /* decrement the count on our device */
	ftdi_elan_put_kref(ftdi);
	वापस 0;
पूर्ण


/*
 *
 * blocking bulk पढ़ोs are used to get data from the device
 *
 */
अटल sमाप_प्रकार ftdi_elan_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर data[30 *3 + 4];
	अक्षर *d = data;
	पूर्णांक m = (माप(data) - 1) / 3 - 1;
	पूर्णांक bytes_पढ़ो = 0;
	पूर्णांक retry_on_empty = 10;
	पूर्णांक retry_on_समयout = 5;
	काष्ठा usb_ftdi *ftdi = file->निजी_data;
	अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण
	data[0] = 0;
have:अगर (ftdi->bulk_in_left > 0) अणु
		अगर (count-- > 0) अणु
			अक्षर *p = ++ftdi->bulk_in_last + ftdi->bulk_in_buffer;
			ftdi->bulk_in_left -= 1;
			अगर (bytes_पढ़ो < m) अणु
				d += प्र_लिखो(d, " %02X", 0x000000FF & *p);
			पूर्ण अन्यथा अगर (bytes_पढ़ो > m) अणु
			पूर्ण अन्यथा
				d += प्र_लिखो(d, " ..");
			अगर (copy_to_user(buffer++, p, 1)) अणु
				वापस -EFAULT;
			पूर्ण अन्यथा अणु
				bytes_पढ़ो += 1;
				जाओ have;
			पूर्ण
		पूर्ण अन्यथा
			वापस bytes_पढ़ो;
	पूर्ण
more:अगर (count > 0) अणु
		पूर्णांक packet_bytes = 0;
		पूर्णांक retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpoपूर्णांकAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 50);
		अगर (packet_bytes > 2) अणु
			ftdi->bulk_in_left = packet_bytes - 2;
			ftdi->bulk_in_last = 1;
			जाओ have;
		पूर्ण अन्यथा अगर (retval == -ETIMEDOUT) अणु
			अगर (retry_on_समयout-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अगर (bytes_पढ़ो > 0) अणु
				वापस bytes_पढ़ो;
			पूर्ण अन्यथा
				वापस retval;
		पूर्ण अन्यथा अगर (retval == 0) अणु
			अगर (retry_on_empty-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा
				वापस bytes_पढ़ो;
		पूर्ण अन्यथा
			वापस retval;
	पूर्ण अन्यथा
		वापस bytes_पढ़ो;
पूर्ण

अटल व्योम ftdi_elan_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_ftdi *ftdi = urb->context;
	पूर्णांक status = urb->status;

	अगर (status && !(status == -ENOENT || status == -ECONNRESET ||
			status == -ESHUTDOWN)) अणु
		dev_err(&ftdi->udev->dev,
			"urb=%p write bulk status received: %d\n", urb, status);
	पूर्ण
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
पूर्ण

अटल पूर्णांक fill_buffer_with_all_queued_commands(काष्ठा usb_ftdi *ftdi,
						अक्षर *buf, पूर्णांक command_size, पूर्णांक total_size)
अणु
	पूर्णांक ed_commands = 0;
	पूर्णांक b = 0;
	पूर्णांक I = command_size;
	पूर्णांक i = ftdi->command_head;
	जबतक (I-- > 0) अणु
		काष्ठा u132_command *command = &ftdi->command[COMMAND_MASK &
							      i++];
		पूर्णांक F = command->follows;
		u8 *f = command->buffer;
		अगर (command->header & 0x80) अणु
			ed_commands |= 1 << (0x3 & (command->header >> 5));
		पूर्ण
		buf[b++] = command->header;
		buf[b++] = (command->length >> 0) & 0x00FF;
		buf[b++] = (command->length >> 8) & 0x00FF;
		buf[b++] = command->address;
		buf[b++] = command->width;
		जबतक (F-- > 0) अणु
			buf[b++] = *f++;
		पूर्ण
	पूर्ण
	वापस ed_commands;
पूर्ण

अटल पूर्णांक ftdi_elan_total_command_size(काष्ठा usb_ftdi *ftdi, पूर्णांक command_size)
अणु
	पूर्णांक total_size = 0;
	पूर्णांक I = command_size;
	पूर्णांक i = ftdi->command_head;
	जबतक (I-- > 0) अणु
		काष्ठा u132_command *command = &ftdi->command[COMMAND_MASK &
							      i++];
		total_size += 5 + command->follows;
	पूर्ण
	वापस total_size;
पूर्ण

अटल पूर्णांक ftdi_elan_command_engine(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retval;
	अक्षर *buf;
	पूर्णांक ed_commands;
	पूर्णांक total_size;
	काष्ठा urb *urb;
	पूर्णांक command_size = ftdi->command_next - ftdi->command_head;
	अगर (command_size == 0)
		वापस 0;
	total_size = ftdi_elan_total_command_size(ftdi, command_size);
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;
	buf = usb_alloc_coherent(ftdi->udev, total_size, GFP_KERNEL,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		dev_err(&ftdi->udev->dev, "could not get a buffer to write %d commands totaling %d bytes to the Uxxx\n",
			command_size, total_size);
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण
	ed_commands = fill_buffer_with_all_queued_commands(ftdi, buf,
							   command_size, total_size);
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpoपूर्णांकAddr), buf, total_size,
			  ftdi_elan_ग_लिखो_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	अगर (ed_commands) अणु
		अक्षर diag[40 *3 + 4];
		अक्षर *d = diag;
		पूर्णांक m = total_size;
		u8 *c = buf;
		पूर्णांक s = (माप(diag) - 1) / 3;
		diag[0] = 0;
		जबतक (s-- > 0 && m-- > 0) अणु
			अगर (s > 0 || m == 0) अणु
				d += प्र_लिखो(d, " %02X", *c++);
			पूर्ण अन्यथा
				d += प्र_लिखो(d, " ..");
		पूर्ण
	पूर्ण
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&ftdi->udev->dev, "failed %d to submit urb %p to write %d commands totaling %d bytes to the Uxxx\n",
			retval, urb, command_size, total_size);
		usb_मुक्त_coherent(ftdi->udev, total_size, buf, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		वापस retval;
	पूर्ण
	usb_मुक्त_urb(urb);        /* release our reference to this urb,
				     the USB core will eventually मुक्त it entirely */
	ftdi->command_head += command_size;
	ftdi_elan_kick_respond_queue(ftdi);
	वापस 0;
पूर्ण

अटल व्योम ftdi_elan_करो_callback(काष्ठा usb_ftdi *ftdi,
				  काष्ठा u132_target *target, u8 *buffer, पूर्णांक length)
अणु
	काष्ठा urb *urb = target->urb;
	पूर्णांक halted = target->halted;
	पूर्णांक skipped = target->skipped;
	पूर्णांक actual = target->actual;
	पूर्णांक non_null = target->non_null;
	पूर्णांक toggle_bits = target->toggle_bits;
	पूर्णांक error_count = target->error_count;
	पूर्णांक condition_code = target->condition_code;
	पूर्णांक repeat_number = target->repeat_number;
	व्योम (*callback) (व्योम *, काष्ठा urb *, u8 *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक,
			  पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक) = target->callback;
	target->active -= 1;
	target->callback = शून्य;
	(*callback) (target->endp, urb, buffer, length, toggle_bits,
		     error_count, condition_code, repeat_number, halted, skipped,
		     actual, non_null);
पूर्ण

अटल अक्षर *have_ed_set_response(काष्ठा usb_ftdi *ftdi,
				  काष्ठा u132_target *target, u16 ed_length, पूर्णांक ed_number, पूर्णांक ed_type,
				  अक्षर *b)
अणु
	पूर्णांक payload = (ed_length >> 0) & 0x07FF;
	mutex_lock(&ftdi->u132_lock);
	target->actual = 0;
	target->non_null = (ed_length >> 15) & 0x0001;
	target->repeat_number = (ed_length >> 11) & 0x000F;
	अगर (ed_type == 0x02 || ed_type == 0x03) अणु
		अगर (payload == 0 || target->abanकरोning > 0) अणु
			target->abanकरोning = 0;
			mutex_unlock(&ftdi->u132_lock);
			ftdi_elan_करो_callback(ftdi, target, 4 + ftdi->response,
					      payload);
			ftdi->received = 0;
			ftdi->expected = 4;
			ftdi->ed_found = 0;
			वापस ftdi->response;
		पूर्ण अन्यथा अणु
			ftdi->expected = 4 + payload;
			ftdi->ed_found = 1;
			mutex_unlock(&ftdi->u132_lock);
			वापस b;
		पूर्ण
	पूर्ण अन्यथा अणु
		target->abanकरोning = 0;
		mutex_unlock(&ftdi->u132_lock);
		ftdi_elan_करो_callback(ftdi, target, 4 + ftdi->response,
				      payload);
		ftdi->received = 0;
		ftdi->expected = 4;
		ftdi->ed_found = 0;
		वापस ftdi->response;
	पूर्ण
पूर्ण

अटल अक्षर *have_ed_get_response(काष्ठा usb_ftdi *ftdi,
				  काष्ठा u132_target *target, u16 ed_length, पूर्णांक ed_number, पूर्णांक ed_type,
				  अक्षर *b)
अणु
	mutex_lock(&ftdi->u132_lock);
	target->condition_code = TD_DEVNOTRESP;
	target->actual = (ed_length >> 0) & 0x01FF;
	target->non_null = (ed_length >> 15) & 0x0001;
	target->repeat_number = (ed_length >> 11) & 0x000F;
	mutex_unlock(&ftdi->u132_lock);
	अगर (target->active)
		ftdi_elan_करो_callback(ftdi, target, शून्य, 0);
	target->abanकरोning = 0;
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	वापस ftdi->response;
पूर्ण


/*
 * The engine tries to empty the FTDI fअगरo
 *
 * all responses found in the fअगरo data are dispatched thus
 * the response buffer can only ever hold a maximum sized
 * response from the Uxxx.
 *
 */
अटल पूर्णांक ftdi_elan_respond_engine(काष्ठा usb_ftdi *ftdi)
अणु
	u8 *b = ftdi->response + ftdi->received;
	पूर्णांक bytes_पढ़ो = 0;
	पूर्णांक retry_on_empty = 1;
	पूर्णांक retry_on_समयout = 3;
पढ़ो:अणु
		पूर्णांक packet_bytes = 0;
		पूर्णांक retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpoपूर्णांकAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 500);
		अक्षर diag[30 *3 + 4];
		अक्षर *d = diag;
		पूर्णांक m = packet_bytes;
		u8 *c = ftdi->bulk_in_buffer;
		पूर्णांक s = (माप(diag) - 1) / 3;
		diag[0] = 0;
		जबतक (s-- > 0 && m-- > 0) अणु
			अगर (s > 0 || m == 0) अणु
				d += प्र_लिखो(d, " %02X", *c++);
			पूर्ण अन्यथा
				d += प्र_लिखो(d, " ..");
		पूर्ण
		अगर (packet_bytes > 2) अणु
			ftdi->bulk_in_left = packet_bytes - 2;
			ftdi->bulk_in_last = 1;
			जाओ have;
		पूर्ण अन्यथा अगर (retval == -ETIMEDOUT) अणु
			अगर (retry_on_समयout-- > 0) अणु
				dev_err(&ftdi->udev->dev, "TIMED OUT with packet_bytes = %d with total %d bytes%s\n",
					packet_bytes, bytes_पढ़ो, diag);
				जाओ more;
			पूर्ण अन्यथा अगर (bytes_पढ़ो > 0) अणु
				dev_err(&ftdi->udev->dev, "ONLY %d bytes%s\n",
					bytes_पढ़ो, diag);
				वापस -ENOMEM;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "TIMED OUT with packet_bytes = %d with total %d bytes%s\n",
					packet_bytes, bytes_पढ़ो, diag);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अगर (retval == -EILSEQ) अणु
			dev_err(&ftdi->udev->dev, "error = %d with packet_bytes = %d with total %d bytes%s\n",
				retval, packet_bytes, bytes_पढ़ो, diag);
			वापस retval;
		पूर्ण अन्यथा अगर (retval) अणु
			dev_err(&ftdi->udev->dev, "error = %d with packet_bytes = %d with total %d bytes%s\n",
				retval, packet_bytes, bytes_पढ़ो, diag);
			वापस retval;
		पूर्ण अन्यथा अणु
			अगर (retry_on_empty-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण
more:अणु
		जाओ पढ़ो;
	पूर्ण
have:अगर (ftdi->bulk_in_left > 0) अणु
		u8 c = ftdi->bulk_in_buffer[++ftdi->bulk_in_last];
		bytes_पढ़ो += 1;
		ftdi->bulk_in_left -= 1;
		अगर (ftdi->received == 0 && c == 0xFF) अणु
			जाओ have;
		पूर्ण अन्यथा
			*b++ = c;
		अगर (++ftdi->received < ftdi->expected) अणु
			जाओ have;
		पूर्ण अन्यथा अगर (ftdi->ed_found) अणु
			पूर्णांक ed_number = (ftdi->response[0] >> 5) & 0x03;
			u16 ed_length = (ftdi->response[2] << 8) |
				ftdi->response[1];
			काष्ठा u132_target *target = &ftdi->target[ed_number];
			पूर्णांक payload = (ed_length >> 0) & 0x07FF;
			अक्षर diag[30 *3 + 4];
			अक्षर *d = diag;
			पूर्णांक m = payload;
			u8 *c = 4 + ftdi->response;
			पूर्णांक s = (माप(diag) - 1) / 3;
			diag[0] = 0;
			जबतक (s-- > 0 && m-- > 0) अणु
				अगर (s > 0 || m == 0) अणु
					d += प्र_लिखो(d, " %02X", *c++);
				पूर्ण अन्यथा
					d += प्र_लिखो(d, " ..");
			पूर्ण
			ftdi_elan_करो_callback(ftdi, target, 4 + ftdi->response,
					      payload);
			ftdi->received = 0;
			ftdi->expected = 4;
			ftdi->ed_found = 0;
			b = ftdi->response;
			जाओ have;
		पूर्ण अन्यथा अगर (ftdi->expected == 8) अणु
			u8 buscmd;
			पूर्णांक respond_head = ftdi->respond_head++;
			काष्ठा u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & respond_head];
			u32 data = ftdi->response[7];
			data <<= 8;
			data |= ftdi->response[6];
			data <<= 8;
			data |= ftdi->response[5];
			data <<= 8;
			data |= ftdi->response[4];
			*respond->value = data;
			*respond->result = 0;
			complete(&respond->रुको_completion);
			ftdi->received = 0;
			ftdi->expected = 4;
			ftdi->ed_found = 0;
			b = ftdi->response;
			buscmd = (ftdi->response[0] >> 0) & 0x0F;
			अगर (buscmd == 0x00) अणु
			पूर्ण अन्यथा अगर (buscmd == 0x02) अणु
			पूर्ण अन्यथा अगर (buscmd == 0x06) अणु
			पूर्ण अन्यथा अगर (buscmd == 0x0A) अणु
			पूर्ण अन्यथा
				dev_err(&ftdi->udev->dev, "Uxxx unknown(%0X) value = %08X\n",
					buscmd, data);
			जाओ have;
		पूर्ण अन्यथा अणु
			अगर ((ftdi->response[0] & 0x80) == 0x00) अणु
				ftdi->expected = 8;
				जाओ have;
			पूर्ण अन्यथा अणु
				पूर्णांक ed_number = (ftdi->response[0] >> 5) & 0x03;
				पूर्णांक ed_type = (ftdi->response[0] >> 0) & 0x03;
				u16 ed_length = (ftdi->response[2] << 8) |
					ftdi->response[1];
				काष्ठा u132_target *target = &ftdi->target[
					ed_number];
				target->halted = (ftdi->response[0] >> 3) &
					0x01;
				target->skipped = (ftdi->response[0] >> 2) &
					0x01;
				target->toggle_bits = (ftdi->response[3] >> 6)
					& 0x03;
				target->error_count = (ftdi->response[3] >> 4)
					& 0x03;
				target->condition_code = (ftdi->response[
								  3] >> 0) & 0x0F;
				अगर ((ftdi->response[0] & 0x10) == 0x00) अणु
					b = have_ed_set_response(ftdi, target,
								 ed_length, ed_number, ed_type,
								 b);
					जाओ have;
				पूर्ण अन्यथा अणु
					b = have_ed_get_response(ftdi, target,
								 ed_length, ed_number, ed_type,
								 b);
					जाओ have;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		जाओ more;
पूर्ण


/*
 * create a urb, and a buffer क्रम it, and copy the data to the urb
 *
 */
अटल sमाप_प्रकार ftdi_elan_ग_लिखो(काष्ठा file *file,
			       स्थिर अक्षर __user *user_buffer, माप_प्रकार count,
			       loff_t *ppos)
अणु
	पूर्णांक retval = 0;
	काष्ठा urb *urb;
	अक्षर *buf;
	काष्ठा usb_ftdi *ftdi = file->निजी_data;

	अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (count == 0) अणु
		जाओ निकास;
	पूर्ण
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb) अणु
		retval = -ENOMEM;
		जाओ error_1;
	पूर्ण
	buf = usb_alloc_coherent(ftdi->udev, count, GFP_KERNEL,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		retval = -ENOMEM;
		जाओ error_2;
	पूर्ण
	अगर (copy_from_user(buf, user_buffer, count)) अणु
		retval = -EFAULT;
		जाओ error_3;
	पूर्ण
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpoपूर्णांकAddr), buf, count,
			  ftdi_elan_ग_लिखो_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&ftdi->udev->dev,
			"failed submitting write urb, error %d\n", retval);
		जाओ error_3;
	पूर्ण
	usb_मुक्त_urb(urb);

निकास:
	वापस count;
error_3:
	usb_मुक्त_coherent(ftdi->udev, count, buf, urb->transfer_dma);
error_2:
	usb_मुक्त_urb(urb);
error_1:
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations ftdi_elan_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.पढ़ो = ftdi_elan_पढ़ो,
	.ग_लिखो = ftdi_elan_ग_लिखो,
	.खोलो = ftdi_elan_खोलो,
	.release = ftdi_elan_release,
पूर्ण;

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver ftdi_elan_jtag_class = अणु
	.name = "ftdi-%d-jtag",
	.fops = &ftdi_elan_fops,
	.minor_base = USB_FTDI_ELAN_MINOR_BASE,
पूर्ण;

/*
 * the following definitions are क्रम the
 * ELAN FPGA state machgine processor that
 * lies on the other side of the FTDI chip
 */
#घोषणा cPCIu132rd 0x0
#घोषणा cPCIu132wr 0x1
#घोषणा cPCIiord 0x2
#घोषणा cPCIiowr 0x3
#घोषणा cPCImemrd 0x6
#घोषणा cPCImemwr 0x7
#घोषणा cPCIcfgrd 0xA
#घोषणा cPCIcfgwr 0xB
#घोषणा cPCInull 0xF
#घोषणा cU132cmd_status 0x0
#घोषणा cU132flash 0x1
#घोषणा cPIDsetup 0x0
#घोषणा cPIDout 0x1
#घोषणा cPIDin 0x2
#घोषणा cPIDinonce 0x3
#घोषणा cCCnoerror 0x0
#घोषणा cCCcrc 0x1
#घोषणा cCCbitstuff 0x2
#घोषणा cCCtoggle 0x3
#घोषणा cCCstall 0x4
#घोषणा cCCnoresp 0x5
#घोषणा cCCbadpid1 0x6
#घोषणा cCCbadpid2 0x7
#घोषणा cCCdataoverrun 0x8
#घोषणा cCCdataunderrun 0x9
#घोषणा cCCbuffoverrun 0xC
#घोषणा cCCbuffunderrun 0xD
#घोषणा cCCnotaccessed 0xF
अटल पूर्णांक ftdi_elan_ग_लिखो_reg(काष्ठा usb_ftdi *ftdi, u32 data)
अणु
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x00 | cPCIu132wr;
			command->length = 0x04;
			command->address = 0x00;
			command->width = 0x00;
			command->follows = 4;
			command->value = data;
			command->buffer = &command->value;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ftdi_elan_ग_लिखो_config(काष्ठा usb_ftdi *ftdi, पूर्णांक config_offset,
				  u8 width, u32 data)
अणु
	u8 addressofs = config_offset / 4;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x00 | (cPCIcfgwr & 0x0F);
			command->length = 0x04;
			command->address = addressofs;
			command->width = 0x00 | (width & 0x0F);
			command->follows = 4;
			command->value = data;
			command->buffer = &command->value;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ftdi_elan_ग_लिखो_pcimem(काष्ठा usb_ftdi *ftdi, पूर्णांक mem_offset,
				  u8 width, u32 data)
अणु
	u8 addressofs = mem_offset / 4;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x00 | (cPCImemwr & 0x0F);
			command->length = 0x04;
			command->address = addressofs;
			command->width = 0x00 | (width & 0x0F);
			command->follows = 4;
			command->value = data;
			command->buffer = &command->value;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_ग_लिखो_pcimem(काष्ठा platक्रमm_device *pdev, पूर्णांक mem_offset,
			       u8 width, u32 data)
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_ग_लिखो_pcimem(ftdi, mem_offset, width, data);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_ग_लिखो_pcimem);
अटल पूर्णांक ftdi_elan_पढ़ो_reg(काष्ठा usb_ftdi *ftdi, u32 *data)
अणु
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		पूर्णांक respond_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		respond_size = ftdi->respond_next - ftdi->respond_head;
		अगर (command_size < COMMAND_SIZE && respond_size < RESPOND_SIZE)
		अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			काष्ठा u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & ftdi->respond_next];
			पूर्णांक result = -ENODEV;
			respond->result = &result;
			respond->header = command->header = 0x00 | cPCIu132rd;
			command->length = 0x04;
			respond->address = command->address = cU132cmd_status;
			command->width = 0x00;
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			respond->value = data;
			init_completion(&respond->रुको_completion);
			ftdi->command_next += 1;
			ftdi->respond_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			रुको_क्रम_completion(&respond->रुको_completion);
			वापस result;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ftdi_elan_पढ़ो_config(काष्ठा usb_ftdi *ftdi, पूर्णांक config_offset,
				 u8 width, u32 *data)
अणु
	u8 addressofs = config_offset / 4;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		पूर्णांक respond_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		respond_size = ftdi->respond_next - ftdi->respond_head;
		अगर (command_size < COMMAND_SIZE && respond_size < RESPOND_SIZE)
		अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			काष्ठा u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & ftdi->respond_next];
			पूर्णांक result = -ENODEV;
			respond->result = &result;
			respond->header = command->header = 0x00 | (cPCIcfgrd &
								    0x0F);
			command->length = 0x04;
			respond->address = command->address = addressofs;
			command->width = 0x00 | (width & 0x0F);
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			respond->value = data;
			init_completion(&respond->रुको_completion);
			ftdi->command_next += 1;
			ftdi->respond_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			रुको_क्रम_completion(&respond->रुको_completion);
			वापस result;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ftdi_elan_पढ़ो_pcimem(काष्ठा usb_ftdi *ftdi, पूर्णांक mem_offset,
				 u8 width, u32 *data)
अणु
	u8 addressofs = mem_offset / 4;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		पूर्णांक respond_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		respond_size = ftdi->respond_next - ftdi->respond_head;
		अगर (command_size < COMMAND_SIZE && respond_size < RESPOND_SIZE)
		अणु
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			काष्ठा u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & ftdi->respond_next];
			पूर्णांक result = -ENODEV;
			respond->result = &result;
			respond->header = command->header = 0x00 | (cPCImemrd &
								    0x0F);
			command->length = 0x04;
			respond->address = command->address = addressofs;
			command->width = 0x00 | (width & 0x0F);
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			respond->value = data;
			init_completion(&respond->रुको_completion);
			ftdi->command_next += 1;
			ftdi->respond_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			रुको_क्रम_completion(&respond->रुको_completion);
			वापस result;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_पढ़ो_pcimem(काष्ठा platक्रमm_device *pdev, पूर्णांक mem_offset,
			      u8 width, u32 *data)
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा
		वापस ftdi_elan_पढ़ो_pcimem(ftdi, mem_offset, width, data);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_पढ़ो_pcimem);
अटल पूर्णांक ftdi_elan_edset_setup(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				 व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
				 व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						   पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						   पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	u8 ed = ed_number - 1;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_target *target = &ftdi->target[ed];
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x80 | (ed << 5);
			command->length = 0x8007;
			command->address = (toggle_bits << 6) | (ep_number << 2)
				| (address << 0);
			command->width = usb_maxpacket(urb->dev, urb->pipe,
						       usb_pipeout(urb->pipe));
			command->follows = 8;
			command->value = 0;
			command->buffer = urb->setup_packet;
			target->callback = callback;
			target->endp = endp;
			target->urb = urb;
			target->active = 1;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_setup(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			      व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
			      व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_setup(ftdi, ed_number, endp, urb, address,
				     ep_number, toggle_bits, callback);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_setup);
अटल पूर्णांक ftdi_elan_edset_input(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				 व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
				 व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						   पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						   पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	u8 ed = ed_number - 1;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_target *target = &ftdi->target[ed];
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			u32 reमुख्यing_length = urb->transfer_buffer_length -
				urb->actual_length;
			command->header = 0x82 | (ed << 5);
			अगर (reमुख्यing_length == 0) अणु
				command->length = 0x0000;
			पूर्ण अन्यथा अगर (reमुख्यing_length > 1024) अणु
				command->length = 0x8000 | 1023;
			पूर्ण अन्यथा
				command->length = 0x8000 | (reमुख्यing_length -
							    1);
			command->address = (toggle_bits << 6) | (ep_number << 2)
				| (address << 0);
			command->width = usb_maxpacket(urb->dev, urb->pipe,
						       usb_pipeout(urb->pipe));
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			target->callback = callback;
			target->endp = endp;
			target->urb = urb;
			target->active = 1;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_input(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			      व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
			      व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_input(ftdi, ed_number, endp, urb, address,
				     ep_number, toggle_bits, callback);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_input);
अटल पूर्णांक ftdi_elan_edset_empty(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				 व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
				 व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						   पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						   पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	u8 ed = ed_number - 1;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			काष्ठा u132_target *target = &ftdi->target[ed];
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x81 | (ed << 5);
			command->length = 0x0000;
			command->address = (toggle_bits << 6) | (ep_number << 2)
				| (address << 0);
			command->width = usb_maxpacket(urb->dev, urb->pipe,
						       usb_pipeout(urb->pipe));
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			target->callback = callback;
			target->endp = endp;
			target->urb = urb;
			target->active = 1;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_empty(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			      व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
			      व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_empty(ftdi, ed_number, endp, urb, address,
				     ep_number, toggle_bits, callback);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_empty);
अटल पूर्णांक ftdi_elan_edset_output(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				  व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
				  व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						    पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						    पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	u8 ed = ed_number - 1;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			u8 *b;
			u16 urb_size;
			पूर्णांक i = 0;
			अक्षर data[30 *3 + 4];
			अक्षर *d = data;
			पूर्णांक m = (माप(data) - 1) / 3 - 1;
			पूर्णांक l = 0;
			काष्ठा u132_target *target = &ftdi->target[ed];
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x81 | (ed << 5);
			command->address = (toggle_bits << 6) | (ep_number << 2)
				| (address << 0);
			command->width = usb_maxpacket(urb->dev, urb->pipe,
						       usb_pipeout(urb->pipe));
			command->follows = min_t(u32, 1024,
						 urb->transfer_buffer_length -
						 urb->actual_length);
			command->value = 0;
			command->buffer = urb->transfer_buffer +
				urb->actual_length;
			command->length = 0x8000 | (command->follows - 1);
			b = command->buffer;
			urb_size = command->follows;
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
			target->callback = callback;
			target->endp = endp;
			target->urb = urb;
			target->active = 1;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_output(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			       व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
			       व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						 पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_output(ftdi, ed_number, endp, urb, address,
				      ep_number, toggle_bits, callback);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_output);
अटल पूर्णांक ftdi_elan_edset_single(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				  व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
				  व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						    पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						    पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	u8 ed = ed_number - 1;
रुको:अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक command_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		अगर (command_size < COMMAND_SIZE) अणु
			u32 reमुख्यing_length = urb->transfer_buffer_length -
				urb->actual_length;
			काष्ठा u132_target *target = &ftdi->target[ed];
			काष्ठा u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			command->header = 0x83 | (ed << 5);
			अगर (reमुख्यing_length == 0) अणु
				command->length = 0x0000;
			पूर्ण अन्यथा अगर (reमुख्यing_length > 1024) अणु
				command->length = 0x8000 | 1023;
			पूर्ण अन्यथा
				command->length = 0x8000 | (reमुख्यing_length -
							    1);
			command->address = (toggle_bits << 6) | (ep_number << 2)
				| (address << 0);
			command->width = usb_maxpacket(urb->dev, urb->pipe,
						       usb_pipeout(urb->pipe));
			command->follows = 0;
			command->value = 0;
			command->buffer = शून्य;
			target->callback = callback;
			target->endp = endp;
			target->urb = urb;
			target->active = 1;
			ftdi->command_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			जाओ रुको;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_single(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			       व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
			       व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
						 पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
						 पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null))
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_single(ftdi, ed_number, endp, urb, address,
				      ep_number, toggle_bits, callback);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_single);
अटल पूर्णांक ftdi_elan_edset_flush(काष्ठा usb_ftdi *ftdi, u8 ed_number,
				 व्योम *endp)
अणु
	u8 ed = ed_number - 1;
	अगर (ftdi->disconnected > 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (ftdi->initialized == 0) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		काष्ठा u132_target *target = &ftdi->target[ed];
		mutex_lock(&ftdi->u132_lock);
		अगर (target->abanकरोning > 0) अणु
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण अन्यथा अणु
			target->abanकरोning = 1;
		रुको_1:अगर (target->active == 1) अणु
				पूर्णांक command_size = ftdi->command_next -
					ftdi->command_head;
				अगर (command_size < COMMAND_SIZE) अणु
					काष्ठा u132_command *command =
						&ftdi->command[COMMAND_MASK &
							       ftdi->command_next];
					command->header = 0x80 | (ed << 5) |
						0x4;
					command->length = 0x00;
					command->address = 0x00;
					command->width = 0x00;
					command->follows = 0;
					command->value = 0;
					command->buffer = &command->value;
					ftdi->command_next += 1;
					ftdi_elan_kick_command_queue(ftdi);
				पूर्ण अन्यथा अणु
					mutex_unlock(&ftdi->u132_lock);
					msleep(100);
					mutex_lock(&ftdi->u132_lock);
					जाओ रुको_1;
				पूर्ण
			पूर्ण
			mutex_unlock(&ftdi->u132_lock);
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक usb_ftdi_elan_edset_flush(काष्ठा platक्रमm_device *pdev, u8 ed_number,
			      व्योम *endp)
अणु
	काष्ठा usb_ftdi *ftdi = platक्रमm_device_to_usb_ftdi(pdev);
	वापस ftdi_elan_edset_flush(ftdi, ed_number, endp);
पूर्ण


EXPORT_SYMBOL_GPL(usb_ftdi_elan_edset_flush);
अटल पूर्णांक ftdi_elan_flush_input_fअगरo(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retry_on_empty = 10;
	पूर्णांक retry_on_समयout = 5;
	पूर्णांक retry_on_status = 20;
more:अणु
		पूर्णांक packet_bytes = 0;
		पूर्णांक retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpoपूर्णांकAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 100);
		अगर (packet_bytes > 2) अणु
			अक्षर diag[30 *3 + 4];
			अक्षर *d = diag;
			पूर्णांक m = (माप(diag) - 1) / 3 - 1;
			अक्षर *b = ftdi->bulk_in_buffer;
			पूर्णांक bytes_पढ़ो = 0;
			diag[0] = 0;
			जबतक (packet_bytes-- > 0) अणु
				अक्षर c = *b++;
				अगर (bytes_पढ़ो < m) अणु
					d += प्र_लिखो(d, " %02X",
						     0x000000FF & c);
				पूर्ण अन्यथा अगर (bytes_पढ़ो > m) अणु
				पूर्ण अन्यथा
					d += प्र_लिखो(d, " ..");
				bytes_पढ़ो += 1;
				जारी;
			पूर्ण
			जाओ more;
		पूर्ण अन्यथा अगर (packet_bytes > 1) अणु
			अक्षर s1 = ftdi->bulk_in_buffer[0];
			अक्षर s2 = ftdi->bulk_in_buffer[1];
			अगर (s1 == 0x31 && s2 == 0x60) अणु
				वापस 0;
			पूर्ण अन्यथा अगर (retry_on_status-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "STATUS ERROR retry limit reached\n");
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अगर (packet_bytes > 0) अणु
			अक्षर b1 = ftdi->bulk_in_buffer[0];
			dev_err(&ftdi->udev->dev, "only one byte flushed from FTDI = %02X\n",
				b1);
			अगर (retry_on_status-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "STATUS ERROR retry limit reached\n");
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अगर (retval == -ETIMEDOUT) अणु
			अगर (retry_on_समयout-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "TIMED OUT retry limit reached\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अगर (retval == 0) अणु
			अगर (retry_on_empty-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "empty packet retry limit reached\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "error = %d\n", retval);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण


/*
 * send the दीर्घ flush sequence
 *
 */
अटल पूर्णांक ftdi_elan_synchronize_flush(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retval;
	काष्ठा urb *urb;
	अक्षर *buf;
	पूर्णांक I = 257;
	पूर्णांक i = 0;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;
	buf = usb_alloc_coherent(ftdi->udev, I, GFP_KERNEL, &urb->transfer_dma);
	अगर (!buf) अणु
		dev_err(&ftdi->udev->dev, "could not get a buffer for flush sequence\n");
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण
	जबतक (I-- > 0)
		buf[i++] = 0x55;
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpoपूर्णांकAddr), buf, i,
			  ftdi_elan_ग_लिखो_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&ftdi->udev->dev, "failed to submit urb containing the flush sequence\n");
		usb_मुक्त_coherent(ftdi->udev, i, buf, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण
	usb_मुक्त_urb(urb);
	वापस 0;
पूर्ण


/*
 * send the reset sequence
 *
 */
अटल पूर्णांक ftdi_elan_synchronize_reset(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retval;
	काष्ठा urb *urb;
	अक्षर *buf;
	पूर्णांक I = 4;
	पूर्णांक i = 0;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;
	buf = usb_alloc_coherent(ftdi->udev, I, GFP_KERNEL, &urb->transfer_dma);
	अगर (!buf) अणु
		dev_err(&ftdi->udev->dev, "could not get a buffer for the reset sequence\n");
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण
	buf[i++] = 0x55;
	buf[i++] = 0xAA;
	buf[i++] = 0x5A;
	buf[i++] = 0xA5;
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpoपूर्णांकAddr), buf, i,
			  ftdi_elan_ग_लिखो_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&ftdi->udev->dev, "failed to submit urb containing the reset sequence\n");
		usb_मुक्त_coherent(ftdi->udev, i, buf, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण
	usb_मुक्त_urb(urb);
	वापस 0;
पूर्ण

अटल पूर्णांक ftdi_elan_synchronize(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retval;
	पूर्णांक दीर्घ_stop = 10;
	पूर्णांक retry_on_समयout = 5;
	पूर्णांक retry_on_empty = 10;
	पूर्णांक err_count = 0;
	retval = ftdi_elan_flush_input_fअगरo(ftdi);
	अगर (retval)
		वापस retval;
	ftdi->bulk_in_left = 0;
	ftdi->bulk_in_last = -1;
	जबतक (दीर्घ_stop-- > 0) अणु
		पूर्णांक पढ़ो_stop;
		पूर्णांक पढ़ो_stuck;
		retval = ftdi_elan_synchronize_flush(ftdi);
		अगर (retval)
			वापस retval;
		retval = ftdi_elan_flush_input_fअगरo(ftdi);
		अगर (retval)
			वापस retval;
	reset:retval = ftdi_elan_synchronize_reset(ftdi);
		अगर (retval)
			वापस retval;
		पढ़ो_stop = 100;
		पढ़ो_stuck = 10;
	पढ़ो:अणु
			पूर्णांक packet_bytes = 0;
			retval = usb_bulk_msg(ftdi->udev,
					      usb_rcvbulkpipe(ftdi->udev,
							      ftdi->bulk_in_endpoपूर्णांकAddr),
					      ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					      &packet_bytes, 500);
			अगर (packet_bytes > 2) अणु
				अक्षर diag[30 *3 + 4];
				अक्षर *d = diag;
				पूर्णांक m = (माप(diag) - 1) / 3 - 1;
				अक्षर *b = ftdi->bulk_in_buffer;
				पूर्णांक bytes_पढ़ो = 0;
				अचिन्हित अक्षर c = 0;
				diag[0] = 0;
				जबतक (packet_bytes-- > 0) अणु
					c = *b++;
					अगर (bytes_पढ़ो < m) अणु
						d += प्र_लिखो(d, " %02X", c);
					पूर्ण अन्यथा अगर (bytes_पढ़ो > m) अणु
					पूर्ण अन्यथा
						d += प्र_लिखो(d, " ..");
					bytes_पढ़ो += 1;
					जारी;
				पूर्ण
				अगर (c == 0x7E) अणु
					वापस 0;
				पूर्ण अन्यथा अणु
					अगर (c == 0x55) अणु
						जाओ पढ़ो;
					पूर्ण अन्यथा अगर (पढ़ो_stop-- > 0) अणु
						जाओ पढ़ो;
					पूर्ण अन्यथा अणु
						dev_err(&ftdi->udev->dev, "retry limit reached\n");
						जारी;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (packet_bytes > 1) अणु
				अचिन्हित अक्षर s1 = ftdi->bulk_in_buffer[0];
				अचिन्हित अक्षर s2 = ftdi->bulk_in_buffer[1];
				अगर (s1 == 0x31 && s2 == 0x00) अणु
					अगर (पढ़ो_stuck-- > 0) अणु
						जाओ पढ़ो;
					पूर्ण अन्यथा
						जाओ reset;
				पूर्ण अन्यथा अणु
					अगर (पढ़ो_stop-- > 0) अणु
						जाओ पढ़ो;
					पूर्ण अन्यथा अणु
						dev_err(&ftdi->udev->dev, "retry limit reached\n");
						जारी;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (packet_bytes > 0) अणु
				अगर (पढ़ो_stop-- > 0) अणु
					जाओ पढ़ो;
				पूर्ण अन्यथा अणु
					dev_err(&ftdi->udev->dev, "retry limit reached\n");
					जारी;
				पूर्ण
			पूर्ण अन्यथा अगर (retval == -ETIMEDOUT) अणु
				अगर (retry_on_समयout-- > 0) अणु
					जाओ पढ़ो;
				पूर्ण अन्यथा अणु
					dev_err(&ftdi->udev->dev, "TIMED OUT retry limit reached\n");
					जारी;
				पूर्ण
			पूर्ण अन्यथा अगर (retval == 0) अणु
				अगर (retry_on_empty-- > 0) अणु
					जाओ पढ़ो;
				पूर्ण अन्यथा अणु
					dev_err(&ftdi->udev->dev, "empty packet retry limit reached\n");
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				err_count += 1;
				dev_err(&ftdi->udev->dev, "error = %d\n",
					retval);
				अगर (पढ़ो_stop-- > 0) अणु
					जाओ पढ़ो;
				पूर्ण अन्यथा अणु
					dev_err(&ftdi->udev->dev, "retry limit reached\n");
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	dev_err(&ftdi->udev->dev, "failed to synchronize\n");
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक ftdi_elan_stuck_रुकोing(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक retry_on_empty = 10;
	पूर्णांक retry_on_समयout = 5;
	पूर्णांक retry_on_status = 50;
more:अणु
		पूर्णांक packet_bytes = 0;
		पूर्णांक retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpoपूर्णांकAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 1000);
		अगर (packet_bytes > 2) अणु
			अक्षर diag[30 *3 + 4];
			अक्षर *d = diag;
			पूर्णांक m = (माप(diag) - 1) / 3 - 1;
			अक्षर *b = ftdi->bulk_in_buffer;
			पूर्णांक bytes_पढ़ो = 0;
			diag[0] = 0;
			जबतक (packet_bytes-- > 0) अणु
				अक्षर c = *b++;
				अगर (bytes_पढ़ो < m) अणु
					d += प्र_लिखो(d, " %02X",
						     0x000000FF & c);
				पूर्ण अन्यथा अगर (bytes_पढ़ो > m) अणु
				पूर्ण अन्यथा
					d += प्र_लिखो(d, " ..");
				bytes_पढ़ो += 1;
				जारी;
			पूर्ण
			जाओ more;
		पूर्ण अन्यथा अगर (packet_bytes > 1) अणु
			अक्षर s1 = ftdi->bulk_in_buffer[0];
			अक्षर s2 = ftdi->bulk_in_buffer[1];
			अगर (s1 == 0x31 && s2 == 0x60) अणु
				वापस 0;
			पूर्ण अन्यथा अगर (retry_on_status-- > 0) अणु
				msleep(5);
				जाओ more;
			पूर्ण अन्यथा
				वापस -EFAULT;
		पूर्ण अन्यथा अगर (packet_bytes > 0) अणु
			अक्षर b1 = ftdi->bulk_in_buffer[0];
			dev_err(&ftdi->udev->dev, "only one byte flushed from FTDI = %02X\n", b1);
			अगर (retry_on_status-- > 0) अणु
				msleep(5);
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "STATUS ERROR retry limit reached\n");
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अगर (retval == -ETIMEDOUT) अणु
			अगर (retry_on_समयout-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "TIMED OUT retry limit reached\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अगर (retval == 0) अणु
			अगर (retry_on_empty-- > 0) अणु
				जाओ more;
			पूर्ण अन्यथा अणु
				dev_err(&ftdi->udev->dev, "empty packet retry limit reached\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "error = %d\n", retval);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक ftdi_elan_checkingPCI(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &ftdi->controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	अगर (ftdi->controlreg & 0x00400000) अणु
		अगर (ftdi->card_ejected) अणु
		पूर्ण अन्यथा अणु
			ftdi->card_ejected = 1;
			dev_err(&ftdi->udev->dev, "CARD EJECTED - controlreg = %08X\n",
				ftdi->controlreg);
		पूर्ण
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		u8 fn = ftdi->function - 1;
		पूर्णांक activePCIfn = fn << 8;
		u32 pcidata;
		u32 pciVID;
		u32 pciPID;
		पूर्णांक reg = 0;
		UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
						   &pcidata);
		अगर (UxxxStatus)
			वापस UxxxStatus;
		pciVID = pcidata & 0xFFFF;
		pciPID = (pcidata >> 16) & 0xFFFF;
		अगर (pciVID == ftdi->platक्रमm_data.venकरोr && pciPID ==
		    ftdi->platक्रमm_data.device) अणु
			वापस 0;
		पूर्ण अन्यथा अणु
			dev_err(&ftdi->udev->dev, "vendor=%04X pciVID=%04X device=%04X pciPID=%04X\n",
				ftdi->platक्रमm_data.venकरोr, pciVID,
				ftdi->platक्रमm_data.device, pciPID);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
पूर्ण


#घोषणा ftdi_पढ़ो_pcimem(ftdi, member, data) ftdi_elan_पढ़ो_pcimem(ftdi, \
								   दुरत्व(काष्ठा ohci_regs, member), 0, data);
#घोषणा ftdi_ग_लिखो_pcimem(ftdi, member, data) ftdi_elan_ग_लिखो_pcimem(ftdi, \
								     दुरत्व(काष्ठा ohci_regs, member), 0, data);

#घोषणा OHCI_CONTROL_INIT OHCI_CTRL_CBSR
#घोषणा OHCI_INTR_INIT (OHCI_INTR_MIE | OHCI_INTR_UE | OHCI_INTR_RD |	\
			OHCI_INTR_WDH)
अटल पूर्णांक ftdi_elan_check_controller(काष्ठा usb_ftdi *ftdi, पूर्णांक quirk)
अणु
	पूर्णांक devices = 0;
	पूर्णांक retval;
	u32 hc_control;
	पूर्णांक num_ports;
	u32 control;
	u32 rh_a = -1;
	u32 status;
	u32 fmपूर्णांकerval;
	u32 hc_fmपूर्णांकerval;
	u32 periodicstart;
	u32 cmdstatus;
	u32 roothub_a;
	पूर्णांक mask = OHCI_INTR_INIT;
	पूर्णांक sleep_समय = 0;
	पूर्णांक reset_समयout = 30;        /* ... allow extra समय */
	पूर्णांक temp;
	retval = ftdi_ग_लिखो_pcimem(ftdi, पूर्णांकrdisable, OHCI_INTR_MIE);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, roothub.a, &rh_a);
	अगर (retval)
		वापस retval;
	num_ports = rh_a & RH_A_NDP;
	retval = ftdi_पढ़ो_pcimem(ftdi, fmपूर्णांकerval, &hc_fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	hc_fmपूर्णांकerval &= 0x3fff;
	अगर (hc_fmपूर्णांकerval != FI) अणु
	पूर्ण
	hc_fmपूर्णांकerval |= FSMP(hc_fmपूर्णांकerval) << 16;
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &hc_control);
	अगर (retval)
		वापस retval;
	चयन (hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_OPER:
		sleep_समय = 0;
		अवरोध;
	हाल OHCI_USB_SUSPEND:
	हाल OHCI_USB_RESUME:
		hc_control &= OHCI_CTRL_RWC;
		hc_control |= OHCI_USB_RESUME;
		sleep_समय = 10;
		अवरोध;
	शेष:
		hc_control &= OHCI_CTRL_RWC;
		hc_control |= OHCI_USB_RESET;
		sleep_समय = 50;
		अवरोध;
	पूर्ण
	retval = ftdi_ग_लिखो_pcimem(ftdi, control, hc_control);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
	अगर (retval)
		वापस retval;
	msleep(sleep_समय);
	retval = ftdi_पढ़ो_pcimem(ftdi, roothub.a, &roothub_a);
	अगर (retval)
		वापस retval;
	अगर (!(roothub_a & RH_A_NPS)) अणु        /* घातer करोwn each port */
		क्रम (temp = 0; temp < num_ports; temp++) अणु
			retval = ftdi_ग_लिखो_pcimem(ftdi,
						   roothub.portstatus[temp], RH_PS_LSDA);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
	अगर (retval)
		वापस retval;
retry:retval = ftdi_पढ़ो_pcimem(ftdi, cmdstatus, &status);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, cmdstatus, OHCI_HCR);
	अगर (retval)
		वापस retval;
extra:अणु
		retval = ftdi_पढ़ो_pcimem(ftdi, cmdstatus, &status);
		अगर (retval)
			वापस retval;
		अगर (0 != (status & OHCI_HCR)) अणु
			अगर (--reset_समयout == 0) अणु
				dev_err(&ftdi->udev->dev, "USB HC reset timed out!\n");
				वापस -ENODEV;
			पूर्ण अन्यथा अणु
				msleep(5);
				जाओ extra;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (quirk & OHCI_QUIRK_INITRESET) अणु
		retval = ftdi_ग_लिखो_pcimem(ftdi, control, hc_control);
		अगर (retval)
			वापस retval;
		retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = ftdi_ग_लिखो_pcimem(ftdi, ed_controlhead, 0x00000000);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, ed_bulkhead, 0x11000000);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, hcca, 0x00000000);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, fmपूर्णांकerval, &fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, fmपूर्णांकerval,
				   ((fmपूर्णांकerval & FIT) ^ FIT) | hc_fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, periodicstart,
				   ((9 *hc_fmपूर्णांकerval) / 10) & 0x3fff);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, fmपूर्णांकerval, &fmपूर्णांकerval);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, periodicstart, &periodicstart);
	अगर (retval)
		वापस retval;
	अगर (0 == (fmपूर्णांकerval & 0x3fff0000) || 0 == periodicstart) अणु
		अगर (!(quirk & OHCI_QUIRK_INITRESET)) अणु
			quirk |= OHCI_QUIRK_INITRESET;
			जाओ retry;
		पूर्ण अन्यथा
			dev_err(&ftdi->udev->dev, "init err(%08x %04x)\n",
				fmपूर्णांकerval, periodicstart);
	पूर्ण                        /* start controller operations */
	hc_control &= OHCI_CTRL_RWC;
	hc_control |= OHCI_CONTROL_INIT | OHCI_CTRL_BLE | OHCI_USB_OPER;
	retval = ftdi_ग_लिखो_pcimem(ftdi, control, hc_control);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, cmdstatus, OHCI_BLF);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, cmdstatus, &cmdstatus);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, roothub.status, RH_HS_DRWE);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, पूर्णांकrstatus, mask);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, पूर्णांकrdisable,
				   OHCI_INTR_MIE | OHCI_INTR_OC | OHCI_INTR_RHSC | OHCI_INTR_FNO |
				   OHCI_INTR_UE | OHCI_INTR_RD | OHCI_INTR_SF | OHCI_INTR_WDH |
				   OHCI_INTR_SO);
	अगर (retval)
		वापस retval;        /* handle root hub init quirks ... */
	retval = ftdi_पढ़ो_pcimem(ftdi, roothub.a, &roothub_a);
	अगर (retval)
		वापस retval;
	roothub_a &= ~(RH_A_PSM | RH_A_OCPM);
	अगर (quirk & OHCI_QUIRK_SUPERIO) अणु
		roothub_a |= RH_A_NOCP;
		roothub_a &= ~(RH_A_POTPGT | RH_A_NPS);
		retval = ftdi_ग_लिखो_pcimem(ftdi, roothub.a, roothub_a);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अगर ((quirk & OHCI_QUIRK_AMD756) || distrust_firmware) अणु
		roothub_a |= RH_A_NPS;
		retval = ftdi_ग_लिखो_pcimem(ftdi, roothub.a, roothub_a);
		अगर (retval)
			वापस retval;
	पूर्ण
	retval = ftdi_ग_लिखो_pcimem(ftdi, roothub.status, RH_HS_LPSC);
	अगर (retval)
		वापस retval;
	retval = ftdi_ग_लिखो_pcimem(ftdi, roothub.b,
				   (roothub_a & RH_A_NPS) ? 0 : RH_B_PPCM);
	अगर (retval)
		वापस retval;
	retval = ftdi_पढ़ो_pcimem(ftdi, control, &control);
	अगर (retval)
		वापस retval;
	mdelay((roothub_a >> 23) & 0x1fe);
	क्रम (temp = 0; temp < num_ports; temp++) अणु
		u32 portstatus;
		retval = ftdi_पढ़ो_pcimem(ftdi, roothub.portstatus[temp],
					  &portstatus);
		अगर (retval)
			वापस retval;
		अगर (1 & portstatus)
			devices += 1;
	पूर्ण
	वापस devices;
पूर्ण

अटल पूर्णांक ftdi_elan_setup_controller(काष्ठा usb_ftdi *ftdi, पूर्णांक fn)
अणु
	u32 latence_समयr;
	पूर्णांक UxxxStatus;
	u32 pcidata;
	पूर्णांक reg = 0;
	पूर्णांक activePCIfn = fn << 8;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000025FL | 0x2800);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 16;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0,
					    0xFFFFFFFF);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0,
					    0xF0000000);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 12;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &latence_समयr);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	latence_समयr &= 0xFFFF00FF;
	latence_समयr |= 0x00001600;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0x00,
					    latence_समयr);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 4;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0x00,
					    0x06);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	क्रम (reg = 0; reg <= 0x54; reg += 4) अणु
		UxxxStatus = ftdi_elan_पढ़ो_pcimem(ftdi, reg, 0, &pcidata);
		अगर (UxxxStatus)
			वापस UxxxStatus;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ftdi_elan_बंद_controller(काष्ठा usb_ftdi *ftdi, पूर्णांक fn)
अणु
	u32 latence_समयr;
	पूर्णांक UxxxStatus;
	u32 pcidata;
	पूर्णांक reg = 0;
	पूर्णांक activePCIfn = fn << 8;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000025FL | 0x2800);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 16;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0,
					    0xFFFFFFFF);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0,
					    0x00000000);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 12;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &latence_समयr);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	latence_समयr &= 0xFFFF00FF;
	latence_समयr |= 0x00001600;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0x00,
					    latence_समयr);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
					   &pcidata);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	reg = 4;
	UxxxStatus = ftdi_elan_ग_लिखो_config(ftdi, activePCIfn | reg, 0x00,
					    0x00);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	वापस ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0, &pcidata);
पूर्ण

अटल पूर्णांक ftdi_elan_found_controller(काष्ठा usb_ftdi *ftdi, पूर्णांक fn, पूर्णांक quirk)
अणु
	पूर्णांक result;
	पूर्णांक UxxxStatus;
	UxxxStatus = ftdi_elan_setup_controller(ftdi, fn);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	result = ftdi_elan_check_controller(ftdi, quirk);
	UxxxStatus = ftdi_elan_बंद_controller(ftdi, fn);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	वापस result;
पूर्ण

अटल पूर्णांक ftdi_elan_क्रमागतeratePCI(काष्ठा usb_ftdi *ftdi)
अणु
	u32 controlreg;
	u8 sensebits;
	पूर्णांक UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x00000000L);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	msleep(750);
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x00000200L | 0x100);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x00000200L | 0x500);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000020CL | 0x000);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000020DL | 0x000);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	msleep(250);
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000020FL | 0x000);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_ग_लिखो_reg(ftdi, 0x0000025FL | 0x800);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	UxxxStatus = ftdi_elan_पढ़ो_reg(ftdi, &controlreg);
	अगर (UxxxStatus)
		वापस UxxxStatus;
	msleep(1000);
	sensebits = (controlreg >> 16) & 0x000F;
	अगर (0x0D == sensebits)
		वापस 0;
	अन्यथा
		वापस - ENXIO;
पूर्ण

अटल पूर्णांक ftdi_elan_setupOHCI(काष्ठा usb_ftdi *ftdi)
अणु
	पूर्णांक UxxxStatus;
	u32 pcidata;
	पूर्णांक reg = 0;
	u8 fn;
	पूर्णांक activePCIfn = 0;
	पूर्णांक max_devices = 0;
	पूर्णांक controllers = 0;
	पूर्णांक unrecognized = 0;
	ftdi->function = 0;
	क्रम (fn = 0; (fn < 4); fn++) अणु
		u32 pciVID = 0;
		u32 pciPID = 0;
		पूर्णांक devices = 0;
		activePCIfn = fn << 8;
		UxxxStatus = ftdi_elan_पढ़ो_config(ftdi, activePCIfn | reg, 0,
						   &pcidata);
		अगर (UxxxStatus)
			वापस UxxxStatus;
		pciVID = pcidata & 0xFFFF;
		pciPID = (pcidata >> 16) & 0xFFFF;
		अगर ((pciVID == PCI_VENDOR_ID_OPTI) && (pciPID == 0xc861)) अणु
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		पूर्ण अन्यथा अगर ((pciVID == PCI_VENDOR_ID_NEC) && (pciPID == 0x0035))
		अणु
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		पूर्ण अन्यथा अगर ((pciVID == PCI_VENDOR_ID_AL) && (pciPID == 0x5237)) अणु
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		पूर्ण अन्यथा अगर ((pciVID == PCI_VENDOR_ID_ATT) && (pciPID == 0x5802))
		अणु
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		पूर्ण अन्यथा अगर (pciVID == PCI_VENDOR_ID_AMD && pciPID == 0x740c) अणु
			devices = ftdi_elan_found_controller(ftdi, fn,
							     OHCI_QUIRK_AMD756);
			controllers += 1;
		पूर्ण अन्यथा अगर (pciVID == PCI_VENDOR_ID_COMPAQ && pciPID == 0xa0f8) अणु
			devices = ftdi_elan_found_controller(ftdi, fn,
							     OHCI_QUIRK_ZFMICRO);
			controllers += 1;
		पूर्ण अन्यथा अगर (0 == pcidata) अणु
		पूर्ण अन्यथा
			unrecognized += 1;
		अगर (devices > max_devices) अणु
			max_devices = devices;
			ftdi->function = fn + 1;
			ftdi->platक्रमm_data.venकरोr = pciVID;
			ftdi->platक्रमm_data.device = pciPID;
		पूर्ण
	पूर्ण
	अगर (ftdi->function > 0) अणु
		वापस ftdi_elan_setup_controller(ftdi,	ftdi->function - 1);
	पूर्ण अन्यथा अगर (controllers > 0) अणु
		वापस -ENXIO;
	पूर्ण अन्यथा अगर (unrecognized > 0) अणु
		वापस -ENXIO;
	पूर्ण अन्यथा अणु
		ftdi->क्रमागतerated = 0;
		वापस -ENXIO;
	पूर्ण
पूर्ण


/*
 * we use only the first bulk-in and bulk-out endpoपूर्णांकs
 */
अटल पूर्णांक ftdi_elan_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out;
	पूर्णांक retval;
	काष्ठा usb_ftdi *ftdi;

	ftdi = kzalloc(माप(काष्ठा usb_ftdi), GFP_KERNEL);
	अगर (!ftdi)
		वापस -ENOMEM;

	mutex_lock(&ftdi_module_lock);
	list_add_tail(&ftdi->ftdi_list, &ftdi_अटल_list);
	ftdi->sequence_num = ++ftdi_instances;
	mutex_unlock(&ftdi_module_lock);
	ftdi_elan_init_kref(ftdi);
	sema_init(&ftdi->sw_lock, 1);
	ftdi->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	ftdi->पूर्णांकerface = पूर्णांकerface;
	mutex_init(&ftdi->u132_lock);
	ftdi->expected = 4;

	अगरace_desc = पूर्णांकerface->cur_altsetting;
	retval = usb_find_common_endpoपूर्णांकs(अगरace_desc,
			&bulk_in, &bulk_out, शून्य, शून्य);
	अगर (retval) अणु
		dev_err(&ftdi->udev->dev, "Could not find both bulk-in and bulk-out endpoints\n");
		जाओ error;
	पूर्ण

	ftdi->bulk_in_size = usb_endpoपूर्णांक_maxp(bulk_in);
	ftdi->bulk_in_endpoपूर्णांकAddr = bulk_in->bEndpoपूर्णांकAddress;
	ftdi->bulk_in_buffer = kदो_स्मृति(ftdi->bulk_in_size, GFP_KERNEL);
	अगर (!ftdi->bulk_in_buffer) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	ftdi->bulk_out_endpoपूर्णांकAddr = bulk_out->bEndpoपूर्णांकAddress;

	dev_info(&ftdi->udev->dev, "interface %d has I=%02X O=%02X\n",
		 अगरace_desc->desc.bInterfaceNumber, ftdi->bulk_in_endpoपूर्णांकAddr,
		 ftdi->bulk_out_endpoपूर्णांकAddr);
	usb_set_पूर्णांकfdata(पूर्णांकerface, ftdi);
	अगर (अगरace_desc->desc.bInterfaceNumber == 0 &&
	    ftdi->bulk_in_endpoपूर्णांकAddr == 0x81 &&
	    ftdi->bulk_out_endpoपूर्णांकAddr == 0x02) अणु
		retval = usb_रेजिस्टर_dev(पूर्णांकerface, &ftdi_elan_jtag_class);
		अगर (retval) अणु
			dev_err(&ftdi->udev->dev, "Not able to get a minor for this device\n");
			usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
			retval = -ENOMEM;
			जाओ error;
		पूर्ण अन्यथा अणु
			ftdi->class = &ftdi_elan_jtag_class;
			dev_info(&ftdi->udev->dev, "USB FDTI=%p JTAG interface %d now attached to ftdi%d\n",
				 ftdi, अगरace_desc->desc.bInterfaceNumber,
				 पूर्णांकerface->minor);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (अगरace_desc->desc.bInterfaceNumber == 1 &&
		   ftdi->bulk_in_endpoपूर्णांकAddr == 0x83 &&
		   ftdi->bulk_out_endpoपूर्णांकAddr == 0x04) अणु
		ftdi->class = शून्य;
		dev_info(&ftdi->udev->dev, "USB FDTI=%p ELAN interface %d now activated\n",
			 ftdi, अगरace_desc->desc.bInterfaceNumber);
		INIT_DELAYED_WORK(&ftdi->status_work, ftdi_elan_status_work);
		INIT_DELAYED_WORK(&ftdi->command_work, ftdi_elan_command_work);
		INIT_DELAYED_WORK(&ftdi->respond_work, ftdi_elan_respond_work);
		ftdi_status_queue_work(ftdi, msecs_to_jअगरfies(3 *1000));
		वापस 0;
	पूर्ण अन्यथा अणु
		dev_err(&ftdi->udev->dev,
			"Could not find ELAN's U132 device\n");
		retval = -ENODEV;
		जाओ error;
	पूर्ण
error:अगर (ftdi) अणु
		ftdi_elan_put_kref(ftdi);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम ftdi_elan_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_ftdi *ftdi = usb_get_पूर्णांकfdata(पूर्णांकerface);
	ftdi->disconnected += 1;
	अगर (ftdi->class) अणु
		पूर्णांक minor = पूर्णांकerface->minor;
		काष्ठा usb_class_driver *class = ftdi->class;
		usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
		usb_deरेजिस्टर_dev(पूर्णांकerface, class);
		dev_info(&ftdi->udev->dev, "USB FTDI U132 jtag interface on minor %d now disconnected\n",
			 minor);
	पूर्ण अन्यथा अणु
		ftdi_status_cancel_work(ftdi);
		ftdi_command_cancel_work(ftdi);
		ftdi_response_cancel_work(ftdi);
		ftdi_elan_abanकरोn_completions(ftdi);
		ftdi_elan_abanकरोn_tarमाला_लो(ftdi);
		अगर (ftdi->रेजिस्टरed) अणु
			platक्रमm_device_unरेजिस्टर(&ftdi->platक्रमm_dev);
			ftdi->synchronized = 0;
			ftdi->क्रमागतerated = 0;
			ftdi->initialized = 0;
			ftdi->रेजिस्टरed = 0;
		पूर्ण
		ftdi->disconnected += 1;
		usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
		dev_info(&ftdi->udev->dev, "USB FTDI U132 host controller interface now disconnected\n");
	पूर्ण
	ftdi_elan_put_kref(ftdi);
पूर्ण

अटल काष्ठा usb_driver ftdi_elan_driver = अणु
	.name = "ftdi-elan",
	.probe = ftdi_elan_probe,
	.disconnect = ftdi_elan_disconnect,
	.id_table = ftdi_elan_table,
पूर्ण;
अटल पूर्णांक __init ftdi_elan_init(व्योम)
अणु
	पूर्णांक result;
	pr_info("driver %s\n", ftdi_elan_driver.name);
	mutex_init(&ftdi_module_lock);
	INIT_LIST_HEAD(&ftdi_अटल_list);
	result = usb_रेजिस्टर(&ftdi_elan_driver);
	अगर (result) अणु
		pr_err("usb_register failed. Error number %d\n", result);
	पूर्ण
	वापस result;

पूर्ण

अटल व्योम __निकास ftdi_elan_निकास(व्योम)
अणु
	काष्ठा usb_ftdi *ftdi;
	काष्ठा usb_ftdi *temp;
	usb_deरेजिस्टर(&ftdi_elan_driver);
	pr_info("ftdi_u132 driver deregistered\n");
	list_क्रम_each_entry_safe(ftdi, temp, &ftdi_अटल_list, ftdi_list) अणु
		ftdi_status_cancel_work(ftdi);
		ftdi_command_cancel_work(ftdi);
		ftdi_response_cancel_work(ftdi);
	पूर्ण
पूर्ण


module_init(ftdi_elan_init);
module_निकास(ftdi_elan_निकास);
