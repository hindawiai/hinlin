<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * driver core
 *
 * (c) 2001-03 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sound.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm.h>

MODULE_DESCRIPTION("v4l2 driver module for saa7130/34 based TV cards");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");
MODULE_VERSION(SAA7134_VERSION);


/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक irq_debug;
module_param(irq_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(irq_debug,"enable debug messages [IRQ handler]");

अटल अचिन्हित पूर्णांक core_debug;
module_param(core_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(core_debug,"enable debug messages [core]");

अटल अचिन्हित पूर्णांक gpio_tracking;
module_param(gpio_tracking, पूर्णांक, 0644);
MODULE_PARM_DESC(gpio_tracking,"enable debug messages [gpio]");

अटल अचिन्हित पूर्णांक alsa = 1;
module_param(alsa, पूर्णांक, 0644);
MODULE_PARM_DESC(alsa,"enable/disable ALSA DMA sound [dmasound]");

अटल अचिन्हित पूर्णांक latency = UNSET;
module_param(latency, पूर्णांक, 0444);
MODULE_PARM_DESC(latency,"pci latency timer");

पूर्णांक saa7134_no_overlay=-1;
module_param_named(no_overlay, saa7134_no_overlay, पूर्णांक, 0444);
MODULE_PARM_DESC(no_overlay, "allow override overlay default (0 disables, 1 enables) [some VIA/SIS chipsets are known to have problem with overlay]");

bool saa7134_userptr;
module_param(saa7134_userptr, bool, 0644);
MODULE_PARM_DESC(saa7134_userptr, "enable page-aligned userptr support");

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक vbi_nr[]   = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक radio_nr[] = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक tuner[]    = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक card[]     = अणु[0 ... (SAA7134_MAXBOARDS - 1)] = UNSET पूर्ण;


module_param_array(video_nr, पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr,   पूर्णांक, शून्य, 0444);
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
module_param_array(tuner,    पूर्णांक, शून्य, 0444);
module_param_array(card,     पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(video_nr, "video device number");
MODULE_PARM_DESC(vbi_nr,   "vbi device number");
MODULE_PARM_DESC(radio_nr, "radio device number");
MODULE_PARM_DESC(tuner,    "tuner type");
MODULE_PARM_DESC(card,     "card type");

DEFINE_MUTEX(saa7134_devlist_lock);
EXPORT_SYMBOL(saa7134_devlist_lock);
LIST_HEAD(saa7134_devlist);
EXPORT_SYMBOL(saa7134_devlist);
अटल LIST_HEAD(mops_list);
अटल अचिन्हित पूर्णांक saa7134_devcount;

पूर्णांक (*saa7134_dmasound_init)(काष्ठा saa7134_dev *dev);
पूर्णांक (*saa7134_dmasound_निकास)(काष्ठा saa7134_dev *dev);

#घोषणा core_dbg(fmt, arg...) करो अणु \
	अगर (core_debug) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("core: " fmt), ## arg); \
	पूर्ण जबतक (0)

#घोषणा irq_dbg(level, fmt, arg...)  करो अणु\
	अगर (irq_debug > level) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("irq: " fmt), ## arg); \
	पूर्ण जबतक (0)

व्योम saa7134_track_gpio(काष्ठा saa7134_dev *dev, स्थिर अक्षर *msg)
अणु
	अचिन्हित दीर्घ mode,status;

	अगर (!gpio_tracking)
		वापस;
	/* rising SAA7134_GPIO_GPRESCAN पढ़ोs the status */
	saa_anकरोrb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN,0);
	saa_anकरोrb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN,SAA7134_GPIO_GPRESCAN);
	mode   = saa_पढ़ोl(SAA7134_GPIO_GPMODE0   >> 2) & 0xfffffff;
	status = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2) & 0xfffffff;
	core_dbg("%s: gpio: mode=0x%07lx in=0x%07lx out=0x%07lx [%s]\n",
	       dev->name, mode, (~mode) & status, mode & status, msg);
पूर्ण

व्योम saa7134_set_gpio(काष्ठा saa7134_dev *dev, पूर्णांक bit_no, पूर्णांक value)
अणु
	u32 index, bitval;

	index = 1 << bit_no;
	चयन (value) अणु
	हाल 0: /* अटल value */
	हाल 1:
		core_dbg("setting GPIO%d to static %d\n", bit_no, value);
		/* turn sync mode off अगर necessary */
		अगर (index & 0x00c00000)
			saa_anकरोrb(SAA7134_VIDEO_PORT_CTRL6, 0x0f, 0x00);
		अगर (value)
			bitval = index;
		अन्यथा
			bitval = 0;
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2, index, index);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, index, bitval);
		अवरोध;
	हाल 3:	/* tristate */
		core_dbg("setting GPIO%d to tristate\n", bit_no);
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2, index, 0);
		अवरोध;
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------ */


/* ----------------------------------------------------------- */
/* delayed request_module                                      */

#अगर defined(CONFIG_MODULES) && defined(MODULE)

अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)अणु
	काष्ठा saa7134_dev* dev = container_of(work, काष्ठा saa7134_dev, request_module_wk);
	अगर (card_is_empress(dev))
		request_module("saa7134-empress");
	अगर (card_is_dvb(dev))
		request_module("saa7134-dvb");
	अगर (card_is_go7007(dev))
		request_module("saa7134-go7007");
	अगर (alsa) अणु
		अगर (dev->pci->device != PCI_DEVICE_ID_PHILIPS_SAA7130)
			request_module("saa7134-alsa");
	पूर्ण
पूर्ण

अटल व्योम request_submodules(काष्ठा saa7134_dev *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_submodules(काष्ठा saa7134_dev *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण

#अन्यथा
#घोषणा request_submodules(dev)
#घोषणा flush_request_submodules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

/* ------------------------------------------------------------------ */

/* nr of (saa7134-)pages क्रम the given buffer size */
अटल पूर्णांक saa7134_buffer_pages(पूर्णांक size)
अणु
	size  = PAGE_ALIGN(size);
	size += PAGE_SIZE; /* क्रम non-page-aligned buffers */
	size /= 4096;
	वापस size;
पूर्ण

/* calc max # of buffers from size (must not exceed the 4MB भव
 * address space per DMA channel) */
पूर्णांक saa7134_buffer_count(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक maxcount;

	maxcount = 1024 / saa7134_buffer_pages(size);
	अगर (count > maxcount)
		count = maxcount;
	वापस count;
पूर्ण

पूर्णांक saa7134_buffer_startpage(काष्ठा saa7134_buf *buf)
अणु
	वापस saa7134_buffer_pages(vb2_plane_size(&buf->vb2.vb2_buf, 0))
			* buf->vb2.vb2_buf.index;
पूर्ण

अचिन्हित दीर्घ saa7134_buffer_base(काष्ठा saa7134_buf *buf)
अणु
	अचिन्हित दीर्घ base;
	काष्ठा sg_table *dma = vb2_dma_sg_plane_desc(&buf->vb2.vb2_buf, 0);

	base  = saa7134_buffer_startpage(buf) * 4096;
	base += dma->sgl[0].offset;
	वापस base;
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक saa7134_pgtable_alloc(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt)
अणु
	__le32       *cpu;
	dma_addr_t   dma_addr = 0;

	cpu = pci_alloc_consistent(pci, SAA7134_PGTABLE_SIZE, &dma_addr);
	अगर (शून्य == cpu)
		वापस -ENOMEM;
	pt->size = SAA7134_PGTABLE_SIZE;
	pt->cpu  = cpu;
	pt->dma  = dma_addr;
	वापस 0;
पूर्ण

पूर्णांक saa7134_pgtable_build(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt,
			  काष्ठा scatterlist *list, अचिन्हित पूर्णांक length,
			  अचिन्हित पूर्णांक startpage)
अणु
	__le32        *ptr;
	अचिन्हित पूर्णांक  i, p;

	BUG_ON(शून्य == pt || शून्य == pt->cpu);

	ptr = pt->cpu + startpage;
	क्रम (i = 0; i < length; i++, list = sg_next(list)) अणु
		क्रम (p = 0; p * 4096 < sg_dma_len(list); p++, ptr++)
			*ptr = cpu_to_le32(sg_dma_address(list) +
						list->offset + p * 4096);
	पूर्ण
	वापस 0;
पूर्ण

व्योम saa7134_pgtable_मुक्त(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt)
अणु
	अगर (शून्य == pt->cpu)
		वापस;
	pci_मुक्त_consistent(pci, pt->size, pt->cpu, pt->dma);
	pt->cpu = शून्य;
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक saa7134_buffer_queue(काष्ठा saa7134_dev *dev,
			 काष्ठा saa7134_dmaqueue *q,
			 काष्ठा saa7134_buf *buf)
अणु
	काष्ठा saa7134_buf *next = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);
	core_dbg("buffer_queue %p\n", buf);
	अगर (शून्य == q->curr) अणु
		अगर (!q->need_two) अणु
			q->curr = buf;
			buf->activate(dev, buf, शून्य);
		पूर्ण अन्यथा अगर (list_empty(&q->queue)) अणु
			list_add_tail(&buf->entry, &q->queue);
		पूर्ण अन्यथा अणु
			next = list_entry(q->queue.next, काष्ठा saa7134_buf,
					  entry);
			q->curr = buf;
			buf->activate(dev, buf, next);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_add_tail(&buf->entry, &q->queue);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
	वापस 0;
पूर्ण

व्योम saa7134_buffer_finish(काष्ठा saa7134_dev *dev,
			   काष्ठा saa7134_dmaqueue *q,
			   अचिन्हित पूर्णांक state)
अणु
	core_dbg("buffer_finish %p\n", q->curr);

	/* finish current buffer */
	q->curr->vb2.vb2_buf.बारtamp = kसमय_get_ns();
	q->curr->vb2.sequence = q->seq_nr++;
	vb2_buffer_करोne(&q->curr->vb2.vb2_buf, state);
	q->curr = शून्य;
पूर्ण

व्योम saa7134_buffer_next(काष्ठा saa7134_dev *dev,
			 काष्ठा saa7134_dmaqueue *q)
अणु
	काष्ठा saa7134_buf *buf,*next = शून्य;

	निश्चित_spin_locked(&dev->slock);
	BUG_ON(शून्य != q->curr);

	अगर (!list_empty(&q->queue)) अणु
		/* activate next one from queue */
		buf = list_entry(q->queue.next, काष्ठा saa7134_buf, entry);
		core_dbg("buffer_next %p [prev=%p/next=%p]\n",
			buf, q->queue.prev, q->queue.next);
		list_del(&buf->entry);
		अगर (!list_empty(&q->queue))
			next = list_entry(q->queue.next, काष्ठा saa7134_buf, entry);
		q->curr = buf;
		buf->activate(dev, buf, next);
		core_dbg("buffer_next #2 prev=%p/next=%p\n",
			q->queue.prev, q->queue.next);
	पूर्ण अन्यथा अणु
		/* nothing to करो -- just stop DMA */
		core_dbg("buffer_next %p\n", शून्य);
		saa7134_set_dmabits(dev);
		del_समयr(&q->समयout);
	पूर्ण
पूर्ण

व्योम saa7134_buffer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा saa7134_dmaqueue *q = from_समयr(q, t, समयout);
	काष्ठा saa7134_dev *dev = q->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);

	/* try to reset the hardware (SWRST) */
	saa_ग_लिखोb(SAA7134_REGION_ENABLE, 0x00);
	saa_ग_लिखोb(SAA7134_REGION_ENABLE, 0x80);
	saa_ग_लिखोb(SAA7134_REGION_ENABLE, 0x00);

	/* flag current buffer as failed,
	   try to start over with the next one. */
	अगर (q->curr) अणु
		core_dbg("timeout on %p\n", q->curr);
		saa7134_buffer_finish(dev, q, VB2_BUF_STATE_ERROR);
	पूर्ण
	saa7134_buffer_next(dev, q);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

व्योम saa7134_stop_streaming(काष्ठा saa7134_dev *dev, काष्ठा saa7134_dmaqueue *q)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *pos, *n;
	काष्ठा saa7134_buf *पंचांगp;

	spin_lock_irqsave(&dev->slock, flags);
	list_क्रम_each_safe(pos, n, &q->queue) अणु
		पंचांगp = list_entry(pos, काष्ठा saa7134_buf, entry);
		vb2_buffer_करोne(&पंचांगp->vb2.vb2_buf,
				VB2_BUF_STATE_ERROR);
		list_del(pos);
		पंचांगp = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
	saa7134_buffer_समयout(&q->समयout); /* also calls del_समयr(&q->समयout) */
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_stop_streaming);

/* ------------------------------------------------------------------ */

पूर्णांक saa7134_set_dmabits(काष्ठा saa7134_dev *dev)
अणु
	u32 split, task=0, ctrl=0, irq=0;
	क्रमागत v4l2_field cap = V4L2_FIELD_ANY;
	क्रमागत v4l2_field ov  = V4L2_FIELD_ANY;

	निश्चित_spin_locked(&dev->slock);

	अगर (dev->insuspend)
		वापस 0;

	/* video capture -- dma 0 + video task A */
	अगर (dev->video_q.curr) अणु
		task |= 0x01;
		ctrl |= SAA7134_MAIN_CTRL_TE0;
		irq  |= SAA7134_IRQ1_INTE_RA0_1 |
			SAA7134_IRQ1_INTE_RA0_0;
		cap = dev->field;
	पूर्ण

	/* video capture -- dma 1+2 (planar modes) */
	अगर (dev->video_q.curr && dev->fmt->planar) अणु
		ctrl |= SAA7134_MAIN_CTRL_TE4 |
			SAA7134_MAIN_CTRL_TE5;
	पूर्ण

	/* screen overlay -- dma 0 + video task B */
	अगर (dev->ovenable) अणु
		task |= 0x10;
		ctrl |= SAA7134_MAIN_CTRL_TE1;
		ov = dev->ovfield;
	पूर्ण

	/* vbi capture -- dma 0 + vbi task A+B */
	अगर (dev->vbi_q.curr) अणु
		task |= 0x22;
		ctrl |= SAA7134_MAIN_CTRL_TE2 |
			SAA7134_MAIN_CTRL_TE3;
		irq  |= SAA7134_IRQ1_INTE_RA0_7 |
			SAA7134_IRQ1_INTE_RA0_6 |
			SAA7134_IRQ1_INTE_RA0_5 |
			SAA7134_IRQ1_INTE_RA0_4;
	पूर्ण

	/* audio capture -- dma 3 */
	अगर (dev->dmasound.dma_running) अणु
		ctrl |= SAA7134_MAIN_CTRL_TE6;
		irq  |= SAA7134_IRQ1_INTE_RA3_1 |
			SAA7134_IRQ1_INTE_RA3_0;
	पूर्ण

	/* TS capture -- dma 5 */
	अगर (dev->ts_q.curr) अणु
		ctrl |= SAA7134_MAIN_CTRL_TE5;
		irq  |= SAA7134_IRQ1_INTE_RA2_1 |
			SAA7134_IRQ1_INTE_RA2_0;
	पूर्ण

	/* set task conditions + field handling */
	अगर (V4L2_FIELD_HAS_BOTH(cap) || V4L2_FIELD_HAS_BOTH(ov) || cap == ov) अणु
		/* शेष config -- use full frames */
		saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0d);
		saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0d);
		saa_ग_लिखोb(SAA7134_FIELD_HANDLING(TASK_A),  0x02);
		saa_ग_लिखोb(SAA7134_FIELD_HANDLING(TASK_B),  0x02);
		split = 0;
	पूर्ण अन्यथा अणु
		/* split fields between tasks */
		अगर (V4L2_FIELD_TOP == cap) अणु
			/* odd A, even B, repeat */
			saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0d);
			saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0e);
		पूर्ण अन्यथा अणु
			/* odd B, even A, repeat */
			saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0e);
			saa_ग_लिखोb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0d);
		पूर्ण
		saa_ग_लिखोb(SAA7134_FIELD_HANDLING(TASK_A),  0x01);
		saa_ग_लिखोb(SAA7134_FIELD_HANDLING(TASK_B),  0x01);
		split = 1;
	पूर्ण

	/* irqs */
	saa_ग_लिखोb(SAA7134_REGION_ENABLE, task);
	saa_ग_लिखोl(SAA7134_IRQ1,          irq);
	saa_anकरोrl(SAA7134_MAIN_CTRL,
		   SAA7134_MAIN_CTRL_TE0 |
		   SAA7134_MAIN_CTRL_TE1 |
		   SAA7134_MAIN_CTRL_TE2 |
		   SAA7134_MAIN_CTRL_TE3 |
		   SAA7134_MAIN_CTRL_TE4 |
		   SAA7134_MAIN_CTRL_TE5 |
		   SAA7134_MAIN_CTRL_TE6,
		   ctrl);
	core_dbg("dmabits: task=0x%02x ctrl=0x%02x irq=0x%x split=%s\n",
		task, ctrl, irq, split ? "no" : "yes");

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* IRQ handler + helpers                                              */

अटल अक्षर *irqbits[] = अणु
	"DONE_RA0", "DONE_RA1", "DONE_RA2", "DONE_RA3",
	"AR", "PE", "PWR_ON", "RDCAP", "INTL", "FIDT", "MMC",
	"TRIG_ERR", "CONF_ERR", "LOAD_ERR",
	"GPIO16", "GPIO18", "GPIO22", "GPIO23"
पूर्ण;
#घोषणा IRQBITS ARRAY_SIZE(irqbits)

अटल व्योम prपूर्णांक_irqstatus(काष्ठा saa7134_dev *dev, पूर्णांक loop,
			    अचिन्हित दीर्घ report, अचिन्हित दीर्घ status)
अणु
	अचिन्हित पूर्णांक i;

	irq_dbg(1, "[%d,%ld]: r=0x%lx s=0x%02lx",
		loop, jअगरfies, report, status);
	क्रम (i = 0; i < IRQBITS; i++) अणु
		अगर (!(report & (1 << i)))
			जारी;
		pr_cont(" %s", irqbits[i]);
	पूर्ण
	अगर (report & SAA7134_IRQ_REPORT_DONE_RA0) अणु
		pr_cont(" | RA0=%s,%s,%s,%ld",
			(status & 0x40) ? "vbi"  : "video",
			(status & 0x20) ? "b"    : "a",
			(status & 0x10) ? "odd"  : "even",
			(status & 0x0f));
	पूर्ण
	pr_cont("\n");
पूर्ण

अटल irqवापस_t saa7134_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा saa7134_dev *dev = (काष्ठा saa7134_dev*) dev_id;
	अचिन्हित दीर्घ report,status;
	पूर्णांक loop, handled = 0;

	अगर (dev->insuspend)
		जाओ out;

	क्रम (loop = 0; loop < 10; loop++) अणु
		report = saa_पढ़ोl(SAA7134_IRQ_REPORT);
		status = saa_पढ़ोl(SAA7134_IRQ_STATUS);

		/* If dmasound support is active and we get a sound report,
		 * mask out the report and let the saa7134-alsa module deal
		 * with it */
		अगर ((report & SAA7134_IRQ_REPORT_DONE_RA3) &&
			(dev->dmasound.priv_data != शून्य) )
		अणु
			irq_dbg(2, "preserving DMA sound interrupt\n");
			report &= ~SAA7134_IRQ_REPORT_DONE_RA3;
		पूर्ण

		अगर (0 == report) अणु
			irq_dbg(2, "no (more) work\n");
			जाओ out;
		पूर्ण

		handled = 1;
		saa_ग_लिखोl(SAA7134_IRQ_REPORT,report);
		अगर (irq_debug)
			prपूर्णांक_irqstatus(dev,loop,report,status);


		अगर ((report & SAA7134_IRQ_REPORT_RDCAP) ||
			(report & SAA7134_IRQ_REPORT_INTL))
				saa7134_irq_video_संकेतchange(dev);


		अगर ((report & SAA7134_IRQ_REPORT_DONE_RA0) &&
		    (status & 0x60) == 0)
			saa7134_irq_video_करोne(dev,status);

		अगर ((report & SAA7134_IRQ_REPORT_DONE_RA0) &&
		    (status & 0x40) == 0x40)
			saa7134_irq_vbi_करोne(dev,status);

		अगर ((report & SAA7134_IRQ_REPORT_DONE_RA2) &&
		    card_has_mpeg(dev)) अणु
			अगर (dev->mops->irq_ts_करोne != शून्य)
				dev->mops->irq_ts_करोne(dev, status);
			अन्यथा
				saa7134_irq_ts_करोne(dev, status);
		पूर्ण

		अगर (report & SAA7134_IRQ_REPORT_GPIO16) अणु
			चयन (dev->has_remote) अणु
				हाल SAA7134_REMOTE_GPIO:
					अगर (!dev->remote)
						अवरोध;
					अगर  (dev->remote->mask_keyकरोwn & 0x10000) अणु
						saa7134_input_irq(dev);
					पूर्ण
					अवरोध;

				हाल SAA7134_REMOTE_I2C:
					अवरोध;			/* FIXME: invoke I2C get_key() */

				शेष:			/* GPIO16 not used by IR remote */
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (report & SAA7134_IRQ_REPORT_GPIO18) अणु
			चयन (dev->has_remote) अणु
				हाल SAA7134_REMOTE_GPIO:
					अगर (!dev->remote)
						अवरोध;
					अगर ((dev->remote->mask_keyकरोwn & 0x40000) ||
					    (dev->remote->mask_keyup & 0x40000)) अणु
						saa7134_input_irq(dev);
					पूर्ण
					अवरोध;

				हाल SAA7134_REMOTE_I2C:
					अवरोध;			/* FIXME: invoke I2C get_key() */

				शेष:			/* GPIO18 not used by IR remote */
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (10 == loop) अणु
		prपूर्णांक_irqstatus(dev,loop,report,status);
		अगर (report & SAA7134_IRQ_REPORT_PE) अणु
			/* disable all parity error */
			pr_warn("%s/irq: looping -- clearing PE (parity error!) enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2,SAA7134_IRQ2_INTE_PE);
		पूर्ण अन्यथा अगर (report & SAA7134_IRQ_REPORT_GPIO16) अणु
			/* disable gpio16 IRQ */
			pr_warn("%s/irq: looping -- clearing GPIO16 enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO16_P);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO16_N);
		पूर्ण अन्यथा अगर (report & SAA7134_IRQ_REPORT_GPIO18) अणु
			/* disable gpio18 IRQs */
			pr_warn("%s/irq: looping -- clearing GPIO18 enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO18_P);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO18_N);
		पूर्ण अन्यथा अणु
			/* disable all irqs */
			pr_warn("%s/irq: looping -- clearing all enable bits\n",
				dev->name);
			saa_ग_लिखोl(SAA7134_IRQ1,0);
			saa_ग_लिखोl(SAA7134_IRQ2,0);
		पूर्ण
	पूर्ण

 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

/* ------------------------------------------------------------------ */

/* early init (no i2c, no irq) */

अटल पूर्णांक saa7134_hw_enable1(काष्ठा saa7134_dev *dev)
अणु
	/* RAM FIFO config */
	saa_ग_लिखोl(SAA7134_FIFO_SIZE, 0x08070503);
	saa_ग_लिखोl(SAA7134_THRESHOULD, 0x02020202);

	/* enable audio + video processing */
	saa_ग_लिखोl(SAA7134_MAIN_CTRL,
			SAA7134_MAIN_CTRL_VPLLE |
			SAA7134_MAIN_CTRL_APLLE |
			SAA7134_MAIN_CTRL_EXOSC |
			SAA7134_MAIN_CTRL_EVFE1 |
			SAA7134_MAIN_CTRL_EVFE2 |
			SAA7134_MAIN_CTRL_ESFE  |
			SAA7134_MAIN_CTRL_EBDAC);

	/*
	* Initialize OSS _after_ enabling audio घड़ी PLL and audio processing.
	* OSS initialization ग_लिखोs to रेजिस्टरs via the audio DSP; these
	* ग_लिखोs will fail unless the audio घड़ी has been started.  At worst,
	* audio will not work.
	*/

	/* enable peripheral devices */
	saa_ग_लिखोb(SAA7134_SPECIAL_MODE, 0x01);

	/* set vertical line numbering start (vbi needs this) */
	saa_ग_लिखोb(SAA7134_SOURCE_TIMING2, 0x20);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_hwinit1(काष्ठा saa7134_dev *dev)
अणु
	core_dbg("hwinit1\n");

	saa_ग_लिखोl(SAA7134_IRQ1, 0);
	saa_ग_लिखोl(SAA7134_IRQ2, 0);

	/* Clear any stale IRQ reports */
	saa_ग_लिखोl(SAA7134_IRQ_REPORT, saa_पढ़ोl(SAA7134_IRQ_REPORT));

	mutex_init(&dev->lock);
	spin_lock_init(&dev->slock);

	saa7134_track_gpio(dev,"pre-init");
	saa7134_video_init1(dev);
	saa7134_vbi_init1(dev);
	अगर (card_has_mpeg(dev))
		saa7134_ts_init1(dev);
	saa7134_input_init1(dev);

	saa7134_hw_enable1(dev);

	वापस 0;
पूर्ण

/* late init (with i2c + irq) */
अटल पूर्णांक saa7134_hw_enable2(काष्ठा saa7134_dev *dev)
अणु

	अचिन्हित पूर्णांक irq2_mask;

	/* enable IRQ's */
	irq2_mask =
		SAA7134_IRQ2_INTE_DEC3    |
		SAA7134_IRQ2_INTE_DEC2    |
		SAA7134_IRQ2_INTE_DEC1    |
		SAA7134_IRQ2_INTE_DEC0    |
		SAA7134_IRQ2_INTE_PE      |
		SAA7134_IRQ2_INTE_AR;

	अगर (dev->has_remote == SAA7134_REMOTE_GPIO && dev->remote) अणु
		अगर (dev->remote->mask_keyकरोwn & 0x10000)
			irq2_mask |= SAA7134_IRQ2_INTE_GPIO16_N;
		अन्यथा अणु		/* Allow enabling both IRQ edge triggers */
			अगर (dev->remote->mask_keyकरोwn & 0x40000)
				irq2_mask |= SAA7134_IRQ2_INTE_GPIO18_P;
			अगर (dev->remote->mask_keyup & 0x40000)
				irq2_mask |= SAA7134_IRQ2_INTE_GPIO18_N;
		पूर्ण
	पूर्ण

	अगर (dev->has_remote == SAA7134_REMOTE_I2C) अणु
		request_module("ir-kbd-i2c");
	पूर्ण

	saa_ग_लिखोl(SAA7134_IRQ1, 0);
	saa_ग_लिखोl(SAA7134_IRQ2, irq2_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_hwinit2(काष्ठा saa7134_dev *dev)
अणु

	core_dbg("hwinit2\n");

	saa7134_video_init2(dev);
	saa7134_tvaudio_init2(dev);

	saa7134_hw_enable2(dev);

	वापस 0;
पूर्ण


/* shutकरोwn */
अटल पूर्णांक saa7134_hwfini(काष्ठा saa7134_dev *dev)
अणु
	core_dbg("hwfini\n");

	अगर (card_has_mpeg(dev))
		saa7134_ts_fini(dev);
	saa7134_input_fini(dev);
	saa7134_vbi_fini(dev);
	saa7134_tvaudio_fini(dev);
	saa7134_video_fini(dev);
	वापस 0;
पूर्ण

अटल व्योम must_configure_manually(पूर्णांक has_eeprom)
अणु
	अचिन्हित पूर्णांक i,p;

	अगर (!has_eeprom)
		pr_warn("saa7134: <rant>\n"
			"saa7134:  Congratulations!  Your TV card vendor saved a few\n"
			"saa7134:  cents for a eeprom, thus your pci board has no\n"
			"saa7134:  subsystem ID and I can't identify it automatically\n"
			"saa7134: </rant>\n"
			"saa7134: I feel better now.  Ok, here are the good news:\n"
			"saa7134: You can use the card=<nr> insmod option to specify\n"
			"saa7134: which board do you have.  The list:\n");
	अन्यथा
		pr_warn("saa7134: Board is currently unknown. You might try to use the card=<nr>\n"
			"saa7134: insmod option to specify which board do you have, but this is\n"
			"saa7134: somewhat risky, as might damage your card. It is better to ask\n"
			"saa7134: for support at linux-media@vger.kernel.org.\n"
			"saa7134: The supported cards are:\n");

	क्रम (i = 0; i < saa7134_bcount; i++) अणु
		pr_warn("saa7134:   card=%d -> %-40.40s",
		       i,saa7134_boards[i].name);
		क्रम (p = 0; saa7134_pci_tbl[p].driver_data; p++) अणु
			अगर (saa7134_pci_tbl[p].driver_data != i)
				जारी;
			pr_cont(" %04x:%04x",
			       saa7134_pci_tbl[p].subvenकरोr,
			       saa7134_pci_tbl[p].subdevice);
		पूर्ण
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम saa7134_unरेजिस्टर_media_device(काष्ठा saa7134_dev *dev)
अणु

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	अगर (!dev->media_dev)
		वापस;
	media_device_unरेजिस्टर(dev->media_dev);
	media_device_cleanup(dev->media_dev);
	kमुक्त(dev->media_dev);
	dev->media_dev = शून्य;
#पूर्ण_अगर
पूर्ण

अटल व्योम saa7134_media_release(काष्ठा saa7134_dev *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक i;

	क्रम (i = 0; i < SAA7134_INPUT_MAX + 1; i++)
		media_device_unरेजिस्टर_entity(&dev->input_ent[i]);
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_MEDIA_CONTROLLER)
अटल व्योम saa7134_create_entities(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक ret, i;
	काष्ठा media_entity *entity;
	काष्ठा media_entity *decoder = शून्य;

	/* Check अगर it is using an बाह्यal analog TV demod */
	media_device_क्रम_each_entity(entity, dev->media_dev) अणु
		अगर (entity->function == MEDIA_ENT_F_ATV_DECODER) अणु
			decoder = entity;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * saa713x is not using an बाह्यal ATV demod.
	 * Register the पूर्णांकernal one
	 */
	अगर (!decoder) अणु
		dev->demod.name = "saa713x";
		dev->demod_pad[SAA7134_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
		dev->demod_pad[SAA7134_PAD_IF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
		dev->demod_pad[SAA7134_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
		dev->demod_pad[SAA7134_PAD_VID_OUT].sig_type = PAD_SIGNAL_DV;
		dev->demod.function = MEDIA_ENT_F_ATV_DECODER;

		ret = media_entity_pads_init(&dev->demod, SAA7134_NUM_PADS,
					     dev->demod_pad);
		अगर (ret < 0)
			pr_err("failed to initialize demod pad!\n");

		ret = media_device_रेजिस्टर_entity(dev->media_dev, &dev->demod);
		अगर (ret < 0)
			pr_err("failed to register demod entity!\n");

		dev->decoder = &dev->demod;
	पूर्ण अन्यथा अणु
		dev->decoder = decoder;
	पूर्ण

	/* Initialize Video, VBI and Radio pads */
	dev->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->video_dev->entity, 1,
				     &dev->video_pad);
	अगर (ret < 0)
		pr_err("failed to initialize video media entity!\n");

	dev->vbi_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vbi_dev->entity, 1,
					&dev->vbi_pad);
	अगर (ret < 0)
		pr_err("failed to initialize vbi media entity!\n");

	/* Create entities क्रम each input connector */
	क्रम (i = 0; i < SAA7134_INPUT_MAX; i++) अणु
		काष्ठा media_entity *ent = &dev->input_ent[i];
		काष्ठा saa7134_input *in = &card_in(dev, i);

		अगर (in->type == SAA7134_NO_INPUT)
			अवरोध;

		/* This input uses the S-Video connector */
		अगर (in->type == SAA7134_INPUT_COMPOSITE_OVER_SVIDEO)
			जारी;

		ent->name = saa7134_input_name[in->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		चयन (in->type) अणु
		हाल SAA7134_INPUT_COMPOSITE:
		हाल SAA7134_INPUT_COMPOSITE0:
		हाल SAA7134_INPUT_COMPOSITE1:
		हाल SAA7134_INPUT_COMPOSITE2:
		हाल SAA7134_INPUT_COMPOSITE3:
		हाल SAA7134_INPUT_COMPOSITE4:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			अवरोध;
		हाल SAA7134_INPUT_SVIDEO:
		हाल SAA7134_INPUT_SVIDEO0:
		हाल SAA7134_INPUT_SVIDEO1:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			अवरोध;
		शेष:
			/*
			 * SAA7134_INPUT_TV and SAA7134_INPUT_TV_MONO.
			 *
			 * Please notice that neither SAA7134_INPUT_MUTE or
			 * SAA7134_INPUT_RADIO are defined at
			 * saa7134_board.input.
			 */
			ent->function = MEDIA_ENT_F_CONN_RF;
			अवरोध;
		पूर्ण

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		अगर (ret < 0)
			pr_err("failed to initialize input pad[%d]!\n", i);

		ret = media_device_रेजिस्टर_entity(dev->media_dev, ent);
		अगर (ret < 0)
			pr_err("failed to register input entity %d!\n", i);
	पूर्ण

	/* Create input क्रम Radio RF connector */
	अगर (card_has_radio(dev)) अणु
		काष्ठा saa7134_input *in = &saa7134_boards[dev->board].radio;
		काष्ठा media_entity *ent = &dev->input_ent[i];

		ent->name = saa7134_input_name[in->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;
		ent->function = MEDIA_ENT_F_CONN_RF;

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		अगर (ret < 0)
			pr_err("failed to initialize input pad[%d]!\n", i);

		ret = media_device_रेजिस्टर_entity(dev->media_dev, ent);
		अगर (ret < 0)
			pr_err("failed to register input entity %d!\n", i);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा video_device *vdev_init(काष्ठा saa7134_dev *dev,
				      काष्ठा video_device *ढाँचा,
				      अक्षर *type)
अणु
	काष्ठा video_device *vfd;

	vfd = video_device_alloc();
	अगर (शून्य == vfd)
		वापस शून्य;
	*vfd = *ढाँचा;
	vfd->v4l2_dev  = &dev->v4l2_dev;
	vfd->release = video_device_release;
	snम_लिखो(vfd->name, माप(vfd->name), "%s %s (%s)",
		 dev->name, type, saa7134_boards[dev->board].name);
	video_set_drvdata(vfd, dev);
	वापस vfd;
पूर्ण

अटल व्योम saa7134_unरेजिस्टर_video(काष्ठा saa7134_dev *dev)
अणु
	saa7134_media_release(dev);

	अगर (dev->video_dev) अणु
		अगर (video_is_रेजिस्टरed(dev->video_dev))
			vb2_video_unरेजिस्टर_device(dev->video_dev);
		अन्यथा
			video_device_release(dev->video_dev);
		dev->video_dev = शून्य;
	पूर्ण
	अगर (dev->vbi_dev) अणु
		अगर (video_is_रेजिस्टरed(dev->vbi_dev))
			vb2_video_unरेजिस्टर_device(dev->vbi_dev);
		अन्यथा
			video_device_release(dev->vbi_dev);
		dev->vbi_dev = शून्य;
	पूर्ण
	अगर (dev->radio_dev) अणु
		अगर (video_is_रेजिस्टरed(dev->radio_dev))
			vb2_video_unरेजिस्टर_device(dev->radio_dev);
		अन्यथा
			video_device_release(dev->radio_dev);
		dev->radio_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mpeg_ops_attach(काष्ठा saa7134_mpeg_ops *ops,
			    काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक err;

	अगर (शून्य != dev->mops)
		वापस;
	अगर (saa7134_boards[dev->board].mpeg != ops->type)
		वापस;
	err = ops->init(dev);
	अगर (0 != err)
		वापस;
	dev->mops = ops;
पूर्ण

अटल व्योम mpeg_ops_detach(काष्ठा saa7134_mpeg_ops *ops,
			    काष्ठा saa7134_dev *dev)
अणु
	अगर (शून्य == dev->mops)
		वापस;
	अगर (dev->mops != ops)
		वापस;
	dev->mops->fini(dev);
	dev->mops = शून्य;
पूर्ण

अटल पूर्णांक saa7134_initdev(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा saa7134_dev *dev;
	काष्ठा saa7134_mpeg_ops *mops;
	पूर्णांक err;

	अगर (saa7134_devcount == SAA7134_MAXBOARDS)
		वापस -ENOMEM;

	dev = kzalloc(माप(*dev),GFP_KERNEL);
	अगर (शून्य == dev)
		वापस -ENOMEM;

	dev->nr = saa7134_devcount;
	प्र_लिखो(dev->name, "saa%x[%d]", pci_dev->device, dev->nr);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->media_dev = kzalloc(माप(*dev->media_dev), GFP_KERNEL);
	अगर (!dev->media_dev) अणु
		err = -ENOMEM;
		जाओ fail0;
	पूर्ण
	media_device_pci_init(dev->media_dev, pci_dev, dev->name);
	dev->v4l2_dev.mdev = dev->media_dev;
#पूर्ण_अगर

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err)
		जाओ fail0;

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ fail1;
	पूर्ण

	/* pci quirks */
	अगर (pci_pci_problems) अणु
		अगर (pci_pci_problems & PCIPCI_TRITON)
			pr_info("%s: quirk: PCIPCI_TRITON\n", dev->name);
		अगर (pci_pci_problems & PCIPCI_NATOMA)
			pr_info("%s: quirk: PCIPCI_NATOMA\n", dev->name);
		अगर (pci_pci_problems & PCIPCI_VIAETBF)
			pr_info("%s: quirk: PCIPCI_VIAETBF\n", dev->name);
		अगर (pci_pci_problems & PCIPCI_VSFX)
			pr_info("%s: quirk: PCIPCI_VSFX\n", dev->name);
#अगर_घोषित PCIPCI_ALIMAGIK
		अगर (pci_pci_problems & PCIPCI_ALIMAGIK) अणु
			pr_info("%s: quirk: PCIPCI_ALIMAGIK -- latency fixup\n",
			       dev->name);
			latency = 0x0A;
		पूर्ण
#पूर्ण_अगर
		अगर (pci_pci_problems & (PCIPCI_FAIL|PCIAGP_FAIL)) अणु
			pr_info("%s: quirk: this driver and your chipset may not work together in overlay mode.\n",
				dev->name);
			अगर (!saa7134_no_overlay) अणु
				pr_info("%s: quirk: overlay mode will be disabled.\n",
						dev->name);
				saa7134_no_overlay = 1;
			पूर्ण अन्यथा अणु
				pr_info("%s: quirk: overlay mode will be forced. Use this option at your own risk.\n",
						dev->name);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (UNSET != latency) अणु
		pr_info("%s: setting pci latency timer to %d\n",
		       dev->name,latency);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, latency);
	पूर्ण

	/* prपूर्णांक pci info */
	dev->pci_rev = pci_dev->revision;
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("%s: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		dev->name, pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
		dev->pci_lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));
	pci_set_master(pci_dev);
	err = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		pr_warn("%s: Oops: no 32bit PCI DMA ???\n", dev->name);
		जाओ fail1;
	पूर्ण

	/* board config */
	dev->board = pci_id->driver_data;
	अगर ((अचिन्हित)card[dev->nr] < saa7134_bcount)
		dev->board = card[dev->nr];
	अगर (SAA7134_BOARD_UNKNOWN == dev->board)
		must_configure_manually(0);
	अन्यथा अगर (SAA7134_BOARD_NOAUTO == dev->board) अणु
		must_configure_manually(1);
		dev->board = SAA7134_BOARD_UNKNOWN;
	पूर्ण
	dev->स्वतःdetected = card[dev->nr] != dev->board;
	dev->tuner_type = saa7134_boards[dev->board].tuner_type;
	dev->tuner_addr = saa7134_boards[dev->board].tuner_addr;
	dev->radio_type = saa7134_boards[dev->board].radio_type;
	dev->radio_addr = saa7134_boards[dev->board].radio_addr;
	dev->tda9887_conf = saa7134_boards[dev->board].tda9887_conf;
	अगर (UNSET != tuner[dev->nr])
		dev->tuner_type = tuner[dev->nr];
	pr_info("%s: subsystem: %04x:%04x, board: %s [card=%d,%s]\n",
		dev->name,pci_dev->subप्रणाली_venकरोr,
		pci_dev->subप्रणाली_device,saa7134_boards[dev->board].name,
		dev->board, dev->स्वतःdetected ?
		"autodetected" : "insmod option");

	/* get mmio */
	अगर (!request_mem_region(pci_resource_start(pci_dev,0),
				pci_resource_len(pci_dev,0),
				dev->name)) अणु
		err = -EBUSY;
		pr_err("%s: can't get MMIO memory @ 0x%llx\n",
		       dev->name,(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev,0));
		जाओ fail1;
	पूर्ण
	dev->lmmio = ioremap(pci_resource_start(pci_dev, 0),
			     pci_resource_len(pci_dev, 0));
	dev->bmmio = (__u8 __iomem *)dev->lmmio;
	अगर (शून्य == dev->lmmio) अणु
		err = -EIO;
		pr_err("%s: can't ioremap() MMIO memory\n",
		       dev->name);
		जाओ fail2;
	पूर्ण

	/* initialize hardware #1 */
	saa7134_board_init1(dev);
	saa7134_hwinit1(dev);

	/* get irq */
	err = request_irq(pci_dev->irq, saa7134_irq,
			  IRQF_SHARED, dev->name, dev);
	अगर (err < 0) अणु
		pr_err("%s: can't get IRQ %d\n",
		       dev->name,pci_dev->irq);
		जाओ fail3;
	पूर्ण

	/* रुको a bit, रेजिस्टर i2c bus */
	msleep(100);
	saa7134_i2c_रेजिस्टर(dev);
	saa7134_board_init2(dev);

	saa7134_hwinit2(dev);

	/* load i2c helpers */
	अगर (card_is_empress(dev)) अणु
		dev->empress_sd =
			v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"saa6752hs",
				saa7134_boards[dev->board].empress_addr, शून्य);

		अगर (dev->empress_sd)
			dev->empress_sd->grp_id = GRP_EMPRESS;
	पूर्ण

	अगर (saa7134_boards[dev->board].rds_addr) अणु
		काष्ठा v4l2_subdev *sd;

		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "saa6588",
				0, I2C_ADDRS(saa7134_boards[dev->board].rds_addr));
		अगर (sd) अणु
			pr_info("%s: found RDS decoder\n", dev->name);
			dev->has_rds = 1;
		पूर्ण
	पूर्ण

	mutex_lock(&saa7134_devlist_lock);
	list_क्रम_each_entry(mops, &mops_list, next)
		mpeg_ops_attach(mops, dev);
	list_add_tail(&dev->devlist, &saa7134_devlist);
	mutex_unlock(&saa7134_devlist_lock);

	/* check क्रम संकेत */
	saa7134_irq_video_संकेतchange(dev);

	अगर (TUNER_ABSENT != dev->tuner_type)
		saa_call_all(dev, core, s_घातer, 0);

	/* रेजिस्टर v4l devices */
	अगर (saa7134_no_overlay > 0)
		pr_info("%s: Overlay support disabled.\n", dev->name);

	dev->video_dev = vdev_init(dev,&saa7134_video_ढाँचा,"video");
	dev->video_dev->ctrl_handler = &dev->ctrl_handler;
	dev->video_dev->lock = &dev->lock;
	dev->video_dev->queue = &dev->video_vbq;
	dev->video_dev->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				      V4L2_CAP_VIDEO_CAPTURE;
	अगर (dev->tuner_type != TUNER_ABSENT && dev->tuner_type != UNSET)
		dev->video_dev->device_caps |= V4L2_CAP_TUNER;

	अगर (saa7134_no_overlay <= 0)
		dev->video_dev->device_caps |= V4L2_CAP_VIDEO_OVERLAY;

	err = video_रेजिस्टर_device(dev->video_dev,VFL_TYPE_VIDEO,
				    video_nr[dev->nr]);
	अगर (err < 0) अणु
		pr_info("%s: can't register video device\n",
		       dev->name);
		जाओ fail4;
	पूर्ण
	pr_info("%s: registered device %s [v4l2]\n",
	       dev->name, video_device_node_name(dev->video_dev));

	dev->vbi_dev = vdev_init(dev, &saa7134_video_ढाँचा, "vbi");
	dev->vbi_dev->ctrl_handler = &dev->ctrl_handler;
	dev->vbi_dev->lock = &dev->lock;
	dev->vbi_dev->queue = &dev->vbi_vbq;
	dev->vbi_dev->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				    V4L2_CAP_VBI_CAPTURE;
	अगर (dev->tuner_type != TUNER_ABSENT && dev->tuner_type != UNSET)
		dev->vbi_dev->device_caps |= V4L2_CAP_TUNER;

	err = video_रेजिस्टर_device(dev->vbi_dev,VFL_TYPE_VBI,
				    vbi_nr[dev->nr]);
	अगर (err < 0)
		जाओ fail4;
	pr_info("%s: registered device %s\n",
	       dev->name, video_device_node_name(dev->vbi_dev));

	अगर (card_has_radio(dev)) अणु
		dev->radio_dev = vdev_init(dev,&saa7134_radio_ढाँचा,"radio");
		dev->radio_dev->ctrl_handler = &dev->radio_ctrl_handler;
		dev->radio_dev->lock = &dev->lock;
		dev->radio_dev->device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		अगर (dev->has_rds)
			dev->radio_dev->device_caps |= V4L2_CAP_RDS_CAPTURE;
		err = video_रेजिस्टर_device(dev->radio_dev,VFL_TYPE_RADIO,
					    radio_nr[dev->nr]);
		अगर (err < 0)
			जाओ fail4;
		pr_info("%s: registered device %s\n",
		       dev->name, video_device_node_name(dev->radio_dev));
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	saa7134_create_entities(dev);

	err = v4l2_mc_create_media_graph(dev->media_dev);
	अगर (err) अणु
		pr_err("failed to create media graph\n");
		जाओ fail4;
	पूर्ण
#पूर्ण_अगर
	/* everything worked */
	saa7134_devcount++;

	अगर (saa7134_dmasound_init && !dev->dmasound.priv_data)
		saa7134_dmasound_init(dev);

	request_submodules(dev);

	/*
	 * Do it at the end, to reduce dynamic configuration changes during
	 * the device init. Yet, as request_modules() can be async, the
	 * topology will likely change after load the saa7134 subdrivers.
	 */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	err = media_device_रेजिस्टर(dev->media_dev);
	अगर (err)
		जाओ fail4;
#पूर्ण_अगर

	वापस 0;

 fail4:
	saa7134_unरेजिस्टर_video(dev);
	saa7134_i2c_unरेजिस्टर(dev);
	मुक्त_irq(pci_dev->irq, dev);
 fail3:
	saa7134_hwfini(dev);
	iounmap(dev->lmmio);
 fail2:
	release_mem_region(pci_resource_start(pci_dev,0),
			   pci_resource_len(pci_dev,0));
 fail1:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
 fail0:
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	kमुक्त(dev->media_dev);
#पूर्ण_अगर
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम saa7134_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा saa7134_dev *dev = container_of(v4l2_dev, काष्ठा saa7134_dev, v4l2_dev);
	काष्ठा saa7134_mpeg_ops *mops;

	flush_request_submodules(dev);

	/* Release DMA sound modules अगर present */
	अगर (saa7134_dmasound_निकास && dev->dmasound.priv_data) अणु
		saa7134_dmasound_निकास(dev);
	पूर्ण

	/* debugging ... */
	अगर (irq_debug) अणु
		u32 report = saa_पढ़ोl(SAA7134_IRQ_REPORT);
		u32 status = saa_पढ़ोl(SAA7134_IRQ_STATUS);
		prपूर्णांक_irqstatus(dev,42,report,status);
	पूर्ण

	/* disable peripheral devices */
	saa_ग_लिखोb(SAA7134_SPECIAL_MODE,0);

	/* shutकरोwn hardware */
	saa_ग_लिखोl(SAA7134_IRQ1,0);
	saa_ग_लिखोl(SAA7134_IRQ2,0);
	saa_ग_लिखोl(SAA7134_MAIN_CTRL,0);

	/* shutकरोwn subप्रणालीs */
	saa7134_hwfini(dev);

	/* unरेजिस्टर */
	mutex_lock(&saa7134_devlist_lock);
	list_del(&dev->devlist);
	list_क्रम_each_entry(mops, &mops_list, next)
		mpeg_ops_detach(mops, dev);
	mutex_unlock(&saa7134_devlist_lock);
	saa7134_devcount--;

	saa7134_i2c_unरेजिस्टर(dev);
	saa7134_unरेजिस्टर_video(dev);


	/* the DMA sound modules should be unloaded beक्रमe reaching
	   this, but just in हाल they are still present... */
	अगर (dev->dmasound.priv_data != शून्य) अणु
		मुक्त_irq(pci_dev->irq, &dev->dmasound);
		dev->dmasound.priv_data = शून्य;
	पूर्ण


	/* release resources */
	मुक्त_irq(pci_dev->irq, dev);
	iounmap(dev->lmmio);
	release_mem_region(pci_resource_start(pci_dev,0),
			   pci_resource_len(pci_dev,0));

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	saa7134_unरेजिस्टर_media_device(dev);

	/* मुक्त memory */
	kमुक्त(dev);
पूर्ण

/* resends a current buffer in queue after resume */
अटल पूर्णांक __maybe_unused saa7134_buffer_requeue(काष्ठा saa7134_dev *dev,
						 काष्ठा saa7134_dmaqueue *q)
अणु
	काष्ठा saa7134_buf *buf, *next;

	निश्चित_spin_locked(&dev->slock);

	buf  = q->curr;
	next = buf;
	core_dbg("buffer_requeue\n");

	अगर (!buf)
		वापस 0;

	core_dbg("buffer_requeue : resending active buffer\n");

	अगर (!list_empty(&q->queue))
		next = list_entry(q->queue.next, काष्ठा saa7134_buf,
					  entry);
	buf->activate(dev, buf, next);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused saa7134_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev_d);
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा saa7134_dev *dev = container_of(v4l2_dev, काष्ठा saa7134_dev, v4l2_dev);

	/* disable overlay - apps should enable it explicitly on resume*/
	dev->ovenable = 0;

	/* Disable पूर्णांकerrupts, DMA, and rest of the chip*/
	saa_ग_लिखोl(SAA7134_IRQ1, 0);
	saa_ग_लिखोl(SAA7134_IRQ2, 0);
	saa_ग_लिखोl(SAA7134_MAIN_CTRL, 0);

	dev->insuspend = 1;
	synchronize_irq(pci_dev->irq);

	/* ACK पूर्णांकerrupts once more, just in हाल,
		since the IRQ handler won't ack them anymore*/

	saa_ग_लिखोl(SAA7134_IRQ_REPORT, saa_पढ़ोl(SAA7134_IRQ_REPORT));

	/* Disable समयout समयrs - अगर we have active buffers, we will
	   fill them on resume*/

	del_समयr(&dev->video_q.समयout);
	del_समयr(&dev->vbi_q.समयout);
	del_समयr(&dev->ts_q.समयout);

	अगर (dev->remote && dev->remote->dev->users)
		saa7134_ir_बंद(dev->remote->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused saa7134_resume(काष्ठा device *dev_d)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev_d);
	काष्ठा saa7134_dev *dev = container_of(v4l2_dev, काष्ठा saa7134_dev, v4l2_dev);
	अचिन्हित दीर्घ flags;

	/* Do things that are करोne in saa7134_initdev ,
		except of initializing memory काष्ठाures.*/

	saa7134_board_init1(dev);

	/* saa7134_hwinit1 */
	अगर (saa7134_boards[dev->board].video_out)
		saa7134_videoport_init(dev);
	अगर (card_has_mpeg(dev))
		saa7134_ts_init_hw(dev);
	अगर (dev->remote && dev->remote->dev->users)
		saa7134_ir_खोलो(dev->remote->dev);
	saa7134_hw_enable1(dev);

	msleep(100);

	saa7134_board_init2(dev);

	/*saa7134_hwinit2*/
	saa7134_set_tvnorm_hw(dev);
	saa7134_tvaudio_seपंचांगute(dev);
	saa7134_tvaudio_setvolume(dev, dev->ctl_volume);
	saa7134_tvaudio_init(dev);
	saa7134_enable_i2s(dev);
	saa7134_hw_enable2(dev);

	saa7134_irq_video_संकेतchange(dev);

	/*resume unfinished buffer(s)*/
	spin_lock_irqsave(&dev->slock, flags);
	saa7134_buffer_requeue(dev, &dev->video_q);
	saa7134_buffer_requeue(dev, &dev->vbi_q);
	saa7134_buffer_requeue(dev, &dev->ts_q);

	/* FIXME: Disable DMA audio sound - temporary till proper support
		  is implemented*/

	dev->dmasound.dma_running = 0;

	/* start DMA now*/
	dev->insuspend = 0;
	smp_wmb();
	saa7134_set_dmabits(dev);
	spin_unlock_irqrestore(&dev->slock, flags);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------- */

पूर्णांक saa7134_ts_रेजिस्टर(काष्ठा saa7134_mpeg_ops *ops)
अणु
	काष्ठा saa7134_dev *dev;

	mutex_lock(&saa7134_devlist_lock);
	list_क्रम_each_entry(dev, &saa7134_devlist, devlist)
		mpeg_ops_attach(ops, dev);
	list_add_tail(&ops->next,&mops_list);
	mutex_unlock(&saa7134_devlist_lock);
	वापस 0;
पूर्ण

व्योम saa7134_ts_unरेजिस्टर(काष्ठा saa7134_mpeg_ops *ops)
अणु
	काष्ठा saa7134_dev *dev;

	mutex_lock(&saa7134_devlist_lock);
	list_del(&ops->next);
	list_क्रम_each_entry(dev, &saa7134_devlist, devlist)
		mpeg_ops_detach(ops, dev);
	mutex_unlock(&saa7134_devlist_lock);
पूर्ण

EXPORT_SYMBOL(saa7134_ts_रेजिस्टर);
EXPORT_SYMBOL(saa7134_ts_unरेजिस्टर);

/* ----------------------------------------------------------- */

अटल SIMPLE_DEV_PM_OPS(saa7134_pm_ops, saa7134_suspend, saa7134_resume);

अटल काष्ठा pci_driver saa7134_pci_driver = अणु
	.name     = "saa7134",
	.id_table = saa7134_pci_tbl,
	.probe    = saa7134_initdev,
	.हटाओ   = saa7134_finidev,
	.driver.pm = &saa7134_pm_ops,
पूर्ण;

अटल पूर्णांक __init saa7134_init(व्योम)
अणु
	INIT_LIST_HEAD(&saa7134_devlist);
	pr_info("saa7130/34: v4l2 driver version %s loaded\n",
	       SAA7134_VERSION);
	वापस pci_रेजिस्टर_driver(&saa7134_pci_driver);
पूर्ण

अटल व्योम __निकास saa7134_fini(व्योम)
अणु
	pci_unरेजिस्टर_driver(&saa7134_pci_driver);
पूर्ण

module_init(saa7134_init);
module_निकास(saa7134_fini);

/* ----------------------------------------------------------- */

EXPORT_SYMBOL(saa7134_set_gpio);
EXPORT_SYMBOL(saa7134_boards);

/* ----------------- क्रम the DMA sound modules --------------- */

EXPORT_SYMBOL(saa7134_dmasound_init);
EXPORT_SYMBOL(saa7134_dmasound_निकास);
EXPORT_SYMBOL(saa7134_pgtable_मुक्त);
EXPORT_SYMBOL(saa7134_pgtable_build);
EXPORT_SYMBOL(saa7134_pgtable_alloc);
EXPORT_SYMBOL(saa7134_set_dmabits);
