<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Capture CSI Subdev क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2014-2017 Mentor Graphics Inc.
 * Copyright (C) 2017 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 */
#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <video/imx-ipu-v3.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"

/*
 * Min/Max supported width and heights.
 *
 * We allow planar output, so we have to align width by 16 pixels
 * to meet IDMAC alignment requirements.
 *
 * TODO: move this पूर्णांकo pad क्रमmat negotiation, अगर capture device
 * has not requested planar क्रमmats, we should allow 8 pixel
 * alignment.
 */
#घोषणा MIN_W       32
#घोषणा MIN_H       32
#घोषणा MAX_W      4096
#घोषणा MAX_H      4096
#घोषणा W_ALIGN    1 /* multiple of 2 pixels */
#घोषणा H_ALIGN    1 /* multiple of 2 lines */
#घोषणा S_ALIGN    1 /* multiple of 2 */

/*
 * काष्ठा csi_skip_desc - CSI frame skipping descriptor
 * @keep - number of frames kept per max_ratio frames
 * @max_ratio - width of skip_smfc, written to MAX_RATIO bitfield
 * @skip_smfc - skip pattern written to the SKIP_SMFC bitfield
 */
काष्ठा csi_skip_desc अणु
	u8 keep;
	u8 max_ratio;
	u8 skip_smfc;
पूर्ण;

काष्ठा csi_priv अणु
	काष्ठा device *dev;
	काष्ठा ipu_soc *ipu;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad[CSI_NUM_PADS];
	काष्ठा v4l2_async_notअगरier notअगरier;

	/* the video device at IDMAC output pad */
	काष्ठा imx_media_video_dev *vdev;
	काष्ठा imx_media_fim *fim;
	पूर्णांक csi_id;
	पूर्णांक smfc_id;

	/* lock to protect all members below */
	काष्ठा mutex lock;

	पूर्णांक active_output_pad;

	काष्ठा ipuv3_channel *idmac_ch;
	काष्ठा ipu_smfc *smfc;
	काष्ठा ipu_csi *csi;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus[CSI_NUM_PADS];
	स्थिर काष्ठा imx_media_pixfmt *cc[CSI_NUM_PADS];
	काष्ठा v4l2_fract frame_पूर्णांकerval[CSI_NUM_PADS];
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_rect compose;
	स्थिर काष्ठा csi_skip_desc *skip;

	/* active vb2 buffers to send to video dev sink */
	काष्ठा imx_media_buffer *active_vb2_buf[2];
	काष्ठा imx_media_dma_buf underrun_buf;

	पूर्णांक ipu_buf_num;  /* ipu द्विगुन buffer index: 0-1 */

	/* the sink क्रम the captured frames */
	काष्ठा media_entity *sink;
	क्रमागत ipu_csi_dest dest;
	/* the source subdev */
	काष्ठा v4l2_subdev *src_sd;

	/* the mipi भव channel number at link validate */
	पूर्णांक vc_num;

	/* the upstream endpoपूर्णांक CSI is receiving from */
	काष्ठा v4l2_fwnode_endpoपूर्णांक upstream_ep;

	spinlock_t irqlock; /* protect eof_irq handler */
	काष्ठा समयr_list eof_समयout_समयr;
	पूर्णांक eof_irq;
	पूर्णांक nfb4eof_irq;

	काष्ठा v4l2_ctrl_handler ctrl_hdlr;

	पूर्णांक stream_count; /* streaming counter */
	u32 frame_sequence; /* frame sequence counter */
	bool last_eof;   /* रुकोing क्रम last खातापूर्ण at stream off */
	bool nfb4eof;    /* NFB4खातापूर्ण encountered during streaming */
	bool पूर्णांकerweave_swap; /* swap top/bottom lines when पूर्णांकerweaving */
	काष्ठा completion last_eof_comp;
पूर्ण;

अटल अंतरभूत काष्ठा csi_priv *sd_to_dev(काष्ठा v4l2_subdev *sdev)
अणु
	वापस container_of(sdev, काष्ठा csi_priv, sd);
पूर्ण

अटल अंतरभूत काष्ठा csi_priv *notअगरier_to_dev(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा csi_priv, notअगरier);
पूर्ण

अटल अंतरभूत bool is_parallel_bus(काष्ठा v4l2_fwnode_endpoपूर्णांक *ep)
अणु
	वापस ep->bus_type != V4L2_MBUS_CSI2_DPHY;
पूर्ण

अटल अंतरभूत bool is_parallel_16bit_bus(काष्ठा v4l2_fwnode_endpoपूर्णांक *ep)
अणु
	वापस is_parallel_bus(ep) && ep->bus.parallel.bus_width >= 16;
पूर्ण

/*
 * Check क्रम conditions that require the IPU to handle the
 * data पूर्णांकernally as generic data, aka passthrough mode:
 * - raw bayer media bus क्रमmats, or
 * - the CSI is receiving from a 16-bit parallel bus, or
 * - the CSI is receiving from an 8-bit parallel bus and the incoming
 *   media bus क्रमmat is other than UYVY8_2X8/YUYV8_2X8.
 */
अटल अंतरभूत bool requires_passthrough(काष्ठा v4l2_fwnode_endpoपूर्णांक *ep,
					काष्ठा v4l2_mbus_framefmt *infmt,
					स्थिर काष्ठा imx_media_pixfmt *incc)
अणु
	वापस incc->bayer || is_parallel_16bit_bus(ep) ||
		(is_parallel_bus(ep) &&
		 infmt->code != MEDIA_BUS_FMT_UYVY8_2X8 &&
		 infmt->code != MEDIA_BUS_FMT_YUYV8_2X8);
पूर्ण

/*
 * Parses the fwnode endpoपूर्णांक from the source pad of the entity
 * connected to this CSI. This will either be the entity directly
 * upstream from the CSI-2 receiver, directly upstream from the
 * video mux, or directly upstream from the CSI itself. The endpoपूर्णांक
 * is needed to determine the bus type and bus config coming पूर्णांकo
 * the CSI.
 */
अटल पूर्णांक csi_get_upstream_endpoपूर्णांक(काष्ठा csi_priv *priv,
				     काष्ठा v4l2_fwnode_endpoपूर्णांक *ep)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा v4l2_subdev *sd;
	काष्ठा media_pad *pad;

	अगर (!IS_ENABLED(CONFIG_OF))
		वापस -ENXIO;

	अगर (!priv->src_sd)
		वापस -EPIPE;

	sd = priv->src_sd;

	चयन (sd->grp_id) अणु
	हाल IMX_MEDIA_GRP_ID_CSI_MUX:
		/*
		 * CSI is connected directly to CSI mux, skip up to
		 * CSI-2 receiver अगर it is in the path, otherwise stay
		 * with the CSI mux.
		 */
		sd = imx_media_pipeline_subdev(&sd->entity,
					       IMX_MEDIA_GRP_ID_CSI2,
					       true);
		अगर (IS_ERR(sd))
			sd = priv->src_sd;
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_CSI2:
		अवरोध;
	शेष:
		/*
		 * the source is neither the CSI mux nor the CSI-2 receiver,
		 * get the source pad directly upstream from CSI itself.
		 */
		sd = &priv->sd;
		अवरोध;
	पूर्ण

	/* get source pad of entity directly upstream from sd */
	pad = imx_media_pipeline_pad(&sd->entity, 0, 0, true);
	अगर (!pad)
		वापस -ENODEV;

	endpoपूर्णांक = imx_media_get_pad_fwnode(pad);
	अगर (IS_ERR(endpoपूर्णांक))
		वापस PTR_ERR(endpoपूर्णांक);

	v4l2_fwnode_endpoपूर्णांक_parse(endpoपूर्णांक, ep);

	fwnode_handle_put(endpoपूर्णांक);

	वापस 0;
पूर्ण

अटल व्योम csi_idmac_put_ipu_resources(काष्ठा csi_priv *priv)
अणु
	अगर (priv->idmac_ch)
		ipu_idmac_put(priv->idmac_ch);
	priv->idmac_ch = शून्य;

	अगर (priv->smfc)
		ipu_smfc_put(priv->smfc);
	priv->smfc = शून्य;
पूर्ण

अटल पूर्णांक csi_idmac_get_ipu_resources(काष्ठा csi_priv *priv)
अणु
	पूर्णांक ch_num, ret;
	काष्ठा ipu_smfc *smfc;
	काष्ठा ipuv3_channel *idmac_ch;

	ch_num = IPUV3_CHANNEL_CSI0 + priv->smfc_id;

	smfc = ipu_smfc_get(priv->ipu, ch_num);
	अगर (IS_ERR(smfc)) अणु
		v4l2_err(&priv->sd, "failed to get SMFC\n");
		ret = PTR_ERR(smfc);
		जाओ out;
	पूर्ण
	priv->smfc = smfc;

	idmac_ch = ipu_idmac_get(priv->ipu, ch_num);
	अगर (IS_ERR(idmac_ch)) अणु
		v4l2_err(&priv->sd, "could not get IDMAC channel %u\n",
			 ch_num);
		ret = PTR_ERR(idmac_ch);
		जाओ out;
	पूर्ण
	priv->idmac_ch = idmac_ch;

	वापस 0;
out:
	csi_idmac_put_ipu_resources(priv);
	वापस ret;
पूर्ण

अटल व्योम csi_vb2_buf_करोne(काष्ठा csi_priv *priv)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_media_buffer *करोne, *next;
	काष्ठा vb2_buffer *vb;
	dma_addr_t phys;

	करोne = priv->active_vb2_buf[priv->ipu_buf_num];
	अगर (करोne) अणु
		करोne->vbuf.field = vdev->fmt.field;
		करोne->vbuf.sequence = priv->frame_sequence;
		vb = &करोne->vbuf.vb2_buf;
		vb->बारtamp = kसमय_get_ns();
		vb2_buffer_करोne(vb, priv->nfb4eof ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
	पूर्ण

	priv->frame_sequence++;
	priv->nfb4eof = false;

	/* get next queued buffer */
	next = imx_media_capture_device_next_buf(vdev);
	अगर (next) अणु
		phys = vb2_dma_contig_plane_dma_addr(&next->vbuf.vb2_buf, 0);
		priv->active_vb2_buf[priv->ipu_buf_num] = next;
	पूर्ण अन्यथा अणु
		phys = priv->underrun_buf.phys;
		priv->active_vb2_buf[priv->ipu_buf_num] = शून्य;
	पूर्ण

	अगर (ipu_idmac_buffer_is_पढ़ोy(priv->idmac_ch, priv->ipu_buf_num))
		ipu_idmac_clear_buffer(priv->idmac_ch, priv->ipu_buf_num);

	अगर (priv->पूर्णांकerweave_swap)
		phys += vdev->fmt.bytesperline;

	ipu_cpmem_set_buffer(priv->idmac_ch, priv->ipu_buf_num, phys);
पूर्ण

अटल irqवापस_t csi_idmac_eof_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csi_priv *priv = dev_id;

	spin_lock(&priv->irqlock);

	अगर (priv->last_eof) अणु
		complete(&priv->last_eof_comp);
		priv->last_eof = false;
		जाओ unlock;
	पूर्ण

	अगर (priv->fim)
		/* call frame पूर्णांकerval monitor */
		imx_media_fim_eof_monitor(priv->fim, kसमय_get());

	csi_vb2_buf_करोne(priv);

	/* select new IPU buf */
	ipu_idmac_select_buffer(priv->idmac_ch, priv->ipu_buf_num);
	/* toggle IPU द्विगुन-buffer index */
	priv->ipu_buf_num ^= 1;

	/* bump the खातापूर्ण समयout समयr */
	mod_समयr(&priv->eof_समयout_समयr,
		  jअगरfies + msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));

unlock:
	spin_unlock(&priv->irqlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t csi_idmac_nfb4eof_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csi_priv *priv = dev_id;

	spin_lock(&priv->irqlock);

	/*
	 * this is not an unrecoverable error, just mark
	 * the next captured frame with vb2 error flag.
	 */
	priv->nfb4eof = true;

	v4l2_err(&priv->sd, "NFB4EOF\n");

	spin_unlock(&priv->irqlock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * खातापूर्ण समयout समयr function. This is an unrecoverable condition
 * without a stream restart.
 */
अटल व्योम csi_idmac_eof_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा csi_priv *priv = from_समयr(priv, t, eof_समयout_समयr);
	काष्ठा imx_media_video_dev *vdev = priv->vdev;

	v4l2_err(&priv->sd, "EOF timeout\n");

	/* संकेत a fatal error to capture device */
	imx_media_capture_device_error(vdev);
पूर्ण

अटल व्योम csi_idmac_setup_vb2_buf(काष्ठा csi_priv *priv, dma_addr_t *phys)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_media_buffer *buf;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		buf = imx_media_capture_device_next_buf(vdev);
		अगर (buf) अणु
			priv->active_vb2_buf[i] = buf;
			phys[i] = vb2_dma_contig_plane_dma_addr(
				&buf->vbuf.vb2_buf, 0);
		पूर्ण अन्यथा अणु
			priv->active_vb2_buf[i] = शून्य;
			phys[i] = priv->underrun_buf.phys;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम csi_idmac_unsetup_vb2_buf(काष्ठा csi_priv *priv,
				      क्रमागत vb2_buffer_state वापस_status)
अणु
	काष्ठा imx_media_buffer *buf;
	पूर्णांक i;

	/* वापस any reमुख्यing active frames with वापस_status */
	क्रम (i = 0; i < 2; i++) अणु
		buf = priv->active_vb2_buf[i];
		अगर (buf) अणु
			काष्ठा vb2_buffer *vb = &buf->vbuf.vb2_buf;

			vb->बारtamp = kसमय_get_ns();
			vb2_buffer_करोne(vb, वापस_status);
		पूर्ण
	पूर्ण
पूर्ण

/* init the SMFC IDMAC channel */
अटल पूर्णांक csi_idmac_setup_channel(काष्ठा csi_priv *priv)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	स्थिर काष्ठा imx_media_pixfmt *incc;
	काष्ठा v4l2_mbus_framefmt *infmt;
	काष्ठा v4l2_mbus_framefmt *outfmt;
	bool passthrough, पूर्णांकerweave;
	काष्ठा ipu_image image;
	u32 passthrough_bits;
	u32 passthrough_cycles;
	dma_addr_t phys[2];
	u32 burst_size;
	पूर्णांक ret;

	infmt = &priv->क्रमmat_mbus[CSI_SINK_PAD];
	incc = priv->cc[CSI_SINK_PAD];
	outfmt = &priv->क्रमmat_mbus[CSI_SRC_PAD_IDMAC];

	ipu_cpmem_zero(priv->idmac_ch);

	स_रखो(&image, 0, माप(image));
	image.pix = vdev->fmt;
	image.rect = vdev->compose;

	csi_idmac_setup_vb2_buf(priv, phys);

	image.phys0 = phys[0];
	image.phys1 = phys[1];

	passthrough = requires_passthrough(&priv->upstream_ep, infmt, incc);
	passthrough_cycles = 1;

	/*
	 * If the field type at capture पूर्णांकerface is पूर्णांकerlaced, and
	 * the output IDMAC pad is sequential, enable पूर्णांकerweave at
	 * the IDMAC output channel.
	 */
	पूर्णांकerweave = V4L2_FIELD_IS_INTERLACED(image.pix.field) &&
		V4L2_FIELD_IS_SEQUENTIAL(outfmt->field);
	priv->पूर्णांकerweave_swap = पूर्णांकerweave &&
		image.pix.field == V4L2_FIELD_INTERLACED_BT;

	चयन (image.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_GREY:
		burst_size = 16;
		passthrough_bits = 8;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SRGGB16:
	हाल V4L2_PIX_FMT_Y10:
	हाल V4L2_PIX_FMT_Y12:
		burst_size = 8;
		passthrough_bits = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_NV12:
		burst_size = (image.pix.width & 0x3f) ?
			     ((image.pix.width & 0x1f) ?
			      ((image.pix.width & 0xf) ? 8 : 16) : 32) : 64;
		passthrough_bits = 16;
		/*
		 * Skip writing U and V components to odd rows (but not
		 * when enabling IDMAC पूर्णांकerweaving, they are incompatible).
		 */
		अगर (!पूर्णांकerweave)
			ipu_cpmem_skip_odd_chroma_rows(priv->idmac_ch);
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
		burst_size = (image.pix.width & 0x1f) ?
			     ((image.pix.width & 0xf) ? 8 : 16) : 32;
		passthrough_bits = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		अगर (passthrough) अणु
			burst_size = 16;
			passthrough_bits = 8;
			passthrough_cycles = incc->cycles;
			अवरोध;
		पूर्ण
		fallthrough;	/* non-passthrough RGB565 (CSI-2 bus) */
	शेष:
		burst_size = (image.pix.width & 0xf) ? 8 : 16;
		passthrough_bits = 16;
		अवरोध;
	पूर्ण

	अगर (passthrough) अणु
		अगर (priv->पूर्णांकerweave_swap) अणु
			/* start पूर्णांकerweave scan at 1st top line (2nd line) */
			image.phys0 += image.pix.bytesperline;
			image.phys1 += image.pix.bytesperline;
		पूर्ण

		ipu_cpmem_set_resolution(priv->idmac_ch,
					 image.rect.width * passthrough_cycles,
					 image.rect.height);
		ipu_cpmem_set_stride(priv->idmac_ch, image.pix.bytesperline);
		ipu_cpmem_set_buffer(priv->idmac_ch, 0, image.phys0);
		ipu_cpmem_set_buffer(priv->idmac_ch, 1, image.phys1);
		ipu_cpmem_set_क्रमmat_passthrough(priv->idmac_ch,
						 passthrough_bits);
	पूर्ण अन्यथा अणु
		अगर (priv->पूर्णांकerweave_swap) अणु
			/* start पूर्णांकerweave scan at 1st top line (2nd line) */
			image.rect.top = 1;
		पूर्ण

		ret = ipu_cpmem_set_image(priv->idmac_ch, &image);
		अगर (ret)
			जाओ unsetup_vb2;
	पूर्ण

	ipu_cpmem_set_burstsize(priv->idmac_ch, burst_size);

	/*
	 * Set the channel क्रम the direct CSI-->memory via SMFC
	 * use-हाल to very high priority, by enabling the watermark
	 * संकेत in the SMFC, enabling WM in the channel, and setting
	 * the channel priority to high.
	 *
	 * Refer to the i.mx6 rev. D TRM Table 36-8: Calculated priority
	 * value.
	 *
	 * The WM's are set very low by पूर्णांकention here to ensure that
	 * the SMFC FIFOs करो not overflow.
	 */
	ipu_smfc_set_watermark(priv->smfc, 0x02, 0x01);
	ipu_cpmem_set_high_priority(priv->idmac_ch);
	ipu_idmac_enable_watermark(priv->idmac_ch, true);
	ipu_cpmem_set_axi_id(priv->idmac_ch, 0);

	burst_size = passthrough ?
		(burst_size >> 3) - 1 : (burst_size >> 2) - 1;

	ipu_smfc_set_burstsize(priv->smfc, burst_size);

	अगर (पूर्णांकerweave)
		ipu_cpmem_पूर्णांकerlaced_scan(priv->idmac_ch,
					  priv->पूर्णांकerweave_swap ?
					  -image.pix.bytesperline :
					  image.pix.bytesperline,
					  image.pix.pixelक्रमmat);

	ipu_idmac_set_द्विगुन_buffer(priv->idmac_ch, true);

	वापस 0;

unsetup_vb2:
	csi_idmac_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम csi_idmac_unsetup(काष्ठा csi_priv *priv,
			      क्रमागत vb2_buffer_state state)
अणु
	ipu_idmac_disable_channel(priv->idmac_ch);
	ipu_smfc_disable(priv->smfc);

	csi_idmac_unsetup_vb2_buf(priv, state);
पूर्ण

अटल पूर्णांक csi_idmac_setup(काष्ठा csi_priv *priv)
अणु
	पूर्णांक ret;

	ret = csi_idmac_setup_channel(priv);
	अगर (ret)
		वापस ret;

	ipu_cpmem_dump(priv->idmac_ch);
	ipu_dump(priv->ipu);

	ipu_smfc_enable(priv->smfc);

	/* set buffers पढ़ोy */
	ipu_idmac_select_buffer(priv->idmac_ch, 0);
	ipu_idmac_select_buffer(priv->idmac_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->idmac_ch);

	वापस 0;
पूर्ण

अटल पूर्णांक csi_idmac_start(काष्ठा csi_priv *priv)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	पूर्णांक ret;

	ret = csi_idmac_get_ipu_resources(priv);
	अगर (ret)
		वापस ret;

	ipu_smfc_map_channel(priv->smfc, priv->csi_id, priv->vc_num);

	ret = imx_media_alloc_dma_buf(priv->dev, &priv->underrun_buf,
				      vdev->fmt.sizeimage);
	अगर (ret)
		जाओ out_put_ipu;

	priv->ipu_buf_num = 0;

	/* init खातापूर्ण completion रुकोq */
	init_completion(&priv->last_eof_comp);
	priv->frame_sequence = 0;
	priv->last_eof = false;
	priv->nfb4eof = false;

	ret = csi_idmac_setup(priv);
	अगर (ret) अणु
		v4l2_err(&priv->sd, "csi_idmac_setup failed: %d\n", ret);
		जाओ out_मुक्त_dma_buf;
	पूर्ण

	priv->nfb4eof_irq = ipu_idmac_channel_irq(priv->ipu,
						  priv->idmac_ch,
						  IPU_IRQ_NFB4खातापूर्ण);
	ret = devm_request_irq(priv->dev, priv->nfb4eof_irq,
			       csi_idmac_nfb4eof_पूर्णांकerrupt, 0,
			       "imx-smfc-nfb4eof", priv);
	अगर (ret) अणु
		v4l2_err(&priv->sd,
			 "Error registering NFB4EOF irq: %d\n", ret);
		जाओ out_unsetup;
	पूर्ण

	priv->eof_irq = ipu_idmac_channel_irq(priv->ipu, priv->idmac_ch,
					      IPU_IRQ_खातापूर्ण);

	ret = devm_request_irq(priv->dev, priv->eof_irq,
			       csi_idmac_eof_पूर्णांकerrupt, 0,
			       "imx-smfc-eof", priv);
	अगर (ret) अणु
		v4l2_err(&priv->sd,
			 "Error registering eof irq: %d\n", ret);
		जाओ out_मुक्त_nfb4eof_irq;
	पूर्ण

	/* start the खातापूर्ण समयout समयr */
	mod_समयr(&priv->eof_समयout_समयr,
		  jअगरfies + msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));

	वापस 0;

out_मुक्त_nfb4eof_irq:
	devm_मुक्त_irq(priv->dev, priv->nfb4eof_irq, priv);
out_unsetup:
	csi_idmac_unsetup(priv, VB2_BUF_STATE_QUEUED);
out_मुक्त_dma_buf:
	imx_media_मुक्त_dma_buf(priv->dev, &priv->underrun_buf);
out_put_ipu:
	csi_idmac_put_ipu_resources(priv);
	वापस ret;
पूर्ण

अटल व्योम csi_idmac_रुको_last_eof(काष्ठा csi_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* mark next खातापूर्ण पूर्णांकerrupt as the last beक्रमe stream off */
	spin_lock_irqsave(&priv->irqlock, flags);
	priv->last_eof = true;
	spin_unlock_irqrestore(&priv->irqlock, flags);

	/*
	 * and then रुको क्रम पूर्णांकerrupt handler to mark completion.
	 */
	ret = रुको_क्रम_completion_समयout(
		&priv->last_eof_comp, msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));
	अगर (ret == 0)
		v4l2_warn(&priv->sd, "wait last EOF timeout\n");
पूर्ण

अटल व्योम csi_idmac_stop(काष्ठा csi_priv *priv)
अणु
	devm_मुक्त_irq(priv->dev, priv->eof_irq, priv);
	devm_मुक्त_irq(priv->dev, priv->nfb4eof_irq, priv);

	csi_idmac_unsetup(priv, VB2_BUF_STATE_ERROR);

	imx_media_मुक्त_dma_buf(priv->dev, &priv->underrun_buf);

	/* cancel the खातापूर्ण समयout समयr */
	del_समयr_sync(&priv->eof_समयout_समयr);

	csi_idmac_put_ipu_resources(priv);
पूर्ण

/* Update the CSI whole sensor and active winकरोws */
अटल पूर्णांक csi_setup(काष्ठा csi_priv *priv)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt, *outfmt;
	स्थिर काष्ठा imx_media_pixfmt *incc;
	काष्ठा v4l2_mbus_config mbus_cfg;
	काष्ठा v4l2_mbus_framefmt अगर_fmt;
	काष्ठा v4l2_rect crop;

	infmt = &priv->क्रमmat_mbus[CSI_SINK_PAD];
	incc = priv->cc[CSI_SINK_PAD];
	outfmt = &priv->क्रमmat_mbus[priv->active_output_pad];

	/* compose mbus_config from the upstream endpoपूर्णांक */
	mbus_cfg.type = priv->upstream_ep.bus_type;
	mbus_cfg.flags = is_parallel_bus(&priv->upstream_ep) ?
		priv->upstream_ep.bus.parallel.flags :
		priv->upstream_ep.bus.mipi_csi2.flags;

	अगर_fmt = *infmt;
	crop = priv->crop;

	/*
	 * अगर cycles is set, we need to handle this over multiple cycles as
	 * generic/bayer data
	 */
	अगर (is_parallel_bus(&priv->upstream_ep) && incc->cycles) अणु
		अगर_fmt.width *= incc->cycles;
		crop.width *= incc->cycles;
	पूर्ण

	ipu_csi_set_winकरोw(priv->csi, &crop);

	ipu_csi_set_करोwnsize(priv->csi,
			     priv->crop.width == 2 * priv->compose.width,
			     priv->crop.height == 2 * priv->compose.height);

	ipu_csi_init_पूर्णांकerface(priv->csi, &mbus_cfg, &अगर_fmt, outfmt);

	ipu_csi_set_dest(priv->csi, priv->dest);

	अगर (priv->dest == IPU_CSI_DEST_IDMAC)
		ipu_csi_set_skip_smfc(priv->csi, priv->skip->skip_smfc,
				      priv->skip->max_ratio - 1, 0);

	ipu_csi_dump(priv->csi);

	वापस 0;
पूर्ण

अटल पूर्णांक csi_start(काष्ठा csi_priv *priv)
अणु
	काष्ठा v4l2_fract *output_fi;
	पूर्णांक ret;

	output_fi = &priv->frame_पूर्णांकerval[priv->active_output_pad];

	/* start upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 1);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	अगर (ret)
		वापस ret;

	अगर (priv->dest == IPU_CSI_DEST_IDMAC) अणु
		ret = csi_idmac_start(priv);
		अगर (ret)
			जाओ stop_upstream;
	पूर्ण

	ret = csi_setup(priv);
	अगर (ret)
		जाओ idmac_stop;

	/* start the frame पूर्णांकerval monitor */
	अगर (priv->fim && priv->dest == IPU_CSI_DEST_IDMAC) अणु
		ret = imx_media_fim_set_stream(priv->fim, output_fi, true);
		अगर (ret)
			जाओ idmac_stop;
	पूर्ण

	ret = ipu_csi_enable(priv->csi);
	अगर (ret) अणु
		v4l2_err(&priv->sd, "CSI enable error: %d\n", ret);
		जाओ fim_off;
	पूर्ण

	वापस 0;

fim_off:
	अगर (priv->fim && priv->dest == IPU_CSI_DEST_IDMAC)
		imx_media_fim_set_stream(priv->fim, शून्य, false);
idmac_stop:
	अगर (priv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_stop(priv);
stop_upstream:
	v4l2_subdev_call(priv->src_sd, video, s_stream, 0);
	वापस ret;
पूर्ण

अटल व्योम csi_stop(काष्ठा csi_priv *priv)
अणु
	अगर (priv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_रुको_last_eof(priv);

	/*
	 * Disable the CSI asap, after syncing with the last खातापूर्ण.
	 * Doing so after the IDMA channel is disabled has shown to
	 * create hard प्रणाली-wide hangs.
	 */
	ipu_csi_disable(priv->csi);

	/* stop upstream */
	v4l2_subdev_call(priv->src_sd, video, s_stream, 0);

	अगर (priv->dest == IPU_CSI_DEST_IDMAC) अणु
		csi_idmac_stop(priv);

		/* stop the frame पूर्णांकerval monitor */
		अगर (priv->fim)
			imx_media_fim_set_stream(priv->fim, शून्य, false);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा csi_skip_desc csi_skip[12] = अणु
	अणु 1, 1, 0x00 पूर्ण, /* Keep all frames */
	अणु 5, 6, 0x10 पूर्ण, /* Skip every sixth frame */
	अणु 4, 5, 0x08 पूर्ण, /* Skip every fअगरth frame */
	अणु 3, 4, 0x04 पूर्ण, /* Skip every fourth frame */
	अणु 2, 3, 0x02 पूर्ण, /* Skip every third frame */
	अणु 3, 5, 0x0a पूर्ण, /* Skip frames 1 and 3 of every 5 */
	अणु 1, 2, 0x01 पूर्ण, /* Skip every second frame */
	अणु 2, 5, 0x0b पूर्ण, /* Keep frames 1 and 4 of every 5 */
	अणु 1, 3, 0x03 पूर्ण, /* Keep one in three frames */
	अणु 1, 4, 0x07 पूर्ण, /* Keep one in four frames */
	अणु 1, 5, 0x0f पूर्ण, /* Keep one in five frames */
	अणु 1, 6, 0x1f पूर्ण, /* Keep one in six frames */
पूर्ण;

अटल व्योम csi_apply_skip_पूर्णांकerval(स्थिर काष्ठा csi_skip_desc *skip,
				    काष्ठा v4l2_fract *पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक भाग;

	पूर्णांकerval->numerator *= skip->max_ratio;
	पूर्णांकerval->denominator *= skip->keep;

	/* Reduce fraction to lowest terms */
	भाग = gcd(पूर्णांकerval->numerator, पूर्णांकerval->denominator);
	अगर (भाग > 1) अणु
		पूर्णांकerval->numerator /= भाग;
		पूर्णांकerval->denominator /= भाग;
	पूर्ण
पूर्ण

/*
 * Find the skip pattern to produce the output frame पूर्णांकerval बंदst to the
 * requested one, क्रम the given input frame पूर्णांकerval. Updates the output frame
 * पूर्णांकerval to the exact value.
 */
अटल स्थिर काष्ठा csi_skip_desc *csi_find_best_skip(काष्ठा v4l2_fract *in,
						      काष्ठा v4l2_fract *out)
अणु
	स्थिर काष्ठा csi_skip_desc *skip = &csi_skip[0], *best_skip = skip;
	u32 min_err = अच_पूर्णांक_उच्च;
	u64 want_us;
	पूर्णांक i;

	/* Default to 1:1 ratio */
	अगर (out->numerator == 0 || out->denominator == 0 ||
	    in->numerator == 0 || in->denominator == 0) अणु
		*out = *in;
		वापस best_skip;
	पूर्ण

	want_us = भाग_u64((u64)USEC_PER_SEC * out->numerator, out->denominator);

	/* Find the reduction बंदst to the requested समय per frame */
	क्रम (i = 0; i < ARRAY_SIZE(csi_skip); i++, skip++) अणु
		u64 पंचांगp, err;

		पंचांगp = भाग_u64((u64)USEC_PER_SEC * in->numerator *
			      skip->max_ratio, in->denominator * skip->keep);

		err = असल((s64)पंचांगp - want_us);
		अगर (err < min_err) अणु
			min_err = err;
			best_skip = skip;
		पूर्ण
	पूर्ण

	*out = *in;
	csi_apply_skip_पूर्णांकerval(best_skip, out);

	वापस best_skip;
पूर्ण

/*
 * V4L2 subdev operations.
 */

अटल पूर्णांक csi_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);

	अगर (fi->pad >= CSI_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	fi->पूर्णांकerval = priv->frame_पूर्णांकerval[fi->pad];

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक csi_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fract *input_fi;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	input_fi = &priv->frame_पूर्णांकerval[CSI_SINK_PAD];

	चयन (fi->pad) अणु
	हाल CSI_SINK_PAD:
		/* No limits on valid input frame पूर्णांकervals */
		अगर (fi->पूर्णांकerval.numerator == 0 ||
		    fi->पूर्णांकerval.denominator == 0)
			fi->पूर्णांकerval = *input_fi;
		/* Reset output पूर्णांकervals and frame skipping ratio to 1:1 */
		priv->frame_पूर्णांकerval[CSI_SRC_PAD_IDMAC] = fi->पूर्णांकerval;
		priv->frame_पूर्णांकerval[CSI_SRC_PAD_सूचीECT] = fi->पूर्णांकerval;
		priv->skip = &csi_skip[0];
		अवरोध;
	हाल CSI_SRC_PAD_IDMAC:
		/*
		 * frame पूर्णांकerval at IDMAC output pad depends on input
		 * पूर्णांकerval, modअगरied by frame skipping.
		 */
		priv->skip = csi_find_best_skip(input_fi, &fi->पूर्णांकerval);
		अवरोध;
	हाल CSI_SRC_PAD_सूचीECT:
		/*
		 * frame पूर्णांकerval at सूचीECT output pad is same as input
		 * पूर्णांकerval.
		 */
		fi->पूर्णांकerval = *input_fi;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	priv->frame_पूर्णांकerval[fi->pad] = fi->पूर्णांकerval;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (!priv->src_sd || !priv->sink) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	/*
	 * enable/disable streaming only अगर stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	अगर (priv->stream_count != !enable)
		जाओ update_count;

	अगर (enable) अणु
		dev_dbg(priv->dev, "stream ON\n");
		ret = csi_start(priv);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		dev_dbg(priv->dev, "stream OFF\n");
		csi_stop(priv);
	पूर्ण

update_count:
	priv->stream_count += enable ? 1 : -1;
	अगर (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_link_setup(काष्ठा media_entity *entity,
			  स्थिर काष्ठा media_pad *local,
			  स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_subdev *remote_sd;
	पूर्णांक ret = 0;

	dev_dbg(priv->dev, "link setup %s -> %s\n", remote->entity->name,
		local->entity->name);

	mutex_lock(&priv->lock);

	अगर (local->flags & MEDIA_PAD_FL_SINK) अणु
		अगर (!is_media_entity_v4l2_subdev(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (priv->src_sd) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			priv->src_sd = remote_sd;
		पूर्ण अन्यथा अणु
			priv->src_sd = शून्य;
		पूर्ण

		जाओ out;
	पूर्ण

	/* this is a source pad */

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (priv->sink) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
		v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);
		priv->sink = शून्य;
		/* करो not apply IC burst alignment in csi_try_crop */
		priv->active_output_pad = CSI_SRC_PAD_IDMAC;
		जाओ out;
	पूर्ण

	/* record which output pad is now active */
	priv->active_output_pad = local->index;

	/* set CSI destination */
	अगर (local->index == CSI_SRC_PAD_IDMAC) अणु
		अगर (!is_media_entity_v4l2_video_device(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (priv->fim) अणु
			ret = imx_media_fim_add_controls(priv->fim);
			अगर (ret)
				जाओ out;
		पूर्ण

		priv->dest = IPU_CSI_DEST_IDMAC;
	पूर्ण अन्यथा अणु
		अगर (!is_media_entity_v4l2_subdev(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);
		चयन (remote_sd->grp_id) अणु
		हाल IMX_MEDIA_GRP_ID_IPU_VDIC:
			priv->dest = IPU_CSI_DEST_VDIC;
			अवरोध;
		हाल IMX_MEDIA_GRP_ID_IPU_IC_PRP:
			priv->dest = IPU_CSI_DEST_IC;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	priv->sink = remote->entity;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_link_validate(काष्ठा v4l2_subdev *sd,
			     काष्ठा media_link *link,
			     काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			     काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fwnode_endpoपूर्णांक upstream_ep = अणु .bus_type = 0 पूर्ण;
	bool is_csi2;
	पूर्णांक ret;

	ret = v4l2_subdev_link_validate_शेष(sd, link,
						source_fmt, sink_fmt);
	अगर (ret)
		वापस ret;

	ret = csi_get_upstream_endpoपूर्णांक(priv, &upstream_ep);
	अगर (ret) अणु
		v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
		वापस ret;
	पूर्ण

	mutex_lock(&priv->lock);

	priv->upstream_ep = upstream_ep;
	is_csi2 = !is_parallel_bus(&upstream_ep);
	अगर (is_csi2) अणु
		/*
		 * NOTE! It seems the भव channels from the mipi csi-2
		 * receiver are used only क्रम routing by the video mux's,
		 * or क्रम hard-wired routing to the CSI's. Once the stream
		 * enters the CSI's however, they are treated पूर्णांकernally
		 * in the IPU as भव channel 0.
		 */
		ipu_csi_set_mipi_datatype(priv->csi, 0,
					  &priv->क्रमmat_mbus[CSI_SINK_PAD]);
	पूर्ण

	/* select either parallel or MIPI-CSI2 as input to CSI */
	ipu_set_csi_src_mux(priv->ipu, priv->csi_id, is_csi2);

	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__csi_get_fmt(काष्ठा csi_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
	      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&priv->sd, cfg, pad);
	अन्यथा
		वापस &priv->क्रमmat_mbus[pad];
पूर्ण

अटल काष्ठा v4l2_rect *
__csi_get_crop(काष्ठा csi_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
	       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&priv->sd, cfg, CSI_SINK_PAD);
	अन्यथा
		वापस &priv->crop;
पूर्ण

अटल काष्ठा v4l2_rect *
__csi_get_compose(काष्ठा csi_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
		  क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_compose(&priv->sd, cfg,
						   CSI_SINK_PAD);
	अन्यथा
		वापस &priv->compose;
पूर्ण

अटल व्योम csi_try_crop(काष्ठा csi_priv *priv,
			 काष्ठा v4l2_rect *crop,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_mbus_framefmt *infmt,
			 काष्ठा v4l2_fwnode_endpoपूर्णांक *upstream_ep)
अणु
	u32 in_height;

	crop->width = min_t(__u32, infmt->width, crop->width);
	अगर (crop->left + crop->width > infmt->width)
		crop->left = infmt->width - crop->width;
	/* adjust crop left/width to h/w alignment restrictions */
	crop->left &= ~0x3;
	अगर (priv->active_output_pad == CSI_SRC_PAD_सूचीECT)
		crop->width &= ~0x7; /* multiple of 8 pixels (IC burst) */
	अन्यथा
		crop->width &= ~0x1; /* multiple of 2 pixels */

	in_height = infmt->height;
	अगर (infmt->field == V4L2_FIELD_ALTERNATE)
		in_height *= 2;

	/*
	 * FIXME: not sure why yet, but on पूर्णांकerlaced bt.656,
	 * changing the vertical cropping causes loss of vertical
	 * sync, so fix it to NTSC/PAL active lines. NTSC contains
	 * 2 extra lines of active video that need to be cropped.
	 */
	अगर (upstream_ep->bus_type == V4L2_MBUS_BT656 &&
	    (V4L2_FIELD_HAS_BOTH(infmt->field) ||
	     infmt->field == V4L2_FIELD_ALTERNATE)) अणु
		crop->height = in_height;
		crop->top = (in_height == 480) ? 2 : 0;
	पूर्ण अन्यथा अणु
		crop->height = min_t(__u32, in_height, crop->height);
		अगर (crop->top + crop->height > in_height)
			crop->top = in_height - crop->height;
	पूर्ण
पूर्ण

अटल पूर्णांक csi_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fwnode_endpoपूर्णांक upstream_ep = अणु .bus_type = 0 पूर्ण;
	स्थिर काष्ठा imx_media_pixfmt *incc;
	काष्ठा v4l2_mbus_framefmt *infmt;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, code->which);
	incc = imx_media_find_mbus_क्रमmat(infmt->code, PIXFMT_SEL_ANY);

	चयन (code->pad) अणु
	हाल CSI_SINK_PAD:
		ret = imx_media_क्रमागत_mbus_क्रमmats(&code->code, code->index,
						  PIXFMT_SEL_ANY);
		अवरोध;
	हाल CSI_SRC_PAD_सूचीECT:
	हाल CSI_SRC_PAD_IDMAC:
		ret = csi_get_upstream_endpoपूर्णांक(priv, &upstream_ep);
		अगर (ret) अणु
			v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
			जाओ out;
		पूर्ण

		अगर (requires_passthrough(&upstream_ep, infmt, incc)) अणु
			अगर (code->index != 0) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			code->code = infmt->code;
		पूर्ण अन्यथा अणु
			क्रमागत imx_pixfmt_sel fmt_sel =
				(incc->cs == IPUV3_COLORSPACE_YUV) ?
				PIXFMT_SEL_YUV : PIXFMT_SEL_RGB;

			ret = imx_media_क्रमागत_ipu_क्रमmats(&code->code,
							 code->index,
							 fmt_sel);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_rect *crop;
	पूर्णांक ret = 0;

	अगर (fse->pad >= CSI_NUM_PADS ||
	    fse->index > (fse->pad == CSI_SINK_PAD ? 0 : 3))
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	अगर (fse->pad == CSI_SINK_PAD) अणु
		fse->min_width = MIN_W;
		fse->max_width = MAX_W;
		fse->min_height = MIN_H;
		fse->max_height = MAX_H;
	पूर्ण अन्यथा अणु
		crop = __csi_get_crop(priv, cfg, fse->which);

		fse->min_width = fse->index & 1 ?
			crop->width / 2 : crop->width;
		fse->max_width = fse->min_width;
		fse->min_height = fse->index & 2 ?
			crop->height / 2 : crop->height;
		fse->max_height = fse->min_height;
	पूर्ण

	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fract *input_fi;
	काष्ठा v4l2_rect *crop;
	पूर्णांक ret = 0;

	अगर (fie->pad >= CSI_NUM_PADS ||
	    fie->index >= (fie->pad != CSI_SRC_PAD_IDMAC ?
			   1 : ARRAY_SIZE(csi_skip)))
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	input_fi = &priv->frame_पूर्णांकerval[CSI_SINK_PAD];
	crop = __csi_get_crop(priv, cfg, fie->which);

	अगर ((fie->width != crop->width && fie->width != crop->width / 2) ||
	    (fie->height != crop->height && fie->height != crop->height / 2)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	fie->पूर्णांकerval = *input_fi;

	अगर (fie->pad == CSI_SRC_PAD_IDMAC)
		csi_apply_skip_पूर्णांकerval(&csi_skip[fie->index],
					&fie->पूर्णांकerval);

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_get_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= CSI_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	fmt = __csi_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	अगर (!fmt) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	sdक्रमmat->क्रमmat = *fmt;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल व्योम csi_try_field(काष्ठा csi_priv *priv,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt =
		__csi_get_fmt(priv, cfg, CSI_SINK_PAD, sdक्रमmat->which);

	/*
	 * no restrictions on sink pad field type except must
	 * be initialized.
	 */
	अगर (sdक्रमmat->pad == CSI_SINK_PAD) अणु
		अगर (sdक्रमmat->क्रमmat.field == V4L2_FIELD_ANY)
			sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;
		वापस;
	पूर्ण

	चयन (infmt->field) अणु
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		/*
		 * If the user requests sequential at the source pad,
		 * allow it (aदीर्घ with possibly inverting field order).
		 * Otherwise passthrough the field type.
		 */
		अगर (!V4L2_FIELD_IS_SEQUENTIAL(sdक्रमmat->क्रमmat.field))
			sdक्रमmat->क्रमmat.field = infmt->field;
		अवरोध;
	हाल V4L2_FIELD_ALTERNATE:
		/*
		 * This driver करोes not support alternate field mode, and
		 * the CSI captures a whole frame, so the CSI never presents
		 * alternate mode at its source pads. If user has not
		 * alपढ़ोy requested sequential, translate ALTERNATE at
		 * sink pad to SEQ_TB or SEQ_BT at the source pad depending
		 * on input height (assume NTSC BT order अगर 480 total active
		 * frame lines, otherwise PAL TB order).
		 */
		अगर (!V4L2_FIELD_IS_SEQUENTIAL(sdक्रमmat->क्रमmat.field))
			sdक्रमmat->क्रमmat.field = (infmt->height == 480 / 2) ?
				V4L2_FIELD_SEQ_BT : V4L2_FIELD_SEQ_TB;
		अवरोध;
	शेष:
		/* Passthrough क्रम all other input field types */
		sdक्रमmat->क्रमmat.field = infmt->field;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम csi_try_fmt(काष्ठा csi_priv *priv,
			काष्ठा v4l2_fwnode_endpoपूर्णांक *upstream_ep,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat,
			काष्ठा v4l2_rect *crop,
			काष्ठा v4l2_rect *compose,
			स्थिर काष्ठा imx_media_pixfmt **cc)
अणु
	स्थिर काष्ठा imx_media_pixfmt *incc;
	काष्ठा v4l2_mbus_framefmt *infmt;
	u32 code;

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, sdक्रमmat->which);

	चयन (sdक्रमmat->pad) अणु
	हाल CSI_SRC_PAD_सूचीECT:
	हाल CSI_SRC_PAD_IDMAC:
		incc = imx_media_find_mbus_क्रमmat(infmt->code, PIXFMT_SEL_ANY);

		sdक्रमmat->क्रमmat.width = compose->width;
		sdक्रमmat->क्रमmat.height = compose->height;

		अगर (requires_passthrough(upstream_ep, infmt, incc)) अणु
			sdक्रमmat->क्रमmat.code = infmt->code;
			*cc = incc;
		पूर्ण अन्यथा अणु
			क्रमागत imx_pixfmt_sel fmt_sel =
				(incc->cs == IPUV3_COLORSPACE_YUV) ?
				PIXFMT_SEL_YUV : PIXFMT_SEL_RGB;

			*cc = imx_media_find_ipu_क्रमmat(sdक्रमmat->क्रमmat.code,
							fmt_sel);
			अगर (!*cc) अणु
				imx_media_क्रमागत_ipu_क्रमmats(&code, 0, fmt_sel);
				*cc = imx_media_find_ipu_क्रमmat(code, fmt_sel);
				sdक्रमmat->क्रमmat.code = (*cc)->codes[0];
			पूर्ण
		पूर्ण

		csi_try_field(priv, cfg, sdक्रमmat);

		/* propagate colorimetry from sink */
		sdक्रमmat->क्रमmat.colorspace = infmt->colorspace;
		sdक्रमmat->क्रमmat.xfer_func = infmt->xfer_func;
		sdक्रमmat->क्रमmat.quantization = infmt->quantization;
		sdक्रमmat->क्रमmat.ycbcr_enc = infmt->ycbcr_enc;

		अवरोध;
	हाल CSI_SINK_PAD:
		v4l_bound_align_image(&sdक्रमmat->क्रमmat.width, MIN_W, MAX_W,
				      W_ALIGN, &sdक्रमmat->क्रमmat.height,
				      MIN_H, MAX_H, H_ALIGN, S_ALIGN);

		*cc = imx_media_find_mbus_क्रमmat(sdक्रमmat->क्रमmat.code,
						 PIXFMT_SEL_ANY);
		अगर (!*cc) अणु
			imx_media_क्रमागत_mbus_क्रमmats(&code, 0,
						    PIXFMT_SEL_YUV_RGB);
			*cc = imx_media_find_mbus_क्रमmat(code,
							 PIXFMT_SEL_YUV_RGB);
			sdक्रमmat->क्रमmat.code = (*cc)->codes[0];
		पूर्ण

		csi_try_field(priv, cfg, sdक्रमmat);

		/* Reset crop and compose rectangles */
		crop->left = 0;
		crop->top = 0;
		crop->width = sdक्रमmat->क्रमmat.width;
		crop->height = sdक्रमmat->क्रमmat.height;
		अगर (sdक्रमmat->क्रमmat.field == V4L2_FIELD_ALTERNATE)
			crop->height *= 2;
		csi_try_crop(priv, crop, cfg, &sdक्रमmat->क्रमmat, upstream_ep);
		compose->left = 0;
		compose->top = 0;
		compose->width = crop->width;
		compose->height = crop->height;

		अवरोध;
	पूर्ण

	imx_media_try_colorimetry(&sdक्रमmat->क्रमmat,
			priv->active_output_pad == CSI_SRC_PAD_सूचीECT);
पूर्ण

अटल पूर्णांक csi_set_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fwnode_endpoपूर्णांक upstream_ep = अणु .bus_type = 0 पूर्ण;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_mbus_framefmt *fmt;
	काष्ठा v4l2_rect *crop, *compose;
	पूर्णांक ret;

	अगर (sdक्रमmat->pad >= CSI_NUM_PADS)
		वापस -EINVAL;

	ret = csi_get_upstream_endpoपूर्णांक(priv, &upstream_ep);
	अगर (ret) अणु
		v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
		वापस ret;
	पूर्ण

	mutex_lock(&priv->lock);

	अगर (priv->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	crop = __csi_get_crop(priv, cfg, sdक्रमmat->which);
	compose = __csi_get_compose(priv, cfg, sdक्रमmat->which);

	csi_try_fmt(priv, &upstream_ep, cfg, sdक्रमmat, crop, compose, &cc);

	fmt = __csi_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	*fmt = sdक्रमmat->क्रमmat;

	अगर (sdक्रमmat->pad == CSI_SINK_PAD) अणु
		पूर्णांक pad;

		/* propagate क्रमmat to source pads */
		क्रम (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) अणु
			स्थिर काष्ठा imx_media_pixfmt *outcc;
			काष्ठा v4l2_mbus_framefmt *outfmt;
			काष्ठा v4l2_subdev_क्रमmat क्रमmat;

			क्रमmat.pad = pad;
			क्रमmat.which = sdक्रमmat->which;
			क्रमmat.क्रमmat = sdक्रमmat->क्रमmat;
			csi_try_fmt(priv, &upstream_ep, cfg, &क्रमmat,
				    शून्य, compose, &outcc);

			outfmt = __csi_get_fmt(priv, cfg, pad, sdक्रमmat->which);
			*outfmt = क्रमmat.क्रमmat;

			अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
				priv->cc[pad] = outcc;
		पूर्ण
	पूर्ण

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		priv->cc[sdक्रमmat->pad] = cc;

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_get_selection(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *infmt;
	काष्ठा v4l2_rect *crop, *compose;
	पूर्णांक ret = 0;

	अगर (sel->pad != CSI_SINK_PAD)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, sel->which);
	crop = __csi_get_crop(priv, cfg, sel->which);
	compose = __csi_get_compose(priv, cfg, sel->which);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = infmt->width;
		sel->r.height = infmt->height;
		अगर (infmt->field == V4L2_FIELD_ALTERNATE)
			sel->r.height *= 2;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *crop;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = crop->width;
		sel->r.height = crop->height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r = *compose;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_set_scale(u32 *compose, u32 crop, u32 flags)
अणु
	अगर ((flags & (V4L2_SEL_FLAG_LE | V4L2_SEL_FLAG_GE)) ==
		     (V4L2_SEL_FLAG_LE | V4L2_SEL_FLAG_GE) &&
	    *compose != crop && *compose != crop / 2)
		वापस -दुस्फल;

	अगर (*compose <= crop / 2 ||
	    (*compose < crop * 3 / 4 && !(flags & V4L2_SEL_FLAG_GE)) ||
	    (*compose < crop && (flags & V4L2_SEL_FLAG_LE)))
		*compose = crop / 2;
	अन्यथा
		*compose = crop;

	वापस 0;
पूर्ण

अटल पूर्णांक csi_set_selection(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fwnode_endpoपूर्णांक upstream_ep = अणु .bus_type = 0 पूर्ण;
	काष्ठा v4l2_mbus_framefmt *infmt;
	काष्ठा v4l2_rect *crop, *compose;
	पूर्णांक pad, ret;

	अगर (sel->pad != CSI_SINK_PAD)
		वापस -EINVAL;

	ret = csi_get_upstream_endpoपूर्णांक(priv, &upstream_ep);
	अगर (ret) अणु
		v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
		वापस ret;
	पूर्ण

	mutex_lock(&priv->lock);

	अगर (priv->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, sel->which);
	crop = __csi_get_crop(priv, cfg, sel->which);
	compose = __csi_get_compose(priv, cfg, sel->which);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		/*
		 * Modअगरying the crop rectangle always changes the क्रमmat on
		 * the source pads. If the KEEP_CONFIG flag is set, just वापस
		 * the current crop rectangle.
		 */
		अगर (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) अणु
			sel->r = priv->crop;
			अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY)
				*crop = sel->r;
			जाओ out;
		पूर्ण

		csi_try_crop(priv, &sel->r, cfg, infmt, &upstream_ep);

		*crop = sel->r;

		/* Reset scaling to 1:1 */
		compose->width = crop->width;
		compose->height = crop->height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		/*
		 * Modअगरying the compose rectangle always changes the क्रमmat on
		 * the source pads. If the KEEP_CONFIG flag is set, just वापस
		 * the current compose rectangle.
		 */
		अगर (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) अणु
			sel->r = priv->compose;
			अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY)
				*compose = sel->r;
			जाओ out;
		पूर्ण

		sel->r.left = 0;
		sel->r.top = 0;
		ret = csi_set_scale(&sel->r.width, crop->width, sel->flags);
		अगर (ret)
			जाओ out;
		ret = csi_set_scale(&sel->r.height, crop->height, sel->flags);
		अगर (ret)
			जाओ out;

		*compose = sel->r;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Reset source pads to sink compose rectangle */
	क्रम (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) अणु
		काष्ठा v4l2_mbus_framefmt *outfmt;

		outfmt = __csi_get_fmt(priv, cfg, pad, sel->which);
		outfmt->width = compose->width;
		outfmt->height = compose->height;
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
			       काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type != V4L2_EVENT_IMX_FRAME_INTERVAL_ERROR)
		वापस -EINVAL;
	अगर (sub->id != 0)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
पूर्ण

अटल पूर्णांक csi_unsubscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				 काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण

अटल पूर्णांक csi_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा ipu_csi *csi;
	पूर्णांक i, ret;
	u32 code;

	/* get handle to IPU CSI */
	csi = ipu_csi_get(priv->ipu, priv->csi_id);
	अगर (IS_ERR(csi)) अणु
		v4l2_err(&priv->sd, "failed to get CSI%d\n", priv->csi_id);
		वापस PTR_ERR(csi);
	पूर्ण
	priv->csi = csi;

	क्रम (i = 0; i < CSI_NUM_PADS; i++) अणु
		code = 0;
		अगर (i != CSI_SINK_PAD)
			imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV);

		/* set a शेष mbus क्रमmat  */
		ret = imx_media_init_mbus_fmt(&priv->क्रमmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4L2_FIELD_NONE, &priv->cc[i]);
		अगर (ret)
			जाओ put_csi;

		/* init शेष frame पूर्णांकerval */
		priv->frame_पूर्णांकerval[i].numerator = 1;
		priv->frame_पूर्णांकerval[i].denominator = 30;
	पूर्ण

	/* disable frame skipping */
	priv->skip = &csi_skip[0];

	/* init शेष crop and compose rectangle sizes */
	priv->crop.width = IMX_MEDIA_DEF_PIX_WIDTH;
	priv->crop.height = IMX_MEDIA_DEF_PIX_HEIGHT;
	priv->compose.width = IMX_MEDIA_DEF_PIX_WIDTH;
	priv->compose.height = IMX_MEDIA_DEF_PIX_HEIGHT;

	priv->fim = imx_media_fim_init(&priv->sd);
	अगर (IS_ERR(priv->fim)) अणु
		ret = PTR_ERR(priv->fim);
		जाओ put_csi;
	पूर्ण

	priv->vdev = imx_media_capture_device_init(priv->sd.dev, &priv->sd,
						   CSI_SRC_PAD_IDMAC, true);
	अगर (IS_ERR(priv->vdev)) अणु
		ret = PTR_ERR(priv->vdev);
		जाओ मुक्त_fim;
	पूर्ण

	ret = imx_media_capture_device_रेजिस्टर(priv->vdev, 0);
	अगर (ret)
		जाओ हटाओ_vdev;

	वापस 0;

हटाओ_vdev:
	imx_media_capture_device_हटाओ(priv->vdev);
मुक्त_fim:
	अगर (priv->fim)
		imx_media_fim_मुक्त(priv->fim);
put_csi:
	ipu_csi_put(priv->csi);
	वापस ret;
पूर्ण

अटल व्योम csi_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);

	imx_media_capture_device_unरेजिस्टर(priv->vdev);
	imx_media_capture_device_हटाओ(priv->vdev);

	अगर (priv->fim)
		imx_media_fim_मुक्त(priv->fim);

	अगर (priv->csi)
		ipu_csi_put(priv->csi);
पूर्ण

/*
 * The CSI has only one fwnode endpoपूर्णांक, at the sink pad. Verअगरy the
 * endpoपूर्णांक beदीर्घs to us, and वापस CSI_SINK_PAD.
 */
अटल पूर्णांक csi_get_fwnode_pad(काष्ठा media_entity *entity,
			      काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा csi_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा fwnode_handle *csi_port = dev_fwnode(priv->dev);
	काष्ठा fwnode_handle *csi_ep;
	पूर्णांक ret;

	csi_ep = fwnode_get_next_child_node(csi_port, शून्य);

	ret = endpoपूर्णांक->local_fwnode == csi_ep ? CSI_SINK_PAD : -ENXIO;

	fwnode_handle_put(csi_ep);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations csi_entity_ops = अणु
	.link_setup = csi_link_setup,
	.link_validate = v4l2_subdev_link_validate,
	.get_fwnode_pad = csi_get_fwnode_pad,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops csi_core_ops = अणु
	.subscribe_event = csi_subscribe_event,
	.unsubscribe_event = csi_unsubscribe_event,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops csi_video_ops = अणु
	.g_frame_पूर्णांकerval = csi_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = csi_s_frame_पूर्णांकerval,
	.s_stream = csi_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops csi_pad_ops = अणु
	.init_cfg = imx_media_init_cfg,
	.क्रमागत_mbus_code = csi_क्रमागत_mbus_code,
	.क्रमागत_frame_size = csi_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = csi_क्रमागत_frame_पूर्णांकerval,
	.get_fmt = csi_get_fmt,
	.set_fmt = csi_set_fmt,
	.get_selection = csi_get_selection,
	.set_selection = csi_set_selection,
	.link_validate = csi_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csi_subdev_ops = अणु
	.core = &csi_core_ops,
	.video = &csi_video_ops,
	.pad = &csi_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops csi_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = csi_रेजिस्टरed,
	.unरेजिस्टरed = csi_unरेजिस्टरed,
पूर्ण;

अटल पूर्णांक imx_csi_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा csi_priv *priv = notअगरier_to_dev(notअगरier);
	काष्ठा media_pad *sink = &priv->sd.entity.pads[CSI_SINK_PAD];

	/*
	 * If the subdev is a video mux, it must be one of the CSI
	 * muxes. Mark it as such via its group id.
	 */
	अगर (sd->entity.function == MEDIA_ENT_F_VID_MUX)
		sd->grp_id = IMX_MEDIA_GRP_ID_CSI_MUX;

	वापस v4l2_create_fwnode_links_to_pad(sd, sink, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations csi_notअगरy_ops = अणु
	.bound = imx_csi_notअगरy_bound,
पूर्ण;

अटल पूर्णांक imx_csi_async_रेजिस्टर(काष्ठा csi_priv *priv)
अणु
	काष्ठा v4l2_async_subdev *asd = शून्य;
	काष्ठा fwnode_handle *ep;
	अचिन्हित पूर्णांक port;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&priv->notअगरier);

	/* get this CSI's port id */
	ret = fwnode_property_पढ़ो_u32(dev_fwnode(priv->dev), "reg", &port);
	अगर (ret < 0)
		वापस ret;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(priv->dev->parent),
					     port, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (ep) अणु
		asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
			&priv->notअगरier, ep, काष्ठा v4l2_async_subdev);

		fwnode_handle_put(ep);

		अगर (IS_ERR(asd)) अणु
			ret = PTR_ERR(asd);
			/* OK अगर asd alपढ़ोy exists */
			अगर (ret != -EEXIST)
				वापस ret;
		पूर्ण
	पूर्ण

	priv->notअगरier.ops = &csi_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&priv->sd,
						  &priv->notअगरier);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&priv->sd);
पूर्ण

अटल पूर्णांक imx_csi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipu_client_platक्रमmdata *pdata;
	काष्ठा pinctrl *pinctrl;
	काष्ठा csi_priv *priv;
	पूर्णांक i, ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, &priv->sd);
	priv->dev = &pdev->dev;

	ret = dma_set_coherent_mask(priv->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	/* get parent IPU */
	priv->ipu = dev_get_drvdata(priv->dev->parent);

	/* get our CSI id */
	pdata = priv->dev->platक्रमm_data;
	priv->csi_id = pdata->csi;
	priv->smfc_id = (priv->csi_id == 0) ? 0 : 2;

	priv->active_output_pad = CSI_SRC_PAD_IDMAC;

	समयr_setup(&priv->eof_समयout_समयr, csi_idmac_eof_समयout, 0);
	spin_lock_init(&priv->irqlock);

	v4l2_subdev_init(&priv->sd, &csi_subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.पूर्णांकernal_ops = &csi_पूर्णांकernal_ops;
	priv->sd.entity.ops = &csi_entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->sd.dev = &pdev->dev;
	priv->sd.fwnode = of_fwnode_handle(pdata->of_node);
	priv->sd.owner = THIS_MODULE;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	priv->sd.grp_id = priv->csi_id ?
		IMX_MEDIA_GRP_ID_IPU_CSI1 : IMX_MEDIA_GRP_ID_IPU_CSI0;
	imx_media_grp_id_to_sd_name(priv->sd.name, माप(priv->sd.name),
				    priv->sd.grp_id, ipu_get_num(priv->ipu));

	क्रम (i = 0; i < CSI_NUM_PADS; i++)
		priv->pad[i].flags = (i == CSI_SINK_PAD) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&priv->sd.entity, CSI_NUM_PADS,
				     priv->pad);
	अगर (ret)
		वापस ret;

	mutex_init(&priv->lock);

	v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);
	priv->sd.ctrl_handler = &priv->ctrl_hdlr;

	/*
	 * The IPUv3 driver did not assign an of_node to this
	 * device. As a result, pinctrl करोes not स्वतःmatically
	 * configure our pin groups, so we need to करो that manually
	 * here, after setting this device's of_node.
	 */
	priv->dev->of_node = pdata->of_node;
	pinctrl = devm_pinctrl_get_select_शेष(priv->dev);
	अगर (IS_ERR(pinctrl)) अणु
		ret = PTR_ERR(pinctrl);
		dev_dbg(priv->dev,
			"devm_pinctrl_get_select_default() failed: %d\n", ret);
		अगर (ret != -ENODEV)
			जाओ मुक्त;
	पूर्ण

	ret = imx_csi_async_रेजिस्टर(priv);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	v4l2_async_notअगरier_unरेजिस्टर(&priv->notअगरier);
	v4l2_async_notअगरier_cleanup(&priv->notअगरier);
मुक्त:
	v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
	mutex_destroy(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_csi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *sd = platक्रमm_get_drvdata(pdev);
	काष्ठा csi_priv *priv = sd_to_dev(sd);

	v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
	mutex_destroy(&priv->lock);
	v4l2_async_notअगरier_unरेजिस्टर(&priv->notअगरier);
	v4l2_async_notअगरier_cleanup(&priv->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id imx_csi_ids[] = अणु
	अणु .name = "imx-ipuv3-csi" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, imx_csi_ids);

अटल काष्ठा platक्रमm_driver imx_csi_driver = अणु
	.probe = imx_csi_probe,
	.हटाओ = imx_csi_हटाओ,
	.id_table = imx_csi_ids,
	.driver = अणु
		.name = "imx-ipuv3-csi",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_csi_driver);

MODULE_DESCRIPTION("i.MX CSI subdev driver");
MODULE_AUTHOR("Steve Longerbeam <steve_longerbeam@mentor.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:imx-ipuv3-csi");
