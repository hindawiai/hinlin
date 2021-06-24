<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx XADC driver
 *
 * Copyright 2013-2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 *
 * Documentation क्रम the parts can be found at:
 *  - XADC hardmacro: Xilinx UG480
 *  - ZYNQ XADC पूर्णांकerface: Xilinx UG585
 *  - AXI XADC पूर्णांकerface: Xilinx PG019
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/overflow.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश "xilinx-xadc.h"

अटल स्थिर अचिन्हित पूर्णांक XADC_ZYNQ_UNMASK_TIMEOUT = 500;

/* ZYNQ रेजिस्टर definitions */
#घोषणा XADC_ZYNQ_REG_CFG	0x00
#घोषणा XADC_ZYNQ_REG_INTSTS	0x04
#घोषणा XADC_ZYNQ_REG_INTMSK	0x08
#घोषणा XADC_ZYNQ_REG_STATUS	0x0c
#घोषणा XADC_ZYNQ_REG_CFIFO	0x10
#घोषणा XADC_ZYNQ_REG_DFIFO	0x14
#घोषणा XADC_ZYNQ_REG_CTL		0x18

#घोषणा XADC_ZYNQ_CFG_ENABLE		BIT(31)
#घोषणा XADC_ZYNQ_CFG_CFIFOTH_MASK	(0xf << 20)
#घोषणा XADC_ZYNQ_CFG_CFIFOTH_OFFSET	20
#घोषणा XADC_ZYNQ_CFG_DFIFOTH_MASK	(0xf << 16)
#घोषणा XADC_ZYNQ_CFG_DFIFOTH_OFFSET	16
#घोषणा XADC_ZYNQ_CFG_WEDGE		BIT(13)
#घोषणा XADC_ZYNQ_CFG_REDGE		BIT(12)
#घोषणा XADC_ZYNQ_CFG_TCKRATE_MASK	(0x3 << 8)
#घोषणा XADC_ZYNQ_CFG_TCKRATE_DIV2	(0x0 << 8)
#घोषणा XADC_ZYNQ_CFG_TCKRATE_DIV4	(0x1 << 8)
#घोषणा XADC_ZYNQ_CFG_TCKRATE_DIV8	(0x2 << 8)
#घोषणा XADC_ZYNQ_CFG_TCKRATE_DIV16	(0x3 << 8)
#घोषणा XADC_ZYNQ_CFG_IGAP_MASK		0x1f
#घोषणा XADC_ZYNQ_CFG_IGAP(x)		(x)

#घोषणा XADC_ZYNQ_INT_CFIFO_LTH		BIT(9)
#घोषणा XADC_ZYNQ_INT_DFIFO_GTH		BIT(8)
#घोषणा XADC_ZYNQ_INT_ALARM_MASK	0xff
#घोषणा XADC_ZYNQ_INT_ALARM_OFFSET	0

#घोषणा XADC_ZYNQ_STATUS_CFIFO_LVL_MASK	(0xf << 16)
#घोषणा XADC_ZYNQ_STATUS_CFIFO_LVL_OFFSET	16
#घोषणा XADC_ZYNQ_STATUS_DFIFO_LVL_MASK	(0xf << 12)
#घोषणा XADC_ZYNQ_STATUS_DFIFO_LVL_OFFSET	12
#घोषणा XADC_ZYNQ_STATUS_CFIFOF		BIT(11)
#घोषणा XADC_ZYNQ_STATUS_CFIFOE		BIT(10)
#घोषणा XADC_ZYNQ_STATUS_DFIFOF		BIT(9)
#घोषणा XADC_ZYNQ_STATUS_DFIFOE		BIT(8)
#घोषणा XADC_ZYNQ_STATUS_OT		BIT(7)
#घोषणा XADC_ZYNQ_STATUS_ALM(x)		BIT(x)

#घोषणा XADC_ZYNQ_CTL_RESET		BIT(4)

#घोषणा XADC_ZYNQ_CMD_NOP		0x00
#घोषणा XADC_ZYNQ_CMD_READ		0x01
#घोषणा XADC_ZYNQ_CMD_WRITE		0x02

#घोषणा XADC_ZYNQ_CMD(cmd, addr, data) (((cmd) << 26) | ((addr) << 16) | (data))

/* AXI रेजिस्टर definitions */
#घोषणा XADC_AXI_REG_RESET		0x00
#घोषणा XADC_AXI_REG_STATUS		0x04
#घोषणा XADC_AXI_REG_ALARM_STATUS	0x08
#घोषणा XADC_AXI_REG_CONVST		0x0c
#घोषणा XADC_AXI_REG_XADC_RESET		0x10
#घोषणा XADC_AXI_REG_GIER		0x5c
#घोषणा XADC_AXI_REG_IPISR		0x60
#घोषणा XADC_AXI_REG_IPIER		0x68

/* 7 Series */
#घोषणा XADC_7S_AXI_ADC_REG_OFFSET	0x200

/* UltraScale */
#घोषणा XADC_US_AXI_ADC_REG_OFFSET	0x400

#घोषणा XADC_AXI_RESET_MAGIC		0xa
#घोषणा XADC_AXI_GIER_ENABLE		BIT(31)

#घोषणा XADC_AXI_INT_EOS		BIT(4)
#घोषणा XADC_AXI_INT_ALARM_MASK		0x3c0f

#घोषणा XADC_FLAGS_BUFFERED BIT(0)

/*
 * The XADC hardware supports a samplerate of up to 1MSPS. Unक्रमtunately it करोes
 * not have a hardware FIFO. Which means an पूर्णांकerrupt is generated क्रम each
 * conversion sequence. At 1MSPS sample rate the CPU in ZYNQ7000 is completely
 * overloaded by the पूर्णांकerrupts that it soft-lockups. For this reason the driver
 * limits the maximum samplerate 150kSPS. At this rate the CPU is fairly busy,
 * but still responsive.
 */
#घोषणा XADC_MAX_SAMPLERATE 150000

अटल व्योम xadc_ग_लिखो_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, xadc->base + reg);
पूर्ण

अटल व्योम xadc_पढ़ो_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक32_t *val)
अणु
	*val = पढ़ोl(xadc->base + reg);
पूर्ण

/*
 * The ZYNQ पूर्णांकerface uses two asynchronous FIFOs क्रम communication with the
 * XADC. Reads and ग_लिखोs to the XADC रेजिस्टर are perक्रमmed by submitting a
 * request to the command FIFO (CFIFO), once the request has been completed the
 * result can be पढ़ो from the data FIFO (DFIFO). The method currently used in
 * this driver is to submit the request क्रम a पढ़ो/ग_लिखो operation, then go to
 * sleep and रुको क्रम an पूर्णांकerrupt that संकेतs that a response is available in
 * the data FIFO.
 */

अटल व्योम xadc_zynq_ग_लिखो_fअगरo(काष्ठा xadc *xadc, uपूर्णांक32_t *cmd,
	अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CFIFO, cmd[i]);
पूर्ण

अटल व्योम xadc_zynq_drain_fअगरo(काष्ठा xadc *xadc)
अणु
	uपूर्णांक32_t status, पंचांगp;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_STATUS, &status);

	जबतक (!(status & XADC_ZYNQ_STATUS_DFIFOE)) अणु
		xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_DFIFO, &पंचांगp);
		xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_STATUS, &status);
	पूर्ण
पूर्ण

अटल व्योम xadc_zynq_update_पूर्णांकmsk(काष्ठा xadc *xadc, अचिन्हित पूर्णांक mask,
	अचिन्हित पूर्णांक val)
अणु
	xadc->zynq_पूर्णांकmask &= ~mask;
	xadc->zynq_पूर्णांकmask |= val;

	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTMSK,
		xadc->zynq_पूर्णांकmask | xadc->zynq_masked_alarm);
पूर्ण

अटल पूर्णांक xadc_zynq_ग_लिखो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	uपूर्णांक32_t cmd[1];
	uपूर्णांक32_t पंचांगp;
	पूर्णांक ret;

	spin_lock_irq(&xadc->lock);
	xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);

	reinit_completion(&xadc->completion);

	cmd[0] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_WRITE, reg, val);
	xadc_zynq_ग_लिखो_fअगरo(xadc, cmd, ARRAY_SIZE(cmd));
	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_CFG, &पंचांगp);
	पंचांगp &= ~XADC_ZYNQ_CFG_DFIFOTH_MASK;
	पंचांगp |= 0 << XADC_ZYNQ_CFG_DFIFOTH_OFFSET;
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CFG, पंचांगp);

	xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH, 0);
	spin_unlock_irq(&xadc->lock);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xadc->completion, HZ);
	अगर (ret == 0)
		ret = -EIO;
	अन्यथा
		ret = 0;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_DFIFO, &पंचांगp);

	वापस ret;
पूर्ण

अटल पूर्णांक xadc_zynq_पढ़ो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	uपूर्णांक32_t cmd[2];
	uपूर्णांक32_t resp, पंचांगp;
	पूर्णांक ret;

	cmd[0] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_READ, reg, 0);
	cmd[1] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_NOP, 0, 0);

	spin_lock_irq(&xadc->lock);
	xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
	xadc_zynq_drain_fअगरo(xadc);
	reinit_completion(&xadc->completion);

	xadc_zynq_ग_लिखो_fअगरo(xadc, cmd, ARRAY_SIZE(cmd));
	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_CFG, &पंचांगp);
	पंचांगp &= ~XADC_ZYNQ_CFG_DFIFOTH_MASK;
	पंचांगp |= 1 << XADC_ZYNQ_CFG_DFIFOTH_OFFSET;
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CFG, पंचांगp);

	xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH, 0);
	spin_unlock_irq(&xadc->lock);
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&xadc->completion, HZ);
	अगर (ret == 0)
		ret = -EIO;
	अगर (ret < 0)
		वापस ret;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_DFIFO, &resp);
	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_DFIFO, &resp);

	*val = resp & 0xffff;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक xadc_zynq_transक्रमm_alarm(अचिन्हित पूर्णांक alarm)
अणु
	वापस ((alarm & 0x80) >> 4) |
		((alarm & 0x78) << 1) |
		(alarm & 0x07);
पूर्ण

/*
 * The ZYNQ threshold पूर्णांकerrupts are level sensitive. Since we can't make the
 * threshold condition go way from within the पूर्णांकerrupt handler, this means as
 * soon as a threshold condition is present we would enter the पूर्णांकerrupt handler
 * again and again. To work around this we mask all active thresholds पूर्णांकerrupts
 * in the पूर्णांकerrupt handler and start a समयr. In this समयr we poll the
 * पूर्णांकerrupt status and only अगर the पूर्णांकerrupt is inactive we unmask it again.
 */
अटल व्योम xadc_zynq_unmask_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xadc *xadc = container_of(work, काष्ठा xadc, zynq_unmask_work.work);
	अचिन्हित पूर्णांक misc_sts, unmask;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_STATUS, &misc_sts);

	misc_sts &= XADC_ZYNQ_INT_ALARM_MASK;

	spin_lock_irq(&xadc->lock);

	/* Clear those bits which are not active anymore */
	unmask = (xadc->zynq_masked_alarm ^ misc_sts) & xadc->zynq_masked_alarm;
	xadc->zynq_masked_alarm &= misc_sts;

	/* Also clear those which are masked out anyway */
	xadc->zynq_masked_alarm &= ~xadc->zynq_पूर्णांकmask;

	/* Clear the पूर्णांकerrupts beक्रमe we unmask them */
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTSTS, unmask);

	xadc_zynq_update_पूर्णांकmsk(xadc, 0, 0);

	spin_unlock_irq(&xadc->lock);

	/* अगर still pending some alarm re-trigger the समयr */
	अगर (xadc->zynq_masked_alarm) अणु
		schedule_delayed_work(&xadc->zynq_unmask_work,
				msecs_to_jअगरfies(XADC_ZYNQ_UNMASK_TIMEOUT));
	पूर्ण

पूर्ण

अटल irqवापस_t xadc_zynq_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा iio_dev *indio_dev = devid;
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	uपूर्णांक32_t status;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_INTSTS, &status);

	status &= ~(xadc->zynq_पूर्णांकmask | xadc->zynq_masked_alarm);

	अगर (!status)
		वापस IRQ_NONE;

	spin_lock(&xadc->lock);

	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTSTS, status);

	अगर (status & XADC_ZYNQ_INT_DFIFO_GTH) अणु
		xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
		complete(&xadc->completion);
	पूर्ण

	status &= XADC_ZYNQ_INT_ALARM_MASK;
	अगर (status) अणु
		xadc->zynq_masked_alarm |= status;
		/*
		 * mask the current event पूर्णांकerrupt,
		 * unmask it when the पूर्णांकerrupt is no more active.
		 */
		xadc_zynq_update_पूर्णांकmsk(xadc, 0, 0);

		xadc_handle_events(indio_dev,
				xadc_zynq_transक्रमm_alarm(status));

		/* unmask the required पूर्णांकerrupts in समयr. */
		schedule_delayed_work(&xadc->zynq_unmask_work,
				msecs_to_jअगरfies(XADC_ZYNQ_UNMASK_TIMEOUT));
	पूर्ण
	spin_unlock(&xadc->lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा XADC_ZYNQ_TCK_RATE_MAX 50000000
#घोषणा XADC_ZYNQ_IGAP_DEFAULT 20
#घोषणा XADC_ZYNQ_PCAP_RATE_MAX 200000000

अटल पूर्णांक xadc_zynq_setup(काष्ठा platक्रमm_device *pdev,
	काष्ठा iio_dev *indio_dev, पूर्णांक irq)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	अचिन्हित दीर्घ pcap_rate;
	अचिन्हित पूर्णांक tck_भाग;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक igap;
	अचिन्हित पूर्णांक tck_rate;
	पूर्णांक ret;

	/* TODO: Figure out how to make igap and tck_rate configurable */
	igap = XADC_ZYNQ_IGAP_DEFAULT;
	tck_rate = XADC_ZYNQ_TCK_RATE_MAX;

	xadc->zynq_पूर्णांकmask = ~0;

	pcap_rate = clk_get_rate(xadc->clk);
	अगर (!pcap_rate)
		वापस -EINVAL;

	अगर (pcap_rate > XADC_ZYNQ_PCAP_RATE_MAX) अणु
		ret = clk_set_rate(xadc->clk,
				   (अचिन्हित दीर्घ)XADC_ZYNQ_PCAP_RATE_MAX);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tck_rate > pcap_rate / 2) अणु
		भाग = 2;
	पूर्ण अन्यथा अणु
		भाग = pcap_rate / tck_rate;
		अगर (pcap_rate / भाग > XADC_ZYNQ_TCK_RATE_MAX)
			भाग++;
	पूर्ण

	अगर (भाग <= 3)
		tck_भाग = XADC_ZYNQ_CFG_TCKRATE_DIV2;
	अन्यथा अगर (भाग <= 7)
		tck_भाग = XADC_ZYNQ_CFG_TCKRATE_DIV4;
	अन्यथा अगर (भाग <= 15)
		tck_भाग = XADC_ZYNQ_CFG_TCKRATE_DIV8;
	अन्यथा
		tck_भाग = XADC_ZYNQ_CFG_TCKRATE_DIV16;

	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CTL, XADC_ZYNQ_CTL_RESET);
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CTL, 0);
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTSTS, ~0);
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTMSK, xadc->zynq_पूर्णांकmask);
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_CFG, XADC_ZYNQ_CFG_ENABLE |
			XADC_ZYNQ_CFG_REDGE | XADC_ZYNQ_CFG_WEDGE |
			tck_भाग | XADC_ZYNQ_CFG_IGAP(igap));

	अगर (pcap_rate > XADC_ZYNQ_PCAP_RATE_MAX) अणु
		ret = clk_set_rate(xadc->clk, pcap_rate);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ xadc_zynq_get_dclk_rate(काष्ठा xadc *xadc)
अणु
	अचिन्हित पूर्णांक भाग;
	uपूर्णांक32_t val;

	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_CFG, &val);

	चयन (val & XADC_ZYNQ_CFG_TCKRATE_MASK) अणु
	हाल XADC_ZYNQ_CFG_TCKRATE_DIV4:
		भाग = 4;
		अवरोध;
	हाल XADC_ZYNQ_CFG_TCKRATE_DIV8:
		भाग = 8;
		अवरोध;
	हाल XADC_ZYNQ_CFG_TCKRATE_DIV16:
		भाग = 16;
		अवरोध;
	शेष:
		भाग = 2;
		अवरोध;
	पूर्ण

	वापस clk_get_rate(xadc->clk) / भाग;
पूर्ण

अटल व्योम xadc_zynq_update_alarm(काष्ठा xadc *xadc, अचिन्हित पूर्णांक alarm)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t status;

	/* Move OT to bit 7 */
	alarm = ((alarm & 0x08) << 4) | ((alarm & 0xf0) >> 1) | (alarm & 0x07);

	spin_lock_irqsave(&xadc->lock, flags);

	/* Clear previous पूर्णांकerrupts अगर any. */
	xadc_पढ़ो_reg(xadc, XADC_ZYNQ_REG_INTSTS, &status);
	xadc_ग_लिखो_reg(xadc, XADC_ZYNQ_REG_INTSTS, status & alarm);

	xadc_zynq_update_पूर्णांकmsk(xadc, XADC_ZYNQ_INT_ALARM_MASK,
		~alarm & XADC_ZYNQ_INT_ALARM_MASK);

	spin_unlock_irqrestore(&xadc->lock, flags);
पूर्ण

अटल स्थिर काष्ठा xadc_ops xadc_zynq_ops = अणु
	.पढ़ो = xadc_zynq_पढ़ो_adc_reg,
	.ग_लिखो = xadc_zynq_ग_लिखो_adc_reg,
	.setup = xadc_zynq_setup,
	.get_dclk_rate = xadc_zynq_get_dclk_rate,
	.पूर्णांकerrupt_handler = xadc_zynq_पूर्णांकerrupt_handler,
	.update_alarm = xadc_zynq_update_alarm,
	.type = XADC_TYPE_S7,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक xadc_axi_reg_offsets[] = अणु
	[XADC_TYPE_S7] = XADC_7S_AXI_ADC_REG_OFFSET,
	[XADC_TYPE_US] = XADC_US_AXI_ADC_REG_OFFSET,
पूर्ण;

अटल पूर्णांक xadc_axi_पढ़ो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	uपूर्णांक32_t val32;

	xadc_पढ़ो_reg(xadc, xadc_axi_reg_offsets[xadc->ops->type] + reg * 4,
		&val32);
	*val = val32 & 0xffff;

	वापस 0;
पूर्ण

अटल पूर्णांक xadc_axi_ग_लिखो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	xadc_ग_लिखो_reg(xadc, xadc_axi_reg_offsets[xadc->ops->type] + reg * 4,
		val);

	वापस 0;
पूर्ण

अटल पूर्णांक xadc_axi_setup(काष्ठा platक्रमm_device *pdev,
	काष्ठा iio_dev *indio_dev, पूर्णांक irq)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);

	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_RESET, XADC_AXI_RESET_MAGIC);
	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_GIER, XADC_AXI_GIER_ENABLE);

	वापस 0;
पूर्ण

अटल irqवापस_t xadc_axi_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा iio_dev *indio_dev = devid;
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	uपूर्णांक32_t status, mask;
	अचिन्हित पूर्णांक events;

	xadc_पढ़ो_reg(xadc, XADC_AXI_REG_IPISR, &status);
	xadc_पढ़ो_reg(xadc, XADC_AXI_REG_IPIER, &mask);
	status &= mask;

	अगर (!status)
		वापस IRQ_NONE;

	अगर ((status & XADC_AXI_INT_EOS) && xadc->trigger)
		iio_trigger_poll(xadc->trigger);

	अगर (status & XADC_AXI_INT_ALARM_MASK) अणु
		/*
		 * The order of the bits in the AXI-XADC status रेजिस्टर करोes
		 * not match the order of the bits in the XADC alarm enable
		 * रेजिस्टर. xadc_handle_events() expects the events to be in
		 * the same order as the XADC alarm enable रेजिस्टर.
		 */
		events = (status & 0x000e) >> 1;
		events |= (status & 0x0001) << 3;
		events |= (status & 0x3c00) >> 6;
		xadc_handle_events(indio_dev, events);
	पूर्ण

	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_IPISR, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xadc_axi_update_alarm(काष्ठा xadc *xadc, अचिन्हित पूर्णांक alarm)
अणु
	uपूर्णांक32_t val;
	अचिन्हित दीर्घ flags;

	/*
	 * The order of the bits in the AXI-XADC status रेजिस्टर करोes not match
	 * the order of the bits in the XADC alarm enable रेजिस्टर. We get
	 * passed the alarm mask in the same order as in the XADC alarm enable
	 * रेजिस्टर.
	 */
	alarm = ((alarm & 0x07) << 1) | ((alarm & 0x08) >> 3) |
			((alarm & 0xf0) << 6);

	spin_lock_irqsave(&xadc->lock, flags);
	xadc_पढ़ो_reg(xadc, XADC_AXI_REG_IPIER, &val);
	val &= ~XADC_AXI_INT_ALARM_MASK;
	val |= alarm;
	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_IPIER, val);
	spin_unlock_irqrestore(&xadc->lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ xadc_axi_get_dclk(काष्ठा xadc *xadc)
अणु
	वापस clk_get_rate(xadc->clk);
पूर्ण

अटल स्थिर काष्ठा xadc_ops xadc_7s_axi_ops = अणु
	.पढ़ो = xadc_axi_पढ़ो_adc_reg,
	.ग_लिखो = xadc_axi_ग_लिखो_adc_reg,
	.setup = xadc_axi_setup,
	.get_dclk_rate = xadc_axi_get_dclk,
	.update_alarm = xadc_axi_update_alarm,
	.पूर्णांकerrupt_handler = xadc_axi_पूर्णांकerrupt_handler,
	.flags = XADC_FLAGS_BUFFERED,
	.type = XADC_TYPE_S7,
पूर्ण;

अटल स्थिर काष्ठा xadc_ops xadc_us_axi_ops = अणु
	.पढ़ो = xadc_axi_पढ़ो_adc_reg,
	.ग_लिखो = xadc_axi_ग_लिखो_adc_reg,
	.setup = xadc_axi_setup,
	.get_dclk_rate = xadc_axi_get_dclk,
	.update_alarm = xadc_axi_update_alarm,
	.पूर्णांकerrupt_handler = xadc_axi_पूर्णांकerrupt_handler,
	.flags = XADC_FLAGS_BUFFERED,
	.type = XADC_TYPE_US,
पूर्ण;

अटल पूर्णांक _xadc_update_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t mask, uपूर्णांक16_t val)
अणु
	uपूर्णांक16_t पंचांगp;
	पूर्णांक ret;

	ret = _xadc_पढ़ो_adc_reg(xadc, reg, &पंचांगp);
	अगर (ret)
		वापस ret;

	वापस _xadc_ग_लिखो_adc_reg(xadc, reg, (पंचांगp & ~mask) | val);
पूर्ण

अटल पूर्णांक xadc_update_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t mask, uपूर्णांक16_t val)
अणु
	पूर्णांक ret;

	mutex_lock(&xadc->mutex);
	ret = _xadc_update_adc_reg(xadc, reg, mask, val);
	mutex_unlock(&xadc->mutex);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ xadc_get_dclk_rate(काष्ठा xadc *xadc)
अणु
	वापस xadc->ops->get_dclk_rate(xadc);
पूर्ण

अटल पूर्णांक xadc_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *mask)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	माप_प्रकार new_size, n;
	व्योम *data;

	n = biपंचांगap_weight(mask, indio_dev->masklength);

	अगर (check_mul_overflow(n, माप(*xadc->data), &new_size))
		वापस -ENOMEM;

	data = devm_kपुनः_स्मृति(indio_dev->dev.parent, xadc->data,
			     new_size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	स_रखो(data, 0, new_size);
	xadc->data = data;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक xadc_scan_index_to_channel(अचिन्हित पूर्णांक scan_index)
अणु
	चयन (scan_index) अणु
	हाल 5:
		वापस XADC_REG_VCCPINT;
	हाल 6:
		वापस XADC_REG_VCCPAUX;
	हाल 7:
		वापस XADC_REG_VCCO_DDR;
	हाल 8:
		वापस XADC_REG_TEMP;
	हाल 9:
		वापस XADC_REG_VCCINT;
	हाल 10:
		वापस XADC_REG_VCCAUX;
	हाल 11:
		वापस XADC_REG_VPVN;
	हाल 12:
		वापस XADC_REG_VREFP;
	हाल 13:
		वापस XADC_REG_VREFN;
	हाल 14:
		वापस XADC_REG_VCCBRAM;
	शेष:
		वापस XADC_REG_VAUX(scan_index - 16);
	पूर्ण
पूर्ण

अटल irqवापस_t xadc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक chan;
	पूर्णांक i, j;

	अगर (!xadc->data)
		जाओ out;

	j = 0;
	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		chan = xadc_scan_index_to_channel(i);
		xadc_पढ़ो_adc_reg(xadc, chan, &xadc->data[j]);
		j++;
	पूर्ण

	iio_push_to_buffers(indio_dev, xadc->data);

out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xadc_trigger_set_state(काष्ठा iio_trigger *trigger, bool state)
अणु
	काष्ठा xadc *xadc = iio_trigger_get_drvdata(trigger);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक convst;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;

	mutex_lock(&xadc->mutex);

	अगर (state) अणु
		/* Only one of the two triggers can be active at a समय. */
		अगर (xadc->trigger != शून्य) अणु
			ret = -EBUSY;
			जाओ err_out;
		पूर्ण अन्यथा अणु
			xadc->trigger = trigger;
			अगर (trigger == xadc->convst_trigger)
				convst = XADC_CONF0_EC;
			अन्यथा
				convst = 0;
		पूर्ण
		ret = _xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF0_EC,
					convst);
		अगर (ret)
			जाओ err_out;
	पूर्ण अन्यथा अणु
		xadc->trigger = शून्य;
	पूर्ण

	spin_lock_irqsave(&xadc->lock, flags);
	xadc_पढ़ो_reg(xadc, XADC_AXI_REG_IPIER, &val);
	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_IPISR, XADC_AXI_INT_EOS);
	अगर (state)
		val |= XADC_AXI_INT_EOS;
	अन्यथा
		val &= ~XADC_AXI_INT_EOS;
	xadc_ग_लिखो_reg(xadc, XADC_AXI_REG_IPIER, val);
	spin_unlock_irqrestore(&xadc->lock, flags);

err_out:
	mutex_unlock(&xadc->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops xadc_trigger_ops = अणु
	.set_trigger_state = &xadc_trigger_set_state,
पूर्ण;

अटल काष्ठा iio_trigger *xadc_alloc_trigger(काष्ठा iio_dev *indio_dev,
	स्थिर अक्षर *name)
अणु
	काष्ठा device *dev = indio_dev->dev.parent;
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(dev, "%s%d-%s", indio_dev->name,
				      indio_dev->id, name);
	अगर (trig == शून्य)
		वापस ERR_PTR(-ENOMEM);

	trig->ops = &xadc_trigger_ops;
	iio_trigger_set_drvdata(trig, iio_priv(indio_dev));

	ret = devm_iio_trigger_रेजिस्टर(dev, trig);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस trig;
पूर्ण

अटल पूर्णांक xadc_घातer_adc_b(काष्ठा xadc *xadc, अचिन्हित पूर्णांक seq_mode)
अणु
	uपूर्णांक16_t val;

	/*
	 * As per datasheet the घातer-करोwn bits are करोn't care in the
	 * UltraScale, but as per reality setting the घातer-करोwn bit क्रम the
	 * non-existing ADC-B घातers करोwn the मुख्य ADC, so just वापस and करोn't
	 * करो anything.
	 */
	अगर (xadc->ops->type == XADC_TYPE_US)
		वापस 0;

	/* Powerकरोwn the ADC-B when it is not needed. */
	चयन (seq_mode) अणु
	हाल XADC_CONF1_SEQ_SIMULTANEOUS:
	हाल XADC_CONF1_SEQ_INDEPENDENT:
		val = 0;
		अवरोध;
	शेष:
		val = XADC_CONF2_PD_ADC_B;
		अवरोध;
	पूर्ण

	वापस xadc_update_adc_reg(xadc, XADC_REG_CONF2, XADC_CONF2_PD_MASK,
		val);
पूर्ण

अटल पूर्णांक xadc_get_seq_mode(काष्ठा xadc *xadc, अचिन्हित दीर्घ scan_mode)
अणु
	अचिन्हित पूर्णांक aux_scan_mode = scan_mode >> 16;

	/* UltraScale has only one ADC and supports only continuous mode */
	अगर (xadc->ops->type == XADC_TYPE_US)
		वापस XADC_CONF1_SEQ_CONTINUOUS;

	अगर (xadc->बाह्यal_mux_mode == XADC_EXTERNAL_MUX_DUAL)
		वापस XADC_CONF1_SEQ_SIMULTANEOUS;

	अगर ((aux_scan_mode & 0xff00) == 0 ||
		(aux_scan_mode & 0x00ff) == 0)
		वापस XADC_CONF1_SEQ_CONTINUOUS;

	वापस XADC_CONF1_SEQ_SIMULTANEOUS;
पूर्ण

अटल पूर्णांक xadc_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	अचिन्हित दीर्घ scan_mask;
	पूर्णांक ret;
	पूर्णांक i;

	scan_mask = 1; /* Run calibration as part of the sequence */
	क्रम (i = 0; i < indio_dev->num_channels; i++)
		scan_mask |= BIT(indio_dev->channels[i].scan_index);

	/* Enable all channels and calibration */
	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_SEQ(0), scan_mask & 0xffff);
	अगर (ret)
		वापस ret;

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_SEQ(1), scan_mask >> 16);
	अगर (ret)
		वापस ret;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_CONTINUOUS);
	अगर (ret)
		वापस ret;

	वापस xadc_घातer_adc_b(xadc, XADC_CONF1_SEQ_CONTINUOUS);
पूर्ण

अटल पूर्णांक xadc_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	अचिन्हित दीर्घ scan_mask;
	पूर्णांक seq_mode;
	पूर्णांक ret;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_DEFAULT);
	अगर (ret)
		जाओ err;

	scan_mask = *indio_dev->active_scan_mask;
	seq_mode = xadc_get_seq_mode(xadc, scan_mask);

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_SEQ(0), scan_mask & 0xffff);
	अगर (ret)
		जाओ err;

	/*
	 * In simultaneous mode the upper and lower aux channels are samples at
	 * the same समय. In this mode the upper 8 bits in the sequencer
	 * रेजिस्टर are करोn't care and the lower 8 bits control two channels
	 * each. As such we must set the bit अगर either the channel in the lower
	 * group or the upper group is enabled.
	 */
	अगर (seq_mode == XADC_CONF1_SEQ_SIMULTANEOUS)
		scan_mask = ((scan_mask >> 8) | scan_mask) & 0xff0000;

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_SEQ(1), scan_mask >> 16);
	अगर (ret)
		जाओ err;

	ret = xadc_घातer_adc_b(xadc, seq_mode);
	अगर (ret)
		जाओ err;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		seq_mode);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	xadc_postdisable(indio_dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops xadc_buffer_ops = अणु
	.preenable = &xadc_preenable,
	.postdisable = &xadc_postdisable,
पूर्ण;

अटल पूर्णांक xadc_पढ़ो_samplerate(काष्ठा xadc *xadc)
अणु
	अचिन्हित पूर्णांक भाग;
	uपूर्णांक16_t val16;
	पूर्णांक ret;

	ret = xadc_पढ़ो_adc_reg(xadc, XADC_REG_CONF2, &val16);
	अगर (ret)
		वापस ret;

	भाग = (val16 & XADC_CONF2_DIV_MASK) >> XADC_CONF2_DIV_OFFSET;
	अगर (भाग < 2)
		भाग = 2;

	वापस xadc_get_dclk_rate(xadc) / भाग / 26;
पूर्ण

अटल पूर्णांक xadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक bits = chan->scan_type.realbits;
	uपूर्णांक16_t val16;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;
		ret = xadc_पढ़ो_adc_reg(xadc, chan->address, &val16);
		अगर (ret < 0)
			वापस ret;

		val16 >>= chan->scan_type.shअगरt;
		अगर (chan->scan_type.sign == 'u')
			*val = val16;
		अन्यथा
			*val = sign_extend32(val16, bits - 1);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			/* V = (val * 3.0) / 2**bits */
			चयन (chan->address) अणु
			हाल XADC_REG_VCCINT:
			हाल XADC_REG_VCCAUX:
			हाल XADC_REG_VREFP:
			हाल XADC_REG_VREFN:
			हाल XADC_REG_VCCBRAM:
			हाल XADC_REG_VCCPINT:
			हाल XADC_REG_VCCPAUX:
			हाल XADC_REG_VCCO_DDR:
				*val = 3000;
				अवरोध;
			शेष:
				*val = 1000;
				अवरोध;
			पूर्ण
			*val2 = chan->scan_type.realbits;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		हाल IIO_TEMP:
			/* Temp in C = (val * 503.975) / 2**bits - 273.15 */
			*val = 503975;
			*val2 = bits;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		/* Only the temperature channel has an offset */
		*val = -((273150 << bits) / 503975);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = xadc_पढ़ो_samplerate(xadc);
		अगर (ret < 0)
			वापस ret;

		*val = ret;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक xadc_ग_लिखो_samplerate(काष्ठा xadc *xadc, पूर्णांक val)
अणु
	अचिन्हित दीर्घ clk_rate = xadc_get_dclk_rate(xadc);
	अचिन्हित पूर्णांक भाग;

	अगर (!clk_rate)
		वापस -EINVAL;

	अगर (val <= 0)
		वापस -EINVAL;

	/* Max. 150 kSPS */
	अगर (val > XADC_MAX_SAMPLERATE)
		val = XADC_MAX_SAMPLERATE;

	val *= 26;

	/* Min 1MHz */
	अगर (val < 1000000)
		val = 1000000;

	/*
	 * We want to round करोwn, but only अगर we करो not exceed the 150 kSPS
	 * limit.
	 */
	भाग = clk_rate / val;
	अगर (clk_rate / भाग / 26 > XADC_MAX_SAMPLERATE)
		भाग++;
	अगर (भाग < 2)
		भाग = 2;
	अन्यथा अगर (भाग > 0xff)
		भाग = 0xff;

	वापस xadc_update_adc_reg(xadc, XADC_REG_CONF2, XADC_CONF2_DIV_MASK,
		भाग << XADC_CONF2_DIV_OFFSET);
पूर्ण

अटल पूर्णांक xadc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);

	अगर (info != IIO_CHAN_INFO_SAMP_FREQ)
		वापस -EINVAL;

	वापस xadc_ग_लिखो_samplerate(xadc, val);
पूर्ण

अटल स्थिर काष्ठा iio_event_spec xadc_temp_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				BIT(IIO_EV_INFO_VALUE) |
				BIT(IIO_EV_INFO_HYSTERESIS),
	पूर्ण,
पूर्ण;

/* Separate values क्रम upper and lower thresholds, but only a shared enabled */
अटल स्थिर काष्ठा iio_event_spec xadc_voltage_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

#घोषणा XADC_CHAN_TEMP(_chan, _scan_index, _addr, _bits) अणु \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channel = (_chan), \
	.address = (_addr), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_OFFSET), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.event_spec = xadc_temp_events, \
	.num_event_specs = ARRAY_SIZE(xadc_temp_events), \
	.scan_index = (_scan_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (_bits), \
		.storagebits = 16, \
		.shअगरt = 16 - (_bits), \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

#घोषणा XADC_CHAN_VOLTAGE(_chan, _scan_index, _addr, _bits, _ext, _alarm) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (_chan), \
	.address = (_addr), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.event_spec = (_alarm) ? xadc_voltage_events : शून्य, \
	.num_event_specs = (_alarm) ? ARRAY_SIZE(xadc_voltage_events) : 0, \
	.scan_index = (_scan_index), \
	.scan_type = अणु \
		.sign = ((_addr) == XADC_REG_VREFN) ? 's' : 'u', \
		.realbits = (_bits), \
		.storagebits = 16, \
		.shअगरt = 16 - (_bits), \
		.endianness = IIO_CPU, \
	पूर्ण, \
	.extend_name = _ext, \
पूर्ण

/* 7 Series */
#घोषणा XADC_7S_CHAN_TEMP(_chan, _scan_index, _addr) \
	XADC_CHAN_TEMP(_chan, _scan_index, _addr, 12)
#घोषणा XADC_7S_CHAN_VOLTAGE(_chan, _scan_index, _addr, _ext, _alarm) \
	XADC_CHAN_VOLTAGE(_chan, _scan_index, _addr, 12, _ext, _alarm)

अटल स्थिर काष्ठा iio_chan_spec xadc_7s_channels[] = अणु
	XADC_7S_CHAN_TEMP(0, 8, XADC_REG_TEMP),
	XADC_7S_CHAN_VOLTAGE(0, 9, XADC_REG_VCCINT, "vccint", true),
	XADC_7S_CHAN_VOLTAGE(1, 10, XADC_REG_VCCAUX, "vccaux", true),
	XADC_7S_CHAN_VOLTAGE(2, 14, XADC_REG_VCCBRAM, "vccbram", true),
	XADC_7S_CHAN_VOLTAGE(3, 5, XADC_REG_VCCPINT, "vccpint", true),
	XADC_7S_CHAN_VOLTAGE(4, 6, XADC_REG_VCCPAUX, "vccpaux", true),
	XADC_7S_CHAN_VOLTAGE(5, 7, XADC_REG_VCCO_DDR, "vccoddr", true),
	XADC_7S_CHAN_VOLTAGE(6, 12, XADC_REG_VREFP, "vrefp", false),
	XADC_7S_CHAN_VOLTAGE(7, 13, XADC_REG_VREFN, "vrefn", false),
	XADC_7S_CHAN_VOLTAGE(8, 11, XADC_REG_VPVN, शून्य, false),
	XADC_7S_CHAN_VOLTAGE(9, 16, XADC_REG_VAUX(0), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(10, 17, XADC_REG_VAUX(1), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(11, 18, XADC_REG_VAUX(2), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(12, 19, XADC_REG_VAUX(3), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(13, 20, XADC_REG_VAUX(4), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(14, 21, XADC_REG_VAUX(5), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(15, 22, XADC_REG_VAUX(6), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(16, 23, XADC_REG_VAUX(7), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(17, 24, XADC_REG_VAUX(8), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(18, 25, XADC_REG_VAUX(9), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(19, 26, XADC_REG_VAUX(10), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(20, 27, XADC_REG_VAUX(11), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(21, 28, XADC_REG_VAUX(12), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(22, 29, XADC_REG_VAUX(13), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(23, 30, XADC_REG_VAUX(14), शून्य, false),
	XADC_7S_CHAN_VOLTAGE(24, 31, XADC_REG_VAUX(15), शून्य, false),
पूर्ण;

/* UltraScale */
#घोषणा XADC_US_CHAN_TEMP(_chan, _scan_index, _addr) \
	XADC_CHAN_TEMP(_chan, _scan_index, _addr, 10)
#घोषणा XADC_US_CHAN_VOLTAGE(_chan, _scan_index, _addr, _ext, _alarm) \
	XADC_CHAN_VOLTAGE(_chan, _scan_index, _addr, 10, _ext, _alarm)

अटल स्थिर काष्ठा iio_chan_spec xadc_us_channels[] = अणु
	XADC_US_CHAN_TEMP(0, 8, XADC_REG_TEMP),
	XADC_US_CHAN_VOLTAGE(0, 9, XADC_REG_VCCINT, "vccint", true),
	XADC_US_CHAN_VOLTAGE(1, 10, XADC_REG_VCCAUX, "vccaux", true),
	XADC_US_CHAN_VOLTAGE(2, 14, XADC_REG_VCCBRAM, "vccbram", true),
	XADC_US_CHAN_VOLTAGE(3, 5, XADC_REG_VCCPINT, "vccpsintlp", true),
	XADC_US_CHAN_VOLTAGE(4, 6, XADC_REG_VCCPAUX, "vccpsintfp", true),
	XADC_US_CHAN_VOLTAGE(5, 7, XADC_REG_VCCO_DDR, "vccpsaux", true),
	XADC_US_CHAN_VOLTAGE(6, 12, XADC_REG_VREFP, "vrefp", false),
	XADC_US_CHAN_VOLTAGE(7, 13, XADC_REG_VREFN, "vrefn", false),
	XADC_US_CHAN_VOLTAGE(8, 11, XADC_REG_VPVN, शून्य, false),
	XADC_US_CHAN_VOLTAGE(9, 16, XADC_REG_VAUX(0), शून्य, false),
	XADC_US_CHAN_VOLTAGE(10, 17, XADC_REG_VAUX(1), शून्य, false),
	XADC_US_CHAN_VOLTAGE(11, 18, XADC_REG_VAUX(2), शून्य, false),
	XADC_US_CHAN_VOLTAGE(12, 19, XADC_REG_VAUX(3), शून्य, false),
	XADC_US_CHAN_VOLTAGE(13, 20, XADC_REG_VAUX(4), शून्य, false),
	XADC_US_CHAN_VOLTAGE(14, 21, XADC_REG_VAUX(5), शून्य, false),
	XADC_US_CHAN_VOLTAGE(15, 22, XADC_REG_VAUX(6), शून्य, false),
	XADC_US_CHAN_VOLTAGE(16, 23, XADC_REG_VAUX(7), शून्य, false),
	XADC_US_CHAN_VOLTAGE(17, 24, XADC_REG_VAUX(8), शून्य, false),
	XADC_US_CHAN_VOLTAGE(18, 25, XADC_REG_VAUX(9), शून्य, false),
	XADC_US_CHAN_VOLTAGE(19, 26, XADC_REG_VAUX(10), शून्य, false),
	XADC_US_CHAN_VOLTAGE(20, 27, XADC_REG_VAUX(11), शून्य, false),
	XADC_US_CHAN_VOLTAGE(21, 28, XADC_REG_VAUX(12), शून्य, false),
	XADC_US_CHAN_VOLTAGE(22, 29, XADC_REG_VAUX(13), शून्य, false),
	XADC_US_CHAN_VOLTAGE(23, 30, XADC_REG_VAUX(14), शून्य, false),
	XADC_US_CHAN_VOLTAGE(24, 31, XADC_REG_VAUX(15), शून्य, false),
पूर्ण;

अटल स्थिर काष्ठा iio_info xadc_info = अणु
	.पढ़ो_raw = &xadc_पढ़ो_raw,
	.ग_लिखो_raw = &xadc_ग_लिखो_raw,
	.पढ़ो_event_config = &xadc_पढ़ो_event_config,
	.ग_लिखो_event_config = &xadc_ग_लिखो_event_config,
	.पढ़ो_event_value = &xadc_पढ़ो_event_value,
	.ग_लिखो_event_value = &xadc_ग_लिखो_event_value,
	.update_scan_mode = &xadc_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xadc_of_match_table[] = अणु
	अणु
		.compatible = "xlnx,zynq-xadc-1.00.a",
		.data = &xadc_zynq_ops
	पूर्ण, अणु
		.compatible = "xlnx,axi-xadc-1.00.a",
		.data = &xadc_7s_axi_ops
	पूर्ण, अणु
		.compatible = "xlnx,system-management-wiz-1.3",
		.data = &xadc_us_axi_ops
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xadc_of_match_table);

अटल पूर्णांक xadc_parse_dt(काष्ठा iio_dev *indio_dev, काष्ठा device_node *np,
	अचिन्हित पूर्णांक *conf)
अणु
	काष्ठा device *dev = indio_dev->dev.parent;
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	स्थिर काष्ठा iio_chan_spec *channel_ढाँचाs;
	काष्ठा iio_chan_spec *channels, *chan;
	काष्ठा device_node *chan_node, *child;
	अचिन्हित पूर्णांक max_channels;
	अचिन्हित पूर्णांक num_channels;
	स्थिर अक्षर *बाह्यal_mux;
	u32 ext_mux_chan;
	u32 reg;
	पूर्णांक ret;

	*conf = 0;

	ret = of_property_पढ़ो_string(np, "xlnx,external-mux", &बाह्यal_mux);
	अगर (ret < 0 || strहालcmp(बाह्यal_mux, "none") == 0)
		xadc->बाह्यal_mux_mode = XADC_EXTERNAL_MUX_NONE;
	अन्यथा अगर (strहालcmp(बाह्यal_mux, "single") == 0)
		xadc->बाह्यal_mux_mode = XADC_EXTERNAL_MUX_SINGLE;
	अन्यथा अगर (strहालcmp(बाह्यal_mux, "dual") == 0)
		xadc->बाह्यal_mux_mode = XADC_EXTERNAL_MUX_DUAL;
	अन्यथा
		वापस -EINVAL;

	अगर (xadc->बाह्यal_mux_mode != XADC_EXTERNAL_MUX_NONE) अणु
		ret = of_property_पढ़ो_u32(np, "xlnx,external-mux-channel",
					&ext_mux_chan);
		अगर (ret < 0)
			वापस ret;

		अगर (xadc->बाह्यal_mux_mode == XADC_EXTERNAL_MUX_SINGLE) अणु
			अगर (ext_mux_chan == 0)
				ext_mux_chan = XADC_REG_VPVN;
			अन्यथा अगर (ext_mux_chan <= 16)
				ext_mux_chan = XADC_REG_VAUX(ext_mux_chan - 1);
			अन्यथा
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (ext_mux_chan > 0 && ext_mux_chan <= 8)
				ext_mux_chan = XADC_REG_VAUX(ext_mux_chan - 1);
			अन्यथा
				वापस -EINVAL;
		पूर्ण

		*conf |= XADC_CONF0_MUX | XADC_CONF0_CHAN(ext_mux_chan);
	पूर्ण
	अगर (xadc->ops->type == XADC_TYPE_S7) अणु
		channel_ढाँचाs = xadc_7s_channels;
		max_channels = ARRAY_SIZE(xadc_7s_channels);
	पूर्ण अन्यथा अणु
		channel_ढाँचाs = xadc_us_channels;
		max_channels = ARRAY_SIZE(xadc_us_channels);
	पूर्ण
	channels = devm_kmemdup(dev, channel_ढाँचाs,
				माप(channels[0]) * max_channels, GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	num_channels = 9;
	chan = &channels[9];

	chan_node = of_get_child_by_name(np, "xlnx,channels");
	अगर (chan_node) अणु
		क्रम_each_child_of_node(chan_node, child) अणु
			अगर (num_channels >= max_channels) अणु
				of_node_put(child);
				अवरोध;
			पूर्ण

			ret = of_property_पढ़ो_u32(child, "reg", &reg);
			अगर (ret || reg > 16)
				जारी;

			अगर (of_property_पढ़ो_bool(child, "xlnx,bipolar"))
				chan->scan_type.sign = 's';

			अगर (reg == 0) अणु
				chan->scan_index = 11;
				chan->address = XADC_REG_VPVN;
			पूर्ण अन्यथा अणु
				chan->scan_index = 15 + reg;
				chan->address = XADC_REG_VAUX(reg - 1);
			पूर्ण
			num_channels++;
			chan++;
		पूर्ण
	पूर्ण
	of_node_put(chan_node);

	indio_dev->num_channels = num_channels;
	indio_dev->channels = devm_kपुनः_स्मृति(dev, channels,
					    माप(*channels) * num_channels,
					    GFP_KERNEL);
	/* If we can't resize the channels array, just use the original */
	अगर (!indio_dev->channels)
		indio_dev->channels = channels;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर xadc_type_names[] = अणु
	[XADC_TYPE_S7] = "xadc",
	[XADC_TYPE_US] = "xilinx-system-monitor",
पूर्ण;

अटल व्योम xadc_clk_disable_unprepare(व्योम *data)
अणु
	काष्ठा clk *clk = data;

	clk_disable_unprepare(clk);
पूर्ण

अटल व्योम xadc_cancel_delayed_work(व्योम *data)
अणु
	काष्ठा delayed_work *work = data;

	cancel_delayed_work_sync(work);
पूर्ण

अटल पूर्णांक xadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *id;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक bipolar_mask;
	अचिन्हित पूर्णांक conf0;
	काष्ठा xadc *xadc;
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i;

	अगर (!dev->of_node)
		वापस -ENODEV;

	id = of_match_node(xadc_of_match_table, dev->of_node);
	अगर (!id)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	indio_dev = devm_iio_device_alloc(dev, माप(*xadc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	xadc = iio_priv(indio_dev);
	xadc->ops = id->data;
	xadc->irq = irq;
	init_completion(&xadc->completion);
	mutex_init(&xadc->mutex);
	spin_lock_init(&xadc->lock);
	INIT_DELAYED_WORK(&xadc->zynq_unmask_work, xadc_zynq_unmask_worker);

	xadc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xadc->base))
		वापस PTR_ERR(xadc->base);

	indio_dev->name = xadc_type_names[xadc->ops->type];
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &xadc_info;

	ret = xadc_parse_dt(indio_dev, dev->of_node, &conf0);
	अगर (ret)
		वापस ret;

	अगर (xadc->ops->flags & XADC_FLAGS_BUFFERED) अणु
		ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
						      &iio_pollfunc_store_समय,
						      &xadc_trigger_handler,
						      &xadc_buffer_ops);
		अगर (ret)
			वापस ret;

		xadc->convst_trigger = xadc_alloc_trigger(indio_dev, "convst");
		अगर (IS_ERR(xadc->convst_trigger))
			वापस PTR_ERR(xadc->convst_trigger);

		xadc->samplerate_trigger = xadc_alloc_trigger(indio_dev,
			"samplerate");
		अगर (IS_ERR(xadc->samplerate_trigger))
			वापस PTR_ERR(xadc->samplerate_trigger);
	पूर्ण

	xadc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(xadc->clk))
		वापस PTR_ERR(xadc->clk);

	ret = clk_prepare_enable(xadc->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev,
				       xadc_clk_disable_unprepare, xadc->clk);
	अगर (ret)
		वापस ret;

	/*
	 * Make sure not to exceed the maximum samplerate since otherwise the
	 * resulting पूर्णांकerrupt storm will soft-lock the प्रणाली.
	 */
	अगर (xadc->ops->flags & XADC_FLAGS_BUFFERED) अणु
		ret = xadc_पढ़ो_samplerate(xadc);
		अगर (ret < 0)
			वापस ret;

		अगर (ret > XADC_MAX_SAMPLERATE) अणु
			ret = xadc_ग_लिखो_samplerate(xadc, XADC_MAX_SAMPLERATE);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(dev, xadc->irq, xadc->ops->पूर्णांकerrupt_handler, 0,
			       dev_name(dev), indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, xadc_cancel_delayed_work,
				       &xadc->zynq_unmask_work);
	अगर (ret)
		वापस ret;

	ret = xadc->ops->setup(pdev, indio_dev, xadc->irq);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < 16; i++)
		xadc_पढ़ो_adc_reg(xadc, XADC_REG_THRESHOLD(i),
			&xadc->threshold[i]);

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_CONF0, conf0);
	अगर (ret)
		वापस ret;

	bipolar_mask = 0;
	क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
		अगर (indio_dev->channels[i].scan_type.sign == 's')
			bipolar_mask |= BIT(indio_dev->channels[i].scan_index);
	पूर्ण

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_INPUT_MODE(0), bipolar_mask);
	अगर (ret)
		वापस ret;

	ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_INPUT_MODE(1),
		bipolar_mask >> 16);
	अगर (ret)
		वापस ret;

	/* Disable all alarms */
	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_ALARM_MASK,
				  XADC_CONF1_ALARM_MASK);
	अगर (ret)
		वापस ret;

	/* Set thresholds to min/max */
	क्रम (i = 0; i < 16; i++) अणु
		/*
		 * Set max voltage threshold and both temperature thresholds to
		 * 0xffff, min voltage threshold to 0.
		 */
		अगर (i % 8 < 4 || i == 7)
			xadc->threshold[i] = 0xffff;
		अन्यथा
			xadc->threshold[i] = 0;
		ret = xadc_ग_लिखो_adc_reg(xadc, XADC_REG_THRESHOLD(i),
			xadc->threshold[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Go to non-buffered mode */
	xadc_postdisable(indio_dev);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver xadc_driver = अणु
	.probe = xadc_probe,
	.driver = अणु
		.name = "xadc",
		.of_match_table = xadc_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xadc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Xilinx XADC IIO driver");
