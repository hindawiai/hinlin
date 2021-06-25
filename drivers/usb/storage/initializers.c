<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Special Initializers क्रम certain USB Mass Storage devices
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

#समावेश <linux/त्रुटिसं.स>

#समावेश "usb.h"
#समावेश "initializers.h"
#समावेश "debug.h"
#समावेश "transport.h"

/*
 * This places the Shuttle/SCM USB<->SCSI bridge devices in multi-target
 * mode
 */
पूर्णांक usb_stor_euscsi_init(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	usb_stor_dbg(us, "Attempting to init eUSCSI bridge...\n");
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x0C, USB_RECIP_INTERFACE | USB_TYPE_VENDOR,
			0x01, 0x0, शून्य, 0x0, 5 * HZ);
	usb_stor_dbg(us, "-- result is %d\n", result);

	वापस 0;
पूर्ण

/*
 * This function is required to activate all four slots on the UCR-61S2B
 * flash पढ़ोer
 */
पूर्णांक usb_stor_ucr61s2b_init(काष्ठा us_data *us)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap*) us->iobuf;
	काष्ठा bulk_cs_wrap *bcs = (काष्ठा bulk_cs_wrap*) us->iobuf;
	पूर्णांक res;
	अचिन्हित पूर्णांक partial;
	अटल अक्षर init_string[] = "\xec\x0a\x06\x00$PCCHIPS";

	usb_stor_dbg(us, "Sending UCR-61S2B initialization packet...\n");

	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->Tag = 0;
	bcb->DataTransferLength = cpu_to_le32(0);
	bcb->Flags = bcb->Lun = 0;
	bcb->Length = माप(init_string) - 1;
	स_रखो(bcb->CDB, 0, माप(bcb->CDB));
	स_नकल(bcb->CDB, init_string, माप(init_string) - 1);

	res = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe, bcb,
			US_BULK_CB_WRAP_LEN, &partial);
	अगर (res)
		वापस -EIO;

	usb_stor_dbg(us, "Getting status packet...\n");
	res = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe, bcs,
			US_BULK_CS_WRAP_LEN, &partial);
	अगर (res)
		वापस -EIO;

	वापस 0;
पूर्ण

/* This places the HUAWEI E220 devices in multi-port mode */
पूर्णांक usb_stor_huawei_e220_init(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
				      USB_REQ_SET_FEATURE,
				      USB_TYPE_STANDARD | USB_RECIP_DEVICE,
				      0x01, 0x0, शून्य, 0x0, 1 * HZ);
	usb_stor_dbg(us, "Huawei mode set result is %d\n", result);
	वापस 0;
पूर्ण
