<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SCSI_TRANSPORT_SAS_H
#घोषणा SCSI_TRANSPORT_SAS_H

#समावेश <linux/transport_class.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <scsi/sas.h>
#समावेश <linux/bsg-lib.h>

काष्ठा scsi_transport_ढाँचा;
काष्ठा sas_rphy;
काष्ठा request;

#अगर !IS_ENABLED(CONFIG_SCSI_SAS_ATTRS)
अटल अंतरभूत पूर्णांक scsi_is_sas_rphy(स्थिर काष्ठा device *sdev)
अणु
	वापस 0;
पूर्ण
#अन्यथा
बाह्य पूर्णांक scsi_is_sas_rphy(स्थिर काष्ठा device *);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sas_protocol_ata(क्रमागत sas_protocol proto)
अणु
	वापस ((proto & SAS_PROTOCOL_SATA) ||
		(proto & SAS_PROTOCOL_STP))? 1 : 0;
पूर्ण

क्रमागत sas_linkrate अणु
	/* These Values are defined in the SAS standard */
	SAS_LINK_RATE_UNKNOWN = 0,
	SAS_PHY_DISABLED = 1,
	SAS_PHY_RESET_PROBLEM = 2,
	SAS_SATA_SPINUP_HOLD = 3,
	SAS_SATA_PORT_SELECTOR = 4,
	SAS_PHY_RESET_IN_PROGRESS = 5,
	SAS_LINK_RATE_1_5_GBPS = 8,
	SAS_LINK_RATE_G1 = SAS_LINK_RATE_1_5_GBPS,
	SAS_LINK_RATE_3_0_GBPS = 9,
	SAS_LINK_RATE_G2 = SAS_LINK_RATE_3_0_GBPS,
	SAS_LINK_RATE_6_0_GBPS = 10,
	SAS_LINK_RATE_12_0_GBPS = 11,
	/* These are भव to the transport class and may never
	 * be संकेतled normally since the standard defined field
	 * is only 4 bits */
	SAS_LINK_RATE_FAILED = 0x10,
	SAS_PHY_VIRTUAL = 0x11,
पूर्ण;

काष्ठा sas_identअगरy अणु
	क्रमागत sas_device_type	device_type;
	क्रमागत sas_protocol	initiator_port_protocols;
	क्रमागत sas_protocol	target_port_protocols;
	u64			sas_address;
	u8			phy_identअगरier;
पूर्ण;

काष्ठा sas_phy अणु
	काष्ठा device		dev;
	पूर्णांक			number;
	पूर्णांक			enabled;

	/* phy identअगरication */
	काष्ठा sas_identअगरy	identअगरy;

	/* phy attributes */
	क्रमागत sas_linkrate	negotiated_linkrate;
	क्रमागत sas_linkrate	minimum_linkrate_hw;
	क्रमागत sas_linkrate	minimum_linkrate;
	क्रमागत sas_linkrate	maximum_linkrate_hw;
	क्रमागत sas_linkrate	maximum_linkrate;

	/* link error statistics */
	u32			invalid_dword_count;
	u32			running_disparity_error_count;
	u32			loss_of_dword_sync_count;
	u32			phy_reset_problem_count;

	/* क्रम the list of phys beदीर्घing to a port */
	काष्ठा list_head	port_siblings;

	/* available to the lldd */
	व्योम			*hostdata;
पूर्ण;

#घोषणा dev_to_phy(d) \
	container_of((d), काष्ठा sas_phy, dev)
#घोषणा transport_class_to_phy(dev) \
	dev_to_phy((dev)->parent)
#घोषणा phy_to_shost(phy) \
	dev_to_shost((phy)->dev.parent)

काष्ठा request_queue;
काष्ठा sas_rphy अणु
	काष्ठा device		dev;
	काष्ठा sas_identअगरy	identअगरy;
	काष्ठा list_head	list;
	काष्ठा request_queue	*q;
	u32			scsi_target_id;
पूर्ण;

#घोषणा dev_to_rphy(d) \
	container_of((d), काष्ठा sas_rphy, dev)
#घोषणा transport_class_to_rphy(dev) \
	dev_to_rphy((dev)->parent)
#घोषणा rphy_to_shost(rphy) \
	dev_to_shost((rphy)->dev.parent)
#घोषणा target_to_rphy(targ) \
	dev_to_rphy((targ)->dev.parent)

काष्ठा sas_end_device अणु
	काष्ठा sas_rphy		rphy;
	/* flags */
	अचिन्हित		पढ़ोy_led_meaning:1;
	अचिन्हित		tlr_supported:1;
	अचिन्हित		tlr_enabled:1;
	/* parameters */
	u16			I_T_nexus_loss_समयout;
	u16			initiator_response_समयout;
पूर्ण;
#घोषणा rphy_to_end_device(r) \
	container_of((r), काष्ठा sas_end_device, rphy)

काष्ठा sas_expander_device अणु
	पूर्णांक    level;
	पूर्णांक    next_port_id;

	#घोषणा SAS_EXPANDER_VENDOR_ID_LEN	8
	अक्षर   venकरोr_id[SAS_EXPANDER_VENDOR_ID_LEN+1];
	#घोषणा SAS_EXPANDER_PRODUCT_ID_LEN	16
	अक्षर   product_id[SAS_EXPANDER_PRODUCT_ID_LEN+1];
	#घोषणा SAS_EXPANDER_PRODUCT_REV_LEN	4
	अक्षर   product_rev[SAS_EXPANDER_PRODUCT_REV_LEN+1];
	#घोषणा SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN	8
	अक्षर   component_venकरोr_id[SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN+1];
	u16    component_id;
	u8     component_revision_id;

	काष्ठा sas_rphy		rphy;

पूर्ण;
#घोषणा rphy_to_expander_device(r) \
	container_of((r), काष्ठा sas_expander_device, rphy)

काष्ठा sas_port अणु
	काष्ठा device		dev;

	पूर्णांक			port_identअगरier;
	पूर्णांक			num_phys;
	/* port flags */
	अचिन्हित पूर्णांक		is_backlink:1;

	/* the other end of the link */
	काष्ठा sas_rphy		*rphy;

	काष्ठा mutex		phy_list_mutex;
	काष्ठा list_head	phy_list;
	काष्ठा list_head	del_list; /* libsas only */
पूर्ण;

#घोषणा dev_to_sas_port(d) \
	container_of((d), काष्ठा sas_port, dev)
#घोषणा transport_class_to_sas_port(dev) \
	dev_to_sas_port((dev)->parent)

काष्ठा sas_phy_linkrates अणु
	क्रमागत sas_linkrate maximum_linkrate;
	क्रमागत sas_linkrate minimum_linkrate;
पूर्ण;

/* The functions by which the transport class and the driver communicate */
काष्ठा sas_function_ढाँचा अणु
	पूर्णांक (*get_linkerrors)(काष्ठा sas_phy *);
	पूर्णांक (*get_enclosure_identअगरier)(काष्ठा sas_rphy *, u64 *);
	पूर्णांक (*get_bay_identअगरier)(काष्ठा sas_rphy *);
	पूर्णांक (*phy_reset)(काष्ठा sas_phy *, पूर्णांक);
	पूर्णांक (*phy_enable)(काष्ठा sas_phy *, पूर्णांक);
	पूर्णांक (*phy_setup)(काष्ठा sas_phy *);
	व्योम (*phy_release)(काष्ठा sas_phy *);
	पूर्णांक (*set_phy_speed)(काष्ठा sas_phy *, काष्ठा sas_phy_linkrates *);
	व्योम (*smp_handler)(काष्ठा bsg_job *, काष्ठा Scsi_Host *,
			काष्ठा sas_rphy *);
पूर्ण;


व्योम sas_हटाओ_children(काष्ठा device *);
बाह्य व्योम sas_हटाओ_host(काष्ठा Scsi_Host *);

बाह्य काष्ठा sas_phy *sas_phy_alloc(काष्ठा device *, पूर्णांक);
बाह्य व्योम sas_phy_मुक्त(काष्ठा sas_phy *);
बाह्य पूर्णांक sas_phy_add(काष्ठा sas_phy *);
बाह्य व्योम sas_phy_delete(काष्ठा sas_phy *);
बाह्य पूर्णांक scsi_is_sas_phy(स्थिर काष्ठा device *);

u64 sas_get_address(काष्ठा scsi_device *);
अचिन्हित पूर्णांक sas_tlr_supported(काष्ठा scsi_device *);
अचिन्हित पूर्णांक sas_is_tlr_enabled(काष्ठा scsi_device *);
व्योम sas_disable_tlr(काष्ठा scsi_device *);
व्योम sas_enable_tlr(काष्ठा scsi_device *);

बाह्य काष्ठा sas_rphy *sas_end_device_alloc(काष्ठा sas_port *);
बाह्य काष्ठा sas_rphy *sas_expander_alloc(काष्ठा sas_port *, क्रमागत sas_device_type);
व्योम sas_rphy_मुक्त(काष्ठा sas_rphy *);
बाह्य पूर्णांक sas_rphy_add(काष्ठा sas_rphy *);
बाह्य व्योम sas_rphy_हटाओ(काष्ठा sas_rphy *);
बाह्य व्योम sas_rphy_delete(काष्ठा sas_rphy *);
बाह्य व्योम sas_rphy_unlink(काष्ठा sas_rphy *);

काष्ठा sas_port *sas_port_alloc(काष्ठा device *, पूर्णांक);
काष्ठा sas_port *sas_port_alloc_num(काष्ठा device *);
पूर्णांक sas_port_add(काष्ठा sas_port *);
व्योम sas_port_मुक्त(काष्ठा sas_port *);
व्योम sas_port_delete(काष्ठा sas_port *);
व्योम sas_port_add_phy(काष्ठा sas_port *, काष्ठा sas_phy *);
व्योम sas_port_delete_phy(काष्ठा sas_port *, काष्ठा sas_phy *);
व्योम sas_port_mark_backlink(काष्ठा sas_port *);
पूर्णांक scsi_is_sas_port(स्थिर काष्ठा device *);
काष्ठा sas_phy *sas_port_get_phy(काष्ठा sas_port *port);
अटल अंतरभूत व्योम sas_port_put_phy(काष्ठा sas_phy *phy)
अणु
	अगर (phy)
		put_device(&phy->dev);
पूर्ण

बाह्य काष्ठा scsi_transport_ढाँचा *
sas_attach_transport(काष्ठा sas_function_ढाँचा *);
बाह्य व्योम sas_release_transport(काष्ठा scsi_transport_ढाँचा *);
पूर्णांक sas_पढ़ो_port_mode_page(काष्ठा scsi_device *);

अटल अंतरभूत पूर्णांक
scsi_is_sas_expander_device(काष्ठा device *dev)
अणु
	काष्ठा sas_rphy *rphy;
	अगर (!scsi_is_sas_rphy(dev))
		वापस 0;
	rphy = dev_to_rphy(dev);
	वापस rphy->identअगरy.device_type == SAS_FANOUT_EXPANDER_DEVICE ||
		rphy->identअगरy.device_type == SAS_EDGE_EXPANDER_DEVICE;
पूर्ण

#घोषणा scsi_is_sas_phy_local(phy)	scsi_is_host_device((phy)->dev.parent)

#पूर्ण_अगर /* SCSI_TRANSPORT_SAS_H */
