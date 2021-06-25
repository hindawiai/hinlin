<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2016 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/coresight.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>
#समावेश "coresight-priv.h"
#समावेश "coresight-tmc.h"
#समावेश "coresight-etm-perf.h"

अटल पूर्णांक पंचांगc_set_etf_buffer(काष्ठा coresight_device *csdev,
			      काष्ठा perf_output_handle *handle);

अटल व्योम __पंचांगc_etb_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	/* Wait क्रम TMCSReady bit to be set */
	पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(drvdata);

	ग_लिखोl_relaxed(TMC_MODE_CIRCULAR_BUFFER, drvdata->base + TMC_MODE);
	ग_लिखोl_relaxed(TMC_FFCR_EN_FMT | TMC_FFCR_EN_TI |
		       TMC_FFCR_FON_FLIN | TMC_FFCR_FON_TRIG_EVT |
		       TMC_FFCR_TRIGON_TRIGIN,
		       drvdata->base + TMC_FFCR);

	ग_लिखोl_relaxed(drvdata->trigger_cntr, drvdata->base + TMC_TRG);
	पंचांगc_enable_hw(drvdata);

	CS_LOCK(drvdata->base);
पूर्ण

अटल पूर्णांक पंचांगc_etb_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक rc = coresight_claim_device(drvdata->csdev);

	अगर (rc)
		वापस rc;

	__पंचांगc_etb_enable_hw(drvdata);
	वापस 0;
पूर्ण

अटल व्योम पंचांगc_etb_dump_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	अक्षर *bufp;
	u32 पढ़ो_data, lost;

	/* Check अगर the buffer wrapped around. */
	lost = पढ़ोl_relaxed(drvdata->base + TMC_STS) & TMC_STS_FULL;
	bufp = drvdata->buf;
	drvdata->len = 0;
	जबतक (1) अणु
		पढ़ो_data = पढ़ोl_relaxed(drvdata->base + TMC_RRD);
		अगर (पढ़ो_data == 0xFFFFFFFF)
			अवरोध;
		स_नकल(bufp, &पढ़ो_data, 4);
		bufp += 4;
		drvdata->len += 4;
	पूर्ण

	अगर (lost)
		coresight_insert_barrier_packet(drvdata->buf);
	वापस;
पूर्ण

अटल व्योम __पंचांगc_etb_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	पंचांगc_flush_and_stop(drvdata);
	/*
	 * When operating in sysFS mode the content of the buffer needs to be
	 * पढ़ो beक्रमe the TMC is disabled.
	 */
	अगर (drvdata->mode == CS_MODE_SYSFS)
		पंचांगc_etb_dump_hw(drvdata);
	पंचांगc_disable_hw(drvdata);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम पंचांगc_etb_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	__पंचांगc_etb_disable_hw(drvdata);
	coresight_disclaim_device(drvdata->csdev);
पूर्ण

अटल व्योम __पंचांगc_etf_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	/* Wait क्रम TMCSReady bit to be set */
	पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(drvdata);

	ग_लिखोl_relaxed(TMC_MODE_HARDWARE_FIFO, drvdata->base + TMC_MODE);
	ग_लिखोl_relaxed(TMC_FFCR_EN_FMT | TMC_FFCR_EN_TI,
		       drvdata->base + TMC_FFCR);
	ग_लिखोl_relaxed(0x0, drvdata->base + TMC_BUFWM);
	पंचांगc_enable_hw(drvdata);

	CS_LOCK(drvdata->base);
पूर्ण

अटल पूर्णांक पंचांगc_etf_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक rc = coresight_claim_device(drvdata->csdev);

	अगर (rc)
		वापस rc;

	__पंचांगc_etf_enable_hw(drvdata);
	वापस 0;
पूर्ण

अटल व्योम पंचांगc_etf_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	पंचांगc_flush_and_stop(drvdata);
	पंचांगc_disable_hw(drvdata);
	coresight_disclaim_device_unlocked(csdev);
	CS_LOCK(drvdata->base);
पूर्ण

/*
 * Return the available trace data in the buffer from @pos, with
 * a maximum limit of @len, updating the @bufpp on where to
 * find it.
 */
sमाप_प्रकार पंचांगc_etb_get_sysfs_trace(काष्ठा पंचांगc_drvdata *drvdata,
				loff_t pos, माप_प्रकार len, अक्षर **bufpp)
अणु
	sमाप_प्रकार actual = len;

	/* Adjust the len to available size @pos */
	अगर (pos + actual > drvdata->len)
		actual = drvdata->len - pos;
	अगर (actual > 0)
		*bufpp = drvdata->buf + pos;
	वापस actual;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etf_sink_sysfs(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret = 0;
	bool used = false;
	अक्षर *buf = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * If we करोn't have a buffer release the lock and allocate memory.
	 * Otherwise keep the lock and move aदीर्घ.
	 */
	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (!drvdata->buf) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);

		/* Allocating the memory here जबतक outside of the spinlock */
		buf = kzalloc(drvdata->size, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		/* Let's try again */
		spin_lock_irqsave(&drvdata->spinlock, flags);
	पूर्ण

	अगर (drvdata->पढ़ोing) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * In sysFS mode we can have multiple ग_लिखोrs per sink.  Since this
	 * sink is alपढ़ोy enabled no memory is needed and the HW need not be
	 * touched.
	 */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		atomic_inc(csdev->refcnt);
		जाओ out;
	पूर्ण

	/*
	 * If drvdata::buf isn't शून्य, memory was allocated क्रम a previous
	 * trace run but wasn't पढ़ो.  If so simply zero-out the memory.
	 * Otherwise use the memory allocated above.
	 *
	 * The memory is मुक्तd when users पढ़ो the buffer using the
	 * /dev/xyz.अणुetf|etbपूर्ण पूर्णांकerface.  See पंचांगc_पढ़ो_unprepare_etf() क्रम
	 * details.
	 */
	अगर (drvdata->buf) अणु
		स_रखो(drvdata->buf, 0, drvdata->size);
	पूर्ण अन्यथा अणु
		used = true;
		drvdata->buf = buf;
	पूर्ण

	ret = पंचांगc_etb_enable_hw(drvdata);
	अगर (!ret) अणु
		drvdata->mode = CS_MODE_SYSFS;
		atomic_inc(csdev->refcnt);
	पूर्ण अन्यथा अणु
		/* Free up the buffer अगर we failed to enable */
		used = false;
	पूर्ण
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free memory outside the spinlock अगर need be */
	अगर (!used)
		kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etf_sink_perf(काष्ठा coresight_device *csdev, व्योम *data)
अणु
	पूर्णांक ret = 0;
	pid_t pid;
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा perf_output_handle *handle = data;
	काष्ठा cs_buffers *buf = eपंचांग_perf_sink_config(handle);

	spin_lock_irqsave(&drvdata->spinlock, flags);
	करो अणु
		ret = -EINVAL;
		अगर (drvdata->पढ़ोing)
			अवरोध;
		/*
		 * No need to जारी अगर the ETB/ETF is alपढ़ोy operated
		 * from sysFS.
		 */
		अगर (drvdata->mode == CS_MODE_SYSFS) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		/* Get a handle on the pid of the process to monitor */
		pid = buf->pid;

		अगर (drvdata->pid != -1 && drvdata->pid != pid) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		ret = पंचांगc_set_etf_buffer(csdev, handle);
		अगर (ret)
			अवरोध;

		/*
		 * No HW configuration is needed अगर the sink is alपढ़ोy in
		 * use क्रम this session.
		 */
		अगर (drvdata->pid == pid) अणु
			atomic_inc(csdev->refcnt);
			अवरोध;
		पूर्ण

		ret  = पंचांगc_etb_enable_hw(drvdata);
		अगर (!ret) अणु
			/* Associate with monitored process. */
			drvdata->pid = pid;
			drvdata->mode = CS_MODE_PERF;
			atomic_inc(csdev->refcnt);
		पूर्ण
	पूर्ण जबतक (0);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etf_sink(काष्ठा coresight_device *csdev,
			       u32 mode, व्योम *data)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल CS_MODE_SYSFS:
		ret = पंचांगc_enable_etf_sink_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		ret = पंचांगc_enable_etf_sink_perf(csdev, data);
		अवरोध;
	/* We shouldn't be here */
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	dev_dbg(&csdev->dev, "TMC-ETB/ETF enabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगc_disable_etf_sink(काष्ठा coresight_device *csdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	अगर (drvdata->पढ़ोing) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (atomic_dec_वापस(csdev->refcnt)) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	/* Complain अगर we (somehow) got out of sync */
	WARN_ON_ONCE(drvdata->mode == CS_MODE_DISABLED);
	पंचांगc_etb_disable_hw(drvdata);
	/* Dissociate from monitored process. */
	drvdata->pid = -1;
	drvdata->mode = CS_MODE_DISABLED;

	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&csdev->dev, "TMC-ETB/ETF disabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etf_link(काष्ठा coresight_device *csdev,
			       पूर्णांक inport, पूर्णांक outport)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	bool first_enable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (drvdata->पढ़ोing) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (atomic_पढ़ो(&csdev->refcnt[0]) == 0) अणु
		ret = पंचांगc_etf_enable_hw(drvdata);
		अगर (!ret) अणु
			drvdata->mode = CS_MODE_SYSFS;
			first_enable = true;
		पूर्ण
	पूर्ण
	अगर (!ret)
		atomic_inc(&csdev->refcnt[0]);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (first_enable)
		dev_dbg(&csdev->dev, "TMC-ETF enabled\n");
	वापस ret;
पूर्ण

अटल व्योम पंचांगc_disable_etf_link(काष्ठा coresight_device *csdev,
				 पूर्णांक inport, पूर्णांक outport)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	bool last_disable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (drvdata->पढ़ोing) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस;
	पूर्ण

	अगर (atomic_dec_वापस(&csdev->refcnt[0]) == 0) अणु
		पंचांगc_etf_disable_hw(drvdata);
		drvdata->mode = CS_MODE_DISABLED;
		last_disable = true;
	पूर्ण
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (last_disable)
		dev_dbg(&csdev->dev, "TMC-ETF disabled\n");
पूर्ण

अटल व्योम *पंचांगc_alloc_etf_buffer(काष्ठा coresight_device *csdev,
				  काष्ठा perf_event *event, व्योम **pages,
				  पूर्णांक nr_pages, bool overग_लिखो)
अणु
	पूर्णांक node;
	काष्ठा cs_buffers *buf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	/* Allocate memory काष्ठाure क्रम पूर्णांकeraction with Perf */
	buf = kzalloc_node(माप(काष्ठा cs_buffers), GFP_KERNEL, node);
	अगर (!buf)
		वापस शून्य;

	buf->pid = task_pid_nr(event->owner);
	buf->snapshot = overग_लिखो;
	buf->nr_pages = nr_pages;
	buf->data_pages = pages;

	वापस buf;
पूर्ण

अटल व्योम पंचांगc_मुक्त_etf_buffer(व्योम *config)
अणु
	काष्ठा cs_buffers *buf = config;

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक पंचांगc_set_etf_buffer(काष्ठा coresight_device *csdev,
			      काष्ठा perf_output_handle *handle)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ head;
	काष्ठा cs_buffers *buf = eपंचांग_perf_sink_config(handle);

	अगर (!buf)
		वापस -EINVAL;

	/* wrap head around to the amount of space we have */
	head = handle->head & ((buf->nr_pages << PAGE_SHIFT) - 1);

	/* find the page to ग_लिखो to */
	buf->cur = head / PAGE_SIZE;

	/* and offset within that page */
	buf->offset = head % PAGE_SIZE;

	local_set(&buf->data_size, 0);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ पंचांगc_update_etf_buffer(काष्ठा coresight_device *csdev,
				  काष्ठा perf_output_handle *handle,
				  व्योम *sink_config)
अणु
	bool lost = false;
	पूर्णांक i, cur;
	स्थिर u32 *barrier;
	u32 *buf_ptr;
	u64 पढ़ो_ptr, ग_लिखो_ptr;
	u32 status;
	अचिन्हित दीर्घ offset, to_पढ़ो = 0, flags;
	काष्ठा cs_buffers *buf = sink_config;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (!buf)
		वापस 0;

	/* This shouldn't happen */
	अगर (WARN_ON_ONCE(drvdata->mode != CS_MODE_PERF))
		वापस 0;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't करो anything अगर another tracer is using this sink */
	अगर (atomic_पढ़ो(csdev->refcnt) != 1)
		जाओ out;

	CS_UNLOCK(drvdata->base);

	पंचांगc_flush_and_stop(drvdata);

	पढ़ो_ptr = पंचांगc_पढ़ो_rrp(drvdata);
	ग_लिखो_ptr = पंचांगc_पढ़ो_rwp(drvdata);

	/*
	 * Get a hold of the status रेजिस्टर and see अगर a wrap around
	 * has occurred.  If so adjust things accordingly.
	 */
	status = पढ़ोl_relaxed(drvdata->base + TMC_STS);
	अगर (status & TMC_STS_FULL) अणु
		lost = true;
		to_पढ़ो = drvdata->size;
	पूर्ण अन्यथा अणु
		to_पढ़ो = CIRC_CNT(ग_लिखो_ptr, पढ़ो_ptr, drvdata->size);
	पूर्ण

	/*
	 * The TMC RAM buffer may be bigger than the space available in the
	 * perf ring buffer (handle->size).  If so advance the RRP so that we
	 * get the latest trace data.  In snapshot mode none of that matters
	 * since we are expected to clobber stale data in favour of the latest
	 * traces.
	 */
	अगर (!buf->snapshot && to_पढ़ो > handle->size) अणु
		u32 mask = पंचांगc_get_memwidth_mask(drvdata);

		/*
		 * Make sure the new size is aligned in accordance with the
		 * requirement explained in function पंचांगc_get_memwidth_mask().
		 */
		to_पढ़ो = handle->size & mask;
		/* Move the RAM पढ़ो poपूर्णांकer up */
		पढ़ो_ptr = (ग_लिखो_ptr + drvdata->size) - to_पढ़ो;
		/* Make sure we are still within our limits */
		अगर (पढ़ो_ptr > (drvdata->size - 1))
			पढ़ो_ptr -= drvdata->size;
		/* Tell the HW */
		पंचांगc_ग_लिखो_rrp(drvdata, पढ़ो_ptr);
		lost = true;
	पूर्ण

	/*
	 * Don't set the TRUNCATED flag in snapshot mode because 1) the
	 * captured buffer is expected to be truncated and 2) a full buffer
	 * prevents the event from being re-enabled by the perf core,
	 * resulting in stale data being send to user space.
	 */
	अगर (!buf->snapshot && lost)
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);

	cur = buf->cur;
	offset = buf->offset;
	barrier = coresight_barrier_pkt;

	/* क्रम every byte to पढ़ो */
	क्रम (i = 0; i < to_पढ़ो; i += 4) अणु
		buf_ptr = buf->data_pages[cur] + offset;
		*buf_ptr = पढ़ोl_relaxed(drvdata->base + TMC_RRD);

		अगर (lost && *barrier) अणु
			*buf_ptr = *barrier;
			barrier++;
		पूर्ण

		offset += 4;
		अगर (offset >= PAGE_SIZE) अणु
			offset = 0;
			cur++;
			/* wrap around at the end of the buffer */
			cur &= buf->nr_pages - 1;
		पूर्ण
	पूर्ण

	/*
	 * In snapshot mode we simply increment the head by the number of byte
	 * that were written.  User space function  cs_eपंचांग_find_snapshot() will
	 * figure out how many bytes to get from the AUX buffer based on the
	 * position of the head.
	 */
	अगर (buf->snapshot)
		handle->head += to_पढ़ो;

	CS_LOCK(drvdata->base);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	वापस to_पढ़ो;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_sink पंचांगc_etf_sink_ops = अणु
	.enable		= पंचांगc_enable_etf_sink,
	.disable	= पंचांगc_disable_etf_sink,
	.alloc_buffer	= पंचांगc_alloc_etf_buffer,
	.मुक्त_buffer	= पंचांगc_मुक्त_etf_buffer,
	.update_buffer	= पंचांगc_update_etf_buffer,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops_link पंचांगc_etf_link_ops = अणु
	.enable		= पंचांगc_enable_etf_link,
	.disable	= पंचांगc_disable_etf_link,
पूर्ण;

स्थिर काष्ठा coresight_ops पंचांगc_etb_cs_ops = अणु
	.sink_ops	= &पंचांगc_etf_sink_ops,
पूर्ण;

स्थिर काष्ठा coresight_ops पंचांगc_etf_cs_ops = अणु
	.sink_ops	= &पंचांगc_etf_sink_ops,
	.link_ops	= &पंचांगc_etf_link_ops,
पूर्ण;

पूर्णांक पंचांगc_पढ़ो_prepare_etb(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	क्रमागत पंचांगc_mode mode;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	/* config types are set a boot समय and never change */
	अगर (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETB &&
			 drvdata->config_type != TMC_CONFIG_TYPE_ETF))
		वापस -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	अगर (drvdata->पढ़ोing) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Don't पूर्णांकerfere अगर operated from Perf */
	अगर (drvdata->mode == CS_MODE_PERF) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If drvdata::buf is शून्य the trace data has been पढ़ो alपढ़ोy */
	अगर (drvdata->buf == शून्य) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Disable the TMC अगर need be */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		/* There is no poपूर्णांक in पढ़ोing a TMC in HW FIFO mode */
		mode = पढ़ोl_relaxed(drvdata->base + TMC_MODE);
		अगर (mode != TMC_MODE_CIRCULAR_BUFFER) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		__पंचांगc_etb_disable_hw(drvdata);
	पूर्ण

	drvdata->पढ़ोing = true;
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	वापस ret;
पूर्ण

पूर्णांक पंचांगc_पढ़ो_unprepare_etb(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	अक्षर *buf = शून्य;
	क्रमागत पंचांगc_mode mode;
	अचिन्हित दीर्घ flags;

	/* config types are set a boot समय and never change */
	अगर (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETB &&
			 drvdata->config_type != TMC_CONFIG_TYPE_ETF))
		वापस -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Re-enable the TMC अगर need be */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		/* There is no poपूर्णांक in पढ़ोing a TMC in HW FIFO mode */
		mode = पढ़ोl_relaxed(drvdata->base + TMC_MODE);
		अगर (mode != TMC_MODE_CIRCULAR_BUFFER) अणु
			spin_unlock_irqrestore(&drvdata->spinlock, flags);
			वापस -EINVAL;
		पूर्ण
		/*
		 * The trace run will जारी with the same allocated trace
		 * buffer. As such zero-out the buffer so that we करोn't end
		 * up with stale data.
		 *
		 * Since the tracer is still enabled drvdata::buf
		 * can't be शून्य.
		 */
		स_रखो(drvdata->buf, 0, drvdata->size);
		__पंचांगc_etb_enable_hw(drvdata);
	पूर्ण अन्यथा अणु
		/*
		 * The ETB/ETF is not tracing and the buffer was just पढ़ो.
		 * As such prepare to मुक्त the trace buffer.
		 */
		buf = drvdata->buf;
		drvdata->buf = शून्य;
	पूर्ण

	drvdata->पढ़ोing = false;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/*
	 * Free allocated memory outside of the spinlock.  There is no need
	 * to निश्चित the validity of 'buf' since calling kमुक्त(शून्य) is safe.
	 */
	kमुक्त(buf);

	वापस 0;
पूर्ण
