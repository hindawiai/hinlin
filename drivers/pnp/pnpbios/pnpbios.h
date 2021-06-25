<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * pnpमूलप्रण.स - contains local definitions
 */

/*
 * Include file क्रम the पूर्णांकerface to a PnP BIOS
 *
 * Original BIOS code (C) 1998 Christian Schmidt (chr.schmidt@tu-bs.de)
 * PnP handler parts (c) 1998 Tom Lees <tom@lpsg.demon.co.uk>
 * Minor reorganizations by David Hinds <dahinds@users.sourceक्रमge.net>
 */

/*
 * Return codes
 */
#घोषणा PNP_SUCCESS                     0x00
#घोषणा PNP_NOT_SET_STATICALLY          0x7f
#घोषणा PNP_UNKNOWN_FUNCTION            0x81
#घोषणा PNP_FUNCTION_NOT_SUPPORTED      0x82
#घोषणा PNP_INVALID_HANDLE              0x83
#घोषणा PNP_BAD_PARAMETER               0x84
#घोषणा PNP_SET_FAILED                  0x85
#घोषणा PNP_EVENTS_NOT_PENDING          0x86
#घोषणा PNP_SYSTEM_NOT_DOCKED           0x87
#घोषणा PNP_NO_ISA_PNP_CARDS            0x88
#घोषणा PNP_UNABLE_TO_DETERMINE_DOCK_CAPABILITIES 0x89
#घोषणा PNP_CONFIG_CHANGE_FAILED_NO_BATTERY 0x8a
#घोषणा PNP_CONFIG_CHANGE_FAILED_RESOURCE_CONFLICT 0x8b
#घोषणा PNP_BUFFER_TOO_SMALL            0x8c
#घोषणा PNP_USE_ESCD_SUPPORT            0x8d
#घोषणा PNP_MESSAGE_NOT_SUPPORTED       0x8e
#घोषणा PNP_HARDWARE_ERROR              0x8f

#घोषणा ESCD_SUCCESS                    0x00
#घोषणा ESCD_IO_ERROR_READING           0x55
#घोषणा ESCD_INVALID                    0x56
#घोषणा ESCD_BUFFER_TOO_SMALL           0x59
#घोषणा ESCD_NVRAM_TOO_SMALL            0x5a
#घोषणा ESCD_FUNCTION_NOT_SUPPORTED     0x81

/*
 * Events that can be received by "get event"
 */
#घोषणा PNPEV_ABOUT_TO_CHANGE_CONFIG	0x0001
#घोषणा PNPEV_DOCK_CHANGED		0x0002
#घोषणा PNPEV_SYSTEM_DEVICE_CHANGED	0x0003
#घोषणा PNPEV_CONFIG_CHANGED_FAILED	0x0004
#घोषणा PNPEV_UNKNOWN_SYSTEM_EVENT	0xffff
/* 0x8000 through 0xfffe are OEM defined */

/*
 * Messages that should be sent through "send message"
 */
#घोषणा PNPMSG_OK			0x00
#घोषणा PNPMSG_ABORT			0x01
#घोषणा PNPMSG_UNDOCK_DEFAULT_ACTION	0x40
#घोषणा PNPMSG_POWER_OFF		0x41
#घोषणा PNPMSG_PNP_OS_ACTIVE		0x42
#घोषणा PNPMSG_PNP_OS_INACTIVE		0x43

/*
 * Plug and Play BIOS flags
 */
#घोषणा PNPBIOS_NO_DISABLE		0x0001
#घोषणा PNPBIOS_NO_CONFIG		0x0002
#घोषणा PNPBIOS_OUTPUT			0x0004
#घोषणा PNPBIOS_INPUT			0x0008
#घोषणा PNPBIOS_BOOTABLE		0x0010
#घोषणा PNPBIOS_DOCK			0x0020
#घोषणा PNPBIOS_REMOVABLE		0x0040
#घोषणा pnpbios_is_अटल(x) (((x)->flags & 0x0100) == 0x0000)
#घोषणा pnpbios_is_dynamic(x) ((x)->flags & 0x0080)

/*
 * Function Parameters
 */
#घोषणा PNPMODE_STATIC 1
#घोषणा PNPMODE_DYNAMIC 0

/* 0x8000 through 0xffff are OEM defined */

#आशय pack(1)
काष्ठा pnp_dev_node_info अणु
	__u16 no_nodes;
	__u16 max_node_size;
पूर्ण;
काष्ठा pnp_करोcking_station_info अणु
	__u32 location_id;
	__u32 serial;
	__u16 capabilities;
पूर्ण;
काष्ठा pnp_isa_config_struc अणु
	__u8 revision;
	__u8 no_csns;
	__u16 isa_rd_data_port;
	__u16 reserved;
पूर्ण;
काष्ठा escd_info_struc अणु
	__u16 min_escd_ग_लिखो_size;
	__u16 escd_size;
	__u32 nv_storage_base;
पूर्ण;
काष्ठा pnp_bios_node अणु
	__u16 size;
	__u8 handle;
	__u32 eisa_id;
	__u8 type_code[3];
	__u16 flags;
	__u8 data[];
पूर्ण;
#आशय pack()

/* non-exported */
बाह्य काष्ठा pnp_dev_node_info node_info;

बाह्य पूर्णांक pnp_bios_dev_node_info(काष्ठा pnp_dev_node_info *data);
बाह्य पूर्णांक pnp_bios_get_dev_node(u8 *nodक्रमागत, अक्षर config,
				 काष्ठा pnp_bios_node *data);
बाह्य पूर्णांक pnp_bios_set_dev_node(u8 nodक्रमागत, अक्षर config,
				 काष्ठा pnp_bios_node *data);
बाह्य पूर्णांक pnp_bios_get_stat_res(अक्षर *info);
बाह्य पूर्णांक pnp_bios_isapnp_config(काष्ठा pnp_isa_config_struc *data);
बाह्य पूर्णांक pnp_bios_escd_info(काष्ठा escd_info_struc *data);
बाह्य पूर्णांक pnp_bios_पढ़ो_escd(अक्षर *data, u32 nvram_base);
बाह्य पूर्णांक pnp_bios_करोck_station_info(काष्ठा pnp_करोcking_station_info *data);

#आशय pack(1)
जोड़ pnp_bios_install_काष्ठा अणु
	काष्ठा अणु
		u32 signature;    /* "$PnP" */
		u8 version;	  /* in BCD */
		u8 length;	  /* length in bytes, currently 21h */
		u16 control;	  /* प्रणाली capabilities */
		u8 checksum;	  /* all bytes must add up to 0 */

		u32 eventflag;    /* phys. address of the event flag */
		u16 rmoffset;     /* real mode entry poपूर्णांक */
		u16 rmcseg;
		u16 pm16offset;   /* 16 bit रक्षित mode entry */
		u32 pm16cseg;
		u32 deviceID;	  /* EISA encoded प्रणाली ID or 0 */
		u16 rmdseg;	  /* real mode data segment */
		u32 pm16dseg;	  /* 16 bit pm data segment base */
	पूर्ण fields;
	अक्षर अक्षरs[0x21];	  /* To calculate the checksum */
पूर्ण;
#आशय pack()

बाह्य पूर्णांक pnp_bios_present(व्योम);
बाह्य पूर्णांक  pnpbios_करोnt_use_current_config;

बाह्य पूर्णांक pnpbios_parse_data_stream(काष्ठा pnp_dev *dev, काष्ठा pnp_bios_node * node);
बाह्य पूर्णांक pnpbios_पढ़ो_resources_from_node(काष्ठा pnp_dev *dev, काष्ठा pnp_bios_node *node);
बाह्य पूर्णांक pnpbios_ग_लिखो_resources_to_node(काष्ठा pnp_dev *dev, काष्ठा pnp_bios_node *node);
बाह्य व्योम pnpid32_to_pnpid(u32 id, अक्षर *str);

बाह्य व्योम pnpbios_prपूर्णांक_status(स्थिर अक्षर * module, u16 status);
बाह्य व्योम pnpbios_calls_init(जोड़ pnp_bios_install_काष्ठा * header);

#अगर_घोषित CONFIG_PNPBIOS_PROC_FS
बाह्य पूर्णांक pnpbios_पूर्णांकerface_attach_device(काष्ठा pnp_bios_node * node);
बाह्य पूर्णांक pnpbios_proc_init (व्योम);
बाह्य व्योम pnpbios_proc_निकास (व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pnpbios_पूर्णांकerface_attach_device(काष्ठा pnp_bios_node * node) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pnpbios_proc_init (व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pnpbios_proc_निकास (व्योम) अणु ; पूर्ण
#पूर्ण_अगर /* CONFIG_PNPBIOS_PROC_FS */
