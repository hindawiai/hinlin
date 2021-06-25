<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/err_ev6.c
 *
 *	Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 *	Error handling code supporting Alpha प्रणालीs
 */

#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/err_common.h>
#समावेश <यंत्र/err_ev6.h>

#समावेश "err_impl.h"
#समावेश "proto.h"

अटल पूर्णांक
ev6_parse_ibox(u64 i_stat, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_REPORT;

#घोषणा EV6__I_STAT__PAR	(1UL << 29)
#घोषणा EV6__I_STAT__ERRMASK	(EV6__I_STAT__PAR)

	अगर (!(i_stat & EV6__I_STAT__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

	अगर (!prपूर्णांक)
		वापस status;

	अगर (i_stat & EV6__I_STAT__PAR)
		prपूर्णांकk("%s    Icache parity error\n", err_prपूर्णांक_prefix);

	वापस status;
पूर्ण

अटल पूर्णांक
ev6_parse_mbox(u64 mm_stat, u64 d_stat, u64 c_stat, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_REPORT;

#घोषणा EV6__MM_STAT__DC_TAG_PERR	(1UL << 10)
#घोषणा EV6__MM_STAT__ERRMASK		(EV6__MM_STAT__DC_TAG_PERR)
#घोषणा EV6__D_STAT__TPERR_P0		(1UL << 0)
#घोषणा EV6__D_STAT__TPERR_P1		(1UL << 1)
#घोषणा EV6__D_STAT__ECC_ERR_ST		(1UL << 2)
#घोषणा EV6__D_STAT__ECC_ERR_LD		(1UL << 3)
#घोषणा EV6__D_STAT__SEO		(1UL << 4)
#घोषणा EV6__D_STAT__ERRMASK		(EV6__D_STAT__TPERR_P0 |	\
                                         EV6__D_STAT__TPERR_P1 | 	\
                                         EV6__D_STAT__ECC_ERR_ST | 	\
                                         EV6__D_STAT__ECC_ERR_LD | 	\
                                         EV6__D_STAT__SEO)

	अगर (!(d_stat & EV6__D_STAT__ERRMASK) && 
	    !(mm_stat & EV6__MM_STAT__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

	अगर (!prपूर्णांक)
		वापस status;

	अगर (mm_stat & EV6__MM_STAT__DC_TAG_PERR)
		prपूर्णांकk("%s    Dcache tag parity error on probe\n",
		       err_prपूर्णांक_prefix);
	अगर (d_stat & EV6__D_STAT__TPERR_P0)
		prपूर्णांकk("%s    Dcache tag parity error - pipe 0\n",
		       err_prपूर्णांक_prefix);
	अगर (d_stat & EV6__D_STAT__TPERR_P1)
		prपूर्णांकk("%s    Dcache tag parity error - pipe 1\n",
		       err_prपूर्णांक_prefix);
	अगर (d_stat & EV6__D_STAT__ECC_ERR_ST)
		prपूर्णांकk("%s    ECC error occurred on a store\n", 
		       err_prपूर्णांक_prefix);
	अगर (d_stat & EV6__D_STAT__ECC_ERR_LD)
		prपूर्णांकk("%s    ECC error occurred on a %s load\n",
		       err_prपूर्णांक_prefix,
		       c_stat ? "" : "speculative ");
	अगर (d_stat & EV6__D_STAT__SEO)
		prपूर्णांकk("%s    Dcache second error\n", err_prपूर्णांक_prefix);

	वापस status;
पूर्ण

अटल पूर्णांक
ev6_parse_cbox(u64 c_addr, u64 c1_syn, u64 c2_syn, 
	       u64 c_stat, u64 c_sts, पूर्णांक prपूर्णांक)
अणु
	अटल स्थिर अक्षर * स्थिर sourcename[] = अणु
		"UNKNOWN", "UNKNOWN", "UNKNOWN",
		"MEMORY", "BCACHE", "DCACHE",
		"BCACHE PROBE", "BCACHE PROBE"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर streamname[] = अणु "D", "I" पूर्ण;
	अटल स्थिर अक्षर * स्थिर bitsname[] = अणु "SINGLE", "DOUBLE" पूर्ण;
	पूर्णांक status = MCHK_DISPOSITION_REPORT;
	पूर्णांक source = -1, stream = -1, bits = -1;

#घोषणा EV6__C_STAT__BC_PERR		(0x01)
#घोषणा EV6__C_STAT__DC_PERR		(0x02)
#घोषणा EV6__C_STAT__DSTREAM_MEM_ERR	(0x03)
#घोषणा EV6__C_STAT__DSTREAM_BC_ERR	(0x04)
#घोषणा EV6__C_STAT__DSTREAM_DC_ERR	(0x05)
#घोषणा EV6__C_STAT__PROBE_BC_ERR0	(0x06)	/* both 6 and 7 indicate... */
#घोषणा EV6__C_STAT__PROBE_BC_ERR1	(0x07)	/* ...probe bc error.       */
#घोषणा EV6__C_STAT__ISTREAM_MEM_ERR	(0x0B)
#घोषणा EV6__C_STAT__ISTREAM_BC_ERR	(0x0C)
#घोषणा EV6__C_STAT__DSTREAM_MEM_DBL	(0x13)
#घोषणा EV6__C_STAT__DSTREAM_BC_DBL	(0x14)
#घोषणा EV6__C_STAT__ISTREAM_MEM_DBL	(0x1B)
#घोषणा EV6__C_STAT__ISTREAM_BC_DBL	(0x1C)
#घोषणा EV6__C_STAT__SOURCE_MEMORY	(0x03)
#घोषणा EV6__C_STAT__SOURCE_BCACHE	(0x04)
#घोषणा EV6__C_STAT__SOURCE__S		(0)
#घोषणा EV6__C_STAT__SOURCE__M 		(0x07)
#घोषणा EV6__C_STAT__ISTREAM__S		(3)
#घोषणा EV6__C_STAT__ISTREAM__M		(0x01)
#घोषणा EV6__C_STAT__DOUBLE__S		(4)
#घोषणा EV6__C_STAT__DOUBLE__M		(0x01)
#घोषणा EV6__C_STAT__ERRMASK		(0x1F)
#घोषणा EV6__C_STS__SHARED		(1 << 0)
#घोषणा EV6__C_STS__सूचीTY		(1 << 1)
#घोषणा EV6__C_STS__VALID		(1 << 2)
#घोषणा EV6__C_STS__PARITY		(1 << 3)

	अगर (!(c_stat & EV6__C_STAT__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

	अगर (!prपूर्णांक)
		वापस status;

	source = EXTRACT(c_stat, EV6__C_STAT__SOURCE);
	stream = EXTRACT(c_stat, EV6__C_STAT__ISTREAM);
	bits = EXTRACT(c_stat, EV6__C_STAT__DOUBLE);

	अगर (c_stat & EV6__C_STAT__BC_PERR) अणु
		prपूर्णांकk("%s    Bcache tag parity error\n", err_prपूर्णांक_prefix);
		source = -1;
	पूर्ण

	अगर (c_stat & EV6__C_STAT__DC_PERR) अणु
		prपूर्णांकk("%s    Dcache tag parity error\n", err_prपूर्णांक_prefix);
		source = -1;
	पूर्ण

	अगर (c_stat == EV6__C_STAT__PROBE_BC_ERR0 ||
	    c_stat == EV6__C_STAT__PROBE_BC_ERR1) अणु
		prपूर्णांकk("%s    Bcache single-bit error on a probe hit\n",
		       err_prपूर्णांक_prefix);
		source = -1;
	पूर्ण

	अगर (source != -1) 
		prपूर्णांकk("%s    %s-STREAM %s-BIT ECC error from %s\n",
		       err_prपूर्णांक_prefix,
		       streamname[stream], bitsname[bits], sourcename[source]);

	prपूर्णांकk("%s    Address: 0x%016llx\n"
	         "    Syndrome[upper.lower]: %02llx.%02llx\n",
	       err_prपूर्णांक_prefix,
	       c_addr,
	       c2_syn, c1_syn);

	अगर (source == EV6__C_STAT__SOURCE_MEMORY ||
	    source == EV6__C_STAT__SOURCE_BCACHE) 
		prपूर्णांकk("%s    Block status: %s%s%s%s\n",
		       err_prपूर्णांक_prefix,
		       (c_sts & EV6__C_STS__SHARED) ? "SHARED " : "",
		       (c_sts & EV6__C_STS__सूचीTY)  ? "DIRTY "  : "",
		       (c_sts & EV6__C_STS__VALID)  ? "VALID "  : "",
		       (c_sts & EV6__C_STS__PARITY) ? "PARITY " : "");
		
	वापस status;
पूर्ण

व्योम
ev6_रेजिस्टर_error_handlers(व्योम)
अणु
	/* None right now. */
पूर्ण

पूर्णांक
ev6_process_logout_frame(काष्ठा el_common *mchk_header, पूर्णांक prपूर्णांक)
अणु
	काष्ठा el_common_EV6_mcheck *ev6mchk = 
		(काष्ठा el_common_EV6_mcheck *)mchk_header;
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	status |= ev6_parse_ibox(ev6mchk->I_STAT, prपूर्णांक);
	status |= ev6_parse_mbox(ev6mchk->MM_STAT, ev6mchk->DC_STAT, 
				 ev6mchk->C_STAT, prपूर्णांक);
	status |= ev6_parse_cbox(ev6mchk->C_ADDR, ev6mchk->DC1_SYNDROME,
				 ev6mchk->DC0_SYNDROME, ev6mchk->C_STAT,
				 ev6mchk->C_STS, prपूर्णांक);

	अगर (!prपूर्णांक)
		वापस status;

	अगर (status != MCHK_DISPOSITION_DISMISS) अणु
		अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;

		/*
		 * Dump some additional inक्रमmation from the frame
		 */
		prपूर्णांकk("%s    EXC_ADDR: 0x%016lx   IER_CM: 0x%016lx"
		            "   ISUM: 0x%016lx\n"
		         "    PAL_BASE: 0x%016lx   I_CTL:  0x%016lx"
		            "   PCTX: 0x%016lx\n",
		       err_prपूर्णांक_prefix,
		       ev6mchk->EXC_ADDR, ev6mchk->IER_CM, ev6mchk->ISUM,
		       ev6mchk->PAL_BASE, ev6mchk->I_CTL, ev6mchk->PCTX);

		अगर (status == MCHK_DISPOSITION_UNKNOWN_ERROR) अणु
			prपूर्णांकk("%s    UNKNOWN error, frame follows:\n",
			       err_prपूर्णांक_prefix);
		पूर्ण अन्यथा अणु
			/* had decode -- करोwngrade prपूर्णांक level क्रम frame */
			err_prपूर्णांक_prefix = KERN_NOTICE;
		पूर्ण

		mchk_dump_logout_frame(mchk_header);

		err_prपूर्णांक_prefix = saved_err_prefix;
	पूर्ण

	वापस status;
पूर्ण

व्योम
ev6_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *mchk_header = (काष्ठा el_common *)la_ptr;

	/*
	 * Sync the processor
	 */
	mb();
	draina();

	/*
	 * Parse the logout frame without prपूर्णांकing first. If the only error(s)
	 * found are have a disposition of "dismiss", then just dismiss them
	 * and करोn't prपूर्णांक any message
	 */
	अगर (ev6_process_logout_frame(mchk_header, 0) != 
	    MCHK_DISPOSITION_DISMISS) अणु
		अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;
		err_prपूर्णांक_prefix = KERN_CRIT;

		/*
		 * Either a nondismissable error was detected or no
		 * recognized error was detected  in the logout frame 
		 * -- report the error in either हाल
		 */
		prपूर्णांकk("%s*CPU %s Error (Vector 0x%x) reported on CPU %d:\n", 
		       err_prपूर्णांक_prefix,
		       (vector == SCB_Q_PROCERR)?"Correctable":"Uncorrectable",
		       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
		
		ev6_process_logout_frame(mchk_header, 1);
		dik_show_regs(get_irq_regs(), शून्य);

		err_prपूर्णांक_prefix = saved_err_prefix;
	पूर्ण

	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
पूर्ण

