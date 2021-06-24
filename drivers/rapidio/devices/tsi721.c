<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO mport driver क्रम Tsi721 PCIExpress-to-SRIO bridge
 *
 * Copyright 2011 Integrated Device Technology, Inc.
 * Alexandre Bounine <alexandre.bounine@idt.com>
 * Chul Kim <chul.kim@idt.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/delay.h>

#समावेश "tsi721.h"

#अगर_घोषित DEBUG
u32 tsi_dbg_level;
module_param_named(dbg_level, tsi_dbg_level, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(dbg_level, "Debugging output level (default 0 = none)");
#पूर्ण_अगर

अटल पूर्णांक pcie_mrrs = -1;
module_param(pcie_mrrs, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_mrrs, "PCIe MRRS override value (0...5)");

अटल u8 mbox_sel = 0x0f;
module_param(mbox_sel, byte, S_IRUGO);
MODULE_PARM_DESC(mbox_sel,
		 "RIO Messaging MBOX Selection Mask (default: 0x0f = all)");

अटल DEFINE_SPINLOCK(tsi721_मुख्यt_lock);

अटल व्योम tsi721_omsg_handler(काष्ठा tsi721_device *priv, पूर्णांक ch);
अटल व्योम tsi721_imsg_handler(काष्ठा tsi721_device *priv, पूर्णांक ch);

/**
 * tsi721_lcपढ़ो - पढ़ो from local SREP config space
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @data: Value to be पढ़ो पूर्णांकo
 *
 * Generates a local SREP space पढ़ो. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक tsi721_lcपढ़ो(काष्ठा rio_mport *mport, पूर्णांक index, u32 offset,
			 पूर्णांक len, u32 *data)
अणु
	काष्ठा tsi721_device *priv = mport->priv;

	अगर (len != माप(u32))
		वापस -EINVAL; /* only 32-bit access is supported */

	*data = ioपढ़ो32(priv->regs + offset);

	वापस 0;
पूर्ण

/**
 * tsi721_lcग_लिखो - ग_लिखो पूर्णांकo local SREP config space
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @data: Value to be written
 *
 * Generates a local ग_लिखो पूर्णांकo SREP configuration space. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक tsi721_lcग_लिखो(काष्ठा rio_mport *mport, पूर्णांक index, u32 offset,
			  पूर्णांक len, u32 data)
अणु
	काष्ठा tsi721_device *priv = mport->priv;

	अगर (len != माप(u32))
		वापस -EINVAL; /* only 32-bit access is supported */

	ioग_लिखो32(data, priv->regs + offset);

	वापस 0;
पूर्ण

/**
 * tsi721_मुख्यt_dma - Helper function to generate RapidIO मुख्यtenance
 *                    transactions using designated Tsi721 DMA channel.
 * @priv: poपूर्णांकer to tsi721 निजी data
 * @sys_size: RapdiIO transport प्रणाली size
 * @destid: Destination ID of transaction
 * @hopcount: Number of hops to target device
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @data: Location to be पढ़ो from or ग_लिखो पूर्णांकo
 * @करो_wr: Operation flag (1 == MAINT_WR)
 *
 * Generates a RapidIO मुख्यtenance transaction (Read or Write).
 * Returns %0 on success and %-EINVAL or %-EFAULT on failure.
 */
अटल पूर्णांक tsi721_मुख्यt_dma(काष्ठा tsi721_device *priv, u32 sys_size,
			u16 destid, u8 hopcount, u32 offset, पूर्णांक len,
			u32 *data, पूर्णांक करो_wr)
अणु
	व्योम __iomem *regs = priv->regs + TSI721_DMAC_BASE(priv->mdma.ch_id);
	काष्ठा tsi721_dma_desc *bd_ptr;
	u32 rd_count, swr_ptr, ch_stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err = 0;
	u32 op = करो_wr ? MAINT_WR : MAINT_RD;

	अगर (offset > (RIO_MAINT_SPACE_SZ - len) || (len != माप(u32)))
		वापस -EINVAL;

	spin_lock_irqsave(&tsi721_मुख्यt_lock, flags);

	bd_ptr = priv->mdma.bd_base;

	rd_count = ioपढ़ो32(regs + TSI721_DMAC_DRDCNT);

	/* Initialize DMA descriptor */
	bd_ptr[0].type_id = cpu_to_le32((DTYPE2 << 29) | (op << 19) | destid);
	bd_ptr[0].bcount = cpu_to_le32((sys_size << 26) | 0x04);
	bd_ptr[0].raddr_lo = cpu_to_le32((hopcount << 24) | offset);
	bd_ptr[0].raddr_hi = 0;
	अगर (करो_wr)
		bd_ptr[0].data[0] = cpu_to_be32p(data);
	अन्यथा
		bd_ptr[0].data[0] = 0xffffffff;

	mb();

	/* Start DMA operation */
	ioग_लिखो32(rd_count + 2,	regs + TSI721_DMAC_DWRCNT);
	ioपढ़ो32(regs + TSI721_DMAC_DWRCNT);
	i = 0;

	/* Wait until DMA transfer is finished */
	जबतक ((ch_stat = ioपढ़ो32(regs + TSI721_DMAC_STS))
							& TSI721_DMAC_STS_RUN) अणु
		udelay(1);
		अगर (++i >= 5000000) अणु
			tsi_debug(MAINT, &priv->pdev->dev,
				"DMA[%d] read timeout ch_status=%x",
				priv->mdma.ch_id, ch_stat);
			अगर (!करो_wr)
				*data = 0xffffffff;
			err = -EIO;
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (ch_stat & TSI721_DMAC_STS_ABORT) अणु
		/* If DMA operation पातed due to error,
		 * reinitialize DMA channel
		 */
		tsi_debug(MAINT, &priv->pdev->dev, "DMA ABORT ch_stat=%x",
			  ch_stat);
		tsi_debug(MAINT, &priv->pdev->dev,
			  "OP=%d : destid=%x hc=%x off=%x",
			  करो_wr ? MAINT_WR : MAINT_RD,
			  destid, hopcount, offset);
		ioग_लिखो32(TSI721_DMAC_INT_ALL, regs + TSI721_DMAC_INT);
		ioग_लिखो32(TSI721_DMAC_CTL_INIT, regs + TSI721_DMAC_CTL);
		udelay(10);
		ioग_लिखो32(0, regs + TSI721_DMAC_DWRCNT);
		udelay(1);
		अगर (!करो_wr)
			*data = 0xffffffff;
		err = -EIO;
		जाओ err_out;
	पूर्ण

	अगर (!करो_wr)
		*data = be32_to_cpu(bd_ptr[0].data[0]);

	/*
	 * Update descriptor status FIFO RD poपूर्णांकer.
	 * NOTE: Skipping check and clear FIFO entries because we are रुकोing
	 * क्रम transfer to be completed.
	 */
	swr_ptr = ioपढ़ो32(regs + TSI721_DMAC_DSWP);
	ioग_लिखो32(swr_ptr, regs + TSI721_DMAC_DSRP);

err_out:
	spin_unlock_irqrestore(&tsi721_मुख्यt_lock, flags);

	वापस err;
पूर्ण

/**
 * tsi721_cपढ़ो_dma - Generate a RapidIO मुख्यtenance पढ़ो transaction
 *                    using Tsi721 BDMA engine.
 * @mport: RapidIO master port control काष्ठाure
 * @index: ID of RapdiIO पूर्णांकerface
 * @destid: Destination ID of transaction
 * @hopcount: Number of hops to target device
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @val: Location to be पढ़ो पूर्णांकo
 *
 * Generates a RapidIO मुख्यtenance पढ़ो transaction.
 * Returns %0 on success and %-EINVAL or %-EFAULT on failure.
 */
अटल पूर्णांक tsi721_cपढ़ो_dma(काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			u8 hopcount, u32 offset, पूर्णांक len, u32 *data)
अणु
	काष्ठा tsi721_device *priv = mport->priv;

	वापस tsi721_मुख्यt_dma(priv, mport->sys_size, destid, hopcount,
				offset, len, data, 0);
पूर्ण

/**
 * tsi721_cग_लिखो_dma - Generate a RapidIO मुख्यtenance ग_लिखो transaction
 *                     using Tsi721 BDMA engine
 * @mport: RapidIO master port control काष्ठाure
 * @index: ID of RapdiIO पूर्णांकerface
 * @destid: Destination ID of transaction
 * @hopcount: Number of hops to target device
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @val: Value to be written
 *
 * Generates a RapidIO मुख्यtenance ग_लिखो transaction.
 * Returns %0 on success and %-EINVAL or %-EFAULT on failure.
 */
अटल पूर्णांक tsi721_cग_लिखो_dma(काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			 u8 hopcount, u32 offset, पूर्णांक len, u32 data)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 temp = data;

	वापस tsi721_मुख्यt_dma(priv, mport->sys_size, destid, hopcount,
				offset, len, &temp, 1);
पूर्ण

/**
 * tsi721_pw_handler - Tsi721 inbound port-ग_लिखो पूर्णांकerrupt handler
 * @priv:  tsi721 device निजी काष्ठाure
 *
 * Handles inbound port-ग_लिखो पूर्णांकerrupts. Copies PW message from an पूर्णांकernal
 * buffer पूर्णांकo PW message FIFO and schedules deferred routine to process
 * queued messages.
 */
अटल पूर्णांक
tsi721_pw_handler(काष्ठा tsi721_device *priv)
अणु
	u32 pw_stat;
	u32 pw_buf[TSI721_RIO_PW_MSG_SIZE/माप(u32)];


	pw_stat = ioपढ़ो32(priv->regs + TSI721_RIO_PW_RX_STAT);

	अगर (pw_stat & TSI721_RIO_PW_RX_STAT_PW_VAL) अणु
		pw_buf[0] = ioपढ़ो32(priv->regs + TSI721_RIO_PW_RX_CAPT(0));
		pw_buf[1] = ioपढ़ो32(priv->regs + TSI721_RIO_PW_RX_CAPT(1));
		pw_buf[2] = ioपढ़ो32(priv->regs + TSI721_RIO_PW_RX_CAPT(2));
		pw_buf[3] = ioपढ़ो32(priv->regs + TSI721_RIO_PW_RX_CAPT(3));

		/* Queue PW message (अगर there is room in FIFO),
		 * otherwise discard it.
		 */
		spin_lock(&priv->pw_fअगरo_lock);
		अगर (kfअगरo_avail(&priv->pw_fअगरo) >= TSI721_RIO_PW_MSG_SIZE)
			kfअगरo_in(&priv->pw_fअगरo, pw_buf,
						TSI721_RIO_PW_MSG_SIZE);
		अन्यथा
			priv->pw_discard_count++;
		spin_unlock(&priv->pw_fअगरo_lock);
	पूर्ण

	/* Clear pending PW पूर्णांकerrupts */
	ioग_लिखो32(TSI721_RIO_PW_RX_STAT_PW_DISC | TSI721_RIO_PW_RX_STAT_PW_VAL,
		  priv->regs + TSI721_RIO_PW_RX_STAT);

	schedule_work(&priv->pw_work);

	वापस 0;
पूर्ण

अटल व्योम tsi721_pw_dpc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tsi721_device *priv = container_of(work, काष्ठा tsi721_device,
						    pw_work);
	जोड़ rio_pw_msg pwmsg;

	/*
	 * Process port-ग_लिखो messages
	 */
	जबतक (kfअगरo_out_spinlocked(&priv->pw_fअगरo, (अचिन्हित अक्षर *)&pwmsg,
			 TSI721_RIO_PW_MSG_SIZE, &priv->pw_fअगरo_lock)) अणु
		/* Pass the port-ग_लिखो message to RIO core क्रम processing */
		rio_inb_pग_लिखो_handler(&priv->mport, &pwmsg);
	पूर्ण
पूर्ण

/**
 * tsi721_pw_enable - enable/disable port-ग_लिखो पूर्णांकerface init
 * @mport: Master port implementing the port ग_लिखो unit
 * @enable:    1=enable; 0=disable port-ग_लिखो message handling
 */
अटल पूर्णांक tsi721_pw_enable(काष्ठा rio_mport *mport, पूर्णांक enable)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 rval;

	rval = ioपढ़ो32(priv->regs + TSI721_RIO_EM_INT_ENABLE);

	अगर (enable)
		rval |= TSI721_RIO_EM_INT_ENABLE_PW_RX;
	अन्यथा
		rval &= ~TSI721_RIO_EM_INT_ENABLE_PW_RX;

	/* Clear pending PW पूर्णांकerrupts */
	ioग_लिखो32(TSI721_RIO_PW_RX_STAT_PW_DISC | TSI721_RIO_PW_RX_STAT_PW_VAL,
		  priv->regs + TSI721_RIO_PW_RX_STAT);
	/* Update enable bits */
	ioग_लिखो32(rval, priv->regs + TSI721_RIO_EM_INT_ENABLE);

	वापस 0;
पूर्ण

/**
 * tsi721_dsend - Send a RapidIO करोorbell
 * @mport: RapidIO master port info
 * @index: ID of RapidIO पूर्णांकerface
 * @destid: Destination ID of target device
 * @data: 16-bit info field of RapidIO करोorbell
 *
 * Sends a RapidIO करोorbell message. Always वापसs %0.
 */
अटल पूर्णांक tsi721_dsend(काष्ठा rio_mport *mport, पूर्णांक index,
			u16 destid, u16 data)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 offset;

	offset = (((mport->sys_size) ? RIO_TT_CODE_16 : RIO_TT_CODE_8) << 18) |
		 (destid << 2);

	tsi_debug(DBELL, &priv->pdev->dev,
		  "Send Doorbell 0x%04x to destID 0x%x", data, destid);
	ioग_लिखो16be(data, priv->odb_base + offset);

	वापस 0;
पूर्ण

/**
 * tsi721_dbell_handler - Tsi721 करोorbell पूर्णांकerrupt handler
 * @priv: tsi721 device-specअगरic data काष्ठाure
 *
 * Handles inbound करोorbell पूर्णांकerrupts. Copies करोorbell entry from an पूर्णांकernal
 * buffer पूर्णांकo DB message FIFO and schedules deferred  routine to process
 * queued DBs.
 */
अटल पूर्णांक
tsi721_dbell_handler(काष्ठा tsi721_device *priv)
अणु
	u32 regval;

	/* Disable IDB पूर्णांकerrupts */
	regval = ioपढ़ो32(priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));
	regval &= ~TSI721_SR_CHINT_IDBQRCV;
	ioग_लिखो32(regval,
		priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));

	schedule_work(&priv->idb_work);

	वापस 0;
पूर्ण

अटल व्योम tsi721_db_dpc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tsi721_device *priv = container_of(work, काष्ठा tsi721_device,
						    idb_work);
	काष्ठा rio_mport *mport;
	काष्ठा rio_dbell *dbell;
	पूर्णांक found = 0;
	u32 wr_ptr, rd_ptr;
	u64 *idb_entry;
	u32 regval;
	जोड़ अणु
		u64 msg;
		u8  bytes[8];
	पूर्ण idb;

	/*
	 * Process queued inbound करोorbells
	 */
	mport = &priv->mport;

	wr_ptr = ioपढ़ो32(priv->regs + TSI721_IDQ_WP(IDB_QUEUE)) % IDB_QSIZE;
	rd_ptr = ioपढ़ो32(priv->regs + TSI721_IDQ_RP(IDB_QUEUE)) % IDB_QSIZE;

	जबतक (wr_ptr != rd_ptr) अणु
		idb_entry = (u64 *)(priv->idb_base +
					(TSI721_IDB_ENTRY_SIZE * rd_ptr));
		rd_ptr++;
		rd_ptr %= IDB_QSIZE;
		idb.msg = *idb_entry;
		*idb_entry = 0;

		/* Process one करोorbell */
		list_क्रम_each_entry(dbell, &mport->dbells, node) अणु
			अगर ((dbell->res->start <= DBELL_INF(idb.bytes)) &&
			    (dbell->res->end >= DBELL_INF(idb.bytes))) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found) अणु
			dbell->dinb(mport, dbell->dev_id, DBELL_SID(idb.bytes),
				    DBELL_TID(idb.bytes), DBELL_INF(idb.bytes));
		पूर्ण अन्यथा अणु
			tsi_debug(DBELL, &priv->pdev->dev,
				  "spurious IDB sid %2.2x tid %2.2x info %4.4x",
				  DBELL_SID(idb.bytes), DBELL_TID(idb.bytes),
				  DBELL_INF(idb.bytes));
		पूर्ण

		wr_ptr = ioपढ़ो32(priv->regs +
				  TSI721_IDQ_WP(IDB_QUEUE)) % IDB_QSIZE;
	पूर्ण

	ioग_लिखो32(rd_ptr & (IDB_QSIZE - 1),
		priv->regs + TSI721_IDQ_RP(IDB_QUEUE));

	/* Re-enable IDB पूर्णांकerrupts */
	regval = ioपढ़ो32(priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));
	regval |= TSI721_SR_CHINT_IDBQRCV;
	ioग_लिखो32(regval,
		priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));

	wr_ptr = ioपढ़ो32(priv->regs + TSI721_IDQ_WP(IDB_QUEUE)) % IDB_QSIZE;
	अगर (wr_ptr != rd_ptr)
		schedule_work(&priv->idb_work);
पूर्ण

/**
 * tsi721_irqhandler - Tsi721 पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (tsi721_device काष्ठाure)
 *
 * Handles Tsi721 पूर्णांकerrupts संकेतed using MSI and INTA. Checks reported
 * पूर्णांकerrupt events and calls an event-specअगरic handler(s).
 */
अटल irqवापस_t tsi721_irqhandler(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_device *priv = (काष्ठा tsi721_device *)ptr;
	u32 dev_पूर्णांक;
	u32 dev_ch_पूर्णांक;
	u32 पूर्णांकval;
	u32 ch_पूर्णांकe;

	/* For MSI mode disable all device-level पूर्णांकerrupts */
	अगर (priv->flags & TSI721_USING_MSI)
		ioग_लिखो32(0, priv->regs + TSI721_DEV_INTE);

	dev_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_DEV_INT);
	अगर (!dev_पूर्णांक)
		वापस IRQ_NONE;

	dev_ch_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INT);

	अगर (dev_पूर्णांक & TSI721_DEV_INT_SR2PC_CH) अणु
		/* Service SR2PC Channel पूर्णांकerrupts */
		अगर (dev_ch_पूर्णांक & TSI721_INT_SR2PC_CHAN(IDB_QUEUE)) अणु
			/* Service Inbound Doorbell पूर्णांकerrupt */
			पूर्णांकval = ioपढ़ो32(priv->regs +
						TSI721_SR_CHINT(IDB_QUEUE));
			अगर (पूर्णांकval & TSI721_SR_CHINT_IDBQRCV)
				tsi721_dbell_handler(priv);
			अन्यथा
				tsi_info(&priv->pdev->dev,
					"Unsupported SR_CH_INT %x", पूर्णांकval);

			/* Clear पूर्णांकerrupts */
			ioग_लिखो32(पूर्णांकval,
				priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
			ioपढ़ो32(priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
		पूर्ण
	पूर्ण

	अगर (dev_पूर्णांक & TSI721_DEV_INT_SMSG_CH) अणु
		पूर्णांक ch;

		/*
		 * Service channel पूर्णांकerrupts from Messaging Engine
		 */

		अगर (dev_ch_पूर्णांक & TSI721_INT_IMSG_CHAN_M) अणु /* Inbound Msg */
			/* Disable संकेतed OB MSG Channel पूर्णांकerrupts */
			ch_पूर्णांकe = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
			ch_पूर्णांकe &= ~(dev_ch_पूर्णांक & TSI721_INT_IMSG_CHAN_M);
			ioग_लिखो32(ch_पूर्णांकe, priv->regs + TSI721_DEV_CHAN_INTE);

			/*
			 * Process Inbound Message पूर्णांकerrupt क्रम each MBOX
			 */
			क्रम (ch = 4; ch < RIO_MAX_MBOX + 4; ch++) अणु
				अगर (!(dev_ch_पूर्णांक & TSI721_INT_IMSG_CHAN(ch)))
					जारी;
				tsi721_imsg_handler(priv, ch);
			पूर्ण
		पूर्ण

		अगर (dev_ch_पूर्णांक & TSI721_INT_OMSG_CHAN_M) अणु /* Outbound Msg */
			/* Disable संकेतed OB MSG Channel पूर्णांकerrupts */
			ch_पूर्णांकe = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
			ch_पूर्णांकe &= ~(dev_ch_पूर्णांक & TSI721_INT_OMSG_CHAN_M);
			ioग_लिखो32(ch_पूर्णांकe, priv->regs + TSI721_DEV_CHAN_INTE);

			/*
			 * Process Outbound Message पूर्णांकerrupts क्रम each MBOX
			 */

			क्रम (ch = 0; ch < RIO_MAX_MBOX; ch++) अणु
				अगर (!(dev_ch_पूर्णांक & TSI721_INT_OMSG_CHAN(ch)))
					जारी;
				tsi721_omsg_handler(priv, ch);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev_पूर्णांक & TSI721_DEV_INT_SRIO) अणु
		/* Service SRIO MAC पूर्णांकerrupts */
		पूर्णांकval = ioपढ़ो32(priv->regs + TSI721_RIO_EM_INT_STAT);
		अगर (पूर्णांकval & TSI721_RIO_EM_INT_STAT_PW_RX)
			tsi721_pw_handler(priv);
	पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	अगर (dev_पूर्णांक & TSI721_DEV_INT_BDMA_CH) अणु
		पूर्णांक ch;

		अगर (dev_ch_पूर्णांक & TSI721_INT_BDMA_CHAN_M) अणु
			tsi_debug(DMA, &priv->pdev->dev,
				  "IRQ from DMA channel 0x%08x", dev_ch_पूर्णांक);

			क्रम (ch = 0; ch < TSI721_DMA_MAXCH; ch++) अणु
				अगर (!(dev_ch_पूर्णांक & TSI721_INT_BDMA_CHAN(ch)))
					जारी;
				tsi721_bdma_handler(&priv->bdma[ch]);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* For MSI mode re-enable device-level पूर्णांकerrupts */
	अगर (priv->flags & TSI721_USING_MSI) अणु
		dev_पूर्णांक = TSI721_DEV_INT_SR2PC_CH | TSI721_DEV_INT_SRIO |
			TSI721_DEV_INT_SMSG_CH | TSI721_DEV_INT_BDMA_CH;
		ioग_लिखो32(dev_पूर्णांक, priv->regs + TSI721_DEV_INTE);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tsi721_पूर्णांकerrupts_init(काष्ठा tsi721_device *priv)
अणु
	u32 पूर्णांकr;

	/* Enable IDB पूर्णांकerrupts */
	ioग_लिखो32(TSI721_SR_CHINT_ALL,
		priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
	ioग_लिखो32(TSI721_SR_CHINT_IDBQRCV,
		priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));

	/* Enable SRIO MAC पूर्णांकerrupts */
	ioग_लिखो32(TSI721_RIO_EM_DEV_INT_EN_INT,
		priv->regs + TSI721_RIO_EM_DEV_INT_EN);

	/* Enable पूर्णांकerrupts from channels in use */
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	पूर्णांकr = TSI721_INT_SR2PC_CHAN(IDB_QUEUE) |
		(TSI721_INT_BDMA_CHAN_M &
		 ~TSI721_INT_BDMA_CHAN(TSI721_DMACH_MAINT));
#अन्यथा
	पूर्णांकr = TSI721_INT_SR2PC_CHAN(IDB_QUEUE);
#पूर्ण_अगर
	ioग_लिखो32(पूर्णांकr,	priv->regs + TSI721_DEV_CHAN_INTE);

	अगर (priv->flags & TSI721_USING_MSIX)
		पूर्णांकr = TSI721_DEV_INT_SRIO;
	अन्यथा
		पूर्णांकr = TSI721_DEV_INT_SR2PC_CH | TSI721_DEV_INT_SRIO |
			TSI721_DEV_INT_SMSG_CH | TSI721_DEV_INT_BDMA_CH;

	ioग_लिखो32(पूर्णांकr, priv->regs + TSI721_DEV_INTE);
	ioपढ़ो32(priv->regs + TSI721_DEV_INTE);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
/**
 * tsi721_omsg_msix - MSI-X पूर्णांकerrupt handler क्रम outbound messaging
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (tsi721_device काष्ठाure)
 *
 * Handles outbound messaging पूर्णांकerrupts संकेतed using MSI-X.
 */
अटल irqवापस_t tsi721_omsg_msix(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_device *priv = (काष्ठा tsi721_device *)ptr;
	पूर्णांक mbox;

	mbox = (irq - priv->msix[TSI721_VECT_OMB0_DONE].vector) % RIO_MAX_MBOX;
	tsi721_omsg_handler(priv, mbox);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * tsi721_imsg_msix - MSI-X पूर्णांकerrupt handler क्रम inbound messaging
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (tsi721_device काष्ठाure)
 *
 * Handles inbound messaging पूर्णांकerrupts संकेतed using MSI-X.
 */
अटल irqवापस_t tsi721_imsg_msix(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_device *priv = (काष्ठा tsi721_device *)ptr;
	पूर्णांक mbox;

	mbox = (irq - priv->msix[TSI721_VECT_IMB0_RCV].vector) % RIO_MAX_MBOX;
	tsi721_imsg_handler(priv, mbox + 4);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * tsi721_srio_msix - Tsi721 MSI-X SRIO MAC पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (tsi721_device काष्ठाure)
 *
 * Handles Tsi721 पूर्णांकerrupts from SRIO MAC.
 */
अटल irqवापस_t tsi721_srio_msix(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_device *priv = (काष्ठा tsi721_device *)ptr;
	u32 srio_पूर्णांक;

	/* Service SRIO MAC पूर्णांकerrupts */
	srio_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_RIO_EM_INT_STAT);
	अगर (srio_पूर्णांक & TSI721_RIO_EM_INT_STAT_PW_RX)
		tsi721_pw_handler(priv);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * tsi721_sr2pc_ch_msix - Tsi721 MSI-X SR2PC Channel पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (tsi721_device काष्ठाure)
 *
 * Handles Tsi721 पूर्णांकerrupts from SR2PC Channel.
 * NOTE: At this moment services only one SR2PC channel associated with inbound
 * करोorbells.
 */
अटल irqवापस_t tsi721_sr2pc_ch_msix(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_device *priv = (काष्ठा tsi721_device *)ptr;
	u32 sr_ch_पूर्णांक;

	/* Service Inbound DB पूर्णांकerrupt from SR2PC channel */
	sr_ch_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
	अगर (sr_ch_पूर्णांक & TSI721_SR_CHINT_IDBQRCV)
		tsi721_dbell_handler(priv);

	/* Clear पूर्णांकerrupts */
	ioग_लिखो32(sr_ch_पूर्णांक, priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
	/* Read back to ensure that पूर्णांकerrupt was cleared */
	sr_ch_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_SR_CHINT(IDB_QUEUE));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * tsi721_request_msix - रेजिस्टर पूर्णांकerrupt service क्रम MSI-X mode.
 * @priv: tsi721 device-specअगरic data काष्ठाure
 *
 * Registers MSI-X पूर्णांकerrupt service routines क्रम पूर्णांकerrupts that are active
 * immediately after mport initialization. Messaging पूर्णांकerrupt service routines
 * should be रेजिस्टरed during corresponding खोलो requests.
 */
अटल पूर्णांक tsi721_request_msix(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक err = 0;

	err = request_irq(priv->msix[TSI721_VECT_IDB].vector,
			tsi721_sr2pc_ch_msix, 0,
			priv->msix[TSI721_VECT_IDB].irq_name, (व्योम *)priv);
	अगर (err)
		वापस err;

	err = request_irq(priv->msix[TSI721_VECT_PWRX].vector,
			tsi721_srio_msix, 0,
			priv->msix[TSI721_VECT_PWRX].irq_name, (व्योम *)priv);
	अगर (err) अणु
		मुक्त_irq(priv->msix[TSI721_VECT_IDB].vector, (व्योम *)priv);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tsi721_enable_msix - Attempts to enable MSI-X support क्रम Tsi721.
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Configures MSI-X support क्रम Tsi721. Supports only an exact number
 * of requested vectors.
 */
अटल पूर्णांक tsi721_enable_msix(काष्ठा tsi721_device *priv)
अणु
	काष्ठा msix_entry entries[TSI721_VECT_MAX];
	पूर्णांक err;
	पूर्णांक i;

	entries[TSI721_VECT_IDB].entry = TSI721_MSIX_SR2PC_IDBQ_RCV(IDB_QUEUE);
	entries[TSI721_VECT_PWRX].entry = TSI721_MSIX_SRIO_MAC_INT;

	/*
	 * Initialize MSI-X entries क्रम Messaging Engine:
	 * this driver supports four RIO mailboxes (inbound and outbound)
	 * NOTE: Inbound message MBOX 0...4 use IB channels 4...7. Thereक्रमe
	 * offset +4 is added to IB MBOX number.
	 */
	क्रम (i = 0; i < RIO_MAX_MBOX; i++) अणु
		entries[TSI721_VECT_IMB0_RCV + i].entry =
					TSI721_MSIX_IMSG_DQ_RCV(i + 4);
		entries[TSI721_VECT_IMB0_INT + i].entry =
					TSI721_MSIX_IMSG_INT(i + 4);
		entries[TSI721_VECT_OMB0_DONE + i].entry =
					TSI721_MSIX_OMSG_DONE(i);
		entries[TSI721_VECT_OMB0_INT + i].entry =
					TSI721_MSIX_OMSG_INT(i);
	पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	/*
	 * Initialize MSI-X entries क्रम Block DMA Engine:
	 * this driver supports XXX DMA channels
	 * (one is reserved क्रम SRIO मुख्यtenance transactions)
	 */
	क्रम (i = 0; i < TSI721_DMA_CHNUM; i++) अणु
		entries[TSI721_VECT_DMA0_DONE + i].entry =
					TSI721_MSIX_DMACH_DONE(i);
		entries[TSI721_VECT_DMA0_INT + i].entry =
					TSI721_MSIX_DMACH_INT(i);
	पूर्ण
#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

	err = pci_enable_msix_exact(priv->pdev, entries, ARRAY_SIZE(entries));
	अगर (err) अणु
		tsi_err(&priv->pdev->dev,
			"Failed to enable MSI-X (err=%d)", err);
		वापस err;
	पूर्ण

	/*
	 * Copy MSI-X vector inक्रमmation पूर्णांकo tsi721 निजी काष्ठाure
	 */
	priv->msix[TSI721_VECT_IDB].vector = entries[TSI721_VECT_IDB].vector;
	snम_लिखो(priv->msix[TSI721_VECT_IDB].irq_name, IRQ_DEVICE_NAME_MAX,
		 DRV_NAME "-idb@pci:%s", pci_name(priv->pdev));
	priv->msix[TSI721_VECT_PWRX].vector = entries[TSI721_VECT_PWRX].vector;
	snम_लिखो(priv->msix[TSI721_VECT_PWRX].irq_name, IRQ_DEVICE_NAME_MAX,
		 DRV_NAME "-pwrx@pci:%s", pci_name(priv->pdev));

	क्रम (i = 0; i < RIO_MAX_MBOX; i++) अणु
		priv->msix[TSI721_VECT_IMB0_RCV + i].vector =
				entries[TSI721_VECT_IMB0_RCV + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_IMB0_RCV + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-imbr%d@pci:%s",
			 i, pci_name(priv->pdev));

		priv->msix[TSI721_VECT_IMB0_INT + i].vector =
				entries[TSI721_VECT_IMB0_INT + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_IMB0_INT + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-imbi%d@pci:%s",
			 i, pci_name(priv->pdev));

		priv->msix[TSI721_VECT_OMB0_DONE + i].vector =
				entries[TSI721_VECT_OMB0_DONE + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_OMB0_DONE + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-ombd%d@pci:%s",
			 i, pci_name(priv->pdev));

		priv->msix[TSI721_VECT_OMB0_INT + i].vector =
				entries[TSI721_VECT_OMB0_INT + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_OMB0_INT + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-ombi%d@pci:%s",
			 i, pci_name(priv->pdev));
	पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	क्रम (i = 0; i < TSI721_DMA_CHNUM; i++) अणु
		priv->msix[TSI721_VECT_DMA0_DONE + i].vector =
				entries[TSI721_VECT_DMA0_DONE + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_DMA0_DONE + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-dmad%d@pci:%s",
			 i, pci_name(priv->pdev));

		priv->msix[TSI721_VECT_DMA0_INT + i].vector =
				entries[TSI721_VECT_DMA0_INT + i].vector;
		snम_लिखो(priv->msix[TSI721_VECT_DMA0_INT + i].irq_name,
			 IRQ_DEVICE_NAME_MAX, DRV_NAME "-dmai%d@pci:%s",
			 i, pci_name(priv->pdev));
	पूर्ण
#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

अटल पूर्णांक tsi721_request_irq(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक err;

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX)
		err = tsi721_request_msix(priv);
	अन्यथा
#पूर्ण_अगर
		err = request_irq(priv->pdev->irq, tsi721_irqhandler,
			  (priv->flags & TSI721_USING_MSI) ? 0 : IRQF_SHARED,
			  DRV_NAME, (व्योम *)priv);

	अगर (err)
		tsi_err(&priv->pdev->dev,
			"Unable to allocate interrupt, err=%d", err);

	वापस err;
पूर्ण

अटल व्योम tsi721_मुक्त_irq(काष्ठा tsi721_device *priv)
अणु
#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		मुक्त_irq(priv->msix[TSI721_VECT_IDB].vector, (व्योम *)priv);
		मुक्त_irq(priv->msix[TSI721_VECT_PWRX].vector, (व्योम *)priv);
	पूर्ण अन्यथा
#पूर्ण_अगर
	मुक्त_irq(priv->pdev->irq, (व्योम *)priv);
पूर्ण

अटल पूर्णांक
tsi721_obw_alloc(काष्ठा tsi721_device *priv, काष्ठा tsi721_obw_bar *pbar,
		 u32 size, पूर्णांक *win_id)
अणु
	u64 win_base;
	u64 bar_base;
	u64 bar_end;
	u32 align;
	काष्ठा tsi721_ob_win *win;
	काष्ठा tsi721_ob_win *new_win = शून्य;
	पूर्णांक new_win_idx = -1;
	पूर्णांक i = 0;

	bar_base = pbar->base;
	bar_end =  bar_base + pbar->size;
	win_base = bar_base;
	align = size/TSI721_PC2SR_ZONES;

	जबतक (i < TSI721_IBWIN_NUM) अणु
		क्रम (i = 0; i < TSI721_IBWIN_NUM; i++) अणु
			अगर (!priv->ob_win[i].active) अणु
				अगर (new_win == शून्य) अणु
					new_win = &priv->ob_win[i];
					new_win_idx = i;
				पूर्ण
				जारी;
			पूर्ण

			/*
			 * If this winकरोw beदीर्घs to the current BAR check it
			 * क्रम overlap
			 */
			win = &priv->ob_win[i];

			अगर (win->base >= bar_base && win->base < bar_end) अणु
				अगर (win_base < (win->base + win->size) &&
						(win_base + size) > win->base) अणु
					/* Overlap detected */
					win_base = win->base + win->size;
					win_base = ALIGN(win_base, align);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (win_base + size > bar_end)
		वापस -ENOMEM;

	अगर (!new_win) अणु
		tsi_err(&priv->pdev->dev, "OBW count tracking failed");
		वापस -EIO;
	पूर्ण

	new_win->active = true;
	new_win->base = win_base;
	new_win->size = size;
	new_win->pbar = pbar;
	priv->obwin_cnt--;
	pbar->मुक्त -= size;
	*win_id = new_win_idx;
	वापस 0;
पूर्ण

अटल पूर्णांक tsi721_map_outb_win(काष्ठा rio_mport *mport, u16 destid, u64 rstart,
			u32 size, u32 flags, dma_addr_t *laddr)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	पूर्णांक i;
	काष्ठा tsi721_obw_bar *pbar;
	काष्ठा tsi721_ob_win *ob_win;
	पूर्णांक obw = -1;
	u32 rval;
	u64 rio_addr;
	u32 zsize;
	पूर्णांक ret = -ENOMEM;

	tsi_debug(OBW, &priv->pdev->dev,
		  "did=%d ra=0x%llx sz=0x%x", destid, rstart, size);

	अगर (!is_घातer_of_2(size) || (size < 0x8000) || (rstart & (size - 1)))
		वापस -EINVAL;

	अगर (priv->obwin_cnt == 0)
		वापस -EBUSY;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (priv->p2r_bar[i].मुक्त >= size) अणु
			pbar = &priv->p2r_bar[i];
			ret = tsi721_obw_alloc(priv, pbar, size, &obw);
			अगर (!ret)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	WARN_ON(obw == -1);
	ob_win = &priv->ob_win[obw];
	ob_win->destid = destid;
	ob_win->rstart = rstart;
	tsi_debug(OBW, &priv->pdev->dev,
		  "allocated OBW%d @%llx", obw, ob_win->base);

	/*
	 * Configure Outbound Winकरोw
	 */

	zsize = size/TSI721_PC2SR_ZONES;
	rio_addr = rstart;

	/*
	 * Program Address Translation Zones:
	 *  This implementation uses all 8 zones associated wit winकरोw.
	 */
	क्रम (i = 0; i < TSI721_PC2SR_ZONES; i++) अणु

		जबतक (ioपढ़ो32(priv->regs + TSI721_ZONE_SEL) &
			TSI721_ZONE_SEL_GO) अणु
			udelay(1);
		पूर्ण

		rval = (u32)(rio_addr & TSI721_LUT_DATA0_ADD) |
			TSI721_LUT_DATA0_NREAD | TSI721_LUT_DATA0_NWR;
		ioग_लिखो32(rval, priv->regs + TSI721_LUT_DATA0);
		rval = (u32)(rio_addr >> 32);
		ioग_लिखो32(rval, priv->regs + TSI721_LUT_DATA1);
		rval = destid;
		ioग_लिखो32(rval, priv->regs + TSI721_LUT_DATA2);

		rval = TSI721_ZONE_SEL_GO | (obw << 3) | i;
		ioग_लिखो32(rval, priv->regs + TSI721_ZONE_SEL);

		rio_addr += zsize;
	पूर्ण

	ioग_लिखो32(TSI721_OBWIN_SIZE(size) << 8,
		  priv->regs + TSI721_OBWINSZ(obw));
	ioग_लिखो32((u32)(ob_win->base >> 32), priv->regs + TSI721_OBWINUB(obw));
	ioग_लिखो32((u32)(ob_win->base & TSI721_OBWINLB_BA) | TSI721_OBWINLB_WEN,
		  priv->regs + TSI721_OBWINLB(obw));

	*laddr = ob_win->base;
	वापस 0;
पूर्ण

अटल व्योम tsi721_unmap_outb_win(काष्ठा rio_mport *mport,
				  u16 destid, u64 rstart)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	काष्ठा tsi721_ob_win *ob_win;
	पूर्णांक i;

	tsi_debug(OBW, &priv->pdev->dev, "did=%d ra=0x%llx", destid, rstart);

	क्रम (i = 0; i < TSI721_OBWIN_NUM; i++) अणु
		ob_win = &priv->ob_win[i];

		अगर (ob_win->active &&
		    ob_win->destid == destid && ob_win->rstart == rstart) अणु
			tsi_debug(OBW, &priv->pdev->dev,
				  "free OBW%d @%llx", i, ob_win->base);
			ob_win->active = false;
			ioग_लिखो32(0, priv->regs + TSI721_OBWINLB(i));
			ob_win->pbar->मुक्त += ob_win->size;
			priv->obwin_cnt++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * tsi721_init_pc2sr_mapping - initializes outbound (PCIe->SRIO)
 * translation regions.
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Disables SREP translation regions.
 */
अटल व्योम tsi721_init_pc2sr_mapping(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक i, z;
	u32 rval;

	/* Disable all PC2SR translation winकरोws */
	क्रम (i = 0; i < TSI721_OBWIN_NUM; i++)
		ioग_लिखो32(0, priv->regs + TSI721_OBWINLB(i));

	/* Initialize zone lookup tables to aव्योम ECC errors on पढ़ोs */
	ioग_लिखो32(0, priv->regs + TSI721_LUT_DATA0);
	ioग_लिखो32(0, priv->regs + TSI721_LUT_DATA1);
	ioग_लिखो32(0, priv->regs + TSI721_LUT_DATA2);

	क्रम (i = 0; i < TSI721_OBWIN_NUM; i++) अणु
		क्रम (z = 0; z < TSI721_PC2SR_ZONES; z++) अणु
			जबतक (ioपढ़ो32(priv->regs + TSI721_ZONE_SEL) &
				TSI721_ZONE_SEL_GO) अणु
				udelay(1);
			पूर्ण
			rval = TSI721_ZONE_SEL_GO | (i << 3) | z;
			ioग_लिखो32(rval, priv->regs + TSI721_ZONE_SEL);
		पूर्ण
	पूर्ण

	अगर (priv->p2r_bar[0].size == 0 && priv->p2r_bar[1].size == 0) अणु
		priv->obwin_cnt = 0;
		वापस;
	पूर्ण

	priv->p2r_bar[0].मुक्त = priv->p2r_bar[0].size;
	priv->p2r_bar[1].मुक्त = priv->p2r_bar[1].size;

	क्रम (i = 0; i < TSI721_OBWIN_NUM; i++)
		priv->ob_win[i].active = false;

	priv->obwin_cnt = TSI721_OBWIN_NUM;
पूर्ण

/**
 * tsi721_rio_map_inb_mem -- Mapping inbound memory region.
 * @mport: RapidIO master port
 * @lstart: Local memory space start address.
 * @rstart: RapidIO space start address.
 * @size: The mapping region size.
 * @flags: Flags क्रम mapping. 0 क्रम using शेष flags.
 *
 * Return: 0 -- Success.
 *
 * This function will create the inbound mapping
 * from rstart to lstart.
 */
अटल पूर्णांक tsi721_rio_map_inb_mem(काष्ठा rio_mport *mport, dma_addr_t lstart,
		u64 rstart, u64 size, u32 flags)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	पूर्णांक i, avail = -1;
	u32 regval;
	काष्ठा tsi721_ib_win *ib_win;
	bool direct = (lstart == rstart);
	u64 ibw_size;
	dma_addr_t loc_start;
	u64 ibw_start;
	काष्ठा tsi721_ib_win_mapping *map = शून्य;
	पूर्णांक ret = -EBUSY;

	/* Max IBW size supported by HW is 16GB */
	अगर (size > 0x400000000UL)
		वापस -EINVAL;

	अगर (direct) अणु
		/* Calculate minimal acceptable winकरोw size and base address */

		ibw_size = roundup_घात_of_two(size);
		ibw_start = lstart & ~(ibw_size - 1);

		tsi_debug(IBW, &priv->pdev->dev,
			"Direct (RIO_0x%llx -> PCIe_%pad), size=0x%llx, ibw_start = 0x%llx",
			rstart, &lstart, size, ibw_start);

		जबतक ((lstart + size) > (ibw_start + ibw_size)) अणु
			ibw_size *= 2;
			ibw_start = lstart & ~(ibw_size - 1);
			/* Check क्रम crossing IBW max size 16GB */
			अगर (ibw_size > 0x400000000UL)
				वापस -EBUSY;
		पूर्ण

		loc_start = ibw_start;

		map = kzalloc(माप(काष्ठा tsi721_ib_win_mapping), GFP_ATOMIC);
		अगर (map == शून्य)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		tsi_debug(IBW, &priv->pdev->dev,
			"Translated (RIO_0x%llx -> PCIe_%pad), size=0x%llx",
			rstart, &lstart, size);

		अगर (!is_घातer_of_2(size) || size < 0x1000 ||
		    ((u64)lstart & (size - 1)) || (rstart & (size - 1)))
			वापस -EINVAL;
		अगर (priv->ibwin_cnt == 0)
			वापस -EBUSY;
		ibw_start = rstart;
		ibw_size = size;
		loc_start = lstart;
	पूर्ण

	/*
	 * Scan क्रम overlapping with active regions and mark the first available
	 * IB winकरोw at the same समय.
	 */
	क्रम (i = 0; i < TSI721_IBWIN_NUM; i++) अणु
		ib_win = &priv->ib_win[i];

		अगर (!ib_win->active) अणु
			अगर (avail == -1) अणु
				avail = i;
				ret = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (ibw_start < (ib_win->rstart + ib_win->size) &&
			   (ibw_start + ibw_size) > ib_win->rstart) अणु
			/* Return error अगर address translation involved */
			अगर (!direct || ib_win->xlat) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण

			/*
			 * Direct mappings usually are larger than originally
			 * requested fragments - check अगर this new request fits
			 * पूर्णांकo it.
			 */
			अगर (rstart >= ib_win->rstart &&
			    (rstart + size) <= (ib_win->rstart +
							ib_win->size)) अणु
				/* We are in - no further mapping required */
				map->lstart = lstart;
				list_add_tail(&map->node, &ib_win->mappings);
				वापस 0;
			पूर्ण

			ret = -EFAULT;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		जाओ out;
	i = avail;

	/* Sanity check: available IB winकरोw must be disabled at this poपूर्णांक */
	regval = ioपढ़ो32(priv->regs + TSI721_IBWIN_LB(i));
	अगर (WARN_ON(regval & TSI721_IBWIN_LB_WEN)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ib_win = &priv->ib_win[i];
	ib_win->active = true;
	ib_win->rstart = ibw_start;
	ib_win->lstart = loc_start;
	ib_win->size = ibw_size;
	ib_win->xlat = (lstart != rstart);
	INIT_LIST_HEAD(&ib_win->mappings);

	/*
	 * When using direct IBW mapping and have larger than requested IBW size
	 * we can have multiple local memory blocks mapped through the same IBW
	 * To handle this situation we मुख्यtain list of "clients" क्रम such IBWs.
	 */
	अगर (direct) अणु
		map->lstart = lstart;
		list_add_tail(&map->node, &ib_win->mappings);
	पूर्ण

	ioग_लिखो32(TSI721_IBWIN_SIZE(ibw_size) << 8,
			priv->regs + TSI721_IBWIN_SZ(i));

	ioग_लिखो32(((u64)loc_start >> 32), priv->regs + TSI721_IBWIN_TUA(i));
	ioग_लिखो32(((u64)loc_start & TSI721_IBWIN_TLA_ADD),
		  priv->regs + TSI721_IBWIN_TLA(i));

	ioग_लिखो32(ibw_start >> 32, priv->regs + TSI721_IBWIN_UB(i));
	ioग_लिखो32((ibw_start & TSI721_IBWIN_LB_BA) | TSI721_IBWIN_LB_WEN,
		priv->regs + TSI721_IBWIN_LB(i));

	priv->ibwin_cnt--;

	tsi_debug(IBW, &priv->pdev->dev,
		"Configured IBWIN%d (RIO_0x%llx -> PCIe_%pad), size=0x%llx",
		i, ibw_start, &loc_start, ibw_size);

	वापस 0;
out:
	kमुक्त(map);
	वापस ret;
पूर्ण

/**
 * tsi721_rio_unmap_inb_mem -- Unmapping inbound memory region.
 * @mport: RapidIO master port
 * @lstart: Local memory space start address.
 */
अटल व्योम tsi721_rio_unmap_inb_mem(काष्ठा rio_mport *mport,
				dma_addr_t lstart)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	काष्ठा tsi721_ib_win *ib_win;
	पूर्णांक i;

	tsi_debug(IBW, &priv->pdev->dev,
		"Unmap IBW mapped to PCIe_%pad", &lstart);

	/* Search क्रम matching active inbound translation winकरोw */
	क्रम (i = 0; i < TSI721_IBWIN_NUM; i++) अणु
		ib_win = &priv->ib_win[i];

		/* Address translating IBWs must to be an exact march */
		अगर (!ib_win->active ||
		    (ib_win->xlat && lstart != ib_win->lstart))
			जारी;

		अगर (lstart >= ib_win->lstart &&
		    lstart < (ib_win->lstart + ib_win->size)) अणु

			अगर (!ib_win->xlat) अणु
				काष्ठा tsi721_ib_win_mapping *map;
				पूर्णांक found = 0;

				list_क्रम_each_entry(map,
						    &ib_win->mappings, node) अणु
					अगर (map->lstart == lstart) अणु
						list_del(&map->node);
						kमुक्त(map);
						found = 1;
						अवरोध;
					पूर्ण
				पूर्ण

				अगर (!found)
					जारी;

				अगर (!list_empty(&ib_win->mappings))
					अवरोध;
			पूर्ण

			tsi_debug(IBW, &priv->pdev->dev, "Disable IBWIN_%d", i);
			ioग_लिखो32(0, priv->regs + TSI721_IBWIN_LB(i));
			ib_win->active = false;
			priv->ibwin_cnt++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == TSI721_IBWIN_NUM)
		tsi_debug(IBW, &priv->pdev->dev,
			"IB window mapped to %pad not found", &lstart);
पूर्ण

/**
 * tsi721_init_sr2pc_mapping - initializes inbound (SRIO->PCIe)
 * translation regions.
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Disables inbound winकरोws.
 */
अटल व्योम tsi721_init_sr2pc_mapping(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक i;

	/* Disable all SR2PC inbound winकरोws */
	क्रम (i = 0; i < TSI721_IBWIN_NUM; i++)
		ioग_लिखो32(0, priv->regs + TSI721_IBWIN_LB(i));
	priv->ibwin_cnt = TSI721_IBWIN_NUM;
पूर्ण

/*
 * tsi721_बंद_sr2pc_mapping - बंदs all active inbound (SRIO->PCIe)
 * translation regions.
 * @priv: poपूर्णांकer to tsi721 device निजी data
 */
अटल व्योम tsi721_बंद_sr2pc_mapping(काष्ठा tsi721_device *priv)
अणु
	काष्ठा tsi721_ib_win *ib_win;
	पूर्णांक i;

	/* Disable all active SR2PC inbound winकरोws */
	क्रम (i = 0; i < TSI721_IBWIN_NUM; i++) अणु
		ib_win = &priv->ib_win[i];
		अगर (ib_win->active) अणु
			ioग_लिखो32(0, priv->regs + TSI721_IBWIN_LB(i));
			ib_win->active = false;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * tsi721_port_ग_लिखो_init - Inbound port ग_लिखो पूर्णांकerface init
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Initializes inbound port ग_लिखो handler.
 * Returns %0 on success or %-ENOMEM on failure.
 */
अटल पूर्णांक tsi721_port_ग_लिखो_init(काष्ठा tsi721_device *priv)
अणु
	priv->pw_discard_count = 0;
	INIT_WORK(&priv->pw_work, tsi721_pw_dpc);
	spin_lock_init(&priv->pw_fअगरo_lock);
	अगर (kfअगरo_alloc(&priv->pw_fअगरo,
			TSI721_RIO_PW_MSG_SIZE * 32, GFP_KERNEL)) अणु
		tsi_err(&priv->pdev->dev, "PW FIFO allocation failed");
		वापस -ENOMEM;
	पूर्ण

	/* Use reliable port-ग_लिखो capture mode */
	ioग_लिखो32(TSI721_RIO_PW_CTL_PWC_REL, priv->regs + TSI721_RIO_PW_CTL);
	वापस 0;
पूर्ण

अटल व्योम tsi721_port_ग_लिखो_मुक्त(काष्ठा tsi721_device *priv)
अणु
	kfअगरo_मुक्त(&priv->pw_fअगरo);
पूर्ण

अटल पूर्णांक tsi721_करोorbell_init(काष्ठा tsi721_device *priv)
अणु
	/* Outbound Doorbells करो not require any setup.
	 * Tsi721 uses dedicated PCI BAR1 to generate करोorbells.
	 * That BAR1 was mapped during the probe routine.
	 */

	/* Initialize Inbound Doorbell processing DPC and queue */
	priv->db_discard_count = 0;
	INIT_WORK(&priv->idb_work, tsi721_db_dpc);

	/* Allocate buffer क्रम inbound करोorbells queue */
	priv->idb_base = dma_alloc_coherent(&priv->pdev->dev,
					    IDB_QSIZE * TSI721_IDB_ENTRY_SIZE,
					    &priv->idb_dma, GFP_KERNEL);
	अगर (!priv->idb_base)
		वापस -ENOMEM;

	tsi_debug(DBELL, &priv->pdev->dev,
		  "Allocated IDB buffer @ %p (phys = %pad)",
		  priv->idb_base, &priv->idb_dma);

	ioग_लिखो32(TSI721_IDQ_SIZE_VAL(IDB_QSIZE),
		priv->regs + TSI721_IDQ_SIZE(IDB_QUEUE));
	ioग_लिखो32(((u64)priv->idb_dma >> 32),
		priv->regs + TSI721_IDQ_BASEU(IDB_QUEUE));
	ioग_लिखो32(((u64)priv->idb_dma & TSI721_IDQ_BASEL_ADDR),
		priv->regs + TSI721_IDQ_BASEL(IDB_QUEUE));
	/* Enable accepting all inbound करोorbells */
	ioग_लिखो32(0, priv->regs + TSI721_IDQ_MASK(IDB_QUEUE));

	ioग_लिखो32(TSI721_IDQ_INIT, priv->regs + TSI721_IDQ_CTL(IDB_QUEUE));

	ioग_लिखो32(0, priv->regs + TSI721_IDQ_RP(IDB_QUEUE));

	वापस 0;
पूर्ण

अटल व्योम tsi721_करोorbell_मुक्त(काष्ठा tsi721_device *priv)
अणु
	अगर (priv->idb_base == शून्य)
		वापस;

	/* Free buffer allocated क्रम inbound करोorbell queue */
	dma_मुक्त_coherent(&priv->pdev->dev, IDB_QSIZE * TSI721_IDB_ENTRY_SIZE,
			  priv->idb_base, priv->idb_dma);
	priv->idb_base = शून्य;
पूर्ण

/**
 * tsi721_bdma_मुख्यt_init - Initialize मुख्यtenance request BDMA channel.
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Initialize BDMA channel allocated क्रम RapidIO मुख्यtenance पढ़ो/ग_लिखो
 * request generation
 * Returns %0 on success or %-ENOMEM on failure.
 */
अटल पूर्णांक tsi721_bdma_मुख्यt_init(काष्ठा tsi721_device *priv)
अणु
	काष्ठा tsi721_dma_desc *bd_ptr;
	u64		*sts_ptr;
	dma_addr_t	bd_phys, sts_phys;
	पूर्णांक		sts_size;
	पूर्णांक		bd_num = 2;
	व्योम __iomem	*regs;

	tsi_debug(MAINT, &priv->pdev->dev,
		  "Init BDMA_%d Maintenance requests", TSI721_DMACH_MAINT);

	/*
	 * Initialize DMA channel क्रम मुख्यtenance requests
	 */

	priv->mdma.ch_id = TSI721_DMACH_MAINT;
	regs = priv->regs + TSI721_DMAC_BASE(TSI721_DMACH_MAINT);

	/* Allocate space क्रम DMA descriptors */
	bd_ptr = dma_alloc_coherent(&priv->pdev->dev,
				    bd_num * माप(काष्ठा tsi721_dma_desc),
				    &bd_phys, GFP_KERNEL);
	अगर (!bd_ptr)
		वापस -ENOMEM;

	priv->mdma.bd_num = bd_num;
	priv->mdma.bd_phys = bd_phys;
	priv->mdma.bd_base = bd_ptr;

	tsi_debug(MAINT, &priv->pdev->dev, "DMA descriptors @ %p (phys = %pad)",
		  bd_ptr, &bd_phys);

	/* Allocate space क्रम descriptor status FIFO */
	sts_size = (bd_num >= TSI721_DMA_MINSTSSZ) ?
					bd_num : TSI721_DMA_MINSTSSZ;
	sts_size = roundup_घात_of_two(sts_size);
	sts_ptr = dma_alloc_coherent(&priv->pdev->dev,
				     sts_size * माप(काष्ठा tsi721_dma_sts),
				     &sts_phys, GFP_KERNEL);
	अगर (!sts_ptr) अणु
		/* Free space allocated क्रम DMA descriptors */
		dma_मुक्त_coherent(&priv->pdev->dev,
				  bd_num * माप(काष्ठा tsi721_dma_desc),
				  bd_ptr, bd_phys);
		priv->mdma.bd_base = शून्य;
		वापस -ENOMEM;
	पूर्ण

	priv->mdma.sts_phys = sts_phys;
	priv->mdma.sts_base = sts_ptr;
	priv->mdma.sts_size = sts_size;

	tsi_debug(MAINT, &priv->pdev->dev,
		"desc status FIFO @ %p (phys = %pad) size=0x%x",
		sts_ptr, &sts_phys, sts_size);

	/* Initialize DMA descriptors ring */
	bd_ptr[bd_num - 1].type_id = cpu_to_le32(DTYPE3 << 29);
	bd_ptr[bd_num - 1].next_lo = cpu_to_le32((u64)bd_phys &
						 TSI721_DMAC_DPTRL_MASK);
	bd_ptr[bd_num - 1].next_hi = cpu_to_le32((u64)bd_phys >> 32);

	/* Setup DMA descriptor poपूर्णांकers */
	ioग_लिखो32(((u64)bd_phys >> 32),	regs + TSI721_DMAC_DPTRH);
	ioग_लिखो32(((u64)bd_phys & TSI721_DMAC_DPTRL_MASK),
		regs + TSI721_DMAC_DPTRL);

	/* Setup descriptor status FIFO */
	ioग_लिखो32(((u64)sts_phys >> 32), regs + TSI721_DMAC_DSBH);
	ioग_लिखो32(((u64)sts_phys & TSI721_DMAC_DSBL_MASK),
		regs + TSI721_DMAC_DSBL);
	ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(sts_size),
		regs + TSI721_DMAC_DSSZ);

	/* Clear पूर्णांकerrupt bits */
	ioग_लिखो32(TSI721_DMAC_INT_ALL, regs + TSI721_DMAC_INT);

	ioपढ़ो32(regs + TSI721_DMAC_INT);

	/* Toggle DMA channel initialization */
	ioग_लिखो32(TSI721_DMAC_CTL_INIT,	regs + TSI721_DMAC_CTL);
	ioपढ़ो32(regs + TSI721_DMAC_CTL);
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक tsi721_bdma_मुख्यt_मुक्त(काष्ठा tsi721_device *priv)
अणु
	u32 ch_stat;
	काष्ठा tsi721_bdma_मुख्यt *mdma = &priv->mdma;
	व्योम __iomem *regs = priv->regs + TSI721_DMAC_BASE(mdma->ch_id);

	अगर (mdma->bd_base == शून्य)
		वापस 0;

	/* Check अगर DMA channel still running */
	ch_stat = ioपढ़ो32(regs + TSI721_DMAC_STS);
	अगर (ch_stat & TSI721_DMAC_STS_RUN)
		वापस -EFAULT;

	/* Put DMA channel पूर्णांकo init state */
	ioग_लिखो32(TSI721_DMAC_CTL_INIT,	regs + TSI721_DMAC_CTL);

	/* Free space allocated क्रम DMA descriptors */
	dma_मुक्त_coherent(&priv->pdev->dev,
		mdma->bd_num * माप(काष्ठा tsi721_dma_desc),
		mdma->bd_base, mdma->bd_phys);
	mdma->bd_base = शून्य;

	/* Free space allocated क्रम status FIFO */
	dma_मुक्त_coherent(&priv->pdev->dev,
		mdma->sts_size * माप(काष्ठा tsi721_dma_sts),
		mdma->sts_base, mdma->sts_phys);
	mdma->sts_base = शून्य;
	वापस 0;
पूर्ण

/* Enable Inbound Messaging Interrupts */
अटल व्योम
tsi721_imsg_पूर्णांकerrupt_enable(काष्ठा tsi721_device *priv, पूर्णांक ch,
				  u32 पूर्णांकe_mask)
अणु
	u32 rval;

	अगर (!पूर्णांकe_mask)
		वापस;

	/* Clear pending Inbound Messaging पूर्णांकerrupts */
	ioग_लिखो32(पूर्णांकe_mask, priv->regs + TSI721_IBDMAC_INT(ch));

	/* Enable Inbound Messaging पूर्णांकerrupts */
	rval = ioपढ़ो32(priv->regs + TSI721_IBDMAC_INTE(ch));
	ioग_लिखो32(rval | पूर्णांकe_mask, priv->regs + TSI721_IBDMAC_INTE(ch));

	अगर (priv->flags & TSI721_USING_MSIX)
		वापस; /* Finished अगर we are in MSI-X mode */

	/*
	 * For MSI and INTA पूर्णांकerrupt संकेतling we need to enable next levels
	 */

	/* Enable Device Channel Interrupt */
	rval = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
	ioग_लिखो32(rval | TSI721_INT_IMSG_CHAN(ch),
		  priv->regs + TSI721_DEV_CHAN_INTE);
पूर्ण

/* Disable Inbound Messaging Interrupts */
अटल व्योम
tsi721_imsg_पूर्णांकerrupt_disable(काष्ठा tsi721_device *priv, पूर्णांक ch,
				   u32 पूर्णांकe_mask)
अणु
	u32 rval;

	अगर (!पूर्णांकe_mask)
		वापस;

	/* Clear pending Inbound Messaging पूर्णांकerrupts */
	ioग_लिखो32(पूर्णांकe_mask, priv->regs + TSI721_IBDMAC_INT(ch));

	/* Disable Inbound Messaging पूर्णांकerrupts */
	rval = ioपढ़ो32(priv->regs + TSI721_IBDMAC_INTE(ch));
	rval &= ~पूर्णांकe_mask;
	ioग_लिखो32(rval, priv->regs + TSI721_IBDMAC_INTE(ch));

	अगर (priv->flags & TSI721_USING_MSIX)
		वापस; /* Finished अगर we are in MSI-X mode */

	/*
	 * For MSI and INTA पूर्णांकerrupt संकेतling we need to disable next levels
	 */

	/* Disable Device Channel Interrupt */
	rval = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
	rval &= ~TSI721_INT_IMSG_CHAN(ch);
	ioग_लिखो32(rval, priv->regs + TSI721_DEV_CHAN_INTE);
पूर्ण

/* Enable Outbound Messaging पूर्णांकerrupts */
अटल व्योम
tsi721_omsg_पूर्णांकerrupt_enable(काष्ठा tsi721_device *priv, पूर्णांक ch,
				  u32 पूर्णांकe_mask)
अणु
	u32 rval;

	अगर (!पूर्णांकe_mask)
		वापस;

	/* Clear pending Outbound Messaging पूर्णांकerrupts */
	ioग_लिखो32(पूर्णांकe_mask, priv->regs + TSI721_OBDMAC_INT(ch));

	/* Enable Outbound Messaging channel पूर्णांकerrupts */
	rval = ioपढ़ो32(priv->regs + TSI721_OBDMAC_INTE(ch));
	ioग_लिखो32(rval | पूर्णांकe_mask, priv->regs + TSI721_OBDMAC_INTE(ch));

	अगर (priv->flags & TSI721_USING_MSIX)
		वापस; /* Finished अगर we are in MSI-X mode */

	/*
	 * For MSI and INTA पूर्णांकerrupt संकेतling we need to enable next levels
	 */

	/* Enable Device Channel Interrupt */
	rval = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
	ioग_लिखो32(rval | TSI721_INT_OMSG_CHAN(ch),
		  priv->regs + TSI721_DEV_CHAN_INTE);
पूर्ण

/* Disable Outbound Messaging पूर्णांकerrupts */
अटल व्योम
tsi721_omsg_पूर्णांकerrupt_disable(काष्ठा tsi721_device *priv, पूर्णांक ch,
				   u32 पूर्णांकe_mask)
अणु
	u32 rval;

	अगर (!पूर्णांकe_mask)
		वापस;

	/* Clear pending Outbound Messaging पूर्णांकerrupts */
	ioग_लिखो32(पूर्णांकe_mask, priv->regs + TSI721_OBDMAC_INT(ch));

	/* Disable Outbound Messaging पूर्णांकerrupts */
	rval = ioपढ़ो32(priv->regs + TSI721_OBDMAC_INTE(ch));
	rval &= ~पूर्णांकe_mask;
	ioग_लिखो32(rval, priv->regs + TSI721_OBDMAC_INTE(ch));

	अगर (priv->flags & TSI721_USING_MSIX)
		वापस; /* Finished अगर we are in MSI-X mode */

	/*
	 * For MSI and INTA पूर्णांकerrupt संकेतling we need to disable next levels
	 */

	/* Disable Device Channel Interrupt */
	rval = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
	rval &= ~TSI721_INT_OMSG_CHAN(ch);
	ioग_लिखो32(rval, priv->regs + TSI721_DEV_CHAN_INTE);
पूर्ण

/**
 * tsi721_add_outb_message - Add message to the Tsi721 outbound message queue
 * @mport: Master port with outbound message queue
 * @rdev: Target of outbound message
 * @mbox: Outbound mailbox
 * @buffer: Message to add to outbound queue
 * @len: Length of message
 */
अटल पूर्णांक
tsi721_add_outb_message(काष्ठा rio_mport *mport, काष्ठा rio_dev *rdev, पूर्णांक mbox,
			व्योम *buffer, माप_प्रकार len)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	काष्ठा tsi721_omsg_desc *desc;
	u32 tx_slot;
	अचिन्हित दीर्घ flags;

	अगर (!priv->omsg_init[mbox] ||
	    len > TSI721_MSG_MAX_SIZE || len < 8)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->omsg_ring[mbox].lock, flags);

	tx_slot = priv->omsg_ring[mbox].tx_slot;

	/* Copy copy message पूर्णांकo transfer buffer */
	स_नकल(priv->omsg_ring[mbox].omq_base[tx_slot], buffer, len);

	अगर (len & 0x7)
		len += 8;

	/* Build descriptor associated with buffer */
	desc = priv->omsg_ring[mbox].omd_base;
	desc[tx_slot].type_id = cpu_to_le32((DTYPE4 << 29) | rdev->destid);
#अगर_घोषित TSI721_OMSG_DESC_INT
	/* Request IOF_DONE पूर्णांकerrupt generation क्रम each N-th frame in queue */
	अगर (tx_slot % 4 == 0)
		desc[tx_slot].type_id |= cpu_to_le32(TSI721_OMD_IOF);
#पूर्ण_अगर
	desc[tx_slot].msg_info =
		cpu_to_le32((mport->sys_size << 26) | (mbox << 22) |
			    (0xe << 12) | (len & 0xff8));
	desc[tx_slot].bufptr_lo =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omq_phys[tx_slot] &
			    0xffffffff);
	desc[tx_slot].bufptr_hi =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omq_phys[tx_slot] >> 32);

	priv->omsg_ring[mbox].wr_count++;

	/* Go to next descriptor */
	अगर (++priv->omsg_ring[mbox].tx_slot == priv->omsg_ring[mbox].size) अणु
		priv->omsg_ring[mbox].tx_slot = 0;
		/* Move through the ring link descriptor at the end */
		priv->omsg_ring[mbox].wr_count++;
	पूर्ण

	mb();

	/* Set new ग_लिखो count value */
	ioग_लिखो32(priv->omsg_ring[mbox].wr_count,
		priv->regs + TSI721_OBDMAC_DWRCNT(mbox));
	ioपढ़ो32(priv->regs + TSI721_OBDMAC_DWRCNT(mbox));

	spin_unlock_irqrestore(&priv->omsg_ring[mbox].lock, flags);

	वापस 0;
पूर्ण

/**
 * tsi721_omsg_handler - Outbound Message Interrupt Handler
 * @priv: poपूर्णांकer to tsi721 निजी data
 * @ch:   number of OB MSG channel to service
 *
 * Services channel पूर्णांकerrupts from outbound messaging engine.
 */
अटल व्योम tsi721_omsg_handler(काष्ठा tsi721_device *priv, पूर्णांक ch)
अणु
	u32 omsg_पूर्णांक;
	काष्ठा rio_mport *mport = &priv->mport;
	व्योम *dev_id = शून्य;
	u32 tx_slot = 0xffffffff;
	पूर्णांक करो_callback = 0;

	spin_lock(&priv->omsg_ring[ch].lock);

	omsg_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_OBDMAC_INT(ch));

	अगर (omsg_पूर्णांक & TSI721_OBDMAC_INT_ST_FULL)
		tsi_info(&priv->pdev->dev,
			"OB MBOX%d: Status FIFO is full", ch);

	अगर (omsg_पूर्णांक & (TSI721_OBDMAC_INT_DONE | TSI721_OBDMAC_INT_IOF_DONE)) अणु
		u32 srd_ptr;
		u64 *sts_ptr, last_ptr = 0, prev_ptr = 0;
		पूर्णांक i, j;

		/*
		 * Find last successfully processed descriptor
		 */

		/* Check and clear descriptor status FIFO entries */
		srd_ptr = priv->omsg_ring[ch].sts_rdptr;
		sts_ptr = priv->omsg_ring[ch].sts_base;
		j = srd_ptr * 8;
		जबतक (sts_ptr[j]) अणु
			क्रम (i = 0; i < 8 && sts_ptr[j]; i++, j++) अणु
				prev_ptr = last_ptr;
				last_ptr = le64_to_cpu(sts_ptr[j]);
				sts_ptr[j] = 0;
			पूर्ण

			++srd_ptr;
			srd_ptr %= priv->omsg_ring[ch].sts_size;
			j = srd_ptr * 8;
		पूर्ण

		अगर (last_ptr == 0)
			जाओ no_sts_update;

		priv->omsg_ring[ch].sts_rdptr = srd_ptr;
		ioग_लिखो32(srd_ptr, priv->regs + TSI721_OBDMAC_DSRP(ch));

		अगर (!mport->outb_msg[ch].mcback)
			जाओ no_sts_update;

		/* Inक्रमm upper layer about transfer completion */

		tx_slot = (last_ptr - (u64)priv->omsg_ring[ch].omd_phys)/
						माप(काष्ठा tsi721_omsg_desc);

		/*
		 * Check अगर this is a Link Descriptor (LD).
		 * If yes, ignore LD and use descriptor processed
		 * beक्रमe LD.
		 */
		अगर (tx_slot == priv->omsg_ring[ch].size) अणु
			अगर (prev_ptr)
				tx_slot = (prev_ptr -
					(u64)priv->omsg_ring[ch].omd_phys)/
						माप(काष्ठा tsi721_omsg_desc);
			अन्यथा
				जाओ no_sts_update;
		पूर्ण

		अगर (tx_slot >= priv->omsg_ring[ch].size)
			tsi_debug(OMSG, &priv->pdev->dev,
				  "OB_MSG tx_slot=%x > size=%x",
				  tx_slot, priv->omsg_ring[ch].size);
		WARN_ON(tx_slot >= priv->omsg_ring[ch].size);

		/* Move slot index to the next message to be sent */
		++tx_slot;
		अगर (tx_slot == priv->omsg_ring[ch].size)
			tx_slot = 0;

		dev_id = priv->omsg_ring[ch].dev_id;
		करो_callback = 1;
	पूर्ण

no_sts_update:

	अगर (omsg_पूर्णांक & TSI721_OBDMAC_INT_ERROR) अणु
		/*
		* Outbound message operation पातed due to error,
		* reinitialize OB MSG channel
		*/

		tsi_debug(OMSG, &priv->pdev->dev, "OB MSG ABORT ch_stat=%x",
			  ioपढ़ो32(priv->regs + TSI721_OBDMAC_STS(ch)));

		ioग_लिखो32(TSI721_OBDMAC_INT_ERROR,
				priv->regs + TSI721_OBDMAC_INT(ch));
		ioग_लिखो32(TSI721_OBDMAC_CTL_RETRY_THR | TSI721_OBDMAC_CTL_INIT,
				priv->regs + TSI721_OBDMAC_CTL(ch));
		ioपढ़ो32(priv->regs + TSI721_OBDMAC_CTL(ch));

		/* Inक्रमm upper level to clear all pending tx slots */
		dev_id = priv->omsg_ring[ch].dev_id;
		tx_slot = priv->omsg_ring[ch].tx_slot;
		करो_callback = 1;

		/* Synch tx_slot tracking */
		ioग_लिखो32(priv->omsg_ring[ch].tx_slot,
			priv->regs + TSI721_OBDMAC_DRDCNT(ch));
		ioपढ़ो32(priv->regs + TSI721_OBDMAC_DRDCNT(ch));
		priv->omsg_ring[ch].wr_count = priv->omsg_ring[ch].tx_slot;
		priv->omsg_ring[ch].sts_rdptr = 0;
	पूर्ण

	/* Clear channel पूर्णांकerrupts */
	ioग_लिखो32(omsg_पूर्णांक, priv->regs + TSI721_OBDMAC_INT(ch));

	अगर (!(priv->flags & TSI721_USING_MSIX)) अणु
		u32 ch_पूर्णांकe;

		/* Re-enable channel पूर्णांकerrupts */
		ch_पूर्णांकe = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
		ch_पूर्णांकe |= TSI721_INT_OMSG_CHAN(ch);
		ioग_लिखो32(ch_पूर्णांकe, priv->regs + TSI721_DEV_CHAN_INTE);
	पूर्ण

	spin_unlock(&priv->omsg_ring[ch].lock);

	अगर (mport->outb_msg[ch].mcback && करो_callback)
		mport->outb_msg[ch].mcback(mport, dev_id, ch, tx_slot);
पूर्ण

/**
 * tsi721_खोलो_outb_mbox - Initialize Tsi721 outbound mailbox
 * @mport: Master port implementing Outbound Messaging Engine
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox to खोलो
 * @entries: Number of entries in the outbound mailbox ring
 */
अटल पूर्णांक tsi721_खोलो_outb_mbox(काष्ठा rio_mport *mport, व्योम *dev_id,
				 पूर्णांक mbox, पूर्णांक entries)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	काष्ठा tsi721_omsg_desc *bd_ptr;
	पूर्णांक i, rc = 0;

	अगर ((entries < TSI721_OMSGD_MIN_RING_SIZE) ||
	    (entries > (TSI721_OMSGD_RING_SIZE)) ||
	    (!is_घातer_of_2(entries)) || mbox >= RIO_MAX_MBOX) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((mbox_sel & (1 << mbox)) == 0) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	priv->omsg_ring[mbox].dev_id = dev_id;
	priv->omsg_ring[mbox].size = entries;
	priv->omsg_ring[mbox].sts_rdptr = 0;
	spin_lock_init(&priv->omsg_ring[mbox].lock);

	/* Outbound Msg Buffer allocation based on
	   the number of maximum descriptor entries */
	क्रम (i = 0; i < entries; i++) अणु
		priv->omsg_ring[mbox].omq_base[i] =
			dma_alloc_coherent(
				&priv->pdev->dev, TSI721_MSG_BUFFER_SIZE,
				&priv->omsg_ring[mbox].omq_phys[i],
				GFP_KERNEL);
		अगर (priv->omsg_ring[mbox].omq_base[i] == शून्य) अणु
			tsi_debug(OMSG, &priv->pdev->dev,
				  "ENOMEM for OB_MSG_%d data buffer", mbox);
			rc = -ENOMEM;
			जाओ out_buf;
		पूर्ण
	पूर्ण

	/* Outbound message descriptor allocation */
	priv->omsg_ring[mbox].omd_base = dma_alloc_coherent(
				&priv->pdev->dev,
				(entries + 1) * माप(काष्ठा tsi721_omsg_desc),
				&priv->omsg_ring[mbox].omd_phys, GFP_KERNEL);
	अगर (priv->omsg_ring[mbox].omd_base == शून्य) अणु
		tsi_debug(OMSG, &priv->pdev->dev,
			"ENOMEM for OB_MSG_%d descriptor memory", mbox);
		rc = -ENOMEM;
		जाओ out_buf;
	पूर्ण

	priv->omsg_ring[mbox].tx_slot = 0;

	/* Outbound message descriptor status FIFO allocation */
	priv->omsg_ring[mbox].sts_size = roundup_घात_of_two(entries + 1);
	priv->omsg_ring[mbox].sts_base = dma_alloc_coherent(&priv->pdev->dev,
							    priv->omsg_ring[mbox].sts_size * माप(काष्ठा tsi721_dma_sts),
							    &priv->omsg_ring[mbox].sts_phys,
							    GFP_KERNEL);
	अगर (priv->omsg_ring[mbox].sts_base == शून्य) अणु
		tsi_debug(OMSG, &priv->pdev->dev,
			"ENOMEM for OB_MSG_%d status FIFO", mbox);
		rc = -ENOMEM;
		जाओ out_desc;
	पूर्ण

	/*
	 * Configure Outbound Messaging Engine
	 */

	/* Setup Outbound Message descriptor poपूर्णांकer */
	ioग_लिखो32(((u64)priv->omsg_ring[mbox].omd_phys >> 32),
			priv->regs + TSI721_OBDMAC_DPTRH(mbox));
	ioग_लिखो32(((u64)priv->omsg_ring[mbox].omd_phys &
					TSI721_OBDMAC_DPTRL_MASK),
			priv->regs + TSI721_OBDMAC_DPTRL(mbox));

	/* Setup Outbound Message descriptor status FIFO */
	ioग_लिखो32(((u64)priv->omsg_ring[mbox].sts_phys >> 32),
			priv->regs + TSI721_OBDMAC_DSBH(mbox));
	ioग_लिखो32(((u64)priv->omsg_ring[mbox].sts_phys &
					TSI721_OBDMAC_DSBL_MASK),
			priv->regs + TSI721_OBDMAC_DSBL(mbox));
	ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(priv->omsg_ring[mbox].sts_size),
		priv->regs + (u32)TSI721_OBDMAC_DSSZ(mbox));

	/* Enable पूर्णांकerrupts */

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		पूर्णांक idx = TSI721_VECT_OMB0_DONE + mbox;

		/* Request पूर्णांकerrupt service अगर we are in MSI-X mode */
		rc = request_irq(priv->msix[idx].vector, tsi721_omsg_msix, 0,
				 priv->msix[idx].irq_name, (व्योम *)priv);

		अगर (rc) अणु
			tsi_debug(OMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for OBOX%d-DONE",
				mbox);
			जाओ out_stat;
		पूर्ण

		idx = TSI721_VECT_OMB0_INT + mbox;
		rc = request_irq(priv->msix[idx].vector, tsi721_omsg_msix, 0,
				 priv->msix[idx].irq_name, (व्योम *)priv);

		अगर (rc)	अणु
			tsi_debug(OMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for MBOX%d-INT", mbox);
			idx = TSI721_VECT_OMB0_DONE + mbox;
			मुक्त_irq(priv->msix[idx].vector, (व्योम *)priv);
			जाओ out_stat;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	tsi721_omsg_पूर्णांकerrupt_enable(priv, mbox, TSI721_OBDMAC_INT_ALL);

	/* Initialize Outbound Message descriptors ring */
	bd_ptr = priv->omsg_ring[mbox].omd_base;
	bd_ptr[entries].type_id = cpu_to_le32(DTYPE5 << 29);
	bd_ptr[entries].msg_info = 0;
	bd_ptr[entries].next_lo =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omd_phys &
		TSI721_OBDMAC_DPTRL_MASK);
	bd_ptr[entries].next_hi =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omd_phys >> 32);
	priv->omsg_ring[mbox].wr_count = 0;
	mb();

	/* Initialize Outbound Message engine */
	ioग_लिखो32(TSI721_OBDMAC_CTL_RETRY_THR | TSI721_OBDMAC_CTL_INIT,
		  priv->regs + TSI721_OBDMAC_CTL(mbox));
	ioपढ़ो32(priv->regs + TSI721_OBDMAC_DWRCNT(mbox));
	udelay(10);

	priv->omsg_init[mbox] = 1;

	वापस 0;

#अगर_घोषित CONFIG_PCI_MSI
out_stat:
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->omsg_ring[mbox].sts_size * माप(काष्ठा tsi721_dma_sts),
		priv->omsg_ring[mbox].sts_base,
		priv->omsg_ring[mbox].sts_phys);

	priv->omsg_ring[mbox].sts_base = शून्य;
#पूर्ण_अगर /* CONFIG_PCI_MSI */

out_desc:
	dma_मुक्त_coherent(&priv->pdev->dev,
		(entries + 1) * माप(काष्ठा tsi721_omsg_desc),
		priv->omsg_ring[mbox].omd_base,
		priv->omsg_ring[mbox].omd_phys);

	priv->omsg_ring[mbox].omd_base = शून्य;

out_buf:
	क्रम (i = 0; i < priv->omsg_ring[mbox].size; i++) अणु
		अगर (priv->omsg_ring[mbox].omq_base[i]) अणु
			dma_मुक्त_coherent(&priv->pdev->dev,
				TSI721_MSG_BUFFER_SIZE,
				priv->omsg_ring[mbox].omq_base[i],
				priv->omsg_ring[mbox].omq_phys[i]);

			priv->omsg_ring[mbox].omq_base[i] = शून्य;
		पूर्ण
	पूर्ण

out:
	वापस rc;
पूर्ण

/**
 * tsi721_बंद_outb_mbox - Close Tsi721 outbound mailbox
 * @mport: Master port implementing the outbound message unit
 * @mbox: Mailbox to बंद
 */
अटल व्योम tsi721_बंद_outb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 i;

	अगर (!priv->omsg_init[mbox])
		वापस;
	priv->omsg_init[mbox] = 0;

	/* Disable Interrupts */

	tsi721_omsg_पूर्णांकerrupt_disable(priv, mbox, TSI721_OBDMAC_INT_ALL);

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		मुक्त_irq(priv->msix[TSI721_VECT_OMB0_DONE + mbox].vector,
			 (व्योम *)priv);
		मुक्त_irq(priv->msix[TSI721_VECT_OMB0_INT + mbox].vector,
			 (व्योम *)priv);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	/* Free OMSG Descriptor Status FIFO */
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->omsg_ring[mbox].sts_size * माप(काष्ठा tsi721_dma_sts),
		priv->omsg_ring[mbox].sts_base,
		priv->omsg_ring[mbox].sts_phys);

	priv->omsg_ring[mbox].sts_base = शून्य;

	/* Free OMSG descriptors */
	dma_मुक्त_coherent(&priv->pdev->dev,
		(priv->omsg_ring[mbox].size + 1) *
			माप(काष्ठा tsi721_omsg_desc),
		priv->omsg_ring[mbox].omd_base,
		priv->omsg_ring[mbox].omd_phys);

	priv->omsg_ring[mbox].omd_base = शून्य;

	/* Free message buffers */
	क्रम (i = 0; i < priv->omsg_ring[mbox].size; i++) अणु
		अगर (priv->omsg_ring[mbox].omq_base[i]) अणु
			dma_मुक्त_coherent(&priv->pdev->dev,
				TSI721_MSG_BUFFER_SIZE,
				priv->omsg_ring[mbox].omq_base[i],
				priv->omsg_ring[mbox].omq_phys[i]);

			priv->omsg_ring[mbox].omq_base[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * tsi721_imsg_handler - Inbound Message Interrupt Handler
 * @priv: poपूर्णांकer to tsi721 निजी data
 * @ch: inbound message channel number to service
 *
 * Services channel पूर्णांकerrupts from inbound messaging engine.
 */
अटल व्योम tsi721_imsg_handler(काष्ठा tsi721_device *priv, पूर्णांक ch)
अणु
	u32 mbox = ch - 4;
	u32 imsg_पूर्णांक;
	काष्ठा rio_mport *mport = &priv->mport;

	spin_lock(&priv->imsg_ring[mbox].lock);

	imsg_पूर्णांक = ioपढ़ो32(priv->regs + TSI721_IBDMAC_INT(ch));

	अगर (imsg_पूर्णांक & TSI721_IBDMAC_INT_SRTO)
		tsi_info(&priv->pdev->dev, "IB MBOX%d SRIO timeout", mbox);

	अगर (imsg_पूर्णांक & TSI721_IBDMAC_INT_PC_ERROR)
		tsi_info(&priv->pdev->dev, "IB MBOX%d PCIe error", mbox);

	अगर (imsg_पूर्णांक & TSI721_IBDMAC_INT_FQ_LOW)
		tsi_info(&priv->pdev->dev, "IB MBOX%d IB free queue low", mbox);

	/* Clear IB channel पूर्णांकerrupts */
	ioग_लिखो32(imsg_पूर्णांक, priv->regs + TSI721_IBDMAC_INT(ch));

	/* If an IB Msg is received notअगरy the upper layer */
	अगर (imsg_पूर्णांक & TSI721_IBDMAC_INT_DQ_RCV &&
		mport->inb_msg[mbox].mcback)
		mport->inb_msg[mbox].mcback(mport,
				priv->imsg_ring[mbox].dev_id, mbox, -1);

	अगर (!(priv->flags & TSI721_USING_MSIX)) अणु
		u32 ch_पूर्णांकe;

		/* Re-enable channel पूर्णांकerrupts */
		ch_पूर्णांकe = ioपढ़ो32(priv->regs + TSI721_DEV_CHAN_INTE);
		ch_पूर्णांकe |= TSI721_INT_IMSG_CHAN(ch);
		ioग_लिखो32(ch_पूर्णांकe, priv->regs + TSI721_DEV_CHAN_INTE);
	पूर्ण

	spin_unlock(&priv->imsg_ring[mbox].lock);
पूर्ण

/**
 * tsi721_खोलो_inb_mbox - Initialize Tsi721 inbound mailbox
 * @mport: Master port implementing the Inbound Messaging Engine
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox to खोलो
 * @entries: Number of entries in the inbound mailbox ring
 */
अटल पूर्णांक tsi721_खोलो_inb_mbox(काष्ठा rio_mport *mport, व्योम *dev_id,
				पूर्णांक mbox, पूर्णांक entries)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	पूर्णांक ch = mbox + 4;
	पूर्णांक i;
	u64 *मुक्त_ptr;
	पूर्णांक rc = 0;

	अगर ((entries < TSI721_IMSGD_MIN_RING_SIZE) ||
	    (entries > TSI721_IMSGD_RING_SIZE) ||
	    (!is_घातer_of_2(entries)) || mbox >= RIO_MAX_MBOX) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((mbox_sel & (1 << mbox)) == 0) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	/* Initialize IB Messaging Ring */
	priv->imsg_ring[mbox].dev_id = dev_id;
	priv->imsg_ring[mbox].size = entries;
	priv->imsg_ring[mbox].rx_slot = 0;
	priv->imsg_ring[mbox].desc_rdptr = 0;
	priv->imsg_ring[mbox].fq_wrptr = 0;
	क्रम (i = 0; i < priv->imsg_ring[mbox].size; i++)
		priv->imsg_ring[mbox].imq_base[i] = शून्य;
	spin_lock_init(&priv->imsg_ring[mbox].lock);

	/* Allocate buffers क्रम incoming messages */
	priv->imsg_ring[mbox].buf_base =
		dma_alloc_coherent(&priv->pdev->dev,
				   entries * TSI721_MSG_BUFFER_SIZE,
				   &priv->imsg_ring[mbox].buf_phys,
				   GFP_KERNEL);

	अगर (priv->imsg_ring[mbox].buf_base == शून्य) अणु
		tsi_err(&priv->pdev->dev,
			"Failed to allocate buffers for IB MBOX%d", mbox);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Allocate memory क्रम circular मुक्त list */
	priv->imsg_ring[mbox].imfq_base =
		dma_alloc_coherent(&priv->pdev->dev,
				   entries * 8,
				   &priv->imsg_ring[mbox].imfq_phys,
				   GFP_KERNEL);

	अगर (priv->imsg_ring[mbox].imfq_base == शून्य) अणु
		tsi_err(&priv->pdev->dev,
			"Failed to allocate free queue for IB MBOX%d", mbox);
		rc = -ENOMEM;
		जाओ out_buf;
	पूर्ण

	/* Allocate memory क्रम Inbound message descriptors */
	priv->imsg_ring[mbox].imd_base =
		dma_alloc_coherent(&priv->pdev->dev,
				   entries * माप(काष्ठा tsi721_imsg_desc),
				   &priv->imsg_ring[mbox].imd_phys, GFP_KERNEL);

	अगर (priv->imsg_ring[mbox].imd_base == शून्य) अणु
		tsi_err(&priv->pdev->dev,
			"Failed to allocate descriptor memory for IB MBOX%d",
			mbox);
		rc = -ENOMEM;
		जाओ out_dma;
	पूर्ण

	/* Fill मुक्त buffer poपूर्णांकer list */
	मुक्त_ptr = priv->imsg_ring[mbox].imfq_base;
	क्रम (i = 0; i < entries; i++)
		मुक्त_ptr[i] = cpu_to_le64(
				(u64)(priv->imsg_ring[mbox].buf_phys) +
				i * 0x1000);

	mb();

	/*
	 * For mapping of inbound SRIO Messages पूर्णांकo appropriate queues we need
	 * to set Inbound Device ID रेजिस्टर in the messaging engine. We करो it
	 * once when first inbound mailbox is requested.
	 */
	अगर (!(priv->flags & TSI721_IMSGID_SET)) अणु
		ioग_लिखो32((u32)priv->mport.host_deviceid,
			priv->regs + TSI721_IB_DEVID);
		priv->flags |= TSI721_IMSGID_SET;
	पूर्ण

	/*
	 * Configure Inbound Messaging channel (ch = mbox + 4)
	 */

	/* Setup Inbound Message मुक्त queue */
	ioग_लिखो32(((u64)priv->imsg_ring[mbox].imfq_phys >> 32),
		priv->regs + TSI721_IBDMAC_FQBH(ch));
	ioग_लिखो32(((u64)priv->imsg_ring[mbox].imfq_phys &
			TSI721_IBDMAC_FQBL_MASK),
		priv->regs+TSI721_IBDMAC_FQBL(ch));
	ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(entries),
		priv->regs + TSI721_IBDMAC_FQSZ(ch));

	/* Setup Inbound Message descriptor queue */
	ioग_लिखो32(((u64)priv->imsg_ring[mbox].imd_phys >> 32),
		priv->regs + TSI721_IBDMAC_DQBH(ch));
	ioग_लिखो32(((u32)priv->imsg_ring[mbox].imd_phys &
		   (u32)TSI721_IBDMAC_DQBL_MASK),
		priv->regs+TSI721_IBDMAC_DQBL(ch));
	ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(entries),
		priv->regs + TSI721_IBDMAC_DQSZ(ch));

	/* Enable पूर्णांकerrupts */

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		पूर्णांक idx = TSI721_VECT_IMB0_RCV + mbox;

		/* Request पूर्णांकerrupt service अगर we are in MSI-X mode */
		rc = request_irq(priv->msix[idx].vector, tsi721_imsg_msix, 0,
				 priv->msix[idx].irq_name, (व्योम *)priv);

		अगर (rc) अणु
			tsi_debug(IMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for IBOX%d-DONE",
				mbox);
			जाओ out_desc;
		पूर्ण

		idx = TSI721_VECT_IMB0_INT + mbox;
		rc = request_irq(priv->msix[idx].vector, tsi721_imsg_msix, 0,
				 priv->msix[idx].irq_name, (व्योम *)priv);

		अगर (rc)	अणु
			tsi_debug(IMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for IBOX%d-INT", mbox);
			मुक्त_irq(
				priv->msix[TSI721_VECT_IMB0_RCV + mbox].vector,
				(व्योम *)priv);
			जाओ out_desc;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	tsi721_imsg_पूर्णांकerrupt_enable(priv, ch, TSI721_IBDMAC_INT_ALL);

	/* Initialize Inbound Message Engine */
	ioग_लिखो32(TSI721_IBDMAC_CTL_INIT, priv->regs + TSI721_IBDMAC_CTL(ch));
	ioपढ़ो32(priv->regs + TSI721_IBDMAC_CTL(ch));
	udelay(10);
	priv->imsg_ring[mbox].fq_wrptr = entries - 1;
	ioग_लिखो32(entries - 1, priv->regs + TSI721_IBDMAC_FQWP(ch));

	priv->imsg_init[mbox] = 1;
	वापस 0;

#अगर_घोषित CONFIG_PCI_MSI
out_desc:
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * माप(काष्ठा tsi721_imsg_desc),
		priv->imsg_ring[mbox].imd_base,
		priv->imsg_ring[mbox].imd_phys);

	priv->imsg_ring[mbox].imd_base = शून्य;
#पूर्ण_अगर /* CONFIG_PCI_MSI */

out_dma:
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * 8,
		priv->imsg_ring[mbox].imfq_base,
		priv->imsg_ring[mbox].imfq_phys);

	priv->imsg_ring[mbox].imfq_base = शून्य;

out_buf:
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * TSI721_MSG_BUFFER_SIZE,
		priv->imsg_ring[mbox].buf_base,
		priv->imsg_ring[mbox].buf_phys);

	priv->imsg_ring[mbox].buf_base = शून्य;

out:
	वापस rc;
पूर्ण

/**
 * tsi721_बंद_inb_mbox - Shut करोwn Tsi721 inbound mailbox
 * @mport: Master port implementing the Inbound Messaging Engine
 * @mbox: Mailbox to बंद
 */
अटल व्योम tsi721_बंद_inb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 rx_slot;
	पूर्णांक ch = mbox + 4;

	अगर (!priv->imsg_init[mbox]) /* mbox isn't initialized yet */
		वापस;
	priv->imsg_init[mbox] = 0;

	/* Disable Inbound Messaging Engine */

	/* Disable Interrupts */
	tsi721_imsg_पूर्णांकerrupt_disable(priv, ch, TSI721_OBDMAC_INT_MASK);

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		मुक्त_irq(priv->msix[TSI721_VECT_IMB0_RCV + mbox].vector,
				(व्योम *)priv);
		मुक्त_irq(priv->msix[TSI721_VECT_IMB0_INT + mbox].vector,
				(व्योम *)priv);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	/* Clear Inbound Buffer Queue */
	क्रम (rx_slot = 0; rx_slot < priv->imsg_ring[mbox].size; rx_slot++)
		priv->imsg_ring[mbox].imq_base[rx_slot] = शून्य;

	/* Free memory allocated क्रम message buffers */
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * TSI721_MSG_BUFFER_SIZE,
		priv->imsg_ring[mbox].buf_base,
		priv->imsg_ring[mbox].buf_phys);

	priv->imsg_ring[mbox].buf_base = शून्य;

	/* Free memory allocated क्रम मुक्त poपूर्णांकr list */
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * 8,
		priv->imsg_ring[mbox].imfq_base,
		priv->imsg_ring[mbox].imfq_phys);

	priv->imsg_ring[mbox].imfq_base = शून्य;

	/* Free memory allocated क्रम RX descriptors */
	dma_मुक्त_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * माप(काष्ठा tsi721_imsg_desc),
		priv->imsg_ring[mbox].imd_base,
		priv->imsg_ring[mbox].imd_phys);

	priv->imsg_ring[mbox].imd_base = शून्य;
पूर्ण

/**
 * tsi721_add_inb_buffer - Add buffer to the Tsi721 inbound message queue
 * @mport: Master port implementing the Inbound Messaging Engine
 * @mbox: Inbound mailbox number
 * @buf: Buffer to add to inbound queue
 */
अटल पूर्णांक tsi721_add_inb_buffer(काष्ठा rio_mport *mport, पूर्णांक mbox, व्योम *buf)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 rx_slot;
	पूर्णांक rc = 0;

	rx_slot = priv->imsg_ring[mbox].rx_slot;
	अगर (priv->imsg_ring[mbox].imq_base[rx_slot]) अणु
		tsi_err(&priv->pdev->dev,
			"Error adding inbound buffer %d, buffer exists",
			rx_slot);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	priv->imsg_ring[mbox].imq_base[rx_slot] = buf;

	अगर (++priv->imsg_ring[mbox].rx_slot == priv->imsg_ring[mbox].size)
		priv->imsg_ring[mbox].rx_slot = 0;

out:
	वापस rc;
पूर्ण

/**
 * tsi721_get_inb_message - Fetch inbound message from the Tsi721 MSG Queue
 * @mport: Master port implementing the Inbound Messaging Engine
 * @mbox: Inbound mailbox number
 *
 * Returns poपूर्णांकer to the message on success or शून्य on failure.
 */
अटल व्योम *tsi721_get_inb_message(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	काष्ठा tsi721_imsg_desc *desc;
	u32 rx_slot;
	व्योम *rx_virt = शून्य;
	u64 rx_phys;
	व्योम *buf = शून्य;
	u64 *मुक्त_ptr;
	पूर्णांक ch = mbox + 4;
	पूर्णांक msg_size;

	अगर (!priv->imsg_init[mbox])
		वापस शून्य;

	desc = priv->imsg_ring[mbox].imd_base;
	desc += priv->imsg_ring[mbox].desc_rdptr;

	अगर (!(le32_to_cpu(desc->msg_info) & TSI721_IMD_HO))
		जाओ out;

	rx_slot = priv->imsg_ring[mbox].rx_slot;
	जबतक (priv->imsg_ring[mbox].imq_base[rx_slot] == शून्य) अणु
		अगर (++rx_slot == priv->imsg_ring[mbox].size)
			rx_slot = 0;
	पूर्ण

	rx_phys = ((u64)le32_to_cpu(desc->bufptr_hi) << 32) |
			le32_to_cpu(desc->bufptr_lo);

	rx_virt = priv->imsg_ring[mbox].buf_base +
		  (rx_phys - (u64)priv->imsg_ring[mbox].buf_phys);

	buf = priv->imsg_ring[mbox].imq_base[rx_slot];
	msg_size = le32_to_cpu(desc->msg_info) & TSI721_IMD_BCOUNT;
	अगर (msg_size == 0)
		msg_size = RIO_MAX_MSG_SIZE;

	स_नकल(buf, rx_virt, msg_size);
	priv->imsg_ring[mbox].imq_base[rx_slot] = शून्य;

	desc->msg_info &= cpu_to_le32(~TSI721_IMD_HO);
	अगर (++priv->imsg_ring[mbox].desc_rdptr == priv->imsg_ring[mbox].size)
		priv->imsg_ring[mbox].desc_rdptr = 0;

	ioग_लिखो32(priv->imsg_ring[mbox].desc_rdptr,
		priv->regs + TSI721_IBDMAC_DQRP(ch));

	/* Return मुक्त buffer पूर्णांकo the poपूर्णांकer list */
	मुक्त_ptr = priv->imsg_ring[mbox].imfq_base;
	मुक्त_ptr[priv->imsg_ring[mbox].fq_wrptr] = cpu_to_le64(rx_phys);

	अगर (++priv->imsg_ring[mbox].fq_wrptr == priv->imsg_ring[mbox].size)
		priv->imsg_ring[mbox].fq_wrptr = 0;

	ioग_लिखो32(priv->imsg_ring[mbox].fq_wrptr,
		priv->regs + TSI721_IBDMAC_FQWP(ch));
out:
	वापस buf;
पूर्ण

/**
 * tsi721_messages_init - Initialization of Messaging Engine
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Configures Tsi721 messaging engine.
 */
अटल पूर्णांक tsi721_messages_init(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक	ch;

	ioग_लिखो32(0, priv->regs + TSI721_SMSG_ECC_LOG);
	ioग_लिखो32(0, priv->regs + TSI721_RETRY_GEN_CNT);
	ioग_लिखो32(0, priv->regs + TSI721_RETRY_RX_CNT);

	/* Set SRIO Message Request/Response Timeout */
	ioग_लिखो32(TSI721_RQRPTO_VAL, priv->regs + TSI721_RQRPTO);

	/* Initialize Inbound Messaging Engine Registers */
	क्रम (ch = 0; ch < TSI721_IMSG_CHNUM; ch++) अणु
		/* Clear पूर्णांकerrupt bits */
		ioग_लिखो32(TSI721_IBDMAC_INT_MASK,
			priv->regs + TSI721_IBDMAC_INT(ch));
		/* Clear Status */
		ioग_लिखो32(0, priv->regs + TSI721_IBDMAC_STS(ch));

		ioग_लिखो32(TSI721_SMSG_ECC_COR_LOG_MASK,
				priv->regs + TSI721_SMSG_ECC_COR_LOG(ch));
		ioग_लिखो32(TSI721_SMSG_ECC_NCOR_MASK,
				priv->regs + TSI721_SMSG_ECC_NCOR(ch));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tsi721_query_mport - Fetch inbound message from the Tsi721 MSG Queue
 * @mport: Master port implementing the Inbound Messaging Engine
 * @mbox: Inbound mailbox number
 *
 * Returns poपूर्णांकer to the message on success or शून्य on failure.
 */
अटल पूर्णांक tsi721_query_mport(काष्ठा rio_mport *mport,
			      काष्ठा rio_mport_attr *attr)
अणु
	काष्ठा tsi721_device *priv = mport->priv;
	u32 rval;

	rval = ioपढ़ो32(priv->regs + 0x100 + RIO_PORT_N_ERR_STS_CSR(0, 0));
	अगर (rval & RIO_PORT_N_ERR_STS_PORT_OK) अणु
		rval = ioपढ़ो32(priv->regs + 0x100 + RIO_PORT_N_CTL2_CSR(0, 0));
		attr->link_speed = (rval & RIO_PORT_N_CTL2_SEL_BAUD) >> 28;
		rval = ioपढ़ो32(priv->regs + 0x100 + RIO_PORT_N_CTL_CSR(0, 0));
		attr->link_width = (rval & RIO_PORT_N_CTL_IPW) >> 27;
	पूर्ण अन्यथा
		attr->link_speed = RIO_LINK_DOWN;

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	attr->flags = RIO_MPORT_DMA | RIO_MPORT_DMA_SG;
	attr->dma_max_sge = 0;
	attr->dma_max_size = TSI721_BDMA_MAX_BCOUNT;
	attr->dma_align = 0;
#अन्यथा
	attr->flags = 0;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * tsi721_disable_पूर्णांकs - disables all device पूर्णांकerrupts
 * @priv: poपूर्णांकer to tsi721 निजी data
 */
अटल व्योम tsi721_disable_पूर्णांकs(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक ch;

	/* Disable all device level पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_DEV_INTE);

	/* Disable all Device Channel पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_DEV_CHAN_INTE);

	/* Disable all Inbound Msg Channel पूर्णांकerrupts */
	क्रम (ch = 0; ch < TSI721_IMSG_CHNUM; ch++)
		ioग_लिखो32(0, priv->regs + TSI721_IBDMAC_INTE(ch));

	/* Disable all Outbound Msg Channel पूर्णांकerrupts */
	क्रम (ch = 0; ch < TSI721_OMSG_CHNUM; ch++)
		ioग_लिखो32(0, priv->regs + TSI721_OBDMAC_INTE(ch));

	/* Disable all general messaging पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_SMSG_INTE);

	/* Disable all BDMA Channel पूर्णांकerrupts */
	क्रम (ch = 0; ch < TSI721_DMA_MAXCH; ch++)
		ioग_लिखो32(0,
			priv->regs + TSI721_DMAC_BASE(ch) + TSI721_DMAC_INTE);

	/* Disable all general BDMA पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_BDMA_INTE);

	/* Disable all SRIO Channel पूर्णांकerrupts */
	क्रम (ch = 0; ch < TSI721_SRIO_MAXCH; ch++)
		ioग_लिखो32(0, priv->regs + TSI721_SR_CHINTE(ch));

	/* Disable all general SR2PC पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_SR2PC_GEN_INTE);

	/* Disable all PC2SR पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_PC2SR_INTE);

	/* Disable all I2C पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_I2C_INT_ENABLE);

	/* Disable SRIO MAC पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + TSI721_RIO_EM_INT_ENABLE);
	ioग_लिखो32(0, priv->regs + TSI721_RIO_EM_DEV_INT_EN);
पूर्ण

अटल काष्ठा rio_ops tsi721_rio_ops = अणु
	.lcपढ़ो			= tsi721_lcपढ़ो,
	.lcग_लिखो		= tsi721_lcग_लिखो,
	.cपढ़ो			= tsi721_cपढ़ो_dma,
	.cग_लिखो			= tsi721_cग_लिखो_dma,
	.dsend			= tsi721_dsend,
	.खोलो_inb_mbox		= tsi721_खोलो_inb_mbox,
	.बंद_inb_mbox		= tsi721_बंद_inb_mbox,
	.खोलो_outb_mbox		= tsi721_खोलो_outb_mbox,
	.बंद_outb_mbox	= tsi721_बंद_outb_mbox,
	.add_outb_message	= tsi721_add_outb_message,
	.add_inb_buffer		= tsi721_add_inb_buffer,
	.get_inb_message	= tsi721_get_inb_message,
	.map_inb		= tsi721_rio_map_inb_mem,
	.unmap_inb		= tsi721_rio_unmap_inb_mem,
	.pwenable		= tsi721_pw_enable,
	.query_mport		= tsi721_query_mport,
	.map_outb		= tsi721_map_outb_win,
	.unmap_outb		= tsi721_unmap_outb_win,
पूर्ण;

अटल व्योम tsi721_mport_release(काष्ठा device *dev)
अणु
	काष्ठा rio_mport *mport = to_rio_mport(dev);

	tsi_debug(EXIT, dev, "%s id=%d", mport->name, mport->id);
पूर्ण

/**
 * tsi721_setup_mport - Setup Tsi721 as RapidIO subप्रणाली master port
 * @priv: poपूर्णांकer to tsi721 निजी data
 *
 * Configures Tsi721 as RapidIO master port.
 */
अटल पूर्णांक tsi721_setup_mport(काष्ठा tsi721_device *priv)
अणु
	काष्ठा pci_dev *pdev = priv->pdev;
	पूर्णांक err = 0;
	काष्ठा rio_mport *mport = &priv->mport;

	err = rio_mport_initialize(mport);
	अगर (err)
		वापस err;

	mport->ops = &tsi721_rio_ops;
	mport->index = 0;
	mport->sys_size = 0; /* small प्रणाली */
	mport->priv = (व्योम *)priv;
	mport->phys_efptr = 0x100;
	mport->phys_rmap = 1;
	mport->dev.parent = &pdev->dev;
	mport->dev.release = tsi721_mport_release;

	INIT_LIST_HEAD(&mport->dbells);

	rio_init_dbell_res(&mport->riores[RIO_DOORBELL_RESOURCE], 0, 0xffff);
	rio_init_mbox_res(&mport->riores[RIO_INB_MBOX_RESOURCE], 0, 3);
	rio_init_mbox_res(&mport->riores[RIO_OUTB_MBOX_RESOURCE], 0, 3);
	snम_लिखो(mport->name, RIO_MAX_MPORT_NAME, "%s(%s)",
		 dev_driver_string(&pdev->dev), dev_name(&pdev->dev));

	/* Hook up पूर्णांकerrupt handler */

#अगर_घोषित CONFIG_PCI_MSI
	अगर (!tsi721_enable_msix(priv))
		priv->flags |= TSI721_USING_MSIX;
	अन्यथा अगर (!pci_enable_msi(pdev))
		priv->flags |= TSI721_USING_MSI;
	अन्यथा
		tsi_debug(MPORT, &pdev->dev,
			 "MSI/MSI-X is not available. Using legacy INTx.");
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	err = tsi721_request_irq(priv);

	अगर (err) अणु
		tsi_err(&pdev->dev, "Unable to get PCI IRQ %02X (err=0x%x)",
			pdev->irq, err);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	err = tsi721_रेजिस्टर_dma(priv);
	अगर (err)
		जाओ err_निकास;
#पूर्ण_अगर
	/* Enable SRIO link */
	ioग_लिखो32(ioपढ़ो32(priv->regs + TSI721_DEVCTL) |
		  TSI721_DEVCTL_SRBOOT_CMPL,
		  priv->regs + TSI721_DEVCTL);

	अगर (mport->host_deviceid >= 0)
		ioग_लिखो32(RIO_PORT_GEN_HOST | RIO_PORT_GEN_MASTER |
			  RIO_PORT_GEN_DISCOVERED,
			  priv->regs + (0x100 + RIO_PORT_GEN_CTL_CSR));
	अन्यथा
		ioग_लिखो32(0, priv->regs + (0x100 + RIO_PORT_GEN_CTL_CSR));

	err = rio_रेजिस्टर_mport(mport);
	अगर (err) अणु
		tsi721_unरेजिस्टर_dma(priv);
		जाओ err_निकास;
	पूर्ण

	वापस 0;

err_निकास:
	tsi721_मुक्त_irq(priv);
	वापस err;
पूर्ण

अटल पूर्णांक tsi721_probe(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा tsi721_device *priv;
	पूर्णांक err;

	priv = kzalloc(माप(काष्ठा tsi721_device), GFP_KERNEL);
	अगर (!priv) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		tsi_err(&pdev->dev, "Failed to enable PCI device");
		जाओ err_clean;
	पूर्ण

	priv->pdev = pdev;

#अगर_घोषित DEBUG
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
			tsi_debug(INIT, &pdev->dev, "res%d %pR",
				  i, &pdev->resource[i]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/*
	 * Verअगरy BAR configuration
	 */

	/* BAR_0 (रेजिस्टरs) must be 512KB+ in 32-bit address space */
	अगर (!(pci_resource_flags(pdev, BAR_0) & IORESOURCE_MEM) ||
	    pci_resource_flags(pdev, BAR_0) & IORESOURCE_MEM_64 ||
	    pci_resource_len(pdev, BAR_0) < TSI721_REG_SPACE_SIZE) अणु
		tsi_err(&pdev->dev, "Missing or misconfigured CSR BAR0");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण

	/* BAR_1 (outbound करोorbells) must be 16MB+ in 32-bit address space */
	अगर (!(pci_resource_flags(pdev, BAR_1) & IORESOURCE_MEM) ||
	    pci_resource_flags(pdev, BAR_1) & IORESOURCE_MEM_64 ||
	    pci_resource_len(pdev, BAR_1) < TSI721_DB_WIN_SIZE) अणु
		tsi_err(&pdev->dev, "Missing or misconfigured Doorbell BAR1");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण

	/*
	 * BAR_2 and BAR_4 (outbound translation) must be in 64-bit PCIe address
	 * space.
	 * NOTE: BAR_2 and BAR_4 are not used by this version of driver.
	 * It may be a good idea to keep them disabled using HW configuration
	 * to save PCI memory space.
	 */

	priv->p2r_bar[0].size = priv->p2r_bar[1].size = 0;

	अगर (pci_resource_flags(pdev, BAR_2) & IORESOURCE_MEM_64) अणु
		अगर (pci_resource_flags(pdev, BAR_2) & IORESOURCE_PREFETCH)
			tsi_debug(INIT, &pdev->dev,
				 "Prefetchable OBW BAR2 will not be used");
		अन्यथा अणु
			priv->p2r_bar[0].base = pci_resource_start(pdev, BAR_2);
			priv->p2r_bar[0].size = pci_resource_len(pdev, BAR_2);
		पूर्ण
	पूर्ण

	अगर (pci_resource_flags(pdev, BAR_4) & IORESOURCE_MEM_64) अणु
		अगर (pci_resource_flags(pdev, BAR_4) & IORESOURCE_PREFETCH)
			tsi_debug(INIT, &pdev->dev,
				 "Prefetchable OBW BAR4 will not be used");
		अन्यथा अणु
			priv->p2r_bar[1].base = pci_resource_start(pdev, BAR_4);
			priv->p2r_bar[1].size = pci_resource_len(pdev, BAR_4);
		पूर्ण
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		tsi_err(&pdev->dev, "Unable to obtain PCI resources");
		जाओ err_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	priv->regs = pci_ioremap_bar(pdev, BAR_0);
	अगर (!priv->regs) अणु
		tsi_err(&pdev->dev, "Unable to map device registers space");
		err = -ENOMEM;
		जाओ err_मुक्त_res;
	पूर्ण

	priv->odb_base = pci_ioremap_bar(pdev, BAR_1);
	अगर (!priv->odb_base) अणु
		tsi_err(&pdev->dev, "Unable to map outbound doorbells space");
		err = -ENOMEM;
		जाओ err_unmap_bars;
	पूर्ण

	/* Configure DMA attributes. */
	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			tsi_err(&pdev->dev, "Unable to set DMA mask");
			जाओ err_unmap_bars;
		पूर्ण

		अगर (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32)))
			tsi_info(&pdev->dev, "Unable to set consistent DMA mask");
	पूर्ण अन्यथा अणु
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (err)
			tsi_info(&pdev->dev, "Unable to set consistent DMA mask");
	पूर्ण

	BUG_ON(!pci_is_pcie(pdev));

	/* Clear "no snoop" and "relaxed ordering" bits. */
	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
		PCI_EXP_DEVCTL_RELAX_EN | PCI_EXP_DEVCTL_NOSNOOP_EN, 0);

	/* Override PCIe Maximum Read Request Size setting अगर requested */
	अगर (pcie_mrrs >= 0) अणु
		अगर (pcie_mrrs <= 5)
			pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
					PCI_EXP_DEVCTL_READRQ, pcie_mrrs << 12);
		अन्यथा
			tsi_info(&pdev->dev,
				 "Invalid MRRS override value %d", pcie_mrrs);
	पूर्ण

	/* Set PCIe completion समयout to 1-10ms */
	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL2,
					   PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0x2);

	/*
	 * FIXUP: correct offsets of MSI-X tables in the MSI-X Capability Block
	 */
	pci_ग_लिखो_config_dword(pdev, TSI721_PCIECFG_EPCTL, 0x01);
	pci_ग_लिखो_config_dword(pdev, TSI721_PCIECFG_MSIXTBL,
						TSI721_MSIXTBL_OFFSET);
	pci_ग_लिखो_config_dword(pdev, TSI721_PCIECFG_MSIXPBA,
						TSI721_MSIXPBA_OFFSET);
	pci_ग_लिखो_config_dword(pdev, TSI721_PCIECFG_EPCTL, 0);
	/* End of FIXUP */

	tsi721_disable_पूर्णांकs(priv);

	tsi721_init_pc2sr_mapping(priv);
	tsi721_init_sr2pc_mapping(priv);

	अगर (tsi721_bdma_मुख्यt_init(priv)) अणु
		tsi_err(&pdev->dev, "BDMA initialization failed");
		err = -ENOMEM;
		जाओ err_unmap_bars;
	पूर्ण

	err = tsi721_करोorbell_init(priv);
	अगर (err)
		जाओ err_मुक्त_bdma;

	tsi721_port_ग_लिखो_init(priv);

	err = tsi721_messages_init(priv);
	अगर (err)
		जाओ err_मुक्त_consistent;

	err = tsi721_setup_mport(priv);
	अगर (err)
		जाओ err_मुक्त_consistent;

	pci_set_drvdata(pdev, priv);
	tsi721_पूर्णांकerrupts_init(priv);

	वापस 0;

err_मुक्त_consistent:
	tsi721_port_ग_लिखो_मुक्त(priv);
	tsi721_करोorbell_मुक्त(priv);
err_मुक्त_bdma:
	tsi721_bdma_मुख्यt_मुक्त(priv);
err_unmap_bars:
	अगर (priv->regs)
		iounmap(priv->regs);
	अगर (priv->odb_base)
		iounmap(priv->odb_base);
err_मुक्त_res:
	pci_release_regions(pdev);
	pci_clear_master(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
err_clean:
	kमुक्त(priv);
err_निकास:
	वापस err;
पूर्ण

अटल व्योम tsi721_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा tsi721_device *priv = pci_get_drvdata(pdev);

	tsi_debug(EXIT, &pdev->dev, "enter");

	tsi721_disable_पूर्णांकs(priv);
	tsi721_मुक्त_irq(priv);
	flush_scheduled_work();
	rio_unरेजिस्टर_mport(&priv->mport);

	tsi721_unरेजिस्टर_dma(priv);
	tsi721_bdma_मुख्यt_मुक्त(priv);
	tsi721_करोorbell_मुक्त(priv);
	tsi721_port_ग_लिखो_मुक्त(priv);
	tsi721_बंद_sr2pc_mapping(priv);

	अगर (priv->regs)
		iounmap(priv->regs);
	अगर (priv->odb_base)
		iounmap(priv->odb_base);
#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX)
		pci_disable_msix(priv->pdev);
	अन्यथा अगर (priv->flags & TSI721_USING_MSI)
		pci_disable_msi(priv->pdev);
#पूर्ण_अगर
	pci_release_regions(pdev);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	kमुक्त(priv);
	tsi_debug(EXIT, &pdev->dev, "exit");
पूर्ण

अटल व्योम tsi721_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा tsi721_device *priv = pci_get_drvdata(pdev);

	tsi_debug(EXIT, &pdev->dev, "enter");

	tsi721_disable_पूर्णांकs(priv);
	tsi721_dma_stop_all(priv);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id tsi721_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_IDT, PCI_DEVICE_ID_TSI721) पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(pci, tsi721_pci_tbl);

अटल काष्ठा pci_driver tsi721_driver = अणु
	.name		= "tsi721",
	.id_table	= tsi721_pci_tbl,
	.probe		= tsi721_probe,
	.हटाओ		= tsi721_हटाओ,
	.shutकरोwn	= tsi721_shutकरोwn,
पूर्ण;

module_pci_driver(tsi721_driver);

MODULE_DESCRIPTION("IDT Tsi721 PCIExpress-to-SRIO bridge driver");
MODULE_AUTHOR("Integrated Device Technology, Inc.");
MODULE_LICENSE("GPL");
