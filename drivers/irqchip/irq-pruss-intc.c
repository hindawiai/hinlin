<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PRU-ICSS INTC IRQChip driver क्रम various TI SoCs
 *
 * Copyright (C) 2016-2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Author(s):
 *	Andrew F. Davis <afd@ti.com>
 *	Suman Anna <s-anna@ti.com>
 *	Grzegorz Jaszczyk <grzegorz.jaszczyk@linaro.org> क्रम Texas Instruments
 *
 * Copyright (C) 2019 David Lechner <david@lechnology.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Number of host पूर्णांकerrupts reaching the मुख्य MPU sub-प्रणाली. Note that this
 * is not the same as the total number of host पूर्णांकerrupts supported by the PRUSS
 * INTC instance
 */
#घोषणा MAX_NUM_HOST_IRQS	8

/* minimum starting host पूर्णांकerrupt number क्रम MPU */
#घोषणा FIRST_PRU_HOST_INT	2

/* PRU_ICSS_INTC रेजिस्टरs */
#घोषणा PRU_INTC_REVID		0x0000
#घोषणा PRU_INTC_CR		0x0004
#घोषणा PRU_INTC_GER		0x0010
#घोषणा PRU_INTC_GNLR		0x001c
#घोषणा PRU_INTC_SISR		0x0020
#घोषणा PRU_INTC_SICR		0x0024
#घोषणा PRU_INTC_EISR		0x0028
#घोषणा PRU_INTC_EICR		0x002c
#घोषणा PRU_INTC_HIEISR		0x0034
#घोषणा PRU_INTC_HIDISR		0x0038
#घोषणा PRU_INTC_GPIR		0x0080
#घोषणा PRU_INTC_SRSR(x)	(0x0200 + (x) * 4)
#घोषणा PRU_INTC_SECR(x)	(0x0280 + (x) * 4)
#घोषणा PRU_INTC_ESR(x)		(0x0300 + (x) * 4)
#घोषणा PRU_INTC_ECR(x)		(0x0380 + (x) * 4)
#घोषणा PRU_INTC_CMR(x)		(0x0400 + (x) * 4)
#घोषणा PRU_INTC_HMR(x)		(0x0800 + (x) * 4)
#घोषणा PRU_INTC_HIPIR(x)	(0x0900 + (x) * 4)
#घोषणा PRU_INTC_SIPR(x)	(0x0d00 + (x) * 4)
#घोषणा PRU_INTC_SITR(x)	(0x0d80 + (x) * 4)
#घोषणा PRU_INTC_HINLR(x)	(0x1100 + (x) * 4)
#घोषणा PRU_INTC_HIER		0x1500

/* CMR रेजिस्टर bit-field macros */
#घोषणा CMR_EVT_MAP_MASK	0xf
#घोषणा CMR_EVT_MAP_BITS	8
#घोषणा CMR_EVT_PER_REG		4

/* HMR रेजिस्टर bit-field macros */
#घोषणा HMR_CH_MAP_MASK		0xf
#घोषणा HMR_CH_MAP_BITS		8
#घोषणा HMR_CH_PER_REG		4

/* HIPIR रेजिस्टर bit-fields */
#घोषणा INTC_HIPIR_NONE_HINT	0x80000000

#घोषणा MAX_PRU_SYS_EVENTS 160
#घोषणा MAX_PRU_CHANNELS 20

/**
 * काष्ठा pruss_पूर्णांकc_map_record - keeps track of actual mapping state
 * @value: The currently mapped value (channel or host)
 * @ref_count: Keeps track of number of current users of this resource
 */
काष्ठा pruss_पूर्णांकc_map_record अणु
	u8 value;
	u8 ref_count;
पूर्ण;

/**
 * काष्ठा pruss_पूर्णांकc_match_data - match data to handle SoC variations
 * @num_प्रणाली_events: number of input प्रणाली events handled by the PRUSS INTC
 * @num_host_events: number of host events (which is equal to number of
 *		     channels) supported by the PRUSS INTC
 */
काष्ठा pruss_पूर्णांकc_match_data अणु
	u8 num_प्रणाली_events;
	u8 num_host_events;
पूर्ण;

/**
 * काष्ठा pruss_पूर्णांकc - PRUSS पूर्णांकerrupt controller काष्ठाure
 * @event_channel: current state of प्रणाली event to channel mappings
 * @channel_host: current state of channel to host mappings
 * @irqs: kernel irq numbers corresponding to PRUSS host पूर्णांकerrupts
 * @base: base भव address of INTC रेजिस्टर space
 * @करोमुख्य: irq करोमुख्य क्रम this पूर्णांकerrupt controller
 * @soc_config: cached PRUSS INTC IP configuration data
 * @dev: PRUSS INTC device poपूर्णांकer
 * @lock: mutex to serialize पूर्णांकerrupts mapping
 */
काष्ठा pruss_पूर्णांकc अणु
	काष्ठा pruss_पूर्णांकc_map_record event_channel[MAX_PRU_SYS_EVENTS];
	काष्ठा pruss_पूर्णांकc_map_record channel_host[MAX_PRU_CHANNELS];
	अचिन्हित पूर्णांक irqs[MAX_NUM_HOST_IRQS];
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	स्थिर काष्ठा pruss_पूर्णांकc_match_data *soc_config;
	काष्ठा device *dev;
	काष्ठा mutex lock; /* PRUSS INTC lock */
पूर्ण;

/**
 * काष्ठा pruss_host_irq_data - PRUSS host irq data काष्ठाure
 * @पूर्णांकc: PRUSS पूर्णांकerrupt controller poपूर्णांकer
 * @host_irq: host irq number
 */
काष्ठा pruss_host_irq_data अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc;
	u8 host_irq;
पूर्ण;

अटल अंतरभूत u32 pruss_पूर्णांकc_पढ़ो_reg(काष्ठा pruss_पूर्णांकc *पूर्णांकc, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(पूर्णांकc->base + reg);
पूर्ण

अटल अंतरभूत व्योम pruss_पूर्णांकc_ग_लिखो_reg(काष्ठा pruss_पूर्णांकc *पूर्णांकc,
					अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, पूर्णांकc->base + reg);
पूर्ण

अटल व्योम pruss_पूर्णांकc_update_cmr(काष्ठा pruss_पूर्णांकc *पूर्णांकc, अचिन्हित पूर्णांक evt,
				  u8 ch)
अणु
	u32 idx, offset, val;

	idx = evt / CMR_EVT_PER_REG;
	offset = (evt % CMR_EVT_PER_REG) * CMR_EVT_MAP_BITS;

	val = pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, PRU_INTC_CMR(idx));
	val &= ~(CMR_EVT_MAP_MASK << offset);
	val |= ch << offset;
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_CMR(idx), val);

	dev_dbg(पूर्णांकc->dev, "SYSEV%u -> CH%d (CMR%d 0x%08x)\n", evt, ch,
		idx, pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, PRU_INTC_CMR(idx)));
पूर्ण

अटल व्योम pruss_पूर्णांकc_update_hmr(काष्ठा pruss_पूर्णांकc *पूर्णांकc, u8 ch, u8 host)
अणु
	u32 idx, offset, val;

	idx = ch / HMR_CH_PER_REG;
	offset = (ch % HMR_CH_PER_REG) * HMR_CH_MAP_BITS;

	val = pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, PRU_INTC_HMR(idx));
	val &= ~(HMR_CH_MAP_MASK << offset);
	val |= host << offset;
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_HMR(idx), val);

	dev_dbg(पूर्णांकc->dev, "CH%d -> HOST%d (HMR%d 0x%08x)\n", ch, host, idx,
		pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, PRU_INTC_HMR(idx)));
पूर्ण

/**
 * pruss_पूर्णांकc_map() - configure the PRUSS INTC
 * @पूर्णांकc: PRUSS पूर्णांकerrupt controller poपूर्णांकer
 * @hwirq: the प्रणाली event number
 *
 * Configures the PRUSS INTC with the provided configuration from the one parsed
 * in the xlate function.
 */
अटल व्योम pruss_पूर्णांकc_map(काष्ठा pruss_पूर्णांकc *पूर्णांकc, अचिन्हित दीर्घ hwirq)
अणु
	काष्ठा device *dev = पूर्णांकc->dev;
	u8 ch, host, reg_idx;
	u32 val;

	mutex_lock(&पूर्णांकc->lock);

	पूर्णांकc->event_channel[hwirq].ref_count++;

	ch = पूर्णांकc->event_channel[hwirq].value;
	host = पूर्णांकc->channel_host[ch].value;

	pruss_पूर्णांकc_update_cmr(पूर्णांकc, hwirq, ch);

	reg_idx = hwirq / 32;
	val = BIT(hwirq  % 32);

	/* clear and enable प्रणाली event */
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_ESR(reg_idx), val);
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SECR(reg_idx), val);

	अगर (++पूर्णांकc->channel_host[ch].ref_count == 1) अणु
		pruss_पूर्णांकc_update_hmr(पूर्णांकc, ch, host);

		/* enable host पूर्णांकerrupts */
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_HIEISR, host);
	पूर्ण

	dev_dbg(dev, "mapped system_event = %lu channel = %d host = %d",
		hwirq, ch, host);

	mutex_unlock(&पूर्णांकc->lock);
पूर्ण

/**
 * pruss_पूर्णांकc_unmap() - unconfigure the PRUSS INTC
 * @पूर्णांकc: PRUSS पूर्णांकerrupt controller poपूर्णांकer
 * @hwirq: the प्रणाली event number
 *
 * Unकरो whatever was करोne in pruss_पूर्णांकc_map() क्रम a PRU core.
 * Mappings are reference counted, so resources are only disabled when there
 * are no दीर्घer any users.
 */
अटल व्योम pruss_पूर्णांकc_unmap(काष्ठा pruss_पूर्णांकc *पूर्णांकc, अचिन्हित दीर्घ hwirq)
अणु
	u8 ch, host, reg_idx;
	u32 val;

	mutex_lock(&पूर्णांकc->lock);

	ch = पूर्णांकc->event_channel[hwirq].value;
	host = पूर्णांकc->channel_host[ch].value;

	अगर (--पूर्णांकc->channel_host[ch].ref_count == 0) अणु
		/* disable host पूर्णांकerrupts */
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_HIDISR, host);

		/* clear the map using reset value 0 */
		pruss_पूर्णांकc_update_hmr(पूर्णांकc, ch, 0);
	पूर्ण

	पूर्णांकc->event_channel[hwirq].ref_count--;
	reg_idx = hwirq / 32;
	val = BIT(hwirq  % 32);

	/* disable प्रणाली events */
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_ECR(reg_idx), val);
	/* clear any pending status */
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SECR(reg_idx), val);

	/* clear the map using reset value 0 */
	pruss_पूर्णांकc_update_cmr(पूर्णांकc, hwirq, 0);

	dev_dbg(पूर्णांकc->dev, "unmapped system_event = %lu channel = %d host = %d\n",
		hwirq, ch, host);

	mutex_unlock(&पूर्णांकc->lock);
पूर्ण

अटल व्योम pruss_पूर्णांकc_init(काष्ठा pruss_पूर्णांकc *पूर्णांकc)
अणु
	स्थिर काष्ठा pruss_पूर्णांकc_match_data *soc_config = पूर्णांकc->soc_config;
	पूर्णांक num_chnl_map_regs, num_host_पूर्णांकr_regs, num_event_type_regs, i;

	num_chnl_map_regs = DIV_ROUND_UP(soc_config->num_प्रणाली_events,
					 CMR_EVT_PER_REG);
	num_host_पूर्णांकr_regs = DIV_ROUND_UP(soc_config->num_host_events,
					  HMR_CH_PER_REG);
	num_event_type_regs = DIV_ROUND_UP(soc_config->num_प्रणाली_events, 32);

	/*
	 * configure polarity (SIPR रेजिस्टर) to active high and
	 * type (SITR रेजिस्टर) to level पूर्णांकerrupt क्रम all प्रणाली events
	 */
	क्रम (i = 0; i < num_event_type_regs; i++) अणु
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SIPR(i), 0xffffffff);
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SITR(i), 0);
	पूर्ण

	/* clear all पूर्णांकerrupt channel map रेजिस्टरs, 4 events per रेजिस्टर */
	क्रम (i = 0; i < num_chnl_map_regs; i++)
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_CMR(i), 0);

	/* clear all host पूर्णांकerrupt map रेजिस्टरs, 4 channels per रेजिस्टर */
	क्रम (i = 0; i < num_host_पूर्णांकr_regs; i++)
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_HMR(i), 0);

	/* global पूर्णांकerrupt enable */
	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_GER, 1);
पूर्ण

अटल व्योम pruss_पूर्णांकc_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक hwirq = data->hwirq;

	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SICR, hwirq);
पूर्ण

अटल व्योम pruss_पूर्णांकc_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक hwirq = data->hwirq;

	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_EICR, hwirq);
पूर्ण

अटल व्योम pruss_पूर्णांकc_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक hwirq = data->hwirq;

	pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_EISR, hwirq);
पूर्ण

अटल पूर्णांक pruss_पूर्णांकc_irq_reqres(काष्ठा irq_data *data)
अणु
	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम pruss_पूर्णांकc_irq_relres(काष्ठा irq_data *data)
अणु
	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक pruss_पूर्णांकc_irq_get_irqchip_state(काष्ठा irq_data *data,
					    क्रमागत irqchip_irq_state which,
					    bool *state)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = irq_data_get_irq_chip_data(data);
	u32 reg, mask, srsr;

	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	reg = PRU_INTC_SRSR(data->hwirq / 32);
	mask = BIT(data->hwirq % 32);

	srsr = pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, reg);

	*state = !!(srsr & mask);

	वापस 0;
पूर्ण

अटल पूर्णांक pruss_पूर्णांकc_irq_set_irqchip_state(काष्ठा irq_data *data,
					    क्रमागत irqchip_irq_state which,
					    bool state)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = irq_data_get_irq_chip_data(data);

	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	अगर (state)
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SISR, data->hwirq);
	अन्यथा
		pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SICR, data->hwirq);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pruss_irqchip = अणु
	.name			= "pruss-intc",
	.irq_ack		= pruss_पूर्णांकc_irq_ack,
	.irq_mask		= pruss_पूर्णांकc_irq_mask,
	.irq_unmask		= pruss_पूर्णांकc_irq_unmask,
	.irq_request_resources	= pruss_पूर्णांकc_irq_reqres,
	.irq_release_resources	= pruss_पूर्णांकc_irq_relres,
	.irq_get_irqchip_state	= pruss_पूर्णांकc_irq_get_irqchip_state,
	.irq_set_irqchip_state	= pruss_पूर्णांकc_irq_set_irqchip_state,
पूर्ण;

अटल पूर्णांक pruss_पूर्णांकc_validate_mapping(काष्ठा pruss_पूर्णांकc *पूर्णांकc, पूर्णांक event,
				       पूर्णांक channel, पूर्णांक host)
अणु
	काष्ठा device *dev = पूर्णांकc->dev;
	पूर्णांक ret = 0;

	mutex_lock(&पूर्णांकc->lock);

	/* check अगर sysevent alपढ़ोy asचिन्हित */
	अगर (पूर्णांकc->event_channel[event].ref_count > 0 &&
	    पूर्णांकc->event_channel[event].value != channel) अणु
		dev_err(dev, "event %d (req. ch %d) already assigned to channel %d\n",
			event, channel, पूर्णांकc->event_channel[event].value);
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	/* check अगर channel alपढ़ोy asचिन्हित */
	अगर (पूर्णांकc->channel_host[channel].ref_count > 0 &&
	    पूर्णांकc->channel_host[channel].value != host) अणु
		dev_err(dev, "channel %d (req. host %d) already assigned to host %d\n",
			channel, host, पूर्णांकc->channel_host[channel].value);
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	पूर्णांकc->event_channel[event].value = channel;
	पूर्णांकc->channel_host[channel].value = host;

unlock:
	mutex_unlock(&पूर्णांकc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
pruss_पूर्णांकc_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
			    स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			    अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = d->host_data;
	काष्ठा device *dev = पूर्णांकc->dev;
	पूर्णांक ret, sys_event, channel, host;

	अगर (पूर्णांकsize < 3)
		वापस -EINVAL;

	sys_event = पूर्णांकspec[0];
	अगर (sys_event < 0 || sys_event >= पूर्णांकc->soc_config->num_प्रणाली_events) अणु
		dev_err(dev, "%d is not valid event number\n", sys_event);
		वापस -EINVAL;
	पूर्ण

	channel = पूर्णांकspec[1];
	अगर (channel < 0 || channel >= पूर्णांकc->soc_config->num_host_events) अणु
		dev_err(dev, "%d is not valid channel number", channel);
		वापस -EINVAL;
	पूर्ण

	host = पूर्णांकspec[2];
	अगर (host < 0 || host >= पूर्णांकc->soc_config->num_host_events) अणु
		dev_err(dev, "%d is not valid host irq number\n", host);
		वापस -EINVAL;
	पूर्ण

	/* check अगर requested sys_event was alपढ़ोy mapped, अगर so validate it */
	ret = pruss_पूर्णांकc_validate_mapping(पूर्णांकc, sys_event, channel, host);
	अगर (ret)
		वापस ret;

	*out_hwirq = sys_event;
	*out_type = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल पूर्णांक pruss_पूर्णांकc_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				     irq_hw_number_t hw)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = d->host_data;

	pruss_पूर्णांकc_map(पूर्णांकc, hw);

	irq_set_chip_data(virq, पूर्णांकc);
	irq_set_chip_and_handler(virq, &pruss_irqchip, handle_level_irq);

	वापस 0;
पूर्ण

अटल व्योम pruss_पूर्णांकc_irq_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = d->host_data;
	अचिन्हित दीर्घ hwirq = irqd_to_hwirq(irq_get_irq_data(virq));

	irq_set_chip_and_handler(virq, शून्य, शून्य);
	irq_set_chip_data(virq, शून्य);
	pruss_पूर्णांकc_unmap(पूर्णांकc, hwirq);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pruss_पूर्णांकc_irq_करोमुख्य_ops = अणु
	.xlate	= pruss_पूर्णांकc_irq_करोमुख्य_xlate,
	.map	= pruss_पूर्णांकc_irq_करोमुख्य_map,
	.unmap	= pruss_पूर्णांकc_irq_करोमुख्य_unmap,
पूर्ण;

अटल व्योम pruss_पूर्णांकc_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा pruss_host_irq_data *host_irq_data = irq_get_handler_data(irq);
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = host_irq_data->पूर्णांकc;
	u8 host_irq = host_irq_data->host_irq + FIRST_PRU_HOST_INT;

	chained_irq_enter(chip, desc);

	जबतक (true) अणु
		u32 hipir;
		अचिन्हित पूर्णांक virq;
		पूर्णांक hwirq;

		/* get highest priority pending PRUSS प्रणाली event */
		hipir = pruss_पूर्णांकc_पढ़ो_reg(पूर्णांकc, PRU_INTC_HIPIR(host_irq));
		अगर (hipir & INTC_HIPIR_NONE_HINT)
			अवरोध;

		hwirq = hipir & GENMASK(9, 0);
		virq = irq_find_mapping(पूर्णांकc->करोमुख्य, hwirq);

		/*
		 * NOTE: manually ACK any प्रणाली events that करो not have a
		 * handler mapped yet
		 */
		अगर (WARN_ON_ONCE(!virq))
			pruss_पूर्णांकc_ग_लिखो_reg(पूर्णांकc, PRU_INTC_SICR, hwirq);
		अन्यथा
			generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल स्थिर अक्षर * स्थिर irq_names[MAX_NUM_HOST_IRQS] = अणु
	"host_intr0", "host_intr1", "host_intr2", "host_intr3",
	"host_intr4", "host_intr5", "host_intr6", "host_intr7",
पूर्ण;

अटल पूर्णांक pruss_पूर्णांकc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा pruss_पूर्णांकc_match_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pruss_पूर्णांकc *पूर्णांकc;
	काष्ठा pruss_host_irq_data *host_data;
	पूर्णांक i, irq, ret;
	u8 max_प्रणाली_events, irqs_reserved = 0;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	max_प्रणाली_events = data->num_प्रणाली_events;

	पूर्णांकc = devm_kzalloc(dev, माप(*पूर्णांकc), GFP_KERNEL);
	अगर (!पूर्णांकc)
		वापस -ENOMEM;

	पूर्णांकc->soc_config = data;
	पूर्णांकc->dev = dev;
	platक्रमm_set_drvdata(pdev, पूर्णांकc);

	पूर्णांकc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(पूर्णांकc->base))
		वापस PTR_ERR(पूर्णांकc->base);

	ret = of_property_पढ़ो_u8(dev->of_node, "ti,irqs-reserved",
				  &irqs_reserved);

	/*
	 * The irqs-reserved is used only क्रम some SoC's thereक्रमe not having
	 * this property is still valid
	 */
	अगर (ret < 0 && ret != -EINVAL)
		वापस ret;

	pruss_पूर्णांकc_init(पूर्णांकc);

	mutex_init(&पूर्णांकc->lock);

	पूर्णांकc->करोमुख्य = irq_करोमुख्य_add_linear(dev->of_node, max_प्रणाली_events,
					     &pruss_पूर्णांकc_irq_करोमुख्य_ops, पूर्णांकc);
	अगर (!पूर्णांकc->करोमुख्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAX_NUM_HOST_IRQS; i++) अणु
		अगर (irqs_reserved & BIT(i))
			जारी;

		irq = platक्रमm_get_irq_byname(pdev, irq_names[i]);
		अगर (irq <= 0) अणु
			ret = (irq == 0) ? -EINVAL : irq;
			जाओ fail_irq;
		पूर्ण

		पूर्णांकc->irqs[i] = irq;

		host_data = devm_kzalloc(dev, माप(*host_data), GFP_KERNEL);
		अगर (!host_data) अणु
			ret = -ENOMEM;
			जाओ fail_irq;
		पूर्ण

		host_data->पूर्णांकc = पूर्णांकc;
		host_data->host_irq = i;

		irq_set_handler_data(irq, host_data);
		irq_set_chained_handler(irq, pruss_पूर्णांकc_irq_handler);
	पूर्ण

	वापस 0;

fail_irq:
	जबतक (--i >= 0) अणु
		अगर (पूर्णांकc->irqs[i])
			irq_set_chained_handler_and_data(पूर्णांकc->irqs[i], शून्य,
							 शून्य);
	पूर्ण

	irq_करोमुख्य_हटाओ(पूर्णांकc->करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक pruss_पूर्णांकc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pruss_पूर्णांकc *पूर्णांकc = platक्रमm_get_drvdata(pdev);
	u8 max_प्रणाली_events = पूर्णांकc->soc_config->num_प्रणाली_events;
	अचिन्हित पूर्णांक hwirq;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUM_HOST_IRQS; i++) अणु
		अगर (पूर्णांकc->irqs[i])
			irq_set_chained_handler_and_data(पूर्णांकc->irqs[i], शून्य,
							 शून्य);
	पूर्ण

	क्रम (hwirq = 0; hwirq < max_प्रणाली_events; hwirq++)
		irq_dispose_mapping(irq_find_mapping(पूर्णांकc->करोमुख्य, hwirq));

	irq_करोमुख्य_हटाओ(पूर्णांकc->करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pruss_पूर्णांकc_match_data pruss_पूर्णांकc_data = अणु
	.num_प्रणाली_events = 64,
	.num_host_events = 10,
पूर्ण;

अटल स्थिर काष्ठा pruss_पूर्णांकc_match_data icssg_पूर्णांकc_data = अणु
	.num_प्रणाली_events = 160,
	.num_host_events = 20,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pruss_पूर्णांकc_of_match[] = अणु
	अणु
		.compatible = "ti,pruss-intc",
		.data = &pruss_पूर्णांकc_data,
	पूर्ण,
	अणु
		.compatible = "ti,icssg-intc",
		.data = &icssg_पूर्णांकc_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pruss_पूर्णांकc_of_match);

अटल काष्ठा platक्रमm_driver pruss_पूर्णांकc_driver = अणु
	.driver = अणु
		.name = "pruss-intc",
		.of_match_table = pruss_पूर्णांकc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe  = pruss_पूर्णांकc_probe,
	.हटाओ = pruss_पूर्णांकc_हटाओ,
पूर्ण;
module_platक्रमm_driver(pruss_पूर्णांकc_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_AUTHOR("Grzegorz Jaszczyk <grzegorz.jaszczyk@linaro.org>");
MODULE_DESCRIPTION("TI PRU-ICSS INTC Driver");
MODULE_LICENSE("GPL v2");
