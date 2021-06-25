<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <drm/lima_drm.h>

#समावेश "lima_device.h"
#समावेश "lima_pp.h"
#समावेश "lima_dlbu.h"
#समावेश "lima_bcast.h"
#समावेश "lima_vm.h"
#समावेश "lima_regs.h"

#घोषणा pp_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा pp_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

अटल व्योम lima_pp_handle_irq(काष्ठा lima_ip *ip, u32 state)
अणु
	काष्ठा lima_device *dev = ip->dev;
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;

	अगर (state & LIMA_PP_IRQ_MASK_ERROR) अणु
		u32 status = pp_पढ़ो(LIMA_PP_STATUS);

		dev_err(dev->dev, "pp error irq state=%x status=%x\n",
			state, status);

		pipe->error = true;

		/* mask all पूर्णांकerrupts beक्रमe hard reset */
		pp_ग_लिखो(LIMA_PP_INT_MASK, 0);
	पूर्ण

	pp_ग_लिखो(LIMA_PP_INT_CLEAR, state);
पूर्ण

अटल irqवापस_t lima_pp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lima_ip *ip = data;
	काष्ठा lima_device *dev = ip->dev;
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	u32 state = pp_पढ़ो(LIMA_PP_INT_STATUS);

	/* क्रम shared irq हाल */
	अगर (!state)
		वापस IRQ_NONE;

	lima_pp_handle_irq(ip, state);

	अगर (atomic_dec_and_test(&pipe->task))
		lima_sched_pipe_task_करोne(pipe);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lima_pp_bcast_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक i;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा lima_ip *pp_bcast = data;
	काष्ठा lima_device *dev = pp_bcast->dev;
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	काष्ठा drm_lima_m450_pp_frame *frame;

	/* क्रम shared irq हाल */
	अगर (!pipe->current_task)
		वापस IRQ_NONE;

	frame = pipe->current_task->frame;

	क्रम (i = 0; i < frame->num_pp; i++) अणु
		काष्ठा lima_ip *ip = pipe->processor[i];
		u32 status, state;

		अगर (pipe->करोne & (1 << i))
			जारी;

		/* status पढ़ो first in हाल पूर्णांक state change in the middle
		 * which may miss the पूर्णांकerrupt handling
		 */
		status = pp_पढ़ो(LIMA_PP_STATUS);
		state = pp_पढ़ो(LIMA_PP_INT_STATUS);

		अगर (state) अणु
			lima_pp_handle_irq(ip, state);
			ret = IRQ_HANDLED;
		पूर्ण अन्यथा अणु
			अगर (status & LIMA_PP_STATUS_RENDERING_ACTIVE)
				जारी;
		पूर्ण

		pipe->करोne |= (1 << i);
		अगर (atomic_dec_and_test(&pipe->task))
			lima_sched_pipe_task_करोne(pipe);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम lima_pp_soft_reset_async(काष्ठा lima_ip *ip)
अणु
	अगर (ip->data.async_reset)
		वापस;

	pp_ग_लिखो(LIMA_PP_INT_MASK, 0);
	pp_ग_लिखो(LIMA_PP_INT_RAWSTAT, LIMA_PP_IRQ_MASK_ALL);
	pp_ग_लिखो(LIMA_PP_CTRL, LIMA_PP_CTRL_SOFT_RESET);
	ip->data.async_reset = true;
पूर्ण

अटल पूर्णांक lima_pp_soft_reset_poll(काष्ठा lima_ip *ip)
अणु
	वापस !(pp_पढ़ो(LIMA_PP_STATUS) & LIMA_PP_STATUS_RENDERING_ACTIVE) &&
		pp_पढ़ो(LIMA_PP_INT_RAWSTAT) == LIMA_PP_IRQ_RESET_COMPLETED;
पूर्ण

अटल पूर्णांक lima_pp_soft_reset_async_रुको_one(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक ret;

	ret = lima_poll_समयout(ip, lima_pp_soft_reset_poll, 0, 100);
	अगर (ret) अणु
		dev_err(dev->dev, "pp %s reset time out\n", lima_ip_name(ip));
		वापस ret;
	पूर्ण

	pp_ग_लिखो(LIMA_PP_INT_CLEAR, LIMA_PP_IRQ_MASK_ALL);
	pp_ग_लिखो(LIMA_PP_INT_MASK, LIMA_PP_IRQ_MASK_USED);
	वापस 0;
पूर्ण

अटल पूर्णांक lima_pp_soft_reset_async_रुको(काष्ठा lima_ip *ip)
अणु
	पूर्णांक i, err = 0;

	अगर (!ip->data.async_reset)
		वापस 0;

	अगर (ip->id == lima_ip_pp_bcast) अणु
		काष्ठा lima_device *dev = ip->dev;
		काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
		काष्ठा drm_lima_m450_pp_frame *frame = pipe->current_task->frame;

		क्रम (i = 0; i < frame->num_pp; i++)
			err |= lima_pp_soft_reset_async_रुको_one(pipe->processor[i]);
	पूर्ण अन्यथा
		err = lima_pp_soft_reset_async_रुको_one(ip);

	ip->data.async_reset = false;
	वापस err;
पूर्ण

अटल व्योम lima_pp_ग_लिखो_frame(काष्ठा lima_ip *ip, u32 *frame, u32 *wb)
अणु
	पूर्णांक i, j, n = 0;

	क्रम (i = 0; i < LIMA_PP_FRAME_REG_NUM; i++)
		ग_लिखोl(frame[i], ip->iomem + LIMA_PP_FRAME + i * 4);

	क्रम (i = 0; i < 3; i++) अणु
		क्रम (j = 0; j < LIMA_PP_WB_REG_NUM; j++)
			ग_लिखोl(wb[n++], ip->iomem + LIMA_PP_WB(i) + j * 4);
	पूर्ण
पूर्ण

अटल पूर्णांक lima_pp_hard_reset_poll(काष्ठा lima_ip *ip)
अणु
	pp_ग_लिखो(LIMA_PP_PERF_CNT_0_LIMIT, 0xC01A0000);
	वापस pp_पढ़ो(LIMA_PP_PERF_CNT_0_LIMIT) == 0xC01A0000;
पूर्ण

अटल पूर्णांक lima_pp_hard_reset(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक ret;

	pp_ग_लिखो(LIMA_PP_PERF_CNT_0_LIMIT, 0xC0FFE000);
	pp_ग_लिखो(LIMA_PP_INT_MASK, 0);
	pp_ग_लिखो(LIMA_PP_CTRL, LIMA_PP_CTRL_FORCE_RESET);
	ret = lima_poll_समयout(ip, lima_pp_hard_reset_poll, 10, 100);
	अगर (ret) अणु
		dev_err(dev->dev, "pp hard reset timeout\n");
		वापस ret;
	पूर्ण

	pp_ग_लिखो(LIMA_PP_PERF_CNT_0_LIMIT, 0);
	pp_ग_लिखो(LIMA_PP_INT_CLEAR, LIMA_PP_IRQ_MASK_ALL);
	pp_ग_लिखो(LIMA_PP_INT_MASK, LIMA_PP_IRQ_MASK_USED);
	वापस 0;
पूर्ण

अटल व्योम lima_pp_prपूर्णांक_version(काष्ठा lima_ip *ip)
अणु
	u32 version, major, minor;
	अक्षर *name;

	version = pp_पढ़ो(LIMA_PP_VERSION);
	major = (version >> 8) & 0xFF;
	minor = version & 0xFF;
	चयन (version >> 16) अणु
	हाल 0xC807:
	    name = "mali200";
		अवरोध;
	हाल 0xCE07:
		name = "mali300";
		अवरोध;
	हाल 0xCD07:
		name = "mali400";
		अवरोध;
	हाल 0xCF07:
		name = "mali450";
		अवरोध;
	शेष:
		name = "unknown";
		अवरोध;
	पूर्ण
	dev_info(ip->dev->dev, "%s - %s version major %d minor %d\n",
		 lima_ip_name(ip), name, major, minor);
पूर्ण

अटल पूर्णांक lima_pp_hw_init(काष्ठा lima_ip *ip)
अणु
	ip->data.async_reset = false;
	lima_pp_soft_reset_async(ip);
	वापस lima_pp_soft_reset_async_रुको(ip);
पूर्ण

पूर्णांक lima_pp_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_pp_hw_init(ip);
पूर्ण

व्योम lima_pp_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_pp_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;

	lima_pp_prपूर्णांक_version(ip);

	err = lima_pp_hw_init(ip);
	अगर (err)
		वापस err;

	err = devm_request_irq(dev->dev, ip->irq, lima_pp_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	अगर (err) अणु
		dev_err(dev->dev, "pp %s fail to request irq\n",
			lima_ip_name(ip));
		वापस err;
	पूर्ण

	dev->pp_version = pp_पढ़ो(LIMA_PP_VERSION);

	वापस 0;
पूर्ण

व्योम lima_pp_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_pp_bcast_resume(काष्ठा lima_ip *ip)
अणु
	/* PP has been reset by inभागidual PP resume */
	ip->data.async_reset = false;
	वापस 0;
पूर्ण

व्योम lima_pp_bcast_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_pp_bcast_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;

	err = devm_request_irq(dev->dev, ip->irq, lima_pp_bcast_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	अगर (err) अणु
		dev_err(dev->dev, "pp %s fail to request irq\n",
			lima_ip_name(ip));
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम lima_pp_bcast_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण

अटल पूर्णांक lima_pp_task_validate(काष्ठा lima_sched_pipe *pipe,
				 काष्ठा lima_sched_task *task)
अणु
	u32 num_pp;

	अगर (pipe->bcast_processor) अणु
		काष्ठा drm_lima_m450_pp_frame *f = task->frame;

		num_pp = f->num_pp;

		अगर (f->_pad)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		काष्ठा drm_lima_m400_pp_frame *f = task->frame;

		num_pp = f->num_pp;
	पूर्ण

	अगर (num_pp == 0 || num_pp > pipe->num_processor)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम lima_pp_task_run(काष्ठा lima_sched_pipe *pipe,
			     काष्ठा lima_sched_task *task)
अणु
	अगर (pipe->bcast_processor) अणु
		काष्ठा drm_lima_m450_pp_frame *frame = task->frame;
		काष्ठा lima_device *dev = pipe->bcast_processor->dev;
		काष्ठा lima_ip *ip = pipe->bcast_processor;
		पूर्णांक i;

		pipe->करोne = 0;
		atomic_set(&pipe->task, frame->num_pp);

		अगर (frame->use_dlbu) अणु
			lima_dlbu_enable(dev, frame->num_pp);

			frame->frame[LIMA_PP_FRAME >> 2] = LIMA_VA_RESERVE_DLBU;
			lima_dlbu_set_reg(dev->ip + lima_ip_dlbu, frame->dlbu_regs);
		पूर्ण अन्यथा
			lima_dlbu_disable(dev);

		lima_bcast_enable(dev, frame->num_pp);

		lima_pp_soft_reset_async_रुको(ip);

		lima_pp_ग_लिखो_frame(ip, frame->frame, frame->wb);

		क्रम (i = 0; i < frame->num_pp; i++) अणु
			काष्ठा lima_ip *ip = pipe->processor[i];

			pp_ग_लिखो(LIMA_PP_STACK, frame->fragment_stack_address[i]);
			अगर (!frame->use_dlbu)
				pp_ग_लिखो(LIMA_PP_FRAME, frame->plbu_array_address[i]);
		पूर्ण

		pp_ग_लिखो(LIMA_PP_CTRL, LIMA_PP_CTRL_START_RENDERING);
	पूर्ण अन्यथा अणु
		काष्ठा drm_lima_m400_pp_frame *frame = task->frame;
		पूर्णांक i;

		atomic_set(&pipe->task, frame->num_pp);

		क्रम (i = 0; i < frame->num_pp; i++) अणु
			काष्ठा lima_ip *ip = pipe->processor[i];

			frame->frame[LIMA_PP_FRAME >> 2] =
				frame->plbu_array_address[i];
			frame->frame[LIMA_PP_STACK >> 2] =
				frame->fragment_stack_address[i];

			lima_pp_soft_reset_async_रुको(ip);

			lima_pp_ग_लिखो_frame(ip, frame->frame, frame->wb);

			pp_ग_लिखो(LIMA_PP_CTRL, LIMA_PP_CTRL_START_RENDERING);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम lima_pp_task_fini(काष्ठा lima_sched_pipe *pipe)
अणु
	अगर (pipe->bcast_processor)
		lima_pp_soft_reset_async(pipe->bcast_processor);
	अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < pipe->num_processor; i++)
			lima_pp_soft_reset_async(pipe->processor[i]);
	पूर्ण
पूर्ण

अटल व्योम lima_pp_task_error(काष्ठा lima_sched_pipe *pipe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pipe->num_processor; i++) अणु
		काष्ठा lima_ip *ip = pipe->processor[i];

		dev_err(ip->dev->dev, "pp task error %d int_state=%x status=%x\n",
			i, pp_पढ़ो(LIMA_PP_INT_STATUS), pp_पढ़ो(LIMA_PP_STATUS));

		lima_pp_hard_reset(ip);
	पूर्ण
पूर्ण

अटल व्योम lima_pp_task_mmu_error(काष्ठा lima_sched_pipe *pipe)
अणु
	अगर (atomic_dec_and_test(&pipe->task))
		lima_sched_pipe_task_करोne(pipe);
पूर्ण

अटल काष्ठा kmem_cache *lima_pp_task_slab;
अटल पूर्णांक lima_pp_task_slab_refcnt;

पूर्णांक lima_pp_pipe_init(काष्ठा lima_device *dev)
अणु
	पूर्णांक frame_size;
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;

	अगर (dev->id == lima_gpu_mali400)
		frame_size = माप(काष्ठा drm_lima_m400_pp_frame);
	अन्यथा
		frame_size = माप(काष्ठा drm_lima_m450_pp_frame);

	अगर (!lima_pp_task_slab) अणु
		lima_pp_task_slab = kmem_cache_create_usercopy(
			"lima_pp_task", माप(काष्ठा lima_sched_task) + frame_size,
			0, SLAB_HWCACHE_ALIGN, माप(काष्ठा lima_sched_task),
			frame_size, शून्य);
		अगर (!lima_pp_task_slab)
			वापस -ENOMEM;
	पूर्ण
	lima_pp_task_slab_refcnt++;

	pipe->frame_size = frame_size;
	pipe->task_slab = lima_pp_task_slab;

	pipe->task_validate = lima_pp_task_validate;
	pipe->task_run = lima_pp_task_run;
	pipe->task_fini = lima_pp_task_fini;
	pipe->task_error = lima_pp_task_error;
	pipe->task_mmu_error = lima_pp_task_mmu_error;

	वापस 0;
पूर्ण

व्योम lima_pp_pipe_fini(काष्ठा lima_device *dev)
अणु
	अगर (!--lima_pp_task_slab_refcnt) अणु
		kmem_cache_destroy(lima_pp_task_slab);
		lima_pp_task_slab = शून्य;
	पूर्ण
पूर्ण
