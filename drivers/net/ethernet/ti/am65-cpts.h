<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* TI K3 AM65 CPTS driver पूर्णांकerface
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 */

#अगर_अघोषित K3_CPTS_H_
#घोषणा K3_CPTS_H_

#समावेश <linux/device.h>
#समावेश <linux/of.h>

काष्ठा am65_cpts;

काष्ठा am65_cpts_estf_cfg अणु
	u64 ns_period;
	u64 ns_start;
पूर्ण;

#अगर IS_ENABLED(CONFIG_TI_K3_AM65_CPTS)
काष्ठा am65_cpts *am65_cpts_create(काष्ठा device *dev, व्योम __iomem *regs,
				   काष्ठा device_node *node);
पूर्णांक am65_cpts_phc_index(काष्ठा am65_cpts *cpts);
व्योम am65_cpts_tx_बारtamp(काष्ठा am65_cpts *cpts, काष्ठा sk_buff *skb);
व्योम am65_cpts_prep_tx_बारtamp(काष्ठा am65_cpts *cpts, काष्ठा sk_buff *skb);
व्योम am65_cpts_rx_enable(काष्ठा am65_cpts *cpts, bool en);
u64 am65_cpts_ns_समय_लो(काष्ठा am65_cpts *cpts);
पूर्णांक am65_cpts_estf_enable(काष्ठा am65_cpts *cpts, पूर्णांक idx,
			  काष्ठा am65_cpts_estf_cfg *cfg);
व्योम am65_cpts_estf_disable(काष्ठा am65_cpts *cpts, पूर्णांक idx);
#अन्यथा
अटल अंतरभूत काष्ठा am65_cpts *am65_cpts_create(काष्ठा device *dev,
						 व्योम __iomem *regs,
						 काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक am65_cpts_phc_index(काष्ठा am65_cpts *cpts)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम am65_cpts_tx_बारtamp(काष्ठा am65_cpts *cpts,
					  काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम am65_cpts_prep_tx_बारtamp(काष्ठा am65_cpts *cpts,
					       काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम am65_cpts_rx_enable(काष्ठा am65_cpts *cpts, bool en)
अणु
पूर्ण

अटल अंतरभूत s64 am65_cpts_ns_समय_लो(काष्ठा am65_cpts *cpts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक am65_cpts_estf_enable(काष्ठा am65_cpts *cpts, पूर्णांक idx,
					काष्ठा am65_cpts_estf_cfg *cfg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम am65_cpts_estf_disable(काष्ठा am65_cpts *cpts, पूर्णांक idx)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* K3_CPTS_H_ */
