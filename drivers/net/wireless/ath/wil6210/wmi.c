<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>

#समावेश "wil6210.h"
#समावेश "txrx.h"
#समावेश "wmi.h"
#समावेश "trace.h"

/* set the शेष max assoc sta to max supported by driver */
uपूर्णांक max_assoc_sta = WIL6210_MAX_CID;
module_param(max_assoc_sta, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_assoc_sta, " Max number of stations associated to the AP");

पूर्णांक agg_wsize; /* = 0; */
module_param(agg_wsize, पूर्णांक, 0644);
MODULE_PARM_DESC(agg_wsize, " Window size for Tx Block Ack after connect;"
		 " 0 - use default; < 0 - don't auto-establish");

u8 led_id = WIL_LED_INVALID_ID;
module_param(led_id, byte, 0444);
MODULE_PARM_DESC(led_id,
		 " 60G device led enablement. Set the led ID (0-2) to enable");

#घोषणा WIL_WAIT_FOR_SUSPEND_RESUME_COMP 200
#घोषणा WIL_WMI_PCP_STOP_TO_MS 5000

/**
 * DOC: WMI event receiving - theory of operations
 *
 * When firmware about to report WMI event, it fills memory area
 * in the mailbox and उठाओs misc. IRQ. Thपढ़ो पूर्णांकerrupt handler invoked क्रम
 * the misc IRQ, function @wmi_recv_cmd called by thपढ़ो IRQ handler.
 *
 * @wmi_recv_cmd पढ़ोs event, allocates memory chunk  and attaches it to the
 * event list @wil->pending_wmi_ev. Then, work queue @wil->wmi_wq wakes up
 * and handles events within the @wmi_event_worker. Every event get detached
 * from list, processed and deleted.
 *
 * Purpose क्रम this mechanism is to release IRQ thपढ़ो; otherwise,
 * अगर WMI event handling involves another WMI command flow, this 2-nd flow
 * won't be completed because of blocked IRQ thपढ़ो.
 */

/**
 * DOC: Addressing - theory of operations
 *
 * There are several buses present on the WIL6210 card.
 * Same memory areas are visible at dअगरferent address on
 * the dअगरferent busses. There are 3 मुख्य bus masters:
 *  - MAC CPU (ucode)
 *  - User CPU (firmware)
 *  - AHB (host)
 *
 * On the PCI bus, there is one BAR (BAR0) of 2Mb size, exposing
 * AHB addresses starting from 0x880000
 *
 * Internally, firmware uses addresses that allow faster access but
 * are invisible from the host. To पढ़ो from these addresses, alternative
 * AHB address must be used.
 */

/* sparrow_fw_mapping provides memory remapping table क्रम sparrow
 *
 * array size should be in sync with the declaration in the wil6210.h
 *
 * Sparrow memory mapping:
 * Linker address         PCI/Host address
 *                        0x880000 .. 0xa80000  2Mb BAR0
 * 0x800000 .. 0x808000   0x900000 .. 0x908000  32k DCCM
 * 0x840000 .. 0x860000   0x908000 .. 0x928000  128k PERIPH
 */
स्थिर काष्ठा fw_map sparrow_fw_mapping[] = अणु
	/* FW code RAM 256k */
	अणु0x000000, 0x040000, 0x8c0000, "fw_code", true, trueपूर्ण,
	/* FW data RAM 32k */
	अणु0x800000, 0x808000, 0x900000, "fw_data", true, trueपूर्ण,
	/* periph data 128k */
	अणु0x840000, 0x860000, 0x908000, "fw_peri", true, trueपूर्ण,
	/* various RGF 40k */
	अणु0x880000, 0x88a000, 0x880000, "rgf", true, trueपूर्ण,
	/* AGC table   4k */
	अणु0x88a000, 0x88b000, 0x88a000, "AGC_tbl", true, trueपूर्ण,
	/* Pcie_ext_rgf 4k */
	अणु0x88b000, 0x88c000, 0x88b000, "rgf_ext", true, trueपूर्ण,
	/* mac_ext_rgf 512b */
	अणु0x88c000, 0x88c200, 0x88c000, "mac_rgf_ext", true, trueपूर्ण,
	/* upper area 548k */
	अणु0x8c0000, 0x949000, 0x8c0000, "upper", true, trueपूर्ण,
	/* UCODE areas - accessible by debugfs blobs but not by
	 * wmi_addr_remap. UCODE areas MUST be added AFTER FW areas!
	 */
	/* ucode code RAM 128k */
	अणु0x000000, 0x020000, 0x920000, "uc_code", false, falseपूर्ण,
	/* ucode data RAM 16k */
	अणु0x800000, 0x804000, 0x940000, "uc_data", false, falseपूर्ण,
पूर्ण;

/* sparrow_d0_mac_rgf_ext - mac_rgf_ext section क्रम Sparrow D0
 * it is a bit larger to support extra features
 */
स्थिर काष्ठा fw_map sparrow_d0_mac_rgf_ext = अणु
	0x88c000, 0x88c500, 0x88c000, "mac_rgf_ext", true, true
पूर्ण;

/* talyn_fw_mapping provides memory remapping table क्रम Talyn
 *
 * array size should be in sync with the declaration in the wil6210.h
 *
 * Talyn memory mapping:
 * Linker address         PCI/Host address
 *                        0x880000 .. 0xc80000  4Mb BAR0
 * 0x800000 .. 0x820000   0xa00000 .. 0xa20000  128k DCCM
 * 0x840000 .. 0x858000   0xa20000 .. 0xa38000  96k PERIPH
 */
स्थिर काष्ठा fw_map talyn_fw_mapping[] = अणु
	/* FW code RAM 1M */
	अणु0x000000, 0x100000, 0x900000, "fw_code", true, trueपूर्ण,
	/* FW data RAM 128k */
	अणु0x800000, 0x820000, 0xa00000, "fw_data", true, trueपूर्ण,
	/* periph. data RAM 96k */
	अणु0x840000, 0x858000, 0xa20000, "fw_peri", true, trueपूर्ण,
	/* various RGF 40k */
	अणु0x880000, 0x88a000, 0x880000, "rgf", true, trueपूर्ण,
	/* AGC table 4k */
	अणु0x88a000, 0x88b000, 0x88a000, "AGC_tbl", true, trueपूर्ण,
	/* Pcie_ext_rgf 4k */
	अणु0x88b000, 0x88c000, 0x88b000, "rgf_ext", true, trueपूर्ण,
	/* mac_ext_rgf 1344b */
	अणु0x88c000, 0x88c540, 0x88c000, "mac_rgf_ext", true, trueपूर्ण,
	/* ext USER RGF 4k */
	अणु0x88d000, 0x88e000, 0x88d000, "ext_user_rgf", true, trueपूर्ण,
	/* OTP 4k */
	अणु0x8a0000, 0x8a1000, 0x8a0000, "otp", true, falseपूर्ण,
	/* DMA EXT RGF 64k */
	अणु0x8b0000, 0x8c0000, 0x8b0000, "dma_ext_rgf", true, trueपूर्ण,
	/* upper area 1536k */
	अणु0x900000, 0xa80000, 0x900000, "upper", true, trueपूर्ण,
	/* UCODE areas - accessible by debugfs blobs but not by
	 * wmi_addr_remap. UCODE areas MUST be added AFTER FW areas!
	 */
	/* ucode code RAM 256k */
	अणु0x000000, 0x040000, 0xa38000, "uc_code", false, falseपूर्ण,
	/* ucode data RAM 32k */
	अणु0x800000, 0x808000, 0xa78000, "uc_data", false, falseपूर्ण,
पूर्ण;

/* talyn_mb_fw_mapping provides memory remapping table क्रम Talyn-MB
 *
 * array size should be in sync with the declaration in the wil6210.h
 *
 * Talyn MB memory mapping:
 * Linker address         PCI/Host address
 *                        0x880000 .. 0xc80000  4Mb BAR0
 * 0x800000 .. 0x820000   0xa00000 .. 0xa20000  128k DCCM
 * 0x840000 .. 0x858000   0xa20000 .. 0xa38000  96k PERIPH
 */
स्थिर काष्ठा fw_map talyn_mb_fw_mapping[] = अणु
	/* FW code RAM 768k */
	अणु0x000000, 0x0c0000, 0x900000, "fw_code", true, trueपूर्ण,
	/* FW data RAM 128k */
	अणु0x800000, 0x820000, 0xa00000, "fw_data", true, trueपूर्ण,
	/* periph. data RAM 96k */
	अणु0x840000, 0x858000, 0xa20000, "fw_peri", true, trueपूर्ण,
	/* various RGF 40k */
	अणु0x880000, 0x88a000, 0x880000, "rgf", true, trueपूर्ण,
	/* AGC table 4k */
	अणु0x88a000, 0x88b000, 0x88a000, "AGC_tbl", true, trueपूर्ण,
	/* Pcie_ext_rgf 4k */
	अणु0x88b000, 0x88c000, 0x88b000, "rgf_ext", true, trueपूर्ण,
	/* mac_ext_rgf 2256b */
	अणु0x88c000, 0x88c8d0, 0x88c000, "mac_rgf_ext", true, trueपूर्ण,
	/* ext USER RGF 4k */
	अणु0x88d000, 0x88e000, 0x88d000, "ext_user_rgf", true, trueपूर्ण,
	/* SEC PKA 16k */
	अणु0x890000, 0x894000, 0x890000, "sec_pka", true, trueपूर्ण,
	/* SEC KDF RGF 3096b */
	अणु0x898000, 0x898c18, 0x898000, "sec_kdf_rgf", true, trueपूर्ण,
	/* SEC MAIN 2124b */
	अणु0x89a000, 0x89a84c, 0x89a000, "sec_main", true, trueपूर्ण,
	/* OTP 4k */
	अणु0x8a0000, 0x8a1000, 0x8a0000, "otp", true, falseपूर्ण,
	/* DMA EXT RGF 64k */
	अणु0x8b0000, 0x8c0000, 0x8b0000, "dma_ext_rgf", true, trueपूर्ण,
	/* DUM USER RGF 528b */
	अणु0x8c0000, 0x8c0210, 0x8c0000, "dum_user_rgf", true, trueपूर्ण,
	/* DMA OFU 296b */
	अणु0x8c2000, 0x8c2128, 0x8c2000, "dma_ofu", true, trueपूर्ण,
	/* ucode debug 256b */
	अणु0x8c3000, 0x8c3100, 0x8c3000, "ucode_debug", true, trueपूर्ण,
	/* upper area 1536k */
	अणु0x900000, 0xa80000, 0x900000, "upper", true, trueपूर्ण,
	/* UCODE areas - accessible by debugfs blobs but not by
	 * wmi_addr_remap. UCODE areas MUST be added AFTER FW areas!
	 */
	/* ucode code RAM 256k */
	अणु0x000000, 0x040000, 0xa38000, "uc_code", false, falseपूर्ण,
	/* ucode data RAM 32k */
	अणु0x800000, 0x808000, 0xa78000, "uc_data", false, falseपूर्ण,
पूर्ण;

काष्ठा fw_map fw_mapping[MAX_FW_MAPPING_TABLE_SIZE];

काष्ठा blink_on_off_समय led_blink_समय[] = अणु
	अणुWIL_LED_BLINK_ON_SLOW_MS, WIL_LED_BLINK_OFF_SLOW_MSपूर्ण,
	अणुWIL_LED_BLINK_ON_MED_MS, WIL_LED_BLINK_OFF_MED_MSपूर्ण,
	अणुWIL_LED_BLINK_ON_FAST_MS, WIL_LED_BLINK_OFF_FAST_MSपूर्ण,
पूर्ण;

काष्ठा auth_no_hdr अणु
	__le16 auth_alg;
	__le16 auth_transaction;
	__le16 status_code;
	/* possibly followed by Challenge text */
	u8 variable[];
पूर्ण __packed;

u8 led_polarity = LED_POLARITY_LOW_ACTIVE;

/**
 * वापस AHB address क्रम given firmware पूर्णांकernal (linker) address
 * @x: पूर्णांकernal address
 * If address have no valid AHB mapping, वापस 0
 */
अटल u32 wmi_addr_remap(u32 x)
अणु
	uपूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_mapping); i++) अणु
		अगर (fw_mapping[i].fw &&
		    ((x >= fw_mapping[i].from) && (x < fw_mapping[i].to)))
			वापस x + fw_mapping[i].host - fw_mapping[i].from;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * find fw_mapping entry by section name
 * @section: section name
 *
 * Return poपूर्णांकer to section or शून्य अगर not found
 */
काष्ठा fw_map *wil_find_fw_mapping(स्थिर अक्षर *section)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_mapping); i++)
		अगर (fw_mapping[i].name &&
		    !म_भेद(section, fw_mapping[i].name))
			वापस &fw_mapping[i];

	वापस शून्य;
पूर्ण

/**
 * Check address validity क्रम WMI buffer; remap अगर needed
 * @wil: driver data
 * @ptr_: पूर्णांकernal (linker) fw/ucode address
 * @size: अगर non zero, validate the block करोes not
 *  exceed the device memory (bar)
 *
 * Valid buffer should be DWORD aligned
 *
 * वापस address क्रम accessing buffer from the host;
 * अगर buffer is not valid, वापस शून्य.
 */
व्योम __iomem *wmi_buffer_block(काष्ठा wil6210_priv *wil, __le32 ptr_, u32 size)
अणु
	u32 off;
	u32 ptr = le32_to_cpu(ptr_);

	अगर (ptr % 4)
		वापस शून्य;

	ptr = wmi_addr_remap(ptr);
	अगर (ptr < WIL6210_FW_HOST_OFF)
		वापस शून्य;

	off = HOSTADDR(ptr);
	अगर (off > wil->bar_size - 4)
		वापस शून्य;
	अगर (size && ((off + size > wil->bar_size) || (off + size < off)))
		वापस शून्य;

	वापस wil->csr + off;
पूर्ण

व्योम __iomem *wmi_buffer(काष्ठा wil6210_priv *wil, __le32 ptr_)
अणु
	वापस wmi_buffer_block(wil, ptr_, 0);
पूर्ण

/* Check address validity */
व्योम __iomem *wmi_addr(काष्ठा wil6210_priv *wil, u32 ptr)
अणु
	u32 off;

	अगर (ptr % 4)
		वापस शून्य;

	अगर (ptr < WIL6210_FW_HOST_OFF)
		वापस शून्य;

	off = HOSTADDR(ptr);
	अगर (off > wil->bar_size - 4)
		वापस शून्य;

	वापस wil->csr + off;
पूर्ण

पूर्णांक wmi_पढ़ो_hdr(काष्ठा wil6210_priv *wil, __le32 ptr,
		 काष्ठा wil6210_mbox_hdr *hdr)
अणु
	व्योम __iomem *src = wmi_buffer(wil, ptr);

	अगर (!src)
		वापस -EINVAL;

	wil_स_नकल_fromio_32(hdr, src, माप(*hdr));

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *cmdid2name(u16 cmdid)
अणु
	चयन (cmdid) अणु
	हाल WMI_NOTIFY_REQ_CMDID:
		वापस "WMI_NOTIFY_REQ_CMD";
	हाल WMI_START_SCAN_CMDID:
		वापस "WMI_START_SCAN_CMD";
	हाल WMI_CONNECT_CMDID:
		वापस "WMI_CONNECT_CMD";
	हाल WMI_DISCONNECT_CMDID:
		वापस "WMI_DISCONNECT_CMD";
	हाल WMI_SW_TX_REQ_CMDID:
		वापस "WMI_SW_TX_REQ_CMD";
	हाल WMI_GET_RF_SECTOR_PARAMS_CMDID:
		वापस "WMI_GET_RF_SECTOR_PARAMS_CMD";
	हाल WMI_SET_RF_SECTOR_PARAMS_CMDID:
		वापस "WMI_SET_RF_SECTOR_PARAMS_CMD";
	हाल WMI_GET_SELECTED_RF_SECTOR_INDEX_CMDID:
		वापस "WMI_GET_SELECTED_RF_SECTOR_INDEX_CMD";
	हाल WMI_SET_SELECTED_RF_SECTOR_INDEX_CMDID:
		वापस "WMI_SET_SELECTED_RF_SECTOR_INDEX_CMD";
	हाल WMI_BRP_SET_ANT_LIMIT_CMDID:
		वापस "WMI_BRP_SET_ANT_LIMIT_CMD";
	हाल WMI_TOF_SESSION_START_CMDID:
		वापस "WMI_TOF_SESSION_START_CMD";
	हाल WMI_AOA_MEAS_CMDID:
		वापस "WMI_AOA_MEAS_CMD";
	हाल WMI_PMC_CMDID:
		वापस "WMI_PMC_CMD";
	हाल WMI_TOF_GET_TX_RX_OFFSET_CMDID:
		वापस "WMI_TOF_GET_TX_RX_OFFSET_CMD";
	हाल WMI_TOF_SET_TX_RX_OFFSET_CMDID:
		वापस "WMI_TOF_SET_TX_RX_OFFSET_CMD";
	हाल WMI_VRING_CFG_CMDID:
		वापस "WMI_VRING_CFG_CMD";
	हाल WMI_BCAST_VRING_CFG_CMDID:
		वापस "WMI_BCAST_VRING_CFG_CMD";
	हाल WMI_TRAFFIC_SUSPEND_CMDID:
		वापस "WMI_TRAFFIC_SUSPEND_CMD";
	हाल WMI_TRAFFIC_RESUME_CMDID:
		वापस "WMI_TRAFFIC_RESUME_CMD";
	हाल WMI_ECHO_CMDID:
		वापस "WMI_ECHO_CMD";
	हाल WMI_SET_MAC_ADDRESS_CMDID:
		वापस "WMI_SET_MAC_ADDRESS_CMD";
	हाल WMI_LED_CFG_CMDID:
		वापस "WMI_LED_CFG_CMD";
	हाल WMI_PCP_START_CMDID:
		वापस "WMI_PCP_START_CMD";
	हाल WMI_PCP_STOP_CMDID:
		वापस "WMI_PCP_STOP_CMD";
	हाल WMI_SET_SSID_CMDID:
		वापस "WMI_SET_SSID_CMD";
	हाल WMI_GET_SSID_CMDID:
		वापस "WMI_GET_SSID_CMD";
	हाल WMI_SET_PCP_CHANNEL_CMDID:
		वापस "WMI_SET_PCP_CHANNEL_CMD";
	हाल WMI_GET_PCP_CHANNEL_CMDID:
		वापस "WMI_GET_PCP_CHANNEL_CMD";
	हाल WMI_P2P_CFG_CMDID:
		वापस "WMI_P2P_CFG_CMD";
	हाल WMI_PORT_ALLOCATE_CMDID:
		वापस "WMI_PORT_ALLOCATE_CMD";
	हाल WMI_PORT_DELETE_CMDID:
		वापस "WMI_PORT_DELETE_CMD";
	हाल WMI_START_LISTEN_CMDID:
		वापस "WMI_START_LISTEN_CMD";
	हाल WMI_START_SEARCH_CMDID:
		वापस "WMI_START_SEARCH_CMD";
	हाल WMI_DISCOVERY_STOP_CMDID:
		वापस "WMI_DISCOVERY_STOP_CMD";
	हाल WMI_DELETE_CIPHER_KEY_CMDID:
		वापस "WMI_DELETE_CIPHER_KEY_CMD";
	हाल WMI_ADD_CIPHER_KEY_CMDID:
		वापस "WMI_ADD_CIPHER_KEY_CMD";
	हाल WMI_SET_APPIE_CMDID:
		वापस "WMI_SET_APPIE_CMD";
	हाल WMI_CFG_RX_CHAIN_CMDID:
		वापस "WMI_CFG_RX_CHAIN_CMD";
	हाल WMI_TEMP_SENSE_CMDID:
		वापस "WMI_TEMP_SENSE_CMD";
	हाल WMI_DEL_STA_CMDID:
		वापस "WMI_DEL_STA_CMD";
	हाल WMI_DISCONNECT_STA_CMDID:
		वापस "WMI_DISCONNECT_STA_CMD";
	हाल WMI_RING_BA_EN_CMDID:
		वापस "WMI_RING_BA_EN_CMD";
	हाल WMI_RING_BA_DIS_CMDID:
		वापस "WMI_RING_BA_DIS_CMD";
	हाल WMI_RCP_DELBA_CMDID:
		वापस "WMI_RCP_DELBA_CMD";
	हाल WMI_RCP_ADDBA_RESP_CMDID:
		वापस "WMI_RCP_ADDBA_RESP_CMD";
	हाल WMI_RCP_ADDBA_RESP_EDMA_CMDID:
		वापस "WMI_RCP_ADDBA_RESP_EDMA_CMD";
	हाल WMI_PS_DEV_PROखाता_CFG_CMDID:
		वापस "WMI_PS_DEV_PROFILE_CFG_CMD";
	हाल WMI_SET_MGMT_RETRY_LIMIT_CMDID:
		वापस "WMI_SET_MGMT_RETRY_LIMIT_CMD";
	हाल WMI_GET_MGMT_RETRY_LIMIT_CMDID:
		वापस "WMI_GET_MGMT_RETRY_LIMIT_CMD";
	हाल WMI_ABORT_SCAN_CMDID:
		वापस "WMI_ABORT_SCAN_CMD";
	हाल WMI_NEW_STA_CMDID:
		वापस "WMI_NEW_STA_CMD";
	हाल WMI_SET_THERMAL_THROTTLING_CFG_CMDID:
		वापस "WMI_SET_THERMAL_THROTTLING_CFG_CMD";
	हाल WMI_GET_THERMAL_THROTTLING_CFG_CMDID:
		वापस "WMI_GET_THERMAL_THROTTLING_CFG_CMD";
	हाल WMI_LINK_MAINTAIN_CFG_WRITE_CMDID:
		वापस "WMI_LINK_MAINTAIN_CFG_WRITE_CMD";
	हाल WMI_LO_POWER_CALIB_FROM_OTP_CMDID:
		वापस "WMI_LO_POWER_CALIB_FROM_OTP_CMD";
	हाल WMI_START_SCHED_SCAN_CMDID:
		वापस "WMI_START_SCHED_SCAN_CMD";
	हाल WMI_STOP_SCHED_SCAN_CMDID:
		वापस "WMI_STOP_SCHED_SCAN_CMD";
	हाल WMI_TX_STATUS_RING_ADD_CMDID:
		वापस "WMI_TX_STATUS_RING_ADD_CMD";
	हाल WMI_RX_STATUS_RING_ADD_CMDID:
		वापस "WMI_RX_STATUS_RING_ADD_CMD";
	हाल WMI_TX_DESC_RING_ADD_CMDID:
		वापस "WMI_TX_DESC_RING_ADD_CMD";
	हाल WMI_RX_DESC_RING_ADD_CMDID:
		वापस "WMI_RX_DESC_RING_ADD_CMD";
	हाल WMI_BCAST_DESC_RING_ADD_CMDID:
		वापस "WMI_BCAST_DESC_RING_ADD_CMD";
	हाल WMI_CFG_DEF_RX_OFFLOAD_CMDID:
		वापस "WMI_CFG_DEF_RX_OFFLOAD_CMD";
	हाल WMI_LINK_STATS_CMDID:
		वापस "WMI_LINK_STATS_CMD";
	हाल WMI_SW_TX_REQ_EXT_CMDID:
		वापस "WMI_SW_TX_REQ_EXT_CMDID";
	हाल WMI_FT_AUTH_CMDID:
		वापस "WMI_FT_AUTH_CMD";
	हाल WMI_FT_REASSOC_CMDID:
		वापस "WMI_FT_REASSOC_CMD";
	हाल WMI_UPDATE_FT_IES_CMDID:
		वापस "WMI_UPDATE_FT_IES_CMD";
	हाल WMI_RBUFCAP_CFG_CMDID:
		वापस "WMI_RBUFCAP_CFG_CMD";
	हाल WMI_TEMP_SENSE_ALL_CMDID:
		वापस "WMI_TEMP_SENSE_ALL_CMDID";
	हाल WMI_SET_LINK_MONITOR_CMDID:
		वापस "WMI_SET_LINK_MONITOR_CMD";
	शेष:
		वापस "Untracked CMD";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *eventid2name(u16 eventid)
अणु
	चयन (eventid) अणु
	हाल WMI_NOTIFY_REQ_DONE_EVENTID:
		वापस "WMI_NOTIFY_REQ_DONE_EVENT";
	हाल WMI_DISCONNECT_EVENTID:
		वापस "WMI_DISCONNECT_EVENT";
	हाल WMI_SW_TX_COMPLETE_EVENTID:
		वापस "WMI_SW_TX_COMPLETE_EVENT";
	हाल WMI_GET_RF_SECTOR_PARAMS_DONE_EVENTID:
		वापस "WMI_GET_RF_SECTOR_PARAMS_DONE_EVENT";
	हाल WMI_SET_RF_SECTOR_PARAMS_DONE_EVENTID:
		वापस "WMI_SET_RF_SECTOR_PARAMS_DONE_EVENT";
	हाल WMI_GET_SELECTED_RF_SECTOR_INDEX_DONE_EVENTID:
		वापस "WMI_GET_SELECTED_RF_SECTOR_INDEX_DONE_EVENT";
	हाल WMI_SET_SELECTED_RF_SECTOR_INDEX_DONE_EVENTID:
		वापस "WMI_SET_SELECTED_RF_SECTOR_INDEX_DONE_EVENT";
	हाल WMI_BRP_SET_ANT_LIMIT_EVENTID:
		वापस "WMI_BRP_SET_ANT_LIMIT_EVENT";
	हाल WMI_FW_READY_EVENTID:
		वापस "WMI_FW_READY_EVENT";
	हाल WMI_TRAFFIC_RESUME_EVENTID:
		वापस "WMI_TRAFFIC_RESUME_EVENT";
	हाल WMI_TOF_GET_TX_RX_OFFSET_EVENTID:
		वापस "WMI_TOF_GET_TX_RX_OFFSET_EVENT";
	हाल WMI_TOF_SET_TX_RX_OFFSET_EVENTID:
		वापस "WMI_TOF_SET_TX_RX_OFFSET_EVENT";
	हाल WMI_VRING_CFG_DONE_EVENTID:
		वापस "WMI_VRING_CFG_DONE_EVENT";
	हाल WMI_READY_EVENTID:
		वापस "WMI_READY_EVENT";
	हाल WMI_RX_MGMT_PACKET_EVENTID:
		वापस "WMI_RX_MGMT_PACKET_EVENT";
	हाल WMI_TX_MGMT_PACKET_EVENTID:
		वापस "WMI_TX_MGMT_PACKET_EVENT";
	हाल WMI_SCAN_COMPLETE_EVENTID:
		वापस "WMI_SCAN_COMPLETE_EVENT";
	हाल WMI_ACS_PASSIVE_SCAN_COMPLETE_EVENTID:
		वापस "WMI_ACS_PASSIVE_SCAN_COMPLETE_EVENT";
	हाल WMI_CONNECT_EVENTID:
		वापस "WMI_CONNECT_EVENT";
	हाल WMI_EAPOL_RX_EVENTID:
		वापस "WMI_EAPOL_RX_EVENT";
	हाल WMI_BA_STATUS_EVENTID:
		वापस "WMI_BA_STATUS_EVENT";
	हाल WMI_RCP_ADDBA_REQ_EVENTID:
		वापस "WMI_RCP_ADDBA_REQ_EVENT";
	हाल WMI_DELBA_EVENTID:
		वापस "WMI_DELBA_EVENT";
	हाल WMI_RING_EN_EVENTID:
		वापस "WMI_RING_EN_EVENT";
	हाल WMI_DATA_PORT_OPEN_EVENTID:
		वापस "WMI_DATA_PORT_OPEN_EVENT";
	हाल WMI_AOA_MEAS_EVENTID:
		वापस "WMI_AOA_MEAS_EVENT";
	हाल WMI_TOF_SESSION_END_EVENTID:
		वापस "WMI_TOF_SESSION_END_EVENT";
	हाल WMI_TOF_GET_CAPABILITIES_EVENTID:
		वापस "WMI_TOF_GET_CAPABILITIES_EVENT";
	हाल WMI_TOF_SET_LCR_EVENTID:
		वापस "WMI_TOF_SET_LCR_EVENT";
	हाल WMI_TOF_SET_LCI_EVENTID:
		वापस "WMI_TOF_SET_LCI_EVENT";
	हाल WMI_TOF_FTM_PER_DEST_RES_EVENTID:
		वापस "WMI_TOF_FTM_PER_DEST_RES_EVENT";
	हाल WMI_TOF_CHANNEL_INFO_EVENTID:
		वापस "WMI_TOF_CHANNEL_INFO_EVENT";
	हाल WMI_TRAFFIC_SUSPEND_EVENTID:
		वापस "WMI_TRAFFIC_SUSPEND_EVENT";
	हाल WMI_ECHO_RSP_EVENTID:
		वापस "WMI_ECHO_RSP_EVENT";
	हाल WMI_LED_CFG_DONE_EVENTID:
		वापस "WMI_LED_CFG_DONE_EVENT";
	हाल WMI_PCP_STARTED_EVENTID:
		वापस "WMI_PCP_STARTED_EVENT";
	हाल WMI_PCP_STOPPED_EVENTID:
		वापस "WMI_PCP_STOPPED_EVENT";
	हाल WMI_GET_SSID_EVENTID:
		वापस "WMI_GET_SSID_EVENT";
	हाल WMI_GET_PCP_CHANNEL_EVENTID:
		वापस "WMI_GET_PCP_CHANNEL_EVENT";
	हाल WMI_P2P_CFG_DONE_EVENTID:
		वापस "WMI_P2P_CFG_DONE_EVENT";
	हाल WMI_PORT_ALLOCATED_EVENTID:
		वापस "WMI_PORT_ALLOCATED_EVENT";
	हाल WMI_PORT_DELETED_EVENTID:
		वापस "WMI_PORT_DELETED_EVENT";
	हाल WMI_LISTEN_STARTED_EVENTID:
		वापस "WMI_LISTEN_STARTED_EVENT";
	हाल WMI_SEARCH_STARTED_EVENTID:
		वापस "WMI_SEARCH_STARTED_EVENT";
	हाल WMI_DISCOVERY_STOPPED_EVENTID:
		वापस "WMI_DISCOVERY_STOPPED_EVENT";
	हाल WMI_CFG_RX_CHAIN_DONE_EVENTID:
		वापस "WMI_CFG_RX_CHAIN_DONE_EVENT";
	हाल WMI_TEMP_SENSE_DONE_EVENTID:
		वापस "WMI_TEMP_SENSE_DONE_EVENT";
	हाल WMI_RCP_ADDBA_RESP_SENT_EVENTID:
		वापस "WMI_RCP_ADDBA_RESP_SENT_EVENT";
	हाल WMI_PS_DEV_PROखाता_CFG_EVENTID:
		वापस "WMI_PS_DEV_PROFILE_CFG_EVENT";
	हाल WMI_SET_MGMT_RETRY_LIMIT_EVENTID:
		वापस "WMI_SET_MGMT_RETRY_LIMIT_EVENT";
	हाल WMI_GET_MGMT_RETRY_LIMIT_EVENTID:
		वापस "WMI_GET_MGMT_RETRY_LIMIT_EVENT";
	हाल WMI_SET_THERMAL_THROTTLING_CFG_EVENTID:
		वापस "WMI_SET_THERMAL_THROTTLING_CFG_EVENT";
	हाल WMI_GET_THERMAL_THROTTLING_CFG_EVENTID:
		वापस "WMI_GET_THERMAL_THROTTLING_CFG_EVENT";
	हाल WMI_LINK_MAINTAIN_CFG_WRITE_DONE_EVENTID:
		वापस "WMI_LINK_MAINTAIN_CFG_WRITE_DONE_EVENT";
	हाल WMI_LO_POWER_CALIB_FROM_OTP_EVENTID:
		वापस "WMI_LO_POWER_CALIB_FROM_OTP_EVENT";
	हाल WMI_START_SCHED_SCAN_EVENTID:
		वापस "WMI_START_SCHED_SCAN_EVENT";
	हाल WMI_STOP_SCHED_SCAN_EVENTID:
		वापस "WMI_STOP_SCHED_SCAN_EVENT";
	हाल WMI_SCHED_SCAN_RESULT_EVENTID:
		वापस "WMI_SCHED_SCAN_RESULT_EVENT";
	हाल WMI_TX_STATUS_RING_CFG_DONE_EVENTID:
		वापस "WMI_TX_STATUS_RING_CFG_DONE_EVENT";
	हाल WMI_RX_STATUS_RING_CFG_DONE_EVENTID:
		वापस "WMI_RX_STATUS_RING_CFG_DONE_EVENT";
	हाल WMI_TX_DESC_RING_CFG_DONE_EVENTID:
		वापस "WMI_TX_DESC_RING_CFG_DONE_EVENT";
	हाल WMI_RX_DESC_RING_CFG_DONE_EVENTID:
		वापस "WMI_RX_DESC_RING_CFG_DONE_EVENT";
	हाल WMI_CFG_DEF_RX_OFFLOAD_DONE_EVENTID:
		वापस "WMI_CFG_DEF_RX_OFFLOAD_DONE_EVENT";
	हाल WMI_LINK_STATS_CONFIG_DONE_EVENTID:
		वापस "WMI_LINK_STATS_CONFIG_DONE_EVENT";
	हाल WMI_LINK_STATS_EVENTID:
		वापस "WMI_LINK_STATS_EVENT";
	हाल WMI_COMMAND_NOT_SUPPORTED_EVENTID:
		वापस "WMI_COMMAND_NOT_SUPPORTED_EVENT";
	हाल WMI_FT_AUTH_STATUS_EVENTID:
		वापस "WMI_FT_AUTH_STATUS_EVENT";
	हाल WMI_FT_REASSOC_STATUS_EVENTID:
		वापस "WMI_FT_REASSOC_STATUS_EVENT";
	हाल WMI_RBUFCAP_CFG_EVENTID:
		वापस "WMI_RBUFCAP_CFG_EVENT";
	हाल WMI_TEMP_SENSE_ALL_DONE_EVENTID:
		वापस "WMI_TEMP_SENSE_ALL_DONE_EVENTID";
	हाल WMI_SET_LINK_MONITOR_EVENTID:
		वापस "WMI_SET_LINK_MONITOR_EVENT";
	हाल WMI_LINK_MONITOR_EVENTID:
		वापस "WMI_LINK_MONITOR_EVENT";
	शेष:
		वापस "Untracked EVENT";
	पूर्ण
पूर्ण

अटल पूर्णांक __wmi_send(काष्ठा wil6210_priv *wil, u16 cmdid, u8 mid,
		      व्योम *buf, u16 len)
अणु
	काष्ठा अणु
		काष्ठा wil6210_mbox_hdr hdr;
		काष्ठा wmi_cmd_hdr wmi;
	पूर्ण __packed cmd = अणु
		.hdr = अणु
			.type = WIL_MBOX_HDR_TYPE_WMI,
			.flags = 0,
			.len = cpu_to_le16(माप(cmd.wmi) + len),
		पूर्ण,
		.wmi = अणु
			.mid = mid,
			.command_id = cpu_to_le16(cmdid),
		पूर्ण,
	पूर्ण;
	काष्ठा wil6210_mbox_ring *r = &wil->mbox_ctl.tx;
	काष्ठा wil6210_mbox_ring_desc d_head;
	u32 next_head;
	व्योम __iomem *dst;
	व्योम __iomem *head = wmi_addr(wil, r->head);
	uपूर्णांक retry;
	पूर्णांक rc = 0;

	अगर (len > r->entry_size - माप(cmd)) अणु
		wil_err(wil, "WMI size too large: %d bytes, max is %d\n",
			(पूर्णांक)(माप(cmd) + len), r->entry_size);
		वापस -दुस्फल;
	पूर्ण

	might_sleep();

	अगर (!test_bit(wil_status_fwपढ़ोy, wil->status)) अणु
		wil_err(wil, "WMI: cannot send command while FW not ready\n");
		वापस -EAGAIN;
	पूर्ण

	/* Allow sending only suspend / resume commands during susepnd flow */
	अगर ((test_bit(wil_status_suspending, wil->status) ||
	     test_bit(wil_status_suspended, wil->status) ||
	     test_bit(wil_status_resuming, wil->status)) &&
	     ((cmdid != WMI_TRAFFIC_SUSPEND_CMDID) &&
	      (cmdid != WMI_TRAFFIC_RESUME_CMDID))) अणु
		wil_err(wil, "WMI: reject send_command during suspend\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!head) अणु
		wil_err(wil, "WMI head is garbage: 0x%08x\n", r->head);
		वापस -EINVAL;
	पूर्ण

	wil_halp_vote(wil);

	/* पढ़ो Tx head till it is not busy */
	क्रम (retry = 5; retry > 0; retry--) अणु
		wil_स_नकल_fromio_32(&d_head, head, माप(d_head));
		अगर (d_head.sync == 0)
			अवरोध;
		msleep(20);
	पूर्ण
	अगर (d_head.sync != 0) अणु
		wil_err(wil, "WMI head busy\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	/* next head */
	next_head = r->base + ((r->head - r->base + माप(d_head)) % r->size);
	wil_dbg_wmi(wil, "Head 0x%08x -> 0x%08x\n", r->head, next_head);
	/* रुको till FW finish with previous command */
	क्रम (retry = 5; retry > 0; retry--) अणु
		अगर (!test_bit(wil_status_fwपढ़ोy, wil->status)) अणु
			wil_err(wil, "WMI: cannot send command while FW not ready\n");
			rc = -EAGAIN;
			जाओ out;
		पूर्ण
		r->tail = wil_r(wil, RGF_MBOX +
				दुरत्व(काष्ठा wil6210_mbox_ctl, tx.tail));
		अगर (next_head != r->tail)
			अवरोध;
		msleep(20);
	पूर्ण
	अगर (next_head == r->tail) अणु
		wil_err(wil, "WMI ring full\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	dst = wmi_buffer(wil, d_head.addr);
	अगर (!dst) अणु
		wil_err(wil, "invalid WMI buffer: 0x%08x\n",
			le32_to_cpu(d_head.addr));
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	cmd.hdr.seq = cpu_to_le16(++wil->wmi_seq);
	/* set command */
	wil_dbg_wmi(wil, "sending %s (0x%04x) [%d] mid %d\n",
		    cmdid2name(cmdid), cmdid, len, mid);
	wil_hex_dump_wmi("Cmd ", DUMP_PREFIX_OFFSET, 16, 1, &cmd,
			 माप(cmd), true);
	wil_hex_dump_wmi("cmd ", DUMP_PREFIX_OFFSET, 16, 1, buf,
			 len, true);
	wil_स_नकल_toio_32(dst, &cmd, माप(cmd));
	wil_स_नकल_toio_32(dst + माप(cmd), buf, len);
	/* mark entry as full */
	wil_w(wil, r->head + दुरत्व(काष्ठा wil6210_mbox_ring_desc, sync), 1);
	/* advance next ptr */
	wil_w(wil, RGF_MBOX + दुरत्व(काष्ठा wil6210_mbox_ctl, tx.head),
	      r->head = next_head);

	trace_wil6210_wmi_cmd(&cmd.wmi, buf, len);

	/* पूर्णांकerrupt to FW */
	wil_w(wil, RGF_USER_USER_ICR + दुरत्व(काष्ठा RGF_ICR, ICS),
	      SW_INT_MBOX);

out:
	wil_halp_unvote(wil);
	वापस rc;
पूर्ण

पूर्णांक wmi_send(काष्ठा wil6210_priv *wil, u16 cmdid, u8 mid, व्योम *buf, u16 len)
अणु
	पूर्णांक rc;

	mutex_lock(&wil->wmi_mutex);
	rc = __wmi_send(wil, cmdid, mid, buf, len);
	mutex_unlock(&wil->wmi_mutex);

	वापस rc;
पूर्ण

/*=== Event handlers ===*/
अटल व्योम wmi_evt_पढ़ोy(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	काष्ठा wmi_पढ़ोy_event *evt = d;
	u8 fw_max_assoc_sta;

	wil_info(wil, "FW ver. %s(SW %d); MAC %pM; %d MID's\n",
		 wil->fw_version, le32_to_cpu(evt->sw_version),
		 evt->mac, evt->numof_additional_mids);
	अगर (evt->numof_additional_mids + 1 < wil->max_vअगरs) अणु
		wil_err(wil, "FW does not support enough MIDs (need %d)",
			wil->max_vअगरs - 1);
		वापस; /* FW load will fail after समयout */
	पूर्ण
	/* ignore MAC address, we alपढ़ोy have it from the boot loader */
	strlcpy(wiphy->fw_version, wil->fw_version, माप(wiphy->fw_version));

	अगर (len > दुरत्व(काष्ठा wmi_पढ़ोy_event, rfc_पढ़ो_calib_result)) अणु
		wil_dbg_wmi(wil, "rfc calibration result %d\n",
			    evt->rfc_पढ़ो_calib_result);
		wil->fw_calib_result = evt->rfc_पढ़ो_calib_result;
	पूर्ण

	fw_max_assoc_sta = WIL6210_RX_DESC_MAX_CID;
	अगर (len > दुरत्व(काष्ठा wmi_पढ़ोy_event, max_assoc_sta) &&
	    evt->max_assoc_sta > 0) अणु
		fw_max_assoc_sta = evt->max_assoc_sta;
		wil_dbg_wmi(wil, "fw reported max assoc sta %d\n",
			    fw_max_assoc_sta);

		अगर (fw_max_assoc_sta > WIL6210_MAX_CID) अणु
			wil_dbg_wmi(wil,
				    "fw max assoc sta %d exceeds max driver supported %d\n",
				    fw_max_assoc_sta, WIL6210_MAX_CID);
			fw_max_assoc_sta = WIL6210_MAX_CID;
		पूर्ण
	पूर्ण

	wil->max_assoc_sta = min_t(uपूर्णांक, max_assoc_sta, fw_max_assoc_sta);
	wil_dbg_wmi(wil, "setting max assoc sta to %d\n", wil->max_assoc_sta);

	wil_set_recovery_state(wil, fw_recovery_idle);
	set_bit(wil_status_fwपढ़ोy, wil->status);
	/* let the reset sequence जारी */
	complete(&wil->wmi_पढ़ोy);
पूर्ण

अटल व्योम wmi_evt_rx_mgmt(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_rx_mgmt_packet_event *data = d;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	काष्ठा ieee80211_mgmt *rx_mgmt_frame =
			(काष्ठा ieee80211_mgmt *)data->payload;
	पूर्णांक flen = len - दुरत्व(काष्ठा wmi_rx_mgmt_packet_event, payload);
	पूर्णांक ch_no;
	u32 freq;
	काष्ठा ieee80211_channel *channel;
	s32 संकेत;
	__le16 fc;
	u32 d_len;
	u16 d_status;

	अगर (flen < 0) अणु
		wil_err(wil, "MGMT Rx: short event, len %d\n", len);
		वापस;
	पूर्ण

	d_len = le32_to_cpu(data->info.len);
	अगर (d_len != flen) अणु
		wil_err(wil,
			"MGMT Rx: length mismatch, d_len %d should be %d\n",
			d_len, flen);
		वापस;
	पूर्ण

	ch_no = data->info.channel + 1;
	freq = ieee80211_channel_to_frequency(ch_no, NL80211_BAND_60GHZ);
	channel = ieee80211_get_channel(wiphy, freq);
	अगर (test_bit(WMI_FW_CAPABILITY_RSSI_REPORTING, wil->fw_capabilities))
		संकेत = 100 * data->info.rssi;
	अन्यथा
		संकेत = data->info.sqi;
	d_status = le16_to_cpu(data->info.status);
	fc = rx_mgmt_frame->frame_control;

	wil_dbg_wmi(wil, "MGMT Rx: channel %d MCS %s RSSI %d SQI %d%%\n",
		    data->info.channel, WIL_EXTENDED_MCS_CHECK(data->info.mcs),
		    data->info.rssi, data->info.sqi);
	wil_dbg_wmi(wil, "status 0x%04x len %d fc 0x%04x\n", d_status, d_len,
		    le16_to_cpu(fc));
	wil_dbg_wmi(wil, "qid %d mid %d cid %d\n",
		    data->info.qid, data->info.mid, data->info.cid);
	wil_hex_dump_wmi("MGMT Rx ", DUMP_PREFIX_OFFSET, 16, 1, rx_mgmt_frame,
			 d_len, true);

	अगर (!channel) अणु
		wil_err(wil, "Frame on unsupported channel\n");
		वापस;
	पूर्ण

	अगर (ieee80211_is_beacon(fc) || ieee80211_is_probe_resp(fc)) अणु
		काष्ठा cfg80211_bss *bss;
		काष्ठा cfg80211_inक्रमm_bss bss_data = अणु
			.chan = channel,
			.scan_width = NL80211_BSS_CHAN_WIDTH_20,
			.संकेत = संकेत,
			.bootसमय_ns = kसमय_प्रकारo_ns(kसमय_get_bootसमय()),
		पूर्ण;
		u64 tsf = le64_to_cpu(rx_mgmt_frame->u.beacon.बारtamp);
		u16 cap = le16_to_cpu(rx_mgmt_frame->u.beacon.capab_info);
		u16 bi = le16_to_cpu(rx_mgmt_frame->u.beacon.beacon_पूर्णांक);
		स्थिर u8 *ie_buf = rx_mgmt_frame->u.beacon.variable;
		माप_प्रकार ie_len = d_len - दुरत्व(काष्ठा ieee80211_mgmt,
						 u.beacon.variable);
		wil_dbg_wmi(wil, "Capability info : 0x%04x\n", cap);
		wil_dbg_wmi(wil, "TSF : 0x%016llx\n", tsf);
		wil_dbg_wmi(wil, "Beacon interval : %d\n", bi);
		wil_hex_dump_wmi("IE ", DUMP_PREFIX_OFFSET, 16, 1, ie_buf,
				 ie_len, true);

		wil_dbg_wmi(wil, "Capability info : 0x%04x\n", cap);

		bss = cfg80211_inक्रमm_bss_frame_data(wiphy, &bss_data,
						     rx_mgmt_frame,
						     d_len, GFP_KERNEL);
		अगर (bss) अणु
			wil_dbg_wmi(wil, "Added BSS %pM\n",
				    rx_mgmt_frame->bssid);
			cfg80211_put_bss(wiphy, bss);
		पूर्ण अन्यथा अणु
			wil_err(wil, "cfg80211_inform_bss_frame() failed\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&wil->vअगर_mutex);
		cfg80211_rx_mgmt(vअगर_to_radio_wdev(wil, vअगर), freq, संकेत,
				 (व्योम *)rx_mgmt_frame, d_len, 0);
		mutex_unlock(&wil->vअगर_mutex);
	पूर्ण
पूर्ण

अटल व्योम wmi_evt_tx_mgmt(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wmi_tx_mgmt_packet_event *data = d;
	काष्ठा ieee80211_mgmt *mgmt_frame =
			(काष्ठा ieee80211_mgmt *)data->payload;
	पूर्णांक flen = len - दुरत्व(काष्ठा wmi_tx_mgmt_packet_event, payload);

	wil_hex_dump_wmi("MGMT Tx ", DUMP_PREFIX_OFFSET, 16, 1, mgmt_frame,
			 flen, true);
पूर्ण

अटल व्योम wmi_evt_scan_complete(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id,
				  व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	mutex_lock(&wil->vअगर_mutex);
	अगर (vअगर->scan_request) अणु
		काष्ठा wmi_scan_complete_event *data = d;
		पूर्णांक status = le32_to_cpu(data->status);
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = ((status != WMI_SCAN_SUCCESS) &&
				(status != WMI_SCAN_ABORT_REJECTED)),
		पूर्ण;

		wil_dbg_wmi(wil, "SCAN_COMPLETE(0x%08x)\n", status);
		wil_dbg_misc(wil, "Complete scan_request 0x%p aborted %d\n",
			     vअगर->scan_request, info.पातed);
		del_समयr_sync(&vअगर->scan_समयr);
		cfg80211_scan_करोne(vअगर->scan_request, &info);
		अगर (vअगर->mid == 0)
			wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
		vअगर->scan_request = शून्य;
		wake_up_पूर्णांकerruptible(&wil->wq);
		अगर (vअगर->p2p.pending_listen_wdev) अणु
			wil_dbg_misc(wil, "Scheduling delayed listen\n");
			schedule_work(&vअगर->p2p.delayed_listen_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		wil_err(wil, "SCAN_COMPLETE while not scanning\n");
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);
पूर्ण

अटल व्योम wmi_evt_connect(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	काष्ठा wmi_connect_event *evt = d;
	पूर्णांक ch; /* channel number */
	काष्ठा station_info *sinfo;
	u8 *assoc_req_ie, *assoc_resp_ie;
	माप_प्रकार assoc_req_ielen, assoc_resp_ielen;
	/* capinfo(u16) + listen_पूर्णांकerval(u16) + IEs */
	स्थिर माप_प्रकार assoc_req_ie_offset = माप(u16) * 2;
	/* capinfo(u16) + status_code(u16) + associd(u16) + IEs */
	स्थिर माप_प्रकार assoc_resp_ie_offset = माप(u16) * 3;
	पूर्णांक rc;

	अगर (len < माप(*evt)) अणु
		wil_err(wil, "Connect event too short : %d bytes\n", len);
		वापस;
	पूर्ण
	अगर (len != माप(*evt) + evt->beacon_ie_len + evt->assoc_req_len +
		   evt->assoc_resp_len) अणु
		wil_err(wil,
			"Connect event corrupted : %d != %d + %d + %d + %d\n",
			len, (पूर्णांक)माप(*evt), evt->beacon_ie_len,
			evt->assoc_req_len, evt->assoc_resp_len);
		वापस;
	पूर्ण
	अगर (evt->cid >= wil->max_assoc_sta) अणु
		wil_err(wil, "Connect CID invalid : %d\n", evt->cid);
		वापस;
	पूर्ण

	ch = evt->channel + 1;
	wil_info(wil, "Connect %pM channel [%d] cid %d aid %d\n",
		 evt->bssid, ch, evt->cid, evt->aid);
	wil_hex_dump_wmi("connect AI : ", DUMP_PREFIX_OFFSET, 16, 1,
			 evt->assoc_info, len - माप(*evt), true);

	/* figure out IE's */
	assoc_req_ie = &evt->assoc_info[evt->beacon_ie_len +
					assoc_req_ie_offset];
	assoc_req_ielen = evt->assoc_req_len - assoc_req_ie_offset;
	अगर (evt->assoc_req_len <= assoc_req_ie_offset) अणु
		assoc_req_ie = शून्य;
		assoc_req_ielen = 0;
	पूर्ण

	assoc_resp_ie = &evt->assoc_info[evt->beacon_ie_len +
					 evt->assoc_req_len +
					 assoc_resp_ie_offset];
	assoc_resp_ielen = evt->assoc_resp_len - assoc_resp_ie_offset;
	अगर (evt->assoc_resp_len <= assoc_resp_ie_offset) अणु
		assoc_resp_ie = शून्य;
		assoc_resp_ielen = 0;
	पूर्ण

	अगर (test_bit(wil_status_resetting, wil->status) ||
	    !test_bit(wil_status_fwपढ़ोy, wil->status)) अणु
		wil_err(wil, "status_resetting, cancel connect event, CID %d\n",
			evt->cid);
		/* no need क्रम cleanup, wil_reset will करो that */
		वापस;
	पूर्ण

	mutex_lock(&wil->mutex);

	अगर ((wdev->अगरtype == NL80211_IFTYPE_STATION) ||
	    (wdev->अगरtype == NL80211_IFTYPE_P2P_CLIENT)) अणु
		अगर (!test_bit(wil_vअगर_fwconnecting, vअगर->status)) अणु
			wil_err(wil, "Not in connecting state\n");
			mutex_unlock(&wil->mutex);
			वापस;
		पूर्ण
		del_समयr_sync(&vअगर->connect_समयr);
	पूर्ण अन्यथा अगर ((wdev->अगरtype == NL80211_IFTYPE_AP) ||
		   (wdev->अगरtype == NL80211_IFTYPE_P2P_GO)) अणु
		अगर (wil->sta[evt->cid].status != wil_sta_unused) अणु
			wil_err(wil, "AP: Invalid status %d for CID %d\n",
				wil->sta[evt->cid].status, evt->cid);
			mutex_unlock(&wil->mutex);
			वापस;
		पूर्ण
	पूर्ण

	ether_addr_copy(wil->sta[evt->cid].addr, evt->bssid);
	wil->sta[evt->cid].mid = vअगर->mid;
	wil->sta[evt->cid].status = wil_sta_conn_pending;

	rc = wil_ring_init_tx(vअगर, evt->cid);
	अगर (rc) अणु
		wil_err(wil, "config tx vring failed for CID %d, rc (%d)\n",
			evt->cid, rc);
		wmi_disconnect_sta(vअगर, wil->sta[evt->cid].addr,
				   WLAN_REASON_UNSPECIFIED, false);
	पूर्ण अन्यथा अणु
		wil_info(wil, "successful connection to CID %d\n", evt->cid);
	पूर्ण

	अगर ((wdev->अगरtype == NL80211_IFTYPE_STATION) ||
	    (wdev->अगरtype == NL80211_IFTYPE_P2P_CLIENT)) अणु
		अगर (rc) अणु
			netअगर_carrier_off(ndev);
			wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);
			wil_err(wil, "cfg80211_connect_result with failure\n");
			cfg80211_connect_result(ndev, evt->bssid, शून्य, 0,
						शून्य, 0,
						WLAN_STATUS_UNSPECIFIED_FAILURE,
						GFP_KERNEL);
			जाओ out;
		पूर्ण अन्यथा अणु
			काष्ठा wiphy *wiphy = wil_to_wiphy(wil);

			cfg80211_ref_bss(wiphy, vअगर->bss);
			cfg80211_connect_bss(ndev, evt->bssid, vअगर->bss,
					     assoc_req_ie, assoc_req_ielen,
					     assoc_resp_ie, assoc_resp_ielen,
					     WLAN_STATUS_SUCCESS, GFP_KERNEL,
					     NL80211_TIMEOUT_UNSPECIFIED);
		पूर्ण
		vअगर->bss = शून्य;
	पूर्ण अन्यथा अगर ((wdev->अगरtype == NL80211_IFTYPE_AP) ||
		   (wdev->अगरtype == NL80211_IFTYPE_P2P_GO)) अणु

		अगर (rc) अणु
			अगर (disable_ap_sme)
				/* notअगरy new_sta has failed */
				cfg80211_del_sta(ndev, evt->bssid, GFP_KERNEL);
			जाओ out;
		पूर्ण

		sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
		अगर (!sinfo) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		sinfo->generation = wil->sinfo_gen++;

		अगर (assoc_req_ie) अणु
			sinfo->assoc_req_ies = assoc_req_ie;
			sinfo->assoc_req_ies_len = assoc_req_ielen;
		पूर्ण

		cfg80211_new_sta(ndev, evt->bssid, sinfo, GFP_KERNEL);

		kमुक्त(sinfo);
	पूर्ण अन्यथा अणु
		wil_err(wil, "unhandled iftype %d for CID %d\n", wdev->अगरtype,
			evt->cid);
		जाओ out;
	पूर्ण

	wil->sta[evt->cid].status = wil_sta_connected;
	wil->sta[evt->cid].aid = evt->aid;
	अगर (!test_and_set_bit(wil_vअगर_fwconnected, vअगर->status))
		atomic_inc(&wil->connected_vअगरs);
	wil_update_net_queues_bh(wil, vअगर, शून्य, false);

out:
	अगर (rc) अणु
		wil->sta[evt->cid].status = wil_sta_unused;
		wil->sta[evt->cid].mid = U8_MAX;
	पूर्ण
	clear_bit(wil_vअगर_fwconnecting, vअगर->status);
	mutex_unlock(&wil->mutex);
पूर्ण

अटल व्योम wmi_evt_disconnect(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id,
			       व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_disconnect_event *evt = d;
	u16 reason_code = le16_to_cpu(evt->protocol_reason_status);

	wil_info(wil, "Disconnect %pM reason [proto %d wmi %d]\n",
		 evt->bssid, reason_code, evt->disconnect_reason);

	wil->sinfo_gen++;

	अगर (test_bit(wil_status_resetting, wil->status) ||
	    !test_bit(wil_status_fwपढ़ोy, wil->status)) अणु
		wil_err(wil, "status_resetting, cancel disconnect event\n");
		/* no need क्रम cleanup, wil_reset will करो that */
		वापस;
	पूर्ण

	mutex_lock(&wil->mutex);
	wil6210_disconnect_complete(vअगर, evt->bssid, reason_code);
	अगर (disable_ap_sme) अणु
		काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
		काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);

		/* disconnect event in disable_ap_sme mode means link loss */
		चयन (wdev->अगरtype) अणु
		/* AP-like पूर्णांकerface */
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_P2P_GO:
			/* notअगरy hostapd about link loss */
			cfg80211_cqm_pktloss_notअगरy(ndev, evt->bssid, 0,
						    GFP_KERNEL);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&wil->mutex);
पूर्ण

/*
 * Firmware reports EAPOL frame using WME event.
 * Reस्थिरruct Ethernet frame and deliver it via normal Rx
 */
अटल व्योम wmi_evt_eapol_rx(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wmi_eapol_rx_event *evt = d;
	u16 eapol_len = le16_to_cpu(evt->eapol_len);
	पूर्णांक sz = eapol_len + ETH_HLEN;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *eth;
	पूर्णांक cid;
	काष्ठा wil_net_stats *stats = शून्य;

	wil_dbg_wmi(wil, "EAPOL len %d from %pM MID %d\n", eapol_len,
		    evt->src_mac, vअगर->mid);

	cid = wil_find_cid(wil, vअगर->mid, evt->src_mac);
	अगर (cid >= 0)
		stats = &wil->sta[cid].stats;

	अगर (eapol_len > 196) अणु /* TODO: revisit size limit */
		wil_err(wil, "EAPOL too large\n");
		वापस;
	पूर्ण

	skb = alloc_skb(sz, GFP_KERNEL);
	अगर (!skb) अणु
		wil_err(wil, "Failed to allocate skb\n");
		वापस;
	पूर्ण

	eth = skb_put(skb, ETH_HLEN);
	ether_addr_copy(eth->h_dest, ndev->dev_addr);
	ether_addr_copy(eth->h_source, evt->src_mac);
	eth->h_proto = cpu_to_be16(ETH_P_PAE);
	skb_put_data(skb, evt->eapol, eapol_len);
	skb->protocol = eth_type_trans(skb, ndev);
	अगर (likely(netअगर_rx_ni(skb) == NET_RX_SUCCESS)) अणु
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += sz;
		अगर (stats) अणु
			stats->rx_packets++;
			stats->rx_bytes += sz;
		पूर्ण
	पूर्ण अन्यथा अणु
		ndev->stats.rx_dropped++;
		अगर (stats)
			stats->rx_dropped++;
	पूर्ण
पूर्ण

अटल व्योम wmi_evt_ring_en(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_ring_en_event *evt = d;
	u8 vri = evt->ring_index;
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	काष्ठा wil_sta_info *sta;
	u8 cid;
	काष्ठा key_params params;

	wil_dbg_wmi(wil, "Enable vring %d MID %d\n", vri, vअगर->mid);

	अगर (vri >= ARRAY_SIZE(wil->ring_tx)) अणु
		wil_err(wil, "Enable for invalid vring %d\n", vri);
		वापस;
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP || !disable_ap_sme ||
	    test_bit(wil_vअगर_ft_roam, vअगर->status))
		/* in AP mode with disable_ap_sme that is not FT,
		 * this is करोne by wil_cfg80211_change_station()
		 */
		wil->ring_tx_data[vri].करोt1x_खोलो = true;
	अगर (vri == vअगर->bcast_ring) /* no BA क्रम bcast */
		वापस;

	cid = wil->ring2cid_tid[vri][0];
	अगर (!wil_cid_valid(wil, cid)) अणु
		wil_err(wil, "invalid cid %d for vring %d\n", cid, vri);
		वापस;
	पूर्ण

	/* In FT mode we get key but not store it as it is received
	 * beक्रमe WMI_CONNECT_EVENT received from FW.
	 * wil_set_crypto_rx is called here to reset the security PN
	 */
	sta = &wil->sta[cid];
	अगर (test_bit(wil_vअगर_ft_roam, vअगर->status)) अणु
		स_रखो(&params, 0, माप(params));
		wil_set_crypto_rx(0, WMI_KEY_USE_PAIRWISE, sta, &params);
		अगर (wdev->अगरtype != NL80211_IFTYPE_AP)
			clear_bit(wil_vअगर_ft_roam, vअगर->status);
	पूर्ण

	अगर (agg_wsize >= 0)
		wil_addba_tx_request(wil, vri, agg_wsize);
पूर्ण

अटल व्योम wmi_evt_ba_status(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id,
			      व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_ba_status_event *evt = d;
	काष्ठा wil_ring_tx_data *txdata;

	wil_dbg_wmi(wil, "BACK[%d] %s {%d} timeout %d AMSDU%s\n",
		    evt->ringid,
		    evt->status == WMI_BA_AGREED ? "OK" : "N/A",
		    evt->agg_wsize, __le16_to_cpu(evt->ba_समयout),
		    evt->amsdu ? "+" : "-");

	अगर (evt->ringid >= WIL6210_MAX_TX_RINGS) अणु
		wil_err(wil, "invalid ring id %d\n", evt->ringid);
		वापस;
	पूर्ण

	अगर (evt->status != WMI_BA_AGREED) अणु
		evt->ba_समयout = 0;
		evt->agg_wsize = 0;
		evt->amsdu = 0;
	पूर्ण

	txdata = &wil->ring_tx_data[evt->ringid];

	txdata->agg_समयout = le16_to_cpu(evt->ba_समयout);
	txdata->agg_wsize = evt->agg_wsize;
	txdata->agg_amsdu = evt->amsdu;
	txdata->addba_in_progress = false;
पूर्ण

अटल व्योम wmi_evt_addba_rx_req(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id,
				 व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	u8 cid, tid;
	काष्ठा wmi_rcp_addba_req_event *evt = d;

	अगर (evt->cidxtid != CIDXTID_EXTENDED_CID_TID) अणु
		parse_cidxtid(evt->cidxtid, &cid, &tid);
	पूर्ण अन्यथा अणु
		cid = evt->cid;
		tid = evt->tid;
	पूर्ण
	wil_addba_rx_request(wil, vअगर->mid, cid, tid, evt->dialog_token,
			     evt->ba_param_set, evt->ba_समयout,
			     evt->ba_seq_ctrl);
पूर्ण

अटल व्योम wmi_evt_delba(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
__acquires(&sta->tid_rx_lock) __releases(&sta->tid_rx_lock)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_delba_event *evt = d;
	u8 cid, tid;
	u16 reason = __le16_to_cpu(evt->reason);
	काष्ठा wil_sta_info *sta;
	काष्ठा wil_tid_ampdu_rx *r;

	might_sleep();

	अगर (evt->cidxtid != CIDXTID_EXTENDED_CID_TID) अणु
		parse_cidxtid(evt->cidxtid, &cid, &tid);
	पूर्ण अन्यथा अणु
		cid = evt->cid;
		tid = evt->tid;
	पूर्ण

	अगर (!wil_cid_valid(wil, cid)) अणु
		wil_err(wil, "DELBA: Invalid CID %d\n", cid);
		वापस;
	पूर्ण

	wil_dbg_wmi(wil, "DELBA MID %d CID %d TID %d from %s reason %d\n",
		    vअगर->mid, cid, tid,
		    evt->from_initiator ? "originator" : "recipient",
		    reason);
	अगर (!evt->from_initiator) अणु
		पूर्णांक i;
		/* find Tx vring it beदीर्घs to */
		क्रम (i = 0; i < ARRAY_SIZE(wil->ring2cid_tid); i++) अणु
			अगर (wil->ring2cid_tid[i][0] == cid &&
			    wil->ring2cid_tid[i][1] == tid) अणु
				काष्ठा wil_ring_tx_data *txdata =
					&wil->ring_tx_data[i];

				wil_dbg_wmi(wil, "DELBA Tx vring %d\n", i);
				txdata->agg_समयout = 0;
				txdata->agg_wsize = 0;
				txdata->addba_in_progress = false;

				अवरोध; /* max. 1 matching ring */
			पूर्ण
		पूर्ण
		अगर (i >= ARRAY_SIZE(wil->ring2cid_tid))
			wil_err(wil, "DELBA: unable to find Tx vring\n");
		वापस;
	पूर्ण

	sta = &wil->sta[cid];

	spin_lock_bh(&sta->tid_rx_lock);

	r = sta->tid_rx[tid];
	sta->tid_rx[tid] = शून्य;
	wil_tid_ampdu_rx_मुक्त(wil, r);

	spin_unlock_bh(&sta->tid_rx_lock);
पूर्ण

अटल व्योम
wmi_evt_sched_scan_result(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_sched_scan_result_event *data = d;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	काष्ठा ieee80211_mgmt *rx_mgmt_frame =
		(काष्ठा ieee80211_mgmt *)data->payload;
	पूर्णांक flen = len - दुरत्व(काष्ठा wmi_sched_scan_result_event, payload);
	पूर्णांक ch_no;
	u32 freq;
	काष्ठा ieee80211_channel *channel;
	s32 संकेत;
	__le16 fc;
	u32 d_len;
	काष्ठा cfg80211_bss *bss;
	काष्ठा cfg80211_inक्रमm_bss bss_data = अणु
		.scan_width = NL80211_BSS_CHAN_WIDTH_20,
		.bootसमय_ns = kसमय_प्रकारo_ns(kसमय_get_bootसमय()),
	पूर्ण;

	अगर (flen < 0) अणु
		wil_err(wil, "sched scan result event too short, len %d\n",
			len);
		वापस;
	पूर्ण

	d_len = le32_to_cpu(data->info.len);
	अगर (d_len != flen) अणु
		wil_err(wil,
			"sched scan result length mismatch, d_len %d should be %d\n",
			d_len, flen);
		वापस;
	पूर्ण

	fc = rx_mgmt_frame->frame_control;
	अगर (!ieee80211_is_probe_resp(fc)) अणु
		wil_err(wil, "sched scan result invalid frame, fc 0x%04x\n",
			fc);
		वापस;
	पूर्ण

	ch_no = data->info.channel + 1;
	freq = ieee80211_channel_to_frequency(ch_no, NL80211_BAND_60GHZ);
	channel = ieee80211_get_channel(wiphy, freq);
	अगर (test_bit(WMI_FW_CAPABILITY_RSSI_REPORTING, wil->fw_capabilities))
		संकेत = 100 * data->info.rssi;
	अन्यथा
		संकेत = data->info.sqi;

	wil_dbg_wmi(wil, "sched scan result: channel %d MCS %s RSSI %d\n",
		    data->info.channel, WIL_EXTENDED_MCS_CHECK(data->info.mcs),
		    data->info.rssi);
	wil_dbg_wmi(wil, "len %d qid %d mid %d cid %d\n",
		    d_len, data->info.qid, data->info.mid, data->info.cid);
	wil_hex_dump_wmi("PROBE ", DUMP_PREFIX_OFFSET, 16, 1, rx_mgmt_frame,
			 d_len, true);

	अगर (!channel) अणु
		wil_err(wil, "Frame on unsupported channel\n");
		वापस;
	पूर्ण

	bss_data.संकेत = संकेत;
	bss_data.chan = channel;
	bss = cfg80211_inक्रमm_bss_frame_data(wiphy, &bss_data, rx_mgmt_frame,
					     d_len, GFP_KERNEL);
	अगर (bss) अणु
		wil_dbg_wmi(wil, "Added BSS %pM\n", rx_mgmt_frame->bssid);
		cfg80211_put_bss(wiphy, bss);
	पूर्ण अन्यथा अणु
		wil_err(wil, "cfg80211_inform_bss_frame() failed\n");
	पूर्ण

	cfg80211_sched_scan_results(wiphy, 0);
पूर्ण

अटल व्योम wil_link_stats_store_basic(काष्ठा wil6210_vअगर *vअगर,
				       काष्ठा wmi_link_stats_basic *basic)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	u8 cid = basic->cid;
	काष्ठा wil_sta_info *sta;

	अगर (cid >= wil->max_assoc_sta) अणु
		wil_err(wil, "invalid cid %d\n", cid);
		वापस;
	पूर्ण

	sta = &wil->sta[cid];
	sta->fw_stats_basic = *basic;
पूर्ण

अटल व्योम wil_link_stats_store_global(काष्ठा wil6210_vअगर *vअगर,
					काष्ठा wmi_link_stats_global *global)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil->fw_stats_global.stats = *global;
पूर्ण

अटल व्योम wmi_link_stats_parse(काष्ठा wil6210_vअगर *vअगर, u64 tsf,
				 bool has_next, व्योम *payload,
				 माप_प्रकार payload_size)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	माप_प्रकार hdr_size = माप(काष्ठा wmi_link_stats_record);
	माप_प्रकार stats_size, record_size, expected_size;
	काष्ठा wmi_link_stats_record *hdr;

	अगर (payload_size < hdr_size) अणु
		wil_err(wil, "link stats wrong event size %zu\n", payload_size);
		वापस;
	पूर्ण

	जबतक (payload_size >= hdr_size) अणु
		hdr = payload;
		stats_size = le16_to_cpu(hdr->record_size);
		record_size = hdr_size + stats_size;

		अगर (payload_size < record_size) अणु
			wil_err(wil, "link stats payload ended unexpectedly, size %zu < %zu\n",
				payload_size, record_size);
			वापस;
		पूर्ण

		चयन (hdr->record_type_id) अणु
		हाल WMI_LINK_STATS_TYPE_BASIC:
			expected_size = माप(काष्ठा wmi_link_stats_basic);
			अगर (stats_size < expected_size) अणु
				wil_err(wil, "link stats invalid basic record size %zu < %zu\n",
					stats_size, expected_size);
				वापस;
			पूर्ण
			अगर (vअगर->fw_stats_पढ़ोy) अणु
				/* clean old statistics */
				vअगर->fw_stats_tsf = 0;
				vअगर->fw_stats_पढ़ोy = false;
			पूर्ण

			wil_link_stats_store_basic(vअगर, payload + hdr_size);

			अगर (!has_next) अणु
				vअगर->fw_stats_tsf = tsf;
				vअगर->fw_stats_पढ़ोy = true;
			पूर्ण

			अवरोध;
		हाल WMI_LINK_STATS_TYPE_GLOBAL:
			expected_size = माप(काष्ठा wmi_link_stats_global);
			अगर (stats_size < माप(काष्ठा wmi_link_stats_global)) अणु
				wil_err(wil, "link stats invalid global record size %zu < %zu\n",
					stats_size, expected_size);
				वापस;
			पूर्ण

			अगर (wil->fw_stats_global.पढ़ोy) अणु
				/* clean old statistics */
				wil->fw_stats_global.tsf = 0;
				wil->fw_stats_global.पढ़ोy = false;
			पूर्ण

			wil_link_stats_store_global(vअगर, payload + hdr_size);

			अगर (!has_next) अणु
				wil->fw_stats_global.tsf = tsf;
				wil->fw_stats_global.पढ़ोy = true;
			पूर्ण

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* skip to next record */
		payload += record_size;
		payload_size -= record_size;
	पूर्ण
पूर्ण

अटल व्योम
wmi_evt_link_stats(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_link_stats_event *evt = d;
	माप_प्रकार payload_size;

	अगर (len < दुरत्व(काष्ठा wmi_link_stats_event, payload)) अणु
		wil_err(wil, "stats event way too short %d\n", len);
		वापस;
	पूर्ण
	payload_size = le16_to_cpu(evt->payload_size);
	अगर (len < माप(काष्ठा wmi_link_stats_event) + payload_size) अणु
		wil_err(wil, "stats event too short %d\n", len);
		वापस;
	पूर्ण

	wmi_link_stats_parse(vअगर, le64_to_cpu(evt->tsf), evt->has_next,
			     evt->payload, payload_size);
पूर्ण

/* find cid and ringid क्रम the station vअगर
 *
 * वापस error, अगर other पूर्णांकerfaces are used or ring was not found
 */
अटल पूर्णांक wil_find_cid_ringid_sta(काष्ठा wil6210_priv *wil,
				   काष्ठा wil6210_vअगर *vअगर,
				   पूर्णांक *cid,
				   पूर्णांक *ringid)
अणु
	काष्ठा wil_ring *ring;
	काष्ठा wil_ring_tx_data *txdata;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);
	पूर्णांक i;
	u8 lcid;

	अगर (!(vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION ||
	      vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_CLIENT)) अणु
		wil_err(wil, "invalid interface type %d\n", vअगर->wdev.अगरtype);
		वापस -EINVAL;
	पूर्ण

	/* In the STA mode, it is expected to have only one ring
	 * क्रम the AP we are connected to.
	 * find it and वापस the cid associated with it.
	 */
	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		ring = &wil->ring_tx[i];
		txdata = &wil->ring_tx_data[i];
		अगर (!ring->va || !txdata->enabled || txdata->mid != vअगर->mid)
			जारी;

		lcid = wil->ring2cid_tid[i][0];
		अगर (lcid >= wil->max_assoc_sta) /* skip BCAST */
			जारी;

		wil_dbg_wmi(wil, "find sta -> ringid %d cid %d\n", i, lcid);
		*cid = lcid;
		*ringid = i;
		वापस 0;
	पूर्ण

	wil_dbg_wmi(wil, "find sta cid while no rings active?\n");

	वापस -ENOENT;
पूर्ण

अटल व्योम
wmi_evt_auth_status(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wmi_ft_auth_status_event *data = d;
	पूर्णांक ie_len = len - दुरत्व(काष्ठा wmi_ft_auth_status_event, ie_info);
	पूर्णांक rc, cid = 0, ringid = 0;
	काष्ठा cfg80211_ft_event_params ft;
	u16 d_len;
	/* auth_alg(u16) + auth_transaction(u16) + status_code(u16) */
	स्थिर माप_प्रकार auth_ie_offset = माप(u16) * 3;
	काष्ठा auth_no_hdr *auth = (काष्ठा auth_no_hdr *)data->ie_info;

	/* check the status */
	अगर (ie_len >= 0 && data->status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "FT: auth failed. status %d\n", data->status);
		जाओ fail;
	पूर्ण

	अगर (ie_len < auth_ie_offset) अणु
		wil_err(wil, "FT: auth event too short, len %d\n", len);
		जाओ fail;
	पूर्ण

	d_len = le16_to_cpu(data->ie_len);
	अगर (d_len != ie_len) अणु
		wil_err(wil,
			"FT: auth ie length mismatch, d_len %d should be %d\n",
			d_len, ie_len);
		जाओ fail;
	पूर्ण

	अगर (!test_bit(wil_vअगर_ft_roam, wil->status)) अणु
		wil_err(wil, "FT: Not in roaming state\n");
		जाओ fail;
	पूर्ण

	अगर (le16_to_cpu(auth->auth_transaction) != 2) अणु
		wil_err(wil, "FT: auth error. auth_transaction %d\n",
			le16_to_cpu(auth->auth_transaction));
		जाओ fail;
	पूर्ण

	अगर (le16_to_cpu(auth->auth_alg) != WLAN_AUTH_FT) अणु
		wil_err(wil, "FT: auth error. auth_alg %d\n",
			le16_to_cpu(auth->auth_alg));
		जाओ fail;
	पूर्ण

	wil_dbg_wmi(wil, "FT: Auth to %pM successfully\n", data->mac_addr);
	wil_hex_dump_wmi("FT Auth ies : ", DUMP_PREFIX_OFFSET, 16, 1,
			 data->ie_info, d_len, true);

	/* find cid and ringid */
	rc = wil_find_cid_ringid_sta(wil, vअगर, &cid, &ringid);
	अगर (rc) अणु
		wil_err(wil, "No valid cid found\n");
		जाओ fail;
	पूर्ण

	अगर (vअगर->privacy) अणु
		/* For secure assoc, हटाओ old keys */
		rc = wmi_del_cipher_key(vअगर, 0, wil->sta[cid].addr,
					WMI_KEY_USE_PAIRWISE);
		अगर (rc) अणु
			wil_err(wil, "WMI_DELETE_CIPHER_KEY_CMD(PTK) failed\n");
			जाओ fail;
		पूर्ण
		rc = wmi_del_cipher_key(vअगर, 0, wil->sta[cid].addr,
					WMI_KEY_USE_RX_GROUP);
		अगर (rc) अणु
			wil_err(wil, "WMI_DELETE_CIPHER_KEY_CMD(GTK) failed\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	स_रखो(&ft, 0, माप(ft));
	ft.ies = data->ie_info + auth_ie_offset;
	ft.ies_len = d_len - auth_ie_offset;
	ft.target_ap = data->mac_addr;
	cfg80211_ft_event(ndev, &ft);

	वापस;

fail:
	wil6210_disconnect(vअगर, शून्य, WLAN_REASON_PREV_AUTH_NOT_VALID);
पूर्ण

अटल व्योम
wmi_evt_reassoc_status(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	काष्ठा wmi_ft_reassoc_status_event *data = d;
	पूर्णांक ies_len = len - दुरत्व(काष्ठा wmi_ft_reassoc_status_event,
				     ie_info);
	पूर्णांक rc = -ENOENT, cid = 0, ringid = 0;
	पूर्णांक ch; /* channel number (primary) */
	माप_प्रकार assoc_req_ie_len = 0, assoc_resp_ie_len = 0;
	u8 *assoc_req_ie = शून्य, *assoc_resp_ie = शून्य;
	/* capinfo(u16) + listen_पूर्णांकerval(u16) + current_ap mac addr + IEs */
	स्थिर माप_प्रकार assoc_req_ie_offset = माप(u16) * 2 + ETH_ALEN;
	/* capinfo(u16) + status_code(u16) + associd(u16) + IEs */
	स्थिर माप_प्रकार assoc_resp_ie_offset = माप(u16) * 3;
	u16 d_len;
	पूर्णांक freq;
	काष्ठा cfg80211_roam_info info;

	अगर (ies_len < 0) अणु
		wil_err(wil, "ft reassoc event too short, len %d\n", len);
		जाओ fail;
	पूर्ण

	wil_dbg_wmi(wil, "Reasoc Status event: status=%d, aid=%d",
		    data->status, data->aid);
	wil_dbg_wmi(wil, "    mac_addr=%pM, beacon_ie_len=%d",
		    data->mac_addr, data->beacon_ie_len);
	wil_dbg_wmi(wil, "    reassoc_req_ie_len=%d, reassoc_resp_ie_len=%d",
		    le16_to_cpu(data->reassoc_req_ie_len),
		    le16_to_cpu(data->reassoc_resp_ie_len));

	d_len = le16_to_cpu(data->beacon_ie_len) +
		le16_to_cpu(data->reassoc_req_ie_len) +
		le16_to_cpu(data->reassoc_resp_ie_len);
	अगर (d_len != ies_len) अणु
		wil_err(wil,
			"ft reassoc ie length mismatch, d_len %d should be %d\n",
			d_len, ies_len);
		जाओ fail;
	पूर्ण

	/* check the status */
	अगर (data->status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "ft reassoc failed. status %d\n", data->status);
		जाओ fail;
	पूर्ण

	/* find cid and ringid */
	rc = wil_find_cid_ringid_sta(wil, vअगर, &cid, &ringid);
	अगर (rc) अणु
		wil_err(wil, "No valid cid found\n");
		जाओ fail;
	पूर्ण

	ch = data->channel + 1;
	wil_info(wil, "FT: Roam %pM channel [%d] cid %d aid %d\n",
		 data->mac_addr, ch, cid, data->aid);

	wil_hex_dump_wmi("reassoc AI : ", DUMP_PREFIX_OFFSET, 16, 1,
			 data->ie_info, len - माप(*data), true);

	/* figure out IE's */
	अगर (le16_to_cpu(data->reassoc_req_ie_len) > assoc_req_ie_offset) अणु
		assoc_req_ie = &data->ie_info[assoc_req_ie_offset];
		assoc_req_ie_len = le16_to_cpu(data->reassoc_req_ie_len) -
			assoc_req_ie_offset;
	पूर्ण
	अगर (le16_to_cpu(data->reassoc_resp_ie_len) <= assoc_resp_ie_offset) अणु
		wil_err(wil, "FT: reassoc resp ie len is too short, len %d\n",
			le16_to_cpu(data->reassoc_resp_ie_len));
		जाओ fail;
	पूर्ण

	assoc_resp_ie = &data->ie_info[le16_to_cpu(data->reassoc_req_ie_len) +
		assoc_resp_ie_offset];
	assoc_resp_ie_len = le16_to_cpu(data->reassoc_resp_ie_len) -
		assoc_resp_ie_offset;

	अगर (test_bit(wil_status_resetting, wil->status) ||
	    !test_bit(wil_status_fwपढ़ोy, wil->status)) अणु
		wil_err(wil, "FT: status_resetting, cancel reassoc event\n");
		/* no need क्रम cleanup, wil_reset will करो that */
		वापस;
	पूर्ण

	mutex_lock(&wil->mutex);

	/* ring modअगरy to set the ring क्रम the roamed AP settings */
	wil_dbg_wmi(wil,
		    "ft modify tx config for connection CID %d ring %d\n",
		    cid, ringid);

	rc = wil->txrx_ops.tx_ring_modअगरy(vअगर, ringid, cid, 0);
	अगर (rc) अणु
		wil_err(wil, "modify TX for CID %d MID %d ring %d failed (%d)\n",
			cid, vअगर->mid, ringid, rc);
		mutex_unlock(&wil->mutex);
		जाओ fail;
	पूर्ण

	/* Update the driver STA members with the new bss */
	wil->sta[cid].aid = data->aid;
	wil->sta[cid].stats.ft_roams++;
	ether_addr_copy(wil->sta[cid].addr, vअगर->bss->bssid);
	mutex_unlock(&wil->mutex);
	del_समयr_sync(&vअगर->connect_समयr);

	cfg80211_ref_bss(wiphy, vअगर->bss);
	freq = ieee80211_channel_to_frequency(ch, NL80211_BAND_60GHZ);

	स_रखो(&info, 0, माप(info));
	info.channel = ieee80211_get_channel(wiphy, freq);
	info.bss = vअगर->bss;
	info.req_ie = assoc_req_ie;
	info.req_ie_len = assoc_req_ie_len;
	info.resp_ie = assoc_resp_ie;
	info.resp_ie_len = assoc_resp_ie_len;
	cfg80211_roamed(ndev, &info, GFP_KERNEL);
	vअगर->bss = शून्य;

	वापस;

fail:
	wil6210_disconnect(vअगर, शून्य, WLAN_REASON_PREV_AUTH_NOT_VALID);
पूर्ण

अटल व्योम
wmi_evt_link_monitor(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wmi_link_monitor_event *evt = d;
	क्रमागत nl80211_cqm_rssi_threshold_event event_type;

	अगर (len < माप(*evt)) अणु
		wil_err(wil, "link monitor event too short %d\n", len);
		वापस;
	पूर्ण

	wil_dbg_wmi(wil, "link monitor event, type %d rssi %d (stored %d)\n",
		    evt->type, evt->rssi_level, wil->cqm_rssi_thold);

	अगर (evt->type != WMI_LINK_MONITOR_NOTIF_RSSI_THRESHOLD_EVT)
		/* ignore */
		वापस;

	event_type = (evt->rssi_level > wil->cqm_rssi_thold ?
		      NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH :
		      NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW);
	cfg80211_cqm_rssi_notअगरy(ndev, event_type, evt->rssi_level, GFP_KERNEL);
पूर्ण

/* Some events are ignored क्रम purpose; and need not be पूर्णांकerpreted as
 * "unhandled events"
 */
अटल व्योम wmi_evt_ignore(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, व्योम *d, पूर्णांक len)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_dbg_wmi(wil, "Ignore event 0x%04x len %d\n", id, len);
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक eventid;
	व्योम (*handler)(काष्ठा wil6210_vअगर *vअगर,
			पूर्णांक eventid, व्योम *data, पूर्णांक data_len);
पूर्ण wmi_evt_handlers[] = अणु
	अणुWMI_READY_EVENTID,		wmi_evt_पढ़ोyपूर्ण,
	अणुWMI_FW_READY_EVENTID,			wmi_evt_ignoreपूर्ण,
	अणुWMI_RX_MGMT_PACKET_EVENTID,	wmi_evt_rx_mgmtपूर्ण,
	अणुWMI_TX_MGMT_PACKET_EVENTID,		wmi_evt_tx_mgmtपूर्ण,
	अणुWMI_SCAN_COMPLETE_EVENTID,	wmi_evt_scan_completeपूर्ण,
	अणुWMI_CONNECT_EVENTID,		wmi_evt_connectपूर्ण,
	अणुWMI_DISCONNECT_EVENTID,	wmi_evt_disconnectपूर्ण,
	अणुWMI_EAPOL_RX_EVENTID,		wmi_evt_eapol_rxपूर्ण,
	अणुWMI_BA_STATUS_EVENTID,		wmi_evt_ba_statusपूर्ण,
	अणुWMI_RCP_ADDBA_REQ_EVENTID,	wmi_evt_addba_rx_reqपूर्ण,
	अणुWMI_DELBA_EVENTID,		wmi_evt_delbaपूर्ण,
	अणुWMI_RING_EN_EVENTID,		wmi_evt_ring_enपूर्ण,
	अणुWMI_DATA_PORT_OPEN_EVENTID,		wmi_evt_ignoreपूर्ण,
	अणुWMI_SCHED_SCAN_RESULT_EVENTID,		wmi_evt_sched_scan_resultपूर्ण,
	अणुWMI_LINK_STATS_EVENTID,		wmi_evt_link_statsपूर्ण,
	अणुWMI_FT_AUTH_STATUS_EVENTID,		wmi_evt_auth_statusपूर्ण,
	अणुWMI_FT_REASSOC_STATUS_EVENTID,		wmi_evt_reassoc_statusपूर्ण,
	अणुWMI_LINK_MONITOR_EVENTID,		wmi_evt_link_monitorपूर्ण,
पूर्ण;

/*
 * Run in IRQ context
 * Extract WMI command from mailbox. Queue it to the @wil->pending_wmi_ev
 * that will be eventually handled by the @wmi_event_worker in the thपढ़ो
 * context of thपढ़ो "wil6210_wmi"
 */
व्योम wmi_recv_cmd(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_mbox_ring_desc d_tail;
	काष्ठा wil6210_mbox_hdr hdr;
	काष्ठा wil6210_mbox_ring *r = &wil->mbox_ctl.rx;
	काष्ठा pending_wmi_event *evt;
	u8 *cmd;
	व्योम __iomem *src;
	uदीर्घ flags;
	अचिन्हित n;
	अचिन्हित पूर्णांक num_immed_reply = 0;

	अगर (!test_bit(wil_status_mbox_पढ़ोy, wil->status)) अणु
		wil_err(wil, "Reset in progress. Cannot handle WMI event\n");
		वापस;
	पूर्ण

	अगर (test_bit(wil_status_suspended, wil->status)) अणु
		wil_err(wil, "suspended. cannot handle WMI event\n");
		वापस;
	पूर्ण

	क्रम (n = 0;; n++) अणु
		u16 len;
		bool q;
		bool immed_reply = false;

		r->head = wil_r(wil, RGF_MBOX +
				दुरत्व(काष्ठा wil6210_mbox_ctl, rx.head));
		अगर (r->tail == r->head)
			अवरोध;

		wil_dbg_wmi(wil, "Mbox head %08x tail %08x\n",
			    r->head, r->tail);
		/* पढ़ो cmd descriptor from tail */
		wil_स_नकल_fromio_32(&d_tail, wil->csr + HOSTADDR(r->tail),
				     माप(काष्ठा wil6210_mbox_ring_desc));
		अगर (d_tail.sync == 0) अणु
			wil_err(wil, "Mbox evt not owned by FW?\n");
			अवरोध;
		पूर्ण

		/* पढ़ो cmd header from descriptor */
		अगर (0 != wmi_पढ़ो_hdr(wil, d_tail.addr, &hdr)) अणु
			wil_err(wil, "Mbox evt at 0x%08x?\n",
				le32_to_cpu(d_tail.addr));
			अवरोध;
		पूर्ण
		len = le16_to_cpu(hdr.len);
		wil_dbg_wmi(wil, "Mbox evt %04x %04x %04x %02x\n",
			    le16_to_cpu(hdr.seq), len, le16_to_cpu(hdr.type),
			    hdr.flags);

		/* पढ़ो cmd buffer from descriptor */
		src = wmi_buffer(wil, d_tail.addr) +
		      माप(काष्ठा wil6210_mbox_hdr);
		evt = kदो_स्मृति(ALIGN(दुरत्व(काष्ठा pending_wmi_event,
					     event.wmi) + len, 4),
			      GFP_KERNEL);
		अगर (!evt)
			अवरोध;

		evt->event.hdr = hdr;
		cmd = (व्योम *)&evt->event.wmi;
		wil_स_नकल_fromio_32(cmd, src, len);
		/* mark entry as empty */
		wil_w(wil, r->tail +
		      दुरत्व(काष्ठा wil6210_mbox_ring_desc, sync), 0);
		/* indicate */
		अगर ((hdr.type == WIL_MBOX_HDR_TYPE_WMI) &&
		    (len >= माप(काष्ठा wmi_cmd_hdr))) अणु
			काष्ठा wmi_cmd_hdr *wmi = &evt->event.wmi;
			u16 id = le16_to_cpu(wmi->command_id);
			u8 mid = wmi->mid;
			u32 tstamp = le32_to_cpu(wmi->fw_बारtamp);
			अगर (test_bit(wil_status_resuming, wil->status)) अणु
				अगर (id == WMI_TRAFFIC_RESUME_EVENTID)
					clear_bit(wil_status_resuming,
						  wil->status);
				अन्यथा
					wil_err(wil,
						"WMI evt %d while resuming\n",
						id);
			पूर्ण
			spin_lock_irqsave(&wil->wmi_ev_lock, flags);
			अगर (wil->reply_id && wil->reply_id == id &&
			    wil->reply_mid == mid) अणु
				अगर (wil->reply_buf) अणु
					स_नकल(wil->reply_buf, wmi,
					       min(len, wil->reply_size));
					immed_reply = true;
				पूर्ण
				अगर (id == WMI_TRAFFIC_SUSPEND_EVENTID) अणु
					wil_dbg_wmi(wil,
						    "set suspend_resp_rcvd\n");
					wil->suspend_resp_rcvd = true;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);

			wil_dbg_wmi(wil, "recv %s (0x%04x) MID %d @%d msec\n",
				    eventid2name(id), id, wmi->mid, tstamp);
			trace_wil6210_wmi_event(wmi, &wmi[1],
						len - माप(*wmi));
		पूर्ण
		wil_hex_dump_wmi("evt ", DUMP_PREFIX_OFFSET, 16, 1,
				 &evt->event.hdr, माप(hdr) + len, true);

		/* advance tail */
		r->tail = r->base + ((r->tail - r->base +
			  माप(काष्ठा wil6210_mbox_ring_desc)) % r->size);
		wil_w(wil, RGF_MBOX +
		      दुरत्व(काष्ठा wil6210_mbox_ctl, rx.tail), r->tail);

		अगर (immed_reply) अणु
			wil_dbg_wmi(wil, "recv_cmd: Complete WMI 0x%04x\n",
				    wil->reply_id);
			kमुक्त(evt);
			num_immed_reply++;
			complete(&wil->wmi_call);
		पूर्ण अन्यथा अणु
			/* add to the pending list */
			spin_lock_irqsave(&wil->wmi_ev_lock, flags);
			list_add_tail(&evt->list, &wil->pending_wmi_ev);
			spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);
			q = queue_work(wil->wmi_wq, &wil->wmi_event_worker);
			wil_dbg_wmi(wil, "queue_work -> %d\n", q);
		पूर्ण
	पूर्ण
	/* normally, 1 event per IRQ should be processed */
	wil_dbg_wmi(wil, "recv_cmd: -> %d events queued, %d completed\n",
		    n - num_immed_reply, num_immed_reply);
पूर्ण

पूर्णांक wmi_call(काष्ठा wil6210_priv *wil, u16 cmdid, u8 mid, व्योम *buf, u16 len,
	     u16 reply_id, व्योम *reply, u16 reply_size, पूर्णांक to_msec)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ reमुख्य;
	uदीर्घ flags;

	mutex_lock(&wil->wmi_mutex);

	spin_lock_irqsave(&wil->wmi_ev_lock, flags);
	wil->reply_id = reply_id;
	wil->reply_mid = mid;
	wil->reply_buf = reply;
	wil->reply_size = reply_size;
	reinit_completion(&wil->wmi_call);
	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);

	rc = __wmi_send(wil, cmdid, mid, buf, len);
	अगर (rc)
		जाओ out;

	reमुख्य = रुको_क्रम_completion_समयout(&wil->wmi_call,
					     msecs_to_jअगरfies(to_msec));
	अगर (0 == reमुख्य) अणु
		wil_err(wil, "wmi_call(0x%04x->0x%04x) timeout %d msec\n",
			cmdid, reply_id, to_msec);
		rc = -ETIME;
	पूर्ण अन्यथा अणु
		wil_dbg_wmi(wil,
			    "wmi_call(0x%04x->0x%04x) completed in %d msec\n",
			    cmdid, reply_id,
			    to_msec - jअगरfies_to_msecs(reमुख्य));
	पूर्ण

out:
	spin_lock_irqsave(&wil->wmi_ev_lock, flags);
	wil->reply_id = 0;
	wil->reply_mid = U8_MAX;
	wil->reply_buf = शून्य;
	wil->reply_size = 0;
	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);

	mutex_unlock(&wil->wmi_mutex);

	वापस rc;
पूर्ण

पूर्णांक wmi_echo(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_echo_cmd cmd = अणु
		.value = cpu_to_le32(0x12345678),
	पूर्ण;

	वापस wmi_call(wil, WMI_ECHO_CMDID, vअगर->mid, &cmd, माप(cmd),
			WMI_ECHO_RSP_EVENTID, शून्य, 0,
			WIL_WMI_CALL_GENERAL_TO_MS);
पूर्ण

पूर्णांक wmi_set_mac_address(काष्ठा wil6210_priv *wil, व्योम *addr)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_set_mac_address_cmd cmd;

	ether_addr_copy(cmd.mac, addr);

	wil_dbg_wmi(wil, "Set MAC %pM\n", addr);

	वापस wmi_send(wil, WMI_SET_MAC_ADDRESS_CMDID, vअगर->mid,
			&cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_led_cfg(काष्ठा wil6210_priv *wil, bool enable)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc = 0;
	काष्ठा wmi_led_cfg_cmd cmd = अणु
		.led_mode = enable,
		.id = led_id,
		.slow_blink_cfg.blink_on =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_SLOW].on_ms),
		.slow_blink_cfg.blink_off =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_SLOW].off_ms),
		.medium_blink_cfg.blink_on =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_MED].on_ms),
		.medium_blink_cfg.blink_off =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_MED].off_ms),
		.fast_blink_cfg.blink_on =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_FAST].on_ms),
		.fast_blink_cfg.blink_off =
			cpu_to_le32(led_blink_समय[WIL_LED_TIME_FAST].off_ms),
		.led_polarity = led_polarity,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_led_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = cpu_to_le32(WMI_FW_STATUS_FAILURE)पूर्ण,
	पूर्ण;

	अगर (led_id == WIL_LED_INVALID_ID)
		जाओ out;

	अगर (led_id > WIL_LED_MAX_ID) अणु
		wil_err(wil, "Invalid led id %d\n", led_id);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	wil_dbg_wmi(wil,
		    "%s led %d\n",
		    enable ? "enabling" : "disabling", led_id);

	rc = wmi_call(wil, WMI_LED_CFG_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_LED_CFG_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		जाओ out;

	अगर (reply.evt.status) अणु
		wil_err(wil, "led %d cfg failed with status %d\n",
			led_id, le32_to_cpu(reply.evt.status));
		rc = -EINVAL;
	पूर्ण

out:
	वापस rc;
पूर्ण

पूर्णांक wmi_rbufcap_cfg(काष्ठा wil6210_priv *wil, bool enable, u16 threshold)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;

	काष्ठा wmi_rbufcap_cfg_cmd cmd = अणु
		.enable = enable,
		.rx_desc_threshold = cpu_to_le16(threshold),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_rbufcap_cfg_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	rc = wmi_call(wil, WMI_RBUFCAP_CFG_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_RBUFCAP_CFG_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "RBUFCAP_CFG failed. status %d\n",
			reply.evt.status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_pcp_start(काष्ठा wil6210_vअगर *vअगर, पूर्णांक bi, u8 wmi_nettype,
		  u8 chan, u8 wmi_edmg_chan, u8 hidden_ssid, u8 is_go)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;

	काष्ठा wmi_pcp_start_cmd cmd = अणु
		.bcon_पूर्णांकerval = cpu_to_le16(bi),
		.network_type = wmi_nettype,
		.disable_sec_offload = 1,
		.channel = chan - 1,
		.edmg_channel = wmi_edmg_chan,
		.pcp_max_assoc_sta = wil->max_assoc_sta,
		.hidden_ssid = hidden_ssid,
		.is_go = is_go,
		.ap_sme_offload_mode = disable_ap_sme ?
				       WMI_AP_SME_OFFLOAD_PARTIAL :
				       WMI_AP_SME_OFFLOAD_FULL,
		.abft_len = wil->abft_len,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_pcp_started_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	अगर (!vअगर->privacy)
		cmd.disable_sec = 1;

	अगर ((cmd.pcp_max_assoc_sta > WIL6210_MAX_CID) ||
	    (cmd.pcp_max_assoc_sta <= 0)) अणु
		wil_err(wil, "unexpected max_assoc_sta %d\n",
			cmd.pcp_max_assoc_sta);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (disable_ap_sme &&
	    !test_bit(WMI_FW_CAPABILITY_AP_SME_OFFLOAD_PARTIAL,
		      wil->fw_capabilities)) अणु
		wil_err(wil, "disable_ap_sme not supported by FW\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Processing समय may be huge, in हाल of secure AP it takes about
	 * 3500ms क्रम FW to start AP
	 */
	rc = wmi_call(wil, WMI_PCP_START_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_PCP_STARTED_EVENTID, &reply, माप(reply), 5000);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS)
		rc = -EINVAL;

	अगर (wmi_nettype != WMI_NETTYPE_P2P)
		/* Don't fail due to error in the led configuration */
		wmi_led_cfg(wil, true);

	वापस rc;
पूर्ण

पूर्णांक wmi_pcp_stop(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;

	rc = wmi_led_cfg(wil, false);
	अगर (rc)
		वापस rc;

	वापस wmi_call(wil, WMI_PCP_STOP_CMDID, vअगर->mid, शून्य, 0,
			WMI_PCP_STOPPED_EVENTID, शून्य, 0,
			WIL_WMI_PCP_STOP_TO_MS);
पूर्ण

पूर्णांक wmi_set_ssid(काष्ठा wil6210_vअगर *vअगर, u8 ssid_len, स्थिर व्योम *ssid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_set_ssid_cmd cmd = अणु
		.ssid_len = cpu_to_le32(ssid_len),
	पूर्ण;

	अगर (ssid_len > माप(cmd.ssid))
		वापस -EINVAL;

	स_नकल(cmd.ssid, ssid, ssid_len);

	वापस wmi_send(wil, WMI_SET_SSID_CMDID, vअगर->mid, &cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_get_ssid(काष्ठा wil6210_vअगर *vअगर, u8 *ssid_len, व्योम *ssid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_set_ssid_cmd cmd;
	पूर्ण __packed reply;
	पूर्णांक len; /* reply.cmd.ssid_len in CPU order */

	स_रखो(&reply, 0, माप(reply));

	rc = wmi_call(wil, WMI_GET_SSID_CMDID, vअगर->mid, शून्य, 0,
		      WMI_GET_SSID_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	len = le32_to_cpu(reply.cmd.ssid_len);
	अगर (len > माप(reply.cmd.ssid))
		वापस -EINVAL;

	*ssid_len = len;
	स_नकल(ssid, reply.cmd.ssid, len);

	वापस 0;
पूर्ण

पूर्णांक wmi_set_channel(काष्ठा wil6210_priv *wil, पूर्णांक channel)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_set_pcp_channel_cmd cmd = अणु
		.channel = channel - 1,
	पूर्ण;

	वापस wmi_send(wil, WMI_SET_PCP_CHANNEL_CMDID, vअगर->mid,
			&cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_get_channel(काष्ठा wil6210_priv *wil, पूर्णांक *channel)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_set_pcp_channel_cmd cmd;
	पूर्ण __packed reply;

	स_रखो(&reply, 0, माप(reply));

	rc = wmi_call(wil, WMI_GET_PCP_CHANNEL_CMDID, vअगर->mid, शून्य, 0,
		      WMI_GET_PCP_CHANNEL_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.cmd.channel > 3)
		वापस -EINVAL;

	*channel = reply.cmd.channel + 1;

	वापस 0;
पूर्ण

पूर्णांक wmi_p2p_cfg(काष्ठा wil6210_vअगर *vअगर, पूर्णांक channel, पूर्णांक bi)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_p2p_cfg_cmd cmd = अणु
		.discovery_mode = WMI_DISCOVERY_MODE_PEER2PEER,
		.bcon_पूर्णांकerval = cpu_to_le16(bi),
		.channel = channel - 1,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_p2p_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_wmi(wil, "sending WMI_P2P_CFG_CMDID\n");

	rc = wmi_call(wil, WMI_P2P_CFG_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_P2P_CFG_DONE_EVENTID, &reply, माप(reply), 300);
	अगर (!rc && reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "P2P_CFG failed. status %d\n", reply.evt.status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_start_listen(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_listen_started_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_wmi(wil, "sending WMI_START_LISTEN_CMDID\n");

	rc = wmi_call(wil, WMI_START_LISTEN_CMDID, vअगर->mid, शून्य, 0,
		      WMI_LISTEN_STARTED_EVENTID, &reply, माप(reply), 300);
	अगर (!rc && reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "device failed to start listen. status %d\n",
			reply.evt.status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_start_search(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_search_started_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_wmi(wil, "sending WMI_START_SEARCH_CMDID\n");

	rc = wmi_call(wil, WMI_START_SEARCH_CMDID, vअगर->mid, शून्य, 0,
		      WMI_SEARCH_STARTED_EVENTID, &reply, माप(reply), 300);
	अगर (!rc && reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "device failed to start search. status %d\n",
			reply.evt.status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_stop_discovery(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;

	wil_dbg_wmi(wil, "sending WMI_DISCOVERY_STOP_CMDID\n");

	rc = wmi_call(wil, WMI_DISCOVERY_STOP_CMDID, vअगर->mid, शून्य, 0,
		      WMI_DISCOVERY_STOPPED_EVENTID, शून्य, 0,
		      WIL_WMI_CALL_GENERAL_TO_MS);

	अगर (rc)
		wil_err(wil, "Failed to stop discovery\n");

	वापस rc;
पूर्ण

पूर्णांक wmi_del_cipher_key(काष्ठा wil6210_vअगर *vअगर, u8 key_index,
		       स्थिर व्योम *mac_addr, पूर्णांक key_usage)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_delete_cipher_key_cmd cmd = अणु
		.key_index = key_index,
	पूर्ण;

	अगर (mac_addr)
		स_नकल(cmd.mac, mac_addr, WMI_MAC_LEN);

	वापस wmi_send(wil, WMI_DELETE_CIPHER_KEY_CMDID, vअगर->mid,
			&cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_add_cipher_key(काष्ठा wil6210_vअगर *vअगर, u8 key_index,
		       स्थिर व्योम *mac_addr, पूर्णांक key_len, स्थिर व्योम *key,
		       पूर्णांक key_usage)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_add_cipher_key_cmd cmd = अणु
		.key_index = key_index,
		.key_usage = key_usage,
		.key_len = key_len,
	पूर्ण;

	अगर (key_len > माप(cmd.key))
		वापस -EINVAL;

	/* key len = 0 is allowed only क्रम usage of WMI_KEY_USE_APPLY */
	अगर ((key_len == 0 || !key) &&
	    key_usage != WMI_KEY_USE_APPLY_PTK)
		वापस -EINVAL;

	अगर (key)
		स_नकल(cmd.key, key, key_len);

	अगर (mac_addr)
		स_नकल(cmd.mac, mac_addr, WMI_MAC_LEN);

	वापस wmi_send(wil, WMI_ADD_CIPHER_KEY_CMDID, vअगर->mid,
			&cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_set_ie(काष्ठा wil6210_vअगर *vअगर, u8 type, u16 ie_len, स्थिर व्योम *ie)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[WMI_FRAME_BEACON]	= "BEACON",
		[WMI_FRAME_PROBE_REQ]	= "PROBE_REQ",
		[WMI_FRAME_PROBE_RESP]	= "WMI_FRAME_PROBE_RESP",
		[WMI_FRAME_ASSOC_REQ]	= "WMI_FRAME_ASSOC_REQ",
		[WMI_FRAME_ASSOC_RESP]	= "WMI_FRAME_ASSOC_RESP",
	पूर्ण;
	पूर्णांक rc;
	u16 len = माप(काष्ठा wmi_set_appie_cmd) + ie_len;
	काष्ठा wmi_set_appie_cmd *cmd;

	अगर (len < ie_len) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	cmd = kzalloc(len, GFP_KERNEL);
	अगर (!cmd) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (!ie)
		ie_len = 0;

	cmd->mgmt_frm_type = type;
	/* BUG: FW API define ieLen as u8. Will fix FW */
	cmd->ie_len = cpu_to_le16(ie_len);
	अगर (ie_len)
		स_नकल(cmd->ie_info, ie, ie_len);
	rc = wmi_send(wil, WMI_SET_APPIE_CMDID, vअगर->mid, cmd, len);
	kमुक्त(cmd);
out:
	अगर (rc) अणु
		स्थिर अक्षर *name = type < ARRAY_SIZE(names) ?
				   names[type] : "??";
		wil_err(wil, "set_ie(%d %s) failed : %d\n", type, name, rc);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_update_ft_ies(काष्ठा wil6210_vअगर *vअगर, u16 ie_len, स्थिर व्योम *ie)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	u16 len;
	काष्ठा wmi_update_ft_ies_cmd *cmd;
	पूर्णांक rc;

	अगर (!ie)
		ie_len = 0;

	len = माप(काष्ठा wmi_update_ft_ies_cmd) + ie_len;
	अगर (len < ie_len) अणु
		wil_err(wil, "wraparound. ie len %d\n", ie_len);
		वापस -EINVAL;
	पूर्ण

	cmd = kzalloc(len, GFP_KERNEL);
	अगर (!cmd) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->ie_len = cpu_to_le16(ie_len);
	अगर (ie_len)
		स_नकल(cmd->ie_info, ie, ie_len);
	rc = wmi_send(wil, WMI_UPDATE_FT_IES_CMDID, vअगर->mid, cmd, len);
	kमुक्त(cmd);

out:
	अगर (rc)
		wil_err(wil, "update ft ies failed : %d\n", rc);

	वापस rc;
पूर्ण

/**
 * wmi_rxon - turn radio on/off
 * @wil:	driver data
 * @on:		turn on अगर true, off otherwise
 *
 * Only चयन radio. Channel should be set separately.
 * No समयout क्रम rxon - radio turned on क्रमever unless some other call
 * turns it off
 */
पूर्णांक wmi_rxon(काष्ठा wil6210_priv *wil, bool on)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_listen_started_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_info(wil, "(%s)\n", on ? "on" : "off");

	अगर (on) अणु
		rc = wmi_call(wil, WMI_START_LISTEN_CMDID, vअगर->mid, शून्य, 0,
			      WMI_LISTEN_STARTED_EVENTID,
			      &reply, माप(reply),
			      WIL_WMI_CALL_GENERAL_TO_MS);
		अगर ((rc == 0) && (reply.evt.status != WMI_FW_STATUS_SUCCESS))
			rc = -EINVAL;
	पूर्ण अन्यथा अणु
		rc = wmi_call(wil, WMI_DISCOVERY_STOP_CMDID, vअगर->mid, शून्य, 0,
			      WMI_DISCOVERY_STOPPED_EVENTID, शून्य, 0,
			      WIL_WMI_CALL_GENERAL_TO_MS);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_rx_chain_add(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *vring)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wmi_cfg_rx_chain_cmd cmd = अणु
		.action = WMI_RX_CHAIN_ADD,
		.rx_sw_ring = अणु
			.max_mpdu_size = cpu_to_le16(
				wil_mtu2macbuf(wil->rx_buf_len)),
			.ring_mem_base = cpu_to_le64(vring->pa),
			.ring_size = cpu_to_le16(vring->size),
		पूर्ण,
		.mid = 0, /* TODO - what is it? */
		.decap_trans_type = WMI_DECAP_TYPE_802_3,
		.reorder_type = WMI_RX_SW_REORDER,
		.host_thrsh = cpu_to_le16(rx_ring_overflow_thrsh),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_cfg_rx_chain_करोne_event evt;
	पूर्ण __packed evt;
	पूर्णांक rc;

	स_रखो(&evt, 0, माप(evt));

	अगर (wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		काष्ठा ieee80211_channel *ch = wil->monitor_chandef.chan;

		cmd.snअगरfer_cfg.mode = cpu_to_le32(WMI_SNIFFER_ON);
		अगर (ch)
			cmd.snअगरfer_cfg.channel = ch->hw_value - 1;
		cmd.snअगरfer_cfg.phy_info_mode =
			cpu_to_le32(WMI_SNIFFER_PHY_INFO_DISABLED);
		cmd.snअगरfer_cfg.phy_support =
			cpu_to_le32((wil->monitor_flags & MONITOR_FLAG_CONTROL)
				    ? WMI_SNIFFER_CP : WMI_SNIFFER_BOTH_PHYS);
	पूर्ण अन्यथा अणु
		/* Initialize offload (in non-snअगरfer mode).
		 * Linux IP stack always calculates IP checksum
		 * HW always calculate TCP/UDP checksum
		 */
		cmd.l3_l4_ctrl |= (1 << L3_L4_CTRL_TCPIP_CHECKSUM_EN_POS);
	पूर्ण

	अगर (rx_align_2)
		cmd.l2_802_3_offload_ctrl |=
				L2_802_3_OFFLOAD_CTRL_SNAP_KEEP_MSK;

	/* typical समय क्रम secure PCP is 840ms */
	rc = wmi_call(wil, WMI_CFG_RX_CHAIN_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_CFG_RX_CHAIN_DONE_EVENTID, &evt, माप(evt), 2000);
	अगर (rc)
		वापस rc;

	अगर (le32_to_cpu(evt.evt.status) != WMI_CFG_RX_CHAIN_SUCCESS)
		rc = -EINVAL;

	vring->hwtail = le32_to_cpu(evt.evt.rx_ring_tail_ptr);

	wil_dbg_misc(wil, "Rx init: status %d tail 0x%08x\n",
		     le32_to_cpu(evt.evt.status), vring->hwtail);

	वापस rc;
पूर्ण

पूर्णांक wmi_get_temperature(काष्ठा wil6210_priv *wil, u32 *t_bb, u32 *t_rf)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_temp_sense_cmd cmd = अणु
		.measure_baseband_en = cpu_to_le32(!!t_bb),
		.measure_rf_en = cpu_to_le32(!!t_rf),
		.measure_mode = cpu_to_le32(TEMPERATURE_MEASURE_NOW),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_temp_sense_करोne_event evt;
	पूर्ण __packed reply;

	स_रखो(&reply, 0, माप(reply));

	rc = wmi_call(wil, WMI_TEMP_SENSE_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_TEMP_SENSE_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (t_bb)
		*t_bb = le32_to_cpu(reply.evt.baseband_t1000);
	अगर (t_rf)
		*t_rf = le32_to_cpu(reply.evt.rf_t1000);

	वापस 0;
पूर्ण

पूर्णांक wmi_get_all_temperatures(काष्ठा wil6210_priv *wil,
			     काष्ठा wmi_temp_sense_all_करोne_event
			     *sense_all_evt)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_temp_sense_all_cmd cmd = अणु
		.measure_baseband_en = true,
		.measure_rf_en = true,
		.measure_mode = TEMPERATURE_MEASURE_NOW,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_temp_sense_all_करोne_event evt;
	पूर्ण __packed reply;

	अगर (!sense_all_evt) अणु
		wil_err(wil, "Invalid sense_all_evt value\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&reply, 0, माप(reply));
	reply.evt.status = WMI_FW_STATUS_FAILURE;
	rc = wmi_call(wil, WMI_TEMP_SENSE_ALL_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_TEMP_SENSE_ALL_DONE_EVENTID,
		      &reply, माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status == WMI_FW_STATUS_FAILURE) अणु
		wil_err(wil, "Failed getting TEMP_SENSE_ALL\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(sense_all_evt, &reply.evt, माप(reply.evt));
	वापस 0;
पूर्ण

पूर्णांक wmi_disconnect_sta(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *mac, u16 reason,
		       bool del_sta)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_disconnect_sta_cmd disc_sta_cmd = अणु
		.disconnect_reason = cpu_to_le16(reason),
	पूर्ण;
	काष्ठा wmi_del_sta_cmd del_sta_cmd = अणु
		.disconnect_reason = cpu_to_le16(reason),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_disconnect_event evt;
	पूर्ण __packed reply;

	wil_dbg_wmi(wil, "disconnect_sta: (%pM, reason %d)\n", mac, reason);

	स_रखो(&reply, 0, माप(reply));
	vअगर->locally_generated_disc = true;
	अगर (del_sta) अणु
		ether_addr_copy(del_sta_cmd.dst_mac, mac);
		rc = wmi_call(wil, WMI_DEL_STA_CMDID, vअगर->mid, &del_sta_cmd,
			      माप(del_sta_cmd), WMI_DISCONNECT_EVENTID,
			      &reply, माप(reply), 1000);
	पूर्ण अन्यथा अणु
		ether_addr_copy(disc_sta_cmd.dst_mac, mac);
		rc = wmi_call(wil, WMI_DISCONNECT_STA_CMDID, vअगर->mid,
			      &disc_sta_cmd, माप(disc_sta_cmd),
			      WMI_DISCONNECT_EVENTID,
			      &reply, माप(reply), 1000);
	पूर्ण
	/* failure to disconnect in reasonable समय treated as FW error */
	अगर (rc) अणु
		wil_fw_error_recovery(wil);
		वापस rc;
	पूर्ण
	wil->sinfo_gen++;

	वापस 0;
पूर्ण

पूर्णांक wmi_addba(काष्ठा wil6210_priv *wil, u8 mid,
	      u8 ringid, u8 size, u16 समयout)
अणु
	u8 amsdu = wil->use_enhanced_dma_hw && wil->use_rx_hw_reordering &&
		test_bit(WMI_FW_CAPABILITY_AMSDU, wil->fw_capabilities) &&
		wil->amsdu_en;
	काष्ठा wmi_ring_ba_en_cmd cmd = अणु
		.ring_id = ringid,
		.agg_max_wsize = size,
		.ba_समयout = cpu_to_le16(समयout),
		.amsdu = amsdu,
	पूर्ण;

	wil_dbg_wmi(wil, "addba: (ring %d size %d timeout %d amsdu %d)\n",
		    ringid, size, समयout, amsdu);

	वापस wmi_send(wil, WMI_RING_BA_EN_CMDID, mid, &cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_delba_tx(काष्ठा wil6210_priv *wil, u8 mid, u8 ringid, u16 reason)
अणु
	काष्ठा wmi_ring_ba_dis_cmd cmd = अणु
		.ring_id = ringid,
		.reason = cpu_to_le16(reason),
	पूर्ण;

	wil_dbg_wmi(wil, "delba_tx: (ring %d reason %d)\n", ringid, reason);

	वापस wmi_send(wil, WMI_RING_BA_DIS_CMDID, mid, &cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_delba_rx(काष्ठा wil6210_priv *wil, u8 mid, u8 cid, u8 tid, u16 reason)
अणु
	काष्ठा wmi_rcp_delba_cmd cmd = अणु
		.reason = cpu_to_le16(reason),
	पूर्ण;

	अगर (cid >= WIL6210_RX_DESC_MAX_CID) अणु
		cmd.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.cid = cid;
		cmd.tid = tid;
	पूर्ण अन्यथा अणु
		cmd.cidxtid = mk_cidxtid(cid, tid);
	पूर्ण

	wil_dbg_wmi(wil, "delba_rx: (CID %d TID %d reason %d)\n", cid,
		    tid, reason);

	वापस wmi_send(wil, WMI_RCP_DELBA_CMDID, mid, &cmd, माप(cmd));
पूर्ण

पूर्णांक wmi_addba_rx_resp(काष्ठा wil6210_priv *wil,
		      u8 mid, u8 cid, u8 tid, u8 token,
		      u16 status, bool amsdu, u16 agg_wsize, u16 समयout)
अणु
	पूर्णांक rc;
	काष्ठा wmi_rcp_addba_resp_cmd cmd = अणु
		.dialog_token = token,
		.status_code = cpu_to_le16(status),
		/* bit 0: A-MSDU supported
		 * bit 1: policy (controlled by FW)
		 * bits 2..5: TID
		 * bits 6..15: buffer size
		 */
		.ba_param_set = cpu_to_le16((amsdu ? 1 : 0) | (tid << 2) |
					    (agg_wsize << 6)),
		.ba_समयout = cpu_to_le16(समयout),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_rcp_addba_resp_sent_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = cpu_to_le16(WMI_FW_STATUS_FAILURE)पूर्ण,
	पूर्ण;

	अगर (cid >= WIL6210_RX_DESC_MAX_CID) अणु
		cmd.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.cid = cid;
		cmd.tid = tid;
	पूर्ण अन्यथा अणु
		cmd.cidxtid = mk_cidxtid(cid, tid);
	पूर्ण

	wil_dbg_wmi(wil,
		    "ADDBA response for MID %d CID %d TID %d size %d timeout %d status %d AMSDU%s\n",
		    mid, cid, tid, agg_wsize,
		    समयout, status, amsdu ? "+" : "-");

	rc = wmi_call(wil, WMI_RCP_ADDBA_RESP_CMDID, mid, &cmd, माप(cmd),
		      WMI_RCP_ADDBA_RESP_SENT_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status) अणु
		wil_err(wil, "ADDBA response failed with status %d\n",
			le16_to_cpu(reply.evt.status));
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_addba_rx_resp_edma(काष्ठा wil6210_priv *wil, u8 mid, u8 cid, u8 tid,
			   u8 token, u16 status, bool amsdu, u16 agg_wsize,
			   u16 समयout)
अणु
	पूर्णांक rc;
	काष्ठा wmi_rcp_addba_resp_edma_cmd cmd = अणु
		.cid = cid,
		.tid = tid,
		.dialog_token = token,
		.status_code = cpu_to_le16(status),
		/* bit 0: A-MSDU supported
		 * bit 1: policy (controlled by FW)
		 * bits 2..5: TID
		 * bits 6..15: buffer size
		 */
		.ba_param_set = cpu_to_le16((amsdu ? 1 : 0) | (tid << 2) |
					    (agg_wsize << 6)),
		.ba_समयout = cpu_to_le16(समयout),
		/* route all the connections to status ring 0 */
		.status_ring_id = WIL_DEFAULT_RX_STATUS_RING_ID,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_rcp_addba_resp_sent_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = cpu_to_le16(WMI_FW_STATUS_FAILURE)पूर्ण,
	पूर्ण;

	wil_dbg_wmi(wil,
		    "ADDBA response for CID %d TID %d size %d timeout %d status %d AMSDU%s, sring_id %d\n",
		    cid, tid, agg_wsize, समयout, status, amsdu ? "+" : "-",
		    WIL_DEFAULT_RX_STATUS_RING_ID);

	rc = wmi_call(wil, WMI_RCP_ADDBA_RESP_EDMA_CMDID, mid, &cmd,
		      माप(cmd), WMI_RCP_ADDBA_RESP_SENT_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status) अणु
		wil_err(wil, "ADDBA response failed with status %d\n",
			le16_to_cpu(reply.evt.status));
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_ps_dev_profile_cfg(काष्ठा wil6210_priv *wil,
			   क्रमागत wmi_ps_profile_type ps_profile)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_ps_dev_profile_cfg_cmd cmd = अणु
		.ps_profile = ps_profile,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_ps_dev_profile_cfg_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = cpu_to_le32(WMI_PS_CFG_CMD_STATUS_ERROR)पूर्ण,
	पूर्ण;
	u32 status;

	wil_dbg_wmi(wil, "Setting ps dev profile %d\n", ps_profile);

	rc = wmi_call(wil, WMI_PS_DEV_PROखाता_CFG_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_PS_DEV_PROखाता_CFG_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	status = le32_to_cpu(reply.evt.status);

	अगर (status != WMI_PS_CFG_CMD_STATUS_SUCCESS) अणु
		wil_err(wil, "ps dev profile cfg failed with status %d\n",
			status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_set_mgmt_retry(काष्ठा wil6210_priv *wil, u8 retry_लघु)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_set_mgmt_retry_limit_cmd cmd = अणु
		.mgmt_retry_limit = retry_लघु,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_set_mgmt_retry_limit_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_wmi(wil, "Setting mgmt retry short %d\n", retry_लघु);

	अगर (!test_bit(WMI_FW_CAPABILITY_MGMT_RETRY_LIMIT, wil->fw_capabilities))
		वापस -ENOTSUPP;

	rc = wmi_call(wil, WMI_SET_MGMT_RETRY_LIMIT_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_SET_MGMT_RETRY_LIMIT_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "set mgmt retry limit failed with status %d\n",
			reply.evt.status);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक wmi_get_mgmt_retry(काष्ठा wil6210_priv *wil, u8 *retry_लघु)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_get_mgmt_retry_limit_event evt;
	पूर्ण __packed reply;

	wil_dbg_wmi(wil, "getting mgmt retry short\n");

	अगर (!test_bit(WMI_FW_CAPABILITY_MGMT_RETRY_LIMIT, wil->fw_capabilities))
		वापस -ENOTSUPP;

	स_रखो(&reply, 0, माप(reply));
	rc = wmi_call(wil, WMI_GET_MGMT_RETRY_LIMIT_CMDID, vअगर->mid, शून्य, 0,
		      WMI_GET_MGMT_RETRY_LIMIT_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (retry_लघु)
		*retry_लघु = reply.evt.mgmt_retry_limit;

	वापस 0;
पूर्ण

पूर्णांक wmi_पात_scan(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;

	wil_dbg_wmi(wil, "sending WMI_ABORT_SCAN_CMDID\n");

	rc = wmi_send(wil, WMI_ABORT_SCAN_CMDID, vअगर->mid, शून्य, 0);
	अगर (rc)
		wil_err(wil, "Failed to abort scan (%d)\n", rc);

	वापस rc;
पूर्ण

पूर्णांक wmi_new_sta(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *mac, u8 aid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_new_sta_cmd cmd = अणु
		.aid = aid,
	पूर्ण;

	wil_dbg_wmi(wil, "new sta %pM, aid %d\n", mac, aid);

	ether_addr_copy(cmd.dst_mac, mac);

	rc = wmi_send(wil, WMI_NEW_STA_CMDID, vअगर->mid, &cmd, माप(cmd));
	अगर (rc)
		wil_err(wil, "Failed to send new sta (%d)\n", rc);

	वापस rc;
पूर्ण

व्योम wmi_event_flush(काष्ठा wil6210_priv *wil)
अणु
	uदीर्घ flags;
	काष्ठा pending_wmi_event *evt, *t;

	wil_dbg_wmi(wil, "event_flush\n");

	spin_lock_irqsave(&wil->wmi_ev_lock, flags);

	list_क्रम_each_entry_safe(evt, t, &wil->pending_wmi_ev, list) अणु
		list_del(&evt->list);
		kमुक्त(evt);
	पूर्ण

	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);
पूर्ण

अटल स्थिर अक्षर *suspend_status2name(u8 status)
अणु
	चयन (status) अणु
	हाल WMI_TRAFFIC_SUSPEND_REJECTED_LINK_NOT_IDLE:
		वापस "LINK_NOT_IDLE";
	हाल WMI_TRAFFIC_SUSPEND_REJECTED_DISCONNECT:
		वापस "DISCONNECT";
	हाल WMI_TRAFFIC_SUSPEND_REJECTED_OTHER:
		वापस "OTHER";
	शेष:
		वापस "Untracked status";
	पूर्ण
पूर्ण

पूर्णांक wmi_suspend(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_traffic_suspend_cmd cmd = अणु
		.wakeup_trigger = wil->wakeup_trigger,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_traffic_suspend_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_TRAFFIC_SUSPEND_REJECTED_LINK_NOT_IDLEपूर्ण,
	पूर्ण;

	u32 suspend_to = WIL_WAIT_FOR_SUSPEND_RESUME_COMP;

	wil->suspend_resp_rcvd = false;
	wil->suspend_resp_comp = false;

	rc = wmi_call(wil, WMI_TRAFFIC_SUSPEND_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_TRAFFIC_SUSPEND_EVENTID, &reply, माप(reply),
		      suspend_to);
	अगर (rc) अणु
		wil_err(wil, "wmi_call for suspend req failed, rc=%d\n", rc);
		अगर (rc == -ETIME)
			/* wmi_call TO */
			wil->suspend_stats.rejected_by_device++;
		अन्यथा
			wil->suspend_stats.rejected_by_host++;
		जाओ out;
	पूर्ण

	wil_dbg_wmi(wil, "waiting for suspend_response_completed\n");

	rc = रुको_event_पूर्णांकerruptible_समयout(wil->wq,
					      wil->suspend_resp_comp,
					      msecs_to_jअगरfies(suspend_to));
	अगर (rc == 0) अणु
		wil_err(wil, "TO waiting for suspend_response_completed\n");
		अगर (wil->suspend_resp_rcvd)
			/* Device responded but we TO due to another reason */
			wil->suspend_stats.rejected_by_host++;
		अन्यथा
			wil->suspend_stats.rejected_by_device++;
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	wil_dbg_wmi(wil, "suspend_response_completed rcvd\n");
	अगर (reply.evt.status != WMI_TRAFFIC_SUSPEND_APPROVED) अणु
		wil_dbg_pm(wil, "device rejected the suspend, %s\n",
			   suspend_status2name(reply.evt.status));
		wil->suspend_stats.rejected_by_device++;
	पूर्ण
	rc = reply.evt.status;

out:
	wil->suspend_resp_rcvd = false;
	wil->suspend_resp_comp = false;

	वापस rc;
पूर्ण

अटल व्योम resume_triggers2string(u32 triggers, अक्षर *string, पूर्णांक str_size)
अणु
	string[0] = '\0';

	अगर (!triggers) अणु
		strlcat(string, " UNKNOWN", str_size);
		वापस;
	पूर्ण

	अगर (triggers & WMI_RESUME_TRIGGER_HOST)
		strlcat(string, " HOST", str_size);

	अगर (triggers & WMI_RESUME_TRIGGER_UCAST_RX)
		strlcat(string, " UCAST_RX", str_size);

	अगर (triggers & WMI_RESUME_TRIGGER_BCAST_RX)
		strlcat(string, " BCAST_RX", str_size);

	अगर (triggers & WMI_RESUME_TRIGGER_WMI_EVT)
		strlcat(string, " WMI_EVT", str_size);

	अगर (triggers & WMI_RESUME_TRIGGER_DISCONNECT)
		strlcat(string, " DISCONNECT", str_size);
पूर्ण

पूर्णांक wmi_resume(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	अक्षर string[100];
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_traffic_resume_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_TRAFFIC_RESUME_FAILED,
			.resume_triggers =
				cpu_to_le32(WMI_RESUME_TRIGGER_UNKNOWN)पूर्ण,
	पूर्ण;

	rc = wmi_call(wil, WMI_TRAFFIC_RESUME_CMDID, vअगर->mid, शून्य, 0,
		      WMI_TRAFFIC_RESUME_EVENTID, &reply, माप(reply),
		      WIL_WAIT_FOR_SUSPEND_RESUME_COMP);
	अगर (rc)
		वापस rc;
	resume_triggers2string(le32_to_cpu(reply.evt.resume_triggers), string,
			       माप(string));
	wil_dbg_pm(wil, "device resume %s, resume triggers:%s (0x%x)\n",
		   reply.evt.status ? "failed" : "passed", string,
		   le32_to_cpu(reply.evt.resume_triggers));

	वापस reply.evt.status;
पूर्ण

पूर्णांक wmi_port_allocate(काष्ठा wil6210_priv *wil, u8 mid,
		      स्थिर u8 *mac, क्रमागत nl80211_अगरtype अगरtype)
अणु
	पूर्णांक rc;
	काष्ठा wmi_port_allocate_cmd cmd = अणु
		.mid = mid,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_port_allocated_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_misc(wil, "port allocate, mid %d iftype %d, mac %pM\n",
		     mid, अगरtype, mac);

	ether_addr_copy(cmd.mac, mac);
	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
		cmd.port_role = WMI_PORT_STA;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		cmd.port_role = WMI_PORT_AP;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		cmd.port_role = WMI_PORT_P2P_CLIENT;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		cmd.port_role = WMI_PORT_P2P_GO;
		अवरोध;
	/* what about monitor??? */
	शेष:
		wil_err(wil, "unsupported iftype: %d\n", अगरtype);
		वापस -EINVAL;
	पूर्ण

	rc = wmi_call(wil, WMI_PORT_ALLOCATE_CMDID, mid,
		      &cmd, माप(cmd),
		      WMI_PORT_ALLOCATED_EVENTID, &reply,
		      माप(reply), 300);
	अगर (rc) अणु
		wil_err(wil, "failed to allocate port, status %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_PORT_ALLOCATE returned status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wmi_port_delete(काष्ठा wil6210_priv *wil, u8 mid)
अणु
	पूर्णांक rc;
	काष्ठा wmi_port_delete_cmd cmd = अणु
		.mid = mid,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_port_deleted_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	wil_dbg_misc(wil, "port delete, mid %d\n", mid);

	rc = wmi_call(wil, WMI_PORT_DELETE_CMDID, mid,
		      &cmd, माप(cmd),
		      WMI_PORT_DELETED_EVENTID, &reply,
		      माप(reply), 2000);
	अगर (rc) अणु
		wil_err(wil, "failed to delete port, status %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_PORT_DELETE returned status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool wmi_evt_call_handler(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id,
				 व्योम *d, पूर्णांक len)
अणु
	uपूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wmi_evt_handlers); i++) अणु
		अगर (wmi_evt_handlers[i].eventid == id) अणु
			wmi_evt_handlers[i].handler(vअगर, id, d, len);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम wmi_event_handle(काष्ठा wil6210_priv *wil,
			     काष्ठा wil6210_mbox_hdr *hdr)
अणु
	u16 len = le16_to_cpu(hdr->len);
	काष्ठा wil6210_vअगर *vअगर;

	अगर ((hdr->type == WIL_MBOX_HDR_TYPE_WMI) &&
	    (len >= माप(काष्ठा wmi_cmd_hdr))) अणु
		काष्ठा wmi_cmd_hdr *wmi = (व्योम *)(&hdr[1]);
		व्योम *evt_data = (व्योम *)(&wmi[1]);
		u16 id = le16_to_cpu(wmi->command_id);
		u8 mid = wmi->mid;

		wil_dbg_wmi(wil, "Handle %s (0x%04x) (reply_id 0x%04x,%d)\n",
			    eventid2name(id), id, wil->reply_id,
			    wil->reply_mid);

		अगर (mid == MID_BROADCAST)
			mid = 0;
		अगर (mid >= GET_MAX_VIFS(wil)) अणु
			wil_dbg_wmi(wil, "invalid mid %d, event skipped\n",
				    mid);
			वापस;
		पूर्ण
		vअगर = wil->vअगरs[mid];
		अगर (!vअगर) अणु
			wil_dbg_wmi(wil, "event for empty VIF(%d), skipped\n",
				    mid);
			वापस;
		पूर्ण

		/* check अगर someone रुकोs क्रम this event */
		अगर (wil->reply_id && wil->reply_id == id &&
		    wil->reply_mid == mid) अणु
			अगर (wil->reply_buf) अणु
				/* event received जबतक wmi_call is रुकोing
				 * with a buffer. Such event should be handled
				 * in wmi_recv_cmd function. Handling the event
				 * here means a previous wmi_call was समयout.
				 * Drop the event and करो not handle it.
				 */
				wil_err(wil,
					"Old event (%d, %s) while wmi_call is waiting. Drop it and Continue waiting\n",
					id, eventid2name(id));
				वापस;
			पूर्ण

			wmi_evt_call_handler(vअगर, id, evt_data,
					     len - माप(*wmi));
			wil_dbg_wmi(wil, "event_handle: Complete WMI 0x%04x\n",
				    id);
			complete(&wil->wmi_call);
			वापस;
		पूर्ण
		/* unsolicited event */
		/* search क्रम handler */
		अगर (!wmi_evt_call_handler(vअगर, id, evt_data,
					  len - माप(*wmi))) अणु
			wil_info(wil, "Unhandled event 0x%04x\n", id);
		पूर्ण
	पूर्ण अन्यथा अणु
		wil_err(wil, "Unknown event type\n");
		prपूर्णांक_hex_dump(KERN_ERR, "evt?? ", DUMP_PREFIX_OFFSET, 16, 1,
			       hdr, माप(*hdr) + len, true);
	पूर्ण
पूर्ण

/*
 * Retrieve next WMI event from the pending list
 */
अटल काष्ठा list_head *next_wmi_ev(काष्ठा wil6210_priv *wil)
अणु
	uदीर्घ flags;
	काष्ठा list_head *ret = शून्य;

	spin_lock_irqsave(&wil->wmi_ev_lock, flags);

	अगर (!list_empty(&wil->pending_wmi_ev)) अणु
		ret = wil->pending_wmi_ev.next;
		list_del(ret);
	पूर्ण

	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);

	वापस ret;
पूर्ण

/*
 * Handler क्रम the WMI events
 */
व्योम wmi_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil6210_priv *wil = container_of(work, काष्ठा wil6210_priv,
						 wmi_event_worker);
	काष्ठा pending_wmi_event *evt;
	काष्ठा list_head *lh;

	wil_dbg_wmi(wil, "event_worker: Start\n");
	जबतक ((lh = next_wmi_ev(wil)) != शून्य) अणु
		evt = list_entry(lh, काष्ठा pending_wmi_event, list);
		wmi_event_handle(wil, &evt->event.hdr);
		kमुक्त(evt);
	पूर्ण
	wil_dbg_wmi(wil, "event_worker: Finished\n");
पूर्ण

bool wil_is_wmi_idle(काष्ठा wil6210_priv *wil)
अणु
	uदीर्घ flags;
	काष्ठा wil6210_mbox_ring *r = &wil->mbox_ctl.rx;
	bool rc = false;

	spin_lock_irqsave(&wil->wmi_ev_lock, flags);

	/* Check अगर there are pending WMI events in the events queue */
	अगर (!list_empty(&wil->pending_wmi_ev)) अणु
		wil_dbg_pm(wil, "Pending WMI events in queue\n");
		जाओ out;
	पूर्ण

	/* Check अगर there is a pending WMI call */
	अगर (wil->reply_id) अणु
		wil_dbg_pm(wil, "Pending WMI call\n");
		जाओ out;
	पूर्ण

	/* Check अगर there are pending RX events in mbox */
	r->head = wil_r(wil, RGF_MBOX +
			दुरत्व(काष्ठा wil6210_mbox_ctl, rx.head));
	अगर (r->tail != r->head)
		wil_dbg_pm(wil, "Pending WMI mbox events\n");
	अन्यथा
		rc = true;

out:
	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);
	वापस rc;
पूर्ण

अटल व्योम
wmi_sched_scan_set_ssids(काष्ठा wil6210_priv *wil,
			 काष्ठा wmi_start_sched_scan_cmd *cmd,
			 काष्ठा cfg80211_ssid *ssids, पूर्णांक n_ssids,
			 काष्ठा cfg80211_match_set *match_sets,
			 पूर्णांक n_match_sets)
अणु
	पूर्णांक i;

	अगर (n_match_sets > WMI_MAX_PNO_SSID_NUM) अणु
		wil_dbg_wmi(wil, "too many match sets (%d), use first %d\n",
			    n_match_sets, WMI_MAX_PNO_SSID_NUM);
		n_match_sets = WMI_MAX_PNO_SSID_NUM;
	पूर्ण
	cmd->num_of_ssids = n_match_sets;

	क्रम (i = 0; i < n_match_sets; i++) अणु
		काष्ठा wmi_sched_scan_ssid_match *wmi_match =
			&cmd->ssid_क्रम_match[i];
		काष्ठा cfg80211_match_set *cfg_match = &match_sets[i];
		पूर्णांक j;

		wmi_match->ssid_len = cfg_match->ssid.ssid_len;
		स_नकल(wmi_match->ssid, cfg_match->ssid.ssid,
		       min_t(u8, wmi_match->ssid_len, WMI_MAX_SSID_LEN));
		wmi_match->rssi_threshold = S8_MIN;
		अगर (cfg_match->rssi_thold >= S8_MIN &&
		    cfg_match->rssi_thold <= S8_MAX)
			wmi_match->rssi_threshold = cfg_match->rssi_thold;

		क्रम (j = 0; j < n_ssids; j++)
			अगर (wmi_match->ssid_len == ssids[j].ssid_len &&
			    स_भेद(wmi_match->ssid, ssids[j].ssid,
				   wmi_match->ssid_len) == 0)
				wmi_match->add_ssid_to_probe = true;
	पूर्ण
पूर्ण

अटल व्योम
wmi_sched_scan_set_channels(काष्ठा wil6210_priv *wil,
			    काष्ठा wmi_start_sched_scan_cmd *cmd,
			    u32 n_channels,
			    काष्ठा ieee80211_channel **channels)
अणु
	पूर्णांक i;

	अगर (n_channels > WMI_MAX_CHANNEL_NUM) अणु
		wil_dbg_wmi(wil, "too many channels (%d), use first %d\n",
			    n_channels, WMI_MAX_CHANNEL_NUM);
		n_channels = WMI_MAX_CHANNEL_NUM;
	पूर्ण
	cmd->num_of_channels = n_channels;

	क्रम (i = 0; i < n_channels; i++) अणु
		काष्ठा ieee80211_channel *cfg_chan = channels[i];

		cmd->channel_list[i] = cfg_chan->hw_value - 1;
	पूर्ण
पूर्ण

अटल व्योम
wmi_sched_scan_set_plans(काष्ठा wil6210_priv *wil,
			 काष्ठा wmi_start_sched_scan_cmd *cmd,
			 काष्ठा cfg80211_sched_scan_plan *scan_plans,
			 पूर्णांक n_scan_plans)
अणु
	पूर्णांक i;

	अगर (n_scan_plans > WMI_MAX_PLANS_NUM) अणु
		wil_dbg_wmi(wil, "too many plans (%d), use first %d\n",
			    n_scan_plans, WMI_MAX_PLANS_NUM);
		n_scan_plans = WMI_MAX_PLANS_NUM;
	पूर्ण

	क्रम (i = 0; i < n_scan_plans; i++) अणु
		काष्ठा cfg80211_sched_scan_plan *cfg_plan = &scan_plans[i];

		cmd->scan_plans[i].पूर्णांकerval_sec =
			cpu_to_le16(cfg_plan->पूर्णांकerval);
		cmd->scan_plans[i].num_of_iterations =
			cpu_to_le16(cfg_plan->iterations);
	पूर्ण
पूर्ण

पूर्णांक wmi_start_sched_scan(काष्ठा wil6210_priv *wil,
			 काष्ठा cfg80211_sched_scan_request *request)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा wmi_start_sched_scan_cmd cmd = अणु
		.min_rssi_threshold = S8_MIN,
		.initial_delay_sec = cpu_to_le16(request->delay),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_start_sched_scan_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.result = WMI_PNO_REJECTपूर्ण,
	पूर्ण;

	अगर (!test_bit(WMI_FW_CAPABILITY_PNO, wil->fw_capabilities))
		वापस -ENOTSUPP;

	अगर (request->min_rssi_thold >= S8_MIN &&
	    request->min_rssi_thold <= S8_MAX)
		cmd.min_rssi_threshold = request->min_rssi_thold;

	wmi_sched_scan_set_ssids(wil, &cmd, request->ssids, request->n_ssids,
				 request->match_sets, request->n_match_sets);
	wmi_sched_scan_set_channels(wil, &cmd,
				    request->n_channels, request->channels);
	wmi_sched_scan_set_plans(wil, &cmd,
				 request->scan_plans, request->n_scan_plans);

	rc = wmi_call(wil, WMI_START_SCHED_SCAN_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_START_SCHED_SCAN_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.result != WMI_PNO_SUCCESS) अणु
		wil_err(wil, "start sched scan failed, result %d\n",
			reply.evt.result);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wmi_stop_sched_scan(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_stop_sched_scan_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.result = WMI_PNO_REJECTपूर्ण,
	पूर्ण;

	अगर (!test_bit(WMI_FW_CAPABILITY_PNO, wil->fw_capabilities))
		वापस -ENOTSUPP;

	rc = wmi_call(wil, WMI_STOP_SCHED_SCAN_CMDID, vअगर->mid, शून्य, 0,
		      WMI_STOP_SCHED_SCAN_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	अगर (reply.evt.result != WMI_PNO_SUCCESS) अणु
		wil_err(wil, "stop sched scan failed, result %d\n",
			reply.evt.result);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wmi_mgmt_tx(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *buf, माप_प्रकार len)
अणु
	माप_प्रकार total;
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा ieee80211_mgmt *mgmt_frame = (व्योम *)buf;
	काष्ठा wmi_sw_tx_req_cmd *cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_sw_tx_complete_event evt;
	पूर्ण __packed evt = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	पूर्णांक rc;

	wil_dbg_misc(wil, "mgmt_tx mid %d\n", vअगर->mid);
	wil_hex_dump_misc("mgmt tx frame ", DUMP_PREFIX_OFFSET, 16, 1, buf,
			  len, true);

	अगर (len < माप(काष्ठा ieee80211_hdr_3addr))
		वापस -EINVAL;

	total = माप(*cmd) + len;
	अगर (total < len) अणु
		wil_err(wil, "mgmt_tx invalid len %zu\n", len);
		वापस -EINVAL;
	पूर्ण

	cmd = kदो_स्मृति(total, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_नकल(cmd->dst_mac, mgmt_frame->da, WMI_MAC_LEN);
	cmd->len = cpu_to_le16(len);
	स_नकल(cmd->payload, buf, len);

	rc = wmi_call(wil, WMI_SW_TX_REQ_CMDID, vअगर->mid, cmd, total,
		      WMI_SW_TX_COMPLETE_EVENTID, &evt, माप(evt), 2000);
	अगर (!rc && evt.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_dbg_wmi(wil, "mgmt_tx failed with status %d\n",
			    evt.evt.status);
		rc = -EAGAIN;
	पूर्ण

	kमुक्त(cmd);

	वापस rc;
पूर्ण

पूर्णांक wmi_mgmt_tx_ext(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *buf, माप_प्रकार len,
		    u8 channel, u16 duration_ms)
अणु
	माप_प्रकार total;
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा ieee80211_mgmt *mgmt_frame = (व्योम *)buf;
	काष्ठा wmi_sw_tx_req_ext_cmd *cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_sw_tx_complete_event evt;
	पूर्ण __packed evt = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	पूर्णांक rc;

	wil_dbg_wmi(wil, "mgmt_tx_ext mid %d channel %d duration %d\n",
		    vअगर->mid, channel, duration_ms);
	wil_hex_dump_wmi("mgmt_tx_ext frame ", DUMP_PREFIX_OFFSET, 16, 1, buf,
			 len, true);

	अगर (len < माप(काष्ठा ieee80211_hdr_3addr)) अणु
		wil_err(wil, "short frame. len %zu\n", len);
		वापस -EINVAL;
	पूर्ण

	total = माप(*cmd) + len;
	अगर (total < len) अणु
		wil_err(wil, "mgmt_tx_ext invalid len %zu\n", len);
		वापस -EINVAL;
	पूर्ण

	cmd = kzalloc(total, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_नकल(cmd->dst_mac, mgmt_frame->da, WMI_MAC_LEN);
	cmd->len = cpu_to_le16(len);
	स_नकल(cmd->payload, buf, len);
	cmd->channel = channel - 1;
	cmd->duration_ms = cpu_to_le16(duration_ms);

	rc = wmi_call(wil, WMI_SW_TX_REQ_EXT_CMDID, vअगर->mid, cmd, total,
		      WMI_SW_TX_COMPLETE_EVENTID, &evt, माप(evt), 2000);
	अगर (!rc && evt.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_dbg_wmi(wil, "mgmt_tx_ext failed with status %d\n",
			    evt.evt.status);
		rc = -EAGAIN;
	पूर्ण

	kमुक्त(cmd);

	वापस rc;
पूर्ण

पूर्णांक wil_wmi_tx_sring_cfg(काष्ठा wil6210_priv *wil, पूर्णांक ring_id)
अणु
	पूर्णांक rc;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wil_status_ring *sring = &wil->srings[ring_id];
	काष्ठा wmi_tx_status_ring_add_cmd cmd = अणु
		.ring_cfg = अणु
			.ring_size = cpu_to_le16(sring->size),
		पूर्ण,
		.irq_index = WIL_TX_STATUS_IRQ_IDX
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_tx_status_ring_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	cmd.ring_cfg.ring_id = ring_id;

	cmd.ring_cfg.ring_mem_base = cpu_to_le64(sring->pa);
	rc = wmi_call(wil, WMI_TX_STATUS_RING_ADD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_TX_STATUS_RING_CFG_DONE_EVENTID,
		      &reply, माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "TX_STATUS_RING_ADD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "TX_STATUS_RING_ADD_CMD failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	sring->hwtail = le32_to_cpu(reply.evt.ring_tail_ptr);

	वापस 0;
पूर्ण

पूर्णांक wil_wmi_cfg_def_rx_offload(काष्ठा wil6210_priv *wil, u16 max_rx_pl_per_desc)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	पूर्णांक rc;
	काष्ठा wmi_cfg_def_rx_offload_cmd cmd = अणु
		.max_msdu_size = cpu_to_le16(wil_mtu2macbuf(WIL_MAX_ETH_MTU)),
		.max_rx_pl_per_desc = cpu_to_le16(max_rx_pl_per_desc),
		.decap_trans_type = WMI_DECAP_TYPE_802_3,
		.l2_802_3_offload_ctrl = 0,
		.l3_l4_ctrl = 1 << L3_L4_CTRL_TCPIP_CHECKSUM_EN_POS,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_cfg_def_rx_offload_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	rc = wmi_call(wil, WMI_CFG_DEF_RX_OFFLOAD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_CFG_DEF_RX_OFFLOAD_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_CFG_DEF_RX_OFFLOAD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_CFG_DEF_RX_OFFLOAD_CMD failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wil_wmi_rx_sring_add(काष्ठा wil6210_priv *wil, u16 ring_id)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil_status_ring *sring = &wil->srings[ring_id];
	पूर्णांक rc;
	काष्ठा wmi_rx_status_ring_add_cmd cmd = अणु
		.ring_cfg = अणु
			.ring_size = cpu_to_le16(sring->size),
			.ring_id = ring_id,
		पूर्ण,
		.rx_msg_type = wil->use_compressed_rx_status ?
			WMI_RX_MSG_TYPE_COMPRESSED :
			WMI_RX_MSG_TYPE_EXTENDED,
		.irq_index = WIL_RX_STATUS_IRQ_IDX,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_rx_status_ring_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	cmd.ring_cfg.ring_mem_base = cpu_to_le64(sring->pa);
	rc = wmi_call(wil, WMI_RX_STATUS_RING_ADD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_RX_STATUS_RING_CFG_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "RX_STATUS_RING_ADD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "RX_STATUS_RING_ADD_CMD failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	sring->hwtail = le32_to_cpu(reply.evt.ring_tail_ptr);

	वापस 0;
पूर्ण

पूर्णांक wil_wmi_rx_desc_ring_add(काष्ठा wil6210_priv *wil, पूर्णांक status_ring_id)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil_ring *ring = &wil->ring_rx;
	पूर्णांक rc;
	काष्ठा wmi_rx_desc_ring_add_cmd cmd = अणु
		.ring_cfg = अणु
			.ring_size = cpu_to_le16(ring->size),
			.ring_id = WIL_RX_DESC_RING_ID,
		पूर्ण,
		.status_ring_id = status_ring_id,
		.irq_index = WIL_RX_STATUS_IRQ_IDX,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_rx_desc_ring_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	cmd.ring_cfg.ring_mem_base = cpu_to_le64(ring->pa);
	cmd.sw_tail_host_addr = cpu_to_le64(ring->edma_rx_swtail.pa);
	rc = wmi_call(wil, WMI_RX_DESC_RING_ADD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_RX_DESC_RING_CFG_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_RX_DESC_RING_ADD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_RX_DESC_RING_ADD_CMD failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	ring->hwtail = le32_to_cpu(reply.evt.ring_tail_ptr);

	वापस 0;
पूर्ण

पूर्णांक wil_wmi_tx_desc_ring_add(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id, पूर्णांक cid,
			     पूर्णांक tid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक sring_id = wil->tx_sring_idx; /* there is only one TX sring */
	पूर्णांक rc;
	काष्ठा wil_ring *ring = &wil->ring_tx[ring_id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];
	काष्ठा wmi_tx_desc_ring_add_cmd cmd = अणु
		.ring_cfg = अणु
			.ring_size = cpu_to_le16(ring->size),
			.ring_id = ring_id,
		पूर्ण,
		.status_ring_id = sring_id,
		.cid = cid,
		.tid = tid,
		.encap_trans_type = WMI_VRING_ENC_TYPE_802_3,
		.max_msdu_size = cpu_to_le16(wil_mtu2macbuf(mtu_max)),
		.schd_params = अणु
			.priority = cpu_to_le16(0),
			.बारlot_us = cpu_to_le16(0xfff),
		पूर्ण
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_tx_desc_ring_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	cmd.ring_cfg.ring_mem_base = cpu_to_le64(ring->pa);
	rc = wmi_call(wil, WMI_TX_DESC_RING_ADD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_TX_DESC_RING_CFG_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_TX_DESC_RING_ADD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_TX_DESC_RING_ADD_CMD failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&txdata->lock);
	ring->hwtail = le32_to_cpu(reply.evt.ring_tail_ptr);
	txdata->mid = vअगर->mid;
	txdata->enabled = 1;
	spin_unlock_bh(&txdata->lock);

	वापस 0;
पूर्ण

पूर्णांक wil_wmi_bcast_desc_ring_add(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wil_ring *ring = &wil->ring_tx[ring_id];
	पूर्णांक rc;
	काष्ठा wmi_bcast_desc_ring_add_cmd cmd = अणु
		.ring_cfg = अणु
			.ring_size = cpu_to_le16(ring->size),
			.ring_id = ring_id,
		पूर्ण,
		.max_msdu_size = cpu_to_le16(wil_mtu2macbuf(mtu_max)),
		.status_ring_id = wil->tx_sring_idx,
		.encap_trans_type = WMI_VRING_ENC_TYPE_802_3,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_rx_desc_ring_cfg_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];

	cmd.ring_cfg.ring_mem_base = cpu_to_le64(ring->pa);
	rc = wmi_call(wil, WMI_BCAST_DESC_RING_ADD_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_TX_DESC_RING_CFG_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_BCAST_DESC_RING_ADD_CMD failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "Broadcast Tx config failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&txdata->lock);
	ring->hwtail = le32_to_cpu(reply.evt.ring_tail_ptr);
	txdata->mid = vअगर->mid;
	txdata->enabled = 1;
	spin_unlock_bh(&txdata->lock);

	वापस 0;
पूर्ण

पूर्णांक wmi_link_stats_cfg(काष्ठा wil6210_vअगर *vअगर, u32 type, u8 cid, u32 पूर्णांकerval)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_link_stats_cmd cmd = अणु
		.record_type_mask = cpu_to_le32(type),
		.cid = cid,
		.action = WMI_LINK_STATS_SNAPSHOT,
		.पूर्णांकerval_msec = cpu_to_le32(पूर्णांकerval),
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_link_stats_config_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	पूर्णांक rc;

	rc = wmi_call(wil, WMI_LINK_STATS_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_LINK_STATS_CONFIG_DONE_EVENTID, &reply,
		      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_LINK_STATS_CMDID failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "Link statistics config failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wmi_set_cqm_rssi_config(काष्ठा wil6210_priv *wil,
			    s32 rssi_thold, u32 rssi_hyst)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_set_link_monitor_cmd cmd;
		s8 rssi_thold;
	पूर्ण __packed cmd = अणु
		.cmd = अणु
			.rssi_hyst = rssi_hyst,
			.rssi_thresholds_list_size = 1,
		पूर्ण,
		.rssi_thold = rssi_thold,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr hdr;
		काष्ठा wmi_set_link_monitor_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;

	अगर (rssi_thold > S8_MAX || rssi_thold < S8_MIN || rssi_hyst > U8_MAX)
		वापस -EINVAL;

	rc = wmi_call(wil, WMI_SET_LINK_MONITOR_CMDID, vअगर->mid, &cmd,
		      माप(cmd), WMI_SET_LINK_MONITOR_EVENTID,
		      &reply, माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "WMI_SET_LINK_MONITOR_CMDID failed, rc %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (reply.evt.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "WMI_SET_LINK_MONITOR_CMDID failed, status %d\n",
			reply.evt.status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
