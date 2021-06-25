<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पन.स>

#समावेश "hci.h"
#समावेश "dat.h"


/*
 * Device Address Table Structure
 */

#घोषणा DAT_1_AUTOCMD_HDR_CODE		W1_MASK(58, 51)
#घोषणा DAT_1_AUTOCMD_MODE		W1_MASK(50, 48)
#घोषणा DAT_1_AUTOCMD_VALUE		W1_MASK(47, 40)
#घोषणा DAT_1_AUTOCMD_MASK		W1_MASK(39, 32)
/*	DAT_0_I2C_DEVICE		W0_BIT_(31) */
#घोषणा DAT_0_DEV_NACK_RETRY_CNT	W0_MASK(30, 29)
#घोषणा DAT_0_RING_ID			W0_MASK(28, 26)
#घोषणा DAT_0_DYNADDR_PARITY		W0_BIT_(23)
#घोषणा DAT_0_DYNAMIC_ADDRESS		W0_MASK(22, 16)
#घोषणा DAT_0_TS			W0_BIT_(15)
#घोषणा DAT_0_MR_REJECT			W0_BIT_(14)
/*	DAT_0_SIR_REJECT		W0_BIT_(13) */
/*	DAT_0_IBI_PAYLOAD		W0_BIT_(12) */
#घोषणा DAT_0_STATIC_ADDRESS		W0_MASK(6, 0)

#घोषणा dat_w0_पढ़ो(i)		पढ़ोl(hci->DAT_regs + (i) * 8)
#घोषणा dat_w1_पढ़ो(i)		पढ़ोl(hci->DAT_regs + (i) * 8 + 4)
#घोषणा dat_w0_ग_लिखो(i, v)	ग_लिखोl(v, hci->DAT_regs + (i) * 8)
#घोषणा dat_w1_ग_लिखो(i, v)	ग_लिखोl(v, hci->DAT_regs + (i) * 8 + 4)

अटल अंतरभूत bool dynaddr_parity(अचिन्हित पूर्णांक addr)
अणु
	addr |= 1 << 7;
	addr += addr >> 4;
	addr += addr >> 2;
	addr += addr >> 1;
	वापस (addr & 1);
पूर्ण

अटल पूर्णांक hci_dat_v1_init(काष्ठा i3c_hci *hci)
अणु
	अचिन्हित पूर्णांक dat_idx;

	अगर (!hci->DAT_regs) अणु
		dev_err(&hci->master.dev,
			"only DAT in register space is supported at the moment\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (hci->DAT_entry_size != 8) अणु
		dev_err(&hci->master.dev,
			"only 8-bytes DAT entries are supported at the moment\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* use a biपंचांगap क्रम faster मुक्त slot search */
	hci->DAT_data = biपंचांगap_zalloc(hci->DAT_entries, GFP_KERNEL);
	अगर (!hci->DAT_data)
		वापस -ENOMEM;

	/* clear them */
	क्रम (dat_idx = 0; dat_idx < hci->DAT_entries; dat_idx++) अणु
		dat_w0_ग_लिखो(dat_idx, 0);
		dat_w1_ग_लिखो(dat_idx, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hci_dat_v1_cleanup(काष्ठा i3c_hci *hci)
अणु
	biपंचांगap_मुक्त(hci->DAT_data);
	hci->DAT_data = शून्य;
पूर्ण

अटल पूर्णांक hci_dat_v1_alloc_entry(काष्ठा i3c_hci *hci)
अणु
	अचिन्हित पूर्णांक dat_idx;

	dat_idx = find_first_zero_bit(hci->DAT_data, hci->DAT_entries);
	अगर (dat_idx >= hci->DAT_entries)
		वापस -ENOENT;
	__set_bit(dat_idx, hci->DAT_data);

	/* शेष flags */
	dat_w0_ग_लिखो(dat_idx, DAT_0_SIR_REJECT | DAT_0_MR_REJECT);

	वापस dat_idx;
पूर्ण

अटल व्योम hci_dat_v1_मुक्त_entry(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx)
अणु
	dat_w0_ग_लिखो(dat_idx, 0);
	dat_w1_ग_लिखो(dat_idx, 0);
	__clear_bit(dat_idx, hci->DAT_data);
पूर्ण

अटल व्योम hci_dat_v1_set_dynamic_addr(काष्ठा i3c_hci *hci,
					अचिन्हित पूर्णांक dat_idx, u8 address)
अणु
	u32 dat_w0;

	dat_w0 = dat_w0_पढ़ो(dat_idx);
	dat_w0 &= ~(DAT_0_DYNAMIC_ADDRESS | DAT_0_DYNADDR_PARITY);
	dat_w0 |= FIELD_PREP(DAT_0_DYNAMIC_ADDRESS, address) |
		  (dynaddr_parity(address) ? DAT_0_DYNADDR_PARITY : 0);
	dat_w0_ग_लिखो(dat_idx, dat_w0);
पूर्ण

अटल व्योम hci_dat_v1_set_अटल_addr(काष्ठा i3c_hci *hci,
				       अचिन्हित पूर्णांक dat_idx, u8 address)
अणु
	u32 dat_w0;

	dat_w0 = dat_w0_पढ़ो(dat_idx);
	dat_w0 &= ~DAT_0_STATIC_ADDRESS;
	dat_w0 |= FIELD_PREP(DAT_0_STATIC_ADDRESS, address);
	dat_w0_ग_लिखो(dat_idx, dat_w0);
पूर्ण

अटल व्योम hci_dat_v1_set_flags(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx,
				 u32 w0_flags, u32 w1_flags)
अणु
	u32 dat_w0, dat_w1;

	dat_w0 = dat_w0_पढ़ो(dat_idx);
	dat_w1 = dat_w1_पढ़ो(dat_idx);
	dat_w0 |= w0_flags;
	dat_w1 |= w1_flags;
	dat_w0_ग_लिखो(dat_idx, dat_w0);
	dat_w1_ग_लिखो(dat_idx, dat_w1);
पूर्ण

अटल व्योम hci_dat_v1_clear_flags(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dat_idx,
				   u32 w0_flags, u32 w1_flags)
अणु
	u32 dat_w0, dat_w1;

	dat_w0 = dat_w0_पढ़ो(dat_idx);
	dat_w1 = dat_w1_पढ़ो(dat_idx);
	dat_w0 &= ~w0_flags;
	dat_w1 &= ~w1_flags;
	dat_w0_ग_लिखो(dat_idx, dat_w0);
	dat_w1_ग_लिखो(dat_idx, dat_w1);
पूर्ण

अटल पूर्णांक hci_dat_v1_get_index(काष्ठा i3c_hci *hci, u8 dev_addr)
अणु
	अचिन्हित पूर्णांक dat_idx;
	u32 dat_w0;

	क्रम (dat_idx = find_first_bit(hci->DAT_data, hci->DAT_entries);
	     dat_idx < hci->DAT_entries;
	     dat_idx = find_next_bit(hci->DAT_data, hci->DAT_entries, dat_idx)) अणु
		dat_w0 = dat_w0_पढ़ो(dat_idx);
		अगर (FIELD_GET(DAT_0_DYNAMIC_ADDRESS, dat_w0) == dev_addr)
			वापस dat_idx;
	पूर्ण

	वापस -ENODEV;
पूर्ण

स्थिर काष्ठा hci_dat_ops mipi_i3c_hci_dat_v1 = अणु
	.init			= hci_dat_v1_init,
	.cleanup		= hci_dat_v1_cleanup,
	.alloc_entry		= hci_dat_v1_alloc_entry,
	.मुक्त_entry		= hci_dat_v1_मुक्त_entry,
	.set_dynamic_addr	= hci_dat_v1_set_dynamic_addr,
	.set_अटल_addr	= hci_dat_v1_set_अटल_addr,
	.set_flags		= hci_dat_v1_set_flags,
	.clear_flags		= hci_dat_v1_clear_flags,
	.get_index		= hci_dat_v1_get_index,
पूर्ण;
