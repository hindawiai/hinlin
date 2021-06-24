<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <drm/lima_drm.h>

#समावेश "lima_device.h"
#समावेश "lima_gp.h"
#समावेश "lima_regs.h"
#समावेश "lima_gem.h"
#समावेश "lima_vm.h"

#घोषणा gp_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा gp_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

अटल irqवापस_t lima_gp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lima_ip *ip = data;
	काष्ठा lima_device *dev = ip->dev;
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;
	काष्ठा lima_sched_task *task = pipe->current_task;
	u32 state = gp_पढ़ो(LIMA_GP_INT_STAT);
	u32 status = gp_पढ़ो(LIMA_GP_STATUS);
	bool करोne = false;

	/* क्रम shared irq हाल */
	अगर (!state)
		वापस IRQ_NONE;

	अगर (state & LIMA_GP_IRQ_MASK_ERROR) अणु
		अगर ((state & LIMA_GP_IRQ_MASK_ERROR) ==
		    LIMA_GP_IRQ_PLBU_OUT_OF_MEM) अणु
			dev_dbg(dev->dev, "gp out of heap irq status=%x\n",
				status);
		पूर्ण अन्यथा अणु
			dev_err(dev->dev, "gp error irq state=%x status=%x\n",
				state, status);
			अगर (task)
				task->recoverable = false;
		पूर्ण

		/* mask all पूर्णांकerrupts beक्रमe hard reset */
		gp_ग_लिखो(LIMA_GP_INT_MASK, 0);

		pipe->error = true;
		करोne = true;
	पूर्ण अन्यथा अणु
		bool valid = state & (LIMA_GP_IRQ_VS_END_CMD_LST |
				      LIMA_GP_IRQ_PLBU_END_CMD_LST);
		bool active = status & (LIMA_GP_STATUS_VS_ACTIVE |
					LIMA_GP_STATUS_PLBU_ACTIVE);
		करोne = valid && !active;
		pipe->error = false;
	पूर्ण

	gp_ग_लिखो(LIMA_GP_INT_CLEAR, state);

	अगर (करोne)
		lima_sched_pipe_task_करोne(pipe);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lima_gp_soft_reset_async(काष्ठा lima_ip *ip)
अणु
	अगर (ip->data.async_reset)
		वापस;

	gp_ग_लिखो(LIMA_GP_INT_MASK, 0);
	gp_ग_लिखो(LIMA_GP_INT_CLEAR, LIMA_GP_IRQ_RESET_COMPLETED);
	gp_ग_लिखो(LIMA_GP_CMD, LIMA_GP_CMD_SOFT_RESET);
	ip->data.async_reset = true;
पूर्ण

अटल पूर्णांक lima_gp_soft_reset_async_रुको(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;
	u32 v;

	अगर (!ip->data.async_reset)
		वापस 0;

	err = पढ़ोl_poll_समयout(ip->iomem + LIMA_GP_INT_RAWSTAT, v,
				 v & LIMA_GP_IRQ_RESET_COMPLETED,
				 0, 100);
	अगर (err) अणु
		dev_err(dev->dev, "gp soft reset time out\n");
		वापस err;
	पूर्ण

	gp_ग_लिखो(LIMA_GP_INT_CLEAR, LIMA_GP_IRQ_MASK_ALL);
	gp_ग_लिखो(LIMA_GP_INT_MASK, LIMA_GP_IRQ_MASK_USED);

	ip->data.async_reset = false;
	वापस 0;
पूर्ण

अटल पूर्णांक lima_gp_task_validate(काष्ठा lima_sched_pipe *pipe,
				 काष्ठा lima_sched_task *task)
अणु
	काष्ठा drm_lima_gp_frame *frame = task->frame;
	u32 *f = frame->frame;
	(व्योम)pipe;

	अगर (f[LIMA_GP_VSCL_START_ADDR >> 2] >
	    f[LIMA_GP_VSCL_END_ADDR >> 2] ||
	    f[LIMA_GP_PLBUCL_START_ADDR >> 2] >
	    f[LIMA_GP_PLBUCL_END_ADDR >> 2] ||
	    f[LIMA_GP_PLBU_ALLOC_START_ADDR >> 2] >
	    f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2])
		वापस -EINVAL;

	अगर (f[LIMA_GP_VSCL_START_ADDR >> 2] ==
	    f[LIMA_GP_VSCL_END_ADDR >> 2] &&
	    f[LIMA_GP_PLBUCL_START_ADDR >> 2] ==
	    f[LIMA_GP_PLBUCL_END_ADDR >> 2])
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम lima_gp_task_run(काष्ठा lima_sched_pipe *pipe,
			     काष्ठा lima_sched_task *task)
अणु
	काष्ठा lima_ip *ip = pipe->processor[0];
	काष्ठा drm_lima_gp_frame *frame = task->frame;
	u32 *f = frame->frame;
	u32 cmd = 0;
	पूर्णांक i;

	/* update real heap buffer size क्रम GP */
	क्रम (i = 0; i < task->num_bos; i++) अणु
		काष्ठा lima_bo *bo = task->bos[i];

		अगर (bo->heap_size &&
		    lima_vm_get_va(task->vm, bo) ==
		    f[LIMA_GP_PLBU_ALLOC_START_ADDR >> 2]) अणु
			f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2] =
				f[LIMA_GP_PLBU_ALLOC_START_ADDR >> 2] +
				bo->heap_size;
			task->recoverable = true;
			task->heap = bo;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (f[LIMA_GP_VSCL_START_ADDR >> 2] !=
	    f[LIMA_GP_VSCL_END_ADDR >> 2])
		cmd |= LIMA_GP_CMD_START_VS;
	अगर (f[LIMA_GP_PLBUCL_START_ADDR >> 2] !=
	    f[LIMA_GP_PLBUCL_END_ADDR >> 2])
		cmd |= LIMA_GP_CMD_START_PLBU;

	/* beक्रमe any hw ops, रुको last success task async soft reset */
	lima_gp_soft_reset_async_रुको(ip);

	क्रम (i = 0; i < LIMA_GP_FRAME_REG_NUM; i++)
		ग_लिखोl(f[i], ip->iomem + LIMA_GP_VSCL_START_ADDR + i * 4);

	gp_ग_लिखो(LIMA_GP_CMD, LIMA_GP_CMD_UPDATE_PLBU_ALLOC);
	gp_ग_लिखो(LIMA_GP_CMD, cmd);
पूर्ण

अटल पूर्णांक lima_gp_hard_reset_poll(काष्ठा lima_ip *ip)
अणु
	gp_ग_लिखो(LIMA_GP_PERF_CNT_0_LIMIT, 0xC01A0000);
	वापस gp_पढ़ो(LIMA_GP_PERF_CNT_0_LIMIT) == 0xC01A0000;
पूर्ण

अटल पूर्णांक lima_gp_hard_reset(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक ret;

	gp_ग_लिखो(LIMA_GP_PERF_CNT_0_LIMIT, 0xC0FFE000);
	gp_ग_लिखो(LIMA_GP_INT_MASK, 0);
	gp_ग_लिखो(LIMA_GP_CMD, LIMA_GP_CMD_RESET);
	ret = lima_poll_समयout(ip, lima_gp_hard_reset_poll, 10, 100);
	अगर (ret) अणु
		dev_err(dev->dev, "gp hard reset timeout\n");
		वापस ret;
	पूर्ण

	gp_ग_लिखो(LIMA_GP_PERF_CNT_0_LIMIT, 0);
	gp_ग_लिखो(LIMA_GP_INT_CLEAR, LIMA_GP_IRQ_MASK_ALL);
	gp_ग_लिखो(LIMA_GP_INT_MASK, LIMA_GP_IRQ_MASK_USED);
	वापस 0;
पूर्ण

अटल व्योम lima_gp_task_fini(काष्ठा lima_sched_pipe *pipe)
अणु
	lima_gp_soft_reset_async(pipe->processor[0]);
पूर्ण

अटल व्योम lima_gp_task_error(काष्ठा lima_sched_pipe *pipe)
अणु
	काष्ठा lima_ip *ip = pipe->processor[0];

	dev_err(ip->dev->dev, "gp task error int_state=%x status=%x\n",
		gp_पढ़ो(LIMA_GP_INT_STAT), gp_पढ़ो(LIMA_GP_STATUS));

	lima_gp_hard_reset(ip);
पूर्ण

अटल व्योम lima_gp_task_mmu_error(काष्ठा lima_sched_pipe *pipe)
अणु
	lima_sched_pipe_task_करोne(pipe);
पूर्ण

अटल पूर्णांक lima_gp_task_recover(काष्ठा lima_sched_pipe *pipe)
अणु
	काष्ठा lima_ip *ip = pipe->processor[0];
	काष्ठा lima_sched_task *task = pipe->current_task;
	काष्ठा drm_lima_gp_frame *frame = task->frame;
	u32 *f = frame->frame;
	माप_प्रकार fail_size =
		f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2] -
		f[LIMA_GP_PLBU_ALLOC_START_ADDR >> 2];

	अगर (fail_size == task->heap->heap_size) अणु
		पूर्णांक ret;

		ret = lima_heap_alloc(task->heap, task->vm);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	gp_ग_लिखो(LIMA_GP_INT_MASK, LIMA_GP_IRQ_MASK_USED);
	/* Resume from where we stopped, i.e. new start is old end */
	gp_ग_लिखो(LIMA_GP_PLBU_ALLOC_START_ADDR,
		 f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2]);
	f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2] =
		f[LIMA_GP_PLBU_ALLOC_START_ADDR >> 2] + task->heap->heap_size;
	gp_ग_लिखो(LIMA_GP_PLBU_ALLOC_END_ADDR,
		 f[LIMA_GP_PLBU_ALLOC_END_ADDR >> 2]);
	gp_ग_लिखो(LIMA_GP_CMD, LIMA_GP_CMD_UPDATE_PLBU_ALLOC);
	वापस 0;
पूर्ण

अटल व्योम lima_gp_prपूर्णांक_version(काष्ठा lima_ip *ip)
अणु
	u32 version, major, minor;
	अक्षर *name;

	version = gp_पढ़ो(LIMA_GP_VERSION);
	major = (version >> 8) & 0xFF;
	minor = version & 0xFF;
	चयन (version >> 16) अणु
	हाल 0xA07:
	    name = "mali200";
		अवरोध;
	हाल 0xC07:
		name = "mali300";
		अवरोध;
	हाल 0xB07:
		name = "mali400";
		अवरोध;
	हाल 0xD07:
		name = "mali450";
		अवरोध;
	शेष:
		name = "unknown";
		अवरोध;
	पूर्ण
	dev_info(ip->dev->dev, "%s - %s version major %d minor %d\n",
		 lima_ip_name(ip), name, major, minor);
पूर्ण

अटल काष्ठा kmem_cache *lima_gp_task_slab;
अटल पूर्णांक lima_gp_task_slab_refcnt;

अटल पूर्णांक lima_gp_hw_init(काष्ठा lima_ip *ip)
अणु
	ip->data.async_reset = false;
	lima_gp_soft_reset_async(ip);
	वापस lima_gp_soft_reset_async_रुको(ip);
पूर्ण

पूर्णांक lima_gp_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_gp_hw_init(ip);
पूर्ण

व्योम lima_gp_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_gp_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;

	lima_gp_prपूर्णांक_version(ip);

	err = lima_gp_hw_init(ip);
	अगर (err)
		वापस err;

	err = devm_request_irq(dev->dev, ip->irq, lima_gp_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	अगर (err) अणु
		dev_err(dev->dev, "gp %s fail to request irq\n",
			lima_ip_name(ip));
		वापस err;
	पूर्ण

	dev->gp_version = gp_पढ़ो(LIMA_GP_VERSION);

	वापस 0;
पूर्ण

व्योम lima_gp_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_gp_pipe_init(काष्ठा lima_device *dev)
अणु
	पूर्णांक frame_size = माप(काष्ठा drm_lima_gp_frame);
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;

	अगर (!lima_gp_task_slab) अणु
		lima_gp_task_slab = kmem_cache_create_usercopy(
			"lima_gp_task", माप(काष्ठा lima_sched_task) + frame_size,
			0, SLAB_HWCACHE_ALIGN, माप(काष्ठा lima_sched_task),
			frame_size, शून्य);
		अगर (!lima_gp_task_slab)
			वापस -ENOMEM;
	पूर्ण
	lima_gp_task_slab_refcnt++;

	pipe->frame_size = frame_size;
	pipe->task_slab = lima_gp_task_slab;

	pipe->task_validate = lima_gp_task_validate;
	pipe->task_run = lima_gp_task_run;
	pipe->task_fini = lima_gp_task_fini;
	pipe->task_error = lima_gp_task_error;
	pipe->task_mmu_error = lima_gp_task_mmu_error;
	pipe->task_recover = lima_gp_task_recover;

	वापस 0;
पूर्ण

व्योम lima_gp_pipe_fini(काष्ठा lima_device *dev)
अणु
	अगर (!--lima_gp_task_slab_refcnt) अणु
		kmem_cache_destroy(lima_gp_task_slab);
		lima_gp_task_slab = शून्य;
	पूर्ण
पूर्ण
