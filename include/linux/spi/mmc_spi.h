<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPI_MMC_SPI_H
#घोषणा __LINUX_SPI_MMC_SPI_H

#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा device;
काष्ठा mmc_host;

/* Put this in platक्रमm_data of a device being used to manage an MMC/SD
 * card slot.  (Modeled after PXA mmc glue; see that क्रम usage examples.)
 *
 * REVISIT This is not a spi-specअगरic notion.  Any card slot should be
 * able to handle it.  If the MMC core करोesn't aकरोpt this kind of notion,
 * चयन the "struct device *" parameters over to "struct spi_device *".
 */
काष्ठा mmc_spi_platक्रमm_data अणु
	/* driver activation and (optional) card detect irq hookup */
	पूर्णांक (*init)(काष्ठा device *,
		irqवापस_t (*)(पूर्णांक, व्योम *),
		व्योम *);
	व्योम (*निकास)(काष्ठा device *, व्योम *);

	/* Capabilities to pass पूर्णांकo mmc core (e.g. MMC_CAP_NEEDS_POLL). */
	अचिन्हित दीर्घ caps;
	अचिन्हित दीर्घ caps2;

	/* how दीर्घ to debounce card detect, in msecs */
	u16 detect_delay;

	/* घातer management */
	u16 घातerup_msecs;		/* delay of up to 250 msec */
	u32 ocr_mask;			/* available voltages */
	व्योम (*setघातer)(काष्ठा device *, अचिन्हित पूर्णांक maskval);
पूर्ण;

बाह्य काष्ठा mmc_spi_platक्रमm_data *mmc_spi_get_pdata(काष्ठा spi_device *spi);
बाह्य व्योम mmc_spi_put_pdata(काष्ठा spi_device *spi);

#पूर्ण_अगर /* __LINUX_SPI_MMC_SPI_H */
