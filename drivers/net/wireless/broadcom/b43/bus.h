<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_BUS_H_
#घोषणा B43_BUS_H_

क्रमागत b43_bus_type अणु
#अगर_घोषित CONFIG_B43_BCMA
	B43_BUS_BCMA,
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	B43_BUS_SSB,
#पूर्ण_अगर
पूर्ण;

काष्ठा b43_bus_dev अणु
	क्रमागत b43_bus_type bus_type;
	जोड़ अणु
		काष्ठा bcma_device *bdev;
		काष्ठा ssb_device *sdev;
	पूर्ण;

	पूर्णांक (*bus_may_घातerकरोwn)(काष्ठा b43_bus_dev *dev);
	पूर्णांक (*bus_घातerup)(काष्ठा b43_bus_dev *dev, bool dynamic_pctl);
	पूर्णांक (*device_is_enabled)(काष्ठा b43_bus_dev *dev);
	व्योम (*device_enable)(काष्ठा b43_bus_dev *dev,
			      u32 core_specअगरic_flags);
	व्योम (*device_disable)(काष्ठा b43_bus_dev *dev,
			       u32 core_specअगरic_flags);

	u16 (*पढ़ो16)(काष्ठा b43_bus_dev *dev, u16 offset);
	u32 (*पढ़ो32)(काष्ठा b43_bus_dev *dev, u16 offset);
	व्योम (*ग_लिखो16)(काष्ठा b43_bus_dev *dev, u16 offset, u16 value);
	व्योम (*ग_लिखो32)(काष्ठा b43_bus_dev *dev, u16 offset, u32 value);
	व्योम (*block_पढ़ो)(काष्ठा b43_bus_dev *dev, व्योम *buffer,
			   माप_प्रकार count, u16 offset, u8 reg_width);
	व्योम (*block_ग_लिखो)(काष्ठा b43_bus_dev *dev, स्थिर व्योम *buffer,
			    माप_प्रकार count, u16 offset, u8 reg_width);
	bool flush_ग_लिखोs;

	काष्ठा device *dev;
	काष्ठा device *dma_dev;
	अचिन्हित पूर्णांक irq;

	u16 board_venकरोr;
	u16 board_type;
	u16 board_rev;

	u16 chip_id;
	u8 chip_rev;
	u8 chip_pkg;

	काष्ठा ssb_sprom *bus_sprom;

	u16 core_id;
	u8 core_rev;
पूर्ण;

अटल अंतरभूत bool b43_bus_host_is_pcmcia(काष्ठा b43_bus_dev *dev)
अणु
#अगर_घोषित CONFIG_B43_SSB
	वापस (dev->bus_type == B43_BUS_SSB &&
		dev->sdev->bus->bustype == SSB_BUSTYPE_PCMCIA);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool b43_bus_host_is_pci(काष्ठा b43_bus_dev *dev)
अणु
#अगर_घोषित CONFIG_B43_BCMA
	अगर (dev->bus_type == B43_BUS_BCMA)
		वापस (dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI);
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	अगर (dev->bus_type == B43_BUS_SSB)
		वापस (dev->sdev->bus->bustype == SSB_BUSTYPE_PCI);
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool b43_bus_host_is_sdio(काष्ठा b43_bus_dev *dev)
अणु
#अगर_घोषित CONFIG_B43_SSB
	वापस (dev->bus_type == B43_BUS_SSB &&
		dev->sdev->bus->bustype == SSB_BUSTYPE_SDIO);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

काष्ठा b43_bus_dev *b43_bus_dev_bcma_init(काष्ठा bcma_device *core);
काष्ठा b43_bus_dev *b43_bus_dev_ssb_init(काष्ठा ssb_device *sdev);

व्योम *b43_bus_get_wldev(काष्ठा b43_bus_dev *dev);
व्योम b43_bus_set_wldev(काष्ठा b43_bus_dev *dev, व्योम *data);

#पूर्ण_अगर /* B43_BUS_H_ */
