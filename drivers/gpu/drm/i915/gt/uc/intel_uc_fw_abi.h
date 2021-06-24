<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_UC_FW_ABI_H
#घोषणा _INTEL_UC_FW_ABI_H

#समावेश <linux/types.h>
#समावेश <linux/build_bug.h>

/**
 * DOC: Firmware Layout
 *
 * The GuC/HuC firmware layout looks like this::
 *
 *      +======================================================================+
 *      |  Firmware blob                                                       |
 *      +===============+===============+============+============+============+
 *      |  CSS header   |     uCode     |  RSA key   |  modulus   |  exponent  |
 *      +===============+===============+============+============+============+
 *       <-header size->                 <---header size जारीd ----------->
 *       <--- size ----------------------------------------------------------->
 *                                       <-key size->
 *                                                    <-mod size->
 *                                                                 <-exp size->
 *
 * The firmware may or may not have modulus key and exponent data. The header,
 * uCode and RSA signature are must-have components that will be used by driver.
 * Length of each components, which is all in dwords, can be found in header.
 * In the हाल that modulus and exponent are not present in fw, a.k.a truncated
 * image, the length value still appears in header.
 *
 * Driver will करो some basic fw size validation based on the following rules:
 *
 * 1. Header, uCode and RSA are must-have components.
 * 2. All firmware components, अगर they present, are in the sequence illustrated
 *    in the layout table above.
 * 3. Length info of each component can be found in header, in dwords.
 * 4. Modulus and exponent key are not required by driver. They may not appear
 *    in fw. So driver will load a truncated firmware in this हाल.
 */

काष्ठा uc_css_header अणु
	u32 module_type;
	/*
	 * header_size includes all non-uCode bits, including css_header, rsa
	 * key, modulus key and exponent data.
	 */
	u32 header_size_dw;
	u32 header_version;
	u32 module_id;
	u32 module_venकरोr;
	u32 date;
#घोषणा CSS_DATE_DAY			(0xFF << 0)
#घोषणा CSS_DATE_MONTH			(0xFF << 8)
#घोषणा CSS_DATE_YEAR			(0xFFFF << 16)
	u32 size_dw; /* uCode plus header_size_dw */
	u32 key_size_dw;
	u32 modulus_size_dw;
	u32 exponent_size_dw;
	u32 समय;
#घोषणा CSS_TIME_HOUR			(0xFF << 0)
#घोषणा CSS_DATE_MIN			(0xFF << 8)
#घोषणा CSS_DATE_SEC			(0xFFFF << 16)
	अक्षर username[8];
	अक्षर buildnumber[12];
	u32 sw_version;
#घोषणा CSS_SW_VERSION_UC_MAJOR		(0xFF << 16)
#घोषणा CSS_SW_VERSION_UC_MINOR		(0xFF << 8)
#घोषणा CSS_SW_VERSION_UC_PATCH		(0xFF << 0)
	u32 reserved0[13];
	जोड़ अणु
		u32 निजी_data_size; /* only applies to GuC */
		u32 reserved1;
	पूर्ण;
	u32 header_info;
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा uc_css_header) == 128);

#पूर्ण_अगर /* _INTEL_UC_FW_ABI_H */
