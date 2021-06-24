<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * i.MX8QXP/i.MX8QM JPEG encoder/decoder v4l2 driver
 *
 * Copyright 2018-2019 NXP
 */

#समावेश <linux/delay.h>
#समावेश <media/videobuf2-core.h>
#समावेश "mxc-jpeg-hw.h"

#घोषणा prपूर्णांक_wrapper_reg(dev, base_address, reg_offset)\
		पूर्णांकernal_prपूर्णांक_wrapper_reg(dev, (base_address), #reg_offset,\
					   (reg_offset))
#घोषणा पूर्णांकernal_prपूर्णांक_wrapper_reg(dev, base_address, reg_name, reg_offset) अणु\
		पूर्णांक val;\
		val = पढ़ोl((base_address) + (reg_offset));\
		dev_dbg(dev, "Wrapper reg %s = 0x%x\n", reg_name, val);\
पूर्ण

व्योम prपूर्णांक_descriptor_info(काष्ठा device *dev, काष्ठा mxc_jpeg_desc *desc)
अणु
	dev_dbg(dev, " MXC JPEG NEXT_DESCPT_PTR 0x%x\n",
		desc->next_descpt_ptr);
	dev_dbg(dev, " MXC JPEG BUF_BASE0 0x%x\n", desc->buf_base0);
	dev_dbg(dev, " MXC JPEG BUF_BASE1 0x%x\n", desc->buf_base1);
	dev_dbg(dev, " MXC JPEG LINE_PITCH %d\n", desc->line_pitch);
	dev_dbg(dev, " MXC JPEG STM_BUFBASE 0x%x\n", desc->sपंचांग_bufbase);
	dev_dbg(dev, " MXC JPEG STM_BUFSIZE %d\n", desc->sपंचांग_bufsize);
	dev_dbg(dev, " MXC JPEG IMGSIZE %x (%d x %d)\n", desc->imgsize,
		desc->imgsize >> 16, desc->imgsize & 0xFFFF);
	dev_dbg(dev, " MXC JPEG STM_CTRL 0x%x\n", desc->sपंचांग_ctrl);
पूर्ण

व्योम prपूर्णांक_cast_status(काष्ठा device *dev, व्योम __iomem *reg,
		       अचिन्हित पूर्णांक mode)
अणु
	dev_dbg(dev, "CAST IP status regs:\n");
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS0);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS1);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS2);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS3);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS4);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS5);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS6);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS7);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS8);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS9);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS10);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS11);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS12);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS13);
	अगर (mode == MXC_JPEG_DECODE)
		वापस;
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS14);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS15);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS16);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS17);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS18);
	prपूर्णांक_wrapper_reg(dev, reg, CAST_STATUS19);
पूर्ण

व्योम prपूर्णांक_wrapper_info(काष्ठा device *dev, व्योम __iomem *reg)
अणु
	dev_dbg(dev, "Wrapper regs:\n");
	prपूर्णांक_wrapper_reg(dev, reg, GLB_CTRL);
	prपूर्णांक_wrapper_reg(dev, reg, COM_STATUS);
	prपूर्णांक_wrapper_reg(dev, reg, BUF_BASE0);
	prपूर्णांक_wrapper_reg(dev, reg, BUF_BASE1);
	prपूर्णांक_wrapper_reg(dev, reg, LINE_PITCH);
	prपूर्णांक_wrapper_reg(dev, reg, STM_BUFBASE);
	prपूर्णांक_wrapper_reg(dev, reg, STM_बफ_मानE);
	prपूर्णांक_wrapper_reg(dev, reg, IMGSIZE);
	prपूर्णांक_wrapper_reg(dev, reg, STM_CTRL);
पूर्ण

व्योम mxc_jpeg_enable_irq(व्योम __iomem *reg, पूर्णांक slot)
अणु
	ग_लिखोl(0xFFFFFFFF, reg + MXC_SLOT_OFFSET(slot, SLOT_IRQ_EN));
पूर्ण

व्योम mxc_jpeg_sw_reset(व्योम __iomem *reg)
अणु
	/*
	 * engine soft reset, पूर्णांकernal state machine reset
	 * this will not reset रेजिस्टरs, however, it seems
	 * the रेजिस्टरs may reमुख्य inconsistent with the पूर्णांकernal state
	 * so, on purpose, at least let GLB_CTRL bits clear after this reset
	 */
	ग_लिखोl(GLB_CTRL_SFT_RST, reg + GLB_CTRL);
पूर्ण

व्योम mxc_jpeg_enc_mode_conf(काष्ठा device *dev, व्योम __iomem *reg)
अणु
	dev_dbg(dev, "CAST Encoder CONFIG...\n");
	/*
	 * "Config_Mode" enabled, "Config_Mode auto clear enabled",
	 */
	ग_लिखोl(0xa0, reg + CAST_MODE);

	/* all markers and segments */
	ग_लिखोl(0x3ff, reg + CAST_CFG_MODE);

	/* quality factor */
	ग_लिखोl(0x4b, reg + CAST_QUALITY);
पूर्ण

व्योम mxc_jpeg_enc_mode_go(काष्ठा device *dev, व्योम __iomem *reg)
अणु
	dev_dbg(dev, "CAST Encoder GO...\n");
	/*
	 * "GO" enabled, "GO bit auto clear" enabled
	 */
	ग_लिखोl(0x140, reg + CAST_MODE);
पूर्ण

व्योम mxc_jpeg_dec_mode_go(काष्ठा device *dev, व्योम __iomem *reg)
अणु
	dev_dbg(dev, "CAST Decoder GO...\n");
	ग_लिखोl(MXC_DEC_EXIT_IDLE_MODE, reg + CAST_CTRL);
पूर्ण

पूर्णांक mxc_jpeg_enable(व्योम __iomem *reg)
अणु
	u32 regval;

	ग_लिखोl(GLB_CTRL_JPG_EN, reg + GLB_CTRL);
	regval = पढ़ोl(reg);
	वापस regval;
पूर्ण

व्योम mxc_jpeg_enable_slot(व्योम __iomem *reg, पूर्णांक slot)
अणु
	u32 regval;

	regval = पढ़ोl(reg + GLB_CTRL);
	ग_लिखोl(GLB_CTRL_SLOT_EN(slot) | regval, reg + GLB_CTRL);
पूर्ण

व्योम mxc_jpeg_set_l_endian(व्योम __iomem *reg, पूर्णांक le)
अणु
	u32 regval;

	regval = पढ़ोl(reg + GLB_CTRL);
	regval &= ~GLB_CTRL_L_ENDIAN(1); /* clear */
	ग_लिखोl(GLB_CTRL_L_ENDIAN(le) | regval, reg + GLB_CTRL); /* set */
पूर्ण

व्योम mxc_jpeg_set_bufsize(काष्ठा mxc_jpeg_desc *desc,  u32 bufsize)
अणु
	desc->sपंचांग_bufsize = bufsize;
पूर्ण

व्योम mxc_jpeg_set_res(काष्ठा mxc_jpeg_desc *desc, u16 w, u16 h)
अणु
	desc->imgsize = w << 16 | h;
पूर्ण

व्योम mxc_jpeg_set_line_pitch(काष्ठा mxc_jpeg_desc *desc, u32 line_pitch)
अणु
	desc->line_pitch = line_pitch;
पूर्ण

व्योम mxc_jpeg_set_desc(u32 desc, व्योम __iomem *reg, पूर्णांक slot)
अणु
	ग_लिखोl(desc | MXC_NXT_DESCPT_EN,
	       reg + MXC_SLOT_OFFSET(slot, SLOT_NXT_DESCPT_PTR));
पूर्ण
