<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OF helpers क्रम network devices.
 */

#अगर_अघोषित __LINUX_OF_NET_H
#घोषणा __LINUX_OF_NET_H

#समावेश <linux/phy.h>

#अगर_घोषित CONFIG_OF_NET
#समावेश <linux/of.h>

काष्ठा net_device;
बाह्य पूर्णांक of_get_phy_mode(काष्ठा device_node *np, phy_पूर्णांकerface_t *पूर्णांकerface);
बाह्य पूर्णांक of_get_mac_address(काष्ठा device_node *np, u8 *mac);
बाह्य काष्ठा net_device *of_find_net_device_by_node(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत पूर्णांक of_get_phy_mode(काष्ठा device_node *np,
				  phy_पूर्णांकerface_t *पूर्णांकerface)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_get_mac_address(काष्ठा device_node *np, u8 *mac)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा net_device *of_find_net_device_by_node(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_OF_NET_H */
