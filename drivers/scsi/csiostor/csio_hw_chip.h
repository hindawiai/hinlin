<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2013 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CSIO_HW_CHIP_H__
#घोषणा __CSIO_HW_CHIP_H__

#समावेश "csio_defs.h"

/* Define MACRO values */
#घोषणा CSIO_HW_T5				0x5000
#घोषणा CSIO_T5_FCOE_ASIC			0x5600
#घोषणा CSIO_HW_T6				0x6000
#घोषणा CSIO_T6_FCOE_ASIC			0x6600
#घोषणा CSIO_HW_CHIP_MASK			0xF000

#घोषणा T5_REGMAP_SIZE				(332 * 1024)
#घोषणा FW_FNAME_T5				"cxgb4/t5fw.bin"
#घोषणा FW_CFG_NAME_T5				"cxgb4/t5-config.txt"
#घोषणा FW_FNAME_T6				"cxgb4/t6fw.bin"
#घोषणा FW_CFG_NAME_T6				"cxgb4/t6-config.txt"

#घोषणा CHELSIO_CHIP_CODE(version, revision) (((version) << 4) | (revision))
#घोषणा CHELSIO_CHIP_FPGA          0x100
#घोषणा CHELSIO_CHIP_VERSION(code) (((code) >> 12) & 0xf)
#घोषणा CHELSIO_CHIP_RELEASE(code) ((code) & 0xf)

#घोषणा CHELSIO_T5		0x5
#घोषणा CHELSIO_T6		0x6

क्रमागत chip_type अणु
	T5_A0 = CHELSIO_CHIP_CODE(CHELSIO_T5, 0),
	T5_A1 = CHELSIO_CHIP_CODE(CHELSIO_T5, 1),
	T5_FIRST_REV	= T5_A0,
	T5_LAST_REV	= T5_A1,

	T6_A0 = CHELSIO_CHIP_CODE(CHELSIO_T6, 0),
	T6_FIRST_REV    = T6_A0,
	T6_LAST_REV     = T6_A0,
पूर्ण;

अटल अंतरभूत पूर्णांक csio_is_t5(uपूर्णांक16_t chip)
अणु
	वापस (chip == CSIO_HW_T5);
पूर्ण

अटल अंतरभूत पूर्णांक csio_is_t6(uपूर्णांक16_t chip)
अणु
	वापस (chip == CSIO_HW_T6);
पूर्ण

/* Define MACRO DEFINITIONS */
#घोषणा CSIO_DEVICE(devid, idx)						\
	अणु PCI_VENDOR_ID_CHELSIO, (devid), PCI_ANY_ID, PCI_ANY_ID, 0, 0, (idx) पूर्ण

#समावेश "t4fw_api.h"
#समावेश "t4fw_version.h"

#घोषणा FW_VERSION(chip) ( \
		FW_HDR_FW_VER_MAJOR_G(chip##FW_VERSION_MAJOR) | \
		FW_HDR_FW_VER_MINOR_G(chip##FW_VERSION_MINOR) | \
		FW_HDR_FW_VER_MICRO_G(chip##FW_VERSION_MICRO) | \
		FW_HDR_FW_VER_BUILD_G(chip##FW_VERSION_BUILD))
#घोषणा FW_INTFVER(chip, पूर्णांकf) (FW_HDR_INTFVER_##पूर्णांकf)

काष्ठा fw_info अणु
	u8 chip;
	अक्षर *fs_name;
	अक्षर *fw_mod_name;
	काष्ठा fw_hdr fw_hdr;
पूर्ण;

/* Declare ENUMS */
क्रमागत अणु MEM_EDC0, MEM_EDC1, MEM_MC, MEM_MC0 = MEM_MC, MEM_MC1 पूर्ण;

क्रमागत अणु
	MEMWIN_APERTURE = 2048,
	MEMWIN_BASE     = 0x1b800,
पूर्ण;

/* Slow path handlers */
काष्ठा पूर्णांकr_info अणु
	अचिन्हित पूर्णांक mask;       /* bits to check in पूर्णांकerrupt status */
	स्थिर अक्षर *msg;         /* message to prपूर्णांक or शून्य */
	लघु stat_idx;          /* stat counter to increment or -1 */
	अचिन्हित लघु fatal;    /* whether the condition reported is fatal */
पूर्ण;

/* T4/T5 Chip specअगरic ops */
काष्ठा csio_hw;
काष्ठा csio_hw_chip_ops अणु
	पूर्णांक (*chip_set_mem_win)(काष्ठा csio_hw *, uपूर्णांक32_t);
	व्योम (*chip_pcie_पूर्णांकr_handler)(काष्ठा csio_hw *);
	uपूर्णांक32_t (*chip_flash_cfg_addr)(काष्ठा csio_hw *);
	पूर्णांक (*chip_mc_पढ़ो)(काष्ठा csio_hw *, पूर्णांक, uपूर्णांक32_t,
					__be32 *, uपूर्णांक64_t *);
	पूर्णांक (*chip_edc_पढ़ो)(काष्ठा csio_hw *, पूर्णांक, uपूर्णांक32_t,
					__be32 *, uपूर्णांक64_t *);
	पूर्णांक (*chip_memory_rw)(काष्ठा csio_hw *, u32, पूर्णांक, u32,
					u32, uपूर्णांक32_t *, पूर्णांक);
	व्योम (*chip_dfs_create_ext_mem)(काष्ठा csio_hw *);
पूर्ण;

बाह्य काष्ठा csio_hw_chip_ops t5_ops;

#पूर्ण_अगर /* #अगर_अघोषित __CSIO_HW_CHIP_H__ */
