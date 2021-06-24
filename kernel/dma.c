<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/kernel/dma.c: A DMA channel allocator. Inspired by linux/kernel/irq.c.
 *
 * Written by Hennus Bergman, 1992.
 *
 * 1994/12/26: Changes by Alex Nash to fix a minor bug in /proc/dma.
 *   In the previous version the reported device could end up being wrong,
 *   अगर a device requested a DMA channel that was alपढ़ोy in use.
 *   [It also happened to हटाओ the माप(अक्षर *) == माप(पूर्णांक)
 *   assumption पूर्णांकroduced because of those /proc/dma patches. -- Hennus]
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/dma.h>



/* A note on resource allocation:
 *
 * All drivers needing DMA channels, should allocate and release them
 * through the खुला routines `request_dma()' and `free_dma()'.
 *
 * In order to aव्योम problems, all processes should allocate resources in
 * the same sequence and release them in the reverse order.
 *
 * So, when allocating DMAs and IRQs, first allocate the IRQ, then the DMA.
 * When releasing them, first release the DMA, then release the IRQ.
 * If you करोn't, you may cause allocation requests to fail unnecessarily.
 * This करोesn't really matter now, but it will once we get real semaphores
 * in the kernel.
 */


DEFINE_SPINLOCK(dma_spin_lock);

/*
 *	If our port करोesn't define this it has no PC like DMA
 */

#अगर_घोषित MAX_DMA_CHANNELS


/* Channel n is busy अगरf dma_chan_busy[n].lock != 0.
 * DMA0 used to be reserved क्रम DRAM refresh, but apparently not any more...
 * DMA4 is reserved क्रम cascading.
 */

काष्ठा dma_chan अणु
	पूर्णांक  lock;
	स्थिर अक्षर *device_id;
पूर्ण;

अटल काष्ठा dma_chan dma_chan_busy[MAX_DMA_CHANNELS] = अणु
	[4] = अणु 1, "cascade" पूर्ण,
पूर्ण;


/**
 * request_dma - request and reserve a प्रणाली DMA channel
 * @dmanr: DMA channel number
 * @device_id: reserving device ID string, used in /proc/dma
 */
पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id)
अणु
	अगर (dmanr >= MAX_DMA_CHANNELS)
		वापस -EINVAL;

	अगर (xchg(&dma_chan_busy[dmanr].lock, 1) != 0)
		वापस -EBUSY;

	dma_chan_busy[dmanr].device_id = device_id;

	/* old flag was 0, now contains 1 to indicate busy */
	वापस 0;
पूर्ण /* request_dma */

/**
 * मुक्त_dma - मुक्त a reserved प्रणाली DMA channel
 * @dmanr: DMA channel number
 */
व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr >= MAX_DMA_CHANNELS) अणु
		prपूर्णांकk(KERN_WARNING "Trying to free DMA%d\n", dmanr);
		वापस;
	पूर्ण

	अगर (xchg(&dma_chan_busy[dmanr].lock, 0) == 0) अणु
		prपूर्णांकk(KERN_WARNING "Trying to free free DMA%d\n", dmanr);
		वापस;
	पूर्ण

पूर्ण /* मुक्त_dma */

#अन्यथा

पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर *device_id)
अणु
	वापस -EINVAL;
पूर्ण

व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS

#अगर_घोषित MAX_DMA_CHANNELS
अटल पूर्णांक proc_dma_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < MAX_DMA_CHANNELS ; i++) अणु
		अगर (dma_chan_busy[i].lock) अणु
			seq_म_लिखो(m, "%2d: %s\n", i,
				   dma_chan_busy[i].device_id);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक proc_dma_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "No DMA\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* MAX_DMA_CHANNELS */

अटल पूर्णांक __init proc_dma_init(व्योम)
अणु
	proc_create_single("dma", 0, शून्य, proc_dma_show);
	वापस 0;
पूर्ण

__initcall(proc_dma_init);
#पूर्ण_अगर

EXPORT_SYMBOL(request_dma);
EXPORT_SYMBOL(मुक्त_dma);
EXPORT_SYMBOL(dma_spin_lock);
