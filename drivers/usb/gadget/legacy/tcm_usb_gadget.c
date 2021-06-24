<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Target based USB-Gadget
 *
 * UAS protocol handling, target callbacks, configfs handling,
 * BBB (USB Mass Storage Class Bulk-Only (BBB) and Transport protocol handling.
 *
 * Author: Sebastian Andrzej Siewior <bigeasy at linutronix करोt de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/storage.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "u_tcm.h"

USB_GADGET_COMPOSITE_OPTIONS();

#घोषणा UAS_VENDOR_ID	0x0525	/* NetChip */
#घोषणा UAS_PRODUCT_ID	0xa4a5	/* Linux-USB File-backed Storage Gadget */

अटल काष्ठा usb_device_descriptor usbg_device_desc = अणु
	.bLength =		माप(usbg_device_desc),
	.bDescriptorType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.idVenकरोr =		cpu_to_le16(UAS_VENDOR_ID),
	.idProduct =		cpu_to_le16(UAS_PRODUCT_ID),
	.bNumConfigurations =   1,
पूर्ण;

#घोषणा USB_G_STR_CONFIG USB_GADGET_FIRST_AVAIL_IDX

अटल काष्ठा usb_string	usbg_us_strings[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s	= "Target Manufacturer",
	[USB_GADGET_PRODUCT_IDX].s	= "Target Product",
	[USB_GADGET_SERIAL_IDX].s	= "000000000001",
	[USB_G_STR_CONFIG].s		= "default config",
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा usb_gadget_strings usbg_stringtab = अणु
	.language = 0x0409,
	.strings = usbg_us_strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *usbg_strings[] = अणु
	&usbg_stringtab,
	शून्य,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_tcm;
अटल काष्ठा usb_function *f_tcm;

अटल पूर्णांक guas_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (!IS_ERR_OR_शून्य(f_tcm))
		usb_put_function(f_tcm);

	वापस 0;
पूर्ण

अटल पूर्णांक tcm_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status;

	f_tcm = usb_get_function(fi_tcm);
	अगर (IS_ERR(f_tcm))
		वापस PTR_ERR(f_tcm);

	status = usb_add_function(c, f_tcm);
	अगर (status < 0) अणु
		usb_put_function(f_tcm);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usb_configuration usbg_config_driver = अणु
	.label                  = "Linux Target",
	.bConfigurationValue    = 1,
	.bmAttributes           = USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

अटल पूर्णांक usbg_attach(काष्ठा usb_function_instance *f);
अटल व्योम usbg_detach(काष्ठा usb_function_instance *f);

अटल पूर्णांक usb_target_bind(काष्ठा usb_composite_dev *cdev)
अणु
	पूर्णांक ret;

	ret = usb_string_ids_tab(cdev, usbg_us_strings);
	अगर (ret)
		वापस ret;

	usbg_device_desc.iManufacturer =
		usbg_us_strings[USB_GADGET_MANUFACTURER_IDX].id;
	usbg_device_desc.iProduct = usbg_us_strings[USB_GADGET_PRODUCT_IDX].id;
	usbg_device_desc.iSerialNumber =
		usbg_us_strings[USB_GADGET_SERIAL_IDX].id;
	usbg_config_driver.iConfiguration =
		usbg_us_strings[USB_G_STR_CONFIG].id;

	ret = usb_add_config(cdev, &usbg_config_driver, tcm_करो_config);
	अगर (ret)
		वापस ret;
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver usbg_driver = अणु
	.name           = "g_target",
	.dev            = &usbg_device_desc,
	.strings        = usbg_strings,
	.max_speed      = USB_SPEED_SUPER,
	.bind		= usb_target_bind,
	.unbind         = guas_unbind,
पूर्ण;

अटल पूर्णांक usbg_attach(काष्ठा usb_function_instance *f)
अणु
	वापस usb_composite_probe(&usbg_driver);
पूर्ण

अटल व्योम usbg_detach(काष्ठा usb_function_instance *f)
अणु
	usb_composite_unरेजिस्टर(&usbg_driver);
पूर्ण

अटल पूर्णांक __init usb_target_gadget_init(व्योम)
अणु
	काष्ठा f_tcm_opts *tcm_opts;

	fi_tcm = usb_get_function_instance("tcm");
	अगर (IS_ERR(fi_tcm))
		वापस PTR_ERR(fi_tcm);

	tcm_opts = container_of(fi_tcm, काष्ठा f_tcm_opts, func_inst);
	mutex_lock(&tcm_opts->dep_lock);
	tcm_opts->tcm_रेजिस्टर_callback = usbg_attach;
	tcm_opts->tcm_unरेजिस्टर_callback = usbg_detach;
	tcm_opts->dependent = THIS_MODULE;
	tcm_opts->can_attach = true;
	tcm_opts->has_dep = true;
	mutex_unlock(&tcm_opts->dep_lock);

	fi_tcm->set_inst_name(fi_tcm, "tcm-legacy");

	वापस 0;
पूर्ण
module_init(usb_target_gadget_init);

अटल व्योम __निकास usb_target_gadget_निकास(व्योम)
अणु
	अगर (!IS_ERR_OR_शून्य(fi_tcm))
		usb_put_function_instance(fi_tcm);

पूर्ण
module_निकास(usb_target_gadget_निकास);

MODULE_AUTHOR("Sebastian Andrzej Siewior <bigeasy@linutronix.de>");
MODULE_DESCRIPTION("usb-gadget fabric");
MODULE_LICENSE("GPL v2");
