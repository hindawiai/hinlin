<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
अटल काष्ठा fsr_info fsr_info[] = अणु
	/*
	 * The following are the standard ARMv3 and ARMv4 पातs.  ARMv5
	 * defines these to be "precise" पातs.
	 */
	अणु करो_bad,		संक_अंश, 0,		"vector exception"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 BUS_ADRALN,	"alignment exception"		   पूर्ण,
	अणु करो_bad,		SIGKILL, 0,		"terminal exception"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 BUS_ADRALN,	"alignment exception"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on linefetch"	   पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"section translation fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on linefetch"	   पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_MAPERR,	"page translation fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on non-linefetch"  पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"section domain fault"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on non-linefetch"  पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"page domain fault"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on translation"	   पूर्ण,
	अणु करो_sect_fault,	संक_अंश, SEGV_ACCERR,	"section permission fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on translation"	   पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"page permission fault"		   पूर्ण,
	/*
	 * The following are "imprecise" पातs, which are संकेतled by bit
	 * 10 of the FSR, and may not be recoverable.  These are only
	 * supported अगर the CPU पात handler supports bit 10.
	 */
	अणु करो_bad,		SIGBUS,  0,		"unknown 16"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 17"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 18"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 19"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"lock abort"			   पूर्ण, /* xscale */
	अणु करो_bad,		SIGBUS,  0,		"unknown 21"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  BUS_OBJERR,	"imprecise external abort"	   पूर्ण, /* xscale */
	अणु करो_bad,		SIGBUS,  0,		"unknown 23"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"dcache parity error"		   पूर्ण, /* xscale */
	अणु करो_bad,		SIGBUS,  0,		"unknown 25"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 26"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 27"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 28"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 29"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 30"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 31"			   पूर्ण,
पूर्ण;

अटल काष्ठा fsr_info अगरsr_info[] = अणु
	अणु करो_bad,		SIGBUS,  0,		"unknown 0"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 1"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"debug event"			   पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"section access flag fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 4"			   पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"section translation fault"	   पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"page access flag fault"	   पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_MAPERR,	"page translation fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on non-linefetch"  पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"section domain fault"		   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 10"			   पूर्ण,
	अणु करो_bad,		संक_अंश, SEGV_ACCERR,	"page domain fault"		   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on translation"	   पूर्ण,
	अणु करो_sect_fault,	संक_अंश, SEGV_ACCERR,	"section permission fault"	   पूर्ण,
	अणु करो_bad,		SIGBUS,	 0,		"external abort on translation"	   पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"page permission fault"		   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 16"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 17"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 18"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 19"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 20"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 21"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 22"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 23"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 24"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 25"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 26"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 27"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 28"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 29"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 30"			   पूर्ण,
	अणु करो_bad,		SIGBUS,  0,		"unknown 31"			   पूर्ण,
पूर्ण;
