<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
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
 * Author: Stanislaw Skowronek
 */

#अगर_अघोषित ATOM_H
#घोषणा ATOM_H

#समावेश <linux/types.h>

काष्ठा drm_device;

#घोषणा ATOM_BIOS_MAGIC		0xAA55
#घोषणा ATOM_ATI_MAGIC_PTR	0x30
#घोषणा ATOM_ATI_MAGIC		" 761295520"
#घोषणा ATOM_ROM_TABLE_PTR	0x48
#घोषणा ATOM_ROM_PART_NUMBER_PTR	0x6E

#घोषणा ATOM_ROM_MAGIC		"ATOM"
#घोषणा ATOM_ROM_MAGIC_PTR	4

#घोषणा ATOM_ROM_MSG_PTR	0x10
#घोषणा ATOM_ROM_CMD_PTR	0x1E
#घोषणा ATOM_ROM_DATA_PTR	0x20

#घोषणा ATOM_CMD_INIT		0
#घोषणा ATOM_CMD_SETSCLK	0x0A
#घोषणा ATOM_CMD_SETMCLK	0x0B
#घोषणा ATOM_CMD_SETPCLK	0x0C
#घोषणा ATOM_CMD_SPDFANCNTL	0x39

#घोषणा ATOM_DATA_FWI_PTR	0xC
#घोषणा ATOM_DATA_IIO_PTR	0x32

#घोषणा ATOM_FWI_DEFSCLK_PTR	8
#घोषणा ATOM_FWI_DEFMCLK_PTR	0xC
#घोषणा ATOM_FWI_MAXSCLK_PTR	0x24
#घोषणा ATOM_FWI_MAXMCLK_PTR	0x28

#घोषणा ATOM_CT_SIZE_PTR	0
#घोषणा ATOM_CT_WS_PTR		4
#घोषणा ATOM_CT_PS_PTR		5
#घोषणा ATOM_CT_PS_MASK		0x7F
#घोषणा ATOM_CT_CODE_PTR	6

#घोषणा ATOM_OP_CNT		127
#घोषणा ATOM_OP_EOT		91

#घोषणा ATOM_CASE_MAGIC		0x63
#घोषणा ATOM_CASE_END		0x5A5A

#घोषणा ATOM_ARG_REG		0
#घोषणा ATOM_ARG_PS		1
#घोषणा ATOM_ARG_WS		2
#घोषणा ATOM_ARG_FB		3
#घोषणा ATOM_ARG_ID		4
#घोषणा ATOM_ARG_IMM		5
#घोषणा ATOM_ARG_PLL		6
#घोषणा ATOM_ARG_MC		7

#घोषणा ATOM_SRC_DWORD		0
#घोषणा ATOM_SRC_WORD0		1
#घोषणा ATOM_SRC_WORD8		2
#घोषणा ATOM_SRC_WORD16		3
#घोषणा ATOM_SRC_BYTE0		4
#घोषणा ATOM_SRC_BYTE8		5
#घोषणा ATOM_SRC_BYTE16		6
#घोषणा ATOM_SRC_BYTE24		7

#घोषणा ATOM_WS_QUOTIENT	0x40
#घोषणा ATOM_WS_REMAINDER	0x41
#घोषणा ATOM_WS_DATAPTR		0x42
#घोषणा ATOM_WS_SHIFT		0x43
#घोषणा ATOM_WS_OR_MASK		0x44
#घोषणा ATOM_WS_AND_MASK	0x45
#घोषणा ATOM_WS_FB_WINDOW	0x46
#घोषणा ATOM_WS_ATTRIBUTES	0x47
#घोषणा ATOM_WS_REGPTR		0x48

#घोषणा ATOM_IIO_NOP		0
#घोषणा ATOM_IIO_START		1
#घोषणा ATOM_IIO_READ		2
#घोषणा ATOM_IIO_WRITE		3
#घोषणा ATOM_IIO_CLEAR		4
#घोषणा ATOM_IIO_SET		5
#घोषणा ATOM_IIO_MOVE_INDEX	6
#घोषणा ATOM_IIO_MOVE_ATTR	7
#घोषणा ATOM_IIO_MOVE_DATA	8
#घोषणा ATOM_IIO_END		9

#घोषणा ATOM_IO_MM		0
#घोषणा ATOM_IO_PCI		1
#घोषणा ATOM_IO_SYSIO		2
#घोषणा ATOM_IO_IIO		0x80

काष्ठा card_info अणु
	काष्ठा drm_device *dev;
	व्योम (* reg_ग_लिखो)(काष्ठा card_info *, uपूर्णांक32_t, uपूर्णांक32_t);   /*  filled by driver */
	uपूर्णांक32_t (* reg_पढ़ो)(काष्ठा card_info *, uपूर्णांक32_t);          /*  filled by driver */
	व्योम (* mc_ग_लिखो)(काष्ठा card_info *, uपूर्णांक32_t, uपूर्णांक32_t);   /*  filled by driver */
	uपूर्णांक32_t (* mc_पढ़ो)(काष्ठा card_info *, uपूर्णांक32_t);          /*  filled by driver */
	व्योम (* pll_ग_लिखो)(काष्ठा card_info *, uपूर्णांक32_t, uपूर्णांक32_t);   /*  filled by driver */
	uपूर्णांक32_t (* pll_पढ़ो)(काष्ठा card_info *, uपूर्णांक32_t);          /*  filled by driver */
पूर्ण;

काष्ठा atom_context अणु
	काष्ठा card_info *card;
	काष्ठा mutex mutex;
	व्योम *bios;
	uपूर्णांक32_t cmd_table, data_table;
	uपूर्णांक16_t *iio;

	uपूर्णांक16_t data_block;
	uपूर्णांक32_t fb_base;
	uपूर्णांक32_t भागmul[2];
	uपूर्णांक16_t io_attr;
	uपूर्णांक16_t reg_block;
	uपूर्णांक8_t shअगरt;
	पूर्णांक cs_equal, cs_above;
	पूर्णांक io_mode;
	uपूर्णांक32_t *scratch;
	पूर्णांक scratch_size_bytes;
	अक्षर vbios_version[20];
पूर्ण;

बाह्य पूर्णांक amdgpu_atom_debug;

काष्ठा atom_context *amdgpu_atom_parse(काष्ठा card_info *, व्योम *);
पूर्णांक amdgpu_atom_execute_table(काष्ठा atom_context *, पूर्णांक, uपूर्णांक32_t *);
पूर्णांक amdgpu_atom_asic_init(काष्ठा atom_context *);
व्योम amdgpu_atom_destroy(काष्ठा atom_context *);
bool amdgpu_atom_parse_data_header(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक16_t *size,
			    uपूर्णांक8_t *frev, uपूर्णांक8_t *crev, uपूर्णांक16_t *data_start);
bool amdgpu_atom_parse_cmd_header(काष्ठा atom_context *ctx, पूर्णांक index,
			   uपूर्णांक8_t *frev, uपूर्णांक8_t *crev);
#समावेश "atom-types.h"
#समावेश "atombios.h"
#समावेश "ObjectID.h"

#पूर्ण_अगर
