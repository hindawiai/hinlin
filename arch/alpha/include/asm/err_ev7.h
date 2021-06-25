<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_ERR_EV7_H
#घोषणा __ALPHA_ERR_EV7_H 1

/*
 * Data क्रम el packet class PAL (14), type LOGOUT_FRAME (1)
 */
काष्ठा ev7_pal_logout_subpacket अणु
	u32 mchk_code;
	u32 subpacket_count;
	u64 whami;
	u64 rbox_whami;
	u64 rbox_पूर्णांक;
	u64 exc_addr;
	जोड़ el_बारtamp बारtamp;
	u64 halt_code;
	u64 reserved;
पूर्ण;

/*
 * Data क्रम el packet class PAL (14), type EV7_PROCESSOR (4)
 */
काष्ठा ev7_pal_processor_subpacket अणु
	u64 i_stat;
	u64 dc_stat;
	u64 c_addr;
	u64 c_syndrome_1;
	u64 c_syndrome_0;
	u64 c_stat;
	u64 c_sts;
	u64 mm_stat;
	u64 exc_addr;
	u64 ier_cm;
	u64 isum;
	u64 pal_base;
	u64 i_ctl;
	u64 process_context;
	u64 cbox_ctl;
	u64 cbox_stp_ctl;
	u64 cbox_acc_ctl;
	u64 cbox_lcl_set;
	u64 cbox_gbl_set;
	u64 bbox_ctl;
	u64 bbox_err_sts;
	u64 bbox_err_idx;
	u64 cbox_ddp_err_sts;
	u64 bbox_dat_rmp;
	u64 reserved[2];
पूर्ण;

/*
 * Data क्रम el packet class PAL (14), type EV7_ZBOX (5)
 */
काष्ठा ev7_pal_zbox_subpacket अणु
	u32 zbox0_dram_err_status_1;
	u32 zbox0_dram_err_status_2;
	u32 zbox0_dram_err_status_3;
	u32 zbox0_dram_err_ctl;
	u32 zbox0_dram_err_adr;
	u32 zbox0_dअगरt_समयout;
	u32 zbox0_dram_mapper_ctl;
	u32 zbox0_frc_err_adr;
	u32 zbox0_dअगरt_err_status;
	u32 reserved1;
	u32 zbox1_dram_err_status_1;
	u32 zbox1_dram_err_status_2;
	u32 zbox1_dram_err_status_3;
	u32 zbox1_dram_err_ctl;
	u32 zbox1_dram_err_adr;
	u32 zbox1_dअगरt_समयout;
	u32 zbox1_dram_mapper_ctl;
	u32 zbox1_frc_err_adr;
	u32 zbox1_dअगरt_err_status;
	u32 reserved2;
	u64 cbox_ctl;
	u64 cbox_stp_ctl;
	u64 zbox0_error_pa;
	u64 zbox1_error_pa;
	u64 zbox0_ored_syndrome;
	u64 zbox1_ored_syndrome;
	u64 reserved3[2];
पूर्ण;

/*
 * Data क्रम el packet class PAL (14), type EV7_RBOX (6)
 */
काष्ठा ev7_pal_rbox_subpacket अणु
	u64 rbox_cfg;
	u64 rbox_n_cfg;
	u64 rbox_s_cfg;
	u64 rbox_e_cfg;
	u64 rbox_w_cfg;
	u64 rbox_n_err;
	u64 rbox_s_err;
	u64 rbox_e_err;
	u64 rbox_w_err;
	u64 rbox_io_cfg;
	u64 rbox_io_err;
	u64 rbox_l_err;
	u64 rbox_whoami;
	u64 rbox_imask;
	u64 rbox_पूर्णांकq;
	u64 rbox_पूर्णांक;
	u64 reserved[2];
पूर्ण;

/*
 * Data क्रम el packet class PAL (14), type EV7_IO (7)
 */
काष्ठा ev7_pal_io_one_port अणु
	u64 pox_err_sum;
	u64 pox_tlb_err;
	u64 pox_spl_cmplt;
	u64 pox_trans_sum;
	u64 pox_first_err;
	u64 pox_mult_err;
	u64 pox_dm_source;
	u64 pox_dm_dest;
	u64 pox_dm_size;
	u64 pox_dm_ctrl;
	u64 reserved;
पूर्ण;

काष्ठा ev7_pal_io_subpacket अणु
	u64 io_asic_rev;
	u64 io_sys_rev;
	u64 io7_uph;
	u64 hpi_ctl;
	u64 crd_ctl;
	u64 hei_ctl;
	u64 po7_error_sum;
	u64 po7_uncrr_sym;
	u64 po7_crrct_sym;
	u64 po7_ugbge_sym;
	u64 po7_err_pkt0;
	u64 po7_err_pkt1;
	u64 reserved[2];
	काष्ठा ev7_pal_io_one_port ports[4];
पूर्ण;

/*
 * Environmental subpacket. Data used क्रम el packets:
 * 	   class PAL (14), type AMBIENT_TEMPERATURE (10)
 * 	   class PAL (14), type AIRMOVER_FAN (11)
 * 	   class PAL (14), type VOLTAGE (12)
 * 	   class PAL (14), type INTRUSION (13)
 *	   class PAL (14), type POWER_SUPPLY (14)
 *	   class PAL (14), type LAN (15)
 *	   class PAL (14), type HOT_PLUG (16)
 */
काष्ठा ev7_pal_environmental_subpacket अणु
	u16 cabinet;
	u16 drawer;
	u16 reserved1[2];
	u8 module_type;
	u8 unit_id;		/* unit reporting condition */
	u8 reserved2;
	u8 condition;		/* condition reported       */
पूर्ण;

/*
 * Convert environmental type to index
 */
अटल अंतरभूत पूर्णांक ev7_lf_env_index(पूर्णांक type)
अणु
	BUG_ON((type < EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE) 
	       || (type > EL_TYPE__PAL__ENV__HOT_PLUG));

	वापस type - EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE;
पूर्ण

/*
 * Data क्रम generic el packet class PAL.
 */
काष्ठा ev7_pal_subpacket अणु
	जोड़ अणु
		काष्ठा ev7_pal_logout_subpacket logout;	     /* Type     1 */
		काष्ठा ev7_pal_processor_subpacket ev7;	     /* Type     4 */
		काष्ठा ev7_pal_zbox_subpacket zbox;	     /* Type     5 */
		काष्ठा ev7_pal_rbox_subpacket rbox;	     /* Type     6 */
		काष्ठा ev7_pal_io_subpacket io;		     /* Type     7 */
		काष्ठा ev7_pal_environmental_subpacket env;  /* Type 10-16 */
		u64 as_quad[1];				     /* Raw u64    */
	पूर्ण by_type;
पूर्ण;

/*
 * Struct to contain collected logout from subpackets.
 */
काष्ठा ev7_lf_subpackets अणु
	काष्ठा ev7_pal_logout_subpacket *logout;		/* Type  1 */
	काष्ठा ev7_pal_processor_subpacket *ev7;		/* Type  4 */
	काष्ठा ev7_pal_zbox_subpacket *zbox;			/* Type  5 */
	काष्ठा ev7_pal_rbox_subpacket *rbox;			/* Type  6 */
	काष्ठा ev7_pal_io_subpacket *io;			/* Type  7 */
	काष्ठा ev7_pal_environmental_subpacket *env[7];	     /* Type 10-16 */

	अचिन्हित पूर्णांक io_pid;
पूर्ण;

#पूर्ण_अगर /* __ALPHA_ERR_EV7_H */


