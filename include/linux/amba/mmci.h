<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/linux/amba/mmci.h
 */
#अगर_अघोषित AMBA_MMCI_H
#घोषणा AMBA_MMCI_H

#समावेश <linux/mmc/host.h>

/**
 * काष्ठा mmci_platक्रमm_data - platक्रमm configuration क्रम the MMCI
 * (also known as PL180) block.
 * @ocr_mask: available voltages on the 4 pins from the block, this
 * is ignored अगर a regulator is used, see the MMC_VDD_* masks in
 * mmc/host.h
 * @ios_handler: a callback function to act on specfic ios changes,
 * used क्रम example to control a levelshअगरter
 * mask पूर्णांकo a value to be binary (or set some other custom bits
 * in MMCIPWR) or:ed and written पूर्णांकo the MMCIPWR रेजिस्टर of the
 * block.  May also control बाह्यal घातer based on the घातer_mode.
 * @status: अगर no GPIO line was given to the block in this function will
 * be called to determine whether a card is present in the MMC slot or not
 */
काष्ठा mmci_platक्रमm_data अणु
	अचिन्हित पूर्णांक ocr_mask;
	पूर्णांक (*ios_handler)(काष्ठा device *, काष्ठा mmc_ios *);
	अचिन्हित पूर्णांक (*status)(काष्ठा device *);
पूर्ण;

#पूर्ण_अगर
