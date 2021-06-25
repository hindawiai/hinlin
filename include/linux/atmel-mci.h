<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ATMEL_MCI_H
#घोषणा __LINUX_ATMEL_MCI_H

#समावेश <linux/types.h>
#समावेश <linux/dmaengine.h>

#घोषणा ATMCI_MAX_NR_SLOTS	2

/**
 * काष्ठा mci_slot_pdata - board-specअगरic per-slot configuration
 * @bus_width: Number of data lines wired up the slot
 * @detect_pin: GPIO pin wired to the card detect चयन
 * @wp_pin: GPIO pin wired to the ग_लिखो protect sensor
 * @detect_is_active_high: The state of the detect pin when it is active
 * @non_removable: The slot is not removable, only detect once
 *
 * If a given slot is not present on the board, @bus_width should be
 * set to 0. The other fields are ignored in this हाल.
 *
 * Any pins that aren't available should be set to a negative value.
 *
 * Note that support क्रम multiple slots is experimental -- some cards
 * might get upset अगर we करोn't get the घड़ी management exactly right.
 * But in most हालs, it should work just fine.
 */
काष्ठा mci_slot_pdata अणु
	अचिन्हित पूर्णांक		bus_width;
	पूर्णांक			detect_pin;
	पूर्णांक			wp_pin;
	bool			detect_is_active_high;
	bool			non_removable;
पूर्ण;

/**
 * काष्ठा mci_platक्रमm_data - board-specअगरic MMC/SDcard configuration
 * @dma_slave: DMA slave पूर्णांकerface to use in data transfers.
 * @slot: Per-slot configuration data.
 */
काष्ठा mci_platक्रमm_data अणु
	व्योम			*dma_slave;
	dma_filter_fn		dma_filter;
	काष्ठा mci_slot_pdata	slot[ATMCI_MAX_NR_SLOTS];
पूर्ण;

#पूर्ण_अगर /* __LINUX_ATMEL_MCI_H */
