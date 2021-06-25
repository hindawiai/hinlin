<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#अगर_अघोषित _IDXD_REGISTERS_H_
#घोषणा _IDXD_REGISTERS_H_

/* PCI Config */
#घोषणा PCI_DEVICE_ID_INTEL_DSA_SPR0	0x0b25
#घोषणा PCI_DEVICE_ID_INTEL_IAX_SPR0	0x0cfe

#घोषणा IDXD_MMIO_BAR		0
#घोषणा IDXD_WQ_BAR		2
#घोषणा IDXD_PORTAL_SIZE	PAGE_SIZE

/* MMIO Device BAR0 Registers */
#घोषणा IDXD_VER_OFFSET			0x00
#घोषणा IDXD_VER_MAJOR_MASK		0xf0
#घोषणा IDXD_VER_MINOR_MASK		0x0f
#घोषणा GET_IDXD_VER_MAJOR(x)		(((x) & IDXD_VER_MAJOR_MASK) >> 4)
#घोषणा GET_IDXD_VER_MINOR(x)		((x) & IDXD_VER_MINOR_MASK)

जोड़ gen_cap_reg अणु
	काष्ठा अणु
		u64 block_on_fault:1;
		u64 overlap_copy:1;
		u64 cache_control_mem:1;
		u64 cache_control_cache:1;
		u64 cmd_cap:1;
		u64 rsvd:3;
		u64 dest_पढ़ोback:1;
		u64 drain_पढ़ोback:1;
		u64 rsvd2:6;
		u64 max_xfer_shअगरt:5;
		u64 max_batch_shअगरt:4;
		u64 max_ims_mult:6;
		u64 config_en:1;
		u64 max_descs_per_engine:8;
		u64 rsvd3:24;
	पूर्ण;
	u64 bits;
पूर्ण __packed;
#घोषणा IDXD_GENCAP_OFFSET		0x10

जोड़ wq_cap_reg अणु
	काष्ठा अणु
		u64 total_wq_size:16;
		u64 num_wqs:8;
		u64 wqcfg_size:4;
		u64 rsvd:20;
		u64 shared_mode:1;
		u64 dedicated_mode:1;
		u64 wq_ats_support:1;
		u64 priority:1;
		u64 occupancy:1;
		u64 occupancy_पूर्णांक:1;
		u64 rsvd3:10;
	पूर्ण;
	u64 bits;
पूर्ण __packed;
#घोषणा IDXD_WQCAP_OFFSET		0x20
#घोषणा IDXD_WQCFG_MIN			5

जोड़ group_cap_reg अणु
	काष्ठा अणु
		u64 num_groups:8;
		u64 total_tokens:8;
		u64 token_en:1;
		u64 token_limit:1;
		u64 rsvd:46;
	पूर्ण;
	u64 bits;
पूर्ण __packed;
#घोषणा IDXD_GRPCAP_OFFSET		0x30

जोड़ engine_cap_reg अणु
	काष्ठा अणु
		u64 num_engines:8;
		u64 rsvd:56;
	पूर्ण;
	u64 bits;
पूर्ण __packed;

#घोषणा IDXD_ENGCAP_OFFSET		0x38

#घोषणा IDXD_OPCAP_NOOP			0x0001
#घोषणा IDXD_OPCAP_BATCH			0x0002
#घोषणा IDXD_OPCAP_MEMMOVE		0x0008
काष्ठा opcap अणु
	u64 bits[4];
पूर्ण;

#घोषणा IDXD_OPCAP_OFFSET		0x40

#घोषणा IDXD_TABLE_OFFSET		0x60
जोड़ offsets_reg अणु
	काष्ठा अणु
		u64 grpcfg:16;
		u64 wqcfg:16;
		u64 msix_perm:16;
		u64 ims:16;
		u64 perfmon:16;
		u64 rsvd:48;
	पूर्ण;
	u64 bits[2];
पूर्ण __packed;

#घोषणा IDXD_TABLE_MULT			0x100

#घोषणा IDXD_GENCFG_OFFSET		0x80
जोड़ gencfg_reg अणु
	काष्ठा अणु
		u32 token_limit:8;
		u32 rsvd:4;
		u32 user_पूर्णांक_en:1;
		u32 rsvd2:19;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

#घोषणा IDXD_GENCTRL_OFFSET		0x88
जोड़ genctrl_reg अणु
	काष्ठा अणु
		u32 softerr_पूर्णांक_en:1;
		u32 halt_पूर्णांक_en:1;
		u32 rsvd:30;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

#घोषणा IDXD_GENSTATS_OFFSET		0x90
जोड़ gensts_reg अणु
	काष्ठा अणु
		u32 state:2;
		u32 reset_type:2;
		u32 rsvd:28;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

क्रमागत idxd_device_status_state अणु
	IDXD_DEVICE_STATE_DISABLED = 0,
	IDXD_DEVICE_STATE_ENABLED,
	IDXD_DEVICE_STATE_DRAIN,
	IDXD_DEVICE_STATE_HALT,
पूर्ण;

क्रमागत idxd_device_reset_type अणु
	IDXD_DEVICE_RESET_SOFTWARE = 0,
	IDXD_DEVICE_RESET_FLR,
	IDXD_DEVICE_RESET_WARM,
	IDXD_DEVICE_RESET_COLD,
पूर्ण;

#घोषणा IDXD_INTCAUSE_OFFSET		0x98
#घोषणा IDXD_INTC_ERR			0x01
#घोषणा IDXD_INTC_CMD			0x02
#घोषणा IDXD_INTC_OCCUPY			0x04
#घोषणा IDXD_INTC_PERFMON_OVFL		0x08

#घोषणा IDXD_CMD_OFFSET			0xa0
जोड़ idxd_command_reg अणु
	काष्ठा अणु
		u32 opeअक्रम:20;
		u32 cmd:5;
		u32 rsvd:6;
		u32 पूर्णांक_req:1;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

क्रमागत idxd_cmd अणु
	IDXD_CMD_ENABLE_DEVICE = 1,
	IDXD_CMD_DISABLE_DEVICE,
	IDXD_CMD_DRAIN_ALL,
	IDXD_CMD_ABORT_ALL,
	IDXD_CMD_RESET_DEVICE,
	IDXD_CMD_ENABLE_WQ,
	IDXD_CMD_DISABLE_WQ,
	IDXD_CMD_DRAIN_WQ,
	IDXD_CMD_ABORT_WQ,
	IDXD_CMD_RESET_WQ,
	IDXD_CMD_DRAIN_PASID,
	IDXD_CMD_ABORT_PASID,
	IDXD_CMD_REQUEST_INT_HANDLE,
	IDXD_CMD_RELEASE_INT_HANDLE,
पूर्ण;

#घोषणा CMD_INT_HANDLE_IMS		0x10000

#घोषणा IDXD_CMDSTS_OFFSET		0xa8
जोड़ cmdsts_reg अणु
	काष्ठा अणु
		u8 err;
		u16 result;
		u8 rsvd:7;
		u8 active:1;
	पूर्ण;
	u32 bits;
पूर्ण __packed;
#घोषणा IDXD_CMDSTS_ACTIVE		0x80000000
#घोषणा IDXD_CMDSTS_ERR_MASK		0xff
#घोषणा IDXD_CMDSTS_RES_SHIFT		8

क्रमागत idxd_cmdsts_err अणु
	IDXD_CMDSTS_SUCCESS = 0,
	IDXD_CMDSTS_INVAL_CMD,
	IDXD_CMDSTS_INVAL_WQIDX,
	IDXD_CMDSTS_HW_ERR,
	/* enable device errors */
	IDXD_CMDSTS_ERR_DEV_ENABLED = 0x10,
	IDXD_CMDSTS_ERR_CONFIG,
	IDXD_CMDSTS_ERR_BUSMASTER_EN,
	IDXD_CMDSTS_ERR_PASID_INVAL,
	IDXD_CMDSTS_ERR_WQ_SIZE_दुस्फल,
	IDXD_CMDSTS_ERR_GRP_CONFIG,
	IDXD_CMDSTS_ERR_GRP_CONFIG2,
	IDXD_CMDSTS_ERR_GRP_CONFIG3,
	IDXD_CMDSTS_ERR_GRP_CONFIG4,
	/* enable wq errors */
	IDXD_CMDSTS_ERR_DEV_NOTEN = 0x20,
	IDXD_CMDSTS_ERR_WQ_ENABLED,
	IDXD_CMDSTS_ERR_WQ_SIZE,
	IDXD_CMDSTS_ERR_WQ_PRIOR,
	IDXD_CMDSTS_ERR_WQ_MODE,
	IDXD_CMDSTS_ERR_BOF_EN,
	IDXD_CMDSTS_ERR_PASID_EN,
	IDXD_CMDSTS_ERR_MAX_BATCH_SIZE,
	IDXD_CMDSTS_ERR_MAX_XFER_SIZE,
	/* disable device errors */
	IDXD_CMDSTS_ERR_DIS_DEV_EN = 0x31,
	/* disable WQ, drain WQ, पात WQ, reset WQ */
	IDXD_CMDSTS_ERR_DEV_NOT_EN,
	/* request पूर्णांकerrupt handle */
	IDXD_CMDSTS_ERR_INVAL_INT_IDX = 0x41,
	IDXD_CMDSTS_ERR_NO_HANDLE,
पूर्ण;

#घोषणा IDXD_CMDCAP_OFFSET		0xb0

#घोषणा IDXD_SWERR_OFFSET		0xc0
#घोषणा IDXD_SWERR_VALID		0x00000001
#घोषणा IDXD_SWERR_OVERFLOW		0x00000002
#घोषणा IDXD_SWERR_ACK			(IDXD_SWERR_VALID | IDXD_SWERR_OVERFLOW)
जोड़ sw_err_reg अणु
	काष्ठा अणु
		u64 valid:1;
		u64 overflow:1;
		u64 desc_valid:1;
		u64 wq_idx_valid:1;
		u64 batch:1;
		u64 fault_rw:1;
		u64 priv:1;
		u64 rsvd:1;
		u64 error:8;
		u64 wq_idx:8;
		u64 rsvd2:8;
		u64 operation:8;
		u64 pasid:20;
		u64 rsvd3:4;

		u64 batch_idx:16;
		u64 rsvd4:16;
		u64 invalid_flags:32;

		u64 fault_addr;

		u64 rsvd5;
	पूर्ण;
	u64 bits[4];
पूर्ण __packed;

जोड़ msix_perm अणु
	काष्ठा अणु
		u32 rsvd:2;
		u32 ignore:1;
		u32 pasid_en:1;
		u32 rsvd2:8;
		u32 pasid:20;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

जोड़ group_flags अणु
	काष्ठा अणु
		u32 tc_a:3;
		u32 tc_b:3;
		u32 rsvd:1;
		u32 use_token_limit:1;
		u32 tokens_reserved:8;
		u32 rsvd2:4;
		u32 tokens_allowed:8;
		u32 rsvd3:4;
	पूर्ण;
	u32 bits;
पूर्ण __packed;

काष्ठा grpcfg अणु
	u64 wqs[4];
	u64 engines;
	जोड़ group_flags flags;
पूर्ण __packed;

जोड़ wqcfg अणु
	काष्ठा अणु
		/* bytes 0-3 */
		u16 wq_size;
		u16 rsvd;

		/* bytes 4-7 */
		u16 wq_thresh;
		u16 rsvd1;

		/* bytes 8-11 */
		u32 mode:1;	/* shared or dedicated */
		u32 bof:1;	/* block on fault */
		u32 wq_ats_disable:1;
		u32 rsvd2:1;
		u32 priority:4;
		u32 pasid:20;
		u32 pasid_en:1;
		u32 priv:1;
		u32 rsvd3:2;

		/* bytes 12-15 */
		u32 max_xfer_shअगरt:5;
		u32 max_batch_shअगरt:4;
		u32 rsvd4:23;

		/* bytes 16-19 */
		u16 occupancy_पूर्णांकh;
		u16 occupancy_table_sel:1;
		u16 rsvd5:15;

		/* bytes 20-23 */
		u16 occupancy_limit;
		u16 occupancy_पूर्णांक_en:1;
		u16 rsvd6:15;

		/* bytes 24-27 */
		u16 occupancy;
		u16 occupancy_पूर्णांक:1;
		u16 rsvd7:12;
		u16 mode_support:1;
		u16 wq_state:2;

		/* bytes 28-31 */
		u32 rsvd8;
	पूर्ण;
	u32 bits[8];
पूर्ण __packed;

#घोषणा WQCFG_PASID_IDX                2

/*
 * This macro calculates the offset पूर्णांकo the WQCFG रेजिस्टर
 * idxd - काष्ठा idxd *
 * n - wq id
 * ofs - the index of the 32b dword क्रम the config रेजिस्टर
 *
 * The WQCFG रेजिस्टर block is भागided पूर्णांकo groups per each wq. The n index
 * allows us to move to the रेजिस्टर group that's क्रम that particular wq.
 * Each रेजिस्टर is 32bits. The ofs gives us the number of रेजिस्टर to access.
 */
#घोषणा WQCFG_OFFSET(_idxd_dev, n, ofs) \
(अणु\
	typeof(_idxd_dev) __idxd_dev = (_idxd_dev);	\
	(__idxd_dev)->wqcfg_offset + (n) * (__idxd_dev)->wqcfg_size + माप(u32) * (ofs);	\
पूर्ण)

#घोषणा WQCFG_STRIDES(_idxd_dev) ((_idxd_dev)->wqcfg_size / माप(u32))

#घोषणा GRPCFG_SIZE		64
#घोषणा GRPWQCFG_STRIDES	4

/*
 * This macro calculates the offset पूर्णांकo the GRPCFG रेजिस्टर
 * idxd - काष्ठा idxd *
 * n - wq id
 * ofs - the index of the 32b dword क्रम the config रेजिस्टर
 *
 * The WQCFG रेजिस्टर block is भागided पूर्णांकo groups per each wq. The n index
 * allows us to move to the रेजिस्टर group that's क्रम that particular wq.
 * Each रेजिस्टर is 32bits. The ofs gives us the number of रेजिस्टर to access.
 */
#घोषणा GRPWQCFG_OFFSET(idxd_dev, n, ofs) ((idxd_dev)->grpcfg_offset +\
					   (n) * GRPCFG_SIZE + माप(u64) * (ofs))
#घोषणा GRPENGCFG_OFFSET(idxd_dev, n) ((idxd_dev)->grpcfg_offset + (n) * GRPCFG_SIZE + 32)
#घोषणा GRPFLGCFG_OFFSET(idxd_dev, n) ((idxd_dev)->grpcfg_offset + (n) * GRPCFG_SIZE + 40)

/* Following is perक्रमmance monitor रेजिस्टरs */
#घोषणा IDXD_PERFCAP_OFFSET		0x0
जोड़ idxd_perfcap अणु
	काष्ठा अणु
		u64 num_perf_counter:6;
		u64 rsvd1:2;
		u64 counter_width:8;
		u64 num_event_category:4;
		u64 global_event_category:16;
		u64 filter:8;
		u64 rsvd2:8;
		u64 cap_per_counter:1;
		u64 ग_लिखोable_counter:1;
		u64 counter_मुक्तze:1;
		u64 overflow_पूर्णांकerrupt:1;
		u64 rsvd3:8;
	पूर्ण;
	u64 bits;
पूर्ण __packed;

#घोषणा IDXD_EVNTCAP_OFFSET		0x80
जोड़ idxd_evntcap अणु
	काष्ठा अणु
		u64 events:28;
		u64 rsvd:36;
	पूर्ण;
	u64 bits;
पूर्ण __packed;

काष्ठा idxd_event अणु
	जोड़ अणु
		काष्ठा अणु
			u32 event_category:4;
			u32 events:28;
		पूर्ण;
		u32 val;
	पूर्ण;
पूर्ण __packed;

#घोषणा IDXD_CNTRCAP_OFFSET		0x800
काष्ठा idxd_cntrcap अणु
	जोड़ अणु
		काष्ठा अणु
			u32 counter_width:8;
			u32 rsvd:20;
			u32 num_events:4;
		पूर्ण;
		u32 val;
	पूर्ण;
	काष्ठा idxd_event events[];
पूर्ण __packed;

#घोषणा IDXD_PERFRST_OFFSET		0x10
जोड़ idxd_perfrst अणु
	काष्ठा अणु
		u32 perfrst_config:1;
		u32 perfrst_counter:1;
		u32 rsvd:30;
	पूर्ण;
	u32 val;
पूर्ण __packed;

#घोषणा IDXD_OVFSTATUS_OFFSET		0x30
#घोषणा IDXD_PERFFRZ_OFFSET		0x20
#घोषणा IDXD_CNTRCFG_OFFSET		0x100
जोड़ idxd_cntrcfg अणु
	काष्ठा अणु
		u64 enable:1;
		u64 पूर्णांकerrupt_ovf:1;
		u64 global_मुक्तze_ovf:1;
		u64 rsvd1:5;
		u64 event_category:4;
		u64 rsvd2:20;
		u64 events:28;
		u64 rsvd3:4;
	पूर्ण;
	u64 val;
पूर्ण __packed;

#घोषणा IDXD_FLTCFG_OFFSET		0x300

#घोषणा IDXD_CNTRDATA_OFFSET		0x200
जोड़ idxd_cntrdata अणु
	काष्ठा अणु
		u64 event_count_value;
	पूर्ण;
	u64 val;
पूर्ण __packed;

जोड़ event_cfg अणु
	काष्ठा अणु
		u64 event_cat:4;
		u64 event_enc:28;
	पूर्ण;
	u64 val;
पूर्ण __packed;

जोड़ filter_cfg अणु
	काष्ठा अणु
		u64 wq:32;
		u64 tc:8;
		u64 pg_sz:4;
		u64 xfer_sz:8;
		u64 eng:8;
	पूर्ण;
	u64 val;
पूर्ण __packed;

#पूर्ण_अगर
