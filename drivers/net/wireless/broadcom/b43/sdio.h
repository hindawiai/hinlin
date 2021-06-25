<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_SDIO_H_
#घोषणा B43_SDIO_H_

#समावेश <linux/ssb/ssb.h>

काष्ठा b43_wldev;


#अगर_घोषित CONFIG_B43_SDIO

काष्ठा b43_sdio अणु
	काष्ठा ssb_bus ssb;
	व्योम *irq_handler_opaque;
	व्योम (*irq_handler)(काष्ठा b43_wldev *dev);
पूर्ण;

पूर्णांक b43_sdio_request_irq(काष्ठा b43_wldev *dev,
			 व्योम (*handler)(काष्ठा b43_wldev *dev));
व्योम b43_sdio_मुक्त_irq(काष्ठा b43_wldev *dev);

पूर्णांक b43_sdio_init(व्योम);
व्योम b43_sdio_निकास(व्योम);


#अन्यथा /* CONFIG_B43_SDIO */


अटल अंतरभूत पूर्णांक b43_sdio_request_irq(काष्ठा b43_wldev *dev,
			 व्योम (*handler)(काष्ठा b43_wldev *dev))
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम b43_sdio_मुक्त_irq(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक b43_sdio_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम b43_sdio_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_B43_SDIO */
#पूर्ण_अगर /* B43_SDIO_H_ */
