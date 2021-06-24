<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "solo6x10.h"
#समावेश "solo6x10-tw28.h"
#समावेश "solo6x10-jpeg.h"

#घोषणा MIN_VID_BUFFERS		2
#घोषणा FRAME_BUF_SIZE		(400 * 1024)
#घोषणा MP4_QS			16
#घोषणा DMA_ALIGN		4096

/* 6010 M4V */
अटल u8 vop_6010_ntsc_d1[] = अणु
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x1d, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x58, 0x10, 0xf0, 0x71, 0x18, 0x3f,
पूर्ण;

अटल u8 vop_6010_ntsc_cअगर[] = अणु
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x1d, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x2c, 0x10, 0x78, 0x51, 0x18, 0x3f,
पूर्ण;

अटल u8 vop_6010_pal_d1[] = अणु
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x15, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x58, 0x11, 0x20, 0x71, 0x18, 0x3f,
पूर्ण;

अटल u8 vop_6010_pal_cअगर[] = अणु
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x15, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x2c, 0x10, 0x90, 0x51, 0x18, 0x3f,
पूर्ण;

/* 6110 h.264 */
अटल u8 vop_6110_ntsc_d1[] = अणु
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x05, 0x81, 0xec, 0x80, 0x00, 0x00,
	0x00, 0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00,
पूर्ण;

अटल u8 vop_6110_ntsc_cअगर[] = अणु
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x0b, 0x0f, 0xc8, 0x00, 0x00, 0x00,
	0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00, 0x00,
पूर्ण;

अटल u8 vop_6110_pal_d1[] = अणु
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x05, 0x80, 0x93, 0x20, 0x00, 0x00,
	0x00, 0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00,
पूर्ण;

अटल u8 vop_6110_pal_cअगर[] = अणु
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x0b, 0x04, 0xb2, 0x00, 0x00, 0x00,
	0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00, 0x00,
पूर्ण;

प्रकार __le32 vop_header[16];

काष्ठा solo_enc_buf अणु
	क्रमागत solo_enc_types	type;
	स्थिर vop_header	*vh;
	पूर्णांक			motion;
पूर्ण;

अटल पूर्णांक solo_is_motion_on(काष्ठा solo_enc_dev *solo_enc)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	वापस (solo_dev->motion_mask >> solo_enc->ch) & 1;
पूर्ण

अटल पूर्णांक solo_motion_detected(काष्ठा solo_enc_dev *solo_enc)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	अचिन्हित दीर्घ flags;
	u32 ch_mask = 1 << solo_enc->ch;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&solo_enc->motion_lock, flags);
	अगर (solo_reg_पढ़ो(solo_dev, SOLO_VI_MOT_STATUS) & ch_mask) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOT_CLEAR, ch_mask);
		ret = 1;
	पूर्ण
	spin_unlock_irqrestore(&solo_enc->motion_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम solo_motion_toggle(काष्ठा solo_enc_dev *solo_enc, पूर्णांक on)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	u32 mask = 1 << solo_enc->ch;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&solo_enc->motion_lock, flags);

	अगर (on)
		solo_dev->motion_mask |= mask;
	अन्यथा
		solo_dev->motion_mask &= ~mask;

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOT_CLEAR, mask);

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOT_ADR,
		       SOLO_VI_MOTION_EN(solo_dev->motion_mask) |
		       (SOLO_MOTION_EXT_ADDR(solo_dev) >> 16));

	spin_unlock_irqrestore(&solo_enc->motion_lock, flags);
पूर्ण

व्योम solo_update_mode(काष्ठा solo_enc_dev *solo_enc)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	पूर्णांक vop_len;
	u8 *vop;

	solo_enc->पूर्णांकerlaced = (solo_enc->mode & 0x08) ? 1 : 0;
	solo_enc->bw_weight = max(solo_dev->fps / solo_enc->पूर्णांकerval, 1);

	अगर (solo_enc->mode == SOLO_ENC_MODE_CIF) अणु
		solo_enc->width = solo_dev->video_hsize >> 1;
		solo_enc->height = solo_dev->video_vsize;
		अगर (solo_dev->type == SOLO_DEV_6110) अणु
			अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
				vop = vop_6110_ntsc_cअगर;
				vop_len = माप(vop_6110_ntsc_cअगर);
			पूर्ण अन्यथा अणु
				vop = vop_6110_pal_cअगर;
				vop_len = माप(vop_6110_pal_cअगर);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
				vop = vop_6010_ntsc_cअगर;
				vop_len = माप(vop_6010_ntsc_cअगर);
			पूर्ण अन्यथा अणु
				vop = vop_6010_pal_cअगर;
				vop_len = माप(vop_6010_pal_cअगर);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		solo_enc->width = solo_dev->video_hsize;
		solo_enc->height = solo_dev->video_vsize << 1;
		solo_enc->bw_weight <<= 2;
		अगर (solo_dev->type == SOLO_DEV_6110) अणु
			अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
				vop = vop_6110_ntsc_d1;
				vop_len = माप(vop_6110_ntsc_d1);
			पूर्ण अन्यथा अणु
				vop = vop_6110_pal_d1;
				vop_len = माप(vop_6110_pal_d1);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
				vop = vop_6010_ntsc_d1;
				vop_len = माप(vop_6010_ntsc_d1);
			पूर्ण अन्यथा अणु
				vop = vop_6010_pal_d1;
				vop_len = माप(vop_6010_pal_d1);
			पूर्ण
		पूर्ण
	पूर्ण

	स_नकल(solo_enc->vop, vop, vop_len);

	/* Some fixups क्रम 6010/M4V */
	अगर (solo_dev->type == SOLO_DEV_6010) अणु
		u16 fps = solo_dev->fps * 1000;
		u16 पूर्णांकerval = solo_enc->पूर्णांकerval * 1000;

		vop = solo_enc->vop;

		/* Frame rate and पूर्णांकerval */
		vop[22] = fps >> 4;
		vop[23] = ((fps << 4) & 0xf0) | 0x0c
			| ((पूर्णांकerval >> 13) & 0x3);
		vop[24] = (पूर्णांकerval >> 5) & 0xff;
		vop[25] = ((पूर्णांकerval << 3) & 0xf8) | 0x04;
	पूर्ण

	solo_enc->vop_len = vop_len;

	/* Now handle the jpeg header */
	vop = solo_enc->jpeg_header;
	vop[SOF0_START + 5] = 0xff & (solo_enc->height >> 8);
	vop[SOF0_START + 6] = 0xff & solo_enc->height;
	vop[SOF0_START + 7] = 0xff & (solo_enc->width >> 8);
	vop[SOF0_START + 8] = 0xff & solo_enc->width;

	स_नकल(vop + DQT_START,
	       jpeg_dqt[solo_g_jpeg_qp(solo_dev, solo_enc->ch)], DQT_LEN);
पूर्ण

अटल पूर्णांक solo_enc_on(काष्ठा solo_enc_dev *solo_enc)
अणु
	u8 ch = solo_enc->ch;
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	u8 पूर्णांकerval;

	solo_update_mode(solo_enc);

	/* Make sure to करो a bandwidth check */
	अगर (solo_enc->bw_weight > solo_dev->enc_bw_reमुख्य)
		वापस -EBUSY;
	solo_enc->sequence = 0;
	solo_dev->enc_bw_reमुख्य -= solo_enc->bw_weight;

	अगर (solo_enc->type == SOLO_ENC_TYPE_EXT)
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_COMP_ENA_E(ch), 1);

	/* Disable all encoding क्रम this channel */
	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_SCALE(ch), 0);

	/* Common क्रम both std and ext encoding */
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_INTL(ch),
		       solo_enc->पूर्णांकerlaced ? 1 : 0);

	अगर (solo_enc->पूर्णांकerlaced)
		पूर्णांकerval = solo_enc->पूर्णांकerval - 1;
	अन्यथा
		पूर्णांकerval = solo_enc->पूर्णांकerval;

	/* Standard encoding only */
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_GOP(ch), solo_enc->gop);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_QP(ch), solo_enc->qp);
	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_INTV(ch), पूर्णांकerval);

	/* Extended encoding only */
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_GOP_E(ch), solo_enc->gop);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_QP_E(ch), solo_enc->qp);
	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_INTV_E(ch), पूर्णांकerval);

	/* Enables the standard encoder */
	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_SCALE(ch), solo_enc->mode);

	वापस 0;
पूर्ण

अटल व्योम solo_enc_off(काष्ठा solo_enc_dev *solo_enc)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	solo_dev->enc_bw_reमुख्य += solo_enc->bw_weight;

	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_SCALE(solo_enc->ch), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_COMP_ENA_E(solo_enc->ch), 0);
पूर्ण

अटल पूर्णांक enc_get_mpeg_dma(काष्ठा solo_dev *solo_dev, dma_addr_t dma,
			      अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	अगर (off > SOLO_MP4E_EXT_SIZE(solo_dev))
		वापस -EINVAL;

	/* Single shot */
	अगर (off + size <= SOLO_MP4E_EXT_SIZE(solo_dev)) अणु
		वापस solo_p2m_dma_t(solo_dev, 0, dma,
				      SOLO_MP4E_EXT_ADDR(solo_dev) + off, size,
				      0, 0);
	पूर्ण

	/* Buffer wrap */
	ret = solo_p2m_dma_t(solo_dev, 0, dma,
			     SOLO_MP4E_EXT_ADDR(solo_dev) + off,
			     SOLO_MP4E_EXT_SIZE(solo_dev) - off, 0, 0);

	अगर (!ret) अणु
		ret = solo_p2m_dma_t(solo_dev, 0,
			     dma + SOLO_MP4E_EXT_SIZE(solo_dev) - off,
			     SOLO_MP4E_EXT_ADDR(solo_dev),
			     size + off - SOLO_MP4E_EXT_SIZE(solo_dev), 0, 0);
	पूर्ण

	वापस ret;
पूर्ण

/* Build a descriptor queue out of an SG list and send it to the P2M क्रम
 * processing. */
अटल पूर्णांक solo_send_desc(काष्ठा solo_enc_dev *solo_enc, पूर्णांक skip,
			  काष्ठा sg_table *vbuf, पूर्णांक off, पूर्णांक size,
			  अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक base_size)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(size > FRAME_BUF_SIZE))
		वापस -EINVAL;

	solo_enc->desc_count = 1;

	क्रम_each_sg(vbuf->sgl, sg, vbuf->nents, i) अणु
		काष्ठा solo_p2m_desc *desc;
		dma_addr_t dma;
		पूर्णांक len;
		पूर्णांक left = base_size - off;

		desc = &solo_enc->desc_items[solo_enc->desc_count++];
		dma = sg_dma_address(sg);
		len = sg_dma_len(sg);

		/* We assume this is smaller than the scatter size */
		BUG_ON(skip >= len);
		अगर (skip) अणु
			len -= skip;
			dma += skip;
			size -= skip;
			skip = 0;
		पूर्ण

		len = min(len, size);

		अगर (len <= left) अणु
			/* Single descriptor */
			solo_p2m_fill_desc(desc, 0, dma, base + off,
					   len, 0, 0);
		पूर्ण अन्यथा अणु
			/* Buffer wrap */
			/* XXX: Do these as separate DMA requests, to aव्योम
			   समयout errors triggered by awkwardly sized
			   descriptors. See
			   <https://github.com/bluecherrydvr/solo6x10/issues/8>
			 */
			ret = solo_p2m_dma_t(solo_dev, 0, dma, base + off,
					     left, 0, 0);
			अगर (ret)
				वापस ret;

			ret = solo_p2m_dma_t(solo_dev, 0, dma + left, base,
					     len - left, 0, 0);
			अगर (ret)
				वापस ret;

			solo_enc->desc_count--;
		पूर्ण

		size -= len;
		अगर (size <= 0)
			अवरोध;

		off += len;
		अगर (off >= base_size)
			off -= base_size;

		/* Because we may use two descriptors per loop */
		अगर (solo_enc->desc_count >= (solo_enc->desc_nelts - 1)) अणु
			ret = solo_p2m_dma_desc(solo_dev, solo_enc->desc_items,
						solo_enc->desc_dma,
						solo_enc->desc_count - 1);
			अगर (ret)
				वापस ret;
			solo_enc->desc_count = 1;
		पूर्ण
	पूर्ण

	अगर (solo_enc->desc_count <= 1)
		वापस 0;

	वापस solo_p2m_dma_desc(solo_dev, solo_enc->desc_items,
			solo_enc->desc_dma, solo_enc->desc_count - 1);
पूर्ण

/* Extract values from VOP header - VE_STATUSxx */
अटल अंतरभूत पूर्णांक vop_पूर्णांकerlaced(स्थिर vop_header *vh)
अणु
	वापस (__le32_to_cpu((*vh)[0]) >> 30) & 1;
पूर्ण

अटल अंतरभूत u8 vop_channel(स्थिर vop_header *vh)
अणु
	वापस (__le32_to_cpu((*vh)[0]) >> 24) & 0x1F;
पूर्ण

अटल अंतरभूत u8 vop_type(स्थिर vop_header *vh)
अणु
	वापस (__le32_to_cpu((*vh)[0]) >> 22) & 3;
पूर्ण

अटल अंतरभूत u32 vop_mpeg_size(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[0]) & 0xFFFFF;
पूर्ण

अटल अंतरभूत u8 vop_hsize(स्थिर vop_header *vh)
अणु
	वापस (__le32_to_cpu((*vh)[1]) >> 8) & 0xFF;
पूर्ण

अटल अंतरभूत u8 vop_vsize(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[1]) & 0xFF;
पूर्ण

अटल अंतरभूत u32 vop_mpeg_offset(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[2]);
पूर्ण

अटल अंतरभूत u32 vop_jpeg_offset(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[3]);
पूर्ण

अटल अंतरभूत u32 vop_jpeg_size(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[4]) & 0xFFFFF;
पूर्ण

अटल अंतरभूत u32 vop_sec(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[5]);
पूर्ण

अटल अंतरभूत u32 vop_usec(स्थिर vop_header *vh)
अणु
	वापस __le32_to_cpu((*vh)[6]);
पूर्ण

अटल पूर्णांक solo_fill_jpeg(काष्ठा solo_enc_dev *solo_enc,
			  काष्ठा vb2_buffer *vb, स्थिर vop_header *vh)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	पूर्णांक frame_size;

	vbuf->flags |= V4L2_BUF_FLAG_KEYFRAME;

	अगर (vb2_plane_size(vb, 0) < vop_jpeg_size(vh) + solo_enc->jpeg_len)
		वापस -EIO;

	frame_size = ALIGN(vop_jpeg_size(vh) + solo_enc->jpeg_len, DMA_ALIGN);
	vb2_set_plane_payload(vb, 0, vop_jpeg_size(vh) + solo_enc->jpeg_len);

	वापस solo_send_desc(solo_enc, solo_enc->jpeg_len, sgt,
			     vop_jpeg_offset(vh) - SOLO_JPEG_EXT_ADDR(solo_dev),
			     frame_size, SOLO_JPEG_EXT_ADDR(solo_dev),
			     SOLO_JPEG_EXT_SIZE(solo_dev));
पूर्ण

अटल पूर्णांक solo_fill_mpeg(काष्ठा solo_enc_dev *solo_enc,
		काष्ठा vb2_buffer *vb, स्थिर vop_header *vh)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	पूर्णांक frame_off, frame_size;
	पूर्णांक skip = 0;

	अगर (vb2_plane_size(vb, 0) < vop_mpeg_size(vh))
		वापस -EIO;

	/* If this is a key frame, add extra header */
	vbuf->flags &= ~(V4L2_BUF_FLAG_KEYFRAME | V4L2_BUF_FLAG_PFRAME |
		V4L2_BUF_FLAG_BFRAME);
	अगर (!vop_type(vh)) अणु
		skip = solo_enc->vop_len;
		vbuf->flags |= V4L2_BUF_FLAG_KEYFRAME;
		vb2_set_plane_payload(vb, 0, vop_mpeg_size(vh) +
			solo_enc->vop_len);
	पूर्ण अन्यथा अणु
		vbuf->flags |= V4L2_BUF_FLAG_PFRAME;
		vb2_set_plane_payload(vb, 0, vop_mpeg_size(vh));
	पूर्ण

	/* Now get the actual mpeg payload */
	frame_off = (vop_mpeg_offset(vh) - SOLO_MP4E_EXT_ADDR(solo_dev) +
		माप(*vh)) % SOLO_MP4E_EXT_SIZE(solo_dev);
	frame_size = ALIGN(vop_mpeg_size(vh) + skip, DMA_ALIGN);

	वापस solo_send_desc(solo_enc, skip, sgt, frame_off, frame_size,
			SOLO_MP4E_EXT_ADDR(solo_dev),
			SOLO_MP4E_EXT_SIZE(solo_dev));
पूर्ण

अटल पूर्णांक solo_enc_fillbuf(काष्ठा solo_enc_dev *solo_enc,
			    काष्ठा vb2_buffer *vb, काष्ठा solo_enc_buf *enc_buf)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	स्थिर vop_header *vh = enc_buf->vh;
	पूर्णांक ret;

	चयन (solo_enc->fmt) अणु
	हाल V4L2_PIX_FMT_MPEG4:
	हाल V4L2_PIX_FMT_H264:
		ret = solo_fill_mpeg(solo_enc, vb, vh);
		अवरोध;
	शेष: /* V4L2_PIX_FMT_MJPEG */
		ret = solo_fill_jpeg(solo_enc, vb, vh);
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		vbuf->sequence = solo_enc->sequence++;
		vb->बारtamp = kसमय_get_ns();

		/* Check क्रम motion flags */
		अगर (solo_is_motion_on(solo_enc) && enc_buf->motion) अणु
			काष्ठा v4l2_event ev = अणु
				.type = V4L2_EVENT_MOTION_DET,
				.u.motion_det = अणु
					.flags
					= V4L2_EVENT_MD_FL_HAVE_FRAME_SEQ,
					.frame_sequence = vbuf->sequence,
					.region_mask = enc_buf->motion ? 1 : 0,
				पूर्ण,
			पूर्ण;

			v4l2_event_queue(solo_enc->vfd, &ev);
		पूर्ण
	पूर्ण

	vb2_buffer_करोne(vb, ret ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);

	वापस ret;
पूर्ण

अटल व्योम solo_enc_handle_one(काष्ठा solo_enc_dev *solo_enc,
				काष्ठा solo_enc_buf *enc_buf)
अणु
	काष्ठा solo_vb2_buf *vb;
	अचिन्हित दीर्घ flags;

	mutex_lock(&solo_enc->lock);
	अगर (solo_enc->type != enc_buf->type)
		जाओ unlock;

	spin_lock_irqsave(&solo_enc->av_lock, flags);
	अगर (list_empty(&solo_enc->vidq_active)) अणु
		spin_unlock_irqrestore(&solo_enc->av_lock, flags);
		जाओ unlock;
	पूर्ण
	vb = list_first_entry(&solo_enc->vidq_active, काष्ठा solo_vb2_buf,
		list);
	list_del(&vb->list);
	spin_unlock_irqrestore(&solo_enc->av_lock, flags);

	solo_enc_fillbuf(solo_enc, &vb->vb.vb2_buf, enc_buf);
unlock:
	mutex_unlock(&solo_enc->lock);
पूर्ण

व्योम solo_enc_v4l2_isr(काष्ठा solo_dev *solo_dev)
अणु
	wake_up_पूर्णांकerruptible_all(&solo_dev->ring_thपढ़ो_रुको);
पूर्ण

अटल व्योम solo_handle_ring(काष्ठा solo_dev *solo_dev)
अणु
	क्रम (;;) अणु
		काष्ठा solo_enc_dev *solo_enc;
		काष्ठा solo_enc_buf enc_buf;
		u32 mpeg_current, off;
		u8 ch;
		u8 cur_q;

		/* Check अगर the hardware has any new ones in the queue */
		cur_q = solo_reg_पढ़ो(solo_dev, SOLO_VE_STATE(11)) & 0xff;
		अगर (cur_q == solo_dev->enc_idx)
			अवरोध;

		mpeg_current = solo_reg_पढ़ो(solo_dev,
					SOLO_VE_MPEG4_QUE(solo_dev->enc_idx));
		solo_dev->enc_idx = (solo_dev->enc_idx + 1) % MP4_QS;

		ch = (mpeg_current >> 24) & 0x1f;
		off = mpeg_current & 0x00ffffff;

		अगर (ch >= SOLO_MAX_CHANNELS) अणु
			ch -= SOLO_MAX_CHANNELS;
			enc_buf.type = SOLO_ENC_TYPE_EXT;
		पूर्ण अन्यथा
			enc_buf.type = SOLO_ENC_TYPE_STD;

		solo_enc = solo_dev->v4l2_enc[ch];
		अगर (solo_enc == शून्य) अणु
			dev_err(&solo_dev->pdev->dev,
				"Got spurious packet for channel %d\n", ch);
			जारी;
		पूर्ण

		/* FAIL... */
		अगर (enc_get_mpeg_dma(solo_dev, solo_dev->vh_dma, off,
				     माप(vop_header)))
			जारी;

		enc_buf.vh = solo_dev->vh_buf;

		/* Sanity check */
		अगर (vop_mpeg_offset(enc_buf.vh) !=
			SOLO_MP4E_EXT_ADDR(solo_dev) + off)
			जारी;

		अगर (solo_motion_detected(solo_enc))
			enc_buf.motion = 1;
		अन्यथा
			enc_buf.motion = 0;

		solo_enc_handle_one(solo_enc, &enc_buf);
	पूर्ण
पूर्ण

अटल पूर्णांक solo_ring_thपढ़ो(व्योम *data)
अणु
	काष्ठा solo_dev *solo_dev = data;
	DECLARE_WAITQUEUE(रुको, current);

	set_मुक्तzable();
	add_रुको_queue(&solo_dev->ring_thपढ़ो_रुको, &रुको);

	क्रम (;;) अणु
		दीर्घ समयout = schedule_समयout_पूर्णांकerruptible(HZ);

		अगर (समयout == -ERESTARTSYS || kthपढ़ो_should_stop())
			अवरोध;
		solo_handle_ring(solo_dev);
		try_to_मुक्तze();
	पूर्ण

	हटाओ_रुको_queue(&solo_dev->ring_thपढ़ो_रुको, &रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_queue_setup(काष्ठा vb2_queue *q,
				अचिन्हित पूर्णांक *num_buffers,
				अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	sizes[0] = FRAME_BUF_SIZE;
	*num_planes = 1;

	अगर (*num_buffers < MIN_VID_BUFFERS)
		*num_buffers = MIN_VID_BUFFERS;

	वापस 0;
पूर्ण

अटल व्योम solo_enc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा solo_enc_dev *solo_enc = vb2_get_drv_priv(vq);
	काष्ठा solo_vb2_buf *solo_vb =
		container_of(vbuf, काष्ठा solo_vb2_buf, vb);

	spin_lock(&solo_enc->av_lock);
	list_add_tail(&solo_vb->list, &solo_enc->vidq_active);
	spin_unlock(&solo_enc->av_lock);
पूर्ण

अटल पूर्णांक solo_ring_start(काष्ठा solo_dev *solo_dev)
अणु
	solo_dev->ring_thपढ़ो = kthपढ़ो_run(solo_ring_thपढ़ो, solo_dev,
					    SOLO6X10_NAME "_ring");
	अगर (IS_ERR(solo_dev->ring_thपढ़ो)) अणु
		पूर्णांक err = PTR_ERR(solo_dev->ring_thपढ़ो);

		solo_dev->ring_thपढ़ो = शून्य;
		वापस err;
	पूर्ण

	solo_irq_on(solo_dev, SOLO_IRQ_ENCODER);

	वापस 0;
पूर्ण

अटल व्योम solo_ring_stop(काष्ठा solo_dev *solo_dev)
अणु
	अगर (solo_dev->ring_thपढ़ो) अणु
		kthपढ़ो_stop(solo_dev->ring_thपढ़ो);
		solo_dev->ring_thपढ़ो = शून्य;
	पूर्ण

	solo_irq_off(solo_dev, SOLO_IRQ_ENCODER);
पूर्ण

अटल पूर्णांक solo_enc_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा solo_enc_dev *solo_enc = vb2_get_drv_priv(q);

	वापस solo_enc_on(solo_enc);
पूर्ण

अटल व्योम solo_enc_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा solo_enc_dev *solo_enc = vb2_get_drv_priv(q);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&solo_enc->av_lock, flags);
	solo_enc_off(solo_enc);
	जबतक (!list_empty(&solo_enc->vidq_active)) अणु
		काष्ठा solo_vb2_buf *buf = list_entry(
				solo_enc->vidq_active.next,
				काष्ठा solo_vb2_buf, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&solo_enc->av_lock, flags);
पूर्ण

अटल व्योम solo_enc_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा solo_enc_dev *solo_enc = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);

	चयन (solo_enc->fmt) अणु
	हाल V4L2_PIX_FMT_MPEG4:
	हाल V4L2_PIX_FMT_H264:
		अगर (vbuf->flags & V4L2_BUF_FLAG_KEYFRAME)
			sg_copy_from_buffer(sgt->sgl, sgt->nents,
					solo_enc->vop, solo_enc->vop_len);
		अवरोध;
	शेष: /* V4L2_PIX_FMT_MJPEG */
		sg_copy_from_buffer(sgt->sgl, sgt->nents,
				solo_enc->jpeg_header, solo_enc->jpeg_len);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops solo_enc_video_qops = अणु
	.queue_setup	= solo_enc_queue_setup,
	.buf_queue	= solo_enc_buf_queue,
	.buf_finish	= solo_enc_buf_finish,
	.start_streaming = solo_enc_start_streaming,
	.stop_streaming = solo_enc_stop_streaming,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक solo_enc_querycap(काष्ठा file *file, व्योम  *priv,
			     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	strscpy(cap->driver, SOLO6X10_NAME, माप(cap->driver));
	snम_लिखो(cap->card, माप(cap->card), "Softlogic 6x10 Enc %d",
		 solo_enc->ch);
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s",
		 pci_name(solo_dev->pdev));
	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_input *input)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	अगर (input->index)
		वापस -EINVAL;

	snम_लिखो(input->name, माप(input->name), "Encoder %d",
		 solo_enc->ch + 1);
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = solo_enc->vfd->tvnorms;

	अगर (!tw28_get_video_status(solo_dev, solo_enc->ch))
		input->status = V4L2_IN_ST_NO_SIGNAL;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_set_input(काष्ठा file *file, व्योम *priv,
			      अचिन्हित पूर्णांक index)
अणु
	अगर (index)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_get_input(काष्ठा file *file, व्योम *priv,
			      अचिन्हित पूर्णांक *index)
अणु
	*index = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_क्रमागत_fmt_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	पूर्णांक dev_type = solo_enc->solo_dev->type;

	चयन (f->index) अणु
	हाल 0:
		चयन (dev_type) अणु
		हाल SOLO_DEV_6010:
			f->pixelक्रमmat = V4L2_PIX_FMT_MPEG4;
			अवरोध;
		हाल SOLO_DEV_6110:
			f->pixelक्रमmat = V4L2_PIX_FMT_H264;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		f->pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक solo_valid_pixfmt(u32 pixfmt, पूर्णांक dev_type)
अणु
	वापस (pixfmt == V4L2_PIX_FMT_H264 && dev_type == SOLO_DEV_6110)
		|| (pixfmt == V4L2_PIX_FMT_MPEG4 && dev_type == SOLO_DEV_6010)
		|| pixfmt == V4L2_PIX_FMT_MJPEG ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक solo_enc_try_fmt_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	अगर (solo_valid_pixfmt(pix->pixelक्रमmat, solo_dev->type))
		वापस -EINVAL;

	अगर (pix->width < solo_dev->video_hsize ||
	    pix->height < solo_dev->video_vsize << 1) अणु
		/* Default to CIF 1/2 size */
		pix->width = solo_dev->video_hsize >> 1;
		pix->height = solo_dev->video_vsize;
	पूर्ण अन्यथा अणु
		/* Full frame */
		pix->width = solo_dev->video_hsize;
		pix->height = solo_dev->video_vsize << 1;
	पूर्ण

	चयन (pix->field) अणु
	हाल V4L2_FIELD_NONE:
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	हाल V4L2_FIELD_ANY:
	शेष:
		pix->field = V4L2_FIELD_INTERLACED;
		अवरोध;
	पूर्ण

	/* Just set these */
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->sizeimage = FRAME_BUF_SIZE;
	pix->bytesperline = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_set_fmt_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	पूर्णांक ret;

	अगर (vb2_is_busy(&solo_enc->vidq))
		वापस -EBUSY;

	ret = solo_enc_try_fmt_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	अगर (pix->width == solo_dev->video_hsize)
		solo_enc->mode = SOLO_ENC_MODE_D1;
	अन्यथा
		solo_enc->mode = SOLO_ENC_MODE_CIF;

	/* This करोes not change the encoder at all */
	solo_enc->fmt = pix->pixelक्रमmat;

	/*
	 * More inक्रमmation is needed about these 'extended' types. As far
	 * as I can tell these are basically additional video streams with
	 * dअगरferent MPEG encoding attributes that can run in parallel with
	 * the मुख्य stream. If so, then this should be implemented as a
	 * second video node. Abusing priv like this is certainly not the
	 * right approach.
	अगर (pix->priv)
		solo_enc->type = SOLO_ENC_TYPE_EXT;
	 */
	solo_update_mode(solo_enc);
	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_get_fmt_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	pix->width = solo_enc->width;
	pix->height = solo_enc->height;
	pix->pixelक्रमmat = solo_enc->fmt;
	pix->field = solo_enc->पूर्णांकerlaced ? V4L2_FIELD_INTERLACED :
		     V4L2_FIELD_NONE;
	pix->sizeimage = FRAME_BUF_SIZE;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *i)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC)
		*i = V4L2_STD_NTSC_M;
	अन्यथा
		*i = V4L2_STD_PAL;
	वापस 0;
पूर्ण

अटल पूर्णांक solo_enc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);

	वापस solo_set_video_type(solo_enc->solo_dev, std & V4L2_STD_625_50);
पूर्ण

अटल पूर्णांक solo_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	अगर (solo_valid_pixfmt(fsize->pixel_क्रमmat, solo_dev->type))
		वापस -EINVAL;

	चयन (fsize->index) अणु
	हाल 0:
		fsize->discrete.width = solo_dev->video_hsize >> 1;
		fsize->discrete.height = solo_dev->video_vsize;
		अवरोध;
	हाल 1:
		fsize->discrete.width = solo_dev->video_hsize;
		fsize->discrete.height = solo_dev->video_vsize << 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_frmivalक्रमागत *fपूर्णांकv)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;

	अगर (solo_valid_pixfmt(fपूर्णांकv->pixel_क्रमmat, solo_dev->type))
		वापस -EINVAL;
	अगर (fपूर्णांकv->index)
		वापस -EINVAL;
	अगर ((fपूर्णांकv->width != solo_dev->video_hsize >> 1 ||
	     fपूर्णांकv->height != solo_dev->video_vsize) &&
	    (fपूर्णांकv->width != solo_dev->video_hsize ||
	     fपूर्णांकv->height != solo_dev->video_vsize << 1))
		वापस -EINVAL;

	fपूर्णांकv->type = V4L2_FRMIVAL_TYPE_STEPWISE;

	fपूर्णांकv->stepwise.min.numerator = 1;
	fपूर्णांकv->stepwise.min.denominator = solo_dev->fps;

	fपूर्णांकv->stepwise.max.numerator = 15;
	fपूर्णांकv->stepwise.max.denominator = solo_dev->fps;

	fपूर्णांकv->stepwise.step.numerator = 1;
	fपूर्णांकv->stepwise.step.denominator = solo_dev->fps;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_g_parm(काष्ठा file *file, व्योम *priv,
		       काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा v4l2_captureparm *cp = &sp->parm.capture;

	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->समयperframe.numerator = solo_enc->पूर्णांकerval;
	cp->समयperframe.denominator = solo_enc->solo_dev->fps;
	cp->capturemode = 0;
	/* XXX: Shouldn't we be able to get/set this from videobuf? */
	cp->पढ़ोbuffers = 2;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक calc_पूर्णांकerval(u8 fps, u32 n, u32 d)
अणु
	अगर (!n || !d)
		वापस 1;
	अगर (d == fps)
		वापस n;
	n *= fps;
	वापस min(15U, n / d + (n % d >= (fps >> 1)));
पूर्ण

अटल पूर्णांक solo_s_parm(काष्ठा file *file, व्योम *priv,
		       काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा solo_enc_dev *solo_enc = video_drvdata(file);
	काष्ठा v4l2_fract *t = &sp->parm.capture.समयperframe;
	u8 fps = solo_enc->solo_dev->fps;

	अगर (vb2_is_streaming(&solo_enc->vidq))
		वापस -EBUSY;

	solo_enc->पूर्णांकerval = calc_पूर्णांकerval(fps, t->numerator, t->denominator);
	solo_update_mode(solo_enc);
	वापस solo_g_parm(file, priv, sp);
पूर्ण

अटल पूर्णांक solo_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा solo_enc_dev *solo_enc =
		container_of(ctrl->handler, काष्ठा solo_enc_dev, hdl);
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	पूर्णांक err;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
	हाल V4L2_CID_CONTRAST:
	हाल V4L2_CID_SATURATION:
	हाल V4L2_CID_HUE:
	हाल V4L2_CID_SHARPNESS:
		वापस tw28_set_ctrl_val(solo_dev, ctrl->id, solo_enc->ch,
					 ctrl->val);
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		solo_enc->gop = ctrl->val;
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_GOP(solo_enc->ch), solo_enc->gop);
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_GOP_E(solo_enc->ch), solo_enc->gop);
		वापस 0;
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		solo_enc->qp = ctrl->val;
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_QP(solo_enc->ch), solo_enc->qp);
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_QP_E(solo_enc->ch), solo_enc->qp);
		वापस 0;
	हाल V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD:
		solo_enc->motion_thresh = ctrl->val << 8;
		अगर (!solo_enc->motion_global || !solo_enc->motion_enabled)
			वापस 0;
		वापस solo_set_motion_threshold(solo_dev, solo_enc->ch,
				solo_enc->motion_thresh);
	हाल V4L2_CID_DETECT_MD_MODE:
		solo_enc->motion_global = ctrl->val == V4L2_DETECT_MD_MODE_GLOBAL;
		solo_enc->motion_enabled = ctrl->val > V4L2_DETECT_MD_MODE_DISABLED;
		अगर (ctrl->val) अणु
			अगर (solo_enc->motion_global)
				err = solo_set_motion_threshold(solo_dev, solo_enc->ch,
					solo_enc->motion_thresh);
			अन्यथा
				err = solo_set_motion_block(solo_dev, solo_enc->ch,
					solo_enc->md_thresholds->p_cur.p_u16);
			अगर (err)
				वापस err;
		पूर्ण
		solo_motion_toggle(solo_enc, ctrl->val);
		वापस 0;
	हाल V4L2_CID_DETECT_MD_THRESHOLD_GRID:
		अगर (solo_enc->motion_enabled && !solo_enc->motion_global)
			वापस solo_set_motion_block(solo_dev, solo_enc->ch,
					solo_enc->md_thresholds->p_new.p_u16);
		अवरोध;
	हाल V4L2_CID_OSD_TEXT:
		strscpy(solo_enc->osd_text, ctrl->p_new.p_अक्षर,
			माप(solo_enc->osd_text));
		वापस solo_osd_prपूर्णांक(solo_enc);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक solo_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु

	चयन (sub->type) अणु
	हाल V4L2_EVENT_MOTION_DET:
		/* Allow क्रम up to 30 events (1 second क्रम NTSC) to be
		 * stored. */
		वापस v4l2_event_subscribe(fh, sub, 30, शून्य);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations solo_enc_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= v4l2_fh_खोलो,
	.release		= vb2_fop_release,
	.पढ़ो			= vb2_fop_पढ़ो,
	.poll			= vb2_fop_poll,
	.mmap			= vb2_fop_mmap,
	.unlocked_ioctl		= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops solo_enc_ioctl_ops = अणु
	.vidioc_querycap		= solo_enc_querycap,
	.vidioc_s_std			= solo_enc_s_std,
	.vidioc_g_std			= solo_enc_g_std,
	/* Input callbacks */
	.vidioc_क्रमागत_input		= solo_enc_क्रमागत_input,
	.vidioc_s_input			= solo_enc_set_input,
	.vidioc_g_input			= solo_enc_get_input,
	/* Video capture क्रमmat callbacks */
	.vidioc_क्रमागत_fmt_vid_cap	= solo_enc_क्रमागत_fmt_cap,
	.vidioc_try_fmt_vid_cap		= solo_enc_try_fmt_cap,
	.vidioc_s_fmt_vid_cap		= solo_enc_set_fmt_cap,
	.vidioc_g_fmt_vid_cap		= solo_enc_get_fmt_cap,
	/* Streaming I/O */
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	/* Frame size and पूर्णांकerval */
	.vidioc_क्रमागत_framesizes		= solo_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= solo_क्रमागत_frameपूर्णांकervals,
	/* Video capture parameters */
	.vidioc_s_parm			= solo_s_parm,
	.vidioc_g_parm			= solo_g_parm,
	/* Logging and events */
	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= solo_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device solo_enc_ढाँचा = अणु
	.name			= SOLO6X10_NAME,
	.fops			= &solo_enc_fops,
	.ioctl_ops		= &solo_enc_ioctl_ops,
	.minor			= -1,
	.release		= video_device_release,
	.tvnorms		= V4L2_STD_NTSC_M | V4L2_STD_PAL,
	.device_caps		= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				  V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops solo_ctrl_ops = अणु
	.s_ctrl = solo_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config solo_osd_text_ctrl = अणु
	.ops = &solo_ctrl_ops,
	.id = V4L2_CID_OSD_TEXT,
	.name = "OSD Text",
	.type = V4L2_CTRL_TYPE_STRING,
	.max = OSD_TEXT_MAX,
	.step = 1,
पूर्ण;

/* Motion Detection Threshold matrix */
अटल स्थिर काष्ठा v4l2_ctrl_config solo_md_thresholds = अणु
	.ops = &solo_ctrl_ops,
	.id = V4L2_CID_DETECT_MD_THRESHOLD_GRID,
	.dims = अणु SOLO_MOTION_SZ, SOLO_MOTION_SZ पूर्ण,
	.def = SOLO_DEF_MOT_THRESH,
	.max = 65535,
	.step = 1,
पूर्ण;

अटल काष्ठा solo_enc_dev *solo_enc_alloc(काष्ठा solo_dev *solo_dev,
					   u8 ch, अचिन्हित nr)
अणु
	काष्ठा solo_enc_dev *solo_enc;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक ret;

	solo_enc = kzalloc(माप(*solo_enc), GFP_KERNEL);
	अगर (!solo_enc)
		वापस ERR_PTR(-ENOMEM);

	hdl = &solo_enc->hdl;
	v4l2_ctrl_handler_init(hdl, 10);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_HUE, 0, 255, 1, 128);
	अगर (tw28_has_sharpness(solo_dev, ch))
		v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 15, 1, 0);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_GOP_SIZE, 1, 255, 1, solo_dev->fps);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_MIN_QP, 0, 31, 1, SOLO_DEFAULT_QP);
	v4l2_ctrl_new_std_menu(hdl, &solo_ctrl_ops,
			V4L2_CID_DETECT_MD_MODE,
			V4L2_DETECT_MD_MODE_THRESHOLD_GRID, 0,
			V4L2_DETECT_MD_MODE_DISABLED);
	v4l2_ctrl_new_std(hdl, &solo_ctrl_ops,
			V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD, 0, 0xff, 1,
			SOLO_DEF_MOT_THRESH >> 8);
	v4l2_ctrl_new_custom(hdl, &solo_osd_text_ctrl, शून्य);
	solo_enc->md_thresholds =
		v4l2_ctrl_new_custom(hdl, &solo_md_thresholds, शून्य);
	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ hdl_मुक्त;
	पूर्ण

	solo_enc->solo_dev = solo_dev;
	solo_enc->ch = ch;
	mutex_init(&solo_enc->lock);
	spin_lock_init(&solo_enc->av_lock);
	INIT_LIST_HEAD(&solo_enc->vidq_active);
	solo_enc->fmt = (solo_dev->type == SOLO_DEV_6010) ?
		V4L2_PIX_FMT_MPEG4 : V4L2_PIX_FMT_H264;
	solo_enc->type = SOLO_ENC_TYPE_STD;

	solo_enc->qp = SOLO_DEFAULT_QP;
	solo_enc->gop = solo_dev->fps;
	solo_enc->पूर्णांकerval = 1;
	solo_enc->mode = SOLO_ENC_MODE_CIF;
	solo_enc->motion_global = true;
	solo_enc->motion_thresh = SOLO_DEF_MOT_THRESH;
	solo_enc->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	solo_enc->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	solo_enc->vidq.ops = &solo_enc_video_qops;
	solo_enc->vidq.mem_ops = &vb2_dma_sg_memops;
	solo_enc->vidq.drv_priv = solo_enc;
	solo_enc->vidq.gfp_flags = __GFP_DMA32 | __GFP_KSWAPD_RECLAIM;
	solo_enc->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	solo_enc->vidq.buf_काष्ठा_size = माप(काष्ठा solo_vb2_buf);
	solo_enc->vidq.lock = &solo_enc->lock;
	solo_enc->vidq.dev = &solo_dev->pdev->dev;
	ret = vb2_queue_init(&solo_enc->vidq);
	अगर (ret)
		जाओ hdl_मुक्त;
	solo_update_mode(solo_enc);

	spin_lock_init(&solo_enc->motion_lock);

	/* Initialize this per encoder */
	solo_enc->jpeg_len = माप(jpeg_header);
	स_नकल(solo_enc->jpeg_header, jpeg_header, solo_enc->jpeg_len);

	solo_enc->desc_nelts = 32;
	solo_enc->desc_items = dma_alloc_coherent(&solo_dev->pdev->dev,
						  माप(काष्ठा solo_p2m_desc) *
						  solo_enc->desc_nelts,
						  &solo_enc->desc_dma,
						  GFP_KERNEL);
	ret = -ENOMEM;
	अगर (solo_enc->desc_items == शून्य)
		जाओ hdl_मुक्त;

	solo_enc->vfd = video_device_alloc();
	अगर (!solo_enc->vfd)
		जाओ pci_मुक्त;

	*solo_enc->vfd = solo_enc_ढाँचा;
	solo_enc->vfd->v4l2_dev = &solo_dev->v4l2_dev;
	solo_enc->vfd->ctrl_handler = hdl;
	solo_enc->vfd->queue = &solo_enc->vidq;
	solo_enc->vfd->lock = &solo_enc->lock;
	video_set_drvdata(solo_enc->vfd, solo_enc);
	ret = video_रेजिस्टर_device(solo_enc->vfd, VFL_TYPE_VIDEO, nr);
	अगर (ret < 0)
		जाओ vdev_release;

	snम_लिखो(solo_enc->vfd->name, माप(solo_enc->vfd->name),
		 "%s-enc (%i/%i)", SOLO6X10_NAME, solo_dev->vfd->num,
		 solo_enc->vfd->num);

	वापस solo_enc;

vdev_release:
	video_device_release(solo_enc->vfd);
pci_मुक्त:
	dma_मुक्त_coherent(&solo_enc->solo_dev->pdev->dev,
			  माप(काष्ठा solo_p2m_desc) * solo_enc->desc_nelts,
			  solo_enc->desc_items, solo_enc->desc_dma);
hdl_मुक्त:
	v4l2_ctrl_handler_मुक्त(hdl);
	kमुक्त(solo_enc);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम solo_enc_मुक्त(काष्ठा solo_enc_dev *solo_enc)
अणु
	अगर (solo_enc == शून्य)
		वापस;

	dma_मुक्त_coherent(&solo_enc->solo_dev->pdev->dev,
			  माप(काष्ठा solo_p2m_desc) * solo_enc->desc_nelts,
			  solo_enc->desc_items, solo_enc->desc_dma);
	video_unरेजिस्टर_device(solo_enc->vfd);
	v4l2_ctrl_handler_मुक्त(&solo_enc->hdl);
	kमुक्त(solo_enc);
पूर्ण

पूर्णांक solo_enc_v4l2_init(काष्ठा solo_dev *solo_dev, अचिन्हित nr)
अणु
	पूर्णांक i;

	init_रुकोqueue_head(&solo_dev->ring_thपढ़ो_रुको);

	solo_dev->vh_size = माप(vop_header);
	solo_dev->vh_buf = dma_alloc_coherent(&solo_dev->pdev->dev,
					      solo_dev->vh_size,
					      &solo_dev->vh_dma, GFP_KERNEL);
	अगर (solo_dev->vh_buf == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_dev->v4l2_enc[i] = solo_enc_alloc(solo_dev, i, nr);
		अगर (IS_ERR(solo_dev->v4l2_enc[i]))
			अवरोध;
	पूर्ण

	अगर (i != solo_dev->nr_chans) अणु
		पूर्णांक ret = PTR_ERR(solo_dev->v4l2_enc[i]);

		जबतक (i--)
			solo_enc_मुक्त(solo_dev->v4l2_enc[i]);
		dma_मुक्त_coherent(&solo_dev->pdev->dev, solo_dev->vh_size,
				  solo_dev->vh_buf, solo_dev->vh_dma);
		solo_dev->vh_buf = शून्य;
		वापस ret;
	पूर्ण

	अगर (solo_dev->type == SOLO_DEV_6010)
		solo_dev->enc_bw_reमुख्य = solo_dev->fps * 4 * 4;
	अन्यथा
		solo_dev->enc_bw_reमुख्य = solo_dev->fps * 4 * 5;

	dev_info(&solo_dev->pdev->dev, "Encoders as /dev/video%d-%d\n",
		 solo_dev->v4l2_enc[0]->vfd->num,
		 solo_dev->v4l2_enc[solo_dev->nr_chans - 1]->vfd->num);

	वापस solo_ring_start(solo_dev);
पूर्ण

व्योम solo_enc_v4l2_निकास(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	solo_ring_stop(solo_dev);

	क्रम (i = 0; i < solo_dev->nr_chans; i++)
		solo_enc_मुक्त(solo_dev->v4l2_enc[i]);

	अगर (solo_dev->vh_buf)
		dma_मुक्त_coherent(&solo_dev->pdev->dev, solo_dev->vh_size,
				  solo_dev->vh_buf, solo_dev->vh_dma);
पूर्ण
