<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek RTS51xx USB card पढ़ोer
 *
 * Copyright(c) 2009 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   wwang (wei_wang@realsil.com.cn)
 *   No. 450, Shenhu Road, Suzhou Industry Park, Suzhou, China
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/cdrom.h>

#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb_usual.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-realtek"

MODULE_DESCRIPTION("Driver for Realtek USB Card Reader");
MODULE_AUTHOR("wwang <wei_wang@realsil.com.cn>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

अटल पूर्णांक स्वतः_delink_en = 1;
module_param(स्वतः_delink_en, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(स्वतः_delink_en, "auto delink mode (0=firmware, 1=software [default])");

#अगर_घोषित CONFIG_REALTEK_AUTOPM
अटल पूर्णांक ss_en = 1;
module_param(ss_en, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ss_en, "enable selective suspend");

अटल पूर्णांक ss_delay = 50;
module_param(ss_delay, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ss_delay,
		 "seconds to delay before entering selective suspend");

क्रमागत RTS51X_STAT अणु
	RTS51X_STAT_INIT,
	RTS51X_STAT_IDLE,
	RTS51X_STAT_RUN,
	RTS51X_STAT_SS
पूर्ण;

#घोषणा POLLING_INTERVAL	50

#घोषणा rts51x_set_stat(chip, stat)	\
	((chip)->state = (क्रमागत RTS51X_STAT)(stat))
#घोषणा rts51x_get_stat(chip)		((chip)->state)

#घोषणा SET_LUN_READY(chip, lun)	((chip)->lun_पढ़ोy |= ((u8)1 << (lun)))
#घोषणा CLR_LUN_READY(chip, lun)	((chip)->lun_पढ़ोy &= ~((u8)1 << (lun)))
#घोषणा TST_LUN_READY(chip, lun)	((chip)->lun_पढ़ोy & ((u8)1 << (lun)))

#पूर्ण_अगर

काष्ठा rts51x_status अणु
	u16 vid;
	u16 pid;
	u8 cur_lun;
	u8 card_type;
	u8 total_lun;
	u16 fw_ver;
	u8 phy_exist;
	u8 multi_flag;
	u8 multi_card;
	u8 log_exist;
	जोड़ अणु
		u8 detailed_type1;
		u8 detailed_type2;
	पूर्ण detailed_type;
	u8 function[2];
पूर्ण;

काष्ठा rts51x_chip अणु
	u16 venकरोr_id;
	u16 product_id;
	अक्षर max_lun;

	काष्ठा rts51x_status *status;
	पूर्णांक status_len;

	u32 flag;
	काष्ठा us_data *us;

#अगर_घोषित CONFIG_REALTEK_AUTOPM
	काष्ठा समयr_list rts51x_suspend_समयr;
	अचिन्हित दीर्घ समयr_expires;
	पूर्णांक pwr_state;
	u8 lun_पढ़ोy;
	क्रमागत RTS51X_STAT state;
	पूर्णांक support_स्वतः_delink;
#पूर्ण_अगर
	/* used to back up the protocol chosen in probe1 phase */
	proto_cmnd proto_handler_backup;
पूर्ण;

/* flag definition */
#घोषणा FLIDX_AUTO_DELINK		0x01

#घोषणा SCSI_LUN(srb)			((srb)->device->lun)

/* Bit Operation */
#घोषणा SET_BIT(data, idx)		((data) |= 1 << (idx))
#घोषणा CLR_BIT(data, idx)		((data) &= ~(1 << (idx)))
#घोषणा CHK_BIT(data, idx)		((data) & (1 << (idx)))

#घोषणा SET_AUTO_DELINK(chip)		((chip)->flag |= FLIDX_AUTO_DELINK)
#घोषणा CLR_AUTO_DELINK(chip)		((chip)->flag &= ~FLIDX_AUTO_DELINK)
#घोषणा CHK_AUTO_DELINK(chip)		((chip)->flag & FLIDX_AUTO_DELINK)

#घोषणा RTS51X_GET_VID(chip)		((chip)->venकरोr_id)
#घोषणा RTS51X_GET_PID(chip)		((chip)->product_id)

#घोषणा VENDOR_ID(chip)			((chip)->status[0].vid)
#घोषणा PRODUCT_ID(chip)		((chip)->status[0].pid)
#घोषणा FW_VERSION(chip)		((chip)->status[0].fw_ver)
#घोषणा STATUS_LEN(chip)		((chip)->status_len)

#घोषणा STATUS_SUCCESS		0
#घोषणा STATUS_FAIL		1

/* Check card पढ़ोer function */
#घोषणा SUPPORT_DETAILED_TYPE1(chip)	\
		CHK_BIT((chip)->status[0].function[0], 1)
#घोषणा SUPPORT_OT(chip)		\
		CHK_BIT((chip)->status[0].function[0], 2)
#घोषणा SUPPORT_OC(chip)		\
		CHK_BIT((chip)->status[0].function[0], 3)
#घोषणा SUPPORT_AUTO_DELINK(chip)	\
		CHK_BIT((chip)->status[0].function[0], 4)
#घोषणा SUPPORT_SDIO(chip)		\
		CHK_BIT((chip)->status[0].function[1], 0)
#घोषणा SUPPORT_DETAILED_TYPE2(chip)	\
		CHK_BIT((chip)->status[0].function[1], 1)

#घोषणा CHECK_PID(chip, pid)		(RTS51X_GET_PID(chip) == (pid))
#घोषणा CHECK_FW_VER(chip, fw_ver)	(FW_VERSION(chip) == (fw_ver))
#घोषणा CHECK_ID(chip, pid, fw_ver)	\
		(CHECK_PID((chip), (pid)) && CHECK_FW_VER((chip), (fw_ver)))

अटल पूर्णांक init_realtek_cr(काष्ठा us_data *us);

/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु\
	USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
	.driver_info = (flags) \
पूर्ण

अटल स्थिर काष्ठा usb_device_id realtek_cr_ids[] = अणु
#	include "unusual_realtek.h"
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, realtek_cr_ids);

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

अटल काष्ठा us_unusual_dev realtek_cr_unusual_dev_list[] = अणु
#	include "unusual_realtek.h"
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV

अटल पूर्णांक rts51x_bulk_transport(काष्ठा us_data *us, u8 lun,
				 u8 *cmd, पूर्णांक cmd_len, u8 *buf, पूर्णांक buf_len,
				 क्रमागत dma_data_direction dir, पूर्णांक *act_len)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *)us->iobuf;
	काष्ठा bulk_cs_wrap *bcs = (काष्ठा bulk_cs_wrap *)us->iobuf;
	पूर्णांक result;
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक cswlen;
	अचिन्हित पूर्णांक cbwlen = US_BULK_CB_WRAP_LEN;

	/* set up the command wrapper */
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = cpu_to_le32(buf_len);
	bcb->Flags = (dir == DMA_FROM_DEVICE) ? US_BULK_FLAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Lun = lun;
	bcb->Length = cmd_len;

	/* copy the command payload */
	स_रखो(bcb->CDB, 0, माप(bcb->CDB));
	स_नकल(bcb->CDB, cmd, bcb->Length);

	/* send it to out endpoपूर्णांक */
	result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
					    bcb, cbwlen, शून्य);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* DATA STAGE */
	/* send/receive data payload, अगर there is any */

	अगर (buf && buf_len) अणु
		अचिन्हित पूर्णांक pipe = (dir == DMA_FROM_DEVICE) ?
		    us->recv_bulk_pipe : us->send_bulk_pipe;
		result = usb_stor_bulk_transfer_buf(us, pipe,
						    buf, buf_len, शून्य);
		अगर (result == USB_STOR_XFER_ERROR)
			वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* get CSW क्रम device status */
	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
					    bcs, US_BULK_CS_WRAP_LEN, &cswlen);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* check bulk status */
	अगर (bcs->Signature != cpu_to_le32(US_BULK_CS_SIGN)) अणु
		usb_stor_dbg(us, "Signature mismatch: got %08X, expecting %08X\n",
			     le32_to_cpu(bcs->Signature), US_BULK_CS_SIGN);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	residue = bcs->Residue;
	अगर (bcs->Tag != us->tag)
		वापस USB_STOR_TRANSPORT_ERROR;

	/*
	 * try to compute the actual residue, based on how much data
	 * was really transferred and what the device tells us
	 */
	अगर (residue)
		residue = residue < buf_len ? residue : buf_len;

	अगर (act_len)
		*act_len = buf_len - residue;

	/* based on the status code, we report good or bad */
	चयन (bcs->Status) अणु
	हाल US_BULK_STAT_OK:
		/* command good -- note that data could be लघु */
		वापस USB_STOR_TRANSPORT_GOOD;

	हाल US_BULK_STAT_FAIL:
		/* command failed */
		वापस USB_STOR_TRANSPORT_FAILED;

	हाल US_BULK_STAT_PHASE:
		/*
		 * phase error -- note that a transport reset will be
		 * invoked by the invoke_transport() function
		 */
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* we should never get here, but अगर we करो, we're in trouble */
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण

अटल पूर्णांक rts51x_bulk_transport_special(काष्ठा us_data *us, u8 lun,
				 u8 *cmd, पूर्णांक cmd_len, u8 *buf, पूर्णांक buf_len,
				 क्रमागत dma_data_direction dir, पूर्णांक *act_len)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा bulk_cs_wrap *bcs = (काष्ठा bulk_cs_wrap *) us->iobuf;
	पूर्णांक result;
	अचिन्हित पूर्णांक cswlen;
	अचिन्हित पूर्णांक cbwlen = US_BULK_CB_WRAP_LEN;

	/* set up the command wrapper */
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = cpu_to_le32(buf_len);
	bcb->Flags = (dir == DMA_FROM_DEVICE) ? US_BULK_FLAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Lun = lun;
	bcb->Length = cmd_len;

	/* copy the command payload */
	स_रखो(bcb->CDB, 0, माप(bcb->CDB));
	स_नकल(bcb->CDB, cmd, bcb->Length);

	/* send it to out endpoपूर्णांक */
	result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
				bcb, cbwlen, शून्य);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* DATA STAGE */
	/* send/receive data payload, अगर there is any */

	अगर (buf && buf_len) अणु
		अचिन्हित पूर्णांक pipe = (dir == DMA_FROM_DEVICE) ?
				us->recv_bulk_pipe : us->send_bulk_pipe;
		result = usb_stor_bulk_transfer_buf(us, pipe,
				buf, buf_len, शून्य);
		अगर (result == USB_STOR_XFER_ERROR)
			वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* get CSW क्रम device status */
	result = usb_bulk_msg(us->pusb_dev, us->recv_bulk_pipe, bcs,
			US_BULK_CS_WRAP_LEN, &cswlen, 250);
	वापस result;
पूर्ण

/* Determine what the maximum LUN supported is */
अटल पूर्णांक rts51x_get_max_lun(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	/* issue the command */
	us->iobuf[0] = 0;
	result = usb_stor_control_msg(us, us->recv_ctrl_pipe,
				      US_BULK_GET_MAX_LUN,
				      USB_सूची_IN | USB_TYPE_CLASS |
				      USB_RECIP_INTERFACE,
				      0, us->अगरnum, us->iobuf, 1, 10 * HZ);

	usb_stor_dbg(us, "GetMaxLUN command result is %d, data is %d\n",
		     result, us->iobuf[0]);

	/* अगर we have a successful request, वापस the result */
	अगर (result > 0)
		वापस us->iobuf[0];

	वापस 0;
पूर्ण

अटल पूर्णांक rts51x_पढ़ो_mem(काष्ठा us_data *us, u16 addr, u8 *data, u16 len)
अणु
	पूर्णांक retval;
	u8 cmnd[12] = अणु 0 पूर्ण;
	u8 *buf;

	buf = kदो_स्मृति(len, GFP_NOIO);
	अगर (buf == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "addr = 0x%x, len = %d\n", addr, len);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0D;
	cmnd[2] = (u8) (addr >> 8);
	cmnd[3] = (u8) addr;
	cmnd[4] = (u8) (len >> 8);
	cmnd[5] = (u8) len;

	retval = rts51x_bulk_transport(us, 0, cmnd, 12,
				       buf, len, DMA_FROM_DEVICE, शून्य);
	अगर (retval != USB_STOR_TRANSPORT_GOOD) अणु
		kमुक्त(buf);
		वापस -EIO;
	पूर्ण

	स_नकल(data, buf, len);
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक rts51x_ग_लिखो_mem(काष्ठा us_data *us, u16 addr, u8 *data, u16 len)
अणु
	पूर्णांक retval;
	u8 cmnd[12] = अणु 0 पूर्ण;
	u8 *buf;

	buf = kmemdup(data, len, GFP_NOIO);
	अगर (buf == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "addr = 0x%x, len = %d\n", addr, len);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0E;
	cmnd[2] = (u8) (addr >> 8);
	cmnd[3] = (u8) addr;
	cmnd[4] = (u8) (len >> 8);
	cmnd[5] = (u8) len;

	retval = rts51x_bulk_transport(us, 0, cmnd, 12,
				       buf, len, DMA_TO_DEVICE, शून्य);
	kमुक्त(buf);
	अगर (retval != USB_STOR_TRANSPORT_GOOD)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक rts51x_पढ़ो_status(काष्ठा us_data *us,
			      u8 lun, u8 *status, पूर्णांक len, पूर्णांक *actlen)
अणु
	पूर्णांक retval;
	u8 cmnd[12] = अणु 0 पूर्ण;
	u8 *buf;

	buf = kदो_स्मृति(len, GFP_NOIO);
	अगर (buf == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "lun = %d\n", lun);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x09;

	retval = rts51x_bulk_transport(us, lun, cmnd, 12,
				       buf, len, DMA_FROM_DEVICE, actlen);
	अगर (retval != USB_STOR_TRANSPORT_GOOD) अणु
		kमुक्त(buf);
		वापस -EIO;
	पूर्ण

	स_नकल(status, buf, len);
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक rts51x_check_status(काष्ठा us_data *us, u8 lun)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	पूर्णांक retval;
	u8 buf[16];

	retval = rts51x_पढ़ो_status(us, lun, buf, 16, &(chip->status_len));
	अगर (retval != STATUS_SUCCESS)
		वापस -EIO;

	usb_stor_dbg(us, "chip->status_len = %d\n", chip->status_len);

	chip->status[lun].vid = ((u16) buf[0] << 8) | buf[1];
	chip->status[lun].pid = ((u16) buf[2] << 8) | buf[3];
	chip->status[lun].cur_lun = buf[4];
	chip->status[lun].card_type = buf[5];
	chip->status[lun].total_lun = buf[6];
	chip->status[lun].fw_ver = ((u16) buf[7] << 8) | buf[8];
	chip->status[lun].phy_exist = buf[9];
	chip->status[lun].multi_flag = buf[10];
	chip->status[lun].multi_card = buf[11];
	chip->status[lun].log_exist = buf[12];
	अगर (chip->status_len == 16) अणु
		chip->status[lun].detailed_type.detailed_type1 = buf[13];
		chip->status[lun].function[0] = buf[14];
		chip->status[lun].function[1] = buf[15];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enable_oscillator(काष्ठा us_data *us)
अणु
	पूर्णांक retval;
	u8 value;

	retval = rts51x_पढ़ो_mem(us, 0xFE77, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	value |= 0x04;
	retval = rts51x_ग_लिखो_mem(us, 0xFE77, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	retval = rts51x_पढ़ो_mem(us, 0xFE77, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	अगर (!(value & 0x04))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक __करो_config_स्वतःdelink(काष्ठा us_data *us, u8 *data, u16 len)
अणु
	पूर्णांक retval;
	u8 cmnd[12] = अणु0पूर्ण;
	u8 *buf;

	usb_stor_dbg(us, "addr = 0xfe47, len = %d\n", len);

	buf = kmemdup(data, len, GFP_NOIO);
	अगर (!buf)
		वापस USB_STOR_TRANSPORT_ERROR;

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0E;
	cmnd[2] = 0xfe;
	cmnd[3] = 0x47;
	cmnd[4] = (u8)(len >> 8);
	cmnd[5] = (u8)len;

	retval = rts51x_bulk_transport_special(us, 0, cmnd, 12, buf, len, DMA_TO_DEVICE, शून्य);
	kमुक्त(buf);
	अगर (retval != USB_STOR_TRANSPORT_GOOD) अणु
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_config_स्वतःdelink(काष्ठा us_data *us, पूर्णांक enable, पूर्णांक क्रमce)
अणु
	पूर्णांक retval;
	u8 value;

	retval = rts51x_पढ़ो_mem(us, 0xFE47, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	अगर (enable) अणु
		अगर (क्रमce)
			value |= 0x03;
		अन्यथा
			value |= 0x01;
	पूर्ण अन्यथा अणु
		value &= ~0x03;
	पूर्ण

	usb_stor_dbg(us, "set 0xfe47 to 0x%x\n", value);

	/* retval = rts51x_ग_लिखो_mem(us, 0xFE47, &value, 1); */
	retval = __करो_config_स्वतःdelink(us, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक config_स्वतःdelink_after_घातer_on(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	पूर्णांक retval;
	u8 value;

	अगर (!CHK_AUTO_DELINK(chip))
		वापस 0;

	retval = rts51x_पढ़ो_mem(us, 0xFE47, &value, 1);
	अगर (retval < 0)
		वापस -EIO;

	अगर (स्वतः_delink_en) अणु
		CLR_BIT(value, 0);
		CLR_BIT(value, 1);
		SET_BIT(value, 2);

		अगर (CHECK_ID(chip, 0x0138, 0x3882))
			CLR_BIT(value, 2);

		SET_BIT(value, 7);

		/* retval = rts51x_ग_लिखो_mem(us, 0xFE47, &value, 1); */
		retval = __करो_config_स्वतःdelink(us, &value, 1);
		अगर (retval < 0)
			वापस -EIO;

		retval = enable_oscillator(us);
		अगर (retval == 0)
			(व्योम)करो_config_स्वतःdelink(us, 1, 0);
	पूर्ण अन्यथा अणु
		/* Autodelink controlled by firmware */

		SET_BIT(value, 2);

		अगर (CHECK_ID(chip, 0x0138, 0x3882))
			CLR_BIT(value, 2);

		अगर (CHECK_ID(chip, 0x0159, 0x5889) ||
		    CHECK_ID(chip, 0x0138, 0x3880)) अणु
			CLR_BIT(value, 0);
			CLR_BIT(value, 7);
		पूर्ण

		/* retval = rts51x_ग_लिखो_mem(us, 0xFE47, &value, 1); */
		retval = __करो_config_स्वतःdelink(us, &value, 1);
		अगर (retval < 0)
			वापस -EIO;

		अगर (CHECK_ID(chip, 0x0159, 0x5888)) अणु
			value = 0xFF;
			retval = rts51x_ग_लिखो_mem(us, 0xFE79, &value, 1);
			अगर (retval < 0)
				वापस -EIO;

			value = 0x01;
			retval = rts51x_ग_लिखो_mem(us, 0x48, &value, 1);
			अगर (retval < 0)
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक config_स्वतःdelink_beक्रमe_घातer_करोwn(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	पूर्णांक retval;
	u8 value;

	अगर (!CHK_AUTO_DELINK(chip))
		वापस 0;

	अगर (स्वतः_delink_en) अणु
		retval = rts51x_पढ़ो_mem(us, 0xFE77, &value, 1);
		अगर (retval < 0)
			वापस -EIO;

		SET_BIT(value, 2);
		retval = rts51x_ग_लिखो_mem(us, 0xFE77, &value, 1);
		अगर (retval < 0)
			वापस -EIO;

		अगर (CHECK_ID(chip, 0x0159, 0x5888)) अणु
			value = 0x01;
			retval = rts51x_ग_लिखो_mem(us, 0x48, &value, 1);
			अगर (retval < 0)
				वापस -EIO;
		पूर्ण

		retval = rts51x_पढ़ो_mem(us, 0xFE47, &value, 1);
		अगर (retval < 0)
			वापस -EIO;

		SET_BIT(value, 0);
		अगर (CHECK_ID(chip, 0x0138, 0x3882))
			SET_BIT(value, 2);
		retval = rts51x_ग_लिखो_mem(us, 0xFE77, &value, 1);
		अगर (retval < 0)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		अगर (CHECK_ID(chip, 0x0159, 0x5889) ||
		    CHECK_ID(chip, 0x0138, 0x3880) ||
		    CHECK_ID(chip, 0x0138, 0x3882)) अणु
			retval = rts51x_पढ़ो_mem(us, 0xFE47, &value, 1);
			अगर (retval < 0)
				वापस -EIO;

			अगर (CHECK_ID(chip, 0x0159, 0x5889) ||
			    CHECK_ID(chip, 0x0138, 0x3880)) अणु
				SET_BIT(value, 0);
				SET_BIT(value, 7);
			पूर्ण

			अगर (CHECK_ID(chip, 0x0138, 0x3882))
				SET_BIT(value, 2);

			/* retval = rts51x_ग_लिखो_mem(us, 0xFE47, &value, 1); */
			retval = __करो_config_स्वतःdelink(us, &value, 1);
			अगर (retval < 0)
				वापस -EIO;
		पूर्ण

		अगर (CHECK_ID(chip, 0x0159, 0x5888)) अणु
			value = 0x01;
			retval = rts51x_ग_लिखो_mem(us, 0x48, &value, 1);
			अगर (retval < 0)
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fw5895_init(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	पूर्णांक retval;
	u8 val;

	अगर ((PRODUCT_ID(chip) != 0x0158) || (FW_VERSION(chip) != 0x5895)) अणु
		usb_stor_dbg(us, "Not the specified device, return immediately!\n");
	पूर्ण अन्यथा अणु
		retval = rts51x_पढ़ो_mem(us, 0xFD6F, &val, 1);
		अगर (retval == STATUS_SUCCESS && (val & 0x1F) == 0) अणु
			val = 0x1F;
			retval = rts51x_ग_लिखो_mem(us, 0xFD70, &val, 1);
			अगर (retval != STATUS_SUCCESS)
				usb_stor_dbg(us, "Write memory fail\n");
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "Read memory fail, OR (val & 0x1F) != 0\n");
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_REALTEK_AUTOPM
अटल व्योम fw5895_set_mmc_wp(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	पूर्णांक retval;
	u8 buf[13];

	अगर ((PRODUCT_ID(chip) != 0x0158) || (FW_VERSION(chip) != 0x5895)) अणु
		usb_stor_dbg(us, "Not the specified device, return immediately!\n");
	पूर्ण अन्यथा अणु
		retval = rts51x_पढ़ो_mem(us, 0xFD6F, buf, 1);
		अगर (retval == STATUS_SUCCESS && (buf[0] & 0x24) == 0x24) अणु
			/* SD Exist and SD WP */
			retval = rts51x_पढ़ो_mem(us, 0xD04E, buf, 1);
			अगर (retval == STATUS_SUCCESS) अणु
				buf[0] |= 0x04;
				retval = rts51x_ग_लिखो_mem(us, 0xFD70, buf, 1);
				अगर (retval != STATUS_SUCCESS)
					usb_stor_dbg(us, "Write memory fail\n");
			पूर्ण अन्यथा अणु
				usb_stor_dbg(us, "Read memory fail\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "Read memory fail, OR (buf[0]&0x24)!=0x24\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rts51x_modi_suspend_समयr(काष्ठा rts51x_chip *chip)
अणु
	काष्ठा us_data *us = chip->us;

	usb_stor_dbg(us, "state:%d\n", rts51x_get_stat(chip));

	chip->समयr_expires = jअगरfies + msecs_to_jअगरfies(1000*ss_delay);
	mod_समयr(&chip->rts51x_suspend_समयr, chip->समयr_expires);
पूर्ण

अटल व्योम rts51x_suspend_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा rts51x_chip *chip = from_समयr(chip, t, rts51x_suspend_समयr);
	काष्ठा us_data *us = chip->us;

	चयन (rts51x_get_stat(chip)) अणु
	हाल RTS51X_STAT_INIT:
	हाल RTS51X_STAT_RUN:
		rts51x_modi_suspend_समयr(chip);
		अवरोध;
	हाल RTS51X_STAT_IDLE:
	हाल RTS51X_STAT_SS:
		usb_stor_dbg(us, "RTS51X_STAT_SS, power.usage:%d\n",
			     atomic_पढ़ो(&us->pusb_पूर्णांकf->dev.घातer.usage_count));

		अगर (atomic_पढ़ो(&us->pusb_पूर्णांकf->dev.घातer.usage_count) > 0) अणु
			usb_stor_dbg(us, "Ready to enter SS state\n");
			rts51x_set_stat(chip, RTS51X_STAT_SS);
			/* ignore mass storage पूर्णांकerface's children */
			pm_suspend_ignore_children(&us->pusb_पूर्णांकf->dev, true);
			usb_स्वतःpm_put_पूर्णांकerface_async(us->pusb_पूर्णांकf);
			usb_stor_dbg(us, "RTS51X_STAT_SS 01, power.usage:%d\n",
				     atomic_पढ़ो(&us->pusb_पूर्णांकf->dev.घातer.usage_count));
		पूर्ण
		अवरोध;
	शेष:
		usb_stor_dbg(us, "Unknown state !!!\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक working_scsi(काष्ठा scsi_cmnd *srb)
अणु
	अगर ((srb->cmnd[0] == TEST_UNIT_READY) ||
	    (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL)) अणु
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम rts51x_invoke_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip = (काष्ठा rts51x_chip *)(us->extra);
	अटल पूर्णांक card_first_show = 1;
	अटल u8 media_not_present[] = अणु 0x70, 0, 0x02, 0, 0, 0, 0,
		10, 0, 0, 0, 0, 0x3A, 0, 0, 0, 0, 0
	पूर्ण;
	अटल u8 invalid_cmd_field[] = अणु 0x70, 0, 0x05, 0, 0, 0, 0,
		10, 0, 0, 0, 0, 0x24, 0, 0, 0, 0, 0
	पूर्ण;
	पूर्णांक ret;

	अगर (working_scsi(srb)) अणु
		usb_stor_dbg(us, "working scsi, power.usage:%d\n",
			     atomic_पढ़ो(&us->pusb_पूर्णांकf->dev.घातer.usage_count));

		अगर (atomic_पढ़ो(&us->pusb_पूर्णांकf->dev.घातer.usage_count) <= 0) अणु
			ret = usb_स्वतःpm_get_पूर्णांकerface(us->pusb_पूर्णांकf);
			usb_stor_dbg(us, "working scsi, ret=%d\n", ret);
		पूर्ण
		अगर (rts51x_get_stat(chip) != RTS51X_STAT_RUN)
			rts51x_set_stat(chip, RTS51X_STAT_RUN);
		chip->proto_handler_backup(srb, us);
	पूर्ण अन्यथा अणु
		अगर (rts51x_get_stat(chip) == RTS51X_STAT_SS) अणु
			usb_stor_dbg(us, "NOT working scsi\n");
			अगर ((srb->cmnd[0] == TEST_UNIT_READY) &&
			    (chip->pwr_state == US_SUSPEND)) अणु
				अगर (TST_LUN_READY(chip, srb->device->lun)) अणु
					srb->result = SAM_STAT_GOOD;
				पूर्ण अन्यथा अणु
					srb->result = SAM_STAT_CHECK_CONDITION;
					स_नकल(srb->sense_buffer,
					       media_not_present,
					       US_SENSE_SIZE);
				पूर्ण
				usb_stor_dbg(us, "TEST_UNIT_READY\n");
				जाओ out;
			पूर्ण
			अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) अणु
				पूर्णांक prevent = srb->cmnd[4] & 0x1;
				अगर (prevent) अणु
					srb->result = SAM_STAT_CHECK_CONDITION;
					स_नकल(srb->sense_buffer,
					       invalid_cmd_field,
					       US_SENSE_SIZE);
				पूर्ण अन्यथा अणु
					srb->result = SAM_STAT_GOOD;
				पूर्ण
				usb_stor_dbg(us, "ALLOW_MEDIUM_REMOVAL\n");
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "NOT working scsi, not SS\n");
			chip->proto_handler_backup(srb, us);
			/* Check whether card is plugged in */
			अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
				अगर (srb->result == SAM_STAT_GOOD) अणु
					SET_LUN_READY(chip, srb->device->lun);
					अगर (card_first_show) अणु
						card_first_show = 0;
						fw5895_set_mmc_wp(us);
					पूर्ण
				पूर्ण अन्यथा अणु
					CLR_LUN_READY(chip, srb->device->lun);
					card_first_show = 1;
				पूर्ण
			पूर्ण
			अगर (rts51x_get_stat(chip) != RTS51X_STAT_IDLE)
				rts51x_set_stat(chip, RTS51X_STAT_IDLE);
		पूर्ण
	पूर्ण
out:
	usb_stor_dbg(us, "state:%d\n", rts51x_get_stat(chip));
	अगर (rts51x_get_stat(chip) == RTS51X_STAT_RUN)
		rts51x_modi_suspend_समयr(chip);
पूर्ण

अटल पूर्णांक realtek_cr_स्वतःsuspend_setup(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip;
	काष्ठा rts51x_status *status = शून्य;
	u8 buf[16];
	पूर्णांक retval;

	chip = (काष्ठा rts51x_chip *)us->extra;
	chip->support_स्वतः_delink = 0;
	chip->pwr_state = US_RESUME;
	chip->lun_पढ़ोy = 0;
	rts51x_set_stat(chip, RTS51X_STAT_INIT);

	retval = rts51x_पढ़ो_status(us, 0, buf, 16, &(chip->status_len));
	अगर (retval != STATUS_SUCCESS) अणु
		usb_stor_dbg(us, "Read status fail\n");
		वापस -EIO;
	पूर्ण
	status = chip->status;
	status->vid = ((u16) buf[0] << 8) | buf[1];
	status->pid = ((u16) buf[2] << 8) | buf[3];
	status->cur_lun = buf[4];
	status->card_type = buf[5];
	status->total_lun = buf[6];
	status->fw_ver = ((u16) buf[7] << 8) | buf[8];
	status->phy_exist = buf[9];
	status->multi_flag = buf[10];
	status->multi_card = buf[11];
	status->log_exist = buf[12];
	अगर (chip->status_len == 16) अणु
		status->detailed_type.detailed_type1 = buf[13];
		status->function[0] = buf[14];
		status->function[1] = buf[15];
	पूर्ण

	/* back up the proto_handler in us->extra */
	chip = (काष्ठा rts51x_chip *)(us->extra);
	chip->proto_handler_backup = us->proto_handler;
	/* Set the स्वतःsuspend_delay to 0 */
	pm_runसमय_set_स्वतःsuspend_delay(&us->pusb_dev->dev, 0);
	/* override us->proto_handler setted in get_protocol() */
	us->proto_handler = rts51x_invoke_transport;

	chip->समयr_expires = 0;
	समयr_setup(&chip->rts51x_suspend_समयr, rts51x_suspend_समयr_fn, 0);
	fw5895_init(us);

	/* enable स्वतःsuspend function of the usb device */
	usb_enable_स्वतःsuspend(us->pusb_dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम realtek_cr_deकाष्ठाor(व्योम *extra)
अणु
	काष्ठा rts51x_chip *chip = extra;

	अगर (!chip)
		वापस;

#अगर_घोषित CONFIG_REALTEK_AUTOPM
	अगर (ss_en) अणु
		del_समयr(&chip->rts51x_suspend_समयr);
		chip->समयr_expires = 0;
	पूर्ण
#पूर्ण_अगर
	kमुक्त(chip->status);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक realtek_cr_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message)
अणु
	काष्ठा us_data *us = usb_get_पूर्णांकfdata(अगरace);

	/* रुको until no command is running */
	mutex_lock(&us->dev_mutex);

	config_स्वतःdelink_beक्रमe_घातer_करोwn(us);

	mutex_unlock(&us->dev_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक realtek_cr_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा us_data *us = usb_get_पूर्णांकfdata(अगरace);

	fw5895_init(us);
	config_स्वतःdelink_after_घातer_on(us);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा realtek_cr_suspend	शून्य
#घोषणा realtek_cr_resume	शून्य
#पूर्ण_अगर

अटल पूर्णांक init_realtek_cr(काष्ठा us_data *us)
अणु
	काष्ठा rts51x_chip *chip;
	पूर्णांक size, i, retval;

	chip = kzalloc(माप(काष्ठा rts51x_chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	us->extra = chip;
	us->extra_deकाष्ठाor = realtek_cr_deकाष्ठाor;
	us->max_lun = chip->max_lun = rts51x_get_max_lun(us);
	chip->us = us;

	usb_stor_dbg(us, "chip->max_lun = %d\n", chip->max_lun);

	size = (chip->max_lun + 1) * माप(काष्ठा rts51x_status);
	chip->status = kzalloc(size, GFP_KERNEL);
	अगर (!chip->status)
		जाओ INIT_FAIL;

	क्रम (i = 0; i <= (पूर्णांक)(chip->max_lun); i++) अणु
		retval = rts51x_check_status(us, (u8) i);
		अगर (retval < 0)
			जाओ INIT_FAIL;
	पूर्ण

	अगर (CHECK_PID(chip, 0x0138) || CHECK_PID(chip, 0x0158) ||
	    CHECK_PID(chip, 0x0159)) अणु
		अगर (CHECK_FW_VER(chip, 0x5888) || CHECK_FW_VER(chip, 0x5889) ||
				CHECK_FW_VER(chip, 0x5901))
			SET_AUTO_DELINK(chip);
		अगर (STATUS_LEN(chip) == 16) अणु
			अगर (SUPPORT_AUTO_DELINK(chip))
				SET_AUTO_DELINK(chip);
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_REALTEK_AUTOPM
	अगर (ss_en)
		realtek_cr_स्वतःsuspend_setup(us);
#पूर्ण_अगर

	usb_stor_dbg(us, "chip->flag = 0x%x\n", chip->flag);

	(व्योम)config_स्वतःdelink_after_घातer_on(us);

	वापस 0;

INIT_FAIL:
	अगर (us->extra) अणु
		kमुक्त(chip->status);
		kमुक्त(us->extra);
		us->extra = शून्य;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा realtek_cr_host_ढाँचा;

अटल पूर्णांक realtek_cr_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	dev_dbg(&पूर्णांकf->dev, "Probe Realtek Card Reader!\n");

	result = usb_stor_probe1(&us, पूर्णांकf, id,
				 (id - realtek_cr_ids) +
				 realtek_cr_unusual_dev_list,
				 &realtek_cr_host_ढाँचा);
	अगर (result)
		वापस result;

	result = usb_stor_probe2(us);

	वापस result;
पूर्ण

अटल काष्ठा usb_driver realtek_cr_driver = अणु
	.name = DRV_NAME,
	.probe = realtek_cr_probe,
	.disconnect = usb_stor_disconnect,
	/* .suspend =      usb_stor_suspend, */
	/* .resume =       usb_stor_resume, */
	.reset_resume = usb_stor_reset_resume,
	.suspend = realtek_cr_suspend,
	.resume = realtek_cr_resume,
	.pre_reset = usb_stor_pre_reset,
	.post_reset = usb_stor_post_reset,
	.id_table = realtek_cr_ids,
	.soft_unbind = 1,
	.supports_स्वतःsuspend = 1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(realtek_cr_driver, realtek_cr_host_ढाँचा, DRV_NAME);
