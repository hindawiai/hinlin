<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp 2019

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fsi-occ.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "common.h"

#घोषणा OCC_TIMEOUT_MS			1000
#घोषणा OCC_CMD_IN_PRG_WAIT_MS		50

/* OCB (on-chip control bridge - पूर्णांकerface to OCC) रेजिस्टरs */
#घोषणा OCB_DATA1			0x6B035
#घोषणा OCB_ADDR			0x6B070
#घोषणा OCB_DATA3			0x6B075

/* OCC SRAM address space */
#घोषणा OCC_SRAM_ADDR_CMD		0xFFFF6000
#घोषणा OCC_SRAM_ADDR_RESP		0xFFFF7000

#घोषणा OCC_DATA_ATTN			0x20010000

काष्ठा p8_i2c_occ अणु
	काष्ठा occ occ;
	काष्ठा i2c_client *client;
पूर्ण;

#घोषणा to_p8_i2c_occ(x)	container_of((x), काष्ठा p8_i2c_occ, occ)

अटल पूर्णांक p8_i2c_occ_माला_लोcom(काष्ठा i2c_client *client, u32 address, u8 *data)
अणु
	sमाप_प्रकार rc;
	__be64 buf;
	काष्ठा i2c_msg msgs[2];

	/* p8 i2c slave requires shअगरt */
	address <<= 1;

	msgs[0].addr = client->addr;
	msgs[0].flags = client->flags & I2C_M_TEN;
	msgs[0].len = माप(u32);
	/* address is a scom address; bus-endian */
	msgs[0].buf = (अक्षर *)&address;

	/* data from OCC is big-endian */
	msgs[1].addr = client->addr;
	msgs[1].flags = (client->flags & I2C_M_TEN) | I2C_M_RD;
	msgs[1].len = माप(u64);
	msgs[1].buf = (अक्षर *)&buf;

	rc = i2c_transfer(client->adapter, msgs, 2);
	अगर (rc < 0)
		वापस rc;

	*(u64 *)data = be64_to_cpu(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक p8_i2c_occ_माला_दोcom(काष्ठा i2c_client *client, u32 address, u8 *data)
अणु
	u32 buf[3];
	sमाप_प्रकार rc;

	/* p8 i2c slave requires shअगरt */
	address <<= 1;

	/* address is bus-endian; data passed through from user as-is */
	buf[0] = address;
	स_नकल(&buf[1], &data[4], माप(u32));
	स_नकल(&buf[2], data, माप(u32));

	rc = i2c_master_send(client, (स्थिर अक्षर *)buf, माप(buf));
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (rc != माप(buf))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक p8_i2c_occ_माला_दोcom_u32(काष्ठा i2c_client *client, u32 address,
				  u32 data0, u32 data1)
अणु
	u8 buf[8];

	स_नकल(buf, &data0, 4);
	स_नकल(buf + 4, &data1, 4);

	वापस p8_i2c_occ_माला_दोcom(client, address, buf);
पूर्ण

अटल पूर्णांक p8_i2c_occ_माला_दोcom_be(काष्ठा i2c_client *client, u32 address,
				 u8 *data)
अणु
	__be32 data0, data1;

	स_नकल(&data0, data, 4);
	स_नकल(&data1, data + 4, 4);

	वापस p8_i2c_occ_माला_दोcom_u32(client, address, be32_to_cpu(data0),
				      be32_to_cpu(data1));
पूर्ण

अटल पूर्णांक p8_i2c_occ_send_cmd(काष्ठा occ *occ, u8 *cmd)
अणु
	पूर्णांक i, rc;
	अचिन्हित दीर्घ start;
	u16 data_length;
	स्थिर अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(OCC_TIMEOUT_MS);
	स्थिर दीर्घ रुको_समय = msecs_to_jअगरfies(OCC_CMD_IN_PRG_WAIT_MS);
	काष्ठा p8_i2c_occ *ctx = to_p8_i2c_occ(occ);
	काष्ठा i2c_client *client = ctx->client;
	काष्ठा occ_response *resp = &occ->resp;

	start = jअगरfies;

	/* set sram address क्रम command */
	rc = p8_i2c_occ_माला_दोcom_u32(client, OCB_ADDR, OCC_SRAM_ADDR_CMD, 0);
	अगर (rc)
		वापस rc;

	/* ग_लिखो command (expected to alपढ़ोy be BE), we need bus-endian... */
	rc = p8_i2c_occ_माला_दोcom_be(client, OCB_DATA3, cmd);
	अगर (rc)
		वापस rc;

	/* trigger OCC attention */
	rc = p8_i2c_occ_माला_दोcom_u32(client, OCB_DATA1, OCC_DATA_ATTN, 0);
	अगर (rc)
		वापस rc;

	करो अणु
		/* set sram address क्रम response */
		rc = p8_i2c_occ_माला_दोcom_u32(client, OCB_ADDR,
					    OCC_SRAM_ADDR_RESP, 0);
		अगर (rc)
			वापस rc;

		rc = p8_i2c_occ_माला_लोcom(client, OCB_DATA3, (u8 *)resp);
		अगर (rc)
			वापस rc;

		/* रुको क्रम OCC */
		अगर (resp->वापस_status == OCC_RESP_CMD_IN_PRG) अणु
			rc = -EALREADY;

			अगर (समय_after(jअगरfies, start + समयout))
				अवरोध;

			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(रुको_समय);
		पूर्ण
	पूर्ण जबतक (rc);

	/* check the OCC response */
	चयन (resp->वापस_status) अणु
	हाल OCC_RESP_CMD_IN_PRG:
		rc = -ETIMEDOUT;
		अवरोध;
	हाल OCC_RESP_SUCCESS:
		rc = 0;
		अवरोध;
	हाल OCC_RESP_CMD_INVAL:
	हाल OCC_RESP_CMD_LEN_INVAL:
	हाल OCC_RESP_DATA_INVAL:
	हाल OCC_RESP_CHKSUM_ERR:
		rc = -EINVAL;
		अवरोध;
	हाल OCC_RESP_INT_ERR:
	हाल OCC_RESP_BAD_STATE:
	हाल OCC_RESP_CRIT_EXCEPT:
	हाल OCC_RESP_CRIT_INIT:
	हाल OCC_RESP_CRIT_WATCHDOG:
	हाल OCC_RESP_CRIT_OCB:
	हाल OCC_RESP_CRIT_HW:
		rc = -EREMOTEIO;
		अवरोध;
	शेष:
		rc = -EPROTO;
	पूर्ण

	अगर (rc < 0)
		वापस rc;

	data_length = get_unaligned_be16(&resp->data_length);
	अगर (data_length > OCC_RESP_DATA_BYTES)
		वापस -EMSGSIZE;

	/* fetch the rest of the response data */
	क्रम (i = 8; i < data_length + 7; i += 8) अणु
		rc = p8_i2c_occ_माला_लोcom(client, OCB_DATA3, ((u8 *)resp) + i);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक p8_i2c_occ_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा occ *occ;
	काष्ठा p8_i2c_occ *ctx = devm_kzalloc(&client->dev, माप(*ctx),
					      GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->client = client;
	occ = &ctx->occ;
	occ->bus_dev = &client->dev;
	dev_set_drvdata(&client->dev, occ);

	occ->घातr_sample_समय_us = 250;
	occ->poll_cmd_data = 0x10;		/* P8 OCC poll data */
	occ->send_cmd = p8_i2c_occ_send_cmd;

	वापस occ_setup(occ, "p8_occ");
पूर्ण

अटल पूर्णांक p8_i2c_occ_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा occ *occ = dev_get_drvdata(&client->dev);

	occ_shutकरोwn(occ);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id p8_i2c_occ_of_match[] = अणु
	अणु .compatible = "ibm,p8-occ-hwmon" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, p8_i2c_occ_of_match);

अटल काष्ठा i2c_driver p8_i2c_occ_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "occ-hwmon",
		.of_match_table = p8_i2c_occ_of_match,
	पूर्ण,
	.probe_new = p8_i2c_occ_probe,
	.हटाओ = p8_i2c_occ_हटाओ,
पूर्ण;

module_i2c_driver(p8_i2c_occ_driver);

MODULE_AUTHOR("Eddie James <eajames@linux.ibm.com>");
MODULE_DESCRIPTION("BMC P8 OCC hwmon driver");
MODULE_LICENSE("GPL");
