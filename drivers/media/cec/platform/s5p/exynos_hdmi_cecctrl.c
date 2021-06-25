<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/media/platक्रमm/s5p-cec/exynos_hdmi_cecctrl.c
 *
 * Copyright (c) 2009, 2014 Samsung Electronics
 *		http://www.samsung.com/
 *
 * cec ftn file क्रम Samsung TVOUT driver
 */

#समावेश <linux/पन.स>
#समावेश <linux/device.h>

#समावेश "exynos_hdmi_cec.h"
#समावेश "regs-cec.h"

#घोषणा S5P_HDMI_FIN			24000000
#घोषणा CEC_DIV_RATIO			320000

#घोषणा CEC_MESSAGE_BROADCAST_MASK	0x0F
#घोषणा CEC_MESSAGE_BROADCAST		0x0F
#घोषणा CEC_FILTER_THRESHOLD		0x15

व्योम s5p_cec_set_भागider(काष्ठा s5p_cec_dev *cec)
अणु
	u32 भाग_ratio, भाग_val;
	अचिन्हित पूर्णांक reg;

	भाग_ratio  = S5P_HDMI_FIN / CEC_DIV_RATIO - 1;

	अगर (regmap_पढ़ो(cec->pmu, EXYNOS_HDMI_PHY_CONTROL, &reg)) अणु
		dev_err(cec->dev, "failed to read phy control\n");
		वापस;
	पूर्ण

	reg = (reg & ~(0x3FF << 16)) | (भाग_ratio << 16);

	अगर (regmap_ग_लिखो(cec->pmu, EXYNOS_HDMI_PHY_CONTROL, reg)) अणु
		dev_err(cec->dev, "failed to write phy control\n");
		वापस;
	पूर्ण

	भाग_val = CEC_DIV_RATIO * 0.00005 - 1;

	ग_लिखोb(0x0, cec->reg + S5P_CEC_DIVISOR_3);
	ग_लिखोb(0x0, cec->reg + S5P_CEC_DIVISOR_2);
	ग_लिखोb(0x0, cec->reg + S5P_CEC_DIVISOR_1);
	ग_लिखोb(भाग_val, cec->reg + S5P_CEC_DIVISOR_0);
पूर्ण

व्योम s5p_cec_enable_rx(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	reg = पढ़ोb(cec->reg + S5P_CEC_RX_CTRL);
	reg |= S5P_CEC_RX_CTRL_ENABLE;
	ग_लिखोb(reg, cec->reg + S5P_CEC_RX_CTRL);
पूर्ण

व्योम s5p_cec_mask_rx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	reg = पढ़ोb(cec->reg + S5P_CEC_IRQ_MASK);
	reg |= S5P_CEC_IRQ_RX_DONE;
	reg |= S5P_CEC_IRQ_RX_ERROR;
	ग_लिखोb(reg, cec->reg + S5P_CEC_IRQ_MASK);
पूर्ण

व्योम s5p_cec_unmask_rx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	reg = पढ़ोb(cec->reg + S5P_CEC_IRQ_MASK);
	reg &= ~S5P_CEC_IRQ_RX_DONE;
	reg &= ~S5P_CEC_IRQ_RX_ERROR;
	ग_लिखोb(reg, cec->reg + S5P_CEC_IRQ_MASK);
पूर्ण

व्योम s5p_cec_mask_tx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	reg = पढ़ोb(cec->reg + S5P_CEC_IRQ_MASK);
	reg |= S5P_CEC_IRQ_TX_DONE;
	reg |= S5P_CEC_IRQ_TX_ERROR;
	ग_लिखोb(reg, cec->reg + S5P_CEC_IRQ_MASK);
पूर्ण

व्योम s5p_cec_unmask_tx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	reg = पढ़ोb(cec->reg + S5P_CEC_IRQ_MASK);
	reg &= ~S5P_CEC_IRQ_TX_DONE;
	reg &= ~S5P_CEC_IRQ_TX_ERROR;
	ग_लिखोb(reg, cec->reg + S5P_CEC_IRQ_MASK);
पूर्ण

व्योम s5p_cec_reset(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	ग_लिखोb(S5P_CEC_RX_CTRL_RESET, cec->reg + S5P_CEC_RX_CTRL);
	ग_लिखोb(S5P_CEC_TX_CTRL_RESET, cec->reg + S5P_CEC_TX_CTRL);

	reg = पढ़ोb(cec->reg + 0xc4);
	reg &= ~0x1;
	ग_लिखोb(reg, cec->reg + 0xc4);
पूर्ण

व्योम s5p_cec_tx_reset(काष्ठा s5p_cec_dev *cec)
अणु
	ग_लिखोb(S5P_CEC_TX_CTRL_RESET, cec->reg + S5P_CEC_TX_CTRL);
पूर्ण

व्योम s5p_cec_rx_reset(काष्ठा s5p_cec_dev *cec)
अणु
	u8 reg;

	ग_लिखोb(S5P_CEC_RX_CTRL_RESET, cec->reg + S5P_CEC_RX_CTRL);

	reg = पढ़ोb(cec->reg + 0xc4);
	reg &= ~0x1;
	ग_लिखोb(reg, cec->reg + 0xc4);
पूर्ण

व्योम s5p_cec_threshold(काष्ठा s5p_cec_dev *cec)
अणु
	ग_लिखोb(CEC_FILTER_THRESHOLD, cec->reg + S5P_CEC_RX_FILTER_TH);
	ग_लिखोb(0, cec->reg + S5P_CEC_RX_FILTER_CTRL);
पूर्ण

व्योम s5p_cec_copy_packet(काष्ठा s5p_cec_dev *cec, अक्षर *data,
			 माप_प्रकार count, u8 retries)
अणु
	पूर्णांक i = 0;
	u8 reg;

	जबतक (i < count) अणु
		ग_लिखोb(data[i], cec->reg + (S5P_CEC_TX_BUFF0 + (i * 4)));
		i++;
	पूर्ण

	ग_लिखोb(count, cec->reg + S5P_CEC_TX_BYTES);
	reg = पढ़ोb(cec->reg + S5P_CEC_TX_CTRL);
	reg |= S5P_CEC_TX_CTRL_START;
	reg &= ~0x70;
	reg |= retries << 4;

	अगर ((data[0] & CEC_MESSAGE_BROADCAST_MASK) == CEC_MESSAGE_BROADCAST) अणु
		dev_dbg(cec->dev, "Broadcast");
		reg |= S5P_CEC_TX_CTRL_BCAST;
	पूर्ण अन्यथा अणु
		dev_dbg(cec->dev, "No Broadcast");
		reg &= ~S5P_CEC_TX_CTRL_BCAST;
	पूर्ण

	ग_लिखोb(reg, cec->reg + S5P_CEC_TX_CTRL);
	dev_dbg(cec->dev, "cec-tx: cec count (%zu): %*ph", count,
		(पूर्णांक)count, data);
पूर्ण

व्योम s5p_cec_set_addr(काष्ठा s5p_cec_dev *cec, u32 addr)
अणु
	ग_लिखोb(addr & 0x0F, cec->reg + S5P_CEC_LOGIC_ADDR);
पूर्ण

u32 s5p_cec_get_status(काष्ठा s5p_cec_dev *cec)
अणु
	u32 status = 0;

	status = पढ़ोb(cec->reg + S5P_CEC_STATUS_0) & 0xf;
	status |= (पढ़ोb(cec->reg + S5P_CEC_TX_STAT1) & 0xf) << 4;
	status |= पढ़ोb(cec->reg + S5P_CEC_STATUS_1) << 8;
	status |= पढ़ोb(cec->reg + S5P_CEC_STATUS_2) << 16;
	status |= पढ़ोb(cec->reg + S5P_CEC_STATUS_3) << 24;

	dev_dbg(cec->dev, "status = 0x%x!\n", status);

	वापस status;
पूर्ण

व्योम s5p_clr_pending_tx(काष्ठा s5p_cec_dev *cec)
अणु
	ग_लिखोb(S5P_CEC_IRQ_TX_DONE | S5P_CEC_IRQ_TX_ERROR,
	       cec->reg + S5P_CEC_IRQ_CLEAR);
पूर्ण

व्योम s5p_clr_pending_rx(काष्ठा s5p_cec_dev *cec)
अणु
	ग_लिखोb(S5P_CEC_IRQ_RX_DONE | S5P_CEC_IRQ_RX_ERROR,
	       cec->reg + S5P_CEC_IRQ_CLEAR);
पूर्ण

व्योम s5p_cec_get_rx_buf(काष्ठा s5p_cec_dev *cec, u32 size, u8 *buffer)
अणु
	u32 i = 0;
	अक्षर debug[40];

	जबतक (i < size) अणु
		buffer[i] = पढ़ोb(cec->reg + S5P_CEC_RX_BUFF0 + (i * 4));
		प्र_लिखो(debug + i * 2, "%02x ", buffer[i]);
		i++;
	पूर्ण
	dev_dbg(cec->dev, "cec-rx: cec size(%d): %s", size, debug);
पूर्ण
