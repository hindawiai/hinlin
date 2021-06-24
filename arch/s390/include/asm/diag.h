<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * s390 diagnose functions
 *
 * Copyright IBM Corp. 2007
 * Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_DIAG_H
#घोषणा _ASM_S390_DIAG_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/percpu.h>

क्रमागत diag_stat_क्रमागत अणु
	DIAG_STAT_X008,
	DIAG_STAT_X00C,
	DIAG_STAT_X010,
	DIAG_STAT_X014,
	DIAG_STAT_X044,
	DIAG_STAT_X064,
	DIAG_STAT_X09C,
	DIAG_STAT_X0DC,
	DIAG_STAT_X204,
	DIAG_STAT_X210,
	DIAG_STAT_X224,
	DIAG_STAT_X250,
	DIAG_STAT_X258,
	DIAG_STAT_X26C,
	DIAG_STAT_X288,
	DIAG_STAT_X2C4,
	DIAG_STAT_X2FC,
	DIAG_STAT_X304,
	DIAG_STAT_X308,
	DIAG_STAT_X318,
	DIAG_STAT_X500,
	NR_DIAG_STAT
पूर्ण;

व्योम diag_stat_inc(क्रमागत diag_stat_क्रमागत nr);
व्योम diag_stat_inc_norecursion(क्रमागत diag_stat_क्रमागत nr);

/*
 * Diagnose 10: Release page range
 */
अटल अंतरभूत व्योम diag10_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ num_pfn)
अणु
	अचिन्हित दीर्घ start_addr, end_addr;

	start_addr = start_pfn << PAGE_SHIFT;
	end_addr = (start_pfn + num_pfn - 1) << PAGE_SHIFT;

	diag_stat_inc(DIAG_STAT_X010);
	यंत्र अस्थिर(
		"0:	diag	%0,%1,0x10\n"
		"1:	nopr	%%r7\n"
		EX_TABLE(0b, 1b)
		EX_TABLE(1b, 1b)
		: : "a" (start_addr), "a" (end_addr));
पूर्ण

/*
 * Diagnose 14: Input spool file manipulation
 */
बाह्य पूर्णांक diag14(अचिन्हित दीर्घ rx, अचिन्हित दीर्घ ry1, अचिन्हित दीर्घ subcode);

/*
 * Diagnose 210: Get inक्रमmation about a भव device
 */
काष्ठा diag210 अणु
	u16 vrdcdvno;	/* device number (input) */
	u16 vrdclen;	/* data block length (input) */
	u8 vrdcvcla;	/* भव device class (output) */
	u8 vrdcvtyp;	/* भव device type (output) */
	u8 vrdcvsta;	/* भव device status (output) */
	u8 vrdcvfla;	/* भव device flags (output) */
	u8 vrdcrccl;	/* real device class (output) */
	u8 vrdccrty;	/* real device type (output) */
	u8 vrdccrmd;	/* real device model (output) */
	u8 vrdccrft;	/* real device feature (output) */
पूर्ण __attribute__((packed, aligned(4)));

बाह्य पूर्णांक diag210(काष्ठा diag210 *addr);

/* bit is set in flags, when physical cpu info is included in diag 204 data */
#घोषणा DIAG204_LPAR_PHYS_FLG 0x80
#घोषणा DIAG204_LPAR_NAME_LEN 8		/* lpar name len in diag 204 data */
#घोषणा DIAG204_CPU_NAME_LEN 16		/* type name len of cpus in diag224 name table */

/* diag 204 subcodes */
क्रमागत diag204_sc अणु
	DIAG204_SUBC_STIB4 = 4,
	DIAG204_SUBC_RSI = 5,
	DIAG204_SUBC_STIB6 = 6,
	DIAG204_SUBC_STIB7 = 7
पूर्ण;

/* The two available diag 204 data क्रमmats */
क्रमागत diag204_क्रमmat अणु
	DIAG204_INFO_SIMPLE = 0,
	DIAG204_INFO_EXT = 0x00010000
पूर्ण;

क्रमागत diag204_cpu_flags अणु
	DIAG204_CPU_ONLINE = 0x20,
	DIAG204_CPU_CAPPED = 0x40,
पूर्ण;

काष्ठा diag204_info_blk_hdr अणु
	__u8  npar;
	__u8  flags;
	__u16 tslice;
	__u16 phys_cpus;
	__u16 this_part;
	__u64 curtod;
पूर्ण __packed;

काष्ठा diag204_x_info_blk_hdr अणु
	__u8  npar;
	__u8  flags;
	__u16 tslice;
	__u16 phys_cpus;
	__u16 this_part;
	__u64 curtod1;
	__u64 curtod2;
	अक्षर reserved[40];
पूर्ण __packed;

काष्ठा diag204_part_hdr अणु
	__u8 pn;
	__u8 cpus;
	अक्षर reserved[6];
	अक्षर part_name[DIAG204_LPAR_NAME_LEN];
पूर्ण __packed;

काष्ठा diag204_x_part_hdr अणु
	__u8  pn;
	__u8  cpus;
	__u8  rcpus;
	__u8  pflag;
	__u32 mlu;
	अक्षर  part_name[DIAG204_LPAR_NAME_LEN];
	अक्षर  lpc_name[8];
	अक्षर  os_name[8];
	__u64 online_cs;
	__u64 online_es;
	__u8  upid;
	__u8  reserved:3;
	__u8  mtid:5;
	अक्षर  reserved1[2];
	__u32 group_mlu;
	अक्षर  group_name[8];
	अक्षर  hardware_group_name[8];
	अक्षर  reserved2[24];
पूर्ण __packed;

काष्ठा diag204_cpu_info अणु
	__u16 cpu_addr;
	अक्षर  reserved1[2];
	__u8  ctidx;
	__u8  cflag;
	__u16 weight;
	__u64 acc_समय;
	__u64 lp_समय;
पूर्ण __packed;

काष्ठा diag204_x_cpu_info अणु
	__u16 cpu_addr;
	अक्षर  reserved1[2];
	__u8  ctidx;
	__u8  cflag;
	__u16 weight;
	__u64 acc_समय;
	__u64 lp_समय;
	__u16 min_weight;
	__u16 cur_weight;
	__u16 max_weight;
	अक्षर  reseved2[2];
	__u64 online_समय;
	__u64 रुको_समय;
	__u32 pma_weight;
	__u32 polar_weight;
	__u32 cpu_type_cap;
	__u32 group_cpu_type_cap;
	अक्षर  reserved3[32];
पूर्ण __packed;

काष्ठा diag204_phys_hdr अणु
	अक्षर reserved1[1];
	__u8 cpus;
	अक्षर reserved2[6];
	अक्षर mgm_name[8];
पूर्ण __packed;

काष्ठा diag204_x_phys_hdr अणु
	अक्षर reserved1[1];
	__u8 cpus;
	अक्षर reserved2[6];
	अक्षर mgm_name[8];
	अक्षर reserved3[80];
पूर्ण __packed;

काष्ठा diag204_phys_cpu अणु
	__u16 cpu_addr;
	अक्षर  reserved1[2];
	__u8  ctidx;
	अक्षर  reserved2[3];
	__u64 mgm_समय;
	अक्षर  reserved3[8];
पूर्ण __packed;

काष्ठा diag204_x_phys_cpu अणु
	__u16 cpu_addr;
	अक्षर  reserved1[2];
	__u8  ctidx;
	अक्षर  reserved2[1];
	__u16 weight;
	__u64 mgm_समय;
	अक्षर  reserved3[80];
पूर्ण __packed;

काष्ठा diag204_x_part_block अणु
	काष्ठा diag204_x_part_hdr hdr;
	काष्ठा diag204_x_cpu_info cpus[];
पूर्ण __packed;

काष्ठा diag204_x_phys_block अणु
	काष्ठा diag204_x_phys_hdr hdr;
	काष्ठा diag204_x_phys_cpu cpus[];
पूर्ण __packed;

क्रमागत diag26c_sc अणु
	DIAG26C_PORT_VNIC    = 0x00000024,
	DIAG26C_MAC_SERVICES = 0x00000030
पूर्ण;

क्रमागत diag26c_version अणु
	DIAG26C_VERSION2	 = 0x00000002,	/* z/VM 5.4.0 */
	DIAG26C_VERSION6_VM65918 = 0x00020006	/* z/VM 6.4.0 + VM65918 */
पूर्ण;

#घोषणा DIAG26C_VNIC_INFO	0x0002
काष्ठा diag26c_vnic_req अणु
	u32	resp_buf_len;
	u32	resp_version;
	u16	req_क्रमmat;
	u16	vlan_id;
	u64	sys_name;
	u8	res[2];
	u16	devno;
पूर्ण __packed __aligned(8);

#घोषणा VNIC_INFO_PROT_L3	1
#घोषणा VNIC_INFO_PROT_L2	2
/* Note: this is the bare minimum, use it क्रम uninitialized VNICs only. */
काष्ठा diag26c_vnic_resp अणु
	u32	version;
	u32	entry_cnt;
	/* VNIC info: */
	u32	next_entry;
	u64	owner;
	u16	devno;
	u8	status;
	u8	type;
	u64	lan_owner;
	u64	lan_name;
	u64	port_name;
	u8	port_type;
	u8	ext_status:6;
	u8	protocol:2;
	u16	base_devno;
	u32	port_num;
	u32	अगरindex;
	u32	maxinfo;
	u32	dev_count;
	/* 3x device info: */
	u8	dev_info1[28];
	u8	dev_info2[28];
	u8	dev_info3[28];
पूर्ण __packed __aligned(8);

#घोषणा DIAG26C_GET_MAC	0x0000
काष्ठा diag26c_mac_req अणु
	u32	resp_buf_len;
	u32	resp_version;
	u16	op_code;
	u16	devno;
	u8	res[4];
पूर्ण;

काष्ठा diag26c_mac_resp अणु
	u32	version;
	u8	mac[ETH_ALEN];
	u8	res[2];
पूर्ण __aligned(8);

#घोषणा CPNC_LINUX		0x4
जोड़ diag318_info अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ cpnc : 8;
		अचिन्हित दीर्घ cpvc : 56;
	पूर्ण;
पूर्ण;

पूर्णांक diag204(अचिन्हित दीर्घ subcode, अचिन्हित दीर्घ size, व्योम *addr);
पूर्णांक diag224(व्योम *ptr);
पूर्णांक diag26c(व्योम *req, व्योम *resp, क्रमागत diag26c_sc subcode);

काष्ठा hypfs_diag0c_entry;

काष्ठा diag_ops अणु
	पूर्णांक (*diag210)(काष्ठा diag210 *addr);
	पूर्णांक (*diag26c)(व्योम *req, व्योम *resp, क्रमागत diag26c_sc subcode);
	पूर्णांक (*diag14)(अचिन्हित दीर्घ rx, अचिन्हित दीर्घ ry1, अचिन्हित दीर्घ subcode);
	व्योम (*diag0c)(काष्ठा hypfs_diag0c_entry *entry);
	व्योम (*diag308_reset)(व्योम);
पूर्ण;

बाह्य काष्ठा diag_ops diag_dma_ops;
बाह्य काष्ठा diag210 *__diag210_पंचांगp_dma;
#पूर्ण_अगर /* _ASM_S390_DIAG_H */
