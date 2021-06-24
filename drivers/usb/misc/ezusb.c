<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EZ-USB specअगरic functions used by some of the USB to Serial drivers.
 *
 * Copyright (C) 1999 - 2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश <linux/usb/ezusb.h>

काष्ठा ezusb_fx_type अणु
	/* EZ-USB Control and Status Register.  Bit 0 controls 8051 reset */
	अचिन्हित लघु cpucs_reg;
	अचिन्हित लघु max_पूर्णांकernal_adress;
पूर्ण;

अटल स्थिर काष्ठा ezusb_fx_type ezusb_fx1 = अणु
	.cpucs_reg = 0x7F92,
	.max_पूर्णांकernal_adress = 0x1B3F,
पूर्ण;

/* Commands क्रम writing to memory */
#घोषणा WRITE_INT_RAM 0xA0
#घोषणा WRITE_EXT_RAM 0xA3

अटल पूर्णांक ezusb_ग_लिखोmemory(काष्ठा usb_device *dev, पूर्णांक address,
				अचिन्हित अक्षर *data, पूर्णांक length, __u8 request)
अणु
	अगर (!dev)
		वापस -ENODEV;

	वापस usb_control_msg_send(dev, 0, request,
				 USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				 address, 0, data, length, 3000, GFP_KERNEL);
पूर्ण

अटल पूर्णांक ezusb_set_reset(काष्ठा usb_device *dev, अचिन्हित लघु cpucs_reg,
			   अचिन्हित अक्षर reset_bit)
अणु
	पूर्णांक response = ezusb_ग_लिखोmemory(dev, cpucs_reg, &reset_bit, 1, WRITE_INT_RAM);
	अगर (response < 0)
		dev_err(&dev->dev, "%s-%d failed: %d\n",
						__func__, reset_bit, response);
	वापस response;
पूर्ण

पूर्णांक ezusb_fx1_set_reset(काष्ठा usb_device *dev, अचिन्हित अक्षर reset_bit)
अणु
	वापस ezusb_set_reset(dev, ezusb_fx1.cpucs_reg, reset_bit);
पूर्ण
EXPORT_SYMBOL_GPL(ezusb_fx1_set_reset);

अटल पूर्णांक ezusb_ihex_firmware_करोwnload(काष्ठा usb_device *dev,
					काष्ठा ezusb_fx_type fx,
					स्थिर अक्षर *firmware_path)
अणु
	पूर्णांक ret = -ENOENT;
	स्थिर काष्ठा firmware *firmware = शून्य;
	स्थिर काष्ठा ihex_binrec *record;

	अगर (request_ihex_firmware(&firmware, firmware_path,
				  &dev->dev)) अणु
		dev_err(&dev->dev,
			"%s - request \"%s\" failed\n",
			__func__, firmware_path);
		जाओ out;
	पूर्ण

	ret = ezusb_set_reset(dev, fx.cpucs_reg, 0);
	अगर (ret < 0)
		जाओ out;

	record = (स्थिर काष्ठा ihex_binrec *)firmware->data;
	क्रम (; record; record = ihex_next_binrec(record)) अणु
		अगर (be32_to_cpu(record->addr) > fx.max_पूर्णांकernal_adress) अणु
			ret = ezusb_ग_लिखोmemory(dev, be32_to_cpu(record->addr),
						(अचिन्हित अक्षर *)record->data,
						be16_to_cpu(record->len), WRITE_EXT_RAM);
			अगर (ret < 0) अणु
				dev_err(&dev->dev, "%s - ezusb_writememory "
					"failed writing internal memory "
					"(%d %04X %p %d)\n", __func__, ret,
					be32_to_cpu(record->addr), record->data,
					be16_to_cpu(record->len));
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = ezusb_set_reset(dev, fx.cpucs_reg, 1);
	अगर (ret < 0)
		जाओ out;
	record = (स्थिर काष्ठा ihex_binrec *)firmware->data;
	क्रम (; record; record = ihex_next_binrec(record)) अणु
		अगर (be32_to_cpu(record->addr) <= fx.max_पूर्णांकernal_adress) अणु
			ret = ezusb_ग_लिखोmemory(dev, be32_to_cpu(record->addr),
						(अचिन्हित अक्षर *)record->data,
						be16_to_cpu(record->len), WRITE_INT_RAM);
			अगर (ret < 0) अणु
				dev_err(&dev->dev, "%s - ezusb_writememory "
					"failed writing external memory "
					"(%d %04X %p %d)\n", __func__, ret,
					be32_to_cpu(record->addr), record->data,
					be16_to_cpu(record->len));
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = ezusb_set_reset(dev, fx.cpucs_reg, 0);
out:
	release_firmware(firmware);
	वापस ret;
पूर्ण

पूर्णांक ezusb_fx1_ihex_firmware_करोwnload(काष्ठा usb_device *dev,
				     स्थिर अक्षर *firmware_path)
अणु
	वापस ezusb_ihex_firmware_करोwnload(dev, ezusb_fx1, firmware_path);
पूर्ण
EXPORT_SYMBOL_GPL(ezusb_fx1_ihex_firmware_करोwnload);

#अगर 0
/*
 * Once someone one needs these fx2 functions, uncomment them
 * and add them to ezusb.h and all should be good.
 */
अटल काष्ठा ezusb_fx_type ezusb_fx2 = अणु
	.cpucs_reg = 0xE600,
	.max_पूर्णांकernal_adress = 0x3FFF,
पूर्ण;

पूर्णांक ezusb_fx2_set_reset(काष्ठा usb_device *dev, अचिन्हित अक्षर reset_bit)
अणु
	वापस ezusb_set_reset(dev, ezusb_fx2.cpucs_reg, reset_bit);
पूर्ण
EXPORT_SYMBOL_GPL(ezusb_fx2_set_reset);

पूर्णांक ezusb_fx2_ihex_firmware_करोwnload(काष्ठा usb_device *dev,
				     स्थिर अक्षर *firmware_path)
अणु
	वापस ezusb_ihex_firmware_करोwnload(dev, ezusb_fx2, firmware_path);
पूर्ण
EXPORT_SYMBOL_GPL(ezusb_fx2_ihex_firmware_करोwnload);
#पूर्ण_अगर

MODULE_LICENSE("GPL");
