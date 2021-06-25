<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    hexium_gemini.c - v4l2 driver क्रम Hexium Gemini frame grabber cards

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

#घोषणा HEXIUM_GEMINI			4
#घोषणा HEXIUM_GEMINI_DUAL		5

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

#घोषणा HEXIUM_GEMINI_V_1_0		1
#घोषणा HEXIUM_GEMINI_DUAL_V_1_0	2

काष्ठा hexium
अणु
	पूर्णांक type;

	काष्ठा video_device	video_dev;
	काष्ठा i2c_adapter	i2c_adapter;

	पूर्णांक		cur_input;	/* current input */
	v4l2_std_id	cur_std;	/* current standard */
पूर्ण;

/* Samsung KS0127B decoder शेष रेजिस्टरs */
अटल u8 hexium_ks0127b[0x100]=अणु
/*00*/ 0x00,0x52,0x30,0x40,0x01,0x0C,0x2A,0x10,
/*08*/ 0x00,0x00,0x00,0x60,0x00,0x00,0x0F,0x06,
/*10*/ 0x00,0x00,0xE4,0xC0,0x00,0x00,0x00,0x00,
/*18*/ 0x14,0x9B,0xFE,0xFF,0xFC,0xFF,0x03,0x22,
/*20*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*28*/ 0x00,0x00,0x00,0x00,0x00,0x2C,0x9B,0x00,
/*30*/ 0x00,0x00,0x10,0x80,0x80,0x10,0x80,0x80,
/*38*/ 0x01,0x04,0x00,0x00,0x00,0x29,0xC0,0x00,
/*40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*48*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*50*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*58*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*60*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*68*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*78*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*80*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*88*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*90*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*98*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*A0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*A8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*B0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*B8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*C0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*C8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*D0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*D8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*E0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*E8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*F0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*F8*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
पूर्ण;

अटल काष्ठा hexium_data hexium_pal[] = अणु
	अणु 0x01, 0x52 पूर्ण, अणु 0x12, 0x64 पूर्ण, अणु 0x2D, 0x2C पूर्ण, अणु 0x2E, 0x9B पूर्ण, अणु -1 , 0xFF पूर्ण
पूर्ण;

अटल काष्ठा hexium_data hexium_ntsc[] = अणु
	अणु 0x01, 0x53 पूर्ण, अणु 0x12, 0x04 पूर्ण, अणु 0x2D, 0x23 पूर्ण, अणु 0x2E, 0x81 पूर्ण, अणु -1 , 0xFF पूर्ण
पूर्ण;

अटल काष्ठा hexium_data hexium_secam[] = अणु
	अणु 0x01, 0x52 पूर्ण, अणु 0x12, 0x64 पूर्ण, अणु 0x2D, 0x2C पूर्ण, अणु 0x2E, 0x9B पूर्ण, अणु -1 , 0xFF पूर्ण
पूर्ण;

अटल काष्ठा hexium_data hexium_input_select[] = अणु
	अणु 0x02, 0x60 पूर्ण,
	अणु 0x02, 0x64 पूर्ण,
	अणु 0x02, 0x61 पूर्ण,
	अणु 0x02, 0x65 पूर्ण,
	अणु 0x02, 0x62 पूर्ण,
	अणु 0x02, 0x66 पूर्ण,
	अणु 0x02, 0x68 पूर्ण,
	अणु 0x02, 0x69 पूर्ण,
	अणु 0x02, 0x6A पूर्ण,
पूर्ण;

/* fixme: h_offset = 0 क्रम Hexium Gemini *Dual*, which
   are currently *not* supported*/
अटल काष्ठा saa7146_standard hexium_standards[] = अणु
	अणु
		.name	= "PAL",	.id	= V4L2_STD_PAL,
		.v_offset	= 28,	.v_field	= 288,
		.h_offset	= 1,	.h_pixels	= 680,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण, अणु
		.name	= "NTSC",	.id	= V4L2_STD_NTSC,
		.v_offset	= 28,	.v_field	= 240,
		.h_offset	= 1,	.h_pixels	= 640,
		.v_max_out	= 480,	.h_max_out	= 640,
	पूर्ण, अणु
		.name	= "SECAM",	.id	= V4L2_STD_SECAM,
		.v_offset	= 28,	.v_field	= 288,
		.h_offset	= 1,	.h_pixels	= 720,
		.v_max_out	= 576,	.h_max_out	= 768,
	पूर्ण
पूर्ण;

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
	क्रम (i = 0; i < माप(hexium_ks0127b); i++) अणु
		data.byte = hexium_ks0127b[i];
		अगर (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x6c, 0, I2C_SMBUS_WRITE, i, I2C_SMBUS_BYTE_DATA, &data)) अणु
			pr_err("hexium_init_done() failed for address 0x%02x\n",
			       i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hexium_set_input(काष्ठा hexium *hexium, पूर्णांक input)
अणु
	जोड़ i2c_smbus_data data;

	DEB_D("\n");

	data.byte = hexium_input_select[input].byte;
	अगर (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x6c, 0, I2C_SMBUS_WRITE, hexium_input_select[input].adr, I2C_SMBUS_BYTE_DATA, &data)) अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hexium_set_standard(काष्ठा hexium *hexium, काष्ठा hexium_data *vdec)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक i = 0;

	DEB_D("\n");

	जबतक (vdec[i].adr != -1) अणु
		data.byte = vdec[i].byte;
		अगर (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x6c, 0, I2C_SMBUS_WRITE, vdec[i].adr, I2C_SMBUS_BYTE_DATA, &data)) अणु
			pr_err("hexium_init_done: hexium_set_standard() failed for address 0x%02x\n",
			       i);
			वापस -1;
		पूर्ण
		i++;
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

	DEB_EE("VIDIOC_S_INPUT %d\n", input);

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
	काष्ठा hexium *hexium;
	पूर्णांक ret;

	DEB_EE("\n");

	hexium = kzalloc(माप(*hexium), GFP_KERNEL);
	अगर (!hexium)
		वापस -ENOMEM;

	dev->ext_priv = hexium;

	/* enable i2c-port pins */
	saa7146_ग_लिखो(dev, MC1, (MASK_08 | MASK_24 | MASK_10 | MASK_26));

	strscpy(hexium->i2c_adapter.name, "hexium gemini",
		माप(hexium->i2c_adapter.name));
	saa7146_i2c_adapter_prepare(dev, &hexium->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	अगर (i2c_add_adapter(&hexium->i2c_adapter) < 0) अणु
		DEB_S("cannot register i2c-device. skipping.\n");
		kमुक्त(hexium);
		वापस -EFAULT;
	पूर्ण

	/*  set HWControl GPIO number 2 */
	saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	saa7146_ग_लिखो(dev, DD1_INIT, 0x07000700);
	saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
	saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	/* the rest */
	hexium->cur_input = 0;
	hexium_init_करोne(dev);

	hexium_set_standard(hexium, hexium_pal);
	hexium->cur_std = V4L2_STD_PAL;

	hexium_set_input(hexium, 0);
	hexium->cur_input = 0;

	saa7146_vv_init(dev, &vv_data);

	vv_data.vid_ops.vidioc_क्रमागत_input = vidioc_क्रमागत_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	ret = saa7146_रेजिस्टर_device(&hexium->video_dev, dev, "hexium gemini", VFL_TYPE_VIDEO);
	अगर (ret < 0) अणु
		pr_err("cannot register capture v4l2 device. skipping.\n");
		saa7146_vv_release(dev);
		i2c_del_adapter(&hexium->i2c_adapter);
		kमुक्त(hexium);
		वापस ret;
	पूर्ण

	pr_info("found 'hexium gemini' frame grabber-%d\n", hexium_num);
	hexium_num++;

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
	काष्ठा hexium *hexium = (काष्ठा hexium *) dev->ext_priv;

	अगर (V4L2_STD_PAL == std->id) अणु
		hexium_set_standard(hexium, hexium_pal);
		hexium->cur_std = V4L2_STD_PAL;
		वापस 0;
	पूर्ण अन्यथा अगर (V4L2_STD_NTSC == std->id) अणु
		hexium_set_standard(hexium, hexium_ntsc);
		hexium->cur_std = V4L2_STD_NTSC;
		वापस 0;
	पूर्ण अन्यथा अगर (V4L2_STD_SECAM == std->id) अणु
		hexium_set_standard(hexium, hexium_secam);
		hexium->cur_std = V4L2_STD_SECAM;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल काष्ठा saa7146_extension hexium_extension;

अटल काष्ठा saa7146_pci_extension_data hexium_gemini_4bnc = अणु
	.ext_priv = "Hexium Gemini (4 BNC)",
	.ext = &hexium_extension,
पूर्ण;

अटल काष्ठा saa7146_pci_extension_data hexium_gemini_dual_4bnc = अणु
	.ext_priv = "Hexium Gemini Dual (4 BNC)",
	.ext = &hexium_extension,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु
	 .venकरोr = PCI_VENDOR_ID_PHILIPS,
	 .device = PCI_DEVICE_ID_PHILIPS_SAA7146,
	 .subvenकरोr = 0x17c8,
	 .subdevice = 0x2401,
	 .driver_data = (अचिन्हित दीर्घ) &hexium_gemini_4bnc,
	 पूर्ण,
	अणु
	 .venकरोr = PCI_VENDOR_ID_PHILIPS,
	 .device = PCI_DEVICE_ID_PHILIPS_SAA7146,
	 .subvenकरोr = 0x17c8,
	 .subdevice = 0x2402,
	 .driver_data = (अचिन्हित दीर्घ) &hexium_gemini_dual_4bnc,
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

अटल काष्ठा saa7146_extension hexium_extension = अणु
	.name = "hexium gemini",
	.flags = SAA7146_USE_I2C_IRQ,

	.pci_tbl = &pci_tbl[0],
	.module = THIS_MODULE,

	.attach = hexium_attach,
	.detach = hexium_detach,

	.irq_mask = 0,
	.irq_func = शून्य,
पूर्ण;

अटल पूर्णांक __init hexium_init_module(व्योम)
अणु
	अगर (0 != saa7146_रेजिस्टर_extension(&hexium_extension)) अणु
		DEB_S("failed to register extension\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hexium_cleanup_module(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&hexium_extension);
पूर्ण

module_init(hexium_init_module);
module_निकास(hexium_cleanup_module);

MODULE_DESCRIPTION("video4linux-2 driver for Hexium Gemini frame grabber cards");
MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_LICENSE("GPL");
