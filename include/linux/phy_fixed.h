<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PHY_FIXED_H
#घोषणा __PHY_FIXED_H

काष्ठा fixed_phy_status अणु
	पूर्णांक link;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक छोड़ो;
	पूर्णांक asym_छोड़ो;
पूर्ण;

काष्ठा device_node;
काष्ठा gpio_desc;

#अगर IS_ENABLED(CONFIG_FIXED_PHY)
बाह्य पूर्णांक fixed_phy_change_carrier(काष्ठा net_device *dev, bool new_carrier);
बाह्य पूर्णांक fixed_phy_add(अचिन्हित पूर्णांक irq, पूर्णांक phy_id,
			 काष्ठा fixed_phy_status *status);
बाह्य काष्ठा phy_device *fixed_phy_रेजिस्टर(अचिन्हित पूर्णांक irq,
					     काष्ठा fixed_phy_status *status,
					     काष्ठा device_node *np);

बाह्य काष्ठा phy_device *
fixed_phy_रेजिस्टर_with_gpiod(अचिन्हित पूर्णांक irq,
			      काष्ठा fixed_phy_status *status,
			      काष्ठा gpio_desc *gpiod);

बाह्य व्योम fixed_phy_unरेजिस्टर(काष्ठा phy_device *phydev);
बाह्य पूर्णांक fixed_phy_set_link_update(काष्ठा phy_device *phydev,
			पूर्णांक (*link_update)(काष्ठा net_device *,
					   काष्ठा fixed_phy_status *));
#अन्यथा
अटल अंतरभूत पूर्णांक fixed_phy_add(अचिन्हित पूर्णांक irq, पूर्णांक phy_id,
				काष्ठा fixed_phy_status *status)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत काष्ठा phy_device *fixed_phy_रेजिस्टर(अचिन्हित पूर्णांक irq,
						काष्ठा fixed_phy_status *status,
						काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा phy_device *
fixed_phy_रेजिस्टर_with_gpiod(अचिन्हित पूर्णांक irq,
			      काष्ठा fixed_phy_status *status,
			      काष्ठा gpio_desc *gpiod)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम fixed_phy_unरेजिस्टर(काष्ठा phy_device *phydev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक fixed_phy_set_link_update(काष्ठा phy_device *phydev,
			पूर्णांक (*link_update)(काष्ठा net_device *,
					   काष्ठा fixed_phy_status *))
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक fixed_phy_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_FIXED_PHY */

#पूर्ण_अगर /* __PHY_FIXED_H */
