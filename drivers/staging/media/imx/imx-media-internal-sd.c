<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Media driver क्रम Freescale i.MX5/6 SOC
 *
 * Adds the IPU पूर्णांकernal subdevices and the media links between them.
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश "imx-media.h"

/* max pads per पूर्णांकernal-sd */
#घोषणा MAX_INTERNAL_PADS   8
/* max links per पूर्णांकernal-sd pad */
#घोषणा MAX_INTERNAL_LINKS  8

काष्ठा पूर्णांकernal_subdev;

काष्ठा पूर्णांकernal_link अणु
	पूर्णांक remote;
	पूर्णांक local_pad;
	पूर्णांक remote_pad;
पूर्ण;

काष्ठा पूर्णांकernal_pad अणु
	पूर्णांक num_links;
	काष्ठा पूर्णांकernal_link link[MAX_INTERNAL_LINKS];
पूर्ण;

काष्ठा पूर्णांकernal_subdev अणु
	u32 grp_id;
	काष्ठा पूर्णांकernal_pad pad[MAX_INTERNAL_PADS];

	काष्ठा v4l2_subdev * (*sync_रेजिस्टर)(काष्ठा v4l2_device *v4l2_dev,
					      काष्ठा device *ipu_dev,
					      काष्ठा ipu_soc *ipu,
					      u32 grp_id);
	पूर्णांक (*sync_unरेजिस्टर)(काष्ठा v4l2_subdev *sd);
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकernal_subdev पूर्णांक_subdev[NUM_IPU_SUBDEVS] = अणु
	[IPU_CSI0] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_CSI0,
		.pad[CSI_SRC_PAD_सूचीECT] = अणु
			.num_links = 2,
			.link = अणु
				अणु
					.local_pad = CSI_SRC_PAD_सूचीECT,
					.remote = IPU_IC_PRP,
					.remote_pad = PRP_SINK_PAD,
				पूर्ण, अणु
					.local_pad = CSI_SRC_PAD_सूचीECT,
					.remote = IPU_VDIC,
					.remote_pad = VDIC_SINK_PAD_सूचीECT,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	[IPU_CSI1] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_CSI1,
		.pad[CSI_SRC_PAD_सूचीECT] = अणु
			.num_links = 2,
			.link = अणु
				अणु
					.local_pad = CSI_SRC_PAD_सूचीECT,
					.remote = IPU_IC_PRP,
					.remote_pad = PRP_SINK_PAD,
				पूर्ण, अणु
					.local_pad = CSI_SRC_PAD_सूचीECT,
					.remote = IPU_VDIC,
					.remote_pad = VDIC_SINK_PAD_सूचीECT,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	[IPU_VDIC] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_VDIC,
		.sync_रेजिस्टर = imx_media_vdic_रेजिस्टर,
		.sync_unरेजिस्टर = imx_media_vdic_unरेजिस्टर,
		.pad[VDIC_SRC_PAD_सूचीECT] = अणु
			.num_links = 1,
			.link = अणु
				अणु
					.local_pad = VDIC_SRC_PAD_सूचीECT,
					.remote = IPU_IC_PRP,
					.remote_pad = PRP_SINK_PAD,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	[IPU_IC_PRP] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_IC_PRP,
		.sync_रेजिस्टर = imx_media_ic_रेजिस्टर,
		.sync_unरेजिस्टर = imx_media_ic_unरेजिस्टर,
		.pad[PRP_SRC_PAD_PRPENC] = अणु
			.num_links = 1,
			.link = अणु
				अणु
					.local_pad = PRP_SRC_PAD_PRPENC,
					.remote = IPU_IC_PRPENC,
					.remote_pad = PRPENCVF_SINK_PAD,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.pad[PRP_SRC_PAD_PRPVF] = अणु
			.num_links = 1,
			.link = अणु
				अणु
					.local_pad = PRP_SRC_PAD_PRPVF,
					.remote = IPU_IC_PRPVF,
					.remote_pad = PRPENCVF_SINK_PAD,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	[IPU_IC_PRPENC] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_IC_PRPENC,
		.sync_रेजिस्टर = imx_media_ic_रेजिस्टर,
		.sync_unरेजिस्टर = imx_media_ic_unरेजिस्टर,
	पूर्ण,

	[IPU_IC_PRPVF] = अणु
		.grp_id = IMX_MEDIA_GRP_ID_IPU_IC_PRPVF,
		.sync_रेजिस्टर = imx_media_ic_रेजिस्टर,
		.sync_unरेजिस्टर = imx_media_ic_unरेजिस्टर,
	पूर्ण,
पूर्ण;

अटल पूर्णांक create_पूर्णांकernal_link(काष्ठा imx_media_dev *imxmd,
				काष्ठा v4l2_subdev *src,
				काष्ठा v4l2_subdev *sink,
				स्थिर काष्ठा पूर्णांकernal_link *link)
अणु
	पूर्णांक ret;

	/* skip अगर this link alपढ़ोy created */
	अगर (media_entity_find_link(&src->entity.pads[link->local_pad],
				   &sink->entity.pads[link->remote_pad]))
		वापस 0;

	dev_dbg(imxmd->md.dev, "%s:%d -> %s:%d\n",
		src->name, link->local_pad,
		sink->name, link->remote_pad);

	ret = media_create_pad_link(&src->entity, link->local_pad,
				    &sink->entity, link->remote_pad, 0);
	अगर (ret)
		v4l2_err(&imxmd->v4l2_dev, "%s failed: %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक create_ipu_पूर्णांकernal_links(काष्ठा imx_media_dev *imxmd,
				     स्थिर काष्ठा पूर्णांकernal_subdev *पूर्णांकsd,
				     काष्ठा v4l2_subdev *sd,
				     पूर्णांक ipu_id)
अणु
	स्थिर काष्ठा पूर्णांकernal_pad *पूर्णांकpad;
	स्थिर काष्ठा पूर्णांकernal_link *link;
	काष्ठा media_pad *pad;
	पूर्णांक i, j, ret;

	/* create the source->sink links */
	क्रम (i = 0; i < sd->entity.num_pads; i++) अणु
		पूर्णांकpad = &पूर्णांकsd->pad[i];
		pad = &sd->entity.pads[i];

		अगर (!(pad->flags & MEDIA_PAD_FL_SOURCE))
			जारी;

		क्रम (j = 0; j < पूर्णांकpad->num_links; j++) अणु
			काष्ठा v4l2_subdev *sink;

			link = &पूर्णांकpad->link[j];
			sink = imxmd->sync_sd[ipu_id][link->remote];

			ret = create_पूर्णांकernal_link(imxmd, sd, sink, link);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक imx_media_रेजिस्टर_ipu_पूर्णांकernal_subdevs(काष्ठा imx_media_dev *imxmd,
					    काष्ठा v4l2_subdev *csi)
अणु
	काष्ठा device *ipu_dev = csi->dev->parent;
	स्थिर काष्ठा पूर्णांकernal_subdev *पूर्णांकsd;
	काष्ठा v4l2_subdev *sd;
	काष्ठा ipu_soc *ipu;
	पूर्णांक i, ipu_id, ret;

	ipu = dev_get_drvdata(ipu_dev);
	अगर (!ipu) अणु
		v4l2_err(&imxmd->v4l2_dev, "invalid IPU device!\n");
		वापस -ENODEV;
	पूर्ण

	ipu_id = ipu_get_num(ipu);
	अगर (ipu_id > 1) अणु
		v4l2_err(&imxmd->v4l2_dev, "invalid IPU id %d!\n", ipu_id);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&imxmd->mutex);

	/* record this IPU */
	अगर (!imxmd->ipu[ipu_id])
		imxmd->ipu[ipu_id] = ipu;

	/* रेजिस्टर the synchronous subdevs */
	क्रम (i = 0; i < NUM_IPU_SUBDEVS; i++) अणु
		पूर्णांकsd = &पूर्णांक_subdev[i];

		sd = imxmd->sync_sd[ipu_id][i];

		/*
		 * skip अगर this sync subdev alपढ़ोy रेजिस्टरed or its
		 * not a sync subdev (one of the CSIs)
		 */
		अगर (sd || !पूर्णांकsd->sync_रेजिस्टर)
			जारी;

		mutex_unlock(&imxmd->mutex);
		sd = पूर्णांकsd->sync_रेजिस्टर(&imxmd->v4l2_dev, ipu_dev, ipu,
					  पूर्णांकsd->grp_id);
		mutex_lock(&imxmd->mutex);
		अगर (IS_ERR(sd)) अणु
			ret = PTR_ERR(sd);
			जाओ err_unwind;
		पूर्ण

		imxmd->sync_sd[ipu_id][i] = sd;
	पूर्ण

	/*
	 * all the sync subdevs are रेजिस्टरed, create the media links
	 * between them.
	 */
	क्रम (i = 0; i < NUM_IPU_SUBDEVS; i++) अणु
		पूर्णांकsd = &पूर्णांक_subdev[i];

		अगर (पूर्णांकsd->grp_id == csi->grp_id) अणु
			sd = csi;
		पूर्ण अन्यथा अणु
			sd = imxmd->sync_sd[ipu_id][i];
			अगर (!sd)
				जारी;
		पूर्ण

		ret = create_ipu_पूर्णांकernal_links(imxmd, पूर्णांकsd, sd, ipu_id);
		अगर (ret) अणु
			mutex_unlock(&imxmd->mutex);
			imx_media_unरेजिस्टर_ipu_पूर्णांकernal_subdevs(imxmd);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&imxmd->mutex);
	वापस 0;

err_unwind:
	जबतक (--i >= 0) अणु
		पूर्णांकsd = &पूर्णांक_subdev[i];
		sd = imxmd->sync_sd[ipu_id][i];
		अगर (!sd || !पूर्णांकsd->sync_unरेजिस्टर)
			जारी;
		mutex_unlock(&imxmd->mutex);
		पूर्णांकsd->sync_unरेजिस्टर(sd);
		mutex_lock(&imxmd->mutex);
	पूर्ण

	mutex_unlock(&imxmd->mutex);
	वापस ret;
पूर्ण

व्योम imx_media_unरेजिस्टर_ipu_पूर्णांकernal_subdevs(काष्ठा imx_media_dev *imxmd)
अणु
	स्थिर काष्ठा पूर्णांकernal_subdev *पूर्णांकsd;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i, j;

	mutex_lock(&imxmd->mutex);

	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < NUM_IPU_SUBDEVS; j++) अणु
			पूर्णांकsd = &पूर्णांक_subdev[j];
			sd = imxmd->sync_sd[i][j];

			अगर (!sd || !पूर्णांकsd->sync_unरेजिस्टर)
				जारी;

			mutex_unlock(&imxmd->mutex);
			पूर्णांकsd->sync_unरेजिस्टर(sd);
			mutex_lock(&imxmd->mutex);
		पूर्ण
	पूर्ण

	mutex_unlock(&imxmd->mutex);
पूर्ण
