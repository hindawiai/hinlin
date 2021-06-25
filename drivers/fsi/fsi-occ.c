<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/fsi-sbefअगरo.h>
#समावेश <linux/gfp.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fsi-occ.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा OCC_SRAM_BYTES		4096
#घोषणा OCC_CMD_DATA_BYTES	4090
#घोषणा OCC_RESP_DATA_BYTES	4089

#घोषणा OCC_P9_SRAM_CMD_ADDR	0xFFFBE000
#घोषणा OCC_P9_SRAM_RSP_ADDR	0xFFFBF000

#घोषणा OCC_P10_SRAM_CMD_ADDR	0xFFFFD000
#घोषणा OCC_P10_SRAM_RSP_ADDR	0xFFFFE000

#घोषणा OCC_P10_SRAM_MODE	0x58	/* Normal mode, OCB channel 2 */

/*
 * Assume we करोn't have much FFDC, if we do we'll overflow and
 * fail the command. This needs to be big enough क्रम simple
 * commands as well.
 */
#घोषणा OCC_SBE_STATUS_WORDS	32

#घोषणा OCC_TIMEOUT_MS		1000
#घोषणा OCC_CMD_IN_PRG_WAIT_MS	50

क्रमागत versions अणु occ_p9, occ_p10 पूर्ण;

काष्ठा occ अणु
	काष्ठा device *dev;
	काष्ठा device *sbefअगरo;
	अक्षर name[32];
	पूर्णांक idx;
	क्रमागत versions version;
	काष्ठा miscdevice mdev;
	काष्ठा mutex occ_lock;
पूर्ण;

#घोषणा to_occ(x)	container_of((x), काष्ठा occ, mdev)

काष्ठा occ_response अणु
	u8 seq_no;
	u8 cmd_type;
	u8 वापस_status;
	__be16 data_length;
	u8 data[OCC_RESP_DATA_BYTES + 2];	/* two bytes checksum */
पूर्ण __packed;

काष्ठा occ_client अणु
	काष्ठा occ *occ;
	काष्ठा mutex lock;
	माप_प्रकार data_size;
	माप_प्रकार पढ़ो_offset;
	u8 *buffer;
पूर्ण;

#घोषणा to_client(x)	container_of((x), काष्ठा occ_client, xfr)

अटल DEFINE_IDA(occ_ida);

अटल पूर्णांक occ_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा occ_client *client = kzalloc(माप(*client), GFP_KERNEL);
	काष्ठा miscdevice *mdev = file->निजी_data;
	काष्ठा occ *occ = to_occ(mdev);

	अगर (!client)
		वापस -ENOMEM;

	client->buffer = (u8 *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!client->buffer) अणु
		kमुक्त(client);
		वापस -ENOMEM;
	पूर्ण

	client->occ = occ;
	mutex_init(&client->lock);
	file->निजी_data = client;

	/* We allocate a 1-page buffer, make sure it all fits */
	BUILD_BUG_ON((OCC_CMD_DATA_BYTES + 3) > PAGE_SIZE);
	BUILD_BUG_ON((OCC_RESP_DATA_BYTES + 7) > PAGE_SIZE);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार occ_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
			loff_t *offset)
अणु
	काष्ठा occ_client *client = file->निजी_data;
	sमाप_प्रकार rc = 0;

	अगर (!client)
		वापस -ENODEV;

	अगर (len > OCC_SRAM_BYTES)
		वापस -EINVAL;

	mutex_lock(&client->lock);

	/* This should not be possible ... */
	अगर (WARN_ON_ONCE(client->पढ़ो_offset > client->data_size)) अणु
		rc = -EIO;
		जाओ करोne;
	पूर्ण

	/* Grab how much data we have to पढ़ो */
	rc = min(len, client->data_size - client->पढ़ो_offset);
	अगर (copy_to_user(buf, client->buffer + client->पढ़ो_offset, rc))
		rc = -EFAULT;
	अन्यथा
		client->पढ़ो_offset += rc;

 करोne:
	mutex_unlock(&client->lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार occ_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा occ_client *client = file->निजी_data;
	माप_प्रकार rlen, data_length;
	u16 checksum = 0;
	sमाप_प्रकार rc, i;
	u8 *cmd;

	अगर (!client)
		वापस -ENODEV;

	अगर (len > (OCC_CMD_DATA_BYTES + 3) || len < 3)
		वापस -EINVAL;

	mutex_lock(&client->lock);

	/* Conकाष्ठा the command */
	cmd = client->buffer;

	/* Sequence number (we could increment and compare with response) */
	cmd[0] = 1;

	/*
	 * Copy the user command (assume user data follows the occ command
	 * क्रमmat)
	 * byte 0: command type
	 * bytes 1-2: data length (msb first)
	 * bytes 3-n: data
	 */
	अगर (copy_from_user(&cmd[1], buf, len)) अणु
		rc = -EFAULT;
		जाओ करोne;
	पूर्ण

	/* Extract data length */
	data_length = (cmd[2] << 8) + cmd[3];
	अगर (data_length > OCC_CMD_DATA_BYTES) अणु
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Calculate checksum */
	क्रम (i = 0; i < data_length + 4; ++i)
		checksum += cmd[i];

	cmd[data_length + 4] = checksum >> 8;
	cmd[data_length + 5] = checksum & 0xFF;

	/* Submit command */
	rlen = PAGE_SIZE;
	rc = fsi_occ_submit(client->occ->dev, cmd, data_length + 6, cmd,
			    &rlen);
	अगर (rc)
		जाओ करोne;

	/* Set पढ़ो tracking data */
	client->data_size = rlen;
	client->पढ़ो_offset = 0;

	/* Done */
	rc = len;

 करोne:
	mutex_unlock(&client->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक occ_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा occ_client *client = file->निजी_data;

	मुक्त_page((अचिन्हित दीर्घ)client->buffer);
	kमुक्त(client);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations occ_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = occ_खोलो,
	.पढ़ो = occ_पढ़ो,
	.ग_लिखो = occ_ग_लिखो,
	.release = occ_release,
पूर्ण;

अटल पूर्णांक occ_verअगरy_checksum(काष्ठा occ_response *resp, u16 data_length)
अणु
	/* Fetch the two bytes after the data क्रम the checksum. */
	u16 checksum_resp = get_unaligned_be16(&resp->data[data_length]);
	u16 checksum;
	u16 i;

	checksum = resp->seq_no;
	checksum += resp->cmd_type;
	checksum += resp->वापस_status;
	checksum += (data_length >> 8) + (data_length & 0xFF);

	क्रम (i = 0; i < data_length; ++i)
		checksum += resp->data[i];

	अगर (checksum != checksum_resp)
		वापस -EBADMSG;

	वापस 0;
पूर्ण

अटल पूर्णांक occ_माला_लोram(काष्ठा occ *occ, u32 offset, व्योम *data, sमाप_प्रकार len)
अणु
	u32 data_len = ((len + 7) / 8) * 8;	/* must be multiples of 8 B */
	माप_प्रकार cmd_len, resp_len, resp_data_len;
	__be32 *resp, cmd[6];
	पूर्णांक idx = 0, rc;

	/*
	 * Magic sequence to करो SBE माला_लोram command. SBE will fetch data from
	 * specअगरied SRAM address.
	 */
	चयन (occ->version) अणु
	शेष:
	हाल occ_p9:
		cmd_len = 5;
		cmd[2] = cpu_to_be32(1);	/* Normal mode */
		cmd[3] = cpu_to_be32(OCC_P9_SRAM_RSP_ADDR + offset);
		अवरोध;
	हाल occ_p10:
		idx = 1;
		cmd_len = 6;
		cmd[2] = cpu_to_be32(OCC_P10_SRAM_MODE);
		cmd[3] = 0;
		cmd[4] = cpu_to_be32(OCC_P10_SRAM_RSP_ADDR + offset);
		अवरोध;
	पूर्ण

	cmd[0] = cpu_to_be32(cmd_len);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_OCC_SRAM);
	cmd[4 + idx] = cpu_to_be32(data_len);

	resp_len = (data_len >> 2) + OCC_SBE_STATUS_WORDS;
	resp = kzalloc(resp_len << 2, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	rc = sbefअगरo_submit(occ->sbefअगरo, cmd, cmd_len, resp, &resp_len);
	अगर (rc)
		जाओ मुक्त;

	rc = sbefअगरo_parse_status(occ->sbefअगरo, SBEFIFO_CMD_GET_OCC_SRAM,
				  resp, resp_len, &resp_len);
	अगर (rc)
		जाओ मुक्त;

	resp_data_len = be32_to_cpu(resp[resp_len - 1]);
	अगर (resp_data_len != data_len) अणु
		dev_err(occ->dev, "SRAM read expected %d bytes got %zd\n",
			data_len, resp_data_len);
		rc = -EBADMSG;
	पूर्ण अन्यथा अणु
		स_नकल(data, resp, len);
	पूर्ण

मुक्त:
	/* Convert positive SBEI status */
	अगर (rc > 0) अणु
		dev_err(occ->dev, "SRAM read returned failure status: %08x\n",
			rc);
		rc = -EBADMSG;
	पूर्ण

	kमुक्त(resp);
	वापस rc;
पूर्ण

अटल पूर्णांक occ_माला_दोram(काष्ठा occ *occ, स्थिर व्योम *data, sमाप_प्रकार len)
अणु
	माप_प्रकार cmd_len, buf_len, resp_len, resp_data_len;
	u32 data_len = ((len + 7) / 8) * 8;	/* must be multiples of 8 B */
	__be32 *buf;
	पूर्णांक idx = 0, rc;

	cmd_len = (occ->version == occ_p10) ? 6 : 5;

	/*
	 * We use the same buffer क्रम command and response, make
	 * sure it's big enough
	 */
	resp_len = OCC_SBE_STATUS_WORDS;
	cmd_len += data_len >> 2;
	buf_len = max(cmd_len, resp_len);
	buf = kzalloc(buf_len << 2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * Magic sequence to करो SBE माला_दोram command. SBE will transfer
	 * data to specअगरied SRAM address.
	 */
	buf[0] = cpu_to_be32(cmd_len);
	buf[1] = cpu_to_be32(SBEFIFO_CMD_PUT_OCC_SRAM);

	चयन (occ->version) अणु
	शेष:
	हाल occ_p9:
		buf[2] = cpu_to_be32(1);	/* Normal mode */
		buf[3] = cpu_to_be32(OCC_P9_SRAM_CMD_ADDR);
		अवरोध;
	हाल occ_p10:
		idx = 1;
		buf[2] = cpu_to_be32(OCC_P10_SRAM_MODE);
		buf[3] = 0;
		buf[4] = cpu_to_be32(OCC_P10_SRAM_CMD_ADDR);
		अवरोध;
	पूर्ण

	buf[4 + idx] = cpu_to_be32(data_len);
	स_नकल(&buf[5 + idx], data, len);

	rc = sbefअगरo_submit(occ->sbefअगरo, buf, cmd_len, buf, &resp_len);
	अगर (rc)
		जाओ मुक्त;

	rc = sbefअगरo_parse_status(occ->sbefअगरo, SBEFIFO_CMD_PUT_OCC_SRAM,
				  buf, resp_len, &resp_len);
	अगर (rc)
		जाओ मुक्त;

	अगर (resp_len != 1) अणु
		dev_err(occ->dev, "SRAM write response length invalid: %zd\n",
			resp_len);
		rc = -EBADMSG;
	पूर्ण अन्यथा अणु
		resp_data_len = be32_to_cpu(buf[0]);
		अगर (resp_data_len != data_len) अणु
			dev_err(occ->dev,
				"SRAM write expected %d bytes got %zd\n",
				data_len, resp_data_len);
			rc = -EBADMSG;
		पूर्ण
	पूर्ण

मुक्त:
	/* Convert positive SBEI status */
	अगर (rc > 0) अणु
		dev_err(occ->dev, "SRAM write returned failure status: %08x\n",
			rc);
		rc = -EBADMSG;
	पूर्ण

	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक occ_trigger_attn(काष्ठा occ *occ)
अणु
	__be32 buf[OCC_SBE_STATUS_WORDS];
	माप_प्रकार cmd_len, resp_len, resp_data_len;
	पूर्णांक idx = 0, rc;

	BUILD_BUG_ON(OCC_SBE_STATUS_WORDS < 8);
	resp_len = OCC_SBE_STATUS_WORDS;

	चयन (occ->version) अणु
	शेष:
	हाल occ_p9:
		cmd_len = 7;
		buf[2] = cpu_to_be32(3); /* Circular mode */
		buf[3] = 0;
		अवरोध;
	हाल occ_p10:
		idx = 1;
		cmd_len = 8;
		buf[2] = cpu_to_be32(0xd0); /* Circular mode, OCB Channel 1 */
		buf[3] = 0;
		buf[4] = 0;
		अवरोध;
	पूर्ण

	buf[0] = cpu_to_be32(cmd_len);		/* Chip-op length in words */
	buf[1] = cpu_to_be32(SBEFIFO_CMD_PUT_OCC_SRAM);
	buf[4 + idx] = cpu_to_be32(8);		/* Data length in bytes */
	buf[5 + idx] = cpu_to_be32(0x20010000);	/* Trigger OCC attention */
	buf[6 + idx] = 0;

	rc = sbefअगरo_submit(occ->sbefअगरo, buf, cmd_len, buf, &resp_len);
	अगर (rc)
		जाओ error;

	rc = sbefअगरo_parse_status(occ->sbefअगरo, SBEFIFO_CMD_PUT_OCC_SRAM,
				  buf, resp_len, &resp_len);
	अगर (rc)
		जाओ error;

	अगर (resp_len != 1) अणु
		dev_err(occ->dev, "SRAM attn response length invalid: %zd\n",
			resp_len);
		rc = -EBADMSG;
	पूर्ण अन्यथा अणु
		resp_data_len = be32_to_cpu(buf[0]);
		अगर (resp_data_len != 8) अणु
			dev_err(occ->dev,
				"SRAM attn expected 8 bytes got %zd\n",
				resp_data_len);
			rc = -EBADMSG;
		पूर्ण
	पूर्ण

 error:
	/* Convert positive SBEI status */
	अगर (rc > 0) अणु
		dev_err(occ->dev, "SRAM attn returned failure status: %08x\n",
			rc);
		rc = -EBADMSG;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक fsi_occ_submit(काष्ठा device *dev, स्थिर व्योम *request, माप_प्रकार req_len,
		   व्योम *response, माप_प्रकार *resp_len)
अणु
	स्थिर अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(OCC_TIMEOUT_MS);
	स्थिर अचिन्हित दीर्घ रुको_समय =
		msecs_to_jअगरfies(OCC_CMD_IN_PRG_WAIT_MS);
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_response *resp = response;
	u8 seq_no;
	u16 resp_data_length;
	अचिन्हित दीर्घ start;
	पूर्णांक rc;

	अगर (!occ)
		वापस -ENODEV;

	अगर (*resp_len < 7) अणु
		dev_dbg(dev, "Bad resplen %zd\n", *resp_len);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&occ->occ_lock);

	/* Extract the seq_no from the command (first byte) */
	seq_no = *(स्थिर u8 *)request;
	rc = occ_माला_दोram(occ, request, req_len);
	अगर (rc)
		जाओ करोne;

	rc = occ_trigger_attn(occ);
	अगर (rc)
		जाओ करोne;

	/* Read occ response header */
	start = jअगरfies;
	करो अणु
		rc = occ_माला_लोram(occ, 0, resp, 8);
		अगर (rc)
			जाओ करोne;

		अगर (resp->वापस_status == OCC_RESP_CMD_IN_PRG ||
		    resp->seq_no != seq_no) अणु
			rc = -ETIMEDOUT;

			अगर (समय_after(jअगरfies, start + समयout)) अणु
				dev_err(occ->dev, "resp timeout status=%02x "
					"resp seq_no=%d our seq_no=%d\n",
					resp->वापस_status, resp->seq_no,
					seq_no);
				जाओ करोne;
			पूर्ण

			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(रुको_समय);
		पूर्ण
	पूर्ण जबतक (rc);

	/* Extract size of response data */
	resp_data_length = get_unaligned_be16(&resp->data_length);

	/* Message size is data length + 5 bytes header + 2 bytes checksum */
	अगर ((resp_data_length + 7) > *resp_len) अणु
		rc = -EMSGSIZE;
		जाओ करोne;
	पूर्ण

	dev_dbg(dev, "resp_status=%02x resp_data_len=%d\n",
		resp->वापस_status, resp_data_length);

	/* Grab the rest */
	अगर (resp_data_length > 1) अणु
		/* alपढ़ोy got 3 bytes resp, also need 2 bytes checksum */
		rc = occ_माला_लोram(occ, 8, &resp->data[3], resp_data_length - 1);
		अगर (rc)
			जाओ करोne;
	पूर्ण

	*resp_len = resp_data_length + 7;
	rc = occ_verअगरy_checksum(resp, resp_data_length);

 करोne:
	mutex_unlock(&occ->occ_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_occ_submit);

अटल पूर्णांक occ_unरेजिस्टर_child(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *hwmon_dev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(hwmon_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक occ_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	u32 reg;
	काष्ठा occ *occ;
	काष्ठा platक्रमm_device *hwmon_dev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा platक्रमm_device_info hwmon_dev_info = अणु
		.parent = dev,
		.name = "occ-hwmon",
	पूर्ण;

	occ = devm_kzalloc(dev, माप(*occ), GFP_KERNEL);
	अगर (!occ)
		वापस -ENOMEM;

	occ->version = (uपूर्णांकptr_t)of_device_get_match_data(dev);
	occ->dev = dev;
	occ->sbefअगरo = dev->parent;
	mutex_init(&occ->occ_lock);

	अगर (dev->of_node) अणु
		rc = of_property_पढ़ो_u32(dev->of_node, "reg", &reg);
		अगर (!rc) अणु
			/* make sure we करोn't have a duplicate from dts */
			occ->idx = ida_simple_get(&occ_ida, reg, reg + 1,
						  GFP_KERNEL);
			अगर (occ->idx < 0)
				occ->idx = ida_simple_get(&occ_ida, 1, पूर्णांक_उच्च,
							  GFP_KERNEL);
		पूर्ण अन्यथा अणु
			occ->idx = ida_simple_get(&occ_ida, 1, पूर्णांक_उच्च,
						  GFP_KERNEL);
		पूर्ण
	पूर्ण अन्यथा अणु
		occ->idx = ida_simple_get(&occ_ida, 1, पूर्णांक_उच्च, GFP_KERNEL);
	पूर्ण

	platक्रमm_set_drvdata(pdev, occ);

	snम_लिखो(occ->name, माप(occ->name), "occ%d", occ->idx);
	occ->mdev.fops = &occ_fops;
	occ->mdev.minor = MISC_DYNAMIC_MINOR;
	occ->mdev.name = occ->name;
	occ->mdev.parent = dev;

	rc = misc_रेजिस्टर(&occ->mdev);
	अगर (rc) अणु
		dev_err(dev, "failed to register miscdevice: %d\n", rc);
		ida_simple_हटाओ(&occ_ida, occ->idx);
		वापस rc;
	पूर्ण

	hwmon_dev_info.id = occ->idx;
	hwmon_dev = platक्रमm_device_रेजिस्टर_full(&hwmon_dev_info);
	अगर (IS_ERR(hwmon_dev))
		dev_warn(dev, "failed to create hwmon device\n");

	वापस 0;
पूर्ण

अटल पूर्णांक occ_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा occ *occ = platक्रमm_get_drvdata(pdev);

	misc_deरेजिस्टर(&occ->mdev);

	device_क्रम_each_child(&pdev->dev, शून्य, occ_unरेजिस्टर_child);

	ida_simple_हटाओ(&occ_ida, occ->idx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id occ_match[] = अणु
	अणु
		.compatible = "ibm,p9-occ",
		.data = (व्योम *)occ_p9
	पूर्ण,
	अणु
		.compatible = "ibm,p10-occ",
		.data = (व्योम *)occ_p10
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver occ_driver = अणु
	.driver = अणु
		.name = "occ",
		.of_match_table	= occ_match,
	पूर्ण,
	.probe	= occ_probe,
	.हटाओ = occ_हटाओ,
पूर्ण;

अटल पूर्णांक occ_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&occ_driver);
पूर्ण

अटल व्योम occ_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&occ_driver);

	ida_destroy(&occ_ida);
पूर्ण

module_init(occ_init);
module_निकास(occ_निकास);

MODULE_AUTHOR("Eddie James <eajames@linux.ibm.com>");
MODULE_DESCRIPTION("BMC P9 OCC driver");
MODULE_LICENSE("GPL");
