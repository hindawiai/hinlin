<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Linaro Ltd
 *
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */
#अगर_अघोषित _MMC_CORE_PWRSEQ_H
#घोषणा _MMC_CORE_PWRSEQ_H

#समावेश <linux/types.h>

काष्ठा mmc_host;
काष्ठा device;
काष्ठा module;

काष्ठा mmc_pwrseq_ops अणु
	व्योम (*pre_घातer_on)(काष्ठा mmc_host *host);
	व्योम (*post_घातer_on)(काष्ठा mmc_host *host);
	व्योम (*घातer_off)(काष्ठा mmc_host *host);
	व्योम (*reset)(काष्ठा mmc_host *host);
पूर्ण;

काष्ठा mmc_pwrseq अणु
	स्थिर काष्ठा mmc_pwrseq_ops *ops;
	काष्ठा device *dev;
	काष्ठा list_head pwrseq_node;
	काष्ठा module *owner;
पूर्ण;

#अगर_घोषित CONFIG_OF

पूर्णांक mmc_pwrseq_रेजिस्टर(काष्ठा mmc_pwrseq *pwrseq);
व्योम mmc_pwrseq_unरेजिस्टर(काष्ठा mmc_pwrseq *pwrseq);

पूर्णांक mmc_pwrseq_alloc(काष्ठा mmc_host *host);
व्योम mmc_pwrseq_pre_घातer_on(काष्ठा mmc_host *host);
व्योम mmc_pwrseq_post_घातer_on(काष्ठा mmc_host *host);
व्योम mmc_pwrseq_घातer_off(काष्ठा mmc_host *host);
व्योम mmc_pwrseq_reset(काष्ठा mmc_host *host);
व्योम mmc_pwrseq_मुक्त(काष्ठा mmc_host *host);

#अन्यथा

अटल अंतरभूत पूर्णांक mmc_pwrseq_रेजिस्टर(काष्ठा mmc_pwrseq *pwrseq)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_unरेजिस्टर(काष्ठा mmc_pwrseq *pwrseq) अणुपूर्ण
अटल अंतरभूत पूर्णांक mmc_pwrseq_alloc(काष्ठा mmc_host *host) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_pre_घातer_on(काष्ठा mmc_host *host) अणुपूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_post_घातer_on(काष्ठा mmc_host *host) अणुपूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_घातer_off(काष्ठा mmc_host *host) अणुपूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_reset(काष्ठा mmc_host *host) अणुपूर्ण
अटल अंतरभूत व्योम mmc_pwrseq_मुक्त(काष्ठा mmc_host *host) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
