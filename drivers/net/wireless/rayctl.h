<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAYCTL_H_
#घोषणा _RAYCTL_H_

प्रकार अचिन्हित अक्षर UCHAR;

/****** IEEE 802.11 स्थिरants ************************************************/
#घोषणा ADDRLEN           6
/* Frame control 1 bit fields */
#घोषणा PROTOCOL_VER      0x00
#घोषणा DATA_TYPE         0x08
#घोषणा ASSOC_REQ_TYPE    0x00
#घोषणा ASSOC_RESP_TYPE   0x10
#घोषणा REASSOC_REQ_TYPE  0x20
#घोषणा REASSOC_RESP_TYPE 0x30
#घोषणा शून्य_MSG_TYPE     0x48
#घोषणा BEACON_TYPE       0x80
#घोषणा DISASSOC_TYPE     0xA0
#घोषणा PSPOLL_TYPE       0xA4
#घोषणा AUTHENTIC_TYPE    0xB0
#घोषणा DEAUTHENTIC_TYPE  0xC0
/* Frame control 2 bit fields */
#घोषणा FC2_TO_DS         0x01
#घोषणा FC2_FROM_DS       0x02
#घोषणा FC2_MORE_FRAG     0x04
#घोषणा FC2_RETRY         0x08
#घोषणा FC2_PSM           0x10
#घोषणा FC2_MORE_DATA     0x20
#घोषणा FC2_WEP           0x40
#घोषणा FC2_ORDER         0x80
/*****************************************************************************/
/* 802.11 element ID's and lengths */
#घोषणा C_BP_CAPABILITY_ESS             0x01
#घोषणा C_BP_CAPABILITY_IBSS            0x02
#घोषणा C_BP_CAPABILITY_CF_POLLABLE     0x04
#घोषणा C_BP_CAPABILITY_CF_POLL_REQUEST 0x08
#घोषणा C_BP_CAPABILITY_PRIVACY         0x10

#घोषणा C_ESSID_ELEMENT_ID               0
#घोषणा C_ESSID_ELEMENT_MAX_LENGTH       32

#घोषणा C_SUPPORTED_RATES_ELEMENT_ID     1
#घोषणा C_SUPPORTED_RATES_ELEMENT_LENGTH 2

#घोषणा C_FH_PARAM_SET_ELEMENT_ID        2
#घोषणा C_FH_PARAM_SET_ELEMENT_LNGTH     5

#घोषणा C_CF_PARAM_SET_ELEMENT_ID        4
#घोषणा C_CF_PARAM_SET_ELEMENT_LNGTH     6

#घोषणा C_TIM_ELEMENT_ID                 5
#घोषणा C_TIM_BITMAP_LENGTH            251
#घोषणा C_TIM_BMCAST_BIT              0x01

#घोषणा C_IBSS_ELEMENT_ID                6
#घोषणा C_IBSS_ELEMENT_LENGTH            2

#घोषणा C_JAPAN_CALL_SIGN_ELEMENT_ID    51
#घोषणा C_JAPAN_CALL_SIGN_ELEMENT_LNGTH 12

#घोषणा C_DISASSOC_REASON_CODE_LEN       2
#घोषणा C_DISASSOC_REASON_CODE_DEFAULT   8

#घोषणा C_CRC_LEN                        4
#घोषणा C_NUM_SUPPORTED_RATES            8 
/****** IEEE 802.11 mac header क्रम type data packets *************************/
काष्ठा mac_header अणु
  UCHAR frame_ctl_1;                          
  UCHAR frame_ctl_2;
  UCHAR duration_lsb;
  UCHAR duration_msb;
  UCHAR addr_1[ADDRLEN];
  UCHAR addr_2[ADDRLEN];
  UCHAR addr_3[ADDRLEN];
  UCHAR seq_frag_num[2];
/*  UCHAR addr_4[ADDRLEN]; *//* only present क्रम AP to AP (TO DS and FROM DS */
पूर्ण;
/****** IEEE 802.11 frame element काष्ठाures *********************************/
काष्ठा essid_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR text[C_ESSID_ELEMENT_MAX_LENGTH];
पूर्ण;
काष्ठा rates_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR value[8];
पूर्ण;
काष्ठा freq_hop_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR dwell_समय[2];
  UCHAR hop_set;
  UCHAR hop_pattern;
  UCHAR hop_index;
पूर्ण;
काष्ठा tim_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR dtim_count;
  UCHAR dtim_period;    
  UCHAR biपंचांगap_control;
  UCHAR tim[C_TIM_BITMAP_LENGTH];
पूर्ण;
काष्ठा ibss_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR atim_winकरोw[2];
पूर्ण;
काष्ठा japan_call_sign_element
अणु
  UCHAR id;
  UCHAR length;
  UCHAR call_sign[12];
पूर्ण;
/****** Beacon message काष्ठाures ********************************************/
/* .elements is a large lump of max size because elements are variable size  */
काष्ठा infra_beacon
अणु
    UCHAR बारtamp[8];
    UCHAR beacon_पूर्णांकvl[2];
    UCHAR capability[2];
    UCHAR elements[माप(काष्ठा essid_element) 
                  + माप(काष्ठा rates_element)
                  + माप(काष्ठा freq_hop_element) 
                  + माप(काष्ठा japan_call_sign_element)
                  + माप(काष्ठा tim_element)];
पूर्ण;
काष्ठा adhoc_beacon
अणु
    UCHAR बारtamp[8];
    UCHAR beacon_पूर्णांकvl[2];
    UCHAR capability[2];
    UCHAR elements[माप(काष्ठा essid_element) 
                  + माप(काष्ठा rates_element)
                  + माप(काष्ठा freq_hop_element) 
                  + माप(काष्ठा japan_call_sign_element)
                  + माप(काष्ठा ibss_element)];
पूर्ण;
/*****************************************************************************/
/*****************************************************************************/
/* #घोषणा C_MAC_HDR_2_WEP 0x40 */
/* TX/RX CCS स्थिरants */
#घोषणा TX_HEADER_LENGTH 0x1C
#घोषणा RX_MAC_HEADER_LENGTH 0x18
#घोषणा TX_AUTHENTICATE_LENGTH (TX_HEADER_LENGTH + 6)
#घोषणा TX_AUTHENTICATE_LENGTH_MSB (TX_AUTHENTICATE_LENGTH >> 8)
#घोषणा TX_AUTHENTICATE_LENGTH_LSB (TX_AUTHENTICATE_LENGTH & 0xff)
#घोषणा TX_DEAUTHENTICATE_LENGTH (TX_HEADER_LENGTH + 2)
#घोषणा TX_DEAUTHENTICATE_LENGTH_MSB (TX_AUTHENTICATE_LENGTH >> 8)
#घोषणा TX_DEAUTHENTICATE_LENGTH_LSB (TX_AUTHENTICATE_LENGTH & 0xff)
#घोषणा FCS_LEN           4

#घोषणा ADHOC                 0
#घोषणा INFRA                 1

#घोषणा TYPE_STA              0
#घोषणा TYPE_AP               1

#घोषणा PASSIVE_SCAN          1
#घोषणा ACTIVE_SCAN           1

#घोषणा PSM_CAM               0

/* Country codes */
#घोषणा USA                   1
#घोषणा EUROPE                2
#घोषणा JAPAN                 3
#घोषणा KOREA                 4
#घोषणा SPAIN                 5
#घोषणा FRANCE                6
#घोषणा ISRAEL                7
#घोषणा AUSTRALIA             8
#घोषणा JAPAN_TEST            9

/* Hop pattern lengths */
#घोषणा USA_HOP_MOD          79 
#घोषणा EUROPE_HOP_MOD       79 
#घोषणा JAPAN_HOP_MOD        23
#घोषणा KOREA_HOP_MOD        23
#घोषणा SPAIN_HOP_MOD        27
#घोषणा FRANCE_HOP_MOD       35
#घोषणा ISRAEL_HOP_MOD       35
#घोषणा AUSTRALIA_HOP_MOD    47
#घोषणा JAPAN_TEST_HOP_MOD   23

#घोषणा ESSID_SIZE           32
/**********************************************************************/
/* CIS Register Constants */
#घोषणा CIS_OFFSET             0x0f00
/* Configuration Option Register (0x0F00) */
#घोषणा COR_OFFSET             0x00
#घोषणा COR_SOFT_RESET         0x80
#घोषणा COR_LEVEL_IRQ          0x40
#घोषणा COR_CONFIG_NUM         0x01
#घोषणा COR_DEFAULT            (COR_LEVEL_IRQ | COR_CONFIG_NUM)

/* Card Configuration and Status Register (0x0F01) */
#घोषणा CCSR_OFFSET            0x01
#घोषणा CCSR_HOST_INTR_PENDING 0x01
#घोषणा CCSR_POWER_DOWN        0x04

/* HCS Interrupt Register (0x0F05) */
#घोषणा HCS_INTR_OFFSET        0x05
/* #घोषणा HCS_INTR_OFFSET        0x0A */
#घोषणा HCS_INTR_CLEAR         0x00

/* ECF Interrupt Register (0x0F06) */
#घोषणा ECF_INTR_OFFSET        0x06
/* #घोषणा ECF_INTR_OFFSET        0x0C */
#घोषणा ECF_INTR_SET           0x01

/* Authorization Register 0 (0x0F08) */
#घोषणा AUTH_0_ON              0x57

/* Authorization Register 1 (0x0F09) */
#घोषणा AUTH_1_ON              0x82

/* Program Mode Register (0x0F0A) */
#घोषणा PC2PM                  0x02
#घोषणा PC2CAL                 0x10
#घोषणा PC2MLSE                0x20

/* PC Test Mode Register (0x0F0B) */
#घोषणा PC_TEST_MODE           0x08

/* Frequency Control Word (0x0F10) */
/* Range 0x02 - 0xA6 */

/* Test Mode Control 1-4 (0x0F14 - 0x0F17) */

/**********************************************************************/

/* Shared RAM Area */
#घोषणा SCB_BASE               0x0000
#घोषणा STATUS_BASE            0x0100
#घोषणा HOST_TO_ECF_BASE       0x0200
#घोषणा ECF_TO_HOST_BASE       0x0300
#घोषणा CCS_BASE               0x0400
#घोषणा RCS_BASE               0x0800
#घोषणा INFRA_TIM_BASE         0x0C00
#घोषणा SSID_LIST_BASE         0x0D00
#घोषणा TX_BUF_BASE            0x1000
#घोषणा RX_BUF_BASE            0x8000

#घोषणा NUMBER_OF_CCS    64
#घोषणा NUMBER_OF_RCS    64
/*#घोषणा NUMBER_OF_TX_CCS 14 */
#घोषणा NUMBER_OF_TX_CCS 14

#घोषणा TX_BUF_SIZE      (2048 - माप(काष्ठा tx_msg))
#घोषणा RX_BUFF_END      0x3FFF
/* Values क्रम buffer_status */
#घोषणा CCS_BUFFER_FREE       0
#घोषणा CCS_BUFFER_BUSY       1
#घोषणा CCS_COMMAND_COMPLETE  2
#घोषणा CCS_COMMAND_FAILED    3

/* Values क्रम cmd */
#घोषणा CCS_DOWNLOAD_STARTUP_PARAMS    1
#घोषणा CCS_UPDATE_PARAMS              2
#घोषणा CCS_REPORT_PARAMS              3
#घोषणा CCS_UPDATE_MULTICAST_LIST      4
#घोषणा CCS_UPDATE_POWER_SAVINGS_MODE  5
#घोषणा CCS_START_NETWORK              6
#घोषणा CCS_JOIN_NETWORK               7
#घोषणा CCS_START_ASSOCIATION          8
#घोषणा CCS_TX_REQUEST                 9
#घोषणा CCS_TEST_MEMORY              0xa
#घोषणा CCS_SHUTDOWN                 0xb
#घोषणा CCS_DUMP_MEMORY              0xc
#घोषणा CCS_START_TIMER              0xe
#घोषणा CCS_LAST_CMD                 CCS_START_TIMER

/* Values क्रम link field */
#घोषणा CCS_END_LIST                 0xff

/* values क्रम buffer_status field */
#घोषणा RCS_BUFFER_FREE       0
#घोषणा RCS_BUFFER_BUSY       1
#घोषणा RCS_COMPLETE          2
#घोषणा RCS_FAILED            3
#घोषणा RCS_BUFFER_RELEASE    0xFF

/* values क्रम पूर्णांकerrupt_id field */
#घोषणा PROCESS_RX_PACKET           0x80 /* */
#घोषणा REJOIN_NET_COMPLETE         0x81 /* RCS ID: Rejoin Net Complete */
#घोषणा ROAMING_INITIATED           0x82 /* RCS ID: Roaming Initiated   */
#घोषणा JAPAN_CALL_SIGN_RXD         0x83 /* RCS ID: New Japan Call Sign */

/*****************************************************************************/
/* Memory types क्रम dump memory command */
#घोषणा C_MEM_PROG  0
#घोषणा C_MEM_XDATA 1
#घोषणा C_MEM_SFR   2
#घोषणा C_MEM_IDATA 3

/*** Return values क्रम hw_xmit **********/
#घोषणा XMIT_OK        (0)
#घोषणा XMIT_MSG_BAD   (-1)
#घोषणा XMIT_NO_CCS    (-2)
#घोषणा XMIT_NO_INTR   (-3)
#घोषणा XMIT_NEED_AUTH (-4)

/*** Values क्रम card status */
#घोषणा CARD_INSERTED       (0)

#घोषणा CARD_AWAITING_PARAM (1)
#घोषणा CARD_INIT_ERROR     (11)

#घोषणा CARD_DL_PARAM       (2)
#घोषणा CARD_DL_PARAM_ERROR (12)

#घोषणा CARD_DOING_ACQ      (3)

#घोषणा CARD_ACQ_COMPLETE   (4)
#घोषणा CARD_ACQ_FAILED     (14)

#घोषणा CARD_AUTH_COMPLETE  (5)
#घोषणा CARD_AUTH_REFUSED   (15)

#घोषणा CARD_ASSOC_COMPLETE (6)
#घोषणा CARD_ASSOC_FAILED   (16)

/*** Values क्रम authentication_state ***********************************/
#घोषणा UNAUTHENTICATED     (0)
#घोषणा AWAITING_RESPONSE   (1)
#घोषणा AUTHENTICATED       (2)
#घोषणा NEED_TO_AUTH        (3)

/*** Values क्रम authentication type ************************************/
#घोषणा OPEN_AUTH_REQUEST   (1)
#घोषणा OPEN_AUTH_RESPONSE  (2)
#घोषणा BROADCAST_DEAUTH    (0xc0)
/*** Values क्रम समयr functions ****************************************/
#घोषणा TODO_NOTHING              (0)
#घोषणा TODO_VERIFY_DL_START      (-1)
#घोषणा TODO_START_NET            (-2)
#घोषणा TODO_JOIN_NET             (-3)
#घोषणा TODO_AUTHENTICATE_TIMEOUT (-4)
#घोषणा TODO_SEND_CCS             (-5)
/***********************************************************************/
/* Parameter passing काष्ठाure क्रम update/report parameter CCS's */
काष्ठा object_id अणु
    व्योम          *object_addr;
    अचिन्हित अक्षर object_length;
पूर्ण;

#घोषणा OBJID_network_type            0
#घोषणा OBJID_acting_as_ap_status     1
#घोषणा OBJID_current_ess_id          2
#घोषणा OBJID_scanning_mode           3
#घोषणा OBJID_घातer_mgt_state         4
#घोषणा OBJID_mac_address             5
#घोषणा OBJID_frag_threshold          6
#घोषणा OBJID_hop_समय                7
#घोषणा OBJID_beacon_period           8
#घोषणा OBJID_dtim_period             9
#घोषणा OBJID_retry_max              10
#घोषणा OBJID_ack_समयout            11
#घोषणा OBJID_sअगरs                   12
#घोषणा OBJID_dअगरs                   13
#घोषणा OBJID_pअगरs                   14
#घोषणा OBJID_rts_threshold          15
#घोषणा OBJID_scan_dwell_समय        16
#घोषणा OBJID_max_scan_dwell_समय    17
#घोषणा OBJID_assoc_resp_समयout     18
#घोषणा OBJID_adhoc_scan_cycle_max   19
#घोषणा OBJID_infra_scan_cycle_max   20
#घोषणा OBJID_infra_super_cycle_max  21
#घोषणा OBJID_promiscuous_mode       22
#घोषणा OBJID_unique_word            23
#घोषणा OBJID_slot_समय              24
#घोषणा OBJID_roaming_low_snr        25
#घोषणा OBJID_low_snr_count_thresh   26
#घोषणा OBJID_infra_missed_bcn       27
#घोषणा OBJID_adhoc_missed_bcn       28
#घोषणा OBJID_curr_country_code      29
#घोषणा OBJID_hop_pattern            30
#घोषणा OBJID_reserved               31
#घोषणा OBJID_cw_max_msb             32
#घोषणा OBJID_cw_min_msb             33
#घोषणा OBJID_noise_filter_gain      34
#घोषणा OBJID_noise_limit_offset     35
#घोषणा OBJID_det_rssi_thresh_offset 36
#घोषणा OBJID_med_busy_thresh_offset 37
#घोषणा OBJID_det_sync_thresh        38
#घोषणा OBJID_test_mode              39
#घोषणा OBJID_test_min_chan_num      40
#घोषणा OBJID_test_max_chan_num      41
#घोषणा OBJID_allow_bcast_ID_prbrsp  42
#घोषणा OBJID_privacy_must_start     43
#घोषणा OBJID_privacy_can_join       44
#घोषणा OBJID_basic_rate_set         45

/**** Configuration/Status/Control Area ***************************/
/*    System Control Block (SCB) Area
 *    Located at Shared RAM offset 0
 */
काष्ठा scb अणु
    UCHAR ccs_index;
    UCHAR rcs_index;
पूर्ण;

/****** Status area at Shared RAM offset 0x0100 ******************************/
काष्ठा status अणु
    UCHAR mrx_overflow_क्रम_host;         /* 0=ECF may ग_लिखो, 1=host may ग_लिखो*/
    UCHAR mrx_checksum_error_क्रम_host;   /* 0=ECF may ग_लिखो, 1=host may ग_लिखो*/
    UCHAR rx_hec_error_क्रम_host;         /* 0=ECF may ग_लिखो, 1=host may ग_लिखो*/
    UCHAR reserved1;
    लघु mrx_overflow;                  /* ECF increments on rx overflow    */
    लघु mrx_checksum_error;            /* ECF increments on rx CRC error   */
    लघु rx_hec_error;                  /* ECF incs on mac header CRC error */
    UCHAR rxnoise;                       /* Average RSL measurement          */
पूर्ण;

/****** Host-to-ECF Data Area at Shared RAM offset 0x200 *********************/
काष्ठा host_to_ecf_area अणु
    
पूर्ण;

/****** ECF-to-Host Data Area at Shared RAM offset 0x0300 ********************/
काष्ठा startup_res_518 अणु
    UCHAR startup_word;
    UCHAR station_addr[ADDRLEN];
    UCHAR calc_prog_chksum;
    UCHAR calc_cis_chksum;
    UCHAR ecf_spare[7];
    UCHAR japan_call_sign[12];
पूर्ण;

काष्ठा startup_res_6 अणु
    UCHAR startup_word;
    UCHAR station_addr[ADDRLEN];
    UCHAR reserved;
    UCHAR supp_rates[8];
    UCHAR japan_call_sign[12];
    UCHAR calc_prog_chksum;
    UCHAR calc_cis_chksum;
    UCHAR firmware_version[3];
    UCHAR asic_version;
    UCHAR tib_length;
पूर्ण;

काष्ठा start_join_net_params अणु
    UCHAR net_type;
    UCHAR ssid[ESSID_SIZE];
    UCHAR reserved;
    UCHAR privacy_can_join;
पूर्ण;

/****** Command Control Structure area at Shared ram offset 0x0400 ***********/
/* Structures क्रम command specअगरic parameters (ccs.var) */
काष्ठा update_param_cmd अणु
    UCHAR object_id;
    UCHAR number_objects;
    UCHAR failure_cause;
पूर्ण;
काष्ठा report_param_cmd अणु
    UCHAR object_id;
    UCHAR number_objects;
    UCHAR failure_cause;
    UCHAR length;
पूर्ण;
काष्ठा start_network_cmd अणु
    UCHAR update_param;
    UCHAR bssid[ADDRLEN];
    UCHAR net_initiated;
    UCHAR net_शेष_tx_rate;
    UCHAR encryption;
पूर्ण;
काष्ठा join_network_cmd अणु
    UCHAR update_param;
    UCHAR bssid[ADDRLEN];
    UCHAR net_initiated;
    UCHAR net_शेष_tx_rate;
    UCHAR encryption;
पूर्ण;
काष्ठा tx_requested_cmd अणु
 
    UCHAR tx_data_ptr[2];
    UCHAR tx_data_length[2];
    UCHAR host_reserved[2];
    UCHAR reserved[3];
    UCHAR tx_rate;
    UCHAR घात_sav_mode;
    UCHAR retries;
    UCHAR antenna;
पूर्ण;
काष्ठा tx_requested_cmd_4 अणु
 
    UCHAR tx_data_ptr[2];
    UCHAR tx_data_length[2];
    UCHAR dest_addr[ADDRLEN];
    UCHAR घात_sav_mode;
    UCHAR retries;
    UCHAR station_id;
पूर्ण;
काष्ठा memory_dump_cmd अणु
    UCHAR memory_type;
    UCHAR memory_ptr[2];
    UCHAR length;
पूर्ण;
काष्ठा update_association_cmd अणु
    UCHAR status;
    UCHAR aid[2];
पूर्ण;
काष्ठा start_समयr_cmd अणु
    UCHAR duration[2];
पूर्ण;

काष्ठा ccs अणु
    UCHAR buffer_status;                 /* 0 = buffer मुक्त, 1 = buffer busy */
                                         /* 2 = command complete, 3 = failed */
    UCHAR cmd;                           /* command to ECF                   */
    UCHAR link;                          /* link to next CCS, FF=end of list */
    /* command specअगरic parameters      */
    जोड़ अणु
        अक्षर reserved[13];
        काष्ठा update_param_cmd update_param;
        काष्ठा report_param_cmd report_param;
        UCHAR nummulticast;
        UCHAR mode;
        काष्ठा start_network_cmd start_network;
        काष्ठा join_network_cmd join_network;
        काष्ठा tx_requested_cmd tx_request;
        काष्ठा memory_dump_cmd memory_dump;
        काष्ठा update_association_cmd update_assoc;
        काष्ठा start_समयr_cmd start_समयr;
    पूर्ण var;
पूर्ण;

/*****************************************************************************/
/* Transmit buffer काष्ठाures */
काष्ठा tib_काष्ठाure अणु
    UCHAR ccs_index;
    UCHAR psm;
    UCHAR pass_fail;
    UCHAR retry_count;
    UCHAR max_retries;
    UCHAR frags_reमुख्यing;
    UCHAR no_rb;
    UCHAR rts_reqd;
    UCHAR csma_tx_cntrl_2;
    UCHAR sअगरs_tx_cntrl_2;
    UCHAR tx_dma_addr_1[2];
    UCHAR tx_dma_addr_2[2];
    UCHAR var_dur_2mhz[2];
    UCHAR var_dur_1mhz[2];
    UCHAR max_dur_2mhz[2];
    UCHAR max_dur_1mhz[2];
    UCHAR hdr_len;
    UCHAR max_frag_len[2];
    UCHAR var_len[2];
    UCHAR phy_hdr_4;
    UCHAR mac_hdr_1;
    UCHAR mac_hdr_2;
    UCHAR sid[2];
पूर्ण;

काष्ठा phy_header अणु
    UCHAR sfd[2];
    UCHAR hdr_3;
    UCHAR hdr_4;
पूर्ण;
काष्ठा ray_rx_msg अणु
    काष्ठा mac_header mac;
	UCHAR	var[];
पूर्ण;

काष्ठा tx_msg अणु
    काष्ठा tib_काष्ठाure tib;
    काष्ठा phy_header phy;
    काष्ठा mac_header mac;
    UCHAR  var[1];
पूर्ण;

/****** ECF Receive Control Structure (RCS) Area at Shared RAM offset 0x0800  */
/* Structures क्रम command specअगरic parameters (rcs.var) */
काष्ठा rx_packet_cmd अणु
    UCHAR rx_data_ptr[2];
    UCHAR rx_data_length[2];
    UCHAR rx_sig_lev;
    UCHAR next_frag_rcs_index;
    UCHAR totalpacketlength[2];
पूर्ण;
काष्ठा rejoin_net_cmplt_cmd अणु
    UCHAR reserved;
    UCHAR bssid[ADDRLEN];
पूर्ण;
काष्ठा japan_call_sign_rxd अणु
    UCHAR rxd_call_sign[8];
    UCHAR reserved[5];
पूर्ण;

काष्ठा rcs अणु
    UCHAR buffer_status;
    UCHAR पूर्णांकerrupt_id;
    UCHAR link_field;
    /* command specअगरic parameters      */
    जोड़ अणु
        UCHAR reserved[13]; 
        काष्ठा rx_packet_cmd rx_packet;
        काष्ठा rejoin_net_cmplt_cmd rejoin_net_complete;
        काष्ठा japan_call_sign_rxd japan_call_sign;
    पूर्ण var;
पूर्ण;

/****** Startup parameter काष्ठाures क्रम both versions of firmware ***********/
काष्ठा b4_startup_params अणु
    UCHAR a_network_type;                /* C_ADHOC, C_INFRA                 */
    UCHAR a_acting_as_ap_status;         /* C_TYPE_STA, C_TYPE_AP            */
    UCHAR a_current_ess_id[ESSID_SIZE];  /* Null terminated unless 32 दीर्घ   */
    UCHAR a_scanning_mode;               /* passive 0, active 1              */
    UCHAR a_घातer_mgt_state;             /* CAM 0,                           */
    UCHAR a_mac_addr[ADDRLEN];           /*                                  */
    UCHAR a_frag_threshold[2];           /* 512                              */
    UCHAR a_hop_समय[2];                 /* 16k * 2**n, n=0-4 in Kus         */
    UCHAR a_beacon_period[2];            /* n * a_hop_समय  in Kus           */
    UCHAR a_dtim_period;                 /* in beacons                       */
    UCHAR a_retry_max;                   /*                                  */
    UCHAR a_ack_समयout;                 /*                                  */
    UCHAR a_sअगरs;                        /*                                  */
    UCHAR a_dअगरs;                        /*                                  */
    UCHAR a_pअगरs;                        /*                                  */
    UCHAR a_rts_threshold[2];            /*                                  */
    UCHAR a_scan_dwell_समय[2];          /*                                  */
    UCHAR a_max_scan_dwell_समय[2];      /*                                  */
    UCHAR a_assoc_resp_समयout_thresh;   /*                                  */
    UCHAR a_adhoc_scan_cycle_max;        /*                                  */
    UCHAR a_infra_scan_cycle_max;        /*                                  */
    UCHAR a_infra_super_scan_cycle_max;  /*                                  */
    UCHAR a_promiscuous_mode;            /*                                  */
    UCHAR a_unique_word[2];              /*                                  */
    UCHAR a_slot_समय;                   /*                                  */
    UCHAR a_roaming_low_snr_thresh;      /*                                  */
    UCHAR a_low_snr_count_thresh;        /*                                  */
    UCHAR a_infra_missed_bcn_thresh;     /*                                  */
    UCHAR a_adhoc_missed_bcn_thresh;     /*                                  */
    UCHAR a_curr_country_code;           /* C_USA                            */
    UCHAR a_hop_pattern;                 /*                                  */
    UCHAR a_hop_pattern_length;          /*                                  */
/* b4 - b5 dअगरferences start here */
    UCHAR a_cw_max;                      /*                                  */
    UCHAR a_cw_min;                      /*                                  */
    UCHAR a_noise_filter_gain;           /*                                  */
    UCHAR a_noise_limit_offset;          /*                                  */
    UCHAR a_det_rssi_thresh_offset;      /*                                  */
    UCHAR a_med_busy_thresh_offset;      /*                                  */
    UCHAR a_det_sync_thresh;             /*                                  */
    UCHAR a_test_mode;                   /*                                  */
    UCHAR a_test_min_chan_num;           /*                                  */
    UCHAR a_test_max_chan_num;           /*                                  */
    UCHAR a_rx_tx_delay;                 /*                                  */
    UCHAR a_current_bss_id[ADDRLEN];     /*                                  */
    UCHAR a_hop_set;                     /*                                  */
पूर्ण;
काष्ठा b5_startup_params अणु
    UCHAR a_network_type;                /* C_ADHOC, C_INFRA                 */
    UCHAR a_acting_as_ap_status;         /* C_TYPE_STA, C_TYPE_AP            */
    UCHAR a_current_ess_id[ESSID_SIZE];  /* Null terminated unless 32 दीर्घ   */
    UCHAR a_scanning_mode;               /* passive 0, active 1              */
    UCHAR a_घातer_mgt_state;             /* CAM 0,                           */
    UCHAR a_mac_addr[ADDRLEN];           /*                                  */
    UCHAR a_frag_threshold[2];           /* 512                              */
    UCHAR a_hop_समय[2];                 /* 16k * 2**n, n=0-4 in Kus         */
    UCHAR a_beacon_period[2];            /* n * a_hop_समय  in Kus           */
    UCHAR a_dtim_period;                 /* in beacons                       */
    UCHAR a_retry_max;                   /* 4                                */
    UCHAR a_ack_समयout;                 /*                                  */
    UCHAR a_sअगरs;                        /*                                  */
    UCHAR a_dअगरs;                        /*                                  */
    UCHAR a_pअगरs;                        /*                                  */
    UCHAR a_rts_threshold[2];            /*                                  */
    UCHAR a_scan_dwell_समय[2];          /*                                  */
    UCHAR a_max_scan_dwell_समय[2];      /*                                  */
    UCHAR a_assoc_resp_समयout_thresh;   /*                                  */
    UCHAR a_adhoc_scan_cycle_max;        /*                                  */
    UCHAR a_infra_scan_cycle_max;        /*                                  */
    UCHAR a_infra_super_scan_cycle_max;  /*                                  */
    UCHAR a_promiscuous_mode;            /*                                  */
    UCHAR a_unique_word[2];              /*                                  */
    UCHAR a_slot_समय;                   /*                                  */
    UCHAR a_roaming_low_snr_thresh;      /*                                  */
    UCHAR a_low_snr_count_thresh;        /*                                  */
    UCHAR a_infra_missed_bcn_thresh;     /*                                  */
    UCHAR a_adhoc_missed_bcn_thresh;     /*                                  */
    UCHAR a_curr_country_code;           /* C_USA                            */
    UCHAR a_hop_pattern;                 /*                                  */
    UCHAR a_hop_pattern_length;          /*                                  */
/* b4 - b5 dअगरferences start here */
    UCHAR a_cw_max[2];                   /*                                  */
    UCHAR a_cw_min[2];                   /*                                  */
    UCHAR a_noise_filter_gain;           /*                                  */
    UCHAR a_noise_limit_offset;          /*                                  */
    UCHAR a_det_rssi_thresh_offset;      /*                                  */
    UCHAR a_med_busy_thresh_offset;      /*                                  */
    UCHAR a_det_sync_thresh;             /*                                  */
    UCHAR a_test_mode;                   /*                                  */
    UCHAR a_test_min_chan_num;           /*                                  */
    UCHAR a_test_max_chan_num;           /*                                  */
    UCHAR a_allow_bcast_SSID_probe_rsp;
    UCHAR a_privacy_must_start;
    UCHAR a_privacy_can_join;
    UCHAR a_basic_rate_set[8];
पूर्ण;

/*****************************************************************************/
#घोषणा RAY_IOCG_PARMS (SIOCDEVPRIVATE)
#घोषणा RAY_IOCS_PARMS (SIOCDEVPRIVATE + 1)
#घोषणा RAY_DO_CMD     (SIOCDEVPRIVATE + 2)

/****** ethernet <-> 802.11 translation **************************************/
प्रकार काष्ठा snaphdr_t
अणु
  UCHAR   dsap;
  UCHAR   ssap;
  UCHAR   ctrl;
  UCHAR   org[3];
  UCHAR   ethertype[2];
पूर्ण snaphdr_t;

#घोषणा BRIDGE_ENCAP  0xf80000
#घोषणा RFC1042_ENCAP 0
#घोषणा SNAP_ID       0x0003aaaa
#घोषणा RAY_IPX_TYPE  0x8137
#घोषणा APPLEARP_TYPE 0x80f3
/*****************************************************************************/
#पूर्ण_अगर /* _RAYCTL_H_ */
