<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPIC समयr driver
 *
 * Copyright 2013 Freescale Semiconductor, Inc.
 * Author: Dongsheng Wang <Dongsheng.Wang@मुक्तscale.com>
 *	   Li Yang <leoli@मुक्तscale.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/syscore_ops.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/mpic_समयr.h>

#घोषणा FSL_GLOBAL_TIMER		0x1

/* Clock Ratio
 * Divide by 64 0x00000300
 * Divide by 32 0x00000200
 * Divide by 16 0x00000100
 * Divide by  8 0x00000000 (Hardware शेष भाग)
 */
#घोषणा MPIC_TIMER_TCR_CLKDIV		0x00000300

#घोषणा MPIC_TIMER_TCR_ROVR_OFFSET	24

#घोषणा TIMER_STOP			0x80000000
#घोषणा GTCCR_TOG			0x80000000
#घोषणा TIMERS_PER_GROUP		4
#घोषणा MAX_TICKS			(~0U >> 1)
#घोषणा MAX_TICKS_CASCADE		(~0U)
#घोषणा TIMER_OFFSET(num)		(1 << (TIMERS_PER_GROUP - 1 - num))

काष्ठा समयr_regs अणु
	u32	gtccr;
	u32	res0[3];
	u32	gtbcr;
	u32	res1[3];
	u32	gtvpr;
	u32	res2[3];
	u32	gtdr;
	u32	res3[3];
पूर्ण;

काष्ठा cascade_priv अणु
	u32 tcr_value;			/* TCR रेजिस्टर: CASC & ROVR value */
	अचिन्हित पूर्णांक cascade_map;	/* cascade map */
	अचिन्हित पूर्णांक समयr_num;		/* cascade control समयr */
पूर्ण;

काष्ठा समयr_group_priv अणु
	काष्ठा समयr_regs __iomem	*regs;
	काष्ठा mpic_समयr		समयr[TIMERS_PER_GROUP];
	काष्ठा list_head		node;
	अचिन्हित पूर्णांक			समयrfreq;
	अचिन्हित पूर्णांक			idle;
	अचिन्हित पूर्णांक			flags;
	spinlock_t			lock;
	व्योम __iomem			*group_tcr;
पूर्ण;

अटल काष्ठा cascade_priv cascade_समयr[] = अणु
	/* cascade समयr 0 and 1 */
	अणु0x1, 0xc, 0x1पूर्ण,
	/* cascade समयr 1 and 2 */
	अणु0x2, 0x6, 0x2पूर्ण,
	/* cascade समयr 2 and 3 */
	अणु0x4, 0x3, 0x3पूर्ण
पूर्ण;

अटल LIST_HEAD(समयr_group_list);

अटल व्योम convert_ticks_to_समय(काष्ठा समयr_group_priv *priv,
		स्थिर u64 ticks, समय64_t *समय)
अणु
	*समय = (u64)भाग_u64(ticks, priv->समयrfreq);
पूर्ण

/* the समय set by the user is converted to "ticks" */
अटल पूर्णांक convert_समय_प्रकारo_ticks(काष्ठा समयr_group_priv *priv,
		समय64_t समय, u64 *ticks)
अणु
	u64 max_value;		/* prevent u64 overflow */

	max_value = भाग_u64(ULदीर्घ_उच्च, priv->समयrfreq);

	अगर (समय > max_value)
		वापस -EINVAL;

	*ticks = (u64)समय * (u64)priv->समयrfreq;

	वापस 0;
पूर्ण

/* detect whether there is a cascade समयr available */
अटल काष्ठा mpic_समयr *detect_idle_cascade_समयr(
					काष्ठा समयr_group_priv *priv)
अणु
	काष्ठा cascade_priv *casc_priv;
	अचिन्हित पूर्णांक map;
	अचिन्हित पूर्णांक array_size = ARRAY_SIZE(cascade_समयr);
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	casc_priv = cascade_समयr;
	क्रम (i = 0; i < array_size; i++) अणु
		spin_lock_irqsave(&priv->lock, flags);
		map = casc_priv->cascade_map & priv->idle;
		अगर (map == casc_priv->cascade_map) अणु
			num = casc_priv->समयr_num;
			priv->समयr[num].cascade_handle = casc_priv;

			/* set समयr busy */
			priv->idle &= ~casc_priv->cascade_map;
			spin_unlock_irqrestore(&priv->lock, flags);
			वापस &priv->समयr[num];
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
		casc_priv++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक set_cascade_समयr(काष्ठा समयr_group_priv *priv, u64 ticks,
		अचिन्हित पूर्णांक num)
अणु
	काष्ठा cascade_priv *casc_priv;
	u32 tcr;
	u32 पंचांगp_ticks;
	u32 rem_ticks;

	/* set group tcr reg क्रम cascade */
	casc_priv = priv->समयr[num].cascade_handle;
	अगर (!casc_priv)
		वापस -EINVAL;

	tcr = casc_priv->tcr_value |
		(casc_priv->tcr_value << MPIC_TIMER_TCR_ROVR_OFFSET);
	setbits32(priv->group_tcr, tcr);

	पंचांगp_ticks = भाग_u64_rem(ticks, MAX_TICKS_CASCADE, &rem_ticks);

	out_be32(&priv->regs[num].gtccr, 0);
	out_be32(&priv->regs[num].gtbcr, पंचांगp_ticks | TIMER_STOP);

	out_be32(&priv->regs[num - 1].gtccr, 0);
	out_be32(&priv->regs[num - 1].gtbcr, rem_ticks);

	वापस 0;
पूर्ण

अटल काष्ठा mpic_समयr *get_cascade_समयr(काष्ठा समयr_group_priv *priv,
					u64 ticks)
अणु
	काष्ठा mpic_समयr *allocated_समयr;

	/* Two cascade समयrs: Support the maximum समय */
	स्थिर u64 max_ticks = (u64)MAX_TICKS * (u64)MAX_TICKS_CASCADE;
	पूर्णांक ret;

	अगर (ticks > max_ticks)
		वापस शून्य;

	/* detect idle समयr */
	allocated_समयr = detect_idle_cascade_समयr(priv);
	अगर (!allocated_समयr)
		वापस शून्य;

	/* set ticks to समयr */
	ret = set_cascade_समयr(priv, ticks, allocated_समयr->num);
	अगर (ret < 0)
		वापस शून्य;

	वापस allocated_समयr;
पूर्ण

अटल काष्ठा mpic_समयr *get_समयr(समय64_t समय)
अणु
	काष्ठा समयr_group_priv *priv;
	काष्ठा mpic_समयr *समयr;

	u64 ticks;
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	list_क्रम_each_entry(priv, &समयr_group_list, node) अणु
		ret = convert_समय_प्रकारo_ticks(priv, समय, &ticks);
		अगर (ret < 0)
			वापस शून्य;

		अगर (ticks > MAX_TICKS) अणु
			अगर (!(priv->flags & FSL_GLOBAL_TIMER))
				वापस शून्य;

			समयr = get_cascade_समयr(priv, ticks);
			अगर (!समयr)
				जारी;

			वापस समयr;
		पूर्ण

		क्रम (i = 0; i < TIMERS_PER_GROUP; i++) अणु
			/* one समयr: Reverse allocation */
			num = TIMERS_PER_GROUP - 1 - i;
			spin_lock_irqsave(&priv->lock, flags);
			अगर (priv->idle & (1 << i)) अणु
				/* set समयr busy */
				priv->idle &= ~(1 << i);
				/* set ticks & stop समयr */
				out_be32(&priv->regs[num].gtbcr,
					ticks | TIMER_STOP);
				out_be32(&priv->regs[num].gtccr, 0);
				priv->समयr[num].cascade_handle = शून्य;
				spin_unlock_irqrestore(&priv->lock, flags);
				वापस &priv->समयr[num];
			पूर्ण
			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mpic_start_समयr - start hardware समयr
 * @handle: the समयr to be started.
 *
 * It will करो ->fn(->dev) callback from the hardware पूर्णांकerrupt at
 * the 'time64_t' poपूर्णांक in the future.
 */
व्योम mpic_start_समयr(काष्ठा mpic_समयr *handle)
अणु
	काष्ठा समयr_group_priv *priv = container_of(handle,
			काष्ठा समयr_group_priv, समयr[handle->num]);

	clrbits32(&priv->regs[handle->num].gtbcr, TIMER_STOP);
पूर्ण
EXPORT_SYMBOL(mpic_start_समयr);

/**
 * mpic_stop_समयr - stop hardware समयr
 * @handle: the समयr to be stoped
 *
 * The समयr periodically generates an पूर्णांकerrupt. Unless user stops the समयr.
 */
व्योम mpic_stop_समयr(काष्ठा mpic_समयr *handle)
अणु
	काष्ठा समयr_group_priv *priv = container_of(handle,
			काष्ठा समयr_group_priv, समयr[handle->num]);
	काष्ठा cascade_priv *casc_priv;

	setbits32(&priv->regs[handle->num].gtbcr, TIMER_STOP);

	casc_priv = priv->समयr[handle->num].cascade_handle;
	अगर (casc_priv) अणु
		out_be32(&priv->regs[handle->num].gtccr, 0);
		out_be32(&priv->regs[handle->num - 1].gtccr, 0);
	पूर्ण अन्यथा अणु
		out_be32(&priv->regs[handle->num].gtccr, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mpic_stop_समयr);

/**
 * mpic_get_reमुख्य_समय - get समयr समय
 * @handle: the समयr to be selected.
 * @समय: समय क्रम समयr
 *
 * Query समयr reमुख्यing समय.
 */
व्योम mpic_get_reमुख्य_समय(काष्ठा mpic_समयr *handle, समय64_t *समय)
अणु
	काष्ठा समयr_group_priv *priv = container_of(handle,
			काष्ठा समयr_group_priv, समयr[handle->num]);
	काष्ठा cascade_priv *casc_priv;

	u64 ticks;
	u32 पंचांगp_ticks;

	casc_priv = priv->समयr[handle->num].cascade_handle;
	अगर (casc_priv) अणु
		पंचांगp_ticks = in_be32(&priv->regs[handle->num].gtccr);
		पंचांगp_ticks &= ~GTCCR_TOG;
		ticks = ((u64)पंचांगp_ticks & अच_पूर्णांक_उच्च) * (u64)MAX_TICKS_CASCADE;
		पंचांगp_ticks = in_be32(&priv->regs[handle->num - 1].gtccr);
		ticks += पंचांगp_ticks;
	पूर्ण अन्यथा अणु
		ticks = in_be32(&priv->regs[handle->num].gtccr);
		ticks &= ~GTCCR_TOG;
	पूर्ण

	convert_ticks_to_समय(priv, ticks, समय);
पूर्ण
EXPORT_SYMBOL(mpic_get_reमुख्य_समय);

/**
 * mpic_मुक्त_समयr - मुक्त hardware समयr
 * @handle: the समयr to be हटाओd.
 *
 * Free the समयr.
 *
 * Note: can not be used in पूर्णांकerrupt context.
 */
व्योम mpic_मुक्त_समयr(काष्ठा mpic_समयr *handle)
अणु
	काष्ठा समयr_group_priv *priv = container_of(handle,
			काष्ठा समयr_group_priv, समयr[handle->num]);

	काष्ठा cascade_priv *casc_priv;
	अचिन्हित दीर्घ flags;

	mpic_stop_समयr(handle);

	casc_priv = priv->समयr[handle->num].cascade_handle;

	मुक्त_irq(priv->समयr[handle->num].irq, priv->समयr[handle->num].dev);

	spin_lock_irqsave(&priv->lock, flags);
	अगर (casc_priv) अणु
		u32 tcr;
		tcr = casc_priv->tcr_value | (casc_priv->tcr_value <<
					MPIC_TIMER_TCR_ROVR_OFFSET);
		clrbits32(priv->group_tcr, tcr);
		priv->idle |= casc_priv->cascade_map;
		priv->समयr[handle->num].cascade_handle = शून्य;
	पूर्ण अन्यथा अणु
		priv->idle |= TIMER_OFFSET(handle->num);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
EXPORT_SYMBOL(mpic_मुक्त_समयr);

/**
 * mpic_request_समयr - get a hardware समयr
 * @fn: पूर्णांकerrupt handler function
 * @dev: callback function of the data
 * @समय: समय क्रम समयr
 *
 * This executes the "request_irq", वापसing शून्य
 * अन्यथा "handle" on success.
 */
काष्ठा mpic_समयr *mpic_request_समयr(irq_handler_t fn, व्योम *dev,
				      समय64_t समय)
अणु
	काष्ठा mpic_समयr *allocated_समयr;
	पूर्णांक ret;

	अगर (list_empty(&समयr_group_list))
		वापस शून्य;

	अगर (समय < 0)
		वापस शून्य;

	allocated_समयr = get_समयr(समय);
	अगर (!allocated_समयr)
		वापस शून्य;

	ret = request_irq(allocated_समयr->irq, fn,
			IRQF_TRIGGER_LOW, "global-timer", dev);
	अगर (ret) अणु
		mpic_मुक्त_समयr(allocated_समयr);
		वापस शून्य;
	पूर्ण

	allocated_समयr->dev = dev;

	वापस allocated_समयr;
पूर्ण
EXPORT_SYMBOL(mpic_request_समयr);

अटल पूर्णांक समयr_group_get_freq(काष्ठा device_node *np,
			काष्ठा समयr_group_priv *priv)
अणु
	u32 भाग;

	अगर (priv->flags & FSL_GLOBAL_TIMER) अणु
		काष्ठा device_node *dn;

		dn = of_find_compatible_node(शून्य, शून्य, "fsl,mpic");
		अगर (dn) अणु
			of_property_पढ़ो_u32(dn, "clock-frequency",
					&priv->समयrfreq);
			of_node_put(dn);
		पूर्ण
	पूर्ण

	अगर (priv->समयrfreq <= 0)
		वापस -EINVAL;

	अगर (priv->flags & FSL_GLOBAL_TIMER) अणु
		भाग = (1 << (MPIC_TIMER_TCR_CLKDIV >> 8)) * 8;
		priv->समयrfreq /= भाग;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक समयr_group_get_irq(काष्ठा device_node *np,
		काष्ठा समयr_group_priv *priv)
अणु
	स्थिर u32 all_समयr[] = अणु 0, TIMERS_PER_GROUP पूर्ण;
	स्थिर u32 *p;
	u32 offset;
	u32 count;

	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक irq_index = 0;
	अचिन्हित पूर्णांक irq;
	पूर्णांक len;

	p = of_get_property(np, "fsl,available-ranges", &len);
	अगर (p && len % (2 * माप(u32)) != 0) अणु
		pr_err("%pOF: malformed available-ranges property.\n", np);
		वापस -EINVAL;
	पूर्ण

	अगर (!p) अणु
		p = all_समयr;
		len = माप(all_समयr);
	पूर्ण

	len /= 2 * माप(u32);

	क्रम (i = 0; i < len; i++) अणु
		offset = p[i * 2];
		count = p[i * 2 + 1];
		क्रम (j = 0; j < count; j++) अणु
			irq = irq_of_parse_and_map(np, irq_index);
			अगर (!irq) अणु
				pr_err("%pOF: irq parse and map failed.\n", np);
				वापस -EINVAL;
			पूर्ण

			/* Set समयr idle */
			priv->idle |= TIMER_OFFSET((offset + j));
			priv->समयr[offset + j].irq = irq;
			priv->समयr[offset + j].num = offset + j;
			irq_index++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम समयr_group_init(काष्ठा device_node *np)
अणु
	काष्ठा समयr_group_priv *priv;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret;

	priv = kzalloc(माप(काष्ठा समयr_group_priv), GFP_KERNEL);
	अगर (!priv) अणु
		pr_err("%pOF: cannot allocate memory for group.\n", np);
		वापस;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,mpic-global-timer"))
		priv->flags |= FSL_GLOBAL_TIMER;

	priv->regs = of_iomap(np, i++);
	अगर (!priv->regs) अणु
		pr_err("%pOF: cannot ioremap timer register address.\n", np);
		जाओ out;
	पूर्ण

	अगर (priv->flags & FSL_GLOBAL_TIMER) अणु
		priv->group_tcr = of_iomap(np, i++);
		अगर (!priv->group_tcr) अणु
			pr_err("%pOF: cannot ioremap tcr address.\n", np);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = समयr_group_get_freq(np, priv);
	अगर (ret < 0) अणु
		pr_err("%pOF: cannot get timer frequency.\n", np);
		जाओ out;
	पूर्ण

	ret = समयr_group_get_irq(np, priv);
	अगर (ret < 0) अणु
		pr_err("%pOF: cannot get timer irqs.\n", np);
		जाओ out;
	पूर्ण

	spin_lock_init(&priv->lock);

	/* Init FSL समयr hardware */
	अगर (priv->flags & FSL_GLOBAL_TIMER)
		setbits32(priv->group_tcr, MPIC_TIMER_TCR_CLKDIV);

	list_add_tail(&priv->node, &समयr_group_list);

	वापस;

out:
	अगर (priv->regs)
		iounmap(priv->regs);

	अगर (priv->group_tcr)
		iounmap(priv->group_tcr);

	kमुक्त(priv);
पूर्ण

अटल व्योम mpic_समयr_resume(व्योम)
अणु
	काष्ठा समयr_group_priv *priv;

	list_क्रम_each_entry(priv, &समयr_group_list, node) अणु
		/* Init FSL समयr hardware */
		अगर (priv->flags & FSL_GLOBAL_TIMER)
			setbits32(priv->group_tcr, MPIC_TIMER_TCR_CLKDIV);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id mpic_समयr_ids[] = अणु
	अणु .compatible = "fsl,mpic-global-timer", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा syscore_ops mpic_समयr_syscore_ops = अणु
	.resume = mpic_समयr_resume,
पूर्ण;

अटल पूर्णांक __init mpic_समयr_init(व्योम)
अणु
	काष्ठा device_node *np = शून्य;

	क्रम_each_matching_node(np, mpic_समयr_ids)
		समयr_group_init(np);

	रेजिस्टर_syscore_ops(&mpic_समयr_syscore_ops);

	अगर (list_empty(&समयr_group_list))
		वापस -ENODEV;

	वापस 0;
पूर्ण
subsys_initcall(mpic_समयr_init);
