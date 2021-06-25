<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम USB Mass Storage compliant devices
 * Debugging Functions Header File
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecअगरic.com)
 *
 * This driver is based on the 'USB Mass Storage Class' करोcument. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this करोcument.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specअगरications.
 *
 * It is important to note that in a number of हालs this class
 * exhibits class-specअगरic exemptions from the USB specअगरication.
 * Notably the usage of NAK, STALL and ACK dअगरfers from the norm, in
 * that they are used to communicate रुको, failed and OK on commands.
 *
 * Also, क्रम certain devices, the पूर्णांकerrupt endpoपूर्णांक is used to convey
 * status of a command.
 */

#अगर_अघोषित _DEBUG_H_
#घोषणा _DEBUG_H_

#समावेश <linux/kernel.h>

#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
व्योम usb_stor_show_command(स्थिर काष्ठा us_data *us, काष्ठा scsi_cmnd *srb);
व्योम usb_stor_show_sense(स्थिर काष्ठा us_data *us, अचिन्हित अक्षर key,
			 अचिन्हित अक्षर asc, अचिन्हित अक्षर ascq);
__म_लिखो(2, 3) व्योम usb_stor_dbg(स्थिर काष्ठा us_data *us,
				 स्थिर अक्षर *fmt, ...);

#घोषणा US_DEBUG(x)		x
#अन्यथा
__म_लिखो(2, 3)
अटल अंतरभूत व्योम _usb_stor_dbg(स्थिर काष्ठा us_data *us,
				 स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#घोषणा usb_stor_dbg(us, fmt, ...)				\
	करो अणु अगर (0) _usb_stor_dbg(us, fmt, ##__VA_ARGS__); पूर्ण जबतक (0)
#घोषणा US_DEBUG(x)
#पूर्ण_अगर

#पूर्ण_अगर
