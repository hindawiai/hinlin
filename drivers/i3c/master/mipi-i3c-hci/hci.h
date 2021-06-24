<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Common HCI stuff
 */

#अगर_अघोषित HCI_H
#घोषणा HCI_H


/* Handy logging macro to save on line length */
#घोषणा DBG(x, ...) pr_devel("%s: " x "\n", __func__, ##__VA_ARGS__)

/* 32-bit word aware bit and mask macros */
#घोषणा W0_MASK(h, l)  GENMASK((h) - 0,  (l) - 0)
#घोषणा W1_MASK(h, l)  GENMASK((h) - 32, (l) - 32)
#घोषणा W2_MASK(h, l)  GENMASK((h) - 64, (l) - 64)
#घोषणा W3_MASK(h, l)  GENMASK((h) - 96, (l) - 96)

/* Same क्रम single bit macros (trailing _ to align with W*_MASK width) */
#घोषणा W0_BIT_(x)  BIT((x) - 0)
#घोषणा W1_BIT_(x)  BIT((x) - 32)
#घोषणा W2_BIT_(x)  BIT((x) - 64)
#घोषणा W3_BIT_(x)  BIT((x) - 96)


काष्ठा hci_cmd_ops;

/* Our मुख्य काष्ठाure */
काष्ठा i3c_hci अणु
	काष्ठा i3c_master_controller master;
	व्योम __iomem *base_regs;
	व्योम __iomem *DAT_regs;
	व्योम __iomem *DCT_regs;
	व्योम __iomem *RHS_regs;
	व्योम __iomem *PIO_regs;
	व्योम __iomem *EXTCAPS_regs;
	व्योम __iomem *AUTOCMD_regs;
	व्योम __iomem *DEBUG_regs;
	स्थिर काष्ठा hci_io_ops *io;
	व्योम *io_data;
	स्थिर काष्ठा hci_cmd_ops *cmd;
	atomic_t next_cmd_tid;
	u32 caps;
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक DAT_entries;
	अचिन्हित पूर्णांक DAT_entry_size;
	व्योम *DAT_data;
	अचिन्हित पूर्णांक DCT_entries;
	अचिन्हित पूर्णांक DCT_entry_size;
	u8 version_major;
	u8 version_minor;
	u8 revision;
	u32 venकरोr_mipi_id;
	u32 venकरोr_version_id;
	u32 venकरोr_product_id;
	व्योम *venकरोr_data;
पूर्ण;


/*
 * Structure to represent a master initiated transfer.
 * The rnw, data and data_len fields must be initialized beक्रमe calling any
 * hci->cmd->*() method. The cmd method will initialize cmd_desc[] and
 * possibly modअगरy (clear) the data field. Then xfer->cmd_desc[0] can
 * be augmented with CMD_0_ROC and/or CMD_0_TOC.
 * The completion field needs to be initialized beक्रमe queueing with
 * hci->io->queue_xfer(), and requires CMD_0_ROC to be set.
 */
काष्ठा hci_xfer अणु
	u32 cmd_desc[4];
	u32 response;
	bool rnw;
	व्योम *data;
	अचिन्हित पूर्णांक data_len;
	अचिन्हित पूर्णांक cmd_tid;
	काष्ठा completion *completion;
	जोड़ अणु
		काष्ठा अणु
			/* PIO specअगरic */
			काष्ठा hci_xfer *next_xfer;
			काष्ठा hci_xfer *next_data;
			काष्ठा hci_xfer *next_resp;
			अचिन्हित पूर्णांक data_left;
			u32 data_word_beक्रमe_partial;
		पूर्ण;
		काष्ठा अणु
			/* DMA specअगरic */
			dma_addr_t data_dma;
			पूर्णांक ring_number;
			पूर्णांक ring_entry;
		पूर्ण;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा hci_xfer *hci_alloc_xfer(अचिन्हित पूर्णांक n)
अणु
	वापस kzalloc(माप(काष्ठा hci_xfer) * n, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम hci_मुक्त_xfer(काष्ठा hci_xfer *xfer, अचिन्हित पूर्णांक n)
अणु
	kमुक्त(xfer);
पूर्ण


/* This असलtracts PIO vs DMA operations */
काष्ठा hci_io_ops अणु
	bool (*irq_handler)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक mask);
	पूर्णांक (*queue_xfer)(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer, पूर्णांक n);
	bool (*dequeue_xfer)(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer, पूर्णांक n);
	पूर्णांक (*request_ibi)(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev,
			   स्थिर काष्ठा i3c_ibi_setup *req);
	व्योम (*मुक्त_ibi)(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev);
	व्योम (*recycle_ibi_slot)(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev,
				काष्ठा i3c_ibi_slot *slot);
	पूर्णांक (*init)(काष्ठा i3c_hci *hci);
	व्योम (*cleanup)(काष्ठा i3c_hci *hci);
पूर्ण;

बाह्य स्थिर काष्ठा hci_io_ops mipi_i3c_hci_pio;
बाह्य स्थिर काष्ठा hci_io_ops mipi_i3c_hci_dma;


/* Our per device master निजी data */
काष्ठा i3c_hci_dev_data अणु
	पूर्णांक dat_idx;
	व्योम *ibi_data;
पूर्ण;


/* list of quirks */
#घोषणा HCI_QUIRK_RAW_CCC	BIT(1)	/* CCC framing must be explicit */


/* global functions */
व्योम mipi_i3c_hci_resume(काष्ठा i3c_hci *hci);
व्योम mipi_i3c_hci_pio_reset(काष्ठा i3c_hci *hci);
व्योम mipi_i3c_hci_dct_index_reset(काष्ठा i3c_hci *hci);

#पूर्ण_अगर
