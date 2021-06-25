<शैली गुरु>
/*
 *  linux/arch/nios2/kernel/misaligned.c
 *
 *  basic emulation क्रम mis-aligned accesses on the NIOS II cpu
 *  modelled after the version क्रम arm in arm/alignment.c
 *
 *  Brad Parker <brad@heeltoe.com>
 *  Copyright (C) 2010 Ambient Corporation
 *  Copyright (c) 2010 Altera Corporation, San Jose, Calअगरornia, USA.
 *  Copyright (c) 2010 Arrow Electronics, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/unaligned.h>

/* inकाष्ठाions we emulate */
#घोषणा INST_LDHU	0x0b
#घोषणा INST_STH	0x0d
#घोषणा INST_LDH	0x0f
#घोषणा INST_STW	0x15
#घोषणा INST_LDW	0x17

अटल अचिन्हित पूर्णांक ma_usermode;
#घोषणा UM_WARN		0x01
#घोषणा UM_FIXUP	0x02
#घोषणा UM_SIGNAL	0x04
#घोषणा KM_WARN		0x08

/* see arch/nios2/include/यंत्र/ptrace.h */
अटल u8 sys_stack_frame_reg_offset[] = अणु
	/* काष्ठा pt_regs */
	8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6, 7, 0,
	/* काष्ठा चयन_stack */
	16, 17, 18, 19, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल पूर्णांक reg_offsets[32];

अटल अंतरभूत u32 get_reg_val(काष्ठा pt_regs *fp, पूर्णांक reg)
अणु
	u8 *p = ((u8 *)fp) + reg_offsets[reg];
	वापस *(u32 *)p;
पूर्ण

अटल अंतरभूत व्योम put_reg_val(काष्ठा pt_regs *fp, पूर्णांक reg, u32 val)
अणु
	u8 *p = ((u8 *)fp) + reg_offsets[reg];
	*(u32 *)p = val;
पूर्ण

/*
 * (mis)alignment handler
 */
यंत्रlinkage व्योम handle_unaligned_c(काष्ठा pt_regs *fp, पूर्णांक cause)
अणु
	u32 isn, addr, val;
	पूर्णांक in_kernel;
	u8 a, b, d0, d1, d2, d3;
	s16 imm16;
	अचिन्हित पूर्णांक fault;

	/* back up one inकाष्ठाion */
	fp->ea -= 4;

	अगर (fixup_exception(fp)) अणु
		वापस;
	पूर्ण

	in_kernel = !user_mode(fp);

	isn = *(अचिन्हित दीर्घ *)(fp->ea);

	fault = 0;

	/* करो fixup अगर in kernel or mode turned on */
	अगर (in_kernel || (ma_usermode & UM_FIXUP)) अणु
		/* decompose inकाष्ठाion */
		a = (isn >> 27) & 0x1f;
		b = (isn >> 22) & 0x1f;
		imm16 = (isn >> 6) & 0xffff;
		addr = get_reg_val(fp, a) + imm16;

		/* करो fixup to saved रेजिस्टरs */
		चयन (isn & 0x3f) अणु
		हाल INST_LDHU:
			fault |= __get_user(d0, (u8 *)(addr+0));
			fault |= __get_user(d1, (u8 *)(addr+1));
			val = (d1 << 8) | d0;
			put_reg_val(fp, b, val);
			अवरोध;
		हाल INST_STH:
			val = get_reg_val(fp, b);
			d1 = val >> 8;
			d0 = val >> 0;
			अगर (in_kernel) अणु
				*(u8 *)(addr+0) = d0;
				*(u8 *)(addr+1) = d1;
			पूर्ण अन्यथा अणु
				fault |= __put_user(d0, (u8 *)(addr+0));
				fault |= __put_user(d1, (u8 *)(addr+1));
			पूर्ण
			अवरोध;
		हाल INST_LDH:
			fault |= __get_user(d0, (u8 *)(addr+0));
			fault |= __get_user(d1, (u8 *)(addr+1));
			val = (लघु)((d1 << 8) | d0);
			put_reg_val(fp, b, val);
			अवरोध;
		हाल INST_STW:
			val = get_reg_val(fp, b);
			d3 = val >> 24;
			d2 = val >> 16;
			d1 = val >> 8;
			d0 = val >> 0;
			अगर (in_kernel) अणु
				*(u8 *)(addr+0) = d0;
				*(u8 *)(addr+1) = d1;
				*(u8 *)(addr+2) = d2;
				*(u8 *)(addr+3) = d3;
			पूर्ण अन्यथा अणु
				fault |= __put_user(d0, (u8 *)(addr+0));
				fault |= __put_user(d1, (u8 *)(addr+1));
				fault |= __put_user(d2, (u8 *)(addr+2));
				fault |= __put_user(d3, (u8 *)(addr+3));
			पूर्ण
			अवरोध;
		हाल INST_LDW:
			fault |= __get_user(d0, (u8 *)(addr+0));
			fault |= __get_user(d1, (u8 *)(addr+1));
			fault |= __get_user(d2, (u8 *)(addr+2));
			fault |= __get_user(d3, (u8 *)(addr+3));
			val = (d3 << 24) | (d2 << 16) | (d1 << 8) | d0;
			put_reg_val(fp, b, val);
			अवरोध;
		पूर्ण
	पूर्ण

	addr = RDCTL(CTL_BADADDR);
	cause >>= 2;

	अगर (fault) अणु
		अगर (in_kernel) अणु
			pr_err("fault during kernel misaligned fixup @ %#lx; addr 0x%08x; isn=0x%08x\n",
				fp->ea, (अचिन्हित पूर्णांक)addr,
				(अचिन्हित पूर्णांक)isn);
		पूर्ण अन्यथा अणु
			pr_err("fault during user misaligned fixup @ %#lx; isn=%08x addr=0x%08x sp=0x%08lx pid=%d\n",
				fp->ea,
				(अचिन्हित पूर्णांक)isn, addr, fp->sp,
				current->pid);

			_exception(संक_अंश, fp, SEGV_MAPERR, fp->ea);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * kernel mode -
	 *  note exception and skip bad inकाष्ठाion (वापस)
	 */
	अगर (in_kernel) अणु
		fp->ea += 4;

		अगर (ma_usermode & KM_WARN) अणु
			pr_err("kernel unaligned access @ %#lx; BADADDR 0x%08x; cause=%d, isn=0x%08x\n",
				fp->ea,
				(अचिन्हित पूर्णांक)addr, cause,
				(अचिन्हित पूर्णांक)isn);
			/* show_regs(fp); */
		पूर्ण

		वापस;
	पूर्ण

	/*
	 * user mode -
	 *  possibly warn,
	 *  possibly send SIGBUS संकेत to process
	 */
	अगर (ma_usermode & UM_WARN) अणु
		pr_err("user unaligned access @ %#lx; isn=0x%08lx ea=0x%08lx ra=0x%08lx sp=0x%08lx\n",
			(अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)isn,
			fp->ea, fp->ra, fp->sp);
	पूर्ण

	अगर (ma_usermode & UM_SIGNAL)
		_exception(SIGBUS, fp, BUS_ADRALN, fp->ea);
	अन्यथा
		fp->ea += 4;	/* अन्यथा advance */
पूर्ण

अटल व्योम __init misaligned_calc_reg_offsets(व्योम)
अणु
	पूर्णांक i, r, offset;

	/* pre-calc offsets of रेजिस्टरs on sys call stack frame */
	offset = 0;

	/* काष्ठा pt_regs */
	क्रम (i = 0; i < 16; i++) अणु
		r = sys_stack_frame_reg_offset[i];
		reg_offsets[r] = offset;
		offset += 4;
	पूर्ण

	/* काष्ठा चयन_stack */
	offset = -माप(काष्ठा चयन_stack);
	क्रम (i = 16; i < 32; i++) अणु
		r = sys_stack_frame_reg_offset[i];
		reg_offsets[r] = offset;
		offset += 4;
	पूर्ण
पूर्ण


अटल पूर्णांक __init misaligned_init(व्योम)
अणु
	/* शेष mode - silent fix */
	ma_usermode = UM_FIXUP | KM_WARN;

	misaligned_calc_reg_offsets();

	वापस 0;
पूर्ण

fs_initcall(misaligned_init);
