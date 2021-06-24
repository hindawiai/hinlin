<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>

#समावेश <linux/mei_cl_bus.h>

#समावेश "mei_dev.h"
#समावेश "client.h"

#घोषणा MEI_UUID_NFC_INFO UUID_LE(0xd2de1625, 0x382d, 0x417d, \
			0x48, 0xa4, 0xef, 0xab, 0xba, 0x8a, 0x12, 0x06)

अटल स्थिर uuid_le mei_nfc_info_guid = MEI_UUID_NFC_INFO;

#घोषणा MEI_UUID_NFC_HCI UUID_LE(0x0bb17a78, 0x2a8e, 0x4c50, \
			0x94, 0xd4, 0x50, 0x26, 0x67, 0x23, 0x77, 0x5c)

#घोषणा MEI_UUID_WD UUID_LE(0x05B79A6F, 0x4628, 0x4D7F, \
			    0x89, 0x9D, 0xA9, 0x15, 0x14, 0xCB, 0x32, 0xAB)

#घोषणा MEI_UUID_MKHIF_FIX UUID_LE(0x55213584, 0x9a29, 0x4916, \
			0xba, 0xdf, 0xf, 0xb7, 0xed, 0x68, 0x2a, 0xeb)

#घोषणा MEI_UUID_HDCP UUID_LE(0xB638AB7E, 0x94E2, 0x4EA2, \
			      0xA5, 0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)

#घोषणा MEI_UUID_PAVP UUID_LE(0xfbf6fcf1, 0x96cf, 0x4e2e, 0xA6, \
			      0xa6, 0x1b, 0xab, 0x8c, 0xbe, 0x36, 0xb1)

#घोषणा MEI_UUID_ANY शून्य_UUID_LE

/**
 * number_of_connections - determine whether an client be on the bus
 *    according number of connections
 *    We support only clients:
 *       1. with single connection
 *       2. and fixed clients (max_number_of_connections == 0)
 *
 * @cldev: me clients device
 */
अटल व्योम number_of_connections(काष्ठा mei_cl_device *cldev)
अणु
	अगर (cldev->me_cl->props.max_number_of_connections > 1)
		cldev->करो_match = 0;
पूर्ण

/**
 * blacklist - blacklist a client from the bus
 *
 * @cldev: me clients device
 */
अटल व्योम blacklist(काष्ठा mei_cl_device *cldev)
अणु
	cldev->करो_match = 0;
पूर्ण

/**
 * whitelist - क्रमcefully whitelist client
 *
 * @cldev: me clients device
 */
अटल व्योम whitelist(काष्ठा mei_cl_device *cldev)
अणु
	cldev->करो_match = 1;
पूर्ण

#घोषणा OSTYPE_LINUX    2
काष्ठा mei_os_ver अणु
	__le16 build;
	__le16 reserved1;
	u8  os_type;
	u8  major;
	u8  minor;
	u8  reserved2;
पूर्ण __packed;

#घोषणा MKHI_FEATURE_PTT 0x10

काष्ठा mkhi_rule_id अणु
	__le16 rule_type;
	u8 feature_id;
	u8 reserved;
पूर्ण __packed;

काष्ठा mkhi_fwcaps अणु
	काष्ठा mkhi_rule_id id;
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा mkhi_fw_ver_block अणु
	u16 minor;
	u8 major;
	u8 platक्रमm;
	u16 buildno;
	u16 hotfix;
पूर्ण __packed;

काष्ठा mkhi_fw_ver अणु
	काष्ठा mkhi_fw_ver_block ver[MEI_MAX_FW_VER_BLOCKS];
पूर्ण __packed;

#घोषणा MKHI_FWCAPS_GROUP_ID 0x3
#घोषणा MKHI_FWCAPS_SET_OS_VER_APP_RULE_CMD 6
#घोषणा MKHI_GEN_GROUP_ID 0xFF
#घोषणा MKHI_GEN_GET_FW_VERSION_CMD 0x2
काष्ठा mkhi_msg_hdr अणु
	u8  group_id;
	u8  command;
	u8  reserved;
	u8  result;
पूर्ण __packed;

काष्ठा mkhi_msg अणु
	काष्ठा mkhi_msg_hdr hdr;
	u8 data[];
पूर्ण __packed;

#घोषणा MKHI_OSVER_BUF_LEN (माप(काष्ठा mkhi_msg_hdr) + \
			    माप(काष्ठा mkhi_fwcaps) + \
			    माप(काष्ठा mei_os_ver))
अटल पूर्णांक mei_osver(काष्ठा mei_cl_device *cldev)
अणु
	स्थिर माप_प्रकार size = MKHI_OSVER_BUF_LEN;
	अक्षर buf[MKHI_OSVER_BUF_LEN];
	काष्ठा mkhi_msg *req;
	काष्ठा mkhi_fwcaps *fwcaps;
	काष्ठा mei_os_ver *os_ver;
	अचिन्हित पूर्णांक mode = MEI_CL_IO_TX_BLOCKING | MEI_CL_IO_TX_INTERNAL;

	स_रखो(buf, 0, size);

	req = (काष्ठा mkhi_msg *)buf;
	req->hdr.group_id = MKHI_FWCAPS_GROUP_ID;
	req->hdr.command = MKHI_FWCAPS_SET_OS_VER_APP_RULE_CMD;

	fwcaps = (काष्ठा mkhi_fwcaps *)req->data;

	fwcaps->id.rule_type = 0x0;
	fwcaps->id.feature_id = MKHI_FEATURE_PTT;
	fwcaps->len = माप(*os_ver);
	os_ver = (काष्ठा mei_os_ver *)fwcaps->data;
	os_ver->os_type = OSTYPE_LINUX;

	वापस __mei_cl_send(cldev->cl, buf, size, 0, mode);
पूर्ण

#घोषणा MKHI_FWVER_BUF_LEN (माप(काष्ठा mkhi_msg_hdr) + \
			    माप(काष्ठा mkhi_fw_ver))
#घोषणा MKHI_FWVER_LEN(__num) (माप(काष्ठा mkhi_msg_hdr) + \
			       माप(काष्ठा mkhi_fw_ver_block) * (__num))
#घोषणा MKHI_RCV_TIMEOUT 500 /* receive समयout in msec */
अटल पूर्णांक mei_fwver(काष्ठा mei_cl_device *cldev)
अणु
	अक्षर buf[MKHI_FWVER_BUF_LEN];
	काष्ठा mkhi_msg req;
	काष्ठा mkhi_msg *rsp;
	काष्ठा mkhi_fw_ver *fwver;
	पूर्णांक bytes_recv, ret, i;

	स_रखो(buf, 0, माप(buf));

	req.hdr.group_id = MKHI_GEN_GROUP_ID;
	req.hdr.command = MKHI_GEN_GET_FW_VERSION_CMD;

	ret = __mei_cl_send(cldev->cl, (u8 *)&req, माप(req), 0,
			    MEI_CL_IO_TX_BLOCKING);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "Could not send ReqFWVersion cmd\n");
		वापस ret;
	पूर्ण

	ret = 0;
	bytes_recv = __mei_cl_recv(cldev->cl, buf, माप(buf), शून्य, 0,
				   MKHI_RCV_TIMEOUT);
	अगर (bytes_recv < 0 || (माप_प्रकार)bytes_recv < MKHI_FWVER_LEN(1)) अणु
		/*
		 * Should be at least one version block,
		 * error out अगर nothing found
		 */
		dev_err(&cldev->dev, "Could not read FW version\n");
		वापस -EIO;
	पूर्ण

	rsp = (काष्ठा mkhi_msg *)buf;
	fwver = (काष्ठा mkhi_fw_ver *)rsp->data;
	स_रखो(cldev->bus->fw_ver, 0, माप(cldev->bus->fw_ver));
	क्रम (i = 0; i < MEI_MAX_FW_VER_BLOCKS; i++) अणु
		अगर ((माप_प्रकार)bytes_recv < MKHI_FWVER_LEN(i + 1))
			अवरोध;
		dev_dbg(&cldev->dev, "FW version%d %d:%d.%d.%d.%d\n",
			i, fwver->ver[i].platक्रमm,
			fwver->ver[i].major, fwver->ver[i].minor,
			fwver->ver[i].hotfix, fwver->ver[i].buildno);

		cldev->bus->fw_ver[i].platक्रमm = fwver->ver[i].platक्रमm;
		cldev->bus->fw_ver[i].major = fwver->ver[i].major;
		cldev->bus->fw_ver[i].minor = fwver->ver[i].minor;
		cldev->bus->fw_ver[i].hotfix = fwver->ver[i].hotfix;
		cldev->bus->fw_ver[i].buildno = fwver->ver[i].buildno;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mei_mkhi_fix(काष्ठा mei_cl_device *cldev)
अणु
	पूर्णांक ret;

	/* No need to enable the client अगर nothing is needed from it */
	अगर (!cldev->bus->fw_f_fw_ver_supported &&
	    !cldev->bus->hbm_f_os_supported)
		वापस;

	ret = mei_cldev_enable(cldev);
	अगर (ret)
		वापस;

	अगर (cldev->bus->fw_f_fw_ver_supported) अणु
		ret = mei_fwver(cldev);
		अगर (ret < 0)
			dev_err(&cldev->dev, "FW version command failed %d\n",
				ret);
	पूर्ण

	अगर (cldev->bus->hbm_f_os_supported) अणु
		ret = mei_osver(cldev);
		अगर (ret < 0)
			dev_err(&cldev->dev, "OS version command failed %d\n",
				ret);
	पूर्ण
	mei_cldev_disable(cldev);
पूर्ण

/**
 * mei_wd - wd client on the bus, change protocol version
 *   as the API has changed.
 *
 * @cldev: me clients device
 */
#अगर IS_ENABLED(CONFIG_INTEL_MEI_ME)
#समावेश <linux/pci.h>
#समावेश "hw-me-regs.h"
अटल व्योम mei_wd(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(cldev->dev.parent);

	अगर (pdev->device == MEI_DEV_ID_WPT_LP ||
	    pdev->device == MEI_DEV_ID_SPT ||
	    pdev->device == MEI_DEV_ID_SPT_H)
		cldev->me_cl->props.protocol_version = 0x2;

	cldev->करो_match = 1;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mei_wd(काष्ठा mei_cl_device *cldev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_INTEL_MEI_ME */

काष्ठा mei_nfc_cmd अणु
	u8 command;
	u8 status;
	u16 req_id;
	u32 reserved;
	u16 data_size;
	u8 sub_command;
	u8 data[];
पूर्ण __packed;

काष्ठा mei_nfc_reply अणु
	u8 command;
	u8 status;
	u16 req_id;
	u32 reserved;
	u16 data_size;
	u8 sub_command;
	u8 reply_status;
	u8 data[];
पूर्ण __packed;

काष्ठा mei_nfc_अगर_version अणु
	u8 radio_version_sw[3];
	u8 reserved[3];
	u8 radio_version_hw[3];
	u8 i2c_addr;
	u8 fw_ivn;
	u8 venकरोr_id;
	u8 radio_type;
पूर्ण __packed;


#घोषणा MEI_NFC_CMD_MAINTEन_अंकCE 0x00
#घोषणा MEI_NFC_SUBCMD_IF_VERSION 0x01

/* Venकरोrs */
#घोषणा MEI_NFC_VENDOR_INSIDE 0x00
#घोषणा MEI_NFC_VENDOR_NXP    0x01

/* Radio types */
#घोषणा MEI_NFC_VENDOR_INSIDE_UREAD 0x00
#घोषणा MEI_NFC_VENDOR_NXP_PN544    0x01

/**
 * mei_nfc_अगर_version - get NFC पूर्णांकerface version
 *
 * @cl: host client (nfc info)
 * @ver: NFC पूर्णांकerface version to be filled in
 *
 * Return: 0 on success; < 0 otherwise
 */
अटल पूर्णांक mei_nfc_अगर_version(काष्ठा mei_cl *cl,
			      काष्ठा mei_nfc_अगर_version *ver)
अणु
	काष्ठा mei_device *bus;
	काष्ठा mei_nfc_cmd cmd = अणु
		.command = MEI_NFC_CMD_MAINTEन_अंकCE,
		.data_size = 1,
		.sub_command = MEI_NFC_SUBCMD_IF_VERSION,
	पूर्ण;
	काष्ठा mei_nfc_reply *reply = शून्य;
	माप_प्रकार अगर_version_length;
	u8 vtag;
	पूर्णांक bytes_recv, ret;

	bus = cl->dev;

	WARN_ON(mutex_is_locked(&bus->device_lock));

	ret = __mei_cl_send(cl, (u8 *)&cmd, माप(cmd), 0,
			    MEI_CL_IO_TX_BLOCKING);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Could not send IF version cmd\n");
		वापस ret;
	पूर्ण

	/* to be sure on the stack we alloc memory */
	अगर_version_length = माप(*reply) + माप(*ver);

	reply = kzalloc(अगर_version_length, GFP_KERNEL);
	अगर (!reply)
		वापस -ENOMEM;

	ret = 0;
	bytes_recv = __mei_cl_recv(cl, (u8 *)reply, अगर_version_length, &vtag,
				   0, 0);
	अगर (bytes_recv < 0 || (माप_प्रकार)bytes_recv < अगर_version_length) अणु
		dev_err(bus->dev, "Could not read IF version\n");
		ret = -EIO;
		जाओ err;
	पूर्ण

	स_नकल(ver, reply->data, माप(*ver));

	dev_info(bus->dev, "NFC MEI VERSION: IVN 0x%x Vendor ID 0x%x Type 0x%x\n",
		ver->fw_ivn, ver->venकरोr_id, ver->radio_type);

err:
	kमुक्त(reply);
	वापस ret;
पूर्ण

/**
 * mei_nfc_radio_name - derive nfc radio name from the पूर्णांकerface version
 *
 * @ver: NFC radio version
 *
 * Return: radio name string
 */
अटल स्थिर अक्षर *mei_nfc_radio_name(काष्ठा mei_nfc_अगर_version *ver)
अणु

	अगर (ver->venकरोr_id == MEI_NFC_VENDOR_INSIDE) अणु
		अगर (ver->radio_type == MEI_NFC_VENDOR_INSIDE_UREAD)
			वापस "microread";
	पूर्ण

	अगर (ver->venकरोr_id == MEI_NFC_VENDOR_NXP) अणु
		अगर (ver->radio_type == MEI_NFC_VENDOR_NXP_PN544)
			वापस "pn544";
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mei_nfc - The nfc fixup function. The function retrieves nfc radio
 *    name and set is as device attribute so we can load
 *    the proper device driver क्रम it
 *
 * @cldev: me client device (nfc)
 */
अटल व्योम mei_nfc(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_device *bus;
	काष्ठा mei_cl *cl;
	काष्ठा mei_me_client *me_cl = शून्य;
	काष्ठा mei_nfc_अगर_version ver;
	स्थिर अक्षर *radio_name = शून्य;
	पूर्णांक ret;

	bus = cldev->bus;

	mutex_lock(&bus->device_lock);
	/* we need to connect to INFO GUID */
	cl = mei_cl_alloc_linked(bus);
	अगर (IS_ERR(cl)) अणु
		ret = PTR_ERR(cl);
		cl = शून्य;
		dev_err(bus->dev, "nfc hook alloc failed %d\n", ret);
		जाओ out;
	पूर्ण

	me_cl = mei_me_cl_by_uuid(bus, &mei_nfc_info_guid);
	अगर (!me_cl) अणु
		ret = -ENOTTY;
		dev_err(bus->dev, "Cannot find nfc info %d\n", ret);
		जाओ out;
	पूर्ण

	ret = mei_cl_connect(cl, me_cl, शून्य);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "Can't connect to the NFC INFO ME ret = %d\n",
			ret);
		जाओ out;
	पूर्ण

	mutex_unlock(&bus->device_lock);

	ret = mei_nfc_अगर_version(cl, &ver);
	अगर (ret)
		जाओ disconnect;

	radio_name = mei_nfc_radio_name(&ver);

	अगर (!radio_name) अणु
		ret = -ENOENT;
		dev_err(&cldev->dev, "Can't get the NFC interface version ret = %d\n",
			ret);
		जाओ disconnect;
	पूर्ण

	dev_dbg(bus->dev, "nfc radio %s\n", radio_name);
	strlcpy(cldev->name, radio_name, माप(cldev->name));

disconnect:
	mutex_lock(&bus->device_lock);
	अगर (mei_cl_disconnect(cl) < 0)
		dev_err(bus->dev, "Can't disconnect the NFC INFO ME\n");

	mei_cl_flush_queues(cl, शून्य);

out:
	mei_cl_unlink(cl);
	mutex_unlock(&bus->device_lock);
	mei_me_cl_put(me_cl);
	kमुक्त(cl);

	अगर (ret)
		cldev->करो_match = 0;

	dev_dbg(bus->dev, "end of fixup match = %d\n", cldev->करो_match);
पूर्ण

/**
 * vt_support - enable on bus clients with vtag support
 *
 * @cldev: me clients device
 */
अटल व्योम vt_support(काष्ठा mei_cl_device *cldev)
अणु
	अगर (cldev->me_cl->props.vt_supported == 1)
		cldev->करो_match = 1;
पूर्ण

#घोषणा MEI_FIXUP(_uuid, _hook) अणु _uuid, _hook पूर्ण

अटल काष्ठा mei_fixup अणु

	स्थिर uuid_le uuid;
	व्योम (*hook)(काष्ठा mei_cl_device *cldev);
पूर्ण mei_fixups[] = अणु
	MEI_FIXUP(MEI_UUID_ANY, number_of_connections),
	MEI_FIXUP(MEI_UUID_NFC_INFO, blacklist),
	MEI_FIXUP(MEI_UUID_NFC_HCI, mei_nfc),
	MEI_FIXUP(MEI_UUID_WD, mei_wd),
	MEI_FIXUP(MEI_UUID_MKHIF_FIX, mei_mkhi_fix),
	MEI_FIXUP(MEI_UUID_HDCP, whitelist),
	MEI_FIXUP(MEI_UUID_ANY, vt_support),
	MEI_FIXUP(MEI_UUID_PAVP, whitelist),
पूर्ण;

/**
 * mei_cldev_fixup - run fixup handlers
 *
 * @cldev: me client device
 */
व्योम mei_cl_bus_dev_fixup(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_fixup *f;
	स्थिर uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(mei_fixups); i++) अणु

		f = &mei_fixups[i];
		अगर (uuid_le_cmp(f->uuid, MEI_UUID_ANY) == 0 ||
		    uuid_le_cmp(f->uuid, *uuid) == 0)
			f->hook(cldev);
	पूर्ण
पूर्ण

