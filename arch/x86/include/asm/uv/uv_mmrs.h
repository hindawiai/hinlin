<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * HPE UV MMR definitions
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2007-2016 Silicon Graphics, Inc. All rights reserved.
 */

#अगर_अघोषित _ASM_X86_UV_UV_MMRS_H
#घोषणा _ASM_X86_UV_UV_MMRS_H

/*
 * This file contains MMR definitions क्रम all UV hubs types.
 *
 * To minimize coding dअगरferences between hub types, the symbols are
 * grouped by architecture types.
 *
 * UVH  - definitions common to all UV hub types.
 * UVXH - definitions common to UVX class (2, 3, 4).
 * UVYH - definitions common to UVY class (5).
 * UV5H - definitions specअगरic to UV type 5 hub.
 * UV4AH - definitions specअगरic to UV type 4A hub.
 * UV4H - definitions specअगरic to UV type 4 hub.
 * UV3H - definitions specअगरic to UV type 3 hub.
 * UV2H - definitions specअगरic to UV type 2 hub.
 *
 * If the MMR exists on all hub types but have dअगरferent addresses,
 * use a conditional चालक to define the value at runसमय.  Any
 * that are not defined are blank.
 *	(UV4A variations only generated अगर dअगरferent from uv4)
 *	#घोषणा UVHxxx (
 *		is_uv(UV5) ? UV5Hxxx value :
 *		is_uv(UV4A) ? UV4AHxxx value :
 *		is_uv(UV4) ? UV4Hxxx value :
 *		is_uv(UV3) ? UV3Hxxx value :
 *		is_uv(UV2) ? UV2Hxxx value :
 *		<ucv> or <undef value>)
 *
 * Class UVX has UVs (2|3|4|4A).
 * Class UVY has UVs (5).
 *
 *	जोड़ uvh_xxx अणु
 *		अचिन्हित दीर्घ       v;
 *		काष्ठा uvh_xxx_s अणु	 # Common fields only
 *		पूर्ण s;
 *		काष्ठा uv5h_xxx_s अणु	 # Full UV5 definition (*)
 *		पूर्ण s5;
 *		काष्ठा uv4ah_xxx_s अणु	 # Full UV4A definition (*)
 *		पूर्ण s4a;
 *		काष्ठा uv4h_xxx_s अणु	 # Full UV4 definition (*)
 *		पूर्ण s4;
 *		काष्ठा uv3h_xxx_s अणु	 # Full UV3 definition (*)
 *		पूर्ण s3;
 *		काष्ठा uv2h_xxx_s अणु	 # Full UV2 definition (*)
 *		पूर्ण s2;
 *	पूर्ण;
 *		(* - अगर present and dअगरferent than the common काष्ठा)
 *
 * Only essential dअगरferences are क्रमागतerated. For example, अगर the address is
 * the same क्रम all UV's, only a single #घोषणा is generated. Likewise,
 * अगर the contents is the same क्रम all hubs, only the "s" काष्ठाure is
 * generated.
 *
 * (GEN Flags: undefs=function)
 */

 /* UV bit masks */
#घोषणा	UV2	(1 << 0)
#घोषणा	UV3	(1 << 1)
#घोषणा	UV4	(1 << 2)
#घोषणा	UV4A	(1 << 3)
#घोषणा	UV5	(1 << 4)
#घोषणा	UVX	(UV2|UV3|UV4)
#घोषणा	UVY	(UV5)
#घोषणा	UV_ANY	(~0)




#घोषणा UV_MMR_ENABLE		(1UL << 63)

#घोषणा UV1_HUB_PART_NUMBER	0x88a5
#घोषणा UV2_HUB_PART_NUMBER	0x8eb8
#घोषणा UV2_HUB_PART_NUMBER_X	0x1111
#घोषणा UV3_HUB_PART_NUMBER	0x9578
#घोषणा UV3_HUB_PART_NUMBER_X	0x4321
#घोषणा UV4_HUB_PART_NUMBER	0x99a1
#घोषणा UV5_HUB_PART_NUMBER	0xa171

/* Error function to catch undefined references */
बाह्य अचिन्हित दीर्घ uv_undefined(अक्षर *str);

/* ========================================================================= */
/*                           UVH_EVENT_OCCURRED0                             */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED0 0x70000UL

/* UVH common defines*/
#घोषणा UVH_EVENT_OCCURRED0_LB_HCERR_SHFT		0
#घोषणा UVH_EVENT_OCCURRED0_LB_HCERR_MASK		0x0000000000000001UL

/* UVXH common defines */
#घोषणा UVXH_EVENT_OCCURRED0_RH_HCERR_SHFT		2
#घोषणा UVXH_EVENT_OCCURRED0_RH_HCERR_MASK		0x0000000000000004UL
#घोषणा UVXH_EVENT_OCCURRED0_LH0_HCERR_SHFT		3
#घोषणा UVXH_EVENT_OCCURRED0_LH0_HCERR_MASK		0x0000000000000008UL
#घोषणा UVXH_EVENT_OCCURRED0_LH1_HCERR_SHFT		4
#घोषणा UVXH_EVENT_OCCURRED0_LH1_HCERR_MASK		0x0000000000000010UL
#घोषणा UVXH_EVENT_OCCURRED0_GR0_HCERR_SHFT		5
#घोषणा UVXH_EVENT_OCCURRED0_GR0_HCERR_MASK		0x0000000000000020UL
#घोषणा UVXH_EVENT_OCCURRED0_GR1_HCERR_SHFT		6
#घोषणा UVXH_EVENT_OCCURRED0_GR1_HCERR_MASK		0x0000000000000040UL
#घोषणा UVXH_EVENT_OCCURRED0_NI0_HCERR_SHFT		7
#घोषणा UVXH_EVENT_OCCURRED0_NI0_HCERR_MASK		0x0000000000000080UL
#घोषणा UVXH_EVENT_OCCURRED0_NI1_HCERR_SHFT		8
#घोषणा UVXH_EVENT_OCCURRED0_NI1_HCERR_MASK		0x0000000000000100UL
#घोषणा UVXH_EVENT_OCCURRED0_LB_AOERR0_SHFT		9
#घोषणा UVXH_EVENT_OCCURRED0_LB_AOERR0_MASK		0x0000000000000200UL
#घोषणा UVXH_EVENT_OCCURRED0_RH_AOERR0_SHFT		11
#घोषणा UVXH_EVENT_OCCURRED0_RH_AOERR0_MASK		0x0000000000000800UL
#घोषणा UVXH_EVENT_OCCURRED0_LH0_AOERR0_SHFT		12
#घोषणा UVXH_EVENT_OCCURRED0_LH0_AOERR0_MASK		0x0000000000001000UL
#घोषणा UVXH_EVENT_OCCURRED0_LH1_AOERR0_SHFT		13
#घोषणा UVXH_EVENT_OCCURRED0_LH1_AOERR0_MASK		0x0000000000002000UL
#घोषणा UVXH_EVENT_OCCURRED0_GR0_AOERR0_SHFT		14
#घोषणा UVXH_EVENT_OCCURRED0_GR0_AOERR0_MASK		0x0000000000004000UL
#घोषणा UVXH_EVENT_OCCURRED0_GR1_AOERR0_SHFT		15
#घोषणा UVXH_EVENT_OCCURRED0_GR1_AOERR0_MASK		0x0000000000008000UL
#घोषणा UVXH_EVENT_OCCURRED0_XB_AOERR0_SHFT		16
#घोषणा UVXH_EVENT_OCCURRED0_XB_AOERR0_MASK		0x0000000000010000UL

/* UVYH common defines */
#घोषणा UVYH_EVENT_OCCURRED0_KT_HCERR_SHFT		1
#घोषणा UVYH_EVENT_OCCURRED0_KT_HCERR_MASK		0x0000000000000002UL
#घोषणा UVYH_EVENT_OCCURRED0_RH0_HCERR_SHFT		2
#घोषणा UVYH_EVENT_OCCURRED0_RH0_HCERR_MASK		0x0000000000000004UL
#घोषणा UVYH_EVENT_OCCURRED0_RH1_HCERR_SHFT		3
#घोषणा UVYH_EVENT_OCCURRED0_RH1_HCERR_MASK		0x0000000000000008UL
#घोषणा UVYH_EVENT_OCCURRED0_LH0_HCERR_SHFT		4
#घोषणा UVYH_EVENT_OCCURRED0_LH0_HCERR_MASK		0x0000000000000010UL
#घोषणा UVYH_EVENT_OCCURRED0_LH1_HCERR_SHFT		5
#घोषणा UVYH_EVENT_OCCURRED0_LH1_HCERR_MASK		0x0000000000000020UL
#घोषणा UVYH_EVENT_OCCURRED0_LH2_HCERR_SHFT		6
#घोषणा UVYH_EVENT_OCCURRED0_LH2_HCERR_MASK		0x0000000000000040UL
#घोषणा UVYH_EVENT_OCCURRED0_LH3_HCERR_SHFT		7
#घोषणा UVYH_EVENT_OCCURRED0_LH3_HCERR_MASK		0x0000000000000080UL
#घोषणा UVYH_EVENT_OCCURRED0_XB_HCERR_SHFT		8
#घोषणा UVYH_EVENT_OCCURRED0_XB_HCERR_MASK		0x0000000000000100UL
#घोषणा UVYH_EVENT_OCCURRED0_RDM_HCERR_SHFT		9
#घोषणा UVYH_EVENT_OCCURRED0_RDM_HCERR_MASK		0x0000000000000200UL
#घोषणा UVYH_EVENT_OCCURRED0_NI0_HCERR_SHFT		10
#घोषणा UVYH_EVENT_OCCURRED0_NI0_HCERR_MASK		0x0000000000000400UL
#घोषणा UVYH_EVENT_OCCURRED0_NI1_HCERR_SHFT		11
#घोषणा UVYH_EVENT_OCCURRED0_NI1_HCERR_MASK		0x0000000000000800UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_AOERR0_SHFT		12
#घोषणा UVYH_EVENT_OCCURRED0_LB_AOERR0_MASK		0x0000000000001000UL
#घोषणा UVYH_EVENT_OCCURRED0_KT_AOERR0_SHFT		13
#घोषणा UVYH_EVENT_OCCURRED0_KT_AOERR0_MASK		0x0000000000002000UL
#घोषणा UVYH_EVENT_OCCURRED0_RH0_AOERR0_SHFT		14
#घोषणा UVYH_EVENT_OCCURRED0_RH0_AOERR0_MASK		0x0000000000004000UL
#घोषणा UVYH_EVENT_OCCURRED0_RH1_AOERR0_SHFT		15
#घोषणा UVYH_EVENT_OCCURRED0_RH1_AOERR0_MASK		0x0000000000008000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH0_AOERR0_SHFT		16
#घोषणा UVYH_EVENT_OCCURRED0_LH0_AOERR0_MASK		0x0000000000010000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH1_AOERR0_SHFT		17
#घोषणा UVYH_EVENT_OCCURRED0_LH1_AOERR0_MASK		0x0000000000020000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH2_AOERR0_SHFT		18
#घोषणा UVYH_EVENT_OCCURRED0_LH2_AOERR0_MASK		0x0000000000040000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH3_AOERR0_SHFT		19
#घोषणा UVYH_EVENT_OCCURRED0_LH3_AOERR0_MASK		0x0000000000080000UL
#घोषणा UVYH_EVENT_OCCURRED0_XB_AOERR0_SHFT		20
#घोषणा UVYH_EVENT_OCCURRED0_XB_AOERR0_MASK		0x0000000000100000UL
#घोषणा UVYH_EVENT_OCCURRED0_RDM_AOERR0_SHFT		21
#घोषणा UVYH_EVENT_OCCURRED0_RDM_AOERR0_MASK		0x0000000000200000UL
#घोषणा UVYH_EVENT_OCCURRED0_RT0_AOERR0_SHFT		22
#घोषणा UVYH_EVENT_OCCURRED0_RT0_AOERR0_MASK		0x0000000000400000UL
#घोषणा UVYH_EVENT_OCCURRED0_RT1_AOERR0_SHFT		23
#घोषणा UVYH_EVENT_OCCURRED0_RT1_AOERR0_MASK		0x0000000000800000UL
#घोषणा UVYH_EVENT_OCCURRED0_NI0_AOERR0_SHFT		24
#घोषणा UVYH_EVENT_OCCURRED0_NI0_AOERR0_MASK		0x0000000001000000UL
#घोषणा UVYH_EVENT_OCCURRED0_NI1_AOERR0_SHFT		25
#घोषणा UVYH_EVENT_OCCURRED0_NI1_AOERR0_MASK		0x0000000002000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_AOERR1_SHFT		26
#घोषणा UVYH_EVENT_OCCURRED0_LB_AOERR1_MASK		0x0000000004000000UL
#घोषणा UVYH_EVENT_OCCURRED0_KT_AOERR1_SHFT		27
#घोषणा UVYH_EVENT_OCCURRED0_KT_AOERR1_MASK		0x0000000008000000UL
#घोषणा UVYH_EVENT_OCCURRED0_RH0_AOERR1_SHFT		28
#घोषणा UVYH_EVENT_OCCURRED0_RH0_AOERR1_MASK		0x0000000010000000UL
#घोषणा UVYH_EVENT_OCCURRED0_RH1_AOERR1_SHFT		29
#घोषणा UVYH_EVENT_OCCURRED0_RH1_AOERR1_MASK		0x0000000020000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH0_AOERR1_SHFT		30
#घोषणा UVYH_EVENT_OCCURRED0_LH0_AOERR1_MASK		0x0000000040000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH1_AOERR1_SHFT		31
#घोषणा UVYH_EVENT_OCCURRED0_LH1_AOERR1_MASK		0x0000000080000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH2_AOERR1_SHFT		32
#घोषणा UVYH_EVENT_OCCURRED0_LH2_AOERR1_MASK		0x0000000100000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LH3_AOERR1_SHFT		33
#घोषणा UVYH_EVENT_OCCURRED0_LH3_AOERR1_MASK		0x0000000200000000UL
#घोषणा UVYH_EVENT_OCCURRED0_XB_AOERR1_SHFT		34
#घोषणा UVYH_EVENT_OCCURRED0_XB_AOERR1_MASK		0x0000000400000000UL
#घोषणा UVYH_EVENT_OCCURRED0_RDM_AOERR1_SHFT		35
#घोषणा UVYH_EVENT_OCCURRED0_RDM_AOERR1_MASK		0x0000000800000000UL
#घोषणा UVYH_EVENT_OCCURRED0_RT0_AOERR1_SHFT		36
#घोषणा UVYH_EVENT_OCCURRED0_RT0_AOERR1_MASK		0x0000001000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_RT1_AOERR1_SHFT		37
#घोषणा UVYH_EVENT_OCCURRED0_RT1_AOERR1_MASK		0x0000002000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_NI0_AOERR1_SHFT		38
#घोषणा UVYH_EVENT_OCCURRED0_NI0_AOERR1_MASK		0x0000004000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_NI1_AOERR1_SHFT		39
#घोषणा UVYH_EVENT_OCCURRED0_NI1_AOERR1_MASK		0x0000008000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_SHFT	40
#घोषणा UVYH_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_MASK	0x0000010000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_0_SHFT		41
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_0_MASK		0x0000020000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_1_SHFT		42
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_1_MASK		0x0000040000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_2_SHFT		43
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_2_MASK		0x0000080000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_3_SHFT		44
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_3_MASK		0x0000100000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_4_SHFT		45
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_4_MASK		0x0000200000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_5_SHFT		46
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_5_MASK		0x0000400000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_6_SHFT		47
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_6_MASK		0x0000800000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_7_SHFT		48
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_7_MASK		0x0001000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_8_SHFT		49
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_8_MASK		0x0002000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_9_SHFT		50
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_9_MASK		0x0004000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_10_SHFT		51
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_10_MASK		0x0008000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_11_SHFT		52
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_11_MASK		0x0010000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_12_SHFT		53
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_12_MASK		0x0020000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_13_SHFT		54
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_13_MASK		0x0040000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_14_SHFT		55
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_14_MASK		0x0080000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_15_SHFT		56
#घोषणा UVYH_EVENT_OCCURRED0_LB_IRQ_INT_15_MASK		0x0100000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_L1_NMI_INT_SHFT		57
#घोषणा UVYH_EVENT_OCCURRED0_L1_NMI_INT_MASK		0x0200000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_STOP_CLOCK_SHFT		58
#घोषणा UVYH_EVENT_OCCURRED0_STOP_CLOCK_MASK		0x0400000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_ASIC_TO_L1_SHFT		59
#घोषणा UVYH_EVENT_OCCURRED0_ASIC_TO_L1_MASK		0x0800000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_L1_TO_ASIC_SHFT		60
#घोषणा UVYH_EVENT_OCCURRED0_L1_TO_ASIC_MASK		0x1000000000000000UL
#घोषणा UVYH_EVENT_OCCURRED0_LA_SEQ_TRIGGER_SHFT	61
#घोषणा UVYH_EVENT_OCCURRED0_LA_SEQ_TRIGGER_MASK	0x2000000000000000UL

/* UV4 unique defines */
#घोषणा UV4H_EVENT_OCCURRED0_KT_HCERR_SHFT		1
#घोषणा UV4H_EVENT_OCCURRED0_KT_HCERR_MASK		0x0000000000000002UL
#घोषणा UV4H_EVENT_OCCURRED0_KT_AOERR0_SHFT		10
#घोषणा UV4H_EVENT_OCCURRED0_KT_AOERR0_MASK		0x0000000000000400UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ0_AOERR0_SHFT		17
#घोषणा UV4H_EVENT_OCCURRED0_RTQ0_AOERR0_MASK		0x0000000000020000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ1_AOERR0_SHFT		18
#घोषणा UV4H_EVENT_OCCURRED0_RTQ1_AOERR0_MASK		0x0000000000040000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ2_AOERR0_SHFT		19
#घोषणा UV4H_EVENT_OCCURRED0_RTQ2_AOERR0_MASK		0x0000000000080000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ3_AOERR0_SHFT		20
#घोषणा UV4H_EVENT_OCCURRED0_RTQ3_AOERR0_MASK		0x0000000000100000UL
#घोषणा UV4H_EVENT_OCCURRED0_NI0_AOERR0_SHFT		21
#घोषणा UV4H_EVENT_OCCURRED0_NI0_AOERR0_MASK		0x0000000000200000UL
#घोषणा UV4H_EVENT_OCCURRED0_NI1_AOERR0_SHFT		22
#घोषणा UV4H_EVENT_OCCURRED0_NI1_AOERR0_MASK		0x0000000000400000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_AOERR1_SHFT		23
#घोषणा UV4H_EVENT_OCCURRED0_LB_AOERR1_MASK		0x0000000000800000UL
#घोषणा UV4H_EVENT_OCCURRED0_KT_AOERR1_SHFT		24
#घोषणा UV4H_EVENT_OCCURRED0_KT_AOERR1_MASK		0x0000000001000000UL
#घोषणा UV4H_EVENT_OCCURRED0_RH_AOERR1_SHFT		25
#घोषणा UV4H_EVENT_OCCURRED0_RH_AOERR1_MASK		0x0000000002000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LH0_AOERR1_SHFT		26
#घोषणा UV4H_EVENT_OCCURRED0_LH0_AOERR1_MASK		0x0000000004000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LH1_AOERR1_SHFT		27
#घोषणा UV4H_EVENT_OCCURRED0_LH1_AOERR1_MASK		0x0000000008000000UL
#घोषणा UV4H_EVENT_OCCURRED0_GR0_AOERR1_SHFT		28
#घोषणा UV4H_EVENT_OCCURRED0_GR0_AOERR1_MASK		0x0000000010000000UL
#घोषणा UV4H_EVENT_OCCURRED0_GR1_AOERR1_SHFT		29
#घोषणा UV4H_EVENT_OCCURRED0_GR1_AOERR1_MASK		0x0000000020000000UL
#घोषणा UV4H_EVENT_OCCURRED0_XB_AOERR1_SHFT		30
#घोषणा UV4H_EVENT_OCCURRED0_XB_AOERR1_MASK		0x0000000040000000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ0_AOERR1_SHFT		31
#घोषणा UV4H_EVENT_OCCURRED0_RTQ0_AOERR1_MASK		0x0000000080000000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ1_AOERR1_SHFT		32
#घोषणा UV4H_EVENT_OCCURRED0_RTQ1_AOERR1_MASK		0x0000000100000000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ2_AOERR1_SHFT		33
#घोषणा UV4H_EVENT_OCCURRED0_RTQ2_AOERR1_MASK		0x0000000200000000UL
#घोषणा UV4H_EVENT_OCCURRED0_RTQ3_AOERR1_SHFT		34
#घोषणा UV4H_EVENT_OCCURRED0_RTQ3_AOERR1_MASK		0x0000000400000000UL
#घोषणा UV4H_EVENT_OCCURRED0_NI0_AOERR1_SHFT		35
#घोषणा UV4H_EVENT_OCCURRED0_NI0_AOERR1_MASK		0x0000000800000000UL
#घोषणा UV4H_EVENT_OCCURRED0_NI1_AOERR1_SHFT		36
#घोषणा UV4H_EVENT_OCCURRED0_NI1_AOERR1_MASK		0x0000001000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_SHFT	37
#घोषणा UV4H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_MASK	0x0000002000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_0_SHFT		38
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_0_MASK		0x0000004000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_1_SHFT		39
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_1_MASK		0x0000008000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_2_SHFT		40
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_2_MASK		0x0000010000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_3_SHFT		41
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_3_MASK		0x0000020000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_4_SHFT		42
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_4_MASK		0x0000040000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_5_SHFT		43
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_5_MASK		0x0000080000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_6_SHFT		44
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_6_MASK		0x0000100000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_7_SHFT		45
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_7_MASK		0x0000200000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_8_SHFT		46
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_8_MASK		0x0000400000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_9_SHFT		47
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_9_MASK		0x0000800000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_10_SHFT		48
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_10_MASK		0x0001000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_11_SHFT		49
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_11_MASK		0x0002000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_12_SHFT		50
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_12_MASK		0x0004000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_13_SHFT		51
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_13_MASK		0x0008000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_14_SHFT		52
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_14_MASK		0x0010000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_15_SHFT		53
#घोषणा UV4H_EVENT_OCCURRED0_LB_IRQ_INT_15_MASK		0x0020000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_L1_NMI_INT_SHFT		54
#घोषणा UV4H_EVENT_OCCURRED0_L1_NMI_INT_MASK		0x0040000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_STOP_CLOCK_SHFT		55
#घोषणा UV4H_EVENT_OCCURRED0_STOP_CLOCK_MASK		0x0080000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_ASIC_TO_L1_SHFT		56
#घोषणा UV4H_EVENT_OCCURRED0_ASIC_TO_L1_MASK		0x0100000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_L1_TO_ASIC_SHFT		57
#घोषणा UV4H_EVENT_OCCURRED0_L1_TO_ASIC_MASK		0x0200000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_SHFT	58
#घोषणा UV4H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_MASK	0x0400000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_IPI_INT_SHFT		59
#घोषणा UV4H_EVENT_OCCURRED0_IPI_INT_MASK		0x0800000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT0_SHFT		60
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT0_MASK		0x1000000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT1_SHFT		61
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT1_MASK		0x2000000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT2_SHFT		62
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT2_MASK		0x4000000000000000UL
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT3_SHFT		63
#घोषणा UV4H_EVENT_OCCURRED0_EXTIO_INT3_MASK		0x8000000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_EVENT_OCCURRED0_QP_HCERR_SHFT		1
#घोषणा UV3H_EVENT_OCCURRED0_QP_HCERR_MASK		0x0000000000000002UL
#घोषणा UV3H_EVENT_OCCURRED0_QP_AOERR0_SHFT		10
#घोषणा UV3H_EVENT_OCCURRED0_QP_AOERR0_MASK		0x0000000000000400UL
#घोषणा UV3H_EVENT_OCCURRED0_RT_AOERR0_SHFT		17
#घोषणा UV3H_EVENT_OCCURRED0_RT_AOERR0_MASK		0x0000000000020000UL
#घोषणा UV3H_EVENT_OCCURRED0_NI0_AOERR0_SHFT		18
#घोषणा UV3H_EVENT_OCCURRED0_NI0_AOERR0_MASK		0x0000000000040000UL
#घोषणा UV3H_EVENT_OCCURRED0_NI1_AOERR0_SHFT		19
#घोषणा UV3H_EVENT_OCCURRED0_NI1_AOERR0_MASK		0x0000000000080000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_AOERR1_SHFT		20
#घोषणा UV3H_EVENT_OCCURRED0_LB_AOERR1_MASK		0x0000000000100000UL
#घोषणा UV3H_EVENT_OCCURRED0_QP_AOERR1_SHFT		21
#घोषणा UV3H_EVENT_OCCURRED0_QP_AOERR1_MASK		0x0000000000200000UL
#घोषणा UV3H_EVENT_OCCURRED0_RH_AOERR1_SHFT		22
#घोषणा UV3H_EVENT_OCCURRED0_RH_AOERR1_MASK		0x0000000000400000UL
#घोषणा UV3H_EVENT_OCCURRED0_LH0_AOERR1_SHFT		23
#घोषणा UV3H_EVENT_OCCURRED0_LH0_AOERR1_MASK		0x0000000000800000UL
#घोषणा UV3H_EVENT_OCCURRED0_LH1_AOERR1_SHFT		24
#घोषणा UV3H_EVENT_OCCURRED0_LH1_AOERR1_MASK		0x0000000001000000UL
#घोषणा UV3H_EVENT_OCCURRED0_GR0_AOERR1_SHFT		25
#घोषणा UV3H_EVENT_OCCURRED0_GR0_AOERR1_MASK		0x0000000002000000UL
#घोषणा UV3H_EVENT_OCCURRED0_GR1_AOERR1_SHFT		26
#घोषणा UV3H_EVENT_OCCURRED0_GR1_AOERR1_MASK		0x0000000004000000UL
#घोषणा UV3H_EVENT_OCCURRED0_XB_AOERR1_SHFT		27
#घोषणा UV3H_EVENT_OCCURRED0_XB_AOERR1_MASK		0x0000000008000000UL
#घोषणा UV3H_EVENT_OCCURRED0_RT_AOERR1_SHFT		28
#घोषणा UV3H_EVENT_OCCURRED0_RT_AOERR1_MASK		0x0000000010000000UL
#घोषणा UV3H_EVENT_OCCURRED0_NI0_AOERR1_SHFT		29
#घोषणा UV3H_EVENT_OCCURRED0_NI0_AOERR1_MASK		0x0000000020000000UL
#घोषणा UV3H_EVENT_OCCURRED0_NI1_AOERR1_SHFT		30
#घोषणा UV3H_EVENT_OCCURRED0_NI1_AOERR1_MASK		0x0000000040000000UL
#घोषणा UV3H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_SHFT	31
#घोषणा UV3H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_MASK	0x0000000080000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_0_SHFT		32
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_0_MASK		0x0000000100000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_1_SHFT		33
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_1_MASK		0x0000000200000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_2_SHFT		34
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_2_MASK		0x0000000400000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_3_SHFT		35
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_3_MASK		0x0000000800000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_4_SHFT		36
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_4_MASK		0x0000001000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_5_SHFT		37
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_5_MASK		0x0000002000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_6_SHFT		38
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_6_MASK		0x0000004000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_7_SHFT		39
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_7_MASK		0x0000008000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_8_SHFT		40
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_8_MASK		0x0000010000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_9_SHFT		41
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_9_MASK		0x0000020000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_10_SHFT		42
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_10_MASK		0x0000040000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_11_SHFT		43
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_11_MASK		0x0000080000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_12_SHFT		44
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_12_MASK		0x0000100000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_13_SHFT		45
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_13_MASK		0x0000200000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_14_SHFT		46
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_14_MASK		0x0000400000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_15_SHFT		47
#घोषणा UV3H_EVENT_OCCURRED0_LB_IRQ_INT_15_MASK		0x0000800000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_L1_NMI_INT_SHFT		48
#घोषणा UV3H_EVENT_OCCURRED0_L1_NMI_INT_MASK		0x0001000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_STOP_CLOCK_SHFT		49
#घोषणा UV3H_EVENT_OCCURRED0_STOP_CLOCK_MASK		0x0002000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_ASIC_TO_L1_SHFT		50
#घोषणा UV3H_EVENT_OCCURRED0_ASIC_TO_L1_MASK		0x0004000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_L1_TO_ASIC_SHFT		51
#घोषणा UV3H_EVENT_OCCURRED0_L1_TO_ASIC_MASK		0x0008000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_SHFT	52
#घोषणा UV3H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_MASK	0x0010000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_IPI_INT_SHFT		53
#घोषणा UV3H_EVENT_OCCURRED0_IPI_INT_MASK		0x0020000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT0_SHFT		54
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT0_MASK		0x0040000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT1_SHFT		55
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT1_MASK		0x0080000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT2_SHFT		56
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT2_MASK		0x0100000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT3_SHFT		57
#घोषणा UV3H_EVENT_OCCURRED0_EXTIO_INT3_MASK		0x0200000000000000UL
#घोषणा UV3H_EVENT_OCCURRED0_PROखाता_INT_SHFT		58
#घोषणा UV3H_EVENT_OCCURRED0_PROखाता_INT_MASK		0x0400000000000000UL

/* UV2 unique defines */
#घोषणा UV2H_EVENT_OCCURRED0_QP_HCERR_SHFT		1
#घोषणा UV2H_EVENT_OCCURRED0_QP_HCERR_MASK		0x0000000000000002UL
#घोषणा UV2H_EVENT_OCCURRED0_QP_AOERR0_SHFT		10
#घोषणा UV2H_EVENT_OCCURRED0_QP_AOERR0_MASK		0x0000000000000400UL
#घोषणा UV2H_EVENT_OCCURRED0_RT_AOERR0_SHFT		17
#घोषणा UV2H_EVENT_OCCURRED0_RT_AOERR0_MASK		0x0000000000020000UL
#घोषणा UV2H_EVENT_OCCURRED0_NI0_AOERR0_SHFT		18
#घोषणा UV2H_EVENT_OCCURRED0_NI0_AOERR0_MASK		0x0000000000040000UL
#घोषणा UV2H_EVENT_OCCURRED0_NI1_AOERR0_SHFT		19
#घोषणा UV2H_EVENT_OCCURRED0_NI1_AOERR0_MASK		0x0000000000080000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_AOERR1_SHFT		20
#घोषणा UV2H_EVENT_OCCURRED0_LB_AOERR1_MASK		0x0000000000100000UL
#घोषणा UV2H_EVENT_OCCURRED0_QP_AOERR1_SHFT		21
#घोषणा UV2H_EVENT_OCCURRED0_QP_AOERR1_MASK		0x0000000000200000UL
#घोषणा UV2H_EVENT_OCCURRED0_RH_AOERR1_SHFT		22
#घोषणा UV2H_EVENT_OCCURRED0_RH_AOERR1_MASK		0x0000000000400000UL
#घोषणा UV2H_EVENT_OCCURRED0_LH0_AOERR1_SHFT		23
#घोषणा UV2H_EVENT_OCCURRED0_LH0_AOERR1_MASK		0x0000000000800000UL
#घोषणा UV2H_EVENT_OCCURRED0_LH1_AOERR1_SHFT		24
#घोषणा UV2H_EVENT_OCCURRED0_LH1_AOERR1_MASK		0x0000000001000000UL
#घोषणा UV2H_EVENT_OCCURRED0_GR0_AOERR1_SHFT		25
#घोषणा UV2H_EVENT_OCCURRED0_GR0_AOERR1_MASK		0x0000000002000000UL
#घोषणा UV2H_EVENT_OCCURRED0_GR1_AOERR1_SHFT		26
#घोषणा UV2H_EVENT_OCCURRED0_GR1_AOERR1_MASK		0x0000000004000000UL
#घोषणा UV2H_EVENT_OCCURRED0_XB_AOERR1_SHFT		27
#घोषणा UV2H_EVENT_OCCURRED0_XB_AOERR1_MASK		0x0000000008000000UL
#घोषणा UV2H_EVENT_OCCURRED0_RT_AOERR1_SHFT		28
#घोषणा UV2H_EVENT_OCCURRED0_RT_AOERR1_MASK		0x0000000010000000UL
#घोषणा UV2H_EVENT_OCCURRED0_NI0_AOERR1_SHFT		29
#घोषणा UV2H_EVENT_OCCURRED0_NI0_AOERR1_MASK		0x0000000020000000UL
#घोषणा UV2H_EVENT_OCCURRED0_NI1_AOERR1_SHFT		30
#घोषणा UV2H_EVENT_OCCURRED0_NI1_AOERR1_MASK		0x0000000040000000UL
#घोषणा UV2H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_SHFT	31
#घोषणा UV2H_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_MASK	0x0000000080000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_0_SHFT		32
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_0_MASK		0x0000000100000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_1_SHFT		33
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_1_MASK		0x0000000200000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_2_SHFT		34
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_2_MASK		0x0000000400000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_3_SHFT		35
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_3_MASK		0x0000000800000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_4_SHFT		36
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_4_MASK		0x0000001000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_5_SHFT		37
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_5_MASK		0x0000002000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_6_SHFT		38
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_6_MASK		0x0000004000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_7_SHFT		39
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_7_MASK		0x0000008000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_8_SHFT		40
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_8_MASK		0x0000010000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_9_SHFT		41
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_9_MASK		0x0000020000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_10_SHFT		42
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_10_MASK		0x0000040000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_11_SHFT		43
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_11_MASK		0x0000080000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_12_SHFT		44
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_12_MASK		0x0000100000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_13_SHFT		45
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_13_MASK		0x0000200000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_14_SHFT		46
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_14_MASK		0x0000400000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_15_SHFT		47
#घोषणा UV2H_EVENT_OCCURRED0_LB_IRQ_INT_15_MASK		0x0000800000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_L1_NMI_INT_SHFT		48
#घोषणा UV2H_EVENT_OCCURRED0_L1_NMI_INT_MASK		0x0001000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_STOP_CLOCK_SHFT		49
#घोषणा UV2H_EVENT_OCCURRED0_STOP_CLOCK_MASK		0x0002000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_ASIC_TO_L1_SHFT		50
#घोषणा UV2H_EVENT_OCCURRED0_ASIC_TO_L1_MASK		0x0004000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_L1_TO_ASIC_SHFT		51
#घोषणा UV2H_EVENT_OCCURRED0_L1_TO_ASIC_MASK		0x0008000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_SHFT	52
#घोषणा UV2H_EVENT_OCCURRED0_LA_SEQ_TRIGGER_MASK	0x0010000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_IPI_INT_SHFT		53
#घोषणा UV2H_EVENT_OCCURRED0_IPI_INT_MASK		0x0020000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT0_SHFT		54
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT0_MASK		0x0040000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT1_SHFT		55
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT1_MASK		0x0080000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT2_SHFT		56
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT2_MASK		0x0100000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT3_SHFT		57
#घोषणा UV2H_EVENT_OCCURRED0_EXTIO_INT3_MASK		0x0200000000000000UL
#घोषणा UV2H_EVENT_OCCURRED0_PROखाता_INT_SHFT		58
#घोषणा UV2H_EVENT_OCCURRED0_PROखाता_INT_MASK		0x0400000000000000UL

#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT0_MASK (				\
	is_uv(UV4) ? 0x1000000000000000UL :				\
	is_uv(UV3) ? 0x0040000000000000UL :				\
	is_uv(UV2) ? 0x0040000000000000UL :				\
	0)
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT0_SHFT (				\
	is_uv(UV4) ? 60 :						\
	is_uv(UV3) ? 54 :						\
	is_uv(UV2) ? 54 :						\
	-1)

जोड़ uvh_event_occurred0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1:1;
		अचिन्हित दीर्घ	rh_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_10:1;
		अचिन्हित दीर्घ	rh_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_17_63:47;
	पूर्ण sx;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	kt_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh2_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh3_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	xb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rdm_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh2_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh3_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rdm_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh2_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh3_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rdm_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_0:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_1:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_2:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_3:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_4:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_5:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_6:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_7:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_8:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_9:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_10:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_11:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_12:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_13:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_14:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_15:1;		/* RW */
		अचिन्हित दीर्घ	l1_nmi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	stop_घड़ी:1;			/* RW */
		अचिन्हित दीर्घ	asic_to_l1:1;			/* RW */
		अचिन्हित दीर्घ	l1_to_asic:1;			/* RW */
		अचिन्हित दीर्घ	la_seq_trigger:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	kt_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh2_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh3_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	xb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rdm_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh2_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh3_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rdm_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh2_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh3_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rdm_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_0:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_1:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_2:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_3:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_4:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_5:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_6:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_7:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_8:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_9:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_10:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_11:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_12:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_13:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_14:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_15:1;		/* RW */
		अचिन्हित दीर्घ	l1_nmi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	stop_घड़ी:1;			/* RW */
		अचिन्हित दीर्घ	asic_to_l1:1;			/* RW */
		अचिन्हित दीर्घ	l1_to_asic:1;			/* RW */
		अचिन्हित दीर्घ	la_seq_trigger:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	kt_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rtq0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rtq1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rtq2_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rtq3_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	kt_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rtq0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rtq1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rtq2_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rtq3_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_0:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_1:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_2:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_3:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_4:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_5:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_6:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_7:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_8:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_9:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_10:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_11:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_12:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_13:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_14:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_15:1;		/* RW */
		अचिन्हित दीर्घ	l1_nmi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	stop_घड़ी:1;			/* RW */
		अचिन्हित दीर्घ	asic_to_l1:1;			/* RW */
		अचिन्हित दीर्घ	l1_to_asic:1;			/* RW */
		अचिन्हित दीर्घ	la_seq_trigger:1;		/* RW */
		अचिन्हित दीर्घ	ipi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक3:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	qp_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	qp_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	qp_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_0:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_1:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_2:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_3:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_4:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_5:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_6:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_7:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_8:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_9:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_10:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_11:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_12:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_13:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_14:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_15:1;		/* RW */
		अचिन्हित दीर्घ	l1_nmi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	stop_घड़ी:1;			/* RW */
		अचिन्हित दीर्घ	asic_to_l1:1;			/* RW */
		अचिन्हित दीर्घ	l1_to_asic:1;			/* RW */
		अचिन्हित दीर्घ	la_seq_trigger:1;		/* RW */
		अचिन्हित दीर्घ	ipi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	profile_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_59_63:5;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_event_occurred0_s अणु
		अचिन्हित दीर्घ	lb_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	qp_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	rh_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lh1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	gr1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni0_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	ni1_hcerr:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	qp_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	rt_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr0:1;			/* RW */
		अचिन्हित दीर्घ	lb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	qp_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rh_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	lh1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	xb_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	rt_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni0_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	ni1_aoerr1:1;			/* RW */
		अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_0:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_1:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_2:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_3:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_4:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_5:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_6:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_7:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_8:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_9:1;			/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_10:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_11:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_12:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_13:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_14:1;		/* RW */
		अचिन्हित दीर्घ	lb_irq_पूर्णांक_15:1;		/* RW */
		अचिन्हित दीर्घ	l1_nmi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	stop_घड़ी:1;			/* RW */
		अचिन्हित दीर्घ	asic_to_l1:1;			/* RW */
		अचिन्हित दीर्घ	l1_to_asic:1;			/* RW */
		अचिन्हित दीर्घ	la_seq_trigger:1;		/* RW */
		अचिन्हित दीर्घ	ipi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	profile_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_59_63:5;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                        UVH_EVENT_OCCURRED0_ALIAS                          */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED0_ALIAS 0x70008UL


/* ========================================================================= */
/*                           UVH_EVENT_OCCURRED1                             */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED1 0x70080UL



/* UVYH common defines */
#घोषणा UVYH_EVENT_OCCURRED1_IPI_INT_SHFT		0
#घोषणा UVYH_EVENT_OCCURRED1_IPI_INT_MASK		0x0000000000000001UL
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT0_SHFT		1
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT0_MASK		0x0000000000000002UL
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT1_SHFT		2
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT1_MASK		0x0000000000000004UL
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT2_SHFT		3
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT2_MASK		0x0000000000000008UL
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT3_SHFT		4
#घोषणा UVYH_EVENT_OCCURRED1_EXTIO_INT3_MASK		0x0000000000000010UL
#घोषणा UVYH_EVENT_OCCURRED1_PROखाता_INT_SHFT		5
#घोषणा UVYH_EVENT_OCCURRED1_PROखाता_INT_MASK		0x0000000000000020UL
#घोषणा UVYH_EVENT_OCCURRED1_BAU_DATA_SHFT		6
#घोषणा UVYH_EVENT_OCCURRED1_BAU_DATA_MASK		0x0000000000000040UL
#घोषणा UVYH_EVENT_OCCURRED1_PROC_GENERAL_SHFT		7
#घोषणा UVYH_EVENT_OCCURRED1_PROC_GENERAL_MASK		0x0000000000000080UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT0_SHFT		8
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT0_MASK		0x0000000000000100UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT1_SHFT		9
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT1_MASK		0x0000000000000200UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT2_SHFT		10
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT2_MASK		0x0000000000000400UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT3_SHFT		11
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT3_MASK		0x0000000000000800UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT4_SHFT		12
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT4_MASK		0x0000000000001000UL
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT5_SHFT		13
#घोषणा UVYH_EVENT_OCCURRED1_XH_TLB_INT5_MASK		0x0000000000002000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT0_SHFT		14
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT0_MASK		0x0000000000004000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT1_SHFT		15
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT1_MASK		0x0000000000008000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT2_SHFT		16
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT2_MASK		0x0000000000010000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT3_SHFT		17
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT3_MASK		0x0000000000020000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT4_SHFT		18
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT4_MASK		0x0000000000040000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT5_SHFT		19
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT5_MASK		0x0000000000080000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT6_SHFT		20
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT6_MASK		0x0000000000100000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT7_SHFT		21
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT7_MASK		0x0000000000200000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT8_SHFT		22
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT8_MASK		0x0000000000400000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT9_SHFT		23
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT9_MASK		0x0000000000800000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT10_SHFT		24
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT10_MASK		0x0000000001000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT11_SHFT		25
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT11_MASK		0x0000000002000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT12_SHFT		26
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT12_MASK		0x0000000004000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT13_SHFT		27
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT13_MASK		0x0000000008000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT14_SHFT		28
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT14_MASK		0x0000000010000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT15_SHFT		29
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT15_MASK		0x0000000020000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT16_SHFT		30
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT16_MASK		0x0000000040000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT17_SHFT		31
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT17_MASK		0x0000000080000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT18_SHFT		32
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT18_MASK		0x0000000100000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT19_SHFT		33
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT19_MASK		0x0000000200000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT20_SHFT		34
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT20_MASK		0x0000000400000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT21_SHFT		35
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT21_MASK		0x0000000800000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT22_SHFT		36
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT22_MASK		0x0000001000000000UL
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT23_SHFT		37
#घोषणा UVYH_EVENT_OCCURRED1_RDM_TLB_INT23_MASK		0x0000002000000000UL

/* UV4 unique defines */
#घोषणा UV4H_EVENT_OCCURRED1_PROखाता_INT_SHFT		0
#घोषणा UV4H_EVENT_OCCURRED1_PROखाता_INT_MASK		0x0000000000000001UL
#घोषणा UV4H_EVENT_OCCURRED1_BAU_DATA_SHFT		1
#घोषणा UV4H_EVENT_OCCURRED1_BAU_DATA_MASK		0x0000000000000002UL
#घोषणा UV4H_EVENT_OCCURRED1_PROC_GENERAL_SHFT		2
#घोषणा UV4H_EVENT_OCCURRED1_PROC_GENERAL_MASK		0x0000000000000004UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT0_SHFT		3
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT0_MASK		0x0000000000000008UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT1_SHFT		4
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT1_MASK		0x0000000000000010UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT2_SHFT		5
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT2_MASK		0x0000000000000020UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT3_SHFT		6
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT3_MASK		0x0000000000000040UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT4_SHFT		7
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT4_MASK		0x0000000000000080UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT5_SHFT		8
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT5_MASK		0x0000000000000100UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT6_SHFT		9
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT6_MASK		0x0000000000000200UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT7_SHFT		10
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT7_MASK		0x0000000000000400UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT8_SHFT		11
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT8_MASK		0x0000000000000800UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT9_SHFT		12
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT9_MASK		0x0000000000001000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT10_SHFT		13
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT10_MASK		0x0000000000002000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT11_SHFT		14
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT11_MASK		0x0000000000004000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT12_SHFT		15
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT12_MASK		0x0000000000008000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT13_SHFT		16
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT13_MASK		0x0000000000010000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT14_SHFT		17
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT14_MASK		0x0000000000020000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT15_SHFT		18
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT15_MASK		0x0000000000040000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT16_SHFT		19
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT16_MASK		0x0000000000080000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT17_SHFT		20
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT17_MASK		0x0000000000100000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT18_SHFT		21
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT18_MASK		0x0000000000200000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT19_SHFT		22
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT19_MASK		0x0000000000400000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT20_SHFT		23
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT20_MASK		0x0000000000800000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT21_SHFT		24
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT21_MASK		0x0000000001000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT22_SHFT		25
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT22_MASK		0x0000000002000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT23_SHFT		26
#घोषणा UV4H_EVENT_OCCURRED1_GR0_TLB_INT23_MASK		0x0000000004000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT0_SHFT		27
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT0_MASK		0x0000000008000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT1_SHFT		28
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT1_MASK		0x0000000010000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT2_SHFT		29
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT2_MASK		0x0000000020000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT3_SHFT		30
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT3_MASK		0x0000000040000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT4_SHFT		31
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT4_MASK		0x0000000080000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT5_SHFT		32
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT5_MASK		0x0000000100000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT6_SHFT		33
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT6_MASK		0x0000000200000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT7_SHFT		34
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT7_MASK		0x0000000400000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT8_SHFT		35
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT8_MASK		0x0000000800000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT9_SHFT		36
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT9_MASK		0x0000001000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT10_SHFT		37
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT10_MASK		0x0000002000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT11_SHFT		38
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT11_MASK		0x0000004000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT12_SHFT		39
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT12_MASK		0x0000008000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT13_SHFT		40
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT13_MASK		0x0000010000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT14_SHFT		41
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT14_MASK		0x0000020000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT15_SHFT		42
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT15_MASK		0x0000040000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT16_SHFT		43
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT16_MASK		0x0000080000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT17_SHFT		44
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT17_MASK		0x0000100000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT18_SHFT		45
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT18_MASK		0x0000200000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT19_SHFT		46
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT19_MASK		0x0000400000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT20_SHFT		47
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT20_MASK		0x0000800000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT21_SHFT		48
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT21_MASK		0x0001000000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT22_SHFT		49
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT22_MASK		0x0002000000000000UL
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT23_SHFT		50
#घोषणा UV4H_EVENT_OCCURRED1_GR1_TLB_INT23_MASK		0x0004000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_EVENT_OCCURRED1_BAU_DATA_SHFT		0
#घोषणा UV3H_EVENT_OCCURRED1_BAU_DATA_MASK		0x0000000000000001UL
#घोषणा UV3H_EVENT_OCCURRED1_POWER_MANAGEMENT_REQ_SHFT	1
#घोषणा UV3H_EVENT_OCCURRED1_POWER_MANAGEMENT_REQ_MASK	0x0000000000000002UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT0_SHFT 2
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT0_MASK 0x0000000000000004UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT1_SHFT 3
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT1_MASK 0x0000000000000008UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT2_SHFT 4
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT2_MASK 0x0000000000000010UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT3_SHFT 5
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT3_MASK 0x0000000000000020UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT4_SHFT 6
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT4_MASK 0x0000000000000040UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT5_SHFT 7
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT5_MASK 0x0000000000000080UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT6_SHFT 8
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT6_MASK 0x0000000000000100UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT7_SHFT 9
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT7_MASK 0x0000000000000200UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT8_SHFT 10
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT8_MASK 0x0000000000000400UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT9_SHFT 11
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT9_MASK 0x0000000000000800UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT10_SHFT 12
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT10_MASK 0x0000000000001000UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT11_SHFT 13
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT11_MASK 0x0000000000002000UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT12_SHFT 14
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT12_MASK 0x0000000000004000UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT13_SHFT 15
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT13_MASK 0x0000000000008000UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT14_SHFT 16
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT14_MASK 0x0000000000010000UL
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT15_SHFT 17
#घोषणा UV3H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT15_MASK 0x0000000000020000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT0_SHFT		18
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT0_MASK		0x0000000000040000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT1_SHFT		19
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT1_MASK		0x0000000000080000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT2_SHFT		20
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT2_MASK		0x0000000000100000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT3_SHFT		21
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT3_MASK		0x0000000000200000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT4_SHFT		22
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT4_MASK		0x0000000000400000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT5_SHFT		23
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT5_MASK		0x0000000000800000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT6_SHFT		24
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT6_MASK		0x0000000001000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT7_SHFT		25
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT7_MASK		0x0000000002000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT8_SHFT		26
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT8_MASK		0x0000000004000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT9_SHFT		27
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT9_MASK		0x0000000008000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT10_SHFT		28
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT10_MASK		0x0000000010000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT11_SHFT		29
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT11_MASK		0x0000000020000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT12_SHFT		30
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT12_MASK		0x0000000040000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT13_SHFT		31
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT13_MASK		0x0000000080000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT14_SHFT		32
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT14_MASK		0x0000000100000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT15_SHFT		33
#घोषणा UV3H_EVENT_OCCURRED1_GR0_TLB_INT15_MASK		0x0000000200000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT0_SHFT		34
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT0_MASK		0x0000000400000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT1_SHFT		35
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT1_MASK		0x0000000800000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT2_SHFT		36
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT2_MASK		0x0000001000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT3_SHFT		37
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT3_MASK		0x0000002000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT4_SHFT		38
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT4_MASK		0x0000004000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT5_SHFT		39
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT5_MASK		0x0000008000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT6_SHFT		40
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT6_MASK		0x0000010000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT7_SHFT		41
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT7_MASK		0x0000020000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT8_SHFT		42
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT8_MASK		0x0000040000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT9_SHFT		43
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT9_MASK		0x0000080000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT10_SHFT		44
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT10_MASK		0x0000100000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT11_SHFT		45
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT11_MASK		0x0000200000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT12_SHFT		46
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT12_MASK		0x0000400000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT13_SHFT		47
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT13_MASK		0x0000800000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT14_SHFT		48
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT14_MASK		0x0001000000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT15_SHFT		49
#घोषणा UV3H_EVENT_OCCURRED1_GR1_TLB_INT15_MASK		0x0002000000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_RTC_INTERVAL_INT_SHFT	50
#घोषणा UV3H_EVENT_OCCURRED1_RTC_INTERVAL_INT_MASK	0x0004000000000000UL
#घोषणा UV3H_EVENT_OCCURRED1_BAU_DASHBOARD_INT_SHFT	51
#घोषणा UV3H_EVENT_OCCURRED1_BAU_DASHBOARD_INT_MASK	0x0008000000000000UL

/* UV2 unique defines */
#घोषणा UV2H_EVENT_OCCURRED1_BAU_DATA_SHFT		0
#घोषणा UV2H_EVENT_OCCURRED1_BAU_DATA_MASK		0x0000000000000001UL
#घोषणा UV2H_EVENT_OCCURRED1_POWER_MANAGEMENT_REQ_SHFT	1
#घोषणा UV2H_EVENT_OCCURRED1_POWER_MANAGEMENT_REQ_MASK	0x0000000000000002UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT0_SHFT 2
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT0_MASK 0x0000000000000004UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT1_SHFT 3
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT1_MASK 0x0000000000000008UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT2_SHFT 4
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT2_MASK 0x0000000000000010UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT3_SHFT 5
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT3_MASK 0x0000000000000020UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT4_SHFT 6
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT4_MASK 0x0000000000000040UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT5_SHFT 7
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT5_MASK 0x0000000000000080UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT6_SHFT 8
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT6_MASK 0x0000000000000100UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT7_SHFT 9
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT7_MASK 0x0000000000000200UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT8_SHFT 10
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT8_MASK 0x0000000000000400UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT9_SHFT 11
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT9_MASK 0x0000000000000800UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT10_SHFT 12
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT10_MASK 0x0000000000001000UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT11_SHFT 13
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT11_MASK 0x0000000000002000UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT12_SHFT 14
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT12_MASK 0x0000000000004000UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT13_SHFT 15
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT13_MASK 0x0000000000008000UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT14_SHFT 16
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT14_MASK 0x0000000000010000UL
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT15_SHFT 17
#घोषणा UV2H_EVENT_OCCURRED1_MESSAGE_ACCELERATOR_INT15_MASK 0x0000000000020000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT0_SHFT		18
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT0_MASK		0x0000000000040000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT1_SHFT		19
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT1_MASK		0x0000000000080000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT2_SHFT		20
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT2_MASK		0x0000000000100000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT3_SHFT		21
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT3_MASK		0x0000000000200000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT4_SHFT		22
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT4_MASK		0x0000000000400000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT5_SHFT		23
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT5_MASK		0x0000000000800000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT6_SHFT		24
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT6_MASK		0x0000000001000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT7_SHFT		25
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT7_MASK		0x0000000002000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT8_SHFT		26
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT8_MASK		0x0000000004000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT9_SHFT		27
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT9_MASK		0x0000000008000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT10_SHFT		28
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT10_MASK		0x0000000010000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT11_SHFT		29
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT11_MASK		0x0000000020000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT12_SHFT		30
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT12_MASK		0x0000000040000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT13_SHFT		31
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT13_MASK		0x0000000080000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT14_SHFT		32
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT14_MASK		0x0000000100000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT15_SHFT		33
#घोषणा UV2H_EVENT_OCCURRED1_GR0_TLB_INT15_MASK		0x0000000200000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT0_SHFT		34
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT0_MASK		0x0000000400000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT1_SHFT		35
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT1_MASK		0x0000000800000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT2_SHFT		36
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT2_MASK		0x0000001000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT3_SHFT		37
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT3_MASK		0x0000002000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT4_SHFT		38
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT4_MASK		0x0000004000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT5_SHFT		39
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT5_MASK		0x0000008000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT6_SHFT		40
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT6_MASK		0x0000010000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT7_SHFT		41
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT7_MASK		0x0000020000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT8_SHFT		42
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT8_MASK		0x0000040000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT9_SHFT		43
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT9_MASK		0x0000080000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT10_SHFT		44
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT10_MASK		0x0000100000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT11_SHFT		45
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT11_MASK		0x0000200000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT12_SHFT		46
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT12_MASK		0x0000400000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT13_SHFT		47
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT13_MASK		0x0000800000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT14_SHFT		48
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT14_MASK		0x0001000000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT15_SHFT		49
#घोषणा UV2H_EVENT_OCCURRED1_GR1_TLB_INT15_MASK		0x0002000000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_RTC_INTERVAL_INT_SHFT	50
#घोषणा UV2H_EVENT_OCCURRED1_RTC_INTERVAL_INT_MASK	0x0004000000000000UL
#घोषणा UV2H_EVENT_OCCURRED1_BAU_DASHBOARD_INT_SHFT	51
#घोषणा UV2H_EVENT_OCCURRED1_BAU_DASHBOARD_INT_MASK	0x0008000000000000UL

#घोषणा UVH_EVENT_OCCURRED1_EXTIO_INT0_MASK (				\
	is_uv(UV5) ? 0x0000000000000002UL :				\
	0)
#घोषणा UVH_EVENT_OCCURRED1_EXTIO_INT0_SHFT (				\
	is_uv(UV5) ? 1 :						\
	-1)

जोड़ uvyh_event_occurred1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_event_occurred1_s अणु
		अचिन्हित दीर्घ	ipi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	profile_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	bau_data:1;			/* RW */
		अचिन्हित दीर्घ	proc_general:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक16:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक17:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक18:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक19:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक20:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक21:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक22:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक23:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_38_63:26;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_event_occurred1_s अणु
		अचिन्हित दीर्घ	ipi_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	extio_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	profile_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	bau_data:1;			/* RW */
		अचिन्हित दीर्घ	proc_general:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	xh_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक16:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक17:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक18:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक19:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक20:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक21:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक22:1;		/* RW */
		अचिन्हित दीर्घ	rdm_tlb_पूर्णांक23:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_38_63:26;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_event_occurred1_s अणु
		अचिन्हित दीर्घ	profile_पूर्णांक:1;			/* RW */
		अचिन्हित दीर्घ	bau_data:1;			/* RW */
		अचिन्हित दीर्घ	proc_general:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक16:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक17:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक18:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक19:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक20:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक21:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक22:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक23:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक16:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक17:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक18:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक19:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक20:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक21:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक22:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक23:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_51_63:13;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_event_occurred1_s अणु
		अचिन्हित दीर्घ	bau_data:1;			/* RW */
		अचिन्हित दीर्घ	घातer_management_req:1;		/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक0:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक1:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक2:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक3:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक4:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक5:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक6:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक7:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक8:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक9:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक10:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक11:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक12:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक13:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक14:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक15:1;	/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	rtc_पूर्णांकerval_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	bau_dashboard_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_52_63:12;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_event_occurred1_s अणु
		अचिन्हित दीर्घ	bau_data:1;			/* RW */
		अचिन्हित दीर्घ	घातer_management_req:1;		/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक0:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक1:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक2:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक3:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक4:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक5:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक6:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक7:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक8:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक9:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक10:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक11:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक12:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक13:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक14:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक15:1;	/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr0_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक0:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक1:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक2:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक3:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक4:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक5:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक6:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक7:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक8:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक9:1;			/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक10:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक11:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक12:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक13:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक14:1;		/* RW */
		अचिन्हित दीर्घ	gr1_tlb_पूर्णांक15:1;		/* RW */
		अचिन्हित दीर्घ	rtc_पूर्णांकerval_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	bau_dashboard_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	rsvd_52_63:12;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                        UVH_EVENT_OCCURRED1_ALIAS                          */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED1_ALIAS 0x70088UL


/* ========================================================================= */
/*                           UVH_EVENT_OCCURRED2                             */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED2 0x70100UL



/* UVYH common defines */
#घोषणा UVYH_EVENT_OCCURRED2_RTC_INTERVAL_INT_SHFT	0
#घोषणा UVYH_EVENT_OCCURRED2_RTC_INTERVAL_INT_MASK	0x0000000000000001UL
#घोषणा UVYH_EVENT_OCCURRED2_BAU_DASHBOARD_INT_SHFT	1
#घोषणा UVYH_EVENT_OCCURRED2_BAU_DASHBOARD_INT_MASK	0x0000000000000002UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_0_SHFT			2
#घोषणा UVYH_EVENT_OCCURRED2_RTC_0_MASK			0x0000000000000004UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_1_SHFT			3
#घोषणा UVYH_EVENT_OCCURRED2_RTC_1_MASK			0x0000000000000008UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_2_SHFT			4
#घोषणा UVYH_EVENT_OCCURRED2_RTC_2_MASK			0x0000000000000010UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_3_SHFT			5
#घोषणा UVYH_EVENT_OCCURRED2_RTC_3_MASK			0x0000000000000020UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_4_SHFT			6
#घोषणा UVYH_EVENT_OCCURRED2_RTC_4_MASK			0x0000000000000040UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_5_SHFT			7
#घोषणा UVYH_EVENT_OCCURRED2_RTC_5_MASK			0x0000000000000080UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_6_SHFT			8
#घोषणा UVYH_EVENT_OCCURRED2_RTC_6_MASK			0x0000000000000100UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_7_SHFT			9
#घोषणा UVYH_EVENT_OCCURRED2_RTC_7_MASK			0x0000000000000200UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_8_SHFT			10
#घोषणा UVYH_EVENT_OCCURRED2_RTC_8_MASK			0x0000000000000400UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_9_SHFT			11
#घोषणा UVYH_EVENT_OCCURRED2_RTC_9_MASK			0x0000000000000800UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_10_SHFT		12
#घोषणा UVYH_EVENT_OCCURRED2_RTC_10_MASK		0x0000000000001000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_11_SHFT		13
#घोषणा UVYH_EVENT_OCCURRED2_RTC_11_MASK		0x0000000000002000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_12_SHFT		14
#घोषणा UVYH_EVENT_OCCURRED2_RTC_12_MASK		0x0000000000004000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_13_SHFT		15
#घोषणा UVYH_EVENT_OCCURRED2_RTC_13_MASK		0x0000000000008000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_14_SHFT		16
#घोषणा UVYH_EVENT_OCCURRED2_RTC_14_MASK		0x0000000000010000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_15_SHFT		17
#घोषणा UVYH_EVENT_OCCURRED2_RTC_15_MASK		0x0000000000020000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_16_SHFT		18
#घोषणा UVYH_EVENT_OCCURRED2_RTC_16_MASK		0x0000000000040000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_17_SHFT		19
#घोषणा UVYH_EVENT_OCCURRED2_RTC_17_MASK		0x0000000000080000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_18_SHFT		20
#घोषणा UVYH_EVENT_OCCURRED2_RTC_18_MASK		0x0000000000100000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_19_SHFT		21
#घोषणा UVYH_EVENT_OCCURRED2_RTC_19_MASK		0x0000000000200000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_20_SHFT		22
#घोषणा UVYH_EVENT_OCCURRED2_RTC_20_MASK		0x0000000000400000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_21_SHFT		23
#घोषणा UVYH_EVENT_OCCURRED2_RTC_21_MASK		0x0000000000800000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_22_SHFT		24
#घोषणा UVYH_EVENT_OCCURRED2_RTC_22_MASK		0x0000000001000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_23_SHFT		25
#घोषणा UVYH_EVENT_OCCURRED2_RTC_23_MASK		0x0000000002000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_24_SHFT		26
#घोषणा UVYH_EVENT_OCCURRED2_RTC_24_MASK		0x0000000004000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_25_SHFT		27
#घोषणा UVYH_EVENT_OCCURRED2_RTC_25_MASK		0x0000000008000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_26_SHFT		28
#घोषणा UVYH_EVENT_OCCURRED2_RTC_26_MASK		0x0000000010000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_27_SHFT		29
#घोषणा UVYH_EVENT_OCCURRED2_RTC_27_MASK		0x0000000020000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_28_SHFT		30
#घोषणा UVYH_EVENT_OCCURRED2_RTC_28_MASK		0x0000000040000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_29_SHFT		31
#घोषणा UVYH_EVENT_OCCURRED2_RTC_29_MASK		0x0000000080000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_30_SHFT		32
#घोषणा UVYH_EVENT_OCCURRED2_RTC_30_MASK		0x0000000100000000UL
#घोषणा UVYH_EVENT_OCCURRED2_RTC_31_SHFT		33
#घोषणा UVYH_EVENT_OCCURRED2_RTC_31_MASK		0x0000000200000000UL

/* UV4 unique defines */
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT0_SHFT 0
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT0_MASK 0x0000000000000001UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT1_SHFT 1
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT1_MASK 0x0000000000000002UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT2_SHFT 2
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT2_MASK 0x0000000000000004UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT3_SHFT 3
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT3_MASK 0x0000000000000008UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT4_SHFT 4
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT4_MASK 0x0000000000000010UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT5_SHFT 5
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT5_MASK 0x0000000000000020UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT6_SHFT 6
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT6_MASK 0x0000000000000040UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT7_SHFT 7
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT7_MASK 0x0000000000000080UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT8_SHFT 8
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT8_MASK 0x0000000000000100UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT9_SHFT 9
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT9_MASK 0x0000000000000200UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT10_SHFT 10
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT10_MASK 0x0000000000000400UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT11_SHFT 11
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT11_MASK 0x0000000000000800UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT12_SHFT 12
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT12_MASK 0x0000000000001000UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT13_SHFT 13
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT13_MASK 0x0000000000002000UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT14_SHFT 14
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT14_MASK 0x0000000000004000UL
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT15_SHFT 15
#घोषणा UV4H_EVENT_OCCURRED2_MESSAGE_ACCELERATOR_INT15_MASK 0x0000000000008000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_INTERVAL_INT_SHFT	16
#घोषणा UV4H_EVENT_OCCURRED2_RTC_INTERVAL_INT_MASK	0x0000000000010000UL
#घोषणा UV4H_EVENT_OCCURRED2_BAU_DASHBOARD_INT_SHFT	17
#घोषणा UV4H_EVENT_OCCURRED2_BAU_DASHBOARD_INT_MASK	0x0000000000020000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_0_SHFT			18
#घोषणा UV4H_EVENT_OCCURRED2_RTC_0_MASK			0x0000000000040000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_1_SHFT			19
#घोषणा UV4H_EVENT_OCCURRED2_RTC_1_MASK			0x0000000000080000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_2_SHFT			20
#घोषणा UV4H_EVENT_OCCURRED2_RTC_2_MASK			0x0000000000100000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_3_SHFT			21
#घोषणा UV4H_EVENT_OCCURRED2_RTC_3_MASK			0x0000000000200000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_4_SHFT			22
#घोषणा UV4H_EVENT_OCCURRED2_RTC_4_MASK			0x0000000000400000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_5_SHFT			23
#घोषणा UV4H_EVENT_OCCURRED2_RTC_5_MASK			0x0000000000800000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_6_SHFT			24
#घोषणा UV4H_EVENT_OCCURRED2_RTC_6_MASK			0x0000000001000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_7_SHFT			25
#घोषणा UV4H_EVENT_OCCURRED2_RTC_7_MASK			0x0000000002000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_8_SHFT			26
#घोषणा UV4H_EVENT_OCCURRED2_RTC_8_MASK			0x0000000004000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_9_SHFT			27
#घोषणा UV4H_EVENT_OCCURRED2_RTC_9_MASK			0x0000000008000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_10_SHFT		28
#घोषणा UV4H_EVENT_OCCURRED2_RTC_10_MASK		0x0000000010000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_11_SHFT		29
#घोषणा UV4H_EVENT_OCCURRED2_RTC_11_MASK		0x0000000020000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_12_SHFT		30
#घोषणा UV4H_EVENT_OCCURRED2_RTC_12_MASK		0x0000000040000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_13_SHFT		31
#घोषणा UV4H_EVENT_OCCURRED2_RTC_13_MASK		0x0000000080000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_14_SHFT		32
#घोषणा UV4H_EVENT_OCCURRED2_RTC_14_MASK		0x0000000100000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_15_SHFT		33
#घोषणा UV4H_EVENT_OCCURRED2_RTC_15_MASK		0x0000000200000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_16_SHFT		34
#घोषणा UV4H_EVENT_OCCURRED2_RTC_16_MASK		0x0000000400000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_17_SHFT		35
#घोषणा UV4H_EVENT_OCCURRED2_RTC_17_MASK		0x0000000800000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_18_SHFT		36
#घोषणा UV4H_EVENT_OCCURRED2_RTC_18_MASK		0x0000001000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_19_SHFT		37
#घोषणा UV4H_EVENT_OCCURRED2_RTC_19_MASK		0x0000002000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_20_SHFT		38
#घोषणा UV4H_EVENT_OCCURRED2_RTC_20_MASK		0x0000004000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_21_SHFT		39
#घोषणा UV4H_EVENT_OCCURRED2_RTC_21_MASK		0x0000008000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_22_SHFT		40
#घोषणा UV4H_EVENT_OCCURRED2_RTC_22_MASK		0x0000010000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_23_SHFT		41
#घोषणा UV4H_EVENT_OCCURRED2_RTC_23_MASK		0x0000020000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_24_SHFT		42
#घोषणा UV4H_EVENT_OCCURRED2_RTC_24_MASK		0x0000040000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_25_SHFT		43
#घोषणा UV4H_EVENT_OCCURRED2_RTC_25_MASK		0x0000080000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_26_SHFT		44
#घोषणा UV4H_EVENT_OCCURRED2_RTC_26_MASK		0x0000100000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_27_SHFT		45
#घोषणा UV4H_EVENT_OCCURRED2_RTC_27_MASK		0x0000200000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_28_SHFT		46
#घोषणा UV4H_EVENT_OCCURRED2_RTC_28_MASK		0x0000400000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_29_SHFT		47
#घोषणा UV4H_EVENT_OCCURRED2_RTC_29_MASK		0x0000800000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_30_SHFT		48
#घोषणा UV4H_EVENT_OCCURRED2_RTC_30_MASK		0x0001000000000000UL
#घोषणा UV4H_EVENT_OCCURRED2_RTC_31_SHFT		49
#घोषणा UV4H_EVENT_OCCURRED2_RTC_31_MASK		0x0002000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_EVENT_OCCURRED2_RTC_0_SHFT			0
#घोषणा UV3H_EVENT_OCCURRED2_RTC_0_MASK			0x0000000000000001UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_1_SHFT			1
#घोषणा UV3H_EVENT_OCCURRED2_RTC_1_MASK			0x0000000000000002UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_2_SHFT			2
#घोषणा UV3H_EVENT_OCCURRED2_RTC_2_MASK			0x0000000000000004UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_3_SHFT			3
#घोषणा UV3H_EVENT_OCCURRED2_RTC_3_MASK			0x0000000000000008UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_4_SHFT			4
#घोषणा UV3H_EVENT_OCCURRED2_RTC_4_MASK			0x0000000000000010UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_5_SHFT			5
#घोषणा UV3H_EVENT_OCCURRED2_RTC_5_MASK			0x0000000000000020UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_6_SHFT			6
#घोषणा UV3H_EVENT_OCCURRED2_RTC_6_MASK			0x0000000000000040UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_7_SHFT			7
#घोषणा UV3H_EVENT_OCCURRED2_RTC_7_MASK			0x0000000000000080UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_8_SHFT			8
#घोषणा UV3H_EVENT_OCCURRED2_RTC_8_MASK			0x0000000000000100UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_9_SHFT			9
#घोषणा UV3H_EVENT_OCCURRED2_RTC_9_MASK			0x0000000000000200UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_10_SHFT		10
#घोषणा UV3H_EVENT_OCCURRED2_RTC_10_MASK		0x0000000000000400UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_11_SHFT		11
#घोषणा UV3H_EVENT_OCCURRED2_RTC_11_MASK		0x0000000000000800UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_12_SHFT		12
#घोषणा UV3H_EVENT_OCCURRED2_RTC_12_MASK		0x0000000000001000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_13_SHFT		13
#घोषणा UV3H_EVENT_OCCURRED2_RTC_13_MASK		0x0000000000002000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_14_SHFT		14
#घोषणा UV3H_EVENT_OCCURRED2_RTC_14_MASK		0x0000000000004000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_15_SHFT		15
#घोषणा UV3H_EVENT_OCCURRED2_RTC_15_MASK		0x0000000000008000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_16_SHFT		16
#घोषणा UV3H_EVENT_OCCURRED2_RTC_16_MASK		0x0000000000010000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_17_SHFT		17
#घोषणा UV3H_EVENT_OCCURRED2_RTC_17_MASK		0x0000000000020000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_18_SHFT		18
#घोषणा UV3H_EVENT_OCCURRED2_RTC_18_MASK		0x0000000000040000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_19_SHFT		19
#घोषणा UV3H_EVENT_OCCURRED2_RTC_19_MASK		0x0000000000080000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_20_SHFT		20
#घोषणा UV3H_EVENT_OCCURRED2_RTC_20_MASK		0x0000000000100000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_21_SHFT		21
#घोषणा UV3H_EVENT_OCCURRED2_RTC_21_MASK		0x0000000000200000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_22_SHFT		22
#घोषणा UV3H_EVENT_OCCURRED2_RTC_22_MASK		0x0000000000400000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_23_SHFT		23
#घोषणा UV3H_EVENT_OCCURRED2_RTC_23_MASK		0x0000000000800000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_24_SHFT		24
#घोषणा UV3H_EVENT_OCCURRED2_RTC_24_MASK		0x0000000001000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_25_SHFT		25
#घोषणा UV3H_EVENT_OCCURRED2_RTC_25_MASK		0x0000000002000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_26_SHFT		26
#घोषणा UV3H_EVENT_OCCURRED2_RTC_26_MASK		0x0000000004000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_27_SHFT		27
#घोषणा UV3H_EVENT_OCCURRED2_RTC_27_MASK		0x0000000008000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_28_SHFT		28
#घोषणा UV3H_EVENT_OCCURRED2_RTC_28_MASK		0x0000000010000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_29_SHFT		29
#घोषणा UV3H_EVENT_OCCURRED2_RTC_29_MASK		0x0000000020000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_30_SHFT		30
#घोषणा UV3H_EVENT_OCCURRED2_RTC_30_MASK		0x0000000040000000UL
#घोषणा UV3H_EVENT_OCCURRED2_RTC_31_SHFT		31
#घोषणा UV3H_EVENT_OCCURRED2_RTC_31_MASK		0x0000000080000000UL

/* UV2 unique defines */
#घोषणा UV2H_EVENT_OCCURRED2_RTC_0_SHFT			0
#घोषणा UV2H_EVENT_OCCURRED2_RTC_0_MASK			0x0000000000000001UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_1_SHFT			1
#घोषणा UV2H_EVENT_OCCURRED2_RTC_1_MASK			0x0000000000000002UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_2_SHFT			2
#घोषणा UV2H_EVENT_OCCURRED2_RTC_2_MASK			0x0000000000000004UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_3_SHFT			3
#घोषणा UV2H_EVENT_OCCURRED2_RTC_3_MASK			0x0000000000000008UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_4_SHFT			4
#घोषणा UV2H_EVENT_OCCURRED2_RTC_4_MASK			0x0000000000000010UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_5_SHFT			5
#घोषणा UV2H_EVENT_OCCURRED2_RTC_5_MASK			0x0000000000000020UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_6_SHFT			6
#घोषणा UV2H_EVENT_OCCURRED2_RTC_6_MASK			0x0000000000000040UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_7_SHFT			7
#घोषणा UV2H_EVENT_OCCURRED2_RTC_7_MASK			0x0000000000000080UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_8_SHFT			8
#घोषणा UV2H_EVENT_OCCURRED2_RTC_8_MASK			0x0000000000000100UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_9_SHFT			9
#घोषणा UV2H_EVENT_OCCURRED2_RTC_9_MASK			0x0000000000000200UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_10_SHFT		10
#घोषणा UV2H_EVENT_OCCURRED2_RTC_10_MASK		0x0000000000000400UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_11_SHFT		11
#घोषणा UV2H_EVENT_OCCURRED2_RTC_11_MASK		0x0000000000000800UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_12_SHFT		12
#घोषणा UV2H_EVENT_OCCURRED2_RTC_12_MASK		0x0000000000001000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_13_SHFT		13
#घोषणा UV2H_EVENT_OCCURRED2_RTC_13_MASK		0x0000000000002000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_14_SHFT		14
#घोषणा UV2H_EVENT_OCCURRED2_RTC_14_MASK		0x0000000000004000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_15_SHFT		15
#घोषणा UV2H_EVENT_OCCURRED2_RTC_15_MASK		0x0000000000008000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_16_SHFT		16
#घोषणा UV2H_EVENT_OCCURRED2_RTC_16_MASK		0x0000000000010000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_17_SHFT		17
#घोषणा UV2H_EVENT_OCCURRED2_RTC_17_MASK		0x0000000000020000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_18_SHFT		18
#घोषणा UV2H_EVENT_OCCURRED2_RTC_18_MASK		0x0000000000040000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_19_SHFT		19
#घोषणा UV2H_EVENT_OCCURRED2_RTC_19_MASK		0x0000000000080000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_20_SHFT		20
#घोषणा UV2H_EVENT_OCCURRED2_RTC_20_MASK		0x0000000000100000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_21_SHFT		21
#घोषणा UV2H_EVENT_OCCURRED2_RTC_21_MASK		0x0000000000200000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_22_SHFT		22
#घोषणा UV2H_EVENT_OCCURRED2_RTC_22_MASK		0x0000000000400000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_23_SHFT		23
#घोषणा UV2H_EVENT_OCCURRED2_RTC_23_MASK		0x0000000000800000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_24_SHFT		24
#घोषणा UV2H_EVENT_OCCURRED2_RTC_24_MASK		0x0000000001000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_25_SHFT		25
#घोषणा UV2H_EVENT_OCCURRED2_RTC_25_MASK		0x0000000002000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_26_SHFT		26
#घोषणा UV2H_EVENT_OCCURRED2_RTC_26_MASK		0x0000000004000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_27_SHFT		27
#घोषणा UV2H_EVENT_OCCURRED2_RTC_27_MASK		0x0000000008000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_28_SHFT		28
#घोषणा UV2H_EVENT_OCCURRED2_RTC_28_MASK		0x0000000010000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_29_SHFT		29
#घोषणा UV2H_EVENT_OCCURRED2_RTC_29_MASK		0x0000000020000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_30_SHFT		30
#घोषणा UV2H_EVENT_OCCURRED2_RTC_30_MASK		0x0000000040000000UL
#घोषणा UV2H_EVENT_OCCURRED2_RTC_31_SHFT		31
#घोषणा UV2H_EVENT_OCCURRED2_RTC_31_MASK		0x0000000080000000UL

#घोषणा UVH_EVENT_OCCURRED2_RTC_1_MASK (				\
	is_uv(UV5) ? 0x0000000000000008UL :				\
	is_uv(UV4) ? 0x0000000000080000UL :				\
	is_uv(UV3) ? 0x0000000000000002UL :				\
	is_uv(UV2) ? 0x0000000000000002UL :				\
	0)
#घोषणा UVH_EVENT_OCCURRED2_RTC_1_SHFT (				\
	is_uv(UV5) ? 3 :						\
	is_uv(UV4) ? 19 :						\
	is_uv(UV3) ? 1 :						\
	is_uv(UV2) ? 1 :						\
	-1)

जोड़ uvyh_event_occurred2_u अणु
	अचिन्हित दीर्घ	v;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_event_occurred2_s अणु
		अचिन्हित दीर्घ	rtc_पूर्णांकerval_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	bau_dashboard_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	rtc_0:1;			/* RW */
		अचिन्हित दीर्घ	rtc_1:1;			/* RW */
		अचिन्हित दीर्घ	rtc_2:1;			/* RW */
		अचिन्हित दीर्घ	rtc_3:1;			/* RW */
		अचिन्हित दीर्घ	rtc_4:1;			/* RW */
		अचिन्हित दीर्घ	rtc_5:1;			/* RW */
		अचिन्हित दीर्घ	rtc_6:1;			/* RW */
		अचिन्हित दीर्घ	rtc_7:1;			/* RW */
		अचिन्हित दीर्घ	rtc_8:1;			/* RW */
		अचिन्हित दीर्घ	rtc_9:1;			/* RW */
		अचिन्हित दीर्घ	rtc_10:1;			/* RW */
		अचिन्हित दीर्घ	rtc_11:1;			/* RW */
		अचिन्हित दीर्घ	rtc_12:1;			/* RW */
		अचिन्हित दीर्घ	rtc_13:1;			/* RW */
		अचिन्हित दीर्घ	rtc_14:1;			/* RW */
		अचिन्हित दीर्घ	rtc_15:1;			/* RW */
		अचिन्हित दीर्घ	rtc_16:1;			/* RW */
		अचिन्हित दीर्घ	rtc_17:1;			/* RW */
		अचिन्हित दीर्घ	rtc_18:1;			/* RW */
		अचिन्हित दीर्घ	rtc_19:1;			/* RW */
		अचिन्हित दीर्घ	rtc_20:1;			/* RW */
		अचिन्हित दीर्घ	rtc_21:1;			/* RW */
		अचिन्हित दीर्घ	rtc_22:1;			/* RW */
		अचिन्हित दीर्घ	rtc_23:1;			/* RW */
		अचिन्हित दीर्घ	rtc_24:1;			/* RW */
		अचिन्हित दीर्घ	rtc_25:1;			/* RW */
		अचिन्हित दीर्घ	rtc_26:1;			/* RW */
		अचिन्हित दीर्घ	rtc_27:1;			/* RW */
		अचिन्हित दीर्घ	rtc_28:1;			/* RW */
		अचिन्हित दीर्घ	rtc_29:1;			/* RW */
		अचिन्हित दीर्घ	rtc_30:1;			/* RW */
		अचिन्हित दीर्घ	rtc_31:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_34_63:30;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_event_occurred2_s अणु
		अचिन्हित दीर्घ	rtc_पूर्णांकerval_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	bau_dashboard_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	rtc_0:1;			/* RW */
		अचिन्हित दीर्घ	rtc_1:1;			/* RW */
		अचिन्हित दीर्घ	rtc_2:1;			/* RW */
		अचिन्हित दीर्घ	rtc_3:1;			/* RW */
		अचिन्हित दीर्घ	rtc_4:1;			/* RW */
		अचिन्हित दीर्घ	rtc_5:1;			/* RW */
		अचिन्हित दीर्घ	rtc_6:1;			/* RW */
		अचिन्हित दीर्घ	rtc_7:1;			/* RW */
		अचिन्हित दीर्घ	rtc_8:1;			/* RW */
		अचिन्हित दीर्घ	rtc_9:1;			/* RW */
		अचिन्हित दीर्घ	rtc_10:1;			/* RW */
		अचिन्हित दीर्घ	rtc_11:1;			/* RW */
		अचिन्हित दीर्घ	rtc_12:1;			/* RW */
		अचिन्हित दीर्घ	rtc_13:1;			/* RW */
		अचिन्हित दीर्घ	rtc_14:1;			/* RW */
		अचिन्हित दीर्घ	rtc_15:1;			/* RW */
		अचिन्हित दीर्घ	rtc_16:1;			/* RW */
		अचिन्हित दीर्घ	rtc_17:1;			/* RW */
		अचिन्हित दीर्घ	rtc_18:1;			/* RW */
		अचिन्हित दीर्घ	rtc_19:1;			/* RW */
		अचिन्हित दीर्घ	rtc_20:1;			/* RW */
		अचिन्हित दीर्घ	rtc_21:1;			/* RW */
		अचिन्हित दीर्घ	rtc_22:1;			/* RW */
		अचिन्हित दीर्घ	rtc_23:1;			/* RW */
		अचिन्हित दीर्घ	rtc_24:1;			/* RW */
		अचिन्हित दीर्घ	rtc_25:1;			/* RW */
		अचिन्हित दीर्घ	rtc_26:1;			/* RW */
		अचिन्हित दीर्घ	rtc_27:1;			/* RW */
		अचिन्हित दीर्घ	rtc_28:1;			/* RW */
		अचिन्हित दीर्घ	rtc_29:1;			/* RW */
		अचिन्हित दीर्घ	rtc_30:1;			/* RW */
		अचिन्हित दीर्घ	rtc_31:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_34_63:30;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_event_occurred2_s अणु
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक0:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक1:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक2:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक3:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक4:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक5:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक6:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक7:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक8:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक9:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक10:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक11:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक12:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक13:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक14:1;	/* RW */
		अचिन्हित दीर्घ	message_accelerator_पूर्णांक15:1;	/* RW */
		अचिन्हित दीर्घ	rtc_पूर्णांकerval_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	bau_dashboard_पूर्णांक:1;		/* RW */
		अचिन्हित दीर्घ	rtc_0:1;			/* RW */
		अचिन्हित दीर्घ	rtc_1:1;			/* RW */
		अचिन्हित दीर्घ	rtc_2:1;			/* RW */
		अचिन्हित दीर्घ	rtc_3:1;			/* RW */
		अचिन्हित दीर्घ	rtc_4:1;			/* RW */
		अचिन्हित दीर्घ	rtc_5:1;			/* RW */
		अचिन्हित दीर्घ	rtc_6:1;			/* RW */
		अचिन्हित दीर्घ	rtc_7:1;			/* RW */
		अचिन्हित दीर्घ	rtc_8:1;			/* RW */
		अचिन्हित दीर्घ	rtc_9:1;			/* RW */
		अचिन्हित दीर्घ	rtc_10:1;			/* RW */
		अचिन्हित दीर्घ	rtc_11:1;			/* RW */
		अचिन्हित दीर्घ	rtc_12:1;			/* RW */
		अचिन्हित दीर्घ	rtc_13:1;			/* RW */
		अचिन्हित दीर्घ	rtc_14:1;			/* RW */
		अचिन्हित दीर्घ	rtc_15:1;			/* RW */
		अचिन्हित दीर्घ	rtc_16:1;			/* RW */
		अचिन्हित दीर्घ	rtc_17:1;			/* RW */
		अचिन्हित दीर्घ	rtc_18:1;			/* RW */
		अचिन्हित दीर्घ	rtc_19:1;			/* RW */
		अचिन्हित दीर्घ	rtc_20:1;			/* RW */
		अचिन्हित दीर्घ	rtc_21:1;			/* RW */
		अचिन्हित दीर्घ	rtc_22:1;			/* RW */
		अचिन्हित दीर्घ	rtc_23:1;			/* RW */
		अचिन्हित दीर्घ	rtc_24:1;			/* RW */
		अचिन्हित दीर्घ	rtc_25:1;			/* RW */
		अचिन्हित दीर्घ	rtc_26:1;			/* RW */
		अचिन्हित दीर्घ	rtc_27:1;			/* RW */
		अचिन्हित दीर्घ	rtc_28:1;			/* RW */
		अचिन्हित दीर्घ	rtc_29:1;			/* RW */
		अचिन्हित दीर्घ	rtc_30:1;			/* RW */
		अचिन्हित दीर्घ	rtc_31:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_50_63:14;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_event_occurred2_s अणु
		अचिन्हित दीर्घ	rtc_0:1;			/* RW */
		अचिन्हित दीर्घ	rtc_1:1;			/* RW */
		अचिन्हित दीर्घ	rtc_2:1;			/* RW */
		अचिन्हित दीर्घ	rtc_3:1;			/* RW */
		अचिन्हित दीर्घ	rtc_4:1;			/* RW */
		अचिन्हित दीर्घ	rtc_5:1;			/* RW */
		अचिन्हित दीर्घ	rtc_6:1;			/* RW */
		अचिन्हित दीर्घ	rtc_7:1;			/* RW */
		अचिन्हित दीर्घ	rtc_8:1;			/* RW */
		अचिन्हित दीर्घ	rtc_9:1;			/* RW */
		अचिन्हित दीर्घ	rtc_10:1;			/* RW */
		अचिन्हित दीर्घ	rtc_11:1;			/* RW */
		अचिन्हित दीर्घ	rtc_12:1;			/* RW */
		अचिन्हित दीर्घ	rtc_13:1;			/* RW */
		अचिन्हित दीर्घ	rtc_14:1;			/* RW */
		अचिन्हित दीर्घ	rtc_15:1;			/* RW */
		अचिन्हित दीर्घ	rtc_16:1;			/* RW */
		अचिन्हित दीर्घ	rtc_17:1;			/* RW */
		अचिन्हित दीर्घ	rtc_18:1;			/* RW */
		अचिन्हित दीर्घ	rtc_19:1;			/* RW */
		अचिन्हित दीर्घ	rtc_20:1;			/* RW */
		अचिन्हित दीर्घ	rtc_21:1;			/* RW */
		अचिन्हित दीर्घ	rtc_22:1;			/* RW */
		अचिन्हित दीर्घ	rtc_23:1;			/* RW */
		अचिन्हित दीर्घ	rtc_24:1;			/* RW */
		अचिन्हित दीर्घ	rtc_25:1;			/* RW */
		अचिन्हित दीर्घ	rtc_26:1;			/* RW */
		अचिन्हित दीर्घ	rtc_27:1;			/* RW */
		अचिन्हित दीर्घ	rtc_28:1;			/* RW */
		अचिन्हित दीर्घ	rtc_29:1;			/* RW */
		अचिन्हित दीर्घ	rtc_30:1;			/* RW */
		अचिन्हित दीर्घ	rtc_31:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_32_63:32;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_event_occurred2_s अणु
		अचिन्हित दीर्घ	rtc_0:1;			/* RW */
		अचिन्हित दीर्घ	rtc_1:1;			/* RW */
		अचिन्हित दीर्घ	rtc_2:1;			/* RW */
		अचिन्हित दीर्घ	rtc_3:1;			/* RW */
		अचिन्हित दीर्घ	rtc_4:1;			/* RW */
		अचिन्हित दीर्घ	rtc_5:1;			/* RW */
		अचिन्हित दीर्घ	rtc_6:1;			/* RW */
		अचिन्हित दीर्घ	rtc_7:1;			/* RW */
		अचिन्हित दीर्घ	rtc_8:1;			/* RW */
		अचिन्हित दीर्घ	rtc_9:1;			/* RW */
		अचिन्हित दीर्घ	rtc_10:1;			/* RW */
		अचिन्हित दीर्घ	rtc_11:1;			/* RW */
		अचिन्हित दीर्घ	rtc_12:1;			/* RW */
		अचिन्हित दीर्घ	rtc_13:1;			/* RW */
		अचिन्हित दीर्घ	rtc_14:1;			/* RW */
		अचिन्हित दीर्घ	rtc_15:1;			/* RW */
		अचिन्हित दीर्घ	rtc_16:1;			/* RW */
		अचिन्हित दीर्घ	rtc_17:1;			/* RW */
		अचिन्हित दीर्घ	rtc_18:1;			/* RW */
		अचिन्हित दीर्घ	rtc_19:1;			/* RW */
		अचिन्हित दीर्घ	rtc_20:1;			/* RW */
		अचिन्हित दीर्घ	rtc_21:1;			/* RW */
		अचिन्हित दीर्घ	rtc_22:1;			/* RW */
		अचिन्हित दीर्घ	rtc_23:1;			/* RW */
		अचिन्हित दीर्घ	rtc_24:1;			/* RW */
		अचिन्हित दीर्घ	rtc_25:1;			/* RW */
		अचिन्हित दीर्घ	rtc_26:1;			/* RW */
		अचिन्हित दीर्घ	rtc_27:1;			/* RW */
		अचिन्हित दीर्घ	rtc_28:1;			/* RW */
		अचिन्हित दीर्घ	rtc_29:1;			/* RW */
		अचिन्हित दीर्घ	rtc_30:1;			/* RW */
		अचिन्हित दीर्घ	rtc_31:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_32_63:32;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                        UVH_EVENT_OCCURRED2_ALIAS                          */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED2_ALIAS 0x70108UL


/* ========================================================================= */
/*                         UVH_EXTIO_INT0_BROADCAST                          */
/* ========================================================================= */
#घोषणा UVH_EXTIO_INT0_BROADCAST 0x61448UL

/* UVH common defines*/
#घोषणा UVH_EXTIO_INT0_BROADCAST_ENABLE_SHFT		0
#घोषणा UVH_EXTIO_INT0_BROADCAST_ENABLE_MASK		0x0000000000000001UL


जोड़ uvh_extio_पूर्णांक0_broadcast_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_extio_पूर्णांक0_broadcast_s अणु
		अचिन्हित दीर्घ	enable:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_extio_पूर्णांक0_broadcast_s अणु
		अचिन्हित दीर्घ	enable:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_extio_पूर्णांक0_broadcast_s अणु
		अचिन्हित दीर्घ	enable:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_extio_पूर्णांक0_broadcast_s अणु
		अचिन्हित दीर्घ	enable:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_extio_पूर्णांक0_broadcast_s अणु
		अचिन्हित दीर्घ	enable:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_1_63:63;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                          UVH_GR0_GAM_GR_CONFIG                            */
/* ========================================================================= */
#घोषणा UVH_GR0_GAM_GR_CONFIG (						\
	is_uv(UV5) ? 0x600028UL :					\
	is_uv(UV4) ? 0x600028UL :					\
	is_uv(UV3) ? 0xc00028UL :					\
	is_uv(UV2) ? 0xc00028UL :					\
	0)



/* UVYH common defines */
#घोषणा UVYH_GR0_GAM_GR_CONFIG_SUBSPACE_SHFT		10
#घोषणा UVYH_GR0_GAM_GR_CONFIG_SUBSPACE_MASK		0x0000000000000400UL

/* UV4 unique defines */
#घोषणा UV4H_GR0_GAM_GR_CONFIG_SUBSPACE_SHFT		10
#घोषणा UV4H_GR0_GAM_GR_CONFIG_SUBSPACE_MASK		0x0000000000000400UL

/* UV3 unique defines */
#घोषणा UV3H_GR0_GAM_GR_CONFIG_M_SKT_SHFT		0
#घोषणा UV3H_GR0_GAM_GR_CONFIG_M_SKT_MASK		0x000000000000003fUL
#घोषणा UV3H_GR0_GAM_GR_CONFIG_SUBSPACE_SHFT		10
#घोषणा UV3H_GR0_GAM_GR_CONFIG_SUBSPACE_MASK		0x0000000000000400UL

/* UV2 unique defines */
#घोषणा UV2H_GR0_GAM_GR_CONFIG_N_GR_SHFT		0
#घोषणा UV2H_GR0_GAM_GR_CONFIG_N_GR_MASK		0x000000000000000fUL


जोड़ uvyh_gr0_gam_gr_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_gr0_gam_gr_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_9:10;
		अचिन्हित दीर्घ	subspace:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_11_63:53;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_gr0_gam_gr_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_9:10;
		अचिन्हित दीर्घ	subspace:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_11_63:53;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_gr0_gam_gr_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_9:10;
		अचिन्हित दीर्घ	subspace:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_11_63:53;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_gr0_gam_gr_config_s अणु
		अचिन्हित दीर्घ	m_skt:6;			/* RW */
		अचिन्हित दीर्घ	undef_6_9:4;			/* Undefined */
		अचिन्हित दीर्घ	subspace:1;			/* RW */
		अचिन्हित दीर्घ	reserved:53;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_gr0_gam_gr_config_s अणु
		अचिन्हित दीर्घ	n_gr:4;				/* RW */
		अचिन्हित दीर्घ	reserved:60;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR0_TLB_INT0_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR0_TLB_INT0_CONFIG (					\
	is_uv(UV4) ? 0x61b00UL :					\
	is_uv(UV3) ? 0x61b00UL :					\
	is_uv(UV2) ? 0x61b00UL :					\
	uv_undefined("UVH_GR0_TLB_INT0_CONFIG"))


/* UVXH common defines */
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_VECTOR_SHFT		0
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_VECTOR_MASK		0x00000000000000ffUL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_DM_SHFT		8
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_DM_MASK		0x0000000000000700UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_DESTMODE_SHFT		11
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_DESTMODE_MASK		0x0000000000000800UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_STATUS_SHFT		12
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_STATUS_MASK		0x0000000000001000UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_P_SHFT			13
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_P_MASK			0x0000000000002000UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_T_SHFT			15
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_T_MASK			0x0000000000008000UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_M_SHFT			16
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_M_MASK			0x0000000000010000UL
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_APIC_ID_SHFT		32
#घोषणा UVXH_GR0_TLB_INT0_CONFIG_APIC_ID_MASK		0xffffffff00000000UL


जोड़ uvh_gr0_tlb_पूर्णांक0_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_gr0_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_gr0_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_gr0_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_gr0_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_gr0_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR0_TLB_INT1_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR0_TLB_INT1_CONFIG (					\
	is_uv(UV4) ? 0x61b40UL :					\
	is_uv(UV3) ? 0x61b40UL :					\
	is_uv(UV2) ? 0x61b40UL :					\
	uv_undefined("UVH_GR0_TLB_INT1_CONFIG"))


/* UVXH common defines */
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_VECTOR_SHFT		0
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_VECTOR_MASK		0x00000000000000ffUL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_DM_SHFT		8
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_DM_MASK		0x0000000000000700UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_DESTMODE_SHFT		11
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_DESTMODE_MASK		0x0000000000000800UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_STATUS_SHFT		12
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_STATUS_MASK		0x0000000000001000UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_P_SHFT			13
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_P_MASK			0x0000000000002000UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_T_SHFT			15
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_T_MASK			0x0000000000008000UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_M_SHFT			16
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_M_MASK			0x0000000000010000UL
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_APIC_ID_SHFT		32
#घोषणा UVXH_GR0_TLB_INT1_CONFIG_APIC_ID_MASK		0xffffffff00000000UL


जोड़ uvh_gr0_tlb_पूर्णांक1_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_gr0_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_gr0_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_gr0_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_gr0_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_gr0_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR1_TLB_INT0_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR1_TLB_INT0_CONFIG (					\
	is_uv(UV4) ? 0x62100UL :					\
	is_uv(UV3) ? 0x61f00UL :					\
	is_uv(UV2) ? 0x61f00UL :					\
	uv_undefined("UVH_GR1_TLB_INT0_CONFIG"))


/* UVXH common defines */
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_VECTOR_SHFT		0
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_VECTOR_MASK		0x00000000000000ffUL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_DM_SHFT		8
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_DM_MASK		0x0000000000000700UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_DESTMODE_SHFT		11
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_DESTMODE_MASK		0x0000000000000800UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_STATUS_SHFT		12
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_STATUS_MASK		0x0000000000001000UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_P_SHFT			13
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_P_MASK			0x0000000000002000UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_T_SHFT			15
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_T_MASK			0x0000000000008000UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_M_SHFT			16
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_M_MASK			0x0000000000010000UL
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_APIC_ID_SHFT		32
#घोषणा UVXH_GR1_TLB_INT0_CONFIG_APIC_ID_MASK		0xffffffff00000000UL


जोड़ uvh_gr1_tlb_पूर्णांक0_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_gr1_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_gr1_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_gr1_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_gr1_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_gr1_tlb_पूर्णांक0_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR1_TLB_INT1_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR1_TLB_INT1_CONFIG (					\
	is_uv(UV4) ? 0x62140UL :					\
	is_uv(UV3) ? 0x61f40UL :					\
	is_uv(UV2) ? 0x61f40UL :					\
	uv_undefined("UVH_GR1_TLB_INT1_CONFIG"))


/* UVXH common defines */
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_VECTOR_SHFT		0
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_VECTOR_MASK		0x00000000000000ffUL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_DM_SHFT		8
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_DM_MASK		0x0000000000000700UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_DESTMODE_SHFT		11
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_DESTMODE_MASK		0x0000000000000800UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_STATUS_SHFT		12
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_STATUS_MASK		0x0000000000001000UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_P_SHFT			13
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_P_MASK			0x0000000000002000UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_T_SHFT			15
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_T_MASK			0x0000000000008000UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_M_SHFT			16
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_M_MASK			0x0000000000010000UL
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_APIC_ID_SHFT		32
#घोषणा UVXH_GR1_TLB_INT1_CONFIG_APIC_ID_MASK		0xffffffff00000000UL


जोड़ uvh_gr1_tlb_पूर्णांक1_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_gr1_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_gr1_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_gr1_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_gr1_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_gr1_tlb_पूर्णांक1_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                               UVH_INT_CMPB                                */
/* ========================================================================= */
#घोषणा UVH_INT_CMPB 0x22080UL

/* UVH common defines*/
#घोषणा UVH_INT_CMPB_REAL_TIME_CMPB_SHFT		0
#घोषणा UVH_INT_CMPB_REAL_TIME_CMPB_MASK		0x00ffffffffffffffUL


जोड़ uvh_पूर्णांक_cmpb_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_पूर्णांक_cmpb_s अणु
		अचिन्हित दीर्घ	real_समय_cmpb:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_पूर्णांक_cmpb_s अणु
		अचिन्हित दीर्घ	real_समय_cmpb:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_पूर्णांक_cmpb_s अणु
		अचिन्हित दीर्घ	real_समय_cmpb:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_पूर्णांक_cmpb_s अणु
		अचिन्हित दीर्घ	real_समय_cmpb:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_पूर्णांक_cmpb_s अणु
		अचिन्हित दीर्घ	real_समय_cmpb:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                               UVH_IPI_INT                                 */
/* ========================================================================= */
#घोषणा UVH_IPI_INT 0x60500UL

/* UVH common defines*/
#घोषणा UVH_IPI_INT_VECTOR_SHFT				0
#घोषणा UVH_IPI_INT_VECTOR_MASK				0x00000000000000ffUL
#घोषणा UVH_IPI_INT_DELIVERY_MODE_SHFT			8
#घोषणा UVH_IPI_INT_DELIVERY_MODE_MASK			0x0000000000000700UL
#घोषणा UVH_IPI_INT_DESTMODE_SHFT			11
#घोषणा UVH_IPI_INT_DESTMODE_MASK			0x0000000000000800UL
#घोषणा UVH_IPI_INT_APIC_ID_SHFT			16
#घोषणा UVH_IPI_INT_APIC_ID_MASK			0x0000ffffffff0000UL
#घोषणा UVH_IPI_INT_SEND_SHFT				63
#घोषणा UVH_IPI_INT_SEND_MASK				0x8000000000000000UL


जोड़ uvh_ipi_पूर्णांक_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_ipi_पूर्णांक_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	delivery_mode:3;		/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_15:4;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
		अचिन्हित दीर्घ	rsvd_48_62:15;
		अचिन्हित दीर्घ	send:1;				/* WP */
	पूर्ण s;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_ipi_पूर्णांक_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	delivery_mode:3;		/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_15:4;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
		अचिन्हित दीर्घ	rsvd_48_62:15;
		अचिन्हित दीर्घ	send:1;				/* WP */
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_ipi_पूर्णांक_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	delivery_mode:3;		/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_15:4;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
		अचिन्हित दीर्घ	rsvd_48_62:15;
		अचिन्हित दीर्घ	send:1;				/* WP */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_ipi_पूर्णांक_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	delivery_mode:3;		/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_15:4;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
		अचिन्हित दीर्घ	rsvd_48_62:15;
		अचिन्हित दीर्घ	send:1;				/* WP */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_ipi_पूर्णांक_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	delivery_mode:3;		/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_15:4;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
		अचिन्हित दीर्घ	rsvd_48_62:15;
		अचिन्हित दीर्घ	send:1;				/* WP */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                               UVH_NODE_ID                                 */
/* ========================================================================= */
#घोषणा UVH_NODE_ID 0x0UL

/* UVH common defines*/
#घोषणा UVH_NODE_ID_FORCE1_SHFT				0
#घोषणा UVH_NODE_ID_FORCE1_MASK				0x0000000000000001UL
#घोषणा UVH_NODE_ID_MANUFACTURER_SHFT			1
#घोषणा UVH_NODE_ID_MANUFACTURER_MASK			0x0000000000000ffeUL
#घोषणा UVH_NODE_ID_PART_NUMBER_SHFT			12
#घोषणा UVH_NODE_ID_PART_NUMBER_MASK			0x000000000ffff000UL
#घोषणा UVH_NODE_ID_REVISION_SHFT			28
#घोषणा UVH_NODE_ID_REVISION_MASK			0x00000000f0000000UL
#घोषणा UVH_NODE_ID_NODE_ID_SHFT			32
#घोषणा UVH_NODE_ID_NI_PORT_SHFT			57

/* UVXH common defines */
#घोषणा UVXH_NODE_ID_NODE_ID_MASK			0x00007fff00000000UL
#घोषणा UVXH_NODE_ID_NODES_PER_BIT_SHFT			50
#घोषणा UVXH_NODE_ID_NODES_PER_BIT_MASK			0x01fc000000000000UL
#घोषणा UVXH_NODE_ID_NI_PORT_MASK			0x3e00000000000000UL

/* UVYH common defines */
#घोषणा UVYH_NODE_ID_NODE_ID_MASK			0x0000007f00000000UL
#घोषणा UVYH_NODE_ID_NI_PORT_MASK			0x7e00000000000000UL

/* UV4 unique defines */
#घोषणा UV4H_NODE_ID_ROUTER_SELECT_SHFT			48
#घोषणा UV4H_NODE_ID_ROUTER_SELECT_MASK			0x0001000000000000UL
#घोषणा UV4H_NODE_ID_RESERVED_2_SHFT			49
#घोषणा UV4H_NODE_ID_RESERVED_2_MASK			0x0002000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_NODE_ID_ROUTER_SELECT_SHFT			48
#घोषणा UV3H_NODE_ID_ROUTER_SELECT_MASK			0x0001000000000000UL
#घोषणा UV3H_NODE_ID_RESERVED_2_SHFT			49
#घोषणा UV3H_NODE_ID_RESERVED_2_MASK			0x0002000000000000UL


जोड़ uvh_node_id_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	rsvd_32_63:32;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_47_49:3;
		अचिन्हित दीर्घ	nodes_per_bit:7;		/* RO */
		अचिन्हित दीर्घ	ni_port:5;			/* RO */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण sx;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_39_56:18;
		अचिन्हित दीर्घ	ni_port:6;			/* RO */
		अचिन्हित दीर्घ	rsvd_63:1;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_39_56:18;
		अचिन्हित दीर्घ	ni_port:6;			/* RO */
		अचिन्हित दीर्घ	rsvd_63:1;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_47:1;
		अचिन्हित दीर्घ	router_select:1;		/* RO */
		अचिन्हित दीर्घ	rsvd_49:1;
		अचिन्हित दीर्घ	nodes_per_bit:7;		/* RO */
		अचिन्हित दीर्घ	ni_port:5;			/* RO */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_47:1;
		अचिन्हित दीर्घ	router_select:1;		/* RO */
		अचिन्हित दीर्घ	rsvd_49:1;
		अचिन्हित दीर्घ	nodes_per_bit:7;		/* RO */
		अचिन्हित दीर्घ	ni_port:5;			/* RO */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_node_id_s अणु
		अचिन्हित दीर्घ	क्रमce1:1;			/* RO */
		अचिन्हित दीर्घ	manufacturer:11;		/* RO */
		अचिन्हित दीर्घ	part_number:16;			/* RO */
		अचिन्हित दीर्घ	revision:4;			/* RO */
		अचिन्हित दीर्घ	node_id:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_47_49:3;
		अचिन्हित दीर्घ	nodes_per_bit:7;		/* RO */
		अचिन्हित दीर्घ	ni_port:5;			/* RO */
		अचिन्हित दीर्घ	rsvd_62_63:2;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                            UVH_NODE_PRESENT_0                             */
/* ========================================================================= */
#घोषणा UVH_NODE_PRESENT_0 (						\
	is_uv(UV5) ? 0x1400UL :						\
	0)


/* UVYH common defines */
#घोषणा UVYH_NODE_PRESENT_0_NODES_SHFT			0
#घोषणा UVYH_NODE_PRESENT_0_NODES_MASK			0xffffffffffffffffUL


जोड़ uvh_node_present_0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_node_present_0_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_node_present_0_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_node_present_0_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                            UVH_NODE_PRESENT_1                             */
/* ========================================================================= */
#घोषणा UVH_NODE_PRESENT_1 (						\
	is_uv(UV5) ? 0x1408UL :						\
	0)


/* UVYH common defines */
#घोषणा UVYH_NODE_PRESENT_1_NODES_SHFT			0
#घोषणा UVYH_NODE_PRESENT_1_NODES_MASK			0xffffffffffffffffUL


जोड़ uvh_node_present_1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_node_present_1_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_node_present_1_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_node_present_1_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                          UVH_NODE_PRESENT_TABLE                           */
/* ========================================================================= */
#घोषणा UVH_NODE_PRESENT_TABLE (					\
	is_uv(UV4) ? 0x1400UL :						\
	is_uv(UV3) ? 0x1400UL :						\
	is_uv(UV2) ? 0x1400UL :						\
	0)

#घोषणा UVH_NODE_PRESENT_TABLE_DEPTH (					\
	is_uv(UV4) ? 4 :						\
	is_uv(UV3) ? 16 :						\
	is_uv(UV2) ? 16 :						\
	0)


/* UVXH common defines */
#घोषणा UVXH_NODE_PRESENT_TABLE_NODES_SHFT		0
#घोषणा UVXH_NODE_PRESENT_TABLE_NODES_MASK		0xffffffffffffffffUL


जोड़ uvh_node_present_table_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_node_present_table_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_node_present_table_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_node_present_table_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_node_present_table_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_node_present_table_s अणु
		अचिन्हित दीर्घ	nodes:64;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                       UVH_RH10_GAM_ADDR_MAP_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_ADDR_MAP_CONFIG (					\
	is_uv(UV5) ? 0x470000UL :					\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_N_SKT_SHFT	6
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_N_SKT_MASK	0x00000000000001c0UL
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_LS_ENABLE_SHFT	12
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_LS_ENABLE_MASK	0x0000000000001000UL
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_MK_TME_KEYID_BITS_SHFT 16
#घोषणा UVYH_RH10_GAM_ADDR_MAP_CONFIG_MK_TME_KEYID_BITS_MASK 0x00000000000f0000UL


जोड़ uvh_rh10_gam_addr_map_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	undef_0_5:6;			/* Undefined */
		अचिन्हित दीर्घ	n_skt:3;			/* RW */
		अचिन्हित दीर्घ	undef_9_11:3;			/* Undefined */
		अचिन्हित दीर्घ	ls_enable:1;			/* RW */
		अचिन्हित दीर्घ	undef_13_15:3;			/* Undefined */
		अचिन्हित दीर्घ	mk_पंचांगe_keyid_bits:4;		/* RW */
		अचिन्हित दीर्घ	rsvd_20_63:44;
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	undef_0_5:6;			/* Undefined */
		अचिन्हित दीर्घ	n_skt:3;			/* RW */
		अचिन्हित दीर्घ	undef_9_11:3;			/* Undefined */
		अचिन्हित दीर्घ	ls_enable:1;			/* RW */
		अचिन्हित दीर्घ	undef_13_15:3;			/* Undefined */
		अचिन्हित दीर्घ	mk_पंचांगe_keyid_bits:4;		/* RW */
		अचिन्हित दीर्घ	rsvd_20_63:44;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	undef_0_5:6;			/* Undefined */
		अचिन्हित दीर्घ	n_skt:3;			/* RW */
		अचिन्हित दीर्घ	undef_9_11:3;			/* Undefined */
		अचिन्हित दीर्घ	ls_enable:1;			/* RW */
		अचिन्हित दीर्घ	undef_13_15:3;			/* Undefined */
		अचिन्हित दीर्घ	mk_पंचांगe_keyid_bits:4;		/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                     UVH_RH10_GAM_GRU_OVERLAY_CONFIG                       */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_GRU_OVERLAY_CONFIG (				\
	is_uv(UV5) ? 0x4700b0UL :					\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	25
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x000ffffffe000000UL
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_N_GRU_SHFT	52
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_N_GRU_MASK	0x0070000000000000UL
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVYH_RH10_GAM_GRU_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_MASK (			\
	is_uv(UV5) ? 0x000ffffffe000000UL :				\
	0)
#घोषणा UVH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT (			\
	is_uv(UV5) ? 25 :						\
	-1)

जोड़ uvh_rh10_gam_gru_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	n_gru:3;			/* RW */
		अचिन्हित दीर्घ	undef_55_62:8;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	n_gru:3;			/* RW */
		अचिन्हित दीर्घ	undef_55_62:8;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	n_gru:3;			/* RW */
		अचिन्हित दीर्घ	undef_55_62:8;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0                     */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0 (				\
	is_uv(UV5) ? 0x473000UL :					\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT	26
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK	0x000ffffffc000000UL
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_SHFT	52
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_MASK	0x03f0000000000000UL
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_SHFT	63
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK (			\
	is_uv(UV5) ? 0x000ffffffc000000UL :				\
	0)
#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT (			\
	is_uv(UV5) ? 26 :						\
	-1)

जोड़ uvh_rh10_gam_mmioh_overlay_config0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1                     */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1 (				\
	is_uv(UV5) ? 0x474000UL :					\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT	26
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK	0x000ffffffc000000UL
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_SHFT	52
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_MASK	0x03f0000000000000UL
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_SHFT	63
#घोषणा UVYH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK (			\
	is_uv(UV5) ? 0x000ffffffc000000UL :				\
	0)
#घोषणा UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT (			\
	is_uv(UV5) ? 26 :						\
	-1)

जोड़ uvh_rh10_gam_mmioh_overlay_config1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                   UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0                     */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0 (				\
	is_uv(UV5) ? 0x473800UL :					\
	0)

#घोषणा UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0_DEPTH (			\
	is_uv(UV5) ? 128 :						\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_SHFT	0
#घोषणा UVYH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_MASK	0x000000000000007fUL


जोड़ uvh_rh10_gam_mmioh_redirect_config0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                   UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1                     */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1 (				\
	is_uv(UV5) ? 0x474800UL :					\
	0)

#घोषणा UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1_DEPTH (			\
	is_uv(UV5) ? 128 :						\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_SHFT	0
#घोषणा UVYH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_MASK	0x000000000000007fUL


जोड़ uvh_rh10_gam_mmioh_redirect_config1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:7;			/* RW */
		अचिन्हित दीर्घ	rsvd_7_63:57;
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                     UVH_RH10_GAM_MMR_OVERLAY_CONFIG                       */
/* ========================================================================= */
#घोषणा UVH_RH10_GAM_MMR_OVERLAY_CONFIG (				\
	is_uv(UV5) ? 0x470090UL :					\
	0)


/* UVYH common defines */
#घोषणा UVYH_RH10_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT	25
#घोषणा UVYH_RH10_GAM_MMR_OVERLAY_CONFIG_BASE_MASK	0x000ffffffe000000UL
#घोषणा UVYH_RH10_GAM_MMR_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVYH_RH10_GAM_MMR_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH10_GAM_MMR_OVERLAY_CONFIG_BASE_MASK (			\
	is_uv(UV5) ? 0x000ffffffe000000UL :				\
	0)
#घोषणा UVH_RH10_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT (			\
	is_uv(UV5) ? 25 :						\
	-1)

जोड़ uvh_rh10_gam_mmr_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh10_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	undef_52_62:11;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_rh10_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	undef_52_62:11;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rh10_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	undef_0_24:25;			/* Undefined */
		अचिन्हित दीर्घ	base:27;			/* RW */
		अचिन्हित दीर्घ	undef_52_62:11;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s5;
पूर्ण;

/* ========================================================================= */
/*                        UVH_RH_GAM_ADDR_MAP_CONFIG                         */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ADDR_MAP_CONFIG (					\
	is_uv(UV4) ? 0x480000UL :					\
	is_uv(UV3) ? 0x1600000UL :					\
	is_uv(UV2) ? 0x1600000UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ADDR_MAP_CONFIG_N_SKT_SHFT		6
#घोषणा UVXH_RH_GAM_ADDR_MAP_CONFIG_N_SKT_MASK		0x00000000000003c0UL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_ADDR_MAP_CONFIG_M_SKT_SHFT		0
#घोषणा UV3H_RH_GAM_ADDR_MAP_CONFIG_M_SKT_MASK		0x000000000000003fUL

/* UV2 unique defines */
#घोषणा UV2H_RH_GAM_ADDR_MAP_CONFIG_M_SKT_SHFT		0
#घोषणा UV2H_RH_GAM_ADDR_MAP_CONFIG_M_SKT_MASK		0x000000000000003fUL


जोड़ uvh_rh_gam_addr_map_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_5:6;
		अचिन्हित दीर्घ	n_skt:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_10_63:54;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_5:6;
		अचिन्हित दीर्घ	n_skt:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_10_63:54;
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_5:6;
		अचिन्हित दीर्घ	n_skt:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_10_63:54;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	m_skt:6;			/* RW */
		अचिन्हित दीर्घ	n_skt:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_10_63:54;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_addr_map_config_s अणु
		अचिन्हित दीर्घ	m_skt:6;			/* RW */
		अचिन्हित दीर्घ	n_skt:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_10_63:54;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_0_OVERLAY_CONFIG                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_0_OVERLAY_CONFIG (				\
	is_uv(UV4) ? 0x4800c8UL :					\
	is_uv(UV3) ? 0x16000c8UL :					\
	is_uv(UV2) ? 0x16000c8UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_BASE_SHFT	24
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_BASE_MASK	0x00000000ff000000UL
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_M_ALIAS_SHFT	48
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_M_ALIAS_MASK	0x001f000000000000UL
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVXH_RH_GAM_ALIAS_0_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL


जोड़ uvh_rh_gam_alias_0_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_0_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_0_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_0_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_0_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_0_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG                     */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG (				\
	is_uv(UV4) ? 0x4800d0UL :					\
	is_uv(UV3) ? 0x16000d0UL :					\
	is_uv(UV2) ? 0x16000d0UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG_DEST_BASE_SHFT 24
#घोषणा UVXH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG_DEST_BASE_MASK 0x00003fffff000000UL


जोड़ uvh_rh_gam_alias_0_redirect_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_0_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_0_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_0_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_0_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_0_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_1_OVERLAY_CONFIG                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_1_OVERLAY_CONFIG (				\
	is_uv(UV4) ? 0x4800d8UL :					\
	is_uv(UV3) ? 0x16000d8UL :					\
	is_uv(UV2) ? 0x16000d8UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_BASE_SHFT	24
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_BASE_MASK	0x00000000ff000000UL
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_M_ALIAS_SHFT	48
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_M_ALIAS_MASK	0x001f000000000000UL
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVXH_RH_GAM_ALIAS_1_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL


जोड़ uvh_rh_gam_alias_1_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_1_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_1_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_1_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_1_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_1_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_1_REसूचीECT_CONFIG                     */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_1_REसूचीECT_CONFIG (				\
	is_uv(UV4) ? 0x4800e0UL :					\
	is_uv(UV3) ? 0x16000e0UL :					\
	is_uv(UV2) ? 0x16000e0UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_1_REसूचीECT_CONFIG_DEST_BASE_SHFT 24
#घोषणा UVXH_RH_GAM_ALIAS_1_REसूचीECT_CONFIG_DEST_BASE_MASK 0x00003fffff000000UL


जोड़ uvh_rh_gam_alias_1_redirect_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_1_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_1_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_1_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_1_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_1_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_2_OVERLAY_CONFIG                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_2_OVERLAY_CONFIG (				\
	is_uv(UV4) ? 0x4800e8UL :					\
	is_uv(UV3) ? 0x16000e8UL :					\
	is_uv(UV2) ? 0x16000e8UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_BASE_SHFT	24
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_BASE_MASK	0x00000000ff000000UL
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_M_ALIAS_SHFT	48
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_M_ALIAS_MASK	0x001f000000000000UL
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVXH_RH_GAM_ALIAS_2_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL


जोड़ uvh_rh_gam_alias_2_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_2_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_2_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_2_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_2_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_2_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	base:8;				/* RW */
		अचिन्हित दीर्घ	rsvd_32_47:16;
		अचिन्हित दीर्घ	m_alias:5;			/* RW */
		अचिन्हित दीर्घ	rsvd_53_62:10;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_ALIAS_2_REसूचीECT_CONFIG                     */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS_2_REसूचीECT_CONFIG (				\
	is_uv(UV4) ? 0x4800f0UL :					\
	is_uv(UV3) ? 0x16000f0UL :					\
	is_uv(UV2) ? 0x16000f0UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_ALIAS_2_REसूचीECT_CONFIG_DEST_BASE_SHFT 24
#घोषणा UVXH_RH_GAM_ALIAS_2_REसूचीECT_CONFIG_DEST_BASE_MASK 0x00003fffff000000UL


जोड़ uvh_rh_gam_alias_2_redirect_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_alias_2_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_alias_2_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_alias_2_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_alias_2_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_alias_2_redirect_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_23:24;
		अचिन्हित दीर्घ	dest_base:22;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_63:18;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                      UVH_RH_GAM_GRU_OVERLAY_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG (					\
	is_uv(UV4) ? 0x480010UL :					\
	is_uv(UV3) ? 0x1600010UL :					\
	is_uv(UV2) ? 0x1600010UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_GRU_OVERLAY_CONFIG_N_GRU_SHFT	52
#घोषणा UVXH_RH_GAM_GRU_OVERLAY_CONFIG_N_GRU_MASK	0x00f0000000000000UL
#घोषणा UVXH_RH_GAM_GRU_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVXH_RH_GAM_GRU_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	26
#घोषणा UV4AH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x000ffffffc000000UL

/* UV4 unique defines */
#घोषणा UV4H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	26
#घोषणा UV4H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x00003ffffc000000UL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	28
#घोषणा UV3H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x00003ffff0000000UL
#घोषणा UV3H_RH_GAM_GRU_OVERLAY_CONFIG_MODE_SHFT	62
#घोषणा UV3H_RH_GAM_GRU_OVERLAY_CONFIG_MODE_MASK	0x4000000000000000UL

/* UV2 unique defines */
#घोषणा UV2H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	28
#घोषणा UV2H_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x00003ffff0000000UL

#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK (			\
	is_uv(UV4A) ? 0x000ffffffc000000UL :				\
	is_uv(UV4) ? 0x00003ffffc000000UL :				\
	is_uv(UV3) ? 0x00003ffff0000000UL :				\
	is_uv(UV2) ? 0x00003ffff0000000UL :				\
	0)
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT (			\
	is_uv(UV4) ? 26 :						\
	is_uv(UV3) ? 28 :						\
	is_uv(UV2) ? 28 :						\
	-1)

जोड़ uvh_rh_gam_gru_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_45:46;
		अचिन्हित दीर्घ	rsvd_46_51:6;
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_45:46;
		अचिन्हित दीर्घ	rsvd_46_51:6;
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4A unique काष्ठा */
	काष्ठा uv4ah_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_24:25;
		अचिन्हित दीर्घ	undef_25:1;			/* Undefined */
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4a;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_24:25;
		अचिन्हित दीर्घ	undef_25:1;			/* Undefined */
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_51:6;
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_27:28;
		अचिन्हित दीर्घ	base:18;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_51:6;
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_61:6;
		अचिन्हित दीर्घ	mode:1;				/* RW */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_gru_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_27:28;
		अचिन्हित दीर्घ	base:18;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_51:6;
		अचिन्हित दीर्घ	n_gru:4;			/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                     UVH_RH_GAM_MMIOH_OVERLAY_CONFIG                       */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG (				\
	is_uv(UV2) ? 0x1600030UL :					\
	0)



/* UV2 unique defines */
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_BASE_SHFT	27
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_BASE_MASK	0x00003ffff8000000UL
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_M_IO_SHFT	46
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_M_IO_MASK	0x000fc00000000000UL
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_N_IO_SHFT	52
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_N_IO_MASK	0x00f0000000000000UL
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG_BASE_SHFT (			\
	is_uv(UV2) ? 27 :						\
	uv_undefined("UVH_RH_GAM_MMIOH_OVERLAY_CONFIG_BASE_SHFT"))

जोड़ uvh_rh_gam_mmioh_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmioh_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_26:27;
		अचिन्हित दीर्घ	base:19;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;				/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmioh_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_26:27;
		अचिन्हित दीर्घ	base:19;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;				/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_mmioh_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_26:27;
		अचिन्हित दीर्घ	base:19;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;				/* RW */
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                     UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0 (				\
	is_uv(UV4) ? 0x483000UL :					\
	is_uv(UV3) ? 0x1603000UL :					\
	0)

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT	26
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK	0x000ffffffc000000UL
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_SHFT	52
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_MASK	0x03f0000000000000UL
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_SHFT	63
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_MASK	0x8000000000000000UL

/* UV4 unique defines */
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT	26
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK	0x00003ffffc000000UL
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_SHFT	46
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_MASK	0x000fc00000000000UL
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_SHFT	63
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_MASK	0x8000000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT	26
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK	0x00003ffffc000000UL
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_SHFT	46
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_M_IO_MASK	0x000fc00000000000UL
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_SHFT	63
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG0_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK (			\
	is_uv(UV4A) ? 0x000ffffffc000000UL :				\
	is_uv(UV4) ? 0x00003ffffc000000UL :				\
	is_uv(UV3) ? 0x00003ffffc000000UL :				\
	0)
#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT (			\
	is_uv(UV4) ? 26 :						\
	is_uv(UV3) ? 26 :						\
	-1)

जोड़ uvh_rh_gam_mmioh_overlay_config0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4A unique काष्ठा */
	काष्ठा uv4ah_rh_gam_mmioh_overlay_config0_mmr_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4a;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_mmioh_overlay_config0_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;
पूर्ण;

/* ========================================================================= */
/*                     UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1 (				\
	is_uv(UV4) ? 0x484000UL :					\
	is_uv(UV3) ? 0x1604000UL :					\
	0)

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT	26
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK	0x000ffffffc000000UL
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_SHFT	52
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_MASK	0x03f0000000000000UL
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_SHFT	63
#घोषणा UV4AH_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_MASK	0x8000000000000000UL

/* UV4 unique defines */
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT	26
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK	0x00003ffffc000000UL
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_SHFT	46
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_MASK	0x000fc00000000000UL
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_SHFT	63
#घोषणा UV4H_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_MASK	0x8000000000000000UL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT	26
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK	0x00003ffffc000000UL
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_SHFT	46
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_M_IO_MASK	0x000fc00000000000UL
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_SHFT	63
#घोषणा UV3H_RH_GAM_MMIOH_OVERLAY_CONFIG1_ENABLE_MASK	0x8000000000000000UL

#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK (			\
	is_uv(UV4A) ? 0x000ffffffc000000UL : \
	is_uv(UV4) ? 0x00003ffffc000000UL :				\
	is_uv(UV3) ? 0x00003ffffc000000UL :				\
	0)
#घोषणा UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT (			\
	is_uv(UV4) ? 26 :						\
	is_uv(UV3) ? 26 :						\
	-1)

जोड़ uvh_rh_gam_mmioh_overlay_config1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4A unique काष्ठा */
	काष्ठा uv4ah_rh_gam_mmioh_overlay_config1_mmr_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:26;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	undef_62:1;			/* Undefined */
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4a;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_mmioh_overlay_config1_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	m_io:6;				/* RW */
		अचिन्हित दीर्घ	n_io:4;
		अचिन्हित दीर्घ	rsvd_56_62:7;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG0                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG0 (				\
	is_uv(UV4) ? 0x483800UL :					\
	is_uv(UV3) ? 0x1603800UL :					\
	0)

#घोषणा UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_DEPTH (			\
	is_uv(UV4) ? 128 :						\
	is_uv(UV3) ? 128 :						\
	0)

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_SHFT	0
#घोषणा UV4AH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_MASK	0x0000000000000fffUL

/* UV4 unique defines */
#घोषणा UV4H_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_SHFT	0
#घोषणा UV4H_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_MASK	0x0000000000007fffUL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_SHFT	0
#घोषणा UV3H_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_MASK	0x0000000000007fffUL


जोड़ uvh_rh_gam_mmioh_redirect_config0_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण sx;

	काष्ठा uv4ah_rh_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:12;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_63:52;
	पूर्ण s4a;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_mmioh_redirect_config0_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s3;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG1                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG1 (				\
	is_uv(UV4) ? 0x484800UL :					\
	is_uv(UV3) ? 0x1604800UL :					\
	0)

#घोषणा UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG1_DEPTH (			\
	is_uv(UV4) ? 128 :						\
	is_uv(UV3) ? 128 :						\
	0)

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_SHFT	0
#घोषणा UV4AH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_NASID_MASK	0x0000000000000fffUL

/* UV4 unique defines */
#घोषणा UV4H_RH_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_SHFT	0
#घोषणा UV4H_RH_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_MASK	0x0000000000007fffUL

/* UV3 unique defines */
#घोषणा UV3H_RH_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_SHFT	0
#घोषणा UV3H_RH_GAM_MMIOH_REसूचीECT_CONFIG1_NASID_MASK	0x0000000000007fffUL


जोड़ uvh_rh_gam_mmioh_redirect_config1_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण sx;

	काष्ठा uv4ah_rh_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:12;			/* RW */
		अचिन्हित दीर्घ	rsvd_12_63:52;
	पूर्ण s4a;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_mmioh_redirect_config1_s अणु
		अचिन्हित दीर्घ	nasid:15;			/* RW */
		अचिन्हित दीर्घ	rsvd_15_63:49;
	पूर्ण s3;
पूर्ण;

/* ========================================================================= */
/*                      UVH_RH_GAM_MMR_OVERLAY_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG (					\
	is_uv(UV4) ? 0x480028UL :					\
	is_uv(UV3) ? 0x1600028UL :					\
	is_uv(UV2) ? 0x1600028UL :					\
	0)


/* UVXH common defines */
#घोषणा UVXH_RH_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT	26
#घोषणा UVXH_RH_GAM_MMR_OVERLAY_CONFIG_BASE_MASK (			\
	is_uv(UV4A) ? 0x000ffffffc000000UL :				\
	is_uv(UV4) ? 0x00003ffffc000000UL :				\
	is_uv(UV3) ? 0x00003ffffc000000UL :				\
	is_uv(UV2) ? 0x00003ffffc000000UL :				\
	0)
#घोषणा UVXH_RH_GAM_MMR_OVERLAY_CONFIG_ENABLE_SHFT	63
#घोषणा UVXH_RH_GAM_MMR_OVERLAY_CONFIG_ENABLE_MASK	0x8000000000000000UL

/* UV4A unique defines */
#घोषणा UV4AH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT	26
#घोषणा UV4AH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK	0x000ffffffc000000UL

#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_BASE_MASK (			\
	is_uv(UV4A) ? 0x000ffffffc000000UL :				\
	is_uv(UV4) ? 0x00003ffffc000000UL :				\
	is_uv(UV3) ? 0x00003ffffc000000UL :				\
	is_uv(UV2) ? 0x00003ffffc000000UL :				\
	0)

#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT (			\
	is_uv(UV4) ? 26 :						\
	is_uv(UV3) ? 26 :						\
	is_uv(UV2) ? 26 :						\
	-1)

जोड़ uvh_rh_gam_mmr_overlay_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rh_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_62:17;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_rh_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_62:17;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण sx;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rh_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_62:17;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rh_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_62:17;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rh_gam_mmr_overlay_config_s अणु
		अचिन्हित दीर्घ	rsvd_0_25:26;
		अचिन्हित दीर्घ	base:20;			/* RW */
		अचिन्हित दीर्घ	rsvd_46_62:17;
		अचिन्हित दीर्घ	enable:1;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                                 UVH_RTC                                   */
/* ========================================================================= */
#घोषणा UVH_RTC (							\
	is_uv(UV5) ? 0xe0000UL :					\
	is_uv(UV4) ? 0xe0000UL :					\
	is_uv(UV3) ? 0x340000UL :					\
	is_uv(UV2) ? 0x340000UL :					\
	0)

/* UVH common defines*/
#घोषणा UVH_RTC_REAL_TIME_CLOCK_SHFT			0
#घोषणा UVH_RTC_REAL_TIME_CLOCK_MASK			0x00ffffffffffffffUL


जोड़ uvh_rtc_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rtc_s अणु
		अचिन्हित दीर्घ	real_समय_घड़ी:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rtc_s अणु
		अचिन्हित दीर्घ	real_समय_घड़ी:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rtc_s अणु
		अचिन्हित दीर्घ	real_समय_घड़ी:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rtc_s अणु
		अचिन्हित दीर्घ	real_समय_घड़ी:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rtc_s अणु
		अचिन्हित दीर्घ	real_समय_घड़ी:56;		/* RW */
		अचिन्हित दीर्घ	rsvd_56_63:8;
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                           UVH_RTC1_INT_CONFIG                             */
/* ========================================================================= */
#घोषणा UVH_RTC1_INT_CONFIG 0x615c0UL

/* UVH common defines*/
#घोषणा UVH_RTC1_INT_CONFIG_VECTOR_SHFT			0
#घोषणा UVH_RTC1_INT_CONFIG_VECTOR_MASK			0x00000000000000ffUL
#घोषणा UVH_RTC1_INT_CONFIG_DM_SHFT			8
#घोषणा UVH_RTC1_INT_CONFIG_DM_MASK			0x0000000000000700UL
#घोषणा UVH_RTC1_INT_CONFIG_DESTMODE_SHFT		11
#घोषणा UVH_RTC1_INT_CONFIG_DESTMODE_MASK		0x0000000000000800UL
#घोषणा UVH_RTC1_INT_CONFIG_STATUS_SHFT			12
#घोषणा UVH_RTC1_INT_CONFIG_STATUS_MASK			0x0000000000001000UL
#घोषणा UVH_RTC1_INT_CONFIG_P_SHFT			13
#घोषणा UVH_RTC1_INT_CONFIG_P_MASK			0x0000000000002000UL
#घोषणा UVH_RTC1_INT_CONFIG_T_SHFT			15
#घोषणा UVH_RTC1_INT_CONFIG_T_MASK			0x0000000000008000UL
#घोषणा UVH_RTC1_INT_CONFIG_M_SHFT			16
#घोषणा UVH_RTC1_INT_CONFIG_M_MASK			0x0000000000010000UL
#घोषणा UVH_RTC1_INT_CONFIG_APIC_ID_SHFT		32
#घोषणा UVH_RTC1_INT_CONFIG_APIC_ID_MASK		0xffffffff00000000UL


जोड़ uvh_rtc1_पूर्णांक_config_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_rtc1_पूर्णांक_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_rtc1_पूर्णांक_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_rtc1_पूर्णांक_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_rtc1_पूर्णांक_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_rtc1_पूर्णांक_config_s अणु
		अचिन्हित दीर्घ	vector_:8;			/* RW */
		अचिन्हित दीर्घ	dm:3;				/* RW */
		अचिन्हित दीर्घ	desपंचांगode:1;			/* RW */
		अचिन्हित दीर्घ	status:1;			/* RO */
		अचिन्हित दीर्घ	p:1;				/* RO */
		अचिन्हित दीर्घ	rsvd_14:1;
		अचिन्हित दीर्घ	t:1;				/* RO */
		अचिन्हित दीर्घ	m:1;				/* RW */
		अचिन्हित दीर्घ	rsvd_17_31:15;
		अचिन्हित दीर्घ	apic_id:32;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                               UVH_SCRATCH5                                */
/* ========================================================================= */
#घोषणा UVH_SCRATCH5 (							\
	is_uv(UV5) ? 0xb0200UL :					\
	is_uv(UV4) ? 0xb0200UL :					\
	is_uv(UV3) ? 0x2d0200UL :					\
	is_uv(UV2) ? 0x2d0200UL :					\
	0)
#घोषणा UV5H_SCRATCH5 0xb0200UL
#घोषणा UV4H_SCRATCH5 0xb0200UL
#घोषणा UV3H_SCRATCH5 0x2d0200UL
#घोषणा UV2H_SCRATCH5 0x2d0200UL

/* UVH common defines*/
#घोषणा UVH_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UVH_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UVXH common defines */
#घोषणा UVXH_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UVXH_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UVYH common defines */
#घोषणा UVYH_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UVYH_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UV5 unique defines */
#घोषणा UV5H_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UV5H_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UV4 unique defines */
#घोषणा UV4H_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UV4H_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UV3 unique defines */
#घोषणा UV3H_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UV3H_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL

/* UV2 unique defines */
#घोषणा UV2H_SCRATCH5_SCRATCH5_SHFT			0
#घोषणा UV2H_SCRATCH5_SCRATCH5_MASK			0xffffffffffffffffUL


जोड़ uvh_scratch5_u अणु
	अचिन्हित दीर्घ	v;

	/* UVH common काष्ठा */
	काष्ठा uvh_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण s;

	/* UVXH common काष्ठा */
	काष्ठा uvxh_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण sx;

	/* UVYH common काष्ठा */
	काष्ठा uvyh_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण sy;

	/* UV5 unique काष्ठा */
	काष्ठा uv5h_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण s5;

	/* UV4 unique काष्ठा */
	काष्ठा uv4h_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण s4;

	/* UV3 unique काष्ठा */
	काष्ठा uv3h_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण s3;

	/* UV2 unique काष्ठा */
	काष्ठा uv2h_scratch5_s अणु
		अचिन्हित दीर्घ	scratch5:64;			/* RW */
	पूर्ण s2;
पूर्ण;

/* ========================================================================= */
/*                            UVH_SCRATCH5_ALIAS                             */
/* ========================================================================= */
#घोषणा UVH_SCRATCH5_ALIAS (						\
	is_uv(UV5) ? 0xb0208UL :					\
	is_uv(UV4) ? 0xb0208UL :					\
	is_uv(UV3) ? 0x2d0208UL :					\
	is_uv(UV2) ? 0x2d0208UL :					\
	0)
#घोषणा UV5H_SCRATCH5_ALIAS 0xb0208UL
#घोषणा UV4H_SCRATCH5_ALIAS 0xb0208UL
#घोषणा UV3H_SCRATCH5_ALIAS 0x2d0208UL
#घोषणा UV2H_SCRATCH5_ALIAS 0x2d0208UL


/* ========================================================================= */
/*                           UVH_SCRATCH5_ALIAS_2                            */
/* ========================================================================= */
#घोषणा UVH_SCRATCH5_ALIAS_2 (						\
	is_uv(UV5) ? 0xb0210UL :					\
	is_uv(UV4) ? 0xb0210UL :					\
	is_uv(UV3) ? 0x2d0210UL :					\
	is_uv(UV2) ? 0x2d0210UL :					\
	0)
#घोषणा UV5H_SCRATCH5_ALIAS_2 0xb0210UL
#घोषणा UV4H_SCRATCH5_ALIAS_2 0xb0210UL
#घोषणा UV3H_SCRATCH5_ALIAS_2 0x2d0210UL
#घोषणा UV2H_SCRATCH5_ALIAS_2 0x2d0210UL



#पूर्ण_अगर /* _ASM_X86_UV_UV_MMRS_H */
