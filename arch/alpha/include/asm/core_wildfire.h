<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_WILDFIRE__H__
#घोषणा __ALPHA_WILDFIRE__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

#घोषणा WILDFIRE_MAX_QBB	8	/* more than 8 requires other mods */
#घोषणा WILDFIRE_PCA_PER_QBB	4
#घोषणा WILDFIRE_IRQ_PER_PCA	64

#घोषणा WILDFIRE_NR_IRQS \
  (WILDFIRE_MAX_QBB * WILDFIRE_PCA_PER_QBB * WILDFIRE_IRQ_PER_PCA)

बाह्य अचिन्हित अक्षर wildfire_hard_qbb_map[WILDFIRE_MAX_QBB];
बाह्य अचिन्हित अक्षर wildfire_soft_qbb_map[WILDFIRE_MAX_QBB];
#घोषणा QBB_MAP_EMPTY	0xff

बाह्य अचिन्हित दीर्घ wildfire_hard_qbb_mask;
बाह्य अचिन्हित दीर्घ wildfire_soft_qbb_mask;
बाह्य अचिन्हित दीर्घ wildfire_gp_mask;
बाह्य अचिन्हित दीर्घ wildfire_hs_mask;
बाह्य अचिन्हित दीर्घ wildfire_iop_mask;
बाह्य अचिन्हित दीर्घ wildfire_ior_mask;
बाह्य अचिन्हित दीर्घ wildfire_pca_mask;
बाह्य अचिन्हित दीर्घ wildfire_cpu_mask;
बाह्य अचिन्हित दीर्घ wildfire_mem_mask;

#घोषणा WILDFIRE_QBB_EXISTS(qbbno) (wildfire_soft_qbb_mask & (1 << (qbbno)))

#घोषणा WILDFIRE_MEM_EXISTS(qbbno) (wildfire_mem_mask & (0xf << ((qbbno) << 2)))

#घोषणा WILDFIRE_PCA_EXISTS(qbbno, pcano) \
		(wildfire_pca_mask & (1 << (((qbbno) << 2) + (pcano))))

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(64)));
पूर्ण wildfire_64;

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(256)));
पूर्ण wildfire_256;

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(2048)));
पूर्ण wildfire_2k;

प्रकार काष्ठा अणु
	wildfire_64	qsd_whami;
	wildfire_64	qsd_rev;
	wildfire_64	qsd_port_present;
	wildfire_64	qsd_port_active;
	wildfire_64	qsd_fault_ena;
	wildfire_64	qsd_cpu_पूर्णांक_ena;
	wildfire_64	qsd_mem_config;
	wildfire_64	qsd_err_sum;
	wildfire_64	ce_sum[4];
	wildfire_64	dev_init[4];
	wildfire_64	it_पूर्णांक[4];
	wildfire_64	ip_पूर्णांक[4];
	wildfire_64	uce_sum[4];
	wildfire_64	se_sum__non_dev_पूर्णांक[4];
	wildfire_64	scratch[4];
	wildfire_64	qsd_समयr;
	wildfire_64	qsd_diag;
पूर्ण wildfire_qsd;

प्रकार काष्ठा अणु
	wildfire_256	qsd_whami;
	wildfire_256	__pad1;
	wildfire_256	ce_sum;
	wildfire_256	dev_init;
	wildfire_256	it_पूर्णांक;
	wildfire_256	ip_पूर्णांक;
	wildfire_256	uce_sum;
	wildfire_256	se_sum;
पूर्ण wildfire_fast_qsd;

प्रकार काष्ठा अणु
	wildfire_2k	qsa_qbb_id;
	wildfire_2k	__pad1;
	wildfire_2k	qsa_port_ena;
	wildfire_2k	qsa_scratch;
	wildfire_2k	qsa_config[5];
	wildfire_2k	qsa_ref_पूर्णांक;
	wildfire_2k	qsa_qbb_pop[2];
	wildfire_2k	qsa_dtag_fc;
	wildfire_2k	__pad2[3];
	wildfire_2k	qsa_diag;
	wildfire_2k	qsa_diag_lock[4];
	wildfire_2k	__pad3[11];
	wildfire_2k	qsa_cpu_err_sum;
	wildfire_2k	qsa_misc_err_sum;
	wildfire_2k	qsa_पंचांगo_err_sum;
	wildfire_2k	qsa_err_ena;
	wildfire_2k	qsa_पंचांगo_config;
	wildfire_2k	qsa_ill_cmd_err_sum;
	wildfire_2k	__pad4[26];
	wildfire_2k	qsa_busy_mask;
	wildfire_2k	qsa_arr_valid;
	wildfire_2k	__pad5[2];
	wildfire_2k	qsa_port_map[4];
	wildfire_2k	qsa_arr_addr[8];
	wildfire_2k	qsa_arr_mask[8];
पूर्ण wildfire_qsa;

प्रकार काष्ठा अणु
	wildfire_64	ioa_config;
	wildfire_64	iod_config;
	wildfire_64	iop_चयन_credits;
	wildfire_64	__pad1;
	wildfire_64	iop_hose_credits;
	wildfire_64	__pad2[11];
	काष्ठा अणु
		wildfire_64	__pad3;
		wildfire_64	init;
	पूर्ण iop_hose[4];
	wildfire_64	ioa_hose_0_ctrl;
	wildfire_64	iod_hose_0_ctrl;
	wildfire_64	ioa_hose_1_ctrl;
	wildfire_64	iod_hose_1_ctrl;
	wildfire_64	ioa_hose_2_ctrl;
	wildfire_64	iod_hose_2_ctrl;
	wildfire_64	ioa_hose_3_ctrl;
	wildfire_64	iod_hose_3_ctrl;
	काष्ठा अणु
		wildfire_64	target;
		wildfire_64	__pad4;
	पूर्ण iop_dev_पूर्णांक[4];

	wildfire_64	iop_err_पूर्णांक_target;
	wildfire_64	__pad5[7];
	wildfire_64	iop_qbb_err_sum;
	wildfire_64	__pad6;
	wildfire_64	iop_qbb_se_sum;
	wildfire_64	__pad7;
	wildfire_64	ioa_err_sum;
	wildfire_64	iod_err_sum;
	wildfire_64	__pad8[4];
	wildfire_64	ioa_diag_क्रमce_err;
	wildfire_64	iod_diag_क्रमce_err;
	wildfire_64	__pad9[4];
	wildfire_64	iop_diag_send_err_पूर्णांक;
	wildfire_64	__pad10[15];
	wildfire_64	ioa_scratch;
	wildfire_64	iod_scratch;
पूर्ण wildfire_iop;

प्रकार काष्ठा अणु
	wildfire_2k	gpa_qbb_map[4];
	wildfire_2k	gpa_mem_pop_map;
	wildfire_2k	gpa_scratch;
	wildfire_2k	gpa_diag;
	wildfire_2k	gpa_config_0;
	wildfire_2k	__pad1;
	wildfire_2k	gpa_init_id;
	wildfire_2k	gpa_config_2;
	/* not complete */
पूर्ण wildfire_gp;

प्रकार काष्ठा अणु
	wildfire_64	pca_what_am_i;
	wildfire_64	pca_err_sum;
	wildfire_64	pca_diag_क्रमce_err;
	wildfire_64	pca_diag_send_err_पूर्णांक;
	wildfire_64	pca_hose_credits;
	wildfire_64	pca_scratch;
	wildfire_64	pca_micro_addr;
	wildfire_64	pca_micro_data;
	wildfire_64	pca_pend_पूर्णांक;
	wildfire_64	pca_sent_पूर्णांक;
	wildfire_64	__pad1;
	wildfire_64	pca_stdio_edge_level;
	wildfire_64	__pad2[52];
	काष्ठा अणु
		wildfire_64	target;
		wildfire_64	enable;
	पूर्ण pca_पूर्णांक[4];
	wildfire_64	__pad3[56];
	wildfire_64	pca_alt_sent_पूर्णांक[32];
पूर्ण wildfire_pca;

प्रकार काष्ठा अणु
	wildfire_64	ne_what_am_i;
	/* not complete */
पूर्ण wildfire_ne;

प्रकार काष्ठा अणु
	wildfire_64	fe_what_am_i;
	/* not complete */
पूर्ण wildfire_fe;

प्रकार काष्ठा अणु
	wildfire_64	pci_io_addr_ext;
	wildfire_64	pci_ctrl;
	wildfire_64	pci_err_sum;
	wildfire_64	pci_err_addr;
	wildfire_64	pci_stall_cnt;
	wildfire_64	pci_iack_special;
	wildfire_64	__pad1[2];
	wildfire_64	pci_pend_पूर्णांक;
	wildfire_64	pci_sent_पूर्णांक;
	wildfire_64	__pad2[54];
	काष्ठा अणु
		wildfire_64	wbase;
		wildfire_64	wmask;
		wildfire_64	tbase;
	पूर्ण pci_winकरोw[4];
	wildfire_64	pci_flush_tlb;
	wildfire_64	pci_perf_mon;
पूर्ण wildfire_pci;

#घोषणा WILDFIRE_ENTITY_SHIFT		18

#घोषणा WILDFIRE_GP_ENTITY		(0x10UL << WILDFIRE_ENTITY_SHIFT)
#घोषणा WILDFIRE_IOP_ENTITY		(0x08UL << WILDFIRE_ENTITY_SHIFT)
#घोषणा WILDFIRE_QSA_ENTITY		(0x04UL << WILDFIRE_ENTITY_SHIFT)
#घोषणा WILDFIRE_QSD_ENTITY_SLOW	(0x05UL << WILDFIRE_ENTITY_SHIFT)
#घोषणा WILDFIRE_QSD_ENTITY_FAST	(0x01UL << WILDFIRE_ENTITY_SHIFT)

#घोषणा WILDFIRE_PCA_ENTITY(pca)	((0xc|(pca))<<WILDFIRE_ENTITY_SHIFT)

#घोषणा WILDFIRE_BASE		(IDENT_ADDR | (1UL << 40))

#घोषणा WILDFIRE_QBB_MASK	0x0fUL	/* क्रम now, only 4 bits/16 QBBs */

#घोषणा WILDFIRE_QBB(q)		((~((दीर्घ)(q)) & WILDFIRE_QBB_MASK) << 36)
#घोषणा WILDFIRE_HOSE(h)	((दीर्घ)(h) << 33)

#घोषणा WILDFIRE_QBB_IO(q)	(WILDFIRE_BASE | WILDFIRE_QBB(q))
#घोषणा WILDFIRE_QBB_HOSE(q,h)	(WILDFIRE_QBB_IO(q) | WILDFIRE_HOSE(h))

#घोषणा WILDFIRE_MEM(q,h)	(WILDFIRE_QBB_HOSE(q,h) | 0x000000000UL)
#घोषणा WILDFIRE_CONF(q,h)	(WILDFIRE_QBB_HOSE(q,h) | 0x1FE000000UL)
#घोषणा WILDFIRE_IO(q,h)	(WILDFIRE_QBB_HOSE(q,h) | 0x1FF000000UL)

#घोषणा WILDFIRE_qsd(q) \
 ((wildfire_qsd *)(WILDFIRE_QBB_IO(q)|WILDFIRE_QSD_ENTITY_SLOW|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_fast_qsd() \
 ((wildfire_fast_qsd *)(WILDFIRE_QBB_IO(0)|WILDFIRE_QSD_ENTITY_FAST|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_qsa(q) \
 ((wildfire_qsa *)(WILDFIRE_QBB_IO(q)|WILDFIRE_QSA_ENTITY|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_iop(q) \
 ((wildfire_iop *)(WILDFIRE_QBB_IO(q)|WILDFIRE_IOP_ENTITY|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_gp(q) \
 ((wildfire_gp *)(WILDFIRE_QBB_IO(q)|WILDFIRE_GP_ENTITY|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_pca(q,pca) \
 ((wildfire_pca *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_ne(q,pca) \
 ((wildfire_ne *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL<<13)-1)<<23)|(1UL<<16)))

#घोषणा WILDFIRE_fe(q,pca) \
 ((wildfire_fe *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(pca)|(((1UL<<13)-1)<<23)|(3UL<<15)))

#घोषणा WILDFIRE_pci(q,h) \
 ((wildfire_pci *)(WILDFIRE_QBB_IO(q)|WILDFIRE_PCA_ENTITY(((h)&6)>>1)|((((h)&1)|2)<<16)|(((1UL<<13)-1)<<23)))

#घोषणा WILDFIRE_IO_BIAS        WILDFIRE_IO(0,0)
#घोषणा WILDFIRE_MEM_BIAS       WILDFIRE_MEM(0,0) /* ??? */

/* The IO address space is larger than 0xffff */
#घोषणा WILDFIRE_IO_SPACE	(8UL*1024*1024)

#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * Memory functions.  all accesses are करोne through linear space.
 */

__EXTERN_INLINE व्योम __iomem *wildfire_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + WILDFIRE_IO_BIAS);
पूर्ण

__EXTERN_INLINE व्योम __iomem *wildfire_ioremap(अचिन्हित दीर्घ addr, 
					       अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + WILDFIRE_MEM_BIAS);
पूर्ण

__EXTERN_INLINE पूर्णांक wildfire_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= WILDFIRE_BASE;
पूर्ण

__EXTERN_INLINE पूर्णांक wildfire_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr;
	वापस (addr & 0x100000000UL) == 0;
पूर्ण

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX			wildfire
#घोषणा wildfire_trivial_rw_bw		1
#घोषणा wildfire_trivial_rw_lq		1
#घोषणा wildfire_trivial_io_bw		1
#घोषणा wildfire_trivial_io_lq		1
#घोषणा wildfire_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_WILDFIRE__H__ */
