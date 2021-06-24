<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 NXP Semiconductors
 */
#अगर_अघोषित _MSCC_FELIX_H
#घोषणा _MSCC_FELIX_H

#घोषणा ocelot_to_felix(o)		container_of((o), काष्ठा felix, ocelot)

/* Platक्रमm-specअगरic inक्रमmation */
काष्ठा felix_info अणु
	स्थिर काष्ठा resource		*target_io_res;
	स्थिर काष्ठा resource		*port_io_res;
	स्थिर काष्ठा resource		*imdio_res;
	स्थिर काष्ठा reg_field		*regfields;
	स्थिर u32 *स्थिर		*map;
	स्थिर काष्ठा ocelot_ops		*ops;
	पूर्णांक				num_mact_rows;
	स्थिर काष्ठा ocelot_stat_layout	*stats_layout;
	अचिन्हित पूर्णांक			num_stats;
	पूर्णांक				num_ports;
	पूर्णांक				num_tx_queues;
	काष्ठा vcap_props		*vcap;
	पूर्णांक				चयन_pci_bar;
	पूर्णांक				imdio_pci_bar;
	स्थिर काष्ठा ptp_घड़ी_info	*ptp_caps;

	/* Some Ocelot चयनes are पूर्णांकegrated पूर्णांकo the SoC without the
	 * extraction IRQ line connected to the ARM GIC. By enabling this
	 * workaround, the few packets that are delivered to the CPU port
	 * module (currently only PTP) are copied not only to the hardware CPU
	 * port module, but also to the 802.1Q Ethernet CPU port, and polling
	 * the extraction रेजिस्टरs is triggered once the DSA tagger sees a PTP
	 * frame. The Ethernet frame is only used as a notअगरication: it is
	 * dropped, and the original frame is extracted over MMIO and annotated
	 * with the RX बारtamp.
	 */
	bool				quirk_no_xtr_irq;

	पूर्णांक	(*mdio_bus_alloc)(काष्ठा ocelot *ocelot);
	व्योम	(*mdio_bus_मुक्त)(काष्ठा ocelot *ocelot);
	व्योम	(*phylink_validate)(काष्ठा ocelot *ocelot, पूर्णांक port,
				    अचिन्हित दीर्घ *supported,
				    काष्ठा phylink_link_state *state);
	पूर्णांक	(*prevalidate_phy_mode)(काष्ठा ocelot *ocelot, पूर्णांक port,
					phy_पूर्णांकerface_t phy_mode);
	पूर्णांक	(*port_setup_tc)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 क्रमागत tc_setup_type type, व्योम *type_data);
	व्योम	(*port_sched_speed_set)(काष्ठा ocelot *ocelot, पूर्णांक port,
					u32 speed);
पूर्ण;

बाह्य स्थिर काष्ठा dsa_चयन_ops felix_चयन_ops;

/* DSA glue / front-end क्रम काष्ठा ocelot */
काष्ठा felix अणु
	काष्ठा dsa_चयन		*ds;
	स्थिर काष्ठा felix_info		*info;
	काष्ठा ocelot			ocelot;
	काष्ठा mii_bus			*imdio;
	काष्ठा lynx_pcs			**pcs;
	resource_माप_प्रकार			चयन_base;
	resource_माप_प्रकार			imdio_base;
	काष्ठा dsa_8021q_context	*dsa_8021q_ctx;
	क्रमागत dsa_tag_protocol		tag_proto;
पूर्ण;

काष्ठा net_device *felix_port_to_netdev(काष्ठा ocelot *ocelot, पूर्णांक port);
पूर्णांक felix_netdev_to_port(काष्ठा net_device *dev);

#पूर्ण_अगर
