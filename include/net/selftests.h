<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_SELFTESTS
#घोषणा _NET_SELFTESTS

#समावेश <linux/ethtool.h>

#अगर IS_ENABLED(CONFIG_NET_SELFTESTS)

व्योम net_selftest(काष्ठा net_device *ndev, काष्ठा ethtool_test *etest,
		  u64 *buf);
पूर्णांक net_selftest_get_count(व्योम);
व्योम net_selftest_get_strings(u8 *data);

#अन्यथा

अटल अंतरभूत व्योम net_selftest(काष्ठा net_device *ndev, काष्ठा ethtool_test *etest,
				u64 *buf)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक net_selftest_get_count(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम net_selftest_get_strings(u8 *data)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _NET_SELFTESTS */
