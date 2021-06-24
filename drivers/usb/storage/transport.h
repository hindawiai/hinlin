<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम USB Mass Storage compliant devices
 * Transport Functions Header File
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

#अगर_अघोषित _TRANSPORT_H_
#घोषणा _TRANSPORT_H_

#समावेश <linux/blkdev.h>

/*
 * usb_stor_bulk_transfer_xxx() वापस codes, in order of severity
 */

#घोषणा USB_STOR_XFER_GOOD	0	/* good transfer                 */
#घोषणा USB_STOR_XFER_SHORT	1	/* transferred less than expected */
#घोषणा USB_STOR_XFER_STALLED	2	/* endpoपूर्णांक stalled              */
#घोषणा USB_STOR_XFER_LONG	3	/* device tried to send too much */
#घोषणा USB_STOR_XFER_ERROR	4	/* transfer died in the middle   */

/*
 * Transport वापस codes
 */

#घोषणा USB_STOR_TRANSPORT_GOOD	   0   /* Transport good, command good	   */
#घोषणा USB_STOR_TRANSPORT_FAILED  1   /* Transport good, command failed   */
#घोषणा USB_STOR_TRANSPORT_NO_SENSE 2  /* Command failed, no स्वतः-sense    */
#घोषणा USB_STOR_TRANSPORT_ERROR   3   /* Transport bad (i.e. device dead) */

/*
 * We used to have USB_STOR_XFER_ABORTED and USB_STOR_TRANSPORT_ABORTED
 * वापस codes.  But now the transport and low-level transfer routines
 * treat an पात as just another error (-ENOENT क्रम a cancelled URB).
 * It is up to the invoke_transport() function to test क्रम पातs and
 * distinguish them from genuine communication errors.
 */

/*
 * CBI accept device specअगरic command
 */

#घोषणा US_CBI_ADSC		0

बाह्य पूर्णांक usb_stor_CB_transport(काष्ठा scsi_cmnd *, काष्ठा us_data*);
बाह्य पूर्णांक usb_stor_CB_reset(काष्ठा us_data*);

बाह्य पूर्णांक usb_stor_Bulk_transport(काष्ठा scsi_cmnd *, काष्ठा us_data*);
बाह्य पूर्णांक usb_stor_Bulk_max_lun(काष्ठा us_data*);
बाह्य पूर्णांक usb_stor_Bulk_reset(काष्ठा us_data*);

बाह्य व्योम usb_stor_invoke_transport(काष्ठा scsi_cmnd *, काष्ठा us_data*);
बाह्य व्योम usb_stor_stop_transport(काष्ठा us_data*);

बाह्य पूर्णांक usb_stor_control_msg(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		u8 request, u8 requesttype, u16 value, u16 index,
		व्योम *data, u16 size, पूर्णांक समयout);
बाह्य पूर्णांक usb_stor_clear_halt(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe);

बाह्य पूर्णांक usb_stor_ctrl_transfer(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		u8 request, u8 requesttype, u16 value, u16 index,
		व्योम *data, u16 size);
बाह्य पूर्णांक usb_stor_bulk_transfer_buf(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		व्योम *buf, अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक *act_len);
बाह्य पूर्णांक usb_stor_bulk_transfer_sg(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		व्योम *buf, अचिन्हित पूर्णांक length, पूर्णांक use_sg, पूर्णांक *residual);
बाह्य पूर्णांक usb_stor_bulk_srb(काष्ठा us_data* us, अचिन्हित पूर्णांक pipe,
		काष्ठा scsi_cmnd* srb);

बाह्य पूर्णांक usb_stor_port_reset(काष्ठा us_data *us);
#पूर्ण_अगर
