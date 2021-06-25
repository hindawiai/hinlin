<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/******************************************************************************
 *  xusbaपंचांग.c -	dumb usbaपंचांग-based driver क्रम modems initialized in userspace
 *
 *  Copyright (C) 2005 Duncan Sands, Roman Kagan (rkagan % mail ! ru)
 ******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>		/* क्रम eth_अक्रमom_addr() */

#समावेश "usbatm.h"


#घोषणा XUSBATM_DRIVERS_MAX	8

#घोषणा XUSBATM_PARM(name, type, parmtype, desc) \
	अटल type name[XUSBATM_DRIVERS_MAX]; \
	अटल अचिन्हित पूर्णांक num_##name; \
	module_param_array(name, parmtype, &num_##name, 0444); \
	MODULE_PARM_DESC(name, desc)

XUSBATM_PARM(venकरोr, अचिन्हित लघु, uलघु, "USB device vendor");
XUSBATM_PARM(product, अचिन्हित लघु, uलघु, "USB device product");

XUSBATM_PARM(rx_endpoपूर्णांक, अचिन्हित अक्षर, byte, "rx endpoint number");
XUSBATM_PARM(tx_endpoपूर्णांक, अचिन्हित अक्षर, byte, "tx endpoint number");
XUSBATM_PARM(rx_padding, अचिन्हित अक्षर, byte, "rx padding (default 0)");
XUSBATM_PARM(tx_padding, अचिन्हित अक्षर, byte, "tx padding (default 0)");
XUSBATM_PARM(rx_altsetting, अचिन्हित अक्षर, byte, "rx altsetting (default 0)");
XUSBATM_PARM(tx_altsetting, अचिन्हित अक्षर, byte, "rx altsetting (default 0)");

अटल स्थिर अक्षर xusbaपंचांग_driver_name[] = "xusbatm";

अटल काष्ठा usbaपंचांग_driver xusbaपंचांग_drivers[XUSBATM_DRIVERS_MAX];
अटल काष्ठा usb_device_id xusbaपंचांग_usb_ids[XUSBATM_DRIVERS_MAX + 1];
अटल काष्ठा usb_driver xusbaपंचांग_usb_driver;

अटल काष्ठा usb_पूर्णांकerface *xusbaपंचांग_find_पूर्णांकf(काष्ठा usb_device *usb_dev, पूर्णांक altsetting, u8 ep)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक i, j;

	क्रम (i = 0; i < usb_dev->actconfig->desc.bNumInterfaces; i++)
		अगर ((पूर्णांकf = usb_dev->actconfig->पूर्णांकerface[i]) && (alt = usb_altnum_to_altsetting(पूर्णांकf, altsetting)))
			क्रम (j = 0; j < alt->desc.bNumEndpoपूर्णांकs; j++)
				अगर (alt->endpoपूर्णांक[j].desc.bEndpoपूर्णांकAddress == ep)
					वापस पूर्णांकf;
	वापस शून्य;
पूर्ण

अटल पूर्णांक xusbaपंचांग_capture_पूर्णांकf(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_device *usb_dev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक altsetting, पूर्णांक claim)
अणु
	पूर्णांक अगरnum = पूर्णांकf->altsetting->desc.bInterfaceNumber;
	पूर्णांक ret;

	अगर (claim && (ret = usb_driver_claim_पूर्णांकerface(&xusbaपंचांग_usb_driver, पूर्णांकf, usbaपंचांग))) अणु
		usb_err(usbaपंचांग, "%s: failed to claim interface %2d (%d)!\n", __func__, अगरnum, ret);
		वापस ret;
	पूर्ण
	ret = usb_set_पूर्णांकerface(usb_dev, अगरnum, altsetting);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "%s: altsetting %2d for interface %2d failed (%d)!\n", __func__, altsetting, अगरnum, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम xusbaपंचांग_release_पूर्णांकf(काष्ठा usb_device *usb_dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक claimed)
अणु
	अगर (claimed) अणु
		usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
		usb_driver_release_पूर्णांकerface(&xusbaपंचांग_usb_driver, पूर्णांकf);
	पूर्ण
पूर्ण

अटल पूर्णांक xusbaपंचांग_bind(काष्ठा usbaपंचांग_data *usbaपंचांग,
			काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक drv_ix = id - xusbaपंचांग_usb_ids;
	पूर्णांक rx_alt = rx_altsetting[drv_ix];
	पूर्णांक tx_alt = tx_altsetting[drv_ix];
	काष्ठा usb_पूर्णांकerface *rx_पूर्णांकf = xusbaपंचांग_find_पूर्णांकf(usb_dev, rx_alt, rx_endpoपूर्णांक[drv_ix]);
	काष्ठा usb_पूर्णांकerface *tx_पूर्णांकf = xusbaपंचांग_find_पूर्णांकf(usb_dev, tx_alt, tx_endpoपूर्णांक[drv_ix]);
	पूर्णांक ret;

	usb_dbg(usbaपंचांग, "%s: binding driver %d: vendor %04x product %04x"
		" rx: ep %02x padd %d alt %2d tx: ep %02x padd %d alt %2d\n",
		__func__, drv_ix, venकरोr[drv_ix], product[drv_ix],
		rx_endpoपूर्णांक[drv_ix], rx_padding[drv_ix], rx_alt,
		tx_endpoपूर्णांक[drv_ix], tx_padding[drv_ix], tx_alt);

	अगर (!rx_पूर्णांकf || !tx_पूर्णांकf) अणु
		अगर (!rx_पूर्णांकf)
			usb_dbg(usbaपंचांग, "%s: no interface contains endpoint %02x in altsetting %2d\n",
				__func__, rx_endpoपूर्णांक[drv_ix], rx_alt);
		अगर (!tx_पूर्णांकf)
			usb_dbg(usbaपंचांग, "%s: no interface contains endpoint %02x in altsetting %2d\n",
				__func__, tx_endpoपूर्णांक[drv_ix], tx_alt);
		वापस -ENODEV;
	पूर्ण

	अगर ((rx_पूर्णांकf != पूर्णांकf) && (tx_पूर्णांकf != पूर्णांकf))
		वापस -ENODEV;

	अगर ((rx_पूर्णांकf == tx_पूर्णांकf) && (rx_alt != tx_alt)) अणु
		usb_err(usbaपंचांग, "%s: altsettings clash on interface %2d (%2d vs %2d)!\n", __func__,
				rx_पूर्णांकf->altsetting->desc.bInterfaceNumber, rx_alt, tx_alt);
		वापस -EINVAL;
	पूर्ण

	usb_dbg(usbaपंचांग, "%s: rx If#=%2d; tx If#=%2d\n", __func__,
			rx_पूर्णांकf->altsetting->desc.bInterfaceNumber,
			tx_पूर्णांकf->altsetting->desc.bInterfaceNumber);

	ret = xusbaपंचांग_capture_पूर्णांकf(usbaपंचांग, usb_dev, rx_पूर्णांकf, rx_alt, rx_पूर्णांकf != पूर्णांकf);
	अगर (ret)
		वापस ret;

	अगर ((tx_पूर्णांकf != rx_पूर्णांकf) && (ret = xusbaपंचांग_capture_पूर्णांकf(usbaपंचांग, usb_dev, tx_पूर्णांकf, tx_alt, tx_पूर्णांकf != पूर्णांकf))) अणु
		xusbaपंचांग_release_पूर्णांकf(usb_dev, rx_पूर्णांकf, rx_पूर्णांकf != पूर्णांकf);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xusbaपंचांग_unbind(काष्ठा usbaपंचांग_data *usbaपंचांग,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक i;

	usb_dbg(usbaपंचांग, "%s entered\n", __func__);

	क्रम (i = 0; i < usb_dev->actconfig->desc.bNumInterfaces; i++) अणु
		काष्ठा usb_पूर्णांकerface *cur_पूर्णांकf = usb_dev->actconfig->पूर्णांकerface[i];

		अगर (cur_पूर्णांकf && (usb_get_पूर्णांकfdata(cur_पूर्णांकf) == usbaपंचांग)) अणु
			usb_set_पूर्णांकfdata(cur_पूर्णांकf, शून्य);
			usb_driver_release_पूर्णांकerface(&xusbaपंचांग_usb_driver, cur_पूर्णांकf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xusbaपंचांग_aपंचांग_start(काष्ठा usbaपंचांग_data *usbaपंचांग,
			     काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);

	/* use अक्रमom MAC as we've no way to get it from the device */
	eth_अक्रमom_addr(aपंचांग_dev->esi);

	वापस 0;
पूर्ण


अटल पूर्णांक xusbaपंचांग_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	वापस usbaपंचांग_usb_probe(पूर्णांकf, id,
				xusbaपंचांग_drivers + (id - xusbaपंचांग_usb_ids));
पूर्ण

अटल काष्ठा usb_driver xusbaपंचांग_usb_driver = अणु
	.name		= xusbaपंचांग_driver_name,
	.probe		= xusbaपंचांग_usb_probe,
	.disconnect	= usbaपंचांग_usb_disconnect,
	.id_table	= xusbaपंचांग_usb_ids
पूर्ण;

अटल पूर्णांक __init xusbaपंचांग_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!num_venकरोr ||
	    num_venकरोr != num_product ||
	    num_venकरोr != num_rx_endpoपूर्णांक ||
	    num_venकरोr != num_tx_endpoपूर्णांक) अणु
		pr_warn("xusbatm: malformed module parameters\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_venकरोr; i++) अणु
		rx_endpoपूर्णांक[i] |= USB_सूची_IN;
		tx_endpoपूर्णांक[i] &= USB_ENDPOINT_NUMBER_MASK;

		xusbaपंचांग_usb_ids[i].match_flags	= USB_DEVICE_ID_MATCH_DEVICE;
		xusbaपंचांग_usb_ids[i].idVenकरोr	= venकरोr[i];
		xusbaपंचांग_usb_ids[i].idProduct	= product[i];

		xusbaपंचांग_drivers[i].driver_name	= xusbaपंचांग_driver_name;
		xusbaपंचांग_drivers[i].bind		= xusbaपंचांग_bind;
		xusbaपंचांग_drivers[i].unbind	= xusbaपंचांग_unbind;
		xusbaपंचांग_drivers[i].aपंचांग_start	= xusbaपंचांग_aपंचांग_start;
		xusbaपंचांग_drivers[i].bulk_in	= rx_endpoपूर्णांक[i];
		xusbaपंचांग_drivers[i].bulk_out	= tx_endpoपूर्णांक[i];
		xusbaपंचांग_drivers[i].rx_padding	= rx_padding[i];
		xusbaपंचांग_drivers[i].tx_padding	= tx_padding[i];
	पूर्ण

	वापस usb_रेजिस्टर(&xusbaपंचांग_usb_driver);
पूर्ण
module_init(xusbaपंचांग_init);

अटल व्योम __निकास xusbaपंचांग_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&xusbaपंचांग_usb_driver);
पूर्ण
module_निकास(xusbaपंचांग_निकास);

MODULE_AUTHOR("Roman Kagan, Duncan Sands");
MODULE_DESCRIPTION("Driver for USB ADSL modems initialized in userspace");
MODULE_LICENSE("GPL");
