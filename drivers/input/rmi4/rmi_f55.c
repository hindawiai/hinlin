<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015 Synaptics Incorporated
 * Copyright (C) 2016 Zodiac Inflight Innovations
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश "rmi_driver.h"

#घोषणा F55_NAME		"rmi4_f55"

/* F55 data offsets */
#घोषणा F55_NUM_RX_OFFSET	0
#घोषणा F55_NUM_TX_OFFSET	1
#घोषणा F55_PHYS_CHAR_OFFSET	2

/* Only पढ़ो required query रेजिस्टरs */
#घोषणा F55_QUERY_LEN		3

/* F55 capabilities */
#घोषणा F55_CAP_SENSOR_ASSIGN	BIT(0)

काष्ठा f55_data अणु
	काष्ठा rmi_function *fn;

	u8 qry[F55_QUERY_LEN];
	u8 num_rx_electrodes;
	u8 cfg_num_rx_electrodes;
	u8 num_tx_electrodes;
	u8 cfg_num_tx_electrodes;
पूर्ण;

अटल पूर्णांक rmi_f55_detect(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f55_data *f55;
	पूर्णांक error;

	f55 = dev_get_drvdata(&fn->dev);

	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr,
			       &f55->qry, माप(f55->qry));
	अगर (error) अणु
		dev_err(&fn->dev, "%s: Failed to query F55 properties\n",
			__func__);
		वापस error;
	पूर्ण

	f55->num_rx_electrodes = f55->qry[F55_NUM_RX_OFFSET];
	f55->num_tx_electrodes = f55->qry[F55_NUM_TX_OFFSET];

	f55->cfg_num_rx_electrodes = f55->num_rx_electrodes;
	f55->cfg_num_tx_electrodes = f55->num_rx_electrodes;

	drv_data->num_rx_electrodes = f55->cfg_num_rx_electrodes;
	drv_data->num_tx_electrodes = f55->cfg_num_rx_electrodes;

	अगर (f55->qry[F55_PHYS_CHAR_OFFSET] & F55_CAP_SENSOR_ASSIGN) अणु
		पूर्णांक i, total;
		u8 buf[256];

		/*
		 * Calculate the number of enabled receive and transmit
		 * electrodes by पढ़ोing F55:Ctrl1 (sensor receiver assignment)
		 * and F55:Ctrl2 (sensor transmitter assignment). The number of
		 * enabled electrodes is the sum of all field entries with a
		 * value other than 0xff.
		 */
		error = rmi_पढ़ो_block(fn->rmi_dev,
				       fn->fd.control_base_addr + 1,
				       buf, f55->num_rx_electrodes);
		अगर (!error) अणु
			total = 0;
			क्रम (i = 0; i < f55->num_rx_electrodes; i++) अणु
				अगर (buf[i] != 0xff)
					total++;
			पूर्ण
			f55->cfg_num_rx_electrodes = total;
			drv_data->num_rx_electrodes = total;
		पूर्ण

		error = rmi_पढ़ो_block(fn->rmi_dev,
				       fn->fd.control_base_addr + 2,
				       buf, f55->num_tx_electrodes);
		अगर (!error) अणु
			total = 0;
			क्रम (i = 0; i < f55->num_tx_electrodes; i++) अणु
				अगर (buf[i] != 0xff)
					total++;
			पूर्ण
			f55->cfg_num_tx_electrodes = total;
			drv_data->num_tx_electrodes = total;
		पूर्ण
	पूर्ण

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F55 num_rx_electrodes: %d (raw %d)\n",
		f55->cfg_num_rx_electrodes, f55->num_rx_electrodes);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F55 num_tx_electrodes: %d (raw %d)\n",
		f55->cfg_num_tx_electrodes, f55->num_tx_electrodes);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f55_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा f55_data *f55;

	f55 = devm_kzalloc(&fn->dev, माप(काष्ठा f55_data), GFP_KERNEL);
	अगर (!f55)
		वापस -ENOMEM;

	f55->fn = fn;
	dev_set_drvdata(&fn->dev, f55);

	वापस rmi_f55_detect(fn);
पूर्ण

काष्ठा rmi_function_handler rmi_f55_handler = अणु
	.driver = अणु
		.name = F55_NAME,
	पूर्ण,
	.func = 0x55,
	.probe = rmi_f55_probe,
पूर्ण;
