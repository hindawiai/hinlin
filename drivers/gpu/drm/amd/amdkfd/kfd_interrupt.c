<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * KFD Interrupts.
 *
 * AMD GPUs deliver पूर्णांकerrupts by pushing an पूर्णांकerrupt description onto the
 * पूर्णांकerrupt ring and then sending an पूर्णांकerrupt. KGD receives the पूर्णांकerrupt
 * in ISR and sends us a poपूर्णांकer to each new entry on the पूर्णांकerrupt ring.
 *
 * We generally can't process पूर्णांकerrupt-संकेतed events from ISR, so we call
 * out to each पूर्णांकerrupt client module (currently only the scheduler) to ask अगर
 * each पूर्णांकerrupt is पूर्णांकeresting. If they वापस true, then it requires further
 * processing so we copy it to an पूर्णांकernal पूर्णांकerrupt ring and call each
 * पूर्णांकerrupt client again from a work-queue.
 *
 * There's no acknowledgment क्रम the पूर्णांकerrupts we use. The hardware simply
 * queues a new पूर्णांकerrupt each समय without रुकोing.
 *
 * The fixed-size पूर्णांकernal queue means that it's possible क्रम us to lose
 * पूर्णांकerrupts because we have no back-pressure to the hardware.
 */

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/kfअगरo.h>
#समावेश "kfd_priv.h"

#घोषणा KFD_IH_NUM_ENTRIES 8192

अटल व्योम पूर्णांकerrupt_wq(काष्ठा work_काष्ठा *);

पूर्णांक kfd_पूर्णांकerrupt_init(काष्ठा kfd_dev *kfd)
अणु
	पूर्णांक r;

	r = kfअगरo_alloc(&kfd->ih_fअगरo,
		KFD_IH_NUM_ENTRIES * kfd->device_info->ih_ring_entry_size,
		GFP_KERNEL);
	अगर (r) अणु
		dev_err(kfd_अक्षरdev(), "Failed to allocate IH fifo\n");
		वापस r;
	पूर्ण

	kfd->ih_wq = alloc_workqueue("KFD IH", WQ_HIGHPRI, 1);
	अगर (unlikely(!kfd->ih_wq)) अणु
		kfअगरo_मुक्त(&kfd->ih_fअगरo);
		dev_err(kfd_अक्षरdev(), "Failed to allocate KFD IH workqueue\n");
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&kfd->पूर्णांकerrupt_lock);

	INIT_WORK(&kfd->पूर्णांकerrupt_work, पूर्णांकerrupt_wq);

	kfd->पूर्णांकerrupts_active = true;

	/*
	 * After this function वापसs, the पूर्णांकerrupt will be enabled. This
	 * barrier ensures that the पूर्णांकerrupt running on a dअगरferent processor
	 * sees all the above ग_लिखोs.
	 */
	smp_wmb();

	वापस 0;
पूर्ण

व्योम kfd_पूर्णांकerrupt_निकास(काष्ठा kfd_dev *kfd)
अणु
	/*
	 * Stop the पूर्णांकerrupt handler from writing to the ring and scheduling
	 * workqueue items. The spinlock ensures that any पूर्णांकerrupt running
	 * after we have unlocked sees पूर्णांकerrupts_active = false.
	 */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kfd->पूर्णांकerrupt_lock, flags);
	kfd->पूर्णांकerrupts_active = false;
	spin_unlock_irqrestore(&kfd->पूर्णांकerrupt_lock, flags);

	/*
	 * flush_work ensures that there are no outstanding
	 * work-queue items that will access पूर्णांकerrupt_ring. New work items
	 * can't be created because we stopped पूर्णांकerrupt handling above.
	 */
	flush_workqueue(kfd->ih_wq);

	kfअगरo_मुक्त(&kfd->ih_fअगरo);
पूर्ण

/*
 * Assumption: single पढ़ोer/ग_लिखोr. This function is not re-entrant
 */
bool enqueue_ih_ring_entry(काष्ठा kfd_dev *kfd,	स्थिर व्योम *ih_ring_entry)
अणु
	पूर्णांक count;

	count = kfअगरo_in(&kfd->ih_fअगरo, ih_ring_entry,
				kfd->device_info->ih_ring_entry_size);
	अगर (count != kfd->device_info->ih_ring_entry_size) अणु
		dev_err_ratelimited(kfd_अक्षरdev(),
			"Interrupt ring overflow, dropping interrupt %d\n",
			count);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Assumption: single पढ़ोer/ग_लिखोr. This function is not re-entrant
 */
अटल bool dequeue_ih_ring_entry(काष्ठा kfd_dev *kfd, व्योम *ih_ring_entry)
अणु
	पूर्णांक count;

	count = kfअगरo_out(&kfd->ih_fअगरo, ih_ring_entry,
				kfd->device_info->ih_ring_entry_size);

	WARN_ON(count && count != kfd->device_info->ih_ring_entry_size);

	वापस count == kfd->device_info->ih_ring_entry_size;
पूर्ण

अटल व्योम पूर्णांकerrupt_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kfd_dev *dev = container_of(work, काष्ठा kfd_dev,
						पूर्णांकerrupt_work);
	uपूर्णांक32_t ih_ring_entry[KFD_MAX_RING_ENTRY_SIZE];

	अगर (dev->device_info->ih_ring_entry_size > माप(ih_ring_entry)) अणु
		dev_err_once(kfd_अक्षरdev(), "Ring entry too small\n");
		वापस;
	पूर्ण

	जबतक (dequeue_ih_ring_entry(dev, ih_ring_entry))
		dev->device_info->event_पूर्णांकerrupt_class->पूर्णांकerrupt_wq(dev,
								ih_ring_entry);
पूर्ण

bool पूर्णांकerrupt_is_wanted(काष्ठा kfd_dev *dev,
			स्थिर uपूर्णांक32_t *ih_ring_entry,
			uपूर्णांक32_t *patched_ihre, bool *flag)
अणु
	/* पूर्णांकeger and bitwise OR so there is no boolean लघु-circuiting */
	अचिन्हित पूर्णांक wanted = 0;

	wanted |= dev->device_info->event_पूर्णांकerrupt_class->पूर्णांकerrupt_isr(dev,
					 ih_ring_entry, patched_ihre, flag);

	वापस wanted != 0;
पूर्ण
