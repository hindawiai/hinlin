<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cimax2.c
 *
 * CIMax2(R) SP2 driver in conjunction with NetUp Dual DVB-S2 CI card
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 * Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#समावेश "cx23885.h"
#समावेश "cimax2.h"
#समावेश <media/dvb_ca_en50221.h>

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

/**** Bit definitions क्रम MC417_RWD and MC417_OEN रेजिस्टरs  ***
  bits 31-16
+-----------+
| Reserved  |
+-----------+
  bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
+-------+-------+-------+-------+-------+-------+-------+-------+
|  WR#  |  RD#  |       |  ACK# |  ADHI |  ADLO |  CS1# |  CS0# |
+-------+-------+-------+-------+-------+-------+-------+-------+
 bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
+-------+-------+-------+-------+-------+-------+-------+-------+
|  DATA7|  DATA6|  DATA5|  DATA4|  DATA3|  DATA2|  DATA1|  DATA0|
+-------+-------+-------+-------+-------+-------+-------+-------+
***/
/* MC417 */
#घोषणा NETUP_DATA		0x000000ff
#घोषणा NETUP_WR		0x00008000
#घोषणा NETUP_RD		0x00004000
#घोषणा NETUP_ACK		0x00001000
#घोषणा NETUP_ADHI		0x00000800
#घोषणा NETUP_ADLO		0x00000400
#घोषणा NETUP_CS1		0x00000200
#घोषणा NETUP_CS0		0x00000100
#घोषणा NETUP_EN_ALL		0x00001000
#घोषणा NETUP_CTRL_OFF		(NETUP_CS1 | NETUP_CS0 | NETUP_WR | NETUP_RD)
#घोषणा NETUP_CI_CTL		0x04
#घोषणा NETUP_CI_RD		1

#घोषणा NETUP_IRQ_DETAM		0x1
#घोषणा NETUP_IRQ_IRQAM		0x4

अटल अचिन्हित पूर्णांक ci_dbg;
module_param(ci_dbg, पूर्णांक, 0644);
MODULE_PARM_DESC(ci_dbg, "Enable CI debugging");

अटल अचिन्हित पूर्णांक ci_irq_enable;
module_param(ci_irq_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(ci_irq_enable, "Enable IRQ from CAM");

#घोषणा ci_dbg_prपूर्णांक(fmt, args...) \
	करो अणु \
		अगर (ci_dbg) \
			prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), \
			       __func__, ##args); \
	पूर्ण जबतक (0)

#घोषणा ci_irq_flags() (ci_irq_enable ? NETUP_IRQ_IRQAM : 0)

/* stores all निजी variables क्रम communication with CI */
काष्ठा netup_ci_state अणु
	काष्ठा dvb_ca_en50221 ca;
	काष्ठा mutex ca_mutex;
	काष्ठा i2c_adapter *i2c_adap;
	u8 ci_i2c_addr;
	पूर्णांक status;
	काष्ठा work_काष्ठा work;
	व्योम *priv;
	u8 current_irq_mode;
	पूर्णांक current_ci_flag;
	अचिन्हित दीर्घ next_status_checked_समय;
पूर्ण;


अटल पूर्णांक netup_पढ़ो_i2c(काष्ठा i2c_adapter *i2c_adap, u8 addr, u8 reg,
						u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= addr,
			.flags	= 0,
			.buf	= &reg,
			.len	= 1
		पूर्ण, अणु
			.addr	= addr,
			.flags	= I2C_M_RD,
			.buf	= buf,
			.len	= len
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(i2c_adap, msg, 2);

	अगर (ret != 2) अणु
		ci_dbg_prपूर्णांक("%s: i2c read error, Reg = 0x%02x, Status = %d\n",
						__func__, reg, ret);

		वापस -1;
	पूर्ण

	ci_dbg_prपूर्णांक("%s: i2c read Addr=0x%04x, Reg = 0x%02x, data = %02x\n",
						__func__, addr, reg, buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक netup_ग_लिखो_i2c(काष्ठा i2c_adapter *i2c_adap, u8 addr, u8 reg,
						u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	u8 buffer[MAX_XFER_SIZE];

	काष्ठा i2c_msg msg = अणु
		.addr	= addr,
		.flags	= 0,
		.buf	= &buffer[0],
		.len	= len + 1
	पूर्ण;

	अगर (1 + len > माप(buffer)) अणु
		pr_warn("%s: i2c wr reg=%04x: len=%d is too big!\n",
		       KBUILD_MODNAME, reg, len);
		वापस -EINVAL;
	पूर्ण

	buffer[0] = reg;
	स_नकल(&buffer[1], buf, len);

	ret = i2c_transfer(i2c_adap, &msg, 1);

	अगर (ret != 1) अणु
		ci_dbg_prपूर्णांक("%s: i2c write error, Reg=[0x%02x], Status=%d\n",
						__func__, reg, ret);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक netup_ci_get_mem(काष्ठा cx23885_dev *dev)
अणु
	पूर्णांक mem;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);

	क्रम (;;) अणु
		mem = cx_पढ़ो(MC417_RWD);
		अगर ((mem & NETUP_ACK) == 0)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		udelay(1);
	पूर्ण

	cx_set(MC417_RWD, NETUP_CTRL_OFF);

	वापस mem & 0xff;
पूर्ण

अटल पूर्णांक netup_ci_op_cam(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot,
				u8 flag, u8 पढ़ो, पूर्णांक addr, u8 data)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा cx23885_tsport *port = state->priv;
	काष्ठा cx23885_dev *dev = port->dev;

	u8 store;
	पूर्णांक mem;
	पूर्णांक ret;

	अगर (0 != slot)
		वापस -EINVAL;

	अगर (state->current_ci_flag != flag) अणु
		ret = netup_पढ़ो_i2c(state->i2c_adap, state->ci_i2c_addr,
				0, &store, 1);
		अगर (ret != 0)
			वापस ret;

		store &= ~0x0c;
		store |= flag;

		ret = netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
				0, &store, 1);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	state->current_ci_flag = flag;

	mutex_lock(&dev->gpio_lock);

	/* ग_लिखो addr */
	cx_ग_लिखो(MC417_OEN, NETUP_EN_ALL);
	cx_ग_लिखो(MC417_RWD, NETUP_CTRL_OFF |
				NETUP_ADLO | (0xff & addr));
	cx_clear(MC417_RWD, NETUP_ADLO);
	cx_ग_लिखो(MC417_RWD, NETUP_CTRL_OFF |
				NETUP_ADHI | (0xff & (addr >> 8)));
	cx_clear(MC417_RWD, NETUP_ADHI);

	अगर (पढ़ो) अणु /* data in */
		cx_ग_लिखो(MC417_OEN, NETUP_EN_ALL | NETUP_DATA);
	पूर्ण अन्यथा /* data out */
		cx_ग_लिखो(MC417_RWD, NETUP_CTRL_OFF | data);

	/* choose chip */
	cx_clear(MC417_RWD,
			(state->ci_i2c_addr == 0x40) ? NETUP_CS0 : NETUP_CS1);
	/* पढ़ो/ग_लिखो */
	cx_clear(MC417_RWD, (पढ़ो) ? NETUP_RD : NETUP_WR);
	mem = netup_ci_get_mem(dev);

	mutex_unlock(&dev->gpio_lock);

	अगर (!पढ़ो)
		अगर (mem < 0)
			वापस -EREMOTEIO;

	ci_dbg_prपूर्णांक("%s: %s: chipaddr=[0x%x] addr=[0x%02x], %s=%x\n", __func__,
			(पढ़ो) ? "read" : "write", state->ci_i2c_addr, addr,
			(flag == NETUP_CI_CTL) ? "ctl" : "mem",
			(पढ़ो) ? mem : data);

	अगर (पढ़ो)
		वापस mem;

	वापस 0;
पूर्ण

पूर्णांक netup_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, पूर्णांक addr)
अणु
	वापस netup_ci_op_cam(en50221, slot, 0, NETUP_CI_RD, addr, 0);
पूर्ण

पूर्णांक netup_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, पूर्णांक addr, u8 data)
अणु
	वापस netup_ci_op_cam(en50221, slot, 0, 0, addr, data);
पूर्ण

पूर्णांक netup_ci_पढ़ो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot,
				 u8 addr)
अणु
	वापस netup_ci_op_cam(en50221, slot, NETUP_CI_CTL,
							NETUP_CI_RD, addr, 0);
पूर्ण

पूर्णांक netup_ci_ग_लिखो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot,
							u8 addr, u8 data)
अणु
	वापस netup_ci_op_cam(en50221, slot, NETUP_CI_CTL, 0, addr, data);
पूर्ण

पूर्णांक netup_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	u8 buf =  0x80;
	पूर्णांक ret;

	अगर (0 != slot)
		वापस -EINVAL;

	udelay(500);
	ret = netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
							0, &buf, 1);

	अगर (ret != 0)
		वापस ret;

	udelay(500);

	buf = 0x00;
	ret = netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
							0, &buf, 1);

	msleep(1000);
	dvb_ca_en50221_camपढ़ोy_irq(&state->ca, 0);

	वापस 0;

पूर्ण

पूर्णांक netup_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	/* not implemented */
	वापस 0;
पूर्ण

अटल पूर्णांक netup_ci_set_irq(काष्ठा dvb_ca_en50221 *en50221, u8 irq_mode)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	पूर्णांक ret;

	अगर (irq_mode == state->current_irq_mode)
		वापस 0;

	ci_dbg_prपूर्णांक("%s: chipaddr=[0x%x] setting ci IRQ to [0x%x] \n",
			__func__, state->ci_i2c_addr, irq_mode);
	ret = netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
							0x1b, &irq_mode, 1);

	अगर (ret != 0)
		वापस ret;

	state->current_irq_mode = irq_mode;

	वापस 0;
पूर्ण

पूर्णांक netup_ci_slot_ts_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	u8 buf;

	अगर (0 != slot)
		वापस -EINVAL;

	netup_पढ़ो_i2c(state->i2c_adap, state->ci_i2c_addr,
			0, &buf, 1);
	buf |= 0x60;

	वापस netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
							0, &buf, 1);
पूर्ण

/* work handler */
अटल व्योम netup_पढ़ो_ci_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netup_ci_state *state =
			container_of(work, काष्ठा netup_ci_state, work);
	u8 buf[33];
	पूर्णांक ret;

	/* CAM module IRQ processing. fast operation */
	dvb_ca_en50221_frda_irq(&state->ca, 0);

	/* CAM module INSERT/REMOVE processing. slow operation because of i2c
	 * transfers */
	अगर (समय_after(jअगरfies, state->next_status_checked_समय)
			|| !state->status) अणु
		ret = netup_पढ़ो_i2c(state->i2c_adap, state->ci_i2c_addr,
				0, &buf[0], 33);

		state->next_status_checked_समय = jअगरfies
			+ msecs_to_jअगरfies(1000);

		अगर (ret != 0)
			वापस;

		ci_dbg_prपूर्णांक("%s: Slot Status Addr=[0x%04x], Reg=[0x%02x], data=%02x, TS config = %02x\n",
			     __func__,	state->ci_i2c_addr, 0, buf[0], buf[0]);


		अगर (buf[0] & 1)
			state->status = DVB_CA_EN50221_POLL_CAM_PRESENT |
				DVB_CA_EN50221_POLL_CAM_READY;
		अन्यथा
			state->status = 0;
	पूर्ण
पूर्ण

/* CI irq handler */
पूर्णांक netup_ci_slot_status(काष्ठा cx23885_dev *dev, u32 pci_status)
अणु
	काष्ठा cx23885_tsport *port = शून्य;
	काष्ठा netup_ci_state *state = शून्य;

	ci_dbg_prपूर्णांक("%s:\n", __func__);

	अगर (0 == (pci_status & (PCI_MSK_GPIO0 | PCI_MSK_GPIO1)))
		वापस 0;

	अगर (pci_status & PCI_MSK_GPIO0) अणु
		port = &dev->ts1;
		state = port->port_priv;
		schedule_work(&state->work);
		ci_dbg_prपूर्णांक("%s: Wakeup CI0\n", __func__);
	पूर्ण

	अगर (pci_status & PCI_MSK_GPIO1) अणु
		port = &dev->ts2;
		state = port->port_priv;
		schedule_work(&state->work);
		ci_dbg_prपूर्णांक("%s: Wakeup CI1\n", __func__);
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक netup_poll_ci_slot_status(काष्ठा dvb_ca_en50221 *en50221,
				     पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा netup_ci_state *state = en50221->data;

	अगर (0 != slot)
		वापस -EINVAL;

	netup_ci_set_irq(en50221, खोलो ? (NETUP_IRQ_DETAM | ci_irq_flags())
			: NETUP_IRQ_DETAM);

	वापस state->status;
पूर्ण

पूर्णांक netup_ci_init(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा netup_ci_state *state;
	u8 cimax_init[34] = अणु
		0x00, /* module A control*/
		0x00, /* स्वतः select mask high A */
		0x00, /* स्वतः select mask low A */
		0x00, /* स्वतः select pattern high A */
		0x00, /* स्वतः select pattern low A */
		0x44, /* memory access समय A */
		0x00, /* invert input A */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* module B control*/
		0x00, /* स्वतः select mask high B */
		0x00, /* स्वतः select mask low B */
		0x00, /* स्वतः select pattern high B */
		0x00, /* स्वतः select pattern low B */
		0x44, /* memory access समय B */
		0x00, /* invert input B */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* स्वतः select mask high Ext */
		0x00, /* स्वतः select mask low Ext */
		0x00, /* स्वतः select pattern high Ext */
		0x00, /* स्वतः select pattern low Ext */
		0x00, /* RFU */
		0x02, /* destination - module A */
		0x01, /* घातer on (use it like store place) */
		0x00, /* RFU */
		0x00, /* पूर्णांक status पढ़ो only */
		ci_irq_flags() | NETUP_IRQ_DETAM, /* DETAM, IRQAM unmasked */
		0x05, /* EXTINT=active-high, INT=push-pull */
		0x00, /* USCG1 */
		0x04, /* ack active low */
		0x00, /* LOCK = 0 */
		0x33, /* serial mode, rising in, rising out, MSB first*/
		0x31, /* synchronization */
	पूर्ण;
	पूर्णांक ret;

	ci_dbg_prपूर्णांक("%s\n", __func__);
	state = kzalloc(माप(काष्ठा netup_ci_state), GFP_KERNEL);
	अगर (!state) अणु
		ci_dbg_prपूर्णांक("%s: Unable create CI structure!\n", __func__);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	port->port_priv = state;

	चयन (port->nr) अणु
	हाल 1:
		state->ci_i2c_addr = 0x40;
		अवरोध;
	हाल 2:
		state->ci_i2c_addr = 0x41;
		अवरोध;
	पूर्ण

	state->i2c_adap = &port->dev->i2c_bus[0].i2c_adap;
	state->ca.owner = THIS_MODULE;
	state->ca.पढ़ो_attribute_mem = netup_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem = netup_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control = netup_ci_पढ़ो_cam_ctl;
	state->ca.ग_लिखो_cam_control = netup_ci_ग_लिखो_cam_ctl;
	state->ca.slot_reset = netup_ci_slot_reset;
	state->ca.slot_shutकरोwn = netup_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable = netup_ci_slot_ts_ctl;
	state->ca.poll_slot_status = netup_poll_ci_slot_status;
	state->ca.data = state;
	state->priv = port;
	state->current_irq_mode = ci_irq_flags() | NETUP_IRQ_DETAM;

	ret = netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
						0, &cimax_init[0], 34);
	/* lock रेजिस्टरs */
	ret |= netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
						0x1f, &cimax_init[0x18], 1);
	/* घातer on slots */
	ret |= netup_ग_लिखो_i2c(state->i2c_adap, state->ci_i2c_addr,
						0x18, &cimax_init[0x18], 1);

	अगर (0 != ret)
		जाओ err;

	ret = dvb_ca_en50221_init(&port->frontends.adapter,
				   &state->ca,
				   /* flags */ 0,
				   /* n_slots */ 1);
	अगर (0 != ret)
		जाओ err;

	INIT_WORK(&state->work, netup_पढ़ो_ci_status);
	schedule_work(&state->work);

	ci_dbg_prपूर्णांक("%s: CI initialized!\n", __func__);

	वापस 0;
err:
	ci_dbg_prपूर्णांक("%s: Cannot initialize CI: Error %d.\n", __func__, ret);
	kमुक्त(state);
	वापस ret;
पूर्ण

व्योम netup_ci_निकास(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा netup_ci_state *state;

	अगर (शून्य == port)
		वापस;

	state = (काष्ठा netup_ci_state *)port->port_priv;
	अगर (शून्य == state)
		वापस;

	अगर (शून्य == state->ca.data)
		वापस;

	dvb_ca_en50221_release(&state->ca);
	kमुक्त(state);
पूर्ण
