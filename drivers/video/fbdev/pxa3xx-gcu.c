<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pxa3xx-gcu.c - Linux kernel module क्रम PXA3xx graphics controllers
 *
 *  This driver needs a DirectFB counterpart in user space, communication
 *  is handled via mmap()ed memory areas and an ioctl.
 *
 *  Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 *  Copyright (c) 2009 Janine Kropp <nin@directfb.org>
 *  Copyright (c) 2009 Denis Oliver Kropp <करोk@directfb.org>
 */

/*
 * WARNING: This controller is attached to System Bus 2 of the PXA which
 * needs its arbiter to be enabled explicitly (CKENB & 1<<9).
 * There is currently no way to करो this from Linux, so you need to teach
 * your bootloader क्रम now.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश "pxa3xx-gcu.h"

#घोषणा DRV_NAME	"pxa3xx-gcu"

#घोषणा REG_GCCR	0x00
#घोषणा GCCR_SYNC_CLR	(1 << 9)
#घोषणा GCCR_BP_RST	(1 << 8)
#घोषणा GCCR_ABORT	(1 << 6)
#घोषणा GCCR_STOP	(1 << 4)

#घोषणा REG_GCISCR	0x04
#घोषणा REG_GCIECR	0x08
#घोषणा REG_GCRBBR	0x20
#घोषणा REG_GCRBLR	0x24
#घोषणा REG_GCRBHR	0x28
#घोषणा REG_GCRBTR	0x2C
#घोषणा REG_GCRBEXHR	0x30

#घोषणा IE_EOB		(1 << 0)
#घोषणा IE_EEOB		(1 << 5)
#घोषणा IE_ALL		0xff

#घोषणा SHARED_SIZE	PAGE_ALIGN(माप(काष्ठा pxa3xx_gcu_shared))

/* #घोषणा PXA3XX_GCU_DEBUG */
/* #घोषणा PXA3XX_GCU_DEBUG_TIMER */

#अगर_घोषित PXA3XX_GCU_DEBUG
#घोषणा QDUMP(msg)					\
	करो अणु						\
		QPRINT(priv, KERN_DEBUG, msg);		\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा QDUMP(msg)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा QERROR(msg)					\
	करो अणु						\
		QPRINT(priv, KERN_ERR, msg);		\
	पूर्ण जबतक (0)

काष्ठा pxa3xx_gcu_batch अणु
	काष्ठा pxa3xx_gcu_batch *next;
	u32			*ptr;
	dma_addr_t		 phys;
	अचिन्हित दीर्घ		 length;
पूर्ण;

काष्ठा pxa3xx_gcu_priv अणु
	काष्ठा device		 *dev;
	व्योम __iomem		 *mmio_base;
	काष्ठा clk		 *clk;
	काष्ठा pxa3xx_gcu_shared *shared;
	dma_addr_t		  shared_phys;
	काष्ठा resource		 *resource_mem;
	काष्ठा miscdevice	  misc_dev;
	रुको_queue_head_t	  रुको_idle;
	रुको_queue_head_t	  रुको_मुक्त;
	spinlock_t		  spinlock;
	काष्ठा बारpec64	  base_समय;

	काष्ठा pxa3xx_gcu_batch *मुक्त;
	काष्ठा pxa3xx_gcu_batch *पढ़ोy;
	काष्ठा pxa3xx_gcu_batch *पढ़ोy_last;
	काष्ठा pxa3xx_gcu_batch *running;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ
gc_पढ़ोl(काष्ठा pxa3xx_gcu_priv *priv, अचिन्हित पूर्णांक off)
अणु
	वापस __raw_पढ़ोl(priv->mmio_base + off);
पूर्ण

अटल अंतरभूत व्योम
gc_ग_लिखोl(काष्ठा pxa3xx_gcu_priv *priv, अचिन्हित पूर्णांक off, अचिन्हित दीर्घ val)
अणु
	__raw_ग_लिखोl(val, priv->mmio_base + off);
पूर्ण

#घोषणा QPRINT(priv, level, msg)					\
	करो अणु								\
		काष्ठा बारpec64 ts;					\
		काष्ठा pxa3xx_gcu_shared *shared = priv->shared;	\
		u32 base = gc_पढ़ोl(priv, REG_GCRBBR);			\
									\
		kसमय_get_ts64(&ts);					\
		ts = बारpec64_sub(ts, priv->base_समय);		\
									\
		prपूर्णांकk(level "%lld.%03ld.%03ld - %-17s: %-21s (%s, "	\
			"STATUS "					\
			"0x%02lx, B 0x%08lx [%ld], E %5ld, H %5ld, "	\
			"T %5ld)\n",					\
			(s64)(ts.tv_sec),				\
			ts.tv_nsec / NSEC_PER_MSEC,			\
			(ts.tv_nsec % NSEC_PER_MSEC) / USEC_PER_MSEC,	\
			__func__, msg,					\
			shared->hw_running ? "running" : "   idle",	\
			gc_पढ़ोl(priv, REG_GCISCR),			\
			gc_पढ़ोl(priv, REG_GCRBBR),			\
			gc_पढ़ोl(priv, REG_GCRBLR),			\
			(gc_पढ़ोl(priv, REG_GCRBEXHR) - base) / 4,	\
			(gc_पढ़ोl(priv, REG_GCRBHR) - base) / 4,	\
			(gc_पढ़ोl(priv, REG_GCRBTR) - base) / 4);	\
	पूर्ण जबतक (0)

अटल व्योम
pxa3xx_gcu_reset(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	QDUMP("RESET");

	/* disable पूर्णांकerrupts */
	gc_ग_लिखोl(priv, REG_GCIECR, 0);

	/* reset hardware */
	gc_ग_लिखोl(priv, REG_GCCR, GCCR_ABORT);
	gc_ग_लिखोl(priv, REG_GCCR, 0);

	स_रखो(priv->shared, 0, SHARED_SIZE);
	priv->shared->buffer_phys = priv->shared_phys;
	priv->shared->magic = PXA3XX_GCU_SHARED_MAGIC;

	kसमय_get_ts64(&priv->base_समय);

	/* set up the ring buffer poपूर्णांकers */
	gc_ग_लिखोl(priv, REG_GCRBLR, 0);
	gc_ग_लिखोl(priv, REG_GCRBBR, priv->shared_phys);
	gc_ग_लिखोl(priv, REG_GCRBTR, priv->shared_phys);

	/* enable all IRQs except EOB */
	gc_ग_लिखोl(priv, REG_GCIECR, IE_ALL & ~IE_EOB);
पूर्ण

अटल व्योम
dump_whole_state(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	काष्ठा pxa3xx_gcu_shared *sh = priv->shared;
	u32 base = gc_पढ़ोl(priv, REG_GCRBBR);

	QDUMP("DUMP");

	prपूर्णांकk(KERN_DEBUG "== PXA3XX-GCU DUMP ==\n"
		"%s, STATUS 0x%02lx, B 0x%08lx [%ld], E %5ld, H %5ld, T %5ld\n",
		sh->hw_running ? "running" : "idle   ",
		gc_पढ़ोl(priv, REG_GCISCR),
		gc_पढ़ोl(priv, REG_GCRBBR),
		gc_पढ़ोl(priv, REG_GCRBLR),
		(gc_पढ़ोl(priv, REG_GCRBEXHR) - base) / 4,
		(gc_पढ़ोl(priv, REG_GCRBHR) - base) / 4,
		(gc_पढ़ोl(priv, REG_GCRBTR) - base) / 4);
पूर्ण

अटल व्योम
flush_running(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	काष्ठा pxa3xx_gcu_batch *running = priv->running;
	काष्ठा pxa3xx_gcu_batch *next;

	जबतक (running) अणु
		next = running->next;
		running->next = priv->मुक्त;
		priv->मुक्त = running;
		running = next;
	पूर्ण

	priv->running = शून्य;
पूर्ण

अटल व्योम
run_पढ़ोy(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	अचिन्हित पूर्णांक num = 0;
	काष्ठा pxa3xx_gcu_shared *shared = priv->shared;
	काष्ठा pxa3xx_gcu_batch	*पढ़ोy = priv->पढ़ोy;

	QDUMP("Start");

	BUG_ON(!पढ़ोy);

	shared->buffer[num++] = 0x05000000;

	जबतक (पढ़ोy) अणु
		shared->buffer[num++] = 0x00000001;
		shared->buffer[num++] = पढ़ोy->phys;
		पढ़ोy = पढ़ोy->next;
	पूर्ण

	shared->buffer[num++] = 0x05000000;
	priv->running = priv->पढ़ोy;
	priv->पढ़ोy = priv->पढ़ोy_last = शून्य;
	gc_ग_लिखोl(priv, REG_GCRBLR, 0);
	shared->hw_running = 1;

	/* ring base address */
	gc_ग_लिखोl(priv, REG_GCRBBR, shared->buffer_phys);

	/* ring tail address */
	gc_ग_लिखोl(priv, REG_GCRBTR, shared->buffer_phys + num * 4);

	/* ring length */
	gc_ग_लिखोl(priv, REG_GCRBLR, ((num + 63) & ~63) * 4);
पूर्ण

अटल irqवापस_t
pxa3xx_gcu_handle_irq(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा pxa3xx_gcu_priv *priv = ctx;
	काष्ठा pxa3xx_gcu_shared *shared = priv->shared;
	u32 status = gc_पढ़ोl(priv, REG_GCISCR) & IE_ALL;

	QDUMP("-Interrupt");

	अगर (!status)
		वापस IRQ_NONE;

	spin_lock(&priv->spinlock);
	shared->num_पूर्णांकerrupts++;

	अगर (status & IE_EEOB) अणु
		QDUMP(" [EEOB]");

		flush_running(priv);
		wake_up_all(&priv->रुको_मुक्त);

		अगर (priv->पढ़ोy) अणु
			run_पढ़ोy(priv);
		पूर्ण अन्यथा अणु
			/* There is no more data prepared by the userspace.
			 * Set hw_running = 0 and रुको क्रम the next userspace
			 * kick-off */
			shared->num_idle++;
			shared->hw_running = 0;

			QDUMP(" '-> Idle.");

			/* set ring buffer length to zero */
			gc_ग_लिखोl(priv, REG_GCRBLR, 0);

			wake_up_all(&priv->रुको_idle);
		पूर्ण

		shared->num_करोne++;
	पूर्ण अन्यथा अणु
		QERROR(" [???]");
		dump_whole_state(priv);
	पूर्ण

	/* Clear the पूर्णांकerrupt */
	gc_ग_लिखोl(priv, REG_GCISCR, status);
	spin_unlock(&priv->spinlock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
pxa3xx_gcu_रुको_idle(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	पूर्णांक ret = 0;

	QDUMP("Waiting for idle...");

	/* Does not need to be atomic. There's a lock in user space,
	 * but anyhow, this is just क्रम statistics. */
	priv->shared->num_रुको_idle++;

	जबतक (priv->shared->hw_running) अणु
		पूर्णांक num = priv->shared->num_पूर्णांकerrupts;
		u32 rbexhr = gc_पढ़ोl(priv, REG_GCRBEXHR);

		ret = रुको_event_पूर्णांकerruptible_समयout(priv->रुको_idle,
					!priv->shared->hw_running, HZ*4);

		अगर (ret != 0)
			अवरोध;

		अगर (gc_पढ़ोl(priv, REG_GCRBEXHR) == rbexhr &&
		    priv->shared->num_पूर्णांकerrupts == num) अणु
			QERROR("TIMEOUT");
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण

	QDUMP("done");

	वापस ret;
पूर्ण

अटल पूर्णांक
pxa3xx_gcu_रुको_मुक्त(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	पूर्णांक ret = 0;

	QDUMP("Waiting for free...");

	/* Does not need to be atomic. There's a lock in user space,
	 * but anyhow, this is just क्रम statistics. */
	priv->shared->num_रुको_मुक्त++;

	जबतक (!priv->मुक्त) अणु
		u32 rbexhr = gc_पढ़ोl(priv, REG_GCRBEXHR);

		ret = रुको_event_पूर्णांकerruptible_समयout(priv->रुको_मुक्त,
						       priv->मुक्त, HZ*4);

		अगर (ret < 0)
			अवरोध;

		अगर (ret > 0)
			जारी;

		अगर (gc_पढ़ोl(priv, REG_GCRBEXHR) == rbexhr) अणु
			QERROR("TIMEOUT");
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण

	QDUMP("done");

	वापस ret;
पूर्ण

/* Misc device layer */

अटल अंतरभूत काष्ठा pxa3xx_gcu_priv *to_pxa3xx_gcu_priv(काष्ठा file *file)
अणु
	काष्ठा miscdevice *dev = file->निजी_data;
	वापस container_of(dev, काष्ठा pxa3xx_gcu_priv, misc_dev);
पूर्ण

/*
 * provide an empty .खोलो callback, so the core sets file->निजी_data
 * क्रम us.
 */
अटल पूर्णांक pxa3xx_gcu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
pxa3xx_gcu_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *buff,
		 माप_प्रकार count, loff_t *offp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा pxa3xx_gcu_batch	*buffer;
	काष्ठा pxa3xx_gcu_priv *priv = to_pxa3xx_gcu_priv(file);

	पूर्णांक words = count / 4;

	/* Does not need to be atomic. There's a lock in user space,
	 * but anyhow, this is just क्रम statistics. */
	priv->shared->num_ग_लिखोs++;
	priv->shared->num_words += words;

	/* Last word reserved क्रम batch buffer end command */
	अगर (words >= PXA3XX_GCU_BATCH_WORDS)
		वापस -E2BIG;

	/* Wait क्रम a मुक्त buffer */
	अगर (!priv->मुक्त) अणु
		ret = pxa3xx_gcu_रुको_मुक्त(priv);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * Get buffer from मुक्त list
	 */
	spin_lock_irqsave(&priv->spinlock, flags);
	buffer = priv->मुक्त;
	priv->मुक्त = buffer->next;
	spin_unlock_irqrestore(&priv->spinlock, flags);


	/* Copy data from user पूर्णांकo buffer */
	ret = copy_from_user(buffer->ptr, buff, words * 4);
	अगर (ret) अणु
		spin_lock_irqsave(&priv->spinlock, flags);
		buffer->next = priv->मुक्त;
		priv->मुक्त = buffer;
		spin_unlock_irqrestore(&priv->spinlock, flags);
		वापस -EFAULT;
	पूर्ण

	buffer->length = words;

	/* Append batch buffer end command */
	buffer->ptr[words] = 0x01000000;

	/*
	 * Add buffer to पढ़ोy list
	 */
	spin_lock_irqsave(&priv->spinlock, flags);

	buffer->next = शून्य;

	अगर (priv->पढ़ोy) अणु
		BUG_ON(priv->पढ़ोy_last == शून्य);

		priv->पढ़ोy_last->next = buffer;
	पूर्ण अन्यथा
		priv->पढ़ोy = buffer;

	priv->पढ़ोy_last = buffer;

	अगर (!priv->shared->hw_running)
		run_पढ़ोy(priv);

	spin_unlock_irqrestore(&priv->spinlock, flags);

	वापस words * 4;
पूर्ण


अटल दीर्घ
pxa3xx_gcu_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pxa3xx_gcu_priv *priv = to_pxa3xx_gcu_priv(file);

	चयन (cmd) अणु
	हाल PXA3XX_GCU_IOCTL_RESET:
		spin_lock_irqsave(&priv->spinlock, flags);
		pxa3xx_gcu_reset(priv);
		spin_unlock_irqrestore(&priv->spinlock, flags);
		वापस 0;

	हाल PXA3XX_GCU_IOCTL_WAIT_IDLE:
		वापस pxa3xx_gcu_रुको_idle(priv);
	पूर्ण

	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक
pxa3xx_gcu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक size = vma->vm_end - vma->vm_start;
	काष्ठा pxa3xx_gcu_priv *priv = to_pxa3xx_gcu_priv(file);

	चयन (vma->vm_pgoff) अणु
	हाल 0:
		/* hand out the shared data area */
		अगर (size != SHARED_SIZE)
			वापस -EINVAL;

		वापस dma_mmap_coherent(priv->dev, vma,
			priv->shared, priv->shared_phys, size);

	हाल SHARED_SIZE >> PAGE_SHIFT:
		/* hand out the MMIO base क्रम direct रेजिस्टर access
		 * from userspace */
		अगर (size != resource_size(priv->resource_mem))
			वापस -EINVAL;

		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

		वापस io_remap_pfn_range(vma, vma->vm_start,
				priv->resource_mem->start >> PAGE_SHIFT,
				size, vma->vm_page_prot);
	पूर्ण

	वापस -EINVAL;
पूर्ण


#अगर_घोषित PXA3XX_GCU_DEBUG_TIMER
अटल काष्ठा समयr_list pxa3xx_gcu_debug_समयr;
अटल काष्ठा pxa3xx_gcu_priv *debug_समयr_priv;

अटल व्योम pxa3xx_gcu_debug_समयकरोut(काष्ठा समयr_list *unused)
अणु
	काष्ठा pxa3xx_gcu_priv *priv = debug_समयr_priv;

	QERROR("Timer DUMP");

	mod_समयr(&pxa3xx_gcu_debug_समयr, jअगरfies + 5 * HZ);
पूर्ण

अटल व्योम pxa3xx_gcu_init_debug_समयr(काष्ठा pxa3xx_gcu_priv *priv)
अणु
	/* init the समयr काष्ठाure */
	debug_समयr_priv = priv;
	समयr_setup(&pxa3xx_gcu_debug_समयr, pxa3xx_gcu_debug_समयकरोut, 0);
	pxa3xx_gcu_debug_समयकरोut(शून्य);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa3xx_gcu_init_debug_समयr(काष्ठा pxa3xx_gcu_priv *priv) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक
pxa3xx_gcu_add_buffer(काष्ठा device *dev,
		      काष्ठा pxa3xx_gcu_priv *priv)
अणु
	काष्ठा pxa3xx_gcu_batch *buffer;

	buffer = kzalloc(माप(काष्ठा pxa3xx_gcu_batch), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->ptr = dma_alloc_coherent(dev, PXA3XX_GCU_BATCH_WORDS * 4,
					 &buffer->phys, GFP_KERNEL);
	अगर (!buffer->ptr) अणु
		kमुक्त(buffer);
		वापस -ENOMEM;
	पूर्ण

	buffer->next = priv->मुक्त;
	priv->मुक्त = buffer;

	वापस 0;
पूर्ण

अटल व्योम
pxa3xx_gcu_मुक्त_buffers(काष्ठा device *dev,
			काष्ठा pxa3xx_gcu_priv *priv)
अणु
	काष्ठा pxa3xx_gcu_batch *next, *buffer = priv->मुक्त;

	जबतक (buffer) अणु
		next = buffer->next;

		dma_मुक्त_coherent(dev, PXA3XX_GCU_BATCH_WORDS * 4,
				  buffer->ptr, buffer->phys);

		kमुक्त(buffer);
		buffer = next;
	पूर्ण

	priv->मुक्त = शून्य;
पूर्ण

अटल स्थिर काष्ठा file_operations pxa3xx_gcu_miscdev_fops = अणु
	.owner =		THIS_MODULE,
	.खोलो =			pxa3xx_gcu_खोलो,
	.ग_लिखो =		pxa3xx_gcu_ग_लिखो,
	.unlocked_ioctl =	pxa3xx_gcu_ioctl,
	.mmap =			pxa3xx_gcu_mmap,
पूर्ण;

अटल पूर्णांक pxa3xx_gcu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret, irq;
	काष्ठा resource *r;
	काष्ठा pxa3xx_gcu_priv *priv;
	काष्ठा device *dev = &pdev->dev;

	priv = devm_kzalloc(dev, माप(काष्ठा pxa3xx_gcu_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	init_रुकोqueue_head(&priv->रुको_idle);
	init_रुकोqueue_head(&priv->रुको_मुक्त);
	spin_lock_init(&priv->spinlock);

	/* we allocate the misc device काष्ठाure as part of our own allocation,
	 * so we can get a poपूर्णांकer to our priv काष्ठाure later on with
	 * container_of(). This isn't really necessary as we have a fixed minor
	 * number anyway, but this is to aव्योम अटलs. */

	priv->misc_dev.minor	= PXA3XX_GCU_MINOR,
	priv->misc_dev.name	= DRV_NAME,
	priv->misc_dev.fops	= &pxa3xx_gcu_miscdev_fops;

	/* handle IO resources */
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->mmio_base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(priv->mmio_base))
		वापस PTR_ERR(priv->mmio_base);

	/* enable the घड़ी */
	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	/* request the IRQ */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "no IRQ defined: %d\n", irq);
		वापस irq;
	पूर्ण

	ret = devm_request_irq(dev, irq, pxa3xx_gcu_handle_irq,
			       0, DRV_NAME, priv);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed\n");
		वापस ret;
	पूर्ण

	/* allocate dma memory */
	priv->shared = dma_alloc_coherent(dev, SHARED_SIZE,
					  &priv->shared_phys, GFP_KERNEL);
	अगर (!priv->shared) अणु
		dev_err(dev, "failed to allocate DMA memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* रेजिस्टर misc device */
	ret = misc_रेजिस्टर(&priv->misc_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "misc_register() for minor %d failed\n",
			PXA3XX_GCU_MINOR);
		जाओ err_मुक्त_dma;
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable clock\n");
		जाओ err_misc_deरेजिस्टर;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		ret = pxa3xx_gcu_add_buffer(dev, priv);
		अगर (ret) अणु
			dev_err(dev, "failed to allocate DMA memory\n");
			जाओ err_disable_clk;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	priv->resource_mem = r;
	priv->dev = dev;
	pxa3xx_gcu_reset(priv);
	pxa3xx_gcu_init_debug_समयr(priv);

	dev_info(dev, "registered @0x%p, DMA 0x%p (%d bytes), IRQ %d\n",
			(व्योम *) r->start, (व्योम *) priv->shared_phys,
			SHARED_SIZE, irq);
	वापस 0;

err_मुक्त_dma:
	dma_मुक्त_coherent(dev, SHARED_SIZE,
			priv->shared, priv->shared_phys);

err_misc_deरेजिस्टर:
	misc_deरेजिस्टर(&priv->misc_dev);

err_disable_clk:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa3xx_gcu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa3xx_gcu_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	pxa3xx_gcu_रुको_idle(priv);
	misc_deरेजिस्टर(&priv->misc_dev);
	dma_मुक्त_coherent(dev, SHARED_SIZE, priv->shared, priv->shared_phys);
	pxa3xx_gcu_मुक्त_buffers(dev, priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa3xx_gcu_of_match[] = अणु
	अणु .compatible = "marvell,pxa300-gcu", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa3xx_gcu_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pxa3xx_gcu_driver = अणु
	.probe	  = pxa3xx_gcu_probe,
	.हटाओ	 = pxa3xx_gcu_हटाओ,
	.driver	 = अणु
		.name   = DRV_NAME,
		.of_match_table = of_match_ptr(pxa3xx_gcu_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxa3xx_gcu_driver);

MODULE_DESCRIPTION("PXA3xx graphics controller unit driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(PXA3XX_GCU_MINOR);
MODULE_AUTHOR("Janine Kropp <nin@directfb.org>, "
		"Denis Oliver Kropp <dok@directfb.org>, "
		"Daniel Mack <daniel@caiaq.de>");
