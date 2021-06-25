<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/dma.c
 *
 *  Copyright (C) 1995-2000 Russell King
 *
 *  Front-end to the DMA handling.  This handles the allocation/मुक्तing
 *  of DMA channels, and provides a unअगरied पूर्णांकerface to the machines
 *  DMA facilities.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>

#समावेश <यंत्र/dma.h>

#समावेश <यंत्र/mach/dma.h>

DEFINE_RAW_SPINLOCK(dma_spin_lock);
EXPORT_SYMBOL(dma_spin_lock);

अटल dma_t *dma_chan[MAX_DMA_CHANNELS];

अटल अंतरभूत dma_t *dma_channel(अचिन्हित पूर्णांक chan)
अणु
	अगर (chan >= MAX_DMA_CHANNELS)
		वापस शून्य;

	वापस dma_chan[chan];
पूर्ण

पूर्णांक __init isa_dma_add(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	अगर (!dma->d_ops)
		वापस -EINVAL;

	sg_init_table(&dma->buf, 1);

	अगर (dma_chan[chan])
		वापस -EBUSY;
	dma_chan[chan] = dma;
	वापस 0;
पूर्ण

/*
 * Request DMA channel
 *
 * On certain platक्रमms, we have to allocate an पूर्णांकerrupt as well...
 */
पूर्णांक request_dma(अचिन्हित पूर्णांक chan, स्थिर अक्षर *device_id)
अणु
	dma_t *dma = dma_channel(chan);
	पूर्णांक ret;

	अगर (!dma)
		जाओ bad_dma;

	अगर (xchg(&dma->lock, 1) != 0)
		जाओ busy;

	dma->device_id = device_id;
	dma->active    = 0;
	dma->invalid   = 1;

	ret = 0;
	अगर (dma->d_ops->request)
		ret = dma->d_ops->request(chan, dma);

	अगर (ret)
		xchg(&dma->lock, 0);

	वापस ret;

bad_dma:
	pr_err("dma: trying to allocate DMA%d\n", chan);
	वापस -EINVAL;

busy:
	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL(request_dma);

/*
 * Free DMA channel
 *
 * On certain platक्रमms, we have to मुक्त पूर्णांकerrupt as well...
 */
व्योम मुक्त_dma(अचिन्हित पूर्णांक chan)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (!dma)
		जाओ bad_dma;

	अगर (dma->active) अणु
		pr_err("dma%d: freeing active DMA\n", chan);
		dma->d_ops->disable(chan, dma);
		dma->active = 0;
	पूर्ण

	अगर (xchg(&dma->lock, 0) != 0) अणु
		अगर (dma->d_ops->मुक्त)
			dma->d_ops->मुक्त(chan, dma);
		वापस;
	पूर्ण

	pr_err("dma%d: trying to free free DMA\n", chan);
	वापस;

bad_dma:
	pr_err("dma: trying to free DMA%d\n", chan);
पूर्ण
EXPORT_SYMBOL(मुक्त_dma);

/* Set DMA Scatter-Gather list
 */
व्योम set_dma_sg (अचिन्हित पूर्णांक chan, काष्ठा scatterlist *sg, पूर्णांक nr_sg)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (dma->active)
		pr_err("dma%d: altering DMA SG while DMA active\n", chan);

	dma->sg = sg;
	dma->sgcount = nr_sg;
	dma->invalid = 1;
पूर्ण
EXPORT_SYMBOL(set_dma_sg);

/* Set DMA address
 *
 * Copy address to the काष्ठाure, and set the invalid bit
 */
व्योम __set_dma_addr (अचिन्हित पूर्णांक chan, व्योम *addr)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (dma->active)
		pr_err("dma%d: altering DMA address while DMA active\n", chan);

	dma->sg = शून्य;
	dma->addr = addr;
	dma->invalid = 1;
पूर्ण
EXPORT_SYMBOL(__set_dma_addr);

/* Set DMA byte count
 *
 * Copy address to the काष्ठाure, and set the invalid bit
 */
व्योम set_dma_count (अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ count)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (dma->active)
		pr_err("dma%d: altering DMA count while DMA active\n", chan);

	dma->sg = शून्य;
	dma->count = count;
	dma->invalid = 1;
पूर्ण
EXPORT_SYMBOL(set_dma_count);

/* Set DMA direction mode
 */
व्योम set_dma_mode (अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक mode)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (dma->active)
		pr_err("dma%d: altering DMA mode while DMA active\n", chan);

	dma->dma_mode = mode;
	dma->invalid = 1;
पूर्ण
EXPORT_SYMBOL(set_dma_mode);

/* Enable DMA channel
 */
व्योम enable_dma (अचिन्हित पूर्णांक chan)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (!dma->lock)
		जाओ मुक्त_dma;

	अगर (dma->active == 0) अणु
		dma->active = 1;
		dma->d_ops->enable(chan, dma);
	पूर्ण
	वापस;

मुक्त_dma:
	pr_err("dma%d: trying to enable free DMA\n", chan);
	BUG();
पूर्ण
EXPORT_SYMBOL(enable_dma);

/* Disable DMA channel
 */
व्योम disable_dma (अचिन्हित पूर्णांक chan)
अणु
	dma_t *dma = dma_channel(chan);

	अगर (!dma->lock)
		जाओ मुक्त_dma;

	अगर (dma->active == 1) अणु
		dma->active = 0;
		dma->d_ops->disable(chan, dma);
	पूर्ण
	वापस;

मुक्त_dma:
	pr_err("dma%d: trying to disable free DMA\n", chan);
	BUG();
पूर्ण
EXPORT_SYMBOL(disable_dma);

/*
 * Is the specअगरied DMA channel active?
 */
पूर्णांक dma_channel_active(अचिन्हित पूर्णांक chan)
अणु
	dma_t *dma = dma_channel(chan);
	वापस dma->active;
पूर्ण
EXPORT_SYMBOL(dma_channel_active);

व्योम set_dma_page(अचिन्हित पूर्णांक chan, अक्षर pagenr)
अणु
	pr_err("dma%d: trying to set_dma_page\n", chan);
पूर्ण
EXPORT_SYMBOL(set_dma_page);

व्योम set_dma_speed(अचिन्हित पूर्णांक chan, पूर्णांक cycle_ns)
अणु
	dma_t *dma = dma_channel(chan);
	पूर्णांक ret = 0;

	अगर (dma->d_ops->setspeed)
		ret = dma->d_ops->setspeed(chan, dma, cycle_ns);
	dma->speed = ret;
पूर्ण
EXPORT_SYMBOL(set_dma_speed);

पूर्णांक get_dma_residue(अचिन्हित पूर्णांक chan)
अणु
	dma_t *dma = dma_channel(chan);
	पूर्णांक ret = 0;

	अगर (dma->d_ops->residue)
		ret = dma->d_ops->residue(chan, dma);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(get_dma_residue);

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_dma_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < MAX_DMA_CHANNELS ; i++) अणु
		dma_t *dma = dma_channel(i);
		अगर (dma && dma->lock)
			seq_म_लिखो(m, "%2d: %s\n", i, dma->device_id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_dma_init(व्योम)
अणु
	proc_create_single("dma", 0, शून्य, proc_dma_show);
	वापस 0;
पूर्ण

__initcall(proc_dma_init);
#पूर्ण_अगर
