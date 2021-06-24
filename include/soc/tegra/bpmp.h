<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __SOC_TEGRA_BPMP_H
#घोषणा __SOC_TEGRA_BPMP_H

#समावेश <linux/mailbox_client.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/types.h>

#समावेश <soc/tegra/bpmp-abi.h>

काष्ठा tegra_bpmp_clk;
काष्ठा tegra_bpmp_ops;

काष्ठा tegra_bpmp_soc अणु
	काष्ठा अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक offset;
			अचिन्हित पूर्णांक count;
			अचिन्हित पूर्णांक समयout;
		पूर्ण cpu_tx, thपढ़ो, cpu_rx;
	पूर्ण channels;

	स्थिर काष्ठा tegra_bpmp_ops *ops;
	अचिन्हित पूर्णांक num_resets;
पूर्ण;

काष्ठा tegra_bpmp_mb_data अणु
	u32 code;
	u32 flags;
	u8 data[MSG_DATA_MIN_SZ];
पूर्ण __packed;

काष्ठा tegra_bpmp_channel अणु
	काष्ठा tegra_bpmp *bpmp;
	काष्ठा tegra_bpmp_mb_data *ib;
	काष्ठा tegra_bpmp_mb_data *ob;
	काष्ठा completion completion;
	काष्ठा tegra_ivc *ivc;
	अचिन्हित पूर्णांक index;
पूर्ण;

प्रकार व्योम (*tegra_bpmp_mrq_handler_t)(अचिन्हित पूर्णांक mrq,
					 काष्ठा tegra_bpmp_channel *channel,
					 व्योम *data);

काष्ठा tegra_bpmp_mrq अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक mrq;
	tegra_bpmp_mrq_handler_t handler;
	व्योम *data;
पूर्ण;

काष्ठा tegra_bpmp अणु
	स्थिर काष्ठा tegra_bpmp_soc *soc;
	काष्ठा device *dev;
	व्योम *priv;

	काष्ठा अणु
		काष्ठा mbox_client client;
		काष्ठा mbox_chan *channel;
	पूर्ण mbox;

	spinlock_t atomic_tx_lock;
	काष्ठा tegra_bpmp_channel *tx_channel, *rx_channel, *thपढ़ोed_channels;

	काष्ठा अणु
		अचिन्हित दीर्घ *allocated;
		अचिन्हित दीर्घ *busy;
		अचिन्हित पूर्णांक count;
		काष्ठा semaphore lock;
	पूर्ण thपढ़ोed;

	काष्ठा list_head mrqs;
	spinlock_t lock;

	काष्ठा tegra_bpmp_clk **घड़ीs;
	अचिन्हित पूर्णांक num_घड़ीs;

	काष्ठा reset_controller_dev rstc;

	काष्ठा genpd_onecell_data genpd;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_mirror;
#पूर्ण_अगर
पूर्ण;

काष्ठा tegra_bpmp_message अणु
	अचिन्हित पूर्णांक mrq;

	काष्ठा अणु
		स्थिर व्योम *data;
		माप_प्रकार size;
	पूर्ण tx;

	काष्ठा अणु
		व्योम *data;
		माप_प्रकार size;
		पूर्णांक ret;
	पूर्ण rx;
पूर्ण;

#अगर IS_ENABLED(CONFIG_TEGRA_BPMP)
काष्ठा tegra_bpmp *tegra_bpmp_get(काष्ठा device *dev);
व्योम tegra_bpmp_put(काष्ठा tegra_bpmp *bpmp);
पूर्णांक tegra_bpmp_transfer_atomic(काष्ठा tegra_bpmp *bpmp,
			       काष्ठा tegra_bpmp_message *msg);
पूर्णांक tegra_bpmp_transfer(काष्ठा tegra_bpmp *bpmp,
			काष्ठा tegra_bpmp_message *msg);
व्योम tegra_bpmp_mrq_वापस(काष्ठा tegra_bpmp_channel *channel, पूर्णांक code,
			   स्थिर व्योम *data, माप_प्रकार size);

पूर्णांक tegra_bpmp_request_mrq(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq,
			   tegra_bpmp_mrq_handler_t handler, व्योम *data);
व्योम tegra_bpmp_मुक्त_mrq(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq,
			 व्योम *data);
bool tegra_bpmp_mrq_is_supported(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq);
#अन्यथा
अटल अंतरभूत काष्ठा tegra_bpmp *tegra_bpmp_get(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण
अटल अंतरभूत व्योम tegra_bpmp_put(काष्ठा tegra_bpmp *bpmp)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक tegra_bpmp_transfer_atomic(काष्ठा tegra_bpmp *bpmp,
					     काष्ठा tegra_bpmp_message *msg)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक tegra_bpmp_transfer(काष्ठा tegra_bpmp *bpmp,
				      काष्ठा tegra_bpmp_message *msg)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत व्योम tegra_bpmp_mrq_वापस(काष्ठा tegra_bpmp_channel *channel,
					 पूर्णांक code, स्थिर व्योम *data,
					 माप_प्रकार size)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक tegra_bpmp_request_mrq(काष्ठा tegra_bpmp *bpmp,
					 अचिन्हित पूर्णांक mrq,
					 tegra_bpmp_mrq_handler_t handler,
					 व्योम *data)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत व्योम tegra_bpmp_मुक्त_mrq(काष्ठा tegra_bpmp *bpmp,
				       अचिन्हित पूर्णांक mrq, व्योम *data)
अणु
पूर्ण

अटल अंतरभूत bool tegra_bpmp_mrq_is_supported(काष्ठा tegra_bpmp *bpmp,
					      अचिन्हित पूर्णांक mrq)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

व्योम tegra_bpmp_handle_rx(काष्ठा tegra_bpmp *bpmp);

#अगर IS_ENABLED(CONFIG_CLK_TEGRA_BPMP)
पूर्णांक tegra_bpmp_init_घड़ीs(काष्ठा tegra_bpmp *bpmp);
#अन्यथा
अटल अंतरभूत पूर्णांक tegra_bpmp_init_घड़ीs(काष्ठा tegra_bpmp *bpmp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RESET_TEGRA_BPMP)
पूर्णांक tegra_bpmp_init_resets(काष्ठा tegra_bpmp *bpmp);
#अन्यथा
अटल अंतरभूत पूर्णांक tegra_bpmp_init_resets(काष्ठा tegra_bpmp *bpmp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SOC_TEGRA_POWERGATE_BPMP)
पूर्णांक tegra_bpmp_init_घातergates(काष्ठा tegra_bpmp *bpmp);
#अन्यथा
अटल अंतरभूत पूर्णांक tegra_bpmp_init_घातergates(काष्ठा tegra_bpmp *bpmp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
पूर्णांक tegra_bpmp_init_debugfs(काष्ठा tegra_bpmp *bpmp);
#अन्यथा
अटल अंतरभूत पूर्णांक tegra_bpmp_init_debugfs(काष्ठा tegra_bpmp *bpmp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर /* __SOC_TEGRA_BPMP_H */
