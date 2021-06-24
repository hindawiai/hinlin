<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains inकाष्ठाions क्रम testing by the test titled:
 *
 *         "Test x86 instruction decoder - new instructions"
 *
 * Note that the 'Expecting' comment lines are consumed by the
 * gen-insn-x86-dat.awk script and have the क्रमmat:
 *
 *         Expecting: <op> <branch> <rel>
 *
 * If this file is changed, remember to run the gen-insn-x86-dat.sh
 * script and commit the result.
 *
 * Refer to insn-x86.c क्रम more details.
 */

पूर्णांक मुख्य(व्योम)
अणु
	/* Following line is a marker क्रम the awk script - करो not change */
	यंत्र अस्थिर("rdtsc"); /* Start here */

	/* Test fix क्रम vcvtph2ps in x86-opcode-map.txt */

	यंत्र अस्थिर("vcvtph2ps %xmm3,%ymm5");

#अगर_घोषित __x86_64__

	/* AVX-512: Inकाष्ठाions with the same op codes as Mask Inकाष्ठाions  */

	यंत्र अस्थिर("cmovno %rax,%rbx");
	यंत्र अस्थिर("cmovno 0x12345678(%rax),%rcx");
	यंत्र अस्थिर("cmovno 0x12345678(%rax),%cx");

	यंत्र अस्थिर("cmove  %rax,%rbx");
	यंत्र अस्थिर("cmove 0x12345678(%rax),%rcx");
	यंत्र अस्थिर("cmove 0x12345678(%rax),%cx");

	यंत्र अस्थिर("seto    0x12345678(%rax)");
	यंत्र अस्थिर("setno   0x12345678(%rax)");
	यंत्र अस्थिर("setb    0x12345678(%rax)");
	यंत्र अस्थिर("setc    0x12345678(%rax)");
	यंत्र अस्थिर("setnae  0x12345678(%rax)");
	यंत्र अस्थिर("setae   0x12345678(%rax)");
	यंत्र अस्थिर("setnb   0x12345678(%rax)");
	यंत्र अस्थिर("setnc   0x12345678(%rax)");
	यंत्र अस्थिर("sets    0x12345678(%rax)");
	यंत्र अस्थिर("setns   0x12345678(%rax)");

	/* AVX-512: Mask Inकाष्ठाions */

	यंत्र अस्थिर("kandw  %k7,%k6,%k5");
	यंत्र अस्थिर("kandq  %k7,%k6,%k5");
	यंत्र अस्थिर("kandb  %k7,%k6,%k5");
	यंत्र अस्थिर("kandd  %k7,%k6,%k5");

	यंत्र अस्थिर("kandnw  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnq  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnb  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnd  %k7,%k6,%k5");

	यंत्र अस्थिर("knotw  %k7,%k6");
	यंत्र अस्थिर("knotq  %k7,%k6");
	यंत्र अस्थिर("knotb  %k7,%k6");
	यंत्र अस्थिर("knotd  %k7,%k6");

	यंत्र अस्थिर("korw  %k7,%k6,%k5");
	यंत्र अस्थिर("korq  %k7,%k6,%k5");
	यंत्र अस्थिर("korb  %k7,%k6,%k5");
	यंत्र अस्थिर("kord  %k7,%k6,%k5");

	यंत्र अस्थिर("kxnorw  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnorq  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnorb  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnord  %k7,%k6,%k5");

	यंत्र अस्थिर("kxorw  %k7,%k6,%k5");
	यंत्र अस्थिर("kxorq  %k7,%k6,%k5");
	यंत्र अस्थिर("kxorb  %k7,%k6,%k5");
	यंत्र अस्थिर("kxord  %k7,%k6,%k5");

	यंत्र अस्थिर("kaddw  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddq  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddb  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddd  %k7,%k6,%k5");

	यंत्र अस्थिर("kunpckbw %k7,%k6,%k5");
	यंत्र अस्थिर("kunpckwd %k7,%k6,%k5");
	यंत्र अस्थिर("kunpckdq %k7,%k6,%k5");

	यंत्र अस्थिर("kmovw  %k6,%k5");
	यंत्र अस्थिर("kmovw  (%rcx),%k5");
	यंत्र अस्थिर("kmovw  0x123(%rax,%r14,8),%k5");
	यंत्र अस्थिर("kmovw  %k5,(%rcx)");
	यंत्र अस्थिर("kmovw  %k5,0x123(%rax,%r14,8)");
	यंत्र अस्थिर("kmovw  %eax,%k5");
	यंत्र अस्थिर("kmovw  %ebp,%k5");
	यंत्र अस्थिर("kmovw  %r13d,%k5");
	यंत्र अस्थिर("kmovw  %k5,%eax");
	यंत्र अस्थिर("kmovw  %k5,%ebp");
	यंत्र अस्थिर("kmovw  %k5,%r13d");

	यंत्र अस्थिर("kmovq  %k6,%k5");
	यंत्र अस्थिर("kmovq  (%rcx),%k5");
	यंत्र अस्थिर("kmovq  0x123(%rax,%r14,8),%k5");
	यंत्र अस्थिर("kmovq  %k5,(%rcx)");
	यंत्र अस्थिर("kmovq  %k5,0x123(%rax,%r14,8)");
	यंत्र अस्थिर("kmovq  %rax,%k5");
	यंत्र अस्थिर("kmovq  %rbp,%k5");
	यंत्र अस्थिर("kmovq  %r13,%k5");
	यंत्र अस्थिर("kmovq  %k5,%rax");
	यंत्र अस्थिर("kmovq  %k5,%rbp");
	यंत्र अस्थिर("kmovq  %k5,%r13");

	यंत्र अस्थिर("kmovb  %k6,%k5");
	यंत्र अस्थिर("kmovb  (%rcx),%k5");
	यंत्र अस्थिर("kmovb  0x123(%rax,%r14,8),%k5");
	यंत्र अस्थिर("kmovb  %k5,(%rcx)");
	यंत्र अस्थिर("kmovb  %k5,0x123(%rax,%r14,8)");
	यंत्र अस्थिर("kmovb  %eax,%k5");
	यंत्र अस्थिर("kmovb  %ebp,%k5");
	यंत्र अस्थिर("kmovb  %r13d,%k5");
	यंत्र अस्थिर("kmovb  %k5,%eax");
	यंत्र अस्थिर("kmovb  %k5,%ebp");
	यंत्र अस्थिर("kmovb  %k5,%r13d");

	यंत्र अस्थिर("kmovd  %k6,%k5");
	यंत्र अस्थिर("kmovd  (%rcx),%k5");
	यंत्र अस्थिर("kmovd  0x123(%rax,%r14,8),%k5");
	यंत्र अस्थिर("kmovd  %k5,(%rcx)");
	यंत्र अस्थिर("kmovd  %k5,0x123(%rax,%r14,8)");
	यंत्र अस्थिर("kmovd  %eax,%k5");
	यंत्र अस्थिर("kmovd  %ebp,%k5");
	यंत्र अस्थिर("kmovd  %r13d,%k5");
	यंत्र अस्थिर("kmovd  %k5,%eax");
	यंत्र अस्थिर("kmovd  %k5,%ebp");
	यंत्र अस्थिर("kmovd %k5,%r13d");

	यंत्र अस्थिर("kortestw %k6,%k5");
	यंत्र अस्थिर("kortestq %k6,%k5");
	यंत्र अस्थिर("kortestb %k6,%k5");
	यंत्र अस्थिर("kortestd %k6,%k5");

	यंत्र अस्थिर("ktestw %k6,%k5");
	यंत्र अस्थिर("ktestq %k6,%k5");
	यंत्र अस्थिर("ktestb %k6,%k5");
	यंत्र अस्थिर("ktestd %k6,%k5");

	यंत्र अस्थिर("kshiftrw $0x12,%k6,%k5");
	यंत्र अस्थिर("kshiftrq $0x5b,%k6,%k5");
	यंत्र अस्थिर("kshiftlw $0x12,%k6,%k5");
	यंत्र अस्थिर("kshiftlq $0x5b,%k6,%k5");

	/* AVX-512: Op code 0f 5b */
	यंत्र अस्थिर("vcvtdq2ps %xmm5,%xmm6");
	यंत्र अस्थिर("vcvtqq2ps %zmm29,%ymm6{%k7}");
	यंत्र अस्थिर("vcvtps2dq %xmm5,%xmm6");
	यंत्र अस्थिर("vcvttps2dq %xmm5,%xmm6");

	/* AVX-512: Op code 0f 6f */

	यंत्र अस्थिर("movq   %mm0,%mm4");
	यंत्र अस्थिर("vmovdqa %ymm4,%ymm6");
	यंत्र अस्थिर("vmovdqa32 %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqa64 %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqu %ymm4,%ymm6");
	यंत्र अस्थिर("vmovdqu32 %zmm29,%zmm30");
	यंत्र अस्थिर("vmovdqu64 %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqu8 %zmm29,%zmm30");
	यंत्र अस्थिर("vmovdqu16 %zmm25,%zmm26");

	/* AVX-512: Op code 0f 78 */

	यंत्र अस्थिर("vmread %rax,%rbx");
	यंत्र अस्थिर("vcvttps2udq %zmm25,%zmm26");
	यंत्र अस्थिर("vcvttpd2udq %zmm29,%ymm6{%k7}");
	यंत्र अस्थिर("vcvttsd2usi %xmm6,%rax");
	यंत्र अस्थिर("vcvttss2usi %xmm6,%rax");
	यंत्र अस्थिर("vcvttps2uqq %ymm5,%zmm26{%k7}");
	यंत्र अस्थिर("vcvttpd2uqq %zmm29,%zmm30");

	/* AVX-512: Op code 0f 79 */

	यंत्र अस्थिर("vmwrite %rax,%rbx");
	यंत्र अस्थिर("vcvtps2udq %zmm25,%zmm26");
	यंत्र अस्थिर("vcvtpd2udq %zmm29,%ymm6{%k7}");
	यंत्र अस्थिर("vcvtsd2usi %xmm6,%rax");
	यंत्र अस्थिर("vcvtss2usi %xmm6,%rax");
	यंत्र अस्थिर("vcvtps2uqq %ymm5,%zmm26{%k7}");
	यंत्र अस्थिर("vcvtpd2uqq %zmm29,%zmm30");

	/* AVX-512: Op code 0f 7a */

	यंत्र अस्थिर("vcvtudq2pd %ymm5,%zmm29{%k7}");
	यंत्र अस्थिर("vcvtuqq2pd %zmm25,%zmm26");
	यंत्र अस्थिर("vcvtudq2ps %zmm29,%zmm30");
	यंत्र अस्थिर("vcvtuqq2ps %zmm25,%ymm26{%k7}");
	यंत्र अस्थिर("vcvttps2qq %ymm25,%zmm26{%k7}");
	यंत्र अस्थिर("vcvttpd2qq %zmm29,%zmm30");

	/* AVX-512: Op code 0f 7b */

	यंत्र अस्थिर("vcvtusi2sd %eax,%xmm5,%xmm6");
	यंत्र अस्थिर("vcvtusi2ss %eax,%xmm5,%xmm6");
	यंत्र अस्थिर("vcvtps2qq %ymm5,%zmm26{%k7}");
	यंत्र अस्थिर("vcvtpd2qq %zmm29,%zmm30");

	/* AVX-512: Op code 0f 7f */

	यंत्र अस्थिर("movq.s  %mm0,%mm4");
	यंत्र अस्थिर("vmovdqa %ymm8,%ymm6");
	यंत्र अस्थिर("vmovdqa32.s %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqa64.s %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqu %ymm8,%ymm6");
	यंत्र अस्थिर("vmovdqu32.s %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqu64.s %zmm25,%zmm26");
	यंत्र अस्थिर("vmovdqu8.s %zmm30,(%rcx)");
	यंत्र अस्थिर("vmovdqu16.s %zmm25,%zmm26");

	/* AVX-512: Op code 0f db */

	यंत्र अस्थिर("pand  %mm1,%mm2");
	यंत्र अस्थिर("pand  %xmm1,%xmm2");
	यंत्र अस्थिर("vpand  %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpandd %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpandq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f df */

	यंत्र अस्थिर("pandn  %mm1,%mm2");
	यंत्र अस्थिर("pandn  %xmm1,%xmm2");
	यंत्र अस्थिर("vpandn %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpandnd %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpandnq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f e6 */

	यंत्र अस्थिर("vcvttpd2dq %xmm1,%xmm2");
	यंत्र अस्थिर("vcvtdq2pd %xmm5,%xmm6");
	यंत्र अस्थिर("vcvtdq2pd %ymm5,%zmm26{%k7}");
	यंत्र अस्थिर("vcvtqq2pd %zmm25,%zmm26");
	यंत्र अस्थिर("vcvtpd2dq %xmm1,%xmm2");

	/* AVX-512: Op code 0f eb */

	यंत्र अस्थिर("por   %mm4,%mm6");
	यंत्र अस्थिर("vpor   %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpord  %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vporq  %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f ef */

	यंत्र अस्थिर("pxor   %mm4,%mm6");
	यंत्र अस्थिर("vpxor  %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpxord %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpxorq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 10 */

	यंत्र अस्थिर("pblendvb %xmm1,%xmm0");
	यंत्र अस्थिर("vpsrlvw %zmm27,%zmm28,%zmm29");
	यंत्र अस्थिर("vpmovuswb %zmm28,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 11 */

	यंत्र अस्थिर("vpmovusdb %zmm28,%xmm6{%k7}");
	यंत्र अस्थिर("vpsravw %zmm27,%zmm28,%zmm29");

	/* AVX-512: Op code 0f 38 12 */

	यंत्र अस्थिर("vpmovusqb %zmm27,%xmm6{%k7}");
	यंत्र अस्थिर("vpsllvw %zmm27,%zmm28,%zmm29");

	/* AVX-512: Op code 0f 38 13 */

	यंत्र अस्थिर("vcvtph2ps %xmm3,%ymm5");
	यंत्र अस्थिर("vcvtph2ps %ymm5,%zmm27{%k7}");
	यंत्र अस्थिर("vpmovusdw %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 14 */

	यंत्र अस्थिर("blendvps %xmm1,%xmm0");
	यंत्र अस्थिर("vpmovusqw %zmm27,%xmm6{%k7}");
	यंत्र अस्थिर("vprorvd %zmm27,%zmm28,%zmm29");
	यंत्र अस्थिर("vprorvq %zmm27,%zmm28,%zmm29");

	/* AVX-512: Op code 0f 38 15 */

	यंत्र अस्थिर("blendvpd %xmm1,%xmm0");
	यंत्र अस्थिर("vpmovusqd %zmm27,%ymm6{%k7}");
	यंत्र अस्थिर("vprolvd %zmm27,%zmm28,%zmm29");
	यंत्र अस्थिर("vprolvq %zmm27,%zmm28,%zmm29");

	/* AVX-512: Op code 0f 38 16 */

	यंत्र अस्थिर("vpermps %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpermps %ymm24,%ymm26,%ymm22{%k7}");
	यंत्र अस्थिर("vpermpd %ymm24,%ymm26,%ymm22{%k7}");

	/* AVX-512: Op code 0f 38 19 */

	यंत्र अस्थिर("vbroadcastsd %xmm4,%ymm6");
	यंत्र अस्थिर("vbroadcastf32x2 %xmm27,%zmm26");

	/* AVX-512: Op code 0f 38 1a */

	यंत्र अस्थिर("vbroadcastf128 (%rcx),%ymm4");
	यंत्र अस्थिर("vbroadcastf32x4 (%rcx),%zmm26");
	यंत्र अस्थिर("vbroadcastf64x2 (%rcx),%zmm26");

	/* AVX-512: Op code 0f 38 1b */

	यंत्र अस्थिर("vbroadcastf32x8 (%rcx),%zmm27");
	यंत्र अस्थिर("vbroadcastf64x4 (%rcx),%zmm26");

	/* AVX-512: Op code 0f 38 1f */

	यंत्र अस्थिर("vpabsq %zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 20 */

	यंत्र अस्थिर("vpmovsxbw %xmm4,%xmm5");
	यंत्र अस्थिर("vpmovswb %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 21 */

	यंत्र अस्थिर("vpmovsxbd %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovsdb %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 22 */

	यंत्र अस्थिर("vpmovsxbq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsqb %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 23 */

	यंत्र अस्थिर("vpmovsxwd %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsdw %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 24 */

	यंत्र अस्थिर("vpmovsxwq %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovsqw %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 25 */

	यंत्र अस्थिर("vpmovsxdq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsqd %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 26 */

	यंत्र अस्थिर("vptestmb %zmm27,%zmm28,%k5");
	यंत्र अस्थिर("vptestmw %zmm27,%zmm28,%k5");
	यंत्र अस्थिर("vptestnmb %zmm26,%zmm27,%k5");
	यंत्र अस्थिर("vptestnmw %zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 38 27 */

	यंत्र अस्थिर("vptestmd %zmm27,%zmm28,%k5");
	यंत्र अस्थिर("vptestmq %zmm27,%zmm28,%k5");
	यंत्र अस्थिर("vptestnmd %zmm26,%zmm27,%k5");
	यंत्र अस्थिर("vptestnmq %zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 38 28 */

	यंत्र अस्थिर("vpmuldq %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovm2b %k5,%zmm28");
	यंत्र अस्थिर("vpmovm2w %k5,%zmm28");

	/* AVX-512: Op code 0f 38 29 */

	यंत्र अस्थिर("vpcmpeqq %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovb2m %zmm28,%k5");
	यंत्र अस्थिर("vpmovw2m %zmm28,%k5");

	/* AVX-512: Op code 0f 38 2a */

	यंत्र अस्थिर("vmovntdqa (%rcx),%ymm4");
	यंत्र अस्थिर("vpbroadcastmb2q %k6,%zmm30");

	/* AVX-512: Op code 0f 38 2c */

	यंत्र अस्थिर("vmaskmovps (%rcx),%ymm4,%ymm6");
	यंत्र अस्थिर("vscalefps %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vscalefpd %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 2d */

	यंत्र अस्थिर("vmaskmovpd (%rcx),%ymm4,%ymm6");
	यंत्र अस्थिर("vscalefss %xmm24,%xmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vscalefsd %xmm24,%xmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 38 30 */

	यंत्र अस्थिर("vpmovzxbw %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovwb %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 31 */

	यंत्र अस्थिर("vpmovzxbd %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovdb %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 32 */

	यंत्र अस्थिर("vpmovzxbq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovqb %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 33 */

	यंत्र अस्थिर("vpmovzxwd %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovdw %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 34 */

	यंत्र अस्थिर("vpmovzxwq %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovqw %zmm27,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 35 */

	यंत्र अस्थिर("vpmovzxdq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovqd %zmm27,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 38 */

	यंत्र अस्थिर("vpermd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpermd %ymm24,%ymm26,%ymm22{%k7}");
	यंत्र अस्थिर("vpermq %ymm24,%ymm26,%ymm22{%k7}");

	/* AVX-512: Op code 0f 38 38 */

	यंत्र अस्थिर("vpminsb %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovm2d %k5,%zmm28");
	यंत्र अस्थिर("vpmovm2q %k5,%zmm28");

	/* AVX-512: Op code 0f 38 39 */

	यंत्र अस्थिर("vpminsd %xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpminsd %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpminsq %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpmovd2m %zmm28,%k5");
	यंत्र अस्थिर("vpmovq2m %zmm28,%k5");

	/* AVX-512: Op code 0f 38 3a */

	यंत्र अस्थिर("vpminuw %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpbroadcastmw2d %k6,%zmm28");

	/* AVX-512: Op code 0f 38 3b */

	यंत्र अस्थिर("vpminud %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpminud %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpminuq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 3d */

	यंत्र अस्थिर("vpmaxsd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmaxsd %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpmaxsq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 3f */

	यंत्र अस्थिर("vpmaxud %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmaxud %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpmaxuq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 42 */

	यंत्र अस्थिर("vpmulld %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmulld %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpmullq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 42 */

	यंत्र अस्थिर("vgetexpps %zmm25,%zmm26");
	यंत्र अस्थिर("vgetexppd %zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 43 */

	यंत्र अस्थिर("vgetexpss %xmm24,%xmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vgetexpsd %xmm28,%xmm29,%xmm30{%k7}");

	/* AVX-512: Op code 0f 38 44 */

	यंत्र अस्थिर("vplzcntd %zmm27,%zmm28");
	यंत्र अस्थिर("vplzcntq %zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 46 */

	यंत्र अस्थिर("vpsravd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpsravd %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpsravq %zmm24,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 38 4c */

	यंत्र अस्थिर("vrcp14ps %zmm25,%zmm26");
	यंत्र अस्थिर("vrcp14pd %zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 4d */

	यंत्र अस्थिर("vrcp14ss %xmm24,%xmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vrcp14sd %xmm24,%xmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 38 4e */

	यंत्र अस्थिर("vrsqrt14ps %zmm25,%zmm26");
	यंत्र अस्थिर("vrsqrt14pd %zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 4f */

	यंत्र अस्थिर("vrsqrt14ss %xmm24,%xmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vrsqrt14sd %xmm24,%xmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 38 50 */

	यंत्र अस्थिर("vpdpbusd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpbusd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpbusd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpbusd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpdpbusd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 51 */

	यंत्र अस्थिर("vpdpbusds %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpbusds %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpbusds %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpbusds 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpdpbusds 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 52 */

	यंत्र अस्थिर("vdpbf16ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vdpbf16ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vdpbf16ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vdpbf16ps 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vdpbf16ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpdpwssd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpwssd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpwssd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpwssd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpdpwssd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vp4dpwssd (%rax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssd (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssd 0x12345678(%rax,%rcx,8),%zmm0,%zmm4");
	यंत्र अस्थिर("vp4dpwssd 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 53 */

	यंत्र अस्थिर("vpdpwssds %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpwssds %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpwssds %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpwssds 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpdpwssds 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vp4dpwssds (%rax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssds (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssds 0x12345678(%rax,%rcx,8),%zmm0,%zmm4");
	यंत्र अस्थिर("vp4dpwssds 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 54 */

	यंत्र अस्थिर("vpopcntb %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntb %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntb %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntb 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpopcntb 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpopcntw %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntw %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntw %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntw 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpopcntw 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 55 */

	यंत्र अस्थिर("vpopcntd %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntd %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntd %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntd 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpopcntd 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpopcntq %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntq %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntq %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntq 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpopcntq 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 59 */

	यंत्र अस्थिर("vpbroadcastq %xmm4,%xmm6");
	यंत्र अस्थिर("vbroadcasti32x2 %xmm27,%zmm26");

	/* AVX-512: Op code 0f 38 5a */

	यंत्र अस्थिर("vbroadcasti128 (%rcx),%ymm4");
	यंत्र अस्थिर("vbroadcasti32x4 (%rcx),%zmm26");
	यंत्र अस्थिर("vbroadcasti64x2 (%rcx),%zmm26");

	/* AVX-512: Op code 0f 38 5b */

	यंत्र अस्थिर("vbroadcasti32x8 (%rcx),%zmm28");
	यंत्र अस्थिर("vbroadcasti64x4 (%rcx),%zmm26");

	/* AVX-512: Op code 0f 38 62 */

	यंत्र अस्थिर("vpexpandb %xmm1, %xmm2");
	यंत्र अस्थिर("vpexpandb %ymm1, %ymm2");
	यंत्र अस्थिर("vpexpandb %zmm1, %zmm2");
	यंत्र अस्थिर("vpexpandb 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpexpandb 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpexpandw %xmm1, %xmm2");
	यंत्र अस्थिर("vpexpandw %ymm1, %ymm2");
	यंत्र अस्थिर("vpexpandw %zmm1, %zmm2");
	यंत्र अस्थिर("vpexpandw 0x12345678(%rax,%rcx,8),%zmm2");
	यंत्र अस्थिर("vpexpandw 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 63 */

	यंत्र अस्थिर("vpcompressb %xmm1, %xmm2");
	यंत्र अस्थिर("vpcompressb %ymm1, %ymm2");
	यंत्र अस्थिर("vpcompressb %zmm1, %zmm2");
	यंत्र अस्थिर("vpcompressb %zmm2,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("vpcompressb %zmm2,0x12345678(%eax,%ecx,8)");

	यंत्र अस्थिर("vpcompressw %xmm1, %xmm2");
	यंत्र अस्थिर("vpcompressw %ymm1, %ymm2");
	यंत्र अस्थिर("vpcompressw %zmm1, %zmm2");
	यंत्र अस्थिर("vpcompressw %zmm2,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("vpcompressw %zmm2,0x12345678(%eax,%ecx,8)");

	/* AVX-512: Op code 0f 38 64 */

	यंत्र अस्थिर("vpblendmd %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpblendmq %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 65 */

	यंत्र अस्थिर("vblendmps %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vblendmpd %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 66 */

	यंत्र अस्थिर("vpblendmb %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpblendmw %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 68 */

	यंत्र अस्थिर("vp2intersectd %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vp2intersectd %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vp2intersectd %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vp2intersectd 0x12345678(%rax,%rcx,8),%zmm2,%k3");
	यंत्र अस्थिर("vp2intersectd 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	यंत्र अस्थिर("vp2intersectq %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vp2intersectq %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vp2intersectq %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vp2intersectq 0x12345678(%rax,%rcx,8),%zmm2,%k3");
	यंत्र अस्थिर("vp2intersectq 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	/* AVX-512: Op code 0f 38 70 */

	यंत्र अस्थिर("vpshldvw %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvw %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvw %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvw 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldvw 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 71 */

	यंत्र अस्थिर("vpshldvd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldvd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpshldvq %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvq %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvq %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvq 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldvq 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 72 */

	यंत्र अस्थिर("vcvtne2ps2bf16 %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vcvtneps2bf16 %xmm1, %xmm2");
	यंत्र अस्थिर("vcvtneps2bf16 %ymm1, %xmm2");
	यंत्र अस्थिर("vcvtneps2bf16 %zmm1, %ymm2");
	यंत्र अस्थिर("vcvtneps2bf16 0x12345678(%rax,%rcx,8),%ymm2");
	यंत्र अस्थिर("vcvtneps2bf16 0x12345678(%eax,%ecx,8),%ymm2");

	यंत्र अस्थिर("vpshrdvw %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvw %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvw %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvw 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdvw 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 73 */

	यंत्र अस्थिर("vpshrdvd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdvd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpshrdvq %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvq %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvq %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvq 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdvq 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 75 */

	यंत्र अस्थिर("vpermi2b %zmm24,%zmm25,%zmm26");
	यंत्र अस्थिर("vpermi2w %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 76 */

	यंत्र अस्थिर("vpermi2d %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermi2q %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 77 */

	यंत्र अस्थिर("vpermi2ps %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermi2pd %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 7a */

	यंत्र अस्थिर("vpbroadcastb %eax,%xmm30");

	/* AVX-512: Op code 0f 38 7b */

	यंत्र अस्थिर("vpbroadcastw %eax,%xmm30");

	/* AVX-512: Op code 0f 38 7c */

	यंत्र अस्थिर("vpbroadcastd %eax,%xmm30");
	यंत्र अस्थिर("vpbroadcastq %rax,%zmm30");

	/* AVX-512: Op code 0f 38 7d */

	यंत्र अस्थिर("vpermt2b %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermt2w %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 7e */

	यंत्र अस्थिर("vpermt2d %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermt2q %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 7f */

	यंत्र अस्थिर("vpermt2ps %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermt2pd %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 83 */

	यंत्र अस्थिर("vpmultishiftqb %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 88 */

	यंत्र अस्थिर("vexpandps (%rcx),%zmm26");
	यंत्र अस्थिर("vexpandpd (%rcx),%zmm28");

	/* AVX-512: Op code 0f 38 89 */

	यंत्र अस्थिर("vpexpandd (%rcx),%zmm28");
	यंत्र अस्थिर("vpexpandq (%rcx),%zmm26");

	/* AVX-512: Op code 0f 38 8a */

	यंत्र अस्थिर("vcompressps %zmm28,(%rcx)");
	यंत्र अस्थिर("vcompresspd %zmm28,(%rcx)");

	/* AVX-512: Op code 0f 38 8b */

	यंत्र अस्थिर("vpcompressd %zmm28,(%rcx)");
	यंत्र अस्थिर("vpcompressq %zmm26,(%rcx)");

	/* AVX-512: Op code 0f 38 8d */

	यंत्र अस्थिर("vpermb %zmm26,%zmm27,%zmm28");
	यंत्र अस्थिर("vpermw %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 8f */

	यंत्र अस्थिर("vpshufbitqmb %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb 0x12345678(%rax,%rcx,8),%zmm2,%k3");
	यंत्र अस्थिर("vpshufbitqmb 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	/* AVX-512: Op code 0f 38 90 */

	यंत्र अस्थिर("vpgatherdd %xmm2,0x02(%rbp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherdq %xmm2,0x04(%rbp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherdd 0x7b(%rbp,%zmm27,8),%zmm26{%k1}");
	यंत्र अस्थिर("vpgatherdq 0x7b(%rbp,%ymm27,8),%zmm26{%k1}");

	/* AVX-512: Op code 0f 38 91 */

	यंत्र अस्थिर("vpgatherqd %xmm2,0x02(%rbp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherqq %xmm2,0x02(%rbp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherqd 0x7b(%rbp,%zmm27,8),%ymm26{%k1}");
	यंत्र अस्थिर("vpgatherqq 0x7b(%rbp,%zmm27,8),%zmm26{%k1}");

	/* AVX-512: Op code 0f 38 9a */

	यंत्र अस्थिर("vfmsub132ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub132ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub132ps 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vfmsub132ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vfmsub132pd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132pd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub132pd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub132pd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vfmsub132pd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("v4fmaddps (%rax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fmaddps (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fmaddps 0x12345678(%rax,%rcx,8),%zmm0,%zmm4");
	यंत्र अस्थिर("v4fmaddps 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 9b */

	यंत्र अस्थिर("vfmsub132ss %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132ss 0x12345678(%rax,%rcx,8),%xmm2,%xmm3");
	यंत्र अस्थिर("vfmsub132ss 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("vfmsub132sd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132sd 0x12345678(%rax,%rcx,8),%xmm2,%xmm3");
	यंत्र अस्थिर("vfmsub132sd 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("v4fmaddss (%rax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fmaddss (%eax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fmaddss 0x12345678(%rax,%rcx,8),%xmm0,%xmm4");
	यंत्र अस्थिर("v4fmaddss 0x12345678(%eax,%ecx,8),%xmm0,%xmm4");

	/* AVX-512: Op code 0f 38 a0 */

	यंत्र अस्थिर("vpscatterdd %zmm28,0x7b(%rbp,%zmm29,8){%k1}");
	यंत्र अस्थिर("vpscatterdq %zmm26,0x7b(%rbp,%ymm27,8){%k1}");

	/* AVX-512: Op code 0f 38 a1 */

	यंत्र अस्थिर("vpscatterqd %ymm6,0x7b(%rbp,%zmm29,8){%k1}");
	यंत्र अस्थिर("vpscatterqq %ymm6,0x7b(%rbp,%ymm27,8){%k1}");

	/* AVX-512: Op code 0f 38 a2 */

	यंत्र अस्थिर("vscatterdps %zmm28,0x7b(%rbp,%zmm29,8){%k1}");
	यंत्र अस्थिर("vscatterdpd %zmm28,0x7b(%rbp,%ymm27,8){%k1}");

	/* AVX-512: Op code 0f 38 a3 */

	यंत्र अस्थिर("vscatterqps %ymm6,0x7b(%rbp,%zmm29,8){%k1}");
	यंत्र अस्थिर("vscatterqpd %zmm28,0x7b(%rbp,%zmm29,8){%k1}");

	/* AVX-512: Op code 0f 38 aa */

	यंत्र अस्थिर("vfmsub213ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub213ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub213ps 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vfmsub213ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vfmsub213pd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213pd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub213pd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub213pd 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vfmsub213pd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("v4fnmaddps (%rax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fnmaddps (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fnmaddps 0x12345678(%rax,%rcx,8),%zmm0,%zmm4");
	यंत्र अस्थिर("v4fnmaddps 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 ab */

	यंत्र अस्थिर("vfmsub213ss %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213ss 0x12345678(%rax,%rcx,8),%xmm2,%xmm3");
	यंत्र अस्थिर("vfmsub213ss 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("vfmsub213sd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213sd 0x12345678(%rax,%rcx,8),%xmm2,%xmm3");
	यंत्र अस्थिर("vfmsub213sd 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("v4fnmaddss (%rax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fnmaddss (%eax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fnmaddss 0x12345678(%rax,%rcx,8),%xmm0,%xmm4");
	यंत्र अस्थिर("v4fnmaddss 0x12345678(%eax,%ecx,8),%xmm0,%xmm4");

	/* AVX-512: Op code 0f 38 b4 */

	यंत्र अस्थिर("vpmadd52luq %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 b5 */

	यंत्र अस्थिर("vpmadd52huq %zmm26,%zmm27,%zmm28");

	/* AVX-512: Op code 0f 38 c4 */

	यंत्र अस्थिर("vpconflictd %zmm26,%zmm27");
	यंत्र अस्थिर("vpconflictq %zmm26,%zmm27");

	/* AVX-512: Op code 0f 38 c8 */

	यंत्र अस्थिर("vexp2ps %zmm29,%zmm30");
	यंत्र अस्थिर("vexp2pd %zmm26,%zmm27");

	/* AVX-512: Op code 0f 38 ca */

	यंत्र अस्थिर("vrcp28ps %zmm29,%zmm30");
	यंत्र अस्थिर("vrcp28pd %zmm26,%zmm27");

	/* AVX-512: Op code 0f 38 cb */

	यंत्र अस्थिर("vrcp28ss %xmm28,%xmm29,%xmm30{%k7}");
	यंत्र अस्थिर("vrcp28sd %xmm25,%xmm26,%xmm27{%k7}");

	/* AVX-512: Op code 0f 38 cc */

	यंत्र अस्थिर("vrsqrt28ps %zmm29,%zmm30");
	यंत्र अस्थिर("vrsqrt28pd %zmm26,%zmm27");

	/* AVX-512: Op code 0f 38 cd */

	यंत्र अस्थिर("vrsqrt28ss %xmm28,%xmm29,%xmm30{%k7}");
	यंत्र अस्थिर("vrsqrt28sd %xmm25,%xmm26,%xmm27{%k7}");

	/* AVX-512: Op code 0f 38 cf */

	यंत्र अस्थिर("gf2p8mulb %xmm1, %xmm3");
	यंत्र अस्थिर("gf2p8mulb 0x12345678(%rax,%rcx,8),%xmm3");
	यंत्र अस्थिर("gf2p8mulb 0x12345678(%eax,%ecx,8),%xmm3");

	यंत्र अस्थिर("vgf2p8mulb %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vgf2p8mulb %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vgf2p8mulb %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vgf2p8mulb 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vgf2p8mulb 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 dc */

	यंत्र अस्थिर("vaesenc %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesenc %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesenc %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesenc 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vaesenc 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 dd */

	यंत्र अस्थिर("vaesenclast %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesenclast %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesenclast %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesenclast 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vaesenclast 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 de */

	यंत्र अस्थिर("vaesdec %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesdec %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesdec %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesdec 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vaesdec 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 df */

	यंत्र अस्थिर("vaesdeclast %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesdeclast %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesdeclast %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesdeclast 0x12345678(%rax,%rcx,8),%zmm2,%zmm3");
	यंत्र अस्थिर("vaesdeclast 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 03 */

	यंत्र अस्थिर("valignd $0x12,%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("valignq $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 08 */

	यंत्र अस्थिर("vroundps $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vrndscaleps $0x12,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 3a 09 */

	यंत्र अस्थिर("vroundpd $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vrndscalepd $0x12,%zmm25,%zmm26");

	/* AVX-512: Op code 0f 3a 1a */

	यंत्र अस्थिर("vroundss $0x5,%xmm4,%xmm6,%xmm2");
	यंत्र अस्थिर("vrndscaless $0x12,%xmm24,%xmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 3a 0b */

	यंत्र अस्थिर("vroundsd $0x5,%xmm4,%xmm6,%xmm2");
	यंत्र अस्थिर("vrndscalesd $0x12,%xmm24,%xmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 3a 18 */

	यंत्र अस्थिर("vinsertf128 $0x5,%xmm4,%ymm4,%ymm6");
	यंत्र अस्थिर("vinsertf32x4 $0x12,%xmm24,%zmm25,%zmm26{%k7}");
	यंत्र अस्थिर("vinsertf64x2 $0x12,%xmm24,%zmm25,%zmm26{%k7}");

	/* AVX-512: Op code 0f 3a 19 */

	यंत्र अस्थिर("vextractf128 $0x5,%ymm4,%xmm4");
	यंत्र अस्थिर("vextractf32x4 $0x12,%zmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vextractf64x2 $0x12,%zmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 3a 1a */

	यंत्र अस्थिर("vinsertf32x8 $0x12,%ymm25,%zmm26,%zmm27{%k7}");
	यंत्र अस्थिर("vinsertf64x4 $0x12,%ymm28,%zmm29,%zmm30{%k7}");

	/* AVX-512: Op code 0f 3a 1b */

	यंत्र अस्थिर("vextractf32x8 $0x12,%zmm29,%ymm30{%k7}");
	यंत्र अस्थिर("vextractf64x4 $0x12,%zmm26,%ymm27{%k7}");

	/* AVX-512: Op code 0f 3a 1e */

	यंत्र अस्थिर("vpcmpud $0x12,%zmm29,%zmm30,%k5");
	यंत्र अस्थिर("vpcmpuq $0x12,%zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 3a 1f */

	यंत्र अस्थिर("vpcmpd $0x12,%zmm29,%zmm30,%k5");
	यंत्र अस्थिर("vpcmpq $0x12,%zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 3a 23 */

	यंत्र अस्थिर("vshuff32x4 $0x12,%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vshuff64x2 $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 25 */

	यंत्र अस्थिर("vpternlogd $0x12,%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vpternlogq $0x12,%zmm28,%zmm29,%zmm30");

	/* AVX-512: Op code 0f 3a 26 */

	यंत्र अस्थिर("vgetmantps $0x12,%zmm26,%zmm27");
	यंत्र अस्थिर("vgetmantpd $0x12,%zmm29,%zmm30");

	/* AVX-512: Op code 0f 3a 27 */

	यंत्र अस्थिर("vgetmantss $0x12,%xmm25,%xmm26,%xmm27{%k7}");
	यंत्र अस्थिर("vgetmantsd $0x12,%xmm28,%xmm29,%xmm30{%k7}");

	/* AVX-512: Op code 0f 3a 38 */

	यंत्र अस्थिर("vinserti128 $0x5,%xmm4,%ymm4,%ymm6");
	यंत्र अस्थिर("vinserti32x4 $0x12,%xmm24,%zmm25,%zmm26{%k7}");
	यंत्र अस्थिर("vinserti64x2 $0x12,%xmm24,%zmm25,%zmm26{%k7}");

	/* AVX-512: Op code 0f 3a 39 */

	यंत्र अस्थिर("vextracti128 $0x5,%ymm4,%xmm6");
	यंत्र अस्थिर("vextracti32x4 $0x12,%zmm25,%xmm26{%k7}");
	यंत्र अस्थिर("vextracti64x2 $0x12,%zmm25,%xmm26{%k7}");

	/* AVX-512: Op code 0f 3a 3a */

	यंत्र अस्थिर("vinserti32x8 $0x12,%ymm28,%zmm29,%zmm30{%k7}");
	यंत्र अस्थिर("vinserti64x4 $0x12,%ymm25,%zmm26,%zmm27{%k7}");

	/* AVX-512: Op code 0f 3a 3b */

	यंत्र अस्थिर("vextracti32x8 $0x12,%zmm29,%ymm30{%k7}");
	यंत्र अस्थिर("vextracti64x4 $0x12,%zmm26,%ymm27{%k7}");

	/* AVX-512: Op code 0f 3a 3e */

	यंत्र अस्थिर("vpcmpub $0x12,%zmm29,%zmm30,%k5");
	यंत्र अस्थिर("vpcmpuw $0x12,%zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 3a 3f */

	यंत्र अस्थिर("vpcmpb $0x12,%zmm29,%zmm30,%k5");
	यंत्र अस्थिर("vpcmpw $0x12,%zmm26,%zmm27,%k5");

	/* AVX-512: Op code 0f 3a 43 */

	यंत्र अस्थिर("vmpsadbw $0x5,%ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vdbpsadbw $0x12,%zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 3a 43 */

	यंत्र अस्थिर("vshufi32x4 $0x12,%zmm25,%zmm26,%zmm27");
	यंत्र अस्थिर("vshufi64x2 $0x12,%zmm28,%zmm29,%zmm30");

	/* AVX-512: Op code 0f 3a 44 */

	यंत्र अस्थिर("vpclmulqdq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpclmulqdq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpclmulqdq $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpclmulqdq $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 50 */

	यंत्र अस्थिर("vrangeps $0x12,%zmm25,%zmm26,%zmm27");
	यंत्र अस्थिर("vrangepd $0x12,%zmm28,%zmm29,%zmm30");

	/* AVX-512: Op code 0f 3a 51 */

	यंत्र अस्थिर("vrangess $0x12,%xmm25,%xmm26,%xmm27");
	यंत्र अस्थिर("vrangesd $0x12,%xmm28,%xmm29,%xmm30");

	/* AVX-512: Op code 0f 3a 54 */

	यंत्र अस्थिर("vfixupimmps $0x12,%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vfixupimmpd $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 55 */

	यंत्र अस्थिर("vfixupimmss $0x12,%xmm28,%xmm29,%xmm30{%k7}");
	यंत्र अस्थिर("vfixupimmsd $0x12,%xmm25,%xmm26,%xmm27{%k7}");

	/* AVX-512: Op code 0f 3a 56 */

	यंत्र अस्थिर("vreduceps $0x12,%zmm26,%zmm27");
	यंत्र अस्थिर("vreducepd $0x12,%zmm29,%zmm30");

	/* AVX-512: Op code 0f 3a 57 */

	यंत्र अस्थिर("vreducess $0x12,%xmm25,%xmm26,%xmm27");
	यंत्र अस्थिर("vreducesd $0x12,%xmm28,%xmm29,%xmm30");

	/* AVX-512: Op code 0f 3a 66 */

	यंत्र अस्थिर("vfpclassps $0x12,%zmm27,%k5");
	यंत्र अस्थिर("vfpclasspd $0x12,%zmm30,%k5");

	/* AVX-512: Op code 0f 3a 67 */

	यंत्र अस्थिर("vfpclassss $0x12,%xmm27,%k5");
	यंत्र अस्थिर("vfpclasssd $0x12,%xmm30,%k5");

	/* AVX-512: Op code 0f 3a 70 */

	यंत्र अस्थिर("vpshldw $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldw $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldw $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldw $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 71 */

	यंत्र अस्थिर("vpshldd $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldd $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldd $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldd $0x12,%zmm25,%zmm26,%zmm27");

	यंत्र अस्थिर("vpshldq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldq $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshldq $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 72 */

	यंत्र अस्थिर("vpshrdw $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdw $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdw $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdw $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a 73 */

	यंत्र अस्थिर("vpshrdd $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdd $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdd $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdd $0x12,%zmm25,%zmm26,%zmm27");

	यंत्र अस्थिर("vpshrdq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdq $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vpshrdq $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a ce */

	यंत्र अस्थिर("gf2p8affineqb $0x12,%xmm1,%xmm3");

	यंत्र अस्थिर("vgf2p8affineqb $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vgf2p8affineqb $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vgf2p8affineqb $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vgf2p8affineqb $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 3a cf */

	यंत्र अस्थिर("gf2p8affineinvqb $0x12,%xmm1,%xmm3");

	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%zmm1,%zmm2,%zmm3");
	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%zmm25,%zmm26,%zmm27");

	/* AVX-512: Op code 0f 72 (Grp13) */

	यंत्र अस्थिर("vprord $0x12,%zmm25,%zmm26");
	यंत्र अस्थिर("vprorq $0x12,%zmm25,%zmm26");
	यंत्र अस्थिर("vprold $0x12,%zmm29,%zmm30");
	यंत्र अस्थिर("vprolq $0x12,%zmm29,%zmm30");
	यंत्र अस्थिर("psrad  $0x2,%mm6");
	यंत्र अस्थिर("vpsrad $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vpsrad $0x5,%zmm26,%zmm22");
	यंत्र अस्थिर("vpsraq $0x5,%zmm26,%zmm22");

	/* AVX-512: Op code 0f 38 c6 (Grp18) */

	यंत्र अस्थिर("vgatherpf0dps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf0dpd 0x7b(%r14,%ymm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf1dps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf1dpd 0x7b(%r14,%ymm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf0dps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf0dpd 0x7b(%r14,%ymm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf1dps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf1dpd 0x7b(%r14,%ymm31,8){%k1}");

	/* AVX-512: Op code 0f 38 c7 (Grp19) */

	यंत्र अस्थिर("vgatherpf0qps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf0qpd 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf1qps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vgatherpf1qpd 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf0qps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf0qpd 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf1qps 0x7b(%r14,%zmm31,8){%k1}");
	यंत्र अस्थिर("vscatterpf1qpd 0x7b(%r14,%zmm31,8){%k1}");

	/* AVX-512: Examples */

	यंत्र अस्थिर("vaddpd %zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd %zmm28,%zmm29,%zmm30{%k7}");
	यंत्र अस्थिर("vaddpd %zmm28,%zmm29,%zmm30{%k7}{z}");
	यंत्र अस्थिर("vaddpd {rn-sae},%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd {ru-sae},%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd {rd-sae},%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd {rz-sae},%zmm28,%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd (%rcx),%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd 0x123(%rax,%r14,8),%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd (%rcx){1to8},%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd 0x1fc0(%rdx),%zmm29,%zmm30");
	यंत्र अस्थिर("vaddpd 0x3f8(%rdx){1to8},%zmm29,%zmm30");
	यंत्र अस्थिर("vcmpeq_uqps 0x1fc(%rdx){1to16},%zmm30,%k5");
	यंत्र अस्थिर("vcmpltsd 0x123(%rax,%r14,8),%xmm29,%k5{%k7}");
	यंत्र अस्थिर("vcmplesd {sae},%xmm28,%xmm29,%k5{%k7}");
	यंत्र अस्थिर("vgetmantss $0x5b,0x123(%rax,%r14,8),%xmm29,%xmm30{%k7}");

	/* bndmk m64, bnd */

	यंत्र अस्थिर("bndmk (%rax), %bnd0");
	यंत्र अस्थिर("bndmk (%r8), %bnd0");
	यंत्र अस्थिर("bndmk (0x12345678), %bnd0");
	यंत्र अस्थिर("bndmk (%rax), %bnd3");
	यंत्र अस्थिर("bndmk (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmk (%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%rax,%rcx,8), %bnd0");

	/* bndcl r/m64, bnd */

	यंत्र अस्थिर("bndcl (%rax), %bnd0");
	यंत्र अस्थिर("bndcl (%r8), %bnd0");
	यंत्र अस्थिर("bndcl (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcl (%rax), %bnd3");
	यंत्र अस्थिर("bndcl (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcl (%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcl %rax, %bnd0");

	/* bndcu r/m64, bnd */

	यंत्र अस्थिर("bndcu (%rax), %bnd0");
	यंत्र अस्थिर("bndcu (%r8), %bnd0");
	यंत्र अस्थिर("bndcu (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcu (%rax), %bnd3");
	यंत्र अस्थिर("bndcu (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcu (%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcu %rax, %bnd0");

	/* bndcn r/m64, bnd */

	यंत्र अस्थिर("bndcn (%rax), %bnd0");
	यंत्र अस्थिर("bndcn (%r8), %bnd0");
	यंत्र अस्थिर("bndcn (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcn (%rax), %bnd3");
	यंत्र अस्थिर("bndcn (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcn (%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndcn %rax, %bnd0");

	/* bndmov m128, bnd */

	यंत्र अस्थिर("bndmov (%rax), %bnd0");
	यंत्र अस्थिर("bndmov (%r8), %bnd0");
	यंत्र अस्थिर("bndmov (0x12345678), %bnd0");
	यंत्र अस्थिर("bndmov (%rax), %bnd3");
	यंत्र अस्थिर("bndmov (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmov (%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%rax,%rcx,8), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%rax,%rcx,8), %bnd0");

	/* bndmov bnd, m128 */

	यंत्र अस्थिर("bndmov %bnd0, (%rax)");
	यंत्र अस्थिर("bndmov %bnd0, (%r8)");
	यंत्र अस्थिर("bndmov %bnd0, (0x12345678)");
	यंत्र अस्थिर("bndmov %bnd3, (%rax)");
	यंत्र अस्थिर("bndmov %bnd0, (%rcx,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, (%rax,%rcx,1)");
	यंत्र अस्थिर("bndmov %bnd0, (%rax,%rcx,8)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rax)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rbp)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rcx,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rbp,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rax,%rcx,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%rax,%rcx,8)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rax)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rbp)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rcx,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rbp,%rax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rax,%rcx,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%rax,%rcx,8)");

	/* bndmov bnd2, bnd1 */

	यंत्र अस्थिर("bndmov %bnd0, %bnd1");
	यंत्र अस्थिर("bndmov %bnd1, %bnd0");

	/* bndldx mib, bnd */

	यंत्र अस्थिर("bndldx (%rax), %bnd0");
	यंत्र अस्थिर("bndldx (%r8), %bnd0");
	यंत्र अस्थिर("bndldx (0x12345678), %bnd0");
	यंत्र अस्थिर("bndldx (%rax), %bnd3");
	यंत्र अस्थिर("bndldx (%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx (%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%rax), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%rbp), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%rax,%rcx,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%rax), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%rbp), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%rcx,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%rbp,%rax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%rax,%rcx,1), %bnd0");

	/* bndstx bnd, mib */

	यंत्र अस्थिर("bndstx %bnd0, (%rax)");
	यंत्र अस्थिर("bndstx %bnd0, (%r8)");
	यंत्र अस्थिर("bndstx %bnd0, (0x12345678)");
	यंत्र अस्थिर("bndstx %bnd3, (%rax)");
	यंत्र अस्थिर("bndstx %bnd0, (%rcx,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, (%rax,%rcx,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%rax)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%rbp)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%rcx,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%rbp,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%rax,%rcx,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%rax)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%rbp)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%rcx,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%rbp,%rax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%rax,%rcx,1)");

	/* bnd prefix on call, ret, jmp and all jcc */

	यंत्र अस्थिर("bnd call label1");  /* Expecting: call unconditional 0 */
	यंत्र अस्थिर("bnd call *(%eax)"); /* Expecting: call indirect      0 */
	यंत्र अस्थिर("bnd ret");          /* Expecting: ret  indirect      0 */
	यंत्र अस्थिर("bnd jmp label1");   /* Expecting: jmp  unconditional 0 */
	यंत्र अस्थिर("bnd jmp label1");   /* Expecting: jmp  unconditional 0 */
	यंत्र अस्थिर("bnd jmp *(%ecx)");  /* Expecting: jmp  indirect      0 */
	यंत्र अस्थिर("bnd jne label1");   /* Expecting: jcc  conditional   0 */

	/* sha1rnds4 imm8, xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1rnds4 $0x0, %xmm1, %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, %xmm7, %xmm2");
	यंत्र अस्थिर("sha1rnds4 $0x91, %xmm8, %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, %xmm7, %xmm8");
	यंत्र अस्थिर("sha1rnds4 $0x91, %xmm15, %xmm8");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%rax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%r8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%rax), %xmm3");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha1nexte xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1nexte %xmm1, %xmm0");
	यंत्र अस्थिर("sha1nexte %xmm7, %xmm2");
	यंत्र अस्थिर("sha1nexte %xmm8, %xmm0");
	यंत्र अस्थिर("sha1nexte %xmm7, %xmm8");
	यंत्र अस्थिर("sha1nexte %xmm15, %xmm8");
	यंत्र अस्थिर("sha1nexte (%rax), %xmm0");
	यंत्र अस्थिर("sha1nexte (%r8), %xmm0");
	यंत्र अस्थिर("sha1nexte (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1nexte (%rax), %xmm3");
	यंत्र अस्थिर("sha1nexte (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha1msg1 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1msg1 %xmm1, %xmm0");
	यंत्र अस्थिर("sha1msg1 %xmm7, %xmm2");
	यंत्र अस्थिर("sha1msg1 %xmm8, %xmm0");
	यंत्र अस्थिर("sha1msg1 %xmm7, %xmm8");
	यंत्र अस्थिर("sha1msg1 %xmm15, %xmm8");
	यंत्र अस्थिर("sha1msg1 (%rax), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%r8), %xmm0");
	यंत्र अस्थिर("sha1msg1 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%rax), %xmm3");
	यंत्र अस्थिर("sha1msg1 (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha1msg2 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1msg2 %xmm1, %xmm0");
	यंत्र अस्थिर("sha1msg2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha1msg2 %xmm8, %xmm0");
	यंत्र अस्थिर("sha1msg2 %xmm7, %xmm8");
	यंत्र अस्थिर("sha1msg2 %xmm15, %xmm8");
	यंत्र अस्थिर("sha1msg2 (%rax), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%r8), %xmm0");
	यंत्र अस्थिर("sha1msg2 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%rax), %xmm3");
	यंत्र अस्थिर("sha1msg2 (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha256rnds2 <XMM0>, xmm2/m128, xmm1 */
	/* Note sha256rnds2 has an implicit opeअक्रम 'xmm0' */

	यंत्र अस्थिर("sha256rnds2 %xmm4, %xmm1");
	यंत्र अस्थिर("sha256rnds2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256rnds2 %xmm8, %xmm1");
	यंत्र अस्थिर("sha256rnds2 %xmm7, %xmm8");
	यंत्र अस्थिर("sha256rnds2 %xmm15, %xmm8");
	यंत्र अस्थिर("sha256rnds2 (%rax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%r8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (0x12345678), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%rax), %xmm3");
	यंत्र अस्थिर("sha256rnds2 (%rcx,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%rax,%rcx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%rax,%rcx,8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rbp), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rcx,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rbp,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rax,%rcx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%rax,%rcx,8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rbp), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rcx,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rbp,%rax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rax,%rcx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rax,%rcx,8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha256msg1 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha256msg1 %xmm1, %xmm0");
	यंत्र अस्थिर("sha256msg1 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256msg1 %xmm8, %xmm0");
	यंत्र अस्थिर("sha256msg1 %xmm7, %xmm8");
	यंत्र अस्थिर("sha256msg1 %xmm15, %xmm8");
	यंत्र अस्थिर("sha256msg1 (%rax), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%r8), %xmm0");
	यंत्र अस्थिर("sha256msg1 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%rax), %xmm3");
	यंत्र अस्थिर("sha256msg1 (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%rax,%rcx,8), %xmm15");

	/* sha256msg2 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha256msg2 %xmm1, %xmm0");
	यंत्र अस्थिर("sha256msg2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256msg2 %xmm8, %xmm0");
	यंत्र अस्थिर("sha256msg2 %xmm7, %xmm8");
	यंत्र अस्थिर("sha256msg2 %xmm15, %xmm8");
	यंत्र अस्थिर("sha256msg2 (%rax), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%r8), %xmm0");
	यंत्र अस्थिर("sha256msg2 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%rax), %xmm3");
	यंत्र अस्थिर("sha256msg2 (%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rax), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rbp), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rax), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rbp), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rcx,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rbp,%rax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rax,%rcx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rax,%rcx,8), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%rax,%rcx,8), %xmm15");

	/* clflushopt m8 */

	यंत्र अस्थिर("clflushopt (%rax)");
	यंत्र अस्थिर("clflushopt (%r8)");
	यंत्र अस्थिर("clflushopt (0x12345678)");
	यंत्र अस्थिर("clflushopt 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("clflushopt 0x12345678(%r8,%rcx,8)");
	/* Also check inकाष्ठाions in the same group encoding as clflushopt */
	यंत्र अस्थिर("clflush (%rax)");
	यंत्र अस्थिर("clflush (%r8)");
	यंत्र अस्थिर("sfence");

	/* clwb m8 */

	यंत्र अस्थिर("clwb (%rax)");
	यंत्र अस्थिर("clwb (%r8)");
	यंत्र अस्थिर("clwb (0x12345678)");
	यंत्र अस्थिर("clwb 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("clwb 0x12345678(%r8,%rcx,8)");
	/* Also check inकाष्ठाions in the same group encoding as clwb */
	यंत्र अस्थिर("xsaveopt (%rax)");
	यंत्र अस्थिर("xsaveopt (%r8)");
	यंत्र अस्थिर("mfence");

	/* cldemote m8 */

	यंत्र अस्थिर("cldemote (%rax)");
	यंत्र अस्थिर("cldemote (%r8)");
	यंत्र अस्थिर("cldemote (0x12345678)");
	यंत्र अस्थिर("cldemote 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("cldemote 0x12345678(%r8,%rcx,8)");

	/* xsavec mem */

	यंत्र अस्थिर("xsavec (%rax)");
	यंत्र अस्थिर("xsavec (%r8)");
	यंत्र अस्थिर("xsavec (0x12345678)");
	यंत्र अस्थिर("xsavec 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("xsavec 0x12345678(%r8,%rcx,8)");

	/* xsaves mem */

	यंत्र अस्थिर("xsaves (%rax)");
	यंत्र अस्थिर("xsaves (%r8)");
	यंत्र अस्थिर("xsaves (0x12345678)");
	यंत्र अस्थिर("xsaves 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("xsaves 0x12345678(%r8,%rcx,8)");

	/* xrstors mem */

	यंत्र अस्थिर("xrstors (%rax)");
	यंत्र अस्थिर("xrstors (%r8)");
	यंत्र अस्थिर("xrstors (0x12345678)");
	यंत्र अस्थिर("xrstors 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("xrstors 0x12345678(%r8,%rcx,8)");

	/* ptग_लिखो */

	यंत्र अस्थिर("ptwrite (%rax)");
	यंत्र अस्थिर("ptwrite (%r8)");
	यंत्र अस्थिर("ptwrite (0x12345678)");
	यंत्र अस्थिर("ptwrite 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("ptwrite 0x12345678(%r8,%rcx,8)");

	यंत्र अस्थिर("ptwritel (%rax)");
	यंत्र अस्थिर("ptwritel (%r8)");
	यंत्र अस्थिर("ptwritel (0x12345678)");
	यंत्र अस्थिर("ptwritel 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("ptwritel 0x12345678(%r8,%rcx,8)");

	यंत्र अस्थिर("ptwriteq (%rax)");
	यंत्र अस्थिर("ptwriteq (%r8)");
	यंत्र अस्थिर("ptwriteq (0x12345678)");
	यंत्र अस्थिर("ptwriteq 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("ptwriteq 0x12345678(%r8,%rcx,8)");

	/* tछोड़ो */

	यंत्र अस्थिर("tpause %ebx");
	यंत्र अस्थिर("tpause %r8d");

	/* umonitor */

	यंत्र अस्थिर("umonitor %eax");
	यंत्र अस्थिर("umonitor %rax");
	यंत्र अस्थिर("umonitor %r8d");

	/* umरुको */

	यंत्र अस्थिर("umwait %eax");
	यंत्र अस्थिर("umwait %r8d");

	/* movdiri */

	यंत्र अस्थिर("movdiri %rax,(%rbx)");
	यंत्र अस्थिर("movdiri %rcx,0x12345678(%rax)");

	/* movdir64b */

	यंत्र अस्थिर("movdir64b (%rax),%rbx");
	यंत्र अस्थिर("movdir64b 0x12345678(%rax),%rcx");
	यंत्र अस्थिर("movdir64b (%eax),%ebx");
	यंत्र अस्थिर("movdir64b 0x12345678(%eax),%ecx");

	/* enqcmd */

	यंत्र अस्थिर("enqcmd (%rax),%rbx");
	यंत्र अस्थिर("enqcmd 0x12345678(%rax),%rcx");
	यंत्र अस्थिर("enqcmd (%eax),%ebx");
	यंत्र अस्थिर("enqcmd 0x12345678(%eax),%ecx");

	/* enqcmds */

	यंत्र अस्थिर("enqcmds (%rax),%rbx");
	यंत्र अस्थिर("enqcmds 0x12345678(%rax),%rcx");
	यंत्र अस्थिर("enqcmds (%eax),%ebx");
	यंत्र अस्थिर("enqcmds 0x12345678(%eax),%ecx");

	/* incsspd/q */

	यंत्र अस्थिर("incsspd %eax");
	यंत्र अस्थिर("incsspd %r8d");
	यंत्र अस्थिर("incsspq %rax");
	यंत्र अस्थिर("incsspq %r8");
	/* Also check inकाष्ठाions in the same group encoding as incsspd/q */
	यंत्र अस्थिर("xrstor (%rax)");
	यंत्र अस्थिर("xrstor (%r8)");
	यंत्र अस्थिर("xrstor (0x12345678)");
	यंत्र अस्थिर("xrstor 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("xrstor 0x12345678(%r8,%rcx,8)");
	यंत्र अस्थिर("lfence");

	/* rdsspd/q */

	यंत्र अस्थिर("rdsspd %eax");
	यंत्र अस्थिर("rdsspd %r8d");
	यंत्र अस्थिर("rdsspq %rax");
	यंत्र अस्थिर("rdsspq %r8");

	/* saveprevssp */

	यंत्र अस्थिर("saveprevssp");

	/* rstorssp */

	यंत्र अस्थिर("rstorssp (%rax)");
	यंत्र अस्थिर("rstorssp (%r8)");
	यंत्र अस्थिर("rstorssp (0x12345678)");
	यंत्र अस्थिर("rstorssp 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("rstorssp 0x12345678(%r8,%rcx,8)");

	/* wrssd/q */

	यंत्र अस्थिर("wrssd %ecx,(%rax)");
	यंत्र अस्थिर("wrssd %edx,(%r8)");
	यंत्र अस्थिर("wrssd %edx,(0x12345678)");
	यंत्र अस्थिर("wrssd %edx,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("wrssd %edx,0x12345678(%r8,%rcx,8)");
	यंत्र अस्थिर("wrssq %rcx,(%rax)");
	यंत्र अस्थिर("wrssq %rdx,(%r8)");
	यंत्र अस्थिर("wrssq %rdx,(0x12345678)");
	यंत्र अस्थिर("wrssq %rdx,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("wrssq %rdx,0x12345678(%r8,%rcx,8)");

	/* wrussd/q */

	यंत्र अस्थिर("wrussd %ecx,(%rax)");
	यंत्र अस्थिर("wrussd %edx,(%r8)");
	यंत्र अस्थिर("wrussd %edx,(0x12345678)");
	यंत्र अस्थिर("wrussd %edx,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("wrussd %edx,0x12345678(%r8,%rcx,8)");
	यंत्र अस्थिर("wrussq %rcx,(%rax)");
	यंत्र अस्थिर("wrussq %rdx,(%r8)");
	यंत्र अस्थिर("wrussq %rdx,(0x12345678)");
	यंत्र अस्थिर("wrussq %rdx,0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("wrussq %rdx,0x12345678(%r8,%rcx,8)");

	/* setssbsy */

	यंत्र अस्थिर("setssbsy");
	/* Also check inकाष्ठाions in the same group encoding as setssbsy */
	यंत्र अस्थिर("rdpkru");
	यंत्र अस्थिर("wrpkru");

	/* clrssbsy */

	यंत्र अस्थिर("clrssbsy (%rax)");
	यंत्र अस्थिर("clrssbsy (%r8)");
	यंत्र अस्थिर("clrssbsy (0x12345678)");
	यंत्र अस्थिर("clrssbsy 0x12345678(%rax,%rcx,8)");
	यंत्र अस्थिर("clrssbsy 0x12345678(%r8,%rcx,8)");

	/* endbr32/64 */

	यंत्र अस्थिर("endbr32");
	यंत्र अस्थिर("endbr64");

	/* call with/without notrack prefix */

	यंत्र अस्थिर("callq *%rax");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("callq *(%rax)");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("callq *(%r8)");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("callq *(0x12345678)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("callq *0x12345678(%rax,%rcx,8)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("callq *0x12345678(%r8,%rcx,8)");		/* Expecting: call indirect 0 */

	यंत्र अस्थिर("bnd callq *%rax");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd callq *(%rax)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd callq *(%r8)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd callq *(0x12345678)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd callq *0x12345678(%rax,%rcx,8)");	/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd callq *0x12345678(%r8,%rcx,8)");	/* Expecting: call indirect 0 */

	यंत्र अस्थिर("notrack callq *%rax");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack callq *(%rax)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack callq *(%r8)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack callq *(0x12345678)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack callq *0x12345678(%rax,%rcx,8)");	/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack callq *0x12345678(%r8,%rcx,8)");	/* Expecting: call indirect 0 */

	यंत्र अस्थिर("notrack bnd callq *%rax");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd callq *(%rax)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd callq *(%r8)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd callq *(0x12345678)");	/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd callq *0x12345678(%rax,%rcx,8)");	/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd callq *0x12345678(%r8,%rcx,8)");	/* Expecting: call indirect 0 */

	/* jmp with/without notrack prefix */

	यंत्र अस्थिर("jmpq *%rax");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmpq *(%rax)");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmpq *(%r8)");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmpq *(0x12345678)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmpq *0x12345678(%rax,%rcx,8)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmpq *0x12345678(%r8,%rcx,8)");		/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("bnd jmpq *%rax");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmpq *(%rax)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmpq *(%r8)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmpq *(0x12345678)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmpq *0x12345678(%rax,%rcx,8)");	/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmpq *0x12345678(%r8,%rcx,8)");	/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("notrack jmpq *%rax");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmpq *(%rax)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmpq *(%r8)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmpq *(0x12345678)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmpq *0x12345678(%rax,%rcx,8)");	/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmpq *0x12345678(%r8,%rcx,8)");	/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("notrack bnd jmpq *%rax");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmpq *(%rax)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmpq *(%r8)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmpq *(0x12345678)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmpq *0x12345678(%rax,%rcx,8)");	/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmpq *0x12345678(%r8,%rcx,8)");	/* Expecting: jmp indirect 0 */

#अन्यथा  /* #अगर_घोषित __x86_64__ */

	/* bound r32, mem (same op code as EVEX prefix) */

	यंत्र अस्थिर("bound %eax, 0x12345678(%ecx)");
	यंत्र अस्थिर("bound %ecx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %ebx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %esp, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %ebp, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %esi, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %edi, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %ecx, (%eax)");
	यंत्र अस्थिर("bound %eax, (0x12345678)");
	यंत्र अस्थिर("bound %edx, (%ecx,%eax,1)");
	यंत्र अस्थिर("bound %edx, 0x12345678(,%eax,1)");
	यंत्र अस्थिर("bound %edx, (%eax,%ecx,1)");
	यंत्र अस्थिर("bound %edx, (%eax,%ecx,8)");
	यंत्र अस्थिर("bound %edx, 0x12(%eax)");
	यंत्र अस्थिर("bound %edx, 0x12(%ebp)");
	यंत्र अस्थिर("bound %edx, 0x12(%ecx,%eax,1)");
	यंत्र अस्थिर("bound %edx, 0x12(%ebp,%eax,1)");
	यंत्र अस्थिर("bound %edx, 0x12(%eax,%ecx,1)");
	यंत्र अस्थिर("bound %edx, 0x12(%eax,%ecx,8)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%ebp)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%ecx,%eax,1)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%ebp,%eax,1)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%eax,%ecx,1)");
	यंत्र अस्थिर("bound %edx, 0x12345678(%eax,%ecx,8)");

	/* bound r16, mem (same op code as EVEX prefix) */

	यंत्र अस्थिर("bound %ax, 0x12345678(%ecx)");
	यंत्र अस्थिर("bound %cx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %bx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %sp, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %bp, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %si, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %di, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %cx, (%eax)");
	यंत्र अस्थिर("bound %ax, (0x12345678)");
	यंत्र अस्थिर("bound %dx, (%ecx,%eax,1)");
	यंत्र अस्थिर("bound %dx, 0x12345678(,%eax,1)");
	यंत्र अस्थिर("bound %dx, (%eax,%ecx,1)");
	यंत्र अस्थिर("bound %dx, (%eax,%ecx,8)");
	यंत्र अस्थिर("bound %dx, 0x12(%eax)");
	यंत्र अस्थिर("bound %dx, 0x12(%ebp)");
	यंत्र अस्थिर("bound %dx, 0x12(%ecx,%eax,1)");
	यंत्र अस्थिर("bound %dx, 0x12(%ebp,%eax,1)");
	यंत्र अस्थिर("bound %dx, 0x12(%eax,%ecx,1)");
	यंत्र अस्थिर("bound %dx, 0x12(%eax,%ecx,8)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%eax)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%ebp)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%ecx,%eax,1)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%ebp,%eax,1)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%eax,%ecx,1)");
	यंत्र अस्थिर("bound %dx, 0x12345678(%eax,%ecx,8)");

	/* AVX-512: Inकाष्ठाions with the same op codes as Mask Inकाष्ठाions  */

	यंत्र अस्थिर("cmovno %eax,%ebx");
	यंत्र अस्थिर("cmovno 0x12345678(%eax),%ecx");
	यंत्र अस्थिर("cmovno 0x12345678(%eax),%cx");

	यंत्र अस्थिर("cmove  %eax,%ebx");
	यंत्र अस्थिर("cmove 0x12345678(%eax),%ecx");
	यंत्र अस्थिर("cmove 0x12345678(%eax),%cx");

	यंत्र अस्थिर("seto    0x12345678(%eax)");
	यंत्र अस्थिर("setno   0x12345678(%eax)");
	यंत्र अस्थिर("setb    0x12345678(%eax)");
	यंत्र अस्थिर("setc    0x12345678(%eax)");
	यंत्र अस्थिर("setnae  0x12345678(%eax)");
	यंत्र अस्थिर("setae   0x12345678(%eax)");
	यंत्र अस्थिर("setnb   0x12345678(%eax)");
	यंत्र अस्थिर("setnc   0x12345678(%eax)");
	यंत्र अस्थिर("sets    0x12345678(%eax)");
	यंत्र अस्थिर("setns   0x12345678(%eax)");

	/* AVX-512: Mask Inकाष्ठाions */

	यंत्र अस्थिर("kandw  %k7,%k6,%k5");
	यंत्र अस्थिर("kandq  %k7,%k6,%k5");
	यंत्र अस्थिर("kandb  %k7,%k6,%k5");
	यंत्र अस्थिर("kandd  %k7,%k6,%k5");

	यंत्र अस्थिर("kandnw  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnq  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnb  %k7,%k6,%k5");
	यंत्र अस्थिर("kandnd  %k7,%k6,%k5");

	यंत्र अस्थिर("knotw  %k7,%k6");
	यंत्र अस्थिर("knotq  %k7,%k6");
	यंत्र अस्थिर("knotb  %k7,%k6");
	यंत्र अस्थिर("knotd  %k7,%k6");

	यंत्र अस्थिर("korw  %k7,%k6,%k5");
	यंत्र अस्थिर("korq  %k7,%k6,%k5");
	यंत्र अस्थिर("korb  %k7,%k6,%k5");
	यंत्र अस्थिर("kord  %k7,%k6,%k5");

	यंत्र अस्थिर("kxnorw  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnorq  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnorb  %k7,%k6,%k5");
	यंत्र अस्थिर("kxnord  %k7,%k6,%k5");

	यंत्र अस्थिर("kxorw  %k7,%k6,%k5");
	यंत्र अस्थिर("kxorq  %k7,%k6,%k5");
	यंत्र अस्थिर("kxorb  %k7,%k6,%k5");
	यंत्र अस्थिर("kxord  %k7,%k6,%k5");

	यंत्र अस्थिर("kaddw  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddq  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddb  %k7,%k6,%k5");
	यंत्र अस्थिर("kaddd  %k7,%k6,%k5");

	यंत्र अस्थिर("kunpckbw %k7,%k6,%k5");
	यंत्र अस्थिर("kunpckwd %k7,%k6,%k5");
	यंत्र अस्थिर("kunpckdq %k7,%k6,%k5");

	यंत्र अस्थिर("kmovw  %k6,%k5");
	यंत्र अस्थिर("kmovw  (%ecx),%k5");
	यंत्र अस्थिर("kmovw  0x123(%eax,%ecx,8),%k5");
	यंत्र अस्थिर("kmovw  %k5,(%ecx)");
	यंत्र अस्थिर("kmovw  %k5,0x123(%eax,%ecx,8)");
	यंत्र अस्थिर("kmovw  %eax,%k5");
	यंत्र अस्थिर("kmovw  %ebp,%k5");
	यंत्र अस्थिर("kmovw  %k5,%eax");
	यंत्र अस्थिर("kmovw  %k5,%ebp");

	यंत्र अस्थिर("kmovq  %k6,%k5");
	यंत्र अस्थिर("kmovq  (%ecx),%k5");
	यंत्र अस्थिर("kmovq  0x123(%eax,%ecx,8),%k5");
	यंत्र अस्थिर("kmovq  %k5,(%ecx)");
	यंत्र अस्थिर("kmovq  %k5,0x123(%eax,%ecx,8)");

	यंत्र अस्थिर("kmovb  %k6,%k5");
	यंत्र अस्थिर("kmovb  (%ecx),%k5");
	यंत्र अस्थिर("kmovb  0x123(%eax,%ecx,8),%k5");
	यंत्र अस्थिर("kmovb  %k5,(%ecx)");
	यंत्र अस्थिर("kmovb  %k5,0x123(%eax,%ecx,8)");
	यंत्र अस्थिर("kmovb  %eax,%k5");
	यंत्र अस्थिर("kmovb  %ebp,%k5");
	यंत्र अस्थिर("kmovb  %k5,%eax");
	यंत्र अस्थिर("kmovb  %k5,%ebp");

	यंत्र अस्थिर("kmovd  %k6,%k5");
	यंत्र अस्थिर("kmovd  (%ecx),%k5");
	यंत्र अस्थिर("kmovd  0x123(%eax,%ecx,8),%k5");
	यंत्र अस्थिर("kmovd  %k5,(%ecx)");
	यंत्र अस्थिर("kmovd  %k5,0x123(%eax,%ecx,8)");
	यंत्र अस्थिर("kmovd  %eax,%k5");
	यंत्र अस्थिर("kmovd  %ebp,%k5");
	यंत्र अस्थिर("kmovd  %k5,%eax");
	यंत्र अस्थिर("kmovd  %k5,%ebp");

	यंत्र अस्थिर("kortestw %k6,%k5");
	यंत्र अस्थिर("kortestq %k6,%k5");
	यंत्र अस्थिर("kortestb %k6,%k5");
	यंत्र अस्थिर("kortestd %k6,%k5");

	यंत्र अस्थिर("ktestw %k6,%k5");
	यंत्र अस्थिर("ktestq %k6,%k5");
	यंत्र अस्थिर("ktestb %k6,%k5");
	यंत्र अस्थिर("ktestd %k6,%k5");

	यंत्र अस्थिर("kshiftrw $0x12,%k6,%k5");
	यंत्र अस्थिर("kshiftrq $0x5b,%k6,%k5");
	यंत्र अस्थिर("kshiftlw $0x12,%k6,%k5");
	यंत्र अस्थिर("kshiftlq $0x5b,%k6,%k5");

	/* AVX-512: Op code 0f 5b */
	यंत्र अस्थिर("vcvtdq2ps %xmm5,%xmm6");
	यंत्र अस्थिर("vcvtqq2ps %zmm5,%ymm6{%k7}");
	यंत्र अस्थिर("vcvtps2dq %xmm5,%xmm6");
	यंत्र अस्थिर("vcvttps2dq %xmm5,%xmm6");

	/* AVX-512: Op code 0f 6f */

	यंत्र अस्थिर("movq   %mm0,%mm4");
	यंत्र अस्थिर("vmovdqa %ymm4,%ymm6");
	यंत्र अस्थिर("vmovdqa32 %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqa64 %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu %ymm4,%ymm6");
	यंत्र अस्थिर("vmovdqu32 %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu64 %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu8 %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu16 %zmm5,%zmm6");

	/* AVX-512: Op code 0f 78 */

	यंत्र अस्थिर("vmread %eax,%ebx");
	यंत्र अस्थिर("vcvttps2udq %zmm5,%zmm6");
	यंत्र अस्थिर("vcvttpd2udq %zmm5,%ymm6{%k7}");
	यंत्र अस्थिर("vcvttsd2usi %xmm6,%eax");
	यंत्र अस्थिर("vcvttss2usi %xmm6,%eax");
	यंत्र अस्थिर("vcvttps2uqq %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvttpd2uqq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 79 */

	यंत्र अस्थिर("vmwrite %eax,%ebx");
	यंत्र अस्थिर("vcvtps2udq %zmm5,%zmm6");
	यंत्र अस्थिर("vcvtpd2udq %zmm5,%ymm6{%k7}");
	यंत्र अस्थिर("vcvtsd2usi %xmm6,%eax");
	यंत्र अस्थिर("vcvtss2usi %xmm6,%eax");
	यंत्र अस्थिर("vcvtps2uqq %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvtpd2uqq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 7a */

	यंत्र अस्थिर("vcvtudq2pd %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvtuqq2pd %zmm5,%zmm6");
	यंत्र अस्थिर("vcvtudq2ps %zmm5,%zmm6");
	यंत्र अस्थिर("vcvtuqq2ps %zmm5,%ymm6{%k7}");
	यंत्र अस्थिर("vcvttps2qq %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvttpd2qq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 7b */

	यंत्र अस्थिर("vcvtusi2sd %eax,%xmm5,%xmm6");
	यंत्र अस्थिर("vcvtusi2ss %eax,%xmm5,%xmm6");
	यंत्र अस्थिर("vcvtps2qq %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvtpd2qq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 7f */

	यंत्र अस्थिर("movq.s  %mm0,%mm4");
	यंत्र अस्थिर("vmovdqa.s %ymm5,%ymm6");
	यंत्र अस्थिर("vmovdqa32.s %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqa64.s %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu.s %ymm5,%ymm6");
	यंत्र अस्थिर("vmovdqu32.s %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu64.s %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu8.s %zmm5,%zmm6");
	यंत्र अस्थिर("vmovdqu16.s %zmm5,%zmm6");

	/* AVX-512: Op code 0f db */

	यंत्र अस्थिर("pand  %mm1,%mm2");
	यंत्र अस्थिर("pand  %xmm1,%xmm2");
	यंत्र अस्थिर("vpand  %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpandd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpandq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f df */

	यंत्र अस्थिर("pandn  %mm1,%mm2");
	यंत्र अस्थिर("pandn  %xmm1,%xmm2");
	यंत्र अस्थिर("vpandn %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpandnd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpandnq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f e6 */

	यंत्र अस्थिर("vcvttpd2dq %xmm1,%xmm2");
	यंत्र अस्थिर("vcvtdq2pd %xmm5,%xmm6");
	यंत्र अस्थिर("vcvtdq2pd %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vcvtqq2pd %zmm5,%zmm6");
	यंत्र अस्थिर("vcvtpd2dq %xmm1,%xmm2");

	/* AVX-512: Op code 0f eb */

	यंत्र अस्थिर("por   %mm4,%mm6");
	यंत्र अस्थिर("vpor   %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpord  %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vporq  %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f ef */

	यंत्र अस्थिर("pxor   %mm4,%mm6");
	यंत्र अस्थिर("vpxor  %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpxord %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpxorq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 10 */

	यंत्र अस्थिर("pblendvb %xmm1,%xmm0");
	यंत्र अस्थिर("vpsrlvw %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpmovuswb %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 11 */

	यंत्र अस्थिर("vpmovusdb %zmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vpsravw %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 12 */

	यंत्र अस्थिर("vpmovusqb %zmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vpsllvw %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 13 */

	यंत्र अस्थिर("vcvtph2ps %xmm3,%ymm5");
	यंत्र अस्थिर("vcvtph2ps %ymm5,%zmm6{%k7}");
	यंत्र अस्थिर("vpmovusdw %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 14 */

	यंत्र अस्थिर("blendvps %xmm1,%xmm0");
	यंत्र अस्थिर("vpmovusqw %zmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vprorvd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vprorvq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 15 */

	यंत्र अस्थिर("blendvpd %xmm1,%xmm0");
	यंत्र अस्थिर("vpmovusqd %zmm5,%ymm6{%k7}");
	यंत्र अस्थिर("vprolvd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vprolvq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 16 */

	यंत्र अस्थिर("vpermps %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpermps %ymm4,%ymm6,%ymm2{%k7}");
	यंत्र अस्थिर("vpermpd %ymm4,%ymm6,%ymm2{%k7}");

	/* AVX-512: Op code 0f 38 19 */

	यंत्र अस्थिर("vbroadcastsd %xmm4,%ymm6");
	यंत्र अस्थिर("vbroadcastf32x2 %xmm7,%zmm6");

	/* AVX-512: Op code 0f 38 1a */

	यंत्र अस्थिर("vbroadcastf128 (%ecx),%ymm4");
	यंत्र अस्थिर("vbroadcastf32x4 (%ecx),%zmm6");
	यंत्र अस्थिर("vbroadcastf64x2 (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 1b */

	यंत्र अस्थिर("vbroadcastf32x8 (%ecx),%zmm6");
	यंत्र अस्थिर("vbroadcastf64x4 (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 1f */

	यंत्र अस्थिर("vpabsq %zmm4,%zmm6");

	/* AVX-512: Op code 0f 38 20 */

	यंत्र अस्थिर("vpmovsxbw %xmm4,%xmm5");
	यंत्र अस्थिर("vpmovswb %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 21 */

	यंत्र अस्थिर("vpmovsxbd %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovsdb %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 22 */

	यंत्र अस्थिर("vpmovsxbq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsqb %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 23 */

	यंत्र अस्थिर("vpmovsxwd %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsdw %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 24 */

	यंत्र अस्थिर("vpmovsxwq %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovsqw %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 25 */

	यंत्र अस्थिर("vpmovsxdq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovsqd %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 26 */

	यंत्र अस्थिर("vptestmb %zmm5,%zmm6,%k5");
	यंत्र अस्थिर("vptestmw %zmm5,%zmm6,%k5");
	यंत्र अस्थिर("vptestnmb %zmm4,%zmm5,%k5");
	यंत्र अस्थिर("vptestnmw %zmm4,%zmm5,%k5");

	/* AVX-512: Op code 0f 38 27 */

	यंत्र अस्थिर("vptestmd %zmm5,%zmm6,%k5");
	यंत्र अस्थिर("vptestmq %zmm5,%zmm6,%k5");
	यंत्र अस्थिर("vptestnmd %zmm4,%zmm5,%k5");
	यंत्र अस्थिर("vptestnmq %zmm4,%zmm5,%k5");

	/* AVX-512: Op code 0f 38 28 */

	यंत्र अस्थिर("vpmuldq %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovm2b %k5,%zmm6");
	यंत्र अस्थिर("vpmovm2w %k5,%zmm6");

	/* AVX-512: Op code 0f 38 29 */

	यंत्र अस्थिर("vpcmpeqq %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovb2m %zmm6,%k5");
	यंत्र अस्थिर("vpmovw2m %zmm6,%k5");

	/* AVX-512: Op code 0f 38 2a */

	यंत्र अस्थिर("vmovntdqa (%ecx),%ymm4");
	यंत्र अस्थिर("vpbroadcastmb2q %k6,%zmm1");

	/* AVX-512: Op code 0f 38 2c */

	यंत्र अस्थिर("vmaskmovps (%ecx),%ymm4,%ymm6");
	यंत्र अस्थिर("vscalefps %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vscalefpd %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 2d */

	यंत्र अस्थिर("vmaskmovpd (%ecx),%ymm4,%ymm6");
	यंत्र अस्थिर("vscalefss %xmm4,%xmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vscalefsd %xmm4,%xmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 30 */

	यंत्र अस्थिर("vpmovzxbw %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovwb %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 31 */

	यंत्र अस्थिर("vpmovzxbd %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovdb %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 32 */

	यंत्र अस्थिर("vpmovzxbq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovqb %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 33 */

	यंत्र अस्थिर("vpmovzxwd %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovdw %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 34 */

	यंत्र अस्थिर("vpmovzxwq %xmm4,%ymm6");
	यंत्र अस्थिर("vpmovqw %zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 35 */

	यंत्र अस्थिर("vpmovzxdq %xmm4,%ymm4");
	यंत्र अस्थिर("vpmovqd %zmm5,%ymm6{%k7}");

	/* AVX-512: Op code 0f 38 36 */

	यंत्र अस्थिर("vpermd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpermd %ymm4,%ymm6,%ymm2{%k7}");
	यंत्र अस्थिर("vpermq %ymm4,%ymm6,%ymm2{%k7}");

	/* AVX-512: Op code 0f 38 38 */

	यंत्र अस्थिर("vpminsb %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmovm2d %k5,%zmm6");
	यंत्र अस्थिर("vpmovm2q %k5,%zmm6");

	/* AVX-512: Op code 0f 38 39 */

	यंत्र अस्थिर("vpminsd %xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpminsd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpminsq %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpmovd2m %zmm6,%k5");
	यंत्र अस्थिर("vpmovq2m %zmm6,%k5");

	/* AVX-512: Op code 0f 38 3a */

	यंत्र अस्थिर("vpminuw %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpbroadcastmw2d %k6,%zmm6");

	/* AVX-512: Op code 0f 38 3b */

	यंत्र अस्थिर("vpminud %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpminud %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpminuq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 3d */

	यंत्र अस्थिर("vpmaxsd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmaxsd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpmaxsq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 3f */

	यंत्र अस्थिर("vpmaxud %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmaxud %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpmaxuq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 40 */

	यंत्र अस्थिर("vpmulld %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpmulld %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpmullq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 42 */

	यंत्र अस्थिर("vgetexpps %zmm5,%zmm6");
	यंत्र अस्थिर("vgetexppd %zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 43 */

	यंत्र अस्थिर("vgetexpss %xmm4,%xmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vgetexpsd %xmm2,%xmm3,%xmm4{%k7}");

	/* AVX-512: Op code 0f 38 44 */

	यंत्र अस्थिर("vplzcntd %zmm5,%zmm6");
	यंत्र अस्थिर("vplzcntq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 46 */

	यंत्र अस्थिर("vpsravd %ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vpsravd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpsravq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 4c */

	यंत्र अस्थिर("vrcp14ps %zmm5,%zmm6");
	यंत्र अस्थिर("vrcp14pd %zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 4d */

	यंत्र अस्थिर("vrcp14ss %xmm4,%xmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vrcp14sd %xmm4,%xmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 4e */

	यंत्र अस्थिर("vrsqrt14ps %zmm5,%zmm6");
	यंत्र अस्थिर("vrsqrt14pd %zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 4f */

	यंत्र अस्थिर("vrsqrt14ss %xmm4,%xmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vrsqrt14sd %xmm4,%xmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 38 50 */

	यंत्र अस्थिर("vpdpbusd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpbusd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpbusd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpbusd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 51 */

	यंत्र अस्थिर("vpdpbusds %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpbusds %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpbusds %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpbusds 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 52 */

	यंत्र अस्थिर("vdpbf16ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vdpbf16ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vdpbf16ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vdpbf16ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpdpwssd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpwssd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpwssd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpwssd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vp4dpwssd (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssd 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 53 */

	यंत्र अस्थिर("vpdpwssds %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpdpwssds %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpdpwssds %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpdpwssds 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vp4dpwssds (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("vp4dpwssds 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 54 */

	यंत्र अस्थिर("vpopcntb %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntb %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntb %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntb 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpopcntw %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntw %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntw %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntw 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 55 */

	यंत्र अस्थिर("vpopcntd %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntd %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntd %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntd 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpopcntq %xmm1, %xmm2");
	यंत्र अस्थिर("vpopcntq %ymm1, %ymm2");
	यंत्र अस्थिर("vpopcntq %zmm1, %zmm2");
	यंत्र अस्थिर("vpopcntq 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 59 */

	यंत्र अस्थिर("vpbroadcastq %xmm4,%xmm6");
	यंत्र अस्थिर("vbroadcasti32x2 %xmm7,%zmm6");

	/* AVX-512: Op code 0f 38 5a */

	यंत्र अस्थिर("vbroadcasti128 (%ecx),%ymm4");
	यंत्र अस्थिर("vbroadcasti32x4 (%ecx),%zmm6");
	यंत्र अस्थिर("vbroadcasti64x2 (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 5b */

	यंत्र अस्थिर("vbroadcasti32x8 (%ecx),%zmm6");
	यंत्र अस्थिर("vbroadcasti64x4 (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 62 */

	यंत्र अस्थिर("vpexpandb %xmm1, %xmm2");
	यंत्र अस्थिर("vpexpandb %ymm1, %ymm2");
	यंत्र अस्थिर("vpexpandb %zmm1, %zmm2");
	यंत्र अस्थिर("vpexpandb 0x12345678(%eax,%ecx,8),%zmm2");

	यंत्र अस्थिर("vpexpandw %xmm1, %xmm2");
	यंत्र अस्थिर("vpexpandw %ymm1, %ymm2");
	यंत्र अस्थिर("vpexpandw %zmm1, %zmm2");
	यंत्र अस्थिर("vpexpandw 0x12345678(%eax,%ecx,8),%zmm2");

	/* AVX-512: Op code 0f 38 63 */

	यंत्र अस्थिर("vpcompressb %xmm1, %xmm2");
	यंत्र अस्थिर("vpcompressb %ymm1, %ymm2");
	यंत्र अस्थिर("vpcompressb %zmm1, %zmm2");
	यंत्र अस्थिर("vpcompressb %zmm2,0x12345678(%eax,%ecx,8)");

	यंत्र अस्थिर("vpcompressw %xmm1, %xmm2");
	यंत्र अस्थिर("vpcompressw %ymm1, %ymm2");
	यंत्र अस्थिर("vpcompressw %zmm1, %zmm2");
	यंत्र अस्थिर("vpcompressw %zmm2,0x12345678(%eax,%ecx,8)");

	/* AVX-512: Op code 0f 38 64 */

	यंत्र अस्थिर("vpblendmd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpblendmq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 65 */

	यंत्र अस्थिर("vblendmps %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vblendmpd %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 66 */

	यंत्र अस्थिर("vpblendmb %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpblendmw %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 68 */

	यंत्र अस्थिर("vp2intersectd %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vp2intersectd %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vp2intersectd %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vp2intersectd 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	यंत्र अस्थिर("vp2intersectq %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vp2intersectq %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vp2intersectq %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vp2intersectq 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	/* AVX-512: Op code 0f 38 70 */

	यंत्र अस्थिर("vpshldvw %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvw %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvw %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvw 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 71 */

	यंत्र अस्थिर("vpshldvd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpshldvq %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshldvq %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshldvq %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshldvq 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 72 */

	यंत्र अस्थिर("vcvtne2ps2bf16 %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vcvtne2ps2bf16 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vcvtneps2bf16 %xmm1, %xmm2");
	यंत्र अस्थिर("vcvtneps2bf16 %ymm1, %xmm2");
	यंत्र अस्थिर("vcvtneps2bf16 %zmm1, %ymm2");
	यंत्र अस्थिर("vcvtneps2bf16 0x12345678(%eax,%ecx,8),%ymm2");

	यंत्र अस्थिर("vpshrdvw %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvw %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvw %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvw 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 73 */

	यंत्र अस्थिर("vpshrdvd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vpshrdvq %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vpshrdvq %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vpshrdvq %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vpshrdvq 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 75 */

	यंत्र अस्थिर("vpermi2b %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermi2w %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 76 */

	यंत्र अस्थिर("vpermi2d %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermi2q %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 77 */

	यंत्र अस्थिर("vpermi2ps %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermi2pd %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 7a */

	यंत्र अस्थिर("vpbroadcastb %eax,%xmm3");

	/* AVX-512: Op code 0f 38 7b */

	यंत्र अस्थिर("vpbroadcastw %eax,%xmm3");

	/* AVX-512: Op code 0f 38 7c */

	यंत्र अस्थिर("vpbroadcastd %eax,%xmm3");

	/* AVX-512: Op code 0f 38 7d */

	यंत्र अस्थिर("vpermt2b %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermt2w %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 7e */

	यंत्र अस्थिर("vpermt2d %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermt2q %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 7f */

	यंत्र अस्थिर("vpermt2ps %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermt2pd %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 83 */

	यंत्र अस्थिर("vpmultishiftqb %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 88 */

	यंत्र अस्थिर("vexpandps (%ecx),%zmm6");
	यंत्र अस्थिर("vexpandpd (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 89 */

	यंत्र अस्थिर("vpexpandd (%ecx),%zmm6");
	यंत्र अस्थिर("vpexpandq (%ecx),%zmm6");

	/* AVX-512: Op code 0f 38 8a */

	यंत्र अस्थिर("vcompressps %zmm6,(%ecx)");
	यंत्र अस्थिर("vcompresspd %zmm6,(%ecx)");

	/* AVX-512: Op code 0f 38 8b */

	यंत्र अस्थिर("vpcompressd %zmm6,(%ecx)");
	यंत्र अस्थिर("vpcompressq %zmm6,(%ecx)");

	/* AVX-512: Op code 0f 38 8d */

	यंत्र अस्थिर("vpermb %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vpermw %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 8f */

	यंत्र अस्थिर("vpshufbitqmb %xmm1, %xmm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb %ymm1, %ymm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb %zmm1, %zmm2, %k3");
	यंत्र अस्थिर("vpshufbitqmb 0x12345678(%eax,%ecx,8),%zmm2,%k3");

	/* AVX-512: Op code 0f 38 90 */

	यंत्र अस्थिर("vpgatherdd %xmm2,0x02(%ebp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherdq %xmm2,0x04(%ebp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherdd 0x7b(%ebp,%zmm7,8),%zmm6{%k1}");
	यंत्र अस्थिर("vpgatherdq 0x7b(%ebp,%ymm7,8),%zmm6{%k1}");

	/* AVX-512: Op code 0f 38 91 */

	यंत्र अस्थिर("vpgatherqd %xmm2,0x02(%ebp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherqq %xmm2,0x02(%ebp,%xmm7,2),%xmm1");
	यंत्र अस्थिर("vpgatherqd 0x7b(%ebp,%zmm7,8),%ymm6{%k1}");
	यंत्र अस्थिर("vpgatherqq 0x7b(%ebp,%zmm7,8),%zmm6{%k1}");

	/* AVX-512: Op code 0f 38 9a */

	यंत्र अस्थिर("vfmsub132ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub132ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub132ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vfmsub132pd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132pd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub132pd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub132pd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("v4fmaddps (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fmaddps 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 9b */

	यंत्र अस्थिर("vfmsub132ss %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132ss 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("vfmsub132sd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub132sd 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("v4fmaddss (%eax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fmaddss 0x12345678(%eax,%ecx,8),%xmm0,%xmm4");

	/* AVX-512: Op code 0f 38 a0 */

	यंत्र अस्थिर("vpscatterdd %zmm6,0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vpscatterdq %zmm6,0x7b(%ebp,%ymm7,8){%k1}");

	/* AVX-512: Op code 0f 38 a1 */

	यंत्र अस्थिर("vpscatterqd %ymm6,0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vpscatterqq %ymm6,0x7b(%ebp,%ymm7,8){%k1}");

	/* AVX-512: Op code 0f 38 a2 */

	यंत्र अस्थिर("vscatterdps %zmm6,0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterdpd %zmm6,0x7b(%ebp,%ymm7,8){%k1}");

	/* AVX-512: Op code 0f 38 a3 */

	यंत्र अस्थिर("vscatterqps %ymm6,0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterqpd %zmm6,0x7b(%ebp,%zmm7,8){%k1}");

	/* AVX-512: Op code 0f 38 aa */

	यंत्र अस्थिर("vfmsub213ps %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213ps %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub213ps %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub213ps 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("vfmsub213pd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213pd %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vfmsub213pd %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vfmsub213pd 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	यंत्र अस्थिर("v4fnmaddps (%eax), %zmm0, %zmm4");
	यंत्र अस्थिर("v4fnmaddps 0x12345678(%eax,%ecx,8),%zmm0,%zmm4");

	/* AVX-512: Op code 0f 38 ab */

	यंत्र अस्थिर("vfmsub213ss %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213ss 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("vfmsub213sd %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vfmsub213sd 0x12345678(%eax,%ecx,8),%xmm2,%xmm3");

	यंत्र अस्थिर("v4fnmaddss (%eax), %xmm0, %xmm4");
	यंत्र अस्थिर("v4fnmaddss 0x12345678(%eax,%ecx,8),%xmm0,%xmm4");

	/* AVX-512: Op code 0f 38 b4 */

	यंत्र अस्थिर("vpmadd52luq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 b5 */

	यंत्र अस्थिर("vpmadd52huq %zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 c4 */

	यंत्र अस्थिर("vpconflictd %zmm5,%zmm6");
	यंत्र अस्थिर("vpconflictq %zmm5,%zmm6");

	/* AVX-512: Op code 0f 38 c8 */

	यंत्र अस्थिर("vexp2ps %zmm6,%zmm7");
	यंत्र अस्थिर("vexp2pd %zmm6,%zmm7");

	/* AVX-512: Op code 0f 38 ca */

	यंत्र अस्थिर("vrcp28ps %zmm6,%zmm7");
	यंत्र अस्थिर("vrcp28pd %zmm6,%zmm7");

	/* AVX-512: Op code 0f 38 cb */

	यंत्र अस्थिर("vrcp28ss %xmm5,%xmm6,%xmm7{%k7}");
	यंत्र अस्थिर("vrcp28sd %xmm5,%xmm6,%xmm7{%k7}");

	/* AVX-512: Op code 0f 38 cc */

	यंत्र अस्थिर("vrsqrt28ps %zmm6,%zmm7");
	यंत्र अस्थिर("vrsqrt28pd %zmm6,%zmm7");

	/* AVX-512: Op code 0f 38 cd */

	यंत्र अस्थिर("vrsqrt28ss %xmm5,%xmm6,%xmm7{%k7}");
	यंत्र अस्थिर("vrsqrt28sd %xmm5,%xmm6,%xmm7{%k7}");

	/* AVX-512: Op code 0f 38 cf */

	यंत्र अस्थिर("gf2p8mulb %xmm1, %xmm3");
	यंत्र अस्थिर("gf2p8mulb 0x12345678(%eax,%ecx,8),%xmm3");

	यंत्र अस्थिर("vgf2p8mulb %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vgf2p8mulb %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vgf2p8mulb %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vgf2p8mulb 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 dc */

	यंत्र अस्थिर("vaesenc %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesenc %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesenc %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesenc 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 dd */

	यंत्र अस्थिर("vaesenclast %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesenclast %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesenclast %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesenclast 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 de */

	यंत्र अस्थिर("vaesdec %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesdec %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesdec %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesdec 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 38 df */

	यंत्र अस्थिर("vaesdeclast %xmm1, %xmm2, %xmm3");
	यंत्र अस्थिर("vaesdeclast %ymm1, %ymm2, %ymm3");
	यंत्र अस्थिर("vaesdeclast %zmm1, %zmm2, %zmm3");
	यंत्र अस्थिर("vaesdeclast 0x12345678(%eax,%ecx,8),%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 03 */

	यंत्र अस्थिर("valignd $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("valignq $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 08 */

	यंत्र अस्थिर("vroundps $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vrndscaleps $0x12,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 3a 09 */

	यंत्र अस्थिर("vroundpd $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vrndscalepd $0x12,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 3a 0a */

	यंत्र अस्थिर("vroundss $0x5,%xmm4,%xmm6,%xmm2");
	यंत्र अस्थिर("vrndscaless $0x12,%xmm4,%xmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 3a 0b */

	यंत्र अस्थिर("vroundsd $0x5,%xmm4,%xmm6,%xmm2");
	यंत्र अस्थिर("vrndscalesd $0x12,%xmm4,%xmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 3a 18 */

	यंत्र अस्थिर("vinsertf128 $0x5,%xmm4,%ymm4,%ymm6");
	यंत्र अस्थिर("vinsertf32x4 $0x12,%xmm4,%zmm5,%zmm6{%k7}");
	यंत्र अस्थिर("vinsertf64x2 $0x12,%xmm4,%zmm5,%zmm6{%k7}");

	/* AVX-512: Op code 0f 3a 19 */

	यंत्र अस्थिर("vextractf128 $0x5,%ymm4,%xmm4");
	यंत्र अस्थिर("vextractf32x4 $0x12,%zmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vextractf64x2 $0x12,%zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 3a 1a */

	यंत्र अस्थिर("vinsertf32x8 $0x12,%ymm5,%zmm6,%zmm7{%k7}");
	यंत्र अस्थिर("vinsertf64x4 $0x12,%ymm5,%zmm6,%zmm7{%k7}");

	/* AVX-512: Op code 0f 3a 1b */

	यंत्र अस्थिर("vextractf32x8 $0x12,%zmm6,%ymm7{%k7}");
	यंत्र अस्थिर("vextractf64x4 $0x12,%zmm6,%ymm7{%k7}");

	/* AVX-512: Op code 0f 3a 1e */

	यंत्र अस्थिर("vpcmpud $0x12,%zmm6,%zmm7,%k5");
	यंत्र अस्थिर("vpcmpuq $0x12,%zmm6,%zmm7,%k5");

	/* AVX-512: Op code 0f 3a 1f */

	यंत्र अस्थिर("vpcmpd $0x12,%zmm6,%zmm7,%k5");
	यंत्र अस्थिर("vpcmpq $0x12,%zmm6,%zmm7,%k5");

	/* AVX-512: Op code 0f 3a 23 */

	यंत्र अस्थिर("vshuff32x4 $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("vshuff64x2 $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 25 */

	यंत्र अस्थिर("vpternlogd $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("vpternlogq $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 26 */

	यंत्र अस्थिर("vgetmantps $0x12,%zmm6,%zmm7");
	यंत्र अस्थिर("vgetmantpd $0x12,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 27 */

	यंत्र अस्थिर("vgetmantss $0x12,%xmm5,%xmm6,%xmm7{%k7}");
	यंत्र अस्थिर("vgetmantsd $0x12,%xmm5,%xmm6,%xmm7{%k7}");

	/* AVX-512: Op code 0f 3a 38 */

	यंत्र अस्थिर("vinserti128 $0x5,%xmm4,%ymm4,%ymm6");
	यंत्र अस्थिर("vinserti32x4 $0x12,%xmm4,%zmm5,%zmm6{%k7}");
	यंत्र अस्थिर("vinserti64x2 $0x12,%xmm4,%zmm5,%zmm6{%k7}");

	/* AVX-512: Op code 0f 3a 39 */

	यंत्र अस्थिर("vextracti128 $0x5,%ymm4,%xmm6");
	यंत्र अस्थिर("vextracti32x4 $0x12,%zmm5,%xmm6{%k7}");
	यंत्र अस्थिर("vextracti64x2 $0x12,%zmm5,%xmm6{%k7}");

	/* AVX-512: Op code 0f 3a 3a */

	यंत्र अस्थिर("vinserti32x8 $0x12,%ymm5,%zmm6,%zmm7{%k7}");
	यंत्र अस्थिर("vinserti64x4 $0x12,%ymm5,%zmm6,%zmm7{%k7}");

	/* AVX-512: Op code 0f 3a 3b */

	यंत्र अस्थिर("vextracti32x8 $0x12,%zmm6,%ymm7{%k7}");
	यंत्र अस्थिर("vextracti64x4 $0x12,%zmm6,%ymm7{%k7}");

	/* AVX-512: Op code 0f 3a 3e */

	यंत्र अस्थिर("vpcmpub $0x12,%zmm6,%zmm7,%k5");
	यंत्र अस्थिर("vpcmpuw $0x12,%zmm6,%zmm7,%k5");

	/* AVX-512: Op code 0f 3a 3f */

	यंत्र अस्थिर("vpcmpb $0x12,%zmm6,%zmm7,%k5");
	यंत्र अस्थिर("vpcmpw $0x12,%zmm6,%zmm7,%k5");

	/* AVX-512: Op code 0f 3a 42 */

	यंत्र अस्थिर("vmpsadbw $0x5,%ymm4,%ymm6,%ymm2");
	यंत्र अस्थिर("vdbpsadbw $0x12,%zmm4,%zmm5,%zmm6");

	/* AVX-512: Op code 0f 3a 43 */

	यंत्र अस्थिर("vshufi32x4 $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("vshufi64x2 $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 44 */

	यंत्र अस्थिर("vpclmulqdq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpclmulqdq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpclmulqdq $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 50 */

	यंत्र अस्थिर("vrangeps $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("vrangepd $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 51 */

	यंत्र अस्थिर("vrangess $0x12,%xmm5,%xmm6,%xmm7");
	यंत्र अस्थिर("vrangesd $0x12,%xmm5,%xmm6,%xmm7");

	/* AVX-512: Op code 0f 3a 54 */

	यंत्र अस्थिर("vfixupimmps $0x12,%zmm5,%zmm6,%zmm7");
	यंत्र अस्थिर("vfixupimmpd $0x12,%zmm5,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 55 */

	यंत्र अस्थिर("vfixupimmss $0x12,%xmm5,%xmm6,%xmm7{%k7}");
	यंत्र अस्थिर("vfixupimmsd $0x12,%xmm5,%xmm6,%xmm7{%k7}");

	/* AVX-512: Op code 0f 3a 56 */

	यंत्र अस्थिर("vreduceps $0x12,%zmm6,%zmm7");
	यंत्र अस्थिर("vreducepd $0x12,%zmm6,%zmm7");

	/* AVX-512: Op code 0f 3a 57 */

	यंत्र अस्थिर("vreducess $0x12,%xmm5,%xmm6,%xmm7");
	यंत्र अस्थिर("vreducesd $0x12,%xmm5,%xmm6,%xmm7");

	/* AVX-512: Op code 0f 3a 66 */

	यंत्र अस्थिर("vfpclassps $0x12,%zmm7,%k5");
	यंत्र अस्थिर("vfpclasspd $0x12,%zmm7,%k5");

	/* AVX-512: Op code 0f 3a 67 */

	यंत्र अस्थिर("vfpclassss $0x12,%xmm7,%k5");
	यंत्र अस्थिर("vfpclasssd $0x12,%xmm7,%k5");

	/* AVX-512: Op code 0f 3a 70 */

	यंत्र अस्थिर("vpshldw $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldw $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldw $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 71 */

	यंत्र अस्थिर("vpshldd $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldd $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldd $0x12,%zmm1,%zmm2,%zmm3");

	यंत्र अस्थिर("vpshldq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshldq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshldq $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 72 */

	यंत्र अस्थिर("vpshrdw $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdw $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdw $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a 73 */

	यंत्र अस्थिर("vpshrdd $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdd $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdd $0x12,%zmm1,%zmm2,%zmm3");

	यंत्र अस्थिर("vpshrdq $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vpshrdq $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vpshrdq $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a ce */

	यंत्र अस्थिर("gf2p8affineqb $0x12,%xmm1,%xmm3");

	यंत्र अस्थिर("vgf2p8affineqb $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vgf2p8affineqb $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vgf2p8affineqb $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 3a cf */

	यंत्र अस्थिर("gf2p8affineinvqb $0x12,%xmm1,%xmm3");

	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%xmm1,%xmm2,%xmm3");
	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%ymm1,%ymm2,%ymm3");
	यंत्र अस्थिर("vgf2p8affineinvqb $0x12,%zmm1,%zmm2,%zmm3");

	/* AVX-512: Op code 0f 72 (Grp13) */

	यंत्र अस्थिर("vprord $0x12,%zmm5,%zmm6");
	यंत्र अस्थिर("vprorq $0x12,%zmm5,%zmm6");
	यंत्र अस्थिर("vprold $0x12,%zmm5,%zmm6");
	यंत्र अस्थिर("vprolq $0x12,%zmm5,%zmm6");
	यंत्र अस्थिर("psrad  $0x2,%mm6");
	यंत्र अस्थिर("vpsrad $0x5,%ymm6,%ymm2");
	यंत्र अस्थिर("vpsrad $0x5,%zmm6,%zmm2");
	यंत्र अस्थिर("vpsraq $0x5,%zmm6,%zmm2");

	/* AVX-512: Op code 0f 38 c6 (Grp18) */

	यंत्र अस्थिर("vgatherpf0dps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf0dpd 0x7b(%ebp,%ymm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf1dps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf1dpd 0x7b(%ebp,%ymm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf0dps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf0dpd 0x7b(%ebp,%ymm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf1dps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf1dpd 0x7b(%ebp,%ymm7,8){%k1}");

	/* AVX-512: Op code 0f 38 c7 (Grp19) */

	यंत्र अस्थिर("vgatherpf0qps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf0qpd 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf1qps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vgatherpf1qpd 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf0qps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf0qpd 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf1qps 0x7b(%ebp,%zmm7,8){%k1}");
	यंत्र अस्थिर("vscatterpf1qpd 0x7b(%ebp,%zmm7,8){%k1}");

	/* AVX-512: Examples */

	यंत्र अस्थिर("vaddpd %zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd %zmm4,%zmm5,%zmm6{%k7}");
	यंत्र अस्थिर("vaddpd %zmm4,%zmm5,%zmm6{%k7}{z}");
	यंत्र अस्थिर("vaddpd {rn-sae},%zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd {ru-sae},%zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd {rd-sae},%zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd {rz-sae},%zmm4,%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd (%ecx),%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd 0x123(%eax,%ecx,8),%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd (%ecx){1to8},%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd 0x1fc0(%edx),%zmm5,%zmm6");
	यंत्र अस्थिर("vaddpd 0x3f8(%edx){1to8},%zmm5,%zmm6");
	यंत्र अस्थिर("vcmpeq_uqps 0x1fc(%edx){1to16},%zmm6,%k5");
	यंत्र अस्थिर("vcmpltsd 0x123(%eax,%ecx,8),%xmm3,%k5{%k7}");
	यंत्र अस्थिर("vcmplesd {sae},%xmm4,%xmm5,%k5{%k7}");
	यंत्र अस्थिर("vgetmantss $0x5b,0x123(%eax,%ecx,8),%xmm4,%xmm5{%k7}");

	/* bndmk m32, bnd */

	यंत्र अस्थिर("bndmk (%eax), %bnd0");
	यंत्र अस्थिर("bndmk (0x12345678), %bnd0");
	यंत्र अस्थिर("bndmk (%eax), %bnd3");
	यंत्र अस्थिर("bndmk (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmk (%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmk 0x12345678(%eax,%ecx,8), %bnd0");

	/* bndcl r/m32, bnd */

	यंत्र अस्थिर("bndcl (%eax), %bnd0");
	यंत्र अस्थिर("bndcl (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcl (%eax), %bnd3");
	यंत्र अस्थिर("bndcl (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcl (%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcl 0x12345678(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcl %eax, %bnd0");

	/* bndcu r/m32, bnd */

	यंत्र अस्थिर("bndcu (%eax), %bnd0");
	यंत्र अस्थिर("bndcu (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcu (%eax), %bnd3");
	यंत्र अस्थिर("bndcu (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcu (%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcu 0x12345678(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcu %eax, %bnd0");

	/* bndcn r/m32, bnd */

	यंत्र अस्थिर("bndcn (%eax), %bnd0");
	यंत्र अस्थिर("bndcn (0x12345678), %bnd0");
	यंत्र अस्थिर("bndcn (%eax), %bnd3");
	यंत्र अस्थिर("bndcn (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcn (%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndcn 0x12345678(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndcn %eax, %bnd0");

	/* bndmov m64, bnd */

	यंत्र अस्थिर("bndmov (%eax), %bnd0");
	यंत्र अस्थिर("bndmov (0x12345678), %bnd0");
	यंत्र अस्थिर("bndmov (%eax), %bnd3");
	यंत्र अस्थिर("bndmov (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmov (%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12(%eax,%ecx,8), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndmov 0x12345678(%eax,%ecx,8), %bnd0");

	/* bndmov bnd, m64 */

	यंत्र अस्थिर("bndmov %bnd0, (%eax)");
	यंत्र अस्थिर("bndmov %bnd0, (0x12345678)");
	यंत्र अस्थिर("bndmov %bnd3, (%eax)");
	यंत्र अस्थिर("bndmov %bnd0, (%ecx,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, (%eax,%ecx,1)");
	यंत्र अस्थिर("bndmov %bnd0, (%eax,%ecx,8)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%eax)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%ebp)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%ecx,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%ebp,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%eax,%ecx,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12(%eax,%ecx,8)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%eax)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%ebp)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%ecx,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%ebp,%eax,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%eax,%ecx,1)");
	यंत्र अस्थिर("bndmov %bnd0, 0x12345678(%eax,%ecx,8)");

	/* bndmov bnd2, bnd1 */

	यंत्र अस्थिर("bndmov %bnd0, %bnd1");
	यंत्र अस्थिर("bndmov %bnd1, %bnd0");

	/* bndldx mib, bnd */

	यंत्र अस्थिर("bndldx (%eax), %bnd0");
	यंत्र अस्थिर("bndldx (0x12345678), %bnd0");
	यंत्र अस्थिर("bndldx (%eax), %bnd3");
	यंत्र अस्थिर("bndldx (%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx (%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%eax), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%ebp), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12(%eax,%ecx,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%eax), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%ebp), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%ecx,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%ebp,%eax,1), %bnd0");
	यंत्र अस्थिर("bndldx 0x12345678(%eax,%ecx,1), %bnd0");

	/* bndstx bnd, mib */

	यंत्र अस्थिर("bndstx %bnd0, (%eax)");
	यंत्र अस्थिर("bndstx %bnd0, (0x12345678)");
	यंत्र अस्थिर("bndstx %bnd3, (%eax)");
	यंत्र अस्थिर("bndstx %bnd0, (%ecx,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, (%eax,%ecx,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%eax)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%ebp)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%ecx,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%ebp,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12(%eax,%ecx,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%eax)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%ebp)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%ecx,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%ebp,%eax,1)");
	यंत्र अस्थिर("bndstx %bnd0, 0x12345678(%eax,%ecx,1)");

	/* bnd prefix on call, ret, jmp and all jcc */

	यंत्र अस्थिर("bnd call label1");  /* Expecting: call unconditional 0xfffffffc */
	यंत्र अस्थिर("bnd call *(%eax)"); /* Expecting: call indirect      0 */
	यंत्र अस्थिर("bnd ret");          /* Expecting: ret  indirect      0 */
	यंत्र अस्थिर("bnd jmp label1");   /* Expecting: jmp  unconditional 0xfffffffc */
	यंत्र अस्थिर("bnd jmp label1");   /* Expecting: jmp  unconditional 0xfffffffc */
	यंत्र अस्थिर("bnd jmp *(%ecx)");  /* Expecting: jmp  indirect      0 */
	यंत्र अस्थिर("bnd jne label1");   /* Expecting: jcc  conditional   0xfffffffc */

	/* sha1rnds4 imm8, xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1rnds4 $0x0, %xmm1, %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, %xmm7, %xmm2");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%eax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%eax), %xmm3");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1rnds4 $0x91, 0x12345678(%eax,%ecx,8), %xmm0");

	/* sha1nexte xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1nexte %xmm1, %xmm0");
	यंत्र अस्थिर("sha1nexte %xmm7, %xmm2");
	यंत्र अस्थिर("sha1nexte (%eax), %xmm0");
	यंत्र अस्थिर("sha1nexte (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1nexte (%eax), %xmm3");
	यंत्र अस्थिर("sha1nexte (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1nexte 0x12345678(%eax,%ecx,8), %xmm0");

	/* sha1msg1 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1msg1 %xmm1, %xmm0");
	यंत्र अस्थिर("sha1msg1 %xmm7, %xmm2");
	यंत्र अस्थिर("sha1msg1 (%eax), %xmm0");
	यंत्र अस्थिर("sha1msg1 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%eax), %xmm3");
	यंत्र अस्थिर("sha1msg1 (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg1 0x12345678(%eax,%ecx,8), %xmm0");

	/* sha1msg2 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha1msg2 %xmm1, %xmm0");
	यंत्र अस्थिर("sha1msg2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha1msg2 (%eax), %xmm0");
	यंत्र अस्थिर("sha1msg2 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%eax), %xmm3");
	यंत्र अस्थिर("sha1msg2 (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha1msg2 0x12345678(%eax,%ecx,8), %xmm0");

	/* sha256rnds2 <XMM0>, xmm2/m128, xmm1 */
	/* Note sha256rnds2 has an implicit opeअक्रम 'xmm0' */

	यंत्र अस्थिर("sha256rnds2 %xmm4, %xmm1");
	यंत्र अस्थिर("sha256rnds2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256rnds2 (%eax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (0x12345678), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%eax), %xmm3");
	यंत्र अस्थिर("sha256rnds2 (%ecx,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%eax,%ecx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 (%eax,%ecx,8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%eax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%ebp), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%ecx,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%ebp,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%eax,%ecx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12(%eax,%ecx,8), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%eax), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%ebp), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%ecx,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%ebp,%eax,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%eax,%ecx,1), %xmm1");
	यंत्र अस्थिर("sha256rnds2 0x12345678(%eax,%ecx,8), %xmm1");

	/* sha256msg1 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha256msg1 %xmm1, %xmm0");
	यंत्र अस्थिर("sha256msg1 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256msg1 (%eax), %xmm0");
	यंत्र अस्थिर("sha256msg1 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%eax), %xmm3");
	यंत्र अस्थिर("sha256msg1 (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg1 0x12345678(%eax,%ecx,8), %xmm0");

	/* sha256msg2 xmm2/m128, xmm1 */

	यंत्र अस्थिर("sha256msg2 %xmm1, %xmm0");
	यंत्र अस्थिर("sha256msg2 %xmm7, %xmm2");
	यंत्र अस्थिर("sha256msg2 (%eax), %xmm0");
	यंत्र अस्थिर("sha256msg2 (0x12345678), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%eax), %xmm3");
	यंत्र अस्थिर("sha256msg2 (%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 (%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%eax), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%ebp), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12(%eax,%ecx,8), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%eax), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%ebp), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%ecx,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%ebp,%eax,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%eax,%ecx,1), %xmm0");
	यंत्र अस्थिर("sha256msg2 0x12345678(%eax,%ecx,8), %xmm0");

	/* clflushopt m8 */

	यंत्र अस्थिर("clflushopt (%eax)");
	यंत्र अस्थिर("clflushopt (0x12345678)");
	यंत्र अस्थिर("clflushopt 0x12345678(%eax,%ecx,8)");
	/* Also check inकाष्ठाions in the same group encoding as clflushopt */
	यंत्र अस्थिर("clflush (%eax)");
	यंत्र अस्थिर("sfence");

	/* clwb m8 */

	यंत्र अस्थिर("clwb (%eax)");
	यंत्र अस्थिर("clwb (0x12345678)");
	यंत्र अस्थिर("clwb 0x12345678(%eax,%ecx,8)");
	/* Also check inकाष्ठाions in the same group encoding as clwb */
	यंत्र अस्थिर("xsaveopt (%eax)");
	यंत्र अस्थिर("mfence");

	/* cldemote m8 */

	यंत्र अस्थिर("cldemote (%eax)");
	यंत्र अस्थिर("cldemote (0x12345678)");
	यंत्र अस्थिर("cldemote 0x12345678(%eax,%ecx,8)");

	/* xsavec mem */

	यंत्र अस्थिर("xsavec (%eax)");
	यंत्र अस्थिर("xsavec (0x12345678)");
	यंत्र अस्थिर("xsavec 0x12345678(%eax,%ecx,8)");

	/* xsaves mem */

	यंत्र अस्थिर("xsaves (%eax)");
	यंत्र अस्थिर("xsaves (0x12345678)");
	यंत्र अस्थिर("xsaves 0x12345678(%eax,%ecx,8)");

	/* xrstors mem */

	यंत्र अस्थिर("xrstors (%eax)");
	यंत्र अस्थिर("xrstors (0x12345678)");
	यंत्र अस्थिर("xrstors 0x12345678(%eax,%ecx,8)");

	/* ptग_लिखो */

	यंत्र अस्थिर("ptwrite (%eax)");
	यंत्र अस्थिर("ptwrite (0x12345678)");
	यंत्र अस्थिर("ptwrite 0x12345678(%eax,%ecx,8)");

	यंत्र अस्थिर("ptwritel (%eax)");
	यंत्र अस्थिर("ptwritel (0x12345678)");
	यंत्र अस्थिर("ptwritel 0x12345678(%eax,%ecx,8)");

	/* tछोड़ो */

	यंत्र अस्थिर("tpause %ebx");

	/* umonitor */

	यंत्र अस्थिर("umonitor %ax");
	यंत्र अस्थिर("umonitor %eax");

	/* umरुको */

	यंत्र अस्थिर("umwait %eax");

	/* movdiri */

	यंत्र अस्थिर("movdiri %eax,(%ebx)");
	यंत्र अस्थिर("movdiri %ecx,0x12345678(%eax)");

	/* movdir64b */

	यंत्र अस्थिर("movdir64b (%eax),%ebx");
	यंत्र अस्थिर("movdir64b 0x12345678(%eax),%ecx");
	यंत्र अस्थिर("movdir64b (%si),%bx");
	यंत्र अस्थिर("movdir64b 0x1234(%si),%cx");

	/* enqcmd */

	यंत्र अस्थिर("enqcmd (%eax),%ebx");
	यंत्र अस्थिर("enqcmd 0x12345678(%eax),%ecx");
	यंत्र अस्थिर("enqcmd (%si),%bx");
	यंत्र अस्थिर("enqcmd 0x1234(%si),%cx");

	/* enqcmds */

	यंत्र अस्थिर("enqcmds (%eax),%ebx");
	यंत्र अस्थिर("enqcmds 0x12345678(%eax),%ecx");
	यंत्र अस्थिर("enqcmds (%si),%bx");
	यंत्र अस्थिर("enqcmds 0x1234(%si),%cx");

	/* incsspd */

	यंत्र अस्थिर("incsspd %eax");
	/* Also check inकाष्ठाions in the same group encoding as incsspd */
	यंत्र अस्थिर("xrstor (%eax)");
	यंत्र अस्थिर("xrstor (0x12345678)");
	यंत्र अस्थिर("xrstor 0x12345678(%eax,%ecx,8)");
	यंत्र अस्थिर("lfence");

	/* rdsspd */

	यंत्र अस्थिर("rdsspd %eax");

	/* saveprevssp */

	यंत्र अस्थिर("saveprevssp");

	/* rstorssp */

	यंत्र अस्थिर("rstorssp (%eax)");
	यंत्र अस्थिर("rstorssp (0x12345678)");
	यंत्र अस्थिर("rstorssp 0x12345678(%eax,%ecx,8)");

	/* wrssd */

	यंत्र अस्थिर("wrssd %ecx,(%eax)");
	यंत्र अस्थिर("wrssd %edx,(0x12345678)");
	यंत्र अस्थिर("wrssd %edx,0x12345678(%eax,%ecx,8)");

	/* wrussd */

	यंत्र अस्थिर("wrussd %ecx,(%eax)");
	यंत्र अस्थिर("wrussd %edx,(0x12345678)");
	यंत्र अस्थिर("wrussd %edx,0x12345678(%eax,%ecx,8)");

	/* setssbsy */

	यंत्र अस्थिर("setssbsy");
	/* Also check inकाष्ठाions in the same group encoding as setssbsy */
	यंत्र अस्थिर("rdpkru");
	यंत्र अस्थिर("wrpkru");

	/* clrssbsy */

	यंत्र अस्थिर("clrssbsy (%eax)");
	यंत्र अस्थिर("clrssbsy (0x12345678)");
	यंत्र अस्थिर("clrssbsy 0x12345678(%eax,%ecx,8)");

	/* endbr32/64 */

	यंत्र अस्थिर("endbr32");
	यंत्र अस्थिर("endbr64");

	/* call with/without notrack prefix */

	यंत्र अस्थिर("call *%eax");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("call *(%eax)");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("call *(0x12345678)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("call *0x12345678(%eax,%ecx,8)");		/* Expecting: call indirect 0 */

	यंत्र अस्थिर("bnd call *%eax");				/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd call *(%eax)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd call *(0x12345678)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("bnd call *0x12345678(%eax,%ecx,8)");	/* Expecting: call indirect 0 */

	यंत्र अस्थिर("notrack call *%eax");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack call *(%eax)");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack call *(0x12345678)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack call *0x12345678(%eax,%ecx,8)");	/* Expecting: call indirect 0 */

	यंत्र अस्थिर("notrack bnd call *%eax");			/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd call *(%eax)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd call *(0x12345678)");		/* Expecting: call indirect 0 */
	यंत्र अस्थिर("notrack bnd call *0x12345678(%eax,%ecx,8)"); /* Expecting: call indirect 0 */

	/* jmp with/without notrack prefix */

	यंत्र अस्थिर("jmp *%eax");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmp *(%eax)");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmp *(0x12345678)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("jmp *0x12345678(%eax,%ecx,8)");		/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("bnd jmp *%eax");				/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmp *(%eax)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmp *(0x12345678)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("bnd jmp *0x12345678(%eax,%ecx,8)");	/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("notrack jmp *%eax");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmp *(%eax)");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmp *(0x12345678)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack jmp *0x12345678(%eax,%ecx,8)");	/* Expecting: jmp indirect 0 */

	यंत्र अस्थिर("notrack bnd jmp *%eax");			/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmp *(%eax)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmp *(0x12345678)");		/* Expecting: jmp indirect 0 */
	यंत्र अस्थिर("notrack bnd jmp *0x12345678(%eax,%ecx,8)"); /* Expecting: jmp indirect 0 */

#पूर्ण_अगर /* #अगर_अघोषित __x86_64__ */

	/* SGX */

	यंत्र अस्थिर("encls");
	यंत्र अस्थिर("enclu");
	यंत्र अस्थिर("enclv");

	/* pconfig */

	यंत्र अस्थिर("pconfig");

	/* wbnoinvd */

	यंत्र अस्थिर("wbnoinvd");

	/* Following line is a marker क्रम the awk script - करो not change */
	यंत्र अस्थिर("rdtsc"); /* Stop here */

	वापस 0;
पूर्ण
