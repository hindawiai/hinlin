<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/err_titan.c
 *
 *	Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 *	Error handling code supporting TITAN प्रणालीs
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_titan.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/err_common.h>
#समावेश <यंत्र/err_ev6.h>
#समावेश <यंत्र/irq_regs.h>

#समावेश "err_impl.h"
#समावेश "proto.h"


अटल पूर्णांक
titan_parse_c_misc(u64 c_misc, पूर्णांक prपूर्णांक)
अणु
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अक्षर *src;
	पूर्णांक nxs = 0;
#पूर्ण_अगर
	पूर्णांक status = MCHK_DISPOSITION_REPORT;

#घोषणा TITAN__CCHIP_MISC__NXM		(1UL << 28)
#घोषणा TITAN__CCHIP_MISC__NXS__S	(29)
#घोषणा TITAN__CCHIP_MISC__NXS__M	(0x7)

	अगर (!(c_misc & TITAN__CCHIP_MISC__NXM))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (!prपूर्णांक)
		वापस status;

	nxs = EXTRACT(c_misc, TITAN__CCHIP_MISC__NXS);
	चयन(nxs) अणु
	हाल 0:	/* CPU 0 */
	हाल 1:	/* CPU 1 */
	हाल 2:	/* CPU 2 */
	हाल 3:	/* CPU 3 */
		src = "CPU";
		/* num is alपढ़ोy the CPU number */
		अवरोध;
	हाल 4:	/* Pchip 0 */
	हाल 5:	/* Pchip 1 */
		src = "Pchip";
		nxs -= 4;
		अवरोध;
	शेष:/* reserved */
		src = "Unknown, NXS =";
		/* leave num untouched */
		अवरोध;
	पूर्ण

	prपूर्णांकk("%s    Non-existent memory access from: %s %d\n", 
	       err_prपूर्णांक_prefix, src, nxs);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण

अटल पूर्णांक
titan_parse_p_serror(पूर्णांक which, u64 serror, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_REPORT;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अटल स्थिर अक्षर * स्थिर serror_src[] = अणु
		"GPCI", "APCI", "AGP HP", "AGP LP"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर serror_cmd[] = अणु
		"DMA Read", "DMA RMW", "SGTE Read", "Reserved"
	पूर्ण;
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

#घोषणा TITAN__PCHIP_SERROR__LOST_UECC	(1UL << 0)
#घोषणा TITAN__PCHIP_SERROR__UECC	(1UL << 1)
#घोषणा TITAN__PCHIP_SERROR__CRE	(1UL << 2)
#घोषणा TITAN__PCHIP_SERROR__NXIO	(1UL << 3)
#घोषणा TITAN__PCHIP_SERROR__LOST_CRE	(1UL << 4)
#घोषणा TITAN__PCHIP_SERROR__ECCMASK	(TITAN__PCHIP_SERROR__UECC |	  \
					 TITAN__PCHIP_SERROR__CRE)
#घोषणा TITAN__PCHIP_SERROR__ERRMASK	(TITAN__PCHIP_SERROR__LOST_UECC | \
					 TITAN__PCHIP_SERROR__UECC |	  \
					 TITAN__PCHIP_SERROR__CRE |	  \
					 TITAN__PCHIP_SERROR__NXIO |	  \
					 TITAN__PCHIP_SERROR__LOST_CRE)
#घोषणा TITAN__PCHIP_SERROR__SRC__S	(52)
#घोषणा TITAN__PCHIP_SERROR__SRC__M	(0x3)
#घोषणा TITAN__PCHIP_SERROR__CMD__S	(54)
#घोषणा TITAN__PCHIP_SERROR__CMD__M	(0x3)
#घोषणा TITAN__PCHIP_SERROR__SYN__S	(56)
#घोषणा TITAN__PCHIP_SERROR__SYN__M	(0xff)
#घोषणा TITAN__PCHIP_SERROR__ADDR__S	(15)
#घोषणा TITAN__PCHIP_SERROR__ADDR__M	(0xffffffffUL)

	अगर (!(serror & TITAN__PCHIP_SERROR__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (!prपूर्णांक)
		वापस status;

	prपूर्णांकk("%s  PChip %d SERROR: %016llx\n",
	       err_prपूर्णांक_prefix, which, serror);
	अगर (serror & TITAN__PCHIP_SERROR__ECCMASK) अणु
		prपूर्णांकk("%s    %sorrectable ECC Error:\n"
		       "      Source: %-6s  Command: %-8s  Syndrome: 0x%08x\n"
		       "      Address: 0x%llx\n",
		       err_prपूर्णांक_prefix,
		       (serror & TITAN__PCHIP_SERROR__UECC) ? "Unc" : "C",
		       serror_src[EXTRACT(serror, TITAN__PCHIP_SERROR__SRC)],
		       serror_cmd[EXTRACT(serror, TITAN__PCHIP_SERROR__CMD)],
		       (अचिन्हित)EXTRACT(serror, TITAN__PCHIP_SERROR__SYN),
		       EXTRACT(serror, TITAN__PCHIP_SERROR__ADDR));
	पूर्ण
	अगर (serror & TITAN__PCHIP_SERROR__NXIO)
		prपूर्णांकk("%s    Non Existent I/O Error\n", err_prपूर्णांक_prefix);
	अगर (serror & TITAN__PCHIP_SERROR__LOST_UECC)
		prपूर्णांकk("%s    Lost Uncorrectable ECC Error\n", 
		       err_prपूर्णांक_prefix);
	अगर (serror & TITAN__PCHIP_SERROR__LOST_CRE)
		prपूर्णांकk("%s    Lost Correctable ECC Error\n", err_prपूर्णांक_prefix);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण

अटल पूर्णांक 
titan_parse_p_लिखो_त्रुटि(पूर्णांक which, पूर्णांक port, u64 लिखो_त्रुटि, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक cmd;
	अचिन्हित दीर्घ addr;
	पूर्णांक status = MCHK_DISPOSITION_REPORT;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अटल स्थिर अक्षर * स्थिर लिखो_त्रुटि_cmd[] = अणु
		"Interrupt Acknowledge", "Special Cycle",
		"I/O Read",		"I/O Write",
		"Reserved",		"Reserved",
		"Memory Read",		"Memory Write",
		"Reserved",		"Reserved",
		"Configuration Read",	"Configuration Write",
		"Memory Read Multiple",	"Dual Address Cycle",
		"Memory Read Line",	"Memory Write and Invalidate"
	पूर्ण;
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

#घोषणा TITAN__PCHIP_PERROR__LOST	(1UL << 0)
#घोषणा TITAN__PCHIP_PERROR__SERR	(1UL << 1)
#घोषणा TITAN__PCHIP_PERROR__PERR	(1UL << 2)
#घोषणा TITAN__PCHIP_PERROR__DCRTO	(1UL << 3)
#घोषणा TITAN__PCHIP_PERROR__SGE	(1UL << 4)
#घोषणा TITAN__PCHIP_PERROR__APE	(1UL << 5)
#घोषणा TITAN__PCHIP_PERROR__TA		(1UL << 6)
#घोषणा TITAN__PCHIP_PERROR__DPE	(1UL << 7)
#घोषणा TITAN__PCHIP_PERROR__NDS	(1UL << 8)
#घोषणा TITAN__PCHIP_PERROR__IPTPR	(1UL << 9)
#घोषणा TITAN__PCHIP_PERROR__IPTPW	(1UL << 10)
#घोषणा TITAN__PCHIP_PERROR__ERRMASK	(TITAN__PCHIP_PERROR__LOST |	\
					 TITAN__PCHIP_PERROR__SERR |	\
					 TITAN__PCHIP_PERROR__PERR |	\
					 TITAN__PCHIP_PERROR__DCRTO |	\
					 TITAN__PCHIP_PERROR__SGE |	\
					 TITAN__PCHIP_PERROR__APE |	\
					 TITAN__PCHIP_PERROR__TA |	\
					 TITAN__PCHIP_PERROR__DPE |	\
					 TITAN__PCHIP_PERROR__NDS |	\
					 TITAN__PCHIP_PERROR__IPTPR |	\
					 TITAN__PCHIP_PERROR__IPTPW)
#घोषणा TITAN__PCHIP_PERROR__DAC	(1UL << 47)
#घोषणा TITAN__PCHIP_PERROR__MWIN	(1UL << 48)
#घोषणा TITAN__PCHIP_PERROR__CMD__S	(52)
#घोषणा TITAN__PCHIP_PERROR__CMD__M	(0x0f)
#घोषणा TITAN__PCHIP_PERROR__ADDR__S	(14)
#घोषणा TITAN__PCHIP_PERROR__ADDR__M	(0x1fffffffful)

	अगर (!(लिखो_त्रुटि & TITAN__PCHIP_PERROR__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

	cmd = EXTRACT(लिखो_त्रुटि, TITAN__PCHIP_PERROR__CMD);
	addr = EXTRACT(लिखो_त्रुटि, TITAN__PCHIP_PERROR__ADDR) << 2;

	/*
	 * Initializing the BIOS on a video card on a bus without
	 * a south bridge (subtractive decode agent) can result in 
	 * master पातs as the BIOS probes the capabilities of the
	 * card. XFree86 करोes such initialization. If the error
	 * is a master पात (No DevSel as PCI Master) and the command
	 * is an I/O पढ़ो or ग_लिखो below the address where we start
	 * assigning PCI I/O spaces (SRM uses 0x1000), then mark the
	 * error as dismissable so starting XFree86 करोesn't result
	 * in a series of uncorrectable errors being reported. Also
	 * dismiss master पातs to VGA frame buffer space
	 * (0xA0000 - 0xC0000) and legacy BIOS space (0xC0000 - 0x100000)
	 * क्रम the same reason.
	 *
	 * Also mark the error dismissible अगर it looks like the right
	 * error but only the Lost bit is set. Since the BIOS initialization
	 * can cause multiple master पातs and the error पूर्णांकerrupt can
	 * be handled on a dअगरferent CPU than the BIOS code is run on,
	 * it is possible क्रम a second master पात to occur between the
	 * समय the PALcode पढ़ोs PERROR and the समय it ग_लिखोs PERROR
	 * to acknowledge the error. If this timing happens, a second
	 * error will be संकेतled after the first, and अगर no additional
	 * errors occur, will look like a Lost error with no additional 
	 * errors on the same transaction as the previous error.
	 */
	अगर (((लिखो_त्रुटि & TITAN__PCHIP_PERROR__NDS) || 
	     ((लिखो_त्रुटि & TITAN__PCHIP_PERROR__ERRMASK) == 
	      TITAN__PCHIP_PERROR__LOST)) &&
	    ((((cmd & 0xE) == 2) && (addr < 0x1000)) ||
	     (((cmd & 0xE) == 6) && (addr >= 0xA0000) && (addr < 0x100000)))) अणु
		status = MCHK_DISPOSITION_DISMISS;
	पूर्ण

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (!prपूर्णांक) 
		वापस status;

	prपूर्णांकk("%s  PChip %d %cPERROR: %016llx\n",
	       err_prपूर्णांक_prefix, which, 
	       port ? 'A' : 'G', लिखो_त्रुटि);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__IPTPW)
		prपूर्णांकk("%s    Invalid Peer-to-Peer Write\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__IPTPR)
		prपूर्णांकk("%s    Invalid Peer-to-Peer Read\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__NDS)
		prपूर्णांकk("%s    No DEVSEL as PCI Master [Master Abort]\n",
		       err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__DPE)
		prपूर्णांकk("%s    Data Parity Error\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__TA)
		prपूर्णांकk("%s    Target Abort\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__APE)
		prपूर्णांकk("%s    Address Parity Error\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__SGE)
		prपूर्णांकk("%s    Scatter-Gather Error, Invalid PTE\n", 
		       err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__DCRTO)
		prपूर्णांकk("%s    Delayed-Completion Retry Timeout\n", 
		       err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__PERR)
		prपूर्णांकk("%s    PERR Asserted\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__SERR)
		prपूर्णांकk("%s    SERR Asserted\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__LOST)
		prपूर्णांकk("%s    Lost Error\n", err_prपूर्णांक_prefix);
	prपूर्णांकk("%s      Command: 0x%x - %s\n"
		 "      Address: 0x%lx\n",
	       err_prपूर्णांक_prefix,
	       cmd, लिखो_त्रुटि_cmd[cmd],
	       addr);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__DAC)
		prपूर्णांकk("%s      Dual Address Cycle\n", err_prपूर्णांक_prefix);
	अगर (लिखो_त्रुटि & TITAN__PCHIP_PERROR__MWIN)
		prपूर्णांकk("%s      Hit in Monster Window\n", err_prपूर्णांक_prefix);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण

अटल पूर्णांक
titan_parse_p_agलिखो_त्रुटि(पूर्णांक which, u64 agलिखो_त्रुटि, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_REPORT;
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	पूर्णांक cmd, len;
	अचिन्हित दीर्घ addr;

	अटल स्थिर अक्षर * स्थिर agलिखो_त्रुटि_cmd[] = अणु
		"Read (low-priority)",	"Read (high-priority)",
		"Write (low-priority)",	"Write (high-priority)",
		"Reserved",		"Reserved",
		"Flush",		"Fence"
	पूर्ण;
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

#घोषणा TITAN__PCHIP_AGPERROR__LOST	(1UL << 0)
#घोषणा TITAN__PCHIP_AGPERROR__LPQFULL	(1UL << 1)
#घोषणा TITAN__PCHIP_AGPERROR__HPQFULL	(1UL << 2)
#घोषणा TITAN__PCHIP_AGPERROR__RESCMD	(1UL << 3)
#घोषणा TITAN__PCHIP_AGPERROR__IPTE	(1UL << 4)
#घोषणा TITAN__PCHIP_AGPERROR__PTP	(1UL << 5)
#घोषणा TITAN__PCHIP_AGPERROR__NOWINDOW	(1UL << 6)
#घोषणा TITAN__PCHIP_AGPERROR__ERRMASK	(TITAN__PCHIP_AGPERROR__LOST |    \
					 TITAN__PCHIP_AGPERROR__LPQFULL | \
					 TITAN__PCHIP_AGPERROR__HPQFULL | \
					 TITAN__PCHIP_AGPERROR__RESCMD |  \
					 TITAN__PCHIP_AGPERROR__IPTE |    \
					 TITAN__PCHIP_AGPERROR__PTP |     \
					 TITAN__PCHIP_AGPERROR__NOWINDOW)
#घोषणा TITAN__PCHIP_AGPERROR__DAC	(1UL << 48)
#घोषणा TITAN__PCHIP_AGPERROR__MWIN	(1UL << 49)
#घोषणा TITAN__PCHIP_AGPERROR__FENCE	(1UL << 59)
#घोषणा TITAN__PCHIP_AGPERROR__CMD__S	(50)
#घोषणा TITAN__PCHIP_AGPERROR__CMD__M	(0x07)
#घोषणा TITAN__PCHIP_AGPERROR__ADDR__S	(15)
#घोषणा TITAN__PCHIP_AGPERROR__ADDR__M  (0xffffffffUL)
#घोषणा TITAN__PCHIP_AGPERROR__LEN__S	(53)
#घोषणा TITAN__PCHIP_AGPERROR__LEN__M	(0x3f)

	अगर (!(agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__ERRMASK))
		वापस MCHK_DISPOSITION_UNKNOWN_ERROR;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (!prपूर्णांक)
		वापस status;

	cmd = EXTRACT(agलिखो_त्रुटि, TITAN__PCHIP_AGPERROR__CMD);
	addr = EXTRACT(agलिखो_त्रुटि, TITAN__PCHIP_AGPERROR__ADDR) << 3;
	len = EXTRACT(agलिखो_त्रुटि, TITAN__PCHIP_AGPERROR__LEN);

	prपूर्णांकk("%s  PChip %d AGPERROR: %016llx\n", err_prपूर्णांक_prefix,
	       which, agलिखो_त्रुटि);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__NOWINDOW)
		prपूर्णांकk("%s    No Window\n", err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__PTP)
		prपूर्णांकk("%s    Peer-to-Peer set\n", err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__IPTE)
		prपूर्णांकk("%s    Invalid PTE\n", err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__RESCMD)
		prपूर्णांकk("%s    Reserved Command\n", err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__HPQFULL)
		prपूर्णांकk("%s    HP Transaction Received while Queue Full\n", 
		       err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__LPQFULL)
		prपूर्णांकk("%s    LP Transaction Received while Queue Full\n", 
		       err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__LOST)
		prपूर्णांकk("%s    Lost Error\n", err_prपूर्णांक_prefix);
	prपूर्णांकk("%s      Command: 0x%x - %s, %d Quadwords%s\n"
		 "      Address: 0x%lx\n",
	       err_prपूर्णांक_prefix, cmd, agलिखो_त्रुटि_cmd[cmd], len,
	       (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__FENCE) ? ", FENCE" : "",
	       addr);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__DAC)
		prपूर्णांकk("%s      Dual Address Cycle\n", err_prपूर्णांक_prefix);
	अगर (agलिखो_त्रुटि & TITAN__PCHIP_AGPERROR__MWIN)
		prपूर्णांकk("%s      Hit in Monster Window\n", err_prपूर्णांक_prefix);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण	

अटल पूर्णांक
titan_parse_p_chip(पूर्णांक which, u64 serror, u64 gलिखो_त्रुटि, 
		   u64 aलिखो_त्रुटि, u64 agलिखो_त्रुटि, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;
	status |= titan_parse_p_serror(which, serror, prपूर्णांक);
	status |= titan_parse_p_लिखो_त्रुटि(which, 0, gलिखो_त्रुटि, prपूर्णांक);
	status |= titan_parse_p_लिखो_त्रुटि(which, 1, aलिखो_त्रुटि, prपूर्णांक);
	status |= titan_parse_p_agलिखो_त्रुटि(which, agलिखो_त्रुटि, prपूर्णांक);
	वापस status;
पूर्ण

पूर्णांक
titan_process_logout_frame(काष्ठा el_common *mchk_header, पूर्णांक prपूर्णांक)
अणु
	काष्ठा el_TITAN_sysdata_mcheck *पंचांगchk =
		(काष्ठा el_TITAN_sysdata_mcheck *)
		((अचिन्हित दीर्घ)mchk_header + mchk_header->sys_offset);
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	status |= titan_parse_c_misc(पंचांगchk->c_misc, prपूर्णांक);
	status |= titan_parse_p_chip(0, पंचांगchk->p0_serror, पंचांगchk->p0_gलिखो_त्रुटि,
				     पंचांगchk->p0_aलिखो_त्रुटि, पंचांगchk->p0_agलिखो_त्रुटि, 
				     prपूर्णांक);
	status |= titan_parse_p_chip(1, पंचांगchk->p1_serror, पंचांगchk->p1_gलिखो_त्रुटि,
				     पंचांगchk->p1_aलिखो_त्रुटि, पंचांगchk->p1_agलिखो_त्रुटि, 
				     prपूर्णांक);

	वापस status;
पूर्ण

व्योम
titan_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *mchk_header = (काष्ठा el_common *)la_ptr;
	काष्ठा el_TITAN_sysdata_mcheck *पंचांगchk =
		(काष्ठा el_TITAN_sysdata_mcheck *)
		((अचिन्हित दीर्घ)mchk_header + mchk_header->sys_offset);
	u64 irqmask;

	/*
	 * Mask of Titan पूर्णांकerrupt sources which are reported as machine checks
	 *
	 * 63 - CChip Error
	 * 62 - PChip 0 H_Error
	 * 61 - PChip 1 H_Error
	 * 60 - PChip 0 C_Error
	 * 59 - PChip 1 C_Error
	 */
#घोषणा TITAN_MCHECK_INTERRUPT_MASK	0xF800000000000000UL

	/*
	 * Sync the processor
	 */
	mb();
	draina();
	
	/*
	 * Only handle प्रणाली errors here 
	 */
	अगर ((vector != SCB_Q_SYSMCHK) && (vector != SCB_Q_SYSERR)) अणु
		ev6_machine_check(vector, la_ptr);
		वापस;
	पूर्ण

	/* 
	 * It's a प्रणाली error, handle it here
	 *
	 * The PALcode has alपढ़ोy cleared the error, so just parse it
	 */
	
	/* 
	 * Parse the logout frame without prपूर्णांकing first. If the only error(s)
	 * found are classअगरied as "dismissable", then just dismiss them and
	 * करोn't prपूर्णांक any message
	 */
	अगर (titan_process_logout_frame(mchk_header, 0) != 
	    MCHK_DISPOSITION_DISMISS) अणु
		अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;
		err_prपूर्णांक_prefix = KERN_CRIT;

		/*
		 * Either a nondismissable error was detected or no
		 * recognized error was detected  in the logout frame 
		 * -- report the error in either हाल
		 */
		prपूर्णांकk("%s"
		       "*System %s Error (Vector 0x%x) reported on CPU %d:\n", 
		       err_prपूर्णांक_prefix,
		       (vector == SCB_Q_SYSERR)?"Correctable":"Uncorrectable",
		       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
		
#अगर_घोषित CONFIG_VERBOSE_MCHECK
		titan_process_logout_frame(mchk_header, alpha_verbose_mcheck);
		अगर (alpha_verbose_mcheck)
			dik_show_regs(get_irq_regs(), शून्य);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

		err_prपूर्णांक_prefix = saved_err_prefix;

		/*
		 * Convert any pending पूर्णांकerrupts which report as प्रणाली
		 * machine checks to पूर्णांकerrupts
		 */
		irqmask = पंचांगchk->c_dirx & TITAN_MCHECK_INTERRUPT_MASK;
		titan_dispatch_irqs(irqmask);
	पूर्ण	


	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
पूर्ण

/*
 * Subpacket Annotations
 */
अटल अक्षर *el_titan_pchip0_extended_annotation[] = अणु
	"Subpacket Header", 	"P0_SCTL",	"P0_SERREN",
	"P0_APCTL",		"P0_APERREN",	"P0_AGPERREN",
	"P0_ASPRST",		"P0_AWSBA0",	"P0_AWSBA1",
	"P0_AWSBA2",		"P0_AWSBA3",	"P0_AWSM0",
	"P0_AWSM1",		"P0_AWSM2",	"P0_AWSM3",
	"P0_ATBA0",		"P0_ATBA1",	"P0_ATBA2",
	"P0_ATBA3",		"P0_GPCTL",	"P0_GPERREN",
	"P0_GSPRST",		"P0_GWSBA0",	"P0_GWSBA1",
	"P0_GWSBA2",		"P0_GWSBA3",	"P0_GWSM0",
	"P0_GWSM1",		"P0_GWSM2",	"P0_GWSM3",
	"P0_GTBA0",		"P0_GTBA1",	"P0_GTBA2",
	"P0_GTBA3",		शून्य 
पूर्ण;
अटल अक्षर *el_titan_pchip1_extended_annotation[] = अणु
	"Subpacket Header", 	"P1_SCTL",	"P1_SERREN",
	"P1_APCTL",		"P1_APERREN",	"P1_AGPERREN",
	"P1_ASPRST",		"P1_AWSBA0",	"P1_AWSBA1",
	"P1_AWSBA2",		"P1_AWSBA3",	"P1_AWSM0",
	"P1_AWSM1",		"P1_AWSM2",	"P1_AWSM3",
	"P1_ATBA0",		"P1_ATBA1",	"P1_ATBA2",
	"P1_ATBA3",		"P1_GPCTL",	"P1_GPERREN",
	"P1_GSPRST",		"P1_GWSBA0",	"P1_GWSBA1",
	"P1_GWSBA2",		"P1_GWSBA3",	"P1_GWSM0",
	"P1_GWSM1",		"P1_GWSM2",	"P1_GWSM3",
	"P1_GTBA0",		"P1_GTBA1",	"P1_GTBA2",
	"P1_GTBA3",		शून्य 
पूर्ण;
अटल अक्षर *el_titan_memory_extended_annotation[] = अणु
	"Subpacket Header", 	"AAR0",		"AAR1",
	"AAR2",			"AAR3",		"P0_SCTL",
	"P0_GPCTL",		"P0_APCTL",	"P1_SCTL",
	"P1_GPCTL",		"P1_SCTL",	शून्य 
पूर्ण;

अटल काष्ठा el_subpacket_annotation el_titan_annotations[] = अणु
	SUBPACKET_ANNOTATION(EL_CLASS__REGATTA_FAMILY,
			     EL_TYPE__REGATTA__TITAN_PCHIP0_EXTENDED,
			     1,
			     "Titan PChip 0 Extended Frame",
			     el_titan_pchip0_extended_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__REGATTA_FAMILY,
			     EL_TYPE__REGATTA__TITAN_PCHIP1_EXTENDED,
			     1,
			     "Titan PChip 1 Extended Frame",
			     el_titan_pchip1_extended_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__REGATTA_FAMILY,
			     EL_TYPE__REGATTA__TITAN_MEMORY_EXTENDED,
			     1,
			     "Titan Memory Extended Frame",
			     el_titan_memory_extended_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__REGATTA_FAMILY,
			     EL_TYPE__TERMINATION__TERMINATION,
			     1,
			     "Termination Subpacket",
			     शून्य)
पूर्ण;

अटल काष्ठा el_subpacket *
el_process_regatta_subpacket(काष्ठा el_subpacket *header)
अणु
	अगर (header->class != EL_CLASS__REGATTA_FAMILY) अणु
		prपूर्णांकk("%s  ** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_prपूर्णांक_prefix,
		       header->class, header->type);
		वापस शून्य;
	पूर्ण

	चयन(header->type) अणु
	हाल EL_TYPE__REGATTA__PROCESSOR_ERROR_FRAME:
	हाल EL_TYPE__REGATTA__SYSTEM_ERROR_FRAME:
	हाल EL_TYPE__REGATTA__ENVIRONMENTAL_FRAME:
	हाल EL_TYPE__REGATTA__PROCESSOR_DBL_ERROR_HALT:
	हाल EL_TYPE__REGATTA__SYSTEM_DBL_ERROR_HALT:
		prपूर्णांकk("%s  ** Occurred on CPU %d:\n", 
		       err_prपूर्णांक_prefix,
		       (पूर्णांक)header->by_type.regatta_frame.cpuid);
		निजीer_process_logout_frame((काष्ठा el_common *)
			header->by_type.regatta_frame.data_start, 1);
		अवरोध;
	शेष:
		prपूर्णांकk("%s  ** REGATTA TYPE %d SUBPACKET\n", 
		       err_prपूर्णांक_prefix, header->type);
		el_annotate_subpacket(header);
		अवरोध;
	पूर्ण


	वापस (काष्ठा el_subpacket *)((अचिन्हित दीर्घ)header + header->length);
पूर्ण 

अटल काष्ठा el_subpacket_handler titan_subpacket_handler = 
	SUBPACKET_HANDLER_INIT(EL_CLASS__REGATTA_FAMILY, 
			       el_process_regatta_subpacket);

व्योम __init
titan_रेजिस्टर_error_handlers(व्योम)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE (el_titan_annotations); i++)
		cdl_रेजिस्टर_subpacket_annotation(&el_titan_annotations[i]);

	cdl_रेजिस्टर_subpacket_handler(&titan_subpacket_handler);

	ev6_रेजिस्टर_error_handlers();
पूर्ण


/*
 * Privateer
 */

अटल पूर्णांक
निजीer_process_680_frame(काष्ठा el_common *mchk_header, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	काष्ठा el_PRIVATEER_envdata_mcheck *emchk =
		(काष्ठा el_PRIVATEER_envdata_mcheck *)
		((अचिन्हित दीर्घ)mchk_header + mchk_header->sys_offset);

	/* TODO - categorize errors, क्रम now, no error */

	अगर (!prपूर्णांक)
		वापस status;

	/* TODO - decode instead of just dumping... */
	prपूर्णांकk("%s  Summary Flags:         %016llx\n"
 	         "  CChip DIRx:            %016llx\n"
		 "  System Management IR:  %016llx\n"
		 "  CPU IR:                %016llx\n"
		 "  Power Supply IR:       %016llx\n"
		 "  LM78 Fault Status:     %016llx\n"
		 "  System Doors:          %016llx\n"
		 "  Temperature Warning:   %016llx\n"
		 "  Fan Control:           %016llx\n"
		 "  Fatal Power Down Code: %016llx\n",
	       err_prपूर्णांक_prefix,
	       emchk->summary,
	       emchk->c_dirx,
	       emchk->smir,
	       emchk->cpuir,
	       emchk->psir,
	       emchk->fault,
	       emchk->sys_करोors,
	       emchk->temp_warn,
	       emchk->fan_ctrl,
	       emchk->code);
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण

पूर्णांक
निजीer_process_logout_frame(काष्ठा el_common *mchk_header, पूर्णांक prपूर्णांक)
अणु
	काष्ठा el_common_EV6_mcheck *ev6mchk = 
		(काष्ठा el_common_EV6_mcheck *)mchk_header;
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	/*
	 * Machine check codes
	 */
#घोषणा PRIVATEER_MCHK__CORR_ECC		0x86	/* 630 */
#घोषणा PRIVATEER_MCHK__DC_TAG_PERR		0x9E	/* 630 */
#घोषणा PRIVATEER_MCHK__PAL_BUGCHECK		0x8E	/* 670 */
#घोषणा PRIVATEER_MCHK__OS_BUGCHECK		0x90	/* 670 */
#घोषणा PRIVATEER_MCHK__PROC_HRD_ERR		0x98	/* 670 */
#घोषणा PRIVATEER_MCHK__ISTREAM_CMOV_PRX	0xA0	/* 670 */
#घोषणा PRIVATEER_MCHK__ISTREAM_CMOV_FLT	0xA2	/* 670 */
#घोषणा PRIVATEER_MCHK__SYS_HRD_ERR		0x202	/* 660 */
#घोषणा PRIVATEER_MCHK__SYS_CORR_ERR		0x204	/* 620 */
#घोषणा PRIVATEER_MCHK__SYS_ENVIRON		0x206	/* 680 */

	चयन(ev6mchk->MCHK_Code) अणु
	/*
	 * Vector 630 - Processor, Correctable
	 */
	हाल PRIVATEER_MCHK__CORR_ECC:
	हाल PRIVATEER_MCHK__DC_TAG_PERR:
		/*
		 * Fall through to vector 670 क्रम processing...
		 */
	/*
	 * Vector 670 - Processor, Uncorrectable
	 */
	हाल PRIVATEER_MCHK__PAL_BUGCHECK:
	हाल PRIVATEER_MCHK__OS_BUGCHECK:
	हाल PRIVATEER_MCHK__PROC_HRD_ERR:
	हाल PRIVATEER_MCHK__ISTREAM_CMOV_PRX:
	हाल PRIVATEER_MCHK__ISTREAM_CMOV_FLT:
		status |= ev6_process_logout_frame(mchk_header, prपूर्णांक);
		अवरोध;

	/*
	 * Vector 620 - System, Correctable
	 */
	हाल PRIVATEER_MCHK__SYS_CORR_ERR:
		/*
		 * Fall through to vector 660 क्रम processing...
		 */
	/*
	 * Vector 660 - System, Uncorrectable
	 */
	हाल PRIVATEER_MCHK__SYS_HRD_ERR:
		status |= titan_process_logout_frame(mchk_header, prपूर्णांक);
		अवरोध;

	/* 
	 * Vector 680 - System, Environmental
	 */
	हाल PRIVATEER_MCHK__SYS_ENVIRON:	/* System, Environmental */
		status |= निजीer_process_680_frame(mchk_header, prपूर्णांक);
		अवरोध;

	/* 
	 * Unknown
	 */
	शेष:
		status |= MCHK_DISPOSITION_REPORT;
		अगर (prपूर्णांक) अणु
			prपूर्णांकk("%s** Unknown Error, frame follows\n", 
			       err_prपूर्णांक_prefix);
			mchk_dump_logout_frame(mchk_header);
		पूर्ण

	पूर्ण

	वापस status;
पूर्ण

व्योम
निजीer_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *mchk_header = (काष्ठा el_common *)la_ptr;
	काष्ठा el_TITAN_sysdata_mcheck *पंचांगchk =
		(काष्ठा el_TITAN_sysdata_mcheck *)
		(la_ptr + mchk_header->sys_offset);
	u64 irqmask;
	अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;

#घोषणा PRIVATEER_680_INTERRUPT_MASK		(0xE00UL)
#घोषणा PRIVATEER_HOTPLUG_INTERRUPT_MASK	(0xE00UL)

	/*
	 * Sync the processor.
	 */
	mb();
	draina();

	/* 
	 * Only handle प्रणाली events here.
	 */
	अगर (vector != SCB_Q_SYSEVENT) 
		वापस titan_machine_check(vector, la_ptr);

	/*
	 * Report the event - System Events should be reported even अगर no
	 * error is indicated since the event could indicate the वापस
	 * to normal status.
	 */
	err_prपूर्णांक_prefix = KERN_CRIT;
	prपूर्णांकk("%s*System Event (Vector 0x%x) reported on CPU %d:\n", 
	       err_prपूर्णांक_prefix,
	       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
	निजीer_process_680_frame(mchk_header, 1);
	err_prपूर्णांक_prefix = saved_err_prefix;
	
	/* 
	 * Convert any pending पूर्णांकerrupts which report as 680 machine
	 * checks to पूर्णांकerrupts.
	 */
	irqmask = पंचांगchk->c_dirx & PRIVATEER_680_INTERRUPT_MASK;

	/*
	 * Dispatch the पूर्णांकerrupt(s).
	 */
	titan_dispatch_irqs(irqmask);

	/* 
	 * Release the logout frame.
	 */
	wrmces(0x7);
	mb();
पूर्ण
