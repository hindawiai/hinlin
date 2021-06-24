<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -------------------------------------------------------------------------
 * Copyright (C) 2014-2016, Intel Corporation
 *
 * -------------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "fdp.h"

#घोषणा FDP_OTP_PATCH_NAME			"otp.bin"
#घोषणा FDP_RAM_PATCH_NAME			"ram.bin"
#घोषणा FDP_FW_HEADER_SIZE			576
#घोषणा FDP_FW_UPDATE_SLEEP			1000

#घोषणा NCI_GET_VERSION_TIMEOUT			8000
#घोषणा NCI_PATCH_REQUEST_TIMEOUT		8000
#घोषणा FDP_PATCH_CONN_DEST			0xC2
#घोषणा FDP_PATCH_CONN_PARAM_TYPE		0xA0

#घोषणा NCI_PATCH_TYPE_RAM			0x00
#घोषणा NCI_PATCH_TYPE_OTP			0x01
#घोषणा NCI_PATCH_TYPE_EOT			0xFF

#घोषणा NCI_PARAM_ID_FW_RAM_VERSION		0xA0
#घोषणा NCI_PARAM_ID_FW_OTP_VERSION		0xA1
#घोषणा NCI_PARAM_ID_OTP_LIMITED_VERSION	0xC5
#घोषणा NCI_PARAM_ID_KEY_INDEX_ID		0xC6

#घोषणा NCI_GID_PROP				0x0F
#घोषणा NCI_OP_PROP_PATCH_OID			0x08
#घोषणा NCI_OP_PROP_SET_PDATA_OID		0x23

काष्ठा fdp_nci_info अणु
	काष्ठा nfc_phy_ops *phy_ops;
	काष्ठा fdp_i2c_phy *phy;
	काष्ठा nci_dev *ndev;

	स्थिर काष्ठा firmware *otp_patch;
	स्थिर काष्ठा firmware *ram_patch;
	u32 otp_patch_version;
	u32 ram_patch_version;

	u32 otp_version;
	u32 ram_version;
	u32 limited_otp_version;
	u8 key_index;

	u8 *fw_vsc_cfg;
	u8 घड़ी_प्रकारype;
	u32 घड़ी_freq;

	atomic_t data_pkt_counter;
	व्योम (*data_pkt_counter_cb)(काष्ठा nci_dev *ndev);
	u8 setup_patch_sent;
	u8 setup_patch_ntf;
	u8 setup_patch_status;
	u8 setup_reset_ntf;
	रुको_queue_head_t setup_wq;
पूर्ण;

अटल u8 nci_core_get_config_otp_ram_version[5] = अणु
	0x04,
	NCI_PARAM_ID_FW_RAM_VERSION,
	NCI_PARAM_ID_FW_OTP_VERSION,
	NCI_PARAM_ID_OTP_LIMITED_VERSION,
	NCI_PARAM_ID_KEY_INDEX_ID
पूर्ण;

काष्ठा nci_core_get_config_rsp अणु
	u8 status;
	u8 count;
	u8 data[];
पूर्ण;

अटल पूर्णांक fdp_nci_create_conn(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा core_conn_create_dest_spec_params param;
	पूर्णांक r;

	/* proprietary destination specअगरic paramerer without value */
	param.type = FDP_PATCH_CONN_PARAM_TYPE;
	param.length = 0x00;

	r = nci_core_conn_create(info->ndev, FDP_PATCH_CONN_DEST, 1,
				 माप(param), &param);
	अगर (r)
		वापस r;

	वापस nci_get_conn_info_by_dest_type_params(ndev,
						     FDP_PATCH_CONN_DEST, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक fdp_nci_get_versions(काष्ठा nci_dev *ndev)
अणु
	वापस nci_core_cmd(ndev, NCI_OP_CORE_GET_CONFIG_CMD,
			    माप(nci_core_get_config_otp_ram_version),
			    (__u8 *) &nci_core_get_config_otp_ram_version);
पूर्ण

अटल अंतरभूत पूर्णांक fdp_nci_patch_cmd(काष्ठा nci_dev *ndev, u8 type)
अणु
	वापस nci_prop_cmd(ndev, NCI_OP_PROP_PATCH_OID, माप(type), &type);
पूर्ण

अटल अंतरभूत पूर्णांक fdp_nci_set_production_data(काष्ठा nci_dev *ndev, u8 len,
					      अक्षर *data)
अणु
	वापस nci_prop_cmd(ndev, NCI_OP_PROP_SET_PDATA_OID, len, data);
पूर्ण

अटल पूर्णांक fdp_nci_set_घड़ी(काष्ठा nci_dev *ndev, u8 घड़ी_प्रकारype,
			     u32 घड़ी_freq)
अणु
	u32 fc = 13560;
	u32 nd, num, delta;
	अक्षर data[9];

	nd = (24 * fc) / घड़ी_freq;
	delta = 24 * fc - nd * घड़ी_freq;
	num = (32768 * delta) / घड़ी_freq;

	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;

	data[3] = 0x10;
	data[4] = 0x04;
	data[5] = num & 0xFF;
	data[6] = (num >> 8) & 0xff;
	data[7] = nd;
	data[8] = घड़ी_प्रकारype;

	वापस fdp_nci_set_production_data(ndev, 9, data);
पूर्ण

अटल व्योम fdp_nci_send_patch_cb(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);

	info->setup_patch_sent = 1;
	wake_up(&info->setup_wq);
पूर्ण

/**
 * Register a packet sent counter and a callback
 *
 * We have no other way of knowing when all firmware packets were sent out
 * on the i2c bus. We need to know that in order to बंद the connection and
 * send the patch end message.
 */
अटल व्योम fdp_nci_set_data_pkt_counter(काष्ठा nci_dev *ndev,
				  व्योम (*cb)(काष्ठा nci_dev *ndev), पूर्णांक count)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "NCI data pkt counter %d\n", count);
	atomic_set(&info->data_pkt_counter, count);
	info->data_pkt_counter_cb = cb;
पूर्ण

/**
 * The device is expecting a stream of packets. All packets need to
 * have the PBF flag set to 0x0 (last packet) even अगर the firmware
 * file is segmented and there are multiple packets. If we give the
 * whole firmware to nci_send_data it will segment it and it will set
 * the PBF flag to 0x01 so we need to करो the segmentation here.
 *
 * The firmware will be analyzed and applied when we send NCI_OP_PROP_PATCH_CMD
 * command with NCI_PATCH_TYPE_EOT parameter. The device will send a
 * NFCC_PATCH_NTF packet and a NCI_OP_CORE_RESET_NTF packet.
 */
अटल पूर्णांक fdp_nci_send_patch(काष्ठा nci_dev *ndev, u8 conn_id, u8 type)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	स्थिर काष्ठा firmware *fw;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ len;
	पूर्णांक max_size, payload_size;
	पूर्णांक rc = 0;

	अगर ((type == NCI_PATCH_TYPE_OTP && !info->otp_patch) ||
	    (type == NCI_PATCH_TYPE_RAM && !info->ram_patch))
		वापस -EINVAL;

	अगर (type == NCI_PATCH_TYPE_OTP)
		fw = info->otp_patch;
	अन्यथा
		fw = info->ram_patch;

	max_size = nci_conn_max_data_pkt_payload_size(ndev, conn_id);
	अगर (max_size <= 0)
		वापस -EINVAL;

	len = fw->size;

	fdp_nci_set_data_pkt_counter(ndev, fdp_nci_send_patch_cb,
				     DIV_ROUND_UP(fw->size, max_size));

	जबतक (len) अणु

		payload_size = min_t(अचिन्हित दीर्घ, max_size, len);

		skb = nci_skb_alloc(ndev, (NCI_CTRL_HDR_SIZE + payload_size),
				    GFP_KERNEL);
		अगर (!skb) अणु
			fdp_nci_set_data_pkt_counter(ndev, शून्य, 0);
			वापस -ENOMEM;
		पूर्ण


		skb_reserve(skb, NCI_CTRL_HDR_SIZE);

		skb_put_data(skb, fw->data + (fw->size - len), payload_size);

		rc = nci_send_data(ndev, conn_id, skb);

		अगर (rc) अणु
			fdp_nci_set_data_pkt_counter(ndev, शून्य, 0);
			वापस rc;
		पूर्ण

		len -= payload_size;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक fdp_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);

	वापस info->phy_ops->enable(info->phy);
पूर्ण

अटल पूर्णांक fdp_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);

	अगर (atomic_dec_and_test(&info->data_pkt_counter))
		info->data_pkt_counter_cb(ndev);

	वापस info->phy_ops->ग_लिखो(info->phy, skb);
पूर्ण

पूर्णांक fdp_nci_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);
	वापस nci_recv_frame(ndev, skb);
पूर्ण
EXPORT_SYMBOL(fdp_nci_recv_frame);

अटल पूर्णांक fdp_nci_request_firmware(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	u8 *data;
	पूर्णांक r;

	r = request_firmware(&info->ram_patch, FDP_RAM_PATCH_NAME, dev);
	अगर (r < 0) अणु
		nfc_err(dev, "RAM patch request error\n");
		जाओ error;
	पूर्ण

	data = (u8 *) info->ram_patch->data;
	info->ram_patch_version =
		data[FDP_FW_HEADER_SIZE] |
		(data[FDP_FW_HEADER_SIZE + 1] << 8) |
		(data[FDP_FW_HEADER_SIZE + 2] << 16) |
		(data[FDP_FW_HEADER_SIZE + 3] << 24);

	dev_dbg(dev, "RAM patch version: %d, size: %d\n",
		  info->ram_patch_version, (पूर्णांक) info->ram_patch->size);


	r = request_firmware(&info->otp_patch, FDP_OTP_PATCH_NAME, dev);
	अगर (r < 0) अणु
		nfc_err(dev, "OTP patch request error\n");
		जाओ out;
	पूर्ण

	data = (u8 *) info->otp_patch->data;
	info->otp_patch_version =
		data[FDP_FW_HEADER_SIZE] |
		(data[FDP_FW_HEADER_SIZE + 1] << 8) |
		(data[FDP_FW_HEADER_SIZE+2] << 16) |
		(data[FDP_FW_HEADER_SIZE+3] << 24);

	dev_dbg(dev, "OTP patch version: %d, size: %d\n",
		 info->otp_patch_version, (पूर्णांक) info->otp_patch->size);
out:
	वापस 0;
error:
	वापस r;
पूर्ण

अटल व्योम fdp_nci_release_firmware(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);

	अगर (info->otp_patch) अणु
		release_firmware(info->otp_patch);
		info->otp_patch = शून्य;
	पूर्ण

	अगर (info->ram_patch) अणु
		release_firmware(info->ram_patch);
		info->ram_patch = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक fdp_nci_patch_otp(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	पूर्णांक conn_id;
	पूर्णांक r = 0;

	अगर (info->otp_version >= info->otp_patch_version)
		वापस r;

	info->setup_patch_sent = 0;
	info->setup_reset_ntf = 0;
	info->setup_patch_ntf = 0;

	/* Patch init request */
	r = fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_OTP);
	अगर (r)
		वापस r;

	/* Patch data connection creation */
	conn_id = fdp_nci_create_conn(ndev);
	अगर (conn_id < 0)
		वापस conn_id;

	/* Send the patch over the data connection */
	r = fdp_nci_send_patch(ndev, conn_id, NCI_PATCH_TYPE_OTP);
	अगर (r)
		वापस r;

	/* Wait क्रम all the packets to be send over i2c */
	रुको_event_पूर्णांकerruptible(info->setup_wq,
				 info->setup_patch_sent == 1);

	/* make sure that the NFCC processed the last data packet */
	msleep(FDP_FW_UPDATE_SLEEP);

	/* Close the data connection */
	r = nci_core_conn_बंद(info->ndev, conn_id);
	अगर (r)
		वापस r;

	/* Patch finish message */
	अगर (fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_EOT)) अणु
		nfc_err(dev, "OTP patch error 0x%x\n", r);
		वापस -EINVAL;
	पूर्ण

	/* If the patch notअगरication didn't arrive yet, रुको क्रम it */
	रुको_event_पूर्णांकerruptible(info->setup_wq, info->setup_patch_ntf);

	/* Check अगर the patching was successful */
	r = info->setup_patch_status;
	अगर (r) अणु
		nfc_err(dev, "OTP patch error 0x%x\n", r);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We need to रुको क्रम the reset notअगरication beक्रमe we
	 * can जारी
	 */
	रुको_event_पूर्णांकerruptible(info->setup_wq, info->setup_reset_ntf);

	वापस r;
पूर्ण

अटल पूर्णांक fdp_nci_patch_ram(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	पूर्णांक conn_id;
	पूर्णांक r = 0;

	अगर (info->ram_version >= info->ram_patch_version)
		वापस r;

	info->setup_patch_sent = 0;
	info->setup_reset_ntf = 0;
	info->setup_patch_ntf = 0;

	/* Patch init request */
	r = fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_RAM);
	अगर (r)
		वापस r;

	/* Patch data connection creation */
	conn_id = fdp_nci_create_conn(ndev);
	अगर (conn_id < 0)
		वापस conn_id;

	/* Send the patch over the data connection */
	r = fdp_nci_send_patch(ndev, conn_id, NCI_PATCH_TYPE_RAM);
	अगर (r)
		वापस r;

	/* Wait क्रम all the packets to be send over i2c */
	रुको_event_पूर्णांकerruptible(info->setup_wq,
				 info->setup_patch_sent == 1);

	/* make sure that the NFCC processed the last data packet */
	msleep(FDP_FW_UPDATE_SLEEP);

	/* Close the data connection */
	r = nci_core_conn_बंद(info->ndev, conn_id);
	अगर (r)
		वापस r;

	/* Patch finish message */
	अगर (fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_EOT)) अणु
		nfc_err(dev, "RAM patch error 0x%x\n", r);
		वापस -EINVAL;
	पूर्ण

	/* If the patch notअगरication didn't arrive yet, रुको क्रम it */
	रुको_event_पूर्णांकerruptible(info->setup_wq, info->setup_patch_ntf);

	/* Check अगर the patching was successful */
	r = info->setup_patch_status;
	अगर (r) अणु
		nfc_err(dev, "RAM patch error 0x%x\n", r);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We need to रुको क्रम the reset notअगरication beक्रमe we
	 * can जारी
	 */
	रुको_event_पूर्णांकerruptible(info->setup_wq, info->setup_reset_ntf);

	वापस r;
पूर्ण

अटल पूर्णांक fdp_nci_setup(काष्ठा nci_dev *ndev)
अणु
	/* Format: total length followed by an NCI packet */
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	पूर्णांक r;
	u8 patched = 0;

	dev_dbg(dev, "%s\n", __func__);

	r = nci_core_init(ndev);
	अगर (r)
		जाओ error;

	/* Get RAM and OTP version */
	r = fdp_nci_get_versions(ndev);
	अगर (r)
		जाओ error;

	/* Load firmware from disk */
	r = fdp_nci_request_firmware(ndev);
	अगर (r)
		जाओ error;

	/* Update OTP */
	अगर (info->otp_version < info->otp_patch_version) अणु
		r = fdp_nci_patch_otp(ndev);
		अगर (r)
			जाओ error;
		patched = 1;
	पूर्ण

	/* Update RAM */
	अगर (info->ram_version < info->ram_patch_version) अणु
		r = fdp_nci_patch_ram(ndev);
		अगर (r)
			जाओ error;
		patched = 1;
	पूर्ण

	/* Release the firmware buffers */
	fdp_nci_release_firmware(ndev);

	/* If a patch was applied the new version is checked */
	अगर (patched) अणु
		r = nci_core_init(ndev);
		अगर (r)
			जाओ error;

		r = fdp_nci_get_versions(ndev);
		अगर (r)
			जाओ error;

		अगर (info->otp_version != info->otp_patch_version ||
		    info->ram_version != info->ram_patch_version) अणु
			nfc_err(dev, "Firmware update failed");
			r = -EINVAL;
			जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * We initialized the devices but the NFC subप्रणाली expects
	 * it to not be initialized.
	 */
	वापस nci_core_reset(ndev);

error:
	fdp_nci_release_firmware(ndev);
	nfc_err(dev, "Setup error %d\n", r);
	वापस r;
पूर्ण

अटल पूर्णांक fdp_nci_post_setup(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	पूर्णांक r;

	/* Check अगर the device has VSC */
	अगर (info->fw_vsc_cfg && info->fw_vsc_cfg[0]) अणु

		/* Set the venकरोr specअगरic configuration */
		r = fdp_nci_set_production_data(ndev, info->fw_vsc_cfg[3],
						&info->fw_vsc_cfg[4]);
		अगर (r) अणु
			nfc_err(dev, "Vendor specific config set error %d\n",
				r);
			वापस r;
		पूर्ण
	पूर्ण

	/* Set घड़ी type and frequency */
	r = fdp_nci_set_घड़ी(ndev, info->घड़ी_प्रकारype, info->घड़ी_freq);
	अगर (r) अणु
		nfc_err(dev, "Clock set error %d\n", r);
		वापस r;
	पूर्ण

	/*
	 * In order to apply the VSC FDP needs a reset
	 */
	r = nci_core_reset(ndev);
	अगर (r)
		वापस r;

	/**
	 * The nci core was initialized when post setup was called
	 * so we leave it like that
	 */
	वापस nci_core_init(ndev);
पूर्ण

अटल पूर्णांक fdp_nci_core_reset_ntf_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);
	info->setup_reset_ntf = 1;
	wake_up(&info->setup_wq);

	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_prop_patch_ntf_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);
	info->setup_patch_ntf = 1;
	info->setup_patch_status = skb->data[0];
	wake_up(&info->setup_wq);

	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_prop_patch_rsp_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	u8 status = skb->data[0];

	dev_dbg(dev, "%s: status 0x%x\n", __func__, status);
	nci_req_complete(ndev, status);

	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_prop_set_production_data_rsp_packet(काष्ठा nci_dev *ndev,
							काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	u8 status = skb->data[0];

	dev_dbg(dev, "%s: status 0x%x\n", __func__, status);
	nci_req_complete(ndev, status);

	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_core_get_config_rsp_packet(काष्ठा nci_dev *ndev,
						काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;
	काष्ठा nci_core_get_config_rsp *rsp = (व्योम *) skb->data;
	u8 i, *p;

	अगर (rsp->status == NCI_STATUS_OK) अणु

		p = rsp->data;
		क्रम (i = 0; i < 4; i++) अणु

			चयन (*p++) अणु
			हाल NCI_PARAM_ID_FW_RAM_VERSION:
				p++;
				info->ram_version = le32_to_cpup((__le32 *) p);
				p += 4;
				अवरोध;
			हाल NCI_PARAM_ID_FW_OTP_VERSION:
				p++;
				info->otp_version = le32_to_cpup((__le32 *) p);
				p += 4;
				अवरोध;
			हाल NCI_PARAM_ID_OTP_LIMITED_VERSION:
				p++;
				info->otp_version = le32_to_cpup((__le32 *) p);
				p += 4;
				अवरोध;
			हाल NCI_PARAM_ID_KEY_INDEX_ID:
				p++;
				info->key_index = *p++;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(dev, "OTP version %d\n", info->otp_version);
	dev_dbg(dev, "RAM version %d\n", info->ram_version);
	dev_dbg(dev, "key index %d\n", info->key_index);
	dev_dbg(dev, "%s: status 0x%x\n", __func__, rsp->status);

	nci_req_complete(ndev, rsp->status);

	वापस 0;
पूर्ण

अटल काष्ठा nci_driver_ops fdp_core_ops[] = अणु
	अणु
		.opcode = NCI_OP_CORE_GET_CONFIG_RSP,
		.rsp = fdp_nci_core_get_config_rsp_packet,
	पूर्ण,
	अणु
		.opcode = NCI_OP_CORE_RESET_NTF,
		.ntf = fdp_nci_core_reset_ntf_packet,
	पूर्ण,
पूर्ण;

अटल काष्ठा nci_driver_ops fdp_prop_ops[] = अणु
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROP, NCI_OP_PROP_PATCH_OID),
		.rsp = fdp_nci_prop_patch_rsp_packet,
		.ntf = fdp_nci_prop_patch_ntf_packet,
	पूर्ण,
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROP,
					  NCI_OP_PROP_SET_PDATA_OID),
		.rsp = fdp_nci_prop_set_production_data_rsp_packet,
	पूर्ण,
पूर्ण;

अटल काष्ठा nci_ops nci_ops = अणु
	.खोलो = fdp_nci_खोलो,
	.बंद = fdp_nci_बंद,
	.send = fdp_nci_send,
	.setup = fdp_nci_setup,
	.post_setup = fdp_nci_post_setup,
	.prop_ops = fdp_prop_ops,
	.n_prop_ops = ARRAY_SIZE(fdp_prop_ops),
	.core_ops = fdp_core_ops,
	.n_core_ops = ARRAY_SIZE(fdp_core_ops),
पूर्ण;

पूर्णांक fdp_nci_probe(काष्ठा fdp_i2c_phy *phy, काष्ठा nfc_phy_ops *phy_ops,
			काष्ठा nci_dev **ndevp, पूर्णांक tx_headroom,
			पूर्णांक tx_tailroom, u8 घड़ी_प्रकारype, u32 घड़ी_freq,
			u8 *fw_vsc_cfg)
अणु
	काष्ठा device *dev = &phy->i2c_dev->dev;
	काष्ठा fdp_nci_info *info;
	काष्ठा nci_dev *ndev;
	u32 protocols;
	पूर्णांक r;

	info = devm_kzalloc(dev, माप(काष्ठा fdp_nci_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->phy = phy;
	info->phy_ops = phy_ops;
	info->घड़ी_प्रकारype = घड़ी_प्रकारype;
	info->घड़ी_freq = घड़ी_freq;
	info->fw_vsc_cfg = fw_vsc_cfg;

	init_रुकोqueue_head(&info->setup_wq);

	protocols = NFC_PROTO_JEWEL_MASK |
		    NFC_PROTO_MIFARE_MASK |
		    NFC_PROTO_FELICA_MASK |
		    NFC_PROTO_ISO14443_MASK |
		    NFC_PROTO_ISO14443_B_MASK |
		    NFC_PROTO_NFC_DEP_MASK |
		    NFC_PROTO_ISO15693_MASK;

	ndev = nci_allocate_device(&nci_ops, protocols, tx_headroom,
				   tx_tailroom);
	अगर (!ndev) अणु
		nfc_err(dev, "Cannot allocate nfc ndev\n");
		वापस -ENOMEM;
	पूर्ण

	r = nci_रेजिस्टर_device(ndev);
	अगर (r)
		जाओ err_regdev;

	*ndevp = ndev;
	info->ndev = ndev;

	nci_set_drvdata(ndev, info);

	वापस 0;

err_regdev:
	nci_मुक्त_device(ndev);
	वापस r;
पूर्ण
EXPORT_SYMBOL(fdp_nci_probe);

व्योम fdp_nci_हटाओ(काष्ठा nci_dev *ndev)
अणु
	काष्ठा fdp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "%s\n", __func__);

	nci_unरेजिस्टर_device(ndev);
	nci_मुक्त_device(ndev);
पूर्ण
EXPORT_SYMBOL(fdp_nci_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("NFC NCI driver for Intel Fields Peak NFC controller");
MODULE_AUTHOR("Robert Dolca <robert.dolca@intel.com>");
