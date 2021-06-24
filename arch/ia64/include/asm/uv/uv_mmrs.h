<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV MMR definitions
 *
 * Copyright (C) 2007-2008 Silicon Graphics, Inc. All rights reserved.
 */

#अगर_अघोषित _ASM_IA64_UV_UV_MMRS_H
#घोषणा _ASM_IA64_UV_UV_MMRS_H

#घोषणा UV_MMR_ENABLE		(1UL << 63)

/* ========================================================================= */
/*                           UVH_BAU_DATA_CONFIG                             */
/* ========================================================================= */
#घोषणा UVH_BAU_DATA_CONFIG 0x61680UL
#घोषणा UVH_BAU_DATA_CONFIG_32 0x0438

#घोषणा UVH_BAU_DATA_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_BAU_DATA_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_BAU_DATA_CONFIG_DM_SHFT 8
#घोषणा UVH_BAU_DATA_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_BAU_DATA_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_BAU_DATA_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_BAU_DATA_CONFIG_STATUS_SHFT 12
#घोषणा UVH_BAU_DATA_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_BAU_DATA_CONFIG_P_SHFT 13
#घोषणा UVH_BAU_DATA_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_BAU_DATA_CONFIG_T_SHFT 15
#घोषणा UVH_BAU_DATA_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_BAU_DATA_CONFIG_M_SHFT 16
#घोषणा UVH_BAU_DATA_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_BAU_DATA_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_BAU_DATA_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_bau_data_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_bau_data_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                           UVH_EVENT_OCCURRED0                             */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED0 0x70000UL
#घोषणा UVH_EVENT_OCCURRED0_32 0x005e8

#घोषणा UVH_EVENT_OCCURRED0_LB_HCERR_SHFT 0
#घोषणा UVH_EVENT_OCCURRED0_LB_HCERR_MASK 0x0000000000000001UL
#घोषणा UVH_EVENT_OCCURRED0_GR0_HCERR_SHFT 1
#घोषणा UVH_EVENT_OCCURRED0_GR0_HCERR_MASK 0x0000000000000002UL
#घोषणा UVH_EVENT_OCCURRED0_GR1_HCERR_SHFT 2
#घोषणा UVH_EVENT_OCCURRED0_GR1_HCERR_MASK 0x0000000000000004UL
#घोषणा UVH_EVENT_OCCURRED0_LH_HCERR_SHFT 3
#घोषणा UVH_EVENT_OCCURRED0_LH_HCERR_MASK 0x0000000000000008UL
#घोषणा UVH_EVENT_OCCURRED0_RH_HCERR_SHFT 4
#घोषणा UVH_EVENT_OCCURRED0_RH_HCERR_MASK 0x0000000000000010UL
#घोषणा UVH_EVENT_OCCURRED0_XN_HCERR_SHFT 5
#घोषणा UVH_EVENT_OCCURRED0_XN_HCERR_MASK 0x0000000000000020UL
#घोषणा UVH_EVENT_OCCURRED0_SI_HCERR_SHFT 6
#घोषणा UVH_EVENT_OCCURRED0_SI_HCERR_MASK 0x0000000000000040UL
#घोषणा UVH_EVENT_OCCURRED0_LB_AOERR0_SHFT 7
#घोषणा UVH_EVENT_OCCURRED0_LB_AOERR0_MASK 0x0000000000000080UL
#घोषणा UVH_EVENT_OCCURRED0_GR0_AOERR0_SHFT 8
#घोषणा UVH_EVENT_OCCURRED0_GR0_AOERR0_MASK 0x0000000000000100UL
#घोषणा UVH_EVENT_OCCURRED0_GR1_AOERR0_SHFT 9
#घोषणा UVH_EVENT_OCCURRED0_GR1_AOERR0_MASK 0x0000000000000200UL
#घोषणा UVH_EVENT_OCCURRED0_LH_AOERR0_SHFT 10
#घोषणा UVH_EVENT_OCCURRED0_LH_AOERR0_MASK 0x0000000000000400UL
#घोषणा UVH_EVENT_OCCURRED0_RH_AOERR0_SHFT 11
#घोषणा UVH_EVENT_OCCURRED0_RH_AOERR0_MASK 0x0000000000000800UL
#घोषणा UVH_EVENT_OCCURRED0_XN_AOERR0_SHFT 12
#घोषणा UVH_EVENT_OCCURRED0_XN_AOERR0_MASK 0x0000000000001000UL
#घोषणा UVH_EVENT_OCCURRED0_SI_AOERR0_SHFT 13
#घोषणा UVH_EVENT_OCCURRED0_SI_AOERR0_MASK 0x0000000000002000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_AOERR1_SHFT 14
#घोषणा UVH_EVENT_OCCURRED0_LB_AOERR1_MASK 0x0000000000004000UL
#घोषणा UVH_EVENT_OCCURRED0_GR0_AOERR1_SHFT 15
#घोषणा UVH_EVENT_OCCURRED0_GR0_AOERR1_MASK 0x0000000000008000UL
#घोषणा UVH_EVENT_OCCURRED0_GR1_AOERR1_SHFT 16
#घोषणा UVH_EVENT_OCCURRED0_GR1_AOERR1_MASK 0x0000000000010000UL
#घोषणा UVH_EVENT_OCCURRED0_LH_AOERR1_SHFT 17
#घोषणा UVH_EVENT_OCCURRED0_LH_AOERR1_MASK 0x0000000000020000UL
#घोषणा UVH_EVENT_OCCURRED0_RH_AOERR1_SHFT 18
#घोषणा UVH_EVENT_OCCURRED0_RH_AOERR1_MASK 0x0000000000040000UL
#घोषणा UVH_EVENT_OCCURRED0_XN_AOERR1_SHFT 19
#घोषणा UVH_EVENT_OCCURRED0_XN_AOERR1_MASK 0x0000000000080000UL
#घोषणा UVH_EVENT_OCCURRED0_SI_AOERR1_SHFT 20
#घोषणा UVH_EVENT_OCCURRED0_SI_AOERR1_MASK 0x0000000000100000UL
#घोषणा UVH_EVENT_OCCURRED0_RH_VPI_INT_SHFT 21
#घोषणा UVH_EVENT_OCCURRED0_RH_VPI_INT_MASK 0x0000000000200000UL
#घोषणा UVH_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_SHFT 22
#घोषणा UVH_EVENT_OCCURRED0_SYSTEM_SHUTDOWN_INT_MASK 0x0000000000400000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_0_SHFT 23
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_0_MASK 0x0000000000800000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_1_SHFT 24
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_1_MASK 0x0000000001000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_2_SHFT 25
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_2_MASK 0x0000000002000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_3_SHFT 26
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_3_MASK 0x0000000004000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_4_SHFT 27
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_4_MASK 0x0000000008000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_5_SHFT 28
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_5_MASK 0x0000000010000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_6_SHFT 29
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_6_MASK 0x0000000020000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_7_SHFT 30
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_7_MASK 0x0000000040000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_8_SHFT 31
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_8_MASK 0x0000000080000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_9_SHFT 32
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_9_MASK 0x0000000100000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_10_SHFT 33
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_10_MASK 0x0000000200000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_11_SHFT 34
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_11_MASK 0x0000000400000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_12_SHFT 35
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_12_MASK 0x0000000800000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_13_SHFT 36
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_13_MASK 0x0000001000000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_14_SHFT 37
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_14_MASK 0x0000002000000000UL
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_15_SHFT 38
#घोषणा UVH_EVENT_OCCURRED0_LB_IRQ_INT_15_MASK 0x0000004000000000UL
#घोषणा UVH_EVENT_OCCURRED0_L1_NMI_INT_SHFT 39
#घोषणा UVH_EVENT_OCCURRED0_L1_NMI_INT_MASK 0x0000008000000000UL
#घोषणा UVH_EVENT_OCCURRED0_STOP_CLOCK_SHFT 40
#घोषणा UVH_EVENT_OCCURRED0_STOP_CLOCK_MASK 0x0000010000000000UL
#घोषणा UVH_EVENT_OCCURRED0_ASIC_TO_L1_SHFT 41
#घोषणा UVH_EVENT_OCCURRED0_ASIC_TO_L1_MASK 0x0000020000000000UL
#घोषणा UVH_EVENT_OCCURRED0_L1_TO_ASIC_SHFT 42
#घोषणा UVH_EVENT_OCCURRED0_L1_TO_ASIC_MASK 0x0000040000000000UL
#घोषणा UVH_EVENT_OCCURRED0_LTC_INT_SHFT 43
#घोषणा UVH_EVENT_OCCURRED0_LTC_INT_MASK 0x0000080000000000UL
#घोषणा UVH_EVENT_OCCURRED0_LA_SEQ_TRIGGER_SHFT 44
#घोषणा UVH_EVENT_OCCURRED0_LA_SEQ_TRIGGER_MASK 0x0000100000000000UL
#घोषणा UVH_EVENT_OCCURRED0_IPI_INT_SHFT 45
#घोषणा UVH_EVENT_OCCURRED0_IPI_INT_MASK 0x0000200000000000UL
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT0_SHFT 46
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT0_MASK 0x0000400000000000UL
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT1_SHFT 47
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT1_MASK 0x0000800000000000UL
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT2_SHFT 48
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT2_MASK 0x0001000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT3_SHFT 49
#घोषणा UVH_EVENT_OCCURRED0_EXTIO_INT3_MASK 0x0002000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_PROखाता_INT_SHFT 50
#घोषणा UVH_EVENT_OCCURRED0_PROखाता_INT_MASK 0x0004000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_RTC0_SHFT 51
#घोषणा UVH_EVENT_OCCURRED0_RTC0_MASK 0x0008000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_RTC1_SHFT 52
#घोषणा UVH_EVENT_OCCURRED0_RTC1_MASK 0x0010000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_RTC2_SHFT 53
#घोषणा UVH_EVENT_OCCURRED0_RTC2_MASK 0x0020000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_RTC3_SHFT 54
#घोषणा UVH_EVENT_OCCURRED0_RTC3_MASK 0x0040000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_BAU_DATA_SHFT 55
#घोषणा UVH_EVENT_OCCURRED0_BAU_DATA_MASK 0x0080000000000000UL
#घोषणा UVH_EVENT_OCCURRED0_POWER_MANAGEMENT_REQ_SHFT 56
#घोषणा UVH_EVENT_OCCURRED0_POWER_MANAGEMENT_REQ_MASK 0x0100000000000000UL
जोड़ uvh_event_occurred0_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_event_occurred0_s अणु
	अचिन्हित दीर्घ	lb_hcerr             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr0_hcerr            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr1_hcerr            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lh_hcerr             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rh_hcerr             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	xn_hcerr             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	si_hcerr             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_aoerr0            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr0_aoerr0           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr1_aoerr0           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lh_aoerr0            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rh_aoerr0            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	xn_aoerr0            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	si_aoerr0            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_aoerr1            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr0_aoerr1           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	gr1_aoerr1           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lh_aoerr1            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rh_aoerr1            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	xn_aoerr1            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	si_aoerr1            :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rh_vpi_पूर्णांक           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	प्रणाली_shutकरोwn_पूर्णांक  :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_0         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_1         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_2         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_3         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_4         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_5         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_6         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_7         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_8         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_9         :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_10        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_11        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_12        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_13        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_14        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	lb_irq_पूर्णांक_15        :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	l1_nmi_पूर्णांक           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	stop_घड़ी           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	asic_to_l1           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	l1_to_asic           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	ltc_पूर्णांक              :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	la_seq_trigger       :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	ipi_पूर्णांक              :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	extio_पूर्णांक0           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	extio_पूर्णांक1           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	extio_पूर्णांक2           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	extio_पूर्णांक3           :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	profile_पूर्णांक          :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rtc0                 :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rtc1                 :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rtc2                 :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rtc3                 :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	bau_data             :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	घातer_management_req :  1;  /* RW, W1C */
	अचिन्हित दीर्घ	rsvd_57_63           :  7;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                        UVH_EVENT_OCCURRED0_ALIAS                          */
/* ========================================================================= */
#घोषणा UVH_EVENT_OCCURRED0_ALIAS 0x0000000000070008UL
#घोषणा UVH_EVENT_OCCURRED0_ALIAS_32 0x005f0

/* ========================================================================= */
/*                         UVH_GR0_TLB_INT0_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR0_TLB_INT0_CONFIG 0x61b00UL

#घोषणा UVH_GR0_TLB_INT0_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_GR0_TLB_INT0_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_DM_SHFT 8
#घोषणा UVH_GR0_TLB_INT0_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_GR0_TLB_INT0_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_STATUS_SHFT 12
#घोषणा UVH_GR0_TLB_INT0_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_P_SHFT 13
#घोषणा UVH_GR0_TLB_INT0_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_T_SHFT 15
#घोषणा UVH_GR0_TLB_INT0_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_M_SHFT 16
#घोषणा UVH_GR0_TLB_INT0_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_GR0_TLB_INT0_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_GR0_TLB_INT0_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_gr0_tlb_पूर्णांक0_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_gr0_tlb_पूर्णांक0_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR0_TLB_INT1_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR0_TLB_INT1_CONFIG 0x61b40UL

#घोषणा UVH_GR0_TLB_INT1_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_GR0_TLB_INT1_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_DM_SHFT 8
#घोषणा UVH_GR0_TLB_INT1_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_GR0_TLB_INT1_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_STATUS_SHFT 12
#घोषणा UVH_GR0_TLB_INT1_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_P_SHFT 13
#घोषणा UVH_GR0_TLB_INT1_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_T_SHFT 15
#घोषणा UVH_GR0_TLB_INT1_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_M_SHFT 16
#घोषणा UVH_GR0_TLB_INT1_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_GR0_TLB_INT1_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_GR0_TLB_INT1_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_gr0_tlb_पूर्णांक1_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_gr0_tlb_पूर्णांक1_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR1_TLB_INT0_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR1_TLB_INT0_CONFIG 0x61f00UL

#घोषणा UVH_GR1_TLB_INT0_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_GR1_TLB_INT0_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_DM_SHFT 8
#घोषणा UVH_GR1_TLB_INT0_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_GR1_TLB_INT0_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_STATUS_SHFT 12
#घोषणा UVH_GR1_TLB_INT0_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_P_SHFT 13
#घोषणा UVH_GR1_TLB_INT0_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_T_SHFT 15
#घोषणा UVH_GR1_TLB_INT0_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_M_SHFT 16
#घोषणा UVH_GR1_TLB_INT0_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_GR1_TLB_INT0_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_GR1_TLB_INT0_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_gr1_tlb_पूर्णांक0_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_gr1_tlb_पूर्णांक0_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                         UVH_GR1_TLB_INT1_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_GR1_TLB_INT1_CONFIG 0x61f40UL

#घोषणा UVH_GR1_TLB_INT1_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_GR1_TLB_INT1_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_DM_SHFT 8
#घोषणा UVH_GR1_TLB_INT1_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_GR1_TLB_INT1_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_STATUS_SHFT 12
#घोषणा UVH_GR1_TLB_INT1_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_P_SHFT 13
#घोषणा UVH_GR1_TLB_INT1_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_T_SHFT 15
#घोषणा UVH_GR1_TLB_INT1_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_M_SHFT 16
#घोषणा UVH_GR1_TLB_INT1_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_GR1_TLB_INT1_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_GR1_TLB_INT1_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_gr1_tlb_पूर्णांक1_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_gr1_tlb_पूर्णांक1_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                               UVH_INT_CMPB                                */
/* ========================================================================= */
#घोषणा UVH_INT_CMPB 0x22080UL

#घोषणा UVH_INT_CMPB_REAL_TIME_CMPB_SHFT 0
#घोषणा UVH_INT_CMPB_REAL_TIME_CMPB_MASK 0x00ffffffffffffffUL

जोड़ uvh_पूर्णांक_cmpb_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_पूर्णांक_cmpb_s अणु
	अचिन्हित दीर्घ	real_समय_cmpb : 56;  /* RW */
	अचिन्हित दीर्घ	rsvd_56_63     :  8;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                               UVH_INT_CMPC                                */
/* ========================================================================= */
#घोषणा UVH_INT_CMPC 0x22100UL

#घोषणा UVH_INT_CMPC_REAL_TIME_CMPC_SHFT 0
#घोषणा UVH_INT_CMPC_REAL_TIME_CMPC_MASK 0x00ffffffffffffffUL

जोड़ uvh_पूर्णांक_cmpc_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_पूर्णांक_cmpc_s अणु
	अचिन्हित दीर्घ	real_समय_cmpc : 56;  /* RW */
	अचिन्हित दीर्घ	rsvd_56_63     :  8;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                               UVH_INT_CMPD                                */
/* ========================================================================= */
#घोषणा UVH_INT_CMPD 0x22180UL

#घोषणा UVH_INT_CMPD_REAL_TIME_CMPD_SHFT 0
#घोषणा UVH_INT_CMPD_REAL_TIME_CMPD_MASK 0x00ffffffffffffffUL

जोड़ uvh_पूर्णांक_cmpd_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_पूर्णांक_cmpd_s अणु
	अचिन्हित दीर्घ	real_समय_cmpd : 56;  /* RW */
	अचिन्हित दीर्घ	rsvd_56_63     :  8;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                               UVH_NODE_ID                                 */
/* ========================================================================= */
#घोषणा UVH_NODE_ID 0x0UL

#घोषणा UVH_NODE_ID_FORCE1_SHFT 0
#घोषणा UVH_NODE_ID_FORCE1_MASK 0x0000000000000001UL
#घोषणा UVH_NODE_ID_MANUFACTURER_SHFT 1
#घोषणा UVH_NODE_ID_MANUFACTURER_MASK 0x0000000000000ffeUL
#घोषणा UVH_NODE_ID_PART_NUMBER_SHFT 12
#घोषणा UVH_NODE_ID_PART_NUMBER_MASK 0x000000000ffff000UL
#घोषणा UVH_NODE_ID_REVISION_SHFT 28
#घोषणा UVH_NODE_ID_REVISION_MASK 0x00000000f0000000UL
#घोषणा UVH_NODE_ID_NODE_ID_SHFT 32
#घोषणा UVH_NODE_ID_NODE_ID_MASK 0x00007fff00000000UL
#घोषणा UVH_NODE_ID_NODES_PER_BIT_SHFT 48
#घोषणा UVH_NODE_ID_NODES_PER_BIT_MASK 0x007f000000000000UL
#घोषणा UVH_NODE_ID_NI_PORT_SHFT 56
#घोषणा UVH_NODE_ID_NI_PORT_MASK 0x0f00000000000000UL

जोड़ uvh_node_id_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_node_id_s अणु
	अचिन्हित दीर्घ	क्रमce1        :  1;  /* RO */
	अचिन्हित दीर्घ	manufacturer  : 11;  /* RO */
	अचिन्हित दीर्घ	part_number   : 16;  /* RO */
	अचिन्हित दीर्घ	revision      :  4;  /* RO */
	अचिन्हित दीर्घ	node_id       : 15;  /* RW */
	अचिन्हित दीर्घ	rsvd_47       :  1;  /*    */
	अचिन्हित दीर्घ	nodes_per_bit :  7;  /* RW */
	अचिन्हित दीर्घ	rsvd_55       :  1;  /*    */
	अचिन्हित दीर्घ	ni_port       :  4;  /* RO */
	अचिन्हित दीर्घ	rsvd_60_63    :  4;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR                  */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR 0x16000d0UL

#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR_DEST_BASE_SHFT 24
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR_DEST_BASE_MASK 0x00003fffff000000UL

जोड़ uvh_rh_gam_alias210_redirect_config_0_mmr_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rh_gam_alias210_redirect_config_0_mmr_s अणु
	अचिन्हित दीर्घ	rsvd_0_23 : 24;  /*    */
	अचिन्हित दीर्घ	dest_base : 22;  /* RW */
	अचिन्हित दीर्घ	rsvd_46_63: 18;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_1_MMR                  */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_1_MMR 0x16000e0UL

#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_1_MMR_DEST_BASE_SHFT 24
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_1_MMR_DEST_BASE_MASK 0x00003fffff000000UL

जोड़ uvh_rh_gam_alias210_redirect_config_1_mmr_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rh_gam_alias210_redirect_config_1_mmr_s अणु
	अचिन्हित दीर्घ	rsvd_0_23 : 24;  /*    */
	अचिन्हित दीर्घ	dest_base : 22;  /* RW */
	अचिन्हित दीर्घ	rsvd_46_63: 18;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_2_MMR                  */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_2_MMR 0x16000f0UL

#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_2_MMR_DEST_BASE_SHFT 24
#घोषणा UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_2_MMR_DEST_BASE_MASK 0x00003fffff000000UL

जोड़ uvh_rh_gam_alias210_redirect_config_2_mmr_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rh_gam_alias210_redirect_config_2_mmr_s अणु
	अचिन्हित दीर्घ	rsvd_0_23 : 24;  /*    */
	अचिन्हित दीर्घ	dest_base : 22;  /* RW */
	अचिन्हित दीर्घ	rsvd_46_63: 18;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR 0x1600010UL

#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_BASE_SHFT 28
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_BASE_MASK 0x00003ffff0000000UL
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_GR4_SHFT 48
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_GR4_MASK 0x0001000000000000UL
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_N_GRU_SHFT 52
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_N_GRU_MASK 0x00f0000000000000UL
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_ENABLE_SHFT 63
#घोषणा UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_ENABLE_MASK 0x8000000000000000UL

जोड़ uvh_rh_gam_gru_overlay_config_mmr_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rh_gam_gru_overlay_config_mmr_s अणु
	अचिन्हित दीर्घ	rsvd_0_27: 28;  /*    */
	अचिन्हित दीर्घ	base   : 18;  /* RW */
	अचिन्हित दीर्घ	rsvd_46_47:  2;  /*    */
	अचिन्हित दीर्घ	gr4    :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_49_51:  3;  /*    */
	अचिन्हित दीर्घ	n_gru  :  4;  /* RW */
	अचिन्हित दीर्घ	rsvd_56_62:  7;  /*    */
	अचिन्हित दीर्घ	enable :  1;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                    UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR                      */
/* ========================================================================= */
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR 0x1600028UL

#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_BASE_SHFT 26
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_BASE_MASK 0x00003ffffc000000UL
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_DUAL_HUB_SHFT 46
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_DUAL_HUB_MASK 0x0000400000000000UL
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_ENABLE_SHFT 63
#घोषणा UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR_ENABLE_MASK 0x8000000000000000UL

जोड़ uvh_rh_gam_mmr_overlay_config_mmr_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rh_gam_mmr_overlay_config_mmr_s अणु
	अचिन्हित दीर्घ	rsvd_0_25: 26;  /*    */
	अचिन्हित दीर्घ	base     : 20;  /* RW */
	अचिन्हित दीर्घ	dual_hub :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_47_62: 16;  /*    */
	अचिन्हित दीर्घ	enable   :  1;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                                 UVH_RTC                                   */
/* ========================================================================= */
#घोषणा UVH_RTC 0x340000UL

#घोषणा UVH_RTC_REAL_TIME_CLOCK_SHFT 0
#घोषणा UVH_RTC_REAL_TIME_CLOCK_MASK 0x00ffffffffffffffUL

जोड़ uvh_rtc_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rtc_s अणु
	अचिन्हित दीर्घ	real_समय_घड़ी : 56;  /* RW */
	अचिन्हित दीर्घ	rsvd_56_63      :  8;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                           UVH_RTC1_INT_CONFIG                             */
/* ========================================================================= */
#घोषणा UVH_RTC1_INT_CONFIG 0x615c0UL

#घोषणा UVH_RTC1_INT_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_RTC1_INT_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_RTC1_INT_CONFIG_DM_SHFT 8
#घोषणा UVH_RTC1_INT_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_RTC1_INT_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_RTC1_INT_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_RTC1_INT_CONFIG_STATUS_SHFT 12
#घोषणा UVH_RTC1_INT_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_RTC1_INT_CONFIG_P_SHFT 13
#घोषणा UVH_RTC1_INT_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_RTC1_INT_CONFIG_T_SHFT 15
#घोषणा UVH_RTC1_INT_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_RTC1_INT_CONFIG_M_SHFT 16
#घोषणा UVH_RTC1_INT_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_RTC1_INT_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_RTC1_INT_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_rtc1_पूर्णांक_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rtc1_पूर्णांक_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                           UVH_RTC2_INT_CONFIG                             */
/* ========================================================================= */
#घोषणा UVH_RTC2_INT_CONFIG 0x61600UL

#घोषणा UVH_RTC2_INT_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_RTC2_INT_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_RTC2_INT_CONFIG_DM_SHFT 8
#घोषणा UVH_RTC2_INT_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_RTC2_INT_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_RTC2_INT_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_RTC2_INT_CONFIG_STATUS_SHFT 12
#घोषणा UVH_RTC2_INT_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_RTC2_INT_CONFIG_P_SHFT 13
#घोषणा UVH_RTC2_INT_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_RTC2_INT_CONFIG_T_SHFT 15
#घोषणा UVH_RTC2_INT_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_RTC2_INT_CONFIG_M_SHFT 16
#घोषणा UVH_RTC2_INT_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_RTC2_INT_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_RTC2_INT_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_rtc2_पूर्णांक_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rtc2_पूर्णांक_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                           UVH_RTC3_INT_CONFIG                             */
/* ========================================================================= */
#घोषणा UVH_RTC3_INT_CONFIG 0x61640UL

#घोषणा UVH_RTC3_INT_CONFIG_VECTOR_SHFT 0
#घोषणा UVH_RTC3_INT_CONFIG_VECTOR_MASK 0x00000000000000ffUL
#घोषणा UVH_RTC3_INT_CONFIG_DM_SHFT 8
#घोषणा UVH_RTC3_INT_CONFIG_DM_MASK 0x0000000000000700UL
#घोषणा UVH_RTC3_INT_CONFIG_DESTMODE_SHFT 11
#घोषणा UVH_RTC3_INT_CONFIG_DESTMODE_MASK 0x0000000000000800UL
#घोषणा UVH_RTC3_INT_CONFIG_STATUS_SHFT 12
#घोषणा UVH_RTC3_INT_CONFIG_STATUS_MASK 0x0000000000001000UL
#घोषणा UVH_RTC3_INT_CONFIG_P_SHFT 13
#घोषणा UVH_RTC3_INT_CONFIG_P_MASK 0x0000000000002000UL
#घोषणा UVH_RTC3_INT_CONFIG_T_SHFT 15
#घोषणा UVH_RTC3_INT_CONFIG_T_MASK 0x0000000000008000UL
#घोषणा UVH_RTC3_INT_CONFIG_M_SHFT 16
#घोषणा UVH_RTC3_INT_CONFIG_M_MASK 0x0000000000010000UL
#घोषणा UVH_RTC3_INT_CONFIG_APIC_ID_SHFT 32
#घोषणा UVH_RTC3_INT_CONFIG_APIC_ID_MASK 0xffffffff00000000UL

जोड़ uvh_rtc3_पूर्णांक_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rtc3_पूर्णांक_config_s अणु
	अचिन्हित दीर्घ	vector_  :  8;  /* RW */
	अचिन्हित दीर्घ	dm       :  3;  /* RW */
	अचिन्हित दीर्घ	desपंचांगode :  1;  /* RW */
	अचिन्हित दीर्घ	status   :  1;  /* RO */
	अचिन्हित दीर्घ	p        :  1;  /* RO */
	अचिन्हित दीर्घ	rsvd_14  :  1;  /*    */
	अचिन्हित दीर्घ	t        :  1;  /* RO */
	अचिन्हित दीर्घ	m        :  1;  /* RW */
	अचिन्हित दीर्घ	rsvd_17_31: 15;  /*    */
	अचिन्हित दीर्घ	apic_id  : 32;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                            UVH_RTC_INC_RATIO                              */
/* ========================================================================= */
#घोषणा UVH_RTC_INC_RATIO 0x350000UL

#घोषणा UVH_RTC_INC_RATIO_FRACTION_SHFT 0
#घोषणा UVH_RTC_INC_RATIO_FRACTION_MASK 0x00000000000fffffUL
#घोषणा UVH_RTC_INC_RATIO_RATIO_SHFT 20
#घोषणा UVH_RTC_INC_RATIO_RATIO_MASK 0x0000000000700000UL

जोड़ uvh_rtc_inc_ratio_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_rtc_inc_ratio_s अणु
	अचिन्हित दीर्घ	fraction : 20;  /* RW */
	अचिन्हित दीर्घ	ratio    :  3;  /* RW */
	अचिन्हित दीर्घ	rsvd_23_63: 41;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                          UVH_SI_ADDR_MAP_CONFIG                           */
/* ========================================================================= */
#घोषणा UVH_SI_ADDR_MAP_CONFIG 0xc80000UL

#घोषणा UVH_SI_ADDR_MAP_CONFIG_M_SKT_SHFT 0
#घोषणा UVH_SI_ADDR_MAP_CONFIG_M_SKT_MASK 0x000000000000003fUL
#घोषणा UVH_SI_ADDR_MAP_CONFIG_N_SKT_SHFT 8
#घोषणा UVH_SI_ADDR_MAP_CONFIG_N_SKT_MASK 0x0000000000000f00UL

जोड़ uvh_si_addr_map_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_si_addr_map_config_s अणु
	अचिन्हित दीर्घ	m_skt :  6;  /* RW */
	अचिन्हित दीर्घ	rsvd_6_7:  2;  /*    */
	अचिन्हित दीर्घ	n_skt :  4;  /* RW */
	अचिन्हित दीर्घ	rsvd_12_63: 52;  /*    */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                       UVH_SI_ALIAS0_OVERLAY_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG 0xc80008UL

#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_BASE_SHFT 24
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_BASE_MASK 0x00000000ff000000UL
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_M_ALIAS_SHFT 48
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_M_ALIAS_MASK 0x001f000000000000UL
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_ENABLE_SHFT 63
#घोषणा UVH_SI_ALIAS0_OVERLAY_CONFIG_ENABLE_MASK 0x8000000000000000UL

जोड़ uvh_si_alias0_overlay_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_si_alias0_overlay_config_s अणु
	अचिन्हित दीर्घ	rsvd_0_23: 24;  /*    */
	अचिन्हित दीर्घ	base    :  8;  /* RW */
	अचिन्हित दीर्घ	rsvd_32_47: 16;  /*    */
	अचिन्हित दीर्घ	m_alias :  5;  /* RW */
	अचिन्हित दीर्घ	rsvd_53_62: 10;  /*    */
	अचिन्हित दीर्घ	enable  :  1;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                       UVH_SI_ALIAS1_OVERLAY_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG 0xc80010UL

#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_BASE_SHFT 24
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_BASE_MASK 0x00000000ff000000UL
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_M_ALIAS_SHFT 48
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_M_ALIAS_MASK 0x001f000000000000UL
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_ENABLE_SHFT 63
#घोषणा UVH_SI_ALIAS1_OVERLAY_CONFIG_ENABLE_MASK 0x8000000000000000UL

जोड़ uvh_si_alias1_overlay_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_si_alias1_overlay_config_s अणु
	अचिन्हित दीर्घ	rsvd_0_23: 24;  /*    */
	अचिन्हित दीर्घ	base    :  8;  /* RW */
	अचिन्हित दीर्घ	rsvd_32_47: 16;  /*    */
	अचिन्हित दीर्घ	m_alias :  5;  /* RW */
	अचिन्हित दीर्घ	rsvd_53_62: 10;  /*    */
	अचिन्हित दीर्घ	enable  :  1;  /* RW */
    पूर्ण s;
पूर्ण;

/* ========================================================================= */
/*                       UVH_SI_ALIAS2_OVERLAY_CONFIG                        */
/* ========================================================================= */
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG 0xc80018UL

#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_BASE_SHFT 24
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_BASE_MASK 0x00000000ff000000UL
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_M_ALIAS_SHFT 48
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_M_ALIAS_MASK 0x001f000000000000UL
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_ENABLE_SHFT 63
#घोषणा UVH_SI_ALIAS2_OVERLAY_CONFIG_ENABLE_MASK 0x8000000000000000UL

जोड़ uvh_si_alias2_overlay_config_u अणु
    अचिन्हित दीर्घ	v;
    काष्ठा uvh_si_alias2_overlay_config_s अणु
	अचिन्हित दीर्घ	rsvd_0_23: 24;  /*    */
	अचिन्हित दीर्घ	base    :  8;  /* RW */
	अचिन्हित दीर्घ	rsvd_32_47: 16;  /*    */
	अचिन्हित दीर्घ	m_alias :  5;  /* RW */
	अचिन्हित दीर्घ	rsvd_53_62: 10;  /*    */
	अचिन्हित दीर्घ	enable  :  1;  /* RW */
    पूर्ण s;
पूर्ण;


#पूर्ण_अगर /* _ASM_IA64_UV_UV_MMRS_H */
