<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    hexium_orion.c - v4l2 driver क्रम the Hexium Orion frame grabber cards

    Visit http://www.mihu.de/linux/saa7146/ and follow the link
    to "hexium" क्रम further details about this card.

    Copyright (C) 2003 Michael Hunold <michael@mihu.de>

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DEBUG_VARIABLE debug

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "debug verbosity");

/* global variables */
अटल पूर्णांक hexium_num;

#घोषणा HEXIUM_HV_PCI6_ORION		1
#घोषणा HEXIUM_ORION_1SVHS_3BNC		2
#घोषणा HEXIUM_ORION_4BNC		3

#घोषणा HEXIUM_INPUTS	9
अटल काष्ठा v4l2_input hexium_inमाला_दो[HEXIUM_INPUTS] = अणु
	अणु 0, "CVBS 1",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 1, "CVBS 2",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 2, "CVBS 3",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 3, "CVBS 4",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 4, "CVBS 5",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 5, "CVBS 6",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 6, "Y/C 1",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 7, "Y/C 2",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 8, "Y/C 3",	V4L2_INPUT_TYPE_CAMERA,	0, 0, V4L2_STD_ALL, 0, V4L2_IN_CAP_STD पूर्ण,
पूर्ण;

#घोषणा HEXIUM_AUDIOS	0

काष्ठा hexium_data
अणु
	s8 adr;
	u8 byte;
पूर्ण;

काष्ठा hexium
अणु
	पूर्णांक type;
	काष्ठा video_device	video_dev;
	काष्ठा i2c_adapter	i2c_adapter;

	पूर्णांक cur_input;	/* current input */
पूर्ण;

/* Philips SAA7110 decoder शेष रेजिस्टरs */
अटल u8 hexium_saa7110[53]=अणु
/*00*/ 0x4C,0x3C,0x0D,0xEF,0xBD,0xF0,0x00,0x00,
/*08*/ 0xF8,0xF8,0x60,0x60,0x40,0x86,0x18,0x90,
/*10*/ 0x00,0x2C,0x40,0x46,0x42,0x1A,0xFF,0xDA,
/*18*/ 0xF0,0x8B,0x00,0x00,0x00,0x00,0x00,0x00,
/*20*/ 0xD9,0x17,0x40,0x41,0x80,0x41,0x80,0x4F,
/*28*/ 0xFE,0x01,0x0F,0x0F,0x03,0x01,0x81,0x03,
/*30*/ 0x44,0x75,0x01,0x8C,0x03
पूर्ण;

अटल काष्ठा अणु
	काष्ठा hexium_data data[8];
पूर्ण hexium_input_select[] = अणु
अणु
	अणु /* cvbs 1 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0xD9 पूर्ण,
		अणु 0x21, 0x17 पूर्ण, // 0x16,
		अणु 0x22, 0x40 पूर्ण,
		अणु 0x2C, 0x03 पूर्ण,
		अणु 0x30, 0x44 पूर्ण,
		अणु 0x31, 0x75 पूर्ण, // ??
		अणु 0x21, 0x16 पूर्ण, // 0x03,
	पूर्ण
पूर्ण, अणु
	अणु /* cvbs 2 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0x78 पूर्ण,
		अणु 0x21, 0x07 पूर्ण, // 0x03,
		अणु 0x22, 0xD2 पूर्ण,
		अणु 0x2C, 0x83 पूर्ण,
		अणु 0x30, 0x60 पूर्ण,
		अणु 0x31, 0xB5 पूर्ण, // ?
		अणु 0x21, 0x03 पूर्ण,
	पूर्ण
पूर्ण, अणु
	अणु /* cvbs 3 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0xBA पूर्ण,
		अणु 0x21, 0x07 पूर्ण, // 0x05,
		अणु 0x22, 0x91 पूर्ण,
		अणु 0x2C, 0x03 पूर्ण,
		अणु 0x30, 0x60 पूर्ण,
		अणु 0x31, 0xB5 पूर्ण, // ??
		अणु 0x21, 0x05 पूर्ण, // 0x03,
	पूर्ण
पूर्ण, अणु
	अणु /* cvbs 4 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0xD8 पूर्ण,
		अणु 0x21, 0x17 पूर्ण, // 0x16,
		अणु 0x22, 0x40 पूर्ण,
		अणु 0x2C, 0x03 पूर्ण,
		अणु 0x30, 0x44 पूर्ण,
		अणु 0x31, 0x75 पूर्ण, // ??
		अणु 0x21, 0x16 पूर्ण, // 0x03,
	पूर्ण
पूर्ण, अणु
	अणु /* cvbs 5 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0xB8 पूर्ण,
		अणु 0x21, 0x07 पूर्ण, // 0x05,
		अणु 0x22, 0x91 पूर्ण,
		अणु 0x2C, 0x03 पूर्ण,
		अणु 0x30, 0x60 पूर्ण,
		अणु 0x31, 0xB5 पूर्ण, // ??
		अणु 0x21, 0x05 पूर्ण, // 0x03,
	पूर्ण
पूर्ण, अणु
	अणु /* cvbs 6 */
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x20, 0x7C पूर्ण,
		अणु 0x21, 0x07 पूर्ण, // 0x03
		अणु 0x22, 0xD2 पूर्ण,
		अणु 0x2C, 0x83 पूर्ण,
		अणु 0x30, 0x60 पूर्ण,
		अणु 0x31, 0xB5 पूर्ण, // ??
		अणु 0x21, 0x03 पूर्ण,
	पूर्ण
पूर्ण, अणु
	अणु /* y/c 1 */
		अणु 0x06, 0x80 पूर्ण,
		अणु 0x20, 0x59 पूर्ण,
		अणु 0x21, 0x17 पूर्ण,
		अणु 0x22, 0x42 पूर्ण,
		अणु 0x2C, 0xA3 पूर्ण,
		अणु 0x30, 0x44 पूर्ण,
		अणु 0x31, 0x75 पूर्ण,
		अणु 0x21, 0x12 पूर्ण,
	पूर्ण
पूर्ण, अणु
	अणु /* y/c 2 */
		अणु 0x06, 0x80 पूर्ण,
		अणु 0x20, 0x9A पूर्ण,
		अणु 0x21, 0x17 पूर्ण,
		अणु 0x22, 0xB1 पूर्ण,
		अणु 0x2C, 0x13 पूर्ण,
		अणु 0x30, 0x60 पूर्ण,
		अणु 0x31, 0xB5 पूर्ण,
		अणु 0x21, 0x14 पूर्ण,
	पूर्ण
पूर्ण, अणु
	अणु /* y/c 3 */
		अणु 0x06, 0x80 पूर्ण,
		अणु 0x20, 0x3C पूर्ण,
		अणु 0x21, 0x27 पूर्ण,
		अणु 0x22, 0xC1 पूर्ण,
		अणु 0x2C, 0x23 पूर्ण,
		अणु 0x30, 0x44 पूर्ण,
		अणु 0x31, 0x75 पूर्ण,
		अणु 0x21, 0x21 पूर्ण,
	पूर्ण
पूर्ण
पूर्ण;

अटल काष्ठा saa7146_standard hexium_standards[] = अणु
	अणु
		.name	= "PAL",	.id	= V4L2_STD_PAL,
		.v_offset	= 16,	.v_field	= 288,
		.h_offset	= 1,	.h_pixels	= 680,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id	= V4L2_STD_NTSC,
		.v_offset	= 16,	.v_field	= 240,
		.h_offset	= 1,	.h_pixels	= 640,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण, अणु
		.name	= "SECAM",	.id	= V4L2_STD_SECAM,
		.v_offset	= 16,	.v_field	= 288,
		.h_offset	= 1,	.h_pixels	= 720,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण
पूर्ण;

/* this is only called क्रम old HV-PCI6/Orion cards
   without eeprom */
अटल पूर्णांक hexium_probe(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा hexium *hexium = शून्य;
	जोड़ i2c_smbus_data data;
	पूर्णांक err = 0;

	DEB_EE("\n");

	/* there are no hexium orion cards with revision 0 saa7146s */
	अगर (0 == dev->revision) अणु
		वापस -EFAULT;
	पूर्ण

	hexium = kzalloc(माप(*hexium), GFP_KERNEL);
	अगर (!hexium)
		वापस -ENOMEM;

	/* enable i2c-port pins */
	saa7146_ग_लिखो(dev, MC1, (MASK_08 | MASK_24 | MASK_10 | MASK_26));

	saa7146_ग_लिखो(dev, DD1_INIT, 0x01000100);
	saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
	saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	strscpy(hexium->i2c_adapter.name, "hexium orion",
		माप(hexium->i2c_adapter.name));
	saa7146_i2c_adapter_prepare(dev, &hexium->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	अगर (i2c_add_adapter(&hexium->i2c_adapter) < 0) अणु
		DEB_S("cannot register i2c-device. skipping.\n");
		kमुक्त(hexium);
		वापस -EFAULT;
	पूर्ण

	/* set SAA7110 control GPIO 0 */
	saa7146_setgpio(dev, 0, SAA7146_GPIO_OUTHI);
	/*  set HWControl GPIO number 2 */
	saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	mdelay(10);

	/* detect newer Hexium Orion cards by subप्रणाली ids */
	अगर (0x17c8 == dev->pci->subप्रणाली_venकरोr && 0x0101 == dev->pci->subप्रणाली_device) अणु
		pr_info("device is a Hexium Orion w/ 1 SVHS + 3 BNC inputs\n");
		/* we store the poपूर्णांकer in our निजी data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_ORION_1SVHS_3BNC;
		वापस 0;
	पूर्ण

	अगर (0x17c8 == dev->pci->subप्रणाली_venकरोr && 0x2101 == dev->pci->subप्रणाली_device) अणु
		pr_info("device is a Hexium Orion w/ 4 BNC inputs\n");
		/* we store the poपूर्णांकer in our निजी data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_ORION_4BNC;
		वापस 0;
	पूर्ण

	/* check अगर this is an old hexium Orion card by looking at
	   a saa7110 at address 0x4e */
	err = i2c_smbus_xfer(&hexium->i2c_adapter, 0x4e, 0, I2C_SMBUS_READ,
			     0x00, I2C_SMBUS_BYTE_DATA, &data);
	अगर (err == 0) अणु
		pr_info("device is a Hexium HV-PCI6/Orion (old)\n");
		/* we store the poपूर्णांकer in our निजी data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_HV_PCI6_ORION;
		वापस 0;
	पूर्ण

	i2c_del_adapter(&hexium->i2c_adapter);
	kमुक्त(hexium);
	वापस -EFAULT;
पूर्ण

/* bring hardware to a sane state. this has to be करोne, just in हाल someone
   wants to capture from this device beक्रमe it has been properly initialized.
   the capture engine would badly fail, because no valid संकेत arrives on the
   saa7146, thus leading to समयouts and stuff. */
अटल पूर्णांक hexium_init_करोne(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;
	जोड़ i2c_smbus_data data;
	पूर्णांक i = 0;

	DEB_D("hexium_init_done called\n");

	/* initialize the helper ics to useful values */
	क्रम (i = 0; i < माप(hexium_saa7110); i++) अणु
		data.byte = hexium_saa7110[i];
		अगर (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x4e, 0, I2C_SMBUS_WRITE, i, I2C_SMBUS_BYTE_DATA, &data)) अणु
			pr_err("failed for address 0x%02x\n", i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hexium_set_input(काष्ठा hexium *hexium, पूर्णांक input)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक i = 0;

	DEB_D("\n");

	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक adr = hexium_input_select[input].data[i].adr;
		data.byte = hexium_input_select[input].data[i].byte;
		अगर (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x4e, 0, I2C_SMBUS_WRITE, adr, I2C_SMBUS_BYTE_DATA, &data)) अणु
			वापस -1;
		पूर्ण
		pr_debug("%d: 0x%02x => 0x%02x\n", input, adr, data.byte);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	DEB_EE("VIDIOC_ENUMINPUT %d\n", i->index);

	अगर (i->index >= HEXIUM_INPUTS)
		वापस -EINVAL;

	स_नकल(i, &hexium_inमाला_दो[i->index], माप(काष्ठा v4l2_input));

	DEB_D("v4l2_ioctl: VIDIOC_ENUMINPUT %d\n", i->index);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;

	*input = hexium->cur_input;

	DEB_D("VIDIOC_G_INPUT: %d\n", *input);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;

	अगर (input >= HEXIUM_INPUTS)
		वापस -EINVAL;

	hexium->cur_input = input;
	hexium_set_input(hexium, input);

	वापस 0;
पूर्ण

अटल काष्ठा saa7146_ext_vv vv_data;

/* this function only माला_लो called when the probing was successful */
अटल पूर्णांक hexium_attach(काष्ठा saa7146_dev *dev, काष्ठा saa7146_pci_extension_data *info)
अणु
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;

	DEB_EE("\n");

	saa7146_vv_init(dev, &vv_data);
	vv_data.vid_ops.vidioc_क्रमागत_input = vidioc_क्रमागत_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	अगर (0 != saa7146_रेजिस्टर_device(&hexium->video_dev, dev, "hexium orion", VFL_TYPE_VIDEO)) अणु
		pr_err("cannot register capture v4l2 device. skipping.\n");
		वापस -1;
	पूर्ण

	pr_err("found 'hexium orion' frame grabber-%d\n", hexium_num);
	hexium_num++;

	/* the rest */
	hexium->cur_input = 0;
	hexium_init_करोne(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक hexium_detach(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;

	DEB_EE("dev:%p\n", dev);

	saa7146_unरेजिस्टर_device(&hexium->video_dev, dev);
	saa7146_vv_release(dev);

	hexium_num--;

	i2c_del_adapter(&hexium->i2c_adapter);
	kमुक्त(hexium);
	वापस 0;
पूर्ण

अटल पूर्णांक std_callback(काष्ठा saa7146_dev *dev, काष्ठा saa7146_standard *std)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा saa7146_extension extension;

अटल काष्ठा saa7146_pci_extension_data hexium_hv_pci6 = अणु
	.ext_priv = "Hexium HV-PCI6 / Orion",
	.ext = &extension,
पूर्ण;

अटल काष्ठा saa7146_pci_extension_data hexium_orion_1svhs_3bnc = अणु
	.ext_priv = "Hexium HV-PCI6 / Orion (1 SVHS/3 BNC)",
	.ext = &extension,
पूर्ण;

अटल काष्ठा saa7146_pci_extension_data hexium_orion_4bnc = अणु
	.ext_priv = "Hexium HV-PCI6 / Orion (4 BNC)",
	.ext = &extension,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु
	 .venकरोr = PCI_VENDOR_ID_PHILIPS,
	 .device = PCI_DEVICE_ID_PHILIPS_SAA7146,
	 .subvenकरोr = 0x0000,
	 .subdevice = 0x0000,
	 .driver_data = (अचिन्हित दीर्घ) &hexium_hv_pci6,
	 पूर्ण,
	अणु
	 .venकरोr = PCI_VENDOR_ID_PHILIPS,
	 .device = PCI_DEVICE_ID_PHILIPS_SAA7146,
	 .subvenकरोr = 0x17c8,
	 .subdevice = 0x0101,
	 .driver_data = (अचिन्हित दीर्घ) &hexium_orion_1svhs_3bnc,
	 पूर्ण,
	अणु
	 .venकरोr = PCI_VENDOR_ID_PHILIPS,
	 .device = PCI_DEVICE_ID_PHILIPS_SAA7146,
	 .subvenकरोr = 0x17c8,
	 .subdevice = 0x2101,
	 .driver_data = (अचिन्हित दीर्घ) &hexium_orion_4bnc,
	 पूर्ण,
	अणु
	 .venकरोr = 0,
	 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल काष्ठा saa7146_ext_vv vv_data = अणु
	.inमाला_दो = HEXIUM_INPUTS,
	.capabilities = 0,
	.stds = &hexium_standards[0],
	.num_stds = ARRAY_SIZE(hexium_standards),
	.std_callback = &std_callback,
पूर्ण;

अटल काष्ठा saa7146_extension extension = अणु
	.name = "hexium HV-PCI6 Orion",
	.flags = 0,		// SAA7146_USE_I2C_IRQ,

	.pci_tbl = &pci_tbl[0],
	.module = THIS_MODULE,

	.probe = hexium_probe,
	.attach = hexium_attach,
	.detach = hexium_detach,

	.irq_mask = 0,
	.irq_func = शून्य,
पूर्ण;

अटल पूर्णांक __init hexium_init_module(व्योम)
अणु
	अगर (0 != saa7146_रेजिस्टर_extension(&extension)) अणु
		DEB_S("failed to register extension\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hexium_cleanup_module(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&extension);
पूर्ण

module_init(hexium_init_module);
module_निकास(hexium_cleanup_module);

MODULE_DESCRIPTION("video4linux-2 driver for Hexium Orion frame grabber cards");
MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_LICENSE("GPL");
