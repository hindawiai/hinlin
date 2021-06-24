<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2005, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/rtlx.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/vpe.h>

अटल पूर्णांक sp_stopping;
काष्ठा rtlx_info *rtlx;
काष्ठा chan_रुकोqueues channel_wqs[RTLX_CHANNELS];
काष्ठा vpe_notअगरications rtlx_notअगरy;
व्योम (*aprp_hook)(व्योम) = शून्य;
EXPORT_SYMBOL(aprp_hook);

अटल व्योम __used dump_rtlx(व्योम)
अणु
	पूर्णांक i;

	pr_info("id 0x%lx state %d\n", rtlx->id, rtlx->state);

	क्रम (i = 0; i < RTLX_CHANNELS; i++) अणु
		काष्ठा rtlx_channel *chan = &rtlx->channel[i];

		pr_info(" rt_state %d lx_state %d buffer_size %d\n",
			chan->rt_state, chan->lx_state, chan->buffer_size);

		pr_info(" rt_read %d rt_write %d\n",
			chan->rt_पढ़ो, chan->rt_ग_लिखो);

		pr_info(" lx_read %d lx_write %d\n",
			chan->lx_पढ़ो, chan->lx_ग_लिखो);

		pr_info(" rt_buffer <%s>\n", chan->rt_buffer);
		pr_info(" lx_buffer <%s>\n", chan->lx_buffer);
	पूर्ण
पूर्ण

/* call when we have the address of the shared काष्ठाure from the SP side. */
अटल पूर्णांक rtlx_init(काष्ठा rtlx_info *rtlxi)
अणु
	अगर (rtlxi->id != RTLX_ID) अणु
		pr_err("no valid RTLX id at 0x%p 0x%lx\n", rtlxi, rtlxi->id);
		वापस -ENOEXEC;
	पूर्ण

	rtlx = rtlxi;

	वापस 0;
पूर्ण

/* notअगरications */
व्योम rtlx_starting(पूर्णांक vpe)
अणु
	पूर्णांक i;
	sp_stopping = 0;

	/* क्रमce a reload of rtlx */
	rtlx = शून्य;

	/* wake up any sleeping rtlx_खोलो's */
	क्रम (i = 0; i < RTLX_CHANNELS; i++)
		wake_up_पूर्णांकerruptible(&channel_wqs[i].lx_queue);
पूर्ण

व्योम rtlx_stopping(पूर्णांक vpe)
अणु
	पूर्णांक i;

	sp_stopping = 1;
	क्रम (i = 0; i < RTLX_CHANNELS; i++)
		wake_up_पूर्णांकerruptible(&channel_wqs[i].lx_queue);
पूर्ण


पूर्णांक rtlx_खोलो(पूर्णांक index, पूर्णांक can_sleep)
अणु
	काष्ठा rtlx_info **p;
	काष्ठा rtlx_channel *chan;
	क्रमागत rtlx_state state;
	पूर्णांक ret = 0;

	अगर (index >= RTLX_CHANNELS) अणु
		pr_debug("rtlx_open index out of range\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (atomic_inc_वापस(&channel_wqs[index].in_खोलो) > 1) अणु
		pr_debug("rtlx_open channel %d already opened\n", index);
		ret = -EBUSY;
		जाओ out_fail;
	पूर्ण

	अगर (rtlx == शून्य) अणु
		p = vpe_get_shared(aprp_cpu_index());
		अगर (p == शून्य) अणु
			अगर (can_sleep) अणु
				ret = __रुको_event_पूर्णांकerruptible(
					channel_wqs[index].lx_queue,
					(p = vpe_get_shared(aprp_cpu_index())));
				अगर (ret)
					जाओ out_fail;
			पूर्ण अन्यथा अणु
				pr_debug("No SP program loaded, and device opened with O_NONBLOCK\n");
				ret = -ENOSYS;
				जाओ out_fail;
			पूर्ण
		पूर्ण

		smp_rmb();
		अगर (*p == शून्य) अणु
			अगर (can_sleep) अणु
				DEFINE_WAIT(रुको);

				क्रम (;;) अणु
					prepare_to_रुको(
						&channel_wqs[index].lx_queue,
						&रुको, TASK_INTERRUPTIBLE);
					smp_rmb();
					अगर (*p != शून्य)
						अवरोध;
					अगर (!संकेत_pending(current)) अणु
						schedule();
						जारी;
					पूर्ण
					ret = -ERESTARTSYS;
					जाओ out_fail;
				पूर्ण
				finish_रुको(&channel_wqs[index].lx_queue,
					    &रुको);
			पूर्ण अन्यथा अणु
				pr_err(" *vpe_get_shared is NULL. Has an SP program been loaded?\n");
				ret = -ENOSYS;
				जाओ out_fail;
			पूर्ण
		पूर्ण

		अगर ((अचिन्हित पूर्णांक)*p < KSEG0) अणु
			pr_warn("vpe_get_shared returned an invalid pointer maybe an error code %d\n",
				(पूर्णांक)*p);
			ret = -ENOSYS;
			जाओ out_fail;
		पूर्ण

		ret = rtlx_init(*p);
		अगर (ret < 0)
			जाओ out_ret;
	पूर्ण

	chan = &rtlx->channel[index];

	state = xchg(&chan->lx_state, RTLX_STATE_OPENED);
	अगर (state == RTLX_STATE_OPENED) अणु
		ret = -EBUSY;
		जाओ out_fail;
	पूर्ण

out_fail:
	smp_mb();
	atomic_dec(&channel_wqs[index].in_खोलो);
	smp_mb();

out_ret:
	वापस ret;
पूर्ण

पूर्णांक rtlx_release(पूर्णांक index)
अणु
	अगर (rtlx == शून्य) अणु
		pr_err("rtlx_release() with null rtlx\n");
		वापस 0;
	पूर्ण
	rtlx->channel[index].lx_state = RTLX_STATE_UNUSED;
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक rtlx_पढ़ो_poll(पूर्णांक index, पूर्णांक can_sleep)
अणु
	काष्ठा rtlx_channel *chan;

	अगर (rtlx == शून्य)
		वापस 0;

	chan = &rtlx->channel[index];

	/* data available to पढ़ो? */
	अगर (chan->lx_पढ़ो == chan->lx_ग_लिखो) अणु
		अगर (can_sleep) अणु
			पूर्णांक ret = __रुको_event_पूर्णांकerruptible(
				channel_wqs[index].lx_queue,
				(chan->lx_पढ़ो != chan->lx_ग_लिखो) ||
				sp_stopping);
			अगर (ret)
				वापस ret;

			अगर (sp_stopping)
				वापस 0;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण

	वापस (chan->lx_ग_लिखो + chan->buffer_size - chan->lx_पढ़ो)
	       % chan->buffer_size;
पूर्ण

अटल अंतरभूत पूर्णांक ग_लिखो_spaceमुक्त(पूर्णांक पढ़ो, पूर्णांक ग_लिखो, पूर्णांक size)
अणु
	अगर (पढ़ो == ग_लिखो) अणु
		/*
		 * Never fill the buffer completely, so indexes are always
		 * equal अगर empty and only empty, or !equal अगर data available
		 */
		वापस size - 1;
	पूर्ण

	वापस ((पढ़ो + size - ग_लिखो) % size) - 1;
पूर्ण

अचिन्हित पूर्णांक rtlx_ग_लिखो_poll(पूर्णांक index)
अणु
	काष्ठा rtlx_channel *chan = &rtlx->channel[index];

	वापस ग_लिखो_spaceमुक्त(chan->rt_पढ़ो, chan->rt_ग_लिखो,
				chan->buffer_size);
पूर्ण

sमाप_प्रकार rtlx_पढ़ो(पूर्णांक index, व्योम __user *buff, माप_प्रकार count)
अणु
	माप_प्रकार lx_ग_लिखो, fl = 0L;
	काष्ठा rtlx_channel *lx;
	अचिन्हित दीर्घ failed;

	अगर (rtlx == शून्य)
		वापस -ENOSYS;

	lx = &rtlx->channel[index];

	mutex_lock(&channel_wqs[index].mutex);
	smp_rmb();
	lx_ग_लिखो = lx->lx_ग_लिखो;

	/* find out how much in total */
	count = min(count,
		     (माप_प्रकार)(lx_ग_लिखो + lx->buffer_size - lx->lx_पढ़ो)
		     % lx->buffer_size);

	/* then how much from the पढ़ो poपूर्णांकer onwards */
	fl = min(count, (माप_प्रकार)lx->buffer_size - lx->lx_पढ़ो);

	failed = copy_to_user(buff, lx->lx_buffer + lx->lx_पढ़ो, fl);
	अगर (failed)
		जाओ out;

	/* and अगर there is anything left at the beginning of the buffer */
	अगर (count - fl)
		failed = copy_to_user(buff + fl, lx->lx_buffer, count - fl);

out:
	count -= failed;

	smp_wmb();
	lx->lx_पढ़ो = (lx->lx_पढ़ो + count) % lx->buffer_size;
	smp_wmb();
	mutex_unlock(&channel_wqs[index].mutex);

	वापस count;
पूर्ण

sमाप_प्रकार rtlx_ग_लिखो(पूर्णांक index, स्थिर व्योम __user *buffer, माप_प्रकार count)
अणु
	काष्ठा rtlx_channel *rt;
	अचिन्हित दीर्घ failed;
	माप_प्रकार rt_पढ़ो;
	माप_प्रकार fl;

	अगर (rtlx == शून्य)
		वापस -ENOSYS;

	rt = &rtlx->channel[index];

	mutex_lock(&channel_wqs[index].mutex);
	smp_rmb();
	rt_पढ़ो = rt->rt_पढ़ो;

	/* total number of bytes to copy */
	count = min_t(माप_प्रकार, count, ग_लिखो_spaceमुक्त(rt_पढ़ो, rt->rt_ग_लिखो,
						     rt->buffer_size));

	/* first bit from ग_लिखो poपूर्णांकer to the end of the buffer, or count */
	fl = min(count, (माप_प्रकार) rt->buffer_size - rt->rt_ग_लिखो);

	failed = copy_from_user(rt->rt_buffer + rt->rt_ग_लिखो, buffer, fl);
	अगर (failed)
		जाओ out;

	/* अगर there's any left copy to the beginning of the buffer */
	अगर (count - fl)
		failed = copy_from_user(rt->rt_buffer, buffer + fl, count - fl);

out:
	count -= failed;

	smp_wmb();
	rt->rt_ग_लिखो = (rt->rt_ग_लिखो + count) % rt->buffer_size;
	smp_wmb();
	mutex_unlock(&channel_wqs[index].mutex);

	_पूर्णांकerrupt_sp();

	वापस count;
पूर्ण


अटल पूर्णांक file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस rtlx_खोलो(iminor(inode), (filp->f_flags & O_NONBLOCK) ? 0 : 1);
पूर्ण

अटल पूर्णांक file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस rtlx_release(iminor(inode));
पूर्ण

अटल __poll_t file_poll(काष्ठा file *file, poll_table *रुको)
अणु
	पूर्णांक minor = iminor(file_inode(file));
	__poll_t mask = 0;

	poll_रुको(file, &channel_wqs[minor].rt_queue, रुको);
	poll_रुको(file, &channel_wqs[minor].lx_queue, रुको);

	अगर (rtlx == शून्य)
		वापस 0;

	/* data available to पढ़ो? */
	अगर (rtlx_पढ़ो_poll(minor, 0))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* space to ग_लिखो */
	अगर (rtlx_ग_लिखो_poll(minor))
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

अटल sमाप_प्रकार file_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
			 loff_t *ppos)
अणु
	पूर्णांक minor = iminor(file_inode(file));

	/* data available? */
	अगर (!rtlx_पढ़ो_poll(minor, (file->f_flags & O_NONBLOCK) ? 0 : 1))
		वापस 0;	/* -EAGAIN makes 'cat' whine */

	वापस rtlx_पढ़ो(minor, buffer, count);
पूर्ण

अटल sमाप_प्रकार file_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक minor = iminor(file_inode(file));

	/* any space left... */
	अगर (!rtlx_ग_लिखो_poll(minor)) अणु
		पूर्णांक ret;

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		ret = __रुको_event_पूर्णांकerruptible(channel_wqs[minor].rt_queue,
					   rtlx_ग_लिखो_poll(minor));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस rtlx_ग_लिखो(minor, buffer, count);
पूर्ण

स्थिर काष्ठा file_operations rtlx_fops = अणु
	.owner =   THIS_MODULE,
	.खोलो =    file_खोलो,
	.release = file_release,
	.ग_लिखो =   file_ग_लिखो,
	.पढ़ो =    file_पढ़ो,
	.poll =    file_poll,
	.llseek =  noop_llseek,
पूर्ण;

module_init(rtlx_module_init);
module_निकास(rtlx_module_निकास);

MODULE_DESCRIPTION("MIPS RTLX");
MODULE_AUTHOR("Elizabeth Oldham, MIPS Technologies, Inc.");
MODULE_LICENSE("GPL");
