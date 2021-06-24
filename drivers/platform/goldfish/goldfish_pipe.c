<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Intel, Inc.
 * Copyright (C) 2013 Intel, Inc.
 * Copyright (C) 2014 Linaro Limited
 * Copyright (C) 2011-2016 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

/* This source file contains the implementation of a special device driver
 * that पूर्णांकends to provide a *very* fast communication channel between the
 * guest प्रणाली and the QEMU emulator.
 *
 * Usage from the guest is simply the following (error handling simplअगरied):
 *
 *    पूर्णांक  fd = खोलो("/dev/qemu_pipe",O_RDWR);
 *    .... ग_लिखो() or पढ़ो() through the pipe.
 *
 * This driver करोesn't deal with the exact protocol used during the session.
 * It is पूर्णांकended to be as simple as something like:
 *
 *    // करो this _just_ after खोलोing the fd to connect to a specअगरic
 *    // emulator service.
 *    स्थिर अक्षर*  msg = "<pipename>";
 *    अगर (ग_लिखो(fd, msg, म_माप(msg)+1) < 0) अणु
 *       ... could not connect to <pipename> service
 *       बंद(fd);
 *    पूर्ण
 *
 *    // after this, simply पढ़ो() and ग_लिखो() to communicate with the
 *    // service. Exact protocol details left as an exercise to the पढ़ोer.
 *
 * This driver is very fast because it करोesn't copy any data through
 * पूर्णांकermediate buffers, since the emulator is capable of translating
 * guest user addresses पूर्णांकo host ones.
 *
 * Note that we must however ensure that each user page involved in the
 * exchange is properly mapped during a transfer.
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/acpi.h>
#समावेश <linux/bug.h>
#समावेश "goldfish_pipe_qemu.h"

/*
 * Update this when something changes in the driver's behavior so the host
 * can benefit from knowing it
 */
क्रमागत अणु
	PIPE_DRIVER_VERSION = 2,
	PIPE_CURRENT_DEVICE_VERSION = 2
पूर्ण;

क्रमागत अणु
	MAX_BUFFERS_PER_COMMAND = 336,
	MAX_SIGNALLED_PIPES = 64,
	INITIAL_PIPES_CAPACITY = 64
पूर्ण;

काष्ठा goldfish_pipe_dev;

/* A per-pipe command काष्ठाure, shared with the host */
काष्ठा goldfish_pipe_command अणु
	s32 cmd;	/* PipeCmdCode, guest -> host */
	s32 id;		/* pipe id, guest -> host */
	s32 status;	/* command execution status, host -> guest */
	s32 reserved;	/* to pad to 64-bit boundary */
	जोड़ अणु
		/* Parameters क्रम PIPE_CMD_अणुREAD,WRITEपूर्ण */
		काष्ठा अणु
			/* number of buffers, guest -> host */
			u32 buffers_count;
			/* number of consumed bytes, host -> guest */
			s32 consumed_size;
			/* buffer poपूर्णांकers, guest -> host */
			u64 ptrs[MAX_BUFFERS_PER_COMMAND];
			/* buffer sizes, guest -> host */
			u32 sizes[MAX_BUFFERS_PER_COMMAND];
		पूर्ण rw_params;
	पूर्ण;
पूर्ण;

/* A single संकेतled pipe inक्रमmation */
काष्ठा संकेतled_pipe_buffer अणु
	u32 id;
	u32 flags;
पूर्ण;

/* Parameters क्रम the PIPE_CMD_OPEN command */
काष्ठा खोलो_command_param अणु
	u64 command_buffer_ptr;
	u32 rw_params_max_count;
पूर्ण;

/* Device-level set of buffers shared with the host */
काष्ठा goldfish_pipe_dev_buffers अणु
	काष्ठा खोलो_command_param खोलो_command_params;
	काष्ठा संकेतled_pipe_buffer
		संकेतled_pipe_buffers[MAX_SIGNALLED_PIPES];
पूर्ण;

/* This data type models a given pipe instance */
काष्ठा goldfish_pipe अणु
	/* pipe ID - index पूर्णांकo goldfish_pipe_dev::pipes array */
	u32 id;

	/* The wake flags pipe is रुकोing क्रम
	 * Note: not रक्षित with any lock, uses atomic operations
	 *  and barriers to make it thपढ़ो-safe.
	 */
	अचिन्हित दीर्घ flags;

	/* wake flags host have संकेतled,
	 *  - रक्षित by goldfish_pipe_dev::lock
	 */
	अचिन्हित दीर्घ संकेतled_flags;

	/* A poपूर्णांकer to command buffer */
	काष्ठा goldfish_pipe_command *command_buffer;

	/* करोubly linked list of संकेतled pipes, रक्षित by
	 * goldfish_pipe_dev::lock
	 */
	काष्ठा goldfish_pipe *prev_संकेतled;
	काष्ठा goldfish_pipe *next_संकेतled;

	/*
	 * A pipe's own lock. Protects the following:
	 *  - *command_buffer - makes sure a command can safely ग_लिखो its
	 *    parameters to the host and पढ़ो the results back.
	 */
	काष्ठा mutex lock;

	/* A wake queue क्रम sleeping until host संकेतs an event */
	रुको_queue_head_t wake_queue;

	/* Poपूर्णांकer to the parent goldfish_pipe_dev instance */
	काष्ठा goldfish_pipe_dev *dev;

	/* A buffer of pages, too large to fit पूर्णांकo a stack frame */
	काष्ठा page *pages[MAX_BUFFERS_PER_COMMAND];
पूर्ण;

/* The global driver data. Holds a reference to the i/o page used to
 * communicate with the emulator, and a wake queue क्रम blocked tasks
 * रुकोing to be awoken.
 */
काष्ठा goldfish_pipe_dev अणु
	/* A magic number to check अगर this is an instance of this काष्ठा */
	व्योम *magic;

	/*
	 * Global device spinlock. Protects the following members:
	 *  - pipes, pipes_capacity
	 *  - [*pipes, *pipes + pipes_capacity) - array data
	 *  - first_संकेतled_pipe,
	 *      goldfish_pipe::prev_संकेतled,
	 *      goldfish_pipe::next_संकेतled,
	 *      goldfish_pipe::संकेतled_flags - all singnalled-related fields,
	 *                                       in all allocated pipes
	 *  - खोलो_command_params - PIPE_CMD_OPEN-related buffers
	 *
	 * It looks like a lot of dअगरferent fields, but the trick is that
	 * the only operation that happens often is the संकेतled pipes array
	 * manipulation. That's why it's OK क्रम now to keep the rest of the
	 * fields under the same lock. If we notice too much contention because
	 * of PIPE_CMD_OPEN, then we should add a separate lock there.
	 */
	spinlock_t lock;

	/*
	 * Array of the pipes of |pipes_capacity| elements,
	 * indexed by goldfish_pipe::id
	 */
	काष्ठा goldfish_pipe **pipes;
	u32 pipes_capacity;

	/* Poपूर्णांकers to the buffers host uses क्रम पूर्णांकeraction with this driver */
	काष्ठा goldfish_pipe_dev_buffers *buffers;

	/* Head of a करोubly linked list of संकेतled pipes */
	काष्ठा goldfish_pipe *first_संकेतled_pipe;

	/* ptr to platक्रमm device's device काष्ठा */
	काष्ठा device *pdev_dev;

	/* Some device-specअगरic data */
	पूर्णांक irq;
	पूर्णांक version;
	अचिन्हित अक्षर __iomem *base;

	काष्ठा miscdevice miscdev;
पूर्ण;

अटल पूर्णांक goldfish_pipe_cmd_locked(काष्ठा goldfish_pipe *pipe,
				    क्रमागत PipeCmdCode cmd)
अणु
	pipe->command_buffer->cmd = cmd;
	/* failure by शेष */
	pipe->command_buffer->status = PIPE_ERROR_INVAL;
	ग_लिखोl(pipe->id, pipe->dev->base + PIPE_REG_CMD);
	वापस pipe->command_buffer->status;
पूर्ण

अटल पूर्णांक goldfish_pipe_cmd(काष्ठा goldfish_pipe *pipe, क्रमागत PipeCmdCode cmd)
अणु
	पूर्णांक status;

	अगर (mutex_lock_पूर्णांकerruptible(&pipe->lock))
		वापस PIPE_ERROR_IO;
	status = goldfish_pipe_cmd_locked(pipe, cmd);
	mutex_unlock(&pipe->lock);
	वापस status;
पूर्ण

/*
 * This function converts an error code वापसed by the emulator through
 * the PIPE_REG_STATUS i/o रेजिस्टर पूर्णांकo a valid negative त्रुटि_सं value.
 */
अटल पूर्णांक goldfish_pipe_error_convert(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल PIPE_ERROR_AGAIN:
		वापस -EAGAIN;
	हाल PIPE_ERROR_NOMEM:
		वापस -ENOMEM;
	हाल PIPE_ERROR_IO:
		वापस -EIO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक goldfish_pin_pages(अचिन्हित दीर्घ first_page,
			      अचिन्हित दीर्घ last_page,
			      अचिन्हित पूर्णांक last_page_size,
			      पूर्णांक is_ग_लिखो,
			      काष्ठा page *pages[MAX_BUFFERS_PER_COMMAND],
			      अचिन्हित पूर्णांक *iter_last_page_size)
अणु
	पूर्णांक ret;
	पूर्णांक requested_pages = ((last_page - first_page) >> PAGE_SHIFT) + 1;

	अगर (requested_pages > MAX_BUFFERS_PER_COMMAND) अणु
		requested_pages = MAX_BUFFERS_PER_COMMAND;
		*iter_last_page_size = PAGE_SIZE;
	पूर्ण अन्यथा अणु
		*iter_last_page_size = last_page_size;
	पूर्ण

	ret = pin_user_pages_fast(first_page, requested_pages,
				  !is_ग_लिखो ? FOLL_WRITE : 0,
				  pages);
	अगर (ret <= 0)
		वापस -EFAULT;
	अगर (ret < requested_pages)
		*iter_last_page_size = PAGE_SIZE;

	वापस ret;
पूर्ण

/* Populate the call parameters, merging adjacent pages together */
अटल व्योम populate_rw_params(काष्ठा page **pages,
			       पूर्णांक pages_count,
			       अचिन्हित दीर्घ address,
			       अचिन्हित दीर्घ address_end,
			       अचिन्हित दीर्घ first_page,
			       अचिन्हित दीर्घ last_page,
			       अचिन्हित पूर्णांक iter_last_page_size,
			       पूर्णांक is_ग_लिखो,
			       काष्ठा goldfish_pipe_command *command)
अणु
	/*
	 * Process the first page separately - it's the only page that
	 * needs special handling क्रम its start address.
	 */
	अचिन्हित दीर्घ xaddr = page_to_phys(pages[0]);
	अचिन्हित दीर्घ xaddr_prev = xaddr;
	पूर्णांक buffer_idx = 0;
	पूर्णांक i = 1;
	पूर्णांक size_on_page = first_page == last_page
			? (पूर्णांक)(address_end - address)
			: (PAGE_SIZE - (address & ~PAGE_MASK));
	command->rw_params.ptrs[0] = (u64)(xaddr | (address & ~PAGE_MASK));
	command->rw_params.sizes[0] = size_on_page;
	क्रम (; i < pages_count; ++i) अणु
		xaddr = page_to_phys(pages[i]);
		size_on_page = (i == pages_count - 1) ?
			iter_last_page_size : PAGE_SIZE;
		अगर (xaddr == xaddr_prev + PAGE_SIZE) अणु
			command->rw_params.sizes[buffer_idx] += size_on_page;
		पूर्ण अन्यथा अणु
			++buffer_idx;
			command->rw_params.ptrs[buffer_idx] = (u64)xaddr;
			command->rw_params.sizes[buffer_idx] = size_on_page;
		पूर्ण
		xaddr_prev = xaddr;
	पूर्ण
	command->rw_params.buffers_count = buffer_idx + 1;
पूर्ण

अटल पूर्णांक transfer_max_buffers(काष्ठा goldfish_pipe *pipe,
				अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ address_end,
				पूर्णांक is_ग_लिखो,
				अचिन्हित दीर्घ last_page,
				अचिन्हित पूर्णांक last_page_size,
				s32 *consumed_size,
				पूर्णांक *status)
अणु
	अचिन्हित दीर्घ first_page = address & PAGE_MASK;
	अचिन्हित पूर्णांक iter_last_page_size;
	पूर्णांक pages_count;

	/* Serialize access to the pipe command buffers */
	अगर (mutex_lock_पूर्णांकerruptible(&pipe->lock))
		वापस -ERESTARTSYS;

	pages_count = goldfish_pin_pages(first_page, last_page,
					 last_page_size, is_ग_लिखो,
					 pipe->pages, &iter_last_page_size);
	अगर (pages_count < 0) अणु
		mutex_unlock(&pipe->lock);
		वापस pages_count;
	पूर्ण

	populate_rw_params(pipe->pages, pages_count, address, address_end,
			   first_page, last_page, iter_last_page_size, is_ग_लिखो,
			   pipe->command_buffer);

	/* Transfer the data */
	*status = goldfish_pipe_cmd_locked(pipe,
				is_ग_लिखो ? PIPE_CMD_WRITE : PIPE_CMD_READ);

	*consumed_size = pipe->command_buffer->rw_params.consumed_size;

	unpin_user_pages_dirty_lock(pipe->pages, pages_count,
				    !is_ग_लिखो && *consumed_size > 0);

	mutex_unlock(&pipe->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक रुको_क्रम_host_संकेत(काष्ठा goldfish_pipe *pipe, पूर्णांक is_ग_लिखो)
अणु
	u32 wake_bit = is_ग_लिखो ? BIT_WAKE_ON_WRITE : BIT_WAKE_ON_READ;

	set_bit(wake_bit, &pipe->flags);

	/* Tell the emulator we're going to रुको क्रम a wake event */
	goldfish_pipe_cmd(pipe,
		is_ग_लिखो ? PIPE_CMD_WAKE_ON_WRITE : PIPE_CMD_WAKE_ON_READ);

	जबतक (test_bit(wake_bit, &pipe->flags)) अणु
		अगर (रुको_event_पूर्णांकerruptible(pipe->wake_queue,
					     !test_bit(wake_bit, &pipe->flags)))
			वापस -ERESTARTSYS;

		अगर (test_bit(BIT_CLOSED_ON_HOST, &pipe->flags))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार goldfish_pipe_पढ़ो_ग_लिखो(काष्ठा file *filp,
					अक्षर __user *buffer,
					माप_प्रकार bufflen,
					पूर्णांक is_ग_लिखो)
अणु
	काष्ठा goldfish_pipe *pipe = filp->निजी_data;
	पूर्णांक count = 0, ret = -EINVAL;
	अचिन्हित दीर्घ address, address_end, last_page;
	अचिन्हित पूर्णांक last_page_size;

	/* If the emulator alपढ़ोy बंदd the pipe, no need to go further */
	अगर (unlikely(test_bit(BIT_CLOSED_ON_HOST, &pipe->flags)))
		वापस -EIO;
	/* Null पढ़ोs or ग_लिखोs succeeds */
	अगर (unlikely(bufflen == 0))
		वापस 0;
	/* Check the buffer range क्रम access */
	अगर (unlikely(!access_ok(buffer, bufflen)))
		वापस -EFAULT;

	address = (अचिन्हित दीर्घ)buffer;
	address_end = address + bufflen;
	last_page = (address_end - 1) & PAGE_MASK;
	last_page_size = ((address_end - 1) & ~PAGE_MASK) + 1;

	जबतक (address < address_end) अणु
		s32 consumed_size;
		पूर्णांक status;

		ret = transfer_max_buffers(pipe, address, address_end, is_ग_लिखो,
					   last_page, last_page_size,
					   &consumed_size, &status);
		अगर (ret < 0)
			अवरोध;

		अगर (consumed_size > 0) अणु
			/* No matter what's the status, we've transferred
			 * something.
			 */
			count += consumed_size;
			address += consumed_size;
		पूर्ण
		अगर (status > 0)
			जारी;
		अगर (status == 0) अणु
			/* खातापूर्ण */
			ret = 0;
			अवरोध;
		पूर्ण
		अगर (count > 0) अणु
			/*
			 * An error occurred, but we alपढ़ोy transferred
			 * something on one of the previous iterations.
			 * Just वापस what we alपढ़ोy copied and log this
			 * err.
			 */
			अगर (status != PIPE_ERROR_AGAIN)
				dev_err_ratelimited(pipe->dev->pdev_dev,
					"backend error %d on %s\n",
					status, is_ग_लिखो ? "write" : "read");
			अवरोध;
		पूर्ण

		/*
		 * If the error is not PIPE_ERROR_AGAIN, or अगर we are in
		 * non-blocking mode, just वापस the error code.
		 */
		अगर (status != PIPE_ERROR_AGAIN ||
			(filp->f_flags & O_NONBLOCK) != 0) अणु
			ret = goldfish_pipe_error_convert(status);
			अवरोध;
		पूर्ण

		status = रुको_क्रम_host_संकेत(pipe, is_ग_लिखो);
		अगर (status < 0)
			वापस status;
	पूर्ण

	अगर (count > 0)
		वापस count;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार goldfish_pipe_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				  माप_प्रकार bufflen, loff_t *ppos)
अणु
	वापस goldfish_pipe_पढ़ो_ग_लिखो(filp, buffer, bufflen,
					/* is_ग_लिखो */ 0);
पूर्ण

अटल sमाप_प्रकार goldfish_pipe_ग_लिखो(काष्ठा file *filp,
				   स्थिर अक्षर __user *buffer, माप_प्रकार bufflen,
				   loff_t *ppos)
अणु
	/* cast away the स्थिर */
	अक्षर __user *no_स्थिर_buffer = (अक्षर __user *)buffer;

	वापस goldfish_pipe_पढ़ो_ग_लिखो(filp, no_स्थिर_buffer, bufflen,
					/* is_ग_लिखो */ 1);
पूर्ण

अटल __poll_t goldfish_pipe_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा goldfish_pipe *pipe = filp->निजी_data;
	__poll_t mask = 0;
	पूर्णांक status;

	poll_रुको(filp, &pipe->wake_queue, रुको);

	status = goldfish_pipe_cmd(pipe, PIPE_CMD_POLL);
	अगर (status < 0)
		वापस -ERESTARTSYS;

	अगर (status & PIPE_POLL_IN)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (status & PIPE_POLL_OUT)
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (status & PIPE_POLL_HUP)
		mask |= EPOLLHUP;
	अगर (test_bit(BIT_CLOSED_ON_HOST, &pipe->flags))
		mask |= EPOLLERR;

	वापस mask;
पूर्ण

अटल व्योम संकेतled_pipes_add_locked(काष्ठा goldfish_pipe_dev *dev,
				       u32 id, u32 flags)
अणु
	काष्ठा goldfish_pipe *pipe;

	अगर (WARN_ON(id >= dev->pipes_capacity))
		वापस;

	pipe = dev->pipes[id];
	अगर (!pipe)
		वापस;
	pipe->संकेतled_flags |= flags;

	अगर (pipe->prev_संकेतled || pipe->next_संकेतled ||
		dev->first_संकेतled_pipe == pipe)
		वापस;	/* alपढ़ोy in the list */
	pipe->next_संकेतled = dev->first_संकेतled_pipe;
	अगर (dev->first_संकेतled_pipe)
		dev->first_संकेतled_pipe->prev_संकेतled = pipe;
	dev->first_संकेतled_pipe = pipe;
पूर्ण

अटल व्योम संकेतled_pipes_हटाओ_locked(काष्ठा goldfish_pipe_dev *dev,
					  काष्ठा goldfish_pipe *pipe)
अणु
	अगर (pipe->prev_संकेतled)
		pipe->prev_संकेतled->next_संकेतled = pipe->next_संकेतled;
	अगर (pipe->next_संकेतled)
		pipe->next_संकेतled->prev_संकेतled = pipe->prev_संकेतled;
	अगर (pipe == dev->first_संकेतled_pipe)
		dev->first_संकेतled_pipe = pipe->next_संकेतled;
	pipe->prev_संकेतled = शून्य;
	pipe->next_संकेतled = शून्य;
पूर्ण

अटल काष्ठा goldfish_pipe *संकेतled_pipes_pop_front(
		काष्ठा goldfish_pipe_dev *dev, पूर्णांक *wakes)
अणु
	काष्ठा goldfish_pipe *pipe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	pipe = dev->first_संकेतled_pipe;
	अगर (pipe) अणु
		*wakes = pipe->संकेतled_flags;
		pipe->संकेतled_flags = 0;
		/*
		 * This is an optimized version of
		 * संकेतled_pipes_हटाओ_locked()
		 * - We want to make it as fast as possible to
		 * wake the sleeping pipe operations faster.
		 */
		dev->first_संकेतled_pipe = pipe->next_संकेतled;
		अगर (dev->first_संकेतled_pipe)
			dev->first_संकेतled_pipe->prev_संकेतled = शून्य;
		pipe->next_संकेतled = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);
	वापस pipe;
पूर्ण

अटल irqवापस_t goldfish_पूर्णांकerrupt_task(पूर्णांक irq, व्योम *dev_addr)
अणु
	/* Iterate over the संकेतled pipes and wake them one by one */
	काष्ठा goldfish_pipe_dev *dev = dev_addr;
	काष्ठा goldfish_pipe *pipe;
	पूर्णांक wakes;

	जबतक ((pipe = संकेतled_pipes_pop_front(dev, &wakes)) != शून्य) अणु
		अगर (wakes & PIPE_WAKE_CLOSED) अणु
			pipe->flags = 1 << BIT_CLOSED_ON_HOST;
		पूर्ण अन्यथा अणु
			अगर (wakes & PIPE_WAKE_READ)
				clear_bit(BIT_WAKE_ON_READ, &pipe->flags);
			अगर (wakes & PIPE_WAKE_WRITE)
				clear_bit(BIT_WAKE_ON_WRITE, &pipe->flags);
		पूर्ण
		/*
		 * wake_up_पूर्णांकerruptible() implies a ग_लिखो barrier, so करोn't
		 * explicitly add another one here.
		 */
		wake_up_पूर्णांकerruptible(&pipe->wake_queue);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम goldfish_pipe_device_deinit(काष्ठा platक्रमm_device *pdev,
					काष्ठा goldfish_pipe_dev *dev);

/*
 * The general idea of the (thपढ़ोed) पूर्णांकerrupt handling:
 *
 *  1. device उठाओs an पूर्णांकerrupt अगर there's at least one संकेतled pipe
 *  2. IRQ handler पढ़ोs the संकेतled pipes and their count from the device
 *  3. device ग_लिखोs them पूर्णांकo a shared buffer and वापसs the count
 *      it only resets the IRQ अगर it has वापसed all संकेतled pipes,
 *      otherwise it leaves it उठाओd, so IRQ handler will be called
 *      again क्रम the next chunk
 *  4. IRQ handler adds all वापसed pipes to the device's संकेतled pipes list
 *  5. IRQ handler defers processing the संकेतled pipes from the list in a
 *      separate context
 */
अटल irqवापस_t goldfish_pipe_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 count;
	u32 i;
	अचिन्हित दीर्घ flags;
	काष्ठा goldfish_pipe_dev *dev = dev_id;

	अगर (dev->magic != &goldfish_pipe_device_deinit)
		वापस IRQ_NONE;

	/* Request the संकेतled pipes from the device */
	spin_lock_irqsave(&dev->lock, flags);

	count = पढ़ोl(dev->base + PIPE_REG_GET_SIGNALLED);
	अगर (count == 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस IRQ_NONE;
	पूर्ण
	अगर (count > MAX_SIGNALLED_PIPES)
		count = MAX_SIGNALLED_PIPES;

	क्रम (i = 0; i < count; ++i)
		संकेतled_pipes_add_locked(dev,
			dev->buffers->संकेतled_pipe_buffers[i].id,
			dev->buffers->संकेतled_pipe_buffers[i].flags);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक get_मुक्त_pipe_id_locked(काष्ठा goldfish_pipe_dev *dev)
अणु
	पूर्णांक id;

	क्रम (id = 0; id < dev->pipes_capacity; ++id)
		अगर (!dev->pipes[id])
			वापस id;

	अणु
		/* Reallocate the array.
		 * Since get_मुक्त_pipe_id_locked runs with पूर्णांकerrupts disabled,
		 * we करोn't want to make calls that could lead to sleep.
		 */
		u32 new_capacity = 2 * dev->pipes_capacity;
		काष्ठा goldfish_pipe **pipes =
			kसुस्मृति(new_capacity, माप(*pipes), GFP_ATOMIC);
		अगर (!pipes)
			वापस -ENOMEM;
		स_नकल(pipes, dev->pipes, माप(*pipes) * dev->pipes_capacity);
		kमुक्त(dev->pipes);
		dev->pipes = pipes;
		id = dev->pipes_capacity;
		dev->pipes_capacity = new_capacity;
	पूर्ण
	वापस id;
पूर्ण

/* A helper function to get the instance of goldfish_pipe_dev from file */
अटल काष्ठा goldfish_pipe_dev *to_goldfish_pipe_dev(काष्ठा file *file)
अणु
	काष्ठा miscdevice *miscdev = file->निजी_data;

	वापस container_of(miscdev, काष्ठा goldfish_pipe_dev, miscdev);
पूर्ण

/**
 *	goldfish_pipe_खोलो - खोलो a channel to the AVD
 *	@inode: inode of device
 *	@file: file काष्ठा of खोलोer
 *
 *	Create a new pipe link between the emulator and the use application.
 *	Each new request produces a new pipe.
 *
 *	Note: we use the pipe ID as a mux. All goldfish emulations are 32bit
 *	right now so this is fine. A move to 64bit will need this addressing
 */
अटल पूर्णांक goldfish_pipe_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा goldfish_pipe_dev *dev = to_goldfish_pipe_dev(file);
	अचिन्हित दीर्घ flags;
	पूर्णांक id;
	पूर्णांक status;

	/* Allocate new pipe kernel object */
	काष्ठा goldfish_pipe *pipe = kzalloc(माप(*pipe), GFP_KERNEL);

	अगर (!pipe)
		वापस -ENOMEM;

	pipe->dev = dev;
	mutex_init(&pipe->lock);
	init_रुकोqueue_head(&pipe->wake_queue);

	/*
	 * Command buffer needs to be allocated on its own page to make sure
	 * it is physically contiguous in host's address space.
	 */
	BUILD_BUG_ON(माप(काष्ठा goldfish_pipe_command) > PAGE_SIZE);
	pipe->command_buffer =
		(काष्ठा goldfish_pipe_command *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!pipe->command_buffer) अणु
		status = -ENOMEM;
		जाओ err_pipe;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);

	id = get_मुक्त_pipe_id_locked(dev);
	अगर (id < 0) अणु
		status = id;
		जाओ err_id_locked;
	पूर्ण

	dev->pipes[id] = pipe;
	pipe->id = id;
	pipe->command_buffer->id = id;

	/* Now tell the emulator we're खोलोing a new pipe. */
	dev->buffers->खोलो_command_params.rw_params_max_count =
			MAX_BUFFERS_PER_COMMAND;
	dev->buffers->खोलो_command_params.command_buffer_ptr =
			(u64)(अचिन्हित दीर्घ)__pa(pipe->command_buffer);
	status = goldfish_pipe_cmd_locked(pipe, PIPE_CMD_OPEN);
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (status < 0)
		जाओ err_cmd;
	/* All is करोne, save the pipe पूर्णांकo the file's निजी data field */
	file->निजी_data = pipe;
	वापस 0;

err_cmd:
	spin_lock_irqsave(&dev->lock, flags);
	dev->pipes[id] = शून्य;
err_id_locked:
	spin_unlock_irqrestore(&dev->lock, flags);
	मुक्त_page((अचिन्हित दीर्घ)pipe->command_buffer);
err_pipe:
	kमुक्त(pipe);
	वापस status;
पूर्ण

अटल पूर्णांक goldfish_pipe_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा goldfish_pipe *pipe = filp->निजी_data;
	काष्ठा goldfish_pipe_dev *dev = pipe->dev;

	/* The guest is closing the channel, so tell the emulator right now */
	goldfish_pipe_cmd(pipe, PIPE_CMD_CLOSE);

	spin_lock_irqsave(&dev->lock, flags);
	dev->pipes[pipe->id] = शून्य;
	संकेतled_pipes_हटाओ_locked(dev, pipe);
	spin_unlock_irqrestore(&dev->lock, flags);

	filp->निजी_data = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)pipe->command_buffer);
	kमुक्त(pipe);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations goldfish_pipe_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = goldfish_pipe_पढ़ो,
	.ग_लिखो = goldfish_pipe_ग_लिखो,
	.poll = goldfish_pipe_poll,
	.खोलो = goldfish_pipe_खोलो,
	.release = goldfish_pipe_release,
पूर्ण;

अटल व्योम init_miscdevice(काष्ठा miscdevice *miscdev)
अणु
	स_रखो(miscdev, 0, माप(*miscdev));

	miscdev->minor = MISC_DYNAMIC_MINOR;
	miscdev->name = "goldfish_pipe";
	miscdev->fops = &goldfish_pipe_fops;
पूर्ण

अटल व्योम ग_लिखो_pa_addr(व्योम *addr, व्योम __iomem *portl, व्योम __iomem *porth)
अणु
	स्थिर अचिन्हित दीर्घ paddr = __pa(addr);

	ग_लिखोl(upper_32_bits(paddr), porth);
	ग_लिखोl(lower_32_bits(paddr), portl);
पूर्ण

अटल पूर्णांक goldfish_pipe_device_init(काष्ठा platक्रमm_device *pdev,
				     काष्ठा goldfish_pipe_dev *dev)
अणु
	पूर्णांक err;

	err = devm_request_thपढ़ोed_irq(&pdev->dev, dev->irq,
					goldfish_pipe_पूर्णांकerrupt,
					goldfish_पूर्णांकerrupt_task,
					IRQF_SHARED, "goldfish_pipe", dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to allocate IRQ for v2\n");
		वापस err;
	पूर्ण

	init_miscdevice(&dev->miscdev);
	err = misc_रेजिस्टर(&dev->miscdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to register v2 device\n");
		वापस err;
	पूर्ण

	dev->pdev_dev = &pdev->dev;
	dev->first_संकेतled_pipe = शून्य;
	dev->pipes_capacity = INITIAL_PIPES_CAPACITY;
	dev->pipes = kसुस्मृति(dev->pipes_capacity, माप(*dev->pipes),
			     GFP_KERNEL);
	अगर (!dev->pipes) अणु
		misc_deरेजिस्टर(&dev->miscdev);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * We're going to pass two buffers, खोलो_command_params and
	 * संकेतled_pipe_buffers, to the host. This means each of those buffers
	 * needs to be contained in a single physical page. The easiest choice
	 * is to just allocate a page and place the buffers in it.
	 */
	BUILD_BUG_ON(माप(काष्ठा goldfish_pipe_dev_buffers) > PAGE_SIZE);
	dev->buffers = (काष्ठा goldfish_pipe_dev_buffers *)
		__get_मुक्त_page(GFP_KERNEL);
	अगर (!dev->buffers) अणु
		kमुक्त(dev->pipes);
		misc_deरेजिस्टर(&dev->miscdev);
		वापस -ENOMEM;
	पूर्ण

	/* Send the buffer addresses to the host */
	ग_लिखो_pa_addr(&dev->buffers->संकेतled_pipe_buffers,
		      dev->base + PIPE_REG_SIGNAL_BUFFER,
		      dev->base + PIPE_REG_SIGNAL_BUFFER_HIGH);

	ग_लिखोl(MAX_SIGNALLED_PIPES,
	       dev->base + PIPE_REG_SIGNAL_BUFFER_COUNT);

	ग_लिखो_pa_addr(&dev->buffers->खोलो_command_params,
		      dev->base + PIPE_REG_OPEN_BUFFER,
		      dev->base + PIPE_REG_OPEN_BUFFER_HIGH);

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;
पूर्ण

अटल व्योम goldfish_pipe_device_deinit(काष्ठा platक्रमm_device *pdev,
					काष्ठा goldfish_pipe_dev *dev)
अणु
	misc_deरेजिस्टर(&dev->miscdev);
	kमुक्त(dev->pipes);
	मुक्त_page((अचिन्हित दीर्घ)dev->buffers);
पूर्ण

अटल पूर्णांक goldfish_pipe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r;
	काष्ठा goldfish_pipe_dev *dev;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->magic = &goldfish_pipe_device_deinit;
	spin_lock_init(&dev->lock);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r || resource_size(r) < PAGE_SIZE) अणु
		dev_err(&pdev->dev, "can't allocate i/o page\n");
		वापस -EINVAL;
	पूर्ण
	dev->base = devm_ioremap(&pdev->dev, r->start, PAGE_SIZE);
	अगर (!dev->base) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		वापस -EINVAL;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!r)
		वापस -EINVAL;

	dev->irq = r->start;

	/*
	 * Exchange the versions with the host device
	 *
	 * Note: v1 driver used to not report its version, so we ग_लिखो it beक्रमe
	 *  पढ़ोing device version back: this allows the host implementation to
	 *  detect the old driver (अगर there was no version ग_लिखो beक्रमe पढ़ो).
	 */
	ग_लिखोl(PIPE_DRIVER_VERSION, dev->base + PIPE_REG_VERSION);
	dev->version = पढ़ोl(dev->base + PIPE_REG_VERSION);
	अगर (WARN_ON(dev->version < PIPE_CURRENT_DEVICE_VERSION))
		वापस -EINVAL;

	वापस goldfish_pipe_device_init(pdev, dev);
पूर्ण

अटल पूर्णांक goldfish_pipe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा goldfish_pipe_dev *dev = platक्रमm_get_drvdata(pdev);

	goldfish_pipe_device_deinit(pdev, dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id goldfish_pipe_acpi_match[] = अणु
	अणु "GFSH0003", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, goldfish_pipe_acpi_match);

अटल स्थिर काष्ठा of_device_id goldfish_pipe_of_match[] = अणु
	अणु .compatible = "google,android-pipe", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, goldfish_pipe_of_match);

अटल काष्ठा platक्रमm_driver goldfish_pipe_driver = अणु
	.probe = goldfish_pipe_probe,
	.हटाओ = goldfish_pipe_हटाओ,
	.driver = अणु
		.name = "goldfish_pipe",
		.of_match_table = goldfish_pipe_of_match,
		.acpi_match_table = ACPI_PTR(goldfish_pipe_acpi_match),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(goldfish_pipe_driver);
MODULE_AUTHOR("David Turner <digit@google.com>");
MODULE_LICENSE("GPL v2");
