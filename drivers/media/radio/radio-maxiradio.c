<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Guillemot Maxi Radio FM 2000 PCI radio card driver क्रम Linux
 * (C) 2001 Dimitromanolakis Apostolos <apdim@grecian.net>
 *
 * Based in the radio Maestro PCI driver. Actually it uses the same chip
 * क्रम radio but dअगरferent pci controller.
 *
 * I didn't have any specs I reversed engineered the protocol from
 * the winकरोws driver (radio.dll).
 *
 * The card uses the TEA5757 chip that includes a search function but it
 * is useless as I haven't found any way to पढ़ो back the frequency. If
 * anybody करोes please mail me.
 *
 * For the pdf file see:
 * http://www.nxp.com/acrobat_करोwnload2/expired_datasheets/TEA5757_5759_3.pdf
 *
 *
 * CHANGES:
 *   0.75b
 *     - better pci पूर्णांकerface thanks to Francois Romieu <romieu@cogenit.fr>
 *
 *   0.75      Sun Feb  4 22:51:27 EET 2001
 *     - tiding up
 *     - हटाओd support क्रम multiple devices as it didn't work anyway
 *
 * BUGS:
 *   - card unmutes अगर you change frequency
 *
 * (c) 2006, 2007 by Mauro Carvalho Chehab <mchehab@kernel.org>:
 *	- Conversion to V4L2 API
 *      - Uses video_ioctl2 क्रम parsing and to add debug support
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <media/drv-पूर्णांकf/tea575x.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

MODULE_AUTHOR("Dimitromanolakis Apostolos, apdim@grecian.net");
MODULE_DESCRIPTION("Radio driver for the Guillemot Maxi Radio FM2000.");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");

अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0644);
MODULE_PARM_DESC(radio_nr, "Radio device number");

/* TEA5757 pin mappings */
अटल स्थिर पूर्णांक clk = 1, data = 2, wren = 4, mo_st = 8, घातer = 16;

अटल atomic_t maxiradio_instance = ATOMIC_INIT(0);

#घोषणा PCI_VENDOR_ID_GUILLEMOT 0x5046
#घोषणा PCI_DEVICE_ID_GUILLEMOT_MAXIRADIO 0x1001

काष्ठा maxiradio
अणु
	काष्ठा snd_tea575x tea;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा pci_dev *pdev;

	u16	io;	/* base of radio io */
पूर्ण;

अटल अंतरभूत काष्ठा maxiradio *to_maxiradio(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा maxiradio, v4l2_dev);
पूर्ण

अटल व्योम maxiradio_tea575x_set_pins(काष्ठा snd_tea575x *tea, u8 pins)
अणु
	काष्ठा maxiradio *dev = tea->निजी_data;
	u8 bits = 0;

	bits |= (pins & TEA575X_DATA) ? data : 0;
	bits |= (pins & TEA575X_CLK)  ? clk  : 0;
	bits |= (pins & TEA575X_WREN) ? wren : 0;
	bits |= घातer;

	outb(bits, dev->io);
पूर्ण

/* Note: this card cannot पढ़ो out the data of the shअगरt रेजिस्टरs,
   only the mono/stereo pin works. */
अटल u8 maxiradio_tea575x_get_pins(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा maxiradio *dev = tea->निजी_data;
	u8 bits = inb(dev->io);

	वापस  ((bits & data) ? TEA575X_DATA : 0) |
		((bits & mo_st) ? TEA575X_MOST : 0);
पूर्ण

अटल व्योम maxiradio_tea575x_set_direction(काष्ठा snd_tea575x *tea, bool output)
अणु
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops maxiradio_tea_ops = अणु
	.set_pins = maxiradio_tea575x_set_pins,
	.get_pins = maxiradio_tea575x_get_pins,
	.set_direction = maxiradio_tea575x_set_direction,
पूर्ण;

अटल पूर्णांक maxiradio_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा maxiradio *dev;
	काष्ठा v4l2_device *v4l2_dev;
	पूर्णांक retval = -ENOMEM;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		dev_err(&pdev->dev, "not enough memory\n");
		वापस -ENOMEM;
	पूर्ण

	v4l2_dev = &dev->v4l2_dev;
	v4l2_device_set_name(v4l2_dev, "maxiradio", &maxiradio_instance);

	retval = v4l2_device_रेजिस्टर(&pdev->dev, v4l2_dev);
	अगर (retval < 0) अणु
		v4l2_err(v4l2_dev, "Could not register v4l2_device\n");
		जाओ errfr;
	पूर्ण
	dev->tea.निजी_data = dev;
	dev->tea.ops = &maxiradio_tea_ops;
	/* The data pin cannot be पढ़ो. This may be a hardware limitation, or
	   we just करोn't know how to पढ़ो it. */
	dev->tea.cannot_पढ़ो_data = true;
	dev->tea.v4l2_dev = v4l2_dev;
	dev->tea.radio_nr = radio_nr;
	strscpy(dev->tea.card, "Maxi Radio FM2000", माप(dev->tea.card));
	snम_लिखो(dev->tea.bus_info, माप(dev->tea.bus_info),
			"PCI:%s", pci_name(pdev));

	retval = -ENODEV;

	अगर (!request_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0), v4l2_dev->name)) अणु
		dev_err(&pdev->dev, "can't reserve I/O ports\n");
		जाओ err_hdl;
	पूर्ण

	अगर (pci_enable_device(pdev))
		जाओ err_out_मुक्त_region;

	dev->io = pci_resource_start(pdev, 0);
	अगर (snd_tea575x_init(&dev->tea, THIS_MODULE)) अणु
		prपूर्णांकk(KERN_ERR "radio-maxiradio: Unable to detect TEA575x tuner\n");
		जाओ err_out_मुक्त_region;
	पूर्ण
	वापस 0;

err_out_मुक्त_region:
	release_region(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
err_hdl:
	v4l2_device_unरेजिस्टर(v4l2_dev);
errfr:
	kमुक्त(dev);
	वापस retval;
पूर्ण

अटल व्योम maxiradio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा maxiradio *dev = to_maxiradio(v4l2_dev);

	snd_tea575x_निकास(&dev->tea);
	/* Turn off घातer */
	outb(0, dev->io);
	v4l2_device_unरेजिस्टर(v4l2_dev);
	release_region(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id maxiradio_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_GUILLEMOT, PCI_DEVICE_ID_GUILLEMOT_MAXIRADIO,
		PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, maxiradio_pci_tbl);

अटल काष्ठा pci_driver maxiradio_driver = अणु
	.name		= "radio-maxiradio",
	.id_table	= maxiradio_pci_tbl,
	.probe		= maxiradio_probe,
	.हटाओ		= maxiradio_हटाओ,
पूर्ण;

module_pci_driver(maxiradio_driver);
