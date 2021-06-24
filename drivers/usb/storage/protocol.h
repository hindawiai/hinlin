<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम USB Mass Storage compliant devices
 * Protocol Functions Header File
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

#अगर_अघोषित _PROTOCOL_H_
#घोषणा _PROTOCOL_H_

/* Protocol handling routines */
बाह्य व्योम usb_stor_pad12_command(काष्ठा scsi_cmnd*, काष्ठा us_data*);
बाह्य व्योम usb_stor_ufi_command(काष्ठा scsi_cmnd*, काष्ठा us_data*);
बाह्य व्योम usb_stor_transparent_scsi_command(काष्ठा scsi_cmnd*,
		काष्ठा us_data*);

/* काष्ठा scsi_cmnd transfer buffer access utilities */
क्रमागत xfer_buf_dir	अणुTO_XFER_BUF, FROM_XFER_BUFपूर्ण;

बाह्य अचिन्हित पूर्णांक usb_stor_access_xfer_buf(अचिन्हित अक्षर *buffer,
	अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb, काष्ठा scatterlist **,
	अचिन्हित पूर्णांक *offset, क्रमागत xfer_buf_dir dir);

बाह्य व्योम usb_stor_set_xfer_buf(अचिन्हित अक्षर *buffer,
	अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb);
#पूर्ण_अगर
