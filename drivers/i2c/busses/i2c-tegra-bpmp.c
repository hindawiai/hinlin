<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/i2c/busses/i2c-tegra-bpmp.c
 *
 * Copyright (c) 2016 NVIDIA Corporation.  All rights reserved.
 *
 * Author: Shardar Sharअगरf Md <smohammed@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <soc/tegra/bpmp-abi.h>
#समावेश <soc/tegra/bpmp.h>

/*
 * Serialized I2C message header size is 6 bytes and includes address, flags
 * and length
 */
#घोषणा SERIALI2C_HDR_SIZE 6

काष्ठा tegra_bpmp_i2c अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा device *dev;

	काष्ठा tegra_bpmp *bpmp;
	अचिन्हित पूर्णांक bus;
पूर्ण;

/*
 * Linux flags are translated to BPMP defined I2C flags that are used in BPMP
 * firmware I2C driver to aव्योम any issues in future अगर Linux I2C flags are
 * changed.
 */
अटल व्योम tegra_bpmp_xlate_flags(u16 flags, u16 *out)
अणु
	अगर (flags & I2C_M_TEN)
		*out |= SERIALI2C_TEN;

	अगर (flags & I2C_M_RD)
		*out |= SERIALI2C_RD;

	अगर (flags & I2C_M_STOP)
		*out |= SERIALI2C_STOP;

	अगर (flags & I2C_M_NOSTART)
		*out |= SERIALI2C_NOSTART;

	अगर (flags & I2C_M_REV_सूची_ADDR)
		*out |= SERIALI2C_REV_सूची_ADDR;

	अगर (flags & I2C_M_IGNORE_NAK)
		*out |= SERIALI2C_IGNORE_NAK;

	अगर (flags & I2C_M_NO_RD_ACK)
		*out |= SERIALI2C_NO_RD_ACK;

	अगर (flags & I2C_M_RECV_LEN)
		*out |= SERIALI2C_RECV_LEN;
पूर्ण

/*
 * The serialized I2C क्रमmat is simply the following:
 * [addr little-endian][flags little-endian][len little-endian][data अगर ग_लिखो]
 * [addr little-endian][flags little-endian][len little-endian][data अगर ग_लिखो]
 *  ...
 *
 * The flags are translated from Linux kernel representation to seriali2c
 * representation. Any undefined flag being set causes an error.
 *
 * The data is there only क्रम ग_लिखोs. Reads have the data transferred in the
 * other direction, and thus data is not present.
 *
 * See deserialize_i2c करोcumentation क्रम the data क्रमmat in the other direction.
 */
अटल व्योम tegra_bpmp_serialize_i2c_msg(काष्ठा tegra_bpmp_i2c *i2c,
					काष्ठा mrq_i2c_request *request,
					काष्ठा i2c_msg *msgs,
					अचिन्हित पूर्णांक num)
अणु
	अक्षर *buf = request->xfer.data_buf;
	अचिन्हित पूर्णांक i, j, pos = 0;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा i2c_msg *msg = &msgs[i];
		u16 flags = 0;

		tegra_bpmp_xlate_flags(msg->flags, &flags);

		buf[pos++] = msg->addr & 0xff;
		buf[pos++] = (msg->addr & 0xff00) >> 8;
		buf[pos++] = flags & 0xff;
		buf[pos++] = (flags & 0xff00) >> 8;
		buf[pos++] = msg->len & 0xff;
		buf[pos++] = (msg->len & 0xff00) >> 8;

		अगर ((flags & SERIALI2C_RD) == 0) अणु
			क्रम (j = 0; j < msg->len; j++)
				buf[pos++] = msg->buf[j];
		पूर्ण
	पूर्ण

	request->xfer.data_size = pos;
पूर्ण

/*
 * The data in the BPMP -> CPU direction is composed of sequential blocks क्रम
 * those messages that have I2C_M_RD. So, क्रम example, अगर you have:
 *
 * - !I2C_M_RD, len == 5, data == a0 01 02 03 04
 * - !I2C_M_RD, len == 1, data == a0
 * - I2C_M_RD, len == 2, data == [uninitialized buffer 1]
 * - !I2C_M_RD, len == 1, data == a2
 * - I2C_M_RD, len == 2, data == [uninitialized buffer 2]
 *
 * ...then the data in the BPMP -> CPU direction would be 4 bytes total, and
 * would contain 2 bytes that will go to uninitialized buffer 1, and 2 bytes
 * that will go to uninitialized buffer 2.
 */
अटल पूर्णांक tegra_bpmp_i2c_deserialize(काष्ठा tegra_bpmp_i2c *i2c,
				      काष्ठा mrq_i2c_response *response,
				      काष्ठा i2c_msg *msgs,
				      अचिन्हित पूर्णांक num)
अणु
	माप_प्रकार size = response->xfer.data_size, len = 0, pos = 0;
	अक्षर *buf = response->xfer.data_buf;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (msgs[i].flags & I2C_M_RD)
			len += msgs[i].len;

	अगर (len != size)
		वापस -EINVAL;

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD) अणु
			स_नकल(msgs[i].buf, buf + pos, msgs[i].len);
			pos += msgs[i].len;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_msg_len_check(काष्ठा i2c_msg *msgs, अचिन्हित पूर्णांक num)
अणु
	माप_प्रकार tx_len = 0, rx_len = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (!(msgs[i].flags & I2C_M_RD))
			tx_len += SERIALI2C_HDR_SIZE + msgs[i].len;

	अगर (tx_len > TEGRA_I2C_IPC_MAX_IN_BUF_SIZE)
		वापस -EINVAL;

	क्रम (i = 0; i < num; i++)
		अगर ((msgs[i].flags & I2C_M_RD))
			rx_len += msgs[i].len;

	अगर (rx_len > TEGRA_I2C_IPC_MAX_OUT_BUF_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_msg_xfer(काष्ठा tegra_bpmp_i2c *i2c,
				   काष्ठा mrq_i2c_request *request,
				   काष्ठा mrq_i2c_response *response,
				   bool atomic)
अणु
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	request->cmd = CMD_I2C_XFER;
	request->xfer.bus_id = i2c->bus;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_I2C;
	msg.tx.data = request;
	msg.tx.size = माप(*request);
	msg.rx.data = response;
	msg.rx.size = माप(*response);

	अगर (atomic)
		err = tegra_bpmp_transfer_atomic(i2c->bpmp, &msg);
	अन्यथा
		err = tegra_bpmp_transfer(i2c->bpmp, &msg);

	अगर (err < 0) अणु
		dev_err(i2c->dev, "failed to transfer message: %d\n", err);
		वापस err;
	पूर्ण

	अगर (msg.rx.ret != 0) अणु
		अगर (msg.rx.ret == -BPMP_EAGAIN) अणु
			dev_dbg(i2c->dev, "arbitration lost\n");
			वापस -EAGAIN;
		पूर्ण

		अगर (msg.rx.ret == -BPMP_ETIMEDOUT) अणु
			dev_dbg(i2c->dev, "timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण

		अगर (msg.rx.ret == -BPMP_ENXIO) अणु
			dev_dbg(i2c->dev, "NAK\n");
			वापस -ENXIO;
		पूर्ण

		dev_err(i2c->dev, "transaction failed: %d\n", msg.rx.ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_xfer_common(काष्ठा i2c_adapter *adapter,
				      काष्ठा i2c_msg *msgs, पूर्णांक num,
				      bool atomic)
अणु
	काष्ठा tegra_bpmp_i2c *i2c = i2c_get_adapdata(adapter);
	काष्ठा mrq_i2c_response response;
	काष्ठा mrq_i2c_request request;
	पूर्णांक err;

	err = tegra_bpmp_i2c_msg_len_check(msgs, num);
	अगर (err < 0) अणु
		dev_err(i2c->dev, "unsupported message length\n");
		वापस err;
	पूर्ण

	स_रखो(&request, 0, माप(request));
	स_रखो(&response, 0, माप(response));

	tegra_bpmp_serialize_i2c_msg(i2c, &request, msgs, num);
	err = tegra_bpmp_i2c_msg_xfer(i2c, &request, &response, atomic);
	अगर (err < 0) अणु
		dev_err(i2c->dev, "failed to transfer message: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_bpmp_i2c_deserialize(i2c, &response, msgs, num);
	अगर (err < 0) अणु
		dev_err(i2c->dev, "failed to deserialize message: %d\n", err);
		वापस err;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_xfer(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस tegra_bpmp_i2c_xfer_common(adapter, msgs, num, false);
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_xfer_atomic(काष्ठा i2c_adapter *adapter,
				      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस tegra_bpmp_i2c_xfer_common(adapter, msgs, num, true);
पूर्ण

अटल u32 tegra_bpmp_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR |
	       I2C_FUNC_PROTOCOL_MANGLING | I2C_FUNC_NOSTART;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm tegra_bpmp_i2c_algo = अणु
	.master_xfer = tegra_bpmp_i2c_xfer,
	.master_xfer_atomic = tegra_bpmp_i2c_xfer_atomic,
	.functionality = tegra_bpmp_i2c_func,
पूर्ण;

अटल पूर्णांक tegra_bpmp_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_bpmp_i2c *i2c;
	u32 value;
	पूर्णांक err;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->dev = &pdev->dev;

	i2c->bpmp = dev_get_drvdata(pdev->dev.parent);
	अगर (!i2c->bpmp)
		वापस -ENODEV;

	err = of_property_पढ़ो_u32(pdev->dev.of_node, "nvidia,bpmp-bus-id",
				   &value);
	अगर (err < 0)
		वापस err;

	i2c->bus = value;

	i2c_set_adapdata(&i2c->adapter, i2c);
	i2c->adapter.owner = THIS_MODULE;
	strlcpy(i2c->adapter.name, "Tegra BPMP I2C adapter",
		माप(i2c->adapter.name));
	i2c->adapter.algo = &tegra_bpmp_i2c_algo;
	i2c->adapter.dev.parent = &pdev->dev;
	i2c->adapter.dev.of_node = pdev->dev.of_node;

	platक्रमm_set_drvdata(pdev, i2c);

	वापस i2c_add_adapter(&i2c->adapter);
पूर्ण

अटल पूर्णांक tegra_bpmp_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_bpmp_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_bpmp_i2c_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-bpmp-i2c", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_bpmp_i2c_of_match);

अटल काष्ठा platक्रमm_driver tegra_bpmp_i2c_driver = अणु
	.driver = अणु
		.name = "tegra-bpmp-i2c",
		.of_match_table = tegra_bpmp_i2c_of_match,
	पूर्ण,
	.probe = tegra_bpmp_i2c_probe,
	.हटाओ = tegra_bpmp_i2c_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_bpmp_i2c_driver);

MODULE_DESCRIPTION("NVIDIA Tegra BPMP I2C bus controller driver");
MODULE_AUTHOR("Shardar Shariff Md <smohammed@nvidia.com>");
MODULE_AUTHOR("Juha-Matti Tilli");
MODULE_LICENSE("GPL v2");
