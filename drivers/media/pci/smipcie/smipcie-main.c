<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMI PCIe driver क्रम DVBSky cards.
 *
 * Copyright (C) 2014 Max nibble <nibble.max@gmail.com>
 */

#समावेश "smipcie.h"
#समावेश "m88ds3103.h"
#समावेश "ts2020.h"
#समावेश "m88rs6000t.h"
#समावेश "si2168.h"
#समावेश "si2157.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक smi_hw_init(काष्ठा smi_dev *dev)
अणु
	u32 port_mux, port_ctrl, पूर्णांक_stat;

	/* set port mux.*/
	port_mux = smi_पढ़ो(MUX_MODE_CTRL);
	port_mux &= ~(rbPaMSMask);
	port_mux |= rbPaMSDtvNoGpio;
	port_mux &= ~(rbPbMSMask);
	port_mux |= rbPbMSDtvNoGpio;
	port_mux &= ~(0x0f0000);
	port_mux |= 0x50000;
	smi_ग_लिखो(MUX_MODE_CTRL, port_mux);

	/* set DTV रेजिस्टर.*/
	/* Port A */
	port_ctrl = smi_पढ़ो(VIDEO_CTRL_STATUS_A);
	port_ctrl &= ~0x01;
	smi_ग_लिखो(VIDEO_CTRL_STATUS_A, port_ctrl);
	port_ctrl = smi_पढ़ो(MPEG2_CTRL_A);
	port_ctrl &= ~0x40;
	port_ctrl |= 0x80;
	smi_ग_लिखो(MPEG2_CTRL_A, port_ctrl);
	/* Port B */
	port_ctrl = smi_पढ़ो(VIDEO_CTRL_STATUS_B);
	port_ctrl &= ~0x01;
	smi_ग_लिखो(VIDEO_CTRL_STATUS_B, port_ctrl);
	port_ctrl = smi_पढ़ो(MPEG2_CTRL_B);
	port_ctrl &= ~0x40;
	port_ctrl |= 0x80;
	smi_ग_लिखो(MPEG2_CTRL_B, port_ctrl);

	/* disable and clear पूर्णांकerrupt.*/
	smi_ग_लिखो(MSI_INT_ENA_CLR, ALL_INT);
	पूर्णांक_stat = smi_पढ़ो(MSI_INT_STATUS);
	smi_ग_लिखो(MSI_INT_STATUS_CLR, पूर्णांक_stat);

	/* reset demod.*/
	smi_clear(PERIPHERAL_CTRL, 0x0303);
	msleep(50);
	smi_set(PERIPHERAL_CTRL, 0x0101);
	वापस 0;
पूर्ण

/* i2c bit bus.*/
अटल व्योम smi_i2c_cfg(काष्ठा smi_dev *dev, u32 sw_ctl)
अणु
	u32 dwCtrl;

	dwCtrl = smi_पढ़ो(sw_ctl);
	dwCtrl &= ~0x18; /* disable output.*/
	dwCtrl |= 0x21; /* reset and software mode.*/
	dwCtrl &= ~0xff00;
	dwCtrl |= 0x6400;
	smi_ग_लिखो(sw_ctl, dwCtrl);
	msleep(20);
	dwCtrl = smi_पढ़ो(sw_ctl);
	dwCtrl &= ~0x20;
	smi_ग_लिखो(sw_ctl, dwCtrl);
पूर्ण

अटल व्योम smi_i2c_setsda(काष्ठा smi_dev *dev, पूर्णांक state, u32 sw_ctl)
अणु
	अगर (state) अणु
		/* set as input.*/
		smi_clear(sw_ctl, SW_I2C_MSK_DAT_EN);
	पूर्ण अन्यथा अणु
		smi_clear(sw_ctl, SW_I2C_MSK_DAT_OUT);
		/* set as output.*/
		smi_set(sw_ctl, SW_I2C_MSK_DAT_EN);
	पूर्ण
पूर्ण

अटल व्योम smi_i2c_setscl(व्योम *data, पूर्णांक state, u32 sw_ctl)
अणु
	काष्ठा smi_dev *dev = data;

	अगर (state) अणु
		/* set as input.*/
		smi_clear(sw_ctl, SW_I2C_MSK_CLK_EN);
	पूर्ण अन्यथा अणु
		smi_clear(sw_ctl, SW_I2C_MSK_CLK_OUT);
		/* set as output.*/
		smi_set(sw_ctl, SW_I2C_MSK_CLK_EN);
	पूर्ण
पूर्ण

अटल पूर्णांक smi_i2c_माला_लोda(व्योम *data, u32 sw_ctl)
अणु
	काष्ठा smi_dev *dev = data;
	/* set as input.*/
	smi_clear(sw_ctl, SW_I2C_MSK_DAT_EN);
	udelay(1);
	वापस (smi_पढ़ो(sw_ctl) & SW_I2C_MSK_DAT_IN) ? 1 : 0;
पूर्ण

अटल पूर्णांक smi_i2c_माला_लोcl(व्योम *data, u32 sw_ctl)
अणु
	काष्ठा smi_dev *dev = data;
	/* set as input.*/
	smi_clear(sw_ctl, SW_I2C_MSK_CLK_EN);
	udelay(1);
	वापस (smi_पढ़ो(sw_ctl) & SW_I2C_MSK_CLK_IN) ? 1 : 0;
पूर्ण
/* i2c 0.*/
अटल व्योम smi_i2c0_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा smi_dev *dev = data;

	smi_i2c_setsda(dev, state, I2C_A_SW_CTL);
पूर्ण

अटल व्योम smi_i2c0_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा smi_dev *dev = data;

	smi_i2c_setscl(dev, state, I2C_A_SW_CTL);
पूर्ण

अटल पूर्णांक smi_i2c0_माला_लोda(व्योम *data)
अणु
	काष्ठा smi_dev *dev = data;

	वापस	smi_i2c_माला_लोda(dev, I2C_A_SW_CTL);
पूर्ण

अटल पूर्णांक smi_i2c0_माला_लोcl(व्योम *data)
अणु
	काष्ठा smi_dev *dev = data;

	वापस	smi_i2c_माला_लोcl(dev, I2C_A_SW_CTL);
पूर्ण
/* i2c 1.*/
अटल व्योम smi_i2c1_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा smi_dev *dev = data;

	smi_i2c_setsda(dev, state, I2C_B_SW_CTL);
पूर्ण

अटल व्योम smi_i2c1_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा smi_dev *dev = data;

	smi_i2c_setscl(dev, state, I2C_B_SW_CTL);
पूर्ण

अटल पूर्णांक smi_i2c1_माला_लोda(व्योम *data)
अणु
	काष्ठा smi_dev *dev = data;

	वापस	smi_i2c_माला_लोda(dev, I2C_B_SW_CTL);
पूर्ण

अटल पूर्णांक smi_i2c1_माला_लोcl(व्योम *data)
अणु
	काष्ठा smi_dev *dev = data;

	वापस	smi_i2c_माला_लोcl(dev, I2C_B_SW_CTL);
पूर्ण

अटल पूर्णांक smi_i2c_init(काष्ठा smi_dev *dev)
अणु
	पूर्णांक ret;

	/* i2c bus 0 */
	smi_i2c_cfg(dev, I2C_A_SW_CTL);
	i2c_set_adapdata(&dev->i2c_bus[0], dev);
	strscpy(dev->i2c_bus[0].name, "SMI-I2C0", माप(dev->i2c_bus[0].name));
	dev->i2c_bus[0].owner = THIS_MODULE;
	dev->i2c_bus[0].dev.parent = &dev->pci_dev->dev;
	dev->i2c_bus[0].algo_data = &dev->i2c_bit[0];
	dev->i2c_bit[0].data = dev;
	dev->i2c_bit[0].setsda = smi_i2c0_setsda;
	dev->i2c_bit[0].setscl = smi_i2c0_setscl;
	dev->i2c_bit[0].माला_लोda = smi_i2c0_माला_लोda;
	dev->i2c_bit[0].माला_लोcl = smi_i2c0_माला_लोcl;
	dev->i2c_bit[0].udelay = 12;
	dev->i2c_bit[0].समयout = 10;
	/* Raise SCL and SDA */
	smi_i2c0_setsda(dev, 1);
	smi_i2c0_setscl(dev, 1);

	ret = i2c_bit_add_bus(&dev->i2c_bus[0]);
	अगर (ret < 0)
		वापस ret;

	/* i2c bus 1 */
	smi_i2c_cfg(dev, I2C_B_SW_CTL);
	i2c_set_adapdata(&dev->i2c_bus[1], dev);
	strscpy(dev->i2c_bus[1].name, "SMI-I2C1", माप(dev->i2c_bus[1].name));
	dev->i2c_bus[1].owner = THIS_MODULE;
	dev->i2c_bus[1].dev.parent = &dev->pci_dev->dev;
	dev->i2c_bus[1].algo_data = &dev->i2c_bit[1];
	dev->i2c_bit[1].data = dev;
	dev->i2c_bit[1].setsda = smi_i2c1_setsda;
	dev->i2c_bit[1].setscl = smi_i2c1_setscl;
	dev->i2c_bit[1].माला_लोda = smi_i2c1_माला_लोda;
	dev->i2c_bit[1].माला_लोcl = smi_i2c1_माला_लोcl;
	dev->i2c_bit[1].udelay = 12;
	dev->i2c_bit[1].समयout = 10;
	/* Raise SCL and SDA */
	smi_i2c1_setsda(dev, 1);
	smi_i2c1_setscl(dev, 1);

	ret = i2c_bit_add_bus(&dev->i2c_bus[1]);
	अगर (ret < 0)
		i2c_del_adapter(&dev->i2c_bus[0]);

	वापस ret;
पूर्ण

अटल व्योम smi_i2c_निकास(काष्ठा smi_dev *dev)
अणु
	i2c_del_adapter(&dev->i2c_bus[0]);
	i2c_del_adapter(&dev->i2c_bus[1]);
पूर्ण

अटल पूर्णांक smi_पढ़ो_eeprom(काष्ठा i2c_adapter *i2c, u16 reg, u8 *data, u16 size)
अणु
	पूर्णांक ret;
	u8 b0[2] = अणु (reg >> 8) & 0xff, reg & 0xff पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = 0x50, .flags = 0,
			.buf = b0, .len = 2 पूर्ण,
		अणु .addr = 0x50, .flags = I2C_M_RD,
			.buf = data, .len = size पूर्ण
	पूर्ण;

	ret = i2c_transfer(i2c, msg, 2);

	अगर (ret != 2) अणु
		dev_err(&i2c->dev, "%s: reg=0x%x (error=%d)\n",
			__func__, reg, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

/* ts port पूर्णांकerrupt operations */
अटल व्योम smi_port_disableInterrupt(काष्ठा smi_port *port)
अणु
	काष्ठा smi_dev *dev = port->dev;

	smi_ग_लिखो(MSI_INT_ENA_CLR,
		(port->_dmaInterruptCH0 | port->_dmaInterruptCH1));
पूर्ण

अटल व्योम smi_port_enableInterrupt(काष्ठा smi_port *port)
अणु
	काष्ठा smi_dev *dev = port->dev;

	smi_ग_लिखो(MSI_INT_ENA_SET,
		(port->_dmaInterruptCH0 | port->_dmaInterruptCH1));
पूर्ण

अटल व्योम smi_port_clearInterrupt(काष्ठा smi_port *port)
अणु
	काष्ठा smi_dev *dev = port->dev;

	smi_ग_लिखो(MSI_INT_STATUS_CLR,
		(port->_dmaInterruptCH0 | port->_dmaInterruptCH1));
पूर्ण

/* tasklet handler: DMA data to dmx.*/
अटल व्योम smi_dma_xfer(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा smi_port *port = from_tasklet(port, t, tasklet);
	काष्ठा smi_dev *dev = port->dev;
	u32 पूर्णांकr_status, finishedData, dmaManagement;
	u8 dmaChan0State, dmaChan1State;

	पूर्णांकr_status = port->_पूर्णांक_status;
	dmaManagement = smi_पढ़ो(port->DMA_MANAGEMENT);
	dmaChan0State = (u8)((dmaManagement & 0x00000030) >> 4);
	dmaChan1State = (u8)((dmaManagement & 0x00300000) >> 20);

	/* CH-0 DMA पूर्णांकerrupt.*/
	अगर ((पूर्णांकr_status & port->_dmaInterruptCH0) && (dmaChan0State == 0x01)) अणु
		dev_dbg(&dev->pci_dev->dev,
			"Port[%d]-DMA CH0 engine complete successful !\n",
			port->idx);
		finishedData = smi_पढ़ो(port->DMA_CHAN0_TRANS_STATE);
		finishedData &= 0x003FFFFF;
		/* value of DMA_PORT0_CHAN0_TRANS_STATE रेजिस्टर [21:0]
		 * indicate dma total transfer length and
		 * zero of [21:0] indicate dma total transfer length
		 * equal to 0x400000 (4MB)*/
		अगर (finishedData == 0)
			finishedData = 0x00400000;
		अगर (finishedData != SMI_TS_DMA_BUF_SIZE) अणु
			dev_dbg(&dev->pci_dev->dev,
				"DMA CH0 engine complete length mismatched, finish data=%d !\n",
				finishedData);
		पूर्ण
		dvb_dmx_swfilter_packets(&port->demux,
			port->cpu_addr[0], (finishedData / 188));
		/*dvb_dmx_swfilter(&port->demux,
			port->cpu_addr[0], finishedData);*/
	पूर्ण
	/* CH-1 DMA पूर्णांकerrupt.*/
	अगर ((पूर्णांकr_status & port->_dmaInterruptCH1) && (dmaChan1State == 0x01)) अणु
		dev_dbg(&dev->pci_dev->dev,
			"Port[%d]-DMA CH1 engine complete successful !\n",
			port->idx);
		finishedData = smi_पढ़ो(port->DMA_CHAN1_TRANS_STATE);
		finishedData &= 0x003FFFFF;
		/* value of DMA_PORT0_CHAN0_TRANS_STATE रेजिस्टर [21:0]
		 * indicate dma total transfer length and
		 * zero of [21:0] indicate dma total transfer length
		 * equal to 0x400000 (4MB)*/
		अगर (finishedData == 0)
			finishedData = 0x00400000;
		अगर (finishedData != SMI_TS_DMA_BUF_SIZE) अणु
			dev_dbg(&dev->pci_dev->dev,
				"DMA CH1 engine complete length mismatched, finish data=%d !\n",
				finishedData);
		पूर्ण
		dvb_dmx_swfilter_packets(&port->demux,
			port->cpu_addr[1], (finishedData / 188));
		/*dvb_dmx_swfilter(&port->demux,
			port->cpu_addr[1], finishedData);*/
	पूर्ण
	/* restart DMA.*/
	अगर (पूर्णांकr_status & port->_dmaInterruptCH0)
		dmaManagement |= 0x00000002;
	अगर (पूर्णांकr_status & port->_dmaInterruptCH1)
		dmaManagement |= 0x00020000;
	smi_ग_लिखो(port->DMA_MANAGEMENT, dmaManagement);
	/* Re-enable पूर्णांकerrupts */
	smi_port_enableInterrupt(port);
पूर्ण

अटल व्योम smi_port_dma_मुक्त(काष्ठा smi_port *port)
अणु
	अगर (port->cpu_addr[0]) अणु
		dma_मुक्त_coherent(&port->dev->pci_dev->dev,
				  SMI_TS_DMA_BUF_SIZE, port->cpu_addr[0],
				  port->dma_addr[0]);
		port->cpu_addr[0] = शून्य;
	पूर्ण
	अगर (port->cpu_addr[1]) अणु
		dma_मुक्त_coherent(&port->dev->pci_dev->dev,
				  SMI_TS_DMA_BUF_SIZE, port->cpu_addr[1],
				  port->dma_addr[1]);
		port->cpu_addr[1] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक smi_port_init(काष्ठा smi_port *port, पूर्णांक dmaChanUsed)
अणु
	dev_dbg(&port->dev->pci_dev->dev,
		"%s, port %d, dmaused %d\n", __func__, port->idx, dmaChanUsed);
	port->enable = 0;
	अगर (port->idx == 0) अणु
		/* Port A */
		port->_dmaInterruptCH0 = dmaChanUsed & 0x01;
		port->_dmaInterruptCH1 = dmaChanUsed & 0x02;

		port->DMA_CHAN0_ADDR_LOW	= DMA_PORTA_CHAN0_ADDR_LOW;
		port->DMA_CHAN0_ADDR_HI		= DMA_PORTA_CHAN0_ADDR_HI;
		port->DMA_CHAN0_TRANS_STATE	= DMA_PORTA_CHAN0_TRANS_STATE;
		port->DMA_CHAN0_CONTROL		= DMA_PORTA_CHAN0_CONTROL;
		port->DMA_CHAN1_ADDR_LOW	= DMA_PORTA_CHAN1_ADDR_LOW;
		port->DMA_CHAN1_ADDR_HI		= DMA_PORTA_CHAN1_ADDR_HI;
		port->DMA_CHAN1_TRANS_STATE	= DMA_PORTA_CHAN1_TRANS_STATE;
		port->DMA_CHAN1_CONTROL		= DMA_PORTA_CHAN1_CONTROL;
		port->DMA_MANAGEMENT		= DMA_PORTA_MANAGEMENT;
	पूर्ण अन्यथा अणु
		/* Port B */
		port->_dmaInterruptCH0 = (dmaChanUsed << 2) & 0x04;
		port->_dmaInterruptCH1 = (dmaChanUsed << 2) & 0x08;

		port->DMA_CHAN0_ADDR_LOW	= DMA_PORTB_CHAN0_ADDR_LOW;
		port->DMA_CHAN0_ADDR_HI		= DMA_PORTB_CHAN0_ADDR_HI;
		port->DMA_CHAN0_TRANS_STATE	= DMA_PORTB_CHAN0_TRANS_STATE;
		port->DMA_CHAN0_CONTROL		= DMA_PORTB_CHAN0_CONTROL;
		port->DMA_CHAN1_ADDR_LOW	= DMA_PORTB_CHAN1_ADDR_LOW;
		port->DMA_CHAN1_ADDR_HI		= DMA_PORTB_CHAN1_ADDR_HI;
		port->DMA_CHAN1_TRANS_STATE	= DMA_PORTB_CHAN1_TRANS_STATE;
		port->DMA_CHAN1_CONTROL		= DMA_PORTB_CHAN1_CONTROL;
		port->DMA_MANAGEMENT		= DMA_PORTB_MANAGEMENT;
	पूर्ण

	अगर (port->_dmaInterruptCH0) अणु
		port->cpu_addr[0] = dma_alloc_coherent(&port->dev->pci_dev->dev,
						       SMI_TS_DMA_BUF_SIZE,
						       &port->dma_addr[0],
						       GFP_KERNEL);
		अगर (!port->cpu_addr[0]) अणु
			dev_err(&port->dev->pci_dev->dev,
				"Port[%d] DMA CH0 memory allocation failed!\n",
				port->idx);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (port->_dmaInterruptCH1) अणु
		port->cpu_addr[1] = dma_alloc_coherent(&port->dev->pci_dev->dev,
						       SMI_TS_DMA_BUF_SIZE,
						       &port->dma_addr[1],
						       GFP_KERNEL);
		अगर (!port->cpu_addr[1]) अणु
			dev_err(&port->dev->pci_dev->dev,
				"Port[%d] DMA CH1 memory allocation failed!\n",
				port->idx);
			जाओ err;
		पूर्ण
	पूर्ण

	smi_port_disableInterrupt(port);
	tasklet_setup(&port->tasklet, smi_dma_xfer);
	tasklet_disable(&port->tasklet);
	port->enable = 1;
	वापस 0;
err:
	smi_port_dma_मुक्त(port);
	वापस -ENOMEM;
पूर्ण

अटल व्योम smi_port_निकास(काष्ठा smi_port *port)
अणु
	smi_port_disableInterrupt(port);
	tasklet_समाप्त(&port->tasklet);
	smi_port_dma_मुक्त(port);
	port->enable = 0;
पूर्ण

अटल पूर्णांक smi_port_irq(काष्ठा smi_port *port, u32 पूर्णांक_status)
अणु
	u32 port_req_irq = port->_dmaInterruptCH0 | port->_dmaInterruptCH1;
	पूर्णांक handled = 0;

	अगर (पूर्णांक_status & port_req_irq) अणु
		smi_port_disableInterrupt(port);
		port->_पूर्णांक_status = पूर्णांक_status;
		smi_port_clearInterrupt(port);
		tasklet_schedule(&port->tasklet);
		handled = 1;
	पूर्ण
	वापस handled;
पूर्ण

अटल irqवापस_t smi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा smi_dev *dev = dev_id;
	काष्ठा smi_port *port0 = &dev->ts_port[0];
	काष्ठा smi_port *port1 = &dev->ts_port[1];
	काष्ठा smi_rc *ir = &dev->ir;
	पूर्णांक handled = 0;

	u32 पूर्णांकr_status = smi_पढ़ो(MSI_INT_STATUS);

	/* ts0 पूर्णांकerrupt.*/
	अगर (dev->info->ts_0)
		handled += smi_port_irq(port0, पूर्णांकr_status);

	/* ts1 पूर्णांकerrupt.*/
	अगर (dev->info->ts_1)
		handled += smi_port_irq(port1, पूर्णांकr_status);

	/* ir पूर्णांकerrupt.*/
	handled += smi_ir_irq(ir, पूर्णांकr_status);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल काष्ठा i2c_client *smi_add_i2c_client(काष्ठा i2c_adapter *adapter,
			काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_client *client;

	request_module(info->type);
	client = i2c_new_client_device(adapter, info);
	अगर (!i2c_client_has_driver(client))
		जाओ err_add_i2c_client;

	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		जाओ err_add_i2c_client;
	पूर्ण
	वापस client;

err_add_i2c_client:
	client = शून्य;
	वापस client;
पूर्ण

अटल व्योम smi_del_i2c_client(काष्ठा i2c_client *client)
अणु
	module_put(client->dev.driver->owner);
	i2c_unरेजिस्टर_device(client);
पूर्ण

अटल स्थिर काष्ठा m88ds3103_config smi_dvbsky_m88ds3103_cfg = अणु
	.i2c_addr = 0x68,
	.घड़ी = 27000000,
	.i2c_wr_max = 33,
	.घड़ी_out = 0,
	.ts_mode = M88DS3103_TS_PARALLEL,
	.ts_clk = 16000,
	.ts_clk_pol = 1,
	.agc = 0x99,
	.lnb_hv_pol = 0,
	.lnb_en_pol = 1,
पूर्ण;

अटल पूर्णांक smi_dvbsky_m88ds3103_fe_attach(काष्ठा smi_port *port)
अणु
	पूर्णांक ret = 0;
	काष्ठा smi_dev *dev = port->dev;
	काष्ठा i2c_adapter *i2c;
	/* tuner I2C module */
	काष्ठा i2c_adapter *tuner_i2c_adapter;
	काष्ठा i2c_client *tuner_client;
	काष्ठा i2c_board_info tuner_info;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;
	स_रखो(&tuner_info, 0, माप(काष्ठा i2c_board_info));
	i2c = (port->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	port->fe = dvb_attach(m88ds3103_attach,
			&smi_dvbsky_m88ds3103_cfg, i2c, &tuner_i2c_adapter);
	अगर (!port->fe) अणु
		ret = -ENODEV;
		वापस ret;
	पूर्ण
	/* attach tuner */
	ts2020_config.fe = port->fe;
	strscpy(tuner_info.type, "ts2020", I2C_NAME_SIZE);
	tuner_info.addr = 0x60;
	tuner_info.platक्रमm_data = &ts2020_config;
	tuner_client = smi_add_i2c_client(tuner_i2c_adapter, &tuner_info);
	अगर (!tuner_client) अणु
		ret = -ENODEV;
		जाओ err_tuner_i2c_device;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	port->fe->ops.पढ़ो_संकेत_strength =
			port->fe->ops.tuner_ops.get_rf_strength;

	port->i2c_client_tuner = tuner_client;
	वापस ret;

err_tuner_i2c_device:
	dvb_frontend_detach(port->fe);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा m88ds3103_config smi_dvbsky_m88rs6000_cfg = अणु
	.i2c_addr = 0x69,
	.घड़ी = 27000000,
	.i2c_wr_max = 33,
	.ts_mode = M88DS3103_TS_PARALLEL,
	.ts_clk = 16000,
	.ts_clk_pol = 1,
	.agc = 0x99,
	.lnb_hv_pol = 0,
	.lnb_en_pol = 1,
पूर्ण;

अटल पूर्णांक smi_dvbsky_m88rs6000_fe_attach(काष्ठा smi_port *port)
अणु
	पूर्णांक ret = 0;
	काष्ठा smi_dev *dev = port->dev;
	काष्ठा i2c_adapter *i2c;
	/* tuner I2C module */
	काष्ठा i2c_adapter *tuner_i2c_adapter;
	काष्ठा i2c_client *tuner_client;
	काष्ठा i2c_board_info tuner_info;
	काष्ठा m88rs6000t_config m88rs6000t_config;

	स_रखो(&tuner_info, 0, माप(काष्ठा i2c_board_info));
	i2c = (port->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	port->fe = dvb_attach(m88ds3103_attach,
			&smi_dvbsky_m88rs6000_cfg, i2c, &tuner_i2c_adapter);
	अगर (!port->fe) अणु
		ret = -ENODEV;
		वापस ret;
	पूर्ण
	/* attach tuner */
	m88rs6000t_config.fe = port->fe;
	strscpy(tuner_info.type, "m88rs6000t", I2C_NAME_SIZE);
	tuner_info.addr = 0x21;
	tuner_info.platक्रमm_data = &m88rs6000t_config;
	tuner_client = smi_add_i2c_client(tuner_i2c_adapter, &tuner_info);
	अगर (!tuner_client) अणु
		ret = -ENODEV;
		जाओ err_tuner_i2c_device;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	port->fe->ops.पढ़ो_संकेत_strength =
			port->fe->ops.tuner_ops.get_rf_strength;

	port->i2c_client_tuner = tuner_client;
	वापस ret;

err_tuner_i2c_device:
	dvb_frontend_detach(port->fe);
	वापस ret;
पूर्ण

अटल पूर्णांक smi_dvbsky_sit2_fe_attach(काष्ठा smi_port *port)
अणु
	पूर्णांक ret = 0;
	काष्ठा smi_dev *dev = port->dev;
	काष्ठा i2c_adapter *i2c;
	काष्ठा i2c_adapter *tuner_i2c_adapter;
	काष्ठा i2c_client *client_tuner, *client_demod;
	काष्ठा i2c_board_info client_info;
	काष्ठा si2168_config si2168_config;
	काष्ठा si2157_config si2157_config;

	/* select i2c bus */
	i2c = (port->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	स_रखो(&si2168_config, 0, माप(si2168_config));
	si2168_config.i2c_adapter = &tuner_i2c_adapter;
	si2168_config.fe = &port->fe;
	si2168_config.ts_mode = SI2168_TS_PARALLEL;

	स_रखो(&client_info, 0, माप(काष्ठा i2c_board_info));
	strscpy(client_info.type, "si2168", I2C_NAME_SIZE);
	client_info.addr = 0x64;
	client_info.platक्रमm_data = &si2168_config;

	client_demod = smi_add_i2c_client(i2c, &client_info);
	अगर (!client_demod) अणु
		ret = -ENODEV;
		वापस ret;
	पूर्ण
	port->i2c_client_demod = client_demod;

	/* attach tuner */
	स_रखो(&si2157_config, 0, माप(si2157_config));
	si2157_config.fe = port->fe;
	si2157_config.अगर_port = 1;

	स_रखो(&client_info, 0, माप(काष्ठा i2c_board_info));
	strscpy(client_info.type, "si2157", I2C_NAME_SIZE);
	client_info.addr = 0x60;
	client_info.platक्रमm_data = &si2157_config;

	client_tuner = smi_add_i2c_client(tuner_i2c_adapter, &client_info);
	अगर (!client_tuner) अणु
		smi_del_i2c_client(port->i2c_client_demod);
		port->i2c_client_demod = शून्य;
		ret = -ENODEV;
		वापस ret;
	पूर्ण
	port->i2c_client_tuner = client_tuner;
	वापस ret;
पूर्ण

अटल पूर्णांक smi_fe_init(काष्ठा smi_port *port)
अणु
	पूर्णांक ret = 0;
	काष्ठा smi_dev *dev = port->dev;
	काष्ठा dvb_adapter *adap = &port->dvb_adapter;
	u8 mac_ee[16];

	dev_dbg(&port->dev->pci_dev->dev,
		"%s: port %d, fe_type = %d\n",
		__func__, port->idx, port->fe_type);
	चयन (port->fe_type) अणु
	हाल DVBSKY_FE_M88DS3103:
		ret = smi_dvbsky_m88ds3103_fe_attach(port);
		अवरोध;
	हाल DVBSKY_FE_M88RS6000:
		ret = smi_dvbsky_m88rs6000_fe_attach(port);
		अवरोध;
	हाल DVBSKY_FE_SIT2:
		ret = smi_dvbsky_sit2_fe_attach(port);
		अवरोध;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	/* रेजिस्टर dvb frontend */
	ret = dvb_रेजिस्टर_frontend(adap, port->fe);
	अगर (ret < 0) अणु
		अगर (port->i2c_client_tuner)
			smi_del_i2c_client(port->i2c_client_tuner);
		अगर (port->i2c_client_demod)
			smi_del_i2c_client(port->i2c_client_demod);
		dvb_frontend_detach(port->fe);
		वापस ret;
	पूर्ण
	/* init MAC.*/
	ret = smi_पढ़ो_eeprom(&dev->i2c_bus[0], 0xc0, mac_ee, 16);
	dev_info(&port->dev->pci_dev->dev,
		"%s port %d MAC: %pM\n", dev->info->name,
		port->idx, mac_ee + (port->idx)*8);
	स_नकल(adap->proposed_mac, mac_ee + (port->idx)*8, 6);
	वापस ret;
पूर्ण

अटल व्योम smi_fe_निकास(काष्ठा smi_port *port)
अणु
	dvb_unरेजिस्टर_frontend(port->fe);
	/* हटाओ I2C demod and tuner */
	अगर (port->i2c_client_tuner)
		smi_del_i2c_client(port->i2c_client_tuner);
	अगर (port->i2c_client_demod)
		smi_del_i2c_client(port->i2c_client_demod);
	dvb_frontend_detach(port->fe);
पूर्ण

अटल पूर्णांक my_dvb_dmx_ts_card_init(काष्ठा dvb_demux *dvbdemux, अक्षर *id,
			    पूर्णांक (*start_feed)(काष्ठा dvb_demux_feed *),
			    पूर्णांक (*stop_feed)(काष्ठा dvb_demux_feed *),
			    व्योम *priv)
अणु
	dvbdemux->priv = priv;

	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = start_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->ग_लिखो_to_decoder = शून्य;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
				      DMX_SECTION_FILTERING |
				      DMX_MEMORY_BASED_FILTERING);
	वापस dvb_dmx_init(dvbdemux);
पूर्ण

अटल पूर्णांक my_dvb_dmxdev_ts_card_init(काष्ठा dmxdev *dmxdev,
			       काष्ठा dvb_demux *dvbdemux,
			       काष्ठा dmx_frontend *hw_frontend,
			       काष्ठा dmx_frontend *mem_frontend,
			       काष्ठा dvb_adapter *dvb_adapter)
अणु
	पूर्णांक ret;

	dmxdev->filternum = 256;
	dmxdev->demux = &dvbdemux->dmx;
	dmxdev->capabilities = 0;
	ret = dvb_dmxdev_init(dmxdev, dvb_adapter);
	अगर (ret < 0)
		वापस ret;

	hw_frontend->source = DMX_FRONTEND_0;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, hw_frontend);
	mem_frontend->source = DMX_MEMORY_FE;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, mem_frontend);
	वापस dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, hw_frontend);
पूर्ण

अटल u32 smi_config_DMA(काष्ठा smi_port *port)
अणु
	काष्ठा smi_dev *dev = port->dev;
	u32 totalLength = 0, dmaMemPtrLow, dmaMemPtrHi, dmaCtlReg;
	u8 chanLatencyTimer = 0, dmaChanEnable = 1, dmaTransStart = 1;
	u32 dmaManagement = 0, tlpTransUnit = DMA_TRANS_UNIT_188;
	u8 tlpTc = 0, tlpTd = 1, tlpEp = 0, tlpAttr = 0;
	u64 mem;

	dmaManagement = smi_पढ़ो(port->DMA_MANAGEMENT);
	/* Setup Channel-0 */
	अगर (port->_dmaInterruptCH0) अणु
		totalLength = SMI_TS_DMA_BUF_SIZE;
		mem = port->dma_addr[0];
		dmaMemPtrLow = mem & 0xffffffff;
		dmaMemPtrHi = mem >> 32;
		dmaCtlReg = (totalLength) | (tlpTransUnit << 22) | (tlpTc << 25)
			| (tlpTd << 28) | (tlpEp << 29) | (tlpAttr << 30);
		dmaManagement |= dmaChanEnable | (dmaTransStart << 1)
			| (chanLatencyTimer << 8);
		/* ग_लिखो DMA रेजिस्टर, start DMA engine */
		smi_ग_लिखो(port->DMA_CHAN0_ADDR_LOW, dmaMemPtrLow);
		smi_ग_लिखो(port->DMA_CHAN0_ADDR_HI, dmaMemPtrHi);
		smi_ग_लिखो(port->DMA_CHAN0_CONTROL, dmaCtlReg);
	पूर्ण
	/* Setup Channel-1 */
	अगर (port->_dmaInterruptCH1) अणु
		totalLength = SMI_TS_DMA_BUF_SIZE;
		mem = port->dma_addr[1];
		dmaMemPtrLow = mem & 0xffffffff;
		dmaMemPtrHi = mem >> 32;
		dmaCtlReg = (totalLength) | (tlpTransUnit << 22) | (tlpTc << 25)
			| (tlpTd << 28) | (tlpEp << 29) | (tlpAttr << 30);
		dmaManagement |= (dmaChanEnable << 16) | (dmaTransStart << 17)
			| (chanLatencyTimer << 24);
		/* ग_लिखो DMA रेजिस्टर, start DMA engine */
		smi_ग_लिखो(port->DMA_CHAN1_ADDR_LOW, dmaMemPtrLow);
		smi_ग_लिखो(port->DMA_CHAN1_ADDR_HI, dmaMemPtrHi);
		smi_ग_लिखो(port->DMA_CHAN1_CONTROL, dmaCtlReg);
	पूर्ण
	वापस dmaManagement;
पूर्ण

अटल पूर्णांक smi_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा smi_port *port = dvbdmx->priv;
	काष्ठा smi_dev *dev = port->dev;
	u32 dmaManagement;

	अगर (port->users++ == 0) अणु
		dmaManagement = smi_config_DMA(port);
		smi_port_clearInterrupt(port);
		smi_port_enableInterrupt(port);
		smi_ग_लिखो(port->DMA_MANAGEMENT, dmaManagement);
		tasklet_enable(&port->tasklet);
	पूर्ण
	वापस port->users;
पूर्ण

अटल पूर्णांक smi_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा smi_port *port = dvbdmx->priv;
	काष्ठा smi_dev *dev = port->dev;

	अगर (--port->users)
		वापस port->users;

	tasklet_disable(&port->tasklet);
	smi_port_disableInterrupt(port);
	smi_clear(port->DMA_MANAGEMENT, 0x30003);
	वापस 0;
पूर्ण

अटल पूर्णांक smi_dvb_init(काष्ठा smi_port *port)
अणु
	पूर्णांक ret;
	काष्ठा dvb_adapter *adap = &port->dvb_adapter;
	काष्ठा dvb_demux *dvbdemux = &port->demux;

	dev_dbg(&port->dev->pci_dev->dev,
		"%s, port %d\n", __func__, port->idx);

	ret = dvb_रेजिस्टर_adapter(adap, "SMI_DVB", THIS_MODULE,
				   &port->dev->pci_dev->dev,
				   adapter_nr);
	अगर (ret < 0) अणु
		dev_err(&port->dev->pci_dev->dev, "Fail to register DVB adapter.\n");
		वापस ret;
	पूर्ण
	ret = my_dvb_dmx_ts_card_init(dvbdemux, "SW demux",
				      smi_start_feed,
				      smi_stop_feed, port);
	अगर (ret < 0)
		जाओ err_del_dvb_रेजिस्टर_adapter;

	ret = my_dvb_dmxdev_ts_card_init(&port->dmxdev, &port->demux,
					 &port->hw_frontend,
					 &port->mem_frontend, adap);
	अगर (ret < 0)
		जाओ err_del_dvb_dmx;

	ret = dvb_net_init(adap, &port->dvbnet, port->dmxdev.demux);
	अगर (ret < 0)
		जाओ err_del_dvb_dmxdev;
	वापस 0;
err_del_dvb_dmxdev:
	dvbdemux->dmx.बंद(&dvbdemux->dmx);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &port->hw_frontend);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &port->mem_frontend);
	dvb_dmxdev_release(&port->dmxdev);
err_del_dvb_dmx:
	dvb_dmx_release(&port->demux);
err_del_dvb_रेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter(&port->dvb_adapter);
	वापस ret;
पूर्ण

अटल व्योम smi_dvb_निकास(काष्ठा smi_port *port)
अणु
	काष्ठा dvb_demux *dvbdemux = &port->demux;

	dvb_net_release(&port->dvbnet);

	dvbdemux->dmx.बंद(&dvbdemux->dmx);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &port->hw_frontend);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &port->mem_frontend);
	dvb_dmxdev_release(&port->dmxdev);
	dvb_dmx_release(&port->demux);

	dvb_unरेजिस्टर_adapter(&port->dvb_adapter);
पूर्ण

अटल पूर्णांक smi_port_attach(काष्ठा smi_dev *dev,
		काष्ठा smi_port *port, पूर्णांक index)
अणु
	पूर्णांक ret, dmachs;

	port->dev = dev;
	port->idx = index;
	port->fe_type = (index == 0) ? dev->info->fe_0 : dev->info->fe_1;
	dmachs = (index == 0) ? dev->info->ts_0 : dev->info->ts_1;
	/* port init.*/
	ret = smi_port_init(port, dmachs);
	अगर (ret < 0)
		वापस ret;
	/* dvb init.*/
	ret = smi_dvb_init(port);
	अगर (ret < 0)
		जाओ err_del_port_init;
	/* fe init.*/
	ret = smi_fe_init(port);
	अगर (ret < 0)
		जाओ err_del_dvb_init;
	वापस 0;
err_del_dvb_init:
	smi_dvb_निकास(port);
err_del_port_init:
	smi_port_निकास(port);
	वापस ret;
पूर्ण

अटल व्योम smi_port_detach(काष्ठा smi_port *port)
अणु
	smi_fe_निकास(port);
	smi_dvb_निकास(port);
	smi_port_निकास(port);
पूर्ण

अटल पूर्णांक smi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा smi_dev *dev;
	पूर्णांक ret = -ENOMEM;

	अगर (pci_enable_device(pdev) < 0)
		वापस -ENODEV;

	dev = kzalloc(माप(काष्ठा smi_dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err_pci_disable_device;
	पूर्ण

	dev->pci_dev = pdev;
	pci_set_drvdata(pdev, dev);
	dev->info = (काष्ठा smi_cfg_info *) id->driver_data;
	dev_info(&dev->pci_dev->dev,
		"card detected: %s\n", dev->info->name);

	dev->nr = dev->info->type;
	dev->lmmio = ioremap(pci_resource_start(dev->pci_dev, 0),
			    pci_resource_len(dev->pci_dev, 0));
	अगर (!dev->lmmio) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण

	/* should we set to 32bit DMA? */
	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		जाओ err_pci_iounmap;

	pci_set_master(pdev);

	ret = smi_hw_init(dev);
	अगर (ret < 0)
		जाओ err_pci_iounmap;

	ret = smi_i2c_init(dev);
	अगर (ret < 0)
		जाओ err_pci_iounmap;

	अगर (dev->info->ts_0) अणु
		ret = smi_port_attach(dev, &dev->ts_port[0], 0);
		अगर (ret < 0)
			जाओ err_del_i2c_adaptor;
	पूर्ण

	अगर (dev->info->ts_1) अणु
		ret = smi_port_attach(dev, &dev->ts_port[1], 1);
		अगर (ret < 0)
			जाओ err_del_port0_attach;
	पूर्ण

	ret = smi_ir_init(dev);
	अगर (ret < 0)
		जाओ err_del_port1_attach;

#अगर_घोषित CONFIG_PCI_MSI /* to करो msi पूर्णांकerrupt.???*/
	अगर (pci_msi_enabled())
		ret = pci_enable_msi(dev->pci_dev);
	अगर (ret)
		dev_info(&dev->pci_dev->dev, "MSI not available.\n");
#पूर्ण_अगर

	ret = request_irq(dev->pci_dev->irq, smi_irq_handler,
			   IRQF_SHARED, "SMI_PCIE", dev);
	अगर (ret < 0)
		जाओ err_del_ir;

	smi_ir_start(&dev->ir);
	वापस 0;

err_del_ir:
	smi_ir_निकास(dev);
err_del_port1_attach:
	अगर (dev->info->ts_1)
		smi_port_detach(&dev->ts_port[1]);
err_del_port0_attach:
	अगर (dev->info->ts_0)
		smi_port_detach(&dev->ts_port[0]);
err_del_i2c_adaptor:
	smi_i2c_निकास(dev);
err_pci_iounmap:
	iounmap(dev->lmmio);
err_kमुक्त:
	pci_set_drvdata(pdev, शून्य);
	kमुक्त(dev);
err_pci_disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम smi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा smi_dev *dev = pci_get_drvdata(pdev);

	smi_ग_लिखो(MSI_INT_ENA_CLR, ALL_INT);
	मुक्त_irq(dev->pci_dev->irq, dev);
#अगर_घोषित CONFIG_PCI_MSI
	pci_disable_msi(dev->pci_dev);
#पूर्ण_अगर
	अगर (dev->info->ts_1)
		smi_port_detach(&dev->ts_port[1]);
	अगर (dev->info->ts_0)
		smi_port_detach(&dev->ts_port[0]);

	smi_ir_निकास(dev);
	smi_i2c_निकास(dev);
	iounmap(dev->lmmio);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
	kमुक्त(dev);
पूर्ण

/* DVBSky cards */
अटल स्थिर काष्ठा smi_cfg_info dvbsky_s950_cfg = अणु
	.type = SMI_DVBSKY_S950,
	.name = "DVBSky S950 V3",
	.ts_0 = SMI_TS_शून्य,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_शून्य,
	.fe_1 = DVBSKY_FE_M88DS3103,
	.rc_map = RC_MAP_DVBSKY,
पूर्ण;

अटल स्थिर काष्ठा smi_cfg_info dvbsky_s952_cfg = अणु
	.type = SMI_DVBSKY_S952,
	.name = "DVBSky S952 V3",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_M88RS6000,
	.fe_1 = DVBSKY_FE_M88RS6000,
	.rc_map = RC_MAP_DVBSKY,
पूर्ण;

अटल स्थिर काष्ठा smi_cfg_info dvbsky_t9580_cfg = अणु
	.type = SMI_DVBSKY_T9580,
	.name = "DVBSky T9580 V3",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_SIT2,
	.fe_1 = DVBSKY_FE_M88DS3103,
	.rc_map = RC_MAP_DVBSKY,
पूर्ण;

अटल स्थिर काष्ठा smi_cfg_info technotrend_s2_4200_cfg = अणु
	.type = SMI_TECHNOTREND_S2_4200,
	.name = "TechnoTrend TT-budget S2-4200 Twin",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_M88RS6000,
	.fe_1 = DVBSKY_FE_M88RS6000,
	.rc_map = RC_MAP_TT_1500,
पूर्ण;

/* PCI IDs */
#घोषणा SMI_ID(_subvend, _subdev, _driverdata) अणु	\
	.venकरोr      = SMI_VID,    .device    = SMI_PID, \
	.subvenकरोr   = _subvend, .subdevice = _subdev, \
	.driver_data = (अचिन्हित दीर्घ)&_driverdata पूर्ण

अटल स्थिर काष्ठा pci_device_id smi_id_table[] = अणु
	SMI_ID(0x4254, 0x0550, dvbsky_s950_cfg),
	SMI_ID(0x4254, 0x0552, dvbsky_s952_cfg),
	SMI_ID(0x4254, 0x5580, dvbsky_t9580_cfg),
	SMI_ID(0x13c2, 0x3016, technotrend_s2_4200_cfg),
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, smi_id_table);

अटल काष्ठा pci_driver smipcie_driver = अणु
	.name = "SMI PCIe driver",
	.id_table = smi_id_table,
	.probe = smi_probe,
	.हटाओ = smi_हटाओ,
पूर्ण;

module_pci_driver(smipcie_driver);

MODULE_AUTHOR("Max nibble <nibble.max@gmail.com>");
MODULE_DESCRIPTION("SMI PCIe driver");
MODULE_LICENSE("GPL");
