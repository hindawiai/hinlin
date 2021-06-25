<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ATMMPC_H_
#घोषणा _ATMMPC_H_

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/types.h>

#घोषणा ATMMPC_CTRL _IO('a', ATMIOC_MPOA)
#घोषणा ATMMPC_DATA _IO('a', ATMIOC_MPOA+1)

#घोषणा MPC_SOCKET_INGRESS 1
#घोषणा MPC_SOCKET_EGRESS  2

काष्ठा aपंचांगmpc_ioc अणु
        पूर्णांक dev_num;
        __be32 ipaddr;              /* the IP address of the लघुcut    */
        पूर्णांक type;                     /* ingress or egress                 */
पूर्ण;

प्रकार काष्ठा in_ctrl_info अणु
        __u8   Last_NHRP_CIE_code;
        __u8   Last_Q2931_cause_value;
        __u8   eg_MPC_ATM_addr[ATM_ESA_LEN];
        __be32  tag;
        __be32  in_dst_ip;      /* IP address this ingress MPC sends packets to */
        __u16  holding_समय;
        __u32  request_id;
पूर्ण in_ctrl_info;

प्रकार काष्ठा eg_ctrl_info अणु
        __u8   DLL_header[256];
        __u8   DH_length;
        __be32  cache_id;
        __be32  tag;
        __be32  mps_ip;
        __be32  eg_dst_ip;      /* IP address to which ingress MPC sends packets */
        __u8   in_MPC_data_ATM_addr[ATM_ESA_LEN];
        __u16  holding_समय;
पूर्ण eg_ctrl_info;

काष्ठा mpc_parameters अणु
        __u16 mpc_p1;   /* Shortcut-Setup Frame Count    */
        __u16 mpc_p2;   /* Shortcut-Setup Frame Time     */
        __u8 mpc_p3[8]; /* Flow-detection Protocols      */
        __u16 mpc_p4;   /* MPC Initial Retry Time        */
        __u16 mpc_p5;   /* MPC Retry Time Maximum        */
        __u16 mpc_p6;   /* Hold Down Time                */
पूर्ण ;

काष्ठा k_message अणु
        __u16 type;
        __be32 ip_mask;
        __u8  MPS_ctrl[ATM_ESA_LEN];
        जोड़ अणु
                in_ctrl_info in_info;
                eg_ctrl_info eg_info;
                काष्ठा mpc_parameters params;
        पूर्ण content;
        काष्ठा aपंचांग_qos qos;       
पूर्ण __ATM_API_ALIGN;

काष्ठा llc_snap_hdr अणु
	/* RFC 1483 LLC/SNAP encapsulation क्रम routed IP PDUs */
        __u8  dsap;    /* Destination Service Access Poपूर्णांक (0xAA)     */
        __u8  ssap;    /* Source Service Access Poपूर्णांक      (0xAA)     */
        __u8  ui;      /* Unnumbered Inक्रमmation           (0x03)     */
        __u8  org[3];  /* Organizational identअगरication    (0x000000) */
        __u8  type[2]; /* Ether type (क्रम IP)              (0x0800)   */
पूर्ण;

/* TLVs this MPC recognizes */
#घोषणा TLV_MPOA_DEVICE_TYPE         0x00a03e2a  

/* MPOA device types in MPOA Device Type TLV */
#घोषणा NON_MPOA    0
#घोषणा MPS         1
#घोषणा MPC         2
#घोषणा MPS_AND_MPC 3


/* MPC parameter शेषs */

#घोषणा MPC_P1 10  /* Shortcut-Setup Frame Count  */ 
#घोषणा MPC_P2 1   /* Shortcut-Setup Frame Time   */
#घोषणा MPC_P3 0   /* Flow-detection Protocols    */
#घोषणा MPC_P4 5   /* MPC Initial Retry Time      */
#घोषणा MPC_P5 40  /* MPC Retry Time Maximum      */
#घोषणा MPC_P6 160 /* Hold Down Time              */
#घोषणा HOLDING_TIME_DEFAULT 1200 /* same as MPS-p7 */

/* MPC स्थिरants */

#घोषणा MPC_C1 2   /* Retry Time Multiplier       */
#घोषणा MPC_C2 60  /* Initial Keep-Alive Lअगरeसमय */

/* Message types - to MPOA daemon */

#घोषणा SND_MPOA_RES_RQST    201
#घोषणा SET_MPS_CTRL_ADDR    202
#घोषणा SND_MPOA_RES_RTRY    203 /* Dअगरferent type in a retry due to req id         */
#घोषणा STOP_KEEP_ALIVE_SM   204
#घोषणा EGRESS_ENTRY_REMOVED 205
#घोषणा SND_EGRESS_PURGE     206
#घोषणा DIE                  207 /* tell the daemon to निकास()                       */
#घोषणा DATA_PLANE_PURGE     208 /* Data plane purge because of egress cache hit miss or dead MPS */
#घोषणा OPEN_INGRESS_SVC     209

/* Message types - from MPOA daemon */

#घोषणा MPOA_TRIGGER_RCVD     101
#घोषणा MPOA_RES_REPLY_RCVD   102
#घोषणा INGRESS_PURGE_RCVD    103
#घोषणा EGRESS_PURGE_RCVD     104
#घोषणा MPS_DEATH             105
#घोषणा CACHE_IMPOS_RCVD      106
#घोषणा SET_MPC_CTRL_ADDR     107 /* Our MPC's control ATM address   */
#घोषणा SET_MPS_MAC_ADDR      108
#घोषणा CLEAN_UP_AND_EXIT     109
#घोषणा SET_MPC_PARAMS        110 /* MPC configuration parameters    */

/* Message types - bidirectional */       

#घोषणा RELOAD                301 /* समाप्त -HUP the daemon क्रम reload */

#पूर्ण_अगर /* _ATMMPC_H_ */
