<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Silvaco dual-role I3C master driver
 *
 * Copyright (C) 2020 Silvaco
 * Author: Miquel RAYNAL <miquel.raynal@bootlin.com>
 * Based on a work from: Conor Culhane <conor.culhane@silvaco.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/* Master Mode Registers */
#घोषणा SVC_I3C_MCONFIG      0x000
#घोषणा   SVC_I3C_MCONFIG_MASTER_EN BIT(0)
#घोषणा   SVC_I3C_MCONFIG_DISTO(x) FIELD_PREP(BIT(3), (x))
#घोषणा   SVC_I3C_MCONFIG_HKEEP(x) FIELD_PREP(GENMASK(5, 4), (x))
#घोषणा   SVC_I3C_MCONFIG_ODSTOP(x) FIELD_PREP(BIT(6), (x))
#घोषणा   SVC_I3C_MCONFIG_PPBAUD(x) FIELD_PREP(GENMASK(11, 8), (x))
#घोषणा   SVC_I3C_MCONFIG_PPLOW(x) FIELD_PREP(GENMASK(15, 12), (x))
#घोषणा   SVC_I3C_MCONFIG_ODBAUD(x) FIELD_PREP(GENMASK(23, 16), (x))
#घोषणा   SVC_I3C_MCONFIG_ODHPP(x) FIELD_PREP(BIT(24), (x))
#घोषणा   SVC_I3C_MCONFIG_SKEW(x) FIELD_PREP(GENMASK(27, 25), (x))
#घोषणा   SVC_I3C_MCONFIG_I2CBAUD(x) FIELD_PREP(GENMASK(31, 28), (x))

#घोषणा SVC_I3C_MCTRL        0x084
#घोषणा   SVC_I3C_MCTRL_REQUEST_MASK GENMASK(2, 0)
#घोषणा   SVC_I3C_MCTRL_REQUEST_NONE 0
#घोषणा   SVC_I3C_MCTRL_REQUEST_START_ADDR 1
#घोषणा   SVC_I3C_MCTRL_REQUEST_STOP 2
#घोषणा   SVC_I3C_MCTRL_REQUEST_IBI_ACKNACK 3
#घोषणा   SVC_I3C_MCTRL_REQUEST_PROC_DAA 4
#घोषणा   SVC_I3C_MCTRL_REQUEST_AUTO_IBI 7
#घोषणा   SVC_I3C_MCTRL_TYPE_I3C 0
#घोषणा   SVC_I3C_MCTRL_TYPE_I2C BIT(4)
#घोषणा   SVC_I3C_MCTRL_IBIRESP_AUTO 0
#घोषणा   SVC_I3C_MCTRL_IBIRESP_ACK_WITHOUT_BYTE 0
#घोषणा   SVC_I3C_MCTRL_IBIRESP_ACK_WITH_BYTE BIT(7)
#घोषणा   SVC_I3C_MCTRL_IBIRESP_NACK BIT(6)
#घोषणा   SVC_I3C_MCTRL_IBIRESP_MANUAL GENMASK(7, 6)
#घोषणा   SVC_I3C_MCTRL_सूची(x) FIELD_PREP(BIT(8), (x))
#घोषणा   SVC_I3C_MCTRL_सूची_WRITE 0
#घोषणा   SVC_I3C_MCTRL_सूची_READ 1
#घोषणा   SVC_I3C_MCTRL_ADDR(x) FIELD_PREP(GENMASK(15, 9), (x))
#घोषणा   SVC_I3C_MCTRL_RDTERM(x) FIELD_PREP(GENMASK(23, 16), (x))

#घोषणा SVC_I3C_MSTATUS      0x088
#घोषणा   SVC_I3C_MSTATUS_STATE(x) FIELD_GET(GENMASK(2, 0), (x))
#घोषणा   SVC_I3C_MSTATUS_STATE_DAA(x) (SVC_I3C_MSTATUS_STATE(x) == 5)
#घोषणा   SVC_I3C_MSTATUS_STATE_IDLE(x) (SVC_I3C_MSTATUS_STATE(x) == 0)
#घोषणा   SVC_I3C_MSTATUS_BETWEEN(x) FIELD_GET(BIT(4), (x))
#घोषणा   SVC_I3C_MSTATUS_NACKED(x) FIELD_GET(BIT(5), (x))
#घोषणा   SVC_I3C_MSTATUS_IBITYPE(x) FIELD_GET(GENMASK(7, 6), (x))
#घोषणा   SVC_I3C_MSTATUS_IBITYPE_IBI 1
#घोषणा   SVC_I3C_MSTATUS_IBITYPE_MASTER_REQUEST 2
#घोषणा   SVC_I3C_MSTATUS_IBITYPE_HOT_JOIN 3
#घोषणा   SVC_I3C_MINT_SLVSTART BIT(8)
#घोषणा   SVC_I3C_MINT_MCTRLDONE BIT(9)
#घोषणा   SVC_I3C_MINT_COMPLETE BIT(10)
#घोषणा   SVC_I3C_MINT_RXPEND BIT(11)
#घोषणा   SVC_I3C_MINT_TXNOTFULL BIT(12)
#घोषणा   SVC_I3C_MINT_IBIWON BIT(13)
#घोषणा   SVC_I3C_MINT_ERRWARN BIT(15)
#घोषणा   SVC_I3C_MSTATUS_SLVSTART(x) FIELD_GET(SVC_I3C_MINT_SLVSTART, (x))
#घोषणा   SVC_I3C_MSTATUS_MCTRLDONE(x) FIELD_GET(SVC_I3C_MINT_MCTRLDONE, (x))
#घोषणा   SVC_I3C_MSTATUS_COMPLETE(x) FIELD_GET(SVC_I3C_MINT_COMPLETE, (x))
#घोषणा   SVC_I3C_MSTATUS_RXPEND(x) FIELD_GET(SVC_I3C_MINT_RXPEND, (x))
#घोषणा   SVC_I3C_MSTATUS_TXNOTFULL(x) FIELD_GET(SVC_I3C_MINT_TXNOTFULL, (x))
#घोषणा   SVC_I3C_MSTATUS_IBIWON(x) FIELD_GET(SVC_I3C_MINT_IBIWON, (x))
#घोषणा   SVC_I3C_MSTATUS_ERRWARN(x) FIELD_GET(SVC_I3C_MINT_ERRWARN, (x))
#घोषणा   SVC_I3C_MSTATUS_IBIADDR(x) FIELD_GET(GENMASK(30, 24), (x))

#घोषणा SVC_I3C_IBIRULES     0x08C
#घोषणा   SVC_I3C_IBIRULES_ADDR(slot, addr) FIELD_PREP(GENMASK(29, 0), \
						       ((addr) & 0x3F) << ((slot) * 6))
#घोषणा   SVC_I3C_IBIRULES_ADDRS 5
#घोषणा   SVC_I3C_IBIRULES_MSB0 BIT(30)
#घोषणा   SVC_I3C_IBIRULES_NOBYTE BIT(31)
#घोषणा   SVC_I3C_IBIRULES_MANDBYTE 0
#घोषणा SVC_I3C_MINTSET      0x090
#घोषणा SVC_I3C_MINTCLR      0x094
#घोषणा SVC_I3C_MINTMASKED   0x098
#घोषणा SVC_I3C_MERRWARN     0x09C
#घोषणा SVC_I3C_MDMACTRL     0x0A0
#घोषणा SVC_I3C_MDATACTRL    0x0AC
#घोषणा   SVC_I3C_MDATACTRL_FLUSHTB BIT(0)
#घोषणा   SVC_I3C_MDATACTRL_FLUSHRB BIT(1)
#घोषणा   SVC_I3C_MDATACTRL_UNLOCK_TRIG BIT(3)
#घोषणा   SVC_I3C_MDATACTRL_TXTRIG_FIFO_NOT_FULL GENMASK(5, 4)
#घोषणा   SVC_I3C_MDATACTRL_RXTRIG_FIFO_NOT_EMPTY 0
#घोषणा   SVC_I3C_MDATACTRL_RXCOUNT(x) FIELD_GET(GENMASK(28, 24), (x))
#घोषणा   SVC_I3C_MDATACTRL_TXFULL BIT(30)
#घोषणा   SVC_I3C_MDATACTRL_RXEMPTY BIT(31)

#घोषणा SVC_I3C_MWDATAB      0x0B0
#घोषणा   SVC_I3C_MWDATAB_END BIT(8)

#घोषणा SVC_I3C_MWDATABE     0x0B4
#घोषणा SVC_I3C_MWDATAH      0x0B8
#घोषणा SVC_I3C_MWDATAHE     0x0BC
#घोषणा SVC_I3C_MRDATAB      0x0C0
#घोषणा SVC_I3C_MRDATAH      0x0C8
#घोषणा SVC_I3C_MWMSG_SDR    0x0D0
#घोषणा SVC_I3C_MRMSG_SDR    0x0D4
#घोषणा SVC_I3C_MWMSG_DDR    0x0D8
#घोषणा SVC_I3C_MRMSG_DDR    0x0DC

#घोषणा SVC_I3C_MDYNADDR     0x0E4
#घोषणा   SVC_MDYNADDR_VALID BIT(0)
#घोषणा   SVC_MDYNADDR_ADDR(x) FIELD_PREP(GENMASK(7, 1), (x))

#घोषणा SVC_I3C_MAX_DEVS 32

/* This parameter depends on the implementation and may be tuned */
#घोषणा SVC_I3C_FIFO_SIZE 16

काष्ठा svc_i3c_cmd अणु
	u8 addr;
	bool rnw;
	u8 *in;
	स्थिर व्योम *out;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक पढ़ो_len;
	bool जारीd;
पूर्ण;

काष्ठा svc_i3c_xfer अणु
	काष्ठा list_head node;
	काष्ठा completion comp;
	पूर्णांक ret;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक ncmds;
	काष्ठा svc_i3c_cmd cmds[];
पूर्ण;

/**
 * काष्ठा svc_i3c_master - Silvaco I3C Master काष्ठाure
 * @base: I3C master controller
 * @dev: Corresponding device
 * @regs: Memory mapping
 * @मुक्त_slots: Bit array of available slots
 * @addrs: Array containing the dynamic addresses of each attached device
 * @descs: Array of descriptors, one per attached device
 * @hj_work: Hot-join work
 * @ibi_work: IBI work
 * @irq: Main पूर्णांकerrupt
 * @pclk: System घड़ी
 * @fclk: Fast घड़ी (bus)
 * @sclk: Slow घड़ी (other events)
 * @xferqueue: Transfer queue काष्ठाure
 * @xferqueue.list: List member
 * @xferqueue.cur: Current ongoing transfer
 * @xferqueue.lock: Queue lock
 * @ibi: IBI काष्ठाure
 * @ibi.num_slots: Number of slots available in @ibi.slots
 * @ibi.slots: Available IBI slots
 * @ibi.tbq_slot: To be queued IBI slot
 * @ibi.lock: IBI lock
 */
काष्ठा svc_i3c_master अणु
	काष्ठा i3c_master_controller base;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	u32 मुक्त_slots;
	u8 addrs[SVC_I3C_MAX_DEVS];
	काष्ठा i3c_dev_desc *descs[SVC_I3C_MAX_DEVS];
	काष्ठा work_काष्ठा hj_work;
	काष्ठा work_काष्ठा ibi_work;
	पूर्णांक irq;
	काष्ठा clk *pclk;
	काष्ठा clk *fclk;
	काष्ठा clk *sclk;
	काष्ठा अणु
		काष्ठा list_head list;
		काष्ठा svc_i3c_xfer *cur;
		/* Prevent races between transfers */
		spinlock_t lock;
	पूर्ण xferqueue;
	काष्ठा अणु
		अचिन्हित पूर्णांक num_slots;
		काष्ठा i3c_dev_desc **slots;
		काष्ठा i3c_ibi_slot *tbq_slot;
		/* Prevent races within IBI handlers */
		spinlock_t lock;
	पूर्ण ibi;
पूर्ण;

/**
 * काष्ठा svc_i3c_i3c_dev_data - Device specअगरic data
 * @index: Index in the master tables corresponding to this device
 * @ibi: IBI slot index in the master काष्ठाure
 * @ibi_pool: IBI pool associated to this device
 */
काष्ठा svc_i3c_i2c_dev_data अणु
	u8 index;
	पूर्णांक ibi;
	काष्ठा i3c_generic_ibi_pool *ibi_pool;
पूर्ण;

अटल bool svc_i3c_master_error(काष्ठा svc_i3c_master *master)
अणु
	u32 mstatus, merrwarn;

	mstatus = पढ़ोl(master->regs + SVC_I3C_MSTATUS);
	अगर (SVC_I3C_MSTATUS_ERRWARN(mstatus)) अणु
		merrwarn = पढ़ोl(master->regs + SVC_I3C_MERRWARN);
		ग_लिखोl(merrwarn, master->regs + SVC_I3C_MERRWARN);
		dev_err(master->dev,
			"Error condition: MSTATUS 0x%08x, MERRWARN 0x%08x\n",
			mstatus, merrwarn);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम svc_i3c_master_enable_पूर्णांकerrupts(काष्ठा svc_i3c_master *master, u32 mask)
अणु
	ग_लिखोl(mask, master->regs + SVC_I3C_MINTSET);
पूर्ण

अटल व्योम svc_i3c_master_disable_पूर्णांकerrupts(काष्ठा svc_i3c_master *master)
अणु
	u32 mask = पढ़ोl(master->regs + SVC_I3C_MINTSET);

	ग_लिखोl(mask, master->regs + SVC_I3C_MINTCLR);
पूर्ण

अटल अंतरभूत काष्ठा svc_i3c_master *
to_svc_i3c_master(काष्ठा i3c_master_controller *master)
अणु
	वापस container_of(master, काष्ठा svc_i3c_master, base);
पूर्ण

अटल व्योम svc_i3c_master_hj_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा svc_i3c_master *master;

	master = container_of(work, काष्ठा svc_i3c_master, hj_work);
	i3c_master_करो_daa(&master->base);
पूर्ण

अटल काष्ठा i3c_dev_desc *
svc_i3c_master_dev_from_addr(काष्ठा svc_i3c_master *master,
			     अचिन्हित पूर्णांक ibiaddr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SVC_I3C_MAX_DEVS; i++)
		अगर (master->addrs[i] == ibiaddr)
			अवरोध;

	अगर (i == SVC_I3C_MAX_DEVS)
		वापस शून्य;

	वापस master->descs[i];
पूर्ण

अटल व्योम svc_i3c_master_emit_stop(काष्ठा svc_i3c_master *master)
अणु
	ग_लिखोl(SVC_I3C_MCTRL_REQUEST_STOP, master->regs + SVC_I3C_MCTRL);

	/*
	 * This delay is necessary after the emission of a stop, otherwise eg.
	 * repeating IBIs करो not get detected. There is a note in the manual
	 * about it, stating that the stop condition might not be settled
	 * correctly अगर a start condition follows too rapidly.
	 */
	udelay(1);
पूर्ण

अटल व्योम svc_i3c_master_clear_merrwarn(काष्ठा svc_i3c_master *master)
अणु
	ग_लिखोl(पढ़ोl(master->regs + SVC_I3C_MERRWARN),
	       master->regs + SVC_I3C_MERRWARN);
पूर्ण

अटल पूर्णांक svc_i3c_master_handle_ibi(काष्ठा svc_i3c_master *master,
				     काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_ibi_slot *slot;
	अचिन्हित पूर्णांक count;
	u32 mdatactrl;
	u8 *buf;

	slot = i3c_generic_ibi_get_मुक्त_slot(data->ibi_pool);
	अगर (!slot)
		वापस -ENOSPC;

	slot->len = 0;
	buf = slot->data;

	जबतक (SVC_I3C_MSTATUS_RXPEND(पढ़ोl(master->regs + SVC_I3C_MSTATUS))  &&
	       slot->len < SVC_I3C_FIFO_SIZE) अणु
		mdatactrl = पढ़ोl(master->regs + SVC_I3C_MDATACTRL);
		count = SVC_I3C_MDATACTRL_RXCOUNT(mdatactrl);
		पढ़ोsl(master->regs + SVC_I3C_MRDATAB, buf, count);
		slot->len += count;
		buf += count;
	पूर्ण

	master->ibi.tbq_slot = slot;

	वापस 0;
पूर्ण

अटल व्योम svc_i3c_master_ack_ibi(काष्ठा svc_i3c_master *master,
				   bool mandatory_byte)
अणु
	अचिन्हित पूर्णांक ibi_ack_nack;

	ibi_ack_nack = SVC_I3C_MCTRL_REQUEST_IBI_ACKNACK;
	अगर (mandatory_byte)
		ibi_ack_nack |= SVC_I3C_MCTRL_IBIRESP_ACK_WITH_BYTE;
	अन्यथा
		ibi_ack_nack |= SVC_I3C_MCTRL_IBIRESP_ACK_WITHOUT_BYTE;

	ग_लिखोl(ibi_ack_nack, master->regs + SVC_I3C_MCTRL);
पूर्ण

अटल व्योम svc_i3c_master_nack_ibi(काष्ठा svc_i3c_master *master)
अणु
	ग_लिखोl(SVC_I3C_MCTRL_REQUEST_IBI_ACKNACK |
	       SVC_I3C_MCTRL_IBIRESP_NACK,
	       master->regs + SVC_I3C_MCTRL);
पूर्ण

अटल व्योम svc_i3c_master_ibi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा svc_i3c_master *master = container_of(work, काष्ठा svc_i3c_master, ibi_work);
	काष्ठा svc_i3c_i2c_dev_data *data;
	अचिन्हित पूर्णांक ibitype, ibiaddr;
	काष्ठा i3c_dev_desc *dev;
	u32 status, val;
	पूर्णांक ret;

	/* Acknowledge the incoming पूर्णांकerrupt with the AUTOIBI mechanism */
	ग_लिखोl(SVC_I3C_MCTRL_REQUEST_AUTO_IBI |
	       SVC_I3C_MCTRL_IBIRESP_AUTO,
	       master->regs + SVC_I3C_MCTRL);

	/* Wait क्रम IBIWON, should take approximately 100us */
	ret = पढ़ोl_relaxed_poll_समयout(master->regs + SVC_I3C_MSTATUS, val,
					 SVC_I3C_MSTATUS_IBIWON(val), 0, 1000);
	अगर (ret) अणु
		dev_err(master->dev, "Timeout when polling for IBIWON\n");
		जाओ reenable_ibis;
	पूर्ण

	/* Clear the पूर्णांकerrupt status */
	ग_लिखोl(SVC_I3C_MINT_IBIWON, master->regs + SVC_I3C_MSTATUS);

	status = पढ़ोl(master->regs + SVC_I3C_MSTATUS);
	ibitype = SVC_I3C_MSTATUS_IBITYPE(status);
	ibiaddr = SVC_I3C_MSTATUS_IBIADDR(status);

	/* Handle the critical responses to IBI's */
	चयन (ibitype) अणु
	हाल SVC_I3C_MSTATUS_IBITYPE_IBI:
		dev = svc_i3c_master_dev_from_addr(master, ibiaddr);
		अगर (!dev)
			svc_i3c_master_nack_ibi(master);
		अन्यथा
			svc_i3c_master_handle_ibi(master, dev);
		अवरोध;
	हाल SVC_I3C_MSTATUS_IBITYPE_HOT_JOIN:
		svc_i3c_master_ack_ibi(master, false);
		अवरोध;
	हाल SVC_I3C_MSTATUS_IBITYPE_MASTER_REQUEST:
		svc_i3c_master_nack_ibi(master);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * If an error happened, we probably got पूर्णांकerrupted and the exchange
	 * समयकरोut. In this हाल we just drop everything, emit a stop and रुको
	 * क्रम the slave to पूर्णांकerrupt again.
	 */
	अगर (svc_i3c_master_error(master)) अणु
		अगर (master->ibi.tbq_slot) अणु
			data = i3c_dev_get_master_data(dev);
			i3c_generic_ibi_recycle_slot(data->ibi_pool,
						     master->ibi.tbq_slot);
			master->ibi.tbq_slot = शून्य;
		पूर्ण

		svc_i3c_master_emit_stop(master);

		जाओ reenable_ibis;
	पूर्ण

	/* Handle the non critical tasks */
	चयन (ibitype) अणु
	हाल SVC_I3C_MSTATUS_IBITYPE_IBI:
		अगर (dev) अणु
			i3c_master_queue_ibi(dev, master->ibi.tbq_slot);
			master->ibi.tbq_slot = शून्य;
		पूर्ण
		svc_i3c_master_emit_stop(master);
		अवरोध;
	हाल SVC_I3C_MSTATUS_IBITYPE_HOT_JOIN:
		queue_work(master->base.wq, &master->hj_work);
		अवरोध;
	हाल SVC_I3C_MSTATUS_IBITYPE_MASTER_REQUEST:
	शेष:
		अवरोध;
	पूर्ण

reenable_ibis:
	svc_i3c_master_enable_पूर्णांकerrupts(master, SVC_I3C_MINT_SLVSTART);
पूर्ण

अटल irqवापस_t svc_i3c_master_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा svc_i3c_master *master = (काष्ठा svc_i3c_master *)dev_id;
	u32 active = पढ़ोl(master->regs + SVC_I3C_MINTMASKED);

	अगर (!SVC_I3C_MSTATUS_SLVSTART(active))
		वापस IRQ_NONE;

	/* Clear the पूर्णांकerrupt status */
	ग_लिखोl(SVC_I3C_MINT_SLVSTART, master->regs + SVC_I3C_MSTATUS);

	svc_i3c_master_disable_पूर्णांकerrupts(master);

	/* Handle the पूर्णांकerrupt in a non atomic context */
	queue_work(master->base.wq, &master->ibi_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक svc_i3c_master_bus_init(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा i3c_bus *bus = i3c_master_get_bus(m);
	काष्ठा i3c_device_info info = अणुपूर्ण;
	अचिन्हित दीर्घ fclk_rate, fclk_period_ns;
	अचिन्हित पूर्णांक high_period_ns, od_low_period_ns;
	u32 ppbaud, pplow, odhpp, odbaud, i2cbaud, reg;
	पूर्णांक ret;

	/* Timings derivation */
	fclk_rate = clk_get_rate(master->fclk);
	अगर (!fclk_rate)
		वापस -EINVAL;

	fclk_period_ns = DIV_ROUND_UP(1000000000, fclk_rate);

	/*
	 * Using I3C Push-Pull mode, target is 12.5MHz/80ns period.
	 * Simplest configuration is using a 50% duty-cycle of 40ns.
	 */
	ppbaud = DIV_ROUND_UP(40, fclk_period_ns) - 1;
	pplow = 0;

	/*
	 * Using I3C Open-Drain mode, target is 4.17MHz/240ns with a
	 * duty-cycle tuned so that high levels are filetered out by
	 * the 50ns filter (target being 40ns).
	 */
	odhpp = 1;
	high_period_ns = (ppbaud + 1) * fclk_period_ns;
	odbaud = DIV_ROUND_UP(240 - high_period_ns, high_period_ns) - 1;
	od_low_period_ns = (odbaud + 1) * high_period_ns;

	चयन (bus->mode) अणु
	हाल I3C_BUS_MODE_PURE:
		i2cbaud = 0;
		अवरोध;
	हाल I3C_BUS_MODE_MIXED_FAST:
	हाल I3C_BUS_MODE_MIXED_LIMITED:
		/*
		 * Using I2C Fm+ mode, target is 1MHz/1000ns, the dअगरference
		 * between the high and low period करोes not really matter.
		 */
		i2cbaud = DIV_ROUND_UP(1000, od_low_period_ns) - 2;
		अवरोध;
	हाल I3C_BUS_MODE_MIXED_SLOW:
		/*
		 * Using I2C Fm mode, target is 0.4MHz/2500ns, with the same
		 * स्थिरraपूर्णांकs as the FM+ mode.
		 */
		i2cbaud = DIV_ROUND_UP(2500, od_low_period_ns) - 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = SVC_I3C_MCONFIG_MASTER_EN |
	      SVC_I3C_MCONFIG_DISTO(0) |
	      SVC_I3C_MCONFIG_HKEEP(0) |
	      SVC_I3C_MCONFIG_ODSTOP(0) |
	      SVC_I3C_MCONFIG_PPBAUD(ppbaud) |
	      SVC_I3C_MCONFIG_PPLOW(pplow) |
	      SVC_I3C_MCONFIG_ODBAUD(odbaud) |
	      SVC_I3C_MCONFIG_ODHPP(odhpp) |
	      SVC_I3C_MCONFIG_SKEW(0) |
	      SVC_I3C_MCONFIG_I2CBAUD(i2cbaud);
	ग_लिखोl(reg, master->regs + SVC_I3C_MCONFIG);

	/* Master core's registration */
	ret = i3c_master_get_मुक्त_addr(m, 0);
	अगर (ret < 0)
		वापस ret;

	info.dyn_addr = ret;

	ग_लिखोl(SVC_MDYNADDR_VALID | SVC_MDYNADDR_ADDR(info.dyn_addr),
	       master->regs + SVC_I3C_MDYNADDR);

	ret = i3c_master_set_info(&master->base, &info);
	अगर (ret)
		वापस ret;

	svc_i3c_master_enable_पूर्णांकerrupts(master, SVC_I3C_MINT_SLVSTART);

	वापस 0;
पूर्ण

अटल व्योम svc_i3c_master_bus_cleanup(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);

	svc_i3c_master_disable_पूर्णांकerrupts(master);

	/* Disable master */
	ग_लिखोl(0, master->regs + SVC_I3C_MCONFIG);
पूर्ण

अटल पूर्णांक svc_i3c_master_reserve_slot(काष्ठा svc_i3c_master *master)
अणु
	अचिन्हित पूर्णांक slot;

	अगर (!(master->मुक्त_slots & GENMASK(SVC_I3C_MAX_DEVS - 1, 0)))
		वापस -ENOSPC;

	slot = ffs(master->मुक्त_slots) - 1;

	master->मुक्त_slots &= ~BIT(slot);

	वापस slot;
पूर्ण

अटल व्योम svc_i3c_master_release_slot(काष्ठा svc_i3c_master *master,
					अचिन्हित पूर्णांक slot)
अणु
	master->मुक्त_slots |= BIT(slot);
पूर्ण

अटल पूर्णांक svc_i3c_master_attach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data;
	पूर्णांक slot;

	slot = svc_i3c_master_reserve_slot(master);
	अगर (slot < 0)
		वापस slot;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		svc_i3c_master_release_slot(master, slot);
		वापस -ENOMEM;
	पूर्ण

	data->ibi = -1;
	data->index = slot;
	master->addrs[slot] = dev->info.dyn_addr ? dev->info.dyn_addr :
						   dev->info.अटल_addr;
	master->descs[slot] = dev;

	i3c_dev_set_master_data(dev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_master_reattach_i3c_dev(काष्ठा i3c_dev_desc *dev,
					   u8 old_dyn_addr)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	master->addrs[data->index] = dev->info.dyn_addr ? dev->info.dyn_addr :
							  dev->info.अटल_addr;

	वापस 0;
पूर्ण

अटल व्योम svc_i3c_master_detach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);

	master->addrs[data->index] = 0;
	svc_i3c_master_release_slot(master, data->index);

	kमुक्त(data);
पूर्ण

अटल पूर्णांक svc_i3c_master_attach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data;
	पूर्णांक slot;

	slot = svc_i3c_master_reserve_slot(master);
	अगर (slot < 0)
		वापस slot;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		svc_i3c_master_release_slot(master, slot);
		वापस -ENOMEM;
	पूर्ण

	data->index = slot;
	master->addrs[slot] = dev->addr;

	i2c_dev_set_master_data(dev, data);

	वापस 0;
पूर्ण

अटल व्योम svc_i3c_master_detach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा svc_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);

	svc_i3c_master_release_slot(master, data->index);

	kमुक्त(data);
पूर्ण

अटल पूर्णांक svc_i3c_master_पढ़ोb(काष्ठा svc_i3c_master *master, u8 *dst,
				अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret, i;
	u32 reg;

	क्रम (i = 0; i < len; i++) अणु
		ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MSTATUS, reg,
					 SVC_I3C_MSTATUS_RXPEND(reg), 0, 1000);
		अगर (ret)
			वापस ret;

		dst[i] = पढ़ोl(master->regs + SVC_I3C_MRDATAB);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_master_करो_daa_locked(काष्ठा svc_i3c_master *master,
					u8 *addrs, अचिन्हित पूर्णांक *count)
अणु
	u64 prov_id[SVC_I3C_MAX_DEVS] = अणुपूर्ण, nacking_prov_id = 0;
	अचिन्हित पूर्णांक dev_nb = 0, last_addr = 0;
	u32 reg;
	पूर्णांक ret, i;

	जबतक (true) अणु
		/* Enter/proceed with DAA */
		ग_लिखोl(SVC_I3C_MCTRL_REQUEST_PROC_DAA |
		       SVC_I3C_MCTRL_TYPE_I3C |
		       SVC_I3C_MCTRL_IBIRESP_NACK |
		       SVC_I3C_MCTRL_सूची(SVC_I3C_MCTRL_सूची_WRITE),
		       master->regs + SVC_I3C_MCTRL);

		/*
		 * Either one slave will send its ID, or the assignment process
		 * is करोne.
		 */
		ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MSTATUS, reg,
					 SVC_I3C_MSTATUS_RXPEND(reg) |
					 SVC_I3C_MSTATUS_MCTRLDONE(reg),
					 1, 1000);
		अगर (ret)
			वापस ret;

		अगर (SVC_I3C_MSTATUS_RXPEND(reg)) अणु
			u8 data[6];

			/*
			 * We only care about the 48-bit provisional ID yet to
			 * be sure a device करोes not nack an address twice.
			 * Otherwise, we would just need to flush the RX FIFO.
			 */
			ret = svc_i3c_master_पढ़ोb(master, data, 6);
			अगर (ret)
				वापस ret;

			क्रम (i = 0; i < 6; i++)
				prov_id[dev_nb] |= (u64)(data[i]) << (8 * (5 - i));

			/* We करो not care about the BCR and DCR yet */
			ret = svc_i3c_master_पढ़ोb(master, data, 2);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (SVC_I3C_MSTATUS_MCTRLDONE(reg)) अणु
			अगर (SVC_I3C_MSTATUS_STATE_IDLE(reg) &&
			    SVC_I3C_MSTATUS_COMPLETE(reg)) अणु
				/*
				 * All devices received and acked they dynamic
				 * address, this is the natural end of the DAA
				 * procedure.
				 */
				अवरोध;
			पूर्ण अन्यथा अगर (SVC_I3C_MSTATUS_NACKED(reg)) अणु
				/*
				 * A slave device nacked the address, this is
				 * allowed only once, DAA will be stopped and
				 * then resumed. The same device is supposed to
				 * answer again immediately and shall ack the
				 * address this समय.
				 */
				अगर (prov_id[dev_nb] == nacking_prov_id)
					वापस -EIO;

				dev_nb--;
				nacking_prov_id = prov_id[dev_nb];
				svc_i3c_master_emit_stop(master);

				जारी;
			पूर्ण अन्यथा अणु
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* Wait क्रम the slave to be पढ़ोy to receive its address */
		ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MSTATUS, reg,
					 SVC_I3C_MSTATUS_MCTRLDONE(reg) &&
					 SVC_I3C_MSTATUS_STATE_DAA(reg) &&
					 SVC_I3C_MSTATUS_BETWEEN(reg),
					 0, 1000);
		अगर (ret)
			वापस ret;

		/* Give the slave device a suitable dynamic address */
		ret = i3c_master_get_मुक्त_addr(&master->base, last_addr + 1);
		अगर (ret < 0)
			वापस ret;

		addrs[dev_nb] = ret;
		dev_dbg(master->dev, "DAA: device %d assigned to 0x%02x\n",
			dev_nb, addrs[dev_nb]);

		ग_लिखोl(addrs[dev_nb], master->regs + SVC_I3C_MWDATAB);
		last_addr = addrs[dev_nb++];
	पूर्ण

	*count = dev_nb;

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_update_ibirules(काष्ठा svc_i3c_master *master)
अणु
	काष्ठा i3c_dev_desc *dev;
	u32 reg_mbyte = 0, reg_nobyte = SVC_I3C_IBIRULES_NOBYTE;
	अचिन्हित पूर्णांक mbyte_addr_ok = 0, mbyte_addr_ko = 0, nobyte_addr_ok = 0,
		nobyte_addr_ko = 0;
	bool list_mbyte = false, list_nobyte = false;

	/* Create the IBIRULES रेजिस्टर क्रम both हालs */
	i3c_bus_क्रम_each_i3cdev(&master->base.bus, dev) अणु
		अगर (I3C_BCR_DEVICE_ROLE(dev->info.bcr) == I3C_BCR_I3C_MASTER)
			जारी;

		अगर (dev->info.bcr & I3C_BCR_IBI_PAYLOAD) अणु
			reg_mbyte |= SVC_I3C_IBIRULES_ADDR(mbyte_addr_ok,
							   dev->info.dyn_addr);

			/* IBI rules cannot be applied to devices with MSb=1 */
			अगर (dev->info.dyn_addr & BIT(7))
				mbyte_addr_ko++;
			अन्यथा
				mbyte_addr_ok++;
		पूर्ण अन्यथा अणु
			reg_nobyte |= SVC_I3C_IBIRULES_ADDR(nobyte_addr_ok,
							    dev->info.dyn_addr);

			/* IBI rules cannot be applied to devices with MSb=1 */
			अगर (dev->info.dyn_addr & BIT(7))
				nobyte_addr_ko++;
			अन्यथा
				nobyte_addr_ok++;
		पूर्ण
	पूर्ण

	/* Device list cannot be handled by hardware */
	अगर (!mbyte_addr_ko && mbyte_addr_ok <= SVC_I3C_IBIRULES_ADDRS)
		list_mbyte = true;

	अगर (!nobyte_addr_ko && nobyte_addr_ok <= SVC_I3C_IBIRULES_ADDRS)
		list_nobyte = true;

	/* No list can be properly handled, वापस an error */
	अगर (!list_mbyte && !list_nobyte)
		वापस -दुस्फल;

	/* Pick the first list that can be handled by hardware, अक्रमomly */
	अगर (list_mbyte)
		ग_लिखोl(reg_mbyte, master->regs + SVC_I3C_IBIRULES);
	अन्यथा
		ग_लिखोl(reg_nobyte, master->regs + SVC_I3C_IBIRULES);

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_master_करो_daa(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	u8 addrs[SVC_I3C_MAX_DEVS];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक dev_nb;
	पूर्णांक ret, i;

	spin_lock_irqsave(&master->xferqueue.lock, flags);
	ret = svc_i3c_master_करो_daa_locked(master, addrs, &dev_nb);
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
	अगर (ret)
		जाओ emit_stop;

	/* Register all devices who participated to the core */
	क्रम (i = 0; i < dev_nb; i++) अणु
		ret = i3c_master_add_i3c_dev_locked(m, addrs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Configure IBI स्वतः-rules */
	ret = svc_i3c_update_ibirules(master);
	अगर (ret) अणु
		dev_err(master->dev, "Cannot handle such a list of devices");
		वापस ret;
	पूर्ण

	वापस 0;

emit_stop:
	svc_i3c_master_emit_stop(master);
	svc_i3c_master_clear_merrwarn(master);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_पढ़ो(काष्ठा svc_i3c_master *master,
			       u8 *in, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक offset = 0, i, ret;
	u32 mdctrl;

	जबतक (offset < len) अणु
		अचिन्हित पूर्णांक count;

		ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MDATACTRL,
					 mdctrl,
					 !(mdctrl & SVC_I3C_MDATACTRL_RXEMPTY),
					 0, 1000);
		अगर (ret)
			वापस ret;

		count = SVC_I3C_MDATACTRL_RXCOUNT(mdctrl);
		क्रम (i = 0; i < count; i++)
			in[offset + i] = पढ़ोl(master->regs + SVC_I3C_MRDATAB);

		offset += count;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_master_ग_लिखो(काष्ठा svc_i3c_master *master,
				स्थिर u8 *out, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक offset = 0, ret;
	u32 mdctrl;

	जबतक (offset < len) अणु
		ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MDATACTRL,
					 mdctrl,
					 !(mdctrl & SVC_I3C_MDATACTRL_TXFULL),
					 0, 1000);
		अगर (ret)
			वापस ret;

		/*
		 * The last byte to be sent over the bus must either have the
		 * "end" bit set or be written in MWDATABE.
		 */
		अगर (likely(offset < (len - 1)))
			ग_लिखोl(out[offset++], master->regs + SVC_I3C_MWDATAB);
		अन्यथा
			ग_लिखोl(out[offset++], master->regs + SVC_I3C_MWDATABE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक svc_i3c_master_xfer(काष्ठा svc_i3c_master *master,
			       bool rnw, अचिन्हित पूर्णांक xfer_type, u8 addr,
			       u8 *in, स्थिर u8 *out, अचिन्हित पूर्णांक xfer_len,
			       अचिन्हित पूर्णांक पढ़ो_len, bool जारीd)
अणु
	u32 reg;
	पूर्णांक ret;

	ग_लिखोl(SVC_I3C_MCTRL_REQUEST_START_ADDR |
	       xfer_type |
	       SVC_I3C_MCTRL_IBIRESP_NACK |
	       SVC_I3C_MCTRL_सूची(rnw) |
	       SVC_I3C_MCTRL_ADDR(addr) |
	       SVC_I3C_MCTRL_RDTERM(पढ़ो_len),
	       master->regs + SVC_I3C_MCTRL);

	ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MSTATUS, reg,
				 SVC_I3C_MSTATUS_MCTRLDONE(reg), 0, 1000);
	अगर (ret)
		जाओ emit_stop;

	अगर (rnw)
		ret = svc_i3c_master_पढ़ो(master, in, xfer_len);
	अन्यथा
		ret = svc_i3c_master_ग_लिखो(master, out, xfer_len);
	अगर (ret)
		जाओ emit_stop;

	ret = पढ़ोl_poll_समयout(master->regs + SVC_I3C_MSTATUS, reg,
				 SVC_I3C_MSTATUS_COMPLETE(reg), 0, 1000);
	अगर (ret)
		जाओ emit_stop;

	अगर (!जारीd)
		svc_i3c_master_emit_stop(master);

	वापस 0;

emit_stop:
	svc_i3c_master_emit_stop(master);
	svc_i3c_master_clear_merrwarn(master);

	वापस ret;
पूर्ण

अटल काष्ठा svc_i3c_xfer *
svc_i3c_master_alloc_xfer(काष्ठा svc_i3c_master *master, अचिन्हित पूर्णांक ncmds)
अणु
	काष्ठा svc_i3c_xfer *xfer;

	xfer = kzalloc(काष्ठा_size(xfer, cmds, ncmds), GFP_KERNEL);
	अगर (!xfer)
		वापस शून्य;

	INIT_LIST_HEAD(&xfer->node);
	xfer->ncmds = ncmds;
	xfer->ret = -ETIMEDOUT;

	वापस xfer;
पूर्ण

अटल व्योम svc_i3c_master_मुक्त_xfer(काष्ठा svc_i3c_xfer *xfer)
अणु
	kमुक्त(xfer);
पूर्ण

अटल व्योम svc_i3c_master_dequeue_xfer_locked(काष्ठा svc_i3c_master *master,
					       काष्ठा svc_i3c_xfer *xfer)
अणु
	अगर (master->xferqueue.cur == xfer)
		master->xferqueue.cur = शून्य;
	अन्यथा
		list_del_init(&xfer->node);
पूर्ण

अटल व्योम svc_i3c_master_dequeue_xfer(काष्ठा svc_i3c_master *master,
					काष्ठा svc_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->xferqueue.lock, flags);
	svc_i3c_master_dequeue_xfer_locked(master, xfer);
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल व्योम svc_i3c_master_start_xfer_locked(काष्ठा svc_i3c_master *master)
अणु
	काष्ठा svc_i3c_xfer *xfer = master->xferqueue.cur;
	पूर्णांक ret, i;

	अगर (!xfer)
		वापस;

	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		काष्ठा svc_i3c_cmd *cmd = &xfer->cmds[i];

		ret = svc_i3c_master_xfer(master, cmd->rnw, xfer->type,
					  cmd->addr, cmd->in, cmd->out,
					  cmd->len, cmd->पढ़ो_len,
					  cmd->जारीd);
		अगर (ret)
			अवरोध;
	पूर्ण

	xfer->ret = ret;
	complete(&xfer->comp);

	अगर (ret < 0)
		svc_i3c_master_dequeue_xfer_locked(master, xfer);

	xfer = list_first_entry_or_null(&master->xferqueue.list,
					काष्ठा svc_i3c_xfer,
					node);
	अगर (xfer)
		list_del_init(&xfer->node);

	master->xferqueue.cur = xfer;
	svc_i3c_master_start_xfer_locked(master);
पूर्ण

अटल व्योम svc_i3c_master_enqueue_xfer(काष्ठा svc_i3c_master *master,
					काष्ठा svc_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	init_completion(&xfer->comp);
	spin_lock_irqsave(&master->xferqueue.lock, flags);
	अगर (master->xferqueue.cur) अणु
		list_add_tail(&xfer->node, &master->xferqueue.list);
	पूर्ण अन्यथा अणु
		master->xferqueue.cur = xfer;
		svc_i3c_master_start_xfer_locked(master);
	पूर्ण
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल bool
svc_i3c_master_supports_ccc_cmd(काष्ठा i3c_master_controller *master,
				स्थिर काष्ठा i3c_ccc_cmd *cmd)
अणु
	/* No software support क्रम CCC commands targeting more than one slave */
	वापस (cmd->ndests == 1);
पूर्ण

अटल पूर्णांक svc_i3c_master_send_bdcast_ccc_cmd(काष्ठा svc_i3c_master *master,
					      काष्ठा i3c_ccc_cmd *ccc)
अणु
	अचिन्हित पूर्णांक xfer_len = ccc->dests[0].payload.len + 1;
	काष्ठा svc_i3c_xfer *xfer;
	काष्ठा svc_i3c_cmd *cmd;
	u8 *buf;
	पूर्णांक ret;

	xfer = svc_i3c_master_alloc_xfer(master, 1);
	अगर (!xfer)
		वापस -ENOMEM;

	buf = kदो_स्मृति(xfer_len, GFP_KERNEL);
	अगर (!buf) अणु
		svc_i3c_master_मुक्त_xfer(xfer);
		वापस -ENOMEM;
	पूर्ण

	buf[0] = ccc->id;
	स_नकल(&buf[1], ccc->dests[0].payload.data, ccc->dests[0].payload.len);

	xfer->type = SVC_I3C_MCTRL_TYPE_I3C;

	cmd = &xfer->cmds[0];
	cmd->addr = ccc->dests[0].addr;
	cmd->rnw = ccc->rnw;
	cmd->in = शून्य;
	cmd->out = buf;
	cmd->len = xfer_len;
	cmd->पढ़ो_len = 0;
	cmd->जारीd = false;

	svc_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		svc_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	kमुक्त(buf);
	svc_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_send_direct_ccc_cmd(काष्ठा svc_i3c_master *master,
					      काष्ठा i3c_ccc_cmd *ccc)
अणु
	अचिन्हित पूर्णांक xfer_len = ccc->dests[0].payload.len;
	अचिन्हित पूर्णांक पढ़ो_len = ccc->rnw ? xfer_len : 0;
	काष्ठा svc_i3c_xfer *xfer;
	काष्ठा svc_i3c_cmd *cmd;
	पूर्णांक ret;

	xfer = svc_i3c_master_alloc_xfer(master, 2);
	अगर (!xfer)
		वापस -ENOMEM;

	xfer->type = SVC_I3C_MCTRL_TYPE_I3C;

	/* Broadcasted message */
	cmd = &xfer->cmds[0];
	cmd->addr = I3C_BROADCAST_ADDR;
	cmd->rnw = 0;
	cmd->in = शून्य;
	cmd->out = &ccc->id;
	cmd->len = 1;
	cmd->पढ़ो_len = 0;
	cmd->जारीd = true;

	/* Directed message */
	cmd = &xfer->cmds[1];
	cmd->addr = ccc->dests[0].addr;
	cmd->rnw = ccc->rnw;
	cmd->in = ccc->rnw ? ccc->dests[0].payload.data : शून्य;
	cmd->out = ccc->rnw ? शून्य : ccc->dests[0].payload.data,
	cmd->len = xfer_len;
	cmd->पढ़ो_len = पढ़ो_len;
	cmd->जारीd = false;

	svc_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		svc_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	svc_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_send_ccc_cmd(काष्ठा i3c_master_controller *m,
				       काष्ठा i3c_ccc_cmd *cmd)
अणु
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	bool broadcast = cmd->id < 0x80;

	अगर (broadcast)
		वापस svc_i3c_master_send_bdcast_ccc_cmd(master, cmd);
	अन्यथा
		वापस svc_i3c_master_send_direct_ccc_cmd(master, cmd);
पूर्ण

अटल पूर्णांक svc_i3c_master_priv_xfers(काष्ठा i3c_dev_desc *dev,
				     काष्ठा i3c_priv_xfer *xfers,
				     पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा svc_i3c_xfer *xfer;
	पूर्णांक ret, i;

	xfer = svc_i3c_master_alloc_xfer(master, nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	xfer->type = SVC_I3C_MCTRL_TYPE_I3C;

	क्रम (i = 0; i < nxfers; i++) अणु
		काष्ठा svc_i3c_cmd *cmd = &xfer->cmds[i];

		cmd->addr = master->addrs[data->index];
		cmd->rnw = xfers[i].rnw;
		cmd->in = xfers[i].rnw ? xfers[i].data.in : शून्य;
		cmd->out = xfers[i].rnw ? शून्य : xfers[i].data.out;
		cmd->len = xfers[i].len;
		cmd->पढ़ो_len = xfers[i].rnw ? xfers[i].len : 0;
		cmd->जारीd = (i + 1) < nxfers;
	पूर्ण

	svc_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		svc_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	svc_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_i2c_xfers(काष्ठा i2c_dev_desc *dev,
				    स्थिर काष्ठा i2c_msg *xfers,
				    पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);
	काष्ठा svc_i3c_xfer *xfer;
	पूर्णांक ret, i;

	xfer = svc_i3c_master_alloc_xfer(master, nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	xfer->type = SVC_I3C_MCTRL_TYPE_I2C;

	क्रम (i = 0; i < nxfers; i++) अणु
		काष्ठा svc_i3c_cmd *cmd = &xfer->cmds[i];

		cmd->addr = master->addrs[data->index];
		cmd->rnw = xfers[i].flags & I2C_M_RD;
		cmd->in = cmd->rnw ? xfers[i].buf : शून्य;
		cmd->out = cmd->rnw ? शून्य : xfers[i].buf;
		cmd->len = xfers[i].len;
		cmd->पढ़ो_len = cmd->rnw ? xfers[i].len : 0;
		cmd->जारीd = (i + 1 < nxfers);
	पूर्ण

	svc_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		svc_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	svc_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_request_ibi(काष्ठा i3c_dev_desc *dev,
				      स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (dev->ibi->max_payload_len > SVC_I3C_FIFO_SIZE) अणु
		dev_err(master->dev, "IBI max payload %d should be < %d\n",
			dev->ibi->max_payload_len, SVC_I3C_FIFO_SIZE);
		वापस -दुस्फल;
	पूर्ण

	data->ibi_pool = i3c_generic_ibi_alloc_pool(dev, req);
	अगर (IS_ERR(data->ibi_pool))
		वापस PTR_ERR(data->ibi_pool);

	spin_lock_irqsave(&master->ibi.lock, flags);
	क्रम (i = 0; i < master->ibi.num_slots; i++) अणु
		अगर (!master->ibi.slots[i]) अणु
			data->ibi = i;
			master->ibi.slots[i] = dev;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	अगर (i < master->ibi.num_slots)
		वापस 0;

	i3c_generic_ibi_मुक्त_pool(data->ibi_pool);
	data->ibi_pool = शून्य;

	वापस -ENOSPC;
पूर्ण

अटल व्योम svc_i3c_master_मुक्त_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा svc_i3c_master *master = to_svc_i3c_master(m);
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->ibi.lock, flags);
	master->ibi.slots[data->ibi] = शून्य;
	data->ibi = -1;
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	i3c_generic_ibi_मुक्त_pool(data->ibi_pool);
पूर्ण

अटल पूर्णांक svc_i3c_master_enable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);

	वापस i3c_master_enec_locked(m, dev->info.dyn_addr, I3C_CCC_EVENT_SIR);
पूर्ण

अटल पूर्णांक svc_i3c_master_disable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);

	वापस i3c_master_disec_locked(m, dev->info.dyn_addr, I3C_CCC_EVENT_SIR);
पूर्ण

अटल व्योम svc_i3c_master_recycle_ibi_slot(काष्ठा i3c_dev_desc *dev,
					    काष्ठा i3c_ibi_slot *slot)
अणु
	काष्ठा svc_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	i3c_generic_ibi_recycle_slot(data->ibi_pool, slot);
पूर्ण

अटल स्थिर काष्ठा i3c_master_controller_ops svc_i3c_master_ops = अणु
	.bus_init = svc_i3c_master_bus_init,
	.bus_cleanup = svc_i3c_master_bus_cleanup,
	.attach_i3c_dev = svc_i3c_master_attach_i3c_dev,
	.detach_i3c_dev = svc_i3c_master_detach_i3c_dev,
	.reattach_i3c_dev = svc_i3c_master_reattach_i3c_dev,
	.attach_i2c_dev = svc_i3c_master_attach_i2c_dev,
	.detach_i2c_dev = svc_i3c_master_detach_i2c_dev,
	.करो_daa = svc_i3c_master_करो_daa,
	.supports_ccc_cmd = svc_i3c_master_supports_ccc_cmd,
	.send_ccc_cmd = svc_i3c_master_send_ccc_cmd,
	.priv_xfers = svc_i3c_master_priv_xfers,
	.i2c_xfers = svc_i3c_master_i2c_xfers,
	.request_ibi = svc_i3c_master_request_ibi,
	.मुक्त_ibi = svc_i3c_master_मुक्त_ibi,
	.recycle_ibi_slot = svc_i3c_master_recycle_ibi_slot,
	.enable_ibi = svc_i3c_master_enable_ibi,
	.disable_ibi = svc_i3c_master_disable_ibi,
पूर्ण;

अटल व्योम svc_i3c_master_reset(काष्ठा svc_i3c_master *master)
अणु
	u32 reg;

	/* Clear pending warnings */
	ग_लिखोl(पढ़ोl(master->regs + SVC_I3C_MERRWARN),
	       master->regs + SVC_I3C_MERRWARN);

	/* Set RX and TX tigger levels, flush FIFOs */
	reg = SVC_I3C_MDATACTRL_FLUSHTB |
	      SVC_I3C_MDATACTRL_FLUSHRB |
	      SVC_I3C_MDATACTRL_UNLOCK_TRIG |
	      SVC_I3C_MDATACTRL_TXTRIG_FIFO_NOT_FULL |
	      SVC_I3C_MDATACTRL_RXTRIG_FIFO_NOT_EMPTY;
	ग_लिखोl(reg, master->regs + SVC_I3C_MDATACTRL);

	svc_i3c_master_disable_पूर्णांकerrupts(master);
पूर्ण

अटल पूर्णांक svc_i3c_master_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा svc_i3c_master *master;
	पूर्णांक ret;

	master = devm_kzalloc(dev, माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(master->regs))
		वापस PTR_ERR(master->regs);

	master->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(master->pclk))
		वापस PTR_ERR(master->pclk);

	master->fclk = devm_clk_get(dev, "fast_clk");
	अगर (IS_ERR(master->fclk))
		वापस PTR_ERR(master->fclk);

	master->sclk = devm_clk_get(dev, "slow_clk");
	अगर (IS_ERR(master->sclk))
		वापस PTR_ERR(master->sclk);

	master->irq = platक्रमm_get_irq(pdev, 0);
	अगर (master->irq <= 0)
		वापस -ENOENT;

	master->dev = dev;

	svc_i3c_master_reset(master);

	ret = clk_prepare_enable(master->pclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(master->fclk);
	अगर (ret)
		जाओ err_disable_pclk;

	ret = clk_prepare_enable(master->sclk);
	अगर (ret)
		जाओ err_disable_fclk;

	INIT_WORK(&master->hj_work, svc_i3c_master_hj_work);
	INIT_WORK(&master->ibi_work, svc_i3c_master_ibi_work);
	ret = devm_request_irq(dev, master->irq, svc_i3c_master_irq_handler,
			       IRQF_NO_SUSPEND, "svc-i3c-irq", master);
	अगर (ret)
		जाओ err_disable_sclk;

	master->मुक्त_slots = GENMASK(SVC_I3C_MAX_DEVS - 1, 0);

	spin_lock_init(&master->xferqueue.lock);
	INIT_LIST_HEAD(&master->xferqueue.list);

	spin_lock_init(&master->ibi.lock);
	master->ibi.num_slots = SVC_I3C_MAX_DEVS;
	master->ibi.slots = devm_kसुस्मृति(&pdev->dev, master->ibi.num_slots,
					 माप(*master->ibi.slots),
					 GFP_KERNEL);
	अगर (!master->ibi.slots) अणु
		ret = -ENOMEM;
		जाओ err_disable_sclk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);

	/* Register the master */
	ret = i3c_master_रेजिस्टर(&master->base, &pdev->dev,
				  &svc_i3c_master_ops, false);
	अगर (ret)
		जाओ err_disable_sclk;

	वापस 0;

err_disable_sclk:
	clk_disable_unprepare(master->sclk);

err_disable_fclk:
	clk_disable_unprepare(master->fclk);

err_disable_pclk:
	clk_disable_unprepare(master->pclk);

	वापस ret;
पूर्ण

अटल पूर्णांक svc_i3c_master_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा svc_i3c_master *master = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = i3c_master_unरेजिस्टर(&master->base);
	अगर (ret)
		वापस ret;

	मुक्त_irq(master->irq, master);
	clk_disable_unprepare(master->pclk);
	clk_disable_unprepare(master->fclk);
	clk_disable_unprepare(master->sclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id svc_i3c_master_of_match_tbl[] = अणु
	अणु .compatible = "silvaco,i3c-master" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver svc_i3c_master = अणु
	.probe = svc_i3c_master_probe,
	.हटाओ = svc_i3c_master_हटाओ,
	.driver = अणु
		.name = "silvaco-i3c-master",
		.of_match_table = svc_i3c_master_of_match_tbl,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(svc_i3c_master);

MODULE_AUTHOR("Conor Culhane <conor.culhane@silvaco.com>");
MODULE_AUTHOR("Miquel Raynal <miquel.raynal@bootlin.com>");
MODULE_DESCRIPTION("Silvaco dual-role I3C master driver");
MODULE_LICENSE("GPL v2");
