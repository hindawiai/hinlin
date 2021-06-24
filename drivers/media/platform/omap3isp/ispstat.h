<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispस्थिति.स
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

#अगर_अघोषित OMAP3_ISP_STAT_H
#घोषणा OMAP3_ISP_STAT_H

#समावेश <linux/types.h>
#समावेश <linux/omap3isp.h>
#समावेश <media/v4l2-event.h>

#समावेश "isp.h"
#समावेश "ispvideo.h"

#घोषणा STAT_MAX_BUFS		5
#घोषणा STAT_NEVENTS		8

#घोषणा STAT_BUF_DONE		0	/* Buffer is पढ़ोy */
#घोषणा STAT_NO_BUF		1	/* An error has occurred */
#घोषणा STAT_BUF_WAITING_DMA	2	/* Histogram only: DMA is running */

काष्ठा dma_chan;
काष्ठा ispstat;

काष्ठा ispstat_buffer अणु
	काष्ठा sg_table sgt;
	व्योम *virt_addr;
	dma_addr_t dma_addr;
	काष्ठा बारpec64 ts;
	u32 buf_size;
	u32 frame_number;
	u16 config_counter;
	u8 empty;
पूर्ण;

काष्ठा ispstat_ops अणु
	/*
	 * Validate new params configuration.
	 * new_conf->buf_size value must be changed to the exact buffer size
	 * necessary क्रम the new configuration अगर it's smaller.
	 */
	पूर्णांक (*validate_params)(काष्ठा ispstat *stat, व्योम *new_conf);

	/*
	 * Save new params configuration.
	 * stat->priv->buf_size value must be set to the exact buffer size क्रम
	 * the new configuration.
	 * stat->update is set to 1 अगर new configuration is dअगरferent than
	 * current one.
	 */
	व्योम (*set_params)(काष्ठा ispstat *stat, व्योम *new_conf);

	/* Apply stored configuration. */
	व्योम (*setup_regs)(काष्ठा ispstat *stat, व्योम *priv);

	/* Enable/Disable module. */
	व्योम (*enable)(काष्ठा ispstat *stat, पूर्णांक enable);

	/* Verअगरy is module is busy. */
	पूर्णांक (*busy)(काष्ठा ispstat *stat);

	/* Used क्रम specअगरic operations during generic buf process task. */
	पूर्णांक (*buf_process)(काष्ठा ispstat *stat);
पूर्ण;

क्रमागत ispstat_state_t अणु
	ISPSTAT_DISABLED = 0,
	ISPSTAT_DISABLING,
	ISPSTAT_ENABLED,
	ISPSTAT_ENABLING,
	ISPSTAT_SUSPENDED,
पूर्ण;

काष्ठा ispstat अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;	/* sink pad */

	/* Control */
	अचिन्हित configured:1;
	अचिन्हित update:1;
	अचिन्हित buf_processing:1;
	अचिन्हित sbl_ovl_recover:1;
	u8 inc_config;
	atomic_t buf_err;
	क्रमागत ispstat_state_t state;	/* enabling/disabling state */
	काष्ठा isp_device *isp;
	व्योम *priv;		/* poपूर्णांकer to priv config काष्ठा */
	व्योम *recover_priv;	/* poपूर्णांकer to recover priv configuration */
	काष्ठा mutex ioctl_lock; /* serialize निजी ioctl */

	स्थिर काष्ठा ispstat_ops *ops;

	/* Buffer */
	u8 रुको_acc_frames;
	u16 config_counter;
	u32 frame_number;
	u32 buf_size;
	u32 buf_alloc_size;
	काष्ठा dma_chan *dma_ch;
	अचिन्हित दीर्घ event_type;
	काष्ठा ispstat_buffer *buf;
	काष्ठा ispstat_buffer *active_buf;
	काष्ठा ispstat_buffer *locked_buf;
पूर्ण;

काष्ठा ispstat_generic_config अणु
	/*
	 * Fields must be in the same order as in:
	 *  - omap3isp_h3a_aewb_config
	 *  - omap3isp_h3a_af_config
	 *  - omap3isp_hist_config
	 */
	u32 buf_size;
	u16 config_counter;
पूर्ण;

पूर्णांक omap3isp_stat_config(काष्ठा ispstat *stat, व्योम *new_conf);
पूर्णांक omap3isp_stat_request_statistics(काष्ठा ispstat *stat,
				     काष्ठा omap3isp_stat_data *data);
पूर्णांक omap3isp_stat_request_statistics_समय32(काष्ठा ispstat *stat,
				     काष्ठा omap3isp_stat_data_समय32 *data);
पूर्णांक omap3isp_stat_init(काष्ठा ispstat *stat, स्थिर अक्षर *name,
		       स्थिर काष्ठा v4l2_subdev_ops *sd_ops);
व्योम omap3isp_stat_cleanup(काष्ठा ispstat *stat);
पूर्णांक omap3isp_stat_subscribe_event(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_fh *fh,
				  काष्ठा v4l2_event_subscription *sub);
पूर्णांक omap3isp_stat_unsubscribe_event(काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_fh *fh,
				    काष्ठा v4l2_event_subscription *sub);
पूर्णांक omap3isp_stat_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable);

पूर्णांक omap3isp_stat_busy(काष्ठा ispstat *stat);
पूर्णांक omap3isp_stat_pcr_busy(काष्ठा ispstat *stat);
व्योम omap3isp_stat_suspend(काष्ठा ispstat *stat);
व्योम omap3isp_stat_resume(काष्ठा ispstat *stat);
पूर्णांक omap3isp_stat_enable(काष्ठा ispstat *stat, u8 enable);
व्योम omap3isp_stat_sbl_overflow(काष्ठा ispstat *stat);
व्योम omap3isp_stat_isr(काष्ठा ispstat *stat);
व्योम omap3isp_stat_isr_frame_sync(काष्ठा ispstat *stat);
व्योम omap3isp_stat_dma_isr(काष्ठा ispstat *stat);
पूर्णांक omap3isp_stat_रेजिस्टर_entities(काष्ठा ispstat *stat,
				    काष्ठा v4l2_device *vdev);
व्योम omap3isp_stat_unरेजिस्टर_entities(काष्ठा ispstat *stat);

#पूर्ण_अगर /* OMAP3_ISP_STAT_H */
