<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Auxtrace support क्रम s390 CPU measurement sampling facility
 *
 *  Copyright IBM Corp. 2018
 *  Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 *	       Thomas Richter <पंचांगricht@linux.ibm.com>
 */
#अगर_अघोषित S390_CPUMSF_KERNEL_H
#घोषणा S390_CPUMSF_KERNEL_H

#घोषणा	S390_CPUMSF_PAGESZ	4096	/* Size of sample block units */
#घोषणा	S390_CPUMSF_DIAG_DEF_FIRST	0x8001	/* Diagnostic entry lowest id */

काष्ठा hws_basic_entry अणु
	अचिन्हित पूर्णांक def:16;	    /* 0-15  Data Entry Format		 */
	अचिन्हित पूर्णांक R:4;	    /* 16-19 reserved			 */
	अचिन्हित पूर्णांक U:4;	    /* 20-23 Number of unique inकाष्ठा.  */
	अचिन्हित पूर्णांक z:2;	    /* zeros				 */
	अचिन्हित पूर्णांक T:1;	    /* 26 PSW DAT mode			 */
	अचिन्हित पूर्णांक W:1;	    /* 27 PSW रुको state		 */
	अचिन्हित पूर्णांक P:1;	    /* 28 PSW Problem state		 */
	अचिन्हित पूर्णांक AS:2;	    /* 29-30 PSW address-space control	 */
	अचिन्हित पूर्णांक I:1;	    /* 31 entry valid or invalid	 */
	अचिन्हित पूर्णांक CL:2;	    /* 32-33 Configuration Level	 */
	अचिन्हित पूर्णांक:14;
	अचिन्हित पूर्णांक prim_asn:16;   /* primary ASN			 */
	अचिन्हित दीर्घ दीर्घ ia;	    /* Inकाष्ठाion Address		 */
	अचिन्हित दीर्घ दीर्घ gpp;     /* Guest Program Parameter		 */
	अचिन्हित दीर्घ दीर्घ hpp;     /* Host Program Parameter		 */
पूर्ण;

काष्ठा hws_diag_entry अणु
	अचिन्हित पूर्णांक def:16;	    /* 0-15  Data Entry Format		 */
	अचिन्हित पूर्णांक R:15;	    /* 16-19 and 20-30 reserved		 */
	अचिन्हित पूर्णांक I:1;	    /* 31 entry valid or invalid	 */
	u8	     data[];	    /* Machine-dependent sample data	 */
पूर्ण;

काष्ठा hws_combined_entry अणु
	काष्ठा hws_basic_entry	basic;	/* Basic-sampling data entry */
	काष्ठा hws_diag_entry	diag;	/* Diagnostic-sampling data entry */
पूर्ण;

काष्ठा hws_trailer_entry अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक f:1;	/* 0 - Block Full Indicator   */
			अचिन्हित पूर्णांक a:1;	/* 1 - Alert request control  */
			अचिन्हित पूर्णांक t:1;	/* 2 - Timestamp क्रमmat	      */
			अचिन्हित पूर्णांक:29;	/* 3 - 31: Reserved	      */
			अचिन्हित पूर्णांक bsdes:16;	/* 32-47: size of basic SDE   */
			अचिन्हित पूर्णांक dsdes:16;	/* 48-63: size of diagnostic SDE */
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ flags;	/* 0 - 64: All indicators     */
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ overflow;	 /* 64 - sample Overflow count	      */
	अचिन्हित अक्षर बारtamp[16];	 /* 16 - 31 बारtamp		      */
	अचिन्हित दीर्घ दीर्घ reserved1;	 /* 32 -Reserved		      */
	अचिन्हित दीर्घ दीर्घ reserved2;	 /*				      */
	जोड़ अणु				 /* 48 - reserved क्रम programming use */
		काष्ठा अणु
			अचिन्हित दीर्घ दीर्घ घड़ी_base:1; /* in progusage2 */
			अचिन्हित दीर्घ दीर्घ progusage1:63;
			अचिन्हित दीर्घ दीर्घ progusage2;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ progusage[2];
	पूर्ण;
पूर्ण;

#पूर्ण_अगर
