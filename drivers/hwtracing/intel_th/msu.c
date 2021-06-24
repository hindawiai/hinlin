<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub Memory Storage Unit
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sizes.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/dma-mapping.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर

#समावेश <linux/पूर्णांकel_th.h>
#समावेश "intel_th.h"
#समावेश "msu.h"

#घोषणा msc_dev(x) (&(x)->thdev->dev)

/*
 * Lockout state transitions:
 *   READY -> INUSE -+-> LOCKED -+-> READY -> etc.
 *                   \-----------/
 * WIN_READY:	winकरोw can be used by HW
 * WIN_INUSE:	winकरोw is in use
 * WIN_LOCKED:	winकरोw is filled up and is being processed by the buffer
 * handling code
 *
 * All state transitions happen स्वतःmatically, except क्रम the LOCKED->READY,
 * which needs to be संकेतled by the buffer code by calling
 * पूर्णांकel_th_msc_winकरोw_unlock().
 *
 * When the पूर्णांकerrupt handler has to चयन to the next winकरोw, it checks
 * whether it's READY, and अगर it is, it perक्रमms the चयन and tracing
 * जारीs. If it's LOCKED, it stops the trace.
 */
क्रमागत lockout_state अणु
	WIN_READY = 0,
	WIN_INUSE,
	WIN_LOCKED
पूर्ण;

/**
 * काष्ठा msc_winकरोw - multiblock mode winकरोw descriptor
 * @entry:	winकरोw list linkage (msc::win_list)
 * @pgoff:	page offset पूर्णांकo the buffer that this winकरोw starts at
 * @lockout:	lockout state, see comment below
 * @lo_lock:	lockout state serialization
 * @nr_blocks:	number of blocks (pages) in this winकरोw
 * @nr_segs:	number of segments in this winकरोw (<= @nr_blocks)
 * @_sgt:	array of block descriptors
 * @sgt:	array of block descriptors
 */
काष्ठा msc_winकरोw अणु
	काष्ठा list_head	entry;
	अचिन्हित दीर्घ		pgoff;
	क्रमागत lockout_state	lockout;
	spinlock_t		lo_lock;
	अचिन्हित पूर्णांक		nr_blocks;
	अचिन्हित पूर्णांक		nr_segs;
	काष्ठा msc		*msc;
	काष्ठा sg_table		_sgt;
	काष्ठा sg_table		*sgt;
पूर्ण;

/**
 * काष्ठा msc_iter - iterator क्रम msc buffer
 * @entry:		msc::iter_list linkage
 * @msc:		poपूर्णांकer to the MSC device
 * @start_win:		oldest winकरोw
 * @win:		current winकरोw
 * @offset:		current logical offset पूर्णांकo the buffer
 * @start_block:	oldest block in the winकरोw
 * @block:		block number in the winकरोw
 * @block_off:		offset पूर्णांकo current block
 * @wrap_count:		block wrapping handling
 * @eof:		end of buffer reached
 */
काष्ठा msc_iter अणु
	काष्ठा list_head	entry;
	काष्ठा msc		*msc;
	काष्ठा msc_winकरोw	*start_win;
	काष्ठा msc_winकरोw	*win;
	अचिन्हित दीर्घ		offset;
	काष्ठा scatterlist	*start_block;
	काष्ठा scatterlist	*block;
	अचिन्हित पूर्णांक		block_off;
	अचिन्हित पूर्णांक		wrap_count;
	अचिन्हित पूर्णांक		eof;
पूर्ण;

/**
 * काष्ठा msc - MSC device representation
 * @reg_base:		रेजिस्टर winकरोw base address
 * @thdev:		पूर्णांकel_th_device poपूर्णांकer
 * @mbuf:		MSU buffer, अगर asचिन्हित
 * @mbuf_priv		MSU buffer's निजी data, अगर @mbuf
 * @win_list:		list of winकरोws in multiblock mode
 * @single_sgt:		single mode buffer
 * @cur_win:		current winकरोw
 * @nr_pages:		total number of pages allocated क्रम this buffer
 * @single_sz:		amount of data in single mode
 * @single_wrap:	single mode wrap occurred
 * @base:		buffer's base poपूर्णांकer
 * @base_addr:		buffer's base address
 * @user_count:		number of users of the buffer
 * @mmap_count:		number of mappings
 * @buf_mutex:		mutex to serialize access to buffer-related bits

 * @enabled:		MSC is enabled
 * @wrap:		wrapping is enabled
 * @mode:		MSC operating mode
 * @burst_len:		ग_लिखो burst length
 * @index:		number of this MSC in the MSU
 */
काष्ठा msc अणु
	व्योम __iomem		*reg_base;
	व्योम __iomem		*msu_base;
	काष्ठा पूर्णांकel_th_device	*thdev;

	स्थिर काष्ठा msu_buffer	*mbuf;
	व्योम			*mbuf_priv;

	काष्ठा work_काष्ठा	work;
	काष्ठा list_head	win_list;
	काष्ठा sg_table		single_sgt;
	काष्ठा msc_winकरोw	*cur_win;
	काष्ठा msc_winकरोw	*चयन_on_unlock;
	अचिन्हित दीर्घ		nr_pages;
	अचिन्हित दीर्घ		single_sz;
	अचिन्हित पूर्णांक		single_wrap : 1;
	व्योम			*base;
	dma_addr_t		base_addr;
	u32			orig_addr;
	u32			orig_sz;

	/* <0: no buffer, 0: no users, >0: active users */
	atomic_t		user_count;

	atomic_t		mmap_count;
	काष्ठा mutex		buf_mutex;

	काष्ठा list_head	iter_list;

	bool			stop_on_full;

	/* config */
	अचिन्हित पूर्णांक		enabled : 1,
				wrap	: 1,
				करो_irq	: 1,
				multi_is_broken : 1;
	अचिन्हित पूर्णांक		mode;
	अचिन्हित पूर्णांक		burst_len;
	अचिन्हित पूर्णांक		index;
पूर्ण;

अटल LIST_HEAD(msu_buffer_list);
अटल DEFINE_MUTEX(msu_buffer_mutex);

/**
 * काष्ठा msu_buffer_entry - पूर्णांकernal MSU buffer bookkeeping
 * @entry:	link to msu_buffer_list
 * @mbuf:	MSU buffer object
 * @owner:	module that provides this MSU buffer
 */
काष्ठा msu_buffer_entry अणु
	काष्ठा list_head	entry;
	स्थिर काष्ठा msu_buffer	*mbuf;
	काष्ठा module		*owner;
पूर्ण;

अटल काष्ठा msu_buffer_entry *__msu_buffer_entry_find(स्थिर अक्षर *name)
अणु
	काष्ठा msu_buffer_entry *mbe;

	lockdep_निश्चित_held(&msu_buffer_mutex);

	list_क्रम_each_entry(mbe, &msu_buffer_list, entry) अणु
		अगर (!म_भेद(mbe->mbuf->name, name))
			वापस mbe;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा msu_buffer *
msu_buffer_get(स्थिर अक्षर *name)
अणु
	काष्ठा msu_buffer_entry *mbe;

	mutex_lock(&msu_buffer_mutex);
	mbe = __msu_buffer_entry_find(name);
	अगर (mbe && !try_module_get(mbe->owner))
		mbe = शून्य;
	mutex_unlock(&msu_buffer_mutex);

	वापस mbe ? mbe->mbuf : शून्य;
पूर्ण

अटल व्योम msu_buffer_put(स्थिर काष्ठा msu_buffer *mbuf)
अणु
	काष्ठा msu_buffer_entry *mbe;

	mutex_lock(&msu_buffer_mutex);
	mbe = __msu_buffer_entry_find(mbuf->name);
	अगर (mbe)
		module_put(mbe->owner);
	mutex_unlock(&msu_buffer_mutex);
पूर्ण

पूर्णांक पूर्णांकel_th_msu_buffer_रेजिस्टर(स्थिर काष्ठा msu_buffer *mbuf,
				 काष्ठा module *owner)
अणु
	काष्ठा msu_buffer_entry *mbe;
	पूर्णांक ret = 0;

	mbe = kzalloc(माप(*mbe), GFP_KERNEL);
	अगर (!mbe)
		वापस -ENOMEM;

	mutex_lock(&msu_buffer_mutex);
	अगर (__msu_buffer_entry_find(mbuf->name)) अणु
		ret = -EEXIST;
		kमुक्त(mbe);
		जाओ unlock;
	पूर्ण

	mbe->mbuf = mbuf;
	mbe->owner = owner;
	list_add_tail(&mbe->entry, &msu_buffer_list);
unlock:
	mutex_unlock(&msu_buffer_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_msu_buffer_रेजिस्टर);

व्योम पूर्णांकel_th_msu_buffer_unरेजिस्टर(स्थिर काष्ठा msu_buffer *mbuf)
अणु
	काष्ठा msu_buffer_entry *mbe;

	mutex_lock(&msu_buffer_mutex);
	mbe = __msu_buffer_entry_find(mbuf->name);
	अगर (mbe) अणु
		list_del(&mbe->entry);
		kमुक्त(mbe);
	पूर्ण
	mutex_unlock(&msu_buffer_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_msu_buffer_unरेजिस्टर);

अटल अंतरभूत bool msc_block_is_empty(काष्ठा msc_block_desc *bdesc)
अणु
	/* header hasn't been written */
	अगर (!bdesc->valid_dw)
		वापस true;

	/* valid_dw includes the header */
	अगर (!msc_data_sz(bdesc))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *msc_win_base_sg(काष्ठा msc_winकरोw *win)
अणु
	वापस win->sgt->sgl;
पूर्ण

अटल अंतरभूत काष्ठा msc_block_desc *msc_win_base(काष्ठा msc_winकरोw *win)
अणु
	वापस sg_virt(msc_win_base_sg(win));
पूर्ण

अटल अंतरभूत dma_addr_t msc_win_base_dma(काष्ठा msc_winकरोw *win)
अणु
	वापस sg_dma_address(msc_win_base_sg(win));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
msc_win_base_pfn(काष्ठा msc_winकरोw *win)
अणु
	वापस PFN_DOWN(msc_win_base_dma(win));
पूर्ण

/**
 * msc_is_last_win() - check अगर a winकरोw is the last one क्रम a given MSC
 * @win:	winकरोw
 * Return:	true अगर @win is the last winकरोw in MSC's multiblock buffer
 */
अटल अंतरभूत bool msc_is_last_win(काष्ठा msc_winकरोw *win)
अणु
	वापस win->entry.next == &win->msc->win_list;
पूर्ण

/**
 * msc_next_winकरोw() - वापस next winकरोw in the multiblock buffer
 * @win:	current winकरोw
 *
 * Return:	winकरोw following the current one
 */
अटल काष्ठा msc_winकरोw *msc_next_winकरोw(काष्ठा msc_winकरोw *win)
अणु
	अगर (msc_is_last_win(win))
		वापस list_first_entry(&win->msc->win_list, काष्ठा msc_winकरोw,
					entry);

	वापस list_next_entry(win, entry);
पूर्ण

अटल माप_प्रकार msc_win_total_sz(काष्ठा msc_winकरोw *win)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक blk;
	माप_प्रकार size = 0;

	क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, blk) अणु
		काष्ठा msc_block_desc *bdesc = sg_virt(sg);

		अगर (msc_block_wrapped(bdesc))
			वापस (माप_प्रकार)win->nr_blocks << PAGE_SHIFT;

		size += msc_total_sz(bdesc);
		अगर (msc_block_last_written(bdesc))
			अवरोध;
	पूर्ण

	वापस size;
पूर्ण

/**
 * msc_find_winकरोw() - find a winकरोw matching a given sg_table
 * @msc:	MSC device
 * @sgt:	SG table of the winकरोw
 * @nonempty:	skip over empty winकरोws
 *
 * Return:	MSC winकरोw काष्ठाure poपूर्णांकer or शून्य अगर the winकरोw
 *		could not be found.
 */
अटल काष्ठा msc_winकरोw *
msc_find_winकरोw(काष्ठा msc *msc, काष्ठा sg_table *sgt, bool nonempty)
अणु
	काष्ठा msc_winकरोw *win;
	अचिन्हित पूर्णांक found = 0;

	अगर (list_empty(&msc->win_list))
		वापस शून्य;

	/*
	 * we might need a radix tree क्रम this, depending on how
	 * many winकरोws a typical user would allocate; ideally it's
	 * something like 2, in which हाल we're good
	 */
	list_क्रम_each_entry(win, &msc->win_list, entry) अणु
		अगर (win->sgt == sgt)
			found++;

		/* skip the empty ones */
		अगर (nonempty && msc_block_is_empty(msc_win_base(win)))
			जारी;

		अगर (found)
			वापस win;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * msc_oldest_winकरोw() - locate the winकरोw with oldest data
 * @msc:	MSC device
 *
 * This should only be used in multiblock mode. Caller should hold the
 * msc::user_count reference.
 *
 * Return:	the oldest winकरोw with valid data
 */
अटल काष्ठा msc_winकरोw *msc_oldest_winकरोw(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *win;

	अगर (list_empty(&msc->win_list))
		वापस शून्य;

	win = msc_find_winकरोw(msc, msc_next_winकरोw(msc->cur_win)->sgt, true);
	अगर (win)
		वापस win;

	वापस list_first_entry(&msc->win_list, काष्ठा msc_winकरोw, entry);
पूर्ण

/**
 * msc_win_oldest_sg() - locate the oldest block in a given winकरोw
 * @win:	winकरोw to look at
 *
 * Return:	index of the block with the oldest data
 */
अटल काष्ठा scatterlist *msc_win_oldest_sg(काष्ठा msc_winकरोw *win)
अणु
	अचिन्हित पूर्णांक blk;
	काष्ठा scatterlist *sg;
	काष्ठा msc_block_desc *bdesc = msc_win_base(win);

	/* without wrapping, first block is the oldest */
	अगर (!msc_block_wrapped(bdesc))
		वापस msc_win_base_sg(win);

	/*
	 * with wrapping, last written block contains both the newest and the
	 * oldest data क्रम this winकरोw.
	 */
	क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, blk) अणु
		काष्ठा msc_block_desc *bdesc = sg_virt(sg);

		अगर (msc_block_last_written(bdesc))
			वापस sg;
	पूर्ण

	वापस msc_win_base_sg(win);
पूर्ण

अटल काष्ठा msc_block_desc *msc_iter_bdesc(काष्ठा msc_iter *iter)
अणु
	वापस sg_virt(iter->block);
पूर्ण

अटल काष्ठा msc_iter *msc_iter_install(काष्ठा msc *msc)
अणु
	काष्ठा msc_iter *iter;

	iter = kzalloc(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&msc->buf_mutex);

	/*
	 * Reading and tracing are mutually exclusive; अगर msc is
	 * enabled, खोलो() will fail; otherwise existing पढ़ोers
	 * will prevent enabling the msc and the rest of fops करोn't
	 * need to worry about it.
	 */
	अगर (msc->enabled) अणु
		kमुक्त(iter);
		iter = ERR_PTR(-EBUSY);
		जाओ unlock;
	पूर्ण

	iter->msc = msc;

	list_add_tail(&iter->entry, &msc->iter_list);
unlock:
	mutex_unlock(&msc->buf_mutex);

	वापस iter;
पूर्ण

अटल व्योम msc_iter_हटाओ(काष्ठा msc_iter *iter, काष्ठा msc *msc)
अणु
	mutex_lock(&msc->buf_mutex);
	list_del(&iter->entry);
	mutex_unlock(&msc->buf_mutex);

	kमुक्त(iter);
पूर्ण

अटल व्योम msc_iter_block_start(काष्ठा msc_iter *iter)
अणु
	अगर (iter->start_block)
		वापस;

	iter->start_block = msc_win_oldest_sg(iter->win);
	iter->block = iter->start_block;
	iter->wrap_count = 0;

	/*
	 * start with the block with oldest data; अगर data has wrapped
	 * in this winकरोw, it should be in this block
	 */
	अगर (msc_block_wrapped(msc_iter_bdesc(iter)))
		iter->wrap_count = 2;

पूर्ण

अटल पूर्णांक msc_iter_win_start(काष्ठा msc_iter *iter, काष्ठा msc *msc)
अणु
	/* alपढ़ोy started, nothing to करो */
	अगर (iter->start_win)
		वापस 0;

	iter->start_win = msc_oldest_winकरोw(msc);
	अगर (!iter->start_win)
		वापस -EINVAL;

	iter->win = iter->start_win;
	iter->start_block = शून्य;

	msc_iter_block_start(iter);

	वापस 0;
पूर्ण

अटल पूर्णांक msc_iter_win_advance(काष्ठा msc_iter *iter)
अणु
	iter->win = msc_next_winकरोw(iter->win);
	iter->start_block = शून्य;

	अगर (iter->win == iter->start_win) अणु
		iter->eof++;
		वापस 1;
	पूर्ण

	msc_iter_block_start(iter);

	वापस 0;
पूर्ण

अटल पूर्णांक msc_iter_block_advance(काष्ठा msc_iter *iter)
अणु
	iter->block_off = 0;

	/* wrapping */
	अगर (iter->wrap_count && iter->block == iter->start_block) अणु
		iter->wrap_count--;
		अगर (!iter->wrap_count)
			/* copied newest data from the wrapped block */
			वापस msc_iter_win_advance(iter);
	पूर्ण

	/* no wrapping, check क्रम last written block */
	अगर (!iter->wrap_count && msc_block_last_written(msc_iter_bdesc(iter)))
		/* copied newest data क्रम the winकरोw */
		वापस msc_iter_win_advance(iter);

	/* block advance */
	अगर (sg_is_last(iter->block))
		iter->block = msc_win_base_sg(iter->win);
	अन्यथा
		iter->block = sg_next(iter->block);

	/* no wrapping, sanity check in हाल there is no last written block */
	अगर (!iter->wrap_count && iter->block == iter->start_block)
		वापस msc_iter_win_advance(iter);

	वापस 0;
पूर्ण

/**
 * msc_buffer_iterate() - go through multiblock buffer's data
 * @iter:	iterator काष्ठाure
 * @size:	amount of data to scan
 * @data:	callback's निजी data
 * @fn:		iterator callback
 *
 * This will start at the winकरोw which will be written to next (containing
 * the oldest data) and work its way to the current winकरोw, calling @fn
 * क्रम each chunk of data as it goes.
 *
 * Caller should have msc::user_count reference to make sure the buffer
 * करोesn't disappear from under us.
 *
 * Return:	amount of data actually scanned.
 */
अटल sमाप_प्रकार
msc_buffer_iterate(काष्ठा msc_iter *iter, माप_प्रकार size, व्योम *data,
		   अचिन्हित दीर्घ (*fn)(व्योम *, व्योम *, माप_प्रकार))
अणु
	काष्ठा msc *msc = iter->msc;
	माप_प्रकार len = size;
	अचिन्हित पूर्णांक advance;

	अगर (iter->eof)
		वापस 0;

	/* start with the oldest winकरोw */
	अगर (msc_iter_win_start(iter, msc))
		वापस 0;

	करो अणु
		अचिन्हित दीर्घ data_bytes = msc_data_sz(msc_iter_bdesc(iter));
		व्योम *src = (व्योम *)msc_iter_bdesc(iter) + MSC_BDESC;
		माप_प्रकार tocopy = data_bytes, copied = 0;
		माप_प्रकार reमुख्यing = 0;

		advance = 1;

		/*
		 * If block wrapping happened, we need to visit the last block
		 * twice, because it contains both the oldest and the newest
		 * data in this winकरोw.
		 *
		 * First समय (wrap_count==2), in the very beginning, to collect
		 * the oldest data, which is in the range
		 * (data_bytes..DATA_IN_PAGE).
		 *
		 * Second समय (wrap_count==1), it's just like any other block,
		 * containing data in the range of [MSC_BDESC..data_bytes].
		 */
		अगर (iter->block == iter->start_block && iter->wrap_count == 2) अणु
			tocopy = DATA_IN_PAGE - data_bytes;
			src += data_bytes;
		पूर्ण

		अगर (!tocopy)
			जाओ next_block;

		tocopy -= iter->block_off;
		src += iter->block_off;

		अगर (len < tocopy) अणु
			tocopy = len;
			advance = 0;
		पूर्ण

		reमुख्यing = fn(data, src, tocopy);

		अगर (reमुख्यing)
			advance = 0;

		copied = tocopy - reमुख्यing;
		len -= copied;
		iter->block_off += copied;
		iter->offset += copied;

		अगर (!advance)
			अवरोध;

next_block:
		अगर (msc_iter_block_advance(iter))
			अवरोध;

	पूर्ण जबतक (len);

	वापस size - len;
पूर्ण

/**
 * msc_buffer_clear_hw_header() - clear hw header क्रम multiblock
 * @msc:	MSC device
 */
अटल व्योम msc_buffer_clear_hw_header(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *win;
	काष्ठा scatterlist *sg;

	list_क्रम_each_entry(win, &msc->win_list, entry) अणु
		अचिन्हित पूर्णांक blk;
		माप_प्रकार hw_sz = माप(काष्ठा msc_block_desc) -
			दुरत्व(काष्ठा msc_block_desc, hw_tag);

		क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, blk) अणु
			काष्ठा msc_block_desc *bdesc = sg_virt(sg);

			स_रखो(&bdesc->hw_tag, 0, hw_sz);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_th_msu_init(काष्ठा msc *msc)
अणु
	u32 mपूर्णांकctl, msusts;

	अगर (!msc->करो_irq)
		वापस 0;

	अगर (!msc->mbuf)
		वापस 0;

	mपूर्णांकctl = ioपढ़ो32(msc->msu_base + REG_MSU_MINTCTL);
	mपूर्णांकctl |= msc->index ? M1BLIE : M0BLIE;
	ioग_लिखो32(mपूर्णांकctl, msc->msu_base + REG_MSU_MINTCTL);
	अगर (mपूर्णांकctl != ioपढ़ो32(msc->msu_base + REG_MSU_MINTCTL)) अणु
		dev_info(msc_dev(msc), "MINTCTL ignores writes: no usable interrupts\n");
		msc->करो_irq = 0;
		वापस 0;
	पूर्ण

	msusts = ioपढ़ो32(msc->msu_base + REG_MSU_MSUSTS);
	ioग_लिखो32(msusts, msc->msu_base + REG_MSU_MSUSTS);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_msu_deinit(काष्ठा msc *msc)
अणु
	u32 mपूर्णांकctl;

	अगर (!msc->करो_irq)
		वापस;

	mपूर्णांकctl = ioपढ़ो32(msc->msu_base + REG_MSU_MINTCTL);
	mपूर्णांकctl &= msc->index ? ~M1BLIE : ~M0BLIE;
	ioग_लिखो32(mपूर्णांकctl, msc->msu_base + REG_MSU_MINTCTL);
पूर्ण

अटल पूर्णांक msc_win_set_lockout(काष्ठा msc_winकरोw *win,
			       क्रमागत lockout_state expect,
			       क्रमागत lockout_state new)
अणु
	क्रमागत lockout_state old;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!win->msc->mbuf)
		वापस 0;

	spin_lock_irqsave(&win->lo_lock, flags);
	old = win->lockout;

	अगर (old != expect) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	win->lockout = new;

	अगर (old == expect && new == WIN_LOCKED)
		atomic_inc(&win->msc->user_count);
	अन्यथा अगर (old == expect && old == WIN_LOCKED)
		atomic_dec(&win->msc->user_count);

unlock:
	spin_unlock_irqrestore(&win->lo_lock, flags);

	अगर (ret) अणु
		अगर (expect == WIN_READY && old == WIN_LOCKED)
			वापस -EBUSY;

		/* from पूर्णांकel_th_msc_winकरोw_unlock(), करोn't warn अगर not locked */
		अगर (expect == WIN_LOCKED && old == new)
			वापस 0;

		dev_warn_ratelimited(msc_dev(win->msc),
				     "expected lockout state %d, got %d\n",
				     expect, old);
	पूर्ण

	वापस ret;
पूर्ण
/**
 * msc_configure() - set up MSC hardware
 * @msc:	the MSC device to configure
 *
 * Program storage mode, wrapping, burst length and trace buffer address
 * पूर्णांकo a given MSC. Then, enable tracing and set msc::enabled.
 * The latter is serialized on msc::buf_mutex, so make sure to hold it.
 */
अटल पूर्णांक msc_configure(काष्ठा msc *msc)
अणु
	u32 reg;

	lockdep_निश्चित_held(&msc->buf_mutex);

	अगर (msc->mode > MSC_MODE_MULTI)
		वापस -EINVAL;

	अगर (msc->mode == MSC_MODE_MULTI) अणु
		अगर (msc_win_set_lockout(msc->cur_win, WIN_READY, WIN_INUSE))
			वापस -EBUSY;

		msc_buffer_clear_hw_header(msc);
	पूर्ण

	msc->orig_addr = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0BAR);
	msc->orig_sz   = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0SIZE);

	reg = msc->base_addr >> PAGE_SHIFT;
	ioग_लिखो32(reg, msc->reg_base + REG_MSU_MSC0BAR);

	अगर (msc->mode == MSC_MODE_SINGLE) अणु
		reg = msc->nr_pages;
		ioग_लिखो32(reg, msc->reg_base + REG_MSU_MSC0SIZE);
	पूर्ण

	reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0CTL);
	reg &= ~(MSC_MODE | MSC_WRAPEN | MSC_EN | MSC_RD_HDR_OVRD);

	reg |= MSC_EN;
	reg |= msc->mode << __ffs(MSC_MODE);
	reg |= msc->burst_len << __ffs(MSC_LEN);

	अगर (msc->wrap)
		reg |= MSC_WRAPEN;

	ioग_लिखो32(reg, msc->reg_base + REG_MSU_MSC0CTL);

	पूर्णांकel_th_msu_init(msc);

	msc->thdev->output.multiblock = msc->mode == MSC_MODE_MULTI;
	पूर्णांकel_th_trace_enable(msc->thdev);
	msc->enabled = 1;

	अगर (msc->mbuf && msc->mbuf->activate)
		msc->mbuf->activate(msc->mbuf_priv);

	वापस 0;
पूर्ण

/**
 * msc_disable() - disable MSC hardware
 * @msc:	MSC device to disable
 *
 * If @msc is enabled, disable tracing on the चयन and then disable MSC
 * storage. Caller must hold msc::buf_mutex.
 */
अटल व्योम msc_disable(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *win = msc->cur_win;
	u32 reg;

	lockdep_निश्चित_held(&msc->buf_mutex);

	अगर (msc->mode == MSC_MODE_MULTI)
		msc_win_set_lockout(win, WIN_INUSE, WIN_LOCKED);

	अगर (msc->mbuf && msc->mbuf->deactivate)
		msc->mbuf->deactivate(msc->mbuf_priv);
	पूर्णांकel_th_msu_deinit(msc);
	पूर्णांकel_th_trace_disable(msc->thdev);

	अगर (msc->mode == MSC_MODE_SINGLE) अणु
		reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0STS);
		msc->single_wrap = !!(reg & MSCSTS_WRAPSTAT);

		reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0MWP);
		msc->single_sz = reg & ((msc->nr_pages << PAGE_SHIFT) - 1);
		dev_dbg(msc_dev(msc), "MSCnMWP: %08x/%08lx, wrap: %d\n",
			reg, msc->single_sz, msc->single_wrap);
	पूर्ण

	reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0CTL);
	reg &= ~MSC_EN;
	ioग_लिखो32(reg, msc->reg_base + REG_MSU_MSC0CTL);

	अगर (msc->mbuf && msc->mbuf->पढ़ोy)
		msc->mbuf->पढ़ोy(msc->mbuf_priv, win->sgt,
				 msc_win_total_sz(win));

	msc->enabled = 0;

	ioग_लिखो32(msc->orig_addr, msc->reg_base + REG_MSU_MSC0BAR);
	ioग_लिखो32(msc->orig_sz, msc->reg_base + REG_MSU_MSC0SIZE);

	dev_dbg(msc_dev(msc), "MSCnNWSA: %08x\n",
		ioपढ़ो32(msc->reg_base + REG_MSU_MSC0NWSA));

	reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSC0STS);
	dev_dbg(msc_dev(msc), "MSCnSTS: %08x\n", reg);

	reg = ioपढ़ो32(msc->reg_base + REG_MSU_MSUSTS);
	reg &= msc->index ? MSUSTS_MSC1BLAST : MSUSTS_MSC0BLAST;
	ioग_लिखो32(reg, msc->reg_base + REG_MSU_MSUSTS);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_msc_activate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);
	पूर्णांक ret = -EBUSY;

	अगर (!atomic_inc_unless_negative(&msc->user_count))
		वापस -ENODEV;

	mutex_lock(&msc->buf_mutex);

	/* अगर there are पढ़ोers, refuse */
	अगर (list_empty(&msc->iter_list))
		ret = msc_configure(msc);

	mutex_unlock(&msc->buf_mutex);

	अगर (ret)
		atomic_dec(&msc->user_count);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_th_msc_deactivate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);

	mutex_lock(&msc->buf_mutex);
	अगर (msc->enabled) अणु
		msc_disable(msc);
		atomic_dec(&msc->user_count);
	पूर्ण
	mutex_unlock(&msc->buf_mutex);
पूर्ण

/**
 * msc_buffer_contig_alloc() - allocate a contiguous buffer क्रम SINGLE mode
 * @msc:	MSC device
 * @size:	allocation size in bytes
 *
 * This modअगरies msc::base, which requires msc::buf_mutex to serialize, so the
 * caller is expected to hold it.
 *
 * Return:	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक msc_buffer_contig_alloc(काष्ठा msc *msc, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक order = get_order(size);
	काष्ठा page *page;
	पूर्णांक ret;

	अगर (!size)
		वापस 0;

	ret = sg_alloc_table(&msc->single_sgt, 1, GFP_KERNEL);
	अगर (ret)
		जाओ err_out;

	ret = -ENOMEM;
	page = alloc_pages(GFP_KERNEL | __GFP_ZERO | GFP_DMA32, order);
	अगर (!page)
		जाओ err_मुक्त_sgt;

	split_page(page, order);
	sg_set_buf(msc->single_sgt.sgl, page_address(page), size);

	ret = dma_map_sg(msc_dev(msc)->parent->parent, msc->single_sgt.sgl, 1,
			 DMA_FROM_DEVICE);
	अगर (ret < 0)
		जाओ err_मुक्त_pages;

	msc->nr_pages = nr_pages;
	msc->base = page_address(page);
	msc->base_addr = sg_dma_address(msc->single_sgt.sgl);

	वापस 0;

err_मुक्त_pages:
	__मुक्त_pages(page, order);

err_मुक्त_sgt:
	sg_मुक्त_table(&msc->single_sgt);

err_out:
	वापस ret;
पूर्ण

/**
 * msc_buffer_contig_मुक्त() - मुक्त a contiguous buffer
 * @msc:	MSC configured in SINGLE mode
 */
अटल व्योम msc_buffer_contig_मुक्त(काष्ठा msc *msc)
अणु
	अचिन्हित दीर्घ off;

	dma_unmap_sg(msc_dev(msc)->parent->parent, msc->single_sgt.sgl,
		     1, DMA_FROM_DEVICE);
	sg_मुक्त_table(&msc->single_sgt);

	क्रम (off = 0; off < msc->nr_pages << PAGE_SHIFT; off += PAGE_SIZE) अणु
		काष्ठा page *page = virt_to_page(msc->base + off);

		page->mapping = शून्य;
		__मुक्त_page(page);
	पूर्ण

	msc->nr_pages = 0;
पूर्ण

/**
 * msc_buffer_contig_get_page() - find a page at a given offset
 * @msc:	MSC configured in SINGLE mode
 * @pgoff:	page offset
 *
 * Return:	page, अगर @pgoff is within the range, शून्य otherwise.
 */
अटल काष्ठा page *msc_buffer_contig_get_page(काष्ठा msc *msc,
					       अचिन्हित दीर्घ pgoff)
अणु
	अगर (pgoff >= msc->nr_pages)
		वापस शून्य;

	वापस virt_to_page(msc->base + (pgoff << PAGE_SHIFT));
पूर्ण

अटल पूर्णांक __msc_buffer_win_alloc(काष्ठा msc_winकरोw *win,
				  अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा scatterlist *sg_ptr;
	व्योम *block;
	पूर्णांक i, ret;

	ret = sg_alloc_table(win->sgt, nr_segs, GFP_KERNEL);
	अगर (ret)
		वापस -ENOMEM;

	क्रम_each_sg(win->sgt->sgl, sg_ptr, nr_segs, i) अणु
		block = dma_alloc_coherent(msc_dev(win->msc)->parent->parent,
					  PAGE_SIZE, &sg_dma_address(sg_ptr),
					  GFP_KERNEL);
		अगर (!block)
			जाओ err_nomem;

		sg_set_buf(sg_ptr, block, PAGE_SIZE);
	पूर्ण

	वापस nr_segs;

err_nomem:
	क्रम_each_sg(win->sgt->sgl, sg_ptr, i, ret)
		dma_मुक्त_coherent(msc_dev(win->msc)->parent->parent, PAGE_SIZE,
				  sg_virt(sg_ptr), sg_dma_address(sg_ptr));

	sg_मुक्त_table(win->sgt);

	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_X86
अटल व्योम msc_buffer_set_uc(काष्ठा msc_winकरोw *win, अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा scatterlist *sg_ptr;
	पूर्णांक i;

	क्रम_each_sg(win->sgt->sgl, sg_ptr, nr_segs, i) अणु
		/* Set the page as uncached */
		set_memory_uc((अचिन्हित दीर्घ)sg_virt(sg_ptr),
			      PFN_DOWN(sg_ptr->length));
	पूर्ण
पूर्ण

अटल व्योम msc_buffer_set_wb(काष्ठा msc_winकरोw *win)
अणु
	काष्ठा scatterlist *sg_ptr;
	पूर्णांक i;

	क्रम_each_sg(win->sgt->sgl, sg_ptr, win->nr_segs, i) अणु
		/* Reset the page to ग_लिखो-back */
		set_memory_wb((अचिन्हित दीर्घ)sg_virt(sg_ptr),
			      PFN_DOWN(sg_ptr->length));
	पूर्ण
पूर्ण
#अन्यथा /* !X86 */
अटल अंतरभूत व्योम
msc_buffer_set_uc(काष्ठा msc_winकरोw *win, अचिन्हित पूर्णांक nr_segs) अणुपूर्ण
अटल अंतरभूत व्योम msc_buffer_set_wb(काष्ठा msc_winकरोw *win) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_X86 */

/**
 * msc_buffer_win_alloc() - alloc a winकरोw क्रम a multiblock mode
 * @msc:	MSC device
 * @nr_blocks:	number of pages in this winकरोw
 *
 * This modअगरies msc::win_list and msc::base, which requires msc::buf_mutex
 * to serialize, so the caller is expected to hold it.
 *
 * Return:	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक msc_buffer_win_alloc(काष्ठा msc *msc, अचिन्हित पूर्णांक nr_blocks)
अणु
	काष्ठा msc_winकरोw *win;
	पूर्णांक ret = -ENOMEM;

	अगर (!nr_blocks)
		वापस 0;

	win = kzalloc(माप(*win), GFP_KERNEL);
	अगर (!win)
		वापस -ENOMEM;

	win->msc = msc;
	win->sgt = &win->_sgt;
	win->lockout = WIN_READY;
	spin_lock_init(&win->lo_lock);

	अगर (!list_empty(&msc->win_list)) अणु
		काष्ठा msc_winकरोw *prev = list_last_entry(&msc->win_list,
							  काष्ठा msc_winकरोw,
							  entry);

		win->pgoff = prev->pgoff + prev->nr_blocks;
	पूर्ण

	अगर (msc->mbuf && msc->mbuf->alloc_winकरोw)
		ret = msc->mbuf->alloc_winकरोw(msc->mbuf_priv, &win->sgt,
					      nr_blocks << PAGE_SHIFT);
	अन्यथा
		ret = __msc_buffer_win_alloc(win, nr_blocks);

	अगर (ret <= 0)
		जाओ err_nomem;

	msc_buffer_set_uc(win, ret);

	win->nr_segs = ret;
	win->nr_blocks = nr_blocks;

	अगर (list_empty(&msc->win_list)) अणु
		msc->base = msc_win_base(win);
		msc->base_addr = msc_win_base_dma(win);
		msc->cur_win = win;
	पूर्ण

	list_add_tail(&win->entry, &msc->win_list);
	msc->nr_pages += nr_blocks;

	वापस 0;

err_nomem:
	kमुक्त(win);

	वापस ret;
पूर्ण

अटल व्योम __msc_buffer_win_मुक्त(काष्ठा msc *msc, काष्ठा msc_winकरोw *win)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, i) अणु
		काष्ठा page *page = sg_page(sg);

		page->mapping = शून्य;
		dma_मुक्त_coherent(msc_dev(win->msc)->parent->parent, PAGE_SIZE,
				  sg_virt(sg), sg_dma_address(sg));
	पूर्ण
	sg_मुक्त_table(win->sgt);
पूर्ण

/**
 * msc_buffer_win_मुक्त() - मुक्त a winकरोw from MSC's winकरोw list
 * @msc:	MSC device
 * @win:	winकरोw to मुक्त
 *
 * This modअगरies msc::win_list and msc::base, which requires msc::buf_mutex
 * to serialize, so the caller is expected to hold it.
 */
अटल व्योम msc_buffer_win_मुक्त(काष्ठा msc *msc, काष्ठा msc_winकरोw *win)
अणु
	msc->nr_pages -= win->nr_blocks;

	list_del(&win->entry);
	अगर (list_empty(&msc->win_list)) अणु
		msc->base = शून्य;
		msc->base_addr = 0;
	पूर्ण

	msc_buffer_set_wb(win);

	अगर (msc->mbuf && msc->mbuf->मुक्त_winकरोw)
		msc->mbuf->मुक्त_winकरोw(msc->mbuf_priv, win->sgt);
	अन्यथा
		__msc_buffer_win_मुक्त(msc, win);

	kमुक्त(win);
पूर्ण

/**
 * msc_buffer_relink() - set up block descriptors क्रम multiblock mode
 * @msc:	MSC device
 *
 * This traverses msc::win_list, which requires msc::buf_mutex to serialize,
 * so the caller is expected to hold it.
 */
अटल व्योम msc_buffer_relink(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *win, *next_win;

	/* call with msc::mutex locked */
	list_क्रम_each_entry(win, &msc->win_list, entry) अणु
		काष्ठा scatterlist *sg;
		अचिन्हित पूर्णांक blk;
		u32 sw_tag = 0;

		/*
		 * Last winकरोw's next_win should poपूर्णांक to the first winकरोw
		 * and MSC_SW_TAG_LASTWIN should be set.
		 */
		अगर (msc_is_last_win(win)) अणु
			sw_tag |= MSC_SW_TAG_LASTWIN;
			next_win = list_first_entry(&msc->win_list,
						    काष्ठा msc_winकरोw, entry);
		पूर्ण अन्यथा अणु
			next_win = list_next_entry(win, entry);
		पूर्ण

		क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, blk) अणु
			काष्ठा msc_block_desc *bdesc = sg_virt(sg);

			स_रखो(bdesc, 0, माप(*bdesc));

			bdesc->next_win = msc_win_base_pfn(next_win);

			/*
			 * Similarly to last winकरोw, last block should poपूर्णांक
			 * to the first one.
			 */
			अगर (blk == win->nr_segs - 1) अणु
				sw_tag |= MSC_SW_TAG_LASTBLK;
				bdesc->next_blk = msc_win_base_pfn(win);
			पूर्ण अन्यथा अणु
				dma_addr_t addr = sg_dma_address(sg_next(sg));

				bdesc->next_blk = PFN_DOWN(addr);
			पूर्ण

			bdesc->sw_tag = sw_tag;
			bdesc->block_sz = sg->length / 64;
		पूर्ण
	पूर्ण

	/*
	 * Make the above ग_लिखोs globally visible beक्रमe tracing is
	 * enabled to make sure hardware sees them coherently.
	 */
	wmb();
पूर्ण

अटल व्योम msc_buffer_multi_मुक्त(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *win, *iter;

	list_क्रम_each_entry_safe(win, iter, &msc->win_list, entry)
		msc_buffer_win_मुक्त(msc, win);
पूर्ण

अटल पूर्णांक msc_buffer_multi_alloc(काष्ठा msc *msc, अचिन्हित दीर्घ *nr_pages,
				  अचिन्हित पूर्णांक nr_wins)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < nr_wins; i++) अणु
		ret = msc_buffer_win_alloc(msc, nr_pages[i]);
		अगर (ret) अणु
			msc_buffer_multi_मुक्त(msc);
			वापस ret;
		पूर्ण
	पूर्ण

	msc_buffer_relink(msc);

	वापस 0;
पूर्ण

/**
 * msc_buffer_मुक्त() - मुक्त buffers क्रम MSC
 * @msc:	MSC device
 *
 * Free MSC's storage buffers.
 *
 * This modअगरies msc::win_list and msc::base, which requires msc::buf_mutex to
 * serialize, so the caller is expected to hold it.
 */
अटल व्योम msc_buffer_मुक्त(काष्ठा msc *msc)
अणु
	अगर (msc->mode == MSC_MODE_SINGLE)
		msc_buffer_contig_मुक्त(msc);
	अन्यथा अगर (msc->mode == MSC_MODE_MULTI)
		msc_buffer_multi_मुक्त(msc);
पूर्ण

/**
 * msc_buffer_alloc() - allocate a buffer क्रम MSC
 * @msc:	MSC device
 * @size:	allocation size in bytes
 *
 * Allocate a storage buffer क्रम MSC, depending on the msc::mode, it will be
 * either करोne via msc_buffer_contig_alloc() क्रम SINGLE operation mode or
 * msc_buffer_win_alloc() क्रम multiblock operation. The latter allocates one
 * winकरोw per invocation, so in multiblock mode this can be called multiple
 * बार क्रम the same MSC to allocate multiple winकरोws.
 *
 * This modअगरies msc::win_list and msc::base, which requires msc::buf_mutex
 * to serialize, so the caller is expected to hold it.
 *
 * Return:	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक msc_buffer_alloc(काष्ठा msc *msc, अचिन्हित दीर्घ *nr_pages,
			    अचिन्हित पूर्णांक nr_wins)
अणु
	पूर्णांक ret;

	/* -1: buffer not allocated */
	अगर (atomic_पढ़ो(&msc->user_count) != -1)
		वापस -EBUSY;

	अगर (msc->mode == MSC_MODE_SINGLE) अणु
		अगर (nr_wins != 1)
			वापस -EINVAL;

		ret = msc_buffer_contig_alloc(msc, nr_pages[0] << PAGE_SHIFT);
	पूर्ण अन्यथा अगर (msc->mode == MSC_MODE_MULTI) अणु
		ret = msc_buffer_multi_alloc(msc, nr_pages, nr_wins);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		/* allocation should be visible beक्रमe the counter goes to 0 */
		smp_mb__beक्रमe_atomic();

		अगर (WARN_ON_ONCE(atomic_cmpxchg(&msc->user_count, -1, 0) != -1))
			वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * msc_buffer_unlocked_मुक्त_unless_used() - मुक्त a buffer unless it's in use
 * @msc:	MSC device
 *
 * This will मुक्त MSC buffer unless it is in use or there is no allocated
 * buffer.
 * Caller needs to hold msc::buf_mutex.
 *
 * Return:	0 on successful deallocation or अगर there was no buffer to
 *		deallocate, -EBUSY अगर there are active users.
 */
अटल पूर्णांक msc_buffer_unlocked_मुक्त_unless_used(काष्ठा msc *msc)
अणु
	पूर्णांक count, ret = 0;

	count = atomic_cmpxchg(&msc->user_count, 0, -1);

	/* > 0: buffer is allocated and has users */
	अगर (count > 0)
		ret = -EBUSY;
	/* 0: buffer is allocated, no users */
	अन्यथा अगर (!count)
		msc_buffer_मुक्त(msc);
	/* < 0: no buffer, nothing to करो */

	वापस ret;
पूर्ण

/**
 * msc_buffer_मुक्त_unless_used() - मुक्त a buffer unless it's in use
 * @msc:	MSC device
 *
 * This is a locked version of msc_buffer_unlocked_मुक्त_unless_used().
 */
अटल पूर्णांक msc_buffer_मुक्त_unless_used(काष्ठा msc *msc)
अणु
	पूर्णांक ret;

	mutex_lock(&msc->buf_mutex);
	ret = msc_buffer_unlocked_मुक्त_unless_used(msc);
	mutex_unlock(&msc->buf_mutex);

	वापस ret;
पूर्ण

/**
 * msc_buffer_get_page() - get MSC buffer page at a given offset
 * @msc:	MSC device
 * @pgoff:	page offset पूर्णांकo the storage buffer
 *
 * This traverses msc::win_list, so holding msc::buf_mutex is expected from
 * the caller.
 *
 * Return:	page अगर @pgoff corresponds to a valid buffer page or शून्य.
 */
अटल काष्ठा page *msc_buffer_get_page(काष्ठा msc *msc, अचिन्हित दीर्घ pgoff)
अणु
	काष्ठा msc_winकरोw *win;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक blk;

	अगर (msc->mode == MSC_MODE_SINGLE)
		वापस msc_buffer_contig_get_page(msc, pgoff);

	list_क्रम_each_entry(win, &msc->win_list, entry)
		अगर (pgoff >= win->pgoff && pgoff < win->pgoff + win->nr_blocks)
			जाओ found;

	वापस शून्य;

found:
	pgoff -= win->pgoff;

	क्रम_each_sg(win->sgt->sgl, sg, win->nr_segs, blk) अणु
		काष्ठा page *page = sg_page(sg);
		माप_प्रकार pgsz = PFN_DOWN(sg->length);

		अगर (pgoff < pgsz)
			वापस page + pgoff;

		pgoff -= pgsz;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * काष्ठा msc_win_to_user_काष्ठा - data क्रम copy_to_user() callback
 * @buf:	userspace buffer to copy data to
 * @offset:	running offset
 */
काष्ठा msc_win_to_user_काष्ठा अणु
	अक्षर __user	*buf;
	अचिन्हित दीर्घ	offset;
पूर्ण;

/**
 * msc_win_to_user() - iterator क्रम msc_buffer_iterate() to copy data to user
 * @data:	callback's निजी data
 * @src:	source buffer
 * @len:	amount of data to copy from the source buffer
 */
अटल अचिन्हित दीर्घ msc_win_to_user(व्योम *data, व्योम *src, माप_प्रकार len)
अणु
	काष्ठा msc_win_to_user_काष्ठा *u = data;
	अचिन्हित दीर्घ ret;

	ret = copy_to_user(u->buf + u->offset, src, len);
	u->offset += len - ret;

	वापस ret;
पूर्ण


/*
 * file operations' callbacks
 */

अटल पूर्णांक पूर्णांकel_th_msc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा पूर्णांकel_th_device *thdev = file->निजी_data;
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);
	काष्ठा msc_iter *iter;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	iter = msc_iter_install(msc);
	अगर (IS_ERR(iter))
		वापस PTR_ERR(iter);

	file->निजी_data = iter;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_msc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा msc_iter *iter = file->निजी_data;
	काष्ठा msc *msc = iter->msc;

	msc_iter_हटाओ(iter, msc);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
msc_single_to_user(काष्ठा msc *msc, अक्षर __user *buf, loff_t off, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ size = msc->nr_pages << PAGE_SHIFT, rem = len;
	अचिन्हित दीर्घ start = off, tocopy = 0;

	अगर (msc->single_wrap) अणु
		start += msc->single_sz;
		अगर (start < size) अणु
			tocopy = min(rem, size - start);
			अगर (copy_to_user(buf, msc->base + start, tocopy))
				वापस -EFAULT;

			buf += tocopy;
			rem -= tocopy;
			start += tocopy;
		पूर्ण

		start &= size - 1;
		अगर (rem) अणु
			tocopy = min(rem, msc->single_sz - start);
			अगर (copy_to_user(buf, msc->base + start, tocopy))
				वापस -EFAULT;

			rem -= tocopy;
		पूर्ण

		वापस len - rem;
	पूर्ण

	अगर (copy_to_user(buf, msc->base + start, rem))
		वापस -EFAULT;

	वापस len;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_th_msc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा msc_iter *iter = file->निजी_data;
	काष्ठा msc *msc = iter->msc;
	माप_प्रकार size;
	loff_t off = *ppos;
	sमाप_प्रकार ret = 0;

	अगर (!atomic_inc_unless_negative(&msc->user_count))
		वापस 0;

	अगर (msc->mode == MSC_MODE_SINGLE && !msc->single_wrap)
		size = msc->single_sz;
	अन्यथा
		size = msc->nr_pages << PAGE_SHIFT;

	अगर (!size)
		जाओ put_count;

	अगर (off >= size)
		जाओ put_count;

	अगर (off + len >= size)
		len = size - off;

	अगर (msc->mode == MSC_MODE_SINGLE) अणु
		ret = msc_single_to_user(msc, buf, off, len);
		अगर (ret >= 0)
			*ppos += ret;
	पूर्ण अन्यथा अगर (msc->mode == MSC_MODE_MULTI) अणु
		काष्ठा msc_win_to_user_काष्ठा u = अणु
			.buf	= buf,
			.offset	= 0,
		पूर्ण;

		ret = msc_buffer_iterate(iter, len, &u, msc_win_to_user);
		अगर (ret >= 0)
			*ppos = iter->offset;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

put_count:
	atomic_dec(&msc->user_count);

	वापस ret;
पूर्ण

/*
 * vm operations callbacks (vm_ops)
 */

अटल व्योम msc_mmap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा msc_iter *iter = vma->vm_file->निजी_data;
	काष्ठा msc *msc = iter->msc;

	atomic_inc(&msc->mmap_count);
पूर्ण

अटल व्योम msc_mmap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा msc_iter *iter = vma->vm_file->निजी_data;
	काष्ठा msc *msc = iter->msc;
	अचिन्हित दीर्घ pg;

	अगर (!atomic_dec_and_mutex_lock(&msc->mmap_count, &msc->buf_mutex))
		वापस;

	/* drop page _refcounts */
	क्रम (pg = 0; pg < msc->nr_pages; pg++) अणु
		काष्ठा page *page = msc_buffer_get_page(msc, pg);

		अगर (WARN_ON_ONCE(!page))
			जारी;

		अगर (page->mapping)
			page->mapping = शून्य;
	पूर्ण

	/* last mapping -- drop user_count */
	atomic_dec(&msc->user_count);
	mutex_unlock(&msc->buf_mutex);
पूर्ण

अटल vm_fault_t msc_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा msc_iter *iter = vmf->vma->vm_file->निजी_data;
	काष्ठा msc *msc = iter->msc;

	vmf->page = msc_buffer_get_page(msc, vmf->pgoff);
	अगर (!vmf->page)
		वापस VM_FAULT_SIGBUS;

	get_page(vmf->page);
	vmf->page->mapping = vmf->vma->vm_file->f_mapping;
	vmf->page->index = vmf->pgoff;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा msc_mmap_ops = अणु
	.खोलो	= msc_mmap_खोलो,
	.बंद	= msc_mmap_बंद,
	.fault	= msc_mmap_fault,
पूर्ण;

अटल पूर्णांक पूर्णांकel_th_msc_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	काष्ठा msc_iter *iter = vma->vm_file->निजी_data;
	काष्ठा msc *msc = iter->msc;
	पूर्णांक ret = -EINVAL;

	अगर (!size || offset_in_page(size))
		वापस -EINVAL;

	अगर (vma->vm_pgoff)
		वापस -EINVAL;

	/* grab user_count once per mmap; drop in msc_mmap_बंद() */
	अगर (!atomic_inc_unless_negative(&msc->user_count))
		वापस -EINVAL;

	अगर (msc->mode != MSC_MODE_SINGLE &&
	    msc->mode != MSC_MODE_MULTI)
		जाओ out;

	अगर (size >> PAGE_SHIFT != msc->nr_pages)
		जाओ out;

	atomic_set(&msc->mmap_count, 1);
	ret = 0;

out:
	अगर (ret)
		atomic_dec(&msc->user_count);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTCOPY;
	vma->vm_ops = &msc_mmap_ops;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations पूर्णांकel_th_msc_fops = अणु
	.खोलो		= पूर्णांकel_th_msc_खोलो,
	.release	= पूर्णांकel_th_msc_release,
	.पढ़ो		= पूर्णांकel_th_msc_पढ़ो,
	.mmap		= पूर्णांकel_th_msc_mmap,
	.llseek		= no_llseek,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम पूर्णांकel_th_msc_रुको_empty(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);
	अचिन्हित दीर्घ count;
	u32 reg;

	क्रम (reg = 0, count = MSC_PLE_WAITLOOP_DEPTH;
	     count && !(reg & MSCSTS_PLE); count--) अणु
		reg = __raw_पढ़ोl(msc->reg_base + REG_MSU_MSC0STS);
		cpu_relax();
	पूर्ण

	अगर (!count)
		dev_dbg(msc_dev(msc), "timeout waiting for MSC0 PLE\n");
पूर्ण

अटल पूर्णांक पूर्णांकel_th_msc_init(काष्ठा msc *msc)
अणु
	atomic_set(&msc->user_count, -1);

	msc->mode = msc->multi_is_broken ? MSC_MODE_SINGLE : MSC_MODE_MULTI;
	mutex_init(&msc->buf_mutex);
	INIT_LIST_HEAD(&msc->win_list);
	INIT_LIST_HEAD(&msc->iter_list);

	msc->burst_len =
		(ioपढ़ो32(msc->reg_base + REG_MSU_MSC0CTL) & MSC_LEN) >>
		__ffs(MSC_LEN);

	वापस 0;
पूर्ण

अटल पूर्णांक msc_win_चयन(काष्ठा msc *msc)
अणु
	काष्ठा msc_winकरोw *first;

	अगर (list_empty(&msc->win_list))
		वापस -EINVAL;

	first = list_first_entry(&msc->win_list, काष्ठा msc_winकरोw, entry);

	अगर (msc_is_last_win(msc->cur_win))
		msc->cur_win = first;
	अन्यथा
		msc->cur_win = list_next_entry(msc->cur_win, entry);

	msc->base = msc_win_base(msc->cur_win);
	msc->base_addr = msc_win_base_dma(msc->cur_win);

	पूर्णांकel_th_trace_चयन(msc->thdev);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_th_msc_winकरोw_unlock - put the winकरोw back in rotation
 * @dev:	MSC device to which this relates
 * @sgt:	buffer's sg_table क्रम the winकरोw, करोes nothing अगर शून्य
 */
व्योम पूर्णांकel_th_msc_winकरोw_unlock(काष्ठा device *dev, काष्ठा sg_table *sgt)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	काष्ठा msc_winकरोw *win;

	अगर (!sgt)
		वापस;

	win = msc_find_winकरोw(msc, sgt, false);
	अगर (!win)
		वापस;

	msc_win_set_lockout(win, WIN_LOCKED, WIN_READY);
	अगर (msc->चयन_on_unlock == win) अणु
		msc->चयन_on_unlock = शून्य;
		msc_win_चयन(msc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_msc_winकरोw_unlock);

अटल व्योम msc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msc *msc = container_of(work, काष्ठा msc, work);

	पूर्णांकel_th_msc_deactivate(msc->thdev);
पूर्ण

अटल irqवापस_t पूर्णांकel_th_msc_पूर्णांकerrupt(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);
	u32 msusts = ioपढ़ो32(msc->msu_base + REG_MSU_MSUSTS);
	u32 mask = msc->index ? MSUSTS_MSC1BLAST : MSUSTS_MSC0BLAST;
	काष्ठा msc_winकरोw *win, *next_win;

	अगर (!msc->करो_irq || !msc->mbuf)
		वापस IRQ_NONE;

	msusts &= mask;

	अगर (!msusts)
		वापस msc->enabled ? IRQ_HANDLED : IRQ_NONE;

	ioग_लिखो32(msusts, msc->msu_base + REG_MSU_MSUSTS);

	अगर (!msc->enabled)
		वापस IRQ_NONE;

	/* grab the winकरोw beक्रमe we करो the चयन */
	win = msc->cur_win;
	अगर (!win)
		वापस IRQ_HANDLED;
	next_win = msc_next_winकरोw(win);
	अगर (!next_win)
		वापस IRQ_HANDLED;

	/* next winकरोw: अगर READY, proceed, अगर LOCKED, stop the trace */
	अगर (msc_win_set_lockout(next_win, WIN_READY, WIN_INUSE)) अणु
		अगर (msc->stop_on_full)
			schedule_work(&msc->work);
		अन्यथा
			msc->चयन_on_unlock = next_win;

		वापस IRQ_HANDLED;
	पूर्ण

	/* current winकरोw: INUSE -> LOCKED */
	msc_win_set_lockout(win, WIN_INUSE, WIN_LOCKED);

	msc_win_चयन(msc);

	अगर (msc->mbuf && msc->mbuf->पढ़ोy)
		msc->mbuf->पढ़ोy(msc->mbuf_priv, win->sgt,
				 msc_win_total_sz(win));

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर * स्थिर msc_mode[] = अणु
	[MSC_MODE_SINGLE]	= "single",
	[MSC_MODE_MULTI]	= "multi",
	[MSC_MODE_EXI]		= "ExI",
	[MSC_MODE_DEBUG]	= "debug",
पूर्ण;

अटल sमाप_प्रकार
wrap_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", msc->wrap);
पूर्ण

अटल sमाप_प्रकार
wrap_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार size)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	msc->wrap = !!val;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(wrap);

अटल व्योम msc_buffer_unassign(काष्ठा msc *msc)
अणु
	lockdep_निश्चित_held(&msc->buf_mutex);

	अगर (!msc->mbuf)
		वापस;

	msc->mbuf->unassign(msc->mbuf_priv);
	msu_buffer_put(msc->mbuf);
	msc->mbuf_priv = शून्य;
	msc->mbuf = शून्य;
पूर्ण

अटल sमाप_प्रकार
mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	स्थिर अक्षर *mode = msc_mode[msc->mode];
	sमाप_प्रकार ret;

	mutex_lock(&msc->buf_mutex);
	अगर (msc->mbuf)
		mode = msc->mbuf->name;
	ret = scnम_लिखो(buf, PAGE_SIZE, "%s\n", mode);
	mutex_unlock(&msc->buf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार size)
अणु
	स्थिर काष्ठा msu_buffer *mbuf = शून्य;
	काष्ठा msc *msc = dev_get_drvdata(dev);
	माप_प्रकार len = size;
	अक्षर *cp, *mode;
	पूर्णांक i, ret;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	cp = स_प्रथम(buf, '\n', len);
	अगर (cp)
		len = cp - buf;

	mode = kstrndup(buf, len, GFP_KERNEL);
	अगर (!mode)
		वापस -ENOMEM;

	i = match_string(msc_mode, ARRAY_SIZE(msc_mode), mode);
	अगर (i >= 0) अणु
		kमुक्त(mode);
		जाओ found;
	पूर्ण

	/* Buffer sinks only work with a usable IRQ */
	अगर (!msc->करो_irq) अणु
		kमुक्त(mode);
		वापस -EINVAL;
	पूर्ण

	mbuf = msu_buffer_get(mode);
	kमुक्त(mode);
	अगर (mbuf)
		जाओ found;

	वापस -EINVAL;

found:
	अगर (i == MSC_MODE_MULTI && msc->multi_is_broken)
		वापस -EOPNOTSUPP;

	mutex_lock(&msc->buf_mutex);
	ret = 0;

	/* Same buffer: करो nothing */
	अगर (mbuf && mbuf == msc->mbuf) अणु
		/* put the extra reference we just got */
		msu_buffer_put(mbuf);
		जाओ unlock;
	पूर्ण

	ret = msc_buffer_unlocked_मुक्त_unless_used(msc);
	अगर (ret)
		जाओ unlock;

	अगर (mbuf) अणु
		व्योम *mbuf_priv = mbuf->assign(dev, &i);

		अगर (!mbuf_priv) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण

		msc_buffer_unassign(msc);
		msc->mbuf_priv = mbuf_priv;
		msc->mbuf = mbuf;
	पूर्ण अन्यथा अणु
		msc_buffer_unassign(msc);
	पूर्ण

	msc->mode = i;

unlock:
	अगर (ret && mbuf)
		msu_buffer_put(mbuf);
	mutex_unlock(&msc->buf_mutex);

	वापस ret ? ret : size;
पूर्ण

अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार
nr_pages_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	काष्ठा msc_winकरोw *win;
	माप_प्रकार count = 0;

	mutex_lock(&msc->buf_mutex);

	अगर (msc->mode == MSC_MODE_SINGLE)
		count = scnम_लिखो(buf, PAGE_SIZE, "%ld\n", msc->nr_pages);
	अन्यथा अगर (msc->mode == MSC_MODE_MULTI) अणु
		list_क्रम_each_entry(win, &msc->win_list, entry) अणु
			count += scnम_लिखो(buf + count, PAGE_SIZE - count,
					   "%d%c", win->nr_blocks,
					   msc_is_last_win(win) ? '\n' : ',');
		पूर्ण
	पूर्ण अन्यथा अणु
		count = scnम_लिखो(buf, PAGE_SIZE, "unsupported\n");
	पूर्ण

	mutex_unlock(&msc->buf_mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
nr_pages_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val, *win = शून्य, *rewin;
	माप_प्रकार len = size;
	स्थिर अक्षर *p = buf;
	अक्षर *end, *s;
	पूर्णांक ret, nr_wins = 0;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	ret = msc_buffer_मुक्त_unless_used(msc);
	अगर (ret)
		वापस ret;

	/* scan the comma-separated list of allocation sizes */
	end = स_प्रथम(buf, '\n', len);
	अगर (end)
		len = end - buf;

	करो अणु
		end = स_प्रथम(p, ',', len);
		s = kstrndup(p, end ? end - p : len, GFP_KERNEL);
		अगर (!s) अणु
			ret = -ENOMEM;
			जाओ मुक्त_win;
		पूर्ण

		ret = kम_से_अदीर्घ(s, 10, &val);
		kमुक्त(s);

		अगर (ret || !val)
			जाओ मुक्त_win;

		अगर (nr_wins && msc->mode == MSC_MODE_SINGLE) अणु
			ret = -EINVAL;
			जाओ मुक्त_win;
		पूर्ण

		nr_wins++;
		rewin = kपुनः_स्मृति_array(win, nr_wins, माप(*win), GFP_KERNEL);
		अगर (!rewin) अणु
			kमुक्त(win);
			वापस -ENOMEM;
		पूर्ण

		win = rewin;
		win[nr_wins - 1] = val;

		अगर (!end)
			अवरोध;

		/* consume the number and the following comma, hence +1 */
		len -= end - p + 1;
		p = end + 1;
	पूर्ण जबतक (len);

	mutex_lock(&msc->buf_mutex);
	ret = msc_buffer_alloc(msc, win, nr_wins);
	mutex_unlock(&msc->buf_mutex);

मुक्त_win:
	kमुक्त(win);

	वापस ret ? ret : size;
पूर्ण

अटल DEVICE_ATTR_RW(nr_pages);

अटल sमाप_प्रकार
win_चयन_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 1)
		वापस -EINVAL;

	ret = -EINVAL;
	mutex_lock(&msc->buf_mutex);
	/*
	 * Winकरोw चयन can only happen in the "multi" mode.
	 * If a बाह्यal buffer is engaged, they have the full
	 * control over winकरोw चयनing.
	 */
	अगर (msc->mode == MSC_MODE_MULTI && !msc->mbuf)
		ret = msc_win_चयन(msc);
	mutex_unlock(&msc->buf_mutex);

	वापस ret ? ret : size;
पूर्ण

अटल DEVICE_ATTR_WO(win_चयन);

अटल sमाप_प्रकार stop_on_full_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", msc->stop_on_full);
पूर्ण

अटल sमाप_प्रकार stop_on_full_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा msc *msc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = kstrtobool(buf, &msc->stop_on_full);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(stop_on_full);

अटल काष्ठा attribute *msc_output_attrs[] = अणु
	&dev_attr_wrap.attr,
	&dev_attr_mode.attr,
	&dev_attr_nr_pages.attr,
	&dev_attr_win_चयन.attr,
	&dev_attr_stop_on_full.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group msc_output_group = अणु
	.attrs	= msc_output_attrs,
पूर्ण;

अटल पूर्णांक पूर्णांकel_th_msc_probe(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा device *dev = &thdev->dev;
	काष्ठा resource *res;
	काष्ठा msc *msc;
	व्योम __iomem *base;
	पूर्णांक err;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!base)
		वापस -ENOMEM;

	msc = devm_kzalloc(dev, माप(*msc), GFP_KERNEL);
	अगर (!msc)
		वापस -ENOMEM;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_IRQ, 1);
	अगर (!res)
		msc->करो_irq = 1;

	अगर (INTEL_TH_CAP(to_पूर्णांकel_th(thdev), multi_is_broken))
		msc->multi_is_broken = 1;

	msc->index = thdev->id;

	msc->thdev = thdev;
	msc->reg_base = base + msc->index * 0x100;
	msc->msu_base = base;

	INIT_WORK(&msc->work, msc_work);
	err = पूर्णांकel_th_msc_init(msc);
	अगर (err)
		वापस err;

	dev_set_drvdata(dev, msc);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_msc_हटाओ(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा msc *msc = dev_get_drvdata(&thdev->dev);
	पूर्णांक ret;

	पूर्णांकel_th_msc_deactivate(thdev);

	/*
	 * Buffers should not be used at this poपूर्णांक except अगर the
	 * output अक्षरacter device is still खोलो and the parent
	 * device माला_लो detached from its bus, which is a FIXME.
	 */
	ret = msc_buffer_मुक्त_unless_used(msc);
	WARN_ON_ONCE(ret);
पूर्ण

अटल काष्ठा पूर्णांकel_th_driver पूर्णांकel_th_msc_driver = अणु
	.probe	= पूर्णांकel_th_msc_probe,
	.हटाओ	= पूर्णांकel_th_msc_हटाओ,
	.irq		= पूर्णांकel_th_msc_पूर्णांकerrupt,
	.रुको_empty	= पूर्णांकel_th_msc_रुको_empty,
	.activate	= पूर्णांकel_th_msc_activate,
	.deactivate	= पूर्णांकel_th_msc_deactivate,
	.fops	= &पूर्णांकel_th_msc_fops,
	.attr_group	= &msc_output_group,
	.driver	= अणु
		.name	= "msc",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

module_driver(पूर्णांकel_th_msc_driver,
	      पूर्णांकel_th_driver_रेजिस्टर,
	      पूर्णांकel_th_driver_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub Memory Storage Unit driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
