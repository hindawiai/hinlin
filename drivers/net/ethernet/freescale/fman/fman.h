<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 * Copyright 2020 NXP
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __FM_H
#घोषणा __FM_H

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>

/* FM Frame descriptor macros  */
/* Frame queue Context Override */
#घोषणा FM_FD_CMD_FCO                   0x80000000
#घोषणा FM_FD_CMD_RPD                   0x40000000  /* Read Prepended Data */
#घोषणा FM_FD_CMD_UPD			0x20000000  /* Update Prepended Data */
#घोषणा FM_FD_CMD_DTC                   0x10000000  /* Do L4 Checksum */

/* TX-Port: Unsupported Format */
#घोषणा FM_FD_ERR_UNSUPPORTED_FORMAT    0x04000000
/* TX Port: Length Error */
#घोषणा FM_FD_ERR_LENGTH                0x02000000
#घोषणा FM_FD_ERR_DMA                   0x01000000  /* DMA Data error */

/* IPR frame (not error) */
#घोषणा FM_FD_IPR                       0x00000001
/* IPR non-consistent-sp */
#घोषणा FM_FD_ERR_IPR_NCSP              (0x00100000 | FM_FD_IPR)
/* IPR error */
#घोषणा FM_FD_ERR_IPR                   (0x00200000 | FM_FD_IPR)
/* IPR समयout */
#घोषणा FM_FD_ERR_IPR_TO                (0x00300000 | FM_FD_IPR)
/* TX Port: Length Error */
#घोषणा FM_FD_ERR_IPRE                  (FM_FD_ERR_IPR & ~FM_FD_IPR)

/* Rx FIFO overflow, FCS error, code error, running disparity error
 * (SGMII and TBI modes), FIFO parity error. PHY Sequence error,
 * PHY error control अक्षरacter detected.
 */
#घोषणा FM_FD_ERR_PHYSICAL              0x00080000
/* Frame too दीर्घ OR Frame size exceeds max_length_frame  */
#घोषणा FM_FD_ERR_SIZE                  0x00040000
/* classअगरication discard */
#घोषणा FM_FD_ERR_CLS_DISCARD           0x00020000
/* Extract Out of Frame */
#घोषणा FM_FD_ERR_EXTRACTION            0x00008000
/* No Scheme Selected */
#घोषणा FM_FD_ERR_NO_SCHEME             0x00004000
/* Keysize Overflow */
#घोषणा FM_FD_ERR_KEYSIZE_OVERFLOW      0x00002000
/* Frame color is red */
#घोषणा FM_FD_ERR_COLOR_RED             0x00000800
/* Frame color is yellow */
#घोषणा FM_FD_ERR_COLOR_YELLOW          0x00000400
/* Parser Time out Exceed */
#घोषणा FM_FD_ERR_PRS_TIMEOUT           0x00000080
/* Invalid Soft Parser inकाष्ठाion */
#घोषणा FM_FD_ERR_PRS_ILL_INSTRUCT      0x00000040
/* Header error was identअगरied during parsing */
#घोषणा FM_FD_ERR_PRS_HDR_ERR           0x00000020
/* Frame parsed beyind 256 first bytes */
#घोषणा FM_FD_ERR_BLOCK_LIMIT_EXCEEDED  0x00000008

/* non Frame-Manager error */
#घोषणा FM_FD_RX_STATUS_ERR_NON_FM      0x00400000

/* FMan driver defines */
#घोषणा FMAN_BMI_FIFO_UNITS		0x100
#घोषणा OFFSET_UNITS			16

/* BMan defines */
#घोषणा BM_MAX_NUM_OF_POOLS		64 /* Buffers pools */
#घोषणा FMAN_PORT_MAX_EXT_POOLS_NUM	8  /* External BM pools per Rx port */

काष्ठा fman; /* FMan data */

/* Enum क्रम defining port types */
क्रमागत fman_port_type अणु
	FMAN_PORT_TYPE_TX = 0,	/* TX Port */
	FMAN_PORT_TYPE_RX,	/* RX Port */
पूर्ण;

काष्ठा fman_rev_info अणु
	u8 major;			/* Major revision */
	u8 minor;			/* Minor revision */
पूर्ण;

क्रमागत fman_exceptions अणु
	FMAN_EX_DMA_BUS_ERROR = 0,	/* DMA bus error. */
	FMAN_EX_DMA_READ_ECC,		/* Read Buffer ECC error */
	FMAN_EX_DMA_SYSTEM_WRITE_ECC,	/* Write Buffer ECC err on sys side */
	FMAN_EX_DMA_FM_WRITE_ECC,	/* Write Buffer ECC error on FM side */
	FMAN_EX_DMA_SINGLE_PORT_ECC,	/* Single Port ECC error on FM side */
	FMAN_EX_FPM_STALL_ON_TASKS,	/* Stall of tasks on FPM */
	FMAN_EX_FPM_SINGLE_ECC,		/* Single ECC on FPM. */
	FMAN_EX_FPM_DOUBLE_ECC,		/* Double ECC error on FPM ram access */
	FMAN_EX_QMI_SINGLE_ECC,	/* Single ECC on QMI. */
	FMAN_EX_QMI_DOUBLE_ECC,	/* Double bit ECC occurred on QMI */
	FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID,/* DeQ from unknown port id */
	FMAN_EX_BMI_LIST_RAM_ECC,	/* Linked List RAM ECC error */
	FMAN_EX_BMI_STORAGE_PROखाता_ECC,/* storage profile */
	FMAN_EX_BMI_STATISTICS_RAM_ECC,/* Statistics RAM ECC Err Enable */
	FMAN_EX_BMI_DISPATCH_RAM_ECC,	/* Dispatch RAM ECC Error Enable */
	FMAN_EX_IRAM_ECC,		/* Double bit ECC occurred on IRAM */
	FMAN_EX_MURAM_ECC		/* Double bit ECC occurred on MURAM */
पूर्ण;

/* Parse results memory layout */
काष्ठा fman_prs_result अणु
	u8 lpid;		/* Logical port id */
	u8 shimr;		/* Shim header result  */
	__be16 l2r;		/* Layer 2 result */
	__be16 l3r;		/* Layer 3 result */
	u8 l4r;		/* Layer 4 result */
	u8 cplan;		/* Classअगरication plan id */
	__be16 nxthdr;		/* Next Header  */
	__be16 cksum;		/* Running-sum */
	/* Flags&fragment-offset field of the last IP-header */
	__be16 flags_frag_off;
	/* Routing type field of a IPV6 routing extension header */
	u8 route_type;
	/* Routing Extension Header Present; last bit is IP valid */
	u8 rhp_ip_valid;
	u8 shim_off[2];		/* Shim offset */
	u8 ip_pid_off;		/* IP PID (last IP-proto) offset */
	u8 eth_off;		/* ETH offset */
	u8 llc_snap_off;	/* LLC_SNAP offset */
	u8 vlan_off[2];		/* VLAN offset */
	u8 etype_off;		/* ETYPE offset */
	u8 pppoe_off;		/* PPP offset */
	u8 mpls_off[2];		/* MPLS offset */
	u8 ip_off[2];		/* IP offset */
	u8 gre_off;		/* GRE offset */
	u8 l4_off;		/* Layer 4 offset */
	u8 nxthdr_off;		/* Parser end poपूर्णांक */
पूर्ण;

/* A काष्ठाure क्रम defining buffer prefix area content. */
काष्ठा fman_buffer_prefix_content अणु
	/* Number of bytes to be left at the beginning of the बाह्यal
	 * buffer; Note that the निजी-area will start from the base
	 * of the buffer address.
	 */
	u16 priv_data_size;
	/* true to pass the parse result to/from the FM;
	 * User may use FM_PORT_GetBufferPrsResult() in
	 * order to get the parser-result from a buffer.
	 */
	bool pass_prs_result;
	/* true to pass the समयStamp to/from the FM User */
	bool pass_समय_stamp;
	/* true to pass the KG hash result to/from the FM User may
	 * use FM_PORT_GetBufferHashResult() in order to get the
	 * parser-result from a buffer.
	 */
	bool pass_hash_result;
	/* Add all other Internal-Context inक्रमmation: AD,
	 * hash-result, key, etc.
	 */
	u16 data_align;
पूर्ण;

/* A काष्ठाure of inक्रमmation about each of the बाह्यal
 * buffer pools used by a port or storage-profile.
 */
काष्ठा fman_ext_pool_params अणु
	u8 id;		    /* External buffer pool id */
	u16 size;		    /* External buffer pool buffer size */
पूर्ण;

/* A काष्ठाure क्रम inक्रमming the driver about the बाह्यal
 * buffer pools allocated in the BM and used by a port or a
 * storage-profile.
 */
काष्ठा fman_ext_pools अणु
	u8 num_of_pools_used; /* Number of pools use by this port */
	काष्ठा fman_ext_pool_params ext_buf_pool[FMAN_PORT_MAX_EXT_POOLS_NUM];
					/* Parameters क्रम each port */
पूर्ण;

/* A काष्ठाure क्रम defining BM pool depletion criteria */
काष्ठा fman_buf_pool_depletion अणु
	/* select mode in which छोड़ो frames will be sent after a
	 * number of pools (all together!) are depleted
	 */
	bool pools_grp_mode_enable;
	/* the number of depleted pools that will invoke छोड़ो
	 * frames transmission.
	 */
	u8 num_of_pools;
	/* For each pool, true अगर it should be considered क्रम
	 * depletion (Note - this pool must be used by this port!).
	 */
	bool pools_to_consider[BM_MAX_NUM_OF_POOLS];
	/* select mode in which छोड़ो frames will be sent
	 * after a single-pool is depleted;
	 */
	bool single_pool_mode_enable;
	/* For each pool, true अगर it should be considered
	 * क्रम depletion (Note - this pool must be used by this port!)
	 */
	bool pools_to_consider_क्रम_single_mode[BM_MAX_NUM_OF_POOLS];
पूर्ण;

/* Enum क्रम पूर्णांकer-module पूर्णांकerrupts registration */
क्रमागत fman_event_modules अणु
	FMAN_MOD_MAC = 0,		/* MAC event */
	FMAN_MOD_FMAN_CTRL,	/* FMAN Controller */
	FMAN_MOD_DUMMY_LAST
पूर्ण;

/* Enum क्रम पूर्णांकerrupts types */
क्रमागत fman_पूर्णांकr_type अणु
	FMAN_INTR_TYPE_ERR,
	FMAN_INTR_TYPE_NORMAL
पूर्ण;

/* Enum क्रम पूर्णांकer-module पूर्णांकerrupts registration */
क्रमागत fman_पूर्णांकer_module_event अणु
	FMAN_EV_ERR_MAC0 = 0,	/* MAC 0 error event */
	FMAN_EV_ERR_MAC1,		/* MAC 1 error event */
	FMAN_EV_ERR_MAC2,		/* MAC 2 error event */
	FMAN_EV_ERR_MAC3,		/* MAC 3 error event */
	FMAN_EV_ERR_MAC4,		/* MAC 4 error event */
	FMAN_EV_ERR_MAC5,		/* MAC 5 error event */
	FMAN_EV_ERR_MAC6,		/* MAC 6 error event */
	FMAN_EV_ERR_MAC7,		/* MAC 7 error event */
	FMAN_EV_ERR_MAC8,		/* MAC 8 error event */
	FMAN_EV_ERR_MAC9,		/* MAC 9 error event */
	FMAN_EV_MAC0,		/* MAC 0 event (Magic packet detection) */
	FMAN_EV_MAC1,		/* MAC 1 event (Magic packet detection) */
	FMAN_EV_MAC2,		/* MAC 2 (Magic packet detection) */
	FMAN_EV_MAC3,		/* MAC 3 (Magic packet detection) */
	FMAN_EV_MAC4,		/* MAC 4 (Magic packet detection) */
	FMAN_EV_MAC5,		/* MAC 5 (Magic packet detection) */
	FMAN_EV_MAC6,		/* MAC 6 (Magic packet detection) */
	FMAN_EV_MAC7,		/* MAC 7 (Magic packet detection) */
	FMAN_EV_MAC8,		/* MAC 8 event (Magic packet detection) */
	FMAN_EV_MAC9,		/* MAC 9 event (Magic packet detection) */
	FMAN_EV_FMAN_CTRL_0,	/* Fman controller event 0 */
	FMAN_EV_FMAN_CTRL_1,	/* Fman controller event 1 */
	FMAN_EV_FMAN_CTRL_2,	/* Fman controller event 2 */
	FMAN_EV_FMAN_CTRL_3,	/* Fman controller event 3 */
	FMAN_EV_CNT
पूर्ण;

काष्ठा fman_पूर्णांकr_src अणु
	व्योम (*isr_cb)(व्योम *src_arg);
	व्योम *src_handle;
पूर्ण;

/** fman_exceptions_cb
 * fman         - Poपूर्णांकer to FMan
 * exception    - The exception.
 *
 * Exceptions user callback routine, will be called upon an exception
 * passing the exception identअगरication.
 *
 * Return: irq status
 */
प्रकार irqवापस_t (fman_exceptions_cb)(काष्ठा fman *fman,
					 क्रमागत fman_exceptions exception);
/** fman_bus_error_cb
 * fman         - Poपूर्णांकer to FMan
 * port_id      - Port id
 * addr         - Address that caused the error
 * tnum         - Owner of error
 * liodn        - Logical IO device number
 *
 * Bus error user callback routine, will be called upon bus error,
 * passing parameters describing the errors and the owner.
 *
 * Return: IRQ status
 */
प्रकार irqवापस_t (fman_bus_error_cb)(काष्ठा fman *fman, u8 port_id,
					u64 addr, u8 tnum, u16 liodn);

/* Structure that holds inक्रमmation received from device tree */
काष्ठा fman_dts_params अणु
	व्योम __iomem *base_addr;                /* FMan भव address */
	काष्ठा resource *res;                   /* FMan memory resource */
	u8 id;                                  /* FMan ID */

	पूर्णांक err_irq;                            /* FMan Error IRQ */

	u16 clk_freq;                           /* FMan घड़ी freq (In Mhz) */

	u32 qman_channel_base;                  /* QMan channels base */
	u32 num_of_qman_channels;               /* Number of QMan channels */

	काष्ठा resource muram_res;              /* MURAM resource */
पूर्ण;

काष्ठा fman अणु
	काष्ठा device *dev;
	व्योम __iomem *base_addr;
	काष्ठा fman_पूर्णांकr_src पूर्णांकr_mng[FMAN_EV_CNT];

	काष्ठा fman_fpm_regs __iomem *fpm_regs;
	काष्ठा fman_bmi_regs __iomem *bmi_regs;
	काष्ठा fman_qmi_regs __iomem *qmi_regs;
	काष्ठा fman_dma_regs __iomem *dma_regs;
	काष्ठा fman_hwp_regs __iomem *hwp_regs;
	काष्ठा fman_kg_regs __iomem *kg_regs;
	fman_exceptions_cb *exception_cb;
	fman_bus_error_cb *bus_error_cb;
	/* Spinlock क्रम FMan use */
	spinlock_t spinlock;
	काष्ठा fman_state_काष्ठा *state;

	काष्ठा fman_cfg *cfg;
	काष्ठा muram_info *muram;
	काष्ठा fman_keygen *keygen;
	/* cam section in muram */
	अचिन्हित दीर्घ cam_offset;
	माप_प्रकार cam_size;
	/* Fअगरo in MURAM */
	अचिन्हित दीर्घ fअगरo_offset;
	माप_प्रकार fअगरo_size;

	u32 liodn_base[64];
	u32 liodn_offset[64];

	काष्ठा fman_dts_params dts_params;
पूर्ण;

/* Structure क्रम port-FM communication during fman_port_init. */
काष्ठा fman_port_init_params अणु
	u8 port_id;			/* port Id */
	क्रमागत fman_port_type port_type;	/* Port type */
	u16 port_speed;			/* Port speed */
	u16 liodn_offset;		/* Port's requested resource */
	u8 num_of_tasks;		/* Port's requested resource */
	u8 num_of_extra_tasks;		/* Port's requested resource */
	u8 num_of_खोलो_dmas;		/* Port's requested resource */
	u8 num_of_extra_खोलो_dmas;	/* Port's requested resource */
	u32 size_of_fअगरo;		/* Port's requested resource */
	u32 extra_size_of_fअगरo;		/* Port's requested resource */
	u8 deq_pipeline_depth;		/* Port's requested resource */
	u16 max_frame_length;		/* Port's max frame length. */
	u16 liodn_base;
	/* LIODN base क्रम this port, to be used together with LIODN offset. */
पूर्ण;

व्योम fman_get_revision(काष्ठा fman *fman, काष्ठा fman_rev_info *rev_info);

व्योम fman_रेजिस्टर_पूर्णांकr(काष्ठा fman *fman, क्रमागत fman_event_modules mod,
			u8 mod_id, क्रमागत fman_पूर्णांकr_type पूर्णांकr_type,
			व्योम (*f_isr)(व्योम *h_src_arg), व्योम *h_src_arg);

व्योम fman_unरेजिस्टर_पूर्णांकr(काष्ठा fman *fman, क्रमागत fman_event_modules mod,
			  u8 mod_id, क्रमागत fman_पूर्णांकr_type पूर्णांकr_type);

पूर्णांक fman_set_port_params(काष्ठा fman *fman,
			 काष्ठा fman_port_init_params *port_params);

पूर्णांक fman_reset_mac(काष्ठा fman *fman, u8 mac_id);

u16 fman_get_घड़ी_freq(काष्ठा fman *fman);

u32 fman_get_bmi_max_fअगरo_size(काष्ठा fman *fman);

पूर्णांक fman_set_mac_max_frame(काष्ठा fman *fman, u8 mac_id, u16 mfl);

u32 fman_get_qman_channel_id(काष्ठा fman *fman, u32 port_id);

काष्ठा resource *fman_get_mem_region(काष्ठा fman *fman);

u16 fman_get_max_frm(व्योम);

पूर्णांक fman_get_rx_extra_headroom(व्योम);

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
bool fman_has_errata_a050385(व्योम);
#पूर्ण_अगर

काष्ठा fman *fman_bind(काष्ठा device *dev);

#पूर्ण_अगर /* __FM_H */
