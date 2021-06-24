<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम s390 CPU measurement counter set diagnostic facility
 *
 * Copyright IBM Corp. 2019
   Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 *		Thomas Richter <पंचांगricht@linux.ibm.com>
 */
#अगर_अघोषित S390_CPUMCF_KERNEL_H
#घोषणा S390_CPUMCF_KERNEL_H

#घोषणा	S390_CPUMCF_DIAG_DEF	0xfeef	/* Counter diagnostic entry ID */
#घोषणा	PERF_EVENT_CPUM_CF_DIAG	0xBC000	/* Event: Counter sets */
#घोषणा PERF_EVENT_CPUM_SF_DIAG	0xBD000 /* Event: Combined-sampling */

काष्ठा cf_ctrset_entry अणु	/* CPU-M CF counter set entry (8 byte) */
	अचिन्हित पूर्णांक def:16;	/* 0-15  Data Entry Format */
	अचिन्हित पूर्णांक set:16;	/* 16-23 Counter set identअगरier */
	अचिन्हित पूर्णांक ctr:16;	/* 24-39 Number of stored counters */
	अचिन्हित पूर्णांक res1:16;	/* 40-63 Reserved */
पूर्ण;

काष्ठा cf_trailer_entry अणु	/* CPU-M CF trailer क्रम raw traces (64 byte) */
	/* 0 - 7 */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक घड़ी_base:1;	/* TOD घड़ी base */
			अचिन्हित पूर्णांक speed:1;		/* CPU speed */
			/* Measurement alerts */
			अचिन्हित पूर्णांक mtda:1;	/* Loss of MT ctr. data alert */
			अचिन्हित पूर्णांक caca:1;	/* Counter auth. change alert */
			अचिन्हित पूर्णांक lcda:1;	/* Loss of counter data alert */
		पूर्ण;
		अचिन्हित दीर्घ flags;		/* 0-63    All indicators */
	पूर्ण;
	/* 8 - 15 */
	अचिन्हित पूर्णांक cfvn:16;			/* 64-79   Ctr First Version */
	अचिन्हित पूर्णांक csvn:16;			/* 80-95   Ctr Second Version */
	अचिन्हित पूर्णांक cpu_speed:32;		/* 96-127  CPU speed */
	/* 16 - 23 */
	अचिन्हित दीर्घ बारtamp;		/* 128-191 Timestamp (TOD) */
	/* 24 - 55 */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ progusage1;
			अचिन्हित दीर्घ progusage2;
			अचिन्हित दीर्घ progusage3;
			अचिन्हित दीर्घ tod_base;
		पूर्ण;
		अचिन्हित दीर्घ progusage[4];
	पूर्ण;
	/* 56 - 63 */
	अचिन्हित पूर्णांक mach_type:16;		/* Machine type */
	अचिन्हित पूर्णांक res1:16;			/* Reserved */
	अचिन्हित पूर्णांक res2:32;			/* Reserved */
पूर्ण;

#घोषणा	CPUMF_CTR_SET_BASIC	0	/* Basic Counter Set */
#घोषणा	CPUMF_CTR_SET_USER	1	/* Problem-State Counter Set */
#घोषणा	CPUMF_CTR_SET_CRYPTO	2	/* Crypto-Activity Counter Set */
#घोषणा	CPUMF_CTR_SET_EXT	3	/* Extended Counter Set */
#घोषणा	CPUMF_CTR_SET_MT_DIAG	4	/* MT-diagnostic Counter Set */
#पूर्ण_अगर
