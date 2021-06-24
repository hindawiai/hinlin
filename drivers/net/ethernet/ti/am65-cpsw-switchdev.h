<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित DRIVERS_NET_ETHERNET_TI_AM65_CPSW_SWITCHDEV_H_
#घोषणा DRIVERS_NET_ETHERNET_TI_AM65_CPSW_SWITCHDEV_H_

#समावेश <linux/skbuff.h>

#अगर IS_ENABLED(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV)
अटल अंतरभूत व्योम am65_cpsw_nuss_set_offload_fwd_mark(काष्ठा sk_buff *skb, bool val)
अणु
	skb->offload_fwd_mark = val;
पूर्ण

पूर्णांक am65_cpsw_चयनdev_रेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw);
व्योम am65_cpsw_चयनdev_unरेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw);
#अन्यथा
अटल अंतरभूत पूर्णांक am65_cpsw_चयनdev_रेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम am65_cpsw_चयनdev_unरेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
पूर्ण

अटल अंतरभूत व्योम am65_cpsw_nuss_set_offload_fwd_mark(काष्ठा sk_buff *skb, bool val)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* DRIVERS_NET_ETHERNET_TI_AM65_CPSW_SWITCHDEV_H_ */
