<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2003 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

#अगर_अघोषित LINUX_RAID_RAID6_H
#घोषणा LINUX_RAID_RAID6_H

#अगर_घोषित __KERNEL__

/* Set to 1 to use kernel-wide empty_zero_page */
#घोषणा RAID6_USE_EMPTY_ZERO_PAGE 0
#समावेश <linux/blkdev.h>

/* We need a pre-zeroed page... अगर we करोn't want to use the kernel-provided
   one define it here */
#अगर RAID6_USE_EMPTY_ZERO_PAGE
# define raid6_empty_zero_page empty_zero_page
#अन्यथा
बाह्य स्थिर अक्षर raid6_empty_zero_page[PAGE_SIZE];
#पूर्ण_अगर

#अन्यथा /* ! __KERNEL__ */
/* Used क्रम testing in user space */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>

/* Not standard, but glibc defines it */
#घोषणा BITS_PER_LONG __WORDSIZE

प्रकार uपूर्णांक8_t  u8;
प्रकार uपूर्णांक16_t u16;
प्रकार uपूर्णांक32_t u32;
प्रकार uपूर्णांक64_t u64;

#अगर_अघोषित PAGE_SIZE
# define PAGE_SIZE 4096
#पूर्ण_अगर
#अगर_अघोषित PAGE_SHIFT
# define PAGE_SHIFT 12
#पूर्ण_अगर
बाह्य स्थिर अक्षर raid6_empty_zero_page[PAGE_SIZE];

#घोषणा __init
#घोषणा __निकास
#अगर_अघोषित __attribute_स्थिर__
# define __attribute_स्थिर__ __attribute__((स्थिर))
#पूर्ण_अगर
#घोषणा noअंतरभूत __attribute__((noअंतरभूत))

#घोषणा preempt_enable()
#घोषणा preempt_disable()
#घोषणा cpu_has_feature(x) 1
#घोषणा enable_kernel_altivec()
#घोषणा disable_kernel_altivec()

#अघोषित	EXPORT_SYMBOL
#घोषणा EXPORT_SYMBOL(sym)
#अघोषित	EXPORT_SYMBOL_GPL
#घोषणा EXPORT_SYMBOL_GPL(sym)
#घोषणा MODULE_LICENSE(licence)
#घोषणा MODULE_DESCRIPTION(desc)
#घोषणा subsys_initcall(x)
#घोषणा module_निकास(x)

#घोषणा IS_ENABLED(x) (x)
#घोषणा CONFIG_RAID6_PQ_BENCHMARK 1
#पूर्ण_अगर /* __KERNEL__ */

/* Routine choices */
काष्ठा raid6_calls अणु
	व्योम (*gen_syndrome)(पूर्णांक, माप_प्रकार, व्योम **);
	व्योम (*xor_syndrome)(पूर्णांक, पूर्णांक, पूर्णांक, माप_प्रकार, व्योम **);
	पूर्णांक  (*valid)(व्योम);	/* Returns 1 अगर this routine set is usable */
	स्थिर अक्षर *name;	/* Name of this routine set */
	पूर्णांक prefer;		/* Has special perक्रमmance attribute */
पूर्ण;

/* Selected algorithm */
बाह्य काष्ठा raid6_calls raid6_call;

/* Various routine sets */
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx1;
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx2;
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx4;
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx8;
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx16;
बाह्य स्थिर काष्ठा raid6_calls raid6_पूर्णांकx32;
बाह्य स्थिर काष्ठा raid6_calls raid6_mmxx1;
बाह्य स्थिर काष्ठा raid6_calls raid6_mmxx2;
बाह्य स्थिर काष्ठा raid6_calls raid6_sse1x1;
बाह्य स्थिर काष्ठा raid6_calls raid6_sse1x2;
बाह्य स्थिर काष्ठा raid6_calls raid6_sse2x1;
बाह्य स्थिर काष्ठा raid6_calls raid6_sse2x2;
बाह्य स्थिर काष्ठा raid6_calls raid6_sse2x4;
बाह्य स्थिर काष्ठा raid6_calls raid6_altivec1;
बाह्य स्थिर काष्ठा raid6_calls raid6_altivec2;
बाह्य स्थिर काष्ठा raid6_calls raid6_altivec4;
बाह्य स्थिर काष्ठा raid6_calls raid6_altivec8;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx2x1;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx2x2;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx2x4;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx512x1;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx512x2;
बाह्य स्थिर काष्ठा raid6_calls raid6_avx512x4;
बाह्य स्थिर काष्ठा raid6_calls raid6_s390vx8;
बाह्य स्थिर काष्ठा raid6_calls raid6_vpermxor1;
बाह्य स्थिर काष्ठा raid6_calls raid6_vpermxor2;
बाह्य स्थिर काष्ठा raid6_calls raid6_vpermxor4;
बाह्य स्थिर काष्ठा raid6_calls raid6_vpermxor8;

काष्ठा raid6_recov_calls अणु
	व्योम (*data2)(पूर्णांक, माप_प्रकार, पूर्णांक, पूर्णांक, व्योम **);
	व्योम (*datap)(पूर्णांक, माप_प्रकार, पूर्णांक, व्योम **);
	पूर्णांक  (*valid)(व्योम);
	स्थिर अक्षर *name;
	पूर्णांक priority;
पूर्ण;

बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_पूर्णांकx1;
बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_ssse3;
बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_avx2;
बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_avx512;
बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_s390xc;
बाह्य स्थिर काष्ठा raid6_recov_calls raid6_recov_neon;

बाह्य स्थिर काष्ठा raid6_calls raid6_neonx1;
बाह्य स्थिर काष्ठा raid6_calls raid6_neonx2;
बाह्य स्थिर काष्ठा raid6_calls raid6_neonx4;
बाह्य स्थिर काष्ठा raid6_calls raid6_neonx8;

/* Algorithm list */
बाह्य स्थिर काष्ठा raid6_calls * स्थिर raid6_algos[];
बाह्य स्थिर काष्ठा raid6_recov_calls *स्थिर raid6_recov_algos[];
पूर्णांक raid6_select_algo(व्योम);

/* Return values from chk_syndrome */
#घोषणा RAID6_OK	0
#घोषणा RAID6_P_BAD	1
#घोषणा RAID6_Q_BAD	2
#घोषणा RAID6_PQ_BAD	3

/* Galois field tables */
बाह्य स्थिर u8 raid6_gfmul[256][256] __attribute__((aligned(256)));
बाह्य स्थिर u8 raid6_vgfmul[256][32] __attribute__((aligned(256)));
बाह्य स्थिर u8 raid6_gfexp[256]      __attribute__((aligned(256)));
बाह्य स्थिर u8 raid6_gflog[256]      __attribute__((aligned(256)));
बाह्य स्थिर u8 raid6_gfinv[256]      __attribute__((aligned(256)));
बाह्य स्थिर u8 raid6_gfexi[256]      __attribute__((aligned(256)));

/* Recovery routines */
बाह्य व्योम (*raid6_2data_recov)(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
		       व्योम **ptrs);
बाह्य व्योम (*raid6_datap_recov)(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
			व्योम **ptrs);
व्योम raid6_dual_recov(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
		      व्योम **ptrs);

/* Some definitions to allow code to be compiled क्रम testing in userspace */
#अगर_अघोषित __KERNEL__

# define jअगरfies	raid6_jअगरfies()
# define prपूर्णांकk 	म_लिखो
# define pr_err(क्रमmat, ...) ख_लिखो(मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
# define pr_info(क्रमmat, ...) ख_लिखो(मानक_निकास, क्रमmat, ## __VA_ARGS__)
# define GFP_KERNEL	0
# define __get_मुक्त_pages(x, y)	((अचिन्हित दीर्घ)mmap(शून्य, PAGE_SIZE << (y), \
						     PROT_READ|PROT_WRITE,   \
						     MAP_PRIVATE|MAP_ANONYMOUS,\
						     0, 0))
# define मुक्त_pages(x, y)	munmap((व्योम *)(x), PAGE_SIZE << (y))

अटल अंतरभूत व्योम cpu_relax(व्योम)
अणु
	/* Nothing */
पूर्ण

#अघोषित  HZ
#घोषणा HZ 1000
अटल अंतरभूत uपूर्णांक32_t raid6_jअगरfies(व्योम)
अणु
	काष्ठा समयval tv;
	समय_लोofday(&tv, शून्य);
	वापस tv.tv_sec*1000 + tv.tv_usec/1000;
पूर्ण

#पूर्ण_अगर /* ! __KERNEL__ */

#पूर्ण_अगर /* LINUX_RAID_RAID6_H */
