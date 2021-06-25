<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Infineon Technologies AG
 * Copyright (C) 2016 STMicroelectronics SAS
 */

#अगर_अघोषित TPM_TIS_SPI_H
#घोषणा TPM_TIS_SPI_H

#समावेश "tpm_tis_core.h"

काष्ठा tpm_tis_spi_phy अणु
	काष्ठा tpm_tis_data priv;
	काष्ठा spi_device *spi_device;
	पूर्णांक (*flow_control)(काष्ठा tpm_tis_spi_phy *phy,
			     काष्ठा spi_transfer *xfer);
	काष्ठा completion पढ़ोy;
	अचिन्हित दीर्घ wake_after;

	u8 *iobuf;
पूर्ण;

अटल अंतरभूत काष्ठा tpm_tis_spi_phy *to_tpm_tis_spi_phy(काष्ठा tpm_tis_data *data)
अणु
	वापस container_of(data, काष्ठा tpm_tis_spi_phy, priv);
पूर्ण

बाह्य पूर्णांक tpm_tis_spi_init(काष्ठा spi_device *spi, काष्ठा tpm_tis_spi_phy *phy,
			    पूर्णांक irq, स्थिर काष्ठा tpm_tis_phy_ops *phy_ops);

बाह्य पूर्णांक tpm_tis_spi_transfer(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
				u8 *in, स्थिर u8 *out);

बाह्य पूर्णांक tpm_tis_spi_पढ़ो16(काष्ठा tpm_tis_data *data, u32 addr, u16 *result);
बाह्य पूर्णांक tpm_tis_spi_पढ़ो32(काष्ठा tpm_tis_data *data, u32 addr, u32 *result);
बाह्य पूर्णांक tpm_tis_spi_ग_लिखो32(काष्ठा tpm_tis_data *data, u32 addr, u32 value);

#अगर_घोषित CONFIG_TCG_TIS_SPI_CR50
बाह्य पूर्णांक cr50_spi_probe(काष्ठा spi_device *spi);
#अन्यथा
अटल अंतरभूत पूर्णांक cr50_spi_probe(काष्ठा spi_device *spi)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_TCG_TIS_SPI_CR50)
बाह्य पूर्णांक tpm_tis_spi_resume(काष्ठा device *dev);
#अन्यथा
#घोषणा tpm_tis_spi_resume	शून्य
#पूर्ण_अगर

#पूर्ण_अगर
