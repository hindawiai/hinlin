<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/platक्रमm_device.h>
#अगर_अघोषित __LLCC_QCOM__
#घोषणा __LLCC_QCOM__

#घोषणा LLCC_CPUSS       1
#घोषणा LLCC_VIDSC0      2
#घोषणा LLCC_VIDSC1      3
#घोषणा LLCC_ROTATOR     4
#घोषणा LLCC_VOICE       5
#घोषणा LLCC_AUDIO       6
#घोषणा LLCC_MDMHPGRW    7
#घोषणा LLCC_MDM         8
#घोषणा LLCC_MODHW       9
#घोषणा LLCC_CMPT        10
#घोषणा LLCC_GPUHTW      11
#घोषणा LLCC_GPU         12
#घोषणा LLCC_MMUHWT      13
#घोषणा LLCC_CMPTDMA     15
#घोषणा LLCC_DISP        16
#घोषणा LLCC_VIDFW       17
#घोषणा LLCC_MDMHPFX     20
#घोषणा LLCC_MDMPNG      21
#घोषणा LLCC_AUDHW       22
#घोषणा LLCC_NPU         23
#घोषणा LLCC_WLHW        24
#घोषणा LLCC_CVP         28
#घोषणा LLCC_MODPE       29
#घोषणा LLCC_APTCM       30
#घोषणा LLCC_WRCACHE     31

/**
 * काष्ठा llcc_slice_desc - Cache slice descriptor
 * @slice_id: llcc slice id
 * @slice_size: Size allocated क्रम the llcc slice
 */
काष्ठा llcc_slice_desc अणु
	u32 slice_id;
	माप_प्रकार slice_size;
पूर्ण;

/**
 * काष्ठा llcc_edac_reg_data - llcc edac रेजिस्टरs data क्रम each error type
 * @name: Name of the error
 * @synd_reg: Syndrome रेजिस्टर address
 * @count_status_reg: Status रेजिस्टर address to पढ़ो the error count
 * @ways_status_reg: Status रेजिस्टर address to पढ़ो the error ways
 * @reg_cnt: Number of रेजिस्टरs
 * @count_mask: Mask value to get the error count
 * @ways_mask: Mask value to get the error ways
 * @count_shअगरt: Shअगरt value to get the error count
 * @ways_shअगरt: Shअगरt value to get the error ways
 */
काष्ठा llcc_edac_reg_data अणु
	अक्षर *name;
	u64 synd_reg;
	u64 count_status_reg;
	u64 ways_status_reg;
	u32 reg_cnt;
	u32 count_mask;
	u32 ways_mask;
	u8  count_shअगरt;
	u8  ways_shअगरt;
पूर्ण;

/**
 * काष्ठा llcc_drv_data - Data associated with the llcc driver
 * @regmap: regmap associated with the llcc device
 * @bcast_regmap: regmap associated with llcc broadcast offset
 * @cfg: poपूर्णांकer to the data काष्ठाure क्रम slice configuration
 * @lock: mutex associated with each slice
 * @cfg_size: size of the config data table
 * @max_slices: max slices as पढ़ो from device tree
 * @num_banks: Number of llcc banks
 * @biपंचांगap: Bit map to track the active slice ids
 * @offsets: Poपूर्णांकer to the bank offsets array
 * @ecc_irq: पूर्णांकerrupt क्रम llcc cache error detection and reporting
 * @major_version: Indicates the LLCC major version
 */
काष्ठा llcc_drv_data अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap *bcast_regmap;
	स्थिर काष्ठा llcc_slice_config *cfg;
	काष्ठा mutex lock;
	u32 cfg_size;
	u32 max_slices;
	u32 num_banks;
	अचिन्हित दीर्घ *biपंचांगap;
	u32 *offsets;
	पूर्णांक ecc_irq;
	u32 major_version;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QCOM_LLCC)
/**
 * llcc_slice_getd - get llcc slice descriptor
 * @uid: useहाल_id of the client
 */
काष्ठा llcc_slice_desc *llcc_slice_getd(u32 uid);

/**
 * llcc_slice_putd - llcc slice descritpor
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
व्योम llcc_slice_putd(काष्ठा llcc_slice_desc *desc);

/**
 * llcc_get_slice_id - get slice id
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
पूर्णांक llcc_get_slice_id(काष्ठा llcc_slice_desc *desc);

/**
 * llcc_get_slice_size - llcc slice size
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
माप_प्रकार llcc_get_slice_size(काष्ठा llcc_slice_desc *desc);

/**
 * llcc_slice_activate - Activate the llcc slice
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
पूर्णांक llcc_slice_activate(काष्ठा llcc_slice_desc *desc);

/**
 * llcc_slice_deactivate - Deactivate the llcc slice
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
पूर्णांक llcc_slice_deactivate(काष्ठा llcc_slice_desc *desc);

#अन्यथा
अटल अंतरभूत काष्ठा llcc_slice_desc *llcc_slice_getd(u32 uid)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम llcc_slice_putd(काष्ठा llcc_slice_desc *desc)
अणु

पूर्ण;

अटल अंतरभूत पूर्णांक llcc_get_slice_id(काष्ठा llcc_slice_desc *desc)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत माप_प्रकार llcc_get_slice_size(काष्ठा llcc_slice_desc *desc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक llcc_slice_activate(काष्ठा llcc_slice_desc *desc)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक llcc_slice_deactivate(काष्ठा llcc_slice_desc *desc)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
