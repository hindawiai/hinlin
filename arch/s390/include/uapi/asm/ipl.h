<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_S390_UAPI_IPL_H
#घोषणा _ASM_S390_UAPI_IPL_H

#समावेश <linux/types.h>

/* IPL Parameter List header */
काष्ठा ipl_pl_hdr अणु
	__u32 len;
	__u8  flags;
	__u8  reserved1[2];
	__u8  version;
पूर्ण __packed;

#घोषणा IPL_PL_FLAG_IPLPS	0x80
#घोषणा IPL_PL_FLAG_SIPL	0x40
#घोषणा IPL_PL_FLAG_IPLSR	0x20

/* IPL Parameter Block header */
काष्ठा ipl_pb_hdr अणु
	__u32 len;
	__u8  pbt;
पूर्ण __packed;

/* IPL Parameter Block types */
क्रमागत ipl_pbt अणु
	IPL_PBT_FCP = 0,
	IPL_PBT_SCP_DATA = 1,
	IPL_PBT_CCW = 2,
	IPL_PBT_NVME = 4,
पूर्ण;

/* IPL Parameter Block 0 with common fields */
काष्ठा ipl_pb0_common अणु
	__u32 len;
	__u8  pbt;
	__u8  flags;
	__u8  reserved1[2];
	__u8  loadparm[8];
	__u8  reserved2[84];
पूर्ण __packed;

#घोषणा IPL_PB0_FLAG_LOADPARM	0x80

/* IPL Parameter Block 0 क्रम FCP */
काष्ठा ipl_pb0_fcp अणु
	__u32 len;
	__u8  pbt;
	__u8  reserved1[3];
	__u8  loadparm[8];
	__u8  reserved2[304];
	__u8  opt;
	__u8  reserved3[3];
	__u8  cssid;
	__u8  reserved4[1];
	__u16 devno;
	__u8  reserved5[4];
	__u64 wwpn;
	__u64 lun;
	__u32 bootprog;
	__u8  reserved6[12];
	__u64 br_lba;
	__u32 scp_data_len;
	__u8  reserved7[260];
	__u8  scp_data[];
पूर्ण __packed;

#घोषणा IPL_PB0_FCP_OPT_IPL	0x10
#घोषणा IPL_PB0_FCP_OPT_DUMP	0x20

/* IPL Parameter Block 0 क्रम NVMe */
काष्ठा ipl_pb0_nvme अणु
	__u32 len;
	__u8  pbt;
	__u8  reserved1[3];
	__u8  loadparm[8];
	__u8  reserved2[304];
	__u8  opt;
	__u8  reserved3[3];
	__u32 fid;
	__u8 reserved4[12];
	__u32 nsid;
	__u8 reserved5[4];
	__u32 bootprog;
	__u8 reserved6[12];
	__u64 br_lba;
	__u32 scp_data_len;
	__u8  reserved7[260];
	__u8  scp_data[];
पूर्ण __packed;

#घोषणा IPL_PB0_NVME_OPT_IPL	0x10
#घोषणा IPL_PB0_NVME_OPT_DUMP	0x20

/* IPL Parameter Block 0 क्रम CCW */
काष्ठा ipl_pb0_ccw अणु
	__u32 len;
	__u8  pbt;
	__u8  flags;
	__u8  reserved1[2];
	__u8  loadparm[8];
	__u8  reserved2[84];
	__u16 reserved3 : 13;
	__u8  ssid : 3;
	__u16 devno;
	__u8  vm_flags;
	__u8  reserved4[3];
	__u32 vm_parm_len;
	__u8  nss_name[8];
	__u8  vm_parm[64];
	__u8  reserved5[8];
पूर्ण __packed;

#घोषणा IPL_PB0_CCW_VM_FLAG_NSS		0x80
#घोषणा IPL_PB0_CCW_VM_FLAG_VP		0x40

/* IPL Parameter Block 1 क्रम additional SCP data */
काष्ठा ipl_pb1_scp_data अणु
	__u32 len;
	__u8  pbt;
	__u8  scp_data[];
पूर्ण __packed;

/* IPL Report List header */
काष्ठा ipl_rl_hdr अणु
	__u32 len;
	__u8  flags;
	__u8  reserved1[2];
	__u8  version;
	__u8  reserved2[8];
पूर्ण __packed;

/* IPL Report Block header */
काष्ठा ipl_rb_hdr अणु
	__u32 len;
	__u8  rbt;
	__u8  reserved1[11];
पूर्ण __packed;

/* IPL Report Block types */
क्रमागत ipl_rbt अणु
	IPL_RBT_CERTIFICATES = 1,
	IPL_RBT_COMPONENTS = 2,
पूर्ण;

/* IPL Report Block क्रम the certअगरicate list */
काष्ठा ipl_rb_certअगरicate_entry अणु
	__u64 addr;
	__u64 len;
पूर्ण __packed;

काष्ठा ipl_rb_certअगरicates अणु
	__u32 len;
	__u8  rbt;
	__u8  reserved1[11];
	काष्ठा ipl_rb_certअगरicate_entry entries[];
पूर्ण __packed;

/* IPL Report Block क्रम the component list */
काष्ठा ipl_rb_component_entry अणु
	__u64 addr;
	__u64 len;
	__u8  flags;
	__u8  reserved1[5];
	__u16 certअगरicate_index;
	__u8  reserved2[8];
पूर्ण;

#घोषणा IPL_RB_COMPONENT_FLAG_SIGNED	0x80
#घोषणा IPL_RB_COMPONENT_FLAG_VERIFIED	0x40

काष्ठा ipl_rb_components अणु
	__u32 len;
	__u8  rbt;
	__u8  reserved1[11];
	काष्ठा ipl_rb_component_entry entries[];
पूर्ण __packed;

#पूर्ण_अगर
