<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2018-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित HL_BOOT_IF_H
#घोषणा HL_BOOT_IF_H

#घोषणा LKD_HARD_RESET_MAGIC		0xED7BD694
#घोषणा HL_POWER9_HOST_MAGIC		0x1DA30009

#घोषणा BOOT_FIT_SRAM_OFFSET		0x200000

#घोषणा VERSION_MAX_LEN			128

/*
 * CPU error bits in BOOT_ERROR रेजिस्टरs
 *
 * CPU_BOOT_ERR0_DRAM_INIT_FAIL		DRAM initialization failed.
 *					DRAM is not reliable to use.
 *
 * CPU_BOOT_ERR0_FIT_CORRUPTED		FIT data पूर्णांकegrity verअगरication of the
 *					image provided by the host has failed.
 *
 * CPU_BOOT_ERR0_TS_INIT_FAIL		Thermal Sensor initialization failed.
 *					Boot जारीs as usual, but keep in
 *					mind this is a warning.
 *
 * CPU_BOOT_ERR0_DRAM_SKIPPED		DRAM initialization has been skipped.
 *					Skipping DRAM initialization has been
 *					requested (e.g. strap, command, etc.)
 *					and FW skipped the DRAM initialization.
 *					Host can initialize the DRAM.
 *
 * CPU_BOOT_ERR0_BMC_WAIT_SKIPPED	Waiting क्रम BMC data will be skipped.
 *					Meaning the BMC data might not be
 *					available until reset.
 *
 * CPU_BOOT_ERR0_NIC_DATA_NOT_RDY	NIC data from BMC is not पढ़ोy.
 *					BMC has not provided the NIC data yet.
 *					Once provided this bit will be cleared.
 *
 * CPU_BOOT_ERR0_NIC_FW_FAIL		NIC FW loading failed.
 *					The NIC FW loading and initialization
 *					failed. This means NICs are not usable.
 *
 * CPU_BOOT_ERR0_SECURITY_NOT_RDY	Chip security initialization has been
 *					started, but is not पढ़ोy yet - chip
 *					cannot be accessed.
 *
 * CPU_BOOT_ERR0_SECURITY_FAIL		Security related tasks have failed.
 *					The tasks are security init (root of
 *					trust), boot authentication (chain of
 *					trust), data packets authentication.
 *
 * CPU_BOOT_ERR0_EFUSE_FAIL		Reading from eFuse failed.
 *					The PCI device ID might be wrong.
 *
 * CPU_BOOT_ERR0_PRI_IMG_VER_FAIL	Verअगरication of primary image failed.
 *					It mean that ppboot checksum
 *					verअगरication क्रम the preboot primary
 *					image has failed to match expected
 *					checksum. Trying to program image again
 *					might solve this.
 *
 * CPU_BOOT_ERR0_SEC_IMG_VER_FAIL	Verअगरication of secondary image failed.
 *					It mean that ppboot checksum
 *					verअगरication क्रम the preboot secondary
 *					image has failed to match expected
 *					checksum. Trying to program image again
 *					might solve this.
 *
 * CPU_BOOT_ERR0_PLL_FAIL		PLL settings failed, meaning that one
 *					of the PLLs reमुख्यs in REF_CLK
 *
 * CPU_BOOT_ERR0_DEVICE_UNUSABLE_FAIL	Device is unusable and customer support
 *					should be contacted.
 *
 * CPU_BOOT_ERR0_ENABLED		Error रेजिस्टरs enabled.
 *					This is a मुख्य indication that the
 *					running FW populates the error
 *					रेजिस्टरs. Meaning the error bits are
 *					not garbage, but actual error statuses.
 */
#घोषणा CPU_BOOT_ERR0_DRAM_INIT_FAIL		(1 << 0)
#घोषणा CPU_BOOT_ERR0_FIT_CORRUPTED		(1 << 1)
#घोषणा CPU_BOOT_ERR0_TS_INIT_FAIL		(1 << 2)
#घोषणा CPU_BOOT_ERR0_DRAM_SKIPPED		(1 << 3)
#घोषणा CPU_BOOT_ERR0_BMC_WAIT_SKIPPED		(1 << 4)
#घोषणा CPU_BOOT_ERR0_NIC_DATA_NOT_RDY		(1 << 5)
#घोषणा CPU_BOOT_ERR0_NIC_FW_FAIL		(1 << 6)
#घोषणा CPU_BOOT_ERR0_SECURITY_NOT_RDY		(1 << 7)
#घोषणा CPU_BOOT_ERR0_SECURITY_FAIL		(1 << 8)
#घोषणा CPU_BOOT_ERR0_EFUSE_FAIL		(1 << 9)
#घोषणा CPU_BOOT_ERR0_PRI_IMG_VER_FAIL		(1 << 10)
#घोषणा CPU_BOOT_ERR0_SEC_IMG_VER_FAIL		(1 << 11)
#घोषणा CPU_BOOT_ERR0_PLL_FAIL			(1 << 12)
#घोषणा CPU_BOOT_ERR0_DEVICE_UNUSABLE_FAIL	(1 << 13)
#घोषणा CPU_BOOT_ERR0_ENABLED			(1 << 31)

/*
 * BOOT DEVICE STATUS bits in BOOT_DEVICE_STS रेजिस्टरs
 *
 * CPU_BOOT_DEV_STS0_SECURITY_EN	Security is Enabled.
 *					This is an indication क्रम security
 *					enabled in FW, which means that
 *					all conditions क्रम security are met:
 *					device is indicated as security enabled,
 *					रेजिस्टरs are रक्षित, and device
 *					uses keys क्रम image verअगरication.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_DEBUG_EN		Debug is enabled.
 *					Enabled when JTAG or DEBUG is enabled
 *					in FW.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_WATCHDOG_EN	Watchकरोg is enabled.
 *					Watchकरोg is enabled in FW.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_DRAM_INIT_EN	DRAM initialization is enabled.
 *					DRAM initialization has been करोne in FW.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_BMC_WAIT_EN	Waiting क्रम BMC data enabled.
 *					If set, it means that during boot,
 *					FW रुकोed क्रम BMC data.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_E2E_CRED_EN	E2E credits initialized.
 *					FW initialized E2E credits.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_HBM_CRED_EN	HBM credits initialized.
 *					FW initialized HBM credits.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_RL_EN		Rate limiter initialized.
 *					FW initialized rate limiter.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_SRAM_SCR_EN	SRAM scrambler enabled.
 *					FW initialized SRAM scrambler.
 *					Initialized in: linux
 *
 * CPU_BOOT_DEV_STS0_DRAM_SCR_EN	DRAM scrambler enabled.
 *					FW initialized DRAM scrambler.
 *					Initialized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_FW_HARD_RST_EN	FW hard reset procedure is enabled.
 *					FW has the hard reset procedure
 *					implemented. This means that FW will
 *					perक्रमm hard reset procedure on
 *					receiving the halt-machine event.
 *					Initialized in: preboot, u-boot, linux
 *
 * CPU_BOOT_DEV_STS0_PLL_INFO_EN	FW retrieval of PLL info is enabled.
 *					Initialized in: linux
 *
 * CPU_BOOT_DEV_STS0_SP_SRAM_EN		SP SRAM is initialized and available
 *					क्रम use.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_CLK_GATE_EN	Clock Gating enabled.
 *					FW initialized Clock Gating.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_HBM_ECC_EN		HBM ECC handling Enabled.
 *					FW handles HBM ECC indications.
 *					Initialized in: linux
 *
 * CPU_BOOT_DEV_STS0_PKT_PI_ACK_EN	Packets ack value used in the armcpd
 *					is set to the PI counter.
 *					Initialized in: linux
 *
 * CPU_BOOT_DEV_STS0_FW_LD_COM_EN	Flexible FW loading communication
 *					protocol is enabled.
 *					Initialized in: preboot
 *
 * CPU_BOOT_DEV_STS0_FW_IATU_CONF_EN	FW iATU configuration is enabled.
 *					This bit अगर set, means the iATU has been
 *					configured and is पढ़ोy क्रम use.
 *					Initialized in: ppboot
 *
 * CPU_BOOT_DEV_STS0_DYN_PLL_EN		Dynamic PLL configuration is enabled.
 *					FW sends to host a biपंचांगap of supported
 *					PLLs.
 *					Initialized in: linux
 *
 * CPU_BOOT_DEV_STS0_ENABLED		Device status रेजिस्टर enabled.
 *					This is a मुख्य indication that the
 *					running FW populates the device status
 *					रेजिस्टर. Meaning the device status
 *					bits are not garbage, but actual
 *					statuses.
 *					Initialized in: preboot
 *
 */
#घोषणा CPU_BOOT_DEV_STS0_SECURITY_EN			(1 << 0)
#घोषणा CPU_BOOT_DEV_STS0_DEBUG_EN			(1 << 1)
#घोषणा CPU_BOOT_DEV_STS0_WATCHDOG_EN			(1 << 2)
#घोषणा CPU_BOOT_DEV_STS0_DRAM_INIT_EN			(1 << 3)
#घोषणा CPU_BOOT_DEV_STS0_BMC_WAIT_EN			(1 << 4)
#घोषणा CPU_BOOT_DEV_STS0_E2E_CRED_EN			(1 << 5)
#घोषणा CPU_BOOT_DEV_STS0_HBM_CRED_EN			(1 << 6)
#घोषणा CPU_BOOT_DEV_STS0_RL_EN				(1 << 7)
#घोषणा CPU_BOOT_DEV_STS0_SRAM_SCR_EN			(1 << 8)
#घोषणा CPU_BOOT_DEV_STS0_DRAM_SCR_EN			(1 << 9)
#घोषणा CPU_BOOT_DEV_STS0_FW_HARD_RST_EN		(1 << 10)
#घोषणा CPU_BOOT_DEV_STS0_PLL_INFO_EN			(1 << 11)
#घोषणा CPU_BOOT_DEV_STS0_SP_SRAM_EN			(1 << 12)
#घोषणा CPU_BOOT_DEV_STS0_CLK_GATE_EN			(1 << 13)
#घोषणा CPU_BOOT_DEV_STS0_HBM_ECC_EN			(1 << 14)
#घोषणा CPU_BOOT_DEV_STS0_PKT_PI_ACK_EN			(1 << 15)
#घोषणा CPU_BOOT_DEV_STS0_FW_LD_COM_EN			(1 << 16)
#घोषणा CPU_BOOT_DEV_STS0_FW_IATU_CONF_EN		(1 << 17)
#घोषणा CPU_BOOT_DEV_STS0_DYN_PLL_EN			(1 << 19)
#घोषणा CPU_BOOT_DEV_STS0_ENABLED			(1 << 31)

क्रमागत cpu_boot_status अणु
	CPU_BOOT_STATUS_NA = 0,		/* Default value after reset of chip */
	CPU_BOOT_STATUS_IN_WFE = 1,
	CPU_BOOT_STATUS_DRAM_RDY = 2,
	CPU_BOOT_STATUS_SRAM_AVAIL = 3,
	CPU_BOOT_STATUS_IN_BTL = 4,	/* BTL is H/W FSM */
	CPU_BOOT_STATUS_IN_PREBOOT = 5,
	CPU_BOOT_STATUS_IN_SPL,		/* deprecated - not reported */
	CPU_BOOT_STATUS_IN_UBOOT = 7,
	CPU_BOOT_STATUS_DRAM_INIT_FAIL,	/* deprecated - will be हटाओd */
	CPU_BOOT_STATUS_FIT_CORRUPTED,	/* deprecated - will be हटाओd */
	/* U-Boot console prompt activated, commands are not processed */
	CPU_BOOT_STATUS_UBOOT_NOT_READY = 10,
	/* Finished NICs init, reported after DRAM and NICs */
	CPU_BOOT_STATUS_NIC_FW_RDY = 11,
	CPU_BOOT_STATUS_TS_INIT_FAIL,	/* deprecated - will be हटाओd */
	CPU_BOOT_STATUS_DRAM_SKIPPED,	/* deprecated - will be हटाओd */
	CPU_BOOT_STATUS_BMC_WAITING_SKIPPED, /* deprecated - will be हटाओd */
	/* Last boot loader progress status, पढ़ोy to receive commands */
	CPU_BOOT_STATUS_READY_TO_BOOT = 15,
	/* Internal Boot finished, पढ़ोy क्रम boot-fit */
	CPU_BOOT_STATUS_WAITING_FOR_BOOT_FIT = 16,
	/* Internal Security has been initialized, device can be accessed */
	CPU_BOOT_STATUS_SECURITY_READY = 17,
पूर्ण;

क्रमागत kmd_msg अणु
	KMD_MSG_NA = 0,
	KMD_MSG_GOTO_WFE,
	KMD_MSG_FIT_RDY,
	KMD_MSG_SKIP_BMC,
	RESERVED,
	KMD_MSG_RST_DEV,
	KMD_MSG_LAST
पूर्ण;

क्रमागत cpu_msg_status अणु
	CPU_MSG_CLR = 0,
	CPU_MSG_OK,
	CPU_MSG_ERR,
पूर्ण;

/* communication रेजिस्टरs mapping - consider ABI when changing */
काष्ठा cpu_dyn_regs अणु
	uपूर्णांक32_t cpu_pq_base_addr_low;
	uपूर्णांक32_t cpu_pq_base_addr_high;
	uपूर्णांक32_t cpu_pq_length;
	uपूर्णांक32_t cpu_pq_init_status;
	uपूर्णांक32_t cpu_eq_base_addr_low;
	uपूर्णांक32_t cpu_eq_base_addr_high;
	uपूर्णांक32_t cpu_eq_length;
	uपूर्णांक32_t cpu_eq_ci;
	uपूर्णांक32_t cpu_cq_base_addr_low;
	uपूर्णांक32_t cpu_cq_base_addr_high;
	uपूर्णांक32_t cpu_cq_length;
	uपूर्णांक32_t cpu_pf_pq_pi;
	uपूर्णांक32_t cpu_boot_dev_sts0;
	uपूर्णांक32_t cpu_boot_dev_sts1;
	uपूर्णांक32_t cpu_boot_err0;
	uपूर्णांक32_t cpu_boot_err1;
	uपूर्णांक32_t cpu_boot_status;
	uपूर्णांक32_t fw_upd_sts;
	uपूर्णांक32_t fw_upd_cmd;
	uपूर्णांक32_t fw_upd_pending_sts;
	uपूर्णांक32_t fuse_ver_offset;
	uपूर्णांक32_t preboot_ver_offset;
	uपूर्णांक32_t uboot_ver_offset;
	uपूर्णांक32_t hw_state;
	uपूर्णांक32_t kmd_msg_to_cpu;
	uपूर्णांक32_t cpu_cmd_status_to_host;
	uपूर्णांक32_t reserved1[32];		/* reserve क्रम future use */
पूर्ण;

/* HCDM - Habana Communications Descriptor Magic */
#घोषणा HL_COMMS_DESC_MAGIC	0x4843444D
#घोषणा HL_COMMS_DESC_VER	1

/* this is the comms descriptor header - meta data */
काष्ठा comms_desc_header अणु
	uपूर्णांक32_t magic;		/* magic क्रम validation */
	uपूर्णांक32_t crc32;		/* CRC32 of the descriptor w/o header */
	uपूर्णांक16_t size;		/* size of the descriptor w/o header */
	uपूर्णांक8_t version;	/* descriptor version */
	uपूर्णांक8_t reserved[5];	/* pad to 64 bit */
पूर्ण;

/* this is the मुख्य FW descriptor - consider ABI when changing */
काष्ठा lkd_fw_comms_desc अणु
	काष्ठा comms_desc_header header;
	काष्ठा cpu_dyn_regs cpu_dyn_regs;
	अक्षर fuse_ver[VERSION_MAX_LEN];
	अक्षर cur_fw_ver[VERSION_MAX_LEN];
	/* can be used क्रम 1 more version w/o ABI change */
	अक्षर reserved0[VERSION_MAX_LEN];
	uपूर्णांक64_t img_addr;	/* address क्रम next FW component load */
पूर्ण;

/*
 * LKD commands:
 *
 * COMMS_NOOP			Used to clear the command रेजिस्टर and no actual
 *				command is send.
 *
 * COMMS_CLR_STS		Clear status command - FW should clear the
 *				status रेजिस्टर. Used क्रम synchronization
 *				between the commands as part of the race मुक्त
 *				protocol.
 *
 * COMMS_RST_STATE		Reset the current communication state which is
 *				kept by FW क्रम proper responses.
 *				Should be used in the beginning of the
 *				communication cycle to clean any leftovers from
 *				previous communication attempts.
 *
 * COMMS_PREP_DESC		Prepare descriptor क्रम setting up the
 *				communication and other dynamic data:
 *				काष्ठा lkd_fw_comms_desc.
 *				This command has a parameter stating the next FW
 *				component size, so the FW can actually prepare a
 *				space क्रम it and in the status response provide
 *				the descriptor offset. The Offset of the next FW
 *				data component is a part of the descriptor
 *				काष्ठाure.
 *
 * COMMS_DATA_RDY		The FW data has been uploaded and is पढ़ोy क्रम
 *				validation.
 *
 * COMMS_EXEC			Execute the next FW component.
 *
 * COMMS_RST_DEV		Reset the device.
 *
 * COMMS_GOTO_WFE		Execute WFE command. Allowed only on non-secure
 *				devices.
 *
 * COMMS_SKIP_BMC		Perक्रमm actions required क्रम BMC-less servers.
 *				Do not रुको क्रम BMC response.
 *
 * COMMS_LOW_PLL_OPP		Initialize PLLs क्रम low OPP.
 */
क्रमागत comms_cmd अणु
	COMMS_NOOP = 0,
	COMMS_CLR_STS = 1,
	COMMS_RST_STATE = 2,
	COMMS_PREP_DESC = 3,
	COMMS_DATA_RDY = 4,
	COMMS_EXEC = 5,
	COMMS_RST_DEV = 6,
	COMMS_GOTO_WFE = 7,
	COMMS_SKIP_BMC = 8,
	COMMS_LOW_PLL_OPP = 9,
	COMMS_INVLD_LAST
पूर्ण;

#घोषणा COMMS_COMMAND_SIZE_SHIFT	0
#घोषणा COMMS_COMMAND_SIZE_MASK		0x1FFFFFF
#घोषणा COMMS_COMMAND_CMD_SHIFT		27
#घोषणा COMMS_COMMAND_CMD_MASK		0xF8000000

/*
 * LKD command to FW रेजिस्टर काष्ठाure
 * @size	- FW component size
 * @cmd		- command from क्रमागत comms_cmd
 */
काष्ठा comms_command अणु
	जोड़ अणु		/* bit fields are only क्रम FW use */
		काष्ठा अणु
			अचिन्हित पूर्णांक size :25;		/* 32MB max. */
			अचिन्हित पूर्णांक reserved :2;
			क्रमागत comms_cmd cmd :5;		/* 32 commands */
		पूर्ण;
		अचिन्हित पूर्णांक val;
	पूर्ण;
पूर्ण;

/*
 * FW status
 *
 * COMMS_STS_NOOP		Used to clear the status रेजिस्टर and no actual
 *				status is provided.
 *
 * COMMS_STS_ACK		Command has been received and recognized.
 *
 * COMMS_STS_OK			Command execution has finished successfully.
 *
 * COMMS_STS_ERR		Command execution was unsuccessful and resulted
 *				in error.
 *
 * COMMS_STS_VALID_ERR		FW validation has failed.
 *
 * COMMS_STS_TIMEOUT_ERR	Command execution has समयd out.
 */
क्रमागत comms_sts अणु
	COMMS_STS_NOOP = 0,
	COMMS_STS_ACK = 1,
	COMMS_STS_OK = 2,
	COMMS_STS_ERR = 3,
	COMMS_STS_VALID_ERR = 4,
	COMMS_STS_TIMEOUT_ERR = 5,
	COMMS_STS_INVLD_LAST
पूर्ण;

/* RAM types क्रम FW components loading - defines the base address */
क्रमागत comms_ram_types अणु
	COMMS_SRAM = 0,
	COMMS_DRAM = 1,
पूर्ण;

#घोषणा COMMS_STATUS_OFFSET_SHIFT	0
#घोषणा COMMS_STATUS_OFFSET_MASK	0x03FFFFFF
#घोषणा COMMS_STATUS_OFFSET_ALIGN_SHIFT	2
#घोषणा COMMS_STATUS_RAM_TYPE_SHIFT	26
#घोषणा COMMS_STATUS_RAM_TYPE_MASK	0x0C000000
#घोषणा COMMS_STATUS_STATUS_SHIFT	28
#घोषणा COMMS_STATUS_STATUS_MASK	0xF0000000

/*
 * FW status to LKD रेजिस्टर काष्ठाure
 * @offset	- an offset from the base of the ram_type shअगरted right by
 *		  2 bits (always aligned to 32 bits).
 *		  Allows a maximum addressable offset of 256MB from RAM base.
 *		  Example: क्रम real offset in RAM of 0x800000 (8MB), the value
 *		  in offset field is (0x800000 >> 2) = 0x200000.
 * @ram_type	- the RAM type that should be used क्रम offset from
 *		  क्रमागत comms_ram_types
 * @status	- status from क्रमागत comms_sts
 */
काष्ठा comms_status अणु
	जोड़ अणु		/* bit fields are only क्रम FW use */
		काष्ठा अणु
			अचिन्हित पूर्णांक offset :26;
			अचिन्हित पूर्णांक ram_type :2;
			क्रमागत comms_sts status :4;	/* 16 statuses */
		पूर्ण;
		अचिन्हित पूर्णांक val;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* HL_BOOT_IF_H */
