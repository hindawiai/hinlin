<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  पूर्णांकel-nhlt.h - Intel HDA Platक्रमm NHLT header
 *
 *  Copyright (c) 2015-2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_NHLT_H__
#घोषणा __INTEL_NHLT_H__

#समावेश <linux/acpi.h>

#अगर IS_ENABLED(CONFIG_ACPI) && IS_ENABLED(CONFIG_SND_INTEL_NHLT)

काष्ठा wav_fmt अणु
	u16 fmt_tag;
	u16 channels;
	u32 samples_per_sec;
	u32 avg_bytes_per_sec;
	u16 block_align;
	u16 bits_per_sample;
	u16 cb_size;
पूर्ण __packed;

काष्ठा wav_fmt_ext अणु
	काष्ठा wav_fmt fmt;
	जोड़ samples अणु
		u16 valid_bits_per_sample;
		u16 samples_per_block;
		u16 reserved;
	पूर्ण sample;
	u32 channel_mask;
	u8 sub_fmt[16];
पूर्ण __packed;

क्रमागत nhlt_link_type अणु
	NHLT_LINK_HDA = 0,
	NHLT_LINK_DSP = 1,
	NHLT_LINK_DMIC = 2,
	NHLT_LINK_SSP = 3,
	NHLT_LINK_INVALID
पूर्ण;

क्रमागत nhlt_device_type अणु
	NHLT_DEVICE_BT = 0,
	NHLT_DEVICE_DMIC = 1,
	NHLT_DEVICE_I2S = 4,
	NHLT_DEVICE_INVALID
पूर्ण;

काष्ठा nhlt_specअगरic_cfg अणु
	u32 size;
	u8 caps[];
पूर्ण __packed;

काष्ठा nhlt_fmt_cfg अणु
	काष्ठा wav_fmt_ext fmt_ext;
	काष्ठा nhlt_specअगरic_cfg config;
पूर्ण __packed;

काष्ठा nhlt_fmt अणु
	u8 fmt_count;
	काष्ठा nhlt_fmt_cfg fmt_config[];
पूर्ण __packed;

काष्ठा nhlt_endpoपूर्णांक अणु
	u32  length;
	u8   linktype;
	u8   instance_id;
	u16  venकरोr_id;
	u16  device_id;
	u16  revision_id;
	u32  subप्रणाली_id;
	u8   device_type;
	u8   direction;
	u8   भव_bus_id;
	काष्ठा nhlt_specअगरic_cfg config;
पूर्ण __packed;

काष्ठा nhlt_acpi_table अणु
	काष्ठा acpi_table_header header;
	u8 endpoपूर्णांक_count;
	काष्ठा nhlt_endpoपूर्णांक desc[];
पूर्ण __packed;

काष्ठा nhlt_resource_desc  अणु
	u32 extra;
	u16 flags;
	u64 addr_spc_gra;
	u64 min_addr;
	u64 max_addr;
	u64 addr_trans_offset;
	u64 length;
पूर्ण __packed;

#घोषणा MIC_ARRAY_2CH 2
#घोषणा MIC_ARRAY_4CH 4

काष्ठा nhlt_device_specअगरic_config अणु
	u8 भव_slot;
	u8 config_type;
पूर्ण __packed;

काष्ठा nhlt_dmic_array_config अणु
	काष्ठा nhlt_device_specअगरic_config device_config;
	u8 array_type;
पूर्ण __packed;

काष्ठा nhlt_venकरोr_dmic_array_config अणु
	काष्ठा nhlt_dmic_array_config dmic_config;
	u8 nb_mics;
	/* TODO add venकरोr mic config */
पूर्ण __packed;

क्रमागत अणु
	NHLT_CONFIG_TYPE_GENERIC = 0,
	NHLT_CONFIG_TYPE_MIC_ARRAY = 1
पूर्ण;

क्रमागत अणु
	NHLT_MIC_ARRAY_2CH_SMALL = 0xa,
	NHLT_MIC_ARRAY_2CH_BIG = 0xb,
	NHLT_MIC_ARRAY_4CH_1ST_GEOM = 0xc,
	NHLT_MIC_ARRAY_4CH_L_SHAPED = 0xd,
	NHLT_MIC_ARRAY_4CH_2ND_GEOM = 0xe,
	NHLT_MIC_ARRAY_VENDOR_DEFINED = 0xf,
पूर्ण;

काष्ठा nhlt_acpi_table *पूर्णांकel_nhlt_init(काष्ठा device *dev);

व्योम पूर्णांकel_nhlt_मुक्त(काष्ठा nhlt_acpi_table *addr);

पूर्णांक पूर्णांकel_nhlt_get_dmic_geo(काष्ठा device *dev, काष्ठा nhlt_acpi_table *nhlt);

#अन्यथा

काष्ठा nhlt_acpi_table;

अटल अंतरभूत काष्ठा nhlt_acpi_table *पूर्णांकel_nhlt_init(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_nhlt_मुक्त(काष्ठा nhlt_acpi_table *addr)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_nhlt_get_dmic_geo(काष्ठा device *dev,
					  काष्ठा nhlt_acpi_table *nhlt)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
