<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * V4L2 Media Controller Driver क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#अगर_अघोषित _IMX_MEDIA_H
#घोषणा _IMX_MEDIA_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <video/imx-ipu-v3.h>

#घोषणा IMX_MEDIA_DEF_PIX_WIDTH		640
#घोषणा IMX_MEDIA_DEF_PIX_HEIGHT	480

/*
 * Enumeration of the IPU पूर्णांकernal sub-devices
 */
क्रमागत अणु
	IPU_CSI0 = 0,
	IPU_CSI1,
	IPU_VDIC,
	IPU_IC_PRP,
	IPU_IC_PRPENC,
	IPU_IC_PRPVF,
	NUM_IPU_SUBDEVS,
पूर्ण;

/*
 * Pad definitions क्रम the subdevs with multiple source or
 * sink pads
 */

/* ipu_csi */
क्रमागत अणु
	CSI_SINK_PAD = 0,
	CSI_SRC_PAD_सूचीECT,
	CSI_SRC_PAD_IDMAC,
	CSI_NUM_PADS,
पूर्ण;

/* ipu_vdic */
क्रमागत अणु
	VDIC_SINK_PAD_सूचीECT = 0,
	VDIC_SINK_PAD_IDMAC,
	VDIC_SRC_PAD_सूचीECT,
	VDIC_NUM_PADS,
पूर्ण;

/* ipu_ic_prp */
क्रमागत अणु
	PRP_SINK_PAD = 0,
	PRP_SRC_PAD_PRPENC,
	PRP_SRC_PAD_PRPVF,
	PRP_NUM_PADS,
पूर्ण;

/* ipu_ic_prpencvf */
क्रमागत अणु
	PRPENCVF_SINK_PAD = 0,
	PRPENCVF_SRC_PAD,
	PRPENCVF_NUM_PADS,
पूर्ण;

/* How दीर्घ to रुको क्रम खातापूर्ण पूर्णांकerrupts in the buffer-capture subdevs */
#घोषणा IMX_MEDIA_खातापूर्ण_TIMEOUT       2000

काष्ठा imx_media_pixfmt अणु
	/* the in-memory FourCC pixel क्रमmat */
	u32     fourcc;
	/*
	 * the set of equivalent media bus codes क्रम the fourcc.
	 * NOTE! codes poपूर्णांकer is शून्य क्रम in-memory-only क्रमmats.
	 */
	स्थिर u32 *codes;
	पूर्णांक     bpp;     /* total bpp */
	/* cycles per pixel क्रम generic (bayer) क्रमmats क्रम the parallel bus */
	पूर्णांक	cycles;
	क्रमागत ipu_color_space cs;
	bool    planar;  /* is a planar क्रमmat */
	bool    bayer;   /* is a raw bayer क्रमmat */
	bool    ipufmt;  /* is one of the IPU पूर्णांकernal क्रमmats */
पूर्ण;

क्रमागत imx_pixfmt_sel अणु
	PIXFMT_SEL_YUV   = BIT(0), /* select YUV क्रमmats */
	PIXFMT_SEL_RGB   = BIT(1), /* select RGB क्रमmats */
	PIXFMT_SEL_BAYER = BIT(2), /* select BAYER क्रमmats */
	PIXFMT_SEL_IPU   = BIT(3), /* select IPU-पूर्णांकernal क्रमmats */
	PIXFMT_SEL_YUV_RGB = PIXFMT_SEL_YUV | PIXFMT_SEL_RGB,
	PIXFMT_SEL_ANY = PIXFMT_SEL_YUV | PIXFMT_SEL_RGB | PIXFMT_SEL_BAYER,
पूर्ण;

काष्ठा imx_media_buffer अणु
	काष्ठा vb2_v4l2_buffer vbuf; /* v4l buffer must be first */
	काष्ठा list_head  list;
पूर्ण;

काष्ठा imx_media_video_dev अणु
	काष्ठा video_device *vfd;

	/* the user क्रमmat */
	काष्ठा v4l2_pix_क्रमmat fmt;
	/* the compose rectangle */
	काष्ठा v4l2_rect compose;
	स्थिर काष्ठा imx_media_pixfmt *cc;

	/* links this vdev to master list */
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत काष्ठा imx_media_buffer *to_imx_media_vb(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	वापस container_of(vbuf, काष्ठा imx_media_buffer, vbuf);
पूर्ण

/*
 * to support control inheritance to video devices, this
 * retrieves a pad's list_head of video devices that can
 * be reached from the pad. Note that only the lists in
 * source pads get populated, sink pads have empty lists.
 */
अटल अंतरभूत काष्ठा list_head *
to_pad_vdev_list(काष्ठा v4l2_subdev *sd, पूर्णांक pad_index)
अणु
	काष्ठा list_head *vdev_list = sd->host_priv;

	वापस vdev_list ? &vdev_list[pad_index] : शून्य;
पूर्ण

/* an entry in a pad's video device list */
काष्ठा imx_media_pad_vdev अणु
	काष्ठा imx_media_video_dev *vdev;
	काष्ठा list_head list;
पूर्ण;

काष्ठा imx_media_dev अणु
	काष्ठा media_device md;
	काष्ठा v4l2_device  v4l2_dev;

	/* the pipeline object */
	काष्ठा media_pipeline pipe;

	काष्ठा mutex mutex; /* protect elements below */

	/* master video device list */
	काष्ठा list_head vdev_list;

	/* IPUs this media driver control, valid after subdevs bound */
	काष्ठा ipu_soc *ipu[2];

	/* क्रम async subdev registration */
	काष्ठा v4l2_async_notअगरier notअगरier;

	/* IC scaler/CSC mem2mem video device */
	काष्ठा imx_media_video_dev *m2m_vdev;

	/* the IPU पूर्णांकernal subdev's रेजिस्टरed synchronously */
	काष्ठा v4l2_subdev *sync_sd[2][NUM_IPU_SUBDEVS];
पूर्ण;

/* imx-media-utils.c */
स्थिर काष्ठा imx_media_pixfmt *
imx_media_find_pixel_क्रमmat(u32 fourcc, क्रमागत imx_pixfmt_sel sel);
पूर्णांक imx_media_क्रमागत_pixel_क्रमmats(u32 *fourcc, u32 index,
				 क्रमागत imx_pixfmt_sel sel, u32 code);
स्थिर काष्ठा imx_media_pixfmt *
imx_media_find_mbus_क्रमmat(u32 code, क्रमागत imx_pixfmt_sel sel);
पूर्णांक imx_media_क्रमागत_mbus_क्रमmats(u32 *code, u32 index,
				क्रमागत imx_pixfmt_sel sel);

अटल अंतरभूत स्थिर काष्ठा imx_media_pixfmt *
imx_media_find_ipu_क्रमmat(u32 code, क्रमागत imx_pixfmt_sel fmt_sel)
अणु
	वापस imx_media_find_mbus_क्रमmat(code, fmt_sel | PIXFMT_SEL_IPU);
पूर्ण

अटल अंतरभूत पूर्णांक imx_media_क्रमागत_ipu_क्रमmats(u32 *code, u32 index,
					     क्रमागत imx_pixfmt_sel fmt_sel)
अणु
	वापस imx_media_क्रमागत_mbus_क्रमmats(code, index,
					  fmt_sel | PIXFMT_SEL_IPU);
पूर्ण

पूर्णांक imx_media_init_mbus_fmt(काष्ठा v4l2_mbus_framefmt *mbus,
			    u32 width, u32 height, u32 code, u32 field,
			    स्थिर काष्ठा imx_media_pixfmt **cc);
पूर्णांक imx_media_init_cfg(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg);
व्योम imx_media_try_colorimetry(काष्ठा v4l2_mbus_framefmt *tryfmt,
			       bool ic_route);
पूर्णांक imx_media_mbus_fmt_to_pix_fmt(काष्ठा v4l2_pix_क्रमmat *pix,
				  स्थिर काष्ठा v4l2_mbus_framefmt *mbus,
				  स्थिर काष्ठा imx_media_pixfmt *cc);
पूर्णांक imx_media_mbus_fmt_to_ipu_image(काष्ठा ipu_image *image,
				    स्थिर काष्ठा v4l2_mbus_framefmt *mbus);
पूर्णांक imx_media_ipu_image_to_mbus_fmt(काष्ठा v4l2_mbus_framefmt *mbus,
				    स्थिर काष्ठा ipu_image *image);
व्योम imx_media_grp_id_to_sd_name(अक्षर *sd_name, पूर्णांक sz,
				 u32 grp_id, पूर्णांक ipu_id);
काष्ठा v4l2_subdev *
imx_media_find_subdev_by_fwnode(काष्ठा imx_media_dev *imxmd,
				काष्ठा fwnode_handle *fwnode);
काष्ठा v4l2_subdev *
imx_media_find_subdev_by_devname(काष्ठा imx_media_dev *imxmd,
				 स्थिर अक्षर *devname);
व्योम imx_media_add_video_device(काष्ठा imx_media_dev *imxmd,
				काष्ठा imx_media_video_dev *vdev);
पूर्णांक imx_media_pipeline_csi2_channel(काष्ठा media_entity *start_entity);
काष्ठा media_pad *
imx_media_pipeline_pad(काष्ठा media_entity *start_entity, u32 grp_id,
		       क्रमागत v4l2_buf_type buftype, bool upstream);
काष्ठा v4l2_subdev *
imx_media_pipeline_subdev(काष्ठा media_entity *start_entity, u32 grp_id,
			  bool upstream);
काष्ठा video_device *
imx_media_pipeline_video_device(काष्ठा media_entity *start_entity,
				क्रमागत v4l2_buf_type buftype, bool upstream);
काष्ठा fwnode_handle *imx_media_get_pad_fwnode(काष्ठा media_pad *pad);

काष्ठा imx_media_dma_buf अणु
	व्योम          *virt;
	dma_addr_t     phys;
	अचिन्हित दीर्घ  len;
पूर्ण;

व्योम imx_media_मुक्त_dma_buf(काष्ठा device *dev,
			    काष्ठा imx_media_dma_buf *buf);
पूर्णांक imx_media_alloc_dma_buf(काष्ठा device *dev,
			    काष्ठा imx_media_dma_buf *buf,
			    पूर्णांक size);

पूर्णांक imx_media_pipeline_set_stream(काष्ठा imx_media_dev *imxmd,
				  काष्ठा media_entity *entity,
				  bool on);

/* imx-media-dev-common.c */
पूर्णांक imx_media_probe_complete(काष्ठा v4l2_async_notअगरier *notअगरier);
काष्ठा imx_media_dev *imx_media_dev_init(काष्ठा device *dev,
					 स्थिर काष्ठा media_device_ops *ops);
पूर्णांक imx_media_dev_notअगरier_रेजिस्टर(काष्ठा imx_media_dev *imxmd,
			    स्थिर काष्ठा v4l2_async_notअगरier_operations *ops);

/* imx-media-fim.c */
काष्ठा imx_media_fim;
व्योम imx_media_fim_eof_monitor(काष्ठा imx_media_fim *fim, kसमय_प्रकार बारtamp);
पूर्णांक imx_media_fim_set_stream(काष्ठा imx_media_fim *fim,
			     स्थिर काष्ठा v4l2_fract *frame_पूर्णांकerval,
			     bool on);
पूर्णांक imx_media_fim_add_controls(काष्ठा imx_media_fim *fim);
काष्ठा imx_media_fim *imx_media_fim_init(काष्ठा v4l2_subdev *sd);
व्योम imx_media_fim_मुक्त(काष्ठा imx_media_fim *fim);

/* imx-media-पूर्णांकernal-sd.c */
पूर्णांक imx_media_रेजिस्टर_ipu_पूर्णांकernal_subdevs(काष्ठा imx_media_dev *imxmd,
					    काष्ठा v4l2_subdev *csi);
व्योम imx_media_unरेजिस्टर_ipu_पूर्णांकernal_subdevs(काष्ठा imx_media_dev *imxmd);

/* imx-media-of.c */
पूर्णांक imx_media_add_of_subdevs(काष्ठा imx_media_dev *dev,
			     काष्ठा device_node *np);
पूर्णांक imx_media_of_add_csi(काष्ठा imx_media_dev *imxmd,
			 काष्ठा device_node *csi_np);

/* imx-media-vdic.c */
काष्ठा v4l2_subdev *imx_media_vdic_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
					    काष्ठा device *ipu_dev,
					    काष्ठा ipu_soc *ipu,
					    u32 grp_id);
पूर्णांक imx_media_vdic_unरेजिस्टर(काष्ठा v4l2_subdev *sd);

/* imx-ic-common.c */
काष्ठा v4l2_subdev *imx_media_ic_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
					  काष्ठा device *ipu_dev,
					  काष्ठा ipu_soc *ipu,
					  u32 grp_id);
पूर्णांक imx_media_ic_unरेजिस्टर(काष्ठा v4l2_subdev *sd);

/* imx-media-capture.c */
काष्ठा imx_media_video_dev *
imx_media_capture_device_init(काष्ठा device *dev, काष्ठा v4l2_subdev *src_sd,
			      पूर्णांक pad, bool legacy_api);
व्योम imx_media_capture_device_हटाओ(काष्ठा imx_media_video_dev *vdev);
पूर्णांक imx_media_capture_device_रेजिस्टर(काष्ठा imx_media_video_dev *vdev,
				      u32 link_flags);
व्योम imx_media_capture_device_unरेजिस्टर(काष्ठा imx_media_video_dev *vdev);
काष्ठा imx_media_buffer *
imx_media_capture_device_next_buf(काष्ठा imx_media_video_dev *vdev);
व्योम imx_media_capture_device_error(काष्ठा imx_media_video_dev *vdev);

/* imx-media-csc-scaler.c */
काष्ठा imx_media_video_dev *
imx_media_csc_scaler_device_init(काष्ठा imx_media_dev *dev);
पूर्णांक imx_media_csc_scaler_device_रेजिस्टर(काष्ठा imx_media_video_dev *vdev);
व्योम imx_media_csc_scaler_device_unरेजिस्टर(काष्ठा imx_media_video_dev *vdev);

/* subdev group ids */
#घोषणा IMX_MEDIA_GRP_ID_CSI2          BIT(8)
#घोषणा IMX_MEDIA_GRP_ID_CSI           BIT(9)
#घोषणा IMX_MEDIA_GRP_ID_IPU_CSI_BIT   10
#घोषणा IMX_MEDIA_GRP_ID_IPU_CSI       (0x3 << IMX_MEDIA_GRP_ID_IPU_CSI_BIT)
#घोषणा IMX_MEDIA_GRP_ID_IPU_CSI0      BIT(IMX_MEDIA_GRP_ID_IPU_CSI_BIT)
#घोषणा IMX_MEDIA_GRP_ID_IPU_CSI1      (2 << IMX_MEDIA_GRP_ID_IPU_CSI_BIT)
#घोषणा IMX_MEDIA_GRP_ID_IPU_VDIC      BIT(12)
#घोषणा IMX_MEDIA_GRP_ID_IPU_IC_PRP    BIT(13)
#घोषणा IMX_MEDIA_GRP_ID_IPU_IC_PRPENC BIT(14)
#घोषणा IMX_MEDIA_GRP_ID_IPU_IC_PRPVF  BIT(15)
#घोषणा IMX_MEDIA_GRP_ID_CSI_MUX       BIT(16)

#पूर्ण_अगर
