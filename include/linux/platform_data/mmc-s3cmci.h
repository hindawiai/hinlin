<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_MCI_H
#घोषणा _ARCH_MCI_H

/**
 * काष्ठा s3c24xx_mci_pdata - sd/mmc controller platक्रमm data
 * @no_wprotect: Set this to indicate there is no ग_लिखो-protect चयन.
 * @no_detect: Set this अगर there is no detect चयन.
 * @wprotect_invert: Invert the शेष sense of the ग_लिखो protect चयन.
 * @use_dma: Set to allow the use of DMA.
 * @gpio_detect: GPIO number क्रम the card detect line.
 * @gpio_wprotect: GPIO number क्रम the ग_लिखो protect line.
 * @ocr_avail: The mask of the available घातer states, non-zero to use.
 * @set_घातer: Callback to control the घातer mode.
 *
 * The @gpio_detect is used क्रम card detection when @no_wprotect is unset,
 * and the शेष sense is that 0 वापसed from gpio_get_value() means
 * that a card is inserted. If @detect_invert is set, then the value from
 * gpio_get_value() is inverted, which makes 1 mean card inserted.
 *
 * The driver will use @gpio_wprotect to संकेत whether the card is ग_लिखो
 * रक्षित अगर @no_wprotect is not set. A 0 वापसed from gpio_get_value()
 * means the card is पढ़ो/ग_लिखो, and 1 means पढ़ो-only. The @wprotect_invert
 * will invert the value वापसed from gpio_get_value().
 *
 * Card घातer is set by @ocr_availa, using MCC_VDD_ स्थिरants अगर it is set
 * to a non-zero value, otherwise the शेष of 3.2-3.4V is used.
 */
काष्ठा s3c24xx_mci_pdata अणु
	अचिन्हित पूर्णांक	no_wprotect:1;
	अचिन्हित पूर्णांक	no_detect:1;
	अचिन्हित पूर्णांक	wprotect_invert:1;
	अचिन्हित पूर्णांक	use_dma:1;

	अचिन्हित दीर्घ	ocr_avail;
	व्योम		(*set_घातer)(अचिन्हित अक्षर घातer_mode,
				     अचिन्हित लघु vdd);
	काष्ठा gpio_desc *bus[6];
पूर्ण;

/**
 * s3c24xx_mci_set_platdata - set platक्रमm data क्रम mmc/sdi device
 * @pdata: The platक्रमm data
 *
 * Copy the platक्रमm data supplied by @pdata so that this can be marked
 * __initdata.
 */
बाह्य व्योम s3c24xx_mci_def_set_घातer(अचिन्हित अक्षर घातer_mode, अचिन्हित लघु vdd);
बाह्य व्योम s3c24xx_mci_set_platdata(काष्ठा s3c24xx_mci_pdata *pdata);

#पूर्ण_अगर /* _ARCH_NCI_H */
