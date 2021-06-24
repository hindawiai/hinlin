<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_AHCI_REMAP_H
#घोषणा _LINUX_AHCI_REMAP_H

#समावेश <linux/sizes.h>

#घोषणा AHCI_VSCAP		0xa4
#घोषणा AHCI_REMAP_CAP		0x800

/* device class code */
#घोषणा AHCI_REMAP_N_DCC	0x880

/* remap-device base relative to ahci-bar */
#घोषणा AHCI_REMAP_N_OFFSET	SZ_16K
#घोषणा AHCI_REMAP_N_SIZE	SZ_16K

#घोषणा AHCI_MAX_REMAP		3

अटल अंतरभूत अचिन्हित पूर्णांक ahci_remap_dcc(पूर्णांक i)
अणु
	वापस AHCI_REMAP_N_DCC + i * 0x80;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ahci_remap_base(पूर्णांक i)
अणु
	वापस AHCI_REMAP_N_OFFSET + i * AHCI_REMAP_N_SIZE;
पूर्ण

#पूर्ण_अगर /* _LINUX_AHCI_REMAP_H */
