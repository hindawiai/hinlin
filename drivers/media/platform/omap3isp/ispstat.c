<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispstat.c
 *
 * TI OMAP3 ISP - Statistics core
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Contacts: David Cohen <dacohen@gmail.com>
 *	     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/uaccess.h>

#समावेश "isp.h"

#घोषणा ISP_STAT_USES_DMAENGINE(stat)	((stat)->dma_ch != शून्य)

/*
 * MAGIC_SIZE must always be the greatest common भागisor of
 * AEWB_PACKET_SIZE and AF_PAXEL_SIZE.
 */
#घोषणा MAGIC_SIZE		16
#घोषणा MAGIC_NUM		0x55

/* HACK: AF module seems to be writing one more paxel data than it should. */
#घोषणा AF_EXTRA_DATA		OMAP3ISP_AF_PAXEL_SIZE

/*
 * HACK: H3A modules go to an invalid state after have a SBL overflow. It makes
 * the next buffer to start to be written in the same poपूर्णांक where the overflow
 * occurred instead of the configured address. The only known way to make it to
 * go back to a valid state is having a valid buffer processing. Of course it
 * requires at least a द्विगुनd buffer size to aव्योम an access to invalid memory
 * region. But it करोes not fix everything. It may happen more than one
 * consecutive SBL overflows. In that हाल, it might be unpredictable how many
 * buffers the allocated memory should fit. For that हाल, a recover
 * configuration was created. It produces the minimum buffer size क्रम each H3A
 * module and decrease the change क्रम more SBL overflows. This recover state
 * will be enabled every समय a SBL overflow occur. As the output buffer size
 * isn't big, it's possible to have an extra size able to fit many recover
 * buffers making it extreamily unlikely to have an access to invalid memory
 * region.
 */
#घोषणा NUM_H3A_RECOVER_BUFS	10

/*
 * HACK: Because of HW issues the generic layer someबार need to have
 * dअगरferent behaviour क्रम dअगरferent statistic modules.
 */
#घोषणा IS_H3A_AF(stat)		((stat) == &(stat)->isp->isp_af)
#घोषणा IS_H3A_AEWB(stat)	((stat) == &(stat)->isp->isp_aewb)
#घोषणा IS_H3A(stat)		(IS_H3A_AF(stat) || IS_H3A_AEWB(stat))

अटल व्योम __isp_stat_buf_sync_magic(काष्ठा ispstat *stat,
				      काष्ठा ispstat_buffer *buf,
				      u32 buf_size, क्रमागत dma_data_direction dir,
				      व्योम (*dma_sync)(काष्ठा device *,
					dma_addr_t, अचिन्हित दीर्घ, माप_प्रकार,
					क्रमागत dma_data_direction))
अणु
	/* Sync the initial and final magic words. */
	dma_sync(stat->isp->dev, buf->dma_addr, 0, MAGIC_SIZE, dir);
	dma_sync(stat->isp->dev, buf->dma_addr + (buf_size & PAGE_MASK),
		 buf_size & ~PAGE_MASK, MAGIC_SIZE, dir);
पूर्ण

अटल व्योम isp_stat_buf_sync_magic_क्रम_device(काष्ठा ispstat *stat,
					       काष्ठा ispstat_buffer *buf,
					       u32 buf_size,
					       क्रमागत dma_data_direction dir)
अणु
	अगर (ISP_STAT_USES_DMAENGINE(stat))
		वापस;

	__isp_stat_buf_sync_magic(stat, buf, buf_size, dir,
				  dma_sync_single_range_क्रम_device);
पूर्ण

अटल व्योम isp_stat_buf_sync_magic_क्रम_cpu(काष्ठा ispstat *stat,
					    काष्ठा ispstat_buffer *buf,
					    u32 buf_size,
					    क्रमागत dma_data_direction dir)
अणु
	अगर (ISP_STAT_USES_DMAENGINE(stat))
		वापस;

	__isp_stat_buf_sync_magic(stat, buf, buf_size, dir,
				  dma_sync_single_range_क्रम_cpu);
पूर्ण

अटल पूर्णांक isp_stat_buf_check_magic(काष्ठा ispstat *stat,
				    काष्ठा ispstat_buffer *buf)
अणु
	स्थिर u32 buf_size = IS_H3A_AF(stat) ?
			     buf->buf_size + AF_EXTRA_DATA : buf->buf_size;
	u8 *w;
	u8 *end;
	पूर्णांक ret = -EINVAL;

	isp_stat_buf_sync_magic_क्रम_cpu(stat, buf, buf_size, DMA_FROM_DEVICE);

	/* Checking initial magic numbers. They shouldn't be here anymore. */
	क्रम (w = buf->virt_addr, end = w + MAGIC_SIZE; w < end; w++)
		अगर (likely(*w != MAGIC_NUM))
			ret = 0;

	अगर (ret) अणु
		dev_dbg(stat->isp->dev,
			"%s: beginning magic check does not match.\n",
			stat->subdev.name);
		वापस ret;
	पूर्ण

	/* Checking magic numbers at the end. They must be still here. */
	क्रम (w = buf->virt_addr + buf_size, end = w + MAGIC_SIZE;
	     w < end; w++) अणु
		अगर (unlikely(*w != MAGIC_NUM)) अणु
			dev_dbg(stat->isp->dev,
				"%s: ending magic check does not match.\n",
				stat->subdev.name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	isp_stat_buf_sync_magic_क्रम_device(stat, buf, buf_size,
					   DMA_FROM_DEVICE);

	वापस 0;
पूर्ण

अटल व्योम isp_stat_buf_insert_magic(काष्ठा ispstat *stat,
				      काष्ठा ispstat_buffer *buf)
अणु
	स्थिर u32 buf_size = IS_H3A_AF(stat) ?
			     stat->buf_size + AF_EXTRA_DATA : stat->buf_size;

	isp_stat_buf_sync_magic_क्रम_cpu(stat, buf, buf_size, DMA_FROM_DEVICE);

	/*
	 * Inserting MAGIC_NUM at the beginning and end of the buffer.
	 * buf->buf_size is set only after the buffer is queued. For now the
	 * right buf_size क्रम the current configuration is poपूर्णांकed by
	 * stat->buf_size.
	 */
	स_रखो(buf->virt_addr, MAGIC_NUM, MAGIC_SIZE);
	स_रखो(buf->virt_addr + buf_size, MAGIC_NUM, MAGIC_SIZE);

	isp_stat_buf_sync_magic_क्रम_device(stat, buf, buf_size,
					   DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम isp_stat_buf_sync_क्रम_device(काष्ठा ispstat *stat,
					 काष्ठा ispstat_buffer *buf)
अणु
	अगर (ISP_STAT_USES_DMAENGINE(stat))
		वापस;

	dma_sync_sg_क्रम_device(stat->isp->dev, buf->sgt.sgl,
			       buf->sgt.nents, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम isp_stat_buf_sync_क्रम_cpu(काष्ठा ispstat *stat,
				      काष्ठा ispstat_buffer *buf)
अणु
	अगर (ISP_STAT_USES_DMAENGINE(stat))
		वापस;

	dma_sync_sg_क्रम_cpu(stat->isp->dev, buf->sgt.sgl,
			    buf->sgt.nents, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम isp_stat_buf_clear(काष्ठा ispstat *stat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < STAT_MAX_BUFS; i++)
		stat->buf[i].empty = 1;
पूर्ण

अटल काष्ठा ispstat_buffer *
__isp_stat_buf_find(काष्ठा ispstat *stat, पूर्णांक look_empty)
अणु
	काष्ठा ispstat_buffer *found = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < STAT_MAX_BUFS; i++) अणु
		काष्ठा ispstat_buffer *curr = &stat->buf[i];

		/*
		 * Don't select the buffer which is being copied to
		 * userspace or used by the module.
		 */
		अगर (curr == stat->locked_buf || curr == stat->active_buf)
			जारी;

		/* Don't select uninitialised buffers if it's not required */
		अगर (!look_empty && curr->empty)
			जारी;

		/* Pick uninitialised buffer over anything अन्यथा अगर look_empty */
		अगर (curr->empty) अणु
			found = curr;
			अवरोध;
		पूर्ण

		/* Choose the oldest buffer */
		अगर (!found ||
		    (s32)curr->frame_number - (s32)found->frame_number < 0)
			found = curr;
	पूर्ण

	वापस found;
पूर्ण

अटल अंतरभूत काष्ठा ispstat_buffer *
isp_stat_buf_find_oldest(काष्ठा ispstat *stat)
अणु
	वापस __isp_stat_buf_find(stat, 0);
पूर्ण

अटल अंतरभूत काष्ठा ispstat_buffer *
isp_stat_buf_find_oldest_or_empty(काष्ठा ispstat *stat)
अणु
	वापस __isp_stat_buf_find(stat, 1);
पूर्ण

अटल पूर्णांक isp_stat_buf_queue(काष्ठा ispstat *stat)
अणु
	अगर (!stat->active_buf)
		वापस STAT_NO_BUF;

	kसमय_get_ts64(&stat->active_buf->ts);

	stat->active_buf->buf_size = stat->buf_size;
	अगर (isp_stat_buf_check_magic(stat, stat->active_buf)) अणु
		dev_dbg(stat->isp->dev, "%s: data wasn't properly written.\n",
			stat->subdev.name);
		वापस STAT_NO_BUF;
	पूर्ण
	stat->active_buf->config_counter = stat->config_counter;
	stat->active_buf->frame_number = stat->frame_number;
	stat->active_buf->empty = 0;
	stat->active_buf = शून्य;

	वापस STAT_BUF_DONE;
पूर्ण

/* Get next मुक्त buffer to ग_लिखो the statistics to and mark it active. */
अटल व्योम isp_stat_buf_next(काष्ठा ispstat *stat)
अणु
	अगर (unlikely(stat->active_buf))
		/* Overwriting unused active buffer */
		dev_dbg(stat->isp->dev,
			"%s: new buffer requested without queuing active one.\n",
			stat->subdev.name);
	अन्यथा
		stat->active_buf = isp_stat_buf_find_oldest_or_empty(stat);
पूर्ण

अटल व्योम isp_stat_buf_release(काष्ठा ispstat *stat)
अणु
	अचिन्हित दीर्घ flags;

	isp_stat_buf_sync_क्रम_device(stat, stat->locked_buf);
	spin_lock_irqsave(&stat->isp->stat_lock, flags);
	stat->locked_buf = शून्य;
	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
पूर्ण

/* Get buffer to userspace. */
अटल काष्ठा ispstat_buffer *isp_stat_buf_get(काष्ठा ispstat *stat,
					       काष्ठा omap3isp_stat_data *data)
अणु
	पूर्णांक rval = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा ispstat_buffer *buf;

	spin_lock_irqsave(&stat->isp->stat_lock, flags);

	जबतक (1) अणु
		buf = isp_stat_buf_find_oldest(stat);
		अगर (!buf) अणु
			spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
			dev_dbg(stat->isp->dev, "%s: cannot find a buffer.\n",
				stat->subdev.name);
			वापस ERR_PTR(-EBUSY);
		पूर्ण
		अगर (isp_stat_buf_check_magic(stat, buf)) अणु
			dev_dbg(stat->isp->dev,
				"%s: current buffer has corrupted data\n.",
				stat->subdev.name);
			/* Mark empty because it करोesn't have valid data. */
			buf->empty = 1;
		पूर्ण अन्यथा अणु
			/* Buffer isn't corrupted. */
			अवरोध;
		पूर्ण
	पूर्ण

	stat->locked_buf = buf;

	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

	अगर (buf->buf_size > data->buf_size) अणु
		dev_warn(stat->isp->dev,
			 "%s: userspace's buffer size is not enough.\n",
			 stat->subdev.name);
		isp_stat_buf_release(stat);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	isp_stat_buf_sync_क्रम_cpu(stat, buf);

	rval = copy_to_user(data->buf,
			    buf->virt_addr,
			    buf->buf_size);

	अगर (rval) अणु
		dev_info(stat->isp->dev,
			 "%s: failed copying %d bytes of stat data\n",
			 stat->subdev.name, rval);
		buf = ERR_PTR(-EFAULT);
		isp_stat_buf_release(stat);
	पूर्ण

	वापस buf;
पूर्ण

अटल व्योम isp_stat_bufs_मुक्त(काष्ठा ispstat *stat)
अणु
	काष्ठा device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? शून्य : stat->isp->dev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < STAT_MAX_BUFS; i++) अणु
		काष्ठा ispstat_buffer *buf = &stat->buf[i];

		अगर (!buf->virt_addr)
			जारी;

		sg_मुक्त_table(&buf->sgt);

		dma_मुक्त_coherent(dev, stat->buf_alloc_size, buf->virt_addr,
				  buf->dma_addr);

		buf->dma_addr = 0;
		buf->virt_addr = शून्य;
		buf->empty = 1;
	पूर्ण

	dev_dbg(stat->isp->dev, "%s: all buffers were freed.\n",
		stat->subdev.name);

	stat->buf_alloc_size = 0;
	stat->active_buf = शून्य;
पूर्ण

अटल पूर्णांक isp_stat_bufs_alloc_one(काष्ठा device *dev,
				   काष्ठा ispstat_buffer *buf,
				   अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	buf->virt_addr = dma_alloc_coherent(dev, size, &buf->dma_addr,
					    GFP_KERNEL);
	अगर (!buf->virt_addr)
		वापस -ENOMEM;

	ret = dma_get_sgtable(dev, &buf->sgt, buf->virt_addr, buf->dma_addr,
			      size);
	अगर (ret < 0) अणु
		dma_मुक्त_coherent(dev, size, buf->virt_addr, buf->dma_addr);
		buf->virt_addr = शून्य;
		buf->dma_addr = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The device passed to the DMA API depends on whether the statistics block uses
 * ISP DMA, बाह्यal DMA or PIO to transfer data.
 *
 * The first हाल (क्रम the AEWB and AF engines) passes the ISP device, resulting
 * in the DMA buffers being mapped through the ISP IOMMU.
 *
 * The second हाल (क्रम the histogram engine) should pass the DMA engine device.
 * As that device isn't accessible through the OMAP DMA engine API the driver
 * passes शून्य instead, resulting in the buffers being mapped directly as
 * physical pages.
 *
 * The third हाल (क्रम the histogram engine) करोesn't require any mapping. The
 * buffers could be allocated with kदो_स्मृति/vदो_स्मृति, but we still use
 * dma_alloc_coherent() क्रम consistency purpose.
 */
अटल पूर्णांक isp_stat_bufs_alloc(काष्ठा ispstat *stat, u32 size)
अणु
	काष्ठा device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? शून्य : stat->isp->dev;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&stat->isp->stat_lock, flags);

	BUG_ON(stat->locked_buf != शून्य);

	/* Are the old buffers big enough? */
	अगर (stat->buf_alloc_size >= size) अणु
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
		वापस 0;
	पूर्ण

	अगर (stat->state != ISPSTAT_DISABLED || stat->buf_processing) अणु
		dev_info(stat->isp->dev,
			 "%s: trying to allocate memory when busy\n",
			 stat->subdev.name);
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
		वापस -EBUSY;
	पूर्ण

	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

	isp_stat_bufs_मुक्त(stat);

	stat->buf_alloc_size = size;

	क्रम (i = 0; i < STAT_MAX_BUFS; i++) अणु
		काष्ठा ispstat_buffer *buf = &stat->buf[i];
		पूर्णांक ret;

		ret = isp_stat_bufs_alloc_one(dev, buf, size);
		अगर (ret < 0) अणु
			dev_err(stat->isp->dev,
				"%s: Failed to allocate DMA buffer %u\n",
				stat->subdev.name, i);
			isp_stat_bufs_मुक्त(stat);
			वापस ret;
		पूर्ण

		buf->empty = 1;

		dev_dbg(stat->isp->dev,
			"%s: buffer[%u] allocated. dma=%pad virt=%p",
			stat->subdev.name, i, &buf->dma_addr, buf->virt_addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम isp_stat_queue_event(काष्ठा ispstat *stat, पूर्णांक err)
अणु
	काष्ठा video_device *vdev = stat->subdev.devnode;
	काष्ठा v4l2_event event;
	काष्ठा omap3isp_stat_event_status *status = (व्योम *)event.u.data;

	स_रखो(&event, 0, माप(event));
	अगर (!err) अणु
		status->frame_number = stat->frame_number;
		status->config_counter = stat->config_counter;
	पूर्ण अन्यथा अणु
		status->buf_err = 1;
	पूर्ण
	event.type = stat->event_type;
	v4l2_event_queue(vdev, &event);
पूर्ण


/*
 * omap3isp_stat_request_statistics - Request statistics.
 * @data: Poपूर्णांकer to वापस statistics data.
 *
 * Returns 0 अगर successful.
 */
पूर्णांक omap3isp_stat_request_statistics(काष्ठा ispstat *stat,
				     काष्ठा omap3isp_stat_data *data)
अणु
	काष्ठा ispstat_buffer *buf;

	अगर (stat->state != ISPSTAT_ENABLED) अणु
		dev_dbg(stat->isp->dev, "%s: engine not enabled.\n",
			stat->subdev.name);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&stat->ioctl_lock);
	buf = isp_stat_buf_get(stat, data);
	अगर (IS_ERR(buf)) अणु
		mutex_unlock(&stat->ioctl_lock);
		वापस PTR_ERR(buf);
	पूर्ण

	data->ts.tv_sec = buf->ts.tv_sec;
	data->ts.tv_usec = buf->ts.tv_nsec / NSEC_PER_USEC;
	data->config_counter = buf->config_counter;
	data->frame_number = buf->frame_number;
	data->buf_size = buf->buf_size;

	buf->empty = 1;
	isp_stat_buf_release(stat);
	mutex_unlock(&stat->ioctl_lock);

	वापस 0;
पूर्ण

पूर्णांक omap3isp_stat_request_statistics_समय32(काष्ठा ispstat *stat,
					काष्ठा omap3isp_stat_data_समय32 *data)
अणु
	काष्ठा omap3isp_stat_data data64;
	पूर्णांक ret;

	ret = omap3isp_stat_request_statistics(stat, &data64);
	अगर (ret)
		वापस ret;

	data->ts.tv_sec = data64.ts.tv_sec;
	data->ts.tv_usec = data64.ts.tv_usec;
	स_नकल(&data->buf, &data64.buf, माप(*data) - माप(data->ts));

	वापस 0;
पूर्ण

/*
 * omap3isp_stat_config - Receives new statistic engine configuration.
 * @new_conf: Poपूर्णांकer to config काष्ठाure.
 *
 * Returns 0 अगर successful, -EINVAL अगर new_conf poपूर्णांकer is शून्य, -ENOMEM अगर
 * was unable to allocate memory क्रम the buffer, or other errors अगर parameters
 * are invalid.
 */
पूर्णांक omap3isp_stat_config(काष्ठा ispstat *stat, व्योम *new_conf)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ irqflags;
	काष्ठा ispstat_generic_config *user_cfg = new_conf;
	u32 buf_size = user_cfg->buf_size;

	mutex_lock(&stat->ioctl_lock);

	dev_dbg(stat->isp->dev,
		"%s: configuring module with buffer size=0x%08lx\n",
		stat->subdev.name, (अचिन्हित दीर्घ)buf_size);

	ret = stat->ops->validate_params(stat, new_conf);
	अगर (ret) अणु
		mutex_unlock(&stat->ioctl_lock);
		dev_dbg(stat->isp->dev, "%s: configuration values are invalid.\n",
			stat->subdev.name);
		वापस ret;
	पूर्ण

	अगर (buf_size != user_cfg->buf_size)
		dev_dbg(stat->isp->dev,
			"%s: driver has corrected buffer size request to 0x%08lx\n",
			stat->subdev.name,
			(अचिन्हित दीर्घ)user_cfg->buf_size);

	/*
	 * Hack: H3A modules may need a द्विगुनd buffer size to aव्योम access
	 * to a invalid memory address after a SBL overflow.
	 * The buffer size is always PAGE_ALIGNED.
	 * Hack 2: MAGIC_SIZE is added to buf_size so a magic word can be
	 * inserted at the end to data पूर्णांकegrity check purpose.
	 * Hack 3: AF module ग_लिखोs one paxel data more than it should, so
	 * the buffer allocation must consider it to aव्योम invalid memory
	 * access.
	 * Hack 4: H3A need to allocate extra space क्रम the recover state.
	 */
	अगर (IS_H3A(stat)) अणु
		buf_size = user_cfg->buf_size * 2 + MAGIC_SIZE;
		अगर (IS_H3A_AF(stat))
			/*
			 * Adding one extra paxel data size क्रम each recover
			 * buffer + 2 regular ones.
			 */
			buf_size += AF_EXTRA_DATA * (NUM_H3A_RECOVER_BUFS + 2);
		अगर (stat->recover_priv) अणु
			काष्ठा ispstat_generic_config *recover_cfg =
				stat->recover_priv;
			buf_size += recover_cfg->buf_size *
				    NUM_H3A_RECOVER_BUFS;
		पूर्ण
		buf_size = PAGE_ALIGN(buf_size);
	पूर्ण अन्यथा अणु /* Histogram */
		buf_size = PAGE_ALIGN(user_cfg->buf_size + MAGIC_SIZE);
	पूर्ण

	ret = isp_stat_bufs_alloc(stat, buf_size);
	अगर (ret) अणु
		mutex_unlock(&stat->ioctl_lock);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	stat->ops->set_params(stat, new_conf);
	spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);

	/*
	 * Returning the right future config_counter क्रम this setup, so
	 * userspace can *know* when it has been applied.
	 */
	user_cfg->config_counter = stat->config_counter + stat->inc_config;

	/* Module has a valid configuration. */
	stat->configured = 1;
	dev_dbg(stat->isp->dev,
		"%s: module has been successfully configured.\n",
		stat->subdev.name);

	mutex_unlock(&stat->ioctl_lock);

	वापस 0;
पूर्ण

/*
 * isp_stat_buf_process - Process statistic buffers.
 * @buf_state: poपूर्णांकs out अगर buffer is पढ़ोy to be processed. It's necessary
 *	       because histogram needs to copy the data from पूर्णांकernal memory
 *	       beक्रमe be able to process the buffer.
 */
अटल पूर्णांक isp_stat_buf_process(काष्ठा ispstat *stat, पूर्णांक buf_state)
अणु
	पूर्णांक ret = STAT_NO_BUF;

	अगर (!atomic_add_unless(&stat->buf_err, -1, 0) &&
	    buf_state == STAT_BUF_DONE && stat->state == ISPSTAT_ENABLED) अणु
		ret = isp_stat_buf_queue(stat);
		isp_stat_buf_next(stat);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक omap3isp_stat_pcr_busy(काष्ठा ispstat *stat)
अणु
	वापस stat->ops->busy(stat);
पूर्ण

पूर्णांक omap3isp_stat_busy(काष्ठा ispstat *stat)
अणु
	वापस omap3isp_stat_pcr_busy(stat) | stat->buf_processing |
		(stat->state != ISPSTAT_DISABLED);
पूर्ण

/*
 * isp_stat_pcr_enable - Disables/Enables statistic engines.
 * @pcr_enable: 0/1 - Disables/Enables the engine.
 *
 * Must be called from ISP driver when the module is idle and synchronized
 * with CCDC.
 */
अटल व्योम isp_stat_pcr_enable(काष्ठा ispstat *stat, u8 pcr_enable)
अणु
	अगर ((stat->state != ISPSTAT_ENABLING &&
	     stat->state != ISPSTAT_ENABLED) && pcr_enable)
		/* Userspace has disabled the module. Aborting. */
		वापस;

	stat->ops->enable(stat, pcr_enable);
	अगर (stat->state == ISPSTAT_DISABLING && !pcr_enable)
		stat->state = ISPSTAT_DISABLED;
	अन्यथा अगर (stat->state == ISPSTAT_ENABLING && pcr_enable)
		stat->state = ISPSTAT_ENABLED;
पूर्ण

व्योम omap3isp_stat_suspend(काष्ठा ispstat *stat)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&stat->isp->stat_lock, flags);

	अगर (stat->state != ISPSTAT_DISABLED)
		stat->ops->enable(stat, 0);
	अगर (stat->state == ISPSTAT_ENABLED)
		stat->state = ISPSTAT_SUSPENDED;

	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
पूर्ण

व्योम omap3isp_stat_resume(काष्ठा ispstat *stat)
अणु
	/* Module will be re-enabled with its pipeline */
	अगर (stat->state == ISPSTAT_SUSPENDED)
		stat->state = ISPSTAT_ENABLING;
पूर्ण

अटल व्योम isp_stat_try_enable(काष्ठा ispstat *stat)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (stat->priv == शून्य)
		/* driver wasn't initialised */
		वापस;

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	अगर (stat->state == ISPSTAT_ENABLING && !stat->buf_processing &&
	    stat->buf_alloc_size) अणु
		/*
		 * Userspace's requested to enable the engine but it wasn't yet.
		 * Let's करो that now.
		 */
		stat->update = 1;
		isp_stat_buf_next(stat);
		stat->ops->setup_regs(stat, stat->priv);
		isp_stat_buf_insert_magic(stat, stat->active_buf);

		/*
		 * H3A module has some hw issues which क्रमces the driver to
		 * ignore next buffers even अगर it was disabled in the meanसमय.
		 * On the other hand, Histogram shouldn't ignore buffers anymore
		 * अगर it's being enabled.
		 */
		अगर (!IS_H3A(stat))
			atomic_set(&stat->buf_err, 0);

		isp_stat_pcr_enable(stat, 1);
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
		dev_dbg(stat->isp->dev, "%s: module is enabled.\n",
			stat->subdev.name);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
	पूर्ण
पूर्ण

व्योम omap3isp_stat_isr_frame_sync(काष्ठा ispstat *stat)
अणु
	isp_stat_try_enable(stat);
पूर्ण

व्योम omap3isp_stat_sbl_overflow(काष्ठा ispstat *stat)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	/*
	 * Due to a H3A hw issue which prevents the next buffer to start from
	 * the correct memory address, 2 buffers must be ignored.
	 */
	atomic_set(&stat->buf_err, 2);

	/*
	 * If more than one SBL overflow happen in a row, H3A module may access
	 * invalid memory region.
	 * stat->sbl_ovl_recover is set to tell to the driver to temporarily use
	 * a soft configuration which helps to aव्योम consecutive overflows.
	 */
	अगर (stat->recover_priv)
		stat->sbl_ovl_recover = 1;
	spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
पूर्ण

/*
 * omap3isp_stat_enable - Disable/Enable statistic engine as soon as possible
 * @enable: 0/1 - Disables/Enables the engine.
 *
 * Client should configure all the module रेजिस्टरs beक्रमe this.
 * This function can be called from a userspace request.
 */
पूर्णांक omap3isp_stat_enable(काष्ठा ispstat *stat, u8 enable)
अणु
	अचिन्हित दीर्घ irqflags;

	dev_dbg(stat->isp->dev, "%s: user wants to %s module.\n",
		stat->subdev.name, enable ? "enable" : "disable");

	/* Prevent enabling जबतक configuring */
	mutex_lock(&stat->ioctl_lock);

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);

	अगर (!stat->configured && enable) अणु
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
		mutex_unlock(&stat->ioctl_lock);
		dev_dbg(stat->isp->dev,
			"%s: cannot enable module as it's never been successfully configured so far.\n",
			stat->subdev.name);
		वापस -EINVAL;
	पूर्ण

	अगर (enable) अणु
		अगर (stat->state == ISPSTAT_DISABLING)
			/* Previous disabling request wasn't करोne yet */
			stat->state = ISPSTAT_ENABLED;
		अन्यथा अगर (stat->state == ISPSTAT_DISABLED)
			/* Module is now being enabled */
			stat->state = ISPSTAT_ENABLING;
	पूर्ण अन्यथा अणु
		अगर (stat->state == ISPSTAT_ENABLING) अणु
			/* Previous enabling request wasn't करोne yet */
			stat->state = ISPSTAT_DISABLED;
		पूर्ण अन्यथा अगर (stat->state == ISPSTAT_ENABLED) अणु
			/* Module is now being disabled */
			stat->state = ISPSTAT_DISABLING;
			isp_stat_buf_clear(stat);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
	mutex_unlock(&stat->ioctl_lock);

	वापस 0;
पूर्ण

पूर्णांक omap3isp_stat_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ispstat *stat = v4l2_get_subdevdata(subdev);

	अगर (enable) अणु
		/*
		 * Only set enable PCR bit अगर the module was previously
		 * enabled through ioctl.
		 */
		isp_stat_try_enable(stat);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		/* Disable PCR bit and config enable field */
		omap3isp_stat_enable(stat, 0);
		spin_lock_irqsave(&stat->isp->stat_lock, flags);
		stat->ops->enable(stat, 0);
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

		/*
		 * If module isn't busy, a new पूर्णांकerrupt may come or not to
		 * set the state to DISABLED. As Histogram needs to पढ़ो its
		 * पूर्णांकernal memory to clear it, let पूर्णांकerrupt handler
		 * responsible of changing state to DISABLED. If the last
		 * पूर्णांकerrupt is coming, it's still safe as the handler will
		 * ignore the second समय when state is alपढ़ोy set to DISABLED.
		 * It's necessary to synchronize Histogram with streamoff, once
		 * the module may be considered idle beक्रमe last SDMA transfer
		 * starts अगर we वापस here.
		 */
		अगर (!omap3isp_stat_pcr_busy(stat))
			omap3isp_stat_isr(stat);

		dev_dbg(stat->isp->dev, "%s: module is being disabled\n",
			stat->subdev.name);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * __stat_isr - Interrupt handler क्रम statistic drivers
 */
अटल व्योम __stat_isr(काष्ठा ispstat *stat, पूर्णांक from_dma)
अणु
	पूर्णांक ret = STAT_BUF_DONE;
	पूर्णांक buf_processing;
	अचिन्हित दीर्घ irqflags;
	काष्ठा isp_pipeline *pipe;

	/*
	 * stat->buf_processing must be set beक्रमe disable module. It's
	 * necessary to not inक्रमm too early the buffers aren't busy in हाल
	 * of SDMA is going to be used.
	 */
	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	अगर (stat->state == ISPSTAT_DISABLED) अणु
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
		वापस;
	पूर्ण
	buf_processing = stat->buf_processing;
	stat->buf_processing = 1;
	stat->ops->enable(stat, 0);

	अगर (buf_processing && !from_dma) अणु
		अगर (stat->state == ISPSTAT_ENABLED) अणु
			spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
			dev_err(stat->isp->dev,
				"%s: interrupt occurred when module was still processing a buffer.\n",
				stat->subdev.name);
			ret = STAT_NO_BUF;
			जाओ out;
		पूर्ण अन्यथा अणु
			/*
			 * Interrupt handler was called from streamoff when
			 * the module wasn't busy anymore to ensure it is being
			 * disabled after process last buffer. If such buffer
			 * processing has alपढ़ोy started, no need to करो
			 * anything अन्यथा.
			 */
			spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);

	/* If it's busy we can't process this buffer anymore */
	अगर (!omap3isp_stat_pcr_busy(stat)) अणु
		अगर (!from_dma && stat->ops->buf_process)
			/* Module still need to copy data to buffer. */
			ret = stat->ops->buf_process(stat);
		अगर (ret == STAT_BUF_WAITING_DMA)
			/* Buffer is not पढ़ोy yet */
			वापस;

		spin_lock_irqsave(&stat->isp->stat_lock, irqflags);

		/*
		 * Histogram needs to पढ़ो its पूर्णांकernal memory to clear it
		 * beक्रमe be disabled. For that reason, common statistic layer
		 * can वापस only after call stat's buf_process() चालक.
		 */
		अगर (stat->state == ISPSTAT_DISABLING) अणु
			stat->state = ISPSTAT_DISABLED;
			spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
			stat->buf_processing = 0;
			वापस;
		पूर्ण
		pipe = to_isp_pipeline(&stat->subdev.entity);
		stat->frame_number = atomic_पढ़ो(&pipe->frame_number);

		/*
		 * Beक्रमe this poपूर्णांक, 'ret' stores the buffer's status if it's
		 * पढ़ोy to be processed. Afterwards, it holds the status अगर
		 * it was processed successfully.
		 */
		ret = isp_stat_buf_process(stat, ret);

		अगर (likely(!stat->sbl_ovl_recover)) अणु
			stat->ops->setup_regs(stat, stat->priv);
		पूर्ण अन्यथा अणु
			/*
			 * Using recover config to increase the chance to have
			 * a good buffer processing and make the H3A module to
			 * go back to a valid state.
			 */
			stat->update = 1;
			stat->ops->setup_regs(stat, stat->recover_priv);
			stat->sbl_ovl_recover = 0;

			/*
			 * Set 'update' in हाल of the module needs to use
			 * regular configuration after next buffer.
			 */
			stat->update = 1;
		पूर्ण

		isp_stat_buf_insert_magic(stat, stat->active_buf);

		/*
		 * Hack: H3A modules may access invalid memory address or send
		 * corrupted data to userspace अगर more than 1 SBL overflow
		 * happens in a row without re-writing its buffer's start memory
		 * address in the meanसमय. Such situation is aव्योमed अगर the
		 * module is not immediately re-enabled when the ISR misses the
		 * timing to process the buffer and to setup the रेजिस्टरs.
		 * Because of that, pcr_enable(1) was moved to inside this 'if'
		 * block. But the next पूर्णांकerruption will still happen as during
		 * pcr_enable(0) the module was busy.
		 */
		isp_stat_pcr_enable(stat, 1);
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
	पूर्ण अन्यथा अणु
		/*
		 * If a SBL overflow occurs and the H3A driver misses the timing
		 * to process the buffer, stat->buf_err is set and won't be
		 * cleared now. So the next buffer will be correctly ignored.
		 * It's necessary due to a hw issue which makes the next H3A
		 * buffer to start from the memory address where the previous
		 * one stopped, instead of start where it was configured to.
		 * Do not "stat->buf_err = 0" here.
		 */

		अगर (stat->ops->buf_process)
			/*
			 * Driver may need to erase current data prior to
			 * process a new buffer. If it misses the timing, the
			 * next buffer might be wrong. So should be ignored.
			 * It happens only क्रम Histogram.
			 */
			atomic_set(&stat->buf_err, 1);

		ret = STAT_NO_BUF;
		dev_dbg(stat->isp->dev,
			"%s: cannot process buffer, device is busy.\n",
			stat->subdev.name);
	पूर्ण

out:
	stat->buf_processing = 0;
	isp_stat_queue_event(stat, ret != STAT_BUF_DONE);
पूर्ण

व्योम omap3isp_stat_isr(काष्ठा ispstat *stat)
अणु
	__stat_isr(stat, 0);
पूर्ण

व्योम omap3isp_stat_dma_isr(काष्ठा ispstat *stat)
अणु
	__stat_isr(stat, 1);
पूर्ण

पूर्णांक omap3isp_stat_subscribe_event(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_fh *fh,
				  काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा ispstat *stat = v4l2_get_subdevdata(subdev);

	अगर (sub->type != stat->event_type)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, STAT_NEVENTS, शून्य);
पूर्ण

पूर्णांक omap3isp_stat_unsubscribe_event(काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_fh *fh,
				    काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण

व्योम omap3isp_stat_unरेजिस्टर_entities(काष्ठा ispstat *stat)
अणु
	v4l2_device_unरेजिस्टर_subdev(&stat->subdev);
पूर्ण

पूर्णांक omap3isp_stat_रेजिस्टर_entities(काष्ठा ispstat *stat,
				    काष्ठा v4l2_device *vdev)
अणु
	stat->subdev.dev = vdev->mdev->dev;

	वापस v4l2_device_रेजिस्टर_subdev(vdev, &stat->subdev);
पूर्ण

अटल पूर्णांक isp_stat_init_entities(काष्ठा ispstat *stat, स्थिर अक्षर *name,
				  स्थिर काष्ठा v4l2_subdev_ops *sd_ops)
अणु
	काष्ठा v4l2_subdev *subdev = &stat->subdev;
	काष्ठा media_entity *me = &subdev->entity;

	v4l2_subdev_init(subdev, sd_ops);
	snम_लिखो(subdev->name, V4L2_SUBDEV_NAME_SIZE, "OMAP3 ISP %s", name);
	subdev->grp_id = BIT(16);	/* group ID क्रम isp subdevs */
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;
	v4l2_set_subdevdata(subdev, stat);

	stat->pad.flags = MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	me->ops = शून्य;

	वापस media_entity_pads_init(me, 1, &stat->pad);
पूर्ण

पूर्णांक omap3isp_stat_init(काष्ठा ispstat *stat, स्थिर अक्षर *name,
		       स्थिर काष्ठा v4l2_subdev_ops *sd_ops)
अणु
	पूर्णांक ret;

	stat->buf = kसुस्मृति(STAT_MAX_BUFS, माप(*stat->buf), GFP_KERNEL);
	अगर (!stat->buf)
		वापस -ENOMEM;

	isp_stat_buf_clear(stat);
	mutex_init(&stat->ioctl_lock);
	atomic_set(&stat->buf_err, 0);

	ret = isp_stat_init_entities(stat, name, sd_ops);
	अगर (ret < 0) अणु
		mutex_destroy(&stat->ioctl_lock);
		kमुक्त(stat->buf);
	पूर्ण

	वापस ret;
पूर्ण

व्योम omap3isp_stat_cleanup(काष्ठा ispstat *stat)
अणु
	media_entity_cleanup(&stat->subdev.entity);
	mutex_destroy(&stat->ioctl_lock);
	isp_stat_bufs_मुक्त(stat);
	kमुक्त(stat->buf);
	kमुक्त(stat->priv);
	kमुक्त(stat->recover_priv);
पूर्ण
