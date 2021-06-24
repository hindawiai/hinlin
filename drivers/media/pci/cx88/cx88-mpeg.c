<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Support क्रम the mpeg transport stream transfers
 *  PCI function #2 of the cx2388x.
 *
 *    (c) 2004 Jelle Foks <jelle@foks.us>
 *    (c) 2004 Chris Pascoe <c.pascoe@itee.uq.edu.au>
 *    (c) 2004 Gerd Knorr <kraxel@bytesex.org>
 */

#समावेश "cx88.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

/* ------------------------------------------------------------------ */

MODULE_DESCRIPTION("mpeg driver for cx2388x based TV cards");
MODULE_AUTHOR("Jelle Foks <jelle@foks.us>");
MODULE_AUTHOR("Chris Pascoe <c.pascoe@itee.uq.edu.au>");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");
MODULE_VERSION(CX88_VERSION);

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages [mpeg]");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug + 1 > level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: mpeg:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx8802_dev *dev = container_of(work, काष्ठा cx8802_dev,
					      request_module_wk);

	अगर (dev->core->board.mpeg & CX88_MPEG_DVB)
		request_module("cx88-dvb");
	अगर (dev->core->board.mpeg & CX88_MPEG_BLACKBIRD)
		request_module("cx88-blackbird");
पूर्ण

अटल व्योम request_modules(काष्ठा cx8802_dev *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा cx8802_dev *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

अटल LIST_HEAD(cx8802_devlist);
अटल DEFINE_MUTEX(cx8802_mutex);
/* ------------------------------------------------------------------ */

पूर्णांक cx8802_start_dma(काष्ठा cx8802_dev    *dev,
		     काष्ठा cx88_dmaqueue *q,
		     काष्ठा cx88_buffer   *buf)
अणु
	काष्ठा cx88_core *core = dev->core;

	dprपूर्णांकk(1, "w: %d, h: %d, f: %d\n",
		core->width, core->height, core->field);

	/* setup fअगरo + क्रमmat */
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH28],
				dev->ts_packet_size, buf->risc.dma);

	/* ग_लिखो TS length to chip */
	cx_ग_लिखो(MO_TS_LNGTH, dev->ts_packet_size);

	/*
	 * FIXME: this needs a review.
	 * also: move to cx88-blackbird + cx88-dvb source files?
	 */

	dprपूर्णांकk(1, "core->active_type_id = 0x%08x\n", core->active_type_id);

	अगर ((core->active_type_id == CX88_MPEG_DVB) &&
	    (core->board.mpeg & CX88_MPEG_DVB)) अणु
		dprपूर्णांकk(1, "cx8802_start_dma doing .dvb\n");
		/* negedge driven & software reset */
		cx_ग_लिखो(TS_GEN_CNTRL, 0x0040 | dev->ts_gen_cntrl);
		udelay(100);
		cx_ग_लिखो(MO_PINMUX_IO, 0x00);
		cx_ग_लिखो(TS_HW_SOP_CNTRL, 0x47 << 16 | 188 << 4 | 0x01);
		चयन (core->boardnr) अणु
		हाल CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q:
		हाल CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_T:
		हाल CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD:
		हाल CX88_BOARD_PCHDTV_HD5500:
			cx_ग_लिखो(TS_SOP_STAT, 1 << 13);
			अवरोध;
		हाल CX88_BOARD_SAMSUNG_SMT_7020:
			cx_ग_लिखो(TS_SOP_STAT, 0x00);
			अवरोध;
		हाल CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1:
		हाल CX88_BOARD_HAUPPAUGE_NOVASE2_S1:
			/* Enable MPEG parallel IO and video संकेत pins */
			cx_ग_लिखो(MO_PINMUX_IO, 0x88);
			udelay(100);
			अवरोध;
		हाल CX88_BOARD_HAUPPAUGE_HVR1300:
			/* Enable MPEG parallel IO and video संकेत pins */
			cx_ग_लिखो(MO_PINMUX_IO, 0x88);
			cx_ग_लिखो(TS_SOP_STAT, 0);
			cx_ग_लिखो(TS_VALERR_CNTRL, 0);
			अवरोध;
		हाल CX88_BOARD_PINNACLE_PCTV_HD_800i:
			/* Enable MPEG parallel IO and video संकेत pins */
			cx_ग_लिखो(MO_PINMUX_IO, 0x88);
			cx_ग_लिखो(TS_HW_SOP_CNTRL, (0x47 << 16) | (188 << 4));
			dev->ts_gen_cntrl = 5;
			cx_ग_लिखो(TS_SOP_STAT, 0);
			cx_ग_लिखो(TS_VALERR_CNTRL, 0);
			udelay(100);
			अवरोध;
		शेष:
			cx_ग_लिखो(TS_SOP_STAT, 0x00);
			अवरोध;
		पूर्ण
		cx_ग_लिखो(TS_GEN_CNTRL, dev->ts_gen_cntrl);
		udelay(100);
	पूर्ण अन्यथा अगर ((core->active_type_id == CX88_MPEG_BLACKBIRD) &&
		(core->board.mpeg & CX88_MPEG_BLACKBIRD)) अणु
		dprपूर्णांकk(1, "cx8802_start_dma doing .blackbird\n");
		cx_ग_लिखो(MO_PINMUX_IO, 0x88); /* enable MPEG parallel IO */

		/* punctured घड़ी TS & posedge driven & software reset */
		cx_ग_लिखो(TS_GEN_CNTRL, 0x46);
		udelay(100);

		cx_ग_लिखो(TS_HW_SOP_CNTRL, 0x408); /* mpeg start byte */
		cx_ग_लिखो(TS_VALERR_CNTRL, 0x2000);

		/* punctured घड़ी TS & posedge driven */
		cx_ग_लिखो(TS_GEN_CNTRL, 0x06);
		udelay(100);
	पूर्ण अन्यथा अणु
		pr_err("%s() Failed. Unsupported value in .mpeg (0x%08x)\n",
		       __func__, core->board.mpeg);
		वापस -EINVAL;
	पूर्ण

	/* reset counter */
	cx_ग_लिखो(MO_TS_GPCNTRL, GP_COUNT_CONTROL_RESET);
	q->count = 0;

	/* enable irqs */
	dprपूर्णांकk(1, "setting the interrupt mask\n");
	cx_set(MO_PCI_INTMSK, core->pci_irqmask | PCI_INT_TSINT);
	cx_set(MO_TS_INTMSK,  0x1f0011);

	/* start dma */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	cx_set(MO_TS_DMACNTRL, 0x11);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx8802_start_dma);

अटल पूर्णांक cx8802_stop_dma(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;

	dprपूर्णांकk(1, "\n");

	/* stop dma */
	cx_clear(MO_TS_DMACNTRL, 0x11);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_TSINT);
	cx_clear(MO_TS_INTMSK, 0x1f0011);

	/* Reset the controller */
	cx_ग_लिखो(TS_GEN_CNTRL, 0xcd);
	वापस 0;
पूर्ण

अटल पूर्णांक cx8802_restart_queue(काष्ठा cx8802_dev    *dev,
				काष्ठा cx88_dmaqueue *q)
अणु
	काष्ठा cx88_buffer *buf;

	dprपूर्णांकk(1, "\n");
	अगर (list_empty(&q->active))
		वापस 0;

	buf = list_entry(q->active.next, काष्ठा cx88_buffer, list);
	dprपूर्णांकk(2, "restart_queue [%p/%d]: restart dma\n",
		buf, buf->vb.vb2_buf.index);
	cx8802_start_dma(dev, q, buf);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक cx8802_buf_prepare(काष्ठा vb2_queue *q, काष्ठा cx8802_dev *dev,
		       काष्ठा cx88_buffer *buf)
अणु
	पूर्णांक size = dev->ts_packet_size * dev->ts_packet_count;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(&buf->vb.vb2_buf, 0);
	काष्ठा cx88_riscmem *risc = &buf->risc;
	पूर्णांक rc;

	अगर (vb2_plane_size(&buf->vb.vb2_buf, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);

	rc = cx88_risc_databuffer(dev->pci, risc, sgt->sgl,
				  dev->ts_packet_size, dev->ts_packet_count, 0);
	अगर (rc) अणु
		अगर (risc->cpu)
			pci_मुक्त_consistent(dev->pci, risc->size,
					    risc->cpu, risc->dma);
		स_रखो(risc, 0, माप(*risc));
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx8802_buf_prepare);

व्योम cx8802_buf_queue(काष्ठा cx8802_dev *dev, काष्ठा cx88_buffer *buf)
अणु
	काष्ठा cx88_buffer    *prev;
	काष्ठा cx88_dmaqueue  *cx88q = &dev->mpegq;

	dprपूर्णांकk(1, "\n");
	/* add jump to start */
	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 8);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 8);

	अगर (list_empty(&cx88q->active)) अणु
		dprपूर्णांकk(1, "queue is empty - first active\n");
		list_add_tail(&buf->list, &cx88q->active);
		dprपूर्णांकk(1, "[%p/%d] %s - first active\n",
			buf, buf->vb.vb2_buf.index, __func__);

	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		dprपूर्णांकk(1, "queue is not empty - append to active\n");
		prev = list_entry(cx88q->active.prev, काष्ठा cx88_buffer, list);
		list_add_tail(&buf->list, &cx88q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(1, "[%p/%d] %s - append to active\n",
			buf, buf->vb.vb2_buf.index, __func__);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx8802_buf_queue);

/* ----------------------------------------------------------- */

अटल व्योम करो_cancel_buffers(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_dmaqueue *q = &dev->mpegq;
	काष्ठा cx88_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&q->active)) अणु
		buf = list_entry(q->active.next, काष्ठा cx88_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

व्योम cx8802_cancel_buffers(काष्ठा cx8802_dev *dev)
अणु
	dprपूर्णांकk(1, "\n");
	cx8802_stop_dma(dev);
	करो_cancel_buffers(dev);
पूर्ण
EXPORT_SYMBOL(cx8802_cancel_buffers);

अटल स्थिर अक्षर *cx88_mpeg_irqs[32] = अणु
	"ts_risci1", शून्य, शून्य, शून्य,
	"ts_risci2", शून्य, शून्य, शून्य,
	"ts_oflow",  शून्य, शून्य, शून्य,
	"ts_sync",   शून्य, शून्य, शून्य,
	"opc_err", "par_err", "rip_err", "pci_abort",
	"ts_err?",
पूर्ण;

अटल व्योम cx8802_mpeg_irq(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	u32 status, mask, count;

	dprपूर्णांकk(1, "\n");
	status = cx_पढ़ो(MO_TS_INTSTAT);
	mask   = cx_पढ़ो(MO_TS_INTMSK);
	अगर (0 == (status & mask))
		वापस;

	cx_ग_लिखो(MO_TS_INTSTAT, status);

	अगर (debug || (status & mask & ~0xff))
		cx88_prपूर्णांक_irqbits("irq mpeg ",
				   cx88_mpeg_irqs, ARRAY_SIZE(cx88_mpeg_irqs),
				   status, mask);

	/* risc op code error */
	अगर (status & (1 << 16)) अणु
		pr_warn("mpeg risc op code error\n");
		cx_clear(MO_TS_DMACNTRL, 0x11);
		cx88_sram_channel_dump(dev->core,
				       &cx88_sram_channels[SRAM_CH28]);
	पूर्ण

	/* risc1 y */
	अगर (status & 0x01) अणु
		dprपूर्णांकk(1, "wake up\n");
		spin_lock(&dev->slock);
		count = cx_पढ़ो(MO_TS_GPCNT);
		cx88_wakeup(dev->core, &dev->mpegq, count);
		spin_unlock(&dev->slock);
	पूर्ण

	/* other general errors */
	अगर (status & 0x1f0100) अणु
		dprपूर्णांकk(0, "general errors: 0x%08x\n", status & 0x1f0100);
		spin_lock(&dev->slock);
		cx8802_stop_dma(dev);
		spin_unlock(&dev->slock);
	पूर्ण
पूर्ण

#घोषणा MAX_IRQ_LOOP 10

अटल irqवापस_t cx8802_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx8802_dev *dev = dev_id;
	काष्ठा cx88_core *core = dev->core;
	u32 status;
	पूर्णांक loop, handled = 0;

	क्रम (loop = 0; loop < MAX_IRQ_LOOP; loop++) अणु
		status = cx_पढ़ो(MO_PCI_INTSTAT) &
			(core->pci_irqmask | PCI_INT_TSINT);
		अगर (status == 0)
			जाओ out;
		dprपूर्णांकk(1, "cx8802_irq\n");
		dprपूर्णांकk(1, "    loop: %d/%d\n", loop, MAX_IRQ_LOOP);
		dprपूर्णांकk(1, "    status: %d\n", status);
		handled = 1;
		cx_ग_लिखो(MO_PCI_INTSTAT, status);

		अगर (status & core->pci_irqmask)
			cx88_core_irq(core, status);
		अगर (status & PCI_INT_TSINT)
			cx8802_mpeg_irq(dev);
	पूर्ण
	अगर (loop == MAX_IRQ_LOOP) अणु
		dprपूर्णांकk(0, "clearing mask\n");
		pr_warn("irq loop -- clearing mask\n");
		cx_ग_लिखो(MO_PCI_INTMSK, 0);
	पूर्ण

 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक cx8802_init_common(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	पूर्णांक err;

	/* pci init */
	अगर (pci_enable_device(dev->pci))
		वापस -EIO;
	pci_set_master(dev->pci);
	err = pci_set_dma_mask(dev->pci, DMA_BIT_MASK(32));
	अगर (err) अणु
		pr_err("Oops: no 32bit PCI DMA ???\n");
		वापस -EIO;
	पूर्ण

	dev->pci_rev = dev->pci->revision;
	pci_पढ़ो_config_byte(dev->pci, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		pci_name(dev->pci), dev->pci_rev, dev->pci->irq,
		dev->pci_lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev->pci, 0));

	/* initialize driver काष्ठा */
	spin_lock_init(&dev->slock);

	/* init dma queue */
	INIT_LIST_HEAD(&dev->mpegq.active);

	/* get irq */
	err = request_irq(dev->pci->irq, cx8802_irq,
			  IRQF_SHARED, dev->core->name, dev);
	अगर (err < 0) अणु
		pr_err("can't get IRQ %d\n", dev->pci->irq);
		वापस err;
	पूर्ण
	cx_set(MO_PCI_INTMSK, core->pci_irqmask);

	/* everything worked */
	pci_set_drvdata(dev->pci, dev);
	वापस 0;
पूर्ण

अटल व्योम cx8802_fini_common(काष्ठा cx8802_dev *dev)
अणु
	dprपूर्णांकk(2, "\n");
	cx8802_stop_dma(dev);
	pci_disable_device(dev->pci);

	/* unरेजिस्टर stuff */
	मुक्त_irq(dev->pci->irq, dev);
पूर्ण

/* ----------------------------------------------------------- */

अटल पूर्णांक cx8802_suspend_common(काष्ठा pci_dev *pci_dev, pm_message_t state)
अणु
	काष्ठा cx8802_dev *dev = pci_get_drvdata(pci_dev);
	अचिन्हित दीर्घ flags;

	/* stop mpeg dma */
	spin_lock_irqsave(&dev->slock, flags);
	अगर (!list_empty(&dev->mpegq.active)) अणु
		dprपूर्णांकk(2, "suspend\n");
		pr_info("suspend mpeg\n");
		cx8802_stop_dma(dev);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);

	/* FIXME -- shutकरोwn device */
	cx88_shutकरोwn(dev->core);

	pci_save_state(pci_dev);
	अगर (pci_set_घातer_state(pci_dev,
				pci_choose_state(pci_dev, state)) != 0) अणु
		pci_disable_device(pci_dev);
		dev->state.disabled = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx8802_resume_common(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा cx8802_dev *dev = pci_get_drvdata(pci_dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (dev->state.disabled) अणु
		err = pci_enable_device(pci_dev);
		अगर (err) अणु
			pr_err("can't enable device\n");
			वापस err;
		पूर्ण
		dev->state.disabled = 0;
	पूर्ण
	err = pci_set_घातer_state(pci_dev, PCI_D0);
	अगर (err) अणु
		pr_err("can't enable device\n");
		pci_disable_device(pci_dev);
		dev->state.disabled = 1;

		वापस err;
	पूर्ण
	pci_restore_state(pci_dev);

	/* FIXME: re-initialize hardware */
	cx88_reset(dev->core);

	/* restart video+vbi capture */
	spin_lock_irqsave(&dev->slock, flags);
	अगर (!list_empty(&dev->mpegq.active)) अणु
		pr_info("resume mpeg\n");
		cx8802_restart_queue(dev, &dev->mpegq);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);

	वापस 0;
पूर्ण

काष्ठा cx8802_driver *cx8802_get_driver(काष्ठा cx8802_dev *dev,
					क्रमागत cx88_board_type btype)
अणु
	काष्ठा cx8802_driver *d;

	list_क्रम_each_entry(d, &dev->drvlist, drvlist)
		अगर (d->type_id == btype)
			वापस d;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cx8802_get_driver);

/* Driver asked क्रम hardware access. */
अटल पूर्णांक cx8802_request_acquire(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	अचिन्हित पूर्णांक	i;

	/* Fail a request क्रम hardware अगर the device is busy. */
	अगर (core->active_type_id != CX88_BOARD_NONE &&
	    core->active_type_id != drv->type_id)
		वापस -EBUSY;

	अगर (drv->type_id == CX88_MPEG_DVB) अणु
		/* When चयनing to DVB, always set the input to the tuner */
		core->last_analog_input = core->input;
		core->input = 0;
		क्रम (i = 0;
		     i < ARRAY_SIZE(core->board.input);
		     i++) अणु
			अगर (core->board.input[i].type == CX88_VMUX_DVB) अणु
				core->input = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (drv->advise_acquire) अणु
		core->active_ref++;
		अगर (core->active_type_id == CX88_BOARD_NONE) अणु
			core->active_type_id = drv->type_id;
			drv->advise_acquire(drv);
		पूर्ण

		dprपूर्णांकk(1, "Post acquire GPIO=%x\n", cx_पढ़ो(MO_GP0_IO));
	पूर्ण

	वापस 0;
पूर्ण

/* Driver asked to release hardware. */
अटल पूर्णांक cx8802_request_release(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;

	अगर (drv->advise_release && --core->active_ref == 0) अणु
		अगर (drv->type_id == CX88_MPEG_DVB) अणु
			/*
			 * If the DVB driver is releasing, reset the input
			 * state to the last configured analog input
			 */
			core->input = core->last_analog_input;
		पूर्ण

		drv->advise_release(drv);
		core->active_type_id = CX88_BOARD_NONE;
		dprपूर्णांकk(1, "Post release GPIO=%x\n", cx_पढ़ो(MO_GP0_IO));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx8802_check_driver(काष्ठा cx8802_driver *drv)
अणु
	अगर (!drv)
		वापस -ENODEV;

	अगर ((drv->type_id != CX88_MPEG_DVB) &&
	    (drv->type_id != CX88_MPEG_BLACKBIRD))
		वापस -EINVAL;

	अगर ((drv->hw_access != CX8802_DRVCTL_SHARED) &&
	    (drv->hw_access != CX8802_DRVCTL_EXCLUSIVE))
		वापस -EINVAL;

	अगर ((!drv->probe) ||
	    (!drv->हटाओ) ||
	    (!drv->advise_acquire) ||
	    (!drv->advise_release))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक cx8802_रेजिस्टर_driver(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx8802_dev *dev;
	काष्ठा cx8802_driver *driver;
	पूर्णांक err, i = 0;

	pr_info("registering cx8802 driver, type: %s access: %s\n",
		drv->type_id == CX88_MPEG_DVB ? "dvb" : "blackbird",
		drv->hw_access == CX8802_DRVCTL_SHARED ?
				  "shared" : "exclusive");

	err = cx8802_check_driver(drv);
	अगर (err) अणु
		pr_err("cx8802_driver is invalid\n");
		वापस err;
	पूर्ण

	mutex_lock(&cx8802_mutex);

	list_क्रम_each_entry(dev, &cx8802_devlist, devlist) अणु
		pr_info("subsystem: %04x:%04x, board: %s [card=%d]\n",
			dev->pci->subप्रणाली_venकरोr,
			dev->pci->subप्रणाली_device, dev->core->board.name,
			dev->core->boardnr);

		/* Bring up a new काष्ठा क्रम each driver instance */
		driver = kzalloc(माप(*drv), GFP_KERNEL);
		अगर (!driver) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		/* Snapshot of the driver registration data */
		drv->core = dev->core;
		drv->suspend = cx8802_suspend_common;
		drv->resume = cx8802_resume_common;
		drv->request_acquire = cx8802_request_acquire;
		drv->request_release = cx8802_request_release;
		स_नकल(driver, drv, माप(*driver));

		mutex_lock(&drv->core->lock);
		err = drv->probe(driver);
		अगर (err == 0) अणु
			i++;
			list_add_tail(&driver->drvlist, &dev->drvlist);
		पूर्ण अन्यथा अणु
			pr_err("cx8802 probe failed, err = %d\n", err);
		पूर्ण
		mutex_unlock(&drv->core->lock);
	पूर्ण

	err = i ? 0 : -ENODEV;
out:
	mutex_unlock(&cx8802_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL(cx8802_रेजिस्टर_driver);

पूर्णांक cx8802_unरेजिस्टर_driver(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx8802_dev *dev;
	काष्ठा cx8802_driver *d, *dपंचांगp;
	पूर्णांक err = 0;

	pr_info("unregistering cx8802 driver, type: %s access: %s\n",
		drv->type_id == CX88_MPEG_DVB ? "dvb" : "blackbird",
		drv->hw_access == CX8802_DRVCTL_SHARED ?
				  "shared" : "exclusive");

	mutex_lock(&cx8802_mutex);

	list_क्रम_each_entry(dev, &cx8802_devlist, devlist) अणु
		pr_info("subsystem: %04x:%04x, board: %s [card=%d]\n",
			dev->pci->subप्रणाली_venकरोr,
			dev->pci->subप्रणाली_device, dev->core->board.name,
			dev->core->boardnr);

		mutex_lock(&dev->core->lock);

		list_क्रम_each_entry_safe(d, dपंचांगp, &dev->drvlist, drvlist) अणु
			/* only unरेजिस्टर the correct driver type */
			अगर (d->type_id != drv->type_id)
				जारी;

			err = d->हटाओ(d);
			अगर (err == 0) अणु
				list_del(&d->drvlist);
				kमुक्त(d);
			पूर्ण अन्यथा
				pr_err("cx8802 driver remove failed (%d)\n",
				       err);
		पूर्ण

		mutex_unlock(&dev->core->lock);
	पूर्ण

	mutex_unlock(&cx8802_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cx8802_unरेजिस्टर_driver);

/* ----------------------------------------------------------- */
अटल पूर्णांक cx8802_probe(काष्ठा pci_dev *pci_dev,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा cx8802_dev *dev;
	काष्ठा cx88_core  *core;
	पूर्णांक err;

	/* general setup */
	core = cx88_core_get(pci_dev);
	अगर (!core)
		वापस -EINVAL;

	pr_info("cx2388x 8802 Driver Manager\n");

	err = -ENODEV;
	अगर (!core->board.mpeg)
		जाओ fail_core;

	err = -ENOMEM;
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ fail_core;
	dev->pci = pci_dev;
	dev->core = core;

	/* Maपूर्णांकain a reference so cx88-video can query the 8802 device. */
	core->dvbdev = dev;

	err = cx8802_init_common(dev);
	अगर (err != 0)
		जाओ fail_dev;

	INIT_LIST_HEAD(&dev->drvlist);
	mutex_lock(&cx8802_mutex);
	list_add_tail(&dev->devlist, &cx8802_devlist);
	mutex_unlock(&cx8802_mutex);

	/* now स्वतःload cx88-dvb or cx88-blackbird */
	request_modules(dev);
	वापस 0;

 fail_dev:
	kमुक्त(dev);
 fail_core:
	core->dvbdev = शून्य;
	cx88_core_put(core, pci_dev);
	वापस err;
पूर्ण

अटल व्योम cx8802_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा cx8802_dev *dev;

	dev = pci_get_drvdata(pci_dev);

	dprपूर्णांकk(1, "%s\n", __func__);

	flush_request_modules(dev);

	mutex_lock(&dev->core->lock);

	अगर (!list_empty(&dev->drvlist)) अणु
		काष्ठा cx8802_driver *drv, *पंचांगp;
		पूर्णांक err;

		pr_warn("Trying to remove cx8802 driver while cx8802 sub-drivers still loaded?!\n");

		list_क्रम_each_entry_safe(drv, पंचांगp, &dev->drvlist, drvlist) अणु
			err = drv->हटाओ(drv);
			अगर (err == 0) अणु
				list_del(&drv->drvlist);
			पूर्ण अन्यथा
				pr_err("cx8802 driver remove failed (%d)\n",
				       err);
			kमुक्त(drv);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->core->lock);

	/* Destroy any 8802 reference. */
	dev->core->dvbdev = शून्य;

	/* common */
	cx8802_fini_common(dev);
	cx88_core_put(dev->core, dev->pci);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cx8802_pci_tbl[] = अणु
	अणु
		.venकरोr       = 0x14f1,
		.device       = 0x8802,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	पूर्ण, अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cx8802_pci_tbl);

अटल काष्ठा pci_driver cx8802_pci_driver = अणु
	.name     = "cx88-mpeg driver manager",
	.id_table = cx8802_pci_tbl,
	.probe    = cx8802_probe,
	.हटाओ   = cx8802_हटाओ,
पूर्ण;

module_pci_driver(cx8802_pci_driver);
