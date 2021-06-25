<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wmfw.h - Wolfson firmware क्रमmat inक्रमmation
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __WMFW_H
#घोषणा __WMFW_H

#समावेश <linux/types.h>

#घोषणा WMFW_MAX_ALG_NAME         256
#घोषणा WMFW_MAX_ALG_DESCR_NAME   256

#घोषणा WMFW_MAX_COEFF_NAME       256
#घोषणा WMFW_MAX_COEFF_DESCR_NAME 256

#घोषणा WMFW_CTL_FLAG_SYS         0x8000
#घोषणा WMFW_CTL_FLAG_VOLATILE    0x0004
#घोषणा WMFW_CTL_FLAG_WRITEABLE   0x0002
#घोषणा WMFW_CTL_FLAG_READABLE    0x0001

/* Non-ALSA coefficient types start at 0x1000 */
#घोषणा WMFW_CTL_TYPE_ACKED       ((__क्रमce snd_ctl_elem_type_t)0x1000) /* acked control */
#घोषणा WMFW_CTL_TYPE_HOSTEVENT   ((__क्रमce snd_ctl_elem_type_t)0x1001) /* event control */
#घोषणा WMFW_CTL_TYPE_HOST_BUFFER ((__क्रमce snd_ctl_elem_type_t)0x1002) /* host buffer poपूर्णांकer */

काष्ठा wmfw_header अणु
	अक्षर magic[4];
	__le32 len;
	__le16 rev;
	u8 core;
	u8 ver;
पूर्ण __packed;

काष्ठा wmfw_footer अणु
	__le64 बारtamp;
	__le32 checksum;
पूर्ण __packed;

काष्ठा wmfw_adsp1_sizes अणु
	__le32 dm;
	__le32 pm;
	__le32 zm;
पूर्ण __packed;

काष्ठा wmfw_adsp2_sizes अणु
	__le32 xm;
	__le32 ym;
	__le32 pm;
	__le32 zm;
पूर्ण __packed;

काष्ठा wmfw_region अणु
	जोड़ अणु
		__be32 type;
		__le32 offset;
	पूर्ण;
	__le32 len;
	u8 data[];
पूर्ण __packed;

काष्ठा wmfw_id_hdr अणु
	__be32 core_id;
	__be32 core_rev;
	__be32 id;
	__be32 ver;
पूर्ण __packed;

काष्ठा wmfw_v3_id_hdr अणु
	__be32 core_id;
	__be32 block_rev;
	__be32 venकरोr_id;
	__be32 id;
	__be32 ver;
पूर्ण __packed;

काष्ठा wmfw_adsp1_id_hdr अणु
	काष्ठा wmfw_id_hdr fw;
	__be32 zm;
	__be32 dm;
	__be32 n_algs;
पूर्ण __packed;

काष्ठा wmfw_adsp2_id_hdr अणु
	काष्ठा wmfw_id_hdr fw;
	__be32 zm;
	__be32 xm;
	__be32 ym;
	__be32 n_algs;
पूर्ण __packed;

काष्ठा wmfw_halo_id_hdr अणु
	काष्ठा wmfw_v3_id_hdr fw;
	__be32 xm_base;
	__be32 xm_size;
	__be32 ym_base;
	__be32 ym_size;
	__be32 n_algs;
पूर्ण __packed;

काष्ठा wmfw_alg_hdr अणु
	__be32 id;
	__be32 ver;
पूर्ण __packed;

काष्ठा wmfw_adsp1_alg_hdr अणु
	काष्ठा wmfw_alg_hdr alg;
	__be32 zm;
	__be32 dm;
पूर्ण __packed;

काष्ठा wmfw_adsp2_alg_hdr अणु
	काष्ठा wmfw_alg_hdr alg;
	__be32 zm;
	__be32 xm;
	__be32 ym;
पूर्ण __packed;

काष्ठा wmfw_halo_alg_hdr अणु
	काष्ठा wmfw_alg_hdr alg;
	__be32 xm_base;
	__be32 xm_size;
	__be32 ym_base;
	__be32 ym_size;
पूर्ण __packed;

काष्ठा wmfw_adsp_alg_data अणु
	__le32 id;
	u8 name[WMFW_MAX_ALG_NAME];
	u8 descr[WMFW_MAX_ALG_DESCR_NAME];
	__le32 ncoeff;
	u8 data[];
पूर्ण __packed;

काष्ठा wmfw_adsp_coeff_data अणु
	काष्ठा अणु
		__le16 offset;
		__le16 type;
		__le32 size;
	पूर्ण hdr;
	u8 name[WMFW_MAX_COEFF_NAME];
	u8 descr[WMFW_MAX_COEFF_DESCR_NAME];
	__le16 ctl_type;
	__le16 flags;
	__le32 len;
	u8 data[];
पूर्ण __packed;

काष्ठा wmfw_coeff_hdr अणु
	u8 magic[4];
	__le32 len;
	जोड़ अणु
		__be32 rev;
		__le32 ver;
	पूर्ण;
	जोड़ अणु
		__be32 core;
		__le32 core_ver;
	पूर्ण;
	u8 data[];
पूर्ण __packed;

काष्ठा wmfw_coeff_item अणु
	__le16 offset;
	__le16 type;
	__le32 id;
	__le32 ver;
	__le32 sr;
	__le32 len;
	u8 data[];
पूर्ण __packed;

#घोषणा WMFW_ADSP1 1
#घोषणा WMFW_ADSP2 2
#घोषणा WMFW_HALO 4

#घोषणा WMFW_ABSOLUTE         0xf0
#घोषणा WMFW_ALGORITHM_DATA   0xf2
#घोषणा WMFW_METADATA         0xfc
#घोषणा WMFW_NAME_TEXT        0xfe
#घोषणा WMFW_INFO_TEXT        0xff

#घोषणा WMFW_ADSP1_PM 2
#घोषणा WMFW_ADSP1_DM 3
#घोषणा WMFW_ADSP1_ZM 4

#घोषणा WMFW_ADSP2_PM 2
#घोषणा WMFW_ADSP2_ZM 4
#घोषणा WMFW_ADSP2_XM 5
#घोषणा WMFW_ADSP2_YM 6

#घोषणा WMFW_HALO_PM_PACKED 0x10
#घोषणा WMFW_HALO_XM_PACKED 0x11
#घोषणा WMFW_HALO_YM_PACKED 0x12

#पूर्ण_अगर
