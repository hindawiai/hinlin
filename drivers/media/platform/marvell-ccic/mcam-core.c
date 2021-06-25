<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Marvell camera core.  This device appears in a number of settings,
 * so it needs platक्रमm-specअगरic support outside of the core.
 *
 * Copyright 2011 Jonathan Corbet corbet@lwn.net
 * Copyright 2018 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "mcam-core.h"

#अगर_घोषित MCAM_MODE_VMALLOC
/*
 * Internal DMA buffer management.  Since the controller cannot करो S/G I/O,
 * we must have physically contiguous buffers to bring frames पूर्णांकo.
 * These parameters control how many buffers we use, whether we
 * allocate them at load समय (better chance of success, but nails करोwn
 * memory) or when somebody tries to use the camera (riskier), and,
 * क्रम load-समय allocation, how big they should be.
 *
 * The controller can cycle through three buffers.  We could use
 * more by flipping poपूर्णांकers around, but it probably makes little
 * sense.
 */

अटल bool alloc_bufs_at_पढ़ो;
module_param(alloc_bufs_at_पढ़ो, bool, 0444);
MODULE_PARM_DESC(alloc_bufs_at_पढ़ो,
		"Non-zero value causes DMA buffers to be allocated when the video capture device is read, rather than at module load time.  This saves memory, but decreases the chances of successfully getting those buffers.  This parameter is only used in the vmalloc buffer mode");

अटल पूर्णांक n_dma_bufs = 3;
module_param(n_dma_bufs, uपूर्णांक, 0644);
MODULE_PARM_DESC(n_dma_bufs,
		"The number of DMA buffers to allocate.  Can be either two (saves memory, makes timing tighter) or three.");

अटल पूर्णांक dma_buf_size = VGA_WIDTH * VGA_HEIGHT * 2;  /* Worst हाल */
module_param(dma_buf_size, uपूर्णांक, 0444);
MODULE_PARM_DESC(dma_buf_size,
		"The size of the allocated DMA buffers.  If actual operating parameters require larger buffers, an attempt to reallocate will be made.");
#अन्यथा /* MCAM_MODE_VMALLOC */
अटल स्थिर bool alloc_bufs_at_पढ़ो;
अटल स्थिर पूर्णांक n_dma_bufs = 3;  /* Used by S/G_PARM */
#पूर्ण_अगर /* MCAM_MODE_VMALLOC */

अटल bool flip;
module_param(flip, bool, 0444);
MODULE_PARM_DESC(flip,
		"If set, the sensor will be instructed to flip the image vertically.");

अटल पूर्णांक buffer_mode = -1;
module_param(buffer_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(buffer_mode,
		"Set the buffer mode to be used; default is to go with what the platform driver asks for.  Set to 0 for vmalloc, 1 for DMA contiguous.");

/*
 * Status flags.  Always manipulated with bit operations.
 */
#घोषणा CF_BUF0_VALID	 0	/* Buffers valid - first three */
#घोषणा CF_BUF1_VALID	 1
#घोषणा CF_BUF2_VALID	 2
#घोषणा CF_DMA_ACTIVE	 3	/* A frame is incoming */
#घोषणा CF_CONFIG_NEEDED 4	/* Must configure hardware */
#घोषणा CF_SINGLE_BUFFER 5	/* Running with a single buffer */
#घोषणा CF_SG_RESTART	 6	/* SG restart needed */
#घोषणा CF_FRAME_SOF0	 7	/* Frame 0 started */
#घोषणा CF_FRAME_SOF1	 8
#घोषणा CF_FRAME_SOF2	 9

#घोषणा sensor_call(cam, o, f, args...) \
	v4l2_subdev_call(cam->sensor, o, f, ##args)

#घोषणा notअगरier_to_mcam(notअगरier) \
	container_of(notअगरier, काष्ठा mcam_camera, notअगरier)

अटल काष्ठा mcam_क्रमmat_काष्ठा अणु
	__u32 pixelक्रमmat;
	पूर्णांक bpp;   /* Bytes per pixel */
	bool planar;
	u32 mbus_code;
पूर्ण mcam_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 2,
		.planar		= false,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVYU,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 2,
		.planar		= false,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV420,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 1,
		.planar		= true,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVU420,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 1,
		.planar		= true,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_XRGB444,
		.mbus_code	= MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE,
		.bpp		= 2,
		.planar		= false,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB565,
		.mbus_code	= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.bpp		= 2,
		.planar		= false,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_SBGGR8,
		.mbus_code	= MEDIA_BUS_FMT_SBGGR8_1X8,
		.bpp		= 1,
		.planar		= false,
	पूर्ण,
पूर्ण;
#घोषणा N_MCAM_FMTS ARRAY_SIZE(mcam_क्रमmats)

अटल काष्ठा mcam_क्रमmat_काष्ठा *mcam_find_क्रमmat(u32 pixelक्रमmat)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < N_MCAM_FMTS; i++)
		अगर (mcam_क्रमmats[i].pixelक्रमmat == pixelक्रमmat)
			वापस mcam_क्रमmats + i;
	/* Not found? Then वापस the first क्रमmat. */
	वापस mcam_क्रमmats;
पूर्ण

/*
 * The शेष क्रमmat we use until somebody says otherwise.
 */
अटल स्थिर काष्ठा v4l2_pix_क्रमmat mcam_def_pix_क्रमmat = अणु
	.width		= VGA_WIDTH,
	.height		= VGA_HEIGHT,
	.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
	.field		= V4L2_FIELD_NONE,
	.bytesperline	= VGA_WIDTH*2,
	.sizeimage	= VGA_WIDTH*VGA_HEIGHT*2,
	.colorspace	= V4L2_COLORSPACE_SRGB,
पूर्ण;

अटल स्थिर u32 mcam_def_mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;


/*
 * The two-word DMA descriptor क्रमmat used by the Armada 610 and like.  There
 * Is a three-word क्रमmat as well (set C1_DESC_3WORD) where the third
 * word is a poपूर्णांकer to the next descriptor, but we करोn't use it.  Two-word
 * descriptors have to be contiguous in memory.
 */
काष्ठा mcam_dma_desc अणु
	u32 dma_addr;
	u32 segment_len;
पूर्ण;

/*
 * Our buffer type क्रम working with videobuf2.  Note that the vb2
 * developers have decreed that काष्ठा vb2_v4l2_buffer must be at the
 * beginning of this काष्ठाure.
 */
काष्ठा mcam_vb_buffer अणु
	काष्ठा vb2_v4l2_buffer vb_buf;
	काष्ठा list_head queue;
	काष्ठा mcam_dma_desc *dma_desc;	/* Descriptor भव address */
	dma_addr_t dma_desc_pa;		/* Descriptor physical address */
पूर्ण;

अटल अंतरभूत काष्ठा mcam_vb_buffer *vb_to_mvb(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा mcam_vb_buffer, vb_buf);
पूर्ण

/*
 * Hand a completed buffer back to user space.
 */
अटल व्योम mcam_buffer_करोne(काष्ठा mcam_camera *cam, पूर्णांक frame,
		काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	vbuf->vb2_buf.planes[0].bytesused = cam->pix_क्रमmat.sizeimage;
	vbuf->sequence = cam->buf_seq[frame];
	vbuf->field = V4L2_FIELD_NONE;
	vbuf->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&vbuf->vb2_buf, 0, cam->pix_क्रमmat.sizeimage);
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण



/*
 * Debugging and related.
 */
#घोषणा cam_err(cam, fmt, arg...) \
	dev_err((cam)->dev, fmt, ##arg);
#घोषणा cam_warn(cam, fmt, arg...) \
	dev_warn((cam)->dev, fmt, ##arg);
#घोषणा cam_dbg(cam, fmt, arg...) \
	dev_dbg((cam)->dev, fmt, ##arg);


/*
 * Flag manipulation helpers
 */
अटल व्योम mcam_reset_buffers(काष्ठा mcam_camera *cam)
अणु
	पूर्णांक i;

	cam->next_buf = -1;
	क्रम (i = 0; i < cam->nbufs; i++) अणु
		clear_bit(i, &cam->flags);
		clear_bit(CF_FRAME_SOF0 + i, &cam->flags);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक mcam_needs_config(काष्ठा mcam_camera *cam)
अणु
	वापस test_bit(CF_CONFIG_NEEDED, &cam->flags);
पूर्ण

अटल व्योम mcam_set_config_needed(काष्ठा mcam_camera *cam, पूर्णांक needed)
अणु
	अगर (needed)
		set_bit(CF_CONFIG_NEEDED, &cam->flags);
	अन्यथा
		clear_bit(CF_CONFIG_NEEDED, &cam->flags);
पूर्ण

/* ------------------------------------------------------------------- */
/*
 * Make the controller start grabbing images.  Everything must
 * be set up beक्रमe करोing this.
 */
अटल व्योम mcam_ctlr_start(काष्ठा mcam_camera *cam)
अणु
	/* set_bit perक्रमms a पढ़ो, so no other barrier should be
	   needed here */
	mcam_reg_set_bit(cam, REG_CTRL0, C0_ENABLE);
पूर्ण

अटल व्योम mcam_ctlr_stop(काष्ठा mcam_camera *cam)
अणु
	mcam_reg_clear_bit(cam, REG_CTRL0, C0_ENABLE);
पूर्ण

अटल व्योम mcam_enable_mipi(काष्ठा mcam_camera *mcam)
अणु
	/* Using MIPI mode and enable MIPI */
	अगर (mcam->calc_dphy)
		mcam->calc_dphy(mcam);
	cam_dbg(mcam, "camera: DPHY3=0x%x, DPHY5=0x%x, DPHY6=0x%x\n",
			mcam->dphy[0], mcam->dphy[1], mcam->dphy[2]);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY3, mcam->dphy[0]);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY5, mcam->dphy[1]);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY6, mcam->dphy[2]);

	अगर (!mcam->mipi_enabled) अणु
		अगर (mcam->lane > 4 || mcam->lane <= 0) अणु
			cam_warn(mcam, "lane number error\n");
			mcam->lane = 1;	/* set the शेष value */
		पूर्ण
		/*
		 * 0x41 actives 1 lane
		 * 0x43 actives 2 lanes
		 * 0x45 actives 3 lanes (never happen)
		 * 0x47 actives 4 lanes
		 */
		mcam_reg_ग_लिखो(mcam, REG_CSI2_CTRL0,
			CSI2_C0_MIPI_EN | CSI2_C0_ACT_LANE(mcam->lane));
		mcam->mipi_enabled = true;
	पूर्ण
पूर्ण

अटल व्योम mcam_disable_mipi(काष्ठा mcam_camera *mcam)
अणु
	/* Using Parallel mode or disable MIPI */
	mcam_reg_ग_लिखो(mcam, REG_CSI2_CTRL0, 0x0);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY3, 0x0);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY5, 0x0);
	mcam_reg_ग_लिखो(mcam, REG_CSI2_DPHY6, 0x0);
	mcam->mipi_enabled = false;
पूर्ण

अटल bool mcam_fmt_is_planar(__u32 pfmt)
अणु
	काष्ठा mcam_क्रमmat_काष्ठा *f;

	f = mcam_find_क्रमmat(pfmt);
	वापस f->planar;
पूर्ण

अटल व्योम mcam_ग_लिखो_yuv_bases(काष्ठा mcam_camera *cam,
				 अचिन्हित frame, dma_addr_t base)
अणु
	काष्ठा v4l2_pix_क्रमmat *fmt = &cam->pix_क्रमmat;
	u32 pixel_count = fmt->width * fmt->height;
	dma_addr_t y, u = 0, v = 0;

	y = base;

	चयन (fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		u = y + pixel_count;
		v = u + pixel_count / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YVU420:
		v = y + pixel_count;
		u = v + pixel_count / 4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mcam_reg_ग_लिखो(cam, REG_Y0BAR + frame * 4, y);
	अगर (mcam_fmt_is_planar(fmt->pixelक्रमmat)) अणु
		mcam_reg_ग_लिखो(cam, REG_U0BAR + frame * 4, u);
		mcam_reg_ग_लिखो(cam, REG_V0BAR + frame * 4, v);
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------- */

#अगर_घोषित MCAM_MODE_VMALLOC
/*
 * Code specअगरic to the vदो_स्मृति buffer mode.
 */

/*
 * Allocate in-kernel DMA buffers क्रम vदो_स्मृति mode.
 */
अटल पूर्णांक mcam_alloc_dma_bufs(काष्ठा mcam_camera *cam, पूर्णांक loadसमय)
अणु
	पूर्णांक i;

	mcam_set_config_needed(cam, 1);
	अगर (loadसमय)
		cam->dma_buf_size = dma_buf_size;
	अन्यथा
		cam->dma_buf_size = cam->pix_क्रमmat.sizeimage;
	अगर (n_dma_bufs > 3)
		n_dma_bufs = 3;

	cam->nbufs = 0;
	क्रम (i = 0; i < n_dma_bufs; i++) अणु
		cam->dma_bufs[i] = dma_alloc_coherent(cam->dev,
				cam->dma_buf_size, cam->dma_handles + i,
				GFP_KERNEL);
		अगर (cam->dma_bufs[i] == शून्य) अणु
			cam_warn(cam, "Failed to allocate DMA buffer\n");
			अवरोध;
		पूर्ण
		(cam->nbufs)++;
	पूर्ण

	चयन (cam->nbufs) अणु
	हाल 1:
		dma_मुक्त_coherent(cam->dev, cam->dma_buf_size,
				cam->dma_bufs[0], cam->dma_handles[0]);
		cam->nbufs = 0;
		fallthrough;
	हाल 0:
		cam_err(cam, "Insufficient DMA buffers, cannot operate\n");
		वापस -ENOMEM;

	हाल 2:
		अगर (n_dma_bufs > 2)
			cam_warn(cam, "Will limp along with only 2 buffers\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mcam_मुक्त_dma_bufs(काष्ठा mcam_camera *cam)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cam->nbufs; i++) अणु
		dma_मुक्त_coherent(cam->dev, cam->dma_buf_size,
				cam->dma_bufs[i], cam->dma_handles[i]);
		cam->dma_bufs[i] = शून्य;
	पूर्ण
	cam->nbufs = 0;
पूर्ण


/*
 * Set up DMA buffers when operating in vदो_स्मृति mode
 */
अटल व्योम mcam_ctlr_dma_vदो_स्मृति(काष्ठा mcam_camera *cam)
अणु
	/*
	 * Store the first two YUV buffers. Then either
	 * set the third अगर it exists, or tell the controller
	 * to just use two.
	 */
	mcam_ग_लिखो_yuv_bases(cam, 0, cam->dma_handles[0]);
	mcam_ग_लिखो_yuv_bases(cam, 1, cam->dma_handles[1]);
	अगर (cam->nbufs > 2) अणु
		mcam_ग_लिखो_yuv_bases(cam, 2, cam->dma_handles[2]);
		mcam_reg_clear_bit(cam, REG_CTRL1, C1_TWOBUFS);
	पूर्ण अन्यथा
		mcam_reg_set_bit(cam, REG_CTRL1, C1_TWOBUFS);
	अगर (cam->chip_id == MCAM_CAFE)
		mcam_reg_ग_लिखो(cam, REG_UBAR, 0); /* 32 bits only */
पूर्ण

/*
 * Copy data out to user space in the vदो_स्मृति हाल
 */
अटल व्योम mcam_frame_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mcam_camera *cam = from_tasklet(cam, t, s_tasklet);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा mcam_vb_buffer *buf;

	spin_lock_irqsave(&cam->dev_lock, flags);
	क्रम (i = 0; i < cam->nbufs; i++) अणु
		पूर्णांक bufno = cam->next_buf;

		अगर (cam->state != S_STREAMING || bufno < 0)
			अवरोध;  /* I/O got stopped */
		अगर (++(cam->next_buf) >= cam->nbufs)
			cam->next_buf = 0;
		अगर (!test_bit(bufno, &cam->flags))
			जारी;
		अगर (list_empty(&cam->buffers)) अणु
			cam->frame_state.singles++;
			अवरोध;  /* Leave it valid, hope क्रम better later */
		पूर्ण
		cam->frame_state.delivered++;
		clear_bit(bufno, &cam->flags);
		buf = list_first_entry(&cam->buffers, काष्ठा mcam_vb_buffer,
				queue);
		list_del_init(&buf->queue);
		/*
		 * Drop the lock during the big copy.  This *should* be safe...
		 */
		spin_unlock_irqrestore(&cam->dev_lock, flags);
		स_नकल(vb2_plane_vaddr(&buf->vb_buf.vb2_buf, 0),
				cam->dma_bufs[bufno],
				cam->pix_क्रमmat.sizeimage);
		mcam_buffer_करोne(cam, bufno, &buf->vb_buf);
		spin_lock_irqsave(&cam->dev_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&cam->dev_lock, flags);
पूर्ण


/*
 * Make sure our allocated buffers are up to the task.
 */
अटल पूर्णांक mcam_check_dma_buffers(काष्ठा mcam_camera *cam)
अणु
	अगर (cam->nbufs > 0 && cam->dma_buf_size < cam->pix_क्रमmat.sizeimage)
			mcam_मुक्त_dma_bufs(cam);
	अगर (cam->nbufs == 0)
		वापस mcam_alloc_dma_bufs(cam, 0);
	वापस 0;
पूर्ण

अटल व्योम mcam_vदो_स्मृति_करोne(काष्ठा mcam_camera *cam, पूर्णांक frame)
अणु
	tasklet_schedule(&cam->s_tasklet);
पूर्ण

#अन्यथा /* MCAM_MODE_VMALLOC */

अटल अंतरभूत पूर्णांक mcam_alloc_dma_bufs(काष्ठा mcam_camera *cam, पूर्णांक loadसमय)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mcam_मुक्त_dma_bufs(काष्ठा mcam_camera *cam)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक mcam_check_dma_buffers(काष्ठा mcam_camera *cam)
अणु
	वापस 0;
पूर्ण



#पूर्ण_अगर /* MCAM_MODE_VMALLOC */


#अगर_घोषित MCAM_MODE_DMA_CONTIG
/* ---------------------------------------------------------------------- */
/*
 * DMA-contiguous code.
 */

/*
 * Set up a contiguous buffer क्रम the given frame.  Here also is where
 * the underrun strategy is set: अगर there is no buffer available, reuse
 * the buffer from the other BAR and set the CF_SINGLE_BUFFER flag to
 * keep the पूर्णांकerrupt handler from giving that buffer back to user
 * space.  In this way, we always have a buffer to DMA to and करोn't
 * have to try to play games stopping and restarting the controller.
 */
अटल व्योम mcam_set_contig_buffer(काष्ठा mcam_camera *cam, पूर्णांक frame)
अणु
	काष्ठा mcam_vb_buffer *buf;
	dma_addr_t dma_handle;
	काष्ठा vb2_v4l2_buffer *vb;

	/*
	 * If there are no available buffers, go पूर्णांकo single mode
	 */
	अगर (list_empty(&cam->buffers)) अणु
		buf = cam->vb_bufs[frame ^ 0x1];
		set_bit(CF_SINGLE_BUFFER, &cam->flags);
		cam->frame_state.singles++;
	पूर्ण अन्यथा अणु
		/*
		 * OK, we have a buffer we can use.
		 */
		buf = list_first_entry(&cam->buffers, काष्ठा mcam_vb_buffer,
					queue);
		list_del_init(&buf->queue);
		clear_bit(CF_SINGLE_BUFFER, &cam->flags);
	पूर्ण

	cam->vb_bufs[frame] = buf;
	vb = &buf->vb_buf;

	dma_handle = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);
	mcam_ग_लिखो_yuv_bases(cam, frame, dma_handle);
पूर्ण

/*
 * Initial B_DMA_contig setup.
 */
अटल व्योम mcam_ctlr_dma_contig(काष्ठा mcam_camera *cam)
अणु
	mcam_reg_set_bit(cam, REG_CTRL1, C1_TWOBUFS);
	cam->nbufs = 2;
	mcam_set_contig_buffer(cam, 0);
	mcam_set_contig_buffer(cam, 1);
पूर्ण

/*
 * Frame completion handling.
 */
अटल व्योम mcam_dma_contig_करोne(काष्ठा mcam_camera *cam, पूर्णांक frame)
अणु
	काष्ठा mcam_vb_buffer *buf = cam->vb_bufs[frame];

	अगर (!test_bit(CF_SINGLE_BUFFER, &cam->flags)) अणु
		cam->frame_state.delivered++;
		cam->vb_bufs[frame] = शून्य;
		mcam_buffer_करोne(cam, frame, &buf->vb_buf);
	पूर्ण
	mcam_set_contig_buffer(cam, frame);
पूर्ण

#पूर्ण_अगर /* MCAM_MODE_DMA_CONTIG */

#अगर_घोषित MCAM_MODE_DMA_SG
/* ---------------------------------------------------------------------- */
/*
 * Scatter/gather-specअगरic code.
 */

/*
 * Set up the next buffer क्रम S/G I/O; caller should be sure that
 * the controller is stopped and a buffer is available.
 */
अटल व्योम mcam_sg_next_buffer(काष्ठा mcam_camera *cam)
अणु
	काष्ठा mcam_vb_buffer *buf;
	काष्ठा sg_table *sg_table;

	buf = list_first_entry(&cam->buffers, काष्ठा mcam_vb_buffer, queue);
	list_del_init(&buf->queue);
	sg_table = vb2_dma_sg_plane_desc(&buf->vb_buf.vb2_buf, 0);
	/*
	 * Very Bad Not Good Things happen अगर you करोn't clear
	 * C1_DESC_ENA beक्रमe making any descriptor changes.
	 */
	mcam_reg_clear_bit(cam, REG_CTRL1, C1_DESC_ENA);
	mcam_reg_ग_लिखो(cam, REG_DMA_DESC_Y, buf->dma_desc_pa);
	mcam_reg_ग_लिखो(cam, REG_DESC_LEN_Y,
			sg_table->nents * माप(काष्ठा mcam_dma_desc));
	mcam_reg_ग_लिखो(cam, REG_DESC_LEN_U, 0);
	mcam_reg_ग_लिखो(cam, REG_DESC_LEN_V, 0);
	mcam_reg_set_bit(cam, REG_CTRL1, C1_DESC_ENA);
	cam->vb_bufs[0] = buf;
पूर्ण

/*
 * Initial B_DMA_sg setup
 */
अटल व्योम mcam_ctlr_dma_sg(काष्ठा mcam_camera *cam)
अणु
	/*
	 * The list-empty condition can hit us at resume समय
	 * अगर the buffer list was empty when the प्रणाली was suspended.
	 */
	अगर (list_empty(&cam->buffers)) अणु
		set_bit(CF_SG_RESTART, &cam->flags);
		वापस;
	पूर्ण

	mcam_reg_clear_bit(cam, REG_CTRL1, C1_DESC_3WORD);
	mcam_sg_next_buffer(cam);
	cam->nbufs = 3;
पूर्ण


/*
 * Frame completion with S/G is trickier.  We can't muck with
 * a descriptor chain on the fly, since the controller buffers it
 * पूर्णांकernally.  So we have to actually stop and restart; Marvell
 * says this is the way to करो it.
 *
 * Of course, stopping is easier said than करोne; experience shows
 * that the controller can start a frame *after* C0_ENABLE has been
 * cleared.  So when running in S/G mode, the controller is "stopped"
 * on receipt of the start-of-frame पूर्णांकerrupt.  That means we can
 * safely change the DMA descriptor array here and restart things
 * (assuming there's another buffer रुकोing to go).
 */
अटल व्योम mcam_dma_sg_करोne(काष्ठा mcam_camera *cam, पूर्णांक frame)
अणु
	काष्ठा mcam_vb_buffer *buf = cam->vb_bufs[0];

	/*
	 * If we're no longer supposed to be streaming, don't करो anything.
	 */
	अगर (cam->state != S_STREAMING)
		वापस;
	/*
	 * If we have another buffer available, put it in and
	 * restart the engine.
	 */
	अगर (!list_empty(&cam->buffers)) अणु
		mcam_sg_next_buffer(cam);
		mcam_ctlr_start(cam);
	/*
	 * Otherwise set CF_SG_RESTART and the controller will
	 * be restarted once another buffer shows up.
	 */
	पूर्ण अन्यथा अणु
		set_bit(CF_SG_RESTART, &cam->flags);
		cam->frame_state.singles++;
		cam->vb_bufs[0] = शून्य;
	पूर्ण
	/*
	 * Now we can give the completed frame back to user space.
	 */
	cam->frame_state.delivered++;
	mcam_buffer_करोne(cam, frame, &buf->vb_buf);
पूर्ण


/*
 * Scatter/gather mode requires stopping the controller between
 * frames so we can put in a new DMA descriptor array.  If no new
 * buffer exists at frame completion, the controller is left stopped;
 * this function is अक्षरged with gettig things going again.
 */
अटल व्योम mcam_sg_restart(काष्ठा mcam_camera *cam)
अणु
	mcam_ctlr_dma_sg(cam);
	mcam_ctlr_start(cam);
	clear_bit(CF_SG_RESTART, &cam->flags);
पूर्ण

#अन्यथा /* MCAM_MODE_DMA_SG */

अटल अंतरभूत व्योम mcam_sg_restart(काष्ठा mcam_camera *cam)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर /* MCAM_MODE_DMA_SG */

/* ---------------------------------------------------------------------- */
/*
 * Buffer-mode-independent controller code.
 */

/*
 * Image क्रमmat setup
 */
अटल व्योम mcam_ctlr_image(काष्ठा mcam_camera *cam)
अणु
	काष्ठा v4l2_pix_क्रमmat *fmt = &cam->pix_क्रमmat;
	u32 widthy = 0, widthuv = 0, imgsz_h, imgsz_w;

	cam_dbg(cam, "camera: bytesperline = %d; height = %d\n",
		fmt->bytesperline, fmt->sizeimage / fmt->bytesperline);
	imgsz_h = (fmt->height << IMGSZ_V_SHIFT) & IMGSZ_V_MASK;
	imgsz_w = (fmt->width * 2) & IMGSZ_H_MASK;

	चयन (fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
		widthy = fmt->width * 2;
		widthuv = 0;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		widthy = fmt->width;
		widthuv = fmt->width / 2;
		अवरोध;
	शेष:
		widthy = fmt->bytesperline;
		widthuv = 0;
		अवरोध;
	पूर्ण

	mcam_reg_ग_लिखो_mask(cam, REG_IMGPITCH, widthuv << 16 | widthy,
			IMGP_YP_MASK | IMGP_UVP_MASK);
	mcam_reg_ग_लिखो(cam, REG_IMGSIZE, imgsz_h | imgsz_w);
	mcam_reg_ग_लिखो(cam, REG_IMGOFFSET, 0x0);

	/*
	 * Tell the controller about the image क्रमmat we are using.
	 */
	चयन (fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_YUV | C0_YUV_420PL | C0_YUVE_VYUY, C0_DF_MASK);
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_YUV | C0_YUV_PACKED | C0_YUVE_NOSWAP, C0_DF_MASK);
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_YUV | C0_YUV_PACKED | C0_YUVE_SWAP24, C0_DF_MASK);
		अवरोध;
	हाल V4L2_PIX_FMT_XRGB444:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_RGB | C0_RGBF_444 | C0_RGB4_XBGR, C0_DF_MASK);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_RGB | C0_RGBF_565 | C0_RGB5_BGGR, C0_DF_MASK);
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:
		mcam_reg_ग_लिखो_mask(cam, REG_CTRL0,
			C0_DF_RGB | C0_RGB5_GRBG, C0_DF_MASK);
		अवरोध;
	शेष:
		cam_err(cam, "camera: unknown format: %#x\n", fmt->pixelक्रमmat);
		अवरोध;
	पूर्ण

	/*
	 * Make sure it knows we want to use hsync/vsync.
	 */
	mcam_reg_ग_लिखो_mask(cam, REG_CTRL0, C0_SIF_HVSYNC, C0_SIFM_MASK);
पूर्ण


/*
 * Configure the controller क्रम operation; caller holds the
 * device mutex.
 */
अटल पूर्णांक mcam_ctlr_configure(काष्ठा mcam_camera *cam)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_SG_RESTART, &cam->flags);
	cam->dma_setup(cam);
	mcam_ctlr_image(cam);
	mcam_set_config_needed(cam, 0);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम mcam_ctlr_irq_enable(काष्ठा mcam_camera *cam)
अणु
	/*
	 * Clear any pending पूर्णांकerrupts, since we करो not
	 * expect to have I/O active prior to enabling.
	 */
	mcam_reg_ग_लिखो(cam, REG_IRQSTAT, FRAMEIRQS);
	mcam_reg_set_bit(cam, REG_IRQMASK, FRAMEIRQS);
पूर्ण

अटल व्योम mcam_ctlr_irq_disable(काष्ठा mcam_camera *cam)
अणु
	mcam_reg_clear_bit(cam, REG_IRQMASK, FRAMEIRQS);
पूर्ण

/*
 * Stop the controller, and करोn't return until we're really sure that no
 * further DMA is going on.
 */
अटल व्योम mcam_ctlr_stop_dma(काष्ठा mcam_camera *cam)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Theory: stop the camera controller (whether it is operating
	 * or not).  Delay briefly just in हाल we race with the SOF
	 * पूर्णांकerrupt, then रुको until no DMA is active.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_SG_RESTART, &cam->flags);
	mcam_ctlr_stop(cam);
	cam->state = S_IDLE;
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	/*
	 * This is a brutally दीर्घ sleep, but experience shows that
	 * it can take the controller a जबतक to get the message that
	 * it needs to stop grabbing frames.  In particular, we can
	 * someबार (on mmp) get a frame at the end WITHOUT the
	 * start-of-frame indication.
	 */
	msleep(150);
	अगर (test_bit(CF_DMA_ACTIVE, &cam->flags))
		cam_err(cam, "Timeout waiting for DMA to end\n");
		/* This would be bad news - what now? */
	spin_lock_irqsave(&cam->dev_lock, flags);
	mcam_ctlr_irq_disable(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
पूर्ण

/*
 * Power up and करोwn.
 */
अटल पूर्णांक mcam_ctlr_घातer_up(काष्ठा mcam_camera *cam)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cam->dev_lock, flags);
	अगर (cam->plat_घातer_up) अणु
		ret = cam->plat_घातer_up(cam);
		अगर (ret) अणु
			spin_unlock_irqrestore(&cam->dev_lock, flags);
			वापस ret;
		पूर्ण
	पूर्ण
	mcam_reg_clear_bit(cam, REG_CTRL1, C1_PWRDWN);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम mcam_ctlr_घातer_करोwn(काष्ठा mcam_camera *cam)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	/*
	 * School of hard knocks deparपंचांगent: be sure we करो any रेजिस्टर
	 * twiddling on the controller *beक्रमe* calling the platक्रमm
	 * घातer करोwn routine.
	 */
	mcam_reg_set_bit(cam, REG_CTRL1, C1_PWRDWN);
	अगर (cam->plat_घातer_करोwn)
		cam->plat_घातer_करोwn(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
पूर्ण

/* ---------------------------------------------------------------------- */
/*
 * Master sensor घड़ी.
 */
अटल पूर्णांक mclk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mcam_camera *cam = container_of(hw, काष्ठा mcam_camera, mclk_hw);

	clk_prepare(cam->clk[0]);
	वापस 0;
पूर्ण

अटल व्योम mclk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mcam_camera *cam = container_of(hw, काष्ठा mcam_camera, mclk_hw);

	clk_unprepare(cam->clk[0]);
पूर्ण

अटल पूर्णांक mclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mcam_camera *cam = container_of(hw, काष्ठा mcam_camera, mclk_hw);
	पूर्णांक mclk_src;
	पूर्णांक mclk_भाग;

	/*
	 * Clock the sensor appropriately.  Controller घड़ी should
	 * be 48MHz, sensor "typical" value is half that.
	 */
	अगर (cam->bus_type == V4L2_MBUS_CSI2_DPHY) अणु
		mclk_src = cam->mclk_src;
		mclk_भाग = cam->mclk_भाग;
	पूर्ण अन्यथा अणु
		mclk_src = 3;
		mclk_भाग = 2;
	पूर्ण

	pm_runसमय_get_sync(cam->dev);
	clk_enable(cam->clk[0]);
	mcam_reg_ग_लिखो(cam, REG_CLKCTRL, (mclk_src << 29) | mclk_भाग);
	mcam_ctlr_घातer_up(cam);

	वापस 0;
पूर्ण

अटल व्योम mclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mcam_camera *cam = container_of(hw, काष्ठा mcam_camera, mclk_hw);

	mcam_ctlr_घातer_करोwn(cam);
	clk_disable(cam->clk[0]);
	pm_runसमय_put(cam->dev);
पूर्ण

अटल अचिन्हित दीर्घ mclk_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	वापस 48000000;
पूर्ण

अटल स्थिर काष्ठा clk_ops mclk_ops = अणु
	.prepare = mclk_prepare,
	.unprepare = mclk_unprepare,
	.enable = mclk_enable,
	.disable = mclk_disable,
	.recalc_rate = mclk_recalc_rate,
पूर्ण;

/* -------------------------------------------------------------------- */
/*
 * Communications with the sensor.
 */

अटल पूर्णांक __mcam_cam_reset(काष्ठा mcam_camera *cam)
अणु
	वापस sensor_call(cam, core, reset, 0);
पूर्ण

/*
 * We have found the sensor on the i2c.  Let's try to have a
 * conversation.
 */
अटल पूर्णांक mcam_cam_init(काष्ठा mcam_camera *cam)
अणु
	पूर्णांक ret;

	अगर (cam->state != S_NOTREADY)
		cam_warn(cam, "Cam init with device in funky state %d",
				cam->state);
	ret = __mcam_cam_reset(cam);
	/* Get/set parameters? */
	cam->state = S_IDLE;
	वापस ret;
पूर्ण

/*
 * Configure the sensor to match the parameters we have.  Caller should
 * hold s_mutex
 */
अटल पूर्णांक mcam_cam_set_flip(काष्ठा mcam_camera *cam)
अणु
	काष्ठा v4l2_control ctrl;

	स_रखो(&ctrl, 0, माप(ctrl));
	ctrl.id = V4L2_CID_VFLIP;
	ctrl.value = flip;
	वापस v4l2_s_ctrl(शून्य, cam->sensor->ctrl_handler, &ctrl);
पूर्ण


अटल पूर्णांक mcam_cam_configure(काष्ठा mcam_camera *cam)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &cam->pix_क्रमmat, cam->mbus_code);
	ret = sensor_call(cam, core, init, 0);
	अगर (ret == 0)
		ret = sensor_call(cam, pad, set_fmt, शून्य, &क्रमmat);
	/*
	 * OV7670 करोes weird things अगर flip is set *beक्रमe* क्रमmat...
	 */
	ret += mcam_cam_set_flip(cam);
	वापस ret;
पूर्ण

/*
 * Get everything पढ़ोy, and start grabbing frames.
 */
अटल पूर्णांक mcam_पढ़ो_setup(काष्ठा mcam_camera *cam)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	/*
	 * Configuration.  If we still करोn't have DMA buffers,
	 * make one last, desperate attempt.
	 */
	अगर (cam->buffer_mode == B_vदो_स्मृति && cam->nbufs == 0 &&
			mcam_alloc_dma_bufs(cam, 0))
		वापस -ENOMEM;

	अगर (mcam_needs_config(cam)) अणु
		mcam_cam_configure(cam);
		ret = mcam_ctlr_configure(cam);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Turn it loose.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	mcam_reset_buffers(cam);
	अगर (cam->bus_type == V4L2_MBUS_CSI2_DPHY)
		mcam_enable_mipi(cam);
	अन्यथा
		mcam_disable_mipi(cam);
	mcam_ctlr_irq_enable(cam);
	cam->state = S_STREAMING;
	अगर (!test_bit(CF_SG_RESTART, &cam->flags))
		mcam_ctlr_start(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */
/*
 * Videobuf2 पूर्णांकerface code.
 */

अटल पूर्णांक mcam_vb_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbufs,
		अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
		काष्ठा device *alloc_devs[])
अणु
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vq);
	पूर्णांक minbufs = (cam->buffer_mode == B_DMA_contig) ? 3 : 2;
	अचिन्हित size = cam->pix_क्रमmat.sizeimage;

	अगर (*nbufs < minbufs)
		*nbufs = minbufs;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;
	sizes[0] = size;
	*num_planes = 1; /* Someday we have to support planar क्रमmats... */
	वापस 0;
पूर्ण


अटल व्योम mcam_vb_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mcam_vb_buffer *mvb = vb_to_mvb(vbuf);
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags;
	पूर्णांक start;

	spin_lock_irqsave(&cam->dev_lock, flags);
	start = (cam->state == S_BUFWAIT) && !list_empty(&cam->buffers);
	list_add(&mvb->queue, &cam->buffers);
	अगर (cam->state == S_STREAMING && test_bit(CF_SG_RESTART, &cam->flags))
		mcam_sg_restart(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	अगर (start)
		mcam_पढ़ो_setup(cam);
पूर्ण

अटल व्योम mcam_vb_requeue_bufs(काष्ठा vb2_queue *vq,
				 क्रमागत vb2_buffer_state state)
अणु
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vq);
	काष्ठा mcam_vb_buffer *buf, *node;
	अचिन्हित दीर्घ flags;
	अचिन्हित i;

	spin_lock_irqsave(&cam->dev_lock, flags);
	list_क्रम_each_entry_safe(buf, node, &cam->buffers, queue) अणु
		vb2_buffer_करोne(&buf->vb_buf.vb2_buf, state);
		list_del(&buf->queue);
	पूर्ण
	क्रम (i = 0; i < MAX_DMA_BUFS; i++) अणु
		buf = cam->vb_bufs[i];

		अगर (buf) अणु
			vb2_buffer_करोne(&buf->vb_buf.vb2_buf, state);
			cam->vb_bufs[i] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cam->dev_lock, flags);
पूर्ण

/*
 * These need to be called with the mutex held from vb2
 */
अटल पूर्णांक mcam_vb_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक frame;
	पूर्णांक ret;

	अगर (cam->state != S_IDLE) अणु
		mcam_vb_requeue_bufs(vq, VB2_BUF_STATE_QUEUED);
		वापस -EINVAL;
	पूर्ण
	cam->frame_state.frames = 0;
	cam->frame_state.singles = 0;
	cam->frame_state.delivered = 0;
	cam->sequence = 0;
	/*
	 * Videobuf2 sneakily hoards all the buffers and won't
	 * give them to us until *after* streaming starts.  But
	 * we can't actually start streaming until we have a
	 * destination.  So go पूर्णांकo a रुको state and hope they
	 * give us buffers soon.
	 */
	अगर (cam->buffer_mode != B_vदो_स्मृति && list_empty(&cam->buffers)) अणु
		cam->state = S_BUFWAIT;
		वापस 0;
	पूर्ण

	/*
	 * Ensure clear the left over frame flags
	 * beक्रमe every really start streaming
	 */
	क्रम (frame = 0; frame < cam->nbufs; frame++)
		clear_bit(CF_FRAME_SOF0 + frame, &cam->flags);

	ret = mcam_पढ़ो_setup(cam);
	अगर (ret)
		mcam_vb_requeue_bufs(vq, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम mcam_vb_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vq);

	cam_dbg(cam, "stop_streaming: %d frames, %d singles, %d delivered\n",
			cam->frame_state.frames, cam->frame_state.singles,
			cam->frame_state.delivered);
	अगर (cam->state == S_BUFWAIT) अणु
		/* They never gave us buffers */
		cam->state = S_IDLE;
		वापस;
	पूर्ण
	अगर (cam->state != S_STREAMING)
		वापस;
	mcam_ctlr_stop_dma(cam);
	/*
	 * VB2 reclaims the buffers, so we need to क्रमget
	 * about them.
	 */
	mcam_vb_requeue_bufs(vq, VB2_BUF_STATE_ERROR);
पूर्ण


अटल स्थिर काष्ठा vb2_ops mcam_vb2_ops = अणु
	.queue_setup		= mcam_vb_queue_setup,
	.buf_queue		= mcam_vb_buf_queue,
	.start_streaming	= mcam_vb_start_streaming,
	.stop_streaming		= mcam_vb_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;


#अगर_घोषित MCAM_MODE_DMA_SG
/*
 * Scatter/gather mode uses all of the above functions plus a
 * few extras to deal with DMA mapping.
 */
अटल पूर्णांक mcam_vb_sg_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mcam_vb_buffer *mvb = vb_to_mvb(vbuf);
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	पूर्णांक ndesc = cam->pix_क्रमmat.sizeimage/PAGE_SIZE + 1;

	mvb->dma_desc = dma_alloc_coherent(cam->dev,
			ndesc * माप(काष्ठा mcam_dma_desc),
			&mvb->dma_desc_pa, GFP_KERNEL);
	अगर (mvb->dma_desc == शून्य) अणु
		cam_err(cam, "Unable to get DMA descriptor array\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vb_sg_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mcam_vb_buffer *mvb = vb_to_mvb(vbuf);
	काष्ठा sg_table *sg_table = vb2_dma_sg_plane_desc(vb, 0);
	काष्ठा mcam_dma_desc *desc = mvb->dma_desc;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sg_table->sgl, sg, sg_table->nents, i) अणु
		desc->dma_addr = sg_dma_address(sg);
		desc->segment_len = sg_dma_len(sg);
		desc++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mcam_vb_sg_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mcam_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mcam_vb_buffer *mvb = vb_to_mvb(vbuf);
	पूर्णांक ndesc = cam->pix_क्रमmat.sizeimage/PAGE_SIZE + 1;

	dma_मुक्त_coherent(cam->dev, ndesc * माप(काष्ठा mcam_dma_desc),
			mvb->dma_desc, mvb->dma_desc_pa);
पूर्ण


अटल स्थिर काष्ठा vb2_ops mcam_vb2_sg_ops = अणु
	.queue_setup		= mcam_vb_queue_setup,
	.buf_init		= mcam_vb_sg_buf_init,
	.buf_prepare		= mcam_vb_sg_buf_prepare,
	.buf_queue		= mcam_vb_buf_queue,
	.buf_cleanup		= mcam_vb_sg_buf_cleanup,
	.start_streaming	= mcam_vb_start_streaming,
	.stop_streaming		= mcam_vb_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

#पूर्ण_अगर /* MCAM_MODE_DMA_SG */

अटल पूर्णांक mcam_setup_vb2(काष्ठा mcam_camera *cam)
अणु
	काष्ठा vb2_queue *vq = &cam->vb_queue;

	स_रखो(vq, 0, माप(*vq));
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->drv_priv = cam;
	vq->lock = &cam->s_mutex;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	vq->buf_काष्ठा_size = माप(काष्ठा mcam_vb_buffer);
	vq->dev = cam->dev;
	INIT_LIST_HEAD(&cam->buffers);
	चयन (cam->buffer_mode) अणु
	हाल B_DMA_contig:
#अगर_घोषित MCAM_MODE_DMA_CONTIG
		vq->ops = &mcam_vb2_ops;
		vq->mem_ops = &vb2_dma_contig_memops;
		cam->dma_setup = mcam_ctlr_dma_contig;
		cam->frame_complete = mcam_dma_contig_करोne;
#पूर्ण_अगर
		अवरोध;
	हाल B_DMA_sg:
#अगर_घोषित MCAM_MODE_DMA_SG
		vq->ops = &mcam_vb2_sg_ops;
		vq->mem_ops = &vb2_dma_sg_memops;
		cam->dma_setup = mcam_ctlr_dma_sg;
		cam->frame_complete = mcam_dma_sg_करोne;
#पूर्ण_अगर
		अवरोध;
	हाल B_vदो_स्मृति:
#अगर_घोषित MCAM_MODE_VMALLOC
		tasklet_setup(&cam->s_tasklet, mcam_frame_tasklet);
		vq->ops = &mcam_vb2_ops;
		vq->mem_ops = &vb2_vदो_स्मृति_memops;
		cam->dma_setup = mcam_ctlr_dma_vदो_स्मृति;
		cam->frame_complete = mcam_vदो_स्मृति_करोne;
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	वापस vb2_queue_init(vq);
पूर्ण


/* ---------------------------------------------------------------------- */
/*
 * The दीर्घ list of V4L2 ioctl() operations.
 */

अटल पूर्णांक mcam_vidioc_querycap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_capability *cap)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(file);

	strscpy(cap->driver, "marvell_ccic", माप(cap->driver));
	strscpy(cap->card, "marvell_ccic", माप(cap->card));
	strscpy(cap->bus_info, cam->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण


अटल पूर्णांक mcam_vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_fmtdesc *fmt)
अणु
	अगर (fmt->index >= N_MCAM_FMTS)
		वापस -EINVAL;
	fmt->pixelक्रमmat = mcam_क्रमmats[fmt->index].pixelक्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vidioc_try_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	काष्ठा mcam_क्रमmat_काष्ठा *f;
	काष्ठा v4l2_pix_क्रमmat *pix = &fmt->fmt.pix;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	पूर्णांक ret;

	f = mcam_find_क्रमmat(pix->pixelक्रमmat);
	pix->pixelक्रमmat = f->pixelक्रमmat;
	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pix, f->mbus_code);
	ret = sensor_call(cam, pad, set_fmt, &pad_cfg, &क्रमmat);
	v4l2_fill_pix_क्रमmat(pix, &क्रमmat.क्रमmat);
	pix->bytesperline = pix->width * f->bpp;
	चयन (f->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		pix->sizeimage = pix->height * pix->bytesperline * 3 / 2;
		अवरोध;
	शेष:
		pix->sizeimage = pix->height * pix->bytesperline;
		अवरोध;
	पूर्ण
	pix->colorspace = V4L2_COLORSPACE_SRGB;
	वापस ret;
पूर्ण

अटल पूर्णांक mcam_vidioc_s_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	काष्ठा mcam_क्रमmat_काष्ठा *f;
	पूर्णांक ret;

	/*
	 * Can't करो anything अगर the device is not idle
	 * Also can't अगर there are streaming buffers in place.
	 */
	अगर (cam->state != S_IDLE || vb2_is_busy(&cam->vb_queue))
		वापस -EBUSY;

	f = mcam_find_क्रमmat(fmt->fmt.pix.pixelक्रमmat);

	/*
	 * See अगर the क्रमmatting works in principle.
	 */
	ret = mcam_vidioc_try_fmt_vid_cap(filp, priv, fmt);
	अगर (ret)
		वापस ret;
	/*
	 * Now we start to change things क्रम real, so let's करो it
	 * under lock.
	 */
	cam->pix_क्रमmat = fmt->fmt.pix;
	cam->mbus_code = f->mbus_code;

	/*
	 * Make sure we have appropriate DMA buffers.
	 */
	अगर (cam->buffer_mode == B_vदो_स्मृति) अणु
		ret = mcam_check_dma_buffers(cam);
		अगर (ret)
			जाओ out;
	पूर्ण
	mcam_set_config_needed(cam, 1);
out:
	वापस ret;
पूर्ण

/*
 * Return our stored notion of how the camera is/should be configured.
 * The V4l2 spec wants us to be smarter, and actually get this from
 * the camera (and not mess with it at खोलो समय).  Someday.
 */
अटल पूर्णांक mcam_vidioc_g_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);

	f->fmt.pix = cam->pix_क्रमmat;
	वापस 0;
पूर्ण

/*
 * We only have one input - the sensor - so minimize the nonsense here.
 */
अटल पूर्णांक mcam_vidioc_क्रमागत_input(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_input *input)
अणु
	अगर (input->index != 0)
		वापस -EINVAL;

	input->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(input->name, "Camera", माप(input->name));
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vidioc_g_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vidioc_s_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * G/S_PARM.  Most of this is करोne by the sensor, but we are
 * the level which controls the number of पढ़ो buffers.
 */
अटल पूर्णांक mcam_vidioc_g_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	पूर्णांक ret;

	ret = v4l2_g_parm_cap(video_devdata(filp), cam->sensor, a);
	a->parm.capture.पढ़ोbuffers = n_dma_bufs;
	वापस ret;
पूर्ण

अटल पूर्णांक mcam_vidioc_s_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	पूर्णांक ret;

	ret = v4l2_s_parm_cap(video_devdata(filp), cam->sensor, a);
	a->parm.capture.पढ़ोbuffers = n_dma_bufs;
	वापस ret;
पूर्ण

अटल पूर्णांक mcam_vidioc_क्रमागत_framesizes(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_frmsizeक्रमागत *sizes)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	काष्ठा mcam_क्रमmat_काष्ठा *f;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.index = sizes->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	f = mcam_find_क्रमmat(sizes->pixel_क्रमmat);
	अगर (f->pixelक्रमmat != sizes->pixel_क्रमmat)
		वापस -EINVAL;
	fse.code = f->mbus_code;
	ret = sensor_call(cam, pad, क्रमागत_frame_size, शून्य, &fse);
	अगर (ret)
		वापस ret;
	अगर (fse.min_width == fse.max_width &&
	    fse.min_height == fse.max_height) अणु
		sizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		sizes->discrete.width = fse.min_width;
		sizes->discrete.height = fse.min_height;
		वापस 0;
	पूर्ण
	sizes->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = fse.min_width;
	sizes->stepwise.max_width = fse.max_width;
	sizes->stepwise.min_height = fse.min_height;
	sizes->stepwise.max_height = fse.max_height;
	sizes->stepwise.step_width = 1;
	sizes->stepwise.step_height = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_frmivalक्रमागत *पूर्णांकerval)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	काष्ठा mcam_क्रमmat_काष्ठा *f;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = पूर्णांकerval->index,
		.width = पूर्णांकerval->width,
		.height = पूर्णांकerval->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	f = mcam_find_क्रमmat(पूर्णांकerval->pixel_क्रमmat);
	अगर (f->pixelक्रमmat != पूर्णांकerval->pixel_क्रमmat)
		वापस -EINVAL;
	fie.code = f->mbus_code;
	ret = sensor_call(cam, pad, क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;
	पूर्णांकerval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	पूर्णांकerval->discrete = fie.पूर्णांकerval;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mcam_vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(file);

	अगर (reg->reg > cam->regs_size - 4)
		वापस -EINVAL;
	reg->val = mcam_reg_पढ़ो(cam, reg->reg);
	reg->size = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक mcam_vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(file);

	अगर (reg->reg > cam->regs_size - 4)
		वापस -EINVAL;
	mcam_reg_ग_लिखो(cam, reg->reg, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ioctl_ops mcam_v4l_ioctl_ops = अणु
	.vidioc_querycap	= mcam_vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = mcam_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= mcam_vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= mcam_vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= mcam_vidioc_g_fmt_vid_cap,
	.vidioc_क्रमागत_input	= mcam_vidioc_क्रमागत_input,
	.vidioc_g_input		= mcam_vidioc_g_input,
	.vidioc_s_input		= mcam_vidioc_s_input,
	.vidioc_reqbufs		= vb2_ioctl_reqbufs,
	.vidioc_create_bufs	= vb2_ioctl_create_bufs,
	.vidioc_querybuf	= vb2_ioctl_querybuf,
	.vidioc_qbuf		= vb2_ioctl_qbuf,
	.vidioc_dqbuf		= vb2_ioctl_dqbuf,
	.vidioc_expbuf		= vb2_ioctl_expbuf,
	.vidioc_streamon	= vb2_ioctl_streamon,
	.vidioc_streamoff	= vb2_ioctl_streamoff,
	.vidioc_g_parm		= mcam_vidioc_g_parm,
	.vidioc_s_parm		= mcam_vidioc_s_parm,
	.vidioc_क्रमागत_framesizes = mcam_vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = mcam_vidioc_क्रमागत_frameपूर्णांकervals,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर	= mcam_vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर	= mcam_vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

/* ---------------------------------------------------------------------- */
/*
 * Our various file operations.
 */
अटल पूर्णांक mcam_v4l_खोलो(काष्ठा file *filp)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	पूर्णांक ret;

	mutex_lock(&cam->s_mutex);
	ret = v4l2_fh_खोलो(filp);
	अगर (ret)
		जाओ out;
	अगर (v4l2_fh_is_singular_file(filp)) अणु
		ret = sensor_call(cam, core, s_घातer, 1);
		अगर (ret)
			जाओ out;
		pm_runसमय_get_sync(cam->dev);
		__mcam_cam_reset(cam);
		mcam_set_config_needed(cam, 1);
	पूर्ण
out:
	mutex_unlock(&cam->s_mutex);
	अगर (ret)
		v4l2_fh_release(filp);
	वापस ret;
पूर्ण


अटल पूर्णांक mcam_v4l_release(काष्ठा file *filp)
अणु
	काष्ठा mcam_camera *cam = video_drvdata(filp);
	bool last_खोलो;

	mutex_lock(&cam->s_mutex);
	last_खोलो = v4l2_fh_is_singular_file(filp);
	_vb2_fop_release(filp, शून्य);
	अगर (last_खोलो) अणु
		mcam_disable_mipi(cam);
		sensor_call(cam, core, s_घातer, 0);
		pm_runसमय_put(cam->dev);
		अगर (cam->buffer_mode == B_vदो_स्मृति && alloc_bufs_at_पढ़ो)
			mcam_मुक्त_dma_bufs(cam);
	पूर्ण

	mutex_unlock(&cam->s_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mcam_v4l_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = mcam_v4l_खोलो,
	.release = mcam_v4l_release,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;


/*
 * This ढाँचा device holds all of those v4l2 methods; we
 * clone it क्रम specअगरic real devices.
 */
अटल स्थिर काष्ठा video_device mcam_v4l_ढाँचा = अणु
	.name = "mcam",
	.fops = &mcam_v4l_fops,
	.ioctl_ops = &mcam_v4l_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		       V4L2_CAP_STREAMING,
पूर्ण;

/* ---------------------------------------------------------------------- */
/*
 * Interrupt handler stuff
 */
अटल व्योम mcam_frame_complete(काष्ठा mcam_camera *cam, पूर्णांक frame)
अणु
	/*
	 * Basic frame housekeeping.
	 */
	set_bit(frame, &cam->flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	cam->next_buf = frame;
	cam->buf_seq[frame] = cam->sequence++;
	cam->frame_state.frames++;
	/*
	 * "This should never happen"
	 */
	अगर (cam->state != S_STREAMING)
		वापस;
	/*
	 * Process the frame and set up the next one.
	 */
	cam->frame_complete(cam, frame);
पूर्ण


/*
 * The पूर्णांकerrupt handler; this needs to be called from the
 * platक्रमm irq handler with the lock held.
 */
पूर्णांक mccic_irq(काष्ठा mcam_camera *cam, अचिन्हित पूर्णांक irqs)
अणु
	अचिन्हित पूर्णांक frame, handled = 0;

	mcam_reg_ग_लिखो(cam, REG_IRQSTAT, FRAMEIRQS); /* Clear'em all */
	/*
	 * Handle any frame completions.  There really should
	 * not be more than one of these, or we have fallen
	 * far behind.
	 *
	 * When running in S/G mode, the frame number lacks any
	 * real meaning - there's only one descriptor array - but
	 * the controller still picks a dअगरferent one to संकेत
	 * each समय.
	 */
	क्रम (frame = 0; frame < cam->nbufs; frame++)
		अगर (irqs & (IRQ_खातापूर्ण0 << frame) &&
			test_bit(CF_FRAME_SOF0 + frame, &cam->flags)) अणु
			mcam_frame_complete(cam, frame);
			handled = 1;
			clear_bit(CF_FRAME_SOF0 + frame, &cam->flags);
			अगर (cam->buffer_mode == B_DMA_sg)
				अवरोध;
		पूर्ण
	/*
	 * If a frame starts, note that we have DMA active.  This
	 * code assumes that we won't get multiple frame पूर्णांकerrupts
	 * at once; may want to rethink that.
	 */
	क्रम (frame = 0; frame < cam->nbufs; frame++) अणु
		अगर (irqs & (IRQ_SOF0 << frame)) अणु
			set_bit(CF_FRAME_SOF0 + frame, &cam->flags);
			handled = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	अगर (handled == IRQ_HANDLED) अणु
		set_bit(CF_DMA_ACTIVE, &cam->flags);
		अगर (cam->buffer_mode == B_DMA_sg)
			mcam_ctlr_stop(cam);
	पूर्ण
	वापस handled;
पूर्ण
EXPORT_SYMBOL_GPL(mccic_irq);

/* ---------------------------------------------------------------------- */
/*
 * Registration and such.
 */

अटल पूर्णांक mccic_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
	काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा mcam_camera *cam = notअगरier_to_mcam(notअगरier);
	पूर्णांक ret;

	mutex_lock(&cam->s_mutex);
	अगर (cam->sensor) अणु
		cam_err(cam, "sensor already bound\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	v4l2_set_subdev_hostdata(subdev, cam);
	cam->sensor = subdev;

	ret = mcam_cam_init(cam);
	अगर (ret) अणु
		cam->sensor = शून्य;
		जाओ out;
	पूर्ण

	ret = mcam_setup_vb2(cam);
	अगर (ret) अणु
		cam->sensor = शून्य;
		जाओ out;
	पूर्ण

	cam->vdev = mcam_v4l_ढाँचा;
	cam->vdev.v4l2_dev = &cam->v4l2_dev;
	cam->vdev.lock = &cam->s_mutex;
	cam->vdev.queue = &cam->vb_queue;
	video_set_drvdata(&cam->vdev, cam);
	ret = video_रेजिस्टर_device(&cam->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		cam->sensor = शून्य;
		जाओ out;
	पूर्ण

	cam_dbg(cam, "sensor %s bound\n", subdev->name);
out:
	mutex_unlock(&cam->s_mutex);
	वापस ret;
पूर्ण

अटल व्योम mccic_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
	काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा mcam_camera *cam = notअगरier_to_mcam(notअगरier);

	mutex_lock(&cam->s_mutex);
	अगर (cam->sensor != subdev) अणु
		cam_err(cam, "sensor %s not bound\n", subdev->name);
		जाओ out;
	पूर्ण

	video_unरेजिस्टर_device(&cam->vdev);
	cam->sensor = शून्य;
	cam_dbg(cam, "sensor %s unbound\n", subdev->name);

out:
	mutex_unlock(&cam->s_mutex);
पूर्ण

अटल पूर्णांक mccic_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा mcam_camera *cam = notअगरier_to_mcam(notअगरier);
	पूर्णांक ret;

	/*
	 * Get the v4l2 setup करोne.
	 */
	ret = v4l2_ctrl_handler_init(&cam->ctrl_handler, 10);
	अगर (!ret)
		cam->v4l2_dev.ctrl_handler = &cam->ctrl_handler;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations mccic_notअगरy_ops = अणु
	.bound = mccic_notअगरy_bound,
	.unbind = mccic_notअगरy_unbind,
	.complete = mccic_notअगरy_complete,
पूर्ण;

पूर्णांक mccic_रेजिस्टर(काष्ठा mcam_camera *cam)
अणु
	काष्ठा clk_init_data mclk_init = अणु पूर्ण;
	पूर्णांक ret;

	/*
	 * Validate the requested buffer mode.
	 */
	अगर (buffer_mode >= 0)
		cam->buffer_mode = buffer_mode;
	अगर (cam->buffer_mode == B_DMA_sg &&
			cam->chip_id == MCAM_CAFE) अणु
		prपूर्णांकk(KERN_ERR "marvell-cam: Cafe can't do S/G I/O, attempting vmalloc mode instead\n");
		cam->buffer_mode = B_vदो_स्मृति;
	पूर्ण

	अगर (!mcam_buffer_mode_supported(cam->buffer_mode)) अणु
		prपूर्णांकk(KERN_ERR "marvell-cam: buffer mode %d unsupported\n",
				cam->buffer_mode);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Register with V4L
	 */
	ret = v4l2_device_रेजिस्टर(cam->dev, &cam->v4l2_dev);
	अगर (ret)
		जाओ out;

	mutex_init(&cam->s_mutex);
	cam->state = S_NOTREADY;
	mcam_set_config_needed(cam, 1);
	cam->pix_क्रमmat = mcam_def_pix_क्रमmat;
	cam->mbus_code = mcam_def_mbus_code;

	cam->notअगरier.ops = &mccic_notअगरy_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&cam->v4l2_dev, &cam->notअगरier);
	अगर (ret < 0) अणु
		cam_warn(cam, "failed to register a sensor notifier");
		जाओ out;
	पूर्ण

	/*
	 * Register sensor master घड़ी.
	 */
	mclk_init.parent_names = शून्य;
	mclk_init.num_parents = 0;
	mclk_init.ops = &mclk_ops;
	mclk_init.name = "mclk";

	of_property_पढ़ो_string(cam->dev->of_node, "clock-output-names",
							&mclk_init.name);

	cam->mclk_hw.init = &mclk_init;

	cam->mclk = devm_clk_रेजिस्टर(cam->dev, &cam->mclk_hw);
	अगर (IS_ERR(cam->mclk)) अणु
		ret = PTR_ERR(cam->mclk);
		dev_err(cam->dev, "can't register clock\n");
		जाओ out;
	पूर्ण

	/*
	 * If so requested, try to get our DMA buffers now.
	 */
	अगर (cam->buffer_mode == B_vदो_स्मृति && !alloc_bufs_at_पढ़ो) अणु
		अगर (mcam_alloc_dma_bufs(cam, 1))
			cam_warn(cam, "Unable to alloc DMA buffers at load will try again later.");
	पूर्ण

	वापस 0;

out:
	v4l2_async_notअगरier_unरेजिस्टर(&cam->notअगरier);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
	v4l2_async_notअगरier_cleanup(&cam->notअगरier);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mccic_रेजिस्टर);

व्योम mccic_shutकरोwn(काष्ठा mcam_camera *cam)
अणु
	/*
	 * If we have no users (and we really, really should have no
	 * users) the device will alपढ़ोy be घातered करोwn.  Trying to
	 * take it करोwn again will wedge the machine, which is frowned
	 * upon.
	 */
	अगर (!list_empty(&cam->vdev.fh_list)) अणु
		cam_warn(cam, "Removing a device with users!\n");
		sensor_call(cam, core, s_घातer, 0);
	पूर्ण
	अगर (cam->buffer_mode == B_vदो_स्मृति)
		mcam_मुक्त_dma_bufs(cam);
	v4l2_ctrl_handler_मुक्त(&cam->ctrl_handler);
	v4l2_async_notअगरier_unरेजिस्टर(&cam->notअगरier);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
	v4l2_async_notअगरier_cleanup(&cam->notअगरier);
पूर्ण
EXPORT_SYMBOL_GPL(mccic_shutकरोwn);

/*
 * Power management
 */
व्योम mccic_suspend(काष्ठा mcam_camera *cam)
अणु
	mutex_lock(&cam->s_mutex);
	अगर (!list_empty(&cam->vdev.fh_list)) अणु
		क्रमागत mcam_state cstate = cam->state;

		mcam_ctlr_stop_dma(cam);
		sensor_call(cam, core, s_घातer, 0);
		cam->state = cstate;
	पूर्ण
	mutex_unlock(&cam->s_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mccic_suspend);

पूर्णांक mccic_resume(काष्ठा mcam_camera *cam)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&cam->s_mutex);
	अगर (!list_empty(&cam->vdev.fh_list)) अणु
		ret = sensor_call(cam, core, s_घातer, 1);
		अगर (ret) अणु
			mutex_unlock(&cam->s_mutex);
			वापस ret;
		पूर्ण
		__mcam_cam_reset(cam);
	पूर्ण अन्यथा अणु
		sensor_call(cam, core, s_घातer, 0);
	पूर्ण
	mutex_unlock(&cam->s_mutex);

	set_bit(CF_CONFIG_NEEDED, &cam->flags);
	अगर (cam->state == S_STREAMING) अणु
		/*
		 * If there was a buffer in the DMA engine at suspend
		 * समय, put it back on the queue or we'll क्रमget about it.
		 */
		अगर (cam->buffer_mode == B_DMA_sg && cam->vb_bufs[0])
			list_add(&cam->vb_bufs[0]->queue, &cam->buffers);
		ret = mcam_पढ़ो_setup(cam);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mccic_resume);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonathan Corbet <corbet@lwn.net>");
