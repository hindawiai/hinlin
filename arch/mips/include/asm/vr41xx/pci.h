<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Include file क्रम NEC VR4100 series PCI Control Unit.
 *
 *  Copyright (C) 2004-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __NEC_VR41XX_PCI_H
#घोषणा __NEC_VR41XX_PCI_H

#घोषणा PCI_MASTER_ADDRESS_MASK 0x7fffffffU

काष्ठा pci_master_address_conversion अणु
	uपूर्णांक32_t bus_base_address;
	uपूर्णांक32_t address_mask;
	uपूर्णांक32_t pci_base_address;
पूर्ण;

काष्ठा pci_target_address_conversion अणु
	uपूर्णांक32_t address_mask;
	uपूर्णांक32_t bus_base_address;
पूर्ण;

प्रकार क्रमागत अणु
	CANNOT_LOCK_FROM_DEVICE,
	CAN_LOCK_FROM_DEVICE,
पूर्ण pci_exclusive_access_t;

काष्ठा pci_mailbox_address अणु
	uपूर्णांक32_t base_address;
पूर्ण;

काष्ठा pci_target_address_winकरोw अणु
	uपूर्णांक32_t base_address;
पूर्ण;

प्रकार क्रमागत अणु
	PCI_ARBITRATION_MODE_FAIR,
	PCI_ARBITRATION_MODE_ALTERNATE_0,
	PCI_ARBITRATION_MODE_ALTERNATE_B,
पूर्ण pci_arbiter_priority_control_t;

प्रकार क्रमागत अणु
	PCI_TAKE_AWAY_GNT_DISABLE,
	PCI_TAKE_AWAY_GNT_ENABLE,
पूर्ण pci_take_away_gnt_mode_t;

काष्ठा pci_controller_unit_setup अणु
	काष्ठा pci_master_address_conversion *master_memory1;
	काष्ठा pci_master_address_conversion *master_memory2;

	काष्ठा pci_target_address_conversion *target_memory1;
	काष्ठा pci_target_address_conversion *target_memory2;

	काष्ठा pci_master_address_conversion *master_io;

	pci_exclusive_access_t exclusive_access;

	uपूर्णांक32_t pci_घड़ी_max;
	uपूर्णांक8_t रुको_समय_limit_from_irdy_to_trdy;	/* Only VR4122 is supported */

	काष्ठा pci_mailbox_address *mailbox;
	काष्ठा pci_target_address_winकरोw *target_winकरोw1;
	काष्ठा pci_target_address_winकरोw *target_winकरोw2;

	uपूर्णांक8_t master_latency_समयr;
	uपूर्णांक8_t retry_limit;

	pci_arbiter_priority_control_t arbiter_priority_control;
	pci_take_away_gnt_mode_t take_away_gnt_mode;

	काष्ठा resource *mem_resource;
	काष्ठा resource *io_resource;
पूर्ण;

बाह्य व्योम vr41xx_pciu_setup(काष्ठा pci_controller_unit_setup *setup);

#पूर्ण_अगर /* __NEC_VR41XX_PCI_H */
