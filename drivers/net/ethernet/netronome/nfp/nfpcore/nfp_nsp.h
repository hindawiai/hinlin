<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

#अगर_अघोषित NSP_NSP_H
#घोषणा NSP_NSP_H 1

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

काष्ठा firmware;
काष्ठा nfp_cpp;
काष्ठा nfp_nsp;

काष्ठा nfp_nsp *nfp_nsp_खोलो(काष्ठा nfp_cpp *cpp);
व्योम nfp_nsp_बंद(काष्ठा nfp_nsp *state);
u16 nfp_nsp_get_abi_ver_major(काष्ठा nfp_nsp *state);
u16 nfp_nsp_get_abi_ver_minor(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_रुको(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_device_soft_reset(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_load_fw(काष्ठा nfp_nsp *state, स्थिर काष्ठा firmware *fw);
पूर्णांक nfp_nsp_ग_लिखो_flash(काष्ठा nfp_nsp *state, स्थिर काष्ठा firmware *fw);
पूर्णांक nfp_nsp_mac_reinit(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_load_stored_fw(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_hwinfo_lookup(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size);
पूर्णांक nfp_nsp_hwinfo_lookup_optional(काष्ठा nfp_nsp *state, व्योम *buf,
				   अचिन्हित पूर्णांक size, स्थिर अक्षर *शेष_val);
पूर्णांक nfp_nsp_hwinfo_set(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size);
पूर्णांक nfp_nsp_fw_loaded(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_पढ़ो_module_eeprom(काष्ठा nfp_nsp *state, पूर्णांक eth_index,
			       अचिन्हित पूर्णांक offset, व्योम *data,
			       अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक *पढ़ो_len);

अटल अंतरभूत bool nfp_nsp_has_mac_reinit(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 20;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_stored_fw_load(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 23;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_hwinfo_lookup(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 24;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_hwinfo_set(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 25;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_fw_loaded(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 25;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_versions(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 27;
पूर्ण

अटल अंतरभूत bool nfp_nsp_has_पढ़ो_module_eeprom(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_get_abi_ver_minor(state) > 28;
पूर्ण

क्रमागत nfp_eth_पूर्णांकerface अणु
	NFP_INTERFACE_NONE	= 0,
	NFP_INTERFACE_SFP	= 1,
	NFP_INTERFACE_SFPP	= 10,
	NFP_INTERFACE_SFP28	= 28,
	NFP_INTERFACE_QSFP	= 40,
	NFP_INTERFACE_RJ45	= 45,
	NFP_INTERFACE_CXP	= 100,
	NFP_INTERFACE_QSFP28	= 112,
पूर्ण;

क्रमागत nfp_eth_media अणु
	NFP_MEDIA_DAC_PASSIVE = 0,
	NFP_MEDIA_DAC_ACTIVE,
	NFP_MEDIA_FIBRE,
पूर्ण;

क्रमागत nfp_eth_aneg अणु
	NFP_ANEG_AUTO = 0,
	NFP_ANEG_SEARCH,
	NFP_ANEG_25G_CONSORTIUM,
	NFP_ANEG_25G_IEEE,
	NFP_ANEG_DISABLED,
पूर्ण;

क्रमागत nfp_eth_fec अणु
	NFP_FEC_AUTO_BIT = 0,
	NFP_FEC_BASER_BIT,
	NFP_FEC_REED_SOLOMON_BIT,
	NFP_FEC_DISABLED_BIT,
पूर्ण;

#घोषणा NFP_FEC_AUTO		BIT(NFP_FEC_AUTO_BIT)
#घोषणा NFP_FEC_BASER		BIT(NFP_FEC_BASER_BIT)
#घोषणा NFP_FEC_REED_SOLOMON	BIT(NFP_FEC_REED_SOLOMON_BIT)
#घोषणा NFP_FEC_DISABLED	BIT(NFP_FEC_DISABLED_BIT)

/* Defines the valid values of the 'abi_drv_reset' hwinfo key */
#घोषणा NFP_NSP_DRV_RESET_DISK			0
#घोषणा NFP_NSP_DRV_RESET_ALWAYS		1
#घोषणा NFP_NSP_DRV_RESET_NEVER			2
#घोषणा NFP_NSP_DRV_RESET_DEFAULT		"0"

/* Defines the valid values of the 'app_fw_from_flash' hwinfo key */
#घोषणा NFP_NSP_APP_FW_LOAD_DISK		0
#घोषणा NFP_NSP_APP_FW_LOAD_FLASH		1
#घोषणा NFP_NSP_APP_FW_LOAD_PREF		2
#घोषणा NFP_NSP_APP_FW_LOAD_DEFAULT		"2"

/* Define the शेष value क्रम the 'abi_drv_load_ifc' key */
#घोषणा NFP_NSP_DRV_LOAD_IFC_DEFAULT		"0x10ff"

/**
 * काष्ठा nfp_eth_table - ETH table inक्रमmation
 * @count:	number of table entries
 * @max_index:	max of @index fields of all @ports
 * @ports:	table of ports
 *
 * @ports.eth_index:	port index according to legacy ethX numbering
 * @ports.index:	chip-wide first channel index
 * @ports.nbi:		NBI index
 * @ports.base:		first channel index (within NBI)
 * @ports.lanes:	number of channels
 * @ports.speed:	पूर्णांकerface speed (in Mbps)
 * @ports.पूर्णांकerface:	पूर्णांकerface (module) plugged in
 * @ports.media:	media type of the @पूर्णांकerface
 * @ports.fec:		क्रमward error correction mode
 * @ports.aneg:		स्वतः negotiation mode
 * @ports.mac_addr:	पूर्णांकerface MAC address
 * @ports.label_port:	port id
 * @ports.label_subport:  id of पूर्णांकerface within port (क्रम split ports)
 * @ports.enabled:	is enabled?
 * @ports.tx_enabled:	is TX enabled?
 * @ports.rx_enabled:	is RX enabled?
 * @ports.override_changed: is media reconfig pending?
 *
 * @ports.port_type:	one of %PORT_* defines क्रम ethtool
 * @ports.port_lanes:	total number of lanes on the port (sum of lanes of all
 *			subports)
 * @ports.is_split:	is पूर्णांकerface part of a split port
 * @ports.fec_modes_supported:	biपंचांगap of FEC modes supported
 */
काष्ठा nfp_eth_table अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक max_index;
	काष्ठा nfp_eth_table_port अणु
		अचिन्हित पूर्णांक eth_index;
		अचिन्हित पूर्णांक index;
		अचिन्हित पूर्णांक nbi;
		अचिन्हित पूर्णांक base;
		अचिन्हित पूर्णांक lanes;
		अचिन्हित पूर्णांक speed;

		अचिन्हित पूर्णांक पूर्णांकerface;
		क्रमागत nfp_eth_media media;

		क्रमागत nfp_eth_fec fec;
		क्रमागत nfp_eth_aneg aneg;

		u8 mac_addr[ETH_ALEN];

		u8 label_port;
		u8 label_subport;

		bool enabled;
		bool tx_enabled;
		bool rx_enabled;

		bool override_changed;

		/* Computed fields */
		u8 port_type;

		अचिन्हित पूर्णांक port_lanes;

		bool is_split;

		अचिन्हित पूर्णांक fec_modes_supported;
	पूर्ण ports[];
पूर्ण;

काष्ठा nfp_eth_table *nfp_eth_पढ़ो_ports(काष्ठा nfp_cpp *cpp);
काष्ठा nfp_eth_table *
__nfp_eth_पढ़ो_ports(काष्ठा nfp_cpp *cpp, काष्ठा nfp_nsp *nsp);

पूर्णांक nfp_eth_set_mod_enable(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx, bool enable);
पूर्णांक nfp_eth_set_configured(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx,
			   bool configed);
पूर्णांक
nfp_eth_set_fec(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx, क्रमागत nfp_eth_fec mode);

अटल अंतरभूत bool nfp_eth_can_support_fec(काष्ठा nfp_eth_table_port *eth_port)
अणु
	वापस !!eth_port->fec_modes_supported;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
nfp_eth_supported_fec_modes(काष्ठा nfp_eth_table_port *eth_port)
अणु
	वापस eth_port->fec_modes_supported;
पूर्ण

काष्ठा nfp_nsp *nfp_eth_config_start(काष्ठा nfp_cpp *cpp, अचिन्हित पूर्णांक idx);
पूर्णांक nfp_eth_config_commit_end(काष्ठा nfp_nsp *nsp);
व्योम nfp_eth_config_cleanup_end(काष्ठा nfp_nsp *nsp);

पूर्णांक __nfp_eth_set_aneg(काष्ठा nfp_nsp *nsp, क्रमागत nfp_eth_aneg mode);
पूर्णांक __nfp_eth_set_speed(काष्ठा nfp_nsp *nsp, अचिन्हित पूर्णांक speed);
पूर्णांक __nfp_eth_set_split(काष्ठा nfp_nsp *nsp, अचिन्हित पूर्णांक lanes);

/**
 * काष्ठा nfp_nsp_identअगरy - NSP अटल inक्रमmation
 * @version:      opaque version string
 * @flags:        version flags
 * @br_primary:   branch id of primary bootloader
 * @br_secondary: branch id of secondary bootloader
 * @br_nsp:       branch id of NSP
 * @primary:      version of primarary bootloader
 * @secondary:    version id of secondary bootloader
 * @nsp:          version id of NSP
 * @sensor_mask:  mask of present sensors available on NIC
 */
काष्ठा nfp_nsp_identअगरy अणु
	अक्षर version[40];
	u8 flags;
	u8 br_primary;
	u8 br_secondary;
	u8 br_nsp;
	u16 primary;
	u16 secondary;
	u16 nsp;
	u64 sensor_mask;
पूर्ण;

काष्ठा nfp_nsp_identअगरy *__nfp_nsp_identअगरy(काष्ठा nfp_nsp *nsp);

क्रमागत nfp_nsp_sensor_id अणु
	NFP_SENSOR_CHIP_TEMPERATURE,
	NFP_SENSOR_ASSEMBLY_POWER,
	NFP_SENSOR_ASSEMBLY_12V_POWER,
	NFP_SENSOR_ASSEMBLY_3V3_POWER,
पूर्ण;

पूर्णांक nfp_hwmon_पढ़ो_sensor(काष्ठा nfp_cpp *cpp, क्रमागत nfp_nsp_sensor_id id,
			  दीर्घ *val);

#घोषणा NFP_NSP_VERSION_BUFSZ	1024 /* reasonable size, not in the ABI */

क्रमागत nfp_nsp_versions अणु
	NFP_VERSIONS_BSP,
	NFP_VERSIONS_CPLD,
	NFP_VERSIONS_APP,
	NFP_VERSIONS_BUNDLE,
	NFP_VERSIONS_UNDI,
	NFP_VERSIONS_NCSI,
	NFP_VERSIONS_CFGR,
पूर्ण;

पूर्णांक nfp_nsp_versions(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size);
स्थिर अक्षर *nfp_nsp_versions_get(क्रमागत nfp_nsp_versions id, bool flash,
				 स्थिर u8 *buf, अचिन्हित पूर्णांक size);
#पूर्ण_अगर
