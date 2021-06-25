<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the HP iLO management processor.
 *
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	David Altobelli <david.altobelli@hpe.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/cdev.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश "hpilo.h"

अटल काष्ठा class *ilo_class;
अटल अचिन्हित पूर्णांक ilo_major;
अटल अचिन्हित पूर्णांक max_ccb = 16;
अटल अक्षर ilo_hwdev[MAX_ILO_DEV];
अटल स्थिर काष्ठा pci_device_id ilo_blacklist[] = अणु
	/* auxiliary iLO */
	अणुPCI_DEVICE_SUB(PCI_VENDOR_ID_HP, 0x3307, PCI_VENDOR_ID_HP, 0x1979)पूर्ण,
	/* CL */
	अणुPCI_DEVICE_SUB(PCI_VENDOR_ID_HP, 0x3307, PCI_VENDOR_ID_HP_3PAR, 0x0289)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक get_entry_id(पूर्णांक entry)
अणु
	वापस (entry & ENTRY_MASK_DESCRIPTOR) >> ENTRY_BITPOS_DESCRIPTOR;
पूर्ण

अटल अंतरभूत पूर्णांक get_entry_len(पूर्णांक entry)
अणु
	वापस ((entry & ENTRY_MASK_QWORDS) >> ENTRY_BITPOS_QWORDS) << 3;
पूर्ण

अटल अंतरभूत पूर्णांक mk_entry(पूर्णांक id, पूर्णांक len)
अणु
	पूर्णांक qlen = len & 7 ? (len >> 3) + 1 : len >> 3;
	वापस id << ENTRY_BITPOS_DESCRIPTOR | qlen << ENTRY_BITPOS_QWORDS;
पूर्ण

अटल अंतरभूत पूर्णांक desc_mem_sz(पूर्णांक nr_entry)
अणु
	वापस nr_entry << L2_QENTRY_SZ;
पूर्ण

/*
 * FIFO queues, shared with hardware.
 *
 * If a queue has empty slots, an entry is added to the queue tail,
 * and that entry is marked as occupied.
 * Entries can be dequeued from the head of the list, when the device
 * has marked the entry as consumed.
 *
 * Returns true on successful queue/dequeue, false on failure.
 */
अटल पूर्णांक fअगरo_enqueue(काष्ठा ilo_hwinfo *hw, अक्षर *fअगरobar, पूर्णांक entry)
अणु
	काष्ठा fअगरo *fअगरo_q = FIFOBARTOHANDLE(fअगरobar);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hw->fअगरo_lock, flags);
	अगर (!(fअगरo_q->fअगरobar[(fअगरo_q->tail + 1) & fअगरo_q->imask]
	      & ENTRY_MASK_O)) अणु
		fअगरo_q->fअगरobar[fअगरo_q->tail & fअगरo_q->imask] |=
				(entry & ENTRY_MASK_NOSTATE) | fअगरo_q->merge;
		fअगरo_q->tail += 1;
		ret = 1;
	पूर्ण
	spin_unlock_irqrestore(&hw->fअगरo_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक fअगरo_dequeue(काष्ठा ilo_hwinfo *hw, अक्षर *fअगरobar, पूर्णांक *entry)
अणु
	काष्ठा fअगरo *fअगरo_q = FIFOBARTOHANDLE(fअगरobar);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u64 c;

	spin_lock_irqsave(&hw->fअगरo_lock, flags);
	c = fअगरo_q->fअगरobar[fअगरo_q->head & fअगरo_q->imask];
	अगर (c & ENTRY_MASK_C) अणु
		अगर (entry)
			*entry = c & ENTRY_MASK_NOSTATE;

		fअगरo_q->fअगरobar[fअगरo_q->head & fअगरo_q->imask] =
							(c | ENTRY_MASK) + 1;
		fअगरo_q->head += 1;
		ret = 1;
	पूर्ण
	spin_unlock_irqrestore(&hw->fअगरo_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक fअगरo_check_recv(काष्ठा ilo_hwinfo *hw, अक्षर *fअगरobar)
अणु
	काष्ठा fअगरo *fअगरo_q = FIFOBARTOHANDLE(fअगरobar);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u64 c;

	spin_lock_irqsave(&hw->fअगरo_lock, flags);
	c = fअगरo_q->fअगरobar[fअगरo_q->head & fअगरo_q->imask];
	अगर (c & ENTRY_MASK_C)
		ret = 1;
	spin_unlock_irqrestore(&hw->fअगरo_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक ilo_pkt_enqueue(काष्ठा ilo_hwinfo *hw, काष्ठा ccb *ccb,
			   पूर्णांक dir, पूर्णांक id, पूर्णांक len)
अणु
	अक्षर *fअगरobar;
	पूर्णांक entry;

	अगर (dir == SENDQ)
		fअगरobar = ccb->ccb_u1.send_fअगरobar;
	अन्यथा
		fअगरobar = ccb->ccb_u3.recv_fअगरobar;

	entry = mk_entry(id, len);
	वापस fअगरo_enqueue(hw, fअगरobar, entry);
पूर्ण

अटल पूर्णांक ilo_pkt_dequeue(काष्ठा ilo_hwinfo *hw, काष्ठा ccb *ccb,
			   पूर्णांक dir, पूर्णांक *id, पूर्णांक *len, व्योम **pkt)
अणु
	अक्षर *fअगरobar, *desc;
	पूर्णांक entry = 0, pkt_id = 0;
	पूर्णांक ret;

	अगर (dir == SENDQ) अणु
		fअगरobar = ccb->ccb_u1.send_fअगरobar;
		desc = ccb->ccb_u2.send_desc;
	पूर्ण अन्यथा अणु
		fअगरobar = ccb->ccb_u3.recv_fअगरobar;
		desc = ccb->ccb_u4.recv_desc;
	पूर्ण

	ret = fअगरo_dequeue(hw, fअगरobar, &entry);
	अगर (ret) अणु
		pkt_id = get_entry_id(entry);
		अगर (id)
			*id = pkt_id;
		अगर (len)
			*len = get_entry_len(entry);
		अगर (pkt)
			*pkt = (व्योम *)(desc + desc_mem_sz(pkt_id));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ilo_pkt_recv(काष्ठा ilo_hwinfo *hw, काष्ठा ccb *ccb)
अणु
	अक्षर *fअगरobar = ccb->ccb_u3.recv_fअगरobar;

	वापस fअगरo_check_recv(hw, fअगरobar);
पूर्ण

अटल अंतरभूत व्योम करोorbell_set(काष्ठा ccb *ccb)
अणु
	ioग_लिखो8(1, ccb->ccb_u5.db_base);
पूर्ण

अटल अंतरभूत व्योम करोorbell_clr(काष्ठा ccb *ccb)
अणु
	ioग_लिखो8(2, ccb->ccb_u5.db_base);
पूर्ण

अटल अंतरभूत पूर्णांक ctrl_set(पूर्णांक l2sz, पूर्णांक idxmask, पूर्णांक desclim)
अणु
	पूर्णांक active = 0, go = 1;
	वापस l2sz << CTRL_BITPOS_L2SZ |
	       idxmask << CTRL_BITPOS_FIFOINDEXMASK |
	       desclim << CTRL_BITPOS_DESCLIMIT |
	       active << CTRL_BITPOS_A |
	       go << CTRL_BITPOS_G;
पूर्ण

अटल व्योम ctrl_setup(काष्ठा ccb *ccb, पूर्णांक nr_desc, पूर्णांक l2desc_sz)
अणु
	/* क्रम simplicity, use the same parameters क्रम send and recv ctrls */
	ccb->send_ctrl = ctrl_set(l2desc_sz, nr_desc-1, nr_desc-1);
	ccb->recv_ctrl = ctrl_set(l2desc_sz, nr_desc-1, nr_desc-1);
पूर्ण

अटल अंतरभूत पूर्णांक fअगरo_sz(पूर्णांक nr_entry)
अणु
	/* size of a fअगरo is determined by the number of entries it contains */
	वापस nr_entry * माप(u64) + FIFOHANDLESIZE;
पूर्ण

अटल व्योम fअगरo_setup(व्योम *base_addr, पूर्णांक nr_entry)
अणु
	काष्ठा fअगरo *fअगरo_q = base_addr;
	पूर्णांक i;

	/* set up an empty fअगरo */
	fअगरo_q->head = 0;
	fअगरo_q->tail = 0;
	fअगरo_q->reset = 0;
	fअगरo_q->nrents = nr_entry;
	fअगरo_q->imask = nr_entry - 1;
	fअगरo_q->merge = ENTRY_MASK_O;

	क्रम (i = 0; i < nr_entry; i++)
		fअगरo_q->fअगरobar[i] = 0;
पूर्ण

अटल व्योम ilo_ccb_बंद(काष्ठा pci_dev *pdev, काष्ठा ccb_data *data)
अणु
	काष्ठा ccb *driver_ccb = &data->driver_ccb;
	काष्ठा ccb __iomem *device_ccb = data->mapped_ccb;
	पूर्णांक retries;

	/* complicated dance to tell the hw we are stopping */
	करोorbell_clr(driver_ccb);
	ioग_लिखो32(ioपढ़ो32(&device_ccb->send_ctrl) & ~(1 << CTRL_BITPOS_G),
		  &device_ccb->send_ctrl);
	ioग_लिखो32(ioपढ़ो32(&device_ccb->recv_ctrl) & ~(1 << CTRL_BITPOS_G),
		  &device_ccb->recv_ctrl);

	/* give iLO some समय to process stop request */
	क्रम (retries = MAX_WAIT; retries > 0; retries--) अणु
		करोorbell_set(driver_ccb);
		udelay(WAIT_TIME);
		अगर (!(ioपढ़ो32(&device_ccb->send_ctrl) & (1 << CTRL_BITPOS_A))
		    &&
		    !(ioपढ़ो32(&device_ccb->recv_ctrl) & (1 << CTRL_BITPOS_A)))
			अवरोध;
	पूर्ण
	अगर (retries == 0)
		dev_err(&pdev->dev, "Closing, but controller still active\n");

	/* clear the hw ccb */
	स_रखो_io(device_ccb, 0, माप(काष्ठा ccb));

	/* मुक्त resources used to back send/recv queues */
	dma_मुक्त_coherent(&pdev->dev, data->dma_size, data->dma_va,
			  data->dma_pa);
पूर्ण

अटल पूर्णांक ilo_ccb_setup(काष्ठा ilo_hwinfo *hw, काष्ठा ccb_data *data, पूर्णांक slot)
अणु
	अक्षर *dma_va;
	dma_addr_t dma_pa;
	काष्ठा ccb *driver_ccb, *ilo_ccb;

	driver_ccb = &data->driver_ccb;
	ilo_ccb = &data->ilo_ccb;

	data->dma_size = 2 * fअगरo_sz(NR_QENTRY) +
			 2 * desc_mem_sz(NR_QENTRY) +
			 ILO_START_ALIGN + ILO_CACHE_SZ;

	data->dma_va = dma_alloc_coherent(&hw->ilo_dev->dev, data->dma_size,
					  &data->dma_pa, GFP_ATOMIC);
	अगर (!data->dma_va)
		वापस -ENOMEM;

	dma_va = (अक्षर *)data->dma_va;
	dma_pa = data->dma_pa;

	dma_va = (अक्षर *)roundup((अचिन्हित दीर्घ)dma_va, ILO_START_ALIGN);
	dma_pa = roundup(dma_pa, ILO_START_ALIGN);

	/*
	 * Create two ccb's, one with virt addrs, one with phys addrs.
	 * Copy the phys addr ccb to device shared mem.
	 */
	ctrl_setup(driver_ccb, NR_QENTRY, L2_QENTRY_SZ);
	ctrl_setup(ilo_ccb, NR_QENTRY, L2_QENTRY_SZ);

	fअगरo_setup(dma_va, NR_QENTRY);
	driver_ccb->ccb_u1.send_fअगरobar = dma_va + FIFOHANDLESIZE;
	ilo_ccb->ccb_u1.send_fअगरobar_pa = dma_pa + FIFOHANDLESIZE;
	dma_va += fअगरo_sz(NR_QENTRY);
	dma_pa += fअगरo_sz(NR_QENTRY);

	dma_va = (अक्षर *)roundup((अचिन्हित दीर्घ)dma_va, ILO_CACHE_SZ);
	dma_pa = roundup(dma_pa, ILO_CACHE_SZ);

	fअगरo_setup(dma_va, NR_QENTRY);
	driver_ccb->ccb_u3.recv_fअगरobar = dma_va + FIFOHANDLESIZE;
	ilo_ccb->ccb_u3.recv_fअगरobar_pa = dma_pa + FIFOHANDLESIZE;
	dma_va += fअगरo_sz(NR_QENTRY);
	dma_pa += fअगरo_sz(NR_QENTRY);

	driver_ccb->ccb_u2.send_desc = dma_va;
	ilo_ccb->ccb_u2.send_desc_pa = dma_pa;
	dma_pa += desc_mem_sz(NR_QENTRY);
	dma_va += desc_mem_sz(NR_QENTRY);

	driver_ccb->ccb_u4.recv_desc = dma_va;
	ilo_ccb->ccb_u4.recv_desc_pa = dma_pa;

	driver_ccb->channel = slot;
	ilo_ccb->channel = slot;

	driver_ccb->ccb_u5.db_base = hw->db_vaddr + (slot << L2_DB_SIZE);
	ilo_ccb->ccb_u5.db_base = शून्य; /* hw ccb's करोorbell is not used */

	वापस 0;
पूर्ण

अटल व्योम ilo_ccb_खोलो(काष्ठा ilo_hwinfo *hw, काष्ठा ccb_data *data, पूर्णांक slot)
अणु
	पूर्णांक pkt_id, pkt_sz;
	काष्ठा ccb *driver_ccb = &data->driver_ccb;

	/* copy the ccb with physical addrs to device memory */
	data->mapped_ccb = (काष्ठा ccb __iomem *)
				(hw->ram_vaddr + (slot * ILOHW_CCB_SZ));
	स_नकल_toio(data->mapped_ccb, &data->ilo_ccb, माप(काष्ठा ccb));

	/* put packets on the send and receive queues */
	pkt_sz = 0;
	क्रम (pkt_id = 0; pkt_id < NR_QENTRY; pkt_id++) अणु
		ilo_pkt_enqueue(hw, driver_ccb, SENDQ, pkt_id, pkt_sz);
		करोorbell_set(driver_ccb);
	पूर्ण

	pkt_sz = desc_mem_sz(1);
	क्रम (pkt_id = 0; pkt_id < NR_QENTRY; pkt_id++)
		ilo_pkt_enqueue(hw, driver_ccb, RECVQ, pkt_id, pkt_sz);

	/* the ccb is पढ़ोy to use */
	करोorbell_clr(driver_ccb);
पूर्ण

अटल पूर्णांक ilo_ccb_verअगरy(काष्ठा ilo_hwinfo *hw, काष्ठा ccb_data *data)
अणु
	पूर्णांक pkt_id, i;
	काष्ठा ccb *driver_ccb = &data->driver_ccb;

	/* make sure iLO is really handling requests */
	क्रम (i = MAX_WAIT; i > 0; i--) अणु
		अगर (ilo_pkt_dequeue(hw, driver_ccb, SENDQ, &pkt_id, शून्य, शून्य))
			अवरोध;
		udelay(WAIT_TIME);
	पूर्ण

	अगर (i == 0) अणु
		dev_err(&hw->ilo_dev->dev, "Open could not dequeue a packet\n");
		वापस -EBUSY;
	पूर्ण

	ilo_pkt_enqueue(hw, driver_ccb, SENDQ, pkt_id, 0);
	करोorbell_set(driver_ccb);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_channel_reset(काष्ठा ccb *ccb)
अणु
	/* check क्रम this particular channel needing a reset */
	वापस FIFOBARTOHANDLE(ccb->ccb_u1.send_fअगरobar)->reset;
पूर्ण

अटल अंतरभूत व्योम set_channel_reset(काष्ठा ccb *ccb)
अणु
	/* set a flag indicating this channel needs a reset */
	FIFOBARTOHANDLE(ccb->ccb_u1.send_fअगरobar)->reset = 1;
पूर्ण

अटल अंतरभूत पूर्णांक get_device_outbound(काष्ठा ilo_hwinfo *hw)
अणु
	वापस ioपढ़ो32(&hw->mmio_vaddr[DB_OUT]);
पूर्ण

अटल अंतरभूत पूर्णांक is_db_reset(पूर्णांक db_out)
अणु
	वापस db_out & (1 << DB_RESET);
पूर्ण

अटल अंतरभूत पूर्णांक is_device_reset(काष्ठा ilo_hwinfo *hw)
अणु
	/* check क्रम global reset condition */
	वापस is_db_reset(get_device_outbound(hw));
पूर्ण

अटल अंतरभूत व्योम clear_pending_db(काष्ठा ilo_hwinfo *hw, पूर्णांक clr)
अणु
	ioग_लिखो32(clr, &hw->mmio_vaddr[DB_OUT]);
पूर्ण

अटल अंतरभूत व्योम clear_device(काष्ठा ilo_hwinfo *hw)
अणु
	/* clear the device (reset bits, pending channel entries) */
	clear_pending_db(hw, -1);
पूर्ण

अटल अंतरभूत व्योम ilo_enable_पूर्णांकerrupts(काष्ठा ilo_hwinfo *hw)
अणु
	ioग_लिखो8(ioपढ़ो8(&hw->mmio_vaddr[DB_IRQ]) | 1, &hw->mmio_vaddr[DB_IRQ]);
पूर्ण

अटल अंतरभूत व्योम ilo_disable_पूर्णांकerrupts(काष्ठा ilo_hwinfo *hw)
अणु
	ioग_लिखो8(ioपढ़ो8(&hw->mmio_vaddr[DB_IRQ]) & ~1,
		 &hw->mmio_vaddr[DB_IRQ]);
पूर्ण

अटल व्योम ilo_set_reset(काष्ठा ilo_hwinfo *hw)
अणु
	पूर्णांक slot;

	/*
	 * Mapped memory is zeroed on ilo reset, so set a per ccb flag
	 * to indicate that this ccb needs to be बंदd and reखोलोed.
	 */
	क्रम (slot = 0; slot < max_ccb; slot++) अणु
		अगर (!hw->ccb_alloc[slot])
			जारी;
		set_channel_reset(&hw->ccb_alloc[slot]->driver_ccb);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ilo_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
			माप_प्रकार len, loff_t *off)
अणु
	पूर्णांक err, found, cnt, pkt_id, pkt_len;
	काष्ठा ccb_data *data = fp->निजी_data;
	काष्ठा ccb *driver_ccb = &data->driver_ccb;
	काष्ठा ilo_hwinfo *hw = data->ilo_hw;
	व्योम *pkt;

	अगर (is_channel_reset(driver_ccb)) अणु
		/*
		 * If the device has been reset, applications
		 * need to बंद and reखोलो all ccbs.
		 */
		वापस -ENODEV;
	पूर्ण

	/*
	 * This function is to be called when data is expected
	 * in the channel, and will वापस an error अगर no packet is found
	 * during the loop below.  The sleep/retry logic is to allow
	 * applications to call पढ़ो() immediately post ग_लिखो(),
	 * and give iLO some समय to process the sent packet.
	 */
	cnt = 20;
	करो अणु
		/* look क्रम a received packet */
		found = ilo_pkt_dequeue(hw, driver_ccb, RECVQ, &pkt_id,
					&pkt_len, &pkt);
		अगर (found)
			अवरोध;
		cnt--;
		msleep(100);
	पूर्ण जबतक (!found && cnt);

	अगर (!found)
		वापस -EAGAIN;

	/* only copy the length of the received packet */
	अगर (pkt_len < len)
		len = pkt_len;

	err = copy_to_user(buf, pkt, len);

	/* वापस the received packet to the queue */
	ilo_pkt_enqueue(hw, driver_ccb, RECVQ, pkt_id, desc_mem_sz(1));

	वापस err ? -EFAULT : len;
पूर्ण

अटल sमाप_प्रकार ilo_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *buf,
			 माप_प्रकार len, loff_t *off)
अणु
	पूर्णांक err, pkt_id, pkt_len;
	काष्ठा ccb_data *data = fp->निजी_data;
	काष्ठा ccb *driver_ccb = &data->driver_ccb;
	काष्ठा ilo_hwinfo *hw = data->ilo_hw;
	व्योम *pkt;

	अगर (is_channel_reset(driver_ccb))
		वापस -ENODEV;

	/* get a packet to send the user command */
	अगर (!ilo_pkt_dequeue(hw, driver_ccb, SENDQ, &pkt_id, &pkt_len, &pkt))
		वापस -EBUSY;

	/* limit the length to the length of the packet */
	अगर (pkt_len < len)
		len = pkt_len;

	/* on failure, set the len to 0 to वापस empty packet to the device */
	err = copy_from_user(pkt, buf, len);
	अगर (err)
		len = 0;

	/* send the packet */
	ilo_pkt_enqueue(hw, driver_ccb, SENDQ, pkt_id, len);
	करोorbell_set(driver_ccb);

	वापस err ? -EFAULT : len;
पूर्ण

अटल __poll_t ilo_poll(काष्ठा file *fp, poll_table *रुको)
अणु
	काष्ठा ccb_data *data = fp->निजी_data;
	काष्ठा ccb *driver_ccb = &data->driver_ccb;

	poll_रुको(fp, &data->ccb_रुकोq, रुको);

	अगर (is_channel_reset(driver_ccb))
		वापस EPOLLERR;
	अन्यथा अगर (ilo_pkt_recv(data->ilo_hw, driver_ccb))
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल पूर्णांक ilo_बंद(काष्ठा inode *ip, काष्ठा file *fp)
अणु
	पूर्णांक slot;
	काष्ठा ccb_data *data;
	काष्ठा ilo_hwinfo *hw;
	अचिन्हित दीर्घ flags;

	slot = iminor(ip) % max_ccb;
	hw = container_of(ip->i_cdev, काष्ठा ilo_hwinfo, cdev);

	spin_lock(&hw->खोलो_lock);

	अगर (hw->ccb_alloc[slot]->ccb_cnt == 1) अणु

		data = fp->निजी_data;

		spin_lock_irqsave(&hw->alloc_lock, flags);
		hw->ccb_alloc[slot] = शून्य;
		spin_unlock_irqrestore(&hw->alloc_lock, flags);

		ilo_ccb_बंद(hw->ilo_dev, data);

		kमुक्त(data);
	पूर्ण अन्यथा
		hw->ccb_alloc[slot]->ccb_cnt--;

	spin_unlock(&hw->खोलो_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ilo_खोलो(काष्ठा inode *ip, काष्ठा file *fp)
अणु
	पूर्णांक slot, error;
	काष्ठा ccb_data *data;
	काष्ठा ilo_hwinfo *hw;
	अचिन्हित दीर्घ flags;

	slot = iminor(ip) % max_ccb;
	hw = container_of(ip->i_cdev, काष्ठा ilo_hwinfo, cdev);

	/* new ccb allocation */
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock(&hw->खोलो_lock);

	/* each fd निजी_data holds sw/hw view of ccb */
	अगर (hw->ccb_alloc[slot] == शून्य) अणु
		/* create a channel control block क्रम this minor */
		error = ilo_ccb_setup(hw, data, slot);
		अगर (error) अणु
			kमुक्त(data);
			जाओ out;
		पूर्ण

		data->ccb_cnt = 1;
		data->ccb_excl = fp->f_flags & O_EXCL;
		data->ilo_hw = hw;
		init_रुकोqueue_head(&data->ccb_रुकोq);

		/* ग_लिखो the ccb to hw */
		spin_lock_irqsave(&hw->alloc_lock, flags);
		ilo_ccb_खोलो(hw, data, slot);
		hw->ccb_alloc[slot] = data;
		spin_unlock_irqrestore(&hw->alloc_lock, flags);

		/* make sure the channel is functional */
		error = ilo_ccb_verअगरy(hw, data);
		अगर (error) अणु

			spin_lock_irqsave(&hw->alloc_lock, flags);
			hw->ccb_alloc[slot] = शून्य;
			spin_unlock_irqrestore(&hw->alloc_lock, flags);

			ilo_ccb_बंद(hw->ilo_dev, data);

			kमुक्त(data);
			जाओ out;
		पूर्ण

	पूर्ण अन्यथा अणु
		kमुक्त(data);
		अगर (fp->f_flags & O_EXCL || hw->ccb_alloc[slot]->ccb_excl) अणु
			/*
			 * The channel exists, and either this खोलो
			 * or a previous खोलो of this channel wants
			 * exclusive access.
			 */
			error = -EBUSY;
		पूर्ण अन्यथा अणु
			hw->ccb_alloc[slot]->ccb_cnt++;
			error = 0;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&hw->खोलो_lock);

	अगर (!error)
		fp->निजी_data = hw->ccb_alloc[slot];

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations ilo_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= ilo_पढ़ो,
	.ग_लिखो		= ilo_ग_लिखो,
	.poll		= ilo_poll,
	.खोलो 		= ilo_खोलो,
	.release 	= ilo_बंद,
	.llseek		= noop_llseek,
पूर्ण;

अटल irqवापस_t ilo_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ilo_hwinfo *hw = data;
	पूर्णांक pending, i;

	spin_lock(&hw->alloc_lock);

	/* check क्रम ccbs which have data */
	pending = get_device_outbound(hw);
	अगर (!pending) अणु
		spin_unlock(&hw->alloc_lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (is_db_reset(pending)) अणु
		/* wake up all ccbs अगर the device was reset */
		pending = -1;
		ilo_set_reset(hw);
	पूर्ण

	क्रम (i = 0; i < max_ccb; i++) अणु
		अगर (!hw->ccb_alloc[i])
			जारी;
		अगर (pending & (1 << i))
			wake_up_पूर्णांकerruptible(&hw->ccb_alloc[i]->ccb_रुकोq);
	पूर्ण

	/* clear the device of the channels that have been handled */
	clear_pending_db(hw, pending);

	spin_unlock(&hw->alloc_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ilo_unmap_device(काष्ठा pci_dev *pdev, काष्ठा ilo_hwinfo *hw)
अणु
	pci_iounmap(pdev, hw->db_vaddr);
	pci_iounmap(pdev, hw->ram_vaddr);
	pci_iounmap(pdev, hw->mmio_vaddr);
पूर्ण

अटल पूर्णांक ilo_map_device(काष्ठा pci_dev *pdev, काष्ठा ilo_hwinfo *hw)
अणु
	पूर्णांक bar;
	अचिन्हित दीर्घ off;

	/* map the memory mapped i/o रेजिस्टरs */
	hw->mmio_vaddr = pci_iomap(pdev, 1, 0);
	अगर (hw->mmio_vaddr == शून्य) अणु
		dev_err(&pdev->dev, "Error mapping mmio\n");
		जाओ out;
	पूर्ण

	/* map the adapter shared memory region */
	अगर (pdev->subप्रणाली_device == 0x00E4) अणु
		bar = 5;
		/* Last 8k is reserved क्रम CCBs */
		off = pci_resource_len(pdev, bar) - 0x2000;
	पूर्ण अन्यथा अणु
		bar = 2;
		off = 0;
	पूर्ण
	hw->ram_vaddr = pci_iomap_range(pdev, bar, off, max_ccb * ILOHW_CCB_SZ);
	अगर (hw->ram_vaddr == शून्य) अणु
		dev_err(&pdev->dev, "Error mapping shared mem\n");
		जाओ mmio_मुक्त;
	पूर्ण

	/* map the करोorbell aperture */
	hw->db_vaddr = pci_iomap(pdev, 3, max_ccb * ONE_DB_SIZE);
	अगर (hw->db_vaddr == शून्य) अणु
		dev_err(&pdev->dev, "Error mapping doorbell\n");
		जाओ ram_मुक्त;
	पूर्ण

	वापस 0;
ram_मुक्त:
	pci_iounmap(pdev, hw->ram_vaddr);
mmio_मुक्त:
	pci_iounmap(pdev, hw->mmio_vaddr);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम ilo_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i, minor;
	काष्ठा ilo_hwinfo *ilo_hw = pci_get_drvdata(pdev);

	अगर (!ilo_hw)
		वापस;

	clear_device(ilo_hw);

	minor = MINOR(ilo_hw->cdev.dev);
	क्रम (i = minor; i < minor + max_ccb; i++)
		device_destroy(ilo_class, MKDEV(ilo_major, i));

	cdev_del(&ilo_hw->cdev);
	ilo_disable_पूर्णांकerrupts(ilo_hw);
	मुक्त_irq(pdev->irq, ilo_hw);
	ilo_unmap_device(pdev, ilo_hw);
	pci_release_regions(pdev);
	/*
	 * pci_disable_device(pdev) used to be here. But this PCI device has
	 * two functions with पूर्णांकerrupt lines connected to a single pin. The
	 * other one is a USB host controller. So when we disable the PIN here
	 * e.g. by rmmod hpilo, the controller stops working. It is because
	 * the पूर्णांकerrupt link is disabled in ACPI since it is not refcounted
	 * yet. See acpi_pci_link_मुक्त_irq called from acpi_pci_irq_disable.
	 */
	kमुक्त(ilo_hw);
	ilo_hwdev[(minor / max_ccb)] = 0;
पूर्ण

अटल पूर्णांक ilo_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक devnum, minor, start, error = 0;
	काष्ठा ilo_hwinfo *ilo_hw;

	अगर (pci_match_id(ilo_blacklist, pdev)) अणु
		dev_dbg(&pdev->dev, "Not supported on this device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (max_ccb > MAX_CCB)
		max_ccb = MAX_CCB;
	अन्यथा अगर (max_ccb < MIN_CCB)
		max_ccb = MIN_CCB;

	/* find a मुक्त range क्रम device files */
	क्रम (devnum = 0; devnum < MAX_ILO_DEV; devnum++) अणु
		अगर (ilo_hwdev[devnum] == 0) अणु
			ilo_hwdev[devnum] = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (devnum == MAX_ILO_DEV) अणु
		dev_err(&pdev->dev, "Error finding free device\n");
		वापस -ENODEV;
	पूर्ण

	/* track global allocations क्रम this device */
	error = -ENOMEM;
	ilo_hw = kzalloc(माप(*ilo_hw), GFP_KERNEL);
	अगर (!ilo_hw)
		जाओ out;

	ilo_hw->ilo_dev = pdev;
	spin_lock_init(&ilo_hw->alloc_lock);
	spin_lock_init(&ilo_hw->fअगरo_lock);
	spin_lock_init(&ilo_hw->खोलो_lock);

	error = pci_enable_device(pdev);
	अगर (error)
		जाओ मुक्त;

	pci_set_master(pdev);

	error = pci_request_regions(pdev, ILO_NAME);
	अगर (error)
		जाओ disable;

	error = ilo_map_device(pdev, ilo_hw);
	अगर (error)
		जाओ मुक्त_regions;

	pci_set_drvdata(pdev, ilo_hw);
	clear_device(ilo_hw);

	error = request_irq(pdev->irq, ilo_isr, IRQF_SHARED, "hpilo", ilo_hw);
	अगर (error)
		जाओ unmap;

	ilo_enable_पूर्णांकerrupts(ilo_hw);

	cdev_init(&ilo_hw->cdev, &ilo_fops);
	ilo_hw->cdev.owner = THIS_MODULE;
	start = devnum * max_ccb;
	error = cdev_add(&ilo_hw->cdev, MKDEV(ilo_major, start), max_ccb);
	अगर (error) अणु
		dev_err(&pdev->dev, "Could not add cdev\n");
		जाओ हटाओ_isr;
	पूर्ण

	क्रम (minor = 0 ; minor < max_ccb; minor++) अणु
		काष्ठा device *dev;
		dev = device_create(ilo_class, &pdev->dev,
				    MKDEV(ilo_major, minor), शून्य,
				    "hpilo!d%dccb%d", devnum, minor);
		अगर (IS_ERR(dev))
			dev_err(&pdev->dev, "Could not create files\n");
	पूर्ण

	वापस 0;
हटाओ_isr:
	ilo_disable_पूर्णांकerrupts(ilo_hw);
	मुक्त_irq(pdev->irq, ilo_hw);
unmap:
	ilo_unmap_device(pdev, ilo_hw);
मुक्त_regions:
	pci_release_regions(pdev);
disable:
/*	pci_disable_device(pdev);  see comment in ilo_हटाओ */
मुक्त:
	kमुक्त(ilo_hw);
out:
	ilo_hwdev[devnum] = 0;
	वापस error;
पूर्ण

अटल स्थिर काष्ठा pci_device_id ilo_devices[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_COMPAQ, 0xB204) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, 0x3307) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ilo_devices);

अटल काष्ठा pci_driver ilo_driver = अणु
	.name 	  = ILO_NAME,
	.id_table = ilo_devices,
	.probe 	  = ilo_probe,
	.हटाओ   = ilo_हटाओ,
पूर्ण;

अटल पूर्णांक __init ilo_init(व्योम)
अणु
	पूर्णांक error;
	dev_t dev;

	ilo_class = class_create(THIS_MODULE, "iLO");
	अगर (IS_ERR(ilo_class)) अणु
		error = PTR_ERR(ilo_class);
		जाओ out;
	पूर्ण

	error = alloc_chrdev_region(&dev, 0, MAX_OPEN, ILO_NAME);
	अगर (error)
		जाओ class_destroy;

	ilo_major = MAJOR(dev);

	error =	pci_रेजिस्टर_driver(&ilo_driver);
	अगर (error)
		जाओ chr_हटाओ;

	वापस 0;
chr_हटाओ:
	unरेजिस्टर_chrdev_region(dev, MAX_OPEN);
class_destroy:
	class_destroy(ilo_class);
out:
	वापस error;
पूर्ण

अटल व्योम __निकास ilo_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ilo_driver);
	unरेजिस्टर_chrdev_region(MKDEV(ilo_major, 0), MAX_OPEN);
	class_destroy(ilo_class);
पूर्ण

MODULE_VERSION("1.5.0");
MODULE_ALIAS(ILO_NAME);
MODULE_DESCRIPTION(ILO_NAME);
MODULE_AUTHOR("David Altobelli <david.altobelli@hpe.com>");
MODULE_LICENSE("GPL v2");

module_param(max_ccb, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_ccb, "Maximum number of HP iLO channels to attach (8-24)(default=16)");

module_init(ilo_init);
module_निकास(ilo_निकास);
