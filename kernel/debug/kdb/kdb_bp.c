<शैली गुरु>
/*
 * Kernel Debugger Architecture Independent Breakpoपूर्णांक Handler
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1999-2004 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/kdb.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "kdb_private.h"

/*
 * Table of kdb_अवरोधpoपूर्णांकs
 */
kdb_bp_t kdb_अवरोधpoपूर्णांकs[KDB_MAXBPT];

अटल व्योम kdb_setsinglestep(काष्ठा pt_regs *regs)
अणु
	KDB_STATE_SET(DOING_SS);
पूर्ण

अटल अक्षर *kdb_rwtypes[] = अणु
	"Instruction(i)",
	"Instruction(Register)",
	"Data Write",
	"I/O",
	"Data Access"
पूर्ण;

अटल अक्षर *kdb_bptype(kdb_bp_t *bp)
अणु
	अगर (bp->bp_type < 0 || bp->bp_type > 4)
		वापस "";

	वापस kdb_rwtypes[bp->bp_type];
पूर्ण

अटल पूर्णांक kdb_parsebp(पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक *nextargp, kdb_bp_t *bp)
अणु
	पूर्णांक nextarg = *nextargp;
	पूर्णांक diag;

	bp->bph_length = 1;
	अगर ((argc + 1) != nextarg) अणु
		अगर (strnहालcmp(argv[nextarg], "datar", माप("datar")) == 0)
			bp->bp_type = BP_ACCESS_WATCHPOINT;
		अन्यथा अगर (strnहालcmp(argv[nextarg], "dataw", माप("dataw")) == 0)
			bp->bp_type = BP_WRITE_WATCHPOINT;
		अन्यथा अगर (strnहालcmp(argv[nextarg], "inst", माप("inst")) == 0)
			bp->bp_type = BP_HARDWARE_BREAKPOINT;
		अन्यथा
			वापस KDB_ARGCOUNT;

		bp->bph_length = 1;

		nextarg++;

		अगर ((argc + 1) != nextarg) अणु
			अचिन्हित दीर्घ len;

			diag = kdbgetularg((अक्षर *)argv[nextarg],
					   &len);
			अगर (diag)
				वापस diag;


			अगर (len > 8)
				वापस KDB_BADLENGTH;

			bp->bph_length = len;
			nextarg++;
		पूर्ण

		अगर ((argc + 1) != nextarg)
			वापस KDB_ARGCOUNT;
	पूर्ण

	*nextargp = nextarg;
	वापस 0;
पूर्ण

अटल पूर्णांक _kdb_bp_हटाओ(kdb_bp_t *bp)
अणु
	पूर्णांक ret = 1;
	अगर (!bp->bp_installed)
		वापस ret;
	अगर (!bp->bp_type)
		ret = dbg_हटाओ_sw_अवरोध(bp->bp_addr);
	अन्यथा
		ret = arch_kgdb_ops.हटाओ_hw_अवरोधpoपूर्णांक(bp->bp_addr,
			 bp->bph_length,
			 bp->bp_type);
	अगर (ret == 0)
		bp->bp_installed = 0;
	वापस ret;
पूर्ण

अटल व्योम kdb_handle_bp(काष्ठा pt_regs *regs, kdb_bp_t *bp)
अणु
	अगर (KDB_DEBUG(BP))
		kdb_म_लिखो("regs->ip = 0x%lx\n", inकाष्ठाion_poपूर्णांकer(regs));

	/*
	 * Setup single step
	 */
	kdb_setsinglestep(regs);

	/*
	 * Reset delay attribute
	 */
	bp->bp_delay = 0;
	bp->bp_delayed = 1;
पूर्ण

अटल पूर्णांक _kdb_bp_install(काष्ठा pt_regs *regs, kdb_bp_t *bp)
अणु
	पूर्णांक ret;
	/*
	 * Install the अवरोधpoपूर्णांक, अगर it is not alपढ़ोy installed.
	 */

	अगर (KDB_DEBUG(BP))
		kdb_म_लिखो("%s: bp_installed %d\n",
			   __func__, bp->bp_installed);
	अगर (!KDB_STATE(SSBPT))
		bp->bp_delay = 0;
	अगर (bp->bp_installed)
		वापस 1;
	अगर (bp->bp_delay || (bp->bp_delayed && KDB_STATE(DOING_SS))) अणु
		अगर (KDB_DEBUG(BP))
			kdb_म_लिखो("%s: delayed bp\n", __func__);
		kdb_handle_bp(regs, bp);
		वापस 0;
	पूर्ण
	अगर (!bp->bp_type)
		ret = dbg_set_sw_अवरोध(bp->bp_addr);
	अन्यथा
		ret = arch_kgdb_ops.set_hw_अवरोधpoपूर्णांक(bp->bp_addr,
			 bp->bph_length,
			 bp->bp_type);
	अगर (ret == 0) अणु
		bp->bp_installed = 1;
	पूर्ण अन्यथा अणु
		kdb_म_लिखो("%s: failed to set breakpoint at 0x%lx\n",
			   __func__, bp->bp_addr);
		अगर (!bp->bp_type) अणु
			kdb_म_लिखो("Software breakpoints are unavailable.\n"
				   "  Boot the kernel with rodata=off\n"
				   "  OR use hw breaks: help bph\n");
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kdb_bp_install
 *
 *	Install kdb_अवरोधpoपूर्णांकs prior to वापसing from the
 *	kernel debugger.  This allows the kdb_अवरोधpoपूर्णांकs to be set
 *	upon functions that are used पूर्णांकernally by kdb, such as
 *	prपूर्णांकk().  This function is only called once per kdb session.
 */
व्योम kdb_bp_install(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KDB_MAXBPT; i++) अणु
		kdb_bp_t *bp = &kdb_अवरोधpoपूर्णांकs[i];

		अगर (KDB_DEBUG(BP)) अणु
			kdb_म_लिखो("%s: bp %d bp_enabled %d\n",
				   __func__, i, bp->bp_enabled);
		पूर्ण
		अगर (bp->bp_enabled)
			_kdb_bp_install(regs, bp);
	पूर्ण
पूर्ण

/*
 * kdb_bp_हटाओ
 *
 *	Remove kdb_अवरोधpoपूर्णांकs upon entry to the kernel debugger.
 *
 * Parameters:
 *	None.
 * Outमाला_दो:
 *	None.
 * Returns:
 *	None.
 * Locking:
 *	None.
 * Remarks:
 */
व्योम kdb_bp_हटाओ(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = KDB_MAXBPT - 1; i >= 0; i--) अणु
		kdb_bp_t *bp = &kdb_अवरोधpoपूर्णांकs[i];

		अगर (KDB_DEBUG(BP)) अणु
			kdb_म_लिखो("%s: bp %d bp_enabled %d\n",
				   __func__, i, bp->bp_enabled);
		पूर्ण
		अगर (bp->bp_enabled)
			_kdb_bp_हटाओ(bp);
	पूर्ण
पूर्ण


/*
 * kdb_prपूर्णांकbp
 *
 *	Internal function to क्रमmat and prपूर्णांक a अवरोधpoपूर्णांक entry.
 *
 * Parameters:
 *	None.
 * Outमाला_दो:
 *	None.
 * Returns:
 *	None.
 * Locking:
 *	None.
 * Remarks:
 */

अटल व्योम kdb_prपूर्णांकbp(kdb_bp_t *bp, पूर्णांक i)
अणु
	kdb_म_लिखो("%s ", kdb_bptype(bp));
	kdb_म_लिखो("BP #%d at ", i);
	kdb_symbol_prपूर्णांक(bp->bp_addr, शून्य, KDB_SP_DEFAULT);

	अगर (bp->bp_enabled)
		kdb_म_लिखो("\n    is enabled ");
	अन्यथा
		kdb_म_लिखो("\n    is disabled");

	kdb_म_लिखो("  addr at %016lx, hardtype=%d installed=%d\n",
		   bp->bp_addr, bp->bp_type, bp->bp_installed);

	kdb_म_लिखो("\n");
पूर्ण

/*
 * kdb_bp
 *
 *	Handle the bp commands.
 *
 *	[bp|bph] <addr-expression> [DATAR|DATAW]
 *
 * Parameters:
 *	argc	Count of arguments in argv
 *	argv	Space delimited command line arguments
 * Outमाला_दो:
 *	None.
 * Returns:
 *	Zero क्रम success, a kdb diagnostic अगर failure.
 * Locking:
 *	None.
 * Remarks:
 *
 *	bp	Set अवरोधpoपूर्णांक on all cpus.  Only use hardware assist अगर need.
 *	bph	Set अवरोधpoपूर्णांक on all cpus.  Force hardware रेजिस्टर
 */

अटल पूर्णांक kdb_bp(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i, bpno;
	kdb_bp_t *bp, *bp_check;
	पूर्णांक diag;
	अक्षर *symname = शून्य;
	दीर्घ offset = 0ul;
	पूर्णांक nextarg;
	kdb_bp_t ढाँचा = अणु0पूर्ण;

	अगर (argc == 0) अणु
		/*
		 * Display अवरोधpoपूर्णांक table
		 */
		क्रम (bpno = 0, bp = kdb_अवरोधpoपूर्णांकs; bpno < KDB_MAXBPT;
		     bpno++, bp++) अणु
			अगर (bp->bp_मुक्त)
				जारी;
			kdb_prपूर्णांकbp(bp, bpno);
		पूर्ण

		वापस 0;
	पूर्ण

	nextarg = 1;
	diag = kdbgetaddrarg(argc, argv, &nextarg, &ढाँचा.bp_addr,
			     &offset, &symname);
	अगर (diag)
		वापस diag;
	अगर (!ढाँचा.bp_addr)
		वापस KDB_BADINT;

	/*
	 * This check is redundant (since the अवरोधpoपूर्णांक machinery should
	 * be करोing the same check during kdb_bp_install) but gives the
	 * user immediate feedback.
	 */
	diag = kgdb_validate_अवरोध_address(ढाँचा.bp_addr);
	अगर (diag)
		वापस diag;

	/*
	 * Find an empty bp काष्ठाure to allocate
	 */
	क्रम (bpno = 0, bp = kdb_अवरोधpoपूर्णांकs; bpno < KDB_MAXBPT; bpno++, bp++) अणु
		अगर (bp->bp_मुक्त)
			अवरोध;
	पूर्ण

	अगर (bpno == KDB_MAXBPT)
		वापस KDB_TOOMANYBPT;

	अगर (म_भेद(argv[0], "bph") == 0) अणु
		ढाँचा.bp_type = BP_HARDWARE_BREAKPOINT;
		diag = kdb_parsebp(argc, argv, &nextarg, &ढाँचा);
		अगर (diag)
			वापस diag;
	पूर्ण अन्यथा अणु
		ढाँचा.bp_type = BP_BREAKPOINT;
	पूर्ण

	/*
	 * Check क्रम clashing अवरोधpoपूर्णांकs.
	 *
	 * Note, in this design we can't have hardware अवरोधpoपूर्णांकs
	 * enabled क्रम both पढ़ो and ग_लिखो on the same address.
	 */
	क्रम (i = 0, bp_check = kdb_अवरोधpoपूर्णांकs; i < KDB_MAXBPT;
	     i++, bp_check++) अणु
		अगर (!bp_check->bp_मुक्त &&
		    bp_check->bp_addr == ढाँचा.bp_addr) अणु
			kdb_म_लिखो("You already have a breakpoint at "
				   kdb_bfd_vma_fmt0 "\n", ढाँचा.bp_addr);
			वापस KDB_DUPBPT;
		पूर्ण
	पूर्ण

	ढाँचा.bp_enabled = 1;

	/*
	 * Actually allocate the अवरोधpoपूर्णांक found earlier
	 */
	*bp = ढाँचा;
	bp->bp_मुक्त = 0;

	kdb_prपूर्णांकbp(bp, bpno);

	वापस 0;
पूर्ण

/*
 * kdb_bc
 *
 *	Handles the 'bc', 'be', and 'bd' commands
 *
 *	[bd|bc|be] <अवरोधpoपूर्णांक-number>
 *	[bd|bc|be] *
 *
 * Parameters:
 *	argc	Count of arguments in argv
 *	argv	Space delimited command line arguments
 * Outमाला_दो:
 *	None.
 * Returns:
 *	Zero क्रम success, a kdb diagnostic क्रम failure
 * Locking:
 *	None.
 * Remarks:
 */
अटल पूर्णांक kdb_bc(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित दीर्घ addr;
	kdb_bp_t *bp = शून्य;
	पूर्णांक lowbp = KDB_MAXBPT;
	पूर्णांक highbp = 0;
	पूर्णांक करोne = 0;
	पूर्णांक i;
	पूर्णांक diag = 0;

	पूर्णांक cmd;			/* KDBCMD_B? */
#घोषणा KDBCMD_BC	0
#घोषणा KDBCMD_BE	1
#घोषणा KDBCMD_BD	2

	अगर (म_भेद(argv[0], "be") == 0)
		cmd = KDBCMD_BE;
	अन्यथा अगर (म_भेद(argv[0], "bd") == 0)
		cmd = KDBCMD_BD;
	अन्यथा
		cmd = KDBCMD_BC;

	अगर (argc != 1)
		वापस KDB_ARGCOUNT;

	अगर (म_भेद(argv[1], "*") == 0) अणु
		lowbp = 0;
		highbp = KDB_MAXBPT;
	पूर्ण अन्यथा अणु
		diag = kdbgetularg(argv[1], &addr);
		अगर (diag)
			वापस diag;

		/*
		 * For addresses less than the maximum अवरोधpoपूर्णांक number,
		 * assume that the अवरोधpoपूर्णांक number is desired.
		 */
		अगर (addr < KDB_MAXBPT) अणु
			lowbp = highbp = addr;
			highbp++;
		पूर्ण अन्यथा अणु
			क्रम (i = 0, bp = kdb_अवरोधpoपूर्णांकs; i < KDB_MAXBPT;
			    i++, bp++) अणु
				अगर (bp->bp_addr == addr) अणु
					lowbp = highbp = i;
					highbp++;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Now operate on the set of अवरोधpoपूर्णांकs matching the input
	 * criteria (either '*' क्रम all, or an inभागidual अवरोधpoपूर्णांक).
	 */
	क्रम (bp = &kdb_अवरोधpoपूर्णांकs[lowbp], i = lowbp;
	    i < highbp;
	    i++, bp++) अणु
		अगर (bp->bp_मुक्त)
			जारी;

		करोne++;

		चयन (cmd) अणु
		हाल KDBCMD_BC:
			bp->bp_enabled = 0;

			kdb_म_लिखो("Breakpoint %d at "
				   kdb_bfd_vma_fmt " cleared\n",
				   i, bp->bp_addr);

			bp->bp_addr = 0;
			bp->bp_मुक्त = 1;

			अवरोध;
		हाल KDBCMD_BE:
			bp->bp_enabled = 1;

			kdb_म_लिखो("Breakpoint %d at "
				   kdb_bfd_vma_fmt " enabled",
				   i, bp->bp_addr);

			kdb_म_लिखो("\n");
			अवरोध;
		हाल KDBCMD_BD:
			अगर (!bp->bp_enabled)
				अवरोध;

			bp->bp_enabled = 0;

			kdb_म_लिखो("Breakpoint %d at "
				   kdb_bfd_vma_fmt " disabled\n",
				   i, bp->bp_addr);

			अवरोध;
		पूर्ण
		अगर (bp->bp_delay && (cmd == KDBCMD_BC || cmd == KDBCMD_BD)) अणु
			bp->bp_delay = 0;
			KDB_STATE_CLEAR(SSBPT);
		पूर्ण
	पूर्ण

	वापस (!करोne) ? KDB_BPTNOTFOUND : 0;
पूर्ण

/*
 * kdb_ss
 *
 *	Process the 'ss' (Single Step) command.
 *
 *	ss
 *
 * Parameters:
 *	argc	Argument count
 *	argv	Argument vector
 * Outमाला_दो:
 *	None.
 * Returns:
 *	KDB_CMD_SS क्रम success, a kdb error अगर failure.
 * Locking:
 *	None.
 * Remarks:
 *
 *	Set the arch specअगरic option to trigger a debug trap after the next
 *	inकाष्ठाion.
 */

अटल पूर्णांक kdb_ss(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अगर (argc != 0)
		वापस KDB_ARGCOUNT;
	/*
	 * Set trace flag and go.
	 */
	KDB_STATE_SET(DOING_SS);
	वापस KDB_CMD_SS;
पूर्ण

अटल kdbtab_t bptab[] = अणु
	अणु	.cmd_name = "bp",
		.cmd_func = kdb_bp,
		.cmd_usage = "[<vaddr>]",
		.cmd_help = "Set/Display breakpoints",
		.cmd_flags = KDB_ENABLE_FLOW_CTRL | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "bl",
		.cmd_func = kdb_bp,
		.cmd_usage = "[<vaddr>]",
		.cmd_help = "Display breakpoints",
		.cmd_flags = KDB_ENABLE_FLOW_CTRL | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "bc",
		.cmd_func = kdb_bc,
		.cmd_usage = "<bpnum>",
		.cmd_help = "Clear Breakpoint",
		.cmd_flags = KDB_ENABLE_FLOW_CTRL,
	पूर्ण,
	अणु	.cmd_name = "be",
		.cmd_func = kdb_bc,
		.cmd_usage = "<bpnum>",
		.cmd_help = "Enable Breakpoint",
		.cmd_flags = KDB_ENABLE_FLOW_CTRL,
	पूर्ण,
	अणु	.cmd_name = "bd",
		.cmd_func = kdb_bc,
		.cmd_usage = "<bpnum>",
		.cmd_help = "Disable Breakpoint",
		.cmd_flags = KDB_ENABLE_FLOW_CTRL,
	पूर्ण,
	अणु	.cmd_name = "ss",
		.cmd_func = kdb_ss,
		.cmd_usage = "",
		.cmd_help = "Single Step",
		.cmd_minlen = 1,
		.cmd_flags = KDB_ENABLE_FLOW_CTRL | KDB_REPEAT_NO_ARGS,
	पूर्ण,
पूर्ण;

अटल kdbtab_t bphcmd = अणु
	.cmd_name = "bph",
	.cmd_func = kdb_bp,
	.cmd_usage = "[<vaddr>]",
	.cmd_help = "[datar [length]|dataw [length]]   Set hw brk",
	.cmd_flags = KDB_ENABLE_FLOW_CTRL | KDB_REPEAT_NO_ARGS,
पूर्ण;

/* Initialize the अवरोधpoपूर्णांक table and रेजिस्टर	अवरोधpoपूर्णांक commands. */

व्योम __init kdb_initbptab(व्योम)
अणु
	पूर्णांक i;
	kdb_bp_t *bp;

	/*
	 * First समय initialization.
	 */
	स_रखो(&kdb_अवरोधpoपूर्णांकs, '\0', माप(kdb_अवरोधpoपूर्णांकs));

	क्रम (i = 0, bp = kdb_अवरोधpoपूर्णांकs; i < KDB_MAXBPT; i++, bp++)
		bp->bp_मुक्त = 1;

	kdb_रेजिस्टर_table(bptab, ARRAY_SIZE(bptab));
	अगर (arch_kgdb_ops.flags & KGDB_HW_BREAKPOINT)
		kdb_रेजिस्टर_table(&bphcmd, 1);
पूर्ण
