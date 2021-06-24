<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PCI_BRIDGE_EMUL_H__
#घोषणा __PCI_BRIDGE_EMUL_H__

#समावेश <linux/kernel.h>

/* PCI configuration space of a PCI-to-PCI bridge. */
काष्ठा pci_bridge_emul_conf अणु
	__le16 venकरोr;
	__le16 device;
	__le16 command;
	__le16 status;
	__le32 class_revision;
	u8 cache_line_size;
	u8 latency_समयr;
	u8 header_type;
	u8 bist;
	__le32 bar[2];
	u8 primary_bus;
	u8 secondary_bus;
	u8 subordinate_bus;
	u8 secondary_latency_समयr;
	u8 iobase;
	u8 iolimit;
	__le16 secondary_status;
	__le16 membase;
	__le16 memlimit;
	__le16 pref_mem_base;
	__le16 pref_mem_limit;
	__le32 prefbaseupper;
	__le32 preflimitupper;
	__le16 iobaseupper;
	__le16 iolimitupper;
	u8 capabilities_poपूर्णांकer;
	u8 reserve[3];
	__le32 romaddr;
	u8 पूर्णांकline;
	u8 पूर्णांकpin;
	__le16 bridgectrl;
पूर्ण;

/* PCI configuration space of the PCIe capabilities */
काष्ठा pci_bridge_emul_pcie_conf अणु
	u8 cap_id;
	u8 next;
	__le16 cap;
	__le32 devcap;
	__le16 devctl;
	__le16 devsta;
	__le32 lnkcap;
	__le16 lnkctl;
	__le16 lnksta;
	__le32 slotcap;
	__le16 slotctl;
	__le16 slotsta;
	__le16 rootctl;
	__le16 rsvd;
	__le32 rootsta;
	__le32 devcap2;
	__le16 devctl2;
	__le16 devsta2;
	__le32 lnkcap2;
	__le16 lnkctl2;
	__le16 lnksta2;
	__le32 slotcap2;
	__le16 slotctl2;
	__le16 slotsta2;
पूर्ण;

काष्ठा pci_bridge_emul;

प्रकार क्रमागत अणु PCI_BRIDGE_EMUL_HANDLED,
	       PCI_BRIDGE_EMUL_NOT_HANDLED पूर्ण pci_bridge_emul_पढ़ो_status_t;

काष्ठा pci_bridge_emul_ops अणु
	/*
	 * Called when पढ़ोing from the regular PCI bridge
	 * configuration space. Return PCI_BRIDGE_EMUL_HANDLED when the
	 * operation has handled the पढ़ो operation and filled in the
	 * *value, or PCI_BRIDGE_EMUL_NOT_HANDLED when the पढ़ो should
	 * be emulated by the common code by पढ़ोing from the
	 * in-memory copy of the configuration space.
	 */
	pci_bridge_emul_पढ़ो_status_t (*पढ़ो_base)(काष्ठा pci_bridge_emul *bridge,
						   पूर्णांक reg, u32 *value);

	/*
	 * Same as ->पढ़ो_base(), except it is क्रम पढ़ोing from the
	 * PCIe capability configuration space.
	 */
	pci_bridge_emul_पढ़ो_status_t (*पढ़ो_pcie)(काष्ठा pci_bridge_emul *bridge,
						   पूर्णांक reg, u32 *value);
	/*
	 * Called when writing to the regular PCI bridge configuration
	 * space. old is the current value, new is the new value being
	 * written, and mask indicates which parts of the value are
	 * being changed.
	 */
	व्योम (*ग_लिखो_base)(काष्ठा pci_bridge_emul *bridge, पूर्णांक reg,
			   u32 old, u32 new, u32 mask);

	/*
	 * Same as ->ग_लिखो_base(), except it is क्रम writing from the
	 * PCIe capability configuration space.
	 */
	व्योम (*ग_लिखो_pcie)(काष्ठा pci_bridge_emul *bridge, पूर्णांक reg,
			   u32 old, u32 new, u32 mask);
पूर्ण;

काष्ठा pci_bridge_reg_behavior;

काष्ठा pci_bridge_emul अणु
	काष्ठा pci_bridge_emul_conf conf;
	काष्ठा pci_bridge_emul_pcie_conf pcie_conf;
	काष्ठा pci_bridge_emul_ops *ops;
	काष्ठा pci_bridge_reg_behavior *pci_regs_behavior;
	काष्ठा pci_bridge_reg_behavior *pcie_cap_regs_behavior;
	व्योम *data;
	bool has_pcie;
पूर्ण;

क्रमागत अणु
	PCI_BRIDGE_EMUL_NO_PREFETCHABLE_BAR = BIT(0),
पूर्ण;

पूर्णांक pci_bridge_emul_init(काष्ठा pci_bridge_emul *bridge,
			 अचिन्हित पूर्णांक flags);
व्योम pci_bridge_emul_cleanup(काष्ठा pci_bridge_emul *bridge);

पूर्णांक pci_bridge_emul_conf_पढ़ो(काष्ठा pci_bridge_emul *bridge, पूर्णांक where,
			      पूर्णांक size, u32 *value);
पूर्णांक pci_bridge_emul_conf_ग_लिखो(काष्ठा pci_bridge_emul *bridge, पूर्णांक where,
			       पूर्णांक size, u32 value);

#पूर्ण_अगर /* __PCI_BRIDGE_EMUL_H__ */
