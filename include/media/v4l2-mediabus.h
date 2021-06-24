<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Media Bus API header
 *
 * Copyright (C) 2009, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#अगर_अघोषित V4L2_MEDIABUS_H
#घोषणा V4L2_MEDIABUS_H

#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/bitops.h>

/*
 * How to use the V4L2_MBUS_* flags:
 * Flags are defined क्रम each of the possible states and values of a media
 * bus configuration parameter. One and only one bit of each group of flags
 * shall be set by the users of the v4l2_subdev_pad_ops.get_mbus_config and
 * v4l2_subdev_pad_ops.set_mbus_config operations to ensure that no
 * conflicting settings are specअगरied when reporting and setting the media bus
 * configuration with the two operations respectively. For example, it is
 * invalid to set or clear both the V4L2_MBUS_HSYNC_ACTIVE_HIGH and the
 * V4L2_MBUS_HSYNC_ACTIVE_LOW flag at the same समय. Instead either flag
 * V4L2_MBUS_HSYNC_ACTIVE_HIGH or flag V4L2_MBUS_HSYNC_ACTIVE_LOW shall be
 * set. The same is true क्रम the V4L2_MBUS_CSI2_1/2/3/4_LANE flags group: only
 * one of these four bits shall be set.
 *
 * TODO: replace the existing V4L2_MBUS_* flags with काष्ठाures of fields
 * to aव्योम conflicting settings.
 *
 * In example:
 *     #घोषणा V4L2_MBUS_HSYNC_ACTIVE_HIGH             BIT(2)
 *     #घोषणा V4L2_MBUS_HSYNC_ACTIVE_LOW              BIT(3)
 * will be replaced by a field whose value reports the पूर्णांकended active state of
 * the संकेत:
 *     अचिन्हित पूर्णांक v4l2_mbus_hsync_active : 1;
 */

/* Parallel flags */
/*
 * The client runs in master or in slave mode. By "Master mode" an operation
 * mode is meant, when the client (e.g., a camera sensor) is producing
 * horizontal and vertical synchronisation. In "Slave mode" the host is
 * providing these संकेतs to the slave.
 */
#घोषणा V4L2_MBUS_MASTER			BIT(0)
#घोषणा V4L2_MBUS_SLAVE				BIT(1)
/*
 * Signal polarity flags
 * Note: in BT.656 mode HSYNC, FIELD, and VSYNC are unused
 * V4L2_MBUS_[HV]SYNC* flags should be also used क्रम specअगरying
 * configuration of hardware that uses [HV]REF संकेतs
 */
#घोषणा V4L2_MBUS_HSYNC_ACTIVE_HIGH		BIT(2)
#घोषणा V4L2_MBUS_HSYNC_ACTIVE_LOW		BIT(3)
#घोषणा V4L2_MBUS_VSYNC_ACTIVE_HIGH		BIT(4)
#घोषणा V4L2_MBUS_VSYNC_ACTIVE_LOW		BIT(5)
#घोषणा V4L2_MBUS_PCLK_SAMPLE_RISING		BIT(6)
#घोषणा V4L2_MBUS_PCLK_SAMPLE_FALLING		BIT(7)
#घोषणा V4L2_MBUS_DATA_ACTIVE_HIGH		BIT(8)
#घोषणा V4L2_MBUS_DATA_ACTIVE_LOW		BIT(9)
/* FIELD = 0/1 - Field1 (odd)/Field2 (even) */
#घोषणा V4L2_MBUS_FIELD_EVEN_HIGH		BIT(10)
/* FIELD = 1/0 - Field1 (odd)/Field2 (even) */
#घोषणा V4L2_MBUS_FIELD_EVEN_LOW		BIT(11)
/* Active state of Sync-on-green (SoG) संकेत, 0/1 क्रम LOW/HIGH respectively. */
#घोषणा V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH		BIT(12)
#घोषणा V4L2_MBUS_VIDEO_SOG_ACTIVE_LOW		BIT(13)
#घोषणा V4L2_MBUS_DATA_ENABLE_HIGH		BIT(14)
#घोषणा V4L2_MBUS_DATA_ENABLE_LOW		BIT(15)

/* Serial flags */
/* CSI-2 D-PHY number of data lanes. */
#घोषणा V4L2_MBUS_CSI2_1_LANE			BIT(0)
#घोषणा V4L2_MBUS_CSI2_2_LANE			BIT(1)
#घोषणा V4L2_MBUS_CSI2_3_LANE			BIT(2)
#घोषणा V4L2_MBUS_CSI2_4_LANE			BIT(3)
/* CSI-2 Virtual Channel identअगरiers. */
#घोषणा V4L2_MBUS_CSI2_CHANNEL_0		BIT(4)
#घोषणा V4L2_MBUS_CSI2_CHANNEL_1		BIT(5)
#घोषणा V4L2_MBUS_CSI2_CHANNEL_2		BIT(6)
#घोषणा V4L2_MBUS_CSI2_CHANNEL_3		BIT(7)
/* Clock non-continuous mode support. */
#घोषणा V4L2_MBUS_CSI2_CONTINUOUS_CLOCK		BIT(8)
#घोषणा V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK	BIT(9)

#घोषणा V4L2_MBUS_CSI2_LANES		(V4L2_MBUS_CSI2_1_LANE | \
					 V4L2_MBUS_CSI2_2_LANE | \
					 V4L2_MBUS_CSI2_3_LANE | \
					 V4L2_MBUS_CSI2_4_LANE)
#घोषणा V4L2_MBUS_CSI2_CHANNELS		(V4L2_MBUS_CSI2_CHANNEL_0 | \
					 V4L2_MBUS_CSI2_CHANNEL_1 | \
					 V4L2_MBUS_CSI2_CHANNEL_2 | \
					 V4L2_MBUS_CSI2_CHANNEL_3)

/**
 * क्रमागत v4l2_mbus_type - media bus type
 * @V4L2_MBUS_UNKNOWN:	unknown bus type, no V4L2 mediabus configuration
 * @V4L2_MBUS_PARALLEL:	parallel पूर्णांकerface with hsync and vsync
 * @V4L2_MBUS_BT656:	parallel पूर्णांकerface with embedded synchronisation, can
 *			also be used क्रम BT.1120
 * @V4L2_MBUS_CSI1:	MIPI CSI-1 serial पूर्णांकerface
 * @V4L2_MBUS_CCP2:	CCP2 (Compact Camera Port 2)
 * @V4L2_MBUS_CSI2_DPHY: MIPI CSI-2 serial पूर्णांकerface, with D-PHY
 * @V4L2_MBUS_CSI2_CPHY: MIPI CSI-2 serial पूर्णांकerface, with C-PHY
 * @V4L2_MBUS_INVALID:	invalid bus type (keep as last)
 */
क्रमागत v4l2_mbus_type अणु
	V4L2_MBUS_UNKNOWN,
	V4L2_MBUS_PARALLEL,
	V4L2_MBUS_BT656,
	V4L2_MBUS_CSI1,
	V4L2_MBUS_CCP2,
	V4L2_MBUS_CSI2_DPHY,
	V4L2_MBUS_CSI2_CPHY,
	V4L2_MBUS_INVALID,
पूर्ण;

/**
 * काष्ठा v4l2_mbus_config - media bus configuration
 * @type:	in: पूर्णांकerface type
 * @flags:	in / out: configuration flags, depending on @type
 */
काष्ठा v4l2_mbus_config अणु
	क्रमागत v4l2_mbus_type type;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * v4l2_fill_pix_क्रमmat - Ancillary routine that fills a &काष्ठा
 *	v4l2_pix_क्रमmat fields from a &काष्ठा v4l2_mbus_framefmt.
 *
 * @pix_fmt:	poपूर्णांकer to &काष्ठा v4l2_pix_क्रमmat to be filled
 * @mbus_fmt:	poपूर्णांकer to &काष्ठा v4l2_mbus_framefmt to be used as model
 */
अटल अंतरभूत व्योम
v4l2_fill_pix_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix_fmt,
		     स्थिर काष्ठा v4l2_mbus_framefmt *mbus_fmt)
अणु
	pix_fmt->width = mbus_fmt->width;
	pix_fmt->height = mbus_fmt->height;
	pix_fmt->field = mbus_fmt->field;
	pix_fmt->colorspace = mbus_fmt->colorspace;
	pix_fmt->ycbcr_enc = mbus_fmt->ycbcr_enc;
	pix_fmt->quantization = mbus_fmt->quantization;
	pix_fmt->xfer_func = mbus_fmt->xfer_func;
पूर्ण

/**
 * v4l2_fill_mbus_क्रमmat - Ancillary routine that fills a &काष्ठा
 *	v4l2_mbus_framefmt from a &काष्ठा v4l2_pix_क्रमmat and a
 *	data क्रमmat code.
 *
 * @mbus_fmt:	poपूर्णांकer to &काष्ठा v4l2_mbus_framefmt to be filled
 * @pix_fmt:	poपूर्णांकer to &काष्ठा v4l2_pix_क्रमmat to be used as model
 * @code:	data क्रमmat code (from &क्रमागत v4l2_mbus_pixelcode)
 */
अटल अंतरभूत व्योम v4l2_fill_mbus_क्रमmat(काष्ठा v4l2_mbus_framefmt *mbus_fmt,
					 स्थिर काष्ठा v4l2_pix_क्रमmat *pix_fmt,
			   u32 code)
अणु
	mbus_fmt->width = pix_fmt->width;
	mbus_fmt->height = pix_fmt->height;
	mbus_fmt->field = pix_fmt->field;
	mbus_fmt->colorspace = pix_fmt->colorspace;
	mbus_fmt->ycbcr_enc = pix_fmt->ycbcr_enc;
	mbus_fmt->quantization = pix_fmt->quantization;
	mbus_fmt->xfer_func = pix_fmt->xfer_func;
	mbus_fmt->code = code;
पूर्ण

/**
 * v4l2_fill_pix_क्रमmat_mplane - Ancillary routine that fills a &काष्ठा
 *	v4l2_pix_क्रमmat_mplane fields from a media bus काष्ठाure.
 *
 * @pix_mp_fmt:	poपूर्णांकer to &काष्ठा v4l2_pix_क्रमmat_mplane to be filled
 * @mbus_fmt:	poपूर्णांकer to &काष्ठा v4l2_mbus_framefmt to be used as model
 */
अटल अंतरभूत व्योम
v4l2_fill_pix_क्रमmat_mplane(काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp_fmt,
			    स्थिर काष्ठा v4l2_mbus_framefmt *mbus_fmt)
अणु
	pix_mp_fmt->width = mbus_fmt->width;
	pix_mp_fmt->height = mbus_fmt->height;
	pix_mp_fmt->field = mbus_fmt->field;
	pix_mp_fmt->colorspace = mbus_fmt->colorspace;
	pix_mp_fmt->ycbcr_enc = mbus_fmt->ycbcr_enc;
	pix_mp_fmt->quantization = mbus_fmt->quantization;
	pix_mp_fmt->xfer_func = mbus_fmt->xfer_func;
पूर्ण

/**
 * v4l2_fill_mbus_क्रमmat_mplane - Ancillary routine that fills a &काष्ठा
 *	v4l2_mbus_framefmt from a &काष्ठा v4l2_pix_क्रमmat_mplane.
 *
 * @mbus_fmt:	poपूर्णांकer to &काष्ठा v4l2_mbus_framefmt to be filled
 * @pix_mp_fmt:	poपूर्णांकer to &काष्ठा v4l2_pix_क्रमmat_mplane to be used as model
 */
अटल अंतरभूत व्योम
v4l2_fill_mbus_क्रमmat_mplane(काष्ठा v4l2_mbus_framefmt *mbus_fmt,
			     स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp_fmt)
अणु
	mbus_fmt->width = pix_mp_fmt->width;
	mbus_fmt->height = pix_mp_fmt->height;
	mbus_fmt->field = pix_mp_fmt->field;
	mbus_fmt->colorspace = pix_mp_fmt->colorspace;
	mbus_fmt->ycbcr_enc = pix_mp_fmt->ycbcr_enc;
	mbus_fmt->quantization = pix_mp_fmt->quantization;
	mbus_fmt->xfer_func = pix_mp_fmt->xfer_func;
पूर्ण

#पूर्ण_अगर
