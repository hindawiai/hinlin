<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ImgTec IR Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 */

#अगर_अघोषित _IMG_IR_H_
#घोषणा _IMG_IR_H_

#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश "img-ir-raw.h"
#समावेश "img-ir-hw.h"

/* रेजिस्टरs */

/* relative to the start of the IR block of रेजिस्टरs */
#घोषणा IMG_IR_CONTROL		0x00
#घोषणा IMG_IR_STATUS		0x04
#घोषणा IMG_IR_DATA_LW		0x08
#घोषणा IMG_IR_DATA_UP		0x0c
#घोषणा IMG_IR_LEAD_SYMB_TIMING	0x10
#घोषणा IMG_IR_S00_SYMB_TIMING	0x14
#घोषणा IMG_IR_S01_SYMB_TIMING	0x18
#घोषणा IMG_IR_S10_SYMB_TIMING	0x1c
#घोषणा IMG_IR_S11_SYMB_TIMING	0x20
#घोषणा IMG_IR_FREE_SYMB_TIMING	0x24
#घोषणा IMG_IR_POW_MOD_PARAMS	0x28
#घोषणा IMG_IR_POW_MOD_ENABLE	0x2c
#घोषणा IMG_IR_IRQ_MSG_DATA_LW	0x30
#घोषणा IMG_IR_IRQ_MSG_DATA_UP	0x34
#घोषणा IMG_IR_IRQ_MSG_MASK_LW	0x38
#घोषणा IMG_IR_IRQ_MSG_MASK_UP	0x3c
#घोषणा IMG_IR_IRQ_ENABLE	0x40
#घोषणा IMG_IR_IRQ_STATUS	0x44
#घोषणा IMG_IR_IRQ_CLEAR	0x48
#घोषणा IMG_IR_IRCORE_ID	0xf0
#घोषणा IMG_IR_CORE_REV		0xf4
#घोषणा IMG_IR_CORE_DES1	0xf8
#घोषणा IMG_IR_CORE_DES2	0xfc


/* field masks */

/* IMG_IR_CONTROL */
#घोषणा IMG_IR_DECODEN		0x40000000
#घोषणा IMG_IR_CODETYPE		0x30000000
#घोषणा IMG_IR_CODETYPE_SHIFT		28
#घोषणा IMG_IR_HDRTOG		0x08000000
#घोषणा IMG_IR_LDRDEC		0x04000000
#घोषणा IMG_IR_DECODINPOL	0x02000000	/* active high */
#घोषणा IMG_IR_BITORIEN		0x01000000	/* MSB first */
#घोषणा IMG_IR_D1VALIDSEL	0x00008000
#घोषणा IMG_IR_BITINV		0x00000040	/* करोn't invert */
#घोषणा IMG_IR_DECODEND2	0x00000010
#घोषणा IMG_IR_BITORIEND2	0x00000002	/* MSB first */
#घोषणा IMG_IR_BITINVD2		0x00000001	/* करोn't invert */

/* IMG_IR_STATUS */
#घोषणा IMG_IR_RXDVALD2		0x00001000
#घोषणा IMG_IR_IRRXD		0x00000400
#घोषणा IMG_IR_TOGSTATE		0x00000200
#घोषणा IMG_IR_RXDVAL		0x00000040
#घोषणा IMG_IR_RXDLEN		0x0000003f
#घोषणा IMG_IR_RXDLEN_SHIFT		0

/* IMG_IR_LEAD_SYMB_TIMING, IMG_IR_Sxx_SYMB_TIMING */
#घोषणा IMG_IR_PD_MAX		0xff000000
#घोषणा IMG_IR_PD_MAX_SHIFT		24
#घोषणा IMG_IR_PD_MIN		0x00ff0000
#घोषणा IMG_IR_PD_MIN_SHIFT		16
#घोषणा IMG_IR_W_MAX		0x0000ff00
#घोषणा IMG_IR_W_MAX_SHIFT		8
#घोषणा IMG_IR_W_MIN		0x000000ff
#घोषणा IMG_IR_W_MIN_SHIFT		0

/* IMG_IR_FREE_SYMB_TIMING */
#घोषणा IMG_IR_MAXLEN		0x0007e000
#घोषणा IMG_IR_MAXLEN_SHIFT		13
#घोषणा IMG_IR_MINLEN		0x00001f00
#घोषणा IMG_IR_MINLEN_SHIFT		8
#घोषणा IMG_IR_FT_MIN		0x000000ff
#घोषणा IMG_IR_FT_MIN_SHIFT		0

/* IMG_IR_POW_MOD_PARAMS */
#घोषणा IMG_IR_PERIOD_LEN	0x3f000000
#घोषणा IMG_IR_PERIOD_LEN_SHIFT		24
#घोषणा IMG_IR_PERIOD_DUTY	0x003f0000
#घोषणा IMG_IR_PERIOD_DUTY_SHIFT	16
#घोषणा IMG_IR_STABLE_STOP	0x00003f00
#घोषणा IMG_IR_STABLE_STOP_SHIFT	8
#घोषणा IMG_IR_STABLE_START	0x0000003f
#घोषणा IMG_IR_STABLE_START_SHIFT	0

/* IMG_IR_POW_MOD_ENABLE */
#घोषणा IMG_IR_POWER_OUT_EN	0x00000002
#घोषणा IMG_IR_POWER_MOD_EN	0x00000001

/* IMG_IR_IRQ_ENABLE, IMG_IR_IRQ_STATUS, IMG_IR_IRQ_CLEAR */
#घोषणा IMG_IR_IRQ_DEC2_ERR	0x00000080
#घोषणा IMG_IR_IRQ_DEC_ERR	0x00000040
#घोषणा IMG_IR_IRQ_ACT_LEVEL	0x00000020
#घोषणा IMG_IR_IRQ_FALL_EDGE	0x00000010
#घोषणा IMG_IR_IRQ_RISE_EDGE	0x00000008
#घोषणा IMG_IR_IRQ_DATA_MATCH	0x00000004
#घोषणा IMG_IR_IRQ_DATA2_VALID	0x00000002
#घोषणा IMG_IR_IRQ_DATA_VALID	0x00000001
#घोषणा IMG_IR_IRQ_ALL		0x000000ff
#घोषणा IMG_IR_IRQ_EDGE		(IMG_IR_IRQ_FALL_EDGE | IMG_IR_IRQ_RISE_EDGE)

/* IMG_IR_CORE_ID */
#घोषणा IMG_IR_CORE_ID		0x00ff0000
#घोषणा IMG_IR_CORE_ID_SHIFT		16
#घोषणा IMG_IR_CORE_CONFIG	0x0000ffff
#घोषणा IMG_IR_CORE_CONFIG_SHIFT	0

/* IMG_IR_CORE_REV */
#घोषणा IMG_IR_DESIGNER		0xff000000
#घोषणा IMG_IR_DESIGNER_SHIFT		24
#घोषणा IMG_IR_MAJOR_REV	0x00ff0000
#घोषणा IMG_IR_MAJOR_REV_SHIFT		16
#घोषणा IMG_IR_MINOR_REV	0x0000ff00
#घोषणा IMG_IR_MINOR_REV_SHIFT		8
#घोषणा IMG_IR_MAINT_REV	0x000000ff
#घोषणा IMG_IR_MAINT_REV_SHIFT		0

काष्ठा device;
काष्ठा clk;

/**
 * काष्ठा img_ir_priv - Private driver data.
 * @dev:		Platक्रमm device.
 * @irq:		IRQ number.
 * @clk:		Input घड़ी.
 * @sys_clk:		System घड़ी.
 * @reg_base:		Iomem base address of IR रेजिस्टर block.
 * @lock:		Protects IR रेजिस्टरs and variables in this काष्ठा.
 * @raw:		Driver data क्रम raw decoder.
 * @hw:			Driver data क्रम hardware decoder.
 */
काष्ठा img_ir_priv अणु
	काष्ठा device		*dev;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	काष्ठा clk		*sys_clk;
	व्योम __iomem		*reg_base;
	spinlock_t		lock;

	काष्ठा img_ir_priv_raw	raw;
	काष्ठा img_ir_priv_hw	hw;
पूर्ण;

/* Hardware access */

अटल अंतरभूत व्योम img_ir_ग_लिखो(काष्ठा img_ir_priv *priv,
				अचिन्हित पूर्णांक reg_offs, अचिन्हित पूर्णांक data)
अणु
	ioग_लिखो32(data, priv->reg_base + reg_offs);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक img_ir_पढ़ो(काष्ठा img_ir_priv *priv,
				       अचिन्हित पूर्णांक reg_offs)
अणु
	वापस ioपढ़ो32(priv->reg_base + reg_offs);
पूर्ण

#पूर्ण_अगर /* _IMG_IR_H_ */
