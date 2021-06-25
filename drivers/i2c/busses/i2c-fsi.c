<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FSI-attached I2C master algorithm
 *
 * Copyright 2018 IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fsi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#घोषणा FSI_ENGID_I2C		0x7

#घोषणा I2C_DEFAULT_CLK_DIV	6

/* i2c रेजिस्टरs */
#घोषणा I2C_FSI_FIFO		0x00
#घोषणा I2C_FSI_CMD		0x04
#घोषणा I2C_FSI_MODE		0x08
#घोषणा I2C_FSI_WATER_MARK	0x0C
#घोषणा I2C_FSI_INT_MASK	0x10
#घोषणा I2C_FSI_INT_COND	0x14
#घोषणा I2C_FSI_OR_INT_MASK	0x14
#घोषणा I2C_FSI_INTS		0x18
#घोषणा I2C_FSI_AND_INT_MASK	0x18
#घोषणा I2C_FSI_STAT		0x1C
#घोषणा I2C_FSI_RESET_I2C	0x1C
#घोषणा I2C_FSI_ESTAT		0x20
#घोषणा I2C_FSI_RESET_ERR	0x20
#घोषणा I2C_FSI_RESID_LEN	0x24
#घोषणा I2C_FSI_SET_SCL		0x24
#घोषणा I2C_FSI_PORT_BUSY	0x28
#घोषणा I2C_FSI_RESET_SCL	0x2C
#घोषणा I2C_FSI_SET_SDA		0x30
#घोषणा I2C_FSI_RESET_SDA	0x34

/* cmd रेजिस्टर */
#घोषणा I2C_CMD_WITH_START	BIT(31)
#घोषणा I2C_CMD_WITH_ADDR	BIT(30)
#घोषणा I2C_CMD_RD_CONT		BIT(29)
#घोषणा I2C_CMD_WITH_STOP	BIT(28)
#घोषणा I2C_CMD_FORCELAUNCH	BIT(27)
#घोषणा I2C_CMD_ADDR		GENMASK(23, 17)
#घोषणा I2C_CMD_READ		BIT(16)
#घोषणा I2C_CMD_LEN		GENMASK(15, 0)

/* mode रेजिस्टर */
#घोषणा I2C_MODE_CLKDIV		GENMASK(31, 16)
#घोषणा I2C_MODE_PORT		GENMASK(15, 10)
#घोषणा I2C_MODE_ENHANCED	BIT(3)
#घोषणा I2C_MODE_DIAG		BIT(2)
#घोषणा I2C_MODE_PACE_ALLOW	BIT(1)
#घोषणा I2C_MODE_WRAP		BIT(0)

/* watermark रेजिस्टर */
#घोषणा I2C_WATERMARK_HI	GENMASK(15, 12)
#घोषणा I2C_WATERMARK_LO	GENMASK(7, 4)

#घोषणा I2C_FIFO_HI_LVL		4
#घोषणा I2C_FIFO_LO_LVL		4

/* पूर्णांकerrupt रेजिस्टर */
#घोषणा I2C_INT_INV_CMD		BIT(15)
#घोषणा I2C_INT_PARITY		BIT(14)
#घोषणा I2C_INT_BE_OVERRUN	BIT(13)
#घोषणा I2C_INT_BE_ACCESS	BIT(12)
#घोषणा I2C_INT_LOST_ARB	BIT(11)
#घोषणा I2C_INT_NACK		BIT(10)
#घोषणा I2C_INT_DAT_REQ		BIT(9)
#घोषणा I2C_INT_CMD_COMP	BIT(8)
#घोषणा I2C_INT_STOP_ERR	BIT(7)
#घोषणा I2C_INT_BUSY		BIT(6)
#घोषणा I2C_INT_IDLE		BIT(5)

/* status रेजिस्टर */
#घोषणा I2C_STAT_INV_CMD	BIT(31)
#घोषणा I2C_STAT_PARITY		BIT(30)
#घोषणा I2C_STAT_BE_OVERRUN	BIT(29)
#घोषणा I2C_STAT_BE_ACCESS	BIT(28)
#घोषणा I2C_STAT_LOST_ARB	BIT(27)
#घोषणा I2C_STAT_NACK		BIT(26)
#घोषणा I2C_STAT_DAT_REQ	BIT(25)
#घोषणा I2C_STAT_CMD_COMP	BIT(24)
#घोषणा I2C_STAT_STOP_ERR	BIT(23)
#घोषणा I2C_STAT_MAX_PORT	GENMASK(22, 16)
#घोषणा I2C_STAT_ANY_INT	BIT(15)
#घोषणा I2C_STAT_SCL_IN		BIT(11)
#घोषणा I2C_STAT_SDA_IN		BIT(10)
#घोषणा I2C_STAT_PORT_BUSY	BIT(9)
#घोषणा I2C_STAT_SELF_BUSY	BIT(8)
#घोषणा I2C_STAT_FIFO_COUNT	GENMASK(7, 0)

#घोषणा I2C_STAT_ERR		(I2C_STAT_INV_CMD |			\
				 I2C_STAT_PARITY |			\
				 I2C_STAT_BE_OVERRUN |			\
				 I2C_STAT_BE_ACCESS |			\
				 I2C_STAT_LOST_ARB |			\
				 I2C_STAT_NACK |			\
				 I2C_STAT_STOP_ERR)
#घोषणा I2C_STAT_ANY_RESP	(I2C_STAT_ERR |				\
				 I2C_STAT_DAT_REQ |			\
				 I2C_STAT_CMD_COMP)

/* extended status रेजिस्टर */
#घोषणा I2C_ESTAT_FIFO_SZ	GENMASK(31, 24)
#घोषणा I2C_ESTAT_SCL_IN_SY	BIT(15)
#घोषणा I2C_ESTAT_SDA_IN_SY	BIT(14)
#घोषणा I2C_ESTAT_S_SCL		BIT(13)
#घोषणा I2C_ESTAT_S_SDA		BIT(12)
#घोषणा I2C_ESTAT_M_SCL		BIT(11)
#घोषणा I2C_ESTAT_M_SDA		BIT(10)
#घोषणा I2C_ESTAT_HI_WATER	BIT(9)
#घोषणा I2C_ESTAT_LO_WATER	BIT(8)
#घोषणा I2C_ESTAT_PORT_BUSY	BIT(7)
#घोषणा I2C_ESTAT_SELF_BUSY	BIT(6)
#घोषणा I2C_ESTAT_VERSION	GENMASK(4, 0)

/* port busy रेजिस्टर */
#घोषणा I2C_PORT_BUSY_RESET	BIT(31)

/* रुको क्रम command complete or data request */
#घोषणा I2C_CMD_SLEEP_MAX_US	500
#घोषणा I2C_CMD_SLEEP_MIN_US	50

/* रुको after reset; choose समय from legacy driver */
#घोषणा I2C_RESET_SLEEP_MAX_US	2000
#घोषणा I2C_RESET_SLEEP_MIN_US	1000

/* choose समयout length from legacy driver; it's well tested */
#घोषणा I2C_ABORT_TIMEOUT	msecs_to_jअगरfies(100)

काष्ठा fsi_i2c_master अणु
	काष्ठा fsi_device	*fsi;
	u8			fअगरo_size;
	काष्ठा list_head	ports;
	काष्ठा mutex		lock;
पूर्ण;

काष्ठा fsi_i2c_port अणु
	काष्ठा list_head	list;
	काष्ठा i2c_adapter	adapter;
	काष्ठा fsi_i2c_master	*master;
	u16			port;
	u16			xfrd;
पूर्ण;

अटल पूर्णांक fsi_i2c_पढ़ो_reg(काष्ठा fsi_device *fsi, अचिन्हित पूर्णांक reg,
			    u32 *data)
अणु
	पूर्णांक rc;
	__be32 data_be;

	rc = fsi_device_पढ़ो(fsi, reg, &data_be, माप(data_be));
	अगर (rc)
		वापस rc;

	*data = be32_to_cpu(data_be);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_ग_लिखो_reg(काष्ठा fsi_device *fsi, अचिन्हित पूर्णांक reg,
			     u32 *data)
अणु
	__be32 data_be = cpu_to_be32p(data);

	वापस fsi_device_ग_लिखो(fsi, reg, &data_be, माप(data_be));
पूर्ण

अटल पूर्णांक fsi_i2c_dev_init(काष्ठा fsi_i2c_master *i2c)
अणु
	पूर्णांक rc;
	u32 mode = I2C_MODE_ENHANCED, extended_status, watermark;
	u32 पूर्णांकerrupt = 0;

	/* since we use polling, disable पूर्णांकerrupts */
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_INT_MASK, &पूर्णांकerrupt);
	अगर (rc)
		वापस rc;

	mode |= FIELD_PREP(I2C_MODE_CLKDIV, I2C_DEFAULT_CLK_DIV);
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस rc;

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_ESTAT, &extended_status);
	अगर (rc)
		वापस rc;

	i2c->fअगरo_size = FIELD_GET(I2C_ESTAT_FIFO_SZ, extended_status);
	watermark = FIELD_PREP(I2C_WATERMARK_HI,
			       i2c->fअगरo_size - I2C_FIFO_HI_LVL);
	watermark |= FIELD_PREP(I2C_WATERMARK_LO, I2C_FIFO_LO_LVL);

	वापस fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_WATER_MARK, &watermark);
पूर्ण

अटल पूर्णांक fsi_i2c_set_port(काष्ठा fsi_i2c_port *port)
अणु
	पूर्णांक rc;
	काष्ठा fsi_device *fsi = port->master->fsi;
	u32 mode, dummy = 0;

	rc = fsi_i2c_पढ़ो_reg(fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस rc;

	अगर (FIELD_GET(I2C_MODE_PORT, mode) == port->port)
		वापस 0;

	mode = (mode & ~I2C_MODE_PORT) | FIELD_PREP(I2C_MODE_PORT, port->port);
	rc = fsi_i2c_ग_लिखो_reg(fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस rc;

	/* reset engine when port is changed */
	वापस fsi_i2c_ग_लिखो_reg(fsi, I2C_FSI_RESET_ERR, &dummy);
पूर्ण

अटल पूर्णांक fsi_i2c_start(काष्ठा fsi_i2c_port *port, काष्ठा i2c_msg *msg,
			 bool stop)
अणु
	काष्ठा fsi_i2c_master *i2c = port->master;
	u32 cmd = I2C_CMD_WITH_START | I2C_CMD_WITH_ADDR;

	port->xfrd = 0;

	अगर (msg->flags & I2C_M_RD)
		cmd |= I2C_CMD_READ;

	अगर (stop || msg->flags & I2C_M_STOP)
		cmd |= I2C_CMD_WITH_STOP;

	cmd |= FIELD_PREP(I2C_CMD_ADDR, msg->addr);
	cmd |= FIELD_PREP(I2C_CMD_LEN, msg->len);

	वापस fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_CMD, &cmd);
पूर्ण

अटल पूर्णांक fsi_i2c_get_op_bytes(पूर्णांक op_bytes)
अणु
	/* fsi is limited to max 4 byte aligned ops */
	अगर (op_bytes > 4)
		वापस 4;
	अन्यथा अगर (op_bytes == 3)
		वापस 2;
	वापस op_bytes;
पूर्ण

अटल पूर्णांक fsi_i2c_ग_लिखो_fअगरo(काष्ठा fsi_i2c_port *port, काष्ठा i2c_msg *msg,
			      u8 fअगरo_count)
अणु
	पूर्णांक ग_लिखो;
	पूर्णांक rc;
	काष्ठा fsi_i2c_master *i2c = port->master;
	पूर्णांक bytes_to_ग_लिखो = i2c->fअगरo_size - fअगरo_count;
	पूर्णांक bytes_reमुख्यing = msg->len - port->xfrd;

	bytes_to_ग_लिखो = min(bytes_to_ग_लिखो, bytes_reमुख्यing);

	जबतक (bytes_to_ग_लिखो) अणु
		ग_लिखो = fsi_i2c_get_op_bytes(bytes_to_ग_लिखो);

		rc = fsi_device_ग_लिखो(i2c->fsi, I2C_FSI_FIFO,
				      &msg->buf[port->xfrd], ग_लिखो);
		अगर (rc)
			वापस rc;

		port->xfrd += ग_लिखो;
		bytes_to_ग_लिखो -= ग_लिखो;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_पढ़ो_fअगरo(काष्ठा fsi_i2c_port *port, काष्ठा i2c_msg *msg,
			     u8 fअगरo_count)
अणु
	पूर्णांक पढ़ो;
	पूर्णांक rc;
	काष्ठा fsi_i2c_master *i2c = port->master;
	पूर्णांक bytes_to_पढ़ो;
	पूर्णांक xfr_reमुख्यing = msg->len - port->xfrd;
	u32 dummy;

	bytes_to_पढ़ो = min_t(पूर्णांक, fअगरo_count, xfr_reमुख्यing);

	जबतक (bytes_to_पढ़ो) अणु
		पढ़ो = fsi_i2c_get_op_bytes(bytes_to_पढ़ो);

		अगर (xfr_reमुख्यing) अणु
			rc = fsi_device_पढ़ो(i2c->fsi, I2C_FSI_FIFO,
					     &msg->buf[port->xfrd], पढ़ो);
			अगर (rc)
				वापस rc;

			port->xfrd += पढ़ो;
			xfr_reमुख्यing -= पढ़ो;
		पूर्ण अन्यथा अणु
			/* no more buffer but data in fअगरo, need to clear it */
			rc = fsi_device_पढ़ो(i2c->fsi, I2C_FSI_FIFO, &dummy,
					     पढ़ो);
			अगर (rc)
				वापस rc;
		पूर्ण

		bytes_to_पढ़ो -= पढ़ो;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	u32 stat = 0;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_STAT, &stat);

	वापस !!(stat & I2C_STAT_SCL_IN);
पूर्ण

अटल व्योम fsi_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	u32 dummy = 0;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	अगर (val)
		fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_SET_SCL, &dummy);
	अन्यथा
		fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_RESET_SCL, &dummy);
पूर्ण

अटल पूर्णांक fsi_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	u32 stat = 0;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_STAT, &stat);

	वापस !!(stat & I2C_STAT_SDA_IN);
पूर्ण

अटल व्योम fsi_i2c_set_sda(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	u32 dummy = 0;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	अगर (val)
		fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_SET_SDA, &dummy);
	अन्यथा
		fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_RESET_SDA, &dummy);
पूर्ण

अटल व्योम fsi_i2c_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक rc;
	u32 mode;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस;

	mode |= I2C_MODE_DIAG;
	fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
पूर्ण

अटल व्योम fsi_i2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक rc;
	u32 mode;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *i2c = port->master;

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस;

	mode &= ~I2C_MODE_DIAG;
	fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
पूर्ण

अटल पूर्णांक fsi_i2c_reset_bus(काष्ठा fsi_i2c_master *i2c,
			     काष्ठा fsi_i2c_port *port)
अणु
	पूर्णांक rc;
	u32 stat, dummy = 0;

	/* क्रमce bus reset, ignore errors */
	i2c_recover_bus(&port->adapter);

	/* reset errors */
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_RESET_ERR, &dummy);
	अगर (rc)
		वापस rc;

	/* रुको क्रम command complete */
	usleep_range(I2C_RESET_SLEEP_MIN_US, I2C_RESET_SLEEP_MAX_US);

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_STAT, &stat);
	अगर (rc)
		वापस rc;

	अगर (stat & I2C_STAT_CMD_COMP)
		वापस 0;

	/* failed to get command complete; reset engine again */
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_RESET_I2C, &dummy);
	अगर (rc)
		वापस rc;

	/* re-init engine again */
	वापस fsi_i2c_dev_init(i2c);
पूर्ण

अटल पूर्णांक fsi_i2c_reset_engine(काष्ठा fsi_i2c_master *i2c, u16 port)
अणु
	पूर्णांक rc;
	u32 mode, dummy = 0;

	/* reset engine */
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_RESET_I2C, &dummy);
	अगर (rc)
		वापस rc;

	/* re-init engine */
	rc = fsi_i2c_dev_init(i2c);
	अगर (rc)
		वापस rc;

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
	अगर (rc)
		वापस rc;

	/* set port; शेष after reset is 0 */
	अगर (port) अणु
		mode &= ~I2C_MODE_PORT;
		mode |= FIELD_PREP(I2C_MODE_PORT, port);
		rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_MODE, &mode);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* reset busy रेजिस्टर; hw workaround */
	dummy = I2C_PORT_BUSY_RESET;
	rc = fsi_i2c_ग_लिखो_reg(i2c->fsi, I2C_FSI_PORT_BUSY, &dummy);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_पात(काष्ठा fsi_i2c_port *port, u32 status)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ start;
	u32 cmd = I2C_CMD_WITH_STOP;
	u32 stat;
	काष्ठा fsi_i2c_master *i2c = port->master;
	काष्ठा fsi_device *fsi = i2c->fsi;

	rc = fsi_i2c_reset_engine(i2c, port->port);
	अगर (rc)
		वापस rc;

	rc = fsi_i2c_पढ़ो_reg(fsi, I2C_FSI_STAT, &stat);
	अगर (rc)
		वापस rc;

	/* अगर sda is low, peक्रमm full bus reset */
	अगर (!(stat & I2C_STAT_SDA_IN)) अणु
		rc = fsi_i2c_reset_bus(i2c, port);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* skip final stop command क्रम these errors */
	अगर (status & (I2C_STAT_PARITY | I2C_STAT_LOST_ARB | I2C_STAT_STOP_ERR))
		वापस 0;

	/* ग_लिखो stop command */
	rc = fsi_i2c_ग_लिखो_reg(fsi, I2C_FSI_CMD, &cmd);
	अगर (rc)
		वापस rc;

	/* रुको until we see command complete in the master */
	start = jअगरfies;

	करो अणु
		rc = fsi_i2c_पढ़ो_reg(fsi, I2C_FSI_STAT, &status);
		अगर (rc)
			वापस rc;

		अगर (status & I2C_STAT_CMD_COMP)
			वापस 0;

		usleep_range(I2C_CMD_SLEEP_MIN_US, I2C_CMD_SLEEP_MAX_US);
	पूर्ण जबतक (समय_after(start + I2C_ABORT_TIMEOUT, jअगरfies));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक fsi_i2c_handle_status(काष्ठा fsi_i2c_port *port,
				 काष्ठा i2c_msg *msg, u32 status)
अणु
	पूर्णांक rc;
	u8 fअगरo_count;

	अगर (status & I2C_STAT_ERR) अणु
		rc = fsi_i2c_पात(port, status);
		अगर (rc)
			वापस rc;

		अगर (status & I2C_STAT_INV_CMD)
			वापस -EINVAL;

		अगर (status & (I2C_STAT_PARITY | I2C_STAT_BE_OVERRUN |
		    I2C_STAT_BE_ACCESS))
			वापस -EPROTO;

		अगर (status & I2C_STAT_NACK)
			वापस -ENXIO;

		अगर (status & I2C_STAT_LOST_ARB)
			वापस -EAGAIN;

		अगर (status & I2C_STAT_STOP_ERR)
			वापस -EBADMSG;

		वापस -EIO;
	पूर्ण

	अगर (status & I2C_STAT_DAT_REQ) अणु
		fअगरo_count = FIELD_GET(I2C_STAT_FIFO_COUNT, status);

		अगर (msg->flags & I2C_M_RD)
			वापस fsi_i2c_पढ़ो_fअगरo(port, msg, fअगरo_count);

		वापस fsi_i2c_ग_लिखो_fअगरo(port, msg, fअगरo_count);
	पूर्ण

	अगर (status & I2C_STAT_CMD_COMP) अणु
		अगर (port->xfrd < msg->len)
			वापस -ENODATA;

		वापस msg->len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_रुको(काष्ठा fsi_i2c_port *port, काष्ठा i2c_msg *msg,
			अचिन्हित दीर्घ समयout)
अणु
	u32 status = 0;
	पूर्णांक rc;
	अचिन्हित दीर्घ start = jअगरfies;

	करो अणु
		rc = fsi_i2c_पढ़ो_reg(port->master->fsi, I2C_FSI_STAT,
				      &status);
		अगर (rc)
			वापस rc;

		अगर (status & I2C_STAT_ANY_RESP) अणु
			rc = fsi_i2c_handle_status(port, msg, status);
			अगर (rc < 0)
				वापस rc;

			/* cmd complete and all data xfrd */
			अगर (rc == msg->len)
				वापस 0;

			/* need to xfr more data, but maybe करोn't need रुको */
			जारी;
		पूर्ण

		usleep_range(I2C_CMD_SLEEP_MIN_US, I2C_CMD_SLEEP_MAX_US);
	पूर्ण जबतक (समय_after(start + समयout, jअगरfies));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक fsi_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			पूर्णांक num)
अणु
	पूर्णांक i, rc;
	अचिन्हित दीर्घ start_समय;
	काष्ठा fsi_i2c_port *port = adap->algo_data;
	काष्ठा fsi_i2c_master *master = port->master;
	काष्ठा i2c_msg *msg;

	mutex_lock(&master->lock);

	rc = fsi_i2c_set_port(port);
	अगर (rc)
		जाओ unlock;

	क्रम (i = 0; i < num; i++) अणु
		msg = msgs + i;
		start_समय = jअगरfies;

		rc = fsi_i2c_start(port, msg, i == num - 1);
		अगर (rc)
			जाओ unlock;

		rc = fsi_i2c_रुको(port, msg,
				  adap->समयout - (jअगरfies - start_समय));
		अगर (rc)
			जाओ unlock;
	पूर्ण

unlock:
	mutex_unlock(&master->lock);
	वापस rc ? : num;
पूर्ण

अटल u32 fsi_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_PROTOCOL_MANGLING |
		I2C_FUNC_SMBUS_EMUL | I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल काष्ठा i2c_bus_recovery_info fsi_i2c_bus_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.get_scl = fsi_i2c_get_scl,
	.set_scl = fsi_i2c_set_scl,
	.get_sda = fsi_i2c_get_sda,
	.set_sda = fsi_i2c_set_sda,
	.prepare_recovery = fsi_i2c_prepare_recovery,
	.unprepare_recovery = fsi_i2c_unprepare_recovery,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm fsi_i2c_algorithm = अणु
	.master_xfer = fsi_i2c_xfer,
	.functionality = fsi_i2c_functionality,
पूर्ण;

अटल काष्ठा device_node *fsi_i2c_find_port_of_node(काष्ठा device_node *fsi,
						     पूर्णांक port)
अणु
	काष्ठा device_node *np;
	u32 port_no;
	पूर्णांक rc;

	क्रम_each_child_of_node(fsi, np) अणु
		rc = of_property_पढ़ो_u32(np, "reg", &port_no);
		अगर (!rc && port_no == port)
			वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक fsi_i2c_probe(काष्ठा device *dev)
अणु
	काष्ठा fsi_i2c_master *i2c;
	काष्ठा fsi_i2c_port *port;
	काष्ठा device_node *np;
	u32 port_no, ports, stat;
	पूर्णांक rc;

	i2c = devm_kzalloc(dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	mutex_init(&i2c->lock);
	i2c->fsi = to_fsi_dev(dev);
	INIT_LIST_HEAD(&i2c->ports);

	rc = fsi_i2c_dev_init(i2c);
	अगर (rc)
		वापस rc;

	rc = fsi_i2c_पढ़ो_reg(i2c->fsi, I2C_FSI_STAT, &stat);
	अगर (rc)
		वापस rc;

	ports = FIELD_GET(I2C_STAT_MAX_PORT, stat) + 1;
	dev_dbg(dev, "I2C master has %d ports\n", ports);

	क्रम (port_no = 0; port_no < ports; port_no++) अणु
		np = fsi_i2c_find_port_of_node(dev->of_node, port_no);
		अगर (!of_device_is_available(np))
			जारी;

		port = kzalloc(माप(*port), GFP_KERNEL);
		अगर (!port) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण

		port->master = i2c;
		port->port = port_no;

		port->adapter.owner = THIS_MODULE;
		port->adapter.dev.of_node = np;
		port->adapter.dev.parent = dev;
		port->adapter.algo = &fsi_i2c_algorithm;
		port->adapter.bus_recovery_info = &fsi_i2c_bus_recovery_info;
		port->adapter.algo_data = port;

		snम_लिखो(port->adapter.name, माप(port->adapter.name),
			 "i2c_bus-%u", port_no);

		rc = i2c_add_adapter(&port->adapter);
		अगर (rc < 0) अणु
			dev_err(dev, "Failed to register adapter: %d\n", rc);
			kमुक्त(port);
			जारी;
		पूर्ण

		list_add(&port->list, &i2c->ports);
	पूर्ण

	dev_set_drvdata(dev, i2c);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_i2c_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा fsi_i2c_master *i2c = dev_get_drvdata(dev);
	काष्ठा fsi_i2c_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &i2c->ports, list) अणु
		list_del(&port->list);
		i2c_del_adapter(&port->adapter);
		kमुक्त(port);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsi_device_id fsi_i2c_ids[] = अणु
	अणु FSI_ENGID_I2C, FSI_VERSION_ANY पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा fsi_driver fsi_i2c_driver = अणु
	.id_table = fsi_i2c_ids,
	.drv = अणु
		.name = "i2c-fsi",
		.bus = &fsi_bus_type,
		.probe = fsi_i2c_probe,
		.हटाओ = fsi_i2c_हटाओ,
	पूर्ण,
पूर्ण;

module_fsi_driver(fsi_i2c_driver);

MODULE_AUTHOR("Eddie James <eajames@us.ibm.com>");
MODULE_DESCRIPTION("FSI attached I2C master");
MODULE_LICENSE("GPL");
