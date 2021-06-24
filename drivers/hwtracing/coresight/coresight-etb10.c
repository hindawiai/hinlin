<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Embedded Trace Buffer driver
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/coresight.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/clk.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/mm.h>
#समावेश <linux/perf_event.h>


#समावेश "coresight-priv.h"
#समावेश "coresight-etm-perf.h"

#घोषणा ETB_RAM_DEPTH_REG	0x004
#घोषणा ETB_STATUS_REG		0x00c
#घोषणा ETB_RAM_READ_DATA_REG	0x010
#घोषणा ETB_RAM_READ_POINTER	0x014
#घोषणा ETB_RAM_WRITE_POINTER	0x018
#घोषणा ETB_TRG			0x01c
#घोषणा ETB_CTL_REG		0x020
#घोषणा ETB_RWD_REG		0x024
#घोषणा ETB_FFSR		0x300
#घोषणा ETB_FFCR		0x304
#घोषणा ETB_ITMISCOP0		0xee0
#घोषणा ETB_ITTRFLINACK		0xee4
#घोषणा ETB_ITTRFLIN		0xee8
#घोषणा ETB_ITATBDATA0		0xeeC
#घोषणा ETB_ITATBCTR2		0xef0
#घोषणा ETB_ITATBCTR1		0xef4
#घोषणा ETB_ITATBCTR0		0xef8

/* रेजिस्टर description */
/* STS - 0x00C */
#घोषणा ETB_STATUS_RAM_FULL	BIT(0)
/* CTL - 0x020 */
#घोषणा ETB_CTL_CAPT_EN		BIT(0)
/* FFCR - 0x304 */
#घोषणा ETB_FFCR_EN_FTC		BIT(0)
#घोषणा ETB_FFCR_FON_MAN	BIT(6)
#घोषणा ETB_FFCR_STOP_FI	BIT(12)
#घोषणा ETB_FFCR_STOP_TRIGGER	BIT(13)

#घोषणा ETB_FFCR_BIT		6
#घोषणा ETB_FFSR_BIT		1
#घोषणा ETB_FRAME_SIZE_WORDS	4

DEFINE_CORESIGHT_DEVLIST(etb_devs, "etb");

/**
 * काष्ठा etb_drvdata - specअगरics associated to an ETB component
 * @base:	memory mapped base address क्रम this component.
 * @atclk:	optional घड़ी क्रम the core parts of the ETB.
 * @csdev:	component vitals needed by the framework.
 * @miscdev:	specअगरics to handle "/dev/xyz.etb" entry.
 * @spinlock:	only one at a समय pls.
 * @पढ़ोing:	synchronise user space access to etb buffer.
 * @pid:	Process ID of the process being monitored by the session
 *		that is using this component.
 * @buf:	area of memory where ETB buffer content माला_लो sent.
 * @mode:	this ETB is being used.
 * @buffer_depth: size of @buf.
 * @trigger_cntr: amount of words to store after a trigger.
 */
काष्ठा etb_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा clk		*atclk;
	काष्ठा coresight_device	*csdev;
	काष्ठा miscdevice	miscdev;
	spinlock_t		spinlock;
	local_t			पढ़ोing;
	pid_t			pid;
	u8			*buf;
	u32			mode;
	u32			buffer_depth;
	u32			trigger_cntr;
पूर्ण;

अटल पूर्णांक etb_set_buffer(काष्ठा coresight_device *csdev,
			  काष्ठा perf_output_handle *handle);

अटल अंतरभूत अचिन्हित पूर्णांक etb_get_buffer_depth(काष्ठा etb_drvdata *drvdata)
अणु
	वापस पढ़ोl_relaxed(drvdata->base + ETB_RAM_DEPTH_REG);
पूर्ण

अटल व्योम __etb_enable_hw(काष्ठा etb_drvdata *drvdata)
अणु
	पूर्णांक i;
	u32 depth;

	CS_UNLOCK(drvdata->base);

	depth = drvdata->buffer_depth;
	/* reset ग_लिखो RAM poपूर्णांकer address */
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);
	/* clear entire RAM buffer */
	क्रम (i = 0; i < depth; i++)
		ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RWD_REG);

	/* reset ग_लिखो RAM poपूर्णांकer address */
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);
	/* reset पढ़ो RAM poपूर्णांकer address */
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_READ_POINTER);

	ग_लिखोl_relaxed(drvdata->trigger_cntr, drvdata->base + ETB_TRG);
	ग_लिखोl_relaxed(ETB_FFCR_EN_FTC | ETB_FFCR_STOP_TRIGGER,
		       drvdata->base + ETB_FFCR);
	/* ETB trace capture enable */
	ग_लिखोl_relaxed(ETB_CTL_CAPT_EN, drvdata->base + ETB_CTL_REG);

	CS_LOCK(drvdata->base);
पूर्ण

अटल पूर्णांक etb_enable_hw(काष्ठा etb_drvdata *drvdata)
अणु
	पूर्णांक rc = coresight_claim_device(drvdata->csdev);

	अगर (rc)
		वापस rc;

	__etb_enable_hw(drvdata);
	वापस 0;
पूर्ण

अटल पूर्णांक etb_enable_sysfs(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't messup with perf sessions. */
	अगर (drvdata->mode == CS_MODE_PERF) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (drvdata->mode == CS_MODE_DISABLED) अणु
		ret = etb_enable_hw(drvdata);
		अगर (ret)
			जाओ out;

		drvdata->mode = CS_MODE_SYSFS;
	पूर्ण

	atomic_inc(csdev->refcnt);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक etb_enable_perf(काष्ठा coresight_device *csdev, व्योम *data)
अणु
	पूर्णांक ret = 0;
	pid_t pid;
	अचिन्हित दीर्घ flags;
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा perf_output_handle *handle = data;
	काष्ठा cs_buffers *buf = eपंचांग_perf_sink_config(handle);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* No need to जारी अगर the component is alपढ़ोy in used by sysFS. */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Get a handle on the pid of the process to monitor */
	pid = buf->pid;

	अगर (drvdata->pid != -1 && drvdata->pid != pid) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * No HW configuration is needed अगर the sink is alपढ़ोy in
	 * use क्रम this session.
	 */
	अगर (drvdata->pid == pid) अणु
		atomic_inc(csdev->refcnt);
		जाओ out;
	पूर्ण

	/*
	 * We करोn't have an पूर्णांकernal state to clean up अगर we fail to setup
	 * the perf buffer. So we can perक्रमm the step beक्रमe we turn the
	 * ETB on and leave without cleaning up.
	 */
	ret = etb_set_buffer(csdev, handle);
	अगर (ret)
		जाओ out;

	ret = etb_enable_hw(drvdata);
	अगर (!ret) अणु
		/* Associate with monitored process. */
		drvdata->pid = pid;
		drvdata->mode = CS_MODE_PERF;
		atomic_inc(csdev->refcnt);
	पूर्ण

out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक etb_enable(काष्ठा coresight_device *csdev, u32 mode, व्योम *data)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल CS_MODE_SYSFS:
		ret = etb_enable_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		ret = etb_enable_perf(csdev, data);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	dev_dbg(&csdev->dev, "ETB enabled\n");
	वापस 0;
पूर्ण

अटल व्योम __etb_disable_hw(काष्ठा etb_drvdata *drvdata)
अणु
	u32 ffcr;
	काष्ठा device *dev = &drvdata->csdev->dev;
	काष्ठा csdev_access *csa = &drvdata->csdev->access;

	CS_UNLOCK(drvdata->base);

	ffcr = पढ़ोl_relaxed(drvdata->base + ETB_FFCR);
	/* stop क्रमmatter when a stop has completed */
	ffcr |= ETB_FFCR_STOP_FI;
	ग_लिखोl_relaxed(ffcr, drvdata->base + ETB_FFCR);
	/* manually generate a flush of the प्रणाली */
	ffcr |= ETB_FFCR_FON_MAN;
	ग_लिखोl_relaxed(ffcr, drvdata->base + ETB_FFCR);

	अगर (coresight_समयout(csa, ETB_FFCR, ETB_FFCR_BIT, 0)) अणु
		dev_err(dev,
		"timeout while waiting for completion of Manual Flush\n");
	पूर्ण

	/* disable trace capture */
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_CTL_REG);

	अगर (coresight_समयout(csa, ETB_FFSR, ETB_FFSR_BIT, 1)) अणु
		dev_err(dev,
			"timeout while waiting for Formatter to Stop\n");
	पूर्ण

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम etb_dump_hw(काष्ठा etb_drvdata *drvdata)
अणु
	bool lost = false;
	पूर्णांक i;
	u8 *buf_ptr;
	u32 पढ़ो_data, depth;
	u32 पढ़ो_ptr, ग_लिखो_ptr;
	u32 frame_off, frame_enकरोff;
	काष्ठा device *dev = &drvdata->csdev->dev;

	CS_UNLOCK(drvdata->base);

	पढ़ो_ptr = पढ़ोl_relaxed(drvdata->base + ETB_RAM_READ_POINTER);
	ग_लिखो_ptr = पढ़ोl_relaxed(drvdata->base + ETB_RAM_WRITE_POINTER);

	frame_off = ग_लिखो_ptr % ETB_FRAME_SIZE_WORDS;
	frame_enकरोff = ETB_FRAME_SIZE_WORDS - frame_off;
	अगर (frame_off) अणु
		dev_err(dev,
			"write_ptr: %lu not aligned to formatter frame size\n",
			(अचिन्हित दीर्घ)ग_लिखो_ptr);
		dev_err(dev, "frameoff: %lu, frame_endoff: %lu\n",
			(अचिन्हित दीर्घ)frame_off, (अचिन्हित दीर्घ)frame_enकरोff);
		ग_लिखो_ptr += frame_enकरोff;
	पूर्ण

	अगर ((पढ़ोl_relaxed(drvdata->base + ETB_STATUS_REG)
		      & ETB_STATUS_RAM_FULL) == 0) अणु
		ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_READ_POINTER);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(ग_लिखो_ptr, drvdata->base + ETB_RAM_READ_POINTER);
		lost = true;
	पूर्ण

	depth = drvdata->buffer_depth;
	buf_ptr = drvdata->buf;
	क्रम (i = 0; i < depth; i++) अणु
		पढ़ो_data = पढ़ोl_relaxed(drvdata->base +
					  ETB_RAM_READ_DATA_REG);
		*(u32 *)buf_ptr = पढ़ो_data;
		buf_ptr += 4;
	पूर्ण

	अगर (lost)
		coresight_insert_barrier_packet(drvdata->buf);

	अगर (frame_off) अणु
		buf_ptr -= (frame_enकरोff * 4);
		क्रम (i = 0; i < frame_enकरोff; i++) अणु
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
		पूर्ण
	पूर्ण

	ग_लिखोl_relaxed(पढ़ो_ptr, drvdata->base + ETB_RAM_READ_POINTER);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम etb_disable_hw(काष्ठा etb_drvdata *drvdata)
अणु
	__etb_disable_hw(drvdata);
	etb_dump_hw(drvdata);
	coresight_disclaim_device(drvdata->csdev);
पूर्ण

अटल पूर्णांक etb_disable(काष्ठा coresight_device *csdev)
अणु
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	अगर (atomic_dec_वापस(csdev->refcnt)) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	/* Complain अगर we (somehow) got out of sync */
	WARN_ON_ONCE(drvdata->mode == CS_MODE_DISABLED);
	etb_disable_hw(drvdata);
	/* Dissociate from monitored process. */
	drvdata->pid = -1;
	drvdata->mode = CS_MODE_DISABLED;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&csdev->dev, "ETB disabled\n");
	वापस 0;
पूर्ण

अटल व्योम *etb_alloc_buffer(काष्ठा coresight_device *csdev,
			      काष्ठा perf_event *event, व्योम **pages,
			      पूर्णांक nr_pages, bool overग_लिखो)
अणु
	पूर्णांक node;
	काष्ठा cs_buffers *buf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	buf = kzalloc_node(माप(काष्ठा cs_buffers), GFP_KERNEL, node);
	अगर (!buf)
		वापस शून्य;

	buf->pid = task_pid_nr(event->owner);
	buf->snapshot = overग_लिखो;
	buf->nr_pages = nr_pages;
	buf->data_pages = pages;

	वापस buf;
पूर्ण

अटल व्योम etb_मुक्त_buffer(व्योम *config)
अणु
	काष्ठा cs_buffers *buf = config;

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक etb_set_buffer(काष्ठा coresight_device *csdev,
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

अटल अचिन्हित दीर्घ etb_update_buffer(काष्ठा coresight_device *csdev,
			      काष्ठा perf_output_handle *handle,
			      व्योम *sink_config)
अणु
	bool lost = false;
	पूर्णांक i, cur;
	u8 *buf_ptr;
	स्थिर u32 *barrier;
	u32 पढ़ो_ptr, ग_लिखो_ptr, capacity;
	u32 status, पढ़ो_data;
	अचिन्हित दीर्घ offset, to_पढ़ो = 0, flags;
	काष्ठा cs_buffers *buf = sink_config;
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (!buf)
		वापस 0;

	capacity = drvdata->buffer_depth * ETB_FRAME_SIZE_WORDS;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't करो anything अगर another tracer is using this sink */
	अगर (atomic_पढ़ो(csdev->refcnt) != 1)
		जाओ out;

	__etb_disable_hw(drvdata);
	CS_UNLOCK(drvdata->base);

	/* unit is in words, not bytes */
	पढ़ो_ptr = पढ़ोl_relaxed(drvdata->base + ETB_RAM_READ_POINTER);
	ग_लिखो_ptr = पढ़ोl_relaxed(drvdata->base + ETB_RAM_WRITE_POINTER);

	/*
	 * Entries should be aligned to the frame size.  If they are not
	 * go back to the last alignment poपूर्णांक to give decoding tools a
	 * chance to fix things.
	 */
	अगर (ग_लिखो_ptr % ETB_FRAME_SIZE_WORDS) अणु
		dev_err(&csdev->dev,
			"write_ptr: %lu not aligned to formatter frame size\n",
			(अचिन्हित दीर्घ)ग_लिखो_ptr);

		ग_लिखो_ptr &= ~(ETB_FRAME_SIZE_WORDS - 1);
		lost = true;
	पूर्ण

	/*
	 * Get a hold of the status रेजिस्टर and see अगर a wrap around
	 * has occurred.  If so adjust things accordingly.  Otherwise
	 * start at the beginning and go until the ग_लिखो poपूर्णांकer has
	 * been reached.
	 */
	status = पढ़ोl_relaxed(drvdata->base + ETB_STATUS_REG);
	अगर (status & ETB_STATUS_RAM_FULL) अणु
		lost = true;
		to_पढ़ो = capacity;
		पढ़ो_ptr = ग_लिखो_ptr;
	पूर्ण अन्यथा अणु
		to_पढ़ो = CIRC_CNT(ग_लिखो_ptr, पढ़ो_ptr, drvdata->buffer_depth);
		to_पढ़ो *= ETB_FRAME_SIZE_WORDS;
	पूर्ण

	/*
	 * Make sure we करोn't overwrite data that hasn't been consumed yet.
	 * It is entirely possible that the HW buffer has more data than the
	 * ring buffer can currently handle.  If so adjust the start address
	 * to take only the last traces.
	 *
	 * In snapshot mode we are looking to get the latest traces only and as
	 * such, we करोn't care about not overwriting data that hasn't been
	 * processed by user space.
	 */
	अगर (!buf->snapshot && to_पढ़ो > handle->size) अणु
		u32 mask = ~(ETB_FRAME_SIZE_WORDS - 1);

		/* The new पढ़ो poपूर्णांकer must be frame size aligned */
		to_पढ़ो = handle->size & mask;
		/*
		 * Move the RAM पढ़ो poपूर्णांकer up, keeping in mind that
		 * everything is in frame size units.
		 */
		पढ़ो_ptr = (ग_लिखो_ptr + drvdata->buffer_depth) -
					to_पढ़ो / ETB_FRAME_SIZE_WORDS;
		/* Wrap around अगर need be*/
		अगर (पढ़ो_ptr > (drvdata->buffer_depth - 1))
			पढ़ो_ptr -= drvdata->buffer_depth;
		/* let the decoder know we've skipped ahead */
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

	/* finally tell HW where we want to start पढ़ोing from */
	ग_लिखोl_relaxed(पढ़ो_ptr, drvdata->base + ETB_RAM_READ_POINTER);

	cur = buf->cur;
	offset = buf->offset;
	barrier = coresight_barrier_pkt;

	क्रम (i = 0; i < to_पढ़ो; i += 4) अणु
		buf_ptr = buf->data_pages[cur] + offset;
		पढ़ो_data = पढ़ोl_relaxed(drvdata->base +
					  ETB_RAM_READ_DATA_REG);
		अगर (lost && i < CORESIGHT_BARRIER_PKT_SIZE) अणु
			पढ़ो_data = *barrier;
			barrier++;
		पूर्ण

		*(u32 *)buf_ptr = पढ़ो_data;
		buf_ptr += 4;

		offset += 4;
		अगर (offset >= PAGE_SIZE) अणु
			offset = 0;
			cur++;
			/* wrap around at the end of the buffer */
			cur &= buf->nr_pages - 1;
		पूर्ण
	पूर्ण

	/* reset ETB buffer क्रम next run */
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_READ_POINTER);
	ग_लिखोl_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);

	/*
	 * In snapshot mode we simply increment the head by the number of byte
	 * that were written.  User space function  cs_eपंचांग_find_snapshot() will
	 * figure out how many bytes to get from the AUX buffer based on the
	 * position of the head.
	 */
	अगर (buf->snapshot)
		handle->head += to_पढ़ो;

	__etb_enable_hw(drvdata);
	CS_LOCK(drvdata->base);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	वापस to_पढ़ो;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_sink etb_sink_ops = अणु
	.enable		= etb_enable,
	.disable	= etb_disable,
	.alloc_buffer	= etb_alloc_buffer,
	.मुक्त_buffer	= etb_मुक्त_buffer,
	.update_buffer	= etb_update_buffer,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops etb_cs_ops = अणु
	.sink_ops	= &etb_sink_ops,
पूर्ण;

अटल व्योम etb_dump(काष्ठा etb_drvdata *drvdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		__etb_disable_hw(drvdata);
		etb_dump_hw(drvdata);
		__etb_enable_hw(drvdata);
	पूर्ण
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&drvdata->csdev->dev, "ETB dumped\n");
पूर्ण

अटल पूर्णांक etb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा etb_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा etb_drvdata, miscdev);

	अगर (local_cmpxchg(&drvdata->पढ़ोing, 0, 1))
		वापस -EBUSY;

	dev_dbg(&drvdata->csdev->dev, "%s: successfully opened\n", __func__);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार etb_पढ़ो(काष्ठा file *file, अक्षर __user *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	u32 depth;
	काष्ठा etb_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा etb_drvdata, miscdev);
	काष्ठा device *dev = &drvdata->csdev->dev;

	etb_dump(drvdata);

	depth = drvdata->buffer_depth;
	अगर (*ppos + len > depth * 4)
		len = depth * 4 - *ppos;

	अगर (copy_to_user(data, drvdata->buf + *ppos, len)) अणु
		dev_dbg(dev,
			"%s: copy_to_user failed\n", __func__);
		वापस -EFAULT;
	पूर्ण

	*ppos += len;

	dev_dbg(dev, "%s: %zu bytes copied, %d bytes left\n",
		__func__, len, (पूर्णांक)(depth * 4 - *ppos));
	वापस len;
पूर्ण

अटल पूर्णांक etb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा etb_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा etb_drvdata, miscdev);
	local_set(&drvdata->पढ़ोing, 0);

	dev_dbg(&drvdata->csdev->dev, "%s: released\n", __func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations etb_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= etb_खोलो,
	.पढ़ो		= etb_पढ़ो,
	.release	= etb_release,
	.llseek		= no_llseek,
पूर्ण;

#घोषणा coresight_etb10_reg(name, offset)		\
	coresight_simple_reg32(काष्ठा etb_drvdata, name, offset)

coresight_etb10_reg(rdp, ETB_RAM_DEPTH_REG);
coresight_etb10_reg(sts, ETB_STATUS_REG);
coresight_etb10_reg(rrp, ETB_RAM_READ_POINTER);
coresight_etb10_reg(rwp, ETB_RAM_WRITE_POINTER);
coresight_etb10_reg(trg, ETB_TRG);
coresight_etb10_reg(ctl, ETB_CTL_REG);
coresight_etb10_reg(ffsr, ETB_FFSR);
coresight_etb10_reg(ffcr, ETB_FFCR);

अटल काष्ठा attribute *coresight_etb_mgmt_attrs[] = अणु
	&dev_attr_rdp.attr,
	&dev_attr_sts.attr,
	&dev_attr_rrp.attr,
	&dev_attr_rwp.attr,
	&dev_attr_trg.attr,
	&dev_attr_ctl.attr,
	&dev_attr_ffsr.attr,
	&dev_attr_ffcr.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार trigger_cntr_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val = drvdata->trigger_cntr;

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार trigger_cntr_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	drvdata->trigger_cntr = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(trigger_cntr);

अटल काष्ठा attribute *coresight_etb_attrs[] = अणु
	&dev_attr_trigger_cntr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_etb_group = अणु
	.attrs = coresight_etb_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_etb_mgmt_group = अणु
	.attrs = coresight_etb_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group *coresight_etb_groups[] = अणु
	&coresight_etb_group,
	&coresight_etb_mgmt_group,
	शून्य,
पूर्ण;

अटल पूर्णांक etb_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा etb_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;

	desc.name = coresight_alloc_device_name(&etb_devs, dev);
	अगर (!desc.name)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->atclk = devm_clk_get(&adev->dev, "atclk"); /* optional */
	अगर (!IS_ERR(drvdata->atclk)) अणु
		ret = clk_prepare_enable(drvdata->atclk);
		अगर (ret)
			वापस ret;
	पूर्ण
	dev_set_drvdata(dev, drvdata);

	/* validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_lock_init(&drvdata->spinlock);

	drvdata->buffer_depth = etb_get_buffer_depth(drvdata);

	अगर (drvdata->buffer_depth & 0x80000000)
		वापस -EINVAL;

	drvdata->buf = devm_kसुस्मृति(dev,
				    drvdata->buffer_depth, 4, GFP_KERNEL);
	अगर (!drvdata->buf)
		वापस -ENOMEM;

	/* This device is not associated with a session */
	drvdata->pid = -1;

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);
	adev->dev.platक्रमm_data = pdata;

	desc.type = CORESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
	desc.ops = &etb_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.groups = coresight_etb_groups;
	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev))
		वापस PTR_ERR(drvdata->csdev);

	drvdata->miscdev.name = desc.name;
	drvdata->miscdev.minor = MISC_DYNAMIC_MINOR;
	drvdata->miscdev.fops = &etb_fops;
	ret = misc_रेजिस्टर(&drvdata->miscdev);
	अगर (ret)
		जाओ err_misc_रेजिस्टर;

	pm_runसमय_put(&adev->dev);
	वापस 0;

err_misc_रेजिस्टर:
	coresight_unरेजिस्टर(drvdata->csdev);
	वापस ret;
पूर्ण

अटल व्योम etb_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	/*
	 * Since misc_खोलो() holds a refcount on the f_ops, which is
	 * etb fops in this हाल, device is there until last file
	 * handler to this device is बंदd.
	 */
	misc_deरेजिस्टर(&drvdata->miscdev);
	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक etb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक etb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा etb_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops etb_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(etb_runसमय_suspend, etb_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा amba_id etb_ids[] = अणु
	अणु
		.id	= 0x000bb907,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, etb_ids);

अटल काष्ठा amba_driver etb_driver = अणु
	.drv = अणु
		.name	= "coresight-etb10",
		.owner	= THIS_MODULE,
		.pm	= &etb_dev_pm_ops,
		.suppress_bind_attrs = true,

	पूर्ण,
	.probe		= etb_probe,
	.हटाओ		= etb_हटाओ,
	.id_table	= etb_ids,
पूर्ण;

module_amba_driver(etb_driver);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight Embedded Trace Buffer driver");
MODULE_LICENSE("GPL v2");
