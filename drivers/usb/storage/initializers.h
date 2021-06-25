<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Header file क्रम Special Initializers क्रम certain USB Mass Storage devices
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
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

#समावेश "usb.h"
#समावेश "transport.h"

/*
 * This places the Shuttle/SCM USB<->SCSI bridge devices in multi-target
 * mode
 */
पूर्णांक usb_stor_euscsi_init(काष्ठा us_data *us);

/*
 * This function is required to activate all four slots on the UCR-61S2B
 * flash पढ़ोer
 */
पूर्णांक usb_stor_ucr61s2b_init(काष्ठा us_data *us);

/* This places the HUAWEI E220 devices in multi-port mode */
पूर्णांक usb_stor_huawei_e220_init(काष्ठा us_data *us);
