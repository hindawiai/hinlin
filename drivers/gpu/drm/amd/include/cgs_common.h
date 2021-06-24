<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 */
#अगर_अघोषित _CGS_COMMON_H
#घोषणा _CGS_COMMON_H

#समावेश "amd_shared.h"

काष्ठा cgs_device;

/**
 * क्रमागत cgs_ind_reg - Indirect रेजिस्टर spaces
 */
क्रमागत cgs_ind_reg अणु
	CGS_IND_REG__PCIE,
	CGS_IND_REG__SMC,
	CGS_IND_REG__UVD_CTX,
	CGS_IND_REG__DIDT,
	CGS_IND_REG_GC_CAC,
	CGS_IND_REG_SE_CAC,
	CGS_IND_REG__AUDIO_ENDPT
पूर्ण;

/*
 * क्रमागत cgs_ucode_id - Firmware types क्रम dअगरferent IPs
 */
क्रमागत cgs_ucode_id अणु
	CGS_UCODE_ID_SMU = 0,
	CGS_UCODE_ID_SMU_SK,
	CGS_UCODE_ID_SDMA0,
	CGS_UCODE_ID_SDMA1,
	CGS_UCODE_ID_CP_CE,
	CGS_UCODE_ID_CP_PFP,
	CGS_UCODE_ID_CP_ME,
	CGS_UCODE_ID_CP_MEC,
	CGS_UCODE_ID_CP_MEC_JT1,
	CGS_UCODE_ID_CP_MEC_JT2,
	CGS_UCODE_ID_GMCON_RENG,
	CGS_UCODE_ID_RLC_G,
	CGS_UCODE_ID_STORAGE,
	CGS_UCODE_ID_MAXIMUM,
पूर्ण;

/**
 * काष्ठा cgs_firmware_info - Firmware inक्रमmation
 */
काष्ठा cgs_firmware_info अणु
	uपूर्णांक16_t		version;
	uपूर्णांक16_t		fw_version;
	uपूर्णांक16_t		feature_version;
	uपूर्णांक32_t		image_size;
	uपूर्णांक64_t		mc_addr;

	/* only क्रम smc firmware */
	uपूर्णांक32_t		ucode_start_address;

	व्योम			*kptr;
	bool			is_kicker;
पूर्ण;

प्रकार अचिन्हित दीर्घ cgs_handle_t;

/**
 * cgs_पढ़ो_रेजिस्टर() - Read an MMIO रेजिस्टर
 * @cgs_device:	opaque device handle
 * @offset:	रेजिस्टर offset
 *
 * Return:  रेजिस्टर value
 */
प्रकार uपूर्णांक32_t (*cgs_पढ़ो_रेजिस्टर_t)(काष्ठा cgs_device *cgs_device, अचिन्हित offset);

/**
 * cgs_ग_लिखो_रेजिस्टर() - Write an MMIO रेजिस्टर
 * @cgs_device:	opaque device handle
 * @offset:	रेजिस्टर offset
 * @value:	रेजिस्टर value
 */
प्रकार व्योम (*cgs_ग_लिखो_रेजिस्टर_t)(काष्ठा cgs_device *cgs_device, अचिन्हित offset,
				     uपूर्णांक32_t value);

/**
 * cgs_पढ़ो_ind_रेजिस्टर() - Read an indirect रेजिस्टर
 * @cgs_device:	opaque device handle
 * @offset:	रेजिस्टर offset
 *
 * Return:  रेजिस्टर value
 */
प्रकार uपूर्णांक32_t (*cgs_पढ़ो_ind_रेजिस्टर_t)(काष्ठा cgs_device *cgs_device, क्रमागत cgs_ind_reg space,
					    अचिन्हित index);

/**
 * cgs_ग_लिखो_ind_रेजिस्टर() - Write an indirect रेजिस्टर
 * @cgs_device:	opaque device handle
 * @offset:	रेजिस्टर offset
 * @value:	रेजिस्टर value
 */
प्रकार व्योम (*cgs_ग_लिखो_ind_रेजिस्टर_t)(काष्ठा cgs_device *cgs_device, क्रमागत cgs_ind_reg space,
					 अचिन्हित index, uपूर्णांक32_t value);

#घोषणा CGS_REG_FIELD_SHIFT(reg, field) reg##__##field##__SHIFT
#घोषणा CGS_REG_FIELD_MASK(reg, field) reg##__##field##_MASK

#घोषणा CGS_REG_SET_FIELD(orig_val, reg, field, field_val)			\
	(((orig_val) & ~CGS_REG_FIELD_MASK(reg, field)) |			\
	 (CGS_REG_FIELD_MASK(reg, field) & ((field_val) << CGS_REG_FIELD_SHIFT(reg, field))))

#घोषणा CGS_REG_GET_FIELD(value, reg, field)				\
	(((value) & CGS_REG_FIELD_MASK(reg, field)) >> CGS_REG_FIELD_SHIFT(reg, field))

#घोषणा CGS_WREG32_FIELD(device, reg, field, val)	\
	cgs_ग_लिखो_रेजिस्टर(device, mm##reg, (cgs_पढ़ो_रेजिस्टर(device, mm##reg) & ~CGS_REG_FIELD_MASK(reg, field)) | (val) << CGS_REG_FIELD_SHIFT(reg, field))

#घोषणा CGS_WREG32_FIELD_IND(device, space, reg, field, val)	\
	cgs_ग_लिखो_ind_रेजिस्टर(device, space, ix##reg, (cgs_पढ़ो_ind_रेजिस्टर(device, space, ix##reg) & ~CGS_REG_FIELD_MASK(reg, field)) | (val) << CGS_REG_FIELD_SHIFT(reg, field))

प्रकार पूर्णांक (*cgs_get_firmware_info)(काष्ठा cgs_device *cgs_device,
				     क्रमागत cgs_ucode_id type,
				     काष्ठा cgs_firmware_info *info);

काष्ठा cgs_ops अणु
	/* MMIO access */
	cgs_पढ़ो_रेजिस्टर_t पढ़ो_रेजिस्टर;
	cgs_ग_लिखो_रेजिस्टर_t ग_लिखो_रेजिस्टर;
	cgs_पढ़ो_ind_रेजिस्टर_t पढ़ो_ind_रेजिस्टर;
	cgs_ग_लिखो_ind_रेजिस्टर_t ग_लिखो_ind_रेजिस्टर;
	/* Firmware Info */
	cgs_get_firmware_info get_firmware_info;
पूर्ण;

काष्ठा cgs_os_ops; /* To be define in OS-specअगरic CGS header */

काष्ठा cgs_device
अणु
	स्थिर काष्ठा cgs_ops *ops;
	/* to be embedded at the start of driver निजी काष्ठाure */
पूर्ण;

/* Convenience macros that make CGS indirect function calls look like
 * normal function calls */
#घोषणा CGS_CALL(func,dev,...) \
	(((काष्ठा cgs_device *)dev)->ops->func(dev, ##__VA_ARGS__))
#घोषणा CGS_OS_CALL(func,dev,...) \
	(((काष्ठा cgs_device *)dev)->os_ops->func(dev, ##__VA_ARGS__))

#घोषणा cgs_पढ़ो_रेजिस्टर(dev,offset)		\
	CGS_CALL(पढ़ो_रेजिस्टर,dev,offset)
#घोषणा cgs_ग_लिखो_रेजिस्टर(dev,offset,value)		\
	CGS_CALL(ग_लिखो_रेजिस्टर,dev,offset,value)
#घोषणा cgs_पढ़ो_ind_रेजिस्टर(dev,space,index)		\
	CGS_CALL(पढ़ो_ind_रेजिस्टर,dev,space,index)
#घोषणा cgs_ग_लिखो_ind_रेजिस्टर(dev,space,index,value)		\
	CGS_CALL(ग_लिखो_ind_रेजिस्टर,dev,space,index,value)

#घोषणा cgs_get_firmware_info(dev, type, info)	\
	CGS_CALL(get_firmware_info, dev, type, info)

#पूर्ण_अगर /* _CGS_COMMON_H */
