<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_ARCH_MMC_H
#घोषणा ASMARM_ARCH_MMC_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mmc/host.h>

काष्ठा device;

/* board specअगरic SDHC data, optional.
 * If not present, a writable card with 3,3V is assumed.
 */
काष्ठा imxmmc_platक्रमm_data अणु
	/* Return values क्रम the get_ro callback should be:
	 *   0 क्रम a पढ़ो/ग_लिखो card
	 *   1 क्रम a पढ़ो-only card
	 *   -ENOSYS when not supported (equal to शून्य callback)
	 *   or a negative त्रुटि_सं value when something bad happened
	 */
	पूर्णांक (*get_ro)(काष्ठा device *);

	/* board specअगरic hook to (de)initialize the SD slot.
	 * The board code can call 'handler' on a card detection
	 * change giving data as argument.
	 */
	पूर्णांक (*init)(काष्ठा device *dev, irq_handler_t handler, व्योम *data);
	व्योम (*निकास)(काष्ठा device *dev, व्योम *data);

	/* available voltages. If not given, assume
	 * MMC_VDD_32_33 | MMC_VDD_33_34
	 */
	अचिन्हित पूर्णांक ocr_avail;

	/* adjust slot voltage */
	व्योम (*setघातer)(काष्ठा device *, अचिन्हित पूर्णांक vdd);

	/* enable card detect using DAT3 */
	पूर्णांक dat3_card_detect;
पूर्ण;

#पूर्ण_अगर
