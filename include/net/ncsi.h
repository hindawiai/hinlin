<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_NCSI_H
#घोषणा __NET_NCSI_H

/*
 * The NCSI device states seen from बाह्यal. More NCSI device states are
 * only visible पूर्णांकernally (in net/ncsi/पूर्णांकernal.h). When the NCSI device
 * is रेजिस्टरed, it's in ncsi_dev_state_रेजिस्टरed state. The state
 * ncsi_dev_state_start is used to drive to choose active package and
 * channel. After that, its state is changed to ncsi_dev_state_functional.
 *
 * The state ncsi_dev_state_stop helps to shut करोwn the currently active
 * package and channel जबतक ncsi_dev_state_config helps to reconfigure
 * them.
 */
क्रमागत अणु
	ncsi_dev_state_रेजिस्टरed	= 0x0000,
	ncsi_dev_state_functional	= 0x0100,
	ncsi_dev_state_probe		= 0x0200,
	ncsi_dev_state_config		= 0x0300,
	ncsi_dev_state_suspend		= 0x0400,
पूर्ण;

काष्ठा ncsi_dev अणु
	पूर्णांक               state;
	पूर्णांक		  link_up;
	काष्ठा net_device *dev;
	व्योम		  (*handler)(काष्ठा ncsi_dev *ndev);
पूर्ण;

#अगर_घोषित CONFIG_NET_NCSI
पूर्णांक ncsi_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid);
पूर्णांक ncsi_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid);
काष्ठा ncsi_dev *ncsi_रेजिस्टर_dev(काष्ठा net_device *dev,
				   व्योम (*notअगरier)(काष्ठा ncsi_dev *nd));
पूर्णांक ncsi_start_dev(काष्ठा ncsi_dev *nd);
व्योम ncsi_stop_dev(काष्ठा ncsi_dev *nd);
व्योम ncsi_unरेजिस्टर_dev(काष्ठा ncsi_dev *nd);
#अन्यथा /* !CONFIG_NET_NCSI */
अटल अंतरभूत पूर्णांक ncsi_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक ncsi_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा ncsi_dev *ncsi_रेजिस्टर_dev(काष्ठा net_device *dev,
					व्योम (*notअगरier)(काष्ठा ncsi_dev *nd))
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ncsi_start_dev(काष्ठा ncsi_dev *nd)
अणु
	वापस -ENOTTY;
पूर्ण

अटल व्योम ncsi_stop_dev(काष्ठा ncsi_dev *nd)
अणु
पूर्ण

अटल अंतरभूत व्योम ncsi_unरेजिस्टर_dev(काष्ठा ncsi_dev *nd)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_NCSI */

#पूर्ण_अगर /* __NET_NCSI_H */
