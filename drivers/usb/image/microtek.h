<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
 /*
 * Driver क्रम Microtek Scanmaker X6 USB scanner and possibly others.
 * 
 * (C) Copyright 2000 John Fremlin <vii@penguinघातered.com>
 * (C) Copyright 2000 Oliver Neukum <Oliver.Neukum@lrz.uni-muenchen.de>
 *
 * See microtek.c क्रम history
 *
 */

प्रकार व्योम (*mts_scsi_cmnd_callback)(काष्ठा scsi_cmnd *);


काष्ठा mts_transfer_context
अणु
	काष्ठा mts_desc *instance;
	mts_scsi_cmnd_callback final_callback;
	काष्ठा scsi_cmnd *srb;
	
	व्योम *data;
	अचिन्हित data_length;
	पूर्णांक data_pipe;
	काष्ठा scatterlist *curr_sg;

	u8 *scsi_status; /* status वापसed from ep_response after command completion */
पूर्ण;


काष्ठा mts_desc अणु
	काष्ठा mts_desc *next;
	काष्ठा mts_desc *prev;

	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf;

	/* Endpoपूर्णांक addresses */
	u8 ep_out;
	u8 ep_response;
	u8 ep_image;

	काष्ठा Scsi_Host *host;

	काष्ठा urb *urb;
	काष्ठा mts_transfer_context context;
पूर्ण;


#घोषणा MTS_EP_OUT	0x1
#घोषणा MTS_EP_RESPONSE	0x2
#घोषणा MTS_EP_IMAGE	0x3
#घोषणा MTS_EP_TOTAL	0x3

#घोषणा MTS_SCSI_ERR_MASK ~0x3fu

