<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ENTRY_H
#घोषणा _ENTRY_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>

/* irq */
व्योम handler_irq(पूर्णांक irq, काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SPARC32
/* traps */
व्योम करो_hw_पूर्णांकerrupt(काष्ठा pt_regs *regs, अचिन्हित दीर्घ type);
व्योम करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                            अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);

व्योम करो_priv_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                         अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम करो_memaccess_unaligned(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                            अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम करो_fpd_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                 अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम करो_fpe_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                 अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम handle_tag_overflow(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                         अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम handle_watchpoपूर्णांक(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                       अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम handle_reg_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                       अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम handle_cp_disabled(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                        अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
व्योम handle_cp_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                         अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);



/* entry.S */
व्योम fpsave(अचिन्हित दीर्घ *fpregs, अचिन्हित दीर्घ *fsr,
            व्योम *fpqueue, अचिन्हित दीर्घ *fpqdepth);
व्योम fpload(अचिन्हित दीर्घ *fpregs, अचिन्हित दीर्घ *fsr);

#अन्यथा /* CONFIG_SPARC32 */

#समावेश <यंत्र/trap_block.h>

काष्ठा popc_3insn_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insns[3];
पूर्ण;
बाह्य काष्ठा popc_3insn_patch_entry __popc_3insn_patch,
	__popc_3insn_patch_end;

काष्ठा popc_6insn_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insns[6];
पूर्ण;
बाह्य काष्ठा popc_6insn_patch_entry __popc_6insn_patch,
	__popc_6insn_patch_end;

काष्ठा छोड़ो_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insns[3];
पूर्ण;
बाह्य काष्ठा छोड़ो_patch_entry __छोड़ो_3insn_patch,
	__छोड़ो_3insn_patch_end;

व्योम sun4v_patch_1insn_range(काष्ठा sun4v_1insn_patch_entry *,
			     काष्ठा sun4v_1insn_patch_entry *);
व्योम sun4v_patch_2insn_range(काष्ठा sun4v_2insn_patch_entry *,
			     काष्ठा sun4v_2insn_patch_entry *);
व्योम sun_m7_patch_2insn_range(काष्ठा sun4v_2insn_patch_entry *,
			     काष्ठा sun4v_2insn_patch_entry *);
बाह्य अचिन्हित पूर्णांक dcache_parity_tl1_occurred;
बाह्य अचिन्हित पूर्णांक icache_parity_tl1_occurred;

यंत्रlinkage व्योम sparc_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs);
व्योम समयr_पूर्णांकerrupt(पूर्णांक irq, काष्ठा pt_regs *regs);

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ orig_i0,
		      अचिन्हित दीर्घ thपढ़ो_info_flags);

यंत्रlinkage पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम syscall_trace_leave(काष्ठा pt_regs *regs);

व्योम bad_trap_tl1(काष्ठा pt_regs *regs, दीर्घ lvl);

व्योम करो_fpieee(काष्ठा pt_regs *regs);
व्योम करो_fpother(काष्ठा pt_regs *regs);
व्योम करो_tof(काष्ठा pt_regs *regs);
व्योम करो_भाग0(काष्ठा pt_regs *regs);
व्योम करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs);
व्योम mem_address_unaligned(काष्ठा pt_regs *regs,
			   अचिन्हित दीर्घ sfar,
			   अचिन्हित दीर्घ sfsr);
व्योम sun4v_करो_mna(काष्ठा pt_regs *regs,
		  अचिन्हित दीर्घ addr,
		  अचिन्हित दीर्घ type_ctx);
व्योम करो_privop(काष्ठा pt_regs *regs);
व्योम करो_privact(काष्ठा pt_regs *regs);
व्योम करो_cee(काष्ठा pt_regs *regs);
व्योम करो_भाग0_tl1(काष्ठा pt_regs *regs);
व्योम करो_fpieee_tl1(काष्ठा pt_regs *regs);
व्योम करो_fpother_tl1(काष्ठा pt_regs *regs);
व्योम करो_ill_tl1(काष्ठा pt_regs *regs);
व्योम करो_irq_tl1(काष्ठा pt_regs *regs);
व्योम करो_lddfmna_tl1(काष्ठा pt_regs *regs);
व्योम करो_stdfmna_tl1(काष्ठा pt_regs *regs);
व्योम करो_paw(काष्ठा pt_regs *regs);
व्योम करो_paw_tl1(काष्ठा pt_regs *regs);
व्योम करो_vaw(काष्ठा pt_regs *regs);
व्योम करो_vaw_tl1(काष्ठा pt_regs *regs);
व्योम करो_tof_tl1(काष्ठा pt_regs *regs);
व्योम करो_getpsr(काष्ठा pt_regs *regs);

व्योम spitfire_insn_access_exception(काष्ठा pt_regs *regs,
				    अचिन्हित दीर्घ sfsr,
				    अचिन्हित दीर्घ sfar);
व्योम spitfire_insn_access_exception_tl1(काष्ठा pt_regs *regs,
				        अचिन्हित दीर्घ sfsr,
				        अचिन्हित दीर्घ sfar);
व्योम spitfire_data_access_exception(काष्ठा pt_regs *regs,
				    अचिन्हित दीर्घ sfsr,
				    अचिन्हित दीर्घ sfar);
व्योम spitfire_data_access_exception_tl1(काष्ठा pt_regs *regs,
				        अचिन्हित दीर्घ sfsr,
				        अचिन्हित दीर्घ sfar);
व्योम spitfire_access_error(काष्ठा pt_regs *regs,
			   अचिन्हित दीर्घ status_encoded,
			   अचिन्हित दीर्घ afar);

व्योम cheetah_fecc_handler(काष्ठा pt_regs *regs,
			  अचिन्हित दीर्घ afsr,
			  अचिन्हित दीर्घ afar);
व्योम cheetah_cee_handler(काष्ठा pt_regs *regs,
			 अचिन्हित दीर्घ afsr,
			 अचिन्हित दीर्घ afar);
व्योम cheetah_deferred_handler(काष्ठा pt_regs *regs,
			      अचिन्हित दीर्घ afsr,
			      अचिन्हित दीर्घ afar);
व्योम cheetah_plus_parity_error(पूर्णांक type, काष्ठा pt_regs *regs);

व्योम sun4v_insn_access_exception(काष्ठा pt_regs *regs,
				 अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ type_ctx);
व्योम sun4v_insn_access_exception_tl1(काष्ठा pt_regs *regs,
				     अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ type_ctx);
व्योम sun4v_data_access_exception(काष्ठा pt_regs *regs,
				 अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ type_ctx);
व्योम sun4v_data_access_exception_tl1(काष्ठा pt_regs *regs,
				     अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ type_ctx);
व्योम sun4v_resum_error(काष्ठा pt_regs *regs,
		       अचिन्हित दीर्घ offset);
व्योम sun4v_resum_overflow(काष्ठा pt_regs *regs);
व्योम sun4v_nonresum_error(काष्ठा pt_regs *regs,
			  अचिन्हित दीर्घ offset);
व्योम sun4v_nonresum_overflow(काष्ठा pt_regs *regs);
व्योम sun4v_mem_corrupt_detect_precise(काष्ठा pt_regs *regs,
				      अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ context);

बाह्य अचिन्हित दीर्घ sun4v_err_itlb_vaddr;
बाह्य अचिन्हित दीर्घ sun4v_err_itlb_ctx;
बाह्य अचिन्हित दीर्घ sun4v_err_itlb_pte;
बाह्य अचिन्हित दीर्घ sun4v_err_itlb_error;

व्योम sun4v_itlb_error_report(काष्ठा pt_regs *regs, पूर्णांक tl);

बाह्य अचिन्हित दीर्घ sun4v_err_dtlb_vaddr;
बाह्य अचिन्हित दीर्घ sun4v_err_dtlb_ctx;
बाह्य अचिन्हित दीर्घ sun4v_err_dtlb_pte;
बाह्य अचिन्हित दीर्घ sun4v_err_dtlb_error;

व्योम sun4v_dtlb_error_report(काष्ठा pt_regs *regs, पूर्णांक tl);
व्योम hypervisor_tlbop_error(अचिन्हित दीर्घ err,
			    अचिन्हित दीर्घ op);
व्योम hypervisor_tlbop_error_xcall(अचिन्हित दीर्घ err,
				  अचिन्हित दीर्घ op);

/* WARNING: The error trap handlers in assembly know the precise
 *	    layout of the following काष्ठाure.
 *
 * C-level handlers in traps.c use this inक्रमmation to log the
 * error and then determine how to recover (अगर possible).
 */
काष्ठा cheetah_err_info अणु
/*0x00*/u64 afsr;
/*0x08*/u64 afar;

	/* D-cache state */
/*0x10*/u64 dcache_data[4];	/* The actual data	*/
/*0x30*/u64 dcache_index;	/* D-cache index	*/
/*0x38*/u64 dcache_tag;		/* D-cache tag/valid	*/
/*0x40*/u64 dcache_utag;	/* D-cache microtag	*/
/*0x48*/u64 dcache_stag;	/* D-cache snooptag	*/

	/* I-cache state */
/*0x50*/u64 icache_data[8];	/* The actual insns + predecode	*/
/*0x90*/u64 icache_index;	/* I-cache index	*/
/*0x98*/u64 icache_tag;		/* I-cache phys tag	*/
/*0xa0*/u64 icache_utag;	/* I-cache microtag	*/
/*0xa8*/u64 icache_stag;	/* I-cache snooptag	*/
/*0xb0*/u64 icache_upper;	/* I-cache upper-tag	*/
/*0xb8*/u64 icache_lower;	/* I-cache lower-tag	*/

	/* E-cache state */
/*0xc0*/u64 ecache_data[4];	/* 32 bytes from staging रेजिस्टरs */
/*0xe0*/u64 ecache_index;	/* E-cache index	*/
/*0xe8*/u64 ecache_tag;		/* E-cache tag/state	*/

/*0xf0*/u64 __pad[32 - 30];
पूर्ण;
#घोषणा CHAFSR_INVALID		((u64)-1L)

/* This is allocated at boot समय based upon the largest hardware
 * cpu ID in the प्रणाली.  We allocate two entries per cpu, one क्रम
 * TL==0 logging and one क्रम TL >= 1 logging.
 */
बाह्य काष्ठा cheetah_err_info *cheetah_error_log;

/* UPA nodes send पूर्णांकerrupt packet to UltraSparc with first data reg
 * value low 5 (7 on Starfire) bits holding the IRQ identअगरier being
 * delivered.  We must translate this पूर्णांकo a non-vector IRQ so we can
 * set the softपूर्णांक on this cpu.
 *
 * To make processing these packets efficient and race मुक्त we use
 * an array of irq buckets below.  The पूर्णांकerrupt vector handler in
 * entry.S feeds incoming packets पूर्णांकo per-cpu pil-indexed lists.
 *
 * If you make changes to ino_bucket, please update hand coded assembler
 * of the vectored पूर्णांकerrupt trap handler(s) in entry.S and sun4v_ivec.S
 */
काष्ठा ino_bucket अणु
/*0x00*/अचिन्हित दीर्घ __irq_chain_pa;

	/* Interrupt number asचिन्हित to this INO.  */
/*0x08*/अचिन्हित पूर्णांक __irq;
/*0x0c*/अचिन्हित पूर्णांक __pad;
पूर्ण;

बाह्य काष्ठा ino_bucket *ivector_table;
बाह्य अचिन्हित दीर्घ ivector_table_pa;

व्योम init_irqwork_curcpu(व्योम);
व्योम sun4v_रेजिस्टर_monकरो_queues(पूर्णांक this_cpu);

#पूर्ण_अगर /* CONFIG_SPARC32 */
#पूर्ण_अगर /* _ENTRY_H */
