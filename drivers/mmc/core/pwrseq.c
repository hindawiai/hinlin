<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2014 Linaro Ltd
 *
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 *
 *  MMC घातer sequence management
 */
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <linux/mmc/host.h>

#समावेश "pwrseq.h"

अटल DEFINE_MUTEX(pwrseq_list_mutex);
अटल LIST_HEAD(pwrseq_list);

पूर्णांक mmc_pwrseq_alloc(काष्ठा mmc_host *host)
अणु
	काष्ठा device_node *np;
	काष्ठा mmc_pwrseq *p;

	np = of_parse_phandle(host->parent->of_node, "mmc-pwrseq", 0);
	अगर (!np)
		वापस 0;

	mutex_lock(&pwrseq_list_mutex);
	list_क्रम_each_entry(p, &pwrseq_list, pwrseq_node) अणु
		अगर (p->dev->of_node == np) अणु
			अगर (!try_module_get(p->owner))
				dev_err(host->parent,
					"increasing module refcount failed\n");
			अन्यथा
				host->pwrseq = p;

			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(np);
	mutex_unlock(&pwrseq_list_mutex);

	अगर (!host->pwrseq)
		वापस -EPROBE_DEFER;

	dev_info(host->parent, "allocated mmc-pwrseq\n");

	वापस 0;
पूर्ण

व्योम mmc_pwrseq_pre_घातer_on(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq *pwrseq = host->pwrseq;

	अगर (pwrseq && pwrseq->ops->pre_घातer_on)
		pwrseq->ops->pre_घातer_on(host);
पूर्ण

व्योम mmc_pwrseq_post_घातer_on(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq *pwrseq = host->pwrseq;

	अगर (pwrseq && pwrseq->ops->post_घातer_on)
		pwrseq->ops->post_घातer_on(host);
पूर्ण

व्योम mmc_pwrseq_घातer_off(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq *pwrseq = host->pwrseq;

	अगर (pwrseq && pwrseq->ops->घातer_off)
		pwrseq->ops->घातer_off(host);
पूर्ण

व्योम mmc_pwrseq_reset(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq *pwrseq = host->pwrseq;

	अगर (pwrseq && pwrseq->ops->reset)
		pwrseq->ops->reset(host);
पूर्ण

व्योम mmc_pwrseq_मुक्त(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq *pwrseq = host->pwrseq;

	अगर (pwrseq) अणु
		module_put(pwrseq->owner);
		host->pwrseq = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mmc_pwrseq_रेजिस्टर(काष्ठा mmc_pwrseq *pwrseq)
अणु
	अगर (!pwrseq || !pwrseq->ops || !pwrseq->dev)
		वापस -EINVAL;

	mutex_lock(&pwrseq_list_mutex);
	list_add(&pwrseq->pwrseq_node, &pwrseq_list);
	mutex_unlock(&pwrseq_list_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_pwrseq_रेजिस्टर);

व्योम mmc_pwrseq_unरेजिस्टर(काष्ठा mmc_pwrseq *pwrseq)
अणु
	अगर (pwrseq) अणु
		mutex_lock(&pwrseq_list_mutex);
		list_del(&pwrseq->pwrseq_node);
		mutex_unlock(&pwrseq_list_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mmc_pwrseq_unरेजिस्टर);
