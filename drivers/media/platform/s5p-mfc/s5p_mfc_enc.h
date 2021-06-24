<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_enc.h
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_ENC_H_
#घोषणा S5P_MFC_ENC_H_

स्थिर काष्ठा s5p_mfc_codec_ops *get_enc_codec_ops(व्योम);
काष्ठा vb2_ops *get_enc_queue_ops(व्योम);
स्थिर काष्ठा v4l2_ioctl_ops *get_enc_v4l2_ioctl_ops(व्योम);
काष्ठा s5p_mfc_fmt *get_enc_def_fmt(bool src);
पूर्णांक s5p_mfc_enc_ctrls_setup(काष्ठा s5p_mfc_ctx *ctx);
व्योम s5p_mfc_enc_ctrls_delete(काष्ठा s5p_mfc_ctx *ctx);
व्योम s5p_mfc_enc_init(काष्ठा s5p_mfc_ctx *ctx);

#पूर्ण_अगर /* S5P_MFC_ENC_H_  */
