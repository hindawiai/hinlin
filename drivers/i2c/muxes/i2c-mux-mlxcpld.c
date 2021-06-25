<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*
 * Mellanox i2c mux driver
 *
 * Copyright (C) 2016-2020 Mellanox Technologies
 */

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/mlxcpld.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* mlxcpld_mux - mux control काष्ठाure:
 * @last_val - last selected रेजिस्टर value or -1 अगर mux deselected
 * @client - I2C device client
 * @pdata: platक्रमm data
 */
काष्ठा mlxcpld_mux अणु
	पूर्णांक last_val;
	काष्ठा i2c_client *client;
	काष्ठा mlxcpld_mux_plat_data pdata;
पूर्ण;

/* MUX logic description.
 * Driver can support dअगरferent mux control logic, according to CPLD
 * implementation.
 *
 * Connectivity schema.
 *
 * i2c-mlxcpld                                 Digital               Analog
 * driver
 * *--------*                                 * -> mux1 (virt bus2) -> mux -> |
 * | I2CLPC | i2c physical                    * -> mux2 (virt bus3) -> mux -> |
 * | bridge | bus 1                 *---------*                               |
 * | logic  |---------------------> * mux reg *                               |
 * | in CPLD|                       *---------*                               |
 * *--------*   i2c-mux-mlxpcld          ^    * -> muxn (virt busn) -> mux -> |
 *     |        driver                   |                                    |
 *     |        *---------------*        |                              Devices
 *     |        * CPLD (i2c bus)* select |
 *     |        * रेजिस्टरs क्रम *--------*
 *     |        * mux selection * deselect
 *     |        *---------------*
 *     |                 |
 * <-------->     <----------->
 * i2c cntrl      Board cntrl reg
 * reg space      space (mux select,
 *                IO, LED, WD, info)
 *
 */

/* Write to mux रेजिस्टर. Don't use i2c_transfer() and i2c_smbus_xfer()
 * क्रम this as they will try to lock adapter a second समय.
 */
अटल पूर्णांक mlxcpld_mux_reg_ग_लिखो(काष्ठा i2c_adapter *adap,
				 काष्ठा mlxcpld_mux *mux, u32 val)
अणु
	काष्ठा i2c_client *client = mux->client;
	जोड़ i2c_smbus_data data;
	काष्ठा i2c_msg msg;
	u8 buf[3];

	चयन (mux->pdata.reg_size) अणु
	हाल 1:
		data.byte = val;
		वापस __i2c_smbus_xfer(adap, client->addr, client->flags,
					I2C_SMBUS_WRITE, mux->pdata.sel_reg_addr,
					I2C_SMBUS_BYTE_DATA, &data);
	हाल 2:
		buf[0] = mux->pdata.sel_reg_addr >> 8;
		buf[1] = mux->pdata.sel_reg_addr;
		buf[2] = val;
		msg.addr = client->addr;
		msg.buf = buf;
		msg.len = mux->pdata.reg_size + 1;
		msg.flags = 0;
		वापस __i2c_transfer(adap, &msg, 1);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxcpld_mux_select_chan(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा mlxcpld_mux *mux = i2c_mux_priv(muxc);
	u32 regval = chan;
	पूर्णांक err = 0;

	अगर (mux->pdata.reg_size == 1)
		regval += 1;

	/* Only select the channel अगर its dअगरferent from the last channel */
	अगर (mux->last_val != regval) अणु
		err = mlxcpld_mux_reg_ग_लिखो(muxc->parent, mux, regval);
		mux->last_val = err < 0 ? -1 : regval;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlxcpld_mux_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा mlxcpld_mux *mux = i2c_mux_priv(muxc);

	/* Deselect active channel */
	mux->last_val = -1;

	वापस mlxcpld_mux_reg_ग_लिखो(muxc->parent, mux, 0);
पूर्ण

/* Probe/reomove functions */
अटल पूर्णांक mlxcpld_mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxcpld_mux_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा i2c_client *client = to_i2c_client(pdev->dev.parent);
	काष्ठा i2c_mux_core *muxc;
	काष्ठा mlxcpld_mux *data;
	पूर्णांक num, err;
	u32 func;

	अगर (!pdata)
		वापस -EINVAL;

	चयन (pdata->reg_size) अणु
	हाल 1:
		func = I2C_FUNC_SMBUS_WRITE_BYTE_DATA;
		अवरोध;
	हाल 2:
		func = I2C_FUNC_I2C;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, func))
		वापस -ENODEV;

	muxc = i2c_mux_alloc(client->adapter, &pdev->dev, pdata->num_adaps,
			     माप(*data), 0, mlxcpld_mux_select_chan,
			     mlxcpld_mux_deselect);
	अगर (!muxc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, muxc);
	data = i2c_mux_priv(muxc);
	data->client = client;
	स_नकल(&data->pdata, pdata, माप(*pdata));
	data->last_val = -1; /* क्रमce the first selection */

	/* Create an adapter क्रम each channel. */
	क्रम (num = 0; num < pdata->num_adaps; num++) अणु
		err = i2c_mux_add_adapter(muxc, 0, pdata->chan_ids[num], 0);
		अगर (err)
			जाओ virt_reg_failed;
	पूर्ण

	/* Notअगरy caller when all channels' adapters are created. */
	अगर (pdata->completion_notअगरy)
		pdata->completion_notअगरy(pdata->handle, muxc->parent, muxc->adapter);

	वापस 0;

virt_reg_failed:
	i2c_mux_del_adapters(muxc);
	वापस err;
पूर्ण

अटल पूर्णांक mlxcpld_mux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxcpld_mux_driver = अणु
	.driver = अणु
		.name = "i2c-mux-mlxcpld",
	पूर्ण,
	.probe = mlxcpld_mux_probe,
	.हटाओ = mlxcpld_mux_हटाओ,
पूर्ण;

module_platक्रमm_driver(mlxcpld_mux_driver);

MODULE_AUTHOR("Michael Shych (michaels@mellanox.com)");
MODULE_DESCRIPTION("Mellanox I2C-CPLD-MUX driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:i2c-mux-mlxcpld");
