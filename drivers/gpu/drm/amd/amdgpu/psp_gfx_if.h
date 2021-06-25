<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _PSP_TEE_GFX_IF_H_
#घोषणा _PSP_TEE_GFX_IF_H_

#घोषणा PSP_GFX_CMD_BUF_VERSION     0x00000001

#घोषणा GFX_CMD_STATUS_MASK         0x0000FFFF
#घोषणा GFX_CMD_ID_MASK             0x000F0000
#घोषणा GFX_CMD_RESERVED_MASK       0x7FF00000
#घोषणा GFX_CMD_RESPONSE_MASK       0x80000000

/* USBC PD FW version retrieval command */
#घोषणा C2PMSG_CMD_GFX_USB_PD_FW_VER 0x2000000

/* TEE Gfx Command IDs क्रम the रेजिस्टर पूर्णांकerface.
*  Command ID must be between 0x00010000 and 0x000F0000.
*/
क्रमागत psp_gfx_crtl_cmd_id
अणु
    GFX_CTRL_CMD_ID_INIT_RBI_RING   = 0x00010000,   /* initialize RBI ring */
    GFX_CTRL_CMD_ID_INIT_GPCOM_RING = 0x00020000,   /* initialize GPCOM ring */
    GFX_CTRL_CMD_ID_DESTROY_RINGS   = 0x00030000,   /* destroy rings */
    GFX_CTRL_CMD_ID_CAN_INIT_RINGS  = 0x00040000,   /* is it allowed to initialized the rings */
    GFX_CTRL_CMD_ID_ENABLE_INT      = 0x00050000,   /* enable PSP-to-Gfx पूर्णांकerrupt */
    GFX_CTRL_CMD_ID_DISABLE_INT     = 0x00060000,   /* disable PSP-to-Gfx पूर्णांकerrupt */
    GFX_CTRL_CMD_ID_MODE1_RST       = 0x00070000,   /* trigger the Mode 1 reset */
    GFX_CTRL_CMD_ID_GBR_IH_SET      = 0x00080000,   /* set Gbr IH_RB_CNTL रेजिस्टरs */
    GFX_CTRL_CMD_ID_CONSUME_CMD     = 0x00090000,   /* send पूर्णांकerrupt to psp क्रम updating ग_लिखो poपूर्णांकer of vf */
    GFX_CTRL_CMD_ID_DESTROY_GPCOM_RING = 0x000C0000, /* destroy GPCOM ring */

    GFX_CTRL_CMD_ID_MAX             = 0x000F0000,   /* max command ID */
पूर्ण;


/*-----------------------------------------------------------------------------
    NOTE:   All physical addresses used in this पूर्णांकerface are actually
            GPU Virtual Addresses.
*/


/* Control रेजिस्टरs of the TEE Gfx पूर्णांकerface. These are located in
*  SRBM-to-PSP mailbox रेजिस्टरs (total 8 रेजिस्टरs).
*/
काष्ठा psp_gfx_ctrl
अणु
    अस्थिर uपूर्णांक32_t   cmd_resp;         /* +0   Command/Response रेजिस्टर क्रम Gfx commands */
    अस्थिर uपूर्णांक32_t   rbi_wptr;         /* +4   Write poपूर्णांकer (index) of RBI ring */
    अस्थिर uपूर्णांक32_t   rbi_rptr;         /* +8   Read poपूर्णांकer (index) of RBI ring */
    अस्थिर uपूर्णांक32_t   gpcom_wptr;       /* +12  Write poपूर्णांकer (index) of GPCOM ring */
    अस्थिर uपूर्णांक32_t   gpcom_rptr;       /* +16  Read poपूर्णांकer (index) of GPCOM ring */
    अस्थिर uपूर्णांक32_t   ring_addr_lo;     /* +20  bits [31:0] of GPU Virtual of ring buffer (VMID=0)*/
    अस्थिर uपूर्णांक32_t   ring_addr_hi;     /* +24  bits [63:32] of GPU Virtual of ring buffer (VMID=0) */
    अस्थिर uपूर्णांक32_t   ring_buf_size;    /* +28  Ring buffer size (in bytes) */

पूर्ण;


/* Response flag is set in the command when command is completed by PSP.
*  Used in the GFX_CTRL.CmdResp.
*  When PSP GFX I/F is initialized, the flag is set.
*/
#घोषणा GFX_FLAG_RESPONSE               0x80000000

/* TEE Gfx Command IDs क्रम the ring buffer पूर्णांकerface. */
क्रमागत psp_gfx_cmd_id
अणु
    GFX_CMD_ID_LOAD_TA            = 0x00000001,   /* load TA */
    GFX_CMD_ID_UNLOAD_TA          = 0x00000002,   /* unload TA */
    GFX_CMD_ID_INVOKE_CMD         = 0x00000003,   /* send command to TA */
    GFX_CMD_ID_LOAD_ASD           = 0x00000004,   /* load ASD Driver */
    GFX_CMD_ID_SETUP_TMR          = 0x00000005,   /* setup TMR region */
    GFX_CMD_ID_LOAD_IP_FW         = 0x00000006,   /* load HW IP FW */
    GFX_CMD_ID_DESTROY_TMR        = 0x00000007,   /* destroy TMR region */
    GFX_CMD_ID_SAVE_RESTORE       = 0x00000008,   /* save/restore HW IP FW */
    GFX_CMD_ID_SETUP_VMR          = 0x00000009,   /* setup VMR region */
    GFX_CMD_ID_DESTROY_VMR        = 0x0000000A,   /* destroy VMR region */
    GFX_CMD_ID_PROG_REG           = 0x0000000B,   /* program regs */
    GFX_CMD_ID_CLEAR_VF_FW        = 0x0000000D,   /* Clear VF FW, to be used on VF shutकरोwn. */
    GFX_CMD_ID_GET_FW_ATTESTATION = 0x0000000F,   /* Query GPUVA of the Fw Attestation DB */
    /* IDs upto 0x1F are reserved क्रम older programs (Raven, Vega 10/12/20) */
    GFX_CMD_ID_LOAD_TOC           = 0x00000020,   /* Load TOC and obtain TMR size */
    GFX_CMD_ID_AUTOLOAD_RLC       = 0x00000021,   /* Indicates all graphics fw loaded, start RLC स्वतःload */
    GFX_CMD_ID_BOOT_CFG           = 0x00000022,   /* Boot Config */
पूर्ण;

/* PSP boot config sub-commands */
क्रमागत psp_gfx_boot_config_cmd
अणु
    BOOTCFG_CMD_SET         = 1, /* Set boot configuration settings */
    BOOTCFG_CMD_GET         = 2, /* Get boot configuration settings */
    BOOTCFG_CMD_INVALIDATE  = 3  /* Reset current boot configuration settings to VBIOS शेषs */
पूर्ण;

/* PSP boot config biपंचांगask values */
क्रमागत psp_gfx_boot_config
अणु
    BOOT_CONFIG_GECC = 0x1,
पूर्ण;

/* Command to load Trusted Application binary पूर्णांकo PSP OS. */
काष्ठा psp_gfx_cmd_load_ta
अणु
    uपूर्णांक32_t        app_phy_addr_lo;        /* bits [31:0] of the GPU Virtual address of the TA binary (must be 4 KB aligned) */
    uपूर्णांक32_t        app_phy_addr_hi;        /* bits [63:32] of the GPU Virtual address of the TA binary */
    uपूर्णांक32_t        app_len;                /* length of the TA binary in bytes */
    uपूर्णांक32_t        cmd_buf_phy_addr_lo;    /* bits [31:0] of the GPU Virtual address of CMD buffer (must be 4 KB aligned) */
    uपूर्णांक32_t        cmd_buf_phy_addr_hi;    /* bits [63:32] of the GPU Virtual address of CMD buffer */
    uपूर्णांक32_t        cmd_buf_len;            /* length of the CMD buffer in bytes; must be multiple of 4 KB */

    /* Note: CmdBufLen can be set to 0. In this हाल no persistent CMD buffer is provided
    *       क्रम the TA. Each InvokeCommand can have dinamically mapped CMD buffer instead
    *       of using global persistent buffer.
    */
पूर्ण;


/* Command to Unload Trusted Application binary from PSP OS. */
काष्ठा psp_gfx_cmd_unload_ta
अणु
    uपूर्णांक32_t        session_id;          /* Session ID of the loaded TA to be unloaded */

पूर्ण;


/* Shared buffers क्रम InvokeCommand.
*/
काष्ठा psp_gfx_buf_desc
अणु
    uपूर्णांक32_t        buf_phy_addr_lo;       /* bits [31:0] of GPU Virtual address of the buffer (must be 4 KB aligned) */
    uपूर्णांक32_t        buf_phy_addr_hi;       /* bits [63:32] of GPU Virtual address of the buffer */
    uपूर्णांक32_t        buf_size;              /* buffer size in bytes (must be multiple of 4 KB and no bigger than 64 MB) */

पूर्ण;

/* Max number of descriptors क्रम one shared buffer (in how many dअगरferent
*  physical locations one shared buffer can be stored). If buffer is too much
*  fragmented, error will be वापसed.
*/
#घोषणा GFX_BUF_MAX_DESC        64

काष्ठा psp_gfx_buf_list
अणु
    uपूर्णांक32_t                num_desc;                    /* number of buffer descriptors in the list */
    uपूर्णांक32_t                total_size;                  /* total size of all buffers in the list in bytes (must be multiple of 4 KB) */
    काष्ठा psp_gfx_buf_desc buf_desc[GFX_BUF_MAX_DESC];  /* list of buffer descriptors */

    /* total 776 bytes */
पूर्ण;

/* Command to execute InvokeCommand entry poपूर्णांक of the TA. */
काष्ठा psp_gfx_cmd_invoke_cmd
अणु
    uपूर्णांक32_t                session_id;           /* Session ID of the TA to be executed */
    uपूर्णांक32_t                ta_cmd_id;            /* Command ID to be sent to TA */
    काष्ठा psp_gfx_buf_list buf;                  /* one indirect buffer (scatter/gather list) */

पूर्ण;


/* Command to setup TMR region. */
काष्ठा psp_gfx_cmd_setup_पंचांगr
अणु
    uपूर्णांक32_t        buf_phy_addr_lo;       /* bits [31:0] of GPU Virtual address of TMR buffer (must be 4 KB aligned) */
    uपूर्णांक32_t        buf_phy_addr_hi;       /* bits [63:32] of GPU Virtual address of TMR buffer */
    uपूर्णांक32_t        buf_size;              /* buffer size in bytes (must be multiple of 4 KB) */
    जोड़ अणु
	काष्ठा अणु
		uपूर्णांक32_t	sriov_enabled:1; /* whether the device runs under SR-IOV*/
		uपूर्णांक32_t	virt_phy_addr:1; /* driver passes both भव and physical address to PSP*/
		uपूर्णांक32_t	reserved:30;
	पूर्ण bitfield;
	uपूर्णांक32_t        पंचांगr_flags;
    पूर्ण;
    uपूर्णांक32_t        प्रणाली_phy_addr_lo;        /* bits [31:0] of प्रणाली physical address of TMR buffer (must be 4 KB aligned) */
    uपूर्णांक32_t        प्रणाली_phy_addr_hi;        /* bits [63:32] of प्रणाली physical address of TMR buffer */

पूर्ण;

/* FW types क्रम GFX_CMD_ID_LOAD_IP_FW command. Limit 31. */
क्रमागत psp_gfx_fw_type अणु
	GFX_FW_TYPE_NONE        = 0,    /* */
	GFX_FW_TYPE_CP_ME       = 1,    /* CP-ME                    VG + RV */
	GFX_FW_TYPE_CP_PFP      = 2,    /* CP-PFP                   VG + RV */
	GFX_FW_TYPE_CP_CE       = 3,    /* CP-CE                    VG + RV */
	GFX_FW_TYPE_CP_MEC      = 4,    /* CP-MEC FW                VG + RV */
	GFX_FW_TYPE_CP_MEC_ME1  = 5,    /* CP-MEC Jump Table 1      VG + RV */
	GFX_FW_TYPE_CP_MEC_ME2  = 6,    /* CP-MEC Jump Table 2      VG      */
	GFX_FW_TYPE_RLC_V       = 7,    /* RLC-V                    VG      */
	GFX_FW_TYPE_RLC_G       = 8,    /* RLC-G                    VG + RV */
	GFX_FW_TYPE_SDMA0       = 9,    /* SDMA0                    VG + RV */
	GFX_FW_TYPE_SDMA1       = 10,   /* SDMA1                    VG      */
	GFX_FW_TYPE_DMCU_ERAM   = 11,   /* DMCU-ERAM                VG + RV */
	GFX_FW_TYPE_DMCU_ISR    = 12,   /* DMCU-ISR                 VG + RV */
	GFX_FW_TYPE_VCN         = 13,   /* VCN                           RV */
	GFX_FW_TYPE_UVD         = 14,   /* UVD                      VG      */
	GFX_FW_TYPE_VCE         = 15,   /* VCE                      VG      */
	GFX_FW_TYPE_ISP         = 16,   /* ISP                           RV */
	GFX_FW_TYPE_ACP         = 17,   /* ACP                           RV */
	GFX_FW_TYPE_SMU         = 18,   /* SMU                      VG      */
	GFX_FW_TYPE_MMSCH       = 19,   /* MMSCH                    VG      */
	GFX_FW_TYPE_RLC_RESTORE_LIST_GPM_MEM        = 20,   /* RLC GPM                  VG + RV */
	GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_MEM        = 21,   /* RLC SRM                  VG + RV */
	GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_CNTL       = 22,   /* RLC CNTL                 VG + RV */
	GFX_FW_TYPE_UVD1        = 23,   /* UVD1                     VG-20   */
	GFX_FW_TYPE_TOC         = 24,   /* TOC                      NV-10   */
	GFX_FW_TYPE_RLC_P                           = 25,   /* RLC P                    NV      */
	GFX_FW_TYPE_RLC_IRAM                        = 26,   /* RLC_IRAM                 NV      */
	GFX_FW_TYPE_GLOBAL_TAP_DELAYS               = 27,   /* GLOBAL TAP DELAYS        NV      */
	GFX_FW_TYPE_SE0_TAP_DELAYS                  = 28,   /* SE0 TAP DELAYS           NV      */
	GFX_FW_TYPE_SE1_TAP_DELAYS                  = 29,   /* SE1 TAP DELAYS           NV      */
	GFX_FW_TYPE_GLOBAL_SE0_SE1_SKEW_DELAYS      = 30,   /* GLOBAL SE0/1 SKEW DELAYS NV      */
	GFX_FW_TYPE_SDMA0_JT                        = 31,   /* SDMA0 JT                 NV      */
	GFX_FW_TYPE_SDMA1_JT                        = 32,   /* SDNA1 JT                 NV      */
	GFX_FW_TYPE_CP_MES                          = 33,   /* CP MES                   NV      */
	GFX_FW_TYPE_MES_STACK                       = 34,   /* MES STACK                NV      */
	GFX_FW_TYPE_RLC_SRM_DRAM_SR                 = 35,   /* RLC SRM DRAM             NV      */
	GFX_FW_TYPE_RLCG_SCRATCH_SR                 = 36,   /* RLCG SCRATCH             NV      */
	GFX_FW_TYPE_RLCP_SCRATCH_SR                 = 37,   /* RLCP SCRATCH             NV      */
	GFX_FW_TYPE_RLCV_SCRATCH_SR                 = 38,   /* RLCV SCRATCH             NV      */
	GFX_FW_TYPE_RLX6_DRAM_SR                    = 39,   /* RLX6 DRAM                NV      */
	GFX_FW_TYPE_SDMA0_PG_CONTEXT                = 40,   /* SDMA0 PG CONTEXT         NV      */
	GFX_FW_TYPE_SDMA1_PG_CONTEXT                = 41,   /* SDMA1 PG CONTEXT         NV      */
	GFX_FW_TYPE_GLOBAL_MUX_SELECT_RAM           = 42,   /* GLOBAL MUX SEL RAM       NV      */
	GFX_FW_TYPE_SE0_MUX_SELECT_RAM              = 43,   /* SE0 MUX SEL RAM          NV      */
	GFX_FW_TYPE_SE1_MUX_SELECT_RAM              = 44,   /* SE1 MUX SEL RAM          NV      */
	GFX_FW_TYPE_ACCUM_CTRL_RAM                  = 45,   /* ACCUM CTRL RAM           NV      */
	GFX_FW_TYPE_RLCP_CAM                        = 46,   /* RLCP CAM                 NV      */
	GFX_FW_TYPE_RLC_SPP_CAM_EXT                 = 47,   /* RLC SPP CAM EXT          NV      */
	GFX_FW_TYPE_RLC_DRAM_BOOT                   = 48,   /* RLC DRAM BOOT            NV      */
	GFX_FW_TYPE_VCN0_RAM                        = 49,   /* VCN_RAM                  NV + RN */
	GFX_FW_TYPE_VCN1_RAM                        = 50,   /* VCN_RAM                  NV + RN */
	GFX_FW_TYPE_DMUB                            = 51,   /* DMUB                          RN */
	GFX_FW_TYPE_SDMA2                           = 52,   /* SDMA2                    MI      */
	GFX_FW_TYPE_SDMA3                           = 53,   /* SDMA3                    MI      */
	GFX_FW_TYPE_SDMA4                           = 54,   /* SDMA4                    MI      */
	GFX_FW_TYPE_SDMA5                           = 55,   /* SDMA5                    MI      */
	GFX_FW_TYPE_SDMA6                           = 56,   /* SDMA6                    MI      */
	GFX_FW_TYPE_SDMA7                           = 57,   /* SDMA7                    MI      */
	GFX_FW_TYPE_VCN1                            = 58,   /* VCN1                     MI      */
	GFX_FW_TYPE_REG_LIST                        = 67,   /* REG_LIST                 MI      */
	GFX_FW_TYPE_MAX
पूर्ण;

/* Command to load HW IP FW. */
काष्ठा psp_gfx_cmd_load_ip_fw
अणु
    uपूर्णांक32_t                fw_phy_addr_lo;    /* bits [31:0] of GPU Virtual address of FW location (must be 4 KB aligned) */
    uपूर्णांक32_t                fw_phy_addr_hi;    /* bits [63:32] of GPU Virtual address of FW location */
    uपूर्णांक32_t                fw_size;           /* FW buffer size in bytes */
    क्रमागत psp_gfx_fw_type    fw_type;           /* FW type */

पूर्ण;

/* Command to save/restore HW IP FW. */
काष्ठा psp_gfx_cmd_save_restore_ip_fw
अणु
    uपूर्णांक32_t                save_fw;              /* अगर set, command is used क्रम saving fw otherwise क्रम resetoring*/
    uपूर्णांक32_t                save_restore_addr_lo; /* bits [31:0] of FB address of GART memory used as save/restore buffer (must be 4 KB aligned) */
    uपूर्णांक32_t                save_restore_addr_hi; /* bits [63:32] of FB address of GART memory used as save/restore buffer */
    uपूर्णांक32_t                buf_size;             /* Size of the save/restore buffer in bytes */
    क्रमागत psp_gfx_fw_type    fw_type;              /* FW type */
पूर्ण;

/* Command to setup रेजिस्टर program */
काष्ठा psp_gfx_cmd_reg_prog अणु
	uपूर्णांक32_t	reg_value;
	uपूर्णांक32_t	reg_id;
पूर्ण;

/* Command to load TOC */
काष्ठा psp_gfx_cmd_load_toc
अणु
    uपूर्णांक32_t        toc_phy_addr_lo;        /* bits [31:0] of GPU Virtual address of FW location (must be 4 KB aligned) */
    uपूर्णांक32_t        toc_phy_addr_hi;        /* bits [63:32] of GPU Virtual address of FW location */
    uपूर्णांक32_t        toc_size;               /* FW buffer size in bytes */
पूर्ण;

/* Dynamic boot configuration */
काष्ठा psp_gfx_cmd_boot_cfg
अणु
    uपूर्णांक32_t                        बारtamp;            /* calendar समय as number of seconds */
    क्रमागत psp_gfx_boot_config_cmd    sub_cmd;              /* sub-command indicating how to process command data */
    uपूर्णांक32_t                        boot_config;          /* dynamic boot configuration biपंचांगask */
    uपूर्णांक32_t                        boot_config_valid;    /* dynamic boot configuration valid bits biपंचांगask */
पूर्ण;

/* All GFX ring buffer commands. */
जोड़ psp_gfx_commands
अणु
    काष्ठा psp_gfx_cmd_load_ta          cmd_load_ta;
    काष्ठा psp_gfx_cmd_unload_ta        cmd_unload_ta;
    काष्ठा psp_gfx_cmd_invoke_cmd       cmd_invoke_cmd;
    काष्ठा psp_gfx_cmd_setup_पंचांगr        cmd_setup_पंचांगr;
    काष्ठा psp_gfx_cmd_load_ip_fw       cmd_load_ip_fw;
    काष्ठा psp_gfx_cmd_save_restore_ip_fw cmd_save_restore_ip_fw;
    काष्ठा psp_gfx_cmd_reg_prog       cmd_setup_reg_prog;
    काष्ठा psp_gfx_cmd_setup_पंचांगr        cmd_setup_vmr;
    काष्ठा psp_gfx_cmd_load_toc         cmd_load_toc;
    काष्ठा psp_gfx_cmd_boot_cfg         boot_cfg;
पूर्ण;

काष्ठा psp_gfx_uresp_reserved
अणु
    uपूर्णांक32_t reserved[8];
पूर्ण;

/* Command-specअगरic response क्रम Fw Attestation Db */
काष्ठा psp_gfx_uresp_fwar_db_info
अणु
    uपूर्णांक32_t fwar_db_addr_lo;
    uपूर्णांक32_t fwar_db_addr_hi;
पूर्ण;

/* Union of command-specअगरic responses क्रम GPCOM ring. */
जोड़ psp_gfx_uresp
अणु
    काष्ठा psp_gfx_uresp_reserved reserved;
    काष्ठा psp_gfx_uresp_fwar_db_info fwar_db_info;
पूर्ण;

/* Structure of GFX Response buffer.
* For GPCOM I/F it is part of GFX_CMD_RESP buffer, क्रम RBI
* it is separate buffer.
*/
काष्ठा psp_gfx_resp
अणु
    uपूर्णांक32_t	status;		/* +0  status of command execution */
    uपूर्णांक32_t	session_id;	/* +4  session ID in response to LoadTa command */
    uपूर्णांक32_t	fw_addr_lo;	/* +8  bits [31:0] of FW address within TMR (in response to cmd_load_ip_fw command) */
    uपूर्णांक32_t	fw_addr_hi;	/* +12 bits [63:32] of FW address within TMR (in response to cmd_load_ip_fw command) */
    uपूर्णांक32_t	पंचांगr_size;	/* +16 size of the TMR to be reserved including MM fw and Gfx fw in response to cmd_load_toc command */

    uपूर्णांक32_t	reserved[11];

    जोड़ psp_gfx_uresp uresp;      /* +64 response जोड़ containing command-specअगरic responses */

    /* total 96 bytes */
पूर्ण;

/* Structure of Command buffer poपूर्णांकed by psp_gfx_rb_frame.cmd_buf_addr_hi
*  and psp_gfx_rb_frame.cmd_buf_addr_lo.
*/
काष्ठा psp_gfx_cmd_resp
अणु
    uपूर्णांक32_t        buf_size;           /* +0  total size of the buffer in bytes */
    uपूर्णांक32_t        buf_version;        /* +4  version of the buffer strusture; must be PSP_GFX_CMD_BUF_VERSION */
    uपूर्णांक32_t        cmd_id;             /* +8  command ID */

    /* These fields are used क्रम RBI only. They are all 0 in GPCOM commands
    */
    uपूर्णांक32_t        resp_buf_addr_lo;   /* +12 bits [31:0] of GPU Virtual address of response buffer (must be 4 KB aligned) */
    uपूर्णांक32_t        resp_buf_addr_hi;   /* +16 bits [63:32] of GPU Virtual address of response buffer */
    uपूर्णांक32_t        resp_offset;        /* +20 offset within response buffer */
    uपूर्णांक32_t        resp_buf_size;      /* +24 total size of the response buffer in bytes */

    जोड़ psp_gfx_commands  cmd;        /* +28 command specअगरic काष्ठाures */

    uपूर्णांक8_t         reserved_1[864 - माप(जोड़ psp_gfx_commands) - 28];

    /* Note: Resp is part of this buffer क्रम GPCOM ring. For RBI ring the response
    *        is separate buffer poपूर्णांकed by resp_buf_addr_hi and resp_buf_addr_lo.
    */
    काष्ठा psp_gfx_resp     resp;       /* +864 response */

    uपूर्णांक8_t         reserved_2[1024 - 864 - माप(काष्ठा psp_gfx_resp)];

    /* total size 1024 bytes */
पूर्ण;


#घोषणा FRAME_TYPE_DESTROY          1   /* frame sent by KMD driver when UMD Scheduler context is destroyed*/

/* Structure of the Ring Buffer Frame */
काष्ठा psp_gfx_rb_frame
अणु
    uपूर्णांक32_t    cmd_buf_addr_lo;    /* +0  bits [31:0] of GPU Virtual address of command buffer (must be 4 KB aligned) */
    uपूर्णांक32_t    cmd_buf_addr_hi;    /* +4  bits [63:32] of GPU Virtual address of command buffer */
    uपूर्णांक32_t    cmd_buf_size;       /* +8  command buffer size in bytes */
    uपूर्णांक32_t    fence_addr_lo;      /* +12 bits [31:0] of GPU Virtual address of Fence क्रम this frame */
    uपूर्णांक32_t    fence_addr_hi;      /* +16 bits [63:32] of GPU Virtual address of Fence क्रम this frame */
    uपूर्णांक32_t    fence_value;        /* +20 Fence value */
    uपूर्णांक32_t    sid_lo;             /* +24 bits [31:0] of SID value (used only क्रम RBI frames) */
    uपूर्णांक32_t    sid_hi;             /* +28 bits [63:32] of SID value (used only क्रम RBI frames) */
    uपूर्णांक8_t     vmid;               /* +32 VMID value used क्रम mapping of all addresses क्रम this frame */
    uपूर्णांक8_t     frame_type;         /* +33 1: destory context frame, 0: all other frames; used only क्रम RBI frames */
    uपूर्णांक8_t     reserved1[2];       /* +34 reserved, must be 0 */
    uपूर्णांक32_t    reserved2[7];       /* +36 reserved, must be 0 */
                /* total 64 bytes */
पूर्ण;

#घोषणा PSP_ERR_UNKNOWN_COMMAND 0x00000100

क्रमागत tee_error_code अणु
    TEE_SUCCESS                         = 0x00000000,
    TEE_ERROR_NOT_SUPPORTED             = 0xFFFF000A,
पूर्ण;

#पूर्ण_अगर /* _PSP_TEE_GFX_IF_H_ */
