<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Fileप्रणाली based user-mode API to USB Gadget controller hardware
 *
 * Other than ep0 operations, most things are करोne by पढ़ो() and ग_लिखो()
 * on endpoपूर्णांक files found in one directory.  They are configured by
 * writing descriptors, and then may be used क्रम normal stream style
 * i/o requests.  When ep0 is configured, the device can क्रमागतerate;
 * when it's बंदd, the device disconnects from usb.  Operations on
 * ep0 require ioctl() operations.
 *
 * Configuration and device descriptors get written to /dev/gadget/$CHIP,
 * which may then be used to पढ़ो usb_gadgetfs_event काष्ठाs.  The driver
 * may activate endpoपूर्णांकs as it handles SET_CONFIGURATION setup events,
 * or earlier; writing endpoपूर्णांक descriptors to /dev/gadget/$ENDPOINT
 * then perक्रमming data transfers by पढ़ोing or writing.
 */

#अगर_अघोषित __LINUX_USB_GADGETFS_H
#घोषणा __LINUX_USB_GADGETFS_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#समावेश <linux/usb/ch9.h>

/*
 * Events are delivered on the ep0 file descriptor, when the user mode driver
 * पढ़ोs from this file descriptor after writing the descriptors.  Don't
 * stop polling this descriptor.
 */

क्रमागत usb_gadgetfs_event_type अणु
	GADGETFS_NOP = 0,

	GADGETFS_CONNECT,
	GADGETFS_DISCONNECT,
	GADGETFS_SETUP,
	GADGETFS_SUSPEND,
	/* and likely more ! */
पूर्ण;

/* NOTE:  this काष्ठाure must stay the same size and layout on
 * both 32-bit and 64-bit kernels.
 */
काष्ठा usb_gadgetfs_event अणु
	जोड़ अणु
		/* NOP, DISCONNECT, SUSPEND: nothing
		 * ... some hardware can't report disconnection
		 */

		/* CONNECT: just the speed */
		क्रमागत usb_device_speed	speed;

		/* SETUP: packet; DATA phase i/o precedes next event
		 *(setup.bmRequestType & USB_सूची_IN) flags direction
		 * ... includes SET_CONFIGURATION, SET_INTERFACE
		 */
		काष्ठा usb_ctrlrequest	setup;
	पूर्ण u;
	क्रमागत usb_gadgetfs_event_type	type;
पूर्ण;


/* The 'g' code is also used by prपूर्णांकer gadget ioctl requests.
 * Don't add any colliding codes to either driver, and keep
 * them in unique ranges (size 0x20 क्रम now).
 */

/* endpoपूर्णांक ioctls */

/* IN transfers may be reported to the gadget driver as complete
 *	when the fअगरo is loaded, beक्रमe the host पढ़ोs the data;
 * OUT transfers may be reported to the host's "client" driver as
 *	complete when they're sitting in the FIFO unपढ़ो.
 * THIS वापसs how many bytes are "unclaimed" in the endpoपूर्णांक fअगरo
 * (needed क्रम precise fault handling, when the hardware allows it)
 */
#घोषणा	GADGETFS_FIFO_STATUS	_IO('g', 1)

/* discards any unclaimed data in the fअगरo. */
#घोषणा	GADGETFS_FIFO_FLUSH	_IO('g', 2)

/* resets endpoपूर्णांक halt+toggle; used to implement set_पूर्णांकerface.
 * some hardware (like pxa2xx) can't support this.
 */
#घोषणा	GADGETFS_CLEAR_HALT	_IO('g', 3)

#पूर्ण_अगर /* __LINUX_USB_GADGETFS_H */
