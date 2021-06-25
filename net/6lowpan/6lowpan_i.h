<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __6LOWPAN_I_H
#घोषणा __6LOWPAN_I_H

#समावेश <linux/netdevice.h>

#समावेश <net/6lowpan.h>

/* caller need to be sure it's dev->type is ARPHRD_6LOWPAN */
अटल अंतरभूत bool lowpan_is_ll(स्थिर काष्ठा net_device *dev,
				क्रमागत lowpan_lltypes lltype)
अणु
	वापस lowpan_dev(dev)->lltype == lltype;
पूर्ण

बाह्य स्थिर काष्ठा ndisc_ops lowpan_ndisc_ops;

पूर्णांक addrconf_अगरid_802154_6lowpan(u8 *eui, काष्ठा net_device *dev);

#अगर_घोषित CONFIG_6LOWPAN_DEBUGFS
व्योम lowpan_dev_debugfs_init(काष्ठा net_device *dev);
व्योम lowpan_dev_debugfs_निकास(काष्ठा net_device *dev);

व्योम __init lowpan_debugfs_init(व्योम);
व्योम lowpan_debugfs_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम lowpan_dev_debugfs_init(काष्ठा net_device *dev) अणु पूर्ण
अटल अंतरभूत व्योम lowpan_dev_debugfs_निकास(काष्ठा net_device *dev) अणु पूर्ण

अटल अंतरभूत व्योम __init lowpan_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम lowpan_debugfs_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_6LOWPAN_DEBUGFS */

#पूर्ण_अगर /* __6LOWPAN_I_H */
