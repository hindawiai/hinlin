<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sysctl.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा DEBUG(enable, tagged, ...)				\
	करोअणु							\
		अगर (enable) अणु					\
			अगर (tagged)				\
			pr_warn("[ %30s() ] ", __func__);	\
			pr_warn(__VA_ARGS__);			\
		पूर्ण						\
	पूर्ण जबतक (0)

#घोषणा RT(inst)	(((inst) >> 20) & 0x1FUL)
#घोषणा RA(inst)	(((inst) >> 15) & 0x1FUL)
#घोषणा RB(inst)	(((inst) >> 10) & 0x1FUL)
#घोषणा SV(inst)	(((inst) >> 8) & 0x3UL)
#घोषणा IMM(inst)	(((inst) >> 0) & 0x7FFFUL)

#घोषणा RA3(inst)	(((inst) >> 3) & 0x7UL)
#घोषणा RT3(inst)	(((inst) >> 6) & 0x7UL)
#घोषणा IMM3U(inst)	(((inst) >> 0) & 0x7UL)

#घोषणा RA5(inst)	(((inst) >> 0) & 0x1FUL)
#घोषणा RT4(inst)	(((inst) >> 5) & 0xFUL)

#घोषणा GET_IMMSVAL(imm_value) \
	(((imm_value >> 14) & 0x1) ? (imm_value - 0x8000) : imm_value)

#घोषणा __get8_data(val,addr,err)	\
	__यंत्र__(					\
	"1:	lbi.bi	%1, [%2], #1\n"			\
	"2:\n"						\
	"	.pushsection .text.fixup,\"ax\"\n"	\
	"	.align	2\n"				\
	"3:	movi	%0, #1\n"			\
	"	j	2b\n"				\
	"	.popsection\n"				\
	"	.pushsection __ex_table,\"a\"\n"	\
	"	.align	3\n"				\
	"	.long	1b, 3b\n"			\
	"	.popsection\n"				\
	: "=r" (err), "=&r" (val), "=r" (addr)		\
	: "0" (err), "2" (addr))

#घोषणा get16_data(addr, val_ptr)				\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v, a = addr;		\
		__get8_data(v,a,err);				\
		*val_ptr =  v << 0;				\
		__get8_data(v,a,err);				\
		*val_ptr |= v << 8;				\
		अगर (err)					\
			जाओ fault;				\
		*val_ptr = le16_to_cpu(*val_ptr);		\
	पूर्ण जबतक(0)

#घोषणा get32_data(addr, val_ptr)				\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v, a = addr;		\
		__get8_data(v,a,err);				\
		*val_ptr =  v << 0;				\
		__get8_data(v,a,err);				\
		*val_ptr |= v << 8;				\
		__get8_data(v,a,err);				\
		*val_ptr |= v << 16;				\
		__get8_data(v,a,err);				\
		*val_ptr |= v << 24;				\
		अगर (err)					\
			जाओ fault;				\
		*val_ptr = le32_to_cpu(*val_ptr);		\
	पूर्ण जबतक(0)

#घोषणा get_data(addr, val_ptr, len)				\
	अगर (len == 2)						\
		get16_data(addr, val_ptr);			\
	अन्यथा							\
		get32_data(addr, val_ptr);

#घोषणा set16_data(addr, val)					\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, *ptr = addr ;		\
		val = le32_to_cpu(val);				\
		__यंत्र__(					\
                "1:	sbi.bi 	%2, [%1], #1\n"			\
                "	srli 	%2, %2, #8\n"			\
                "2:	sbi	%2, [%1]\n"			\
		"3:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.align	2\n"				\
		"4:	movi	%0, #1\n"			\
		"	j	3b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_table,\"a\"\n"	\
		"	.align	3\n"				\
		"	.long	1b, 4b\n"			\
		"	.long	2b, 4b\n"			\
		"	.popsection\n"				\
		: "=r" (err), "+r" (ptr), "+r" (val)		\
		: "0" (err)					\
		);						\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक(0)

#घोषणा set32_data(addr, val)					\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, *ptr = addr ;		\
		val = le32_to_cpu(val);				\
		__यंत्र__(					\
                "1:	sbi.bi 	%2, [%1], #1\n"			\
                "	srli 	%2, %2, #8\n"			\
                "2:	sbi.bi 	%2, [%1], #1\n"			\
                "	srli 	%2, %2, #8\n"			\
                "3:	sbi.bi 	%2, [%1], #1\n"			\
                "	srli 	%2, %2, #8\n"			\
                "4:	sbi 	%2, [%1]\n"			\
		"5:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.align	2\n"				\
		"6:	movi	%0, #1\n"			\
		"	j	5b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_table,\"a\"\n"	\
		"	.align	3\n"				\
		"	.long	1b, 6b\n"			\
		"	.long	2b, 6b\n"			\
		"	.long	3b, 6b\n"			\
		"	.long	4b, 6b\n"			\
		"	.popsection\n"				\
		: "=r" (err), "+r" (ptr), "+r" (val)		\
		: "0" (err)					\
		);						\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक(0)
#घोषणा set_data(addr, val, len)				\
	अगर (len == 2)						\
		set16_data(addr, val);				\
	अन्यथा							\
		set32_data(addr, val);
#घोषणा NDS32_16BIT_INSTRUCTION	0x80000000

बाह्य pte_t va_present(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य pte_t va_kernel_present(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक va_पढ़ोable(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);
बाह्य पूर्णांक va_writable(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);

पूर्णांक unalign_access_mode = 0, unalign_access_debug = 0;

अटल अंतरभूत अचिन्हित दीर्घ *idx_to_addr(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	/* this should be consistent with ptrace.h */
	अगर (idx >= 0 && idx <= 25)	/* R0-R25 */
		वापस &regs->uregs[0] + idx;
	अन्यथा अगर (idx >= 28 && idx <= 30)	/* FP, GP, LP */
		वापस &regs->fp + (idx - 28);
	अन्यथा अगर (idx == 31)	/* SP */
		वापस &regs->sp;
	अन्यथा
		वापस शून्य;	/* cause a segfault */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_inst(अचिन्हित दीर्घ addr)
अणु
	वापस be32_to_cpu(get_unaligned((u32 *) addr));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sign_extend(अचिन्हित दीर्घ val, पूर्णांक len)
अणु
	अचिन्हित दीर्घ ret = 0;
	अचिन्हित अक्षर *s, *t;
	पूर्णांक i = 0;

	val = cpu_to_le32(val);

	s = (व्योम *)&val;
	t = (व्योम *)&ret;

	जबतक (i++ < len)
		*t++ = *s++;

	अगर (((*(t - 1)) & 0x80) && (i < 4)) अणु

		जबतक (i++ <= 4)
			*t++ = 0xff;
	पूर्ण

	वापस le32_to_cpu(ret);
पूर्ण

अटल अंतरभूत पूर्णांक करो_16(अचिन्हित दीर्घ inst, काष्ठा pt_regs *regs)
अणु
	पूर्णांक imm, regular, load, len, addr_mode, idx_mode;
	अचिन्हित दीर्घ unaligned_addr, target_val, source_idx, target_idx,
	    shअगरt = 0;
	चयन ((inst >> 9) & 0x3F) अणु

	हाल 0x12:		/* LHI333    */
		imm = 1;
		regular = 1;
		load = 1;
		len = 2;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x10:		/* LWI333    */
		imm = 1;
		regular = 1;
		load = 1;
		len = 4;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x11:		/* LWI333.bi */
		imm = 1;
		regular = 0;
		load = 1;
		len = 4;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x1A:		/* LWI450    */
		imm = 0;
		regular = 1;
		load = 1;
		len = 4;
		addr_mode = 5;
		idx_mode = 4;
		अवरोध;
	हाल 0x16:		/* SHI333    */
		imm = 1;
		regular = 1;
		load = 0;
		len = 2;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x14:		/* SWI333    */
		imm = 1;
		regular = 1;
		load = 0;
		len = 4;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x15:		/* SWI333.bi */
		imm = 1;
		regular = 0;
		load = 0;
		len = 4;
		addr_mode = 3;
		idx_mode = 3;
		अवरोध;
	हाल 0x1B:		/* SWI450    */
		imm = 0;
		regular = 1;
		load = 0;
		len = 4;
		addr_mode = 5;
		idx_mode = 4;
		अवरोध;

	शेष:
		वापस -EFAULT;
	पूर्ण

	अगर (addr_mode == 3) अणु
		unaligned_addr = *idx_to_addr(regs, RA3(inst));
		source_idx = RA3(inst);
	पूर्ण अन्यथा अणु
		unaligned_addr = *idx_to_addr(regs, RA5(inst));
		source_idx = RA5(inst);
	पूर्ण

	अगर (idx_mode == 3)
		target_idx = RT3(inst);
	अन्यथा
		target_idx = RT4(inst);

	अगर (imm)
		shअगरt = IMM3U(inst) * len;

	अगर (regular)
		unaligned_addr += shअगरt;

	अगर (load) अणु
		अगर (!access_ok((व्योम *)unaligned_addr, len))
			वापस -EACCES;

		get_data(unaligned_addr, &target_val, len);
		*idx_to_addr(regs, target_idx) = target_val;
	पूर्ण अन्यथा अणु
		अगर (!access_ok((व्योम *)unaligned_addr, len))
			वापस -EACCES;
		target_val = *idx_to_addr(regs, target_idx);
		set_data((व्योम *)unaligned_addr, target_val, len);
	पूर्ण

	अगर (!regular)
		*idx_to_addr(regs, source_idx) = unaligned_addr + shअगरt;
	regs->ipc += 2;

	वापस 0;
fault:
	वापस -EACCES;
पूर्ण

अटल अंतरभूत पूर्णांक करो_32(अचिन्हित दीर्घ inst, काष्ठा pt_regs *regs)
अणु
	पूर्णांक imm, regular, load, len, sign_ext;
	अचिन्हित दीर्घ unaligned_addr, target_val, shअगरt;

	unaligned_addr = *idx_to_addr(regs, RA(inst));

	चयन ((inst >> 25) << 1) अणु

	हाल 0x02:		/* LHI       */
		imm = 1;
		regular = 1;
		load = 1;
		len = 2;
		sign_ext = 0;
		अवरोध;
	हाल 0x0A:		/* LHI.bi    */
		imm = 1;
		regular = 0;
		load = 1;
		len = 2;
		sign_ext = 0;
		अवरोध;
	हाल 0x22:		/* LHSI      */
		imm = 1;
		regular = 1;
		load = 1;
		len = 2;
		sign_ext = 1;
		अवरोध;
	हाल 0x2A:		/* LHSI.bi   */
		imm = 1;
		regular = 0;
		load = 1;
		len = 2;
		sign_ext = 1;
		अवरोध;
	हाल 0x04:		/* LWI       */
		imm = 1;
		regular = 1;
		load = 1;
		len = 4;
		sign_ext = 0;
		अवरोध;
	हाल 0x0C:		/* LWI.bi    */
		imm = 1;
		regular = 0;
		load = 1;
		len = 4;
		sign_ext = 0;
		अवरोध;
	हाल 0x12:		/* SHI       */
		imm = 1;
		regular = 1;
		load = 0;
		len = 2;
		sign_ext = 0;
		अवरोध;
	हाल 0x1A:		/* SHI.bi    */
		imm = 1;
		regular = 0;
		load = 0;
		len = 2;
		sign_ext = 0;
		अवरोध;
	हाल 0x14:		/* SWI       */
		imm = 1;
		regular = 1;
		load = 0;
		len = 4;
		sign_ext = 0;
		अवरोध;
	हाल 0x1C:		/* SWI.bi    */
		imm = 1;
		regular = 0;
		load = 0;
		len = 4;
		sign_ext = 0;
		अवरोध;

	शेष:
		चयन (inst & 0xff) अणु

		हाल 0x01:	/* LH        */
			imm = 0;
			regular = 1;
			load = 1;
			len = 2;
			sign_ext = 0;
			अवरोध;
		हाल 0x05:	/* LH.bi     */
			imm = 0;
			regular = 0;
			load = 1;
			len = 2;
			sign_ext = 0;
			अवरोध;
		हाल 0x11:	/* LHS       */
			imm = 0;
			regular = 1;
			load = 1;
			len = 2;
			sign_ext = 1;
			अवरोध;
		हाल 0x15:	/* LHS.bi    */
			imm = 0;
			regular = 0;
			load = 1;
			len = 2;
			sign_ext = 1;
			अवरोध;
		हाल 0x02:	/* LW        */
			imm = 0;
			regular = 1;
			load = 1;
			len = 4;
			sign_ext = 0;
			अवरोध;
		हाल 0x06:	/* LW.bi     */
			imm = 0;
			regular = 0;
			load = 1;
			len = 4;
			sign_ext = 0;
			अवरोध;
		हाल 0x09:	/* SH        */
			imm = 0;
			regular = 1;
			load = 0;
			len = 2;
			sign_ext = 0;
			अवरोध;
		हाल 0x0D:	/* SH.bi     */
			imm = 0;
			regular = 0;
			load = 0;
			len = 2;
			sign_ext = 0;
			अवरोध;
		हाल 0x0A:	/* SW        */
			imm = 0;
			regular = 1;
			load = 0;
			len = 4;
			sign_ext = 0;
			अवरोध;
		हाल 0x0E:	/* SW.bi     */
			imm = 0;
			regular = 0;
			load = 0;
			len = 4;
			sign_ext = 0;
			अवरोध;

		शेष:
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (imm)
		shअगरt = GET_IMMSVAL(IMM(inst)) * len;
	अन्यथा
		shअगरt = *idx_to_addr(regs, RB(inst)) << SV(inst);

	अगर (regular)
		unaligned_addr += shअगरt;

	अगर (load) अणु

		अगर (!access_ok((व्योम *)unaligned_addr, len))
			वापस -EACCES;

		get_data(unaligned_addr, &target_val, len);

		अगर (sign_ext)
			*idx_to_addr(regs, RT(inst)) =
			    sign_extend(target_val, len);
		अन्यथा
			*idx_to_addr(regs, RT(inst)) = target_val;
	पूर्ण अन्यथा अणु

		अगर (!access_ok((व्योम *)unaligned_addr, len))
			वापस -EACCES;

		target_val = *idx_to_addr(regs, RT(inst));
		set_data((व्योम *)unaligned_addr, target_val, len);
	पूर्ण

	अगर (!regular)
		*idx_to_addr(regs, RA(inst)) = unaligned_addr + shअगरt;

	regs->ipc += 4;

	वापस 0;
fault:
	वापस -EACCES;
पूर्ण

पूर्णांक करो_unaligned_access(अचिन्हित दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ inst;
	पूर्णांक ret = -EFAULT;
	mm_segment_t seg;

	inst = get_inst(regs->ipc);

	DEBUG((unalign_access_debug > 0), 1,
	      "Faulting addr: 0x%08lx, pc: 0x%08lx [inst: 0x%08lx ]\n", addr,
	      regs->ipc, inst);

	seg = क्रमce_uaccess_begin();
	अगर (inst & NDS32_16BIT_INSTRUCTION)
		ret = करो_16((inst >> 16) & 0xffff, regs);
	अन्यथा
		ret = करो_32(inst, regs);
	क्रमce_uaccess_end(seg);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल काष्ठा ctl_table alignment_tbl[3] = अणु
	अणु
	 .procname = "enable",
	 .data = &unalign_access_mode,
	 .maxlen = माप(unalign_access_mode),
	 .mode = 0666,
	 .proc_handler = &proc_करोपूर्णांकvec
	पूर्ण
	,
	अणु
	 .procname = "debug_info",
	 .data = &unalign_access_debug,
	 .maxlen = माप(unalign_access_debug),
	 .mode = 0644,
	 .proc_handler = &proc_करोपूर्णांकvec
	पूर्ण
	,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table nds32_sysctl_table[2] = अणु
	अणु
	 .procname = "unaligned_access",
	 .mode = 0555,
	 .child = alignment_tblपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_path nds32_path[2] = अणु
	अणु.procname = "nds32"पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Initialize nds32 alignment-correction पूर्णांकerface
 */
अटल पूर्णांक __init nds32_sysctl_init(व्योम)
अणु
	रेजिस्टर_sysctl_paths(nds32_path, nds32_sysctl_table);
	वापस 0;
पूर्ण

__initcall(nds32_sysctl_init);
#पूर्ण_अगर /* CONFIG_PROC_FS */
