<शैली गुरु>
/*
 * Microblaze KGDB support
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/kgdb.h>
#समावेश <यंत्र/pvr.h>

#घोषणा GDB_REG		0
#घोषणा GDB_PC		32
#घोषणा GDB_MSR		33
#घोषणा GDB_EAR		34
#घोषणा GDB_ESR		35
#घोषणा GDB_FSR		36
#घोषणा GDB_BTR		37
#घोषणा GDB_PVR		38
#घोषणा GDB_REDR	50
#घोषणा GDB_RPID	51
#घोषणा GDB_RZPR	52
#घोषणा GDB_RTLBX	53
#घोषणा GDB_RTLBSX	54 /* mfs can't पढ़ो it */
#घोषणा GDB_RTLBLO	55
#घोषणा GDB_RTLBHI	56

/* keep pvr separately because it is unchangeble */
अटल काष्ठा pvr_s pvr;

व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ *pt_regb = (अचिन्हित दीर्घ *)regs;
	पूर्णांक temp;

	/* रेजिस्टरs r0 - r31, pc, msr, ear, esr, fsr + करो not save pt_mode */
	क्रम (i = 0; i < (माप(काष्ठा pt_regs) / 4) - 1; i++)
		gdb_regs[i] = pt_regb[i];

	/* Branch target रेजिस्टर can't be changed */
	__यंत्र__ __अस्थिर__ ("mfs %0, rbtr;" : "=r"(temp) : );
	gdb_regs[GDB_BTR] = temp;

	/* pvr part  - we have 11 pvr regs */
	क्रम (i = 0; i < माप(काष्ठा pvr_s)/4; i++)
		gdb_regs[GDB_PVR + i] = pvr.pvr[i];

	/* पढ़ो special रेजिस्टरs - can't be changed */
	__यंत्र__ __अस्थिर__ ("mfs %0, redr;" : "=r"(temp) : );
	gdb_regs[GDB_REDR] = temp;
	__यंत्र__ __अस्थिर__ ("mfs %0, rpid;" : "=r"(temp) : );
	gdb_regs[GDB_RPID] = temp;
	__यंत्र__ __अस्थिर__ ("mfs %0, rzpr;" : "=r"(temp) : );
	gdb_regs[GDB_RZPR] = temp;
	__यंत्र__ __अस्थिर__ ("mfs %0, rtlbx;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBX] = temp;
	__यंत्र__ __अस्थिर__ ("mfs %0, rtlblo;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBLO] = temp;
	__यंत्र__ __अस्थिर__ ("mfs %0, rtlbhi;" : "=r"(temp) : );
	gdb_regs[GDB_RTLBHI] = temp;
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ *pt_regb = (अचिन्हित दीर्घ *)regs;

	/* pt_regs and gdb_regs have the same 37 values.
	 * The rest of gdb_regs are unused and can't be changed.
	 * r0 रेजिस्टर value can't be changed too. */
	क्रम (i = 1; i < (माप(काष्ठा pt_regs) / 4) - 1; i++)
		pt_regb[i] = gdb_regs[i];
पूर्ण

यंत्रlinkage व्योम microblaze_kgdb_अवरोध(काष्ठा pt_regs *regs)
अणु
	अगर (kgdb_handle_exception(1, SIGTRAP, 0, regs) != 0)
		वापस;

	/* Jump over the first arch_kgdb_अवरोधpoपूर्णांक which is barrier to
	 * get kgdb work. The same solution is used क्रम घातerpc */
	अगर (*(u32 *) (regs->pc) == *(u32 *) (&arch_kgdb_ops.gdb_bpt_instr))
		regs->pc += BREAK_INSTR_SIZE;
पूर्ण

/* untested */
व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ *pt_regb = (अचिन्हित दीर्घ *)(p->thपढ़ो.regs);

	/* रेजिस्टरs r0 - r31, pc, msr, ear, esr, fsr + करो not save pt_mode */
	क्रम (i = 0; i < (माप(काष्ठा pt_regs) / 4) - 1; i++)
		gdb_regs[i] = pt_regb[i];

	/* pvr part  - we have 11 pvr regs */
	क्रम (i = 0; i < माप(काष्ठा pvr_s)/4; i++)
		gdb_regs[GDB_PVR + i] = pvr.pvr[i];
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->pc = ip;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *regs)
अणु
	अक्षर *ptr;
	अचिन्हित दीर्घ address;

	चयन (remcom_in_buffer[0]) अणु
	हाल 'c':
		/* handle the optional parameter */
		ptr = &remcom_in_buffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &address))
			regs->pc = address;

		वापस 0;
	पूर्ण
	वापस -1; /* this means that we करो not want to निकास from the handler */
पूर्ण

पूर्णांक kgdb_arch_init(व्योम)
अणु
	get_pvr(&pvr); /* Fill PVR काष्ठाure */
	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	/* Nothing to करो */
पूर्ण

/*
 * Global data
 */
स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
#अगर_घोषित __MICROBLAZEEL__
	.gdb_bpt_instr = अणु0x18, 0x00, 0x0c, 0xbaपूर्ण, /* brki r16, 0x18 */
#अन्यथा
	.gdb_bpt_instr = अणु0xba, 0x0c, 0x00, 0x18पूर्ण, /* brki r16, 0x18 */
#पूर्ण_अगर
पूर्ण;
