<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Rio Karma
 *
 *   (c) 2006 Bob Copeland <me@bobcopeland.com>
 *   (c) 2006 Keith Bennett <keith@mcs.st-and.ac.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-karma"

MODULE_DESCRIPTION("Driver for Rio Karma");
MODULE_AUTHOR("Bob Copeland <me@bobcopeland.com>, Keith Bennett <keith@mcs.st-and.ac.uk>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

#घोषणा RIO_PREFIX "RIOP\x00"
#घोषणा RIO_PREFIX_LEN 5
#घोषणा RIO_SEND_LEN 40
#घोषणा RIO_RECV_LEN 0x200

#घोषणा RIO_ENTER_STORAGE 0x1
#घोषणा RIO_LEAVE_STORAGE 0x2
#घोषणा RIO_RESET 0xC

काष्ठा karma_data अणु
	पूर्णांक in_storage;
	अक्षर *recv;
पूर्ण;

अटल पूर्णांक rio_karma_init(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id karma_usb_ids[] = अणु
#	include "unusual_karma.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, karma_usb_ids);

#अघोषित UNUSUAL_DEV

/*
 * The flags table
 */
#घोषणा UNUSUAL_DEV(idVenकरोr, idProduct, bcdDeviceMin, bcdDeviceMax, \
		    venकरोr_name, product_name, use_protocol, use_transport, \
		    init_function, Flags) \
अणु \
	.venकरोrName = venकरोr_name,	\
	.productName = product_name,	\
	.useProtocol = use_protocol,	\
	.useTransport = use_transport,	\
	.initFunction = init_function,	\
पूर्ण

अटल काष्ठा us_unusual_dev karma_unusual_dev_list[] = अणु
#	include "unusual_karma.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


/*
 * Send commands to Rio Karma.
 *
 * For each command we send 40 bytes starting 'RIOP\0' followed by
 * the command number and a sequence number, which the device will ack
 * with a 512-byte packet with the high four bits set and everything
 * अन्यथा null.  Then we send 'RIOP\x80' followed by a zero and the
 * sequence number, until byte 5 in the response repeats the sequence
 * number.
 */
अटल पूर्णांक rio_karma_send_command(अक्षर cmd, काष्ठा us_data *us)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ समयout;
	अटल अचिन्हित अक्षर seq = 1;
	काष्ठा karma_data *data = (काष्ठा karma_data *) us->extra;

	usb_stor_dbg(us, "sending command %04x\n", cmd);
	स_रखो(us->iobuf, 0, RIO_SEND_LEN);
	स_नकल(us->iobuf, RIO_PREFIX, RIO_PREFIX_LEN);
	us->iobuf[5] = cmd;
	us->iobuf[6] = seq;

	समयout = jअगरfies + msecs_to_jअगरfies(6000);
	क्रम (;;) अणु
		result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
			us->iobuf, RIO_SEND_LEN, शून्य);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ err;

		result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			data->recv, RIO_RECV_LEN, शून्य);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ err;

		अगर (data->recv[5] == seq)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout))
			जाओ err;

		us->iobuf[4] = 0x80;
		us->iobuf[5] = 0;
		msleep(50);
	पूर्ण

	seq++;
	अगर (seq == 0)
		seq = 1;

	usb_stor_dbg(us, "sent command %04x\n", cmd);
	वापस 0;
err:
	usb_stor_dbg(us, "command %04x failed\n", cmd);
	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण

/*
 * Trap START_STOP and READ_10 to leave/re-enter storage mode.
 * Everything अन्यथा is propagated to the normal bulk layer.
 */
अटल पूर्णांक rio_karma_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक ret;
	काष्ठा karma_data *data = (काष्ठा karma_data *) us->extra;

	अगर (srb->cmnd[0] == READ_10 && !data->in_storage) अणु
		ret = rio_karma_send_command(RIO_ENTER_STORAGE, us);
		अगर (ret)
			वापस ret;

		data->in_storage = 1;
		वापस usb_stor_Bulk_transport(srb, us);
	पूर्ण अन्यथा अगर (srb->cmnd[0] == START_STOP) अणु
		ret = rio_karma_send_command(RIO_LEAVE_STORAGE, us);
		अगर (ret)
			वापस ret;

		data->in_storage = 0;
		वापस rio_karma_send_command(RIO_RESET, us);
	पूर्ण
	वापस usb_stor_Bulk_transport(srb, us);
पूर्ण

अटल व्योम rio_karma_deकाष्ठाor(व्योम *extra)
अणु
	काष्ठा karma_data *data = (काष्ठा karma_data *) extra;

	kमुक्त(data->recv);
पूर्ण

अटल पूर्णांक rio_karma_init(काष्ठा us_data *us)
अणु
	पूर्णांक ret = 0;
	काष्ठा karma_data *data = kzalloc(माप(काष्ठा karma_data), GFP_NOIO);

	अगर (!data)
		जाओ out;

	data->recv = kदो_स्मृति(RIO_RECV_LEN, GFP_NOIO);
	अगर (!data->recv) अणु
		kमुक्त(data);
		जाओ out;
	पूर्ण

	us->extra = data;
	us->extra_deकाष्ठाor = rio_karma_deकाष्ठाor;
	ret = rio_karma_send_command(RIO_ENTER_STORAGE, us);
	data->in_storage = (ret == 0);
out:
	वापस ret;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा karma_host_ढाँचा;

अटल पूर्णांक karma_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - karma_usb_ids) + karma_unusual_dev_list,
			&karma_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name = "Rio Karma/Bulk";
	us->transport = rio_karma_transport;
	us->transport_reset = usb_stor_Bulk_reset;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver karma_driver = अणु
	.name =		DRV_NAME,
	.probe =	karma_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	karma_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(karma_driver, karma_host_ढाँचा, DRV_NAME);
