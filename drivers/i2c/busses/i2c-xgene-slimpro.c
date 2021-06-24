<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * X-Gene SLIMpro I2C Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Feng Kan <fkan@apm.com>
 * Author: Hieu Le <hnle@apm.com>
 *
 * This driver provides support क्रम X-Gene SLIMpro I2C device access
 * using the APM X-Gene SLIMpro mailbox driver.
 */
#समावेश <acpi/pcc.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MAILBOX_OP_TIMEOUT		1000	/* Operation समय out in ms */
#घोषणा MAILBOX_I2C_INDEX		0
#घोषणा SLIMPRO_IIC_BUS			1	/* Use I2C bus 1 only */

#घोषणा SMBUS_CMD_LEN			1
#घोषणा BYTE_DATA			1
#घोषणा WORD_DATA			2
#घोषणा BLOCK_DATA			3

#घोषणा SLIMPRO_IIC_I2C_PROTOCOL	0
#घोषणा SLIMPRO_IIC_SMB_PROTOCOL	1

#घोषणा SLIMPRO_IIC_READ		0
#घोषणा SLIMPRO_IIC_WRITE		1

#घोषणा IIC_SMB_WITHOUT_DATA_LEN	0
#घोषणा IIC_SMB_WITH_DATA_LEN		1

#घोषणा SLIMPRO_DEBUG_MSG		0
#घोषणा SLIMPRO_MSG_TYPE_SHIFT		28
#घोषणा SLIMPRO_DBG_SUBTYPE_I2C1READ	4
#घोषणा SLIMPRO_DBGMSG_TYPE_SHIFT	24
#घोषणा SLIMPRO_DBGMSG_TYPE_MASK	0x0F000000U
#घोषणा SLIMPRO_IIC_DEV_SHIFT		23
#घोषणा SLIMPRO_IIC_DEV_MASK		0x00800000U
#घोषणा SLIMPRO_IIC_DEVID_SHIFT		13
#घोषणा SLIMPRO_IIC_DEVID_MASK		0x007FE000U
#घोषणा SLIMPRO_IIC_RW_SHIFT		12
#घोषणा SLIMPRO_IIC_RW_MASK		0x00001000U
#घोषणा SLIMPRO_IIC_PROTO_SHIFT		11
#घोषणा SLIMPRO_IIC_PROTO_MASK		0x00000800U
#घोषणा SLIMPRO_IIC_ADDRLEN_SHIFT	8
#घोषणा SLIMPRO_IIC_ADDRLEN_MASK	0x00000700U
#घोषणा SLIMPRO_IIC_DATALEN_SHIFT	0
#घोषणा SLIMPRO_IIC_DATALEN_MASK	0x000000FFU

/*
 * SLIMpro I2C message encode
 *
 * dev		- Controller number (0-based)
 * chip		- I2C chip address
 * op		- SLIMPRO_IIC_READ or SLIMPRO_IIC_WRITE
 * proto	- SLIMPRO_IIC_SMB_PROTOCOL or SLIMPRO_IIC_I2C_PROTOCOL
 * addrlen	- Length of the address field
 * datalen	- Length of the data field
 */
#घोषणा SLIMPRO_IIC_ENCODE_MSG(dev, chip, op, proto, addrlen, datalen) \
	((SLIMPRO_DEBUG_MSG << SLIMPRO_MSG_TYPE_SHIFT) | \
	((SLIMPRO_DBG_SUBTYPE_I2C1READ << SLIMPRO_DBGMSG_TYPE_SHIFT) & \
	SLIMPRO_DBGMSG_TYPE_MASK) | \
	((dev << SLIMPRO_IIC_DEV_SHIFT) & SLIMPRO_IIC_DEV_MASK) | \
	((chip << SLIMPRO_IIC_DEVID_SHIFT) & SLIMPRO_IIC_DEVID_MASK) | \
	((op << SLIMPRO_IIC_RW_SHIFT) & SLIMPRO_IIC_RW_MASK) | \
	((proto << SLIMPRO_IIC_PROTO_SHIFT) & SLIMPRO_IIC_PROTO_MASK) | \
	((addrlen << SLIMPRO_IIC_ADDRLEN_SHIFT) & SLIMPRO_IIC_ADDRLEN_MASK) | \
	((datalen << SLIMPRO_IIC_DATALEN_SHIFT) & SLIMPRO_IIC_DATALEN_MASK))

#घोषणा SLIMPRO_MSG_TYPE(v)             (((v) & 0xF0000000) >> 28)

/*
 * Encode क्रम upper address क्रम block data
 */
#घोषणा SLIMPRO_IIC_ENCODE_FLAG_BUFADDR			0x80000000
#घोषणा SLIMPRO_IIC_ENCODE_FLAG_WITH_DATA_LEN(a)	((u32) (((a) << 30) \
								& 0x40000000))
#घोषणा SLIMPRO_IIC_ENCODE_UPPER_BUFADDR(a)		((u32) (((a) >> 12) \
								& 0x3FF00000))
#घोषणा SLIMPRO_IIC_ENCODE_ADDR(a)			((a) & 0x000FFFFF)

#घोषणा SLIMPRO_IIC_MSG_DWORD_COUNT			3

/* PCC related defines */
#घोषणा PCC_SIGNATURE			0x50424300
#घोषणा PCC_STS_CMD_COMPLETE		BIT(0)
#घोषणा PCC_STS_SCI_DOORBELL		BIT(1)
#घोषणा PCC_STS_ERR			BIT(2)
#घोषणा PCC_STS_PLAT_NOTIFY		BIT(3)
#घोषणा PCC_CMD_GENERATE_DB_INT		BIT(15)

काष्ठा slimpro_i2c_dev अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा device *dev;
	काष्ठा mbox_chan *mbox_chan;
	काष्ठा mbox_client mbox_client;
	पूर्णांक mbox_idx;
	काष्ठा completion rd_complete;
	u8 dma_buffer[I2C_SMBUS_BLOCK_MAX + 1]; /* dma_buffer[0] is used क्रम length */
	u32 *resp_msg;
	phys_addr_t comm_base_addr;
	व्योम *pcc_comm_addr;
पूर्ण;

#घोषणा to_slimpro_i2c_dev(cl)	\
		container_of(cl, काष्ठा slimpro_i2c_dev, mbox_client)

क्रमागत slimpro_i2c_version अणु
	XGENE_SLIMPRO_I2C_V1 = 0,
	XGENE_SLIMPRO_I2C_V2 = 1,
पूर्ण;

/*
 * This function tests and clears a biपंचांगask then वापसs its old value
 */
अटल u16 xgene_word_tst_and_clr(u16 *addr, u16 mask)
अणु
	u16 ret, val;

	val = le16_to_cpu(READ_ONCE(*addr));
	ret = val & mask;
	val &= ~mask;
	WRITE_ONCE(*addr, cpu_to_le16(val));

	वापस ret;
पूर्ण

अटल व्योम slimpro_i2c_rx_cb(काष्ठा mbox_client *cl, व्योम *mssg)
अणु
	काष्ठा slimpro_i2c_dev *ctx = to_slimpro_i2c_dev(cl);

	/*
	 * Response message क्रमmat:
	 * mssg[0] is the वापस code of the operation
	 * mssg[1] is the first data word
	 * mssg[2] is NOT used
	 */
	अगर (ctx->resp_msg)
		*ctx->resp_msg = ((u32 *)mssg)[1];

	अगर (ctx->mbox_client.tx_block)
		complete(&ctx->rd_complete);
पूर्ण

अटल व्योम slimpro_i2c_pcc_rx_cb(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा slimpro_i2c_dev *ctx = to_slimpro_i2c_dev(cl);
	काष्ठा acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;

	/* Check अगर platक्रमm sends पूर्णांकerrupt */
	अगर (!xgene_word_tst_and_clr(&generic_comm_base->status,
				    PCC_STS_SCI_DOORBELL))
		वापस;

	अगर (xgene_word_tst_and_clr(&generic_comm_base->status,
				   PCC_STS_CMD_COMPLETE)) अणु
		msg = generic_comm_base + 1;

		/* Response message msg[1] contains the वापस value. */
		अगर (ctx->resp_msg)
			*ctx->resp_msg = ((u32 *)msg)[1];

		complete(&ctx->rd_complete);
	पूर्ण
पूर्ण

अटल व्योम slimpro_i2c_pcc_tx_prepare(काष्ठा slimpro_i2c_dev *ctx, u32 *msg)
अणु
	काष्ठा acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;
	u32 *ptr = (व्योम *)(generic_comm_base + 1);
	u16 status;
	पूर्णांक i;

	WRITE_ONCE(generic_comm_base->signature,
		   cpu_to_le32(PCC_SIGNATURE | ctx->mbox_idx));

	WRITE_ONCE(generic_comm_base->command,
		   cpu_to_le16(SLIMPRO_MSG_TYPE(msg[0]) | PCC_CMD_GENERATE_DB_INT));

	status = le16_to_cpu(READ_ONCE(generic_comm_base->status));
	status &= ~PCC_STS_CMD_COMPLETE;
	WRITE_ONCE(generic_comm_base->status, cpu_to_le16(status));

	/* Copy the message to the PCC comm space */
	क्रम (i = 0; i < SLIMPRO_IIC_MSG_DWORD_COUNT; i++)
		WRITE_ONCE(ptr[i], cpu_to_le32(msg[i]));
पूर्ण

अटल पूर्णांक start_i2c_msg_xfer(काष्ठा slimpro_i2c_dev *ctx)
अणु
	अगर (ctx->mbox_client.tx_block || !acpi_disabled) अणु
		अगर (!रुको_क्रम_completion_समयout(&ctx->rd_complete,
						 msecs_to_jअगरfies(MAILBOX_OP_TIMEOUT)))
			वापस -ETIMEDOUT;
	पूर्ण

	/* Check of invalid data or no device */
	अगर (*ctx->resp_msg == 0xffffffff)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक slimpro_i2c_send_msg(काष्ठा slimpro_i2c_dev *ctx,
				u32 *msg,
				u32 *data)
अणु
	पूर्णांक rc;

	ctx->resp_msg = data;

	अगर (!acpi_disabled) अणु
		reinit_completion(&ctx->rd_complete);
		slimpro_i2c_pcc_tx_prepare(ctx, msg);
	पूर्ण

	rc = mbox_send_message(ctx->mbox_chan, msg);
	अगर (rc < 0)
		जाओ err;

	rc = start_i2c_msg_xfer(ctx);

err:
	अगर (!acpi_disabled)
		mbox_chan_txकरोne(ctx->mbox_chan, 0);

	ctx->resp_msg = शून्य;

	वापस rc;
पूर्ण

अटल पूर्णांक slimpro_i2c_rd(काष्ठा slimpro_i2c_dev *ctx, u32 chip,
			  u32 addr, u32 addrlen, u32 protocol,
			  u32 पढ़ोlen, u32 *data)
अणु
	u32 msg[3];

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip,
					SLIMPRO_IIC_READ, protocol, addrlen, पढ़ोlen);
	msg[1] = SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = 0;

	वापस slimpro_i2c_send_msg(ctx, msg, data);
पूर्ण

अटल पूर्णांक slimpro_i2c_wr(काष्ठा slimpro_i2c_dev *ctx, u32 chip,
			  u32 addr, u32 addrlen, u32 protocol, u32 ग_लिखोlen,
			  u32 data)
अणु
	u32 msg[3];

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip,
					SLIMPRO_IIC_WRITE, protocol, addrlen, ग_लिखोlen);
	msg[1] = SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = data;

	वापस slimpro_i2c_send_msg(ctx, msg, msg);
पूर्ण

अटल पूर्णांक slimpro_i2c_blkrd(काष्ठा slimpro_i2c_dev *ctx, u32 chip, u32 addr,
			     u32 addrlen, u32 protocol, u32 पढ़ोlen,
			     u32 with_data_len, व्योम *data)
अणु
	dma_addr_t paddr;
	u32 msg[3];
	पूर्णांक rc;

	paddr = dma_map_single(ctx->dev, ctx->dma_buffer, पढ़ोlen, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ctx->dev, paddr)) अणु
		dev_err(&ctx->adapter.dev, "Error in mapping dma buffer %p\n",
			ctx->dma_buffer);
		वापस -ENOMEM;
	पूर्ण

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip, SLIMPRO_IIC_READ,
					protocol, addrlen, पढ़ोlen);
	msg[1] = SLIMPRO_IIC_ENCODE_FLAG_BUFADDR |
		 SLIMPRO_IIC_ENCODE_FLAG_WITH_DATA_LEN(with_data_len) |
		 SLIMPRO_IIC_ENCODE_UPPER_BUFADDR(paddr) |
		 SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = (u32)paddr;

	rc = slimpro_i2c_send_msg(ctx, msg, msg);

	/* Copy to destination */
	स_नकल(data, ctx->dma_buffer, पढ़ोlen);

	dma_unmap_single(ctx->dev, paddr, पढ़ोlen, DMA_FROM_DEVICE);
	वापस rc;
पूर्ण

अटल पूर्णांक slimpro_i2c_blkwr(काष्ठा slimpro_i2c_dev *ctx, u32 chip,
			     u32 addr, u32 addrlen, u32 protocol, u32 ग_लिखोlen,
			     व्योम *data)
अणु
	dma_addr_t paddr;
	u32 msg[3];
	पूर्णांक rc;

	स_नकल(ctx->dma_buffer, data, ग_लिखोlen);
	paddr = dma_map_single(ctx->dev, ctx->dma_buffer, ग_लिखोlen,
			       DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, paddr)) अणु
		dev_err(&ctx->adapter.dev, "Error in mapping dma buffer %p\n",
			ctx->dma_buffer);
		वापस -ENOMEM;
	पूर्ण

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip, SLIMPRO_IIC_WRITE,
					protocol, addrlen, ग_लिखोlen);
	msg[1] = SLIMPRO_IIC_ENCODE_FLAG_BUFADDR |
		 SLIMPRO_IIC_ENCODE_UPPER_BUFADDR(paddr) |
		 SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = (u32)paddr;

	अगर (ctx->mbox_client.tx_block)
		reinit_completion(&ctx->rd_complete);

	rc = slimpro_i2c_send_msg(ctx, msg, msg);

	dma_unmap_single(ctx->dev, paddr, ग_लिखोlen, DMA_TO_DEVICE);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_slimpro_i2c_xfer(काष्ठा i2c_adapter *adap, u16 addr,
				  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				  u8 command, पूर्णांक size,
				  जोड़ i2c_smbus_data *data)
अणु
	काष्ठा slimpro_i2c_dev *ctx = i2c_get_adapdata(adap);
	पूर्णांक ret = -EOPNOTSUPP;
	u32 val;

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = slimpro_i2c_rd(ctx, addr, 0, 0,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     BYTE_DATA, &val);
			data->byte = val;
		पूर्ण अन्यथा अणु
			ret = slimpro_i2c_wr(ctx, addr, command, SMBUS_CMD_LEN,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     0, 0);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = slimpro_i2c_rd(ctx, addr, command, SMBUS_CMD_LEN,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     BYTE_DATA, &val);
			data->byte = val;
		पूर्ण अन्यथा अणु
			val = data->byte;
			ret = slimpro_i2c_wr(ctx, addr, command, SMBUS_CMD_LEN,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     BYTE_DATA, val);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = slimpro_i2c_rd(ctx, addr, command, SMBUS_CMD_LEN,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     WORD_DATA, &val);
			data->word = val;
		पूर्ण अन्यथा अणु
			val = data->word;
			ret = slimpro_i2c_wr(ctx, addr, command, SMBUS_CMD_LEN,
					     SLIMPRO_IIC_SMB_PROTOCOL,
					     WORD_DATA, val);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = slimpro_i2c_blkrd(ctx, addr, command,
						SMBUS_CMD_LEN,
						SLIMPRO_IIC_SMB_PROTOCOL,
						I2C_SMBUS_BLOCK_MAX + 1,
						IIC_SMB_WITH_DATA_LEN,
						&data->block[0]);

		पूर्ण अन्यथा अणु
			ret = slimpro_i2c_blkwr(ctx, addr, command,
						SMBUS_CMD_LEN,
						SLIMPRO_IIC_SMB_PROTOCOL,
						data->block[0] + 1,
						&data->block[0]);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = slimpro_i2c_blkrd(ctx, addr,
						command,
						SMBUS_CMD_LEN,
						SLIMPRO_IIC_I2C_PROTOCOL,
						I2C_SMBUS_BLOCK_MAX,
						IIC_SMB_WITHOUT_DATA_LEN,
						&data->block[1]);
		पूर्ण अन्यथा अणु
			ret = slimpro_i2c_blkwr(ctx, addr, command,
						SMBUS_CMD_LEN,
						SLIMPRO_IIC_I2C_PROTOCOL,
						data->block[0],
						&data->block[1]);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
* Return list of supported functionality.
*/
अटल u32 xgene_slimpro_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm xgene_slimpro_i2c_algorithm = अणु
	.smbus_xfer = xgene_slimpro_i2c_xfer,
	.functionality = xgene_slimpro_i2c_func,
पूर्ण;

अटल पूर्णांक xgene_slimpro_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा slimpro_i2c_dev *ctx;
	काष्ठा i2c_adapter *adapter;
	काष्ठा mbox_client *cl;
	पूर्णांक rc;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ctx);
	cl = &ctx->mbox_client;

	/* Request mailbox channel */
	cl->dev = &pdev->dev;
	init_completion(&ctx->rd_complete);
	cl->tx_tout = MAILBOX_OP_TIMEOUT;
	cl->knows_txकरोne = false;
	अगर (acpi_disabled) अणु
		cl->tx_block = true;
		cl->rx_callback = slimpro_i2c_rx_cb;
		ctx->mbox_chan = mbox_request_channel(cl, MAILBOX_I2C_INDEX);
		अगर (IS_ERR(ctx->mbox_chan)) अणु
			dev_err(&pdev->dev, "i2c mailbox channel request failed\n");
			वापस PTR_ERR(ctx->mbox_chan);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा acpi_pcct_hw_reduced *cppc_ss;
		स्थिर काष्ठा acpi_device_id *acpi_id;
		पूर्णांक version = XGENE_SLIMPRO_I2C_V1;

		acpi_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
					    &pdev->dev);
		अगर (!acpi_id)
			वापस -EINVAL;

		version = (पूर्णांक)acpi_id->driver_data;

		अगर (device_property_पढ़ो_u32(&pdev->dev, "pcc-channel",
					     &ctx->mbox_idx))
			ctx->mbox_idx = MAILBOX_I2C_INDEX;

		cl->tx_block = false;
		cl->rx_callback = slimpro_i2c_pcc_rx_cb;
		ctx->mbox_chan = pcc_mbox_request_channel(cl, ctx->mbox_idx);
		अगर (IS_ERR(ctx->mbox_chan)) अणु
			dev_err(&pdev->dev, "PCC mailbox channel request failed\n");
			वापस PTR_ERR(ctx->mbox_chan);
		पूर्ण

		/*
		 * The PCC mailbox controller driver should
		 * have parsed the PCCT (global table of all
		 * PCC channels) and stored poपूर्णांकers to the
		 * subspace communication region in con_priv.
		 */
		cppc_ss = ctx->mbox_chan->con_priv;
		अगर (!cppc_ss) अणु
			dev_err(&pdev->dev, "PPC subspace not found\n");
			rc = -ENOENT;
			जाओ mbox_err;
		पूर्ण

		अगर (!ctx->mbox_chan->mbox->txकरोne_irq) अणु
			dev_err(&pdev->dev, "PCC IRQ not supported\n");
			rc = -ENOENT;
			जाओ mbox_err;
		पूर्ण

		/*
		 * This is the shared communication region
		 * क्रम the OS and Platक्रमm to communicate over.
		 */
		ctx->comm_base_addr = cppc_ss->base_address;
		अगर (ctx->comm_base_addr) अणु
			अगर (version == XGENE_SLIMPRO_I2C_V2)
				ctx->pcc_comm_addr = memremap(
							ctx->comm_base_addr,
							cppc_ss->length,
							MEMREMAP_WT);
			अन्यथा
				ctx->pcc_comm_addr = memremap(
							ctx->comm_base_addr,
							cppc_ss->length,
							MEMREMAP_WB);
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Failed to get PCC comm region\n");
			rc = -ENOENT;
			जाओ mbox_err;
		पूर्ण

		अगर (!ctx->pcc_comm_addr) अणु
			dev_err(&pdev->dev,
				"Failed to ioremap PCC comm region\n");
			rc = -ENOMEM;
			जाओ mbox_err;
		पूर्ण
	पूर्ण
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc)
		dev_warn(&pdev->dev, "Unable to set dma mask\n");

	/* Setup I2C adapter */
	adapter = &ctx->adapter;
	snम_लिखो(adapter->name, माप(adapter->name), "MAILBOX I2C");
	adapter->algo = &xgene_slimpro_i2c_algorithm;
	adapter->class = I2C_CLASS_HWMON;
	adapter->dev.parent = &pdev->dev;
	adapter->dev.of_node = pdev->dev.of_node;
	ACPI_COMPANION_SET(&adapter->dev, ACPI_COMPANION(&pdev->dev));
	i2c_set_adapdata(adapter, ctx);
	rc = i2c_add_adapter(adapter);
	अगर (rc)
		जाओ mbox_err;

	dev_info(&pdev->dev, "Mailbox I2C Adapter registered\n");
	वापस 0;

mbox_err:
	अगर (acpi_disabled)
		mbox_मुक्त_channel(ctx->mbox_chan);
	अन्यथा
		pcc_mbox_मुक्त_channel(ctx->mbox_chan);

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_slimpro_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा slimpro_i2c_dev *ctx = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&ctx->adapter);

	अगर (acpi_disabled)
		mbox_मुक्त_channel(ctx->mbox_chan);
	अन्यथा
		pcc_mbox_मुक्त_channel(ctx->mbox_chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_slimpro_i2c_dt_ids[] = अणु
	अणु.compatible = "apm,xgene-slimpro-i2c" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_slimpro_i2c_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_slimpro_i2c_acpi_ids[] = अणु
	अणु"APMC0D40", XGENE_SLIMPRO_I2C_V1पूर्ण,
	अणु"APMC0D8B", XGENE_SLIMPRO_I2C_V2पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_slimpro_i2c_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xgene_slimpro_i2c_driver = अणु
	.probe	= xgene_slimpro_i2c_probe,
	.हटाओ	= xgene_slimpro_i2c_हटाओ,
	.driver	= अणु
		.name	= "xgene-slimpro-i2c",
		.of_match_table = of_match_ptr(xgene_slimpro_i2c_dt_ids),
		.acpi_match_table = ACPI_PTR(xgene_slimpro_i2c_acpi_ids)
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xgene_slimpro_i2c_driver);

MODULE_DESCRIPTION("APM X-Gene SLIMpro I2C driver");
MODULE_AUTHOR("Feng Kan <fkan@apm.com>");
MODULE_AUTHOR("Hieu Le <hnle@apm.com>");
MODULE_LICENSE("GPL");
