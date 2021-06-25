<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Common DAT related stuff
 */

#अगर_अघोषित DAT_H
#घोषणा DAT_H

/* Global DAT flags */
#घोषणा DAT_0_I2C_DEVICE		W0_BIT_(31)
#घोषणा DAT_0_SIR_REJECT		W0_BIT_(13)
#घोषणा DAT_0_IBI_PAYLOAD		W0_BIT_(12)

काष्ठा hci_dat_ops अणु
	पूर्णांक (*init)(काष्ठा i3c_hci *hci);
	व्योम (*cleanup)(काष्ठा i3c_hci *hci);
	पूर्णांक (*alloc_entry)(काष्ठा i3c_hci *hci);
	व्योम (*मुक्त_entry)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx);
	व्योम (*set_dynamic_addr)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx, u8 addr);
	व्योम (*set_अटल_addr)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx, u8 addr);
	व्योम (*set_flags)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx, u32 w0, u32 w1);
	व्योम (*clear_flags)(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx, u32 w0, u32 w1);
	पूर्णांक (*get_index)(काष्ठा i3c_hci *hci, u8 address);
पूर्ण;

बाह्य स्थिर काष्ठा hci_dat_ops mipi_i3c_hci_dat_v1;

#पूर्ण_अगर
