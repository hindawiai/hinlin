<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * devices.c
 * (C) Copyright 1999 Randy Dunlap.
 * (C) Copyright 1999,2000 Thomas Sailer <sailer@अगरe.ee.ethz.ch>.
 *     (proc file per device)
 * (C) Copyright 1999 Deti Fliegl (new USB architecture)
 *
 *************************************************************
 *
 * <mountpoपूर्णांक>/devices contains USB topology, device, config, class,
 * पूर्णांकerface, & endpoपूर्णांक data.
 *
 * I considered using /dev/bus/usb/device# क्रम each device
 * as it is attached or detached, but I didn't like this क्रम some
 * reason -- maybe it's just too deep of a directory काष्ठाure.
 * I also करोn't like looking in multiple places to gather and view
 * the data.  Having only one file क्रम ./devices also prevents race
 * conditions that could arise अगर a program was पढ़ोing device info
 * क्रम devices that are being हटाओd (unplugged).  (That is, the
 * program may find a directory क्रम devnum_12 then try to खोलो it,
 * but it was just unplugged, so the directory is now deleted.
 * But programs would just have to be prepared क्रम situations like
 * this in any plug-and-play environment.)
 *
 * 1999-12-16: Thomas Sailer <sailer@अगरe.ee.ethz.ch>
 *   Converted the whole proc stuff to real
 *   पढ़ो methods. Now not the whole device list needs to fit
 *   पूर्णांकo one page, only the device list क्रम one bus.
 *   Added a poll method to /sys/kernel/debug/usb/devices, to wake
 *   up an eventual usbd
 * 2000-01-04: Thomas Sailer <sailer@अगरe.ee.ethz.ch>
 *   Turned पूर्णांकo its own fileप्रणाली
 * 2000-07-05: Ashley Montanaro <ashley@compsoc.man.ac.uk>
 *   Converted file पढ़ोing routine to dump to buffer once
 *   per device, not per bus
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/usb.h>
#समावेश <linux/usbdevice_fs.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#समावेश "usb.h"

/* Define ALLOW_SERIAL_NUMBER अगर you want to see the serial number of devices */
#घोषणा ALLOW_SERIAL_NUMBER

अटल स्थिर अक्षर क्रमmat_topo[] =
/* T:  Bus=dd Lev=dd Prnt=dd Port=dd Cnt=dd Dev#=ddd Spd=dddd MxCh=dd */
"\nT:  Bus=%2.2d Lev=%2.2d Prnt=%2.2d Port=%2.2d Cnt=%2.2d Dev#=%3d Spd=%-4s MxCh=%2d\n";

अटल स्थिर अक्षर क्रमmat_string_manufacturer[] =
/* S:  Manufacturer=xxxx */
  "S:  Manufacturer=%.100s\n";

अटल स्थिर अक्षर क्रमmat_string_product[] =
/* S:  Product=xxxx */
  "S:  Product=%.100s\n";

#अगर_घोषित ALLOW_SERIAL_NUMBER
अटल स्थिर अक्षर क्रमmat_string_serialnumber[] =
/* S:  SerialNumber=xxxx */
  "S:  SerialNumber=%.100s\n";
#पूर्ण_अगर

अटल स्थिर अक्षर क्रमmat_bandwidth[] =
/* B:  Alloc=ddd/ddd us (xx%), #Int=ddd, #Iso=ddd */
  "B:  Alloc=%3d/%3d us (%2d%%), #Int=%3d, #Iso=%3d\n";

अटल स्थिर अक्षर क्रमmat_device1[] =
/* D:  Ver=xx.xx Cls=xx(sssss) Sub=xx Prot=xx MxPS=dd #Cfgs=dd */
  "D:  Ver=%2x.%02x Cls=%02x(%-5s) Sub=%02x Prot=%02x MxPS=%2d #Cfgs=%3d\n";

अटल स्थिर अक्षर क्रमmat_device2[] =
/* P:  Venकरोr=xxxx ProdID=xxxx Rev=xx.xx */
  "P:  Vendor=%04x ProdID=%04x Rev=%2x.%02x\n";

अटल स्थिर अक्षर क्रमmat_config[] =
/* C:  #Ifs=dd Cfg#=dd Atr=xx MPwr=dddmA */
  "C:%c #Ifs=%2d Cfg#=%2d Atr=%02x MxPwr=%3dmA\n";

अटल स्थिर अक्षर क्रमmat_iad[] =
/* A:  FirstIf#=dd IfCount=dd Cls=xx(sssss) Sub=xx Prot=xx */
  "A:  FirstIf#=%2d IfCount=%2d Cls=%02x(%-5s) Sub=%02x Prot=%02x\n";

अटल स्थिर अक्षर क्रमmat_अगरace[] =
/* I:  If#=dd Alt=dd #EPs=dd Cls=xx(sssss) Sub=xx Prot=xx Driver=xxxx*/
  "I:%c If#=%2d Alt=%2d #EPs=%2d Cls=%02x(%-5s) Sub=%02x Prot=%02x Driver=%s\n";

अटल स्थिर अक्षर क्रमmat_endpt[] =
/* E:  Ad=xx(s) Atr=xx(ssss) MxPS=dddd Ivl=D?s */
  "E:  Ad=%02x(%c) Atr=%02x(%-4s) MxPS=%4d Ivl=%d%cs\n";

काष्ठा class_info अणु
	पूर्णांक class;
	अक्षर *class_name;
पूर्ण;

अटल स्थिर काष्ठा class_info clas_info[] = अणु
	/* max. 5 अक्षरs. per name string */
	अणुUSB_CLASS_PER_INTERFACE,	">ifc"पूर्ण,
	अणुUSB_CLASS_AUDIO,		"audio"पूर्ण,
	अणुUSB_CLASS_COMM,		"comm."पूर्ण,
	अणुUSB_CLASS_HID,			"HID"पूर्ण,
	अणुUSB_CLASS_PHYSICAL,		"PID"पूर्ण,
	अणुUSB_CLASS_STILL_IMAGE,		"still"पूर्ण,
	अणुUSB_CLASS_PRINTER,		"print"पूर्ण,
	अणुUSB_CLASS_MASS_STORAGE,	"stor."पूर्ण,
	अणुUSB_CLASS_HUB,			"hub"पूर्ण,
	अणुUSB_CLASS_CDC_DATA,		"data"पूर्ण,
	अणुUSB_CLASS_CSCID,		"scard"पूर्ण,
	अणुUSB_CLASS_CONTENT_SEC,		"c-sec"पूर्ण,
	अणुUSB_CLASS_VIDEO,		"video"पूर्ण,
	अणुUSB_CLASS_PERSONAL_HEALTHCARE,	"perhc"पूर्ण,
	अणुUSB_CLASS_AUDIO_VIDEO,		"av"पूर्ण,
	अणुUSB_CLASS_BILLBOARD,		"blbrd"पूर्ण,
	अणुUSB_CLASS_USB_TYPE_C_BRIDGE,	"bridg"पूर्ण,
	अणुUSB_CLASS_WIRELESS_CONTROLLER,	"wlcon"पूर्ण,
	अणुUSB_CLASS_MISC,		"misc"पूर्ण,
	अणुUSB_CLASS_APP_SPEC,		"app."पूर्ण,
	अणुUSB_CLASS_VENDOR_SPEC,		"vend."पूर्ण,
	अणु-1,				"unk."पूर्ण		/* leave as last */
पूर्ण;

/*****************************************************************/

अटल स्थिर अक्षर *class_decode(स्थिर पूर्णांक class)
अणु
	पूर्णांक ix;

	क्रम (ix = 0; clas_info[ix].class != -1; ix++)
		अगर (clas_info[ix].class == class)
			अवरोध;
	वापस clas_info[ix].class_name;
पूर्ण

अटल अक्षर *usb_dump_endpoपूर्णांक_descriptor(पूर्णांक speed, अक्षर *start, अक्षर *end,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अक्षर dir, unit, *type;
	अचिन्हित पूर्णांकerval, bandwidth = 1;

	अगर (start > end)
		वापस start;

	dir = usb_endpoपूर्णांक_dir_in(desc) ? 'I' : 'O';

	अगर (speed == USB_SPEED_HIGH)
		bandwidth = usb_endpoपूर्णांक_maxp_mult(desc);

	/* this isn't checking क्रम illegal values */
	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		type = "Ctrl";
		dir = 'B';			/* ctrl is bidirectional */
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		type = "Isoc";
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		type = "Bulk";
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		type = "Int.";
		अवरोध;
	शेष:	/* "can't happen" */
		वापस start;
	पूर्ण

	पूर्णांकerval = usb_decode_पूर्णांकerval(desc, speed);
	अगर (पूर्णांकerval % 1000) अणु
		unit = 'u';
	पूर्ण अन्यथा अणु
		unit = 'm';
		पूर्णांकerval /= 1000;
	पूर्ण

	start += प्र_लिखो(start, क्रमmat_endpt, desc->bEndpoपूर्णांकAddress, dir,
			 desc->bmAttributes, type,
			 usb_endpoपूर्णांक_maxp(desc) *
			 bandwidth,
			 पूर्णांकerval, unit);
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_पूर्णांकerface_descriptor(अक्षर *start, अक्षर *end,
					स्थिर काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc,
					स्थिर काष्ठा usb_पूर्णांकerface *अगरace,
					पूर्णांक setno)
अणु
	स्थिर काष्ठा usb_पूर्णांकerface_descriptor *desc;
	स्थिर अक्षर *driver_name = "";
	पूर्णांक active = 0;

	अगर (start > end)
		वापस start;
	desc = &पूर्णांकfc->altsetting[setno].desc;
	अगर (अगरace) अणु
		driver_name = (अगरace->dev.driver
				? अगरace->dev.driver->name
				: "(none)");
		active = (desc == &अगरace->cur_altsetting->desc);
	पूर्ण
	start += प्र_लिखो(start, क्रमmat_अगरace,
			 active ? '*' : ' ',	/* mark active altsetting */
			 desc->bInterfaceNumber,
			 desc->bAlternateSetting,
			 desc->bNumEndpoपूर्णांकs,
			 desc->bInterfaceClass,
			 class_decode(desc->bInterfaceClass),
			 desc->bInterfaceSubClass,
			 desc->bInterfaceProtocol,
			 driver_name);
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_पूर्णांकerface(पूर्णांक speed, अक्षर *start, अक्षर *end,
				स्थिर काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc,
				स्थिर काष्ठा usb_पूर्णांकerface *अगरace, पूर्णांक setno)
अणु
	स्थिर काष्ठा usb_host_पूर्णांकerface *desc = &पूर्णांकfc->altsetting[setno];
	पूर्णांक i;

	start = usb_dump_पूर्णांकerface_descriptor(start, end, पूर्णांकfc, अगरace, setno);
	क्रम (i = 0; i < desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		अगर (start > end)
			वापस start;
		start = usb_dump_endpoपूर्णांक_descriptor(speed,
				start, end, &desc->endpoपूर्णांक[i].desc);
	पूर्ण
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_iad_descriptor(अक्षर *start, अक्षर *end,
			स्थिर काष्ठा usb_पूर्णांकerface_assoc_descriptor *iad)
अणु
	अगर (start > end)
		वापस start;
	start += प्र_लिखो(start, क्रमmat_iad,
			 iad->bFirstInterface,
			 iad->bInterfaceCount,
			 iad->bFunctionClass,
			 class_decode(iad->bFunctionClass),
			 iad->bFunctionSubClass,
			 iad->bFunctionProtocol);
	वापस start;
पूर्ण

/* TBD:
 * 0. TBDs
 * 1. marking active पूर्णांकerface altsettings (code lists all, but should mark
 *    which ones are active, अगर any)
 */
अटल अक्षर *usb_dump_config_descriptor(अक्षर *start, अक्षर *end,
				स्थिर काष्ठा usb_config_descriptor *desc,
				पूर्णांक active, पूर्णांक speed)
अणु
	पूर्णांक mul;

	अगर (start > end)
		वापस start;
	अगर (speed >= USB_SPEED_SUPER)
		mul = 8;
	अन्यथा
		mul = 2;
	start += प्र_लिखो(start, क्रमmat_config,
			 /* mark active/actual/current cfg. */
			 active ? '*' : ' ',
			 desc->bNumInterfaces,
			 desc->bConfigurationValue,
			 desc->bmAttributes,
			 desc->bMaxPower * mul);
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_config(पूर्णांक speed, अक्षर *start, अक्षर *end,
			     स्थिर काष्ठा usb_host_config *config, पूर्णांक active)
अणु
	पूर्णांक i, j;
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	अगर (start > end)
		वापस start;
	अगर (!config)
		/* getting these some in 2.3.7; none in 2.3.6 */
		वापस start + प्र_लिखो(start, "(null Cfg. desc.)\n");
	start = usb_dump_config_descriptor(start, end, &config->desc, active,
			speed);
	क्रम (i = 0; i < USB_MAXIADS; i++) अणु
		अगर (config->पूर्णांकf_assoc[i] == शून्य)
			अवरोध;
		start = usb_dump_iad_descriptor(start, end,
					config->पूर्णांकf_assoc[i]);
	पूर्ण
	क्रम (i = 0; i < config->desc.bNumInterfaces; i++) अणु
		पूर्णांकfc = config->पूर्णांकf_cache[i];
		पूर्णांकerface = config->पूर्णांकerface[i];
		क्रम (j = 0; j < पूर्णांकfc->num_altsetting; j++) अणु
			अगर (start > end)
				वापस start;
			start = usb_dump_पूर्णांकerface(speed,
				start, end, पूर्णांकfc, पूर्णांकerface, j);
		पूर्ण
	पूर्ण
	वापस start;
पूर्ण

/*
 * Dump the dअगरferent USB descriptors.
 */
अटल अक्षर *usb_dump_device_descriptor(अक्षर *start, अक्षर *end,
				स्थिर काष्ठा usb_device_descriptor *desc)
अणु
	u16 bcdUSB = le16_to_cpu(desc->bcdUSB);
	u16 bcdDevice = le16_to_cpu(desc->bcdDevice);

	अगर (start > end)
		वापस start;
	start += प्र_लिखो(start, क्रमmat_device1,
			  bcdUSB >> 8, bcdUSB & 0xff,
			  desc->bDeviceClass,
			  class_decode(desc->bDeviceClass),
			  desc->bDeviceSubClass,
			  desc->bDeviceProtocol,
			  desc->bMaxPacketSize0,
			  desc->bNumConfigurations);
	अगर (start > end)
		वापस start;
	start += प्र_लिखो(start, क्रमmat_device2,
			 le16_to_cpu(desc->idVenकरोr),
			 le16_to_cpu(desc->idProduct),
			 bcdDevice >> 8, bcdDevice & 0xff);
	वापस start;
पूर्ण

/*
 * Dump the dअगरferent strings that this device holds.
 */
अटल अक्षर *usb_dump_device_strings(अक्षर *start, अक्षर *end,
				     काष्ठा usb_device *dev)
अणु
	अगर (start > end)
		वापस start;
	अगर (dev->manufacturer)
		start += प्र_लिखो(start, क्रमmat_string_manufacturer,
				 dev->manufacturer);
	अगर (start > end)
		जाओ out;
	अगर (dev->product)
		start += प्र_लिखो(start, क्रमmat_string_product, dev->product);
	अगर (start > end)
		जाओ out;
#अगर_घोषित ALLOW_SERIAL_NUMBER
	अगर (dev->serial)
		start += प्र_लिखो(start, क्रमmat_string_serialnumber,
				 dev->serial);
#पूर्ण_अगर
 out:
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_desc(अक्षर *start, अक्षर *end, काष्ठा usb_device *dev)
अणु
	पूर्णांक i;

	अगर (start > end)
		वापस start;

	start = usb_dump_device_descriptor(start, end, &dev->descriptor);

	अगर (start > end)
		वापस start;

	start = usb_dump_device_strings(start, end, dev);

	क्रम (i = 0; i < dev->descriptor.bNumConfigurations; i++) अणु
		अगर (start > end)
			वापस start;
		start = usb_dump_config(dev->speed,
				start, end, dev->config + i,
				/* active ? */
				(dev->config + i) == dev->actconfig);
	पूर्ण
	वापस start;
पूर्ण


#अगर_घोषित PROC_EXTRA /* TBD: may want to add this code later */

अटल अक्षर *usb_dump_hub_descriptor(अक्षर *start, अक्षर *end,
				     स्थिर काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक leng = USB_DT_HUB_NONVAR_SIZE;
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)desc;

	अगर (start > end)
		वापस start;
	start += प्र_लिखो(start, "Interface:");
	जबतक (leng && start <= end) अणु
		start += प्र_लिखो(start, " %02x", *ptr);
		ptr++; leng--;
	पूर्ण
	*start++ = '\n';
	वापस start;
पूर्ण

अटल अक्षर *usb_dump_string(अक्षर *start, अक्षर *end,
			     स्थिर काष्ठा usb_device *dev, अक्षर *id, पूर्णांक index)
अणु
	अगर (start > end)
		वापस start;
	start += प्र_लिखो(start, "Interface:");
	अगर (index <= dev->maxstring && dev->stringindex &&
	    dev->stringindex[index])
		start += प्र_लिखो(start, "%s: %.100s ", id,
				 dev->stringindex[index]);
	वापस start;
पूर्ण

#पूर्ण_अगर /* PROC_EXTRA */

/*****************************************************************/

/* This is a recursive function. Parameters:
 * buffer - the user-space buffer to ग_लिखो data पूर्णांकo
 * nbytes - the maximum number of bytes to ग_लिखो
 * skip_bytes - the number of bytes to skip beक्रमe writing anything
 * file_offset - the offset पूर्णांकo the devices file on completion
 * The caller must own the device lock.
 */
अटल sमाप_प्रकार usb_device_dump(अक्षर __user **buffer, माप_प्रकार *nbytes,
			       loff_t *skip_bytes, loff_t *file_offset,
			       काष्ठा usb_device *usbdev, काष्ठा usb_bus *bus,
			       पूर्णांक level, पूर्णांक index, पूर्णांक count)
अणु
	पूर्णांक chix;
	पूर्णांक ret, cnt = 0;
	पूर्णांक parent_devnum = 0;
	अक्षर *pages_start, *data_end, *speed;
	अचिन्हित पूर्णांक length;
	sमाप_प्रकार total_written = 0;
	काष्ठा usb_device *childdev = शून्य;

	/* करोn't bother with anything else if we're not writing any data */
	अगर (*nbytes <= 0)
		वापस 0;

	अगर (level > MAX_TOPO_LEVEL)
		वापस 0;
	/* allocate 2^1 pages = 8K (on i386);
	 * should be more than enough क्रम one device */
	pages_start = (अक्षर *)__get_मुक्त_pages(GFP_NOIO, 1);
	अगर (!pages_start)
		वापस -ENOMEM;

	अगर (usbdev->parent && usbdev->parent->devnum != -1)
		parent_devnum = usbdev->parent->devnum;
	/*
	 * So the root hub's parent is 0 and any device that is
	 * plugged पूर्णांकo the root hub has a parent of 0.
	 */
	चयन (usbdev->speed) अणु
	हाल USB_SPEED_LOW:
		speed = "1.5"; अवरोध;
	हाल USB_SPEED_UNKNOWN:		/* usb 1.1 root hub code */
	हाल USB_SPEED_FULL:
		speed = "12"; अवरोध;
	हाल USB_SPEED_WIRELESS:	/* Wireless has no real fixed speed */
	हाल USB_SPEED_HIGH:
		speed = "480"; अवरोध;
	हाल USB_SPEED_SUPER:
		speed = "5000"; अवरोध;
	हाल USB_SPEED_SUPER_PLUS:
		speed = "10000"; अवरोध;
	शेष:
		speed = "??";
	पूर्ण
	data_end = pages_start + प्र_लिखो(pages_start, क्रमmat_topo,
			bus->busnum, level, parent_devnum,
			index, count, usbdev->devnum,
			speed, usbdev->maxchild);
	/*
	 * level = topology-tier level;
	 * parent_devnum = parent device number;
	 * index = parent's connector number;
	 * count = device count at this level
	 */
	/* If this is the root hub, display the bandwidth inक्रमmation */
	अगर (level == 0) अणु
		पूर्णांक	max;

		/* super/high speed reserves 80%, full/low reserves 90% */
		अगर (usbdev->speed == USB_SPEED_HIGH ||
		    usbdev->speed >= USB_SPEED_SUPER)
			max = 800;
		अन्यथा
			max = FRAME_TIME_MAX_USECS_ALLOC;

		/* report "average" periodic allocation over a microsecond.
		 * the schedules are actually bursty, HCDs need to deal with
		 * that and just compute/report this average.
		 */
		data_end += प्र_लिखो(data_end, क्रमmat_bandwidth,
				bus->bandwidth_allocated, max,
				(100 * bus->bandwidth_allocated + max / 2)
					/ max,
				bus->bandwidth_पूर्णांक_reqs,
				bus->bandwidth_isoc_reqs);

	पूर्ण
	data_end = usb_dump_desc(data_end, pages_start + (2 * PAGE_SIZE) - 256,
				 usbdev);

	अगर (data_end > (pages_start + (2 * PAGE_SIZE) - 256))
		data_end += प्र_लिखो(data_end, "(truncated)\n");

	length = data_end - pages_start;
	/* अगर we can start copying some data to the user */
	अगर (length > *skip_bytes) अणु
		length -= *skip_bytes;
		अगर (length > *nbytes)
			length = *nbytes;
		अगर (copy_to_user(*buffer, pages_start + *skip_bytes, length)) अणु
			मुक्त_pages((अचिन्हित दीर्घ)pages_start, 1);
			वापस -EFAULT;
		पूर्ण
		*nbytes -= length;
		*file_offset += length;
		total_written += length;
		*buffer += length;
		*skip_bytes = 0;
	पूर्ण अन्यथा
		*skip_bytes -= length;

	मुक्त_pages((अचिन्हित दीर्घ)pages_start, 1);

	/* Now look at all of this device's children. */
	usb_hub_क्रम_each_child(usbdev, chix, childdev) अणु
		usb_lock_device(childdev);
		ret = usb_device_dump(buffer, nbytes, skip_bytes,
				      file_offset, childdev, bus,
				      level + 1, chix - 1, ++cnt);
		usb_unlock_device(childdev);
		अगर (ret == -EFAULT)
			वापस total_written;
		total_written += ret;
	पूर्ण
	वापस total_written;
पूर्ण

अटल sमाप_प्रकार usb_device_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा usb_bus *bus;
	sमाप_प्रकार ret, total_written = 0;
	loff_t skip_bytes = *ppos;
	पूर्णांक id;

	अगर (*ppos < 0)
		वापस -EINVAL;
	अगर (nbytes <= 0)
		वापस 0;

	mutex_lock(&usb_bus_idr_lock);
	/* prपूर्णांक devices क्रम all busses */
	idr_क्रम_each_entry(&usb_bus_idr, bus, id) अणु
		/* recurse through all children of the root hub */
		अगर (!bus_to_hcd(bus)->rh_रेजिस्टरed)
			जारी;
		usb_lock_device(bus->root_hub);
		ret = usb_device_dump(&buf, &nbytes, &skip_bytes, ppos,
				      bus->root_hub, bus, 0, 0, 0);
		usb_unlock_device(bus->root_hub);
		अगर (ret < 0) अणु
			mutex_unlock(&usb_bus_idr_lock);
			वापस ret;
		पूर्ण
		total_written += ret;
	पूर्ण
	mutex_unlock(&usb_bus_idr_lock);
	वापस total_written;
पूर्ण

स्थिर काष्ठा file_operations usbfs_devices_fops = अणु
	.llseek =	no_seek_end_llseek,
	.पढ़ो =		usb_device_पढ़ो,
पूर्ण;
